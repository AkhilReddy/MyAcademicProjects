<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title>Linux/net/ipv4/ip_gre.c - Linux Cross Reference - Free Electrons</title>
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
		 &nbsp;&bull;&nbsp;<b><i>source navigation</i></b> &nbsp;&bull;&nbsp;<a href="diff/net/ipv4/ip_gre.c">diff markup</a> &nbsp;&bull;&nbsp;<a href="ident">identifier search</a> &nbsp;&bull;&nbsp;<a href="search">freetext search</a> &nbsp;&bull;&nbsp;
		</p>
	</div>
</div>

<div id="topbar">
  
  <p>Version: &nbsp;<a href="source/net/ipv4/ip_gre.c?v=2.0.40">2.0.40</a>&nbsp;<a href="source/net/ipv4/ip_gre.c?v=2.2.26">2.2.26</a>&nbsp;<a href="source/net/ipv4/ip_gre.c?v=2.4.37">2.4.37</a>&nbsp;<a href="source/net/ipv4/ip_gre.c?v=3.5">3.5</a>&nbsp;<a href="source/net/ipv4/ip_gre.c?v=3.6">3.6</a>&nbsp;<a href="source/net/ipv4/ip_gre.c?v=3.7">3.7</a>&nbsp;<a href="source/net/ipv4/ip_gre.c?v=3.8">3.8</a>&nbsp;<a href="source/net/ipv4/ip_gre.c?v=3.9">3.9</a>&nbsp;<a href="source/net/ipv4/ip_gre.c?v=3.10">3.10</a>&nbsp;<a href="source/net/ipv4/ip_gre.c?v=3.11">3.11</a>&nbsp;<a href="source/net/ipv4/ip_gre.c?v=3.12">3.12</a>&nbsp;<a href="source/net/ipv4/ip_gre.c?v=3.13">3.13</a>&nbsp;<a href="source/net/ipv4/ip_gre.c?v=3.14">3.14</a>&nbsp;<a href="source/net/ipv4/ip_gre.c?v=3.15">3.15</a>&nbsp;<a href="source/net/ipv4/ip_gre.c?v=3.16">3.16</a>&nbsp;<a href="source/net/ipv4/ip_gre.c?v=3.17">3.17</a>&nbsp;<a href="source/net/ipv4/ip_gre.c?v=3.18">3.18</a>&nbsp;<a href="source/net/ipv4/ip_gre.c?v=3.19">3.19</a>&nbsp;<a href="source/net/ipv4/ip_gre.c?v=4.0">4.0</a>&nbsp;<b><i>4.1</i></b></p>
  
</div>

<h1><a href="source/">Linux</a>/<a href="source/net/">net</a>/<a href="source/net/ipv4/">ipv4</a>/<a href="source/net/ipv4/ip_gre.c">ip_gre.c</a></h1>
<div id="lxrcode"><pre>  <a name="L1" href="source/net/ipv4/ip_gre.c#L1">1</a> <b><i>/*</i></b>
  <a name="L2" href="source/net/ipv4/ip_gre.c#L2">2</a> <b><i> *      Linux NET3:     GRE over IP protocol decoder.</i></b>
  <a name="L3" href="source/net/ipv4/ip_gre.c#L3">3</a> <b><i> *</i></b>
  <a name="L4" href="source/net/ipv4/ip_gre.c#L4">4</a> <b><i> *      Authors: Alexey Kuznetsov (kuznet@ms2.inr.ac.ru)</i></b>
  <a name="L5" href="source/net/ipv4/ip_gre.c#L5">5</a> <b><i> *</i></b>
  <a name="L6" href="source/net/ipv4/ip_gre.c#L6">6</a> <b><i> *      This program is free software; you can redistribute it and/or</i></b>
  <a name="L7" href="source/net/ipv4/ip_gre.c#L7">7</a> <b><i> *      modify it under the terms of the GNU General Public License</i></b>
  <a name="L8" href="source/net/ipv4/ip_gre.c#L8">8</a> <b><i> *      as published by the Free Software Foundation; either version</i></b>
  <a name="L9" href="source/net/ipv4/ip_gre.c#L9">9</a> <b><i> *      2 of the License, or (at your option) any later version.</i></b>
 <a name="L10" href="source/net/ipv4/ip_gre.c#L10">10</a> <b><i> *</i></b>
 <a name="L11" href="source/net/ipv4/ip_gre.c#L11">11</a> <b><i> */</i></b>
 <a name="L12" href="source/net/ipv4/ip_gre.c#L12">12</a> 
 <a name="L13" href="source/net/ipv4/ip_gre.c#L13">13</a> #define <a href="ident?i=pr_fmt">pr_fmt</a>(<a href="ident?i=fmt">fmt</a>) KBUILD_MODNAME <i>": "</i> <a href="ident?i=fmt">fmt</a>
 <a name="L14" href="source/net/ipv4/ip_gre.c#L14">14</a> 
 <a name="L15" href="source/net/ipv4/ip_gre.c#L15">15</a> #include &lt;linux/capability.h&gt;
 <a name="L16" href="source/net/ipv4/ip_gre.c#L16">16</a> #include &lt;linux/module.h&gt;
 <a name="L17" href="source/net/ipv4/ip_gre.c#L17">17</a> #include &lt;linux/types.h&gt;
 <a name="L18" href="source/net/ipv4/ip_gre.c#L18">18</a> #include &lt;linux/kernel.h&gt;
 <a name="L19" href="source/net/ipv4/ip_gre.c#L19">19</a> #include &lt;linux/slab.h&gt;
 <a name="L20" href="source/net/ipv4/ip_gre.c#L20">20</a> #include &lt;asm/uaccess.h&gt;
 <a name="L21" href="source/net/ipv4/ip_gre.c#L21">21</a> #include &lt;linux/skbuff.h&gt;
 <a name="L22" href="source/net/ipv4/ip_gre.c#L22">22</a> #include &lt;linux/netdevice.h&gt;
 <a name="L23" href="source/net/ipv4/ip_gre.c#L23">23</a> #include &lt;linux/in.h&gt;
 <a name="L24" href="source/net/ipv4/ip_gre.c#L24">24</a> #include &lt;linux/tcp.h&gt;
 <a name="L25" href="source/net/ipv4/ip_gre.c#L25">25</a> #include &lt;linux/udp.h&gt;
 <a name="L26" href="source/net/ipv4/ip_gre.c#L26">26</a> #include &lt;linux/if_arp.h&gt;
 <a name="L27" href="source/net/ipv4/ip_gre.c#L27">27</a> #include &lt;linux/mroute.h&gt;
 <a name="L28" href="source/net/ipv4/ip_gre.c#L28">28</a> #include &lt;linux/init.h&gt;
 <a name="L29" href="source/net/ipv4/ip_gre.c#L29">29</a> #include &lt;linux/in6.h&gt;
 <a name="L30" href="source/net/ipv4/ip_gre.c#L30">30</a> #include &lt;linux/inetdevice.h&gt;
 <a name="L31" href="source/net/ipv4/ip_gre.c#L31">31</a> #include &lt;linux/igmp.h&gt;
 <a name="L32" href="source/net/ipv4/ip_gre.c#L32">32</a> #include &lt;linux/netfilter_ipv4.h&gt;
 <a name="L33" href="source/net/ipv4/ip_gre.c#L33">33</a> #include &lt;linux/etherdevice.h&gt;
 <a name="L34" href="source/net/ipv4/ip_gre.c#L34">34</a> #include &lt;linux/if_ether.h&gt;
 <a name="L35" href="source/net/ipv4/ip_gre.c#L35">35</a> 
 <a name="L36" href="source/net/ipv4/ip_gre.c#L36">36</a> #include &lt;net/sock.h&gt;
 <a name="L37" href="source/net/ipv4/ip_gre.c#L37">37</a> #include &lt;net/ip.h&gt;
 <a name="L38" href="source/net/ipv4/ip_gre.c#L38">38</a> #include &lt;net/icmp.h&gt;
 <a name="L39" href="source/net/ipv4/ip_gre.c#L39">39</a> #include &lt;net/protocol.h&gt;
 <a name="L40" href="source/net/ipv4/ip_gre.c#L40">40</a> #include &lt;net/ip_tunnels.h&gt;
 <a name="L41" href="source/net/ipv4/ip_gre.c#L41">41</a> #include &lt;net/arp.h&gt;
 <a name="L42" href="source/net/ipv4/ip_gre.c#L42">42</a> #include &lt;net/checksum.h&gt;
 <a name="L43" href="source/net/ipv4/ip_gre.c#L43">43</a> #include &lt;net/dsfield.h&gt;
 <a name="L44" href="source/net/ipv4/ip_gre.c#L44">44</a> #include &lt;net/inet_ecn.h&gt;
 <a name="L45" href="source/net/ipv4/ip_gre.c#L45">45</a> #include &lt;net/xfrm.h&gt;
 <a name="L46" href="source/net/ipv4/ip_gre.c#L46">46</a> #include &lt;net/net_namespace.h&gt;
 <a name="L47" href="source/net/ipv4/ip_gre.c#L47">47</a> #include &lt;net/netns/generic.h&gt;
 <a name="L48" href="source/net/ipv4/ip_gre.c#L48">48</a> #include &lt;net/rtnetlink.h&gt;
 <a name="L49" href="source/net/ipv4/ip_gre.c#L49">49</a> #include &lt;net/gre.h&gt;
 <a name="L50" href="source/net/ipv4/ip_gre.c#L50">50</a> 
 <a name="L51" href="source/net/ipv4/ip_gre.c#L51">51</a> #if <a href="ident?i=IS_ENABLED">IS_ENABLED</a>(CONFIG_IPV6)
 <a name="L52" href="source/net/ipv4/ip_gre.c#L52">52</a> #include &lt;net/ipv6.h&gt;
 <a name="L53" href="source/net/ipv4/ip_gre.c#L53">53</a> #include &lt;net/ip6_fib.h&gt;
 <a name="L54" href="source/net/ipv4/ip_gre.c#L54">54</a> #include &lt;net/ip6_route.h&gt;
 <a name="L55" href="source/net/ipv4/ip_gre.c#L55">55</a> #endif
 <a name="L56" href="source/net/ipv4/ip_gre.c#L56">56</a> 
 <a name="L57" href="source/net/ipv4/ip_gre.c#L57">57</a> <b><i>/*</i></b>
 <a name="L58" href="source/net/ipv4/ip_gre.c#L58">58</a> <b><i>   Problems &amp; solutions</i></b>
 <a name="L59" href="source/net/ipv4/ip_gre.c#L59">59</a> <b><i>   --------------------</i></b>
 <a name="L60" href="source/net/ipv4/ip_gre.c#L60">60</a> <b><i></i></b>
 <a name="L61" href="source/net/ipv4/ip_gre.c#L61">61</a> <b><i>   1. The most important issue is detecting local dead loops.</i></b>
 <a name="L62" href="source/net/ipv4/ip_gre.c#L62">62</a> <b><i>   They would cause complete host lockup in transmit, which</i></b>
 <a name="L63" href="source/net/ipv4/ip_gre.c#L63">63</a> <b><i>   would be "resolved" by stack overflow or, if queueing is enabled,</i></b>
 <a name="L64" href="source/net/ipv4/ip_gre.c#L64">64</a> <b><i>   with infinite looping in net_bh.</i></b>
 <a name="L65" href="source/net/ipv4/ip_gre.c#L65">65</a> <b><i></i></b>
 <a name="L66" href="source/net/ipv4/ip_gre.c#L66">66</a> <b><i>   We cannot track such dead loops during route installation,</i></b>
 <a name="L67" href="source/net/ipv4/ip_gre.c#L67">67</a> <b><i>   it is infeasible task. The most general solutions would be</i></b>
 <a name="L68" href="source/net/ipv4/ip_gre.c#L68">68</a> <b><i>   to keep skb-&gt;encapsulation counter (sort of local ttl),</i></b>
 <a name="L69" href="source/net/ipv4/ip_gre.c#L69">69</a> <b><i>   and silently drop packet when it expires. It is a good</i></b>
 <a name="L70" href="source/net/ipv4/ip_gre.c#L70">70</a> <b><i>   solution, but it supposes maintaining new variable in ALL</i></b>
 <a name="L71" href="source/net/ipv4/ip_gre.c#L71">71</a> <b><i>   skb, even if no tunneling is used.</i></b>
 <a name="L72" href="source/net/ipv4/ip_gre.c#L72">72</a> <b><i></i></b>
 <a name="L73" href="source/net/ipv4/ip_gre.c#L73">73</a> <b><i>   Current solution: xmit_recursion breaks dead loops. This is a percpu</i></b>
 <a name="L74" href="source/net/ipv4/ip_gre.c#L74">74</a> <b><i>   counter, since when we enter the first ndo_xmit(), cpu migration is</i></b>
 <a name="L75" href="source/net/ipv4/ip_gre.c#L75">75</a> <b><i>   forbidden. We force an exit if this counter reaches RECURSION_LIMIT</i></b>
 <a name="L76" href="source/net/ipv4/ip_gre.c#L76">76</a> <b><i></i></b>
 <a name="L77" href="source/net/ipv4/ip_gre.c#L77">77</a> <b><i>   2. Networking dead loops would not kill routers, but would really</i></b>
 <a name="L78" href="source/net/ipv4/ip_gre.c#L78">78</a> <b><i>   kill network. IP hop limit plays role of "t-&gt;recursion" in this case,</i></b>
 <a name="L79" href="source/net/ipv4/ip_gre.c#L79">79</a> <b><i>   if we copy it from packet being encapsulated to upper header.</i></b>
 <a name="L80" href="source/net/ipv4/ip_gre.c#L80">80</a> <b><i>   It is very good solution, but it introduces two problems:</i></b>
 <a name="L81" href="source/net/ipv4/ip_gre.c#L81">81</a> <b><i></i></b>
 <a name="L82" href="source/net/ipv4/ip_gre.c#L82">82</a> <b><i>   - Routing protocols, using packets with ttl=1 (OSPF, RIP2),</i></b>
 <a name="L83" href="source/net/ipv4/ip_gre.c#L83">83</a> <b><i>     do not work over tunnels.</i></b>
 <a name="L84" href="source/net/ipv4/ip_gre.c#L84">84</a> <b><i>   - traceroute does not work. I planned to relay ICMP from tunnel,</i></b>
 <a name="L85" href="source/net/ipv4/ip_gre.c#L85">85</a> <b><i>     so that this problem would be solved and traceroute output</i></b>
 <a name="L86" href="source/net/ipv4/ip_gre.c#L86">86</a> <b><i>     would even more informative. This idea appeared to be wrong:</i></b>
 <a name="L87" href="source/net/ipv4/ip_gre.c#L87">87</a> <b><i>     only Linux complies to rfc1812 now (yes, guys, Linux is the only</i></b>
 <a name="L88" href="source/net/ipv4/ip_gre.c#L88">88</a> <b><i>     true router now :-)), all routers (at least, in neighbourhood of mine)</i></b>
 <a name="L89" href="source/net/ipv4/ip_gre.c#L89">89</a> <b><i>     return only 8 bytes of payload. It is the end.</i></b>
 <a name="L90" href="source/net/ipv4/ip_gre.c#L90">90</a> <b><i></i></b>
 <a name="L91" href="source/net/ipv4/ip_gre.c#L91">91</a> <b><i>   Hence, if we want that OSPF worked or traceroute said something reasonable,</i></b>
 <a name="L92" href="source/net/ipv4/ip_gre.c#L92">92</a> <b><i>   we should search for another solution.</i></b>
 <a name="L93" href="source/net/ipv4/ip_gre.c#L93">93</a> <b><i></i></b>
 <a name="L94" href="source/net/ipv4/ip_gre.c#L94">94</a> <b><i>   One of them is to parse packet trying to detect inner encapsulation</i></b>
 <a name="L95" href="source/net/ipv4/ip_gre.c#L95">95</a> <b><i>   made by our node. It is difficult or even impossible, especially,</i></b>
 <a name="L96" href="source/net/ipv4/ip_gre.c#L96">96</a> <b><i>   taking into account fragmentation. TO be short, ttl is not solution at all.</i></b>
 <a name="L97" href="source/net/ipv4/ip_gre.c#L97">97</a> <b><i></i></b>
 <a name="L98" href="source/net/ipv4/ip_gre.c#L98">98</a> <b><i>   Current solution: The solution was UNEXPECTEDLY SIMPLE.</i></b>
 <a name="L99" href="source/net/ipv4/ip_gre.c#L99">99</a> <b><i>   We force DF flag on tunnels with preconfigured hop limit,</i></b>
<a name="L100" href="source/net/ipv4/ip_gre.c#L100">100</a> <b><i>   that is ALL. :-) Well, it does not remove the problem completely,</i></b>
<a name="L101" href="source/net/ipv4/ip_gre.c#L101">101</a> <b><i>   but exponential growth of network traffic is changed to linear</i></b>
<a name="L102" href="source/net/ipv4/ip_gre.c#L102">102</a> <b><i>   (branches, that exceed pmtu are pruned) and tunnel mtu</i></b>
<a name="L103" href="source/net/ipv4/ip_gre.c#L103">103</a> <b><i>   rapidly degrades to value &lt;68, where looping stops.</i></b>
<a name="L104" href="source/net/ipv4/ip_gre.c#L104">104</a> <b><i>   Yes, it is not good if there exists a router in the loop,</i></b>
<a name="L105" href="source/net/ipv4/ip_gre.c#L105">105</a> <b><i>   which does not force DF, even when encapsulating packets have DF set.</i></b>
<a name="L106" href="source/net/ipv4/ip_gre.c#L106">106</a> <b><i>   But it is not our problem! Nobody could accuse us, we made</i></b>
<a name="L107" href="source/net/ipv4/ip_gre.c#L107">107</a> <b><i>   all that we could make. Even if it is your gated who injected</i></b>
<a name="L108" href="source/net/ipv4/ip_gre.c#L108">108</a> <b><i>   fatal route to network, even if it were you who configured</i></b>
<a name="L109" href="source/net/ipv4/ip_gre.c#L109">109</a> <b><i>   fatal static route: you are innocent. :-)</i></b>
<a name="L110" href="source/net/ipv4/ip_gre.c#L110">110</a> <b><i></i></b>
<a name="L111" href="source/net/ipv4/ip_gre.c#L111">111</a> <b><i>   Alexey Kuznetsov.</i></b>
<a name="L112" href="source/net/ipv4/ip_gre.c#L112">112</a> <b><i> */</i></b>
<a name="L113" href="source/net/ipv4/ip_gre.c#L113">113</a> 
<a name="L114" href="source/net/ipv4/ip_gre.c#L114">114</a> static <a href="ident?i=bool">bool</a> <a href="ident?i=log_ecn_error">log_ecn_error</a> = <a href="ident?i=true">true</a>;
<a name="L115" href="source/net/ipv4/ip_gre.c#L115">115</a> <a href="ident?i=module_param">module_param</a>(<a href="ident?i=log_ecn_error">log_ecn_error</a>, <a href="ident?i=bool">bool</a>, 0644);
<a name="L116" href="source/net/ipv4/ip_gre.c#L116">116</a> <a href="ident?i=MODULE_PARM_DESC">MODULE_PARM_DESC</a>(<a href="ident?i=log_ecn_error">log_ecn_error</a>, <i>"Log packets received with corrupted ECN"</i>);
<a name="L117" href="source/net/ipv4/ip_gre.c#L117">117</a> 
<a name="L118" href="source/net/ipv4/ip_gre.c#L118">118</a> static struct <a href="ident?i=rtnl_link_ops">rtnl_link_ops</a> ipgre_link_ops <a href="ident?i=__read_mostly">__read_mostly</a>;
<a name="L119" href="source/net/ipv4/ip_gre.c#L119">119</a> static int <a href="ident?i=ipgre_tunnel_init">ipgre_tunnel_init</a>(struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>);
<a name="L120" href="source/net/ipv4/ip_gre.c#L120">120</a> 
<a name="L121" href="source/net/ipv4/ip_gre.c#L121">121</a> static int ipgre_net_id <a href="ident?i=__read_mostly">__read_mostly</a>;
<a name="L122" href="source/net/ipv4/ip_gre.c#L122">122</a> static int gre_tap_net_id <a href="ident?i=__read_mostly">__read_mostly</a>;
<a name="L123" href="source/net/ipv4/ip_gre.c#L123">123</a> 
<a name="L124" href="source/net/ipv4/ip_gre.c#L124">124</a> static int <a href="ident?i=ipgre_err">ipgre_err</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, <a href="ident?i=u32">u32</a> <a href="ident?i=info">info</a>,
<a name="L125" href="source/net/ipv4/ip_gre.c#L125">125</a>                      const struct <a href="ident?i=tnl_ptk_info">tnl_ptk_info</a> *<a href="ident?i=tpi">tpi</a>)
<a name="L126" href="source/net/ipv4/ip_gre.c#L126">126</a> {
<a name="L127" href="source/net/ipv4/ip_gre.c#L127">127</a> 
<a name="L128" href="source/net/ipv4/ip_gre.c#L128">128</a>         <b><i>/* All the routers (except for Linux) return only</i></b>
<a name="L129" href="source/net/ipv4/ip_gre.c#L129">129</a> <b><i>           8 bytes of packet payload. It means, that precise relaying of</i></b>
<a name="L130" href="source/net/ipv4/ip_gre.c#L130">130</a> <b><i>           ICMP in the real Internet is absolutely infeasible.</i></b>
<a name="L131" href="source/net/ipv4/ip_gre.c#L131">131</a> <b><i></i></b>
<a name="L132" href="source/net/ipv4/ip_gre.c#L132">132</a> <b><i>           Moreover, Cisco "wise men" put GRE key to the third word</i></b>
<a name="L133" href="source/net/ipv4/ip_gre.c#L133">133</a> <b><i>           in GRE header. It makes impossible maintaining even soft</i></b>
<a name="L134" href="source/net/ipv4/ip_gre.c#L134">134</a> <b><i>           state for keyed GRE tunnels with enabled checksum. Tell</i></b>
<a name="L135" href="source/net/ipv4/ip_gre.c#L135">135</a> <b><i>           them "thank you".</i></b>
<a name="L136" href="source/net/ipv4/ip_gre.c#L136">136</a> <b><i></i></b>
<a name="L137" href="source/net/ipv4/ip_gre.c#L137">137</a> <b><i>           Well, I wonder, rfc1812 was written by Cisco employee,</i></b>
<a name="L138" href="source/net/ipv4/ip_gre.c#L138">138</a> <b><i>           what the hell these idiots break standards established</i></b>
<a name="L139" href="source/net/ipv4/ip_gre.c#L139">139</a> <b><i>           by themselves???</i></b>
<a name="L140" href="source/net/ipv4/ip_gre.c#L140">140</a> <b><i>           */</i></b>
<a name="L141" href="source/net/ipv4/ip_gre.c#L141">141</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=dev">dev</a>);
<a name="L142" href="source/net/ipv4/ip_gre.c#L142">142</a>         struct <a href="ident?i=ip_tunnel_net">ip_tunnel_net</a> *itn;
<a name="L143" href="source/net/ipv4/ip_gre.c#L143">143</a>         const struct <a href="ident?i=iphdr">iphdr</a> *iph;
<a name="L144" href="source/net/ipv4/ip_gre.c#L144">144</a>         const int <a href="ident?i=type">type</a> = <a href="ident?i=icmp_hdr">icmp_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=type">type</a>;
<a name="L145" href="source/net/ipv4/ip_gre.c#L145">145</a>         const int <a href="ident?i=code">code</a> = <a href="ident?i=icmp_hdr">icmp_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=code">code</a>;
<a name="L146" href="source/net/ipv4/ip_gre.c#L146">146</a>         struct <a href="ident?i=ip_tunnel">ip_tunnel</a> *<a href="ident?i=t">t</a>;
<a name="L147" href="source/net/ipv4/ip_gre.c#L147">147</a> 
<a name="L148" href="source/net/ipv4/ip_gre.c#L148">148</a>         switch (<a href="ident?i=type">type</a>) {
<a name="L149" href="source/net/ipv4/ip_gre.c#L149">149</a>         default:
<a name="L150" href="source/net/ipv4/ip_gre.c#L150">150</a>         case <a href="ident?i=ICMP_PARAMETERPROB">ICMP_PARAMETERPROB</a>:
<a name="L151" href="source/net/ipv4/ip_gre.c#L151">151</a>                 return <a href="ident?i=PACKET_RCVD">PACKET_RCVD</a>;
<a name="L152" href="source/net/ipv4/ip_gre.c#L152">152</a> 
<a name="L153" href="source/net/ipv4/ip_gre.c#L153">153</a>         case <a href="ident?i=ICMP_DEST_UNREACH">ICMP_DEST_UNREACH</a>:
<a name="L154" href="source/net/ipv4/ip_gre.c#L154">154</a>                 switch (<a href="ident?i=code">code</a>) {
<a name="L155" href="source/net/ipv4/ip_gre.c#L155">155</a>                 case <a href="ident?i=ICMP_SR_FAILED">ICMP_SR_FAILED</a>:
<a name="L156" href="source/net/ipv4/ip_gre.c#L156">156</a>                 case <a href="ident?i=ICMP_PORT_UNREACH">ICMP_PORT_UNREACH</a>:
<a name="L157" href="source/net/ipv4/ip_gre.c#L157">157</a>                         <b><i>/* Impossible event. */</i></b>
<a name="L158" href="source/net/ipv4/ip_gre.c#L158">158</a>                         return <a href="ident?i=PACKET_RCVD">PACKET_RCVD</a>;
<a name="L159" href="source/net/ipv4/ip_gre.c#L159">159</a>                 default:
<a name="L160" href="source/net/ipv4/ip_gre.c#L160">160</a>                         <b><i>/* All others are translated to HOST_UNREACH.</i></b>
<a name="L161" href="source/net/ipv4/ip_gre.c#L161">161</a> <b><i>                           rfc2003 contains "deep thoughts" about NET_UNREACH,</i></b>
<a name="L162" href="source/net/ipv4/ip_gre.c#L162">162</a> <b><i>                           I believe they are just ether pollution. --ANK</i></b>
<a name="L163" href="source/net/ipv4/ip_gre.c#L163">163</a> <b><i>                         */</i></b>
<a name="L164" href="source/net/ipv4/ip_gre.c#L164">164</a>                         break;
<a name="L165" href="source/net/ipv4/ip_gre.c#L165">165</a>                 }
<a name="L166" href="source/net/ipv4/ip_gre.c#L166">166</a>                 break;
<a name="L167" href="source/net/ipv4/ip_gre.c#L167">167</a>         case <a href="ident?i=ICMP_TIME_EXCEEDED">ICMP_TIME_EXCEEDED</a>:
<a name="L168" href="source/net/ipv4/ip_gre.c#L168">168</a>                 if (<a href="ident?i=code">code</a> != <a href="ident?i=ICMP_EXC_TTL">ICMP_EXC_TTL</a>)
<a name="L169" href="source/net/ipv4/ip_gre.c#L169">169</a>                         return <a href="ident?i=PACKET_RCVD">PACKET_RCVD</a>;
<a name="L170" href="source/net/ipv4/ip_gre.c#L170">170</a>                 break;
<a name="L171" href="source/net/ipv4/ip_gre.c#L171">171</a> 
<a name="L172" href="source/net/ipv4/ip_gre.c#L172">172</a>         case <a href="ident?i=ICMP_REDIRECT">ICMP_REDIRECT</a>:
<a name="L173" href="source/net/ipv4/ip_gre.c#L173">173</a>                 break;
<a name="L174" href="source/net/ipv4/ip_gre.c#L174">174</a>         }
<a name="L175" href="source/net/ipv4/ip_gre.c#L175">175</a> 
<a name="L176" href="source/net/ipv4/ip_gre.c#L176">176</a>         if (<a href="ident?i=tpi">tpi</a>-&gt;<a href="ident?i=proto">proto</a> == <a href="ident?i=htons">htons</a>(<a href="ident?i=ETH_P_TEB">ETH_P_TEB</a>))
<a name="L177" href="source/net/ipv4/ip_gre.c#L177">177</a>                 itn = <a href="ident?i=net_generic">net_generic</a>(<a href="ident?i=net">net</a>, gre_tap_net_id);
<a name="L178" href="source/net/ipv4/ip_gre.c#L178">178</a>         else
<a name="L179" href="source/net/ipv4/ip_gre.c#L179">179</a>                 itn = <a href="ident?i=net_generic">net_generic</a>(<a href="ident?i=net">net</a>, ipgre_net_id);
<a name="L180" href="source/net/ipv4/ip_gre.c#L180">180</a> 
<a name="L181" href="source/net/ipv4/ip_gre.c#L181">181</a>         iph = (const struct <a href="ident?i=iphdr">iphdr</a> *)(<a href="ident?i=icmp_hdr">icmp_hdr</a>(<a href="ident?i=skb">skb</a>) + 1);
<a name="L182" href="source/net/ipv4/ip_gre.c#L182">182</a>         <a href="ident?i=t">t</a> = <a href="ident?i=ip_tunnel_lookup">ip_tunnel_lookup</a>(itn, <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=dev">dev</a>-&gt;ifindex, <a href="ident?i=tpi">tpi</a>-&gt;<a href="ident?i=flags">flags</a>,
<a name="L183" href="source/net/ipv4/ip_gre.c#L183">183</a>                              iph-&gt;<a href="ident?i=daddr">daddr</a>, iph-&gt;<a href="ident?i=saddr">saddr</a>, <a href="ident?i=tpi">tpi</a>-&gt;<a href="ident?i=key">key</a>);
<a name="L184" href="source/net/ipv4/ip_gre.c#L184">184</a> 
<a name="L185" href="source/net/ipv4/ip_gre.c#L185">185</a>         if (!<a href="ident?i=t">t</a>)
<a name="L186" href="source/net/ipv4/ip_gre.c#L186">186</a>                 return <a href="ident?i=PACKET_REJECT">PACKET_REJECT</a>;
<a name="L187" href="source/net/ipv4/ip_gre.c#L187">187</a> 
<a name="L188" href="source/net/ipv4/ip_gre.c#L188">188</a>         if (<a href="ident?i=t">t</a>-&gt;<a href="ident?i=parms">parms</a>.iph.<a href="ident?i=daddr">daddr</a> == 0 ||
<a name="L189" href="source/net/ipv4/ip_gre.c#L189">189</a>             <a href="ident?i=ipv4_is_multicast">ipv4_is_multicast</a>(<a href="ident?i=t">t</a>-&gt;<a href="ident?i=parms">parms</a>.iph.<a href="ident?i=daddr">daddr</a>))
<a name="L190" href="source/net/ipv4/ip_gre.c#L190">190</a>                 return <a href="ident?i=PACKET_RCVD">PACKET_RCVD</a>;
<a name="L191" href="source/net/ipv4/ip_gre.c#L191">191</a> 
<a name="L192" href="source/net/ipv4/ip_gre.c#L192">192</a>         if (<a href="ident?i=t">t</a>-&gt;<a href="ident?i=parms">parms</a>.iph.<a href="ident?i=ttl">ttl</a> == 0 &amp;&amp; <a href="ident?i=type">type</a> == <a href="ident?i=ICMP_TIME_EXCEEDED">ICMP_TIME_EXCEEDED</a>)
<a name="L193" href="source/net/ipv4/ip_gre.c#L193">193</a>                 return <a href="ident?i=PACKET_RCVD">PACKET_RCVD</a>;
<a name="L194" href="source/net/ipv4/ip_gre.c#L194">194</a> 
<a name="L195" href="source/net/ipv4/ip_gre.c#L195">195</a>         if (<a href="ident?i=time_before">time_before</a>(<a href="ident?i=jiffies">jiffies</a>, <a href="ident?i=t">t</a>-&gt;err_time + <a href="ident?i=IPTUNNEL_ERR_TIMEO">IPTUNNEL_ERR_TIMEO</a>))
<a name="L196" href="source/net/ipv4/ip_gre.c#L196">196</a>                 <a href="ident?i=t">t</a>-&gt;err_count++;
<a name="L197" href="source/net/ipv4/ip_gre.c#L197">197</a>         else
<a name="L198" href="source/net/ipv4/ip_gre.c#L198">198</a>                 <a href="ident?i=t">t</a>-&gt;err_count = 1;
<a name="L199" href="source/net/ipv4/ip_gre.c#L199">199</a>         <a href="ident?i=t">t</a>-&gt;err_time = <a href="ident?i=jiffies">jiffies</a>;
<a name="L200" href="source/net/ipv4/ip_gre.c#L200">200</a>         return <a href="ident?i=PACKET_RCVD">PACKET_RCVD</a>;
<a name="L201" href="source/net/ipv4/ip_gre.c#L201">201</a> }
<a name="L202" href="source/net/ipv4/ip_gre.c#L202">202</a> 
<a name="L203" href="source/net/ipv4/ip_gre.c#L203">203</a> static int <a href="ident?i=ipgre_rcv">ipgre_rcv</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, const struct <a href="ident?i=tnl_ptk_info">tnl_ptk_info</a> *<a href="ident?i=tpi">tpi</a>)
<a name="L204" href="source/net/ipv4/ip_gre.c#L204">204</a> {
<a name="L205" href="source/net/ipv4/ip_gre.c#L205">205</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=dev">dev</a>);
<a name="L206" href="source/net/ipv4/ip_gre.c#L206">206</a>         struct <a href="ident?i=ip_tunnel_net">ip_tunnel_net</a> *itn;
<a name="L207" href="source/net/ipv4/ip_gre.c#L207">207</a>         const struct <a href="ident?i=iphdr">iphdr</a> *iph;
<a name="L208" href="source/net/ipv4/ip_gre.c#L208">208</a>         struct <a href="ident?i=ip_tunnel">ip_tunnel</a> *tunnel;
<a name="L209" href="source/net/ipv4/ip_gre.c#L209">209</a> 
<a name="L210" href="source/net/ipv4/ip_gre.c#L210">210</a>         if (<a href="ident?i=tpi">tpi</a>-&gt;<a href="ident?i=proto">proto</a> == <a href="ident?i=htons">htons</a>(<a href="ident?i=ETH_P_TEB">ETH_P_TEB</a>))
<a name="L211" href="source/net/ipv4/ip_gre.c#L211">211</a>                 itn = <a href="ident?i=net_generic">net_generic</a>(<a href="ident?i=net">net</a>, gre_tap_net_id);
<a name="L212" href="source/net/ipv4/ip_gre.c#L212">212</a>         else
<a name="L213" href="source/net/ipv4/ip_gre.c#L213">213</a>                 itn = <a href="ident?i=net_generic">net_generic</a>(<a href="ident?i=net">net</a>, ipgre_net_id);
<a name="L214" href="source/net/ipv4/ip_gre.c#L214">214</a> 
<a name="L215" href="source/net/ipv4/ip_gre.c#L215">215</a>         iph = <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>);
<a name="L216" href="source/net/ipv4/ip_gre.c#L216">216</a>         tunnel = <a href="ident?i=ip_tunnel_lookup">ip_tunnel_lookup</a>(itn, <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=dev">dev</a>-&gt;ifindex, <a href="ident?i=tpi">tpi</a>-&gt;<a href="ident?i=flags">flags</a>,
<a name="L217" href="source/net/ipv4/ip_gre.c#L217">217</a>                                   iph-&gt;<a href="ident?i=saddr">saddr</a>, iph-&gt;<a href="ident?i=daddr">daddr</a>, <a href="ident?i=tpi">tpi</a>-&gt;<a href="ident?i=key">key</a>);
<a name="L218" href="source/net/ipv4/ip_gre.c#L218">218</a> 
<a name="L219" href="source/net/ipv4/ip_gre.c#L219">219</a>         if (tunnel) {
<a name="L220" href="source/net/ipv4/ip_gre.c#L220">220</a>                 <a href="ident?i=skb_pop_mac_header">skb_pop_mac_header</a>(<a href="ident?i=skb">skb</a>);
<a name="L221" href="source/net/ipv4/ip_gre.c#L221">221</a>                 <a href="ident?i=ip_tunnel_rcv">ip_tunnel_rcv</a>(tunnel, <a href="ident?i=skb">skb</a>, <a href="ident?i=tpi">tpi</a>, <a href="ident?i=log_ecn_error">log_ecn_error</a>);
<a name="L222" href="source/net/ipv4/ip_gre.c#L222">222</a>                 return <a href="ident?i=PACKET_RCVD">PACKET_RCVD</a>;
<a name="L223" href="source/net/ipv4/ip_gre.c#L223">223</a>         }
<a name="L224" href="source/net/ipv4/ip_gre.c#L224">224</a>         return <a href="ident?i=PACKET_REJECT">PACKET_REJECT</a>;
<a name="L225" href="source/net/ipv4/ip_gre.c#L225">225</a> }
<a name="L226" href="source/net/ipv4/ip_gre.c#L226">226</a> 
<a name="L227" href="source/net/ipv4/ip_gre.c#L227">227</a> static void <a href="ident?i=__gre_xmit">__gre_xmit</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>,
<a name="L228" href="source/net/ipv4/ip_gre.c#L228">228</a>                        const struct <a href="ident?i=iphdr">iphdr</a> *tnl_params,
<a name="L229" href="source/net/ipv4/ip_gre.c#L229">229</a>                        <a href="ident?i=__be16">__be16</a> <a href="ident?i=proto">proto</a>)
<a name="L230" href="source/net/ipv4/ip_gre.c#L230">230</a> {
<a name="L231" href="source/net/ipv4/ip_gre.c#L231">231</a>         struct <a href="ident?i=ip_tunnel">ip_tunnel</a> *tunnel = <a href="ident?i=netdev_priv">netdev_priv</a>(<a href="ident?i=dev">dev</a>);
<a name="L232" href="source/net/ipv4/ip_gre.c#L232">232</a>         struct <a href="ident?i=tnl_ptk_info">tnl_ptk_info</a> <a href="ident?i=tpi">tpi</a>;
<a name="L233" href="source/net/ipv4/ip_gre.c#L233">233</a> 
<a name="L234" href="source/net/ipv4/ip_gre.c#L234">234</a>         <a href="ident?i=tpi">tpi</a>.<a href="ident?i=flags">flags</a> = tunnel-&gt;<a href="ident?i=parms">parms</a>.o_flags;
<a name="L235" href="source/net/ipv4/ip_gre.c#L235">235</a>         <a href="ident?i=tpi">tpi</a>.<a href="ident?i=proto">proto</a> = <a href="ident?i=proto">proto</a>;
<a name="L236" href="source/net/ipv4/ip_gre.c#L236">236</a>         <a href="ident?i=tpi">tpi</a>.<a href="ident?i=key">key</a> = tunnel-&gt;<a href="ident?i=parms">parms</a>.o_key;
<a name="L237" href="source/net/ipv4/ip_gre.c#L237">237</a>         if (tunnel-&gt;<a href="ident?i=parms">parms</a>.o_flags &amp; <a href="ident?i=TUNNEL_SEQ">TUNNEL_SEQ</a>)
<a name="L238" href="source/net/ipv4/ip_gre.c#L238">238</a>                 tunnel-&gt;o_seqno++;
<a name="L239" href="source/net/ipv4/ip_gre.c#L239">239</a>         <a href="ident?i=tpi">tpi</a>.<a href="ident?i=seq">seq</a> = <a href="ident?i=htonl">htonl</a>(tunnel-&gt;o_seqno);
<a name="L240" href="source/net/ipv4/ip_gre.c#L240">240</a> 
<a name="L241" href="source/net/ipv4/ip_gre.c#L241">241</a>         <b><i>/* Push GRE header. */</i></b>
<a name="L242" href="source/net/ipv4/ip_gre.c#L242">242</a>         <a href="ident?i=gre_build_header">gre_build_header</a>(<a href="ident?i=skb">skb</a>, &amp;<a href="ident?i=tpi">tpi</a>, tunnel-&gt;tun_hlen);
<a name="L243" href="source/net/ipv4/ip_gre.c#L243">243</a> 
<a name="L244" href="source/net/ipv4/ip_gre.c#L244">244</a>         <a href="ident?i=skb_set_inner_protocol">skb_set_inner_protocol</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=tpi">tpi</a>.<a href="ident?i=proto">proto</a>);
<a name="L245" href="source/net/ipv4/ip_gre.c#L245">245</a> 
<a name="L246" href="source/net/ipv4/ip_gre.c#L246">246</a>         <a href="ident?i=ip_tunnel_xmit">ip_tunnel_xmit</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=dev">dev</a>, tnl_params, tnl_params-&gt;<a href="ident?i=protocol">protocol</a>);
<a name="L247" href="source/net/ipv4/ip_gre.c#L247">247</a> }
<a name="L248" href="source/net/ipv4/ip_gre.c#L248">248</a> 
<a name="L249" href="source/net/ipv4/ip_gre.c#L249">249</a> static <a href="ident?i=netdev_tx_t">netdev_tx_t</a> <a href="ident?i=ipgre_xmit">ipgre_xmit</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
<a name="L250" href="source/net/ipv4/ip_gre.c#L250">250</a>                               struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>)
<a name="L251" href="source/net/ipv4/ip_gre.c#L251">251</a> {
<a name="L252" href="source/net/ipv4/ip_gre.c#L252">252</a>         struct <a href="ident?i=ip_tunnel">ip_tunnel</a> *tunnel = <a href="ident?i=netdev_priv">netdev_priv</a>(<a href="ident?i=dev">dev</a>);
<a name="L253" href="source/net/ipv4/ip_gre.c#L253">253</a>         const struct <a href="ident?i=iphdr">iphdr</a> *tnl_params;
<a name="L254" href="source/net/ipv4/ip_gre.c#L254">254</a> 
<a name="L255" href="source/net/ipv4/ip_gre.c#L255">255</a>         if (<a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=header_ops">header_ops</a>) {
<a name="L256" href="source/net/ipv4/ip_gre.c#L256">256</a>                 <b><i>/* Need space for new headers */</i></b>
<a name="L257" href="source/net/ipv4/ip_gre.c#L257">257</a>                 if (<a href="ident?i=skb_cow_head">skb_cow_head</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=dev">dev</a>-&gt;needed_headroom -
<a name="L258" href="source/net/ipv4/ip_gre.c#L258">258</a>                                       (tunnel-&gt;hlen + sizeof(struct <a href="ident?i=iphdr">iphdr</a>))))
<a name="L259" href="source/net/ipv4/ip_gre.c#L259">259</a>                         goto free_skb;
<a name="L260" href="source/net/ipv4/ip_gre.c#L260">260</a> 
<a name="L261" href="source/net/ipv4/ip_gre.c#L261">261</a>                 tnl_params = (const struct <a href="ident?i=iphdr">iphdr</a> *)<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=data">data</a>;
<a name="L262" href="source/net/ipv4/ip_gre.c#L262">262</a> 
<a name="L263" href="source/net/ipv4/ip_gre.c#L263">263</a>                 <b><i>/* Pull skb since ip_tunnel_xmit() needs skb-&gt;data pointing</i></b>
<a name="L264" href="source/net/ipv4/ip_gre.c#L264">264</a> <b><i>                 * to gre header.</i></b>
<a name="L265" href="source/net/ipv4/ip_gre.c#L265">265</a> <b><i>                 */</i></b>
<a name="L266" href="source/net/ipv4/ip_gre.c#L266">266</a>                 <a href="ident?i=skb_pull">skb_pull</a>(<a href="ident?i=skb">skb</a>, tunnel-&gt;hlen + sizeof(struct <a href="ident?i=iphdr">iphdr</a>));
<a name="L267" href="source/net/ipv4/ip_gre.c#L267">267</a>                 <a href="ident?i=skb_reset_mac_header">skb_reset_mac_header</a>(<a href="ident?i=skb">skb</a>);
<a name="L268" href="source/net/ipv4/ip_gre.c#L268">268</a>         } else {
<a name="L269" href="source/net/ipv4/ip_gre.c#L269">269</a>                 if (<a href="ident?i=skb_cow_head">skb_cow_head</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=dev">dev</a>-&gt;needed_headroom))
<a name="L270" href="source/net/ipv4/ip_gre.c#L270">270</a>                         goto free_skb;
<a name="L271" href="source/net/ipv4/ip_gre.c#L271">271</a> 
<a name="L272" href="source/net/ipv4/ip_gre.c#L272">272</a>                 tnl_params = &amp;tunnel-&gt;<a href="ident?i=parms">parms</a>.iph;
<a name="L273" href="source/net/ipv4/ip_gre.c#L273">273</a>         }
<a name="L274" href="source/net/ipv4/ip_gre.c#L274">274</a> 
<a name="L275" href="source/net/ipv4/ip_gre.c#L275">275</a>         <a href="ident?i=skb">skb</a> = <a href="ident?i=gre_handle_offloads">gre_handle_offloads</a>(<a href="ident?i=skb">skb</a>, !!(tunnel-&gt;<a href="ident?i=parms">parms</a>.o_flags&amp;<a href="ident?i=TUNNEL_CSUM">TUNNEL_CSUM</a>));
<a name="L276" href="source/net/ipv4/ip_gre.c#L276">276</a>         if (<a href="ident?i=IS_ERR">IS_ERR</a>(<a href="ident?i=skb">skb</a>))
<a name="L277" href="source/net/ipv4/ip_gre.c#L277">277</a>                 goto <a href="ident?i=out">out</a>;
<a name="L278" href="source/net/ipv4/ip_gre.c#L278">278</a> 
<a name="L279" href="source/net/ipv4/ip_gre.c#L279">279</a>         <a href="ident?i=__gre_xmit">__gre_xmit</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=dev">dev</a>, tnl_params, <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=protocol">protocol</a>);
<a name="L280" href="source/net/ipv4/ip_gre.c#L280">280</a> 
<a name="L281" href="source/net/ipv4/ip_gre.c#L281">281</a>         return <a href="ident?i=NETDEV_TX_OK">NETDEV_TX_OK</a>;
<a name="L282" href="source/net/ipv4/ip_gre.c#L282">282</a> 
<a name="L283" href="source/net/ipv4/ip_gre.c#L283">283</a> free_skb:
<a name="L284" href="source/net/ipv4/ip_gre.c#L284">284</a>         <a href="ident?i=kfree_skb">kfree_skb</a>(<a href="ident?i=skb">skb</a>);
<a name="L285" href="source/net/ipv4/ip_gre.c#L285">285</a> <a href="ident?i=out">out</a>:
<a name="L286" href="source/net/ipv4/ip_gre.c#L286">286</a>         <a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=stats">stats</a>.tx_dropped++;
<a name="L287" href="source/net/ipv4/ip_gre.c#L287">287</a>         return <a href="ident?i=NETDEV_TX_OK">NETDEV_TX_OK</a>;
<a name="L288" href="source/net/ipv4/ip_gre.c#L288">288</a> }
<a name="L289" href="source/net/ipv4/ip_gre.c#L289">289</a> 
<a name="L290" href="source/net/ipv4/ip_gre.c#L290">290</a> static <a href="ident?i=netdev_tx_t">netdev_tx_t</a> <a href="ident?i=gre_tap_xmit">gre_tap_xmit</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
<a name="L291" href="source/net/ipv4/ip_gre.c#L291">291</a>                                 struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>)
<a name="L292" href="source/net/ipv4/ip_gre.c#L292">292</a> {
<a name="L293" href="source/net/ipv4/ip_gre.c#L293">293</a>         struct <a href="ident?i=ip_tunnel">ip_tunnel</a> *tunnel = <a href="ident?i=netdev_priv">netdev_priv</a>(<a href="ident?i=dev">dev</a>);
<a name="L294" href="source/net/ipv4/ip_gre.c#L294">294</a> 
<a name="L295" href="source/net/ipv4/ip_gre.c#L295">295</a>         <a href="ident?i=skb">skb</a> = <a href="ident?i=gre_handle_offloads">gre_handle_offloads</a>(<a href="ident?i=skb">skb</a>, !!(tunnel-&gt;<a href="ident?i=parms">parms</a>.o_flags&amp;<a href="ident?i=TUNNEL_CSUM">TUNNEL_CSUM</a>));
<a name="L296" href="source/net/ipv4/ip_gre.c#L296">296</a>         if (<a href="ident?i=IS_ERR">IS_ERR</a>(<a href="ident?i=skb">skb</a>))
<a name="L297" href="source/net/ipv4/ip_gre.c#L297">297</a>                 goto <a href="ident?i=out">out</a>;
<a name="L298" href="source/net/ipv4/ip_gre.c#L298">298</a> 
<a name="L299" href="source/net/ipv4/ip_gre.c#L299">299</a>         if (<a href="ident?i=skb_cow_head">skb_cow_head</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=dev">dev</a>-&gt;needed_headroom))
<a name="L300" href="source/net/ipv4/ip_gre.c#L300">300</a>                 goto free_skb;
<a name="L301" href="source/net/ipv4/ip_gre.c#L301">301</a> 
<a name="L302" href="source/net/ipv4/ip_gre.c#L302">302</a>         <a href="ident?i=__gre_xmit">__gre_xmit</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=dev">dev</a>, &amp;tunnel-&gt;<a href="ident?i=parms">parms</a>.iph, <a href="ident?i=htons">htons</a>(<a href="ident?i=ETH_P_TEB">ETH_P_TEB</a>));
<a name="L303" href="source/net/ipv4/ip_gre.c#L303">303</a> 
<a name="L304" href="source/net/ipv4/ip_gre.c#L304">304</a>         return <a href="ident?i=NETDEV_TX_OK">NETDEV_TX_OK</a>;
<a name="L305" href="source/net/ipv4/ip_gre.c#L305">305</a> 
<a name="L306" href="source/net/ipv4/ip_gre.c#L306">306</a> free_skb:
<a name="L307" href="source/net/ipv4/ip_gre.c#L307">307</a>         <a href="ident?i=kfree_skb">kfree_skb</a>(<a href="ident?i=skb">skb</a>);
<a name="L308" href="source/net/ipv4/ip_gre.c#L308">308</a> <a href="ident?i=out">out</a>:
<a name="L309" href="source/net/ipv4/ip_gre.c#L309">309</a>         <a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=stats">stats</a>.tx_dropped++;
<a name="L310" href="source/net/ipv4/ip_gre.c#L310">310</a>         return <a href="ident?i=NETDEV_TX_OK">NETDEV_TX_OK</a>;
<a name="L311" href="source/net/ipv4/ip_gre.c#L311">311</a> }
<a name="L312" href="source/net/ipv4/ip_gre.c#L312">312</a> 
<a name="L313" href="source/net/ipv4/ip_gre.c#L313">313</a> static int <a href="ident?i=ipgre_tunnel_ioctl">ipgre_tunnel_ioctl</a>(struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>,
<a name="L314" href="source/net/ipv4/ip_gre.c#L314">314</a>                               struct <a href="ident?i=ifreq">ifreq</a> *ifr, int <a href="ident?i=cmd">cmd</a>)
<a name="L315" href="source/net/ipv4/ip_gre.c#L315">315</a> {
<a name="L316" href="source/net/ipv4/ip_gre.c#L316">316</a>         int <a href="ident?i=err">err</a>;
<a name="L317" href="source/net/ipv4/ip_gre.c#L317">317</a>         struct <a href="ident?i=ip_tunnel_parm">ip_tunnel_parm</a> <a href="ident?i=p">p</a>;
<a name="L318" href="source/net/ipv4/ip_gre.c#L318">318</a> 
<a name="L319" href="source/net/ipv4/ip_gre.c#L319">319</a>         if (<a href="ident?i=copy_from_user">copy_from_user</a>(&amp;<a href="ident?i=p">p</a>, ifr-&gt;ifr_ifru.ifru_data, sizeof(<a href="ident?i=p">p</a>)))
<a name="L320" href="source/net/ipv4/ip_gre.c#L320">320</a>                 return -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L321" href="source/net/ipv4/ip_gre.c#L321">321</a>         if (<a href="ident?i=cmd">cmd</a> == <a href="ident?i=SIOCADDTUNNEL">SIOCADDTUNNEL</a> || <a href="ident?i=cmd">cmd</a> == <a href="ident?i=SIOCCHGTUNNEL">SIOCCHGTUNNEL</a>) {
<a name="L322" href="source/net/ipv4/ip_gre.c#L322">322</a>                 if (<a href="ident?i=p">p</a>.iph.<a href="ident?i=version">version</a> != 4 || <a href="ident?i=p">p</a>.iph.<a href="ident?i=protocol">protocol</a> != <a href="ident?i=IPPROTO_GRE">IPPROTO_GRE</a> ||
<a name="L323" href="source/net/ipv4/ip_gre.c#L323">323</a>                     <a href="ident?i=p">p</a>.iph.ihl != 5 || (<a href="ident?i=p">p</a>.iph.frag_off&amp;<a href="ident?i=htons">htons</a>(~IP_DF)) ||
<a name="L324" href="source/net/ipv4/ip_gre.c#L324">324</a>                     ((<a href="ident?i=p">p</a>.i_flags|<a href="ident?i=p">p</a>.o_flags)&amp;(<a href="ident?i=GRE_VERSION">GRE_VERSION</a>|<a href="ident?i=GRE_ROUTING">GRE_ROUTING</a>)))
<a name="L325" href="source/net/ipv4/ip_gre.c#L325">325</a>                         return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L326" href="source/net/ipv4/ip_gre.c#L326">326</a>         }
<a name="L327" href="source/net/ipv4/ip_gre.c#L327">327</a>         <a href="ident?i=p">p</a>.i_flags = <a href="ident?i=gre_flags_to_tnl_flags">gre_flags_to_tnl_flags</a>(<a href="ident?i=p">p</a>.i_flags);
<a name="L328" href="source/net/ipv4/ip_gre.c#L328">328</a>         <a href="ident?i=p">p</a>.o_flags = <a href="ident?i=gre_flags_to_tnl_flags">gre_flags_to_tnl_flags</a>(<a href="ident?i=p">p</a>.o_flags);
<a name="L329" href="source/net/ipv4/ip_gre.c#L329">329</a> 
<a name="L330" href="source/net/ipv4/ip_gre.c#L330">330</a>         <a href="ident?i=err">err</a> = <a href="ident?i=ip_tunnel_ioctl">ip_tunnel_ioctl</a>(<a href="ident?i=dev">dev</a>, &amp;<a href="ident?i=p">p</a>, <a href="ident?i=cmd">cmd</a>);
<a name="L331" href="source/net/ipv4/ip_gre.c#L331">331</a>         if (<a href="ident?i=err">err</a>)
<a name="L332" href="source/net/ipv4/ip_gre.c#L332">332</a>                 return <a href="ident?i=err">err</a>;
<a name="L333" href="source/net/ipv4/ip_gre.c#L333">333</a> 
<a name="L334" href="source/net/ipv4/ip_gre.c#L334">334</a>         <a href="ident?i=p">p</a>.i_flags = <a href="ident?i=tnl_flags_to_gre_flags">tnl_flags_to_gre_flags</a>(<a href="ident?i=p">p</a>.i_flags);
<a name="L335" href="source/net/ipv4/ip_gre.c#L335">335</a>         <a href="ident?i=p">p</a>.o_flags = <a href="ident?i=tnl_flags_to_gre_flags">tnl_flags_to_gre_flags</a>(<a href="ident?i=p">p</a>.o_flags);
<a name="L336" href="source/net/ipv4/ip_gre.c#L336">336</a> 
<a name="L337" href="source/net/ipv4/ip_gre.c#L337">337</a>         if (<a href="ident?i=copy_to_user">copy_to_user</a>(ifr-&gt;ifr_ifru.ifru_data, &amp;<a href="ident?i=p">p</a>, sizeof(<a href="ident?i=p">p</a>)))
<a name="L338" href="source/net/ipv4/ip_gre.c#L338">338</a>                 return -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L339" href="source/net/ipv4/ip_gre.c#L339">339</a>         return 0;
<a name="L340" href="source/net/ipv4/ip_gre.c#L340">340</a> }
<a name="L341" href="source/net/ipv4/ip_gre.c#L341">341</a> 
<a name="L342" href="source/net/ipv4/ip_gre.c#L342">342</a> <b><i>/* Nice toy. Unfortunately, useless in real life :-)</i></b>
<a name="L343" href="source/net/ipv4/ip_gre.c#L343">343</a> <b><i>   It allows to construct virtual multiprotocol broadcast "LAN"</i></b>
<a name="L344" href="source/net/ipv4/ip_gre.c#L344">344</a> <b><i>   over the Internet, provided multicast routing is tuned.</i></b>
<a name="L345" href="source/net/ipv4/ip_gre.c#L345">345</a> <b><i></i></b>
<a name="L346" href="source/net/ipv4/ip_gre.c#L346">346</a> <b><i></i></b>
<a name="L347" href="source/net/ipv4/ip_gre.c#L347">347</a> <b><i>   I have no idea was this bicycle invented before me,</i></b>
<a name="L348" href="source/net/ipv4/ip_gre.c#L348">348</a> <b><i>   so that I had to set ARPHRD_IPGRE to a random value.</i></b>
<a name="L349" href="source/net/ipv4/ip_gre.c#L349">349</a> <b><i>   I have an impression, that Cisco could make something similar,</i></b>
<a name="L350" href="source/net/ipv4/ip_gre.c#L350">350</a> <b><i>   but this feature is apparently missing in IOS&lt;=11.2(8).</i></b>
<a name="L351" href="source/net/ipv4/ip_gre.c#L351">351</a> <b><i></i></b>
<a name="L352" href="source/net/ipv4/ip_gre.c#L352">352</a> <b><i>   I set up 10.66.66/24 and fec0:6666:6666::0/96 as virtual networks</i></b>
<a name="L353" href="source/net/ipv4/ip_gre.c#L353">353</a> <b><i>   with broadcast 224.66.66.66. If you have access to mbone, play with me :-)</i></b>
<a name="L354" href="source/net/ipv4/ip_gre.c#L354">354</a> <b><i></i></b>
<a name="L355" href="source/net/ipv4/ip_gre.c#L355">355</a> <b><i>   ping -t 255 224.66.66.66</i></b>
<a name="L356" href="source/net/ipv4/ip_gre.c#L356">356</a> <b><i></i></b>
<a name="L357" href="source/net/ipv4/ip_gre.c#L357">357</a> <b><i>   If nobody answers, mbone does not work.</i></b>
<a name="L358" href="source/net/ipv4/ip_gre.c#L358">358</a> <b><i></i></b>
<a name="L359" href="source/net/ipv4/ip_gre.c#L359">359</a> <b><i>   ip tunnel add Universe mode gre remote 224.66.66.66 local &lt;Your_real_addr&gt; ttl 255</i></b>
<a name="L360" href="source/net/ipv4/ip_gre.c#L360">360</a> <b><i>   ip addr add 10.66.66.&lt;somewhat&gt;/24 dev Universe</i></b>
<a name="L361" href="source/net/ipv4/ip_gre.c#L361">361</a> <b><i>   ifconfig Universe up</i></b>
<a name="L362" href="source/net/ipv4/ip_gre.c#L362">362</a> <b><i>   ifconfig Universe add fe80::&lt;Your_real_addr&gt;/10</i></b>
<a name="L363" href="source/net/ipv4/ip_gre.c#L363">363</a> <b><i>   ifconfig Universe add fec0:6666:6666::&lt;Your_real_addr&gt;/96</i></b>
<a name="L364" href="source/net/ipv4/ip_gre.c#L364">364</a> <b><i>   ftp 10.66.66.66</i></b>
<a name="L365" href="source/net/ipv4/ip_gre.c#L365">365</a> <b><i>   ...</i></b>
<a name="L366" href="source/net/ipv4/ip_gre.c#L366">366</a> <b><i>   ftp fec0:6666:6666::193.233.7.65</i></b>
<a name="L367" href="source/net/ipv4/ip_gre.c#L367">367</a> <b><i>   ...</i></b>
<a name="L368" href="source/net/ipv4/ip_gre.c#L368">368</a> <b><i> */</i></b>
<a name="L369" href="source/net/ipv4/ip_gre.c#L369">369</a> static int <a href="ident?i=ipgre_header">ipgre_header</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>,
<a name="L370" href="source/net/ipv4/ip_gre.c#L370">370</a>                         unsigned short <a href="ident?i=type">type</a>,
<a name="L371" href="source/net/ipv4/ip_gre.c#L371">371</a>                         const void *<a href="ident?i=daddr">daddr</a>, const void *<a href="ident?i=saddr">saddr</a>, unsigned int <a href="ident?i=len">len</a>)
<a name="L372" href="source/net/ipv4/ip_gre.c#L372">372</a> {
<a name="L373" href="source/net/ipv4/ip_gre.c#L373">373</a>         struct <a href="ident?i=ip_tunnel">ip_tunnel</a> *<a href="ident?i=t">t</a> = <a href="ident?i=netdev_priv">netdev_priv</a>(<a href="ident?i=dev">dev</a>);
<a name="L374" href="source/net/ipv4/ip_gre.c#L374">374</a>         struct <a href="ident?i=iphdr">iphdr</a> *iph;
<a name="L375" href="source/net/ipv4/ip_gre.c#L375">375</a>         struct <a href="ident?i=gre_base_hdr">gre_base_hdr</a> *greh;
<a name="L376" href="source/net/ipv4/ip_gre.c#L376">376</a> 
<a name="L377" href="source/net/ipv4/ip_gre.c#L377">377</a>         iph = (struct <a href="ident?i=iphdr">iphdr</a> *)<a href="ident?i=skb_push">skb_push</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=t">t</a>-&gt;hlen + sizeof(*iph));
<a name="L378" href="source/net/ipv4/ip_gre.c#L378">378</a>         greh = (struct <a href="ident?i=gre_base_hdr">gre_base_hdr</a> *)(iph+1);
<a name="L379" href="source/net/ipv4/ip_gre.c#L379">379</a>         greh-&gt;<a href="ident?i=flags">flags</a> = <a href="ident?i=tnl_flags_to_gre_flags">tnl_flags_to_gre_flags</a>(<a href="ident?i=t">t</a>-&gt;<a href="ident?i=parms">parms</a>.o_flags);
<a name="L380" href="source/net/ipv4/ip_gre.c#L380">380</a>         greh-&gt;<a href="ident?i=protocol">protocol</a> = <a href="ident?i=htons">htons</a>(<a href="ident?i=type">type</a>);
<a name="L381" href="source/net/ipv4/ip_gre.c#L381">381</a> 
<a name="L382" href="source/net/ipv4/ip_gre.c#L382">382</a>         <a href="ident?i=memcpy">memcpy</a>(iph, &amp;<a href="ident?i=t">t</a>-&gt;<a href="ident?i=parms">parms</a>.iph, sizeof(struct <a href="ident?i=iphdr">iphdr</a>));
<a name="L383" href="source/net/ipv4/ip_gre.c#L383">383</a> 
<a name="L384" href="source/net/ipv4/ip_gre.c#L384">384</a>         <b><i>/* Set the source hardware address. */</i></b>
<a name="L385" href="source/net/ipv4/ip_gre.c#L385">385</a>         if (<a href="ident?i=saddr">saddr</a>)
<a name="L386" href="source/net/ipv4/ip_gre.c#L386">386</a>                 <a href="ident?i=memcpy">memcpy</a>(&amp;iph-&gt;<a href="ident?i=saddr">saddr</a>, <a href="ident?i=saddr">saddr</a>, 4);
<a name="L387" href="source/net/ipv4/ip_gre.c#L387">387</a>         if (<a href="ident?i=daddr">daddr</a>)
<a name="L388" href="source/net/ipv4/ip_gre.c#L388">388</a>                 <a href="ident?i=memcpy">memcpy</a>(&amp;iph-&gt;<a href="ident?i=daddr">daddr</a>, <a href="ident?i=daddr">daddr</a>, 4);
<a name="L389" href="source/net/ipv4/ip_gre.c#L389">389</a>         if (iph-&gt;<a href="ident?i=daddr">daddr</a>)
<a name="L390" href="source/net/ipv4/ip_gre.c#L390">390</a>                 return <a href="ident?i=t">t</a>-&gt;hlen + sizeof(*iph);
<a name="L391" href="source/net/ipv4/ip_gre.c#L391">391</a> 
<a name="L392" href="source/net/ipv4/ip_gre.c#L392">392</a>         return -(<a href="ident?i=t">t</a>-&gt;hlen + sizeof(*iph));
<a name="L393" href="source/net/ipv4/ip_gre.c#L393">393</a> }
<a name="L394" href="source/net/ipv4/ip_gre.c#L394">394</a> 
<a name="L395" href="source/net/ipv4/ip_gre.c#L395">395</a> static int <a href="ident?i=ipgre_header_parse">ipgre_header_parse</a>(const struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, unsigned char *haddr)
<a name="L396" href="source/net/ipv4/ip_gre.c#L396">396</a> {
<a name="L397" href="source/net/ipv4/ip_gre.c#L397">397</a>         const struct <a href="ident?i=iphdr">iphdr</a> *iph = (const struct <a href="ident?i=iphdr">iphdr</a> *) <a href="ident?i=skb_mac_header">skb_mac_header</a>(<a href="ident?i=skb">skb</a>);
<a name="L398" href="source/net/ipv4/ip_gre.c#L398">398</a>         <a href="ident?i=memcpy">memcpy</a>(haddr, &amp;iph-&gt;<a href="ident?i=saddr">saddr</a>, 4);
<a name="L399" href="source/net/ipv4/ip_gre.c#L399">399</a>         return 4;
<a name="L400" href="source/net/ipv4/ip_gre.c#L400">400</a> }
<a name="L401" href="source/net/ipv4/ip_gre.c#L401">401</a> 
<a name="L402" href="source/net/ipv4/ip_gre.c#L402">402</a> static const struct <a href="ident?i=header_ops">header_ops</a> <a href="ident?i=ipgre_header_ops">ipgre_header_ops</a> = {
<a name="L403" href="source/net/ipv4/ip_gre.c#L403">403</a>         .<a href="ident?i=create">create</a> = <a href="ident?i=ipgre_header">ipgre_header</a>,
<a name="L404" href="source/net/ipv4/ip_gre.c#L404">404</a>         .<a href="ident?i=parse">parse</a>  = <a href="ident?i=ipgre_header_parse">ipgre_header_parse</a>,
<a name="L405" href="source/net/ipv4/ip_gre.c#L405">405</a> };
<a name="L406" href="source/net/ipv4/ip_gre.c#L406">406</a> 
<a name="L407" href="source/net/ipv4/ip_gre.c#L407">407</a> #ifdef CONFIG_NET_IPGRE_BROADCAST
<a name="L408" href="source/net/ipv4/ip_gre.c#L408">408</a> static int <a href="ident?i=ipgre_open">ipgre_open</a>(struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>)
<a name="L409" href="source/net/ipv4/ip_gre.c#L409">409</a> {
<a name="L410" href="source/net/ipv4/ip_gre.c#L410">410</a>         struct <a href="ident?i=ip_tunnel">ip_tunnel</a> *<a href="ident?i=t">t</a> = <a href="ident?i=netdev_priv">netdev_priv</a>(<a href="ident?i=dev">dev</a>);
<a name="L411" href="source/net/ipv4/ip_gre.c#L411">411</a> 
<a name="L412" href="source/net/ipv4/ip_gre.c#L412">412</a>         if (<a href="ident?i=ipv4_is_multicast">ipv4_is_multicast</a>(<a href="ident?i=t">t</a>-&gt;<a href="ident?i=parms">parms</a>.iph.<a href="ident?i=daddr">daddr</a>)) {
<a name="L413" href="source/net/ipv4/ip_gre.c#L413">413</a>                 struct <a href="ident?i=flowi4">flowi4</a> fl4;
<a name="L414" href="source/net/ipv4/ip_gre.c#L414">414</a>                 struct <a href="ident?i=rtable">rtable</a> *<a href="ident?i=rt">rt</a>;
<a name="L415" href="source/net/ipv4/ip_gre.c#L415">415</a> 
<a name="L416" href="source/net/ipv4/ip_gre.c#L416">416</a>                 <a href="ident?i=rt">rt</a> = <a href="ident?i=ip_route_output_gre">ip_route_output_gre</a>(<a href="ident?i=t">t</a>-&gt;<a href="ident?i=net">net</a>, &amp;fl4,
<a name="L417" href="source/net/ipv4/ip_gre.c#L417">417</a>                                          <a href="ident?i=t">t</a>-&gt;<a href="ident?i=parms">parms</a>.iph.<a href="ident?i=daddr">daddr</a>,
<a name="L418" href="source/net/ipv4/ip_gre.c#L418">418</a>                                          <a href="ident?i=t">t</a>-&gt;<a href="ident?i=parms">parms</a>.iph.<a href="ident?i=saddr">saddr</a>,
<a name="L419" href="source/net/ipv4/ip_gre.c#L419">419</a>                                          <a href="ident?i=t">t</a>-&gt;<a href="ident?i=parms">parms</a>.o_key,
<a name="L420" href="source/net/ipv4/ip_gre.c#L420">420</a>                                          <a href="ident?i=RT_TOS">RT_TOS</a>(<a href="ident?i=t">t</a>-&gt;<a href="ident?i=parms">parms</a>.iph.tos),
<a name="L421" href="source/net/ipv4/ip_gre.c#L421">421</a>                                          <a href="ident?i=t">t</a>-&gt;<a href="ident?i=parms">parms</a>.<a href="ident?i=link">link</a>);
<a name="L422" href="source/net/ipv4/ip_gre.c#L422">422</a>                 if (<a href="ident?i=IS_ERR">IS_ERR</a>(<a href="ident?i=rt">rt</a>))
<a name="L423" href="source/net/ipv4/ip_gre.c#L423">423</a>                         return -<a href="ident?i=EADDRNOTAVAIL">EADDRNOTAVAIL</a>;
<a name="L424" href="source/net/ipv4/ip_gre.c#L424">424</a>                 <a href="ident?i=dev">dev</a> = <a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>.<a href="ident?i=dev">dev</a>;
<a name="L425" href="source/net/ipv4/ip_gre.c#L425">425</a>                 <a href="ident?i=ip_rt_put">ip_rt_put</a>(<a href="ident?i=rt">rt</a>);
<a name="L426" href="source/net/ipv4/ip_gre.c#L426">426</a>                 if (!<a href="ident?i=__in_dev_get_rtnl">__in_dev_get_rtnl</a>(<a href="ident?i=dev">dev</a>))
<a name="L427" href="source/net/ipv4/ip_gre.c#L427">427</a>                         return -<a href="ident?i=EADDRNOTAVAIL">EADDRNOTAVAIL</a>;
<a name="L428" href="source/net/ipv4/ip_gre.c#L428">428</a>                 <a href="ident?i=t">t</a>-&gt;mlink = <a href="ident?i=dev">dev</a>-&gt;ifindex;
<a name="L429" href="source/net/ipv4/ip_gre.c#L429">429</a>                 <a href="ident?i=ip_mc_inc_group">ip_mc_inc_group</a>(<a href="ident?i=__in_dev_get_rtnl">__in_dev_get_rtnl</a>(<a href="ident?i=dev">dev</a>), <a href="ident?i=t">t</a>-&gt;<a href="ident?i=parms">parms</a>.iph.<a href="ident?i=daddr">daddr</a>);
<a name="L430" href="source/net/ipv4/ip_gre.c#L430">430</a>         }
<a name="L431" href="source/net/ipv4/ip_gre.c#L431">431</a>         return 0;
<a name="L432" href="source/net/ipv4/ip_gre.c#L432">432</a> }
<a name="L433" href="source/net/ipv4/ip_gre.c#L433">433</a> 
<a name="L434" href="source/net/ipv4/ip_gre.c#L434">434</a> static int <a href="ident?i=ipgre_close">ipgre_close</a>(struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>)
<a name="L435" href="source/net/ipv4/ip_gre.c#L435">435</a> {
<a name="L436" href="source/net/ipv4/ip_gre.c#L436">436</a>         struct <a href="ident?i=ip_tunnel">ip_tunnel</a> *<a href="ident?i=t">t</a> = <a href="ident?i=netdev_priv">netdev_priv</a>(<a href="ident?i=dev">dev</a>);
<a name="L437" href="source/net/ipv4/ip_gre.c#L437">437</a> 
<a name="L438" href="source/net/ipv4/ip_gre.c#L438">438</a>         if (<a href="ident?i=ipv4_is_multicast">ipv4_is_multicast</a>(<a href="ident?i=t">t</a>-&gt;<a href="ident?i=parms">parms</a>.iph.<a href="ident?i=daddr">daddr</a>) &amp;&amp; <a href="ident?i=t">t</a>-&gt;mlink) {
<a name="L439" href="source/net/ipv4/ip_gre.c#L439">439</a>                 struct <a href="ident?i=in_device">in_device</a> *in_dev;
<a name="L440" href="source/net/ipv4/ip_gre.c#L440">440</a>                 in_dev = <a href="ident?i=inetdev_by_index">inetdev_by_index</a>(<a href="ident?i=t">t</a>-&gt;<a href="ident?i=net">net</a>, <a href="ident?i=t">t</a>-&gt;mlink);
<a name="L441" href="source/net/ipv4/ip_gre.c#L441">441</a>                 if (in_dev)
<a name="L442" href="source/net/ipv4/ip_gre.c#L442">442</a>                         <a href="ident?i=ip_mc_dec_group">ip_mc_dec_group</a>(in_dev, <a href="ident?i=t">t</a>-&gt;<a href="ident?i=parms">parms</a>.iph.<a href="ident?i=daddr">daddr</a>);
<a name="L443" href="source/net/ipv4/ip_gre.c#L443">443</a>         }
<a name="L444" href="source/net/ipv4/ip_gre.c#L444">444</a>         return 0;
<a name="L445" href="source/net/ipv4/ip_gre.c#L445">445</a> }
<a name="L446" href="source/net/ipv4/ip_gre.c#L446">446</a> #endif
<a name="L447" href="source/net/ipv4/ip_gre.c#L447">447</a> 
<a name="L448" href="source/net/ipv4/ip_gre.c#L448">448</a> static const struct <a href="ident?i=net_device_ops">net_device_ops</a> <a href="ident?i=ipgre_netdev_ops">ipgre_netdev_ops</a> = {
<a name="L449" href="source/net/ipv4/ip_gre.c#L449">449</a>         .ndo_init               = <a href="ident?i=ipgre_tunnel_init">ipgre_tunnel_init</a>,
<a name="L450" href="source/net/ipv4/ip_gre.c#L450">450</a>         .ndo_uninit             = <a href="ident?i=ip_tunnel_uninit">ip_tunnel_uninit</a>,
<a name="L451" href="source/net/ipv4/ip_gre.c#L451">451</a> #ifdef CONFIG_NET_IPGRE_BROADCAST
<a name="L452" href="source/net/ipv4/ip_gre.c#L452">452</a>         .ndo_open               = <a href="ident?i=ipgre_open">ipgre_open</a>,
<a name="L453" href="source/net/ipv4/ip_gre.c#L453">453</a>         .ndo_stop               = <a href="ident?i=ipgre_close">ipgre_close</a>,
<a name="L454" href="source/net/ipv4/ip_gre.c#L454">454</a> #endif
<a name="L455" href="source/net/ipv4/ip_gre.c#L455">455</a>         .ndo_start_xmit         = <a href="ident?i=ipgre_xmit">ipgre_xmit</a>,
<a name="L456" href="source/net/ipv4/ip_gre.c#L456">456</a>         .ndo_do_ioctl           = <a href="ident?i=ipgre_tunnel_ioctl">ipgre_tunnel_ioctl</a>,
<a name="L457" href="source/net/ipv4/ip_gre.c#L457">457</a>         .ndo_change_mtu         = <a href="ident?i=ip_tunnel_change_mtu">ip_tunnel_change_mtu</a>,
<a name="L458" href="source/net/ipv4/ip_gre.c#L458">458</a>         .ndo_get_stats64        = <a href="ident?i=ip_tunnel_get_stats64">ip_tunnel_get_stats64</a>,
<a name="L459" href="source/net/ipv4/ip_gre.c#L459">459</a>         .ndo_get_iflink         = <a href="ident?i=ip_tunnel_get_iflink">ip_tunnel_get_iflink</a>,
<a name="L460" href="source/net/ipv4/ip_gre.c#L460">460</a> };
<a name="L461" href="source/net/ipv4/ip_gre.c#L461">461</a> 
<a name="L462" href="source/net/ipv4/ip_gre.c#L462">462</a> #define <a href="ident?i=GRE_FEATURES">GRE_FEATURES</a> (<a href="ident?i=NETIF_F_SG">NETIF_F_SG</a> |              \
<a name="L463" href="source/net/ipv4/ip_gre.c#L463">463</a>                       <a href="ident?i=NETIF_F_FRAGLIST">NETIF_F_FRAGLIST</a> |        \
<a name="L464" href="source/net/ipv4/ip_gre.c#L464">464</a>                       <a href="ident?i=NETIF_F_HIGHDMA">NETIF_F_HIGHDMA</a> |         \
<a name="L465" href="source/net/ipv4/ip_gre.c#L465">465</a>                       <a href="ident?i=NETIF_F_HW_CSUM">NETIF_F_HW_CSUM</a>)
<a name="L466" href="source/net/ipv4/ip_gre.c#L466">466</a> 
<a name="L467" href="source/net/ipv4/ip_gre.c#L467">467</a> static void <a href="ident?i=ipgre_tunnel_setup">ipgre_tunnel_setup</a>(struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>)
<a name="L468" href="source/net/ipv4/ip_gre.c#L468">468</a> {
<a name="L469" href="source/net/ipv4/ip_gre.c#L469">469</a>         <a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=netdev_ops">netdev_ops</a>         = &amp;<a href="ident?i=ipgre_netdev_ops">ipgre_netdev_ops</a>;
<a name="L470" href="source/net/ipv4/ip_gre.c#L470">470</a>         <a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=type">type</a>               = <a href="ident?i=ARPHRD_IPGRE">ARPHRD_IPGRE</a>;
<a name="L471" href="source/net/ipv4/ip_gre.c#L471">471</a>         <a href="ident?i=ip_tunnel_setup">ip_tunnel_setup</a>(<a href="ident?i=dev">dev</a>, ipgre_net_id);
<a name="L472" href="source/net/ipv4/ip_gre.c#L472">472</a> }
<a name="L473" href="source/net/ipv4/ip_gre.c#L473">473</a> 
<a name="L474" href="source/net/ipv4/ip_gre.c#L474">474</a> static void <a href="ident?i=__gre_tunnel_init">__gre_tunnel_init</a>(struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>)
<a name="L475" href="source/net/ipv4/ip_gre.c#L475">475</a> {
<a name="L476" href="source/net/ipv4/ip_gre.c#L476">476</a>         struct <a href="ident?i=ip_tunnel">ip_tunnel</a> *tunnel;
<a name="L477" href="source/net/ipv4/ip_gre.c#L477">477</a>         int t_hlen;
<a name="L478" href="source/net/ipv4/ip_gre.c#L478">478</a> 
<a name="L479" href="source/net/ipv4/ip_gre.c#L479">479</a>         tunnel = <a href="ident?i=netdev_priv">netdev_priv</a>(<a href="ident?i=dev">dev</a>);
<a name="L480" href="source/net/ipv4/ip_gre.c#L480">480</a>         tunnel-&gt;tun_hlen = <a href="ident?i=ip_gre_calc_hlen">ip_gre_calc_hlen</a>(tunnel-&gt;<a href="ident?i=parms">parms</a>.o_flags);
<a name="L481" href="source/net/ipv4/ip_gre.c#L481">481</a>         tunnel-&gt;<a href="ident?i=parms">parms</a>.iph.<a href="ident?i=protocol">protocol</a> = <a href="ident?i=IPPROTO_GRE">IPPROTO_GRE</a>;
<a name="L482" href="source/net/ipv4/ip_gre.c#L482">482</a> 
<a name="L483" href="source/net/ipv4/ip_gre.c#L483">483</a>         tunnel-&gt;hlen = tunnel-&gt;tun_hlen + tunnel-&gt;encap_hlen;
<a name="L484" href="source/net/ipv4/ip_gre.c#L484">484</a> 
<a name="L485" href="source/net/ipv4/ip_gre.c#L485">485</a>         t_hlen = tunnel-&gt;hlen + sizeof(struct <a href="ident?i=iphdr">iphdr</a>);
<a name="L486" href="source/net/ipv4/ip_gre.c#L486">486</a> 
<a name="L487" href="source/net/ipv4/ip_gre.c#L487">487</a>         <a href="ident?i=dev">dev</a>-&gt;needed_headroom    = <a href="ident?i=LL_MAX_HEADER">LL_MAX_HEADER</a> + t_hlen + 4;
<a name="L488" href="source/net/ipv4/ip_gre.c#L488">488</a>         <a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=mtu">mtu</a>                = <a href="ident?i=ETH_DATA_LEN">ETH_DATA_LEN</a> - t_hlen - 4;
<a name="L489" href="source/net/ipv4/ip_gre.c#L489">489</a> 
<a name="L490" href="source/net/ipv4/ip_gre.c#L490">490</a>         <a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=features">features</a>           |= <a href="ident?i=GRE_FEATURES">GRE_FEATURES</a>;
<a name="L491" href="source/net/ipv4/ip_gre.c#L491">491</a>         <a href="ident?i=dev">dev</a>-&gt;hw_features        |= <a href="ident?i=GRE_FEATURES">GRE_FEATURES</a>;
<a name="L492" href="source/net/ipv4/ip_gre.c#L492">492</a> 
<a name="L493" href="source/net/ipv4/ip_gre.c#L493">493</a>         if (!(tunnel-&gt;<a href="ident?i=parms">parms</a>.o_flags &amp; <a href="ident?i=TUNNEL_SEQ">TUNNEL_SEQ</a>)) {
<a name="L494" href="source/net/ipv4/ip_gre.c#L494">494</a>                 <b><i>/* TCP offload with GRE SEQ is not supported. */</i></b>
<a name="L495" href="source/net/ipv4/ip_gre.c#L495">495</a>                 <a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=features">features</a>    |= <a href="ident?i=NETIF_F_GSO_SOFTWARE">NETIF_F_GSO_SOFTWARE</a>;
<a name="L496" href="source/net/ipv4/ip_gre.c#L496">496</a>                 <a href="ident?i=dev">dev</a>-&gt;hw_features |= <a href="ident?i=NETIF_F_GSO_SOFTWARE">NETIF_F_GSO_SOFTWARE</a>;
<a name="L497" href="source/net/ipv4/ip_gre.c#L497">497</a>                 <b><i>/* Can use a lockless transmit, unless we generate</i></b>
<a name="L498" href="source/net/ipv4/ip_gre.c#L498">498</a> <b><i>                 * output sequences</i></b>
<a name="L499" href="source/net/ipv4/ip_gre.c#L499">499</a> <b><i>                 */</i></b>
<a name="L500" href="source/net/ipv4/ip_gre.c#L500">500</a>                 <a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=features">features</a> |= <a href="ident?i=NETIF_F_LLTX">NETIF_F_LLTX</a>;
<a name="L501" href="source/net/ipv4/ip_gre.c#L501">501</a>         }
<a name="L502" href="source/net/ipv4/ip_gre.c#L502">502</a> }
<a name="L503" href="source/net/ipv4/ip_gre.c#L503">503</a> 
<a name="L504" href="source/net/ipv4/ip_gre.c#L504">504</a> static int <a href="ident?i=ipgre_tunnel_init">ipgre_tunnel_init</a>(struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>)
<a name="L505" href="source/net/ipv4/ip_gre.c#L505">505</a> {
<a name="L506" href="source/net/ipv4/ip_gre.c#L506">506</a>         struct <a href="ident?i=ip_tunnel">ip_tunnel</a> *tunnel = <a href="ident?i=netdev_priv">netdev_priv</a>(<a href="ident?i=dev">dev</a>);
<a name="L507" href="source/net/ipv4/ip_gre.c#L507">507</a>         struct <a href="ident?i=iphdr">iphdr</a> *iph = &amp;tunnel-&gt;<a href="ident?i=parms">parms</a>.iph;
<a name="L508" href="source/net/ipv4/ip_gre.c#L508">508</a> 
<a name="L509" href="source/net/ipv4/ip_gre.c#L509">509</a>         <a href="ident?i=__gre_tunnel_init">__gre_tunnel_init</a>(<a href="ident?i=dev">dev</a>);
<a name="L510" href="source/net/ipv4/ip_gre.c#L510">510</a> 
<a name="L511" href="source/net/ipv4/ip_gre.c#L511">511</a>         <a href="ident?i=memcpy">memcpy</a>(<a href="ident?i=dev">dev</a>-&gt;dev_addr, &amp;iph-&gt;<a href="ident?i=saddr">saddr</a>, 4);
<a name="L512" href="source/net/ipv4/ip_gre.c#L512">512</a>         <a href="ident?i=memcpy">memcpy</a>(<a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=broadcast">broadcast</a>, &amp;iph-&gt;<a href="ident?i=daddr">daddr</a>, 4);
<a name="L513" href="source/net/ipv4/ip_gre.c#L513">513</a> 
<a name="L514" href="source/net/ipv4/ip_gre.c#L514">514</a>         <a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=flags">flags</a>              = <a href="ident?i=IFF_NOARP">IFF_NOARP</a>;
<a name="L515" href="source/net/ipv4/ip_gre.c#L515">515</a>         <a href="ident?i=netif_keep_dst">netif_keep_dst</a>(<a href="ident?i=dev">dev</a>);
<a name="L516" href="source/net/ipv4/ip_gre.c#L516">516</a>         <a href="ident?i=dev">dev</a>-&gt;addr_len           = 4;
<a name="L517" href="source/net/ipv4/ip_gre.c#L517">517</a> 
<a name="L518" href="source/net/ipv4/ip_gre.c#L518">518</a>         if (iph-&gt;<a href="ident?i=daddr">daddr</a>) {
<a name="L519" href="source/net/ipv4/ip_gre.c#L519">519</a> #ifdef CONFIG_NET_IPGRE_BROADCAST
<a name="L520" href="source/net/ipv4/ip_gre.c#L520">520</a>                 if (<a href="ident?i=ipv4_is_multicast">ipv4_is_multicast</a>(iph-&gt;<a href="ident?i=daddr">daddr</a>)) {
<a name="L521" href="source/net/ipv4/ip_gre.c#L521">521</a>                         if (!iph-&gt;<a href="ident?i=saddr">saddr</a>)
<a name="L522" href="source/net/ipv4/ip_gre.c#L522">522</a>                                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L523" href="source/net/ipv4/ip_gre.c#L523">523</a>                         <a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=flags">flags</a> = <a href="ident?i=IFF_BROADCAST">IFF_BROADCAST</a>;
<a name="L524" href="source/net/ipv4/ip_gre.c#L524">524</a>                         <a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=header_ops">header_ops</a> = &amp;<a href="ident?i=ipgre_header_ops">ipgre_header_ops</a>;
<a name="L525" href="source/net/ipv4/ip_gre.c#L525">525</a>                 }
<a name="L526" href="source/net/ipv4/ip_gre.c#L526">526</a> #endif
<a name="L527" href="source/net/ipv4/ip_gre.c#L527">527</a>         } else
<a name="L528" href="source/net/ipv4/ip_gre.c#L528">528</a>                 <a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=header_ops">header_ops</a> = &amp;<a href="ident?i=ipgre_header_ops">ipgre_header_ops</a>;
<a name="L529" href="source/net/ipv4/ip_gre.c#L529">529</a> 
<a name="L530" href="source/net/ipv4/ip_gre.c#L530">530</a>         return <a href="ident?i=ip_tunnel_init">ip_tunnel_init</a>(<a href="ident?i=dev">dev</a>);
<a name="L531" href="source/net/ipv4/ip_gre.c#L531">531</a> }
<a name="L532" href="source/net/ipv4/ip_gre.c#L532">532</a> 
<a name="L533" href="source/net/ipv4/ip_gre.c#L533">533</a> static struct <a href="ident?i=gre_cisco_protocol">gre_cisco_protocol</a> <a href="ident?i=ipgre_protocol">ipgre_protocol</a> = {
<a name="L534" href="source/net/ipv4/ip_gre.c#L534">534</a>         .<a href="ident?i=handler">handler</a>        = <a href="ident?i=ipgre_rcv">ipgre_rcv</a>,
<a name="L535" href="source/net/ipv4/ip_gre.c#L535">535</a>         .<a href="ident?i=err_handler">err_handler</a>    = <a href="ident?i=ipgre_err">ipgre_err</a>,
<a name="L536" href="source/net/ipv4/ip_gre.c#L536">536</a>         .<a href="ident?i=priority">priority</a>       = 0,
<a name="L537" href="source/net/ipv4/ip_gre.c#L537">537</a> };
<a name="L538" href="source/net/ipv4/ip_gre.c#L538">538</a> 
<a name="L539" href="source/net/ipv4/ip_gre.c#L539">539</a> static int <a href="ident?i=__net_init">__net_init</a> <a href="ident?i=ipgre_init_net">ipgre_init_net</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>)
<a name="L540" href="source/net/ipv4/ip_gre.c#L540">540</a> {
<a name="L541" href="source/net/ipv4/ip_gre.c#L541">541</a>         return <a href="ident?i=ip_tunnel_init_net">ip_tunnel_init_net</a>(<a href="ident?i=net">net</a>, ipgre_net_id, &amp;ipgre_link_ops, <a href="ident?i=NULL">NULL</a>);
<a name="L542" href="source/net/ipv4/ip_gre.c#L542">542</a> }
<a name="L543" href="source/net/ipv4/ip_gre.c#L543">543</a> 
<a name="L544" href="source/net/ipv4/ip_gre.c#L544">544</a> static void <a href="ident?i=__net_exit">__net_exit</a> <a href="ident?i=ipgre_exit_net">ipgre_exit_net</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>)
<a name="L545" href="source/net/ipv4/ip_gre.c#L545">545</a> {
<a name="L546" href="source/net/ipv4/ip_gre.c#L546">546</a>         struct <a href="ident?i=ip_tunnel_net">ip_tunnel_net</a> *itn = <a href="ident?i=net_generic">net_generic</a>(<a href="ident?i=net">net</a>, ipgre_net_id);
<a name="L547" href="source/net/ipv4/ip_gre.c#L547">547</a>         <a href="ident?i=ip_tunnel_delete_net">ip_tunnel_delete_net</a>(itn, &amp;ipgre_link_ops);
<a name="L548" href="source/net/ipv4/ip_gre.c#L548">548</a> }
<a name="L549" href="source/net/ipv4/ip_gre.c#L549">549</a> 
<a name="L550" href="source/net/ipv4/ip_gre.c#L550">550</a> static struct <a href="ident?i=pernet_operations">pernet_operations</a> <a href="ident?i=ipgre_net_ops">ipgre_net_ops</a> = {
<a name="L551" href="source/net/ipv4/ip_gre.c#L551">551</a>         .<a href="ident?i=init">init</a> = <a href="ident?i=ipgre_init_net">ipgre_init_net</a>,
<a name="L552" href="source/net/ipv4/ip_gre.c#L552">552</a>         .<a href="ident?i=exit">exit</a> = <a href="ident?i=ipgre_exit_net">ipgre_exit_net</a>,
<a name="L553" href="source/net/ipv4/ip_gre.c#L553">553</a>         .<a href="ident?i=id">id</a>   = &amp;ipgre_net_id,
<a name="L554" href="source/net/ipv4/ip_gre.c#L554">554</a>         .<a href="ident?i=size">size</a> = sizeof(struct <a href="ident?i=ip_tunnel_net">ip_tunnel_net</a>),
<a name="L555" href="source/net/ipv4/ip_gre.c#L555">555</a> };
<a name="L556" href="source/net/ipv4/ip_gre.c#L556">556</a> 
<a name="L557" href="source/net/ipv4/ip_gre.c#L557">557</a> static int <a href="ident?i=ipgre_tunnel_validate">ipgre_tunnel_validate</a>(struct <a href="ident?i=nlattr">nlattr</a> *<a href="ident?i=tb">tb</a>[], struct <a href="ident?i=nlattr">nlattr</a> *<a href="ident?i=data">data</a>[])
<a name="L558" href="source/net/ipv4/ip_gre.c#L558">558</a> {
<a name="L559" href="source/net/ipv4/ip_gre.c#L559">559</a>         <a href="ident?i=__be16">__be16</a> <a href="ident?i=flags">flags</a>;
<a name="L560" href="source/net/ipv4/ip_gre.c#L560">560</a> 
<a name="L561" href="source/net/ipv4/ip_gre.c#L561">561</a>         if (!<a href="ident?i=data">data</a>)
<a name="L562" href="source/net/ipv4/ip_gre.c#L562">562</a>                 return 0;
<a name="L563" href="source/net/ipv4/ip_gre.c#L563">563</a> 
<a name="L564" href="source/net/ipv4/ip_gre.c#L564">564</a>         <a href="ident?i=flags">flags</a> = 0;
<a name="L565" href="source/net/ipv4/ip_gre.c#L565">565</a>         if (<a href="ident?i=data">data</a>[IFLA_GRE_IFLAGS])
<a name="L566" href="source/net/ipv4/ip_gre.c#L566">566</a>                 <a href="ident?i=flags">flags</a> |= <a href="ident?i=nla_get_be16">nla_get_be16</a>(<a href="ident?i=data">data</a>[IFLA_GRE_IFLAGS]);
<a name="L567" href="source/net/ipv4/ip_gre.c#L567">567</a>         if (<a href="ident?i=data">data</a>[IFLA_GRE_OFLAGS])
<a name="L568" href="source/net/ipv4/ip_gre.c#L568">568</a>                 <a href="ident?i=flags">flags</a> |= <a href="ident?i=nla_get_be16">nla_get_be16</a>(<a href="ident?i=data">data</a>[IFLA_GRE_OFLAGS]);
<a name="L569" href="source/net/ipv4/ip_gre.c#L569">569</a>         if (<a href="ident?i=flags">flags</a> &amp; (<a href="ident?i=GRE_VERSION">GRE_VERSION</a>|<a href="ident?i=GRE_ROUTING">GRE_ROUTING</a>))
<a name="L570" href="source/net/ipv4/ip_gre.c#L570">570</a>                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L571" href="source/net/ipv4/ip_gre.c#L571">571</a> 
<a name="L572" href="source/net/ipv4/ip_gre.c#L572">572</a>         return 0;
<a name="L573" href="source/net/ipv4/ip_gre.c#L573">573</a> }
<a name="L574" href="source/net/ipv4/ip_gre.c#L574">574</a> 
<a name="L575" href="source/net/ipv4/ip_gre.c#L575">575</a> static int <a href="ident?i=ipgre_tap_validate">ipgre_tap_validate</a>(struct <a href="ident?i=nlattr">nlattr</a> *<a href="ident?i=tb">tb</a>[], struct <a href="ident?i=nlattr">nlattr</a> *<a href="ident?i=data">data</a>[])
<a name="L576" href="source/net/ipv4/ip_gre.c#L576">576</a> {
<a name="L577" href="source/net/ipv4/ip_gre.c#L577">577</a>         <a href="ident?i=__be32">__be32</a> <a href="ident?i=daddr">daddr</a>;
<a name="L578" href="source/net/ipv4/ip_gre.c#L578">578</a> 
<a name="L579" href="source/net/ipv4/ip_gre.c#L579">579</a>         if (<a href="ident?i=tb">tb</a>[IFLA_ADDRESS]) {
<a name="L580" href="source/net/ipv4/ip_gre.c#L580">580</a>                 if (<a href="ident?i=nla_len">nla_len</a>(<a href="ident?i=tb">tb</a>[IFLA_ADDRESS]) != <a href="ident?i=ETH_ALEN">ETH_ALEN</a>)
<a name="L581" href="source/net/ipv4/ip_gre.c#L581">581</a>                         return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L582" href="source/net/ipv4/ip_gre.c#L582">582</a>                 if (!<a href="ident?i=is_valid_ether_addr">is_valid_ether_addr</a>(<a href="ident?i=nla_data">nla_data</a>(<a href="ident?i=tb">tb</a>[IFLA_ADDRESS])))
<a name="L583" href="source/net/ipv4/ip_gre.c#L583">583</a>                         return -<a href="ident?i=EADDRNOTAVAIL">EADDRNOTAVAIL</a>;
<a name="L584" href="source/net/ipv4/ip_gre.c#L584">584</a>         }
<a name="L585" href="source/net/ipv4/ip_gre.c#L585">585</a> 
<a name="L586" href="source/net/ipv4/ip_gre.c#L586">586</a>         if (!<a href="ident?i=data">data</a>)
<a name="L587" href="source/net/ipv4/ip_gre.c#L587">587</a>                 goto <a href="ident?i=out">out</a>;
<a name="L588" href="source/net/ipv4/ip_gre.c#L588">588</a> 
<a name="L589" href="source/net/ipv4/ip_gre.c#L589">589</a>         if (<a href="ident?i=data">data</a>[IFLA_GRE_REMOTE]) {
<a name="L590" href="source/net/ipv4/ip_gre.c#L590">590</a>                 <a href="ident?i=memcpy">memcpy</a>(&amp;<a href="ident?i=daddr">daddr</a>, <a href="ident?i=nla_data">nla_data</a>(<a href="ident?i=data">data</a>[IFLA_GRE_REMOTE]), 4);
<a name="L591" href="source/net/ipv4/ip_gre.c#L591">591</a>                 if (!<a href="ident?i=daddr">daddr</a>)
<a name="L592" href="source/net/ipv4/ip_gre.c#L592">592</a>                         return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L593" href="source/net/ipv4/ip_gre.c#L593">593</a>         }
<a name="L594" href="source/net/ipv4/ip_gre.c#L594">594</a> 
<a name="L595" href="source/net/ipv4/ip_gre.c#L595">595</a> <a href="ident?i=out">out</a>:
<a name="L596" href="source/net/ipv4/ip_gre.c#L596">596</a>         return <a href="ident?i=ipgre_tunnel_validate">ipgre_tunnel_validate</a>(<a href="ident?i=tb">tb</a>, <a href="ident?i=data">data</a>);
<a name="L597" href="source/net/ipv4/ip_gre.c#L597">597</a> }
<a name="L598" href="source/net/ipv4/ip_gre.c#L598">598</a> 
<a name="L599" href="source/net/ipv4/ip_gre.c#L599">599</a> static void <a href="ident?i=ipgre_netlink_parms">ipgre_netlink_parms</a>(struct <a href="ident?i=nlattr">nlattr</a> *<a href="ident?i=data">data</a>[], struct <a href="ident?i=nlattr">nlattr</a> *<a href="ident?i=tb">tb</a>[],
<a name="L600" href="source/net/ipv4/ip_gre.c#L600">600</a>                                struct <a href="ident?i=ip_tunnel_parm">ip_tunnel_parm</a> *<a href="ident?i=parms">parms</a>)
<a name="L601" href="source/net/ipv4/ip_gre.c#L601">601</a> {
<a name="L602" href="source/net/ipv4/ip_gre.c#L602">602</a>         <a href="ident?i=memset">memset</a>(<a href="ident?i=parms">parms</a>, 0, sizeof(*<a href="ident?i=parms">parms</a>));
<a name="L603" href="source/net/ipv4/ip_gre.c#L603">603</a> 
<a name="L604" href="source/net/ipv4/ip_gre.c#L604">604</a>         <a href="ident?i=parms">parms</a>-&gt;iph.<a href="ident?i=protocol">protocol</a> = <a href="ident?i=IPPROTO_GRE">IPPROTO_GRE</a>;
<a name="L605" href="source/net/ipv4/ip_gre.c#L605">605</a> 
<a name="L606" href="source/net/ipv4/ip_gre.c#L606">606</a>         if (!<a href="ident?i=data">data</a>)
<a name="L607" href="source/net/ipv4/ip_gre.c#L607">607</a>                 return;
<a name="L608" href="source/net/ipv4/ip_gre.c#L608">608</a> 
<a name="L609" href="source/net/ipv4/ip_gre.c#L609">609</a>         if (<a href="ident?i=data">data</a>[IFLA_GRE_LINK])
<a name="L610" href="source/net/ipv4/ip_gre.c#L610">610</a>                 <a href="ident?i=parms">parms</a>-&gt;<a href="ident?i=link">link</a> = <a href="ident?i=nla_get_u32">nla_get_u32</a>(<a href="ident?i=data">data</a>[IFLA_GRE_LINK]);
<a name="L611" href="source/net/ipv4/ip_gre.c#L611">611</a> 
<a name="L612" href="source/net/ipv4/ip_gre.c#L612">612</a>         if (<a href="ident?i=data">data</a>[IFLA_GRE_IFLAGS])
<a name="L613" href="source/net/ipv4/ip_gre.c#L613">613</a>                 <a href="ident?i=parms">parms</a>-&gt;i_flags = <a href="ident?i=gre_flags_to_tnl_flags">gre_flags_to_tnl_flags</a>(<a href="ident?i=nla_get_be16">nla_get_be16</a>(<a href="ident?i=data">data</a>[IFLA_GRE_IFLAGS]));
<a name="L614" href="source/net/ipv4/ip_gre.c#L614">614</a> 
<a name="L615" href="source/net/ipv4/ip_gre.c#L615">615</a>         if (<a href="ident?i=data">data</a>[IFLA_GRE_OFLAGS])
<a name="L616" href="source/net/ipv4/ip_gre.c#L616">616</a>                 <a href="ident?i=parms">parms</a>-&gt;o_flags = <a href="ident?i=gre_flags_to_tnl_flags">gre_flags_to_tnl_flags</a>(<a href="ident?i=nla_get_be16">nla_get_be16</a>(<a href="ident?i=data">data</a>[IFLA_GRE_OFLAGS]));
<a name="L617" href="source/net/ipv4/ip_gre.c#L617">617</a> 
<a name="L618" href="source/net/ipv4/ip_gre.c#L618">618</a>         if (<a href="ident?i=data">data</a>[IFLA_GRE_IKEY])
<a name="L619" href="source/net/ipv4/ip_gre.c#L619">619</a>                 <a href="ident?i=parms">parms</a>-&gt;i_key = <a href="ident?i=nla_get_be32">nla_get_be32</a>(<a href="ident?i=data">data</a>[IFLA_GRE_IKEY]);
<a name="L620" href="source/net/ipv4/ip_gre.c#L620">620</a> 
<a name="L621" href="source/net/ipv4/ip_gre.c#L621">621</a>         if (<a href="ident?i=data">data</a>[IFLA_GRE_OKEY])
<a name="L622" href="source/net/ipv4/ip_gre.c#L622">622</a>                 <a href="ident?i=parms">parms</a>-&gt;o_key = <a href="ident?i=nla_get_be32">nla_get_be32</a>(<a href="ident?i=data">data</a>[IFLA_GRE_OKEY]);
<a name="L623" href="source/net/ipv4/ip_gre.c#L623">623</a> 
<a name="L624" href="source/net/ipv4/ip_gre.c#L624">624</a>         if (<a href="ident?i=data">data</a>[IFLA_GRE_LOCAL])
<a name="L625" href="source/net/ipv4/ip_gre.c#L625">625</a>                 <a href="ident?i=parms">parms</a>-&gt;iph.<a href="ident?i=saddr">saddr</a> = <a href="ident?i=nla_get_in_addr">nla_get_in_addr</a>(<a href="ident?i=data">data</a>[IFLA_GRE_LOCAL]);
<a name="L626" href="source/net/ipv4/ip_gre.c#L626">626</a> 
<a name="L627" href="source/net/ipv4/ip_gre.c#L627">627</a>         if (<a href="ident?i=data">data</a>[IFLA_GRE_REMOTE])
<a name="L628" href="source/net/ipv4/ip_gre.c#L628">628</a>                 <a href="ident?i=parms">parms</a>-&gt;iph.<a href="ident?i=daddr">daddr</a> = <a href="ident?i=nla_get_in_addr">nla_get_in_addr</a>(<a href="ident?i=data">data</a>[IFLA_GRE_REMOTE]);
<a name="L629" href="source/net/ipv4/ip_gre.c#L629">629</a> 
<a name="L630" href="source/net/ipv4/ip_gre.c#L630">630</a>         if (<a href="ident?i=data">data</a>[IFLA_GRE_TTL])
<a name="L631" href="source/net/ipv4/ip_gre.c#L631">631</a>                 <a href="ident?i=parms">parms</a>-&gt;iph.<a href="ident?i=ttl">ttl</a> = <a href="ident?i=nla_get_u8">nla_get_u8</a>(<a href="ident?i=data">data</a>[IFLA_GRE_TTL]);
<a name="L632" href="source/net/ipv4/ip_gre.c#L632">632</a> 
<a name="L633" href="source/net/ipv4/ip_gre.c#L633">633</a>         if (<a href="ident?i=data">data</a>[IFLA_GRE_TOS])
<a name="L634" href="source/net/ipv4/ip_gre.c#L634">634</a>                 <a href="ident?i=parms">parms</a>-&gt;iph.tos = <a href="ident?i=nla_get_u8">nla_get_u8</a>(<a href="ident?i=data">data</a>[IFLA_GRE_TOS]);
<a name="L635" href="source/net/ipv4/ip_gre.c#L635">635</a> 
<a name="L636" href="source/net/ipv4/ip_gre.c#L636">636</a>         if (!<a href="ident?i=data">data</a>[IFLA_GRE_PMTUDISC] || <a href="ident?i=nla_get_u8">nla_get_u8</a>(<a href="ident?i=data">data</a>[IFLA_GRE_PMTUDISC]))
<a name="L637" href="source/net/ipv4/ip_gre.c#L637">637</a>                 <a href="ident?i=parms">parms</a>-&gt;iph.frag_off = <a href="ident?i=htons">htons</a>(<a href="ident?i=IP_DF">IP_DF</a>);
<a name="L638" href="source/net/ipv4/ip_gre.c#L638">638</a> }
<a name="L639" href="source/net/ipv4/ip_gre.c#L639">639</a> 
<a name="L640" href="source/net/ipv4/ip_gre.c#L640">640</a> <b><i>/* This function returns true when ENCAP attributes are present in the nl msg */</i></b>
<a name="L641" href="source/net/ipv4/ip_gre.c#L641">641</a> static <a href="ident?i=bool">bool</a> <a href="ident?i=ipgre_netlink_encap_parms">ipgre_netlink_encap_parms</a>(struct <a href="ident?i=nlattr">nlattr</a> *<a href="ident?i=data">data</a>[],
<a name="L642" href="source/net/ipv4/ip_gre.c#L642">642</a>                                       struct <a href="ident?i=ip_tunnel_encap">ip_tunnel_encap</a> *ipencap)
<a name="L643" href="source/net/ipv4/ip_gre.c#L643">643</a> {
<a name="L644" href="source/net/ipv4/ip_gre.c#L644">644</a>         <a href="ident?i=bool">bool</a> <a href="ident?i=ret">ret</a> = <a href="ident?i=false">false</a>;
<a name="L645" href="source/net/ipv4/ip_gre.c#L645">645</a> 
<a name="L646" href="source/net/ipv4/ip_gre.c#L646">646</a>         <a href="ident?i=memset">memset</a>(ipencap, 0, sizeof(*ipencap));
<a name="L647" href="source/net/ipv4/ip_gre.c#L647">647</a> 
<a name="L648" href="source/net/ipv4/ip_gre.c#L648">648</a>         if (!<a href="ident?i=data">data</a>)
<a name="L649" href="source/net/ipv4/ip_gre.c#L649">649</a>                 return <a href="ident?i=ret">ret</a>;
<a name="L650" href="source/net/ipv4/ip_gre.c#L650">650</a> 
<a name="L651" href="source/net/ipv4/ip_gre.c#L651">651</a>         if (<a href="ident?i=data">data</a>[IFLA_GRE_ENCAP_TYPE]) {
<a name="L652" href="source/net/ipv4/ip_gre.c#L652">652</a>                 <a href="ident?i=ret">ret</a> = <a href="ident?i=true">true</a>;
<a name="L653" href="source/net/ipv4/ip_gre.c#L653">653</a>                 ipencap-&gt;<a href="ident?i=type">type</a> = <a href="ident?i=nla_get_u16">nla_get_u16</a>(<a href="ident?i=data">data</a>[IFLA_GRE_ENCAP_TYPE]);
<a name="L654" href="source/net/ipv4/ip_gre.c#L654">654</a>         }
<a name="L655" href="source/net/ipv4/ip_gre.c#L655">655</a> 
<a name="L656" href="source/net/ipv4/ip_gre.c#L656">656</a>         if (<a href="ident?i=data">data</a>[IFLA_GRE_ENCAP_FLAGS]) {
<a name="L657" href="source/net/ipv4/ip_gre.c#L657">657</a>                 <a href="ident?i=ret">ret</a> = <a href="ident?i=true">true</a>;
<a name="L658" href="source/net/ipv4/ip_gre.c#L658">658</a>                 ipencap-&gt;<a href="ident?i=flags">flags</a> = <a href="ident?i=nla_get_u16">nla_get_u16</a>(<a href="ident?i=data">data</a>[IFLA_GRE_ENCAP_FLAGS]);
<a name="L659" href="source/net/ipv4/ip_gre.c#L659">659</a>         }
<a name="L660" href="source/net/ipv4/ip_gre.c#L660">660</a> 
<a name="L661" href="source/net/ipv4/ip_gre.c#L661">661</a>         if (<a href="ident?i=data">data</a>[IFLA_GRE_ENCAP_SPORT]) {
<a name="L662" href="source/net/ipv4/ip_gre.c#L662">662</a>                 <a href="ident?i=ret">ret</a> = <a href="ident?i=true">true</a>;
<a name="L663" href="source/net/ipv4/ip_gre.c#L663">663</a>                 ipencap-&gt;sport = <a href="ident?i=nla_get_be16">nla_get_be16</a>(<a href="ident?i=data">data</a>[IFLA_GRE_ENCAP_SPORT]);
<a name="L664" href="source/net/ipv4/ip_gre.c#L664">664</a>         }
<a name="L665" href="source/net/ipv4/ip_gre.c#L665">665</a> 
<a name="L666" href="source/net/ipv4/ip_gre.c#L666">666</a>         if (<a href="ident?i=data">data</a>[IFLA_GRE_ENCAP_DPORT]) {
<a name="L667" href="source/net/ipv4/ip_gre.c#L667">667</a>                 <a href="ident?i=ret">ret</a> = <a href="ident?i=true">true</a>;
<a name="L668" href="source/net/ipv4/ip_gre.c#L668">668</a>                 ipencap-&gt;dport = <a href="ident?i=nla_get_be16">nla_get_be16</a>(<a href="ident?i=data">data</a>[IFLA_GRE_ENCAP_DPORT]);
<a name="L669" href="source/net/ipv4/ip_gre.c#L669">669</a>         }
<a name="L670" href="source/net/ipv4/ip_gre.c#L670">670</a> 
<a name="L671" href="source/net/ipv4/ip_gre.c#L671">671</a>         return <a href="ident?i=ret">ret</a>;
<a name="L672" href="source/net/ipv4/ip_gre.c#L672">672</a> }
<a name="L673" href="source/net/ipv4/ip_gre.c#L673">673</a> 
<a name="L674" href="source/net/ipv4/ip_gre.c#L674">674</a> static int <a href="ident?i=gre_tap_init">gre_tap_init</a>(struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>)
<a name="L675" href="source/net/ipv4/ip_gre.c#L675">675</a> {
<a name="L676" href="source/net/ipv4/ip_gre.c#L676">676</a>         <a href="ident?i=__gre_tunnel_init">__gre_tunnel_init</a>(<a href="ident?i=dev">dev</a>);
<a name="L677" href="source/net/ipv4/ip_gre.c#L677">677</a>         <a href="ident?i=dev">dev</a>-&gt;priv_flags |= <a href="ident?i=IFF_LIVE_ADDR_CHANGE">IFF_LIVE_ADDR_CHANGE</a>;
<a name="L678" href="source/net/ipv4/ip_gre.c#L678">678</a> 
<a name="L679" href="source/net/ipv4/ip_gre.c#L679">679</a>         return <a href="ident?i=ip_tunnel_init">ip_tunnel_init</a>(<a href="ident?i=dev">dev</a>);
<a name="L680" href="source/net/ipv4/ip_gre.c#L680">680</a> }
<a name="L681" href="source/net/ipv4/ip_gre.c#L681">681</a> 
<a name="L682" href="source/net/ipv4/ip_gre.c#L682">682</a> static const struct <a href="ident?i=net_device_ops">net_device_ops</a> <a href="ident?i=gre_tap_netdev_ops">gre_tap_netdev_ops</a> = {
<a name="L683" href="source/net/ipv4/ip_gre.c#L683">683</a>         .ndo_init               = <a href="ident?i=gre_tap_init">gre_tap_init</a>,
<a name="L684" href="source/net/ipv4/ip_gre.c#L684">684</a>         .ndo_uninit             = <a href="ident?i=ip_tunnel_uninit">ip_tunnel_uninit</a>,
<a name="L685" href="source/net/ipv4/ip_gre.c#L685">685</a>         .ndo_start_xmit         = <a href="ident?i=gre_tap_xmit">gre_tap_xmit</a>,
<a name="L686" href="source/net/ipv4/ip_gre.c#L686">686</a>         .ndo_set_mac_address    = <a href="ident?i=eth_mac_addr">eth_mac_addr</a>,
<a name="L687" href="source/net/ipv4/ip_gre.c#L687">687</a>         .ndo_validate_addr      = <a href="ident?i=eth_validate_addr">eth_validate_addr</a>,
<a name="L688" href="source/net/ipv4/ip_gre.c#L688">688</a>         .ndo_change_mtu         = <a href="ident?i=ip_tunnel_change_mtu">ip_tunnel_change_mtu</a>,
<a name="L689" href="source/net/ipv4/ip_gre.c#L689">689</a>         .ndo_get_stats64        = <a href="ident?i=ip_tunnel_get_stats64">ip_tunnel_get_stats64</a>,
<a name="L690" href="source/net/ipv4/ip_gre.c#L690">690</a>         .ndo_get_iflink         = <a href="ident?i=ip_tunnel_get_iflink">ip_tunnel_get_iflink</a>,
<a name="L691" href="source/net/ipv4/ip_gre.c#L691">691</a> };
<a name="L692" href="source/net/ipv4/ip_gre.c#L692">692</a> 
<a name="L693" href="source/net/ipv4/ip_gre.c#L693">693</a> static void <a href="ident?i=ipgre_tap_setup">ipgre_tap_setup</a>(struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>)
<a name="L694" href="source/net/ipv4/ip_gre.c#L694">694</a> {
<a name="L695" href="source/net/ipv4/ip_gre.c#L695">695</a>         <a href="ident?i=ether_setup">ether_setup</a>(<a href="ident?i=dev">dev</a>);
<a name="L696" href="source/net/ipv4/ip_gre.c#L696">696</a>         <a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=netdev_ops">netdev_ops</a>         = &amp;<a href="ident?i=gre_tap_netdev_ops">gre_tap_netdev_ops</a>;
<a name="L697" href="source/net/ipv4/ip_gre.c#L697">697</a>         <a href="ident?i=dev">dev</a>-&gt;priv_flags         |= <a href="ident?i=IFF_LIVE_ADDR_CHANGE">IFF_LIVE_ADDR_CHANGE</a>;
<a name="L698" href="source/net/ipv4/ip_gre.c#L698">698</a>         <a href="ident?i=ip_tunnel_setup">ip_tunnel_setup</a>(<a href="ident?i=dev">dev</a>, gre_tap_net_id);
<a name="L699" href="source/net/ipv4/ip_gre.c#L699">699</a> }
<a name="L700" href="source/net/ipv4/ip_gre.c#L700">700</a> 
<a name="L701" href="source/net/ipv4/ip_gre.c#L701">701</a> static int <a href="ident?i=ipgre_newlink">ipgre_newlink</a>(struct <a href="ident?i=net">net</a> *src_net, struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>,
<a name="L702" href="source/net/ipv4/ip_gre.c#L702">702</a>                          struct <a href="ident?i=nlattr">nlattr</a> *<a href="ident?i=tb">tb</a>[], struct <a href="ident?i=nlattr">nlattr</a> *<a href="ident?i=data">data</a>[])
<a name="L703" href="source/net/ipv4/ip_gre.c#L703">703</a> {
<a name="L704" href="source/net/ipv4/ip_gre.c#L704">704</a>         struct <a href="ident?i=ip_tunnel_parm">ip_tunnel_parm</a> <a href="ident?i=p">p</a>;
<a name="L705" href="source/net/ipv4/ip_gre.c#L705">705</a>         struct <a href="ident?i=ip_tunnel_encap">ip_tunnel_encap</a> ipencap;
<a name="L706" href="source/net/ipv4/ip_gre.c#L706">706</a> 
<a name="L707" href="source/net/ipv4/ip_gre.c#L707">707</a>         if (<a href="ident?i=ipgre_netlink_encap_parms">ipgre_netlink_encap_parms</a>(<a href="ident?i=data">data</a>, &amp;ipencap)) {
<a name="L708" href="source/net/ipv4/ip_gre.c#L708">708</a>                 struct <a href="ident?i=ip_tunnel">ip_tunnel</a> *<a href="ident?i=t">t</a> = <a href="ident?i=netdev_priv">netdev_priv</a>(<a href="ident?i=dev">dev</a>);
<a name="L709" href="source/net/ipv4/ip_gre.c#L709">709</a>                 int <a href="ident?i=err">err</a> = <a href="ident?i=ip_tunnel_encap_setup">ip_tunnel_encap_setup</a>(<a href="ident?i=t">t</a>, &amp;ipencap);
<a name="L710" href="source/net/ipv4/ip_gre.c#L710">710</a> 
<a name="L711" href="source/net/ipv4/ip_gre.c#L711">711</a>                 if (<a href="ident?i=err">err</a> &lt; 0)
<a name="L712" href="source/net/ipv4/ip_gre.c#L712">712</a>                         return <a href="ident?i=err">err</a>;
<a name="L713" href="source/net/ipv4/ip_gre.c#L713">713</a>         }
<a name="L714" href="source/net/ipv4/ip_gre.c#L714">714</a> 
<a name="L715" href="source/net/ipv4/ip_gre.c#L715">715</a>         <a href="ident?i=ipgre_netlink_parms">ipgre_netlink_parms</a>(<a href="ident?i=data">data</a>, <a href="ident?i=tb">tb</a>, &amp;<a href="ident?i=p">p</a>);
<a name="L716" href="source/net/ipv4/ip_gre.c#L716">716</a>         return <a href="ident?i=ip_tunnel_newlink">ip_tunnel_newlink</a>(<a href="ident?i=dev">dev</a>, <a href="ident?i=tb">tb</a>, &amp;<a href="ident?i=p">p</a>);
<a name="L717" href="source/net/ipv4/ip_gre.c#L717">717</a> }
<a name="L718" href="source/net/ipv4/ip_gre.c#L718">718</a> 
<a name="L719" href="source/net/ipv4/ip_gre.c#L719">719</a> static int <a href="ident?i=ipgre_changelink">ipgre_changelink</a>(struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>, struct <a href="ident?i=nlattr">nlattr</a> *<a href="ident?i=tb">tb</a>[],
<a name="L720" href="source/net/ipv4/ip_gre.c#L720">720</a>                             struct <a href="ident?i=nlattr">nlattr</a> *<a href="ident?i=data">data</a>[])
<a name="L721" href="source/net/ipv4/ip_gre.c#L721">721</a> {
<a name="L722" href="source/net/ipv4/ip_gre.c#L722">722</a>         struct <a href="ident?i=ip_tunnel_parm">ip_tunnel_parm</a> <a href="ident?i=p">p</a>;
<a name="L723" href="source/net/ipv4/ip_gre.c#L723">723</a>         struct <a href="ident?i=ip_tunnel_encap">ip_tunnel_encap</a> ipencap;
<a name="L724" href="source/net/ipv4/ip_gre.c#L724">724</a> 
<a name="L725" href="source/net/ipv4/ip_gre.c#L725">725</a>         if (<a href="ident?i=ipgre_netlink_encap_parms">ipgre_netlink_encap_parms</a>(<a href="ident?i=data">data</a>, &amp;ipencap)) {
<a name="L726" href="source/net/ipv4/ip_gre.c#L726">726</a>                 struct <a href="ident?i=ip_tunnel">ip_tunnel</a> *<a href="ident?i=t">t</a> = <a href="ident?i=netdev_priv">netdev_priv</a>(<a href="ident?i=dev">dev</a>);
<a name="L727" href="source/net/ipv4/ip_gre.c#L727">727</a>                 int <a href="ident?i=err">err</a> = <a href="ident?i=ip_tunnel_encap_setup">ip_tunnel_encap_setup</a>(<a href="ident?i=t">t</a>, &amp;ipencap);
<a name="L728" href="source/net/ipv4/ip_gre.c#L728">728</a> 
<a name="L729" href="source/net/ipv4/ip_gre.c#L729">729</a>                 if (<a href="ident?i=err">err</a> &lt; 0)
<a name="L730" href="source/net/ipv4/ip_gre.c#L730">730</a>                         return <a href="ident?i=err">err</a>;
<a name="L731" href="source/net/ipv4/ip_gre.c#L731">731</a>         }
<a name="L732" href="source/net/ipv4/ip_gre.c#L732">732</a> 
<a name="L733" href="source/net/ipv4/ip_gre.c#L733">733</a>         <a href="ident?i=ipgre_netlink_parms">ipgre_netlink_parms</a>(<a href="ident?i=data">data</a>, <a href="ident?i=tb">tb</a>, &amp;<a href="ident?i=p">p</a>);
<a name="L734" href="source/net/ipv4/ip_gre.c#L734">734</a>         return <a href="ident?i=ip_tunnel_changelink">ip_tunnel_changelink</a>(<a href="ident?i=dev">dev</a>, <a href="ident?i=tb">tb</a>, &amp;<a href="ident?i=p">p</a>);
<a name="L735" href="source/net/ipv4/ip_gre.c#L735">735</a> }
<a name="L736" href="source/net/ipv4/ip_gre.c#L736">736</a> 
<a name="L737" href="source/net/ipv4/ip_gre.c#L737">737</a> static <a href="ident?i=size_t">size_t</a> <a href="ident?i=ipgre_get_size">ipgre_get_size</a>(const struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>)
<a name="L738" href="source/net/ipv4/ip_gre.c#L738">738</a> {
<a name="L739" href="source/net/ipv4/ip_gre.c#L739">739</a>         return
<a name="L740" href="source/net/ipv4/ip_gre.c#L740">740</a>                 <b><i>/* IFLA_GRE_LINK */</i></b>
<a name="L741" href="source/net/ipv4/ip_gre.c#L741">741</a>                 <a href="ident?i=nla_total_size">nla_total_size</a>(4) +
<a name="L742" href="source/net/ipv4/ip_gre.c#L742">742</a>                 <b><i>/* IFLA_GRE_IFLAGS */</i></b>
<a name="L743" href="source/net/ipv4/ip_gre.c#L743">743</a>                 <a href="ident?i=nla_total_size">nla_total_size</a>(2) +
<a name="L744" href="source/net/ipv4/ip_gre.c#L744">744</a>                 <b><i>/* IFLA_GRE_OFLAGS */</i></b>
<a name="L745" href="source/net/ipv4/ip_gre.c#L745">745</a>                 <a href="ident?i=nla_total_size">nla_total_size</a>(2) +
<a name="L746" href="source/net/ipv4/ip_gre.c#L746">746</a>                 <b><i>/* IFLA_GRE_IKEY */</i></b>
<a name="L747" href="source/net/ipv4/ip_gre.c#L747">747</a>                 <a href="ident?i=nla_total_size">nla_total_size</a>(4) +
<a name="L748" href="source/net/ipv4/ip_gre.c#L748">748</a>                 <b><i>/* IFLA_GRE_OKEY */</i></b>
<a name="L749" href="source/net/ipv4/ip_gre.c#L749">749</a>                 <a href="ident?i=nla_total_size">nla_total_size</a>(4) +
<a name="L750" href="source/net/ipv4/ip_gre.c#L750">750</a>                 <b><i>/* IFLA_GRE_LOCAL */</i></b>
<a name="L751" href="source/net/ipv4/ip_gre.c#L751">751</a>                 <a href="ident?i=nla_total_size">nla_total_size</a>(4) +
<a name="L752" href="source/net/ipv4/ip_gre.c#L752">752</a>                 <b><i>/* IFLA_GRE_REMOTE */</i></b>
<a name="L753" href="source/net/ipv4/ip_gre.c#L753">753</a>                 <a href="ident?i=nla_total_size">nla_total_size</a>(4) +
<a name="L754" href="source/net/ipv4/ip_gre.c#L754">754</a>                 <b><i>/* IFLA_GRE_TTL */</i></b>
<a name="L755" href="source/net/ipv4/ip_gre.c#L755">755</a>                 <a href="ident?i=nla_total_size">nla_total_size</a>(1) +
<a name="L756" href="source/net/ipv4/ip_gre.c#L756">756</a>                 <b><i>/* IFLA_GRE_TOS */</i></b>
<a name="L757" href="source/net/ipv4/ip_gre.c#L757">757</a>                 <a href="ident?i=nla_total_size">nla_total_size</a>(1) +
<a name="L758" href="source/net/ipv4/ip_gre.c#L758">758</a>                 <b><i>/* IFLA_GRE_PMTUDISC */</i></b>
<a name="L759" href="source/net/ipv4/ip_gre.c#L759">759</a>                 <a href="ident?i=nla_total_size">nla_total_size</a>(1) +
<a name="L760" href="source/net/ipv4/ip_gre.c#L760">760</a>                 <b><i>/* IFLA_GRE_ENCAP_TYPE */</i></b>
<a name="L761" href="source/net/ipv4/ip_gre.c#L761">761</a>                 <a href="ident?i=nla_total_size">nla_total_size</a>(2) +
<a name="L762" href="source/net/ipv4/ip_gre.c#L762">762</a>                 <b><i>/* IFLA_GRE_ENCAP_FLAGS */</i></b>
<a name="L763" href="source/net/ipv4/ip_gre.c#L763">763</a>                 <a href="ident?i=nla_total_size">nla_total_size</a>(2) +
<a name="L764" href="source/net/ipv4/ip_gre.c#L764">764</a>                 <b><i>/* IFLA_GRE_ENCAP_SPORT */</i></b>
<a name="L765" href="source/net/ipv4/ip_gre.c#L765">765</a>                 <a href="ident?i=nla_total_size">nla_total_size</a>(2) +
<a name="L766" href="source/net/ipv4/ip_gre.c#L766">766</a>                 <b><i>/* IFLA_GRE_ENCAP_DPORT */</i></b>
<a name="L767" href="source/net/ipv4/ip_gre.c#L767">767</a>                 <a href="ident?i=nla_total_size">nla_total_size</a>(2) +
<a name="L768" href="source/net/ipv4/ip_gre.c#L768">768</a>                 0;
<a name="L769" href="source/net/ipv4/ip_gre.c#L769">769</a> }
<a name="L770" href="source/net/ipv4/ip_gre.c#L770">770</a> 
<a name="L771" href="source/net/ipv4/ip_gre.c#L771">771</a> static int <a href="ident?i=ipgre_fill_info">ipgre_fill_info</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, const struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>)
<a name="L772" href="source/net/ipv4/ip_gre.c#L772">772</a> {
<a name="L773" href="source/net/ipv4/ip_gre.c#L773">773</a>         struct <a href="ident?i=ip_tunnel">ip_tunnel</a> *<a href="ident?i=t">t</a> = <a href="ident?i=netdev_priv">netdev_priv</a>(<a href="ident?i=dev">dev</a>);
<a name="L774" href="source/net/ipv4/ip_gre.c#L774">774</a>         struct <a href="ident?i=ip_tunnel_parm">ip_tunnel_parm</a> *<a href="ident?i=p">p</a> = &amp;<a href="ident?i=t">t</a>-&gt;<a href="ident?i=parms">parms</a>;
<a name="L775" href="source/net/ipv4/ip_gre.c#L775">775</a> 
<a name="L776" href="source/net/ipv4/ip_gre.c#L776">776</a>         if (<a href="ident?i=nla_put_u32">nla_put_u32</a>(<a href="ident?i=skb">skb</a>, IFLA_GRE_LINK, <a href="ident?i=p">p</a>-&gt;<a href="ident?i=link">link</a>) ||
<a name="L777" href="source/net/ipv4/ip_gre.c#L777">777</a>             <a href="ident?i=nla_put_be16">nla_put_be16</a>(<a href="ident?i=skb">skb</a>, IFLA_GRE_IFLAGS, <a href="ident?i=tnl_flags_to_gre_flags">tnl_flags_to_gre_flags</a>(<a href="ident?i=p">p</a>-&gt;i_flags)) ||
<a name="L778" href="source/net/ipv4/ip_gre.c#L778">778</a>             <a href="ident?i=nla_put_be16">nla_put_be16</a>(<a href="ident?i=skb">skb</a>, IFLA_GRE_OFLAGS, <a href="ident?i=tnl_flags_to_gre_flags">tnl_flags_to_gre_flags</a>(<a href="ident?i=p">p</a>-&gt;o_flags)) ||
<a name="L779" href="source/net/ipv4/ip_gre.c#L779">779</a>             <a href="ident?i=nla_put_be32">nla_put_be32</a>(<a href="ident?i=skb">skb</a>, IFLA_GRE_IKEY, <a href="ident?i=p">p</a>-&gt;i_key) ||
<a name="L780" href="source/net/ipv4/ip_gre.c#L780">780</a>             <a href="ident?i=nla_put_be32">nla_put_be32</a>(<a href="ident?i=skb">skb</a>, IFLA_GRE_OKEY, <a href="ident?i=p">p</a>-&gt;o_key) ||
<a name="L781" href="source/net/ipv4/ip_gre.c#L781">781</a>             <a href="ident?i=nla_put_in_addr">nla_put_in_addr</a>(<a href="ident?i=skb">skb</a>, IFLA_GRE_LOCAL, <a href="ident?i=p">p</a>-&gt;iph.<a href="ident?i=saddr">saddr</a>) ||
<a name="L782" href="source/net/ipv4/ip_gre.c#L782">782</a>             <a href="ident?i=nla_put_in_addr">nla_put_in_addr</a>(<a href="ident?i=skb">skb</a>, IFLA_GRE_REMOTE, <a href="ident?i=p">p</a>-&gt;iph.<a href="ident?i=daddr">daddr</a>) ||
<a name="L783" href="source/net/ipv4/ip_gre.c#L783">783</a>             <a href="ident?i=nla_put_u8">nla_put_u8</a>(<a href="ident?i=skb">skb</a>, IFLA_GRE_TTL, <a href="ident?i=p">p</a>-&gt;iph.<a href="ident?i=ttl">ttl</a>) ||
<a name="L784" href="source/net/ipv4/ip_gre.c#L784">784</a>             <a href="ident?i=nla_put_u8">nla_put_u8</a>(<a href="ident?i=skb">skb</a>, IFLA_GRE_TOS, <a href="ident?i=p">p</a>-&gt;iph.tos) ||
<a name="L785" href="source/net/ipv4/ip_gre.c#L785">785</a>             <a href="ident?i=nla_put_u8">nla_put_u8</a>(<a href="ident?i=skb">skb</a>, IFLA_GRE_PMTUDISC,
<a name="L786" href="source/net/ipv4/ip_gre.c#L786">786</a>                        !!(<a href="ident?i=p">p</a>-&gt;iph.frag_off &amp; <a href="ident?i=htons">htons</a>(<a href="ident?i=IP_DF">IP_DF</a>))))
<a name="L787" href="source/net/ipv4/ip_gre.c#L787">787</a>                 goto nla_put_failure;
<a name="L788" href="source/net/ipv4/ip_gre.c#L788">788</a> 
<a name="L789" href="source/net/ipv4/ip_gre.c#L789">789</a>         if (<a href="ident?i=nla_put_u16">nla_put_u16</a>(<a href="ident?i=skb">skb</a>, IFLA_GRE_ENCAP_TYPE,
<a name="L790" href="source/net/ipv4/ip_gre.c#L790">790</a>                         <a href="ident?i=t">t</a>-&gt;encap.<a href="ident?i=type">type</a>) ||
<a name="L791" href="source/net/ipv4/ip_gre.c#L791">791</a>             <a href="ident?i=nla_put_be16">nla_put_be16</a>(<a href="ident?i=skb">skb</a>, IFLA_GRE_ENCAP_SPORT,
<a name="L792" href="source/net/ipv4/ip_gre.c#L792">792</a>                          <a href="ident?i=t">t</a>-&gt;encap.sport) ||
<a name="L793" href="source/net/ipv4/ip_gre.c#L793">793</a>             <a href="ident?i=nla_put_be16">nla_put_be16</a>(<a href="ident?i=skb">skb</a>, IFLA_GRE_ENCAP_DPORT,
<a name="L794" href="source/net/ipv4/ip_gre.c#L794">794</a>                          <a href="ident?i=t">t</a>-&gt;encap.dport) ||
<a name="L795" href="source/net/ipv4/ip_gre.c#L795">795</a>             <a href="ident?i=nla_put_u16">nla_put_u16</a>(<a href="ident?i=skb">skb</a>, IFLA_GRE_ENCAP_FLAGS,
<a name="L796" href="source/net/ipv4/ip_gre.c#L796">796</a>                         <a href="ident?i=t">t</a>-&gt;encap.<a href="ident?i=flags">flags</a>))
<a name="L797" href="source/net/ipv4/ip_gre.c#L797">797</a>                 goto nla_put_failure;
<a name="L798" href="source/net/ipv4/ip_gre.c#L798">798</a> 
<a name="L799" href="source/net/ipv4/ip_gre.c#L799">799</a>         return 0;
<a name="L800" href="source/net/ipv4/ip_gre.c#L800">800</a> 
<a name="L801" href="source/net/ipv4/ip_gre.c#L801">801</a> nla_put_failure:
<a name="L802" href="source/net/ipv4/ip_gre.c#L802">802</a>         return -<a href="ident?i=EMSGSIZE">EMSGSIZE</a>;
<a name="L803" href="source/net/ipv4/ip_gre.c#L803">803</a> }
<a name="L804" href="source/net/ipv4/ip_gre.c#L804">804</a> 
<a name="L805" href="source/net/ipv4/ip_gre.c#L805">805</a> static const struct <a href="ident?i=nla_policy">nla_policy</a> <a href="ident?i=ipgre_policy">ipgre_policy</a>[<a href="ident?i=IFLA_GRE_MAX">IFLA_GRE_MAX</a> + 1] = {
<a name="L806" href="source/net/ipv4/ip_gre.c#L806">806</a>         [IFLA_GRE_LINK]         = { .<a href="ident?i=type">type</a> = NLA_U32 },
<a name="L807" href="source/net/ipv4/ip_gre.c#L807">807</a>         [IFLA_GRE_IFLAGS]       = { .<a href="ident?i=type">type</a> = NLA_U16 },
<a name="L808" href="source/net/ipv4/ip_gre.c#L808">808</a>         [IFLA_GRE_OFLAGS]       = { .<a href="ident?i=type">type</a> = NLA_U16 },
<a name="L809" href="source/net/ipv4/ip_gre.c#L809">809</a>         [IFLA_GRE_IKEY]         = { .<a href="ident?i=type">type</a> = NLA_U32 },
<a name="L810" href="source/net/ipv4/ip_gre.c#L810">810</a>         [IFLA_GRE_OKEY]         = { .<a href="ident?i=type">type</a> = NLA_U32 },
<a name="L811" href="source/net/ipv4/ip_gre.c#L811">811</a>         [IFLA_GRE_LOCAL]        = { .<a href="ident?i=len">len</a> = <a href="ident?i=FIELD_SIZEOF">FIELD_SIZEOF</a>(struct <a href="ident?i=iphdr">iphdr</a>, <a href="ident?i=saddr">saddr</a>) },
<a name="L812" href="source/net/ipv4/ip_gre.c#L812">812</a>         [IFLA_GRE_REMOTE]       = { .<a href="ident?i=len">len</a> = <a href="ident?i=FIELD_SIZEOF">FIELD_SIZEOF</a>(struct <a href="ident?i=iphdr">iphdr</a>, <a href="ident?i=daddr">daddr</a>) },
<a name="L813" href="source/net/ipv4/ip_gre.c#L813">813</a>         [IFLA_GRE_TTL]          = { .<a href="ident?i=type">type</a> = NLA_U8 },
<a name="L814" href="source/net/ipv4/ip_gre.c#L814">814</a>         [IFLA_GRE_TOS]          = { .<a href="ident?i=type">type</a> = NLA_U8 },
<a name="L815" href="source/net/ipv4/ip_gre.c#L815">815</a>         [IFLA_GRE_PMTUDISC]     = { .<a href="ident?i=type">type</a> = NLA_U8 },
<a name="L816" href="source/net/ipv4/ip_gre.c#L816">816</a>         [IFLA_GRE_ENCAP_TYPE]   = { .<a href="ident?i=type">type</a> = NLA_U16 },
<a name="L817" href="source/net/ipv4/ip_gre.c#L817">817</a>         [IFLA_GRE_ENCAP_FLAGS]  = { .<a href="ident?i=type">type</a> = NLA_U16 },
<a name="L818" href="source/net/ipv4/ip_gre.c#L818">818</a>         [IFLA_GRE_ENCAP_SPORT]  = { .<a href="ident?i=type">type</a> = NLA_U16 },
<a name="L819" href="source/net/ipv4/ip_gre.c#L819">819</a>         [IFLA_GRE_ENCAP_DPORT]  = { .<a href="ident?i=type">type</a> = NLA_U16 },
<a name="L820" href="source/net/ipv4/ip_gre.c#L820">820</a> };
<a name="L821" href="source/net/ipv4/ip_gre.c#L821">821</a> 
<a name="L822" href="source/net/ipv4/ip_gre.c#L822">822</a> static struct <a href="ident?i=rtnl_link_ops">rtnl_link_ops</a> ipgre_link_ops <a href="ident?i=__read_mostly">__read_mostly</a> = {
<a name="L823" href="source/net/ipv4/ip_gre.c#L823">823</a>         .kind           = <i>"gre"</i>,
<a name="L824" href="source/net/ipv4/ip_gre.c#L824">824</a>         .maxtype        = <a href="ident?i=IFLA_GRE_MAX">IFLA_GRE_MAX</a>,
<a name="L825" href="source/net/ipv4/ip_gre.c#L825">825</a>         .<a href="ident?i=policy">policy</a>         = <a href="ident?i=ipgre_policy">ipgre_policy</a>,
<a name="L826" href="source/net/ipv4/ip_gre.c#L826">826</a>         .priv_size      = sizeof(struct <a href="ident?i=ip_tunnel">ip_tunnel</a>),
<a name="L827" href="source/net/ipv4/ip_gre.c#L827">827</a>         .<a href="ident?i=setup">setup</a>          = <a href="ident?i=ipgre_tunnel_setup">ipgre_tunnel_setup</a>,
<a name="L828" href="source/net/ipv4/ip_gre.c#L828">828</a>         .<a href="ident?i=validate">validate</a>       = <a href="ident?i=ipgre_tunnel_validate">ipgre_tunnel_validate</a>,
<a name="L829" href="source/net/ipv4/ip_gre.c#L829">829</a>         .newlink        = <a href="ident?i=ipgre_newlink">ipgre_newlink</a>,
<a name="L830" href="source/net/ipv4/ip_gre.c#L830">830</a>         .changelink     = <a href="ident?i=ipgre_changelink">ipgre_changelink</a>,
<a name="L831" href="source/net/ipv4/ip_gre.c#L831">831</a>         .dellink        = <a href="ident?i=ip_tunnel_dellink">ip_tunnel_dellink</a>,
<a name="L832" href="source/net/ipv4/ip_gre.c#L832">832</a>         .<a href="ident?i=get_size">get_size</a>       = <a href="ident?i=ipgre_get_size">ipgre_get_size</a>,
<a name="L833" href="source/net/ipv4/ip_gre.c#L833">833</a>         .fill_info      = <a href="ident?i=ipgre_fill_info">ipgre_fill_info</a>,
<a name="L834" href="source/net/ipv4/ip_gre.c#L834">834</a>         .get_link_net   = <a href="ident?i=ip_tunnel_get_link_net">ip_tunnel_get_link_net</a>,
<a name="L835" href="source/net/ipv4/ip_gre.c#L835">835</a> };
<a name="L836" href="source/net/ipv4/ip_gre.c#L836">836</a> 
<a name="L837" href="source/net/ipv4/ip_gre.c#L837">837</a> static struct <a href="ident?i=rtnl_link_ops">rtnl_link_ops</a> ipgre_tap_ops <a href="ident?i=__read_mostly">__read_mostly</a> = {
<a name="L838" href="source/net/ipv4/ip_gre.c#L838">838</a>         .kind           = <i>"gretap"</i>,
<a name="L839" href="source/net/ipv4/ip_gre.c#L839">839</a>         .maxtype        = <a href="ident?i=IFLA_GRE_MAX">IFLA_GRE_MAX</a>,
<a name="L840" href="source/net/ipv4/ip_gre.c#L840">840</a>         .<a href="ident?i=policy">policy</a>         = <a href="ident?i=ipgre_policy">ipgre_policy</a>,
<a name="L841" href="source/net/ipv4/ip_gre.c#L841">841</a>         .priv_size      = sizeof(struct <a href="ident?i=ip_tunnel">ip_tunnel</a>),
<a name="L842" href="source/net/ipv4/ip_gre.c#L842">842</a>         .<a href="ident?i=setup">setup</a>          = <a href="ident?i=ipgre_tap_setup">ipgre_tap_setup</a>,
<a name="L843" href="source/net/ipv4/ip_gre.c#L843">843</a>         .<a href="ident?i=validate">validate</a>       = <a href="ident?i=ipgre_tap_validate">ipgre_tap_validate</a>,
<a name="L844" href="source/net/ipv4/ip_gre.c#L844">844</a>         .newlink        = <a href="ident?i=ipgre_newlink">ipgre_newlink</a>,
<a name="L845" href="source/net/ipv4/ip_gre.c#L845">845</a>         .changelink     = <a href="ident?i=ipgre_changelink">ipgre_changelink</a>,
<a name="L846" href="source/net/ipv4/ip_gre.c#L846">846</a>         .dellink        = <a href="ident?i=ip_tunnel_dellink">ip_tunnel_dellink</a>,
<a name="L847" href="source/net/ipv4/ip_gre.c#L847">847</a>         .<a href="ident?i=get_size">get_size</a>       = <a href="ident?i=ipgre_get_size">ipgre_get_size</a>,
<a name="L848" href="source/net/ipv4/ip_gre.c#L848">848</a>         .fill_info      = <a href="ident?i=ipgre_fill_info">ipgre_fill_info</a>,
<a name="L849" href="source/net/ipv4/ip_gre.c#L849">849</a>         .get_link_net   = <a href="ident?i=ip_tunnel_get_link_net">ip_tunnel_get_link_net</a>,
<a name="L850" href="source/net/ipv4/ip_gre.c#L850">850</a> };
<a name="L851" href="source/net/ipv4/ip_gre.c#L851">851</a> 
<a name="L852" href="source/net/ipv4/ip_gre.c#L852">852</a> static int <a href="ident?i=__net_init">__net_init</a> <a href="ident?i=ipgre_tap_init_net">ipgre_tap_init_net</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>)
<a name="L853" href="source/net/ipv4/ip_gre.c#L853">853</a> {
<a name="L854" href="source/net/ipv4/ip_gre.c#L854">854</a>         return <a href="ident?i=ip_tunnel_init_net">ip_tunnel_init_net</a>(<a href="ident?i=net">net</a>, gre_tap_net_id, &amp;ipgre_tap_ops, <a href="ident?i=NULL">NULL</a>);
<a name="L855" href="source/net/ipv4/ip_gre.c#L855">855</a> }
<a name="L856" href="source/net/ipv4/ip_gre.c#L856">856</a> 
<a name="L857" href="source/net/ipv4/ip_gre.c#L857">857</a> static void <a href="ident?i=__net_exit">__net_exit</a> <a href="ident?i=ipgre_tap_exit_net">ipgre_tap_exit_net</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>)
<a name="L858" href="source/net/ipv4/ip_gre.c#L858">858</a> {
<a name="L859" href="source/net/ipv4/ip_gre.c#L859">859</a>         struct <a href="ident?i=ip_tunnel_net">ip_tunnel_net</a> *itn = <a href="ident?i=net_generic">net_generic</a>(<a href="ident?i=net">net</a>, gre_tap_net_id);
<a name="L860" href="source/net/ipv4/ip_gre.c#L860">860</a>         <a href="ident?i=ip_tunnel_delete_net">ip_tunnel_delete_net</a>(itn, &amp;ipgre_tap_ops);
<a name="L861" href="source/net/ipv4/ip_gre.c#L861">861</a> }
<a name="L862" href="source/net/ipv4/ip_gre.c#L862">862</a> 
<a name="L863" href="source/net/ipv4/ip_gre.c#L863">863</a> static struct <a href="ident?i=pernet_operations">pernet_operations</a> <a href="ident?i=ipgre_tap_net_ops">ipgre_tap_net_ops</a> = {
<a name="L864" href="source/net/ipv4/ip_gre.c#L864">864</a>         .<a href="ident?i=init">init</a> = <a href="ident?i=ipgre_tap_init_net">ipgre_tap_init_net</a>,
<a name="L865" href="source/net/ipv4/ip_gre.c#L865">865</a>         .<a href="ident?i=exit">exit</a> = <a href="ident?i=ipgre_tap_exit_net">ipgre_tap_exit_net</a>,
<a name="L866" href="source/net/ipv4/ip_gre.c#L866">866</a>         .<a href="ident?i=id">id</a>   = &amp;gre_tap_net_id,
<a name="L867" href="source/net/ipv4/ip_gre.c#L867">867</a>         .<a href="ident?i=size">size</a> = sizeof(struct <a href="ident?i=ip_tunnel_net">ip_tunnel_net</a>),
<a name="L868" href="source/net/ipv4/ip_gre.c#L868">868</a> };
<a name="L869" href="source/net/ipv4/ip_gre.c#L869">869</a> 
<a name="L870" href="source/net/ipv4/ip_gre.c#L870">870</a> static int <a href="ident?i=__init">__init</a> <a href="ident?i=ipgre_init">ipgre_init</a>(void)
<a name="L871" href="source/net/ipv4/ip_gre.c#L871">871</a> {
<a name="L872" href="source/net/ipv4/ip_gre.c#L872">872</a>         int <a href="ident?i=err">err</a>;
<a name="L873" href="source/net/ipv4/ip_gre.c#L873">873</a> 
<a name="L874" href="source/net/ipv4/ip_gre.c#L874">874</a>         <a href="ident?i=pr_info">pr_info</a>(<i>"GRE over IPv4 tunneling driver\n"</i>);
<a name="L875" href="source/net/ipv4/ip_gre.c#L875">875</a> 
<a name="L876" href="source/net/ipv4/ip_gre.c#L876">876</a>         <a href="ident?i=err">err</a> = <a href="ident?i=register_pernet_device">register_pernet_device</a>(&amp;<a href="ident?i=ipgre_net_ops">ipgre_net_ops</a>);
<a name="L877" href="source/net/ipv4/ip_gre.c#L877">877</a>         if (<a href="ident?i=err">err</a> &lt; 0)
<a name="L878" href="source/net/ipv4/ip_gre.c#L878">878</a>                 return <a href="ident?i=err">err</a>;
<a name="L879" href="source/net/ipv4/ip_gre.c#L879">879</a> 
<a name="L880" href="source/net/ipv4/ip_gre.c#L880">880</a>         <a href="ident?i=err">err</a> = <a href="ident?i=register_pernet_device">register_pernet_device</a>(&amp;<a href="ident?i=ipgre_tap_net_ops">ipgre_tap_net_ops</a>);
<a name="L881" href="source/net/ipv4/ip_gre.c#L881">881</a>         if (<a href="ident?i=err">err</a> &lt; 0)
<a name="L882" href="source/net/ipv4/ip_gre.c#L882">882</a>                 goto pnet_tap_faied;
<a name="L883" href="source/net/ipv4/ip_gre.c#L883">883</a> 
<a name="L884" href="source/net/ipv4/ip_gre.c#L884">884</a>         <a href="ident?i=err">err</a> = <a href="ident?i=gre_cisco_register">gre_cisco_register</a>(&amp;<a href="ident?i=ipgre_protocol">ipgre_protocol</a>);
<a name="L885" href="source/net/ipv4/ip_gre.c#L885">885</a>         if (<a href="ident?i=err">err</a> &lt; 0) {
<a name="L886" href="source/net/ipv4/ip_gre.c#L886">886</a>                 <a href="ident?i=pr_info">pr_info</a>(<i>"%s: can't add protocol\n"</i>, <a href="ident?i=__func__">__func__</a>);
<a name="L887" href="source/net/ipv4/ip_gre.c#L887">887</a>                 goto add_proto_failed;
<a name="L888" href="source/net/ipv4/ip_gre.c#L888">888</a>         }
<a name="L889" href="source/net/ipv4/ip_gre.c#L889">889</a> 
<a name="L890" href="source/net/ipv4/ip_gre.c#L890">890</a>         <a href="ident?i=err">err</a> = <a href="ident?i=rtnl_link_register">rtnl_link_register</a>(&amp;ipgre_link_ops);
<a name="L891" href="source/net/ipv4/ip_gre.c#L891">891</a>         if (<a href="ident?i=err">err</a> &lt; 0)
<a name="L892" href="source/net/ipv4/ip_gre.c#L892">892</a>                 goto rtnl_link_failed;
<a name="L893" href="source/net/ipv4/ip_gre.c#L893">893</a> 
<a name="L894" href="source/net/ipv4/ip_gre.c#L894">894</a>         <a href="ident?i=err">err</a> = <a href="ident?i=rtnl_link_register">rtnl_link_register</a>(&amp;ipgre_tap_ops);
<a name="L895" href="source/net/ipv4/ip_gre.c#L895">895</a>         if (<a href="ident?i=err">err</a> &lt; 0)
<a name="L896" href="source/net/ipv4/ip_gre.c#L896">896</a>                 goto tap_ops_failed;
<a name="L897" href="source/net/ipv4/ip_gre.c#L897">897</a> 
<a name="L898" href="source/net/ipv4/ip_gre.c#L898">898</a>         return 0;
<a name="L899" href="source/net/ipv4/ip_gre.c#L899">899</a> 
<a name="L900" href="source/net/ipv4/ip_gre.c#L900">900</a> tap_ops_failed:
<a name="L901" href="source/net/ipv4/ip_gre.c#L901">901</a>         <a href="ident?i=rtnl_link_unregister">rtnl_link_unregister</a>(&amp;ipgre_link_ops);
<a name="L902" href="source/net/ipv4/ip_gre.c#L902">902</a> rtnl_link_failed:
<a name="L903" href="source/net/ipv4/ip_gre.c#L903">903</a>         <a href="ident?i=gre_cisco_unregister">gre_cisco_unregister</a>(&amp;<a href="ident?i=ipgre_protocol">ipgre_protocol</a>);
<a name="L904" href="source/net/ipv4/ip_gre.c#L904">904</a> add_proto_failed:
<a name="L905" href="source/net/ipv4/ip_gre.c#L905">905</a>         <a href="ident?i=unregister_pernet_device">unregister_pernet_device</a>(&amp;<a href="ident?i=ipgre_tap_net_ops">ipgre_tap_net_ops</a>);
<a name="L906" href="source/net/ipv4/ip_gre.c#L906">906</a> pnet_tap_faied:
<a name="L907" href="source/net/ipv4/ip_gre.c#L907">907</a>         <a href="ident?i=unregister_pernet_device">unregister_pernet_device</a>(&amp;<a href="ident?i=ipgre_net_ops">ipgre_net_ops</a>);
<a name="L908" href="source/net/ipv4/ip_gre.c#L908">908</a>         return <a href="ident?i=err">err</a>;
<a name="L909" href="source/net/ipv4/ip_gre.c#L909">909</a> }
<a name="L910" href="source/net/ipv4/ip_gre.c#L910">910</a> 
<a name="L911" href="source/net/ipv4/ip_gre.c#L911">911</a> static void <a href="ident?i=__exit">__exit</a> <a href="ident?i=ipgre_fini">ipgre_fini</a>(void)
<a name="L912" href="source/net/ipv4/ip_gre.c#L912">912</a> {
<a name="L913" href="source/net/ipv4/ip_gre.c#L913">913</a>         <a href="ident?i=rtnl_link_unregister">rtnl_link_unregister</a>(&amp;ipgre_tap_ops);
<a name="L914" href="source/net/ipv4/ip_gre.c#L914">914</a>         <a href="ident?i=rtnl_link_unregister">rtnl_link_unregister</a>(&amp;ipgre_link_ops);
<a name="L915" href="source/net/ipv4/ip_gre.c#L915">915</a>         <a href="ident?i=gre_cisco_unregister">gre_cisco_unregister</a>(&amp;<a href="ident?i=ipgre_protocol">ipgre_protocol</a>);
<a name="L916" href="source/net/ipv4/ip_gre.c#L916">916</a>         <a href="ident?i=unregister_pernet_device">unregister_pernet_device</a>(&amp;<a href="ident?i=ipgre_tap_net_ops">ipgre_tap_net_ops</a>);
<a name="L917" href="source/net/ipv4/ip_gre.c#L917">917</a>         <a href="ident?i=unregister_pernet_device">unregister_pernet_device</a>(&amp;<a href="ident?i=ipgre_net_ops">ipgre_net_ops</a>);
<a name="L918" href="source/net/ipv4/ip_gre.c#L918">918</a> }
<a name="L919" href="source/net/ipv4/ip_gre.c#L919">919</a> 
<a name="L920" href="source/net/ipv4/ip_gre.c#L920">920</a> <a href="ident?i=module_init">module_init</a>(<a href="ident?i=ipgre_init">ipgre_init</a>);
<a name="L921" href="source/net/ipv4/ip_gre.c#L921">921</a> <a href="ident?i=module_exit">module_exit</a>(<a href="ident?i=ipgre_fini">ipgre_fini</a>);
<a name="L922" href="source/net/ipv4/ip_gre.c#L922">922</a> <a href="ident?i=MODULE_LICENSE">MODULE_LICENSE</a>(<i>"GPL"</i>);
<a name="L923" href="source/net/ipv4/ip_gre.c#L923">923</a> <a href="ident?i=MODULE_ALIAS_RTNL_LINK">MODULE_ALIAS_RTNL_LINK</a>(<i>"gre"</i>);
<a name="L924" href="source/net/ipv4/ip_gre.c#L924">924</a> <a href="ident?i=MODULE_ALIAS_RTNL_LINK">MODULE_ALIAS_RTNL_LINK</a>(<i>"gretap"</i>);
<a name="L925" href="source/net/ipv4/ip_gre.c#L925">925</a> <a href="ident?i=MODULE_ALIAS_NETDEV">MODULE_ALIAS_NETDEV</a>(<i>"gre0"</i>);
<a name="L926" href="source/net/ipv4/ip_gre.c#L926">926</a> <a href="ident?i=MODULE_ALIAS_NETDEV">MODULE_ALIAS_NETDEV</a>(<i>"gretap0"</i>);
<a name="L927" href="source/net/ipv4/ip_gre.c#L927">927</a> </pre></div><p>
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
