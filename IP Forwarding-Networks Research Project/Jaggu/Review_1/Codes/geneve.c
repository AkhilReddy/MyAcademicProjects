<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title>Linux/net/ipv4/geneve.c - Linux Cross Reference - Free Electrons</title>
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
		 &nbsp;&bull;&nbsp;<b><i>source navigation</i></b> &nbsp;&bull;&nbsp;<a href="diff/net/ipv4/geneve.c">diff markup</a> &nbsp;&bull;&nbsp;<a href="ident">identifier search</a> &nbsp;&bull;&nbsp;<a href="search">freetext search</a> &nbsp;&bull;&nbsp;
		</p>
	</div>
</div>

<div id="topbar">
  
  <p>Version: &nbsp;<a href="source/net/ipv4/geneve.c?v=2.0.40">2.0.40</a>&nbsp;<a href="source/net/ipv4/geneve.c?v=2.2.26">2.2.26</a>&nbsp;<a href="source/net/ipv4/geneve.c?v=2.4.37">2.4.37</a>&nbsp;<a href="source/net/ipv4/geneve.c?v=3.5">3.5</a>&nbsp;<a href="source/net/ipv4/geneve.c?v=3.6">3.6</a>&nbsp;<a href="source/net/ipv4/geneve.c?v=3.7">3.7</a>&nbsp;<a href="source/net/ipv4/geneve.c?v=3.8">3.8</a>&nbsp;<a href="source/net/ipv4/geneve.c?v=3.9">3.9</a>&nbsp;<a href="source/net/ipv4/geneve.c?v=3.10">3.10</a>&nbsp;<a href="source/net/ipv4/geneve.c?v=3.11">3.11</a>&nbsp;<a href="source/net/ipv4/geneve.c?v=3.12">3.12</a>&nbsp;<a href="source/net/ipv4/geneve.c?v=3.13">3.13</a>&nbsp;<a href="source/net/ipv4/geneve.c?v=3.14">3.14</a>&nbsp;<a href="source/net/ipv4/geneve.c?v=3.15">3.15</a>&nbsp;<a href="source/net/ipv4/geneve.c?v=3.16">3.16</a>&nbsp;<a href="source/net/ipv4/geneve.c?v=3.17">3.17</a>&nbsp;<a href="source/net/ipv4/geneve.c?v=3.18">3.18</a>&nbsp;<a href="source/net/ipv4/geneve.c?v=3.19">3.19</a>&nbsp;<a href="source/net/ipv4/geneve.c?v=4.0">4.0</a>&nbsp;<b><i>4.1</i></b></p>
  
</div>

<h1><a href="source/">Linux</a>/<a href="source/net/">net</a>/<a href="source/net/ipv4/">ipv4</a>/<a href="source/net/ipv4/geneve.c">geneve.c</a></h1>
<div id="lxrcode"><pre>  <a name="L1" href="source/net/ipv4/geneve.c#L1">1</a> <b><i>/*</i></b>
  <a name="L2" href="source/net/ipv4/geneve.c#L2">2</a> <b><i> * Geneve: Generic Network Virtualization Encapsulation</i></b>
  <a name="L3" href="source/net/ipv4/geneve.c#L3">3</a> <b><i> *</i></b>
  <a name="L4" href="source/net/ipv4/geneve.c#L4">4</a> <b><i> * Copyright (c) 2014 Nicira, Inc.</i></b>
  <a name="L5" href="source/net/ipv4/geneve.c#L5">5</a> <b><i> *</i></b>
  <a name="L6" href="source/net/ipv4/geneve.c#L6">6</a> <b><i> * This program is free software; you can redistribute it and/or</i></b>
  <a name="L7" href="source/net/ipv4/geneve.c#L7">7</a> <b><i> * modify it under the terms of the GNU General Public License</i></b>
  <a name="L8" href="source/net/ipv4/geneve.c#L8">8</a> <b><i> * as published by the Free Software Foundation; either version</i></b>
  <a name="L9" href="source/net/ipv4/geneve.c#L9">9</a> <b><i> * 2 of the License, or (at your option) any later version.</i></b>
 <a name="L10" href="source/net/ipv4/geneve.c#L10">10</a> <b><i> */</i></b>
 <a name="L11" href="source/net/ipv4/geneve.c#L11">11</a> 
 <a name="L12" href="source/net/ipv4/geneve.c#L12">12</a> #define <a href="ident?i=pr_fmt">pr_fmt</a>(<a href="ident?i=fmt">fmt</a>) KBUILD_MODNAME <i>": "</i> <a href="ident?i=fmt">fmt</a>
 <a name="L13" href="source/net/ipv4/geneve.c#L13">13</a> 
 <a name="L14" href="source/net/ipv4/geneve.c#L14">14</a> #include &lt;linux/kernel.h&gt;
 <a name="L15" href="source/net/ipv4/geneve.c#L15">15</a> #include &lt;linux/types.h&gt;
 <a name="L16" href="source/net/ipv4/geneve.c#L16">16</a> #include &lt;linux/module.h&gt;
 <a name="L17" href="source/net/ipv4/geneve.c#L17">17</a> #include &lt;linux/errno.h&gt;
 <a name="L18" href="source/net/ipv4/geneve.c#L18">18</a> #include &lt;linux/slab.h&gt;
 <a name="L19" href="source/net/ipv4/geneve.c#L19">19</a> #include &lt;linux/skbuff.h&gt;
 <a name="L20" href="source/net/ipv4/geneve.c#L20">20</a> #include &lt;linux/list.h&gt;
 <a name="L21" href="source/net/ipv4/geneve.c#L21">21</a> #include &lt;linux/netdevice.h&gt;
 <a name="L22" href="source/net/ipv4/geneve.c#L22">22</a> #include &lt;linux/in.h&gt;
 <a name="L23" href="source/net/ipv4/geneve.c#L23">23</a> #include &lt;linux/ip.h&gt;
 <a name="L24" href="source/net/ipv4/geneve.c#L24">24</a> #include &lt;linux/udp.h&gt;
 <a name="L25" href="source/net/ipv4/geneve.c#L25">25</a> #include &lt;linux/igmp.h&gt;
 <a name="L26" href="source/net/ipv4/geneve.c#L26">26</a> #include &lt;linux/etherdevice.h&gt;
 <a name="L27" href="source/net/ipv4/geneve.c#L27">27</a> #include &lt;linux/if_ether.h&gt;
 <a name="L28" href="source/net/ipv4/geneve.c#L28">28</a> #include &lt;linux/if_vlan.h&gt;
 <a name="L29" href="source/net/ipv4/geneve.c#L29">29</a> #include &lt;linux/ethtool.h&gt;
 <a name="L30" href="source/net/ipv4/geneve.c#L30">30</a> #include &lt;linux/mutex.h&gt;
 <a name="L31" href="source/net/ipv4/geneve.c#L31">31</a> #include &lt;net/arp.h&gt;
 <a name="L32" href="source/net/ipv4/geneve.c#L32">32</a> #include &lt;net/ndisc.h&gt;
 <a name="L33" href="source/net/ipv4/geneve.c#L33">33</a> #include &lt;net/ip.h&gt;
 <a name="L34" href="source/net/ipv4/geneve.c#L34">34</a> #include &lt;net/ip_tunnels.h&gt;
 <a name="L35" href="source/net/ipv4/geneve.c#L35">35</a> #include &lt;net/icmp.h&gt;
 <a name="L36" href="source/net/ipv4/geneve.c#L36">36</a> #include &lt;net/udp.h&gt;
 <a name="L37" href="source/net/ipv4/geneve.c#L37">37</a> #include &lt;net/rtnetlink.h&gt;
 <a name="L38" href="source/net/ipv4/geneve.c#L38">38</a> #include &lt;net/route.h&gt;
 <a name="L39" href="source/net/ipv4/geneve.c#L39">39</a> #include &lt;net/dsfield.h&gt;
 <a name="L40" href="source/net/ipv4/geneve.c#L40">40</a> #include &lt;net/inet_ecn.h&gt;
 <a name="L41" href="source/net/ipv4/geneve.c#L41">41</a> #include &lt;net/net_namespace.h&gt;
 <a name="L42" href="source/net/ipv4/geneve.c#L42">42</a> #include &lt;net/netns/generic.h&gt;
 <a name="L43" href="source/net/ipv4/geneve.c#L43">43</a> #include &lt;net/geneve.h&gt;
 <a name="L44" href="source/net/ipv4/geneve.c#L44">44</a> #include &lt;net/protocol.h&gt;
 <a name="L45" href="source/net/ipv4/geneve.c#L45">45</a> #include &lt;net/udp_tunnel.h&gt;
 <a name="L46" href="source/net/ipv4/geneve.c#L46">46</a> #if <a href="ident?i=IS_ENABLED">IS_ENABLED</a>(CONFIG_IPV6)
 <a name="L47" href="source/net/ipv4/geneve.c#L47">47</a> #include &lt;net/ipv6.h&gt;
 <a name="L48" href="source/net/ipv4/geneve.c#L48">48</a> #include &lt;net/addrconf.h&gt;
 <a name="L49" href="source/net/ipv4/geneve.c#L49">49</a> #include &lt;net/ip6_tunnel.h&gt;
 <a name="L50" href="source/net/ipv4/geneve.c#L50">50</a> #include &lt;net/ip6_checksum.h&gt;
 <a name="L51" href="source/net/ipv4/geneve.c#L51">51</a> #endif
 <a name="L52" href="source/net/ipv4/geneve.c#L52">52</a> 
 <a name="L53" href="source/net/ipv4/geneve.c#L53">53</a> <b><i>/* Protects sock_list and refcounts. */</i></b>
 <a name="L54" href="source/net/ipv4/geneve.c#L54">54</a> static <a href="ident?i=DEFINE_MUTEX">DEFINE_MUTEX</a>(geneve_mutex);
 <a name="L55" href="source/net/ipv4/geneve.c#L55">55</a> 
 <a name="L56" href="source/net/ipv4/geneve.c#L56">56</a> <b><i>/* per-network namespace private data for this module */</i></b>
 <a name="L57" href="source/net/ipv4/geneve.c#L57">57</a> struct <a href="ident?i=geneve_net">geneve_net</a> {
 <a name="L58" href="source/net/ipv4/geneve.c#L58">58</a>         struct <a href="ident?i=list_head">list_head</a>        sock_list;
 <a name="L59" href="source/net/ipv4/geneve.c#L59">59</a> };
 <a name="L60" href="source/net/ipv4/geneve.c#L60">60</a> 
 <a name="L61" href="source/net/ipv4/geneve.c#L61">61</a> static int <a href="ident?i=geneve_net_id">geneve_net_id</a>;
 <a name="L62" href="source/net/ipv4/geneve.c#L62">62</a> 
 <a name="L63" href="source/net/ipv4/geneve.c#L63">63</a> static inline struct <a href="ident?i=genevehdr">genevehdr</a> *<a href="ident?i=geneve_hdr">geneve_hdr</a>(const struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
 <a name="L64" href="source/net/ipv4/geneve.c#L64">64</a> {
 <a name="L65" href="source/net/ipv4/geneve.c#L65">65</a>         return (struct <a href="ident?i=genevehdr">genevehdr</a> *)(<a href="ident?i=udp_hdr">udp_hdr</a>(<a href="ident?i=skb">skb</a>) + 1);
 <a name="L66" href="source/net/ipv4/geneve.c#L66">66</a> }
 <a name="L67" href="source/net/ipv4/geneve.c#L67">67</a> 
 <a name="L68" href="source/net/ipv4/geneve.c#L68">68</a> static struct <a href="ident?i=geneve_sock">geneve_sock</a> *<a href="ident?i=geneve_find_sock">geneve_find_sock</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>,
 <a name="L69" href="source/net/ipv4/geneve.c#L69">69</a>                                             <a href="ident?i=sa_family_t">sa_family_t</a> <a href="ident?i=family">family</a>, <a href="ident?i=__be16">__be16</a> <a href="ident?i=port">port</a>)
 <a name="L70" href="source/net/ipv4/geneve.c#L70">70</a> {
 <a name="L71" href="source/net/ipv4/geneve.c#L71">71</a>         struct <a href="ident?i=geneve_net">geneve_net</a> *gn = <a href="ident?i=net_generic">net_generic</a>(<a href="ident?i=net">net</a>, <a href="ident?i=geneve_net_id">geneve_net_id</a>);
 <a name="L72" href="source/net/ipv4/geneve.c#L72">72</a>         struct <a href="ident?i=geneve_sock">geneve_sock</a> *<a href="ident?i=gs">gs</a>;
 <a name="L73" href="source/net/ipv4/geneve.c#L73">73</a> 
 <a name="L74" href="source/net/ipv4/geneve.c#L74">74</a>         <a href="ident?i=list_for_each_entry">list_for_each_entry</a>(<a href="ident?i=gs">gs</a>, &amp;gn-&gt;sock_list, <a href="ident?i=list">list</a>) {
 <a name="L75" href="source/net/ipv4/geneve.c#L75">75</a>                 if (<a href="ident?i=inet_sk">inet_sk</a>(<a href="ident?i=gs">gs</a>-&gt;<a href="ident?i=sock">sock</a>-&gt;sk)-&gt;inet_sport == <a href="ident?i=port">port</a> &amp;&amp;
 <a name="L76" href="source/net/ipv4/geneve.c#L76">76</a>                     <a href="ident?i=inet_sk">inet_sk</a>(<a href="ident?i=gs">gs</a>-&gt;<a href="ident?i=sock">sock</a>-&gt;sk)-&gt;sk.<a href="ident?i=sk_family">sk_family</a> == <a href="ident?i=family">family</a>)
 <a name="L77" href="source/net/ipv4/geneve.c#L77">77</a>                         return <a href="ident?i=gs">gs</a>;
 <a name="L78" href="source/net/ipv4/geneve.c#L78">78</a>         }
 <a name="L79" href="source/net/ipv4/geneve.c#L79">79</a> 
 <a name="L80" href="source/net/ipv4/geneve.c#L80">80</a>         return <a href="ident?i=NULL">NULL</a>;
 <a name="L81" href="source/net/ipv4/geneve.c#L81">81</a> }
 <a name="L82" href="source/net/ipv4/geneve.c#L82">82</a> 
 <a name="L83" href="source/net/ipv4/geneve.c#L83">83</a> static void <a href="ident?i=geneve_build_header">geneve_build_header</a>(struct <a href="ident?i=genevehdr">genevehdr</a> *geneveh,
 <a name="L84" href="source/net/ipv4/geneve.c#L84">84</a>                                 <a href="ident?i=__be16">__be16</a> <a href="ident?i=tun_flags">tun_flags</a>, <a href="ident?i=u8">u8</a> vni[3],
 <a name="L85" href="source/net/ipv4/geneve.c#L85">85</a>                                 <a href="ident?i=u8">u8</a> options_len, <a href="ident?i=u8">u8</a> *<a href="ident?i=options">options</a>)
 <a name="L86" href="source/net/ipv4/geneve.c#L86">86</a> {
 <a name="L87" href="source/net/ipv4/geneve.c#L87">87</a>         geneveh-&gt;ver = <a href="ident?i=GENEVE_VER">GENEVE_VER</a>;
 <a name="L88" href="source/net/ipv4/geneve.c#L88">88</a>         geneveh-&gt;opt_len = options_len / 4;
 <a name="L89" href="source/net/ipv4/geneve.c#L89">89</a>         geneveh-&gt;oam = !!(<a href="ident?i=tun_flags">tun_flags</a> &amp; <a href="ident?i=TUNNEL_OAM">TUNNEL_OAM</a>);
 <a name="L90" href="source/net/ipv4/geneve.c#L90">90</a>         geneveh-&gt;critical = !!(<a href="ident?i=tun_flags">tun_flags</a> &amp; <a href="ident?i=TUNNEL_CRIT_OPT">TUNNEL_CRIT_OPT</a>);
 <a name="L91" href="source/net/ipv4/geneve.c#L91">91</a>         geneveh-&gt;rsvd1 = 0;
 <a name="L92" href="source/net/ipv4/geneve.c#L92">92</a>         <a href="ident?i=memcpy">memcpy</a>(geneveh-&gt;vni, vni, 3);
 <a name="L93" href="source/net/ipv4/geneve.c#L93">93</a>         geneveh-&gt;<a href="ident?i=proto_type">proto_type</a> = <a href="ident?i=htons">htons</a>(<a href="ident?i=ETH_P_TEB">ETH_P_TEB</a>);
 <a name="L94" href="source/net/ipv4/geneve.c#L94">94</a>         geneveh-&gt;rsvd2 = 0;
 <a name="L95" href="source/net/ipv4/geneve.c#L95">95</a> 
 <a name="L96" href="source/net/ipv4/geneve.c#L96">96</a>         <a href="ident?i=memcpy">memcpy</a>(geneveh-&gt;<a href="ident?i=options">options</a>, <a href="ident?i=options">options</a>, options_len);
 <a name="L97" href="source/net/ipv4/geneve.c#L97">97</a> }
 <a name="L98" href="source/net/ipv4/geneve.c#L98">98</a> 
 <a name="L99" href="source/net/ipv4/geneve.c#L99">99</a> <b><i>/* Transmit a fully formatted Geneve frame.</i></b>
<a name="L100" href="source/net/ipv4/geneve.c#L100">100</a> <b><i> *</i></b>
<a name="L101" href="source/net/ipv4/geneve.c#L101">101</a> <b><i> * When calling this function. The skb-&gt;data should point</i></b>
<a name="L102" href="source/net/ipv4/geneve.c#L102">102</a> <b><i> * to the geneve header which is fully formed.</i></b>
<a name="L103" href="source/net/ipv4/geneve.c#L103">103</a> <b><i> *</i></b>
<a name="L104" href="source/net/ipv4/geneve.c#L104">104</a> <b><i> * This function will add other UDP tunnel headers.</i></b>
<a name="L105" href="source/net/ipv4/geneve.c#L105">105</a> <b><i> */</i></b>
<a name="L106" href="source/net/ipv4/geneve.c#L106">106</a> int <a href="ident?i=geneve_xmit_skb">geneve_xmit_skb</a>(struct <a href="ident?i=geneve_sock">geneve_sock</a> *<a href="ident?i=gs">gs</a>, struct <a href="ident?i=rtable">rtable</a> *<a href="ident?i=rt">rt</a>,
<a name="L107" href="source/net/ipv4/geneve.c#L107">107</a>                     struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, <a href="ident?i=__be32">__be32</a> <a href="ident?i=src">src</a>, <a href="ident?i=__be32">__be32</a> <a href="ident?i=dst">dst</a>, <a href="ident?i=__u8">__u8</a> tos,
<a name="L108" href="source/net/ipv4/geneve.c#L108">108</a>                     <a href="ident?i=__u8">__u8</a> <a href="ident?i=ttl">ttl</a>, <a href="ident?i=__be16">__be16</a> <a href="ident?i=df">df</a>, <a href="ident?i=__be16">__be16</a> src_port, <a href="ident?i=__be16">__be16</a> dst_port,
<a name="L109" href="source/net/ipv4/geneve.c#L109">109</a>                     <a href="ident?i=__be16">__be16</a> <a href="ident?i=tun_flags">tun_flags</a>, <a href="ident?i=u8">u8</a> vni[3], <a href="ident?i=u8">u8</a> opt_len, <a href="ident?i=u8">u8</a> *opt,
<a name="L110" href="source/net/ipv4/geneve.c#L110">110</a>                     <a href="ident?i=bool">bool</a> <a href="ident?i=csum">csum</a>, <a href="ident?i=bool">bool</a> xnet)
<a name="L111" href="source/net/ipv4/geneve.c#L111">111</a> {
<a name="L112" href="source/net/ipv4/geneve.c#L112">112</a>         struct <a href="ident?i=genevehdr">genevehdr</a> *gnvh;
<a name="L113" href="source/net/ipv4/geneve.c#L113">113</a>         int min_headroom;
<a name="L114" href="source/net/ipv4/geneve.c#L114">114</a>         int <a href="ident?i=err">err</a>;
<a name="L115" href="source/net/ipv4/geneve.c#L115">115</a> 
<a name="L116" href="source/net/ipv4/geneve.c#L116">116</a>         min_headroom = <a href="ident?i=LL_RESERVED_SPACE">LL_RESERVED_SPACE</a>(<a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>.<a href="ident?i=dev">dev</a>) + <a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>.<a href="ident?i=header_len">header_len</a>
<a name="L117" href="source/net/ipv4/geneve.c#L117">117</a>                         + <a href="ident?i=GENEVE_BASE_HLEN">GENEVE_BASE_HLEN</a> + opt_len + sizeof(struct <a href="ident?i=iphdr">iphdr</a>)
<a name="L118" href="source/net/ipv4/geneve.c#L118">118</a>                         + (<a href="ident?i=skb_vlan_tag_present">skb_vlan_tag_present</a>(<a href="ident?i=skb">skb</a>) ? <a href="ident?i=VLAN_HLEN">VLAN_HLEN</a> : 0);
<a name="L119" href="source/net/ipv4/geneve.c#L119">119</a> 
<a name="L120" href="source/net/ipv4/geneve.c#L120">120</a>         <a href="ident?i=err">err</a> = <a href="ident?i=skb_cow_head">skb_cow_head</a>(<a href="ident?i=skb">skb</a>, min_headroom);
<a name="L121" href="source/net/ipv4/geneve.c#L121">121</a>         if (<a href="ident?i=unlikely">unlikely</a>(<a href="ident?i=err">err</a>)) {
<a name="L122" href="source/net/ipv4/geneve.c#L122">122</a>                 <a href="ident?i=kfree_skb">kfree_skb</a>(<a href="ident?i=skb">skb</a>);
<a name="L123" href="source/net/ipv4/geneve.c#L123">123</a>                 return <a href="ident?i=err">err</a>;
<a name="L124" href="source/net/ipv4/geneve.c#L124">124</a>         }
<a name="L125" href="source/net/ipv4/geneve.c#L125">125</a> 
<a name="L126" href="source/net/ipv4/geneve.c#L126">126</a>         <a href="ident?i=skb">skb</a> = <a href="ident?i=vlan_hwaccel_push_inside">vlan_hwaccel_push_inside</a>(<a href="ident?i=skb">skb</a>);
<a name="L127" href="source/net/ipv4/geneve.c#L127">127</a>         if (<a href="ident?i=unlikely">unlikely</a>(!<a href="ident?i=skb">skb</a>))
<a name="L128" href="source/net/ipv4/geneve.c#L128">128</a>                 return -<a href="ident?i=ENOMEM">ENOMEM</a>;
<a name="L129" href="source/net/ipv4/geneve.c#L129">129</a> 
<a name="L130" href="source/net/ipv4/geneve.c#L130">130</a>         <a href="ident?i=skb">skb</a> = <a href="ident?i=udp_tunnel_handle_offloads">udp_tunnel_handle_offloads</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=csum">csum</a>);
<a name="L131" href="source/net/ipv4/geneve.c#L131">131</a>         if (<a href="ident?i=IS_ERR">IS_ERR</a>(<a href="ident?i=skb">skb</a>))
<a name="L132" href="source/net/ipv4/geneve.c#L132">132</a>                 return <a href="ident?i=PTR_ERR">PTR_ERR</a>(<a href="ident?i=skb">skb</a>);
<a name="L133" href="source/net/ipv4/geneve.c#L133">133</a> 
<a name="L134" href="source/net/ipv4/geneve.c#L134">134</a>         gnvh = (struct <a href="ident?i=genevehdr">genevehdr</a> *)<a href="ident?i=__skb_push">__skb_push</a>(<a href="ident?i=skb">skb</a>, sizeof(*gnvh) + opt_len);
<a name="L135" href="source/net/ipv4/geneve.c#L135">135</a>         <a href="ident?i=geneve_build_header">geneve_build_header</a>(gnvh, <a href="ident?i=tun_flags">tun_flags</a>, vni, opt_len, opt);
<a name="L136" href="source/net/ipv4/geneve.c#L136">136</a> 
<a name="L137" href="source/net/ipv4/geneve.c#L137">137</a>         <a href="ident?i=skb_set_inner_protocol">skb_set_inner_protocol</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=htons">htons</a>(<a href="ident?i=ETH_P_TEB">ETH_P_TEB</a>));
<a name="L138" href="source/net/ipv4/geneve.c#L138">138</a> 
<a name="L139" href="source/net/ipv4/geneve.c#L139">139</a>         return <a href="ident?i=udp_tunnel_xmit_skb">udp_tunnel_xmit_skb</a>(<a href="ident?i=rt">rt</a>, <a href="ident?i=gs">gs</a>-&gt;<a href="ident?i=sock">sock</a>-&gt;sk, <a href="ident?i=skb">skb</a>, <a href="ident?i=src">src</a>, <a href="ident?i=dst">dst</a>,
<a name="L140" href="source/net/ipv4/geneve.c#L140">140</a>                                    tos, <a href="ident?i=ttl">ttl</a>, <a href="ident?i=df">df</a>, src_port, dst_port, xnet,
<a name="L141" href="source/net/ipv4/geneve.c#L141">141</a>                                    !<a href="ident?i=csum">csum</a>);
<a name="L142" href="source/net/ipv4/geneve.c#L142">142</a> }
<a name="L143" href="source/net/ipv4/geneve.c#L143">143</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=geneve_xmit_skb">geneve_xmit_skb</a>);
<a name="L144" href="source/net/ipv4/geneve.c#L144">144</a> 
<a name="L145" href="source/net/ipv4/geneve.c#L145">145</a> static int <a href="ident?i=geneve_hlen">geneve_hlen</a>(struct <a href="ident?i=genevehdr">genevehdr</a> *gh)
<a name="L146" href="source/net/ipv4/geneve.c#L146">146</a> {
<a name="L147" href="source/net/ipv4/geneve.c#L147">147</a>         return sizeof(*gh) + gh-&gt;opt_len * 4;
<a name="L148" href="source/net/ipv4/geneve.c#L148">148</a> }
<a name="L149" href="source/net/ipv4/geneve.c#L149">149</a> 
<a name="L150" href="source/net/ipv4/geneve.c#L150">150</a> static struct <a href="ident?i=sk_buff">sk_buff</a> **<a href="ident?i=geneve_gro_receive">geneve_gro_receive</a>(struct <a href="ident?i=sk_buff">sk_buff</a> **<a href="ident?i=head">head</a>,
<a name="L151" href="source/net/ipv4/geneve.c#L151">151</a>                                            struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
<a name="L152" href="source/net/ipv4/geneve.c#L152">152</a>                                            struct <a href="ident?i=udp_offload">udp_offload</a> *uoff)
<a name="L153" href="source/net/ipv4/geneve.c#L153">153</a> {
<a name="L154" href="source/net/ipv4/geneve.c#L154">154</a>         struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=p">p</a>, **pp = <a href="ident?i=NULL">NULL</a>;
<a name="L155" href="source/net/ipv4/geneve.c#L155">155</a>         struct <a href="ident?i=genevehdr">genevehdr</a> *gh, *gh2;
<a name="L156" href="source/net/ipv4/geneve.c#L156">156</a>         unsigned int hlen, gh_len, off_gnv;
<a name="L157" href="source/net/ipv4/geneve.c#L157">157</a>         const struct <a href="ident?i=packet_offload">packet_offload</a> *ptype;
<a name="L158" href="source/net/ipv4/geneve.c#L158">158</a>         <a href="ident?i=__be16">__be16</a> <a href="ident?i=type">type</a>;
<a name="L159" href="source/net/ipv4/geneve.c#L159">159</a>         int <a href="ident?i=flush">flush</a> = 1;
<a name="L160" href="source/net/ipv4/geneve.c#L160">160</a> 
<a name="L161" href="source/net/ipv4/geneve.c#L161">161</a>         off_gnv = <a href="ident?i=skb_gro_offset">skb_gro_offset</a>(<a href="ident?i=skb">skb</a>);
<a name="L162" href="source/net/ipv4/geneve.c#L162">162</a>         hlen = off_gnv + sizeof(*gh);
<a name="L163" href="source/net/ipv4/geneve.c#L163">163</a>         gh = <a href="ident?i=skb_gro_header_fast">skb_gro_header_fast</a>(<a href="ident?i=skb">skb</a>, off_gnv);
<a name="L164" href="source/net/ipv4/geneve.c#L164">164</a>         if (<a href="ident?i=skb_gro_header_hard">skb_gro_header_hard</a>(<a href="ident?i=skb">skb</a>, hlen)) {
<a name="L165" href="source/net/ipv4/geneve.c#L165">165</a>                 gh = <a href="ident?i=skb_gro_header_slow">skb_gro_header_slow</a>(<a href="ident?i=skb">skb</a>, hlen, off_gnv);
<a name="L166" href="source/net/ipv4/geneve.c#L166">166</a>                 if (<a href="ident?i=unlikely">unlikely</a>(!gh))
<a name="L167" href="source/net/ipv4/geneve.c#L167">167</a>                         goto <a href="ident?i=out">out</a>;
<a name="L168" href="source/net/ipv4/geneve.c#L168">168</a>         }
<a name="L169" href="source/net/ipv4/geneve.c#L169">169</a> 
<a name="L170" href="source/net/ipv4/geneve.c#L170">170</a>         if (gh-&gt;ver != <a href="ident?i=GENEVE_VER">GENEVE_VER</a> || gh-&gt;oam)
<a name="L171" href="source/net/ipv4/geneve.c#L171">171</a>                 goto <a href="ident?i=out">out</a>;
<a name="L172" href="source/net/ipv4/geneve.c#L172">172</a>         gh_len = <a href="ident?i=geneve_hlen">geneve_hlen</a>(gh);
<a name="L173" href="source/net/ipv4/geneve.c#L173">173</a> 
<a name="L174" href="source/net/ipv4/geneve.c#L174">174</a>         hlen = off_gnv + gh_len;
<a name="L175" href="source/net/ipv4/geneve.c#L175">175</a>         if (<a href="ident?i=skb_gro_header_hard">skb_gro_header_hard</a>(<a href="ident?i=skb">skb</a>, hlen)) {
<a name="L176" href="source/net/ipv4/geneve.c#L176">176</a>                 gh = <a href="ident?i=skb_gro_header_slow">skb_gro_header_slow</a>(<a href="ident?i=skb">skb</a>, hlen, off_gnv);
<a name="L177" href="source/net/ipv4/geneve.c#L177">177</a>                 if (<a href="ident?i=unlikely">unlikely</a>(!gh))
<a name="L178" href="source/net/ipv4/geneve.c#L178">178</a>                         goto <a href="ident?i=out">out</a>;
<a name="L179" href="source/net/ipv4/geneve.c#L179">179</a>         }
<a name="L180" href="source/net/ipv4/geneve.c#L180">180</a> 
<a name="L181" href="source/net/ipv4/geneve.c#L181">181</a>         <a href="ident?i=flush">flush</a> = 0;
<a name="L182" href="source/net/ipv4/geneve.c#L182">182</a> 
<a name="L183" href="source/net/ipv4/geneve.c#L183">183</a>         for (<a href="ident?i=p">p</a> = *<a href="ident?i=head">head</a>; <a href="ident?i=p">p</a>; <a href="ident?i=p">p</a> = <a href="ident?i=p">p</a>-&gt;<a href="ident?i=next">next</a>) {
<a name="L184" href="source/net/ipv4/geneve.c#L184">184</a>                 if (!<a href="ident?i=NAPI_GRO_CB">NAPI_GRO_CB</a>(<a href="ident?i=p">p</a>)-&gt;same_flow)
<a name="L185" href="source/net/ipv4/geneve.c#L185">185</a>                         continue;
<a name="L186" href="source/net/ipv4/geneve.c#L186">186</a> 
<a name="L187" href="source/net/ipv4/geneve.c#L187">187</a>                 gh2 = (struct <a href="ident?i=genevehdr">genevehdr</a> *)(<a href="ident?i=p">p</a>-&gt;<a href="ident?i=data">data</a> + off_gnv);
<a name="L188" href="source/net/ipv4/geneve.c#L188">188</a>                 if (gh-&gt;opt_len != gh2-&gt;opt_len ||
<a name="L189" href="source/net/ipv4/geneve.c#L189">189</a>                     <a href="ident?i=memcmp">memcmp</a>(gh, gh2, gh_len)) {
<a name="L190" href="source/net/ipv4/geneve.c#L190">190</a>                         <a href="ident?i=NAPI_GRO_CB">NAPI_GRO_CB</a>(<a href="ident?i=p">p</a>)-&gt;same_flow = 0;
<a name="L191" href="source/net/ipv4/geneve.c#L191">191</a>                         continue;
<a name="L192" href="source/net/ipv4/geneve.c#L192">192</a>                 }
<a name="L193" href="source/net/ipv4/geneve.c#L193">193</a>         }
<a name="L194" href="source/net/ipv4/geneve.c#L194">194</a> 
<a name="L195" href="source/net/ipv4/geneve.c#L195">195</a>         <a href="ident?i=type">type</a> = gh-&gt;<a href="ident?i=proto_type">proto_type</a>;
<a name="L196" href="source/net/ipv4/geneve.c#L196">196</a> 
<a name="L197" href="source/net/ipv4/geneve.c#L197">197</a>         <a href="ident?i=rcu_read_lock">rcu_read_lock</a>();
<a name="L198" href="source/net/ipv4/geneve.c#L198">198</a>         ptype = <a href="ident?i=gro_find_receive_by_type">gro_find_receive_by_type</a>(<a href="ident?i=type">type</a>);
<a name="L199" href="source/net/ipv4/geneve.c#L199">199</a>         if (!ptype) {
<a name="L200" href="source/net/ipv4/geneve.c#L200">200</a>                 <a href="ident?i=flush">flush</a> = 1;
<a name="L201" href="source/net/ipv4/geneve.c#L201">201</a>                 goto out_unlock;
<a name="L202" href="source/net/ipv4/geneve.c#L202">202</a>         }
<a name="L203" href="source/net/ipv4/geneve.c#L203">203</a> 
<a name="L204" href="source/net/ipv4/geneve.c#L204">204</a>         <a href="ident?i=skb_gro_pull">skb_gro_pull</a>(<a href="ident?i=skb">skb</a>, gh_len);
<a name="L205" href="source/net/ipv4/geneve.c#L205">205</a>         <a href="ident?i=skb_gro_postpull_rcsum">skb_gro_postpull_rcsum</a>(<a href="ident?i=skb">skb</a>, gh, gh_len);
<a name="L206" href="source/net/ipv4/geneve.c#L206">206</a>         pp = ptype-&gt;<a href="ident?i=callbacks">callbacks</a>.gro_receive(<a href="ident?i=head">head</a>, <a href="ident?i=skb">skb</a>);
<a name="L207" href="source/net/ipv4/geneve.c#L207">207</a> 
<a name="L208" href="source/net/ipv4/geneve.c#L208">208</a> out_unlock:
<a name="L209" href="source/net/ipv4/geneve.c#L209">209</a>         <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L210" href="source/net/ipv4/geneve.c#L210">210</a> <a href="ident?i=out">out</a>:
<a name="L211" href="source/net/ipv4/geneve.c#L211">211</a>         <a href="ident?i=NAPI_GRO_CB">NAPI_GRO_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=flush">flush</a> |= <a href="ident?i=flush">flush</a>;
<a name="L212" href="source/net/ipv4/geneve.c#L212">212</a> 
<a name="L213" href="source/net/ipv4/geneve.c#L213">213</a>         return pp;
<a name="L214" href="source/net/ipv4/geneve.c#L214">214</a> }
<a name="L215" href="source/net/ipv4/geneve.c#L215">215</a> 
<a name="L216" href="source/net/ipv4/geneve.c#L216">216</a> static int <a href="ident?i=geneve_gro_complete">geneve_gro_complete</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, int nhoff,
<a name="L217" href="source/net/ipv4/geneve.c#L217">217</a>                                struct <a href="ident?i=udp_offload">udp_offload</a> *uoff)
<a name="L218" href="source/net/ipv4/geneve.c#L218">218</a> {
<a name="L219" href="source/net/ipv4/geneve.c#L219">219</a>         struct <a href="ident?i=genevehdr">genevehdr</a> *gh;
<a name="L220" href="source/net/ipv4/geneve.c#L220">220</a>         struct <a href="ident?i=packet_offload">packet_offload</a> *ptype;
<a name="L221" href="source/net/ipv4/geneve.c#L221">221</a>         <a href="ident?i=__be16">__be16</a> <a href="ident?i=type">type</a>;
<a name="L222" href="source/net/ipv4/geneve.c#L222">222</a>         int gh_len;
<a name="L223" href="source/net/ipv4/geneve.c#L223">223</a>         int <a href="ident?i=err">err</a> = -<a href="ident?i=ENOSYS">ENOSYS</a>;
<a name="L224" href="source/net/ipv4/geneve.c#L224">224</a> 
<a name="L225" href="source/net/ipv4/geneve.c#L225">225</a>         <a href="ident?i=udp_tunnel_gro_complete">udp_tunnel_gro_complete</a>(<a href="ident?i=skb">skb</a>, nhoff);
<a name="L226" href="source/net/ipv4/geneve.c#L226">226</a> 
<a name="L227" href="source/net/ipv4/geneve.c#L227">227</a>         gh = (struct <a href="ident?i=genevehdr">genevehdr</a> *)(<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=data">data</a> + nhoff);
<a name="L228" href="source/net/ipv4/geneve.c#L228">228</a>         gh_len = <a href="ident?i=geneve_hlen">geneve_hlen</a>(gh);
<a name="L229" href="source/net/ipv4/geneve.c#L229">229</a>         <a href="ident?i=type">type</a> = gh-&gt;<a href="ident?i=proto_type">proto_type</a>;
<a name="L230" href="source/net/ipv4/geneve.c#L230">230</a> 
<a name="L231" href="source/net/ipv4/geneve.c#L231">231</a>         <a href="ident?i=rcu_read_lock">rcu_read_lock</a>();
<a name="L232" href="source/net/ipv4/geneve.c#L232">232</a>         ptype = <a href="ident?i=gro_find_complete_by_type">gro_find_complete_by_type</a>(<a href="ident?i=type">type</a>);
<a name="L233" href="source/net/ipv4/geneve.c#L233">233</a>         if (ptype)
<a name="L234" href="source/net/ipv4/geneve.c#L234">234</a>                 <a href="ident?i=err">err</a> = ptype-&gt;<a href="ident?i=callbacks">callbacks</a>.gro_complete(<a href="ident?i=skb">skb</a>, nhoff + gh_len);
<a name="L235" href="source/net/ipv4/geneve.c#L235">235</a> 
<a name="L236" href="source/net/ipv4/geneve.c#L236">236</a>         <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L237" href="source/net/ipv4/geneve.c#L237">237</a>         return <a href="ident?i=err">err</a>;
<a name="L238" href="source/net/ipv4/geneve.c#L238">238</a> }
<a name="L239" href="source/net/ipv4/geneve.c#L239">239</a> 
<a name="L240" href="source/net/ipv4/geneve.c#L240">240</a> static void <a href="ident?i=geneve_notify_add_rx_port">geneve_notify_add_rx_port</a>(struct <a href="ident?i=geneve_sock">geneve_sock</a> *<a href="ident?i=gs">gs</a>)
<a name="L241" href="source/net/ipv4/geneve.c#L241">241</a> {
<a name="L242" href="source/net/ipv4/geneve.c#L242">242</a>         struct <a href="ident?i=sock">sock</a> *sk = <a href="ident?i=gs">gs</a>-&gt;<a href="ident?i=sock">sock</a>-&gt;sk;
<a name="L243" href="source/net/ipv4/geneve.c#L243">243</a>         <a href="ident?i=sa_family_t">sa_family_t</a> sa_family = sk-&gt;<a href="ident?i=sk_family">sk_family</a>;
<a name="L244" href="source/net/ipv4/geneve.c#L244">244</a>         int <a href="ident?i=err">err</a>;
<a name="L245" href="source/net/ipv4/geneve.c#L245">245</a> 
<a name="L246" href="source/net/ipv4/geneve.c#L246">246</a>         if (sa_family == <a href="ident?i=AF_INET">AF_INET</a>) {
<a name="L247" href="source/net/ipv4/geneve.c#L247">247</a>                 <a href="ident?i=err">err</a> = <a href="ident?i=udp_add_offload">udp_add_offload</a>(&amp;<a href="ident?i=gs">gs</a>-&gt;udp_offloads);
<a name="L248" href="source/net/ipv4/geneve.c#L248">248</a>                 if (<a href="ident?i=err">err</a>)
<a name="L249" href="source/net/ipv4/geneve.c#L249">249</a>                         <a href="ident?i=pr_warn">pr_warn</a>(<i>"geneve: udp_add_offload failed with status %d\n"</i>,
<a name="L250" href="source/net/ipv4/geneve.c#L250">250</a>                                 <a href="ident?i=err">err</a>);
<a name="L251" href="source/net/ipv4/geneve.c#L251">251</a>         }
<a name="L252" href="source/net/ipv4/geneve.c#L252">252</a> }
<a name="L253" href="source/net/ipv4/geneve.c#L253">253</a> 
<a name="L254" href="source/net/ipv4/geneve.c#L254">254</a> static void <a href="ident?i=geneve_notify_del_rx_port">geneve_notify_del_rx_port</a>(struct <a href="ident?i=geneve_sock">geneve_sock</a> *<a href="ident?i=gs">gs</a>)
<a name="L255" href="source/net/ipv4/geneve.c#L255">255</a> {
<a name="L256" href="source/net/ipv4/geneve.c#L256">256</a>         struct <a href="ident?i=sock">sock</a> *sk = <a href="ident?i=gs">gs</a>-&gt;<a href="ident?i=sock">sock</a>-&gt;sk;
<a name="L257" href="source/net/ipv4/geneve.c#L257">257</a>         <a href="ident?i=sa_family_t">sa_family_t</a> sa_family = sk-&gt;<a href="ident?i=sk_family">sk_family</a>;
<a name="L258" href="source/net/ipv4/geneve.c#L258">258</a> 
<a name="L259" href="source/net/ipv4/geneve.c#L259">259</a>         if (sa_family == <a href="ident?i=AF_INET">AF_INET</a>)
<a name="L260" href="source/net/ipv4/geneve.c#L260">260</a>                 <a href="ident?i=udp_del_offload">udp_del_offload</a>(&amp;<a href="ident?i=gs">gs</a>-&gt;udp_offloads);
<a name="L261" href="source/net/ipv4/geneve.c#L261">261</a> }
<a name="L262" href="source/net/ipv4/geneve.c#L262">262</a> 
<a name="L263" href="source/net/ipv4/geneve.c#L263">263</a> <b><i>/* Callback from net/ipv4/udp.c to receive packets */</i></b>
<a name="L264" href="source/net/ipv4/geneve.c#L264">264</a> static int <a href="ident?i=geneve_udp_encap_recv">geneve_udp_encap_recv</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L265" href="source/net/ipv4/geneve.c#L265">265</a> {
<a name="L266" href="source/net/ipv4/geneve.c#L266">266</a>         struct <a href="ident?i=genevehdr">genevehdr</a> *geneveh;
<a name="L267" href="source/net/ipv4/geneve.c#L267">267</a>         struct <a href="ident?i=geneve_sock">geneve_sock</a> *<a href="ident?i=gs">gs</a>;
<a name="L268" href="source/net/ipv4/geneve.c#L268">268</a>         int opts_len;
<a name="L269" href="source/net/ipv4/geneve.c#L269">269</a> 
<a name="L270" href="source/net/ipv4/geneve.c#L270">270</a>         <b><i>/* Need Geneve and inner Ethernet header to be present */</i></b>
<a name="L271" href="source/net/ipv4/geneve.c#L271">271</a>         if (<a href="ident?i=unlikely">unlikely</a>(!<a href="ident?i=pskb_may_pull">pskb_may_pull</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=GENEVE_BASE_HLEN">GENEVE_BASE_HLEN</a>)))
<a name="L272" href="source/net/ipv4/geneve.c#L272">272</a>                 goto <a href="ident?i=error">error</a>;
<a name="L273" href="source/net/ipv4/geneve.c#L273">273</a> 
<a name="L274" href="source/net/ipv4/geneve.c#L274">274</a>         <b><i>/* Return packets with reserved bits set */</i></b>
<a name="L275" href="source/net/ipv4/geneve.c#L275">275</a>         geneveh = <a href="ident?i=geneve_hdr">geneve_hdr</a>(<a href="ident?i=skb">skb</a>);
<a name="L276" href="source/net/ipv4/geneve.c#L276">276</a> 
<a name="L277" href="source/net/ipv4/geneve.c#L277">277</a>         if (<a href="ident?i=unlikely">unlikely</a>(geneveh-&gt;ver != <a href="ident?i=GENEVE_VER">GENEVE_VER</a>))
<a name="L278" href="source/net/ipv4/geneve.c#L278">278</a>                 goto <a href="ident?i=error">error</a>;
<a name="L279" href="source/net/ipv4/geneve.c#L279">279</a> 
<a name="L280" href="source/net/ipv4/geneve.c#L280">280</a>         if (<a href="ident?i=unlikely">unlikely</a>(geneveh-&gt;<a href="ident?i=proto_type">proto_type</a> != <a href="ident?i=htons">htons</a>(<a href="ident?i=ETH_P_TEB">ETH_P_TEB</a>)))
<a name="L281" href="source/net/ipv4/geneve.c#L281">281</a>                 goto <a href="ident?i=error">error</a>;
<a name="L282" href="source/net/ipv4/geneve.c#L282">282</a> 
<a name="L283" href="source/net/ipv4/geneve.c#L283">283</a>         opts_len = geneveh-&gt;opt_len * 4;
<a name="L284" href="source/net/ipv4/geneve.c#L284">284</a>         if (<a href="ident?i=iptunnel_pull_header">iptunnel_pull_header</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=GENEVE_BASE_HLEN">GENEVE_BASE_HLEN</a> + opts_len,
<a name="L285" href="source/net/ipv4/geneve.c#L285">285</a>                                  <a href="ident?i=htons">htons</a>(<a href="ident?i=ETH_P_TEB">ETH_P_TEB</a>)))
<a name="L286" href="source/net/ipv4/geneve.c#L286">286</a>                 goto <a href="ident?i=drop">drop</a>;
<a name="L287" href="source/net/ipv4/geneve.c#L287">287</a> 
<a name="L288" href="source/net/ipv4/geneve.c#L288">288</a>         <a href="ident?i=gs">gs</a> = <a href="ident?i=rcu_dereference_sk_user_data">rcu_dereference_sk_user_data</a>(sk);
<a name="L289" href="source/net/ipv4/geneve.c#L289">289</a>         if (!<a href="ident?i=gs">gs</a>)
<a name="L290" href="source/net/ipv4/geneve.c#L290">290</a>                 goto <a href="ident?i=drop">drop</a>;
<a name="L291" href="source/net/ipv4/geneve.c#L291">291</a> 
<a name="L292" href="source/net/ipv4/geneve.c#L292">292</a>         <a href="ident?i=gs">gs</a>-&gt;rcv(<a href="ident?i=gs">gs</a>, <a href="ident?i=skb">skb</a>);
<a name="L293" href="source/net/ipv4/geneve.c#L293">293</a>         return 0;
<a name="L294" href="source/net/ipv4/geneve.c#L294">294</a> 
<a name="L295" href="source/net/ipv4/geneve.c#L295">295</a> <a href="ident?i=drop">drop</a>:
<a name="L296" href="source/net/ipv4/geneve.c#L296">296</a>         <b><i>/* Consume bad packet */</i></b>
<a name="L297" href="source/net/ipv4/geneve.c#L297">297</a>         <a href="ident?i=kfree_skb">kfree_skb</a>(<a href="ident?i=skb">skb</a>);
<a name="L298" href="source/net/ipv4/geneve.c#L298">298</a>         return 0;
<a name="L299" href="source/net/ipv4/geneve.c#L299">299</a> 
<a name="L300" href="source/net/ipv4/geneve.c#L300">300</a> <a href="ident?i=error">error</a>:
<a name="L301" href="source/net/ipv4/geneve.c#L301">301</a>         <b><i>/* Let the UDP layer deal with the skb */</i></b>
<a name="L302" href="source/net/ipv4/geneve.c#L302">302</a>         return 1;
<a name="L303" href="source/net/ipv4/geneve.c#L303">303</a> }
<a name="L304" href="source/net/ipv4/geneve.c#L304">304</a> 
<a name="L305" href="source/net/ipv4/geneve.c#L305">305</a> static struct <a href="ident?i=socket">socket</a> *<a href="ident?i=geneve_create_sock">geneve_create_sock</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>, <a href="ident?i=bool">bool</a> ipv6,
<a name="L306" href="source/net/ipv4/geneve.c#L306">306</a>                                          <a href="ident?i=__be16">__be16</a> <a href="ident?i=port">port</a>)
<a name="L307" href="source/net/ipv4/geneve.c#L307">307</a> {
<a name="L308" href="source/net/ipv4/geneve.c#L308">308</a>         struct <a href="ident?i=socket">socket</a> *<a href="ident?i=sock">sock</a>;
<a name="L309" href="source/net/ipv4/geneve.c#L309">309</a>         struct <a href="ident?i=udp_port_cfg">udp_port_cfg</a> udp_conf;
<a name="L310" href="source/net/ipv4/geneve.c#L310">310</a>         int <a href="ident?i=err">err</a>;
<a name="L311" href="source/net/ipv4/geneve.c#L311">311</a> 
<a name="L312" href="source/net/ipv4/geneve.c#L312">312</a>         <a href="ident?i=memset">memset</a>(&amp;udp_conf, 0, sizeof(udp_conf));
<a name="L313" href="source/net/ipv4/geneve.c#L313">313</a> 
<a name="L314" href="source/net/ipv4/geneve.c#L314">314</a>         if (ipv6) {
<a name="L315" href="source/net/ipv4/geneve.c#L315">315</a>                 udp_conf.<a href="ident?i=family">family</a> = <a href="ident?i=AF_INET6">AF_INET6</a>;
<a name="L316" href="source/net/ipv4/geneve.c#L316">316</a>         } else {
<a name="L317" href="source/net/ipv4/geneve.c#L317">317</a>                 udp_conf.<a href="ident?i=family">family</a> = <a href="ident?i=AF_INET">AF_INET</a>;
<a name="L318" href="source/net/ipv4/geneve.c#L318">318</a>                 udp_conf.local_ip.s_addr = <a href="ident?i=htonl">htonl</a>(<a href="ident?i=INADDR_ANY">INADDR_ANY</a>);
<a name="L319" href="source/net/ipv4/geneve.c#L319">319</a>         }
<a name="L320" href="source/net/ipv4/geneve.c#L320">320</a> 
<a name="L321" href="source/net/ipv4/geneve.c#L321">321</a>         udp_conf.local_udp_port = <a href="ident?i=port">port</a>;
<a name="L322" href="source/net/ipv4/geneve.c#L322">322</a> 
<a name="L323" href="source/net/ipv4/geneve.c#L323">323</a>         <b><i>/* Open UDP socket */</i></b>
<a name="L324" href="source/net/ipv4/geneve.c#L324">324</a>         <a href="ident?i=err">err</a> = <a href="ident?i=udp_sock_create">udp_sock_create</a>(<a href="ident?i=net">net</a>, &amp;udp_conf, &amp;<a href="ident?i=sock">sock</a>);
<a name="L325" href="source/net/ipv4/geneve.c#L325">325</a>         if (<a href="ident?i=err">err</a> &lt; 0)
<a name="L326" href="source/net/ipv4/geneve.c#L326">326</a>                 return <a href="ident?i=ERR_PTR">ERR_PTR</a>(<a href="ident?i=err">err</a>);
<a name="L327" href="source/net/ipv4/geneve.c#L327">327</a> 
<a name="L328" href="source/net/ipv4/geneve.c#L328">328</a>         return <a href="ident?i=sock">sock</a>;
<a name="L329" href="source/net/ipv4/geneve.c#L329">329</a> }
<a name="L330" href="source/net/ipv4/geneve.c#L330">330</a> 
<a name="L331" href="source/net/ipv4/geneve.c#L331">331</a> <b><i>/* Create new listen socket if needed */</i></b>
<a name="L332" href="source/net/ipv4/geneve.c#L332">332</a> static struct <a href="ident?i=geneve_sock">geneve_sock</a> *<a href="ident?i=geneve_socket_create">geneve_socket_create</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>, <a href="ident?i=__be16">__be16</a> <a href="ident?i=port">port</a>,
<a name="L333" href="source/net/ipv4/geneve.c#L333">333</a>                                                 <a href="ident?i=geneve_rcv_t">geneve_rcv_t</a> *rcv, void *<a href="ident?i=data">data</a>,
<a name="L334" href="source/net/ipv4/geneve.c#L334">334</a>                                                 <a href="ident?i=bool">bool</a> ipv6)
<a name="L335" href="source/net/ipv4/geneve.c#L335">335</a> {
<a name="L336" href="source/net/ipv4/geneve.c#L336">336</a>         struct <a href="ident?i=geneve_net">geneve_net</a> *gn = <a href="ident?i=net_generic">net_generic</a>(<a href="ident?i=net">net</a>, <a href="ident?i=geneve_net_id">geneve_net_id</a>);
<a name="L337" href="source/net/ipv4/geneve.c#L337">337</a>         struct <a href="ident?i=geneve_sock">geneve_sock</a> *<a href="ident?i=gs">gs</a>;
<a name="L338" href="source/net/ipv4/geneve.c#L338">338</a>         struct <a href="ident?i=socket">socket</a> *<a href="ident?i=sock">sock</a>;
<a name="L339" href="source/net/ipv4/geneve.c#L339">339</a>         struct <a href="ident?i=udp_tunnel_sock_cfg">udp_tunnel_sock_cfg</a> tunnel_cfg;
<a name="L340" href="source/net/ipv4/geneve.c#L340">340</a> 
<a name="L341" href="source/net/ipv4/geneve.c#L341">341</a>         <a href="ident?i=gs">gs</a> = <a href="ident?i=kzalloc">kzalloc</a>(sizeof(*<a href="ident?i=gs">gs</a>), <a href="ident?i=GFP_KERNEL">GFP_KERNEL</a>);
<a name="L342" href="source/net/ipv4/geneve.c#L342">342</a>         if (!<a href="ident?i=gs">gs</a>)
<a name="L343" href="source/net/ipv4/geneve.c#L343">343</a>                 return <a href="ident?i=ERR_PTR">ERR_PTR</a>(-<a href="ident?i=ENOMEM">ENOMEM</a>);
<a name="L344" href="source/net/ipv4/geneve.c#L344">344</a> 
<a name="L345" href="source/net/ipv4/geneve.c#L345">345</a>         <a href="ident?i=sock">sock</a> = <a href="ident?i=geneve_create_sock">geneve_create_sock</a>(<a href="ident?i=net">net</a>, ipv6, <a href="ident?i=port">port</a>);
<a name="L346" href="source/net/ipv4/geneve.c#L346">346</a>         if (<a href="ident?i=IS_ERR">IS_ERR</a>(<a href="ident?i=sock">sock</a>)) {
<a name="L347" href="source/net/ipv4/geneve.c#L347">347</a>                 <a href="ident?i=kfree">kfree</a>(<a href="ident?i=gs">gs</a>);
<a name="L348" href="source/net/ipv4/geneve.c#L348">348</a>                 return <a href="ident?i=ERR_CAST">ERR_CAST</a>(<a href="ident?i=sock">sock</a>);
<a name="L349" href="source/net/ipv4/geneve.c#L349">349</a>         }
<a name="L350" href="source/net/ipv4/geneve.c#L350">350</a> 
<a name="L351" href="source/net/ipv4/geneve.c#L351">351</a>         <a href="ident?i=gs">gs</a>-&gt;<a href="ident?i=sock">sock</a> = <a href="ident?i=sock">sock</a>;
<a name="L352" href="source/net/ipv4/geneve.c#L352">352</a>         <a href="ident?i=gs">gs</a>-&gt;refcnt = 1;
<a name="L353" href="source/net/ipv4/geneve.c#L353">353</a>         <a href="ident?i=gs">gs</a>-&gt;rcv = rcv;
<a name="L354" href="source/net/ipv4/geneve.c#L354">354</a>         <a href="ident?i=gs">gs</a>-&gt;rcv_data = <a href="ident?i=data">data</a>;
<a name="L355" href="source/net/ipv4/geneve.c#L355">355</a> 
<a name="L356" href="source/net/ipv4/geneve.c#L356">356</a>         <b><i>/* Initialize the geneve udp offloads structure */</i></b>
<a name="L357" href="source/net/ipv4/geneve.c#L357">357</a>         <a href="ident?i=gs">gs</a>-&gt;udp_offloads.<a href="ident?i=port">port</a> = <a href="ident?i=port">port</a>;
<a name="L358" href="source/net/ipv4/geneve.c#L358">358</a>         <a href="ident?i=gs">gs</a>-&gt;udp_offloads.<a href="ident?i=callbacks">callbacks</a>.gro_receive  = <a href="ident?i=geneve_gro_receive">geneve_gro_receive</a>;
<a name="L359" href="source/net/ipv4/geneve.c#L359">359</a>         <a href="ident?i=gs">gs</a>-&gt;udp_offloads.<a href="ident?i=callbacks">callbacks</a>.gro_complete = <a href="ident?i=geneve_gro_complete">geneve_gro_complete</a>;
<a name="L360" href="source/net/ipv4/geneve.c#L360">360</a>         <a href="ident?i=geneve_notify_add_rx_port">geneve_notify_add_rx_port</a>(<a href="ident?i=gs">gs</a>);
<a name="L361" href="source/net/ipv4/geneve.c#L361">361</a> 
<a name="L362" href="source/net/ipv4/geneve.c#L362">362</a>         <b><i>/* Mark socket as an encapsulation socket */</i></b>
<a name="L363" href="source/net/ipv4/geneve.c#L363">363</a>         tunnel_cfg.sk_user_data = <a href="ident?i=gs">gs</a>;
<a name="L364" href="source/net/ipv4/geneve.c#L364">364</a>         tunnel_cfg.encap_type = 1;
<a name="L365" href="source/net/ipv4/geneve.c#L365">365</a>         tunnel_cfg.encap_rcv = <a href="ident?i=geneve_udp_encap_recv">geneve_udp_encap_recv</a>;
<a name="L366" href="source/net/ipv4/geneve.c#L366">366</a>         tunnel_cfg.encap_destroy = <a href="ident?i=NULL">NULL</a>;
<a name="L367" href="source/net/ipv4/geneve.c#L367">367</a>         <a href="ident?i=setup_udp_tunnel_sock">setup_udp_tunnel_sock</a>(<a href="ident?i=net">net</a>, <a href="ident?i=sock">sock</a>, &amp;tunnel_cfg);
<a name="L368" href="source/net/ipv4/geneve.c#L368">368</a> 
<a name="L369" href="source/net/ipv4/geneve.c#L369">369</a>         <a href="ident?i=list_add">list_add</a>(&amp;<a href="ident?i=gs">gs</a>-&gt;<a href="ident?i=list">list</a>, &amp;gn-&gt;sock_list);
<a name="L370" href="source/net/ipv4/geneve.c#L370">370</a> 
<a name="L371" href="source/net/ipv4/geneve.c#L371">371</a>         return <a href="ident?i=gs">gs</a>;
<a name="L372" href="source/net/ipv4/geneve.c#L372">372</a> }
<a name="L373" href="source/net/ipv4/geneve.c#L373">373</a> 
<a name="L374" href="source/net/ipv4/geneve.c#L374">374</a> struct <a href="ident?i=geneve_sock">geneve_sock</a> *<a href="ident?i=geneve_sock_add">geneve_sock_add</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>, <a href="ident?i=__be16">__be16</a> <a href="ident?i=port">port</a>,
<a name="L375" href="source/net/ipv4/geneve.c#L375">375</a>                                     <a href="ident?i=geneve_rcv_t">geneve_rcv_t</a> *rcv, void *<a href="ident?i=data">data</a>,
<a name="L376" href="source/net/ipv4/geneve.c#L376">376</a>                                     <a href="ident?i=bool">bool</a> no_share, <a href="ident?i=bool">bool</a> ipv6)
<a name="L377" href="source/net/ipv4/geneve.c#L377">377</a> {
<a name="L378" href="source/net/ipv4/geneve.c#L378">378</a>         struct <a href="ident?i=geneve_sock">geneve_sock</a> *<a href="ident?i=gs">gs</a>;
<a name="L379" href="source/net/ipv4/geneve.c#L379">379</a> 
<a name="L380" href="source/net/ipv4/geneve.c#L380">380</a>         <a href="ident?i=mutex_lock">mutex_lock</a>(&amp;geneve_mutex);
<a name="L381" href="source/net/ipv4/geneve.c#L381">381</a> 
<a name="L382" href="source/net/ipv4/geneve.c#L382">382</a>         <a href="ident?i=gs">gs</a> = <a href="ident?i=geneve_find_sock">geneve_find_sock</a>(<a href="ident?i=net">net</a>, ipv6 ? <a href="ident?i=AF_INET6">AF_INET6</a> : <a href="ident?i=AF_INET">AF_INET</a>, <a href="ident?i=port">port</a>);
<a name="L383" href="source/net/ipv4/geneve.c#L383">383</a>         if (<a href="ident?i=gs">gs</a>) {
<a name="L384" href="source/net/ipv4/geneve.c#L384">384</a>                 if (!no_share &amp;&amp; <a href="ident?i=gs">gs</a>-&gt;rcv == rcv)
<a name="L385" href="source/net/ipv4/geneve.c#L385">385</a>                         <a href="ident?i=gs">gs</a>-&gt;refcnt++;
<a name="L386" href="source/net/ipv4/geneve.c#L386">386</a>                 else
<a name="L387" href="source/net/ipv4/geneve.c#L387">387</a>                         <a href="ident?i=gs">gs</a> = <a href="ident?i=ERR_PTR">ERR_PTR</a>(-<a href="ident?i=EBUSY">EBUSY</a>);
<a name="L388" href="source/net/ipv4/geneve.c#L388">388</a>         } else {
<a name="L389" href="source/net/ipv4/geneve.c#L389">389</a>                 <a href="ident?i=gs">gs</a> = <a href="ident?i=geneve_socket_create">geneve_socket_create</a>(<a href="ident?i=net">net</a>, <a href="ident?i=port">port</a>, rcv, <a href="ident?i=data">data</a>, ipv6);
<a name="L390" href="source/net/ipv4/geneve.c#L390">390</a>         }
<a name="L391" href="source/net/ipv4/geneve.c#L391">391</a> 
<a name="L392" href="source/net/ipv4/geneve.c#L392">392</a>         <a href="ident?i=mutex_unlock">mutex_unlock</a>(&amp;geneve_mutex);
<a name="L393" href="source/net/ipv4/geneve.c#L393">393</a> 
<a name="L394" href="source/net/ipv4/geneve.c#L394">394</a>         return <a href="ident?i=gs">gs</a>;
<a name="L395" href="source/net/ipv4/geneve.c#L395">395</a> }
<a name="L396" href="source/net/ipv4/geneve.c#L396">396</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=geneve_sock_add">geneve_sock_add</a>);
<a name="L397" href="source/net/ipv4/geneve.c#L397">397</a> 
<a name="L398" href="source/net/ipv4/geneve.c#L398">398</a> void <a href="ident?i=geneve_sock_release">geneve_sock_release</a>(struct <a href="ident?i=geneve_sock">geneve_sock</a> *<a href="ident?i=gs">gs</a>)
<a name="L399" href="source/net/ipv4/geneve.c#L399">399</a> {
<a name="L400" href="source/net/ipv4/geneve.c#L400">400</a>         <a href="ident?i=mutex_lock">mutex_lock</a>(&amp;geneve_mutex);
<a name="L401" href="source/net/ipv4/geneve.c#L401">401</a> 
<a name="L402" href="source/net/ipv4/geneve.c#L402">402</a>         if (--<a href="ident?i=gs">gs</a>-&gt;refcnt)
<a name="L403" href="source/net/ipv4/geneve.c#L403">403</a>                 goto unlock;
<a name="L404" href="source/net/ipv4/geneve.c#L404">404</a> 
<a name="L405" href="source/net/ipv4/geneve.c#L405">405</a>         <a href="ident?i=list_del">list_del</a>(&amp;<a href="ident?i=gs">gs</a>-&gt;<a href="ident?i=list">list</a>);
<a name="L406" href="source/net/ipv4/geneve.c#L406">406</a>         <a href="ident?i=geneve_notify_del_rx_port">geneve_notify_del_rx_port</a>(<a href="ident?i=gs">gs</a>);
<a name="L407" href="source/net/ipv4/geneve.c#L407">407</a>         <a href="ident?i=udp_tunnel_sock_release">udp_tunnel_sock_release</a>(<a href="ident?i=gs">gs</a>-&gt;<a href="ident?i=sock">sock</a>);
<a name="L408" href="source/net/ipv4/geneve.c#L408">408</a>         <a href="ident?i=kfree_rcu">kfree_rcu</a>(<a href="ident?i=gs">gs</a>, rcu);
<a name="L409" href="source/net/ipv4/geneve.c#L409">409</a> 
<a name="L410" href="source/net/ipv4/geneve.c#L410">410</a> unlock:
<a name="L411" href="source/net/ipv4/geneve.c#L411">411</a>         <a href="ident?i=mutex_unlock">mutex_unlock</a>(&amp;geneve_mutex);
<a name="L412" href="source/net/ipv4/geneve.c#L412">412</a> }
<a name="L413" href="source/net/ipv4/geneve.c#L413">413</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=geneve_sock_release">geneve_sock_release</a>);
<a name="L414" href="source/net/ipv4/geneve.c#L414">414</a> 
<a name="L415" href="source/net/ipv4/geneve.c#L415">415</a> static <a href="ident?i=__net_init">__net_init</a> int <a href="ident?i=geneve_init_net">geneve_init_net</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>)
<a name="L416" href="source/net/ipv4/geneve.c#L416">416</a> {
<a name="L417" href="source/net/ipv4/geneve.c#L417">417</a>         struct <a href="ident?i=geneve_net">geneve_net</a> *gn = <a href="ident?i=net_generic">net_generic</a>(<a href="ident?i=net">net</a>, <a href="ident?i=geneve_net_id">geneve_net_id</a>);
<a name="L418" href="source/net/ipv4/geneve.c#L418">418</a> 
<a name="L419" href="source/net/ipv4/geneve.c#L419">419</a>         <a href="ident?i=INIT_LIST_HEAD">INIT_LIST_HEAD</a>(&amp;gn-&gt;sock_list);
<a name="L420" href="source/net/ipv4/geneve.c#L420">420</a> 
<a name="L421" href="source/net/ipv4/geneve.c#L421">421</a>         return 0;
<a name="L422" href="source/net/ipv4/geneve.c#L422">422</a> }
<a name="L423" href="source/net/ipv4/geneve.c#L423">423</a> 
<a name="L424" href="source/net/ipv4/geneve.c#L424">424</a> static struct <a href="ident?i=pernet_operations">pernet_operations</a> <a href="ident?i=geneve_net_ops">geneve_net_ops</a> = {
<a name="L425" href="source/net/ipv4/geneve.c#L425">425</a>         .<a href="ident?i=init">init</a> = <a href="ident?i=geneve_init_net">geneve_init_net</a>,
<a name="L426" href="source/net/ipv4/geneve.c#L426">426</a>         .<a href="ident?i=id">id</a>   = &amp;<a href="ident?i=geneve_net_id">geneve_net_id</a>,
<a name="L427" href="source/net/ipv4/geneve.c#L427">427</a>         .<a href="ident?i=size">size</a> = sizeof(struct <a href="ident?i=geneve_net">geneve_net</a>),
<a name="L428" href="source/net/ipv4/geneve.c#L428">428</a> };
<a name="L429" href="source/net/ipv4/geneve.c#L429">429</a> 
<a name="L430" href="source/net/ipv4/geneve.c#L430">430</a> static int <a href="ident?i=__init">__init</a> <a href="ident?i=geneve_init_module">geneve_init_module</a>(void)
<a name="L431" href="source/net/ipv4/geneve.c#L431">431</a> {
<a name="L432" href="source/net/ipv4/geneve.c#L432">432</a>         int <a href="ident?i=rc">rc</a>;
<a name="L433" href="source/net/ipv4/geneve.c#L433">433</a> 
<a name="L434" href="source/net/ipv4/geneve.c#L434">434</a>         <a href="ident?i=rc">rc</a> = <a href="ident?i=register_pernet_subsys">register_pernet_subsys</a>(&amp;<a href="ident?i=geneve_net_ops">geneve_net_ops</a>);
<a name="L435" href="source/net/ipv4/geneve.c#L435">435</a>         if (<a href="ident?i=rc">rc</a>)
<a name="L436" href="source/net/ipv4/geneve.c#L436">436</a>                 return <a href="ident?i=rc">rc</a>;
<a name="L437" href="source/net/ipv4/geneve.c#L437">437</a> 
<a name="L438" href="source/net/ipv4/geneve.c#L438">438</a>         <a href="ident?i=pr_info">pr_info</a>(<i>"Geneve driver\n"</i>);
<a name="L439" href="source/net/ipv4/geneve.c#L439">439</a> 
<a name="L440" href="source/net/ipv4/geneve.c#L440">440</a>         return 0;
<a name="L441" href="source/net/ipv4/geneve.c#L441">441</a> }
<a name="L442" href="source/net/ipv4/geneve.c#L442">442</a> <a href="ident?i=module_init">module_init</a>(<a href="ident?i=geneve_init_module">geneve_init_module</a>);
<a name="L443" href="source/net/ipv4/geneve.c#L443">443</a> 
<a name="L444" href="source/net/ipv4/geneve.c#L444">444</a> static void <a href="ident?i=__exit">__exit</a> <a href="ident?i=geneve_cleanup_module">geneve_cleanup_module</a>(void)
<a name="L445" href="source/net/ipv4/geneve.c#L445">445</a> {
<a name="L446" href="source/net/ipv4/geneve.c#L446">446</a>         <a href="ident?i=unregister_pernet_subsys">unregister_pernet_subsys</a>(&amp;<a href="ident?i=geneve_net_ops">geneve_net_ops</a>);
<a name="L447" href="source/net/ipv4/geneve.c#L447">447</a> }
<a name="L448" href="source/net/ipv4/geneve.c#L448">448</a> <a href="ident?i=module_exit">module_exit</a>(<a href="ident?i=geneve_cleanup_module">geneve_cleanup_module</a>);
<a name="L449" href="source/net/ipv4/geneve.c#L449">449</a> 
<a name="L450" href="source/net/ipv4/geneve.c#L450">450</a> <a href="ident?i=MODULE_LICENSE">MODULE_LICENSE</a>(<i>"GPL"</i>);
<a name="L451" href="source/net/ipv4/geneve.c#L451">451</a> <a href="ident?i=MODULE_AUTHOR">MODULE_AUTHOR</a>(<i>"Jesse Gross &lt;jesse@nicira.com&gt;"</i>);
<a name="L452" href="source/net/ipv4/geneve.c#L452">452</a> <a href="ident?i=MODULE_DESCRIPTION">MODULE_DESCRIPTION</a>(<i>"Driver for GENEVE encapsulated traffic"</i>);
<a name="L453" href="source/net/ipv4/geneve.c#L453">453</a> <a href="ident?i=MODULE_ALIAS_RTNL_LINK">MODULE_ALIAS_RTNL_LINK</a>(<i>"geneve"</i>);
<a name="L454" href="source/net/ipv4/geneve.c#L454">454</a> </pre></div><p>
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
