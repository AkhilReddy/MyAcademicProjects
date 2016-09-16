<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title>Linux/net/ipv4/icmp.c - Linux Cross Reference - Free Electrons</title>
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
		 &nbsp;&bull;&nbsp;<b><i>source navigation</i></b> &nbsp;&bull;&nbsp;<a href="diff/net/ipv4/icmp.c">diff markup</a> &nbsp;&bull;&nbsp;<a href="ident">identifier search</a> &nbsp;&bull;&nbsp;<a href="search">freetext search</a> &nbsp;&bull;&nbsp;
		</p>
	</div>
</div>

<div id="topbar">
  
  <p>Version: &nbsp;<a href="source/net/ipv4/icmp.c?v=2.0.40">2.0.40</a>&nbsp;<a href="source/net/ipv4/icmp.c?v=2.2.26">2.2.26</a>&nbsp;<a href="source/net/ipv4/icmp.c?v=2.4.37">2.4.37</a>&nbsp;<a href="source/net/ipv4/icmp.c?v=3.5">3.5</a>&nbsp;<a href="source/net/ipv4/icmp.c?v=3.6">3.6</a>&nbsp;<a href="source/net/ipv4/icmp.c?v=3.7">3.7</a>&nbsp;<a href="source/net/ipv4/icmp.c?v=3.8">3.8</a>&nbsp;<a href="source/net/ipv4/icmp.c?v=3.9">3.9</a>&nbsp;<a href="source/net/ipv4/icmp.c?v=3.10">3.10</a>&nbsp;<a href="source/net/ipv4/icmp.c?v=3.11">3.11</a>&nbsp;<a href="source/net/ipv4/icmp.c?v=3.12">3.12</a>&nbsp;<a href="source/net/ipv4/icmp.c?v=3.13">3.13</a>&nbsp;<a href="source/net/ipv4/icmp.c?v=3.14">3.14</a>&nbsp;<a href="source/net/ipv4/icmp.c?v=3.15">3.15</a>&nbsp;<a href="source/net/ipv4/icmp.c?v=3.16">3.16</a>&nbsp;<a href="source/net/ipv4/icmp.c?v=3.17">3.17</a>&nbsp;<a href="source/net/ipv4/icmp.c?v=3.18">3.18</a>&nbsp;<a href="source/net/ipv4/icmp.c?v=3.19">3.19</a>&nbsp;<a href="source/net/ipv4/icmp.c?v=4.0">4.0</a>&nbsp;<b><i>4.1</i></b></p>
  
</div>

<h1><a href="source/">Linux</a>/<a href="source/net/">net</a>/<a href="source/net/ipv4/">ipv4</a>/<a href="source/net/ipv4/icmp.c">icmp.c</a></h1>
<div id="lxrcode"><pre>  <a name="L1" href="source/net/ipv4/icmp.c#L1">1</a> <b><i>/*</i></b>
  <a name="L2" href="source/net/ipv4/icmp.c#L2">2</a> <b><i> *      NET3:   Implementation of the ICMP protocol layer.</i></b>
  <a name="L3" href="source/net/ipv4/icmp.c#L3">3</a> <b><i> *</i></b>
  <a name="L4" href="source/net/ipv4/icmp.c#L4">4</a> <b><i> *              Alan Cox, &lt;alan@lxorguk.ukuu.org.uk&gt;</i></b>
  <a name="L5" href="source/net/ipv4/icmp.c#L5">5</a> <b><i> *</i></b>
  <a name="L6" href="source/net/ipv4/icmp.c#L6">6</a> <b><i> *      This program is free software; you can redistribute it and/or</i></b>
  <a name="L7" href="source/net/ipv4/icmp.c#L7">7</a> <b><i> *      modify it under the terms of the GNU General Public License</i></b>
  <a name="L8" href="source/net/ipv4/icmp.c#L8">8</a> <b><i> *      as published by the Free Software Foundation; either version</i></b>
  <a name="L9" href="source/net/ipv4/icmp.c#L9">9</a> <b><i> *      2 of the License, or (at your option) any later version.</i></b>
 <a name="L10" href="source/net/ipv4/icmp.c#L10">10</a> <b><i> *</i></b>
 <a name="L11" href="source/net/ipv4/icmp.c#L11">11</a> <b><i> *      Some of the function names and the icmp unreach table for this</i></b>
 <a name="L12" href="source/net/ipv4/icmp.c#L12">12</a> <b><i> *      module were derived from [icmp.c 1.0.11 06/02/93] by</i></b>
 <a name="L13" href="source/net/ipv4/icmp.c#L13">13</a> <b><i> *      Ross Biro, Fred N. van Kempen, Mark Evans, Alan Cox, Gerhard Koerting.</i></b>
 <a name="L14" href="source/net/ipv4/icmp.c#L14">14</a> <b><i> *      Other than that this module is a complete rewrite.</i></b>
 <a name="L15" href="source/net/ipv4/icmp.c#L15">15</a> <b><i> *</i></b>
 <a name="L16" href="source/net/ipv4/icmp.c#L16">16</a> <b><i> *      Fixes:</i></b>
 <a name="L17" href="source/net/ipv4/icmp.c#L17">17</a> <b><i> *      Clemens Fruhwirth       :       introduce global icmp rate limiting</i></b>
 <a name="L18" href="source/net/ipv4/icmp.c#L18">18</a> <b><i> *                                      with icmp type masking ability instead</i></b>
 <a name="L19" href="source/net/ipv4/icmp.c#L19">19</a> <b><i> *                                      of broken per type icmp timeouts.</i></b>
 <a name="L20" href="source/net/ipv4/icmp.c#L20">20</a> <b><i> *              Mike Shaver     :       RFC1122 checks.</i></b>
 <a name="L21" href="source/net/ipv4/icmp.c#L21">21</a> <b><i> *              Alan Cox        :       Multicast ping reply as self.</i></b>
 <a name="L22" href="source/net/ipv4/icmp.c#L22">22</a> <b><i> *              Alan Cox        :       Fix atomicity lockup in ip_build_xmit</i></b>
 <a name="L23" href="source/net/ipv4/icmp.c#L23">23</a> <b><i> *                                      call.</i></b>
 <a name="L24" href="source/net/ipv4/icmp.c#L24">24</a> <b><i> *              Alan Cox        :       Added 216,128 byte paths to the MTU</i></b>
 <a name="L25" href="source/net/ipv4/icmp.c#L25">25</a> <b><i> *                                      code.</i></b>
 <a name="L26" href="source/net/ipv4/icmp.c#L26">26</a> <b><i> *              Martin Mares    :       RFC1812 checks.</i></b>
 <a name="L27" href="source/net/ipv4/icmp.c#L27">27</a> <b><i> *              Martin Mares    :       Can be configured to follow redirects</i></b>
 <a name="L28" href="source/net/ipv4/icmp.c#L28">28</a> <b><i> *                                      if acting as a router _without_ a</i></b>
 <a name="L29" href="source/net/ipv4/icmp.c#L29">29</a> <b><i> *                                      routing protocol (RFC 1812).</i></b>
 <a name="L30" href="source/net/ipv4/icmp.c#L30">30</a> <b><i> *              Martin Mares    :       Echo requests may be configured to</i></b>
 <a name="L31" href="source/net/ipv4/icmp.c#L31">31</a> <b><i> *                                      be ignored (RFC 1812).</i></b>
 <a name="L32" href="source/net/ipv4/icmp.c#L32">32</a> <b><i> *              Martin Mares    :       Limitation of ICMP error message</i></b>
 <a name="L33" href="source/net/ipv4/icmp.c#L33">33</a> <b><i> *                                      transmit rate (RFC 1812).</i></b>
 <a name="L34" href="source/net/ipv4/icmp.c#L34">34</a> <b><i> *              Martin Mares    :       TOS and Precedence set correctly</i></b>
 <a name="L35" href="source/net/ipv4/icmp.c#L35">35</a> <b><i> *                                      (RFC 1812).</i></b>
 <a name="L36" href="source/net/ipv4/icmp.c#L36">36</a> <b><i> *              Martin Mares    :       Now copying as much data from the</i></b>
 <a name="L37" href="source/net/ipv4/icmp.c#L37">37</a> <b><i> *                                      original packet as we can without</i></b>
 <a name="L38" href="source/net/ipv4/icmp.c#L38">38</a> <b><i> *                                      exceeding 576 bytes (RFC 1812).</i></b>
 <a name="L39" href="source/net/ipv4/icmp.c#L39">39</a> <b><i> *      Willy Konynenberg       :       Transparent proxying support.</i></b>
 <a name="L40" href="source/net/ipv4/icmp.c#L40">40</a> <b><i> *              Keith Owens     :       RFC1191 correction for 4.2BSD based</i></b>
 <a name="L41" href="source/net/ipv4/icmp.c#L41">41</a> <b><i> *                                      path MTU bug.</i></b>
 <a name="L42" href="source/net/ipv4/icmp.c#L42">42</a> <b><i> *              Thomas Quinot   :       ICMP Dest Unreach codes up to 15 are</i></b>
 <a name="L43" href="source/net/ipv4/icmp.c#L43">43</a> <b><i> *                                      valid (RFC 1812).</i></b>
 <a name="L44" href="source/net/ipv4/icmp.c#L44">44</a> <b><i> *              Andi Kleen      :       Check all packet lengths properly</i></b>
 <a name="L45" href="source/net/ipv4/icmp.c#L45">45</a> <b><i> *                                      and moved all kfree_skb() up to</i></b>
 <a name="L46" href="source/net/ipv4/icmp.c#L46">46</a> <b><i> *                                      icmp_rcv.</i></b>
 <a name="L47" href="source/net/ipv4/icmp.c#L47">47</a> <b><i> *              Andi Kleen      :       Move the rate limit bookkeeping</i></b>
 <a name="L48" href="source/net/ipv4/icmp.c#L48">48</a> <b><i> *                                      into the dest entry and use a token</i></b>
 <a name="L49" href="source/net/ipv4/icmp.c#L49">49</a> <b><i> *                                      bucket filter (thanks to ANK). Make</i></b>
 <a name="L50" href="source/net/ipv4/icmp.c#L50">50</a> <b><i> *                                      the rates sysctl configurable.</i></b>
 <a name="L51" href="source/net/ipv4/icmp.c#L51">51</a> <b><i> *              Yu Tianli       :       Fixed two ugly bugs in icmp_send</i></b>
 <a name="L52" href="source/net/ipv4/icmp.c#L52">52</a> <b><i> *                                      - IP option length was accounted wrongly</i></b>
 <a name="L53" href="source/net/ipv4/icmp.c#L53">53</a> <b><i> *                                      - ICMP header length was not accounted</i></b>
 <a name="L54" href="source/net/ipv4/icmp.c#L54">54</a> <b><i> *                                        at all.</i></b>
 <a name="L55" href="source/net/ipv4/icmp.c#L55">55</a> <b><i> *              Tristan Greaves :       Added sysctl option to ignore bogus</i></b>
 <a name="L56" href="source/net/ipv4/icmp.c#L56">56</a> <b><i> *                                      broadcast responses from broken routers.</i></b>
 <a name="L57" href="source/net/ipv4/icmp.c#L57">57</a> <b><i> *</i></b>
 <a name="L58" href="source/net/ipv4/icmp.c#L58">58</a> <b><i> * To Fix:</i></b>
 <a name="L59" href="source/net/ipv4/icmp.c#L59">59</a> <b><i> *</i></b>
 <a name="L60" href="source/net/ipv4/icmp.c#L60">60</a> <b><i> *      - Should use skb_pull() instead of all the manual checking.</i></b>
 <a name="L61" href="source/net/ipv4/icmp.c#L61">61</a> <b><i> *        This would also greatly simply some upper layer error handlers. --AK</i></b>
 <a name="L62" href="source/net/ipv4/icmp.c#L62">62</a> <b><i> *</i></b>
 <a name="L63" href="source/net/ipv4/icmp.c#L63">63</a> <b><i> */</i></b>
 <a name="L64" href="source/net/ipv4/icmp.c#L64">64</a> 
 <a name="L65" href="source/net/ipv4/icmp.c#L65">65</a> #define <a href="ident?i=pr_fmt">pr_fmt</a>(<a href="ident?i=fmt">fmt</a>) KBUILD_MODNAME <i>": "</i> <a href="ident?i=fmt">fmt</a>
 <a name="L66" href="source/net/ipv4/icmp.c#L66">66</a> 
 <a name="L67" href="source/net/ipv4/icmp.c#L67">67</a> #include &lt;linux/module.h&gt;
 <a name="L68" href="source/net/ipv4/icmp.c#L68">68</a> #include &lt;linux/types.h&gt;
 <a name="L69" href="source/net/ipv4/icmp.c#L69">69</a> #include &lt;linux/jiffies.h&gt;
 <a name="L70" href="source/net/ipv4/icmp.c#L70">70</a> #include &lt;linux/kernel.h&gt;
 <a name="L71" href="source/net/ipv4/icmp.c#L71">71</a> #include &lt;linux/fcntl.h&gt;
 <a name="L72" href="source/net/ipv4/icmp.c#L72">72</a> #include &lt;linux/socket.h&gt;
 <a name="L73" href="source/net/ipv4/icmp.c#L73">73</a> #include &lt;linux/in.h&gt;
 <a name="L74" href="source/net/ipv4/icmp.c#L74">74</a> #include &lt;linux/inet.h&gt;
 <a name="L75" href="source/net/ipv4/icmp.c#L75">75</a> #include &lt;linux/inetdevice.h&gt;
 <a name="L76" href="source/net/ipv4/icmp.c#L76">76</a> #include &lt;linux/netdevice.h&gt;
 <a name="L77" href="source/net/ipv4/icmp.c#L77">77</a> #include &lt;linux/string.h&gt;
 <a name="L78" href="source/net/ipv4/icmp.c#L78">78</a> #include &lt;linux/netfilter_ipv4.h&gt;
 <a name="L79" href="source/net/ipv4/icmp.c#L79">79</a> #include &lt;linux/slab.h&gt;
 <a name="L80" href="source/net/ipv4/icmp.c#L80">80</a> #include &lt;net/snmp.h&gt;
 <a name="L81" href="source/net/ipv4/icmp.c#L81">81</a> #include &lt;net/ip.h&gt;
 <a name="L82" href="source/net/ipv4/icmp.c#L82">82</a> #include &lt;net/route.h&gt;
 <a name="L83" href="source/net/ipv4/icmp.c#L83">83</a> #include &lt;net/protocol.h&gt;
 <a name="L84" href="source/net/ipv4/icmp.c#L84">84</a> #include &lt;net/icmp.h&gt;
 <a name="L85" href="source/net/ipv4/icmp.c#L85">85</a> #include &lt;net/tcp.h&gt;
 <a name="L86" href="source/net/ipv4/icmp.c#L86">86</a> #include &lt;net/udp.h&gt;
 <a name="L87" href="source/net/ipv4/icmp.c#L87">87</a> #include &lt;net/raw.h&gt;
 <a name="L88" href="source/net/ipv4/icmp.c#L88">88</a> #include &lt;net/ping.h&gt;
 <a name="L89" href="source/net/ipv4/icmp.c#L89">89</a> #include &lt;linux/skbuff.h&gt;
 <a name="L90" href="source/net/ipv4/icmp.c#L90">90</a> #include &lt;net/sock.h&gt;
 <a name="L91" href="source/net/ipv4/icmp.c#L91">91</a> #include &lt;linux/errno.h&gt;
 <a name="L92" href="source/net/ipv4/icmp.c#L92">92</a> #include &lt;linux/timer.h&gt;
 <a name="L93" href="source/net/ipv4/icmp.c#L93">93</a> #include &lt;linux/init.h&gt;
 <a name="L94" href="source/net/ipv4/icmp.c#L94">94</a> #include &lt;asm/uaccess.h&gt;
 <a name="L95" href="source/net/ipv4/icmp.c#L95">95</a> #include &lt;net/checksum.h&gt;
 <a name="L96" href="source/net/ipv4/icmp.c#L96">96</a> #include &lt;net/xfrm.h&gt;
 <a name="L97" href="source/net/ipv4/icmp.c#L97">97</a> #include &lt;net/inet_common.h&gt;
 <a name="L98" href="source/net/ipv4/icmp.c#L98">98</a> #include &lt;net/ip_fib.h&gt;
 <a name="L99" href="source/net/ipv4/icmp.c#L99">99</a> 
<a name="L100" href="source/net/ipv4/icmp.c#L100">100</a> <b><i>/*</i></b>
<a name="L101" href="source/net/ipv4/icmp.c#L101">101</a> <b><i> *      Build xmit assembly blocks</i></b>
<a name="L102" href="source/net/ipv4/icmp.c#L102">102</a> <b><i> */</i></b>
<a name="L103" href="source/net/ipv4/icmp.c#L103">103</a> 
<a name="L104" href="source/net/ipv4/icmp.c#L104">104</a> struct <a href="ident?i=icmp_bxm">icmp_bxm</a> {
<a name="L105" href="source/net/ipv4/icmp.c#L105">105</a>         struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>;
<a name="L106" href="source/net/ipv4/icmp.c#L106">106</a>         int <a href="ident?i=offset">offset</a>;
<a name="L107" href="source/net/ipv4/icmp.c#L107">107</a>         int <a href="ident?i=data_len">data_len</a>;
<a name="L108" href="source/net/ipv4/icmp.c#L108">108</a> 
<a name="L109" href="source/net/ipv4/icmp.c#L109">109</a>         struct {
<a name="L110" href="source/net/ipv4/icmp.c#L110">110</a>                 struct <a href="ident?i=icmphdr">icmphdr</a> icmph;
<a name="L111" href="source/net/ipv4/icmp.c#L111">111</a>                 <a href="ident?i=__be32">__be32</a>         times[3];
<a name="L112" href="source/net/ipv4/icmp.c#L112">112</a>         } <a href="ident?i=data">data</a>;
<a name="L113" href="source/net/ipv4/icmp.c#L113">113</a>         int head_len;
<a name="L114" href="source/net/ipv4/icmp.c#L114">114</a>         struct <a href="ident?i=ip_options_data">ip_options_data</a> replyopts;
<a name="L115" href="source/net/ipv4/icmp.c#L115">115</a> };
<a name="L116" href="source/net/ipv4/icmp.c#L116">116</a> 
<a name="L117" href="source/net/ipv4/icmp.c#L117">117</a> <b><i>/* An array of errno for error messages from dest unreach. */</i></b>
<a name="L118" href="source/net/ipv4/icmp.c#L118">118</a> <b><i>/* RFC 1122: 3.2.2.1 States that NET_UNREACH, HOST_UNREACH and SR_FAILED MUST be considered 'transient errs'. */</i></b>
<a name="L119" href="source/net/ipv4/icmp.c#L119">119</a> 
<a name="L120" href="source/net/ipv4/icmp.c#L120">120</a> const struct <a href="ident?i=icmp_err">icmp_err</a> <a href="ident?i=icmp_err_convert">icmp_err_convert</a>[] = {
<a name="L121" href="source/net/ipv4/icmp.c#L121">121</a>         {
<a name="L122" href="source/net/ipv4/icmp.c#L122">122</a>                 .<a href="ident?i=errno">errno</a> = <a href="ident?i=ENETUNREACH">ENETUNREACH</a>,   <b><i>/* ICMP_NET_UNREACH */</i></b>
<a name="L123" href="source/net/ipv4/icmp.c#L123">123</a>                 .<a href="ident?i=fatal">fatal</a> = 0,
<a name="L124" href="source/net/ipv4/icmp.c#L124">124</a>         },
<a name="L125" href="source/net/ipv4/icmp.c#L125">125</a>         {
<a name="L126" href="source/net/ipv4/icmp.c#L126">126</a>                 .<a href="ident?i=errno">errno</a> = <a href="ident?i=EHOSTUNREACH">EHOSTUNREACH</a>,  <b><i>/* ICMP_HOST_UNREACH */</i></b>
<a name="L127" href="source/net/ipv4/icmp.c#L127">127</a>                 .<a href="ident?i=fatal">fatal</a> = 0,
<a name="L128" href="source/net/ipv4/icmp.c#L128">128</a>         },
<a name="L129" href="source/net/ipv4/icmp.c#L129">129</a>         {
<a name="L130" href="source/net/ipv4/icmp.c#L130">130</a>                 .<a href="ident?i=errno">errno</a> = <a href="ident?i=ENOPROTOOPT">ENOPROTOOPT</a>    <b><i>/* ICMP_PROT_UNREACH */</i></b>,
<a name="L131" href="source/net/ipv4/icmp.c#L131">131</a>                 .<a href="ident?i=fatal">fatal</a> = 1,
<a name="L132" href="source/net/ipv4/icmp.c#L132">132</a>         },
<a name="L133" href="source/net/ipv4/icmp.c#L133">133</a>         {
<a name="L134" href="source/net/ipv4/icmp.c#L134">134</a>                 .<a href="ident?i=errno">errno</a> = <a href="ident?i=ECONNREFUSED">ECONNREFUSED</a>,  <b><i>/* ICMP_PORT_UNREACH */</i></b>
<a name="L135" href="source/net/ipv4/icmp.c#L135">135</a>                 .<a href="ident?i=fatal">fatal</a> = 1,
<a name="L136" href="source/net/ipv4/icmp.c#L136">136</a>         },
<a name="L137" href="source/net/ipv4/icmp.c#L137">137</a>         {
<a name="L138" href="source/net/ipv4/icmp.c#L138">138</a>                 .<a href="ident?i=errno">errno</a> = <a href="ident?i=EMSGSIZE">EMSGSIZE</a>,      <b><i>/* ICMP_FRAG_NEEDED */</i></b>
<a name="L139" href="source/net/ipv4/icmp.c#L139">139</a>                 .<a href="ident?i=fatal">fatal</a> = 0,
<a name="L140" href="source/net/ipv4/icmp.c#L140">140</a>         },
<a name="L141" href="source/net/ipv4/icmp.c#L141">141</a>         {
<a name="L142" href="source/net/ipv4/icmp.c#L142">142</a>                 .<a href="ident?i=errno">errno</a> = <a href="ident?i=EOPNOTSUPP">EOPNOTSUPP</a>,    <b><i>/* ICMP_SR_FAILED */</i></b>
<a name="L143" href="source/net/ipv4/icmp.c#L143">143</a>                 .<a href="ident?i=fatal">fatal</a> = 0,
<a name="L144" href="source/net/ipv4/icmp.c#L144">144</a>         },
<a name="L145" href="source/net/ipv4/icmp.c#L145">145</a>         {
<a name="L146" href="source/net/ipv4/icmp.c#L146">146</a>                 .<a href="ident?i=errno">errno</a> = <a href="ident?i=ENETUNREACH">ENETUNREACH</a>,   <b><i>/* ICMP_NET_UNKNOWN */</i></b>
<a name="L147" href="source/net/ipv4/icmp.c#L147">147</a>                 .<a href="ident?i=fatal">fatal</a> = 1,
<a name="L148" href="source/net/ipv4/icmp.c#L148">148</a>         },
<a name="L149" href="source/net/ipv4/icmp.c#L149">149</a>         {
<a name="L150" href="source/net/ipv4/icmp.c#L150">150</a>                 .<a href="ident?i=errno">errno</a> = <a href="ident?i=EHOSTDOWN">EHOSTDOWN</a>,     <b><i>/* ICMP_HOST_UNKNOWN */</i></b>
<a name="L151" href="source/net/ipv4/icmp.c#L151">151</a>                 .<a href="ident?i=fatal">fatal</a> = 1,
<a name="L152" href="source/net/ipv4/icmp.c#L152">152</a>         },
<a name="L153" href="source/net/ipv4/icmp.c#L153">153</a>         {
<a name="L154" href="source/net/ipv4/icmp.c#L154">154</a>                 .<a href="ident?i=errno">errno</a> = <a href="ident?i=ENONET">ENONET</a>,        <b><i>/* ICMP_HOST_ISOLATED */</i></b>
<a name="L155" href="source/net/ipv4/icmp.c#L155">155</a>                 .<a href="ident?i=fatal">fatal</a> = 1,
<a name="L156" href="source/net/ipv4/icmp.c#L156">156</a>         },
<a name="L157" href="source/net/ipv4/icmp.c#L157">157</a>         {
<a name="L158" href="source/net/ipv4/icmp.c#L158">158</a>                 .<a href="ident?i=errno">errno</a> = <a href="ident?i=ENETUNREACH">ENETUNREACH</a>,   <b><i>/* ICMP_NET_ANO */</i></b>
<a name="L159" href="source/net/ipv4/icmp.c#L159">159</a>                 .<a href="ident?i=fatal">fatal</a> = 1,
<a name="L160" href="source/net/ipv4/icmp.c#L160">160</a>         },
<a name="L161" href="source/net/ipv4/icmp.c#L161">161</a>         {
<a name="L162" href="source/net/ipv4/icmp.c#L162">162</a>                 .<a href="ident?i=errno">errno</a> = <a href="ident?i=EHOSTUNREACH">EHOSTUNREACH</a>,  <b><i>/* ICMP_HOST_ANO */</i></b>
<a name="L163" href="source/net/ipv4/icmp.c#L163">163</a>                 .<a href="ident?i=fatal">fatal</a> = 1,
<a name="L164" href="source/net/ipv4/icmp.c#L164">164</a>         },
<a name="L165" href="source/net/ipv4/icmp.c#L165">165</a>         {
<a name="L166" href="source/net/ipv4/icmp.c#L166">166</a>                 .<a href="ident?i=errno">errno</a> = <a href="ident?i=ENETUNREACH">ENETUNREACH</a>,   <b><i>/* ICMP_NET_UNR_TOS */</i></b>
<a name="L167" href="source/net/ipv4/icmp.c#L167">167</a>                 .<a href="ident?i=fatal">fatal</a> = 0,
<a name="L168" href="source/net/ipv4/icmp.c#L168">168</a>         },
<a name="L169" href="source/net/ipv4/icmp.c#L169">169</a>         {
<a name="L170" href="source/net/ipv4/icmp.c#L170">170</a>                 .<a href="ident?i=errno">errno</a> = <a href="ident?i=EHOSTUNREACH">EHOSTUNREACH</a>,  <b><i>/* ICMP_HOST_UNR_TOS */</i></b>
<a name="L171" href="source/net/ipv4/icmp.c#L171">171</a>                 .<a href="ident?i=fatal">fatal</a> = 0,
<a name="L172" href="source/net/ipv4/icmp.c#L172">172</a>         },
<a name="L173" href="source/net/ipv4/icmp.c#L173">173</a>         {
<a name="L174" href="source/net/ipv4/icmp.c#L174">174</a>                 .<a href="ident?i=errno">errno</a> = <a href="ident?i=EHOSTUNREACH">EHOSTUNREACH</a>,  <b><i>/* ICMP_PKT_FILTERED */</i></b>
<a name="L175" href="source/net/ipv4/icmp.c#L175">175</a>                 .<a href="ident?i=fatal">fatal</a> = 1,
<a name="L176" href="source/net/ipv4/icmp.c#L176">176</a>         },
<a name="L177" href="source/net/ipv4/icmp.c#L177">177</a>         {
<a name="L178" href="source/net/ipv4/icmp.c#L178">178</a>                 .<a href="ident?i=errno">errno</a> = <a href="ident?i=EHOSTUNREACH">EHOSTUNREACH</a>,  <b><i>/* ICMP_PREC_VIOLATION */</i></b>
<a name="L179" href="source/net/ipv4/icmp.c#L179">179</a>                 .<a href="ident?i=fatal">fatal</a> = 1,
<a name="L180" href="source/net/ipv4/icmp.c#L180">180</a>         },
<a name="L181" href="source/net/ipv4/icmp.c#L181">181</a>         {
<a name="L182" href="source/net/ipv4/icmp.c#L182">182</a>                 .<a href="ident?i=errno">errno</a> = <a href="ident?i=EHOSTUNREACH">EHOSTUNREACH</a>,  <b><i>/* ICMP_PREC_CUTOFF */</i></b>
<a name="L183" href="source/net/ipv4/icmp.c#L183">183</a>                 .<a href="ident?i=fatal">fatal</a> = 1,
<a name="L184" href="source/net/ipv4/icmp.c#L184">184</a>         },
<a name="L185" href="source/net/ipv4/icmp.c#L185">185</a> };
<a name="L186" href="source/net/ipv4/icmp.c#L186">186</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=icmp_err_convert">icmp_err_convert</a>);
<a name="L187" href="source/net/ipv4/icmp.c#L187">187</a> 
<a name="L188" href="source/net/ipv4/icmp.c#L188">188</a> <b><i>/*</i></b>
<a name="L189" href="source/net/ipv4/icmp.c#L189">189</a> <b><i> *      ICMP control array. This specifies what to do with each ICMP.</i></b>
<a name="L190" href="source/net/ipv4/icmp.c#L190">190</a> <b><i> */</i></b>
<a name="L191" href="source/net/ipv4/icmp.c#L191">191</a> 
<a name="L192" href="source/net/ipv4/icmp.c#L192">192</a> struct <a href="ident?i=icmp_control">icmp_control</a> {
<a name="L193" href="source/net/ipv4/icmp.c#L193">193</a>         <a href="ident?i=bool">bool</a> (*<a href="ident?i=handler">handler</a>)(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>);
<a name="L194" href="source/net/ipv4/icmp.c#L194">194</a>         short   <a href="ident?i=error">error</a>;          <b><i>/* This ICMP is classed as an error message */</i></b>
<a name="L195" href="source/net/ipv4/icmp.c#L195">195</a> };
<a name="L196" href="source/net/ipv4/icmp.c#L196">196</a> 
<a name="L197" href="source/net/ipv4/icmp.c#L197">197</a> static const struct <a href="ident?i=icmp_control">icmp_control</a> <a href="ident?i=icmp_pointers">icmp_pointers</a>[<a href="ident?i=NR_ICMP_TYPES">NR_ICMP_TYPES</a>+1];
<a name="L198" href="source/net/ipv4/icmp.c#L198">198</a> 
<a name="L199" href="source/net/ipv4/icmp.c#L199">199</a> <b><i>/*</i></b>
<a name="L200" href="source/net/ipv4/icmp.c#L200">200</a> <b><i> *      The ICMP socket(s). This is the most convenient way to flow control</i></b>
<a name="L201" href="source/net/ipv4/icmp.c#L201">201</a> <b><i> *      our ICMP output as well as maintain a clean interface throughout</i></b>
<a name="L202" href="source/net/ipv4/icmp.c#L202">202</a> <b><i> *      all layers. All Socketless IP sends will soon be gone.</i></b>
<a name="L203" href="source/net/ipv4/icmp.c#L203">203</a> <b><i> *</i></b>
<a name="L204" href="source/net/ipv4/icmp.c#L204">204</a> <b><i> *      On SMP we have one ICMP socket per-cpu.</i></b>
<a name="L205" href="source/net/ipv4/icmp.c#L205">205</a> <b><i> */</i></b>
<a name="L206" href="source/net/ipv4/icmp.c#L206">206</a> static struct <a href="ident?i=sock">sock</a> *<a href="ident?i=icmp_sk">icmp_sk</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>)
<a name="L207" href="source/net/ipv4/icmp.c#L207">207</a> {
<a name="L208" href="source/net/ipv4/icmp.c#L208">208</a>         return *<a href="ident?i=this_cpu_ptr">this_cpu_ptr</a>(<a href="ident?i=net">net</a>-&gt;ipv4.<a href="ident?i=icmp_sk">icmp_sk</a>);
<a name="L209" href="source/net/ipv4/icmp.c#L209">209</a> }
<a name="L210" href="source/net/ipv4/icmp.c#L210">210</a> 
<a name="L211" href="source/net/ipv4/icmp.c#L211">211</a> static inline struct <a href="ident?i=sock">sock</a> *<a href="ident?i=icmp_xmit_lock">icmp_xmit_lock</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>)
<a name="L212" href="source/net/ipv4/icmp.c#L212">212</a> {
<a name="L213" href="source/net/ipv4/icmp.c#L213">213</a>         struct <a href="ident?i=sock">sock</a> *sk;
<a name="L214" href="source/net/ipv4/icmp.c#L214">214</a> 
<a name="L215" href="source/net/ipv4/icmp.c#L215">215</a>         <a href="ident?i=local_bh_disable">local_bh_disable</a>();
<a name="L216" href="source/net/ipv4/icmp.c#L216">216</a> 
<a name="L217" href="source/net/ipv4/icmp.c#L217">217</a>         sk = <a href="ident?i=icmp_sk">icmp_sk</a>(<a href="ident?i=net">net</a>);
<a name="L218" href="source/net/ipv4/icmp.c#L218">218</a> 
<a name="L219" href="source/net/ipv4/icmp.c#L219">219</a>         if (<a href="ident?i=unlikely">unlikely</a>(!<a href="ident?i=spin_trylock">spin_trylock</a>(&amp;sk-&gt;sk_lock.slock))) {
<a name="L220" href="source/net/ipv4/icmp.c#L220">220</a>                 <b><i>/* This can happen if the output path signals a</i></b>
<a name="L221" href="source/net/ipv4/icmp.c#L221">221</a> <b><i>                 * dst_link_failure() for an outgoing ICMP packet.</i></b>
<a name="L222" href="source/net/ipv4/icmp.c#L222">222</a> <b><i>                 */</i></b>
<a name="L223" href="source/net/ipv4/icmp.c#L223">223</a>                 <a href="ident?i=local_bh_enable">local_bh_enable</a>();
<a name="L224" href="source/net/ipv4/icmp.c#L224">224</a>                 return <a href="ident?i=NULL">NULL</a>;
<a name="L225" href="source/net/ipv4/icmp.c#L225">225</a>         }
<a name="L226" href="source/net/ipv4/icmp.c#L226">226</a>         return sk;
<a name="L227" href="source/net/ipv4/icmp.c#L227">227</a> }
<a name="L228" href="source/net/ipv4/icmp.c#L228">228</a> 
<a name="L229" href="source/net/ipv4/icmp.c#L229">229</a> static inline void <a href="ident?i=icmp_xmit_unlock">icmp_xmit_unlock</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L230" href="source/net/ipv4/icmp.c#L230">230</a> {
<a name="L231" href="source/net/ipv4/icmp.c#L231">231</a>         <a href="ident?i=spin_unlock_bh">spin_unlock_bh</a>(&amp;sk-&gt;sk_lock.slock);
<a name="L232" href="source/net/ipv4/icmp.c#L232">232</a> }
<a name="L233" href="source/net/ipv4/icmp.c#L233">233</a> 
<a name="L234" href="source/net/ipv4/icmp.c#L234">234</a> int <a href="ident?i=sysctl_icmp_msgs_per_sec">sysctl_icmp_msgs_per_sec</a> <a href="ident?i=__read_mostly">__read_mostly</a> = 1000;
<a name="L235" href="source/net/ipv4/icmp.c#L235">235</a> int <a href="ident?i=sysctl_icmp_msgs_burst">sysctl_icmp_msgs_burst</a> <a href="ident?i=__read_mostly">__read_mostly</a> = 50;
<a name="L236" href="source/net/ipv4/icmp.c#L236">236</a> 
<a name="L237" href="source/net/ipv4/icmp.c#L237">237</a> static struct {
<a name="L238" href="source/net/ipv4/icmp.c#L238">238</a>         <a href="ident?i=spinlock_t">spinlock_t</a>      <a href="ident?i=lock">lock</a>;
<a name="L239" href="source/net/ipv4/icmp.c#L239">239</a>         <a href="ident?i=u32">u32</a>             credit;
<a name="L240" href="source/net/ipv4/icmp.c#L240">240</a>         <a href="ident?i=u32">u32</a>             <a href="ident?i=stamp">stamp</a>;
<a name="L241" href="source/net/ipv4/icmp.c#L241">241</a> } <a href="ident?i=icmp_global">icmp_global</a> = {
<a name="L242" href="source/net/ipv4/icmp.c#L242">242</a>         .<a href="ident?i=lock">lock</a>           = <a href="ident?i=__SPIN_LOCK_UNLOCKED">__SPIN_LOCK_UNLOCKED</a>(<a href="ident?i=icmp_global">icmp_global</a>.<a href="ident?i=lock">lock</a>),
<a name="L243" href="source/net/ipv4/icmp.c#L243">243</a> };
<a name="L244" href="source/net/ipv4/icmp.c#L244">244</a> 
<a name="L245" href="source/net/ipv4/icmp.c#L245">245</a> <b><i>/**</i></b>
<a name="L246" href="source/net/ipv4/icmp.c#L246">246</a> <b><i> * icmp_global_allow - Are we allowed to send one more ICMP message ?</i></b>
<a name="L247" href="source/net/ipv4/icmp.c#L247">247</a> <b><i> *</i></b>
<a name="L248" href="source/net/ipv4/icmp.c#L248">248</a> <b><i> * Uses a token bucket to limit our ICMP messages to sysctl_icmp_msgs_per_sec.</i></b>
<a name="L249" href="source/net/ipv4/icmp.c#L249">249</a> <b><i> * Returns false if we reached the limit and can not send another packet.</i></b>
<a name="L250" href="source/net/ipv4/icmp.c#L250">250</a> <b><i> * Note: called with BH disabled</i></b>
<a name="L251" href="source/net/ipv4/icmp.c#L251">251</a> <b><i> */</i></b>
<a name="L252" href="source/net/ipv4/icmp.c#L252">252</a> <a href="ident?i=bool">bool</a> <a href="ident?i=icmp_global_allow">icmp_global_allow</a>(void)
<a name="L253" href="source/net/ipv4/icmp.c#L253">253</a> {
<a name="L254" href="source/net/ipv4/icmp.c#L254">254</a>         <a href="ident?i=u32">u32</a> credit, <a href="ident?i=delta">delta</a>, incr = 0, <a href="ident?i=now">now</a> = (<a href="ident?i=u32">u32</a>)<a href="ident?i=jiffies">jiffies</a>;
<a name="L255" href="source/net/ipv4/icmp.c#L255">255</a>         <a href="ident?i=bool">bool</a> <a href="ident?i=rc">rc</a> = <a href="ident?i=false">false</a>;
<a name="L256" href="source/net/ipv4/icmp.c#L256">256</a> 
<a name="L257" href="source/net/ipv4/icmp.c#L257">257</a>         <b><i>/* Check if token bucket is empty and cannot be refilled</i></b>
<a name="L258" href="source/net/ipv4/icmp.c#L258">258</a> <b><i>         * without taking the spinlock.</i></b>
<a name="L259" href="source/net/ipv4/icmp.c#L259">259</a> <b><i>         */</i></b>
<a name="L260" href="source/net/ipv4/icmp.c#L260">260</a>         if (!<a href="ident?i=icmp_global">icmp_global</a>.credit) {
<a name="L261" href="source/net/ipv4/icmp.c#L261">261</a>                 <a href="ident?i=delta">delta</a> = <a href="ident?i=min_t">min_t</a>(<a href="ident?i=u32">u32</a>, <a href="ident?i=now">now</a> - <a href="ident?i=icmp_global">icmp_global</a>.<a href="ident?i=stamp">stamp</a>, <a href="ident?i=HZ">HZ</a>);
<a name="L262" href="source/net/ipv4/icmp.c#L262">262</a>                 if (<a href="ident?i=delta">delta</a> &lt; <a href="ident?i=HZ">HZ</a> / 50)
<a name="L263" href="source/net/ipv4/icmp.c#L263">263</a>                         return <a href="ident?i=false">false</a>;
<a name="L264" href="source/net/ipv4/icmp.c#L264">264</a>         }
<a name="L265" href="source/net/ipv4/icmp.c#L265">265</a> 
<a name="L266" href="source/net/ipv4/icmp.c#L266">266</a>         <a href="ident?i=spin_lock">spin_lock</a>(&amp;<a href="ident?i=icmp_global">icmp_global</a>.<a href="ident?i=lock">lock</a>);
<a name="L267" href="source/net/ipv4/icmp.c#L267">267</a>         <a href="ident?i=delta">delta</a> = <a href="ident?i=min_t">min_t</a>(<a href="ident?i=u32">u32</a>, <a href="ident?i=now">now</a> - <a href="ident?i=icmp_global">icmp_global</a>.<a href="ident?i=stamp">stamp</a>, <a href="ident?i=HZ">HZ</a>);
<a name="L268" href="source/net/ipv4/icmp.c#L268">268</a>         if (<a href="ident?i=delta">delta</a> &gt;= <a href="ident?i=HZ">HZ</a> / 50) {
<a name="L269" href="source/net/ipv4/icmp.c#L269">269</a>                 incr = <a href="ident?i=sysctl_icmp_msgs_per_sec">sysctl_icmp_msgs_per_sec</a> * <a href="ident?i=delta">delta</a> / <a href="ident?i=HZ">HZ</a> ;
<a name="L270" href="source/net/ipv4/icmp.c#L270">270</a>                 if (incr)
<a name="L271" href="source/net/ipv4/icmp.c#L271">271</a>                         <a href="ident?i=icmp_global">icmp_global</a>.<a href="ident?i=stamp">stamp</a> = <a href="ident?i=now">now</a>;
<a name="L272" href="source/net/ipv4/icmp.c#L272">272</a>         }
<a name="L273" href="source/net/ipv4/icmp.c#L273">273</a>         credit = <a href="ident?i=min_t">min_t</a>(<a href="ident?i=u32">u32</a>, <a href="ident?i=icmp_global">icmp_global</a>.credit + incr, <a href="ident?i=sysctl_icmp_msgs_burst">sysctl_icmp_msgs_burst</a>);
<a name="L274" href="source/net/ipv4/icmp.c#L274">274</a>         if (credit) {
<a name="L275" href="source/net/ipv4/icmp.c#L275">275</a>                 credit--;
<a name="L276" href="source/net/ipv4/icmp.c#L276">276</a>                 <a href="ident?i=rc">rc</a> = <a href="ident?i=true">true</a>;
<a name="L277" href="source/net/ipv4/icmp.c#L277">277</a>         }
<a name="L278" href="source/net/ipv4/icmp.c#L278">278</a>         <a href="ident?i=icmp_global">icmp_global</a>.credit = credit;
<a name="L279" href="source/net/ipv4/icmp.c#L279">279</a>         <a href="ident?i=spin_unlock">spin_unlock</a>(&amp;<a href="ident?i=icmp_global">icmp_global</a>.<a href="ident?i=lock">lock</a>);
<a name="L280" href="source/net/ipv4/icmp.c#L280">280</a>         return <a href="ident?i=rc">rc</a>;
<a name="L281" href="source/net/ipv4/icmp.c#L281">281</a> }
<a name="L282" href="source/net/ipv4/icmp.c#L282">282</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=icmp_global_allow">icmp_global_allow</a>);
<a name="L283" href="source/net/ipv4/icmp.c#L283">283</a> 
<a name="L284" href="source/net/ipv4/icmp.c#L284">284</a> <b><i>/*</i></b>
<a name="L285" href="source/net/ipv4/icmp.c#L285">285</a> <b><i> *      Send an ICMP frame.</i></b>
<a name="L286" href="source/net/ipv4/icmp.c#L286">286</a> <b><i> */</i></b>
<a name="L287" href="source/net/ipv4/icmp.c#L287">287</a> 
<a name="L288" href="source/net/ipv4/icmp.c#L288">288</a> static <a href="ident?i=bool">bool</a> <a href="ident?i=icmpv4_xrlim_allow">icmpv4_xrlim_allow</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>, struct <a href="ident?i=rtable">rtable</a> *<a href="ident?i=rt">rt</a>,
<a name="L289" href="source/net/ipv4/icmp.c#L289">289</a>                                struct <a href="ident?i=flowi4">flowi4</a> *fl4, int <a href="ident?i=type">type</a>, int <a href="ident?i=code">code</a>)
<a name="L290" href="source/net/ipv4/icmp.c#L290">290</a> {
<a name="L291" href="source/net/ipv4/icmp.c#L291">291</a>         struct <a href="ident?i=dst_entry">dst_entry</a> *<a href="ident?i=dst">dst</a> = &amp;<a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>;
<a name="L292" href="source/net/ipv4/icmp.c#L292">292</a>         <a href="ident?i=bool">bool</a> <a href="ident?i=rc">rc</a> = <a href="ident?i=true">true</a>;
<a name="L293" href="source/net/ipv4/icmp.c#L293">293</a> 
<a name="L294" href="source/net/ipv4/icmp.c#L294">294</a>         if (<a href="ident?i=type">type</a> &gt; <a href="ident?i=NR_ICMP_TYPES">NR_ICMP_TYPES</a>)
<a name="L295" href="source/net/ipv4/icmp.c#L295">295</a>                 goto <a href="ident?i=out">out</a>;
<a name="L296" href="source/net/ipv4/icmp.c#L296">296</a> 
<a name="L297" href="source/net/ipv4/icmp.c#L297">297</a>         <b><i>/* Don't limit PMTU discovery. */</i></b>
<a name="L298" href="source/net/ipv4/icmp.c#L298">298</a>         if (<a href="ident?i=type">type</a> == <a href="ident?i=ICMP_DEST_UNREACH">ICMP_DEST_UNREACH</a> &amp;&amp; <a href="ident?i=code">code</a> == <a href="ident?i=ICMP_FRAG_NEEDED">ICMP_FRAG_NEEDED</a>)
<a name="L299" href="source/net/ipv4/icmp.c#L299">299</a>                 goto <a href="ident?i=out">out</a>;
<a name="L300" href="source/net/ipv4/icmp.c#L300">300</a> 
<a name="L301" href="source/net/ipv4/icmp.c#L301">301</a>         <b><i>/* No rate limit on loopback */</i></b>
<a name="L302" href="source/net/ipv4/icmp.c#L302">302</a>         if (<a href="ident?i=dst">dst</a>-&gt;<a href="ident?i=dev">dev</a> &amp;&amp; (<a href="ident?i=dst">dst</a>-&gt;<a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=flags">flags</a>&amp;<a href="ident?i=IFF_LOOPBACK">IFF_LOOPBACK</a>))
<a name="L303" href="source/net/ipv4/icmp.c#L303">303</a>                 goto <a href="ident?i=out">out</a>;
<a name="L304" href="source/net/ipv4/icmp.c#L304">304</a> 
<a name="L305" href="source/net/ipv4/icmp.c#L305">305</a>         <b><i>/* Limit if icmp type is enabled in ratemask. */</i></b>
<a name="L306" href="source/net/ipv4/icmp.c#L306">306</a>         if (!((1 &lt;&lt; <a href="ident?i=type">type</a>) &amp; <a href="ident?i=net">net</a>-&gt;ipv4.sysctl_icmp_ratemask))
<a name="L307" href="source/net/ipv4/icmp.c#L307">307</a>                 goto <a href="ident?i=out">out</a>;
<a name="L308" href="source/net/ipv4/icmp.c#L308">308</a> 
<a name="L309" href="source/net/ipv4/icmp.c#L309">309</a>         <a href="ident?i=rc">rc</a> = <a href="ident?i=false">false</a>;
<a name="L310" href="source/net/ipv4/icmp.c#L310">310</a>         if (<a href="ident?i=icmp_global_allow">icmp_global_allow</a>()) {
<a name="L311" href="source/net/ipv4/icmp.c#L311">311</a>                 struct <a href="ident?i=inet_peer">inet_peer</a> *peer;
<a name="L312" href="source/net/ipv4/icmp.c#L312">312</a> 
<a name="L313" href="source/net/ipv4/icmp.c#L313">313</a>                 peer = <a href="ident?i=inet_getpeer_v4">inet_getpeer_v4</a>(<a href="ident?i=net">net</a>-&gt;ipv4.peers, fl4-&gt;<a href="ident?i=daddr">daddr</a>, 1);
<a name="L314" href="source/net/ipv4/icmp.c#L314">314</a>                 <a href="ident?i=rc">rc</a> = <a href="ident?i=inet_peer_xrlim_allow">inet_peer_xrlim_allow</a>(peer,
<a name="L315" href="source/net/ipv4/icmp.c#L315">315</a>                                            <a href="ident?i=net">net</a>-&gt;ipv4.sysctl_icmp_ratelimit);
<a name="L316" href="source/net/ipv4/icmp.c#L316">316</a>                 if (peer)
<a name="L317" href="source/net/ipv4/icmp.c#L317">317</a>                         <a href="ident?i=inet_putpeer">inet_putpeer</a>(peer);
<a name="L318" href="source/net/ipv4/icmp.c#L318">318</a>         }
<a name="L319" href="source/net/ipv4/icmp.c#L319">319</a> <a href="ident?i=out">out</a>:
<a name="L320" href="source/net/ipv4/icmp.c#L320">320</a>         return <a href="ident?i=rc">rc</a>;
<a name="L321" href="source/net/ipv4/icmp.c#L321">321</a> }
<a name="L322" href="source/net/ipv4/icmp.c#L322">322</a> 
<a name="L323" href="source/net/ipv4/icmp.c#L323">323</a> <b><i>/*</i></b>
<a name="L324" href="source/net/ipv4/icmp.c#L324">324</a> <b><i> *      Maintain the counters used in the SNMP statistics for outgoing ICMP</i></b>
<a name="L325" href="source/net/ipv4/icmp.c#L325">325</a> <b><i> */</i></b>
<a name="L326" href="source/net/ipv4/icmp.c#L326">326</a> void <a href="ident?i=icmp_out_count">icmp_out_count</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>, unsigned char <a href="ident?i=type">type</a>)
<a name="L327" href="source/net/ipv4/icmp.c#L327">327</a> {
<a name="L328" href="source/net/ipv4/icmp.c#L328">328</a>         <a href="ident?i=ICMPMSGOUT_INC_STATS">ICMPMSGOUT_INC_STATS</a>(<a href="ident?i=net">net</a>, <a href="ident?i=type">type</a>);
<a name="L329" href="source/net/ipv4/icmp.c#L329">329</a>         <a href="ident?i=ICMP_INC_STATS">ICMP_INC_STATS</a>(<a href="ident?i=net">net</a>, ICMP_MIB_OUTMSGS);
<a name="L330" href="source/net/ipv4/icmp.c#L330">330</a> }
<a name="L331" href="source/net/ipv4/icmp.c#L331">331</a> 
<a name="L332" href="source/net/ipv4/icmp.c#L332">332</a> <b><i>/*</i></b>
<a name="L333" href="source/net/ipv4/icmp.c#L333">333</a> <b><i> *      Checksum each fragment, and on the first include the headers and final</i></b>
<a name="L334" href="source/net/ipv4/icmp.c#L334">334</a> <b><i> *      checksum.</i></b>
<a name="L335" href="source/net/ipv4/icmp.c#L335">335</a> <b><i> */</i></b>
<a name="L336" href="source/net/ipv4/icmp.c#L336">336</a> static int <a href="ident?i=icmp_glue_bits">icmp_glue_bits</a>(void *from, char *to, int <a href="ident?i=offset">offset</a>, int <a href="ident?i=len">len</a>, int odd,
<a name="L337" href="source/net/ipv4/icmp.c#L337">337</a>                           struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L338" href="source/net/ipv4/icmp.c#L338">338</a> {
<a name="L339" href="source/net/ipv4/icmp.c#L339">339</a>         struct <a href="ident?i=icmp_bxm">icmp_bxm</a> *icmp_param = (struct <a href="ident?i=icmp_bxm">icmp_bxm</a> *)from;
<a name="L340" href="source/net/ipv4/icmp.c#L340">340</a>         <a href="ident?i=__wsum">__wsum</a> <a href="ident?i=csum">csum</a>;
<a name="L341" href="source/net/ipv4/icmp.c#L341">341</a> 
<a name="L342" href="source/net/ipv4/icmp.c#L342">342</a>         <a href="ident?i=csum">csum</a> = <a href="ident?i=skb_copy_and_csum_bits">skb_copy_and_csum_bits</a>(icmp_param-&gt;<a href="ident?i=skb">skb</a>,
<a name="L343" href="source/net/ipv4/icmp.c#L343">343</a>                                       icmp_param-&gt;<a href="ident?i=offset">offset</a> + <a href="ident?i=offset">offset</a>,
<a name="L344" href="source/net/ipv4/icmp.c#L344">344</a>                                       to, <a href="ident?i=len">len</a>, 0);
<a name="L345" href="source/net/ipv4/icmp.c#L345">345</a> 
<a name="L346" href="source/net/ipv4/icmp.c#L346">346</a>         <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=csum">csum</a> = <a href="ident?i=csum_block_add">csum_block_add</a>(<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=csum">csum</a>, <a href="ident?i=csum">csum</a>, odd);
<a name="L347" href="source/net/ipv4/icmp.c#L347">347</a>         if (<a href="ident?i=icmp_pointers">icmp_pointers</a>[icmp_param-&gt;<a href="ident?i=data">data</a>.icmph.<a href="ident?i=type">type</a>].<a href="ident?i=error">error</a>)
<a name="L348" href="source/net/ipv4/icmp.c#L348">348</a>                 <a href="ident?i=nf_ct_attach">nf_ct_attach</a>(<a href="ident?i=skb">skb</a>, icmp_param-&gt;<a href="ident?i=skb">skb</a>);
<a name="L349" href="source/net/ipv4/icmp.c#L349">349</a>         return 0;
<a name="L350" href="source/net/ipv4/icmp.c#L350">350</a> }
<a name="L351" href="source/net/ipv4/icmp.c#L351">351</a> 
<a name="L352" href="source/net/ipv4/icmp.c#L352">352</a> static void <a href="ident?i=icmp_push_reply">icmp_push_reply</a>(struct <a href="ident?i=icmp_bxm">icmp_bxm</a> *icmp_param,
<a name="L353" href="source/net/ipv4/icmp.c#L353">353</a>                             struct <a href="ident?i=flowi4">flowi4</a> *fl4,
<a name="L354" href="source/net/ipv4/icmp.c#L354">354</a>                             struct <a href="ident?i=ipcm_cookie">ipcm_cookie</a> *ipc, struct <a href="ident?i=rtable">rtable</a> **<a href="ident?i=rt">rt</a>)
<a name="L355" href="source/net/ipv4/icmp.c#L355">355</a> {
<a name="L356" href="source/net/ipv4/icmp.c#L356">356</a>         struct <a href="ident?i=sock">sock</a> *sk;
<a name="L357" href="source/net/ipv4/icmp.c#L357">357</a>         struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>;
<a name="L358" href="source/net/ipv4/icmp.c#L358">358</a> 
<a name="L359" href="source/net/ipv4/icmp.c#L359">359</a>         sk = <a href="ident?i=icmp_sk">icmp_sk</a>(<a href="ident?i=dev_net">dev_net</a>((*<a href="ident?i=rt">rt</a>)-&gt;<a href="ident?i=dst">dst</a>.<a href="ident?i=dev">dev</a>));
<a name="L360" href="source/net/ipv4/icmp.c#L360">360</a>         if (<a href="ident?i=ip_append_data">ip_append_data</a>(sk, fl4, <a href="ident?i=icmp_glue_bits">icmp_glue_bits</a>, icmp_param,
<a name="L361" href="source/net/ipv4/icmp.c#L361">361</a>                            icmp_param-&gt;<a href="ident?i=data_len">data_len</a>+icmp_param-&gt;head_len,
<a name="L362" href="source/net/ipv4/icmp.c#L362">362</a>                            icmp_param-&gt;head_len,
<a name="L363" href="source/net/ipv4/icmp.c#L363">363</a>                            ipc, <a href="ident?i=rt">rt</a>, <a href="ident?i=MSG_DONTWAIT">MSG_DONTWAIT</a>) &lt; 0) {
<a name="L364" href="source/net/ipv4/icmp.c#L364">364</a>                 <a href="ident?i=ICMP_INC_STATS_BH">ICMP_INC_STATS_BH</a>(<a href="ident?i=sock_net">sock_net</a>(sk), ICMP_MIB_OUTERRORS);
<a name="L365" href="source/net/ipv4/icmp.c#L365">365</a>                 <a href="ident?i=ip_flush_pending_frames">ip_flush_pending_frames</a>(sk);
<a name="L366" href="source/net/ipv4/icmp.c#L366">366</a>         } else if ((<a href="ident?i=skb">skb</a> = <a href="ident?i=skb_peek">skb_peek</a>(&amp;sk-&gt;sk_write_queue)) != <a href="ident?i=NULL">NULL</a>) {
<a name="L367" href="source/net/ipv4/icmp.c#L367">367</a>                 struct <a href="ident?i=icmphdr">icmphdr</a> *icmph = <a href="ident?i=icmp_hdr">icmp_hdr</a>(<a href="ident?i=skb">skb</a>);
<a name="L368" href="source/net/ipv4/icmp.c#L368">368</a>                 <a href="ident?i=__wsum">__wsum</a> <a href="ident?i=csum">csum</a> = 0;
<a name="L369" href="source/net/ipv4/icmp.c#L369">369</a>                 struct <a href="ident?i=sk_buff">sk_buff</a> *skb1;
<a name="L370" href="source/net/ipv4/icmp.c#L370">370</a> 
<a name="L371" href="source/net/ipv4/icmp.c#L371">371</a>                 <a href="ident?i=skb_queue_walk">skb_queue_walk</a>(&amp;sk-&gt;sk_write_queue, skb1) {
<a name="L372" href="source/net/ipv4/icmp.c#L372">372</a>                         <a href="ident?i=csum">csum</a> = <a href="ident?i=csum_add">csum_add</a>(<a href="ident?i=csum">csum</a>, skb1-&gt;<a href="ident?i=csum">csum</a>);
<a name="L373" href="source/net/ipv4/icmp.c#L373">373</a>                 }
<a name="L374" href="source/net/ipv4/icmp.c#L374">374</a>                 <a href="ident?i=csum">csum</a> = <a href="ident?i=csum_partial_copy_nocheck">csum_partial_copy_nocheck</a>((void *)&amp;icmp_param-&gt;<a href="ident?i=data">data</a>,
<a name="L375" href="source/net/ipv4/icmp.c#L375">375</a>                                                  (char *)icmph,
<a name="L376" href="source/net/ipv4/icmp.c#L376">376</a>                                                  icmp_param-&gt;head_len, <a href="ident?i=csum">csum</a>);
<a name="L377" href="source/net/ipv4/icmp.c#L377">377</a>                 icmph-&gt;<a href="ident?i=checksum">checksum</a> = <a href="ident?i=csum_fold">csum_fold</a>(<a href="ident?i=csum">csum</a>);
<a name="L378" href="source/net/ipv4/icmp.c#L378">378</a>                 <a href="ident?i=skb">skb</a>-&gt;ip_summed = <a href="ident?i=CHECKSUM_NONE">CHECKSUM_NONE</a>;
<a name="L379" href="source/net/ipv4/icmp.c#L379">379</a>                 <a href="ident?i=ip_push_pending_frames">ip_push_pending_frames</a>(sk, fl4);
<a name="L380" href="source/net/ipv4/icmp.c#L380">380</a>         }
<a name="L381" href="source/net/ipv4/icmp.c#L381">381</a> }
<a name="L382" href="source/net/ipv4/icmp.c#L382">382</a> 
<a name="L383" href="source/net/ipv4/icmp.c#L383">383</a> <b><i>/*</i></b>
<a name="L384" href="source/net/ipv4/icmp.c#L384">384</a> <b><i> *      Driving logic for building and sending ICMP messages.</i></b>
<a name="L385" href="source/net/ipv4/icmp.c#L385">385</a> <b><i> */</i></b>
<a name="L386" href="source/net/ipv4/icmp.c#L386">386</a> 
<a name="L387" href="source/net/ipv4/icmp.c#L387">387</a> static void <a href="ident?i=icmp_reply">icmp_reply</a>(struct <a href="ident?i=icmp_bxm">icmp_bxm</a> *icmp_param, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L388" href="source/net/ipv4/icmp.c#L388">388</a> {
<a name="L389" href="source/net/ipv4/icmp.c#L389">389</a>         struct <a href="ident?i=ipcm_cookie">ipcm_cookie</a> ipc;
<a name="L390" href="source/net/ipv4/icmp.c#L390">390</a>         struct <a href="ident?i=rtable">rtable</a> *<a href="ident?i=rt">rt</a> = <a href="ident?i=skb_rtable">skb_rtable</a>(<a href="ident?i=skb">skb</a>);
<a name="L391" href="source/net/ipv4/icmp.c#L391">391</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>.<a href="ident?i=dev">dev</a>);
<a name="L392" href="source/net/ipv4/icmp.c#L392">392</a>         struct <a href="ident?i=flowi4">flowi4</a> fl4;
<a name="L393" href="source/net/ipv4/icmp.c#L393">393</a>         struct <a href="ident?i=sock">sock</a> *sk;
<a name="L394" href="source/net/ipv4/icmp.c#L394">394</a>         struct <a href="ident?i=inet_sock">inet_sock</a> *inet;
<a name="L395" href="source/net/ipv4/icmp.c#L395">395</a>         <a href="ident?i=__be32">__be32</a> <a href="ident?i=daddr">daddr</a>, <a href="ident?i=saddr">saddr</a>;
<a name="L396" href="source/net/ipv4/icmp.c#L396">396</a>         <a href="ident?i=u32">u32</a> <a href="ident?i=mark">mark</a> = <a href="ident?i=IP4_REPLY_MARK">IP4_REPLY_MARK</a>(<a href="ident?i=net">net</a>, <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=mark">mark</a>);
<a name="L397" href="source/net/ipv4/icmp.c#L397">397</a> 
<a name="L398" href="source/net/ipv4/icmp.c#L398">398</a>         if (<a href="ident?i=ip_options_echo">ip_options_echo</a>(&amp;icmp_param-&gt;replyopts.opt.opt, <a href="ident?i=skb">skb</a>))
<a name="L399" href="source/net/ipv4/icmp.c#L399">399</a>                 return;
<a name="L400" href="source/net/ipv4/icmp.c#L400">400</a> 
<a name="L401" href="source/net/ipv4/icmp.c#L401">401</a>         sk = <a href="ident?i=icmp_xmit_lock">icmp_xmit_lock</a>(<a href="ident?i=net">net</a>);
<a name="L402" href="source/net/ipv4/icmp.c#L402">402</a>         if (!sk)
<a name="L403" href="source/net/ipv4/icmp.c#L403">403</a>                 return;
<a name="L404" href="source/net/ipv4/icmp.c#L404">404</a>         inet = <a href="ident?i=inet_sk">inet_sk</a>(sk);
<a name="L405" href="source/net/ipv4/icmp.c#L405">405</a> 
<a name="L406" href="source/net/ipv4/icmp.c#L406">406</a>         icmp_param-&gt;<a href="ident?i=data">data</a>.icmph.<a href="ident?i=checksum">checksum</a> = 0;
<a name="L407" href="source/net/ipv4/icmp.c#L407">407</a> 
<a name="L408" href="source/net/ipv4/icmp.c#L408">408</a>         inet-&gt;tos = <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;tos;
<a name="L409" href="source/net/ipv4/icmp.c#L409">409</a>         sk-&gt;sk_mark = <a href="ident?i=mark">mark</a>;
<a name="L410" href="source/net/ipv4/icmp.c#L410">410</a>         <a href="ident?i=daddr">daddr</a> = ipc.<a href="ident?i=addr">addr</a> = <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=saddr">saddr</a>;
<a name="L411" href="source/net/ipv4/icmp.c#L411">411</a>         <a href="ident?i=saddr">saddr</a> = <a href="ident?i=fib_compute_spec_dst">fib_compute_spec_dst</a>(<a href="ident?i=skb">skb</a>);
<a name="L412" href="source/net/ipv4/icmp.c#L412">412</a>         ipc.opt = <a href="ident?i=NULL">NULL</a>;
<a name="L413" href="source/net/ipv4/icmp.c#L413">413</a>         ipc.tx_flags = 0;
<a name="L414" href="source/net/ipv4/icmp.c#L414">414</a>         ipc.<a href="ident?i=ttl">ttl</a> = 0;
<a name="L415" href="source/net/ipv4/icmp.c#L415">415</a>         ipc.tos = -1;
<a name="L416" href="source/net/ipv4/icmp.c#L416">416</a> 
<a name="L417" href="source/net/ipv4/icmp.c#L417">417</a>         if (icmp_param-&gt;replyopts.opt.opt.<a href="ident?i=optlen">optlen</a>) {
<a name="L418" href="source/net/ipv4/icmp.c#L418">418</a>                 ipc.opt = &amp;icmp_param-&gt;replyopts.opt;
<a name="L419" href="source/net/ipv4/icmp.c#L419">419</a>                 if (ipc.opt-&gt;opt.<a href="ident?i=srr">srr</a>)
<a name="L420" href="source/net/ipv4/icmp.c#L420">420</a>                         <a href="ident?i=daddr">daddr</a> = icmp_param-&gt;replyopts.opt.opt.faddr;
<a name="L421" href="source/net/ipv4/icmp.c#L421">421</a>         }
<a name="L422" href="source/net/ipv4/icmp.c#L422">422</a>         <a href="ident?i=memset">memset</a>(&amp;fl4, 0, sizeof(fl4));
<a name="L423" href="source/net/ipv4/icmp.c#L423">423</a>         fl4.<a href="ident?i=daddr">daddr</a> = <a href="ident?i=daddr">daddr</a>;
<a name="L424" href="source/net/ipv4/icmp.c#L424">424</a>         fl4.<a href="ident?i=saddr">saddr</a> = <a href="ident?i=saddr">saddr</a>;
<a name="L425" href="source/net/ipv4/icmp.c#L425">425</a>         fl4.<a href="ident?i=flowi4_mark">flowi4_mark</a> = <a href="ident?i=mark">mark</a>;
<a name="L426" href="source/net/ipv4/icmp.c#L426">426</a>         fl4.<a href="ident?i=flowi4_tos">flowi4_tos</a> = <a href="ident?i=RT_TOS">RT_TOS</a>(<a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;tos);
<a name="L427" href="source/net/ipv4/icmp.c#L427">427</a>         fl4.<a href="ident?i=flowi4_proto">flowi4_proto</a> = <a href="ident?i=IPPROTO_ICMP">IPPROTO_ICMP</a>;
<a name="L428" href="source/net/ipv4/icmp.c#L428">428</a>         <a href="ident?i=security_skb_classify_flow">security_skb_classify_flow</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=flowi4_to_flowi">flowi4_to_flowi</a>(&amp;fl4));
<a name="L429" href="source/net/ipv4/icmp.c#L429">429</a>         <a href="ident?i=rt">rt</a> = <a href="ident?i=ip_route_output_key">ip_route_output_key</a>(<a href="ident?i=net">net</a>, &amp;fl4);
<a name="L430" href="source/net/ipv4/icmp.c#L430">430</a>         if (<a href="ident?i=IS_ERR">IS_ERR</a>(<a href="ident?i=rt">rt</a>))
<a name="L431" href="source/net/ipv4/icmp.c#L431">431</a>                 goto out_unlock;
<a name="L432" href="source/net/ipv4/icmp.c#L432">432</a>         if (<a href="ident?i=icmpv4_xrlim_allow">icmpv4_xrlim_allow</a>(<a href="ident?i=net">net</a>, <a href="ident?i=rt">rt</a>, &amp;fl4, icmp_param-&gt;<a href="ident?i=data">data</a>.icmph.<a href="ident?i=type">type</a>,
<a name="L433" href="source/net/ipv4/icmp.c#L433">433</a>                                icmp_param-&gt;<a href="ident?i=data">data</a>.icmph.<a href="ident?i=code">code</a>))
<a name="L434" href="source/net/ipv4/icmp.c#L434">434</a>                 <a href="ident?i=icmp_push_reply">icmp_push_reply</a>(icmp_param, &amp;fl4, &amp;ipc, &amp;<a href="ident?i=rt">rt</a>);
<a name="L435" href="source/net/ipv4/icmp.c#L435">435</a>         <a href="ident?i=ip_rt_put">ip_rt_put</a>(<a href="ident?i=rt">rt</a>);
<a name="L436" href="source/net/ipv4/icmp.c#L436">436</a> out_unlock:
<a name="L437" href="source/net/ipv4/icmp.c#L437">437</a>         <a href="ident?i=icmp_xmit_unlock">icmp_xmit_unlock</a>(sk);
<a name="L438" href="source/net/ipv4/icmp.c#L438">438</a> }
<a name="L439" href="source/net/ipv4/icmp.c#L439">439</a> 
<a name="L440" href="source/net/ipv4/icmp.c#L440">440</a> static struct <a href="ident?i=rtable">rtable</a> *<a href="ident?i=icmp_route_lookup">icmp_route_lookup</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>,
<a name="L441" href="source/net/ipv4/icmp.c#L441">441</a>                                         struct <a href="ident?i=flowi4">flowi4</a> *fl4,
<a name="L442" href="source/net/ipv4/icmp.c#L442">442</a>                                         struct <a href="ident?i=sk_buff">sk_buff</a> *skb_in,
<a name="L443" href="source/net/ipv4/icmp.c#L443">443</a>                                         const struct <a href="ident?i=iphdr">iphdr</a> *iph,
<a name="L444" href="source/net/ipv4/icmp.c#L444">444</a>                                         <a href="ident?i=__be32">__be32</a> <a href="ident?i=saddr">saddr</a>, <a href="ident?i=u8">u8</a> tos, <a href="ident?i=u32">u32</a> <a href="ident?i=mark">mark</a>,
<a name="L445" href="source/net/ipv4/icmp.c#L445">445</a>                                         int <a href="ident?i=type">type</a>, int <a href="ident?i=code">code</a>,
<a name="L446" href="source/net/ipv4/icmp.c#L446">446</a>                                         struct <a href="ident?i=icmp_bxm">icmp_bxm</a> *<a href="ident?i=param">param</a>)
<a name="L447" href="source/net/ipv4/icmp.c#L447">447</a> {
<a name="L448" href="source/net/ipv4/icmp.c#L448">448</a>         struct <a href="ident?i=rtable">rtable</a> *<a href="ident?i=rt">rt</a>, *rt2;
<a name="L449" href="source/net/ipv4/icmp.c#L449">449</a>         struct <a href="ident?i=flowi4">flowi4</a> fl4_dec;
<a name="L450" href="source/net/ipv4/icmp.c#L450">450</a>         int <a href="ident?i=err">err</a>;
<a name="L451" href="source/net/ipv4/icmp.c#L451">451</a> 
<a name="L452" href="source/net/ipv4/icmp.c#L452">452</a>         <a href="ident?i=memset">memset</a>(fl4, 0, sizeof(*fl4));
<a name="L453" href="source/net/ipv4/icmp.c#L453">453</a>         fl4-&gt;<a href="ident?i=daddr">daddr</a> = (<a href="ident?i=param">param</a>-&gt;replyopts.opt.opt.<a href="ident?i=srr">srr</a> ?
<a name="L454" href="source/net/ipv4/icmp.c#L454">454</a>                       <a href="ident?i=param">param</a>-&gt;replyopts.opt.opt.faddr : iph-&gt;<a href="ident?i=saddr">saddr</a>);
<a name="L455" href="source/net/ipv4/icmp.c#L455">455</a>         fl4-&gt;<a href="ident?i=saddr">saddr</a> = <a href="ident?i=saddr">saddr</a>;
<a name="L456" href="source/net/ipv4/icmp.c#L456">456</a>         fl4-&gt;<a href="ident?i=flowi4_mark">flowi4_mark</a> = <a href="ident?i=mark">mark</a>;
<a name="L457" href="source/net/ipv4/icmp.c#L457">457</a>         fl4-&gt;<a href="ident?i=flowi4_tos">flowi4_tos</a> = <a href="ident?i=RT_TOS">RT_TOS</a>(tos);
<a name="L458" href="source/net/ipv4/icmp.c#L458">458</a>         fl4-&gt;<a href="ident?i=flowi4_proto">flowi4_proto</a> = <a href="ident?i=IPPROTO_ICMP">IPPROTO_ICMP</a>;
<a name="L459" href="source/net/ipv4/icmp.c#L459">459</a>         fl4-&gt;<a href="ident?i=fl4_icmp_type">fl4_icmp_type</a> = <a href="ident?i=type">type</a>;
<a name="L460" href="source/net/ipv4/icmp.c#L460">460</a>         fl4-&gt;<a href="ident?i=fl4_icmp_code">fl4_icmp_code</a> = <a href="ident?i=code">code</a>;
<a name="L461" href="source/net/ipv4/icmp.c#L461">461</a>         <a href="ident?i=security_skb_classify_flow">security_skb_classify_flow</a>(skb_in, <a href="ident?i=flowi4_to_flowi">flowi4_to_flowi</a>(fl4));
<a name="L462" href="source/net/ipv4/icmp.c#L462">462</a>         <a href="ident?i=rt">rt</a> = <a href="ident?i=__ip_route_output_key">__ip_route_output_key</a>(<a href="ident?i=net">net</a>, fl4);
<a name="L463" href="source/net/ipv4/icmp.c#L463">463</a>         if (<a href="ident?i=IS_ERR">IS_ERR</a>(<a href="ident?i=rt">rt</a>))
<a name="L464" href="source/net/ipv4/icmp.c#L464">464</a>                 return <a href="ident?i=rt">rt</a>;
<a name="L465" href="source/net/ipv4/icmp.c#L465">465</a> 
<a name="L466" href="source/net/ipv4/icmp.c#L466">466</a>         <b><i>/* No need to clone since we're just using its address. */</i></b>
<a name="L467" href="source/net/ipv4/icmp.c#L467">467</a>         rt2 = <a href="ident?i=rt">rt</a>;
<a name="L468" href="source/net/ipv4/icmp.c#L468">468</a> 
<a name="L469" href="source/net/ipv4/icmp.c#L469">469</a>         <a href="ident?i=rt">rt</a> = (struct <a href="ident?i=rtable">rtable</a> *) <a href="ident?i=xfrm_lookup">xfrm_lookup</a>(<a href="ident?i=net">net</a>, &amp;<a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>,
<a name="L470" href="source/net/ipv4/icmp.c#L470">470</a>                                            <a href="ident?i=flowi4_to_flowi">flowi4_to_flowi</a>(fl4), <a href="ident?i=NULL">NULL</a>, 0);
<a name="L471" href="source/net/ipv4/icmp.c#L471">471</a>         if (!<a href="ident?i=IS_ERR">IS_ERR</a>(<a href="ident?i=rt">rt</a>)) {
<a name="L472" href="source/net/ipv4/icmp.c#L472">472</a>                 if (<a href="ident?i=rt">rt</a> != rt2)
<a name="L473" href="source/net/ipv4/icmp.c#L473">473</a>                         return <a href="ident?i=rt">rt</a>;
<a name="L474" href="source/net/ipv4/icmp.c#L474">474</a>         } else if (<a href="ident?i=PTR_ERR">PTR_ERR</a>(<a href="ident?i=rt">rt</a>) == -<a href="ident?i=EPERM">EPERM</a>) {
<a name="L475" href="source/net/ipv4/icmp.c#L475">475</a>                 <a href="ident?i=rt">rt</a> = <a href="ident?i=NULL">NULL</a>;
<a name="L476" href="source/net/ipv4/icmp.c#L476">476</a>         } else
<a name="L477" href="source/net/ipv4/icmp.c#L477">477</a>                 return <a href="ident?i=rt">rt</a>;
<a name="L478" href="source/net/ipv4/icmp.c#L478">478</a> 
<a name="L479" href="source/net/ipv4/icmp.c#L479">479</a>         <a href="ident?i=err">err</a> = <a href="ident?i=xfrm_decode_session_reverse">xfrm_decode_session_reverse</a>(skb_in, <a href="ident?i=flowi4_to_flowi">flowi4_to_flowi</a>(&amp;fl4_dec), <a href="ident?i=AF_INET">AF_INET</a>);
<a name="L480" href="source/net/ipv4/icmp.c#L480">480</a>         if (<a href="ident?i=err">err</a>)
<a name="L481" href="source/net/ipv4/icmp.c#L481">481</a>                 goto relookup_failed;
<a name="L482" href="source/net/ipv4/icmp.c#L482">482</a> 
<a name="L483" href="source/net/ipv4/icmp.c#L483">483</a>         if (<a href="ident?i=inet_addr_type">inet_addr_type</a>(<a href="ident?i=net">net</a>, fl4_dec.<a href="ident?i=saddr">saddr</a>) == RTN_LOCAL) {
<a name="L484" href="source/net/ipv4/icmp.c#L484">484</a>                 rt2 = <a href="ident?i=__ip_route_output_key">__ip_route_output_key</a>(<a href="ident?i=net">net</a>, &amp;fl4_dec);
<a name="L485" href="source/net/ipv4/icmp.c#L485">485</a>                 if (<a href="ident?i=IS_ERR">IS_ERR</a>(rt2))
<a name="L486" href="source/net/ipv4/icmp.c#L486">486</a>                         <a href="ident?i=err">err</a> = <a href="ident?i=PTR_ERR">PTR_ERR</a>(rt2);
<a name="L487" href="source/net/ipv4/icmp.c#L487">487</a>         } else {
<a name="L488" href="source/net/ipv4/icmp.c#L488">488</a>                 struct <a href="ident?i=flowi4">flowi4</a> fl4_2 = {};
<a name="L489" href="source/net/ipv4/icmp.c#L489">489</a>                 unsigned long orefdst;
<a name="L490" href="source/net/ipv4/icmp.c#L490">490</a> 
<a name="L491" href="source/net/ipv4/icmp.c#L491">491</a>                 fl4_2.<a href="ident?i=daddr">daddr</a> = fl4_dec.<a href="ident?i=saddr">saddr</a>;
<a name="L492" href="source/net/ipv4/icmp.c#L492">492</a>                 rt2 = <a href="ident?i=ip_route_output_key">ip_route_output_key</a>(<a href="ident?i=net">net</a>, &amp;fl4_2);
<a name="L493" href="source/net/ipv4/icmp.c#L493">493</a>                 if (<a href="ident?i=IS_ERR">IS_ERR</a>(rt2)) {
<a name="L494" href="source/net/ipv4/icmp.c#L494">494</a>                         <a href="ident?i=err">err</a> = <a href="ident?i=PTR_ERR">PTR_ERR</a>(rt2);
<a name="L495" href="source/net/ipv4/icmp.c#L495">495</a>                         goto relookup_failed;
<a name="L496" href="source/net/ipv4/icmp.c#L496">496</a>                 }
<a name="L497" href="source/net/ipv4/icmp.c#L497">497</a>                 <b><i>/* Ugh! */</i></b>
<a name="L498" href="source/net/ipv4/icmp.c#L498">498</a>                 orefdst = skb_in-&gt;_skb_refdst; <b><i>/* save old refdst */</i></b>
<a name="L499" href="source/net/ipv4/icmp.c#L499">499</a>                 <a href="ident?i=err">err</a> = <a href="ident?i=ip_route_input">ip_route_input</a>(skb_in, fl4_dec.<a href="ident?i=daddr">daddr</a>, fl4_dec.<a href="ident?i=saddr">saddr</a>,
<a name="L500" href="source/net/ipv4/icmp.c#L500">500</a>                                      <a href="ident?i=RT_TOS">RT_TOS</a>(tos), rt2-&gt;<a href="ident?i=dst">dst</a>.<a href="ident?i=dev">dev</a>);
<a name="L501" href="source/net/ipv4/icmp.c#L501">501</a> 
<a name="L502" href="source/net/ipv4/icmp.c#L502">502</a>                 <a href="ident?i=dst_release">dst_release</a>(&amp;rt2-&gt;<a href="ident?i=dst">dst</a>);
<a name="L503" href="source/net/ipv4/icmp.c#L503">503</a>                 rt2 = <a href="ident?i=skb_rtable">skb_rtable</a>(skb_in);
<a name="L504" href="source/net/ipv4/icmp.c#L504">504</a>                 skb_in-&gt;_skb_refdst = orefdst; <b><i>/* restore old refdst */</i></b>
<a name="L505" href="source/net/ipv4/icmp.c#L505">505</a>         }
<a name="L506" href="source/net/ipv4/icmp.c#L506">506</a> 
<a name="L507" href="source/net/ipv4/icmp.c#L507">507</a>         if (<a href="ident?i=err">err</a>)
<a name="L508" href="source/net/ipv4/icmp.c#L508">508</a>                 goto relookup_failed;
<a name="L509" href="source/net/ipv4/icmp.c#L509">509</a> 
<a name="L510" href="source/net/ipv4/icmp.c#L510">510</a>         rt2 = (struct <a href="ident?i=rtable">rtable</a> *) <a href="ident?i=xfrm_lookup">xfrm_lookup</a>(<a href="ident?i=net">net</a>, &amp;rt2-&gt;<a href="ident?i=dst">dst</a>,
<a name="L511" href="source/net/ipv4/icmp.c#L511">511</a>                                             <a href="ident?i=flowi4_to_flowi">flowi4_to_flowi</a>(&amp;fl4_dec), <a href="ident?i=NULL">NULL</a>,
<a name="L512" href="source/net/ipv4/icmp.c#L512">512</a>                                             XFRM_LOOKUP_ICMP);
<a name="L513" href="source/net/ipv4/icmp.c#L513">513</a>         if (!<a href="ident?i=IS_ERR">IS_ERR</a>(rt2)) {
<a name="L514" href="source/net/ipv4/icmp.c#L514">514</a>                 <a href="ident?i=dst_release">dst_release</a>(&amp;<a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>);
<a name="L515" href="source/net/ipv4/icmp.c#L515">515</a>                 <a href="ident?i=memcpy">memcpy</a>(fl4, &amp;fl4_dec, sizeof(*fl4));
<a name="L516" href="source/net/ipv4/icmp.c#L516">516</a>                 <a href="ident?i=rt">rt</a> = rt2;
<a name="L517" href="source/net/ipv4/icmp.c#L517">517</a>         } else if (<a href="ident?i=PTR_ERR">PTR_ERR</a>(rt2) == -<a href="ident?i=EPERM">EPERM</a>) {
<a name="L518" href="source/net/ipv4/icmp.c#L518">518</a>                 if (<a href="ident?i=rt">rt</a>)
<a name="L519" href="source/net/ipv4/icmp.c#L519">519</a>                         <a href="ident?i=dst_release">dst_release</a>(&amp;<a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>);
<a name="L520" href="source/net/ipv4/icmp.c#L520">520</a>                 return rt2;
<a name="L521" href="source/net/ipv4/icmp.c#L521">521</a>         } else {
<a name="L522" href="source/net/ipv4/icmp.c#L522">522</a>                 <a href="ident?i=err">err</a> = <a href="ident?i=PTR_ERR">PTR_ERR</a>(rt2);
<a name="L523" href="source/net/ipv4/icmp.c#L523">523</a>                 goto relookup_failed;
<a name="L524" href="source/net/ipv4/icmp.c#L524">524</a>         }
<a name="L525" href="source/net/ipv4/icmp.c#L525">525</a>         return <a href="ident?i=rt">rt</a>;
<a name="L526" href="source/net/ipv4/icmp.c#L526">526</a> 
<a name="L527" href="source/net/ipv4/icmp.c#L527">527</a> relookup_failed:
<a name="L528" href="source/net/ipv4/icmp.c#L528">528</a>         if (<a href="ident?i=rt">rt</a>)
<a name="L529" href="source/net/ipv4/icmp.c#L529">529</a>                 return <a href="ident?i=rt">rt</a>;
<a name="L530" href="source/net/ipv4/icmp.c#L530">530</a>         return <a href="ident?i=ERR_PTR">ERR_PTR</a>(<a href="ident?i=err">err</a>);
<a name="L531" href="source/net/ipv4/icmp.c#L531">531</a> }
<a name="L532" href="source/net/ipv4/icmp.c#L532">532</a> 
<a name="L533" href="source/net/ipv4/icmp.c#L533">533</a> <b><i>/*</i></b>
<a name="L534" href="source/net/ipv4/icmp.c#L534">534</a> <b><i> *      Send an ICMP message in response to a situation</i></b>
<a name="L535" href="source/net/ipv4/icmp.c#L535">535</a> <b><i> *</i></b>
<a name="L536" href="source/net/ipv4/icmp.c#L536">536</a> <b><i> *      RFC 1122: 3.2.2 MUST send at least the IP header and 8 bytes of header.</i></b>
<a name="L537" href="source/net/ipv4/icmp.c#L537">537</a> <b><i> *                MAY send more (we do).</i></b>
<a name="L538" href="source/net/ipv4/icmp.c#L538">538</a> <b><i> *                      MUST NOT change this header information.</i></b>
<a name="L539" href="source/net/ipv4/icmp.c#L539">539</a> <b><i> *                      MUST NOT reply to a multicast/broadcast IP address.</i></b>
<a name="L540" href="source/net/ipv4/icmp.c#L540">540</a> <b><i> *                      MUST NOT reply to a multicast/broadcast MAC address.</i></b>
<a name="L541" href="source/net/ipv4/icmp.c#L541">541</a> <b><i> *                      MUST reply to only the first fragment.</i></b>
<a name="L542" href="source/net/ipv4/icmp.c#L542">542</a> <b><i> */</i></b>
<a name="L543" href="source/net/ipv4/icmp.c#L543">543</a> 
<a name="L544" href="source/net/ipv4/icmp.c#L544">544</a> void <a href="ident?i=icmp_send">icmp_send</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *skb_in, int <a href="ident?i=type">type</a>, int <a href="ident?i=code">code</a>, <a href="ident?i=__be32">__be32</a> <a href="ident?i=info">info</a>)
<a name="L545" href="source/net/ipv4/icmp.c#L545">545</a> {
<a name="L546" href="source/net/ipv4/icmp.c#L546">546</a>         struct <a href="ident?i=iphdr">iphdr</a> *iph;
<a name="L547" href="source/net/ipv4/icmp.c#L547">547</a>         int room;
<a name="L548" href="source/net/ipv4/icmp.c#L548">548</a>         struct <a href="ident?i=icmp_bxm">icmp_bxm</a> *icmp_param;
<a name="L549" href="source/net/ipv4/icmp.c#L549">549</a>         struct <a href="ident?i=rtable">rtable</a> *<a href="ident?i=rt">rt</a> = <a href="ident?i=skb_rtable">skb_rtable</a>(skb_in);
<a name="L550" href="source/net/ipv4/icmp.c#L550">550</a>         struct <a href="ident?i=ipcm_cookie">ipcm_cookie</a> ipc;
<a name="L551" href="source/net/ipv4/icmp.c#L551">551</a>         struct <a href="ident?i=flowi4">flowi4</a> fl4;
<a name="L552" href="source/net/ipv4/icmp.c#L552">552</a>         <a href="ident?i=__be32">__be32</a> <a href="ident?i=saddr">saddr</a>;
<a name="L553" href="source/net/ipv4/icmp.c#L553">553</a>         <a href="ident?i=u8">u8</a>  tos;
<a name="L554" href="source/net/ipv4/icmp.c#L554">554</a>         <a href="ident?i=u32">u32</a> <a href="ident?i=mark">mark</a>;
<a name="L555" href="source/net/ipv4/icmp.c#L555">555</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>;
<a name="L556" href="source/net/ipv4/icmp.c#L556">556</a>         struct <a href="ident?i=sock">sock</a> *sk;
<a name="L557" href="source/net/ipv4/icmp.c#L557">557</a> 
<a name="L558" href="source/net/ipv4/icmp.c#L558">558</a>         if (!<a href="ident?i=rt">rt</a>)
<a name="L559" href="source/net/ipv4/icmp.c#L559">559</a>                 goto <a href="ident?i=out">out</a>;
<a name="L560" href="source/net/ipv4/icmp.c#L560">560</a>         <a href="ident?i=net">net</a> = <a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>.<a href="ident?i=dev">dev</a>);
<a name="L561" href="source/net/ipv4/icmp.c#L561">561</a> 
<a name="L562" href="source/net/ipv4/icmp.c#L562">562</a>         <b><i>/*</i></b>
<a name="L563" href="source/net/ipv4/icmp.c#L563">563</a> <b><i>         *      Find the original header. It is expected to be valid, of course.</i></b>
<a name="L564" href="source/net/ipv4/icmp.c#L564">564</a> <b><i>         *      Check this, icmp_send is called from the most obscure devices</i></b>
<a name="L565" href="source/net/ipv4/icmp.c#L565">565</a> <b><i>         *      sometimes.</i></b>
<a name="L566" href="source/net/ipv4/icmp.c#L566">566</a> <b><i>         */</i></b>
<a name="L567" href="source/net/ipv4/icmp.c#L567">567</a>         iph = <a href="ident?i=ip_hdr">ip_hdr</a>(skb_in);
<a name="L568" href="source/net/ipv4/icmp.c#L568">568</a> 
<a name="L569" href="source/net/ipv4/icmp.c#L569">569</a>         if ((<a href="ident?i=u8">u8</a> *)iph &lt; skb_in-&gt;<a href="ident?i=head">head</a> ||
<a name="L570" href="source/net/ipv4/icmp.c#L570">570</a>             (<a href="ident?i=skb_network_header">skb_network_header</a>(skb_in) + sizeof(*iph)) &gt;
<a name="L571" href="source/net/ipv4/icmp.c#L571">571</a>             <a href="ident?i=skb_tail_pointer">skb_tail_pointer</a>(skb_in))
<a name="L572" href="source/net/ipv4/icmp.c#L572">572</a>                 goto <a href="ident?i=out">out</a>;
<a name="L573" href="source/net/ipv4/icmp.c#L573">573</a> 
<a name="L574" href="source/net/ipv4/icmp.c#L574">574</a>         <b><i>/*</i></b>
<a name="L575" href="source/net/ipv4/icmp.c#L575">575</a> <b><i>         *      No replies to physical multicast/broadcast</i></b>
<a name="L576" href="source/net/ipv4/icmp.c#L576">576</a> <b><i>         */</i></b>
<a name="L577" href="source/net/ipv4/icmp.c#L577">577</a>         if (skb_in-&gt;pkt_type != <a href="ident?i=PACKET_HOST">PACKET_HOST</a>)
<a name="L578" href="source/net/ipv4/icmp.c#L578">578</a>                 goto <a href="ident?i=out">out</a>;
<a name="L579" href="source/net/ipv4/icmp.c#L579">579</a> 
<a name="L580" href="source/net/ipv4/icmp.c#L580">580</a>         <b><i>/*</i></b>
<a name="L581" href="source/net/ipv4/icmp.c#L581">581</a> <b><i>         *      Now check at the protocol level</i></b>
<a name="L582" href="source/net/ipv4/icmp.c#L582">582</a> <b><i>         */</i></b>
<a name="L583" href="source/net/ipv4/icmp.c#L583">583</a>         if (<a href="ident?i=rt">rt</a>-&gt;rt_flags &amp; (<a href="ident?i=RTCF_BROADCAST">RTCF_BROADCAST</a> | <a href="ident?i=RTCF_MULTICAST">RTCF_MULTICAST</a>))
<a name="L584" href="source/net/ipv4/icmp.c#L584">584</a>                 goto <a href="ident?i=out">out</a>;
<a name="L585" href="source/net/ipv4/icmp.c#L585">585</a> 
<a name="L586" href="source/net/ipv4/icmp.c#L586">586</a>         <b><i>/*</i></b>
<a name="L587" href="source/net/ipv4/icmp.c#L587">587</a> <b><i>         *      Only reply to fragment 0. We byte re-order the constant</i></b>
<a name="L588" href="source/net/ipv4/icmp.c#L588">588</a> <b><i>         *      mask for efficiency.</i></b>
<a name="L589" href="source/net/ipv4/icmp.c#L589">589</a> <b><i>         */</i></b>
<a name="L590" href="source/net/ipv4/icmp.c#L590">590</a>         if (iph-&gt;frag_off &amp; <a href="ident?i=htons">htons</a>(<a href="ident?i=IP_OFFSET">IP_OFFSET</a>))
<a name="L591" href="source/net/ipv4/icmp.c#L591">591</a>                 goto <a href="ident?i=out">out</a>;
<a name="L592" href="source/net/ipv4/icmp.c#L592">592</a> 
<a name="L593" href="source/net/ipv4/icmp.c#L593">593</a>         <b><i>/*</i></b>
<a name="L594" href="source/net/ipv4/icmp.c#L594">594</a> <b><i>         *      If we send an ICMP error to an ICMP error a mess would result..</i></b>
<a name="L595" href="source/net/ipv4/icmp.c#L595">595</a> <b><i>         */</i></b>
<a name="L596" href="source/net/ipv4/icmp.c#L596">596</a>         if (<a href="ident?i=icmp_pointers">icmp_pointers</a>[<a href="ident?i=type">type</a>].<a href="ident?i=error">error</a>) {
<a name="L597" href="source/net/ipv4/icmp.c#L597">597</a>                 <b><i>/*</i></b>
<a name="L598" href="source/net/ipv4/icmp.c#L598">598</a> <b><i>                 *      We are an error, check if we are replying to an</i></b>
<a name="L599" href="source/net/ipv4/icmp.c#L599">599</a> <b><i>                 *      ICMP error</i></b>
<a name="L600" href="source/net/ipv4/icmp.c#L600">600</a> <b><i>                 */</i></b>
<a name="L601" href="source/net/ipv4/icmp.c#L601">601</a>                 if (iph-&gt;<a href="ident?i=protocol">protocol</a> == <a href="ident?i=IPPROTO_ICMP">IPPROTO_ICMP</a>) {
<a name="L602" href="source/net/ipv4/icmp.c#L602">602</a>                         <a href="ident?i=u8">u8</a> _inner_type, *itp;
<a name="L603" href="source/net/ipv4/icmp.c#L603">603</a> 
<a name="L604" href="source/net/ipv4/icmp.c#L604">604</a>                         itp = <a href="ident?i=skb_header_pointer">skb_header_pointer</a>(skb_in,
<a name="L605" href="source/net/ipv4/icmp.c#L605">605</a>                                                  <a href="ident?i=skb_network_header">skb_network_header</a>(skb_in) +
<a name="L606" href="source/net/ipv4/icmp.c#L606">606</a>                                                  (iph-&gt;ihl &lt;&lt; 2) +
<a name="L607" href="source/net/ipv4/icmp.c#L607">607</a>                                                  <a href="ident?i=offsetof">offsetof</a>(struct <a href="ident?i=icmphdr">icmphdr</a>,
<a name="L608" href="source/net/ipv4/icmp.c#L608">608</a>                                                           <a href="ident?i=type">type</a>) -
<a name="L609" href="source/net/ipv4/icmp.c#L609">609</a>                                                  skb_in-&gt;<a href="ident?i=data">data</a>,
<a name="L610" href="source/net/ipv4/icmp.c#L610">610</a>                                                  sizeof(_inner_type),
<a name="L611" href="source/net/ipv4/icmp.c#L611">611</a>                                                  &amp;_inner_type);
<a name="L612" href="source/net/ipv4/icmp.c#L612">612</a>                         if (!itp)
<a name="L613" href="source/net/ipv4/icmp.c#L613">613</a>                                 goto <a href="ident?i=out">out</a>;
<a name="L614" href="source/net/ipv4/icmp.c#L614">614</a> 
<a name="L615" href="source/net/ipv4/icmp.c#L615">615</a>                         <b><i>/*</i></b>
<a name="L616" href="source/net/ipv4/icmp.c#L616">616</a> <b><i>                         *      Assume any unknown ICMP type is an error. This</i></b>
<a name="L617" href="source/net/ipv4/icmp.c#L617">617</a> <b><i>                         *      isn't specified by the RFC, but think about it..</i></b>
<a name="L618" href="source/net/ipv4/icmp.c#L618">618</a> <b><i>                         */</i></b>
<a name="L619" href="source/net/ipv4/icmp.c#L619">619</a>                         if (*itp &gt; <a href="ident?i=NR_ICMP_TYPES">NR_ICMP_TYPES</a> ||
<a name="L620" href="source/net/ipv4/icmp.c#L620">620</a>                             <a href="ident?i=icmp_pointers">icmp_pointers</a>[*itp].<a href="ident?i=error">error</a>)
<a name="L621" href="source/net/ipv4/icmp.c#L621">621</a>                                 goto <a href="ident?i=out">out</a>;
<a name="L622" href="source/net/ipv4/icmp.c#L622">622</a>                 }
<a name="L623" href="source/net/ipv4/icmp.c#L623">623</a>         }
<a name="L624" href="source/net/ipv4/icmp.c#L624">624</a> 
<a name="L625" href="source/net/ipv4/icmp.c#L625">625</a>         icmp_param = <a href="ident?i=kmalloc">kmalloc</a>(sizeof(*icmp_param), <a href="ident?i=GFP_ATOMIC">GFP_ATOMIC</a>);
<a name="L626" href="source/net/ipv4/icmp.c#L626">626</a>         if (!icmp_param)
<a name="L627" href="source/net/ipv4/icmp.c#L627">627</a>                 return;
<a name="L628" href="source/net/ipv4/icmp.c#L628">628</a> 
<a name="L629" href="source/net/ipv4/icmp.c#L629">629</a>         sk = <a href="ident?i=icmp_xmit_lock">icmp_xmit_lock</a>(<a href="ident?i=net">net</a>);
<a name="L630" href="source/net/ipv4/icmp.c#L630">630</a>         if (!sk)
<a name="L631" href="source/net/ipv4/icmp.c#L631">631</a>                 goto out_free;
<a name="L632" href="source/net/ipv4/icmp.c#L632">632</a> 
<a name="L633" href="source/net/ipv4/icmp.c#L633">633</a>         <b><i>/*</i></b>
<a name="L634" href="source/net/ipv4/icmp.c#L634">634</a> <b><i>         *      Construct source address and options.</i></b>
<a name="L635" href="source/net/ipv4/icmp.c#L635">635</a> <b><i>         */</i></b>
<a name="L636" href="source/net/ipv4/icmp.c#L636">636</a> 
<a name="L637" href="source/net/ipv4/icmp.c#L637">637</a>         <a href="ident?i=saddr">saddr</a> = iph-&gt;<a href="ident?i=daddr">daddr</a>;
<a name="L638" href="source/net/ipv4/icmp.c#L638">638</a>         if (!(<a href="ident?i=rt">rt</a>-&gt;rt_flags &amp; <a href="ident?i=RTCF_LOCAL">RTCF_LOCAL</a>)) {
<a name="L639" href="source/net/ipv4/icmp.c#L639">639</a>                 struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a> = <a href="ident?i=NULL">NULL</a>;
<a name="L640" href="source/net/ipv4/icmp.c#L640">640</a> 
<a name="L641" href="source/net/ipv4/icmp.c#L641">641</a>                 <a href="ident?i=rcu_read_lock">rcu_read_lock</a>();
<a name="L642" href="source/net/ipv4/icmp.c#L642">642</a>                 if (<a href="ident?i=rt_is_input_route">rt_is_input_route</a>(<a href="ident?i=rt">rt</a>) &amp;&amp;
<a name="L643" href="source/net/ipv4/icmp.c#L643">643</a>                     <a href="ident?i=net">net</a>-&gt;ipv4.sysctl_icmp_errors_use_inbound_ifaddr)
<a name="L644" href="source/net/ipv4/icmp.c#L644">644</a>                         <a href="ident?i=dev">dev</a> = <a href="ident?i=dev_get_by_index_rcu">dev_get_by_index_rcu</a>(<a href="ident?i=net">net</a>, <a href="ident?i=inet_iif">inet_iif</a>(skb_in));
<a name="L645" href="source/net/ipv4/icmp.c#L645">645</a> 
<a name="L646" href="source/net/ipv4/icmp.c#L646">646</a>                 if (<a href="ident?i=dev">dev</a>)
<a name="L647" href="source/net/ipv4/icmp.c#L647">647</a>                         <a href="ident?i=saddr">saddr</a> = <a href="ident?i=inet_select_addr">inet_select_addr</a>(<a href="ident?i=dev">dev</a>, 0, RT_SCOPE_LINK);
<a name="L648" href="source/net/ipv4/icmp.c#L648">648</a>                 else
<a name="L649" href="source/net/ipv4/icmp.c#L649">649</a>                         <a href="ident?i=saddr">saddr</a> = 0;
<a name="L650" href="source/net/ipv4/icmp.c#L650">650</a>                 <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L651" href="source/net/ipv4/icmp.c#L651">651</a>         }
<a name="L652" href="source/net/ipv4/icmp.c#L652">652</a> 
<a name="L653" href="source/net/ipv4/icmp.c#L653">653</a>         tos = <a href="ident?i=icmp_pointers">icmp_pointers</a>[<a href="ident?i=type">type</a>].<a href="ident?i=error">error</a> ? ((iph-&gt;tos &amp; <a href="ident?i=IPTOS_TOS_MASK">IPTOS_TOS_MASK</a>) |
<a name="L654" href="source/net/ipv4/icmp.c#L654">654</a>                                            <a href="ident?i=IPTOS_PREC_INTERNETCONTROL">IPTOS_PREC_INTERNETCONTROL</a>) :
<a name="L655" href="source/net/ipv4/icmp.c#L655">655</a>                                           iph-&gt;tos;
<a name="L656" href="source/net/ipv4/icmp.c#L656">656</a>         <a href="ident?i=mark">mark</a> = <a href="ident?i=IP4_REPLY_MARK">IP4_REPLY_MARK</a>(<a href="ident?i=net">net</a>, skb_in-&gt;<a href="ident?i=mark">mark</a>);
<a name="L657" href="source/net/ipv4/icmp.c#L657">657</a> 
<a name="L658" href="source/net/ipv4/icmp.c#L658">658</a>         if (<a href="ident?i=ip_options_echo">ip_options_echo</a>(&amp;icmp_param-&gt;replyopts.opt.opt, skb_in))
<a name="L659" href="source/net/ipv4/icmp.c#L659">659</a>                 goto out_unlock;
<a name="L660" href="source/net/ipv4/icmp.c#L660">660</a> 
<a name="L661" href="source/net/ipv4/icmp.c#L661">661</a> 
<a name="L662" href="source/net/ipv4/icmp.c#L662">662</a>         <b><i>/*</i></b>
<a name="L663" href="source/net/ipv4/icmp.c#L663">663</a> <b><i>         *      Prepare data for ICMP header.</i></b>
<a name="L664" href="source/net/ipv4/icmp.c#L664">664</a> <b><i>         */</i></b>
<a name="L665" href="source/net/ipv4/icmp.c#L665">665</a> 
<a name="L666" href="source/net/ipv4/icmp.c#L666">666</a>         icmp_param-&gt;<a href="ident?i=data">data</a>.icmph.<a href="ident?i=type">type</a>      = <a href="ident?i=type">type</a>;
<a name="L667" href="source/net/ipv4/icmp.c#L667">667</a>         icmp_param-&gt;<a href="ident?i=data">data</a>.icmph.<a href="ident?i=code">code</a>      = <a href="ident?i=code">code</a>;
<a name="L668" href="source/net/ipv4/icmp.c#L668">668</a>         icmp_param-&gt;<a href="ident?i=data">data</a>.icmph.un.gateway = <a href="ident?i=info">info</a>;
<a name="L669" href="source/net/ipv4/icmp.c#L669">669</a>         icmp_param-&gt;<a href="ident?i=data">data</a>.icmph.<a href="ident?i=checksum">checksum</a>  = 0;
<a name="L670" href="source/net/ipv4/icmp.c#L670">670</a>         icmp_param-&gt;<a href="ident?i=skb">skb</a>   = skb_in;
<a name="L671" href="source/net/ipv4/icmp.c#L671">671</a>         icmp_param-&gt;<a href="ident?i=offset">offset</a> = <a href="ident?i=skb_network_offset">skb_network_offset</a>(skb_in);
<a name="L672" href="source/net/ipv4/icmp.c#L672">672</a>         <a href="ident?i=inet_sk">inet_sk</a>(sk)-&gt;tos = tos;
<a name="L673" href="source/net/ipv4/icmp.c#L673">673</a>         sk-&gt;sk_mark = <a href="ident?i=mark">mark</a>;
<a name="L674" href="source/net/ipv4/icmp.c#L674">674</a>         ipc.<a href="ident?i=addr">addr</a> = iph-&gt;<a href="ident?i=saddr">saddr</a>;
<a name="L675" href="source/net/ipv4/icmp.c#L675">675</a>         ipc.opt = &amp;icmp_param-&gt;replyopts.opt;
<a name="L676" href="source/net/ipv4/icmp.c#L676">676</a>         ipc.tx_flags = 0;
<a name="L677" href="source/net/ipv4/icmp.c#L677">677</a>         ipc.<a href="ident?i=ttl">ttl</a> = 0;
<a name="L678" href="source/net/ipv4/icmp.c#L678">678</a>         ipc.tos = -1;
<a name="L679" href="source/net/ipv4/icmp.c#L679">679</a> 
<a name="L680" href="source/net/ipv4/icmp.c#L680">680</a>         <a href="ident?i=rt">rt</a> = <a href="ident?i=icmp_route_lookup">icmp_route_lookup</a>(<a href="ident?i=net">net</a>, &amp;fl4, skb_in, iph, <a href="ident?i=saddr">saddr</a>, tos, <a href="ident?i=mark">mark</a>,
<a name="L681" href="source/net/ipv4/icmp.c#L681">681</a>                                <a href="ident?i=type">type</a>, <a href="ident?i=code">code</a>, icmp_param);
<a name="L682" href="source/net/ipv4/icmp.c#L682">682</a>         if (<a href="ident?i=IS_ERR">IS_ERR</a>(<a href="ident?i=rt">rt</a>))
<a name="L683" href="source/net/ipv4/icmp.c#L683">683</a>                 goto out_unlock;
<a name="L684" href="source/net/ipv4/icmp.c#L684">684</a> 
<a name="L685" href="source/net/ipv4/icmp.c#L685">685</a>         if (!<a href="ident?i=icmpv4_xrlim_allow">icmpv4_xrlim_allow</a>(<a href="ident?i=net">net</a>, <a href="ident?i=rt">rt</a>, &amp;fl4, <a href="ident?i=type">type</a>, <a href="ident?i=code">code</a>))
<a name="L686" href="source/net/ipv4/icmp.c#L686">686</a>                 goto ende;
<a name="L687" href="source/net/ipv4/icmp.c#L687">687</a> 
<a name="L688" href="source/net/ipv4/icmp.c#L688">688</a>         <b><i>/* RFC says return as much as we can without exceeding 576 bytes. */</i></b>
<a name="L689" href="source/net/ipv4/icmp.c#L689">689</a> 
<a name="L690" href="source/net/ipv4/icmp.c#L690">690</a>         room = <a href="ident?i=dst_mtu">dst_mtu</a>(&amp;<a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>);
<a name="L691" href="source/net/ipv4/icmp.c#L691">691</a>         if (room &gt; 576)
<a name="L692" href="source/net/ipv4/icmp.c#L692">692</a>                 room = 576;
<a name="L693" href="source/net/ipv4/icmp.c#L693">693</a>         room -= sizeof(struct <a href="ident?i=iphdr">iphdr</a>) + icmp_param-&gt;replyopts.opt.opt.<a href="ident?i=optlen">optlen</a>;
<a name="L694" href="source/net/ipv4/icmp.c#L694">694</a>         room -= sizeof(struct <a href="ident?i=icmphdr">icmphdr</a>);
<a name="L695" href="source/net/ipv4/icmp.c#L695">695</a> 
<a name="L696" href="source/net/ipv4/icmp.c#L696">696</a>         icmp_param-&gt;<a href="ident?i=data_len">data_len</a> = skb_in-&gt;<a href="ident?i=len">len</a> - icmp_param-&gt;<a href="ident?i=offset">offset</a>;
<a name="L697" href="source/net/ipv4/icmp.c#L697">697</a>         if (icmp_param-&gt;<a href="ident?i=data_len">data_len</a> &gt; room)
<a name="L698" href="source/net/ipv4/icmp.c#L698">698</a>                 icmp_param-&gt;<a href="ident?i=data_len">data_len</a> = room;
<a name="L699" href="source/net/ipv4/icmp.c#L699">699</a>         icmp_param-&gt;head_len = sizeof(struct <a href="ident?i=icmphdr">icmphdr</a>);
<a name="L700" href="source/net/ipv4/icmp.c#L700">700</a> 
<a name="L701" href="source/net/ipv4/icmp.c#L701">701</a>         <a href="ident?i=icmp_push_reply">icmp_push_reply</a>(icmp_param, &amp;fl4, &amp;ipc, &amp;<a href="ident?i=rt">rt</a>);
<a name="L702" href="source/net/ipv4/icmp.c#L702">702</a> ende:
<a name="L703" href="source/net/ipv4/icmp.c#L703">703</a>         <a href="ident?i=ip_rt_put">ip_rt_put</a>(<a href="ident?i=rt">rt</a>);
<a name="L704" href="source/net/ipv4/icmp.c#L704">704</a> out_unlock:
<a name="L705" href="source/net/ipv4/icmp.c#L705">705</a>         <a href="ident?i=icmp_xmit_unlock">icmp_xmit_unlock</a>(sk);
<a name="L706" href="source/net/ipv4/icmp.c#L706">706</a> out_free:
<a name="L707" href="source/net/ipv4/icmp.c#L707">707</a>         <a href="ident?i=kfree">kfree</a>(icmp_param);
<a name="L708" href="source/net/ipv4/icmp.c#L708">708</a> <a href="ident?i=out">out</a>:;
<a name="L709" href="source/net/ipv4/icmp.c#L709">709</a> }
<a name="L710" href="source/net/ipv4/icmp.c#L710">710</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=icmp_send">icmp_send</a>);
<a name="L711" href="source/net/ipv4/icmp.c#L711">711</a> 
<a name="L712" href="source/net/ipv4/icmp.c#L712">712</a> 
<a name="L713" href="source/net/ipv4/icmp.c#L713">713</a> static void <a href="ident?i=icmp_socket_deliver">icmp_socket_deliver</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, <a href="ident?i=u32">u32</a> <a href="ident?i=info">info</a>)
<a name="L714" href="source/net/ipv4/icmp.c#L714">714</a> {
<a name="L715" href="source/net/ipv4/icmp.c#L715">715</a>         const struct <a href="ident?i=iphdr">iphdr</a> *iph = (const struct <a href="ident?i=iphdr">iphdr</a> *) <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=data">data</a>;
<a name="L716" href="source/net/ipv4/icmp.c#L716">716</a>         const struct <a href="ident?i=net_protocol">net_protocol</a> *ipprot;
<a name="L717" href="source/net/ipv4/icmp.c#L717">717</a>         int <a href="ident?i=protocol">protocol</a> = iph-&gt;<a href="ident?i=protocol">protocol</a>;
<a name="L718" href="source/net/ipv4/icmp.c#L718">718</a> 
<a name="L719" href="source/net/ipv4/icmp.c#L719">719</a>         <b><i>/* Checkin full IP header plus 8 bytes of protocol to</i></b>
<a name="L720" href="source/net/ipv4/icmp.c#L720">720</a> <b><i>         * avoid additional coding at protocol handlers.</i></b>
<a name="L721" href="source/net/ipv4/icmp.c#L721">721</a> <b><i>         */</i></b>
<a name="L722" href="source/net/ipv4/icmp.c#L722">722</a>         if (!<a href="ident?i=pskb_may_pull">pskb_may_pull</a>(<a href="ident?i=skb">skb</a>, iph-&gt;ihl * 4 + 8)) {
<a name="L723" href="source/net/ipv4/icmp.c#L723">723</a>                 <a href="ident?i=ICMP_INC_STATS_BH">ICMP_INC_STATS_BH</a>(<a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=dev">dev</a>), ICMP_MIB_INERRORS);
<a name="L724" href="source/net/ipv4/icmp.c#L724">724</a>                 return;
<a name="L725" href="source/net/ipv4/icmp.c#L725">725</a>         }
<a name="L726" href="source/net/ipv4/icmp.c#L726">726</a> 
<a name="L727" href="source/net/ipv4/icmp.c#L727">727</a>         <a href="ident?i=raw_icmp_error">raw_icmp_error</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=protocol">protocol</a>, <a href="ident?i=info">info</a>);
<a name="L728" href="source/net/ipv4/icmp.c#L728">728</a> 
<a name="L729" href="source/net/ipv4/icmp.c#L729">729</a>         ipprot = <a href="ident?i=rcu_dereference">rcu_dereference</a>(<a href="ident?i=inet_protos">inet_protos</a>[<a href="ident?i=protocol">protocol</a>]);
<a name="L730" href="source/net/ipv4/icmp.c#L730">730</a>         if (ipprot &amp;&amp; ipprot-&gt;<a href="ident?i=err_handler">err_handler</a>)
<a name="L731" href="source/net/ipv4/icmp.c#L731">731</a>                 ipprot-&gt;<a href="ident?i=err_handler">err_handler</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=info">info</a>);
<a name="L732" href="source/net/ipv4/icmp.c#L732">732</a> }
<a name="L733" href="source/net/ipv4/icmp.c#L733">733</a> 
<a name="L734" href="source/net/ipv4/icmp.c#L734">734</a> static <a href="ident?i=bool">bool</a> <a href="ident?i=icmp_tag_validation">icmp_tag_validation</a>(int <a href="ident?i=proto">proto</a>)
<a name="L735" href="source/net/ipv4/icmp.c#L735">735</a> {
<a name="L736" href="source/net/ipv4/icmp.c#L736">736</a>         <a href="ident?i=bool">bool</a> <a href="ident?i=ok">ok</a>;
<a name="L737" href="source/net/ipv4/icmp.c#L737">737</a> 
<a name="L738" href="source/net/ipv4/icmp.c#L738">738</a>         <a href="ident?i=rcu_read_lock">rcu_read_lock</a>();
<a name="L739" href="source/net/ipv4/icmp.c#L739">739</a>         <a href="ident?i=ok">ok</a> = <a href="ident?i=rcu_dereference">rcu_dereference</a>(<a href="ident?i=inet_protos">inet_protos</a>[<a href="ident?i=proto">proto</a>])-&gt;icmp_strict_tag_validation;
<a name="L740" href="source/net/ipv4/icmp.c#L740">740</a>         <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L741" href="source/net/ipv4/icmp.c#L741">741</a>         return <a href="ident?i=ok">ok</a>;
<a name="L742" href="source/net/ipv4/icmp.c#L742">742</a> }
<a name="L743" href="source/net/ipv4/icmp.c#L743">743</a> 
<a name="L744" href="source/net/ipv4/icmp.c#L744">744</a> <b><i>/*</i></b>
<a name="L745" href="source/net/ipv4/icmp.c#L745">745</a> <b><i> *      Handle ICMP_DEST_UNREACH, ICMP_TIME_EXCEED, ICMP_QUENCH, and</i></b>
<a name="L746" href="source/net/ipv4/icmp.c#L746">746</a> <b><i> *      ICMP_PARAMETERPROB.</i></b>
<a name="L747" href="source/net/ipv4/icmp.c#L747">747</a> <b><i> */</i></b>
<a name="L748" href="source/net/ipv4/icmp.c#L748">748</a> 
<a name="L749" href="source/net/ipv4/icmp.c#L749">749</a> static <a href="ident?i=bool">bool</a> <a href="ident?i=icmp_unreach">icmp_unreach</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L750" href="source/net/ipv4/icmp.c#L750">750</a> {
<a name="L751" href="source/net/ipv4/icmp.c#L751">751</a>         const struct <a href="ident?i=iphdr">iphdr</a> *iph;
<a name="L752" href="source/net/ipv4/icmp.c#L752">752</a>         struct <a href="ident?i=icmphdr">icmphdr</a> *icmph;
<a name="L753" href="source/net/ipv4/icmp.c#L753">753</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>;
<a name="L754" href="source/net/ipv4/icmp.c#L754">754</a>         <a href="ident?i=u32">u32</a> <a href="ident?i=info">info</a> = 0;
<a name="L755" href="source/net/ipv4/icmp.c#L755">755</a> 
<a name="L756" href="source/net/ipv4/icmp.c#L756">756</a>         <a href="ident?i=net">net</a> = <a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=skb_dst">skb_dst</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=dev">dev</a>);
<a name="L757" href="source/net/ipv4/icmp.c#L757">757</a> 
<a name="L758" href="source/net/ipv4/icmp.c#L758">758</a>         <b><i>/*</i></b>
<a name="L759" href="source/net/ipv4/icmp.c#L759">759</a> <b><i>         *      Incomplete header ?</i></b>
<a name="L760" href="source/net/ipv4/icmp.c#L760">760</a> <b><i>         *      Only checks for the IP header, there should be an</i></b>
<a name="L761" href="source/net/ipv4/icmp.c#L761">761</a> <b><i>         *      additional check for longer headers in upper levels.</i></b>
<a name="L762" href="source/net/ipv4/icmp.c#L762">762</a> <b><i>         */</i></b>
<a name="L763" href="source/net/ipv4/icmp.c#L763">763</a> 
<a name="L764" href="source/net/ipv4/icmp.c#L764">764</a>         if (!<a href="ident?i=pskb_may_pull">pskb_may_pull</a>(<a href="ident?i=skb">skb</a>, sizeof(struct <a href="ident?i=iphdr">iphdr</a>)))
<a name="L765" href="source/net/ipv4/icmp.c#L765">765</a>                 goto out_err;
<a name="L766" href="source/net/ipv4/icmp.c#L766">766</a> 
<a name="L767" href="source/net/ipv4/icmp.c#L767">767</a>         icmph = <a href="ident?i=icmp_hdr">icmp_hdr</a>(<a href="ident?i=skb">skb</a>);
<a name="L768" href="source/net/ipv4/icmp.c#L768">768</a>         iph   = (const struct <a href="ident?i=iphdr">iphdr</a> *)<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=data">data</a>;
<a name="L769" href="source/net/ipv4/icmp.c#L769">769</a> 
<a name="L770" href="source/net/ipv4/icmp.c#L770">770</a>         if (iph-&gt;ihl &lt; 5) <b><i>/* Mangled header, drop. */</i></b>
<a name="L771" href="source/net/ipv4/icmp.c#L771">771</a>                 goto out_err;
<a name="L772" href="source/net/ipv4/icmp.c#L772">772</a> 
<a name="L773" href="source/net/ipv4/icmp.c#L773">773</a>         if (icmph-&gt;<a href="ident?i=type">type</a> == <a href="ident?i=ICMP_DEST_UNREACH">ICMP_DEST_UNREACH</a>) {
<a name="L774" href="source/net/ipv4/icmp.c#L774">774</a>                 switch (icmph-&gt;<a href="ident?i=code">code</a> &amp; 15) {
<a name="L775" href="source/net/ipv4/icmp.c#L775">775</a>                 case <a href="ident?i=ICMP_NET_UNREACH">ICMP_NET_UNREACH</a>:
<a name="L776" href="source/net/ipv4/icmp.c#L776">776</a>                 case <a href="ident?i=ICMP_HOST_UNREACH">ICMP_HOST_UNREACH</a>:
<a name="L777" href="source/net/ipv4/icmp.c#L777">777</a>                 case <a href="ident?i=ICMP_PROT_UNREACH">ICMP_PROT_UNREACH</a>:
<a name="L778" href="source/net/ipv4/icmp.c#L778">778</a>                 case <a href="ident?i=ICMP_PORT_UNREACH">ICMP_PORT_UNREACH</a>:
<a name="L779" href="source/net/ipv4/icmp.c#L779">779</a>                         break;
<a name="L780" href="source/net/ipv4/icmp.c#L780">780</a>                 case <a href="ident?i=ICMP_FRAG_NEEDED">ICMP_FRAG_NEEDED</a>:
<a name="L781" href="source/net/ipv4/icmp.c#L781">781</a>                         <b><i>/* for documentation of the ip_no_pmtu_disc</i></b>
<a name="L782" href="source/net/ipv4/icmp.c#L782">782</a> <b><i>                         * values please see</i></b>
<a name="L783" href="source/net/ipv4/icmp.c#L783">783</a> <b><i>                         * Documentation/networking/ip-sysctl.txt</i></b>
<a name="L784" href="source/net/ipv4/icmp.c#L784">784</a> <b><i>                         */</i></b>
<a name="L785" href="source/net/ipv4/icmp.c#L785">785</a>                         switch (<a href="ident?i=net">net</a>-&gt;ipv4.sysctl_ip_no_pmtu_disc) {
<a name="L786" href="source/net/ipv4/icmp.c#L786">786</a>                         default:
<a name="L787" href="source/net/ipv4/icmp.c#L787">787</a>                                 <a href="ident?i=net_dbg_ratelimited">net_dbg_ratelimited</a>(<i>"%pI4: fragmentation needed and DF set\n"</i>,
<a name="L788" href="source/net/ipv4/icmp.c#L788">788</a>                                                     &amp;iph-&gt;<a href="ident?i=daddr">daddr</a>);
<a name="L789" href="source/net/ipv4/icmp.c#L789">789</a>                                 break;
<a name="L790" href="source/net/ipv4/icmp.c#L790">790</a>                         case 2:
<a name="L791" href="source/net/ipv4/icmp.c#L791">791</a>                                 goto <a href="ident?i=out">out</a>;
<a name="L792" href="source/net/ipv4/icmp.c#L792">792</a>                         case 3:
<a name="L793" href="source/net/ipv4/icmp.c#L793">793</a>                                 if (!<a href="ident?i=icmp_tag_validation">icmp_tag_validation</a>(iph-&gt;<a href="ident?i=protocol">protocol</a>))
<a name="L794" href="source/net/ipv4/icmp.c#L794">794</a>                                         goto <a href="ident?i=out">out</a>;
<a name="L795" href="source/net/ipv4/icmp.c#L795">795</a>                                 <b><i>/* fall through */</i></b>
<a name="L796" href="source/net/ipv4/icmp.c#L796">796</a>                         case 0:
<a name="L797" href="source/net/ipv4/icmp.c#L797">797</a>                                 <a href="ident?i=info">info</a> = <a href="ident?i=ntohs">ntohs</a>(icmph-&gt;un.<a href="ident?i=frag">frag</a>.<a href="ident?i=mtu">mtu</a>);
<a name="L798" href="source/net/ipv4/icmp.c#L798">798</a>                         }
<a name="L799" href="source/net/ipv4/icmp.c#L799">799</a>                         break;
<a name="L800" href="source/net/ipv4/icmp.c#L800">800</a>                 case <a href="ident?i=ICMP_SR_FAILED">ICMP_SR_FAILED</a>:
<a name="L801" href="source/net/ipv4/icmp.c#L801">801</a>                         <a href="ident?i=net_dbg_ratelimited">net_dbg_ratelimited</a>(<i>"%pI4: Source Route Failed\n"</i>,
<a name="L802" href="source/net/ipv4/icmp.c#L802">802</a>                                             &amp;iph-&gt;<a href="ident?i=daddr">daddr</a>);
<a name="L803" href="source/net/ipv4/icmp.c#L803">803</a>                         break;
<a name="L804" href="source/net/ipv4/icmp.c#L804">804</a>                 default:
<a name="L805" href="source/net/ipv4/icmp.c#L805">805</a>                         break;
<a name="L806" href="source/net/ipv4/icmp.c#L806">806</a>                 }
<a name="L807" href="source/net/ipv4/icmp.c#L807">807</a>                 if (icmph-&gt;<a href="ident?i=code">code</a> &gt; <a href="ident?i=NR_ICMP_UNREACH">NR_ICMP_UNREACH</a>)
<a name="L808" href="source/net/ipv4/icmp.c#L808">808</a>                         goto <a href="ident?i=out">out</a>;
<a name="L809" href="source/net/ipv4/icmp.c#L809">809</a>         } else if (icmph-&gt;<a href="ident?i=type">type</a> == <a href="ident?i=ICMP_PARAMETERPROB">ICMP_PARAMETERPROB</a>)
<a name="L810" href="source/net/ipv4/icmp.c#L810">810</a>                 <a href="ident?i=info">info</a> = <a href="ident?i=ntohl">ntohl</a>(icmph-&gt;un.gateway) &gt;&gt; 24;
<a name="L811" href="source/net/ipv4/icmp.c#L811">811</a> 
<a name="L812" href="source/net/ipv4/icmp.c#L812">812</a>         <b><i>/*</i></b>
<a name="L813" href="source/net/ipv4/icmp.c#L813">813</a> <b><i>         *      Throw it at our lower layers</i></b>
<a name="L814" href="source/net/ipv4/icmp.c#L814">814</a> <b><i>         *</i></b>
<a name="L815" href="source/net/ipv4/icmp.c#L815">815</a> <b><i>         *      RFC 1122: 3.2.2 MUST extract the protocol ID from the passed</i></b>
<a name="L816" href="source/net/ipv4/icmp.c#L816">816</a> <b><i>         *                header.</i></b>
<a name="L817" href="source/net/ipv4/icmp.c#L817">817</a> <b><i>         *      RFC 1122: 3.2.2.1 MUST pass ICMP unreach messages to the</i></b>
<a name="L818" href="source/net/ipv4/icmp.c#L818">818</a> <b><i>         *                transport layer.</i></b>
<a name="L819" href="source/net/ipv4/icmp.c#L819">819</a> <b><i>         *      RFC 1122: 3.2.2.2 MUST pass ICMP time expired messages to</i></b>
<a name="L820" href="source/net/ipv4/icmp.c#L820">820</a> <b><i>         *                transport layer.</i></b>
<a name="L821" href="source/net/ipv4/icmp.c#L821">821</a> <b><i>         */</i></b>
<a name="L822" href="source/net/ipv4/icmp.c#L822">822</a> 
<a name="L823" href="source/net/ipv4/icmp.c#L823">823</a>         <b><i>/*</i></b>
<a name="L824" href="source/net/ipv4/icmp.c#L824">824</a> <b><i>         *      Check the other end isn't violating RFC 1122. Some routers send</i></b>
<a name="L825" href="source/net/ipv4/icmp.c#L825">825</a> <b><i>         *      bogus responses to broadcast frames. If you see this message</i></b>
<a name="L826" href="source/net/ipv4/icmp.c#L826">826</a> <b><i>         *      first check your netmask matches at both ends, if it does then</i></b>
<a name="L827" href="source/net/ipv4/icmp.c#L827">827</a> <b><i>         *      get the other vendor to fix their kit.</i></b>
<a name="L828" href="source/net/ipv4/icmp.c#L828">828</a> <b><i>         */</i></b>
<a name="L829" href="source/net/ipv4/icmp.c#L829">829</a> 
<a name="L830" href="source/net/ipv4/icmp.c#L830">830</a>         if (!<a href="ident?i=net">net</a>-&gt;ipv4.sysctl_icmp_ignore_bogus_error_responses &amp;&amp;
<a name="L831" href="source/net/ipv4/icmp.c#L831">831</a>             <a href="ident?i=inet_addr_type">inet_addr_type</a>(<a href="ident?i=net">net</a>, iph-&gt;<a href="ident?i=daddr">daddr</a>) == RTN_BROADCAST) {
<a name="L832" href="source/net/ipv4/icmp.c#L832">832</a>                 <a href="ident?i=net_warn_ratelimited">net_warn_ratelimited</a>(<i>"%pI4 sent an invalid ICMP type %u, code %u error to a broadcast: %pI4 on %s\n"</i>,
<a name="L833" href="source/net/ipv4/icmp.c#L833">833</a>                                      &amp;<a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=saddr">saddr</a>,
<a name="L834" href="source/net/ipv4/icmp.c#L834">834</a>                                      icmph-&gt;<a href="ident?i=type">type</a>, icmph-&gt;<a href="ident?i=code">code</a>,
<a name="L835" href="source/net/ipv4/icmp.c#L835">835</a>                                      &amp;iph-&gt;<a href="ident?i=daddr">daddr</a>, <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=name">name</a>);
<a name="L836" href="source/net/ipv4/icmp.c#L836">836</a>                 goto <a href="ident?i=out">out</a>;
<a name="L837" href="source/net/ipv4/icmp.c#L837">837</a>         }
<a name="L838" href="source/net/ipv4/icmp.c#L838">838</a> 
<a name="L839" href="source/net/ipv4/icmp.c#L839">839</a>         <a href="ident?i=icmp_socket_deliver">icmp_socket_deliver</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=info">info</a>);
<a name="L840" href="source/net/ipv4/icmp.c#L840">840</a> 
<a name="L841" href="source/net/ipv4/icmp.c#L841">841</a> <a href="ident?i=out">out</a>:
<a name="L842" href="source/net/ipv4/icmp.c#L842">842</a>         return <a href="ident?i=true">true</a>;
<a name="L843" href="source/net/ipv4/icmp.c#L843">843</a> out_err:
<a name="L844" href="source/net/ipv4/icmp.c#L844">844</a>         <a href="ident?i=ICMP_INC_STATS_BH">ICMP_INC_STATS_BH</a>(<a href="ident?i=net">net</a>, ICMP_MIB_INERRORS);
<a name="L845" href="source/net/ipv4/icmp.c#L845">845</a>         return <a href="ident?i=false">false</a>;
<a name="L846" href="source/net/ipv4/icmp.c#L846">846</a> }
<a name="L847" href="source/net/ipv4/icmp.c#L847">847</a> 
<a name="L848" href="source/net/ipv4/icmp.c#L848">848</a> 
<a name="L849" href="source/net/ipv4/icmp.c#L849">849</a> <b><i>/*</i></b>
<a name="L850" href="source/net/ipv4/icmp.c#L850">850</a> <b><i> *      Handle ICMP_REDIRECT.</i></b>
<a name="L851" href="source/net/ipv4/icmp.c#L851">851</a> <b><i> */</i></b>
<a name="L852" href="source/net/ipv4/icmp.c#L852">852</a> 
<a name="L853" href="source/net/ipv4/icmp.c#L853">853</a> static <a href="ident?i=bool">bool</a> <a href="ident?i=icmp_redirect">icmp_redirect</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L854" href="source/net/ipv4/icmp.c#L854">854</a> {
<a name="L855" href="source/net/ipv4/icmp.c#L855">855</a>         if (<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a> &lt; sizeof(struct <a href="ident?i=iphdr">iphdr</a>)) {
<a name="L856" href="source/net/ipv4/icmp.c#L856">856</a>                 <a href="ident?i=ICMP_INC_STATS_BH">ICMP_INC_STATS_BH</a>(<a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=dev">dev</a>), ICMP_MIB_INERRORS);
<a name="L857" href="source/net/ipv4/icmp.c#L857">857</a>                 return <a href="ident?i=false">false</a>;
<a name="L858" href="source/net/ipv4/icmp.c#L858">858</a>         }
<a name="L859" href="source/net/ipv4/icmp.c#L859">859</a> 
<a name="L860" href="source/net/ipv4/icmp.c#L860">860</a>         if (!<a href="ident?i=pskb_may_pull">pskb_may_pull</a>(<a href="ident?i=skb">skb</a>, sizeof(struct <a href="ident?i=iphdr">iphdr</a>))) {
<a name="L861" href="source/net/ipv4/icmp.c#L861">861</a>                 <b><i>/* there aught to be a stat */</i></b>
<a name="L862" href="source/net/ipv4/icmp.c#L862">862</a>                 return <a href="ident?i=false">false</a>;
<a name="L863" href="source/net/ipv4/icmp.c#L863">863</a>         }
<a name="L864" href="source/net/ipv4/icmp.c#L864">864</a> 
<a name="L865" href="source/net/ipv4/icmp.c#L865">865</a>         <a href="ident?i=icmp_socket_deliver">icmp_socket_deliver</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=icmp_hdr">icmp_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;un.gateway);
<a name="L866" href="source/net/ipv4/icmp.c#L866">866</a>         return <a href="ident?i=true">true</a>;
<a name="L867" href="source/net/ipv4/icmp.c#L867">867</a> }
<a name="L868" href="source/net/ipv4/icmp.c#L868">868</a> 
<a name="L869" href="source/net/ipv4/icmp.c#L869">869</a> <b><i>/*</i></b>
<a name="L870" href="source/net/ipv4/icmp.c#L870">870</a> <b><i> *      Handle ICMP_ECHO ("ping") requests.</i></b>
<a name="L871" href="source/net/ipv4/icmp.c#L871">871</a> <b><i> *</i></b>
<a name="L872" href="source/net/ipv4/icmp.c#L872">872</a> <b><i> *      RFC 1122: 3.2.2.6 MUST have an echo server that answers ICMP echo</i></b>
<a name="L873" href="source/net/ipv4/icmp.c#L873">873</a> <b><i> *                requests.</i></b>
<a name="L874" href="source/net/ipv4/icmp.c#L874">874</a> <b><i> *      RFC 1122: 3.2.2.6 Data received in the ICMP_ECHO request MUST be</i></b>
<a name="L875" href="source/net/ipv4/icmp.c#L875">875</a> <b><i> *                included in the reply.</i></b>
<a name="L876" href="source/net/ipv4/icmp.c#L876">876</a> <b><i> *      RFC 1812: 4.3.3.6 SHOULD have a config option for silently ignoring</i></b>
<a name="L877" href="source/net/ipv4/icmp.c#L877">877</a> <b><i> *                echo requests, MUST have default=NOT.</i></b>
<a name="L878" href="source/net/ipv4/icmp.c#L878">878</a> <b><i> *      See also WRT handling of options once they are done and working.</i></b>
<a name="L879" href="source/net/ipv4/icmp.c#L879">879</a> <b><i> */</i></b>
<a name="L880" href="source/net/ipv4/icmp.c#L880">880</a> 
<a name="L881" href="source/net/ipv4/icmp.c#L881">881</a> static <a href="ident?i=bool">bool</a> <a href="ident?i=icmp_echo">icmp_echo</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L882" href="source/net/ipv4/icmp.c#L882">882</a> {
<a name="L883" href="source/net/ipv4/icmp.c#L883">883</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>;
<a name="L884" href="source/net/ipv4/icmp.c#L884">884</a> 
<a name="L885" href="source/net/ipv4/icmp.c#L885">885</a>         <a href="ident?i=net">net</a> = <a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=skb_dst">skb_dst</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=dev">dev</a>);
<a name="L886" href="source/net/ipv4/icmp.c#L886">886</a>         if (!<a href="ident?i=net">net</a>-&gt;ipv4.sysctl_icmp_echo_ignore_all) {
<a name="L887" href="source/net/ipv4/icmp.c#L887">887</a>                 struct <a href="ident?i=icmp_bxm">icmp_bxm</a> icmp_param;
<a name="L888" href="source/net/ipv4/icmp.c#L888">888</a> 
<a name="L889" href="source/net/ipv4/icmp.c#L889">889</a>                 icmp_param.<a href="ident?i=data">data</a>.icmph      = *<a href="ident?i=icmp_hdr">icmp_hdr</a>(<a href="ident?i=skb">skb</a>);
<a name="L890" href="source/net/ipv4/icmp.c#L890">890</a>                 icmp_param.<a href="ident?i=data">data</a>.icmph.<a href="ident?i=type">type</a> = <a href="ident?i=ICMP_ECHOREPLY">ICMP_ECHOREPLY</a>;
<a name="L891" href="source/net/ipv4/icmp.c#L891">891</a>                 icmp_param.<a href="ident?i=skb">skb</a>             = <a href="ident?i=skb">skb</a>;
<a name="L892" href="source/net/ipv4/icmp.c#L892">892</a>                 icmp_param.<a href="ident?i=offset">offset</a>          = 0;
<a name="L893" href="source/net/ipv4/icmp.c#L893">893</a>                 icmp_param.<a href="ident?i=data_len">data_len</a>        = <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a>;
<a name="L894" href="source/net/ipv4/icmp.c#L894">894</a>                 icmp_param.head_len        = sizeof(struct <a href="ident?i=icmphdr">icmphdr</a>);
<a name="L895" href="source/net/ipv4/icmp.c#L895">895</a>                 <a href="ident?i=icmp_reply">icmp_reply</a>(&amp;icmp_param, <a href="ident?i=skb">skb</a>);
<a name="L896" href="source/net/ipv4/icmp.c#L896">896</a>         }
<a name="L897" href="source/net/ipv4/icmp.c#L897">897</a>         <b><i>/* should there be an ICMP stat for ignored echos? */</i></b>
<a name="L898" href="source/net/ipv4/icmp.c#L898">898</a>         return <a href="ident?i=true">true</a>;
<a name="L899" href="source/net/ipv4/icmp.c#L899">899</a> }
<a name="L900" href="source/net/ipv4/icmp.c#L900">900</a> 
<a name="L901" href="source/net/ipv4/icmp.c#L901">901</a> <b><i>/*</i></b>
<a name="L902" href="source/net/ipv4/icmp.c#L902">902</a> <b><i> *      Handle ICMP Timestamp requests.</i></b>
<a name="L903" href="source/net/ipv4/icmp.c#L903">903</a> <b><i> *      RFC 1122: 3.2.2.8 MAY implement ICMP timestamp requests.</i></b>
<a name="L904" href="source/net/ipv4/icmp.c#L904">904</a> <b><i> *                SHOULD be in the kernel for minimum random latency.</i></b>
<a name="L905" href="source/net/ipv4/icmp.c#L905">905</a> <b><i> *                MUST be accurate to a few minutes.</i></b>
<a name="L906" href="source/net/ipv4/icmp.c#L906">906</a> <b><i> *                MUST be updated at least at 15Hz.</i></b>
<a name="L907" href="source/net/ipv4/icmp.c#L907">907</a> <b><i> */</i></b>
<a name="L908" href="source/net/ipv4/icmp.c#L908">908</a> static <a href="ident?i=bool">bool</a> <a href="ident?i=icmp_timestamp">icmp_timestamp</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L909" href="source/net/ipv4/icmp.c#L909">909</a> {
<a name="L910" href="source/net/ipv4/icmp.c#L910">910</a>         struct <a href="ident?i=timespec">timespec</a> tv;
<a name="L911" href="source/net/ipv4/icmp.c#L911">911</a>         struct <a href="ident?i=icmp_bxm">icmp_bxm</a> icmp_param;
<a name="L912" href="source/net/ipv4/icmp.c#L912">912</a>         <b><i>/*</i></b>
<a name="L913" href="source/net/ipv4/icmp.c#L913">913</a> <b><i>         *      Too short.</i></b>
<a name="L914" href="source/net/ipv4/icmp.c#L914">914</a> <b><i>         */</i></b>
<a name="L915" href="source/net/ipv4/icmp.c#L915">915</a>         if (<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a> &lt; 4)
<a name="L916" href="source/net/ipv4/icmp.c#L916">916</a>                 goto out_err;
<a name="L917" href="source/net/ipv4/icmp.c#L917">917</a> 
<a name="L918" href="source/net/ipv4/icmp.c#L918">918</a>         <b><i>/*</i></b>
<a name="L919" href="source/net/ipv4/icmp.c#L919">919</a> <b><i>         *      Fill in the current time as ms since midnight UT:</i></b>
<a name="L920" href="source/net/ipv4/icmp.c#L920">920</a> <b><i>         */</i></b>
<a name="L921" href="source/net/ipv4/icmp.c#L921">921</a>         <a href="ident?i=getnstimeofday">getnstimeofday</a>(&amp;tv);
<a name="L922" href="source/net/ipv4/icmp.c#L922">922</a>         icmp_param.<a href="ident?i=data">data</a>.times[1] = <a href="ident?i=htonl">htonl</a>((tv.tv_sec % 86400) * <a href="ident?i=MSEC_PER_SEC">MSEC_PER_SEC</a> +
<a name="L923" href="source/net/ipv4/icmp.c#L923">923</a>                                          tv.tv_nsec / <a href="ident?i=NSEC_PER_MSEC">NSEC_PER_MSEC</a>);
<a name="L924" href="source/net/ipv4/icmp.c#L924">924</a>         icmp_param.<a href="ident?i=data">data</a>.times[2] = icmp_param.<a href="ident?i=data">data</a>.times[1];
<a name="L925" href="source/net/ipv4/icmp.c#L925">925</a>         if (<a href="ident?i=skb_copy_bits">skb_copy_bits</a>(<a href="ident?i=skb">skb</a>, 0, &amp;icmp_param.<a href="ident?i=data">data</a>.times[0], 4))
<a name="L926" href="source/net/ipv4/icmp.c#L926">926</a>                 <a href="ident?i=BUG">BUG</a>();
<a name="L927" href="source/net/ipv4/icmp.c#L927">927</a>         icmp_param.<a href="ident?i=data">data</a>.icmph      = *<a href="ident?i=icmp_hdr">icmp_hdr</a>(<a href="ident?i=skb">skb</a>);
<a name="L928" href="source/net/ipv4/icmp.c#L928">928</a>         icmp_param.<a href="ident?i=data">data</a>.icmph.<a href="ident?i=type">type</a> = <a href="ident?i=ICMP_TIMESTAMPREPLY">ICMP_TIMESTAMPREPLY</a>;
<a name="L929" href="source/net/ipv4/icmp.c#L929">929</a>         icmp_param.<a href="ident?i=data">data</a>.icmph.<a href="ident?i=code">code</a> = 0;
<a name="L930" href="source/net/ipv4/icmp.c#L930">930</a>         icmp_param.<a href="ident?i=skb">skb</a>             = <a href="ident?i=skb">skb</a>;
<a name="L931" href="source/net/ipv4/icmp.c#L931">931</a>         icmp_param.<a href="ident?i=offset">offset</a>          = 0;
<a name="L932" href="source/net/ipv4/icmp.c#L932">932</a>         icmp_param.<a href="ident?i=data_len">data_len</a>        = 0;
<a name="L933" href="source/net/ipv4/icmp.c#L933">933</a>         icmp_param.head_len        = sizeof(struct <a href="ident?i=icmphdr">icmphdr</a>) + 12;
<a name="L934" href="source/net/ipv4/icmp.c#L934">934</a>         <a href="ident?i=icmp_reply">icmp_reply</a>(&amp;icmp_param, <a href="ident?i=skb">skb</a>);
<a name="L935" href="source/net/ipv4/icmp.c#L935">935</a>         return <a href="ident?i=true">true</a>;
<a name="L936" href="source/net/ipv4/icmp.c#L936">936</a> 
<a name="L937" href="source/net/ipv4/icmp.c#L937">937</a> out_err:
<a name="L938" href="source/net/ipv4/icmp.c#L938">938</a>         <a href="ident?i=ICMP_INC_STATS_BH">ICMP_INC_STATS_BH</a>(<a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=skb_dst">skb_dst</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=dev">dev</a>), ICMP_MIB_INERRORS);
<a name="L939" href="source/net/ipv4/icmp.c#L939">939</a>         return <a href="ident?i=false">false</a>;
<a name="L940" href="source/net/ipv4/icmp.c#L940">940</a> }
<a name="L941" href="source/net/ipv4/icmp.c#L941">941</a> 
<a name="L942" href="source/net/ipv4/icmp.c#L942">942</a> static <a href="ident?i=bool">bool</a> <a href="ident?i=icmp_discard">icmp_discard</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L943" href="source/net/ipv4/icmp.c#L943">943</a> {
<a name="L944" href="source/net/ipv4/icmp.c#L944">944</a>         <b><i>/* pretend it was a success */</i></b>
<a name="L945" href="source/net/ipv4/icmp.c#L945">945</a>         return <a href="ident?i=true">true</a>;
<a name="L946" href="source/net/ipv4/icmp.c#L946">946</a> }
<a name="L947" href="source/net/ipv4/icmp.c#L947">947</a> 
<a name="L948" href="source/net/ipv4/icmp.c#L948">948</a> <b><i>/*</i></b>
<a name="L949" href="source/net/ipv4/icmp.c#L949">949</a> <b><i> *      Deal with incoming ICMP packets.</i></b>
<a name="L950" href="source/net/ipv4/icmp.c#L950">950</a> <b><i> */</i></b>
<a name="L951" href="source/net/ipv4/icmp.c#L951">951</a> int <a href="ident?i=icmp_rcv">icmp_rcv</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L952" href="source/net/ipv4/icmp.c#L952">952</a> {
<a name="L953" href="source/net/ipv4/icmp.c#L953">953</a>         struct <a href="ident?i=icmphdr">icmphdr</a> *icmph;
<a name="L954" href="source/net/ipv4/icmp.c#L954">954</a>         struct <a href="ident?i=rtable">rtable</a> *<a href="ident?i=rt">rt</a> = <a href="ident?i=skb_rtable">skb_rtable</a>(<a href="ident?i=skb">skb</a>);
<a name="L955" href="source/net/ipv4/icmp.c#L955">955</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>.<a href="ident?i=dev">dev</a>);
<a name="L956" href="source/net/ipv4/icmp.c#L956">956</a>         <a href="ident?i=bool">bool</a> success;
<a name="L957" href="source/net/ipv4/icmp.c#L957">957</a> 
<a name="L958" href="source/net/ipv4/icmp.c#L958">958</a>         if (!<a href="ident?i=xfrm4_policy_check">xfrm4_policy_check</a>(<a href="ident?i=NULL">NULL</a>, XFRM_POLICY_IN, <a href="ident?i=skb">skb</a>)) {
<a name="L959" href="source/net/ipv4/icmp.c#L959">959</a>                 struct <a href="ident?i=sec_path">sec_path</a> *<a href="ident?i=sp">sp</a> = <a href="ident?i=skb_sec_path">skb_sec_path</a>(<a href="ident?i=skb">skb</a>);
<a name="L960" href="source/net/ipv4/icmp.c#L960">960</a>                 int nh;
<a name="L961" href="source/net/ipv4/icmp.c#L961">961</a> 
<a name="L962" href="source/net/ipv4/icmp.c#L962">962</a>                 if (!(<a href="ident?i=sp">sp</a> &amp;&amp; <a href="ident?i=sp">sp</a>-&gt;xvec[<a href="ident?i=sp">sp</a>-&gt;<a href="ident?i=len">len</a> - 1]-&gt;props.<a href="ident?i=flags">flags</a> &amp;
<a name="L963" href="source/net/ipv4/icmp.c#L963">963</a>                                  <a href="ident?i=XFRM_STATE_ICMP">XFRM_STATE_ICMP</a>))
<a name="L964" href="source/net/ipv4/icmp.c#L964">964</a>                         goto <a href="ident?i=drop">drop</a>;
<a name="L965" href="source/net/ipv4/icmp.c#L965">965</a> 
<a name="L966" href="source/net/ipv4/icmp.c#L966">966</a>                 if (!<a href="ident?i=pskb_may_pull">pskb_may_pull</a>(<a href="ident?i=skb">skb</a>, sizeof(*icmph) + sizeof(struct <a href="ident?i=iphdr">iphdr</a>)))
<a name="L967" href="source/net/ipv4/icmp.c#L967">967</a>                         goto <a href="ident?i=drop">drop</a>;
<a name="L968" href="source/net/ipv4/icmp.c#L968">968</a> 
<a name="L969" href="source/net/ipv4/icmp.c#L969">969</a>                 nh = <a href="ident?i=skb_network_offset">skb_network_offset</a>(<a href="ident?i=skb">skb</a>);
<a name="L970" href="source/net/ipv4/icmp.c#L970">970</a>                 <a href="ident?i=skb_set_network_header">skb_set_network_header</a>(<a href="ident?i=skb">skb</a>, sizeof(*icmph));
<a name="L971" href="source/net/ipv4/icmp.c#L971">971</a> 
<a name="L972" href="source/net/ipv4/icmp.c#L972">972</a>                 if (!<a href="ident?i=xfrm4_policy_check_reverse">xfrm4_policy_check_reverse</a>(<a href="ident?i=NULL">NULL</a>, XFRM_POLICY_IN, <a href="ident?i=skb">skb</a>))
<a name="L973" href="source/net/ipv4/icmp.c#L973">973</a>                         goto <a href="ident?i=drop">drop</a>;
<a name="L974" href="source/net/ipv4/icmp.c#L974">974</a> 
<a name="L975" href="source/net/ipv4/icmp.c#L975">975</a>                 <a href="ident?i=skb_set_network_header">skb_set_network_header</a>(<a href="ident?i=skb">skb</a>, nh);
<a name="L976" href="source/net/ipv4/icmp.c#L976">976</a>         }
<a name="L977" href="source/net/ipv4/icmp.c#L977">977</a> 
<a name="L978" href="source/net/ipv4/icmp.c#L978">978</a>         <a href="ident?i=ICMP_INC_STATS_BH">ICMP_INC_STATS_BH</a>(<a href="ident?i=net">net</a>, ICMP_MIB_INMSGS);
<a name="L979" href="source/net/ipv4/icmp.c#L979">979</a> 
<a name="L980" href="source/net/ipv4/icmp.c#L980">980</a>         if (<a href="ident?i=skb_checksum_simple_validate">skb_checksum_simple_validate</a>(<a href="ident?i=skb">skb</a>))
<a name="L981" href="source/net/ipv4/icmp.c#L981">981</a>                 goto csum_error;
<a name="L982" href="source/net/ipv4/icmp.c#L982">982</a> 
<a name="L983" href="source/net/ipv4/icmp.c#L983">983</a>         if (!<a href="ident?i=pskb_pull">pskb_pull</a>(<a href="ident?i=skb">skb</a>, sizeof(*icmph)))
<a name="L984" href="source/net/ipv4/icmp.c#L984">984</a>                 goto <a href="ident?i=error">error</a>;
<a name="L985" href="source/net/ipv4/icmp.c#L985">985</a> 
<a name="L986" href="source/net/ipv4/icmp.c#L986">986</a>         icmph = <a href="ident?i=icmp_hdr">icmp_hdr</a>(<a href="ident?i=skb">skb</a>);
<a name="L987" href="source/net/ipv4/icmp.c#L987">987</a> 
<a name="L988" href="source/net/ipv4/icmp.c#L988">988</a>         <a href="ident?i=ICMPMSGIN_INC_STATS_BH">ICMPMSGIN_INC_STATS_BH</a>(<a href="ident?i=net">net</a>, icmph-&gt;<a href="ident?i=type">type</a>);
<a name="L989" href="source/net/ipv4/icmp.c#L989">989</a>         <b><i>/*</i></b>
<a name="L990" href="source/net/ipv4/icmp.c#L990">990</a> <b><i>         *      18 is the highest 'known' ICMP type. Anything else is a mystery</i></b>
<a name="L991" href="source/net/ipv4/icmp.c#L991">991</a> <b><i>         *</i></b>
<a name="L992" href="source/net/ipv4/icmp.c#L992">992</a> <b><i>         *      RFC 1122: 3.2.2  Unknown ICMP messages types MUST be silently</i></b>
<a name="L993" href="source/net/ipv4/icmp.c#L993">993</a> <b><i>         *                discarded.</i></b>
<a name="L994" href="source/net/ipv4/icmp.c#L994">994</a> <b><i>         */</i></b>
<a name="L995" href="source/net/ipv4/icmp.c#L995">995</a>         if (icmph-&gt;<a href="ident?i=type">type</a> &gt; <a href="ident?i=NR_ICMP_TYPES">NR_ICMP_TYPES</a>)
<a name="L996" href="source/net/ipv4/icmp.c#L996">996</a>                 goto <a href="ident?i=error">error</a>;
<a name="L997" href="source/net/ipv4/icmp.c#L997">997</a> 
<a name="L998" href="source/net/ipv4/icmp.c#L998">998</a> 
<a name="L999" href="source/net/ipv4/icmp.c#L999">999</a>         <b><i>/*</i></b>
<a name="L1000" href="source/net/ipv4/icmp.c#L1000">1000</a> <b><i>         *      Parse the ICMP message</i></b>
<a name="L1001" href="source/net/ipv4/icmp.c#L1001">1001</a> <b><i>         */</i></b>
<a name="L1002" href="source/net/ipv4/icmp.c#L1002">1002</a> 
<a name="L1003" href="source/net/ipv4/icmp.c#L1003">1003</a>         if (<a href="ident?i=rt">rt</a>-&gt;rt_flags &amp; (<a href="ident?i=RTCF_BROADCAST">RTCF_BROADCAST</a> | <a href="ident?i=RTCF_MULTICAST">RTCF_MULTICAST</a>)) {
<a name="L1004" href="source/net/ipv4/icmp.c#L1004">1004</a>                 <b><i>/*</i></b>
<a name="L1005" href="source/net/ipv4/icmp.c#L1005">1005</a> <b><i>                 *      RFC 1122: 3.2.2.6 An ICMP_ECHO to broadcast MAY be</i></b>
<a name="L1006" href="source/net/ipv4/icmp.c#L1006">1006</a> <b><i>                 *        silently ignored (we let user decide with a sysctl).</i></b>
<a name="L1007" href="source/net/ipv4/icmp.c#L1007">1007</a> <b><i>                 *      RFC 1122: 3.2.2.8 An ICMP_TIMESTAMP MAY be silently</i></b>
<a name="L1008" href="source/net/ipv4/icmp.c#L1008">1008</a> <b><i>                 *        discarded if to broadcast/multicast.</i></b>
<a name="L1009" href="source/net/ipv4/icmp.c#L1009">1009</a> <b><i>                 */</i></b>
<a name="L1010" href="source/net/ipv4/icmp.c#L1010">1010</a>                 if ((icmph-&gt;<a href="ident?i=type">type</a> == <a href="ident?i=ICMP_ECHO">ICMP_ECHO</a> ||
<a name="L1011" href="source/net/ipv4/icmp.c#L1011">1011</a>                      icmph-&gt;<a href="ident?i=type">type</a> == <a href="ident?i=ICMP_TIMESTAMP">ICMP_TIMESTAMP</a>) &amp;&amp;
<a name="L1012" href="source/net/ipv4/icmp.c#L1012">1012</a>                     <a href="ident?i=net">net</a>-&gt;ipv4.sysctl_icmp_echo_ignore_broadcasts) {
<a name="L1013" href="source/net/ipv4/icmp.c#L1013">1013</a>                         goto <a href="ident?i=error">error</a>;
<a name="L1014" href="source/net/ipv4/icmp.c#L1014">1014</a>                 }
<a name="L1015" href="source/net/ipv4/icmp.c#L1015">1015</a>                 if (icmph-&gt;<a href="ident?i=type">type</a> != <a href="ident?i=ICMP_ECHO">ICMP_ECHO</a> &amp;&amp;
<a name="L1016" href="source/net/ipv4/icmp.c#L1016">1016</a>                     icmph-&gt;<a href="ident?i=type">type</a> != <a href="ident?i=ICMP_TIMESTAMP">ICMP_TIMESTAMP</a> &amp;&amp;
<a name="L1017" href="source/net/ipv4/icmp.c#L1017">1017</a>                     icmph-&gt;<a href="ident?i=type">type</a> != <a href="ident?i=ICMP_ADDRESS">ICMP_ADDRESS</a> &amp;&amp;
<a name="L1018" href="source/net/ipv4/icmp.c#L1018">1018</a>                     icmph-&gt;<a href="ident?i=type">type</a> != <a href="ident?i=ICMP_ADDRESSREPLY">ICMP_ADDRESSREPLY</a>) {
<a name="L1019" href="source/net/ipv4/icmp.c#L1019">1019</a>                         goto <a href="ident?i=error">error</a>;
<a name="L1020" href="source/net/ipv4/icmp.c#L1020">1020</a>                 }
<a name="L1021" href="source/net/ipv4/icmp.c#L1021">1021</a>         }
<a name="L1022" href="source/net/ipv4/icmp.c#L1022">1022</a> 
<a name="L1023" href="source/net/ipv4/icmp.c#L1023">1023</a>         success = <a href="ident?i=icmp_pointers">icmp_pointers</a>[icmph-&gt;<a href="ident?i=type">type</a>].<a href="ident?i=handler">handler</a>(<a href="ident?i=skb">skb</a>);
<a name="L1024" href="source/net/ipv4/icmp.c#L1024">1024</a> 
<a name="L1025" href="source/net/ipv4/icmp.c#L1025">1025</a>         if (success)  {
<a name="L1026" href="source/net/ipv4/icmp.c#L1026">1026</a>                 <a href="ident?i=consume_skb">consume_skb</a>(<a href="ident?i=skb">skb</a>);
<a name="L1027" href="source/net/ipv4/icmp.c#L1027">1027</a>                 return 0;
<a name="L1028" href="source/net/ipv4/icmp.c#L1028">1028</a>         }
<a name="L1029" href="source/net/ipv4/icmp.c#L1029">1029</a> 
<a name="L1030" href="source/net/ipv4/icmp.c#L1030">1030</a> <a href="ident?i=drop">drop</a>:
<a name="L1031" href="source/net/ipv4/icmp.c#L1031">1031</a>         <a href="ident?i=kfree_skb">kfree_skb</a>(<a href="ident?i=skb">skb</a>);
<a name="L1032" href="source/net/ipv4/icmp.c#L1032">1032</a>         return 0;
<a name="L1033" href="source/net/ipv4/icmp.c#L1033">1033</a> csum_error:
<a name="L1034" href="source/net/ipv4/icmp.c#L1034">1034</a>         <a href="ident?i=ICMP_INC_STATS_BH">ICMP_INC_STATS_BH</a>(<a href="ident?i=net">net</a>, ICMP_MIB_CSUMERRORS);
<a name="L1035" href="source/net/ipv4/icmp.c#L1035">1035</a> <a href="ident?i=error">error</a>:
<a name="L1036" href="source/net/ipv4/icmp.c#L1036">1036</a>         <a href="ident?i=ICMP_INC_STATS_BH">ICMP_INC_STATS_BH</a>(<a href="ident?i=net">net</a>, ICMP_MIB_INERRORS);
<a name="L1037" href="source/net/ipv4/icmp.c#L1037">1037</a>         goto <a href="ident?i=drop">drop</a>;
<a name="L1038" href="source/net/ipv4/icmp.c#L1038">1038</a> }
<a name="L1039" href="source/net/ipv4/icmp.c#L1039">1039</a> 
<a name="L1040" href="source/net/ipv4/icmp.c#L1040">1040</a> void <a href="ident?i=icmp_err">icmp_err</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, <a href="ident?i=u32">u32</a> <a href="ident?i=info">info</a>)
<a name="L1041" href="source/net/ipv4/icmp.c#L1041">1041</a> {
<a name="L1042" href="source/net/ipv4/icmp.c#L1042">1042</a>         struct <a href="ident?i=iphdr">iphdr</a> *iph = (struct <a href="ident?i=iphdr">iphdr</a> *)<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=data">data</a>;
<a name="L1043" href="source/net/ipv4/icmp.c#L1043">1043</a>         int <a href="ident?i=offset">offset</a> = iph-&gt;ihl&lt;&lt;2;
<a name="L1044" href="source/net/ipv4/icmp.c#L1044">1044</a>         struct <a href="ident?i=icmphdr">icmphdr</a> *icmph = (struct <a href="ident?i=icmphdr">icmphdr</a> *)(<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=data">data</a> + <a href="ident?i=offset">offset</a>);
<a name="L1045" href="source/net/ipv4/icmp.c#L1045">1045</a>         int <a href="ident?i=type">type</a> = <a href="ident?i=icmp_hdr">icmp_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=type">type</a>;
<a name="L1046" href="source/net/ipv4/icmp.c#L1046">1046</a>         int <a href="ident?i=code">code</a> = <a href="ident?i=icmp_hdr">icmp_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=code">code</a>;
<a name="L1047" href="source/net/ipv4/icmp.c#L1047">1047</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=dev">dev</a>);
<a name="L1048" href="source/net/ipv4/icmp.c#L1048">1048</a> 
<a name="L1049" href="source/net/ipv4/icmp.c#L1049">1049</a>         <b><i>/*</i></b>
<a name="L1050" href="source/net/ipv4/icmp.c#L1050">1050</a> <b><i>         * Use ping_err to handle all icmp errors except those</i></b>
<a name="L1051" href="source/net/ipv4/icmp.c#L1051">1051</a> <b><i>         * triggered by ICMP_ECHOREPLY which sent from kernel.</i></b>
<a name="L1052" href="source/net/ipv4/icmp.c#L1052">1052</a> <b><i>         */</i></b>
<a name="L1053" href="source/net/ipv4/icmp.c#L1053">1053</a>         if (icmph-&gt;<a href="ident?i=type">type</a> != <a href="ident?i=ICMP_ECHOREPLY">ICMP_ECHOREPLY</a>) {
<a name="L1054" href="source/net/ipv4/icmp.c#L1054">1054</a>                 <a href="ident?i=ping_err">ping_err</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=offset">offset</a>, <a href="ident?i=info">info</a>);
<a name="L1055" href="source/net/ipv4/icmp.c#L1055">1055</a>                 return;
<a name="L1056" href="source/net/ipv4/icmp.c#L1056">1056</a>         }
<a name="L1057" href="source/net/ipv4/icmp.c#L1057">1057</a> 
<a name="L1058" href="source/net/ipv4/icmp.c#L1058">1058</a>         if (<a href="ident?i=type">type</a> == <a href="ident?i=ICMP_DEST_UNREACH">ICMP_DEST_UNREACH</a> &amp;&amp; <a href="ident?i=code">code</a> == <a href="ident?i=ICMP_FRAG_NEEDED">ICMP_FRAG_NEEDED</a>)
<a name="L1059" href="source/net/ipv4/icmp.c#L1059">1059</a>                 <a href="ident?i=ipv4_update_pmtu">ipv4_update_pmtu</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=net">net</a>, <a href="ident?i=info">info</a>, 0, 0, <a href="ident?i=IPPROTO_ICMP">IPPROTO_ICMP</a>, 0);
<a name="L1060" href="source/net/ipv4/icmp.c#L1060">1060</a>         else if (<a href="ident?i=type">type</a> == <a href="ident?i=ICMP_REDIRECT">ICMP_REDIRECT</a>)
<a name="L1061" href="source/net/ipv4/icmp.c#L1061">1061</a>                 <a href="ident?i=ipv4_redirect">ipv4_redirect</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=net">net</a>, 0, 0, <a href="ident?i=IPPROTO_ICMP">IPPROTO_ICMP</a>, 0);
<a name="L1062" href="source/net/ipv4/icmp.c#L1062">1062</a> }
<a name="L1063" href="source/net/ipv4/icmp.c#L1063">1063</a> 
<a name="L1064" href="source/net/ipv4/icmp.c#L1064">1064</a> <b><i>/*</i></b>
<a name="L1065" href="source/net/ipv4/icmp.c#L1065">1065</a> <b><i> *      This table is the definition of how we handle ICMP.</i></b>
<a name="L1066" href="source/net/ipv4/icmp.c#L1066">1066</a> <b><i> */</i></b>
<a name="L1067" href="source/net/ipv4/icmp.c#L1067">1067</a> static const struct <a href="ident?i=icmp_control">icmp_control</a> <a href="ident?i=icmp_pointers">icmp_pointers</a>[<a href="ident?i=NR_ICMP_TYPES">NR_ICMP_TYPES</a> + 1] = {
<a name="L1068" href="source/net/ipv4/icmp.c#L1068">1068</a>         [<a href="ident?i=ICMP_ECHOREPLY">ICMP_ECHOREPLY</a>] = {
<a name="L1069" href="source/net/ipv4/icmp.c#L1069">1069</a>                 .<a href="ident?i=handler">handler</a> = <a href="ident?i=ping_rcv">ping_rcv</a>,
<a name="L1070" href="source/net/ipv4/icmp.c#L1070">1070</a>         },
<a name="L1071" href="source/net/ipv4/icmp.c#L1071">1071</a>         [1] = {
<a name="L1072" href="source/net/ipv4/icmp.c#L1072">1072</a>                 .<a href="ident?i=handler">handler</a> = <a href="ident?i=icmp_discard">icmp_discard</a>,
<a name="L1073" href="source/net/ipv4/icmp.c#L1073">1073</a>                 .<a href="ident?i=error">error</a> = 1,
<a name="L1074" href="source/net/ipv4/icmp.c#L1074">1074</a>         },
<a name="L1075" href="source/net/ipv4/icmp.c#L1075">1075</a>         [2] = {
<a name="L1076" href="source/net/ipv4/icmp.c#L1076">1076</a>                 .<a href="ident?i=handler">handler</a> = <a href="ident?i=icmp_discard">icmp_discard</a>,
<a name="L1077" href="source/net/ipv4/icmp.c#L1077">1077</a>                 .<a href="ident?i=error">error</a> = 1,
<a name="L1078" href="source/net/ipv4/icmp.c#L1078">1078</a>         },
<a name="L1079" href="source/net/ipv4/icmp.c#L1079">1079</a>         [<a href="ident?i=ICMP_DEST_UNREACH">ICMP_DEST_UNREACH</a>] = {
<a name="L1080" href="source/net/ipv4/icmp.c#L1080">1080</a>                 .<a href="ident?i=handler">handler</a> = <a href="ident?i=icmp_unreach">icmp_unreach</a>,
<a name="L1081" href="source/net/ipv4/icmp.c#L1081">1081</a>                 .<a href="ident?i=error">error</a> = 1,
<a name="L1082" href="source/net/ipv4/icmp.c#L1082">1082</a>         },
<a name="L1083" href="source/net/ipv4/icmp.c#L1083">1083</a>         [<a href="ident?i=ICMP_SOURCE_QUENCH">ICMP_SOURCE_QUENCH</a>] = {
<a name="L1084" href="source/net/ipv4/icmp.c#L1084">1084</a>                 .<a href="ident?i=handler">handler</a> = <a href="ident?i=icmp_unreach">icmp_unreach</a>,
<a name="L1085" href="source/net/ipv4/icmp.c#L1085">1085</a>                 .<a href="ident?i=error">error</a> = 1,
<a name="L1086" href="source/net/ipv4/icmp.c#L1086">1086</a>         },
<a name="L1087" href="source/net/ipv4/icmp.c#L1087">1087</a>         [<a href="ident?i=ICMP_REDIRECT">ICMP_REDIRECT</a>] = {
<a name="L1088" href="source/net/ipv4/icmp.c#L1088">1088</a>                 .<a href="ident?i=handler">handler</a> = <a href="ident?i=icmp_redirect">icmp_redirect</a>,
<a name="L1089" href="source/net/ipv4/icmp.c#L1089">1089</a>                 .<a href="ident?i=error">error</a> = 1,
<a name="L1090" href="source/net/ipv4/icmp.c#L1090">1090</a>         },
<a name="L1091" href="source/net/ipv4/icmp.c#L1091">1091</a>         [6] = {
<a name="L1092" href="source/net/ipv4/icmp.c#L1092">1092</a>                 .<a href="ident?i=handler">handler</a> = <a href="ident?i=icmp_discard">icmp_discard</a>,
<a name="L1093" href="source/net/ipv4/icmp.c#L1093">1093</a>                 .<a href="ident?i=error">error</a> = 1,
<a name="L1094" href="source/net/ipv4/icmp.c#L1094">1094</a>         },
<a name="L1095" href="source/net/ipv4/icmp.c#L1095">1095</a>         [7] = {
<a name="L1096" href="source/net/ipv4/icmp.c#L1096">1096</a>                 .<a href="ident?i=handler">handler</a> = <a href="ident?i=icmp_discard">icmp_discard</a>,
<a name="L1097" href="source/net/ipv4/icmp.c#L1097">1097</a>                 .<a href="ident?i=error">error</a> = 1,
<a name="L1098" href="source/net/ipv4/icmp.c#L1098">1098</a>         },
<a name="L1099" href="source/net/ipv4/icmp.c#L1099">1099</a>         [<a href="ident?i=ICMP_ECHO">ICMP_ECHO</a>] = {
<a name="L1100" href="source/net/ipv4/icmp.c#L1100">1100</a>                 .<a href="ident?i=handler">handler</a> = <a href="ident?i=icmp_echo">icmp_echo</a>,
<a name="L1101" href="source/net/ipv4/icmp.c#L1101">1101</a>         },
<a name="L1102" href="source/net/ipv4/icmp.c#L1102">1102</a>         [9] = {
<a name="L1103" href="source/net/ipv4/icmp.c#L1103">1103</a>                 .<a href="ident?i=handler">handler</a> = <a href="ident?i=icmp_discard">icmp_discard</a>,
<a name="L1104" href="source/net/ipv4/icmp.c#L1104">1104</a>                 .<a href="ident?i=error">error</a> = 1,
<a name="L1105" href="source/net/ipv4/icmp.c#L1105">1105</a>         },
<a name="L1106" href="source/net/ipv4/icmp.c#L1106">1106</a>         [10] = {
<a name="L1107" href="source/net/ipv4/icmp.c#L1107">1107</a>                 .<a href="ident?i=handler">handler</a> = <a href="ident?i=icmp_discard">icmp_discard</a>,
<a name="L1108" href="source/net/ipv4/icmp.c#L1108">1108</a>                 .<a href="ident?i=error">error</a> = 1,
<a name="L1109" href="source/net/ipv4/icmp.c#L1109">1109</a>         },
<a name="L1110" href="source/net/ipv4/icmp.c#L1110">1110</a>         [<a href="ident?i=ICMP_TIME_EXCEEDED">ICMP_TIME_EXCEEDED</a>] = {
<a name="L1111" href="source/net/ipv4/icmp.c#L1111">1111</a>                 .<a href="ident?i=handler">handler</a> = <a href="ident?i=icmp_unreach">icmp_unreach</a>,
<a name="L1112" href="source/net/ipv4/icmp.c#L1112">1112</a>                 .<a href="ident?i=error">error</a> = 1,
<a name="L1113" href="source/net/ipv4/icmp.c#L1113">1113</a>         },
<a name="L1114" href="source/net/ipv4/icmp.c#L1114">1114</a>         [<a href="ident?i=ICMP_PARAMETERPROB">ICMP_PARAMETERPROB</a>] = {
<a name="L1115" href="source/net/ipv4/icmp.c#L1115">1115</a>                 .<a href="ident?i=handler">handler</a> = <a href="ident?i=icmp_unreach">icmp_unreach</a>,
<a name="L1116" href="source/net/ipv4/icmp.c#L1116">1116</a>                 .<a href="ident?i=error">error</a> = 1,
<a name="L1117" href="source/net/ipv4/icmp.c#L1117">1117</a>         },
<a name="L1118" href="source/net/ipv4/icmp.c#L1118">1118</a>         [<a href="ident?i=ICMP_TIMESTAMP">ICMP_TIMESTAMP</a>] = {
<a name="L1119" href="source/net/ipv4/icmp.c#L1119">1119</a>                 .<a href="ident?i=handler">handler</a> = <a href="ident?i=icmp_timestamp">icmp_timestamp</a>,
<a name="L1120" href="source/net/ipv4/icmp.c#L1120">1120</a>         },
<a name="L1121" href="source/net/ipv4/icmp.c#L1121">1121</a>         [<a href="ident?i=ICMP_TIMESTAMPREPLY">ICMP_TIMESTAMPREPLY</a>] = {
<a name="L1122" href="source/net/ipv4/icmp.c#L1122">1122</a>                 .<a href="ident?i=handler">handler</a> = <a href="ident?i=icmp_discard">icmp_discard</a>,
<a name="L1123" href="source/net/ipv4/icmp.c#L1123">1123</a>         },
<a name="L1124" href="source/net/ipv4/icmp.c#L1124">1124</a>         [<a href="ident?i=ICMP_INFO_REQUEST">ICMP_INFO_REQUEST</a>] = {
<a name="L1125" href="source/net/ipv4/icmp.c#L1125">1125</a>                 .<a href="ident?i=handler">handler</a> = <a href="ident?i=icmp_discard">icmp_discard</a>,
<a name="L1126" href="source/net/ipv4/icmp.c#L1126">1126</a>         },
<a name="L1127" href="source/net/ipv4/icmp.c#L1127">1127</a>         [<a href="ident?i=ICMP_INFO_REPLY">ICMP_INFO_REPLY</a>] = {
<a name="L1128" href="source/net/ipv4/icmp.c#L1128">1128</a>                 .<a href="ident?i=handler">handler</a> = <a href="ident?i=icmp_discard">icmp_discard</a>,
<a name="L1129" href="source/net/ipv4/icmp.c#L1129">1129</a>         },
<a name="L1130" href="source/net/ipv4/icmp.c#L1130">1130</a>         [<a href="ident?i=ICMP_ADDRESS">ICMP_ADDRESS</a>] = {
<a name="L1131" href="source/net/ipv4/icmp.c#L1131">1131</a>                 .<a href="ident?i=handler">handler</a> = <a href="ident?i=icmp_discard">icmp_discard</a>,
<a name="L1132" href="source/net/ipv4/icmp.c#L1132">1132</a>         },
<a name="L1133" href="source/net/ipv4/icmp.c#L1133">1133</a>         [<a href="ident?i=ICMP_ADDRESSREPLY">ICMP_ADDRESSREPLY</a>] = {
<a name="L1134" href="source/net/ipv4/icmp.c#L1134">1134</a>                 .<a href="ident?i=handler">handler</a> = <a href="ident?i=icmp_discard">icmp_discard</a>,
<a name="L1135" href="source/net/ipv4/icmp.c#L1135">1135</a>         },
<a name="L1136" href="source/net/ipv4/icmp.c#L1136">1136</a> };
<a name="L1137" href="source/net/ipv4/icmp.c#L1137">1137</a> 
<a name="L1138" href="source/net/ipv4/icmp.c#L1138">1138</a> static void <a href="ident?i=__net_exit">__net_exit</a> <a href="ident?i=icmp_sk_exit">icmp_sk_exit</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>)
<a name="L1139" href="source/net/ipv4/icmp.c#L1139">1139</a> {
<a name="L1140" href="source/net/ipv4/icmp.c#L1140">1140</a>         int <a href="ident?i=i">i</a>;
<a name="L1141" href="source/net/ipv4/icmp.c#L1141">1141</a> 
<a name="L1142" href="source/net/ipv4/icmp.c#L1142">1142</a>         <a href="ident?i=for_each_possible_cpu">for_each_possible_cpu</a>(<a href="ident?i=i">i</a>)
<a name="L1143" href="source/net/ipv4/icmp.c#L1143">1143</a>                 <a href="ident?i=inet_ctl_sock_destroy">inet_ctl_sock_destroy</a>(*<a href="ident?i=per_cpu_ptr">per_cpu_ptr</a>(<a href="ident?i=net">net</a>-&gt;ipv4.<a href="ident?i=icmp_sk">icmp_sk</a>, <a href="ident?i=i">i</a>));
<a name="L1144" href="source/net/ipv4/icmp.c#L1144">1144</a>         <a href="ident?i=free_percpu">free_percpu</a>(<a href="ident?i=net">net</a>-&gt;ipv4.<a href="ident?i=icmp_sk">icmp_sk</a>);
<a name="L1145" href="source/net/ipv4/icmp.c#L1145">1145</a>         <a href="ident?i=net">net</a>-&gt;ipv4.<a href="ident?i=icmp_sk">icmp_sk</a> = <a href="ident?i=NULL">NULL</a>;
<a name="L1146" href="source/net/ipv4/icmp.c#L1146">1146</a> }
<a name="L1147" href="source/net/ipv4/icmp.c#L1147">1147</a> 
<a name="L1148" href="source/net/ipv4/icmp.c#L1148">1148</a> static int <a href="ident?i=__net_init">__net_init</a> <a href="ident?i=icmp_sk_init">icmp_sk_init</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>)
<a name="L1149" href="source/net/ipv4/icmp.c#L1149">1149</a> {
<a name="L1150" href="source/net/ipv4/icmp.c#L1150">1150</a>         int <a href="ident?i=i">i</a>, <a href="ident?i=err">err</a>;
<a name="L1151" href="source/net/ipv4/icmp.c#L1151">1151</a> 
<a name="L1152" href="source/net/ipv4/icmp.c#L1152">1152</a>         <a href="ident?i=net">net</a>-&gt;ipv4.<a href="ident?i=icmp_sk">icmp_sk</a> = <a href="ident?i=alloc_percpu">alloc_percpu</a>(struct <a href="ident?i=sock">sock</a> *);
<a name="L1153" href="source/net/ipv4/icmp.c#L1153">1153</a>         if (!<a href="ident?i=net">net</a>-&gt;ipv4.<a href="ident?i=icmp_sk">icmp_sk</a>)
<a name="L1154" href="source/net/ipv4/icmp.c#L1154">1154</a>                 return -<a href="ident?i=ENOMEM">ENOMEM</a>;
<a name="L1155" href="source/net/ipv4/icmp.c#L1155">1155</a> 
<a name="L1156" href="source/net/ipv4/icmp.c#L1156">1156</a>         <a href="ident?i=for_each_possible_cpu">for_each_possible_cpu</a>(<a href="ident?i=i">i</a>) {
<a name="L1157" href="source/net/ipv4/icmp.c#L1157">1157</a>                 struct <a href="ident?i=sock">sock</a> *sk;
<a name="L1158" href="source/net/ipv4/icmp.c#L1158">1158</a> 
<a name="L1159" href="source/net/ipv4/icmp.c#L1159">1159</a>                 <a href="ident?i=err">err</a> = <a href="ident?i=inet_ctl_sock_create">inet_ctl_sock_create</a>(&amp;sk, <a href="ident?i=PF_INET">PF_INET</a>,
<a name="L1160" href="source/net/ipv4/icmp.c#L1160">1160</a>                                            SOCK_RAW, <a href="ident?i=IPPROTO_ICMP">IPPROTO_ICMP</a>, <a href="ident?i=net">net</a>);
<a name="L1161" href="source/net/ipv4/icmp.c#L1161">1161</a>                 if (<a href="ident?i=err">err</a> &lt; 0)
<a name="L1162" href="source/net/ipv4/icmp.c#L1162">1162</a>                         goto <a href="ident?i=fail">fail</a>;
<a name="L1163" href="source/net/ipv4/icmp.c#L1163">1163</a> 
<a name="L1164" href="source/net/ipv4/icmp.c#L1164">1164</a>                 *<a href="ident?i=per_cpu_ptr">per_cpu_ptr</a>(<a href="ident?i=net">net</a>-&gt;ipv4.<a href="ident?i=icmp_sk">icmp_sk</a>, <a href="ident?i=i">i</a>) = sk;
<a name="L1165" href="source/net/ipv4/icmp.c#L1165">1165</a> 
<a name="L1166" href="source/net/ipv4/icmp.c#L1166">1166</a>                 <b><i>/* Enough space for 2 64K ICMP packets, including</i></b>
<a name="L1167" href="source/net/ipv4/icmp.c#L1167">1167</a> <b><i>                 * sk_buff/skb_shared_info struct overhead.</i></b>
<a name="L1168" href="source/net/ipv4/icmp.c#L1168">1168</a> <b><i>                 */</i></b>
<a name="L1169" href="source/net/ipv4/icmp.c#L1169">1169</a>                 sk-&gt;sk_sndbuf = 2 * <a href="ident?i=SKB_TRUESIZE">SKB_TRUESIZE</a>(64 * 1024);
<a name="L1170" href="source/net/ipv4/icmp.c#L1170">1170</a> 
<a name="L1171" href="source/net/ipv4/icmp.c#L1171">1171</a>                 <b><i>/*</i></b>
<a name="L1172" href="source/net/ipv4/icmp.c#L1172">1172</a> <b><i>                 * Speedup sock_wfree()</i></b>
<a name="L1173" href="source/net/ipv4/icmp.c#L1173">1173</a> <b><i>                 */</i></b>
<a name="L1174" href="source/net/ipv4/icmp.c#L1174">1174</a>                 <a href="ident?i=sock_set_flag">sock_set_flag</a>(sk, SOCK_USE_WRITE_QUEUE);
<a name="L1175" href="source/net/ipv4/icmp.c#L1175">1175</a>                 <a href="ident?i=inet_sk">inet_sk</a>(sk)-&gt;pmtudisc = <a href="ident?i=IP_PMTUDISC_DONT">IP_PMTUDISC_DONT</a>;
<a name="L1176" href="source/net/ipv4/icmp.c#L1176">1176</a>         }
<a name="L1177" href="source/net/ipv4/icmp.c#L1177">1177</a> 
<a name="L1178" href="source/net/ipv4/icmp.c#L1178">1178</a>         <b><i>/* Control parameters for ECHO replies. */</i></b>
<a name="L1179" href="source/net/ipv4/icmp.c#L1179">1179</a>         <a href="ident?i=net">net</a>-&gt;ipv4.sysctl_icmp_echo_ignore_all = 0;
<a name="L1180" href="source/net/ipv4/icmp.c#L1180">1180</a>         <a href="ident?i=net">net</a>-&gt;ipv4.sysctl_icmp_echo_ignore_broadcasts = 1;
<a name="L1181" href="source/net/ipv4/icmp.c#L1181">1181</a> 
<a name="L1182" href="source/net/ipv4/icmp.c#L1182">1182</a>         <b><i>/* Control parameter - ignore bogus broadcast responses? */</i></b>
<a name="L1183" href="source/net/ipv4/icmp.c#L1183">1183</a>         <a href="ident?i=net">net</a>-&gt;ipv4.sysctl_icmp_ignore_bogus_error_responses = 1;
<a name="L1184" href="source/net/ipv4/icmp.c#L1184">1184</a> 
<a name="L1185" href="source/net/ipv4/icmp.c#L1185">1185</a>         <b><i>/*</i></b>
<a name="L1186" href="source/net/ipv4/icmp.c#L1186">1186</a> <b><i>         *      Configurable global rate limit.</i></b>
<a name="L1187" href="source/net/ipv4/icmp.c#L1187">1187</a> <b><i>         *</i></b>
<a name="L1188" href="source/net/ipv4/icmp.c#L1188">1188</a> <b><i>         *      ratelimit defines tokens/packet consumed for dst-&gt;rate_token</i></b>
<a name="L1189" href="source/net/ipv4/icmp.c#L1189">1189</a> <b><i>         *      bucket ratemask defines which icmp types are ratelimited by</i></b>
<a name="L1190" href="source/net/ipv4/icmp.c#L1190">1190</a> <b><i>         *      setting it's bit position.</i></b>
<a name="L1191" href="source/net/ipv4/icmp.c#L1191">1191</a> <b><i>         *</i></b>
<a name="L1192" href="source/net/ipv4/icmp.c#L1192">1192</a> <b><i>         *      default:</i></b>
<a name="L1193" href="source/net/ipv4/icmp.c#L1193">1193</a> <b><i>         *      dest unreachable (3), source quench (4),</i></b>
<a name="L1194" href="source/net/ipv4/icmp.c#L1194">1194</a> <b><i>         *      time exceeded (11), parameter problem (12)</i></b>
<a name="L1195" href="source/net/ipv4/icmp.c#L1195">1195</a> <b><i>         */</i></b>
<a name="L1196" href="source/net/ipv4/icmp.c#L1196">1196</a> 
<a name="L1197" href="source/net/ipv4/icmp.c#L1197">1197</a>         <a href="ident?i=net">net</a>-&gt;ipv4.sysctl_icmp_ratelimit = 1 * <a href="ident?i=HZ">HZ</a>;
<a name="L1198" href="source/net/ipv4/icmp.c#L1198">1198</a>         <a href="ident?i=net">net</a>-&gt;ipv4.sysctl_icmp_ratemask = 0x1818;
<a name="L1199" href="source/net/ipv4/icmp.c#L1199">1199</a>         <a href="ident?i=net">net</a>-&gt;ipv4.sysctl_icmp_errors_use_inbound_ifaddr = 0;
<a name="L1200" href="source/net/ipv4/icmp.c#L1200">1200</a> 
<a name="L1201" href="source/net/ipv4/icmp.c#L1201">1201</a>         return 0;
<a name="L1202" href="source/net/ipv4/icmp.c#L1202">1202</a> 
<a name="L1203" href="source/net/ipv4/icmp.c#L1203">1203</a> <a href="ident?i=fail">fail</a>:
<a name="L1204" href="source/net/ipv4/icmp.c#L1204">1204</a>         <a href="ident?i=for_each_possible_cpu">for_each_possible_cpu</a>(<a href="ident?i=i">i</a>)
<a name="L1205" href="source/net/ipv4/icmp.c#L1205">1205</a>                 <a href="ident?i=inet_ctl_sock_destroy">inet_ctl_sock_destroy</a>(*<a href="ident?i=per_cpu_ptr">per_cpu_ptr</a>(<a href="ident?i=net">net</a>-&gt;ipv4.<a href="ident?i=icmp_sk">icmp_sk</a>, <a href="ident?i=i">i</a>));
<a name="L1206" href="source/net/ipv4/icmp.c#L1206">1206</a>         <a href="ident?i=free_percpu">free_percpu</a>(<a href="ident?i=net">net</a>-&gt;ipv4.<a href="ident?i=icmp_sk">icmp_sk</a>);
<a name="L1207" href="source/net/ipv4/icmp.c#L1207">1207</a>         return <a href="ident?i=err">err</a>;
<a name="L1208" href="source/net/ipv4/icmp.c#L1208">1208</a> }
<a name="L1209" href="source/net/ipv4/icmp.c#L1209">1209</a> 
<a name="L1210" href="source/net/ipv4/icmp.c#L1210">1210</a> static struct <a href="ident?i=pernet_operations">pernet_operations</a> <a href="ident?i=__net_initdata">__net_initdata</a> <a href="ident?i=icmp_sk_ops">icmp_sk_ops</a> = {
<a name="L1211" href="source/net/ipv4/icmp.c#L1211">1211</a>        .<a href="ident?i=init">init</a> = <a href="ident?i=icmp_sk_init">icmp_sk_init</a>,
<a name="L1212" href="source/net/ipv4/icmp.c#L1212">1212</a>        .<a href="ident?i=exit">exit</a> = <a href="ident?i=icmp_sk_exit">icmp_sk_exit</a>,
<a name="L1213" href="source/net/ipv4/icmp.c#L1213">1213</a> };
<a name="L1214" href="source/net/ipv4/icmp.c#L1214">1214</a> 
<a name="L1215" href="source/net/ipv4/icmp.c#L1215">1215</a> int <a href="ident?i=__init">__init</a> <a href="ident?i=icmp_init">icmp_init</a>(void)
<a name="L1216" href="source/net/ipv4/icmp.c#L1216">1216</a> {
<a name="L1217" href="source/net/ipv4/icmp.c#L1217">1217</a>         return <a href="ident?i=register_pernet_subsys">register_pernet_subsys</a>(&amp;<a href="ident?i=icmp_sk_ops">icmp_sk_ops</a>);
<a name="L1218" href="source/net/ipv4/icmp.c#L1218">1218</a> }
<a name="L1219" href="source/net/ipv4/icmp.c#L1219">1219</a> </pre></div><p>
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
