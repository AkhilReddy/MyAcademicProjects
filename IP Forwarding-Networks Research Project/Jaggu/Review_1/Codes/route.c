<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title>Linux/net/ipv4/route.c - Linux Cross Reference - Free Electrons</title>
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
		 &nbsp;&bull;&nbsp;<b><i>source navigation</i></b> &nbsp;&bull;&nbsp;<a href="diff/net/ipv4/route.c">diff markup</a> &nbsp;&bull;&nbsp;<a href="ident">identifier search</a> &nbsp;&bull;&nbsp;<a href="search">freetext search</a> &nbsp;&bull;&nbsp;
		</p>
	</div>
</div>

<div id="topbar">
  
  <p>Version: &nbsp;<a href="source/net/ipv4/route.c?v=2.0.40">2.0.40</a>&nbsp;<a href="source/net/ipv4/route.c?v=2.2.26">2.2.26</a>&nbsp;<a href="source/net/ipv4/route.c?v=2.4.37">2.4.37</a>&nbsp;<a href="source/net/ipv4/route.c?v=3.5">3.5</a>&nbsp;<a href="source/net/ipv4/route.c?v=3.6">3.6</a>&nbsp;<a href="source/net/ipv4/route.c?v=3.7">3.7</a>&nbsp;<a href="source/net/ipv4/route.c?v=3.8">3.8</a>&nbsp;<a href="source/net/ipv4/route.c?v=3.9">3.9</a>&nbsp;<a href="source/net/ipv4/route.c?v=3.10">3.10</a>&nbsp;<a href="source/net/ipv4/route.c?v=3.11">3.11</a>&nbsp;<a href="source/net/ipv4/route.c?v=3.12">3.12</a>&nbsp;<a href="source/net/ipv4/route.c?v=3.13">3.13</a>&nbsp;<a href="source/net/ipv4/route.c?v=3.14">3.14</a>&nbsp;<a href="source/net/ipv4/route.c?v=3.15">3.15</a>&nbsp;<a href="source/net/ipv4/route.c?v=3.16">3.16</a>&nbsp;<a href="source/net/ipv4/route.c?v=3.17">3.17</a>&nbsp;<a href="source/net/ipv4/route.c?v=3.18">3.18</a>&nbsp;<a href="source/net/ipv4/route.c?v=3.19">3.19</a>&nbsp;<a href="source/net/ipv4/route.c?v=4.0">4.0</a>&nbsp;<b><i>4.1</i></b></p>
  
</div>

<h1><a href="source/">Linux</a>/<a href="source/net/">net</a>/<a href="source/net/ipv4/">ipv4</a>/<a href="source/net/ipv4/route.c">route.c</a></h1>
<div id="lxrcode"><pre>  <a name="L1" href="source/net/ipv4/route.c#L1">1</a> <b><i>/*</i></b>
  <a name="L2" href="source/net/ipv4/route.c#L2">2</a> <b><i> * INET         An implementation of the TCP/IP protocol suite for the LINUX</i></b>
  <a name="L3" href="source/net/ipv4/route.c#L3">3</a> <b><i> *              operating system.  INET is implemented using the  BSD Socket</i></b>
  <a name="L4" href="source/net/ipv4/route.c#L4">4</a> <b><i> *              interface as the means of communication with the user level.</i></b>
  <a name="L5" href="source/net/ipv4/route.c#L5">5</a> <b><i> *</i></b>
  <a name="L6" href="source/net/ipv4/route.c#L6">6</a> <b><i> *              ROUTE - implementation of the IP router.</i></b>
  <a name="L7" href="source/net/ipv4/route.c#L7">7</a> <b><i> *</i></b>
  <a name="L8" href="source/net/ipv4/route.c#L8">8</a> <b><i> * Authors:     Ross Biro</i></b>
  <a name="L9" href="source/net/ipv4/route.c#L9">9</a> <b><i> *              Fred N. van Kempen, &lt;waltje@uWalt.NL.Mugnet.ORG&gt;</i></b>
 <a name="L10" href="source/net/ipv4/route.c#L10">10</a> <b><i> *              Alan Cox, &lt;gw4pts@gw4pts.ampr.org&gt;</i></b>
 <a name="L11" href="source/net/ipv4/route.c#L11">11</a> <b><i> *              Linus Torvalds, &lt;Linus.Torvalds@helsinki.fi&gt;</i></b>
 <a name="L12" href="source/net/ipv4/route.c#L12">12</a> <b><i> *              Alexey Kuznetsov, &lt;kuznet@ms2.inr.ac.ru&gt;</i></b>
 <a name="L13" href="source/net/ipv4/route.c#L13">13</a> <b><i> *</i></b>
 <a name="L14" href="source/net/ipv4/route.c#L14">14</a> <b><i> * Fixes:</i></b>
 <a name="L15" href="source/net/ipv4/route.c#L15">15</a> <b><i> *              Alan Cox        :       Verify area fixes.</i></b>
 <a name="L16" href="source/net/ipv4/route.c#L16">16</a> <b><i> *              Alan Cox        :       cli() protects routing changes</i></b>
 <a name="L17" href="source/net/ipv4/route.c#L17">17</a> <b><i> *              Rui Oliveira    :       ICMP routing table updates</i></b>
 <a name="L18" href="source/net/ipv4/route.c#L18">18</a> <b><i> *              (rco@di.uminho.pt)      Routing table insertion and update</i></b>
 <a name="L19" href="source/net/ipv4/route.c#L19">19</a> <b><i> *              Linus Torvalds  :       Rewrote bits to be sensible</i></b>
 <a name="L20" href="source/net/ipv4/route.c#L20">20</a> <b><i> *              Alan Cox        :       Added BSD route gw semantics</i></b>
 <a name="L21" href="source/net/ipv4/route.c#L21">21</a> <b><i> *              Alan Cox        :       Super /proc &gt;4K</i></b>
 <a name="L22" href="source/net/ipv4/route.c#L22">22</a> <b><i> *              Alan Cox        :       MTU in route table</i></b>
 <a name="L23" href="source/net/ipv4/route.c#L23">23</a> <b><i> *              Alan Cox        :       MSS actually. Also added the window</i></b>
 <a name="L24" href="source/net/ipv4/route.c#L24">24</a> <b><i> *                                      clamper.</i></b>
 <a name="L25" href="source/net/ipv4/route.c#L25">25</a> <b><i> *              Sam Lantinga    :       Fixed route matching in rt_del()</i></b>
 <a name="L26" href="source/net/ipv4/route.c#L26">26</a> <b><i> *              Alan Cox        :       Routing cache support.</i></b>
 <a name="L27" href="source/net/ipv4/route.c#L27">27</a> <b><i> *              Alan Cox        :       Removed compatibility cruft.</i></b>
 <a name="L28" href="source/net/ipv4/route.c#L28">28</a> <b><i> *              Alan Cox        :       RTF_REJECT support.</i></b>
 <a name="L29" href="source/net/ipv4/route.c#L29">29</a> <b><i> *              Alan Cox        :       TCP irtt support.</i></b>
 <a name="L30" href="source/net/ipv4/route.c#L30">30</a> <b><i> *              Jonathan Naylor :       Added Metric support.</i></b>
 <a name="L31" href="source/net/ipv4/route.c#L31">31</a> <b><i> *      Miquel van Smoorenburg  :       BSD API fixes.</i></b>
 <a name="L32" href="source/net/ipv4/route.c#L32">32</a> <b><i> *      Miquel van Smoorenburg  :       Metrics.</i></b>
 <a name="L33" href="source/net/ipv4/route.c#L33">33</a> <b><i> *              Alan Cox        :       Use __u32 properly</i></b>
 <a name="L34" href="source/net/ipv4/route.c#L34">34</a> <b><i> *              Alan Cox        :       Aligned routing errors more closely with BSD</i></b>
 <a name="L35" href="source/net/ipv4/route.c#L35">35</a> <b><i> *                                      our system is still very different.</i></b>
 <a name="L36" href="source/net/ipv4/route.c#L36">36</a> <b><i> *              Alan Cox        :       Faster /proc handling</i></b>
 <a name="L37" href="source/net/ipv4/route.c#L37">37</a> <b><i> *      Alexey Kuznetsov        :       Massive rework to support tree based routing,</i></b>
 <a name="L38" href="source/net/ipv4/route.c#L38">38</a> <b><i> *                                      routing caches and better behaviour.</i></b>
 <a name="L39" href="source/net/ipv4/route.c#L39">39</a> <b><i> *</i></b>
 <a name="L40" href="source/net/ipv4/route.c#L40">40</a> <b><i> *              Olaf Erb        :       irtt wasn't being copied right.</i></b>
 <a name="L41" href="source/net/ipv4/route.c#L41">41</a> <b><i> *              Bjorn Ekwall    :       Kerneld route support.</i></b>
 <a name="L42" href="source/net/ipv4/route.c#L42">42</a> <b><i> *              Alan Cox        :       Multicast fixed (I hope)</i></b>
 <a name="L43" href="source/net/ipv4/route.c#L43">43</a> <b><i> *              Pavel Krauz     :       Limited broadcast fixed</i></b>
 <a name="L44" href="source/net/ipv4/route.c#L44">44</a> <b><i> *              Mike McLagan    :       Routing by source</i></b>
 <a name="L45" href="source/net/ipv4/route.c#L45">45</a> <b><i> *      Alexey Kuznetsov        :       End of old history. Split to fib.c and</i></b>
 <a name="L46" href="source/net/ipv4/route.c#L46">46</a> <b><i> *                                      route.c and rewritten from scratch.</i></b>
 <a name="L47" href="source/net/ipv4/route.c#L47">47</a> <b><i> *              Andi Kleen      :       Load-limit warning messages.</i></b>
 <a name="L48" href="source/net/ipv4/route.c#L48">48</a> <b><i> *      Vitaly E. Lavrov        :       Transparent proxy revived after year coma.</i></b>
 <a name="L49" href="source/net/ipv4/route.c#L49">49</a> <b><i> *      Vitaly E. Lavrov        :       Race condition in ip_route_input_slow.</i></b>
 <a name="L50" href="source/net/ipv4/route.c#L50">50</a> <b><i> *      Tobias Ringstrom        :       Uninitialized res.type in ip_route_output_slow.</i></b>
 <a name="L51" href="source/net/ipv4/route.c#L51">51</a> <b><i> *      Vladimir V. Ivanov      :       IP rule info (flowid) is really useful.</i></b>
 <a name="L52" href="source/net/ipv4/route.c#L52">52</a> <b><i> *              Marc Boucher    :       routing by fwmark</i></b>
 <a name="L53" href="source/net/ipv4/route.c#L53">53</a> <b><i> *      Robert Olsson           :       Added rt_cache statistics</i></b>
 <a name="L54" href="source/net/ipv4/route.c#L54">54</a> <b><i> *      Arnaldo C. Melo         :       Convert proc stuff to seq_file</i></b>
 <a name="L55" href="source/net/ipv4/route.c#L55">55</a> <b><i> *      Eric Dumazet            :       hashed spinlocks and rt_check_expire() fixes.</i></b>
 <a name="L56" href="source/net/ipv4/route.c#L56">56</a> <b><i> *      Ilia Sotnikov           :       Ignore TOS on PMTUD and Redirect</i></b>
 <a name="L57" href="source/net/ipv4/route.c#L57">57</a> <b><i> *      Ilia Sotnikov           :       Removed TOS from hash calculations</i></b>
 <a name="L58" href="source/net/ipv4/route.c#L58">58</a> <b><i> *</i></b>
 <a name="L59" href="source/net/ipv4/route.c#L59">59</a> <b><i> *              This program is free software; you can redistribute it and/or</i></b>
 <a name="L60" href="source/net/ipv4/route.c#L60">60</a> <b><i> *              modify it under the terms of the GNU General Public License</i></b>
 <a name="L61" href="source/net/ipv4/route.c#L61">61</a> <b><i> *              as published by the Free Software Foundation; either version</i></b>
 <a name="L62" href="source/net/ipv4/route.c#L62">62</a> <b><i> *              2 of the License, or (at your option) any later version.</i></b>
 <a name="L63" href="source/net/ipv4/route.c#L63">63</a> <b><i> */</i></b>
 <a name="L64" href="source/net/ipv4/route.c#L64">64</a> 
 <a name="L65" href="source/net/ipv4/route.c#L65">65</a> #define <a href="ident?i=pr_fmt">pr_fmt</a>(<a href="ident?i=fmt">fmt</a>) <i>"IPv4: "</i> <a href="ident?i=fmt">fmt</a>
 <a name="L66" href="source/net/ipv4/route.c#L66">66</a> 
 <a name="L67" href="source/net/ipv4/route.c#L67">67</a> #include &lt;linux/module.h&gt;
 <a name="L68" href="source/net/ipv4/route.c#L68">68</a> #include &lt;asm/uaccess.h&gt;
 <a name="L69" href="source/net/ipv4/route.c#L69">69</a> #include &lt;linux/bitops.h&gt;
 <a name="L70" href="source/net/ipv4/route.c#L70">70</a> #include &lt;linux/types.h&gt;
 <a name="L71" href="source/net/ipv4/route.c#L71">71</a> #include &lt;linux/kernel.h&gt;
 <a name="L72" href="source/net/ipv4/route.c#L72">72</a> #include &lt;linux/mm.h&gt;
 <a name="L73" href="source/net/ipv4/route.c#L73">73</a> #include &lt;linux/string.h&gt;
 <a name="L74" href="source/net/ipv4/route.c#L74">74</a> #include &lt;linux/socket.h&gt;
 <a name="L75" href="source/net/ipv4/route.c#L75">75</a> #include &lt;linux/sockios.h&gt;
 <a name="L76" href="source/net/ipv4/route.c#L76">76</a> #include &lt;linux/errno.h&gt;
 <a name="L77" href="source/net/ipv4/route.c#L77">77</a> #include &lt;linux/in.h&gt;
 <a name="L78" href="source/net/ipv4/route.c#L78">78</a> #include &lt;linux/inet.h&gt;
 <a name="L79" href="source/net/ipv4/route.c#L79">79</a> #include &lt;linux/netdevice.h&gt;
 <a name="L80" href="source/net/ipv4/route.c#L80">80</a> #include &lt;linux/proc_fs.h&gt;
 <a name="L81" href="source/net/ipv4/route.c#L81">81</a> #include &lt;linux/init.h&gt;
 <a name="L82" href="source/net/ipv4/route.c#L82">82</a> #include &lt;linux/skbuff.h&gt;
 <a name="L83" href="source/net/ipv4/route.c#L83">83</a> #include &lt;linux/inetdevice.h&gt;
 <a name="L84" href="source/net/ipv4/route.c#L84">84</a> #include &lt;linux/igmp.h&gt;
 <a name="L85" href="source/net/ipv4/route.c#L85">85</a> #include &lt;linux/pkt_sched.h&gt;
 <a name="L86" href="source/net/ipv4/route.c#L86">86</a> #include &lt;linux/mroute.h&gt;
 <a name="L87" href="source/net/ipv4/route.c#L87">87</a> #include &lt;linux/netfilter_ipv4.h&gt;
 <a name="L88" href="source/net/ipv4/route.c#L88">88</a> #include &lt;linux/random.h&gt;
 <a name="L89" href="source/net/ipv4/route.c#L89">89</a> #include &lt;linux/rcupdate.h&gt;
 <a name="L90" href="source/net/ipv4/route.c#L90">90</a> #include &lt;linux/times.h&gt;
 <a name="L91" href="source/net/ipv4/route.c#L91">91</a> #include &lt;linux/slab.h&gt;
 <a name="L92" href="source/net/ipv4/route.c#L92">92</a> #include &lt;linux/jhash.h&gt;
 <a name="L93" href="source/net/ipv4/route.c#L93">93</a> #include &lt;net/dst.h&gt;
 <a name="L94" href="source/net/ipv4/route.c#L94">94</a> #include &lt;net/net_namespace.h&gt;
 <a name="L95" href="source/net/ipv4/route.c#L95">95</a> #include &lt;net/protocol.h&gt;
 <a name="L96" href="source/net/ipv4/route.c#L96">96</a> #include &lt;net/ip.h&gt;
 <a name="L97" href="source/net/ipv4/route.c#L97">97</a> #include &lt;net/route.h&gt;
 <a name="L98" href="source/net/ipv4/route.c#L98">98</a> #include &lt;net/inetpeer.h&gt;
 <a name="L99" href="source/net/ipv4/route.c#L99">99</a> #include &lt;net/sock.h&gt;
<a name="L100" href="source/net/ipv4/route.c#L100">100</a> #include &lt;net/ip_fib.h&gt;
<a name="L101" href="source/net/ipv4/route.c#L101">101</a> #include &lt;net/arp.h&gt;
<a name="L102" href="source/net/ipv4/route.c#L102">102</a> #include &lt;net/tcp.h&gt;
<a name="L103" href="source/net/ipv4/route.c#L103">103</a> #include &lt;net/icmp.h&gt;
<a name="L104" href="source/net/ipv4/route.c#L104">104</a> #include &lt;net/xfrm.h&gt;
<a name="L105" href="source/net/ipv4/route.c#L105">105</a> #include &lt;net/netevent.h&gt;
<a name="L106" href="source/net/ipv4/route.c#L106">106</a> #include &lt;net/rtnetlink.h&gt;
<a name="L107" href="source/net/ipv4/route.c#L107">107</a> #ifdef CONFIG_SYSCTL
<a name="L108" href="source/net/ipv4/route.c#L108">108</a> #include &lt;linux/sysctl.h&gt;
<a name="L109" href="source/net/ipv4/route.c#L109">109</a> #include &lt;linux/kmemleak.h&gt;
<a name="L110" href="source/net/ipv4/route.c#L110">110</a> #endif
<a name="L111" href="source/net/ipv4/route.c#L111">111</a> #include &lt;net/secure_seq.h&gt;
<a name="L112" href="source/net/ipv4/route.c#L112">112</a> 
<a name="L113" href="source/net/ipv4/route.c#L113">113</a> #define <a href="ident?i=RT_FL_TOS">RT_FL_TOS</a>(oldflp4) \
<a name="L114" href="source/net/ipv4/route.c#L114">114</a>         ((oldflp4)-&gt;<a href="ident?i=flowi4_tos">flowi4_tos</a> &amp; (<a href="ident?i=IPTOS_RT_MASK">IPTOS_RT_MASK</a> | <a href="ident?i=RTO_ONLINK">RTO_ONLINK</a>))
<a name="L115" href="source/net/ipv4/route.c#L115">115</a> 
<a name="L116" href="source/net/ipv4/route.c#L116">116</a> #define <a href="ident?i=RT_GC_TIMEOUT">RT_GC_TIMEOUT</a> (300*<a href="ident?i=HZ">HZ</a>)
<a name="L117" href="source/net/ipv4/route.c#L117">117</a> 
<a name="L118" href="source/net/ipv4/route.c#L118">118</a> static int <a href="ident?i=ip_rt_max_size">ip_rt_max_size</a>;
<a name="L119" href="source/net/ipv4/route.c#L119">119</a> static int ip_rt_redirect_number <a href="ident?i=__read_mostly">__read_mostly</a>  = 9;
<a name="L120" href="source/net/ipv4/route.c#L120">120</a> static int ip_rt_redirect_load <a href="ident?i=__read_mostly">__read_mostly</a>    = <a href="ident?i=HZ">HZ</a> / 50;
<a name="L121" href="source/net/ipv4/route.c#L121">121</a> static int ip_rt_redirect_silence <a href="ident?i=__read_mostly">__read_mostly</a> = ((<a href="ident?i=HZ">HZ</a> / 50) &lt;&lt; (9 + 1));
<a name="L122" href="source/net/ipv4/route.c#L122">122</a> static int ip_rt_error_cost <a href="ident?i=__read_mostly">__read_mostly</a>       = <a href="ident?i=HZ">HZ</a>;
<a name="L123" href="source/net/ipv4/route.c#L123">123</a> static int ip_rt_error_burst <a href="ident?i=__read_mostly">__read_mostly</a>      = 5 * <a href="ident?i=HZ">HZ</a>;
<a name="L124" href="source/net/ipv4/route.c#L124">124</a> static int ip_rt_mtu_expires <a href="ident?i=__read_mostly">__read_mostly</a>      = 10 * 60 * <a href="ident?i=HZ">HZ</a>;
<a name="L125" href="source/net/ipv4/route.c#L125">125</a> static int ip_rt_min_pmtu <a href="ident?i=__read_mostly">__read_mostly</a>         = 512 + 20 + 20;
<a name="L126" href="source/net/ipv4/route.c#L126">126</a> static int ip_rt_min_advmss <a href="ident?i=__read_mostly">__read_mostly</a>       = 256;
<a name="L127" href="source/net/ipv4/route.c#L127">127</a> 
<a name="L128" href="source/net/ipv4/route.c#L128">128</a> <b><i>/*</i></b>
<a name="L129" href="source/net/ipv4/route.c#L129">129</a> <b><i> *      Interface to generic destination cache.</i></b>
<a name="L130" href="source/net/ipv4/route.c#L130">130</a> <b><i> */</i></b>
<a name="L131" href="source/net/ipv4/route.c#L131">131</a> 
<a name="L132" href="source/net/ipv4/route.c#L132">132</a> static struct <a href="ident?i=dst_entry">dst_entry</a> *<a href="ident?i=ipv4_dst_check">ipv4_dst_check</a>(struct <a href="ident?i=dst_entry">dst_entry</a> *<a href="ident?i=dst">dst</a>, <a href="ident?i=u32">u32</a> cookie);
<a name="L133" href="source/net/ipv4/route.c#L133">133</a> static unsigned int      <a href="ident?i=ipv4_default_advmss">ipv4_default_advmss</a>(const struct <a href="ident?i=dst_entry">dst_entry</a> *<a href="ident?i=dst">dst</a>);
<a name="L134" href="source/net/ipv4/route.c#L134">134</a> static unsigned int      <a href="ident?i=ipv4_mtu">ipv4_mtu</a>(const struct <a href="ident?i=dst_entry">dst_entry</a> *<a href="ident?i=dst">dst</a>);
<a name="L135" href="source/net/ipv4/route.c#L135">135</a> static struct <a href="ident?i=dst_entry">dst_entry</a> *<a href="ident?i=ipv4_negative_advice">ipv4_negative_advice</a>(struct <a href="ident?i=dst_entry">dst_entry</a> *<a href="ident?i=dst">dst</a>);
<a name="L136" href="source/net/ipv4/route.c#L136">136</a> static void              <a href="ident?i=ipv4_link_failure">ipv4_link_failure</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>);
<a name="L137" href="source/net/ipv4/route.c#L137">137</a> static void              <a href="ident?i=ip_rt_update_pmtu">ip_rt_update_pmtu</a>(struct <a href="ident?i=dst_entry">dst_entry</a> *<a href="ident?i=dst">dst</a>, struct <a href="ident?i=sock">sock</a> *sk,
<a name="L138" href="source/net/ipv4/route.c#L138">138</a>                                            struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, <a href="ident?i=u32">u32</a> <a href="ident?i=mtu">mtu</a>);
<a name="L139" href="source/net/ipv4/route.c#L139">139</a> static void              <a href="ident?i=ip_do_redirect">ip_do_redirect</a>(struct <a href="ident?i=dst_entry">dst_entry</a> *<a href="ident?i=dst">dst</a>, struct <a href="ident?i=sock">sock</a> *sk,
<a name="L140" href="source/net/ipv4/route.c#L140">140</a>                                         struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>);
<a name="L141" href="source/net/ipv4/route.c#L141">141</a> static void             <a href="ident?i=ipv4_dst_destroy">ipv4_dst_destroy</a>(struct <a href="ident?i=dst_entry">dst_entry</a> *<a href="ident?i=dst">dst</a>);
<a name="L142" href="source/net/ipv4/route.c#L142">142</a> 
<a name="L143" href="source/net/ipv4/route.c#L143">143</a> static <a href="ident?i=u32">u32</a> *<a href="ident?i=ipv4_cow_metrics">ipv4_cow_metrics</a>(struct <a href="ident?i=dst_entry">dst_entry</a> *<a href="ident?i=dst">dst</a>, unsigned long <a href="ident?i=old">old</a>)
<a name="L144" href="source/net/ipv4/route.c#L144">144</a> {
<a name="L145" href="source/net/ipv4/route.c#L145">145</a>         <a href="ident?i=WARN_ON">WARN_ON</a>(1);
<a name="L146" href="source/net/ipv4/route.c#L146">146</a>         return <a href="ident?i=NULL">NULL</a>;
<a name="L147" href="source/net/ipv4/route.c#L147">147</a> }
<a name="L148" href="source/net/ipv4/route.c#L148">148</a> 
<a name="L149" href="source/net/ipv4/route.c#L149">149</a> static struct <a href="ident?i=neighbour">neighbour</a> *<a href="ident?i=ipv4_neigh_lookup">ipv4_neigh_lookup</a>(const struct <a href="ident?i=dst_entry">dst_entry</a> *<a href="ident?i=dst">dst</a>,
<a name="L150" href="source/net/ipv4/route.c#L150">150</a>                                            struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
<a name="L151" href="source/net/ipv4/route.c#L151">151</a>                                            const void *<a href="ident?i=daddr">daddr</a>);
<a name="L152" href="source/net/ipv4/route.c#L152">152</a> 
<a name="L153" href="source/net/ipv4/route.c#L153">153</a> static struct <a href="ident?i=dst_ops">dst_ops</a> <a href="ident?i=ipv4_dst_ops">ipv4_dst_ops</a> = {
<a name="L154" href="source/net/ipv4/route.c#L154">154</a>         .<a href="ident?i=family">family</a> =               <a href="ident?i=AF_INET">AF_INET</a>,
<a name="L155" href="source/net/ipv4/route.c#L155">155</a>         .<a href="ident?i=check">check</a> =                <a href="ident?i=ipv4_dst_check">ipv4_dst_check</a>,
<a name="L156" href="source/net/ipv4/route.c#L156">156</a>         .default_advmss =       <a href="ident?i=ipv4_default_advmss">ipv4_default_advmss</a>,
<a name="L157" href="source/net/ipv4/route.c#L157">157</a>         .<a href="ident?i=mtu">mtu</a> =                  <a href="ident?i=ipv4_mtu">ipv4_mtu</a>,
<a name="L158" href="source/net/ipv4/route.c#L158">158</a>         .cow_metrics =          <a href="ident?i=ipv4_cow_metrics">ipv4_cow_metrics</a>,
<a name="L159" href="source/net/ipv4/route.c#L159">159</a>         .<a href="ident?i=destroy">destroy</a> =              <a href="ident?i=ipv4_dst_destroy">ipv4_dst_destroy</a>,
<a name="L160" href="source/net/ipv4/route.c#L160">160</a>         .negative_advice =      <a href="ident?i=ipv4_negative_advice">ipv4_negative_advice</a>,
<a name="L161" href="source/net/ipv4/route.c#L161">161</a>         .link_failure =         <a href="ident?i=ipv4_link_failure">ipv4_link_failure</a>,
<a name="L162" href="source/net/ipv4/route.c#L162">162</a>         .update_pmtu =          <a href="ident?i=ip_rt_update_pmtu">ip_rt_update_pmtu</a>,
<a name="L163" href="source/net/ipv4/route.c#L163">163</a>         .<a href="ident?i=redirect">redirect</a> =             <a href="ident?i=ip_do_redirect">ip_do_redirect</a>,
<a name="L164" href="source/net/ipv4/route.c#L164">164</a>         .local_out =            <a href="ident?i=__ip_local_out">__ip_local_out</a>,
<a name="L165" href="source/net/ipv4/route.c#L165">165</a>         .<a href="ident?i=neigh_lookup">neigh_lookup</a> =         <a href="ident?i=ipv4_neigh_lookup">ipv4_neigh_lookup</a>,
<a name="L166" href="source/net/ipv4/route.c#L166">166</a> };
<a name="L167" href="source/net/ipv4/route.c#L167">167</a> 
<a name="L168" href="source/net/ipv4/route.c#L168">168</a> #define <a href="ident?i=ECN_OR_COST">ECN_OR_COST</a>(class)      TC_PRIO_##class
<a name="L169" href="source/net/ipv4/route.c#L169">169</a> 
<a name="L170" href="source/net/ipv4/route.c#L170">170</a> const <a href="ident?i=__u8">__u8</a> <a href="ident?i=ip_tos2prio">ip_tos2prio</a>[16] = {
<a name="L171" href="source/net/ipv4/route.c#L171">171</a>         <a href="ident?i=TC_PRIO_BESTEFFORT">TC_PRIO_BESTEFFORT</a>,
<a name="L172" href="source/net/ipv4/route.c#L172">172</a>         <a href="ident?i=ECN_OR_COST">ECN_OR_COST</a>(BESTEFFORT),
<a name="L173" href="source/net/ipv4/route.c#L173">173</a>         <a href="ident?i=TC_PRIO_BESTEFFORT">TC_PRIO_BESTEFFORT</a>,
<a name="L174" href="source/net/ipv4/route.c#L174">174</a>         <a href="ident?i=ECN_OR_COST">ECN_OR_COST</a>(BESTEFFORT),
<a name="L175" href="source/net/ipv4/route.c#L175">175</a>         <a href="ident?i=TC_PRIO_BULK">TC_PRIO_BULK</a>,
<a name="L176" href="source/net/ipv4/route.c#L176">176</a>         <a href="ident?i=ECN_OR_COST">ECN_OR_COST</a>(BULK),
<a name="L177" href="source/net/ipv4/route.c#L177">177</a>         <a href="ident?i=TC_PRIO_BULK">TC_PRIO_BULK</a>,
<a name="L178" href="source/net/ipv4/route.c#L178">178</a>         <a href="ident?i=ECN_OR_COST">ECN_OR_COST</a>(BULK),
<a name="L179" href="source/net/ipv4/route.c#L179">179</a>         <a href="ident?i=TC_PRIO_INTERACTIVE">TC_PRIO_INTERACTIVE</a>,
<a name="L180" href="source/net/ipv4/route.c#L180">180</a>         <a href="ident?i=ECN_OR_COST">ECN_OR_COST</a>(INTERACTIVE),
<a name="L181" href="source/net/ipv4/route.c#L181">181</a>         <a href="ident?i=TC_PRIO_INTERACTIVE">TC_PRIO_INTERACTIVE</a>,
<a name="L182" href="source/net/ipv4/route.c#L182">182</a>         <a href="ident?i=ECN_OR_COST">ECN_OR_COST</a>(INTERACTIVE),
<a name="L183" href="source/net/ipv4/route.c#L183">183</a>         <a href="ident?i=TC_PRIO_INTERACTIVE_BULK">TC_PRIO_INTERACTIVE_BULK</a>,
<a name="L184" href="source/net/ipv4/route.c#L184">184</a>         <a href="ident?i=ECN_OR_COST">ECN_OR_COST</a>(INTERACTIVE_BULK),
<a name="L185" href="source/net/ipv4/route.c#L185">185</a>         <a href="ident?i=TC_PRIO_INTERACTIVE_BULK">TC_PRIO_INTERACTIVE_BULK</a>,
<a name="L186" href="source/net/ipv4/route.c#L186">186</a>         <a href="ident?i=ECN_OR_COST">ECN_OR_COST</a>(INTERACTIVE_BULK)
<a name="L187" href="source/net/ipv4/route.c#L187">187</a> };
<a name="L188" href="source/net/ipv4/route.c#L188">188</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=ip_tos2prio">ip_tos2prio</a>);
<a name="L189" href="source/net/ipv4/route.c#L189">189</a> 
<a name="L190" href="source/net/ipv4/route.c#L190">190</a> static <a href="ident?i=DEFINE_PER_CPU">DEFINE_PER_CPU</a>(struct <a href="ident?i=rt_cache_stat">rt_cache_stat</a>, <a href="ident?i=rt_cache_stat">rt_cache_stat</a>);
<a name="L191" href="source/net/ipv4/route.c#L191">191</a> #define <a href="ident?i=RT_CACHE_STAT_INC">RT_CACHE_STAT_INC</a>(<a href="ident?i=field">field</a>) <a href="ident?i=raw_cpu_inc">raw_cpu_inc</a>(<a href="ident?i=rt_cache_stat">rt_cache_stat</a>.<a href="ident?i=field">field</a>)
<a name="L192" href="source/net/ipv4/route.c#L192">192</a> 
<a name="L193" href="source/net/ipv4/route.c#L193">193</a> #ifdef CONFIG_PROC_FS
<a name="L194" href="source/net/ipv4/route.c#L194">194</a> static void *<a href="ident?i=rt_cache_seq_start">rt_cache_seq_start</a>(struct <a href="ident?i=seq_file">seq_file</a> *<a href="ident?i=seq">seq</a>, <a href="ident?i=loff_t">loff_t</a> *<a href="ident?i=pos">pos</a>)
<a name="L195" href="source/net/ipv4/route.c#L195">195</a> {
<a name="L196" href="source/net/ipv4/route.c#L196">196</a>         if (*<a href="ident?i=pos">pos</a>)
<a name="L197" href="source/net/ipv4/route.c#L197">197</a>                 return <a href="ident?i=NULL">NULL</a>;
<a name="L198" href="source/net/ipv4/route.c#L198">198</a>         return <a href="ident?i=SEQ_START_TOKEN">SEQ_START_TOKEN</a>;
<a name="L199" href="source/net/ipv4/route.c#L199">199</a> }
<a name="L200" href="source/net/ipv4/route.c#L200">200</a> 
<a name="L201" href="source/net/ipv4/route.c#L201">201</a> static void *<a href="ident?i=rt_cache_seq_next">rt_cache_seq_next</a>(struct <a href="ident?i=seq_file">seq_file</a> *<a href="ident?i=seq">seq</a>, void *<a href="ident?i=v">v</a>, <a href="ident?i=loff_t">loff_t</a> *<a href="ident?i=pos">pos</a>)
<a name="L202" href="source/net/ipv4/route.c#L202">202</a> {
<a name="L203" href="source/net/ipv4/route.c#L203">203</a>         ++*<a href="ident?i=pos">pos</a>;
<a name="L204" href="source/net/ipv4/route.c#L204">204</a>         return <a href="ident?i=NULL">NULL</a>;
<a name="L205" href="source/net/ipv4/route.c#L205">205</a> }
<a name="L206" href="source/net/ipv4/route.c#L206">206</a> 
<a name="L207" href="source/net/ipv4/route.c#L207">207</a> static void <a href="ident?i=rt_cache_seq_stop">rt_cache_seq_stop</a>(struct <a href="ident?i=seq_file">seq_file</a> *<a href="ident?i=seq">seq</a>, void *<a href="ident?i=v">v</a>)
<a name="L208" href="source/net/ipv4/route.c#L208">208</a> {
<a name="L209" href="source/net/ipv4/route.c#L209">209</a> }
<a name="L210" href="source/net/ipv4/route.c#L210">210</a> 
<a name="L211" href="source/net/ipv4/route.c#L211">211</a> static int <a href="ident?i=rt_cache_seq_show">rt_cache_seq_show</a>(struct <a href="ident?i=seq_file">seq_file</a> *<a href="ident?i=seq">seq</a>, void *<a href="ident?i=v">v</a>)
<a name="L212" href="source/net/ipv4/route.c#L212">212</a> {
<a name="L213" href="source/net/ipv4/route.c#L213">213</a>         if (<a href="ident?i=v">v</a> == <a href="ident?i=SEQ_START_TOKEN">SEQ_START_TOKEN</a>)
<a name="L214" href="source/net/ipv4/route.c#L214">214</a>                 <a href="ident?i=seq_printf">seq_printf</a>(<a href="ident?i=seq">seq</a>, <i>"%-127s\n"</i>,
<a name="L215" href="source/net/ipv4/route.c#L215">215</a>                            <i>"Iface\tDestination\tGateway \tFlags\t\tRefCnt\tUse\t"</i>
<a name="L216" href="source/net/ipv4/route.c#L216">216</a>                            <i>"Metric\tSource\t\tMTU\tWindow\tIRTT\tTOS\tHHRef\t"</i>
<a name="L217" href="source/net/ipv4/route.c#L217">217</a>                            <i>"HHUptod\tSpecDst"</i>);
<a name="L218" href="source/net/ipv4/route.c#L218">218</a>         return 0;
<a name="L219" href="source/net/ipv4/route.c#L219">219</a> }
<a name="L220" href="source/net/ipv4/route.c#L220">220</a> 
<a name="L221" href="source/net/ipv4/route.c#L221">221</a> static const struct <a href="ident?i=seq_operations">seq_operations</a> <a href="ident?i=rt_cache_seq_ops">rt_cache_seq_ops</a> = {
<a name="L222" href="source/net/ipv4/route.c#L222">222</a>         .<a href="ident?i=start">start</a>  = <a href="ident?i=rt_cache_seq_start">rt_cache_seq_start</a>,
<a name="L223" href="source/net/ipv4/route.c#L223">223</a>         .<a href="ident?i=next">next</a>   = <a href="ident?i=rt_cache_seq_next">rt_cache_seq_next</a>,
<a name="L224" href="source/net/ipv4/route.c#L224">224</a>         .<a href="ident?i=stop">stop</a>   = <a href="ident?i=rt_cache_seq_stop">rt_cache_seq_stop</a>,
<a name="L225" href="source/net/ipv4/route.c#L225">225</a>         .<a href="ident?i=show">show</a>   = <a href="ident?i=rt_cache_seq_show">rt_cache_seq_show</a>,
<a name="L226" href="source/net/ipv4/route.c#L226">226</a> };
<a name="L227" href="source/net/ipv4/route.c#L227">227</a> 
<a name="L228" href="source/net/ipv4/route.c#L228">228</a> static int <a href="ident?i=rt_cache_seq_open">rt_cache_seq_open</a>(struct <a href="ident?i=inode">inode</a> *<a href="ident?i=inode">inode</a>, struct <a href="ident?i=file">file</a> *<a href="ident?i=file">file</a>)
<a name="L229" href="source/net/ipv4/route.c#L229">229</a> {
<a name="L230" href="source/net/ipv4/route.c#L230">230</a>         return <a href="ident?i=seq_open">seq_open</a>(<a href="ident?i=file">file</a>, &amp;<a href="ident?i=rt_cache_seq_ops">rt_cache_seq_ops</a>);
<a name="L231" href="source/net/ipv4/route.c#L231">231</a> }
<a name="L232" href="source/net/ipv4/route.c#L232">232</a> 
<a name="L233" href="source/net/ipv4/route.c#L233">233</a> static const struct <a href="ident?i=file_operations">file_operations</a> <a href="ident?i=rt_cache_seq_fops">rt_cache_seq_fops</a> = {
<a name="L234" href="source/net/ipv4/route.c#L234">234</a>         .owner   = <a href="ident?i=THIS_MODULE">THIS_MODULE</a>,
<a name="L235" href="source/net/ipv4/route.c#L235">235</a>         .<a href="ident?i=open">open</a>    = <a href="ident?i=rt_cache_seq_open">rt_cache_seq_open</a>,
<a name="L236" href="source/net/ipv4/route.c#L236">236</a>         .<a href="ident?i=read">read</a>    = <a href="ident?i=seq_read">seq_read</a>,
<a name="L237" href="source/net/ipv4/route.c#L237">237</a>         .llseek  = <a href="ident?i=seq_lseek">seq_lseek</a>,
<a name="L238" href="source/net/ipv4/route.c#L238">238</a>         .<a href="ident?i=release">release</a> = <a href="ident?i=seq_release">seq_release</a>,
<a name="L239" href="source/net/ipv4/route.c#L239">239</a> };
<a name="L240" href="source/net/ipv4/route.c#L240">240</a> 
<a name="L241" href="source/net/ipv4/route.c#L241">241</a> 
<a name="L242" href="source/net/ipv4/route.c#L242">242</a> static void *<a href="ident?i=rt_cpu_seq_start">rt_cpu_seq_start</a>(struct <a href="ident?i=seq_file">seq_file</a> *<a href="ident?i=seq">seq</a>, <a href="ident?i=loff_t">loff_t</a> *<a href="ident?i=pos">pos</a>)
<a name="L243" href="source/net/ipv4/route.c#L243">243</a> {
<a name="L244" href="source/net/ipv4/route.c#L244">244</a>         int <a href="ident?i=cpu">cpu</a>;
<a name="L245" href="source/net/ipv4/route.c#L245">245</a> 
<a name="L246" href="source/net/ipv4/route.c#L246">246</a>         if (*<a href="ident?i=pos">pos</a> == 0)
<a name="L247" href="source/net/ipv4/route.c#L247">247</a>                 return <a href="ident?i=SEQ_START_TOKEN">SEQ_START_TOKEN</a>;
<a name="L248" href="source/net/ipv4/route.c#L248">248</a> 
<a name="L249" href="source/net/ipv4/route.c#L249">249</a>         for (<a href="ident?i=cpu">cpu</a> = *<a href="ident?i=pos">pos</a>-1; <a href="ident?i=cpu">cpu</a> &lt; <a href="ident?i=nr_cpu_ids">nr_cpu_ids</a>; ++<a href="ident?i=cpu">cpu</a>) {
<a name="L250" href="source/net/ipv4/route.c#L250">250</a>                 if (!<a href="ident?i=cpu_possible">cpu_possible</a>(<a href="ident?i=cpu">cpu</a>))
<a name="L251" href="source/net/ipv4/route.c#L251">251</a>                         continue;
<a name="L252" href="source/net/ipv4/route.c#L252">252</a>                 *<a href="ident?i=pos">pos</a> = <a href="ident?i=cpu">cpu</a>+1;
<a name="L253" href="source/net/ipv4/route.c#L253">253</a>                 return &amp;<a href="ident?i=per_cpu">per_cpu</a>(<a href="ident?i=rt_cache_stat">rt_cache_stat</a>, <a href="ident?i=cpu">cpu</a>);
<a name="L254" href="source/net/ipv4/route.c#L254">254</a>         }
<a name="L255" href="source/net/ipv4/route.c#L255">255</a>         return <a href="ident?i=NULL">NULL</a>;
<a name="L256" href="source/net/ipv4/route.c#L256">256</a> }
<a name="L257" href="source/net/ipv4/route.c#L257">257</a> 
<a name="L258" href="source/net/ipv4/route.c#L258">258</a> static void *<a href="ident?i=rt_cpu_seq_next">rt_cpu_seq_next</a>(struct <a href="ident?i=seq_file">seq_file</a> *<a href="ident?i=seq">seq</a>, void *<a href="ident?i=v">v</a>, <a href="ident?i=loff_t">loff_t</a> *<a href="ident?i=pos">pos</a>)
<a name="L259" href="source/net/ipv4/route.c#L259">259</a> {
<a name="L260" href="source/net/ipv4/route.c#L260">260</a>         int <a href="ident?i=cpu">cpu</a>;
<a name="L261" href="source/net/ipv4/route.c#L261">261</a> 
<a name="L262" href="source/net/ipv4/route.c#L262">262</a>         for (<a href="ident?i=cpu">cpu</a> = *<a href="ident?i=pos">pos</a>; <a href="ident?i=cpu">cpu</a> &lt; <a href="ident?i=nr_cpu_ids">nr_cpu_ids</a>; ++<a href="ident?i=cpu">cpu</a>) {
<a name="L263" href="source/net/ipv4/route.c#L263">263</a>                 if (!<a href="ident?i=cpu_possible">cpu_possible</a>(<a href="ident?i=cpu">cpu</a>))
<a name="L264" href="source/net/ipv4/route.c#L264">264</a>                         continue;
<a name="L265" href="source/net/ipv4/route.c#L265">265</a>                 *<a href="ident?i=pos">pos</a> = <a href="ident?i=cpu">cpu</a>+1;
<a name="L266" href="source/net/ipv4/route.c#L266">266</a>                 return &amp;<a href="ident?i=per_cpu">per_cpu</a>(<a href="ident?i=rt_cache_stat">rt_cache_stat</a>, <a href="ident?i=cpu">cpu</a>);
<a name="L267" href="source/net/ipv4/route.c#L267">267</a>         }
<a name="L268" href="source/net/ipv4/route.c#L268">268</a>         return <a href="ident?i=NULL">NULL</a>;
<a name="L269" href="source/net/ipv4/route.c#L269">269</a> 
<a name="L270" href="source/net/ipv4/route.c#L270">270</a> }
<a name="L271" href="source/net/ipv4/route.c#L271">271</a> 
<a name="L272" href="source/net/ipv4/route.c#L272">272</a> static void <a href="ident?i=rt_cpu_seq_stop">rt_cpu_seq_stop</a>(struct <a href="ident?i=seq_file">seq_file</a> *<a href="ident?i=seq">seq</a>, void *<a href="ident?i=v">v</a>)
<a name="L273" href="source/net/ipv4/route.c#L273">273</a> {
<a name="L274" href="source/net/ipv4/route.c#L274">274</a> 
<a name="L275" href="source/net/ipv4/route.c#L275">275</a> }
<a name="L276" href="source/net/ipv4/route.c#L276">276</a> 
<a name="L277" href="source/net/ipv4/route.c#L277">277</a> static int <a href="ident?i=rt_cpu_seq_show">rt_cpu_seq_show</a>(struct <a href="ident?i=seq_file">seq_file</a> *<a href="ident?i=seq">seq</a>, void *<a href="ident?i=v">v</a>)
<a name="L278" href="source/net/ipv4/route.c#L278">278</a> {
<a name="L279" href="source/net/ipv4/route.c#L279">279</a>         struct <a href="ident?i=rt_cache_stat">rt_cache_stat</a> *<a href="ident?i=st">st</a> = <a href="ident?i=v">v</a>;
<a name="L280" href="source/net/ipv4/route.c#L280">280</a> 
<a name="L281" href="source/net/ipv4/route.c#L281">281</a>         if (<a href="ident?i=v">v</a> == <a href="ident?i=SEQ_START_TOKEN">SEQ_START_TOKEN</a>) {
<a name="L282" href="source/net/ipv4/route.c#L282">282</a>                 <a href="ident?i=seq_printf">seq_printf</a>(<a href="ident?i=seq">seq</a>, <i>"entries  in_hit in_slow_tot in_slow_mc in_no_route in_brd in_martian_dst in_martian_src  out_hit out_slow_tot out_slow_mc  gc_total gc_ignored gc_goal_miss gc_dst_overflow in_hlist_search out_hlist_search\n"</i>);
<a name="L283" href="source/net/ipv4/route.c#L283">283</a>                 return 0;
<a name="L284" href="source/net/ipv4/route.c#L284">284</a>         }
<a name="L285" href="source/net/ipv4/route.c#L285">285</a> 
<a name="L286" href="source/net/ipv4/route.c#L286">286</a>         <a href="ident?i=seq_printf">seq_printf</a>(<a href="ident?i=seq">seq</a>,<i>"%08x  %08x %08x %08x %08x %08x %08x %08x "</i>
<a name="L287" href="source/net/ipv4/route.c#L287">287</a>                    <i>" %08x %08x %08x %08x %08x %08x %08x %08x %08x \n"</i>,
<a name="L288" href="source/net/ipv4/route.c#L288">288</a>                    <a href="ident?i=dst_entries_get_slow">dst_entries_get_slow</a>(&amp;<a href="ident?i=ipv4_dst_ops">ipv4_dst_ops</a>),
<a name="L289" href="source/net/ipv4/route.c#L289">289</a>                    0, <b><i>/* st-&gt;in_hit */</i></b>
<a name="L290" href="source/net/ipv4/route.c#L290">290</a>                    <a href="ident?i=st">st</a>-&gt;in_slow_tot,
<a name="L291" href="source/net/ipv4/route.c#L291">291</a>                    <a href="ident?i=st">st</a>-&gt;in_slow_mc,
<a name="L292" href="source/net/ipv4/route.c#L292">292</a>                    <a href="ident?i=st">st</a>-&gt;in_no_route,
<a name="L293" href="source/net/ipv4/route.c#L293">293</a>                    <a href="ident?i=st">st</a>-&gt;in_brd,
<a name="L294" href="source/net/ipv4/route.c#L294">294</a>                    <a href="ident?i=st">st</a>-&gt;in_martian_dst,
<a name="L295" href="source/net/ipv4/route.c#L295">295</a>                    <a href="ident?i=st">st</a>-&gt;in_martian_src,
<a name="L296" href="source/net/ipv4/route.c#L296">296</a> 
<a name="L297" href="source/net/ipv4/route.c#L297">297</a>                    0, <b><i>/* st-&gt;out_hit */</i></b>
<a name="L298" href="source/net/ipv4/route.c#L298">298</a>                    <a href="ident?i=st">st</a>-&gt;out_slow_tot,
<a name="L299" href="source/net/ipv4/route.c#L299">299</a>                    <a href="ident?i=st">st</a>-&gt;out_slow_mc,
<a name="L300" href="source/net/ipv4/route.c#L300">300</a> 
<a name="L301" href="source/net/ipv4/route.c#L301">301</a>                    0, <b><i>/* st-&gt;gc_total */</i></b>
<a name="L302" href="source/net/ipv4/route.c#L302">302</a>                    0, <b><i>/* st-&gt;gc_ignored */</i></b>
<a name="L303" href="source/net/ipv4/route.c#L303">303</a>                    0, <b><i>/* st-&gt;gc_goal_miss */</i></b>
<a name="L304" href="source/net/ipv4/route.c#L304">304</a>                    0, <b><i>/* st-&gt;gc_dst_overflow */</i></b>
<a name="L305" href="source/net/ipv4/route.c#L305">305</a>                    0, <b><i>/* st-&gt;in_hlist_search */</i></b>
<a name="L306" href="source/net/ipv4/route.c#L306">306</a>                    0  <b><i>/* st-&gt;out_hlist_search */</i></b>
<a name="L307" href="source/net/ipv4/route.c#L307">307</a>                 );
<a name="L308" href="source/net/ipv4/route.c#L308">308</a>         return 0;
<a name="L309" href="source/net/ipv4/route.c#L309">309</a> }
<a name="L310" href="source/net/ipv4/route.c#L310">310</a> 
<a name="L311" href="source/net/ipv4/route.c#L311">311</a> static const struct <a href="ident?i=seq_operations">seq_operations</a> <a href="ident?i=rt_cpu_seq_ops">rt_cpu_seq_ops</a> = {
<a name="L312" href="source/net/ipv4/route.c#L312">312</a>         .<a href="ident?i=start">start</a>  = <a href="ident?i=rt_cpu_seq_start">rt_cpu_seq_start</a>,
<a name="L313" href="source/net/ipv4/route.c#L313">313</a>         .<a href="ident?i=next">next</a>   = <a href="ident?i=rt_cpu_seq_next">rt_cpu_seq_next</a>,
<a name="L314" href="source/net/ipv4/route.c#L314">314</a>         .<a href="ident?i=stop">stop</a>   = <a href="ident?i=rt_cpu_seq_stop">rt_cpu_seq_stop</a>,
<a name="L315" href="source/net/ipv4/route.c#L315">315</a>         .<a href="ident?i=show">show</a>   = <a href="ident?i=rt_cpu_seq_show">rt_cpu_seq_show</a>,
<a name="L316" href="source/net/ipv4/route.c#L316">316</a> };
<a name="L317" href="source/net/ipv4/route.c#L317">317</a> 
<a name="L318" href="source/net/ipv4/route.c#L318">318</a> 
<a name="L319" href="source/net/ipv4/route.c#L319">319</a> static int <a href="ident?i=rt_cpu_seq_open">rt_cpu_seq_open</a>(struct <a href="ident?i=inode">inode</a> *<a href="ident?i=inode">inode</a>, struct <a href="ident?i=file">file</a> *<a href="ident?i=file">file</a>)
<a name="L320" href="source/net/ipv4/route.c#L320">320</a> {
<a name="L321" href="source/net/ipv4/route.c#L321">321</a>         return <a href="ident?i=seq_open">seq_open</a>(<a href="ident?i=file">file</a>, &amp;<a href="ident?i=rt_cpu_seq_ops">rt_cpu_seq_ops</a>);
<a name="L322" href="source/net/ipv4/route.c#L322">322</a> }
<a name="L323" href="source/net/ipv4/route.c#L323">323</a> 
<a name="L324" href="source/net/ipv4/route.c#L324">324</a> static const struct <a href="ident?i=file_operations">file_operations</a> <a href="ident?i=rt_cpu_seq_fops">rt_cpu_seq_fops</a> = {
<a name="L325" href="source/net/ipv4/route.c#L325">325</a>         .owner   = <a href="ident?i=THIS_MODULE">THIS_MODULE</a>,
<a name="L326" href="source/net/ipv4/route.c#L326">326</a>         .<a href="ident?i=open">open</a>    = <a href="ident?i=rt_cpu_seq_open">rt_cpu_seq_open</a>,
<a name="L327" href="source/net/ipv4/route.c#L327">327</a>         .<a href="ident?i=read">read</a>    = <a href="ident?i=seq_read">seq_read</a>,
<a name="L328" href="source/net/ipv4/route.c#L328">328</a>         .llseek  = <a href="ident?i=seq_lseek">seq_lseek</a>,
<a name="L329" href="source/net/ipv4/route.c#L329">329</a>         .<a href="ident?i=release">release</a> = <a href="ident?i=seq_release">seq_release</a>,
<a name="L330" href="source/net/ipv4/route.c#L330">330</a> };
<a name="L331" href="source/net/ipv4/route.c#L331">331</a> 
<a name="L332" href="source/net/ipv4/route.c#L332">332</a> #ifdef CONFIG_IP_ROUTE_CLASSID
<a name="L333" href="source/net/ipv4/route.c#L333">333</a> static int <a href="ident?i=rt_acct_proc_show">rt_acct_proc_show</a>(struct <a href="ident?i=seq_file">seq_file</a> *<a href="ident?i=m">m</a>, void *<a href="ident?i=v">v</a>)
<a name="L334" href="source/net/ipv4/route.c#L334">334</a> {
<a name="L335" href="source/net/ipv4/route.c#L335">335</a>         struct <a href="ident?i=ip_rt_acct">ip_rt_acct</a> *<a href="ident?i=dst">dst</a>, *<a href="ident?i=src">src</a>;
<a name="L336" href="source/net/ipv4/route.c#L336">336</a>         unsigned int <a href="ident?i=i">i</a>, j;
<a name="L337" href="source/net/ipv4/route.c#L337">337</a> 
<a name="L338" href="source/net/ipv4/route.c#L338">338</a>         <a href="ident?i=dst">dst</a> = <a href="ident?i=kcalloc">kcalloc</a>(256, sizeof(struct <a href="ident?i=ip_rt_acct">ip_rt_acct</a>), <a href="ident?i=GFP_KERNEL">GFP_KERNEL</a>);
<a name="L339" href="source/net/ipv4/route.c#L339">339</a>         if (!<a href="ident?i=dst">dst</a>)
<a name="L340" href="source/net/ipv4/route.c#L340">340</a>                 return -<a href="ident?i=ENOMEM">ENOMEM</a>;
<a name="L341" href="source/net/ipv4/route.c#L341">341</a> 
<a name="L342" href="source/net/ipv4/route.c#L342">342</a>         <a href="ident?i=for_each_possible_cpu">for_each_possible_cpu</a>(<a href="ident?i=i">i</a>) {
<a name="L343" href="source/net/ipv4/route.c#L343">343</a>                 <a href="ident?i=src">src</a> = (struct <a href="ident?i=ip_rt_acct">ip_rt_acct</a> *)<a href="ident?i=per_cpu_ptr">per_cpu_ptr</a>(<a href="ident?i=ip_rt_acct">ip_rt_acct</a>, <a href="ident?i=i">i</a>);
<a name="L344" href="source/net/ipv4/route.c#L344">344</a>                 for (j = 0; j &lt; 256; j++) {
<a name="L345" href="source/net/ipv4/route.c#L345">345</a>                         <a href="ident?i=dst">dst</a>[j].o_bytes   += <a href="ident?i=src">src</a>[j].o_bytes;
<a name="L346" href="source/net/ipv4/route.c#L346">346</a>                         <a href="ident?i=dst">dst</a>[j].o_packets += <a href="ident?i=src">src</a>[j].o_packets;
<a name="L347" href="source/net/ipv4/route.c#L347">347</a>                         <a href="ident?i=dst">dst</a>[j].i_bytes   += <a href="ident?i=src">src</a>[j].i_bytes;
<a name="L348" href="source/net/ipv4/route.c#L348">348</a>                         <a href="ident?i=dst">dst</a>[j].i_packets += <a href="ident?i=src">src</a>[j].i_packets;
<a name="L349" href="source/net/ipv4/route.c#L349">349</a>                 }
<a name="L350" href="source/net/ipv4/route.c#L350">350</a>         }
<a name="L351" href="source/net/ipv4/route.c#L351">351</a> 
<a name="L352" href="source/net/ipv4/route.c#L352">352</a>         <a href="ident?i=seq_write">seq_write</a>(<a href="ident?i=m">m</a>, <a href="ident?i=dst">dst</a>, 256 * sizeof(struct <a href="ident?i=ip_rt_acct">ip_rt_acct</a>));
<a name="L353" href="source/net/ipv4/route.c#L353">353</a>         <a href="ident?i=kfree">kfree</a>(<a href="ident?i=dst">dst</a>);
<a name="L354" href="source/net/ipv4/route.c#L354">354</a>         return 0;
<a name="L355" href="source/net/ipv4/route.c#L355">355</a> }
<a name="L356" href="source/net/ipv4/route.c#L356">356</a> 
<a name="L357" href="source/net/ipv4/route.c#L357">357</a> static int <a href="ident?i=rt_acct_proc_open">rt_acct_proc_open</a>(struct <a href="ident?i=inode">inode</a> *<a href="ident?i=inode">inode</a>, struct <a href="ident?i=file">file</a> *<a href="ident?i=file">file</a>)
<a name="L358" href="source/net/ipv4/route.c#L358">358</a> {
<a name="L359" href="source/net/ipv4/route.c#L359">359</a>         return <a href="ident?i=single_open">single_open</a>(<a href="ident?i=file">file</a>, <a href="ident?i=rt_acct_proc_show">rt_acct_proc_show</a>, <a href="ident?i=NULL">NULL</a>);
<a name="L360" href="source/net/ipv4/route.c#L360">360</a> }
<a name="L361" href="source/net/ipv4/route.c#L361">361</a> 
<a name="L362" href="source/net/ipv4/route.c#L362">362</a> static const struct <a href="ident?i=file_operations">file_operations</a> <a href="ident?i=rt_acct_proc_fops">rt_acct_proc_fops</a> = {
<a name="L363" href="source/net/ipv4/route.c#L363">363</a>         .owner          = <a href="ident?i=THIS_MODULE">THIS_MODULE</a>,
<a name="L364" href="source/net/ipv4/route.c#L364">364</a>         .<a href="ident?i=open">open</a>           = <a href="ident?i=rt_acct_proc_open">rt_acct_proc_open</a>,
<a name="L365" href="source/net/ipv4/route.c#L365">365</a>         .<a href="ident?i=read">read</a>           = <a href="ident?i=seq_read">seq_read</a>,
<a name="L366" href="source/net/ipv4/route.c#L366">366</a>         .llseek         = <a href="ident?i=seq_lseek">seq_lseek</a>,
<a name="L367" href="source/net/ipv4/route.c#L367">367</a>         .<a href="ident?i=release">release</a>        = <a href="ident?i=single_release">single_release</a>,
<a name="L368" href="source/net/ipv4/route.c#L368">368</a> };
<a name="L369" href="source/net/ipv4/route.c#L369">369</a> #endif
<a name="L370" href="source/net/ipv4/route.c#L370">370</a> 
<a name="L371" href="source/net/ipv4/route.c#L371">371</a> static int <a href="ident?i=__net_init">__net_init</a> <a href="ident?i=ip_rt_do_proc_init">ip_rt_do_proc_init</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>)
<a name="L372" href="source/net/ipv4/route.c#L372">372</a> {
<a name="L373" href="source/net/ipv4/route.c#L373">373</a>         struct <a href="ident?i=proc_dir_entry">proc_dir_entry</a> *pde;
<a name="L374" href="source/net/ipv4/route.c#L374">374</a> 
<a name="L375" href="source/net/ipv4/route.c#L375">375</a>         pde = <a href="ident?i=proc_create">proc_create</a>(<i>"rt_cache"</i>, <a href="ident?i=S_IRUGO">S_IRUGO</a>, <a href="ident?i=net">net</a>-&gt;proc_net,
<a name="L376" href="source/net/ipv4/route.c#L376">376</a>                           &amp;<a href="ident?i=rt_cache_seq_fops">rt_cache_seq_fops</a>);
<a name="L377" href="source/net/ipv4/route.c#L377">377</a>         if (!pde)
<a name="L378" href="source/net/ipv4/route.c#L378">378</a>                 goto err1;
<a name="L379" href="source/net/ipv4/route.c#L379">379</a> 
<a name="L380" href="source/net/ipv4/route.c#L380">380</a>         pde = <a href="ident?i=proc_create">proc_create</a>(<i>"rt_cache"</i>, <a href="ident?i=S_IRUGO">S_IRUGO</a>,
<a name="L381" href="source/net/ipv4/route.c#L381">381</a>                           <a href="ident?i=net">net</a>-&gt;proc_net_stat, &amp;<a href="ident?i=rt_cpu_seq_fops">rt_cpu_seq_fops</a>);
<a name="L382" href="source/net/ipv4/route.c#L382">382</a>         if (!pde)
<a name="L383" href="source/net/ipv4/route.c#L383">383</a>                 goto err2;
<a name="L384" href="source/net/ipv4/route.c#L384">384</a> 
<a name="L385" href="source/net/ipv4/route.c#L385">385</a> #ifdef CONFIG_IP_ROUTE_CLASSID
<a name="L386" href="source/net/ipv4/route.c#L386">386</a>         pde = <a href="ident?i=proc_create">proc_create</a>(<i>"rt_acct"</i>, 0, <a href="ident?i=net">net</a>-&gt;proc_net, &amp;<a href="ident?i=rt_acct_proc_fops">rt_acct_proc_fops</a>);
<a name="L387" href="source/net/ipv4/route.c#L387">387</a>         if (!pde)
<a name="L388" href="source/net/ipv4/route.c#L388">388</a>                 goto err3;
<a name="L389" href="source/net/ipv4/route.c#L389">389</a> #endif
<a name="L390" href="source/net/ipv4/route.c#L390">390</a>         return 0;
<a name="L391" href="source/net/ipv4/route.c#L391">391</a> 
<a name="L392" href="source/net/ipv4/route.c#L392">392</a> #ifdef CONFIG_IP_ROUTE_CLASSID
<a name="L393" href="source/net/ipv4/route.c#L393">393</a> err3:
<a name="L394" href="source/net/ipv4/route.c#L394">394</a>         <a href="ident?i=remove_proc_entry">remove_proc_entry</a>(<i>"rt_cache"</i>, <a href="ident?i=net">net</a>-&gt;proc_net_stat);
<a name="L395" href="source/net/ipv4/route.c#L395">395</a> #endif
<a name="L396" href="source/net/ipv4/route.c#L396">396</a> err2:
<a name="L397" href="source/net/ipv4/route.c#L397">397</a>         <a href="ident?i=remove_proc_entry">remove_proc_entry</a>(<i>"rt_cache"</i>, <a href="ident?i=net">net</a>-&gt;proc_net);
<a name="L398" href="source/net/ipv4/route.c#L398">398</a> err1:
<a name="L399" href="source/net/ipv4/route.c#L399">399</a>         return -<a href="ident?i=ENOMEM">ENOMEM</a>;
<a name="L400" href="source/net/ipv4/route.c#L400">400</a> }
<a name="L401" href="source/net/ipv4/route.c#L401">401</a> 
<a name="L402" href="source/net/ipv4/route.c#L402">402</a> static void <a href="ident?i=__net_exit">__net_exit</a> <a href="ident?i=ip_rt_do_proc_exit">ip_rt_do_proc_exit</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>)
<a name="L403" href="source/net/ipv4/route.c#L403">403</a> {
<a name="L404" href="source/net/ipv4/route.c#L404">404</a>         <a href="ident?i=remove_proc_entry">remove_proc_entry</a>(<i>"rt_cache"</i>, <a href="ident?i=net">net</a>-&gt;proc_net_stat);
<a name="L405" href="source/net/ipv4/route.c#L405">405</a>         <a href="ident?i=remove_proc_entry">remove_proc_entry</a>(<i>"rt_cache"</i>, <a href="ident?i=net">net</a>-&gt;proc_net);
<a name="L406" href="source/net/ipv4/route.c#L406">406</a> #ifdef CONFIG_IP_ROUTE_CLASSID
<a name="L407" href="source/net/ipv4/route.c#L407">407</a>         <a href="ident?i=remove_proc_entry">remove_proc_entry</a>(<i>"rt_acct"</i>, <a href="ident?i=net">net</a>-&gt;proc_net);
<a name="L408" href="source/net/ipv4/route.c#L408">408</a> #endif
<a name="L409" href="source/net/ipv4/route.c#L409">409</a> }
<a name="L410" href="source/net/ipv4/route.c#L410">410</a> 
<a name="L411" href="source/net/ipv4/route.c#L411">411</a> static struct <a href="ident?i=pernet_operations">pernet_operations</a> ip_rt_proc_ops <a href="ident?i=__net_initdata">__net_initdata</a> =  {
<a name="L412" href="source/net/ipv4/route.c#L412">412</a>         .<a href="ident?i=init">init</a> = <a href="ident?i=ip_rt_do_proc_init">ip_rt_do_proc_init</a>,
<a name="L413" href="source/net/ipv4/route.c#L413">413</a>         .<a href="ident?i=exit">exit</a> = <a href="ident?i=ip_rt_do_proc_exit">ip_rt_do_proc_exit</a>,
<a name="L414" href="source/net/ipv4/route.c#L414">414</a> };
<a name="L415" href="source/net/ipv4/route.c#L415">415</a> 
<a name="L416" href="source/net/ipv4/route.c#L416">416</a> static int <a href="ident?i=__init">__init</a> <a href="ident?i=ip_rt_proc_init">ip_rt_proc_init</a>(void)
<a name="L417" href="source/net/ipv4/route.c#L417">417</a> {
<a name="L418" href="source/net/ipv4/route.c#L418">418</a>         return <a href="ident?i=register_pernet_subsys">register_pernet_subsys</a>(&amp;ip_rt_proc_ops);
<a name="L419" href="source/net/ipv4/route.c#L419">419</a> }
<a name="L420" href="source/net/ipv4/route.c#L420">420</a> 
<a name="L421" href="source/net/ipv4/route.c#L421">421</a> #else
<a name="L422" href="source/net/ipv4/route.c#L422">422</a> static inline int <a href="ident?i=ip_rt_proc_init">ip_rt_proc_init</a>(void)
<a name="L423" href="source/net/ipv4/route.c#L423">423</a> {
<a name="L424" href="source/net/ipv4/route.c#L424">424</a>         return 0;
<a name="L425" href="source/net/ipv4/route.c#L425">425</a> }
<a name="L426" href="source/net/ipv4/route.c#L426">426</a> #endif <b><i>/* CONFIG_PROC_FS */</i></b>
<a name="L427" href="source/net/ipv4/route.c#L427">427</a> 
<a name="L428" href="source/net/ipv4/route.c#L428">428</a> static inline <a href="ident?i=bool">bool</a> <a href="ident?i=rt_is_expired">rt_is_expired</a>(const struct <a href="ident?i=rtable">rtable</a> *rth)
<a name="L429" href="source/net/ipv4/route.c#L429">429</a> {
<a name="L430" href="source/net/ipv4/route.c#L430">430</a>         return rth-&gt;rt_genid != <a href="ident?i=rt_genid_ipv4">rt_genid_ipv4</a>(<a href="ident?i=dev_net">dev_net</a>(rth-&gt;<a href="ident?i=dst">dst</a>.<a href="ident?i=dev">dev</a>));
<a name="L431" href="source/net/ipv4/route.c#L431">431</a> }
<a name="L432" href="source/net/ipv4/route.c#L432">432</a> 
<a name="L433" href="source/net/ipv4/route.c#L433">433</a> void <a href="ident?i=rt_cache_flush">rt_cache_flush</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>)
<a name="L434" href="source/net/ipv4/route.c#L434">434</a> {
<a name="L435" href="source/net/ipv4/route.c#L435">435</a>         <a href="ident?i=rt_genid_bump_ipv4">rt_genid_bump_ipv4</a>(<a href="ident?i=net">net</a>);
<a name="L436" href="source/net/ipv4/route.c#L436">436</a> }
<a name="L437" href="source/net/ipv4/route.c#L437">437</a> 
<a name="L438" href="source/net/ipv4/route.c#L438">438</a> static struct <a href="ident?i=neighbour">neighbour</a> *<a href="ident?i=ipv4_neigh_lookup">ipv4_neigh_lookup</a>(const struct <a href="ident?i=dst_entry">dst_entry</a> *<a href="ident?i=dst">dst</a>,
<a name="L439" href="source/net/ipv4/route.c#L439">439</a>                                            struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
<a name="L440" href="source/net/ipv4/route.c#L440">440</a>                                            const void *<a href="ident?i=daddr">daddr</a>)
<a name="L441" href="source/net/ipv4/route.c#L441">441</a> {
<a name="L442" href="source/net/ipv4/route.c#L442">442</a>         struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a> = <a href="ident?i=dst">dst</a>-&gt;<a href="ident?i=dev">dev</a>;
<a name="L443" href="source/net/ipv4/route.c#L443">443</a>         const <a href="ident?i=__be32">__be32</a> *pkey = <a href="ident?i=daddr">daddr</a>;
<a name="L444" href="source/net/ipv4/route.c#L444">444</a>         const struct <a href="ident?i=rtable">rtable</a> *<a href="ident?i=rt">rt</a>;
<a name="L445" href="source/net/ipv4/route.c#L445">445</a>         struct <a href="ident?i=neighbour">neighbour</a> *<a href="ident?i=n">n</a>;
<a name="L446" href="source/net/ipv4/route.c#L446">446</a> 
<a name="L447" href="source/net/ipv4/route.c#L447">447</a>         <a href="ident?i=rt">rt</a> = (const struct <a href="ident?i=rtable">rtable</a> *) <a href="ident?i=dst">dst</a>;
<a name="L448" href="source/net/ipv4/route.c#L448">448</a>         if (<a href="ident?i=rt">rt</a>-&gt;rt_gateway)
<a name="L449" href="source/net/ipv4/route.c#L449">449</a>                 pkey = (const <a href="ident?i=__be32">__be32</a> *) &amp;<a href="ident?i=rt">rt</a>-&gt;rt_gateway;
<a name="L450" href="source/net/ipv4/route.c#L450">450</a>         else if (<a href="ident?i=skb">skb</a>)
<a name="L451" href="source/net/ipv4/route.c#L451">451</a>                 pkey = &amp;<a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=daddr">daddr</a>;
<a name="L452" href="source/net/ipv4/route.c#L452">452</a> 
<a name="L453" href="source/net/ipv4/route.c#L453">453</a>         <a href="ident?i=n">n</a> = <a href="ident?i=__ipv4_neigh_lookup">__ipv4_neigh_lookup</a>(<a href="ident?i=dev">dev</a>, *(<a href="ident?i=__force">__force</a> <a href="ident?i=u32">u32</a> *)pkey);
<a name="L454" href="source/net/ipv4/route.c#L454">454</a>         if (<a href="ident?i=n">n</a>)
<a name="L455" href="source/net/ipv4/route.c#L455">455</a>                 return <a href="ident?i=n">n</a>;
<a name="L456" href="source/net/ipv4/route.c#L456">456</a>         return <a href="ident?i=neigh_create">neigh_create</a>(&amp;<a href="ident?i=arp_tbl">arp_tbl</a>, pkey, <a href="ident?i=dev">dev</a>);
<a name="L457" href="source/net/ipv4/route.c#L457">457</a> }
<a name="L458" href="source/net/ipv4/route.c#L458">458</a> 
<a name="L459" href="source/net/ipv4/route.c#L459">459</a> #define <a href="ident?i=IP_IDENTS_SZ">IP_IDENTS_SZ</a> 2048u
<a name="L460" href="source/net/ipv4/route.c#L460">460</a> struct <a href="ident?i=ip_ident_bucket">ip_ident_bucket</a> {
<a name="L461" href="source/net/ipv4/route.c#L461">461</a>         <a href="ident?i=atomic_t">atomic_t</a>        <a href="ident?i=id">id</a>;
<a name="L462" href="source/net/ipv4/route.c#L462">462</a>         <a href="ident?i=u32">u32</a>             stamp32;
<a name="L463" href="source/net/ipv4/route.c#L463">463</a> };
<a name="L464" href="source/net/ipv4/route.c#L464">464</a> 
<a name="L465" href="source/net/ipv4/route.c#L465">465</a> static struct <a href="ident?i=ip_ident_bucket">ip_ident_bucket</a> *ip_idents <a href="ident?i=__read_mostly">__read_mostly</a>;
<a name="L466" href="source/net/ipv4/route.c#L466">466</a> 
<a name="L467" href="source/net/ipv4/route.c#L467">467</a> <b><i>/* In order to protect privacy, we add a perturbation to identifiers</i></b>
<a name="L468" href="source/net/ipv4/route.c#L468">468</a> <b><i> * if one generator is seldom used. This makes hard for an attacker</i></b>
<a name="L469" href="source/net/ipv4/route.c#L469">469</a> <b><i> * to infer how many packets were sent between two points in time.</i></b>
<a name="L470" href="source/net/ipv4/route.c#L470">470</a> <b><i> */</i></b>
<a name="L471" href="source/net/ipv4/route.c#L471">471</a> <a href="ident?i=u32">u32</a> <a href="ident?i=ip_idents_reserve">ip_idents_reserve</a>(<a href="ident?i=u32">u32</a> <a href="ident?i=hash">hash</a>, int segs)
<a name="L472" href="source/net/ipv4/route.c#L472">472</a> {
<a name="L473" href="source/net/ipv4/route.c#L473">473</a>         struct <a href="ident?i=ip_ident_bucket">ip_ident_bucket</a> *<a href="ident?i=bucket">bucket</a> = ip_idents + <a href="ident?i=hash">hash</a> % <a href="ident?i=IP_IDENTS_SZ">IP_IDENTS_SZ</a>;
<a name="L474" href="source/net/ipv4/route.c#L474">474</a>         <a href="ident?i=u32">u32</a> <a href="ident?i=old">old</a> = <a href="ident?i=ACCESS_ONCE">ACCESS_ONCE</a>(<a href="ident?i=bucket">bucket</a>-&gt;stamp32);
<a name="L475" href="source/net/ipv4/route.c#L475">475</a>         <a href="ident?i=u32">u32</a> <a href="ident?i=now">now</a> = (<a href="ident?i=u32">u32</a>)<a href="ident?i=jiffies">jiffies</a>;
<a name="L476" href="source/net/ipv4/route.c#L476">476</a>         <a href="ident?i=u32">u32</a> <a href="ident?i=delta">delta</a> = 0;
<a name="L477" href="source/net/ipv4/route.c#L477">477</a> 
<a name="L478" href="source/net/ipv4/route.c#L478">478</a>         if (<a href="ident?i=old">old</a> != <a href="ident?i=now">now</a> &amp;&amp; <a href="ident?i=cmpxchg">cmpxchg</a>(&amp;<a href="ident?i=bucket">bucket</a>-&gt;stamp32, <a href="ident?i=old">old</a>, <a href="ident?i=now">now</a>) == <a href="ident?i=old">old</a>)
<a name="L479" href="source/net/ipv4/route.c#L479">479</a>                 <a href="ident?i=delta">delta</a> = <a href="ident?i=prandom_u32_max">prandom_u32_max</a>(<a href="ident?i=now">now</a> - <a href="ident?i=old">old</a>);
<a name="L480" href="source/net/ipv4/route.c#L480">480</a> 
<a name="L481" href="source/net/ipv4/route.c#L481">481</a>         return <a href="ident?i=atomic_add_return">atomic_add_return</a>(segs + <a href="ident?i=delta">delta</a>, &amp;<a href="ident?i=bucket">bucket</a>-&gt;<a href="ident?i=id">id</a>) - segs;
<a name="L482" href="source/net/ipv4/route.c#L482">482</a> }
<a name="L483" href="source/net/ipv4/route.c#L483">483</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=ip_idents_reserve">ip_idents_reserve</a>);
<a name="L484" href="source/net/ipv4/route.c#L484">484</a> 
<a name="L485" href="source/net/ipv4/route.c#L485">485</a> void <a href="ident?i=__ip_select_ident">__ip_select_ident</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>, struct <a href="ident?i=iphdr">iphdr</a> *iph, int segs)
<a name="L486" href="source/net/ipv4/route.c#L486">486</a> {
<a name="L487" href="source/net/ipv4/route.c#L487">487</a>         static <a href="ident?i=u32">u32</a> ip_idents_hashrnd <a href="ident?i=__read_mostly">__read_mostly</a>;
<a name="L488" href="source/net/ipv4/route.c#L488">488</a>         <a href="ident?i=u32">u32</a> <a href="ident?i=hash">hash</a>, <a href="ident?i=id">id</a>;
<a name="L489" href="source/net/ipv4/route.c#L489">489</a> 
<a name="L490" href="source/net/ipv4/route.c#L490">490</a>         <a href="ident?i=net_get_random_once">net_get_random_once</a>(&amp;ip_idents_hashrnd, sizeof(ip_idents_hashrnd));
<a name="L491" href="source/net/ipv4/route.c#L491">491</a> 
<a name="L492" href="source/net/ipv4/route.c#L492">492</a>         <a href="ident?i=hash">hash</a> = <a href="ident?i=jhash_3words">jhash_3words</a>((<a href="ident?i=__force">__force</a> <a href="ident?i=u32">u32</a>)iph-&gt;<a href="ident?i=daddr">daddr</a>,
<a name="L493" href="source/net/ipv4/route.c#L493">493</a>                             (<a href="ident?i=__force">__force</a> <a href="ident?i=u32">u32</a>)iph-&gt;<a href="ident?i=saddr">saddr</a>,
<a name="L494" href="source/net/ipv4/route.c#L494">494</a>                             iph-&gt;<a href="ident?i=protocol">protocol</a> ^ <a href="ident?i=net_hash_mix">net_hash_mix</a>(<a href="ident?i=net">net</a>),
<a name="L495" href="source/net/ipv4/route.c#L495">495</a>                             ip_idents_hashrnd);
<a name="L496" href="source/net/ipv4/route.c#L496">496</a>         <a href="ident?i=id">id</a> = <a href="ident?i=ip_idents_reserve">ip_idents_reserve</a>(<a href="ident?i=hash">hash</a>, segs);
<a name="L497" href="source/net/ipv4/route.c#L497">497</a>         iph-&gt;<a href="ident?i=id">id</a> = <a href="ident?i=htons">htons</a>(<a href="ident?i=id">id</a>);
<a name="L498" href="source/net/ipv4/route.c#L498">498</a> }
<a name="L499" href="source/net/ipv4/route.c#L499">499</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=__ip_select_ident">__ip_select_ident</a>);
<a name="L500" href="source/net/ipv4/route.c#L500">500</a> 
<a name="L501" href="source/net/ipv4/route.c#L501">501</a> static void <a href="ident?i=__build_flow_key">__build_flow_key</a>(struct <a href="ident?i=flowi4">flowi4</a> *fl4, const struct <a href="ident?i=sock">sock</a> *sk,
<a name="L502" href="source/net/ipv4/route.c#L502">502</a>                              const struct <a href="ident?i=iphdr">iphdr</a> *iph,
<a name="L503" href="source/net/ipv4/route.c#L503">503</a>                              int oif, <a href="ident?i=u8">u8</a> tos,
<a name="L504" href="source/net/ipv4/route.c#L504">504</a>                              <a href="ident?i=u8">u8</a> prot, <a href="ident?i=u32">u32</a> <a href="ident?i=mark">mark</a>, int flow_flags)
<a name="L505" href="source/net/ipv4/route.c#L505">505</a> {
<a name="L506" href="source/net/ipv4/route.c#L506">506</a>         if (sk) {
<a name="L507" href="source/net/ipv4/route.c#L507">507</a>                 const struct <a href="ident?i=inet_sock">inet_sock</a> *inet = <a href="ident?i=inet_sk">inet_sk</a>(sk);
<a name="L508" href="source/net/ipv4/route.c#L508">508</a> 
<a name="L509" href="source/net/ipv4/route.c#L509">509</a>                 oif = sk-&gt;<a href="ident?i=sk_bound_dev_if">sk_bound_dev_if</a>;
<a name="L510" href="source/net/ipv4/route.c#L510">510</a>                 <a href="ident?i=mark">mark</a> = sk-&gt;sk_mark;
<a name="L511" href="source/net/ipv4/route.c#L511">511</a>                 tos = <a href="ident?i=RT_CONN_FLAGS">RT_CONN_FLAGS</a>(sk);
<a name="L512" href="source/net/ipv4/route.c#L512">512</a>                 prot = inet-&gt;hdrincl ? <a href="ident?i=IPPROTO_RAW">IPPROTO_RAW</a> : sk-&gt;sk_protocol;
<a name="L513" href="source/net/ipv4/route.c#L513">513</a>         }
<a name="L514" href="source/net/ipv4/route.c#L514">514</a>         <a href="ident?i=flowi4_init_output">flowi4_init_output</a>(fl4, oif, <a href="ident?i=mark">mark</a>, tos,
<a name="L515" href="source/net/ipv4/route.c#L515">515</a>                            RT_SCOPE_UNIVERSE, prot,
<a name="L516" href="source/net/ipv4/route.c#L516">516</a>                            flow_flags,
<a name="L517" href="source/net/ipv4/route.c#L517">517</a>                            iph-&gt;<a href="ident?i=daddr">daddr</a>, iph-&gt;<a href="ident?i=saddr">saddr</a>, 0, 0);
<a name="L518" href="source/net/ipv4/route.c#L518">518</a> }
<a name="L519" href="source/net/ipv4/route.c#L519">519</a> 
<a name="L520" href="source/net/ipv4/route.c#L520">520</a> static void <a href="ident?i=build_skb_flow_key">build_skb_flow_key</a>(struct <a href="ident?i=flowi4">flowi4</a> *fl4, const struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
<a name="L521" href="source/net/ipv4/route.c#L521">521</a>                                const struct <a href="ident?i=sock">sock</a> *sk)
<a name="L522" href="source/net/ipv4/route.c#L522">522</a> {
<a name="L523" href="source/net/ipv4/route.c#L523">523</a>         const struct <a href="ident?i=iphdr">iphdr</a> *iph = <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>);
<a name="L524" href="source/net/ipv4/route.c#L524">524</a>         int oif = <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=dev">dev</a>-&gt;ifindex;
<a name="L525" href="source/net/ipv4/route.c#L525">525</a>         <a href="ident?i=u8">u8</a> tos = <a href="ident?i=RT_TOS">RT_TOS</a>(iph-&gt;tos);
<a name="L526" href="source/net/ipv4/route.c#L526">526</a>         <a href="ident?i=u8">u8</a> prot = iph-&gt;<a href="ident?i=protocol">protocol</a>;
<a name="L527" href="source/net/ipv4/route.c#L527">527</a>         <a href="ident?i=u32">u32</a> <a href="ident?i=mark">mark</a> = <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=mark">mark</a>;
<a name="L528" href="source/net/ipv4/route.c#L528">528</a> 
<a name="L529" href="source/net/ipv4/route.c#L529">529</a>         <a href="ident?i=__build_flow_key">__build_flow_key</a>(fl4, sk, iph, oif, tos, prot, <a href="ident?i=mark">mark</a>, 0);
<a name="L530" href="source/net/ipv4/route.c#L530">530</a> }
<a name="L531" href="source/net/ipv4/route.c#L531">531</a> 
<a name="L532" href="source/net/ipv4/route.c#L532">532</a> static void <a href="ident?i=build_sk_flow_key">build_sk_flow_key</a>(struct <a href="ident?i=flowi4">flowi4</a> *fl4, const struct <a href="ident?i=sock">sock</a> *sk)
<a name="L533" href="source/net/ipv4/route.c#L533">533</a> {
<a name="L534" href="source/net/ipv4/route.c#L534">534</a>         const struct <a href="ident?i=inet_sock">inet_sock</a> *inet = <a href="ident?i=inet_sk">inet_sk</a>(sk);
<a name="L535" href="source/net/ipv4/route.c#L535">535</a>         const struct <a href="ident?i=ip_options_rcu">ip_options_rcu</a> *inet_opt;
<a name="L536" href="source/net/ipv4/route.c#L536">536</a>         <a href="ident?i=__be32">__be32</a> <a href="ident?i=daddr">daddr</a> = inet-&gt;<a href="ident?i=inet_daddr">inet_daddr</a>;
<a name="L537" href="source/net/ipv4/route.c#L537">537</a> 
<a name="L538" href="source/net/ipv4/route.c#L538">538</a>         <a href="ident?i=rcu_read_lock">rcu_read_lock</a>();
<a name="L539" href="source/net/ipv4/route.c#L539">539</a>         inet_opt = <a href="ident?i=rcu_dereference">rcu_dereference</a>(inet-&gt;inet_opt);
<a name="L540" href="source/net/ipv4/route.c#L540">540</a>         if (inet_opt &amp;&amp; inet_opt-&gt;opt.<a href="ident?i=srr">srr</a>)
<a name="L541" href="source/net/ipv4/route.c#L541">541</a>                 <a href="ident?i=daddr">daddr</a> = inet_opt-&gt;opt.faddr;
<a name="L542" href="source/net/ipv4/route.c#L542">542</a>         <a href="ident?i=flowi4_init_output">flowi4_init_output</a>(fl4, sk-&gt;<a href="ident?i=sk_bound_dev_if">sk_bound_dev_if</a>, sk-&gt;sk_mark,
<a name="L543" href="source/net/ipv4/route.c#L543">543</a>                            <a href="ident?i=RT_CONN_FLAGS">RT_CONN_FLAGS</a>(sk), RT_SCOPE_UNIVERSE,
<a name="L544" href="source/net/ipv4/route.c#L544">544</a>                            inet-&gt;hdrincl ? <a href="ident?i=IPPROTO_RAW">IPPROTO_RAW</a> : sk-&gt;sk_protocol,
<a name="L545" href="source/net/ipv4/route.c#L545">545</a>                            <a href="ident?i=inet_sk_flowi_flags">inet_sk_flowi_flags</a>(sk),
<a name="L546" href="source/net/ipv4/route.c#L546">546</a>                            <a href="ident?i=daddr">daddr</a>, inet-&gt;inet_saddr, 0, 0);
<a name="L547" href="source/net/ipv4/route.c#L547">547</a>         <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L548" href="source/net/ipv4/route.c#L548">548</a> }
<a name="L549" href="source/net/ipv4/route.c#L549">549</a> 
<a name="L550" href="source/net/ipv4/route.c#L550">550</a> static void <a href="ident?i=ip_rt_build_flow_key">ip_rt_build_flow_key</a>(struct <a href="ident?i=flowi4">flowi4</a> *fl4, const struct <a href="ident?i=sock">sock</a> *sk,
<a name="L551" href="source/net/ipv4/route.c#L551">551</a>                                  const struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L552" href="source/net/ipv4/route.c#L552">552</a> {
<a name="L553" href="source/net/ipv4/route.c#L553">553</a>         if (<a href="ident?i=skb">skb</a>)
<a name="L554" href="source/net/ipv4/route.c#L554">554</a>                 <a href="ident?i=build_skb_flow_key">build_skb_flow_key</a>(fl4, <a href="ident?i=skb">skb</a>, sk);
<a name="L555" href="source/net/ipv4/route.c#L555">555</a>         else
<a name="L556" href="source/net/ipv4/route.c#L556">556</a>                 <a href="ident?i=build_sk_flow_key">build_sk_flow_key</a>(fl4, sk);
<a name="L557" href="source/net/ipv4/route.c#L557">557</a> }
<a name="L558" href="source/net/ipv4/route.c#L558">558</a> 
<a name="L559" href="source/net/ipv4/route.c#L559">559</a> static inline void <a href="ident?i=rt_free">rt_free</a>(struct <a href="ident?i=rtable">rtable</a> *<a href="ident?i=rt">rt</a>)
<a name="L560" href="source/net/ipv4/route.c#L560">560</a> {
<a name="L561" href="source/net/ipv4/route.c#L561">561</a>         <a href="ident?i=call_rcu">call_rcu</a>(&amp;<a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>.<a href="ident?i=rcu_head">rcu_head</a>, <a href="ident?i=dst_rcu_free">dst_rcu_free</a>);
<a name="L562" href="source/net/ipv4/route.c#L562">562</a> }
<a name="L563" href="source/net/ipv4/route.c#L563">563</a> 
<a name="L564" href="source/net/ipv4/route.c#L564">564</a> static <a href="ident?i=DEFINE_SPINLOCK">DEFINE_SPINLOCK</a>(fnhe_lock);
<a name="L565" href="source/net/ipv4/route.c#L565">565</a> 
<a name="L566" href="source/net/ipv4/route.c#L566">566</a> static void <a href="ident?i=fnhe_flush_routes">fnhe_flush_routes</a>(struct <a href="ident?i=fib_nh_exception">fib_nh_exception</a> *fnhe)
<a name="L567" href="source/net/ipv4/route.c#L567">567</a> {
<a name="L568" href="source/net/ipv4/route.c#L568">568</a>         struct <a href="ident?i=rtable">rtable</a> *<a href="ident?i=rt">rt</a>;
<a name="L569" href="source/net/ipv4/route.c#L569">569</a> 
<a name="L570" href="source/net/ipv4/route.c#L570">570</a>         <a href="ident?i=rt">rt</a> = <a href="ident?i=rcu_dereference">rcu_dereference</a>(fnhe-&gt;fnhe_rth_input);
<a name="L571" href="source/net/ipv4/route.c#L571">571</a>         if (<a href="ident?i=rt">rt</a>) {
<a name="L572" href="source/net/ipv4/route.c#L572">572</a>                 <a href="ident?i=RCU_INIT_POINTER">RCU_INIT_POINTER</a>(fnhe-&gt;fnhe_rth_input, <a href="ident?i=NULL">NULL</a>);
<a name="L573" href="source/net/ipv4/route.c#L573">573</a>                 <a href="ident?i=rt_free">rt_free</a>(<a href="ident?i=rt">rt</a>);
<a name="L574" href="source/net/ipv4/route.c#L574">574</a>         }
<a name="L575" href="source/net/ipv4/route.c#L575">575</a>         <a href="ident?i=rt">rt</a> = <a href="ident?i=rcu_dereference">rcu_dereference</a>(fnhe-&gt;fnhe_rth_output);
<a name="L576" href="source/net/ipv4/route.c#L576">576</a>         if (<a href="ident?i=rt">rt</a>) {
<a name="L577" href="source/net/ipv4/route.c#L577">577</a>                 <a href="ident?i=RCU_INIT_POINTER">RCU_INIT_POINTER</a>(fnhe-&gt;fnhe_rth_output, <a href="ident?i=NULL">NULL</a>);
<a name="L578" href="source/net/ipv4/route.c#L578">578</a>                 <a href="ident?i=rt_free">rt_free</a>(<a href="ident?i=rt">rt</a>);
<a name="L579" href="source/net/ipv4/route.c#L579">579</a>         }
<a name="L580" href="source/net/ipv4/route.c#L580">580</a> }
<a name="L581" href="source/net/ipv4/route.c#L581">581</a> 
<a name="L582" href="source/net/ipv4/route.c#L582">582</a> static struct <a href="ident?i=fib_nh_exception">fib_nh_exception</a> *<a href="ident?i=fnhe_oldest">fnhe_oldest</a>(struct <a href="ident?i=fnhe_hash_bucket">fnhe_hash_bucket</a> *<a href="ident?i=hash">hash</a>)
<a name="L583" href="source/net/ipv4/route.c#L583">583</a> {
<a name="L584" href="source/net/ipv4/route.c#L584">584</a>         struct <a href="ident?i=fib_nh_exception">fib_nh_exception</a> *fnhe, *oldest;
<a name="L585" href="source/net/ipv4/route.c#L585">585</a> 
<a name="L586" href="source/net/ipv4/route.c#L586">586</a>         oldest = <a href="ident?i=rcu_dereference">rcu_dereference</a>(<a href="ident?i=hash">hash</a>-&gt;<a href="ident?i=chain">chain</a>);
<a name="L587" href="source/net/ipv4/route.c#L587">587</a>         for (fnhe = <a href="ident?i=rcu_dereference">rcu_dereference</a>(oldest-&gt;fnhe_next); fnhe;
<a name="L588" href="source/net/ipv4/route.c#L588">588</a>              fnhe = <a href="ident?i=rcu_dereference">rcu_dereference</a>(fnhe-&gt;fnhe_next)) {
<a name="L589" href="source/net/ipv4/route.c#L589">589</a>                 if (<a href="ident?i=time_before">time_before</a>(fnhe-&gt;fnhe_stamp, oldest-&gt;fnhe_stamp))
<a name="L590" href="source/net/ipv4/route.c#L590">590</a>                         oldest = fnhe;
<a name="L591" href="source/net/ipv4/route.c#L591">591</a>         }
<a name="L592" href="source/net/ipv4/route.c#L592">592</a>         <a href="ident?i=fnhe_flush_routes">fnhe_flush_routes</a>(oldest);
<a name="L593" href="source/net/ipv4/route.c#L593">593</a>         return oldest;
<a name="L594" href="source/net/ipv4/route.c#L594">594</a> }
<a name="L595" href="source/net/ipv4/route.c#L595">595</a> 
<a name="L596" href="source/net/ipv4/route.c#L596">596</a> static inline <a href="ident?i=u32">u32</a> <a href="ident?i=fnhe_hashfun">fnhe_hashfun</a>(<a href="ident?i=__be32">__be32</a> <a href="ident?i=daddr">daddr</a>)
<a name="L597" href="source/net/ipv4/route.c#L597">597</a> {
<a name="L598" href="source/net/ipv4/route.c#L598">598</a>         static <a href="ident?i=u32">u32</a> fnhe_hashrnd <a href="ident?i=__read_mostly">__read_mostly</a>;
<a name="L599" href="source/net/ipv4/route.c#L599">599</a>         <a href="ident?i=u32">u32</a> hval;
<a name="L600" href="source/net/ipv4/route.c#L600">600</a> 
<a name="L601" href="source/net/ipv4/route.c#L601">601</a>         <a href="ident?i=net_get_random_once">net_get_random_once</a>(&amp;fnhe_hashrnd, sizeof(fnhe_hashrnd));
<a name="L602" href="source/net/ipv4/route.c#L602">602</a>         hval = <a href="ident?i=jhash_1word">jhash_1word</a>((<a href="ident?i=__force">__force</a> <a href="ident?i=u32">u32</a>) <a href="ident?i=daddr">daddr</a>, fnhe_hashrnd);
<a name="L603" href="source/net/ipv4/route.c#L603">603</a>         return <a href="ident?i=hash_32">hash_32</a>(hval, <a href="ident?i=FNHE_HASH_SHIFT">FNHE_HASH_SHIFT</a>);
<a name="L604" href="source/net/ipv4/route.c#L604">604</a> }
<a name="L605" href="source/net/ipv4/route.c#L605">605</a> 
<a name="L606" href="source/net/ipv4/route.c#L606">606</a> static void <a href="ident?i=fill_route_from_fnhe">fill_route_from_fnhe</a>(struct <a href="ident?i=rtable">rtable</a> *<a href="ident?i=rt">rt</a>, struct <a href="ident?i=fib_nh_exception">fib_nh_exception</a> *fnhe)
<a name="L607" href="source/net/ipv4/route.c#L607">607</a> {
<a name="L608" href="source/net/ipv4/route.c#L608">608</a>         <a href="ident?i=rt">rt</a>-&gt;rt_pmtu = fnhe-&gt;fnhe_pmtu;
<a name="L609" href="source/net/ipv4/route.c#L609">609</a>         <a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>.expires = fnhe-&gt;fnhe_expires;
<a name="L610" href="source/net/ipv4/route.c#L610">610</a> 
<a name="L611" href="source/net/ipv4/route.c#L611">611</a>         if (fnhe-&gt;fnhe_gw) {
<a name="L612" href="source/net/ipv4/route.c#L612">612</a>                 <a href="ident?i=rt">rt</a>-&gt;rt_flags |= <a href="ident?i=RTCF_REDIRECTED">RTCF_REDIRECTED</a>;
<a name="L613" href="source/net/ipv4/route.c#L613">613</a>                 <a href="ident?i=rt">rt</a>-&gt;rt_gateway = fnhe-&gt;fnhe_gw;
<a name="L614" href="source/net/ipv4/route.c#L614">614</a>                 <a href="ident?i=rt">rt</a>-&gt;rt_uses_gateway = 1;
<a name="L615" href="source/net/ipv4/route.c#L615">615</a>         }
<a name="L616" href="source/net/ipv4/route.c#L616">616</a> }
<a name="L617" href="source/net/ipv4/route.c#L617">617</a> 
<a name="L618" href="source/net/ipv4/route.c#L618">618</a> static void <a href="ident?i=update_or_create_fnhe">update_or_create_fnhe</a>(struct <a href="ident?i=fib_nh">fib_nh</a> *nh, <a href="ident?i=__be32">__be32</a> <a href="ident?i=daddr">daddr</a>, <a href="ident?i=__be32">__be32</a> gw,
<a name="L619" href="source/net/ipv4/route.c#L619">619</a>                                   <a href="ident?i=u32">u32</a> pmtu, unsigned long expires)
<a name="L620" href="source/net/ipv4/route.c#L620">620</a> {
<a name="L621" href="source/net/ipv4/route.c#L621">621</a>         struct <a href="ident?i=fnhe_hash_bucket">fnhe_hash_bucket</a> *<a href="ident?i=hash">hash</a>;
<a name="L622" href="source/net/ipv4/route.c#L622">622</a>         struct <a href="ident?i=fib_nh_exception">fib_nh_exception</a> *fnhe;
<a name="L623" href="source/net/ipv4/route.c#L623">623</a>         struct <a href="ident?i=rtable">rtable</a> *<a href="ident?i=rt">rt</a>;
<a name="L624" href="source/net/ipv4/route.c#L624">624</a>         unsigned int <a href="ident?i=i">i</a>;
<a name="L625" href="source/net/ipv4/route.c#L625">625</a>         int <a href="ident?i=depth">depth</a>;
<a name="L626" href="source/net/ipv4/route.c#L626">626</a>         <a href="ident?i=u32">u32</a> hval = <a href="ident?i=fnhe_hashfun">fnhe_hashfun</a>(<a href="ident?i=daddr">daddr</a>);
<a name="L627" href="source/net/ipv4/route.c#L627">627</a> 
<a name="L628" href="source/net/ipv4/route.c#L628">628</a>         <a href="ident?i=spin_lock_bh">spin_lock_bh</a>(&amp;fnhe_lock);
<a name="L629" href="source/net/ipv4/route.c#L629">629</a> 
<a name="L630" href="source/net/ipv4/route.c#L630">630</a>         <a href="ident?i=hash">hash</a> = <a href="ident?i=rcu_dereference">rcu_dereference</a>(nh-&gt;nh_exceptions);
<a name="L631" href="source/net/ipv4/route.c#L631">631</a>         if (!<a href="ident?i=hash">hash</a>) {
<a name="L632" href="source/net/ipv4/route.c#L632">632</a>                 <a href="ident?i=hash">hash</a> = <a href="ident?i=kzalloc">kzalloc</a>(<a href="ident?i=FNHE_HASH_SIZE">FNHE_HASH_SIZE</a> * sizeof(*<a href="ident?i=hash">hash</a>), <a href="ident?i=GFP_ATOMIC">GFP_ATOMIC</a>);
<a name="L633" href="source/net/ipv4/route.c#L633">633</a>                 if (!<a href="ident?i=hash">hash</a>)
<a name="L634" href="source/net/ipv4/route.c#L634">634</a>                         goto out_unlock;
<a name="L635" href="source/net/ipv4/route.c#L635">635</a>                 <a href="ident?i=rcu_assign_pointer">rcu_assign_pointer</a>(nh-&gt;nh_exceptions, <a href="ident?i=hash">hash</a>);
<a name="L636" href="source/net/ipv4/route.c#L636">636</a>         }
<a name="L637" href="source/net/ipv4/route.c#L637">637</a> 
<a name="L638" href="source/net/ipv4/route.c#L638">638</a>         <a href="ident?i=hash">hash</a> += hval;
<a name="L639" href="source/net/ipv4/route.c#L639">639</a> 
<a name="L640" href="source/net/ipv4/route.c#L640">640</a>         <a href="ident?i=depth">depth</a> = 0;
<a name="L641" href="source/net/ipv4/route.c#L641">641</a>         for (fnhe = <a href="ident?i=rcu_dereference">rcu_dereference</a>(<a href="ident?i=hash">hash</a>-&gt;<a href="ident?i=chain">chain</a>); fnhe;
<a name="L642" href="source/net/ipv4/route.c#L642">642</a>              fnhe = <a href="ident?i=rcu_dereference">rcu_dereference</a>(fnhe-&gt;fnhe_next)) {
<a name="L643" href="source/net/ipv4/route.c#L643">643</a>                 if (fnhe-&gt;fnhe_daddr == <a href="ident?i=daddr">daddr</a>)
<a name="L644" href="source/net/ipv4/route.c#L644">644</a>                         break;
<a name="L645" href="source/net/ipv4/route.c#L645">645</a>                 <a href="ident?i=depth">depth</a>++;
<a name="L646" href="source/net/ipv4/route.c#L646">646</a>         }
<a name="L647" href="source/net/ipv4/route.c#L647">647</a> 
<a name="L648" href="source/net/ipv4/route.c#L648">648</a>         if (fnhe) {
<a name="L649" href="source/net/ipv4/route.c#L649">649</a>                 if (gw)
<a name="L650" href="source/net/ipv4/route.c#L650">650</a>                         fnhe-&gt;fnhe_gw = gw;
<a name="L651" href="source/net/ipv4/route.c#L651">651</a>                 if (pmtu) {
<a name="L652" href="source/net/ipv4/route.c#L652">652</a>                         fnhe-&gt;fnhe_pmtu = pmtu;
<a name="L653" href="source/net/ipv4/route.c#L653">653</a>                         fnhe-&gt;fnhe_expires = <a href="ident?i=max">max</a>(1UL, expires);
<a name="L654" href="source/net/ipv4/route.c#L654">654</a>                 }
<a name="L655" href="source/net/ipv4/route.c#L655">655</a>                 <b><i>/* Update all cached dsts too */</i></b>
<a name="L656" href="source/net/ipv4/route.c#L656">656</a>                 <a href="ident?i=rt">rt</a> = <a href="ident?i=rcu_dereference">rcu_dereference</a>(fnhe-&gt;fnhe_rth_input);
<a name="L657" href="source/net/ipv4/route.c#L657">657</a>                 if (<a href="ident?i=rt">rt</a>)
<a name="L658" href="source/net/ipv4/route.c#L658">658</a>                         <a href="ident?i=fill_route_from_fnhe">fill_route_from_fnhe</a>(<a href="ident?i=rt">rt</a>, fnhe);
<a name="L659" href="source/net/ipv4/route.c#L659">659</a>                 <a href="ident?i=rt">rt</a> = <a href="ident?i=rcu_dereference">rcu_dereference</a>(fnhe-&gt;fnhe_rth_output);
<a name="L660" href="source/net/ipv4/route.c#L660">660</a>                 if (<a href="ident?i=rt">rt</a>)
<a name="L661" href="source/net/ipv4/route.c#L661">661</a>                         <a href="ident?i=fill_route_from_fnhe">fill_route_from_fnhe</a>(<a href="ident?i=rt">rt</a>, fnhe);
<a name="L662" href="source/net/ipv4/route.c#L662">662</a>         } else {
<a name="L663" href="source/net/ipv4/route.c#L663">663</a>                 if (<a href="ident?i=depth">depth</a> &gt; <a href="ident?i=FNHE_RECLAIM_DEPTH">FNHE_RECLAIM_DEPTH</a>)
<a name="L664" href="source/net/ipv4/route.c#L664">664</a>                         fnhe = <a href="ident?i=fnhe_oldest">fnhe_oldest</a>(<a href="ident?i=hash">hash</a>);
<a name="L665" href="source/net/ipv4/route.c#L665">665</a>                 else {
<a name="L666" href="source/net/ipv4/route.c#L666">666</a>                         fnhe = <a href="ident?i=kzalloc">kzalloc</a>(sizeof(*fnhe), <a href="ident?i=GFP_ATOMIC">GFP_ATOMIC</a>);
<a name="L667" href="source/net/ipv4/route.c#L667">667</a>                         if (!fnhe)
<a name="L668" href="source/net/ipv4/route.c#L668">668</a>                                 goto out_unlock;
<a name="L669" href="source/net/ipv4/route.c#L669">669</a> 
<a name="L670" href="source/net/ipv4/route.c#L670">670</a>                         fnhe-&gt;fnhe_next = <a href="ident?i=hash">hash</a>-&gt;<a href="ident?i=chain">chain</a>;
<a name="L671" href="source/net/ipv4/route.c#L671">671</a>                         <a href="ident?i=rcu_assign_pointer">rcu_assign_pointer</a>(<a href="ident?i=hash">hash</a>-&gt;<a href="ident?i=chain">chain</a>, fnhe);
<a name="L672" href="source/net/ipv4/route.c#L672">672</a>                 }
<a name="L673" href="source/net/ipv4/route.c#L673">673</a>                 fnhe-&gt;<a href="ident?i=fnhe_genid">fnhe_genid</a> = <a href="ident?i=fnhe_genid">fnhe_genid</a>(<a href="ident?i=dev_net">dev_net</a>(nh-&gt;nh_dev));
<a name="L674" href="source/net/ipv4/route.c#L674">674</a>                 fnhe-&gt;fnhe_daddr = <a href="ident?i=daddr">daddr</a>;
<a name="L675" href="source/net/ipv4/route.c#L675">675</a>                 fnhe-&gt;fnhe_gw = gw;
<a name="L676" href="source/net/ipv4/route.c#L676">676</a>                 fnhe-&gt;fnhe_pmtu = pmtu;
<a name="L677" href="source/net/ipv4/route.c#L677">677</a>                 fnhe-&gt;fnhe_expires = expires;
<a name="L678" href="source/net/ipv4/route.c#L678">678</a> 
<a name="L679" href="source/net/ipv4/route.c#L679">679</a>                 <b><i>/* Exception created; mark the cached routes for the nexthop</i></b>
<a name="L680" href="source/net/ipv4/route.c#L680">680</a> <b><i>                 * stale, so anyone caching it rechecks if this exception</i></b>
<a name="L681" href="source/net/ipv4/route.c#L681">681</a> <b><i>                 * applies to them.</i></b>
<a name="L682" href="source/net/ipv4/route.c#L682">682</a> <b><i>                 */</i></b>
<a name="L683" href="source/net/ipv4/route.c#L683">683</a>                 <a href="ident?i=rt">rt</a> = <a href="ident?i=rcu_dereference">rcu_dereference</a>(nh-&gt;nh_rth_input);
<a name="L684" href="source/net/ipv4/route.c#L684">684</a>                 if (<a href="ident?i=rt">rt</a>)
<a name="L685" href="source/net/ipv4/route.c#L685">685</a>                         <a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>.obsolete = <a href="ident?i=DST_OBSOLETE_KILL">DST_OBSOLETE_KILL</a>;
<a name="L686" href="source/net/ipv4/route.c#L686">686</a> 
<a name="L687" href="source/net/ipv4/route.c#L687">687</a>                 <a href="ident?i=for_each_possible_cpu">for_each_possible_cpu</a>(<a href="ident?i=i">i</a>) {
<a name="L688" href="source/net/ipv4/route.c#L688">688</a>                         struct <a href="ident?i=rtable">rtable</a> <a href="ident?i=__rcu">__rcu</a> **prt;
<a name="L689" href="source/net/ipv4/route.c#L689">689</a>                         prt = <a href="ident?i=per_cpu_ptr">per_cpu_ptr</a>(nh-&gt;nh_pcpu_rth_output, <a href="ident?i=i">i</a>);
<a name="L690" href="source/net/ipv4/route.c#L690">690</a>                         <a href="ident?i=rt">rt</a> = <a href="ident?i=rcu_dereference">rcu_dereference</a>(*prt);
<a name="L691" href="source/net/ipv4/route.c#L691">691</a>                         if (<a href="ident?i=rt">rt</a>)
<a name="L692" href="source/net/ipv4/route.c#L692">692</a>                                 <a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>.obsolete = <a href="ident?i=DST_OBSOLETE_KILL">DST_OBSOLETE_KILL</a>;
<a name="L693" href="source/net/ipv4/route.c#L693">693</a>                 }
<a name="L694" href="source/net/ipv4/route.c#L694">694</a>         }
<a name="L695" href="source/net/ipv4/route.c#L695">695</a> 
<a name="L696" href="source/net/ipv4/route.c#L696">696</a>         fnhe-&gt;fnhe_stamp = <a href="ident?i=jiffies">jiffies</a>;
<a name="L697" href="source/net/ipv4/route.c#L697">697</a> 
<a name="L698" href="source/net/ipv4/route.c#L698">698</a> out_unlock:
<a name="L699" href="source/net/ipv4/route.c#L699">699</a>         <a href="ident?i=spin_unlock_bh">spin_unlock_bh</a>(&amp;fnhe_lock);
<a name="L700" href="source/net/ipv4/route.c#L700">700</a> }
<a name="L701" href="source/net/ipv4/route.c#L701">701</a> 
<a name="L702" href="source/net/ipv4/route.c#L702">702</a> static void <a href="ident?i=__ip_do_redirect">__ip_do_redirect</a>(struct <a href="ident?i=rtable">rtable</a> *<a href="ident?i=rt">rt</a>, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, struct <a href="ident?i=flowi4">flowi4</a> *fl4,
<a name="L703" href="source/net/ipv4/route.c#L703">703</a>                              <a href="ident?i=bool">bool</a> kill_route)
<a name="L704" href="source/net/ipv4/route.c#L704">704</a> {
<a name="L705" href="source/net/ipv4/route.c#L705">705</a>         <a href="ident?i=__be32">__be32</a> new_gw = <a href="ident?i=icmp_hdr">icmp_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;un.gateway;
<a name="L706" href="source/net/ipv4/route.c#L706">706</a>         <a href="ident?i=__be32">__be32</a> old_gw = <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=saddr">saddr</a>;
<a name="L707" href="source/net/ipv4/route.c#L707">707</a>         struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a> = <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=dev">dev</a>;
<a name="L708" href="source/net/ipv4/route.c#L708">708</a>         struct <a href="ident?i=in_device">in_device</a> *in_dev;
<a name="L709" href="source/net/ipv4/route.c#L709">709</a>         struct <a href="ident?i=fib_result">fib_result</a> <a href="ident?i=res">res</a>;
<a name="L710" href="source/net/ipv4/route.c#L710">710</a>         struct <a href="ident?i=neighbour">neighbour</a> *<a href="ident?i=n">n</a>;
<a name="L711" href="source/net/ipv4/route.c#L711">711</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>;
<a name="L712" href="source/net/ipv4/route.c#L712">712</a> 
<a name="L713" href="source/net/ipv4/route.c#L713">713</a>         switch (<a href="ident?i=icmp_hdr">icmp_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=code">code</a> &amp; 7) {
<a name="L714" href="source/net/ipv4/route.c#L714">714</a>         case <a href="ident?i=ICMP_REDIR_NET">ICMP_REDIR_NET</a>:
<a name="L715" href="source/net/ipv4/route.c#L715">715</a>         case <a href="ident?i=ICMP_REDIR_NETTOS">ICMP_REDIR_NETTOS</a>:
<a name="L716" href="source/net/ipv4/route.c#L716">716</a>         case <a href="ident?i=ICMP_REDIR_HOST">ICMP_REDIR_HOST</a>:
<a name="L717" href="source/net/ipv4/route.c#L717">717</a>         case <a href="ident?i=ICMP_REDIR_HOSTTOS">ICMP_REDIR_HOSTTOS</a>:
<a name="L718" href="source/net/ipv4/route.c#L718">718</a>                 break;
<a name="L719" href="source/net/ipv4/route.c#L719">719</a> 
<a name="L720" href="source/net/ipv4/route.c#L720">720</a>         default:
<a name="L721" href="source/net/ipv4/route.c#L721">721</a>                 return;
<a name="L722" href="source/net/ipv4/route.c#L722">722</a>         }
<a name="L723" href="source/net/ipv4/route.c#L723">723</a> 
<a name="L724" href="source/net/ipv4/route.c#L724">724</a>         if (<a href="ident?i=rt">rt</a>-&gt;rt_gateway != old_gw)
<a name="L725" href="source/net/ipv4/route.c#L725">725</a>                 return;
<a name="L726" href="source/net/ipv4/route.c#L726">726</a> 
<a name="L727" href="source/net/ipv4/route.c#L727">727</a>         in_dev = <a href="ident?i=__in_dev_get_rcu">__in_dev_get_rcu</a>(<a href="ident?i=dev">dev</a>);
<a name="L728" href="source/net/ipv4/route.c#L728">728</a>         if (!in_dev)
<a name="L729" href="source/net/ipv4/route.c#L729">729</a>                 return;
<a name="L730" href="source/net/ipv4/route.c#L730">730</a> 
<a name="L731" href="source/net/ipv4/route.c#L731">731</a>         <a href="ident?i=net">net</a> = <a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=dev">dev</a>);
<a name="L732" href="source/net/ipv4/route.c#L732">732</a>         if (new_gw == old_gw || !<a href="ident?i=IN_DEV_RX_REDIRECTS">IN_DEV_RX_REDIRECTS</a>(in_dev) ||
<a name="L733" href="source/net/ipv4/route.c#L733">733</a>             <a href="ident?i=ipv4_is_multicast">ipv4_is_multicast</a>(new_gw) || <a href="ident?i=ipv4_is_lbcast">ipv4_is_lbcast</a>(new_gw) ||
<a name="L734" href="source/net/ipv4/route.c#L734">734</a>             <a href="ident?i=ipv4_is_zeronet">ipv4_is_zeronet</a>(new_gw))
<a name="L735" href="source/net/ipv4/route.c#L735">735</a>                 goto reject_redirect;
<a name="L736" href="source/net/ipv4/route.c#L736">736</a> 
<a name="L737" href="source/net/ipv4/route.c#L737">737</a>         if (!<a href="ident?i=IN_DEV_SHARED_MEDIA">IN_DEV_SHARED_MEDIA</a>(in_dev)) {
<a name="L738" href="source/net/ipv4/route.c#L738">738</a>                 if (!<a href="ident?i=inet_addr_onlink">inet_addr_onlink</a>(in_dev, new_gw, old_gw))
<a name="L739" href="source/net/ipv4/route.c#L739">739</a>                         goto reject_redirect;
<a name="L740" href="source/net/ipv4/route.c#L740">740</a>                 if (<a href="ident?i=IN_DEV_SEC_REDIRECTS">IN_DEV_SEC_REDIRECTS</a>(in_dev) &amp;&amp; <a href="ident?i=ip_fib_check_default">ip_fib_check_default</a>(new_gw, <a href="ident?i=dev">dev</a>))
<a name="L741" href="source/net/ipv4/route.c#L741">741</a>                         goto reject_redirect;
<a name="L742" href="source/net/ipv4/route.c#L742">742</a>         } else {
<a name="L743" href="source/net/ipv4/route.c#L743">743</a>                 if (<a href="ident?i=inet_addr_type">inet_addr_type</a>(<a href="ident?i=net">net</a>, new_gw) != RTN_UNICAST)
<a name="L744" href="source/net/ipv4/route.c#L744">744</a>                         goto reject_redirect;
<a name="L745" href="source/net/ipv4/route.c#L745">745</a>         }
<a name="L746" href="source/net/ipv4/route.c#L746">746</a> 
<a name="L747" href="source/net/ipv4/route.c#L747">747</a>         <a href="ident?i=n">n</a> = <a href="ident?i=ipv4_neigh_lookup">ipv4_neigh_lookup</a>(&amp;<a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>, <a href="ident?i=NULL">NULL</a>, &amp;new_gw);
<a name="L748" href="source/net/ipv4/route.c#L748">748</a>         if (!<a href="ident?i=IS_ERR">IS_ERR</a>(<a href="ident?i=n">n</a>)) {
<a name="L749" href="source/net/ipv4/route.c#L749">749</a>                 if (!(<a href="ident?i=n">n</a>-&gt;nud_state &amp; <a href="ident?i=NUD_VALID">NUD_VALID</a>)) {
<a name="L750" href="source/net/ipv4/route.c#L750">750</a>                         <a href="ident?i=neigh_event_send">neigh_event_send</a>(<a href="ident?i=n">n</a>, <a href="ident?i=NULL">NULL</a>);
<a name="L751" href="source/net/ipv4/route.c#L751">751</a>                 } else {
<a name="L752" href="source/net/ipv4/route.c#L752">752</a>                         if (<a href="ident?i=fib_lookup">fib_lookup</a>(<a href="ident?i=net">net</a>, fl4, &amp;<a href="ident?i=res">res</a>) == 0) {
<a name="L753" href="source/net/ipv4/route.c#L753">753</a>                                 struct <a href="ident?i=fib_nh">fib_nh</a> *nh = &amp;<a href="ident?i=FIB_RES_NH">FIB_RES_NH</a>(<a href="ident?i=res">res</a>);
<a name="L754" href="source/net/ipv4/route.c#L754">754</a> 
<a name="L755" href="source/net/ipv4/route.c#L755">755</a>                                 <a href="ident?i=update_or_create_fnhe">update_or_create_fnhe</a>(nh, fl4-&gt;<a href="ident?i=daddr">daddr</a>, new_gw,
<a name="L756" href="source/net/ipv4/route.c#L756">756</a>                                                       0, 0);
<a name="L757" href="source/net/ipv4/route.c#L757">757</a>                         }
<a name="L758" href="source/net/ipv4/route.c#L758">758</a>                         if (kill_route)
<a name="L759" href="source/net/ipv4/route.c#L759">759</a>                                 <a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>.obsolete = <a href="ident?i=DST_OBSOLETE_KILL">DST_OBSOLETE_KILL</a>;
<a name="L760" href="source/net/ipv4/route.c#L760">760</a>                         <a href="ident?i=call_netevent_notifiers">call_netevent_notifiers</a>(NETEVENT_NEIGH_UPDATE, <a href="ident?i=n">n</a>);
<a name="L761" href="source/net/ipv4/route.c#L761">761</a>                 }
<a name="L762" href="source/net/ipv4/route.c#L762">762</a>                 <a href="ident?i=neigh_release">neigh_release</a>(<a href="ident?i=n">n</a>);
<a name="L763" href="source/net/ipv4/route.c#L763">763</a>         }
<a name="L764" href="source/net/ipv4/route.c#L764">764</a>         return;
<a name="L765" href="source/net/ipv4/route.c#L765">765</a> 
<a name="L766" href="source/net/ipv4/route.c#L766">766</a> reject_redirect:
<a name="L767" href="source/net/ipv4/route.c#L767">767</a> #ifdef CONFIG_IP_ROUTE_VERBOSE
<a name="L768" href="source/net/ipv4/route.c#L768">768</a>         if (<a href="ident?i=IN_DEV_LOG_MARTIANS">IN_DEV_LOG_MARTIANS</a>(in_dev)) {
<a name="L769" href="source/net/ipv4/route.c#L769">769</a>                 const struct <a href="ident?i=iphdr">iphdr</a> *iph = (const struct <a href="ident?i=iphdr">iphdr</a> *) <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=data">data</a>;
<a name="L770" href="source/net/ipv4/route.c#L770">770</a>                 <a href="ident?i=__be32">__be32</a> <a href="ident?i=daddr">daddr</a> = iph-&gt;<a href="ident?i=daddr">daddr</a>;
<a name="L771" href="source/net/ipv4/route.c#L771">771</a>                 <a href="ident?i=__be32">__be32</a> <a href="ident?i=saddr">saddr</a> = iph-&gt;<a href="ident?i=saddr">saddr</a>;
<a name="L772" href="source/net/ipv4/route.c#L772">772</a> 
<a name="L773" href="source/net/ipv4/route.c#L773">773</a>                 <a href="ident?i=net_info_ratelimited">net_info_ratelimited</a>(<i>"Redirect from %pI4 on %s about %pI4 ignored\n"</i>
<a name="L774" href="source/net/ipv4/route.c#L774">774</a>                                      <i>"  Advised path = %pI4 -&gt; %pI4\n"</i>,
<a name="L775" href="source/net/ipv4/route.c#L775">775</a>                                      &amp;old_gw, <a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=name">name</a>, &amp;new_gw,
<a name="L776" href="source/net/ipv4/route.c#L776">776</a>                                      &amp;<a href="ident?i=saddr">saddr</a>, &amp;<a href="ident?i=daddr">daddr</a>);
<a name="L777" href="source/net/ipv4/route.c#L777">777</a>         }
<a name="L778" href="source/net/ipv4/route.c#L778">778</a> #endif
<a name="L779" href="source/net/ipv4/route.c#L779">779</a>         ;
<a name="L780" href="source/net/ipv4/route.c#L780">780</a> }
<a name="L781" href="source/net/ipv4/route.c#L781">781</a> 
<a name="L782" href="source/net/ipv4/route.c#L782">782</a> static void <a href="ident?i=ip_do_redirect">ip_do_redirect</a>(struct <a href="ident?i=dst_entry">dst_entry</a> *<a href="ident?i=dst">dst</a>, struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L783" href="source/net/ipv4/route.c#L783">783</a> {
<a name="L784" href="source/net/ipv4/route.c#L784">784</a>         struct <a href="ident?i=rtable">rtable</a> *<a href="ident?i=rt">rt</a>;
<a name="L785" href="source/net/ipv4/route.c#L785">785</a>         struct <a href="ident?i=flowi4">flowi4</a> fl4;
<a name="L786" href="source/net/ipv4/route.c#L786">786</a>         const struct <a href="ident?i=iphdr">iphdr</a> *iph = (const struct <a href="ident?i=iphdr">iphdr</a> *) <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=data">data</a>;
<a name="L787" href="source/net/ipv4/route.c#L787">787</a>         int oif = <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=dev">dev</a>-&gt;ifindex;
<a name="L788" href="source/net/ipv4/route.c#L788">788</a>         <a href="ident?i=u8">u8</a> tos = <a href="ident?i=RT_TOS">RT_TOS</a>(iph-&gt;tos);
<a name="L789" href="source/net/ipv4/route.c#L789">789</a>         <a href="ident?i=u8">u8</a> prot = iph-&gt;<a href="ident?i=protocol">protocol</a>;
<a name="L790" href="source/net/ipv4/route.c#L790">790</a>         <a href="ident?i=u32">u32</a> <a href="ident?i=mark">mark</a> = <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=mark">mark</a>;
<a name="L791" href="source/net/ipv4/route.c#L791">791</a> 
<a name="L792" href="source/net/ipv4/route.c#L792">792</a>         <a href="ident?i=rt">rt</a> = (struct <a href="ident?i=rtable">rtable</a> *) <a href="ident?i=dst">dst</a>;
<a name="L793" href="source/net/ipv4/route.c#L793">793</a> 
<a name="L794" href="source/net/ipv4/route.c#L794">794</a>         <a href="ident?i=__build_flow_key">__build_flow_key</a>(&amp;fl4, sk, iph, oif, tos, prot, <a href="ident?i=mark">mark</a>, 0);
<a name="L795" href="source/net/ipv4/route.c#L795">795</a>         <a href="ident?i=__ip_do_redirect">__ip_do_redirect</a>(<a href="ident?i=rt">rt</a>, <a href="ident?i=skb">skb</a>, &amp;fl4, <a href="ident?i=true">true</a>);
<a name="L796" href="source/net/ipv4/route.c#L796">796</a> }
<a name="L797" href="source/net/ipv4/route.c#L797">797</a> 
<a name="L798" href="source/net/ipv4/route.c#L798">798</a> static struct <a href="ident?i=dst_entry">dst_entry</a> *<a href="ident?i=ipv4_negative_advice">ipv4_negative_advice</a>(struct <a href="ident?i=dst_entry">dst_entry</a> *<a href="ident?i=dst">dst</a>)
<a name="L799" href="source/net/ipv4/route.c#L799">799</a> {
<a name="L800" href="source/net/ipv4/route.c#L800">800</a>         struct <a href="ident?i=rtable">rtable</a> *<a href="ident?i=rt">rt</a> = (struct <a href="ident?i=rtable">rtable</a> *)<a href="ident?i=dst">dst</a>;
<a name="L801" href="source/net/ipv4/route.c#L801">801</a>         struct <a href="ident?i=dst_entry">dst_entry</a> *<a href="ident?i=ret">ret</a> = <a href="ident?i=dst">dst</a>;
<a name="L802" href="source/net/ipv4/route.c#L802">802</a> 
<a name="L803" href="source/net/ipv4/route.c#L803">803</a>         if (<a href="ident?i=rt">rt</a>) {
<a name="L804" href="source/net/ipv4/route.c#L804">804</a>                 if (<a href="ident?i=dst">dst</a>-&gt;obsolete &gt; 0) {
<a name="L805" href="source/net/ipv4/route.c#L805">805</a>                         <a href="ident?i=ip_rt_put">ip_rt_put</a>(<a href="ident?i=rt">rt</a>);
<a name="L806" href="source/net/ipv4/route.c#L806">806</a>                         <a href="ident?i=ret">ret</a> = <a href="ident?i=NULL">NULL</a>;
<a name="L807" href="source/net/ipv4/route.c#L807">807</a>                 } else if ((<a href="ident?i=rt">rt</a>-&gt;rt_flags &amp; <a href="ident?i=RTCF_REDIRECTED">RTCF_REDIRECTED</a>) ||
<a name="L808" href="source/net/ipv4/route.c#L808">808</a>                            <a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>.expires) {
<a name="L809" href="source/net/ipv4/route.c#L809">809</a>                         <a href="ident?i=ip_rt_put">ip_rt_put</a>(<a href="ident?i=rt">rt</a>);
<a name="L810" href="source/net/ipv4/route.c#L810">810</a>                         <a href="ident?i=ret">ret</a> = <a href="ident?i=NULL">NULL</a>;
<a name="L811" href="source/net/ipv4/route.c#L811">811</a>                 }
<a name="L812" href="source/net/ipv4/route.c#L812">812</a>         }
<a name="L813" href="source/net/ipv4/route.c#L813">813</a>         return <a href="ident?i=ret">ret</a>;
<a name="L814" href="source/net/ipv4/route.c#L814">814</a> }
<a name="L815" href="source/net/ipv4/route.c#L815">815</a> 
<a name="L816" href="source/net/ipv4/route.c#L816">816</a> <b><i>/*</i></b>
<a name="L817" href="source/net/ipv4/route.c#L817">817</a> <b><i> * Algorithm:</i></b>
<a name="L818" href="source/net/ipv4/route.c#L818">818</a> <b><i> *      1. The first ip_rt_redirect_number redirects are sent</i></b>
<a name="L819" href="source/net/ipv4/route.c#L819">819</a> <b><i> *         with exponential backoff, then we stop sending them at all,</i></b>
<a name="L820" href="source/net/ipv4/route.c#L820">820</a> <b><i> *         assuming that the host ignores our redirects.</i></b>
<a name="L821" href="source/net/ipv4/route.c#L821">821</a> <b><i> *      2. If we did not see packets requiring redirects</i></b>
<a name="L822" href="source/net/ipv4/route.c#L822">822</a> <b><i> *         during ip_rt_redirect_silence, we assume that the host</i></b>
<a name="L823" href="source/net/ipv4/route.c#L823">823</a> <b><i> *         forgot redirected route and start to send redirects again.</i></b>
<a name="L824" href="source/net/ipv4/route.c#L824">824</a> <b><i> *</i></b>
<a name="L825" href="source/net/ipv4/route.c#L825">825</a> <b><i> * This algorithm is much cheaper and more intelligent than dumb load limiting</i></b>
<a name="L826" href="source/net/ipv4/route.c#L826">826</a> <b><i> * in icmp.c.</i></b>
<a name="L827" href="source/net/ipv4/route.c#L827">827</a> <b><i> *</i></b>
<a name="L828" href="source/net/ipv4/route.c#L828">828</a> <b><i> * NOTE. Do not forget to inhibit load limiting for redirects (redundant)</i></b>
<a name="L829" href="source/net/ipv4/route.c#L829">829</a> <b><i> * and "frag. need" (breaks PMTU discovery) in icmp.c.</i></b>
<a name="L830" href="source/net/ipv4/route.c#L830">830</a> <b><i> */</i></b>
<a name="L831" href="source/net/ipv4/route.c#L831">831</a> 
<a name="L832" href="source/net/ipv4/route.c#L832">832</a> void <a href="ident?i=ip_rt_send_redirect">ip_rt_send_redirect</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L833" href="source/net/ipv4/route.c#L833">833</a> {
<a name="L834" href="source/net/ipv4/route.c#L834">834</a>         struct <a href="ident?i=rtable">rtable</a> *<a href="ident?i=rt">rt</a> = <a href="ident?i=skb_rtable">skb_rtable</a>(<a href="ident?i=skb">skb</a>);
<a name="L835" href="source/net/ipv4/route.c#L835">835</a>         struct <a href="ident?i=in_device">in_device</a> *in_dev;
<a name="L836" href="source/net/ipv4/route.c#L836">836</a>         struct <a href="ident?i=inet_peer">inet_peer</a> *peer;
<a name="L837" href="source/net/ipv4/route.c#L837">837</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>;
<a name="L838" href="source/net/ipv4/route.c#L838">838</a>         int log_martians;
<a name="L839" href="source/net/ipv4/route.c#L839">839</a> 
<a name="L840" href="source/net/ipv4/route.c#L840">840</a>         <a href="ident?i=rcu_read_lock">rcu_read_lock</a>();
<a name="L841" href="source/net/ipv4/route.c#L841">841</a>         in_dev = <a href="ident?i=__in_dev_get_rcu">__in_dev_get_rcu</a>(<a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>.<a href="ident?i=dev">dev</a>);
<a name="L842" href="source/net/ipv4/route.c#L842">842</a>         if (!in_dev || !<a href="ident?i=IN_DEV_TX_REDIRECTS">IN_DEV_TX_REDIRECTS</a>(in_dev)) {
<a name="L843" href="source/net/ipv4/route.c#L843">843</a>                 <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L844" href="source/net/ipv4/route.c#L844">844</a>                 return;
<a name="L845" href="source/net/ipv4/route.c#L845">845</a>         }
<a name="L846" href="source/net/ipv4/route.c#L846">846</a>         log_martians = <a href="ident?i=IN_DEV_LOG_MARTIANS">IN_DEV_LOG_MARTIANS</a>(in_dev);
<a name="L847" href="source/net/ipv4/route.c#L847">847</a>         <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L848" href="source/net/ipv4/route.c#L848">848</a> 
<a name="L849" href="source/net/ipv4/route.c#L849">849</a>         <a href="ident?i=net">net</a> = <a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>.<a href="ident?i=dev">dev</a>);
<a name="L850" href="source/net/ipv4/route.c#L850">850</a>         peer = <a href="ident?i=inet_getpeer_v4">inet_getpeer_v4</a>(<a href="ident?i=net">net</a>-&gt;ipv4.peers, <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=saddr">saddr</a>, 1);
<a name="L851" href="source/net/ipv4/route.c#L851">851</a>         if (!peer) {
<a name="L852" href="source/net/ipv4/route.c#L852">852</a>                 <a href="ident?i=icmp_send">icmp_send</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=ICMP_REDIRECT">ICMP_REDIRECT</a>, <a href="ident?i=ICMP_REDIR_HOST">ICMP_REDIR_HOST</a>,
<a name="L853" href="source/net/ipv4/route.c#L853">853</a>                           <a href="ident?i=rt_nexthop">rt_nexthop</a>(<a href="ident?i=rt">rt</a>, <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=daddr">daddr</a>));
<a name="L854" href="source/net/ipv4/route.c#L854">854</a>                 return;
<a name="L855" href="source/net/ipv4/route.c#L855">855</a>         }
<a name="L856" href="source/net/ipv4/route.c#L856">856</a> 
<a name="L857" href="source/net/ipv4/route.c#L857">857</a>         <b><i>/* No redirected packets during ip_rt_redirect_silence;</i></b>
<a name="L858" href="source/net/ipv4/route.c#L858">858</a> <b><i>         * reset the algorithm.</i></b>
<a name="L859" href="source/net/ipv4/route.c#L859">859</a> <b><i>         */</i></b>
<a name="L860" href="source/net/ipv4/route.c#L860">860</a>         if (<a href="ident?i=time_after">time_after</a>(<a href="ident?i=jiffies">jiffies</a>, peer-&gt;rate_last + ip_rt_redirect_silence))
<a name="L861" href="source/net/ipv4/route.c#L861">861</a>                 peer-&gt;rate_tokens = 0;
<a name="L862" href="source/net/ipv4/route.c#L862">862</a> 
<a name="L863" href="source/net/ipv4/route.c#L863">863</a>         <b><i>/* Too many ignored redirects; do not send anything</i></b>
<a name="L864" href="source/net/ipv4/route.c#L864">864</a> <b><i>         * set dst.rate_last to the last seen redirected packet.</i></b>
<a name="L865" href="source/net/ipv4/route.c#L865">865</a> <b><i>         */</i></b>
<a name="L866" href="source/net/ipv4/route.c#L866">866</a>         if (peer-&gt;rate_tokens &gt;= ip_rt_redirect_number) {
<a name="L867" href="source/net/ipv4/route.c#L867">867</a>                 peer-&gt;rate_last = <a href="ident?i=jiffies">jiffies</a>;
<a name="L868" href="source/net/ipv4/route.c#L868">868</a>                 goto out_put_peer;
<a name="L869" href="source/net/ipv4/route.c#L869">869</a>         }
<a name="L870" href="source/net/ipv4/route.c#L870">870</a> 
<a name="L871" href="source/net/ipv4/route.c#L871">871</a>         <b><i>/* Check for load limit; set rate_last to the latest sent</i></b>
<a name="L872" href="source/net/ipv4/route.c#L872">872</a> <b><i>         * redirect.</i></b>
<a name="L873" href="source/net/ipv4/route.c#L873">873</a> <b><i>         */</i></b>
<a name="L874" href="source/net/ipv4/route.c#L874">874</a>         if (peer-&gt;rate_tokens == 0 ||
<a name="L875" href="source/net/ipv4/route.c#L875">875</a>             <a href="ident?i=time_after">time_after</a>(<a href="ident?i=jiffies">jiffies</a>,
<a name="L876" href="source/net/ipv4/route.c#L876">876</a>                        (peer-&gt;rate_last +
<a name="L877" href="source/net/ipv4/route.c#L877">877</a>                         (ip_rt_redirect_load &lt;&lt; peer-&gt;rate_tokens)))) {
<a name="L878" href="source/net/ipv4/route.c#L878">878</a>                 <a href="ident?i=__be32">__be32</a> gw = <a href="ident?i=rt_nexthop">rt_nexthop</a>(<a href="ident?i=rt">rt</a>, <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=daddr">daddr</a>);
<a name="L879" href="source/net/ipv4/route.c#L879">879</a> 
<a name="L880" href="source/net/ipv4/route.c#L880">880</a>                 <a href="ident?i=icmp_send">icmp_send</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=ICMP_REDIRECT">ICMP_REDIRECT</a>, <a href="ident?i=ICMP_REDIR_HOST">ICMP_REDIR_HOST</a>, gw);
<a name="L881" href="source/net/ipv4/route.c#L881">881</a>                 peer-&gt;rate_last = <a href="ident?i=jiffies">jiffies</a>;
<a name="L882" href="source/net/ipv4/route.c#L882">882</a>                 ++peer-&gt;rate_tokens;
<a name="L883" href="source/net/ipv4/route.c#L883">883</a> #ifdef CONFIG_IP_ROUTE_VERBOSE
<a name="L884" href="source/net/ipv4/route.c#L884">884</a>                 if (log_martians &amp;&amp;
<a name="L885" href="source/net/ipv4/route.c#L885">885</a>                     peer-&gt;rate_tokens == ip_rt_redirect_number)
<a name="L886" href="source/net/ipv4/route.c#L886">886</a>                         <a href="ident?i=net_warn_ratelimited">net_warn_ratelimited</a>(<i>"host %pI4/if%d ignores redirects for %pI4 to %pI4\n"</i>,
<a name="L887" href="source/net/ipv4/route.c#L887">887</a>                                              &amp;<a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=saddr">saddr</a>, <a href="ident?i=inet_iif">inet_iif</a>(<a href="ident?i=skb">skb</a>),
<a name="L888" href="source/net/ipv4/route.c#L888">888</a>                                              &amp;<a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=daddr">daddr</a>, &amp;gw);
<a name="L889" href="source/net/ipv4/route.c#L889">889</a> #endif
<a name="L890" href="source/net/ipv4/route.c#L890">890</a>         }
<a name="L891" href="source/net/ipv4/route.c#L891">891</a> out_put_peer:
<a name="L892" href="source/net/ipv4/route.c#L892">892</a>         <a href="ident?i=inet_putpeer">inet_putpeer</a>(peer);
<a name="L893" href="source/net/ipv4/route.c#L893">893</a> }
<a name="L894" href="source/net/ipv4/route.c#L894">894</a> 
<a name="L895" href="source/net/ipv4/route.c#L895">895</a> static int <a href="ident?i=ip_error">ip_error</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L896" href="source/net/ipv4/route.c#L896">896</a> {
<a name="L897" href="source/net/ipv4/route.c#L897">897</a>         struct <a href="ident?i=in_device">in_device</a> *in_dev = <a href="ident?i=__in_dev_get_rcu">__in_dev_get_rcu</a>(<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=dev">dev</a>);
<a name="L898" href="source/net/ipv4/route.c#L898">898</a>         struct <a href="ident?i=rtable">rtable</a> *<a href="ident?i=rt">rt</a> = <a href="ident?i=skb_rtable">skb_rtable</a>(<a href="ident?i=skb">skb</a>);
<a name="L899" href="source/net/ipv4/route.c#L899">899</a>         struct <a href="ident?i=inet_peer">inet_peer</a> *peer;
<a name="L900" href="source/net/ipv4/route.c#L900">900</a>         unsigned long <a href="ident?i=now">now</a>;
<a name="L901" href="source/net/ipv4/route.c#L901">901</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>;
<a name="L902" href="source/net/ipv4/route.c#L902">902</a>         <a href="ident?i=bool">bool</a> send;
<a name="L903" href="source/net/ipv4/route.c#L903">903</a>         int <a href="ident?i=code">code</a>;
<a name="L904" href="source/net/ipv4/route.c#L904">904</a> 
<a name="L905" href="source/net/ipv4/route.c#L905">905</a>         <b><i>/* IP on this device is disabled. */</i></b>
<a name="L906" href="source/net/ipv4/route.c#L906">906</a>         if (!in_dev)
<a name="L907" href="source/net/ipv4/route.c#L907">907</a>                 goto <a href="ident?i=out">out</a>;
<a name="L908" href="source/net/ipv4/route.c#L908">908</a> 
<a name="L909" href="source/net/ipv4/route.c#L909">909</a>         <a href="ident?i=net">net</a> = <a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>.<a href="ident?i=dev">dev</a>);
<a name="L910" href="source/net/ipv4/route.c#L910">910</a>         if (!<a href="ident?i=IN_DEV_FORWARD">IN_DEV_FORWARD</a>(in_dev)) {
<a name="L911" href="source/net/ipv4/route.c#L911">911</a>                 switch (<a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>.<a href="ident?i=error">error</a>) {
<a name="L912" href="source/net/ipv4/route.c#L912">912</a>                 case <a href="ident?i=EHOSTUNREACH">EHOSTUNREACH</a>:
<a name="L913" href="source/net/ipv4/route.c#L913">913</a>                         <a href="ident?i=IP_INC_STATS_BH">IP_INC_STATS_BH</a>(<a href="ident?i=net">net</a>, IPSTATS_MIB_INADDRERRORS);
<a name="L914" href="source/net/ipv4/route.c#L914">914</a>                         break;
<a name="L915" href="source/net/ipv4/route.c#L915">915</a> 
<a name="L916" href="source/net/ipv4/route.c#L916">916</a>                 case <a href="ident?i=ENETUNREACH">ENETUNREACH</a>:
<a name="L917" href="source/net/ipv4/route.c#L917">917</a>                         <a href="ident?i=IP_INC_STATS_BH">IP_INC_STATS_BH</a>(<a href="ident?i=net">net</a>, IPSTATS_MIB_INNOROUTES);
<a name="L918" href="source/net/ipv4/route.c#L918">918</a>                         break;
<a name="L919" href="source/net/ipv4/route.c#L919">919</a>                 }
<a name="L920" href="source/net/ipv4/route.c#L920">920</a>                 goto <a href="ident?i=out">out</a>;
<a name="L921" href="source/net/ipv4/route.c#L921">921</a>         }
<a name="L922" href="source/net/ipv4/route.c#L922">922</a> 
<a name="L923" href="source/net/ipv4/route.c#L923">923</a>         switch (<a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>.<a href="ident?i=error">error</a>) {
<a name="L924" href="source/net/ipv4/route.c#L924">924</a>         case <a href="ident?i=EINVAL">EINVAL</a>:
<a name="L925" href="source/net/ipv4/route.c#L925">925</a>         default:
<a name="L926" href="source/net/ipv4/route.c#L926">926</a>                 goto <a href="ident?i=out">out</a>;
<a name="L927" href="source/net/ipv4/route.c#L927">927</a>         case <a href="ident?i=EHOSTUNREACH">EHOSTUNREACH</a>:
<a name="L928" href="source/net/ipv4/route.c#L928">928</a>                 <a href="ident?i=code">code</a> = <a href="ident?i=ICMP_HOST_UNREACH">ICMP_HOST_UNREACH</a>;
<a name="L929" href="source/net/ipv4/route.c#L929">929</a>                 break;
<a name="L930" href="source/net/ipv4/route.c#L930">930</a>         case <a href="ident?i=ENETUNREACH">ENETUNREACH</a>:
<a name="L931" href="source/net/ipv4/route.c#L931">931</a>                 <a href="ident?i=code">code</a> = <a href="ident?i=ICMP_NET_UNREACH">ICMP_NET_UNREACH</a>;
<a name="L932" href="source/net/ipv4/route.c#L932">932</a>                 <a href="ident?i=IP_INC_STATS_BH">IP_INC_STATS_BH</a>(<a href="ident?i=net">net</a>, IPSTATS_MIB_INNOROUTES);
<a name="L933" href="source/net/ipv4/route.c#L933">933</a>                 break;
<a name="L934" href="source/net/ipv4/route.c#L934">934</a>         case <a href="ident?i=EACCES">EACCES</a>:
<a name="L935" href="source/net/ipv4/route.c#L935">935</a>                 <a href="ident?i=code">code</a> = <a href="ident?i=ICMP_PKT_FILTERED">ICMP_PKT_FILTERED</a>;
<a name="L936" href="source/net/ipv4/route.c#L936">936</a>                 break;
<a name="L937" href="source/net/ipv4/route.c#L937">937</a>         }
<a name="L938" href="source/net/ipv4/route.c#L938">938</a> 
<a name="L939" href="source/net/ipv4/route.c#L939">939</a>         peer = <a href="ident?i=inet_getpeer_v4">inet_getpeer_v4</a>(<a href="ident?i=net">net</a>-&gt;ipv4.peers, <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=saddr">saddr</a>, 1);
<a name="L940" href="source/net/ipv4/route.c#L940">940</a> 
<a name="L941" href="source/net/ipv4/route.c#L941">941</a>         send = <a href="ident?i=true">true</a>;
<a name="L942" href="source/net/ipv4/route.c#L942">942</a>         if (peer) {
<a name="L943" href="source/net/ipv4/route.c#L943">943</a>                 <a href="ident?i=now">now</a> = <a href="ident?i=jiffies">jiffies</a>;
<a name="L944" href="source/net/ipv4/route.c#L944">944</a>                 peer-&gt;rate_tokens += <a href="ident?i=now">now</a> - peer-&gt;rate_last;
<a name="L945" href="source/net/ipv4/route.c#L945">945</a>                 if (peer-&gt;rate_tokens &gt; ip_rt_error_burst)
<a name="L946" href="source/net/ipv4/route.c#L946">946</a>                         peer-&gt;rate_tokens = ip_rt_error_burst;
<a name="L947" href="source/net/ipv4/route.c#L947">947</a>                 peer-&gt;rate_last = <a href="ident?i=now">now</a>;
<a name="L948" href="source/net/ipv4/route.c#L948">948</a>                 if (peer-&gt;rate_tokens &gt;= ip_rt_error_cost)
<a name="L949" href="source/net/ipv4/route.c#L949">949</a>                         peer-&gt;rate_tokens -= ip_rt_error_cost;
<a name="L950" href="source/net/ipv4/route.c#L950">950</a>                 else
<a name="L951" href="source/net/ipv4/route.c#L951">951</a>                         send = <a href="ident?i=false">false</a>;
<a name="L952" href="source/net/ipv4/route.c#L952">952</a>                 <a href="ident?i=inet_putpeer">inet_putpeer</a>(peer);
<a name="L953" href="source/net/ipv4/route.c#L953">953</a>         }
<a name="L954" href="source/net/ipv4/route.c#L954">954</a>         if (send)
<a name="L955" href="source/net/ipv4/route.c#L955">955</a>                 <a href="ident?i=icmp_send">icmp_send</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=ICMP_DEST_UNREACH">ICMP_DEST_UNREACH</a>, <a href="ident?i=code">code</a>, 0);
<a name="L956" href="source/net/ipv4/route.c#L956">956</a> 
<a name="L957" href="source/net/ipv4/route.c#L957">957</a> <a href="ident?i=out">out</a>:    <a href="ident?i=kfree_skb">kfree_skb</a>(<a href="ident?i=skb">skb</a>);
<a name="L958" href="source/net/ipv4/route.c#L958">958</a>         return 0;
<a name="L959" href="source/net/ipv4/route.c#L959">959</a> }
<a name="L960" href="source/net/ipv4/route.c#L960">960</a> 
<a name="L961" href="source/net/ipv4/route.c#L961">961</a> static void <a href="ident?i=__ip_rt_update_pmtu">__ip_rt_update_pmtu</a>(struct <a href="ident?i=rtable">rtable</a> *<a href="ident?i=rt">rt</a>, struct <a href="ident?i=flowi4">flowi4</a> *fl4, <a href="ident?i=u32">u32</a> <a href="ident?i=mtu">mtu</a>)
<a name="L962" href="source/net/ipv4/route.c#L962">962</a> {
<a name="L963" href="source/net/ipv4/route.c#L963">963</a>         struct <a href="ident?i=dst_entry">dst_entry</a> *<a href="ident?i=dst">dst</a> = &amp;<a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>;
<a name="L964" href="source/net/ipv4/route.c#L964">964</a>         struct <a href="ident?i=fib_result">fib_result</a> <a href="ident?i=res">res</a>;
<a name="L965" href="source/net/ipv4/route.c#L965">965</a> 
<a name="L966" href="source/net/ipv4/route.c#L966">966</a>         if (<a href="ident?i=dst_metric_locked">dst_metric_locked</a>(<a href="ident?i=dst">dst</a>, <a href="ident?i=RTAX_MTU">RTAX_MTU</a>))
<a name="L967" href="source/net/ipv4/route.c#L967">967</a>                 return;
<a name="L968" href="source/net/ipv4/route.c#L968">968</a> 
<a name="L969" href="source/net/ipv4/route.c#L969">969</a>         if (<a href="ident?i=ipv4_mtu">ipv4_mtu</a>(<a href="ident?i=dst">dst</a>) &lt; <a href="ident?i=mtu">mtu</a>)
<a name="L970" href="source/net/ipv4/route.c#L970">970</a>                 return;
<a name="L971" href="source/net/ipv4/route.c#L971">971</a> 
<a name="L972" href="source/net/ipv4/route.c#L972">972</a>         if (<a href="ident?i=mtu">mtu</a> &lt; ip_rt_min_pmtu)
<a name="L973" href="source/net/ipv4/route.c#L973">973</a>                 <a href="ident?i=mtu">mtu</a> = ip_rt_min_pmtu;
<a name="L974" href="source/net/ipv4/route.c#L974">974</a> 
<a name="L975" href="source/net/ipv4/route.c#L975">975</a>         if (<a href="ident?i=rt">rt</a>-&gt;rt_pmtu == <a href="ident?i=mtu">mtu</a> &amp;&amp;
<a name="L976" href="source/net/ipv4/route.c#L976">976</a>             <a href="ident?i=time_before">time_before</a>(<a href="ident?i=jiffies">jiffies</a>, <a href="ident?i=dst">dst</a>-&gt;expires - ip_rt_mtu_expires / 2))
<a name="L977" href="source/net/ipv4/route.c#L977">977</a>                 return;
<a name="L978" href="source/net/ipv4/route.c#L978">978</a> 
<a name="L979" href="source/net/ipv4/route.c#L979">979</a>         <a href="ident?i=rcu_read_lock">rcu_read_lock</a>();
<a name="L980" href="source/net/ipv4/route.c#L980">980</a>         if (<a href="ident?i=fib_lookup">fib_lookup</a>(<a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=dst">dst</a>-&gt;<a href="ident?i=dev">dev</a>), fl4, &amp;<a href="ident?i=res">res</a>) == 0) {
<a name="L981" href="source/net/ipv4/route.c#L981">981</a>                 struct <a href="ident?i=fib_nh">fib_nh</a> *nh = &amp;<a href="ident?i=FIB_RES_NH">FIB_RES_NH</a>(<a href="ident?i=res">res</a>);
<a name="L982" href="source/net/ipv4/route.c#L982">982</a> 
<a name="L983" href="source/net/ipv4/route.c#L983">983</a>                 <a href="ident?i=update_or_create_fnhe">update_or_create_fnhe</a>(nh, fl4-&gt;<a href="ident?i=daddr">daddr</a>, 0, <a href="ident?i=mtu">mtu</a>,
<a name="L984" href="source/net/ipv4/route.c#L984">984</a>                                       <a href="ident?i=jiffies">jiffies</a> + ip_rt_mtu_expires);
<a name="L985" href="source/net/ipv4/route.c#L985">985</a>         }
<a name="L986" href="source/net/ipv4/route.c#L986">986</a>         <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L987" href="source/net/ipv4/route.c#L987">987</a> }
<a name="L988" href="source/net/ipv4/route.c#L988">988</a> 
<a name="L989" href="source/net/ipv4/route.c#L989">989</a> static void <a href="ident?i=ip_rt_update_pmtu">ip_rt_update_pmtu</a>(struct <a href="ident?i=dst_entry">dst_entry</a> *<a href="ident?i=dst">dst</a>, struct <a href="ident?i=sock">sock</a> *sk,
<a name="L990" href="source/net/ipv4/route.c#L990">990</a>                               struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, <a href="ident?i=u32">u32</a> <a href="ident?i=mtu">mtu</a>)
<a name="L991" href="source/net/ipv4/route.c#L991">991</a> {
<a name="L992" href="source/net/ipv4/route.c#L992">992</a>         struct <a href="ident?i=rtable">rtable</a> *<a href="ident?i=rt">rt</a> = (struct <a href="ident?i=rtable">rtable</a> *) <a href="ident?i=dst">dst</a>;
<a name="L993" href="source/net/ipv4/route.c#L993">993</a>         struct <a href="ident?i=flowi4">flowi4</a> fl4;
<a name="L994" href="source/net/ipv4/route.c#L994">994</a> 
<a name="L995" href="source/net/ipv4/route.c#L995">995</a>         <a href="ident?i=ip_rt_build_flow_key">ip_rt_build_flow_key</a>(&amp;fl4, sk, <a href="ident?i=skb">skb</a>);
<a name="L996" href="source/net/ipv4/route.c#L996">996</a>         <a href="ident?i=__ip_rt_update_pmtu">__ip_rt_update_pmtu</a>(<a href="ident?i=rt">rt</a>, &amp;fl4, <a href="ident?i=mtu">mtu</a>);
<a name="L997" href="source/net/ipv4/route.c#L997">997</a> }
<a name="L998" href="source/net/ipv4/route.c#L998">998</a> 
<a name="L999" href="source/net/ipv4/route.c#L999">999</a> void <a href="ident?i=ipv4_update_pmtu">ipv4_update_pmtu</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>, <a href="ident?i=u32">u32</a> <a href="ident?i=mtu">mtu</a>,
<a name="L1000" href="source/net/ipv4/route.c#L1000">1000</a>                       int oif, <a href="ident?i=u32">u32</a> <a href="ident?i=mark">mark</a>, <a href="ident?i=u8">u8</a> <a href="ident?i=protocol">protocol</a>, int flow_flags)
<a name="L1001" href="source/net/ipv4/route.c#L1001">1001</a> {
<a name="L1002" href="source/net/ipv4/route.c#L1002">1002</a>         const struct <a href="ident?i=iphdr">iphdr</a> *iph = (const struct <a href="ident?i=iphdr">iphdr</a> *) <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=data">data</a>;
<a name="L1003" href="source/net/ipv4/route.c#L1003">1003</a>         struct <a href="ident?i=flowi4">flowi4</a> fl4;
<a name="L1004" href="source/net/ipv4/route.c#L1004">1004</a>         struct <a href="ident?i=rtable">rtable</a> *<a href="ident?i=rt">rt</a>;
<a name="L1005" href="source/net/ipv4/route.c#L1005">1005</a> 
<a name="L1006" href="source/net/ipv4/route.c#L1006">1006</a>         if (!<a href="ident?i=mark">mark</a>)
<a name="L1007" href="source/net/ipv4/route.c#L1007">1007</a>                 <a href="ident?i=mark">mark</a> = <a href="ident?i=IP4_REPLY_MARK">IP4_REPLY_MARK</a>(<a href="ident?i=net">net</a>, <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=mark">mark</a>);
<a name="L1008" href="source/net/ipv4/route.c#L1008">1008</a> 
<a name="L1009" href="source/net/ipv4/route.c#L1009">1009</a>         <a href="ident?i=__build_flow_key">__build_flow_key</a>(&amp;fl4, <a href="ident?i=NULL">NULL</a>, iph, oif,
<a name="L1010" href="source/net/ipv4/route.c#L1010">1010</a>                          <a href="ident?i=RT_TOS">RT_TOS</a>(iph-&gt;tos), <a href="ident?i=protocol">protocol</a>, <a href="ident?i=mark">mark</a>, flow_flags);
<a name="L1011" href="source/net/ipv4/route.c#L1011">1011</a>         <a href="ident?i=rt">rt</a> = <a href="ident?i=__ip_route_output_key">__ip_route_output_key</a>(<a href="ident?i=net">net</a>, &amp;fl4);
<a name="L1012" href="source/net/ipv4/route.c#L1012">1012</a>         if (!<a href="ident?i=IS_ERR">IS_ERR</a>(<a href="ident?i=rt">rt</a>)) {
<a name="L1013" href="source/net/ipv4/route.c#L1013">1013</a>                 <a href="ident?i=__ip_rt_update_pmtu">__ip_rt_update_pmtu</a>(<a href="ident?i=rt">rt</a>, &amp;fl4, <a href="ident?i=mtu">mtu</a>);
<a name="L1014" href="source/net/ipv4/route.c#L1014">1014</a>                 <a href="ident?i=ip_rt_put">ip_rt_put</a>(<a href="ident?i=rt">rt</a>);
<a name="L1015" href="source/net/ipv4/route.c#L1015">1015</a>         }
<a name="L1016" href="source/net/ipv4/route.c#L1016">1016</a> }
<a name="L1017" href="source/net/ipv4/route.c#L1017">1017</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=ipv4_update_pmtu">ipv4_update_pmtu</a>);
<a name="L1018" href="source/net/ipv4/route.c#L1018">1018</a> 
<a name="L1019" href="source/net/ipv4/route.c#L1019">1019</a> static void <a href="ident?i=__ipv4_sk_update_pmtu">__ipv4_sk_update_pmtu</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, struct <a href="ident?i=sock">sock</a> *sk, <a href="ident?i=u32">u32</a> <a href="ident?i=mtu">mtu</a>)
<a name="L1020" href="source/net/ipv4/route.c#L1020">1020</a> {
<a name="L1021" href="source/net/ipv4/route.c#L1021">1021</a>         const struct <a href="ident?i=iphdr">iphdr</a> *iph = (const struct <a href="ident?i=iphdr">iphdr</a> *) <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=data">data</a>;
<a name="L1022" href="source/net/ipv4/route.c#L1022">1022</a>         struct <a href="ident?i=flowi4">flowi4</a> fl4;
<a name="L1023" href="source/net/ipv4/route.c#L1023">1023</a>         struct <a href="ident?i=rtable">rtable</a> *<a href="ident?i=rt">rt</a>;
<a name="L1024" href="source/net/ipv4/route.c#L1024">1024</a> 
<a name="L1025" href="source/net/ipv4/route.c#L1025">1025</a>         <a href="ident?i=__build_flow_key">__build_flow_key</a>(&amp;fl4, sk, iph, 0, 0, 0, 0, 0);
<a name="L1026" href="source/net/ipv4/route.c#L1026">1026</a> 
<a name="L1027" href="source/net/ipv4/route.c#L1027">1027</a>         if (!fl4.<a href="ident?i=flowi4_mark">flowi4_mark</a>)
<a name="L1028" href="source/net/ipv4/route.c#L1028">1028</a>                 fl4.<a href="ident?i=flowi4_mark">flowi4_mark</a> = <a href="ident?i=IP4_REPLY_MARK">IP4_REPLY_MARK</a>(<a href="ident?i=sock_net">sock_net</a>(sk), <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=mark">mark</a>);
<a name="L1029" href="source/net/ipv4/route.c#L1029">1029</a> 
<a name="L1030" href="source/net/ipv4/route.c#L1030">1030</a>         <a href="ident?i=rt">rt</a> = <a href="ident?i=__ip_route_output_key">__ip_route_output_key</a>(<a href="ident?i=sock_net">sock_net</a>(sk), &amp;fl4);
<a name="L1031" href="source/net/ipv4/route.c#L1031">1031</a>         if (!<a href="ident?i=IS_ERR">IS_ERR</a>(<a href="ident?i=rt">rt</a>)) {
<a name="L1032" href="source/net/ipv4/route.c#L1032">1032</a>                 <a href="ident?i=__ip_rt_update_pmtu">__ip_rt_update_pmtu</a>(<a href="ident?i=rt">rt</a>, &amp;fl4, <a href="ident?i=mtu">mtu</a>);
<a name="L1033" href="source/net/ipv4/route.c#L1033">1033</a>                 <a href="ident?i=ip_rt_put">ip_rt_put</a>(<a href="ident?i=rt">rt</a>);
<a name="L1034" href="source/net/ipv4/route.c#L1034">1034</a>         }
<a name="L1035" href="source/net/ipv4/route.c#L1035">1035</a> }
<a name="L1036" href="source/net/ipv4/route.c#L1036">1036</a> 
<a name="L1037" href="source/net/ipv4/route.c#L1037">1037</a> void <a href="ident?i=ipv4_sk_update_pmtu">ipv4_sk_update_pmtu</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, struct <a href="ident?i=sock">sock</a> *sk, <a href="ident?i=u32">u32</a> <a href="ident?i=mtu">mtu</a>)
<a name="L1038" href="source/net/ipv4/route.c#L1038">1038</a> {
<a name="L1039" href="source/net/ipv4/route.c#L1039">1039</a>         const struct <a href="ident?i=iphdr">iphdr</a> *iph = (const struct <a href="ident?i=iphdr">iphdr</a> *) <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=data">data</a>;
<a name="L1040" href="source/net/ipv4/route.c#L1040">1040</a>         struct <a href="ident?i=flowi4">flowi4</a> fl4;
<a name="L1041" href="source/net/ipv4/route.c#L1041">1041</a>         struct <a href="ident?i=rtable">rtable</a> *<a href="ident?i=rt">rt</a>;
<a name="L1042" href="source/net/ipv4/route.c#L1042">1042</a>         struct <a href="ident?i=dst_entry">dst_entry</a> *odst = <a href="ident?i=NULL">NULL</a>;
<a name="L1043" href="source/net/ipv4/route.c#L1043">1043</a>         <a href="ident?i=bool">bool</a> <a href="ident?i=new">new</a> = <a href="ident?i=false">false</a>;
<a name="L1044" href="source/net/ipv4/route.c#L1044">1044</a> 
<a name="L1045" href="source/net/ipv4/route.c#L1045">1045</a>         <a href="ident?i=bh_lock_sock">bh_lock_sock</a>(sk);
<a name="L1046" href="source/net/ipv4/route.c#L1046">1046</a> 
<a name="L1047" href="source/net/ipv4/route.c#L1047">1047</a>         if (!<a href="ident?i=ip_sk_accept_pmtu">ip_sk_accept_pmtu</a>(sk))
<a name="L1048" href="source/net/ipv4/route.c#L1048">1048</a>                 goto <a href="ident?i=out">out</a>;
<a name="L1049" href="source/net/ipv4/route.c#L1049">1049</a> 
<a name="L1050" href="source/net/ipv4/route.c#L1050">1050</a>         odst = <a href="ident?i=sk_dst_get">sk_dst_get</a>(sk);
<a name="L1051" href="source/net/ipv4/route.c#L1051">1051</a> 
<a name="L1052" href="source/net/ipv4/route.c#L1052">1052</a>         if (<a href="ident?i=sock_owned_by_user">sock_owned_by_user</a>(sk) || !odst) {
<a name="L1053" href="source/net/ipv4/route.c#L1053">1053</a>                 <a href="ident?i=__ipv4_sk_update_pmtu">__ipv4_sk_update_pmtu</a>(<a href="ident?i=skb">skb</a>, sk, <a href="ident?i=mtu">mtu</a>);
<a name="L1054" href="source/net/ipv4/route.c#L1054">1054</a>                 goto <a href="ident?i=out">out</a>;
<a name="L1055" href="source/net/ipv4/route.c#L1055">1055</a>         }
<a name="L1056" href="source/net/ipv4/route.c#L1056">1056</a> 
<a name="L1057" href="source/net/ipv4/route.c#L1057">1057</a>         <a href="ident?i=__build_flow_key">__build_flow_key</a>(&amp;fl4, sk, iph, 0, 0, 0, 0, 0);
<a name="L1058" href="source/net/ipv4/route.c#L1058">1058</a> 
<a name="L1059" href="source/net/ipv4/route.c#L1059">1059</a>         <a href="ident?i=rt">rt</a> = (struct <a href="ident?i=rtable">rtable</a> *)odst;
<a name="L1060" href="source/net/ipv4/route.c#L1060">1060</a>         if (odst-&gt;obsolete &amp;&amp; !odst-&gt;<a href="ident?i=ops">ops</a>-&gt;<a href="ident?i=check">check</a>(odst, 0)) {
<a name="L1061" href="source/net/ipv4/route.c#L1061">1061</a>                 <a href="ident?i=rt">rt</a> = <a href="ident?i=ip_route_output_flow">ip_route_output_flow</a>(<a href="ident?i=sock_net">sock_net</a>(sk), &amp;fl4, sk);
<a name="L1062" href="source/net/ipv4/route.c#L1062">1062</a>                 if (<a href="ident?i=IS_ERR">IS_ERR</a>(<a href="ident?i=rt">rt</a>))
<a name="L1063" href="source/net/ipv4/route.c#L1063">1063</a>                         goto <a href="ident?i=out">out</a>;
<a name="L1064" href="source/net/ipv4/route.c#L1064">1064</a> 
<a name="L1065" href="source/net/ipv4/route.c#L1065">1065</a>                 <a href="ident?i=new">new</a> = <a href="ident?i=true">true</a>;
<a name="L1066" href="source/net/ipv4/route.c#L1066">1066</a>         }
<a name="L1067" href="source/net/ipv4/route.c#L1067">1067</a> 
<a name="L1068" href="source/net/ipv4/route.c#L1068">1068</a>         <a href="ident?i=__ip_rt_update_pmtu">__ip_rt_update_pmtu</a>((struct <a href="ident?i=rtable">rtable</a> *) <a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>.<a href="ident?i=path">path</a>, &amp;fl4, <a href="ident?i=mtu">mtu</a>);
<a name="L1069" href="source/net/ipv4/route.c#L1069">1069</a> 
<a name="L1070" href="source/net/ipv4/route.c#L1070">1070</a>         if (!<a href="ident?i=dst_check">dst_check</a>(&amp;<a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>, 0)) {
<a name="L1071" href="source/net/ipv4/route.c#L1071">1071</a>                 if (<a href="ident?i=new">new</a>)
<a name="L1072" href="source/net/ipv4/route.c#L1072">1072</a>                         <a href="ident?i=dst_release">dst_release</a>(&amp;<a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>);
<a name="L1073" href="source/net/ipv4/route.c#L1073">1073</a> 
<a name="L1074" href="source/net/ipv4/route.c#L1074">1074</a>                 <a href="ident?i=rt">rt</a> = <a href="ident?i=ip_route_output_flow">ip_route_output_flow</a>(<a href="ident?i=sock_net">sock_net</a>(sk), &amp;fl4, sk);
<a name="L1075" href="source/net/ipv4/route.c#L1075">1075</a>                 if (<a href="ident?i=IS_ERR">IS_ERR</a>(<a href="ident?i=rt">rt</a>))
<a name="L1076" href="source/net/ipv4/route.c#L1076">1076</a>                         goto <a href="ident?i=out">out</a>;
<a name="L1077" href="source/net/ipv4/route.c#L1077">1077</a> 
<a name="L1078" href="source/net/ipv4/route.c#L1078">1078</a>                 <a href="ident?i=new">new</a> = <a href="ident?i=true">true</a>;
<a name="L1079" href="source/net/ipv4/route.c#L1079">1079</a>         }
<a name="L1080" href="source/net/ipv4/route.c#L1080">1080</a> 
<a name="L1081" href="source/net/ipv4/route.c#L1081">1081</a>         if (<a href="ident?i=new">new</a>)
<a name="L1082" href="source/net/ipv4/route.c#L1082">1082</a>                 <a href="ident?i=sk_dst_set">sk_dst_set</a>(sk, &amp;<a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>);
<a name="L1083" href="source/net/ipv4/route.c#L1083">1083</a> 
<a name="L1084" href="source/net/ipv4/route.c#L1084">1084</a> <a href="ident?i=out">out</a>:
<a name="L1085" href="source/net/ipv4/route.c#L1085">1085</a>         <a href="ident?i=bh_unlock_sock">bh_unlock_sock</a>(sk);
<a name="L1086" href="source/net/ipv4/route.c#L1086">1086</a>         <a href="ident?i=dst_release">dst_release</a>(odst);
<a name="L1087" href="source/net/ipv4/route.c#L1087">1087</a> }
<a name="L1088" href="source/net/ipv4/route.c#L1088">1088</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=ipv4_sk_update_pmtu">ipv4_sk_update_pmtu</a>);
<a name="L1089" href="source/net/ipv4/route.c#L1089">1089</a> 
<a name="L1090" href="source/net/ipv4/route.c#L1090">1090</a> void <a href="ident?i=ipv4_redirect">ipv4_redirect</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>,
<a name="L1091" href="source/net/ipv4/route.c#L1091">1091</a>                    int oif, <a href="ident?i=u32">u32</a> <a href="ident?i=mark">mark</a>, <a href="ident?i=u8">u8</a> <a href="ident?i=protocol">protocol</a>, int flow_flags)
<a name="L1092" href="source/net/ipv4/route.c#L1092">1092</a> {
<a name="L1093" href="source/net/ipv4/route.c#L1093">1093</a>         const struct <a href="ident?i=iphdr">iphdr</a> *iph = (const struct <a href="ident?i=iphdr">iphdr</a> *) <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=data">data</a>;
<a name="L1094" href="source/net/ipv4/route.c#L1094">1094</a>         struct <a href="ident?i=flowi4">flowi4</a> fl4;
<a name="L1095" href="source/net/ipv4/route.c#L1095">1095</a>         struct <a href="ident?i=rtable">rtable</a> *<a href="ident?i=rt">rt</a>;
<a name="L1096" href="source/net/ipv4/route.c#L1096">1096</a> 
<a name="L1097" href="source/net/ipv4/route.c#L1097">1097</a>         <a href="ident?i=__build_flow_key">__build_flow_key</a>(&amp;fl4, <a href="ident?i=NULL">NULL</a>, iph, oif,
<a name="L1098" href="source/net/ipv4/route.c#L1098">1098</a>                          <a href="ident?i=RT_TOS">RT_TOS</a>(iph-&gt;tos), <a href="ident?i=protocol">protocol</a>, <a href="ident?i=mark">mark</a>, flow_flags);
<a name="L1099" href="source/net/ipv4/route.c#L1099">1099</a>         <a href="ident?i=rt">rt</a> = <a href="ident?i=__ip_route_output_key">__ip_route_output_key</a>(<a href="ident?i=net">net</a>, &amp;fl4);
<a name="L1100" href="source/net/ipv4/route.c#L1100">1100</a>         if (!<a href="ident?i=IS_ERR">IS_ERR</a>(<a href="ident?i=rt">rt</a>)) {
<a name="L1101" href="source/net/ipv4/route.c#L1101">1101</a>                 <a href="ident?i=__ip_do_redirect">__ip_do_redirect</a>(<a href="ident?i=rt">rt</a>, <a href="ident?i=skb">skb</a>, &amp;fl4, <a href="ident?i=false">false</a>);
<a name="L1102" href="source/net/ipv4/route.c#L1102">1102</a>                 <a href="ident?i=ip_rt_put">ip_rt_put</a>(<a href="ident?i=rt">rt</a>);
<a name="L1103" href="source/net/ipv4/route.c#L1103">1103</a>         }
<a name="L1104" href="source/net/ipv4/route.c#L1104">1104</a> }
<a name="L1105" href="source/net/ipv4/route.c#L1105">1105</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=ipv4_redirect">ipv4_redirect</a>);
<a name="L1106" href="source/net/ipv4/route.c#L1106">1106</a> 
<a name="L1107" href="source/net/ipv4/route.c#L1107">1107</a> void <a href="ident?i=ipv4_sk_redirect">ipv4_sk_redirect</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, struct <a href="ident?i=sock">sock</a> *sk)
<a name="L1108" href="source/net/ipv4/route.c#L1108">1108</a> {
<a name="L1109" href="source/net/ipv4/route.c#L1109">1109</a>         const struct <a href="ident?i=iphdr">iphdr</a> *iph = (const struct <a href="ident?i=iphdr">iphdr</a> *) <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=data">data</a>;
<a name="L1110" href="source/net/ipv4/route.c#L1110">1110</a>         struct <a href="ident?i=flowi4">flowi4</a> fl4;
<a name="L1111" href="source/net/ipv4/route.c#L1111">1111</a>         struct <a href="ident?i=rtable">rtable</a> *<a href="ident?i=rt">rt</a>;
<a name="L1112" href="source/net/ipv4/route.c#L1112">1112</a> 
<a name="L1113" href="source/net/ipv4/route.c#L1113">1113</a>         <a href="ident?i=__build_flow_key">__build_flow_key</a>(&amp;fl4, sk, iph, 0, 0, 0, 0, 0);
<a name="L1114" href="source/net/ipv4/route.c#L1114">1114</a>         <a href="ident?i=rt">rt</a> = <a href="ident?i=__ip_route_output_key">__ip_route_output_key</a>(<a href="ident?i=sock_net">sock_net</a>(sk), &amp;fl4);
<a name="L1115" href="source/net/ipv4/route.c#L1115">1115</a>         if (!<a href="ident?i=IS_ERR">IS_ERR</a>(<a href="ident?i=rt">rt</a>)) {
<a name="L1116" href="source/net/ipv4/route.c#L1116">1116</a>                 <a href="ident?i=__ip_do_redirect">__ip_do_redirect</a>(<a href="ident?i=rt">rt</a>, <a href="ident?i=skb">skb</a>, &amp;fl4, <a href="ident?i=false">false</a>);
<a name="L1117" href="source/net/ipv4/route.c#L1117">1117</a>                 <a href="ident?i=ip_rt_put">ip_rt_put</a>(<a href="ident?i=rt">rt</a>);
<a name="L1118" href="source/net/ipv4/route.c#L1118">1118</a>         }
<a name="L1119" href="source/net/ipv4/route.c#L1119">1119</a> }
<a name="L1120" href="source/net/ipv4/route.c#L1120">1120</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=ipv4_sk_redirect">ipv4_sk_redirect</a>);
<a name="L1121" href="source/net/ipv4/route.c#L1121">1121</a> 
<a name="L1122" href="source/net/ipv4/route.c#L1122">1122</a> static struct <a href="ident?i=dst_entry">dst_entry</a> *<a href="ident?i=ipv4_dst_check">ipv4_dst_check</a>(struct <a href="ident?i=dst_entry">dst_entry</a> *<a href="ident?i=dst">dst</a>, <a href="ident?i=u32">u32</a> cookie)
<a name="L1123" href="source/net/ipv4/route.c#L1123">1123</a> {
<a name="L1124" href="source/net/ipv4/route.c#L1124">1124</a>         struct <a href="ident?i=rtable">rtable</a> *<a href="ident?i=rt">rt</a> = (struct <a href="ident?i=rtable">rtable</a> *) <a href="ident?i=dst">dst</a>;
<a name="L1125" href="source/net/ipv4/route.c#L1125">1125</a> 
<a name="L1126" href="source/net/ipv4/route.c#L1126">1126</a>         <b><i>/* All IPV4 dsts are created with -&gt;obsolete set to the value</i></b>
<a name="L1127" href="source/net/ipv4/route.c#L1127">1127</a> <b><i>         * DST_OBSOLETE_FORCE_CHK which forces validation calls down</i></b>
<a name="L1128" href="source/net/ipv4/route.c#L1128">1128</a> <b><i>         * into this function always.</i></b>
<a name="L1129" href="source/net/ipv4/route.c#L1129">1129</a> <b><i>         *</i></b>
<a name="L1130" href="source/net/ipv4/route.c#L1130">1130</a> <b><i>         * When a PMTU/redirect information update invalidates a route,</i></b>
<a name="L1131" href="source/net/ipv4/route.c#L1131">1131</a> <b><i>         * this is indicated by setting obsolete to DST_OBSOLETE_KILL or</i></b>
<a name="L1132" href="source/net/ipv4/route.c#L1132">1132</a> <b><i>         * DST_OBSOLETE_DEAD by dst_free().</i></b>
<a name="L1133" href="source/net/ipv4/route.c#L1133">1133</a> <b><i>         */</i></b>
<a name="L1134" href="source/net/ipv4/route.c#L1134">1134</a>         if (<a href="ident?i=dst">dst</a>-&gt;obsolete != <a href="ident?i=DST_OBSOLETE_FORCE_CHK">DST_OBSOLETE_FORCE_CHK</a> || <a href="ident?i=rt_is_expired">rt_is_expired</a>(<a href="ident?i=rt">rt</a>))
<a name="L1135" href="source/net/ipv4/route.c#L1135">1135</a>                 return <a href="ident?i=NULL">NULL</a>;
<a name="L1136" href="source/net/ipv4/route.c#L1136">1136</a>         return <a href="ident?i=dst">dst</a>;
<a name="L1137" href="source/net/ipv4/route.c#L1137">1137</a> }
<a name="L1138" href="source/net/ipv4/route.c#L1138">1138</a> 
<a name="L1139" href="source/net/ipv4/route.c#L1139">1139</a> static void <a href="ident?i=ipv4_link_failure">ipv4_link_failure</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L1140" href="source/net/ipv4/route.c#L1140">1140</a> {
<a name="L1141" href="source/net/ipv4/route.c#L1141">1141</a>         struct <a href="ident?i=rtable">rtable</a> *<a href="ident?i=rt">rt</a>;
<a name="L1142" href="source/net/ipv4/route.c#L1142">1142</a> 
<a name="L1143" href="source/net/ipv4/route.c#L1143">1143</a>         <a href="ident?i=icmp_send">icmp_send</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=ICMP_DEST_UNREACH">ICMP_DEST_UNREACH</a>, <a href="ident?i=ICMP_HOST_UNREACH">ICMP_HOST_UNREACH</a>, 0);
<a name="L1144" href="source/net/ipv4/route.c#L1144">1144</a> 
<a name="L1145" href="source/net/ipv4/route.c#L1145">1145</a>         <a href="ident?i=rt">rt</a> = <a href="ident?i=skb_rtable">skb_rtable</a>(<a href="ident?i=skb">skb</a>);
<a name="L1146" href="source/net/ipv4/route.c#L1146">1146</a>         if (<a href="ident?i=rt">rt</a>)
<a name="L1147" href="source/net/ipv4/route.c#L1147">1147</a>                 <a href="ident?i=dst_set_expires">dst_set_expires</a>(&amp;<a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>, 0);
<a name="L1148" href="source/net/ipv4/route.c#L1148">1148</a> }
<a name="L1149" href="source/net/ipv4/route.c#L1149">1149</a> 
<a name="L1150" href="source/net/ipv4/route.c#L1150">1150</a> static int <a href="ident?i=ip_rt_bug">ip_rt_bug</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L1151" href="source/net/ipv4/route.c#L1151">1151</a> {
<a name="L1152" href="source/net/ipv4/route.c#L1152">1152</a>         <a href="ident?i=pr_debug">pr_debug</a>(<i>"%s: %pI4 -&gt; %pI4, %s\n"</i>,
<a name="L1153" href="source/net/ipv4/route.c#L1153">1153</a>                  <a href="ident?i=__func__">__func__</a>, &amp;<a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=saddr">saddr</a>, &amp;<a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=daddr">daddr</a>,
<a name="L1154" href="source/net/ipv4/route.c#L1154">1154</a>                  <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=dev">dev</a> ? <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=name">name</a> : <i>"?"</i>);
<a name="L1155" href="source/net/ipv4/route.c#L1155">1155</a>         <a href="ident?i=kfree_skb">kfree_skb</a>(<a href="ident?i=skb">skb</a>);
<a name="L1156" href="source/net/ipv4/route.c#L1156">1156</a>         <a href="ident?i=WARN_ON">WARN_ON</a>(1);
<a name="L1157" href="source/net/ipv4/route.c#L1157">1157</a>         return 0;
<a name="L1158" href="source/net/ipv4/route.c#L1158">1158</a> }
<a name="L1159" href="source/net/ipv4/route.c#L1159">1159</a> 
<a name="L1160" href="source/net/ipv4/route.c#L1160">1160</a> <b><i>/*</i></b>
<a name="L1161" href="source/net/ipv4/route.c#L1161">1161</a> <b><i>   We do not cache source address of outgoing interface,</i></b>
<a name="L1162" href="source/net/ipv4/route.c#L1162">1162</a> <b><i>   because it is used only by IP RR, TS and SRR options,</i></b>
<a name="L1163" href="source/net/ipv4/route.c#L1163">1163</a> <b><i>   so that it out of fast path.</i></b>
<a name="L1164" href="source/net/ipv4/route.c#L1164">1164</a> <b><i></i></b>
<a name="L1165" href="source/net/ipv4/route.c#L1165">1165</a> <b><i>   BTW remember: "addr" is allowed to be not aligned</i></b>
<a name="L1166" href="source/net/ipv4/route.c#L1166">1166</a> <b><i>   in IP options!</i></b>
<a name="L1167" href="source/net/ipv4/route.c#L1167">1167</a> <b><i> */</i></b>
<a name="L1168" href="source/net/ipv4/route.c#L1168">1168</a> 
<a name="L1169" href="source/net/ipv4/route.c#L1169">1169</a> void <a href="ident?i=ip_rt_get_source">ip_rt_get_source</a>(<a href="ident?i=u8">u8</a> *<a href="ident?i=addr">addr</a>, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, struct <a href="ident?i=rtable">rtable</a> *<a href="ident?i=rt">rt</a>)
<a name="L1170" href="source/net/ipv4/route.c#L1170">1170</a> {
<a name="L1171" href="source/net/ipv4/route.c#L1171">1171</a>         <a href="ident?i=__be32">__be32</a> <a href="ident?i=src">src</a>;
<a name="L1172" href="source/net/ipv4/route.c#L1172">1172</a> 
<a name="L1173" href="source/net/ipv4/route.c#L1173">1173</a>         if (<a href="ident?i=rt_is_output_route">rt_is_output_route</a>(<a href="ident?i=rt">rt</a>))
<a name="L1174" href="source/net/ipv4/route.c#L1174">1174</a>                 <a href="ident?i=src">src</a> = <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=saddr">saddr</a>;
<a name="L1175" href="source/net/ipv4/route.c#L1175">1175</a>         else {
<a name="L1176" href="source/net/ipv4/route.c#L1176">1176</a>                 struct <a href="ident?i=fib_result">fib_result</a> <a href="ident?i=res">res</a>;
<a name="L1177" href="source/net/ipv4/route.c#L1177">1177</a>                 struct <a href="ident?i=flowi4">flowi4</a> fl4;
<a name="L1178" href="source/net/ipv4/route.c#L1178">1178</a>                 struct <a href="ident?i=iphdr">iphdr</a> *iph;
<a name="L1179" href="source/net/ipv4/route.c#L1179">1179</a> 
<a name="L1180" href="source/net/ipv4/route.c#L1180">1180</a>                 iph = <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>);
<a name="L1181" href="source/net/ipv4/route.c#L1181">1181</a> 
<a name="L1182" href="source/net/ipv4/route.c#L1182">1182</a>                 <a href="ident?i=memset">memset</a>(&amp;fl4, 0, sizeof(fl4));
<a name="L1183" href="source/net/ipv4/route.c#L1183">1183</a>                 fl4.<a href="ident?i=daddr">daddr</a> = iph-&gt;<a href="ident?i=daddr">daddr</a>;
<a name="L1184" href="source/net/ipv4/route.c#L1184">1184</a>                 fl4.<a href="ident?i=saddr">saddr</a> = iph-&gt;<a href="ident?i=saddr">saddr</a>;
<a name="L1185" href="source/net/ipv4/route.c#L1185">1185</a>                 fl4.<a href="ident?i=flowi4_tos">flowi4_tos</a> = <a href="ident?i=RT_TOS">RT_TOS</a>(iph-&gt;tos);
<a name="L1186" href="source/net/ipv4/route.c#L1186">1186</a>                 fl4.<a href="ident?i=flowi4_oif">flowi4_oif</a> = <a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>.<a href="ident?i=dev">dev</a>-&gt;ifindex;
<a name="L1187" href="source/net/ipv4/route.c#L1187">1187</a>                 fl4.<a href="ident?i=flowi4_iif">flowi4_iif</a> = <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=dev">dev</a>-&gt;ifindex;
<a name="L1188" href="source/net/ipv4/route.c#L1188">1188</a>                 fl4.<a href="ident?i=flowi4_mark">flowi4_mark</a> = <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=mark">mark</a>;
<a name="L1189" href="source/net/ipv4/route.c#L1189">1189</a> 
<a name="L1190" href="source/net/ipv4/route.c#L1190">1190</a>                 <a href="ident?i=rcu_read_lock">rcu_read_lock</a>();
<a name="L1191" href="source/net/ipv4/route.c#L1191">1191</a>                 if (<a href="ident?i=fib_lookup">fib_lookup</a>(<a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>.<a href="ident?i=dev">dev</a>), &amp;fl4, &amp;<a href="ident?i=res">res</a>) == 0)
<a name="L1192" href="source/net/ipv4/route.c#L1192">1192</a>                         <a href="ident?i=src">src</a> = <a href="ident?i=FIB_RES_PREFSRC">FIB_RES_PREFSRC</a>(<a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>.<a href="ident?i=dev">dev</a>), <a href="ident?i=res">res</a>);
<a name="L1193" href="source/net/ipv4/route.c#L1193">1193</a>                 else
<a name="L1194" href="source/net/ipv4/route.c#L1194">1194</a>                         <a href="ident?i=src">src</a> = <a href="ident?i=inet_select_addr">inet_select_addr</a>(<a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>.<a href="ident?i=dev">dev</a>,
<a name="L1195" href="source/net/ipv4/route.c#L1195">1195</a>                                                <a href="ident?i=rt_nexthop">rt_nexthop</a>(<a href="ident?i=rt">rt</a>, iph-&gt;<a href="ident?i=daddr">daddr</a>),
<a name="L1196" href="source/net/ipv4/route.c#L1196">1196</a>                                                RT_SCOPE_UNIVERSE);
<a name="L1197" href="source/net/ipv4/route.c#L1197">1197</a>                 <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L1198" href="source/net/ipv4/route.c#L1198">1198</a>         }
<a name="L1199" href="source/net/ipv4/route.c#L1199">1199</a>         <a href="ident?i=memcpy">memcpy</a>(<a href="ident?i=addr">addr</a>, &amp;<a href="ident?i=src">src</a>, 4);
<a name="L1200" href="source/net/ipv4/route.c#L1200">1200</a> }
<a name="L1201" href="source/net/ipv4/route.c#L1201">1201</a> 
<a name="L1202" href="source/net/ipv4/route.c#L1202">1202</a> #ifdef CONFIG_IP_ROUTE_CLASSID
<a name="L1203" href="source/net/ipv4/route.c#L1203">1203</a> static void <a href="ident?i=set_class_tag">set_class_tag</a>(struct <a href="ident?i=rtable">rtable</a> *<a href="ident?i=rt">rt</a>, <a href="ident?i=u32">u32</a> <a href="ident?i=tag">tag</a>)
<a name="L1204" href="source/net/ipv4/route.c#L1204">1204</a> {
<a name="L1205" href="source/net/ipv4/route.c#L1205">1205</a>         if (!(<a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>.tclassid &amp; 0xFFFF))
<a name="L1206" href="source/net/ipv4/route.c#L1206">1206</a>                 <a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>.tclassid |= <a href="ident?i=tag">tag</a> &amp; 0xFFFF;
<a name="L1207" href="source/net/ipv4/route.c#L1207">1207</a>         if (!(<a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>.tclassid &amp; 0xFFFF0000))
<a name="L1208" href="source/net/ipv4/route.c#L1208">1208</a>                 <a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>.tclassid |= <a href="ident?i=tag">tag</a> &amp; 0xFFFF0000;
<a name="L1209" href="source/net/ipv4/route.c#L1209">1209</a> }
<a name="L1210" href="source/net/ipv4/route.c#L1210">1210</a> #endif
<a name="L1211" href="source/net/ipv4/route.c#L1211">1211</a> 
<a name="L1212" href="source/net/ipv4/route.c#L1212">1212</a> static unsigned int <a href="ident?i=ipv4_default_advmss">ipv4_default_advmss</a>(const struct <a href="ident?i=dst_entry">dst_entry</a> *<a href="ident?i=dst">dst</a>)
<a name="L1213" href="source/net/ipv4/route.c#L1213">1213</a> {
<a name="L1214" href="source/net/ipv4/route.c#L1214">1214</a>         unsigned int advmss = <a href="ident?i=dst_metric_raw">dst_metric_raw</a>(<a href="ident?i=dst">dst</a>, <a href="ident?i=RTAX_ADVMSS">RTAX_ADVMSS</a>);
<a name="L1215" href="source/net/ipv4/route.c#L1215">1215</a> 
<a name="L1216" href="source/net/ipv4/route.c#L1216">1216</a>         if (advmss == 0) {
<a name="L1217" href="source/net/ipv4/route.c#L1217">1217</a>                 advmss = <a href="ident?i=max_t">max_t</a>(unsigned int, <a href="ident?i=dst">dst</a>-&gt;<a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=mtu">mtu</a> - 40,
<a name="L1218" href="source/net/ipv4/route.c#L1218">1218</a>                                ip_rt_min_advmss);
<a name="L1219" href="source/net/ipv4/route.c#L1219">1219</a>                 if (advmss &gt; 65535 - 40)
<a name="L1220" href="source/net/ipv4/route.c#L1220">1220</a>                         advmss = 65535 - 40;
<a name="L1221" href="source/net/ipv4/route.c#L1221">1221</a>         }
<a name="L1222" href="source/net/ipv4/route.c#L1222">1222</a>         return advmss;
<a name="L1223" href="source/net/ipv4/route.c#L1223">1223</a> }
<a name="L1224" href="source/net/ipv4/route.c#L1224">1224</a> 
<a name="L1225" href="source/net/ipv4/route.c#L1225">1225</a> static unsigned int <a href="ident?i=ipv4_mtu">ipv4_mtu</a>(const struct <a href="ident?i=dst_entry">dst_entry</a> *<a href="ident?i=dst">dst</a>)
<a name="L1226" href="source/net/ipv4/route.c#L1226">1226</a> {
<a name="L1227" href="source/net/ipv4/route.c#L1227">1227</a>         const struct <a href="ident?i=rtable">rtable</a> *<a href="ident?i=rt">rt</a> = (const struct <a href="ident?i=rtable">rtable</a> *) <a href="ident?i=dst">dst</a>;
<a name="L1228" href="source/net/ipv4/route.c#L1228">1228</a>         unsigned int <a href="ident?i=mtu">mtu</a> = <a href="ident?i=rt">rt</a>-&gt;rt_pmtu;
<a name="L1229" href="source/net/ipv4/route.c#L1229">1229</a> 
<a name="L1230" href="source/net/ipv4/route.c#L1230">1230</a>         if (!<a href="ident?i=mtu">mtu</a> || <a href="ident?i=time_after_eq">time_after_eq</a>(<a href="ident?i=jiffies">jiffies</a>, <a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>.expires))
<a name="L1231" href="source/net/ipv4/route.c#L1231">1231</a>                 <a href="ident?i=mtu">mtu</a> = <a href="ident?i=dst_metric_raw">dst_metric_raw</a>(<a href="ident?i=dst">dst</a>, <a href="ident?i=RTAX_MTU">RTAX_MTU</a>);
<a name="L1232" href="source/net/ipv4/route.c#L1232">1232</a> 
<a name="L1233" href="source/net/ipv4/route.c#L1233">1233</a>         if (<a href="ident?i=mtu">mtu</a>)
<a name="L1234" href="source/net/ipv4/route.c#L1234">1234</a>                 return <a href="ident?i=mtu">mtu</a>;
<a name="L1235" href="source/net/ipv4/route.c#L1235">1235</a> 
<a name="L1236" href="source/net/ipv4/route.c#L1236">1236</a>         <a href="ident?i=mtu">mtu</a> = <a href="ident?i=dst">dst</a>-&gt;<a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=mtu">mtu</a>;
<a name="L1237" href="source/net/ipv4/route.c#L1237">1237</a> 
<a name="L1238" href="source/net/ipv4/route.c#L1238">1238</a>         if (<a href="ident?i=unlikely">unlikely</a>(<a href="ident?i=dst_metric_locked">dst_metric_locked</a>(<a href="ident?i=dst">dst</a>, <a href="ident?i=RTAX_MTU">RTAX_MTU</a>))) {
<a name="L1239" href="source/net/ipv4/route.c#L1239">1239</a>                 if (<a href="ident?i=rt">rt</a>-&gt;rt_uses_gateway &amp;&amp; <a href="ident?i=mtu">mtu</a> &gt; 576)
<a name="L1240" href="source/net/ipv4/route.c#L1240">1240</a>                         <a href="ident?i=mtu">mtu</a> = 576;
<a name="L1241" href="source/net/ipv4/route.c#L1241">1241</a>         }
<a name="L1242" href="source/net/ipv4/route.c#L1242">1242</a> 
<a name="L1243" href="source/net/ipv4/route.c#L1243">1243</a>         return <a href="ident?i=min_t">min_t</a>(unsigned int, <a href="ident?i=mtu">mtu</a>, <a href="ident?i=IP_MAX_MTU">IP_MAX_MTU</a>);
<a name="L1244" href="source/net/ipv4/route.c#L1244">1244</a> }
<a name="L1245" href="source/net/ipv4/route.c#L1245">1245</a> 
<a name="L1246" href="source/net/ipv4/route.c#L1246">1246</a> static struct <a href="ident?i=fib_nh_exception">fib_nh_exception</a> *<a href="ident?i=find_exception">find_exception</a>(struct <a href="ident?i=fib_nh">fib_nh</a> *nh, <a href="ident?i=__be32">__be32</a> <a href="ident?i=daddr">daddr</a>)
<a name="L1247" href="source/net/ipv4/route.c#L1247">1247</a> {
<a name="L1248" href="source/net/ipv4/route.c#L1248">1248</a>         struct <a href="ident?i=fnhe_hash_bucket">fnhe_hash_bucket</a> *<a href="ident?i=hash">hash</a> = <a href="ident?i=rcu_dereference">rcu_dereference</a>(nh-&gt;nh_exceptions);
<a name="L1249" href="source/net/ipv4/route.c#L1249">1249</a>         struct <a href="ident?i=fib_nh_exception">fib_nh_exception</a> *fnhe;
<a name="L1250" href="source/net/ipv4/route.c#L1250">1250</a>         <a href="ident?i=u32">u32</a> hval;
<a name="L1251" href="source/net/ipv4/route.c#L1251">1251</a> 
<a name="L1252" href="source/net/ipv4/route.c#L1252">1252</a>         if (!<a href="ident?i=hash">hash</a>)
<a name="L1253" href="source/net/ipv4/route.c#L1253">1253</a>                 return <a href="ident?i=NULL">NULL</a>;
<a name="L1254" href="source/net/ipv4/route.c#L1254">1254</a> 
<a name="L1255" href="source/net/ipv4/route.c#L1255">1255</a>         hval = <a href="ident?i=fnhe_hashfun">fnhe_hashfun</a>(<a href="ident?i=daddr">daddr</a>);
<a name="L1256" href="source/net/ipv4/route.c#L1256">1256</a> 
<a name="L1257" href="source/net/ipv4/route.c#L1257">1257</a>         for (fnhe = <a href="ident?i=rcu_dereference">rcu_dereference</a>(<a href="ident?i=hash">hash</a>[hval].<a href="ident?i=chain">chain</a>); fnhe;
<a name="L1258" href="source/net/ipv4/route.c#L1258">1258</a>              fnhe = <a href="ident?i=rcu_dereference">rcu_dereference</a>(fnhe-&gt;fnhe_next)) {
<a name="L1259" href="source/net/ipv4/route.c#L1259">1259</a>                 if (fnhe-&gt;fnhe_daddr == <a href="ident?i=daddr">daddr</a>)
<a name="L1260" href="source/net/ipv4/route.c#L1260">1260</a>                         return fnhe;
<a name="L1261" href="source/net/ipv4/route.c#L1261">1261</a>         }
<a name="L1262" href="source/net/ipv4/route.c#L1262">1262</a>         return <a href="ident?i=NULL">NULL</a>;
<a name="L1263" href="source/net/ipv4/route.c#L1263">1263</a> }
<a name="L1264" href="source/net/ipv4/route.c#L1264">1264</a> 
<a name="L1265" href="source/net/ipv4/route.c#L1265">1265</a> static <a href="ident?i=bool">bool</a> <a href="ident?i=rt_bind_exception">rt_bind_exception</a>(struct <a href="ident?i=rtable">rtable</a> *<a href="ident?i=rt">rt</a>, struct <a href="ident?i=fib_nh_exception">fib_nh_exception</a> *fnhe,
<a name="L1266" href="source/net/ipv4/route.c#L1266">1266</a>                               <a href="ident?i=__be32">__be32</a> <a href="ident?i=daddr">daddr</a>)
<a name="L1267" href="source/net/ipv4/route.c#L1267">1267</a> {
<a name="L1268" href="source/net/ipv4/route.c#L1268">1268</a>         <a href="ident?i=bool">bool</a> <a href="ident?i=ret">ret</a> = <a href="ident?i=false">false</a>;
<a name="L1269" href="source/net/ipv4/route.c#L1269">1269</a> 
<a name="L1270" href="source/net/ipv4/route.c#L1270">1270</a>         <a href="ident?i=spin_lock_bh">spin_lock_bh</a>(&amp;fnhe_lock);
<a name="L1271" href="source/net/ipv4/route.c#L1271">1271</a> 
<a name="L1272" href="source/net/ipv4/route.c#L1272">1272</a>         if (<a href="ident?i=daddr">daddr</a> == fnhe-&gt;fnhe_daddr) {
<a name="L1273" href="source/net/ipv4/route.c#L1273">1273</a>                 struct <a href="ident?i=rtable">rtable</a> <a href="ident?i=__rcu">__rcu</a> **porig;
<a name="L1274" href="source/net/ipv4/route.c#L1274">1274</a>                 struct <a href="ident?i=rtable">rtable</a> *orig;
<a name="L1275" href="source/net/ipv4/route.c#L1275">1275</a>                 int genid = <a href="ident?i=fnhe_genid">fnhe_genid</a>(<a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>.<a href="ident?i=dev">dev</a>));
<a name="L1276" href="source/net/ipv4/route.c#L1276">1276</a> 
<a name="L1277" href="source/net/ipv4/route.c#L1277">1277</a>                 if (<a href="ident?i=rt_is_input_route">rt_is_input_route</a>(<a href="ident?i=rt">rt</a>))
<a name="L1278" href="source/net/ipv4/route.c#L1278">1278</a>                         porig = &amp;fnhe-&gt;fnhe_rth_input;
<a name="L1279" href="source/net/ipv4/route.c#L1279">1279</a>                 else
<a name="L1280" href="source/net/ipv4/route.c#L1280">1280</a>                         porig = &amp;fnhe-&gt;fnhe_rth_output;
<a name="L1281" href="source/net/ipv4/route.c#L1281">1281</a>                 orig = <a href="ident?i=rcu_dereference">rcu_dereference</a>(*porig);
<a name="L1282" href="source/net/ipv4/route.c#L1282">1282</a> 
<a name="L1283" href="source/net/ipv4/route.c#L1283">1283</a>                 if (fnhe-&gt;<a href="ident?i=fnhe_genid">fnhe_genid</a> != genid) {
<a name="L1284" href="source/net/ipv4/route.c#L1284">1284</a>                         fnhe-&gt;<a href="ident?i=fnhe_genid">fnhe_genid</a> = genid;
<a name="L1285" href="source/net/ipv4/route.c#L1285">1285</a>                         fnhe-&gt;fnhe_gw = 0;
<a name="L1286" href="source/net/ipv4/route.c#L1286">1286</a>                         fnhe-&gt;fnhe_pmtu = 0;
<a name="L1287" href="source/net/ipv4/route.c#L1287">1287</a>                         fnhe-&gt;fnhe_expires = 0;
<a name="L1288" href="source/net/ipv4/route.c#L1288">1288</a>                         <a href="ident?i=fnhe_flush_routes">fnhe_flush_routes</a>(fnhe);
<a name="L1289" href="source/net/ipv4/route.c#L1289">1289</a>                         orig = <a href="ident?i=NULL">NULL</a>;
<a name="L1290" href="source/net/ipv4/route.c#L1290">1290</a>                 }
<a name="L1291" href="source/net/ipv4/route.c#L1291">1291</a>                 <a href="ident?i=fill_route_from_fnhe">fill_route_from_fnhe</a>(<a href="ident?i=rt">rt</a>, fnhe);
<a name="L1292" href="source/net/ipv4/route.c#L1292">1292</a>                 if (!<a href="ident?i=rt">rt</a>-&gt;rt_gateway)
<a name="L1293" href="source/net/ipv4/route.c#L1293">1293</a>                         <a href="ident?i=rt">rt</a>-&gt;rt_gateway = <a href="ident?i=daddr">daddr</a>;
<a name="L1294" href="source/net/ipv4/route.c#L1294">1294</a> 
<a name="L1295" href="source/net/ipv4/route.c#L1295">1295</a>                 if (!(<a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>.<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=DST_NOCACHE">DST_NOCACHE</a>)) {
<a name="L1296" href="source/net/ipv4/route.c#L1296">1296</a>                         <a href="ident?i=rcu_assign_pointer">rcu_assign_pointer</a>(*porig, <a href="ident?i=rt">rt</a>);
<a name="L1297" href="source/net/ipv4/route.c#L1297">1297</a>                         if (orig)
<a name="L1298" href="source/net/ipv4/route.c#L1298">1298</a>                                 <a href="ident?i=rt_free">rt_free</a>(orig);
<a name="L1299" href="source/net/ipv4/route.c#L1299">1299</a>                         <a href="ident?i=ret">ret</a> = <a href="ident?i=true">true</a>;
<a name="L1300" href="source/net/ipv4/route.c#L1300">1300</a>                 }
<a name="L1301" href="source/net/ipv4/route.c#L1301">1301</a> 
<a name="L1302" href="source/net/ipv4/route.c#L1302">1302</a>                 fnhe-&gt;fnhe_stamp = <a href="ident?i=jiffies">jiffies</a>;
<a name="L1303" href="source/net/ipv4/route.c#L1303">1303</a>         }
<a name="L1304" href="source/net/ipv4/route.c#L1304">1304</a>         <a href="ident?i=spin_unlock_bh">spin_unlock_bh</a>(&amp;fnhe_lock);
<a name="L1305" href="source/net/ipv4/route.c#L1305">1305</a> 
<a name="L1306" href="source/net/ipv4/route.c#L1306">1306</a>         return <a href="ident?i=ret">ret</a>;
<a name="L1307" href="source/net/ipv4/route.c#L1307">1307</a> }
<a name="L1308" href="source/net/ipv4/route.c#L1308">1308</a> 
<a name="L1309" href="source/net/ipv4/route.c#L1309">1309</a> static <a href="ident?i=bool">bool</a> <a href="ident?i=rt_cache_route">rt_cache_route</a>(struct <a href="ident?i=fib_nh">fib_nh</a> *nh, struct <a href="ident?i=rtable">rtable</a> *<a href="ident?i=rt">rt</a>)
<a name="L1310" href="source/net/ipv4/route.c#L1310">1310</a> {
<a name="L1311" href="source/net/ipv4/route.c#L1311">1311</a>         struct <a href="ident?i=rtable">rtable</a> *orig, *prev, **<a href="ident?i=p">p</a>;
<a name="L1312" href="source/net/ipv4/route.c#L1312">1312</a>         <a href="ident?i=bool">bool</a> <a href="ident?i=ret">ret</a> = <a href="ident?i=true">true</a>;
<a name="L1313" href="source/net/ipv4/route.c#L1313">1313</a> 
<a name="L1314" href="source/net/ipv4/route.c#L1314">1314</a>         if (<a href="ident?i=rt_is_input_route">rt_is_input_route</a>(<a href="ident?i=rt">rt</a>)) {
<a name="L1315" href="source/net/ipv4/route.c#L1315">1315</a>                 <a href="ident?i=p">p</a> = (struct <a href="ident?i=rtable">rtable</a> **)&amp;nh-&gt;nh_rth_input;
<a name="L1316" href="source/net/ipv4/route.c#L1316">1316</a>         } else {
<a name="L1317" href="source/net/ipv4/route.c#L1317">1317</a>                 <a href="ident?i=p">p</a> = (struct <a href="ident?i=rtable">rtable</a> **)<a href="ident?i=raw_cpu_ptr">raw_cpu_ptr</a>(nh-&gt;nh_pcpu_rth_output);
<a name="L1318" href="source/net/ipv4/route.c#L1318">1318</a>         }
<a name="L1319" href="source/net/ipv4/route.c#L1319">1319</a>         orig = *<a href="ident?i=p">p</a>;
<a name="L1320" href="source/net/ipv4/route.c#L1320">1320</a> 
<a name="L1321" href="source/net/ipv4/route.c#L1321">1321</a>         prev = <a href="ident?i=cmpxchg">cmpxchg</a>(<a href="ident?i=p">p</a>, orig, <a href="ident?i=rt">rt</a>);
<a name="L1322" href="source/net/ipv4/route.c#L1322">1322</a>         if (prev == orig) {
<a name="L1323" href="source/net/ipv4/route.c#L1323">1323</a>                 if (orig)
<a name="L1324" href="source/net/ipv4/route.c#L1324">1324</a>                         <a href="ident?i=rt_free">rt_free</a>(orig);
<a name="L1325" href="source/net/ipv4/route.c#L1325">1325</a>         } else
<a name="L1326" href="source/net/ipv4/route.c#L1326">1326</a>                 <a href="ident?i=ret">ret</a> = <a href="ident?i=false">false</a>;
<a name="L1327" href="source/net/ipv4/route.c#L1327">1327</a> 
<a name="L1328" href="source/net/ipv4/route.c#L1328">1328</a>         return <a href="ident?i=ret">ret</a>;
<a name="L1329" href="source/net/ipv4/route.c#L1329">1329</a> }
<a name="L1330" href="source/net/ipv4/route.c#L1330">1330</a> 
<a name="L1331" href="source/net/ipv4/route.c#L1331">1331</a> struct <a href="ident?i=uncached_list">uncached_list</a> {
<a name="L1332" href="source/net/ipv4/route.c#L1332">1332</a>         <a href="ident?i=spinlock_t">spinlock_t</a>              <a href="ident?i=lock">lock</a>;
<a name="L1333" href="source/net/ipv4/route.c#L1333">1333</a>         struct <a href="ident?i=list_head">list_head</a>        <a href="ident?i=head">head</a>;
<a name="L1334" href="source/net/ipv4/route.c#L1334">1334</a> };
<a name="L1335" href="source/net/ipv4/route.c#L1335">1335</a> 
<a name="L1336" href="source/net/ipv4/route.c#L1336">1336</a> static <a href="ident?i=DEFINE_PER_CPU_ALIGNED">DEFINE_PER_CPU_ALIGNED</a>(struct <a href="ident?i=uncached_list">uncached_list</a>, rt_uncached_list);
<a name="L1337" href="source/net/ipv4/route.c#L1337">1337</a> 
<a name="L1338" href="source/net/ipv4/route.c#L1338">1338</a> static void <a href="ident?i=rt_add_uncached_list">rt_add_uncached_list</a>(struct <a href="ident?i=rtable">rtable</a> *<a href="ident?i=rt">rt</a>)
<a name="L1339" href="source/net/ipv4/route.c#L1339">1339</a> {
<a name="L1340" href="source/net/ipv4/route.c#L1340">1340</a>         struct <a href="ident?i=uncached_list">uncached_list</a> *ul = <a href="ident?i=raw_cpu_ptr">raw_cpu_ptr</a>(&amp;rt_uncached_list);
<a name="L1341" href="source/net/ipv4/route.c#L1341">1341</a> 
<a name="L1342" href="source/net/ipv4/route.c#L1342">1342</a>         <a href="ident?i=rt">rt</a>-&gt;rt_uncached_list = ul;
<a name="L1343" href="source/net/ipv4/route.c#L1343">1343</a> 
<a name="L1344" href="source/net/ipv4/route.c#L1344">1344</a>         <a href="ident?i=spin_lock_bh">spin_lock_bh</a>(&amp;ul-&gt;<a href="ident?i=lock">lock</a>);
<a name="L1345" href="source/net/ipv4/route.c#L1345">1345</a>         <a href="ident?i=list_add_tail">list_add_tail</a>(&amp;<a href="ident?i=rt">rt</a>-&gt;rt_uncached, &amp;ul-&gt;<a href="ident?i=head">head</a>);
<a name="L1346" href="source/net/ipv4/route.c#L1346">1346</a>         <a href="ident?i=spin_unlock_bh">spin_unlock_bh</a>(&amp;ul-&gt;<a href="ident?i=lock">lock</a>);
<a name="L1347" href="source/net/ipv4/route.c#L1347">1347</a> }
<a name="L1348" href="source/net/ipv4/route.c#L1348">1348</a> 
<a name="L1349" href="source/net/ipv4/route.c#L1349">1349</a> static void <a href="ident?i=ipv4_dst_destroy">ipv4_dst_destroy</a>(struct <a href="ident?i=dst_entry">dst_entry</a> *<a href="ident?i=dst">dst</a>)
<a name="L1350" href="source/net/ipv4/route.c#L1350">1350</a> {
<a name="L1351" href="source/net/ipv4/route.c#L1351">1351</a>         struct <a href="ident?i=rtable">rtable</a> *<a href="ident?i=rt">rt</a> = (struct <a href="ident?i=rtable">rtable</a> *) <a href="ident?i=dst">dst</a>;
<a name="L1352" href="source/net/ipv4/route.c#L1352">1352</a> 
<a name="L1353" href="source/net/ipv4/route.c#L1353">1353</a>         if (!<a href="ident?i=list_empty">list_empty</a>(&amp;<a href="ident?i=rt">rt</a>-&gt;rt_uncached)) {
<a name="L1354" href="source/net/ipv4/route.c#L1354">1354</a>                 struct <a href="ident?i=uncached_list">uncached_list</a> *ul = <a href="ident?i=rt">rt</a>-&gt;rt_uncached_list;
<a name="L1355" href="source/net/ipv4/route.c#L1355">1355</a> 
<a name="L1356" href="source/net/ipv4/route.c#L1356">1356</a>                 <a href="ident?i=spin_lock_bh">spin_lock_bh</a>(&amp;ul-&gt;<a href="ident?i=lock">lock</a>);
<a name="L1357" href="source/net/ipv4/route.c#L1357">1357</a>                 <a href="ident?i=list_del">list_del</a>(&amp;<a href="ident?i=rt">rt</a>-&gt;rt_uncached);
<a name="L1358" href="source/net/ipv4/route.c#L1358">1358</a>                 <a href="ident?i=spin_unlock_bh">spin_unlock_bh</a>(&amp;ul-&gt;<a href="ident?i=lock">lock</a>);
<a name="L1359" href="source/net/ipv4/route.c#L1359">1359</a>         }
<a name="L1360" href="source/net/ipv4/route.c#L1360">1360</a> }
<a name="L1361" href="source/net/ipv4/route.c#L1361">1361</a> 
<a name="L1362" href="source/net/ipv4/route.c#L1362">1362</a> void <a href="ident?i=rt_flush_dev">rt_flush_dev</a>(struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>)
<a name="L1363" href="source/net/ipv4/route.c#L1363">1363</a> {
<a name="L1364" href="source/net/ipv4/route.c#L1364">1364</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=dev">dev</a>);
<a name="L1365" href="source/net/ipv4/route.c#L1365">1365</a>         struct <a href="ident?i=rtable">rtable</a> *<a href="ident?i=rt">rt</a>;
<a name="L1366" href="source/net/ipv4/route.c#L1366">1366</a>         int <a href="ident?i=cpu">cpu</a>;
<a name="L1367" href="source/net/ipv4/route.c#L1367">1367</a> 
<a name="L1368" href="source/net/ipv4/route.c#L1368">1368</a>         <a href="ident?i=for_each_possible_cpu">for_each_possible_cpu</a>(<a href="ident?i=cpu">cpu</a>) {
<a name="L1369" href="source/net/ipv4/route.c#L1369">1369</a>                 struct <a href="ident?i=uncached_list">uncached_list</a> *ul = &amp;<a href="ident?i=per_cpu">per_cpu</a>(rt_uncached_list, <a href="ident?i=cpu">cpu</a>);
<a name="L1370" href="source/net/ipv4/route.c#L1370">1370</a> 
<a name="L1371" href="source/net/ipv4/route.c#L1371">1371</a>                 <a href="ident?i=spin_lock_bh">spin_lock_bh</a>(&amp;ul-&gt;<a href="ident?i=lock">lock</a>);
<a name="L1372" href="source/net/ipv4/route.c#L1372">1372</a>                 <a href="ident?i=list_for_each_entry">list_for_each_entry</a>(<a href="ident?i=rt">rt</a>, &amp;ul-&gt;<a href="ident?i=head">head</a>, rt_uncached) {
<a name="L1373" href="source/net/ipv4/route.c#L1373">1373</a>                         if (<a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>.<a href="ident?i=dev">dev</a> != <a href="ident?i=dev">dev</a>)
<a name="L1374" href="source/net/ipv4/route.c#L1374">1374</a>                                 continue;
<a name="L1375" href="source/net/ipv4/route.c#L1375">1375</a>                         <a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>.<a href="ident?i=dev">dev</a> = <a href="ident?i=net">net</a>-&gt;<a href="ident?i=loopback_dev">loopback_dev</a>;
<a name="L1376" href="source/net/ipv4/route.c#L1376">1376</a>                         <a href="ident?i=dev_hold">dev_hold</a>(<a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>.<a href="ident?i=dev">dev</a>);
<a name="L1377" href="source/net/ipv4/route.c#L1377">1377</a>                         <a href="ident?i=dev_put">dev_put</a>(<a href="ident?i=dev">dev</a>);
<a name="L1378" href="source/net/ipv4/route.c#L1378">1378</a>                 }
<a name="L1379" href="source/net/ipv4/route.c#L1379">1379</a>                 <a href="ident?i=spin_unlock_bh">spin_unlock_bh</a>(&amp;ul-&gt;<a href="ident?i=lock">lock</a>);
<a name="L1380" href="source/net/ipv4/route.c#L1380">1380</a>         }
<a name="L1381" href="source/net/ipv4/route.c#L1381">1381</a> }
<a name="L1382" href="source/net/ipv4/route.c#L1382">1382</a> 
<a name="L1383" href="source/net/ipv4/route.c#L1383">1383</a> static <a href="ident?i=bool">bool</a> <a href="ident?i=rt_cache_valid">rt_cache_valid</a>(const struct <a href="ident?i=rtable">rtable</a> *<a href="ident?i=rt">rt</a>)
<a name="L1384" href="source/net/ipv4/route.c#L1384">1384</a> {
<a name="L1385" href="source/net/ipv4/route.c#L1385">1385</a>         return  <a href="ident?i=rt">rt</a> &amp;&amp;
<a name="L1386" href="source/net/ipv4/route.c#L1386">1386</a>                 <a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>.obsolete == <a href="ident?i=DST_OBSOLETE_FORCE_CHK">DST_OBSOLETE_FORCE_CHK</a> &amp;&amp;
<a name="L1387" href="source/net/ipv4/route.c#L1387">1387</a>                 !<a href="ident?i=rt_is_expired">rt_is_expired</a>(<a href="ident?i=rt">rt</a>);
<a name="L1388" href="source/net/ipv4/route.c#L1388">1388</a> }
<a name="L1389" href="source/net/ipv4/route.c#L1389">1389</a> 
<a name="L1390" href="source/net/ipv4/route.c#L1390">1390</a> static void <a href="ident?i=rt_set_nexthop">rt_set_nexthop</a>(struct <a href="ident?i=rtable">rtable</a> *<a href="ident?i=rt">rt</a>, <a href="ident?i=__be32">__be32</a> <a href="ident?i=daddr">daddr</a>,
<a name="L1391" href="source/net/ipv4/route.c#L1391">1391</a>                            const struct <a href="ident?i=fib_result">fib_result</a> *<a href="ident?i=res">res</a>,
<a name="L1392" href="source/net/ipv4/route.c#L1392">1392</a>                            struct <a href="ident?i=fib_nh_exception">fib_nh_exception</a> *fnhe,
<a name="L1393" href="source/net/ipv4/route.c#L1393">1393</a>                            struct <a href="ident?i=fib_info">fib_info</a> *fi, <a href="ident?i=u16">u16</a> <a href="ident?i=type">type</a>, <a href="ident?i=u32">u32</a> itag)
<a name="L1394" href="source/net/ipv4/route.c#L1394">1394</a> {
<a name="L1395" href="source/net/ipv4/route.c#L1395">1395</a>         <a href="ident?i=bool">bool</a> <a href="ident?i=cached">cached</a> = <a href="ident?i=false">false</a>;
<a name="L1396" href="source/net/ipv4/route.c#L1396">1396</a> 
<a name="L1397" href="source/net/ipv4/route.c#L1397">1397</a>         if (fi) {
<a name="L1398" href="source/net/ipv4/route.c#L1398">1398</a>                 struct <a href="ident?i=fib_nh">fib_nh</a> *nh = &amp;<a href="ident?i=FIB_RES_NH">FIB_RES_NH</a>(*<a href="ident?i=res">res</a>);
<a name="L1399" href="source/net/ipv4/route.c#L1399">1399</a> 
<a name="L1400" href="source/net/ipv4/route.c#L1400">1400</a>                 if (nh-&gt;nh_gw &amp;&amp; nh-&gt;nh_scope == RT_SCOPE_LINK) {
<a name="L1401" href="source/net/ipv4/route.c#L1401">1401</a>                         <a href="ident?i=rt">rt</a>-&gt;rt_gateway = nh-&gt;nh_gw;
<a name="L1402" href="source/net/ipv4/route.c#L1402">1402</a>                         <a href="ident?i=rt">rt</a>-&gt;rt_uses_gateway = 1;
<a name="L1403" href="source/net/ipv4/route.c#L1403">1403</a>                 }
<a name="L1404" href="source/net/ipv4/route.c#L1404">1404</a>                 <a href="ident?i=dst_init_metrics">dst_init_metrics</a>(&amp;<a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>, fi-&gt;fib_metrics, <a href="ident?i=true">true</a>);
<a name="L1405" href="source/net/ipv4/route.c#L1405">1405</a> #ifdef CONFIG_IP_ROUTE_CLASSID
<a name="L1406" href="source/net/ipv4/route.c#L1406">1406</a>                 <a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>.tclassid = nh-&gt;nh_tclassid;
<a name="L1407" href="source/net/ipv4/route.c#L1407">1407</a> #endif
<a name="L1408" href="source/net/ipv4/route.c#L1408">1408</a>                 if (<a href="ident?i=unlikely">unlikely</a>(fnhe))
<a name="L1409" href="source/net/ipv4/route.c#L1409">1409</a>                         <a href="ident?i=cached">cached</a> = <a href="ident?i=rt_bind_exception">rt_bind_exception</a>(<a href="ident?i=rt">rt</a>, fnhe, <a href="ident?i=daddr">daddr</a>);
<a name="L1410" href="source/net/ipv4/route.c#L1410">1410</a>                 else if (!(<a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>.<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=DST_NOCACHE">DST_NOCACHE</a>))
<a name="L1411" href="source/net/ipv4/route.c#L1411">1411</a>                         <a href="ident?i=cached">cached</a> = <a href="ident?i=rt_cache_route">rt_cache_route</a>(nh, <a href="ident?i=rt">rt</a>);
<a name="L1412" href="source/net/ipv4/route.c#L1412">1412</a>                 if (<a href="ident?i=unlikely">unlikely</a>(!<a href="ident?i=cached">cached</a>)) {
<a name="L1413" href="source/net/ipv4/route.c#L1413">1413</a>                         <b><i>/* Routes we intend to cache in nexthop exception or</i></b>
<a name="L1414" href="source/net/ipv4/route.c#L1414">1414</a> <b><i>                         * FIB nexthop have the DST_NOCACHE bit clear.</i></b>
<a name="L1415" href="source/net/ipv4/route.c#L1415">1415</a> <b><i>                         * However, if we are unsuccessful at storing this</i></b>
<a name="L1416" href="source/net/ipv4/route.c#L1416">1416</a> <b><i>                         * route into the cache we really need to set it.</i></b>
<a name="L1417" href="source/net/ipv4/route.c#L1417">1417</a> <b><i>                         */</i></b>
<a name="L1418" href="source/net/ipv4/route.c#L1418">1418</a>                         <a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>.<a href="ident?i=flags">flags</a> |= <a href="ident?i=DST_NOCACHE">DST_NOCACHE</a>;
<a name="L1419" href="source/net/ipv4/route.c#L1419">1419</a>                         if (!<a href="ident?i=rt">rt</a>-&gt;rt_gateway)
<a name="L1420" href="source/net/ipv4/route.c#L1420">1420</a>                                 <a href="ident?i=rt">rt</a>-&gt;rt_gateway = <a href="ident?i=daddr">daddr</a>;
<a name="L1421" href="source/net/ipv4/route.c#L1421">1421</a>                         <a href="ident?i=rt_add_uncached_list">rt_add_uncached_list</a>(<a href="ident?i=rt">rt</a>);
<a name="L1422" href="source/net/ipv4/route.c#L1422">1422</a>                 }
<a name="L1423" href="source/net/ipv4/route.c#L1423">1423</a>         } else
<a name="L1424" href="source/net/ipv4/route.c#L1424">1424</a>                 <a href="ident?i=rt_add_uncached_list">rt_add_uncached_list</a>(<a href="ident?i=rt">rt</a>);
<a name="L1425" href="source/net/ipv4/route.c#L1425">1425</a> 
<a name="L1426" href="source/net/ipv4/route.c#L1426">1426</a> #ifdef CONFIG_IP_ROUTE_CLASSID
<a name="L1427" href="source/net/ipv4/route.c#L1427">1427</a> #ifdef CONFIG_IP_MULTIPLE_TABLES
<a name="L1428" href="source/net/ipv4/route.c#L1428">1428</a>         <a href="ident?i=set_class_tag">set_class_tag</a>(<a href="ident?i=rt">rt</a>, <a href="ident?i=res">res</a>-&gt;tclassid);
<a name="L1429" href="source/net/ipv4/route.c#L1429">1429</a> #endif
<a name="L1430" href="source/net/ipv4/route.c#L1430">1430</a>         <a href="ident?i=set_class_tag">set_class_tag</a>(<a href="ident?i=rt">rt</a>, itag);
<a name="L1431" href="source/net/ipv4/route.c#L1431">1431</a> #endif
<a name="L1432" href="source/net/ipv4/route.c#L1432">1432</a> }
<a name="L1433" href="source/net/ipv4/route.c#L1433">1433</a> 
<a name="L1434" href="source/net/ipv4/route.c#L1434">1434</a> static struct <a href="ident?i=rtable">rtable</a> *<a href="ident?i=rt_dst_alloc">rt_dst_alloc</a>(struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>,
<a name="L1435" href="source/net/ipv4/route.c#L1435">1435</a>                                    <a href="ident?i=bool">bool</a> nopolicy, <a href="ident?i=bool">bool</a> noxfrm, <a href="ident?i=bool">bool</a> will_cache)
<a name="L1436" href="source/net/ipv4/route.c#L1436">1436</a> {
<a name="L1437" href="source/net/ipv4/route.c#L1437">1437</a>         return <a href="ident?i=dst_alloc">dst_alloc</a>(&amp;<a href="ident?i=ipv4_dst_ops">ipv4_dst_ops</a>, <a href="ident?i=dev">dev</a>, 1, <a href="ident?i=DST_OBSOLETE_FORCE_CHK">DST_OBSOLETE_FORCE_CHK</a>,
<a name="L1438" href="source/net/ipv4/route.c#L1438">1438</a>                          (will_cache ? 0 : (<a href="ident?i=DST_HOST">DST_HOST</a> | <a href="ident?i=DST_NOCACHE">DST_NOCACHE</a>)) |
<a name="L1439" href="source/net/ipv4/route.c#L1439">1439</a>                          (nopolicy ? <a href="ident?i=DST_NOPOLICY">DST_NOPOLICY</a> : 0) |
<a name="L1440" href="source/net/ipv4/route.c#L1440">1440</a>                          (noxfrm ? <a href="ident?i=DST_NOXFRM">DST_NOXFRM</a> : 0));
<a name="L1441" href="source/net/ipv4/route.c#L1441">1441</a> }
<a name="L1442" href="source/net/ipv4/route.c#L1442">1442</a> 
<a name="L1443" href="source/net/ipv4/route.c#L1443">1443</a> <b><i>/* called in rcu_read_lock() section */</i></b>
<a name="L1444" href="source/net/ipv4/route.c#L1444">1444</a> static int <a href="ident?i=ip_route_input_mc">ip_route_input_mc</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, <a href="ident?i=__be32">__be32</a> <a href="ident?i=daddr">daddr</a>, <a href="ident?i=__be32">__be32</a> <a href="ident?i=saddr">saddr</a>,
<a name="L1445" href="source/net/ipv4/route.c#L1445">1445</a>                                 <a href="ident?i=u8">u8</a> tos, struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>, int our)
<a name="L1446" href="source/net/ipv4/route.c#L1446">1446</a> {
<a name="L1447" href="source/net/ipv4/route.c#L1447">1447</a>         struct <a href="ident?i=rtable">rtable</a> *rth;
<a name="L1448" href="source/net/ipv4/route.c#L1448">1448</a>         struct <a href="ident?i=in_device">in_device</a> *in_dev = <a href="ident?i=__in_dev_get_rcu">__in_dev_get_rcu</a>(<a href="ident?i=dev">dev</a>);
<a name="L1449" href="source/net/ipv4/route.c#L1449">1449</a>         <a href="ident?i=u32">u32</a> itag = 0;
<a name="L1450" href="source/net/ipv4/route.c#L1450">1450</a>         int <a href="ident?i=err">err</a>;
<a name="L1451" href="source/net/ipv4/route.c#L1451">1451</a> 
<a name="L1452" href="source/net/ipv4/route.c#L1452">1452</a>         <b><i>/* Primary sanity checks. */</i></b>
<a name="L1453" href="source/net/ipv4/route.c#L1453">1453</a> 
<a name="L1454" href="source/net/ipv4/route.c#L1454">1454</a>         if (!in_dev)
<a name="L1455" href="source/net/ipv4/route.c#L1455">1455</a>                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L1456" href="source/net/ipv4/route.c#L1456">1456</a> 
<a name="L1457" href="source/net/ipv4/route.c#L1457">1457</a>         if (<a href="ident?i=ipv4_is_multicast">ipv4_is_multicast</a>(<a href="ident?i=saddr">saddr</a>) || <a href="ident?i=ipv4_is_lbcast">ipv4_is_lbcast</a>(<a href="ident?i=saddr">saddr</a>) ||
<a name="L1458" href="source/net/ipv4/route.c#L1458">1458</a>             <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=protocol">protocol</a> != <a href="ident?i=htons">htons</a>(<a href="ident?i=ETH_P_IP">ETH_P_IP</a>))
<a name="L1459" href="source/net/ipv4/route.c#L1459">1459</a>                 goto e_inval;
<a name="L1460" href="source/net/ipv4/route.c#L1460">1460</a> 
<a name="L1461" href="source/net/ipv4/route.c#L1461">1461</a>         if (<a href="ident?i=likely">likely</a>(!<a href="ident?i=IN_DEV_ROUTE_LOCALNET">IN_DEV_ROUTE_LOCALNET</a>(in_dev)))
<a name="L1462" href="source/net/ipv4/route.c#L1462">1462</a>                 if (<a href="ident?i=ipv4_is_loopback">ipv4_is_loopback</a>(<a href="ident?i=saddr">saddr</a>))
<a name="L1463" href="source/net/ipv4/route.c#L1463">1463</a>                         goto e_inval;
<a name="L1464" href="source/net/ipv4/route.c#L1464">1464</a> 
<a name="L1465" href="source/net/ipv4/route.c#L1465">1465</a>         if (<a href="ident?i=ipv4_is_zeronet">ipv4_is_zeronet</a>(<a href="ident?i=saddr">saddr</a>)) {
<a name="L1466" href="source/net/ipv4/route.c#L1466">1466</a>                 if (!<a href="ident?i=ipv4_is_local_multicast">ipv4_is_local_multicast</a>(<a href="ident?i=daddr">daddr</a>))
<a name="L1467" href="source/net/ipv4/route.c#L1467">1467</a>                         goto e_inval;
<a name="L1468" href="source/net/ipv4/route.c#L1468">1468</a>         } else {
<a name="L1469" href="source/net/ipv4/route.c#L1469">1469</a>                 <a href="ident?i=err">err</a> = <a href="ident?i=fib_validate_source">fib_validate_source</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=saddr">saddr</a>, 0, tos, 0, <a href="ident?i=dev">dev</a>,
<a name="L1470" href="source/net/ipv4/route.c#L1470">1470</a>                                           in_dev, &amp;itag);
<a name="L1471" href="source/net/ipv4/route.c#L1471">1471</a>                 if (<a href="ident?i=err">err</a> &lt; 0)
<a name="L1472" href="source/net/ipv4/route.c#L1472">1472</a>                         goto <a href="ident?i=e_err">e_err</a>;
<a name="L1473" href="source/net/ipv4/route.c#L1473">1473</a>         }
<a name="L1474" href="source/net/ipv4/route.c#L1474">1474</a>         rth = <a href="ident?i=rt_dst_alloc">rt_dst_alloc</a>(<a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=dev">dev</a>)-&gt;<a href="ident?i=loopback_dev">loopback_dev</a>,
<a name="L1475" href="source/net/ipv4/route.c#L1475">1475</a>                            <a href="ident?i=IN_DEV_CONF_GET">IN_DEV_CONF_GET</a>(in_dev, NOPOLICY), <a href="ident?i=false">false</a>, <a href="ident?i=false">false</a>);
<a name="L1476" href="source/net/ipv4/route.c#L1476">1476</a>         if (!rth)
<a name="L1477" href="source/net/ipv4/route.c#L1477">1477</a>                 goto e_nobufs;
<a name="L1478" href="source/net/ipv4/route.c#L1478">1478</a> 
<a name="L1479" href="source/net/ipv4/route.c#L1479">1479</a> #ifdef CONFIG_IP_ROUTE_CLASSID
<a name="L1480" href="source/net/ipv4/route.c#L1480">1480</a>         rth-&gt;<a href="ident?i=dst">dst</a>.tclassid = itag;
<a name="L1481" href="source/net/ipv4/route.c#L1481">1481</a> #endif
<a name="L1482" href="source/net/ipv4/route.c#L1482">1482</a>         rth-&gt;<a href="ident?i=dst">dst</a>.<a href="ident?i=output">output</a> = <a href="ident?i=ip_rt_bug">ip_rt_bug</a>;
<a name="L1483" href="source/net/ipv4/route.c#L1483">1483</a> 
<a name="L1484" href="source/net/ipv4/route.c#L1484">1484</a>         rth-&gt;rt_genid   = <a href="ident?i=rt_genid_ipv4">rt_genid_ipv4</a>(<a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=dev">dev</a>));
<a name="L1485" href="source/net/ipv4/route.c#L1485">1485</a>         rth-&gt;rt_flags   = <a href="ident?i=RTCF_MULTICAST">RTCF_MULTICAST</a>;
<a name="L1486" href="source/net/ipv4/route.c#L1486">1486</a>         rth-&gt;rt_type    = RTN_MULTICAST;
<a name="L1487" href="source/net/ipv4/route.c#L1487">1487</a>         rth-&gt;rt_is_input= 1;
<a name="L1488" href="source/net/ipv4/route.c#L1488">1488</a>         rth-&gt;rt_iif     = 0;
<a name="L1489" href="source/net/ipv4/route.c#L1489">1489</a>         rth-&gt;rt_pmtu    = 0;
<a name="L1490" href="source/net/ipv4/route.c#L1490">1490</a>         rth-&gt;rt_gateway = 0;
<a name="L1491" href="source/net/ipv4/route.c#L1491">1491</a>         rth-&gt;rt_uses_gateway = 0;
<a name="L1492" href="source/net/ipv4/route.c#L1492">1492</a>         <a href="ident?i=INIT_LIST_HEAD">INIT_LIST_HEAD</a>(&amp;rth-&gt;rt_uncached);
<a name="L1493" href="source/net/ipv4/route.c#L1493">1493</a>         if (our) {
<a name="L1494" href="source/net/ipv4/route.c#L1494">1494</a>                 rth-&gt;<a href="ident?i=dst">dst</a>.<a href="ident?i=input">input</a>= <a href="ident?i=ip_local_deliver">ip_local_deliver</a>;
<a name="L1495" href="source/net/ipv4/route.c#L1495">1495</a>                 rth-&gt;rt_flags |= <a href="ident?i=RTCF_LOCAL">RTCF_LOCAL</a>;
<a name="L1496" href="source/net/ipv4/route.c#L1496">1496</a>         }
<a name="L1497" href="source/net/ipv4/route.c#L1497">1497</a> 
<a name="L1498" href="source/net/ipv4/route.c#L1498">1498</a> #ifdef CONFIG_IP_MROUTE
<a name="L1499" href="source/net/ipv4/route.c#L1499">1499</a>         if (!<a href="ident?i=ipv4_is_local_multicast">ipv4_is_local_multicast</a>(<a href="ident?i=daddr">daddr</a>) &amp;&amp; <a href="ident?i=IN_DEV_MFORWARD">IN_DEV_MFORWARD</a>(in_dev))
<a name="L1500" href="source/net/ipv4/route.c#L1500">1500</a>                 rth-&gt;<a href="ident?i=dst">dst</a>.<a href="ident?i=input">input</a> = <a href="ident?i=ip_mr_input">ip_mr_input</a>;
<a name="L1501" href="source/net/ipv4/route.c#L1501">1501</a> #endif
<a name="L1502" href="source/net/ipv4/route.c#L1502">1502</a>         <a href="ident?i=RT_CACHE_STAT_INC">RT_CACHE_STAT_INC</a>(in_slow_mc);
<a name="L1503" href="source/net/ipv4/route.c#L1503">1503</a> 
<a name="L1504" href="source/net/ipv4/route.c#L1504">1504</a>         <a href="ident?i=skb_dst_set">skb_dst_set</a>(<a href="ident?i=skb">skb</a>, &amp;rth-&gt;<a href="ident?i=dst">dst</a>);
<a name="L1505" href="source/net/ipv4/route.c#L1505">1505</a>         return 0;
<a name="L1506" href="source/net/ipv4/route.c#L1506">1506</a> 
<a name="L1507" href="source/net/ipv4/route.c#L1507">1507</a> e_nobufs:
<a name="L1508" href="source/net/ipv4/route.c#L1508">1508</a>         return -<a href="ident?i=ENOBUFS">ENOBUFS</a>;
<a name="L1509" href="source/net/ipv4/route.c#L1509">1509</a> e_inval:
<a name="L1510" href="source/net/ipv4/route.c#L1510">1510</a>         return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L1511" href="source/net/ipv4/route.c#L1511">1511</a> <a href="ident?i=e_err">e_err</a>:
<a name="L1512" href="source/net/ipv4/route.c#L1512">1512</a>         return <a href="ident?i=err">err</a>;
<a name="L1513" href="source/net/ipv4/route.c#L1513">1513</a> }
<a name="L1514" href="source/net/ipv4/route.c#L1514">1514</a> 
<a name="L1515" href="source/net/ipv4/route.c#L1515">1515</a> 
<a name="L1516" href="source/net/ipv4/route.c#L1516">1516</a> static void <a href="ident?i=ip_handle_martian_source">ip_handle_martian_source</a>(struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>,
<a name="L1517" href="source/net/ipv4/route.c#L1517">1517</a>                                      struct <a href="ident?i=in_device">in_device</a> *in_dev,
<a name="L1518" href="source/net/ipv4/route.c#L1518">1518</a>                                      struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
<a name="L1519" href="source/net/ipv4/route.c#L1519">1519</a>                                      <a href="ident?i=__be32">__be32</a> <a href="ident?i=daddr">daddr</a>,
<a name="L1520" href="source/net/ipv4/route.c#L1520">1520</a>                                      <a href="ident?i=__be32">__be32</a> <a href="ident?i=saddr">saddr</a>)
<a name="L1521" href="source/net/ipv4/route.c#L1521">1521</a> {
<a name="L1522" href="source/net/ipv4/route.c#L1522">1522</a>         <a href="ident?i=RT_CACHE_STAT_INC">RT_CACHE_STAT_INC</a>(in_martian_src);
<a name="L1523" href="source/net/ipv4/route.c#L1523">1523</a> #ifdef CONFIG_IP_ROUTE_VERBOSE
<a name="L1524" href="source/net/ipv4/route.c#L1524">1524</a>         if (<a href="ident?i=IN_DEV_LOG_MARTIANS">IN_DEV_LOG_MARTIANS</a>(in_dev) &amp;&amp; <a href="ident?i=net_ratelimit">net_ratelimit</a>()) {
<a name="L1525" href="source/net/ipv4/route.c#L1525">1525</a>                 <b><i>/*</i></b>
<a name="L1526" href="source/net/ipv4/route.c#L1526">1526</a> <b><i>                 *      RFC1812 recommendation, if source is martian,</i></b>
<a name="L1527" href="source/net/ipv4/route.c#L1527">1527</a> <b><i>                 *      the only hint is MAC header.</i></b>
<a name="L1528" href="source/net/ipv4/route.c#L1528">1528</a> <b><i>                 */</i></b>
<a name="L1529" href="source/net/ipv4/route.c#L1529">1529</a>                 <a href="ident?i=pr_warn">pr_warn</a>(<i>"martian source %pI4 from %pI4, on dev %s\n"</i>,
<a name="L1530" href="source/net/ipv4/route.c#L1530">1530</a>                         &amp;<a href="ident?i=daddr">daddr</a>, &amp;<a href="ident?i=saddr">saddr</a>, <a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=name">name</a>);
<a name="L1531" href="source/net/ipv4/route.c#L1531">1531</a>                 if (<a href="ident?i=dev">dev</a>-&gt;hard_header_len &amp;&amp; <a href="ident?i=skb_mac_header_was_set">skb_mac_header_was_set</a>(<a href="ident?i=skb">skb</a>)) {
<a name="L1532" href="source/net/ipv4/route.c#L1532">1532</a>                         <a href="ident?i=print_hex_dump">print_hex_dump</a>(<a href="ident?i=KERN_WARNING">KERN_WARNING</a>, <i>"ll header: "</i>,
<a name="L1533" href="source/net/ipv4/route.c#L1533">1533</a>                                        DUMP_PREFIX_OFFSET, 16, 1,
<a name="L1534" href="source/net/ipv4/route.c#L1534">1534</a>                                        <a href="ident?i=skb_mac_header">skb_mac_header</a>(<a href="ident?i=skb">skb</a>),
<a name="L1535" href="source/net/ipv4/route.c#L1535">1535</a>                                        <a href="ident?i=dev">dev</a>-&gt;hard_header_len, <a href="ident?i=true">true</a>);
<a name="L1536" href="source/net/ipv4/route.c#L1536">1536</a>                 }
<a name="L1537" href="source/net/ipv4/route.c#L1537">1537</a>         }
<a name="L1538" href="source/net/ipv4/route.c#L1538">1538</a> #endif
<a name="L1539" href="source/net/ipv4/route.c#L1539">1539</a> }
<a name="L1540" href="source/net/ipv4/route.c#L1540">1540</a> 
<a name="L1541" href="source/net/ipv4/route.c#L1541">1541</a> <b><i>/* called in rcu_read_lock() section */</i></b>
<a name="L1542" href="source/net/ipv4/route.c#L1542">1542</a> static int <a href="ident?i=__mkroute_input">__mkroute_input</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
<a name="L1543" href="source/net/ipv4/route.c#L1543">1543</a>                            const struct <a href="ident?i=fib_result">fib_result</a> *<a href="ident?i=res">res</a>,
<a name="L1544" href="source/net/ipv4/route.c#L1544">1544</a>                            struct <a href="ident?i=in_device">in_device</a> *in_dev,
<a name="L1545" href="source/net/ipv4/route.c#L1545">1545</a>                            <a href="ident?i=__be32">__be32</a> <a href="ident?i=daddr">daddr</a>, <a href="ident?i=__be32">__be32</a> <a href="ident?i=saddr">saddr</a>, <a href="ident?i=u32">u32</a> tos)
<a name="L1546" href="source/net/ipv4/route.c#L1546">1546</a> {
<a name="L1547" href="source/net/ipv4/route.c#L1547">1547</a>         struct <a href="ident?i=fib_nh_exception">fib_nh_exception</a> *fnhe;
<a name="L1548" href="source/net/ipv4/route.c#L1548">1548</a>         struct <a href="ident?i=rtable">rtable</a> *rth;
<a name="L1549" href="source/net/ipv4/route.c#L1549">1549</a>         int <a href="ident?i=err">err</a>;
<a name="L1550" href="source/net/ipv4/route.c#L1550">1550</a>         struct <a href="ident?i=in_device">in_device</a> *out_dev;
<a name="L1551" href="source/net/ipv4/route.c#L1551">1551</a>         unsigned int <a href="ident?i=flags">flags</a> = 0;
<a name="L1552" href="source/net/ipv4/route.c#L1552">1552</a>         <a href="ident?i=bool">bool</a> do_cache;
<a name="L1553" href="source/net/ipv4/route.c#L1553">1553</a>         <a href="ident?i=u32">u32</a> itag = 0;
<a name="L1554" href="source/net/ipv4/route.c#L1554">1554</a> 
<a name="L1555" href="source/net/ipv4/route.c#L1555">1555</a>         <b><i>/* get a working reference to the output device */</i></b>
<a name="L1556" href="source/net/ipv4/route.c#L1556">1556</a>         out_dev = <a href="ident?i=__in_dev_get_rcu">__in_dev_get_rcu</a>(<a href="ident?i=FIB_RES_DEV">FIB_RES_DEV</a>(*<a href="ident?i=res">res</a>));
<a name="L1557" href="source/net/ipv4/route.c#L1557">1557</a>         if (!out_dev) {
<a name="L1558" href="source/net/ipv4/route.c#L1558">1558</a>                 <a href="ident?i=net_crit_ratelimited">net_crit_ratelimited</a>(<i>"Bug in ip_route_input_slow(). Please report.\n"</i>);
<a name="L1559" href="source/net/ipv4/route.c#L1559">1559</a>                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L1560" href="source/net/ipv4/route.c#L1560">1560</a>         }
<a name="L1561" href="source/net/ipv4/route.c#L1561">1561</a> 
<a name="L1562" href="source/net/ipv4/route.c#L1562">1562</a>         <a href="ident?i=err">err</a> = <a href="ident?i=fib_validate_source">fib_validate_source</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=saddr">saddr</a>, <a href="ident?i=daddr">daddr</a>, tos, <a href="ident?i=FIB_RES_OIF">FIB_RES_OIF</a>(*<a href="ident?i=res">res</a>),
<a name="L1563" href="source/net/ipv4/route.c#L1563">1563</a>                                   in_dev-&gt;<a href="ident?i=dev">dev</a>, in_dev, &amp;itag);
<a name="L1564" href="source/net/ipv4/route.c#L1564">1564</a>         if (<a href="ident?i=err">err</a> &lt; 0) {
<a name="L1565" href="source/net/ipv4/route.c#L1565">1565</a>                 <a href="ident?i=ip_handle_martian_source">ip_handle_martian_source</a>(in_dev-&gt;<a href="ident?i=dev">dev</a>, in_dev, <a href="ident?i=skb">skb</a>, <a href="ident?i=daddr">daddr</a>,
<a name="L1566" href="source/net/ipv4/route.c#L1566">1566</a>                                          <a href="ident?i=saddr">saddr</a>);
<a name="L1567" href="source/net/ipv4/route.c#L1567">1567</a> 
<a name="L1568" href="source/net/ipv4/route.c#L1568">1568</a>                 goto <a href="ident?i=cleanup">cleanup</a>;
<a name="L1569" href="source/net/ipv4/route.c#L1569">1569</a>         }
<a name="L1570" href="source/net/ipv4/route.c#L1570">1570</a> 
<a name="L1571" href="source/net/ipv4/route.c#L1571">1571</a>         do_cache = <a href="ident?i=res">res</a>-&gt;fi &amp;&amp; !itag;
<a name="L1572" href="source/net/ipv4/route.c#L1572">1572</a>         if (out_dev == in_dev &amp;&amp; <a href="ident?i=err">err</a> &amp;&amp; <a href="ident?i=IN_DEV_TX_REDIRECTS">IN_DEV_TX_REDIRECTS</a>(out_dev) &amp;&amp;
<a name="L1573" href="source/net/ipv4/route.c#L1573">1573</a>             <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=protocol">protocol</a> == <a href="ident?i=htons">htons</a>(<a href="ident?i=ETH_P_IP">ETH_P_IP</a>) &amp;&amp;
<a name="L1574" href="source/net/ipv4/route.c#L1574">1574</a>             (<a href="ident?i=IN_DEV_SHARED_MEDIA">IN_DEV_SHARED_MEDIA</a>(out_dev) ||
<a name="L1575" href="source/net/ipv4/route.c#L1575">1575</a>              <a href="ident?i=inet_addr_onlink">inet_addr_onlink</a>(out_dev, <a href="ident?i=saddr">saddr</a>, <a href="ident?i=FIB_RES_GW">FIB_RES_GW</a>(*<a href="ident?i=res">res</a>))))
<a name="L1576" href="source/net/ipv4/route.c#L1576">1576</a>                 <a href="ident?i=IPCB">IPCB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=flags">flags</a> |= <a href="ident?i=IPSKB_DOREDIRECT">IPSKB_DOREDIRECT</a>;
<a name="L1577" href="source/net/ipv4/route.c#L1577">1577</a> 
<a name="L1578" href="source/net/ipv4/route.c#L1578">1578</a>         if (<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=protocol">protocol</a> != <a href="ident?i=htons">htons</a>(<a href="ident?i=ETH_P_IP">ETH_P_IP</a>)) {
<a name="L1579" href="source/net/ipv4/route.c#L1579">1579</a>                 <b><i>/* Not IP (i.e. ARP). Do not create route, if it is</i></b>
<a name="L1580" href="source/net/ipv4/route.c#L1580">1580</a> <b><i>                 * invalid for proxy arp. DNAT routes are always valid.</i></b>
<a name="L1581" href="source/net/ipv4/route.c#L1581">1581</a> <b><i>                 *</i></b>
<a name="L1582" href="source/net/ipv4/route.c#L1582">1582</a> <b><i>                 * Proxy arp feature have been extended to allow, ARP</i></b>
<a name="L1583" href="source/net/ipv4/route.c#L1583">1583</a> <b><i>                 * replies back to the same interface, to support</i></b>
<a name="L1584" href="source/net/ipv4/route.c#L1584">1584</a> <b><i>                 * Private VLAN switch technologies. See arp.c.</i></b>
<a name="L1585" href="source/net/ipv4/route.c#L1585">1585</a> <b><i>                 */</i></b>
<a name="L1586" href="source/net/ipv4/route.c#L1586">1586</a>                 if (out_dev == in_dev &amp;&amp;
<a name="L1587" href="source/net/ipv4/route.c#L1587">1587</a>                     <a href="ident?i=IN_DEV_PROXY_ARP_PVLAN">IN_DEV_PROXY_ARP_PVLAN</a>(in_dev) == 0) {
<a name="L1588" href="source/net/ipv4/route.c#L1588">1588</a>                         <a href="ident?i=err">err</a> = -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L1589" href="source/net/ipv4/route.c#L1589">1589</a>                         goto <a href="ident?i=cleanup">cleanup</a>;
<a name="L1590" href="source/net/ipv4/route.c#L1590">1590</a>                 }
<a name="L1591" href="source/net/ipv4/route.c#L1591">1591</a>         }
<a name="L1592" href="source/net/ipv4/route.c#L1592">1592</a> 
<a name="L1593" href="source/net/ipv4/route.c#L1593">1593</a>         fnhe = <a href="ident?i=find_exception">find_exception</a>(&amp;<a href="ident?i=FIB_RES_NH">FIB_RES_NH</a>(*<a href="ident?i=res">res</a>), <a href="ident?i=daddr">daddr</a>);
<a name="L1594" href="source/net/ipv4/route.c#L1594">1594</a>         if (do_cache) {
<a name="L1595" href="source/net/ipv4/route.c#L1595">1595</a>                 if (fnhe)
<a name="L1596" href="source/net/ipv4/route.c#L1596">1596</a>                         rth = <a href="ident?i=rcu_dereference">rcu_dereference</a>(fnhe-&gt;fnhe_rth_input);
<a name="L1597" href="source/net/ipv4/route.c#L1597">1597</a>                 else
<a name="L1598" href="source/net/ipv4/route.c#L1598">1598</a>                         rth = <a href="ident?i=rcu_dereference">rcu_dereference</a>(<a href="ident?i=FIB_RES_NH">FIB_RES_NH</a>(*<a href="ident?i=res">res</a>).nh_rth_input);
<a name="L1599" href="source/net/ipv4/route.c#L1599">1599</a> 
<a name="L1600" href="source/net/ipv4/route.c#L1600">1600</a>                 if (<a href="ident?i=rt_cache_valid">rt_cache_valid</a>(rth)) {
<a name="L1601" href="source/net/ipv4/route.c#L1601">1601</a>                         <a href="ident?i=skb_dst_set_noref">skb_dst_set_noref</a>(<a href="ident?i=skb">skb</a>, &amp;rth-&gt;<a href="ident?i=dst">dst</a>);
<a name="L1602" href="source/net/ipv4/route.c#L1602">1602</a>                         goto <a href="ident?i=out">out</a>;
<a name="L1603" href="source/net/ipv4/route.c#L1603">1603</a>                 }
<a name="L1604" href="source/net/ipv4/route.c#L1604">1604</a>         }
<a name="L1605" href="source/net/ipv4/route.c#L1605">1605</a> 
<a name="L1606" href="source/net/ipv4/route.c#L1606">1606</a>         rth = <a href="ident?i=rt_dst_alloc">rt_dst_alloc</a>(out_dev-&gt;<a href="ident?i=dev">dev</a>,
<a name="L1607" href="source/net/ipv4/route.c#L1607">1607</a>                            <a href="ident?i=IN_DEV_CONF_GET">IN_DEV_CONF_GET</a>(in_dev, NOPOLICY),
<a name="L1608" href="source/net/ipv4/route.c#L1608">1608</a>                            <a href="ident?i=IN_DEV_CONF_GET">IN_DEV_CONF_GET</a>(out_dev, NOXFRM), do_cache);
<a name="L1609" href="source/net/ipv4/route.c#L1609">1609</a>         if (!rth) {
<a name="L1610" href="source/net/ipv4/route.c#L1610">1610</a>                 <a href="ident?i=err">err</a> = -<a href="ident?i=ENOBUFS">ENOBUFS</a>;
<a name="L1611" href="source/net/ipv4/route.c#L1611">1611</a>                 goto <a href="ident?i=cleanup">cleanup</a>;
<a name="L1612" href="source/net/ipv4/route.c#L1612">1612</a>         }
<a name="L1613" href="source/net/ipv4/route.c#L1613">1613</a> 
<a name="L1614" href="source/net/ipv4/route.c#L1614">1614</a>         rth-&gt;rt_genid = <a href="ident?i=rt_genid_ipv4">rt_genid_ipv4</a>(<a href="ident?i=dev_net">dev_net</a>(rth-&gt;<a href="ident?i=dst">dst</a>.<a href="ident?i=dev">dev</a>));
<a name="L1615" href="source/net/ipv4/route.c#L1615">1615</a>         rth-&gt;rt_flags = <a href="ident?i=flags">flags</a>;
<a name="L1616" href="source/net/ipv4/route.c#L1616">1616</a>         rth-&gt;rt_type = <a href="ident?i=res">res</a>-&gt;<a href="ident?i=type">type</a>;
<a name="L1617" href="source/net/ipv4/route.c#L1617">1617</a>         rth-&gt;rt_is_input = 1;
<a name="L1618" href="source/net/ipv4/route.c#L1618">1618</a>         rth-&gt;rt_iif     = 0;
<a name="L1619" href="source/net/ipv4/route.c#L1619">1619</a>         rth-&gt;rt_pmtu    = 0;
<a name="L1620" href="source/net/ipv4/route.c#L1620">1620</a>         rth-&gt;rt_gateway = 0;
<a name="L1621" href="source/net/ipv4/route.c#L1621">1621</a>         rth-&gt;rt_uses_gateway = 0;
<a name="L1622" href="source/net/ipv4/route.c#L1622">1622</a>         <a href="ident?i=INIT_LIST_HEAD">INIT_LIST_HEAD</a>(&amp;rth-&gt;rt_uncached);
<a name="L1623" href="source/net/ipv4/route.c#L1623">1623</a>         <a href="ident?i=RT_CACHE_STAT_INC">RT_CACHE_STAT_INC</a>(in_slow_tot);
<a name="L1624" href="source/net/ipv4/route.c#L1624">1624</a> 
<a name="L1625" href="source/net/ipv4/route.c#L1625">1625</a>         rth-&gt;<a href="ident?i=dst">dst</a>.<a href="ident?i=input">input</a> = <a href="ident?i=ip_forward">ip_forward</a>;
<a name="L1626" href="source/net/ipv4/route.c#L1626">1626</a>         rth-&gt;<a href="ident?i=dst">dst</a>.<a href="ident?i=output">output</a> = <a href="ident?i=ip_output">ip_output</a>;
<a name="L1627" href="source/net/ipv4/route.c#L1627">1627</a> 
<a name="L1628" href="source/net/ipv4/route.c#L1628">1628</a>         <a href="ident?i=rt_set_nexthop">rt_set_nexthop</a>(rth, <a href="ident?i=daddr">daddr</a>, <a href="ident?i=res">res</a>, fnhe, <a href="ident?i=res">res</a>-&gt;fi, <a href="ident?i=res">res</a>-&gt;<a href="ident?i=type">type</a>, itag);
<a name="L1629" href="source/net/ipv4/route.c#L1629">1629</a>         <a href="ident?i=skb_dst_set">skb_dst_set</a>(<a href="ident?i=skb">skb</a>, &amp;rth-&gt;<a href="ident?i=dst">dst</a>);
<a name="L1630" href="source/net/ipv4/route.c#L1630">1630</a> <a href="ident?i=out">out</a>:
<a name="L1631" href="source/net/ipv4/route.c#L1631">1631</a>         <a href="ident?i=err">err</a> = 0;
<a name="L1632" href="source/net/ipv4/route.c#L1632">1632</a>  <a href="ident?i=cleanup">cleanup</a>:
<a name="L1633" href="source/net/ipv4/route.c#L1633">1633</a>         return <a href="ident?i=err">err</a>;
<a name="L1634" href="source/net/ipv4/route.c#L1634">1634</a> }
<a name="L1635" href="source/net/ipv4/route.c#L1635">1635</a> 
<a name="L1636" href="source/net/ipv4/route.c#L1636">1636</a> static int <a href="ident?i=ip_mkroute_input">ip_mkroute_input</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
<a name="L1637" href="source/net/ipv4/route.c#L1637">1637</a>                             struct <a href="ident?i=fib_result">fib_result</a> *<a href="ident?i=res">res</a>,
<a name="L1638" href="source/net/ipv4/route.c#L1638">1638</a>                             const struct <a href="ident?i=flowi4">flowi4</a> *fl4,
<a name="L1639" href="source/net/ipv4/route.c#L1639">1639</a>                             struct <a href="ident?i=in_device">in_device</a> *in_dev,
<a name="L1640" href="source/net/ipv4/route.c#L1640">1640</a>                             <a href="ident?i=__be32">__be32</a> <a href="ident?i=daddr">daddr</a>, <a href="ident?i=__be32">__be32</a> <a href="ident?i=saddr">saddr</a>, <a href="ident?i=u32">u32</a> tos)
<a name="L1641" href="source/net/ipv4/route.c#L1641">1641</a> {
<a name="L1642" href="source/net/ipv4/route.c#L1642">1642</a> #ifdef CONFIG_IP_ROUTE_MULTIPATH
<a name="L1643" href="source/net/ipv4/route.c#L1643">1643</a>         if (<a href="ident?i=res">res</a>-&gt;fi &amp;&amp; <a href="ident?i=res">res</a>-&gt;fi-&gt;fib_nhs &gt; 1)
<a name="L1644" href="source/net/ipv4/route.c#L1644">1644</a>                 <a href="ident?i=fib_select_multipath">fib_select_multipath</a>(<a href="ident?i=res">res</a>);
<a name="L1645" href="source/net/ipv4/route.c#L1645">1645</a> #endif
<a name="L1646" href="source/net/ipv4/route.c#L1646">1646</a> 
<a name="L1647" href="source/net/ipv4/route.c#L1647">1647</a>         <b><i>/* create a routing cache entry */</i></b>
<a name="L1648" href="source/net/ipv4/route.c#L1648">1648</a>         return <a href="ident?i=__mkroute_input">__mkroute_input</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=res">res</a>, in_dev, <a href="ident?i=daddr">daddr</a>, <a href="ident?i=saddr">saddr</a>, tos);
<a name="L1649" href="source/net/ipv4/route.c#L1649">1649</a> }
<a name="L1650" href="source/net/ipv4/route.c#L1650">1650</a> 
<a name="L1651" href="source/net/ipv4/route.c#L1651">1651</a> <b><i>/*</i></b>
<a name="L1652" href="source/net/ipv4/route.c#L1652">1652</a> <b><i> *      NOTE. We drop all the packets that has local source</i></b>
<a name="L1653" href="source/net/ipv4/route.c#L1653">1653</a> <b><i> *      addresses, because every properly looped back packet</i></b>
<a name="L1654" href="source/net/ipv4/route.c#L1654">1654</a> <b><i> *      must have correct destination already attached by output routine.</i></b>
<a name="L1655" href="source/net/ipv4/route.c#L1655">1655</a> <b><i> *</i></b>
<a name="L1656" href="source/net/ipv4/route.c#L1656">1656</a> <b><i> *      Such approach solves two big problems:</i></b>
<a name="L1657" href="source/net/ipv4/route.c#L1657">1657</a> <b><i> *      1. Not simplex devices are handled properly.</i></b>
<a name="L1658" href="source/net/ipv4/route.c#L1658">1658</a> <b><i> *      2. IP spoofing attempts are filtered with 100% of guarantee.</i></b>
<a name="L1659" href="source/net/ipv4/route.c#L1659">1659</a> <b><i> *      called with rcu_read_lock()</i></b>
<a name="L1660" href="source/net/ipv4/route.c#L1660">1660</a> <b><i> */</i></b>
<a name="L1661" href="source/net/ipv4/route.c#L1661">1661</a> 
<a name="L1662" href="source/net/ipv4/route.c#L1662">1662</a> static int <a href="ident?i=ip_route_input_slow">ip_route_input_slow</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, <a href="ident?i=__be32">__be32</a> <a href="ident?i=daddr">daddr</a>, <a href="ident?i=__be32">__be32</a> <a href="ident?i=saddr">saddr</a>,
<a name="L1663" href="source/net/ipv4/route.c#L1663">1663</a>                                <a href="ident?i=u8">u8</a> tos, struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>)
<a name="L1664" href="source/net/ipv4/route.c#L1664">1664</a> {
<a name="L1665" href="source/net/ipv4/route.c#L1665">1665</a>         struct <a href="ident?i=fib_result">fib_result</a> <a href="ident?i=res">res</a>;
<a name="L1666" href="source/net/ipv4/route.c#L1666">1666</a>         struct <a href="ident?i=in_device">in_device</a> *in_dev = <a href="ident?i=__in_dev_get_rcu">__in_dev_get_rcu</a>(<a href="ident?i=dev">dev</a>);
<a name="L1667" href="source/net/ipv4/route.c#L1667">1667</a>         struct <a href="ident?i=flowi4">flowi4</a>   fl4;
<a name="L1668" href="source/net/ipv4/route.c#L1668">1668</a>         unsigned int    <a href="ident?i=flags">flags</a> = 0;
<a name="L1669" href="source/net/ipv4/route.c#L1669">1669</a>         <a href="ident?i=u32">u32</a>             itag = 0;
<a name="L1670" href="source/net/ipv4/route.c#L1670">1670</a>         struct <a href="ident?i=rtable">rtable</a>   *rth;
<a name="L1671" href="source/net/ipv4/route.c#L1671">1671</a>         int             <a href="ident?i=err">err</a> = -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L1672" href="source/net/ipv4/route.c#L1672">1672</a>         struct <a href="ident?i=net">net</a>    *<a href="ident?i=net">net</a> = <a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=dev">dev</a>);
<a name="L1673" href="source/net/ipv4/route.c#L1673">1673</a>         <a href="ident?i=bool">bool</a> do_cache;
<a name="L1674" href="source/net/ipv4/route.c#L1674">1674</a> 
<a name="L1675" href="source/net/ipv4/route.c#L1675">1675</a>         <b><i>/* IP on this device is disabled. */</i></b>
<a name="L1676" href="source/net/ipv4/route.c#L1676">1676</a> 
<a name="L1677" href="source/net/ipv4/route.c#L1677">1677</a>         if (!in_dev)
<a name="L1678" href="source/net/ipv4/route.c#L1678">1678</a>                 goto <a href="ident?i=out">out</a>;
<a name="L1679" href="source/net/ipv4/route.c#L1679">1679</a> 
<a name="L1680" href="source/net/ipv4/route.c#L1680">1680</a>         <b><i>/* Check for the most weird martians, which can be not detected</i></b>
<a name="L1681" href="source/net/ipv4/route.c#L1681">1681</a> <b><i>           by fib_lookup.</i></b>
<a name="L1682" href="source/net/ipv4/route.c#L1682">1682</a> <b><i>         */</i></b>
<a name="L1683" href="source/net/ipv4/route.c#L1683">1683</a> 
<a name="L1684" href="source/net/ipv4/route.c#L1684">1684</a>         if (<a href="ident?i=ipv4_is_multicast">ipv4_is_multicast</a>(<a href="ident?i=saddr">saddr</a>) || <a href="ident?i=ipv4_is_lbcast">ipv4_is_lbcast</a>(<a href="ident?i=saddr">saddr</a>))
<a name="L1685" href="source/net/ipv4/route.c#L1685">1685</a>                 goto martian_source;
<a name="L1686" href="source/net/ipv4/route.c#L1686">1686</a> 
<a name="L1687" href="source/net/ipv4/route.c#L1687">1687</a>         <a href="ident?i=res">res</a>.fi = <a href="ident?i=NULL">NULL</a>;
<a name="L1688" href="source/net/ipv4/route.c#L1688">1688</a>         if (<a href="ident?i=ipv4_is_lbcast">ipv4_is_lbcast</a>(<a href="ident?i=daddr">daddr</a>) || (<a href="ident?i=saddr">saddr</a> == 0 &amp;&amp; <a href="ident?i=daddr">daddr</a> == 0))
<a name="L1689" href="source/net/ipv4/route.c#L1689">1689</a>                 goto brd_input;
<a name="L1690" href="source/net/ipv4/route.c#L1690">1690</a> 
<a name="L1691" href="source/net/ipv4/route.c#L1691">1691</a>         <b><i>/* Accept zero addresses only to limited broadcast;</i></b>
<a name="L1692" href="source/net/ipv4/route.c#L1692">1692</a> <b><i>         * I even do not know to fix it or not. Waiting for complains :-)</i></b>
<a name="L1693" href="source/net/ipv4/route.c#L1693">1693</a> <b><i>         */</i></b>
<a name="L1694" href="source/net/ipv4/route.c#L1694">1694</a>         if (<a href="ident?i=ipv4_is_zeronet">ipv4_is_zeronet</a>(<a href="ident?i=saddr">saddr</a>))
<a name="L1695" href="source/net/ipv4/route.c#L1695">1695</a>                 goto martian_source;
<a name="L1696" href="source/net/ipv4/route.c#L1696">1696</a> 
<a name="L1697" href="source/net/ipv4/route.c#L1697">1697</a>         if (<a href="ident?i=ipv4_is_zeronet">ipv4_is_zeronet</a>(<a href="ident?i=daddr">daddr</a>))
<a name="L1698" href="source/net/ipv4/route.c#L1698">1698</a>                 goto martian_destination;
<a name="L1699" href="source/net/ipv4/route.c#L1699">1699</a> 
<a name="L1700" href="source/net/ipv4/route.c#L1700">1700</a>         <b><i>/* Following code try to avoid calling IN_DEV_NET_ROUTE_LOCALNET(),</i></b>
<a name="L1701" href="source/net/ipv4/route.c#L1701">1701</a> <b><i>         * and call it once if daddr or/and saddr are loopback addresses</i></b>
<a name="L1702" href="source/net/ipv4/route.c#L1702">1702</a> <b><i>         */</i></b>
<a name="L1703" href="source/net/ipv4/route.c#L1703">1703</a>         if (<a href="ident?i=ipv4_is_loopback">ipv4_is_loopback</a>(<a href="ident?i=daddr">daddr</a>)) {
<a name="L1704" href="source/net/ipv4/route.c#L1704">1704</a>                 if (!<a href="ident?i=IN_DEV_NET_ROUTE_LOCALNET">IN_DEV_NET_ROUTE_LOCALNET</a>(in_dev, <a href="ident?i=net">net</a>))
<a name="L1705" href="source/net/ipv4/route.c#L1705">1705</a>                         goto martian_destination;
<a name="L1706" href="source/net/ipv4/route.c#L1706">1706</a>         } else if (<a href="ident?i=ipv4_is_loopback">ipv4_is_loopback</a>(<a href="ident?i=saddr">saddr</a>)) {
<a name="L1707" href="source/net/ipv4/route.c#L1707">1707</a>                 if (!<a href="ident?i=IN_DEV_NET_ROUTE_LOCALNET">IN_DEV_NET_ROUTE_LOCALNET</a>(in_dev, <a href="ident?i=net">net</a>))
<a name="L1708" href="source/net/ipv4/route.c#L1708">1708</a>                         goto martian_source;
<a name="L1709" href="source/net/ipv4/route.c#L1709">1709</a>         }
<a name="L1710" href="source/net/ipv4/route.c#L1710">1710</a> 
<a name="L1711" href="source/net/ipv4/route.c#L1711">1711</a>         <b><i>/*</i></b>
<a name="L1712" href="source/net/ipv4/route.c#L1712">1712</a> <b><i>         *      Now we are ready to route packet.</i></b>
<a name="L1713" href="source/net/ipv4/route.c#L1713">1713</a> <b><i>         */</i></b>
<a name="L1714" href="source/net/ipv4/route.c#L1714">1714</a>         fl4.<a href="ident?i=flowi4_oif">flowi4_oif</a> = 0;
<a name="L1715" href="source/net/ipv4/route.c#L1715">1715</a>         fl4.<a href="ident?i=flowi4_iif">flowi4_iif</a> = <a href="ident?i=dev">dev</a>-&gt;ifindex;
<a name="L1716" href="source/net/ipv4/route.c#L1716">1716</a>         fl4.<a href="ident?i=flowi4_mark">flowi4_mark</a> = <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=mark">mark</a>;
<a name="L1717" href="source/net/ipv4/route.c#L1717">1717</a>         fl4.<a href="ident?i=flowi4_tos">flowi4_tos</a> = tos;
<a name="L1718" href="source/net/ipv4/route.c#L1718">1718</a>         fl4.<a href="ident?i=flowi4_scope">flowi4_scope</a> = RT_SCOPE_UNIVERSE;
<a name="L1719" href="source/net/ipv4/route.c#L1719">1719</a>         fl4.<a href="ident?i=daddr">daddr</a> = <a href="ident?i=daddr">daddr</a>;
<a name="L1720" href="source/net/ipv4/route.c#L1720">1720</a>         fl4.<a href="ident?i=saddr">saddr</a> = <a href="ident?i=saddr">saddr</a>;
<a name="L1721" href="source/net/ipv4/route.c#L1721">1721</a>         <a href="ident?i=err">err</a> = <a href="ident?i=fib_lookup">fib_lookup</a>(<a href="ident?i=net">net</a>, &amp;fl4, &amp;<a href="ident?i=res">res</a>);
<a name="L1722" href="source/net/ipv4/route.c#L1722">1722</a>         if (<a href="ident?i=err">err</a> != 0) {
<a name="L1723" href="source/net/ipv4/route.c#L1723">1723</a>                 if (!<a href="ident?i=IN_DEV_FORWARD">IN_DEV_FORWARD</a>(in_dev))
<a name="L1724" href="source/net/ipv4/route.c#L1724">1724</a>                         <a href="ident?i=err">err</a> = -<a href="ident?i=EHOSTUNREACH">EHOSTUNREACH</a>;
<a name="L1725" href="source/net/ipv4/route.c#L1725">1725</a>                 goto no_route;
<a name="L1726" href="source/net/ipv4/route.c#L1726">1726</a>         }
<a name="L1727" href="source/net/ipv4/route.c#L1727">1727</a> 
<a name="L1728" href="source/net/ipv4/route.c#L1728">1728</a>         if (<a href="ident?i=res">res</a>.<a href="ident?i=type">type</a> == RTN_BROADCAST)
<a name="L1729" href="source/net/ipv4/route.c#L1729">1729</a>                 goto brd_input;
<a name="L1730" href="source/net/ipv4/route.c#L1730">1730</a> 
<a name="L1731" href="source/net/ipv4/route.c#L1731">1731</a>         if (<a href="ident?i=res">res</a>.<a href="ident?i=type">type</a> == RTN_LOCAL) {
<a name="L1732" href="source/net/ipv4/route.c#L1732">1732</a>                 <a href="ident?i=err">err</a> = <a href="ident?i=fib_validate_source">fib_validate_source</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=saddr">saddr</a>, <a href="ident?i=daddr">daddr</a>, tos,
<a name="L1733" href="source/net/ipv4/route.c#L1733">1733</a>                                           0, <a href="ident?i=dev">dev</a>, in_dev, &amp;itag);
<a name="L1734" href="source/net/ipv4/route.c#L1734">1734</a>                 if (<a href="ident?i=err">err</a> &lt; 0)
<a name="L1735" href="source/net/ipv4/route.c#L1735">1735</a>                         goto martian_source_keep_err;
<a name="L1736" href="source/net/ipv4/route.c#L1736">1736</a>                 goto local_input;
<a name="L1737" href="source/net/ipv4/route.c#L1737">1737</a>         }
<a name="L1738" href="source/net/ipv4/route.c#L1738">1738</a> 
<a name="L1739" href="source/net/ipv4/route.c#L1739">1739</a>         if (!<a href="ident?i=IN_DEV_FORWARD">IN_DEV_FORWARD</a>(in_dev)) {
<a name="L1740" href="source/net/ipv4/route.c#L1740">1740</a>                 <a href="ident?i=err">err</a> = -<a href="ident?i=EHOSTUNREACH">EHOSTUNREACH</a>;
<a name="L1741" href="source/net/ipv4/route.c#L1741">1741</a>                 goto no_route;
<a name="L1742" href="source/net/ipv4/route.c#L1742">1742</a>         }
<a name="L1743" href="source/net/ipv4/route.c#L1743">1743</a>         if (<a href="ident?i=res">res</a>.<a href="ident?i=type">type</a> != RTN_UNICAST)
<a name="L1744" href="source/net/ipv4/route.c#L1744">1744</a>                 goto martian_destination;
<a name="L1745" href="source/net/ipv4/route.c#L1745">1745</a> 
<a name="L1746" href="source/net/ipv4/route.c#L1746">1746</a>         <a href="ident?i=err">err</a> = <a href="ident?i=ip_mkroute_input">ip_mkroute_input</a>(<a href="ident?i=skb">skb</a>, &amp;<a href="ident?i=res">res</a>, &amp;fl4, in_dev, <a href="ident?i=daddr">daddr</a>, <a href="ident?i=saddr">saddr</a>, tos);
<a name="L1747" href="source/net/ipv4/route.c#L1747">1747</a> <a href="ident?i=out">out</a>:    return <a href="ident?i=err">err</a>;
<a name="L1748" href="source/net/ipv4/route.c#L1748">1748</a> 
<a name="L1749" href="source/net/ipv4/route.c#L1749">1749</a> brd_input:
<a name="L1750" href="source/net/ipv4/route.c#L1750">1750</a>         if (<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=protocol">protocol</a> != <a href="ident?i=htons">htons</a>(<a href="ident?i=ETH_P_IP">ETH_P_IP</a>))
<a name="L1751" href="source/net/ipv4/route.c#L1751">1751</a>                 goto e_inval;
<a name="L1752" href="source/net/ipv4/route.c#L1752">1752</a> 
<a name="L1753" href="source/net/ipv4/route.c#L1753">1753</a>         if (!<a href="ident?i=ipv4_is_zeronet">ipv4_is_zeronet</a>(<a href="ident?i=saddr">saddr</a>)) {
<a name="L1754" href="source/net/ipv4/route.c#L1754">1754</a>                 <a href="ident?i=err">err</a> = <a href="ident?i=fib_validate_source">fib_validate_source</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=saddr">saddr</a>, 0, tos, 0, <a href="ident?i=dev">dev</a>,
<a name="L1755" href="source/net/ipv4/route.c#L1755">1755</a>                                           in_dev, &amp;itag);
<a name="L1756" href="source/net/ipv4/route.c#L1756">1756</a>                 if (<a href="ident?i=err">err</a> &lt; 0)
<a name="L1757" href="source/net/ipv4/route.c#L1757">1757</a>                         goto martian_source_keep_err;
<a name="L1758" href="source/net/ipv4/route.c#L1758">1758</a>         }
<a name="L1759" href="source/net/ipv4/route.c#L1759">1759</a>         <a href="ident?i=flags">flags</a> |= <a href="ident?i=RTCF_BROADCAST">RTCF_BROADCAST</a>;
<a name="L1760" href="source/net/ipv4/route.c#L1760">1760</a>         <a href="ident?i=res">res</a>.<a href="ident?i=type">type</a> = RTN_BROADCAST;
<a name="L1761" href="source/net/ipv4/route.c#L1761">1761</a>         <a href="ident?i=RT_CACHE_STAT_INC">RT_CACHE_STAT_INC</a>(in_brd);
<a name="L1762" href="source/net/ipv4/route.c#L1762">1762</a> 
<a name="L1763" href="source/net/ipv4/route.c#L1763">1763</a> local_input:
<a name="L1764" href="source/net/ipv4/route.c#L1764">1764</a>         do_cache = <a href="ident?i=false">false</a>;
<a name="L1765" href="source/net/ipv4/route.c#L1765">1765</a>         if (<a href="ident?i=res">res</a>.fi) {
<a name="L1766" href="source/net/ipv4/route.c#L1766">1766</a>                 if (!itag) {
<a name="L1767" href="source/net/ipv4/route.c#L1767">1767</a>                         rth = <a href="ident?i=rcu_dereference">rcu_dereference</a>(<a href="ident?i=FIB_RES_NH">FIB_RES_NH</a>(<a href="ident?i=res">res</a>).nh_rth_input);
<a name="L1768" href="source/net/ipv4/route.c#L1768">1768</a>                         if (<a href="ident?i=rt_cache_valid">rt_cache_valid</a>(rth)) {
<a name="L1769" href="source/net/ipv4/route.c#L1769">1769</a>                                 <a href="ident?i=skb_dst_set_noref">skb_dst_set_noref</a>(<a href="ident?i=skb">skb</a>, &amp;rth-&gt;<a href="ident?i=dst">dst</a>);
<a name="L1770" href="source/net/ipv4/route.c#L1770">1770</a>                                 <a href="ident?i=err">err</a> = 0;
<a name="L1771" href="source/net/ipv4/route.c#L1771">1771</a>                                 goto <a href="ident?i=out">out</a>;
<a name="L1772" href="source/net/ipv4/route.c#L1772">1772</a>                         }
<a name="L1773" href="source/net/ipv4/route.c#L1773">1773</a>                         do_cache = <a href="ident?i=true">true</a>;
<a name="L1774" href="source/net/ipv4/route.c#L1774">1774</a>                 }
<a name="L1775" href="source/net/ipv4/route.c#L1775">1775</a>         }
<a name="L1776" href="source/net/ipv4/route.c#L1776">1776</a> 
<a name="L1777" href="source/net/ipv4/route.c#L1777">1777</a>         rth = <a href="ident?i=rt_dst_alloc">rt_dst_alloc</a>(<a href="ident?i=net">net</a>-&gt;<a href="ident?i=loopback_dev">loopback_dev</a>,
<a name="L1778" href="source/net/ipv4/route.c#L1778">1778</a>                            <a href="ident?i=IN_DEV_CONF_GET">IN_DEV_CONF_GET</a>(in_dev, NOPOLICY), <a href="ident?i=false">false</a>, do_cache);
<a name="L1779" href="source/net/ipv4/route.c#L1779">1779</a>         if (!rth)
<a name="L1780" href="source/net/ipv4/route.c#L1780">1780</a>                 goto e_nobufs;
<a name="L1781" href="source/net/ipv4/route.c#L1781">1781</a> 
<a name="L1782" href="source/net/ipv4/route.c#L1782">1782</a>         rth-&gt;<a href="ident?i=dst">dst</a>.<a href="ident?i=input">input</a>= <a href="ident?i=ip_local_deliver">ip_local_deliver</a>;
<a name="L1783" href="source/net/ipv4/route.c#L1783">1783</a>         rth-&gt;<a href="ident?i=dst">dst</a>.<a href="ident?i=output">output</a>= <a href="ident?i=ip_rt_bug">ip_rt_bug</a>;
<a name="L1784" href="source/net/ipv4/route.c#L1784">1784</a> #ifdef CONFIG_IP_ROUTE_CLASSID
<a name="L1785" href="source/net/ipv4/route.c#L1785">1785</a>         rth-&gt;<a href="ident?i=dst">dst</a>.tclassid = itag;
<a name="L1786" href="source/net/ipv4/route.c#L1786">1786</a> #endif
<a name="L1787" href="source/net/ipv4/route.c#L1787">1787</a> 
<a name="L1788" href="source/net/ipv4/route.c#L1788">1788</a>         rth-&gt;rt_genid = <a href="ident?i=rt_genid_ipv4">rt_genid_ipv4</a>(<a href="ident?i=net">net</a>);
<a name="L1789" href="source/net/ipv4/route.c#L1789">1789</a>         rth-&gt;rt_flags   = <a href="ident?i=flags">flags</a>|<a href="ident?i=RTCF_LOCAL">RTCF_LOCAL</a>;
<a name="L1790" href="source/net/ipv4/route.c#L1790">1790</a>         rth-&gt;rt_type    = <a href="ident?i=res">res</a>.<a href="ident?i=type">type</a>;
<a name="L1791" href="source/net/ipv4/route.c#L1791">1791</a>         rth-&gt;rt_is_input = 1;
<a name="L1792" href="source/net/ipv4/route.c#L1792">1792</a>         rth-&gt;rt_iif     = 0;
<a name="L1793" href="source/net/ipv4/route.c#L1793">1793</a>         rth-&gt;rt_pmtu    = 0;
<a name="L1794" href="source/net/ipv4/route.c#L1794">1794</a>         rth-&gt;rt_gateway = 0;
<a name="L1795" href="source/net/ipv4/route.c#L1795">1795</a>         rth-&gt;rt_uses_gateway = 0;
<a name="L1796" href="source/net/ipv4/route.c#L1796">1796</a>         <a href="ident?i=INIT_LIST_HEAD">INIT_LIST_HEAD</a>(&amp;rth-&gt;rt_uncached);
<a name="L1797" href="source/net/ipv4/route.c#L1797">1797</a>         <a href="ident?i=RT_CACHE_STAT_INC">RT_CACHE_STAT_INC</a>(in_slow_tot);
<a name="L1798" href="source/net/ipv4/route.c#L1798">1798</a>         if (<a href="ident?i=res">res</a>.<a href="ident?i=type">type</a> == RTN_UNREACHABLE) {
<a name="L1799" href="source/net/ipv4/route.c#L1799">1799</a>                 rth-&gt;<a href="ident?i=dst">dst</a>.<a href="ident?i=input">input</a>= <a href="ident?i=ip_error">ip_error</a>;
<a name="L1800" href="source/net/ipv4/route.c#L1800">1800</a>                 rth-&gt;<a href="ident?i=dst">dst</a>.<a href="ident?i=error">error</a>= -<a href="ident?i=err">err</a>;
<a name="L1801" href="source/net/ipv4/route.c#L1801">1801</a>                 rth-&gt;rt_flags   &amp;= ~RTCF_LOCAL;
<a name="L1802" href="source/net/ipv4/route.c#L1802">1802</a>         }
<a name="L1803" href="source/net/ipv4/route.c#L1803">1803</a>         if (do_cache) {
<a name="L1804" href="source/net/ipv4/route.c#L1804">1804</a>                 if (<a href="ident?i=unlikely">unlikely</a>(!<a href="ident?i=rt_cache_route">rt_cache_route</a>(&amp;<a href="ident?i=FIB_RES_NH">FIB_RES_NH</a>(<a href="ident?i=res">res</a>), rth))) {
<a name="L1805" href="source/net/ipv4/route.c#L1805">1805</a>                         rth-&gt;<a href="ident?i=dst">dst</a>.<a href="ident?i=flags">flags</a> |= <a href="ident?i=DST_NOCACHE">DST_NOCACHE</a>;
<a name="L1806" href="source/net/ipv4/route.c#L1806">1806</a>                         <a href="ident?i=rt_add_uncached_list">rt_add_uncached_list</a>(rth);
<a name="L1807" href="source/net/ipv4/route.c#L1807">1807</a>                 }
<a name="L1808" href="source/net/ipv4/route.c#L1808">1808</a>         }
<a name="L1809" href="source/net/ipv4/route.c#L1809">1809</a>         <a href="ident?i=skb_dst_set">skb_dst_set</a>(<a href="ident?i=skb">skb</a>, &amp;rth-&gt;<a href="ident?i=dst">dst</a>);
<a name="L1810" href="source/net/ipv4/route.c#L1810">1810</a>         <a href="ident?i=err">err</a> = 0;
<a name="L1811" href="source/net/ipv4/route.c#L1811">1811</a>         goto <a href="ident?i=out">out</a>;
<a name="L1812" href="source/net/ipv4/route.c#L1812">1812</a> 
<a name="L1813" href="source/net/ipv4/route.c#L1813">1813</a> no_route:
<a name="L1814" href="source/net/ipv4/route.c#L1814">1814</a>         <a href="ident?i=RT_CACHE_STAT_INC">RT_CACHE_STAT_INC</a>(in_no_route);
<a name="L1815" href="source/net/ipv4/route.c#L1815">1815</a>         <a href="ident?i=res">res</a>.<a href="ident?i=type">type</a> = RTN_UNREACHABLE;
<a name="L1816" href="source/net/ipv4/route.c#L1816">1816</a>         <a href="ident?i=res">res</a>.fi = <a href="ident?i=NULL">NULL</a>;
<a name="L1817" href="source/net/ipv4/route.c#L1817">1817</a>         goto local_input;
<a name="L1818" href="source/net/ipv4/route.c#L1818">1818</a> 
<a name="L1819" href="source/net/ipv4/route.c#L1819">1819</a>         <b><i>/*</i></b>
<a name="L1820" href="source/net/ipv4/route.c#L1820">1820</a> <b><i>         *      Do not cache martian addresses: they should be logged (RFC1812)</i></b>
<a name="L1821" href="source/net/ipv4/route.c#L1821">1821</a> <b><i>         */</i></b>
<a name="L1822" href="source/net/ipv4/route.c#L1822">1822</a> martian_destination:
<a name="L1823" href="source/net/ipv4/route.c#L1823">1823</a>         <a href="ident?i=RT_CACHE_STAT_INC">RT_CACHE_STAT_INC</a>(in_martian_dst);
<a name="L1824" href="source/net/ipv4/route.c#L1824">1824</a> #ifdef CONFIG_IP_ROUTE_VERBOSE
<a name="L1825" href="source/net/ipv4/route.c#L1825">1825</a>         if (<a href="ident?i=IN_DEV_LOG_MARTIANS">IN_DEV_LOG_MARTIANS</a>(in_dev))
<a name="L1826" href="source/net/ipv4/route.c#L1826">1826</a>                 <a href="ident?i=net_warn_ratelimited">net_warn_ratelimited</a>(<i>"martian destination %pI4 from %pI4, dev %s\n"</i>,
<a name="L1827" href="source/net/ipv4/route.c#L1827">1827</a>                                      &amp;<a href="ident?i=daddr">daddr</a>, &amp;<a href="ident?i=saddr">saddr</a>, <a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=name">name</a>);
<a name="L1828" href="source/net/ipv4/route.c#L1828">1828</a> #endif
<a name="L1829" href="source/net/ipv4/route.c#L1829">1829</a> 
<a name="L1830" href="source/net/ipv4/route.c#L1830">1830</a> e_inval:
<a name="L1831" href="source/net/ipv4/route.c#L1831">1831</a>         <a href="ident?i=err">err</a> = -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L1832" href="source/net/ipv4/route.c#L1832">1832</a>         goto <a href="ident?i=out">out</a>;
<a name="L1833" href="source/net/ipv4/route.c#L1833">1833</a> 
<a name="L1834" href="source/net/ipv4/route.c#L1834">1834</a> e_nobufs:
<a name="L1835" href="source/net/ipv4/route.c#L1835">1835</a>         <a href="ident?i=err">err</a> = -<a href="ident?i=ENOBUFS">ENOBUFS</a>;
<a name="L1836" href="source/net/ipv4/route.c#L1836">1836</a>         goto <a href="ident?i=out">out</a>;
<a name="L1837" href="source/net/ipv4/route.c#L1837">1837</a> 
<a name="L1838" href="source/net/ipv4/route.c#L1838">1838</a> martian_source:
<a name="L1839" href="source/net/ipv4/route.c#L1839">1839</a>         <a href="ident?i=err">err</a> = -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L1840" href="source/net/ipv4/route.c#L1840">1840</a> martian_source_keep_err:
<a name="L1841" href="source/net/ipv4/route.c#L1841">1841</a>         <a href="ident?i=ip_handle_martian_source">ip_handle_martian_source</a>(<a href="ident?i=dev">dev</a>, in_dev, <a href="ident?i=skb">skb</a>, <a href="ident?i=daddr">daddr</a>, <a href="ident?i=saddr">saddr</a>);
<a name="L1842" href="source/net/ipv4/route.c#L1842">1842</a>         goto <a href="ident?i=out">out</a>;
<a name="L1843" href="source/net/ipv4/route.c#L1843">1843</a> }
<a name="L1844" href="source/net/ipv4/route.c#L1844">1844</a> 
<a name="L1845" href="source/net/ipv4/route.c#L1845">1845</a> int <a href="ident?i=ip_route_input_noref">ip_route_input_noref</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, <a href="ident?i=__be32">__be32</a> <a href="ident?i=daddr">daddr</a>, <a href="ident?i=__be32">__be32</a> <a href="ident?i=saddr">saddr</a>,
<a name="L1846" href="source/net/ipv4/route.c#L1846">1846</a>                          <a href="ident?i=u8">u8</a> tos, struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>)
<a name="L1847" href="source/net/ipv4/route.c#L1847">1847</a> {
<a name="L1848" href="source/net/ipv4/route.c#L1848">1848</a>         int <a href="ident?i=res">res</a>;
<a name="L1849" href="source/net/ipv4/route.c#L1849">1849</a> 
<a name="L1850" href="source/net/ipv4/route.c#L1850">1850</a>         <a href="ident?i=rcu_read_lock">rcu_read_lock</a>();
<a name="L1851" href="source/net/ipv4/route.c#L1851">1851</a> 
<a name="L1852" href="source/net/ipv4/route.c#L1852">1852</a>         <b><i>/* Multicast recognition logic is moved from route cache to here.</i></b>
<a name="L1853" href="source/net/ipv4/route.c#L1853">1853</a> <b><i>           The problem was that too many Ethernet cards have broken/missing</i></b>
<a name="L1854" href="source/net/ipv4/route.c#L1854">1854</a> <b><i>           hardware multicast filters :-( As result the host on multicasting</i></b>
<a name="L1855" href="source/net/ipv4/route.c#L1855">1855</a> <b><i>           network acquires a lot of useless route cache entries, sort of</i></b>
<a name="L1856" href="source/net/ipv4/route.c#L1856">1856</a> <b><i>           SDR messages from all the world. Now we try to get rid of them.</i></b>
<a name="L1857" href="source/net/ipv4/route.c#L1857">1857</a> <b><i>           Really, provided software IP multicast filter is organized</i></b>
<a name="L1858" href="source/net/ipv4/route.c#L1858">1858</a> <b><i>           reasonably (at least, hashed), it does not result in a slowdown</i></b>
<a name="L1859" href="source/net/ipv4/route.c#L1859">1859</a> <b><i>           comparing with route cache reject entries.</i></b>
<a name="L1860" href="source/net/ipv4/route.c#L1860">1860</a> <b><i>           Note, that multicast routers are not affected, because</i></b>
<a name="L1861" href="source/net/ipv4/route.c#L1861">1861</a> <b><i>           route cache entry is created eventually.</i></b>
<a name="L1862" href="source/net/ipv4/route.c#L1862">1862</a> <b><i>         */</i></b>
<a name="L1863" href="source/net/ipv4/route.c#L1863">1863</a>         if (<a href="ident?i=ipv4_is_multicast">ipv4_is_multicast</a>(<a href="ident?i=daddr">daddr</a>)) {
<a name="L1864" href="source/net/ipv4/route.c#L1864">1864</a>                 struct <a href="ident?i=in_device">in_device</a> *in_dev = <a href="ident?i=__in_dev_get_rcu">__in_dev_get_rcu</a>(<a href="ident?i=dev">dev</a>);
<a name="L1865" href="source/net/ipv4/route.c#L1865">1865</a> 
<a name="L1866" href="source/net/ipv4/route.c#L1866">1866</a>                 if (in_dev) {
<a name="L1867" href="source/net/ipv4/route.c#L1867">1867</a>                         int our = <a href="ident?i=ip_check_mc_rcu">ip_check_mc_rcu</a>(in_dev, <a href="ident?i=daddr">daddr</a>, <a href="ident?i=saddr">saddr</a>,
<a name="L1868" href="source/net/ipv4/route.c#L1868">1868</a>                                                   <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=protocol">protocol</a>);
<a name="L1869" href="source/net/ipv4/route.c#L1869">1869</a>                         if (our
<a name="L1870" href="source/net/ipv4/route.c#L1870">1870</a> #ifdef CONFIG_IP_MROUTE
<a name="L1871" href="source/net/ipv4/route.c#L1871">1871</a>                                 ||
<a name="L1872" href="source/net/ipv4/route.c#L1872">1872</a>                             (!<a href="ident?i=ipv4_is_local_multicast">ipv4_is_local_multicast</a>(<a href="ident?i=daddr">daddr</a>) &amp;&amp;
<a name="L1873" href="source/net/ipv4/route.c#L1873">1873</a>                              <a href="ident?i=IN_DEV_MFORWARD">IN_DEV_MFORWARD</a>(in_dev))
<a name="L1874" href="source/net/ipv4/route.c#L1874">1874</a> #endif
<a name="L1875" href="source/net/ipv4/route.c#L1875">1875</a>                            ) {
<a name="L1876" href="source/net/ipv4/route.c#L1876">1876</a>                                 int <a href="ident?i=res">res</a> = <a href="ident?i=ip_route_input_mc">ip_route_input_mc</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=daddr">daddr</a>, <a href="ident?i=saddr">saddr</a>,
<a name="L1877" href="source/net/ipv4/route.c#L1877">1877</a>                                                             tos, <a href="ident?i=dev">dev</a>, our);
<a name="L1878" href="source/net/ipv4/route.c#L1878">1878</a>                                 <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L1879" href="source/net/ipv4/route.c#L1879">1879</a>                                 return <a href="ident?i=res">res</a>;
<a name="L1880" href="source/net/ipv4/route.c#L1880">1880</a>                         }
<a name="L1881" href="source/net/ipv4/route.c#L1881">1881</a>                 }
<a name="L1882" href="source/net/ipv4/route.c#L1882">1882</a>                 <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L1883" href="source/net/ipv4/route.c#L1883">1883</a>                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L1884" href="source/net/ipv4/route.c#L1884">1884</a>         }
<a name="L1885" href="source/net/ipv4/route.c#L1885">1885</a>         <a href="ident?i=res">res</a> = <a href="ident?i=ip_route_input_slow">ip_route_input_slow</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=daddr">daddr</a>, <a href="ident?i=saddr">saddr</a>, tos, <a href="ident?i=dev">dev</a>);
<a name="L1886" href="source/net/ipv4/route.c#L1886">1886</a>         <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L1887" href="source/net/ipv4/route.c#L1887">1887</a>         return <a href="ident?i=res">res</a>;
<a name="L1888" href="source/net/ipv4/route.c#L1888">1888</a> }
<a name="L1889" href="source/net/ipv4/route.c#L1889">1889</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=ip_route_input_noref">ip_route_input_noref</a>);
<a name="L1890" href="source/net/ipv4/route.c#L1890">1890</a> 
<a name="L1891" href="source/net/ipv4/route.c#L1891">1891</a> <b><i>/* called with rcu_read_lock() */</i></b>
<a name="L1892" href="source/net/ipv4/route.c#L1892">1892</a> static struct <a href="ident?i=rtable">rtable</a> *<a href="ident?i=__mkroute_output">__mkroute_output</a>(const struct <a href="ident?i=fib_result">fib_result</a> *<a href="ident?i=res">res</a>,
<a name="L1893" href="source/net/ipv4/route.c#L1893">1893</a>                                        const struct <a href="ident?i=flowi4">flowi4</a> *fl4, int orig_oif,
<a name="L1894" href="source/net/ipv4/route.c#L1894">1894</a>                                        struct <a href="ident?i=net_device">net_device</a> *dev_out,
<a name="L1895" href="source/net/ipv4/route.c#L1895">1895</a>                                        unsigned int <a href="ident?i=flags">flags</a>)
<a name="L1896" href="source/net/ipv4/route.c#L1896">1896</a> {
<a name="L1897" href="source/net/ipv4/route.c#L1897">1897</a>         struct <a href="ident?i=fib_info">fib_info</a> *fi = <a href="ident?i=res">res</a>-&gt;fi;
<a name="L1898" href="source/net/ipv4/route.c#L1898">1898</a>         struct <a href="ident?i=fib_nh_exception">fib_nh_exception</a> *fnhe;
<a name="L1899" href="source/net/ipv4/route.c#L1899">1899</a>         struct <a href="ident?i=in_device">in_device</a> *in_dev;
<a name="L1900" href="source/net/ipv4/route.c#L1900">1900</a>         <a href="ident?i=u16">u16</a> <a href="ident?i=type">type</a> = <a href="ident?i=res">res</a>-&gt;<a href="ident?i=type">type</a>;
<a name="L1901" href="source/net/ipv4/route.c#L1901">1901</a>         struct <a href="ident?i=rtable">rtable</a> *rth;
<a name="L1902" href="source/net/ipv4/route.c#L1902">1902</a>         <a href="ident?i=bool">bool</a> do_cache;
<a name="L1903" href="source/net/ipv4/route.c#L1903">1903</a> 
<a name="L1904" href="source/net/ipv4/route.c#L1904">1904</a>         in_dev = <a href="ident?i=__in_dev_get_rcu">__in_dev_get_rcu</a>(dev_out);
<a name="L1905" href="source/net/ipv4/route.c#L1905">1905</a>         if (!in_dev)
<a name="L1906" href="source/net/ipv4/route.c#L1906">1906</a>                 return <a href="ident?i=ERR_PTR">ERR_PTR</a>(-<a href="ident?i=EINVAL">EINVAL</a>);
<a name="L1907" href="source/net/ipv4/route.c#L1907">1907</a> 
<a name="L1908" href="source/net/ipv4/route.c#L1908">1908</a>         if (<a href="ident?i=likely">likely</a>(!<a href="ident?i=IN_DEV_ROUTE_LOCALNET">IN_DEV_ROUTE_LOCALNET</a>(in_dev)))
<a name="L1909" href="source/net/ipv4/route.c#L1909">1909</a>                 if (<a href="ident?i=ipv4_is_loopback">ipv4_is_loopback</a>(fl4-&gt;<a href="ident?i=saddr">saddr</a>) &amp;&amp; !(dev_out-&gt;<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=IFF_LOOPBACK">IFF_LOOPBACK</a>))
<a name="L1910" href="source/net/ipv4/route.c#L1910">1910</a>                         return <a href="ident?i=ERR_PTR">ERR_PTR</a>(-<a href="ident?i=EINVAL">EINVAL</a>);
<a name="L1911" href="source/net/ipv4/route.c#L1911">1911</a> 
<a name="L1912" href="source/net/ipv4/route.c#L1912">1912</a>         if (<a href="ident?i=ipv4_is_lbcast">ipv4_is_lbcast</a>(fl4-&gt;<a href="ident?i=daddr">daddr</a>))
<a name="L1913" href="source/net/ipv4/route.c#L1913">1913</a>                 <a href="ident?i=type">type</a> = RTN_BROADCAST;
<a name="L1914" href="source/net/ipv4/route.c#L1914">1914</a>         else if (<a href="ident?i=ipv4_is_multicast">ipv4_is_multicast</a>(fl4-&gt;<a href="ident?i=daddr">daddr</a>))
<a name="L1915" href="source/net/ipv4/route.c#L1915">1915</a>                 <a href="ident?i=type">type</a> = RTN_MULTICAST;
<a name="L1916" href="source/net/ipv4/route.c#L1916">1916</a>         else if (<a href="ident?i=ipv4_is_zeronet">ipv4_is_zeronet</a>(fl4-&gt;<a href="ident?i=daddr">daddr</a>))
<a name="L1917" href="source/net/ipv4/route.c#L1917">1917</a>                 return <a href="ident?i=ERR_PTR">ERR_PTR</a>(-<a href="ident?i=EINVAL">EINVAL</a>);
<a name="L1918" href="source/net/ipv4/route.c#L1918">1918</a> 
<a name="L1919" href="source/net/ipv4/route.c#L1919">1919</a>         if (dev_out-&gt;<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=IFF_LOOPBACK">IFF_LOOPBACK</a>)
<a name="L1920" href="source/net/ipv4/route.c#L1920">1920</a>                 <a href="ident?i=flags">flags</a> |= <a href="ident?i=RTCF_LOCAL">RTCF_LOCAL</a>;
<a name="L1921" href="source/net/ipv4/route.c#L1921">1921</a> 
<a name="L1922" href="source/net/ipv4/route.c#L1922">1922</a>         do_cache = <a href="ident?i=true">true</a>;
<a name="L1923" href="source/net/ipv4/route.c#L1923">1923</a>         if (<a href="ident?i=type">type</a> == RTN_BROADCAST) {
<a name="L1924" href="source/net/ipv4/route.c#L1924">1924</a>                 <a href="ident?i=flags">flags</a> |= <a href="ident?i=RTCF_BROADCAST">RTCF_BROADCAST</a> | <a href="ident?i=RTCF_LOCAL">RTCF_LOCAL</a>;
<a name="L1925" href="source/net/ipv4/route.c#L1925">1925</a>                 fi = <a href="ident?i=NULL">NULL</a>;
<a name="L1926" href="source/net/ipv4/route.c#L1926">1926</a>         } else if (<a href="ident?i=type">type</a> == RTN_MULTICAST) {
<a name="L1927" href="source/net/ipv4/route.c#L1927">1927</a>                 <a href="ident?i=flags">flags</a> |= <a href="ident?i=RTCF_MULTICAST">RTCF_MULTICAST</a> | <a href="ident?i=RTCF_LOCAL">RTCF_LOCAL</a>;
<a name="L1928" href="source/net/ipv4/route.c#L1928">1928</a>                 if (!<a href="ident?i=ip_check_mc_rcu">ip_check_mc_rcu</a>(in_dev, fl4-&gt;<a href="ident?i=daddr">daddr</a>, fl4-&gt;<a href="ident?i=saddr">saddr</a>,
<a name="L1929" href="source/net/ipv4/route.c#L1929">1929</a>                                      fl4-&gt;<a href="ident?i=flowi4_proto">flowi4_proto</a>))
<a name="L1930" href="source/net/ipv4/route.c#L1930">1930</a>                         <a href="ident?i=flags">flags</a> &amp;= ~RTCF_LOCAL;
<a name="L1931" href="source/net/ipv4/route.c#L1931">1931</a>                 else
<a name="L1932" href="source/net/ipv4/route.c#L1932">1932</a>                         do_cache = <a href="ident?i=false">false</a>;
<a name="L1933" href="source/net/ipv4/route.c#L1933">1933</a>                 <b><i>/* If multicast route do not exist use</i></b>
<a name="L1934" href="source/net/ipv4/route.c#L1934">1934</a> <b><i>                 * default one, but do not gateway in this case.</i></b>
<a name="L1935" href="source/net/ipv4/route.c#L1935">1935</a> <b><i>                 * Yes, it is hack.</i></b>
<a name="L1936" href="source/net/ipv4/route.c#L1936">1936</a> <b><i>                 */</i></b>
<a name="L1937" href="source/net/ipv4/route.c#L1937">1937</a>                 if (fi &amp;&amp; <a href="ident?i=res">res</a>-&gt;prefixlen &lt; 4)
<a name="L1938" href="source/net/ipv4/route.c#L1938">1938</a>                         fi = <a href="ident?i=NULL">NULL</a>;
<a name="L1939" href="source/net/ipv4/route.c#L1939">1939</a>         }
<a name="L1940" href="source/net/ipv4/route.c#L1940">1940</a> 
<a name="L1941" href="source/net/ipv4/route.c#L1941">1941</a>         fnhe = <a href="ident?i=NULL">NULL</a>;
<a name="L1942" href="source/net/ipv4/route.c#L1942">1942</a>         do_cache &amp;= fi != <a href="ident?i=NULL">NULL</a>;
<a name="L1943" href="source/net/ipv4/route.c#L1943">1943</a>         if (do_cache) {
<a name="L1944" href="source/net/ipv4/route.c#L1944">1944</a>                 struct <a href="ident?i=rtable">rtable</a> <a href="ident?i=__rcu">__rcu</a> **prth;
<a name="L1945" href="source/net/ipv4/route.c#L1945">1945</a>                 struct <a href="ident?i=fib_nh">fib_nh</a> *nh = &amp;<a href="ident?i=FIB_RES_NH">FIB_RES_NH</a>(*<a href="ident?i=res">res</a>);
<a name="L1946" href="source/net/ipv4/route.c#L1946">1946</a> 
<a name="L1947" href="source/net/ipv4/route.c#L1947">1947</a>                 fnhe = <a href="ident?i=find_exception">find_exception</a>(nh, fl4-&gt;<a href="ident?i=daddr">daddr</a>);
<a name="L1948" href="source/net/ipv4/route.c#L1948">1948</a>                 if (fnhe)
<a name="L1949" href="source/net/ipv4/route.c#L1949">1949</a>                         prth = &amp;fnhe-&gt;fnhe_rth_output;
<a name="L1950" href="source/net/ipv4/route.c#L1950">1950</a>                 else {
<a name="L1951" href="source/net/ipv4/route.c#L1951">1951</a>                         if (<a href="ident?i=unlikely">unlikely</a>(fl4-&gt;<a href="ident?i=flowi4_flags">flowi4_flags</a> &amp;
<a name="L1952" href="source/net/ipv4/route.c#L1952">1952</a>                                      <a href="ident?i=FLOWI_FLAG_KNOWN_NH">FLOWI_FLAG_KNOWN_NH</a> &amp;&amp;
<a name="L1953" href="source/net/ipv4/route.c#L1953">1953</a>                                      !(nh-&gt;nh_gw &amp;&amp;
<a name="L1954" href="source/net/ipv4/route.c#L1954">1954</a>                                        nh-&gt;nh_scope == RT_SCOPE_LINK))) {
<a name="L1955" href="source/net/ipv4/route.c#L1955">1955</a>                                 do_cache = <a href="ident?i=false">false</a>;
<a name="L1956" href="source/net/ipv4/route.c#L1956">1956</a>                                 goto add;
<a name="L1957" href="source/net/ipv4/route.c#L1957">1957</a>                         }
<a name="L1958" href="source/net/ipv4/route.c#L1958">1958</a>                         prth = <a href="ident?i=raw_cpu_ptr">raw_cpu_ptr</a>(nh-&gt;nh_pcpu_rth_output);
<a name="L1959" href="source/net/ipv4/route.c#L1959">1959</a>                 }
<a name="L1960" href="source/net/ipv4/route.c#L1960">1960</a>                 rth = <a href="ident?i=rcu_dereference">rcu_dereference</a>(*prth);
<a name="L1961" href="source/net/ipv4/route.c#L1961">1961</a>                 if (<a href="ident?i=rt_cache_valid">rt_cache_valid</a>(rth)) {
<a name="L1962" href="source/net/ipv4/route.c#L1962">1962</a>                         <a href="ident?i=dst_hold">dst_hold</a>(&amp;rth-&gt;<a href="ident?i=dst">dst</a>);
<a name="L1963" href="source/net/ipv4/route.c#L1963">1963</a>                         return rth;
<a name="L1964" href="source/net/ipv4/route.c#L1964">1964</a>                 }
<a name="L1965" href="source/net/ipv4/route.c#L1965">1965</a>         }
<a name="L1966" href="source/net/ipv4/route.c#L1966">1966</a> 
<a name="L1967" href="source/net/ipv4/route.c#L1967">1967</a> add:
<a name="L1968" href="source/net/ipv4/route.c#L1968">1968</a>         rth = <a href="ident?i=rt_dst_alloc">rt_dst_alloc</a>(dev_out,
<a name="L1969" href="source/net/ipv4/route.c#L1969">1969</a>                            <a href="ident?i=IN_DEV_CONF_GET">IN_DEV_CONF_GET</a>(in_dev, NOPOLICY),
<a name="L1970" href="source/net/ipv4/route.c#L1970">1970</a>                            <a href="ident?i=IN_DEV_CONF_GET">IN_DEV_CONF_GET</a>(in_dev, NOXFRM),
<a name="L1971" href="source/net/ipv4/route.c#L1971">1971</a>                            do_cache);
<a name="L1972" href="source/net/ipv4/route.c#L1972">1972</a>         if (!rth)
<a name="L1973" href="source/net/ipv4/route.c#L1973">1973</a>                 return <a href="ident?i=ERR_PTR">ERR_PTR</a>(-<a href="ident?i=ENOBUFS">ENOBUFS</a>);
<a name="L1974" href="source/net/ipv4/route.c#L1974">1974</a> 
<a name="L1975" href="source/net/ipv4/route.c#L1975">1975</a>         rth-&gt;<a href="ident?i=dst">dst</a>.<a href="ident?i=output">output</a> = <a href="ident?i=ip_output">ip_output</a>;
<a name="L1976" href="source/net/ipv4/route.c#L1976">1976</a> 
<a name="L1977" href="source/net/ipv4/route.c#L1977">1977</a>         rth-&gt;rt_genid = <a href="ident?i=rt_genid_ipv4">rt_genid_ipv4</a>(<a href="ident?i=dev_net">dev_net</a>(dev_out));
<a name="L1978" href="source/net/ipv4/route.c#L1978">1978</a>         rth-&gt;rt_flags   = <a href="ident?i=flags">flags</a>;
<a name="L1979" href="source/net/ipv4/route.c#L1979">1979</a>         rth-&gt;rt_type    = <a href="ident?i=type">type</a>;
<a name="L1980" href="source/net/ipv4/route.c#L1980">1980</a>         rth-&gt;rt_is_input = 0;
<a name="L1981" href="source/net/ipv4/route.c#L1981">1981</a>         rth-&gt;rt_iif     = orig_oif ? : 0;
<a name="L1982" href="source/net/ipv4/route.c#L1982">1982</a>         rth-&gt;rt_pmtu    = 0;
<a name="L1983" href="source/net/ipv4/route.c#L1983">1983</a>         rth-&gt;rt_gateway = 0;
<a name="L1984" href="source/net/ipv4/route.c#L1984">1984</a>         rth-&gt;rt_uses_gateway = 0;
<a name="L1985" href="source/net/ipv4/route.c#L1985">1985</a>         <a href="ident?i=INIT_LIST_HEAD">INIT_LIST_HEAD</a>(&amp;rth-&gt;rt_uncached);
<a name="L1986" href="source/net/ipv4/route.c#L1986">1986</a> 
<a name="L1987" href="source/net/ipv4/route.c#L1987">1987</a>         <a href="ident?i=RT_CACHE_STAT_INC">RT_CACHE_STAT_INC</a>(out_slow_tot);
<a name="L1988" href="source/net/ipv4/route.c#L1988">1988</a> 
<a name="L1989" href="source/net/ipv4/route.c#L1989">1989</a>         if (<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=RTCF_LOCAL">RTCF_LOCAL</a>)
<a name="L1990" href="source/net/ipv4/route.c#L1990">1990</a>                 rth-&gt;<a href="ident?i=dst">dst</a>.<a href="ident?i=input">input</a> = <a href="ident?i=ip_local_deliver">ip_local_deliver</a>;
<a name="L1991" href="source/net/ipv4/route.c#L1991">1991</a>         if (<a href="ident?i=flags">flags</a> &amp; (<a href="ident?i=RTCF_BROADCAST">RTCF_BROADCAST</a> | <a href="ident?i=RTCF_MULTICAST">RTCF_MULTICAST</a>)) {
<a name="L1992" href="source/net/ipv4/route.c#L1992">1992</a>                 if (<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=RTCF_LOCAL">RTCF_LOCAL</a> &amp;&amp;
<a name="L1993" href="source/net/ipv4/route.c#L1993">1993</a>                     !(dev_out-&gt;<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=IFF_LOOPBACK">IFF_LOOPBACK</a>)) {
<a name="L1994" href="source/net/ipv4/route.c#L1994">1994</a>                         rth-&gt;<a href="ident?i=dst">dst</a>.<a href="ident?i=output">output</a> = <a href="ident?i=ip_mc_output">ip_mc_output</a>;
<a name="L1995" href="source/net/ipv4/route.c#L1995">1995</a>                         <a href="ident?i=RT_CACHE_STAT_INC">RT_CACHE_STAT_INC</a>(out_slow_mc);
<a name="L1996" href="source/net/ipv4/route.c#L1996">1996</a>                 }
<a name="L1997" href="source/net/ipv4/route.c#L1997">1997</a> #ifdef CONFIG_IP_MROUTE
<a name="L1998" href="source/net/ipv4/route.c#L1998">1998</a>                 if (<a href="ident?i=type">type</a> == RTN_MULTICAST) {
<a name="L1999" href="source/net/ipv4/route.c#L1999">1999</a>                         if (<a href="ident?i=IN_DEV_MFORWARD">IN_DEV_MFORWARD</a>(in_dev) &amp;&amp;
<a name="L2000" href="source/net/ipv4/route.c#L2000">2000</a>                             !<a href="ident?i=ipv4_is_local_multicast">ipv4_is_local_multicast</a>(fl4-&gt;<a href="ident?i=daddr">daddr</a>)) {
<a name="L2001" href="source/net/ipv4/route.c#L2001">2001</a>                                 rth-&gt;<a href="ident?i=dst">dst</a>.<a href="ident?i=input">input</a> = <a href="ident?i=ip_mr_input">ip_mr_input</a>;
<a name="L2002" href="source/net/ipv4/route.c#L2002">2002</a>                                 rth-&gt;<a href="ident?i=dst">dst</a>.<a href="ident?i=output">output</a> = <a href="ident?i=ip_mc_output">ip_mc_output</a>;
<a name="L2003" href="source/net/ipv4/route.c#L2003">2003</a>                         }
<a name="L2004" href="source/net/ipv4/route.c#L2004">2004</a>                 }
<a name="L2005" href="source/net/ipv4/route.c#L2005">2005</a> #endif
<a name="L2006" href="source/net/ipv4/route.c#L2006">2006</a>         }
<a name="L2007" href="source/net/ipv4/route.c#L2007">2007</a> 
<a name="L2008" href="source/net/ipv4/route.c#L2008">2008</a>         <a href="ident?i=rt_set_nexthop">rt_set_nexthop</a>(rth, fl4-&gt;<a href="ident?i=daddr">daddr</a>, <a href="ident?i=res">res</a>, fnhe, fi, <a href="ident?i=type">type</a>, 0);
<a name="L2009" href="source/net/ipv4/route.c#L2009">2009</a> 
<a name="L2010" href="source/net/ipv4/route.c#L2010">2010</a>         return rth;
<a name="L2011" href="source/net/ipv4/route.c#L2011">2011</a> }
<a name="L2012" href="source/net/ipv4/route.c#L2012">2012</a> 
<a name="L2013" href="source/net/ipv4/route.c#L2013">2013</a> <b><i>/*</i></b>
<a name="L2014" href="source/net/ipv4/route.c#L2014">2014</a> <b><i> * Major route resolver routine.</i></b>
<a name="L2015" href="source/net/ipv4/route.c#L2015">2015</a> <b><i> */</i></b>
<a name="L2016" href="source/net/ipv4/route.c#L2016">2016</a> 
<a name="L2017" href="source/net/ipv4/route.c#L2017">2017</a> struct <a href="ident?i=rtable">rtable</a> *<a href="ident?i=__ip_route_output_key">__ip_route_output_key</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>, struct <a href="ident?i=flowi4">flowi4</a> *fl4)
<a name="L2018" href="source/net/ipv4/route.c#L2018">2018</a> {
<a name="L2019" href="source/net/ipv4/route.c#L2019">2019</a>         struct <a href="ident?i=net_device">net_device</a> *dev_out = <a href="ident?i=NULL">NULL</a>;
<a name="L2020" href="source/net/ipv4/route.c#L2020">2020</a>         <a href="ident?i=__u8">__u8</a> tos = <a href="ident?i=RT_FL_TOS">RT_FL_TOS</a>(fl4);
<a name="L2021" href="source/net/ipv4/route.c#L2021">2021</a>         unsigned int <a href="ident?i=flags">flags</a> = 0;
<a name="L2022" href="source/net/ipv4/route.c#L2022">2022</a>         struct <a href="ident?i=fib_result">fib_result</a> <a href="ident?i=res">res</a>;
<a name="L2023" href="source/net/ipv4/route.c#L2023">2023</a>         struct <a href="ident?i=rtable">rtable</a> *rth;
<a name="L2024" href="source/net/ipv4/route.c#L2024">2024</a>         int orig_oif;
<a name="L2025" href="source/net/ipv4/route.c#L2025">2025</a> 
<a name="L2026" href="source/net/ipv4/route.c#L2026">2026</a>         <a href="ident?i=res">res</a>.tclassid    = 0;
<a name="L2027" href="source/net/ipv4/route.c#L2027">2027</a>         <a href="ident?i=res">res</a>.fi          = <a href="ident?i=NULL">NULL</a>;
<a name="L2028" href="source/net/ipv4/route.c#L2028">2028</a>         <a href="ident?i=res">res</a>.<a href="ident?i=table">table</a>       = <a href="ident?i=NULL">NULL</a>;
<a name="L2029" href="source/net/ipv4/route.c#L2029">2029</a> 
<a name="L2030" href="source/net/ipv4/route.c#L2030">2030</a>         orig_oif = fl4-&gt;<a href="ident?i=flowi4_oif">flowi4_oif</a>;
<a name="L2031" href="source/net/ipv4/route.c#L2031">2031</a> 
<a name="L2032" href="source/net/ipv4/route.c#L2032">2032</a>         fl4-&gt;<a href="ident?i=flowi4_iif">flowi4_iif</a> = <a href="ident?i=LOOPBACK_IFINDEX">LOOPBACK_IFINDEX</a>;
<a name="L2033" href="source/net/ipv4/route.c#L2033">2033</a>         fl4-&gt;<a href="ident?i=flowi4_tos">flowi4_tos</a> = tos &amp; <a href="ident?i=IPTOS_RT_MASK">IPTOS_RT_MASK</a>;
<a name="L2034" href="source/net/ipv4/route.c#L2034">2034</a>         fl4-&gt;<a href="ident?i=flowi4_scope">flowi4_scope</a> = ((tos &amp; <a href="ident?i=RTO_ONLINK">RTO_ONLINK</a>) ?
<a name="L2035" href="source/net/ipv4/route.c#L2035">2035</a>                          RT_SCOPE_LINK : RT_SCOPE_UNIVERSE);
<a name="L2036" href="source/net/ipv4/route.c#L2036">2036</a> 
<a name="L2037" href="source/net/ipv4/route.c#L2037">2037</a>         <a href="ident?i=rcu_read_lock">rcu_read_lock</a>();
<a name="L2038" href="source/net/ipv4/route.c#L2038">2038</a>         if (fl4-&gt;<a href="ident?i=saddr">saddr</a>) {
<a name="L2039" href="source/net/ipv4/route.c#L2039">2039</a>                 rth = <a href="ident?i=ERR_PTR">ERR_PTR</a>(-<a href="ident?i=EINVAL">EINVAL</a>);
<a name="L2040" href="source/net/ipv4/route.c#L2040">2040</a>                 if (<a href="ident?i=ipv4_is_multicast">ipv4_is_multicast</a>(fl4-&gt;<a href="ident?i=saddr">saddr</a>) ||
<a name="L2041" href="source/net/ipv4/route.c#L2041">2041</a>                     <a href="ident?i=ipv4_is_lbcast">ipv4_is_lbcast</a>(fl4-&gt;<a href="ident?i=saddr">saddr</a>) ||
<a name="L2042" href="source/net/ipv4/route.c#L2042">2042</a>                     <a href="ident?i=ipv4_is_zeronet">ipv4_is_zeronet</a>(fl4-&gt;<a href="ident?i=saddr">saddr</a>))
<a name="L2043" href="source/net/ipv4/route.c#L2043">2043</a>                         goto <a href="ident?i=out">out</a>;
<a name="L2044" href="source/net/ipv4/route.c#L2044">2044</a> 
<a name="L2045" href="source/net/ipv4/route.c#L2045">2045</a>                 <b><i>/* I removed check for oif == dev_out-&gt;oif here.</i></b>
<a name="L2046" href="source/net/ipv4/route.c#L2046">2046</a> <b><i>                   It was wrong for two reasons:</i></b>
<a name="L2047" href="source/net/ipv4/route.c#L2047">2047</a> <b><i>                   1. ip_dev_find(net, saddr) can return wrong iface, if saddr</i></b>
<a name="L2048" href="source/net/ipv4/route.c#L2048">2048</a> <b><i>                      is assigned to multiple interfaces.</i></b>
<a name="L2049" href="source/net/ipv4/route.c#L2049">2049</a> <b><i>                   2. Moreover, we are allowed to send packets with saddr</i></b>
<a name="L2050" href="source/net/ipv4/route.c#L2050">2050</a> <b><i>                      of another iface. --ANK</i></b>
<a name="L2051" href="source/net/ipv4/route.c#L2051">2051</a> <b><i>                 */</i></b>
<a name="L2052" href="source/net/ipv4/route.c#L2052">2052</a> 
<a name="L2053" href="source/net/ipv4/route.c#L2053">2053</a>                 if (fl4-&gt;<a href="ident?i=flowi4_oif">flowi4_oif</a> == 0 &amp;&amp;
<a name="L2054" href="source/net/ipv4/route.c#L2054">2054</a>                     (<a href="ident?i=ipv4_is_multicast">ipv4_is_multicast</a>(fl4-&gt;<a href="ident?i=daddr">daddr</a>) ||
<a name="L2055" href="source/net/ipv4/route.c#L2055">2055</a>                      <a href="ident?i=ipv4_is_lbcast">ipv4_is_lbcast</a>(fl4-&gt;<a href="ident?i=daddr">daddr</a>))) {
<a name="L2056" href="source/net/ipv4/route.c#L2056">2056</a>                         <b><i>/* It is equivalent to inet_addr_type(saddr) == RTN_LOCAL */</i></b>
<a name="L2057" href="source/net/ipv4/route.c#L2057">2057</a>                         dev_out = <a href="ident?i=__ip_dev_find">__ip_dev_find</a>(<a href="ident?i=net">net</a>, fl4-&gt;<a href="ident?i=saddr">saddr</a>, <a href="ident?i=false">false</a>);
<a name="L2058" href="source/net/ipv4/route.c#L2058">2058</a>                         if (!dev_out)
<a name="L2059" href="source/net/ipv4/route.c#L2059">2059</a>                                 goto <a href="ident?i=out">out</a>;
<a name="L2060" href="source/net/ipv4/route.c#L2060">2060</a> 
<a name="L2061" href="source/net/ipv4/route.c#L2061">2061</a>                         <b><i>/* Special hack: user can direct multicasts</i></b>
<a name="L2062" href="source/net/ipv4/route.c#L2062">2062</a> <b><i>                           and limited broadcast via necessary interface</i></b>
<a name="L2063" href="source/net/ipv4/route.c#L2063">2063</a> <b><i>                           without fiddling with IP_MULTICAST_IF or IP_PKTINFO.</i></b>
<a name="L2064" href="source/net/ipv4/route.c#L2064">2064</a> <b><i>                           This hack is not just for fun, it allows</i></b>
<a name="L2065" href="source/net/ipv4/route.c#L2065">2065</a> <b><i>                           vic,vat and friends to work.</i></b>
<a name="L2066" href="source/net/ipv4/route.c#L2066">2066</a> <b><i>                           They bind socket to loopback, set ttl to zero</i></b>
<a name="L2067" href="source/net/ipv4/route.c#L2067">2067</a> <b><i>                           and expect that it will work.</i></b>
<a name="L2068" href="source/net/ipv4/route.c#L2068">2068</a> <b><i>                           From the viewpoint of routing cache they are broken,</i></b>
<a name="L2069" href="source/net/ipv4/route.c#L2069">2069</a> <b><i>                           because we are not allowed to build multicast path</i></b>
<a name="L2070" href="source/net/ipv4/route.c#L2070">2070</a> <b><i>                           with loopback source addr (look, routing cache</i></b>
<a name="L2071" href="source/net/ipv4/route.c#L2071">2071</a> <b><i>                           cannot know, that ttl is zero, so that packet</i></b>
<a name="L2072" href="source/net/ipv4/route.c#L2072">2072</a> <b><i>                           will not leave this host and route is valid).</i></b>
<a name="L2073" href="source/net/ipv4/route.c#L2073">2073</a> <b><i>                           Luckily, this hack is good workaround.</i></b>
<a name="L2074" href="source/net/ipv4/route.c#L2074">2074</a> <b><i>                         */</i></b>
<a name="L2075" href="source/net/ipv4/route.c#L2075">2075</a> 
<a name="L2076" href="source/net/ipv4/route.c#L2076">2076</a>                         fl4-&gt;<a href="ident?i=flowi4_oif">flowi4_oif</a> = dev_out-&gt;ifindex;
<a name="L2077" href="source/net/ipv4/route.c#L2077">2077</a>                         goto make_route;
<a name="L2078" href="source/net/ipv4/route.c#L2078">2078</a>                 }
<a name="L2079" href="source/net/ipv4/route.c#L2079">2079</a> 
<a name="L2080" href="source/net/ipv4/route.c#L2080">2080</a>                 if (!(fl4-&gt;<a href="ident?i=flowi4_flags">flowi4_flags</a> &amp; <a href="ident?i=FLOWI_FLAG_ANYSRC">FLOWI_FLAG_ANYSRC</a>)) {
<a name="L2081" href="source/net/ipv4/route.c#L2081">2081</a>                         <b><i>/* It is equivalent to inet_addr_type(saddr) == RTN_LOCAL */</i></b>
<a name="L2082" href="source/net/ipv4/route.c#L2082">2082</a>                         if (!<a href="ident?i=__ip_dev_find">__ip_dev_find</a>(<a href="ident?i=net">net</a>, fl4-&gt;<a href="ident?i=saddr">saddr</a>, <a href="ident?i=false">false</a>))
<a name="L2083" href="source/net/ipv4/route.c#L2083">2083</a>                                 goto <a href="ident?i=out">out</a>;
<a name="L2084" href="source/net/ipv4/route.c#L2084">2084</a>                 }
<a name="L2085" href="source/net/ipv4/route.c#L2085">2085</a>         }
<a name="L2086" href="source/net/ipv4/route.c#L2086">2086</a> 
<a name="L2087" href="source/net/ipv4/route.c#L2087">2087</a> 
<a name="L2088" href="source/net/ipv4/route.c#L2088">2088</a>         if (fl4-&gt;<a href="ident?i=flowi4_oif">flowi4_oif</a>) {
<a name="L2089" href="source/net/ipv4/route.c#L2089">2089</a>                 dev_out = <a href="ident?i=dev_get_by_index_rcu">dev_get_by_index_rcu</a>(<a href="ident?i=net">net</a>, fl4-&gt;<a href="ident?i=flowi4_oif">flowi4_oif</a>);
<a name="L2090" href="source/net/ipv4/route.c#L2090">2090</a>                 rth = <a href="ident?i=ERR_PTR">ERR_PTR</a>(-<a href="ident?i=ENODEV">ENODEV</a>);
<a name="L2091" href="source/net/ipv4/route.c#L2091">2091</a>                 if (!dev_out)
<a name="L2092" href="source/net/ipv4/route.c#L2092">2092</a>                         goto <a href="ident?i=out">out</a>;
<a name="L2093" href="source/net/ipv4/route.c#L2093">2093</a> 
<a name="L2094" href="source/net/ipv4/route.c#L2094">2094</a>                 <b><i>/* RACE: Check return value of inet_select_addr instead. */</i></b>
<a name="L2095" href="source/net/ipv4/route.c#L2095">2095</a>                 if (!(dev_out-&gt;<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=IFF_UP">IFF_UP</a>) || !<a href="ident?i=__in_dev_get_rcu">__in_dev_get_rcu</a>(dev_out)) {
<a name="L2096" href="source/net/ipv4/route.c#L2096">2096</a>                         rth = <a href="ident?i=ERR_PTR">ERR_PTR</a>(-<a href="ident?i=ENETUNREACH">ENETUNREACH</a>);
<a name="L2097" href="source/net/ipv4/route.c#L2097">2097</a>                         goto <a href="ident?i=out">out</a>;
<a name="L2098" href="source/net/ipv4/route.c#L2098">2098</a>                 }
<a name="L2099" href="source/net/ipv4/route.c#L2099">2099</a>                 if (<a href="ident?i=ipv4_is_local_multicast">ipv4_is_local_multicast</a>(fl4-&gt;<a href="ident?i=daddr">daddr</a>) ||
<a name="L2100" href="source/net/ipv4/route.c#L2100">2100</a>                     <a href="ident?i=ipv4_is_lbcast">ipv4_is_lbcast</a>(fl4-&gt;<a href="ident?i=daddr">daddr</a>)) {
<a name="L2101" href="source/net/ipv4/route.c#L2101">2101</a>                         if (!fl4-&gt;<a href="ident?i=saddr">saddr</a>)
<a name="L2102" href="source/net/ipv4/route.c#L2102">2102</a>                                 fl4-&gt;<a href="ident?i=saddr">saddr</a> = <a href="ident?i=inet_select_addr">inet_select_addr</a>(dev_out, 0,
<a name="L2103" href="source/net/ipv4/route.c#L2103">2103</a>                                                               RT_SCOPE_LINK);
<a name="L2104" href="source/net/ipv4/route.c#L2104">2104</a>                         goto make_route;
<a name="L2105" href="source/net/ipv4/route.c#L2105">2105</a>                 }
<a name="L2106" href="source/net/ipv4/route.c#L2106">2106</a>                 if (!fl4-&gt;<a href="ident?i=saddr">saddr</a>) {
<a name="L2107" href="source/net/ipv4/route.c#L2107">2107</a>                         if (<a href="ident?i=ipv4_is_multicast">ipv4_is_multicast</a>(fl4-&gt;<a href="ident?i=daddr">daddr</a>))
<a name="L2108" href="source/net/ipv4/route.c#L2108">2108</a>                                 fl4-&gt;<a href="ident?i=saddr">saddr</a> = <a href="ident?i=inet_select_addr">inet_select_addr</a>(dev_out, 0,
<a name="L2109" href="source/net/ipv4/route.c#L2109">2109</a>                                                               fl4-&gt;<a href="ident?i=flowi4_scope">flowi4_scope</a>);
<a name="L2110" href="source/net/ipv4/route.c#L2110">2110</a>                         else if (!fl4-&gt;<a href="ident?i=daddr">daddr</a>)
<a name="L2111" href="source/net/ipv4/route.c#L2111">2111</a>                                 fl4-&gt;<a href="ident?i=saddr">saddr</a> = <a href="ident?i=inet_select_addr">inet_select_addr</a>(dev_out, 0,
<a name="L2112" href="source/net/ipv4/route.c#L2112">2112</a>                                                               RT_SCOPE_HOST);
<a name="L2113" href="source/net/ipv4/route.c#L2113">2113</a>                 }
<a name="L2114" href="source/net/ipv4/route.c#L2114">2114</a>         }
<a name="L2115" href="source/net/ipv4/route.c#L2115">2115</a> 
<a name="L2116" href="source/net/ipv4/route.c#L2116">2116</a>         if (!fl4-&gt;<a href="ident?i=daddr">daddr</a>) {
<a name="L2117" href="source/net/ipv4/route.c#L2117">2117</a>                 fl4-&gt;<a href="ident?i=daddr">daddr</a> = fl4-&gt;<a href="ident?i=saddr">saddr</a>;
<a name="L2118" href="source/net/ipv4/route.c#L2118">2118</a>                 if (!fl4-&gt;<a href="ident?i=daddr">daddr</a>)
<a name="L2119" href="source/net/ipv4/route.c#L2119">2119</a>                         fl4-&gt;<a href="ident?i=daddr">daddr</a> = fl4-&gt;<a href="ident?i=saddr">saddr</a> = <a href="ident?i=htonl">htonl</a>(<a href="ident?i=INADDR_LOOPBACK">INADDR_LOOPBACK</a>);
<a name="L2120" href="source/net/ipv4/route.c#L2120">2120</a>                 dev_out = <a href="ident?i=net">net</a>-&gt;<a href="ident?i=loopback_dev">loopback_dev</a>;
<a name="L2121" href="source/net/ipv4/route.c#L2121">2121</a>                 fl4-&gt;<a href="ident?i=flowi4_oif">flowi4_oif</a> = <a href="ident?i=LOOPBACK_IFINDEX">LOOPBACK_IFINDEX</a>;
<a name="L2122" href="source/net/ipv4/route.c#L2122">2122</a>                 <a href="ident?i=res">res</a>.<a href="ident?i=type">type</a> = RTN_LOCAL;
<a name="L2123" href="source/net/ipv4/route.c#L2123">2123</a>                 <a href="ident?i=flags">flags</a> |= <a href="ident?i=RTCF_LOCAL">RTCF_LOCAL</a>;
<a name="L2124" href="source/net/ipv4/route.c#L2124">2124</a>                 goto make_route;
<a name="L2125" href="source/net/ipv4/route.c#L2125">2125</a>         }
<a name="L2126" href="source/net/ipv4/route.c#L2126">2126</a> 
<a name="L2127" href="source/net/ipv4/route.c#L2127">2127</a>         if (<a href="ident?i=fib_lookup">fib_lookup</a>(<a href="ident?i=net">net</a>, fl4, &amp;<a href="ident?i=res">res</a>)) {
<a name="L2128" href="source/net/ipv4/route.c#L2128">2128</a>                 <a href="ident?i=res">res</a>.fi = <a href="ident?i=NULL">NULL</a>;
<a name="L2129" href="source/net/ipv4/route.c#L2129">2129</a>                 <a href="ident?i=res">res</a>.<a href="ident?i=table">table</a> = <a href="ident?i=NULL">NULL</a>;
<a name="L2130" href="source/net/ipv4/route.c#L2130">2130</a>                 if (fl4-&gt;<a href="ident?i=flowi4_oif">flowi4_oif</a>) {
<a name="L2131" href="source/net/ipv4/route.c#L2131">2131</a>                         <b><i>/* Apparently, routing tables are wrong. Assume,</i></b>
<a name="L2132" href="source/net/ipv4/route.c#L2132">2132</a> <b><i>                           that the destination is on link.</i></b>
<a name="L2133" href="source/net/ipv4/route.c#L2133">2133</a> <b><i></i></b>
<a name="L2134" href="source/net/ipv4/route.c#L2134">2134</a> <b><i>                           WHY? DW.</i></b>
<a name="L2135" href="source/net/ipv4/route.c#L2135">2135</a> <b><i>                           Because we are allowed to send to iface</i></b>
<a name="L2136" href="source/net/ipv4/route.c#L2136">2136</a> <b><i>                           even if it has NO routes and NO assigned</i></b>
<a name="L2137" href="source/net/ipv4/route.c#L2137">2137</a> <b><i>                           addresses. When oif is specified, routing</i></b>
<a name="L2138" href="source/net/ipv4/route.c#L2138">2138</a> <b><i>                           tables are looked up with only one purpose:</i></b>
<a name="L2139" href="source/net/ipv4/route.c#L2139">2139</a> <b><i>                           to catch if destination is gatewayed, rather than</i></b>
<a name="L2140" href="source/net/ipv4/route.c#L2140">2140</a> <b><i>                           direct. Moreover, if MSG_DONTROUTE is set,</i></b>
<a name="L2141" href="source/net/ipv4/route.c#L2141">2141</a> <b><i>                           we send packet, ignoring both routing tables</i></b>
<a name="L2142" href="source/net/ipv4/route.c#L2142">2142</a> <b><i>                           and ifaddr state. --ANK</i></b>
<a name="L2143" href="source/net/ipv4/route.c#L2143">2143</a> <b><i></i></b>
<a name="L2144" href="source/net/ipv4/route.c#L2144">2144</a> <b><i></i></b>
<a name="L2145" href="source/net/ipv4/route.c#L2145">2145</a> <b><i>                           We could make it even if oif is unknown,</i></b>
<a name="L2146" href="source/net/ipv4/route.c#L2146">2146</a> <b><i>                           likely IPv6, but we do not.</i></b>
<a name="L2147" href="source/net/ipv4/route.c#L2147">2147</a> <b><i>                         */</i></b>
<a name="L2148" href="source/net/ipv4/route.c#L2148">2148</a> 
<a name="L2149" href="source/net/ipv4/route.c#L2149">2149</a>                         if (fl4-&gt;<a href="ident?i=saddr">saddr</a> == 0)
<a name="L2150" href="source/net/ipv4/route.c#L2150">2150</a>                                 fl4-&gt;<a href="ident?i=saddr">saddr</a> = <a href="ident?i=inet_select_addr">inet_select_addr</a>(dev_out, 0,
<a name="L2151" href="source/net/ipv4/route.c#L2151">2151</a>                                                               RT_SCOPE_LINK);
<a name="L2152" href="source/net/ipv4/route.c#L2152">2152</a>                         <a href="ident?i=res">res</a>.<a href="ident?i=type">type</a> = RTN_UNICAST;
<a name="L2153" href="source/net/ipv4/route.c#L2153">2153</a>                         goto make_route;
<a name="L2154" href="source/net/ipv4/route.c#L2154">2154</a>                 }
<a name="L2155" href="source/net/ipv4/route.c#L2155">2155</a>                 rth = <a href="ident?i=ERR_PTR">ERR_PTR</a>(-<a href="ident?i=ENETUNREACH">ENETUNREACH</a>);
<a name="L2156" href="source/net/ipv4/route.c#L2156">2156</a>                 goto <a href="ident?i=out">out</a>;
<a name="L2157" href="source/net/ipv4/route.c#L2157">2157</a>         }
<a name="L2158" href="source/net/ipv4/route.c#L2158">2158</a> 
<a name="L2159" href="source/net/ipv4/route.c#L2159">2159</a>         if (<a href="ident?i=res">res</a>.<a href="ident?i=type">type</a> == RTN_LOCAL) {
<a name="L2160" href="source/net/ipv4/route.c#L2160">2160</a>                 if (!fl4-&gt;<a href="ident?i=saddr">saddr</a>) {
<a name="L2161" href="source/net/ipv4/route.c#L2161">2161</a>                         if (<a href="ident?i=res">res</a>.fi-&gt;fib_prefsrc)
<a name="L2162" href="source/net/ipv4/route.c#L2162">2162</a>                                 fl4-&gt;<a href="ident?i=saddr">saddr</a> = <a href="ident?i=res">res</a>.fi-&gt;fib_prefsrc;
<a name="L2163" href="source/net/ipv4/route.c#L2163">2163</a>                         else
<a name="L2164" href="source/net/ipv4/route.c#L2164">2164</a>                                 fl4-&gt;<a href="ident?i=saddr">saddr</a> = fl4-&gt;<a href="ident?i=daddr">daddr</a>;
<a name="L2165" href="source/net/ipv4/route.c#L2165">2165</a>                 }
<a name="L2166" href="source/net/ipv4/route.c#L2166">2166</a>                 dev_out = <a href="ident?i=net">net</a>-&gt;<a href="ident?i=loopback_dev">loopback_dev</a>;
<a name="L2167" href="source/net/ipv4/route.c#L2167">2167</a>                 fl4-&gt;<a href="ident?i=flowi4_oif">flowi4_oif</a> = dev_out-&gt;ifindex;
<a name="L2168" href="source/net/ipv4/route.c#L2168">2168</a>                 <a href="ident?i=flags">flags</a> |= <a href="ident?i=RTCF_LOCAL">RTCF_LOCAL</a>;
<a name="L2169" href="source/net/ipv4/route.c#L2169">2169</a>                 goto make_route;
<a name="L2170" href="source/net/ipv4/route.c#L2170">2170</a>         }
<a name="L2171" href="source/net/ipv4/route.c#L2171">2171</a> 
<a name="L2172" href="source/net/ipv4/route.c#L2172">2172</a> #ifdef CONFIG_IP_ROUTE_MULTIPATH
<a name="L2173" href="source/net/ipv4/route.c#L2173">2173</a>         if (<a href="ident?i=res">res</a>.fi-&gt;fib_nhs &gt; 1 &amp;&amp; fl4-&gt;<a href="ident?i=flowi4_oif">flowi4_oif</a> == 0)
<a name="L2174" href="source/net/ipv4/route.c#L2174">2174</a>                 <a href="ident?i=fib_select_multipath">fib_select_multipath</a>(&amp;<a href="ident?i=res">res</a>);
<a name="L2175" href="source/net/ipv4/route.c#L2175">2175</a>         else
<a name="L2176" href="source/net/ipv4/route.c#L2176">2176</a> #endif
<a name="L2177" href="source/net/ipv4/route.c#L2177">2177</a>         if (!<a href="ident?i=res">res</a>.prefixlen &amp;&amp;
<a name="L2178" href="source/net/ipv4/route.c#L2178">2178</a>             <a href="ident?i=res">res</a>.<a href="ident?i=table">table</a>-&gt;tb_num_default &gt; 1 &amp;&amp;
<a name="L2179" href="source/net/ipv4/route.c#L2179">2179</a>             <a href="ident?i=res">res</a>.<a href="ident?i=type">type</a> == RTN_UNICAST &amp;&amp; !fl4-&gt;<a href="ident?i=flowi4_oif">flowi4_oif</a>)
<a name="L2180" href="source/net/ipv4/route.c#L2180">2180</a>                 <a href="ident?i=fib_select_default">fib_select_default</a>(&amp;<a href="ident?i=res">res</a>);
<a name="L2181" href="source/net/ipv4/route.c#L2181">2181</a> 
<a name="L2182" href="source/net/ipv4/route.c#L2182">2182</a>         if (!fl4-&gt;<a href="ident?i=saddr">saddr</a>)
<a name="L2183" href="source/net/ipv4/route.c#L2183">2183</a>                 fl4-&gt;<a href="ident?i=saddr">saddr</a> = <a href="ident?i=FIB_RES_PREFSRC">FIB_RES_PREFSRC</a>(<a href="ident?i=net">net</a>, <a href="ident?i=res">res</a>);
<a name="L2184" href="source/net/ipv4/route.c#L2184">2184</a> 
<a name="L2185" href="source/net/ipv4/route.c#L2185">2185</a>         dev_out = <a href="ident?i=FIB_RES_DEV">FIB_RES_DEV</a>(<a href="ident?i=res">res</a>);
<a name="L2186" href="source/net/ipv4/route.c#L2186">2186</a>         fl4-&gt;<a href="ident?i=flowi4_oif">flowi4_oif</a> = dev_out-&gt;ifindex;
<a name="L2187" href="source/net/ipv4/route.c#L2187">2187</a> 
<a name="L2188" href="source/net/ipv4/route.c#L2188">2188</a> 
<a name="L2189" href="source/net/ipv4/route.c#L2189">2189</a> make_route:
<a name="L2190" href="source/net/ipv4/route.c#L2190">2190</a>         rth = <a href="ident?i=__mkroute_output">__mkroute_output</a>(&amp;<a href="ident?i=res">res</a>, fl4, orig_oif, dev_out, <a href="ident?i=flags">flags</a>);
<a name="L2191" href="source/net/ipv4/route.c#L2191">2191</a> 
<a name="L2192" href="source/net/ipv4/route.c#L2192">2192</a> <a href="ident?i=out">out</a>:
<a name="L2193" href="source/net/ipv4/route.c#L2193">2193</a>         <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L2194" href="source/net/ipv4/route.c#L2194">2194</a>         return rth;
<a name="L2195" href="source/net/ipv4/route.c#L2195">2195</a> }
<a name="L2196" href="source/net/ipv4/route.c#L2196">2196</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=__ip_route_output_key">__ip_route_output_key</a>);
<a name="L2197" href="source/net/ipv4/route.c#L2197">2197</a> 
<a name="L2198" href="source/net/ipv4/route.c#L2198">2198</a> static struct <a href="ident?i=dst_entry">dst_entry</a> *<a href="ident?i=ipv4_blackhole_dst_check">ipv4_blackhole_dst_check</a>(struct <a href="ident?i=dst_entry">dst_entry</a> *<a href="ident?i=dst">dst</a>, <a href="ident?i=u32">u32</a> cookie)
<a name="L2199" href="source/net/ipv4/route.c#L2199">2199</a> {
<a name="L2200" href="source/net/ipv4/route.c#L2200">2200</a>         return <a href="ident?i=NULL">NULL</a>;
<a name="L2201" href="source/net/ipv4/route.c#L2201">2201</a> }
<a name="L2202" href="source/net/ipv4/route.c#L2202">2202</a> 
<a name="L2203" href="source/net/ipv4/route.c#L2203">2203</a> static unsigned int <a href="ident?i=ipv4_blackhole_mtu">ipv4_blackhole_mtu</a>(const struct <a href="ident?i=dst_entry">dst_entry</a> *<a href="ident?i=dst">dst</a>)
<a name="L2204" href="source/net/ipv4/route.c#L2204">2204</a> {
<a name="L2205" href="source/net/ipv4/route.c#L2205">2205</a>         unsigned int <a href="ident?i=mtu">mtu</a> = <a href="ident?i=dst_metric_raw">dst_metric_raw</a>(<a href="ident?i=dst">dst</a>, <a href="ident?i=RTAX_MTU">RTAX_MTU</a>);
<a name="L2206" href="source/net/ipv4/route.c#L2206">2206</a> 
<a name="L2207" href="source/net/ipv4/route.c#L2207">2207</a>         return <a href="ident?i=mtu">mtu</a> ? : <a href="ident?i=dst">dst</a>-&gt;<a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=mtu">mtu</a>;
<a name="L2208" href="source/net/ipv4/route.c#L2208">2208</a> }
<a name="L2209" href="source/net/ipv4/route.c#L2209">2209</a> 
<a name="L2210" href="source/net/ipv4/route.c#L2210">2210</a> static void <a href="ident?i=ipv4_rt_blackhole_update_pmtu">ipv4_rt_blackhole_update_pmtu</a>(struct <a href="ident?i=dst_entry">dst_entry</a> *<a href="ident?i=dst">dst</a>, struct <a href="ident?i=sock">sock</a> *sk,
<a name="L2211" href="source/net/ipv4/route.c#L2211">2211</a>                                           struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, <a href="ident?i=u32">u32</a> <a href="ident?i=mtu">mtu</a>)
<a name="L2212" href="source/net/ipv4/route.c#L2212">2212</a> {
<a name="L2213" href="source/net/ipv4/route.c#L2213">2213</a> }
<a name="L2214" href="source/net/ipv4/route.c#L2214">2214</a> 
<a name="L2215" href="source/net/ipv4/route.c#L2215">2215</a> static void <a href="ident?i=ipv4_rt_blackhole_redirect">ipv4_rt_blackhole_redirect</a>(struct <a href="ident?i=dst_entry">dst_entry</a> *<a href="ident?i=dst">dst</a>, struct <a href="ident?i=sock">sock</a> *sk,
<a name="L2216" href="source/net/ipv4/route.c#L2216">2216</a>                                        struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L2217" href="source/net/ipv4/route.c#L2217">2217</a> {
<a name="L2218" href="source/net/ipv4/route.c#L2218">2218</a> }
<a name="L2219" href="source/net/ipv4/route.c#L2219">2219</a> 
<a name="L2220" href="source/net/ipv4/route.c#L2220">2220</a> static <a href="ident?i=u32">u32</a> *<a href="ident?i=ipv4_rt_blackhole_cow_metrics">ipv4_rt_blackhole_cow_metrics</a>(struct <a href="ident?i=dst_entry">dst_entry</a> *<a href="ident?i=dst">dst</a>,
<a name="L2221" href="source/net/ipv4/route.c#L2221">2221</a>                                           unsigned long <a href="ident?i=old">old</a>)
<a name="L2222" href="source/net/ipv4/route.c#L2222">2222</a> {
<a name="L2223" href="source/net/ipv4/route.c#L2223">2223</a>         return <a href="ident?i=NULL">NULL</a>;
<a name="L2224" href="source/net/ipv4/route.c#L2224">2224</a> }
<a name="L2225" href="source/net/ipv4/route.c#L2225">2225</a> 
<a name="L2226" href="source/net/ipv4/route.c#L2226">2226</a> static struct <a href="ident?i=dst_ops">dst_ops</a> <a href="ident?i=ipv4_dst_blackhole_ops">ipv4_dst_blackhole_ops</a> = {
<a name="L2227" href="source/net/ipv4/route.c#L2227">2227</a>         .<a href="ident?i=family">family</a>                 =       <a href="ident?i=AF_INET">AF_INET</a>,
<a name="L2228" href="source/net/ipv4/route.c#L2228">2228</a>         .<a href="ident?i=check">check</a>                  =       <a href="ident?i=ipv4_blackhole_dst_check">ipv4_blackhole_dst_check</a>,
<a name="L2229" href="source/net/ipv4/route.c#L2229">2229</a>         .<a href="ident?i=mtu">mtu</a>                    =       <a href="ident?i=ipv4_blackhole_mtu">ipv4_blackhole_mtu</a>,
<a name="L2230" href="source/net/ipv4/route.c#L2230">2230</a>         .default_advmss         =       <a href="ident?i=ipv4_default_advmss">ipv4_default_advmss</a>,
<a name="L2231" href="source/net/ipv4/route.c#L2231">2231</a>         .update_pmtu            =       <a href="ident?i=ipv4_rt_blackhole_update_pmtu">ipv4_rt_blackhole_update_pmtu</a>,
<a name="L2232" href="source/net/ipv4/route.c#L2232">2232</a>         .<a href="ident?i=redirect">redirect</a>               =       <a href="ident?i=ipv4_rt_blackhole_redirect">ipv4_rt_blackhole_redirect</a>,
<a name="L2233" href="source/net/ipv4/route.c#L2233">2233</a>         .cow_metrics            =       <a href="ident?i=ipv4_rt_blackhole_cow_metrics">ipv4_rt_blackhole_cow_metrics</a>,
<a name="L2234" href="source/net/ipv4/route.c#L2234">2234</a>         .<a href="ident?i=neigh_lookup">neigh_lookup</a>           =       <a href="ident?i=ipv4_neigh_lookup">ipv4_neigh_lookup</a>,
<a name="L2235" href="source/net/ipv4/route.c#L2235">2235</a> };
<a name="L2236" href="source/net/ipv4/route.c#L2236">2236</a> 
<a name="L2237" href="source/net/ipv4/route.c#L2237">2237</a> struct <a href="ident?i=dst_entry">dst_entry</a> *<a href="ident?i=ipv4_blackhole_route">ipv4_blackhole_route</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>, struct <a href="ident?i=dst_entry">dst_entry</a> *dst_orig)
<a name="L2238" href="source/net/ipv4/route.c#L2238">2238</a> {
<a name="L2239" href="source/net/ipv4/route.c#L2239">2239</a>         struct <a href="ident?i=rtable">rtable</a> *ort = (struct <a href="ident?i=rtable">rtable</a> *) dst_orig;
<a name="L2240" href="source/net/ipv4/route.c#L2240">2240</a>         struct <a href="ident?i=rtable">rtable</a> *<a href="ident?i=rt">rt</a>;
<a name="L2241" href="source/net/ipv4/route.c#L2241">2241</a> 
<a name="L2242" href="source/net/ipv4/route.c#L2242">2242</a>         <a href="ident?i=rt">rt</a> = <a href="ident?i=dst_alloc">dst_alloc</a>(&amp;<a href="ident?i=ipv4_dst_blackhole_ops">ipv4_dst_blackhole_ops</a>, <a href="ident?i=NULL">NULL</a>, 1, <a href="ident?i=DST_OBSOLETE_NONE">DST_OBSOLETE_NONE</a>, 0);
<a name="L2243" href="source/net/ipv4/route.c#L2243">2243</a>         if (<a href="ident?i=rt">rt</a>) {
<a name="L2244" href="source/net/ipv4/route.c#L2244">2244</a>                 struct <a href="ident?i=dst_entry">dst_entry</a> *<a href="ident?i=new">new</a> = &amp;<a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>;
<a name="L2245" href="source/net/ipv4/route.c#L2245">2245</a> 
<a name="L2246" href="source/net/ipv4/route.c#L2246">2246</a>                 <a href="ident?i=new">new</a>-&gt;__use = 1;
<a name="L2247" href="source/net/ipv4/route.c#L2247">2247</a>                 <a href="ident?i=new">new</a>-&gt;<a href="ident?i=input">input</a> = <a href="ident?i=dst_discard">dst_discard</a>;
<a name="L2248" href="source/net/ipv4/route.c#L2248">2248</a>                 <a href="ident?i=new">new</a>-&gt;<a href="ident?i=output">output</a> = <a href="ident?i=dst_discard_sk">dst_discard_sk</a>;
<a name="L2249" href="source/net/ipv4/route.c#L2249">2249</a> 
<a name="L2250" href="source/net/ipv4/route.c#L2250">2250</a>                 <a href="ident?i=new">new</a>-&gt;<a href="ident?i=dev">dev</a> = ort-&gt;<a href="ident?i=dst">dst</a>.<a href="ident?i=dev">dev</a>;
<a name="L2251" href="source/net/ipv4/route.c#L2251">2251</a>                 if (<a href="ident?i=new">new</a>-&gt;<a href="ident?i=dev">dev</a>)
<a name="L2252" href="source/net/ipv4/route.c#L2252">2252</a>                         <a href="ident?i=dev_hold">dev_hold</a>(<a href="ident?i=new">new</a>-&gt;<a href="ident?i=dev">dev</a>);
<a name="L2253" href="source/net/ipv4/route.c#L2253">2253</a> 
<a name="L2254" href="source/net/ipv4/route.c#L2254">2254</a>                 <a href="ident?i=rt">rt</a>-&gt;rt_is_input = ort-&gt;rt_is_input;
<a name="L2255" href="source/net/ipv4/route.c#L2255">2255</a>                 <a href="ident?i=rt">rt</a>-&gt;rt_iif = ort-&gt;rt_iif;
<a name="L2256" href="source/net/ipv4/route.c#L2256">2256</a>                 <a href="ident?i=rt">rt</a>-&gt;rt_pmtu = ort-&gt;rt_pmtu;
<a name="L2257" href="source/net/ipv4/route.c#L2257">2257</a> 
<a name="L2258" href="source/net/ipv4/route.c#L2258">2258</a>                 <a href="ident?i=rt">rt</a>-&gt;rt_genid = <a href="ident?i=rt_genid_ipv4">rt_genid_ipv4</a>(<a href="ident?i=net">net</a>);
<a name="L2259" href="source/net/ipv4/route.c#L2259">2259</a>                 <a href="ident?i=rt">rt</a>-&gt;rt_flags = ort-&gt;rt_flags;
<a name="L2260" href="source/net/ipv4/route.c#L2260">2260</a>                 <a href="ident?i=rt">rt</a>-&gt;rt_type = ort-&gt;rt_type;
<a name="L2261" href="source/net/ipv4/route.c#L2261">2261</a>                 <a href="ident?i=rt">rt</a>-&gt;rt_gateway = ort-&gt;rt_gateway;
<a name="L2262" href="source/net/ipv4/route.c#L2262">2262</a>                 <a href="ident?i=rt">rt</a>-&gt;rt_uses_gateway = ort-&gt;rt_uses_gateway;
<a name="L2263" href="source/net/ipv4/route.c#L2263">2263</a> 
<a name="L2264" href="source/net/ipv4/route.c#L2264">2264</a>                 <a href="ident?i=INIT_LIST_HEAD">INIT_LIST_HEAD</a>(&amp;<a href="ident?i=rt">rt</a>-&gt;rt_uncached);
<a name="L2265" href="source/net/ipv4/route.c#L2265">2265</a> 
<a name="L2266" href="source/net/ipv4/route.c#L2266">2266</a>                 <a href="ident?i=dst_free">dst_free</a>(<a href="ident?i=new">new</a>);
<a name="L2267" href="source/net/ipv4/route.c#L2267">2267</a>         }
<a name="L2268" href="source/net/ipv4/route.c#L2268">2268</a> 
<a name="L2269" href="source/net/ipv4/route.c#L2269">2269</a>         <a href="ident?i=dst_release">dst_release</a>(dst_orig);
<a name="L2270" href="source/net/ipv4/route.c#L2270">2270</a> 
<a name="L2271" href="source/net/ipv4/route.c#L2271">2271</a>         return <a href="ident?i=rt">rt</a> ? &amp;<a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a> : <a href="ident?i=ERR_PTR">ERR_PTR</a>(-<a href="ident?i=ENOMEM">ENOMEM</a>);
<a name="L2272" href="source/net/ipv4/route.c#L2272">2272</a> }
<a name="L2273" href="source/net/ipv4/route.c#L2273">2273</a> 
<a name="L2274" href="source/net/ipv4/route.c#L2274">2274</a> struct <a href="ident?i=rtable">rtable</a> *<a href="ident?i=ip_route_output_flow">ip_route_output_flow</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>, struct <a href="ident?i=flowi4">flowi4</a> *flp4,
<a name="L2275" href="source/net/ipv4/route.c#L2275">2275</a>                                     struct <a href="ident?i=sock">sock</a> *sk)
<a name="L2276" href="source/net/ipv4/route.c#L2276">2276</a> {
<a name="L2277" href="source/net/ipv4/route.c#L2277">2277</a>         struct <a href="ident?i=rtable">rtable</a> *<a href="ident?i=rt">rt</a> = <a href="ident?i=__ip_route_output_key">__ip_route_output_key</a>(<a href="ident?i=net">net</a>, flp4);
<a name="L2278" href="source/net/ipv4/route.c#L2278">2278</a> 
<a name="L2279" href="source/net/ipv4/route.c#L2279">2279</a>         if (<a href="ident?i=IS_ERR">IS_ERR</a>(<a href="ident?i=rt">rt</a>))
<a name="L2280" href="source/net/ipv4/route.c#L2280">2280</a>                 return <a href="ident?i=rt">rt</a>;
<a name="L2281" href="source/net/ipv4/route.c#L2281">2281</a> 
<a name="L2282" href="source/net/ipv4/route.c#L2282">2282</a>         if (flp4-&gt;<a href="ident?i=flowi4_proto">flowi4_proto</a>)
<a name="L2283" href="source/net/ipv4/route.c#L2283">2283</a>                 <a href="ident?i=rt">rt</a> = (struct <a href="ident?i=rtable">rtable</a> *)<a href="ident?i=xfrm_lookup_route">xfrm_lookup_route</a>(<a href="ident?i=net">net</a>, &amp;<a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>,
<a name="L2284" href="source/net/ipv4/route.c#L2284">2284</a>                                                         <a href="ident?i=flowi4_to_flowi">flowi4_to_flowi</a>(flp4),
<a name="L2285" href="source/net/ipv4/route.c#L2285">2285</a>                                                         sk, 0);
<a name="L2286" href="source/net/ipv4/route.c#L2286">2286</a> 
<a name="L2287" href="source/net/ipv4/route.c#L2287">2287</a>         return <a href="ident?i=rt">rt</a>;
<a name="L2288" href="source/net/ipv4/route.c#L2288">2288</a> }
<a name="L2289" href="source/net/ipv4/route.c#L2289">2289</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=ip_route_output_flow">ip_route_output_flow</a>);
<a name="L2290" href="source/net/ipv4/route.c#L2290">2290</a> 
<a name="L2291" href="source/net/ipv4/route.c#L2291">2291</a> static int <a href="ident?i=rt_fill_info">rt_fill_info</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>,  <a href="ident?i=__be32">__be32</a> <a href="ident?i=dst">dst</a>, <a href="ident?i=__be32">__be32</a> <a href="ident?i=src">src</a>,
<a name="L2292" href="source/net/ipv4/route.c#L2292">2292</a>                         struct <a href="ident?i=flowi4">flowi4</a> *fl4, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, <a href="ident?i=u32">u32</a> portid,
<a name="L2293" href="source/net/ipv4/route.c#L2293">2293</a>                         <a href="ident?i=u32">u32</a> <a href="ident?i=seq">seq</a>, int <a href="ident?i=event">event</a>, int <a href="ident?i=nowait">nowait</a>, unsigned int <a href="ident?i=flags">flags</a>)
<a name="L2294" href="source/net/ipv4/route.c#L2294">2294</a> {
<a name="L2295" href="source/net/ipv4/route.c#L2295">2295</a>         struct <a href="ident?i=rtable">rtable</a> *<a href="ident?i=rt">rt</a> = <a href="ident?i=skb_rtable">skb_rtable</a>(<a href="ident?i=skb">skb</a>);
<a name="L2296" href="source/net/ipv4/route.c#L2296">2296</a>         struct <a href="ident?i=rtmsg">rtmsg</a> *<a href="ident?i=r">r</a>;
<a name="L2297" href="source/net/ipv4/route.c#L2297">2297</a>         struct <a href="ident?i=nlmsghdr">nlmsghdr</a> *nlh;
<a name="L2298" href="source/net/ipv4/route.c#L2298">2298</a>         unsigned long expires = 0;
<a name="L2299" href="source/net/ipv4/route.c#L2299">2299</a>         <a href="ident?i=u32">u32</a> <a href="ident?i=error">error</a>;
<a name="L2300" href="source/net/ipv4/route.c#L2300">2300</a>         <a href="ident?i=u32">u32</a> metrics[<a href="ident?i=RTAX_MAX">RTAX_MAX</a>];
<a name="L2301" href="source/net/ipv4/route.c#L2301">2301</a> 
<a name="L2302" href="source/net/ipv4/route.c#L2302">2302</a>         nlh = <a href="ident?i=nlmsg_put">nlmsg_put</a>(<a href="ident?i=skb">skb</a>, portid, <a href="ident?i=seq">seq</a>, <a href="ident?i=event">event</a>, sizeof(*<a href="ident?i=r">r</a>), <a href="ident?i=flags">flags</a>);
<a name="L2303" href="source/net/ipv4/route.c#L2303">2303</a>         if (!nlh)
<a name="L2304" href="source/net/ipv4/route.c#L2304">2304</a>                 return -<a href="ident?i=EMSGSIZE">EMSGSIZE</a>;
<a name="L2305" href="source/net/ipv4/route.c#L2305">2305</a> 
<a name="L2306" href="source/net/ipv4/route.c#L2306">2306</a>         <a href="ident?i=r">r</a> = <a href="ident?i=nlmsg_data">nlmsg_data</a>(nlh);
<a name="L2307" href="source/net/ipv4/route.c#L2307">2307</a>         <a href="ident?i=r">r</a>-&gt;rtm_family    = <a href="ident?i=AF_INET">AF_INET</a>;
<a name="L2308" href="source/net/ipv4/route.c#L2308">2308</a>         <a href="ident?i=r">r</a>-&gt;rtm_dst_len  = 32;
<a name="L2309" href="source/net/ipv4/route.c#L2309">2309</a>         <a href="ident?i=r">r</a>-&gt;rtm_src_len  = 0;
<a name="L2310" href="source/net/ipv4/route.c#L2310">2310</a>         <a href="ident?i=r">r</a>-&gt;rtm_tos      = fl4-&gt;<a href="ident?i=flowi4_tos">flowi4_tos</a>;
<a name="L2311" href="source/net/ipv4/route.c#L2311">2311</a>         <a href="ident?i=r">r</a>-&gt;rtm_table    = RT_TABLE_MAIN;
<a name="L2312" href="source/net/ipv4/route.c#L2312">2312</a>         if (<a href="ident?i=nla_put_u32">nla_put_u32</a>(<a href="ident?i=skb">skb</a>, RTA_TABLE, RT_TABLE_MAIN))
<a name="L2313" href="source/net/ipv4/route.c#L2313">2313</a>                 goto nla_put_failure;
<a name="L2314" href="source/net/ipv4/route.c#L2314">2314</a>         <a href="ident?i=r">r</a>-&gt;rtm_type     = <a href="ident?i=rt">rt</a>-&gt;rt_type;
<a name="L2315" href="source/net/ipv4/route.c#L2315">2315</a>         <a href="ident?i=r">r</a>-&gt;rtm_scope    = RT_SCOPE_UNIVERSE;
<a name="L2316" href="source/net/ipv4/route.c#L2316">2316</a>         <a href="ident?i=r">r</a>-&gt;rtm_protocol = <a href="ident?i=RTPROT_UNSPEC">RTPROT_UNSPEC</a>;
<a name="L2317" href="source/net/ipv4/route.c#L2317">2317</a>         <a href="ident?i=r">r</a>-&gt;rtm_flags    = (<a href="ident?i=rt">rt</a>-&gt;rt_flags &amp; ~0xFFFF) | <a href="ident?i=RTM_F_CLONED">RTM_F_CLONED</a>;
<a name="L2318" href="source/net/ipv4/route.c#L2318">2318</a>         if (<a href="ident?i=rt">rt</a>-&gt;rt_flags &amp; <a href="ident?i=RTCF_NOTIFY">RTCF_NOTIFY</a>)
<a name="L2319" href="source/net/ipv4/route.c#L2319">2319</a>                 <a href="ident?i=r">r</a>-&gt;rtm_flags |= <a href="ident?i=RTM_F_NOTIFY">RTM_F_NOTIFY</a>;
<a name="L2320" href="source/net/ipv4/route.c#L2320">2320</a>         if (<a href="ident?i=IPCB">IPCB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=IPSKB_DOREDIRECT">IPSKB_DOREDIRECT</a>)
<a name="L2321" href="source/net/ipv4/route.c#L2321">2321</a>                 <a href="ident?i=r">r</a>-&gt;rtm_flags |= <a href="ident?i=RTCF_DOREDIRECT">RTCF_DOREDIRECT</a>;
<a name="L2322" href="source/net/ipv4/route.c#L2322">2322</a> 
<a name="L2323" href="source/net/ipv4/route.c#L2323">2323</a>         if (<a href="ident?i=nla_put_in_addr">nla_put_in_addr</a>(<a href="ident?i=skb">skb</a>, RTA_DST, <a href="ident?i=dst">dst</a>))
<a name="L2324" href="source/net/ipv4/route.c#L2324">2324</a>                 goto nla_put_failure;
<a name="L2325" href="source/net/ipv4/route.c#L2325">2325</a>         if (<a href="ident?i=src">src</a>) {
<a name="L2326" href="source/net/ipv4/route.c#L2326">2326</a>                 <a href="ident?i=r">r</a>-&gt;rtm_src_len = 32;
<a name="L2327" href="source/net/ipv4/route.c#L2327">2327</a>                 if (<a href="ident?i=nla_put_in_addr">nla_put_in_addr</a>(<a href="ident?i=skb">skb</a>, RTA_SRC, <a href="ident?i=src">src</a>))
<a name="L2328" href="source/net/ipv4/route.c#L2328">2328</a>                         goto nla_put_failure;
<a name="L2329" href="source/net/ipv4/route.c#L2329">2329</a>         }
<a name="L2330" href="source/net/ipv4/route.c#L2330">2330</a>         if (<a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>.<a href="ident?i=dev">dev</a> &amp;&amp;
<a name="L2331" href="source/net/ipv4/route.c#L2331">2331</a>             <a href="ident?i=nla_put_u32">nla_put_u32</a>(<a href="ident?i=skb">skb</a>, RTA_OIF, <a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>.<a href="ident?i=dev">dev</a>-&gt;ifindex))
<a name="L2332" href="source/net/ipv4/route.c#L2332">2332</a>                 goto nla_put_failure;
<a name="L2333" href="source/net/ipv4/route.c#L2333">2333</a> #ifdef CONFIG_IP_ROUTE_CLASSID
<a name="L2334" href="source/net/ipv4/route.c#L2334">2334</a>         if (<a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>.tclassid &amp;&amp;
<a name="L2335" href="source/net/ipv4/route.c#L2335">2335</a>             <a href="ident?i=nla_put_u32">nla_put_u32</a>(<a href="ident?i=skb">skb</a>, RTA_FLOW, <a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>.tclassid))
<a name="L2336" href="source/net/ipv4/route.c#L2336">2336</a>                 goto nla_put_failure;
<a name="L2337" href="source/net/ipv4/route.c#L2337">2337</a> #endif
<a name="L2338" href="source/net/ipv4/route.c#L2338">2338</a>         if (!<a href="ident?i=rt_is_input_route">rt_is_input_route</a>(<a href="ident?i=rt">rt</a>) &amp;&amp;
<a name="L2339" href="source/net/ipv4/route.c#L2339">2339</a>             fl4-&gt;<a href="ident?i=saddr">saddr</a> != <a href="ident?i=src">src</a>) {
<a name="L2340" href="source/net/ipv4/route.c#L2340">2340</a>                 if (<a href="ident?i=nla_put_in_addr">nla_put_in_addr</a>(<a href="ident?i=skb">skb</a>, RTA_PREFSRC, fl4-&gt;<a href="ident?i=saddr">saddr</a>))
<a name="L2341" href="source/net/ipv4/route.c#L2341">2341</a>                         goto nla_put_failure;
<a name="L2342" href="source/net/ipv4/route.c#L2342">2342</a>         }
<a name="L2343" href="source/net/ipv4/route.c#L2343">2343</a>         if (<a href="ident?i=rt">rt</a>-&gt;rt_uses_gateway &amp;&amp;
<a name="L2344" href="source/net/ipv4/route.c#L2344">2344</a>             <a href="ident?i=nla_put_in_addr">nla_put_in_addr</a>(<a href="ident?i=skb">skb</a>, RTA_GATEWAY, <a href="ident?i=rt">rt</a>-&gt;rt_gateway))
<a name="L2345" href="source/net/ipv4/route.c#L2345">2345</a>                 goto nla_put_failure;
<a name="L2346" href="source/net/ipv4/route.c#L2346">2346</a> 
<a name="L2347" href="source/net/ipv4/route.c#L2347">2347</a>         expires = <a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>.expires;
<a name="L2348" href="source/net/ipv4/route.c#L2348">2348</a>         if (expires) {
<a name="L2349" href="source/net/ipv4/route.c#L2349">2349</a>                 unsigned long <a href="ident?i=now">now</a> = <a href="ident?i=jiffies">jiffies</a>;
<a name="L2350" href="source/net/ipv4/route.c#L2350">2350</a> 
<a name="L2351" href="source/net/ipv4/route.c#L2351">2351</a>                 if (<a href="ident?i=time_before">time_before</a>(<a href="ident?i=now">now</a>, expires))
<a name="L2352" href="source/net/ipv4/route.c#L2352">2352</a>                         expires -= <a href="ident?i=now">now</a>;
<a name="L2353" href="source/net/ipv4/route.c#L2353">2353</a>                 else
<a name="L2354" href="source/net/ipv4/route.c#L2354">2354</a>                         expires = 0;
<a name="L2355" href="source/net/ipv4/route.c#L2355">2355</a>         }
<a name="L2356" href="source/net/ipv4/route.c#L2356">2356</a> 
<a name="L2357" href="source/net/ipv4/route.c#L2357">2357</a>         <a href="ident?i=memcpy">memcpy</a>(metrics, <a href="ident?i=dst_metrics_ptr">dst_metrics_ptr</a>(&amp;<a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>), sizeof(metrics));
<a name="L2358" href="source/net/ipv4/route.c#L2358">2358</a>         if (<a href="ident?i=rt">rt</a>-&gt;rt_pmtu &amp;&amp; expires)
<a name="L2359" href="source/net/ipv4/route.c#L2359">2359</a>                 metrics[<a href="ident?i=RTAX_MTU">RTAX_MTU</a> - 1] = <a href="ident?i=rt">rt</a>-&gt;rt_pmtu;
<a name="L2360" href="source/net/ipv4/route.c#L2360">2360</a>         if (<a href="ident?i=rtnetlink_put_metrics">rtnetlink_put_metrics</a>(<a href="ident?i=skb">skb</a>, metrics) &lt; 0)
<a name="L2361" href="source/net/ipv4/route.c#L2361">2361</a>                 goto nla_put_failure;
<a name="L2362" href="source/net/ipv4/route.c#L2362">2362</a> 
<a name="L2363" href="source/net/ipv4/route.c#L2363">2363</a>         if (fl4-&gt;<a href="ident?i=flowi4_mark">flowi4_mark</a> &amp;&amp;
<a name="L2364" href="source/net/ipv4/route.c#L2364">2364</a>             <a href="ident?i=nla_put_u32">nla_put_u32</a>(<a href="ident?i=skb">skb</a>, RTA_MARK, fl4-&gt;<a href="ident?i=flowi4_mark">flowi4_mark</a>))
<a name="L2365" href="source/net/ipv4/route.c#L2365">2365</a>                 goto nla_put_failure;
<a name="L2366" href="source/net/ipv4/route.c#L2366">2366</a> 
<a name="L2367" href="source/net/ipv4/route.c#L2367">2367</a>         <a href="ident?i=error">error</a> = <a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>.<a href="ident?i=error">error</a>;
<a name="L2368" href="source/net/ipv4/route.c#L2368">2368</a> 
<a name="L2369" href="source/net/ipv4/route.c#L2369">2369</a>         if (<a href="ident?i=rt_is_input_route">rt_is_input_route</a>(<a href="ident?i=rt">rt</a>)) {
<a name="L2370" href="source/net/ipv4/route.c#L2370">2370</a> #ifdef CONFIG_IP_MROUTE
<a name="L2371" href="source/net/ipv4/route.c#L2371">2371</a>                 if (<a href="ident?i=ipv4_is_multicast">ipv4_is_multicast</a>(<a href="ident?i=dst">dst</a>) &amp;&amp; !<a href="ident?i=ipv4_is_local_multicast">ipv4_is_local_multicast</a>(<a href="ident?i=dst">dst</a>) &amp;&amp;
<a name="L2372" href="source/net/ipv4/route.c#L2372">2372</a>                     <a href="ident?i=IPV4_DEVCONF_ALL">IPV4_DEVCONF_ALL</a>(<a href="ident?i=net">net</a>, MC_FORWARDING)) {
<a name="L2373" href="source/net/ipv4/route.c#L2373">2373</a>                         int <a href="ident?i=err">err</a> = <a href="ident?i=ipmr_get_route">ipmr_get_route</a>(<a href="ident?i=net">net</a>, <a href="ident?i=skb">skb</a>,
<a name="L2374" href="source/net/ipv4/route.c#L2374">2374</a>                                                  fl4-&gt;<a href="ident?i=saddr">saddr</a>, fl4-&gt;<a href="ident?i=daddr">daddr</a>,
<a name="L2375" href="source/net/ipv4/route.c#L2375">2375</a>                                                  <a href="ident?i=r">r</a>, <a href="ident?i=nowait">nowait</a>);
<a name="L2376" href="source/net/ipv4/route.c#L2376">2376</a>                         if (<a href="ident?i=err">err</a> &lt;= 0) {
<a name="L2377" href="source/net/ipv4/route.c#L2377">2377</a>                                 if (!<a href="ident?i=nowait">nowait</a>) {
<a name="L2378" href="source/net/ipv4/route.c#L2378">2378</a>                                         if (<a href="ident?i=err">err</a> == 0)
<a name="L2379" href="source/net/ipv4/route.c#L2379">2379</a>                                                 return 0;
<a name="L2380" href="source/net/ipv4/route.c#L2380">2380</a>                                         goto nla_put_failure;
<a name="L2381" href="source/net/ipv4/route.c#L2381">2381</a>                                 } else {
<a name="L2382" href="source/net/ipv4/route.c#L2382">2382</a>                                         if (<a href="ident?i=err">err</a> == -<a href="ident?i=EMSGSIZE">EMSGSIZE</a>)
<a name="L2383" href="source/net/ipv4/route.c#L2383">2383</a>                                                 goto nla_put_failure;
<a name="L2384" href="source/net/ipv4/route.c#L2384">2384</a>                                         <a href="ident?i=error">error</a> = <a href="ident?i=err">err</a>;
<a name="L2385" href="source/net/ipv4/route.c#L2385">2385</a>                                 }
<a name="L2386" href="source/net/ipv4/route.c#L2386">2386</a>                         }
<a name="L2387" href="source/net/ipv4/route.c#L2387">2387</a>                 } else
<a name="L2388" href="source/net/ipv4/route.c#L2388">2388</a> #endif
<a name="L2389" href="source/net/ipv4/route.c#L2389">2389</a>                         if (<a href="ident?i=nla_put_u32">nla_put_u32</a>(<a href="ident?i=skb">skb</a>, RTA_IIF, <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=dev">dev</a>-&gt;ifindex))
<a name="L2390" href="source/net/ipv4/route.c#L2390">2390</a>                                 goto nla_put_failure;
<a name="L2391" href="source/net/ipv4/route.c#L2391">2391</a>         }
<a name="L2392" href="source/net/ipv4/route.c#L2392">2392</a> 
<a name="L2393" href="source/net/ipv4/route.c#L2393">2393</a>         if (<a href="ident?i=rtnl_put_cacheinfo">rtnl_put_cacheinfo</a>(<a href="ident?i=skb">skb</a>, &amp;<a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>, 0, expires, <a href="ident?i=error">error</a>) &lt; 0)
<a name="L2394" href="source/net/ipv4/route.c#L2394">2394</a>                 goto nla_put_failure;
<a name="L2395" href="source/net/ipv4/route.c#L2395">2395</a> 
<a name="L2396" href="source/net/ipv4/route.c#L2396">2396</a>         <a href="ident?i=nlmsg_end">nlmsg_end</a>(<a href="ident?i=skb">skb</a>, nlh);
<a name="L2397" href="source/net/ipv4/route.c#L2397">2397</a>         return 0;
<a name="L2398" href="source/net/ipv4/route.c#L2398">2398</a> 
<a name="L2399" href="source/net/ipv4/route.c#L2399">2399</a> nla_put_failure:
<a name="L2400" href="source/net/ipv4/route.c#L2400">2400</a>         <a href="ident?i=nlmsg_cancel">nlmsg_cancel</a>(<a href="ident?i=skb">skb</a>, nlh);
<a name="L2401" href="source/net/ipv4/route.c#L2401">2401</a>         return -<a href="ident?i=EMSGSIZE">EMSGSIZE</a>;
<a name="L2402" href="source/net/ipv4/route.c#L2402">2402</a> }
<a name="L2403" href="source/net/ipv4/route.c#L2403">2403</a> 
<a name="L2404" href="source/net/ipv4/route.c#L2404">2404</a> static int <a href="ident?i=inet_rtm_getroute">inet_rtm_getroute</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *in_skb, struct <a href="ident?i=nlmsghdr">nlmsghdr</a> *nlh)
<a name="L2405" href="source/net/ipv4/route.c#L2405">2405</a> {
<a name="L2406" href="source/net/ipv4/route.c#L2406">2406</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=sock_net">sock_net</a>(in_skb-&gt;sk);
<a name="L2407" href="source/net/ipv4/route.c#L2407">2407</a>         struct <a href="ident?i=rtmsg">rtmsg</a> *rtm;
<a name="L2408" href="source/net/ipv4/route.c#L2408">2408</a>         struct <a href="ident?i=nlattr">nlattr</a> *<a href="ident?i=tb">tb</a>[<a href="ident?i=RTA_MAX">RTA_MAX</a>+1];
<a name="L2409" href="source/net/ipv4/route.c#L2409">2409</a>         struct <a href="ident?i=rtable">rtable</a> *<a href="ident?i=rt">rt</a> = <a href="ident?i=NULL">NULL</a>;
<a name="L2410" href="source/net/ipv4/route.c#L2410">2410</a>         struct <a href="ident?i=flowi4">flowi4</a> fl4;
<a name="L2411" href="source/net/ipv4/route.c#L2411">2411</a>         <a href="ident?i=__be32">__be32</a> <a href="ident?i=dst">dst</a> = 0;
<a name="L2412" href="source/net/ipv4/route.c#L2412">2412</a>         <a href="ident?i=__be32">__be32</a> <a href="ident?i=src">src</a> = 0;
<a name="L2413" href="source/net/ipv4/route.c#L2413">2413</a>         <a href="ident?i=u32">u32</a> iif;
<a name="L2414" href="source/net/ipv4/route.c#L2414">2414</a>         int <a href="ident?i=err">err</a>;
<a name="L2415" href="source/net/ipv4/route.c#L2415">2415</a>         int <a href="ident?i=mark">mark</a>;
<a name="L2416" href="source/net/ipv4/route.c#L2416">2416</a>         struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>;
<a name="L2417" href="source/net/ipv4/route.c#L2417">2417</a> 
<a name="L2418" href="source/net/ipv4/route.c#L2418">2418</a>         <a href="ident?i=err">err</a> = <a href="ident?i=nlmsg_parse">nlmsg_parse</a>(nlh, sizeof(*rtm), <a href="ident?i=tb">tb</a>, <a href="ident?i=RTA_MAX">RTA_MAX</a>, <a href="ident?i=rtm_ipv4_policy">rtm_ipv4_policy</a>);
<a name="L2419" href="source/net/ipv4/route.c#L2419">2419</a>         if (<a href="ident?i=err">err</a> &lt; 0)
<a name="L2420" href="source/net/ipv4/route.c#L2420">2420</a>                 goto errout;
<a name="L2421" href="source/net/ipv4/route.c#L2421">2421</a> 
<a name="L2422" href="source/net/ipv4/route.c#L2422">2422</a>         rtm = <a href="ident?i=nlmsg_data">nlmsg_data</a>(nlh);
<a name="L2423" href="source/net/ipv4/route.c#L2423">2423</a> 
<a name="L2424" href="source/net/ipv4/route.c#L2424">2424</a>         <a href="ident?i=skb">skb</a> = <a href="ident?i=alloc_skb">alloc_skb</a>(<a href="ident?i=NLMSG_GOODSIZE">NLMSG_GOODSIZE</a>, <a href="ident?i=GFP_KERNEL">GFP_KERNEL</a>);
<a name="L2425" href="source/net/ipv4/route.c#L2425">2425</a>         if (!<a href="ident?i=skb">skb</a>) {
<a name="L2426" href="source/net/ipv4/route.c#L2426">2426</a>                 <a href="ident?i=err">err</a> = -<a href="ident?i=ENOBUFS">ENOBUFS</a>;
<a name="L2427" href="source/net/ipv4/route.c#L2427">2427</a>                 goto errout;
<a name="L2428" href="source/net/ipv4/route.c#L2428">2428</a>         }
<a name="L2429" href="source/net/ipv4/route.c#L2429">2429</a> 
<a name="L2430" href="source/net/ipv4/route.c#L2430">2430</a>         <b><i>/* Reserve room for dummy headers, this skb can pass</i></b>
<a name="L2431" href="source/net/ipv4/route.c#L2431">2431</a> <b><i>           through good chunk of routing engine.</i></b>
<a name="L2432" href="source/net/ipv4/route.c#L2432">2432</a> <b><i>         */</i></b>
<a name="L2433" href="source/net/ipv4/route.c#L2433">2433</a>         <a href="ident?i=skb_reset_mac_header">skb_reset_mac_header</a>(<a href="ident?i=skb">skb</a>);
<a name="L2434" href="source/net/ipv4/route.c#L2434">2434</a>         <a href="ident?i=skb_reset_network_header">skb_reset_network_header</a>(<a href="ident?i=skb">skb</a>);
<a name="L2435" href="source/net/ipv4/route.c#L2435">2435</a> 
<a name="L2436" href="source/net/ipv4/route.c#L2436">2436</a>         <b><i>/* Bugfix: need to give ip_route_input enough of an IP header to not gag. */</i></b>
<a name="L2437" href="source/net/ipv4/route.c#L2437">2437</a>         <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=protocol">protocol</a> = <a href="ident?i=IPPROTO_ICMP">IPPROTO_ICMP</a>;
<a name="L2438" href="source/net/ipv4/route.c#L2438">2438</a>         <a href="ident?i=skb_reserve">skb_reserve</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=MAX_HEADER">MAX_HEADER</a> + sizeof(struct <a href="ident?i=iphdr">iphdr</a>));
<a name="L2439" href="source/net/ipv4/route.c#L2439">2439</a> 
<a name="L2440" href="source/net/ipv4/route.c#L2440">2440</a>         <a href="ident?i=src">src</a> = <a href="ident?i=tb">tb</a>[RTA_SRC] ? <a href="ident?i=nla_get_in_addr">nla_get_in_addr</a>(<a href="ident?i=tb">tb</a>[RTA_SRC]) : 0;
<a name="L2441" href="source/net/ipv4/route.c#L2441">2441</a>         <a href="ident?i=dst">dst</a> = <a href="ident?i=tb">tb</a>[RTA_DST] ? <a href="ident?i=nla_get_in_addr">nla_get_in_addr</a>(<a href="ident?i=tb">tb</a>[RTA_DST]) : 0;
<a name="L2442" href="source/net/ipv4/route.c#L2442">2442</a>         iif = <a href="ident?i=tb">tb</a>[RTA_IIF] ? <a href="ident?i=nla_get_u32">nla_get_u32</a>(<a href="ident?i=tb">tb</a>[RTA_IIF]) : 0;
<a name="L2443" href="source/net/ipv4/route.c#L2443">2443</a>         <a href="ident?i=mark">mark</a> = <a href="ident?i=tb">tb</a>[RTA_MARK] ? <a href="ident?i=nla_get_u32">nla_get_u32</a>(<a href="ident?i=tb">tb</a>[RTA_MARK]) : 0;
<a name="L2444" href="source/net/ipv4/route.c#L2444">2444</a> 
<a name="L2445" href="source/net/ipv4/route.c#L2445">2445</a>         <a href="ident?i=memset">memset</a>(&amp;fl4, 0, sizeof(fl4));
<a name="L2446" href="source/net/ipv4/route.c#L2446">2446</a>         fl4.<a href="ident?i=daddr">daddr</a> = <a href="ident?i=dst">dst</a>;
<a name="L2447" href="source/net/ipv4/route.c#L2447">2447</a>         fl4.<a href="ident?i=saddr">saddr</a> = <a href="ident?i=src">src</a>;
<a name="L2448" href="source/net/ipv4/route.c#L2448">2448</a>         fl4.<a href="ident?i=flowi4_tos">flowi4_tos</a> = rtm-&gt;rtm_tos;
<a name="L2449" href="source/net/ipv4/route.c#L2449">2449</a>         fl4.<a href="ident?i=flowi4_oif">flowi4_oif</a> = <a href="ident?i=tb">tb</a>[RTA_OIF] ? <a href="ident?i=nla_get_u32">nla_get_u32</a>(<a href="ident?i=tb">tb</a>[RTA_OIF]) : 0;
<a name="L2450" href="source/net/ipv4/route.c#L2450">2450</a>         fl4.<a href="ident?i=flowi4_mark">flowi4_mark</a> = <a href="ident?i=mark">mark</a>;
<a name="L2451" href="source/net/ipv4/route.c#L2451">2451</a> 
<a name="L2452" href="source/net/ipv4/route.c#L2452">2452</a>         if (iif) {
<a name="L2453" href="source/net/ipv4/route.c#L2453">2453</a>                 struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>;
<a name="L2454" href="source/net/ipv4/route.c#L2454">2454</a> 
<a name="L2455" href="source/net/ipv4/route.c#L2455">2455</a>                 <a href="ident?i=dev">dev</a> = <a href="ident?i=__dev_get_by_index">__dev_get_by_index</a>(<a href="ident?i=net">net</a>, iif);
<a name="L2456" href="source/net/ipv4/route.c#L2456">2456</a>                 if (!<a href="ident?i=dev">dev</a>) {
<a name="L2457" href="source/net/ipv4/route.c#L2457">2457</a>                         <a href="ident?i=err">err</a> = -<a href="ident?i=ENODEV">ENODEV</a>;
<a name="L2458" href="source/net/ipv4/route.c#L2458">2458</a>                         goto errout_free;
<a name="L2459" href="source/net/ipv4/route.c#L2459">2459</a>                 }
<a name="L2460" href="source/net/ipv4/route.c#L2460">2460</a> 
<a name="L2461" href="source/net/ipv4/route.c#L2461">2461</a>                 <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=protocol">protocol</a>   = <a href="ident?i=htons">htons</a>(<a href="ident?i=ETH_P_IP">ETH_P_IP</a>);
<a name="L2462" href="source/net/ipv4/route.c#L2462">2462</a>                 <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=dev">dev</a>        = <a href="ident?i=dev">dev</a>;
<a name="L2463" href="source/net/ipv4/route.c#L2463">2463</a>                 <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=mark">mark</a>       = <a href="ident?i=mark">mark</a>;
<a name="L2464" href="source/net/ipv4/route.c#L2464">2464</a>                 <a href="ident?i=local_bh_disable">local_bh_disable</a>();
<a name="L2465" href="source/net/ipv4/route.c#L2465">2465</a>                 <a href="ident?i=err">err</a> = <a href="ident?i=ip_route_input">ip_route_input</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=dst">dst</a>, <a href="ident?i=src">src</a>, rtm-&gt;rtm_tos, <a href="ident?i=dev">dev</a>);
<a name="L2466" href="source/net/ipv4/route.c#L2466">2466</a>                 <a href="ident?i=local_bh_enable">local_bh_enable</a>();
<a name="L2467" href="source/net/ipv4/route.c#L2467">2467</a> 
<a name="L2468" href="source/net/ipv4/route.c#L2468">2468</a>                 <a href="ident?i=rt">rt</a> = <a href="ident?i=skb_rtable">skb_rtable</a>(<a href="ident?i=skb">skb</a>);
<a name="L2469" href="source/net/ipv4/route.c#L2469">2469</a>                 if (<a href="ident?i=err">err</a> == 0 &amp;&amp; <a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>.<a href="ident?i=error">error</a>)
<a name="L2470" href="source/net/ipv4/route.c#L2470">2470</a>                         <a href="ident?i=err">err</a> = -<a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>.<a href="ident?i=error">error</a>;
<a name="L2471" href="source/net/ipv4/route.c#L2471">2471</a>         } else {
<a name="L2472" href="source/net/ipv4/route.c#L2472">2472</a>                 <a href="ident?i=rt">rt</a> = <a href="ident?i=ip_route_output_key">ip_route_output_key</a>(<a href="ident?i=net">net</a>, &amp;fl4);
<a name="L2473" href="source/net/ipv4/route.c#L2473">2473</a> 
<a name="L2474" href="source/net/ipv4/route.c#L2474">2474</a>                 <a href="ident?i=err">err</a> = 0;
<a name="L2475" href="source/net/ipv4/route.c#L2475">2475</a>                 if (<a href="ident?i=IS_ERR">IS_ERR</a>(<a href="ident?i=rt">rt</a>))
<a name="L2476" href="source/net/ipv4/route.c#L2476">2476</a>                         <a href="ident?i=err">err</a> = <a href="ident?i=PTR_ERR">PTR_ERR</a>(<a href="ident?i=rt">rt</a>);
<a name="L2477" href="source/net/ipv4/route.c#L2477">2477</a>         }
<a name="L2478" href="source/net/ipv4/route.c#L2478">2478</a> 
<a name="L2479" href="source/net/ipv4/route.c#L2479">2479</a>         if (<a href="ident?i=err">err</a>)
<a name="L2480" href="source/net/ipv4/route.c#L2480">2480</a>                 goto errout_free;
<a name="L2481" href="source/net/ipv4/route.c#L2481">2481</a> 
<a name="L2482" href="source/net/ipv4/route.c#L2482">2482</a>         <a href="ident?i=skb_dst_set">skb_dst_set</a>(<a href="ident?i=skb">skb</a>, &amp;<a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>);
<a name="L2483" href="source/net/ipv4/route.c#L2483">2483</a>         if (rtm-&gt;rtm_flags &amp; <a href="ident?i=RTM_F_NOTIFY">RTM_F_NOTIFY</a>)
<a name="L2484" href="source/net/ipv4/route.c#L2484">2484</a>                 <a href="ident?i=rt">rt</a>-&gt;rt_flags |= <a href="ident?i=RTCF_NOTIFY">RTCF_NOTIFY</a>;
<a name="L2485" href="source/net/ipv4/route.c#L2485">2485</a> 
<a name="L2486" href="source/net/ipv4/route.c#L2486">2486</a>         <a href="ident?i=err">err</a> = <a href="ident?i=rt_fill_info">rt_fill_info</a>(<a href="ident?i=net">net</a>, <a href="ident?i=dst">dst</a>, <a href="ident?i=src">src</a>, &amp;fl4, <a href="ident?i=skb">skb</a>,
<a name="L2487" href="source/net/ipv4/route.c#L2487">2487</a>                            <a href="ident?i=NETLINK_CB">NETLINK_CB</a>(in_skb).portid, nlh-&gt;nlmsg_seq,
<a name="L2488" href="source/net/ipv4/route.c#L2488">2488</a>                            <a href="ident?i=RTM_NEWROUTE">RTM_NEWROUTE</a>, 0, 0);
<a name="L2489" href="source/net/ipv4/route.c#L2489">2489</a>         if (<a href="ident?i=err">err</a> &lt; 0)
<a name="L2490" href="source/net/ipv4/route.c#L2490">2490</a>                 goto errout_free;
<a name="L2491" href="source/net/ipv4/route.c#L2491">2491</a> 
<a name="L2492" href="source/net/ipv4/route.c#L2492">2492</a>         <a href="ident?i=err">err</a> = <a href="ident?i=rtnl_unicast">rtnl_unicast</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=net">net</a>, <a href="ident?i=NETLINK_CB">NETLINK_CB</a>(in_skb).portid);
<a name="L2493" href="source/net/ipv4/route.c#L2493">2493</a> errout:
<a name="L2494" href="source/net/ipv4/route.c#L2494">2494</a>         return <a href="ident?i=err">err</a>;
<a name="L2495" href="source/net/ipv4/route.c#L2495">2495</a> 
<a name="L2496" href="source/net/ipv4/route.c#L2496">2496</a> errout_free:
<a name="L2497" href="source/net/ipv4/route.c#L2497">2497</a>         <a href="ident?i=kfree_skb">kfree_skb</a>(<a href="ident?i=skb">skb</a>);
<a name="L2498" href="source/net/ipv4/route.c#L2498">2498</a>         goto errout;
<a name="L2499" href="source/net/ipv4/route.c#L2499">2499</a> }
<a name="L2500" href="source/net/ipv4/route.c#L2500">2500</a> 
<a name="L2501" href="source/net/ipv4/route.c#L2501">2501</a> void <a href="ident?i=ip_rt_multicast_event">ip_rt_multicast_event</a>(struct <a href="ident?i=in_device">in_device</a> *in_dev)
<a name="L2502" href="source/net/ipv4/route.c#L2502">2502</a> {
<a name="L2503" href="source/net/ipv4/route.c#L2503">2503</a>         <a href="ident?i=rt_cache_flush">rt_cache_flush</a>(<a href="ident?i=dev_net">dev_net</a>(in_dev-&gt;<a href="ident?i=dev">dev</a>));
<a name="L2504" href="source/net/ipv4/route.c#L2504">2504</a> }
<a name="L2505" href="source/net/ipv4/route.c#L2505">2505</a> 
<a name="L2506" href="source/net/ipv4/route.c#L2506">2506</a> #ifdef CONFIG_SYSCTL
<a name="L2507" href="source/net/ipv4/route.c#L2507">2507</a> static int ip_rt_gc_timeout <a href="ident?i=__read_mostly">__read_mostly</a>       = <a href="ident?i=RT_GC_TIMEOUT">RT_GC_TIMEOUT</a>;
<a name="L2508" href="source/net/ipv4/route.c#L2508">2508</a> static int ip_rt_gc_interval <a href="ident?i=__read_mostly">__read_mostly</a>  = 60 * <a href="ident?i=HZ">HZ</a>;
<a name="L2509" href="source/net/ipv4/route.c#L2509">2509</a> static int ip_rt_gc_min_interval <a href="ident?i=__read_mostly">__read_mostly</a>  = <a href="ident?i=HZ">HZ</a> / 2;
<a name="L2510" href="source/net/ipv4/route.c#L2510">2510</a> static int ip_rt_gc_elasticity <a href="ident?i=__read_mostly">__read_mostly</a>    = 8;
<a name="L2511" href="source/net/ipv4/route.c#L2511">2511</a> 
<a name="L2512" href="source/net/ipv4/route.c#L2512">2512</a> static int <a href="ident?i=ipv4_sysctl_rtcache_flush">ipv4_sysctl_rtcache_flush</a>(struct <a href="ident?i=ctl_table">ctl_table</a> *__ctl, int <a href="ident?i=write">write</a>,
<a name="L2513" href="source/net/ipv4/route.c#L2513">2513</a>                                         void <a href="ident?i=__user">__user</a> *<a href="ident?i=buffer">buffer</a>,
<a name="L2514" href="source/net/ipv4/route.c#L2514">2514</a>                                         <a href="ident?i=size_t">size_t</a> *lenp, <a href="ident?i=loff_t">loff_t</a> *<a href="ident?i=ppos">ppos</a>)
<a name="L2515" href="source/net/ipv4/route.c#L2515">2515</a> {
<a name="L2516" href="source/net/ipv4/route.c#L2516">2516</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = (struct <a href="ident?i=net">net</a> *)__ctl-&gt;extra1;
<a name="L2517" href="source/net/ipv4/route.c#L2517">2517</a> 
<a name="L2518" href="source/net/ipv4/route.c#L2518">2518</a>         if (<a href="ident?i=write">write</a>) {
<a name="L2519" href="source/net/ipv4/route.c#L2519">2519</a>                 <a href="ident?i=rt_cache_flush">rt_cache_flush</a>(<a href="ident?i=net">net</a>);
<a name="L2520" href="source/net/ipv4/route.c#L2520">2520</a>                 <a href="ident?i=fnhe_genid_bump">fnhe_genid_bump</a>(<a href="ident?i=net">net</a>);
<a name="L2521" href="source/net/ipv4/route.c#L2521">2521</a>                 return 0;
<a name="L2522" href="source/net/ipv4/route.c#L2522">2522</a>         }
<a name="L2523" href="source/net/ipv4/route.c#L2523">2523</a> 
<a name="L2524" href="source/net/ipv4/route.c#L2524">2524</a>         return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L2525" href="source/net/ipv4/route.c#L2525">2525</a> }
<a name="L2526" href="source/net/ipv4/route.c#L2526">2526</a> 
<a name="L2527" href="source/net/ipv4/route.c#L2527">2527</a> static struct <a href="ident?i=ctl_table">ctl_table</a> <a href="ident?i=ipv4_route_table">ipv4_route_table</a>[] = {
<a name="L2528" href="source/net/ipv4/route.c#L2528">2528</a>         {
<a name="L2529" href="source/net/ipv4/route.c#L2529">2529</a>                 .<a href="ident?i=procname">procname</a>       = <i>"gc_thresh"</i>,
<a name="L2530" href="source/net/ipv4/route.c#L2530">2530</a>                 .<a href="ident?i=data">data</a>           = &amp;<a href="ident?i=ipv4_dst_ops">ipv4_dst_ops</a>.gc_thresh,
<a name="L2531" href="source/net/ipv4/route.c#L2531">2531</a>                 .maxlen         = sizeof(int),
<a name="L2532" href="source/net/ipv4/route.c#L2532">2532</a>                 .<a href="ident?i=mode">mode</a>           = 0644,
<a name="L2533" href="source/net/ipv4/route.c#L2533">2533</a>                 .<a href="ident?i=proc_handler">proc_handler</a>   = <a href="ident?i=proc_dointvec">proc_dointvec</a>,
<a name="L2534" href="source/net/ipv4/route.c#L2534">2534</a>         },
<a name="L2535" href="source/net/ipv4/route.c#L2535">2535</a>         {
<a name="L2536" href="source/net/ipv4/route.c#L2536">2536</a>                 .<a href="ident?i=procname">procname</a>       = <i>"max_size"</i>,
<a name="L2537" href="source/net/ipv4/route.c#L2537">2537</a>                 .<a href="ident?i=data">data</a>           = &amp;<a href="ident?i=ip_rt_max_size">ip_rt_max_size</a>,
<a name="L2538" href="source/net/ipv4/route.c#L2538">2538</a>                 .maxlen         = sizeof(int),
<a name="L2539" href="source/net/ipv4/route.c#L2539">2539</a>                 .<a href="ident?i=mode">mode</a>           = 0644,
<a name="L2540" href="source/net/ipv4/route.c#L2540">2540</a>                 .<a href="ident?i=proc_handler">proc_handler</a>   = <a href="ident?i=proc_dointvec">proc_dointvec</a>,
<a name="L2541" href="source/net/ipv4/route.c#L2541">2541</a>         },
<a name="L2542" href="source/net/ipv4/route.c#L2542">2542</a>         {
<a name="L2543" href="source/net/ipv4/route.c#L2543">2543</a>                 <b><i>/*  Deprecated. Use gc_min_interval_ms */</i></b>
<a name="L2544" href="source/net/ipv4/route.c#L2544">2544</a> 
<a name="L2545" href="source/net/ipv4/route.c#L2545">2545</a>                 .<a href="ident?i=procname">procname</a>       = <i>"gc_min_interval"</i>,
<a name="L2546" href="source/net/ipv4/route.c#L2546">2546</a>                 .<a href="ident?i=data">data</a>           = &amp;ip_rt_gc_min_interval,
<a name="L2547" href="source/net/ipv4/route.c#L2547">2547</a>                 .maxlen         = sizeof(int),
<a name="L2548" href="source/net/ipv4/route.c#L2548">2548</a>                 .<a href="ident?i=mode">mode</a>           = 0644,
<a name="L2549" href="source/net/ipv4/route.c#L2549">2549</a>                 .<a href="ident?i=proc_handler">proc_handler</a>   = <a href="ident?i=proc_dointvec_jiffies">proc_dointvec_jiffies</a>,
<a name="L2550" href="source/net/ipv4/route.c#L2550">2550</a>         },
<a name="L2551" href="source/net/ipv4/route.c#L2551">2551</a>         {
<a name="L2552" href="source/net/ipv4/route.c#L2552">2552</a>                 .<a href="ident?i=procname">procname</a>       = <i>"gc_min_interval_ms"</i>,
<a name="L2553" href="source/net/ipv4/route.c#L2553">2553</a>                 .<a href="ident?i=data">data</a>           = &amp;ip_rt_gc_min_interval,
<a name="L2554" href="source/net/ipv4/route.c#L2554">2554</a>                 .maxlen         = sizeof(int),
<a name="L2555" href="source/net/ipv4/route.c#L2555">2555</a>                 .<a href="ident?i=mode">mode</a>           = 0644,
<a name="L2556" href="source/net/ipv4/route.c#L2556">2556</a>                 .<a href="ident?i=proc_handler">proc_handler</a>   = <a href="ident?i=proc_dointvec_ms_jiffies">proc_dointvec_ms_jiffies</a>,
<a name="L2557" href="source/net/ipv4/route.c#L2557">2557</a>         },
<a name="L2558" href="source/net/ipv4/route.c#L2558">2558</a>         {
<a name="L2559" href="source/net/ipv4/route.c#L2559">2559</a>                 .<a href="ident?i=procname">procname</a>       = <i>"gc_timeout"</i>,
<a name="L2560" href="source/net/ipv4/route.c#L2560">2560</a>                 .<a href="ident?i=data">data</a>           = &amp;ip_rt_gc_timeout,
<a name="L2561" href="source/net/ipv4/route.c#L2561">2561</a>                 .maxlen         = sizeof(int),
<a name="L2562" href="source/net/ipv4/route.c#L2562">2562</a>                 .<a href="ident?i=mode">mode</a>           = 0644,
<a name="L2563" href="source/net/ipv4/route.c#L2563">2563</a>                 .<a href="ident?i=proc_handler">proc_handler</a>   = <a href="ident?i=proc_dointvec_jiffies">proc_dointvec_jiffies</a>,
<a name="L2564" href="source/net/ipv4/route.c#L2564">2564</a>         },
<a name="L2565" href="source/net/ipv4/route.c#L2565">2565</a>         {
<a name="L2566" href="source/net/ipv4/route.c#L2566">2566</a>                 .<a href="ident?i=procname">procname</a>       = <i>"gc_interval"</i>,
<a name="L2567" href="source/net/ipv4/route.c#L2567">2567</a>                 .<a href="ident?i=data">data</a>           = &amp;ip_rt_gc_interval,
<a name="L2568" href="source/net/ipv4/route.c#L2568">2568</a>                 .maxlen         = sizeof(int),
<a name="L2569" href="source/net/ipv4/route.c#L2569">2569</a>                 .<a href="ident?i=mode">mode</a>           = 0644,
<a name="L2570" href="source/net/ipv4/route.c#L2570">2570</a>                 .<a href="ident?i=proc_handler">proc_handler</a>   = <a href="ident?i=proc_dointvec_jiffies">proc_dointvec_jiffies</a>,
<a name="L2571" href="source/net/ipv4/route.c#L2571">2571</a>         },
<a name="L2572" href="source/net/ipv4/route.c#L2572">2572</a>         {
<a name="L2573" href="source/net/ipv4/route.c#L2573">2573</a>                 .<a href="ident?i=procname">procname</a>       = <i>"redirect_load"</i>,
<a name="L2574" href="source/net/ipv4/route.c#L2574">2574</a>                 .<a href="ident?i=data">data</a>           = &amp;ip_rt_redirect_load,
<a name="L2575" href="source/net/ipv4/route.c#L2575">2575</a>                 .maxlen         = sizeof(int),
<a name="L2576" href="source/net/ipv4/route.c#L2576">2576</a>                 .<a href="ident?i=mode">mode</a>           = 0644,
<a name="L2577" href="source/net/ipv4/route.c#L2577">2577</a>                 .<a href="ident?i=proc_handler">proc_handler</a>   = <a href="ident?i=proc_dointvec">proc_dointvec</a>,
<a name="L2578" href="source/net/ipv4/route.c#L2578">2578</a>         },
<a name="L2579" href="source/net/ipv4/route.c#L2579">2579</a>         {
<a name="L2580" href="source/net/ipv4/route.c#L2580">2580</a>                 .<a href="ident?i=procname">procname</a>       = <i>"redirect_number"</i>,
<a name="L2581" href="source/net/ipv4/route.c#L2581">2581</a>                 .<a href="ident?i=data">data</a>           = &amp;ip_rt_redirect_number,
<a name="L2582" href="source/net/ipv4/route.c#L2582">2582</a>                 .maxlen         = sizeof(int),
<a name="L2583" href="source/net/ipv4/route.c#L2583">2583</a>                 .<a href="ident?i=mode">mode</a>           = 0644,
<a name="L2584" href="source/net/ipv4/route.c#L2584">2584</a>                 .<a href="ident?i=proc_handler">proc_handler</a>   = <a href="ident?i=proc_dointvec">proc_dointvec</a>,
<a name="L2585" href="source/net/ipv4/route.c#L2585">2585</a>         },
<a name="L2586" href="source/net/ipv4/route.c#L2586">2586</a>         {
<a name="L2587" href="source/net/ipv4/route.c#L2587">2587</a>                 .<a href="ident?i=procname">procname</a>       = <i>"redirect_silence"</i>,
<a name="L2588" href="source/net/ipv4/route.c#L2588">2588</a>                 .<a href="ident?i=data">data</a>           = &amp;ip_rt_redirect_silence,
<a name="L2589" href="source/net/ipv4/route.c#L2589">2589</a>                 .maxlen         = sizeof(int),
<a name="L2590" href="source/net/ipv4/route.c#L2590">2590</a>                 .<a href="ident?i=mode">mode</a>           = 0644,
<a name="L2591" href="source/net/ipv4/route.c#L2591">2591</a>                 .<a href="ident?i=proc_handler">proc_handler</a>   = <a href="ident?i=proc_dointvec">proc_dointvec</a>,
<a name="L2592" href="source/net/ipv4/route.c#L2592">2592</a>         },
<a name="L2593" href="source/net/ipv4/route.c#L2593">2593</a>         {
<a name="L2594" href="source/net/ipv4/route.c#L2594">2594</a>                 .<a href="ident?i=procname">procname</a>       = <i>"error_cost"</i>,
<a name="L2595" href="source/net/ipv4/route.c#L2595">2595</a>                 .<a href="ident?i=data">data</a>           = &amp;ip_rt_error_cost,
<a name="L2596" href="source/net/ipv4/route.c#L2596">2596</a>                 .maxlen         = sizeof(int),
<a name="L2597" href="source/net/ipv4/route.c#L2597">2597</a>                 .<a href="ident?i=mode">mode</a>           = 0644,
<a name="L2598" href="source/net/ipv4/route.c#L2598">2598</a>                 .<a href="ident?i=proc_handler">proc_handler</a>   = <a href="ident?i=proc_dointvec">proc_dointvec</a>,
<a name="L2599" href="source/net/ipv4/route.c#L2599">2599</a>         },
<a name="L2600" href="source/net/ipv4/route.c#L2600">2600</a>         {
<a name="L2601" href="source/net/ipv4/route.c#L2601">2601</a>                 .<a href="ident?i=procname">procname</a>       = <i>"error_burst"</i>,
<a name="L2602" href="source/net/ipv4/route.c#L2602">2602</a>                 .<a href="ident?i=data">data</a>           = &amp;ip_rt_error_burst,
<a name="L2603" href="source/net/ipv4/route.c#L2603">2603</a>                 .maxlen         = sizeof(int),
<a name="L2604" href="source/net/ipv4/route.c#L2604">2604</a>                 .<a href="ident?i=mode">mode</a>           = 0644,
<a name="L2605" href="source/net/ipv4/route.c#L2605">2605</a>                 .<a href="ident?i=proc_handler">proc_handler</a>   = <a href="ident?i=proc_dointvec">proc_dointvec</a>,
<a name="L2606" href="source/net/ipv4/route.c#L2606">2606</a>         },
<a name="L2607" href="source/net/ipv4/route.c#L2607">2607</a>         {
<a name="L2608" href="source/net/ipv4/route.c#L2608">2608</a>                 .<a href="ident?i=procname">procname</a>       = <i>"gc_elasticity"</i>,
<a name="L2609" href="source/net/ipv4/route.c#L2609">2609</a>                 .<a href="ident?i=data">data</a>           = &amp;ip_rt_gc_elasticity,
<a name="L2610" href="source/net/ipv4/route.c#L2610">2610</a>                 .maxlen         = sizeof(int),
<a name="L2611" href="source/net/ipv4/route.c#L2611">2611</a>                 .<a href="ident?i=mode">mode</a>           = 0644,
<a name="L2612" href="source/net/ipv4/route.c#L2612">2612</a>                 .<a href="ident?i=proc_handler">proc_handler</a>   = <a href="ident?i=proc_dointvec">proc_dointvec</a>,
<a name="L2613" href="source/net/ipv4/route.c#L2613">2613</a>         },
<a name="L2614" href="source/net/ipv4/route.c#L2614">2614</a>         {
<a name="L2615" href="source/net/ipv4/route.c#L2615">2615</a>                 .<a href="ident?i=procname">procname</a>       = <i>"mtu_expires"</i>,
<a name="L2616" href="source/net/ipv4/route.c#L2616">2616</a>                 .<a href="ident?i=data">data</a>           = &amp;ip_rt_mtu_expires,
<a name="L2617" href="source/net/ipv4/route.c#L2617">2617</a>                 .maxlen         = sizeof(int),
<a name="L2618" href="source/net/ipv4/route.c#L2618">2618</a>                 .<a href="ident?i=mode">mode</a>           = 0644,
<a name="L2619" href="source/net/ipv4/route.c#L2619">2619</a>                 .<a href="ident?i=proc_handler">proc_handler</a>   = <a href="ident?i=proc_dointvec_jiffies">proc_dointvec_jiffies</a>,
<a name="L2620" href="source/net/ipv4/route.c#L2620">2620</a>         },
<a name="L2621" href="source/net/ipv4/route.c#L2621">2621</a>         {
<a name="L2622" href="source/net/ipv4/route.c#L2622">2622</a>                 .<a href="ident?i=procname">procname</a>       = <i>"min_pmtu"</i>,
<a name="L2623" href="source/net/ipv4/route.c#L2623">2623</a>                 .<a href="ident?i=data">data</a>           = &amp;ip_rt_min_pmtu,
<a name="L2624" href="source/net/ipv4/route.c#L2624">2624</a>                 .maxlen         = sizeof(int),
<a name="L2625" href="source/net/ipv4/route.c#L2625">2625</a>                 .<a href="ident?i=mode">mode</a>           = 0644,
<a name="L2626" href="source/net/ipv4/route.c#L2626">2626</a>                 .<a href="ident?i=proc_handler">proc_handler</a>   = <a href="ident?i=proc_dointvec">proc_dointvec</a>,
<a name="L2627" href="source/net/ipv4/route.c#L2627">2627</a>         },
<a name="L2628" href="source/net/ipv4/route.c#L2628">2628</a>         {
<a name="L2629" href="source/net/ipv4/route.c#L2629">2629</a>                 .<a href="ident?i=procname">procname</a>       = <i>"min_adv_mss"</i>,
<a name="L2630" href="source/net/ipv4/route.c#L2630">2630</a>                 .<a href="ident?i=data">data</a>           = &amp;ip_rt_min_advmss,
<a name="L2631" href="source/net/ipv4/route.c#L2631">2631</a>                 .maxlen         = sizeof(int),
<a name="L2632" href="source/net/ipv4/route.c#L2632">2632</a>                 .<a href="ident?i=mode">mode</a>           = 0644,
<a name="L2633" href="source/net/ipv4/route.c#L2633">2633</a>                 .<a href="ident?i=proc_handler">proc_handler</a>   = <a href="ident?i=proc_dointvec">proc_dointvec</a>,
<a name="L2634" href="source/net/ipv4/route.c#L2634">2634</a>         },
<a name="L2635" href="source/net/ipv4/route.c#L2635">2635</a>         { }
<a name="L2636" href="source/net/ipv4/route.c#L2636">2636</a> };
<a name="L2637" href="source/net/ipv4/route.c#L2637">2637</a> 
<a name="L2638" href="source/net/ipv4/route.c#L2638">2638</a> static struct <a href="ident?i=ctl_table">ctl_table</a> <a href="ident?i=ipv4_route_flush_table">ipv4_route_flush_table</a>[] = {
<a name="L2639" href="source/net/ipv4/route.c#L2639">2639</a>         {
<a name="L2640" href="source/net/ipv4/route.c#L2640">2640</a>                 .<a href="ident?i=procname">procname</a>       = <i>"flush"</i>,
<a name="L2641" href="source/net/ipv4/route.c#L2641">2641</a>                 .maxlen         = sizeof(int),
<a name="L2642" href="source/net/ipv4/route.c#L2642">2642</a>                 .<a href="ident?i=mode">mode</a>           = 0200,
<a name="L2643" href="source/net/ipv4/route.c#L2643">2643</a>                 .<a href="ident?i=proc_handler">proc_handler</a>   = <a href="ident?i=ipv4_sysctl_rtcache_flush">ipv4_sysctl_rtcache_flush</a>,
<a name="L2644" href="source/net/ipv4/route.c#L2644">2644</a>         },
<a name="L2645" href="source/net/ipv4/route.c#L2645">2645</a>         { },
<a name="L2646" href="source/net/ipv4/route.c#L2646">2646</a> };
<a name="L2647" href="source/net/ipv4/route.c#L2647">2647</a> 
<a name="L2648" href="source/net/ipv4/route.c#L2648">2648</a> static <a href="ident?i=__net_init">__net_init</a> int <a href="ident?i=sysctl_route_net_init">sysctl_route_net_init</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>)
<a name="L2649" href="source/net/ipv4/route.c#L2649">2649</a> {
<a name="L2650" href="source/net/ipv4/route.c#L2650">2650</a>         struct <a href="ident?i=ctl_table">ctl_table</a> *tbl;
<a name="L2651" href="source/net/ipv4/route.c#L2651">2651</a> 
<a name="L2652" href="source/net/ipv4/route.c#L2652">2652</a>         tbl = <a href="ident?i=ipv4_route_flush_table">ipv4_route_flush_table</a>;
<a name="L2653" href="source/net/ipv4/route.c#L2653">2653</a>         if (!<a href="ident?i=net_eq">net_eq</a>(<a href="ident?i=net">net</a>, &amp;<a href="ident?i=init_net">init_net</a>)) {
<a name="L2654" href="source/net/ipv4/route.c#L2654">2654</a>                 tbl = <a href="ident?i=kmemdup">kmemdup</a>(tbl, sizeof(<a href="ident?i=ipv4_route_flush_table">ipv4_route_flush_table</a>), <a href="ident?i=GFP_KERNEL">GFP_KERNEL</a>);
<a name="L2655" href="source/net/ipv4/route.c#L2655">2655</a>                 if (!tbl)
<a name="L2656" href="source/net/ipv4/route.c#L2656">2656</a>                         goto err_dup;
<a name="L2657" href="source/net/ipv4/route.c#L2657">2657</a> 
<a name="L2658" href="source/net/ipv4/route.c#L2658">2658</a>                 <b><i>/* Don't export sysctls to unprivileged users */</i></b>
<a name="L2659" href="source/net/ipv4/route.c#L2659">2659</a>                 if (<a href="ident?i=net">net</a>-&gt;<a href="ident?i=user_ns">user_ns</a> != &amp;<a href="ident?i=init_user_ns">init_user_ns</a>)
<a name="L2660" href="source/net/ipv4/route.c#L2660">2660</a>                         tbl[0].<a href="ident?i=procname">procname</a> = <a href="ident?i=NULL">NULL</a>;
<a name="L2661" href="source/net/ipv4/route.c#L2661">2661</a>         }
<a name="L2662" href="source/net/ipv4/route.c#L2662">2662</a>         tbl[0].extra1 = <a href="ident?i=net">net</a>;
<a name="L2663" href="source/net/ipv4/route.c#L2663">2663</a> 
<a name="L2664" href="source/net/ipv4/route.c#L2664">2664</a>         <a href="ident?i=net">net</a>-&gt;ipv4.route_hdr = <a href="ident?i=register_net_sysctl">register_net_sysctl</a>(<a href="ident?i=net">net</a>, <i>"net/ipv4/route"</i>, tbl);
<a name="L2665" href="source/net/ipv4/route.c#L2665">2665</a>         if (!<a href="ident?i=net">net</a>-&gt;ipv4.route_hdr)
<a name="L2666" href="source/net/ipv4/route.c#L2666">2666</a>                 goto err_reg;
<a name="L2667" href="source/net/ipv4/route.c#L2667">2667</a>         return 0;
<a name="L2668" href="source/net/ipv4/route.c#L2668">2668</a> 
<a name="L2669" href="source/net/ipv4/route.c#L2669">2669</a> err_reg:
<a name="L2670" href="source/net/ipv4/route.c#L2670">2670</a>         if (tbl != <a href="ident?i=ipv4_route_flush_table">ipv4_route_flush_table</a>)
<a name="L2671" href="source/net/ipv4/route.c#L2671">2671</a>                 <a href="ident?i=kfree">kfree</a>(tbl);
<a name="L2672" href="source/net/ipv4/route.c#L2672">2672</a> err_dup:
<a name="L2673" href="source/net/ipv4/route.c#L2673">2673</a>         return -<a href="ident?i=ENOMEM">ENOMEM</a>;
<a name="L2674" href="source/net/ipv4/route.c#L2674">2674</a> }
<a name="L2675" href="source/net/ipv4/route.c#L2675">2675</a> 
<a name="L2676" href="source/net/ipv4/route.c#L2676">2676</a> static <a href="ident?i=__net_exit">__net_exit</a> void <a href="ident?i=sysctl_route_net_exit">sysctl_route_net_exit</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>)
<a name="L2677" href="source/net/ipv4/route.c#L2677">2677</a> {
<a name="L2678" href="source/net/ipv4/route.c#L2678">2678</a>         struct <a href="ident?i=ctl_table">ctl_table</a> *tbl;
<a name="L2679" href="source/net/ipv4/route.c#L2679">2679</a> 
<a name="L2680" href="source/net/ipv4/route.c#L2680">2680</a>         tbl = <a href="ident?i=net">net</a>-&gt;ipv4.route_hdr-&gt;ctl_table_arg;
<a name="L2681" href="source/net/ipv4/route.c#L2681">2681</a>         <a href="ident?i=unregister_net_sysctl_table">unregister_net_sysctl_table</a>(<a href="ident?i=net">net</a>-&gt;ipv4.route_hdr);
<a name="L2682" href="source/net/ipv4/route.c#L2682">2682</a>         <a href="ident?i=BUG_ON">BUG_ON</a>(tbl == <a href="ident?i=ipv4_route_flush_table">ipv4_route_flush_table</a>);
<a name="L2683" href="source/net/ipv4/route.c#L2683">2683</a>         <a href="ident?i=kfree">kfree</a>(tbl);
<a name="L2684" href="source/net/ipv4/route.c#L2684">2684</a> }
<a name="L2685" href="source/net/ipv4/route.c#L2685">2685</a> 
<a name="L2686" href="source/net/ipv4/route.c#L2686">2686</a> static <a href="ident?i=__net_initdata">__net_initdata</a> struct <a href="ident?i=pernet_operations">pernet_operations</a> <a href="ident?i=sysctl_route_ops">sysctl_route_ops</a> = {
<a name="L2687" href="source/net/ipv4/route.c#L2687">2687</a>         .<a href="ident?i=init">init</a> = <a href="ident?i=sysctl_route_net_init">sysctl_route_net_init</a>,
<a name="L2688" href="source/net/ipv4/route.c#L2688">2688</a>         .<a href="ident?i=exit">exit</a> = <a href="ident?i=sysctl_route_net_exit">sysctl_route_net_exit</a>,
<a name="L2689" href="source/net/ipv4/route.c#L2689">2689</a> };
<a name="L2690" href="source/net/ipv4/route.c#L2690">2690</a> #endif
<a name="L2691" href="source/net/ipv4/route.c#L2691">2691</a> 
<a name="L2692" href="source/net/ipv4/route.c#L2692">2692</a> static <a href="ident?i=__net_init">__net_init</a> int <a href="ident?i=rt_genid_init">rt_genid_init</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>)
<a name="L2693" href="source/net/ipv4/route.c#L2693">2693</a> {
<a name="L2694" href="source/net/ipv4/route.c#L2694">2694</a>         <a href="ident?i=atomic_set">atomic_set</a>(&amp;<a href="ident?i=net">net</a>-&gt;ipv4.rt_genid, 0);
<a name="L2695" href="source/net/ipv4/route.c#L2695">2695</a>         <a href="ident?i=atomic_set">atomic_set</a>(&amp;<a href="ident?i=net">net</a>-&gt;<a href="ident?i=fnhe_genid">fnhe_genid</a>, 0);
<a name="L2696" href="source/net/ipv4/route.c#L2696">2696</a>         <a href="ident?i=get_random_bytes">get_random_bytes</a>(&amp;<a href="ident?i=net">net</a>-&gt;ipv4.dev_addr_genid,
<a name="L2697" href="source/net/ipv4/route.c#L2697">2697</a>                          sizeof(<a href="ident?i=net">net</a>-&gt;ipv4.dev_addr_genid));
<a name="L2698" href="source/net/ipv4/route.c#L2698">2698</a>         return 0;
<a name="L2699" href="source/net/ipv4/route.c#L2699">2699</a> }
<a name="L2700" href="source/net/ipv4/route.c#L2700">2700</a> 
<a name="L2701" href="source/net/ipv4/route.c#L2701">2701</a> static <a href="ident?i=__net_initdata">__net_initdata</a> struct <a href="ident?i=pernet_operations">pernet_operations</a> <a href="ident?i=rt_genid_ops">rt_genid_ops</a> = {
<a name="L2702" href="source/net/ipv4/route.c#L2702">2702</a>         .<a href="ident?i=init">init</a> = <a href="ident?i=rt_genid_init">rt_genid_init</a>,
<a name="L2703" href="source/net/ipv4/route.c#L2703">2703</a> };
<a name="L2704" href="source/net/ipv4/route.c#L2704">2704</a> 
<a name="L2705" href="source/net/ipv4/route.c#L2705">2705</a> static int <a href="ident?i=__net_init">__net_init</a> <a href="ident?i=ipv4_inetpeer_init">ipv4_inetpeer_init</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>)
<a name="L2706" href="source/net/ipv4/route.c#L2706">2706</a> {
<a name="L2707" href="source/net/ipv4/route.c#L2707">2707</a>         struct <a href="ident?i=inet_peer_base">inet_peer_base</a> *bp = <a href="ident?i=kmalloc">kmalloc</a>(sizeof(*bp), <a href="ident?i=GFP_KERNEL">GFP_KERNEL</a>);
<a name="L2708" href="source/net/ipv4/route.c#L2708">2708</a> 
<a name="L2709" href="source/net/ipv4/route.c#L2709">2709</a>         if (!bp)
<a name="L2710" href="source/net/ipv4/route.c#L2710">2710</a>                 return -<a href="ident?i=ENOMEM">ENOMEM</a>;
<a name="L2711" href="source/net/ipv4/route.c#L2711">2711</a>         <a href="ident?i=inet_peer_base_init">inet_peer_base_init</a>(bp);
<a name="L2712" href="source/net/ipv4/route.c#L2712">2712</a>         <a href="ident?i=net">net</a>-&gt;ipv4.peers = bp;
<a name="L2713" href="source/net/ipv4/route.c#L2713">2713</a>         return 0;
<a name="L2714" href="source/net/ipv4/route.c#L2714">2714</a> }
<a name="L2715" href="source/net/ipv4/route.c#L2715">2715</a> 
<a name="L2716" href="source/net/ipv4/route.c#L2716">2716</a> static void <a href="ident?i=__net_exit">__net_exit</a> <a href="ident?i=ipv4_inetpeer_exit">ipv4_inetpeer_exit</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>)
<a name="L2717" href="source/net/ipv4/route.c#L2717">2717</a> {
<a name="L2718" href="source/net/ipv4/route.c#L2718">2718</a>         struct <a href="ident?i=inet_peer_base">inet_peer_base</a> *bp = <a href="ident?i=net">net</a>-&gt;ipv4.peers;
<a name="L2719" href="source/net/ipv4/route.c#L2719">2719</a> 
<a name="L2720" href="source/net/ipv4/route.c#L2720">2720</a>         <a href="ident?i=net">net</a>-&gt;ipv4.peers = <a href="ident?i=NULL">NULL</a>;
<a name="L2721" href="source/net/ipv4/route.c#L2721">2721</a>         <a href="ident?i=inetpeer_invalidate_tree">inetpeer_invalidate_tree</a>(bp);
<a name="L2722" href="source/net/ipv4/route.c#L2722">2722</a>         <a href="ident?i=kfree">kfree</a>(bp);
<a name="L2723" href="source/net/ipv4/route.c#L2723">2723</a> }
<a name="L2724" href="source/net/ipv4/route.c#L2724">2724</a> 
<a name="L2725" href="source/net/ipv4/route.c#L2725">2725</a> static <a href="ident?i=__net_initdata">__net_initdata</a> struct <a href="ident?i=pernet_operations">pernet_operations</a> <a href="ident?i=ipv4_inetpeer_ops">ipv4_inetpeer_ops</a> = {
<a name="L2726" href="source/net/ipv4/route.c#L2726">2726</a>         .<a href="ident?i=init">init</a>   =       <a href="ident?i=ipv4_inetpeer_init">ipv4_inetpeer_init</a>,
<a name="L2727" href="source/net/ipv4/route.c#L2727">2727</a>         .<a href="ident?i=exit">exit</a>   =       <a href="ident?i=ipv4_inetpeer_exit">ipv4_inetpeer_exit</a>,
<a name="L2728" href="source/net/ipv4/route.c#L2728">2728</a> };
<a name="L2729" href="source/net/ipv4/route.c#L2729">2729</a> 
<a name="L2730" href="source/net/ipv4/route.c#L2730">2730</a> #ifdef CONFIG_IP_ROUTE_CLASSID
<a name="L2731" href="source/net/ipv4/route.c#L2731">2731</a> struct <a href="ident?i=ip_rt_acct">ip_rt_acct</a> <a href="ident?i=__percpu">__percpu</a> *<a href="ident?i=ip_rt_acct">ip_rt_acct</a> <a href="ident?i=__read_mostly">__read_mostly</a>;
<a name="L2732" href="source/net/ipv4/route.c#L2732">2732</a> #endif <b><i>/* CONFIG_IP_ROUTE_CLASSID */</i></b>
<a name="L2733" href="source/net/ipv4/route.c#L2733">2733</a> 
<a name="L2734" href="source/net/ipv4/route.c#L2734">2734</a> int <a href="ident?i=__init">__init</a> <a href="ident?i=ip_rt_init">ip_rt_init</a>(void)
<a name="L2735" href="source/net/ipv4/route.c#L2735">2735</a> {
<a name="L2736" href="source/net/ipv4/route.c#L2736">2736</a>         int <a href="ident?i=rc">rc</a> = 0;
<a name="L2737" href="source/net/ipv4/route.c#L2737">2737</a>         int <a href="ident?i=cpu">cpu</a>;
<a name="L2738" href="source/net/ipv4/route.c#L2738">2738</a> 
<a name="L2739" href="source/net/ipv4/route.c#L2739">2739</a>         ip_idents = <a href="ident?i=kmalloc">kmalloc</a>(<a href="ident?i=IP_IDENTS_SZ">IP_IDENTS_SZ</a> * sizeof(*ip_idents), <a href="ident?i=GFP_KERNEL">GFP_KERNEL</a>);
<a name="L2740" href="source/net/ipv4/route.c#L2740">2740</a>         if (!ip_idents)
<a name="L2741" href="source/net/ipv4/route.c#L2741">2741</a>                 <a href="ident?i=panic">panic</a>(<i>"IP: failed to allocate ip_idents\n"</i>);
<a name="L2742" href="source/net/ipv4/route.c#L2742">2742</a> 
<a name="L2743" href="source/net/ipv4/route.c#L2743">2743</a>         <a href="ident?i=prandom_bytes">prandom_bytes</a>(ip_idents, <a href="ident?i=IP_IDENTS_SZ">IP_IDENTS_SZ</a> * sizeof(*ip_idents));
<a name="L2744" href="source/net/ipv4/route.c#L2744">2744</a> 
<a name="L2745" href="source/net/ipv4/route.c#L2745">2745</a>         <a href="ident?i=for_each_possible_cpu">for_each_possible_cpu</a>(<a href="ident?i=cpu">cpu</a>) {
<a name="L2746" href="source/net/ipv4/route.c#L2746">2746</a>                 struct <a href="ident?i=uncached_list">uncached_list</a> *ul = &amp;<a href="ident?i=per_cpu">per_cpu</a>(rt_uncached_list, <a href="ident?i=cpu">cpu</a>);
<a name="L2747" href="source/net/ipv4/route.c#L2747">2747</a> 
<a name="L2748" href="source/net/ipv4/route.c#L2748">2748</a>                 <a href="ident?i=INIT_LIST_HEAD">INIT_LIST_HEAD</a>(&amp;ul-&gt;<a href="ident?i=head">head</a>);
<a name="L2749" href="source/net/ipv4/route.c#L2749">2749</a>                 <a href="ident?i=spin_lock_init">spin_lock_init</a>(&amp;ul-&gt;<a href="ident?i=lock">lock</a>);
<a name="L2750" href="source/net/ipv4/route.c#L2750">2750</a>         }
<a name="L2751" href="source/net/ipv4/route.c#L2751">2751</a> #ifdef CONFIG_IP_ROUTE_CLASSID
<a name="L2752" href="source/net/ipv4/route.c#L2752">2752</a>         <a href="ident?i=ip_rt_acct">ip_rt_acct</a> = <a href="ident?i=__alloc_percpu">__alloc_percpu</a>(256 * sizeof(struct <a href="ident?i=ip_rt_acct">ip_rt_acct</a>), __alignof__(struct <a href="ident?i=ip_rt_acct">ip_rt_acct</a>));
<a name="L2753" href="source/net/ipv4/route.c#L2753">2753</a>         if (!<a href="ident?i=ip_rt_acct">ip_rt_acct</a>)
<a name="L2754" href="source/net/ipv4/route.c#L2754">2754</a>                 <a href="ident?i=panic">panic</a>(<i>"IP: failed to allocate ip_rt_acct\n"</i>);
<a name="L2755" href="source/net/ipv4/route.c#L2755">2755</a> #endif
<a name="L2756" href="source/net/ipv4/route.c#L2756">2756</a> 
<a name="L2757" href="source/net/ipv4/route.c#L2757">2757</a>         <a href="ident?i=ipv4_dst_ops">ipv4_dst_ops</a>.<a href="ident?i=kmem_cachep">kmem_cachep</a> =
<a name="L2758" href="source/net/ipv4/route.c#L2758">2758</a>                 <a href="ident?i=kmem_cache_create">kmem_cache_create</a>(<i>"ip_dst_cache"</i>, sizeof(struct <a href="ident?i=rtable">rtable</a>), 0,
<a name="L2759" href="source/net/ipv4/route.c#L2759">2759</a>                                   <a href="ident?i=SLAB_HWCACHE_ALIGN">SLAB_HWCACHE_ALIGN</a>|<a href="ident?i=SLAB_PANIC">SLAB_PANIC</a>, <a href="ident?i=NULL">NULL</a>);
<a name="L2760" href="source/net/ipv4/route.c#L2760">2760</a> 
<a name="L2761" href="source/net/ipv4/route.c#L2761">2761</a>         <a href="ident?i=ipv4_dst_blackhole_ops">ipv4_dst_blackhole_ops</a>.<a href="ident?i=kmem_cachep">kmem_cachep</a> = <a href="ident?i=ipv4_dst_ops">ipv4_dst_ops</a>.<a href="ident?i=kmem_cachep">kmem_cachep</a>;
<a name="L2762" href="source/net/ipv4/route.c#L2762">2762</a> 
<a name="L2763" href="source/net/ipv4/route.c#L2763">2763</a>         if (<a href="ident?i=dst_entries_init">dst_entries_init</a>(&amp;<a href="ident?i=ipv4_dst_ops">ipv4_dst_ops</a>) &lt; 0)
<a name="L2764" href="source/net/ipv4/route.c#L2764">2764</a>                 <a href="ident?i=panic">panic</a>(<i>"IP: failed to allocate ipv4_dst_ops counter\n"</i>);
<a name="L2765" href="source/net/ipv4/route.c#L2765">2765</a> 
<a name="L2766" href="source/net/ipv4/route.c#L2766">2766</a>         if (<a href="ident?i=dst_entries_init">dst_entries_init</a>(&amp;<a href="ident?i=ipv4_dst_blackhole_ops">ipv4_dst_blackhole_ops</a>) &lt; 0)
<a name="L2767" href="source/net/ipv4/route.c#L2767">2767</a>                 <a href="ident?i=panic">panic</a>(<i>"IP: failed to allocate ipv4_dst_blackhole_ops counter\n"</i>);
<a name="L2768" href="source/net/ipv4/route.c#L2768">2768</a> 
<a name="L2769" href="source/net/ipv4/route.c#L2769">2769</a>         <a href="ident?i=ipv4_dst_ops">ipv4_dst_ops</a>.gc_thresh = ~0;
<a name="L2770" href="source/net/ipv4/route.c#L2770">2770</a>         <a href="ident?i=ip_rt_max_size">ip_rt_max_size</a> = <a href="ident?i=INT_MAX">INT_MAX</a>;
<a name="L2771" href="source/net/ipv4/route.c#L2771">2771</a> 
<a name="L2772" href="source/net/ipv4/route.c#L2772">2772</a>         <a href="ident?i=devinet_init">devinet_init</a>();
<a name="L2773" href="source/net/ipv4/route.c#L2773">2773</a>         <a href="ident?i=ip_fib_init">ip_fib_init</a>();
<a name="L2774" href="source/net/ipv4/route.c#L2774">2774</a> 
<a name="L2775" href="source/net/ipv4/route.c#L2775">2775</a>         if (<a href="ident?i=ip_rt_proc_init">ip_rt_proc_init</a>())
<a name="L2776" href="source/net/ipv4/route.c#L2776">2776</a>                 <a href="ident?i=pr_err">pr_err</a>(<i>"Unable to create route proc files\n"</i>);
<a name="L2777" href="source/net/ipv4/route.c#L2777">2777</a> #ifdef CONFIG_XFRM
<a name="L2778" href="source/net/ipv4/route.c#L2778">2778</a>         <a href="ident?i=xfrm_init">xfrm_init</a>();
<a name="L2779" href="source/net/ipv4/route.c#L2779">2779</a>         <a href="ident?i=xfrm4_init">xfrm4_init</a>();
<a name="L2780" href="source/net/ipv4/route.c#L2780">2780</a> #endif
<a name="L2781" href="source/net/ipv4/route.c#L2781">2781</a>         <a href="ident?i=rtnl_register">rtnl_register</a>(<a href="ident?i=PF_INET">PF_INET</a>, <a href="ident?i=RTM_GETROUTE">RTM_GETROUTE</a>, <a href="ident?i=inet_rtm_getroute">inet_rtm_getroute</a>, <a href="ident?i=NULL">NULL</a>, <a href="ident?i=NULL">NULL</a>);
<a name="L2782" href="source/net/ipv4/route.c#L2782">2782</a> 
<a name="L2783" href="source/net/ipv4/route.c#L2783">2783</a> #ifdef CONFIG_SYSCTL
<a name="L2784" href="source/net/ipv4/route.c#L2784">2784</a>         <a href="ident?i=register_pernet_subsys">register_pernet_subsys</a>(&amp;<a href="ident?i=sysctl_route_ops">sysctl_route_ops</a>);
<a name="L2785" href="source/net/ipv4/route.c#L2785">2785</a> #endif
<a name="L2786" href="source/net/ipv4/route.c#L2786">2786</a>         <a href="ident?i=register_pernet_subsys">register_pernet_subsys</a>(&amp;<a href="ident?i=rt_genid_ops">rt_genid_ops</a>);
<a name="L2787" href="source/net/ipv4/route.c#L2787">2787</a>         <a href="ident?i=register_pernet_subsys">register_pernet_subsys</a>(&amp;<a href="ident?i=ipv4_inetpeer_ops">ipv4_inetpeer_ops</a>);
<a name="L2788" href="source/net/ipv4/route.c#L2788">2788</a>         return <a href="ident?i=rc">rc</a>;
<a name="L2789" href="source/net/ipv4/route.c#L2789">2789</a> }
<a name="L2790" href="source/net/ipv4/route.c#L2790">2790</a> 
<a name="L2791" href="source/net/ipv4/route.c#L2791">2791</a> #ifdef CONFIG_SYSCTL
<a name="L2792" href="source/net/ipv4/route.c#L2792">2792</a> <b><i>/*</i></b>
<a name="L2793" href="source/net/ipv4/route.c#L2793">2793</a> <b><i> * We really need to sanitize the damn ipv4 init order, then all</i></b>
<a name="L2794" href="source/net/ipv4/route.c#L2794">2794</a> <b><i> * this nonsense will go away.</i></b>
<a name="L2795" href="source/net/ipv4/route.c#L2795">2795</a> <b><i> */</i></b>
<a name="L2796" href="source/net/ipv4/route.c#L2796">2796</a> void <a href="ident?i=__init">__init</a> <a href="ident?i=ip_static_sysctl_init">ip_static_sysctl_init</a>(void)
<a name="L2797" href="source/net/ipv4/route.c#L2797">2797</a> {
<a name="L2798" href="source/net/ipv4/route.c#L2798">2798</a>         <a href="ident?i=register_net_sysctl">register_net_sysctl</a>(&amp;<a href="ident?i=init_net">init_net</a>, <i>"net/ipv4/route"</i>, <a href="ident?i=ipv4_route_table">ipv4_route_table</a>);
<a name="L2799" href="source/net/ipv4/route.c#L2799">2799</a> }
<a name="L2800" href="source/net/ipv4/route.c#L2800">2800</a> #endif
<a name="L2801" href="source/net/ipv4/route.c#L2801">2801</a> </pre></div><p>
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
