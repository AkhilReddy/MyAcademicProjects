<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title>Linux/net/ipv4/arp.c - Linux Cross Reference - Free Electrons</title>
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
		 &nbsp;&bull;&nbsp;<b><i>source navigation</i></b> &nbsp;&bull;&nbsp;<a href="diff/net/ipv4/arp.c">diff markup</a> &nbsp;&bull;&nbsp;<a href="ident">identifier search</a> &nbsp;&bull;&nbsp;<a href="search">freetext search</a> &nbsp;&bull;&nbsp;
		</p>
	</div>
</div>

<div id="topbar">
  
  <p>Version: &nbsp;<a href="source/net/ipv4/arp.c?v=2.0.40">2.0.40</a>&nbsp;<a href="source/net/ipv4/arp.c?v=2.2.26">2.2.26</a>&nbsp;<a href="source/net/ipv4/arp.c?v=2.4.37">2.4.37</a>&nbsp;<a href="source/net/ipv4/arp.c?v=3.5">3.5</a>&nbsp;<a href="source/net/ipv4/arp.c?v=3.6">3.6</a>&nbsp;<a href="source/net/ipv4/arp.c?v=3.7">3.7</a>&nbsp;<a href="source/net/ipv4/arp.c?v=3.8">3.8</a>&nbsp;<a href="source/net/ipv4/arp.c?v=3.9">3.9</a>&nbsp;<a href="source/net/ipv4/arp.c?v=3.10">3.10</a>&nbsp;<a href="source/net/ipv4/arp.c?v=3.11">3.11</a>&nbsp;<a href="source/net/ipv4/arp.c?v=3.12">3.12</a>&nbsp;<a href="source/net/ipv4/arp.c?v=3.13">3.13</a>&nbsp;<a href="source/net/ipv4/arp.c?v=3.14">3.14</a>&nbsp;<a href="source/net/ipv4/arp.c?v=3.15">3.15</a>&nbsp;<a href="source/net/ipv4/arp.c?v=3.16">3.16</a>&nbsp;<a href="source/net/ipv4/arp.c?v=3.17">3.17</a>&nbsp;<a href="source/net/ipv4/arp.c?v=3.18">3.18</a>&nbsp;<a href="source/net/ipv4/arp.c?v=3.19">3.19</a>&nbsp;<a href="source/net/ipv4/arp.c?v=4.0">4.0</a>&nbsp;<b><i>4.1</i></b></p>
  
</div>

<h1><a href="source/">Linux</a>/<a href="source/net/">net</a>/<a href="source/net/ipv4/">ipv4</a>/<a href="source/net/ipv4/arp.c">arp.c</a></h1>
<div id="lxrcode"><pre>  <a name="L1" href="source/net/ipv4/arp.c#L1">1</a> <b><i>/* linux/net/ipv4/arp.c</i></b>
  <a name="L2" href="source/net/ipv4/arp.c#L2">2</a> <b><i> *</i></b>
  <a name="L3" href="source/net/ipv4/arp.c#L3">3</a> <b><i> * Copyright (C) 1994 by Florian  La Roche</i></b>
  <a name="L4" href="source/net/ipv4/arp.c#L4">4</a> <b><i> *</i></b>
  <a name="L5" href="source/net/ipv4/arp.c#L5">5</a> <b><i> * This module implements the Address Resolution Protocol ARP (RFC 826),</i></b>
  <a name="L6" href="source/net/ipv4/arp.c#L6">6</a> <b><i> * which is used to convert IP addresses (or in the future maybe other</i></b>
  <a name="L7" href="source/net/ipv4/arp.c#L7">7</a> <b><i> * high-level addresses) into a low-level hardware address (like an Ethernet</i></b>
  <a name="L8" href="source/net/ipv4/arp.c#L8">8</a> <b><i> * address).</i></b>
  <a name="L9" href="source/net/ipv4/arp.c#L9">9</a> <b><i> *</i></b>
 <a name="L10" href="source/net/ipv4/arp.c#L10">10</a> <b><i> * This program is free software; you can redistribute it and/or</i></b>
 <a name="L11" href="source/net/ipv4/arp.c#L11">11</a> <b><i> * modify it under the terms of the GNU General Public License</i></b>
 <a name="L12" href="source/net/ipv4/arp.c#L12">12</a> <b><i> * as published by the Free Software Foundation; either version</i></b>
 <a name="L13" href="source/net/ipv4/arp.c#L13">13</a> <b><i> * 2 of the License, or (at your option) any later version.</i></b>
 <a name="L14" href="source/net/ipv4/arp.c#L14">14</a> <b><i> *</i></b>
 <a name="L15" href="source/net/ipv4/arp.c#L15">15</a> <b><i> * Fixes:</i></b>
 <a name="L16" href="source/net/ipv4/arp.c#L16">16</a> <b><i> *              Alan Cox        :       Removed the Ethernet assumptions in</i></b>
 <a name="L17" href="source/net/ipv4/arp.c#L17">17</a> <b><i> *                                      Florian's code</i></b>
 <a name="L18" href="source/net/ipv4/arp.c#L18">18</a> <b><i> *              Alan Cox        :       Fixed some small errors in the ARP</i></b>
 <a name="L19" href="source/net/ipv4/arp.c#L19">19</a> <b><i> *                                      logic</i></b>
 <a name="L20" href="source/net/ipv4/arp.c#L20">20</a> <b><i> *              Alan Cox        :       Allow &gt;4K in /proc</i></b>
 <a name="L21" href="source/net/ipv4/arp.c#L21">21</a> <b><i> *              Alan Cox        :       Make ARP add its own protocol entry</i></b>
 <a name="L22" href="source/net/ipv4/arp.c#L22">22</a> <b><i> *              Ross Martin     :       Rewrote arp_rcv() and arp_get_info()</i></b>
 <a name="L23" href="source/net/ipv4/arp.c#L23">23</a> <b><i> *              Stephen Henson  :       Add AX25 support to arp_get_info()</i></b>
 <a name="L24" href="source/net/ipv4/arp.c#L24">24</a> <b><i> *              Alan Cox        :       Drop data when a device is downed.</i></b>
 <a name="L25" href="source/net/ipv4/arp.c#L25">25</a> <b><i> *              Alan Cox        :       Use init_timer().</i></b>
 <a name="L26" href="source/net/ipv4/arp.c#L26">26</a> <b><i> *              Alan Cox        :       Double lock fixes.</i></b>
 <a name="L27" href="source/net/ipv4/arp.c#L27">27</a> <b><i> *              Martin Seine    :       Move the arphdr structure</i></b>
 <a name="L28" href="source/net/ipv4/arp.c#L28">28</a> <b><i> *                                      to if_arp.h for compatibility.</i></b>
 <a name="L29" href="source/net/ipv4/arp.c#L29">29</a> <b><i> *                                      with BSD based programs.</i></b>
 <a name="L30" href="source/net/ipv4/arp.c#L30">30</a> <b><i> *              Andrew Tridgell :       Added ARP netmask code and</i></b>
 <a name="L31" href="source/net/ipv4/arp.c#L31">31</a> <b><i> *                                      re-arranged proxy handling.</i></b>
 <a name="L32" href="source/net/ipv4/arp.c#L32">32</a> <b><i> *              Alan Cox        :       Changed to use notifiers.</i></b>
 <a name="L33" href="source/net/ipv4/arp.c#L33">33</a> <b><i> *              Niibe Yutaka    :       Reply for this device or proxies only.</i></b>
 <a name="L34" href="source/net/ipv4/arp.c#L34">34</a> <b><i> *              Alan Cox        :       Don't proxy across hardware types!</i></b>
 <a name="L35" href="source/net/ipv4/arp.c#L35">35</a> <b><i> *              Jonathan Naylor :       Added support for NET/ROM.</i></b>
 <a name="L36" href="source/net/ipv4/arp.c#L36">36</a> <b><i> *              Mike Shaver     :       RFC1122 checks.</i></b>
 <a name="L37" href="source/net/ipv4/arp.c#L37">37</a> <b><i> *              Jonathan Naylor :       Only lookup the hardware address for</i></b>
 <a name="L38" href="source/net/ipv4/arp.c#L38">38</a> <b><i> *                                      the correct hardware type.</i></b>
 <a name="L39" href="source/net/ipv4/arp.c#L39">39</a> <b><i> *              Germano Caronni :       Assorted subtle races.</i></b>
 <a name="L40" href="source/net/ipv4/arp.c#L40">40</a> <b><i> *              Craig Schlenter :       Don't modify permanent entry</i></b>
 <a name="L41" href="source/net/ipv4/arp.c#L41">41</a> <b><i> *                                      during arp_rcv.</i></b>
 <a name="L42" href="source/net/ipv4/arp.c#L42">42</a> <b><i> *              Russ Nelson     :       Tidied up a few bits.</i></b>
 <a name="L43" href="source/net/ipv4/arp.c#L43">43</a> <b><i> *              Alexey Kuznetsov:       Major changes to caching and behaviour,</i></b>
 <a name="L44" href="source/net/ipv4/arp.c#L44">44</a> <b><i> *                                      eg intelligent arp probing and</i></b>
 <a name="L45" href="source/net/ipv4/arp.c#L45">45</a> <b><i> *                                      generation</i></b>
 <a name="L46" href="source/net/ipv4/arp.c#L46">46</a> <b><i> *                                      of host down events.</i></b>
 <a name="L47" href="source/net/ipv4/arp.c#L47">47</a> <b><i> *              Alan Cox        :       Missing unlock in device events.</i></b>
 <a name="L48" href="source/net/ipv4/arp.c#L48">48</a> <b><i> *              Eckes           :       ARP ioctl control errors.</i></b>
 <a name="L49" href="source/net/ipv4/arp.c#L49">49</a> <b><i> *              Alexey Kuznetsov:       Arp free fix.</i></b>
 <a name="L50" href="source/net/ipv4/arp.c#L50">50</a> <b><i> *              Manuel Rodriguez:       Gratuitous ARP.</i></b>
 <a name="L51" href="source/net/ipv4/arp.c#L51">51</a> <b><i> *              Jonathan Layes  :       Added arpd support through kerneld</i></b>
 <a name="L52" href="source/net/ipv4/arp.c#L52">52</a> <b><i> *                                      message queue (960314)</i></b>
 <a name="L53" href="source/net/ipv4/arp.c#L53">53</a> <b><i> *              Mike Shaver     :       /proc/sys/net/ipv4/arp_* support</i></b>
 <a name="L54" href="source/net/ipv4/arp.c#L54">54</a> <b><i> *              Mike McLagan    :       Routing by source</i></b>
 <a name="L55" href="source/net/ipv4/arp.c#L55">55</a> <b><i> *              Stuart Cheshire :       Metricom and grat arp fixes</i></b>
 <a name="L56" href="source/net/ipv4/arp.c#L56">56</a> <b><i> *                                      *** FOR 2.1 clean this up ***</i></b>
 <a name="L57" href="source/net/ipv4/arp.c#L57">57</a> <b><i> *              Lawrence V. Stefani: (08/12/96) Added FDDI support.</i></b>
 <a name="L58" href="source/net/ipv4/arp.c#L58">58</a> <b><i> *              Alan Cox        :       Took the AP1000 nasty FDDI hack and</i></b>
 <a name="L59" href="source/net/ipv4/arp.c#L59">59</a> <b><i> *                                      folded into the mainstream FDDI code.</i></b>
 <a name="L60" href="source/net/ipv4/arp.c#L60">60</a> <b><i> *                                      Ack spit, Linus how did you allow that</i></b>
 <a name="L61" href="source/net/ipv4/arp.c#L61">61</a> <b><i> *                                      one in...</i></b>
 <a name="L62" href="source/net/ipv4/arp.c#L62">62</a> <b><i> *              Jes Sorensen    :       Make FDDI work again in 2.1.x and</i></b>
 <a name="L63" href="source/net/ipv4/arp.c#L63">63</a> <b><i> *                                      clean up the APFDDI &amp; gen. FDDI bits.</i></b>
 <a name="L64" href="source/net/ipv4/arp.c#L64">64</a> <b><i> *              Alexey Kuznetsov:       new arp state machine;</i></b>
 <a name="L65" href="source/net/ipv4/arp.c#L65">65</a> <b><i> *                                      now it is in net/core/neighbour.c.</i></b>
 <a name="L66" href="source/net/ipv4/arp.c#L66">66</a> <b><i> *              Krzysztof Halasa:       Added Frame Relay ARP support.</i></b>
 <a name="L67" href="source/net/ipv4/arp.c#L67">67</a> <b><i> *              Arnaldo C. Melo :       convert /proc/net/arp to seq_file</i></b>
 <a name="L68" href="source/net/ipv4/arp.c#L68">68</a> <b><i> *              Shmulik Hen:            Split arp_send to arp_create and</i></b>
 <a name="L69" href="source/net/ipv4/arp.c#L69">69</a> <b><i> *                                      arp_xmit so intermediate drivers like</i></b>
 <a name="L70" href="source/net/ipv4/arp.c#L70">70</a> <b><i> *                                      bonding can change the skb before</i></b>
 <a name="L71" href="source/net/ipv4/arp.c#L71">71</a> <b><i> *                                      sending (e.g. insert 8021q tag).</i></b>
 <a name="L72" href="source/net/ipv4/arp.c#L72">72</a> <b><i> *              Harald Welte    :       convert to make use of jenkins hash</i></b>
 <a name="L73" href="source/net/ipv4/arp.c#L73">73</a> <b><i> *              Jesper D. Brouer:       Proxy ARP PVLAN RFC 3069 support.</i></b>
 <a name="L74" href="source/net/ipv4/arp.c#L74">74</a> <b><i> */</i></b>
 <a name="L75" href="source/net/ipv4/arp.c#L75">75</a> 
 <a name="L76" href="source/net/ipv4/arp.c#L76">76</a> #define <a href="ident?i=pr_fmt">pr_fmt</a>(<a href="ident?i=fmt">fmt</a>) KBUILD_MODNAME <i>": "</i> <a href="ident?i=fmt">fmt</a>
 <a name="L77" href="source/net/ipv4/arp.c#L77">77</a> 
 <a name="L78" href="source/net/ipv4/arp.c#L78">78</a> #include &lt;linux/module.h&gt;
 <a name="L79" href="source/net/ipv4/arp.c#L79">79</a> #include &lt;linux/types.h&gt;
 <a name="L80" href="source/net/ipv4/arp.c#L80">80</a> #include &lt;linux/string.h&gt;
 <a name="L81" href="source/net/ipv4/arp.c#L81">81</a> #include &lt;linux/kernel.h&gt;
 <a name="L82" href="source/net/ipv4/arp.c#L82">82</a> #include &lt;linux/capability.h&gt;
 <a name="L83" href="source/net/ipv4/arp.c#L83">83</a> #include &lt;linux/socket.h&gt;
 <a name="L84" href="source/net/ipv4/arp.c#L84">84</a> #include &lt;linux/sockios.h&gt;
 <a name="L85" href="source/net/ipv4/arp.c#L85">85</a> #include &lt;linux/errno.h&gt;
 <a name="L86" href="source/net/ipv4/arp.c#L86">86</a> #include &lt;linux/in.h&gt;
 <a name="L87" href="source/net/ipv4/arp.c#L87">87</a> #include &lt;linux/mm.h&gt;
 <a name="L88" href="source/net/ipv4/arp.c#L88">88</a> #include &lt;linux/inet.h&gt;
 <a name="L89" href="source/net/ipv4/arp.c#L89">89</a> #include &lt;linux/inetdevice.h&gt;
 <a name="L90" href="source/net/ipv4/arp.c#L90">90</a> #include &lt;linux/netdevice.h&gt;
 <a name="L91" href="source/net/ipv4/arp.c#L91">91</a> #include &lt;linux/etherdevice.h&gt;
 <a name="L92" href="source/net/ipv4/arp.c#L92">92</a> #include &lt;linux/fddidevice.h&gt;
 <a name="L93" href="source/net/ipv4/arp.c#L93">93</a> #include &lt;linux/if_arp.h&gt;
 <a name="L94" href="source/net/ipv4/arp.c#L94">94</a> #include &lt;linux/skbuff.h&gt;
 <a name="L95" href="source/net/ipv4/arp.c#L95">95</a> #include &lt;linux/proc_fs.h&gt;
 <a name="L96" href="source/net/ipv4/arp.c#L96">96</a> #include &lt;linux/seq_file.h&gt;
 <a name="L97" href="source/net/ipv4/arp.c#L97">97</a> #include &lt;linux/stat.h&gt;
 <a name="L98" href="source/net/ipv4/arp.c#L98">98</a> #include &lt;linux/init.h&gt;
 <a name="L99" href="source/net/ipv4/arp.c#L99">99</a> #include &lt;linux/net.h&gt;
<a name="L100" href="source/net/ipv4/arp.c#L100">100</a> #include &lt;linux/rcupdate.h&gt;
<a name="L101" href="source/net/ipv4/arp.c#L101">101</a> #include &lt;linux/slab.h&gt;
<a name="L102" href="source/net/ipv4/arp.c#L102">102</a> #ifdef CONFIG_SYSCTL
<a name="L103" href="source/net/ipv4/arp.c#L103">103</a> #include &lt;linux/sysctl.h&gt;
<a name="L104" href="source/net/ipv4/arp.c#L104">104</a> #endif
<a name="L105" href="source/net/ipv4/arp.c#L105">105</a> 
<a name="L106" href="source/net/ipv4/arp.c#L106">106</a> #include &lt;net/net_namespace.h&gt;
<a name="L107" href="source/net/ipv4/arp.c#L107">107</a> #include &lt;net/ip.h&gt;
<a name="L108" href="source/net/ipv4/arp.c#L108">108</a> #include &lt;net/icmp.h&gt;
<a name="L109" href="source/net/ipv4/arp.c#L109">109</a> #include &lt;net/route.h&gt;
<a name="L110" href="source/net/ipv4/arp.c#L110">110</a> #include &lt;net/protocol.h&gt;
<a name="L111" href="source/net/ipv4/arp.c#L111">111</a> #include &lt;net/tcp.h&gt;
<a name="L112" href="source/net/ipv4/arp.c#L112">112</a> #include &lt;net/sock.h&gt;
<a name="L113" href="source/net/ipv4/arp.c#L113">113</a> #include &lt;net/arp.h&gt;
<a name="L114" href="source/net/ipv4/arp.c#L114">114</a> #include &lt;net/ax25.h&gt;
<a name="L115" href="source/net/ipv4/arp.c#L115">115</a> #include &lt;net/netrom.h&gt;
<a name="L116" href="source/net/ipv4/arp.c#L116">116</a> 
<a name="L117" href="source/net/ipv4/arp.c#L117">117</a> #include &lt;linux/uaccess.h&gt;
<a name="L118" href="source/net/ipv4/arp.c#L118">118</a> 
<a name="L119" href="source/net/ipv4/arp.c#L119">119</a> #include &lt;linux/netfilter_arp.h&gt;
<a name="L120" href="source/net/ipv4/arp.c#L120">120</a> 
<a name="L121" href="source/net/ipv4/arp.c#L121">121</a> <b><i>/*</i></b>
<a name="L122" href="source/net/ipv4/arp.c#L122">122</a> <b><i> *      Interface to generic neighbour cache.</i></b>
<a name="L123" href="source/net/ipv4/arp.c#L123">123</a> <b><i> */</i></b>
<a name="L124" href="source/net/ipv4/arp.c#L124">124</a> static <a href="ident?i=u32">u32</a> <a href="ident?i=arp_hash">arp_hash</a>(const void *pkey, const struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>, <a href="ident?i=__u32">__u32</a> *hash_rnd);
<a name="L125" href="source/net/ipv4/arp.c#L125">125</a> static <a href="ident?i=bool">bool</a> <a href="ident?i=arp_key_eq">arp_key_eq</a>(const struct <a href="ident?i=neighbour">neighbour</a> *<a href="ident?i=n">n</a>, const void *pkey);
<a name="L126" href="source/net/ipv4/arp.c#L126">126</a> static int <a href="ident?i=arp_constructor">arp_constructor</a>(struct <a href="ident?i=neighbour">neighbour</a> *neigh);
<a name="L127" href="source/net/ipv4/arp.c#L127">127</a> static void <a href="ident?i=arp_solicit">arp_solicit</a>(struct <a href="ident?i=neighbour">neighbour</a> *neigh, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>);
<a name="L128" href="source/net/ipv4/arp.c#L128">128</a> static void <a href="ident?i=arp_error_report">arp_error_report</a>(struct <a href="ident?i=neighbour">neighbour</a> *neigh, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>);
<a name="L129" href="source/net/ipv4/arp.c#L129">129</a> static void <a href="ident?i=parp_redo">parp_redo</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>);
<a name="L130" href="source/net/ipv4/arp.c#L130">130</a> 
<a name="L131" href="source/net/ipv4/arp.c#L131">131</a> static const struct <a href="ident?i=neigh_ops">neigh_ops</a> <a href="ident?i=arp_generic_ops">arp_generic_ops</a> = {
<a name="L132" href="source/net/ipv4/arp.c#L132">132</a>         .<a href="ident?i=family">family</a> =               <a href="ident?i=AF_INET">AF_INET</a>,
<a name="L133" href="source/net/ipv4/arp.c#L133">133</a>         .solicit =              <a href="ident?i=arp_solicit">arp_solicit</a>,
<a name="L134" href="source/net/ipv4/arp.c#L134">134</a>         .<a href="ident?i=error_report">error_report</a> =         <a href="ident?i=arp_error_report">arp_error_report</a>,
<a name="L135" href="source/net/ipv4/arp.c#L135">135</a>         .<a href="ident?i=output">output</a> =               <a href="ident?i=neigh_resolve_output">neigh_resolve_output</a>,
<a name="L136" href="source/net/ipv4/arp.c#L136">136</a>         .connected_output =     <a href="ident?i=neigh_connected_output">neigh_connected_output</a>,
<a name="L137" href="source/net/ipv4/arp.c#L137">137</a> };
<a name="L138" href="source/net/ipv4/arp.c#L138">138</a> 
<a name="L139" href="source/net/ipv4/arp.c#L139">139</a> static const struct <a href="ident?i=neigh_ops">neigh_ops</a> <a href="ident?i=arp_hh_ops">arp_hh_ops</a> = {
<a name="L140" href="source/net/ipv4/arp.c#L140">140</a>         .<a href="ident?i=family">family</a> =               <a href="ident?i=AF_INET">AF_INET</a>,
<a name="L141" href="source/net/ipv4/arp.c#L141">141</a>         .solicit =              <a href="ident?i=arp_solicit">arp_solicit</a>,
<a name="L142" href="source/net/ipv4/arp.c#L142">142</a>         .<a href="ident?i=error_report">error_report</a> =         <a href="ident?i=arp_error_report">arp_error_report</a>,
<a name="L143" href="source/net/ipv4/arp.c#L143">143</a>         .<a href="ident?i=output">output</a> =               <a href="ident?i=neigh_resolve_output">neigh_resolve_output</a>,
<a name="L144" href="source/net/ipv4/arp.c#L144">144</a>         .connected_output =     <a href="ident?i=neigh_resolve_output">neigh_resolve_output</a>,
<a name="L145" href="source/net/ipv4/arp.c#L145">145</a> };
<a name="L146" href="source/net/ipv4/arp.c#L146">146</a> 
<a name="L147" href="source/net/ipv4/arp.c#L147">147</a> static const struct <a href="ident?i=neigh_ops">neigh_ops</a> <a href="ident?i=arp_direct_ops">arp_direct_ops</a> = {
<a name="L148" href="source/net/ipv4/arp.c#L148">148</a>         .<a href="ident?i=family">family</a> =               <a href="ident?i=AF_INET">AF_INET</a>,
<a name="L149" href="source/net/ipv4/arp.c#L149">149</a>         .<a href="ident?i=output">output</a> =               <a href="ident?i=neigh_direct_output">neigh_direct_output</a>,
<a name="L150" href="source/net/ipv4/arp.c#L150">150</a>         .connected_output =     <a href="ident?i=neigh_direct_output">neigh_direct_output</a>,
<a name="L151" href="source/net/ipv4/arp.c#L151">151</a> };
<a name="L152" href="source/net/ipv4/arp.c#L152">152</a> 
<a name="L153" href="source/net/ipv4/arp.c#L153">153</a> struct <a href="ident?i=neigh_table">neigh_table</a> <a href="ident?i=arp_tbl">arp_tbl</a> = {
<a name="L154" href="source/net/ipv4/arp.c#L154">154</a>         .<a href="ident?i=family">family</a>         = <a href="ident?i=AF_INET">AF_INET</a>,
<a name="L155" href="source/net/ipv4/arp.c#L155">155</a>         .<a href="ident?i=key_len">key_len</a>        = 4,
<a name="L156" href="source/net/ipv4/arp.c#L156">156</a>         .<a href="ident?i=protocol">protocol</a>       = <a href="ident?i=cpu_to_be16">cpu_to_be16</a>(<a href="ident?i=ETH_P_IP">ETH_P_IP</a>),
<a name="L157" href="source/net/ipv4/arp.c#L157">157</a>         .<a href="ident?i=hash">hash</a>           = <a href="ident?i=arp_hash">arp_hash</a>,
<a name="L158" href="source/net/ipv4/arp.c#L158">158</a>         .key_eq         = <a href="ident?i=arp_key_eq">arp_key_eq</a>,
<a name="L159" href="source/net/ipv4/arp.c#L159">159</a>         .constructor    = <a href="ident?i=arp_constructor">arp_constructor</a>,
<a name="L160" href="source/net/ipv4/arp.c#L160">160</a>         .proxy_redo     = <a href="ident?i=parp_redo">parp_redo</a>,
<a name="L161" href="source/net/ipv4/arp.c#L161">161</a>         .<a href="ident?i=id">id</a>             = <i>"arp_cache"</i>,
<a name="L162" href="source/net/ipv4/arp.c#L162">162</a>         .<a href="ident?i=parms">parms</a>          = {
<a name="L163" href="source/net/ipv4/arp.c#L163">163</a>                 .tbl                    = &amp;<a href="ident?i=arp_tbl">arp_tbl</a>,
<a name="L164" href="source/net/ipv4/arp.c#L164">164</a>                 .reachable_time         = 30 * <a href="ident?i=HZ">HZ</a>,
<a name="L165" href="source/net/ipv4/arp.c#L165">165</a>                 .<a href="ident?i=data">data</a>   = {
<a name="L166" href="source/net/ipv4/arp.c#L166">166</a>                         [NEIGH_VAR_MCAST_PROBES] = 3,
<a name="L167" href="source/net/ipv4/arp.c#L167">167</a>                         [NEIGH_VAR_UCAST_PROBES] = 3,
<a name="L168" href="source/net/ipv4/arp.c#L168">168</a>                         [NEIGH_VAR_RETRANS_TIME] = 1 * <a href="ident?i=HZ">HZ</a>,
<a name="L169" href="source/net/ipv4/arp.c#L169">169</a>                         [NEIGH_VAR_BASE_REACHABLE_TIME] = 30 * <a href="ident?i=HZ">HZ</a>,
<a name="L170" href="source/net/ipv4/arp.c#L170">170</a>                         [NEIGH_VAR_DELAY_PROBE_TIME] = 5 * <a href="ident?i=HZ">HZ</a>,
<a name="L171" href="source/net/ipv4/arp.c#L171">171</a>                         [NEIGH_VAR_GC_STALETIME] = 60 * <a href="ident?i=HZ">HZ</a>,
<a name="L172" href="source/net/ipv4/arp.c#L172">172</a>                         [NEIGH_VAR_QUEUE_LEN_BYTES] = 64 * 1024,
<a name="L173" href="source/net/ipv4/arp.c#L173">173</a>                         [NEIGH_VAR_PROXY_QLEN] = 64,
<a name="L174" href="source/net/ipv4/arp.c#L174">174</a>                         [NEIGH_VAR_ANYCAST_DELAY] = 1 * <a href="ident?i=HZ">HZ</a>,
<a name="L175" href="source/net/ipv4/arp.c#L175">175</a>                         [NEIGH_VAR_PROXY_DELAY] = (8 * <a href="ident?i=HZ">HZ</a>) / 10,
<a name="L176" href="source/net/ipv4/arp.c#L176">176</a>                         [NEIGH_VAR_LOCKTIME] = 1 * <a href="ident?i=HZ">HZ</a>,
<a name="L177" href="source/net/ipv4/arp.c#L177">177</a>                 },
<a name="L178" href="source/net/ipv4/arp.c#L178">178</a>         },
<a name="L179" href="source/net/ipv4/arp.c#L179">179</a>         .gc_interval    = 30 * <a href="ident?i=HZ">HZ</a>,
<a name="L180" href="source/net/ipv4/arp.c#L180">180</a>         .gc_thresh1     = 128,
<a name="L181" href="source/net/ipv4/arp.c#L181">181</a>         .gc_thresh2     = 512,
<a name="L182" href="source/net/ipv4/arp.c#L182">182</a>         .gc_thresh3     = 1024,
<a name="L183" href="source/net/ipv4/arp.c#L183">183</a> };
<a name="L184" href="source/net/ipv4/arp.c#L184">184</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=arp_tbl">arp_tbl</a>);
<a name="L185" href="source/net/ipv4/arp.c#L185">185</a> 
<a name="L186" href="source/net/ipv4/arp.c#L186">186</a> int <a href="ident?i=arp_mc_map">arp_mc_map</a>(<a href="ident?i=__be32">__be32</a> <a href="ident?i=addr">addr</a>, <a href="ident?i=u8">u8</a> *haddr, struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>, int <a href="ident?i=dir">dir</a>)
<a name="L187" href="source/net/ipv4/arp.c#L187">187</a> {
<a name="L188" href="source/net/ipv4/arp.c#L188">188</a>         switch (<a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=type">type</a>) {
<a name="L189" href="source/net/ipv4/arp.c#L189">189</a>         case <a href="ident?i=ARPHRD_ETHER">ARPHRD_ETHER</a>:
<a name="L190" href="source/net/ipv4/arp.c#L190">190</a>         case <a href="ident?i=ARPHRD_FDDI">ARPHRD_FDDI</a>:
<a name="L191" href="source/net/ipv4/arp.c#L191">191</a>         case <a href="ident?i=ARPHRD_IEEE802">ARPHRD_IEEE802</a>:
<a name="L192" href="source/net/ipv4/arp.c#L192">192</a>                 <a href="ident?i=ip_eth_mc_map">ip_eth_mc_map</a>(<a href="ident?i=addr">addr</a>, haddr);
<a name="L193" href="source/net/ipv4/arp.c#L193">193</a>                 return 0;
<a name="L194" href="source/net/ipv4/arp.c#L194">194</a>         case <a href="ident?i=ARPHRD_INFINIBAND">ARPHRD_INFINIBAND</a>:
<a name="L195" href="source/net/ipv4/arp.c#L195">195</a>                 <a href="ident?i=ip_ib_mc_map">ip_ib_mc_map</a>(<a href="ident?i=addr">addr</a>, <a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=broadcast">broadcast</a>, haddr);
<a name="L196" href="source/net/ipv4/arp.c#L196">196</a>                 return 0;
<a name="L197" href="source/net/ipv4/arp.c#L197">197</a>         case <a href="ident?i=ARPHRD_IPGRE">ARPHRD_IPGRE</a>:
<a name="L198" href="source/net/ipv4/arp.c#L198">198</a>                 <a href="ident?i=ip_ipgre_mc_map">ip_ipgre_mc_map</a>(<a href="ident?i=addr">addr</a>, <a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=broadcast">broadcast</a>, haddr);
<a name="L199" href="source/net/ipv4/arp.c#L199">199</a>                 return 0;
<a name="L200" href="source/net/ipv4/arp.c#L200">200</a>         default:
<a name="L201" href="source/net/ipv4/arp.c#L201">201</a>                 if (<a href="ident?i=dir">dir</a>) {
<a name="L202" href="source/net/ipv4/arp.c#L202">202</a>                         <a href="ident?i=memcpy">memcpy</a>(haddr, <a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=broadcast">broadcast</a>, <a href="ident?i=dev">dev</a>-&gt;addr_len);
<a name="L203" href="source/net/ipv4/arp.c#L203">203</a>                         return 0;
<a name="L204" href="source/net/ipv4/arp.c#L204">204</a>                 }
<a name="L205" href="source/net/ipv4/arp.c#L205">205</a>         }
<a name="L206" href="source/net/ipv4/arp.c#L206">206</a>         return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L207" href="source/net/ipv4/arp.c#L207">207</a> }
<a name="L208" href="source/net/ipv4/arp.c#L208">208</a> 
<a name="L209" href="source/net/ipv4/arp.c#L209">209</a> 
<a name="L210" href="source/net/ipv4/arp.c#L210">210</a> static <a href="ident?i=u32">u32</a> <a href="ident?i=arp_hash">arp_hash</a>(const void *pkey,
<a name="L211" href="source/net/ipv4/arp.c#L211">211</a>                     const struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>,
<a name="L212" href="source/net/ipv4/arp.c#L212">212</a>                     <a href="ident?i=__u32">__u32</a> *hash_rnd)
<a name="L213" href="source/net/ipv4/arp.c#L213">213</a> {
<a name="L214" href="source/net/ipv4/arp.c#L214">214</a>         return <a href="ident?i=arp_hashfn">arp_hashfn</a>(pkey, <a href="ident?i=dev">dev</a>, hash_rnd);
<a name="L215" href="source/net/ipv4/arp.c#L215">215</a> }
<a name="L216" href="source/net/ipv4/arp.c#L216">216</a> 
<a name="L217" href="source/net/ipv4/arp.c#L217">217</a> static <a href="ident?i=bool">bool</a> <a href="ident?i=arp_key_eq">arp_key_eq</a>(const struct <a href="ident?i=neighbour">neighbour</a> *neigh, const void *pkey)
<a name="L218" href="source/net/ipv4/arp.c#L218">218</a> {
<a name="L219" href="source/net/ipv4/arp.c#L219">219</a>         return <a href="ident?i=neigh_key_eq32">neigh_key_eq32</a>(neigh, pkey);
<a name="L220" href="source/net/ipv4/arp.c#L220">220</a> }
<a name="L221" href="source/net/ipv4/arp.c#L221">221</a> 
<a name="L222" href="source/net/ipv4/arp.c#L222">222</a> static int <a href="ident?i=arp_constructor">arp_constructor</a>(struct <a href="ident?i=neighbour">neighbour</a> *neigh)
<a name="L223" href="source/net/ipv4/arp.c#L223">223</a> {
<a name="L224" href="source/net/ipv4/arp.c#L224">224</a>         <a href="ident?i=__be32">__be32</a> <a href="ident?i=addr">addr</a> = *(<a href="ident?i=__be32">__be32</a> *)neigh-&gt;primary_key;
<a name="L225" href="source/net/ipv4/arp.c#L225">225</a>         struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a> = neigh-&gt;<a href="ident?i=dev">dev</a>;
<a name="L226" href="source/net/ipv4/arp.c#L226">226</a>         struct <a href="ident?i=in_device">in_device</a> *in_dev;
<a name="L227" href="source/net/ipv4/arp.c#L227">227</a>         struct <a href="ident?i=neigh_parms">neigh_parms</a> *<a href="ident?i=parms">parms</a>;
<a name="L228" href="source/net/ipv4/arp.c#L228">228</a> 
<a name="L229" href="source/net/ipv4/arp.c#L229">229</a>         <a href="ident?i=rcu_read_lock">rcu_read_lock</a>();
<a name="L230" href="source/net/ipv4/arp.c#L230">230</a>         in_dev = <a href="ident?i=__in_dev_get_rcu">__in_dev_get_rcu</a>(<a href="ident?i=dev">dev</a>);
<a name="L231" href="source/net/ipv4/arp.c#L231">231</a>         if (!in_dev) {
<a name="L232" href="source/net/ipv4/arp.c#L232">232</a>                 <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L233" href="source/net/ipv4/arp.c#L233">233</a>                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L234" href="source/net/ipv4/arp.c#L234">234</a>         }
<a name="L235" href="source/net/ipv4/arp.c#L235">235</a> 
<a name="L236" href="source/net/ipv4/arp.c#L236">236</a>         neigh-&gt;<a href="ident?i=type">type</a> = <a href="ident?i=inet_addr_type">inet_addr_type</a>(<a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=dev">dev</a>), <a href="ident?i=addr">addr</a>);
<a name="L237" href="source/net/ipv4/arp.c#L237">237</a> 
<a name="L238" href="source/net/ipv4/arp.c#L238">238</a>         <a href="ident?i=parms">parms</a> = in_dev-&gt;arp_parms;
<a name="L239" href="source/net/ipv4/arp.c#L239">239</a>         <a href="ident?i=__neigh_parms_put">__neigh_parms_put</a>(neigh-&gt;<a href="ident?i=parms">parms</a>);
<a name="L240" href="source/net/ipv4/arp.c#L240">240</a>         neigh-&gt;<a href="ident?i=parms">parms</a> = <a href="ident?i=neigh_parms_clone">neigh_parms_clone</a>(<a href="ident?i=parms">parms</a>);
<a name="L241" href="source/net/ipv4/arp.c#L241">241</a>         <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L242" href="source/net/ipv4/arp.c#L242">242</a> 
<a name="L243" href="source/net/ipv4/arp.c#L243">243</a>         if (!<a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=header_ops">header_ops</a>) {
<a name="L244" href="source/net/ipv4/arp.c#L244">244</a>                 neigh-&gt;nud_state = <a href="ident?i=NUD_NOARP">NUD_NOARP</a>;
<a name="L245" href="source/net/ipv4/arp.c#L245">245</a>                 neigh-&gt;<a href="ident?i=ops">ops</a> = &amp;<a href="ident?i=arp_direct_ops">arp_direct_ops</a>;
<a name="L246" href="source/net/ipv4/arp.c#L246">246</a>                 neigh-&gt;<a href="ident?i=output">output</a> = <a href="ident?i=neigh_direct_output">neigh_direct_output</a>;
<a name="L247" href="source/net/ipv4/arp.c#L247">247</a>         } else {
<a name="L248" href="source/net/ipv4/arp.c#L248">248</a>                 <b><i>/* Good devices (checked by reading texts, but only Ethernet is</i></b>
<a name="L249" href="source/net/ipv4/arp.c#L249">249</a> <b><i>                   tested)</i></b>
<a name="L250" href="source/net/ipv4/arp.c#L250">250</a> <b><i></i></b>
<a name="L251" href="source/net/ipv4/arp.c#L251">251</a> <b><i>                   ARPHRD_ETHER: (ethernet, apfddi)</i></b>
<a name="L252" href="source/net/ipv4/arp.c#L252">252</a> <b><i>                   ARPHRD_FDDI: (fddi)</i></b>
<a name="L253" href="source/net/ipv4/arp.c#L253">253</a> <b><i>                   ARPHRD_IEEE802: (tr)</i></b>
<a name="L254" href="source/net/ipv4/arp.c#L254">254</a> <b><i>                   ARPHRD_METRICOM: (strip)</i></b>
<a name="L255" href="source/net/ipv4/arp.c#L255">255</a> <b><i>                   ARPHRD_ARCNET:</i></b>
<a name="L256" href="source/net/ipv4/arp.c#L256">256</a> <b><i>                   etc. etc. etc.</i></b>
<a name="L257" href="source/net/ipv4/arp.c#L257">257</a> <b><i></i></b>
<a name="L258" href="source/net/ipv4/arp.c#L258">258</a> <b><i>                   ARPHRD_IPDDP will also work, if author repairs it.</i></b>
<a name="L259" href="source/net/ipv4/arp.c#L259">259</a> <b><i>                   I did not it, because this driver does not work even</i></b>
<a name="L260" href="source/net/ipv4/arp.c#L260">260</a> <b><i>                   in old paradigm.</i></b>
<a name="L261" href="source/net/ipv4/arp.c#L261">261</a> <b><i>                 */</i></b>
<a name="L262" href="source/net/ipv4/arp.c#L262">262</a> 
<a name="L263" href="source/net/ipv4/arp.c#L263">263</a>                 if (neigh-&gt;<a href="ident?i=type">type</a> == RTN_MULTICAST) {
<a name="L264" href="source/net/ipv4/arp.c#L264">264</a>                         neigh-&gt;nud_state = <a href="ident?i=NUD_NOARP">NUD_NOARP</a>;
<a name="L265" href="source/net/ipv4/arp.c#L265">265</a>                         <a href="ident?i=arp_mc_map">arp_mc_map</a>(<a href="ident?i=addr">addr</a>, neigh-&gt;ha, <a href="ident?i=dev">dev</a>, 1);
<a name="L266" href="source/net/ipv4/arp.c#L266">266</a>                 } else if (<a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=flags">flags</a> &amp; (<a href="ident?i=IFF_NOARP">IFF_NOARP</a> | <a href="ident?i=IFF_LOOPBACK">IFF_LOOPBACK</a>)) {
<a name="L267" href="source/net/ipv4/arp.c#L267">267</a>                         neigh-&gt;nud_state = <a href="ident?i=NUD_NOARP">NUD_NOARP</a>;
<a name="L268" href="source/net/ipv4/arp.c#L268">268</a>                         <a href="ident?i=memcpy">memcpy</a>(neigh-&gt;ha, <a href="ident?i=dev">dev</a>-&gt;dev_addr, <a href="ident?i=dev">dev</a>-&gt;addr_len);
<a name="L269" href="source/net/ipv4/arp.c#L269">269</a>                 } else if (neigh-&gt;<a href="ident?i=type">type</a> == RTN_BROADCAST ||
<a name="L270" href="source/net/ipv4/arp.c#L270">270</a>                            (<a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=IFF_POINTOPOINT">IFF_POINTOPOINT</a>)) {
<a name="L271" href="source/net/ipv4/arp.c#L271">271</a>                         neigh-&gt;nud_state = <a href="ident?i=NUD_NOARP">NUD_NOARP</a>;
<a name="L272" href="source/net/ipv4/arp.c#L272">272</a>                         <a href="ident?i=memcpy">memcpy</a>(neigh-&gt;ha, <a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=broadcast">broadcast</a>, <a href="ident?i=dev">dev</a>-&gt;addr_len);
<a name="L273" href="source/net/ipv4/arp.c#L273">273</a>                 }
<a name="L274" href="source/net/ipv4/arp.c#L274">274</a> 
<a name="L275" href="source/net/ipv4/arp.c#L275">275</a>                 if (<a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=header_ops">header_ops</a>-&gt;<a href="ident?i=cache">cache</a>)
<a name="L276" href="source/net/ipv4/arp.c#L276">276</a>                         neigh-&gt;<a href="ident?i=ops">ops</a> = &amp;<a href="ident?i=arp_hh_ops">arp_hh_ops</a>;
<a name="L277" href="source/net/ipv4/arp.c#L277">277</a>                 else
<a name="L278" href="source/net/ipv4/arp.c#L278">278</a>                         neigh-&gt;<a href="ident?i=ops">ops</a> = &amp;<a href="ident?i=arp_generic_ops">arp_generic_ops</a>;
<a name="L279" href="source/net/ipv4/arp.c#L279">279</a> 
<a name="L280" href="source/net/ipv4/arp.c#L280">280</a>                 if (neigh-&gt;nud_state &amp; <a href="ident?i=NUD_VALID">NUD_VALID</a>)
<a name="L281" href="source/net/ipv4/arp.c#L281">281</a>                         neigh-&gt;<a href="ident?i=output">output</a> = neigh-&gt;<a href="ident?i=ops">ops</a>-&gt;connected_output;
<a name="L282" href="source/net/ipv4/arp.c#L282">282</a>                 else
<a name="L283" href="source/net/ipv4/arp.c#L283">283</a>                         neigh-&gt;<a href="ident?i=output">output</a> = neigh-&gt;<a href="ident?i=ops">ops</a>-&gt;<a href="ident?i=output">output</a>;
<a name="L284" href="source/net/ipv4/arp.c#L284">284</a>         }
<a name="L285" href="source/net/ipv4/arp.c#L285">285</a>         return 0;
<a name="L286" href="source/net/ipv4/arp.c#L286">286</a> }
<a name="L287" href="source/net/ipv4/arp.c#L287">287</a> 
<a name="L288" href="source/net/ipv4/arp.c#L288">288</a> static void <a href="ident?i=arp_error_report">arp_error_report</a>(struct <a href="ident?i=neighbour">neighbour</a> *neigh, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L289" href="source/net/ipv4/arp.c#L289">289</a> {
<a name="L290" href="source/net/ipv4/arp.c#L290">290</a>         <a href="ident?i=dst_link_failure">dst_link_failure</a>(<a href="ident?i=skb">skb</a>);
<a name="L291" href="source/net/ipv4/arp.c#L291">291</a>         <a href="ident?i=kfree_skb">kfree_skb</a>(<a href="ident?i=skb">skb</a>);
<a name="L292" href="source/net/ipv4/arp.c#L292">292</a> }
<a name="L293" href="source/net/ipv4/arp.c#L293">293</a> 
<a name="L294" href="source/net/ipv4/arp.c#L294">294</a> static void <a href="ident?i=arp_solicit">arp_solicit</a>(struct <a href="ident?i=neighbour">neighbour</a> *neigh, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L295" href="source/net/ipv4/arp.c#L295">295</a> {
<a name="L296" href="source/net/ipv4/arp.c#L296">296</a>         <a href="ident?i=__be32">__be32</a> <a href="ident?i=saddr">saddr</a> = 0;
<a name="L297" href="source/net/ipv4/arp.c#L297">297</a>         <a href="ident?i=u8">u8</a> dst_ha[<a href="ident?i=MAX_ADDR_LEN">MAX_ADDR_LEN</a>], *dst_hw = <a href="ident?i=NULL">NULL</a>;
<a name="L298" href="source/net/ipv4/arp.c#L298">298</a>         struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a> = neigh-&gt;<a href="ident?i=dev">dev</a>;
<a name="L299" href="source/net/ipv4/arp.c#L299">299</a>         <a href="ident?i=__be32">__be32</a> <a href="ident?i=target">target</a> = *(<a href="ident?i=__be32">__be32</a> *)neigh-&gt;primary_key;
<a name="L300" href="source/net/ipv4/arp.c#L300">300</a>         int <a href="ident?i=probes">probes</a> = <a href="ident?i=atomic_read">atomic_read</a>(&amp;neigh-&gt;<a href="ident?i=probes">probes</a>);
<a name="L301" href="source/net/ipv4/arp.c#L301">301</a>         struct <a href="ident?i=in_device">in_device</a> *in_dev;
<a name="L302" href="source/net/ipv4/arp.c#L302">302</a> 
<a name="L303" href="source/net/ipv4/arp.c#L303">303</a>         <a href="ident?i=rcu_read_lock">rcu_read_lock</a>();
<a name="L304" href="source/net/ipv4/arp.c#L304">304</a>         in_dev = <a href="ident?i=__in_dev_get_rcu">__in_dev_get_rcu</a>(<a href="ident?i=dev">dev</a>);
<a name="L305" href="source/net/ipv4/arp.c#L305">305</a>         if (!in_dev) {
<a name="L306" href="source/net/ipv4/arp.c#L306">306</a>                 <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L307" href="source/net/ipv4/arp.c#L307">307</a>                 return;
<a name="L308" href="source/net/ipv4/arp.c#L308">308</a>         }
<a name="L309" href="source/net/ipv4/arp.c#L309">309</a>         switch (<a href="ident?i=IN_DEV_ARP_ANNOUNCE">IN_DEV_ARP_ANNOUNCE</a>(in_dev)) {
<a name="L310" href="source/net/ipv4/arp.c#L310">310</a>         default:
<a name="L311" href="source/net/ipv4/arp.c#L311">311</a>         case 0:         <b><i>/* By default announce any local IP */</i></b>
<a name="L312" href="source/net/ipv4/arp.c#L312">312</a>                 if (<a href="ident?i=skb">skb</a> &amp;&amp; <a href="ident?i=inet_addr_type">inet_addr_type</a>(<a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=dev">dev</a>),
<a name="L313" href="source/net/ipv4/arp.c#L313">313</a>                                           <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=saddr">saddr</a>) == RTN_LOCAL)
<a name="L314" href="source/net/ipv4/arp.c#L314">314</a>                         <a href="ident?i=saddr">saddr</a> = <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=saddr">saddr</a>;
<a name="L315" href="source/net/ipv4/arp.c#L315">315</a>                 break;
<a name="L316" href="source/net/ipv4/arp.c#L316">316</a>         case 1:         <b><i>/* Restrict announcements of saddr in same subnet */</i></b>
<a name="L317" href="source/net/ipv4/arp.c#L317">317</a>                 if (!<a href="ident?i=skb">skb</a>)
<a name="L318" href="source/net/ipv4/arp.c#L318">318</a>                         break;
<a name="L319" href="source/net/ipv4/arp.c#L319">319</a>                 <a href="ident?i=saddr">saddr</a> = <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=saddr">saddr</a>;
<a name="L320" href="source/net/ipv4/arp.c#L320">320</a>                 if (<a href="ident?i=inet_addr_type">inet_addr_type</a>(<a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=dev">dev</a>), <a href="ident?i=saddr">saddr</a>) == RTN_LOCAL) {
<a name="L321" href="source/net/ipv4/arp.c#L321">321</a>                         <b><i>/* saddr should be known to target */</i></b>
<a name="L322" href="source/net/ipv4/arp.c#L322">322</a>                         if (<a href="ident?i=inet_addr_onlink">inet_addr_onlink</a>(in_dev, <a href="ident?i=target">target</a>, <a href="ident?i=saddr">saddr</a>))
<a name="L323" href="source/net/ipv4/arp.c#L323">323</a>                                 break;
<a name="L324" href="source/net/ipv4/arp.c#L324">324</a>                 }
<a name="L325" href="source/net/ipv4/arp.c#L325">325</a>                 <a href="ident?i=saddr">saddr</a> = 0;
<a name="L326" href="source/net/ipv4/arp.c#L326">326</a>                 break;
<a name="L327" href="source/net/ipv4/arp.c#L327">327</a>         case 2:         <b><i>/* Avoid secondary IPs, get a primary/preferred one */</i></b>
<a name="L328" href="source/net/ipv4/arp.c#L328">328</a>                 break;
<a name="L329" href="source/net/ipv4/arp.c#L329">329</a>         }
<a name="L330" href="source/net/ipv4/arp.c#L330">330</a>         <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L331" href="source/net/ipv4/arp.c#L331">331</a> 
<a name="L332" href="source/net/ipv4/arp.c#L332">332</a>         if (!<a href="ident?i=saddr">saddr</a>)
<a name="L333" href="source/net/ipv4/arp.c#L333">333</a>                 <a href="ident?i=saddr">saddr</a> = <a href="ident?i=inet_select_addr">inet_select_addr</a>(<a href="ident?i=dev">dev</a>, <a href="ident?i=target">target</a>, RT_SCOPE_LINK);
<a name="L334" href="source/net/ipv4/arp.c#L334">334</a> 
<a name="L335" href="source/net/ipv4/arp.c#L335">335</a>         <a href="ident?i=probes">probes</a> -= <a href="ident?i=NEIGH_VAR">NEIGH_VAR</a>(neigh-&gt;<a href="ident?i=parms">parms</a>, UCAST_PROBES);
<a name="L336" href="source/net/ipv4/arp.c#L336">336</a>         if (<a href="ident?i=probes">probes</a> &lt; 0) {
<a name="L337" href="source/net/ipv4/arp.c#L337">337</a>                 if (!(neigh-&gt;nud_state &amp; <a href="ident?i=NUD_VALID">NUD_VALID</a>))
<a name="L338" href="source/net/ipv4/arp.c#L338">338</a>                         <a href="ident?i=pr_debug">pr_debug</a>(<i>"trying to ucast probe in NUD_INVALID\n"</i>);
<a name="L339" href="source/net/ipv4/arp.c#L339">339</a>                 <a href="ident?i=neigh_ha_snapshot">neigh_ha_snapshot</a>(dst_ha, neigh, <a href="ident?i=dev">dev</a>);
<a name="L340" href="source/net/ipv4/arp.c#L340">340</a>                 dst_hw = dst_ha;
<a name="L341" href="source/net/ipv4/arp.c#L341">341</a>         } else {
<a name="L342" href="source/net/ipv4/arp.c#L342">342</a>                 <a href="ident?i=probes">probes</a> -= <a href="ident?i=NEIGH_VAR">NEIGH_VAR</a>(neigh-&gt;<a href="ident?i=parms">parms</a>, APP_PROBES);
<a name="L343" href="source/net/ipv4/arp.c#L343">343</a>                 if (<a href="ident?i=probes">probes</a> &lt; 0) {
<a name="L344" href="source/net/ipv4/arp.c#L344">344</a>                         <a href="ident?i=neigh_app_ns">neigh_app_ns</a>(neigh);
<a name="L345" href="source/net/ipv4/arp.c#L345">345</a>                         return;
<a name="L346" href="source/net/ipv4/arp.c#L346">346</a>                 }
<a name="L347" href="source/net/ipv4/arp.c#L347">347</a>         }
<a name="L348" href="source/net/ipv4/arp.c#L348">348</a> 
<a name="L349" href="source/net/ipv4/arp.c#L349">349</a>         <a href="ident?i=arp_send">arp_send</a>(<a href="ident?i=ARPOP_REQUEST">ARPOP_REQUEST</a>, <a href="ident?i=ETH_P_ARP">ETH_P_ARP</a>, <a href="ident?i=target">target</a>, <a href="ident?i=dev">dev</a>, <a href="ident?i=saddr">saddr</a>,
<a name="L350" href="source/net/ipv4/arp.c#L350">350</a>                  dst_hw, <a href="ident?i=dev">dev</a>-&gt;dev_addr, <a href="ident?i=NULL">NULL</a>);
<a name="L351" href="source/net/ipv4/arp.c#L351">351</a> }
<a name="L352" href="source/net/ipv4/arp.c#L352">352</a> 
<a name="L353" href="source/net/ipv4/arp.c#L353">353</a> static int <a href="ident?i=arp_ignore">arp_ignore</a>(struct <a href="ident?i=in_device">in_device</a> *in_dev, <a href="ident?i=__be32">__be32</a> sip, <a href="ident?i=__be32">__be32</a> tip)
<a name="L354" href="source/net/ipv4/arp.c#L354">354</a> {
<a name="L355" href="source/net/ipv4/arp.c#L355">355</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=dev_net">dev_net</a>(in_dev-&gt;<a href="ident?i=dev">dev</a>);
<a name="L356" href="source/net/ipv4/arp.c#L356">356</a>         int <a href="ident?i=scope">scope</a>;
<a name="L357" href="source/net/ipv4/arp.c#L357">357</a> 
<a name="L358" href="source/net/ipv4/arp.c#L358">358</a>         switch (<a href="ident?i=IN_DEV_ARP_IGNORE">IN_DEV_ARP_IGNORE</a>(in_dev)) {
<a name="L359" href="source/net/ipv4/arp.c#L359">359</a>         case 0: <b><i>/* Reply, the tip is already validated */</i></b>
<a name="L360" href="source/net/ipv4/arp.c#L360">360</a>                 return 0;
<a name="L361" href="source/net/ipv4/arp.c#L361">361</a>         case 1: <b><i>/* Reply only if tip is configured on the incoming interface */</i></b>
<a name="L362" href="source/net/ipv4/arp.c#L362">362</a>                 sip = 0;
<a name="L363" href="source/net/ipv4/arp.c#L363">363</a>                 <a href="ident?i=scope">scope</a> = RT_SCOPE_HOST;
<a name="L364" href="source/net/ipv4/arp.c#L364">364</a>                 break;
<a name="L365" href="source/net/ipv4/arp.c#L365">365</a>         case 2: <b><i>/*</i></b>
<a name="L366" href="source/net/ipv4/arp.c#L366">366</a> <b><i>                 * Reply only if tip is configured on the incoming interface</i></b>
<a name="L367" href="source/net/ipv4/arp.c#L367">367</a> <b><i>                 * and is in same subnet as sip</i></b>
<a name="L368" href="source/net/ipv4/arp.c#L368">368</a> <b><i>                 */</i></b>
<a name="L369" href="source/net/ipv4/arp.c#L369">369</a>                 <a href="ident?i=scope">scope</a> = RT_SCOPE_HOST;
<a name="L370" href="source/net/ipv4/arp.c#L370">370</a>                 break;
<a name="L371" href="source/net/ipv4/arp.c#L371">371</a>         case 3: <b><i>/* Do not reply for scope host addresses */</i></b>
<a name="L372" href="source/net/ipv4/arp.c#L372">372</a>                 sip = 0;
<a name="L373" href="source/net/ipv4/arp.c#L373">373</a>                 <a href="ident?i=scope">scope</a> = RT_SCOPE_LINK;
<a name="L374" href="source/net/ipv4/arp.c#L374">374</a>                 in_dev = <a href="ident?i=NULL">NULL</a>;
<a name="L375" href="source/net/ipv4/arp.c#L375">375</a>                 break;
<a name="L376" href="source/net/ipv4/arp.c#L376">376</a>         case 4: <b><i>/* Reserved */</i></b>
<a name="L377" href="source/net/ipv4/arp.c#L377">377</a>         case 5:
<a name="L378" href="source/net/ipv4/arp.c#L378">378</a>         case 6:
<a name="L379" href="source/net/ipv4/arp.c#L379">379</a>         case 7:
<a name="L380" href="source/net/ipv4/arp.c#L380">380</a>                 return 0;
<a name="L381" href="source/net/ipv4/arp.c#L381">381</a>         case 8: <b><i>/* Do not reply */</i></b>
<a name="L382" href="source/net/ipv4/arp.c#L382">382</a>                 return 1;
<a name="L383" href="source/net/ipv4/arp.c#L383">383</a>         default:
<a name="L384" href="source/net/ipv4/arp.c#L384">384</a>                 return 0;
<a name="L385" href="source/net/ipv4/arp.c#L385">385</a>         }
<a name="L386" href="source/net/ipv4/arp.c#L386">386</a>         return !<a href="ident?i=inet_confirm_addr">inet_confirm_addr</a>(<a href="ident?i=net">net</a>, in_dev, sip, tip, <a href="ident?i=scope">scope</a>);
<a name="L387" href="source/net/ipv4/arp.c#L387">387</a> }
<a name="L388" href="source/net/ipv4/arp.c#L388">388</a> 
<a name="L389" href="source/net/ipv4/arp.c#L389">389</a> static int <a href="ident?i=arp_filter">arp_filter</a>(<a href="ident?i=__be32">__be32</a> sip, <a href="ident?i=__be32">__be32</a> tip, struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>)
<a name="L390" href="source/net/ipv4/arp.c#L390">390</a> {
<a name="L391" href="source/net/ipv4/arp.c#L391">391</a>         struct <a href="ident?i=rtable">rtable</a> *<a href="ident?i=rt">rt</a>;
<a name="L392" href="source/net/ipv4/arp.c#L392">392</a>         int <a href="ident?i=flag">flag</a> = 0;
<a name="L393" href="source/net/ipv4/arp.c#L393">393</a>         <b><i>/*unsigned long now; */</i></b>
<a name="L394" href="source/net/ipv4/arp.c#L394">394</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=dev">dev</a>);
<a name="L395" href="source/net/ipv4/arp.c#L395">395</a> 
<a name="L396" href="source/net/ipv4/arp.c#L396">396</a>         <a href="ident?i=rt">rt</a> = <a href="ident?i=ip_route_output">ip_route_output</a>(<a href="ident?i=net">net</a>, sip, tip, 0, 0);
<a name="L397" href="source/net/ipv4/arp.c#L397">397</a>         if (<a href="ident?i=IS_ERR">IS_ERR</a>(<a href="ident?i=rt">rt</a>))
<a name="L398" href="source/net/ipv4/arp.c#L398">398</a>                 return 1;
<a name="L399" href="source/net/ipv4/arp.c#L399">399</a>         if (<a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>.<a href="ident?i=dev">dev</a> != <a href="ident?i=dev">dev</a>) {
<a name="L400" href="source/net/ipv4/arp.c#L400">400</a>                 <a href="ident?i=NET_INC_STATS_BH">NET_INC_STATS_BH</a>(<a href="ident?i=net">net</a>, LINUX_MIB_ARPFILTER);
<a name="L401" href="source/net/ipv4/arp.c#L401">401</a>                 <a href="ident?i=flag">flag</a> = 1;
<a name="L402" href="source/net/ipv4/arp.c#L402">402</a>         }
<a name="L403" href="source/net/ipv4/arp.c#L403">403</a>         <a href="ident?i=ip_rt_put">ip_rt_put</a>(<a href="ident?i=rt">rt</a>);
<a name="L404" href="source/net/ipv4/arp.c#L404">404</a>         return <a href="ident?i=flag">flag</a>;
<a name="L405" href="source/net/ipv4/arp.c#L405">405</a> }
<a name="L406" href="source/net/ipv4/arp.c#L406">406</a> 
<a name="L407" href="source/net/ipv4/arp.c#L407">407</a> <b><i>/*</i></b>
<a name="L408" href="source/net/ipv4/arp.c#L408">408</a> <b><i> * Check if we can use proxy ARP for this path</i></b>
<a name="L409" href="source/net/ipv4/arp.c#L409">409</a> <b><i> */</i></b>
<a name="L410" href="source/net/ipv4/arp.c#L410">410</a> static inline int <a href="ident?i=arp_fwd_proxy">arp_fwd_proxy</a>(struct <a href="ident?i=in_device">in_device</a> *in_dev,
<a name="L411" href="source/net/ipv4/arp.c#L411">411</a>                                 struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>, struct <a href="ident?i=rtable">rtable</a> *<a href="ident?i=rt">rt</a>)
<a name="L412" href="source/net/ipv4/arp.c#L412">412</a> {
<a name="L413" href="source/net/ipv4/arp.c#L413">413</a>         struct <a href="ident?i=in_device">in_device</a> *out_dev;
<a name="L414" href="source/net/ipv4/arp.c#L414">414</a>         int imi, omi = -1;
<a name="L415" href="source/net/ipv4/arp.c#L415">415</a> 
<a name="L416" href="source/net/ipv4/arp.c#L416">416</a>         if (<a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>.<a href="ident?i=dev">dev</a> == <a href="ident?i=dev">dev</a>)
<a name="L417" href="source/net/ipv4/arp.c#L417">417</a>                 return 0;
<a name="L418" href="source/net/ipv4/arp.c#L418">418</a> 
<a name="L419" href="source/net/ipv4/arp.c#L419">419</a>         if (!<a href="ident?i=IN_DEV_PROXY_ARP">IN_DEV_PROXY_ARP</a>(in_dev))
<a name="L420" href="source/net/ipv4/arp.c#L420">420</a>                 return 0;
<a name="L421" href="source/net/ipv4/arp.c#L421">421</a>         imi = <a href="ident?i=IN_DEV_MEDIUM_ID">IN_DEV_MEDIUM_ID</a>(in_dev);
<a name="L422" href="source/net/ipv4/arp.c#L422">422</a>         if (imi == 0)
<a name="L423" href="source/net/ipv4/arp.c#L423">423</a>                 return 1;
<a name="L424" href="source/net/ipv4/arp.c#L424">424</a>         if (imi == -1)
<a name="L425" href="source/net/ipv4/arp.c#L425">425</a>                 return 0;
<a name="L426" href="source/net/ipv4/arp.c#L426">426</a> 
<a name="L427" href="source/net/ipv4/arp.c#L427">427</a>         <b><i>/* place to check for proxy_arp for routes */</i></b>
<a name="L428" href="source/net/ipv4/arp.c#L428">428</a> 
<a name="L429" href="source/net/ipv4/arp.c#L429">429</a>         out_dev = <a href="ident?i=__in_dev_get_rcu">__in_dev_get_rcu</a>(<a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>.<a href="ident?i=dev">dev</a>);
<a name="L430" href="source/net/ipv4/arp.c#L430">430</a>         if (out_dev)
<a name="L431" href="source/net/ipv4/arp.c#L431">431</a>                 omi = <a href="ident?i=IN_DEV_MEDIUM_ID">IN_DEV_MEDIUM_ID</a>(out_dev);
<a name="L432" href="source/net/ipv4/arp.c#L432">432</a> 
<a name="L433" href="source/net/ipv4/arp.c#L433">433</a>         return omi != imi &amp;&amp; omi != -1;
<a name="L434" href="source/net/ipv4/arp.c#L434">434</a> }
<a name="L435" href="source/net/ipv4/arp.c#L435">435</a> 
<a name="L436" href="source/net/ipv4/arp.c#L436">436</a> <b><i>/*</i></b>
<a name="L437" href="source/net/ipv4/arp.c#L437">437</a> <b><i> * Check for RFC3069 proxy arp private VLAN (allow to send back to same dev)</i></b>
<a name="L438" href="source/net/ipv4/arp.c#L438">438</a> <b><i> *</i></b>
<a name="L439" href="source/net/ipv4/arp.c#L439">439</a> <b><i> * RFC3069 supports proxy arp replies back to the same interface.  This</i></b>
<a name="L440" href="source/net/ipv4/arp.c#L440">440</a> <b><i> * is done to support (ethernet) switch features, like RFC 3069, where</i></b>
<a name="L441" href="source/net/ipv4/arp.c#L441">441</a> <b><i> * the individual ports are not allowed to communicate with each</i></b>
<a name="L442" href="source/net/ipv4/arp.c#L442">442</a> <b><i> * other, BUT they are allowed to talk to the upstream router.  As</i></b>
<a name="L443" href="source/net/ipv4/arp.c#L443">443</a> <b><i> * described in RFC 3069, it is possible to allow these hosts to</i></b>
<a name="L444" href="source/net/ipv4/arp.c#L444">444</a> <b><i> * communicate through the upstream router, by proxy_arp'ing.</i></b>
<a name="L445" href="source/net/ipv4/arp.c#L445">445</a> <b><i> *</i></b>
<a name="L446" href="source/net/ipv4/arp.c#L446">446</a> <b><i> * RFC 3069: "VLAN Aggregation for Efficient IP Address Allocation"</i></b>
<a name="L447" href="source/net/ipv4/arp.c#L447">447</a> <b><i> *</i></b>
<a name="L448" href="source/net/ipv4/arp.c#L448">448</a> <b><i> *  This technology is known by different names:</i></b>
<a name="L449" href="source/net/ipv4/arp.c#L449">449</a> <b><i> *    In RFC 3069 it is called VLAN Aggregation.</i></b>
<a name="L450" href="source/net/ipv4/arp.c#L450">450</a> <b><i> *    Cisco and Allied Telesyn call it Private VLAN.</i></b>
<a name="L451" href="source/net/ipv4/arp.c#L451">451</a> <b><i> *    Hewlett-Packard call it Source-Port filtering or port-isolation.</i></b>
<a name="L452" href="source/net/ipv4/arp.c#L452">452</a> <b><i> *    Ericsson call it MAC-Forced Forwarding (RFC Draft).</i></b>
<a name="L453" href="source/net/ipv4/arp.c#L453">453</a> <b><i> *</i></b>
<a name="L454" href="source/net/ipv4/arp.c#L454">454</a> <b><i> */</i></b>
<a name="L455" href="source/net/ipv4/arp.c#L455">455</a> static inline int <a href="ident?i=arp_fwd_pvlan">arp_fwd_pvlan</a>(struct <a href="ident?i=in_device">in_device</a> *in_dev,
<a name="L456" href="source/net/ipv4/arp.c#L456">456</a>                                 struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>, struct <a href="ident?i=rtable">rtable</a> *<a href="ident?i=rt">rt</a>,
<a name="L457" href="source/net/ipv4/arp.c#L457">457</a>                                 <a href="ident?i=__be32">__be32</a> sip, <a href="ident?i=__be32">__be32</a> tip)
<a name="L458" href="source/net/ipv4/arp.c#L458">458</a> {
<a name="L459" href="source/net/ipv4/arp.c#L459">459</a>         <b><i>/* Private VLAN is only concerned about the same ethernet segment */</i></b>
<a name="L460" href="source/net/ipv4/arp.c#L460">460</a>         if (<a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>.<a href="ident?i=dev">dev</a> != <a href="ident?i=dev">dev</a>)
<a name="L461" href="source/net/ipv4/arp.c#L461">461</a>                 return 0;
<a name="L462" href="source/net/ipv4/arp.c#L462">462</a> 
<a name="L463" href="source/net/ipv4/arp.c#L463">463</a>         <b><i>/* Don't reply on self probes (often done by windowz boxes)*/</i></b>
<a name="L464" href="source/net/ipv4/arp.c#L464">464</a>         if (sip == tip)
<a name="L465" href="source/net/ipv4/arp.c#L465">465</a>                 return 0;
<a name="L466" href="source/net/ipv4/arp.c#L466">466</a> 
<a name="L467" href="source/net/ipv4/arp.c#L467">467</a>         if (<a href="ident?i=IN_DEV_PROXY_ARP_PVLAN">IN_DEV_PROXY_ARP_PVLAN</a>(in_dev))
<a name="L468" href="source/net/ipv4/arp.c#L468">468</a>                 return 1;
<a name="L469" href="source/net/ipv4/arp.c#L469">469</a>         else
<a name="L470" href="source/net/ipv4/arp.c#L470">470</a>                 return 0;
<a name="L471" href="source/net/ipv4/arp.c#L471">471</a> }
<a name="L472" href="source/net/ipv4/arp.c#L472">472</a> 
<a name="L473" href="source/net/ipv4/arp.c#L473">473</a> <b><i>/*</i></b>
<a name="L474" href="source/net/ipv4/arp.c#L474">474</a> <b><i> *      Interface to link layer: send routine and receive handler.</i></b>
<a name="L475" href="source/net/ipv4/arp.c#L475">475</a> <b><i> */</i></b>
<a name="L476" href="source/net/ipv4/arp.c#L476">476</a> 
<a name="L477" href="source/net/ipv4/arp.c#L477">477</a> <b><i>/*</i></b>
<a name="L478" href="source/net/ipv4/arp.c#L478">478</a> <b><i> *      Create an arp packet. If dest_hw is not set, we create a broadcast</i></b>
<a name="L479" href="source/net/ipv4/arp.c#L479">479</a> <b><i> *      message.</i></b>
<a name="L480" href="source/net/ipv4/arp.c#L480">480</a> <b><i> */</i></b>
<a name="L481" href="source/net/ipv4/arp.c#L481">481</a> struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=arp_create">arp_create</a>(int <a href="ident?i=type">type</a>, int ptype, <a href="ident?i=__be32">__be32</a> dest_ip,
<a name="L482" href="source/net/ipv4/arp.c#L482">482</a>                            struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>, <a href="ident?i=__be32">__be32</a> src_ip,
<a name="L483" href="source/net/ipv4/arp.c#L483">483</a>                            const unsigned char *dest_hw,
<a name="L484" href="source/net/ipv4/arp.c#L484">484</a>                            const unsigned char *src_hw,
<a name="L485" href="source/net/ipv4/arp.c#L485">485</a>                            const unsigned char *target_hw)
<a name="L486" href="source/net/ipv4/arp.c#L486">486</a> {
<a name="L487" href="source/net/ipv4/arp.c#L487">487</a>         struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>;
<a name="L488" href="source/net/ipv4/arp.c#L488">488</a>         struct <a href="ident?i=arphdr">arphdr</a> *arp;
<a name="L489" href="source/net/ipv4/arp.c#L489">489</a>         unsigned char *arp_ptr;
<a name="L490" href="source/net/ipv4/arp.c#L490">490</a>         int hlen = <a href="ident?i=LL_RESERVED_SPACE">LL_RESERVED_SPACE</a>(<a href="ident?i=dev">dev</a>);
<a name="L491" href="source/net/ipv4/arp.c#L491">491</a>         int tlen = <a href="ident?i=dev">dev</a>-&gt;needed_tailroom;
<a name="L492" href="source/net/ipv4/arp.c#L492">492</a> 
<a name="L493" href="source/net/ipv4/arp.c#L493">493</a>         <b><i>/*</i></b>
<a name="L494" href="source/net/ipv4/arp.c#L494">494</a> <b><i>         *      Allocate a buffer</i></b>
<a name="L495" href="source/net/ipv4/arp.c#L495">495</a> <b><i>         */</i></b>
<a name="L496" href="source/net/ipv4/arp.c#L496">496</a> 
<a name="L497" href="source/net/ipv4/arp.c#L497">497</a>         <a href="ident?i=skb">skb</a> = <a href="ident?i=alloc_skb">alloc_skb</a>(<a href="ident?i=arp_hdr_len">arp_hdr_len</a>(<a href="ident?i=dev">dev</a>) + hlen + tlen, <a href="ident?i=GFP_ATOMIC">GFP_ATOMIC</a>);
<a name="L498" href="source/net/ipv4/arp.c#L498">498</a>         if (!<a href="ident?i=skb">skb</a>)
<a name="L499" href="source/net/ipv4/arp.c#L499">499</a>                 return <a href="ident?i=NULL">NULL</a>;
<a name="L500" href="source/net/ipv4/arp.c#L500">500</a> 
<a name="L501" href="source/net/ipv4/arp.c#L501">501</a>         <a href="ident?i=skb_reserve">skb_reserve</a>(<a href="ident?i=skb">skb</a>, hlen);
<a name="L502" href="source/net/ipv4/arp.c#L502">502</a>         <a href="ident?i=skb_reset_network_header">skb_reset_network_header</a>(<a href="ident?i=skb">skb</a>);
<a name="L503" href="source/net/ipv4/arp.c#L503">503</a>         arp = (struct <a href="ident?i=arphdr">arphdr</a> *) <a href="ident?i=skb_put">skb_put</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=arp_hdr_len">arp_hdr_len</a>(<a href="ident?i=dev">dev</a>));
<a name="L504" href="source/net/ipv4/arp.c#L504">504</a>         <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=dev">dev</a> = <a href="ident?i=dev">dev</a>;
<a name="L505" href="source/net/ipv4/arp.c#L505">505</a>         <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=protocol">protocol</a> = <a href="ident?i=htons">htons</a>(<a href="ident?i=ETH_P_ARP">ETH_P_ARP</a>);
<a name="L506" href="source/net/ipv4/arp.c#L506">506</a>         if (!src_hw)
<a name="L507" href="source/net/ipv4/arp.c#L507">507</a>                 src_hw = <a href="ident?i=dev">dev</a>-&gt;dev_addr;
<a name="L508" href="source/net/ipv4/arp.c#L508">508</a>         if (!dest_hw)
<a name="L509" href="source/net/ipv4/arp.c#L509">509</a>                 dest_hw = <a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=broadcast">broadcast</a>;
<a name="L510" href="source/net/ipv4/arp.c#L510">510</a> 
<a name="L511" href="source/net/ipv4/arp.c#L511">511</a>         <b><i>/*</i></b>
<a name="L512" href="source/net/ipv4/arp.c#L512">512</a> <b><i>         *      Fill the device header for the ARP frame</i></b>
<a name="L513" href="source/net/ipv4/arp.c#L513">513</a> <b><i>         */</i></b>
<a name="L514" href="source/net/ipv4/arp.c#L514">514</a>         if (<a href="ident?i=dev_hard_header">dev_hard_header</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=dev">dev</a>, ptype, dest_hw, src_hw, <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a>) &lt; 0)
<a name="L515" href="source/net/ipv4/arp.c#L515">515</a>                 goto <a href="ident?i=out">out</a>;
<a name="L516" href="source/net/ipv4/arp.c#L516">516</a> 
<a name="L517" href="source/net/ipv4/arp.c#L517">517</a>         <b><i>/*</i></b>
<a name="L518" href="source/net/ipv4/arp.c#L518">518</a> <b><i>         * Fill out the arp protocol part.</i></b>
<a name="L519" href="source/net/ipv4/arp.c#L519">519</a> <b><i>         *</i></b>
<a name="L520" href="source/net/ipv4/arp.c#L520">520</a> <b><i>         * The arp hardware type should match the device type, except for FDDI,</i></b>
<a name="L521" href="source/net/ipv4/arp.c#L521">521</a> <b><i>         * which (according to RFC 1390) should always equal 1 (Ethernet).</i></b>
<a name="L522" href="source/net/ipv4/arp.c#L522">522</a> <b><i>         */</i></b>
<a name="L523" href="source/net/ipv4/arp.c#L523">523</a>         <b><i>/*</i></b>
<a name="L524" href="source/net/ipv4/arp.c#L524">524</a> <b><i>         *      Exceptions everywhere. AX.25 uses the AX.25 PID value not the</i></b>
<a name="L525" href="source/net/ipv4/arp.c#L525">525</a> <b><i>         *      DIX code for the protocol. Make these device structure fields.</i></b>
<a name="L526" href="source/net/ipv4/arp.c#L526">526</a> <b><i>         */</i></b>
<a name="L527" href="source/net/ipv4/arp.c#L527">527</a>         switch (<a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=type">type</a>) {
<a name="L528" href="source/net/ipv4/arp.c#L528">528</a>         default:
<a name="L529" href="source/net/ipv4/arp.c#L529">529</a>                 arp-&gt;ar_hrd = <a href="ident?i=htons">htons</a>(<a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=type">type</a>);
<a name="L530" href="source/net/ipv4/arp.c#L530">530</a>                 arp-&gt;ar_pro = <a href="ident?i=htons">htons</a>(<a href="ident?i=ETH_P_IP">ETH_P_IP</a>);
<a name="L531" href="source/net/ipv4/arp.c#L531">531</a>                 break;
<a name="L532" href="source/net/ipv4/arp.c#L532">532</a> 
<a name="L533" href="source/net/ipv4/arp.c#L533">533</a> #if <a href="ident?i=IS_ENABLED">IS_ENABLED</a>(CONFIG_AX25)
<a name="L534" href="source/net/ipv4/arp.c#L534">534</a>         case <a href="ident?i=ARPHRD_AX25">ARPHRD_AX25</a>:
<a name="L535" href="source/net/ipv4/arp.c#L535">535</a>                 arp-&gt;ar_hrd = <a href="ident?i=htons">htons</a>(<a href="ident?i=ARPHRD_AX25">ARPHRD_AX25</a>);
<a name="L536" href="source/net/ipv4/arp.c#L536">536</a>                 arp-&gt;ar_pro = <a href="ident?i=htons">htons</a>(<a href="ident?i=AX25_P_IP">AX25_P_IP</a>);
<a name="L537" href="source/net/ipv4/arp.c#L537">537</a>                 break;
<a name="L538" href="source/net/ipv4/arp.c#L538">538</a> 
<a name="L539" href="source/net/ipv4/arp.c#L539">539</a> #if <a href="ident?i=IS_ENABLED">IS_ENABLED</a>(CONFIG_NETROM)
<a name="L540" href="source/net/ipv4/arp.c#L540">540</a>         case <a href="ident?i=ARPHRD_NETROM">ARPHRD_NETROM</a>:
<a name="L541" href="source/net/ipv4/arp.c#L541">541</a>                 arp-&gt;ar_hrd = <a href="ident?i=htons">htons</a>(<a href="ident?i=ARPHRD_NETROM">ARPHRD_NETROM</a>);
<a name="L542" href="source/net/ipv4/arp.c#L542">542</a>                 arp-&gt;ar_pro = <a href="ident?i=htons">htons</a>(<a href="ident?i=AX25_P_IP">AX25_P_IP</a>);
<a name="L543" href="source/net/ipv4/arp.c#L543">543</a>                 break;
<a name="L544" href="source/net/ipv4/arp.c#L544">544</a> #endif
<a name="L545" href="source/net/ipv4/arp.c#L545">545</a> #endif
<a name="L546" href="source/net/ipv4/arp.c#L546">546</a> 
<a name="L547" href="source/net/ipv4/arp.c#L547">547</a> #if <a href="ident?i=IS_ENABLED">IS_ENABLED</a>(CONFIG_FDDI)
<a name="L548" href="source/net/ipv4/arp.c#L548">548</a>         case <a href="ident?i=ARPHRD_FDDI">ARPHRD_FDDI</a>:
<a name="L549" href="source/net/ipv4/arp.c#L549">549</a>                 arp-&gt;ar_hrd = <a href="ident?i=htons">htons</a>(<a href="ident?i=ARPHRD_ETHER">ARPHRD_ETHER</a>);
<a name="L550" href="source/net/ipv4/arp.c#L550">550</a>                 arp-&gt;ar_pro = <a href="ident?i=htons">htons</a>(<a href="ident?i=ETH_P_IP">ETH_P_IP</a>);
<a name="L551" href="source/net/ipv4/arp.c#L551">551</a>                 break;
<a name="L552" href="source/net/ipv4/arp.c#L552">552</a> #endif
<a name="L553" href="source/net/ipv4/arp.c#L553">553</a>         }
<a name="L554" href="source/net/ipv4/arp.c#L554">554</a> 
<a name="L555" href="source/net/ipv4/arp.c#L555">555</a>         arp-&gt;ar_hln = <a href="ident?i=dev">dev</a>-&gt;addr_len;
<a name="L556" href="source/net/ipv4/arp.c#L556">556</a>         arp-&gt;ar_pln = 4;
<a name="L557" href="source/net/ipv4/arp.c#L557">557</a>         arp-&gt;ar_op = <a href="ident?i=htons">htons</a>(<a href="ident?i=type">type</a>);
<a name="L558" href="source/net/ipv4/arp.c#L558">558</a> 
<a name="L559" href="source/net/ipv4/arp.c#L559">559</a>         arp_ptr = (unsigned char *)(arp + 1);
<a name="L560" href="source/net/ipv4/arp.c#L560">560</a> 
<a name="L561" href="source/net/ipv4/arp.c#L561">561</a>         <a href="ident?i=memcpy">memcpy</a>(arp_ptr, src_hw, <a href="ident?i=dev">dev</a>-&gt;addr_len);
<a name="L562" href="source/net/ipv4/arp.c#L562">562</a>         arp_ptr += <a href="ident?i=dev">dev</a>-&gt;addr_len;
<a name="L563" href="source/net/ipv4/arp.c#L563">563</a>         <a href="ident?i=memcpy">memcpy</a>(arp_ptr, &amp;src_ip, 4);
<a name="L564" href="source/net/ipv4/arp.c#L564">564</a>         arp_ptr += 4;
<a name="L565" href="source/net/ipv4/arp.c#L565">565</a> 
<a name="L566" href="source/net/ipv4/arp.c#L566">566</a>         switch (<a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=type">type</a>) {
<a name="L567" href="source/net/ipv4/arp.c#L567">567</a> #if <a href="ident?i=IS_ENABLED">IS_ENABLED</a>(CONFIG_FIREWIRE_NET)
<a name="L568" href="source/net/ipv4/arp.c#L568">568</a>         case <a href="ident?i=ARPHRD_IEEE1394">ARPHRD_IEEE1394</a>:
<a name="L569" href="source/net/ipv4/arp.c#L569">569</a>                 break;
<a name="L570" href="source/net/ipv4/arp.c#L570">570</a> #endif
<a name="L571" href="source/net/ipv4/arp.c#L571">571</a>         default:
<a name="L572" href="source/net/ipv4/arp.c#L572">572</a>                 if (target_hw)
<a name="L573" href="source/net/ipv4/arp.c#L573">573</a>                         <a href="ident?i=memcpy">memcpy</a>(arp_ptr, target_hw, <a href="ident?i=dev">dev</a>-&gt;addr_len);
<a name="L574" href="source/net/ipv4/arp.c#L574">574</a>                 else
<a name="L575" href="source/net/ipv4/arp.c#L575">575</a>                         <a href="ident?i=memset">memset</a>(arp_ptr, 0, <a href="ident?i=dev">dev</a>-&gt;addr_len);
<a name="L576" href="source/net/ipv4/arp.c#L576">576</a>                 arp_ptr += <a href="ident?i=dev">dev</a>-&gt;addr_len;
<a name="L577" href="source/net/ipv4/arp.c#L577">577</a>         }
<a name="L578" href="source/net/ipv4/arp.c#L578">578</a>         <a href="ident?i=memcpy">memcpy</a>(arp_ptr, &amp;dest_ip, 4);
<a name="L579" href="source/net/ipv4/arp.c#L579">579</a> 
<a name="L580" href="source/net/ipv4/arp.c#L580">580</a>         return <a href="ident?i=skb">skb</a>;
<a name="L581" href="source/net/ipv4/arp.c#L581">581</a> 
<a name="L582" href="source/net/ipv4/arp.c#L582">582</a> <a href="ident?i=out">out</a>:
<a name="L583" href="source/net/ipv4/arp.c#L583">583</a>         <a href="ident?i=kfree_skb">kfree_skb</a>(<a href="ident?i=skb">skb</a>);
<a name="L584" href="source/net/ipv4/arp.c#L584">584</a>         return <a href="ident?i=NULL">NULL</a>;
<a name="L585" href="source/net/ipv4/arp.c#L585">585</a> }
<a name="L586" href="source/net/ipv4/arp.c#L586">586</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=arp_create">arp_create</a>);
<a name="L587" href="source/net/ipv4/arp.c#L587">587</a> 
<a name="L588" href="source/net/ipv4/arp.c#L588">588</a> <b><i>/*</i></b>
<a name="L589" href="source/net/ipv4/arp.c#L589">589</a> <b><i> *      Send an arp packet.</i></b>
<a name="L590" href="source/net/ipv4/arp.c#L590">590</a> <b><i> */</i></b>
<a name="L591" href="source/net/ipv4/arp.c#L591">591</a> void <a href="ident?i=arp_xmit">arp_xmit</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L592" href="source/net/ipv4/arp.c#L592">592</a> {
<a name="L593" href="source/net/ipv4/arp.c#L593">593</a>         <b><i>/* Send it off, maybe filter it using firewalling first.  */</i></b>
<a name="L594" href="source/net/ipv4/arp.c#L594">594</a>         <a href="ident?i=NF_HOOK">NF_HOOK</a>(NFPROTO_ARP, <a href="ident?i=NF_ARP_OUT">NF_ARP_OUT</a>, <a href="ident?i=NULL">NULL</a>, <a href="ident?i=skb">skb</a>,
<a name="L595" href="source/net/ipv4/arp.c#L595">595</a>                 <a href="ident?i=NULL">NULL</a>, <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=dev">dev</a>, <a href="ident?i=dev_queue_xmit_sk">dev_queue_xmit_sk</a>);
<a name="L596" href="source/net/ipv4/arp.c#L596">596</a> }
<a name="L597" href="source/net/ipv4/arp.c#L597">597</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=arp_xmit">arp_xmit</a>);
<a name="L598" href="source/net/ipv4/arp.c#L598">598</a> 
<a name="L599" href="source/net/ipv4/arp.c#L599">599</a> <b><i>/*</i></b>
<a name="L600" href="source/net/ipv4/arp.c#L600">600</a> <b><i> *      Create and send an arp packet.</i></b>
<a name="L601" href="source/net/ipv4/arp.c#L601">601</a> <b><i> */</i></b>
<a name="L602" href="source/net/ipv4/arp.c#L602">602</a> void <a href="ident?i=arp_send">arp_send</a>(int <a href="ident?i=type">type</a>, int ptype, <a href="ident?i=__be32">__be32</a> dest_ip,
<a name="L603" href="source/net/ipv4/arp.c#L603">603</a>               struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>, <a href="ident?i=__be32">__be32</a> src_ip,
<a name="L604" href="source/net/ipv4/arp.c#L604">604</a>               const unsigned char *dest_hw, const unsigned char *src_hw,
<a name="L605" href="source/net/ipv4/arp.c#L605">605</a>               const unsigned char *target_hw)
<a name="L606" href="source/net/ipv4/arp.c#L606">606</a> {
<a name="L607" href="source/net/ipv4/arp.c#L607">607</a>         struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>;
<a name="L608" href="source/net/ipv4/arp.c#L608">608</a> 
<a name="L609" href="source/net/ipv4/arp.c#L609">609</a>         <b><i>/*</i></b>
<a name="L610" href="source/net/ipv4/arp.c#L610">610</a> <b><i>         *      No arp on this interface.</i></b>
<a name="L611" href="source/net/ipv4/arp.c#L611">611</a> <b><i>         */</i></b>
<a name="L612" href="source/net/ipv4/arp.c#L612">612</a> 
<a name="L613" href="source/net/ipv4/arp.c#L613">613</a>         if (<a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=flags">flags</a>&amp;<a href="ident?i=IFF_NOARP">IFF_NOARP</a>)
<a name="L614" href="source/net/ipv4/arp.c#L614">614</a>                 return;
<a name="L615" href="source/net/ipv4/arp.c#L615">615</a> 
<a name="L616" href="source/net/ipv4/arp.c#L616">616</a>         <a href="ident?i=skb">skb</a> = <a href="ident?i=arp_create">arp_create</a>(<a href="ident?i=type">type</a>, ptype, dest_ip, <a href="ident?i=dev">dev</a>, src_ip,
<a name="L617" href="source/net/ipv4/arp.c#L617">617</a>                          dest_hw, src_hw, target_hw);
<a name="L618" href="source/net/ipv4/arp.c#L618">618</a>         if (!<a href="ident?i=skb">skb</a>)
<a name="L619" href="source/net/ipv4/arp.c#L619">619</a>                 return;
<a name="L620" href="source/net/ipv4/arp.c#L620">620</a> 
<a name="L621" href="source/net/ipv4/arp.c#L621">621</a>         <a href="ident?i=arp_xmit">arp_xmit</a>(<a href="ident?i=skb">skb</a>);
<a name="L622" href="source/net/ipv4/arp.c#L622">622</a> }
<a name="L623" href="source/net/ipv4/arp.c#L623">623</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=arp_send">arp_send</a>);
<a name="L624" href="source/net/ipv4/arp.c#L624">624</a> 
<a name="L625" href="source/net/ipv4/arp.c#L625">625</a> <b><i>/*</i></b>
<a name="L626" href="source/net/ipv4/arp.c#L626">626</a> <b><i> *      Process an arp request.</i></b>
<a name="L627" href="source/net/ipv4/arp.c#L627">627</a> <b><i> */</i></b>
<a name="L628" href="source/net/ipv4/arp.c#L628">628</a> 
<a name="L629" href="source/net/ipv4/arp.c#L629">629</a> static int <a href="ident?i=arp_process">arp_process</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L630" href="source/net/ipv4/arp.c#L630">630</a> {
<a name="L631" href="source/net/ipv4/arp.c#L631">631</a>         struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a> = <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=dev">dev</a>;
<a name="L632" href="source/net/ipv4/arp.c#L632">632</a>         struct <a href="ident?i=in_device">in_device</a> *in_dev = <a href="ident?i=__in_dev_get_rcu">__in_dev_get_rcu</a>(<a href="ident?i=dev">dev</a>);
<a name="L633" href="source/net/ipv4/arp.c#L633">633</a>         struct <a href="ident?i=arphdr">arphdr</a> *arp;
<a name="L634" href="source/net/ipv4/arp.c#L634">634</a>         unsigned char *arp_ptr;
<a name="L635" href="source/net/ipv4/arp.c#L635">635</a>         struct <a href="ident?i=rtable">rtable</a> *<a href="ident?i=rt">rt</a>;
<a name="L636" href="source/net/ipv4/arp.c#L636">636</a>         unsigned char *<a href="ident?i=sha">sha</a>;
<a name="L637" href="source/net/ipv4/arp.c#L637">637</a>         <a href="ident?i=__be32">__be32</a> sip, tip;
<a name="L638" href="source/net/ipv4/arp.c#L638">638</a>         <a href="ident?i=u16">u16</a> <a href="ident?i=dev_type">dev_type</a> = <a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=type">type</a>;
<a name="L639" href="source/net/ipv4/arp.c#L639">639</a>         int addr_type;
<a name="L640" href="source/net/ipv4/arp.c#L640">640</a>         struct <a href="ident?i=neighbour">neighbour</a> *<a href="ident?i=n">n</a>;
<a name="L641" href="source/net/ipv4/arp.c#L641">641</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=dev">dev</a>);
<a name="L642" href="source/net/ipv4/arp.c#L642">642</a>         <a href="ident?i=bool">bool</a> is_garp = <a href="ident?i=false">false</a>;
<a name="L643" href="source/net/ipv4/arp.c#L643">643</a> 
<a name="L644" href="source/net/ipv4/arp.c#L644">644</a>         <b><i>/* arp_rcv below verifies the ARP header and verifies the device</i></b>
<a name="L645" href="source/net/ipv4/arp.c#L645">645</a> <b><i>         * is ARP'able.</i></b>
<a name="L646" href="source/net/ipv4/arp.c#L646">646</a> <b><i>         */</i></b>
<a name="L647" href="source/net/ipv4/arp.c#L647">647</a> 
<a name="L648" href="source/net/ipv4/arp.c#L648">648</a>         if (!in_dev)
<a name="L649" href="source/net/ipv4/arp.c#L649">649</a>                 goto <a href="ident?i=out">out</a>;
<a name="L650" href="source/net/ipv4/arp.c#L650">650</a> 
<a name="L651" href="source/net/ipv4/arp.c#L651">651</a>         arp = <a href="ident?i=arp_hdr">arp_hdr</a>(<a href="ident?i=skb">skb</a>);
<a name="L652" href="source/net/ipv4/arp.c#L652">652</a> 
<a name="L653" href="source/net/ipv4/arp.c#L653">653</a>         switch (<a href="ident?i=dev_type">dev_type</a>) {
<a name="L654" href="source/net/ipv4/arp.c#L654">654</a>         default:
<a name="L655" href="source/net/ipv4/arp.c#L655">655</a>                 if (arp-&gt;ar_pro != <a href="ident?i=htons">htons</a>(<a href="ident?i=ETH_P_IP">ETH_P_IP</a>) ||
<a name="L656" href="source/net/ipv4/arp.c#L656">656</a>                     <a href="ident?i=htons">htons</a>(<a href="ident?i=dev_type">dev_type</a>) != arp-&gt;ar_hrd)
<a name="L657" href="source/net/ipv4/arp.c#L657">657</a>                         goto <a href="ident?i=out">out</a>;
<a name="L658" href="source/net/ipv4/arp.c#L658">658</a>                 break;
<a name="L659" href="source/net/ipv4/arp.c#L659">659</a>         case <a href="ident?i=ARPHRD_ETHER">ARPHRD_ETHER</a>:
<a name="L660" href="source/net/ipv4/arp.c#L660">660</a>         case <a href="ident?i=ARPHRD_FDDI">ARPHRD_FDDI</a>:
<a name="L661" href="source/net/ipv4/arp.c#L661">661</a>         case <a href="ident?i=ARPHRD_IEEE802">ARPHRD_IEEE802</a>:
<a name="L662" href="source/net/ipv4/arp.c#L662">662</a>                 <b><i>/*</i></b>
<a name="L663" href="source/net/ipv4/arp.c#L663">663</a> <b><i>                 * ETHERNET, and Fibre Channel (which are IEEE 802</i></b>
<a name="L664" href="source/net/ipv4/arp.c#L664">664</a> <b><i>                 * devices, according to RFC 2625) devices will accept ARP</i></b>
<a name="L665" href="source/net/ipv4/arp.c#L665">665</a> <b><i>                 * hardware types of either 1 (Ethernet) or 6 (IEEE 802.2).</i></b>
<a name="L666" href="source/net/ipv4/arp.c#L666">666</a> <b><i>                 * This is the case also of FDDI, where the RFC 1390 says that</i></b>
<a name="L667" href="source/net/ipv4/arp.c#L667">667</a> <b><i>                 * FDDI devices should accept ARP hardware of (1) Ethernet,</i></b>
<a name="L668" href="source/net/ipv4/arp.c#L668">668</a> <b><i>                 * however, to be more robust, we'll accept both 1 (Ethernet)</i></b>
<a name="L669" href="source/net/ipv4/arp.c#L669">669</a> <b><i>                 * or 6 (IEEE 802.2)</i></b>
<a name="L670" href="source/net/ipv4/arp.c#L670">670</a> <b><i>                 */</i></b>
<a name="L671" href="source/net/ipv4/arp.c#L671">671</a>                 if ((arp-&gt;ar_hrd != <a href="ident?i=htons">htons</a>(<a href="ident?i=ARPHRD_ETHER">ARPHRD_ETHER</a>) &amp;&amp;
<a name="L672" href="source/net/ipv4/arp.c#L672">672</a>                      arp-&gt;ar_hrd != <a href="ident?i=htons">htons</a>(<a href="ident?i=ARPHRD_IEEE802">ARPHRD_IEEE802</a>)) ||
<a name="L673" href="source/net/ipv4/arp.c#L673">673</a>                     arp-&gt;ar_pro != <a href="ident?i=htons">htons</a>(<a href="ident?i=ETH_P_IP">ETH_P_IP</a>))
<a name="L674" href="source/net/ipv4/arp.c#L674">674</a>                         goto <a href="ident?i=out">out</a>;
<a name="L675" href="source/net/ipv4/arp.c#L675">675</a>                 break;
<a name="L676" href="source/net/ipv4/arp.c#L676">676</a>         case <a href="ident?i=ARPHRD_AX25">ARPHRD_AX25</a>:
<a name="L677" href="source/net/ipv4/arp.c#L677">677</a>                 if (arp-&gt;ar_pro != <a href="ident?i=htons">htons</a>(<a href="ident?i=AX25_P_IP">AX25_P_IP</a>) ||
<a name="L678" href="source/net/ipv4/arp.c#L678">678</a>                     arp-&gt;ar_hrd != <a href="ident?i=htons">htons</a>(<a href="ident?i=ARPHRD_AX25">ARPHRD_AX25</a>))
<a name="L679" href="source/net/ipv4/arp.c#L679">679</a>                         goto <a href="ident?i=out">out</a>;
<a name="L680" href="source/net/ipv4/arp.c#L680">680</a>                 break;
<a name="L681" href="source/net/ipv4/arp.c#L681">681</a>         case <a href="ident?i=ARPHRD_NETROM">ARPHRD_NETROM</a>:
<a name="L682" href="source/net/ipv4/arp.c#L682">682</a>                 if (arp-&gt;ar_pro != <a href="ident?i=htons">htons</a>(<a href="ident?i=AX25_P_IP">AX25_P_IP</a>) ||
<a name="L683" href="source/net/ipv4/arp.c#L683">683</a>                     arp-&gt;ar_hrd != <a href="ident?i=htons">htons</a>(<a href="ident?i=ARPHRD_NETROM">ARPHRD_NETROM</a>))
<a name="L684" href="source/net/ipv4/arp.c#L684">684</a>                         goto <a href="ident?i=out">out</a>;
<a name="L685" href="source/net/ipv4/arp.c#L685">685</a>                 break;
<a name="L686" href="source/net/ipv4/arp.c#L686">686</a>         }
<a name="L687" href="source/net/ipv4/arp.c#L687">687</a> 
<a name="L688" href="source/net/ipv4/arp.c#L688">688</a>         <b><i>/* Understand only these message types */</i></b>
<a name="L689" href="source/net/ipv4/arp.c#L689">689</a> 
<a name="L690" href="source/net/ipv4/arp.c#L690">690</a>         if (arp-&gt;ar_op != <a href="ident?i=htons">htons</a>(<a href="ident?i=ARPOP_REPLY">ARPOP_REPLY</a>) &amp;&amp;
<a name="L691" href="source/net/ipv4/arp.c#L691">691</a>             arp-&gt;ar_op != <a href="ident?i=htons">htons</a>(<a href="ident?i=ARPOP_REQUEST">ARPOP_REQUEST</a>))
<a name="L692" href="source/net/ipv4/arp.c#L692">692</a>                 goto <a href="ident?i=out">out</a>;
<a name="L693" href="source/net/ipv4/arp.c#L693">693</a> 
<a name="L694" href="source/net/ipv4/arp.c#L694">694</a> <b><i>/*</i></b>
<a name="L695" href="source/net/ipv4/arp.c#L695">695</a> <b><i> *      Extract fields</i></b>
<a name="L696" href="source/net/ipv4/arp.c#L696">696</a> <b><i> */</i></b>
<a name="L697" href="source/net/ipv4/arp.c#L697">697</a>         arp_ptr = (unsigned char *)(arp + 1);
<a name="L698" href="source/net/ipv4/arp.c#L698">698</a>         <a href="ident?i=sha">sha</a>     = arp_ptr;
<a name="L699" href="source/net/ipv4/arp.c#L699">699</a>         arp_ptr += <a href="ident?i=dev">dev</a>-&gt;addr_len;
<a name="L700" href="source/net/ipv4/arp.c#L700">700</a>         <a href="ident?i=memcpy">memcpy</a>(&amp;sip, arp_ptr, 4);
<a name="L701" href="source/net/ipv4/arp.c#L701">701</a>         arp_ptr += 4;
<a name="L702" href="source/net/ipv4/arp.c#L702">702</a>         switch (<a href="ident?i=dev_type">dev_type</a>) {
<a name="L703" href="source/net/ipv4/arp.c#L703">703</a> #if <a href="ident?i=IS_ENABLED">IS_ENABLED</a>(CONFIG_FIREWIRE_NET)
<a name="L704" href="source/net/ipv4/arp.c#L704">704</a>         case <a href="ident?i=ARPHRD_IEEE1394">ARPHRD_IEEE1394</a>:
<a name="L705" href="source/net/ipv4/arp.c#L705">705</a>                 break;
<a name="L706" href="source/net/ipv4/arp.c#L706">706</a> #endif
<a name="L707" href="source/net/ipv4/arp.c#L707">707</a>         default:
<a name="L708" href="source/net/ipv4/arp.c#L708">708</a>                 arp_ptr += <a href="ident?i=dev">dev</a>-&gt;addr_len;
<a name="L709" href="source/net/ipv4/arp.c#L709">709</a>         }
<a name="L710" href="source/net/ipv4/arp.c#L710">710</a>         <a href="ident?i=memcpy">memcpy</a>(&amp;tip, arp_ptr, 4);
<a name="L711" href="source/net/ipv4/arp.c#L711">711</a> <b><i>/*</i></b>
<a name="L712" href="source/net/ipv4/arp.c#L712">712</a> <b><i> *      Check for bad requests for 127.x.x.x and requests for multicast</i></b>
<a name="L713" href="source/net/ipv4/arp.c#L713">713</a> <b><i> *      addresses.  If this is one such, delete it.</i></b>
<a name="L714" href="source/net/ipv4/arp.c#L714">714</a> <b><i> */</i></b>
<a name="L715" href="source/net/ipv4/arp.c#L715">715</a>         if (<a href="ident?i=ipv4_is_multicast">ipv4_is_multicast</a>(tip) ||
<a name="L716" href="source/net/ipv4/arp.c#L716">716</a>             (!<a href="ident?i=IN_DEV_ROUTE_LOCALNET">IN_DEV_ROUTE_LOCALNET</a>(in_dev) &amp;&amp; <a href="ident?i=ipv4_is_loopback">ipv4_is_loopback</a>(tip)))
<a name="L717" href="source/net/ipv4/arp.c#L717">717</a>                 goto <a href="ident?i=out">out</a>;
<a name="L718" href="source/net/ipv4/arp.c#L718">718</a> 
<a name="L719" href="source/net/ipv4/arp.c#L719">719</a> <b><i>/*</i></b>
<a name="L720" href="source/net/ipv4/arp.c#L720">720</a> <b><i> *     Special case: We must set Frame Relay source Q.922 address</i></b>
<a name="L721" href="source/net/ipv4/arp.c#L721">721</a> <b><i> */</i></b>
<a name="L722" href="source/net/ipv4/arp.c#L722">722</a>         if (<a href="ident?i=dev_type">dev_type</a> == <a href="ident?i=ARPHRD_DLCI">ARPHRD_DLCI</a>)
<a name="L723" href="source/net/ipv4/arp.c#L723">723</a>                 <a href="ident?i=sha">sha</a> = <a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=broadcast">broadcast</a>;
<a name="L724" href="source/net/ipv4/arp.c#L724">724</a> 
<a name="L725" href="source/net/ipv4/arp.c#L725">725</a> <b><i>/*</i></b>
<a name="L726" href="source/net/ipv4/arp.c#L726">726</a> <b><i> *  Process entry.  The idea here is we want to send a reply if it is a</i></b>
<a name="L727" href="source/net/ipv4/arp.c#L727">727</a> <b><i> *  request for us or if it is a request for someone else that we hold</i></b>
<a name="L728" href="source/net/ipv4/arp.c#L728">728</a> <b><i> *  a proxy for.  We want to add an entry to our cache if it is a reply</i></b>
<a name="L729" href="source/net/ipv4/arp.c#L729">729</a> <b><i> *  to us or if it is a request for our address.</i></b>
<a name="L730" href="source/net/ipv4/arp.c#L730">730</a> <b><i> *  (The assumption for this last is that if someone is requesting our</i></b>
<a name="L731" href="source/net/ipv4/arp.c#L731">731</a> <b><i> *  address, they are probably intending to talk to us, so it saves time</i></b>
<a name="L732" href="source/net/ipv4/arp.c#L732">732</a> <b><i> *  if we cache their address.  Their address is also probably not in</i></b>
<a name="L733" href="source/net/ipv4/arp.c#L733">733</a> <b><i> *  our cache, since ours is not in their cache.)</i></b>
<a name="L734" href="source/net/ipv4/arp.c#L734">734</a> <b><i> *</i></b>
<a name="L735" href="source/net/ipv4/arp.c#L735">735</a> <b><i> *  Putting this another way, we only care about replies if they are to</i></b>
<a name="L736" href="source/net/ipv4/arp.c#L736">736</a> <b><i> *  us, in which case we add them to the cache.  For requests, we care</i></b>
<a name="L737" href="source/net/ipv4/arp.c#L737">737</a> <b><i> *  about those for us and those for our proxies.  We reply to both,</i></b>
<a name="L738" href="source/net/ipv4/arp.c#L738">738</a> <b><i> *  and in the case of requests for us we add the requester to the arp</i></b>
<a name="L739" href="source/net/ipv4/arp.c#L739">739</a> <b><i> *  cache.</i></b>
<a name="L740" href="source/net/ipv4/arp.c#L740">740</a> <b><i> */</i></b>
<a name="L741" href="source/net/ipv4/arp.c#L741">741</a> 
<a name="L742" href="source/net/ipv4/arp.c#L742">742</a>         <b><i>/* Special case: IPv4 duplicate address detection packet (RFC2131) */</i></b>
<a name="L743" href="source/net/ipv4/arp.c#L743">743</a>         if (sip == 0) {
<a name="L744" href="source/net/ipv4/arp.c#L744">744</a>                 if (arp-&gt;ar_op == <a href="ident?i=htons">htons</a>(<a href="ident?i=ARPOP_REQUEST">ARPOP_REQUEST</a>) &amp;&amp;
<a name="L745" href="source/net/ipv4/arp.c#L745">745</a>                     <a href="ident?i=inet_addr_type">inet_addr_type</a>(<a href="ident?i=net">net</a>, tip) == RTN_LOCAL &amp;&amp;
<a name="L746" href="source/net/ipv4/arp.c#L746">746</a>                     !<a href="ident?i=arp_ignore">arp_ignore</a>(in_dev, sip, tip))
<a name="L747" href="source/net/ipv4/arp.c#L747">747</a>                         <a href="ident?i=arp_send">arp_send</a>(<a href="ident?i=ARPOP_REPLY">ARPOP_REPLY</a>, <a href="ident?i=ETH_P_ARP">ETH_P_ARP</a>, sip, <a href="ident?i=dev">dev</a>, tip, <a href="ident?i=sha">sha</a>,
<a name="L748" href="source/net/ipv4/arp.c#L748">748</a>                                  <a href="ident?i=dev">dev</a>-&gt;dev_addr, <a href="ident?i=sha">sha</a>);
<a name="L749" href="source/net/ipv4/arp.c#L749">749</a>                 goto <a href="ident?i=out">out</a>;
<a name="L750" href="source/net/ipv4/arp.c#L750">750</a>         }
<a name="L751" href="source/net/ipv4/arp.c#L751">751</a> 
<a name="L752" href="source/net/ipv4/arp.c#L752">752</a>         if (arp-&gt;ar_op == <a href="ident?i=htons">htons</a>(<a href="ident?i=ARPOP_REQUEST">ARPOP_REQUEST</a>) &amp;&amp;
<a name="L753" href="source/net/ipv4/arp.c#L753">753</a>             <a href="ident?i=ip_route_input_noref">ip_route_input_noref</a>(<a href="ident?i=skb">skb</a>, tip, sip, 0, <a href="ident?i=dev">dev</a>) == 0) {
<a name="L754" href="source/net/ipv4/arp.c#L754">754</a> 
<a name="L755" href="source/net/ipv4/arp.c#L755">755</a>                 <a href="ident?i=rt">rt</a> = <a href="ident?i=skb_rtable">skb_rtable</a>(<a href="ident?i=skb">skb</a>);
<a name="L756" href="source/net/ipv4/arp.c#L756">756</a>                 addr_type = <a href="ident?i=rt">rt</a>-&gt;rt_type;
<a name="L757" href="source/net/ipv4/arp.c#L757">757</a> 
<a name="L758" href="source/net/ipv4/arp.c#L758">758</a>                 if (addr_type == RTN_LOCAL) {
<a name="L759" href="source/net/ipv4/arp.c#L759">759</a>                         int dont_send;
<a name="L760" href="source/net/ipv4/arp.c#L760">760</a> 
<a name="L761" href="source/net/ipv4/arp.c#L761">761</a>                         dont_send = <a href="ident?i=arp_ignore">arp_ignore</a>(in_dev, sip, tip);
<a name="L762" href="source/net/ipv4/arp.c#L762">762</a>                         if (!dont_send &amp;&amp; <a href="ident?i=IN_DEV_ARPFILTER">IN_DEV_ARPFILTER</a>(in_dev))
<a name="L763" href="source/net/ipv4/arp.c#L763">763</a>                                 dont_send = <a href="ident?i=arp_filter">arp_filter</a>(sip, tip, <a href="ident?i=dev">dev</a>);
<a name="L764" href="source/net/ipv4/arp.c#L764">764</a>                         if (!dont_send) {
<a name="L765" href="source/net/ipv4/arp.c#L765">765</a>                                 <a href="ident?i=n">n</a> = <a href="ident?i=neigh_event_ns">neigh_event_ns</a>(&amp;<a href="ident?i=arp_tbl">arp_tbl</a>, <a href="ident?i=sha">sha</a>, &amp;sip, <a href="ident?i=dev">dev</a>);
<a name="L766" href="source/net/ipv4/arp.c#L766">766</a>                                 if (<a href="ident?i=n">n</a>) {
<a name="L767" href="source/net/ipv4/arp.c#L767">767</a>                                         <a href="ident?i=arp_send">arp_send</a>(<a href="ident?i=ARPOP_REPLY">ARPOP_REPLY</a>, <a href="ident?i=ETH_P_ARP">ETH_P_ARP</a>, sip,
<a name="L768" href="source/net/ipv4/arp.c#L768">768</a>                                                  <a href="ident?i=dev">dev</a>, tip, <a href="ident?i=sha">sha</a>, <a href="ident?i=dev">dev</a>-&gt;dev_addr,
<a name="L769" href="source/net/ipv4/arp.c#L769">769</a>                                                  <a href="ident?i=sha">sha</a>);
<a name="L770" href="source/net/ipv4/arp.c#L770">770</a>                                         <a href="ident?i=neigh_release">neigh_release</a>(<a href="ident?i=n">n</a>);
<a name="L771" href="source/net/ipv4/arp.c#L771">771</a>                                 }
<a name="L772" href="source/net/ipv4/arp.c#L772">772</a>                         }
<a name="L773" href="source/net/ipv4/arp.c#L773">773</a>                         goto <a href="ident?i=out">out</a>;
<a name="L774" href="source/net/ipv4/arp.c#L774">774</a>                 } else if (<a href="ident?i=IN_DEV_FORWARD">IN_DEV_FORWARD</a>(in_dev)) {
<a name="L775" href="source/net/ipv4/arp.c#L775">775</a>                         if (addr_type == RTN_UNICAST  &amp;&amp;
<a name="L776" href="source/net/ipv4/arp.c#L776">776</a>                             (<a href="ident?i=arp_fwd_proxy">arp_fwd_proxy</a>(in_dev, <a href="ident?i=dev">dev</a>, <a href="ident?i=rt">rt</a>) ||
<a name="L777" href="source/net/ipv4/arp.c#L777">777</a>                              <a href="ident?i=arp_fwd_pvlan">arp_fwd_pvlan</a>(in_dev, <a href="ident?i=dev">dev</a>, <a href="ident?i=rt">rt</a>, sip, tip) ||
<a name="L778" href="source/net/ipv4/arp.c#L778">778</a>                              (<a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>.<a href="ident?i=dev">dev</a> != <a href="ident?i=dev">dev</a> &amp;&amp;
<a name="L779" href="source/net/ipv4/arp.c#L779">779</a>                               <a href="ident?i=pneigh_lookup">pneigh_lookup</a>(&amp;<a href="ident?i=arp_tbl">arp_tbl</a>, <a href="ident?i=net">net</a>, &amp;tip, <a href="ident?i=dev">dev</a>, 0)))) {
<a name="L780" href="source/net/ipv4/arp.c#L780">780</a>                                 <a href="ident?i=n">n</a> = <a href="ident?i=neigh_event_ns">neigh_event_ns</a>(&amp;<a href="ident?i=arp_tbl">arp_tbl</a>, <a href="ident?i=sha">sha</a>, &amp;sip, <a href="ident?i=dev">dev</a>);
<a name="L781" href="source/net/ipv4/arp.c#L781">781</a>                                 if (<a href="ident?i=n">n</a>)
<a name="L782" href="source/net/ipv4/arp.c#L782">782</a>                                         <a href="ident?i=neigh_release">neigh_release</a>(<a href="ident?i=n">n</a>);
<a name="L783" href="source/net/ipv4/arp.c#L783">783</a> 
<a name="L784" href="source/net/ipv4/arp.c#L784">784</a>                                 if (<a href="ident?i=NEIGH_CB">NEIGH_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=LOCALLY_ENQUEUED">LOCALLY_ENQUEUED</a> ||
<a name="L785" href="source/net/ipv4/arp.c#L785">785</a>                                     <a href="ident?i=skb">skb</a>-&gt;pkt_type == <a href="ident?i=PACKET_HOST">PACKET_HOST</a> ||
<a name="L786" href="source/net/ipv4/arp.c#L786">786</a>                                     <a href="ident?i=NEIGH_VAR">NEIGH_VAR</a>(in_dev-&gt;arp_parms, PROXY_DELAY) == 0) {
<a name="L787" href="source/net/ipv4/arp.c#L787">787</a>                                         <a href="ident?i=arp_send">arp_send</a>(<a href="ident?i=ARPOP_REPLY">ARPOP_REPLY</a>, <a href="ident?i=ETH_P_ARP">ETH_P_ARP</a>, sip,
<a name="L788" href="source/net/ipv4/arp.c#L788">788</a>                                                  <a href="ident?i=dev">dev</a>, tip, <a href="ident?i=sha">sha</a>, <a href="ident?i=dev">dev</a>-&gt;dev_addr,
<a name="L789" href="source/net/ipv4/arp.c#L789">789</a>                                                  <a href="ident?i=sha">sha</a>);
<a name="L790" href="source/net/ipv4/arp.c#L790">790</a>                                 } else {
<a name="L791" href="source/net/ipv4/arp.c#L791">791</a>                                         <a href="ident?i=pneigh_enqueue">pneigh_enqueue</a>(&amp;<a href="ident?i=arp_tbl">arp_tbl</a>,
<a name="L792" href="source/net/ipv4/arp.c#L792">792</a>                                                        in_dev-&gt;arp_parms, <a href="ident?i=skb">skb</a>);
<a name="L793" href="source/net/ipv4/arp.c#L793">793</a>                                         return 0;
<a name="L794" href="source/net/ipv4/arp.c#L794">794</a>                                 }
<a name="L795" href="source/net/ipv4/arp.c#L795">795</a>                                 goto <a href="ident?i=out">out</a>;
<a name="L796" href="source/net/ipv4/arp.c#L796">796</a>                         }
<a name="L797" href="source/net/ipv4/arp.c#L797">797</a>                 }
<a name="L798" href="source/net/ipv4/arp.c#L798">798</a>         }
<a name="L799" href="source/net/ipv4/arp.c#L799">799</a> 
<a name="L800" href="source/net/ipv4/arp.c#L800">800</a>         <b><i>/* Update our ARP tables */</i></b>
<a name="L801" href="source/net/ipv4/arp.c#L801">801</a> 
<a name="L802" href="source/net/ipv4/arp.c#L802">802</a>         <a href="ident?i=n">n</a> = <a href="ident?i=__neigh_lookup">__neigh_lookup</a>(&amp;<a href="ident?i=arp_tbl">arp_tbl</a>, &amp;sip, <a href="ident?i=dev">dev</a>, 0);
<a name="L803" href="source/net/ipv4/arp.c#L803">803</a> 
<a name="L804" href="source/net/ipv4/arp.c#L804">804</a>         if (<a href="ident?i=IN_DEV_ARP_ACCEPT">IN_DEV_ARP_ACCEPT</a>(in_dev)) {
<a name="L805" href="source/net/ipv4/arp.c#L805">805</a>                 <b><i>/* Unsolicited ARP is not accepted by default.</i></b>
<a name="L806" href="source/net/ipv4/arp.c#L806">806</a> <b><i>                   It is possible, that this option should be enabled for some</i></b>
<a name="L807" href="source/net/ipv4/arp.c#L807">807</a> <b><i>                   devices (strip is candidate)</i></b>
<a name="L808" href="source/net/ipv4/arp.c#L808">808</a> <b><i>                 */</i></b>
<a name="L809" href="source/net/ipv4/arp.c#L809">809</a>                 is_garp = arp-&gt;ar_op == <a href="ident?i=htons">htons</a>(<a href="ident?i=ARPOP_REQUEST">ARPOP_REQUEST</a>) &amp;&amp; tip == sip &amp;&amp;
<a name="L810" href="source/net/ipv4/arp.c#L810">810</a>                           <a href="ident?i=inet_addr_type">inet_addr_type</a>(<a href="ident?i=net">net</a>, sip) == RTN_UNICAST;
<a name="L811" href="source/net/ipv4/arp.c#L811">811</a> 
<a name="L812" href="source/net/ipv4/arp.c#L812">812</a>                 if (!<a href="ident?i=n">n</a> &amp;&amp;
<a name="L813" href="source/net/ipv4/arp.c#L813">813</a>                     ((arp-&gt;ar_op == <a href="ident?i=htons">htons</a>(<a href="ident?i=ARPOP_REPLY">ARPOP_REPLY</a>)  &amp;&amp;
<a name="L814" href="source/net/ipv4/arp.c#L814">814</a>                       <a href="ident?i=inet_addr_type">inet_addr_type</a>(<a href="ident?i=net">net</a>, sip) == RTN_UNICAST) || is_garp))
<a name="L815" href="source/net/ipv4/arp.c#L815">815</a>                         <a href="ident?i=n">n</a> = <a href="ident?i=__neigh_lookup">__neigh_lookup</a>(&amp;<a href="ident?i=arp_tbl">arp_tbl</a>, &amp;sip, <a href="ident?i=dev">dev</a>, 1);
<a name="L816" href="source/net/ipv4/arp.c#L816">816</a>         }
<a name="L817" href="source/net/ipv4/arp.c#L817">817</a> 
<a name="L818" href="source/net/ipv4/arp.c#L818">818</a>         if (<a href="ident?i=n">n</a>) {
<a name="L819" href="source/net/ipv4/arp.c#L819">819</a>                 int <a href="ident?i=state">state</a> = <a href="ident?i=NUD_REACHABLE">NUD_REACHABLE</a>;
<a name="L820" href="source/net/ipv4/arp.c#L820">820</a>                 int <a href="ident?i=override">override</a>;
<a name="L821" href="source/net/ipv4/arp.c#L821">821</a> 
<a name="L822" href="source/net/ipv4/arp.c#L822">822</a>                 <b><i>/* If several different ARP replies follows back-to-back,</i></b>
<a name="L823" href="source/net/ipv4/arp.c#L823">823</a> <b><i>                   use the FIRST one. It is possible, if several proxy</i></b>
<a name="L824" href="source/net/ipv4/arp.c#L824">824</a> <b><i>                   agents are active. Taking the first reply prevents</i></b>
<a name="L825" href="source/net/ipv4/arp.c#L825">825</a> <b><i>                   arp trashing and chooses the fastest router.</i></b>
<a name="L826" href="source/net/ipv4/arp.c#L826">826</a> <b><i>                 */</i></b>
<a name="L827" href="source/net/ipv4/arp.c#L827">827</a>                 <a href="ident?i=override">override</a> = <a href="ident?i=time_after">time_after</a>(<a href="ident?i=jiffies">jiffies</a>,
<a name="L828" href="source/net/ipv4/arp.c#L828">828</a>                                       <a href="ident?i=n">n</a>-&gt;updated +
<a name="L829" href="source/net/ipv4/arp.c#L829">829</a>                                       <a href="ident?i=NEIGH_VAR">NEIGH_VAR</a>(<a href="ident?i=n">n</a>-&gt;<a href="ident?i=parms">parms</a>, <a href="ident?i=LOCKTIME">LOCKTIME</a>)) ||
<a name="L830" href="source/net/ipv4/arp.c#L830">830</a>                            is_garp;
<a name="L831" href="source/net/ipv4/arp.c#L831">831</a> 
<a name="L832" href="source/net/ipv4/arp.c#L832">832</a>                 <b><i>/* Broadcast replies and request packets</i></b>
<a name="L833" href="source/net/ipv4/arp.c#L833">833</a> <b><i>                   do not assert neighbour reachability.</i></b>
<a name="L834" href="source/net/ipv4/arp.c#L834">834</a> <b><i>                 */</i></b>
<a name="L835" href="source/net/ipv4/arp.c#L835">835</a>                 if (arp-&gt;ar_op != <a href="ident?i=htons">htons</a>(<a href="ident?i=ARPOP_REPLY">ARPOP_REPLY</a>) ||
<a name="L836" href="source/net/ipv4/arp.c#L836">836</a>                     <a href="ident?i=skb">skb</a>-&gt;pkt_type != <a href="ident?i=PACKET_HOST">PACKET_HOST</a>)
<a name="L837" href="source/net/ipv4/arp.c#L837">837</a>                         <a href="ident?i=state">state</a> = <a href="ident?i=NUD_STALE">NUD_STALE</a>;
<a name="L838" href="source/net/ipv4/arp.c#L838">838</a>                 <a href="ident?i=neigh_update">neigh_update</a>(<a href="ident?i=n">n</a>, <a href="ident?i=sha">sha</a>, <a href="ident?i=state">state</a>,
<a name="L839" href="source/net/ipv4/arp.c#L839">839</a>                              <a href="ident?i=override">override</a> ? <a href="ident?i=NEIGH_UPDATE_F_OVERRIDE">NEIGH_UPDATE_F_OVERRIDE</a> : 0);
<a name="L840" href="source/net/ipv4/arp.c#L840">840</a>                 <a href="ident?i=neigh_release">neigh_release</a>(<a href="ident?i=n">n</a>);
<a name="L841" href="source/net/ipv4/arp.c#L841">841</a>         }
<a name="L842" href="source/net/ipv4/arp.c#L842">842</a> 
<a name="L843" href="source/net/ipv4/arp.c#L843">843</a> <a href="ident?i=out">out</a>:
<a name="L844" href="source/net/ipv4/arp.c#L844">844</a>         <a href="ident?i=consume_skb">consume_skb</a>(<a href="ident?i=skb">skb</a>);
<a name="L845" href="source/net/ipv4/arp.c#L845">845</a>         return 0;
<a name="L846" href="source/net/ipv4/arp.c#L846">846</a> }
<a name="L847" href="source/net/ipv4/arp.c#L847">847</a> 
<a name="L848" href="source/net/ipv4/arp.c#L848">848</a> static void <a href="ident?i=parp_redo">parp_redo</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L849" href="source/net/ipv4/arp.c#L849">849</a> {
<a name="L850" href="source/net/ipv4/arp.c#L850">850</a>         <a href="ident?i=arp_process">arp_process</a>(<a href="ident?i=NULL">NULL</a>, <a href="ident?i=skb">skb</a>);
<a name="L851" href="source/net/ipv4/arp.c#L851">851</a> }
<a name="L852" href="source/net/ipv4/arp.c#L852">852</a> 
<a name="L853" href="source/net/ipv4/arp.c#L853">853</a> 
<a name="L854" href="source/net/ipv4/arp.c#L854">854</a> <b><i>/*</i></b>
<a name="L855" href="source/net/ipv4/arp.c#L855">855</a> <b><i> *      Receive an arp request from the device layer.</i></b>
<a name="L856" href="source/net/ipv4/arp.c#L856">856</a> <b><i> */</i></b>
<a name="L857" href="source/net/ipv4/arp.c#L857">857</a> 
<a name="L858" href="source/net/ipv4/arp.c#L858">858</a> static int <a href="ident?i=arp_rcv">arp_rcv</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>,
<a name="L859" href="source/net/ipv4/arp.c#L859">859</a>                    struct <a href="ident?i=packet_type">packet_type</a> *<a href="ident?i=pt">pt</a>, struct <a href="ident?i=net_device">net_device</a> *orig_dev)
<a name="L860" href="source/net/ipv4/arp.c#L860">860</a> {
<a name="L861" href="source/net/ipv4/arp.c#L861">861</a>         const struct <a href="ident?i=arphdr">arphdr</a> *arp;
<a name="L862" href="source/net/ipv4/arp.c#L862">862</a> 
<a name="L863" href="source/net/ipv4/arp.c#L863">863</a>         <b><i>/* do not tweak dropwatch on an ARP we will ignore */</i></b>
<a name="L864" href="source/net/ipv4/arp.c#L864">864</a>         if (<a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=IFF_NOARP">IFF_NOARP</a> ||
<a name="L865" href="source/net/ipv4/arp.c#L865">865</a>             <a href="ident?i=skb">skb</a>-&gt;pkt_type == <a href="ident?i=PACKET_OTHERHOST">PACKET_OTHERHOST</a> ||
<a name="L866" href="source/net/ipv4/arp.c#L866">866</a>             <a href="ident?i=skb">skb</a>-&gt;pkt_type == <a href="ident?i=PACKET_LOOPBACK">PACKET_LOOPBACK</a>)
<a name="L867" href="source/net/ipv4/arp.c#L867">867</a>                 goto consumeskb;
<a name="L868" href="source/net/ipv4/arp.c#L868">868</a> 
<a name="L869" href="source/net/ipv4/arp.c#L869">869</a>         <a href="ident?i=skb">skb</a> = <a href="ident?i=skb_share_check">skb_share_check</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=GFP_ATOMIC">GFP_ATOMIC</a>);
<a name="L870" href="source/net/ipv4/arp.c#L870">870</a>         if (!<a href="ident?i=skb">skb</a>)
<a name="L871" href="source/net/ipv4/arp.c#L871">871</a>                 goto out_of_mem;
<a name="L872" href="source/net/ipv4/arp.c#L872">872</a> 
<a name="L873" href="source/net/ipv4/arp.c#L873">873</a>         <b><i>/* ARP header, plus 2 device addresses, plus 2 IP addresses.  */</i></b>
<a name="L874" href="source/net/ipv4/arp.c#L874">874</a>         if (!<a href="ident?i=pskb_may_pull">pskb_may_pull</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=arp_hdr_len">arp_hdr_len</a>(<a href="ident?i=dev">dev</a>)))
<a name="L875" href="source/net/ipv4/arp.c#L875">875</a>                 goto freeskb;
<a name="L876" href="source/net/ipv4/arp.c#L876">876</a> 
<a name="L877" href="source/net/ipv4/arp.c#L877">877</a>         arp = <a href="ident?i=arp_hdr">arp_hdr</a>(<a href="ident?i=skb">skb</a>);
<a name="L878" href="source/net/ipv4/arp.c#L878">878</a>         if (arp-&gt;ar_hln != <a href="ident?i=dev">dev</a>-&gt;addr_len || arp-&gt;ar_pln != 4)
<a name="L879" href="source/net/ipv4/arp.c#L879">879</a>                 goto freeskb;
<a name="L880" href="source/net/ipv4/arp.c#L880">880</a> 
<a name="L881" href="source/net/ipv4/arp.c#L881">881</a>         <a href="ident?i=memset">memset</a>(<a href="ident?i=NEIGH_CB">NEIGH_CB</a>(<a href="ident?i=skb">skb</a>), 0, sizeof(struct <a href="ident?i=neighbour_cb">neighbour_cb</a>));
<a name="L882" href="source/net/ipv4/arp.c#L882">882</a> 
<a name="L883" href="source/net/ipv4/arp.c#L883">883</a>         return <a href="ident?i=NF_HOOK">NF_HOOK</a>(NFPROTO_ARP, <a href="ident?i=NF_ARP_IN">NF_ARP_IN</a>, <a href="ident?i=NULL">NULL</a>, <a href="ident?i=skb">skb</a>,
<a name="L884" href="source/net/ipv4/arp.c#L884">884</a>                        <a href="ident?i=dev">dev</a>, <a href="ident?i=NULL">NULL</a>, <a href="ident?i=arp_process">arp_process</a>);
<a name="L885" href="source/net/ipv4/arp.c#L885">885</a> 
<a name="L886" href="source/net/ipv4/arp.c#L886">886</a> consumeskb:
<a name="L887" href="source/net/ipv4/arp.c#L887">887</a>         <a href="ident?i=consume_skb">consume_skb</a>(<a href="ident?i=skb">skb</a>);
<a name="L888" href="source/net/ipv4/arp.c#L888">888</a>         return 0;
<a name="L889" href="source/net/ipv4/arp.c#L889">889</a> freeskb:
<a name="L890" href="source/net/ipv4/arp.c#L890">890</a>         <a href="ident?i=kfree_skb">kfree_skb</a>(<a href="ident?i=skb">skb</a>);
<a name="L891" href="source/net/ipv4/arp.c#L891">891</a> out_of_mem:
<a name="L892" href="source/net/ipv4/arp.c#L892">892</a>         return 0;
<a name="L893" href="source/net/ipv4/arp.c#L893">893</a> }
<a name="L894" href="source/net/ipv4/arp.c#L894">894</a> 
<a name="L895" href="source/net/ipv4/arp.c#L895">895</a> <b><i>/*</i></b>
<a name="L896" href="source/net/ipv4/arp.c#L896">896</a> <b><i> *      User level interface (ioctl)</i></b>
<a name="L897" href="source/net/ipv4/arp.c#L897">897</a> <b><i> */</i></b>
<a name="L898" href="source/net/ipv4/arp.c#L898">898</a> 
<a name="L899" href="source/net/ipv4/arp.c#L899">899</a> <b><i>/*</i></b>
<a name="L900" href="source/net/ipv4/arp.c#L900">900</a> <b><i> *      Set (create) an ARP cache entry.</i></b>
<a name="L901" href="source/net/ipv4/arp.c#L901">901</a> <b><i> */</i></b>
<a name="L902" href="source/net/ipv4/arp.c#L902">902</a> 
<a name="L903" href="source/net/ipv4/arp.c#L903">903</a> static int <a href="ident?i=arp_req_set_proxy">arp_req_set_proxy</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>, struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>, int <a href="ident?i=on">on</a>)
<a name="L904" href="source/net/ipv4/arp.c#L904">904</a> {
<a name="L905" href="source/net/ipv4/arp.c#L905">905</a>         if (!<a href="ident?i=dev">dev</a>) {
<a name="L906" href="source/net/ipv4/arp.c#L906">906</a>                 <a href="ident?i=IPV4_DEVCONF_ALL">IPV4_DEVCONF_ALL</a>(<a href="ident?i=net">net</a>, PROXY_ARP) = <a href="ident?i=on">on</a>;
<a name="L907" href="source/net/ipv4/arp.c#L907">907</a>                 return 0;
<a name="L908" href="source/net/ipv4/arp.c#L908">908</a>         }
<a name="L909" href="source/net/ipv4/arp.c#L909">909</a>         if (<a href="ident?i=__in_dev_get_rtnl">__in_dev_get_rtnl</a>(<a href="ident?i=dev">dev</a>)) {
<a name="L910" href="source/net/ipv4/arp.c#L910">910</a>                 <a href="ident?i=IN_DEV_CONF_SET">IN_DEV_CONF_SET</a>(<a href="ident?i=__in_dev_get_rtnl">__in_dev_get_rtnl</a>(<a href="ident?i=dev">dev</a>), PROXY_ARP, <a href="ident?i=on">on</a>);
<a name="L911" href="source/net/ipv4/arp.c#L911">911</a>                 return 0;
<a name="L912" href="source/net/ipv4/arp.c#L912">912</a>         }
<a name="L913" href="source/net/ipv4/arp.c#L913">913</a>         return -<a href="ident?i=ENXIO">ENXIO</a>;
<a name="L914" href="source/net/ipv4/arp.c#L914">914</a> }
<a name="L915" href="source/net/ipv4/arp.c#L915">915</a> 
<a name="L916" href="source/net/ipv4/arp.c#L916">916</a> static int <a href="ident?i=arp_req_set_public">arp_req_set_public</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>, struct <a href="ident?i=arpreq">arpreq</a> *<a href="ident?i=r">r</a>,
<a name="L917" href="source/net/ipv4/arp.c#L917">917</a>                 struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>)
<a name="L918" href="source/net/ipv4/arp.c#L918">918</a> {
<a name="L919" href="source/net/ipv4/arp.c#L919">919</a>         <a href="ident?i=__be32">__be32</a> <a href="ident?i=ip">ip</a> = ((struct <a href="ident?i=sockaddr_in">sockaddr_in</a> *)&amp;<a href="ident?i=r">r</a>-&gt;arp_pa)-&gt;sin_addr.s_addr;
<a name="L920" href="source/net/ipv4/arp.c#L920">920</a>         <a href="ident?i=__be32">__be32</a> <a href="ident?i=mask">mask</a> = ((struct <a href="ident?i=sockaddr_in">sockaddr_in</a> *)&amp;<a href="ident?i=r">r</a>-&gt;arp_netmask)-&gt;sin_addr.s_addr;
<a name="L921" href="source/net/ipv4/arp.c#L921">921</a> 
<a name="L922" href="source/net/ipv4/arp.c#L922">922</a>         if (<a href="ident?i=mask">mask</a> &amp;&amp; <a href="ident?i=mask">mask</a> != <a href="ident?i=htonl">htonl</a>(0xFFFFFFFF))
<a name="L923" href="source/net/ipv4/arp.c#L923">923</a>                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L924" href="source/net/ipv4/arp.c#L924">924</a>         if (!<a href="ident?i=dev">dev</a> &amp;&amp; (<a href="ident?i=r">r</a>-&gt;arp_flags &amp; <a href="ident?i=ATF_COM">ATF_COM</a>)) {
<a name="L925" href="source/net/ipv4/arp.c#L925">925</a>                 <a href="ident?i=dev">dev</a> = <a href="ident?i=dev_getbyhwaddr_rcu">dev_getbyhwaddr_rcu</a>(<a href="ident?i=net">net</a>, <a href="ident?i=r">r</a>-&gt;arp_ha.sa_family,
<a name="L926" href="source/net/ipv4/arp.c#L926">926</a>                                       <a href="ident?i=r">r</a>-&gt;arp_ha.sa_data);
<a name="L927" href="source/net/ipv4/arp.c#L927">927</a>                 if (!<a href="ident?i=dev">dev</a>)
<a name="L928" href="source/net/ipv4/arp.c#L928">928</a>                         return -<a href="ident?i=ENODEV">ENODEV</a>;
<a name="L929" href="source/net/ipv4/arp.c#L929">929</a>         }
<a name="L930" href="source/net/ipv4/arp.c#L930">930</a>         if (<a href="ident?i=mask">mask</a>) {
<a name="L931" href="source/net/ipv4/arp.c#L931">931</a>                 if (!<a href="ident?i=pneigh_lookup">pneigh_lookup</a>(&amp;<a href="ident?i=arp_tbl">arp_tbl</a>, <a href="ident?i=net">net</a>, &amp;<a href="ident?i=ip">ip</a>, <a href="ident?i=dev">dev</a>, 1))
<a name="L932" href="source/net/ipv4/arp.c#L932">932</a>                         return -<a href="ident?i=ENOBUFS">ENOBUFS</a>;
<a name="L933" href="source/net/ipv4/arp.c#L933">933</a>                 return 0;
<a name="L934" href="source/net/ipv4/arp.c#L934">934</a>         }
<a name="L935" href="source/net/ipv4/arp.c#L935">935</a> 
<a name="L936" href="source/net/ipv4/arp.c#L936">936</a>         return <a href="ident?i=arp_req_set_proxy">arp_req_set_proxy</a>(<a href="ident?i=net">net</a>, <a href="ident?i=dev">dev</a>, 1);
<a name="L937" href="source/net/ipv4/arp.c#L937">937</a> }
<a name="L938" href="source/net/ipv4/arp.c#L938">938</a> 
<a name="L939" href="source/net/ipv4/arp.c#L939">939</a> static int <a href="ident?i=arp_req_set">arp_req_set</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>, struct <a href="ident?i=arpreq">arpreq</a> *<a href="ident?i=r">r</a>,
<a name="L940" href="source/net/ipv4/arp.c#L940">940</a>                        struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>)
<a name="L941" href="source/net/ipv4/arp.c#L941">941</a> {
<a name="L942" href="source/net/ipv4/arp.c#L942">942</a>         <a href="ident?i=__be32">__be32</a> <a href="ident?i=ip">ip</a>;
<a name="L943" href="source/net/ipv4/arp.c#L943">943</a>         struct <a href="ident?i=neighbour">neighbour</a> *neigh;
<a name="L944" href="source/net/ipv4/arp.c#L944">944</a>         int <a href="ident?i=err">err</a>;
<a name="L945" href="source/net/ipv4/arp.c#L945">945</a> 
<a name="L946" href="source/net/ipv4/arp.c#L946">946</a>         if (<a href="ident?i=r">r</a>-&gt;arp_flags &amp; <a href="ident?i=ATF_PUBL">ATF_PUBL</a>)
<a name="L947" href="source/net/ipv4/arp.c#L947">947</a>                 return <a href="ident?i=arp_req_set_public">arp_req_set_public</a>(<a href="ident?i=net">net</a>, <a href="ident?i=r">r</a>, <a href="ident?i=dev">dev</a>);
<a name="L948" href="source/net/ipv4/arp.c#L948">948</a> 
<a name="L949" href="source/net/ipv4/arp.c#L949">949</a>         <a href="ident?i=ip">ip</a> = ((struct <a href="ident?i=sockaddr_in">sockaddr_in</a> *)&amp;<a href="ident?i=r">r</a>-&gt;arp_pa)-&gt;sin_addr.s_addr;
<a name="L950" href="source/net/ipv4/arp.c#L950">950</a>         if (<a href="ident?i=r">r</a>-&gt;arp_flags &amp; <a href="ident?i=ATF_PERM">ATF_PERM</a>)
<a name="L951" href="source/net/ipv4/arp.c#L951">951</a>                 <a href="ident?i=r">r</a>-&gt;arp_flags |= <a href="ident?i=ATF_COM">ATF_COM</a>;
<a name="L952" href="source/net/ipv4/arp.c#L952">952</a>         if (!<a href="ident?i=dev">dev</a>) {
<a name="L953" href="source/net/ipv4/arp.c#L953">953</a>                 struct <a href="ident?i=rtable">rtable</a> *<a href="ident?i=rt">rt</a> = <a href="ident?i=ip_route_output">ip_route_output</a>(<a href="ident?i=net">net</a>, <a href="ident?i=ip">ip</a>, 0, <a href="ident?i=RTO_ONLINK">RTO_ONLINK</a>, 0);
<a name="L954" href="source/net/ipv4/arp.c#L954">954</a> 
<a name="L955" href="source/net/ipv4/arp.c#L955">955</a>                 if (<a href="ident?i=IS_ERR">IS_ERR</a>(<a href="ident?i=rt">rt</a>))
<a name="L956" href="source/net/ipv4/arp.c#L956">956</a>                         return <a href="ident?i=PTR_ERR">PTR_ERR</a>(<a href="ident?i=rt">rt</a>);
<a name="L957" href="source/net/ipv4/arp.c#L957">957</a>                 <a href="ident?i=dev">dev</a> = <a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>.<a href="ident?i=dev">dev</a>;
<a name="L958" href="source/net/ipv4/arp.c#L958">958</a>                 <a href="ident?i=ip_rt_put">ip_rt_put</a>(<a href="ident?i=rt">rt</a>);
<a name="L959" href="source/net/ipv4/arp.c#L959">959</a>                 if (!<a href="ident?i=dev">dev</a>)
<a name="L960" href="source/net/ipv4/arp.c#L960">960</a>                         return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L961" href="source/net/ipv4/arp.c#L961">961</a>         }
<a name="L962" href="source/net/ipv4/arp.c#L962">962</a>         switch (<a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=type">type</a>) {
<a name="L963" href="source/net/ipv4/arp.c#L963">963</a> #if <a href="ident?i=IS_ENABLED">IS_ENABLED</a>(CONFIG_FDDI)
<a name="L964" href="source/net/ipv4/arp.c#L964">964</a>         case <a href="ident?i=ARPHRD_FDDI">ARPHRD_FDDI</a>:
<a name="L965" href="source/net/ipv4/arp.c#L965">965</a>                 <b><i>/*</i></b>
<a name="L966" href="source/net/ipv4/arp.c#L966">966</a> <b><i>                 * According to RFC 1390, FDDI devices should accept ARP</i></b>
<a name="L967" href="source/net/ipv4/arp.c#L967">967</a> <b><i>                 * hardware types of 1 (Ethernet).  However, to be more</i></b>
<a name="L968" href="source/net/ipv4/arp.c#L968">968</a> <b><i>                 * robust, we'll accept hardware types of either 1 (Ethernet)</i></b>
<a name="L969" href="source/net/ipv4/arp.c#L969">969</a> <b><i>                 * or 6 (IEEE 802.2).</i></b>
<a name="L970" href="source/net/ipv4/arp.c#L970">970</a> <b><i>                 */</i></b>
<a name="L971" href="source/net/ipv4/arp.c#L971">971</a>                 if (<a href="ident?i=r">r</a>-&gt;arp_ha.sa_family != <a href="ident?i=ARPHRD_FDDI">ARPHRD_FDDI</a> &amp;&amp;
<a name="L972" href="source/net/ipv4/arp.c#L972">972</a>                     <a href="ident?i=r">r</a>-&gt;arp_ha.sa_family != <a href="ident?i=ARPHRD_ETHER">ARPHRD_ETHER</a> &amp;&amp;
<a name="L973" href="source/net/ipv4/arp.c#L973">973</a>                     <a href="ident?i=r">r</a>-&gt;arp_ha.sa_family != <a href="ident?i=ARPHRD_IEEE802">ARPHRD_IEEE802</a>)
<a name="L974" href="source/net/ipv4/arp.c#L974">974</a>                         return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L975" href="source/net/ipv4/arp.c#L975">975</a>                 break;
<a name="L976" href="source/net/ipv4/arp.c#L976">976</a> #endif
<a name="L977" href="source/net/ipv4/arp.c#L977">977</a>         default:
<a name="L978" href="source/net/ipv4/arp.c#L978">978</a>                 if (<a href="ident?i=r">r</a>-&gt;arp_ha.sa_family != <a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=type">type</a>)
<a name="L979" href="source/net/ipv4/arp.c#L979">979</a>                         return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L980" href="source/net/ipv4/arp.c#L980">980</a>                 break;
<a name="L981" href="source/net/ipv4/arp.c#L981">981</a>         }
<a name="L982" href="source/net/ipv4/arp.c#L982">982</a> 
<a name="L983" href="source/net/ipv4/arp.c#L983">983</a>         neigh = <a href="ident?i=__neigh_lookup_errno">__neigh_lookup_errno</a>(&amp;<a href="ident?i=arp_tbl">arp_tbl</a>, &amp;<a href="ident?i=ip">ip</a>, <a href="ident?i=dev">dev</a>);
<a name="L984" href="source/net/ipv4/arp.c#L984">984</a>         <a href="ident?i=err">err</a> = <a href="ident?i=PTR_ERR">PTR_ERR</a>(neigh);
<a name="L985" href="source/net/ipv4/arp.c#L985">985</a>         if (!<a href="ident?i=IS_ERR">IS_ERR</a>(neigh)) {
<a name="L986" href="source/net/ipv4/arp.c#L986">986</a>                 unsigned int <a href="ident?i=state">state</a> = <a href="ident?i=NUD_STALE">NUD_STALE</a>;
<a name="L987" href="source/net/ipv4/arp.c#L987">987</a>                 if (<a href="ident?i=r">r</a>-&gt;arp_flags &amp; <a href="ident?i=ATF_PERM">ATF_PERM</a>)
<a name="L988" href="source/net/ipv4/arp.c#L988">988</a>                         <a href="ident?i=state">state</a> = <a href="ident?i=NUD_PERMANENT">NUD_PERMANENT</a>;
<a name="L989" href="source/net/ipv4/arp.c#L989">989</a>                 <a href="ident?i=err">err</a> = <a href="ident?i=neigh_update">neigh_update</a>(neigh, (<a href="ident?i=r">r</a>-&gt;arp_flags &amp; <a href="ident?i=ATF_COM">ATF_COM</a>) ?
<a name="L990" href="source/net/ipv4/arp.c#L990">990</a>                                    <a href="ident?i=r">r</a>-&gt;arp_ha.sa_data : <a href="ident?i=NULL">NULL</a>, <a href="ident?i=state">state</a>,
<a name="L991" href="source/net/ipv4/arp.c#L991">991</a>                                    <a href="ident?i=NEIGH_UPDATE_F_OVERRIDE">NEIGH_UPDATE_F_OVERRIDE</a> |
<a name="L992" href="source/net/ipv4/arp.c#L992">992</a>                                    <a href="ident?i=NEIGH_UPDATE_F_ADMIN">NEIGH_UPDATE_F_ADMIN</a>);
<a name="L993" href="source/net/ipv4/arp.c#L993">993</a>                 <a href="ident?i=neigh_release">neigh_release</a>(neigh);
<a name="L994" href="source/net/ipv4/arp.c#L994">994</a>         }
<a name="L995" href="source/net/ipv4/arp.c#L995">995</a>         return <a href="ident?i=err">err</a>;
<a name="L996" href="source/net/ipv4/arp.c#L996">996</a> }
<a name="L997" href="source/net/ipv4/arp.c#L997">997</a> 
<a name="L998" href="source/net/ipv4/arp.c#L998">998</a> static unsigned int <a href="ident?i=arp_state_to_flags">arp_state_to_flags</a>(struct <a href="ident?i=neighbour">neighbour</a> *neigh)
<a name="L999" href="source/net/ipv4/arp.c#L999">999</a> {
<a name="L1000" href="source/net/ipv4/arp.c#L1000">1000</a>         if (neigh-&gt;nud_state&amp;<a href="ident?i=NUD_PERMANENT">NUD_PERMANENT</a>)
<a name="L1001" href="source/net/ipv4/arp.c#L1001">1001</a>                 return <a href="ident?i=ATF_PERM">ATF_PERM</a> | <a href="ident?i=ATF_COM">ATF_COM</a>;
<a name="L1002" href="source/net/ipv4/arp.c#L1002">1002</a>         else if (neigh-&gt;nud_state&amp;<a href="ident?i=NUD_VALID">NUD_VALID</a>)
<a name="L1003" href="source/net/ipv4/arp.c#L1003">1003</a>                 return <a href="ident?i=ATF_COM">ATF_COM</a>;
<a name="L1004" href="source/net/ipv4/arp.c#L1004">1004</a>         else
<a name="L1005" href="source/net/ipv4/arp.c#L1005">1005</a>                 return 0;
<a name="L1006" href="source/net/ipv4/arp.c#L1006">1006</a> }
<a name="L1007" href="source/net/ipv4/arp.c#L1007">1007</a> 
<a name="L1008" href="source/net/ipv4/arp.c#L1008">1008</a> <b><i>/*</i></b>
<a name="L1009" href="source/net/ipv4/arp.c#L1009">1009</a> <b><i> *      Get an ARP cache entry.</i></b>
<a name="L1010" href="source/net/ipv4/arp.c#L1010">1010</a> <b><i> */</i></b>
<a name="L1011" href="source/net/ipv4/arp.c#L1011">1011</a> 
<a name="L1012" href="source/net/ipv4/arp.c#L1012">1012</a> static int <a href="ident?i=arp_req_get">arp_req_get</a>(struct <a href="ident?i=arpreq">arpreq</a> *<a href="ident?i=r">r</a>, struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>)
<a name="L1013" href="source/net/ipv4/arp.c#L1013">1013</a> {
<a name="L1014" href="source/net/ipv4/arp.c#L1014">1014</a>         <a href="ident?i=__be32">__be32</a> <a href="ident?i=ip">ip</a> = ((struct <a href="ident?i=sockaddr_in">sockaddr_in</a> *) &amp;<a href="ident?i=r">r</a>-&gt;arp_pa)-&gt;sin_addr.s_addr;
<a name="L1015" href="source/net/ipv4/arp.c#L1015">1015</a>         struct <a href="ident?i=neighbour">neighbour</a> *neigh;
<a name="L1016" href="source/net/ipv4/arp.c#L1016">1016</a>         int <a href="ident?i=err">err</a> = -<a href="ident?i=ENXIO">ENXIO</a>;
<a name="L1017" href="source/net/ipv4/arp.c#L1017">1017</a> 
<a name="L1018" href="source/net/ipv4/arp.c#L1018">1018</a>         neigh = <a href="ident?i=neigh_lookup">neigh_lookup</a>(&amp;<a href="ident?i=arp_tbl">arp_tbl</a>, &amp;<a href="ident?i=ip">ip</a>, <a href="ident?i=dev">dev</a>);
<a name="L1019" href="source/net/ipv4/arp.c#L1019">1019</a>         if (neigh) {
<a name="L1020" href="source/net/ipv4/arp.c#L1020">1020</a>                 <a href="ident?i=read_lock_bh">read_lock_bh</a>(&amp;neigh-&gt;<a href="ident?i=lock">lock</a>);
<a name="L1021" href="source/net/ipv4/arp.c#L1021">1021</a>                 <a href="ident?i=memcpy">memcpy</a>(<a href="ident?i=r">r</a>-&gt;arp_ha.sa_data, neigh-&gt;ha, <a href="ident?i=dev">dev</a>-&gt;addr_len);
<a name="L1022" href="source/net/ipv4/arp.c#L1022">1022</a>                 <a href="ident?i=r">r</a>-&gt;arp_flags = <a href="ident?i=arp_state_to_flags">arp_state_to_flags</a>(neigh);
<a name="L1023" href="source/net/ipv4/arp.c#L1023">1023</a>                 <a href="ident?i=read_unlock_bh">read_unlock_bh</a>(&amp;neigh-&gt;<a href="ident?i=lock">lock</a>);
<a name="L1024" href="source/net/ipv4/arp.c#L1024">1024</a>                 <a href="ident?i=r">r</a>-&gt;arp_ha.sa_family = <a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=type">type</a>;
<a name="L1025" href="source/net/ipv4/arp.c#L1025">1025</a>                 <a href="ident?i=strlcpy">strlcpy</a>(<a href="ident?i=r">r</a>-&gt;arp_dev, <a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=name">name</a>, sizeof(<a href="ident?i=r">r</a>-&gt;arp_dev));
<a name="L1026" href="source/net/ipv4/arp.c#L1026">1026</a>                 <a href="ident?i=neigh_release">neigh_release</a>(neigh);
<a name="L1027" href="source/net/ipv4/arp.c#L1027">1027</a>                 <a href="ident?i=err">err</a> = 0;
<a name="L1028" href="source/net/ipv4/arp.c#L1028">1028</a>         }
<a name="L1029" href="source/net/ipv4/arp.c#L1029">1029</a>         return <a href="ident?i=err">err</a>;
<a name="L1030" href="source/net/ipv4/arp.c#L1030">1030</a> }
<a name="L1031" href="source/net/ipv4/arp.c#L1031">1031</a> 
<a name="L1032" href="source/net/ipv4/arp.c#L1032">1032</a> static int <a href="ident?i=arp_invalidate">arp_invalidate</a>(struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>, <a href="ident?i=__be32">__be32</a> <a href="ident?i=ip">ip</a>)
<a name="L1033" href="source/net/ipv4/arp.c#L1033">1033</a> {
<a name="L1034" href="source/net/ipv4/arp.c#L1034">1034</a>         struct <a href="ident?i=neighbour">neighbour</a> *neigh = <a href="ident?i=neigh_lookup">neigh_lookup</a>(&amp;<a href="ident?i=arp_tbl">arp_tbl</a>, &amp;<a href="ident?i=ip">ip</a>, <a href="ident?i=dev">dev</a>);
<a name="L1035" href="source/net/ipv4/arp.c#L1035">1035</a>         int <a href="ident?i=err">err</a> = -<a href="ident?i=ENXIO">ENXIO</a>;
<a name="L1036" href="source/net/ipv4/arp.c#L1036">1036</a> 
<a name="L1037" href="source/net/ipv4/arp.c#L1037">1037</a>         if (neigh) {
<a name="L1038" href="source/net/ipv4/arp.c#L1038">1038</a>                 if (neigh-&gt;nud_state &amp; ~NUD_NOARP)
<a name="L1039" href="source/net/ipv4/arp.c#L1039">1039</a>                         <a href="ident?i=err">err</a> = <a href="ident?i=neigh_update">neigh_update</a>(neigh, <a href="ident?i=NULL">NULL</a>, <a href="ident?i=NUD_FAILED">NUD_FAILED</a>,
<a name="L1040" href="source/net/ipv4/arp.c#L1040">1040</a>                                            <a href="ident?i=NEIGH_UPDATE_F_OVERRIDE">NEIGH_UPDATE_F_OVERRIDE</a>|
<a name="L1041" href="source/net/ipv4/arp.c#L1041">1041</a>                                            <a href="ident?i=NEIGH_UPDATE_F_ADMIN">NEIGH_UPDATE_F_ADMIN</a>);
<a name="L1042" href="source/net/ipv4/arp.c#L1042">1042</a>                 <a href="ident?i=neigh_release">neigh_release</a>(neigh);
<a name="L1043" href="source/net/ipv4/arp.c#L1043">1043</a>         }
<a name="L1044" href="source/net/ipv4/arp.c#L1044">1044</a> 
<a name="L1045" href="source/net/ipv4/arp.c#L1045">1045</a>         return <a href="ident?i=err">err</a>;
<a name="L1046" href="source/net/ipv4/arp.c#L1046">1046</a> }
<a name="L1047" href="source/net/ipv4/arp.c#L1047">1047</a> 
<a name="L1048" href="source/net/ipv4/arp.c#L1048">1048</a> static int <a href="ident?i=arp_req_delete_public">arp_req_delete_public</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>, struct <a href="ident?i=arpreq">arpreq</a> *<a href="ident?i=r">r</a>,
<a name="L1049" href="source/net/ipv4/arp.c#L1049">1049</a>                 struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>)
<a name="L1050" href="source/net/ipv4/arp.c#L1050">1050</a> {
<a name="L1051" href="source/net/ipv4/arp.c#L1051">1051</a>         <a href="ident?i=__be32">__be32</a> <a href="ident?i=ip">ip</a> = ((struct <a href="ident?i=sockaddr_in">sockaddr_in</a> *) &amp;<a href="ident?i=r">r</a>-&gt;arp_pa)-&gt;sin_addr.s_addr;
<a name="L1052" href="source/net/ipv4/arp.c#L1052">1052</a>         <a href="ident?i=__be32">__be32</a> <a href="ident?i=mask">mask</a> = ((struct <a href="ident?i=sockaddr_in">sockaddr_in</a> *)&amp;<a href="ident?i=r">r</a>-&gt;arp_netmask)-&gt;sin_addr.s_addr;
<a name="L1053" href="source/net/ipv4/arp.c#L1053">1053</a> 
<a name="L1054" href="source/net/ipv4/arp.c#L1054">1054</a>         if (<a href="ident?i=mask">mask</a> == <a href="ident?i=htonl">htonl</a>(0xFFFFFFFF))
<a name="L1055" href="source/net/ipv4/arp.c#L1055">1055</a>                 return <a href="ident?i=pneigh_delete">pneigh_delete</a>(&amp;<a href="ident?i=arp_tbl">arp_tbl</a>, <a href="ident?i=net">net</a>, &amp;<a href="ident?i=ip">ip</a>, <a href="ident?i=dev">dev</a>);
<a name="L1056" href="source/net/ipv4/arp.c#L1056">1056</a> 
<a name="L1057" href="source/net/ipv4/arp.c#L1057">1057</a>         if (<a href="ident?i=mask">mask</a>)
<a name="L1058" href="source/net/ipv4/arp.c#L1058">1058</a>                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L1059" href="source/net/ipv4/arp.c#L1059">1059</a> 
<a name="L1060" href="source/net/ipv4/arp.c#L1060">1060</a>         return <a href="ident?i=arp_req_set_proxy">arp_req_set_proxy</a>(<a href="ident?i=net">net</a>, <a href="ident?i=dev">dev</a>, 0);
<a name="L1061" href="source/net/ipv4/arp.c#L1061">1061</a> }
<a name="L1062" href="source/net/ipv4/arp.c#L1062">1062</a> 
<a name="L1063" href="source/net/ipv4/arp.c#L1063">1063</a> static int <a href="ident?i=arp_req_delete">arp_req_delete</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>, struct <a href="ident?i=arpreq">arpreq</a> *<a href="ident?i=r">r</a>,
<a name="L1064" href="source/net/ipv4/arp.c#L1064">1064</a>                           struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>)
<a name="L1065" href="source/net/ipv4/arp.c#L1065">1065</a> {
<a name="L1066" href="source/net/ipv4/arp.c#L1066">1066</a>         <a href="ident?i=__be32">__be32</a> <a href="ident?i=ip">ip</a>;
<a name="L1067" href="source/net/ipv4/arp.c#L1067">1067</a> 
<a name="L1068" href="source/net/ipv4/arp.c#L1068">1068</a>         if (<a href="ident?i=r">r</a>-&gt;arp_flags &amp; <a href="ident?i=ATF_PUBL">ATF_PUBL</a>)
<a name="L1069" href="source/net/ipv4/arp.c#L1069">1069</a>                 return <a href="ident?i=arp_req_delete_public">arp_req_delete_public</a>(<a href="ident?i=net">net</a>, <a href="ident?i=r">r</a>, <a href="ident?i=dev">dev</a>);
<a name="L1070" href="source/net/ipv4/arp.c#L1070">1070</a> 
<a name="L1071" href="source/net/ipv4/arp.c#L1071">1071</a>         <a href="ident?i=ip">ip</a> = ((struct <a href="ident?i=sockaddr_in">sockaddr_in</a> *)&amp;<a href="ident?i=r">r</a>-&gt;arp_pa)-&gt;sin_addr.s_addr;
<a name="L1072" href="source/net/ipv4/arp.c#L1072">1072</a>         if (!<a href="ident?i=dev">dev</a>) {
<a name="L1073" href="source/net/ipv4/arp.c#L1073">1073</a>                 struct <a href="ident?i=rtable">rtable</a> *<a href="ident?i=rt">rt</a> = <a href="ident?i=ip_route_output">ip_route_output</a>(<a href="ident?i=net">net</a>, <a href="ident?i=ip">ip</a>, 0, <a href="ident?i=RTO_ONLINK">RTO_ONLINK</a>, 0);
<a name="L1074" href="source/net/ipv4/arp.c#L1074">1074</a>                 if (<a href="ident?i=IS_ERR">IS_ERR</a>(<a href="ident?i=rt">rt</a>))
<a name="L1075" href="source/net/ipv4/arp.c#L1075">1075</a>                         return <a href="ident?i=PTR_ERR">PTR_ERR</a>(<a href="ident?i=rt">rt</a>);
<a name="L1076" href="source/net/ipv4/arp.c#L1076">1076</a>                 <a href="ident?i=dev">dev</a> = <a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>.<a href="ident?i=dev">dev</a>;
<a name="L1077" href="source/net/ipv4/arp.c#L1077">1077</a>                 <a href="ident?i=ip_rt_put">ip_rt_put</a>(<a href="ident?i=rt">rt</a>);
<a name="L1078" href="source/net/ipv4/arp.c#L1078">1078</a>                 if (!<a href="ident?i=dev">dev</a>)
<a name="L1079" href="source/net/ipv4/arp.c#L1079">1079</a>                         return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L1080" href="source/net/ipv4/arp.c#L1080">1080</a>         }
<a name="L1081" href="source/net/ipv4/arp.c#L1081">1081</a>         return <a href="ident?i=arp_invalidate">arp_invalidate</a>(<a href="ident?i=dev">dev</a>, <a href="ident?i=ip">ip</a>);
<a name="L1082" href="source/net/ipv4/arp.c#L1082">1082</a> }
<a name="L1083" href="source/net/ipv4/arp.c#L1083">1083</a> 
<a name="L1084" href="source/net/ipv4/arp.c#L1084">1084</a> <b><i>/*</i></b>
<a name="L1085" href="source/net/ipv4/arp.c#L1085">1085</a> <b><i> *      Handle an ARP layer I/O control request.</i></b>
<a name="L1086" href="source/net/ipv4/arp.c#L1086">1086</a> <b><i> */</i></b>
<a name="L1087" href="source/net/ipv4/arp.c#L1087">1087</a> 
<a name="L1088" href="source/net/ipv4/arp.c#L1088">1088</a> int <a href="ident?i=arp_ioctl">arp_ioctl</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>, unsigned int <a href="ident?i=cmd">cmd</a>, void <a href="ident?i=__user">__user</a> *<a href="ident?i=arg">arg</a>)
<a name="L1089" href="source/net/ipv4/arp.c#L1089">1089</a> {
<a name="L1090" href="source/net/ipv4/arp.c#L1090">1090</a>         int <a href="ident?i=err">err</a>;
<a name="L1091" href="source/net/ipv4/arp.c#L1091">1091</a>         struct <a href="ident?i=arpreq">arpreq</a> <a href="ident?i=r">r</a>;
<a name="L1092" href="source/net/ipv4/arp.c#L1092">1092</a>         struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a> = <a href="ident?i=NULL">NULL</a>;
<a name="L1093" href="source/net/ipv4/arp.c#L1093">1093</a> 
<a name="L1094" href="source/net/ipv4/arp.c#L1094">1094</a>         switch (<a href="ident?i=cmd">cmd</a>) {
<a name="L1095" href="source/net/ipv4/arp.c#L1095">1095</a>         case <a href="ident?i=SIOCDARP">SIOCDARP</a>:
<a name="L1096" href="source/net/ipv4/arp.c#L1096">1096</a>         case <a href="ident?i=SIOCSARP">SIOCSARP</a>:
<a name="L1097" href="source/net/ipv4/arp.c#L1097">1097</a>                 if (!<a href="ident?i=ns_capable">ns_capable</a>(<a href="ident?i=net">net</a>-&gt;<a href="ident?i=user_ns">user_ns</a>, <a href="ident?i=CAP_NET_ADMIN">CAP_NET_ADMIN</a>))
<a name="L1098" href="source/net/ipv4/arp.c#L1098">1098</a>                         return -<a href="ident?i=EPERM">EPERM</a>;
<a name="L1099" href="source/net/ipv4/arp.c#L1099">1099</a>         case <a href="ident?i=SIOCGARP">SIOCGARP</a>:
<a name="L1100" href="source/net/ipv4/arp.c#L1100">1100</a>                 <a href="ident?i=err">err</a> = <a href="ident?i=copy_from_user">copy_from_user</a>(&amp;<a href="ident?i=r">r</a>, <a href="ident?i=arg">arg</a>, sizeof(struct <a href="ident?i=arpreq">arpreq</a>));
<a name="L1101" href="source/net/ipv4/arp.c#L1101">1101</a>                 if (<a href="ident?i=err">err</a>)
<a name="L1102" href="source/net/ipv4/arp.c#L1102">1102</a>                         return -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L1103" href="source/net/ipv4/arp.c#L1103">1103</a>                 break;
<a name="L1104" href="source/net/ipv4/arp.c#L1104">1104</a>         default:
<a name="L1105" href="source/net/ipv4/arp.c#L1105">1105</a>                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L1106" href="source/net/ipv4/arp.c#L1106">1106</a>         }
<a name="L1107" href="source/net/ipv4/arp.c#L1107">1107</a> 
<a name="L1108" href="source/net/ipv4/arp.c#L1108">1108</a>         if (<a href="ident?i=r">r</a>.arp_pa.sa_family != <a href="ident?i=AF_INET">AF_INET</a>)
<a name="L1109" href="source/net/ipv4/arp.c#L1109">1109</a>                 return -<a href="ident?i=EPFNOSUPPORT">EPFNOSUPPORT</a>;
<a name="L1110" href="source/net/ipv4/arp.c#L1110">1110</a> 
<a name="L1111" href="source/net/ipv4/arp.c#L1111">1111</a>         if (!(<a href="ident?i=r">r</a>.arp_flags &amp; <a href="ident?i=ATF_PUBL">ATF_PUBL</a>) &amp;&amp;
<a name="L1112" href="source/net/ipv4/arp.c#L1112">1112</a>             (<a href="ident?i=r">r</a>.arp_flags &amp; (<a href="ident?i=ATF_NETMASK">ATF_NETMASK</a> | <a href="ident?i=ATF_DONTPUB">ATF_DONTPUB</a>)))
<a name="L1113" href="source/net/ipv4/arp.c#L1113">1113</a>                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L1114" href="source/net/ipv4/arp.c#L1114">1114</a>         if (!(<a href="ident?i=r">r</a>.arp_flags &amp; <a href="ident?i=ATF_NETMASK">ATF_NETMASK</a>))
<a name="L1115" href="source/net/ipv4/arp.c#L1115">1115</a>                 ((struct <a href="ident?i=sockaddr_in">sockaddr_in</a> *)&amp;<a href="ident?i=r">r</a>.arp_netmask)-&gt;sin_addr.s_addr =
<a name="L1116" href="source/net/ipv4/arp.c#L1116">1116</a>                                                            <a href="ident?i=htonl">htonl</a>(0xFFFFFFFFUL);
<a name="L1117" href="source/net/ipv4/arp.c#L1117">1117</a>         <a href="ident?i=rtnl_lock">rtnl_lock</a>();
<a name="L1118" href="source/net/ipv4/arp.c#L1118">1118</a>         if (<a href="ident?i=r">r</a>.arp_dev[0]) {
<a name="L1119" href="source/net/ipv4/arp.c#L1119">1119</a>                 <a href="ident?i=err">err</a> = -<a href="ident?i=ENODEV">ENODEV</a>;
<a name="L1120" href="source/net/ipv4/arp.c#L1120">1120</a>                 <a href="ident?i=dev">dev</a> = <a href="ident?i=__dev_get_by_name">__dev_get_by_name</a>(<a href="ident?i=net">net</a>, <a href="ident?i=r">r</a>.arp_dev);
<a name="L1121" href="source/net/ipv4/arp.c#L1121">1121</a>                 if (!<a href="ident?i=dev">dev</a>)
<a name="L1122" href="source/net/ipv4/arp.c#L1122">1122</a>                         goto <a href="ident?i=out">out</a>;
<a name="L1123" href="source/net/ipv4/arp.c#L1123">1123</a> 
<a name="L1124" href="source/net/ipv4/arp.c#L1124">1124</a>                 <b><i>/* Mmmm... It is wrong... ARPHRD_NETROM==0 */</i></b>
<a name="L1125" href="source/net/ipv4/arp.c#L1125">1125</a>                 if (!<a href="ident?i=r">r</a>.arp_ha.sa_family)
<a name="L1126" href="source/net/ipv4/arp.c#L1126">1126</a>                         <a href="ident?i=r">r</a>.arp_ha.sa_family = <a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=type">type</a>;
<a name="L1127" href="source/net/ipv4/arp.c#L1127">1127</a>                 <a href="ident?i=err">err</a> = -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L1128" href="source/net/ipv4/arp.c#L1128">1128</a>                 if ((<a href="ident?i=r">r</a>.arp_flags &amp; <a href="ident?i=ATF_COM">ATF_COM</a>) &amp;&amp; <a href="ident?i=r">r</a>.arp_ha.sa_family != <a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=type">type</a>)
<a name="L1129" href="source/net/ipv4/arp.c#L1129">1129</a>                         goto <a href="ident?i=out">out</a>;
<a name="L1130" href="source/net/ipv4/arp.c#L1130">1130</a>         } else if (<a href="ident?i=cmd">cmd</a> == <a href="ident?i=SIOCGARP">SIOCGARP</a>) {
<a name="L1131" href="source/net/ipv4/arp.c#L1131">1131</a>                 <a href="ident?i=err">err</a> = -<a href="ident?i=ENODEV">ENODEV</a>;
<a name="L1132" href="source/net/ipv4/arp.c#L1132">1132</a>                 goto <a href="ident?i=out">out</a>;
<a name="L1133" href="source/net/ipv4/arp.c#L1133">1133</a>         }
<a name="L1134" href="source/net/ipv4/arp.c#L1134">1134</a> 
<a name="L1135" href="source/net/ipv4/arp.c#L1135">1135</a>         switch (<a href="ident?i=cmd">cmd</a>) {
<a name="L1136" href="source/net/ipv4/arp.c#L1136">1136</a>         case <a href="ident?i=SIOCDARP">SIOCDARP</a>:
<a name="L1137" href="source/net/ipv4/arp.c#L1137">1137</a>                 <a href="ident?i=err">err</a> = <a href="ident?i=arp_req_delete">arp_req_delete</a>(<a href="ident?i=net">net</a>, &amp;<a href="ident?i=r">r</a>, <a href="ident?i=dev">dev</a>);
<a name="L1138" href="source/net/ipv4/arp.c#L1138">1138</a>                 break;
<a name="L1139" href="source/net/ipv4/arp.c#L1139">1139</a>         case <a href="ident?i=SIOCSARP">SIOCSARP</a>:
<a name="L1140" href="source/net/ipv4/arp.c#L1140">1140</a>                 <a href="ident?i=err">err</a> = <a href="ident?i=arp_req_set">arp_req_set</a>(<a href="ident?i=net">net</a>, &amp;<a href="ident?i=r">r</a>, <a href="ident?i=dev">dev</a>);
<a name="L1141" href="source/net/ipv4/arp.c#L1141">1141</a>                 break;
<a name="L1142" href="source/net/ipv4/arp.c#L1142">1142</a>         case <a href="ident?i=SIOCGARP">SIOCGARP</a>:
<a name="L1143" href="source/net/ipv4/arp.c#L1143">1143</a>                 <a href="ident?i=err">err</a> = <a href="ident?i=arp_req_get">arp_req_get</a>(&amp;<a href="ident?i=r">r</a>, <a href="ident?i=dev">dev</a>);
<a name="L1144" href="source/net/ipv4/arp.c#L1144">1144</a>                 break;
<a name="L1145" href="source/net/ipv4/arp.c#L1145">1145</a>         }
<a name="L1146" href="source/net/ipv4/arp.c#L1146">1146</a> <a href="ident?i=out">out</a>:
<a name="L1147" href="source/net/ipv4/arp.c#L1147">1147</a>         <a href="ident?i=rtnl_unlock">rtnl_unlock</a>();
<a name="L1148" href="source/net/ipv4/arp.c#L1148">1148</a>         if (<a href="ident?i=cmd">cmd</a> == <a href="ident?i=SIOCGARP">SIOCGARP</a> &amp;&amp; !<a href="ident?i=err">err</a> &amp;&amp; <a href="ident?i=copy_to_user">copy_to_user</a>(<a href="ident?i=arg">arg</a>, &amp;<a href="ident?i=r">r</a>, sizeof(<a href="ident?i=r">r</a>)))
<a name="L1149" href="source/net/ipv4/arp.c#L1149">1149</a>                 <a href="ident?i=err">err</a> = -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L1150" href="source/net/ipv4/arp.c#L1150">1150</a>         return <a href="ident?i=err">err</a>;
<a name="L1151" href="source/net/ipv4/arp.c#L1151">1151</a> }
<a name="L1152" href="source/net/ipv4/arp.c#L1152">1152</a> 
<a name="L1153" href="source/net/ipv4/arp.c#L1153">1153</a> static int <a href="ident?i=arp_netdev_event">arp_netdev_event</a>(struct <a href="ident?i=notifier_block">notifier_block</a> *<a href="ident?i=this">this</a>, unsigned long <a href="ident?i=event">event</a>,
<a name="L1154" href="source/net/ipv4/arp.c#L1154">1154</a>                             void *<a href="ident?i=ptr">ptr</a>)
<a name="L1155" href="source/net/ipv4/arp.c#L1155">1155</a> {
<a name="L1156" href="source/net/ipv4/arp.c#L1156">1156</a>         struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a> = <a href="ident?i=netdev_notifier_info_to_dev">netdev_notifier_info_to_dev</a>(<a href="ident?i=ptr">ptr</a>);
<a name="L1157" href="source/net/ipv4/arp.c#L1157">1157</a>         struct <a href="ident?i=netdev_notifier_change_info">netdev_notifier_change_info</a> *change_info;
<a name="L1158" href="source/net/ipv4/arp.c#L1158">1158</a> 
<a name="L1159" href="source/net/ipv4/arp.c#L1159">1159</a>         switch (<a href="ident?i=event">event</a>) {
<a name="L1160" href="source/net/ipv4/arp.c#L1160">1160</a>         case <a href="ident?i=NETDEV_CHANGEADDR">NETDEV_CHANGEADDR</a>:
<a name="L1161" href="source/net/ipv4/arp.c#L1161">1161</a>                 <a href="ident?i=neigh_changeaddr">neigh_changeaddr</a>(&amp;<a href="ident?i=arp_tbl">arp_tbl</a>, <a href="ident?i=dev">dev</a>);
<a name="L1162" href="source/net/ipv4/arp.c#L1162">1162</a>                 <a href="ident?i=rt_cache_flush">rt_cache_flush</a>(<a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=dev">dev</a>));
<a name="L1163" href="source/net/ipv4/arp.c#L1163">1163</a>                 break;
<a name="L1164" href="source/net/ipv4/arp.c#L1164">1164</a>         case <a href="ident?i=NETDEV_CHANGE">NETDEV_CHANGE</a>:
<a name="L1165" href="source/net/ipv4/arp.c#L1165">1165</a>                 change_info = <a href="ident?i=ptr">ptr</a>;
<a name="L1166" href="source/net/ipv4/arp.c#L1166">1166</a>                 if (change_info-&gt;flags_changed &amp; <a href="ident?i=IFF_NOARP">IFF_NOARP</a>)
<a name="L1167" href="source/net/ipv4/arp.c#L1167">1167</a>                         <a href="ident?i=neigh_changeaddr">neigh_changeaddr</a>(&amp;<a href="ident?i=arp_tbl">arp_tbl</a>, <a href="ident?i=dev">dev</a>);
<a name="L1168" href="source/net/ipv4/arp.c#L1168">1168</a>                 break;
<a name="L1169" href="source/net/ipv4/arp.c#L1169">1169</a>         default:
<a name="L1170" href="source/net/ipv4/arp.c#L1170">1170</a>                 break;
<a name="L1171" href="source/net/ipv4/arp.c#L1171">1171</a>         }
<a name="L1172" href="source/net/ipv4/arp.c#L1172">1172</a> 
<a name="L1173" href="source/net/ipv4/arp.c#L1173">1173</a>         return <a href="ident?i=NOTIFY_DONE">NOTIFY_DONE</a>;
<a name="L1174" href="source/net/ipv4/arp.c#L1174">1174</a> }
<a name="L1175" href="source/net/ipv4/arp.c#L1175">1175</a> 
<a name="L1176" href="source/net/ipv4/arp.c#L1176">1176</a> static struct <a href="ident?i=notifier_block">notifier_block</a> <a href="ident?i=arp_netdev_notifier">arp_netdev_notifier</a> = {
<a name="L1177" href="source/net/ipv4/arp.c#L1177">1177</a>         .notifier_call = <a href="ident?i=arp_netdev_event">arp_netdev_event</a>,
<a name="L1178" href="source/net/ipv4/arp.c#L1178">1178</a> };
<a name="L1179" href="source/net/ipv4/arp.c#L1179">1179</a> 
<a name="L1180" href="source/net/ipv4/arp.c#L1180">1180</a> <b><i>/* Note, that it is not on notifier chain.</i></b>
<a name="L1181" href="source/net/ipv4/arp.c#L1181">1181</a> <b><i>   It is necessary, that this routine was called after route cache will be</i></b>
<a name="L1182" href="source/net/ipv4/arp.c#L1182">1182</a> <b><i>   flushed.</i></b>
<a name="L1183" href="source/net/ipv4/arp.c#L1183">1183</a> <b><i> */</i></b>
<a name="L1184" href="source/net/ipv4/arp.c#L1184">1184</a> void <a href="ident?i=arp_ifdown">arp_ifdown</a>(struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>)
<a name="L1185" href="source/net/ipv4/arp.c#L1185">1185</a> {
<a name="L1186" href="source/net/ipv4/arp.c#L1186">1186</a>         <a href="ident?i=neigh_ifdown">neigh_ifdown</a>(&amp;<a href="ident?i=arp_tbl">arp_tbl</a>, <a href="ident?i=dev">dev</a>);
<a name="L1187" href="source/net/ipv4/arp.c#L1187">1187</a> }
<a name="L1188" href="source/net/ipv4/arp.c#L1188">1188</a> 
<a name="L1189" href="source/net/ipv4/arp.c#L1189">1189</a> 
<a name="L1190" href="source/net/ipv4/arp.c#L1190">1190</a> <b><i>/*</i></b>
<a name="L1191" href="source/net/ipv4/arp.c#L1191">1191</a> <b><i> *      Called once on startup.</i></b>
<a name="L1192" href="source/net/ipv4/arp.c#L1192">1192</a> <b><i> */</i></b>
<a name="L1193" href="source/net/ipv4/arp.c#L1193">1193</a> 
<a name="L1194" href="source/net/ipv4/arp.c#L1194">1194</a> static struct <a href="ident?i=packet_type">packet_type</a> arp_packet_type <a href="ident?i=__read_mostly">__read_mostly</a> = {
<a name="L1195" href="source/net/ipv4/arp.c#L1195">1195</a>         .<a href="ident?i=type">type</a> = <a href="ident?i=cpu_to_be16">cpu_to_be16</a>(<a href="ident?i=ETH_P_ARP">ETH_P_ARP</a>),
<a name="L1196" href="source/net/ipv4/arp.c#L1196">1196</a>         .<a href="ident?i=func">func</a> = <a href="ident?i=arp_rcv">arp_rcv</a>,
<a name="L1197" href="source/net/ipv4/arp.c#L1197">1197</a> };
<a name="L1198" href="source/net/ipv4/arp.c#L1198">1198</a> 
<a name="L1199" href="source/net/ipv4/arp.c#L1199">1199</a> static int <a href="ident?i=arp_proc_init">arp_proc_init</a>(void);
<a name="L1200" href="source/net/ipv4/arp.c#L1200">1200</a> 
<a name="L1201" href="source/net/ipv4/arp.c#L1201">1201</a> void <a href="ident?i=__init">__init</a> <a href="ident?i=arp_init">arp_init</a>(void)
<a name="L1202" href="source/net/ipv4/arp.c#L1202">1202</a> {
<a name="L1203" href="source/net/ipv4/arp.c#L1203">1203</a>         <a href="ident?i=neigh_table_init">neigh_table_init</a>(NEIGH_ARP_TABLE, &amp;<a href="ident?i=arp_tbl">arp_tbl</a>);
<a name="L1204" href="source/net/ipv4/arp.c#L1204">1204</a> 
<a name="L1205" href="source/net/ipv4/arp.c#L1205">1205</a>         <a href="ident?i=dev_add_pack">dev_add_pack</a>(&amp;arp_packet_type);
<a name="L1206" href="source/net/ipv4/arp.c#L1206">1206</a>         <a href="ident?i=arp_proc_init">arp_proc_init</a>();
<a name="L1207" href="source/net/ipv4/arp.c#L1207">1207</a> #ifdef CONFIG_SYSCTL
<a name="L1208" href="source/net/ipv4/arp.c#L1208">1208</a>         <a href="ident?i=neigh_sysctl_register">neigh_sysctl_register</a>(<a href="ident?i=NULL">NULL</a>, &amp;<a href="ident?i=arp_tbl">arp_tbl</a>.<a href="ident?i=parms">parms</a>, <a href="ident?i=NULL">NULL</a>);
<a name="L1209" href="source/net/ipv4/arp.c#L1209">1209</a> #endif
<a name="L1210" href="source/net/ipv4/arp.c#L1210">1210</a>         <a href="ident?i=register_netdevice_notifier">register_netdevice_notifier</a>(&amp;<a href="ident?i=arp_netdev_notifier">arp_netdev_notifier</a>);
<a name="L1211" href="source/net/ipv4/arp.c#L1211">1211</a> }
<a name="L1212" href="source/net/ipv4/arp.c#L1212">1212</a> 
<a name="L1213" href="source/net/ipv4/arp.c#L1213">1213</a> #ifdef CONFIG_PROC_FS
<a name="L1214" href="source/net/ipv4/arp.c#L1214">1214</a> #if <a href="ident?i=IS_ENABLED">IS_ENABLED</a>(CONFIG_AX25)
<a name="L1215" href="source/net/ipv4/arp.c#L1215">1215</a> 
<a name="L1216" href="source/net/ipv4/arp.c#L1216">1216</a> <b><i>/* ------------------------------------------------------------------------ */</i></b>
<a name="L1217" href="source/net/ipv4/arp.c#L1217">1217</a> <b><i>/*</i></b>
<a name="L1218" href="source/net/ipv4/arp.c#L1218">1218</a> <b><i> *      ax25 -&gt; ASCII conversion</i></b>
<a name="L1219" href="source/net/ipv4/arp.c#L1219">1219</a> <b><i> */</i></b>
<a name="L1220" href="source/net/ipv4/arp.c#L1220">1220</a> static char *<a href="ident?i=ax2asc2">ax2asc2</a>(<a href="ident?i=ax25_address">ax25_address</a> *<a href="ident?i=a">a</a>, char *<a href="ident?i=buf">buf</a>)
<a name="L1221" href="source/net/ipv4/arp.c#L1221">1221</a> {
<a name="L1222" href="source/net/ipv4/arp.c#L1222">1222</a>         char <a href="ident?i=c">c</a>, *<a href="ident?i=s">s</a>;
<a name="L1223" href="source/net/ipv4/arp.c#L1223">1223</a>         int <a href="ident?i=n">n</a>;
<a name="L1224" href="source/net/ipv4/arp.c#L1224">1224</a> 
<a name="L1225" href="source/net/ipv4/arp.c#L1225">1225</a>         for (<a href="ident?i=n">n</a> = 0, <a href="ident?i=s">s</a> = <a href="ident?i=buf">buf</a>; <a href="ident?i=n">n</a> &lt; 6; <a href="ident?i=n">n</a>++) {
<a name="L1226" href="source/net/ipv4/arp.c#L1226">1226</a>                 <a href="ident?i=c">c</a> = (<a href="ident?i=a">a</a>-&gt;ax25_call[<a href="ident?i=n">n</a>] &gt;&gt; 1) &amp; 0x7F;
<a name="L1227" href="source/net/ipv4/arp.c#L1227">1227</a> 
<a name="L1228" href="source/net/ipv4/arp.c#L1228">1228</a>                 if (<a href="ident?i=c">c</a> != <i>' '</i>)
<a name="L1229" href="source/net/ipv4/arp.c#L1229">1229</a>                         *<a href="ident?i=s">s</a>++ = <a href="ident?i=c">c</a>;
<a name="L1230" href="source/net/ipv4/arp.c#L1230">1230</a>         }
<a name="L1231" href="source/net/ipv4/arp.c#L1231">1231</a> 
<a name="L1232" href="source/net/ipv4/arp.c#L1232">1232</a>         *<a href="ident?i=s">s</a>++ = <i>'-'</i>;
<a name="L1233" href="source/net/ipv4/arp.c#L1233">1233</a>         <a href="ident?i=n">n</a> = (<a href="ident?i=a">a</a>-&gt;ax25_call[6] &gt;&gt; 1) &amp; 0x0F;
<a name="L1234" href="source/net/ipv4/arp.c#L1234">1234</a>         if (<a href="ident?i=n">n</a> &gt; 9) {
<a name="L1235" href="source/net/ipv4/arp.c#L1235">1235</a>                 *<a href="ident?i=s">s</a>++ = <i>'1'</i>;
<a name="L1236" href="source/net/ipv4/arp.c#L1236">1236</a>                 <a href="ident?i=n">n</a> -= 10;
<a name="L1237" href="source/net/ipv4/arp.c#L1237">1237</a>         }
<a name="L1238" href="source/net/ipv4/arp.c#L1238">1238</a> 
<a name="L1239" href="source/net/ipv4/arp.c#L1239">1239</a>         *<a href="ident?i=s">s</a>++ = <a href="ident?i=n">n</a> + <i>''</i>;
<a name="L1240" href="source/net/ipv4/arp.c#L1240">1240</a>         *<a href="ident?i=s">s</a>++ = <i>'\0'</i>;
<a name="L1241" href="source/net/ipv4/arp.c#L1241">1241</a> 
<a name="L1242" href="source/net/ipv4/arp.c#L1242">1242</a>         if (*<a href="ident?i=buf">buf</a> == <i>'\0'</i> || *<a href="ident?i=buf">buf</a> == <i>'-'</i>)
<a name="L1243" href="source/net/ipv4/arp.c#L1243">1243</a>                 return <i>"*"</i>;
<a name="L1244" href="source/net/ipv4/arp.c#L1244">1244</a> 
<a name="L1245" href="source/net/ipv4/arp.c#L1245">1245</a>         return <a href="ident?i=buf">buf</a>;
<a name="L1246" href="source/net/ipv4/arp.c#L1246">1246</a> }
<a name="L1247" href="source/net/ipv4/arp.c#L1247">1247</a> #endif <b><i>/* CONFIG_AX25 */</i></b>
<a name="L1248" href="source/net/ipv4/arp.c#L1248">1248</a> 
<a name="L1249" href="source/net/ipv4/arp.c#L1249">1249</a> #define <a href="ident?i=HBUFFERLEN">HBUFFERLEN</a> 30
<a name="L1250" href="source/net/ipv4/arp.c#L1250">1250</a> 
<a name="L1251" href="source/net/ipv4/arp.c#L1251">1251</a> static void <a href="ident?i=arp_format_neigh_entry">arp_format_neigh_entry</a>(struct <a href="ident?i=seq_file">seq_file</a> *<a href="ident?i=seq">seq</a>,
<a name="L1252" href="source/net/ipv4/arp.c#L1252">1252</a>                                    struct <a href="ident?i=neighbour">neighbour</a> *<a href="ident?i=n">n</a>)
<a name="L1253" href="source/net/ipv4/arp.c#L1253">1253</a> {
<a name="L1254" href="source/net/ipv4/arp.c#L1254">1254</a>         char hbuffer[<a href="ident?i=HBUFFERLEN">HBUFFERLEN</a>];
<a name="L1255" href="source/net/ipv4/arp.c#L1255">1255</a>         int k, j;
<a name="L1256" href="source/net/ipv4/arp.c#L1256">1256</a>         char tbuf[16];
<a name="L1257" href="source/net/ipv4/arp.c#L1257">1257</a>         struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a> = <a href="ident?i=n">n</a>-&gt;<a href="ident?i=dev">dev</a>;
<a name="L1258" href="source/net/ipv4/arp.c#L1258">1258</a>         int hatype = <a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=type">type</a>;
<a name="L1259" href="source/net/ipv4/arp.c#L1259">1259</a> 
<a name="L1260" href="source/net/ipv4/arp.c#L1260">1260</a>         <a href="ident?i=read_lock">read_lock</a>(&amp;<a href="ident?i=n">n</a>-&gt;<a href="ident?i=lock">lock</a>);
<a name="L1261" href="source/net/ipv4/arp.c#L1261">1261</a>         <b><i>/* Convert hardware address to XX:XX:XX:XX ... form. */</i></b>
<a name="L1262" href="source/net/ipv4/arp.c#L1262">1262</a> #if <a href="ident?i=IS_ENABLED">IS_ENABLED</a>(CONFIG_AX25)
<a name="L1263" href="source/net/ipv4/arp.c#L1263">1263</a>         if (hatype == <a href="ident?i=ARPHRD_AX25">ARPHRD_AX25</a> || hatype == <a href="ident?i=ARPHRD_NETROM">ARPHRD_NETROM</a>)
<a name="L1264" href="source/net/ipv4/arp.c#L1264">1264</a>                 <a href="ident?i=ax2asc2">ax2asc2</a>((<a href="ident?i=ax25_address">ax25_address</a> *)<a href="ident?i=n">n</a>-&gt;ha, hbuffer);
<a name="L1265" href="source/net/ipv4/arp.c#L1265">1265</a>         else {
<a name="L1266" href="source/net/ipv4/arp.c#L1266">1266</a> #endif
<a name="L1267" href="source/net/ipv4/arp.c#L1267">1267</a>         for (k = 0, j = 0; k &lt; <a href="ident?i=HBUFFERLEN">HBUFFERLEN</a> - 3 &amp;&amp; j &lt; <a href="ident?i=dev">dev</a>-&gt;addr_len; j++) {
<a name="L1268" href="source/net/ipv4/arp.c#L1268">1268</a>                 hbuffer[k++] = <a href="ident?i=hex_asc_hi">hex_asc_hi</a>(<a href="ident?i=n">n</a>-&gt;ha[j]);
<a name="L1269" href="source/net/ipv4/arp.c#L1269">1269</a>                 hbuffer[k++] = <a href="ident?i=hex_asc_lo">hex_asc_lo</a>(<a href="ident?i=n">n</a>-&gt;ha[j]);
<a name="L1270" href="source/net/ipv4/arp.c#L1270">1270</a>                 hbuffer[k++] = <i>':'</i>;
<a name="L1271" href="source/net/ipv4/arp.c#L1271">1271</a>         }
<a name="L1272" href="source/net/ipv4/arp.c#L1272">1272</a>         if (k != 0)
<a name="L1273" href="source/net/ipv4/arp.c#L1273">1273</a>                 --k;
<a name="L1274" href="source/net/ipv4/arp.c#L1274">1274</a>         hbuffer[k] = 0;
<a name="L1275" href="source/net/ipv4/arp.c#L1275">1275</a> #if <a href="ident?i=IS_ENABLED">IS_ENABLED</a>(CONFIG_AX25)
<a name="L1276" href="source/net/ipv4/arp.c#L1276">1276</a>         }
<a name="L1277" href="source/net/ipv4/arp.c#L1277">1277</a> #endif
<a name="L1278" href="source/net/ipv4/arp.c#L1278">1278</a>         <a href="ident?i=sprintf">sprintf</a>(tbuf, <i>"%pI4"</i>, <a href="ident?i=n">n</a>-&gt;primary_key);
<a name="L1279" href="source/net/ipv4/arp.c#L1279">1279</a>         <a href="ident?i=seq_printf">seq_printf</a>(<a href="ident?i=seq">seq</a>, <i>"%-16s 0x%-10x0x%-10x%s     *        %s\n"</i>,
<a name="L1280" href="source/net/ipv4/arp.c#L1280">1280</a>                    tbuf, hatype, <a href="ident?i=arp_state_to_flags">arp_state_to_flags</a>(<a href="ident?i=n">n</a>), hbuffer, <a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=name">name</a>);
<a name="L1281" href="source/net/ipv4/arp.c#L1281">1281</a>         <a href="ident?i=read_unlock">read_unlock</a>(&amp;<a href="ident?i=n">n</a>-&gt;<a href="ident?i=lock">lock</a>);
<a name="L1282" href="source/net/ipv4/arp.c#L1282">1282</a> }
<a name="L1283" href="source/net/ipv4/arp.c#L1283">1283</a> 
<a name="L1284" href="source/net/ipv4/arp.c#L1284">1284</a> static void <a href="ident?i=arp_format_pneigh_entry">arp_format_pneigh_entry</a>(struct <a href="ident?i=seq_file">seq_file</a> *<a href="ident?i=seq">seq</a>,
<a name="L1285" href="source/net/ipv4/arp.c#L1285">1285</a>                                     struct <a href="ident?i=pneigh_entry">pneigh_entry</a> *<a href="ident?i=n">n</a>)
<a name="L1286" href="source/net/ipv4/arp.c#L1286">1286</a> {
<a name="L1287" href="source/net/ipv4/arp.c#L1287">1287</a>         struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a> = <a href="ident?i=n">n</a>-&gt;<a href="ident?i=dev">dev</a>;
<a name="L1288" href="source/net/ipv4/arp.c#L1288">1288</a>         int hatype = <a href="ident?i=dev">dev</a> ? <a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=type">type</a> : 0;
<a name="L1289" href="source/net/ipv4/arp.c#L1289">1289</a>         char tbuf[16];
<a name="L1290" href="source/net/ipv4/arp.c#L1290">1290</a> 
<a name="L1291" href="source/net/ipv4/arp.c#L1291">1291</a>         <a href="ident?i=sprintf">sprintf</a>(tbuf, <i>"%pI4"</i>, <a href="ident?i=n">n</a>-&gt;<a href="ident?i=key">key</a>);
<a name="L1292" href="source/net/ipv4/arp.c#L1292">1292</a>         <a href="ident?i=seq_printf">seq_printf</a>(<a href="ident?i=seq">seq</a>, <i>"%-16s 0x%-10x0x%-10x%s     *        %s\n"</i>,
<a name="L1293" href="source/net/ipv4/arp.c#L1293">1293</a>                    tbuf, hatype, <a href="ident?i=ATF_PUBL">ATF_PUBL</a> | <a href="ident?i=ATF_PERM">ATF_PERM</a>, <i>"00:00:00:00:00:00"</i>,
<a name="L1294" href="source/net/ipv4/arp.c#L1294">1294</a>                    <a href="ident?i=dev">dev</a> ? <a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=name">name</a> : <i>"*"</i>);
<a name="L1295" href="source/net/ipv4/arp.c#L1295">1295</a> }
<a name="L1296" href="source/net/ipv4/arp.c#L1296">1296</a> 
<a name="L1297" href="source/net/ipv4/arp.c#L1297">1297</a> static int <a href="ident?i=arp_seq_show">arp_seq_show</a>(struct <a href="ident?i=seq_file">seq_file</a> *<a href="ident?i=seq">seq</a>, void *<a href="ident?i=v">v</a>)
<a name="L1298" href="source/net/ipv4/arp.c#L1298">1298</a> {
<a name="L1299" href="source/net/ipv4/arp.c#L1299">1299</a>         if (<a href="ident?i=v">v</a> == <a href="ident?i=SEQ_START_TOKEN">SEQ_START_TOKEN</a>) {
<a name="L1300" href="source/net/ipv4/arp.c#L1300">1300</a>                 <a href="ident?i=seq_puts">seq_puts</a>(<a href="ident?i=seq">seq</a>, <i>"IP address       HW type     Flags       "</i>
<a name="L1301" href="source/net/ipv4/arp.c#L1301">1301</a>                               <i>"HW address            Mask     Device\n"</i>);
<a name="L1302" href="source/net/ipv4/arp.c#L1302">1302</a>         } else {
<a name="L1303" href="source/net/ipv4/arp.c#L1303">1303</a>                 struct <a href="ident?i=neigh_seq_state">neigh_seq_state</a> *<a href="ident?i=state">state</a> = <a href="ident?i=seq">seq</a>-&gt;<a href="ident?i=private">private</a>;
<a name="L1304" href="source/net/ipv4/arp.c#L1304">1304</a> 
<a name="L1305" href="source/net/ipv4/arp.c#L1305">1305</a>                 if (<a href="ident?i=state">state</a>-&gt;<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=NEIGH_SEQ_IS_PNEIGH">NEIGH_SEQ_IS_PNEIGH</a>)
<a name="L1306" href="source/net/ipv4/arp.c#L1306">1306</a>                         <a href="ident?i=arp_format_pneigh_entry">arp_format_pneigh_entry</a>(<a href="ident?i=seq">seq</a>, <a href="ident?i=v">v</a>);
<a name="L1307" href="source/net/ipv4/arp.c#L1307">1307</a>                 else
<a name="L1308" href="source/net/ipv4/arp.c#L1308">1308</a>                         <a href="ident?i=arp_format_neigh_entry">arp_format_neigh_entry</a>(<a href="ident?i=seq">seq</a>, <a href="ident?i=v">v</a>);
<a name="L1309" href="source/net/ipv4/arp.c#L1309">1309</a>         }
<a name="L1310" href="source/net/ipv4/arp.c#L1310">1310</a> 
<a name="L1311" href="source/net/ipv4/arp.c#L1311">1311</a>         return 0;
<a name="L1312" href="source/net/ipv4/arp.c#L1312">1312</a> }
<a name="L1313" href="source/net/ipv4/arp.c#L1313">1313</a> 
<a name="L1314" href="source/net/ipv4/arp.c#L1314">1314</a> static void *<a href="ident?i=arp_seq_start">arp_seq_start</a>(struct <a href="ident?i=seq_file">seq_file</a> *<a href="ident?i=seq">seq</a>, <a href="ident?i=loff_t">loff_t</a> *<a href="ident?i=pos">pos</a>)
<a name="L1315" href="source/net/ipv4/arp.c#L1315">1315</a> {
<a name="L1316" href="source/net/ipv4/arp.c#L1316">1316</a>         <b><i>/* Don't want to confuse "arp -a" w/ magic entries,</i></b>
<a name="L1317" href="source/net/ipv4/arp.c#L1317">1317</a> <b><i>         * so we tell the generic iterator to skip NUD_NOARP.</i></b>
<a name="L1318" href="source/net/ipv4/arp.c#L1318">1318</a> <b><i>         */</i></b>
<a name="L1319" href="source/net/ipv4/arp.c#L1319">1319</a>         return <a href="ident?i=neigh_seq_start">neigh_seq_start</a>(<a href="ident?i=seq">seq</a>, <a href="ident?i=pos">pos</a>, &amp;<a href="ident?i=arp_tbl">arp_tbl</a>, <a href="ident?i=NEIGH_SEQ_SKIP_NOARP">NEIGH_SEQ_SKIP_NOARP</a>);
<a name="L1320" href="source/net/ipv4/arp.c#L1320">1320</a> }
<a name="L1321" href="source/net/ipv4/arp.c#L1321">1321</a> 
<a name="L1322" href="source/net/ipv4/arp.c#L1322">1322</a> <b><i>/* ------------------------------------------------------------------------ */</i></b>
<a name="L1323" href="source/net/ipv4/arp.c#L1323">1323</a> 
<a name="L1324" href="source/net/ipv4/arp.c#L1324">1324</a> static const struct <a href="ident?i=seq_operations">seq_operations</a> <a href="ident?i=arp_seq_ops">arp_seq_ops</a> = {
<a name="L1325" href="source/net/ipv4/arp.c#L1325">1325</a>         .<a href="ident?i=start">start</a>  = <a href="ident?i=arp_seq_start">arp_seq_start</a>,
<a name="L1326" href="source/net/ipv4/arp.c#L1326">1326</a>         .<a href="ident?i=next">next</a>   = <a href="ident?i=neigh_seq_next">neigh_seq_next</a>,
<a name="L1327" href="source/net/ipv4/arp.c#L1327">1327</a>         .<a href="ident?i=stop">stop</a>   = <a href="ident?i=neigh_seq_stop">neigh_seq_stop</a>,
<a name="L1328" href="source/net/ipv4/arp.c#L1328">1328</a>         .<a href="ident?i=show">show</a>   = <a href="ident?i=arp_seq_show">arp_seq_show</a>,
<a name="L1329" href="source/net/ipv4/arp.c#L1329">1329</a> };
<a name="L1330" href="source/net/ipv4/arp.c#L1330">1330</a> 
<a name="L1331" href="source/net/ipv4/arp.c#L1331">1331</a> static int <a href="ident?i=arp_seq_open">arp_seq_open</a>(struct <a href="ident?i=inode">inode</a> *<a href="ident?i=inode">inode</a>, struct <a href="ident?i=file">file</a> *<a href="ident?i=file">file</a>)
<a name="L1332" href="source/net/ipv4/arp.c#L1332">1332</a> {
<a name="L1333" href="source/net/ipv4/arp.c#L1333">1333</a>         return <a href="ident?i=seq_open_net">seq_open_net</a>(<a href="ident?i=inode">inode</a>, <a href="ident?i=file">file</a>, &amp;<a href="ident?i=arp_seq_ops">arp_seq_ops</a>,
<a name="L1334" href="source/net/ipv4/arp.c#L1334">1334</a>                             sizeof(struct <a href="ident?i=neigh_seq_state">neigh_seq_state</a>));
<a name="L1335" href="source/net/ipv4/arp.c#L1335">1335</a> }
<a name="L1336" href="source/net/ipv4/arp.c#L1336">1336</a> 
<a name="L1337" href="source/net/ipv4/arp.c#L1337">1337</a> static const struct <a href="ident?i=file_operations">file_operations</a> <a href="ident?i=arp_seq_fops">arp_seq_fops</a> = {
<a name="L1338" href="source/net/ipv4/arp.c#L1338">1338</a>         .owner          = <a href="ident?i=THIS_MODULE">THIS_MODULE</a>,
<a name="L1339" href="source/net/ipv4/arp.c#L1339">1339</a>         .<a href="ident?i=open">open</a>           = <a href="ident?i=arp_seq_open">arp_seq_open</a>,
<a name="L1340" href="source/net/ipv4/arp.c#L1340">1340</a>         .<a href="ident?i=read">read</a>           = <a href="ident?i=seq_read">seq_read</a>,
<a name="L1341" href="source/net/ipv4/arp.c#L1341">1341</a>         .llseek         = <a href="ident?i=seq_lseek">seq_lseek</a>,
<a name="L1342" href="source/net/ipv4/arp.c#L1342">1342</a>         .<a href="ident?i=release">release</a>        = <a href="ident?i=seq_release_net">seq_release_net</a>,
<a name="L1343" href="source/net/ipv4/arp.c#L1343">1343</a> };
<a name="L1344" href="source/net/ipv4/arp.c#L1344">1344</a> 
<a name="L1345" href="source/net/ipv4/arp.c#L1345">1345</a> 
<a name="L1346" href="source/net/ipv4/arp.c#L1346">1346</a> static int <a href="ident?i=__net_init">__net_init</a> <a href="ident?i=arp_net_init">arp_net_init</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>)
<a name="L1347" href="source/net/ipv4/arp.c#L1347">1347</a> {
<a name="L1348" href="source/net/ipv4/arp.c#L1348">1348</a>         if (!<a href="ident?i=proc_create">proc_create</a>(<i>"arp"</i>, <a href="ident?i=S_IRUGO">S_IRUGO</a>, <a href="ident?i=net">net</a>-&gt;proc_net, &amp;<a href="ident?i=arp_seq_fops">arp_seq_fops</a>))
<a name="L1349" href="source/net/ipv4/arp.c#L1349">1349</a>                 return -<a href="ident?i=ENOMEM">ENOMEM</a>;
<a name="L1350" href="source/net/ipv4/arp.c#L1350">1350</a>         return 0;
<a name="L1351" href="source/net/ipv4/arp.c#L1351">1351</a> }
<a name="L1352" href="source/net/ipv4/arp.c#L1352">1352</a> 
<a name="L1353" href="source/net/ipv4/arp.c#L1353">1353</a> static void <a href="ident?i=__net_exit">__net_exit</a> <a href="ident?i=arp_net_exit">arp_net_exit</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>)
<a name="L1354" href="source/net/ipv4/arp.c#L1354">1354</a> {
<a name="L1355" href="source/net/ipv4/arp.c#L1355">1355</a>         <a href="ident?i=remove_proc_entry">remove_proc_entry</a>(<i>"arp"</i>, <a href="ident?i=net">net</a>-&gt;proc_net);
<a name="L1356" href="source/net/ipv4/arp.c#L1356">1356</a> }
<a name="L1357" href="source/net/ipv4/arp.c#L1357">1357</a> 
<a name="L1358" href="source/net/ipv4/arp.c#L1358">1358</a> static struct <a href="ident?i=pernet_operations">pernet_operations</a> <a href="ident?i=arp_net_ops">arp_net_ops</a> = {
<a name="L1359" href="source/net/ipv4/arp.c#L1359">1359</a>         .<a href="ident?i=init">init</a> = <a href="ident?i=arp_net_init">arp_net_init</a>,
<a name="L1360" href="source/net/ipv4/arp.c#L1360">1360</a>         .<a href="ident?i=exit">exit</a> = <a href="ident?i=arp_net_exit">arp_net_exit</a>,
<a name="L1361" href="source/net/ipv4/arp.c#L1361">1361</a> };
<a name="L1362" href="source/net/ipv4/arp.c#L1362">1362</a> 
<a name="L1363" href="source/net/ipv4/arp.c#L1363">1363</a> static int <a href="ident?i=__init">__init</a> <a href="ident?i=arp_proc_init">arp_proc_init</a>(void)
<a name="L1364" href="source/net/ipv4/arp.c#L1364">1364</a> {
<a name="L1365" href="source/net/ipv4/arp.c#L1365">1365</a>         return <a href="ident?i=register_pernet_subsys">register_pernet_subsys</a>(&amp;<a href="ident?i=arp_net_ops">arp_net_ops</a>);
<a name="L1366" href="source/net/ipv4/arp.c#L1366">1366</a> }
<a name="L1367" href="source/net/ipv4/arp.c#L1367">1367</a> 
<a name="L1368" href="source/net/ipv4/arp.c#L1368">1368</a> #else <b><i>/* CONFIG_PROC_FS */</i></b>
<a name="L1369" href="source/net/ipv4/arp.c#L1369">1369</a> 
<a name="L1370" href="source/net/ipv4/arp.c#L1370">1370</a> static int <a href="ident?i=__init">__init</a> <a href="ident?i=arp_proc_init">arp_proc_init</a>(void)
<a name="L1371" href="source/net/ipv4/arp.c#L1371">1371</a> {
<a name="L1372" href="source/net/ipv4/arp.c#L1372">1372</a>         return 0;
<a name="L1373" href="source/net/ipv4/arp.c#L1373">1373</a> }
<a name="L1374" href="source/net/ipv4/arp.c#L1374">1374</a> 
<a name="L1375" href="source/net/ipv4/arp.c#L1375">1375</a> #endif <b><i>/* CONFIG_PROC_FS */</i></b>
<a name="L1376" href="source/net/ipv4/arp.c#L1376">1376</a> </pre></div><p>
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
