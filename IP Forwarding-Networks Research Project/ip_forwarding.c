/*
  2  * INET         An implementation of the TCP/IP protocol suite for the LINUX
  3  *              operating system.  INET is implemented using the  BSD Socket
  4  *              interface as the means of communication with the user level.
  5  *
  6  *              The IP forwarding functionality.
  7  *
  8  * Authors:     see ip.c
  9  *
 10  * Fixes:
 11  *              Many            :       Split from ip.c , see ip_input.c for
 12  *                                      history.
 13  *              Dave Gregorich  :       NULL ip_rt_put fix for multicast
 14  *                                      routing.
 15  *              Jos Vos         :       Add call_out_firewall before sending,
 16  *                                      use output device for accounting.
 17  *              Jos Vos         :       Call forward firewall after routing
 18  *                                      (always use output device).
 19  *              Mike McLagan    :       Routing by source
 20  */
 21 
 22 #include <linux/types.h>
 23 #include <linux/mm.h>
 24 #include <linux/skbuff.h>
 25 #include <linux/ip.h>
 26 #include <linux/icmp.h>
 27 #include <linux/netdevice.h>
 28 #include <linux/slab.h>
 29 #include <net/sock.h>
 30 #include <net/ip.h>
 31 #include <net/tcp.h>
 32 #include <net/udp.h>
 33 #include <net/icmp.h>
 34 #include <linux/tcp.h>
 35 #include <linux/udp.h>
 36 #include <linux/netfilter_ipv4.h>
 37 #include <net/checksum.h>
 38 #include <linux/route.h>
 39 #include <net/route.h>
 40 #include <net/xfrm.h>
 41 
 42 static bool ip_exceeds_mtu(const struct sk_buff *skb, unsigned int mtu)
 43 {
 44         if (skb->len <= mtu)
 45                 return false;
 46 
 47         if (unlikely((ip_hdr(skb)->frag_off & htons(IP_DF)) == 0))
 48                 return false;
 49 
 50         /* original fragment exceeds mtu and DF is set */
 51         if (unlikely(IPCB(skb)->frag_max_size > mtu))
 52                 return true;
 53 
 54         if (skb->ignore_df)
 55                 return false;
 56 
 57         if (skb_is_gso(skb) && skb_gso_network_seglen(skb) <= mtu)
 58                 return false;
 59 
 60         return true;
 61 }
 62 
 63 
 64 static int ip_forward_finish(struct sock *sk, struct sk_buff *skb)
 65 {
 66         struct ip_options *opt  = &(IPCB(skb)->opt);
 67 
 68         IP_INC_STATS_BH(dev_net(skb_dst(skb)->dev), IPSTATS_MIB_OUTFORWDATAGRAMS);
 69         IP_ADD_STATS_BH(dev_net(skb_dst(skb)->dev), IPSTATS_MIB_OUTOCTETS, skb->len);
 70 
 71         if (unlikely(opt->optlen))
 72                 ip_forward_options(skb);
 73 
 74         skb_sender_cpu_clear(skb);
 75         return dst_output_sk(sk, skb);
 76 }
 77 
 78 int ip_forward(struct sk_buff *skb)
 79 {
 80         u32 mtu;
 81         struct iphdr *iph;      /* Our header */
 82         struct rtable *rt;      /* Route we use */
 83         struct ip_options *opt  = &(IPCB(skb)->opt);
 84 
 85         /* that should never happen */
 86         if (skb->pkt_type != PACKET_HOST)
 87                 goto drop;
 88 
 89         if (unlikely(skb->sk))
 90                 goto drop;
 91 
 92         if (skb_warn_if_lro(skb))
 93                 goto drop;
 94 
 95         if (!xfrm4_policy_check(NULL, XFRM_POLICY_FWD, skb))
 96                 goto drop;
 97 
 98         if (IPCB(skb)->opt.router_alert && ip_call_ra_chain(skb))
 99                 return NET_RX_SUCCESS;
100 
101         skb_forward_csum(skb);
102 
103         /*
104          *      According to the RFC, we must first decrease the TTL field. If
105          *      that reaches zero, we must reply an ICMP control message telling
106          *      that the packet's lifetime expired.
107          */
108         if (ip_hdr(skb)->ttl <= 1)
109                 goto too_many_hops;
110 
111         if (!xfrm4_route_forward(skb))
112                 goto drop;
113 
114         rt = skb_rtable(skb);
115 
116         if (opt->is_strictroute && rt->rt_uses_gateway)
117                 goto sr_failed;
118 
119         IPCB(skb)->flags |= IPSKB_FORWARDED;
120         mtu = ip_dst_mtu_maybe_forward(&rt->dst, true);
121         if (ip_exceeds_mtu(skb, mtu)) {
122                 IP_INC_STATS(dev_net(rt->dst.dev), IPSTATS_MIB_FRAGFAILS);
123                 icmp_send(skb, ICMP_DEST_UNREACH, ICMP_FRAG_NEEDED,
124                           htonl(mtu));
125                 goto drop;
126         }
127 
128         /* We are about to mangle packet. Copy it! */
129         if (skb_cow(skb, LL_RESERVED_SPACE(rt->dst.dev)+rt->dst.header_len))
130                 goto drop;
131         iph = ip_hdr(skb);
132 
133         /* Decrease ttl after skb cow done */
134         ip_decrease_ttl(iph);
135 
136         /*
137          *      We now generate an ICMP HOST REDIRECT giving the route
138          *      we calculated.
139          */
140         if (IPCB(skb)->flags & IPSKB_DOREDIRECT && !opt->srr &&
141             !skb_sec_path(skb))
142                 ip_rt_send_redirect(skb);
143 
144         skb->priority = rt_tos2priority(iph->tos);
145 
146         return NF_HOOK(NFPROTO_IPV4, NF_INET_FORWARD, NULL, skb,
147                        skb->dev, rt->dst.dev, ip_forward_finish);
148 
149 sr_failed:
150         /*
151          *      Strict routing permits no gatewaying
152          */
153          icmp_send(skb, ICMP_DEST_UNREACH, ICMP_SR_FAILED, 0);
154          goto drop;
155 
156 too_many_hops:
157         /* Tell the sender its packet died... */
158         IP_INC_STATS_BH(dev_net(skb_dst(skb)->dev), IPSTATS_MIB_INHDRERRORS);
159         icmp_send(skb, ICMP_TIME_EXCEEDED, ICMP_EXC_TTL, 0);
160 drop:
161         kfree_skb(skb);
162         return NET_RX_DROP;
163 }
164 