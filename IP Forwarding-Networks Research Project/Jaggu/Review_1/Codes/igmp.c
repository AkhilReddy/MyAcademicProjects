<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title>Linux/net/ipv4/igmp.c - Linux Cross Reference - Free Electrons</title>
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
		 &nbsp;&bull;&nbsp;<b><i>source navigation</i></b> &nbsp;&bull;&nbsp;<a href="diff/net/ipv4/igmp.c">diff markup</a> &nbsp;&bull;&nbsp;<a href="ident">identifier search</a> &nbsp;&bull;&nbsp;<a href="search">freetext search</a> &nbsp;&bull;&nbsp;
		</p>
	</div>
</div>

<div id="topbar">
  
  <p>Version: &nbsp;<a href="source/net/ipv4/igmp.c?v=2.0.40">2.0.40</a>&nbsp;<a href="source/net/ipv4/igmp.c?v=2.2.26">2.2.26</a>&nbsp;<a href="source/net/ipv4/igmp.c?v=2.4.37">2.4.37</a>&nbsp;<a href="source/net/ipv4/igmp.c?v=3.5">3.5</a>&nbsp;<a href="source/net/ipv4/igmp.c?v=3.6">3.6</a>&nbsp;<a href="source/net/ipv4/igmp.c?v=3.7">3.7</a>&nbsp;<a href="source/net/ipv4/igmp.c?v=3.8">3.8</a>&nbsp;<a href="source/net/ipv4/igmp.c?v=3.9">3.9</a>&nbsp;<a href="source/net/ipv4/igmp.c?v=3.10">3.10</a>&nbsp;<a href="source/net/ipv4/igmp.c?v=3.11">3.11</a>&nbsp;<a href="source/net/ipv4/igmp.c?v=3.12">3.12</a>&nbsp;<a href="source/net/ipv4/igmp.c?v=3.13">3.13</a>&nbsp;<a href="source/net/ipv4/igmp.c?v=3.14">3.14</a>&nbsp;<a href="source/net/ipv4/igmp.c?v=3.15">3.15</a>&nbsp;<a href="source/net/ipv4/igmp.c?v=3.16">3.16</a>&nbsp;<a href="source/net/ipv4/igmp.c?v=3.17">3.17</a>&nbsp;<a href="source/net/ipv4/igmp.c?v=3.18">3.18</a>&nbsp;<a href="source/net/ipv4/igmp.c?v=3.19">3.19</a>&nbsp;<a href="source/net/ipv4/igmp.c?v=4.0">4.0</a>&nbsp;<b><i>4.1</i></b></p>
  
</div>

<h1><a href="source/">Linux</a>/<a href="source/net/">net</a>/<a href="source/net/ipv4/">ipv4</a>/<a href="source/net/ipv4/igmp.c">igmp.c</a></h1>
<div id="lxrcode"><pre>  <a name="L1" href="source/net/ipv4/igmp.c#L1">1</a> <b><i>/*</i></b>
  <a name="L2" href="source/net/ipv4/igmp.c#L2">2</a> <b><i> *      Linux NET3:     Internet Group Management Protocol  [IGMP]</i></b>
  <a name="L3" href="source/net/ipv4/igmp.c#L3">3</a> <b><i> *</i></b>
  <a name="L4" href="source/net/ipv4/igmp.c#L4">4</a> <b><i> *      This code implements the IGMP protocol as defined in RFC1112. There has</i></b>
  <a name="L5" href="source/net/ipv4/igmp.c#L5">5</a> <b><i> *      been a further revision of this protocol since which is now supported.</i></b>
  <a name="L6" href="source/net/ipv4/igmp.c#L6">6</a> <b><i> *</i></b>
  <a name="L7" href="source/net/ipv4/igmp.c#L7">7</a> <b><i> *      If you have trouble with this module be careful what gcc you have used,</i></b>
  <a name="L8" href="source/net/ipv4/igmp.c#L8">8</a> <b><i> *      the older version didn't come out right using gcc 2.5.8, the newer one</i></b>
  <a name="L9" href="source/net/ipv4/igmp.c#L9">9</a> <b><i> *      seems to fall out with gcc 2.6.2.</i></b>
 <a name="L10" href="source/net/ipv4/igmp.c#L10">10</a> <b><i> *</i></b>
 <a name="L11" href="source/net/ipv4/igmp.c#L11">11</a> <b><i> *      Authors:</i></b>
 <a name="L12" href="source/net/ipv4/igmp.c#L12">12</a> <b><i> *              Alan Cox &lt;alan@lxorguk.ukuu.org.uk&gt;</i></b>
 <a name="L13" href="source/net/ipv4/igmp.c#L13">13</a> <b><i> *</i></b>
 <a name="L14" href="source/net/ipv4/igmp.c#L14">14</a> <b><i> *      This program is free software; you can redistribute it and/or</i></b>
 <a name="L15" href="source/net/ipv4/igmp.c#L15">15</a> <b><i> *      modify it under the terms of the GNU General Public License</i></b>
 <a name="L16" href="source/net/ipv4/igmp.c#L16">16</a> <b><i> *      as published by the Free Software Foundation; either version</i></b>
 <a name="L17" href="source/net/ipv4/igmp.c#L17">17</a> <b><i> *      2 of the License, or (at your option) any later version.</i></b>
 <a name="L18" href="source/net/ipv4/igmp.c#L18">18</a> <b><i> *</i></b>
 <a name="L19" href="source/net/ipv4/igmp.c#L19">19</a> <b><i> *      Fixes:</i></b>
 <a name="L20" href="source/net/ipv4/igmp.c#L20">20</a> <b><i> *</i></b>
 <a name="L21" href="source/net/ipv4/igmp.c#L21">21</a> <b><i> *              Alan Cox        :       Added lots of __inline__ to optimise</i></b>
 <a name="L22" href="source/net/ipv4/igmp.c#L22">22</a> <b><i> *                                      the memory usage of all the tiny little</i></b>
 <a name="L23" href="source/net/ipv4/igmp.c#L23">23</a> <b><i> *                                      functions.</i></b>
 <a name="L24" href="source/net/ipv4/igmp.c#L24">24</a> <b><i> *              Alan Cox        :       Dumped the header building experiment.</i></b>
 <a name="L25" href="source/net/ipv4/igmp.c#L25">25</a> <b><i> *              Alan Cox        :       Minor tweaks ready for multicast routing</i></b>
 <a name="L26" href="source/net/ipv4/igmp.c#L26">26</a> <b><i> *                                      and extended IGMP protocol.</i></b>
 <a name="L27" href="source/net/ipv4/igmp.c#L27">27</a> <b><i> *              Alan Cox        :       Removed a load of inline directives. Gcc 2.5.8</i></b>
 <a name="L28" href="source/net/ipv4/igmp.c#L28">28</a> <b><i> *                                      writes utterly bogus code otherwise (sigh)</i></b>
 <a name="L29" href="source/net/ipv4/igmp.c#L29">29</a> <b><i> *                                      fixed IGMP loopback to behave in the manner</i></b>
 <a name="L30" href="source/net/ipv4/igmp.c#L30">30</a> <b><i> *                                      desired by mrouted, fixed the fact it has been</i></b>
 <a name="L31" href="source/net/ipv4/igmp.c#L31">31</a> <b><i> *                                      broken since 1.3.6 and cleaned up a few minor</i></b>
 <a name="L32" href="source/net/ipv4/igmp.c#L32">32</a> <b><i> *                                      points.</i></b>
 <a name="L33" href="source/net/ipv4/igmp.c#L33">33</a> <b><i> *</i></b>
 <a name="L34" href="source/net/ipv4/igmp.c#L34">34</a> <b><i> *              Chih-Jen Chang  :       Tried to revise IGMP to Version 2</i></b>
 <a name="L35" href="source/net/ipv4/igmp.c#L35">35</a> <b><i> *              Tsu-Sheng Tsao          E-mail: chihjenc@scf.usc.edu and tsusheng@scf.usc.edu</i></b>
 <a name="L36" href="source/net/ipv4/igmp.c#L36">36</a> <b><i> *                                      The enhancements are mainly based on Steve Deering's</i></b>
 <a name="L37" href="source/net/ipv4/igmp.c#L37">37</a> <b><i> *                                      ipmulti-3.5 source code.</i></b>
 <a name="L38" href="source/net/ipv4/igmp.c#L38">38</a> <b><i> *              Chih-Jen Chang  :       Added the igmp_get_mrouter_info and</i></b>
 <a name="L39" href="source/net/ipv4/igmp.c#L39">39</a> <b><i> *              Tsu-Sheng Tsao          igmp_set_mrouter_info to keep track of</i></b>
 <a name="L40" href="source/net/ipv4/igmp.c#L40">40</a> <b><i> *                                      the mrouted version on that device.</i></b>
 <a name="L41" href="source/net/ipv4/igmp.c#L41">41</a> <b><i> *              Chih-Jen Chang  :       Added the max_resp_time parameter to</i></b>
 <a name="L42" href="source/net/ipv4/igmp.c#L42">42</a> <b><i> *              Tsu-Sheng Tsao          igmp_heard_query(). Using this parameter</i></b>
 <a name="L43" href="source/net/ipv4/igmp.c#L43">43</a> <b><i> *                                      to identify the multicast router version</i></b>
 <a name="L44" href="source/net/ipv4/igmp.c#L44">44</a> <b><i> *                                      and do what the IGMP version 2 specified.</i></b>
 <a name="L45" href="source/net/ipv4/igmp.c#L45">45</a> <b><i> *              Chih-Jen Chang  :       Added a timer to revert to IGMP V2 router</i></b>
 <a name="L46" href="source/net/ipv4/igmp.c#L46">46</a> <b><i> *              Tsu-Sheng Tsao          if the specified time expired.</i></b>
 <a name="L47" href="source/net/ipv4/igmp.c#L47">47</a> <b><i> *              Alan Cox        :       Stop IGMP from 0.0.0.0 being accepted.</i></b>
 <a name="L48" href="source/net/ipv4/igmp.c#L48">48</a> <b><i> *              Alan Cox        :       Use GFP_ATOMIC in the right places.</i></b>
 <a name="L49" href="source/net/ipv4/igmp.c#L49">49</a> <b><i> *              Christian Daudt :       igmp timer wasn't set for local group</i></b>
 <a name="L50" href="source/net/ipv4/igmp.c#L50">50</a> <b><i> *                                      memberships but was being deleted,</i></b>
 <a name="L51" href="source/net/ipv4/igmp.c#L51">51</a> <b><i> *                                      which caused a "del_timer() called</i></b>
 <a name="L52" href="source/net/ipv4/igmp.c#L52">52</a> <b><i> *                                      from %p with timer not initialized\n"</i></b>
 <a name="L53" href="source/net/ipv4/igmp.c#L53">53</a> <b><i> *                                      message (960131).</i></b>
 <a name="L54" href="source/net/ipv4/igmp.c#L54">54</a> <b><i> *              Christian Daudt :       removed del_timer from</i></b>
 <a name="L55" href="source/net/ipv4/igmp.c#L55">55</a> <b><i> *                                      igmp_timer_expire function (960205).</i></b>
 <a name="L56" href="source/net/ipv4/igmp.c#L56">56</a> <b><i> *             Christian Daudt :       igmp_heard_report now only calls</i></b>
 <a name="L57" href="source/net/ipv4/igmp.c#L57">57</a> <b><i> *                                     igmp_timer_expire if tm-&gt;running is</i></b>
 <a name="L58" href="source/net/ipv4/igmp.c#L58">58</a> <b><i> *                                     true (960216).</i></b>
 <a name="L59" href="source/net/ipv4/igmp.c#L59">59</a> <b><i> *              Malcolm Beattie :       ttl comparison wrong in igmp_rcv made</i></b>
 <a name="L60" href="source/net/ipv4/igmp.c#L60">60</a> <b><i> *                                      igmp_heard_query never trigger. Expiry</i></b>
 <a name="L61" href="source/net/ipv4/igmp.c#L61">61</a> <b><i> *                                      miscalculation fixed in igmp_heard_query</i></b>
 <a name="L62" href="source/net/ipv4/igmp.c#L62">62</a> <b><i> *                                      and random() made to return unsigned to</i></b>
 <a name="L63" href="source/net/ipv4/igmp.c#L63">63</a> <b><i> *                                      prevent negative expiry times.</i></b>
 <a name="L64" href="source/net/ipv4/igmp.c#L64">64</a> <b><i> *              Alexey Kuznetsov:       Wrong group leaving behaviour, backport</i></b>
 <a name="L65" href="source/net/ipv4/igmp.c#L65">65</a> <b><i> *                                      fix from pending 2.1.x patches.</i></b>
 <a name="L66" href="source/net/ipv4/igmp.c#L66">66</a> <b><i> *              Alan Cox:               Forget to enable FDDI support earlier.</i></b>
 <a name="L67" href="source/net/ipv4/igmp.c#L67">67</a> <b><i> *              Alexey Kuznetsov:       Fixed leaving groups on device down.</i></b>
 <a name="L68" href="source/net/ipv4/igmp.c#L68">68</a> <b><i> *              Alexey Kuznetsov:       Accordance to igmp-v2-06 draft.</i></b>
 <a name="L69" href="source/net/ipv4/igmp.c#L69">69</a> <b><i> *              David L Stevens:        IGMPv3 support, with help from</i></b>
 <a name="L70" href="source/net/ipv4/igmp.c#L70">70</a> <b><i> *                                      Vinay Kulkarni</i></b>
 <a name="L71" href="source/net/ipv4/igmp.c#L71">71</a> <b><i> */</i></b>
 <a name="L72" href="source/net/ipv4/igmp.c#L72">72</a> 
 <a name="L73" href="source/net/ipv4/igmp.c#L73">73</a> #include &lt;linux/module.h&gt;
 <a name="L74" href="source/net/ipv4/igmp.c#L74">74</a> #include &lt;linux/slab.h&gt;
 <a name="L75" href="source/net/ipv4/igmp.c#L75">75</a> #include &lt;asm/uaccess.h&gt;
 <a name="L76" href="source/net/ipv4/igmp.c#L76">76</a> #include &lt;linux/types.h&gt;
 <a name="L77" href="source/net/ipv4/igmp.c#L77">77</a> #include &lt;linux/kernel.h&gt;
 <a name="L78" href="source/net/ipv4/igmp.c#L78">78</a> #include &lt;linux/jiffies.h&gt;
 <a name="L79" href="source/net/ipv4/igmp.c#L79">79</a> #include &lt;linux/string.h&gt;
 <a name="L80" href="source/net/ipv4/igmp.c#L80">80</a> #include &lt;linux/socket.h&gt;
 <a name="L81" href="source/net/ipv4/igmp.c#L81">81</a> #include &lt;linux/sockios.h&gt;
 <a name="L82" href="source/net/ipv4/igmp.c#L82">82</a> #include &lt;linux/in.h&gt;
 <a name="L83" href="source/net/ipv4/igmp.c#L83">83</a> #include &lt;linux/inet.h&gt;
 <a name="L84" href="source/net/ipv4/igmp.c#L84">84</a> #include &lt;linux/netdevice.h&gt;
 <a name="L85" href="source/net/ipv4/igmp.c#L85">85</a> #include &lt;linux/skbuff.h&gt;
 <a name="L86" href="source/net/ipv4/igmp.c#L86">86</a> #include &lt;linux/inetdevice.h&gt;
 <a name="L87" href="source/net/ipv4/igmp.c#L87">87</a> #include &lt;linux/igmp.h&gt;
 <a name="L88" href="source/net/ipv4/igmp.c#L88">88</a> #include &lt;linux/if_arp.h&gt;
 <a name="L89" href="source/net/ipv4/igmp.c#L89">89</a> #include &lt;linux/rtnetlink.h&gt;
 <a name="L90" href="source/net/ipv4/igmp.c#L90">90</a> #include &lt;linux/times.h&gt;
 <a name="L91" href="source/net/ipv4/igmp.c#L91">91</a> #include &lt;linux/pkt_sched.h&gt;
 <a name="L92" href="source/net/ipv4/igmp.c#L92">92</a> 
 <a name="L93" href="source/net/ipv4/igmp.c#L93">93</a> #include &lt;net/net_namespace.h&gt;
 <a name="L94" href="source/net/ipv4/igmp.c#L94">94</a> #include &lt;net/arp.h&gt;
 <a name="L95" href="source/net/ipv4/igmp.c#L95">95</a> #include &lt;net/ip.h&gt;
 <a name="L96" href="source/net/ipv4/igmp.c#L96">96</a> #include &lt;net/protocol.h&gt;
 <a name="L97" href="source/net/ipv4/igmp.c#L97">97</a> #include &lt;net/route.h&gt;
 <a name="L98" href="source/net/ipv4/igmp.c#L98">98</a> #include &lt;net/sock.h&gt;
 <a name="L99" href="source/net/ipv4/igmp.c#L99">99</a> #include &lt;net/checksum.h&gt;
<a name="L100" href="source/net/ipv4/igmp.c#L100">100</a> #include &lt;net/inet_common.h&gt;
<a name="L101" href="source/net/ipv4/igmp.c#L101">101</a> #include &lt;linux/netfilter_ipv4.h&gt;
<a name="L102" href="source/net/ipv4/igmp.c#L102">102</a> #ifdef CONFIG_IP_MROUTE
<a name="L103" href="source/net/ipv4/igmp.c#L103">103</a> #include &lt;linux/mroute.h&gt;
<a name="L104" href="source/net/ipv4/igmp.c#L104">104</a> #endif
<a name="L105" href="source/net/ipv4/igmp.c#L105">105</a> #ifdef CONFIG_PROC_FS
<a name="L106" href="source/net/ipv4/igmp.c#L106">106</a> #include &lt;linux/proc_fs.h&gt;
<a name="L107" href="source/net/ipv4/igmp.c#L107">107</a> #include &lt;linux/seq_file.h&gt;
<a name="L108" href="source/net/ipv4/igmp.c#L108">108</a> #endif
<a name="L109" href="source/net/ipv4/igmp.c#L109">109</a> 
<a name="L110" href="source/net/ipv4/igmp.c#L110">110</a> #define <a href="ident?i=IP_MAX_MEMBERSHIPS">IP_MAX_MEMBERSHIPS</a>      20
<a name="L111" href="source/net/ipv4/igmp.c#L111">111</a> #define <a href="ident?i=IP_MAX_MSF">IP_MAX_MSF</a>              10
<a name="L112" href="source/net/ipv4/igmp.c#L112">112</a> 
<a name="L113" href="source/net/ipv4/igmp.c#L113">113</a> #ifdef CONFIG_IP_MULTICAST
<a name="L114" href="source/net/ipv4/igmp.c#L114">114</a> <b><i>/* Parameter names and values are taken from igmp-v2-06 draft */</i></b>
<a name="L115" href="source/net/ipv4/igmp.c#L115">115</a> 
<a name="L116" href="source/net/ipv4/igmp.c#L116">116</a> #define <a href="ident?i=IGMP_V1_ROUTER_PRESENT_TIMEOUT">IGMP_V1_ROUTER_PRESENT_TIMEOUT</a>          (400*<a href="ident?i=HZ">HZ</a>)
<a name="L117" href="source/net/ipv4/igmp.c#L117">117</a> #define <a href="ident?i=IGMP_V2_ROUTER_PRESENT_TIMEOUT">IGMP_V2_ROUTER_PRESENT_TIMEOUT</a>          (400*<a href="ident?i=HZ">HZ</a>)
<a name="L118" href="source/net/ipv4/igmp.c#L118">118</a> #define <a href="ident?i=IGMP_V2_UNSOLICITED_REPORT_INTERVAL">IGMP_V2_UNSOLICITED_REPORT_INTERVAL</a>     (10*<a href="ident?i=HZ">HZ</a>)
<a name="L119" href="source/net/ipv4/igmp.c#L119">119</a> #define <a href="ident?i=IGMP_V3_UNSOLICITED_REPORT_INTERVAL">IGMP_V3_UNSOLICITED_REPORT_INTERVAL</a>     (1*<a href="ident?i=HZ">HZ</a>)
<a name="L120" href="source/net/ipv4/igmp.c#L120">120</a> #define <a href="ident?i=IGMP_QUERY_RESPONSE_INTERVAL">IGMP_QUERY_RESPONSE_INTERVAL</a>            (10*<a href="ident?i=HZ">HZ</a>)
<a name="L121" href="source/net/ipv4/igmp.c#L121">121</a> #define <a href="ident?i=IGMP_QUERY_ROBUSTNESS_VARIABLE">IGMP_QUERY_ROBUSTNESS_VARIABLE</a>          2
<a name="L122" href="source/net/ipv4/igmp.c#L122">122</a> 
<a name="L123" href="source/net/ipv4/igmp.c#L123">123</a> 
<a name="L124" href="source/net/ipv4/igmp.c#L124">124</a> #define <a href="ident?i=IGMP_INITIAL_REPORT_DELAY">IGMP_INITIAL_REPORT_DELAY</a>               (1)
<a name="L125" href="source/net/ipv4/igmp.c#L125">125</a> 
<a name="L126" href="source/net/ipv4/igmp.c#L126">126</a> <b><i>/* IGMP_INITIAL_REPORT_DELAY is not from IGMP specs!</i></b>
<a name="L127" href="source/net/ipv4/igmp.c#L127">127</a> <b><i> * IGMP specs require to report membership immediately after</i></b>
<a name="L128" href="source/net/ipv4/igmp.c#L128">128</a> <b><i> * joining a group, but we delay the first report by a</i></b>
<a name="L129" href="source/net/ipv4/igmp.c#L129">129</a> <b><i> * small interval. It seems more natural and still does not</i></b>
<a name="L130" href="source/net/ipv4/igmp.c#L130">130</a> <b><i> * contradict to specs provided this delay is small enough.</i></b>
<a name="L131" href="source/net/ipv4/igmp.c#L131">131</a> <b><i> */</i></b>
<a name="L132" href="source/net/ipv4/igmp.c#L132">132</a> 
<a name="L133" href="source/net/ipv4/igmp.c#L133">133</a> #define <a href="ident?i=IGMP_V1_SEEN">IGMP_V1_SEEN</a>(in_dev) \
<a name="L134" href="source/net/ipv4/igmp.c#L134">134</a>         (<a href="ident?i=IPV4_DEVCONF_ALL">IPV4_DEVCONF_ALL</a>(<a href="ident?i=dev_net">dev_net</a>(in_dev-&gt;<a href="ident?i=dev">dev</a>), FORCE_IGMP_VERSION) == 1 || \
<a name="L135" href="source/net/ipv4/igmp.c#L135">135</a>          <a href="ident?i=IN_DEV_CONF_GET">IN_DEV_CONF_GET</a>((in_dev), FORCE_IGMP_VERSION) == 1 || \
<a name="L136" href="source/net/ipv4/igmp.c#L136">136</a>          ((in_dev)-&gt;mr_v1_seen &amp;&amp; \
<a name="L137" href="source/net/ipv4/igmp.c#L137">137</a>           <a href="ident?i=time_before">time_before</a>(<a href="ident?i=jiffies">jiffies</a>, (in_dev)-&gt;mr_v1_seen)))
<a name="L138" href="source/net/ipv4/igmp.c#L138">138</a> #define <a href="ident?i=IGMP_V2_SEEN">IGMP_V2_SEEN</a>(in_dev) \
<a name="L139" href="source/net/ipv4/igmp.c#L139">139</a>         (<a href="ident?i=IPV4_DEVCONF_ALL">IPV4_DEVCONF_ALL</a>(<a href="ident?i=dev_net">dev_net</a>(in_dev-&gt;<a href="ident?i=dev">dev</a>), FORCE_IGMP_VERSION) == 2 || \
<a name="L140" href="source/net/ipv4/igmp.c#L140">140</a>          <a href="ident?i=IN_DEV_CONF_GET">IN_DEV_CONF_GET</a>((in_dev), FORCE_IGMP_VERSION) == 2 || \
<a name="L141" href="source/net/ipv4/igmp.c#L141">141</a>          ((in_dev)-&gt;mr_v2_seen &amp;&amp; \
<a name="L142" href="source/net/ipv4/igmp.c#L142">142</a>           <a href="ident?i=time_before">time_before</a>(<a href="ident?i=jiffies">jiffies</a>, (in_dev)-&gt;mr_v2_seen)))
<a name="L143" href="source/net/ipv4/igmp.c#L143">143</a> 
<a name="L144" href="source/net/ipv4/igmp.c#L144">144</a> static int <a href="ident?i=unsolicited_report_interval">unsolicited_report_interval</a>(struct <a href="ident?i=in_device">in_device</a> *in_dev)
<a name="L145" href="source/net/ipv4/igmp.c#L145">145</a> {
<a name="L146" href="source/net/ipv4/igmp.c#L146">146</a>         int interval_ms, interval_jiffies;
<a name="L147" href="source/net/ipv4/igmp.c#L147">147</a> 
<a name="L148" href="source/net/ipv4/igmp.c#L148">148</a>         if (<a href="ident?i=IGMP_V1_SEEN">IGMP_V1_SEEN</a>(in_dev) || <a href="ident?i=IGMP_V2_SEEN">IGMP_V2_SEEN</a>(in_dev))
<a name="L149" href="source/net/ipv4/igmp.c#L149">149</a>                 interval_ms = <a href="ident?i=IN_DEV_CONF_GET">IN_DEV_CONF_GET</a>(
<a name="L150" href="source/net/ipv4/igmp.c#L150">150</a>                         in_dev,
<a name="L151" href="source/net/ipv4/igmp.c#L151">151</a>                         IGMPV2_UNSOLICITED_REPORT_INTERVAL);
<a name="L152" href="source/net/ipv4/igmp.c#L152">152</a>         else <b><i>/* v3 */</i></b>
<a name="L153" href="source/net/ipv4/igmp.c#L153">153</a>                 interval_ms = <a href="ident?i=IN_DEV_CONF_GET">IN_DEV_CONF_GET</a>(
<a name="L154" href="source/net/ipv4/igmp.c#L154">154</a>                         in_dev,
<a name="L155" href="source/net/ipv4/igmp.c#L155">155</a>                         IGMPV3_UNSOLICITED_REPORT_INTERVAL);
<a name="L156" href="source/net/ipv4/igmp.c#L156">156</a> 
<a name="L157" href="source/net/ipv4/igmp.c#L157">157</a>         interval_jiffies = <a href="ident?i=msecs_to_jiffies">msecs_to_jiffies</a>(interval_ms);
<a name="L158" href="source/net/ipv4/igmp.c#L158">158</a> 
<a name="L159" href="source/net/ipv4/igmp.c#L159">159</a>         <b><i>/* _timer functions can't handle a delay of 0 jiffies so ensure</i></b>
<a name="L160" href="source/net/ipv4/igmp.c#L160">160</a> <b><i>         *  we always return a positive value.</i></b>
<a name="L161" href="source/net/ipv4/igmp.c#L161">161</a> <b><i>         */</i></b>
<a name="L162" href="source/net/ipv4/igmp.c#L162">162</a>         if (interval_jiffies &lt;= 0)
<a name="L163" href="source/net/ipv4/igmp.c#L163">163</a>                 interval_jiffies = 1;
<a name="L164" href="source/net/ipv4/igmp.c#L164">164</a>         return interval_jiffies;
<a name="L165" href="source/net/ipv4/igmp.c#L165">165</a> }
<a name="L166" href="source/net/ipv4/igmp.c#L166">166</a> 
<a name="L167" href="source/net/ipv4/igmp.c#L167">167</a> static void <a href="ident?i=igmpv3_add_delrec">igmpv3_add_delrec</a>(struct <a href="ident?i=in_device">in_device</a> *in_dev, struct <a href="ident?i=ip_mc_list">ip_mc_list</a> *im);
<a name="L168" href="source/net/ipv4/igmp.c#L168">168</a> static void <a href="ident?i=igmpv3_del_delrec">igmpv3_del_delrec</a>(struct <a href="ident?i=in_device">in_device</a> *in_dev, <a href="ident?i=__be32">__be32</a> multiaddr);
<a name="L169" href="source/net/ipv4/igmp.c#L169">169</a> static void <a href="ident?i=igmpv3_clear_delrec">igmpv3_clear_delrec</a>(struct <a href="ident?i=in_device">in_device</a> *in_dev);
<a name="L170" href="source/net/ipv4/igmp.c#L170">170</a> static int <a href="ident?i=sf_setstate">sf_setstate</a>(struct <a href="ident?i=ip_mc_list">ip_mc_list</a> *<a href="ident?i=pmc">pmc</a>);
<a name="L171" href="source/net/ipv4/igmp.c#L171">171</a> static void <a href="ident?i=sf_markstate">sf_markstate</a>(struct <a href="ident?i=ip_mc_list">ip_mc_list</a> *<a href="ident?i=pmc">pmc</a>);
<a name="L172" href="source/net/ipv4/igmp.c#L172">172</a> #endif
<a name="L173" href="source/net/ipv4/igmp.c#L173">173</a> static void <a href="ident?i=ip_mc_clear_src">ip_mc_clear_src</a>(struct <a href="ident?i=ip_mc_list">ip_mc_list</a> *<a href="ident?i=pmc">pmc</a>);
<a name="L174" href="source/net/ipv4/igmp.c#L174">174</a> static int <a href="ident?i=ip_mc_add_src">ip_mc_add_src</a>(struct <a href="ident?i=in_device">in_device</a> *in_dev, <a href="ident?i=__be32">__be32</a> *pmca, int sfmode,
<a name="L175" href="source/net/ipv4/igmp.c#L175">175</a>                          int sfcount, <a href="ident?i=__be32">__be32</a> *psfsrc, int <a href="ident?i=delta">delta</a>);
<a name="L176" href="source/net/ipv4/igmp.c#L176">176</a> 
<a name="L177" href="source/net/ipv4/igmp.c#L177">177</a> static void <a href="ident?i=ip_ma_put">ip_ma_put</a>(struct <a href="ident?i=ip_mc_list">ip_mc_list</a> *im)
<a name="L178" href="source/net/ipv4/igmp.c#L178">178</a> {
<a name="L179" href="source/net/ipv4/igmp.c#L179">179</a>         if (<a href="ident?i=atomic_dec_and_test">atomic_dec_and_test</a>(&amp;im-&gt;refcnt)) {
<a name="L180" href="source/net/ipv4/igmp.c#L180">180</a>                 <a href="ident?i=in_dev_put">in_dev_put</a>(im-&gt;<a href="ident?i=interface">interface</a>);
<a name="L181" href="source/net/ipv4/igmp.c#L181">181</a>                 <a href="ident?i=kfree_rcu">kfree_rcu</a>(im, rcu);
<a name="L182" href="source/net/ipv4/igmp.c#L182">182</a>         }
<a name="L183" href="source/net/ipv4/igmp.c#L183">183</a> }
<a name="L184" href="source/net/ipv4/igmp.c#L184">184</a> 
<a name="L185" href="source/net/ipv4/igmp.c#L185">185</a> #define <a href="ident?i=for_each_pmc_rcu">for_each_pmc_rcu</a>(in_dev, <a href="ident?i=pmc">pmc</a>)                           \
<a name="L186" href="source/net/ipv4/igmp.c#L186">186</a>         for (<a href="ident?i=pmc">pmc</a> = <a href="ident?i=rcu_dereference">rcu_dereference</a>(in_dev-&gt;mc_list);            \
<a name="L187" href="source/net/ipv4/igmp.c#L187">187</a>              <a href="ident?i=pmc">pmc</a> != <a href="ident?i=NULL">NULL</a>;                                       \
<a name="L188" href="source/net/ipv4/igmp.c#L188">188</a>              <a href="ident?i=pmc">pmc</a> = <a href="ident?i=rcu_dereference">rcu_dereference</a>(<a href="ident?i=pmc">pmc</a>-&gt;next_rcu))
<a name="L189" href="source/net/ipv4/igmp.c#L189">189</a> 
<a name="L190" href="source/net/ipv4/igmp.c#L190">190</a> #define <a href="ident?i=for_each_pmc_rtnl">for_each_pmc_rtnl</a>(in_dev, <a href="ident?i=pmc">pmc</a>)                          \
<a name="L191" href="source/net/ipv4/igmp.c#L191">191</a>         for (<a href="ident?i=pmc">pmc</a> = <a href="ident?i=rtnl_dereference">rtnl_dereference</a>(in_dev-&gt;mc_list);           \
<a name="L192" href="source/net/ipv4/igmp.c#L192">192</a>              <a href="ident?i=pmc">pmc</a> != <a href="ident?i=NULL">NULL</a>;                                       \
<a name="L193" href="source/net/ipv4/igmp.c#L193">193</a>              <a href="ident?i=pmc">pmc</a> = <a href="ident?i=rtnl_dereference">rtnl_dereference</a>(<a href="ident?i=pmc">pmc</a>-&gt;next_rcu))
<a name="L194" href="source/net/ipv4/igmp.c#L194">194</a> 
<a name="L195" href="source/net/ipv4/igmp.c#L195">195</a> #ifdef CONFIG_IP_MULTICAST
<a name="L196" href="source/net/ipv4/igmp.c#L196">196</a> 
<a name="L197" href="source/net/ipv4/igmp.c#L197">197</a> <b><i>/*</i></b>
<a name="L198" href="source/net/ipv4/igmp.c#L198">198</a> <b><i> *      Timer management</i></b>
<a name="L199" href="source/net/ipv4/igmp.c#L199">199</a> <b><i> */</i></b>
<a name="L200" href="source/net/ipv4/igmp.c#L200">200</a> 
<a name="L201" href="source/net/ipv4/igmp.c#L201">201</a> static void <a href="ident?i=igmp_stop_timer">igmp_stop_timer</a>(struct <a href="ident?i=ip_mc_list">ip_mc_list</a> *im)
<a name="L202" href="source/net/ipv4/igmp.c#L202">202</a> {
<a name="L203" href="source/net/ipv4/igmp.c#L203">203</a>         <a href="ident?i=spin_lock_bh">spin_lock_bh</a>(&amp;im-&gt;<a href="ident?i=lock">lock</a>);
<a name="L204" href="source/net/ipv4/igmp.c#L204">204</a>         if (<a href="ident?i=del_timer">del_timer</a>(&amp;im-&gt;<a href="ident?i=timer">timer</a>))
<a name="L205" href="source/net/ipv4/igmp.c#L205">205</a>                 <a href="ident?i=atomic_dec">atomic_dec</a>(&amp;im-&gt;refcnt);
<a name="L206" href="source/net/ipv4/igmp.c#L206">206</a>         im-&gt;tm_running = 0;
<a name="L207" href="source/net/ipv4/igmp.c#L207">207</a>         im-&gt;reporter = 0;
<a name="L208" href="source/net/ipv4/igmp.c#L208">208</a>         im-&gt;unsolicit_count = 0;
<a name="L209" href="source/net/ipv4/igmp.c#L209">209</a>         <a href="ident?i=spin_unlock_bh">spin_unlock_bh</a>(&amp;im-&gt;<a href="ident?i=lock">lock</a>);
<a name="L210" href="source/net/ipv4/igmp.c#L210">210</a> }
<a name="L211" href="source/net/ipv4/igmp.c#L211">211</a> 
<a name="L212" href="source/net/ipv4/igmp.c#L212">212</a> <b><i>/* It must be called with locked im-&gt;lock */</i></b>
<a name="L213" href="source/net/ipv4/igmp.c#L213">213</a> static void <a href="ident?i=igmp_start_timer">igmp_start_timer</a>(struct <a href="ident?i=ip_mc_list">ip_mc_list</a> *im, int <a href="ident?i=max_delay">max_delay</a>)
<a name="L214" href="source/net/ipv4/igmp.c#L214">214</a> {
<a name="L215" href="source/net/ipv4/igmp.c#L215">215</a>         int tv = <a href="ident?i=prandom_u32">prandom_u32</a>() % <a href="ident?i=max_delay">max_delay</a>;
<a name="L216" href="source/net/ipv4/igmp.c#L216">216</a> 
<a name="L217" href="source/net/ipv4/igmp.c#L217">217</a>         im-&gt;tm_running = 1;
<a name="L218" href="source/net/ipv4/igmp.c#L218">218</a>         if (!<a href="ident?i=mod_timer">mod_timer</a>(&amp;im-&gt;<a href="ident?i=timer">timer</a>, <a href="ident?i=jiffies">jiffies</a>+tv+2))
<a name="L219" href="source/net/ipv4/igmp.c#L219">219</a>                 <a href="ident?i=atomic_inc">atomic_inc</a>(&amp;im-&gt;refcnt);
<a name="L220" href="source/net/ipv4/igmp.c#L220">220</a> }
<a name="L221" href="source/net/ipv4/igmp.c#L221">221</a> 
<a name="L222" href="source/net/ipv4/igmp.c#L222">222</a> static void <a href="ident?i=igmp_gq_start_timer">igmp_gq_start_timer</a>(struct <a href="ident?i=in_device">in_device</a> *in_dev)
<a name="L223" href="source/net/ipv4/igmp.c#L223">223</a> {
<a name="L224" href="source/net/ipv4/igmp.c#L224">224</a>         int tv = <a href="ident?i=prandom_u32">prandom_u32</a>() % in_dev-&gt;mr_maxdelay;
<a name="L225" href="source/net/ipv4/igmp.c#L225">225</a> 
<a name="L226" href="source/net/ipv4/igmp.c#L226">226</a>         in_dev-&gt;mr_gq_running = 1;
<a name="L227" href="source/net/ipv4/igmp.c#L227">227</a>         if (!<a href="ident?i=mod_timer">mod_timer</a>(&amp;in_dev-&gt;mr_gq_timer, <a href="ident?i=jiffies">jiffies</a>+tv+2))
<a name="L228" href="source/net/ipv4/igmp.c#L228">228</a>                 <a href="ident?i=in_dev_hold">in_dev_hold</a>(in_dev);
<a name="L229" href="source/net/ipv4/igmp.c#L229">229</a> }
<a name="L230" href="source/net/ipv4/igmp.c#L230">230</a> 
<a name="L231" href="source/net/ipv4/igmp.c#L231">231</a> static void <a href="ident?i=igmp_ifc_start_timer">igmp_ifc_start_timer</a>(struct <a href="ident?i=in_device">in_device</a> *in_dev, int <a href="ident?i=delay">delay</a>)
<a name="L232" href="source/net/ipv4/igmp.c#L232">232</a> {
<a name="L233" href="source/net/ipv4/igmp.c#L233">233</a>         int tv = <a href="ident?i=prandom_u32">prandom_u32</a>() % <a href="ident?i=delay">delay</a>;
<a name="L234" href="source/net/ipv4/igmp.c#L234">234</a> 
<a name="L235" href="source/net/ipv4/igmp.c#L235">235</a>         if (!<a href="ident?i=mod_timer">mod_timer</a>(&amp;in_dev-&gt;mr_ifc_timer, <a href="ident?i=jiffies">jiffies</a>+tv+2))
<a name="L236" href="source/net/ipv4/igmp.c#L236">236</a>                 <a href="ident?i=in_dev_hold">in_dev_hold</a>(in_dev);
<a name="L237" href="source/net/ipv4/igmp.c#L237">237</a> }
<a name="L238" href="source/net/ipv4/igmp.c#L238">238</a> 
<a name="L239" href="source/net/ipv4/igmp.c#L239">239</a> static void <a href="ident?i=igmp_mod_timer">igmp_mod_timer</a>(struct <a href="ident?i=ip_mc_list">ip_mc_list</a> *im, int <a href="ident?i=max_delay">max_delay</a>)
<a name="L240" href="source/net/ipv4/igmp.c#L240">240</a> {
<a name="L241" href="source/net/ipv4/igmp.c#L241">241</a>         <a href="ident?i=spin_lock_bh">spin_lock_bh</a>(&amp;im-&gt;<a href="ident?i=lock">lock</a>);
<a name="L242" href="source/net/ipv4/igmp.c#L242">242</a>         im-&gt;unsolicit_count = 0;
<a name="L243" href="source/net/ipv4/igmp.c#L243">243</a>         if (<a href="ident?i=del_timer">del_timer</a>(&amp;im-&gt;<a href="ident?i=timer">timer</a>)) {
<a name="L244" href="source/net/ipv4/igmp.c#L244">244</a>                 if ((long)(im-&gt;<a href="ident?i=timer">timer</a>.expires-<a href="ident?i=jiffies">jiffies</a>) &lt; <a href="ident?i=max_delay">max_delay</a>) {
<a name="L245" href="source/net/ipv4/igmp.c#L245">245</a>                         <a href="ident?i=add_timer">add_timer</a>(&amp;im-&gt;<a href="ident?i=timer">timer</a>);
<a name="L246" href="source/net/ipv4/igmp.c#L246">246</a>                         im-&gt;tm_running = 1;
<a name="L247" href="source/net/ipv4/igmp.c#L247">247</a>                         <a href="ident?i=spin_unlock_bh">spin_unlock_bh</a>(&amp;im-&gt;<a href="ident?i=lock">lock</a>);
<a name="L248" href="source/net/ipv4/igmp.c#L248">248</a>                         return;
<a name="L249" href="source/net/ipv4/igmp.c#L249">249</a>                 }
<a name="L250" href="source/net/ipv4/igmp.c#L250">250</a>                 <a href="ident?i=atomic_dec">atomic_dec</a>(&amp;im-&gt;refcnt);
<a name="L251" href="source/net/ipv4/igmp.c#L251">251</a>         }
<a name="L252" href="source/net/ipv4/igmp.c#L252">252</a>         <a href="ident?i=igmp_start_timer">igmp_start_timer</a>(im, <a href="ident?i=max_delay">max_delay</a>);
<a name="L253" href="source/net/ipv4/igmp.c#L253">253</a>         <a href="ident?i=spin_unlock_bh">spin_unlock_bh</a>(&amp;im-&gt;<a href="ident?i=lock">lock</a>);
<a name="L254" href="source/net/ipv4/igmp.c#L254">254</a> }
<a name="L255" href="source/net/ipv4/igmp.c#L255">255</a> 
<a name="L256" href="source/net/ipv4/igmp.c#L256">256</a> 
<a name="L257" href="source/net/ipv4/igmp.c#L257">257</a> <b><i>/*</i></b>
<a name="L258" href="source/net/ipv4/igmp.c#L258">258</a> <b><i> *      Send an IGMP report.</i></b>
<a name="L259" href="source/net/ipv4/igmp.c#L259">259</a> <b><i> */</i></b>
<a name="L260" href="source/net/ipv4/igmp.c#L260">260</a> 
<a name="L261" href="source/net/ipv4/igmp.c#L261">261</a> #define <a href="ident?i=IGMP_SIZE">IGMP_SIZE</a> (sizeof(struct <a href="ident?i=igmphdr">igmphdr</a>)+sizeof(struct <a href="ident?i=iphdr">iphdr</a>)+4)
<a name="L262" href="source/net/ipv4/igmp.c#L262">262</a> 
<a name="L263" href="source/net/ipv4/igmp.c#L263">263</a> 
<a name="L264" href="source/net/ipv4/igmp.c#L264">264</a> static int <a href="ident?i=is_in">is_in</a>(struct <a href="ident?i=ip_mc_list">ip_mc_list</a> *<a href="ident?i=pmc">pmc</a>, struct <a href="ident?i=ip_sf_list">ip_sf_list</a> *psf, int <a href="ident?i=type">type</a>,
<a name="L265" href="source/net/ipv4/igmp.c#L265">265</a>         int gdeleted, int sdeleted)
<a name="L266" href="source/net/ipv4/igmp.c#L266">266</a> {
<a name="L267" href="source/net/ipv4/igmp.c#L267">267</a>         switch (<a href="ident?i=type">type</a>) {
<a name="L268" href="source/net/ipv4/igmp.c#L268">268</a>         case <a href="ident?i=IGMPV3_MODE_IS_INCLUDE">IGMPV3_MODE_IS_INCLUDE</a>:
<a name="L269" href="source/net/ipv4/igmp.c#L269">269</a>         case <a href="ident?i=IGMPV3_MODE_IS_EXCLUDE">IGMPV3_MODE_IS_EXCLUDE</a>:
<a name="L270" href="source/net/ipv4/igmp.c#L270">270</a>                 if (gdeleted || sdeleted)
<a name="L271" href="source/net/ipv4/igmp.c#L271">271</a>                         return 0;
<a name="L272" href="source/net/ipv4/igmp.c#L272">272</a>                 if (!(<a href="ident?i=pmc">pmc</a>-&gt;gsquery &amp;&amp; !psf-&gt;sf_gsresp)) {
<a name="L273" href="source/net/ipv4/igmp.c#L273">273</a>                         if (<a href="ident?i=pmc">pmc</a>-&gt;sfmode == <a href="ident?i=MCAST_INCLUDE">MCAST_INCLUDE</a>)
<a name="L274" href="source/net/ipv4/igmp.c#L274">274</a>                                 return 1;
<a name="L275" href="source/net/ipv4/igmp.c#L275">275</a>                         <b><i>/* don't include if this source is excluded</i></b>
<a name="L276" href="source/net/ipv4/igmp.c#L276">276</a> <b><i>                         * in all filters</i></b>
<a name="L277" href="source/net/ipv4/igmp.c#L277">277</a> <b><i>                         */</i></b>
<a name="L278" href="source/net/ipv4/igmp.c#L278">278</a>                         if (psf-&gt;sf_count[<a href="ident?i=MCAST_INCLUDE">MCAST_INCLUDE</a>])
<a name="L279" href="source/net/ipv4/igmp.c#L279">279</a>                                 return <a href="ident?i=type">type</a> == <a href="ident?i=IGMPV3_MODE_IS_INCLUDE">IGMPV3_MODE_IS_INCLUDE</a>;
<a name="L280" href="source/net/ipv4/igmp.c#L280">280</a>                         return <a href="ident?i=pmc">pmc</a>-&gt;sfcount[<a href="ident?i=MCAST_EXCLUDE">MCAST_EXCLUDE</a>] ==
<a name="L281" href="source/net/ipv4/igmp.c#L281">281</a>                                 psf-&gt;sf_count[<a href="ident?i=MCAST_EXCLUDE">MCAST_EXCLUDE</a>];
<a name="L282" href="source/net/ipv4/igmp.c#L282">282</a>                 }
<a name="L283" href="source/net/ipv4/igmp.c#L283">283</a>                 return 0;
<a name="L284" href="source/net/ipv4/igmp.c#L284">284</a>         case <a href="ident?i=IGMPV3_CHANGE_TO_INCLUDE">IGMPV3_CHANGE_TO_INCLUDE</a>:
<a name="L285" href="source/net/ipv4/igmp.c#L285">285</a>                 if (gdeleted || sdeleted)
<a name="L286" href="source/net/ipv4/igmp.c#L286">286</a>                         return 0;
<a name="L287" href="source/net/ipv4/igmp.c#L287">287</a>                 return psf-&gt;sf_count[<a href="ident?i=MCAST_INCLUDE">MCAST_INCLUDE</a>] != 0;
<a name="L288" href="source/net/ipv4/igmp.c#L288">288</a>         case <a href="ident?i=IGMPV3_CHANGE_TO_EXCLUDE">IGMPV3_CHANGE_TO_EXCLUDE</a>:
<a name="L289" href="source/net/ipv4/igmp.c#L289">289</a>                 if (gdeleted || sdeleted)
<a name="L290" href="source/net/ipv4/igmp.c#L290">290</a>                         return 0;
<a name="L291" href="source/net/ipv4/igmp.c#L291">291</a>                 if (<a href="ident?i=pmc">pmc</a>-&gt;sfcount[<a href="ident?i=MCAST_EXCLUDE">MCAST_EXCLUDE</a>] == 0 ||
<a name="L292" href="source/net/ipv4/igmp.c#L292">292</a>                     psf-&gt;sf_count[<a href="ident?i=MCAST_INCLUDE">MCAST_INCLUDE</a>])
<a name="L293" href="source/net/ipv4/igmp.c#L293">293</a>                         return 0;
<a name="L294" href="source/net/ipv4/igmp.c#L294">294</a>                 return <a href="ident?i=pmc">pmc</a>-&gt;sfcount[<a href="ident?i=MCAST_EXCLUDE">MCAST_EXCLUDE</a>] ==
<a name="L295" href="source/net/ipv4/igmp.c#L295">295</a>                         psf-&gt;sf_count[<a href="ident?i=MCAST_EXCLUDE">MCAST_EXCLUDE</a>];
<a name="L296" href="source/net/ipv4/igmp.c#L296">296</a>         case <a href="ident?i=IGMPV3_ALLOW_NEW_SOURCES">IGMPV3_ALLOW_NEW_SOURCES</a>:
<a name="L297" href="source/net/ipv4/igmp.c#L297">297</a>                 if (gdeleted || !psf-&gt;sf_crcount)
<a name="L298" href="source/net/ipv4/igmp.c#L298">298</a>                         return 0;
<a name="L299" href="source/net/ipv4/igmp.c#L299">299</a>                 return (<a href="ident?i=pmc">pmc</a>-&gt;sfmode == <a href="ident?i=MCAST_INCLUDE">MCAST_INCLUDE</a>) ^ sdeleted;
<a name="L300" href="source/net/ipv4/igmp.c#L300">300</a>         case <a href="ident?i=IGMPV3_BLOCK_OLD_SOURCES">IGMPV3_BLOCK_OLD_SOURCES</a>:
<a name="L301" href="source/net/ipv4/igmp.c#L301">301</a>                 if (<a href="ident?i=pmc">pmc</a>-&gt;sfmode == <a href="ident?i=MCAST_INCLUDE">MCAST_INCLUDE</a>)
<a name="L302" href="source/net/ipv4/igmp.c#L302">302</a>                         return gdeleted || (psf-&gt;sf_crcount &amp;&amp; sdeleted);
<a name="L303" href="source/net/ipv4/igmp.c#L303">303</a>                 return psf-&gt;sf_crcount &amp;&amp; !gdeleted &amp;&amp; !sdeleted;
<a name="L304" href="source/net/ipv4/igmp.c#L304">304</a>         }
<a name="L305" href="source/net/ipv4/igmp.c#L305">305</a>         return 0;
<a name="L306" href="source/net/ipv4/igmp.c#L306">306</a> }
<a name="L307" href="source/net/ipv4/igmp.c#L307">307</a> 
<a name="L308" href="source/net/ipv4/igmp.c#L308">308</a> static int
<a name="L309" href="source/net/ipv4/igmp.c#L309">309</a> <a href="ident?i=igmp_scount">igmp_scount</a>(struct <a href="ident?i=ip_mc_list">ip_mc_list</a> *<a href="ident?i=pmc">pmc</a>, int <a href="ident?i=type">type</a>, int gdeleted, int sdeleted)
<a name="L310" href="source/net/ipv4/igmp.c#L310">310</a> {
<a name="L311" href="source/net/ipv4/igmp.c#L311">311</a>         struct <a href="ident?i=ip_sf_list">ip_sf_list</a> *psf;
<a name="L312" href="source/net/ipv4/igmp.c#L312">312</a>         int scount = 0;
<a name="L313" href="source/net/ipv4/igmp.c#L313">313</a> 
<a name="L314" href="source/net/ipv4/igmp.c#L314">314</a>         for (psf = <a href="ident?i=pmc">pmc</a>-&gt;sources; psf; psf = psf-&gt;sf_next) {
<a name="L315" href="source/net/ipv4/igmp.c#L315">315</a>                 if (!<a href="ident?i=is_in">is_in</a>(<a href="ident?i=pmc">pmc</a>, psf, <a href="ident?i=type">type</a>, gdeleted, sdeleted))
<a name="L316" href="source/net/ipv4/igmp.c#L316">316</a>                         continue;
<a name="L317" href="source/net/ipv4/igmp.c#L317">317</a>                 scount++;
<a name="L318" href="source/net/ipv4/igmp.c#L318">318</a>         }
<a name="L319" href="source/net/ipv4/igmp.c#L319">319</a>         return scount;
<a name="L320" href="source/net/ipv4/igmp.c#L320">320</a> }
<a name="L321" href="source/net/ipv4/igmp.c#L321">321</a> 
<a name="L322" href="source/net/ipv4/igmp.c#L322">322</a> static struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=igmpv3_newpack">igmpv3_newpack</a>(struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>, unsigned int <a href="ident?i=mtu">mtu</a>)
<a name="L323" href="source/net/ipv4/igmp.c#L323">323</a> {
<a name="L324" href="source/net/ipv4/igmp.c#L324">324</a>         struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>;
<a name="L325" href="source/net/ipv4/igmp.c#L325">325</a>         struct <a href="ident?i=rtable">rtable</a> *<a href="ident?i=rt">rt</a>;
<a name="L326" href="source/net/ipv4/igmp.c#L326">326</a>         struct <a href="ident?i=iphdr">iphdr</a> *pip;
<a name="L327" href="source/net/ipv4/igmp.c#L327">327</a>         struct <a href="ident?i=igmpv3_report">igmpv3_report</a> *pig;
<a name="L328" href="source/net/ipv4/igmp.c#L328">328</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=dev">dev</a>);
<a name="L329" href="source/net/ipv4/igmp.c#L329">329</a>         struct <a href="ident?i=flowi4">flowi4</a> fl4;
<a name="L330" href="source/net/ipv4/igmp.c#L330">330</a>         int hlen = <a href="ident?i=LL_RESERVED_SPACE">LL_RESERVED_SPACE</a>(<a href="ident?i=dev">dev</a>);
<a name="L331" href="source/net/ipv4/igmp.c#L331">331</a>         int tlen = <a href="ident?i=dev">dev</a>-&gt;needed_tailroom;
<a name="L332" href="source/net/ipv4/igmp.c#L332">332</a>         unsigned int <a href="ident?i=size">size</a> = <a href="ident?i=mtu">mtu</a>;
<a name="L333" href="source/net/ipv4/igmp.c#L333">333</a> 
<a name="L334" href="source/net/ipv4/igmp.c#L334">334</a>         while (1) {
<a name="L335" href="source/net/ipv4/igmp.c#L335">335</a>                 <a href="ident?i=skb">skb</a> = <a href="ident?i=alloc_skb">alloc_skb</a>(<a href="ident?i=size">size</a> + hlen + tlen,
<a name="L336" href="source/net/ipv4/igmp.c#L336">336</a>                                 <a href="ident?i=GFP_ATOMIC">GFP_ATOMIC</a> | <a href="ident?i=__GFP_NOWARN">__GFP_NOWARN</a>);
<a name="L337" href="source/net/ipv4/igmp.c#L337">337</a>                 if (<a href="ident?i=skb">skb</a>)
<a name="L338" href="source/net/ipv4/igmp.c#L338">338</a>                         break;
<a name="L339" href="source/net/ipv4/igmp.c#L339">339</a>                 <a href="ident?i=size">size</a> &gt;&gt;= 1;
<a name="L340" href="source/net/ipv4/igmp.c#L340">340</a>                 if (<a href="ident?i=size">size</a> &lt; 256)
<a name="L341" href="source/net/ipv4/igmp.c#L341">341</a>                         return <a href="ident?i=NULL">NULL</a>;
<a name="L342" href="source/net/ipv4/igmp.c#L342">342</a>         }
<a name="L343" href="source/net/ipv4/igmp.c#L343">343</a>         <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=priority">priority</a> = <a href="ident?i=TC_PRIO_CONTROL">TC_PRIO_CONTROL</a>;
<a name="L344" href="source/net/ipv4/igmp.c#L344">344</a> 
<a name="L345" href="source/net/ipv4/igmp.c#L345">345</a>         <a href="ident?i=rt">rt</a> = <a href="ident?i=ip_route_output_ports">ip_route_output_ports</a>(<a href="ident?i=net">net</a>, &amp;fl4, <a href="ident?i=NULL">NULL</a>, <a href="ident?i=IGMPV3_ALL_MCR">IGMPV3_ALL_MCR</a>, 0,
<a name="L346" href="source/net/ipv4/igmp.c#L346">346</a>                                    0, 0,
<a name="L347" href="source/net/ipv4/igmp.c#L347">347</a>                                    <a href="ident?i=IPPROTO_IGMP">IPPROTO_IGMP</a>, 0, <a href="ident?i=dev">dev</a>-&gt;ifindex);
<a name="L348" href="source/net/ipv4/igmp.c#L348">348</a>         if (<a href="ident?i=IS_ERR">IS_ERR</a>(<a href="ident?i=rt">rt</a>)) {
<a name="L349" href="source/net/ipv4/igmp.c#L349">349</a>                 <a href="ident?i=kfree_skb">kfree_skb</a>(<a href="ident?i=skb">skb</a>);
<a name="L350" href="source/net/ipv4/igmp.c#L350">350</a>                 return <a href="ident?i=NULL">NULL</a>;
<a name="L351" href="source/net/ipv4/igmp.c#L351">351</a>         }
<a name="L352" href="source/net/ipv4/igmp.c#L352">352</a> 
<a name="L353" href="source/net/ipv4/igmp.c#L353">353</a>         <a href="ident?i=skb_dst_set">skb_dst_set</a>(<a href="ident?i=skb">skb</a>, &amp;<a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>);
<a name="L354" href="source/net/ipv4/igmp.c#L354">354</a>         <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=dev">dev</a> = <a href="ident?i=dev">dev</a>;
<a name="L355" href="source/net/ipv4/igmp.c#L355">355</a> 
<a name="L356" href="source/net/ipv4/igmp.c#L356">356</a>         <a href="ident?i=skb">skb</a>-&gt;reserved_tailroom = <a href="ident?i=skb_end_offset">skb_end_offset</a>(<a href="ident?i=skb">skb</a>) -
<a name="L357" href="source/net/ipv4/igmp.c#L357">357</a>                                  <a href="ident?i=min">min</a>(<a href="ident?i=mtu">mtu</a>, <a href="ident?i=skb_end_offset">skb_end_offset</a>(<a href="ident?i=skb">skb</a>));
<a name="L358" href="source/net/ipv4/igmp.c#L358">358</a>         <a href="ident?i=skb_reserve">skb_reserve</a>(<a href="ident?i=skb">skb</a>, hlen);
<a name="L359" href="source/net/ipv4/igmp.c#L359">359</a> 
<a name="L360" href="source/net/ipv4/igmp.c#L360">360</a>         <a href="ident?i=skb_reset_network_header">skb_reset_network_header</a>(<a href="ident?i=skb">skb</a>);
<a name="L361" href="source/net/ipv4/igmp.c#L361">361</a>         pip = <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>);
<a name="L362" href="source/net/ipv4/igmp.c#L362">362</a>         <a href="ident?i=skb_put">skb_put</a>(<a href="ident?i=skb">skb</a>, sizeof(struct <a href="ident?i=iphdr">iphdr</a>) + 4);
<a name="L363" href="source/net/ipv4/igmp.c#L363">363</a> 
<a name="L364" href="source/net/ipv4/igmp.c#L364">364</a>         pip-&gt;<a href="ident?i=version">version</a>  = 4;
<a name="L365" href="source/net/ipv4/igmp.c#L365">365</a>         pip-&gt;ihl      = (sizeof(struct <a href="ident?i=iphdr">iphdr</a>)+4)&gt;&gt;2;
<a name="L366" href="source/net/ipv4/igmp.c#L366">366</a>         pip-&gt;tos      = 0xc0;
<a name="L367" href="source/net/ipv4/igmp.c#L367">367</a>         pip-&gt;frag_off = <a href="ident?i=htons">htons</a>(<a href="ident?i=IP_DF">IP_DF</a>);
<a name="L368" href="source/net/ipv4/igmp.c#L368">368</a>         pip-&gt;<a href="ident?i=ttl">ttl</a>      = 1;
<a name="L369" href="source/net/ipv4/igmp.c#L369">369</a>         pip-&gt;<a href="ident?i=daddr">daddr</a>    = fl4.<a href="ident?i=daddr">daddr</a>;
<a name="L370" href="source/net/ipv4/igmp.c#L370">370</a>         pip-&gt;<a href="ident?i=saddr">saddr</a>    = fl4.<a href="ident?i=saddr">saddr</a>;
<a name="L371" href="source/net/ipv4/igmp.c#L371">371</a>         pip-&gt;<a href="ident?i=protocol">protocol</a> = <a href="ident?i=IPPROTO_IGMP">IPPROTO_IGMP</a>;
<a name="L372" href="source/net/ipv4/igmp.c#L372">372</a>         pip-&gt;tot_len  = 0;      <b><i>/* filled in later */</i></b>
<a name="L373" href="source/net/ipv4/igmp.c#L373">373</a>         <a href="ident?i=ip_select_ident">ip_select_ident</a>(<a href="ident?i=net">net</a>, <a href="ident?i=skb">skb</a>, <a href="ident?i=NULL">NULL</a>);
<a name="L374" href="source/net/ipv4/igmp.c#L374">374</a>         ((<a href="ident?i=u8">u8</a> *)&amp;pip[1])[0] = <a href="ident?i=IPOPT_RA">IPOPT_RA</a>;
<a name="L375" href="source/net/ipv4/igmp.c#L375">375</a>         ((<a href="ident?i=u8">u8</a> *)&amp;pip[1])[1] = 4;
<a name="L376" href="source/net/ipv4/igmp.c#L376">376</a>         ((<a href="ident?i=u8">u8</a> *)&amp;pip[1])[2] = 0;
<a name="L377" href="source/net/ipv4/igmp.c#L377">377</a>         ((<a href="ident?i=u8">u8</a> *)&amp;pip[1])[3] = 0;
<a name="L378" href="source/net/ipv4/igmp.c#L378">378</a> 
<a name="L379" href="source/net/ipv4/igmp.c#L379">379</a>         <a href="ident?i=skb">skb</a>-&gt;transport_header = <a href="ident?i=skb">skb</a>-&gt;network_header + sizeof(struct <a href="ident?i=iphdr">iphdr</a>) + 4;
<a name="L380" href="source/net/ipv4/igmp.c#L380">380</a>         <a href="ident?i=skb_put">skb_put</a>(<a href="ident?i=skb">skb</a>, sizeof(*pig));
<a name="L381" href="source/net/ipv4/igmp.c#L381">381</a>         pig = <a href="ident?i=igmpv3_report_hdr">igmpv3_report_hdr</a>(<a href="ident?i=skb">skb</a>);
<a name="L382" href="source/net/ipv4/igmp.c#L382">382</a>         pig-&gt;<a href="ident?i=type">type</a> = <a href="ident?i=IGMPV3_HOST_MEMBERSHIP_REPORT">IGMPV3_HOST_MEMBERSHIP_REPORT</a>;
<a name="L383" href="source/net/ipv4/igmp.c#L383">383</a>         pig-&gt;resv1 = 0;
<a name="L384" href="source/net/ipv4/igmp.c#L384">384</a>         pig-&gt;<a href="ident?i=csum">csum</a> = 0;
<a name="L385" href="source/net/ipv4/igmp.c#L385">385</a>         pig-&gt;resv2 = 0;
<a name="L386" href="source/net/ipv4/igmp.c#L386">386</a>         pig-&gt;ngrec = 0;
<a name="L387" href="source/net/ipv4/igmp.c#L387">387</a>         return <a href="ident?i=skb">skb</a>;
<a name="L388" href="source/net/ipv4/igmp.c#L388">388</a> }
<a name="L389" href="source/net/ipv4/igmp.c#L389">389</a> 
<a name="L390" href="source/net/ipv4/igmp.c#L390">390</a> static int <a href="ident?i=igmpv3_sendpack">igmpv3_sendpack</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L391" href="source/net/ipv4/igmp.c#L391">391</a> {
<a name="L392" href="source/net/ipv4/igmp.c#L392">392</a>         struct <a href="ident?i=igmphdr">igmphdr</a> *pig = <a href="ident?i=igmp_hdr">igmp_hdr</a>(<a href="ident?i=skb">skb</a>);
<a name="L393" href="source/net/ipv4/igmp.c#L393">393</a>         const int igmplen = <a href="ident?i=skb_tail_pointer">skb_tail_pointer</a>(<a href="ident?i=skb">skb</a>) - <a href="ident?i=skb_transport_header">skb_transport_header</a>(<a href="ident?i=skb">skb</a>);
<a name="L394" href="source/net/ipv4/igmp.c#L394">394</a> 
<a name="L395" href="source/net/ipv4/igmp.c#L395">395</a>         pig-&gt;<a href="ident?i=csum">csum</a> = <a href="ident?i=ip_compute_csum">ip_compute_csum</a>(<a href="ident?i=igmp_hdr">igmp_hdr</a>(<a href="ident?i=skb">skb</a>), igmplen);
<a name="L396" href="source/net/ipv4/igmp.c#L396">396</a> 
<a name="L397" href="source/net/ipv4/igmp.c#L397">397</a>         return <a href="ident?i=ip_local_out">ip_local_out</a>(<a href="ident?i=skb">skb</a>);
<a name="L398" href="source/net/ipv4/igmp.c#L398">398</a> }
<a name="L399" href="source/net/ipv4/igmp.c#L399">399</a> 
<a name="L400" href="source/net/ipv4/igmp.c#L400">400</a> static int <a href="ident?i=grec_size">grec_size</a>(struct <a href="ident?i=ip_mc_list">ip_mc_list</a> *<a href="ident?i=pmc">pmc</a>, int <a href="ident?i=type">type</a>, int gdel, int sdel)
<a name="L401" href="source/net/ipv4/igmp.c#L401">401</a> {
<a name="L402" href="source/net/ipv4/igmp.c#L402">402</a>         return sizeof(struct <a href="ident?i=igmpv3_grec">igmpv3_grec</a>) + 4*<a href="ident?i=igmp_scount">igmp_scount</a>(<a href="ident?i=pmc">pmc</a>, <a href="ident?i=type">type</a>, gdel, sdel);
<a name="L403" href="source/net/ipv4/igmp.c#L403">403</a> }
<a name="L404" href="source/net/ipv4/igmp.c#L404">404</a> 
<a name="L405" href="source/net/ipv4/igmp.c#L405">405</a> static struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=add_grhead">add_grhead</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, struct <a href="ident?i=ip_mc_list">ip_mc_list</a> *<a href="ident?i=pmc">pmc</a>,
<a name="L406" href="source/net/ipv4/igmp.c#L406">406</a>         int <a href="ident?i=type">type</a>, struct <a href="ident?i=igmpv3_grec">igmpv3_grec</a> **ppgr)
<a name="L407" href="source/net/ipv4/igmp.c#L407">407</a> {
<a name="L408" href="source/net/ipv4/igmp.c#L408">408</a>         struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a> = <a href="ident?i=pmc">pmc</a>-&gt;<a href="ident?i=interface">interface</a>-&gt;<a href="ident?i=dev">dev</a>;
<a name="L409" href="source/net/ipv4/igmp.c#L409">409</a>         struct <a href="ident?i=igmpv3_report">igmpv3_report</a> *pih;
<a name="L410" href="source/net/ipv4/igmp.c#L410">410</a>         struct <a href="ident?i=igmpv3_grec">igmpv3_grec</a> *pgr;
<a name="L411" href="source/net/ipv4/igmp.c#L411">411</a> 
<a name="L412" href="source/net/ipv4/igmp.c#L412">412</a>         if (!<a href="ident?i=skb">skb</a>)
<a name="L413" href="source/net/ipv4/igmp.c#L413">413</a>                 <a href="ident?i=skb">skb</a> = <a href="ident?i=igmpv3_newpack">igmpv3_newpack</a>(<a href="ident?i=dev">dev</a>, <a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=mtu">mtu</a>);
<a name="L414" href="source/net/ipv4/igmp.c#L414">414</a>         if (!<a href="ident?i=skb">skb</a>)
<a name="L415" href="source/net/ipv4/igmp.c#L415">415</a>                 return <a href="ident?i=NULL">NULL</a>;
<a name="L416" href="source/net/ipv4/igmp.c#L416">416</a>         pgr = (struct <a href="ident?i=igmpv3_grec">igmpv3_grec</a> *)<a href="ident?i=skb_put">skb_put</a>(<a href="ident?i=skb">skb</a>, sizeof(struct <a href="ident?i=igmpv3_grec">igmpv3_grec</a>));
<a name="L417" href="source/net/ipv4/igmp.c#L417">417</a>         pgr-&gt;grec_type = <a href="ident?i=type">type</a>;
<a name="L418" href="source/net/ipv4/igmp.c#L418">418</a>         pgr-&gt;grec_auxwords = 0;
<a name="L419" href="source/net/ipv4/igmp.c#L419">419</a>         pgr-&gt;grec_nsrcs = 0;
<a name="L420" href="source/net/ipv4/igmp.c#L420">420</a>         pgr-&gt;grec_mca = <a href="ident?i=pmc">pmc</a>-&gt;multiaddr;
<a name="L421" href="source/net/ipv4/igmp.c#L421">421</a>         pih = <a href="ident?i=igmpv3_report_hdr">igmpv3_report_hdr</a>(<a href="ident?i=skb">skb</a>);
<a name="L422" href="source/net/ipv4/igmp.c#L422">422</a>         pih-&gt;ngrec = <a href="ident?i=htons">htons</a>(<a href="ident?i=ntohs">ntohs</a>(pih-&gt;ngrec)+1);
<a name="L423" href="source/net/ipv4/igmp.c#L423">423</a>         *ppgr = pgr;
<a name="L424" href="source/net/ipv4/igmp.c#L424">424</a>         return <a href="ident?i=skb">skb</a>;
<a name="L425" href="source/net/ipv4/igmp.c#L425">425</a> }
<a name="L426" href="source/net/ipv4/igmp.c#L426">426</a> 
<a name="L427" href="source/net/ipv4/igmp.c#L427">427</a> #define <a href="ident?i=AVAILABLE">AVAILABLE</a>(<a href="ident?i=skb">skb</a>)  ((<a href="ident?i=skb">skb</a>) ? <a href="ident?i=skb_availroom">skb_availroom</a>(<a href="ident?i=skb">skb</a>) : 0)
<a name="L428" href="source/net/ipv4/igmp.c#L428">428</a> 
<a name="L429" href="source/net/ipv4/igmp.c#L429">429</a> static struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=add_grec">add_grec</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, struct <a href="ident?i=ip_mc_list">ip_mc_list</a> *<a href="ident?i=pmc">pmc</a>,
<a name="L430" href="source/net/ipv4/igmp.c#L430">430</a>         int <a href="ident?i=type">type</a>, int gdeleted, int sdeleted)
<a name="L431" href="source/net/ipv4/igmp.c#L431">431</a> {
<a name="L432" href="source/net/ipv4/igmp.c#L432">432</a>         struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a> = <a href="ident?i=pmc">pmc</a>-&gt;<a href="ident?i=interface">interface</a>-&gt;<a href="ident?i=dev">dev</a>;
<a name="L433" href="source/net/ipv4/igmp.c#L433">433</a>         struct <a href="ident?i=igmpv3_report">igmpv3_report</a> *pih;
<a name="L434" href="source/net/ipv4/igmp.c#L434">434</a>         struct <a href="ident?i=igmpv3_grec">igmpv3_grec</a> *pgr = <a href="ident?i=NULL">NULL</a>;
<a name="L435" href="source/net/ipv4/igmp.c#L435">435</a>         struct <a href="ident?i=ip_sf_list">ip_sf_list</a> *psf, *psf_next, *psf_prev, **psf_list;
<a name="L436" href="source/net/ipv4/igmp.c#L436">436</a>         int scount, stotal, <a href="ident?i=first">first</a>, isquery, <a href="ident?i=truncate">truncate</a>;
<a name="L437" href="source/net/ipv4/igmp.c#L437">437</a> 
<a name="L438" href="source/net/ipv4/igmp.c#L438">438</a>         if (<a href="ident?i=pmc">pmc</a>-&gt;multiaddr == <a href="ident?i=IGMP_ALL_HOSTS">IGMP_ALL_HOSTS</a>)
<a name="L439" href="source/net/ipv4/igmp.c#L439">439</a>                 return <a href="ident?i=skb">skb</a>;
<a name="L440" href="source/net/ipv4/igmp.c#L440">440</a> 
<a name="L441" href="source/net/ipv4/igmp.c#L441">441</a>         isquery = <a href="ident?i=type">type</a> == <a href="ident?i=IGMPV3_MODE_IS_INCLUDE">IGMPV3_MODE_IS_INCLUDE</a> ||
<a name="L442" href="source/net/ipv4/igmp.c#L442">442</a>                   <a href="ident?i=type">type</a> == <a href="ident?i=IGMPV3_MODE_IS_EXCLUDE">IGMPV3_MODE_IS_EXCLUDE</a>;
<a name="L443" href="source/net/ipv4/igmp.c#L443">443</a>         <a href="ident?i=truncate">truncate</a> = <a href="ident?i=type">type</a> == <a href="ident?i=IGMPV3_MODE_IS_EXCLUDE">IGMPV3_MODE_IS_EXCLUDE</a> ||
<a name="L444" href="source/net/ipv4/igmp.c#L444">444</a>                     <a href="ident?i=type">type</a> == <a href="ident?i=IGMPV3_CHANGE_TO_EXCLUDE">IGMPV3_CHANGE_TO_EXCLUDE</a>;
<a name="L445" href="source/net/ipv4/igmp.c#L445">445</a> 
<a name="L446" href="source/net/ipv4/igmp.c#L446">446</a>         stotal = scount = 0;
<a name="L447" href="source/net/ipv4/igmp.c#L447">447</a> 
<a name="L448" href="source/net/ipv4/igmp.c#L448">448</a>         psf_list = sdeleted ? &amp;<a href="ident?i=pmc">pmc</a>-&gt;tomb : &amp;<a href="ident?i=pmc">pmc</a>-&gt;sources;
<a name="L449" href="source/net/ipv4/igmp.c#L449">449</a> 
<a name="L450" href="source/net/ipv4/igmp.c#L450">450</a>         if (!*psf_list)
<a name="L451" href="source/net/ipv4/igmp.c#L451">451</a>                 goto empty_source;
<a name="L452" href="source/net/ipv4/igmp.c#L452">452</a> 
<a name="L453" href="source/net/ipv4/igmp.c#L453">453</a>         pih = <a href="ident?i=skb">skb</a> ? <a href="ident?i=igmpv3_report_hdr">igmpv3_report_hdr</a>(<a href="ident?i=skb">skb</a>) : <a href="ident?i=NULL">NULL</a>;
<a name="L454" href="source/net/ipv4/igmp.c#L454">454</a> 
<a name="L455" href="source/net/ipv4/igmp.c#L455">455</a>         <b><i>/* EX and TO_EX get a fresh packet, if needed */</i></b>
<a name="L456" href="source/net/ipv4/igmp.c#L456">456</a>         if (<a href="ident?i=truncate">truncate</a>) {
<a name="L457" href="source/net/ipv4/igmp.c#L457">457</a>                 if (pih &amp;&amp; pih-&gt;ngrec &amp;&amp;
<a name="L458" href="source/net/ipv4/igmp.c#L458">458</a>                     <a href="ident?i=AVAILABLE">AVAILABLE</a>(<a href="ident?i=skb">skb</a>) &lt; <a href="ident?i=grec_size">grec_size</a>(<a href="ident?i=pmc">pmc</a>, <a href="ident?i=type">type</a>, gdeleted, sdeleted)) {
<a name="L459" href="source/net/ipv4/igmp.c#L459">459</a>                         if (<a href="ident?i=skb">skb</a>)
<a name="L460" href="source/net/ipv4/igmp.c#L460">460</a>                                 <a href="ident?i=igmpv3_sendpack">igmpv3_sendpack</a>(<a href="ident?i=skb">skb</a>);
<a name="L461" href="source/net/ipv4/igmp.c#L461">461</a>                         <a href="ident?i=skb">skb</a> = <a href="ident?i=igmpv3_newpack">igmpv3_newpack</a>(<a href="ident?i=dev">dev</a>, <a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=mtu">mtu</a>);
<a name="L462" href="source/net/ipv4/igmp.c#L462">462</a>                 }
<a name="L463" href="source/net/ipv4/igmp.c#L463">463</a>         }
<a name="L464" href="source/net/ipv4/igmp.c#L464">464</a>         <a href="ident?i=first">first</a> = 1;
<a name="L465" href="source/net/ipv4/igmp.c#L465">465</a>         psf_prev = <a href="ident?i=NULL">NULL</a>;
<a name="L466" href="source/net/ipv4/igmp.c#L466">466</a>         for (psf = *psf_list; psf; psf = psf_next) {
<a name="L467" href="source/net/ipv4/igmp.c#L467">467</a>                 <a href="ident?i=__be32">__be32</a> *psrc;
<a name="L468" href="source/net/ipv4/igmp.c#L468">468</a> 
<a name="L469" href="source/net/ipv4/igmp.c#L469">469</a>                 psf_next = psf-&gt;sf_next;
<a name="L470" href="source/net/ipv4/igmp.c#L470">470</a> 
<a name="L471" href="source/net/ipv4/igmp.c#L471">471</a>                 if (!<a href="ident?i=is_in">is_in</a>(<a href="ident?i=pmc">pmc</a>, psf, <a href="ident?i=type">type</a>, gdeleted, sdeleted)) {
<a name="L472" href="source/net/ipv4/igmp.c#L472">472</a>                         psf_prev = psf;
<a name="L473" href="source/net/ipv4/igmp.c#L473">473</a>                         continue;
<a name="L474" href="source/net/ipv4/igmp.c#L474">474</a>                 }
<a name="L475" href="source/net/ipv4/igmp.c#L475">475</a> 
<a name="L476" href="source/net/ipv4/igmp.c#L476">476</a>                 <b><i>/* clear marks on query responses */</i></b>
<a name="L477" href="source/net/ipv4/igmp.c#L477">477</a>                 if (isquery)
<a name="L478" href="source/net/ipv4/igmp.c#L478">478</a>                         psf-&gt;sf_gsresp = 0;
<a name="L479" href="source/net/ipv4/igmp.c#L479">479</a> 
<a name="L480" href="source/net/ipv4/igmp.c#L480">480</a>                 if (<a href="ident?i=AVAILABLE">AVAILABLE</a>(<a href="ident?i=skb">skb</a>) &lt; sizeof(<a href="ident?i=__be32">__be32</a>) +
<a name="L481" href="source/net/ipv4/igmp.c#L481">481</a>                     <a href="ident?i=first">first</a>*sizeof(struct <a href="ident?i=igmpv3_grec">igmpv3_grec</a>)) {
<a name="L482" href="source/net/ipv4/igmp.c#L482">482</a>                         if (<a href="ident?i=truncate">truncate</a> &amp;&amp; !<a href="ident?i=first">first</a>)
<a name="L483" href="source/net/ipv4/igmp.c#L483">483</a>                                 break;   <b><i>/* truncate these */</i></b>
<a name="L484" href="source/net/ipv4/igmp.c#L484">484</a>                         if (pgr)
<a name="L485" href="source/net/ipv4/igmp.c#L485">485</a>                                 pgr-&gt;grec_nsrcs = <a href="ident?i=htons">htons</a>(scount);
<a name="L486" href="source/net/ipv4/igmp.c#L486">486</a>                         if (<a href="ident?i=skb">skb</a>)
<a name="L487" href="source/net/ipv4/igmp.c#L487">487</a>                                 <a href="ident?i=igmpv3_sendpack">igmpv3_sendpack</a>(<a href="ident?i=skb">skb</a>);
<a name="L488" href="source/net/ipv4/igmp.c#L488">488</a>                         <a href="ident?i=skb">skb</a> = <a href="ident?i=igmpv3_newpack">igmpv3_newpack</a>(<a href="ident?i=dev">dev</a>, <a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=mtu">mtu</a>);
<a name="L489" href="source/net/ipv4/igmp.c#L489">489</a>                         <a href="ident?i=first">first</a> = 1;
<a name="L490" href="source/net/ipv4/igmp.c#L490">490</a>                         scount = 0;
<a name="L491" href="source/net/ipv4/igmp.c#L491">491</a>                 }
<a name="L492" href="source/net/ipv4/igmp.c#L492">492</a>                 if (<a href="ident?i=first">first</a>) {
<a name="L493" href="source/net/ipv4/igmp.c#L493">493</a>                         <a href="ident?i=skb">skb</a> = <a href="ident?i=add_grhead">add_grhead</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=pmc">pmc</a>, <a href="ident?i=type">type</a>, &amp;pgr);
<a name="L494" href="source/net/ipv4/igmp.c#L494">494</a>                         <a href="ident?i=first">first</a> = 0;
<a name="L495" href="source/net/ipv4/igmp.c#L495">495</a>                 }
<a name="L496" href="source/net/ipv4/igmp.c#L496">496</a>                 if (!<a href="ident?i=skb">skb</a>)
<a name="L497" href="source/net/ipv4/igmp.c#L497">497</a>                         return <a href="ident?i=NULL">NULL</a>;
<a name="L498" href="source/net/ipv4/igmp.c#L498">498</a>                 psrc = (<a href="ident?i=__be32">__be32</a> *)<a href="ident?i=skb_put">skb_put</a>(<a href="ident?i=skb">skb</a>, sizeof(<a href="ident?i=__be32">__be32</a>));
<a name="L499" href="source/net/ipv4/igmp.c#L499">499</a>                 *psrc = psf-&gt;sf_inaddr;
<a name="L500" href="source/net/ipv4/igmp.c#L500">500</a>                 scount++; stotal++;
<a name="L501" href="source/net/ipv4/igmp.c#L501">501</a>                 if ((<a href="ident?i=type">type</a> == <a href="ident?i=IGMPV3_ALLOW_NEW_SOURCES">IGMPV3_ALLOW_NEW_SOURCES</a> ||
<a name="L502" href="source/net/ipv4/igmp.c#L502">502</a>                      <a href="ident?i=type">type</a> == <a href="ident?i=IGMPV3_BLOCK_OLD_SOURCES">IGMPV3_BLOCK_OLD_SOURCES</a>) &amp;&amp; psf-&gt;sf_crcount) {
<a name="L503" href="source/net/ipv4/igmp.c#L503">503</a>                         psf-&gt;sf_crcount--;
<a name="L504" href="source/net/ipv4/igmp.c#L504">504</a>                         if ((sdeleted || gdeleted) &amp;&amp; psf-&gt;sf_crcount == 0) {
<a name="L505" href="source/net/ipv4/igmp.c#L505">505</a>                                 if (psf_prev)
<a name="L506" href="source/net/ipv4/igmp.c#L506">506</a>                                         psf_prev-&gt;sf_next = psf-&gt;sf_next;
<a name="L507" href="source/net/ipv4/igmp.c#L507">507</a>                                 else
<a name="L508" href="source/net/ipv4/igmp.c#L508">508</a>                                         *psf_list = psf-&gt;sf_next;
<a name="L509" href="source/net/ipv4/igmp.c#L509">509</a>                                 <a href="ident?i=kfree">kfree</a>(psf);
<a name="L510" href="source/net/ipv4/igmp.c#L510">510</a>                                 continue;
<a name="L511" href="source/net/ipv4/igmp.c#L511">511</a>                         }
<a name="L512" href="source/net/ipv4/igmp.c#L512">512</a>                 }
<a name="L513" href="source/net/ipv4/igmp.c#L513">513</a>                 psf_prev = psf;
<a name="L514" href="source/net/ipv4/igmp.c#L514">514</a>         }
<a name="L515" href="source/net/ipv4/igmp.c#L515">515</a> 
<a name="L516" href="source/net/ipv4/igmp.c#L516">516</a> empty_source:
<a name="L517" href="source/net/ipv4/igmp.c#L517">517</a>         if (!stotal) {
<a name="L518" href="source/net/ipv4/igmp.c#L518">518</a>                 if (<a href="ident?i=type">type</a> == <a href="ident?i=IGMPV3_ALLOW_NEW_SOURCES">IGMPV3_ALLOW_NEW_SOURCES</a> ||
<a name="L519" href="source/net/ipv4/igmp.c#L519">519</a>                     <a href="ident?i=type">type</a> == <a href="ident?i=IGMPV3_BLOCK_OLD_SOURCES">IGMPV3_BLOCK_OLD_SOURCES</a>)
<a name="L520" href="source/net/ipv4/igmp.c#L520">520</a>                         return <a href="ident?i=skb">skb</a>;
<a name="L521" href="source/net/ipv4/igmp.c#L521">521</a>                 if (<a href="ident?i=pmc">pmc</a>-&gt;crcount || isquery) {
<a name="L522" href="source/net/ipv4/igmp.c#L522">522</a>                         <b><i>/* make sure we have room for group header */</i></b>
<a name="L523" href="source/net/ipv4/igmp.c#L523">523</a>                         if (<a href="ident?i=skb">skb</a> &amp;&amp; <a href="ident?i=AVAILABLE">AVAILABLE</a>(<a href="ident?i=skb">skb</a>) &lt; sizeof(struct <a href="ident?i=igmpv3_grec">igmpv3_grec</a>)) {
<a name="L524" href="source/net/ipv4/igmp.c#L524">524</a>                                 <a href="ident?i=igmpv3_sendpack">igmpv3_sendpack</a>(<a href="ident?i=skb">skb</a>);
<a name="L525" href="source/net/ipv4/igmp.c#L525">525</a>                                 <a href="ident?i=skb">skb</a> = <a href="ident?i=NULL">NULL</a>; <b><i>/* add_grhead will get a new one */</i></b>
<a name="L526" href="source/net/ipv4/igmp.c#L526">526</a>                         }
<a name="L527" href="source/net/ipv4/igmp.c#L527">527</a>                         <a href="ident?i=skb">skb</a> = <a href="ident?i=add_grhead">add_grhead</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=pmc">pmc</a>, <a href="ident?i=type">type</a>, &amp;pgr);
<a name="L528" href="source/net/ipv4/igmp.c#L528">528</a>                 }
<a name="L529" href="source/net/ipv4/igmp.c#L529">529</a>         }
<a name="L530" href="source/net/ipv4/igmp.c#L530">530</a>         if (pgr)
<a name="L531" href="source/net/ipv4/igmp.c#L531">531</a>                 pgr-&gt;grec_nsrcs = <a href="ident?i=htons">htons</a>(scount);
<a name="L532" href="source/net/ipv4/igmp.c#L532">532</a> 
<a name="L533" href="source/net/ipv4/igmp.c#L533">533</a>         if (isquery)
<a name="L534" href="source/net/ipv4/igmp.c#L534">534</a>                 <a href="ident?i=pmc">pmc</a>-&gt;gsquery = 0;       <b><i>/* clear query state on report */</i></b>
<a name="L535" href="source/net/ipv4/igmp.c#L535">535</a>         return <a href="ident?i=skb">skb</a>;
<a name="L536" href="source/net/ipv4/igmp.c#L536">536</a> }
<a name="L537" href="source/net/ipv4/igmp.c#L537">537</a> 
<a name="L538" href="source/net/ipv4/igmp.c#L538">538</a> static int <a href="ident?i=igmpv3_send_report">igmpv3_send_report</a>(struct <a href="ident?i=in_device">in_device</a> *in_dev, struct <a href="ident?i=ip_mc_list">ip_mc_list</a> *<a href="ident?i=pmc">pmc</a>)
<a name="L539" href="source/net/ipv4/igmp.c#L539">539</a> {
<a name="L540" href="source/net/ipv4/igmp.c#L540">540</a>         struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a> = <a href="ident?i=NULL">NULL</a>;
<a name="L541" href="source/net/ipv4/igmp.c#L541">541</a>         int <a href="ident?i=type">type</a>;
<a name="L542" href="source/net/ipv4/igmp.c#L542">542</a> 
<a name="L543" href="source/net/ipv4/igmp.c#L543">543</a>         if (!<a href="ident?i=pmc">pmc</a>) {
<a name="L544" href="source/net/ipv4/igmp.c#L544">544</a>                 <a href="ident?i=rcu_read_lock">rcu_read_lock</a>();
<a name="L545" href="source/net/ipv4/igmp.c#L545">545</a>                 <a href="ident?i=for_each_pmc_rcu">for_each_pmc_rcu</a>(in_dev, <a href="ident?i=pmc">pmc</a>) {
<a name="L546" href="source/net/ipv4/igmp.c#L546">546</a>                         if (<a href="ident?i=pmc">pmc</a>-&gt;multiaddr == <a href="ident?i=IGMP_ALL_HOSTS">IGMP_ALL_HOSTS</a>)
<a name="L547" href="source/net/ipv4/igmp.c#L547">547</a>                                 continue;
<a name="L548" href="source/net/ipv4/igmp.c#L548">548</a>                         <a href="ident?i=spin_lock_bh">spin_lock_bh</a>(&amp;<a href="ident?i=pmc">pmc</a>-&gt;<a href="ident?i=lock">lock</a>);
<a name="L549" href="source/net/ipv4/igmp.c#L549">549</a>                         if (<a href="ident?i=pmc">pmc</a>-&gt;sfcount[<a href="ident?i=MCAST_EXCLUDE">MCAST_EXCLUDE</a>])
<a name="L550" href="source/net/ipv4/igmp.c#L550">550</a>                                 <a href="ident?i=type">type</a> = <a href="ident?i=IGMPV3_MODE_IS_EXCLUDE">IGMPV3_MODE_IS_EXCLUDE</a>;
<a name="L551" href="source/net/ipv4/igmp.c#L551">551</a>                         else
<a name="L552" href="source/net/ipv4/igmp.c#L552">552</a>                                 <a href="ident?i=type">type</a> = <a href="ident?i=IGMPV3_MODE_IS_INCLUDE">IGMPV3_MODE_IS_INCLUDE</a>;
<a name="L553" href="source/net/ipv4/igmp.c#L553">553</a>                         <a href="ident?i=skb">skb</a> = <a href="ident?i=add_grec">add_grec</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=pmc">pmc</a>, <a href="ident?i=type">type</a>, 0, 0);
<a name="L554" href="source/net/ipv4/igmp.c#L554">554</a>                         <a href="ident?i=spin_unlock_bh">spin_unlock_bh</a>(&amp;<a href="ident?i=pmc">pmc</a>-&gt;<a href="ident?i=lock">lock</a>);
<a name="L555" href="source/net/ipv4/igmp.c#L555">555</a>                 }
<a name="L556" href="source/net/ipv4/igmp.c#L556">556</a>                 <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L557" href="source/net/ipv4/igmp.c#L557">557</a>         } else {
<a name="L558" href="source/net/ipv4/igmp.c#L558">558</a>                 <a href="ident?i=spin_lock_bh">spin_lock_bh</a>(&amp;<a href="ident?i=pmc">pmc</a>-&gt;<a href="ident?i=lock">lock</a>);
<a name="L559" href="source/net/ipv4/igmp.c#L559">559</a>                 if (<a href="ident?i=pmc">pmc</a>-&gt;sfcount[<a href="ident?i=MCAST_EXCLUDE">MCAST_EXCLUDE</a>])
<a name="L560" href="source/net/ipv4/igmp.c#L560">560</a>                         <a href="ident?i=type">type</a> = <a href="ident?i=IGMPV3_MODE_IS_EXCLUDE">IGMPV3_MODE_IS_EXCLUDE</a>;
<a name="L561" href="source/net/ipv4/igmp.c#L561">561</a>                 else
<a name="L562" href="source/net/ipv4/igmp.c#L562">562</a>                         <a href="ident?i=type">type</a> = <a href="ident?i=IGMPV3_MODE_IS_INCLUDE">IGMPV3_MODE_IS_INCLUDE</a>;
<a name="L563" href="source/net/ipv4/igmp.c#L563">563</a>                 <a href="ident?i=skb">skb</a> = <a href="ident?i=add_grec">add_grec</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=pmc">pmc</a>, <a href="ident?i=type">type</a>, 0, 0);
<a name="L564" href="source/net/ipv4/igmp.c#L564">564</a>                 <a href="ident?i=spin_unlock_bh">spin_unlock_bh</a>(&amp;<a href="ident?i=pmc">pmc</a>-&gt;<a href="ident?i=lock">lock</a>);
<a name="L565" href="source/net/ipv4/igmp.c#L565">565</a>         }
<a name="L566" href="source/net/ipv4/igmp.c#L566">566</a>         if (!<a href="ident?i=skb">skb</a>)
<a name="L567" href="source/net/ipv4/igmp.c#L567">567</a>                 return 0;
<a name="L568" href="source/net/ipv4/igmp.c#L568">568</a>         return <a href="ident?i=igmpv3_sendpack">igmpv3_sendpack</a>(<a href="ident?i=skb">skb</a>);
<a name="L569" href="source/net/ipv4/igmp.c#L569">569</a> }
<a name="L570" href="source/net/ipv4/igmp.c#L570">570</a> 
<a name="L571" href="source/net/ipv4/igmp.c#L571">571</a> <b><i>/*</i></b>
<a name="L572" href="source/net/ipv4/igmp.c#L572">572</a> <b><i> * remove zero-count source records from a source filter list</i></b>
<a name="L573" href="source/net/ipv4/igmp.c#L573">573</a> <b><i> */</i></b>
<a name="L574" href="source/net/ipv4/igmp.c#L574">574</a> static void <a href="ident?i=igmpv3_clear_zeros">igmpv3_clear_zeros</a>(struct <a href="ident?i=ip_sf_list">ip_sf_list</a> **ppsf)
<a name="L575" href="source/net/ipv4/igmp.c#L575">575</a> {
<a name="L576" href="source/net/ipv4/igmp.c#L576">576</a>         struct <a href="ident?i=ip_sf_list">ip_sf_list</a> *psf_prev, *psf_next, *psf;
<a name="L577" href="source/net/ipv4/igmp.c#L577">577</a> 
<a name="L578" href="source/net/ipv4/igmp.c#L578">578</a>         psf_prev = <a href="ident?i=NULL">NULL</a>;
<a name="L579" href="source/net/ipv4/igmp.c#L579">579</a>         for (psf = *ppsf; psf; psf = psf_next) {
<a name="L580" href="source/net/ipv4/igmp.c#L580">580</a>                 psf_next = psf-&gt;sf_next;
<a name="L581" href="source/net/ipv4/igmp.c#L581">581</a>                 if (psf-&gt;sf_crcount == 0) {
<a name="L582" href="source/net/ipv4/igmp.c#L582">582</a>                         if (psf_prev)
<a name="L583" href="source/net/ipv4/igmp.c#L583">583</a>                                 psf_prev-&gt;sf_next = psf-&gt;sf_next;
<a name="L584" href="source/net/ipv4/igmp.c#L584">584</a>                         else
<a name="L585" href="source/net/ipv4/igmp.c#L585">585</a>                                 *ppsf = psf-&gt;sf_next;
<a name="L586" href="source/net/ipv4/igmp.c#L586">586</a>                         <a href="ident?i=kfree">kfree</a>(psf);
<a name="L587" href="source/net/ipv4/igmp.c#L587">587</a>                 } else
<a name="L588" href="source/net/ipv4/igmp.c#L588">588</a>                         psf_prev = psf;
<a name="L589" href="source/net/ipv4/igmp.c#L589">589</a>         }
<a name="L590" href="source/net/ipv4/igmp.c#L590">590</a> }
<a name="L591" href="source/net/ipv4/igmp.c#L591">591</a> 
<a name="L592" href="source/net/ipv4/igmp.c#L592">592</a> static void <a href="ident?i=igmpv3_send_cr">igmpv3_send_cr</a>(struct <a href="ident?i=in_device">in_device</a> *in_dev)
<a name="L593" href="source/net/ipv4/igmp.c#L593">593</a> {
<a name="L594" href="source/net/ipv4/igmp.c#L594">594</a>         struct <a href="ident?i=ip_mc_list">ip_mc_list</a> *<a href="ident?i=pmc">pmc</a>, *pmc_prev, *pmc_next;
<a name="L595" href="source/net/ipv4/igmp.c#L595">595</a>         struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a> = <a href="ident?i=NULL">NULL</a>;
<a name="L596" href="source/net/ipv4/igmp.c#L596">596</a>         int <a href="ident?i=type">type</a>, dtype;
<a name="L597" href="source/net/ipv4/igmp.c#L597">597</a> 
<a name="L598" href="source/net/ipv4/igmp.c#L598">598</a>         <a href="ident?i=rcu_read_lock">rcu_read_lock</a>();
<a name="L599" href="source/net/ipv4/igmp.c#L599">599</a>         <a href="ident?i=spin_lock_bh">spin_lock_bh</a>(&amp;in_dev-&gt;mc_tomb_lock);
<a name="L600" href="source/net/ipv4/igmp.c#L600">600</a> 
<a name="L601" href="source/net/ipv4/igmp.c#L601">601</a>         <b><i>/* deleted MCA's */</i></b>
<a name="L602" href="source/net/ipv4/igmp.c#L602">602</a>         pmc_prev = <a href="ident?i=NULL">NULL</a>;
<a name="L603" href="source/net/ipv4/igmp.c#L603">603</a>         for (<a href="ident?i=pmc">pmc</a> = in_dev-&gt;mc_tomb; <a href="ident?i=pmc">pmc</a>; <a href="ident?i=pmc">pmc</a> = pmc_next) {
<a name="L604" href="source/net/ipv4/igmp.c#L604">604</a>                 pmc_next = <a href="ident?i=pmc">pmc</a>-&gt;<a href="ident?i=next">next</a>;
<a name="L605" href="source/net/ipv4/igmp.c#L605">605</a>                 if (<a href="ident?i=pmc">pmc</a>-&gt;sfmode == <a href="ident?i=MCAST_INCLUDE">MCAST_INCLUDE</a>) {
<a name="L606" href="source/net/ipv4/igmp.c#L606">606</a>                         <a href="ident?i=type">type</a> = <a href="ident?i=IGMPV3_BLOCK_OLD_SOURCES">IGMPV3_BLOCK_OLD_SOURCES</a>;
<a name="L607" href="source/net/ipv4/igmp.c#L607">607</a>                         dtype = <a href="ident?i=IGMPV3_BLOCK_OLD_SOURCES">IGMPV3_BLOCK_OLD_SOURCES</a>;
<a name="L608" href="source/net/ipv4/igmp.c#L608">608</a>                         <a href="ident?i=skb">skb</a> = <a href="ident?i=add_grec">add_grec</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=pmc">pmc</a>, <a href="ident?i=type">type</a>, 1, 0);
<a name="L609" href="source/net/ipv4/igmp.c#L609">609</a>                         <a href="ident?i=skb">skb</a> = <a href="ident?i=add_grec">add_grec</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=pmc">pmc</a>, dtype, 1, 1);
<a name="L610" href="source/net/ipv4/igmp.c#L610">610</a>                 }
<a name="L611" href="source/net/ipv4/igmp.c#L611">611</a>                 if (<a href="ident?i=pmc">pmc</a>-&gt;crcount) {
<a name="L612" href="source/net/ipv4/igmp.c#L612">612</a>                         if (<a href="ident?i=pmc">pmc</a>-&gt;sfmode == <a href="ident?i=MCAST_EXCLUDE">MCAST_EXCLUDE</a>) {
<a name="L613" href="source/net/ipv4/igmp.c#L613">613</a>                                 <a href="ident?i=type">type</a> = <a href="ident?i=IGMPV3_CHANGE_TO_INCLUDE">IGMPV3_CHANGE_TO_INCLUDE</a>;
<a name="L614" href="source/net/ipv4/igmp.c#L614">614</a>                                 <a href="ident?i=skb">skb</a> = <a href="ident?i=add_grec">add_grec</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=pmc">pmc</a>, <a href="ident?i=type">type</a>, 1, 0);
<a name="L615" href="source/net/ipv4/igmp.c#L615">615</a>                         }
<a name="L616" href="source/net/ipv4/igmp.c#L616">616</a>                         <a href="ident?i=pmc">pmc</a>-&gt;crcount--;
<a name="L617" href="source/net/ipv4/igmp.c#L617">617</a>                         if (<a href="ident?i=pmc">pmc</a>-&gt;crcount == 0) {
<a name="L618" href="source/net/ipv4/igmp.c#L618">618</a>                                 <a href="ident?i=igmpv3_clear_zeros">igmpv3_clear_zeros</a>(&amp;<a href="ident?i=pmc">pmc</a>-&gt;tomb);
<a name="L619" href="source/net/ipv4/igmp.c#L619">619</a>                                 <a href="ident?i=igmpv3_clear_zeros">igmpv3_clear_zeros</a>(&amp;<a href="ident?i=pmc">pmc</a>-&gt;sources);
<a name="L620" href="source/net/ipv4/igmp.c#L620">620</a>                         }
<a name="L621" href="source/net/ipv4/igmp.c#L621">621</a>                 }
<a name="L622" href="source/net/ipv4/igmp.c#L622">622</a>                 if (<a href="ident?i=pmc">pmc</a>-&gt;crcount == 0 &amp;&amp; !<a href="ident?i=pmc">pmc</a>-&gt;tomb &amp;&amp; !<a href="ident?i=pmc">pmc</a>-&gt;sources) {
<a name="L623" href="source/net/ipv4/igmp.c#L623">623</a>                         if (pmc_prev)
<a name="L624" href="source/net/ipv4/igmp.c#L624">624</a>                                 pmc_prev-&gt;<a href="ident?i=next">next</a> = pmc_next;
<a name="L625" href="source/net/ipv4/igmp.c#L625">625</a>                         else
<a name="L626" href="source/net/ipv4/igmp.c#L626">626</a>                                 in_dev-&gt;mc_tomb = pmc_next;
<a name="L627" href="source/net/ipv4/igmp.c#L627">627</a>                         <a href="ident?i=in_dev_put">in_dev_put</a>(<a href="ident?i=pmc">pmc</a>-&gt;<a href="ident?i=interface">interface</a>);
<a name="L628" href="source/net/ipv4/igmp.c#L628">628</a>                         <a href="ident?i=kfree">kfree</a>(<a href="ident?i=pmc">pmc</a>);
<a name="L629" href="source/net/ipv4/igmp.c#L629">629</a>                 } else
<a name="L630" href="source/net/ipv4/igmp.c#L630">630</a>                         pmc_prev = <a href="ident?i=pmc">pmc</a>;
<a name="L631" href="source/net/ipv4/igmp.c#L631">631</a>         }
<a name="L632" href="source/net/ipv4/igmp.c#L632">632</a>         <a href="ident?i=spin_unlock_bh">spin_unlock_bh</a>(&amp;in_dev-&gt;mc_tomb_lock);
<a name="L633" href="source/net/ipv4/igmp.c#L633">633</a> 
<a name="L634" href="source/net/ipv4/igmp.c#L634">634</a>         <b><i>/* change recs */</i></b>
<a name="L635" href="source/net/ipv4/igmp.c#L635">635</a>         <a href="ident?i=for_each_pmc_rcu">for_each_pmc_rcu</a>(in_dev, <a href="ident?i=pmc">pmc</a>) {
<a name="L636" href="source/net/ipv4/igmp.c#L636">636</a>                 <a href="ident?i=spin_lock_bh">spin_lock_bh</a>(&amp;<a href="ident?i=pmc">pmc</a>-&gt;<a href="ident?i=lock">lock</a>);
<a name="L637" href="source/net/ipv4/igmp.c#L637">637</a>                 if (<a href="ident?i=pmc">pmc</a>-&gt;sfcount[<a href="ident?i=MCAST_EXCLUDE">MCAST_EXCLUDE</a>]) {
<a name="L638" href="source/net/ipv4/igmp.c#L638">638</a>                         <a href="ident?i=type">type</a> = <a href="ident?i=IGMPV3_BLOCK_OLD_SOURCES">IGMPV3_BLOCK_OLD_SOURCES</a>;
<a name="L639" href="source/net/ipv4/igmp.c#L639">639</a>                         dtype = <a href="ident?i=IGMPV3_ALLOW_NEW_SOURCES">IGMPV3_ALLOW_NEW_SOURCES</a>;
<a name="L640" href="source/net/ipv4/igmp.c#L640">640</a>                 } else {
<a name="L641" href="source/net/ipv4/igmp.c#L641">641</a>                         <a href="ident?i=type">type</a> = <a href="ident?i=IGMPV3_ALLOW_NEW_SOURCES">IGMPV3_ALLOW_NEW_SOURCES</a>;
<a name="L642" href="source/net/ipv4/igmp.c#L642">642</a>                         dtype = <a href="ident?i=IGMPV3_BLOCK_OLD_SOURCES">IGMPV3_BLOCK_OLD_SOURCES</a>;
<a name="L643" href="source/net/ipv4/igmp.c#L643">643</a>                 }
<a name="L644" href="source/net/ipv4/igmp.c#L644">644</a>                 <a href="ident?i=skb">skb</a> = <a href="ident?i=add_grec">add_grec</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=pmc">pmc</a>, <a href="ident?i=type">type</a>, 0, 0);
<a name="L645" href="source/net/ipv4/igmp.c#L645">645</a>                 <a href="ident?i=skb">skb</a> = <a href="ident?i=add_grec">add_grec</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=pmc">pmc</a>, dtype, 0, 1);  <b><i>/* deleted sources */</i></b>
<a name="L646" href="source/net/ipv4/igmp.c#L646">646</a> 
<a name="L647" href="source/net/ipv4/igmp.c#L647">647</a>                 <b><i>/* filter mode changes */</i></b>
<a name="L648" href="source/net/ipv4/igmp.c#L648">648</a>                 if (<a href="ident?i=pmc">pmc</a>-&gt;crcount) {
<a name="L649" href="source/net/ipv4/igmp.c#L649">649</a>                         if (<a href="ident?i=pmc">pmc</a>-&gt;sfmode == <a href="ident?i=MCAST_EXCLUDE">MCAST_EXCLUDE</a>)
<a name="L650" href="source/net/ipv4/igmp.c#L650">650</a>                                 <a href="ident?i=type">type</a> = <a href="ident?i=IGMPV3_CHANGE_TO_EXCLUDE">IGMPV3_CHANGE_TO_EXCLUDE</a>;
<a name="L651" href="source/net/ipv4/igmp.c#L651">651</a>                         else
<a name="L652" href="source/net/ipv4/igmp.c#L652">652</a>                                 <a href="ident?i=type">type</a> = <a href="ident?i=IGMPV3_CHANGE_TO_INCLUDE">IGMPV3_CHANGE_TO_INCLUDE</a>;
<a name="L653" href="source/net/ipv4/igmp.c#L653">653</a>                         <a href="ident?i=skb">skb</a> = <a href="ident?i=add_grec">add_grec</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=pmc">pmc</a>, <a href="ident?i=type">type</a>, 0, 0);
<a name="L654" href="source/net/ipv4/igmp.c#L654">654</a>                         <a href="ident?i=pmc">pmc</a>-&gt;crcount--;
<a name="L655" href="source/net/ipv4/igmp.c#L655">655</a>                 }
<a name="L656" href="source/net/ipv4/igmp.c#L656">656</a>                 <a href="ident?i=spin_unlock_bh">spin_unlock_bh</a>(&amp;<a href="ident?i=pmc">pmc</a>-&gt;<a href="ident?i=lock">lock</a>);
<a name="L657" href="source/net/ipv4/igmp.c#L657">657</a>         }
<a name="L658" href="source/net/ipv4/igmp.c#L658">658</a>         <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L659" href="source/net/ipv4/igmp.c#L659">659</a> 
<a name="L660" href="source/net/ipv4/igmp.c#L660">660</a>         if (!<a href="ident?i=skb">skb</a>)
<a name="L661" href="source/net/ipv4/igmp.c#L661">661</a>                 return;
<a name="L662" href="source/net/ipv4/igmp.c#L662">662</a>         (void) <a href="ident?i=igmpv3_sendpack">igmpv3_sendpack</a>(<a href="ident?i=skb">skb</a>);
<a name="L663" href="source/net/ipv4/igmp.c#L663">663</a> }
<a name="L664" href="source/net/ipv4/igmp.c#L664">664</a> 
<a name="L665" href="source/net/ipv4/igmp.c#L665">665</a> static int <a href="ident?i=igmp_send_report">igmp_send_report</a>(struct <a href="ident?i=in_device">in_device</a> *in_dev, struct <a href="ident?i=ip_mc_list">ip_mc_list</a> *<a href="ident?i=pmc">pmc</a>,
<a name="L666" href="source/net/ipv4/igmp.c#L666">666</a>         int <a href="ident?i=type">type</a>)
<a name="L667" href="source/net/ipv4/igmp.c#L667">667</a> {
<a name="L668" href="source/net/ipv4/igmp.c#L668">668</a>         struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>;
<a name="L669" href="source/net/ipv4/igmp.c#L669">669</a>         struct <a href="ident?i=iphdr">iphdr</a> *iph;
<a name="L670" href="source/net/ipv4/igmp.c#L670">670</a>         struct <a href="ident?i=igmphdr">igmphdr</a> *ih;
<a name="L671" href="source/net/ipv4/igmp.c#L671">671</a>         struct <a href="ident?i=rtable">rtable</a> *<a href="ident?i=rt">rt</a>;
<a name="L672" href="source/net/ipv4/igmp.c#L672">672</a>         struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a> = in_dev-&gt;<a href="ident?i=dev">dev</a>;
<a name="L673" href="source/net/ipv4/igmp.c#L673">673</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=dev">dev</a>);
<a name="L674" href="source/net/ipv4/igmp.c#L674">674</a>         <a href="ident?i=__be32">__be32</a>  <a href="ident?i=group">group</a> = <a href="ident?i=pmc">pmc</a> ? <a href="ident?i=pmc">pmc</a>-&gt;multiaddr : 0;
<a name="L675" href="source/net/ipv4/igmp.c#L675">675</a>         struct <a href="ident?i=flowi4">flowi4</a> fl4;
<a name="L676" href="source/net/ipv4/igmp.c#L676">676</a>         <a href="ident?i=__be32">__be32</a>  <a href="ident?i=dst">dst</a>;
<a name="L677" href="source/net/ipv4/igmp.c#L677">677</a>         int hlen, tlen;
<a name="L678" href="source/net/ipv4/igmp.c#L678">678</a> 
<a name="L679" href="source/net/ipv4/igmp.c#L679">679</a>         if (<a href="ident?i=type">type</a> == <a href="ident?i=IGMPV3_HOST_MEMBERSHIP_REPORT">IGMPV3_HOST_MEMBERSHIP_REPORT</a>)
<a name="L680" href="source/net/ipv4/igmp.c#L680">680</a>                 return <a href="ident?i=igmpv3_send_report">igmpv3_send_report</a>(in_dev, <a href="ident?i=pmc">pmc</a>);
<a name="L681" href="source/net/ipv4/igmp.c#L681">681</a>         else if (<a href="ident?i=type">type</a> == <a href="ident?i=IGMP_HOST_LEAVE_MESSAGE">IGMP_HOST_LEAVE_MESSAGE</a>)
<a name="L682" href="source/net/ipv4/igmp.c#L682">682</a>                 <a href="ident?i=dst">dst</a> = <a href="ident?i=IGMP_ALL_ROUTER">IGMP_ALL_ROUTER</a>;
<a name="L683" href="source/net/ipv4/igmp.c#L683">683</a>         else
<a name="L684" href="source/net/ipv4/igmp.c#L684">684</a>                 <a href="ident?i=dst">dst</a> = <a href="ident?i=group">group</a>;
<a name="L685" href="source/net/ipv4/igmp.c#L685">685</a> 
<a name="L686" href="source/net/ipv4/igmp.c#L686">686</a>         <a href="ident?i=rt">rt</a> = <a href="ident?i=ip_route_output_ports">ip_route_output_ports</a>(<a href="ident?i=net">net</a>, &amp;fl4, <a href="ident?i=NULL">NULL</a>, <a href="ident?i=dst">dst</a>, 0,
<a name="L687" href="source/net/ipv4/igmp.c#L687">687</a>                                    0, 0,
<a name="L688" href="source/net/ipv4/igmp.c#L688">688</a>                                    <a href="ident?i=IPPROTO_IGMP">IPPROTO_IGMP</a>, 0, <a href="ident?i=dev">dev</a>-&gt;ifindex);
<a name="L689" href="source/net/ipv4/igmp.c#L689">689</a>         if (<a href="ident?i=IS_ERR">IS_ERR</a>(<a href="ident?i=rt">rt</a>))
<a name="L690" href="source/net/ipv4/igmp.c#L690">690</a>                 return -1;
<a name="L691" href="source/net/ipv4/igmp.c#L691">691</a> 
<a name="L692" href="source/net/ipv4/igmp.c#L692">692</a>         hlen = <a href="ident?i=LL_RESERVED_SPACE">LL_RESERVED_SPACE</a>(<a href="ident?i=dev">dev</a>);
<a name="L693" href="source/net/ipv4/igmp.c#L693">693</a>         tlen = <a href="ident?i=dev">dev</a>-&gt;needed_tailroom;
<a name="L694" href="source/net/ipv4/igmp.c#L694">694</a>         <a href="ident?i=skb">skb</a> = <a href="ident?i=alloc_skb">alloc_skb</a>(<a href="ident?i=IGMP_SIZE">IGMP_SIZE</a> + hlen + tlen, <a href="ident?i=GFP_ATOMIC">GFP_ATOMIC</a>);
<a name="L695" href="source/net/ipv4/igmp.c#L695">695</a>         if (!<a href="ident?i=skb">skb</a>) {
<a name="L696" href="source/net/ipv4/igmp.c#L696">696</a>                 <a href="ident?i=ip_rt_put">ip_rt_put</a>(<a href="ident?i=rt">rt</a>);
<a name="L697" href="source/net/ipv4/igmp.c#L697">697</a>                 return -1;
<a name="L698" href="source/net/ipv4/igmp.c#L698">698</a>         }
<a name="L699" href="source/net/ipv4/igmp.c#L699">699</a>         <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=priority">priority</a> = <a href="ident?i=TC_PRIO_CONTROL">TC_PRIO_CONTROL</a>;
<a name="L700" href="source/net/ipv4/igmp.c#L700">700</a> 
<a name="L701" href="source/net/ipv4/igmp.c#L701">701</a>         <a href="ident?i=skb_dst_set">skb_dst_set</a>(<a href="ident?i=skb">skb</a>, &amp;<a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>);
<a name="L702" href="source/net/ipv4/igmp.c#L702">702</a> 
<a name="L703" href="source/net/ipv4/igmp.c#L703">703</a>         <a href="ident?i=skb_reserve">skb_reserve</a>(<a href="ident?i=skb">skb</a>, hlen);
<a name="L704" href="source/net/ipv4/igmp.c#L704">704</a> 
<a name="L705" href="source/net/ipv4/igmp.c#L705">705</a>         <a href="ident?i=skb_reset_network_header">skb_reset_network_header</a>(<a href="ident?i=skb">skb</a>);
<a name="L706" href="source/net/ipv4/igmp.c#L706">706</a>         iph = <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>);
<a name="L707" href="source/net/ipv4/igmp.c#L707">707</a>         <a href="ident?i=skb_put">skb_put</a>(<a href="ident?i=skb">skb</a>, sizeof(struct <a href="ident?i=iphdr">iphdr</a>) + 4);
<a name="L708" href="source/net/ipv4/igmp.c#L708">708</a> 
<a name="L709" href="source/net/ipv4/igmp.c#L709">709</a>         iph-&gt;<a href="ident?i=version">version</a>  = 4;
<a name="L710" href="source/net/ipv4/igmp.c#L710">710</a>         iph-&gt;ihl      = (sizeof(struct <a href="ident?i=iphdr">iphdr</a>)+4)&gt;&gt;2;
<a name="L711" href="source/net/ipv4/igmp.c#L711">711</a>         iph-&gt;tos      = 0xc0;
<a name="L712" href="source/net/ipv4/igmp.c#L712">712</a>         iph-&gt;frag_off = <a href="ident?i=htons">htons</a>(<a href="ident?i=IP_DF">IP_DF</a>);
<a name="L713" href="source/net/ipv4/igmp.c#L713">713</a>         iph-&gt;<a href="ident?i=ttl">ttl</a>      = 1;
<a name="L714" href="source/net/ipv4/igmp.c#L714">714</a>         iph-&gt;<a href="ident?i=daddr">daddr</a>    = <a href="ident?i=dst">dst</a>;
<a name="L715" href="source/net/ipv4/igmp.c#L715">715</a>         iph-&gt;<a href="ident?i=saddr">saddr</a>    = fl4.<a href="ident?i=saddr">saddr</a>;
<a name="L716" href="source/net/ipv4/igmp.c#L716">716</a>         iph-&gt;<a href="ident?i=protocol">protocol</a> = <a href="ident?i=IPPROTO_IGMP">IPPROTO_IGMP</a>;
<a name="L717" href="source/net/ipv4/igmp.c#L717">717</a>         <a href="ident?i=ip_select_ident">ip_select_ident</a>(<a href="ident?i=net">net</a>, <a href="ident?i=skb">skb</a>, <a href="ident?i=NULL">NULL</a>);
<a name="L718" href="source/net/ipv4/igmp.c#L718">718</a>         ((<a href="ident?i=u8">u8</a> *)&amp;iph[1])[0] = <a href="ident?i=IPOPT_RA">IPOPT_RA</a>;
<a name="L719" href="source/net/ipv4/igmp.c#L719">719</a>         ((<a href="ident?i=u8">u8</a> *)&amp;iph[1])[1] = 4;
<a name="L720" href="source/net/ipv4/igmp.c#L720">720</a>         ((<a href="ident?i=u8">u8</a> *)&amp;iph[1])[2] = 0;
<a name="L721" href="source/net/ipv4/igmp.c#L721">721</a>         ((<a href="ident?i=u8">u8</a> *)&amp;iph[1])[3] = 0;
<a name="L722" href="source/net/ipv4/igmp.c#L722">722</a> 
<a name="L723" href="source/net/ipv4/igmp.c#L723">723</a>         ih = (struct <a href="ident?i=igmphdr">igmphdr</a> *)<a href="ident?i=skb_put">skb_put</a>(<a href="ident?i=skb">skb</a>, sizeof(struct <a href="ident?i=igmphdr">igmphdr</a>));
<a name="L724" href="source/net/ipv4/igmp.c#L724">724</a>         ih-&gt;<a href="ident?i=type">type</a> = <a href="ident?i=type">type</a>;
<a name="L725" href="source/net/ipv4/igmp.c#L725">725</a>         ih-&gt;<a href="ident?i=code">code</a> = 0;
<a name="L726" href="source/net/ipv4/igmp.c#L726">726</a>         ih-&gt;<a href="ident?i=csum">csum</a> = 0;
<a name="L727" href="source/net/ipv4/igmp.c#L727">727</a>         ih-&gt;<a href="ident?i=group">group</a> = <a href="ident?i=group">group</a>;
<a name="L728" href="source/net/ipv4/igmp.c#L728">728</a>         ih-&gt;<a href="ident?i=csum">csum</a> = <a href="ident?i=ip_compute_csum">ip_compute_csum</a>((void *)ih, sizeof(struct <a href="ident?i=igmphdr">igmphdr</a>));
<a name="L729" href="source/net/ipv4/igmp.c#L729">729</a> 
<a name="L730" href="source/net/ipv4/igmp.c#L730">730</a>         return <a href="ident?i=ip_local_out">ip_local_out</a>(<a href="ident?i=skb">skb</a>);
<a name="L731" href="source/net/ipv4/igmp.c#L731">731</a> }
<a name="L732" href="source/net/ipv4/igmp.c#L732">732</a> 
<a name="L733" href="source/net/ipv4/igmp.c#L733">733</a> static void <a href="ident?i=igmp_gq_timer_expire">igmp_gq_timer_expire</a>(unsigned long <a href="ident?i=data">data</a>)
<a name="L734" href="source/net/ipv4/igmp.c#L734">734</a> {
<a name="L735" href="source/net/ipv4/igmp.c#L735">735</a>         struct <a href="ident?i=in_device">in_device</a> *in_dev = (struct <a href="ident?i=in_device">in_device</a> *)<a href="ident?i=data">data</a>;
<a name="L736" href="source/net/ipv4/igmp.c#L736">736</a> 
<a name="L737" href="source/net/ipv4/igmp.c#L737">737</a>         in_dev-&gt;mr_gq_running = 0;
<a name="L738" href="source/net/ipv4/igmp.c#L738">738</a>         <a href="ident?i=igmpv3_send_report">igmpv3_send_report</a>(in_dev, <a href="ident?i=NULL">NULL</a>);
<a name="L739" href="source/net/ipv4/igmp.c#L739">739</a>         <a href="ident?i=in_dev_put">in_dev_put</a>(in_dev);
<a name="L740" href="source/net/ipv4/igmp.c#L740">740</a> }
<a name="L741" href="source/net/ipv4/igmp.c#L741">741</a> 
<a name="L742" href="source/net/ipv4/igmp.c#L742">742</a> static void <a href="ident?i=igmp_ifc_timer_expire">igmp_ifc_timer_expire</a>(unsigned long <a href="ident?i=data">data</a>)
<a name="L743" href="source/net/ipv4/igmp.c#L743">743</a> {
<a name="L744" href="source/net/ipv4/igmp.c#L744">744</a>         struct <a href="ident?i=in_device">in_device</a> *in_dev = (struct <a href="ident?i=in_device">in_device</a> *)<a href="ident?i=data">data</a>;
<a name="L745" href="source/net/ipv4/igmp.c#L745">745</a> 
<a name="L746" href="source/net/ipv4/igmp.c#L746">746</a>         <a href="ident?i=igmpv3_send_cr">igmpv3_send_cr</a>(in_dev);
<a name="L747" href="source/net/ipv4/igmp.c#L747">747</a>         if (in_dev-&gt;mr_ifc_count) {
<a name="L748" href="source/net/ipv4/igmp.c#L748">748</a>                 in_dev-&gt;mr_ifc_count--;
<a name="L749" href="source/net/ipv4/igmp.c#L749">749</a>                 <a href="ident?i=igmp_ifc_start_timer">igmp_ifc_start_timer</a>(in_dev,
<a name="L750" href="source/net/ipv4/igmp.c#L750">750</a>                                      <a href="ident?i=unsolicited_report_interval">unsolicited_report_interval</a>(in_dev));
<a name="L751" href="source/net/ipv4/igmp.c#L751">751</a>         }
<a name="L752" href="source/net/ipv4/igmp.c#L752">752</a>         <a href="ident?i=in_dev_put">in_dev_put</a>(in_dev);
<a name="L753" href="source/net/ipv4/igmp.c#L753">753</a> }
<a name="L754" href="source/net/ipv4/igmp.c#L754">754</a> 
<a name="L755" href="source/net/ipv4/igmp.c#L755">755</a> static void <a href="ident?i=igmp_ifc_event">igmp_ifc_event</a>(struct <a href="ident?i=in_device">in_device</a> *in_dev)
<a name="L756" href="source/net/ipv4/igmp.c#L756">756</a> {
<a name="L757" href="source/net/ipv4/igmp.c#L757">757</a>         if (<a href="ident?i=IGMP_V1_SEEN">IGMP_V1_SEEN</a>(in_dev) || <a href="ident?i=IGMP_V2_SEEN">IGMP_V2_SEEN</a>(in_dev))
<a name="L758" href="source/net/ipv4/igmp.c#L758">758</a>                 return;
<a name="L759" href="source/net/ipv4/igmp.c#L759">759</a>         in_dev-&gt;mr_ifc_count = in_dev-&gt;mr_qrv ?: <a href="ident?i=sysctl_igmp_qrv">sysctl_igmp_qrv</a>;
<a name="L760" href="source/net/ipv4/igmp.c#L760">760</a>         <a href="ident?i=igmp_ifc_start_timer">igmp_ifc_start_timer</a>(in_dev, 1);
<a name="L761" href="source/net/ipv4/igmp.c#L761">761</a> }
<a name="L762" href="source/net/ipv4/igmp.c#L762">762</a> 
<a name="L763" href="source/net/ipv4/igmp.c#L763">763</a> 
<a name="L764" href="source/net/ipv4/igmp.c#L764">764</a> static void <a href="ident?i=igmp_timer_expire">igmp_timer_expire</a>(unsigned long <a href="ident?i=data">data</a>)
<a name="L765" href="source/net/ipv4/igmp.c#L765">765</a> {
<a name="L766" href="source/net/ipv4/igmp.c#L766">766</a>         struct <a href="ident?i=ip_mc_list">ip_mc_list</a> *im = (struct <a href="ident?i=ip_mc_list">ip_mc_list</a> *)<a href="ident?i=data">data</a>;
<a name="L767" href="source/net/ipv4/igmp.c#L767">767</a>         struct <a href="ident?i=in_device">in_device</a> *in_dev = im-&gt;<a href="ident?i=interface">interface</a>;
<a name="L768" href="source/net/ipv4/igmp.c#L768">768</a> 
<a name="L769" href="source/net/ipv4/igmp.c#L769">769</a>         <a href="ident?i=spin_lock">spin_lock</a>(&amp;im-&gt;<a href="ident?i=lock">lock</a>);
<a name="L770" href="source/net/ipv4/igmp.c#L770">770</a>         im-&gt;tm_running = 0;
<a name="L771" href="source/net/ipv4/igmp.c#L771">771</a> 
<a name="L772" href="source/net/ipv4/igmp.c#L772">772</a>         if (im-&gt;unsolicit_count) {
<a name="L773" href="source/net/ipv4/igmp.c#L773">773</a>                 im-&gt;unsolicit_count--;
<a name="L774" href="source/net/ipv4/igmp.c#L774">774</a>                 <a href="ident?i=igmp_start_timer">igmp_start_timer</a>(im, <a href="ident?i=unsolicited_report_interval">unsolicited_report_interval</a>(in_dev));
<a name="L775" href="source/net/ipv4/igmp.c#L775">775</a>         }
<a name="L776" href="source/net/ipv4/igmp.c#L776">776</a>         im-&gt;reporter = 1;
<a name="L777" href="source/net/ipv4/igmp.c#L777">777</a>         <a href="ident?i=spin_unlock">spin_unlock</a>(&amp;im-&gt;<a href="ident?i=lock">lock</a>);
<a name="L778" href="source/net/ipv4/igmp.c#L778">778</a> 
<a name="L779" href="source/net/ipv4/igmp.c#L779">779</a>         if (<a href="ident?i=IGMP_V1_SEEN">IGMP_V1_SEEN</a>(in_dev))
<a name="L780" href="source/net/ipv4/igmp.c#L780">780</a>                 <a href="ident?i=igmp_send_report">igmp_send_report</a>(in_dev, im, <a href="ident?i=IGMP_HOST_MEMBERSHIP_REPORT">IGMP_HOST_MEMBERSHIP_REPORT</a>);
<a name="L781" href="source/net/ipv4/igmp.c#L781">781</a>         else if (<a href="ident?i=IGMP_V2_SEEN">IGMP_V2_SEEN</a>(in_dev))
<a name="L782" href="source/net/ipv4/igmp.c#L782">782</a>                 <a href="ident?i=igmp_send_report">igmp_send_report</a>(in_dev, im, <a href="ident?i=IGMPV2_HOST_MEMBERSHIP_REPORT">IGMPV2_HOST_MEMBERSHIP_REPORT</a>);
<a name="L783" href="source/net/ipv4/igmp.c#L783">783</a>         else
<a name="L784" href="source/net/ipv4/igmp.c#L784">784</a>                 <a href="ident?i=igmp_send_report">igmp_send_report</a>(in_dev, im, <a href="ident?i=IGMPV3_HOST_MEMBERSHIP_REPORT">IGMPV3_HOST_MEMBERSHIP_REPORT</a>);
<a name="L785" href="source/net/ipv4/igmp.c#L785">785</a> 
<a name="L786" href="source/net/ipv4/igmp.c#L786">786</a>         <a href="ident?i=ip_ma_put">ip_ma_put</a>(im);
<a name="L787" href="source/net/ipv4/igmp.c#L787">787</a> }
<a name="L788" href="source/net/ipv4/igmp.c#L788">788</a> 
<a name="L789" href="source/net/ipv4/igmp.c#L789">789</a> <b><i>/* mark EXCLUDE-mode sources */</i></b>
<a name="L790" href="source/net/ipv4/igmp.c#L790">790</a> static int <a href="ident?i=igmp_xmarksources">igmp_xmarksources</a>(struct <a href="ident?i=ip_mc_list">ip_mc_list</a> *<a href="ident?i=pmc">pmc</a>, int nsrcs, <a href="ident?i=__be32">__be32</a> *srcs)
<a name="L791" href="source/net/ipv4/igmp.c#L791">791</a> {
<a name="L792" href="source/net/ipv4/igmp.c#L792">792</a>         struct <a href="ident?i=ip_sf_list">ip_sf_list</a> *psf;
<a name="L793" href="source/net/ipv4/igmp.c#L793">793</a>         int <a href="ident?i=i">i</a>, scount;
<a name="L794" href="source/net/ipv4/igmp.c#L794">794</a> 
<a name="L795" href="source/net/ipv4/igmp.c#L795">795</a>         scount = 0;
<a name="L796" href="source/net/ipv4/igmp.c#L796">796</a>         for (psf = <a href="ident?i=pmc">pmc</a>-&gt;sources; psf; psf = psf-&gt;sf_next) {
<a name="L797" href="source/net/ipv4/igmp.c#L797">797</a>                 if (scount == nsrcs)
<a name="L798" href="source/net/ipv4/igmp.c#L798">798</a>                         break;
<a name="L799" href="source/net/ipv4/igmp.c#L799">799</a>                 for (<a href="ident?i=i">i</a> = 0; <a href="ident?i=i">i</a> &lt; nsrcs; <a href="ident?i=i">i</a>++) {
<a name="L800" href="source/net/ipv4/igmp.c#L800">800</a>                         <b><i>/* skip inactive filters */</i></b>
<a name="L801" href="source/net/ipv4/igmp.c#L801">801</a>                         if (psf-&gt;sf_count[<a href="ident?i=MCAST_INCLUDE">MCAST_INCLUDE</a>] ||
<a name="L802" href="source/net/ipv4/igmp.c#L802">802</a>                             <a href="ident?i=pmc">pmc</a>-&gt;sfcount[<a href="ident?i=MCAST_EXCLUDE">MCAST_EXCLUDE</a>] !=
<a name="L803" href="source/net/ipv4/igmp.c#L803">803</a>                             psf-&gt;sf_count[<a href="ident?i=MCAST_EXCLUDE">MCAST_EXCLUDE</a>])
<a name="L804" href="source/net/ipv4/igmp.c#L804">804</a>                                 break;
<a name="L805" href="source/net/ipv4/igmp.c#L805">805</a>                         if (srcs[<a href="ident?i=i">i</a>] == psf-&gt;sf_inaddr) {
<a name="L806" href="source/net/ipv4/igmp.c#L806">806</a>                                 scount++;
<a name="L807" href="source/net/ipv4/igmp.c#L807">807</a>                                 break;
<a name="L808" href="source/net/ipv4/igmp.c#L808">808</a>                         }
<a name="L809" href="source/net/ipv4/igmp.c#L809">809</a>                 }
<a name="L810" href="source/net/ipv4/igmp.c#L810">810</a>         }
<a name="L811" href="source/net/ipv4/igmp.c#L811">811</a>         <a href="ident?i=pmc">pmc</a>-&gt;gsquery = 0;
<a name="L812" href="source/net/ipv4/igmp.c#L812">812</a>         if (scount == nsrcs)    <b><i>/* all sources excluded */</i></b>
<a name="L813" href="source/net/ipv4/igmp.c#L813">813</a>                 return 0;
<a name="L814" href="source/net/ipv4/igmp.c#L814">814</a>         return 1;
<a name="L815" href="source/net/ipv4/igmp.c#L815">815</a> }
<a name="L816" href="source/net/ipv4/igmp.c#L816">816</a> 
<a name="L817" href="source/net/ipv4/igmp.c#L817">817</a> static int <a href="ident?i=igmp_marksources">igmp_marksources</a>(struct <a href="ident?i=ip_mc_list">ip_mc_list</a> *<a href="ident?i=pmc">pmc</a>, int nsrcs, <a href="ident?i=__be32">__be32</a> *srcs)
<a name="L818" href="source/net/ipv4/igmp.c#L818">818</a> {
<a name="L819" href="source/net/ipv4/igmp.c#L819">819</a>         struct <a href="ident?i=ip_sf_list">ip_sf_list</a> *psf;
<a name="L820" href="source/net/ipv4/igmp.c#L820">820</a>         int <a href="ident?i=i">i</a>, scount;
<a name="L821" href="source/net/ipv4/igmp.c#L821">821</a> 
<a name="L822" href="source/net/ipv4/igmp.c#L822">822</a>         if (<a href="ident?i=pmc">pmc</a>-&gt;sfmode == <a href="ident?i=MCAST_EXCLUDE">MCAST_EXCLUDE</a>)
<a name="L823" href="source/net/ipv4/igmp.c#L823">823</a>                 return <a href="ident?i=igmp_xmarksources">igmp_xmarksources</a>(<a href="ident?i=pmc">pmc</a>, nsrcs, srcs);
<a name="L824" href="source/net/ipv4/igmp.c#L824">824</a> 
<a name="L825" href="source/net/ipv4/igmp.c#L825">825</a>         <b><i>/* mark INCLUDE-mode sources */</i></b>
<a name="L826" href="source/net/ipv4/igmp.c#L826">826</a>         scount = 0;
<a name="L827" href="source/net/ipv4/igmp.c#L827">827</a>         for (psf = <a href="ident?i=pmc">pmc</a>-&gt;sources; psf; psf = psf-&gt;sf_next) {
<a name="L828" href="source/net/ipv4/igmp.c#L828">828</a>                 if (scount == nsrcs)
<a name="L829" href="source/net/ipv4/igmp.c#L829">829</a>                         break;
<a name="L830" href="source/net/ipv4/igmp.c#L830">830</a>                 for (<a href="ident?i=i">i</a> = 0; <a href="ident?i=i">i</a> &lt; nsrcs; <a href="ident?i=i">i</a>++)
<a name="L831" href="source/net/ipv4/igmp.c#L831">831</a>                         if (srcs[<a href="ident?i=i">i</a>] == psf-&gt;sf_inaddr) {
<a name="L832" href="source/net/ipv4/igmp.c#L832">832</a>                                 psf-&gt;sf_gsresp = 1;
<a name="L833" href="source/net/ipv4/igmp.c#L833">833</a>                                 scount++;
<a name="L834" href="source/net/ipv4/igmp.c#L834">834</a>                                 break;
<a name="L835" href="source/net/ipv4/igmp.c#L835">835</a>                         }
<a name="L836" href="source/net/ipv4/igmp.c#L836">836</a>         }
<a name="L837" href="source/net/ipv4/igmp.c#L837">837</a>         if (!scount) {
<a name="L838" href="source/net/ipv4/igmp.c#L838">838</a>                 <a href="ident?i=pmc">pmc</a>-&gt;gsquery = 0;
<a name="L839" href="source/net/ipv4/igmp.c#L839">839</a>                 return 0;
<a name="L840" href="source/net/ipv4/igmp.c#L840">840</a>         }
<a name="L841" href="source/net/ipv4/igmp.c#L841">841</a>         <a href="ident?i=pmc">pmc</a>-&gt;gsquery = 1;
<a name="L842" href="source/net/ipv4/igmp.c#L842">842</a>         return 1;
<a name="L843" href="source/net/ipv4/igmp.c#L843">843</a> }
<a name="L844" href="source/net/ipv4/igmp.c#L844">844</a> 
<a name="L845" href="source/net/ipv4/igmp.c#L845">845</a> <b><i>/* return true if packet was dropped */</i></b>
<a name="L846" href="source/net/ipv4/igmp.c#L846">846</a> static <a href="ident?i=bool">bool</a> <a href="ident?i=igmp_heard_report">igmp_heard_report</a>(struct <a href="ident?i=in_device">in_device</a> *in_dev, <a href="ident?i=__be32">__be32</a> <a href="ident?i=group">group</a>)
<a name="L847" href="source/net/ipv4/igmp.c#L847">847</a> {
<a name="L848" href="source/net/ipv4/igmp.c#L848">848</a>         struct <a href="ident?i=ip_mc_list">ip_mc_list</a> *im;
<a name="L849" href="source/net/ipv4/igmp.c#L849">849</a> 
<a name="L850" href="source/net/ipv4/igmp.c#L850">850</a>         <b><i>/* Timers are only set for non-local groups */</i></b>
<a name="L851" href="source/net/ipv4/igmp.c#L851">851</a> 
<a name="L852" href="source/net/ipv4/igmp.c#L852">852</a>         if (<a href="ident?i=group">group</a> == <a href="ident?i=IGMP_ALL_HOSTS">IGMP_ALL_HOSTS</a>)
<a name="L853" href="source/net/ipv4/igmp.c#L853">853</a>                 return <a href="ident?i=false">false</a>;
<a name="L854" href="source/net/ipv4/igmp.c#L854">854</a> 
<a name="L855" href="source/net/ipv4/igmp.c#L855">855</a>         <a href="ident?i=rcu_read_lock">rcu_read_lock</a>();
<a name="L856" href="source/net/ipv4/igmp.c#L856">856</a>         <a href="ident?i=for_each_pmc_rcu">for_each_pmc_rcu</a>(in_dev, im) {
<a name="L857" href="source/net/ipv4/igmp.c#L857">857</a>                 if (im-&gt;multiaddr == <a href="ident?i=group">group</a>) {
<a name="L858" href="source/net/ipv4/igmp.c#L858">858</a>                         <a href="ident?i=igmp_stop_timer">igmp_stop_timer</a>(im);
<a name="L859" href="source/net/ipv4/igmp.c#L859">859</a>                         break;
<a name="L860" href="source/net/ipv4/igmp.c#L860">860</a>                 }
<a name="L861" href="source/net/ipv4/igmp.c#L861">861</a>         }
<a name="L862" href="source/net/ipv4/igmp.c#L862">862</a>         <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L863" href="source/net/ipv4/igmp.c#L863">863</a>         return <a href="ident?i=false">false</a>;
<a name="L864" href="source/net/ipv4/igmp.c#L864">864</a> }
<a name="L865" href="source/net/ipv4/igmp.c#L865">865</a> 
<a name="L866" href="source/net/ipv4/igmp.c#L866">866</a> <b><i>/* return true if packet was dropped */</i></b>
<a name="L867" href="source/net/ipv4/igmp.c#L867">867</a> static <a href="ident?i=bool">bool</a> <a href="ident?i=igmp_heard_query">igmp_heard_query</a>(struct <a href="ident?i=in_device">in_device</a> *in_dev, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
<a name="L868" href="source/net/ipv4/igmp.c#L868">868</a>         int <a href="ident?i=len">len</a>)
<a name="L869" href="source/net/ipv4/igmp.c#L869">869</a> {
<a name="L870" href="source/net/ipv4/igmp.c#L870">870</a>         struct <a href="ident?i=igmphdr">igmphdr</a>          *ih = <a href="ident?i=igmp_hdr">igmp_hdr</a>(<a href="ident?i=skb">skb</a>);
<a name="L871" href="source/net/ipv4/igmp.c#L871">871</a>         struct <a href="ident?i=igmpv3_query">igmpv3_query</a> *ih3 = <a href="ident?i=igmpv3_query_hdr">igmpv3_query_hdr</a>(<a href="ident?i=skb">skb</a>);
<a name="L872" href="source/net/ipv4/igmp.c#L872">872</a>         struct <a href="ident?i=ip_mc_list">ip_mc_list</a>       *im;
<a name="L873" href="source/net/ipv4/igmp.c#L873">873</a>         <a href="ident?i=__be32">__be32</a>                  <a href="ident?i=group">group</a> = ih-&gt;<a href="ident?i=group">group</a>;
<a name="L874" href="source/net/ipv4/igmp.c#L874">874</a>         int                     <a href="ident?i=max_delay">max_delay</a>;
<a name="L875" href="source/net/ipv4/igmp.c#L875">875</a>         int                     <a href="ident?i=mark">mark</a> = 0;
<a name="L876" href="source/net/ipv4/igmp.c#L876">876</a> 
<a name="L877" href="source/net/ipv4/igmp.c#L877">877</a> 
<a name="L878" href="source/net/ipv4/igmp.c#L878">878</a>         if (<a href="ident?i=len">len</a> == 8) {
<a name="L879" href="source/net/ipv4/igmp.c#L879">879</a>                 if (ih-&gt;<a href="ident?i=code">code</a> == 0) {
<a name="L880" href="source/net/ipv4/igmp.c#L880">880</a>                         <b><i>/* Alas, old v1 router presents here. */</i></b>
<a name="L881" href="source/net/ipv4/igmp.c#L881">881</a> 
<a name="L882" href="source/net/ipv4/igmp.c#L882">882</a>                         <a href="ident?i=max_delay">max_delay</a> = <a href="ident?i=IGMP_QUERY_RESPONSE_INTERVAL">IGMP_QUERY_RESPONSE_INTERVAL</a>;
<a name="L883" href="source/net/ipv4/igmp.c#L883">883</a>                         in_dev-&gt;mr_v1_seen = <a href="ident?i=jiffies">jiffies</a> +
<a name="L884" href="source/net/ipv4/igmp.c#L884">884</a>                                 <a href="ident?i=IGMP_V1_ROUTER_PRESENT_TIMEOUT">IGMP_V1_ROUTER_PRESENT_TIMEOUT</a>;
<a name="L885" href="source/net/ipv4/igmp.c#L885">885</a>                         <a href="ident?i=group">group</a> = 0;
<a name="L886" href="source/net/ipv4/igmp.c#L886">886</a>                 } else {
<a name="L887" href="source/net/ipv4/igmp.c#L887">887</a>                         <b><i>/* v2 router present */</i></b>
<a name="L888" href="source/net/ipv4/igmp.c#L888">888</a>                         <a href="ident?i=max_delay">max_delay</a> = ih-&gt;<a href="ident?i=code">code</a>*(<a href="ident?i=HZ">HZ</a>/<a href="ident?i=IGMP_TIMER_SCALE">IGMP_TIMER_SCALE</a>);
<a name="L889" href="source/net/ipv4/igmp.c#L889">889</a>                         in_dev-&gt;mr_v2_seen = <a href="ident?i=jiffies">jiffies</a> +
<a name="L890" href="source/net/ipv4/igmp.c#L890">890</a>                                 <a href="ident?i=IGMP_V2_ROUTER_PRESENT_TIMEOUT">IGMP_V2_ROUTER_PRESENT_TIMEOUT</a>;
<a name="L891" href="source/net/ipv4/igmp.c#L891">891</a>                 }
<a name="L892" href="source/net/ipv4/igmp.c#L892">892</a>                 <b><i>/* cancel the interface change timer */</i></b>
<a name="L893" href="source/net/ipv4/igmp.c#L893">893</a>                 in_dev-&gt;mr_ifc_count = 0;
<a name="L894" href="source/net/ipv4/igmp.c#L894">894</a>                 if (<a href="ident?i=del_timer">del_timer</a>(&amp;in_dev-&gt;mr_ifc_timer))
<a name="L895" href="source/net/ipv4/igmp.c#L895">895</a>                         <a href="ident?i=__in_dev_put">__in_dev_put</a>(in_dev);
<a name="L896" href="source/net/ipv4/igmp.c#L896">896</a>                 <b><i>/* clear deleted report items */</i></b>
<a name="L897" href="source/net/ipv4/igmp.c#L897">897</a>                 <a href="ident?i=igmpv3_clear_delrec">igmpv3_clear_delrec</a>(in_dev);
<a name="L898" href="source/net/ipv4/igmp.c#L898">898</a>         } else if (<a href="ident?i=len">len</a> &lt; 12) {
<a name="L899" href="source/net/ipv4/igmp.c#L899">899</a>                 return <a href="ident?i=true">true</a>;    <b><i>/* ignore bogus packet; freed by caller */</i></b>
<a name="L900" href="source/net/ipv4/igmp.c#L900">900</a>         } else if (<a href="ident?i=IGMP_V1_SEEN">IGMP_V1_SEEN</a>(in_dev)) {
<a name="L901" href="source/net/ipv4/igmp.c#L901">901</a>                 <b><i>/* This is a v3 query with v1 queriers present */</i></b>
<a name="L902" href="source/net/ipv4/igmp.c#L902">902</a>                 <a href="ident?i=max_delay">max_delay</a> = <a href="ident?i=IGMP_QUERY_RESPONSE_INTERVAL">IGMP_QUERY_RESPONSE_INTERVAL</a>;
<a name="L903" href="source/net/ipv4/igmp.c#L903">903</a>                 <a href="ident?i=group">group</a> = 0;
<a name="L904" href="source/net/ipv4/igmp.c#L904">904</a>         } else if (<a href="ident?i=IGMP_V2_SEEN">IGMP_V2_SEEN</a>(in_dev)) {
<a name="L905" href="source/net/ipv4/igmp.c#L905">905</a>                 <b><i>/* this is a v3 query with v2 queriers present;</i></b>
<a name="L906" href="source/net/ipv4/igmp.c#L906">906</a> <b><i>                 * Interpretation of the max_delay code is problematic here.</i></b>
<a name="L907" href="source/net/ipv4/igmp.c#L907">907</a> <b><i>                 * A real v2 host would use ih_code directly, while v3 has a</i></b>
<a name="L908" href="source/net/ipv4/igmp.c#L908">908</a> <b><i>                 * different encoding. We use the v3 encoding as more likely</i></b>
<a name="L909" href="source/net/ipv4/igmp.c#L909">909</a> <b><i>                 * to be intended in a v3 query.</i></b>
<a name="L910" href="source/net/ipv4/igmp.c#L910">910</a> <b><i>                 */</i></b>
<a name="L911" href="source/net/ipv4/igmp.c#L911">911</a>                 <a href="ident?i=max_delay">max_delay</a> = <a href="ident?i=IGMPV3_MRC">IGMPV3_MRC</a>(ih3-&gt;<a href="ident?i=code">code</a>)*(<a href="ident?i=HZ">HZ</a>/<a href="ident?i=IGMP_TIMER_SCALE">IGMP_TIMER_SCALE</a>);
<a name="L912" href="source/net/ipv4/igmp.c#L912">912</a>                 if (!<a href="ident?i=max_delay">max_delay</a>)
<a name="L913" href="source/net/ipv4/igmp.c#L913">913</a>                         <a href="ident?i=max_delay">max_delay</a> = 1;  <b><i>/* can't mod w/ 0 */</i></b>
<a name="L914" href="source/net/ipv4/igmp.c#L914">914</a>         } else { <b><i>/* v3 */</i></b>
<a name="L915" href="source/net/ipv4/igmp.c#L915">915</a>                 if (!<a href="ident?i=pskb_may_pull">pskb_may_pull</a>(<a href="ident?i=skb">skb</a>, sizeof(struct <a href="ident?i=igmpv3_query">igmpv3_query</a>)))
<a name="L916" href="source/net/ipv4/igmp.c#L916">916</a>                         return <a href="ident?i=true">true</a>;
<a name="L917" href="source/net/ipv4/igmp.c#L917">917</a> 
<a name="L918" href="source/net/ipv4/igmp.c#L918">918</a>                 ih3 = <a href="ident?i=igmpv3_query_hdr">igmpv3_query_hdr</a>(<a href="ident?i=skb">skb</a>);
<a name="L919" href="source/net/ipv4/igmp.c#L919">919</a>                 if (ih3-&gt;nsrcs) {
<a name="L920" href="source/net/ipv4/igmp.c#L920">920</a>                         if (!<a href="ident?i=pskb_may_pull">pskb_may_pull</a>(<a href="ident?i=skb">skb</a>, sizeof(struct <a href="ident?i=igmpv3_query">igmpv3_query</a>)
<a name="L921" href="source/net/ipv4/igmp.c#L921">921</a>                                            + <a href="ident?i=ntohs">ntohs</a>(ih3-&gt;nsrcs)*sizeof(<a href="ident?i=__be32">__be32</a>)))
<a name="L922" href="source/net/ipv4/igmp.c#L922">922</a>                                 return <a href="ident?i=true">true</a>;
<a name="L923" href="source/net/ipv4/igmp.c#L923">923</a>                         ih3 = <a href="ident?i=igmpv3_query_hdr">igmpv3_query_hdr</a>(<a href="ident?i=skb">skb</a>);
<a name="L924" href="source/net/ipv4/igmp.c#L924">924</a>                 }
<a name="L925" href="source/net/ipv4/igmp.c#L925">925</a> 
<a name="L926" href="source/net/ipv4/igmp.c#L926">926</a>                 <a href="ident?i=max_delay">max_delay</a> = <a href="ident?i=IGMPV3_MRC">IGMPV3_MRC</a>(ih3-&gt;<a href="ident?i=code">code</a>)*(<a href="ident?i=HZ">HZ</a>/<a href="ident?i=IGMP_TIMER_SCALE">IGMP_TIMER_SCALE</a>);
<a name="L927" href="source/net/ipv4/igmp.c#L927">927</a>                 if (!<a href="ident?i=max_delay">max_delay</a>)
<a name="L928" href="source/net/ipv4/igmp.c#L928">928</a>                         <a href="ident?i=max_delay">max_delay</a> = 1;  <b><i>/* can't mod w/ 0 */</i></b>
<a name="L929" href="source/net/ipv4/igmp.c#L929">929</a>                 in_dev-&gt;mr_maxdelay = <a href="ident?i=max_delay">max_delay</a>;
<a name="L930" href="source/net/ipv4/igmp.c#L930">930</a>                 if (ih3-&gt;qrv)
<a name="L931" href="source/net/ipv4/igmp.c#L931">931</a>                         in_dev-&gt;mr_qrv = ih3-&gt;qrv;
<a name="L932" href="source/net/ipv4/igmp.c#L932">932</a>                 if (!<a href="ident?i=group">group</a>) { <b><i>/* general query */</i></b>
<a name="L933" href="source/net/ipv4/igmp.c#L933">933</a>                         if (ih3-&gt;nsrcs)
<a name="L934" href="source/net/ipv4/igmp.c#L934">934</a>                                 return <a href="ident?i=true">true</a>;    <b><i>/* no sources allowed */</i></b>
<a name="L935" href="source/net/ipv4/igmp.c#L935">935</a>                         <a href="ident?i=igmp_gq_start_timer">igmp_gq_start_timer</a>(in_dev);
<a name="L936" href="source/net/ipv4/igmp.c#L936">936</a>                         return <a href="ident?i=false">false</a>;
<a name="L937" href="source/net/ipv4/igmp.c#L937">937</a>                 }
<a name="L938" href="source/net/ipv4/igmp.c#L938">938</a>                 <b><i>/* mark sources to include, if group &amp; source-specific */</i></b>
<a name="L939" href="source/net/ipv4/igmp.c#L939">939</a>                 <a href="ident?i=mark">mark</a> = ih3-&gt;nsrcs != 0;
<a name="L940" href="source/net/ipv4/igmp.c#L940">940</a>         }
<a name="L941" href="source/net/ipv4/igmp.c#L941">941</a> 
<a name="L942" href="source/net/ipv4/igmp.c#L942">942</a>         <b><i>/*</i></b>
<a name="L943" href="source/net/ipv4/igmp.c#L943">943</a> <b><i>         * - Start the timers in all of our membership records</i></b>
<a name="L944" href="source/net/ipv4/igmp.c#L944">944</a> <b><i>         *   that the query applies to for the interface on</i></b>
<a name="L945" href="source/net/ipv4/igmp.c#L945">945</a> <b><i>         *   which the query arrived excl. those that belong</i></b>
<a name="L946" href="source/net/ipv4/igmp.c#L946">946</a> <b><i>         *   to a "local" group (224.0.0.X)</i></b>
<a name="L947" href="source/net/ipv4/igmp.c#L947">947</a> <b><i>         * - For timers already running check if they need to</i></b>
<a name="L948" href="source/net/ipv4/igmp.c#L948">948</a> <b><i>         *   be reset.</i></b>
<a name="L949" href="source/net/ipv4/igmp.c#L949">949</a> <b><i>         * - Use the igmp-&gt;igmp_code field as the maximum</i></b>
<a name="L950" href="source/net/ipv4/igmp.c#L950">950</a> <b><i>         *   delay possible</i></b>
<a name="L951" href="source/net/ipv4/igmp.c#L951">951</a> <b><i>         */</i></b>
<a name="L952" href="source/net/ipv4/igmp.c#L952">952</a>         <a href="ident?i=rcu_read_lock">rcu_read_lock</a>();
<a name="L953" href="source/net/ipv4/igmp.c#L953">953</a>         <a href="ident?i=for_each_pmc_rcu">for_each_pmc_rcu</a>(in_dev, im) {
<a name="L954" href="source/net/ipv4/igmp.c#L954">954</a>                 int changed;
<a name="L955" href="source/net/ipv4/igmp.c#L955">955</a> 
<a name="L956" href="source/net/ipv4/igmp.c#L956">956</a>                 if (<a href="ident?i=group">group</a> &amp;&amp; <a href="ident?i=group">group</a> != im-&gt;multiaddr)
<a name="L957" href="source/net/ipv4/igmp.c#L957">957</a>                         continue;
<a name="L958" href="source/net/ipv4/igmp.c#L958">958</a>                 if (im-&gt;multiaddr == <a href="ident?i=IGMP_ALL_HOSTS">IGMP_ALL_HOSTS</a>)
<a name="L959" href="source/net/ipv4/igmp.c#L959">959</a>                         continue;
<a name="L960" href="source/net/ipv4/igmp.c#L960">960</a>                 <a href="ident?i=spin_lock_bh">spin_lock_bh</a>(&amp;im-&gt;<a href="ident?i=lock">lock</a>);
<a name="L961" href="source/net/ipv4/igmp.c#L961">961</a>                 if (im-&gt;tm_running)
<a name="L962" href="source/net/ipv4/igmp.c#L962">962</a>                         im-&gt;gsquery = im-&gt;gsquery &amp;&amp; <a href="ident?i=mark">mark</a>;
<a name="L963" href="source/net/ipv4/igmp.c#L963">963</a>                 else
<a name="L964" href="source/net/ipv4/igmp.c#L964">964</a>                         im-&gt;gsquery = <a href="ident?i=mark">mark</a>;
<a name="L965" href="source/net/ipv4/igmp.c#L965">965</a>                 changed = !im-&gt;gsquery ||
<a name="L966" href="source/net/ipv4/igmp.c#L966">966</a>                         <a href="ident?i=igmp_marksources">igmp_marksources</a>(im, <a href="ident?i=ntohs">ntohs</a>(ih3-&gt;nsrcs), ih3-&gt;srcs);
<a name="L967" href="source/net/ipv4/igmp.c#L967">967</a>                 <a href="ident?i=spin_unlock_bh">spin_unlock_bh</a>(&amp;im-&gt;<a href="ident?i=lock">lock</a>);
<a name="L968" href="source/net/ipv4/igmp.c#L968">968</a>                 if (changed)
<a name="L969" href="source/net/ipv4/igmp.c#L969">969</a>                         <a href="ident?i=igmp_mod_timer">igmp_mod_timer</a>(im, <a href="ident?i=max_delay">max_delay</a>);
<a name="L970" href="source/net/ipv4/igmp.c#L970">970</a>         }
<a name="L971" href="source/net/ipv4/igmp.c#L971">971</a>         <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L972" href="source/net/ipv4/igmp.c#L972">972</a>         return <a href="ident?i=false">false</a>;
<a name="L973" href="source/net/ipv4/igmp.c#L973">973</a> }
<a name="L974" href="source/net/ipv4/igmp.c#L974">974</a> 
<a name="L975" href="source/net/ipv4/igmp.c#L975">975</a> <b><i>/* called in rcu_read_lock() section */</i></b>
<a name="L976" href="source/net/ipv4/igmp.c#L976">976</a> int <a href="ident?i=igmp_rcv">igmp_rcv</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L977" href="source/net/ipv4/igmp.c#L977">977</a> {
<a name="L978" href="source/net/ipv4/igmp.c#L978">978</a>         <b><i>/* This basically follows the spec line by line -- see RFC1112 */</i></b>
<a name="L979" href="source/net/ipv4/igmp.c#L979">979</a>         struct <a href="ident?i=igmphdr">igmphdr</a> *ih;
<a name="L980" href="source/net/ipv4/igmp.c#L980">980</a>         struct <a href="ident?i=in_device">in_device</a> *in_dev = <a href="ident?i=__in_dev_get_rcu">__in_dev_get_rcu</a>(<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=dev">dev</a>);
<a name="L981" href="source/net/ipv4/igmp.c#L981">981</a>         int <a href="ident?i=len">len</a> = <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a>;
<a name="L982" href="source/net/ipv4/igmp.c#L982">982</a>         <a href="ident?i=bool">bool</a> dropped = <a href="ident?i=true">true</a>;
<a name="L983" href="source/net/ipv4/igmp.c#L983">983</a> 
<a name="L984" href="source/net/ipv4/igmp.c#L984">984</a>         if (!in_dev)
<a name="L985" href="source/net/ipv4/igmp.c#L985">985</a>                 goto <a href="ident?i=drop">drop</a>;
<a name="L986" href="source/net/ipv4/igmp.c#L986">986</a> 
<a name="L987" href="source/net/ipv4/igmp.c#L987">987</a>         if (!<a href="ident?i=pskb_may_pull">pskb_may_pull</a>(<a href="ident?i=skb">skb</a>, sizeof(struct <a href="ident?i=igmphdr">igmphdr</a>)))
<a name="L988" href="source/net/ipv4/igmp.c#L988">988</a>                 goto <a href="ident?i=drop">drop</a>;
<a name="L989" href="source/net/ipv4/igmp.c#L989">989</a> 
<a name="L990" href="source/net/ipv4/igmp.c#L990">990</a>         if (<a href="ident?i=skb_checksum_simple_validate">skb_checksum_simple_validate</a>(<a href="ident?i=skb">skb</a>))
<a name="L991" href="source/net/ipv4/igmp.c#L991">991</a>                 goto <a href="ident?i=drop">drop</a>;
<a name="L992" href="source/net/ipv4/igmp.c#L992">992</a> 
<a name="L993" href="source/net/ipv4/igmp.c#L993">993</a>         ih = <a href="ident?i=igmp_hdr">igmp_hdr</a>(<a href="ident?i=skb">skb</a>);
<a name="L994" href="source/net/ipv4/igmp.c#L994">994</a>         switch (ih-&gt;<a href="ident?i=type">type</a>) {
<a name="L995" href="source/net/ipv4/igmp.c#L995">995</a>         case <a href="ident?i=IGMP_HOST_MEMBERSHIP_QUERY">IGMP_HOST_MEMBERSHIP_QUERY</a>:
<a name="L996" href="source/net/ipv4/igmp.c#L996">996</a>                 dropped = <a href="ident?i=igmp_heard_query">igmp_heard_query</a>(in_dev, <a href="ident?i=skb">skb</a>, <a href="ident?i=len">len</a>);
<a name="L997" href="source/net/ipv4/igmp.c#L997">997</a>                 break;
<a name="L998" href="source/net/ipv4/igmp.c#L998">998</a>         case <a href="ident?i=IGMP_HOST_MEMBERSHIP_REPORT">IGMP_HOST_MEMBERSHIP_REPORT</a>:
<a name="L999" href="source/net/ipv4/igmp.c#L999">999</a>         case <a href="ident?i=IGMPV2_HOST_MEMBERSHIP_REPORT">IGMPV2_HOST_MEMBERSHIP_REPORT</a>:
<a name="L1000" href="source/net/ipv4/igmp.c#L1000">1000</a>                 <b><i>/* Is it our report looped back? */</i></b>
<a name="L1001" href="source/net/ipv4/igmp.c#L1001">1001</a>                 if (<a href="ident?i=rt_is_output_route">rt_is_output_route</a>(<a href="ident?i=skb_rtable">skb_rtable</a>(<a href="ident?i=skb">skb</a>)))
<a name="L1002" href="source/net/ipv4/igmp.c#L1002">1002</a>                         break;
<a name="L1003" href="source/net/ipv4/igmp.c#L1003">1003</a>                 <b><i>/* don't rely on MC router hearing unicast reports */</i></b>
<a name="L1004" href="source/net/ipv4/igmp.c#L1004">1004</a>                 if (<a href="ident?i=skb">skb</a>-&gt;pkt_type == <a href="ident?i=PACKET_MULTICAST">PACKET_MULTICAST</a> ||
<a name="L1005" href="source/net/ipv4/igmp.c#L1005">1005</a>                     <a href="ident?i=skb">skb</a>-&gt;pkt_type == <a href="ident?i=PACKET_BROADCAST">PACKET_BROADCAST</a>)
<a name="L1006" href="source/net/ipv4/igmp.c#L1006">1006</a>                         dropped = <a href="ident?i=igmp_heard_report">igmp_heard_report</a>(in_dev, ih-&gt;<a href="ident?i=group">group</a>);
<a name="L1007" href="source/net/ipv4/igmp.c#L1007">1007</a>                 break;
<a name="L1008" href="source/net/ipv4/igmp.c#L1008">1008</a>         case <a href="ident?i=IGMP_PIM">IGMP_PIM</a>:
<a name="L1009" href="source/net/ipv4/igmp.c#L1009">1009</a> #ifdef CONFIG_IP_PIMSM_V1
<a name="L1010" href="source/net/ipv4/igmp.c#L1010">1010</a>                 return <a href="ident?i=pim_rcv_v1">pim_rcv_v1</a>(<a href="ident?i=skb">skb</a>);
<a name="L1011" href="source/net/ipv4/igmp.c#L1011">1011</a> #endif
<a name="L1012" href="source/net/ipv4/igmp.c#L1012">1012</a>         case <a href="ident?i=IGMPV3_HOST_MEMBERSHIP_REPORT">IGMPV3_HOST_MEMBERSHIP_REPORT</a>:
<a name="L1013" href="source/net/ipv4/igmp.c#L1013">1013</a>         case <a href="ident?i=IGMP_DVMRP">IGMP_DVMRP</a>:
<a name="L1014" href="source/net/ipv4/igmp.c#L1014">1014</a>         case <a href="ident?i=IGMP_TRACE">IGMP_TRACE</a>:
<a name="L1015" href="source/net/ipv4/igmp.c#L1015">1015</a>         case <a href="ident?i=IGMP_HOST_LEAVE_MESSAGE">IGMP_HOST_LEAVE_MESSAGE</a>:
<a name="L1016" href="source/net/ipv4/igmp.c#L1016">1016</a>         case <a href="ident?i=IGMP_MTRACE">IGMP_MTRACE</a>:
<a name="L1017" href="source/net/ipv4/igmp.c#L1017">1017</a>         case <a href="ident?i=IGMP_MTRACE_RESP">IGMP_MTRACE_RESP</a>:
<a name="L1018" href="source/net/ipv4/igmp.c#L1018">1018</a>                 break;
<a name="L1019" href="source/net/ipv4/igmp.c#L1019">1019</a>         default:
<a name="L1020" href="source/net/ipv4/igmp.c#L1020">1020</a>                 break;
<a name="L1021" href="source/net/ipv4/igmp.c#L1021">1021</a>         }
<a name="L1022" href="source/net/ipv4/igmp.c#L1022">1022</a> 
<a name="L1023" href="source/net/ipv4/igmp.c#L1023">1023</a> <a href="ident?i=drop">drop</a>:
<a name="L1024" href="source/net/ipv4/igmp.c#L1024">1024</a>         if (dropped)
<a name="L1025" href="source/net/ipv4/igmp.c#L1025">1025</a>                 <a href="ident?i=kfree_skb">kfree_skb</a>(<a href="ident?i=skb">skb</a>);
<a name="L1026" href="source/net/ipv4/igmp.c#L1026">1026</a>         else
<a name="L1027" href="source/net/ipv4/igmp.c#L1027">1027</a>                 <a href="ident?i=consume_skb">consume_skb</a>(<a href="ident?i=skb">skb</a>);
<a name="L1028" href="source/net/ipv4/igmp.c#L1028">1028</a>         return 0;
<a name="L1029" href="source/net/ipv4/igmp.c#L1029">1029</a> }
<a name="L1030" href="source/net/ipv4/igmp.c#L1030">1030</a> 
<a name="L1031" href="source/net/ipv4/igmp.c#L1031">1031</a> #endif
<a name="L1032" href="source/net/ipv4/igmp.c#L1032">1032</a> 
<a name="L1033" href="source/net/ipv4/igmp.c#L1033">1033</a> 
<a name="L1034" href="source/net/ipv4/igmp.c#L1034">1034</a> <b><i>/*</i></b>
<a name="L1035" href="source/net/ipv4/igmp.c#L1035">1035</a> <b><i> *      Add a filter to a device</i></b>
<a name="L1036" href="source/net/ipv4/igmp.c#L1036">1036</a> <b><i> */</i></b>
<a name="L1037" href="source/net/ipv4/igmp.c#L1037">1037</a> 
<a name="L1038" href="source/net/ipv4/igmp.c#L1038">1038</a> static void <a href="ident?i=ip_mc_filter_add">ip_mc_filter_add</a>(struct <a href="ident?i=in_device">in_device</a> *in_dev, <a href="ident?i=__be32">__be32</a> <a href="ident?i=addr">addr</a>)
<a name="L1039" href="source/net/ipv4/igmp.c#L1039">1039</a> {
<a name="L1040" href="source/net/ipv4/igmp.c#L1040">1040</a>         char <a href="ident?i=buf">buf</a>[<a href="ident?i=MAX_ADDR_LEN">MAX_ADDR_LEN</a>];
<a name="L1041" href="source/net/ipv4/igmp.c#L1041">1041</a>         struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a> = in_dev-&gt;<a href="ident?i=dev">dev</a>;
<a name="L1042" href="source/net/ipv4/igmp.c#L1042">1042</a> 
<a name="L1043" href="source/net/ipv4/igmp.c#L1043">1043</a>         <b><i>/* Checking for IFF_MULTICAST here is WRONG-WRONG-WRONG.</i></b>
<a name="L1044" href="source/net/ipv4/igmp.c#L1044">1044</a> <b><i>           We will get multicast token leakage, when IFF_MULTICAST</i></b>
<a name="L1045" href="source/net/ipv4/igmp.c#L1045">1045</a> <b><i>           is changed. This check should be done in ndo_set_rx_mode</i></b>
<a name="L1046" href="source/net/ipv4/igmp.c#L1046">1046</a> <b><i>           routine. Something sort of:</i></b>
<a name="L1047" href="source/net/ipv4/igmp.c#L1047">1047</a> <b><i>           if (dev-&gt;mc_list &amp;&amp; dev-&gt;flags&amp;IFF_MULTICAST) { do it; }</i></b>
<a name="L1048" href="source/net/ipv4/igmp.c#L1048">1048</a> <b><i>           --ANK</i></b>
<a name="L1049" href="source/net/ipv4/igmp.c#L1049">1049</a> <b><i>           */</i></b>
<a name="L1050" href="source/net/ipv4/igmp.c#L1050">1050</a>         if (<a href="ident?i=arp_mc_map">arp_mc_map</a>(<a href="ident?i=addr">addr</a>, <a href="ident?i=buf">buf</a>, <a href="ident?i=dev">dev</a>, 0) == 0)
<a name="L1051" href="source/net/ipv4/igmp.c#L1051">1051</a>                 <a href="ident?i=dev_mc_add">dev_mc_add</a>(<a href="ident?i=dev">dev</a>, <a href="ident?i=buf">buf</a>);
<a name="L1052" href="source/net/ipv4/igmp.c#L1052">1052</a> }
<a name="L1053" href="source/net/ipv4/igmp.c#L1053">1053</a> 
<a name="L1054" href="source/net/ipv4/igmp.c#L1054">1054</a> <b><i>/*</i></b>
<a name="L1055" href="source/net/ipv4/igmp.c#L1055">1055</a> <b><i> *      Remove a filter from a device</i></b>
<a name="L1056" href="source/net/ipv4/igmp.c#L1056">1056</a> <b><i> */</i></b>
<a name="L1057" href="source/net/ipv4/igmp.c#L1057">1057</a> 
<a name="L1058" href="source/net/ipv4/igmp.c#L1058">1058</a> static void <a href="ident?i=ip_mc_filter_del">ip_mc_filter_del</a>(struct <a href="ident?i=in_device">in_device</a> *in_dev, <a href="ident?i=__be32">__be32</a> <a href="ident?i=addr">addr</a>)
<a name="L1059" href="source/net/ipv4/igmp.c#L1059">1059</a> {
<a name="L1060" href="source/net/ipv4/igmp.c#L1060">1060</a>         char <a href="ident?i=buf">buf</a>[<a href="ident?i=MAX_ADDR_LEN">MAX_ADDR_LEN</a>];
<a name="L1061" href="source/net/ipv4/igmp.c#L1061">1061</a>         struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a> = in_dev-&gt;<a href="ident?i=dev">dev</a>;
<a name="L1062" href="source/net/ipv4/igmp.c#L1062">1062</a> 
<a name="L1063" href="source/net/ipv4/igmp.c#L1063">1063</a>         if (<a href="ident?i=arp_mc_map">arp_mc_map</a>(<a href="ident?i=addr">addr</a>, <a href="ident?i=buf">buf</a>, <a href="ident?i=dev">dev</a>, 0) == 0)
<a name="L1064" href="source/net/ipv4/igmp.c#L1064">1064</a>                 <a href="ident?i=dev_mc_del">dev_mc_del</a>(<a href="ident?i=dev">dev</a>, <a href="ident?i=buf">buf</a>);
<a name="L1065" href="source/net/ipv4/igmp.c#L1065">1065</a> }
<a name="L1066" href="source/net/ipv4/igmp.c#L1066">1066</a> 
<a name="L1067" href="source/net/ipv4/igmp.c#L1067">1067</a> #ifdef CONFIG_IP_MULTICAST
<a name="L1068" href="source/net/ipv4/igmp.c#L1068">1068</a> <b><i>/*</i></b>
<a name="L1069" href="source/net/ipv4/igmp.c#L1069">1069</a> <b><i> * deleted ip_mc_list manipulation</i></b>
<a name="L1070" href="source/net/ipv4/igmp.c#L1070">1070</a> <b><i> */</i></b>
<a name="L1071" href="source/net/ipv4/igmp.c#L1071">1071</a> static void <a href="ident?i=igmpv3_add_delrec">igmpv3_add_delrec</a>(struct <a href="ident?i=in_device">in_device</a> *in_dev, struct <a href="ident?i=ip_mc_list">ip_mc_list</a> *im)
<a name="L1072" href="source/net/ipv4/igmp.c#L1072">1072</a> {
<a name="L1073" href="source/net/ipv4/igmp.c#L1073">1073</a>         struct <a href="ident?i=ip_mc_list">ip_mc_list</a> *<a href="ident?i=pmc">pmc</a>;
<a name="L1074" href="source/net/ipv4/igmp.c#L1074">1074</a> 
<a name="L1075" href="source/net/ipv4/igmp.c#L1075">1075</a>         <b><i>/* this is an "ip_mc_list" for convenience; only the fields below</i></b>
<a name="L1076" href="source/net/ipv4/igmp.c#L1076">1076</a> <b><i>         * are actually used. In particular, the refcnt and users are not</i></b>
<a name="L1077" href="source/net/ipv4/igmp.c#L1077">1077</a> <b><i>         * used for management of the delete list. Using the same structure</i></b>
<a name="L1078" href="source/net/ipv4/igmp.c#L1078">1078</a> <b><i>         * for deleted items allows change reports to use common code with</i></b>
<a name="L1079" href="source/net/ipv4/igmp.c#L1079">1079</a> <b><i>         * non-deleted or query-response MCA's.</i></b>
<a name="L1080" href="source/net/ipv4/igmp.c#L1080">1080</a> <b><i>         */</i></b>
<a name="L1081" href="source/net/ipv4/igmp.c#L1081">1081</a>         <a href="ident?i=pmc">pmc</a> = <a href="ident?i=kzalloc">kzalloc</a>(sizeof(*<a href="ident?i=pmc">pmc</a>), <a href="ident?i=GFP_KERNEL">GFP_KERNEL</a>);
<a name="L1082" href="source/net/ipv4/igmp.c#L1082">1082</a>         if (!<a href="ident?i=pmc">pmc</a>)
<a name="L1083" href="source/net/ipv4/igmp.c#L1083">1083</a>                 return;
<a name="L1084" href="source/net/ipv4/igmp.c#L1084">1084</a>         <a href="ident?i=spin_lock_bh">spin_lock_bh</a>(&amp;im-&gt;<a href="ident?i=lock">lock</a>);
<a name="L1085" href="source/net/ipv4/igmp.c#L1085">1085</a>         <a href="ident?i=pmc">pmc</a>-&gt;<a href="ident?i=interface">interface</a> = im-&gt;<a href="ident?i=interface">interface</a>;
<a name="L1086" href="source/net/ipv4/igmp.c#L1086">1086</a>         <a href="ident?i=in_dev_hold">in_dev_hold</a>(in_dev);
<a name="L1087" href="source/net/ipv4/igmp.c#L1087">1087</a>         <a href="ident?i=pmc">pmc</a>-&gt;multiaddr = im-&gt;multiaddr;
<a name="L1088" href="source/net/ipv4/igmp.c#L1088">1088</a>         <a href="ident?i=pmc">pmc</a>-&gt;crcount = in_dev-&gt;mr_qrv ?: <a href="ident?i=sysctl_igmp_qrv">sysctl_igmp_qrv</a>;
<a name="L1089" href="source/net/ipv4/igmp.c#L1089">1089</a>         <a href="ident?i=pmc">pmc</a>-&gt;sfmode = im-&gt;sfmode;
<a name="L1090" href="source/net/ipv4/igmp.c#L1090">1090</a>         if (<a href="ident?i=pmc">pmc</a>-&gt;sfmode == <a href="ident?i=MCAST_INCLUDE">MCAST_INCLUDE</a>) {
<a name="L1091" href="source/net/ipv4/igmp.c#L1091">1091</a>                 struct <a href="ident?i=ip_sf_list">ip_sf_list</a> *psf;
<a name="L1092" href="source/net/ipv4/igmp.c#L1092">1092</a> 
<a name="L1093" href="source/net/ipv4/igmp.c#L1093">1093</a>                 <a href="ident?i=pmc">pmc</a>-&gt;tomb = im-&gt;tomb;
<a name="L1094" href="source/net/ipv4/igmp.c#L1094">1094</a>                 <a href="ident?i=pmc">pmc</a>-&gt;sources = im-&gt;sources;
<a name="L1095" href="source/net/ipv4/igmp.c#L1095">1095</a>                 im-&gt;tomb = im-&gt;sources = <a href="ident?i=NULL">NULL</a>;
<a name="L1096" href="source/net/ipv4/igmp.c#L1096">1096</a>                 for (psf = <a href="ident?i=pmc">pmc</a>-&gt;sources; psf; psf = psf-&gt;sf_next)
<a name="L1097" href="source/net/ipv4/igmp.c#L1097">1097</a>                         psf-&gt;sf_crcount = <a href="ident?i=pmc">pmc</a>-&gt;crcount;
<a name="L1098" href="source/net/ipv4/igmp.c#L1098">1098</a>         }
<a name="L1099" href="source/net/ipv4/igmp.c#L1099">1099</a>         <a href="ident?i=spin_unlock_bh">spin_unlock_bh</a>(&amp;im-&gt;<a href="ident?i=lock">lock</a>);
<a name="L1100" href="source/net/ipv4/igmp.c#L1100">1100</a> 
<a name="L1101" href="source/net/ipv4/igmp.c#L1101">1101</a>         <a href="ident?i=spin_lock_bh">spin_lock_bh</a>(&amp;in_dev-&gt;mc_tomb_lock);
<a name="L1102" href="source/net/ipv4/igmp.c#L1102">1102</a>         <a href="ident?i=pmc">pmc</a>-&gt;<a href="ident?i=next">next</a> = in_dev-&gt;mc_tomb;
<a name="L1103" href="source/net/ipv4/igmp.c#L1103">1103</a>         in_dev-&gt;mc_tomb = <a href="ident?i=pmc">pmc</a>;
<a name="L1104" href="source/net/ipv4/igmp.c#L1104">1104</a>         <a href="ident?i=spin_unlock_bh">spin_unlock_bh</a>(&amp;in_dev-&gt;mc_tomb_lock);
<a name="L1105" href="source/net/ipv4/igmp.c#L1105">1105</a> }
<a name="L1106" href="source/net/ipv4/igmp.c#L1106">1106</a> 
<a name="L1107" href="source/net/ipv4/igmp.c#L1107">1107</a> static void <a href="ident?i=igmpv3_del_delrec">igmpv3_del_delrec</a>(struct <a href="ident?i=in_device">in_device</a> *in_dev, <a href="ident?i=__be32">__be32</a> multiaddr)
<a name="L1108" href="source/net/ipv4/igmp.c#L1108">1108</a> {
<a name="L1109" href="source/net/ipv4/igmp.c#L1109">1109</a>         struct <a href="ident?i=ip_mc_list">ip_mc_list</a> *<a href="ident?i=pmc">pmc</a>, *pmc_prev;
<a name="L1110" href="source/net/ipv4/igmp.c#L1110">1110</a>         struct <a href="ident?i=ip_sf_list">ip_sf_list</a> *psf, *psf_next;
<a name="L1111" href="source/net/ipv4/igmp.c#L1111">1111</a> 
<a name="L1112" href="source/net/ipv4/igmp.c#L1112">1112</a>         <a href="ident?i=spin_lock_bh">spin_lock_bh</a>(&amp;in_dev-&gt;mc_tomb_lock);
<a name="L1113" href="source/net/ipv4/igmp.c#L1113">1113</a>         pmc_prev = <a href="ident?i=NULL">NULL</a>;
<a name="L1114" href="source/net/ipv4/igmp.c#L1114">1114</a>         for (<a href="ident?i=pmc">pmc</a> = in_dev-&gt;mc_tomb; <a href="ident?i=pmc">pmc</a>; <a href="ident?i=pmc">pmc</a> = <a href="ident?i=pmc">pmc</a>-&gt;<a href="ident?i=next">next</a>) {
<a name="L1115" href="source/net/ipv4/igmp.c#L1115">1115</a>                 if (<a href="ident?i=pmc">pmc</a>-&gt;multiaddr == multiaddr)
<a name="L1116" href="source/net/ipv4/igmp.c#L1116">1116</a>                         break;
<a name="L1117" href="source/net/ipv4/igmp.c#L1117">1117</a>                 pmc_prev = <a href="ident?i=pmc">pmc</a>;
<a name="L1118" href="source/net/ipv4/igmp.c#L1118">1118</a>         }
<a name="L1119" href="source/net/ipv4/igmp.c#L1119">1119</a>         if (<a href="ident?i=pmc">pmc</a>) {
<a name="L1120" href="source/net/ipv4/igmp.c#L1120">1120</a>                 if (pmc_prev)
<a name="L1121" href="source/net/ipv4/igmp.c#L1121">1121</a>                         pmc_prev-&gt;<a href="ident?i=next">next</a> = <a href="ident?i=pmc">pmc</a>-&gt;<a href="ident?i=next">next</a>;
<a name="L1122" href="source/net/ipv4/igmp.c#L1122">1122</a>                 else
<a name="L1123" href="source/net/ipv4/igmp.c#L1123">1123</a>                         in_dev-&gt;mc_tomb = <a href="ident?i=pmc">pmc</a>-&gt;<a href="ident?i=next">next</a>;
<a name="L1124" href="source/net/ipv4/igmp.c#L1124">1124</a>         }
<a name="L1125" href="source/net/ipv4/igmp.c#L1125">1125</a>         <a href="ident?i=spin_unlock_bh">spin_unlock_bh</a>(&amp;in_dev-&gt;mc_tomb_lock);
<a name="L1126" href="source/net/ipv4/igmp.c#L1126">1126</a>         if (<a href="ident?i=pmc">pmc</a>) {
<a name="L1127" href="source/net/ipv4/igmp.c#L1127">1127</a>                 for (psf = <a href="ident?i=pmc">pmc</a>-&gt;tomb; psf; psf = psf_next) {
<a name="L1128" href="source/net/ipv4/igmp.c#L1128">1128</a>                         psf_next = psf-&gt;sf_next;
<a name="L1129" href="source/net/ipv4/igmp.c#L1129">1129</a>                         <a href="ident?i=kfree">kfree</a>(psf);
<a name="L1130" href="source/net/ipv4/igmp.c#L1130">1130</a>                 }
<a name="L1131" href="source/net/ipv4/igmp.c#L1131">1131</a>                 <a href="ident?i=in_dev_put">in_dev_put</a>(<a href="ident?i=pmc">pmc</a>-&gt;<a href="ident?i=interface">interface</a>);
<a name="L1132" href="source/net/ipv4/igmp.c#L1132">1132</a>                 <a href="ident?i=kfree">kfree</a>(<a href="ident?i=pmc">pmc</a>);
<a name="L1133" href="source/net/ipv4/igmp.c#L1133">1133</a>         }
<a name="L1134" href="source/net/ipv4/igmp.c#L1134">1134</a> }
<a name="L1135" href="source/net/ipv4/igmp.c#L1135">1135</a> 
<a name="L1136" href="source/net/ipv4/igmp.c#L1136">1136</a> static void <a href="ident?i=igmpv3_clear_delrec">igmpv3_clear_delrec</a>(struct <a href="ident?i=in_device">in_device</a> *in_dev)
<a name="L1137" href="source/net/ipv4/igmp.c#L1137">1137</a> {
<a name="L1138" href="source/net/ipv4/igmp.c#L1138">1138</a>         struct <a href="ident?i=ip_mc_list">ip_mc_list</a> *<a href="ident?i=pmc">pmc</a>, *nextpmc;
<a name="L1139" href="source/net/ipv4/igmp.c#L1139">1139</a> 
<a name="L1140" href="source/net/ipv4/igmp.c#L1140">1140</a>         <a href="ident?i=spin_lock_bh">spin_lock_bh</a>(&amp;in_dev-&gt;mc_tomb_lock);
<a name="L1141" href="source/net/ipv4/igmp.c#L1141">1141</a>         <a href="ident?i=pmc">pmc</a> = in_dev-&gt;mc_tomb;
<a name="L1142" href="source/net/ipv4/igmp.c#L1142">1142</a>         in_dev-&gt;mc_tomb = <a href="ident?i=NULL">NULL</a>;
<a name="L1143" href="source/net/ipv4/igmp.c#L1143">1143</a>         <a href="ident?i=spin_unlock_bh">spin_unlock_bh</a>(&amp;in_dev-&gt;mc_tomb_lock);
<a name="L1144" href="source/net/ipv4/igmp.c#L1144">1144</a> 
<a name="L1145" href="source/net/ipv4/igmp.c#L1145">1145</a>         for (; <a href="ident?i=pmc">pmc</a>; <a href="ident?i=pmc">pmc</a> = nextpmc) {
<a name="L1146" href="source/net/ipv4/igmp.c#L1146">1146</a>                 nextpmc = <a href="ident?i=pmc">pmc</a>-&gt;<a href="ident?i=next">next</a>;
<a name="L1147" href="source/net/ipv4/igmp.c#L1147">1147</a>                 <a href="ident?i=ip_mc_clear_src">ip_mc_clear_src</a>(<a href="ident?i=pmc">pmc</a>);
<a name="L1148" href="source/net/ipv4/igmp.c#L1148">1148</a>                 <a href="ident?i=in_dev_put">in_dev_put</a>(<a href="ident?i=pmc">pmc</a>-&gt;<a href="ident?i=interface">interface</a>);
<a name="L1149" href="source/net/ipv4/igmp.c#L1149">1149</a>                 <a href="ident?i=kfree">kfree</a>(<a href="ident?i=pmc">pmc</a>);
<a name="L1150" href="source/net/ipv4/igmp.c#L1150">1150</a>         }
<a name="L1151" href="source/net/ipv4/igmp.c#L1151">1151</a>         <b><i>/* clear dead sources, too */</i></b>
<a name="L1152" href="source/net/ipv4/igmp.c#L1152">1152</a>         <a href="ident?i=rcu_read_lock">rcu_read_lock</a>();
<a name="L1153" href="source/net/ipv4/igmp.c#L1153">1153</a>         <a href="ident?i=for_each_pmc_rcu">for_each_pmc_rcu</a>(in_dev, <a href="ident?i=pmc">pmc</a>) {
<a name="L1154" href="source/net/ipv4/igmp.c#L1154">1154</a>                 struct <a href="ident?i=ip_sf_list">ip_sf_list</a> *psf, *psf_next;
<a name="L1155" href="source/net/ipv4/igmp.c#L1155">1155</a> 
<a name="L1156" href="source/net/ipv4/igmp.c#L1156">1156</a>                 <a href="ident?i=spin_lock_bh">spin_lock_bh</a>(&amp;<a href="ident?i=pmc">pmc</a>-&gt;<a href="ident?i=lock">lock</a>);
<a name="L1157" href="source/net/ipv4/igmp.c#L1157">1157</a>                 psf = <a href="ident?i=pmc">pmc</a>-&gt;tomb;
<a name="L1158" href="source/net/ipv4/igmp.c#L1158">1158</a>                 <a href="ident?i=pmc">pmc</a>-&gt;tomb = <a href="ident?i=NULL">NULL</a>;
<a name="L1159" href="source/net/ipv4/igmp.c#L1159">1159</a>                 <a href="ident?i=spin_unlock_bh">spin_unlock_bh</a>(&amp;<a href="ident?i=pmc">pmc</a>-&gt;<a href="ident?i=lock">lock</a>);
<a name="L1160" href="source/net/ipv4/igmp.c#L1160">1160</a>                 for (; psf; psf = psf_next) {
<a name="L1161" href="source/net/ipv4/igmp.c#L1161">1161</a>                         psf_next = psf-&gt;sf_next;
<a name="L1162" href="source/net/ipv4/igmp.c#L1162">1162</a>                         <a href="ident?i=kfree">kfree</a>(psf);
<a name="L1163" href="source/net/ipv4/igmp.c#L1163">1163</a>                 }
<a name="L1164" href="source/net/ipv4/igmp.c#L1164">1164</a>         }
<a name="L1165" href="source/net/ipv4/igmp.c#L1165">1165</a>         <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L1166" href="source/net/ipv4/igmp.c#L1166">1166</a> }
<a name="L1167" href="source/net/ipv4/igmp.c#L1167">1167</a> #endif
<a name="L1168" href="source/net/ipv4/igmp.c#L1168">1168</a> 
<a name="L1169" href="source/net/ipv4/igmp.c#L1169">1169</a> static void <a href="ident?i=igmp_group_dropped">igmp_group_dropped</a>(struct <a href="ident?i=ip_mc_list">ip_mc_list</a> *im)
<a name="L1170" href="source/net/ipv4/igmp.c#L1170">1170</a> {
<a name="L1171" href="source/net/ipv4/igmp.c#L1171">1171</a>         struct <a href="ident?i=in_device">in_device</a> *in_dev = im-&gt;<a href="ident?i=interface">interface</a>;
<a name="L1172" href="source/net/ipv4/igmp.c#L1172">1172</a> #ifdef CONFIG_IP_MULTICAST
<a name="L1173" href="source/net/ipv4/igmp.c#L1173">1173</a>         int reporter;
<a name="L1174" href="source/net/ipv4/igmp.c#L1174">1174</a> #endif
<a name="L1175" href="source/net/ipv4/igmp.c#L1175">1175</a> 
<a name="L1176" href="source/net/ipv4/igmp.c#L1176">1176</a>         if (im-&gt;<a href="ident?i=loaded">loaded</a>) {
<a name="L1177" href="source/net/ipv4/igmp.c#L1177">1177</a>                 im-&gt;<a href="ident?i=loaded">loaded</a> = 0;
<a name="L1178" href="source/net/ipv4/igmp.c#L1178">1178</a>                 <a href="ident?i=ip_mc_filter_del">ip_mc_filter_del</a>(in_dev, im-&gt;multiaddr);
<a name="L1179" href="source/net/ipv4/igmp.c#L1179">1179</a>         }
<a name="L1180" href="source/net/ipv4/igmp.c#L1180">1180</a> 
<a name="L1181" href="source/net/ipv4/igmp.c#L1181">1181</a> #ifdef CONFIG_IP_MULTICAST
<a name="L1182" href="source/net/ipv4/igmp.c#L1182">1182</a>         if (im-&gt;multiaddr == <a href="ident?i=IGMP_ALL_HOSTS">IGMP_ALL_HOSTS</a>)
<a name="L1183" href="source/net/ipv4/igmp.c#L1183">1183</a>                 return;
<a name="L1184" href="source/net/ipv4/igmp.c#L1184">1184</a> 
<a name="L1185" href="source/net/ipv4/igmp.c#L1185">1185</a>         reporter = im-&gt;reporter;
<a name="L1186" href="source/net/ipv4/igmp.c#L1186">1186</a>         <a href="ident?i=igmp_stop_timer">igmp_stop_timer</a>(im);
<a name="L1187" href="source/net/ipv4/igmp.c#L1187">1187</a> 
<a name="L1188" href="source/net/ipv4/igmp.c#L1188">1188</a>         if (!in_dev-&gt;dead) {
<a name="L1189" href="source/net/ipv4/igmp.c#L1189">1189</a>                 if (<a href="ident?i=IGMP_V1_SEEN">IGMP_V1_SEEN</a>(in_dev))
<a name="L1190" href="source/net/ipv4/igmp.c#L1190">1190</a>                         return;
<a name="L1191" href="source/net/ipv4/igmp.c#L1191">1191</a>                 if (<a href="ident?i=IGMP_V2_SEEN">IGMP_V2_SEEN</a>(in_dev)) {
<a name="L1192" href="source/net/ipv4/igmp.c#L1192">1192</a>                         if (reporter)
<a name="L1193" href="source/net/ipv4/igmp.c#L1193">1193</a>                                 <a href="ident?i=igmp_send_report">igmp_send_report</a>(in_dev, im, <a href="ident?i=IGMP_HOST_LEAVE_MESSAGE">IGMP_HOST_LEAVE_MESSAGE</a>);
<a name="L1194" href="source/net/ipv4/igmp.c#L1194">1194</a>                         return;
<a name="L1195" href="source/net/ipv4/igmp.c#L1195">1195</a>                 }
<a name="L1196" href="source/net/ipv4/igmp.c#L1196">1196</a>                 <b><i>/* IGMPv3 */</i></b>
<a name="L1197" href="source/net/ipv4/igmp.c#L1197">1197</a>                 <a href="ident?i=igmpv3_add_delrec">igmpv3_add_delrec</a>(in_dev, im);
<a name="L1198" href="source/net/ipv4/igmp.c#L1198">1198</a> 
<a name="L1199" href="source/net/ipv4/igmp.c#L1199">1199</a>                 <a href="ident?i=igmp_ifc_event">igmp_ifc_event</a>(in_dev);
<a name="L1200" href="source/net/ipv4/igmp.c#L1200">1200</a>         }
<a name="L1201" href="source/net/ipv4/igmp.c#L1201">1201</a> #endif
<a name="L1202" href="source/net/ipv4/igmp.c#L1202">1202</a> }
<a name="L1203" href="source/net/ipv4/igmp.c#L1203">1203</a> 
<a name="L1204" href="source/net/ipv4/igmp.c#L1204">1204</a> static void <a href="ident?i=igmp_group_added">igmp_group_added</a>(struct <a href="ident?i=ip_mc_list">ip_mc_list</a> *im)
<a name="L1205" href="source/net/ipv4/igmp.c#L1205">1205</a> {
<a name="L1206" href="source/net/ipv4/igmp.c#L1206">1206</a>         struct <a href="ident?i=in_device">in_device</a> *in_dev = im-&gt;<a href="ident?i=interface">interface</a>;
<a name="L1207" href="source/net/ipv4/igmp.c#L1207">1207</a> 
<a name="L1208" href="source/net/ipv4/igmp.c#L1208">1208</a>         if (im-&gt;<a href="ident?i=loaded">loaded</a> == 0) {
<a name="L1209" href="source/net/ipv4/igmp.c#L1209">1209</a>                 im-&gt;<a href="ident?i=loaded">loaded</a> = 1;
<a name="L1210" href="source/net/ipv4/igmp.c#L1210">1210</a>                 <a href="ident?i=ip_mc_filter_add">ip_mc_filter_add</a>(in_dev, im-&gt;multiaddr);
<a name="L1211" href="source/net/ipv4/igmp.c#L1211">1211</a>         }
<a name="L1212" href="source/net/ipv4/igmp.c#L1212">1212</a> 
<a name="L1213" href="source/net/ipv4/igmp.c#L1213">1213</a> #ifdef CONFIG_IP_MULTICAST
<a name="L1214" href="source/net/ipv4/igmp.c#L1214">1214</a>         if (im-&gt;multiaddr == <a href="ident?i=IGMP_ALL_HOSTS">IGMP_ALL_HOSTS</a>)
<a name="L1215" href="source/net/ipv4/igmp.c#L1215">1215</a>                 return;
<a name="L1216" href="source/net/ipv4/igmp.c#L1216">1216</a> 
<a name="L1217" href="source/net/ipv4/igmp.c#L1217">1217</a>         if (in_dev-&gt;dead)
<a name="L1218" href="source/net/ipv4/igmp.c#L1218">1218</a>                 return;
<a name="L1219" href="source/net/ipv4/igmp.c#L1219">1219</a>         if (<a href="ident?i=IGMP_V1_SEEN">IGMP_V1_SEEN</a>(in_dev) || <a href="ident?i=IGMP_V2_SEEN">IGMP_V2_SEEN</a>(in_dev)) {
<a name="L1220" href="source/net/ipv4/igmp.c#L1220">1220</a>                 <a href="ident?i=spin_lock_bh">spin_lock_bh</a>(&amp;im-&gt;<a href="ident?i=lock">lock</a>);
<a name="L1221" href="source/net/ipv4/igmp.c#L1221">1221</a>                 <a href="ident?i=igmp_start_timer">igmp_start_timer</a>(im, <a href="ident?i=IGMP_INITIAL_REPORT_DELAY">IGMP_INITIAL_REPORT_DELAY</a>);
<a name="L1222" href="source/net/ipv4/igmp.c#L1222">1222</a>                 <a href="ident?i=spin_unlock_bh">spin_unlock_bh</a>(&amp;im-&gt;<a href="ident?i=lock">lock</a>);
<a name="L1223" href="source/net/ipv4/igmp.c#L1223">1223</a>                 return;
<a name="L1224" href="source/net/ipv4/igmp.c#L1224">1224</a>         }
<a name="L1225" href="source/net/ipv4/igmp.c#L1225">1225</a>         <b><i>/* else, v3 */</i></b>
<a name="L1226" href="source/net/ipv4/igmp.c#L1226">1226</a> 
<a name="L1227" href="source/net/ipv4/igmp.c#L1227">1227</a>         im-&gt;crcount = in_dev-&gt;mr_qrv ?: <a href="ident?i=sysctl_igmp_qrv">sysctl_igmp_qrv</a>;
<a name="L1228" href="source/net/ipv4/igmp.c#L1228">1228</a>         <a href="ident?i=igmp_ifc_event">igmp_ifc_event</a>(in_dev);
<a name="L1229" href="source/net/ipv4/igmp.c#L1229">1229</a> #endif
<a name="L1230" href="source/net/ipv4/igmp.c#L1230">1230</a> }
<a name="L1231" href="source/net/ipv4/igmp.c#L1231">1231</a> 
<a name="L1232" href="source/net/ipv4/igmp.c#L1232">1232</a> 
<a name="L1233" href="source/net/ipv4/igmp.c#L1233">1233</a> <b><i>/*</i></b>
<a name="L1234" href="source/net/ipv4/igmp.c#L1234">1234</a> <b><i> *      Multicast list managers</i></b>
<a name="L1235" href="source/net/ipv4/igmp.c#L1235">1235</a> <b><i> */</i></b>
<a name="L1236" href="source/net/ipv4/igmp.c#L1236">1236</a> 
<a name="L1237" href="source/net/ipv4/igmp.c#L1237">1237</a> static <a href="ident?i=u32">u32</a> <a href="ident?i=ip_mc_hash">ip_mc_hash</a>(const struct <a href="ident?i=ip_mc_list">ip_mc_list</a> *im)
<a name="L1238" href="source/net/ipv4/igmp.c#L1238">1238</a> {
<a name="L1239" href="source/net/ipv4/igmp.c#L1239">1239</a>         return <a href="ident?i=hash_32">hash_32</a>((<a href="ident?i=__force">__force</a> <a href="ident?i=u32">u32</a>)im-&gt;multiaddr, <a href="ident?i=MC_HASH_SZ_LOG">MC_HASH_SZ_LOG</a>);
<a name="L1240" href="source/net/ipv4/igmp.c#L1240">1240</a> }
<a name="L1241" href="source/net/ipv4/igmp.c#L1241">1241</a> 
<a name="L1242" href="source/net/ipv4/igmp.c#L1242">1242</a> static void <a href="ident?i=ip_mc_hash_add">ip_mc_hash_add</a>(struct <a href="ident?i=in_device">in_device</a> *in_dev,
<a name="L1243" href="source/net/ipv4/igmp.c#L1243">1243</a>                            struct <a href="ident?i=ip_mc_list">ip_mc_list</a> *im)
<a name="L1244" href="source/net/ipv4/igmp.c#L1244">1244</a> {
<a name="L1245" href="source/net/ipv4/igmp.c#L1245">1245</a>         struct <a href="ident?i=ip_mc_list">ip_mc_list</a> <a href="ident?i=__rcu">__rcu</a> **<a href="ident?i=mc_hash">mc_hash</a>;
<a name="L1246" href="source/net/ipv4/igmp.c#L1246">1246</a>         <a href="ident?i=u32">u32</a> <a href="ident?i=hash">hash</a>;
<a name="L1247" href="source/net/ipv4/igmp.c#L1247">1247</a> 
<a name="L1248" href="source/net/ipv4/igmp.c#L1248">1248</a>         <a href="ident?i=mc_hash">mc_hash</a> = <a href="ident?i=rtnl_dereference">rtnl_dereference</a>(in_dev-&gt;<a href="ident?i=mc_hash">mc_hash</a>);
<a name="L1249" href="source/net/ipv4/igmp.c#L1249">1249</a>         if (<a href="ident?i=mc_hash">mc_hash</a>) {
<a name="L1250" href="source/net/ipv4/igmp.c#L1250">1250</a>                 <a href="ident?i=hash">hash</a> = <a href="ident?i=ip_mc_hash">ip_mc_hash</a>(im);
<a name="L1251" href="source/net/ipv4/igmp.c#L1251">1251</a>                 im-&gt;next_hash = <a href="ident?i=mc_hash">mc_hash</a>[<a href="ident?i=hash">hash</a>];
<a name="L1252" href="source/net/ipv4/igmp.c#L1252">1252</a>                 <a href="ident?i=rcu_assign_pointer">rcu_assign_pointer</a>(<a href="ident?i=mc_hash">mc_hash</a>[<a href="ident?i=hash">hash</a>], im);
<a name="L1253" href="source/net/ipv4/igmp.c#L1253">1253</a>                 return;
<a name="L1254" href="source/net/ipv4/igmp.c#L1254">1254</a>         }
<a name="L1255" href="source/net/ipv4/igmp.c#L1255">1255</a> 
<a name="L1256" href="source/net/ipv4/igmp.c#L1256">1256</a>         <b><i>/* do not use a hash table for small number of items */</i></b>
<a name="L1257" href="source/net/ipv4/igmp.c#L1257">1257</a>         if (in_dev-&gt;mc_count &lt; 4)
<a name="L1258" href="source/net/ipv4/igmp.c#L1258">1258</a>                 return;
<a name="L1259" href="source/net/ipv4/igmp.c#L1259">1259</a> 
<a name="L1260" href="source/net/ipv4/igmp.c#L1260">1260</a>         <a href="ident?i=mc_hash">mc_hash</a> = <a href="ident?i=kzalloc">kzalloc</a>(sizeof(struct <a href="ident?i=ip_mc_list">ip_mc_list</a> *) &lt;&lt; <a href="ident?i=MC_HASH_SZ_LOG">MC_HASH_SZ_LOG</a>,
<a name="L1261" href="source/net/ipv4/igmp.c#L1261">1261</a>                           <a href="ident?i=GFP_KERNEL">GFP_KERNEL</a>);
<a name="L1262" href="source/net/ipv4/igmp.c#L1262">1262</a>         if (!<a href="ident?i=mc_hash">mc_hash</a>)
<a name="L1263" href="source/net/ipv4/igmp.c#L1263">1263</a>                 return;
<a name="L1264" href="source/net/ipv4/igmp.c#L1264">1264</a> 
<a name="L1265" href="source/net/ipv4/igmp.c#L1265">1265</a>         <a href="ident?i=for_each_pmc_rtnl">for_each_pmc_rtnl</a>(in_dev, im) {
<a name="L1266" href="source/net/ipv4/igmp.c#L1266">1266</a>                 <a href="ident?i=hash">hash</a> = <a href="ident?i=ip_mc_hash">ip_mc_hash</a>(im);
<a name="L1267" href="source/net/ipv4/igmp.c#L1267">1267</a>                 im-&gt;next_hash = <a href="ident?i=mc_hash">mc_hash</a>[<a href="ident?i=hash">hash</a>];
<a name="L1268" href="source/net/ipv4/igmp.c#L1268">1268</a>                 <a href="ident?i=RCU_INIT_POINTER">RCU_INIT_POINTER</a>(<a href="ident?i=mc_hash">mc_hash</a>[<a href="ident?i=hash">hash</a>], im);
<a name="L1269" href="source/net/ipv4/igmp.c#L1269">1269</a>         }
<a name="L1270" href="source/net/ipv4/igmp.c#L1270">1270</a> 
<a name="L1271" href="source/net/ipv4/igmp.c#L1271">1271</a>         <a href="ident?i=rcu_assign_pointer">rcu_assign_pointer</a>(in_dev-&gt;<a href="ident?i=mc_hash">mc_hash</a>, <a href="ident?i=mc_hash">mc_hash</a>);
<a name="L1272" href="source/net/ipv4/igmp.c#L1272">1272</a> }
<a name="L1273" href="source/net/ipv4/igmp.c#L1273">1273</a> 
<a name="L1274" href="source/net/ipv4/igmp.c#L1274">1274</a> static void <a href="ident?i=ip_mc_hash_remove">ip_mc_hash_remove</a>(struct <a href="ident?i=in_device">in_device</a> *in_dev,
<a name="L1275" href="source/net/ipv4/igmp.c#L1275">1275</a>                               struct <a href="ident?i=ip_mc_list">ip_mc_list</a> *im)
<a name="L1276" href="source/net/ipv4/igmp.c#L1276">1276</a> {
<a name="L1277" href="source/net/ipv4/igmp.c#L1277">1277</a>         struct <a href="ident?i=ip_mc_list">ip_mc_list</a> <a href="ident?i=__rcu">__rcu</a> **<a href="ident?i=mc_hash">mc_hash</a> = <a href="ident?i=rtnl_dereference">rtnl_dereference</a>(in_dev-&gt;<a href="ident?i=mc_hash">mc_hash</a>);
<a name="L1278" href="source/net/ipv4/igmp.c#L1278">1278</a>         struct <a href="ident?i=ip_mc_list">ip_mc_list</a> *aux;
<a name="L1279" href="source/net/ipv4/igmp.c#L1279">1279</a> 
<a name="L1280" href="source/net/ipv4/igmp.c#L1280">1280</a>         if (!<a href="ident?i=mc_hash">mc_hash</a>)
<a name="L1281" href="source/net/ipv4/igmp.c#L1281">1281</a>                 return;
<a name="L1282" href="source/net/ipv4/igmp.c#L1282">1282</a>         <a href="ident?i=mc_hash">mc_hash</a> += <a href="ident?i=ip_mc_hash">ip_mc_hash</a>(im);
<a name="L1283" href="source/net/ipv4/igmp.c#L1283">1283</a>         while ((aux = <a href="ident?i=rtnl_dereference">rtnl_dereference</a>(*<a href="ident?i=mc_hash">mc_hash</a>)) != im)
<a name="L1284" href="source/net/ipv4/igmp.c#L1284">1284</a>                 <a href="ident?i=mc_hash">mc_hash</a> = &amp;aux-&gt;next_hash;
<a name="L1285" href="source/net/ipv4/igmp.c#L1285">1285</a>         *<a href="ident?i=mc_hash">mc_hash</a> = im-&gt;next_hash;
<a name="L1286" href="source/net/ipv4/igmp.c#L1286">1286</a> }
<a name="L1287" href="source/net/ipv4/igmp.c#L1287">1287</a> 
<a name="L1288" href="source/net/ipv4/igmp.c#L1288">1288</a> 
<a name="L1289" href="source/net/ipv4/igmp.c#L1289">1289</a> <b><i>/*</i></b>
<a name="L1290" href="source/net/ipv4/igmp.c#L1290">1290</a> <b><i> *      A socket has joined a multicast group on device dev.</i></b>
<a name="L1291" href="source/net/ipv4/igmp.c#L1291">1291</a> <b><i> */</i></b>
<a name="L1292" href="source/net/ipv4/igmp.c#L1292">1292</a> 
<a name="L1293" href="source/net/ipv4/igmp.c#L1293">1293</a> void <a href="ident?i=ip_mc_inc_group">ip_mc_inc_group</a>(struct <a href="ident?i=in_device">in_device</a> *in_dev, <a href="ident?i=__be32">__be32</a> <a href="ident?i=addr">addr</a>)
<a name="L1294" href="source/net/ipv4/igmp.c#L1294">1294</a> {
<a name="L1295" href="source/net/ipv4/igmp.c#L1295">1295</a>         struct <a href="ident?i=ip_mc_list">ip_mc_list</a> *im;
<a name="L1296" href="source/net/ipv4/igmp.c#L1296">1296</a> 
<a name="L1297" href="source/net/ipv4/igmp.c#L1297">1297</a>         <a href="ident?i=ASSERT_RTNL">ASSERT_RTNL</a>();
<a name="L1298" href="source/net/ipv4/igmp.c#L1298">1298</a> 
<a name="L1299" href="source/net/ipv4/igmp.c#L1299">1299</a>         <a href="ident?i=for_each_pmc_rtnl">for_each_pmc_rtnl</a>(in_dev, im) {
<a name="L1300" href="source/net/ipv4/igmp.c#L1300">1300</a>                 if (im-&gt;multiaddr == <a href="ident?i=addr">addr</a>) {
<a name="L1301" href="source/net/ipv4/igmp.c#L1301">1301</a>                         im-&gt;users++;
<a name="L1302" href="source/net/ipv4/igmp.c#L1302">1302</a>                         <a href="ident?i=ip_mc_add_src">ip_mc_add_src</a>(in_dev, &amp;<a href="ident?i=addr">addr</a>, <a href="ident?i=MCAST_EXCLUDE">MCAST_EXCLUDE</a>, 0, <a href="ident?i=NULL">NULL</a>, 0);
<a name="L1303" href="source/net/ipv4/igmp.c#L1303">1303</a>                         goto <a href="ident?i=out">out</a>;
<a name="L1304" href="source/net/ipv4/igmp.c#L1304">1304</a>                 }
<a name="L1305" href="source/net/ipv4/igmp.c#L1305">1305</a>         }
<a name="L1306" href="source/net/ipv4/igmp.c#L1306">1306</a> 
<a name="L1307" href="source/net/ipv4/igmp.c#L1307">1307</a>         im = <a href="ident?i=kzalloc">kzalloc</a>(sizeof(*im), <a href="ident?i=GFP_KERNEL">GFP_KERNEL</a>);
<a name="L1308" href="source/net/ipv4/igmp.c#L1308">1308</a>         if (!im)
<a name="L1309" href="source/net/ipv4/igmp.c#L1309">1309</a>                 goto <a href="ident?i=out">out</a>;
<a name="L1310" href="source/net/ipv4/igmp.c#L1310">1310</a> 
<a name="L1311" href="source/net/ipv4/igmp.c#L1311">1311</a>         im-&gt;users = 1;
<a name="L1312" href="source/net/ipv4/igmp.c#L1312">1312</a>         im-&gt;<a href="ident?i=interface">interface</a> = in_dev;
<a name="L1313" href="source/net/ipv4/igmp.c#L1313">1313</a>         <a href="ident?i=in_dev_hold">in_dev_hold</a>(in_dev);
<a name="L1314" href="source/net/ipv4/igmp.c#L1314">1314</a>         im-&gt;multiaddr = <a href="ident?i=addr">addr</a>;
<a name="L1315" href="source/net/ipv4/igmp.c#L1315">1315</a>         <b><i>/* initial mode is (EX, empty) */</i></b>
<a name="L1316" href="source/net/ipv4/igmp.c#L1316">1316</a>         im-&gt;sfmode = <a href="ident?i=MCAST_EXCLUDE">MCAST_EXCLUDE</a>;
<a name="L1317" href="source/net/ipv4/igmp.c#L1317">1317</a>         im-&gt;sfcount[<a href="ident?i=MCAST_EXCLUDE">MCAST_EXCLUDE</a>] = 1;
<a name="L1318" href="source/net/ipv4/igmp.c#L1318">1318</a>         <a href="ident?i=atomic_set">atomic_set</a>(&amp;im-&gt;refcnt, 1);
<a name="L1319" href="source/net/ipv4/igmp.c#L1319">1319</a>         <a href="ident?i=spin_lock_init">spin_lock_init</a>(&amp;im-&gt;<a href="ident?i=lock">lock</a>);
<a name="L1320" href="source/net/ipv4/igmp.c#L1320">1320</a> #ifdef CONFIG_IP_MULTICAST
<a name="L1321" href="source/net/ipv4/igmp.c#L1321">1321</a>         <a href="ident?i=setup_timer">setup_timer</a>(&amp;im-&gt;<a href="ident?i=timer">timer</a>, <a href="ident?i=igmp_timer_expire">igmp_timer_expire</a>, (unsigned long)im);
<a name="L1322" href="source/net/ipv4/igmp.c#L1322">1322</a>         im-&gt;unsolicit_count = <a href="ident?i=sysctl_igmp_qrv">sysctl_igmp_qrv</a>;
<a name="L1323" href="source/net/ipv4/igmp.c#L1323">1323</a> #endif
<a name="L1324" href="source/net/ipv4/igmp.c#L1324">1324</a> 
<a name="L1325" href="source/net/ipv4/igmp.c#L1325">1325</a>         im-&gt;next_rcu = in_dev-&gt;mc_list;
<a name="L1326" href="source/net/ipv4/igmp.c#L1326">1326</a>         in_dev-&gt;mc_count++;
<a name="L1327" href="source/net/ipv4/igmp.c#L1327">1327</a>         <a href="ident?i=rcu_assign_pointer">rcu_assign_pointer</a>(in_dev-&gt;mc_list, im);
<a name="L1328" href="source/net/ipv4/igmp.c#L1328">1328</a> 
<a name="L1329" href="source/net/ipv4/igmp.c#L1329">1329</a>         <a href="ident?i=ip_mc_hash_add">ip_mc_hash_add</a>(in_dev, im);
<a name="L1330" href="source/net/ipv4/igmp.c#L1330">1330</a> 
<a name="L1331" href="source/net/ipv4/igmp.c#L1331">1331</a> #ifdef CONFIG_IP_MULTICAST
<a name="L1332" href="source/net/ipv4/igmp.c#L1332">1332</a>         <a href="ident?i=igmpv3_del_delrec">igmpv3_del_delrec</a>(in_dev, im-&gt;multiaddr);
<a name="L1333" href="source/net/ipv4/igmp.c#L1333">1333</a> #endif
<a name="L1334" href="source/net/ipv4/igmp.c#L1334">1334</a>         <a href="ident?i=igmp_group_added">igmp_group_added</a>(im);
<a name="L1335" href="source/net/ipv4/igmp.c#L1335">1335</a>         if (!in_dev-&gt;dead)
<a name="L1336" href="source/net/ipv4/igmp.c#L1336">1336</a>                 <a href="ident?i=ip_rt_multicast_event">ip_rt_multicast_event</a>(in_dev);
<a name="L1337" href="source/net/ipv4/igmp.c#L1337">1337</a> <a href="ident?i=out">out</a>:
<a name="L1338" href="source/net/ipv4/igmp.c#L1338">1338</a>         return;
<a name="L1339" href="source/net/ipv4/igmp.c#L1339">1339</a> }
<a name="L1340" href="source/net/ipv4/igmp.c#L1340">1340</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=ip_mc_inc_group">ip_mc_inc_group</a>);
<a name="L1341" href="source/net/ipv4/igmp.c#L1341">1341</a> 
<a name="L1342" href="source/net/ipv4/igmp.c#L1342">1342</a> <b><i>/*</i></b>
<a name="L1343" href="source/net/ipv4/igmp.c#L1343">1343</a> <b><i> *      Resend IGMP JOIN report; used by netdev notifier.</i></b>
<a name="L1344" href="source/net/ipv4/igmp.c#L1344">1344</a> <b><i> */</i></b>
<a name="L1345" href="source/net/ipv4/igmp.c#L1345">1345</a> static void <a href="ident?i=ip_mc_rejoin_groups">ip_mc_rejoin_groups</a>(struct <a href="ident?i=in_device">in_device</a> *in_dev)
<a name="L1346" href="source/net/ipv4/igmp.c#L1346">1346</a> {
<a name="L1347" href="source/net/ipv4/igmp.c#L1347">1347</a> #ifdef CONFIG_IP_MULTICAST
<a name="L1348" href="source/net/ipv4/igmp.c#L1348">1348</a>         struct <a href="ident?i=ip_mc_list">ip_mc_list</a> *im;
<a name="L1349" href="source/net/ipv4/igmp.c#L1349">1349</a>         int <a href="ident?i=type">type</a>;
<a name="L1350" href="source/net/ipv4/igmp.c#L1350">1350</a> 
<a name="L1351" href="source/net/ipv4/igmp.c#L1351">1351</a>         <a href="ident?i=ASSERT_RTNL">ASSERT_RTNL</a>();
<a name="L1352" href="source/net/ipv4/igmp.c#L1352">1352</a> 
<a name="L1353" href="source/net/ipv4/igmp.c#L1353">1353</a>         <a href="ident?i=for_each_pmc_rtnl">for_each_pmc_rtnl</a>(in_dev, im) {
<a name="L1354" href="source/net/ipv4/igmp.c#L1354">1354</a>                 if (im-&gt;multiaddr == <a href="ident?i=IGMP_ALL_HOSTS">IGMP_ALL_HOSTS</a>)
<a name="L1355" href="source/net/ipv4/igmp.c#L1355">1355</a>                         continue;
<a name="L1356" href="source/net/ipv4/igmp.c#L1356">1356</a> 
<a name="L1357" href="source/net/ipv4/igmp.c#L1357">1357</a>                 <b><i>/* a failover is happening and switches</i></b>
<a name="L1358" href="source/net/ipv4/igmp.c#L1358">1358</a> <b><i>                 * must be notified immediately</i></b>
<a name="L1359" href="source/net/ipv4/igmp.c#L1359">1359</a> <b><i>                 */</i></b>
<a name="L1360" href="source/net/ipv4/igmp.c#L1360">1360</a>                 if (<a href="ident?i=IGMP_V1_SEEN">IGMP_V1_SEEN</a>(in_dev))
<a name="L1361" href="source/net/ipv4/igmp.c#L1361">1361</a>                         <a href="ident?i=type">type</a> = <a href="ident?i=IGMP_HOST_MEMBERSHIP_REPORT">IGMP_HOST_MEMBERSHIP_REPORT</a>;
<a name="L1362" href="source/net/ipv4/igmp.c#L1362">1362</a>                 else if (<a href="ident?i=IGMP_V2_SEEN">IGMP_V2_SEEN</a>(in_dev))
<a name="L1363" href="source/net/ipv4/igmp.c#L1363">1363</a>                         <a href="ident?i=type">type</a> = <a href="ident?i=IGMPV2_HOST_MEMBERSHIP_REPORT">IGMPV2_HOST_MEMBERSHIP_REPORT</a>;
<a name="L1364" href="source/net/ipv4/igmp.c#L1364">1364</a>                 else
<a name="L1365" href="source/net/ipv4/igmp.c#L1365">1365</a>                         <a href="ident?i=type">type</a> = <a href="ident?i=IGMPV3_HOST_MEMBERSHIP_REPORT">IGMPV3_HOST_MEMBERSHIP_REPORT</a>;
<a name="L1366" href="source/net/ipv4/igmp.c#L1366">1366</a>                 <a href="ident?i=igmp_send_report">igmp_send_report</a>(in_dev, im, <a href="ident?i=type">type</a>);
<a name="L1367" href="source/net/ipv4/igmp.c#L1367">1367</a>         }
<a name="L1368" href="source/net/ipv4/igmp.c#L1368">1368</a> #endif
<a name="L1369" href="source/net/ipv4/igmp.c#L1369">1369</a> }
<a name="L1370" href="source/net/ipv4/igmp.c#L1370">1370</a> 
<a name="L1371" href="source/net/ipv4/igmp.c#L1371">1371</a> <b><i>/*</i></b>
<a name="L1372" href="source/net/ipv4/igmp.c#L1372">1372</a> <b><i> *      A socket has left a multicast group on device dev</i></b>
<a name="L1373" href="source/net/ipv4/igmp.c#L1373">1373</a> <b><i> */</i></b>
<a name="L1374" href="source/net/ipv4/igmp.c#L1374">1374</a> 
<a name="L1375" href="source/net/ipv4/igmp.c#L1375">1375</a> void <a href="ident?i=ip_mc_dec_group">ip_mc_dec_group</a>(struct <a href="ident?i=in_device">in_device</a> *in_dev, <a href="ident?i=__be32">__be32</a> <a href="ident?i=addr">addr</a>)
<a name="L1376" href="source/net/ipv4/igmp.c#L1376">1376</a> {
<a name="L1377" href="source/net/ipv4/igmp.c#L1377">1377</a>         struct <a href="ident?i=ip_mc_list">ip_mc_list</a> *<a href="ident?i=i">i</a>;
<a name="L1378" href="source/net/ipv4/igmp.c#L1378">1378</a>         struct <a href="ident?i=ip_mc_list">ip_mc_list</a> <a href="ident?i=__rcu">__rcu</a> **<a href="ident?i=ip">ip</a>;
<a name="L1379" href="source/net/ipv4/igmp.c#L1379">1379</a> 
<a name="L1380" href="source/net/ipv4/igmp.c#L1380">1380</a>         <a href="ident?i=ASSERT_RTNL">ASSERT_RTNL</a>();
<a name="L1381" href="source/net/ipv4/igmp.c#L1381">1381</a> 
<a name="L1382" href="source/net/ipv4/igmp.c#L1382">1382</a>         for (<a href="ident?i=ip">ip</a> = &amp;in_dev-&gt;mc_list;
<a name="L1383" href="source/net/ipv4/igmp.c#L1383">1383</a>              (<a href="ident?i=i">i</a> = <a href="ident?i=rtnl_dereference">rtnl_dereference</a>(*<a href="ident?i=ip">ip</a>)) != <a href="ident?i=NULL">NULL</a>;
<a name="L1384" href="source/net/ipv4/igmp.c#L1384">1384</a>              <a href="ident?i=ip">ip</a> = &amp;<a href="ident?i=i">i</a>-&gt;next_rcu) {
<a name="L1385" href="source/net/ipv4/igmp.c#L1385">1385</a>                 if (<a href="ident?i=i">i</a>-&gt;multiaddr == <a href="ident?i=addr">addr</a>) {
<a name="L1386" href="source/net/ipv4/igmp.c#L1386">1386</a>                         if (--<a href="ident?i=i">i</a>-&gt;users == 0) {
<a name="L1387" href="source/net/ipv4/igmp.c#L1387">1387</a>                                 <a href="ident?i=ip_mc_hash_remove">ip_mc_hash_remove</a>(in_dev, <a href="ident?i=i">i</a>);
<a name="L1388" href="source/net/ipv4/igmp.c#L1388">1388</a>                                 *<a href="ident?i=ip">ip</a> = <a href="ident?i=i">i</a>-&gt;next_rcu;
<a name="L1389" href="source/net/ipv4/igmp.c#L1389">1389</a>                                 in_dev-&gt;mc_count--;
<a name="L1390" href="source/net/ipv4/igmp.c#L1390">1390</a>                                 <a href="ident?i=igmp_group_dropped">igmp_group_dropped</a>(<a href="ident?i=i">i</a>);
<a name="L1391" href="source/net/ipv4/igmp.c#L1391">1391</a>                                 <a href="ident?i=ip_mc_clear_src">ip_mc_clear_src</a>(<a href="ident?i=i">i</a>);
<a name="L1392" href="source/net/ipv4/igmp.c#L1392">1392</a> 
<a name="L1393" href="source/net/ipv4/igmp.c#L1393">1393</a>                                 if (!in_dev-&gt;dead)
<a name="L1394" href="source/net/ipv4/igmp.c#L1394">1394</a>                                         <a href="ident?i=ip_rt_multicast_event">ip_rt_multicast_event</a>(in_dev);
<a name="L1395" href="source/net/ipv4/igmp.c#L1395">1395</a> 
<a name="L1396" href="source/net/ipv4/igmp.c#L1396">1396</a>                                 <a href="ident?i=ip_ma_put">ip_ma_put</a>(<a href="ident?i=i">i</a>);
<a name="L1397" href="source/net/ipv4/igmp.c#L1397">1397</a>                                 return;
<a name="L1398" href="source/net/ipv4/igmp.c#L1398">1398</a>                         }
<a name="L1399" href="source/net/ipv4/igmp.c#L1399">1399</a>                         break;
<a name="L1400" href="source/net/ipv4/igmp.c#L1400">1400</a>                 }
<a name="L1401" href="source/net/ipv4/igmp.c#L1401">1401</a>         }
<a name="L1402" href="source/net/ipv4/igmp.c#L1402">1402</a> }
<a name="L1403" href="source/net/ipv4/igmp.c#L1403">1403</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=ip_mc_dec_group">ip_mc_dec_group</a>);
<a name="L1404" href="source/net/ipv4/igmp.c#L1404">1404</a> 
<a name="L1405" href="source/net/ipv4/igmp.c#L1405">1405</a> <b><i>/* Device changing type */</i></b>
<a name="L1406" href="source/net/ipv4/igmp.c#L1406">1406</a> 
<a name="L1407" href="source/net/ipv4/igmp.c#L1407">1407</a> void <a href="ident?i=ip_mc_unmap">ip_mc_unmap</a>(struct <a href="ident?i=in_device">in_device</a> *in_dev)
<a name="L1408" href="source/net/ipv4/igmp.c#L1408">1408</a> {
<a name="L1409" href="source/net/ipv4/igmp.c#L1409">1409</a>         struct <a href="ident?i=ip_mc_list">ip_mc_list</a> *<a href="ident?i=pmc">pmc</a>;
<a name="L1410" href="source/net/ipv4/igmp.c#L1410">1410</a> 
<a name="L1411" href="source/net/ipv4/igmp.c#L1411">1411</a>         <a href="ident?i=ASSERT_RTNL">ASSERT_RTNL</a>();
<a name="L1412" href="source/net/ipv4/igmp.c#L1412">1412</a> 
<a name="L1413" href="source/net/ipv4/igmp.c#L1413">1413</a>         <a href="ident?i=for_each_pmc_rtnl">for_each_pmc_rtnl</a>(in_dev, <a href="ident?i=pmc">pmc</a>)
<a name="L1414" href="source/net/ipv4/igmp.c#L1414">1414</a>                 <a href="ident?i=igmp_group_dropped">igmp_group_dropped</a>(<a href="ident?i=pmc">pmc</a>);
<a name="L1415" href="source/net/ipv4/igmp.c#L1415">1415</a> }
<a name="L1416" href="source/net/ipv4/igmp.c#L1416">1416</a> 
<a name="L1417" href="source/net/ipv4/igmp.c#L1417">1417</a> void <a href="ident?i=ip_mc_remap">ip_mc_remap</a>(struct <a href="ident?i=in_device">in_device</a> *in_dev)
<a name="L1418" href="source/net/ipv4/igmp.c#L1418">1418</a> {
<a name="L1419" href="source/net/ipv4/igmp.c#L1419">1419</a>         struct <a href="ident?i=ip_mc_list">ip_mc_list</a> *<a href="ident?i=pmc">pmc</a>;
<a name="L1420" href="source/net/ipv4/igmp.c#L1420">1420</a> 
<a name="L1421" href="source/net/ipv4/igmp.c#L1421">1421</a>         <a href="ident?i=ASSERT_RTNL">ASSERT_RTNL</a>();
<a name="L1422" href="source/net/ipv4/igmp.c#L1422">1422</a> 
<a name="L1423" href="source/net/ipv4/igmp.c#L1423">1423</a>         <a href="ident?i=for_each_pmc_rtnl">for_each_pmc_rtnl</a>(in_dev, <a href="ident?i=pmc">pmc</a>)
<a name="L1424" href="source/net/ipv4/igmp.c#L1424">1424</a>                 <a href="ident?i=igmp_group_added">igmp_group_added</a>(<a href="ident?i=pmc">pmc</a>);
<a name="L1425" href="source/net/ipv4/igmp.c#L1425">1425</a> }
<a name="L1426" href="source/net/ipv4/igmp.c#L1426">1426</a> 
<a name="L1427" href="source/net/ipv4/igmp.c#L1427">1427</a> <b><i>/* Device going down */</i></b>
<a name="L1428" href="source/net/ipv4/igmp.c#L1428">1428</a> 
<a name="L1429" href="source/net/ipv4/igmp.c#L1429">1429</a> void <a href="ident?i=ip_mc_down">ip_mc_down</a>(struct <a href="ident?i=in_device">in_device</a> *in_dev)
<a name="L1430" href="source/net/ipv4/igmp.c#L1430">1430</a> {
<a name="L1431" href="source/net/ipv4/igmp.c#L1431">1431</a>         struct <a href="ident?i=ip_mc_list">ip_mc_list</a> *<a href="ident?i=pmc">pmc</a>;
<a name="L1432" href="source/net/ipv4/igmp.c#L1432">1432</a> 
<a name="L1433" href="source/net/ipv4/igmp.c#L1433">1433</a>         <a href="ident?i=ASSERT_RTNL">ASSERT_RTNL</a>();
<a name="L1434" href="source/net/ipv4/igmp.c#L1434">1434</a> 
<a name="L1435" href="source/net/ipv4/igmp.c#L1435">1435</a>         <a href="ident?i=for_each_pmc_rtnl">for_each_pmc_rtnl</a>(in_dev, <a href="ident?i=pmc">pmc</a>)
<a name="L1436" href="source/net/ipv4/igmp.c#L1436">1436</a>                 <a href="ident?i=igmp_group_dropped">igmp_group_dropped</a>(<a href="ident?i=pmc">pmc</a>);
<a name="L1437" href="source/net/ipv4/igmp.c#L1437">1437</a> 
<a name="L1438" href="source/net/ipv4/igmp.c#L1438">1438</a> #ifdef CONFIG_IP_MULTICAST
<a name="L1439" href="source/net/ipv4/igmp.c#L1439">1439</a>         in_dev-&gt;mr_ifc_count = 0;
<a name="L1440" href="source/net/ipv4/igmp.c#L1440">1440</a>         if (<a href="ident?i=del_timer">del_timer</a>(&amp;in_dev-&gt;mr_ifc_timer))
<a name="L1441" href="source/net/ipv4/igmp.c#L1441">1441</a>                 <a href="ident?i=__in_dev_put">__in_dev_put</a>(in_dev);
<a name="L1442" href="source/net/ipv4/igmp.c#L1442">1442</a>         in_dev-&gt;mr_gq_running = 0;
<a name="L1443" href="source/net/ipv4/igmp.c#L1443">1443</a>         if (<a href="ident?i=del_timer">del_timer</a>(&amp;in_dev-&gt;mr_gq_timer))
<a name="L1444" href="source/net/ipv4/igmp.c#L1444">1444</a>                 <a href="ident?i=__in_dev_put">__in_dev_put</a>(in_dev);
<a name="L1445" href="source/net/ipv4/igmp.c#L1445">1445</a>         <a href="ident?i=igmpv3_clear_delrec">igmpv3_clear_delrec</a>(in_dev);
<a name="L1446" href="source/net/ipv4/igmp.c#L1446">1446</a> #endif
<a name="L1447" href="source/net/ipv4/igmp.c#L1447">1447</a> 
<a name="L1448" href="source/net/ipv4/igmp.c#L1448">1448</a>         <a href="ident?i=ip_mc_dec_group">ip_mc_dec_group</a>(in_dev, <a href="ident?i=IGMP_ALL_HOSTS">IGMP_ALL_HOSTS</a>);
<a name="L1449" href="source/net/ipv4/igmp.c#L1449">1449</a> }
<a name="L1450" href="source/net/ipv4/igmp.c#L1450">1450</a> 
<a name="L1451" href="source/net/ipv4/igmp.c#L1451">1451</a> void <a href="ident?i=ip_mc_init_dev">ip_mc_init_dev</a>(struct <a href="ident?i=in_device">in_device</a> *in_dev)
<a name="L1452" href="source/net/ipv4/igmp.c#L1452">1452</a> {
<a name="L1453" href="source/net/ipv4/igmp.c#L1453">1453</a>         <a href="ident?i=ASSERT_RTNL">ASSERT_RTNL</a>();
<a name="L1454" href="source/net/ipv4/igmp.c#L1454">1454</a> 
<a name="L1455" href="source/net/ipv4/igmp.c#L1455">1455</a> #ifdef CONFIG_IP_MULTICAST
<a name="L1456" href="source/net/ipv4/igmp.c#L1456">1456</a>         <a href="ident?i=setup_timer">setup_timer</a>(&amp;in_dev-&gt;mr_gq_timer, <a href="ident?i=igmp_gq_timer_expire">igmp_gq_timer_expire</a>,
<a name="L1457" href="source/net/ipv4/igmp.c#L1457">1457</a>                         (unsigned long)in_dev);
<a name="L1458" href="source/net/ipv4/igmp.c#L1458">1458</a>         <a href="ident?i=setup_timer">setup_timer</a>(&amp;in_dev-&gt;mr_ifc_timer, <a href="ident?i=igmp_ifc_timer_expire">igmp_ifc_timer_expire</a>,
<a name="L1459" href="source/net/ipv4/igmp.c#L1459">1459</a>                         (unsigned long)in_dev);
<a name="L1460" href="source/net/ipv4/igmp.c#L1460">1460</a>         in_dev-&gt;mr_qrv = <a href="ident?i=sysctl_igmp_qrv">sysctl_igmp_qrv</a>;
<a name="L1461" href="source/net/ipv4/igmp.c#L1461">1461</a> #endif
<a name="L1462" href="source/net/ipv4/igmp.c#L1462">1462</a> 
<a name="L1463" href="source/net/ipv4/igmp.c#L1463">1463</a>         <a href="ident?i=spin_lock_init">spin_lock_init</a>(&amp;in_dev-&gt;mc_tomb_lock);
<a name="L1464" href="source/net/ipv4/igmp.c#L1464">1464</a> }
<a name="L1465" href="source/net/ipv4/igmp.c#L1465">1465</a> 
<a name="L1466" href="source/net/ipv4/igmp.c#L1466">1466</a> <b><i>/* Device going up */</i></b>
<a name="L1467" href="source/net/ipv4/igmp.c#L1467">1467</a> 
<a name="L1468" href="source/net/ipv4/igmp.c#L1468">1468</a> void <a href="ident?i=ip_mc_up">ip_mc_up</a>(struct <a href="ident?i=in_device">in_device</a> *in_dev)
<a name="L1469" href="source/net/ipv4/igmp.c#L1469">1469</a> {
<a name="L1470" href="source/net/ipv4/igmp.c#L1470">1470</a>         struct <a href="ident?i=ip_mc_list">ip_mc_list</a> *<a href="ident?i=pmc">pmc</a>;
<a name="L1471" href="source/net/ipv4/igmp.c#L1471">1471</a> 
<a name="L1472" href="source/net/ipv4/igmp.c#L1472">1472</a>         <a href="ident?i=ASSERT_RTNL">ASSERT_RTNL</a>();
<a name="L1473" href="source/net/ipv4/igmp.c#L1473">1473</a> 
<a name="L1474" href="source/net/ipv4/igmp.c#L1474">1474</a> #ifdef CONFIG_IP_MULTICAST
<a name="L1475" href="source/net/ipv4/igmp.c#L1475">1475</a>         in_dev-&gt;mr_qrv = <a href="ident?i=sysctl_igmp_qrv">sysctl_igmp_qrv</a>;
<a name="L1476" href="source/net/ipv4/igmp.c#L1476">1476</a> #endif
<a name="L1477" href="source/net/ipv4/igmp.c#L1477">1477</a>         <a href="ident?i=ip_mc_inc_group">ip_mc_inc_group</a>(in_dev, <a href="ident?i=IGMP_ALL_HOSTS">IGMP_ALL_HOSTS</a>);
<a name="L1478" href="source/net/ipv4/igmp.c#L1478">1478</a> 
<a name="L1479" href="source/net/ipv4/igmp.c#L1479">1479</a>         <a href="ident?i=for_each_pmc_rtnl">for_each_pmc_rtnl</a>(in_dev, <a href="ident?i=pmc">pmc</a>)
<a name="L1480" href="source/net/ipv4/igmp.c#L1480">1480</a>                 <a href="ident?i=igmp_group_added">igmp_group_added</a>(<a href="ident?i=pmc">pmc</a>);
<a name="L1481" href="source/net/ipv4/igmp.c#L1481">1481</a> }
<a name="L1482" href="source/net/ipv4/igmp.c#L1482">1482</a> 
<a name="L1483" href="source/net/ipv4/igmp.c#L1483">1483</a> <b><i>/*</i></b>
<a name="L1484" href="source/net/ipv4/igmp.c#L1484">1484</a> <b><i> *      Device is about to be destroyed: clean up.</i></b>
<a name="L1485" href="source/net/ipv4/igmp.c#L1485">1485</a> <b><i> */</i></b>
<a name="L1486" href="source/net/ipv4/igmp.c#L1486">1486</a> 
<a name="L1487" href="source/net/ipv4/igmp.c#L1487">1487</a> void <a href="ident?i=ip_mc_destroy_dev">ip_mc_destroy_dev</a>(struct <a href="ident?i=in_device">in_device</a> *in_dev)
<a name="L1488" href="source/net/ipv4/igmp.c#L1488">1488</a> {
<a name="L1489" href="source/net/ipv4/igmp.c#L1489">1489</a>         struct <a href="ident?i=ip_mc_list">ip_mc_list</a> *<a href="ident?i=i">i</a>;
<a name="L1490" href="source/net/ipv4/igmp.c#L1490">1490</a> 
<a name="L1491" href="source/net/ipv4/igmp.c#L1491">1491</a>         <a href="ident?i=ASSERT_RTNL">ASSERT_RTNL</a>();
<a name="L1492" href="source/net/ipv4/igmp.c#L1492">1492</a> 
<a name="L1493" href="source/net/ipv4/igmp.c#L1493">1493</a>         <b><i>/* Deactivate timers */</i></b>
<a name="L1494" href="source/net/ipv4/igmp.c#L1494">1494</a>         <a href="ident?i=ip_mc_down">ip_mc_down</a>(in_dev);
<a name="L1495" href="source/net/ipv4/igmp.c#L1495">1495</a> 
<a name="L1496" href="source/net/ipv4/igmp.c#L1496">1496</a>         while ((<a href="ident?i=i">i</a> = <a href="ident?i=rtnl_dereference">rtnl_dereference</a>(in_dev-&gt;mc_list)) != <a href="ident?i=NULL">NULL</a>) {
<a name="L1497" href="source/net/ipv4/igmp.c#L1497">1497</a>                 in_dev-&gt;mc_list = <a href="ident?i=i">i</a>-&gt;next_rcu;
<a name="L1498" href="source/net/ipv4/igmp.c#L1498">1498</a>                 in_dev-&gt;mc_count--;
<a name="L1499" href="source/net/ipv4/igmp.c#L1499">1499</a> 
<a name="L1500" href="source/net/ipv4/igmp.c#L1500">1500</a>                 <b><i>/* We've dropped the groups in ip_mc_down already */</i></b>
<a name="L1501" href="source/net/ipv4/igmp.c#L1501">1501</a>                 <a href="ident?i=ip_mc_clear_src">ip_mc_clear_src</a>(<a href="ident?i=i">i</a>);
<a name="L1502" href="source/net/ipv4/igmp.c#L1502">1502</a>                 <a href="ident?i=ip_ma_put">ip_ma_put</a>(<a href="ident?i=i">i</a>);
<a name="L1503" href="source/net/ipv4/igmp.c#L1503">1503</a>         }
<a name="L1504" href="source/net/ipv4/igmp.c#L1504">1504</a> }
<a name="L1505" href="source/net/ipv4/igmp.c#L1505">1505</a> 
<a name="L1506" href="source/net/ipv4/igmp.c#L1506">1506</a> <b><i>/* RTNL is locked */</i></b>
<a name="L1507" href="source/net/ipv4/igmp.c#L1507">1507</a> static struct <a href="ident?i=in_device">in_device</a> *<a href="ident?i=ip_mc_find_dev">ip_mc_find_dev</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>, struct <a href="ident?i=ip_mreqn">ip_mreqn</a> *imr)
<a name="L1508" href="source/net/ipv4/igmp.c#L1508">1508</a> {
<a name="L1509" href="source/net/ipv4/igmp.c#L1509">1509</a>         struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a> = <a href="ident?i=NULL">NULL</a>;
<a name="L1510" href="source/net/ipv4/igmp.c#L1510">1510</a>         struct <a href="ident?i=in_device">in_device</a> *<a href="ident?i=idev">idev</a> = <a href="ident?i=NULL">NULL</a>;
<a name="L1511" href="source/net/ipv4/igmp.c#L1511">1511</a> 
<a name="L1512" href="source/net/ipv4/igmp.c#L1512">1512</a>         if (imr-&gt;imr_ifindex) {
<a name="L1513" href="source/net/ipv4/igmp.c#L1513">1513</a>                 <a href="ident?i=idev">idev</a> = <a href="ident?i=inetdev_by_index">inetdev_by_index</a>(<a href="ident?i=net">net</a>, imr-&gt;imr_ifindex);
<a name="L1514" href="source/net/ipv4/igmp.c#L1514">1514</a>                 return <a href="ident?i=idev">idev</a>;
<a name="L1515" href="source/net/ipv4/igmp.c#L1515">1515</a>         }
<a name="L1516" href="source/net/ipv4/igmp.c#L1516">1516</a>         if (imr-&gt;imr_address.s_addr) {
<a name="L1517" href="source/net/ipv4/igmp.c#L1517">1517</a>                 <a href="ident?i=dev">dev</a> = <a href="ident?i=__ip_dev_find">__ip_dev_find</a>(<a href="ident?i=net">net</a>, imr-&gt;imr_address.s_addr, <a href="ident?i=false">false</a>);
<a name="L1518" href="source/net/ipv4/igmp.c#L1518">1518</a>                 if (!<a href="ident?i=dev">dev</a>)
<a name="L1519" href="source/net/ipv4/igmp.c#L1519">1519</a>                         return <a href="ident?i=NULL">NULL</a>;
<a name="L1520" href="source/net/ipv4/igmp.c#L1520">1520</a>         }
<a name="L1521" href="source/net/ipv4/igmp.c#L1521">1521</a> 
<a name="L1522" href="source/net/ipv4/igmp.c#L1522">1522</a>         if (!<a href="ident?i=dev">dev</a>) {
<a name="L1523" href="source/net/ipv4/igmp.c#L1523">1523</a>                 struct <a href="ident?i=rtable">rtable</a> *<a href="ident?i=rt">rt</a> = <a href="ident?i=ip_route_output">ip_route_output</a>(<a href="ident?i=net">net</a>,
<a name="L1524" href="source/net/ipv4/igmp.c#L1524">1524</a>                                                     imr-&gt;imr_multiaddr.s_addr,
<a name="L1525" href="source/net/ipv4/igmp.c#L1525">1525</a>                                                     0, 0, 0);
<a name="L1526" href="source/net/ipv4/igmp.c#L1526">1526</a>                 if (!<a href="ident?i=IS_ERR">IS_ERR</a>(<a href="ident?i=rt">rt</a>)) {
<a name="L1527" href="source/net/ipv4/igmp.c#L1527">1527</a>                         <a href="ident?i=dev">dev</a> = <a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>.<a href="ident?i=dev">dev</a>;
<a name="L1528" href="source/net/ipv4/igmp.c#L1528">1528</a>                         <a href="ident?i=ip_rt_put">ip_rt_put</a>(<a href="ident?i=rt">rt</a>);
<a name="L1529" href="source/net/ipv4/igmp.c#L1529">1529</a>                 }
<a name="L1530" href="source/net/ipv4/igmp.c#L1530">1530</a>         }
<a name="L1531" href="source/net/ipv4/igmp.c#L1531">1531</a>         if (<a href="ident?i=dev">dev</a>) {
<a name="L1532" href="source/net/ipv4/igmp.c#L1532">1532</a>                 imr-&gt;imr_ifindex = <a href="ident?i=dev">dev</a>-&gt;ifindex;
<a name="L1533" href="source/net/ipv4/igmp.c#L1533">1533</a>                 <a href="ident?i=idev">idev</a> = <a href="ident?i=__in_dev_get_rtnl">__in_dev_get_rtnl</a>(<a href="ident?i=dev">dev</a>);
<a name="L1534" href="source/net/ipv4/igmp.c#L1534">1534</a>         }
<a name="L1535" href="source/net/ipv4/igmp.c#L1535">1535</a>         return <a href="ident?i=idev">idev</a>;
<a name="L1536" href="source/net/ipv4/igmp.c#L1536">1536</a> }
<a name="L1537" href="source/net/ipv4/igmp.c#L1537">1537</a> 
<a name="L1538" href="source/net/ipv4/igmp.c#L1538">1538</a> <b><i>/*</i></b>
<a name="L1539" href="source/net/ipv4/igmp.c#L1539">1539</a> <b><i> *      Join a socket to a group</i></b>
<a name="L1540" href="source/net/ipv4/igmp.c#L1540">1540</a> <b><i> */</i></b>
<a name="L1541" href="source/net/ipv4/igmp.c#L1541">1541</a> int <a href="ident?i=sysctl_igmp_max_memberships">sysctl_igmp_max_memberships</a> <a href="ident?i=__read_mostly">__read_mostly</a> = <a href="ident?i=IP_MAX_MEMBERSHIPS">IP_MAX_MEMBERSHIPS</a>;
<a name="L1542" href="source/net/ipv4/igmp.c#L1542">1542</a> int <a href="ident?i=sysctl_igmp_max_msf">sysctl_igmp_max_msf</a> <a href="ident?i=__read_mostly">__read_mostly</a> = <a href="ident?i=IP_MAX_MSF">IP_MAX_MSF</a>;
<a name="L1543" href="source/net/ipv4/igmp.c#L1543">1543</a> #ifdef CONFIG_IP_MULTICAST
<a name="L1544" href="source/net/ipv4/igmp.c#L1544">1544</a> int <a href="ident?i=sysctl_igmp_qrv">sysctl_igmp_qrv</a> <a href="ident?i=__read_mostly">__read_mostly</a> = <a href="ident?i=IGMP_QUERY_ROBUSTNESS_VARIABLE">IGMP_QUERY_ROBUSTNESS_VARIABLE</a>;
<a name="L1545" href="source/net/ipv4/igmp.c#L1545">1545</a> #endif
<a name="L1546" href="source/net/ipv4/igmp.c#L1546">1546</a> 
<a name="L1547" href="source/net/ipv4/igmp.c#L1547">1547</a> static int <a href="ident?i=ip_mc_del1_src">ip_mc_del1_src</a>(struct <a href="ident?i=ip_mc_list">ip_mc_list</a> *<a href="ident?i=pmc">pmc</a>, int sfmode,
<a name="L1548" href="source/net/ipv4/igmp.c#L1548">1548</a>         <a href="ident?i=__be32">__be32</a> *psfsrc)
<a name="L1549" href="source/net/ipv4/igmp.c#L1549">1549</a> {
<a name="L1550" href="source/net/ipv4/igmp.c#L1550">1550</a>         struct <a href="ident?i=ip_sf_list">ip_sf_list</a> *psf, *psf_prev;
<a name="L1551" href="source/net/ipv4/igmp.c#L1551">1551</a>         int <a href="ident?i=rv">rv</a> = 0;
<a name="L1552" href="source/net/ipv4/igmp.c#L1552">1552</a> 
<a name="L1553" href="source/net/ipv4/igmp.c#L1553">1553</a>         psf_prev = <a href="ident?i=NULL">NULL</a>;
<a name="L1554" href="source/net/ipv4/igmp.c#L1554">1554</a>         for (psf = <a href="ident?i=pmc">pmc</a>-&gt;sources; psf; psf = psf-&gt;sf_next) {
<a name="L1555" href="source/net/ipv4/igmp.c#L1555">1555</a>                 if (psf-&gt;sf_inaddr == *psfsrc)
<a name="L1556" href="source/net/ipv4/igmp.c#L1556">1556</a>                         break;
<a name="L1557" href="source/net/ipv4/igmp.c#L1557">1557</a>                 psf_prev = psf;
<a name="L1558" href="source/net/ipv4/igmp.c#L1558">1558</a>         }
<a name="L1559" href="source/net/ipv4/igmp.c#L1559">1559</a>         if (!psf || psf-&gt;sf_count[sfmode] == 0) {
<a name="L1560" href="source/net/ipv4/igmp.c#L1560">1560</a>                 <b><i>/* source filter not found, or count wrong =&gt;  bug */</i></b>
<a name="L1561" href="source/net/ipv4/igmp.c#L1561">1561</a>                 return -<a href="ident?i=ESRCH">ESRCH</a>;
<a name="L1562" href="source/net/ipv4/igmp.c#L1562">1562</a>         }
<a name="L1563" href="source/net/ipv4/igmp.c#L1563">1563</a>         psf-&gt;sf_count[sfmode]--;
<a name="L1564" href="source/net/ipv4/igmp.c#L1564">1564</a>         if (psf-&gt;sf_count[sfmode] == 0) {
<a name="L1565" href="source/net/ipv4/igmp.c#L1565">1565</a>                 <a href="ident?i=ip_rt_multicast_event">ip_rt_multicast_event</a>(<a href="ident?i=pmc">pmc</a>-&gt;<a href="ident?i=interface">interface</a>);
<a name="L1566" href="source/net/ipv4/igmp.c#L1566">1566</a>         }
<a name="L1567" href="source/net/ipv4/igmp.c#L1567">1567</a>         if (!psf-&gt;sf_count[<a href="ident?i=MCAST_INCLUDE">MCAST_INCLUDE</a>] &amp;&amp; !psf-&gt;sf_count[<a href="ident?i=MCAST_EXCLUDE">MCAST_EXCLUDE</a>]) {
<a name="L1568" href="source/net/ipv4/igmp.c#L1568">1568</a> #ifdef CONFIG_IP_MULTICAST
<a name="L1569" href="source/net/ipv4/igmp.c#L1569">1569</a>                 struct <a href="ident?i=in_device">in_device</a> *in_dev = <a href="ident?i=pmc">pmc</a>-&gt;<a href="ident?i=interface">interface</a>;
<a name="L1570" href="source/net/ipv4/igmp.c#L1570">1570</a> #endif
<a name="L1571" href="source/net/ipv4/igmp.c#L1571">1571</a> 
<a name="L1572" href="source/net/ipv4/igmp.c#L1572">1572</a>                 <b><i>/* no more filters for this source */</i></b>
<a name="L1573" href="source/net/ipv4/igmp.c#L1573">1573</a>                 if (psf_prev)
<a name="L1574" href="source/net/ipv4/igmp.c#L1574">1574</a>                         psf_prev-&gt;sf_next = psf-&gt;sf_next;
<a name="L1575" href="source/net/ipv4/igmp.c#L1575">1575</a>                 else
<a name="L1576" href="source/net/ipv4/igmp.c#L1576">1576</a>                         <a href="ident?i=pmc">pmc</a>-&gt;sources = psf-&gt;sf_next;
<a name="L1577" href="source/net/ipv4/igmp.c#L1577">1577</a> #ifdef CONFIG_IP_MULTICAST
<a name="L1578" href="source/net/ipv4/igmp.c#L1578">1578</a>                 if (psf-&gt;sf_oldin &amp;&amp;
<a name="L1579" href="source/net/ipv4/igmp.c#L1579">1579</a>                     !<a href="ident?i=IGMP_V1_SEEN">IGMP_V1_SEEN</a>(in_dev) &amp;&amp; !<a href="ident?i=IGMP_V2_SEEN">IGMP_V2_SEEN</a>(in_dev)) {
<a name="L1580" href="source/net/ipv4/igmp.c#L1580">1580</a>                         psf-&gt;sf_crcount = in_dev-&gt;mr_qrv ?: <a href="ident?i=sysctl_igmp_qrv">sysctl_igmp_qrv</a>;
<a name="L1581" href="source/net/ipv4/igmp.c#L1581">1581</a>                         psf-&gt;sf_next = <a href="ident?i=pmc">pmc</a>-&gt;tomb;
<a name="L1582" href="source/net/ipv4/igmp.c#L1582">1582</a>                         <a href="ident?i=pmc">pmc</a>-&gt;tomb = psf;
<a name="L1583" href="source/net/ipv4/igmp.c#L1583">1583</a>                         <a href="ident?i=rv">rv</a> = 1;
<a name="L1584" href="source/net/ipv4/igmp.c#L1584">1584</a>                 } else
<a name="L1585" href="source/net/ipv4/igmp.c#L1585">1585</a> #endif
<a name="L1586" href="source/net/ipv4/igmp.c#L1586">1586</a>                         <a href="ident?i=kfree">kfree</a>(psf);
<a name="L1587" href="source/net/ipv4/igmp.c#L1587">1587</a>         }
<a name="L1588" href="source/net/ipv4/igmp.c#L1588">1588</a>         return <a href="ident?i=rv">rv</a>;
<a name="L1589" href="source/net/ipv4/igmp.c#L1589">1589</a> }
<a name="L1590" href="source/net/ipv4/igmp.c#L1590">1590</a> 
<a name="L1591" href="source/net/ipv4/igmp.c#L1591">1591</a> #ifndef CONFIG_IP_MULTICAST
<a name="L1592" href="source/net/ipv4/igmp.c#L1592">1592</a> #define <a href="ident?i=igmp_ifc_event">igmp_ifc_event</a>(<a href="ident?i=x">x</a>)       do { } while (0)
<a name="L1593" href="source/net/ipv4/igmp.c#L1593">1593</a> #endif
<a name="L1594" href="source/net/ipv4/igmp.c#L1594">1594</a> 
<a name="L1595" href="source/net/ipv4/igmp.c#L1595">1595</a> static int <a href="ident?i=ip_mc_del_src">ip_mc_del_src</a>(struct <a href="ident?i=in_device">in_device</a> *in_dev, <a href="ident?i=__be32">__be32</a> *pmca, int sfmode,
<a name="L1596" href="source/net/ipv4/igmp.c#L1596">1596</a>                          int sfcount, <a href="ident?i=__be32">__be32</a> *psfsrc, int <a href="ident?i=delta">delta</a>)
<a name="L1597" href="source/net/ipv4/igmp.c#L1597">1597</a> {
<a name="L1598" href="source/net/ipv4/igmp.c#L1598">1598</a>         struct <a href="ident?i=ip_mc_list">ip_mc_list</a> *<a href="ident?i=pmc">pmc</a>;
<a name="L1599" href="source/net/ipv4/igmp.c#L1599">1599</a>         int     changerec = 0;
<a name="L1600" href="source/net/ipv4/igmp.c#L1600">1600</a>         int     <a href="ident?i=i">i</a>, <a href="ident?i=err">err</a>;
<a name="L1601" href="source/net/ipv4/igmp.c#L1601">1601</a> 
<a name="L1602" href="source/net/ipv4/igmp.c#L1602">1602</a>         if (!in_dev)
<a name="L1603" href="source/net/ipv4/igmp.c#L1603">1603</a>                 return -<a href="ident?i=ENODEV">ENODEV</a>;
<a name="L1604" href="source/net/ipv4/igmp.c#L1604">1604</a>         <a href="ident?i=rcu_read_lock">rcu_read_lock</a>();
<a name="L1605" href="source/net/ipv4/igmp.c#L1605">1605</a>         <a href="ident?i=for_each_pmc_rcu">for_each_pmc_rcu</a>(in_dev, <a href="ident?i=pmc">pmc</a>) {
<a name="L1606" href="source/net/ipv4/igmp.c#L1606">1606</a>                 if (*pmca == <a href="ident?i=pmc">pmc</a>-&gt;multiaddr)
<a name="L1607" href="source/net/ipv4/igmp.c#L1607">1607</a>                         break;
<a name="L1608" href="source/net/ipv4/igmp.c#L1608">1608</a>         }
<a name="L1609" href="source/net/ipv4/igmp.c#L1609">1609</a>         if (!<a href="ident?i=pmc">pmc</a>) {
<a name="L1610" href="source/net/ipv4/igmp.c#L1610">1610</a>                 <b><i>/* MCA not found?? bug */</i></b>
<a name="L1611" href="source/net/ipv4/igmp.c#L1611">1611</a>                 <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L1612" href="source/net/ipv4/igmp.c#L1612">1612</a>                 return -<a href="ident?i=ESRCH">ESRCH</a>;
<a name="L1613" href="source/net/ipv4/igmp.c#L1613">1613</a>         }
<a name="L1614" href="source/net/ipv4/igmp.c#L1614">1614</a>         <a href="ident?i=spin_lock_bh">spin_lock_bh</a>(&amp;<a href="ident?i=pmc">pmc</a>-&gt;<a href="ident?i=lock">lock</a>);
<a name="L1615" href="source/net/ipv4/igmp.c#L1615">1615</a>         <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L1616" href="source/net/ipv4/igmp.c#L1616">1616</a> #ifdef CONFIG_IP_MULTICAST
<a name="L1617" href="source/net/ipv4/igmp.c#L1617">1617</a>         <a href="ident?i=sf_markstate">sf_markstate</a>(<a href="ident?i=pmc">pmc</a>);
<a name="L1618" href="source/net/ipv4/igmp.c#L1618">1618</a> #endif
<a name="L1619" href="source/net/ipv4/igmp.c#L1619">1619</a>         if (!<a href="ident?i=delta">delta</a>) {
<a name="L1620" href="source/net/ipv4/igmp.c#L1620">1620</a>                 <a href="ident?i=err">err</a> = -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L1621" href="source/net/ipv4/igmp.c#L1621">1621</a>                 if (!<a href="ident?i=pmc">pmc</a>-&gt;sfcount[sfmode])
<a name="L1622" href="source/net/ipv4/igmp.c#L1622">1622</a>                         goto out_unlock;
<a name="L1623" href="source/net/ipv4/igmp.c#L1623">1623</a>                 <a href="ident?i=pmc">pmc</a>-&gt;sfcount[sfmode]--;
<a name="L1624" href="source/net/ipv4/igmp.c#L1624">1624</a>         }
<a name="L1625" href="source/net/ipv4/igmp.c#L1625">1625</a>         <a href="ident?i=err">err</a> = 0;
<a name="L1626" href="source/net/ipv4/igmp.c#L1626">1626</a>         for (<a href="ident?i=i">i</a> = 0; <a href="ident?i=i">i</a> &lt; sfcount; <a href="ident?i=i">i</a>++) {
<a name="L1627" href="source/net/ipv4/igmp.c#L1627">1627</a>                 int <a href="ident?i=rv">rv</a> = <a href="ident?i=ip_mc_del1_src">ip_mc_del1_src</a>(<a href="ident?i=pmc">pmc</a>, sfmode, &amp;psfsrc[<a href="ident?i=i">i</a>]);
<a name="L1628" href="source/net/ipv4/igmp.c#L1628">1628</a> 
<a name="L1629" href="source/net/ipv4/igmp.c#L1629">1629</a>                 changerec |= <a href="ident?i=rv">rv</a> &gt; 0;
<a name="L1630" href="source/net/ipv4/igmp.c#L1630">1630</a>                 if (!<a href="ident?i=err">err</a> &amp;&amp; <a href="ident?i=rv">rv</a> &lt; 0)
<a name="L1631" href="source/net/ipv4/igmp.c#L1631">1631</a>                         <a href="ident?i=err">err</a> = <a href="ident?i=rv">rv</a>;
<a name="L1632" href="source/net/ipv4/igmp.c#L1632">1632</a>         }
<a name="L1633" href="source/net/ipv4/igmp.c#L1633">1633</a>         if (<a href="ident?i=pmc">pmc</a>-&gt;sfmode == <a href="ident?i=MCAST_EXCLUDE">MCAST_EXCLUDE</a> &amp;&amp;
<a name="L1634" href="source/net/ipv4/igmp.c#L1634">1634</a>             <a href="ident?i=pmc">pmc</a>-&gt;sfcount[<a href="ident?i=MCAST_EXCLUDE">MCAST_EXCLUDE</a>] == 0 &amp;&amp;
<a name="L1635" href="source/net/ipv4/igmp.c#L1635">1635</a>             <a href="ident?i=pmc">pmc</a>-&gt;sfcount[<a href="ident?i=MCAST_INCLUDE">MCAST_INCLUDE</a>]) {
<a name="L1636" href="source/net/ipv4/igmp.c#L1636">1636</a> #ifdef CONFIG_IP_MULTICAST
<a name="L1637" href="source/net/ipv4/igmp.c#L1637">1637</a>                 struct <a href="ident?i=ip_sf_list">ip_sf_list</a> *psf;
<a name="L1638" href="source/net/ipv4/igmp.c#L1638">1638</a> #endif
<a name="L1639" href="source/net/ipv4/igmp.c#L1639">1639</a> 
<a name="L1640" href="source/net/ipv4/igmp.c#L1640">1640</a>                 <b><i>/* filter mode change */</i></b>
<a name="L1641" href="source/net/ipv4/igmp.c#L1641">1641</a>                 <a href="ident?i=pmc">pmc</a>-&gt;sfmode = <a href="ident?i=MCAST_INCLUDE">MCAST_INCLUDE</a>;
<a name="L1642" href="source/net/ipv4/igmp.c#L1642">1642</a> #ifdef CONFIG_IP_MULTICAST
<a name="L1643" href="source/net/ipv4/igmp.c#L1643">1643</a>                 <a href="ident?i=pmc">pmc</a>-&gt;crcount = in_dev-&gt;mr_qrv ?: <a href="ident?i=sysctl_igmp_qrv">sysctl_igmp_qrv</a>;
<a name="L1644" href="source/net/ipv4/igmp.c#L1644">1644</a>                 in_dev-&gt;mr_ifc_count = <a href="ident?i=pmc">pmc</a>-&gt;crcount;
<a name="L1645" href="source/net/ipv4/igmp.c#L1645">1645</a>                 for (psf = <a href="ident?i=pmc">pmc</a>-&gt;sources; psf; psf = psf-&gt;sf_next)
<a name="L1646" href="source/net/ipv4/igmp.c#L1646">1646</a>                         psf-&gt;sf_crcount = 0;
<a name="L1647" href="source/net/ipv4/igmp.c#L1647">1647</a>                 <a href="ident?i=igmp_ifc_event">igmp_ifc_event</a>(<a href="ident?i=pmc">pmc</a>-&gt;<a href="ident?i=interface">interface</a>);
<a name="L1648" href="source/net/ipv4/igmp.c#L1648">1648</a>         } else if (<a href="ident?i=sf_setstate">sf_setstate</a>(<a href="ident?i=pmc">pmc</a>) || changerec) {
<a name="L1649" href="source/net/ipv4/igmp.c#L1649">1649</a>                 <a href="ident?i=igmp_ifc_event">igmp_ifc_event</a>(<a href="ident?i=pmc">pmc</a>-&gt;<a href="ident?i=interface">interface</a>);
<a name="L1650" href="source/net/ipv4/igmp.c#L1650">1650</a> #endif
<a name="L1651" href="source/net/ipv4/igmp.c#L1651">1651</a>         }
<a name="L1652" href="source/net/ipv4/igmp.c#L1652">1652</a> out_unlock:
<a name="L1653" href="source/net/ipv4/igmp.c#L1653">1653</a>         <a href="ident?i=spin_unlock_bh">spin_unlock_bh</a>(&amp;<a href="ident?i=pmc">pmc</a>-&gt;<a href="ident?i=lock">lock</a>);
<a name="L1654" href="source/net/ipv4/igmp.c#L1654">1654</a>         return <a href="ident?i=err">err</a>;
<a name="L1655" href="source/net/ipv4/igmp.c#L1655">1655</a> }
<a name="L1656" href="source/net/ipv4/igmp.c#L1656">1656</a> 
<a name="L1657" href="source/net/ipv4/igmp.c#L1657">1657</a> <b><i>/*</i></b>
<a name="L1658" href="source/net/ipv4/igmp.c#L1658">1658</a> <b><i> * Add multicast single-source filter to the interface list</i></b>
<a name="L1659" href="source/net/ipv4/igmp.c#L1659">1659</a> <b><i> */</i></b>
<a name="L1660" href="source/net/ipv4/igmp.c#L1660">1660</a> static int <a href="ident?i=ip_mc_add1_src">ip_mc_add1_src</a>(struct <a href="ident?i=ip_mc_list">ip_mc_list</a> *<a href="ident?i=pmc">pmc</a>, int sfmode,
<a name="L1661" href="source/net/ipv4/igmp.c#L1661">1661</a>         <a href="ident?i=__be32">__be32</a> *psfsrc)
<a name="L1662" href="source/net/ipv4/igmp.c#L1662">1662</a> {
<a name="L1663" href="source/net/ipv4/igmp.c#L1663">1663</a>         struct <a href="ident?i=ip_sf_list">ip_sf_list</a> *psf, *psf_prev;
<a name="L1664" href="source/net/ipv4/igmp.c#L1664">1664</a> 
<a name="L1665" href="source/net/ipv4/igmp.c#L1665">1665</a>         psf_prev = <a href="ident?i=NULL">NULL</a>;
<a name="L1666" href="source/net/ipv4/igmp.c#L1666">1666</a>         for (psf = <a href="ident?i=pmc">pmc</a>-&gt;sources; psf; psf = psf-&gt;sf_next) {
<a name="L1667" href="source/net/ipv4/igmp.c#L1667">1667</a>                 if (psf-&gt;sf_inaddr == *psfsrc)
<a name="L1668" href="source/net/ipv4/igmp.c#L1668">1668</a>                         break;
<a name="L1669" href="source/net/ipv4/igmp.c#L1669">1669</a>                 psf_prev = psf;
<a name="L1670" href="source/net/ipv4/igmp.c#L1670">1670</a>         }
<a name="L1671" href="source/net/ipv4/igmp.c#L1671">1671</a>         if (!psf) {
<a name="L1672" href="source/net/ipv4/igmp.c#L1672">1672</a>                 psf = <a href="ident?i=kzalloc">kzalloc</a>(sizeof(*psf), <a href="ident?i=GFP_ATOMIC">GFP_ATOMIC</a>);
<a name="L1673" href="source/net/ipv4/igmp.c#L1673">1673</a>                 if (!psf)
<a name="L1674" href="source/net/ipv4/igmp.c#L1674">1674</a>                         return -<a href="ident?i=ENOBUFS">ENOBUFS</a>;
<a name="L1675" href="source/net/ipv4/igmp.c#L1675">1675</a>                 psf-&gt;sf_inaddr = *psfsrc;
<a name="L1676" href="source/net/ipv4/igmp.c#L1676">1676</a>                 if (psf_prev) {
<a name="L1677" href="source/net/ipv4/igmp.c#L1677">1677</a>                         psf_prev-&gt;sf_next = psf;
<a name="L1678" href="source/net/ipv4/igmp.c#L1678">1678</a>                 } else
<a name="L1679" href="source/net/ipv4/igmp.c#L1679">1679</a>                         <a href="ident?i=pmc">pmc</a>-&gt;sources = psf;
<a name="L1680" href="source/net/ipv4/igmp.c#L1680">1680</a>         }
<a name="L1681" href="source/net/ipv4/igmp.c#L1681">1681</a>         psf-&gt;sf_count[sfmode]++;
<a name="L1682" href="source/net/ipv4/igmp.c#L1682">1682</a>         if (psf-&gt;sf_count[sfmode] == 1) {
<a name="L1683" href="source/net/ipv4/igmp.c#L1683">1683</a>                 <a href="ident?i=ip_rt_multicast_event">ip_rt_multicast_event</a>(<a href="ident?i=pmc">pmc</a>-&gt;<a href="ident?i=interface">interface</a>);
<a name="L1684" href="source/net/ipv4/igmp.c#L1684">1684</a>         }
<a name="L1685" href="source/net/ipv4/igmp.c#L1685">1685</a>         return 0;
<a name="L1686" href="source/net/ipv4/igmp.c#L1686">1686</a> }
<a name="L1687" href="source/net/ipv4/igmp.c#L1687">1687</a> 
<a name="L1688" href="source/net/ipv4/igmp.c#L1688">1688</a> #ifdef CONFIG_IP_MULTICAST
<a name="L1689" href="source/net/ipv4/igmp.c#L1689">1689</a> static void <a href="ident?i=sf_markstate">sf_markstate</a>(struct <a href="ident?i=ip_mc_list">ip_mc_list</a> *<a href="ident?i=pmc">pmc</a>)
<a name="L1690" href="source/net/ipv4/igmp.c#L1690">1690</a> {
<a name="L1691" href="source/net/ipv4/igmp.c#L1691">1691</a>         struct <a href="ident?i=ip_sf_list">ip_sf_list</a> *psf;
<a name="L1692" href="source/net/ipv4/igmp.c#L1692">1692</a>         int mca_xcount = <a href="ident?i=pmc">pmc</a>-&gt;sfcount[<a href="ident?i=MCAST_EXCLUDE">MCAST_EXCLUDE</a>];
<a name="L1693" href="source/net/ipv4/igmp.c#L1693">1693</a> 
<a name="L1694" href="source/net/ipv4/igmp.c#L1694">1694</a>         for (psf = <a href="ident?i=pmc">pmc</a>-&gt;sources; psf; psf = psf-&gt;sf_next)
<a name="L1695" href="source/net/ipv4/igmp.c#L1695">1695</a>                 if (<a href="ident?i=pmc">pmc</a>-&gt;sfcount[<a href="ident?i=MCAST_EXCLUDE">MCAST_EXCLUDE</a>]) {
<a name="L1696" href="source/net/ipv4/igmp.c#L1696">1696</a>                         psf-&gt;sf_oldin = mca_xcount ==
<a name="L1697" href="source/net/ipv4/igmp.c#L1697">1697</a>                                 psf-&gt;sf_count[<a href="ident?i=MCAST_EXCLUDE">MCAST_EXCLUDE</a>] &amp;&amp;
<a name="L1698" href="source/net/ipv4/igmp.c#L1698">1698</a>                                 !psf-&gt;sf_count[<a href="ident?i=MCAST_INCLUDE">MCAST_INCLUDE</a>];
<a name="L1699" href="source/net/ipv4/igmp.c#L1699">1699</a>                 } else
<a name="L1700" href="source/net/ipv4/igmp.c#L1700">1700</a>                         psf-&gt;sf_oldin = psf-&gt;sf_count[<a href="ident?i=MCAST_INCLUDE">MCAST_INCLUDE</a>] != 0;
<a name="L1701" href="source/net/ipv4/igmp.c#L1701">1701</a> }
<a name="L1702" href="source/net/ipv4/igmp.c#L1702">1702</a> 
<a name="L1703" href="source/net/ipv4/igmp.c#L1703">1703</a> static int <a href="ident?i=sf_setstate">sf_setstate</a>(struct <a href="ident?i=ip_mc_list">ip_mc_list</a> *<a href="ident?i=pmc">pmc</a>)
<a name="L1704" href="source/net/ipv4/igmp.c#L1704">1704</a> {
<a name="L1705" href="source/net/ipv4/igmp.c#L1705">1705</a>         struct <a href="ident?i=ip_sf_list">ip_sf_list</a> *psf, *dpsf;
<a name="L1706" href="source/net/ipv4/igmp.c#L1706">1706</a>         int mca_xcount = <a href="ident?i=pmc">pmc</a>-&gt;sfcount[<a href="ident?i=MCAST_EXCLUDE">MCAST_EXCLUDE</a>];
<a name="L1707" href="source/net/ipv4/igmp.c#L1707">1707</a>         int qrv = <a href="ident?i=pmc">pmc</a>-&gt;<a href="ident?i=interface">interface</a>-&gt;mr_qrv;
<a name="L1708" href="source/net/ipv4/igmp.c#L1708">1708</a>         int new_in, <a href="ident?i=rv">rv</a>;
<a name="L1709" href="source/net/ipv4/igmp.c#L1709">1709</a> 
<a name="L1710" href="source/net/ipv4/igmp.c#L1710">1710</a>         <a href="ident?i=rv">rv</a> = 0;
<a name="L1711" href="source/net/ipv4/igmp.c#L1711">1711</a>         for (psf = <a href="ident?i=pmc">pmc</a>-&gt;sources; psf; psf = psf-&gt;sf_next) {
<a name="L1712" href="source/net/ipv4/igmp.c#L1712">1712</a>                 if (<a href="ident?i=pmc">pmc</a>-&gt;sfcount[<a href="ident?i=MCAST_EXCLUDE">MCAST_EXCLUDE</a>]) {
<a name="L1713" href="source/net/ipv4/igmp.c#L1713">1713</a>                         new_in = mca_xcount == psf-&gt;sf_count[<a href="ident?i=MCAST_EXCLUDE">MCAST_EXCLUDE</a>] &amp;&amp;
<a name="L1714" href="source/net/ipv4/igmp.c#L1714">1714</a>                                 !psf-&gt;sf_count[<a href="ident?i=MCAST_INCLUDE">MCAST_INCLUDE</a>];
<a name="L1715" href="source/net/ipv4/igmp.c#L1715">1715</a>                 } else
<a name="L1716" href="source/net/ipv4/igmp.c#L1716">1716</a>                         new_in = psf-&gt;sf_count[<a href="ident?i=MCAST_INCLUDE">MCAST_INCLUDE</a>] != 0;
<a name="L1717" href="source/net/ipv4/igmp.c#L1717">1717</a>                 if (new_in) {
<a name="L1718" href="source/net/ipv4/igmp.c#L1718">1718</a>                         if (!psf-&gt;sf_oldin) {
<a name="L1719" href="source/net/ipv4/igmp.c#L1719">1719</a>                                 struct <a href="ident?i=ip_sf_list">ip_sf_list</a> *prev = <a href="ident?i=NULL">NULL</a>;
<a name="L1720" href="source/net/ipv4/igmp.c#L1720">1720</a> 
<a name="L1721" href="source/net/ipv4/igmp.c#L1721">1721</a>                                 for (dpsf = <a href="ident?i=pmc">pmc</a>-&gt;tomb; dpsf; dpsf = dpsf-&gt;sf_next) {
<a name="L1722" href="source/net/ipv4/igmp.c#L1722">1722</a>                                         if (dpsf-&gt;sf_inaddr == psf-&gt;sf_inaddr)
<a name="L1723" href="source/net/ipv4/igmp.c#L1723">1723</a>                                                 break;
<a name="L1724" href="source/net/ipv4/igmp.c#L1724">1724</a>                                         prev = dpsf;
<a name="L1725" href="source/net/ipv4/igmp.c#L1725">1725</a>                                 }
<a name="L1726" href="source/net/ipv4/igmp.c#L1726">1726</a>                                 if (dpsf) {
<a name="L1727" href="source/net/ipv4/igmp.c#L1727">1727</a>                                         if (prev)
<a name="L1728" href="source/net/ipv4/igmp.c#L1728">1728</a>                                                 prev-&gt;sf_next = dpsf-&gt;sf_next;
<a name="L1729" href="source/net/ipv4/igmp.c#L1729">1729</a>                                         else
<a name="L1730" href="source/net/ipv4/igmp.c#L1730">1730</a>                                                 <a href="ident?i=pmc">pmc</a>-&gt;tomb = dpsf-&gt;sf_next;
<a name="L1731" href="source/net/ipv4/igmp.c#L1731">1731</a>                                         <a href="ident?i=kfree">kfree</a>(dpsf);
<a name="L1732" href="source/net/ipv4/igmp.c#L1732">1732</a>                                 }
<a name="L1733" href="source/net/ipv4/igmp.c#L1733">1733</a>                                 psf-&gt;sf_crcount = qrv;
<a name="L1734" href="source/net/ipv4/igmp.c#L1734">1734</a>                                 <a href="ident?i=rv">rv</a>++;
<a name="L1735" href="source/net/ipv4/igmp.c#L1735">1735</a>                         }
<a name="L1736" href="source/net/ipv4/igmp.c#L1736">1736</a>                 } else if (psf-&gt;sf_oldin) {
<a name="L1737" href="source/net/ipv4/igmp.c#L1737">1737</a> 
<a name="L1738" href="source/net/ipv4/igmp.c#L1738">1738</a>                         psf-&gt;sf_crcount = 0;
<a name="L1739" href="source/net/ipv4/igmp.c#L1739">1739</a>                         <b><i>/*</i></b>
<a name="L1740" href="source/net/ipv4/igmp.c#L1740">1740</a> <b><i>                         * add or update "delete" records if an active filter</i></b>
<a name="L1741" href="source/net/ipv4/igmp.c#L1741">1741</a> <b><i>                         * is now inactive</i></b>
<a name="L1742" href="source/net/ipv4/igmp.c#L1742">1742</a> <b><i>                         */</i></b>
<a name="L1743" href="source/net/ipv4/igmp.c#L1743">1743</a>                         for (dpsf = <a href="ident?i=pmc">pmc</a>-&gt;tomb; dpsf; dpsf = dpsf-&gt;sf_next)
<a name="L1744" href="source/net/ipv4/igmp.c#L1744">1744</a>                                 if (dpsf-&gt;sf_inaddr == psf-&gt;sf_inaddr)
<a name="L1745" href="source/net/ipv4/igmp.c#L1745">1745</a>                                         break;
<a name="L1746" href="source/net/ipv4/igmp.c#L1746">1746</a>                         if (!dpsf) {
<a name="L1747" href="source/net/ipv4/igmp.c#L1747">1747</a>                                 dpsf = <a href="ident?i=kmalloc">kmalloc</a>(sizeof(*dpsf), <a href="ident?i=GFP_ATOMIC">GFP_ATOMIC</a>);
<a name="L1748" href="source/net/ipv4/igmp.c#L1748">1748</a>                                 if (!dpsf)
<a name="L1749" href="source/net/ipv4/igmp.c#L1749">1749</a>                                         continue;
<a name="L1750" href="source/net/ipv4/igmp.c#L1750">1750</a>                                 *dpsf = *psf;
<a name="L1751" href="source/net/ipv4/igmp.c#L1751">1751</a>                                 <b><i>/* pmc-&gt;lock held by callers */</i></b>
<a name="L1752" href="source/net/ipv4/igmp.c#L1752">1752</a>                                 dpsf-&gt;sf_next = <a href="ident?i=pmc">pmc</a>-&gt;tomb;
<a name="L1753" href="source/net/ipv4/igmp.c#L1753">1753</a>                                 <a href="ident?i=pmc">pmc</a>-&gt;tomb = dpsf;
<a name="L1754" href="source/net/ipv4/igmp.c#L1754">1754</a>                         }
<a name="L1755" href="source/net/ipv4/igmp.c#L1755">1755</a>                         dpsf-&gt;sf_crcount = qrv;
<a name="L1756" href="source/net/ipv4/igmp.c#L1756">1756</a>                         <a href="ident?i=rv">rv</a>++;
<a name="L1757" href="source/net/ipv4/igmp.c#L1757">1757</a>                 }
<a name="L1758" href="source/net/ipv4/igmp.c#L1758">1758</a>         }
<a name="L1759" href="source/net/ipv4/igmp.c#L1759">1759</a>         return <a href="ident?i=rv">rv</a>;
<a name="L1760" href="source/net/ipv4/igmp.c#L1760">1760</a> }
<a name="L1761" href="source/net/ipv4/igmp.c#L1761">1761</a> #endif
<a name="L1762" href="source/net/ipv4/igmp.c#L1762">1762</a> 
<a name="L1763" href="source/net/ipv4/igmp.c#L1763">1763</a> <b><i>/*</i></b>
<a name="L1764" href="source/net/ipv4/igmp.c#L1764">1764</a> <b><i> * Add multicast source filter list to the interface list</i></b>
<a name="L1765" href="source/net/ipv4/igmp.c#L1765">1765</a> <b><i> */</i></b>
<a name="L1766" href="source/net/ipv4/igmp.c#L1766">1766</a> static int <a href="ident?i=ip_mc_add_src">ip_mc_add_src</a>(struct <a href="ident?i=in_device">in_device</a> *in_dev, <a href="ident?i=__be32">__be32</a> *pmca, int sfmode,
<a name="L1767" href="source/net/ipv4/igmp.c#L1767">1767</a>                          int sfcount, <a href="ident?i=__be32">__be32</a> *psfsrc, int <a href="ident?i=delta">delta</a>)
<a name="L1768" href="source/net/ipv4/igmp.c#L1768">1768</a> {
<a name="L1769" href="source/net/ipv4/igmp.c#L1769">1769</a>         struct <a href="ident?i=ip_mc_list">ip_mc_list</a> *<a href="ident?i=pmc">pmc</a>;
<a name="L1770" href="source/net/ipv4/igmp.c#L1770">1770</a>         int     isexclude;
<a name="L1771" href="source/net/ipv4/igmp.c#L1771">1771</a>         int     <a href="ident?i=i">i</a>, <a href="ident?i=err">err</a>;
<a name="L1772" href="source/net/ipv4/igmp.c#L1772">1772</a> 
<a name="L1773" href="source/net/ipv4/igmp.c#L1773">1773</a>         if (!in_dev)
<a name="L1774" href="source/net/ipv4/igmp.c#L1774">1774</a>                 return -<a href="ident?i=ENODEV">ENODEV</a>;
<a name="L1775" href="source/net/ipv4/igmp.c#L1775">1775</a>         <a href="ident?i=rcu_read_lock">rcu_read_lock</a>();
<a name="L1776" href="source/net/ipv4/igmp.c#L1776">1776</a>         <a href="ident?i=for_each_pmc_rcu">for_each_pmc_rcu</a>(in_dev, <a href="ident?i=pmc">pmc</a>) {
<a name="L1777" href="source/net/ipv4/igmp.c#L1777">1777</a>                 if (*pmca == <a href="ident?i=pmc">pmc</a>-&gt;multiaddr)
<a name="L1778" href="source/net/ipv4/igmp.c#L1778">1778</a>                         break;
<a name="L1779" href="source/net/ipv4/igmp.c#L1779">1779</a>         }
<a name="L1780" href="source/net/ipv4/igmp.c#L1780">1780</a>         if (!<a href="ident?i=pmc">pmc</a>) {
<a name="L1781" href="source/net/ipv4/igmp.c#L1781">1781</a>                 <b><i>/* MCA not found?? bug */</i></b>
<a name="L1782" href="source/net/ipv4/igmp.c#L1782">1782</a>                 <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L1783" href="source/net/ipv4/igmp.c#L1783">1783</a>                 return -<a href="ident?i=ESRCH">ESRCH</a>;
<a name="L1784" href="source/net/ipv4/igmp.c#L1784">1784</a>         }
<a name="L1785" href="source/net/ipv4/igmp.c#L1785">1785</a>         <a href="ident?i=spin_lock_bh">spin_lock_bh</a>(&amp;<a href="ident?i=pmc">pmc</a>-&gt;<a href="ident?i=lock">lock</a>);
<a name="L1786" href="source/net/ipv4/igmp.c#L1786">1786</a>         <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L1787" href="source/net/ipv4/igmp.c#L1787">1787</a> 
<a name="L1788" href="source/net/ipv4/igmp.c#L1788">1788</a> #ifdef CONFIG_IP_MULTICAST
<a name="L1789" href="source/net/ipv4/igmp.c#L1789">1789</a>         <a href="ident?i=sf_markstate">sf_markstate</a>(<a href="ident?i=pmc">pmc</a>);
<a name="L1790" href="source/net/ipv4/igmp.c#L1790">1790</a> #endif
<a name="L1791" href="source/net/ipv4/igmp.c#L1791">1791</a>         isexclude = <a href="ident?i=pmc">pmc</a>-&gt;sfmode == <a href="ident?i=MCAST_EXCLUDE">MCAST_EXCLUDE</a>;
<a name="L1792" href="source/net/ipv4/igmp.c#L1792">1792</a>         if (!<a href="ident?i=delta">delta</a>)
<a name="L1793" href="source/net/ipv4/igmp.c#L1793">1793</a>                 <a href="ident?i=pmc">pmc</a>-&gt;sfcount[sfmode]++;
<a name="L1794" href="source/net/ipv4/igmp.c#L1794">1794</a>         <a href="ident?i=err">err</a> = 0;
<a name="L1795" href="source/net/ipv4/igmp.c#L1795">1795</a>         for (<a href="ident?i=i">i</a> = 0; <a href="ident?i=i">i</a> &lt; sfcount; <a href="ident?i=i">i</a>++) {
<a name="L1796" href="source/net/ipv4/igmp.c#L1796">1796</a>                 <a href="ident?i=err">err</a> = <a href="ident?i=ip_mc_add1_src">ip_mc_add1_src</a>(<a href="ident?i=pmc">pmc</a>, sfmode, &amp;psfsrc[<a href="ident?i=i">i</a>]);
<a name="L1797" href="source/net/ipv4/igmp.c#L1797">1797</a>                 if (<a href="ident?i=err">err</a>)
<a name="L1798" href="source/net/ipv4/igmp.c#L1798">1798</a>                         break;
<a name="L1799" href="source/net/ipv4/igmp.c#L1799">1799</a>         }
<a name="L1800" href="source/net/ipv4/igmp.c#L1800">1800</a>         if (<a href="ident?i=err">err</a>) {
<a name="L1801" href="source/net/ipv4/igmp.c#L1801">1801</a>                 int j;
<a name="L1802" href="source/net/ipv4/igmp.c#L1802">1802</a> 
<a name="L1803" href="source/net/ipv4/igmp.c#L1803">1803</a>                 if (!<a href="ident?i=delta">delta</a>)
<a name="L1804" href="source/net/ipv4/igmp.c#L1804">1804</a>                         <a href="ident?i=pmc">pmc</a>-&gt;sfcount[sfmode]--;
<a name="L1805" href="source/net/ipv4/igmp.c#L1805">1805</a>                 for (j = 0; j &lt; <a href="ident?i=i">i</a>; j++)
<a name="L1806" href="source/net/ipv4/igmp.c#L1806">1806</a>                         (void) <a href="ident?i=ip_mc_del1_src">ip_mc_del1_src</a>(<a href="ident?i=pmc">pmc</a>, sfmode, &amp;psfsrc[j]);
<a name="L1807" href="source/net/ipv4/igmp.c#L1807">1807</a>         } else if (isexclude != (<a href="ident?i=pmc">pmc</a>-&gt;sfcount[<a href="ident?i=MCAST_EXCLUDE">MCAST_EXCLUDE</a>] != 0)) {
<a name="L1808" href="source/net/ipv4/igmp.c#L1808">1808</a> #ifdef CONFIG_IP_MULTICAST
<a name="L1809" href="source/net/ipv4/igmp.c#L1809">1809</a>                 struct <a href="ident?i=ip_sf_list">ip_sf_list</a> *psf;
<a name="L1810" href="source/net/ipv4/igmp.c#L1810">1810</a>                 in_dev = <a href="ident?i=pmc">pmc</a>-&gt;<a href="ident?i=interface">interface</a>;
<a name="L1811" href="source/net/ipv4/igmp.c#L1811">1811</a> #endif
<a name="L1812" href="source/net/ipv4/igmp.c#L1812">1812</a> 
<a name="L1813" href="source/net/ipv4/igmp.c#L1813">1813</a>                 <b><i>/* filter mode change */</i></b>
<a name="L1814" href="source/net/ipv4/igmp.c#L1814">1814</a>                 if (<a href="ident?i=pmc">pmc</a>-&gt;sfcount[<a href="ident?i=MCAST_EXCLUDE">MCAST_EXCLUDE</a>])
<a name="L1815" href="source/net/ipv4/igmp.c#L1815">1815</a>                         <a href="ident?i=pmc">pmc</a>-&gt;sfmode = <a href="ident?i=MCAST_EXCLUDE">MCAST_EXCLUDE</a>;
<a name="L1816" href="source/net/ipv4/igmp.c#L1816">1816</a>                 else if (<a href="ident?i=pmc">pmc</a>-&gt;sfcount[<a href="ident?i=MCAST_INCLUDE">MCAST_INCLUDE</a>])
<a name="L1817" href="source/net/ipv4/igmp.c#L1817">1817</a>                         <a href="ident?i=pmc">pmc</a>-&gt;sfmode = <a href="ident?i=MCAST_INCLUDE">MCAST_INCLUDE</a>;
<a name="L1818" href="source/net/ipv4/igmp.c#L1818">1818</a> #ifdef CONFIG_IP_MULTICAST
<a name="L1819" href="source/net/ipv4/igmp.c#L1819">1819</a>                 <b><i>/* else no filters; keep old mode for reports */</i></b>
<a name="L1820" href="source/net/ipv4/igmp.c#L1820">1820</a> 
<a name="L1821" href="source/net/ipv4/igmp.c#L1821">1821</a>                 <a href="ident?i=pmc">pmc</a>-&gt;crcount = in_dev-&gt;mr_qrv ?: <a href="ident?i=sysctl_igmp_qrv">sysctl_igmp_qrv</a>;
<a name="L1822" href="source/net/ipv4/igmp.c#L1822">1822</a>                 in_dev-&gt;mr_ifc_count = <a href="ident?i=pmc">pmc</a>-&gt;crcount;
<a name="L1823" href="source/net/ipv4/igmp.c#L1823">1823</a>                 for (psf = <a href="ident?i=pmc">pmc</a>-&gt;sources; psf; psf = psf-&gt;sf_next)
<a name="L1824" href="source/net/ipv4/igmp.c#L1824">1824</a>                         psf-&gt;sf_crcount = 0;
<a name="L1825" href="source/net/ipv4/igmp.c#L1825">1825</a>                 <a href="ident?i=igmp_ifc_event">igmp_ifc_event</a>(in_dev);
<a name="L1826" href="source/net/ipv4/igmp.c#L1826">1826</a>         } else if (<a href="ident?i=sf_setstate">sf_setstate</a>(<a href="ident?i=pmc">pmc</a>)) {
<a name="L1827" href="source/net/ipv4/igmp.c#L1827">1827</a>                 <a href="ident?i=igmp_ifc_event">igmp_ifc_event</a>(in_dev);
<a name="L1828" href="source/net/ipv4/igmp.c#L1828">1828</a> #endif
<a name="L1829" href="source/net/ipv4/igmp.c#L1829">1829</a>         }
<a name="L1830" href="source/net/ipv4/igmp.c#L1830">1830</a>         <a href="ident?i=spin_unlock_bh">spin_unlock_bh</a>(&amp;<a href="ident?i=pmc">pmc</a>-&gt;<a href="ident?i=lock">lock</a>);
<a name="L1831" href="source/net/ipv4/igmp.c#L1831">1831</a>         return <a href="ident?i=err">err</a>;
<a name="L1832" href="source/net/ipv4/igmp.c#L1832">1832</a> }
<a name="L1833" href="source/net/ipv4/igmp.c#L1833">1833</a> 
<a name="L1834" href="source/net/ipv4/igmp.c#L1834">1834</a> static void <a href="ident?i=ip_mc_clear_src">ip_mc_clear_src</a>(struct <a href="ident?i=ip_mc_list">ip_mc_list</a> *<a href="ident?i=pmc">pmc</a>)
<a name="L1835" href="source/net/ipv4/igmp.c#L1835">1835</a> {
<a name="L1836" href="source/net/ipv4/igmp.c#L1836">1836</a>         struct <a href="ident?i=ip_sf_list">ip_sf_list</a> *psf, *nextpsf;
<a name="L1837" href="source/net/ipv4/igmp.c#L1837">1837</a> 
<a name="L1838" href="source/net/ipv4/igmp.c#L1838">1838</a>         for (psf = <a href="ident?i=pmc">pmc</a>-&gt;tomb; psf; psf = nextpsf) {
<a name="L1839" href="source/net/ipv4/igmp.c#L1839">1839</a>                 nextpsf = psf-&gt;sf_next;
<a name="L1840" href="source/net/ipv4/igmp.c#L1840">1840</a>                 <a href="ident?i=kfree">kfree</a>(psf);
<a name="L1841" href="source/net/ipv4/igmp.c#L1841">1841</a>         }
<a name="L1842" href="source/net/ipv4/igmp.c#L1842">1842</a>         <a href="ident?i=pmc">pmc</a>-&gt;tomb = <a href="ident?i=NULL">NULL</a>;
<a name="L1843" href="source/net/ipv4/igmp.c#L1843">1843</a>         for (psf = <a href="ident?i=pmc">pmc</a>-&gt;sources; psf; psf = nextpsf) {
<a name="L1844" href="source/net/ipv4/igmp.c#L1844">1844</a>                 nextpsf = psf-&gt;sf_next;
<a name="L1845" href="source/net/ipv4/igmp.c#L1845">1845</a>                 <a href="ident?i=kfree">kfree</a>(psf);
<a name="L1846" href="source/net/ipv4/igmp.c#L1846">1846</a>         }
<a name="L1847" href="source/net/ipv4/igmp.c#L1847">1847</a>         <a href="ident?i=pmc">pmc</a>-&gt;sources = <a href="ident?i=NULL">NULL</a>;
<a name="L1848" href="source/net/ipv4/igmp.c#L1848">1848</a>         <a href="ident?i=pmc">pmc</a>-&gt;sfmode = <a href="ident?i=MCAST_EXCLUDE">MCAST_EXCLUDE</a>;
<a name="L1849" href="source/net/ipv4/igmp.c#L1849">1849</a>         <a href="ident?i=pmc">pmc</a>-&gt;sfcount[<a href="ident?i=MCAST_INCLUDE">MCAST_INCLUDE</a>] = 0;
<a name="L1850" href="source/net/ipv4/igmp.c#L1850">1850</a>         <a href="ident?i=pmc">pmc</a>-&gt;sfcount[<a href="ident?i=MCAST_EXCLUDE">MCAST_EXCLUDE</a>] = 1;
<a name="L1851" href="source/net/ipv4/igmp.c#L1851">1851</a> }
<a name="L1852" href="source/net/ipv4/igmp.c#L1852">1852</a> 
<a name="L1853" href="source/net/ipv4/igmp.c#L1853">1853</a> <b><i>/* Join a multicast group</i></b>
<a name="L1854" href="source/net/ipv4/igmp.c#L1854">1854</a> <b><i> */</i></b>
<a name="L1855" href="source/net/ipv4/igmp.c#L1855">1855</a> 
<a name="L1856" href="source/net/ipv4/igmp.c#L1856">1856</a> int <a href="ident?i=ip_mc_join_group">ip_mc_join_group</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=ip_mreqn">ip_mreqn</a> *imr)
<a name="L1857" href="source/net/ipv4/igmp.c#L1857">1857</a> {
<a name="L1858" href="source/net/ipv4/igmp.c#L1858">1858</a>         <a href="ident?i=__be32">__be32</a> <a href="ident?i=addr">addr</a> = imr-&gt;imr_multiaddr.s_addr;
<a name="L1859" href="source/net/ipv4/igmp.c#L1859">1859</a>         struct <a href="ident?i=ip_mc_socklist">ip_mc_socklist</a> *iml, *<a href="ident?i=i">i</a>;
<a name="L1860" href="source/net/ipv4/igmp.c#L1860">1860</a>         struct <a href="ident?i=in_device">in_device</a> *in_dev;
<a name="L1861" href="source/net/ipv4/igmp.c#L1861">1861</a>         struct <a href="ident?i=inet_sock">inet_sock</a> *inet = <a href="ident?i=inet_sk">inet_sk</a>(sk);
<a name="L1862" href="source/net/ipv4/igmp.c#L1862">1862</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=sock_net">sock_net</a>(sk);
<a name="L1863" href="source/net/ipv4/igmp.c#L1863">1863</a>         int ifindex;
<a name="L1864" href="source/net/ipv4/igmp.c#L1864">1864</a>         int <a href="ident?i=count">count</a> = 0;
<a name="L1865" href="source/net/ipv4/igmp.c#L1865">1865</a>         int <a href="ident?i=err">err</a>;
<a name="L1866" href="source/net/ipv4/igmp.c#L1866">1866</a> 
<a name="L1867" href="source/net/ipv4/igmp.c#L1867">1867</a>         <a href="ident?i=ASSERT_RTNL">ASSERT_RTNL</a>();
<a name="L1868" href="source/net/ipv4/igmp.c#L1868">1868</a> 
<a name="L1869" href="source/net/ipv4/igmp.c#L1869">1869</a>         if (!<a href="ident?i=ipv4_is_multicast">ipv4_is_multicast</a>(<a href="ident?i=addr">addr</a>))
<a name="L1870" href="source/net/ipv4/igmp.c#L1870">1870</a>                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L1871" href="source/net/ipv4/igmp.c#L1871">1871</a> 
<a name="L1872" href="source/net/ipv4/igmp.c#L1872">1872</a>         in_dev = <a href="ident?i=ip_mc_find_dev">ip_mc_find_dev</a>(<a href="ident?i=net">net</a>, imr);
<a name="L1873" href="source/net/ipv4/igmp.c#L1873">1873</a> 
<a name="L1874" href="source/net/ipv4/igmp.c#L1874">1874</a>         if (!in_dev) {
<a name="L1875" href="source/net/ipv4/igmp.c#L1875">1875</a>                 <a href="ident?i=err">err</a> = -<a href="ident?i=ENODEV">ENODEV</a>;
<a name="L1876" href="source/net/ipv4/igmp.c#L1876">1876</a>                 goto <a href="ident?i=done">done</a>;
<a name="L1877" href="source/net/ipv4/igmp.c#L1877">1877</a>         }
<a name="L1878" href="source/net/ipv4/igmp.c#L1878">1878</a> 
<a name="L1879" href="source/net/ipv4/igmp.c#L1879">1879</a>         <a href="ident?i=err">err</a> = -<a href="ident?i=EADDRINUSE">EADDRINUSE</a>;
<a name="L1880" href="source/net/ipv4/igmp.c#L1880">1880</a>         ifindex = imr-&gt;imr_ifindex;
<a name="L1881" href="source/net/ipv4/igmp.c#L1881">1881</a>         <a href="ident?i=for_each_pmc_rtnl">for_each_pmc_rtnl</a>(inet, <a href="ident?i=i">i</a>) {
<a name="L1882" href="source/net/ipv4/igmp.c#L1882">1882</a>                 if (<a href="ident?i=i">i</a>-&gt;<a href="ident?i=multi">multi</a>.imr_multiaddr.s_addr == <a href="ident?i=addr">addr</a> &amp;&amp;
<a name="L1883" href="source/net/ipv4/igmp.c#L1883">1883</a>                     <a href="ident?i=i">i</a>-&gt;<a href="ident?i=multi">multi</a>.imr_ifindex == ifindex)
<a name="L1884" href="source/net/ipv4/igmp.c#L1884">1884</a>                         goto <a href="ident?i=done">done</a>;
<a name="L1885" href="source/net/ipv4/igmp.c#L1885">1885</a>                 <a href="ident?i=count">count</a>++;
<a name="L1886" href="source/net/ipv4/igmp.c#L1886">1886</a>         }
<a name="L1887" href="source/net/ipv4/igmp.c#L1887">1887</a>         <a href="ident?i=err">err</a> = -<a href="ident?i=ENOBUFS">ENOBUFS</a>;
<a name="L1888" href="source/net/ipv4/igmp.c#L1888">1888</a>         if (<a href="ident?i=count">count</a> &gt;= <a href="ident?i=sysctl_igmp_max_memberships">sysctl_igmp_max_memberships</a>)
<a name="L1889" href="source/net/ipv4/igmp.c#L1889">1889</a>                 goto <a href="ident?i=done">done</a>;
<a name="L1890" href="source/net/ipv4/igmp.c#L1890">1890</a>         iml = <a href="ident?i=sock_kmalloc">sock_kmalloc</a>(sk, sizeof(*iml), <a href="ident?i=GFP_KERNEL">GFP_KERNEL</a>);
<a name="L1891" href="source/net/ipv4/igmp.c#L1891">1891</a>         if (!iml)
<a name="L1892" href="source/net/ipv4/igmp.c#L1892">1892</a>                 goto <a href="ident?i=done">done</a>;
<a name="L1893" href="source/net/ipv4/igmp.c#L1893">1893</a> 
<a name="L1894" href="source/net/ipv4/igmp.c#L1894">1894</a>         <a href="ident?i=memcpy">memcpy</a>(&amp;iml-&gt;<a href="ident?i=multi">multi</a>, imr, sizeof(*imr));
<a name="L1895" href="source/net/ipv4/igmp.c#L1895">1895</a>         iml-&gt;next_rcu = inet-&gt;mc_list;
<a name="L1896" href="source/net/ipv4/igmp.c#L1896">1896</a>         iml-&gt;<a href="ident?i=sflist">sflist</a> = <a href="ident?i=NULL">NULL</a>;
<a name="L1897" href="source/net/ipv4/igmp.c#L1897">1897</a>         iml-&gt;sfmode = <a href="ident?i=MCAST_EXCLUDE">MCAST_EXCLUDE</a>;
<a name="L1898" href="source/net/ipv4/igmp.c#L1898">1898</a>         <a href="ident?i=rcu_assign_pointer">rcu_assign_pointer</a>(inet-&gt;mc_list, iml);
<a name="L1899" href="source/net/ipv4/igmp.c#L1899">1899</a>         <a href="ident?i=ip_mc_inc_group">ip_mc_inc_group</a>(in_dev, <a href="ident?i=addr">addr</a>);
<a name="L1900" href="source/net/ipv4/igmp.c#L1900">1900</a>         <a href="ident?i=err">err</a> = 0;
<a name="L1901" href="source/net/ipv4/igmp.c#L1901">1901</a> <a href="ident?i=done">done</a>:
<a name="L1902" href="source/net/ipv4/igmp.c#L1902">1902</a>         return <a href="ident?i=err">err</a>;
<a name="L1903" href="source/net/ipv4/igmp.c#L1903">1903</a> }
<a name="L1904" href="source/net/ipv4/igmp.c#L1904">1904</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=ip_mc_join_group">ip_mc_join_group</a>);
<a name="L1905" href="source/net/ipv4/igmp.c#L1905">1905</a> 
<a name="L1906" href="source/net/ipv4/igmp.c#L1906">1906</a> static int <a href="ident?i=ip_mc_leave_src">ip_mc_leave_src</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=ip_mc_socklist">ip_mc_socklist</a> *iml,
<a name="L1907" href="source/net/ipv4/igmp.c#L1907">1907</a>                            struct <a href="ident?i=in_device">in_device</a> *in_dev)
<a name="L1908" href="source/net/ipv4/igmp.c#L1908">1908</a> {
<a name="L1909" href="source/net/ipv4/igmp.c#L1909">1909</a>         struct <a href="ident?i=ip_sf_socklist">ip_sf_socklist</a> *psf = <a href="ident?i=rtnl_dereference">rtnl_dereference</a>(iml-&gt;<a href="ident?i=sflist">sflist</a>);
<a name="L1910" href="source/net/ipv4/igmp.c#L1910">1910</a>         int <a href="ident?i=err">err</a>;
<a name="L1911" href="source/net/ipv4/igmp.c#L1911">1911</a> 
<a name="L1912" href="source/net/ipv4/igmp.c#L1912">1912</a>         if (!psf) {
<a name="L1913" href="source/net/ipv4/igmp.c#L1913">1913</a>                 <b><i>/* any-source empty exclude case */</i></b>
<a name="L1914" href="source/net/ipv4/igmp.c#L1914">1914</a>                 return <a href="ident?i=ip_mc_del_src">ip_mc_del_src</a>(in_dev, &amp;iml-&gt;<a href="ident?i=multi">multi</a>.imr_multiaddr.s_addr,
<a name="L1915" href="source/net/ipv4/igmp.c#L1915">1915</a>                         iml-&gt;sfmode, 0, <a href="ident?i=NULL">NULL</a>, 0);
<a name="L1916" href="source/net/ipv4/igmp.c#L1916">1916</a>         }
<a name="L1917" href="source/net/ipv4/igmp.c#L1917">1917</a>         <a href="ident?i=err">err</a> = <a href="ident?i=ip_mc_del_src">ip_mc_del_src</a>(in_dev, &amp;iml-&gt;<a href="ident?i=multi">multi</a>.imr_multiaddr.s_addr,
<a name="L1918" href="source/net/ipv4/igmp.c#L1918">1918</a>                         iml-&gt;sfmode, psf-&gt;sl_count, psf-&gt;sl_addr, 0);
<a name="L1919" href="source/net/ipv4/igmp.c#L1919">1919</a>         <a href="ident?i=RCU_INIT_POINTER">RCU_INIT_POINTER</a>(iml-&gt;<a href="ident?i=sflist">sflist</a>, <a href="ident?i=NULL">NULL</a>);
<a name="L1920" href="source/net/ipv4/igmp.c#L1920">1920</a>         <b><i>/* decrease mem now to avoid the memleak warning */</i></b>
<a name="L1921" href="source/net/ipv4/igmp.c#L1921">1921</a>         <a href="ident?i=atomic_sub">atomic_sub</a>(<a href="ident?i=IP_SFLSIZE">IP_SFLSIZE</a>(psf-&gt;sl_max), &amp;sk-&gt;sk_omem_alloc);
<a name="L1922" href="source/net/ipv4/igmp.c#L1922">1922</a>         <a href="ident?i=kfree_rcu">kfree_rcu</a>(psf, rcu);
<a name="L1923" href="source/net/ipv4/igmp.c#L1923">1923</a>         return <a href="ident?i=err">err</a>;
<a name="L1924" href="source/net/ipv4/igmp.c#L1924">1924</a> }
<a name="L1925" href="source/net/ipv4/igmp.c#L1925">1925</a> 
<a name="L1926" href="source/net/ipv4/igmp.c#L1926">1926</a> int <a href="ident?i=ip_mc_leave_group">ip_mc_leave_group</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=ip_mreqn">ip_mreqn</a> *imr)
<a name="L1927" href="source/net/ipv4/igmp.c#L1927">1927</a> {
<a name="L1928" href="source/net/ipv4/igmp.c#L1928">1928</a>         struct <a href="ident?i=inet_sock">inet_sock</a> *inet = <a href="ident?i=inet_sk">inet_sk</a>(sk);
<a name="L1929" href="source/net/ipv4/igmp.c#L1929">1929</a>         struct <a href="ident?i=ip_mc_socklist">ip_mc_socklist</a> *iml;
<a name="L1930" href="source/net/ipv4/igmp.c#L1930">1930</a>         struct <a href="ident?i=ip_mc_socklist">ip_mc_socklist</a> <a href="ident?i=__rcu">__rcu</a> **imlp;
<a name="L1931" href="source/net/ipv4/igmp.c#L1931">1931</a>         struct <a href="ident?i=in_device">in_device</a> *in_dev;
<a name="L1932" href="source/net/ipv4/igmp.c#L1932">1932</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=sock_net">sock_net</a>(sk);
<a name="L1933" href="source/net/ipv4/igmp.c#L1933">1933</a>         <a href="ident?i=__be32">__be32</a> <a href="ident?i=group">group</a> = imr-&gt;imr_multiaddr.s_addr;
<a name="L1934" href="source/net/ipv4/igmp.c#L1934">1934</a>         <a href="ident?i=u32">u32</a> ifindex;
<a name="L1935" href="source/net/ipv4/igmp.c#L1935">1935</a>         int <a href="ident?i=ret">ret</a> = -<a href="ident?i=EADDRNOTAVAIL">EADDRNOTAVAIL</a>;
<a name="L1936" href="source/net/ipv4/igmp.c#L1936">1936</a> 
<a name="L1937" href="source/net/ipv4/igmp.c#L1937">1937</a>         <a href="ident?i=ASSERT_RTNL">ASSERT_RTNL</a>();
<a name="L1938" href="source/net/ipv4/igmp.c#L1938">1938</a> 
<a name="L1939" href="source/net/ipv4/igmp.c#L1939">1939</a>         in_dev = <a href="ident?i=ip_mc_find_dev">ip_mc_find_dev</a>(<a href="ident?i=net">net</a>, imr);
<a name="L1940" href="source/net/ipv4/igmp.c#L1940">1940</a>         if (!in_dev) {
<a name="L1941" href="source/net/ipv4/igmp.c#L1941">1941</a>                 <a href="ident?i=ret">ret</a> = -<a href="ident?i=ENODEV">ENODEV</a>;
<a name="L1942" href="source/net/ipv4/igmp.c#L1942">1942</a>                 goto <a href="ident?i=out">out</a>;
<a name="L1943" href="source/net/ipv4/igmp.c#L1943">1943</a>         }
<a name="L1944" href="source/net/ipv4/igmp.c#L1944">1944</a>         ifindex = imr-&gt;imr_ifindex;
<a name="L1945" href="source/net/ipv4/igmp.c#L1945">1945</a>         for (imlp = &amp;inet-&gt;mc_list;
<a name="L1946" href="source/net/ipv4/igmp.c#L1946">1946</a>              (iml = <a href="ident?i=rtnl_dereference">rtnl_dereference</a>(*imlp)) != <a href="ident?i=NULL">NULL</a>;
<a name="L1947" href="source/net/ipv4/igmp.c#L1947">1947</a>              imlp = &amp;iml-&gt;next_rcu) {
<a name="L1948" href="source/net/ipv4/igmp.c#L1948">1948</a>                 if (iml-&gt;<a href="ident?i=multi">multi</a>.imr_multiaddr.s_addr != <a href="ident?i=group">group</a>)
<a name="L1949" href="source/net/ipv4/igmp.c#L1949">1949</a>                         continue;
<a name="L1950" href="source/net/ipv4/igmp.c#L1950">1950</a>                 if (ifindex) {
<a name="L1951" href="source/net/ipv4/igmp.c#L1951">1951</a>                         if (iml-&gt;<a href="ident?i=multi">multi</a>.imr_ifindex != ifindex)
<a name="L1952" href="source/net/ipv4/igmp.c#L1952">1952</a>                                 continue;
<a name="L1953" href="source/net/ipv4/igmp.c#L1953">1953</a>                 } else if (imr-&gt;imr_address.s_addr &amp;&amp; imr-&gt;imr_address.s_addr !=
<a name="L1954" href="source/net/ipv4/igmp.c#L1954">1954</a>                                 iml-&gt;<a href="ident?i=multi">multi</a>.imr_address.s_addr)
<a name="L1955" href="source/net/ipv4/igmp.c#L1955">1955</a>                         continue;
<a name="L1956" href="source/net/ipv4/igmp.c#L1956">1956</a> 
<a name="L1957" href="source/net/ipv4/igmp.c#L1957">1957</a>                 (void) <a href="ident?i=ip_mc_leave_src">ip_mc_leave_src</a>(sk, iml, in_dev);
<a name="L1958" href="source/net/ipv4/igmp.c#L1958">1958</a> 
<a name="L1959" href="source/net/ipv4/igmp.c#L1959">1959</a>                 *imlp = iml-&gt;next_rcu;
<a name="L1960" href="source/net/ipv4/igmp.c#L1960">1960</a> 
<a name="L1961" href="source/net/ipv4/igmp.c#L1961">1961</a>                 <a href="ident?i=ip_mc_dec_group">ip_mc_dec_group</a>(in_dev, <a href="ident?i=group">group</a>);
<a name="L1962" href="source/net/ipv4/igmp.c#L1962">1962</a> 
<a name="L1963" href="source/net/ipv4/igmp.c#L1963">1963</a>                 <b><i>/* decrease mem now to avoid the memleak warning */</i></b>
<a name="L1964" href="source/net/ipv4/igmp.c#L1964">1964</a>                 <a href="ident?i=atomic_sub">atomic_sub</a>(sizeof(*iml), &amp;sk-&gt;sk_omem_alloc);
<a name="L1965" href="source/net/ipv4/igmp.c#L1965">1965</a>                 <a href="ident?i=kfree_rcu">kfree_rcu</a>(iml, rcu);
<a name="L1966" href="source/net/ipv4/igmp.c#L1966">1966</a>                 return 0;
<a name="L1967" href="source/net/ipv4/igmp.c#L1967">1967</a>         }
<a name="L1968" href="source/net/ipv4/igmp.c#L1968">1968</a> <a href="ident?i=out">out</a>:
<a name="L1969" href="source/net/ipv4/igmp.c#L1969">1969</a>         return <a href="ident?i=ret">ret</a>;
<a name="L1970" href="source/net/ipv4/igmp.c#L1970">1970</a> }
<a name="L1971" href="source/net/ipv4/igmp.c#L1971">1971</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=ip_mc_leave_group">ip_mc_leave_group</a>);
<a name="L1972" href="source/net/ipv4/igmp.c#L1972">1972</a> 
<a name="L1973" href="source/net/ipv4/igmp.c#L1973">1973</a> int <a href="ident?i=ip_mc_source">ip_mc_source</a>(int add, int omode, struct <a href="ident?i=sock">sock</a> *sk, struct
<a name="L1974" href="source/net/ipv4/igmp.c#L1974">1974</a>         <a href="ident?i=ip_mreq_source">ip_mreq_source</a> *mreqs, int ifindex)
<a name="L1975" href="source/net/ipv4/igmp.c#L1975">1975</a> {
<a name="L1976" href="source/net/ipv4/igmp.c#L1976">1976</a>         int <a href="ident?i=err">err</a>;
<a name="L1977" href="source/net/ipv4/igmp.c#L1977">1977</a>         struct <a href="ident?i=ip_mreqn">ip_mreqn</a> imr;
<a name="L1978" href="source/net/ipv4/igmp.c#L1978">1978</a>         <a href="ident?i=__be32">__be32</a> <a href="ident?i=addr">addr</a> = mreqs-&gt;imr_multiaddr;
<a name="L1979" href="source/net/ipv4/igmp.c#L1979">1979</a>         struct <a href="ident?i=ip_mc_socklist">ip_mc_socklist</a> *<a href="ident?i=pmc">pmc</a>;
<a name="L1980" href="source/net/ipv4/igmp.c#L1980">1980</a>         struct <a href="ident?i=in_device">in_device</a> *in_dev = <a href="ident?i=NULL">NULL</a>;
<a name="L1981" href="source/net/ipv4/igmp.c#L1981">1981</a>         struct <a href="ident?i=inet_sock">inet_sock</a> *inet = <a href="ident?i=inet_sk">inet_sk</a>(sk);
<a name="L1982" href="source/net/ipv4/igmp.c#L1982">1982</a>         struct <a href="ident?i=ip_sf_socklist">ip_sf_socklist</a> *psl;
<a name="L1983" href="source/net/ipv4/igmp.c#L1983">1983</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=sock_net">sock_net</a>(sk);
<a name="L1984" href="source/net/ipv4/igmp.c#L1984">1984</a>         int leavegroup = 0;
<a name="L1985" href="source/net/ipv4/igmp.c#L1985">1985</a>         int <a href="ident?i=i">i</a>, j, <a href="ident?i=rv">rv</a>;
<a name="L1986" href="source/net/ipv4/igmp.c#L1986">1986</a> 
<a name="L1987" href="source/net/ipv4/igmp.c#L1987">1987</a>         if (!<a href="ident?i=ipv4_is_multicast">ipv4_is_multicast</a>(<a href="ident?i=addr">addr</a>))
<a name="L1988" href="source/net/ipv4/igmp.c#L1988">1988</a>                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L1989" href="source/net/ipv4/igmp.c#L1989">1989</a> 
<a name="L1990" href="source/net/ipv4/igmp.c#L1990">1990</a>         <a href="ident?i=ASSERT_RTNL">ASSERT_RTNL</a>();
<a name="L1991" href="source/net/ipv4/igmp.c#L1991">1991</a> 
<a name="L1992" href="source/net/ipv4/igmp.c#L1992">1992</a>         imr.imr_multiaddr.s_addr = mreqs-&gt;imr_multiaddr;
<a name="L1993" href="source/net/ipv4/igmp.c#L1993">1993</a>         imr.imr_address.s_addr = mreqs-&gt;imr_interface;
<a name="L1994" href="source/net/ipv4/igmp.c#L1994">1994</a>         imr.imr_ifindex = ifindex;
<a name="L1995" href="source/net/ipv4/igmp.c#L1995">1995</a>         in_dev = <a href="ident?i=ip_mc_find_dev">ip_mc_find_dev</a>(<a href="ident?i=net">net</a>, &amp;imr);
<a name="L1996" href="source/net/ipv4/igmp.c#L1996">1996</a> 
<a name="L1997" href="source/net/ipv4/igmp.c#L1997">1997</a>         if (!in_dev) {
<a name="L1998" href="source/net/ipv4/igmp.c#L1998">1998</a>                 <a href="ident?i=err">err</a> = -<a href="ident?i=ENODEV">ENODEV</a>;
<a name="L1999" href="source/net/ipv4/igmp.c#L1999">1999</a>                 goto <a href="ident?i=done">done</a>;
<a name="L2000" href="source/net/ipv4/igmp.c#L2000">2000</a>         }
<a name="L2001" href="source/net/ipv4/igmp.c#L2001">2001</a>         <a href="ident?i=err">err</a> = -<a href="ident?i=EADDRNOTAVAIL">EADDRNOTAVAIL</a>;
<a name="L2002" href="source/net/ipv4/igmp.c#L2002">2002</a> 
<a name="L2003" href="source/net/ipv4/igmp.c#L2003">2003</a>         <a href="ident?i=for_each_pmc_rtnl">for_each_pmc_rtnl</a>(inet, <a href="ident?i=pmc">pmc</a>) {
<a name="L2004" href="source/net/ipv4/igmp.c#L2004">2004</a>                 if ((<a href="ident?i=pmc">pmc</a>-&gt;<a href="ident?i=multi">multi</a>.imr_multiaddr.s_addr ==
<a name="L2005" href="source/net/ipv4/igmp.c#L2005">2005</a>                      imr.imr_multiaddr.s_addr) &amp;&amp;
<a name="L2006" href="source/net/ipv4/igmp.c#L2006">2006</a>                     (<a href="ident?i=pmc">pmc</a>-&gt;<a href="ident?i=multi">multi</a>.imr_ifindex == imr.imr_ifindex))
<a name="L2007" href="source/net/ipv4/igmp.c#L2007">2007</a>                         break;
<a name="L2008" href="source/net/ipv4/igmp.c#L2008">2008</a>         }
<a name="L2009" href="source/net/ipv4/igmp.c#L2009">2009</a>         if (!<a href="ident?i=pmc">pmc</a>) {             <b><i>/* must have a prior join */</i></b>
<a name="L2010" href="source/net/ipv4/igmp.c#L2010">2010</a>                 <a href="ident?i=err">err</a> = -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L2011" href="source/net/ipv4/igmp.c#L2011">2011</a>                 goto <a href="ident?i=done">done</a>;
<a name="L2012" href="source/net/ipv4/igmp.c#L2012">2012</a>         }
<a name="L2013" href="source/net/ipv4/igmp.c#L2013">2013</a>         <b><i>/* if a source filter was set, must be the same mode as before */</i></b>
<a name="L2014" href="source/net/ipv4/igmp.c#L2014">2014</a>         if (<a href="ident?i=pmc">pmc</a>-&gt;<a href="ident?i=sflist">sflist</a>) {
<a name="L2015" href="source/net/ipv4/igmp.c#L2015">2015</a>                 if (<a href="ident?i=pmc">pmc</a>-&gt;sfmode != omode) {
<a name="L2016" href="source/net/ipv4/igmp.c#L2016">2016</a>                         <a href="ident?i=err">err</a> = -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L2017" href="source/net/ipv4/igmp.c#L2017">2017</a>                         goto <a href="ident?i=done">done</a>;
<a name="L2018" href="source/net/ipv4/igmp.c#L2018">2018</a>                 }
<a name="L2019" href="source/net/ipv4/igmp.c#L2019">2019</a>         } else if (<a href="ident?i=pmc">pmc</a>-&gt;sfmode != omode) {
<a name="L2020" href="source/net/ipv4/igmp.c#L2020">2020</a>                 <b><i>/* allow mode switches for empty-set filters */</i></b>
<a name="L2021" href="source/net/ipv4/igmp.c#L2021">2021</a>                 <a href="ident?i=ip_mc_add_src">ip_mc_add_src</a>(in_dev, &amp;mreqs-&gt;imr_multiaddr, omode, 0, <a href="ident?i=NULL">NULL</a>, 0);
<a name="L2022" href="source/net/ipv4/igmp.c#L2022">2022</a>                 <a href="ident?i=ip_mc_del_src">ip_mc_del_src</a>(in_dev, &amp;mreqs-&gt;imr_multiaddr, <a href="ident?i=pmc">pmc</a>-&gt;sfmode, 0,
<a name="L2023" href="source/net/ipv4/igmp.c#L2023">2023</a>                         <a href="ident?i=NULL">NULL</a>, 0);
<a name="L2024" href="source/net/ipv4/igmp.c#L2024">2024</a>                 <a href="ident?i=pmc">pmc</a>-&gt;sfmode = omode;
<a name="L2025" href="source/net/ipv4/igmp.c#L2025">2025</a>         }
<a name="L2026" href="source/net/ipv4/igmp.c#L2026">2026</a> 
<a name="L2027" href="source/net/ipv4/igmp.c#L2027">2027</a>         psl = <a href="ident?i=rtnl_dereference">rtnl_dereference</a>(<a href="ident?i=pmc">pmc</a>-&gt;<a href="ident?i=sflist">sflist</a>);
<a name="L2028" href="source/net/ipv4/igmp.c#L2028">2028</a>         if (!add) {
<a name="L2029" href="source/net/ipv4/igmp.c#L2029">2029</a>                 if (!psl)
<a name="L2030" href="source/net/ipv4/igmp.c#L2030">2030</a>                         goto <a href="ident?i=done">done</a>;      <b><i>/* err = -EADDRNOTAVAIL */</i></b>
<a name="L2031" href="source/net/ipv4/igmp.c#L2031">2031</a>                 <a href="ident?i=rv">rv</a> = !0;
<a name="L2032" href="source/net/ipv4/igmp.c#L2032">2032</a>                 for (<a href="ident?i=i">i</a> = 0; <a href="ident?i=i">i</a> &lt; psl-&gt;sl_count; <a href="ident?i=i">i</a>++) {
<a name="L2033" href="source/net/ipv4/igmp.c#L2033">2033</a>                         <a href="ident?i=rv">rv</a> = <a href="ident?i=memcmp">memcmp</a>(&amp;psl-&gt;sl_addr[<a href="ident?i=i">i</a>], &amp;mreqs-&gt;imr_sourceaddr,
<a name="L2034" href="source/net/ipv4/igmp.c#L2034">2034</a>                                 sizeof(<a href="ident?i=__be32">__be32</a>));
<a name="L2035" href="source/net/ipv4/igmp.c#L2035">2035</a>                         if (<a href="ident?i=rv">rv</a> == 0)
<a name="L2036" href="source/net/ipv4/igmp.c#L2036">2036</a>                                 break;
<a name="L2037" href="source/net/ipv4/igmp.c#L2037">2037</a>                 }
<a name="L2038" href="source/net/ipv4/igmp.c#L2038">2038</a>                 if (<a href="ident?i=rv">rv</a>)         <b><i>/* source not found */</i></b>
<a name="L2039" href="source/net/ipv4/igmp.c#L2039">2039</a>                         goto <a href="ident?i=done">done</a>;      <b><i>/* err = -EADDRNOTAVAIL */</i></b>
<a name="L2040" href="source/net/ipv4/igmp.c#L2040">2040</a> 
<a name="L2041" href="source/net/ipv4/igmp.c#L2041">2041</a>                 <b><i>/* special case - (INCLUDE, empty) == LEAVE_GROUP */</i></b>
<a name="L2042" href="source/net/ipv4/igmp.c#L2042">2042</a>                 if (psl-&gt;sl_count == 1 &amp;&amp; omode == <a href="ident?i=MCAST_INCLUDE">MCAST_INCLUDE</a>) {
<a name="L2043" href="source/net/ipv4/igmp.c#L2043">2043</a>                         leavegroup = 1;
<a name="L2044" href="source/net/ipv4/igmp.c#L2044">2044</a>                         goto <a href="ident?i=done">done</a>;
<a name="L2045" href="source/net/ipv4/igmp.c#L2045">2045</a>                 }
<a name="L2046" href="source/net/ipv4/igmp.c#L2046">2046</a> 
<a name="L2047" href="source/net/ipv4/igmp.c#L2047">2047</a>                 <b><i>/* update the interface filter */</i></b>
<a name="L2048" href="source/net/ipv4/igmp.c#L2048">2048</a>                 <a href="ident?i=ip_mc_del_src">ip_mc_del_src</a>(in_dev, &amp;mreqs-&gt;imr_multiaddr, omode, 1,
<a name="L2049" href="source/net/ipv4/igmp.c#L2049">2049</a>                         &amp;mreqs-&gt;imr_sourceaddr, 1);
<a name="L2050" href="source/net/ipv4/igmp.c#L2050">2050</a> 
<a name="L2051" href="source/net/ipv4/igmp.c#L2051">2051</a>                 for (j = <a href="ident?i=i">i</a>+1; j &lt; psl-&gt;sl_count; j++)
<a name="L2052" href="source/net/ipv4/igmp.c#L2052">2052</a>                         psl-&gt;sl_addr[j-1] = psl-&gt;sl_addr[j];
<a name="L2053" href="source/net/ipv4/igmp.c#L2053">2053</a>                 psl-&gt;sl_count--;
<a name="L2054" href="source/net/ipv4/igmp.c#L2054">2054</a>                 <a href="ident?i=err">err</a> = 0;
<a name="L2055" href="source/net/ipv4/igmp.c#L2055">2055</a>                 goto <a href="ident?i=done">done</a>;
<a name="L2056" href="source/net/ipv4/igmp.c#L2056">2056</a>         }
<a name="L2057" href="source/net/ipv4/igmp.c#L2057">2057</a>         <b><i>/* else, add a new source to the filter */</i></b>
<a name="L2058" href="source/net/ipv4/igmp.c#L2058">2058</a> 
<a name="L2059" href="source/net/ipv4/igmp.c#L2059">2059</a>         if (psl &amp;&amp; psl-&gt;sl_count &gt;= <a href="ident?i=sysctl_igmp_max_msf">sysctl_igmp_max_msf</a>) {
<a name="L2060" href="source/net/ipv4/igmp.c#L2060">2060</a>                 <a href="ident?i=err">err</a> = -<a href="ident?i=ENOBUFS">ENOBUFS</a>;
<a name="L2061" href="source/net/ipv4/igmp.c#L2061">2061</a>                 goto <a href="ident?i=done">done</a>;
<a name="L2062" href="source/net/ipv4/igmp.c#L2062">2062</a>         }
<a name="L2063" href="source/net/ipv4/igmp.c#L2063">2063</a>         if (!psl || psl-&gt;sl_count == psl-&gt;sl_max) {
<a name="L2064" href="source/net/ipv4/igmp.c#L2064">2064</a>                 struct <a href="ident?i=ip_sf_socklist">ip_sf_socklist</a> *newpsl;
<a name="L2065" href="source/net/ipv4/igmp.c#L2065">2065</a>                 int <a href="ident?i=count">count</a> = <a href="ident?i=IP_SFBLOCK">IP_SFBLOCK</a>;
<a name="L2066" href="source/net/ipv4/igmp.c#L2066">2066</a> 
<a name="L2067" href="source/net/ipv4/igmp.c#L2067">2067</a>                 if (psl)
<a name="L2068" href="source/net/ipv4/igmp.c#L2068">2068</a>                         <a href="ident?i=count">count</a> += psl-&gt;sl_max;
<a name="L2069" href="source/net/ipv4/igmp.c#L2069">2069</a>                 newpsl = <a href="ident?i=sock_kmalloc">sock_kmalloc</a>(sk, <a href="ident?i=IP_SFLSIZE">IP_SFLSIZE</a>(<a href="ident?i=count">count</a>), <a href="ident?i=GFP_KERNEL">GFP_KERNEL</a>);
<a name="L2070" href="source/net/ipv4/igmp.c#L2070">2070</a>                 if (!newpsl) {
<a name="L2071" href="source/net/ipv4/igmp.c#L2071">2071</a>                         <a href="ident?i=err">err</a> = -<a href="ident?i=ENOBUFS">ENOBUFS</a>;
<a name="L2072" href="source/net/ipv4/igmp.c#L2072">2072</a>                         goto <a href="ident?i=done">done</a>;
<a name="L2073" href="source/net/ipv4/igmp.c#L2073">2073</a>                 }
<a name="L2074" href="source/net/ipv4/igmp.c#L2074">2074</a>                 newpsl-&gt;sl_max = <a href="ident?i=count">count</a>;
<a name="L2075" href="source/net/ipv4/igmp.c#L2075">2075</a>                 newpsl-&gt;sl_count = <a href="ident?i=count">count</a> - <a href="ident?i=IP_SFBLOCK">IP_SFBLOCK</a>;
<a name="L2076" href="source/net/ipv4/igmp.c#L2076">2076</a>                 if (psl) {
<a name="L2077" href="source/net/ipv4/igmp.c#L2077">2077</a>                         for (<a href="ident?i=i">i</a> = 0; <a href="ident?i=i">i</a> &lt; psl-&gt;sl_count; <a href="ident?i=i">i</a>++)
<a name="L2078" href="source/net/ipv4/igmp.c#L2078">2078</a>                                 newpsl-&gt;sl_addr[<a href="ident?i=i">i</a>] = psl-&gt;sl_addr[<a href="ident?i=i">i</a>];
<a name="L2079" href="source/net/ipv4/igmp.c#L2079">2079</a>                         <b><i>/* decrease mem now to avoid the memleak warning */</i></b>
<a name="L2080" href="source/net/ipv4/igmp.c#L2080">2080</a>                         <a href="ident?i=atomic_sub">atomic_sub</a>(<a href="ident?i=IP_SFLSIZE">IP_SFLSIZE</a>(psl-&gt;sl_max), &amp;sk-&gt;sk_omem_alloc);
<a name="L2081" href="source/net/ipv4/igmp.c#L2081">2081</a>                         <a href="ident?i=kfree_rcu">kfree_rcu</a>(psl, rcu);
<a name="L2082" href="source/net/ipv4/igmp.c#L2082">2082</a>                 }
<a name="L2083" href="source/net/ipv4/igmp.c#L2083">2083</a>                 <a href="ident?i=rcu_assign_pointer">rcu_assign_pointer</a>(<a href="ident?i=pmc">pmc</a>-&gt;<a href="ident?i=sflist">sflist</a>, newpsl);
<a name="L2084" href="source/net/ipv4/igmp.c#L2084">2084</a>                 psl = newpsl;
<a name="L2085" href="source/net/ipv4/igmp.c#L2085">2085</a>         }
<a name="L2086" href="source/net/ipv4/igmp.c#L2086">2086</a>         <a href="ident?i=rv">rv</a> = 1; <b><i>/* &gt; 0 for insert logic below if sl_count is 0 */</i></b>
<a name="L2087" href="source/net/ipv4/igmp.c#L2087">2087</a>         for (<a href="ident?i=i">i</a> = 0; <a href="ident?i=i">i</a> &lt; psl-&gt;sl_count; <a href="ident?i=i">i</a>++) {
<a name="L2088" href="source/net/ipv4/igmp.c#L2088">2088</a>                 <a href="ident?i=rv">rv</a> = <a href="ident?i=memcmp">memcmp</a>(&amp;psl-&gt;sl_addr[<a href="ident?i=i">i</a>], &amp;mreqs-&gt;imr_sourceaddr,
<a name="L2089" href="source/net/ipv4/igmp.c#L2089">2089</a>                         sizeof(<a href="ident?i=__be32">__be32</a>));
<a name="L2090" href="source/net/ipv4/igmp.c#L2090">2090</a>                 if (<a href="ident?i=rv">rv</a> == 0)
<a name="L2091" href="source/net/ipv4/igmp.c#L2091">2091</a>                         break;
<a name="L2092" href="source/net/ipv4/igmp.c#L2092">2092</a>         }
<a name="L2093" href="source/net/ipv4/igmp.c#L2093">2093</a>         if (<a href="ident?i=rv">rv</a> == 0)            <b><i>/* address already there is an error */</i></b>
<a name="L2094" href="source/net/ipv4/igmp.c#L2094">2094</a>                 goto <a href="ident?i=done">done</a>;
<a name="L2095" href="source/net/ipv4/igmp.c#L2095">2095</a>         for (j = psl-&gt;sl_count-1; j &gt;= <a href="ident?i=i">i</a>; j--)
<a name="L2096" href="source/net/ipv4/igmp.c#L2096">2096</a>                 psl-&gt;sl_addr[j+1] = psl-&gt;sl_addr[j];
<a name="L2097" href="source/net/ipv4/igmp.c#L2097">2097</a>         psl-&gt;sl_addr[<a href="ident?i=i">i</a>] = mreqs-&gt;imr_sourceaddr;
<a name="L2098" href="source/net/ipv4/igmp.c#L2098">2098</a>         psl-&gt;sl_count++;
<a name="L2099" href="source/net/ipv4/igmp.c#L2099">2099</a>         <a href="ident?i=err">err</a> = 0;
<a name="L2100" href="source/net/ipv4/igmp.c#L2100">2100</a>         <b><i>/* update the interface list */</i></b>
<a name="L2101" href="source/net/ipv4/igmp.c#L2101">2101</a>         <a href="ident?i=ip_mc_add_src">ip_mc_add_src</a>(in_dev, &amp;mreqs-&gt;imr_multiaddr, omode, 1,
<a name="L2102" href="source/net/ipv4/igmp.c#L2102">2102</a>                 &amp;mreqs-&gt;imr_sourceaddr, 1);
<a name="L2103" href="source/net/ipv4/igmp.c#L2103">2103</a> <a href="ident?i=done">done</a>:
<a name="L2104" href="source/net/ipv4/igmp.c#L2104">2104</a>         if (leavegroup)
<a name="L2105" href="source/net/ipv4/igmp.c#L2105">2105</a>                 <a href="ident?i=err">err</a> = <a href="ident?i=ip_mc_leave_group">ip_mc_leave_group</a>(sk, &amp;imr);
<a name="L2106" href="source/net/ipv4/igmp.c#L2106">2106</a>         return <a href="ident?i=err">err</a>;
<a name="L2107" href="source/net/ipv4/igmp.c#L2107">2107</a> }
<a name="L2108" href="source/net/ipv4/igmp.c#L2108">2108</a> 
<a name="L2109" href="source/net/ipv4/igmp.c#L2109">2109</a> int <a href="ident?i=ip_mc_msfilter">ip_mc_msfilter</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=ip_msfilter">ip_msfilter</a> *msf, int ifindex)
<a name="L2110" href="source/net/ipv4/igmp.c#L2110">2110</a> {
<a name="L2111" href="source/net/ipv4/igmp.c#L2111">2111</a>         int <a href="ident?i=err">err</a> = 0;
<a name="L2112" href="source/net/ipv4/igmp.c#L2112">2112</a>         struct <a href="ident?i=ip_mreqn">ip_mreqn</a> imr;
<a name="L2113" href="source/net/ipv4/igmp.c#L2113">2113</a>         <a href="ident?i=__be32">__be32</a> <a href="ident?i=addr">addr</a> = msf-&gt;imsf_multiaddr;
<a name="L2114" href="source/net/ipv4/igmp.c#L2114">2114</a>         struct <a href="ident?i=ip_mc_socklist">ip_mc_socklist</a> *<a href="ident?i=pmc">pmc</a>;
<a name="L2115" href="source/net/ipv4/igmp.c#L2115">2115</a>         struct <a href="ident?i=in_device">in_device</a> *in_dev;
<a name="L2116" href="source/net/ipv4/igmp.c#L2116">2116</a>         struct <a href="ident?i=inet_sock">inet_sock</a> *inet = <a href="ident?i=inet_sk">inet_sk</a>(sk);
<a name="L2117" href="source/net/ipv4/igmp.c#L2117">2117</a>         struct <a href="ident?i=ip_sf_socklist">ip_sf_socklist</a> *newpsl, *psl;
<a name="L2118" href="source/net/ipv4/igmp.c#L2118">2118</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=sock_net">sock_net</a>(sk);
<a name="L2119" href="source/net/ipv4/igmp.c#L2119">2119</a>         int leavegroup = 0;
<a name="L2120" href="source/net/ipv4/igmp.c#L2120">2120</a> 
<a name="L2121" href="source/net/ipv4/igmp.c#L2121">2121</a>         if (!<a href="ident?i=ipv4_is_multicast">ipv4_is_multicast</a>(<a href="ident?i=addr">addr</a>))
<a name="L2122" href="source/net/ipv4/igmp.c#L2122">2122</a>                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L2123" href="source/net/ipv4/igmp.c#L2123">2123</a>         if (msf-&gt;imsf_fmode != <a href="ident?i=MCAST_INCLUDE">MCAST_INCLUDE</a> &amp;&amp;
<a name="L2124" href="source/net/ipv4/igmp.c#L2124">2124</a>             msf-&gt;imsf_fmode != <a href="ident?i=MCAST_EXCLUDE">MCAST_EXCLUDE</a>)
<a name="L2125" href="source/net/ipv4/igmp.c#L2125">2125</a>                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L2126" href="source/net/ipv4/igmp.c#L2126">2126</a> 
<a name="L2127" href="source/net/ipv4/igmp.c#L2127">2127</a>         <a href="ident?i=ASSERT_RTNL">ASSERT_RTNL</a>();
<a name="L2128" href="source/net/ipv4/igmp.c#L2128">2128</a> 
<a name="L2129" href="source/net/ipv4/igmp.c#L2129">2129</a>         imr.imr_multiaddr.s_addr = msf-&gt;imsf_multiaddr;
<a name="L2130" href="source/net/ipv4/igmp.c#L2130">2130</a>         imr.imr_address.s_addr = msf-&gt;imsf_interface;
<a name="L2131" href="source/net/ipv4/igmp.c#L2131">2131</a>         imr.imr_ifindex = ifindex;
<a name="L2132" href="source/net/ipv4/igmp.c#L2132">2132</a>         in_dev = <a href="ident?i=ip_mc_find_dev">ip_mc_find_dev</a>(<a href="ident?i=net">net</a>, &amp;imr);
<a name="L2133" href="source/net/ipv4/igmp.c#L2133">2133</a> 
<a name="L2134" href="source/net/ipv4/igmp.c#L2134">2134</a>         if (!in_dev) {
<a name="L2135" href="source/net/ipv4/igmp.c#L2135">2135</a>                 <a href="ident?i=err">err</a> = -<a href="ident?i=ENODEV">ENODEV</a>;
<a name="L2136" href="source/net/ipv4/igmp.c#L2136">2136</a>                 goto <a href="ident?i=done">done</a>;
<a name="L2137" href="source/net/ipv4/igmp.c#L2137">2137</a>         }
<a name="L2138" href="source/net/ipv4/igmp.c#L2138">2138</a> 
<a name="L2139" href="source/net/ipv4/igmp.c#L2139">2139</a>         <b><i>/* special case - (INCLUDE, empty) == LEAVE_GROUP */</i></b>
<a name="L2140" href="source/net/ipv4/igmp.c#L2140">2140</a>         if (msf-&gt;imsf_fmode == <a href="ident?i=MCAST_INCLUDE">MCAST_INCLUDE</a> &amp;&amp; msf-&gt;imsf_numsrc == 0) {
<a name="L2141" href="source/net/ipv4/igmp.c#L2141">2141</a>                 leavegroup = 1;
<a name="L2142" href="source/net/ipv4/igmp.c#L2142">2142</a>                 goto <a href="ident?i=done">done</a>;
<a name="L2143" href="source/net/ipv4/igmp.c#L2143">2143</a>         }
<a name="L2144" href="source/net/ipv4/igmp.c#L2144">2144</a> 
<a name="L2145" href="source/net/ipv4/igmp.c#L2145">2145</a>         <a href="ident?i=for_each_pmc_rtnl">for_each_pmc_rtnl</a>(inet, <a href="ident?i=pmc">pmc</a>) {
<a name="L2146" href="source/net/ipv4/igmp.c#L2146">2146</a>                 if (<a href="ident?i=pmc">pmc</a>-&gt;<a href="ident?i=multi">multi</a>.imr_multiaddr.s_addr == msf-&gt;imsf_multiaddr &amp;&amp;
<a name="L2147" href="source/net/ipv4/igmp.c#L2147">2147</a>                     <a href="ident?i=pmc">pmc</a>-&gt;<a href="ident?i=multi">multi</a>.imr_ifindex == imr.imr_ifindex)
<a name="L2148" href="source/net/ipv4/igmp.c#L2148">2148</a>                         break;
<a name="L2149" href="source/net/ipv4/igmp.c#L2149">2149</a>         }
<a name="L2150" href="source/net/ipv4/igmp.c#L2150">2150</a>         if (!<a href="ident?i=pmc">pmc</a>) {             <b><i>/* must have a prior join */</i></b>
<a name="L2151" href="source/net/ipv4/igmp.c#L2151">2151</a>                 <a href="ident?i=err">err</a> = -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L2152" href="source/net/ipv4/igmp.c#L2152">2152</a>                 goto <a href="ident?i=done">done</a>;
<a name="L2153" href="source/net/ipv4/igmp.c#L2153">2153</a>         }
<a name="L2154" href="source/net/ipv4/igmp.c#L2154">2154</a>         if (msf-&gt;imsf_numsrc) {
<a name="L2155" href="source/net/ipv4/igmp.c#L2155">2155</a>                 newpsl = <a href="ident?i=sock_kmalloc">sock_kmalloc</a>(sk, <a href="ident?i=IP_SFLSIZE">IP_SFLSIZE</a>(msf-&gt;imsf_numsrc),
<a name="L2156" href="source/net/ipv4/igmp.c#L2156">2156</a>                                                            <a href="ident?i=GFP_KERNEL">GFP_KERNEL</a>);
<a name="L2157" href="source/net/ipv4/igmp.c#L2157">2157</a>                 if (!newpsl) {
<a name="L2158" href="source/net/ipv4/igmp.c#L2158">2158</a>                         <a href="ident?i=err">err</a> = -<a href="ident?i=ENOBUFS">ENOBUFS</a>;
<a name="L2159" href="source/net/ipv4/igmp.c#L2159">2159</a>                         goto <a href="ident?i=done">done</a>;
<a name="L2160" href="source/net/ipv4/igmp.c#L2160">2160</a>                 }
<a name="L2161" href="source/net/ipv4/igmp.c#L2161">2161</a>                 newpsl-&gt;sl_max = newpsl-&gt;sl_count = msf-&gt;imsf_numsrc;
<a name="L2162" href="source/net/ipv4/igmp.c#L2162">2162</a>                 <a href="ident?i=memcpy">memcpy</a>(newpsl-&gt;sl_addr, msf-&gt;imsf_slist,
<a name="L2163" href="source/net/ipv4/igmp.c#L2163">2163</a>                         msf-&gt;imsf_numsrc * sizeof(msf-&gt;imsf_slist[0]));
<a name="L2164" href="source/net/ipv4/igmp.c#L2164">2164</a>                 <a href="ident?i=err">err</a> = <a href="ident?i=ip_mc_add_src">ip_mc_add_src</a>(in_dev, &amp;msf-&gt;imsf_multiaddr,
<a name="L2165" href="source/net/ipv4/igmp.c#L2165">2165</a>                         msf-&gt;imsf_fmode, newpsl-&gt;sl_count, newpsl-&gt;sl_addr, 0);
<a name="L2166" href="source/net/ipv4/igmp.c#L2166">2166</a>                 if (<a href="ident?i=err">err</a>) {
<a name="L2167" href="source/net/ipv4/igmp.c#L2167">2167</a>                         <a href="ident?i=sock_kfree_s">sock_kfree_s</a>(sk, newpsl, <a href="ident?i=IP_SFLSIZE">IP_SFLSIZE</a>(newpsl-&gt;sl_max));
<a name="L2168" href="source/net/ipv4/igmp.c#L2168">2168</a>                         goto <a href="ident?i=done">done</a>;
<a name="L2169" href="source/net/ipv4/igmp.c#L2169">2169</a>                 }
<a name="L2170" href="source/net/ipv4/igmp.c#L2170">2170</a>         } else {
<a name="L2171" href="source/net/ipv4/igmp.c#L2171">2171</a>                 newpsl = <a href="ident?i=NULL">NULL</a>;
<a name="L2172" href="source/net/ipv4/igmp.c#L2172">2172</a>                 (void) <a href="ident?i=ip_mc_add_src">ip_mc_add_src</a>(in_dev, &amp;msf-&gt;imsf_multiaddr,
<a name="L2173" href="source/net/ipv4/igmp.c#L2173">2173</a>                                      msf-&gt;imsf_fmode, 0, <a href="ident?i=NULL">NULL</a>, 0);
<a name="L2174" href="source/net/ipv4/igmp.c#L2174">2174</a>         }
<a name="L2175" href="source/net/ipv4/igmp.c#L2175">2175</a>         psl = <a href="ident?i=rtnl_dereference">rtnl_dereference</a>(<a href="ident?i=pmc">pmc</a>-&gt;<a href="ident?i=sflist">sflist</a>);
<a name="L2176" href="source/net/ipv4/igmp.c#L2176">2176</a>         if (psl) {
<a name="L2177" href="source/net/ipv4/igmp.c#L2177">2177</a>                 (void) <a href="ident?i=ip_mc_del_src">ip_mc_del_src</a>(in_dev, &amp;msf-&gt;imsf_multiaddr, <a href="ident?i=pmc">pmc</a>-&gt;sfmode,
<a name="L2178" href="source/net/ipv4/igmp.c#L2178">2178</a>                         psl-&gt;sl_count, psl-&gt;sl_addr, 0);
<a name="L2179" href="source/net/ipv4/igmp.c#L2179">2179</a>                 <b><i>/* decrease mem now to avoid the memleak warning */</i></b>
<a name="L2180" href="source/net/ipv4/igmp.c#L2180">2180</a>                 <a href="ident?i=atomic_sub">atomic_sub</a>(<a href="ident?i=IP_SFLSIZE">IP_SFLSIZE</a>(psl-&gt;sl_max), &amp;sk-&gt;sk_omem_alloc);
<a name="L2181" href="source/net/ipv4/igmp.c#L2181">2181</a>                 <a href="ident?i=kfree_rcu">kfree_rcu</a>(psl, rcu);
<a name="L2182" href="source/net/ipv4/igmp.c#L2182">2182</a>         } else
<a name="L2183" href="source/net/ipv4/igmp.c#L2183">2183</a>                 (void) <a href="ident?i=ip_mc_del_src">ip_mc_del_src</a>(in_dev, &amp;msf-&gt;imsf_multiaddr, <a href="ident?i=pmc">pmc</a>-&gt;sfmode,
<a name="L2184" href="source/net/ipv4/igmp.c#L2184">2184</a>                         0, <a href="ident?i=NULL">NULL</a>, 0);
<a name="L2185" href="source/net/ipv4/igmp.c#L2185">2185</a>         <a href="ident?i=rcu_assign_pointer">rcu_assign_pointer</a>(<a href="ident?i=pmc">pmc</a>-&gt;<a href="ident?i=sflist">sflist</a>, newpsl);
<a name="L2186" href="source/net/ipv4/igmp.c#L2186">2186</a>         <a href="ident?i=pmc">pmc</a>-&gt;sfmode = msf-&gt;imsf_fmode;
<a name="L2187" href="source/net/ipv4/igmp.c#L2187">2187</a>         <a href="ident?i=err">err</a> = 0;
<a name="L2188" href="source/net/ipv4/igmp.c#L2188">2188</a> <a href="ident?i=done">done</a>:
<a name="L2189" href="source/net/ipv4/igmp.c#L2189">2189</a>         if (leavegroup)
<a name="L2190" href="source/net/ipv4/igmp.c#L2190">2190</a>                 <a href="ident?i=err">err</a> = <a href="ident?i=ip_mc_leave_group">ip_mc_leave_group</a>(sk, &amp;imr);
<a name="L2191" href="source/net/ipv4/igmp.c#L2191">2191</a>         return <a href="ident?i=err">err</a>;
<a name="L2192" href="source/net/ipv4/igmp.c#L2192">2192</a> }
<a name="L2193" href="source/net/ipv4/igmp.c#L2193">2193</a> 
<a name="L2194" href="source/net/ipv4/igmp.c#L2194">2194</a> int <a href="ident?i=ip_mc_msfget">ip_mc_msfget</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=ip_msfilter">ip_msfilter</a> *msf,
<a name="L2195" href="source/net/ipv4/igmp.c#L2195">2195</a>         struct <a href="ident?i=ip_msfilter">ip_msfilter</a> <a href="ident?i=__user">__user</a> *optval, int <a href="ident?i=__user">__user</a> *<a href="ident?i=optlen">optlen</a>)
<a name="L2196" href="source/net/ipv4/igmp.c#L2196">2196</a> {
<a name="L2197" href="source/net/ipv4/igmp.c#L2197">2197</a>         int <a href="ident?i=err">err</a>, <a href="ident?i=len">len</a>, <a href="ident?i=count">count</a>, copycount;
<a name="L2198" href="source/net/ipv4/igmp.c#L2198">2198</a>         struct <a href="ident?i=ip_mreqn">ip_mreqn</a> imr;
<a name="L2199" href="source/net/ipv4/igmp.c#L2199">2199</a>         <a href="ident?i=__be32">__be32</a> <a href="ident?i=addr">addr</a> = msf-&gt;imsf_multiaddr;
<a name="L2200" href="source/net/ipv4/igmp.c#L2200">2200</a>         struct <a href="ident?i=ip_mc_socklist">ip_mc_socklist</a> *<a href="ident?i=pmc">pmc</a>;
<a name="L2201" href="source/net/ipv4/igmp.c#L2201">2201</a>         struct <a href="ident?i=in_device">in_device</a> *in_dev;
<a name="L2202" href="source/net/ipv4/igmp.c#L2202">2202</a>         struct <a href="ident?i=inet_sock">inet_sock</a> *inet = <a href="ident?i=inet_sk">inet_sk</a>(sk);
<a name="L2203" href="source/net/ipv4/igmp.c#L2203">2203</a>         struct <a href="ident?i=ip_sf_socklist">ip_sf_socklist</a> *psl;
<a name="L2204" href="source/net/ipv4/igmp.c#L2204">2204</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=sock_net">sock_net</a>(sk);
<a name="L2205" href="source/net/ipv4/igmp.c#L2205">2205</a> 
<a name="L2206" href="source/net/ipv4/igmp.c#L2206">2206</a>         if (!<a href="ident?i=ipv4_is_multicast">ipv4_is_multicast</a>(<a href="ident?i=addr">addr</a>))
<a name="L2207" href="source/net/ipv4/igmp.c#L2207">2207</a>                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L2208" href="source/net/ipv4/igmp.c#L2208">2208</a> 
<a name="L2209" href="source/net/ipv4/igmp.c#L2209">2209</a>         <a href="ident?i=rtnl_lock">rtnl_lock</a>();
<a name="L2210" href="source/net/ipv4/igmp.c#L2210">2210</a> 
<a name="L2211" href="source/net/ipv4/igmp.c#L2211">2211</a>         imr.imr_multiaddr.s_addr = msf-&gt;imsf_multiaddr;
<a name="L2212" href="source/net/ipv4/igmp.c#L2212">2212</a>         imr.imr_address.s_addr = msf-&gt;imsf_interface;
<a name="L2213" href="source/net/ipv4/igmp.c#L2213">2213</a>         imr.imr_ifindex = 0;
<a name="L2214" href="source/net/ipv4/igmp.c#L2214">2214</a>         in_dev = <a href="ident?i=ip_mc_find_dev">ip_mc_find_dev</a>(<a href="ident?i=net">net</a>, &amp;imr);
<a name="L2215" href="source/net/ipv4/igmp.c#L2215">2215</a> 
<a name="L2216" href="source/net/ipv4/igmp.c#L2216">2216</a>         if (!in_dev) {
<a name="L2217" href="source/net/ipv4/igmp.c#L2217">2217</a>                 <a href="ident?i=err">err</a> = -<a href="ident?i=ENODEV">ENODEV</a>;
<a name="L2218" href="source/net/ipv4/igmp.c#L2218">2218</a>                 goto <a href="ident?i=done">done</a>;
<a name="L2219" href="source/net/ipv4/igmp.c#L2219">2219</a>         }
<a name="L2220" href="source/net/ipv4/igmp.c#L2220">2220</a>         <a href="ident?i=err">err</a> = -<a href="ident?i=EADDRNOTAVAIL">EADDRNOTAVAIL</a>;
<a name="L2221" href="source/net/ipv4/igmp.c#L2221">2221</a> 
<a name="L2222" href="source/net/ipv4/igmp.c#L2222">2222</a>         <a href="ident?i=for_each_pmc_rtnl">for_each_pmc_rtnl</a>(inet, <a href="ident?i=pmc">pmc</a>) {
<a name="L2223" href="source/net/ipv4/igmp.c#L2223">2223</a>                 if (<a href="ident?i=pmc">pmc</a>-&gt;<a href="ident?i=multi">multi</a>.imr_multiaddr.s_addr == msf-&gt;imsf_multiaddr &amp;&amp;
<a name="L2224" href="source/net/ipv4/igmp.c#L2224">2224</a>                     <a href="ident?i=pmc">pmc</a>-&gt;<a href="ident?i=multi">multi</a>.imr_ifindex == imr.imr_ifindex)
<a name="L2225" href="source/net/ipv4/igmp.c#L2225">2225</a>                         break;
<a name="L2226" href="source/net/ipv4/igmp.c#L2226">2226</a>         }
<a name="L2227" href="source/net/ipv4/igmp.c#L2227">2227</a>         if (!<a href="ident?i=pmc">pmc</a>)               <b><i>/* must have a prior join */</i></b>
<a name="L2228" href="source/net/ipv4/igmp.c#L2228">2228</a>                 goto <a href="ident?i=done">done</a>;
<a name="L2229" href="source/net/ipv4/igmp.c#L2229">2229</a>         msf-&gt;imsf_fmode = <a href="ident?i=pmc">pmc</a>-&gt;sfmode;
<a name="L2230" href="source/net/ipv4/igmp.c#L2230">2230</a>         psl = <a href="ident?i=rtnl_dereference">rtnl_dereference</a>(<a href="ident?i=pmc">pmc</a>-&gt;<a href="ident?i=sflist">sflist</a>);
<a name="L2231" href="source/net/ipv4/igmp.c#L2231">2231</a>         <a href="ident?i=rtnl_unlock">rtnl_unlock</a>();
<a name="L2232" href="source/net/ipv4/igmp.c#L2232">2232</a>         if (!psl) {
<a name="L2233" href="source/net/ipv4/igmp.c#L2233">2233</a>                 <a href="ident?i=len">len</a> = 0;
<a name="L2234" href="source/net/ipv4/igmp.c#L2234">2234</a>                 <a href="ident?i=count">count</a> = 0;
<a name="L2235" href="source/net/ipv4/igmp.c#L2235">2235</a>         } else {
<a name="L2236" href="source/net/ipv4/igmp.c#L2236">2236</a>                 <a href="ident?i=count">count</a> = psl-&gt;sl_count;
<a name="L2237" href="source/net/ipv4/igmp.c#L2237">2237</a>         }
<a name="L2238" href="source/net/ipv4/igmp.c#L2238">2238</a>         copycount = <a href="ident?i=count">count</a> &lt; msf-&gt;imsf_numsrc ? <a href="ident?i=count">count</a> : msf-&gt;imsf_numsrc;
<a name="L2239" href="source/net/ipv4/igmp.c#L2239">2239</a>         <a href="ident?i=len">len</a> = copycount * sizeof(psl-&gt;sl_addr[0]);
<a name="L2240" href="source/net/ipv4/igmp.c#L2240">2240</a>         msf-&gt;imsf_numsrc = <a href="ident?i=count">count</a>;
<a name="L2241" href="source/net/ipv4/igmp.c#L2241">2241</a>         if (<a href="ident?i=put_user">put_user</a>(<a href="ident?i=IP_MSFILTER_SIZE">IP_MSFILTER_SIZE</a>(copycount), <a href="ident?i=optlen">optlen</a>) ||
<a name="L2242" href="source/net/ipv4/igmp.c#L2242">2242</a>             <a href="ident?i=copy_to_user">copy_to_user</a>(optval, msf, <a href="ident?i=IP_MSFILTER_SIZE">IP_MSFILTER_SIZE</a>(0))) {
<a name="L2243" href="source/net/ipv4/igmp.c#L2243">2243</a>                 return -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L2244" href="source/net/ipv4/igmp.c#L2244">2244</a>         }
<a name="L2245" href="source/net/ipv4/igmp.c#L2245">2245</a>         if (<a href="ident?i=len">len</a> &amp;&amp;
<a name="L2246" href="source/net/ipv4/igmp.c#L2246">2246</a>             <a href="ident?i=copy_to_user">copy_to_user</a>(&amp;optval-&gt;imsf_slist[0], psl-&gt;sl_addr, <a href="ident?i=len">len</a>))
<a name="L2247" href="source/net/ipv4/igmp.c#L2247">2247</a>                 return -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L2248" href="source/net/ipv4/igmp.c#L2248">2248</a>         return 0;
<a name="L2249" href="source/net/ipv4/igmp.c#L2249">2249</a> <a href="ident?i=done">done</a>:
<a name="L2250" href="source/net/ipv4/igmp.c#L2250">2250</a>         <a href="ident?i=rtnl_unlock">rtnl_unlock</a>();
<a name="L2251" href="source/net/ipv4/igmp.c#L2251">2251</a>         return <a href="ident?i=err">err</a>;
<a name="L2252" href="source/net/ipv4/igmp.c#L2252">2252</a> }
<a name="L2253" href="source/net/ipv4/igmp.c#L2253">2253</a> 
<a name="L2254" href="source/net/ipv4/igmp.c#L2254">2254</a> int <a href="ident?i=ip_mc_gsfget">ip_mc_gsfget</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=group_filter">group_filter</a> *gsf,
<a name="L2255" href="source/net/ipv4/igmp.c#L2255">2255</a>         struct <a href="ident?i=group_filter">group_filter</a> <a href="ident?i=__user">__user</a> *optval, int <a href="ident?i=__user">__user</a> *<a href="ident?i=optlen">optlen</a>)
<a name="L2256" href="source/net/ipv4/igmp.c#L2256">2256</a> {
<a name="L2257" href="source/net/ipv4/igmp.c#L2257">2257</a>         int <a href="ident?i=err">err</a>, <a href="ident?i=i">i</a>, <a href="ident?i=count">count</a>, copycount;
<a name="L2258" href="source/net/ipv4/igmp.c#L2258">2258</a>         struct <a href="ident?i=sockaddr_in">sockaddr_in</a> *psin;
<a name="L2259" href="source/net/ipv4/igmp.c#L2259">2259</a>         <a href="ident?i=__be32">__be32</a> <a href="ident?i=addr">addr</a>;
<a name="L2260" href="source/net/ipv4/igmp.c#L2260">2260</a>         struct <a href="ident?i=ip_mc_socklist">ip_mc_socklist</a> *<a href="ident?i=pmc">pmc</a>;
<a name="L2261" href="source/net/ipv4/igmp.c#L2261">2261</a>         struct <a href="ident?i=inet_sock">inet_sock</a> *inet = <a href="ident?i=inet_sk">inet_sk</a>(sk);
<a name="L2262" href="source/net/ipv4/igmp.c#L2262">2262</a>         struct <a href="ident?i=ip_sf_socklist">ip_sf_socklist</a> *psl;
<a name="L2263" href="source/net/ipv4/igmp.c#L2263">2263</a> 
<a name="L2264" href="source/net/ipv4/igmp.c#L2264">2264</a>         psin = (struct <a href="ident?i=sockaddr_in">sockaddr_in</a> *)&amp;gsf-&gt;gf_group;
<a name="L2265" href="source/net/ipv4/igmp.c#L2265">2265</a>         if (psin-&gt;sin_family != <a href="ident?i=AF_INET">AF_INET</a>)
<a name="L2266" href="source/net/ipv4/igmp.c#L2266">2266</a>                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L2267" href="source/net/ipv4/igmp.c#L2267">2267</a>         <a href="ident?i=addr">addr</a> = psin-&gt;sin_addr.s_addr;
<a name="L2268" href="source/net/ipv4/igmp.c#L2268">2268</a>         if (!<a href="ident?i=ipv4_is_multicast">ipv4_is_multicast</a>(<a href="ident?i=addr">addr</a>))
<a name="L2269" href="source/net/ipv4/igmp.c#L2269">2269</a>                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L2270" href="source/net/ipv4/igmp.c#L2270">2270</a> 
<a name="L2271" href="source/net/ipv4/igmp.c#L2271">2271</a>         <a href="ident?i=rtnl_lock">rtnl_lock</a>();
<a name="L2272" href="source/net/ipv4/igmp.c#L2272">2272</a> 
<a name="L2273" href="source/net/ipv4/igmp.c#L2273">2273</a>         <a href="ident?i=err">err</a> = -<a href="ident?i=EADDRNOTAVAIL">EADDRNOTAVAIL</a>;
<a name="L2274" href="source/net/ipv4/igmp.c#L2274">2274</a> 
<a name="L2275" href="source/net/ipv4/igmp.c#L2275">2275</a>         <a href="ident?i=for_each_pmc_rtnl">for_each_pmc_rtnl</a>(inet, <a href="ident?i=pmc">pmc</a>) {
<a name="L2276" href="source/net/ipv4/igmp.c#L2276">2276</a>                 if (<a href="ident?i=pmc">pmc</a>-&gt;<a href="ident?i=multi">multi</a>.imr_multiaddr.s_addr == <a href="ident?i=addr">addr</a> &amp;&amp;
<a name="L2277" href="source/net/ipv4/igmp.c#L2277">2277</a>                     <a href="ident?i=pmc">pmc</a>-&gt;<a href="ident?i=multi">multi</a>.imr_ifindex == gsf-&gt;gf_interface)
<a name="L2278" href="source/net/ipv4/igmp.c#L2278">2278</a>                         break;
<a name="L2279" href="source/net/ipv4/igmp.c#L2279">2279</a>         }
<a name="L2280" href="source/net/ipv4/igmp.c#L2280">2280</a>         if (!<a href="ident?i=pmc">pmc</a>)               <b><i>/* must have a prior join */</i></b>
<a name="L2281" href="source/net/ipv4/igmp.c#L2281">2281</a>                 goto <a href="ident?i=done">done</a>;
<a name="L2282" href="source/net/ipv4/igmp.c#L2282">2282</a>         gsf-&gt;gf_fmode = <a href="ident?i=pmc">pmc</a>-&gt;sfmode;
<a name="L2283" href="source/net/ipv4/igmp.c#L2283">2283</a>         psl = <a href="ident?i=rtnl_dereference">rtnl_dereference</a>(<a href="ident?i=pmc">pmc</a>-&gt;<a href="ident?i=sflist">sflist</a>);
<a name="L2284" href="source/net/ipv4/igmp.c#L2284">2284</a>         <a href="ident?i=rtnl_unlock">rtnl_unlock</a>();
<a name="L2285" href="source/net/ipv4/igmp.c#L2285">2285</a>         <a href="ident?i=count">count</a> = psl ? psl-&gt;sl_count : 0;
<a name="L2286" href="source/net/ipv4/igmp.c#L2286">2286</a>         copycount = <a href="ident?i=count">count</a> &lt; gsf-&gt;gf_numsrc ? <a href="ident?i=count">count</a> : gsf-&gt;gf_numsrc;
<a name="L2287" href="source/net/ipv4/igmp.c#L2287">2287</a>         gsf-&gt;gf_numsrc = <a href="ident?i=count">count</a>;
<a name="L2288" href="source/net/ipv4/igmp.c#L2288">2288</a>         if (<a href="ident?i=put_user">put_user</a>(<a href="ident?i=GROUP_FILTER_SIZE">GROUP_FILTER_SIZE</a>(copycount), <a href="ident?i=optlen">optlen</a>) ||
<a name="L2289" href="source/net/ipv4/igmp.c#L2289">2289</a>             <a href="ident?i=copy_to_user">copy_to_user</a>(optval, gsf, <a href="ident?i=GROUP_FILTER_SIZE">GROUP_FILTER_SIZE</a>(0))) {
<a name="L2290" href="source/net/ipv4/igmp.c#L2290">2290</a>                 return -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L2291" href="source/net/ipv4/igmp.c#L2291">2291</a>         }
<a name="L2292" href="source/net/ipv4/igmp.c#L2292">2292</a>         for (<a href="ident?i=i">i</a> = 0; <a href="ident?i=i">i</a> &lt; copycount; <a href="ident?i=i">i</a>++) {
<a name="L2293" href="source/net/ipv4/igmp.c#L2293">2293</a>                 struct <a href="ident?i=sockaddr_storage">sockaddr_storage</a> ss;
<a name="L2294" href="source/net/ipv4/igmp.c#L2294">2294</a> 
<a name="L2295" href="source/net/ipv4/igmp.c#L2295">2295</a>                 psin = (struct <a href="ident?i=sockaddr_in">sockaddr_in</a> *)&amp;ss;
<a name="L2296" href="source/net/ipv4/igmp.c#L2296">2296</a>                 <a href="ident?i=memset">memset</a>(&amp;ss, 0, sizeof(ss));
<a name="L2297" href="source/net/ipv4/igmp.c#L2297">2297</a>                 psin-&gt;sin_family = <a href="ident?i=AF_INET">AF_INET</a>;
<a name="L2298" href="source/net/ipv4/igmp.c#L2298">2298</a>                 psin-&gt;sin_addr.s_addr = psl-&gt;sl_addr[<a href="ident?i=i">i</a>];
<a name="L2299" href="source/net/ipv4/igmp.c#L2299">2299</a>                 if (<a href="ident?i=copy_to_user">copy_to_user</a>(&amp;optval-&gt;gf_slist[<a href="ident?i=i">i</a>], &amp;ss, sizeof(ss)))
<a name="L2300" href="source/net/ipv4/igmp.c#L2300">2300</a>                         return -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L2301" href="source/net/ipv4/igmp.c#L2301">2301</a>         }
<a name="L2302" href="source/net/ipv4/igmp.c#L2302">2302</a>         return 0;
<a name="L2303" href="source/net/ipv4/igmp.c#L2303">2303</a> <a href="ident?i=done">done</a>:
<a name="L2304" href="source/net/ipv4/igmp.c#L2304">2304</a>         <a href="ident?i=rtnl_unlock">rtnl_unlock</a>();
<a name="L2305" href="source/net/ipv4/igmp.c#L2305">2305</a>         return <a href="ident?i=err">err</a>;
<a name="L2306" href="source/net/ipv4/igmp.c#L2306">2306</a> }
<a name="L2307" href="source/net/ipv4/igmp.c#L2307">2307</a> 
<a name="L2308" href="source/net/ipv4/igmp.c#L2308">2308</a> <b><i>/*</i></b>
<a name="L2309" href="source/net/ipv4/igmp.c#L2309">2309</a> <b><i> * check if a multicast source filter allows delivery for a given &lt;src,dst,intf&gt;</i></b>
<a name="L2310" href="source/net/ipv4/igmp.c#L2310">2310</a> <b><i> */</i></b>
<a name="L2311" href="source/net/ipv4/igmp.c#L2311">2311</a> int <a href="ident?i=ip_mc_sf_allow">ip_mc_sf_allow</a>(struct <a href="ident?i=sock">sock</a> *sk, <a href="ident?i=__be32">__be32</a> loc_addr, <a href="ident?i=__be32">__be32</a> rmt_addr, int dif)
<a name="L2312" href="source/net/ipv4/igmp.c#L2312">2312</a> {
<a name="L2313" href="source/net/ipv4/igmp.c#L2313">2313</a>         struct <a href="ident?i=inet_sock">inet_sock</a> *inet = <a href="ident?i=inet_sk">inet_sk</a>(sk);
<a name="L2314" href="source/net/ipv4/igmp.c#L2314">2314</a>         struct <a href="ident?i=ip_mc_socklist">ip_mc_socklist</a> *<a href="ident?i=pmc">pmc</a>;
<a name="L2315" href="source/net/ipv4/igmp.c#L2315">2315</a>         struct <a href="ident?i=ip_sf_socklist">ip_sf_socklist</a> *psl;
<a name="L2316" href="source/net/ipv4/igmp.c#L2316">2316</a>         int <a href="ident?i=i">i</a>;
<a name="L2317" href="source/net/ipv4/igmp.c#L2317">2317</a>         int <a href="ident?i=ret">ret</a>;
<a name="L2318" href="source/net/ipv4/igmp.c#L2318">2318</a> 
<a name="L2319" href="source/net/ipv4/igmp.c#L2319">2319</a>         <a href="ident?i=ret">ret</a> = 1;
<a name="L2320" href="source/net/ipv4/igmp.c#L2320">2320</a>         if (!<a href="ident?i=ipv4_is_multicast">ipv4_is_multicast</a>(loc_addr))
<a name="L2321" href="source/net/ipv4/igmp.c#L2321">2321</a>                 goto <a href="ident?i=out">out</a>;
<a name="L2322" href="source/net/ipv4/igmp.c#L2322">2322</a> 
<a name="L2323" href="source/net/ipv4/igmp.c#L2323">2323</a>         <a href="ident?i=rcu_read_lock">rcu_read_lock</a>();
<a name="L2324" href="source/net/ipv4/igmp.c#L2324">2324</a>         <a href="ident?i=for_each_pmc_rcu">for_each_pmc_rcu</a>(inet, <a href="ident?i=pmc">pmc</a>) {
<a name="L2325" href="source/net/ipv4/igmp.c#L2325">2325</a>                 if (<a href="ident?i=pmc">pmc</a>-&gt;<a href="ident?i=multi">multi</a>.imr_multiaddr.s_addr == loc_addr &amp;&amp;
<a name="L2326" href="source/net/ipv4/igmp.c#L2326">2326</a>                     <a href="ident?i=pmc">pmc</a>-&gt;<a href="ident?i=multi">multi</a>.imr_ifindex == dif)
<a name="L2327" href="source/net/ipv4/igmp.c#L2327">2327</a>                         break;
<a name="L2328" href="source/net/ipv4/igmp.c#L2328">2328</a>         }
<a name="L2329" href="source/net/ipv4/igmp.c#L2329">2329</a>         <a href="ident?i=ret">ret</a> = inet-&gt;mc_all;
<a name="L2330" href="source/net/ipv4/igmp.c#L2330">2330</a>         if (!<a href="ident?i=pmc">pmc</a>)
<a name="L2331" href="source/net/ipv4/igmp.c#L2331">2331</a>                 goto unlock;
<a name="L2332" href="source/net/ipv4/igmp.c#L2332">2332</a>         psl = <a href="ident?i=rcu_dereference">rcu_dereference</a>(<a href="ident?i=pmc">pmc</a>-&gt;<a href="ident?i=sflist">sflist</a>);
<a name="L2333" href="source/net/ipv4/igmp.c#L2333">2333</a>         <a href="ident?i=ret">ret</a> = (<a href="ident?i=pmc">pmc</a>-&gt;sfmode == <a href="ident?i=MCAST_EXCLUDE">MCAST_EXCLUDE</a>);
<a name="L2334" href="source/net/ipv4/igmp.c#L2334">2334</a>         if (!psl)
<a name="L2335" href="source/net/ipv4/igmp.c#L2335">2335</a>                 goto unlock;
<a name="L2336" href="source/net/ipv4/igmp.c#L2336">2336</a> 
<a name="L2337" href="source/net/ipv4/igmp.c#L2337">2337</a>         for (<a href="ident?i=i">i</a> = 0; <a href="ident?i=i">i</a> &lt; psl-&gt;sl_count; <a href="ident?i=i">i</a>++) {
<a name="L2338" href="source/net/ipv4/igmp.c#L2338">2338</a>                 if (psl-&gt;sl_addr[<a href="ident?i=i">i</a>] == rmt_addr)
<a name="L2339" href="source/net/ipv4/igmp.c#L2339">2339</a>                         break;
<a name="L2340" href="source/net/ipv4/igmp.c#L2340">2340</a>         }
<a name="L2341" href="source/net/ipv4/igmp.c#L2341">2341</a>         <a href="ident?i=ret">ret</a> = 0;
<a name="L2342" href="source/net/ipv4/igmp.c#L2342">2342</a>         if (<a href="ident?i=pmc">pmc</a>-&gt;sfmode == <a href="ident?i=MCAST_INCLUDE">MCAST_INCLUDE</a> &amp;&amp; <a href="ident?i=i">i</a> &gt;= psl-&gt;sl_count)
<a name="L2343" href="source/net/ipv4/igmp.c#L2343">2343</a>                 goto unlock;
<a name="L2344" href="source/net/ipv4/igmp.c#L2344">2344</a>         if (<a href="ident?i=pmc">pmc</a>-&gt;sfmode == <a href="ident?i=MCAST_EXCLUDE">MCAST_EXCLUDE</a> &amp;&amp; <a href="ident?i=i">i</a> &lt; psl-&gt;sl_count)
<a name="L2345" href="source/net/ipv4/igmp.c#L2345">2345</a>                 goto unlock;
<a name="L2346" href="source/net/ipv4/igmp.c#L2346">2346</a>         <a href="ident?i=ret">ret</a> = 1;
<a name="L2347" href="source/net/ipv4/igmp.c#L2347">2347</a> unlock:
<a name="L2348" href="source/net/ipv4/igmp.c#L2348">2348</a>         <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L2349" href="source/net/ipv4/igmp.c#L2349">2349</a> <a href="ident?i=out">out</a>:
<a name="L2350" href="source/net/ipv4/igmp.c#L2350">2350</a>         return <a href="ident?i=ret">ret</a>;
<a name="L2351" href="source/net/ipv4/igmp.c#L2351">2351</a> }
<a name="L2352" href="source/net/ipv4/igmp.c#L2352">2352</a> 
<a name="L2353" href="source/net/ipv4/igmp.c#L2353">2353</a> <b><i>/*</i></b>
<a name="L2354" href="source/net/ipv4/igmp.c#L2354">2354</a> <b><i> *      A socket is closing.</i></b>
<a name="L2355" href="source/net/ipv4/igmp.c#L2355">2355</a> <b><i> */</i></b>
<a name="L2356" href="source/net/ipv4/igmp.c#L2356">2356</a> 
<a name="L2357" href="source/net/ipv4/igmp.c#L2357">2357</a> void <a href="ident?i=ip_mc_drop_socket">ip_mc_drop_socket</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L2358" href="source/net/ipv4/igmp.c#L2358">2358</a> {
<a name="L2359" href="source/net/ipv4/igmp.c#L2359">2359</a>         struct <a href="ident?i=inet_sock">inet_sock</a> *inet = <a href="ident?i=inet_sk">inet_sk</a>(sk);
<a name="L2360" href="source/net/ipv4/igmp.c#L2360">2360</a>         struct <a href="ident?i=ip_mc_socklist">ip_mc_socklist</a> *iml;
<a name="L2361" href="source/net/ipv4/igmp.c#L2361">2361</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=sock_net">sock_net</a>(sk);
<a name="L2362" href="source/net/ipv4/igmp.c#L2362">2362</a> 
<a name="L2363" href="source/net/ipv4/igmp.c#L2363">2363</a>         if (!inet-&gt;mc_list)
<a name="L2364" href="source/net/ipv4/igmp.c#L2364">2364</a>                 return;
<a name="L2365" href="source/net/ipv4/igmp.c#L2365">2365</a> 
<a name="L2366" href="source/net/ipv4/igmp.c#L2366">2366</a>         <a href="ident?i=rtnl_lock">rtnl_lock</a>();
<a name="L2367" href="source/net/ipv4/igmp.c#L2367">2367</a>         while ((iml = <a href="ident?i=rtnl_dereference">rtnl_dereference</a>(inet-&gt;mc_list)) != <a href="ident?i=NULL">NULL</a>) {
<a name="L2368" href="source/net/ipv4/igmp.c#L2368">2368</a>                 struct <a href="ident?i=in_device">in_device</a> *in_dev;
<a name="L2369" href="source/net/ipv4/igmp.c#L2369">2369</a> 
<a name="L2370" href="source/net/ipv4/igmp.c#L2370">2370</a>                 inet-&gt;mc_list = iml-&gt;next_rcu;
<a name="L2371" href="source/net/ipv4/igmp.c#L2371">2371</a>                 in_dev = <a href="ident?i=inetdev_by_index">inetdev_by_index</a>(<a href="ident?i=net">net</a>, iml-&gt;<a href="ident?i=multi">multi</a>.imr_ifindex);
<a name="L2372" href="source/net/ipv4/igmp.c#L2372">2372</a>                 (void) <a href="ident?i=ip_mc_leave_src">ip_mc_leave_src</a>(sk, iml, in_dev);
<a name="L2373" href="source/net/ipv4/igmp.c#L2373">2373</a>                 if (in_dev)
<a name="L2374" href="source/net/ipv4/igmp.c#L2374">2374</a>                         <a href="ident?i=ip_mc_dec_group">ip_mc_dec_group</a>(in_dev, iml-&gt;<a href="ident?i=multi">multi</a>.imr_multiaddr.s_addr);
<a name="L2375" href="source/net/ipv4/igmp.c#L2375">2375</a>                 <b><i>/* decrease mem now to avoid the memleak warning */</i></b>
<a name="L2376" href="source/net/ipv4/igmp.c#L2376">2376</a>                 <a href="ident?i=atomic_sub">atomic_sub</a>(sizeof(*iml), &amp;sk-&gt;sk_omem_alloc);
<a name="L2377" href="source/net/ipv4/igmp.c#L2377">2377</a>                 <a href="ident?i=kfree_rcu">kfree_rcu</a>(iml, rcu);
<a name="L2378" href="source/net/ipv4/igmp.c#L2378">2378</a>         }
<a name="L2379" href="source/net/ipv4/igmp.c#L2379">2379</a>         <a href="ident?i=rtnl_unlock">rtnl_unlock</a>();
<a name="L2380" href="source/net/ipv4/igmp.c#L2380">2380</a> }
<a name="L2381" href="source/net/ipv4/igmp.c#L2381">2381</a> 
<a name="L2382" href="source/net/ipv4/igmp.c#L2382">2382</a> <b><i>/* called with rcu_read_lock() */</i></b>
<a name="L2383" href="source/net/ipv4/igmp.c#L2383">2383</a> int <a href="ident?i=ip_check_mc_rcu">ip_check_mc_rcu</a>(struct <a href="ident?i=in_device">in_device</a> *in_dev, <a href="ident?i=__be32">__be32</a> mc_addr, <a href="ident?i=__be32">__be32</a> src_addr, <a href="ident?i=u16">u16</a> <a href="ident?i=proto">proto</a>)
<a name="L2384" href="source/net/ipv4/igmp.c#L2384">2384</a> {
<a name="L2385" href="source/net/ipv4/igmp.c#L2385">2385</a>         struct <a href="ident?i=ip_mc_list">ip_mc_list</a> *im;
<a name="L2386" href="source/net/ipv4/igmp.c#L2386">2386</a>         struct <a href="ident?i=ip_mc_list">ip_mc_list</a> <a href="ident?i=__rcu">__rcu</a> **<a href="ident?i=mc_hash">mc_hash</a>;
<a name="L2387" href="source/net/ipv4/igmp.c#L2387">2387</a>         struct <a href="ident?i=ip_sf_list">ip_sf_list</a> *psf;
<a name="L2388" href="source/net/ipv4/igmp.c#L2388">2388</a>         int <a href="ident?i=rv">rv</a> = 0;
<a name="L2389" href="source/net/ipv4/igmp.c#L2389">2389</a> 
<a name="L2390" href="source/net/ipv4/igmp.c#L2390">2390</a>         <a href="ident?i=mc_hash">mc_hash</a> = <a href="ident?i=rcu_dereference">rcu_dereference</a>(in_dev-&gt;<a href="ident?i=mc_hash">mc_hash</a>);
<a name="L2391" href="source/net/ipv4/igmp.c#L2391">2391</a>         if (<a href="ident?i=mc_hash">mc_hash</a>) {
<a name="L2392" href="source/net/ipv4/igmp.c#L2392">2392</a>                 <a href="ident?i=u32">u32</a> <a href="ident?i=hash">hash</a> = <a href="ident?i=hash_32">hash_32</a>((<a href="ident?i=__force">__force</a> <a href="ident?i=u32">u32</a>)mc_addr, <a href="ident?i=MC_HASH_SZ_LOG">MC_HASH_SZ_LOG</a>);
<a name="L2393" href="source/net/ipv4/igmp.c#L2393">2393</a> 
<a name="L2394" href="source/net/ipv4/igmp.c#L2394">2394</a>                 for (im = <a href="ident?i=rcu_dereference">rcu_dereference</a>(<a href="ident?i=mc_hash">mc_hash</a>[<a href="ident?i=hash">hash</a>]);
<a name="L2395" href="source/net/ipv4/igmp.c#L2395">2395</a>                      im != <a href="ident?i=NULL">NULL</a>;
<a name="L2396" href="source/net/ipv4/igmp.c#L2396">2396</a>                      im = <a href="ident?i=rcu_dereference">rcu_dereference</a>(im-&gt;next_hash)) {
<a name="L2397" href="source/net/ipv4/igmp.c#L2397">2397</a>                         if (im-&gt;multiaddr == mc_addr)
<a name="L2398" href="source/net/ipv4/igmp.c#L2398">2398</a>                                 break;
<a name="L2399" href="source/net/ipv4/igmp.c#L2399">2399</a>                 }
<a name="L2400" href="source/net/ipv4/igmp.c#L2400">2400</a>         } else {
<a name="L2401" href="source/net/ipv4/igmp.c#L2401">2401</a>                 <a href="ident?i=for_each_pmc_rcu">for_each_pmc_rcu</a>(in_dev, im) {
<a name="L2402" href="source/net/ipv4/igmp.c#L2402">2402</a>                         if (im-&gt;multiaddr == mc_addr)
<a name="L2403" href="source/net/ipv4/igmp.c#L2403">2403</a>                                 break;
<a name="L2404" href="source/net/ipv4/igmp.c#L2404">2404</a>                 }
<a name="L2405" href="source/net/ipv4/igmp.c#L2405">2405</a>         }
<a name="L2406" href="source/net/ipv4/igmp.c#L2406">2406</a>         if (im &amp;&amp; <a href="ident?i=proto">proto</a> == <a href="ident?i=IPPROTO_IGMP">IPPROTO_IGMP</a>) {
<a name="L2407" href="source/net/ipv4/igmp.c#L2407">2407</a>                 <a href="ident?i=rv">rv</a> = 1;
<a name="L2408" href="source/net/ipv4/igmp.c#L2408">2408</a>         } else if (im) {
<a name="L2409" href="source/net/ipv4/igmp.c#L2409">2409</a>                 if (src_addr) {
<a name="L2410" href="source/net/ipv4/igmp.c#L2410">2410</a>                         for (psf = im-&gt;sources; psf; psf = psf-&gt;sf_next) {
<a name="L2411" href="source/net/ipv4/igmp.c#L2411">2411</a>                                 if (psf-&gt;sf_inaddr == src_addr)
<a name="L2412" href="source/net/ipv4/igmp.c#L2412">2412</a>                                         break;
<a name="L2413" href="source/net/ipv4/igmp.c#L2413">2413</a>                         }
<a name="L2414" href="source/net/ipv4/igmp.c#L2414">2414</a>                         if (psf)
<a name="L2415" href="source/net/ipv4/igmp.c#L2415">2415</a>                                 <a href="ident?i=rv">rv</a> = psf-&gt;sf_count[<a href="ident?i=MCAST_INCLUDE">MCAST_INCLUDE</a>] ||
<a name="L2416" href="source/net/ipv4/igmp.c#L2416">2416</a>                                         psf-&gt;sf_count[<a href="ident?i=MCAST_EXCLUDE">MCAST_EXCLUDE</a>] !=
<a name="L2417" href="source/net/ipv4/igmp.c#L2417">2417</a>                                         im-&gt;sfcount[<a href="ident?i=MCAST_EXCLUDE">MCAST_EXCLUDE</a>];
<a name="L2418" href="source/net/ipv4/igmp.c#L2418">2418</a>                         else
<a name="L2419" href="source/net/ipv4/igmp.c#L2419">2419</a>                                 <a href="ident?i=rv">rv</a> = im-&gt;sfcount[<a href="ident?i=MCAST_EXCLUDE">MCAST_EXCLUDE</a>] != 0;
<a name="L2420" href="source/net/ipv4/igmp.c#L2420">2420</a>                 } else
<a name="L2421" href="source/net/ipv4/igmp.c#L2421">2421</a>                         <a href="ident?i=rv">rv</a> = 1; <b><i>/* unspecified source; tentatively allow */</i></b>
<a name="L2422" href="source/net/ipv4/igmp.c#L2422">2422</a>         }
<a name="L2423" href="source/net/ipv4/igmp.c#L2423">2423</a>         return <a href="ident?i=rv">rv</a>;
<a name="L2424" href="source/net/ipv4/igmp.c#L2424">2424</a> }
<a name="L2425" href="source/net/ipv4/igmp.c#L2425">2425</a> 
<a name="L2426" href="source/net/ipv4/igmp.c#L2426">2426</a> #if defined(CONFIG_PROC_FS)
<a name="L2427" href="source/net/ipv4/igmp.c#L2427">2427</a> struct <a href="ident?i=igmp_mc_iter_state">igmp_mc_iter_state</a> {
<a name="L2428" href="source/net/ipv4/igmp.c#L2428">2428</a>         struct <a href="ident?i=seq_net_private">seq_net_private</a> <a href="ident?i=p">p</a>;
<a name="L2429" href="source/net/ipv4/igmp.c#L2429">2429</a>         struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>;
<a name="L2430" href="source/net/ipv4/igmp.c#L2430">2430</a>         struct <a href="ident?i=in_device">in_device</a> *in_dev;
<a name="L2431" href="source/net/ipv4/igmp.c#L2431">2431</a> };
<a name="L2432" href="source/net/ipv4/igmp.c#L2432">2432</a> 
<a name="L2433" href="source/net/ipv4/igmp.c#L2433">2433</a> #define <a href="ident?i=igmp_mc_seq_private">igmp_mc_seq_private</a>(<a href="ident?i=seq">seq</a>)        ((struct <a href="ident?i=igmp_mc_iter_state">igmp_mc_iter_state</a> *)(<a href="ident?i=seq">seq</a>)-&gt;<a href="ident?i=private">private</a>)
<a name="L2434" href="source/net/ipv4/igmp.c#L2434">2434</a> 
<a name="L2435" href="source/net/ipv4/igmp.c#L2435">2435</a> static inline struct <a href="ident?i=ip_mc_list">ip_mc_list</a> *<a href="ident?i=igmp_mc_get_first">igmp_mc_get_first</a>(struct <a href="ident?i=seq_file">seq_file</a> *<a href="ident?i=seq">seq</a>)
<a name="L2436" href="source/net/ipv4/igmp.c#L2436">2436</a> {
<a name="L2437" href="source/net/ipv4/igmp.c#L2437">2437</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=seq_file_net">seq_file_net</a>(<a href="ident?i=seq">seq</a>);
<a name="L2438" href="source/net/ipv4/igmp.c#L2438">2438</a>         struct <a href="ident?i=ip_mc_list">ip_mc_list</a> *im = <a href="ident?i=NULL">NULL</a>;
<a name="L2439" href="source/net/ipv4/igmp.c#L2439">2439</a>         struct <a href="ident?i=igmp_mc_iter_state">igmp_mc_iter_state</a> *<a href="ident?i=state">state</a> = <a href="ident?i=igmp_mc_seq_private">igmp_mc_seq_private</a>(<a href="ident?i=seq">seq</a>);
<a name="L2440" href="source/net/ipv4/igmp.c#L2440">2440</a> 
<a name="L2441" href="source/net/ipv4/igmp.c#L2441">2441</a>         <a href="ident?i=state">state</a>-&gt;in_dev = <a href="ident?i=NULL">NULL</a>;
<a name="L2442" href="source/net/ipv4/igmp.c#L2442">2442</a>         <a href="ident?i=for_each_netdev_rcu">for_each_netdev_rcu</a>(<a href="ident?i=net">net</a>, <a href="ident?i=state">state</a>-&gt;<a href="ident?i=dev">dev</a>) {
<a name="L2443" href="source/net/ipv4/igmp.c#L2443">2443</a>                 struct <a href="ident?i=in_device">in_device</a> *in_dev;
<a name="L2444" href="source/net/ipv4/igmp.c#L2444">2444</a> 
<a name="L2445" href="source/net/ipv4/igmp.c#L2445">2445</a>                 in_dev = <a href="ident?i=__in_dev_get_rcu">__in_dev_get_rcu</a>(<a href="ident?i=state">state</a>-&gt;<a href="ident?i=dev">dev</a>);
<a name="L2446" href="source/net/ipv4/igmp.c#L2446">2446</a>                 if (!in_dev)
<a name="L2447" href="source/net/ipv4/igmp.c#L2447">2447</a>                         continue;
<a name="L2448" href="source/net/ipv4/igmp.c#L2448">2448</a>                 im = <a href="ident?i=rcu_dereference">rcu_dereference</a>(in_dev-&gt;mc_list);
<a name="L2449" href="source/net/ipv4/igmp.c#L2449">2449</a>                 if (im) {
<a name="L2450" href="source/net/ipv4/igmp.c#L2450">2450</a>                         <a href="ident?i=state">state</a>-&gt;in_dev = in_dev;
<a name="L2451" href="source/net/ipv4/igmp.c#L2451">2451</a>                         break;
<a name="L2452" href="source/net/ipv4/igmp.c#L2452">2452</a>                 }
<a name="L2453" href="source/net/ipv4/igmp.c#L2453">2453</a>         }
<a name="L2454" href="source/net/ipv4/igmp.c#L2454">2454</a>         return im;
<a name="L2455" href="source/net/ipv4/igmp.c#L2455">2455</a> }
<a name="L2456" href="source/net/ipv4/igmp.c#L2456">2456</a> 
<a name="L2457" href="source/net/ipv4/igmp.c#L2457">2457</a> static struct <a href="ident?i=ip_mc_list">ip_mc_list</a> *<a href="ident?i=igmp_mc_get_next">igmp_mc_get_next</a>(struct <a href="ident?i=seq_file">seq_file</a> *<a href="ident?i=seq">seq</a>, struct <a href="ident?i=ip_mc_list">ip_mc_list</a> *im)
<a name="L2458" href="source/net/ipv4/igmp.c#L2458">2458</a> {
<a name="L2459" href="source/net/ipv4/igmp.c#L2459">2459</a>         struct <a href="ident?i=igmp_mc_iter_state">igmp_mc_iter_state</a> *<a href="ident?i=state">state</a> = <a href="ident?i=igmp_mc_seq_private">igmp_mc_seq_private</a>(<a href="ident?i=seq">seq</a>);
<a name="L2460" href="source/net/ipv4/igmp.c#L2460">2460</a> 
<a name="L2461" href="source/net/ipv4/igmp.c#L2461">2461</a>         im = <a href="ident?i=rcu_dereference">rcu_dereference</a>(im-&gt;next_rcu);
<a name="L2462" href="source/net/ipv4/igmp.c#L2462">2462</a>         while (!im) {
<a name="L2463" href="source/net/ipv4/igmp.c#L2463">2463</a>                 <a href="ident?i=state">state</a>-&gt;<a href="ident?i=dev">dev</a> = <a href="ident?i=next_net_device_rcu">next_net_device_rcu</a>(<a href="ident?i=state">state</a>-&gt;<a href="ident?i=dev">dev</a>);
<a name="L2464" href="source/net/ipv4/igmp.c#L2464">2464</a>                 if (!<a href="ident?i=state">state</a>-&gt;<a href="ident?i=dev">dev</a>) {
<a name="L2465" href="source/net/ipv4/igmp.c#L2465">2465</a>                         <a href="ident?i=state">state</a>-&gt;in_dev = <a href="ident?i=NULL">NULL</a>;
<a name="L2466" href="source/net/ipv4/igmp.c#L2466">2466</a>                         break;
<a name="L2467" href="source/net/ipv4/igmp.c#L2467">2467</a>                 }
<a name="L2468" href="source/net/ipv4/igmp.c#L2468">2468</a>                 <a href="ident?i=state">state</a>-&gt;in_dev = <a href="ident?i=__in_dev_get_rcu">__in_dev_get_rcu</a>(<a href="ident?i=state">state</a>-&gt;<a href="ident?i=dev">dev</a>);
<a name="L2469" href="source/net/ipv4/igmp.c#L2469">2469</a>                 if (!<a href="ident?i=state">state</a>-&gt;in_dev)
<a name="L2470" href="source/net/ipv4/igmp.c#L2470">2470</a>                         continue;
<a name="L2471" href="source/net/ipv4/igmp.c#L2471">2471</a>                 im = <a href="ident?i=rcu_dereference">rcu_dereference</a>(<a href="ident?i=state">state</a>-&gt;in_dev-&gt;mc_list);
<a name="L2472" href="source/net/ipv4/igmp.c#L2472">2472</a>         }
<a name="L2473" href="source/net/ipv4/igmp.c#L2473">2473</a>         return im;
<a name="L2474" href="source/net/ipv4/igmp.c#L2474">2474</a> }
<a name="L2475" href="source/net/ipv4/igmp.c#L2475">2475</a> 
<a name="L2476" href="source/net/ipv4/igmp.c#L2476">2476</a> static struct <a href="ident?i=ip_mc_list">ip_mc_list</a> *<a href="ident?i=igmp_mc_get_idx">igmp_mc_get_idx</a>(struct <a href="ident?i=seq_file">seq_file</a> *<a href="ident?i=seq">seq</a>, <a href="ident?i=loff_t">loff_t</a> <a href="ident?i=pos">pos</a>)
<a name="L2477" href="source/net/ipv4/igmp.c#L2477">2477</a> {
<a name="L2478" href="source/net/ipv4/igmp.c#L2478">2478</a>         struct <a href="ident?i=ip_mc_list">ip_mc_list</a> *im = <a href="ident?i=igmp_mc_get_first">igmp_mc_get_first</a>(<a href="ident?i=seq">seq</a>);
<a name="L2479" href="source/net/ipv4/igmp.c#L2479">2479</a>         if (im)
<a name="L2480" href="source/net/ipv4/igmp.c#L2480">2480</a>                 while (<a href="ident?i=pos">pos</a> &amp;&amp; (im = <a href="ident?i=igmp_mc_get_next">igmp_mc_get_next</a>(<a href="ident?i=seq">seq</a>, im)) != <a href="ident?i=NULL">NULL</a>)
<a name="L2481" href="source/net/ipv4/igmp.c#L2481">2481</a>                         --<a href="ident?i=pos">pos</a>;
<a name="L2482" href="source/net/ipv4/igmp.c#L2482">2482</a>         return <a href="ident?i=pos">pos</a> ? <a href="ident?i=NULL">NULL</a> : im;
<a name="L2483" href="source/net/ipv4/igmp.c#L2483">2483</a> }
<a name="L2484" href="source/net/ipv4/igmp.c#L2484">2484</a> 
<a name="L2485" href="source/net/ipv4/igmp.c#L2485">2485</a> static void *igmp_mc_seq_start(struct <a href="ident?i=seq_file">seq_file</a> *<a href="ident?i=seq">seq</a>, <a href="ident?i=loff_t">loff_t</a> *<a href="ident?i=pos">pos</a>)
<a name="L2486" href="source/net/ipv4/igmp.c#L2486">2486</a>         <a href="ident?i=__acquires">__acquires</a>(rcu)
<a name="L2487" href="source/net/ipv4/igmp.c#L2487">2487</a> {
<a name="L2488" href="source/net/ipv4/igmp.c#L2488">2488</a>         <a href="ident?i=rcu_read_lock">rcu_read_lock</a>();
<a name="L2489" href="source/net/ipv4/igmp.c#L2489">2489</a>         return *<a href="ident?i=pos">pos</a> ? <a href="ident?i=igmp_mc_get_idx">igmp_mc_get_idx</a>(<a href="ident?i=seq">seq</a>, *<a href="ident?i=pos">pos</a> - 1) : <a href="ident?i=SEQ_START_TOKEN">SEQ_START_TOKEN</a>;
<a name="L2490" href="source/net/ipv4/igmp.c#L2490">2490</a> }
<a name="L2491" href="source/net/ipv4/igmp.c#L2491">2491</a> 
<a name="L2492" href="source/net/ipv4/igmp.c#L2492">2492</a> static void *<a href="ident?i=igmp_mc_seq_next">igmp_mc_seq_next</a>(struct <a href="ident?i=seq_file">seq_file</a> *<a href="ident?i=seq">seq</a>, void *<a href="ident?i=v">v</a>, <a href="ident?i=loff_t">loff_t</a> *<a href="ident?i=pos">pos</a>)
<a name="L2493" href="source/net/ipv4/igmp.c#L2493">2493</a> {
<a name="L2494" href="source/net/ipv4/igmp.c#L2494">2494</a>         struct <a href="ident?i=ip_mc_list">ip_mc_list</a> *im;
<a name="L2495" href="source/net/ipv4/igmp.c#L2495">2495</a>         if (<a href="ident?i=v">v</a> == <a href="ident?i=SEQ_START_TOKEN">SEQ_START_TOKEN</a>)
<a name="L2496" href="source/net/ipv4/igmp.c#L2496">2496</a>                 im = <a href="ident?i=igmp_mc_get_first">igmp_mc_get_first</a>(<a href="ident?i=seq">seq</a>);
<a name="L2497" href="source/net/ipv4/igmp.c#L2497">2497</a>         else
<a name="L2498" href="source/net/ipv4/igmp.c#L2498">2498</a>                 im = <a href="ident?i=igmp_mc_get_next">igmp_mc_get_next</a>(<a href="ident?i=seq">seq</a>, <a href="ident?i=v">v</a>);
<a name="L2499" href="source/net/ipv4/igmp.c#L2499">2499</a>         ++*<a href="ident?i=pos">pos</a>;
<a name="L2500" href="source/net/ipv4/igmp.c#L2500">2500</a>         return im;
<a name="L2501" href="source/net/ipv4/igmp.c#L2501">2501</a> }
<a name="L2502" href="source/net/ipv4/igmp.c#L2502">2502</a> 
<a name="L2503" href="source/net/ipv4/igmp.c#L2503">2503</a> static void igmp_mc_seq_stop(struct <a href="ident?i=seq_file">seq_file</a> *<a href="ident?i=seq">seq</a>, void *<a href="ident?i=v">v</a>)
<a name="L2504" href="source/net/ipv4/igmp.c#L2504">2504</a>         <a href="ident?i=__releases">__releases</a>(rcu)
<a name="L2505" href="source/net/ipv4/igmp.c#L2505">2505</a> {
<a name="L2506" href="source/net/ipv4/igmp.c#L2506">2506</a>         struct <a href="ident?i=igmp_mc_iter_state">igmp_mc_iter_state</a> *<a href="ident?i=state">state</a> = <a href="ident?i=igmp_mc_seq_private">igmp_mc_seq_private</a>(<a href="ident?i=seq">seq</a>);
<a name="L2507" href="source/net/ipv4/igmp.c#L2507">2507</a> 
<a name="L2508" href="source/net/ipv4/igmp.c#L2508">2508</a>         <a href="ident?i=state">state</a>-&gt;in_dev = <a href="ident?i=NULL">NULL</a>;
<a name="L2509" href="source/net/ipv4/igmp.c#L2509">2509</a>         <a href="ident?i=state">state</a>-&gt;<a href="ident?i=dev">dev</a> = <a href="ident?i=NULL">NULL</a>;
<a name="L2510" href="source/net/ipv4/igmp.c#L2510">2510</a>         <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L2511" href="source/net/ipv4/igmp.c#L2511">2511</a> }
<a name="L2512" href="source/net/ipv4/igmp.c#L2512">2512</a> 
<a name="L2513" href="source/net/ipv4/igmp.c#L2513">2513</a> static int <a href="ident?i=igmp_mc_seq_show">igmp_mc_seq_show</a>(struct <a href="ident?i=seq_file">seq_file</a> *<a href="ident?i=seq">seq</a>, void *<a href="ident?i=v">v</a>)
<a name="L2514" href="source/net/ipv4/igmp.c#L2514">2514</a> {
<a name="L2515" href="source/net/ipv4/igmp.c#L2515">2515</a>         if (<a href="ident?i=v">v</a> == <a href="ident?i=SEQ_START_TOKEN">SEQ_START_TOKEN</a>)
<a name="L2516" href="source/net/ipv4/igmp.c#L2516">2516</a>                 <a href="ident?i=seq_puts">seq_puts</a>(<a href="ident?i=seq">seq</a>,
<a name="L2517" href="source/net/ipv4/igmp.c#L2517">2517</a>                          <i>"Idx\tDevice    : Count Querier\tGroup    Users Timer\tReporter\n"</i>);
<a name="L2518" href="source/net/ipv4/igmp.c#L2518">2518</a>         else {
<a name="L2519" href="source/net/ipv4/igmp.c#L2519">2519</a>                 struct <a href="ident?i=ip_mc_list">ip_mc_list</a> *im = (struct <a href="ident?i=ip_mc_list">ip_mc_list</a> *)<a href="ident?i=v">v</a>;
<a name="L2520" href="source/net/ipv4/igmp.c#L2520">2520</a>                 struct <a href="ident?i=igmp_mc_iter_state">igmp_mc_iter_state</a> *<a href="ident?i=state">state</a> = <a href="ident?i=igmp_mc_seq_private">igmp_mc_seq_private</a>(<a href="ident?i=seq">seq</a>);
<a name="L2521" href="source/net/ipv4/igmp.c#L2521">2521</a>                 char   *querier;
<a name="L2522" href="source/net/ipv4/igmp.c#L2522">2522</a>                 long <a href="ident?i=delta">delta</a>;
<a name="L2523" href="source/net/ipv4/igmp.c#L2523">2523</a> 
<a name="L2524" href="source/net/ipv4/igmp.c#L2524">2524</a> #ifdef CONFIG_IP_MULTICAST
<a name="L2525" href="source/net/ipv4/igmp.c#L2525">2525</a>                 querier = <a href="ident?i=IGMP_V1_SEEN">IGMP_V1_SEEN</a>(<a href="ident?i=state">state</a>-&gt;in_dev) ? <i>"V1"</i> :
<a name="L2526" href="source/net/ipv4/igmp.c#L2526">2526</a>                           <a href="ident?i=IGMP_V2_SEEN">IGMP_V2_SEEN</a>(<a href="ident?i=state">state</a>-&gt;in_dev) ? <i>"V2"</i> :
<a name="L2527" href="source/net/ipv4/igmp.c#L2527">2527</a>                           <i>"V3"</i>;
<a name="L2528" href="source/net/ipv4/igmp.c#L2528">2528</a> #else
<a name="L2529" href="source/net/ipv4/igmp.c#L2529">2529</a>                 querier = <i>"NONE"</i>;
<a name="L2530" href="source/net/ipv4/igmp.c#L2530">2530</a> #endif
<a name="L2531" href="source/net/ipv4/igmp.c#L2531">2531</a> 
<a name="L2532" href="source/net/ipv4/igmp.c#L2532">2532</a>                 if (<a href="ident?i=rcu_access_pointer">rcu_access_pointer</a>(<a href="ident?i=state">state</a>-&gt;in_dev-&gt;mc_list) == im) {
<a name="L2533" href="source/net/ipv4/igmp.c#L2533">2533</a>                         <a href="ident?i=seq_printf">seq_printf</a>(<a href="ident?i=seq">seq</a>, <i>"%d\t%-10s: %5d %7s\n"</i>,
<a name="L2534" href="source/net/ipv4/igmp.c#L2534">2534</a>                                    <a href="ident?i=state">state</a>-&gt;<a href="ident?i=dev">dev</a>-&gt;ifindex, <a href="ident?i=state">state</a>-&gt;<a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=name">name</a>, <a href="ident?i=state">state</a>-&gt;in_dev-&gt;mc_count, querier);
<a name="L2535" href="source/net/ipv4/igmp.c#L2535">2535</a>                 }
<a name="L2536" href="source/net/ipv4/igmp.c#L2536">2536</a> 
<a name="L2537" href="source/net/ipv4/igmp.c#L2537">2537</a>                 <a href="ident?i=delta">delta</a> = im-&gt;<a href="ident?i=timer">timer</a>.expires - <a href="ident?i=jiffies">jiffies</a>;
<a name="L2538" href="source/net/ipv4/igmp.c#L2538">2538</a>                 <a href="ident?i=seq_printf">seq_printf</a>(<a href="ident?i=seq">seq</a>,
<a name="L2539" href="source/net/ipv4/igmp.c#L2539">2539</a>                            <i>"\t\t\t\t%08X %5d %d:%08lX\t\t%d\n"</i>,
<a name="L2540" href="source/net/ipv4/igmp.c#L2540">2540</a>                            im-&gt;multiaddr, im-&gt;users,
<a name="L2541" href="source/net/ipv4/igmp.c#L2541">2541</a>                            im-&gt;tm_running,
<a name="L2542" href="source/net/ipv4/igmp.c#L2542">2542</a>                            im-&gt;tm_running ? <a href="ident?i=jiffies_delta_to_clock_t">jiffies_delta_to_clock_t</a>(<a href="ident?i=delta">delta</a>) : 0,
<a name="L2543" href="source/net/ipv4/igmp.c#L2543">2543</a>                            im-&gt;reporter);
<a name="L2544" href="source/net/ipv4/igmp.c#L2544">2544</a>         }
<a name="L2545" href="source/net/ipv4/igmp.c#L2545">2545</a>         return 0;
<a name="L2546" href="source/net/ipv4/igmp.c#L2546">2546</a> }
<a name="L2547" href="source/net/ipv4/igmp.c#L2547">2547</a> 
<a name="L2548" href="source/net/ipv4/igmp.c#L2548">2548</a> static const struct <a href="ident?i=seq_operations">seq_operations</a> <a href="ident?i=igmp_mc_seq_ops">igmp_mc_seq_ops</a> = {
<a name="L2549" href="source/net/ipv4/igmp.c#L2549">2549</a>         .<a href="ident?i=start">start</a>  =       igmp_mc_seq_start,
<a name="L2550" href="source/net/ipv4/igmp.c#L2550">2550</a>         .<a href="ident?i=next">next</a>   =       <a href="ident?i=igmp_mc_seq_next">igmp_mc_seq_next</a>,
<a name="L2551" href="source/net/ipv4/igmp.c#L2551">2551</a>         .<a href="ident?i=stop">stop</a>   =       igmp_mc_seq_stop,
<a name="L2552" href="source/net/ipv4/igmp.c#L2552">2552</a>         .<a href="ident?i=show">show</a>   =       <a href="ident?i=igmp_mc_seq_show">igmp_mc_seq_show</a>,
<a name="L2553" href="source/net/ipv4/igmp.c#L2553">2553</a> };
<a name="L2554" href="source/net/ipv4/igmp.c#L2554">2554</a> 
<a name="L2555" href="source/net/ipv4/igmp.c#L2555">2555</a> static int <a href="ident?i=igmp_mc_seq_open">igmp_mc_seq_open</a>(struct <a href="ident?i=inode">inode</a> *<a href="ident?i=inode">inode</a>, struct <a href="ident?i=file">file</a> *<a href="ident?i=file">file</a>)
<a name="L2556" href="source/net/ipv4/igmp.c#L2556">2556</a> {
<a name="L2557" href="source/net/ipv4/igmp.c#L2557">2557</a>         return <a href="ident?i=seq_open_net">seq_open_net</a>(<a href="ident?i=inode">inode</a>, <a href="ident?i=file">file</a>, &amp;<a href="ident?i=igmp_mc_seq_ops">igmp_mc_seq_ops</a>,
<a name="L2558" href="source/net/ipv4/igmp.c#L2558">2558</a>                         sizeof(struct <a href="ident?i=igmp_mc_iter_state">igmp_mc_iter_state</a>));
<a name="L2559" href="source/net/ipv4/igmp.c#L2559">2559</a> }
<a name="L2560" href="source/net/ipv4/igmp.c#L2560">2560</a> 
<a name="L2561" href="source/net/ipv4/igmp.c#L2561">2561</a> static const struct <a href="ident?i=file_operations">file_operations</a> <a href="ident?i=igmp_mc_seq_fops">igmp_mc_seq_fops</a> = {
<a name="L2562" href="source/net/ipv4/igmp.c#L2562">2562</a>         .owner          =       <a href="ident?i=THIS_MODULE">THIS_MODULE</a>,
<a name="L2563" href="source/net/ipv4/igmp.c#L2563">2563</a>         .<a href="ident?i=open">open</a>           =       <a href="ident?i=igmp_mc_seq_open">igmp_mc_seq_open</a>,
<a name="L2564" href="source/net/ipv4/igmp.c#L2564">2564</a>         .<a href="ident?i=read">read</a>           =       <a href="ident?i=seq_read">seq_read</a>,
<a name="L2565" href="source/net/ipv4/igmp.c#L2565">2565</a>         .llseek         =       <a href="ident?i=seq_lseek">seq_lseek</a>,
<a name="L2566" href="source/net/ipv4/igmp.c#L2566">2566</a>         .<a href="ident?i=release">release</a>        =       <a href="ident?i=seq_release_net">seq_release_net</a>,
<a name="L2567" href="source/net/ipv4/igmp.c#L2567">2567</a> };
<a name="L2568" href="source/net/ipv4/igmp.c#L2568">2568</a> 
<a name="L2569" href="source/net/ipv4/igmp.c#L2569">2569</a> struct <a href="ident?i=igmp_mcf_iter_state">igmp_mcf_iter_state</a> {
<a name="L2570" href="source/net/ipv4/igmp.c#L2570">2570</a>         struct <a href="ident?i=seq_net_private">seq_net_private</a> <a href="ident?i=p">p</a>;
<a name="L2571" href="source/net/ipv4/igmp.c#L2571">2571</a>         struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>;
<a name="L2572" href="source/net/ipv4/igmp.c#L2572">2572</a>         struct <a href="ident?i=in_device">in_device</a> *<a href="ident?i=idev">idev</a>;
<a name="L2573" href="source/net/ipv4/igmp.c#L2573">2573</a>         struct <a href="ident?i=ip_mc_list">ip_mc_list</a> *im;
<a name="L2574" href="source/net/ipv4/igmp.c#L2574">2574</a> };
<a name="L2575" href="source/net/ipv4/igmp.c#L2575">2575</a> 
<a name="L2576" href="source/net/ipv4/igmp.c#L2576">2576</a> #define <a href="ident?i=igmp_mcf_seq_private">igmp_mcf_seq_private</a>(<a href="ident?i=seq">seq</a>)       ((struct <a href="ident?i=igmp_mcf_iter_state">igmp_mcf_iter_state</a> *)(<a href="ident?i=seq">seq</a>)-&gt;<a href="ident?i=private">private</a>)
<a name="L2577" href="source/net/ipv4/igmp.c#L2577">2577</a> 
<a name="L2578" href="source/net/ipv4/igmp.c#L2578">2578</a> static inline struct <a href="ident?i=ip_sf_list">ip_sf_list</a> *<a href="ident?i=igmp_mcf_get_first">igmp_mcf_get_first</a>(struct <a href="ident?i=seq_file">seq_file</a> *<a href="ident?i=seq">seq</a>)
<a name="L2579" href="source/net/ipv4/igmp.c#L2579">2579</a> {
<a name="L2580" href="source/net/ipv4/igmp.c#L2580">2580</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=seq_file_net">seq_file_net</a>(<a href="ident?i=seq">seq</a>);
<a name="L2581" href="source/net/ipv4/igmp.c#L2581">2581</a>         struct <a href="ident?i=ip_sf_list">ip_sf_list</a> *psf = <a href="ident?i=NULL">NULL</a>;
<a name="L2582" href="source/net/ipv4/igmp.c#L2582">2582</a>         struct <a href="ident?i=ip_mc_list">ip_mc_list</a> *im = <a href="ident?i=NULL">NULL</a>;
<a name="L2583" href="source/net/ipv4/igmp.c#L2583">2583</a>         struct <a href="ident?i=igmp_mcf_iter_state">igmp_mcf_iter_state</a> *<a href="ident?i=state">state</a> = <a href="ident?i=igmp_mcf_seq_private">igmp_mcf_seq_private</a>(<a href="ident?i=seq">seq</a>);
<a name="L2584" href="source/net/ipv4/igmp.c#L2584">2584</a> 
<a name="L2585" href="source/net/ipv4/igmp.c#L2585">2585</a>         <a href="ident?i=state">state</a>-&gt;<a href="ident?i=idev">idev</a> = <a href="ident?i=NULL">NULL</a>;
<a name="L2586" href="source/net/ipv4/igmp.c#L2586">2586</a>         <a href="ident?i=state">state</a>-&gt;im = <a href="ident?i=NULL">NULL</a>;
<a name="L2587" href="source/net/ipv4/igmp.c#L2587">2587</a>         <a href="ident?i=for_each_netdev_rcu">for_each_netdev_rcu</a>(<a href="ident?i=net">net</a>, <a href="ident?i=state">state</a>-&gt;<a href="ident?i=dev">dev</a>) {
<a name="L2588" href="source/net/ipv4/igmp.c#L2588">2588</a>                 struct <a href="ident?i=in_device">in_device</a> *<a href="ident?i=idev">idev</a>;
<a name="L2589" href="source/net/ipv4/igmp.c#L2589">2589</a>                 <a href="ident?i=idev">idev</a> = <a href="ident?i=__in_dev_get_rcu">__in_dev_get_rcu</a>(<a href="ident?i=state">state</a>-&gt;<a href="ident?i=dev">dev</a>);
<a name="L2590" href="source/net/ipv4/igmp.c#L2590">2590</a>                 if (<a href="ident?i=unlikely">unlikely</a>(!<a href="ident?i=idev">idev</a>))
<a name="L2591" href="source/net/ipv4/igmp.c#L2591">2591</a>                         continue;
<a name="L2592" href="source/net/ipv4/igmp.c#L2592">2592</a>                 im = <a href="ident?i=rcu_dereference">rcu_dereference</a>(<a href="ident?i=idev">idev</a>-&gt;mc_list);
<a name="L2593" href="source/net/ipv4/igmp.c#L2593">2593</a>                 if (<a href="ident?i=likely">likely</a>(im)) {
<a name="L2594" href="source/net/ipv4/igmp.c#L2594">2594</a>                         <a href="ident?i=spin_lock_bh">spin_lock_bh</a>(&amp;im-&gt;<a href="ident?i=lock">lock</a>);
<a name="L2595" href="source/net/ipv4/igmp.c#L2595">2595</a>                         psf = im-&gt;sources;
<a name="L2596" href="source/net/ipv4/igmp.c#L2596">2596</a>                         if (<a href="ident?i=likely">likely</a>(psf)) {
<a name="L2597" href="source/net/ipv4/igmp.c#L2597">2597</a>                                 <a href="ident?i=state">state</a>-&gt;im = im;
<a name="L2598" href="source/net/ipv4/igmp.c#L2598">2598</a>                                 <a href="ident?i=state">state</a>-&gt;<a href="ident?i=idev">idev</a> = <a href="ident?i=idev">idev</a>;
<a name="L2599" href="source/net/ipv4/igmp.c#L2599">2599</a>                                 break;
<a name="L2600" href="source/net/ipv4/igmp.c#L2600">2600</a>                         }
<a name="L2601" href="source/net/ipv4/igmp.c#L2601">2601</a>                         <a href="ident?i=spin_unlock_bh">spin_unlock_bh</a>(&amp;im-&gt;<a href="ident?i=lock">lock</a>);
<a name="L2602" href="source/net/ipv4/igmp.c#L2602">2602</a>                 }
<a name="L2603" href="source/net/ipv4/igmp.c#L2603">2603</a>         }
<a name="L2604" href="source/net/ipv4/igmp.c#L2604">2604</a>         return psf;
<a name="L2605" href="source/net/ipv4/igmp.c#L2605">2605</a> }
<a name="L2606" href="source/net/ipv4/igmp.c#L2606">2606</a> 
<a name="L2607" href="source/net/ipv4/igmp.c#L2607">2607</a> static struct <a href="ident?i=ip_sf_list">ip_sf_list</a> *<a href="ident?i=igmp_mcf_get_next">igmp_mcf_get_next</a>(struct <a href="ident?i=seq_file">seq_file</a> *<a href="ident?i=seq">seq</a>, struct <a href="ident?i=ip_sf_list">ip_sf_list</a> *psf)
<a name="L2608" href="source/net/ipv4/igmp.c#L2608">2608</a> {
<a name="L2609" href="source/net/ipv4/igmp.c#L2609">2609</a>         struct <a href="ident?i=igmp_mcf_iter_state">igmp_mcf_iter_state</a> *<a href="ident?i=state">state</a> = <a href="ident?i=igmp_mcf_seq_private">igmp_mcf_seq_private</a>(<a href="ident?i=seq">seq</a>);
<a name="L2610" href="source/net/ipv4/igmp.c#L2610">2610</a> 
<a name="L2611" href="source/net/ipv4/igmp.c#L2611">2611</a>         psf = psf-&gt;sf_next;
<a name="L2612" href="source/net/ipv4/igmp.c#L2612">2612</a>         while (!psf) {
<a name="L2613" href="source/net/ipv4/igmp.c#L2613">2613</a>                 <a href="ident?i=spin_unlock_bh">spin_unlock_bh</a>(&amp;<a href="ident?i=state">state</a>-&gt;im-&gt;<a href="ident?i=lock">lock</a>);
<a name="L2614" href="source/net/ipv4/igmp.c#L2614">2614</a>                 <a href="ident?i=state">state</a>-&gt;im = <a href="ident?i=state">state</a>-&gt;im-&gt;<a href="ident?i=next">next</a>;
<a name="L2615" href="source/net/ipv4/igmp.c#L2615">2615</a>                 while (!<a href="ident?i=state">state</a>-&gt;im) {
<a name="L2616" href="source/net/ipv4/igmp.c#L2616">2616</a>                         <a href="ident?i=state">state</a>-&gt;<a href="ident?i=dev">dev</a> = <a href="ident?i=next_net_device_rcu">next_net_device_rcu</a>(<a href="ident?i=state">state</a>-&gt;<a href="ident?i=dev">dev</a>);
<a name="L2617" href="source/net/ipv4/igmp.c#L2617">2617</a>                         if (!<a href="ident?i=state">state</a>-&gt;<a href="ident?i=dev">dev</a>) {
<a name="L2618" href="source/net/ipv4/igmp.c#L2618">2618</a>                                 <a href="ident?i=state">state</a>-&gt;<a href="ident?i=idev">idev</a> = <a href="ident?i=NULL">NULL</a>;
<a name="L2619" href="source/net/ipv4/igmp.c#L2619">2619</a>                                 goto <a href="ident?i=out">out</a>;
<a name="L2620" href="source/net/ipv4/igmp.c#L2620">2620</a>                         }
<a name="L2621" href="source/net/ipv4/igmp.c#L2621">2621</a>                         <a href="ident?i=state">state</a>-&gt;<a href="ident?i=idev">idev</a> = <a href="ident?i=__in_dev_get_rcu">__in_dev_get_rcu</a>(<a href="ident?i=state">state</a>-&gt;<a href="ident?i=dev">dev</a>);
<a name="L2622" href="source/net/ipv4/igmp.c#L2622">2622</a>                         if (!<a href="ident?i=state">state</a>-&gt;<a href="ident?i=idev">idev</a>)
<a name="L2623" href="source/net/ipv4/igmp.c#L2623">2623</a>                                 continue;
<a name="L2624" href="source/net/ipv4/igmp.c#L2624">2624</a>                         <a href="ident?i=state">state</a>-&gt;im = <a href="ident?i=rcu_dereference">rcu_dereference</a>(<a href="ident?i=state">state</a>-&gt;<a href="ident?i=idev">idev</a>-&gt;mc_list);
<a name="L2625" href="source/net/ipv4/igmp.c#L2625">2625</a>                 }
<a name="L2626" href="source/net/ipv4/igmp.c#L2626">2626</a>                 if (!<a href="ident?i=state">state</a>-&gt;im)
<a name="L2627" href="source/net/ipv4/igmp.c#L2627">2627</a>                         break;
<a name="L2628" href="source/net/ipv4/igmp.c#L2628">2628</a>                 <a href="ident?i=spin_lock_bh">spin_lock_bh</a>(&amp;<a href="ident?i=state">state</a>-&gt;im-&gt;<a href="ident?i=lock">lock</a>);
<a name="L2629" href="source/net/ipv4/igmp.c#L2629">2629</a>                 psf = <a href="ident?i=state">state</a>-&gt;im-&gt;sources;
<a name="L2630" href="source/net/ipv4/igmp.c#L2630">2630</a>         }
<a name="L2631" href="source/net/ipv4/igmp.c#L2631">2631</a> <a href="ident?i=out">out</a>:
<a name="L2632" href="source/net/ipv4/igmp.c#L2632">2632</a>         return psf;
<a name="L2633" href="source/net/ipv4/igmp.c#L2633">2633</a> }
<a name="L2634" href="source/net/ipv4/igmp.c#L2634">2634</a> 
<a name="L2635" href="source/net/ipv4/igmp.c#L2635">2635</a> static struct <a href="ident?i=ip_sf_list">ip_sf_list</a> *<a href="ident?i=igmp_mcf_get_idx">igmp_mcf_get_idx</a>(struct <a href="ident?i=seq_file">seq_file</a> *<a href="ident?i=seq">seq</a>, <a href="ident?i=loff_t">loff_t</a> <a href="ident?i=pos">pos</a>)
<a name="L2636" href="source/net/ipv4/igmp.c#L2636">2636</a> {
<a name="L2637" href="source/net/ipv4/igmp.c#L2637">2637</a>         struct <a href="ident?i=ip_sf_list">ip_sf_list</a> *psf = <a href="ident?i=igmp_mcf_get_first">igmp_mcf_get_first</a>(<a href="ident?i=seq">seq</a>);
<a name="L2638" href="source/net/ipv4/igmp.c#L2638">2638</a>         if (psf)
<a name="L2639" href="source/net/ipv4/igmp.c#L2639">2639</a>                 while (<a href="ident?i=pos">pos</a> &amp;&amp; (psf = <a href="ident?i=igmp_mcf_get_next">igmp_mcf_get_next</a>(<a href="ident?i=seq">seq</a>, psf)) != <a href="ident?i=NULL">NULL</a>)
<a name="L2640" href="source/net/ipv4/igmp.c#L2640">2640</a>                         --<a href="ident?i=pos">pos</a>;
<a name="L2641" href="source/net/ipv4/igmp.c#L2641">2641</a>         return <a href="ident?i=pos">pos</a> ? <a href="ident?i=NULL">NULL</a> : psf;
<a name="L2642" href="source/net/ipv4/igmp.c#L2642">2642</a> }
<a name="L2643" href="source/net/ipv4/igmp.c#L2643">2643</a> 
<a name="L2644" href="source/net/ipv4/igmp.c#L2644">2644</a> static void *igmp_mcf_seq_start(struct <a href="ident?i=seq_file">seq_file</a> *<a href="ident?i=seq">seq</a>, <a href="ident?i=loff_t">loff_t</a> *<a href="ident?i=pos">pos</a>)
<a name="L2645" href="source/net/ipv4/igmp.c#L2645">2645</a>         <a href="ident?i=__acquires">__acquires</a>(rcu)
<a name="L2646" href="source/net/ipv4/igmp.c#L2646">2646</a> {
<a name="L2647" href="source/net/ipv4/igmp.c#L2647">2647</a>         <a href="ident?i=rcu_read_lock">rcu_read_lock</a>();
<a name="L2648" href="source/net/ipv4/igmp.c#L2648">2648</a>         return *<a href="ident?i=pos">pos</a> ? <a href="ident?i=igmp_mcf_get_idx">igmp_mcf_get_idx</a>(<a href="ident?i=seq">seq</a>, *<a href="ident?i=pos">pos</a> - 1) : <a href="ident?i=SEQ_START_TOKEN">SEQ_START_TOKEN</a>;
<a name="L2649" href="source/net/ipv4/igmp.c#L2649">2649</a> }
<a name="L2650" href="source/net/ipv4/igmp.c#L2650">2650</a> 
<a name="L2651" href="source/net/ipv4/igmp.c#L2651">2651</a> static void *<a href="ident?i=igmp_mcf_seq_next">igmp_mcf_seq_next</a>(struct <a href="ident?i=seq_file">seq_file</a> *<a href="ident?i=seq">seq</a>, void *<a href="ident?i=v">v</a>, <a href="ident?i=loff_t">loff_t</a> *<a href="ident?i=pos">pos</a>)
<a name="L2652" href="source/net/ipv4/igmp.c#L2652">2652</a> {
<a name="L2653" href="source/net/ipv4/igmp.c#L2653">2653</a>         struct <a href="ident?i=ip_sf_list">ip_sf_list</a> *psf;
<a name="L2654" href="source/net/ipv4/igmp.c#L2654">2654</a>         if (<a href="ident?i=v">v</a> == <a href="ident?i=SEQ_START_TOKEN">SEQ_START_TOKEN</a>)
<a name="L2655" href="source/net/ipv4/igmp.c#L2655">2655</a>                 psf = <a href="ident?i=igmp_mcf_get_first">igmp_mcf_get_first</a>(<a href="ident?i=seq">seq</a>);
<a name="L2656" href="source/net/ipv4/igmp.c#L2656">2656</a>         else
<a name="L2657" href="source/net/ipv4/igmp.c#L2657">2657</a>                 psf = <a href="ident?i=igmp_mcf_get_next">igmp_mcf_get_next</a>(<a href="ident?i=seq">seq</a>, <a href="ident?i=v">v</a>);
<a name="L2658" href="source/net/ipv4/igmp.c#L2658">2658</a>         ++*<a href="ident?i=pos">pos</a>;
<a name="L2659" href="source/net/ipv4/igmp.c#L2659">2659</a>         return psf;
<a name="L2660" href="source/net/ipv4/igmp.c#L2660">2660</a> }
<a name="L2661" href="source/net/ipv4/igmp.c#L2661">2661</a> 
<a name="L2662" href="source/net/ipv4/igmp.c#L2662">2662</a> static void igmp_mcf_seq_stop(struct <a href="ident?i=seq_file">seq_file</a> *<a href="ident?i=seq">seq</a>, void *<a href="ident?i=v">v</a>)
<a name="L2663" href="source/net/ipv4/igmp.c#L2663">2663</a>         <a href="ident?i=__releases">__releases</a>(rcu)
<a name="L2664" href="source/net/ipv4/igmp.c#L2664">2664</a> {
<a name="L2665" href="source/net/ipv4/igmp.c#L2665">2665</a>         struct <a href="ident?i=igmp_mcf_iter_state">igmp_mcf_iter_state</a> *<a href="ident?i=state">state</a> = <a href="ident?i=igmp_mcf_seq_private">igmp_mcf_seq_private</a>(<a href="ident?i=seq">seq</a>);
<a name="L2666" href="source/net/ipv4/igmp.c#L2666">2666</a>         if (<a href="ident?i=likely">likely</a>(<a href="ident?i=state">state</a>-&gt;im)) {
<a name="L2667" href="source/net/ipv4/igmp.c#L2667">2667</a>                 <a href="ident?i=spin_unlock_bh">spin_unlock_bh</a>(&amp;<a href="ident?i=state">state</a>-&gt;im-&gt;<a href="ident?i=lock">lock</a>);
<a name="L2668" href="source/net/ipv4/igmp.c#L2668">2668</a>                 <a href="ident?i=state">state</a>-&gt;im = <a href="ident?i=NULL">NULL</a>;
<a name="L2669" href="source/net/ipv4/igmp.c#L2669">2669</a>         }
<a name="L2670" href="source/net/ipv4/igmp.c#L2670">2670</a>         <a href="ident?i=state">state</a>-&gt;<a href="ident?i=idev">idev</a> = <a href="ident?i=NULL">NULL</a>;
<a name="L2671" href="source/net/ipv4/igmp.c#L2671">2671</a>         <a href="ident?i=state">state</a>-&gt;<a href="ident?i=dev">dev</a> = <a href="ident?i=NULL">NULL</a>;
<a name="L2672" href="source/net/ipv4/igmp.c#L2672">2672</a>         <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L2673" href="source/net/ipv4/igmp.c#L2673">2673</a> }
<a name="L2674" href="source/net/ipv4/igmp.c#L2674">2674</a> 
<a name="L2675" href="source/net/ipv4/igmp.c#L2675">2675</a> static int <a href="ident?i=igmp_mcf_seq_show">igmp_mcf_seq_show</a>(struct <a href="ident?i=seq_file">seq_file</a> *<a href="ident?i=seq">seq</a>, void *<a href="ident?i=v">v</a>)
<a name="L2676" href="source/net/ipv4/igmp.c#L2676">2676</a> {
<a name="L2677" href="source/net/ipv4/igmp.c#L2677">2677</a>         struct <a href="ident?i=ip_sf_list">ip_sf_list</a> *psf = (struct <a href="ident?i=ip_sf_list">ip_sf_list</a> *)<a href="ident?i=v">v</a>;
<a name="L2678" href="source/net/ipv4/igmp.c#L2678">2678</a>         struct <a href="ident?i=igmp_mcf_iter_state">igmp_mcf_iter_state</a> *<a href="ident?i=state">state</a> = <a href="ident?i=igmp_mcf_seq_private">igmp_mcf_seq_private</a>(<a href="ident?i=seq">seq</a>);
<a name="L2679" href="source/net/ipv4/igmp.c#L2679">2679</a> 
<a name="L2680" href="source/net/ipv4/igmp.c#L2680">2680</a>         if (<a href="ident?i=v">v</a> == <a href="ident?i=SEQ_START_TOKEN">SEQ_START_TOKEN</a>) {
<a name="L2681" href="source/net/ipv4/igmp.c#L2681">2681</a>                 <a href="ident?i=seq_puts">seq_puts</a>(<a href="ident?i=seq">seq</a>, <i>"Idx Device        MCA        SRC    INC    EXC\n"</i>);
<a name="L2682" href="source/net/ipv4/igmp.c#L2682">2682</a>         } else {
<a name="L2683" href="source/net/ipv4/igmp.c#L2683">2683</a>                 <a href="ident?i=seq_printf">seq_printf</a>(<a href="ident?i=seq">seq</a>,
<a name="L2684" href="source/net/ipv4/igmp.c#L2684">2684</a>                            <i>"%3d %6.6s 0x%08x "</i>
<a name="L2685" href="source/net/ipv4/igmp.c#L2685">2685</a>                            <i>"0x%08x %6lu %6lu\n"</i>,
<a name="L2686" href="source/net/ipv4/igmp.c#L2686">2686</a>                            <a href="ident?i=state">state</a>-&gt;<a href="ident?i=dev">dev</a>-&gt;ifindex, <a href="ident?i=state">state</a>-&gt;<a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=name">name</a>,
<a name="L2687" href="source/net/ipv4/igmp.c#L2687">2687</a>                            <a href="ident?i=ntohl">ntohl</a>(<a href="ident?i=state">state</a>-&gt;im-&gt;multiaddr),
<a name="L2688" href="source/net/ipv4/igmp.c#L2688">2688</a>                            <a href="ident?i=ntohl">ntohl</a>(psf-&gt;sf_inaddr),
<a name="L2689" href="source/net/ipv4/igmp.c#L2689">2689</a>                            psf-&gt;sf_count[<a href="ident?i=MCAST_INCLUDE">MCAST_INCLUDE</a>],
<a name="L2690" href="source/net/ipv4/igmp.c#L2690">2690</a>                            psf-&gt;sf_count[<a href="ident?i=MCAST_EXCLUDE">MCAST_EXCLUDE</a>]);
<a name="L2691" href="source/net/ipv4/igmp.c#L2691">2691</a>         }
<a name="L2692" href="source/net/ipv4/igmp.c#L2692">2692</a>         return 0;
<a name="L2693" href="source/net/ipv4/igmp.c#L2693">2693</a> }
<a name="L2694" href="source/net/ipv4/igmp.c#L2694">2694</a> 
<a name="L2695" href="source/net/ipv4/igmp.c#L2695">2695</a> static const struct <a href="ident?i=seq_operations">seq_operations</a> <a href="ident?i=igmp_mcf_seq_ops">igmp_mcf_seq_ops</a> = {
<a name="L2696" href="source/net/ipv4/igmp.c#L2696">2696</a>         .<a href="ident?i=start">start</a>  =       igmp_mcf_seq_start,
<a name="L2697" href="source/net/ipv4/igmp.c#L2697">2697</a>         .<a href="ident?i=next">next</a>   =       <a href="ident?i=igmp_mcf_seq_next">igmp_mcf_seq_next</a>,
<a name="L2698" href="source/net/ipv4/igmp.c#L2698">2698</a>         .<a href="ident?i=stop">stop</a>   =       igmp_mcf_seq_stop,
<a name="L2699" href="source/net/ipv4/igmp.c#L2699">2699</a>         .<a href="ident?i=show">show</a>   =       <a href="ident?i=igmp_mcf_seq_show">igmp_mcf_seq_show</a>,
<a name="L2700" href="source/net/ipv4/igmp.c#L2700">2700</a> };
<a name="L2701" href="source/net/ipv4/igmp.c#L2701">2701</a> 
<a name="L2702" href="source/net/ipv4/igmp.c#L2702">2702</a> static int <a href="ident?i=igmp_mcf_seq_open">igmp_mcf_seq_open</a>(struct <a href="ident?i=inode">inode</a> *<a href="ident?i=inode">inode</a>, struct <a href="ident?i=file">file</a> *<a href="ident?i=file">file</a>)
<a name="L2703" href="source/net/ipv4/igmp.c#L2703">2703</a> {
<a name="L2704" href="source/net/ipv4/igmp.c#L2704">2704</a>         return <a href="ident?i=seq_open_net">seq_open_net</a>(<a href="ident?i=inode">inode</a>, <a href="ident?i=file">file</a>, &amp;<a href="ident?i=igmp_mcf_seq_ops">igmp_mcf_seq_ops</a>,
<a name="L2705" href="source/net/ipv4/igmp.c#L2705">2705</a>                         sizeof(struct <a href="ident?i=igmp_mcf_iter_state">igmp_mcf_iter_state</a>));
<a name="L2706" href="source/net/ipv4/igmp.c#L2706">2706</a> }
<a name="L2707" href="source/net/ipv4/igmp.c#L2707">2707</a> 
<a name="L2708" href="source/net/ipv4/igmp.c#L2708">2708</a> static const struct <a href="ident?i=file_operations">file_operations</a> <a href="ident?i=igmp_mcf_seq_fops">igmp_mcf_seq_fops</a> = {
<a name="L2709" href="source/net/ipv4/igmp.c#L2709">2709</a>         .owner          =       <a href="ident?i=THIS_MODULE">THIS_MODULE</a>,
<a name="L2710" href="source/net/ipv4/igmp.c#L2710">2710</a>         .<a href="ident?i=open">open</a>           =       <a href="ident?i=igmp_mcf_seq_open">igmp_mcf_seq_open</a>,
<a name="L2711" href="source/net/ipv4/igmp.c#L2711">2711</a>         .<a href="ident?i=read">read</a>           =       <a href="ident?i=seq_read">seq_read</a>,
<a name="L2712" href="source/net/ipv4/igmp.c#L2712">2712</a>         .llseek         =       <a href="ident?i=seq_lseek">seq_lseek</a>,
<a name="L2713" href="source/net/ipv4/igmp.c#L2713">2713</a>         .<a href="ident?i=release">release</a>        =       <a href="ident?i=seq_release_net">seq_release_net</a>,
<a name="L2714" href="source/net/ipv4/igmp.c#L2714">2714</a> };
<a name="L2715" href="source/net/ipv4/igmp.c#L2715">2715</a> 
<a name="L2716" href="source/net/ipv4/igmp.c#L2716">2716</a> static int <a href="ident?i=__net_init">__net_init</a> <a href="ident?i=igmp_net_init">igmp_net_init</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>)
<a name="L2717" href="source/net/ipv4/igmp.c#L2717">2717</a> {
<a name="L2718" href="source/net/ipv4/igmp.c#L2718">2718</a>         struct <a href="ident?i=proc_dir_entry">proc_dir_entry</a> *pde;
<a name="L2719" href="source/net/ipv4/igmp.c#L2719">2719</a>         int <a href="ident?i=err">err</a>;
<a name="L2720" href="source/net/ipv4/igmp.c#L2720">2720</a> 
<a name="L2721" href="source/net/ipv4/igmp.c#L2721">2721</a>         pde = <a href="ident?i=proc_create">proc_create</a>(<i>"igmp"</i>, <a href="ident?i=S_IRUGO">S_IRUGO</a>, <a href="ident?i=net">net</a>-&gt;proc_net, &amp;<a href="ident?i=igmp_mc_seq_fops">igmp_mc_seq_fops</a>);
<a name="L2722" href="source/net/ipv4/igmp.c#L2722">2722</a>         if (!pde)
<a name="L2723" href="source/net/ipv4/igmp.c#L2723">2723</a>                 goto out_igmp;
<a name="L2724" href="source/net/ipv4/igmp.c#L2724">2724</a>         pde = <a href="ident?i=proc_create">proc_create</a>(<i>"mcfilter"</i>, <a href="ident?i=S_IRUGO">S_IRUGO</a>, <a href="ident?i=net">net</a>-&gt;proc_net,
<a name="L2725" href="source/net/ipv4/igmp.c#L2725">2725</a>                           &amp;<a href="ident?i=igmp_mcf_seq_fops">igmp_mcf_seq_fops</a>);
<a name="L2726" href="source/net/ipv4/igmp.c#L2726">2726</a>         if (!pde)
<a name="L2727" href="source/net/ipv4/igmp.c#L2727">2727</a>                 goto out_mcfilter;
<a name="L2728" href="source/net/ipv4/igmp.c#L2728">2728</a>         <a href="ident?i=err">err</a> = <a href="ident?i=inet_ctl_sock_create">inet_ctl_sock_create</a>(&amp;<a href="ident?i=net">net</a>-&gt;ipv4.mc_autojoin_sk, <a href="ident?i=AF_INET">AF_INET</a>,
<a name="L2729" href="source/net/ipv4/igmp.c#L2729">2729</a>                                    SOCK_DGRAM, 0, <a href="ident?i=net">net</a>);
<a name="L2730" href="source/net/ipv4/igmp.c#L2730">2730</a>         if (<a href="ident?i=err">err</a> &lt; 0) {
<a name="L2731" href="source/net/ipv4/igmp.c#L2731">2731</a>                 <a href="ident?i=pr_err">pr_err</a>(<i>"Failed to initialize the IGMP autojoin socket (err %d)\n"</i>,
<a name="L2732" href="source/net/ipv4/igmp.c#L2732">2732</a>                        <a href="ident?i=err">err</a>);
<a name="L2733" href="source/net/ipv4/igmp.c#L2733">2733</a>                 goto out_sock;
<a name="L2734" href="source/net/ipv4/igmp.c#L2734">2734</a>         }
<a name="L2735" href="source/net/ipv4/igmp.c#L2735">2735</a> 
<a name="L2736" href="source/net/ipv4/igmp.c#L2736">2736</a>         return 0;
<a name="L2737" href="source/net/ipv4/igmp.c#L2737">2737</a> 
<a name="L2738" href="source/net/ipv4/igmp.c#L2738">2738</a> out_sock:
<a name="L2739" href="source/net/ipv4/igmp.c#L2739">2739</a>         <a href="ident?i=remove_proc_entry">remove_proc_entry</a>(<i>"mcfilter"</i>, <a href="ident?i=net">net</a>-&gt;proc_net);
<a name="L2740" href="source/net/ipv4/igmp.c#L2740">2740</a> out_mcfilter:
<a name="L2741" href="source/net/ipv4/igmp.c#L2741">2741</a>         <a href="ident?i=remove_proc_entry">remove_proc_entry</a>(<i>"igmp"</i>, <a href="ident?i=net">net</a>-&gt;proc_net);
<a name="L2742" href="source/net/ipv4/igmp.c#L2742">2742</a> out_igmp:
<a name="L2743" href="source/net/ipv4/igmp.c#L2743">2743</a>         return -<a href="ident?i=ENOMEM">ENOMEM</a>;
<a name="L2744" href="source/net/ipv4/igmp.c#L2744">2744</a> }
<a name="L2745" href="source/net/ipv4/igmp.c#L2745">2745</a> 
<a name="L2746" href="source/net/ipv4/igmp.c#L2746">2746</a> static void <a href="ident?i=__net_exit">__net_exit</a> <a href="ident?i=igmp_net_exit">igmp_net_exit</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>)
<a name="L2747" href="source/net/ipv4/igmp.c#L2747">2747</a> {
<a name="L2748" href="source/net/ipv4/igmp.c#L2748">2748</a>         <a href="ident?i=remove_proc_entry">remove_proc_entry</a>(<i>"mcfilter"</i>, <a href="ident?i=net">net</a>-&gt;proc_net);
<a name="L2749" href="source/net/ipv4/igmp.c#L2749">2749</a>         <a href="ident?i=remove_proc_entry">remove_proc_entry</a>(<i>"igmp"</i>, <a href="ident?i=net">net</a>-&gt;proc_net);
<a name="L2750" href="source/net/ipv4/igmp.c#L2750">2750</a>         <a href="ident?i=inet_ctl_sock_destroy">inet_ctl_sock_destroy</a>(<a href="ident?i=net">net</a>-&gt;ipv4.mc_autojoin_sk);
<a name="L2751" href="source/net/ipv4/igmp.c#L2751">2751</a> }
<a name="L2752" href="source/net/ipv4/igmp.c#L2752">2752</a> 
<a name="L2753" href="source/net/ipv4/igmp.c#L2753">2753</a> static struct <a href="ident?i=pernet_operations">pernet_operations</a> <a href="ident?i=igmp_net_ops">igmp_net_ops</a> = {
<a name="L2754" href="source/net/ipv4/igmp.c#L2754">2754</a>         .<a href="ident?i=init">init</a> = <a href="ident?i=igmp_net_init">igmp_net_init</a>,
<a name="L2755" href="source/net/ipv4/igmp.c#L2755">2755</a>         .<a href="ident?i=exit">exit</a> = <a href="ident?i=igmp_net_exit">igmp_net_exit</a>,
<a name="L2756" href="source/net/ipv4/igmp.c#L2756">2756</a> };
<a name="L2757" href="source/net/ipv4/igmp.c#L2757">2757</a> #endif
<a name="L2758" href="source/net/ipv4/igmp.c#L2758">2758</a> 
<a name="L2759" href="source/net/ipv4/igmp.c#L2759">2759</a> static int <a href="ident?i=igmp_netdev_event">igmp_netdev_event</a>(struct <a href="ident?i=notifier_block">notifier_block</a> *<a href="ident?i=this">this</a>,
<a name="L2760" href="source/net/ipv4/igmp.c#L2760">2760</a>                              unsigned long <a href="ident?i=event">event</a>, void *<a href="ident?i=ptr">ptr</a>)
<a name="L2761" href="source/net/ipv4/igmp.c#L2761">2761</a> {
<a name="L2762" href="source/net/ipv4/igmp.c#L2762">2762</a>         struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a> = <a href="ident?i=netdev_notifier_info_to_dev">netdev_notifier_info_to_dev</a>(<a href="ident?i=ptr">ptr</a>);
<a name="L2763" href="source/net/ipv4/igmp.c#L2763">2763</a>         struct <a href="ident?i=in_device">in_device</a> *in_dev;
<a name="L2764" href="source/net/ipv4/igmp.c#L2764">2764</a> 
<a name="L2765" href="source/net/ipv4/igmp.c#L2765">2765</a>         switch (<a href="ident?i=event">event</a>) {
<a name="L2766" href="source/net/ipv4/igmp.c#L2766">2766</a>         case <a href="ident?i=NETDEV_RESEND_IGMP">NETDEV_RESEND_IGMP</a>:
<a name="L2767" href="source/net/ipv4/igmp.c#L2767">2767</a>                 in_dev = <a href="ident?i=__in_dev_get_rtnl">__in_dev_get_rtnl</a>(<a href="ident?i=dev">dev</a>);
<a name="L2768" href="source/net/ipv4/igmp.c#L2768">2768</a>                 if (in_dev)
<a name="L2769" href="source/net/ipv4/igmp.c#L2769">2769</a>                         <a href="ident?i=ip_mc_rejoin_groups">ip_mc_rejoin_groups</a>(in_dev);
<a name="L2770" href="source/net/ipv4/igmp.c#L2770">2770</a>                 break;
<a name="L2771" href="source/net/ipv4/igmp.c#L2771">2771</a>         default:
<a name="L2772" href="source/net/ipv4/igmp.c#L2772">2772</a>                 break;
<a name="L2773" href="source/net/ipv4/igmp.c#L2773">2773</a>         }
<a name="L2774" href="source/net/ipv4/igmp.c#L2774">2774</a>         return <a href="ident?i=NOTIFY_DONE">NOTIFY_DONE</a>;
<a name="L2775" href="source/net/ipv4/igmp.c#L2775">2775</a> }
<a name="L2776" href="source/net/ipv4/igmp.c#L2776">2776</a> 
<a name="L2777" href="source/net/ipv4/igmp.c#L2777">2777</a> static struct <a href="ident?i=notifier_block">notifier_block</a> <a href="ident?i=igmp_notifier">igmp_notifier</a> = {
<a name="L2778" href="source/net/ipv4/igmp.c#L2778">2778</a>         .notifier_call = <a href="ident?i=igmp_netdev_event">igmp_netdev_event</a>,
<a name="L2779" href="source/net/ipv4/igmp.c#L2779">2779</a> };
<a name="L2780" href="source/net/ipv4/igmp.c#L2780">2780</a> 
<a name="L2781" href="source/net/ipv4/igmp.c#L2781">2781</a> int <a href="ident?i=__init">__init</a> <a href="ident?i=igmp_mc_init">igmp_mc_init</a>(void)
<a name="L2782" href="source/net/ipv4/igmp.c#L2782">2782</a> {
<a name="L2783" href="source/net/ipv4/igmp.c#L2783">2783</a> #if defined(CONFIG_PROC_FS)
<a name="L2784" href="source/net/ipv4/igmp.c#L2784">2784</a>         int <a href="ident?i=err">err</a>;
<a name="L2785" href="source/net/ipv4/igmp.c#L2785">2785</a> 
<a name="L2786" href="source/net/ipv4/igmp.c#L2786">2786</a>         <a href="ident?i=err">err</a> = <a href="ident?i=register_pernet_subsys">register_pernet_subsys</a>(&amp;<a href="ident?i=igmp_net_ops">igmp_net_ops</a>);
<a name="L2787" href="source/net/ipv4/igmp.c#L2787">2787</a>         if (<a href="ident?i=err">err</a>)
<a name="L2788" href="source/net/ipv4/igmp.c#L2788">2788</a>                 return <a href="ident?i=err">err</a>;
<a name="L2789" href="source/net/ipv4/igmp.c#L2789">2789</a>         <a href="ident?i=err">err</a> = <a href="ident?i=register_netdevice_notifier">register_netdevice_notifier</a>(&amp;<a href="ident?i=igmp_notifier">igmp_notifier</a>);
<a name="L2790" href="source/net/ipv4/igmp.c#L2790">2790</a>         if (<a href="ident?i=err">err</a>)
<a name="L2791" href="source/net/ipv4/igmp.c#L2791">2791</a>                 goto reg_notif_fail;
<a name="L2792" href="source/net/ipv4/igmp.c#L2792">2792</a>         return 0;
<a name="L2793" href="source/net/ipv4/igmp.c#L2793">2793</a> 
<a name="L2794" href="source/net/ipv4/igmp.c#L2794">2794</a> reg_notif_fail:
<a name="L2795" href="source/net/ipv4/igmp.c#L2795">2795</a>         <a href="ident?i=unregister_pernet_subsys">unregister_pernet_subsys</a>(&amp;<a href="ident?i=igmp_net_ops">igmp_net_ops</a>);
<a name="L2796" href="source/net/ipv4/igmp.c#L2796">2796</a>         return <a href="ident?i=err">err</a>;
<a name="L2797" href="source/net/ipv4/igmp.c#L2797">2797</a> #else
<a name="L2798" href="source/net/ipv4/igmp.c#L2798">2798</a>         return <a href="ident?i=register_netdevice_notifier">register_netdevice_notifier</a>(&amp;<a href="ident?i=igmp_notifier">igmp_notifier</a>);
<a name="L2799" href="source/net/ipv4/igmp.c#L2799">2799</a> #endif
<a name="L2800" href="source/net/ipv4/igmp.c#L2800">2800</a> }
<a name="L2801" href="source/net/ipv4/igmp.c#L2801">2801</a> </pre></div><p>
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
