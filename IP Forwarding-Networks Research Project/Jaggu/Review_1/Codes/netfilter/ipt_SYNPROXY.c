<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title>Linux/net/ipv4/netfilter/ipt_SYNPROXY.c - Linux Cross Reference - Free Electrons</title>
<link rel="stylesheet" href="/style.css" type="text/css" media="screen" />
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />
<meta description="Linux Cross-Reference (LXR) service by Free Electrons. The easiest way to study Linux kernel sources. Available for all recent releases." />
<base href="http://lxr.free-electrons.com/"/>
</head>

<body>

<div id="wrapper">
<div id="wrapper2">
<div id="header">

	<div id="logo">
		<h1>Linux Cross Reference</h1>
		<h2><a href="http://free-electrons.com">Free Electrons</a></h2>
		<h2>Embedded Linux Experts</h2>
		<p>
		 &nbsp;&bull;&nbsp;<b><i>source navigation</i></b> &nbsp;&bull;&nbsp;<a href="diff/net/ipv4/netfilter/ipt_SYNPROXY.c">diff markup</a> &nbsp;&bull;&nbsp;<a href="ident">identifier search</a> &nbsp;&bull;&nbsp;<a href="search">freetext search</a> &nbsp;&bull;&nbsp;
		</p>
	</div>
</div>

<div id="topbar">
  
  <p>Version: &nbsp;<a href="source/net/ipv4/netfilter/ipt_SYNPROXY.c?v=2.0.40">2.0.40</a>&nbsp;<a href="source/net/ipv4/netfilter/ipt_SYNPROXY.c?v=2.2.26">2.2.26</a>&nbsp;<a href="source/net/ipv4/netfilter/ipt_SYNPROXY.c?v=2.4.37">2.4.37</a>&nbsp;<a href="source/net/ipv4/netfilter/ipt_SYNPROXY.c?v=3.5">3.5</a>&nbsp;<a href="source/net/ipv4/netfilter/ipt_SYNPROXY.c?v=3.6">3.6</a>&nbsp;<a href="source/net/ipv4/netfilter/ipt_SYNPROXY.c?v=3.7">3.7</a>&nbsp;<a href="source/net/ipv4/netfilter/ipt_SYNPROXY.c?v=3.8">3.8</a>&nbsp;<a href="source/net/ipv4/netfilter/ipt_SYNPROXY.c?v=3.9">3.9</a>&nbsp;<a href="source/net/ipv4/netfilter/ipt_SYNPROXY.c?v=3.10">3.10</a>&nbsp;<a href="source/net/ipv4/netfilter/ipt_SYNPROXY.c?v=3.11">3.11</a>&nbsp;<a href="source/net/ipv4/netfilter/ipt_SYNPROXY.c?v=3.12">3.12</a>&nbsp;<a href="source/net/ipv4/netfilter/ipt_SYNPROXY.c?v=3.13">3.13</a>&nbsp;<a href="source/net/ipv4/netfilter/ipt_SYNPROXY.c?v=3.14">3.14</a>&nbsp;<a href="source/net/ipv4/netfilter/ipt_SYNPROXY.c?v=3.15">3.15</a>&nbsp;<a href="source/net/ipv4/netfilter/ipt_SYNPROXY.c?v=3.16">3.16</a>&nbsp;<a href="source/net/ipv4/netfilter/ipt_SYNPROXY.c?v=3.17">3.17</a>&nbsp;<a href="source/net/ipv4/netfilter/ipt_SYNPROXY.c?v=3.18">3.18</a>&nbsp;<a href="source/net/ipv4/netfilter/ipt_SYNPROXY.c?v=3.19">3.19</a>&nbsp;<a href="source/net/ipv4/netfilter/ipt_SYNPROXY.c?v=4.0">4.0</a>&nbsp;<b><i>4.1</i></b></p>
  
</div>

<h1><a href="source/">Linux</a>/<a href="source/net/">net</a>/<a href="source/net/ipv4/">ipv4</a>/<a href="source/net/ipv4/netfilter/">netfilter</a>/<a href="source/net/ipv4/netfilter/ipt_SYNPROXY.c">ipt_SYNPROXY.c</a></h1>
<div id="lxrcode"><pre>  <a name="L1" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L1">1</a> <b><i>/*</i></b>
  <a name="L2" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L2">2</a> <b><i> * Copyright (c) 2013 Patrick McHardy &lt;kaber@trash.net&gt;</i></b>
  <a name="L3" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L3">3</a> <b><i> *</i></b>
  <a name="L4" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L4">4</a> <b><i> * This program is free software; you can redistribute it and/or modify</i></b>
  <a name="L5" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L5">5</a> <b><i> * it under the terms of the GNU General Public License version 2 as</i></b>
  <a name="L6" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L6">6</a> <b><i> * published by the Free Software Foundation.</i></b>
  <a name="L7" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L7">7</a> <b><i> */</i></b>
  <a name="L8" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L8">8</a> 
  <a name="L9" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L9">9</a> #include &lt;linux/module.h&gt;
 <a name="L10" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L10">10</a> #include &lt;linux/skbuff.h&gt;
 <a name="L11" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L11">11</a> #include &lt;net/tcp.h&gt;
 <a name="L12" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L12">12</a> 
 <a name="L13" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L13">13</a> #include &lt;linux/netfilter_ipv4/ip_tables.h&gt;
 <a name="L14" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L14">14</a> #include &lt;linux/netfilter/x_tables.h&gt;
 <a name="L15" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L15">15</a> #include &lt;linux/netfilter/xt_SYNPROXY.h&gt;
 <a name="L16" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L16">16</a> #include &lt;net/netfilter/nf_conntrack.h&gt;
 <a name="L17" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L17">17</a> #include &lt;net/netfilter/nf_conntrack_seqadj.h&gt;
 <a name="L18" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L18">18</a> #include &lt;net/netfilter/nf_conntrack_synproxy.h&gt;
 <a name="L19" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L19">19</a> 
 <a name="L20" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L20">20</a> static struct <a href="ident?i=iphdr">iphdr</a> *
 <a name="L21" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L21">21</a> <a href="ident?i=synproxy_build_ip">synproxy_build_ip</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, <a href="ident?i=u32">u32</a> <a href="ident?i=saddr">saddr</a>, <a href="ident?i=u32">u32</a> <a href="ident?i=daddr">daddr</a>)
 <a name="L22" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L22">22</a> {
 <a name="L23" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L23">23</a>         struct <a href="ident?i=iphdr">iphdr</a> *iph;
 <a name="L24" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L24">24</a> 
 <a name="L25" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L25">25</a>         <a href="ident?i=skb_reset_network_header">skb_reset_network_header</a>(<a href="ident?i=skb">skb</a>);
 <a name="L26" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L26">26</a>         iph = (struct <a href="ident?i=iphdr">iphdr</a> *)<a href="ident?i=skb_put">skb_put</a>(<a href="ident?i=skb">skb</a>, sizeof(*iph));
 <a name="L27" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L27">27</a>         iph-&gt;<a href="ident?i=version">version</a>    = 4;
 <a name="L28" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L28">28</a>         iph-&gt;ihl        = sizeof(*iph) / 4;
 <a name="L29" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L29">29</a>         iph-&gt;tos        = 0;
 <a name="L30" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L30">30</a>         iph-&gt;<a href="ident?i=id">id</a>         = 0;
 <a name="L31" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L31">31</a>         iph-&gt;frag_off   = <a href="ident?i=htons">htons</a>(<a href="ident?i=IP_DF">IP_DF</a>);
 <a name="L32" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L32">32</a>         iph-&gt;<a href="ident?i=ttl">ttl</a>        = <a href="ident?i=sysctl_ip_default_ttl">sysctl_ip_default_ttl</a>;
 <a name="L33" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L33">33</a>         iph-&gt;<a href="ident?i=protocol">protocol</a>   = <a href="ident?i=IPPROTO_TCP">IPPROTO_TCP</a>;
 <a name="L34" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L34">34</a>         iph-&gt;<a href="ident?i=check">check</a>      = 0;
 <a name="L35" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L35">35</a>         iph-&gt;<a href="ident?i=saddr">saddr</a>      = <a href="ident?i=saddr">saddr</a>;
 <a name="L36" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L36">36</a>         iph-&gt;<a href="ident?i=daddr">daddr</a>      = <a href="ident?i=daddr">daddr</a>;
 <a name="L37" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L37">37</a> 
 <a name="L38" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L38">38</a>         return iph;
 <a name="L39" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L39">39</a> }
 <a name="L40" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L40">40</a> 
 <a name="L41" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L41">41</a> static void
 <a name="L42" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L42">42</a> <a href="ident?i=synproxy_send_tcp">synproxy_send_tcp</a>(const struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, struct <a href="ident?i=sk_buff">sk_buff</a> *nskb,
 <a name="L43" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L43">43</a>                   struct <a href="ident?i=nf_conntrack">nf_conntrack</a> *nfct, enum <a href="ident?i=ip_conntrack_info">ip_conntrack_info</a> ctinfo,
 <a name="L44" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L44">44</a>                   struct <a href="ident?i=iphdr">iphdr</a> *niph, struct <a href="ident?i=tcphdr">tcphdr</a> *nth,
 <a name="L45" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L45">45</a>                   unsigned int tcp_hdr_size)
 <a name="L46" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L46">46</a> {
 <a name="L47" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L47">47</a>         nth-&gt;<a href="ident?i=check">check</a> = ~tcp_v4_check(tcp_hdr_size, niph-&gt;<a href="ident?i=saddr">saddr</a>, niph-&gt;<a href="ident?i=daddr">daddr</a>, 0);
 <a name="L48" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L48">48</a>         nskb-&gt;ip_summed   = <a href="ident?i=CHECKSUM_PARTIAL">CHECKSUM_PARTIAL</a>;
 <a name="L49" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L49">49</a>         nskb-&gt;csum_start  = (unsigned char *)nth - nskb-&gt;<a href="ident?i=head">head</a>;
 <a name="L50" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L50">50</a>         nskb-&gt;csum_offset = <a href="ident?i=offsetof">offsetof</a>(struct <a href="ident?i=tcphdr">tcphdr</a>, <a href="ident?i=check">check</a>);
 <a name="L51" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L51">51</a> 
 <a name="L52" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L52">52</a>         <a href="ident?i=skb_dst_set_noref">skb_dst_set_noref</a>(nskb, <a href="ident?i=skb_dst">skb_dst</a>(<a href="ident?i=skb">skb</a>));
 <a name="L53" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L53">53</a>         nskb-&gt;<a href="ident?i=protocol">protocol</a> = <a href="ident?i=htons">htons</a>(<a href="ident?i=ETH_P_IP">ETH_P_IP</a>);
 <a name="L54" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L54">54</a>         if (<a href="ident?i=ip_route_me_harder">ip_route_me_harder</a>(nskb, RTN_UNSPEC))
 <a name="L55" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L55">55</a>                 goto free_nskb;
 <a name="L56" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L56">56</a> 
 <a name="L57" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L57">57</a>         if (nfct) {
 <a name="L58" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L58">58</a>                 nskb-&gt;nfct = nfct;
 <a name="L59" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L59">59</a>                 nskb-&gt;nfctinfo = ctinfo;
 <a name="L60" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L60">60</a>                 <a href="ident?i=nf_conntrack_get">nf_conntrack_get</a>(nfct);
 <a name="L61" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L61">61</a>         }
 <a name="L62" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L62">62</a> 
 <a name="L63" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L63">63</a>         <a href="ident?i=ip_local_out">ip_local_out</a>(nskb);
 <a name="L64" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L64">64</a>         return;
 <a name="L65" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L65">65</a> 
 <a name="L66" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L66">66</a> free_nskb:
 <a name="L67" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L67">67</a>         <a href="ident?i=kfree_skb">kfree_skb</a>(nskb);
 <a name="L68" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L68">68</a> }
 <a name="L69" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L69">69</a> 
 <a name="L70" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L70">70</a> static void
 <a name="L71" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L71">71</a> <a href="ident?i=synproxy_send_client_synack">synproxy_send_client_synack</a>(const struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, const struct <a href="ident?i=tcphdr">tcphdr</a> *<a href="ident?i=th">th</a>,
 <a name="L72" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L72">72</a>                             const struct <a href="ident?i=synproxy_options">synproxy_options</a> *<a href="ident?i=opts">opts</a>)
 <a name="L73" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L73">73</a> {
 <a name="L74" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L74">74</a>         struct <a href="ident?i=sk_buff">sk_buff</a> *nskb;
 <a name="L75" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L75">75</a>         struct <a href="ident?i=iphdr">iphdr</a> *iph, *niph;
 <a name="L76" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L76">76</a>         struct <a href="ident?i=tcphdr">tcphdr</a> *nth;
 <a name="L77" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L77">77</a>         unsigned int tcp_hdr_size;
 <a name="L78" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L78">78</a>         <a href="ident?i=u16">u16</a> mss = <a href="ident?i=opts">opts</a>-&gt;mss;
 <a name="L79" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L79">79</a> 
 <a name="L80" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L80">80</a>         iph = <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>);
 <a name="L81" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L81">81</a> 
 <a name="L82" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L82">82</a>         tcp_hdr_size = sizeof(*nth) + <a href="ident?i=synproxy_options_size">synproxy_options_size</a>(<a href="ident?i=opts">opts</a>);
 <a name="L83" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L83">83</a>         nskb = <a href="ident?i=alloc_skb">alloc_skb</a>(sizeof(*niph) + tcp_hdr_size + <a href="ident?i=MAX_TCP_HEADER">MAX_TCP_HEADER</a>,
 <a name="L84" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L84">84</a>                          <a href="ident?i=GFP_ATOMIC">GFP_ATOMIC</a>);
 <a name="L85" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L85">85</a>         if (nskb == <a href="ident?i=NULL">NULL</a>)
 <a name="L86" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L86">86</a>                 return;
 <a name="L87" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L87">87</a>         <a href="ident?i=skb_reserve">skb_reserve</a>(nskb, <a href="ident?i=MAX_TCP_HEADER">MAX_TCP_HEADER</a>);
 <a name="L88" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L88">88</a> 
 <a name="L89" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L89">89</a>         niph = <a href="ident?i=synproxy_build_ip">synproxy_build_ip</a>(nskb, iph-&gt;<a href="ident?i=daddr">daddr</a>, iph-&gt;<a href="ident?i=saddr">saddr</a>);
 <a name="L90" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L90">90</a> 
 <a name="L91" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L91">91</a>         <a href="ident?i=skb_reset_transport_header">skb_reset_transport_header</a>(nskb);
 <a name="L92" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L92">92</a>         nth = (struct <a href="ident?i=tcphdr">tcphdr</a> *)<a href="ident?i=skb_put">skb_put</a>(nskb, tcp_hdr_size);
 <a name="L93" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L93">93</a>         nth-&gt;source     = <a href="ident?i=th">th</a>-&gt;<a href="ident?i=dest">dest</a>;
 <a name="L94" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L94">94</a>         nth-&gt;<a href="ident?i=dest">dest</a>       = <a href="ident?i=th">th</a>-&gt;source;
 <a name="L95" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L95">95</a>         nth-&gt;<a href="ident?i=seq">seq</a>        = <a href="ident?i=htonl">htonl</a>(<a href="ident?i=__cookie_v4_init_sequence">__cookie_v4_init_sequence</a>(iph, <a href="ident?i=th">th</a>, &amp;mss));
 <a name="L96" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L96">96</a>         nth-&gt;ack_seq    = <a href="ident?i=htonl">htonl</a>(<a href="ident?i=ntohl">ntohl</a>(<a href="ident?i=th">th</a>-&gt;<a href="ident?i=seq">seq</a>) + 1);
 <a name="L97" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L97">97</a>         <a href="ident?i=tcp_flag_word">tcp_flag_word</a>(nth) = TCP_FLAG_SYN | TCP_FLAG_ACK;
 <a name="L98" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L98">98</a>         if (<a href="ident?i=opts">opts</a>-&gt;<a href="ident?i=options">options</a> &amp; <a href="ident?i=XT_SYNPROXY_OPT_ECN">XT_SYNPROXY_OPT_ECN</a>)
 <a name="L99" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L99">99</a>                 <a href="ident?i=tcp_flag_word">tcp_flag_word</a>(nth) |= TCP_FLAG_ECE;
<a name="L100" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L100">100</a>         nth-&gt;doff       = tcp_hdr_size / 4;
<a name="L101" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L101">101</a>         nth-&gt;<a href="ident?i=window">window</a>     = 0;
<a name="L102" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L102">102</a>         nth-&gt;<a href="ident?i=check">check</a>      = 0;
<a name="L103" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L103">103</a>         nth-&gt;urg_ptr    = 0;
<a name="L104" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L104">104</a> 
<a name="L105" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L105">105</a>         <a href="ident?i=synproxy_build_options">synproxy_build_options</a>(nth, <a href="ident?i=opts">opts</a>);
<a name="L106" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L106">106</a> 
<a name="L107" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L107">107</a>         <a href="ident?i=synproxy_send_tcp">synproxy_send_tcp</a>(<a href="ident?i=skb">skb</a>, nskb, <a href="ident?i=skb">skb</a>-&gt;nfct, IP_CT_ESTABLISHED_REPLY,
<a name="L108" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L108">108</a>                           niph, nth, tcp_hdr_size);
<a name="L109" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L109">109</a> }
<a name="L110" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L110">110</a> 
<a name="L111" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L111">111</a> static void
<a name="L112" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L112">112</a> <a href="ident?i=synproxy_send_server_syn">synproxy_send_server_syn</a>(const struct <a href="ident?i=synproxy_net">synproxy_net</a> *snet,
<a name="L113" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L113">113</a>                          const struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, const struct <a href="ident?i=tcphdr">tcphdr</a> *<a href="ident?i=th">th</a>,
<a name="L114" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L114">114</a>                          const struct <a href="ident?i=synproxy_options">synproxy_options</a> *<a href="ident?i=opts">opts</a>, <a href="ident?i=u32">u32</a> recv_seq)
<a name="L115" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L115">115</a> {
<a name="L116" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L116">116</a>         struct <a href="ident?i=sk_buff">sk_buff</a> *nskb;
<a name="L117" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L117">117</a>         struct <a href="ident?i=iphdr">iphdr</a> *iph, *niph;
<a name="L118" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L118">118</a>         struct <a href="ident?i=tcphdr">tcphdr</a> *nth;
<a name="L119" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L119">119</a>         unsigned int tcp_hdr_size;
<a name="L120" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L120">120</a> 
<a name="L121" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L121">121</a>         iph = <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>);
<a name="L122" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L122">122</a> 
<a name="L123" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L123">123</a>         tcp_hdr_size = sizeof(*nth) + <a href="ident?i=synproxy_options_size">synproxy_options_size</a>(<a href="ident?i=opts">opts</a>);
<a name="L124" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L124">124</a>         nskb = <a href="ident?i=alloc_skb">alloc_skb</a>(sizeof(*niph) + tcp_hdr_size + <a href="ident?i=MAX_TCP_HEADER">MAX_TCP_HEADER</a>,
<a name="L125" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L125">125</a>                          <a href="ident?i=GFP_ATOMIC">GFP_ATOMIC</a>);
<a name="L126" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L126">126</a>         if (nskb == <a href="ident?i=NULL">NULL</a>)
<a name="L127" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L127">127</a>                 return;
<a name="L128" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L128">128</a>         <a href="ident?i=skb_reserve">skb_reserve</a>(nskb, <a href="ident?i=MAX_TCP_HEADER">MAX_TCP_HEADER</a>);
<a name="L129" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L129">129</a> 
<a name="L130" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L130">130</a>         niph = <a href="ident?i=synproxy_build_ip">synproxy_build_ip</a>(nskb, iph-&gt;<a href="ident?i=saddr">saddr</a>, iph-&gt;<a href="ident?i=daddr">daddr</a>);
<a name="L131" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L131">131</a> 
<a name="L132" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L132">132</a>         <a href="ident?i=skb_reset_transport_header">skb_reset_transport_header</a>(nskb);
<a name="L133" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L133">133</a>         nth = (struct <a href="ident?i=tcphdr">tcphdr</a> *)<a href="ident?i=skb_put">skb_put</a>(nskb, tcp_hdr_size);
<a name="L134" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L134">134</a>         nth-&gt;source     = <a href="ident?i=th">th</a>-&gt;source;
<a name="L135" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L135">135</a>         nth-&gt;<a href="ident?i=dest">dest</a>       = <a href="ident?i=th">th</a>-&gt;<a href="ident?i=dest">dest</a>;
<a name="L136" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L136">136</a>         nth-&gt;<a href="ident?i=seq">seq</a>        = <a href="ident?i=htonl">htonl</a>(recv_seq - 1);
<a name="L137" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L137">137</a>         <b><i>/* ack_seq is used to relay our ISN to the synproxy hook to initialize</i></b>
<a name="L138" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L138">138</a> <b><i>         * sequence number translation once a connection tracking entry exists.</i></b>
<a name="L139" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L139">139</a> <b><i>         */</i></b>
<a name="L140" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L140">140</a>         nth-&gt;ack_seq    = <a href="ident?i=htonl">htonl</a>(<a href="ident?i=ntohl">ntohl</a>(<a href="ident?i=th">th</a>-&gt;ack_seq) - 1);
<a name="L141" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L141">141</a>         <a href="ident?i=tcp_flag_word">tcp_flag_word</a>(nth) = TCP_FLAG_SYN;
<a name="L142" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L142">142</a>         if (<a href="ident?i=opts">opts</a>-&gt;<a href="ident?i=options">options</a> &amp; <a href="ident?i=XT_SYNPROXY_OPT_ECN">XT_SYNPROXY_OPT_ECN</a>)
<a name="L143" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L143">143</a>                 <a href="ident?i=tcp_flag_word">tcp_flag_word</a>(nth) |= TCP_FLAG_ECE | TCP_FLAG_CWR;
<a name="L144" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L144">144</a>         nth-&gt;doff       = tcp_hdr_size / 4;
<a name="L145" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L145">145</a>         nth-&gt;<a href="ident?i=window">window</a>     = <a href="ident?i=th">th</a>-&gt;<a href="ident?i=window">window</a>;
<a name="L146" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L146">146</a>         nth-&gt;<a href="ident?i=check">check</a>      = 0;
<a name="L147" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L147">147</a>         nth-&gt;urg_ptr    = 0;
<a name="L148" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L148">148</a> 
<a name="L149" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L149">149</a>         <a href="ident?i=synproxy_build_options">synproxy_build_options</a>(nth, <a href="ident?i=opts">opts</a>);
<a name="L150" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L150">150</a> 
<a name="L151" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L151">151</a>         <a href="ident?i=synproxy_send_tcp">synproxy_send_tcp</a>(<a href="ident?i=skb">skb</a>, nskb, &amp;snet-&gt;tmpl-&gt;ct_general, IP_CT_NEW,
<a name="L152" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L152">152</a>                           niph, nth, tcp_hdr_size);
<a name="L153" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L153">153</a> }
<a name="L154" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L154">154</a> 
<a name="L155" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L155">155</a> static void
<a name="L156" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L156">156</a> <a href="ident?i=synproxy_send_server_ack">synproxy_send_server_ack</a>(const struct <a href="ident?i=synproxy_net">synproxy_net</a> *snet,
<a name="L157" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L157">157</a>                          const struct <a href="ident?i=ip_ct_tcp">ip_ct_tcp</a> *<a href="ident?i=state">state</a>,
<a name="L158" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L158">158</a>                          const struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, const struct <a href="ident?i=tcphdr">tcphdr</a> *<a href="ident?i=th">th</a>,
<a name="L159" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L159">159</a>                          const struct <a href="ident?i=synproxy_options">synproxy_options</a> *<a href="ident?i=opts">opts</a>)
<a name="L160" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L160">160</a> {
<a name="L161" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L161">161</a>         struct <a href="ident?i=sk_buff">sk_buff</a> *nskb;
<a name="L162" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L162">162</a>         struct <a href="ident?i=iphdr">iphdr</a> *iph, *niph;
<a name="L163" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L163">163</a>         struct <a href="ident?i=tcphdr">tcphdr</a> *nth;
<a name="L164" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L164">164</a>         unsigned int tcp_hdr_size;
<a name="L165" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L165">165</a> 
<a name="L166" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L166">166</a>         iph = <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>);
<a name="L167" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L167">167</a> 
<a name="L168" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L168">168</a>         tcp_hdr_size = sizeof(*nth) + <a href="ident?i=synproxy_options_size">synproxy_options_size</a>(<a href="ident?i=opts">opts</a>);
<a name="L169" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L169">169</a>         nskb = <a href="ident?i=alloc_skb">alloc_skb</a>(sizeof(*niph) + tcp_hdr_size + <a href="ident?i=MAX_TCP_HEADER">MAX_TCP_HEADER</a>,
<a name="L170" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L170">170</a>                          <a href="ident?i=GFP_ATOMIC">GFP_ATOMIC</a>);
<a name="L171" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L171">171</a>         if (nskb == <a href="ident?i=NULL">NULL</a>)
<a name="L172" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L172">172</a>                 return;
<a name="L173" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L173">173</a>         <a href="ident?i=skb_reserve">skb_reserve</a>(nskb, <a href="ident?i=MAX_TCP_HEADER">MAX_TCP_HEADER</a>);
<a name="L174" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L174">174</a> 
<a name="L175" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L175">175</a>         niph = <a href="ident?i=synproxy_build_ip">synproxy_build_ip</a>(nskb, iph-&gt;<a href="ident?i=daddr">daddr</a>, iph-&gt;<a href="ident?i=saddr">saddr</a>);
<a name="L176" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L176">176</a> 
<a name="L177" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L177">177</a>         <a href="ident?i=skb_reset_transport_header">skb_reset_transport_header</a>(nskb);
<a name="L178" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L178">178</a>         nth = (struct <a href="ident?i=tcphdr">tcphdr</a> *)<a href="ident?i=skb_put">skb_put</a>(nskb, tcp_hdr_size);
<a name="L179" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L179">179</a>         nth-&gt;source     = <a href="ident?i=th">th</a>-&gt;<a href="ident?i=dest">dest</a>;
<a name="L180" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L180">180</a>         nth-&gt;<a href="ident?i=dest">dest</a>       = <a href="ident?i=th">th</a>-&gt;source;
<a name="L181" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L181">181</a>         nth-&gt;<a href="ident?i=seq">seq</a>        = <a href="ident?i=htonl">htonl</a>(<a href="ident?i=ntohl">ntohl</a>(<a href="ident?i=th">th</a>-&gt;ack_seq));
<a name="L182" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L182">182</a>         nth-&gt;ack_seq    = <a href="ident?i=htonl">htonl</a>(<a href="ident?i=ntohl">ntohl</a>(<a href="ident?i=th">th</a>-&gt;<a href="ident?i=seq">seq</a>) + 1);
<a name="L183" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L183">183</a>         <a href="ident?i=tcp_flag_word">tcp_flag_word</a>(nth) = TCP_FLAG_ACK;
<a name="L184" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L184">184</a>         nth-&gt;doff       = tcp_hdr_size / 4;
<a name="L185" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L185">185</a>         nth-&gt;<a href="ident?i=window">window</a>     = <a href="ident?i=htons">htons</a>(<a href="ident?i=state">state</a>-&gt;seen[IP_CT_DIR_ORIGINAL].td_maxwin);
<a name="L186" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L186">186</a>         nth-&gt;<a href="ident?i=check">check</a>      = 0;
<a name="L187" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L187">187</a>         nth-&gt;urg_ptr    = 0;
<a name="L188" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L188">188</a> 
<a name="L189" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L189">189</a>         <a href="ident?i=synproxy_build_options">synproxy_build_options</a>(nth, <a href="ident?i=opts">opts</a>);
<a name="L190" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L190">190</a> 
<a name="L191" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L191">191</a>         <a href="ident?i=synproxy_send_tcp">synproxy_send_tcp</a>(<a href="ident?i=skb">skb</a>, nskb, <a href="ident?i=NULL">NULL</a>, 0, niph, nth, tcp_hdr_size);
<a name="L192" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L192">192</a> }
<a name="L193" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L193">193</a> 
<a name="L194" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L194">194</a> static void
<a name="L195" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L195">195</a> <a href="ident?i=synproxy_send_client_ack">synproxy_send_client_ack</a>(const struct <a href="ident?i=synproxy_net">synproxy_net</a> *snet,
<a name="L196" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L196">196</a>                          const struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, const struct <a href="ident?i=tcphdr">tcphdr</a> *<a href="ident?i=th">th</a>,
<a name="L197" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L197">197</a>                          const struct <a href="ident?i=synproxy_options">synproxy_options</a> *<a href="ident?i=opts">opts</a>)
<a name="L198" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L198">198</a> {
<a name="L199" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L199">199</a>         struct <a href="ident?i=sk_buff">sk_buff</a> *nskb;
<a name="L200" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L200">200</a>         struct <a href="ident?i=iphdr">iphdr</a> *iph, *niph;
<a name="L201" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L201">201</a>         struct <a href="ident?i=tcphdr">tcphdr</a> *nth;
<a name="L202" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L202">202</a>         unsigned int tcp_hdr_size;
<a name="L203" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L203">203</a> 
<a name="L204" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L204">204</a>         iph = <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>);
<a name="L205" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L205">205</a> 
<a name="L206" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L206">206</a>         tcp_hdr_size = sizeof(*nth) + <a href="ident?i=synproxy_options_size">synproxy_options_size</a>(<a href="ident?i=opts">opts</a>);
<a name="L207" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L207">207</a>         nskb = <a href="ident?i=alloc_skb">alloc_skb</a>(sizeof(*niph) + tcp_hdr_size + <a href="ident?i=MAX_TCP_HEADER">MAX_TCP_HEADER</a>,
<a name="L208" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L208">208</a>                          <a href="ident?i=GFP_ATOMIC">GFP_ATOMIC</a>);
<a name="L209" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L209">209</a>         if (nskb == <a href="ident?i=NULL">NULL</a>)
<a name="L210" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L210">210</a>                 return;
<a name="L211" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L211">211</a>         <a href="ident?i=skb_reserve">skb_reserve</a>(nskb, <a href="ident?i=MAX_TCP_HEADER">MAX_TCP_HEADER</a>);
<a name="L212" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L212">212</a> 
<a name="L213" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L213">213</a>         niph = <a href="ident?i=synproxy_build_ip">synproxy_build_ip</a>(nskb, iph-&gt;<a href="ident?i=saddr">saddr</a>, iph-&gt;<a href="ident?i=daddr">daddr</a>);
<a name="L214" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L214">214</a> 
<a name="L215" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L215">215</a>         <a href="ident?i=skb_reset_transport_header">skb_reset_transport_header</a>(nskb);
<a name="L216" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L216">216</a>         nth = (struct <a href="ident?i=tcphdr">tcphdr</a> *)<a href="ident?i=skb_put">skb_put</a>(nskb, tcp_hdr_size);
<a name="L217" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L217">217</a>         nth-&gt;source     = <a href="ident?i=th">th</a>-&gt;source;
<a name="L218" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L218">218</a>         nth-&gt;<a href="ident?i=dest">dest</a>       = <a href="ident?i=th">th</a>-&gt;<a href="ident?i=dest">dest</a>;
<a name="L219" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L219">219</a>         nth-&gt;<a href="ident?i=seq">seq</a>        = <a href="ident?i=htonl">htonl</a>(<a href="ident?i=ntohl">ntohl</a>(<a href="ident?i=th">th</a>-&gt;<a href="ident?i=seq">seq</a>) + 1);
<a name="L220" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L220">220</a>         nth-&gt;ack_seq    = <a href="ident?i=th">th</a>-&gt;ack_seq;
<a name="L221" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L221">221</a>         <a href="ident?i=tcp_flag_word">tcp_flag_word</a>(nth) = TCP_FLAG_ACK;
<a name="L222" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L222">222</a>         nth-&gt;doff       = tcp_hdr_size / 4;
<a name="L223" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L223">223</a>         nth-&gt;<a href="ident?i=window">window</a>     = <a href="ident?i=ntohs">ntohs</a>(<a href="ident?i=htons">htons</a>(<a href="ident?i=th">th</a>-&gt;<a href="ident?i=window">window</a>) &gt;&gt; <a href="ident?i=opts">opts</a>-&gt;wscale);
<a name="L224" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L224">224</a>         nth-&gt;<a href="ident?i=check">check</a>      = 0;
<a name="L225" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L225">225</a>         nth-&gt;urg_ptr    = 0;
<a name="L226" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L226">226</a> 
<a name="L227" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L227">227</a>         <a href="ident?i=synproxy_build_options">synproxy_build_options</a>(nth, <a href="ident?i=opts">opts</a>);
<a name="L228" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L228">228</a> 
<a name="L229" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L229">229</a>         <a href="ident?i=synproxy_send_tcp">synproxy_send_tcp</a>(<a href="ident?i=skb">skb</a>, nskb, <a href="ident?i=NULL">NULL</a>, 0, niph, nth, tcp_hdr_size);
<a name="L230" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L230">230</a> }
<a name="L231" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L231">231</a> 
<a name="L232" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L232">232</a> static <a href="ident?i=bool">bool</a>
<a name="L233" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L233">233</a> <a href="ident?i=synproxy_recv_client_ack">synproxy_recv_client_ack</a>(const struct <a href="ident?i=synproxy_net">synproxy_net</a> *snet,
<a name="L234" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L234">234</a>                          const struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, const struct <a href="ident?i=tcphdr">tcphdr</a> *<a href="ident?i=th">th</a>,
<a name="L235" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L235">235</a>                          struct <a href="ident?i=synproxy_options">synproxy_options</a> *<a href="ident?i=opts">opts</a>, <a href="ident?i=u32">u32</a> recv_seq)
<a name="L236" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L236">236</a> {
<a name="L237" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L237">237</a>         int mss;
<a name="L238" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L238">238</a> 
<a name="L239" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L239">239</a>         mss = <a href="ident?i=__cookie_v4_check">__cookie_v4_check</a>(<a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>), <a href="ident?i=th">th</a>, <a href="ident?i=ntohl">ntohl</a>(<a href="ident?i=th">th</a>-&gt;ack_seq) - 1);
<a name="L240" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L240">240</a>         if (mss == 0) {
<a name="L241" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L241">241</a>                 <a href="ident?i=this_cpu_inc">this_cpu_inc</a>(snet-&gt;<a href="ident?i=stats">stats</a>-&gt;cookie_invalid);
<a name="L242" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L242">242</a>                 return <a href="ident?i=false">false</a>;
<a name="L243" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L243">243</a>         }
<a name="L244" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L244">244</a> 
<a name="L245" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L245">245</a>         <a href="ident?i=this_cpu_inc">this_cpu_inc</a>(snet-&gt;<a href="ident?i=stats">stats</a>-&gt;cookie_valid);
<a name="L246" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L246">246</a>         <a href="ident?i=opts">opts</a>-&gt;mss = mss;
<a name="L247" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L247">247</a>         <a href="ident?i=opts">opts</a>-&gt;<a href="ident?i=options">options</a> |= <a href="ident?i=XT_SYNPROXY_OPT_MSS">XT_SYNPROXY_OPT_MSS</a>;
<a name="L248" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L248">248</a> 
<a name="L249" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L249">249</a>         if (<a href="ident?i=opts">opts</a>-&gt;<a href="ident?i=options">options</a> &amp; <a href="ident?i=XT_SYNPROXY_OPT_TIMESTAMP">XT_SYNPROXY_OPT_TIMESTAMP</a>)
<a name="L250" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L250">250</a>                 <a href="ident?i=synproxy_check_timestamp_cookie">synproxy_check_timestamp_cookie</a>(<a href="ident?i=opts">opts</a>);
<a name="L251" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L251">251</a> 
<a name="L252" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L252">252</a>         <a href="ident?i=synproxy_send_server_syn">synproxy_send_server_syn</a>(snet, <a href="ident?i=skb">skb</a>, <a href="ident?i=th">th</a>, <a href="ident?i=opts">opts</a>, recv_seq);
<a name="L253" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L253">253</a>         return <a href="ident?i=true">true</a>;
<a name="L254" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L254">254</a> }
<a name="L255" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L255">255</a> 
<a name="L256" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L256">256</a> static unsigned int
<a name="L257" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L257">257</a> <a href="ident?i=synproxy_tg4">synproxy_tg4</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, const struct <a href="ident?i=xt_action_param">xt_action_param</a> *<a href="ident?i=par">par</a>)
<a name="L258" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L258">258</a> {
<a name="L259" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L259">259</a>         const struct <a href="ident?i=xt_synproxy_info">xt_synproxy_info</a> *<a href="ident?i=info">info</a> = <a href="ident?i=par">par</a>-&gt;targinfo;
<a name="L260" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L260">260</a>         struct <a href="ident?i=synproxy_net">synproxy_net</a> *snet = <a href="ident?i=synproxy_pernet">synproxy_pernet</a>(<a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=par">par</a>-&gt;<a href="ident?i=in">in</a>));
<a name="L261" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L261">261</a>         struct <a href="ident?i=synproxy_options">synproxy_options</a> <a href="ident?i=opts">opts</a> = {};
<a name="L262" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L262">262</a>         struct <a href="ident?i=tcphdr">tcphdr</a> *<a href="ident?i=th">th</a>, _th;
<a name="L263" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L263">263</a> 
<a name="L264" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L264">264</a>         if (<a href="ident?i=nf_ip_checksum">nf_ip_checksum</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=par">par</a>-&gt;hooknum, <a href="ident?i=par">par</a>-&gt;thoff, <a href="ident?i=IPPROTO_TCP">IPPROTO_TCP</a>))
<a name="L265" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L265">265</a>                 return <a href="ident?i=NF_DROP">NF_DROP</a>;
<a name="L266" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L266">266</a> 
<a name="L267" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L267">267</a>         <a href="ident?i=th">th</a> = <a href="ident?i=skb_header_pointer">skb_header_pointer</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=par">par</a>-&gt;thoff, sizeof(_th), &amp;_th);
<a name="L268" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L268">268</a>         if (<a href="ident?i=th">th</a> == <a href="ident?i=NULL">NULL</a>)
<a name="L269" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L269">269</a>                 return <a href="ident?i=NF_DROP">NF_DROP</a>;
<a name="L270" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L270">270</a> 
<a name="L271" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L271">271</a>         if (!<a href="ident?i=synproxy_parse_options">synproxy_parse_options</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=par">par</a>-&gt;thoff, <a href="ident?i=th">th</a>, &amp;<a href="ident?i=opts">opts</a>))
<a name="L272" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L272">272</a>                 return <a href="ident?i=NF_DROP">NF_DROP</a>;
<a name="L273" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L273">273</a> 
<a name="L274" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L274">274</a>         if (<a href="ident?i=th">th</a>-&gt;syn &amp;&amp; !(<a href="ident?i=th">th</a>-&gt;ack || <a href="ident?i=th">th</a>-&gt;fin || <a href="ident?i=th">th</a>-&gt;rst)) {
<a name="L275" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L275">275</a>                 <b><i>/* Initial SYN from client */</i></b>
<a name="L276" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L276">276</a>                 <a href="ident?i=this_cpu_inc">this_cpu_inc</a>(snet-&gt;<a href="ident?i=stats">stats</a>-&gt;syn_received);
<a name="L277" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L277">277</a> 
<a name="L278" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L278">278</a>                 if (<a href="ident?i=th">th</a>-&gt;ece &amp;&amp; <a href="ident?i=th">th</a>-&gt;cwr)
<a name="L279" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L279">279</a>                         <a href="ident?i=opts">opts</a>.<a href="ident?i=options">options</a> |= <a href="ident?i=XT_SYNPROXY_OPT_ECN">XT_SYNPROXY_OPT_ECN</a>;
<a name="L280" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L280">280</a> 
<a name="L281" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L281">281</a>                 <a href="ident?i=opts">opts</a>.<a href="ident?i=options">options</a> &amp;= <a href="ident?i=info">info</a>-&gt;<a href="ident?i=options">options</a>;
<a name="L282" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L282">282</a>                 if (<a href="ident?i=opts">opts</a>.<a href="ident?i=options">options</a> &amp; <a href="ident?i=XT_SYNPROXY_OPT_TIMESTAMP">XT_SYNPROXY_OPT_TIMESTAMP</a>)
<a name="L283" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L283">283</a>                         <a href="ident?i=synproxy_init_timestamp_cookie">synproxy_init_timestamp_cookie</a>(<a href="ident?i=info">info</a>, &amp;<a href="ident?i=opts">opts</a>);
<a name="L284" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L284">284</a>                 else
<a name="L285" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L285">285</a>                         <a href="ident?i=opts">opts</a>.<a href="ident?i=options">options</a> &amp;= ~(<a href="ident?i=XT_SYNPROXY_OPT_WSCALE">XT_SYNPROXY_OPT_WSCALE</a> |
<a name="L286" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L286">286</a>                                           <a href="ident?i=XT_SYNPROXY_OPT_SACK_PERM">XT_SYNPROXY_OPT_SACK_PERM</a> |
<a name="L287" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L287">287</a>                                           <a href="ident?i=XT_SYNPROXY_OPT_ECN">XT_SYNPROXY_OPT_ECN</a>);
<a name="L288" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L288">288</a> 
<a name="L289" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L289">289</a>                 <a href="ident?i=synproxy_send_client_synack">synproxy_send_client_synack</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=th">th</a>, &amp;<a href="ident?i=opts">opts</a>);
<a name="L290" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L290">290</a>                 return <a href="ident?i=NF_DROP">NF_DROP</a>;
<a name="L291" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L291">291</a> 
<a name="L292" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L292">292</a>         } else if (<a href="ident?i=th">th</a>-&gt;ack &amp;&amp; !(<a href="ident?i=th">th</a>-&gt;fin || <a href="ident?i=th">th</a>-&gt;rst || <a href="ident?i=th">th</a>-&gt;syn)) {
<a name="L293" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L293">293</a>                 <b><i>/* ACK from client */</i></b>
<a name="L294" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L294">294</a>                 <a href="ident?i=synproxy_recv_client_ack">synproxy_recv_client_ack</a>(snet, <a href="ident?i=skb">skb</a>, <a href="ident?i=th">th</a>, &amp;<a href="ident?i=opts">opts</a>, <a href="ident?i=ntohl">ntohl</a>(<a href="ident?i=th">th</a>-&gt;<a href="ident?i=seq">seq</a>));
<a name="L295" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L295">295</a>                 return <a href="ident?i=NF_DROP">NF_DROP</a>;
<a name="L296" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L296">296</a>         }
<a name="L297" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L297">297</a> 
<a name="L298" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L298">298</a>         return <a href="ident?i=XT_CONTINUE">XT_CONTINUE</a>;
<a name="L299" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L299">299</a> }
<a name="L300" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L300">300</a> 
<a name="L301" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L301">301</a> static unsigned int <a href="ident?i=ipv4_synproxy_hook">ipv4_synproxy_hook</a>(const struct <a href="ident?i=nf_hook_ops">nf_hook_ops</a> *<a href="ident?i=ops">ops</a>,
<a name="L302" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L302">302</a>                                        struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
<a name="L303" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L303">303</a>                                        const struct <a href="ident?i=nf_hook_state">nf_hook_state</a> *nhs)
<a name="L304" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L304">304</a> {
<a name="L305" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L305">305</a>         struct <a href="ident?i=synproxy_net">synproxy_net</a> *snet = <a href="ident?i=synproxy_pernet">synproxy_pernet</a>(<a href="ident?i=dev_net">dev_net</a>(nhs-&gt;<a href="ident?i=in">in</a> ? : nhs-&gt;<a href="ident?i=out">out</a>));
<a name="L306" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L306">306</a>         enum <a href="ident?i=ip_conntrack_info">ip_conntrack_info</a> ctinfo;
<a name="L307" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L307">307</a>         struct <a href="ident?i=nf_conn">nf_conn</a> *ct;
<a name="L308" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L308">308</a>         struct <a href="ident?i=nf_conn_synproxy">nf_conn_synproxy</a> *synproxy;
<a name="L309" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L309">309</a>         struct <a href="ident?i=synproxy_options">synproxy_options</a> <a href="ident?i=opts">opts</a> = {};
<a name="L310" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L310">310</a>         const struct <a href="ident?i=ip_ct_tcp">ip_ct_tcp</a> *<a href="ident?i=state">state</a>;
<a name="L311" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L311">311</a>         struct <a href="ident?i=tcphdr">tcphdr</a> *<a href="ident?i=th">th</a>, _th;
<a name="L312" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L312">312</a>         unsigned int thoff;
<a name="L313" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L313">313</a> 
<a name="L314" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L314">314</a>         ct = <a href="ident?i=nf_ct_get">nf_ct_get</a>(<a href="ident?i=skb">skb</a>, &amp;ctinfo);
<a name="L315" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L315">315</a>         if (ct == <a href="ident?i=NULL">NULL</a>)
<a name="L316" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L316">316</a>                 return <a href="ident?i=NF_ACCEPT">NF_ACCEPT</a>;
<a name="L317" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L317">317</a> 
<a name="L318" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L318">318</a>         synproxy = <a href="ident?i=nfct_synproxy">nfct_synproxy</a>(ct);
<a name="L319" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L319">319</a>         if (synproxy == <a href="ident?i=NULL">NULL</a>)
<a name="L320" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L320">320</a>                 return <a href="ident?i=NF_ACCEPT">NF_ACCEPT</a>;
<a name="L321" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L321">321</a> 
<a name="L322" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L322">322</a>         if (<a href="ident?i=nf_is_loopback_packet">nf_is_loopback_packet</a>(<a href="ident?i=skb">skb</a>))
<a name="L323" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L323">323</a>                 return <a href="ident?i=NF_ACCEPT">NF_ACCEPT</a>;
<a name="L324" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L324">324</a> 
<a name="L325" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L325">325</a>         thoff = <a href="ident?i=ip_hdrlen">ip_hdrlen</a>(<a href="ident?i=skb">skb</a>);
<a name="L326" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L326">326</a>         <a href="ident?i=th">th</a> = <a href="ident?i=skb_header_pointer">skb_header_pointer</a>(<a href="ident?i=skb">skb</a>, thoff, sizeof(_th), &amp;_th);
<a name="L327" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L327">327</a>         if (<a href="ident?i=th">th</a> == <a href="ident?i=NULL">NULL</a>)
<a name="L328" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L328">328</a>                 return <a href="ident?i=NF_DROP">NF_DROP</a>;
<a name="L329" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L329">329</a> 
<a name="L330" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L330">330</a>         <a href="ident?i=state">state</a> = &amp;ct-&gt;<a href="ident?i=proto">proto</a>.tcp;
<a name="L331" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L331">331</a>         switch (<a href="ident?i=state">state</a>-&gt;<a href="ident?i=state">state</a>) {
<a name="L332" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L332">332</a>         case TCP_CONNTRACK_CLOSE:
<a name="L333" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L333">333</a>                 if (<a href="ident?i=th">th</a>-&gt;rst &amp;&amp; !<a href="ident?i=test_bit">test_bit</a>(IPS_SEEN_REPLY_BIT, &amp;ct-&gt;<a href="ident?i=status">status</a>)) {
<a name="L334" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L334">334</a>                         <a href="ident?i=nf_ct_seqadj_init">nf_ct_seqadj_init</a>(ct, ctinfo, synproxy-&gt;isn -
<a name="L335" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L335">335</a>                                                       <a href="ident?i=ntohl">ntohl</a>(<a href="ident?i=th">th</a>-&gt;<a href="ident?i=seq">seq</a>) + 1);
<a name="L336" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L336">336</a>                         break;
<a name="L337" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L337">337</a>                 }
<a name="L338" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L338">338</a> 
<a name="L339" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L339">339</a>                 if (!<a href="ident?i=th">th</a>-&gt;syn || <a href="ident?i=th">th</a>-&gt;ack ||
<a name="L340" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L340">340</a>                     <a href="ident?i=CTINFO2DIR">CTINFO2DIR</a>(ctinfo) != IP_CT_DIR_ORIGINAL)
<a name="L341" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L341">341</a>                         break;
<a name="L342" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L342">342</a> 
<a name="L343" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L343">343</a>                 <b><i>/* Reopened connection - reset the sequence number and timestamp</i></b>
<a name="L344" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L344">344</a> <b><i>                 * adjustments, they will get initialized once the connection is</i></b>
<a name="L345" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L345">345</a> <b><i>                 * reestablished.</i></b>
<a name="L346" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L346">346</a> <b><i>                 */</i></b>
<a name="L347" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L347">347</a>                 <a href="ident?i=nf_ct_seqadj_init">nf_ct_seqadj_init</a>(ct, ctinfo, 0);
<a name="L348" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L348">348</a>                 synproxy-&gt;tsoff = 0;
<a name="L349" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L349">349</a>                 <a href="ident?i=this_cpu_inc">this_cpu_inc</a>(snet-&gt;<a href="ident?i=stats">stats</a>-&gt;conn_reopened);
<a name="L350" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L350">350</a> 
<a name="L351" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L351">351</a>                 <b><i>/* fall through */</i></b>
<a name="L352" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L352">352</a>         case TCP_CONNTRACK_SYN_SENT:
<a name="L353" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L353">353</a>                 if (!<a href="ident?i=synproxy_parse_options">synproxy_parse_options</a>(<a href="ident?i=skb">skb</a>, thoff, <a href="ident?i=th">th</a>, &amp;<a href="ident?i=opts">opts</a>))
<a name="L354" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L354">354</a>                         return <a href="ident?i=NF_DROP">NF_DROP</a>;
<a name="L355" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L355">355</a> 
<a name="L356" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L356">356</a>                 if (!<a href="ident?i=th">th</a>-&gt;syn &amp;&amp; <a href="ident?i=th">th</a>-&gt;ack &amp;&amp;
<a name="L357" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L357">357</a>                     <a href="ident?i=CTINFO2DIR">CTINFO2DIR</a>(ctinfo) == IP_CT_DIR_ORIGINAL) {
<a name="L358" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L358">358</a>                         <b><i>/* Keep-Alives are sent with SEG.SEQ = SND.NXT-1,</i></b>
<a name="L359" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L359">359</a> <b><i>                         * therefore we need to add 1 to make the SYN sequence</i></b>
<a name="L360" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L360">360</a> <b><i>                         * number match the one of first SYN.</i></b>
<a name="L361" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L361">361</a> <b><i>                         */</i></b>
<a name="L362" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L362">362</a>                         if (<a href="ident?i=synproxy_recv_client_ack">synproxy_recv_client_ack</a>(snet, <a href="ident?i=skb">skb</a>, <a href="ident?i=th">th</a>, &amp;<a href="ident?i=opts">opts</a>,
<a name="L363" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L363">363</a>                                                      <a href="ident?i=ntohl">ntohl</a>(<a href="ident?i=th">th</a>-&gt;<a href="ident?i=seq">seq</a>) + 1))
<a name="L364" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L364">364</a>                                 <a href="ident?i=this_cpu_inc">this_cpu_inc</a>(snet-&gt;<a href="ident?i=stats">stats</a>-&gt;cookie_retrans);
<a name="L365" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L365">365</a> 
<a name="L366" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L366">366</a>                         return <a href="ident?i=NF_DROP">NF_DROP</a>;
<a name="L367" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L367">367</a>                 }
<a name="L368" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L368">368</a> 
<a name="L369" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L369">369</a>                 synproxy-&gt;isn = <a href="ident?i=ntohl">ntohl</a>(<a href="ident?i=th">th</a>-&gt;ack_seq);
<a name="L370" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L370">370</a>                 if (<a href="ident?i=opts">opts</a>.<a href="ident?i=options">options</a> &amp; <a href="ident?i=XT_SYNPROXY_OPT_TIMESTAMP">XT_SYNPROXY_OPT_TIMESTAMP</a>)
<a name="L371" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L371">371</a>                         synproxy-&gt;its = <a href="ident?i=opts">opts</a>.tsecr;
<a name="L372" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L372">372</a>                 break;
<a name="L373" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L373">373</a>         case TCP_CONNTRACK_SYN_RECV:
<a name="L374" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L374">374</a>                 if (!<a href="ident?i=th">th</a>-&gt;syn || !<a href="ident?i=th">th</a>-&gt;ack)
<a name="L375" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L375">375</a>                         break;
<a name="L376" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L376">376</a> 
<a name="L377" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L377">377</a>                 if (!<a href="ident?i=synproxy_parse_options">synproxy_parse_options</a>(<a href="ident?i=skb">skb</a>, thoff, <a href="ident?i=th">th</a>, &amp;<a href="ident?i=opts">opts</a>))
<a name="L378" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L378">378</a>                         return <a href="ident?i=NF_DROP">NF_DROP</a>;
<a name="L379" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L379">379</a> 
<a name="L380" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L380">380</a>                 if (<a href="ident?i=opts">opts</a>.<a href="ident?i=options">options</a> &amp; <a href="ident?i=XT_SYNPROXY_OPT_TIMESTAMP">XT_SYNPROXY_OPT_TIMESTAMP</a>)
<a name="L381" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L381">381</a>                         synproxy-&gt;tsoff = <a href="ident?i=opts">opts</a>.tsval - synproxy-&gt;its;
<a name="L382" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L382">382</a> 
<a name="L383" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L383">383</a>                 <a href="ident?i=opts">opts</a>.<a href="ident?i=options">options</a> &amp;= ~(<a href="ident?i=XT_SYNPROXY_OPT_MSS">XT_SYNPROXY_OPT_MSS</a> |
<a name="L384" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L384">384</a>                                   <a href="ident?i=XT_SYNPROXY_OPT_WSCALE">XT_SYNPROXY_OPT_WSCALE</a> |
<a name="L385" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L385">385</a>                                   <a href="ident?i=XT_SYNPROXY_OPT_SACK_PERM">XT_SYNPROXY_OPT_SACK_PERM</a>);
<a name="L386" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L386">386</a> 
<a name="L387" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L387">387</a>                 <a href="ident?i=swap">swap</a>(<a href="ident?i=opts">opts</a>.tsval, <a href="ident?i=opts">opts</a>.tsecr);
<a name="L388" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L388">388</a>                 <a href="ident?i=synproxy_send_server_ack">synproxy_send_server_ack</a>(snet, <a href="ident?i=state">state</a>, <a href="ident?i=skb">skb</a>, <a href="ident?i=th">th</a>, &amp;<a href="ident?i=opts">opts</a>);
<a name="L389" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L389">389</a> 
<a name="L390" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L390">390</a>                 <a href="ident?i=nf_ct_seqadj_init">nf_ct_seqadj_init</a>(ct, ctinfo, synproxy-&gt;isn - <a href="ident?i=ntohl">ntohl</a>(<a href="ident?i=th">th</a>-&gt;<a href="ident?i=seq">seq</a>));
<a name="L391" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L391">391</a> 
<a name="L392" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L392">392</a>                 <a href="ident?i=swap">swap</a>(<a href="ident?i=opts">opts</a>.tsval, <a href="ident?i=opts">opts</a>.tsecr);
<a name="L393" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L393">393</a>                 <a href="ident?i=synproxy_send_client_ack">synproxy_send_client_ack</a>(snet, <a href="ident?i=skb">skb</a>, <a href="ident?i=th">th</a>, &amp;<a href="ident?i=opts">opts</a>);
<a name="L394" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L394">394</a> 
<a name="L395" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L395">395</a>                 <a href="ident?i=consume_skb">consume_skb</a>(<a href="ident?i=skb">skb</a>);
<a name="L396" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L396">396</a>                 return <a href="ident?i=NF_STOLEN">NF_STOLEN</a>;
<a name="L397" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L397">397</a>         default:
<a name="L398" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L398">398</a>                 break;
<a name="L399" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L399">399</a>         }
<a name="L400" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L400">400</a> 
<a name="L401" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L401">401</a>         <a href="ident?i=synproxy_tstamp_adjust">synproxy_tstamp_adjust</a>(<a href="ident?i=skb">skb</a>, thoff, <a href="ident?i=th">th</a>, ct, ctinfo, synproxy);
<a name="L402" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L402">402</a>         return <a href="ident?i=NF_ACCEPT">NF_ACCEPT</a>;
<a name="L403" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L403">403</a> }
<a name="L404" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L404">404</a> 
<a name="L405" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L405">405</a> static int <a href="ident?i=synproxy_tg4_check">synproxy_tg4_check</a>(const struct <a href="ident?i=xt_tgchk_param">xt_tgchk_param</a> *<a href="ident?i=par">par</a>)
<a name="L406" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L406">406</a> {
<a name="L407" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L407">407</a>         const struct <a href="ident?i=ipt_entry">ipt_entry</a> *<a href="ident?i=e">e</a> = <a href="ident?i=par">par</a>-&gt;entryinfo;
<a name="L408" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L408">408</a> 
<a name="L409" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L409">409</a>         if (<a href="ident?i=e">e</a>-&gt;<a href="ident?i=ip">ip</a>.<a href="ident?i=proto">proto</a> != <a href="ident?i=IPPROTO_TCP">IPPROTO_TCP</a> ||
<a name="L410" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L410">410</a>             <a href="ident?i=e">e</a>-&gt;<a href="ident?i=ip">ip</a>.invflags &amp; <a href="ident?i=XT_INV_PROTO">XT_INV_PROTO</a>)
<a name="L411" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L411">411</a>                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L412" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L412">412</a> 
<a name="L413" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L413">413</a>         return <a href="ident?i=nf_ct_l3proto_try_module_get">nf_ct_l3proto_try_module_get</a>(<a href="ident?i=par">par</a>-&gt;<a href="ident?i=family">family</a>);
<a name="L414" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L414">414</a> }
<a name="L415" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L415">415</a> 
<a name="L416" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L416">416</a> static void <a href="ident?i=synproxy_tg4_destroy">synproxy_tg4_destroy</a>(const struct <a href="ident?i=xt_tgdtor_param">xt_tgdtor_param</a> *<a href="ident?i=par">par</a>)
<a name="L417" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L417">417</a> {
<a name="L418" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L418">418</a>         <a href="ident?i=nf_ct_l3proto_module_put">nf_ct_l3proto_module_put</a>(<a href="ident?i=par">par</a>-&gt;<a href="ident?i=family">family</a>);
<a name="L419" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L419">419</a> }
<a name="L420" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L420">420</a> 
<a name="L421" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L421">421</a> static struct <a href="ident?i=xt_target">xt_target</a> synproxy_tg4_reg <a href="ident?i=__read_mostly">__read_mostly</a> = {
<a name="L422" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L422">422</a>         .<a href="ident?i=name">name</a>           = <i>"SYNPROXY"</i>,
<a name="L423" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L423">423</a>         .<a href="ident?i=family">family</a>         = NFPROTO_IPV4,
<a name="L424" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L424">424</a>         .<a href="ident?i=hooks">hooks</a>          = (1 &lt;&lt; NF_INET_LOCAL_IN) | (1 &lt;&lt; NF_INET_FORWARD),
<a name="L425" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L425">425</a>         .<a href="ident?i=target">target</a>         = <a href="ident?i=synproxy_tg4">synproxy_tg4</a>,
<a name="L426" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L426">426</a>         .targetsize     = sizeof(struct <a href="ident?i=xt_synproxy_info">xt_synproxy_info</a>),
<a name="L427" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L427">427</a>         .<a href="ident?i=checkentry">checkentry</a>     = <a href="ident?i=synproxy_tg4_check">synproxy_tg4_check</a>,
<a name="L428" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L428">428</a>         .<a href="ident?i=destroy">destroy</a>        = <a href="ident?i=synproxy_tg4_destroy">synproxy_tg4_destroy</a>,
<a name="L429" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L429">429</a>         .<a href="ident?i=me">me</a>             = <a href="ident?i=THIS_MODULE">THIS_MODULE</a>,
<a name="L430" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L430">430</a> };
<a name="L431" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L431">431</a> 
<a name="L432" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L432">432</a> static struct <a href="ident?i=nf_hook_ops">nf_hook_ops</a> ipv4_synproxy_ops[] <a href="ident?i=__read_mostly">__read_mostly</a> = {
<a name="L433" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L433">433</a>         {
<a name="L434" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L434">434</a>                 .hook           = <a href="ident?i=ipv4_synproxy_hook">ipv4_synproxy_hook</a>,
<a name="L435" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L435">435</a>                 .owner          = <a href="ident?i=THIS_MODULE">THIS_MODULE</a>,
<a name="L436" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L436">436</a>                 .<a href="ident?i=pf">pf</a>             = NFPROTO_IPV4,
<a name="L437" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L437">437</a>                 .hooknum        = NF_INET_LOCAL_IN,
<a name="L438" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L438">438</a>                 .<a href="ident?i=priority">priority</a>       = NF_IP_PRI_CONNTRACK_CONFIRM - 1,
<a name="L439" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L439">439</a>         },
<a name="L440" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L440">440</a>         {
<a name="L441" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L441">441</a>                 .hook           = <a href="ident?i=ipv4_synproxy_hook">ipv4_synproxy_hook</a>,
<a name="L442" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L442">442</a>                 .owner          = <a href="ident?i=THIS_MODULE">THIS_MODULE</a>,
<a name="L443" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L443">443</a>                 .<a href="ident?i=pf">pf</a>             = NFPROTO_IPV4,
<a name="L444" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L444">444</a>                 .hooknum        = NF_INET_POST_ROUTING,
<a name="L445" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L445">445</a>                 .<a href="ident?i=priority">priority</a>       = NF_IP_PRI_CONNTRACK_CONFIRM - 1,
<a name="L446" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L446">446</a>         },
<a name="L447" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L447">447</a> };
<a name="L448" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L448">448</a> 
<a name="L449" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L449">449</a> static int <a href="ident?i=__init">__init</a> <a href="ident?i=synproxy_tg4_init">synproxy_tg4_init</a>(void)
<a name="L450" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L450">450</a> {
<a name="L451" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L451">451</a>         int <a href="ident?i=err">err</a>;
<a name="L452" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L452">452</a> 
<a name="L453" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L453">453</a>         <a href="ident?i=err">err</a> = <a href="ident?i=nf_register_hooks">nf_register_hooks</a>(ipv4_synproxy_ops,
<a name="L454" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L454">454</a>                                 <a href="ident?i=ARRAY_SIZE">ARRAY_SIZE</a>(ipv4_synproxy_ops));
<a name="L455" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L455">455</a>         if (<a href="ident?i=err">err</a> &lt; 0)
<a name="L456" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L456">456</a>                 goto err1;
<a name="L457" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L457">457</a> 
<a name="L458" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L458">458</a>         <a href="ident?i=err">err</a> = <a href="ident?i=xt_register_target">xt_register_target</a>(&amp;synproxy_tg4_reg);
<a name="L459" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L459">459</a>         if (<a href="ident?i=err">err</a> &lt; 0)
<a name="L460" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L460">460</a>                 goto err2;
<a name="L461" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L461">461</a> 
<a name="L462" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L462">462</a>         return 0;
<a name="L463" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L463">463</a> 
<a name="L464" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L464">464</a> err2:
<a name="L465" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L465">465</a>         <a href="ident?i=nf_unregister_hooks">nf_unregister_hooks</a>(ipv4_synproxy_ops, <a href="ident?i=ARRAY_SIZE">ARRAY_SIZE</a>(ipv4_synproxy_ops));
<a name="L466" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L466">466</a> err1:
<a name="L467" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L467">467</a>         return <a href="ident?i=err">err</a>;
<a name="L468" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L468">468</a> }
<a name="L469" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L469">469</a> 
<a name="L470" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L470">470</a> static void <a href="ident?i=__exit">__exit</a> <a href="ident?i=synproxy_tg4_exit">synproxy_tg4_exit</a>(void)
<a name="L471" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L471">471</a> {
<a name="L472" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L472">472</a>         <a href="ident?i=xt_unregister_target">xt_unregister_target</a>(&amp;synproxy_tg4_reg);
<a name="L473" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L473">473</a>         <a href="ident?i=nf_unregister_hooks">nf_unregister_hooks</a>(ipv4_synproxy_ops, <a href="ident?i=ARRAY_SIZE">ARRAY_SIZE</a>(ipv4_synproxy_ops));
<a name="L474" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L474">474</a> }
<a name="L475" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L475">475</a> 
<a name="L476" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L476">476</a> <a href="ident?i=module_init">module_init</a>(<a href="ident?i=synproxy_tg4_init">synproxy_tg4_init</a>);
<a name="L477" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L477">477</a> <a href="ident?i=module_exit">module_exit</a>(<a href="ident?i=synproxy_tg4_exit">synproxy_tg4_exit</a>);
<a name="L478" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L478">478</a> 
<a name="L479" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L479">479</a> <a href="ident?i=MODULE_LICENSE">MODULE_LICENSE</a>(<i>"GPL"</i>);
<a name="L480" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L480">480</a> <a href="ident?i=MODULE_AUTHOR">MODULE_AUTHOR</a>(<i>"Patrick McHardy &lt;kaber@trash.net&gt;"</i>);
<a name="L481" href="source/net/ipv4/netfilter/ipt_SYNPROXY.c#L481">481</a> </pre></div><p>
This page was automatically generated by <a href="http://lxr.linux.no">LXR</a> 0.3.1 (<a href="http://free-electrons.com/pub/source/lxr-0.3.1-fe1.tar.bz2">source</a>).
&nbsp;&bull;&nbsp;
Linux is a registered trademark of Linus Torvalds
&nbsp;&bull;&nbsp;
<a href="http://free-electrons.com/company/contact/">Contact us</a>
</p>

<div id="menu">
<ul>
   <li><a href="http://free-electrons.com/">Home</a></li>
   <li><a href="http://free-electrons.com/development/" title="Development">Development</a></li>
   <li><a href="http://free-electrons.com/services/" title="Services">Services</a></li>
   <li><a href="http://free-electrons.com/training/" title="Training">Training</a></li>
   <li><a href="http://free-electrons.com/docs/" title="Docs">Docs</a></li>
   <li><a href="http://free-electrons.com/community/" title="Community">Community</a></li>
   <li><a href="http://free-electrons.com/company/" title="Company">Company</a></li>
   <li><a href="http://free-electrons.com/blog/" title="Blog">Blog</a></li>
</ul>
</div>

</div>
</div>
</body>
</html>
