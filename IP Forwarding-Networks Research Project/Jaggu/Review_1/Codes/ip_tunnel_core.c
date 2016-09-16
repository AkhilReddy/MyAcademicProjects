<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title>Linux/net/ipv4/ip_tunnel_core.c - Linux Cross Reference - Free Electrons</title>
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
		 &nbsp;&bull;&nbsp;<b><i>source navigation</i></b> &nbsp;&bull;&nbsp;<a href="diff/net/ipv4/ip_tunnel_core.c">diff markup</a> &nbsp;&bull;&nbsp;<a href="ident">identifier search</a> &nbsp;&bull;&nbsp;<a href="search">freetext search</a> &nbsp;&bull;&nbsp;
		</p>
	</div>
</div>

<div id="topbar">
  
  <p>Version: &nbsp;<a href="source/net/ipv4/ip_tunnel_core.c?v=2.0.40">2.0.40</a>&nbsp;<a href="source/net/ipv4/ip_tunnel_core.c?v=2.2.26">2.2.26</a>&nbsp;<a href="source/net/ipv4/ip_tunnel_core.c?v=2.4.37">2.4.37</a>&nbsp;<a href="source/net/ipv4/ip_tunnel_core.c?v=3.5">3.5</a>&nbsp;<a href="source/net/ipv4/ip_tunnel_core.c?v=3.6">3.6</a>&nbsp;<a href="source/net/ipv4/ip_tunnel_core.c?v=3.7">3.7</a>&nbsp;<a href="source/net/ipv4/ip_tunnel_core.c?v=3.8">3.8</a>&nbsp;<a href="source/net/ipv4/ip_tunnel_core.c?v=3.9">3.9</a>&nbsp;<a href="source/net/ipv4/ip_tunnel_core.c?v=3.10">3.10</a>&nbsp;<a href="source/net/ipv4/ip_tunnel_core.c?v=3.11">3.11</a>&nbsp;<a href="source/net/ipv4/ip_tunnel_core.c?v=3.12">3.12</a>&nbsp;<a href="source/net/ipv4/ip_tunnel_core.c?v=3.13">3.13</a>&nbsp;<a href="source/net/ipv4/ip_tunnel_core.c?v=3.14">3.14</a>&nbsp;<a href="source/net/ipv4/ip_tunnel_core.c?v=3.15">3.15</a>&nbsp;<a href="source/net/ipv4/ip_tunnel_core.c?v=3.16">3.16</a>&nbsp;<a href="source/net/ipv4/ip_tunnel_core.c?v=3.17">3.17</a>&nbsp;<a href="source/net/ipv4/ip_tunnel_core.c?v=3.18">3.18</a>&nbsp;<a href="source/net/ipv4/ip_tunnel_core.c?v=3.19">3.19</a>&nbsp;<a href="source/net/ipv4/ip_tunnel_core.c?v=4.0">4.0</a>&nbsp;<b><i>4.1</i></b></p>
  
</div>

<h1><a href="source/">Linux</a>/<a href="source/net/">net</a>/<a href="source/net/ipv4/">ipv4</a>/<a href="source/net/ipv4/ip_tunnel_core.c">ip_tunnel_core.c</a></h1>
<div id="lxrcode"><pre>  <a name="L1" href="source/net/ipv4/ip_tunnel_core.c#L1">1</a> <b><i>/*</i></b>
  <a name="L2" href="source/net/ipv4/ip_tunnel_core.c#L2">2</a> <b><i> * Copyright (c) 2013 Nicira, Inc.</i></b>
  <a name="L3" href="source/net/ipv4/ip_tunnel_core.c#L3">3</a> <b><i> *</i></b>
  <a name="L4" href="source/net/ipv4/ip_tunnel_core.c#L4">4</a> <b><i> * This program is free software; you can redistribute it and/or</i></b>
  <a name="L5" href="source/net/ipv4/ip_tunnel_core.c#L5">5</a> <b><i> * modify it under the terms of version 2 of the GNU General Public</i></b>
  <a name="L6" href="source/net/ipv4/ip_tunnel_core.c#L6">6</a> <b><i> * License as published by the Free Software Foundation.</i></b>
  <a name="L7" href="source/net/ipv4/ip_tunnel_core.c#L7">7</a> <b><i> *</i></b>
  <a name="L8" href="source/net/ipv4/ip_tunnel_core.c#L8">8</a> <b><i> * This program is distributed in the hope that it will be useful, but</i></b>
  <a name="L9" href="source/net/ipv4/ip_tunnel_core.c#L9">9</a> <b><i> * WITHOUT ANY WARRANTY; without even the implied warranty of</i></b>
 <a name="L10" href="source/net/ipv4/ip_tunnel_core.c#L10">10</a> <b><i> * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU</i></b>
 <a name="L11" href="source/net/ipv4/ip_tunnel_core.c#L11">11</a> <b><i> * General Public License for more details.</i></b>
 <a name="L12" href="source/net/ipv4/ip_tunnel_core.c#L12">12</a> <b><i> *</i></b>
 <a name="L13" href="source/net/ipv4/ip_tunnel_core.c#L13">13</a> <b><i> * You should have received a copy of the GNU General Public License</i></b>
 <a name="L14" href="source/net/ipv4/ip_tunnel_core.c#L14">14</a> <b><i> * along with this program; if not, write to the Free Software</i></b>
 <a name="L15" href="source/net/ipv4/ip_tunnel_core.c#L15">15</a> <b><i> * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA</i></b>
 <a name="L16" href="source/net/ipv4/ip_tunnel_core.c#L16">16</a> <b><i> * 02110-1301, USA</i></b>
 <a name="L17" href="source/net/ipv4/ip_tunnel_core.c#L17">17</a> <b><i> */</i></b>
 <a name="L18" href="source/net/ipv4/ip_tunnel_core.c#L18">18</a> 
 <a name="L19" href="source/net/ipv4/ip_tunnel_core.c#L19">19</a> #define <a href="ident?i=pr_fmt">pr_fmt</a>(<a href="ident?i=fmt">fmt</a>) KBUILD_MODNAME <i>": "</i> <a href="ident?i=fmt">fmt</a>
 <a name="L20" href="source/net/ipv4/ip_tunnel_core.c#L20">20</a> 
 <a name="L21" href="source/net/ipv4/ip_tunnel_core.c#L21">21</a> #include &lt;linux/types.h&gt;
 <a name="L22" href="source/net/ipv4/ip_tunnel_core.c#L22">22</a> #include &lt;linux/kernel.h&gt;
 <a name="L23" href="source/net/ipv4/ip_tunnel_core.c#L23">23</a> #include &lt;linux/skbuff.h&gt;
 <a name="L24" href="source/net/ipv4/ip_tunnel_core.c#L24">24</a> #include &lt;linux/netdevice.h&gt;
 <a name="L25" href="source/net/ipv4/ip_tunnel_core.c#L25">25</a> #include &lt;linux/in.h&gt;
 <a name="L26" href="source/net/ipv4/ip_tunnel_core.c#L26">26</a> #include &lt;linux/if_arp.h&gt;
 <a name="L27" href="source/net/ipv4/ip_tunnel_core.c#L27">27</a> #include &lt;linux/mroute.h&gt;
 <a name="L28" href="source/net/ipv4/ip_tunnel_core.c#L28">28</a> #include &lt;linux/init.h&gt;
 <a name="L29" href="source/net/ipv4/ip_tunnel_core.c#L29">29</a> #include &lt;linux/in6.h&gt;
 <a name="L30" href="source/net/ipv4/ip_tunnel_core.c#L30">30</a> #include &lt;linux/inetdevice.h&gt;
 <a name="L31" href="source/net/ipv4/ip_tunnel_core.c#L31">31</a> #include &lt;linux/netfilter_ipv4.h&gt;
 <a name="L32" href="source/net/ipv4/ip_tunnel_core.c#L32">32</a> #include &lt;linux/etherdevice.h&gt;
 <a name="L33" href="source/net/ipv4/ip_tunnel_core.c#L33">33</a> #include &lt;linux/if_ether.h&gt;
 <a name="L34" href="source/net/ipv4/ip_tunnel_core.c#L34">34</a> #include &lt;linux/if_vlan.h&gt;
 <a name="L35" href="source/net/ipv4/ip_tunnel_core.c#L35">35</a> 
 <a name="L36" href="source/net/ipv4/ip_tunnel_core.c#L36">36</a> #include &lt;net/ip.h&gt;
 <a name="L37" href="source/net/ipv4/ip_tunnel_core.c#L37">37</a> #include &lt;net/icmp.h&gt;
 <a name="L38" href="source/net/ipv4/ip_tunnel_core.c#L38">38</a> #include &lt;net/protocol.h&gt;
 <a name="L39" href="source/net/ipv4/ip_tunnel_core.c#L39">39</a> #include &lt;net/ip_tunnels.h&gt;
 <a name="L40" href="source/net/ipv4/ip_tunnel_core.c#L40">40</a> #include &lt;net/arp.h&gt;
 <a name="L41" href="source/net/ipv4/ip_tunnel_core.c#L41">41</a> #include &lt;net/checksum.h&gt;
 <a name="L42" href="source/net/ipv4/ip_tunnel_core.c#L42">42</a> #include &lt;net/dsfield.h&gt;
 <a name="L43" href="source/net/ipv4/ip_tunnel_core.c#L43">43</a> #include &lt;net/inet_ecn.h&gt;
 <a name="L44" href="source/net/ipv4/ip_tunnel_core.c#L44">44</a> #include &lt;net/xfrm.h&gt;
 <a name="L45" href="source/net/ipv4/ip_tunnel_core.c#L45">45</a> #include &lt;net/net_namespace.h&gt;
 <a name="L46" href="source/net/ipv4/ip_tunnel_core.c#L46">46</a> #include &lt;net/netns/generic.h&gt;
 <a name="L47" href="source/net/ipv4/ip_tunnel_core.c#L47">47</a> #include &lt;net/rtnetlink.h&gt;
 <a name="L48" href="source/net/ipv4/ip_tunnel_core.c#L48">48</a> 
 <a name="L49" href="source/net/ipv4/ip_tunnel_core.c#L49">49</a> int <a href="ident?i=iptunnel_xmit">iptunnel_xmit</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=rtable">rtable</a> *<a href="ident?i=rt">rt</a>, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
 <a name="L50" href="source/net/ipv4/ip_tunnel_core.c#L50">50</a>                   <a href="ident?i=__be32">__be32</a> <a href="ident?i=src">src</a>, <a href="ident?i=__be32">__be32</a> <a href="ident?i=dst">dst</a>, <a href="ident?i=__u8">__u8</a> <a href="ident?i=proto">proto</a>,
 <a name="L51" href="source/net/ipv4/ip_tunnel_core.c#L51">51</a>                   <a href="ident?i=__u8">__u8</a> tos, <a href="ident?i=__u8">__u8</a> <a href="ident?i=ttl">ttl</a>, <a href="ident?i=__be16">__be16</a> <a href="ident?i=df">df</a>, <a href="ident?i=bool">bool</a> xnet)
 <a name="L52" href="source/net/ipv4/ip_tunnel_core.c#L52">52</a> {
 <a name="L53" href="source/net/ipv4/ip_tunnel_core.c#L53">53</a>         int pkt_len = <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a>;
 <a name="L54" href="source/net/ipv4/ip_tunnel_core.c#L54">54</a>         struct <a href="ident?i=iphdr">iphdr</a> *iph;
 <a name="L55" href="source/net/ipv4/ip_tunnel_core.c#L55">55</a>         int <a href="ident?i=err">err</a>;
 <a name="L56" href="source/net/ipv4/ip_tunnel_core.c#L56">56</a> 
 <a name="L57" href="source/net/ipv4/ip_tunnel_core.c#L57">57</a>         <a href="ident?i=skb_scrub_packet">skb_scrub_packet</a>(<a href="ident?i=skb">skb</a>, xnet);
 <a name="L58" href="source/net/ipv4/ip_tunnel_core.c#L58">58</a> 
 <a name="L59" href="source/net/ipv4/ip_tunnel_core.c#L59">59</a>         <a href="ident?i=skb_clear_hash">skb_clear_hash</a>(<a href="ident?i=skb">skb</a>);
 <a name="L60" href="source/net/ipv4/ip_tunnel_core.c#L60">60</a>         <a href="ident?i=skb_dst_set">skb_dst_set</a>(<a href="ident?i=skb">skb</a>, &amp;<a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>);
 <a name="L61" href="source/net/ipv4/ip_tunnel_core.c#L61">61</a>         <a href="ident?i=memset">memset</a>(<a href="ident?i=IPCB">IPCB</a>(<a href="ident?i=skb">skb</a>), 0, sizeof(*<a href="ident?i=IPCB">IPCB</a>(<a href="ident?i=skb">skb</a>)));
 <a name="L62" href="source/net/ipv4/ip_tunnel_core.c#L62">62</a> 
 <a name="L63" href="source/net/ipv4/ip_tunnel_core.c#L63">63</a>         <b><i>/* Push down and install the IP header. */</i></b>
 <a name="L64" href="source/net/ipv4/ip_tunnel_core.c#L64">64</a>         <a href="ident?i=skb_push">skb_push</a>(<a href="ident?i=skb">skb</a>, sizeof(struct <a href="ident?i=iphdr">iphdr</a>));
 <a name="L65" href="source/net/ipv4/ip_tunnel_core.c#L65">65</a>         <a href="ident?i=skb_reset_network_header">skb_reset_network_header</a>(<a href="ident?i=skb">skb</a>);
 <a name="L66" href="source/net/ipv4/ip_tunnel_core.c#L66">66</a> 
 <a name="L67" href="source/net/ipv4/ip_tunnel_core.c#L67">67</a>         iph = <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>);
 <a name="L68" href="source/net/ipv4/ip_tunnel_core.c#L68">68</a> 
 <a name="L69" href="source/net/ipv4/ip_tunnel_core.c#L69">69</a>         iph-&gt;<a href="ident?i=version">version</a>    =       4;
 <a name="L70" href="source/net/ipv4/ip_tunnel_core.c#L70">70</a>         iph-&gt;ihl        =       sizeof(struct <a href="ident?i=iphdr">iphdr</a>) &gt;&gt; 2;
 <a name="L71" href="source/net/ipv4/ip_tunnel_core.c#L71">71</a>         iph-&gt;frag_off   =       <a href="ident?i=df">df</a>;
 <a name="L72" href="source/net/ipv4/ip_tunnel_core.c#L72">72</a>         iph-&gt;<a href="ident?i=protocol">protocol</a>   =       <a href="ident?i=proto">proto</a>;
 <a name="L73" href="source/net/ipv4/ip_tunnel_core.c#L73">73</a>         iph-&gt;tos        =       tos;
 <a name="L74" href="source/net/ipv4/ip_tunnel_core.c#L74">74</a>         iph-&gt;<a href="ident?i=daddr">daddr</a>      =       <a href="ident?i=dst">dst</a>;
 <a name="L75" href="source/net/ipv4/ip_tunnel_core.c#L75">75</a>         iph-&gt;<a href="ident?i=saddr">saddr</a>      =       <a href="ident?i=src">src</a>;
 <a name="L76" href="source/net/ipv4/ip_tunnel_core.c#L76">76</a>         iph-&gt;<a href="ident?i=ttl">ttl</a>        =       <a href="ident?i=ttl">ttl</a>;
 <a name="L77" href="source/net/ipv4/ip_tunnel_core.c#L77">77</a>         <a href="ident?i=__ip_select_ident">__ip_select_ident</a>(<a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>.<a href="ident?i=dev">dev</a>), iph,
 <a name="L78" href="source/net/ipv4/ip_tunnel_core.c#L78">78</a>                           <a href="ident?i=skb_shinfo">skb_shinfo</a>(<a href="ident?i=skb">skb</a>)-&gt;gso_segs ?: 1);
 <a name="L79" href="source/net/ipv4/ip_tunnel_core.c#L79">79</a> 
 <a name="L80" href="source/net/ipv4/ip_tunnel_core.c#L80">80</a>         <a href="ident?i=err">err</a> = <a href="ident?i=ip_local_out_sk">ip_local_out_sk</a>(sk, <a href="ident?i=skb">skb</a>);
 <a name="L81" href="source/net/ipv4/ip_tunnel_core.c#L81">81</a>         if (<a href="ident?i=unlikely">unlikely</a>(<a href="ident?i=net_xmit_eval">net_xmit_eval</a>(<a href="ident?i=err">err</a>)))
 <a name="L82" href="source/net/ipv4/ip_tunnel_core.c#L82">82</a>                 pkt_len = 0;
 <a name="L83" href="source/net/ipv4/ip_tunnel_core.c#L83">83</a>         return pkt_len;
 <a name="L84" href="source/net/ipv4/ip_tunnel_core.c#L84">84</a> }
 <a name="L85" href="source/net/ipv4/ip_tunnel_core.c#L85">85</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=iptunnel_xmit">iptunnel_xmit</a>);
 <a name="L86" href="source/net/ipv4/ip_tunnel_core.c#L86">86</a> 
 <a name="L87" href="source/net/ipv4/ip_tunnel_core.c#L87">87</a> int <a href="ident?i=iptunnel_pull_header">iptunnel_pull_header</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, int hdr_len, <a href="ident?i=__be16">__be16</a> inner_proto)
 <a name="L88" href="source/net/ipv4/ip_tunnel_core.c#L88">88</a> {
 <a name="L89" href="source/net/ipv4/ip_tunnel_core.c#L89">89</a>         if (<a href="ident?i=unlikely">unlikely</a>(!<a href="ident?i=pskb_may_pull">pskb_may_pull</a>(<a href="ident?i=skb">skb</a>, hdr_len)))
 <a name="L90" href="source/net/ipv4/ip_tunnel_core.c#L90">90</a>                 return -<a href="ident?i=ENOMEM">ENOMEM</a>;
 <a name="L91" href="source/net/ipv4/ip_tunnel_core.c#L91">91</a> 
 <a name="L92" href="source/net/ipv4/ip_tunnel_core.c#L92">92</a>         <a href="ident?i=skb_pull_rcsum">skb_pull_rcsum</a>(<a href="ident?i=skb">skb</a>, hdr_len);
 <a name="L93" href="source/net/ipv4/ip_tunnel_core.c#L93">93</a> 
 <a name="L94" href="source/net/ipv4/ip_tunnel_core.c#L94">94</a>         if (inner_proto == <a href="ident?i=htons">htons</a>(<a href="ident?i=ETH_P_TEB">ETH_P_TEB</a>)) {
 <a name="L95" href="source/net/ipv4/ip_tunnel_core.c#L95">95</a>                 struct <a href="ident?i=ethhdr">ethhdr</a> *eh;
 <a name="L96" href="source/net/ipv4/ip_tunnel_core.c#L96">96</a> 
 <a name="L97" href="source/net/ipv4/ip_tunnel_core.c#L97">97</a>                 if (<a href="ident?i=unlikely">unlikely</a>(!<a href="ident?i=pskb_may_pull">pskb_may_pull</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=ETH_HLEN">ETH_HLEN</a>)))
 <a name="L98" href="source/net/ipv4/ip_tunnel_core.c#L98">98</a>                         return -<a href="ident?i=ENOMEM">ENOMEM</a>;
 <a name="L99" href="source/net/ipv4/ip_tunnel_core.c#L99">99</a> 
<a name="L100" href="source/net/ipv4/ip_tunnel_core.c#L100">100</a>                 eh = (struct <a href="ident?i=ethhdr">ethhdr</a> *)<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=data">data</a>;
<a name="L101" href="source/net/ipv4/ip_tunnel_core.c#L101">101</a>                 if (<a href="ident?i=likely">likely</a>(<a href="ident?i=ntohs">ntohs</a>(eh-&gt;h_proto) &gt;= <a href="ident?i=ETH_P_802_3_MIN">ETH_P_802_3_MIN</a>))
<a name="L102" href="source/net/ipv4/ip_tunnel_core.c#L102">102</a>                         <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=protocol">protocol</a> = eh-&gt;h_proto;
<a name="L103" href="source/net/ipv4/ip_tunnel_core.c#L103">103</a>                 else
<a name="L104" href="source/net/ipv4/ip_tunnel_core.c#L104">104</a>                         <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=protocol">protocol</a> = <a href="ident?i=htons">htons</a>(<a href="ident?i=ETH_P_802_2">ETH_P_802_2</a>);
<a name="L105" href="source/net/ipv4/ip_tunnel_core.c#L105">105</a> 
<a name="L106" href="source/net/ipv4/ip_tunnel_core.c#L106">106</a>         } else {
<a name="L107" href="source/net/ipv4/ip_tunnel_core.c#L107">107</a>                 <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=protocol">protocol</a> = inner_proto;
<a name="L108" href="source/net/ipv4/ip_tunnel_core.c#L108">108</a>         }
<a name="L109" href="source/net/ipv4/ip_tunnel_core.c#L109">109</a> 
<a name="L110" href="source/net/ipv4/ip_tunnel_core.c#L110">110</a>         <a href="ident?i=nf_reset">nf_reset</a>(<a href="ident?i=skb">skb</a>);
<a name="L111" href="source/net/ipv4/ip_tunnel_core.c#L111">111</a>         <a href="ident?i=secpath_reset">secpath_reset</a>(<a href="ident?i=skb">skb</a>);
<a name="L112" href="source/net/ipv4/ip_tunnel_core.c#L112">112</a>         <a href="ident?i=skb_clear_hash_if_not_l4">skb_clear_hash_if_not_l4</a>(<a href="ident?i=skb">skb</a>);
<a name="L113" href="source/net/ipv4/ip_tunnel_core.c#L113">113</a>         <a href="ident?i=skb_dst_drop">skb_dst_drop</a>(<a href="ident?i=skb">skb</a>);
<a name="L114" href="source/net/ipv4/ip_tunnel_core.c#L114">114</a>         <a href="ident?i=skb">skb</a>-&gt;vlan_tci = 0;
<a name="L115" href="source/net/ipv4/ip_tunnel_core.c#L115">115</a>         <a href="ident?i=skb_set_queue_mapping">skb_set_queue_mapping</a>(<a href="ident?i=skb">skb</a>, 0);
<a name="L116" href="source/net/ipv4/ip_tunnel_core.c#L116">116</a>         <a href="ident?i=skb">skb</a>-&gt;pkt_type = <a href="ident?i=PACKET_HOST">PACKET_HOST</a>;
<a name="L117" href="source/net/ipv4/ip_tunnel_core.c#L117">117</a>         return 0;
<a name="L118" href="source/net/ipv4/ip_tunnel_core.c#L118">118</a> }
<a name="L119" href="source/net/ipv4/ip_tunnel_core.c#L119">119</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=iptunnel_pull_header">iptunnel_pull_header</a>);
<a name="L120" href="source/net/ipv4/ip_tunnel_core.c#L120">120</a> 
<a name="L121" href="source/net/ipv4/ip_tunnel_core.c#L121">121</a> struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=iptunnel_handle_offloads">iptunnel_handle_offloads</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
<a name="L122" href="source/net/ipv4/ip_tunnel_core.c#L122">122</a>                                          <a href="ident?i=bool">bool</a> csum_help,
<a name="L123" href="source/net/ipv4/ip_tunnel_core.c#L123">123</a>                                          int gso_type_mask)
<a name="L124" href="source/net/ipv4/ip_tunnel_core.c#L124">124</a> {
<a name="L125" href="source/net/ipv4/ip_tunnel_core.c#L125">125</a>         int <a href="ident?i=err">err</a>;
<a name="L126" href="source/net/ipv4/ip_tunnel_core.c#L126">126</a> 
<a name="L127" href="source/net/ipv4/ip_tunnel_core.c#L127">127</a>         if (<a href="ident?i=likely">likely</a>(!<a href="ident?i=skb">skb</a>-&gt;encapsulation)) {
<a name="L128" href="source/net/ipv4/ip_tunnel_core.c#L128">128</a>                 <a href="ident?i=skb_reset_inner_headers">skb_reset_inner_headers</a>(<a href="ident?i=skb">skb</a>);
<a name="L129" href="source/net/ipv4/ip_tunnel_core.c#L129">129</a>                 <a href="ident?i=skb">skb</a>-&gt;encapsulation = 1;
<a name="L130" href="source/net/ipv4/ip_tunnel_core.c#L130">130</a>         }
<a name="L131" href="source/net/ipv4/ip_tunnel_core.c#L131">131</a> 
<a name="L132" href="source/net/ipv4/ip_tunnel_core.c#L132">132</a>         if (<a href="ident?i=skb_is_gso">skb_is_gso</a>(<a href="ident?i=skb">skb</a>)) {
<a name="L133" href="source/net/ipv4/ip_tunnel_core.c#L133">133</a>                 <a href="ident?i=err">err</a> = <a href="ident?i=skb_unclone">skb_unclone</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=GFP_ATOMIC">GFP_ATOMIC</a>);
<a name="L134" href="source/net/ipv4/ip_tunnel_core.c#L134">134</a>                 if (<a href="ident?i=unlikely">unlikely</a>(<a href="ident?i=err">err</a>))
<a name="L135" href="source/net/ipv4/ip_tunnel_core.c#L135">135</a>                         goto <a href="ident?i=error">error</a>;
<a name="L136" href="source/net/ipv4/ip_tunnel_core.c#L136">136</a>                 <a href="ident?i=skb_shinfo">skb_shinfo</a>(<a href="ident?i=skb">skb</a>)-&gt;gso_type |= gso_type_mask;
<a name="L137" href="source/net/ipv4/ip_tunnel_core.c#L137">137</a>                 return <a href="ident?i=skb">skb</a>;
<a name="L138" href="source/net/ipv4/ip_tunnel_core.c#L138">138</a>         }
<a name="L139" href="source/net/ipv4/ip_tunnel_core.c#L139">139</a> 
<a name="L140" href="source/net/ipv4/ip_tunnel_core.c#L140">140</a>         <b><i>/* If packet is not gso and we are resolving any partial checksum,</i></b>
<a name="L141" href="source/net/ipv4/ip_tunnel_core.c#L141">141</a> <b><i>         * clear encapsulation flag. This allows setting CHECKSUM_PARTIAL</i></b>
<a name="L142" href="source/net/ipv4/ip_tunnel_core.c#L142">142</a> <b><i>         * on the outer header without confusing devices that implement</i></b>
<a name="L143" href="source/net/ipv4/ip_tunnel_core.c#L143">143</a> <b><i>         * NETIF_F_IP_CSUM with encapsulation.</i></b>
<a name="L144" href="source/net/ipv4/ip_tunnel_core.c#L144">144</a> <b><i>         */</i></b>
<a name="L145" href="source/net/ipv4/ip_tunnel_core.c#L145">145</a>         if (csum_help)
<a name="L146" href="source/net/ipv4/ip_tunnel_core.c#L146">146</a>                 <a href="ident?i=skb">skb</a>-&gt;encapsulation = 0;
<a name="L147" href="source/net/ipv4/ip_tunnel_core.c#L147">147</a> 
<a name="L148" href="source/net/ipv4/ip_tunnel_core.c#L148">148</a>         if (<a href="ident?i=skb">skb</a>-&gt;ip_summed == <a href="ident?i=CHECKSUM_PARTIAL">CHECKSUM_PARTIAL</a> &amp;&amp; csum_help) {
<a name="L149" href="source/net/ipv4/ip_tunnel_core.c#L149">149</a>                 <a href="ident?i=err">err</a> = <a href="ident?i=skb_checksum_help">skb_checksum_help</a>(<a href="ident?i=skb">skb</a>);
<a name="L150" href="source/net/ipv4/ip_tunnel_core.c#L150">150</a>                 if (<a href="ident?i=unlikely">unlikely</a>(<a href="ident?i=err">err</a>))
<a name="L151" href="source/net/ipv4/ip_tunnel_core.c#L151">151</a>                         goto <a href="ident?i=error">error</a>;
<a name="L152" href="source/net/ipv4/ip_tunnel_core.c#L152">152</a>         } else if (<a href="ident?i=skb">skb</a>-&gt;ip_summed != <a href="ident?i=CHECKSUM_PARTIAL">CHECKSUM_PARTIAL</a>)
<a name="L153" href="source/net/ipv4/ip_tunnel_core.c#L153">153</a>                 <a href="ident?i=skb">skb</a>-&gt;ip_summed = <a href="ident?i=CHECKSUM_NONE">CHECKSUM_NONE</a>;
<a name="L154" href="source/net/ipv4/ip_tunnel_core.c#L154">154</a> 
<a name="L155" href="source/net/ipv4/ip_tunnel_core.c#L155">155</a>         return <a href="ident?i=skb">skb</a>;
<a name="L156" href="source/net/ipv4/ip_tunnel_core.c#L156">156</a> <a href="ident?i=error">error</a>:
<a name="L157" href="source/net/ipv4/ip_tunnel_core.c#L157">157</a>         <a href="ident?i=kfree_skb">kfree_skb</a>(<a href="ident?i=skb">skb</a>);
<a name="L158" href="source/net/ipv4/ip_tunnel_core.c#L158">158</a>         return <a href="ident?i=ERR_PTR">ERR_PTR</a>(<a href="ident?i=err">err</a>);
<a name="L159" href="source/net/ipv4/ip_tunnel_core.c#L159">159</a> }
<a name="L160" href="source/net/ipv4/ip_tunnel_core.c#L160">160</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=iptunnel_handle_offloads">iptunnel_handle_offloads</a>);
<a name="L161" href="source/net/ipv4/ip_tunnel_core.c#L161">161</a> 
<a name="L162" href="source/net/ipv4/ip_tunnel_core.c#L162">162</a> <b><i>/* Often modified stats are per cpu, other are shared (netdev-&gt;stats) */</i></b>
<a name="L163" href="source/net/ipv4/ip_tunnel_core.c#L163">163</a> struct <a href="ident?i=rtnl_link_stats64">rtnl_link_stats64</a> *<a href="ident?i=ip_tunnel_get_stats64">ip_tunnel_get_stats64</a>(struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>,
<a name="L164" href="source/net/ipv4/ip_tunnel_core.c#L164">164</a>                                                 struct <a href="ident?i=rtnl_link_stats64">rtnl_link_stats64</a> *tot)
<a name="L165" href="source/net/ipv4/ip_tunnel_core.c#L165">165</a> {
<a name="L166" href="source/net/ipv4/ip_tunnel_core.c#L166">166</a>         int <a href="ident?i=i">i</a>;
<a name="L167" href="source/net/ipv4/ip_tunnel_core.c#L167">167</a> 
<a name="L168" href="source/net/ipv4/ip_tunnel_core.c#L168">168</a>         <a href="ident?i=for_each_possible_cpu">for_each_possible_cpu</a>(<a href="ident?i=i">i</a>) {
<a name="L169" href="source/net/ipv4/ip_tunnel_core.c#L169">169</a>                 const struct <a href="ident?i=pcpu_sw_netstats">pcpu_sw_netstats</a> *tstats =
<a name="L170" href="source/net/ipv4/ip_tunnel_core.c#L170">170</a>                                                    <a href="ident?i=per_cpu_ptr">per_cpu_ptr</a>(<a href="ident?i=dev">dev</a>-&gt;tstats, <a href="ident?i=i">i</a>);
<a name="L171" href="source/net/ipv4/ip_tunnel_core.c#L171">171</a>                 <a href="ident?i=u64">u64</a> rx_packets, <a href="ident?i=rx_bytes">rx_bytes</a>, tx_packets, <a href="ident?i=tx_bytes">tx_bytes</a>;
<a name="L172" href="source/net/ipv4/ip_tunnel_core.c#L172">172</a>                 unsigned int <a href="ident?i=start">start</a>;
<a name="L173" href="source/net/ipv4/ip_tunnel_core.c#L173">173</a> 
<a name="L174" href="source/net/ipv4/ip_tunnel_core.c#L174">174</a>                 do {
<a name="L175" href="source/net/ipv4/ip_tunnel_core.c#L175">175</a>                         <a href="ident?i=start">start</a> = <a href="ident?i=u64_stats_fetch_begin_irq">u64_stats_fetch_begin_irq</a>(&amp;tstats-&gt;syncp);
<a name="L176" href="source/net/ipv4/ip_tunnel_core.c#L176">176</a>                         rx_packets = tstats-&gt;rx_packets;
<a name="L177" href="source/net/ipv4/ip_tunnel_core.c#L177">177</a>                         tx_packets = tstats-&gt;tx_packets;
<a name="L178" href="source/net/ipv4/ip_tunnel_core.c#L178">178</a>                         <a href="ident?i=rx_bytes">rx_bytes</a> = tstats-&gt;<a href="ident?i=rx_bytes">rx_bytes</a>;
<a name="L179" href="source/net/ipv4/ip_tunnel_core.c#L179">179</a>                         <a href="ident?i=tx_bytes">tx_bytes</a> = tstats-&gt;<a href="ident?i=tx_bytes">tx_bytes</a>;
<a name="L180" href="source/net/ipv4/ip_tunnel_core.c#L180">180</a>                 } while (<a href="ident?i=u64_stats_fetch_retry_irq">u64_stats_fetch_retry_irq</a>(&amp;tstats-&gt;syncp, <a href="ident?i=start">start</a>));
<a name="L181" href="source/net/ipv4/ip_tunnel_core.c#L181">181</a> 
<a name="L182" href="source/net/ipv4/ip_tunnel_core.c#L182">182</a>                 tot-&gt;rx_packets += rx_packets;
<a name="L183" href="source/net/ipv4/ip_tunnel_core.c#L183">183</a>                 tot-&gt;tx_packets += tx_packets;
<a name="L184" href="source/net/ipv4/ip_tunnel_core.c#L184">184</a>                 tot-&gt;<a href="ident?i=rx_bytes">rx_bytes</a>   += <a href="ident?i=rx_bytes">rx_bytes</a>;
<a name="L185" href="source/net/ipv4/ip_tunnel_core.c#L185">185</a>                 tot-&gt;<a href="ident?i=tx_bytes">tx_bytes</a>   += <a href="ident?i=tx_bytes">tx_bytes</a>;
<a name="L186" href="source/net/ipv4/ip_tunnel_core.c#L186">186</a>         }
<a name="L187" href="source/net/ipv4/ip_tunnel_core.c#L187">187</a> 
<a name="L188" href="source/net/ipv4/ip_tunnel_core.c#L188">188</a>         tot-&gt;multicast = <a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=stats">stats</a>.multicast;
<a name="L189" href="source/net/ipv4/ip_tunnel_core.c#L189">189</a> 
<a name="L190" href="source/net/ipv4/ip_tunnel_core.c#L190">190</a>         tot-&gt;rx_crc_errors = <a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=stats">stats</a>.rx_crc_errors;
<a name="L191" href="source/net/ipv4/ip_tunnel_core.c#L191">191</a>         tot-&gt;rx_fifo_errors = <a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=stats">stats</a>.rx_fifo_errors;
<a name="L192" href="source/net/ipv4/ip_tunnel_core.c#L192">192</a>         tot-&gt;rx_length_errors = <a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=stats">stats</a>.rx_length_errors;
<a name="L193" href="source/net/ipv4/ip_tunnel_core.c#L193">193</a>         tot-&gt;rx_frame_errors = <a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=stats">stats</a>.rx_frame_errors;
<a name="L194" href="source/net/ipv4/ip_tunnel_core.c#L194">194</a>         tot-&gt;rx_errors = <a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=stats">stats</a>.rx_errors;
<a name="L195" href="source/net/ipv4/ip_tunnel_core.c#L195">195</a> 
<a name="L196" href="source/net/ipv4/ip_tunnel_core.c#L196">196</a>         tot-&gt;tx_fifo_errors = <a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=stats">stats</a>.tx_fifo_errors;
<a name="L197" href="source/net/ipv4/ip_tunnel_core.c#L197">197</a>         tot-&gt;tx_carrier_errors = <a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=stats">stats</a>.tx_carrier_errors;
<a name="L198" href="source/net/ipv4/ip_tunnel_core.c#L198">198</a>         tot-&gt;tx_dropped = <a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=stats">stats</a>.tx_dropped;
<a name="L199" href="source/net/ipv4/ip_tunnel_core.c#L199">199</a>         tot-&gt;tx_aborted_errors = <a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=stats">stats</a>.tx_aborted_errors;
<a name="L200" href="source/net/ipv4/ip_tunnel_core.c#L200">200</a>         tot-&gt;tx_errors = <a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=stats">stats</a>.tx_errors;
<a name="L201" href="source/net/ipv4/ip_tunnel_core.c#L201">201</a> 
<a name="L202" href="source/net/ipv4/ip_tunnel_core.c#L202">202</a>         tot-&gt;collisions  = <a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=stats">stats</a>.collisions;
<a name="L203" href="source/net/ipv4/ip_tunnel_core.c#L203">203</a> 
<a name="L204" href="source/net/ipv4/ip_tunnel_core.c#L204">204</a>         return tot;
<a name="L205" href="source/net/ipv4/ip_tunnel_core.c#L205">205</a> }
<a name="L206" href="source/net/ipv4/ip_tunnel_core.c#L206">206</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=ip_tunnel_get_stats64">ip_tunnel_get_stats64</a>);
<a name="L207" href="source/net/ipv4/ip_tunnel_core.c#L207">207</a> </pre></div><p>
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
