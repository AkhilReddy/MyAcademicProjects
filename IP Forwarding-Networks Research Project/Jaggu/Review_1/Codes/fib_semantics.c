<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title>Linux/net/ipv4/fib_semantics.c - Linux Cross Reference - Free Electrons</title>
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
		 &nbsp;&bull;&nbsp;<b><i>source navigation</i></b> &nbsp;&bull;&nbsp;<a href="diff/net/ipv4/fib_semantics.c">diff markup</a> &nbsp;&bull;&nbsp;<a href="ident">identifier search</a> &nbsp;&bull;&nbsp;<a href="search">freetext search</a> &nbsp;&bull;&nbsp;
		</p>
	</div>
</div>

<div id="topbar">
  
  <p>Version: &nbsp;<a href="source/net/ipv4/fib_semantics.c?v=2.0.40">2.0.40</a>&nbsp;<a href="source/net/ipv4/fib_semantics.c?v=2.2.26">2.2.26</a>&nbsp;<a href="source/net/ipv4/fib_semantics.c?v=2.4.37">2.4.37</a>&nbsp;<a href="source/net/ipv4/fib_semantics.c?v=3.5">3.5</a>&nbsp;<a href="source/net/ipv4/fib_semantics.c?v=3.6">3.6</a>&nbsp;<a href="source/net/ipv4/fib_semantics.c?v=3.7">3.7</a>&nbsp;<a href="source/net/ipv4/fib_semantics.c?v=3.8">3.8</a>&nbsp;<a href="source/net/ipv4/fib_semantics.c?v=3.9">3.9</a>&nbsp;<a href="source/net/ipv4/fib_semantics.c?v=3.10">3.10</a>&nbsp;<a href="source/net/ipv4/fib_semantics.c?v=3.11">3.11</a>&nbsp;<a href="source/net/ipv4/fib_semantics.c?v=3.12">3.12</a>&nbsp;<a href="source/net/ipv4/fib_semantics.c?v=3.13">3.13</a>&nbsp;<a href="source/net/ipv4/fib_semantics.c?v=3.14">3.14</a>&nbsp;<a href="source/net/ipv4/fib_semantics.c?v=3.15">3.15</a>&nbsp;<a href="source/net/ipv4/fib_semantics.c?v=3.16">3.16</a>&nbsp;<a href="source/net/ipv4/fib_semantics.c?v=3.17">3.17</a>&nbsp;<a href="source/net/ipv4/fib_semantics.c?v=3.18">3.18</a>&nbsp;<a href="source/net/ipv4/fib_semantics.c?v=3.19">3.19</a>&nbsp;<a href="source/net/ipv4/fib_semantics.c?v=4.0">4.0</a>&nbsp;<b><i>4.1</i></b></p>
  
</div>

<h1><a href="source/">Linux</a>/<a href="source/net/">net</a>/<a href="source/net/ipv4/">ipv4</a>/<a href="source/net/ipv4/fib_semantics.c">fib_semantics.c</a></h1>
<div id="lxrcode"><pre>  <a name="L1" href="source/net/ipv4/fib_semantics.c#L1">1</a> <b><i>/*</i></b>
  <a name="L2" href="source/net/ipv4/fib_semantics.c#L2">2</a> <b><i> * INET         An implementation of the TCP/IP protocol suite for the LINUX</i></b>
  <a name="L3" href="source/net/ipv4/fib_semantics.c#L3">3</a> <b><i> *              operating system.  INET is implemented using the  BSD Socket</i></b>
  <a name="L4" href="source/net/ipv4/fib_semantics.c#L4">4</a> <b><i> *              interface as the means of communication with the user level.</i></b>
  <a name="L5" href="source/net/ipv4/fib_semantics.c#L5">5</a> <b><i> *</i></b>
  <a name="L6" href="source/net/ipv4/fib_semantics.c#L6">6</a> <b><i> *              IPv4 Forwarding Information Base: semantics.</i></b>
  <a name="L7" href="source/net/ipv4/fib_semantics.c#L7">7</a> <b><i> *</i></b>
  <a name="L8" href="source/net/ipv4/fib_semantics.c#L8">8</a> <b><i> * Authors:     Alexey Kuznetsov, &lt;kuznet@ms2.inr.ac.ru&gt;</i></b>
  <a name="L9" href="source/net/ipv4/fib_semantics.c#L9">9</a> <b><i> *</i></b>
 <a name="L10" href="source/net/ipv4/fib_semantics.c#L10">10</a> <b><i> *              This program is free software; you can redistribute it and/or</i></b>
 <a name="L11" href="source/net/ipv4/fib_semantics.c#L11">11</a> <b><i> *              modify it under the terms of the GNU General Public License</i></b>
 <a name="L12" href="source/net/ipv4/fib_semantics.c#L12">12</a> <b><i> *              as published by the Free Software Foundation; either version</i></b>
 <a name="L13" href="source/net/ipv4/fib_semantics.c#L13">13</a> <b><i> *              2 of the License, or (at your option) any later version.</i></b>
 <a name="L14" href="source/net/ipv4/fib_semantics.c#L14">14</a> <b><i> */</i></b>
 <a name="L15" href="source/net/ipv4/fib_semantics.c#L15">15</a> 
 <a name="L16" href="source/net/ipv4/fib_semantics.c#L16">16</a> #include &lt;asm/uaccess.h&gt;
 <a name="L17" href="source/net/ipv4/fib_semantics.c#L17">17</a> #include &lt;linux/bitops.h&gt;
 <a name="L18" href="source/net/ipv4/fib_semantics.c#L18">18</a> #include &lt;linux/types.h&gt;
 <a name="L19" href="source/net/ipv4/fib_semantics.c#L19">19</a> #include &lt;linux/kernel.h&gt;
 <a name="L20" href="source/net/ipv4/fib_semantics.c#L20">20</a> #include &lt;linux/jiffies.h&gt;
 <a name="L21" href="source/net/ipv4/fib_semantics.c#L21">21</a> #include &lt;linux/mm.h&gt;
 <a name="L22" href="source/net/ipv4/fib_semantics.c#L22">22</a> #include &lt;linux/string.h&gt;
 <a name="L23" href="source/net/ipv4/fib_semantics.c#L23">23</a> #include &lt;linux/socket.h&gt;
 <a name="L24" href="source/net/ipv4/fib_semantics.c#L24">24</a> #include &lt;linux/sockios.h&gt;
 <a name="L25" href="source/net/ipv4/fib_semantics.c#L25">25</a> #include &lt;linux/errno.h&gt;
 <a name="L26" href="source/net/ipv4/fib_semantics.c#L26">26</a> #include &lt;linux/in.h&gt;
 <a name="L27" href="source/net/ipv4/fib_semantics.c#L27">27</a> #include &lt;linux/inet.h&gt;
 <a name="L28" href="source/net/ipv4/fib_semantics.c#L28">28</a> #include &lt;linux/inetdevice.h&gt;
 <a name="L29" href="source/net/ipv4/fib_semantics.c#L29">29</a> #include &lt;linux/netdevice.h&gt;
 <a name="L30" href="source/net/ipv4/fib_semantics.c#L30">30</a> #include &lt;linux/if_arp.h&gt;
 <a name="L31" href="source/net/ipv4/fib_semantics.c#L31">31</a> #include &lt;linux/proc_fs.h&gt;
 <a name="L32" href="source/net/ipv4/fib_semantics.c#L32">32</a> #include &lt;linux/skbuff.h&gt;
 <a name="L33" href="source/net/ipv4/fib_semantics.c#L33">33</a> #include &lt;linux/init.h&gt;
 <a name="L34" href="source/net/ipv4/fib_semantics.c#L34">34</a> #include &lt;linux/slab.h&gt;
 <a name="L35" href="source/net/ipv4/fib_semantics.c#L35">35</a> 
 <a name="L36" href="source/net/ipv4/fib_semantics.c#L36">36</a> #include &lt;net/arp.h&gt;
 <a name="L37" href="source/net/ipv4/fib_semantics.c#L37">37</a> #include &lt;net/ip.h&gt;
 <a name="L38" href="source/net/ipv4/fib_semantics.c#L38">38</a> #include &lt;net/protocol.h&gt;
 <a name="L39" href="source/net/ipv4/fib_semantics.c#L39">39</a> #include &lt;net/route.h&gt;
 <a name="L40" href="source/net/ipv4/fib_semantics.c#L40">40</a> #include &lt;net/tcp.h&gt;
 <a name="L41" href="source/net/ipv4/fib_semantics.c#L41">41</a> #include &lt;net/sock.h&gt;
 <a name="L42" href="source/net/ipv4/fib_semantics.c#L42">42</a> #include &lt;net/ip_fib.h&gt;
 <a name="L43" href="source/net/ipv4/fib_semantics.c#L43">43</a> #include &lt;net/netlink.h&gt;
 <a name="L44" href="source/net/ipv4/fib_semantics.c#L44">44</a> #include &lt;net/nexthop.h&gt;
 <a name="L45" href="source/net/ipv4/fib_semantics.c#L45">45</a> 
 <a name="L46" href="source/net/ipv4/fib_semantics.c#L46">46</a> #include "<a href="source/net/ipv4/fib_lookup.h">fib_lookup.h</a>"
 <a name="L47" href="source/net/ipv4/fib_semantics.c#L47">47</a> 
 <a name="L48" href="source/net/ipv4/fib_semantics.c#L48">48</a> static <a href="ident?i=DEFINE_SPINLOCK">DEFINE_SPINLOCK</a>(fib_info_lock);
 <a name="L49" href="source/net/ipv4/fib_semantics.c#L49">49</a> static struct <a href="ident?i=hlist_head">hlist_head</a> *<a href="ident?i=fib_info_hash">fib_info_hash</a>;
 <a name="L50" href="source/net/ipv4/fib_semantics.c#L50">50</a> static struct <a href="ident?i=hlist_head">hlist_head</a> *<a href="ident?i=fib_info_laddrhash">fib_info_laddrhash</a>;
 <a name="L51" href="source/net/ipv4/fib_semantics.c#L51">51</a> static unsigned int <a href="ident?i=fib_info_hash_size">fib_info_hash_size</a>;
 <a name="L52" href="source/net/ipv4/fib_semantics.c#L52">52</a> static unsigned int <a href="ident?i=fib_info_cnt">fib_info_cnt</a>;
 <a name="L53" href="source/net/ipv4/fib_semantics.c#L53">53</a> 
 <a name="L54" href="source/net/ipv4/fib_semantics.c#L54">54</a> #define <a href="ident?i=DEVINDEX_HASHBITS">DEVINDEX_HASHBITS</a> 8
 <a name="L55" href="source/net/ipv4/fib_semantics.c#L55">55</a> #define <a href="ident?i=DEVINDEX_HASHSIZE">DEVINDEX_HASHSIZE</a> (1U &lt;&lt; <a href="ident?i=DEVINDEX_HASHBITS">DEVINDEX_HASHBITS</a>)
 <a name="L56" href="source/net/ipv4/fib_semantics.c#L56">56</a> static struct <a href="ident?i=hlist_head">hlist_head</a> <a href="ident?i=fib_info_devhash">fib_info_devhash</a>[<a href="ident?i=DEVINDEX_HASHSIZE">DEVINDEX_HASHSIZE</a>];
 <a name="L57" href="source/net/ipv4/fib_semantics.c#L57">57</a> 
 <a name="L58" href="source/net/ipv4/fib_semantics.c#L58">58</a> #ifdef CONFIG_IP_ROUTE_MULTIPATH
 <a name="L59" href="source/net/ipv4/fib_semantics.c#L59">59</a> 
 <a name="L60" href="source/net/ipv4/fib_semantics.c#L60">60</a> static <a href="ident?i=DEFINE_SPINLOCK">DEFINE_SPINLOCK</a>(fib_multipath_lock);
 <a name="L61" href="source/net/ipv4/fib_semantics.c#L61">61</a> 
 <a name="L62" href="source/net/ipv4/fib_semantics.c#L62">62</a> #define <a href="ident?i=for_nexthops">for_nexthops</a>(fi) {                                              \
 <a name="L63" href="source/net/ipv4/fib_semantics.c#L63">63</a>         int nhsel; const struct <a href="ident?i=fib_nh">fib_nh</a> *nh;                             \
 <a name="L64" href="source/net/ipv4/fib_semantics.c#L64">64</a>         for (nhsel = 0, nh = (fi)-&gt;<a href="ident?i=fib_nh">fib_nh</a>;                              \
 <a name="L65" href="source/net/ipv4/fib_semantics.c#L65">65</a>              nhsel &lt; (fi)-&gt;fib_nhs;                                     \
 <a name="L66" href="source/net/ipv4/fib_semantics.c#L66">66</a>              nh++, nhsel++)
 <a name="L67" href="source/net/ipv4/fib_semantics.c#L67">67</a> 
 <a name="L68" href="source/net/ipv4/fib_semantics.c#L68">68</a> #define <a href="ident?i=change_nexthops">change_nexthops</a>(fi) {                                           \
 <a name="L69" href="source/net/ipv4/fib_semantics.c#L69">69</a>         int nhsel; struct <a href="ident?i=fib_nh">fib_nh</a> *nexthop_nh;                           \
 <a name="L70" href="source/net/ipv4/fib_semantics.c#L70">70</a>         for (nhsel = 0, nexthop_nh = (struct <a href="ident?i=fib_nh">fib_nh</a> *)((fi)-&gt;<a href="ident?i=fib_nh">fib_nh</a>);   \
 <a name="L71" href="source/net/ipv4/fib_semantics.c#L71">71</a>              nhsel &lt; (fi)-&gt;fib_nhs;                                     \
 <a name="L72" href="source/net/ipv4/fib_semantics.c#L72">72</a>              nexthop_nh++, nhsel++)
 <a name="L73" href="source/net/ipv4/fib_semantics.c#L73">73</a> 
 <a name="L74" href="source/net/ipv4/fib_semantics.c#L74">74</a> #else <b><i>/* CONFIG_IP_ROUTE_MULTIPATH */</i></b>
 <a name="L75" href="source/net/ipv4/fib_semantics.c#L75">75</a> 
 <a name="L76" href="source/net/ipv4/fib_semantics.c#L76">76</a> <b><i>/* Hope, that gcc will optimize it to get rid of dummy loop */</i></b>
 <a name="L77" href="source/net/ipv4/fib_semantics.c#L77">77</a> 
 <a name="L78" href="source/net/ipv4/fib_semantics.c#L78">78</a> #define <a href="ident?i=for_nexthops">for_nexthops</a>(fi) {                                              \
 <a name="L79" href="source/net/ipv4/fib_semantics.c#L79">79</a>         int nhsel; const struct <a href="ident?i=fib_nh">fib_nh</a> *nh = (fi)-&gt;<a href="ident?i=fib_nh">fib_nh</a>;              \
 <a name="L80" href="source/net/ipv4/fib_semantics.c#L80">80</a>         for (nhsel = 0; nhsel &lt; 1; nhsel++)
 <a name="L81" href="source/net/ipv4/fib_semantics.c#L81">81</a> 
 <a name="L82" href="source/net/ipv4/fib_semantics.c#L82">82</a> #define <a href="ident?i=change_nexthops">change_nexthops</a>(fi) {                                           \
 <a name="L83" href="source/net/ipv4/fib_semantics.c#L83">83</a>         int nhsel;                                                      \
 <a name="L84" href="source/net/ipv4/fib_semantics.c#L84">84</a>         struct <a href="ident?i=fib_nh">fib_nh</a> *nexthop_nh = (struct <a href="ident?i=fib_nh">fib_nh</a> *)((fi)-&gt;<a href="ident?i=fib_nh">fib_nh</a>);    \
 <a name="L85" href="source/net/ipv4/fib_semantics.c#L85">85</a>         for (nhsel = 0; nhsel &lt; 1; nhsel++)
 <a name="L86" href="source/net/ipv4/fib_semantics.c#L86">86</a> 
 <a name="L87" href="source/net/ipv4/fib_semantics.c#L87">87</a> #endif <b><i>/* CONFIG_IP_ROUTE_MULTIPATH */</i></b>
 <a name="L88" href="source/net/ipv4/fib_semantics.c#L88">88</a> 
 <a name="L89" href="source/net/ipv4/fib_semantics.c#L89">89</a> #define <a href="ident?i=endfor_nexthops">endfor_nexthops</a>(fi) }
 <a name="L90" href="source/net/ipv4/fib_semantics.c#L90">90</a> 
 <a name="L91" href="source/net/ipv4/fib_semantics.c#L91">91</a> 
 <a name="L92" href="source/net/ipv4/fib_semantics.c#L92">92</a> const struct <a href="ident?i=fib_prop">fib_prop</a> <a href="ident?i=fib_props">fib_props</a>[<a href="ident?i=RTN_MAX">RTN_MAX</a> + 1] = {
 <a name="L93" href="source/net/ipv4/fib_semantics.c#L93">93</a>         [RTN_UNSPEC] = {
 <a name="L94" href="source/net/ipv4/fib_semantics.c#L94">94</a>                 .<a href="ident?i=error">error</a>  = 0,
 <a name="L95" href="source/net/ipv4/fib_semantics.c#L95">95</a>                 .<a href="ident?i=scope">scope</a>  = RT_SCOPE_NOWHERE,
 <a name="L96" href="source/net/ipv4/fib_semantics.c#L96">96</a>         },
 <a name="L97" href="source/net/ipv4/fib_semantics.c#L97">97</a>         [RTN_UNICAST] = {
 <a name="L98" href="source/net/ipv4/fib_semantics.c#L98">98</a>                 .<a href="ident?i=error">error</a>  = 0,
 <a name="L99" href="source/net/ipv4/fib_semantics.c#L99">99</a>                 .<a href="ident?i=scope">scope</a>  = RT_SCOPE_UNIVERSE,
<a name="L100" href="source/net/ipv4/fib_semantics.c#L100">100</a>         },
<a name="L101" href="source/net/ipv4/fib_semantics.c#L101">101</a>         [RTN_LOCAL] = {
<a name="L102" href="source/net/ipv4/fib_semantics.c#L102">102</a>                 .<a href="ident?i=error">error</a>  = 0,
<a name="L103" href="source/net/ipv4/fib_semantics.c#L103">103</a>                 .<a href="ident?i=scope">scope</a>  = RT_SCOPE_HOST,
<a name="L104" href="source/net/ipv4/fib_semantics.c#L104">104</a>         },
<a name="L105" href="source/net/ipv4/fib_semantics.c#L105">105</a>         [RTN_BROADCAST] = {
<a name="L106" href="source/net/ipv4/fib_semantics.c#L106">106</a>                 .<a href="ident?i=error">error</a>  = 0,
<a name="L107" href="source/net/ipv4/fib_semantics.c#L107">107</a>                 .<a href="ident?i=scope">scope</a>  = RT_SCOPE_LINK,
<a name="L108" href="source/net/ipv4/fib_semantics.c#L108">108</a>         },
<a name="L109" href="source/net/ipv4/fib_semantics.c#L109">109</a>         [RTN_ANYCAST] = {
<a name="L110" href="source/net/ipv4/fib_semantics.c#L110">110</a>                 .<a href="ident?i=error">error</a>  = 0,
<a name="L111" href="source/net/ipv4/fib_semantics.c#L111">111</a>                 .<a href="ident?i=scope">scope</a>  = RT_SCOPE_LINK,
<a name="L112" href="source/net/ipv4/fib_semantics.c#L112">112</a>         },
<a name="L113" href="source/net/ipv4/fib_semantics.c#L113">113</a>         [RTN_MULTICAST] = {
<a name="L114" href="source/net/ipv4/fib_semantics.c#L114">114</a>                 .<a href="ident?i=error">error</a>  = 0,
<a name="L115" href="source/net/ipv4/fib_semantics.c#L115">115</a>                 .<a href="ident?i=scope">scope</a>  = RT_SCOPE_UNIVERSE,
<a name="L116" href="source/net/ipv4/fib_semantics.c#L116">116</a>         },
<a name="L117" href="source/net/ipv4/fib_semantics.c#L117">117</a>         [RTN_BLACKHOLE] = {
<a name="L118" href="source/net/ipv4/fib_semantics.c#L118">118</a>                 .<a href="ident?i=error">error</a>  = -<a href="ident?i=EINVAL">EINVAL</a>,
<a name="L119" href="source/net/ipv4/fib_semantics.c#L119">119</a>                 .<a href="ident?i=scope">scope</a>  = RT_SCOPE_UNIVERSE,
<a name="L120" href="source/net/ipv4/fib_semantics.c#L120">120</a>         },
<a name="L121" href="source/net/ipv4/fib_semantics.c#L121">121</a>         [RTN_UNREACHABLE] = {
<a name="L122" href="source/net/ipv4/fib_semantics.c#L122">122</a>                 .<a href="ident?i=error">error</a>  = -<a href="ident?i=EHOSTUNREACH">EHOSTUNREACH</a>,
<a name="L123" href="source/net/ipv4/fib_semantics.c#L123">123</a>                 .<a href="ident?i=scope">scope</a>  = RT_SCOPE_UNIVERSE,
<a name="L124" href="source/net/ipv4/fib_semantics.c#L124">124</a>         },
<a name="L125" href="source/net/ipv4/fib_semantics.c#L125">125</a>         [RTN_PROHIBIT] = {
<a name="L126" href="source/net/ipv4/fib_semantics.c#L126">126</a>                 .<a href="ident?i=error">error</a>  = -<a href="ident?i=EACCES">EACCES</a>,
<a name="L127" href="source/net/ipv4/fib_semantics.c#L127">127</a>                 .<a href="ident?i=scope">scope</a>  = RT_SCOPE_UNIVERSE,
<a name="L128" href="source/net/ipv4/fib_semantics.c#L128">128</a>         },
<a name="L129" href="source/net/ipv4/fib_semantics.c#L129">129</a>         [RTN_THROW] = {
<a name="L130" href="source/net/ipv4/fib_semantics.c#L130">130</a>                 .<a href="ident?i=error">error</a>  = -<a href="ident?i=EAGAIN">EAGAIN</a>,
<a name="L131" href="source/net/ipv4/fib_semantics.c#L131">131</a>                 .<a href="ident?i=scope">scope</a>  = RT_SCOPE_UNIVERSE,
<a name="L132" href="source/net/ipv4/fib_semantics.c#L132">132</a>         },
<a name="L133" href="source/net/ipv4/fib_semantics.c#L133">133</a>         [RTN_NAT] = {
<a name="L134" href="source/net/ipv4/fib_semantics.c#L134">134</a>                 .<a href="ident?i=error">error</a>  = -<a href="ident?i=EINVAL">EINVAL</a>,
<a name="L135" href="source/net/ipv4/fib_semantics.c#L135">135</a>                 .<a href="ident?i=scope">scope</a>  = RT_SCOPE_NOWHERE,
<a name="L136" href="source/net/ipv4/fib_semantics.c#L136">136</a>         },
<a name="L137" href="source/net/ipv4/fib_semantics.c#L137">137</a>         [RTN_XRESOLVE] = {
<a name="L138" href="source/net/ipv4/fib_semantics.c#L138">138</a>                 .<a href="ident?i=error">error</a>  = -<a href="ident?i=EINVAL">EINVAL</a>,
<a name="L139" href="source/net/ipv4/fib_semantics.c#L139">139</a>                 .<a href="ident?i=scope">scope</a>  = RT_SCOPE_NOWHERE,
<a name="L140" href="source/net/ipv4/fib_semantics.c#L140">140</a>         },
<a name="L141" href="source/net/ipv4/fib_semantics.c#L141">141</a> };
<a name="L142" href="source/net/ipv4/fib_semantics.c#L142">142</a> 
<a name="L143" href="source/net/ipv4/fib_semantics.c#L143">143</a> static void <a href="ident?i=rt_fibinfo_free">rt_fibinfo_free</a>(struct <a href="ident?i=rtable">rtable</a> <a href="ident?i=__rcu">__rcu</a> **rtp)
<a name="L144" href="source/net/ipv4/fib_semantics.c#L144">144</a> {
<a name="L145" href="source/net/ipv4/fib_semantics.c#L145">145</a>         struct <a href="ident?i=rtable">rtable</a> *<a href="ident?i=rt">rt</a> = <a href="ident?i=rcu_dereference_protected">rcu_dereference_protected</a>(*rtp, 1);
<a name="L146" href="source/net/ipv4/fib_semantics.c#L146">146</a> 
<a name="L147" href="source/net/ipv4/fib_semantics.c#L147">147</a>         if (!<a href="ident?i=rt">rt</a>)
<a name="L148" href="source/net/ipv4/fib_semantics.c#L148">148</a>                 return;
<a name="L149" href="source/net/ipv4/fib_semantics.c#L149">149</a> 
<a name="L150" href="source/net/ipv4/fib_semantics.c#L150">150</a>         <b><i>/* Not even needed : RCU_INIT_POINTER(*rtp, NULL);</i></b>
<a name="L151" href="source/net/ipv4/fib_semantics.c#L151">151</a> <b><i>         * because we waited an RCU grace period before calling</i></b>
<a name="L152" href="source/net/ipv4/fib_semantics.c#L152">152</a> <b><i>         * free_fib_info_rcu()</i></b>
<a name="L153" href="source/net/ipv4/fib_semantics.c#L153">153</a> <b><i>         */</i></b>
<a name="L154" href="source/net/ipv4/fib_semantics.c#L154">154</a> 
<a name="L155" href="source/net/ipv4/fib_semantics.c#L155">155</a>         <a href="ident?i=dst_free">dst_free</a>(&amp;<a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>);
<a name="L156" href="source/net/ipv4/fib_semantics.c#L156">156</a> }
<a name="L157" href="source/net/ipv4/fib_semantics.c#L157">157</a> 
<a name="L158" href="source/net/ipv4/fib_semantics.c#L158">158</a> static void <a href="ident?i=free_nh_exceptions">free_nh_exceptions</a>(struct <a href="ident?i=fib_nh">fib_nh</a> *nh)
<a name="L159" href="source/net/ipv4/fib_semantics.c#L159">159</a> {
<a name="L160" href="source/net/ipv4/fib_semantics.c#L160">160</a>         struct <a href="ident?i=fnhe_hash_bucket">fnhe_hash_bucket</a> *<a href="ident?i=hash">hash</a>;
<a name="L161" href="source/net/ipv4/fib_semantics.c#L161">161</a>         int <a href="ident?i=i">i</a>;
<a name="L162" href="source/net/ipv4/fib_semantics.c#L162">162</a> 
<a name="L163" href="source/net/ipv4/fib_semantics.c#L163">163</a>         <a href="ident?i=hash">hash</a> = <a href="ident?i=rcu_dereference_protected">rcu_dereference_protected</a>(nh-&gt;nh_exceptions, 1);
<a name="L164" href="source/net/ipv4/fib_semantics.c#L164">164</a>         if (!<a href="ident?i=hash">hash</a>)
<a name="L165" href="source/net/ipv4/fib_semantics.c#L165">165</a>                 return;
<a name="L166" href="source/net/ipv4/fib_semantics.c#L166">166</a>         for (<a href="ident?i=i">i</a> = 0; <a href="ident?i=i">i</a> &lt; <a href="ident?i=FNHE_HASH_SIZE">FNHE_HASH_SIZE</a>; <a href="ident?i=i">i</a>++) {
<a name="L167" href="source/net/ipv4/fib_semantics.c#L167">167</a>                 struct <a href="ident?i=fib_nh_exception">fib_nh_exception</a> *fnhe;
<a name="L168" href="source/net/ipv4/fib_semantics.c#L168">168</a> 
<a name="L169" href="source/net/ipv4/fib_semantics.c#L169">169</a>                 fnhe = <a href="ident?i=rcu_dereference_protected">rcu_dereference_protected</a>(<a href="ident?i=hash">hash</a>[<a href="ident?i=i">i</a>].<a href="ident?i=chain">chain</a>, 1);
<a name="L170" href="source/net/ipv4/fib_semantics.c#L170">170</a>                 while (fnhe) {
<a name="L171" href="source/net/ipv4/fib_semantics.c#L171">171</a>                         struct <a href="ident?i=fib_nh_exception">fib_nh_exception</a> *<a href="ident?i=next">next</a>;
<a name="L172" href="source/net/ipv4/fib_semantics.c#L172">172</a>                         
<a name="L173" href="source/net/ipv4/fib_semantics.c#L173">173</a>                         <a href="ident?i=next">next</a> = <a href="ident?i=rcu_dereference_protected">rcu_dereference_protected</a>(fnhe-&gt;fnhe_next, 1);
<a name="L174" href="source/net/ipv4/fib_semantics.c#L174">174</a> 
<a name="L175" href="source/net/ipv4/fib_semantics.c#L175">175</a>                         <a href="ident?i=rt_fibinfo_free">rt_fibinfo_free</a>(&amp;fnhe-&gt;fnhe_rth_input);
<a name="L176" href="source/net/ipv4/fib_semantics.c#L176">176</a>                         <a href="ident?i=rt_fibinfo_free">rt_fibinfo_free</a>(&amp;fnhe-&gt;fnhe_rth_output);
<a name="L177" href="source/net/ipv4/fib_semantics.c#L177">177</a> 
<a name="L178" href="source/net/ipv4/fib_semantics.c#L178">178</a>                         <a href="ident?i=kfree">kfree</a>(fnhe);
<a name="L179" href="source/net/ipv4/fib_semantics.c#L179">179</a> 
<a name="L180" href="source/net/ipv4/fib_semantics.c#L180">180</a>                         fnhe = <a href="ident?i=next">next</a>;
<a name="L181" href="source/net/ipv4/fib_semantics.c#L181">181</a>                 }
<a name="L182" href="source/net/ipv4/fib_semantics.c#L182">182</a>         }
<a name="L183" href="source/net/ipv4/fib_semantics.c#L183">183</a>         <a href="ident?i=kfree">kfree</a>(<a href="ident?i=hash">hash</a>);
<a name="L184" href="source/net/ipv4/fib_semantics.c#L184">184</a> }
<a name="L185" href="source/net/ipv4/fib_semantics.c#L185">185</a> 
<a name="L186" href="source/net/ipv4/fib_semantics.c#L186">186</a> static void <a href="ident?i=rt_fibinfo_free_cpus">rt_fibinfo_free_cpus</a>(struct <a href="ident?i=rtable">rtable</a> <a href="ident?i=__rcu">__rcu</a> * <a href="ident?i=__percpu">__percpu</a> *rtp)
<a name="L187" href="source/net/ipv4/fib_semantics.c#L187">187</a> {
<a name="L188" href="source/net/ipv4/fib_semantics.c#L188">188</a>         int <a href="ident?i=cpu">cpu</a>;
<a name="L189" href="source/net/ipv4/fib_semantics.c#L189">189</a> 
<a name="L190" href="source/net/ipv4/fib_semantics.c#L190">190</a>         if (!rtp)
<a name="L191" href="source/net/ipv4/fib_semantics.c#L191">191</a>                 return;
<a name="L192" href="source/net/ipv4/fib_semantics.c#L192">192</a> 
<a name="L193" href="source/net/ipv4/fib_semantics.c#L193">193</a>         <a href="ident?i=for_each_possible_cpu">for_each_possible_cpu</a>(<a href="ident?i=cpu">cpu</a>) {
<a name="L194" href="source/net/ipv4/fib_semantics.c#L194">194</a>                 struct <a href="ident?i=rtable">rtable</a> *<a href="ident?i=rt">rt</a>;
<a name="L195" href="source/net/ipv4/fib_semantics.c#L195">195</a> 
<a name="L196" href="source/net/ipv4/fib_semantics.c#L196">196</a>                 <a href="ident?i=rt">rt</a> = <a href="ident?i=rcu_dereference_protected">rcu_dereference_protected</a>(*<a href="ident?i=per_cpu_ptr">per_cpu_ptr</a>(rtp, <a href="ident?i=cpu">cpu</a>), 1);
<a name="L197" href="source/net/ipv4/fib_semantics.c#L197">197</a>                 if (<a href="ident?i=rt">rt</a>)
<a name="L198" href="source/net/ipv4/fib_semantics.c#L198">198</a>                         <a href="ident?i=dst_free">dst_free</a>(&amp;<a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>);
<a name="L199" href="source/net/ipv4/fib_semantics.c#L199">199</a>         }
<a name="L200" href="source/net/ipv4/fib_semantics.c#L200">200</a>         <a href="ident?i=free_percpu">free_percpu</a>(rtp);
<a name="L201" href="source/net/ipv4/fib_semantics.c#L201">201</a> }
<a name="L202" href="source/net/ipv4/fib_semantics.c#L202">202</a> 
<a name="L203" href="source/net/ipv4/fib_semantics.c#L203">203</a> <b><i>/* Release a nexthop info record */</i></b>
<a name="L204" href="source/net/ipv4/fib_semantics.c#L204">204</a> static void <a href="ident?i=free_fib_info_rcu">free_fib_info_rcu</a>(struct <a href="ident?i=rcu_head">rcu_head</a> *<a href="ident?i=head">head</a>)
<a name="L205" href="source/net/ipv4/fib_semantics.c#L205">205</a> {
<a name="L206" href="source/net/ipv4/fib_semantics.c#L206">206</a>         struct <a href="ident?i=fib_info">fib_info</a> *fi = <a href="ident?i=container_of">container_of</a>(<a href="ident?i=head">head</a>, struct <a href="ident?i=fib_info">fib_info</a>, rcu);
<a name="L207" href="source/net/ipv4/fib_semantics.c#L207">207</a> 
<a name="L208" href="source/net/ipv4/fib_semantics.c#L208">208</a>         <a href="ident?i=change_nexthops">change_nexthops</a>(fi) {
<a name="L209" href="source/net/ipv4/fib_semantics.c#L209">209</a>                 if (nexthop_nh-&gt;nh_dev)
<a name="L210" href="source/net/ipv4/fib_semantics.c#L210">210</a>                         <a href="ident?i=dev_put">dev_put</a>(nexthop_nh-&gt;nh_dev);
<a name="L211" href="source/net/ipv4/fib_semantics.c#L211">211</a>                 <a href="ident?i=free_nh_exceptions">free_nh_exceptions</a>(nexthop_nh);
<a name="L212" href="source/net/ipv4/fib_semantics.c#L212">212</a>                 <a href="ident?i=rt_fibinfo_free_cpus">rt_fibinfo_free_cpus</a>(nexthop_nh-&gt;nh_pcpu_rth_output);
<a name="L213" href="source/net/ipv4/fib_semantics.c#L213">213</a>                 <a href="ident?i=rt_fibinfo_free">rt_fibinfo_free</a>(&amp;nexthop_nh-&gt;nh_rth_input);
<a name="L214" href="source/net/ipv4/fib_semantics.c#L214">214</a>         } <a href="ident?i=endfor_nexthops">endfor_nexthops</a>(fi);
<a name="L215" href="source/net/ipv4/fib_semantics.c#L215">215</a> 
<a name="L216" href="source/net/ipv4/fib_semantics.c#L216">216</a>         if (fi-&gt;fib_metrics != (<a href="ident?i=u32">u32</a> *) <a href="ident?i=dst_default_metrics">dst_default_metrics</a>)
<a name="L217" href="source/net/ipv4/fib_semantics.c#L217">217</a>                 <a href="ident?i=kfree">kfree</a>(fi-&gt;fib_metrics);
<a name="L218" href="source/net/ipv4/fib_semantics.c#L218">218</a>         <a href="ident?i=kfree">kfree</a>(fi);
<a name="L219" href="source/net/ipv4/fib_semantics.c#L219">219</a> }
<a name="L220" href="source/net/ipv4/fib_semantics.c#L220">220</a> 
<a name="L221" href="source/net/ipv4/fib_semantics.c#L221">221</a> void <a href="ident?i=free_fib_info">free_fib_info</a>(struct <a href="ident?i=fib_info">fib_info</a> *fi)
<a name="L222" href="source/net/ipv4/fib_semantics.c#L222">222</a> {
<a name="L223" href="source/net/ipv4/fib_semantics.c#L223">223</a>         if (fi-&gt;fib_dead == 0) {
<a name="L224" href="source/net/ipv4/fib_semantics.c#L224">224</a>                 <a href="ident?i=pr_warn">pr_warn</a>(<i>"Freeing alive fib_info %p\n"</i>, fi);
<a name="L225" href="source/net/ipv4/fib_semantics.c#L225">225</a>                 return;
<a name="L226" href="source/net/ipv4/fib_semantics.c#L226">226</a>         }
<a name="L227" href="source/net/ipv4/fib_semantics.c#L227">227</a>         <a href="ident?i=fib_info_cnt">fib_info_cnt</a>--;
<a name="L228" href="source/net/ipv4/fib_semantics.c#L228">228</a> #ifdef CONFIG_IP_ROUTE_CLASSID
<a name="L229" href="source/net/ipv4/fib_semantics.c#L229">229</a>         <a href="ident?i=change_nexthops">change_nexthops</a>(fi) {
<a name="L230" href="source/net/ipv4/fib_semantics.c#L230">230</a>                 if (nexthop_nh-&gt;nh_tclassid)
<a name="L231" href="source/net/ipv4/fib_semantics.c#L231">231</a>                         fi-&gt;fib_net-&gt;ipv4.<a href="ident?i=fib_num_tclassid_users">fib_num_tclassid_users</a>--;
<a name="L232" href="source/net/ipv4/fib_semantics.c#L232">232</a>         } <a href="ident?i=endfor_nexthops">endfor_nexthops</a>(fi);
<a name="L233" href="source/net/ipv4/fib_semantics.c#L233">233</a> #endif
<a name="L234" href="source/net/ipv4/fib_semantics.c#L234">234</a>         <a href="ident?i=call_rcu">call_rcu</a>(&amp;fi-&gt;rcu, <a href="ident?i=free_fib_info_rcu">free_fib_info_rcu</a>);
<a name="L235" href="source/net/ipv4/fib_semantics.c#L235">235</a> }
<a name="L236" href="source/net/ipv4/fib_semantics.c#L236">236</a> 
<a name="L237" href="source/net/ipv4/fib_semantics.c#L237">237</a> void <a href="ident?i=fib_release_info">fib_release_info</a>(struct <a href="ident?i=fib_info">fib_info</a> *fi)
<a name="L238" href="source/net/ipv4/fib_semantics.c#L238">238</a> {
<a name="L239" href="source/net/ipv4/fib_semantics.c#L239">239</a>         <a href="ident?i=spin_lock_bh">spin_lock_bh</a>(&amp;fib_info_lock);
<a name="L240" href="source/net/ipv4/fib_semantics.c#L240">240</a>         if (fi &amp;&amp; --fi-&gt;fib_treeref == 0) {
<a name="L241" href="source/net/ipv4/fib_semantics.c#L241">241</a>                 <a href="ident?i=hlist_del">hlist_del</a>(&amp;fi-&gt;fib_hash);
<a name="L242" href="source/net/ipv4/fib_semantics.c#L242">242</a>                 if (fi-&gt;fib_prefsrc)
<a name="L243" href="source/net/ipv4/fib_semantics.c#L243">243</a>                         <a href="ident?i=hlist_del">hlist_del</a>(&amp;fi-&gt;fib_lhash);
<a name="L244" href="source/net/ipv4/fib_semantics.c#L244">244</a>                 <a href="ident?i=change_nexthops">change_nexthops</a>(fi) {
<a name="L245" href="source/net/ipv4/fib_semantics.c#L245">245</a>                         if (!nexthop_nh-&gt;nh_dev)
<a name="L246" href="source/net/ipv4/fib_semantics.c#L246">246</a>                                 continue;
<a name="L247" href="source/net/ipv4/fib_semantics.c#L247">247</a>                         <a href="ident?i=hlist_del">hlist_del</a>(&amp;nexthop_nh-&gt;nh_hash);
<a name="L248" href="source/net/ipv4/fib_semantics.c#L248">248</a>                 } <a href="ident?i=endfor_nexthops">endfor_nexthops</a>(fi)
<a name="L249" href="source/net/ipv4/fib_semantics.c#L249">249</a>                 fi-&gt;fib_dead = 1;
<a name="L250" href="source/net/ipv4/fib_semantics.c#L250">250</a>                 <a href="ident?i=fib_info_put">fib_info_put</a>(fi);
<a name="L251" href="source/net/ipv4/fib_semantics.c#L251">251</a>         }
<a name="L252" href="source/net/ipv4/fib_semantics.c#L252">252</a>         <a href="ident?i=spin_unlock_bh">spin_unlock_bh</a>(&amp;fib_info_lock);
<a name="L253" href="source/net/ipv4/fib_semantics.c#L253">253</a> }
<a name="L254" href="source/net/ipv4/fib_semantics.c#L254">254</a> 
<a name="L255" href="source/net/ipv4/fib_semantics.c#L255">255</a> static inline int <a href="ident?i=nh_comp">nh_comp</a>(const struct <a href="ident?i=fib_info">fib_info</a> *fi, const struct <a href="ident?i=fib_info">fib_info</a> *ofi)
<a name="L256" href="source/net/ipv4/fib_semantics.c#L256">256</a> {
<a name="L257" href="source/net/ipv4/fib_semantics.c#L257">257</a>         const struct <a href="ident?i=fib_nh">fib_nh</a> *onh = ofi-&gt;<a href="ident?i=fib_nh">fib_nh</a>;
<a name="L258" href="source/net/ipv4/fib_semantics.c#L258">258</a> 
<a name="L259" href="source/net/ipv4/fib_semantics.c#L259">259</a>         <a href="ident?i=for_nexthops">for_nexthops</a>(fi) {
<a name="L260" href="source/net/ipv4/fib_semantics.c#L260">260</a>                 if (nh-&gt;nh_oif != onh-&gt;nh_oif ||
<a name="L261" href="source/net/ipv4/fib_semantics.c#L261">261</a>                     nh-&gt;nh_gw  != onh-&gt;nh_gw ||
<a name="L262" href="source/net/ipv4/fib_semantics.c#L262">262</a>                     nh-&gt;nh_scope != onh-&gt;nh_scope ||
<a name="L263" href="source/net/ipv4/fib_semantics.c#L263">263</a> #ifdef CONFIG_IP_ROUTE_MULTIPATH
<a name="L264" href="source/net/ipv4/fib_semantics.c#L264">264</a>                     nh-&gt;nh_weight != onh-&gt;nh_weight ||
<a name="L265" href="source/net/ipv4/fib_semantics.c#L265">265</a> #endif
<a name="L266" href="source/net/ipv4/fib_semantics.c#L266">266</a> #ifdef CONFIG_IP_ROUTE_CLASSID
<a name="L267" href="source/net/ipv4/fib_semantics.c#L267">267</a>                     nh-&gt;nh_tclassid != onh-&gt;nh_tclassid ||
<a name="L268" href="source/net/ipv4/fib_semantics.c#L268">268</a> #endif
<a name="L269" href="source/net/ipv4/fib_semantics.c#L269">269</a>                     ((nh-&gt;nh_flags ^ onh-&gt;nh_flags) &amp; ~RTNH_F_DEAD))
<a name="L270" href="source/net/ipv4/fib_semantics.c#L270">270</a>                         return -1;
<a name="L271" href="source/net/ipv4/fib_semantics.c#L271">271</a>                 onh++;
<a name="L272" href="source/net/ipv4/fib_semantics.c#L272">272</a>         } <a href="ident?i=endfor_nexthops">endfor_nexthops</a>(fi);
<a name="L273" href="source/net/ipv4/fib_semantics.c#L273">273</a>         return 0;
<a name="L274" href="source/net/ipv4/fib_semantics.c#L274">274</a> }
<a name="L275" href="source/net/ipv4/fib_semantics.c#L275">275</a> 
<a name="L276" href="source/net/ipv4/fib_semantics.c#L276">276</a> static inline unsigned int <a href="ident?i=fib_devindex_hashfn">fib_devindex_hashfn</a>(unsigned int <a href="ident?i=val">val</a>)
<a name="L277" href="source/net/ipv4/fib_semantics.c#L277">277</a> {
<a name="L278" href="source/net/ipv4/fib_semantics.c#L278">278</a>         unsigned int <a href="ident?i=mask">mask</a> = <a href="ident?i=DEVINDEX_HASHSIZE">DEVINDEX_HASHSIZE</a> - 1;
<a name="L279" href="source/net/ipv4/fib_semantics.c#L279">279</a> 
<a name="L280" href="source/net/ipv4/fib_semantics.c#L280">280</a>         return (<a href="ident?i=val">val</a> ^
<a name="L281" href="source/net/ipv4/fib_semantics.c#L281">281</a>                 (<a href="ident?i=val">val</a> &gt;&gt; <a href="ident?i=DEVINDEX_HASHBITS">DEVINDEX_HASHBITS</a>) ^
<a name="L282" href="source/net/ipv4/fib_semantics.c#L282">282</a>                 (<a href="ident?i=val">val</a> &gt;&gt; (<a href="ident?i=DEVINDEX_HASHBITS">DEVINDEX_HASHBITS</a> * 2))) &amp; <a href="ident?i=mask">mask</a>;
<a name="L283" href="source/net/ipv4/fib_semantics.c#L283">283</a> }
<a name="L284" href="source/net/ipv4/fib_semantics.c#L284">284</a> 
<a name="L285" href="source/net/ipv4/fib_semantics.c#L285">285</a> static inline unsigned int <a href="ident?i=fib_info_hashfn">fib_info_hashfn</a>(const struct <a href="ident?i=fib_info">fib_info</a> *fi)
<a name="L286" href="source/net/ipv4/fib_semantics.c#L286">286</a> {
<a name="L287" href="source/net/ipv4/fib_semantics.c#L287">287</a>         unsigned int <a href="ident?i=mask">mask</a> = (<a href="ident?i=fib_info_hash_size">fib_info_hash_size</a> - 1);
<a name="L288" href="source/net/ipv4/fib_semantics.c#L288">288</a>         unsigned int <a href="ident?i=val">val</a> = fi-&gt;fib_nhs;
<a name="L289" href="source/net/ipv4/fib_semantics.c#L289">289</a> 
<a name="L290" href="source/net/ipv4/fib_semantics.c#L290">290</a>         <a href="ident?i=val">val</a> ^= (fi-&gt;fib_protocol &lt;&lt; 8) | fi-&gt;fib_scope;
<a name="L291" href="source/net/ipv4/fib_semantics.c#L291">291</a>         <a href="ident?i=val">val</a> ^= (<a href="ident?i=__force">__force</a> <a href="ident?i=u32">u32</a>)fi-&gt;fib_prefsrc;
<a name="L292" href="source/net/ipv4/fib_semantics.c#L292">292</a>         <a href="ident?i=val">val</a> ^= fi-&gt;fib_priority;
<a name="L293" href="source/net/ipv4/fib_semantics.c#L293">293</a>         <a href="ident?i=for_nexthops">for_nexthops</a>(fi) {
<a name="L294" href="source/net/ipv4/fib_semantics.c#L294">294</a>                 <a href="ident?i=val">val</a> ^= <a href="ident?i=fib_devindex_hashfn">fib_devindex_hashfn</a>(nh-&gt;nh_oif);
<a name="L295" href="source/net/ipv4/fib_semantics.c#L295">295</a>         } <a href="ident?i=endfor_nexthops">endfor_nexthops</a>(fi)
<a name="L296" href="source/net/ipv4/fib_semantics.c#L296">296</a> 
<a name="L297" href="source/net/ipv4/fib_semantics.c#L297">297</a>         return (<a href="ident?i=val">val</a> ^ (<a href="ident?i=val">val</a> &gt;&gt; 7) ^ (<a href="ident?i=val">val</a> &gt;&gt; 12)) &amp; <a href="ident?i=mask">mask</a>;
<a name="L298" href="source/net/ipv4/fib_semantics.c#L298">298</a> }
<a name="L299" href="source/net/ipv4/fib_semantics.c#L299">299</a> 
<a name="L300" href="source/net/ipv4/fib_semantics.c#L300">300</a> static struct <a href="ident?i=fib_info">fib_info</a> *<a href="ident?i=fib_find_info">fib_find_info</a>(const struct <a href="ident?i=fib_info">fib_info</a> *nfi)
<a name="L301" href="source/net/ipv4/fib_semantics.c#L301">301</a> {
<a name="L302" href="source/net/ipv4/fib_semantics.c#L302">302</a>         struct <a href="ident?i=hlist_head">hlist_head</a> *<a href="ident?i=head">head</a>;
<a name="L303" href="source/net/ipv4/fib_semantics.c#L303">303</a>         struct <a href="ident?i=fib_info">fib_info</a> *fi;
<a name="L304" href="source/net/ipv4/fib_semantics.c#L304">304</a>         unsigned int <a href="ident?i=hash">hash</a>;
<a name="L305" href="source/net/ipv4/fib_semantics.c#L305">305</a> 
<a name="L306" href="source/net/ipv4/fib_semantics.c#L306">306</a>         <a href="ident?i=hash">hash</a> = <a href="ident?i=fib_info_hashfn">fib_info_hashfn</a>(nfi);
<a name="L307" href="source/net/ipv4/fib_semantics.c#L307">307</a>         <a href="ident?i=head">head</a> = &amp;<a href="ident?i=fib_info_hash">fib_info_hash</a>[<a href="ident?i=hash">hash</a>];
<a name="L308" href="source/net/ipv4/fib_semantics.c#L308">308</a> 
<a name="L309" href="source/net/ipv4/fib_semantics.c#L309">309</a>         <a href="ident?i=hlist_for_each_entry">hlist_for_each_entry</a>(fi, <a href="ident?i=head">head</a>, fib_hash) {
<a name="L310" href="source/net/ipv4/fib_semantics.c#L310">310</a>                 if (!<a href="ident?i=net_eq">net_eq</a>(fi-&gt;fib_net, nfi-&gt;fib_net))
<a name="L311" href="source/net/ipv4/fib_semantics.c#L311">311</a>                         continue;
<a name="L312" href="source/net/ipv4/fib_semantics.c#L312">312</a>                 if (fi-&gt;fib_nhs != nfi-&gt;fib_nhs)
<a name="L313" href="source/net/ipv4/fib_semantics.c#L313">313</a>                         continue;
<a name="L314" href="source/net/ipv4/fib_semantics.c#L314">314</a>                 if (nfi-&gt;fib_protocol == fi-&gt;fib_protocol &amp;&amp;
<a name="L315" href="source/net/ipv4/fib_semantics.c#L315">315</a>                     nfi-&gt;fib_scope == fi-&gt;fib_scope &amp;&amp;
<a name="L316" href="source/net/ipv4/fib_semantics.c#L316">316</a>                     nfi-&gt;fib_prefsrc == fi-&gt;fib_prefsrc &amp;&amp;
<a name="L317" href="source/net/ipv4/fib_semantics.c#L317">317</a>                     nfi-&gt;fib_priority == fi-&gt;fib_priority &amp;&amp;
<a name="L318" href="source/net/ipv4/fib_semantics.c#L318">318</a>                     nfi-&gt;fib_type == fi-&gt;fib_type &amp;&amp;
<a name="L319" href="source/net/ipv4/fib_semantics.c#L319">319</a>                     <a href="ident?i=memcmp">memcmp</a>(nfi-&gt;fib_metrics, fi-&gt;fib_metrics,
<a name="L320" href="source/net/ipv4/fib_semantics.c#L320">320</a>                            sizeof(<a href="ident?i=u32">u32</a>) * <a href="ident?i=RTAX_MAX">RTAX_MAX</a>) == 0 &amp;&amp;
<a name="L321" href="source/net/ipv4/fib_semantics.c#L321">321</a>                     ((nfi-&gt;fib_flags ^ fi-&gt;fib_flags) &amp; ~RTNH_F_DEAD) == 0 &amp;&amp;
<a name="L322" href="source/net/ipv4/fib_semantics.c#L322">322</a>                     (nfi-&gt;fib_nhs == 0 || <a href="ident?i=nh_comp">nh_comp</a>(fi, nfi) == 0))
<a name="L323" href="source/net/ipv4/fib_semantics.c#L323">323</a>                         return fi;
<a name="L324" href="source/net/ipv4/fib_semantics.c#L324">324</a>         }
<a name="L325" href="source/net/ipv4/fib_semantics.c#L325">325</a> 
<a name="L326" href="source/net/ipv4/fib_semantics.c#L326">326</a>         return <a href="ident?i=NULL">NULL</a>;
<a name="L327" href="source/net/ipv4/fib_semantics.c#L327">327</a> }
<a name="L328" href="source/net/ipv4/fib_semantics.c#L328">328</a> 
<a name="L329" href="source/net/ipv4/fib_semantics.c#L329">329</a> <b><i>/* Check, that the gateway is already configured.</i></b>
<a name="L330" href="source/net/ipv4/fib_semantics.c#L330">330</a> <b><i> * Used only by redirect accept routine.</i></b>
<a name="L331" href="source/net/ipv4/fib_semantics.c#L331">331</a> <b><i> */</i></b>
<a name="L332" href="source/net/ipv4/fib_semantics.c#L332">332</a> int <a href="ident?i=ip_fib_check_default">ip_fib_check_default</a>(<a href="ident?i=__be32">__be32</a> gw, struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>)
<a name="L333" href="source/net/ipv4/fib_semantics.c#L333">333</a> {
<a name="L334" href="source/net/ipv4/fib_semantics.c#L334">334</a>         struct <a href="ident?i=hlist_head">hlist_head</a> *<a href="ident?i=head">head</a>;
<a name="L335" href="source/net/ipv4/fib_semantics.c#L335">335</a>         struct <a href="ident?i=fib_nh">fib_nh</a> *nh;
<a name="L336" href="source/net/ipv4/fib_semantics.c#L336">336</a>         unsigned int <a href="ident?i=hash">hash</a>;
<a name="L337" href="source/net/ipv4/fib_semantics.c#L337">337</a> 
<a name="L338" href="source/net/ipv4/fib_semantics.c#L338">338</a>         <a href="ident?i=spin_lock">spin_lock</a>(&amp;fib_info_lock);
<a name="L339" href="source/net/ipv4/fib_semantics.c#L339">339</a> 
<a name="L340" href="source/net/ipv4/fib_semantics.c#L340">340</a>         <a href="ident?i=hash">hash</a> = <a href="ident?i=fib_devindex_hashfn">fib_devindex_hashfn</a>(<a href="ident?i=dev">dev</a>-&gt;ifindex);
<a name="L341" href="source/net/ipv4/fib_semantics.c#L341">341</a>         <a href="ident?i=head">head</a> = &amp;<a href="ident?i=fib_info_devhash">fib_info_devhash</a>[<a href="ident?i=hash">hash</a>];
<a name="L342" href="source/net/ipv4/fib_semantics.c#L342">342</a>         <a href="ident?i=hlist_for_each_entry">hlist_for_each_entry</a>(nh, <a href="ident?i=head">head</a>, nh_hash) {
<a name="L343" href="source/net/ipv4/fib_semantics.c#L343">343</a>                 if (nh-&gt;nh_dev == <a href="ident?i=dev">dev</a> &amp;&amp;
<a name="L344" href="source/net/ipv4/fib_semantics.c#L344">344</a>                     nh-&gt;nh_gw == gw &amp;&amp;
<a name="L345" href="source/net/ipv4/fib_semantics.c#L345">345</a>                     !(nh-&gt;nh_flags &amp; <a href="ident?i=RTNH_F_DEAD">RTNH_F_DEAD</a>)) {
<a name="L346" href="source/net/ipv4/fib_semantics.c#L346">346</a>                         <a href="ident?i=spin_unlock">spin_unlock</a>(&amp;fib_info_lock);
<a name="L347" href="source/net/ipv4/fib_semantics.c#L347">347</a>                         return 0;
<a name="L348" href="source/net/ipv4/fib_semantics.c#L348">348</a>                 }
<a name="L349" href="source/net/ipv4/fib_semantics.c#L349">349</a>         }
<a name="L350" href="source/net/ipv4/fib_semantics.c#L350">350</a> 
<a name="L351" href="source/net/ipv4/fib_semantics.c#L351">351</a>         <a href="ident?i=spin_unlock">spin_unlock</a>(&amp;fib_info_lock);
<a name="L352" href="source/net/ipv4/fib_semantics.c#L352">352</a> 
<a name="L353" href="source/net/ipv4/fib_semantics.c#L353">353</a>         return -1;
<a name="L354" href="source/net/ipv4/fib_semantics.c#L354">354</a> }
<a name="L355" href="source/net/ipv4/fib_semantics.c#L355">355</a> 
<a name="L356" href="source/net/ipv4/fib_semantics.c#L356">356</a> static inline <a href="ident?i=size_t">size_t</a> <a href="ident?i=fib_nlmsg_size">fib_nlmsg_size</a>(struct <a href="ident?i=fib_info">fib_info</a> *fi)
<a name="L357" href="source/net/ipv4/fib_semantics.c#L357">357</a> {
<a name="L358" href="source/net/ipv4/fib_semantics.c#L358">358</a>         <a href="ident?i=size_t">size_t</a> <a href="ident?i=payload">payload</a> = <a href="ident?i=NLMSG_ALIGN">NLMSG_ALIGN</a>(sizeof(struct <a href="ident?i=rtmsg">rtmsg</a>))
<a name="L359" href="source/net/ipv4/fib_semantics.c#L359">359</a>                          + <a href="ident?i=nla_total_size">nla_total_size</a>(4) <b><i>/* RTA_TABLE */</i></b>
<a name="L360" href="source/net/ipv4/fib_semantics.c#L360">360</a>                          + <a href="ident?i=nla_total_size">nla_total_size</a>(4) <b><i>/* RTA_DST */</i></b>
<a name="L361" href="source/net/ipv4/fib_semantics.c#L361">361</a>                          + <a href="ident?i=nla_total_size">nla_total_size</a>(4) <b><i>/* RTA_PRIORITY */</i></b>
<a name="L362" href="source/net/ipv4/fib_semantics.c#L362">362</a>                          + <a href="ident?i=nla_total_size">nla_total_size</a>(4) <b><i>/* RTA_PREFSRC */</i></b>
<a name="L363" href="source/net/ipv4/fib_semantics.c#L363">363</a>                          + <a href="ident?i=nla_total_size">nla_total_size</a>(<a href="ident?i=TCP_CA_NAME_MAX">TCP_CA_NAME_MAX</a>); <b><i>/* RTAX_CC_ALGO */</i></b>
<a name="L364" href="source/net/ipv4/fib_semantics.c#L364">364</a> 
<a name="L365" href="source/net/ipv4/fib_semantics.c#L365">365</a>         <b><i>/* space for nested metrics */</i></b>
<a name="L366" href="source/net/ipv4/fib_semantics.c#L366">366</a>         <a href="ident?i=payload">payload</a> += <a href="ident?i=nla_total_size">nla_total_size</a>((<a href="ident?i=RTAX_MAX">RTAX_MAX</a> * <a href="ident?i=nla_total_size">nla_total_size</a>(4)));
<a name="L367" href="source/net/ipv4/fib_semantics.c#L367">367</a> 
<a name="L368" href="source/net/ipv4/fib_semantics.c#L368">368</a>         if (fi-&gt;fib_nhs) {
<a name="L369" href="source/net/ipv4/fib_semantics.c#L369">369</a>                 <b><i>/* Also handles the special case fib_nhs == 1 */</i></b>
<a name="L370" href="source/net/ipv4/fib_semantics.c#L370">370</a> 
<a name="L371" href="source/net/ipv4/fib_semantics.c#L371">371</a>                 <b><i>/* each nexthop is packed in an attribute */</i></b>
<a name="L372" href="source/net/ipv4/fib_semantics.c#L372">372</a>                 <a href="ident?i=size_t">size_t</a> nhsize = <a href="ident?i=nla_total_size">nla_total_size</a>(sizeof(struct <a href="ident?i=rtnexthop">rtnexthop</a>));
<a name="L373" href="source/net/ipv4/fib_semantics.c#L373">373</a> 
<a name="L374" href="source/net/ipv4/fib_semantics.c#L374">374</a>                 <b><i>/* may contain flow and gateway attribute */</i></b>
<a name="L375" href="source/net/ipv4/fib_semantics.c#L375">375</a>                 nhsize += 2 * <a href="ident?i=nla_total_size">nla_total_size</a>(4);
<a name="L376" href="source/net/ipv4/fib_semantics.c#L376">376</a> 
<a name="L377" href="source/net/ipv4/fib_semantics.c#L377">377</a>                 <b><i>/* all nexthops are packed in a nested attribute */</i></b>
<a name="L378" href="source/net/ipv4/fib_semantics.c#L378">378</a>                 <a href="ident?i=payload">payload</a> += <a href="ident?i=nla_total_size">nla_total_size</a>(fi-&gt;fib_nhs * nhsize);
<a name="L379" href="source/net/ipv4/fib_semantics.c#L379">379</a>         }
<a name="L380" href="source/net/ipv4/fib_semantics.c#L380">380</a> 
<a name="L381" href="source/net/ipv4/fib_semantics.c#L381">381</a>         return <a href="ident?i=payload">payload</a>;
<a name="L382" href="source/net/ipv4/fib_semantics.c#L382">382</a> }
<a name="L383" href="source/net/ipv4/fib_semantics.c#L383">383</a> 
<a name="L384" href="source/net/ipv4/fib_semantics.c#L384">384</a> void <a href="ident?i=rtmsg_fib">rtmsg_fib</a>(int <a href="ident?i=event">event</a>, <a href="ident?i=__be32">__be32</a> <a href="ident?i=key">key</a>, struct <a href="ident?i=fib_alias">fib_alias</a> *fa,
<a name="L385" href="source/net/ipv4/fib_semantics.c#L385">385</a>                int dst_len, <a href="ident?i=u32">u32</a> tb_id, const struct <a href="ident?i=nl_info">nl_info</a> *<a href="ident?i=info">info</a>,
<a name="L386" href="source/net/ipv4/fib_semantics.c#L386">386</a>                unsigned int nlm_flags)
<a name="L387" href="source/net/ipv4/fib_semantics.c#L387">387</a> {
<a name="L388" href="source/net/ipv4/fib_semantics.c#L388">388</a>         struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>;
<a name="L389" href="source/net/ipv4/fib_semantics.c#L389">389</a>         <a href="ident?i=u32">u32</a> <a href="ident?i=seq">seq</a> = <a href="ident?i=info">info</a>-&gt;nlh ? <a href="ident?i=info">info</a>-&gt;nlh-&gt;nlmsg_seq : 0;
<a name="L390" href="source/net/ipv4/fib_semantics.c#L390">390</a>         int <a href="ident?i=err">err</a> = -<a href="ident?i=ENOBUFS">ENOBUFS</a>;
<a name="L391" href="source/net/ipv4/fib_semantics.c#L391">391</a> 
<a name="L392" href="source/net/ipv4/fib_semantics.c#L392">392</a>         <a href="ident?i=skb">skb</a> = <a href="ident?i=nlmsg_new">nlmsg_new</a>(<a href="ident?i=fib_nlmsg_size">fib_nlmsg_size</a>(fa-&gt;fa_info), <a href="ident?i=GFP_KERNEL">GFP_KERNEL</a>);
<a name="L393" href="source/net/ipv4/fib_semantics.c#L393">393</a>         if (!<a href="ident?i=skb">skb</a>)
<a name="L394" href="source/net/ipv4/fib_semantics.c#L394">394</a>                 goto errout;
<a name="L395" href="source/net/ipv4/fib_semantics.c#L395">395</a> 
<a name="L396" href="source/net/ipv4/fib_semantics.c#L396">396</a>         <a href="ident?i=err">err</a> = <a href="ident?i=fib_dump_info">fib_dump_info</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=info">info</a>-&gt;portid, <a href="ident?i=seq">seq</a>, <a href="ident?i=event">event</a>, tb_id,
<a name="L397" href="source/net/ipv4/fib_semantics.c#L397">397</a>                             fa-&gt;fa_type, <a href="ident?i=key">key</a>, dst_len,
<a name="L398" href="source/net/ipv4/fib_semantics.c#L398">398</a>                             fa-&gt;fa_tos, fa-&gt;fa_info, nlm_flags);
<a name="L399" href="source/net/ipv4/fib_semantics.c#L399">399</a>         if (<a href="ident?i=err">err</a> &lt; 0) {
<a name="L400" href="source/net/ipv4/fib_semantics.c#L400">400</a>                 <b><i>/* -EMSGSIZE implies BUG in fib_nlmsg_size() */</i></b>
<a name="L401" href="source/net/ipv4/fib_semantics.c#L401">401</a>                 <a href="ident?i=WARN_ON">WARN_ON</a>(<a href="ident?i=err">err</a> == -<a href="ident?i=EMSGSIZE">EMSGSIZE</a>);
<a name="L402" href="source/net/ipv4/fib_semantics.c#L402">402</a>                 <a href="ident?i=kfree_skb">kfree_skb</a>(<a href="ident?i=skb">skb</a>);
<a name="L403" href="source/net/ipv4/fib_semantics.c#L403">403</a>                 goto errout;
<a name="L404" href="source/net/ipv4/fib_semantics.c#L404">404</a>         }
<a name="L405" href="source/net/ipv4/fib_semantics.c#L405">405</a>         <a href="ident?i=rtnl_notify">rtnl_notify</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=info">info</a>-&gt;nl_net, <a href="ident?i=info">info</a>-&gt;portid, <a href="ident?i=RTNLGRP_IPV4_ROUTE">RTNLGRP_IPV4_ROUTE</a>,
<a name="L406" href="source/net/ipv4/fib_semantics.c#L406">406</a>                     <a href="ident?i=info">info</a>-&gt;nlh, <a href="ident?i=GFP_KERNEL">GFP_KERNEL</a>);
<a name="L407" href="source/net/ipv4/fib_semantics.c#L407">407</a>         return;
<a name="L408" href="source/net/ipv4/fib_semantics.c#L408">408</a> errout:
<a name="L409" href="source/net/ipv4/fib_semantics.c#L409">409</a>         if (<a href="ident?i=err">err</a> &lt; 0)
<a name="L410" href="source/net/ipv4/fib_semantics.c#L410">410</a>                 <a href="ident?i=rtnl_set_sk_err">rtnl_set_sk_err</a>(<a href="ident?i=info">info</a>-&gt;nl_net, <a href="ident?i=RTNLGRP_IPV4_ROUTE">RTNLGRP_IPV4_ROUTE</a>, <a href="ident?i=err">err</a>);
<a name="L411" href="source/net/ipv4/fib_semantics.c#L411">411</a> }
<a name="L412" href="source/net/ipv4/fib_semantics.c#L412">412</a> 
<a name="L413" href="source/net/ipv4/fib_semantics.c#L413">413</a> static int <a href="ident?i=fib_detect_death">fib_detect_death</a>(struct <a href="ident?i=fib_info">fib_info</a> *fi, int order,
<a name="L414" href="source/net/ipv4/fib_semantics.c#L414">414</a>                             struct <a href="ident?i=fib_info">fib_info</a> **last_resort, int *last_idx,
<a name="L415" href="source/net/ipv4/fib_semantics.c#L415">415</a>                             int <a href="ident?i=dflt">dflt</a>)
<a name="L416" href="source/net/ipv4/fib_semantics.c#L416">416</a> {
<a name="L417" href="source/net/ipv4/fib_semantics.c#L417">417</a>         struct <a href="ident?i=neighbour">neighbour</a> *<a href="ident?i=n">n</a>;
<a name="L418" href="source/net/ipv4/fib_semantics.c#L418">418</a>         int <a href="ident?i=state">state</a> = <a href="ident?i=NUD_NONE">NUD_NONE</a>;
<a name="L419" href="source/net/ipv4/fib_semantics.c#L419">419</a> 
<a name="L420" href="source/net/ipv4/fib_semantics.c#L420">420</a>         <a href="ident?i=n">n</a> = <a href="ident?i=neigh_lookup">neigh_lookup</a>(&amp;<a href="ident?i=arp_tbl">arp_tbl</a>, &amp;fi-&gt;<a href="ident?i=fib_nh">fib_nh</a>[0].nh_gw, fi-&gt;<a href="ident?i=fib_dev">fib_dev</a>);
<a name="L421" href="source/net/ipv4/fib_semantics.c#L421">421</a>         if (<a href="ident?i=n">n</a>) {
<a name="L422" href="source/net/ipv4/fib_semantics.c#L422">422</a>                 <a href="ident?i=state">state</a> = <a href="ident?i=n">n</a>-&gt;nud_state;
<a name="L423" href="source/net/ipv4/fib_semantics.c#L423">423</a>                 <a href="ident?i=neigh_release">neigh_release</a>(<a href="ident?i=n">n</a>);
<a name="L424" href="source/net/ipv4/fib_semantics.c#L424">424</a>         }
<a name="L425" href="source/net/ipv4/fib_semantics.c#L425">425</a>         if (<a href="ident?i=state">state</a> == <a href="ident?i=NUD_REACHABLE">NUD_REACHABLE</a>)
<a name="L426" href="source/net/ipv4/fib_semantics.c#L426">426</a>                 return 0;
<a name="L427" href="source/net/ipv4/fib_semantics.c#L427">427</a>         if ((<a href="ident?i=state">state</a> &amp; <a href="ident?i=NUD_VALID">NUD_VALID</a>) &amp;&amp; order != <a href="ident?i=dflt">dflt</a>)
<a name="L428" href="source/net/ipv4/fib_semantics.c#L428">428</a>                 return 0;
<a name="L429" href="source/net/ipv4/fib_semantics.c#L429">429</a>         if ((<a href="ident?i=state">state</a> &amp; <a href="ident?i=NUD_VALID">NUD_VALID</a>) ||
<a name="L430" href="source/net/ipv4/fib_semantics.c#L430">430</a>             (*last_idx &lt; 0 &amp;&amp; order &gt; <a href="ident?i=dflt">dflt</a>)) {
<a name="L431" href="source/net/ipv4/fib_semantics.c#L431">431</a>                 *last_resort = fi;
<a name="L432" href="source/net/ipv4/fib_semantics.c#L432">432</a>                 *last_idx = order;
<a name="L433" href="source/net/ipv4/fib_semantics.c#L433">433</a>         }
<a name="L434" href="source/net/ipv4/fib_semantics.c#L434">434</a>         return 1;
<a name="L435" href="source/net/ipv4/fib_semantics.c#L435">435</a> }
<a name="L436" href="source/net/ipv4/fib_semantics.c#L436">436</a> 
<a name="L437" href="source/net/ipv4/fib_semantics.c#L437">437</a> #ifdef CONFIG_IP_ROUTE_MULTIPATH
<a name="L438" href="source/net/ipv4/fib_semantics.c#L438">438</a> 
<a name="L439" href="source/net/ipv4/fib_semantics.c#L439">439</a> static int <a href="ident?i=fib_count_nexthops">fib_count_nexthops</a>(struct <a href="ident?i=rtnexthop">rtnexthop</a> *rtnh, int <a href="ident?i=remaining">remaining</a>)
<a name="L440" href="source/net/ipv4/fib_semantics.c#L440">440</a> {
<a name="L441" href="source/net/ipv4/fib_semantics.c#L441">441</a>         int nhs = 0;
<a name="L442" href="source/net/ipv4/fib_semantics.c#L442">442</a> 
<a name="L443" href="source/net/ipv4/fib_semantics.c#L443">443</a>         while (<a href="ident?i=rtnh_ok">rtnh_ok</a>(rtnh, <a href="ident?i=remaining">remaining</a>)) {
<a name="L444" href="source/net/ipv4/fib_semantics.c#L444">444</a>                 nhs++;
<a name="L445" href="source/net/ipv4/fib_semantics.c#L445">445</a>                 rtnh = <a href="ident?i=rtnh_next">rtnh_next</a>(rtnh, &amp;<a href="ident?i=remaining">remaining</a>);
<a name="L446" href="source/net/ipv4/fib_semantics.c#L446">446</a>         }
<a name="L447" href="source/net/ipv4/fib_semantics.c#L447">447</a> 
<a name="L448" href="source/net/ipv4/fib_semantics.c#L448">448</a>         <b><i>/* leftover implies invalid nexthop configuration, discard it */</i></b>
<a name="L449" href="source/net/ipv4/fib_semantics.c#L449">449</a>         return <a href="ident?i=remaining">remaining</a> &gt; 0 ? 0 : nhs;
<a name="L450" href="source/net/ipv4/fib_semantics.c#L450">450</a> }
<a name="L451" href="source/net/ipv4/fib_semantics.c#L451">451</a> 
<a name="L452" href="source/net/ipv4/fib_semantics.c#L452">452</a> static int <a href="ident?i=fib_get_nhs">fib_get_nhs</a>(struct <a href="ident?i=fib_info">fib_info</a> *fi, struct <a href="ident?i=rtnexthop">rtnexthop</a> *rtnh,
<a name="L453" href="source/net/ipv4/fib_semantics.c#L453">453</a>                        int <a href="ident?i=remaining">remaining</a>, struct <a href="ident?i=fib_config">fib_config</a> *<a href="ident?i=cfg">cfg</a>)
<a name="L454" href="source/net/ipv4/fib_semantics.c#L454">454</a> {
<a name="L455" href="source/net/ipv4/fib_semantics.c#L455">455</a>         <a href="ident?i=change_nexthops">change_nexthops</a>(fi) {
<a name="L456" href="source/net/ipv4/fib_semantics.c#L456">456</a>                 int attrlen;
<a name="L457" href="source/net/ipv4/fib_semantics.c#L457">457</a> 
<a name="L458" href="source/net/ipv4/fib_semantics.c#L458">458</a>                 if (!<a href="ident?i=rtnh_ok">rtnh_ok</a>(rtnh, <a href="ident?i=remaining">remaining</a>))
<a name="L459" href="source/net/ipv4/fib_semantics.c#L459">459</a>                         return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L460" href="source/net/ipv4/fib_semantics.c#L460">460</a> 
<a name="L461" href="source/net/ipv4/fib_semantics.c#L461">461</a>                 nexthop_nh-&gt;nh_flags =
<a name="L462" href="source/net/ipv4/fib_semantics.c#L462">462</a>                         (<a href="ident?i=cfg">cfg</a>-&gt;fc_flags &amp; ~0xFF) | rtnh-&gt;rtnh_flags;
<a name="L463" href="source/net/ipv4/fib_semantics.c#L463">463</a>                 nexthop_nh-&gt;nh_oif = rtnh-&gt;rtnh_ifindex;
<a name="L464" href="source/net/ipv4/fib_semantics.c#L464">464</a>                 nexthop_nh-&gt;nh_weight = rtnh-&gt;rtnh_hops + 1;
<a name="L465" href="source/net/ipv4/fib_semantics.c#L465">465</a> 
<a name="L466" href="source/net/ipv4/fib_semantics.c#L466">466</a>                 attrlen = <a href="ident?i=rtnh_attrlen">rtnh_attrlen</a>(rtnh);
<a name="L467" href="source/net/ipv4/fib_semantics.c#L467">467</a>                 if (attrlen &gt; 0) {
<a name="L468" href="source/net/ipv4/fib_semantics.c#L468">468</a>                         struct <a href="ident?i=nlattr">nlattr</a> *nla, *<a href="ident?i=attrs">attrs</a> = <a href="ident?i=rtnh_attrs">rtnh_attrs</a>(rtnh);
<a name="L469" href="source/net/ipv4/fib_semantics.c#L469">469</a> 
<a name="L470" href="source/net/ipv4/fib_semantics.c#L470">470</a>                         nla = <a href="ident?i=nla_find">nla_find</a>(<a href="ident?i=attrs">attrs</a>, attrlen, RTA_GATEWAY);
<a name="L471" href="source/net/ipv4/fib_semantics.c#L471">471</a>                         nexthop_nh-&gt;nh_gw = nla ? <a href="ident?i=nla_get_in_addr">nla_get_in_addr</a>(nla) : 0;
<a name="L472" href="source/net/ipv4/fib_semantics.c#L472">472</a> #ifdef CONFIG_IP_ROUTE_CLASSID
<a name="L473" href="source/net/ipv4/fib_semantics.c#L473">473</a>                         nla = <a href="ident?i=nla_find">nla_find</a>(<a href="ident?i=attrs">attrs</a>, attrlen, RTA_FLOW);
<a name="L474" href="source/net/ipv4/fib_semantics.c#L474">474</a>                         nexthop_nh-&gt;nh_tclassid = nla ? <a href="ident?i=nla_get_u32">nla_get_u32</a>(nla) : 0;
<a name="L475" href="source/net/ipv4/fib_semantics.c#L475">475</a>                         if (nexthop_nh-&gt;nh_tclassid)
<a name="L476" href="source/net/ipv4/fib_semantics.c#L476">476</a>                                 fi-&gt;fib_net-&gt;ipv4.<a href="ident?i=fib_num_tclassid_users">fib_num_tclassid_users</a>++;
<a name="L477" href="source/net/ipv4/fib_semantics.c#L477">477</a> #endif
<a name="L478" href="source/net/ipv4/fib_semantics.c#L478">478</a>                 }
<a name="L479" href="source/net/ipv4/fib_semantics.c#L479">479</a> 
<a name="L480" href="source/net/ipv4/fib_semantics.c#L480">480</a>                 rtnh = <a href="ident?i=rtnh_next">rtnh_next</a>(rtnh, &amp;<a href="ident?i=remaining">remaining</a>);
<a name="L481" href="source/net/ipv4/fib_semantics.c#L481">481</a>         } <a href="ident?i=endfor_nexthops">endfor_nexthops</a>(fi);
<a name="L482" href="source/net/ipv4/fib_semantics.c#L482">482</a> 
<a name="L483" href="source/net/ipv4/fib_semantics.c#L483">483</a>         return 0;
<a name="L484" href="source/net/ipv4/fib_semantics.c#L484">484</a> }
<a name="L485" href="source/net/ipv4/fib_semantics.c#L485">485</a> 
<a name="L486" href="source/net/ipv4/fib_semantics.c#L486">486</a> #endif
<a name="L487" href="source/net/ipv4/fib_semantics.c#L487">487</a> 
<a name="L488" href="source/net/ipv4/fib_semantics.c#L488">488</a> int <a href="ident?i=fib_nh_match">fib_nh_match</a>(struct <a href="ident?i=fib_config">fib_config</a> *<a href="ident?i=cfg">cfg</a>, struct <a href="ident?i=fib_info">fib_info</a> *fi)
<a name="L489" href="source/net/ipv4/fib_semantics.c#L489">489</a> {
<a name="L490" href="source/net/ipv4/fib_semantics.c#L490">490</a> #ifdef CONFIG_IP_ROUTE_MULTIPATH
<a name="L491" href="source/net/ipv4/fib_semantics.c#L491">491</a>         struct <a href="ident?i=rtnexthop">rtnexthop</a> *rtnh;
<a name="L492" href="source/net/ipv4/fib_semantics.c#L492">492</a>         int <a href="ident?i=remaining">remaining</a>;
<a name="L493" href="source/net/ipv4/fib_semantics.c#L493">493</a> #endif
<a name="L494" href="source/net/ipv4/fib_semantics.c#L494">494</a> 
<a name="L495" href="source/net/ipv4/fib_semantics.c#L495">495</a>         if (<a href="ident?i=cfg">cfg</a>-&gt;fc_priority &amp;&amp; <a href="ident?i=cfg">cfg</a>-&gt;fc_priority != fi-&gt;fib_priority)
<a name="L496" href="source/net/ipv4/fib_semantics.c#L496">496</a>                 return 1;
<a name="L497" href="source/net/ipv4/fib_semantics.c#L497">497</a> 
<a name="L498" href="source/net/ipv4/fib_semantics.c#L498">498</a>         if (<a href="ident?i=cfg">cfg</a>-&gt;fc_oif || <a href="ident?i=cfg">cfg</a>-&gt;fc_gw) {
<a name="L499" href="source/net/ipv4/fib_semantics.c#L499">499</a>                 if ((!<a href="ident?i=cfg">cfg</a>-&gt;fc_oif || <a href="ident?i=cfg">cfg</a>-&gt;fc_oif == fi-&gt;<a href="ident?i=fib_nh">fib_nh</a>-&gt;nh_oif) &amp;&amp;
<a name="L500" href="source/net/ipv4/fib_semantics.c#L500">500</a>                     (!<a href="ident?i=cfg">cfg</a>-&gt;fc_gw  || <a href="ident?i=cfg">cfg</a>-&gt;fc_gw == fi-&gt;<a href="ident?i=fib_nh">fib_nh</a>-&gt;nh_gw))
<a name="L501" href="source/net/ipv4/fib_semantics.c#L501">501</a>                         return 0;
<a name="L502" href="source/net/ipv4/fib_semantics.c#L502">502</a>                 return 1;
<a name="L503" href="source/net/ipv4/fib_semantics.c#L503">503</a>         }
<a name="L504" href="source/net/ipv4/fib_semantics.c#L504">504</a> 
<a name="L505" href="source/net/ipv4/fib_semantics.c#L505">505</a> #ifdef CONFIG_IP_ROUTE_MULTIPATH
<a name="L506" href="source/net/ipv4/fib_semantics.c#L506">506</a>         if (!<a href="ident?i=cfg">cfg</a>-&gt;fc_mp)
<a name="L507" href="source/net/ipv4/fib_semantics.c#L507">507</a>                 return 0;
<a name="L508" href="source/net/ipv4/fib_semantics.c#L508">508</a> 
<a name="L509" href="source/net/ipv4/fib_semantics.c#L509">509</a>         rtnh = <a href="ident?i=cfg">cfg</a>-&gt;fc_mp;
<a name="L510" href="source/net/ipv4/fib_semantics.c#L510">510</a>         <a href="ident?i=remaining">remaining</a> = <a href="ident?i=cfg">cfg</a>-&gt;fc_mp_len;
<a name="L511" href="source/net/ipv4/fib_semantics.c#L511">511</a> 
<a name="L512" href="source/net/ipv4/fib_semantics.c#L512">512</a>         <a href="ident?i=for_nexthops">for_nexthops</a>(fi) {
<a name="L513" href="source/net/ipv4/fib_semantics.c#L513">513</a>                 int attrlen;
<a name="L514" href="source/net/ipv4/fib_semantics.c#L514">514</a> 
<a name="L515" href="source/net/ipv4/fib_semantics.c#L515">515</a>                 if (!<a href="ident?i=rtnh_ok">rtnh_ok</a>(rtnh, <a href="ident?i=remaining">remaining</a>))
<a name="L516" href="source/net/ipv4/fib_semantics.c#L516">516</a>                         return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L517" href="source/net/ipv4/fib_semantics.c#L517">517</a> 
<a name="L518" href="source/net/ipv4/fib_semantics.c#L518">518</a>                 if (rtnh-&gt;rtnh_ifindex &amp;&amp; rtnh-&gt;rtnh_ifindex != nh-&gt;nh_oif)
<a name="L519" href="source/net/ipv4/fib_semantics.c#L519">519</a>                         return 1;
<a name="L520" href="source/net/ipv4/fib_semantics.c#L520">520</a> 
<a name="L521" href="source/net/ipv4/fib_semantics.c#L521">521</a>                 attrlen = <a href="ident?i=rtnh_attrlen">rtnh_attrlen</a>(rtnh);
<a name="L522" href="source/net/ipv4/fib_semantics.c#L522">522</a>                 if (attrlen &gt; 0) {
<a name="L523" href="source/net/ipv4/fib_semantics.c#L523">523</a>                         struct <a href="ident?i=nlattr">nlattr</a> *nla, *<a href="ident?i=attrs">attrs</a> = <a href="ident?i=rtnh_attrs">rtnh_attrs</a>(rtnh);
<a name="L524" href="source/net/ipv4/fib_semantics.c#L524">524</a> 
<a name="L525" href="source/net/ipv4/fib_semantics.c#L525">525</a>                         nla = <a href="ident?i=nla_find">nla_find</a>(<a href="ident?i=attrs">attrs</a>, attrlen, RTA_GATEWAY);
<a name="L526" href="source/net/ipv4/fib_semantics.c#L526">526</a>                         if (nla &amp;&amp; <a href="ident?i=nla_get_in_addr">nla_get_in_addr</a>(nla) != nh-&gt;nh_gw)
<a name="L527" href="source/net/ipv4/fib_semantics.c#L527">527</a>                                 return 1;
<a name="L528" href="source/net/ipv4/fib_semantics.c#L528">528</a> #ifdef CONFIG_IP_ROUTE_CLASSID
<a name="L529" href="source/net/ipv4/fib_semantics.c#L529">529</a>                         nla = <a href="ident?i=nla_find">nla_find</a>(<a href="ident?i=attrs">attrs</a>, attrlen, RTA_FLOW);
<a name="L530" href="source/net/ipv4/fib_semantics.c#L530">530</a>                         if (nla &amp;&amp; <a href="ident?i=nla_get_u32">nla_get_u32</a>(nla) != nh-&gt;nh_tclassid)
<a name="L531" href="source/net/ipv4/fib_semantics.c#L531">531</a>                                 return 1;
<a name="L532" href="source/net/ipv4/fib_semantics.c#L532">532</a> #endif
<a name="L533" href="source/net/ipv4/fib_semantics.c#L533">533</a>                 }
<a name="L534" href="source/net/ipv4/fib_semantics.c#L534">534</a> 
<a name="L535" href="source/net/ipv4/fib_semantics.c#L535">535</a>                 rtnh = <a href="ident?i=rtnh_next">rtnh_next</a>(rtnh, &amp;<a href="ident?i=remaining">remaining</a>);
<a name="L536" href="source/net/ipv4/fib_semantics.c#L536">536</a>         } <a href="ident?i=endfor_nexthops">endfor_nexthops</a>(fi);
<a name="L537" href="source/net/ipv4/fib_semantics.c#L537">537</a> #endif
<a name="L538" href="source/net/ipv4/fib_semantics.c#L538">538</a>         return 0;
<a name="L539" href="source/net/ipv4/fib_semantics.c#L539">539</a> }
<a name="L540" href="source/net/ipv4/fib_semantics.c#L540">540</a> 
<a name="L541" href="source/net/ipv4/fib_semantics.c#L541">541</a> 
<a name="L542" href="source/net/ipv4/fib_semantics.c#L542">542</a> <b><i>/*</i></b>
<a name="L543" href="source/net/ipv4/fib_semantics.c#L543">543</a> <b><i> * Picture</i></b>
<a name="L544" href="source/net/ipv4/fib_semantics.c#L544">544</a> <b><i> * -------</i></b>
<a name="L545" href="source/net/ipv4/fib_semantics.c#L545">545</a> <b><i> *</i></b>
<a name="L546" href="source/net/ipv4/fib_semantics.c#L546">546</a> <b><i> * Semantics of nexthop is very messy by historical reasons.</i></b>
<a name="L547" href="source/net/ipv4/fib_semantics.c#L547">547</a> <b><i> * We have to take into account, that:</i></b>
<a name="L548" href="source/net/ipv4/fib_semantics.c#L548">548</a> <b><i> * a) gateway can be actually local interface address,</i></b>
<a name="L549" href="source/net/ipv4/fib_semantics.c#L549">549</a> <b><i> *    so that gatewayed route is direct.</i></b>
<a name="L550" href="source/net/ipv4/fib_semantics.c#L550">550</a> <b><i> * b) gateway must be on-link address, possibly</i></b>
<a name="L551" href="source/net/ipv4/fib_semantics.c#L551">551</a> <b><i> *    described not by an ifaddr, but also by a direct route.</i></b>
<a name="L552" href="source/net/ipv4/fib_semantics.c#L552">552</a> <b><i> * c) If both gateway and interface are specified, they should not</i></b>
<a name="L553" href="source/net/ipv4/fib_semantics.c#L553">553</a> <b><i> *    contradict.</i></b>
<a name="L554" href="source/net/ipv4/fib_semantics.c#L554">554</a> <b><i> * d) If we use tunnel routes, gateway could be not on-link.</i></b>
<a name="L555" href="source/net/ipv4/fib_semantics.c#L555">555</a> <b><i> *</i></b>
<a name="L556" href="source/net/ipv4/fib_semantics.c#L556">556</a> <b><i> * Attempt to reconcile all of these (alas, self-contradictory) conditions</i></b>
<a name="L557" href="source/net/ipv4/fib_semantics.c#L557">557</a> <b><i> * results in pretty ugly and hairy code with obscure logic.</i></b>
<a name="L558" href="source/net/ipv4/fib_semantics.c#L558">558</a> <b><i> *</i></b>
<a name="L559" href="source/net/ipv4/fib_semantics.c#L559">559</a> <b><i> * I chose to generalized it instead, so that the size</i></b>
<a name="L560" href="source/net/ipv4/fib_semantics.c#L560">560</a> <b><i> * of code does not increase practically, but it becomes</i></b>
<a name="L561" href="source/net/ipv4/fib_semantics.c#L561">561</a> <b><i> * much more general.</i></b>
<a name="L562" href="source/net/ipv4/fib_semantics.c#L562">562</a> <b><i> * Every prefix is assigned a "scope" value: "host" is local address,</i></b>
<a name="L563" href="source/net/ipv4/fib_semantics.c#L563">563</a> <b><i> * "link" is direct route,</i></b>
<a name="L564" href="source/net/ipv4/fib_semantics.c#L564">564</a> <b><i> * [ ... "site" ... "interior" ... ]</i></b>
<a name="L565" href="source/net/ipv4/fib_semantics.c#L565">565</a> <b><i> * and "universe" is true gateway route with global meaning.</i></b>
<a name="L566" href="source/net/ipv4/fib_semantics.c#L566">566</a> <b><i> *</i></b>
<a name="L567" href="source/net/ipv4/fib_semantics.c#L567">567</a> <b><i> * Every prefix refers to a set of "nexthop"s (gw, oif),</i></b>
<a name="L568" href="source/net/ipv4/fib_semantics.c#L568">568</a> <b><i> * where gw must have narrower scope. This recursion stops</i></b>
<a name="L569" href="source/net/ipv4/fib_semantics.c#L569">569</a> <b><i> * when gw has LOCAL scope or if "nexthop" is declared ONLINK,</i></b>
<a name="L570" href="source/net/ipv4/fib_semantics.c#L570">570</a> <b><i> * which means that gw is forced to be on link.</i></b>
<a name="L571" href="source/net/ipv4/fib_semantics.c#L571">571</a> <b><i> *</i></b>
<a name="L572" href="source/net/ipv4/fib_semantics.c#L572">572</a> <b><i> * Code is still hairy, but now it is apparently logically</i></b>
<a name="L573" href="source/net/ipv4/fib_semantics.c#L573">573</a> <b><i> * consistent and very flexible. F.e. as by-product it allows</i></b>
<a name="L574" href="source/net/ipv4/fib_semantics.c#L574">574</a> <b><i> * to co-exists in peace independent exterior and interior</i></b>
<a name="L575" href="source/net/ipv4/fib_semantics.c#L575">575</a> <b><i> * routing processes.</i></b>
<a name="L576" href="source/net/ipv4/fib_semantics.c#L576">576</a> <b><i> *</i></b>
<a name="L577" href="source/net/ipv4/fib_semantics.c#L577">577</a> <b><i> * Normally it looks as following.</i></b>
<a name="L578" href="source/net/ipv4/fib_semantics.c#L578">578</a> <b><i> *</i></b>
<a name="L579" href="source/net/ipv4/fib_semantics.c#L579">579</a> <b><i> * {universe prefix}  -&gt; (gw, oif) [scope link]</i></b>
<a name="L580" href="source/net/ipv4/fib_semantics.c#L580">580</a> <b><i> *                |</i></b>
<a name="L581" href="source/net/ipv4/fib_semantics.c#L581">581</a> <b><i> *                |-&gt; {link prefix} -&gt; (gw, oif) [scope local]</i></b>
<a name="L582" href="source/net/ipv4/fib_semantics.c#L582">582</a> <b><i> *                                      |</i></b>
<a name="L583" href="source/net/ipv4/fib_semantics.c#L583">583</a> <b><i> *                                      |-&gt; {local prefix} (terminal node)</i></b>
<a name="L584" href="source/net/ipv4/fib_semantics.c#L584">584</a> <b><i> */</i></b>
<a name="L585" href="source/net/ipv4/fib_semantics.c#L585">585</a> static int <a href="ident?i=fib_check_nh">fib_check_nh</a>(struct <a href="ident?i=fib_config">fib_config</a> *<a href="ident?i=cfg">cfg</a>, struct <a href="ident?i=fib_info">fib_info</a> *fi,
<a name="L586" href="source/net/ipv4/fib_semantics.c#L586">586</a>                         struct <a href="ident?i=fib_nh">fib_nh</a> *nh)
<a name="L587" href="source/net/ipv4/fib_semantics.c#L587">587</a> {
<a name="L588" href="source/net/ipv4/fib_semantics.c#L588">588</a>         int <a href="ident?i=err">err</a>;
<a name="L589" href="source/net/ipv4/fib_semantics.c#L589">589</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>;
<a name="L590" href="source/net/ipv4/fib_semantics.c#L590">590</a>         struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>;
<a name="L591" href="source/net/ipv4/fib_semantics.c#L591">591</a> 
<a name="L592" href="source/net/ipv4/fib_semantics.c#L592">592</a>         <a href="ident?i=net">net</a> = <a href="ident?i=cfg">cfg</a>-&gt;fc_nlinfo.nl_net;
<a name="L593" href="source/net/ipv4/fib_semantics.c#L593">593</a>         if (nh-&gt;nh_gw) {
<a name="L594" href="source/net/ipv4/fib_semantics.c#L594">594</a>                 struct <a href="ident?i=fib_result">fib_result</a> <a href="ident?i=res">res</a>;
<a name="L595" href="source/net/ipv4/fib_semantics.c#L595">595</a> 
<a name="L596" href="source/net/ipv4/fib_semantics.c#L596">596</a>                 if (nh-&gt;nh_flags &amp; <a href="ident?i=RTNH_F_ONLINK">RTNH_F_ONLINK</a>) {
<a name="L597" href="source/net/ipv4/fib_semantics.c#L597">597</a> 
<a name="L598" href="source/net/ipv4/fib_semantics.c#L598">598</a>                         if (<a href="ident?i=cfg">cfg</a>-&gt;fc_scope &gt;= RT_SCOPE_LINK)
<a name="L599" href="source/net/ipv4/fib_semantics.c#L599">599</a>                                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L600" href="source/net/ipv4/fib_semantics.c#L600">600</a>                         if (<a href="ident?i=inet_addr_type">inet_addr_type</a>(<a href="ident?i=net">net</a>, nh-&gt;nh_gw) != RTN_UNICAST)
<a name="L601" href="source/net/ipv4/fib_semantics.c#L601">601</a>                                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L602" href="source/net/ipv4/fib_semantics.c#L602">602</a>                         <a href="ident?i=dev">dev</a> = <a href="ident?i=__dev_get_by_index">__dev_get_by_index</a>(<a href="ident?i=net">net</a>, nh-&gt;nh_oif);
<a name="L603" href="source/net/ipv4/fib_semantics.c#L603">603</a>                         if (!<a href="ident?i=dev">dev</a>)
<a name="L604" href="source/net/ipv4/fib_semantics.c#L604">604</a>                                 return -<a href="ident?i=ENODEV">ENODEV</a>;
<a name="L605" href="source/net/ipv4/fib_semantics.c#L605">605</a>                         if (!(<a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=IFF_UP">IFF_UP</a>))
<a name="L606" href="source/net/ipv4/fib_semantics.c#L606">606</a>                                 return -<a href="ident?i=ENETDOWN">ENETDOWN</a>;
<a name="L607" href="source/net/ipv4/fib_semantics.c#L607">607</a>                         nh-&gt;nh_dev = <a href="ident?i=dev">dev</a>;
<a name="L608" href="source/net/ipv4/fib_semantics.c#L608">608</a>                         <a href="ident?i=dev_hold">dev_hold</a>(<a href="ident?i=dev">dev</a>);
<a name="L609" href="source/net/ipv4/fib_semantics.c#L609">609</a>                         nh-&gt;nh_scope = RT_SCOPE_LINK;
<a name="L610" href="source/net/ipv4/fib_semantics.c#L610">610</a>                         return 0;
<a name="L611" href="source/net/ipv4/fib_semantics.c#L611">611</a>                 }
<a name="L612" href="source/net/ipv4/fib_semantics.c#L612">612</a>                 <a href="ident?i=rcu_read_lock">rcu_read_lock</a>();
<a name="L613" href="source/net/ipv4/fib_semantics.c#L613">613</a>                 {
<a name="L614" href="source/net/ipv4/fib_semantics.c#L614">614</a>                         struct <a href="ident?i=flowi4">flowi4</a> fl4 = {
<a name="L615" href="source/net/ipv4/fib_semantics.c#L615">615</a>                                 .<a href="ident?i=daddr">daddr</a> = nh-&gt;nh_gw,
<a name="L616" href="source/net/ipv4/fib_semantics.c#L616">616</a>                                 .<a href="ident?i=flowi4_scope">flowi4_scope</a> = <a href="ident?i=cfg">cfg</a>-&gt;fc_scope + 1,
<a name="L617" href="source/net/ipv4/fib_semantics.c#L617">617</a>                                 .<a href="ident?i=flowi4_oif">flowi4_oif</a> = nh-&gt;nh_oif,
<a name="L618" href="source/net/ipv4/fib_semantics.c#L618">618</a>                                 .<a href="ident?i=flowi4_iif">flowi4_iif</a> = <a href="ident?i=LOOPBACK_IFINDEX">LOOPBACK_IFINDEX</a>,
<a name="L619" href="source/net/ipv4/fib_semantics.c#L619">619</a>                         };
<a name="L620" href="source/net/ipv4/fib_semantics.c#L620">620</a> 
<a name="L621" href="source/net/ipv4/fib_semantics.c#L621">621</a>                         <b><i>/* It is not necessary, but requires a bit of thinking */</i></b>
<a name="L622" href="source/net/ipv4/fib_semantics.c#L622">622</a>                         if (fl4.<a href="ident?i=flowi4_scope">flowi4_scope</a> &lt; RT_SCOPE_LINK)
<a name="L623" href="source/net/ipv4/fib_semantics.c#L623">623</a>                                 fl4.<a href="ident?i=flowi4_scope">flowi4_scope</a> = RT_SCOPE_LINK;
<a name="L624" href="source/net/ipv4/fib_semantics.c#L624">624</a>                         <a href="ident?i=err">err</a> = <a href="ident?i=fib_lookup">fib_lookup</a>(<a href="ident?i=net">net</a>, &amp;fl4, &amp;<a href="ident?i=res">res</a>);
<a name="L625" href="source/net/ipv4/fib_semantics.c#L625">625</a>                         if (<a href="ident?i=err">err</a>) {
<a name="L626" href="source/net/ipv4/fib_semantics.c#L626">626</a>                                 <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L627" href="source/net/ipv4/fib_semantics.c#L627">627</a>                                 return <a href="ident?i=err">err</a>;
<a name="L628" href="source/net/ipv4/fib_semantics.c#L628">628</a>                         }
<a name="L629" href="source/net/ipv4/fib_semantics.c#L629">629</a>                 }
<a name="L630" href="source/net/ipv4/fib_semantics.c#L630">630</a>                 <a href="ident?i=err">err</a> = -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L631" href="source/net/ipv4/fib_semantics.c#L631">631</a>                 if (<a href="ident?i=res">res</a>.<a href="ident?i=type">type</a> != RTN_UNICAST &amp;&amp; <a href="ident?i=res">res</a>.<a href="ident?i=type">type</a> != RTN_LOCAL)
<a name="L632" href="source/net/ipv4/fib_semantics.c#L632">632</a>                         goto <a href="ident?i=out">out</a>;
<a name="L633" href="source/net/ipv4/fib_semantics.c#L633">633</a>                 nh-&gt;nh_scope = <a href="ident?i=res">res</a>.<a href="ident?i=scope">scope</a>;
<a name="L634" href="source/net/ipv4/fib_semantics.c#L634">634</a>                 nh-&gt;nh_oif = <a href="ident?i=FIB_RES_OIF">FIB_RES_OIF</a>(<a href="ident?i=res">res</a>);
<a name="L635" href="source/net/ipv4/fib_semantics.c#L635">635</a>                 nh-&gt;nh_dev = <a href="ident?i=dev">dev</a> = <a href="ident?i=FIB_RES_DEV">FIB_RES_DEV</a>(<a href="ident?i=res">res</a>);
<a name="L636" href="source/net/ipv4/fib_semantics.c#L636">636</a>                 if (!<a href="ident?i=dev">dev</a>)
<a name="L637" href="source/net/ipv4/fib_semantics.c#L637">637</a>                         goto <a href="ident?i=out">out</a>;
<a name="L638" href="source/net/ipv4/fib_semantics.c#L638">638</a>                 <a href="ident?i=dev_hold">dev_hold</a>(<a href="ident?i=dev">dev</a>);
<a name="L639" href="source/net/ipv4/fib_semantics.c#L639">639</a>                 <a href="ident?i=err">err</a> = (<a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=IFF_UP">IFF_UP</a>) ? 0 : -<a href="ident?i=ENETDOWN">ENETDOWN</a>;
<a name="L640" href="source/net/ipv4/fib_semantics.c#L640">640</a>         } else {
<a name="L641" href="source/net/ipv4/fib_semantics.c#L641">641</a>                 struct <a href="ident?i=in_device">in_device</a> *in_dev;
<a name="L642" href="source/net/ipv4/fib_semantics.c#L642">642</a> 
<a name="L643" href="source/net/ipv4/fib_semantics.c#L643">643</a>                 if (nh-&gt;nh_flags &amp; (<a href="ident?i=RTNH_F_PERVASIVE">RTNH_F_PERVASIVE</a> | <a href="ident?i=RTNH_F_ONLINK">RTNH_F_ONLINK</a>))
<a name="L644" href="source/net/ipv4/fib_semantics.c#L644">644</a>                         return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L645" href="source/net/ipv4/fib_semantics.c#L645">645</a> 
<a name="L646" href="source/net/ipv4/fib_semantics.c#L646">646</a>                 <a href="ident?i=rcu_read_lock">rcu_read_lock</a>();
<a name="L647" href="source/net/ipv4/fib_semantics.c#L647">647</a>                 <a href="ident?i=err">err</a> = -<a href="ident?i=ENODEV">ENODEV</a>;
<a name="L648" href="source/net/ipv4/fib_semantics.c#L648">648</a>                 in_dev = <a href="ident?i=inetdev_by_index">inetdev_by_index</a>(<a href="ident?i=net">net</a>, nh-&gt;nh_oif);
<a name="L649" href="source/net/ipv4/fib_semantics.c#L649">649</a>                 if (!in_dev)
<a name="L650" href="source/net/ipv4/fib_semantics.c#L650">650</a>                         goto <a href="ident?i=out">out</a>;
<a name="L651" href="source/net/ipv4/fib_semantics.c#L651">651</a>                 <a href="ident?i=err">err</a> = -<a href="ident?i=ENETDOWN">ENETDOWN</a>;
<a name="L652" href="source/net/ipv4/fib_semantics.c#L652">652</a>                 if (!(in_dev-&gt;<a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=IFF_UP">IFF_UP</a>))
<a name="L653" href="source/net/ipv4/fib_semantics.c#L653">653</a>                         goto <a href="ident?i=out">out</a>;
<a name="L654" href="source/net/ipv4/fib_semantics.c#L654">654</a>                 nh-&gt;nh_dev = in_dev-&gt;<a href="ident?i=dev">dev</a>;
<a name="L655" href="source/net/ipv4/fib_semantics.c#L655">655</a>                 <a href="ident?i=dev_hold">dev_hold</a>(nh-&gt;nh_dev);
<a name="L656" href="source/net/ipv4/fib_semantics.c#L656">656</a>                 nh-&gt;nh_scope = RT_SCOPE_HOST;
<a name="L657" href="source/net/ipv4/fib_semantics.c#L657">657</a>                 <a href="ident?i=err">err</a> = 0;
<a name="L658" href="source/net/ipv4/fib_semantics.c#L658">658</a>         }
<a name="L659" href="source/net/ipv4/fib_semantics.c#L659">659</a> <a href="ident?i=out">out</a>:
<a name="L660" href="source/net/ipv4/fib_semantics.c#L660">660</a>         <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L661" href="source/net/ipv4/fib_semantics.c#L661">661</a>         return <a href="ident?i=err">err</a>;
<a name="L662" href="source/net/ipv4/fib_semantics.c#L662">662</a> }
<a name="L663" href="source/net/ipv4/fib_semantics.c#L663">663</a> 
<a name="L664" href="source/net/ipv4/fib_semantics.c#L664">664</a> static inline unsigned int <a href="ident?i=fib_laddr_hashfn">fib_laddr_hashfn</a>(<a href="ident?i=__be32">__be32</a> <a href="ident?i=val">val</a>)
<a name="L665" href="source/net/ipv4/fib_semantics.c#L665">665</a> {
<a name="L666" href="source/net/ipv4/fib_semantics.c#L666">666</a>         unsigned int <a href="ident?i=mask">mask</a> = (<a href="ident?i=fib_info_hash_size">fib_info_hash_size</a> - 1);
<a name="L667" href="source/net/ipv4/fib_semantics.c#L667">667</a> 
<a name="L668" href="source/net/ipv4/fib_semantics.c#L668">668</a>         return ((<a href="ident?i=__force">__force</a> <a href="ident?i=u32">u32</a>)<a href="ident?i=val">val</a> ^
<a name="L669" href="source/net/ipv4/fib_semantics.c#L669">669</a>                 ((<a href="ident?i=__force">__force</a> <a href="ident?i=u32">u32</a>)<a href="ident?i=val">val</a> &gt;&gt; 7) ^
<a name="L670" href="source/net/ipv4/fib_semantics.c#L670">670</a>                 ((<a href="ident?i=__force">__force</a> <a href="ident?i=u32">u32</a>)<a href="ident?i=val">val</a> &gt;&gt; 14)) &amp; <a href="ident?i=mask">mask</a>;
<a name="L671" href="source/net/ipv4/fib_semantics.c#L671">671</a> }
<a name="L672" href="source/net/ipv4/fib_semantics.c#L672">672</a> 
<a name="L673" href="source/net/ipv4/fib_semantics.c#L673">673</a> static struct <a href="ident?i=hlist_head">hlist_head</a> *<a href="ident?i=fib_info_hash_alloc">fib_info_hash_alloc</a>(int <a href="ident?i=bytes">bytes</a>)
<a name="L674" href="source/net/ipv4/fib_semantics.c#L674">674</a> {
<a name="L675" href="source/net/ipv4/fib_semantics.c#L675">675</a>         if (<a href="ident?i=bytes">bytes</a> &lt;= <a href="ident?i=PAGE_SIZE">PAGE_SIZE</a>)
<a name="L676" href="source/net/ipv4/fib_semantics.c#L676">676</a>                 return <a href="ident?i=kzalloc">kzalloc</a>(<a href="ident?i=bytes">bytes</a>, <a href="ident?i=GFP_KERNEL">GFP_KERNEL</a>);
<a name="L677" href="source/net/ipv4/fib_semantics.c#L677">677</a>         else
<a name="L678" href="source/net/ipv4/fib_semantics.c#L678">678</a>                 return (struct <a href="ident?i=hlist_head">hlist_head</a> *)
<a name="L679" href="source/net/ipv4/fib_semantics.c#L679">679</a>                         <a href="ident?i=__get_free_pages">__get_free_pages</a>(<a href="ident?i=GFP_KERNEL">GFP_KERNEL</a> | <a href="ident?i=__GFP_ZERO">__GFP_ZERO</a>,
<a name="L680" href="source/net/ipv4/fib_semantics.c#L680">680</a>                                          <a href="ident?i=get_order">get_order</a>(<a href="ident?i=bytes">bytes</a>));
<a name="L681" href="source/net/ipv4/fib_semantics.c#L681">681</a> }
<a name="L682" href="source/net/ipv4/fib_semantics.c#L682">682</a> 
<a name="L683" href="source/net/ipv4/fib_semantics.c#L683">683</a> static void <a href="ident?i=fib_info_hash_free">fib_info_hash_free</a>(struct <a href="ident?i=hlist_head">hlist_head</a> *<a href="ident?i=hash">hash</a>, int <a href="ident?i=bytes">bytes</a>)
<a name="L684" href="source/net/ipv4/fib_semantics.c#L684">684</a> {
<a name="L685" href="source/net/ipv4/fib_semantics.c#L685">685</a>         if (!<a href="ident?i=hash">hash</a>)
<a name="L686" href="source/net/ipv4/fib_semantics.c#L686">686</a>                 return;
<a name="L687" href="source/net/ipv4/fib_semantics.c#L687">687</a> 
<a name="L688" href="source/net/ipv4/fib_semantics.c#L688">688</a>         if (<a href="ident?i=bytes">bytes</a> &lt;= <a href="ident?i=PAGE_SIZE">PAGE_SIZE</a>)
<a name="L689" href="source/net/ipv4/fib_semantics.c#L689">689</a>                 <a href="ident?i=kfree">kfree</a>(<a href="ident?i=hash">hash</a>);
<a name="L690" href="source/net/ipv4/fib_semantics.c#L690">690</a>         else
<a name="L691" href="source/net/ipv4/fib_semantics.c#L691">691</a>                 <a href="ident?i=free_pages">free_pages</a>((unsigned long) <a href="ident?i=hash">hash</a>, <a href="ident?i=get_order">get_order</a>(<a href="ident?i=bytes">bytes</a>));
<a name="L692" href="source/net/ipv4/fib_semantics.c#L692">692</a> }
<a name="L693" href="source/net/ipv4/fib_semantics.c#L693">693</a> 
<a name="L694" href="source/net/ipv4/fib_semantics.c#L694">694</a> static void <a href="ident?i=fib_info_hash_move">fib_info_hash_move</a>(struct <a href="ident?i=hlist_head">hlist_head</a> *new_info_hash,
<a name="L695" href="source/net/ipv4/fib_semantics.c#L695">695</a>                                struct <a href="ident?i=hlist_head">hlist_head</a> *new_laddrhash,
<a name="L696" href="source/net/ipv4/fib_semantics.c#L696">696</a>                                unsigned int new_size)
<a name="L697" href="source/net/ipv4/fib_semantics.c#L697">697</a> {
<a name="L698" href="source/net/ipv4/fib_semantics.c#L698">698</a>         struct <a href="ident?i=hlist_head">hlist_head</a> *old_info_hash, *old_laddrhash;
<a name="L699" href="source/net/ipv4/fib_semantics.c#L699">699</a>         unsigned int old_size = <a href="ident?i=fib_info_hash_size">fib_info_hash_size</a>;
<a name="L700" href="source/net/ipv4/fib_semantics.c#L700">700</a>         unsigned int <a href="ident?i=i">i</a>, <a href="ident?i=bytes">bytes</a>;
<a name="L701" href="source/net/ipv4/fib_semantics.c#L701">701</a> 
<a name="L702" href="source/net/ipv4/fib_semantics.c#L702">702</a>         <a href="ident?i=spin_lock_bh">spin_lock_bh</a>(&amp;fib_info_lock);
<a name="L703" href="source/net/ipv4/fib_semantics.c#L703">703</a>         old_info_hash = <a href="ident?i=fib_info_hash">fib_info_hash</a>;
<a name="L704" href="source/net/ipv4/fib_semantics.c#L704">704</a>         old_laddrhash = <a href="ident?i=fib_info_laddrhash">fib_info_laddrhash</a>;
<a name="L705" href="source/net/ipv4/fib_semantics.c#L705">705</a>         <a href="ident?i=fib_info_hash_size">fib_info_hash_size</a> = new_size;
<a name="L706" href="source/net/ipv4/fib_semantics.c#L706">706</a> 
<a name="L707" href="source/net/ipv4/fib_semantics.c#L707">707</a>         for (<a href="ident?i=i">i</a> = 0; <a href="ident?i=i">i</a> &lt; old_size; <a href="ident?i=i">i</a>++) {
<a name="L708" href="source/net/ipv4/fib_semantics.c#L708">708</a>                 struct <a href="ident?i=hlist_head">hlist_head</a> *<a href="ident?i=head">head</a> = &amp;<a href="ident?i=fib_info_hash">fib_info_hash</a>[<a href="ident?i=i">i</a>];
<a name="L709" href="source/net/ipv4/fib_semantics.c#L709">709</a>                 struct <a href="ident?i=hlist_node">hlist_node</a> *<a href="ident?i=n">n</a>;
<a name="L710" href="source/net/ipv4/fib_semantics.c#L710">710</a>                 struct <a href="ident?i=fib_info">fib_info</a> *fi;
<a name="L711" href="source/net/ipv4/fib_semantics.c#L711">711</a> 
<a name="L712" href="source/net/ipv4/fib_semantics.c#L712">712</a>                 <a href="ident?i=hlist_for_each_entry_safe">hlist_for_each_entry_safe</a>(fi, <a href="ident?i=n">n</a>, <a href="ident?i=head">head</a>, fib_hash) {
<a name="L713" href="source/net/ipv4/fib_semantics.c#L713">713</a>                         struct <a href="ident?i=hlist_head">hlist_head</a> *<a href="ident?i=dest">dest</a>;
<a name="L714" href="source/net/ipv4/fib_semantics.c#L714">714</a>                         unsigned int new_hash;
<a name="L715" href="source/net/ipv4/fib_semantics.c#L715">715</a> 
<a name="L716" href="source/net/ipv4/fib_semantics.c#L716">716</a>                         <a href="ident?i=hlist_del">hlist_del</a>(&amp;fi-&gt;fib_hash);
<a name="L717" href="source/net/ipv4/fib_semantics.c#L717">717</a> 
<a name="L718" href="source/net/ipv4/fib_semantics.c#L718">718</a>                         new_hash = <a href="ident?i=fib_info_hashfn">fib_info_hashfn</a>(fi);
<a name="L719" href="source/net/ipv4/fib_semantics.c#L719">719</a>                         <a href="ident?i=dest">dest</a> = &amp;new_info_hash[new_hash];
<a name="L720" href="source/net/ipv4/fib_semantics.c#L720">720</a>                         <a href="ident?i=hlist_add_head">hlist_add_head</a>(&amp;fi-&gt;fib_hash, <a href="ident?i=dest">dest</a>);
<a name="L721" href="source/net/ipv4/fib_semantics.c#L721">721</a>                 }
<a name="L722" href="source/net/ipv4/fib_semantics.c#L722">722</a>         }
<a name="L723" href="source/net/ipv4/fib_semantics.c#L723">723</a>         <a href="ident?i=fib_info_hash">fib_info_hash</a> = new_info_hash;
<a name="L724" href="source/net/ipv4/fib_semantics.c#L724">724</a> 
<a name="L725" href="source/net/ipv4/fib_semantics.c#L725">725</a>         for (<a href="ident?i=i">i</a> = 0; <a href="ident?i=i">i</a> &lt; old_size; <a href="ident?i=i">i</a>++) {
<a name="L726" href="source/net/ipv4/fib_semantics.c#L726">726</a>                 struct <a href="ident?i=hlist_head">hlist_head</a> *lhead = &amp;<a href="ident?i=fib_info_laddrhash">fib_info_laddrhash</a>[<a href="ident?i=i">i</a>];
<a name="L727" href="source/net/ipv4/fib_semantics.c#L727">727</a>                 struct <a href="ident?i=hlist_node">hlist_node</a> *<a href="ident?i=n">n</a>;
<a name="L728" href="source/net/ipv4/fib_semantics.c#L728">728</a>                 struct <a href="ident?i=fib_info">fib_info</a> *fi;
<a name="L729" href="source/net/ipv4/fib_semantics.c#L729">729</a> 
<a name="L730" href="source/net/ipv4/fib_semantics.c#L730">730</a>                 <a href="ident?i=hlist_for_each_entry_safe">hlist_for_each_entry_safe</a>(fi, <a href="ident?i=n">n</a>, lhead, fib_lhash) {
<a name="L731" href="source/net/ipv4/fib_semantics.c#L731">731</a>                         struct <a href="ident?i=hlist_head">hlist_head</a> *ldest;
<a name="L732" href="source/net/ipv4/fib_semantics.c#L732">732</a>                         unsigned int new_hash;
<a name="L733" href="source/net/ipv4/fib_semantics.c#L733">733</a> 
<a name="L734" href="source/net/ipv4/fib_semantics.c#L734">734</a>                         <a href="ident?i=hlist_del">hlist_del</a>(&amp;fi-&gt;fib_lhash);
<a name="L735" href="source/net/ipv4/fib_semantics.c#L735">735</a> 
<a name="L736" href="source/net/ipv4/fib_semantics.c#L736">736</a>                         new_hash = <a href="ident?i=fib_laddr_hashfn">fib_laddr_hashfn</a>(fi-&gt;fib_prefsrc);
<a name="L737" href="source/net/ipv4/fib_semantics.c#L737">737</a>                         ldest = &amp;new_laddrhash[new_hash];
<a name="L738" href="source/net/ipv4/fib_semantics.c#L738">738</a>                         <a href="ident?i=hlist_add_head">hlist_add_head</a>(&amp;fi-&gt;fib_lhash, ldest);
<a name="L739" href="source/net/ipv4/fib_semantics.c#L739">739</a>                 }
<a name="L740" href="source/net/ipv4/fib_semantics.c#L740">740</a>         }
<a name="L741" href="source/net/ipv4/fib_semantics.c#L741">741</a>         <a href="ident?i=fib_info_laddrhash">fib_info_laddrhash</a> = new_laddrhash;
<a name="L742" href="source/net/ipv4/fib_semantics.c#L742">742</a> 
<a name="L743" href="source/net/ipv4/fib_semantics.c#L743">743</a>         <a href="ident?i=spin_unlock_bh">spin_unlock_bh</a>(&amp;fib_info_lock);
<a name="L744" href="source/net/ipv4/fib_semantics.c#L744">744</a> 
<a name="L745" href="source/net/ipv4/fib_semantics.c#L745">745</a>         <a href="ident?i=bytes">bytes</a> = old_size * sizeof(struct <a href="ident?i=hlist_head">hlist_head</a> *);
<a name="L746" href="source/net/ipv4/fib_semantics.c#L746">746</a>         <a href="ident?i=fib_info_hash_free">fib_info_hash_free</a>(old_info_hash, <a href="ident?i=bytes">bytes</a>);
<a name="L747" href="source/net/ipv4/fib_semantics.c#L747">747</a>         <a href="ident?i=fib_info_hash_free">fib_info_hash_free</a>(old_laddrhash, <a href="ident?i=bytes">bytes</a>);
<a name="L748" href="source/net/ipv4/fib_semantics.c#L748">748</a> }
<a name="L749" href="source/net/ipv4/fib_semantics.c#L749">749</a> 
<a name="L750" href="source/net/ipv4/fib_semantics.c#L750">750</a> <a href="ident?i=__be32">__be32</a> <a href="ident?i=fib_info_update_nh_saddr">fib_info_update_nh_saddr</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>, struct <a href="ident?i=fib_nh">fib_nh</a> *nh)
<a name="L751" href="source/net/ipv4/fib_semantics.c#L751">751</a> {
<a name="L752" href="source/net/ipv4/fib_semantics.c#L752">752</a>         nh-&gt;nh_saddr = <a href="ident?i=inet_select_addr">inet_select_addr</a>(nh-&gt;nh_dev,
<a name="L753" href="source/net/ipv4/fib_semantics.c#L753">753</a>                                         nh-&gt;nh_gw,
<a name="L754" href="source/net/ipv4/fib_semantics.c#L754">754</a>                                         nh-&gt;nh_parent-&gt;fib_scope);
<a name="L755" href="source/net/ipv4/fib_semantics.c#L755">755</a>         nh-&gt;nh_saddr_genid = <a href="ident?i=atomic_read">atomic_read</a>(&amp;<a href="ident?i=net">net</a>-&gt;ipv4.dev_addr_genid);
<a name="L756" href="source/net/ipv4/fib_semantics.c#L756">756</a> 
<a name="L757" href="source/net/ipv4/fib_semantics.c#L757">757</a>         return nh-&gt;nh_saddr;
<a name="L758" href="source/net/ipv4/fib_semantics.c#L758">758</a> }
<a name="L759" href="source/net/ipv4/fib_semantics.c#L759">759</a> 
<a name="L760" href="source/net/ipv4/fib_semantics.c#L760">760</a> struct <a href="ident?i=fib_info">fib_info</a> *<a href="ident?i=fib_create_info">fib_create_info</a>(struct <a href="ident?i=fib_config">fib_config</a> *<a href="ident?i=cfg">cfg</a>)
<a name="L761" href="source/net/ipv4/fib_semantics.c#L761">761</a> {
<a name="L762" href="source/net/ipv4/fib_semantics.c#L762">762</a>         int <a href="ident?i=err">err</a>;
<a name="L763" href="source/net/ipv4/fib_semantics.c#L763">763</a>         struct <a href="ident?i=fib_info">fib_info</a> *fi = <a href="ident?i=NULL">NULL</a>;
<a name="L764" href="source/net/ipv4/fib_semantics.c#L764">764</a>         struct <a href="ident?i=fib_info">fib_info</a> *ofi;
<a name="L765" href="source/net/ipv4/fib_semantics.c#L765">765</a>         int nhs = 1;
<a name="L766" href="source/net/ipv4/fib_semantics.c#L766">766</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=cfg">cfg</a>-&gt;fc_nlinfo.nl_net;
<a name="L767" href="source/net/ipv4/fib_semantics.c#L767">767</a> 
<a name="L768" href="source/net/ipv4/fib_semantics.c#L768">768</a>         if (<a href="ident?i=cfg">cfg</a>-&gt;<a href="ident?i=fc_type">fc_type</a> &gt; <a href="ident?i=RTN_MAX">RTN_MAX</a>)
<a name="L769" href="source/net/ipv4/fib_semantics.c#L769">769</a>                 goto err_inval;
<a name="L770" href="source/net/ipv4/fib_semantics.c#L770">770</a> 
<a name="L771" href="source/net/ipv4/fib_semantics.c#L771">771</a>         <b><i>/* Fast check to catch the most weird cases */</i></b>
<a name="L772" href="source/net/ipv4/fib_semantics.c#L772">772</a>         if (<a href="ident?i=fib_props">fib_props</a>[<a href="ident?i=cfg">cfg</a>-&gt;<a href="ident?i=fc_type">fc_type</a>].<a href="ident?i=scope">scope</a> &gt; <a href="ident?i=cfg">cfg</a>-&gt;fc_scope)
<a name="L773" href="source/net/ipv4/fib_semantics.c#L773">773</a>                 goto err_inval;
<a name="L774" href="source/net/ipv4/fib_semantics.c#L774">774</a> 
<a name="L775" href="source/net/ipv4/fib_semantics.c#L775">775</a> #ifdef CONFIG_IP_ROUTE_MULTIPATH
<a name="L776" href="source/net/ipv4/fib_semantics.c#L776">776</a>         if (<a href="ident?i=cfg">cfg</a>-&gt;fc_mp) {
<a name="L777" href="source/net/ipv4/fib_semantics.c#L777">777</a>                 nhs = <a href="ident?i=fib_count_nexthops">fib_count_nexthops</a>(<a href="ident?i=cfg">cfg</a>-&gt;fc_mp, <a href="ident?i=cfg">cfg</a>-&gt;fc_mp_len);
<a name="L778" href="source/net/ipv4/fib_semantics.c#L778">778</a>                 if (nhs == 0)
<a name="L779" href="source/net/ipv4/fib_semantics.c#L779">779</a>                         goto err_inval;
<a name="L780" href="source/net/ipv4/fib_semantics.c#L780">780</a>         }
<a name="L781" href="source/net/ipv4/fib_semantics.c#L781">781</a> #endif
<a name="L782" href="source/net/ipv4/fib_semantics.c#L782">782</a> 
<a name="L783" href="source/net/ipv4/fib_semantics.c#L783">783</a>         <a href="ident?i=err">err</a> = -<a href="ident?i=ENOBUFS">ENOBUFS</a>;
<a name="L784" href="source/net/ipv4/fib_semantics.c#L784">784</a>         if (<a href="ident?i=fib_info_cnt">fib_info_cnt</a> &gt;= <a href="ident?i=fib_info_hash_size">fib_info_hash_size</a>) {
<a name="L785" href="source/net/ipv4/fib_semantics.c#L785">785</a>                 unsigned int new_size = <a href="ident?i=fib_info_hash_size">fib_info_hash_size</a> &lt;&lt; 1;
<a name="L786" href="source/net/ipv4/fib_semantics.c#L786">786</a>                 struct <a href="ident?i=hlist_head">hlist_head</a> *new_info_hash;
<a name="L787" href="source/net/ipv4/fib_semantics.c#L787">787</a>                 struct <a href="ident?i=hlist_head">hlist_head</a> *new_laddrhash;
<a name="L788" href="source/net/ipv4/fib_semantics.c#L788">788</a>                 unsigned int <a href="ident?i=bytes">bytes</a>;
<a name="L789" href="source/net/ipv4/fib_semantics.c#L789">789</a> 
<a name="L790" href="source/net/ipv4/fib_semantics.c#L790">790</a>                 if (!new_size)
<a name="L791" href="source/net/ipv4/fib_semantics.c#L791">791</a>                         new_size = 16;
<a name="L792" href="source/net/ipv4/fib_semantics.c#L792">792</a>                 <a href="ident?i=bytes">bytes</a> = new_size * sizeof(struct <a href="ident?i=hlist_head">hlist_head</a> *);
<a name="L793" href="source/net/ipv4/fib_semantics.c#L793">793</a>                 new_info_hash = <a href="ident?i=fib_info_hash_alloc">fib_info_hash_alloc</a>(<a href="ident?i=bytes">bytes</a>);
<a name="L794" href="source/net/ipv4/fib_semantics.c#L794">794</a>                 new_laddrhash = <a href="ident?i=fib_info_hash_alloc">fib_info_hash_alloc</a>(<a href="ident?i=bytes">bytes</a>);
<a name="L795" href="source/net/ipv4/fib_semantics.c#L795">795</a>                 if (!new_info_hash || !new_laddrhash) {
<a name="L796" href="source/net/ipv4/fib_semantics.c#L796">796</a>                         <a href="ident?i=fib_info_hash_free">fib_info_hash_free</a>(new_info_hash, <a href="ident?i=bytes">bytes</a>);
<a name="L797" href="source/net/ipv4/fib_semantics.c#L797">797</a>                         <a href="ident?i=fib_info_hash_free">fib_info_hash_free</a>(new_laddrhash, <a href="ident?i=bytes">bytes</a>);
<a name="L798" href="source/net/ipv4/fib_semantics.c#L798">798</a>                 } else
<a name="L799" href="source/net/ipv4/fib_semantics.c#L799">799</a>                         <a href="ident?i=fib_info_hash_move">fib_info_hash_move</a>(new_info_hash, new_laddrhash, new_size);
<a name="L800" href="source/net/ipv4/fib_semantics.c#L800">800</a> 
<a name="L801" href="source/net/ipv4/fib_semantics.c#L801">801</a>                 if (!<a href="ident?i=fib_info_hash_size">fib_info_hash_size</a>)
<a name="L802" href="source/net/ipv4/fib_semantics.c#L802">802</a>                         goto failure;
<a name="L803" href="source/net/ipv4/fib_semantics.c#L803">803</a>         }
<a name="L804" href="source/net/ipv4/fib_semantics.c#L804">804</a> 
<a name="L805" href="source/net/ipv4/fib_semantics.c#L805">805</a>         fi = <a href="ident?i=kzalloc">kzalloc</a>(sizeof(*fi)+nhs*sizeof(struct <a href="ident?i=fib_nh">fib_nh</a>), <a href="ident?i=GFP_KERNEL">GFP_KERNEL</a>);
<a name="L806" href="source/net/ipv4/fib_semantics.c#L806">806</a>         if (!fi)
<a name="L807" href="source/net/ipv4/fib_semantics.c#L807">807</a>                 goto failure;
<a name="L808" href="source/net/ipv4/fib_semantics.c#L808">808</a>         <a href="ident?i=fib_info_cnt">fib_info_cnt</a>++;
<a name="L809" href="source/net/ipv4/fib_semantics.c#L809">809</a>         if (<a href="ident?i=cfg">cfg</a>-&gt;fc_mx) {
<a name="L810" href="source/net/ipv4/fib_semantics.c#L810">810</a>                 fi-&gt;fib_metrics = <a href="ident?i=kzalloc">kzalloc</a>(sizeof(<a href="ident?i=u32">u32</a>) * <a href="ident?i=RTAX_MAX">RTAX_MAX</a>, <a href="ident?i=GFP_KERNEL">GFP_KERNEL</a>);
<a name="L811" href="source/net/ipv4/fib_semantics.c#L811">811</a>                 if (!fi-&gt;fib_metrics)
<a name="L812" href="source/net/ipv4/fib_semantics.c#L812">812</a>                         goto failure;
<a name="L813" href="source/net/ipv4/fib_semantics.c#L813">813</a>         } else
<a name="L814" href="source/net/ipv4/fib_semantics.c#L814">814</a>                 fi-&gt;fib_metrics = (<a href="ident?i=u32">u32</a> *) <a href="ident?i=dst_default_metrics">dst_default_metrics</a>;
<a name="L815" href="source/net/ipv4/fib_semantics.c#L815">815</a> 
<a name="L816" href="source/net/ipv4/fib_semantics.c#L816">816</a>         fi-&gt;fib_net = <a href="ident?i=net">net</a>;
<a name="L817" href="source/net/ipv4/fib_semantics.c#L817">817</a>         fi-&gt;fib_protocol = <a href="ident?i=cfg">cfg</a>-&gt;fc_protocol;
<a name="L818" href="source/net/ipv4/fib_semantics.c#L818">818</a>         fi-&gt;fib_scope = <a href="ident?i=cfg">cfg</a>-&gt;fc_scope;
<a name="L819" href="source/net/ipv4/fib_semantics.c#L819">819</a>         fi-&gt;fib_flags = <a href="ident?i=cfg">cfg</a>-&gt;fc_flags;
<a name="L820" href="source/net/ipv4/fib_semantics.c#L820">820</a>         fi-&gt;fib_priority = <a href="ident?i=cfg">cfg</a>-&gt;fc_priority;
<a name="L821" href="source/net/ipv4/fib_semantics.c#L821">821</a>         fi-&gt;fib_prefsrc = <a href="ident?i=cfg">cfg</a>-&gt;fc_prefsrc;
<a name="L822" href="source/net/ipv4/fib_semantics.c#L822">822</a>         fi-&gt;fib_type = <a href="ident?i=cfg">cfg</a>-&gt;<a href="ident?i=fc_type">fc_type</a>;
<a name="L823" href="source/net/ipv4/fib_semantics.c#L823">823</a> 
<a name="L824" href="source/net/ipv4/fib_semantics.c#L824">824</a>         fi-&gt;fib_nhs = nhs;
<a name="L825" href="source/net/ipv4/fib_semantics.c#L825">825</a>         <a href="ident?i=change_nexthops">change_nexthops</a>(fi) {
<a name="L826" href="source/net/ipv4/fib_semantics.c#L826">826</a>                 nexthop_nh-&gt;nh_parent = fi;
<a name="L827" href="source/net/ipv4/fib_semantics.c#L827">827</a>                 nexthop_nh-&gt;nh_pcpu_rth_output = <a href="ident?i=alloc_percpu">alloc_percpu</a>(struct <a href="ident?i=rtable">rtable</a> <a href="ident?i=__rcu">__rcu</a> *);
<a name="L828" href="source/net/ipv4/fib_semantics.c#L828">828</a>                 if (!nexthop_nh-&gt;nh_pcpu_rth_output)
<a name="L829" href="source/net/ipv4/fib_semantics.c#L829">829</a>                         goto failure;
<a name="L830" href="source/net/ipv4/fib_semantics.c#L830">830</a>         } <a href="ident?i=endfor_nexthops">endfor_nexthops</a>(fi)
<a name="L831" href="source/net/ipv4/fib_semantics.c#L831">831</a> 
<a name="L832" href="source/net/ipv4/fib_semantics.c#L832">832</a>         if (<a href="ident?i=cfg">cfg</a>-&gt;fc_mx) {
<a name="L833" href="source/net/ipv4/fib_semantics.c#L833">833</a>                 struct <a href="ident?i=nlattr">nlattr</a> *nla;
<a name="L834" href="source/net/ipv4/fib_semantics.c#L834">834</a>                 int <a href="ident?i=remaining">remaining</a>;
<a name="L835" href="source/net/ipv4/fib_semantics.c#L835">835</a> 
<a name="L836" href="source/net/ipv4/fib_semantics.c#L836">836</a>                 <a href="ident?i=nla_for_each_attr">nla_for_each_attr</a>(nla, <a href="ident?i=cfg">cfg</a>-&gt;fc_mx, <a href="ident?i=cfg">cfg</a>-&gt;fc_mx_len, <a href="ident?i=remaining">remaining</a>) {
<a name="L837" href="source/net/ipv4/fib_semantics.c#L837">837</a>                         int <a href="ident?i=type">type</a> = <a href="ident?i=nla_type">nla_type</a>(nla);
<a name="L838" href="source/net/ipv4/fib_semantics.c#L838">838</a> 
<a name="L839" href="source/net/ipv4/fib_semantics.c#L839">839</a>                         if (<a href="ident?i=type">type</a>) {
<a name="L840" href="source/net/ipv4/fib_semantics.c#L840">840</a>                                 <a href="ident?i=u32">u32</a> <a href="ident?i=val">val</a>;
<a name="L841" href="source/net/ipv4/fib_semantics.c#L841">841</a> 
<a name="L842" href="source/net/ipv4/fib_semantics.c#L842">842</a>                                 if (<a href="ident?i=type">type</a> &gt; <a href="ident?i=RTAX_MAX">RTAX_MAX</a>)
<a name="L843" href="source/net/ipv4/fib_semantics.c#L843">843</a>                                         goto err_inval;
<a name="L844" href="source/net/ipv4/fib_semantics.c#L844">844</a>                                 if (<a href="ident?i=type">type</a> == <a href="ident?i=RTAX_CC_ALGO">RTAX_CC_ALGO</a>) {
<a name="L845" href="source/net/ipv4/fib_semantics.c#L845">845</a>                                         char <a href="ident?i=tmp">tmp</a>[<a href="ident?i=TCP_CA_NAME_MAX">TCP_CA_NAME_MAX</a>];
<a name="L846" href="source/net/ipv4/fib_semantics.c#L846">846</a> 
<a name="L847" href="source/net/ipv4/fib_semantics.c#L847">847</a>                                         <a href="ident?i=nla_strlcpy">nla_strlcpy</a>(<a href="ident?i=tmp">tmp</a>, nla, sizeof(<a href="ident?i=tmp">tmp</a>));
<a name="L848" href="source/net/ipv4/fib_semantics.c#L848">848</a>                                         <a href="ident?i=val">val</a> = <a href="ident?i=tcp_ca_get_key_by_name">tcp_ca_get_key_by_name</a>(<a href="ident?i=tmp">tmp</a>);
<a name="L849" href="source/net/ipv4/fib_semantics.c#L849">849</a>                                         if (<a href="ident?i=val">val</a> == <a href="ident?i=TCP_CA_UNSPEC">TCP_CA_UNSPEC</a>)
<a name="L850" href="source/net/ipv4/fib_semantics.c#L850">850</a>                                                 goto err_inval;
<a name="L851" href="source/net/ipv4/fib_semantics.c#L851">851</a>                                 } else {
<a name="L852" href="source/net/ipv4/fib_semantics.c#L852">852</a>                                         <a href="ident?i=val">val</a> = <a href="ident?i=nla_get_u32">nla_get_u32</a>(nla);
<a name="L853" href="source/net/ipv4/fib_semantics.c#L853">853</a>                                 }
<a name="L854" href="source/net/ipv4/fib_semantics.c#L854">854</a>                                 if (<a href="ident?i=type">type</a> == <a href="ident?i=RTAX_ADVMSS">RTAX_ADVMSS</a> &amp;&amp; <a href="ident?i=val">val</a> &gt; 65535 - 40)
<a name="L855" href="source/net/ipv4/fib_semantics.c#L855">855</a>                                         <a href="ident?i=val">val</a> = 65535 - 40;
<a name="L856" href="source/net/ipv4/fib_semantics.c#L856">856</a>                                 if (<a href="ident?i=type">type</a> == <a href="ident?i=RTAX_MTU">RTAX_MTU</a> &amp;&amp; <a href="ident?i=val">val</a> &gt; 65535 - 15)
<a name="L857" href="source/net/ipv4/fib_semantics.c#L857">857</a>                                         <a href="ident?i=val">val</a> = 65535 - 15;
<a name="L858" href="source/net/ipv4/fib_semantics.c#L858">858</a>                                 fi-&gt;fib_metrics[<a href="ident?i=type">type</a> - 1] = <a href="ident?i=val">val</a>;
<a name="L859" href="source/net/ipv4/fib_semantics.c#L859">859</a>                         }
<a name="L860" href="source/net/ipv4/fib_semantics.c#L860">860</a>                 }
<a name="L861" href="source/net/ipv4/fib_semantics.c#L861">861</a>         }
<a name="L862" href="source/net/ipv4/fib_semantics.c#L862">862</a> 
<a name="L863" href="source/net/ipv4/fib_semantics.c#L863">863</a>         if (<a href="ident?i=cfg">cfg</a>-&gt;fc_mp) {
<a name="L864" href="source/net/ipv4/fib_semantics.c#L864">864</a> #ifdef CONFIG_IP_ROUTE_MULTIPATH
<a name="L865" href="source/net/ipv4/fib_semantics.c#L865">865</a>                 <a href="ident?i=err">err</a> = <a href="ident?i=fib_get_nhs">fib_get_nhs</a>(fi, <a href="ident?i=cfg">cfg</a>-&gt;fc_mp, <a href="ident?i=cfg">cfg</a>-&gt;fc_mp_len, <a href="ident?i=cfg">cfg</a>);
<a name="L866" href="source/net/ipv4/fib_semantics.c#L866">866</a>                 if (<a href="ident?i=err">err</a> != 0)
<a name="L867" href="source/net/ipv4/fib_semantics.c#L867">867</a>                         goto failure;
<a name="L868" href="source/net/ipv4/fib_semantics.c#L868">868</a>                 if (<a href="ident?i=cfg">cfg</a>-&gt;fc_oif &amp;&amp; fi-&gt;<a href="ident?i=fib_nh">fib_nh</a>-&gt;nh_oif != <a href="ident?i=cfg">cfg</a>-&gt;fc_oif)
<a name="L869" href="source/net/ipv4/fib_semantics.c#L869">869</a>                         goto err_inval;
<a name="L870" href="source/net/ipv4/fib_semantics.c#L870">870</a>                 if (<a href="ident?i=cfg">cfg</a>-&gt;fc_gw &amp;&amp; fi-&gt;<a href="ident?i=fib_nh">fib_nh</a>-&gt;nh_gw != <a href="ident?i=cfg">cfg</a>-&gt;fc_gw)
<a name="L871" href="source/net/ipv4/fib_semantics.c#L871">871</a>                         goto err_inval;
<a name="L872" href="source/net/ipv4/fib_semantics.c#L872">872</a> #ifdef CONFIG_IP_ROUTE_CLASSID
<a name="L873" href="source/net/ipv4/fib_semantics.c#L873">873</a>                 if (<a href="ident?i=cfg">cfg</a>-&gt;fc_flow &amp;&amp; fi-&gt;<a href="ident?i=fib_nh">fib_nh</a>-&gt;nh_tclassid != <a href="ident?i=cfg">cfg</a>-&gt;fc_flow)
<a name="L874" href="source/net/ipv4/fib_semantics.c#L874">874</a>                         goto err_inval;
<a name="L875" href="source/net/ipv4/fib_semantics.c#L875">875</a> #endif
<a name="L876" href="source/net/ipv4/fib_semantics.c#L876">876</a> #else
<a name="L877" href="source/net/ipv4/fib_semantics.c#L877">877</a>                 goto err_inval;
<a name="L878" href="source/net/ipv4/fib_semantics.c#L878">878</a> #endif
<a name="L879" href="source/net/ipv4/fib_semantics.c#L879">879</a>         } else {
<a name="L880" href="source/net/ipv4/fib_semantics.c#L880">880</a>                 struct <a href="ident?i=fib_nh">fib_nh</a> *nh = fi-&gt;<a href="ident?i=fib_nh">fib_nh</a>;
<a name="L881" href="source/net/ipv4/fib_semantics.c#L881">881</a> 
<a name="L882" href="source/net/ipv4/fib_semantics.c#L882">882</a>                 nh-&gt;nh_oif = <a href="ident?i=cfg">cfg</a>-&gt;fc_oif;
<a name="L883" href="source/net/ipv4/fib_semantics.c#L883">883</a>                 nh-&gt;nh_gw = <a href="ident?i=cfg">cfg</a>-&gt;fc_gw;
<a name="L884" href="source/net/ipv4/fib_semantics.c#L884">884</a>                 nh-&gt;nh_flags = <a href="ident?i=cfg">cfg</a>-&gt;fc_flags;
<a name="L885" href="source/net/ipv4/fib_semantics.c#L885">885</a> #ifdef CONFIG_IP_ROUTE_CLASSID
<a name="L886" href="source/net/ipv4/fib_semantics.c#L886">886</a>                 nh-&gt;nh_tclassid = <a href="ident?i=cfg">cfg</a>-&gt;fc_flow;
<a name="L887" href="source/net/ipv4/fib_semantics.c#L887">887</a>                 if (nh-&gt;nh_tclassid)
<a name="L888" href="source/net/ipv4/fib_semantics.c#L888">888</a>                         fi-&gt;fib_net-&gt;ipv4.<a href="ident?i=fib_num_tclassid_users">fib_num_tclassid_users</a>++;
<a name="L889" href="source/net/ipv4/fib_semantics.c#L889">889</a> #endif
<a name="L890" href="source/net/ipv4/fib_semantics.c#L890">890</a> #ifdef CONFIG_IP_ROUTE_MULTIPATH
<a name="L891" href="source/net/ipv4/fib_semantics.c#L891">891</a>                 nh-&gt;nh_weight = 1;
<a name="L892" href="source/net/ipv4/fib_semantics.c#L892">892</a> #endif
<a name="L893" href="source/net/ipv4/fib_semantics.c#L893">893</a>         }
<a name="L894" href="source/net/ipv4/fib_semantics.c#L894">894</a> 
<a name="L895" href="source/net/ipv4/fib_semantics.c#L895">895</a>         if (<a href="ident?i=fib_props">fib_props</a>[<a href="ident?i=cfg">cfg</a>-&gt;<a href="ident?i=fc_type">fc_type</a>].<a href="ident?i=error">error</a>) {
<a name="L896" href="source/net/ipv4/fib_semantics.c#L896">896</a>                 if (<a href="ident?i=cfg">cfg</a>-&gt;fc_gw || <a href="ident?i=cfg">cfg</a>-&gt;fc_oif || <a href="ident?i=cfg">cfg</a>-&gt;fc_mp)
<a name="L897" href="source/net/ipv4/fib_semantics.c#L897">897</a>                         goto err_inval;
<a name="L898" href="source/net/ipv4/fib_semantics.c#L898">898</a>                 goto link_it;
<a name="L899" href="source/net/ipv4/fib_semantics.c#L899">899</a>         } else {
<a name="L900" href="source/net/ipv4/fib_semantics.c#L900">900</a>                 switch (<a href="ident?i=cfg">cfg</a>-&gt;<a href="ident?i=fc_type">fc_type</a>) {
<a name="L901" href="source/net/ipv4/fib_semantics.c#L901">901</a>                 case RTN_UNICAST:
<a name="L902" href="source/net/ipv4/fib_semantics.c#L902">902</a>                 case RTN_LOCAL:
<a name="L903" href="source/net/ipv4/fib_semantics.c#L903">903</a>                 case RTN_BROADCAST:
<a name="L904" href="source/net/ipv4/fib_semantics.c#L904">904</a>                 case RTN_ANYCAST:
<a name="L905" href="source/net/ipv4/fib_semantics.c#L905">905</a>                 case RTN_MULTICAST:
<a name="L906" href="source/net/ipv4/fib_semantics.c#L906">906</a>                         break;
<a name="L907" href="source/net/ipv4/fib_semantics.c#L907">907</a>                 default:
<a name="L908" href="source/net/ipv4/fib_semantics.c#L908">908</a>                         goto err_inval;
<a name="L909" href="source/net/ipv4/fib_semantics.c#L909">909</a>                 }
<a name="L910" href="source/net/ipv4/fib_semantics.c#L910">910</a>         }
<a name="L911" href="source/net/ipv4/fib_semantics.c#L911">911</a> 
<a name="L912" href="source/net/ipv4/fib_semantics.c#L912">912</a>         if (<a href="ident?i=cfg">cfg</a>-&gt;fc_scope &gt; RT_SCOPE_HOST)
<a name="L913" href="source/net/ipv4/fib_semantics.c#L913">913</a>                 goto err_inval;
<a name="L914" href="source/net/ipv4/fib_semantics.c#L914">914</a> 
<a name="L915" href="source/net/ipv4/fib_semantics.c#L915">915</a>         if (<a href="ident?i=cfg">cfg</a>-&gt;fc_scope == RT_SCOPE_HOST) {
<a name="L916" href="source/net/ipv4/fib_semantics.c#L916">916</a>                 struct <a href="ident?i=fib_nh">fib_nh</a> *nh = fi-&gt;<a href="ident?i=fib_nh">fib_nh</a>;
<a name="L917" href="source/net/ipv4/fib_semantics.c#L917">917</a> 
<a name="L918" href="source/net/ipv4/fib_semantics.c#L918">918</a>                 <b><i>/* Local address is added. */</i></b>
<a name="L919" href="source/net/ipv4/fib_semantics.c#L919">919</a>                 if (nhs != 1 || nh-&gt;nh_gw)
<a name="L920" href="source/net/ipv4/fib_semantics.c#L920">920</a>                         goto err_inval;
<a name="L921" href="source/net/ipv4/fib_semantics.c#L921">921</a>                 nh-&gt;nh_scope = RT_SCOPE_NOWHERE;
<a name="L922" href="source/net/ipv4/fib_semantics.c#L922">922</a>                 nh-&gt;nh_dev = <a href="ident?i=dev_get_by_index">dev_get_by_index</a>(<a href="ident?i=net">net</a>, fi-&gt;<a href="ident?i=fib_nh">fib_nh</a>-&gt;nh_oif);
<a name="L923" href="source/net/ipv4/fib_semantics.c#L923">923</a>                 <a href="ident?i=err">err</a> = -<a href="ident?i=ENODEV">ENODEV</a>;
<a name="L924" href="source/net/ipv4/fib_semantics.c#L924">924</a>                 if (!nh-&gt;nh_dev)
<a name="L925" href="source/net/ipv4/fib_semantics.c#L925">925</a>                         goto failure;
<a name="L926" href="source/net/ipv4/fib_semantics.c#L926">926</a>         } else {
<a name="L927" href="source/net/ipv4/fib_semantics.c#L927">927</a>                 <a href="ident?i=change_nexthops">change_nexthops</a>(fi) {
<a name="L928" href="source/net/ipv4/fib_semantics.c#L928">928</a>                         <a href="ident?i=err">err</a> = <a href="ident?i=fib_check_nh">fib_check_nh</a>(<a href="ident?i=cfg">cfg</a>, fi, nexthop_nh);
<a name="L929" href="source/net/ipv4/fib_semantics.c#L929">929</a>                         if (<a href="ident?i=err">err</a> != 0)
<a name="L930" href="source/net/ipv4/fib_semantics.c#L930">930</a>                                 goto failure;
<a name="L931" href="source/net/ipv4/fib_semantics.c#L931">931</a>                 } <a href="ident?i=endfor_nexthops">endfor_nexthops</a>(fi)
<a name="L932" href="source/net/ipv4/fib_semantics.c#L932">932</a>         }
<a name="L933" href="source/net/ipv4/fib_semantics.c#L933">933</a> 
<a name="L934" href="source/net/ipv4/fib_semantics.c#L934">934</a>         if (fi-&gt;fib_prefsrc) {
<a name="L935" href="source/net/ipv4/fib_semantics.c#L935">935</a>                 if (<a href="ident?i=cfg">cfg</a>-&gt;<a href="ident?i=fc_type">fc_type</a> != RTN_LOCAL || !<a href="ident?i=cfg">cfg</a>-&gt;fc_dst ||
<a name="L936" href="source/net/ipv4/fib_semantics.c#L936">936</a>                     fi-&gt;fib_prefsrc != <a href="ident?i=cfg">cfg</a>-&gt;fc_dst)
<a name="L937" href="source/net/ipv4/fib_semantics.c#L937">937</a>                         if (<a href="ident?i=inet_addr_type">inet_addr_type</a>(<a href="ident?i=net">net</a>, fi-&gt;fib_prefsrc) != RTN_LOCAL)
<a name="L938" href="source/net/ipv4/fib_semantics.c#L938">938</a>                                 goto err_inval;
<a name="L939" href="source/net/ipv4/fib_semantics.c#L939">939</a>         }
<a name="L940" href="source/net/ipv4/fib_semantics.c#L940">940</a> 
<a name="L941" href="source/net/ipv4/fib_semantics.c#L941">941</a>         <a href="ident?i=change_nexthops">change_nexthops</a>(fi) {
<a name="L942" href="source/net/ipv4/fib_semantics.c#L942">942</a>                 <a href="ident?i=fib_info_update_nh_saddr">fib_info_update_nh_saddr</a>(<a href="ident?i=net">net</a>, nexthop_nh);
<a name="L943" href="source/net/ipv4/fib_semantics.c#L943">943</a>         } <a href="ident?i=endfor_nexthops">endfor_nexthops</a>(fi)
<a name="L944" href="source/net/ipv4/fib_semantics.c#L944">944</a> 
<a name="L945" href="source/net/ipv4/fib_semantics.c#L945">945</a> link_it:
<a name="L946" href="source/net/ipv4/fib_semantics.c#L946">946</a>         ofi = <a href="ident?i=fib_find_info">fib_find_info</a>(fi);
<a name="L947" href="source/net/ipv4/fib_semantics.c#L947">947</a>         if (ofi) {
<a name="L948" href="source/net/ipv4/fib_semantics.c#L948">948</a>                 fi-&gt;fib_dead = 1;
<a name="L949" href="source/net/ipv4/fib_semantics.c#L949">949</a>                 <a href="ident?i=free_fib_info">free_fib_info</a>(fi);
<a name="L950" href="source/net/ipv4/fib_semantics.c#L950">950</a>                 ofi-&gt;fib_treeref++;
<a name="L951" href="source/net/ipv4/fib_semantics.c#L951">951</a>                 return ofi;
<a name="L952" href="source/net/ipv4/fib_semantics.c#L952">952</a>         }
<a name="L953" href="source/net/ipv4/fib_semantics.c#L953">953</a> 
<a name="L954" href="source/net/ipv4/fib_semantics.c#L954">954</a>         fi-&gt;fib_treeref++;
<a name="L955" href="source/net/ipv4/fib_semantics.c#L955">955</a>         <a href="ident?i=atomic_inc">atomic_inc</a>(&amp;fi-&gt;fib_clntref);
<a name="L956" href="source/net/ipv4/fib_semantics.c#L956">956</a>         <a href="ident?i=spin_lock_bh">spin_lock_bh</a>(&amp;fib_info_lock);
<a name="L957" href="source/net/ipv4/fib_semantics.c#L957">957</a>         <a href="ident?i=hlist_add_head">hlist_add_head</a>(&amp;fi-&gt;fib_hash,
<a name="L958" href="source/net/ipv4/fib_semantics.c#L958">958</a>                        &amp;<a href="ident?i=fib_info_hash">fib_info_hash</a>[<a href="ident?i=fib_info_hashfn">fib_info_hashfn</a>(fi)]);
<a name="L959" href="source/net/ipv4/fib_semantics.c#L959">959</a>         if (fi-&gt;fib_prefsrc) {
<a name="L960" href="source/net/ipv4/fib_semantics.c#L960">960</a>                 struct <a href="ident?i=hlist_head">hlist_head</a> *<a href="ident?i=head">head</a>;
<a name="L961" href="source/net/ipv4/fib_semantics.c#L961">961</a> 
<a name="L962" href="source/net/ipv4/fib_semantics.c#L962">962</a>                 <a href="ident?i=head">head</a> = &amp;<a href="ident?i=fib_info_laddrhash">fib_info_laddrhash</a>[<a href="ident?i=fib_laddr_hashfn">fib_laddr_hashfn</a>(fi-&gt;fib_prefsrc)];
<a name="L963" href="source/net/ipv4/fib_semantics.c#L963">963</a>                 <a href="ident?i=hlist_add_head">hlist_add_head</a>(&amp;fi-&gt;fib_lhash, <a href="ident?i=head">head</a>);
<a name="L964" href="source/net/ipv4/fib_semantics.c#L964">964</a>         }
<a name="L965" href="source/net/ipv4/fib_semantics.c#L965">965</a>         <a href="ident?i=change_nexthops">change_nexthops</a>(fi) {
<a name="L966" href="source/net/ipv4/fib_semantics.c#L966">966</a>                 struct <a href="ident?i=hlist_head">hlist_head</a> *<a href="ident?i=head">head</a>;
<a name="L967" href="source/net/ipv4/fib_semantics.c#L967">967</a>                 unsigned int <a href="ident?i=hash">hash</a>;
<a name="L968" href="source/net/ipv4/fib_semantics.c#L968">968</a> 
<a name="L969" href="source/net/ipv4/fib_semantics.c#L969">969</a>                 if (!nexthop_nh-&gt;nh_dev)
<a name="L970" href="source/net/ipv4/fib_semantics.c#L970">970</a>                         continue;
<a name="L971" href="source/net/ipv4/fib_semantics.c#L971">971</a>                 <a href="ident?i=hash">hash</a> = <a href="ident?i=fib_devindex_hashfn">fib_devindex_hashfn</a>(nexthop_nh-&gt;nh_dev-&gt;ifindex);
<a name="L972" href="source/net/ipv4/fib_semantics.c#L972">972</a>                 <a href="ident?i=head">head</a> = &amp;<a href="ident?i=fib_info_devhash">fib_info_devhash</a>[<a href="ident?i=hash">hash</a>];
<a name="L973" href="source/net/ipv4/fib_semantics.c#L973">973</a>                 <a href="ident?i=hlist_add_head">hlist_add_head</a>(&amp;nexthop_nh-&gt;nh_hash, <a href="ident?i=head">head</a>);
<a name="L974" href="source/net/ipv4/fib_semantics.c#L974">974</a>         } <a href="ident?i=endfor_nexthops">endfor_nexthops</a>(fi)
<a name="L975" href="source/net/ipv4/fib_semantics.c#L975">975</a>         <a href="ident?i=spin_unlock_bh">spin_unlock_bh</a>(&amp;fib_info_lock);
<a name="L976" href="source/net/ipv4/fib_semantics.c#L976">976</a>         return fi;
<a name="L977" href="source/net/ipv4/fib_semantics.c#L977">977</a> 
<a name="L978" href="source/net/ipv4/fib_semantics.c#L978">978</a> err_inval:
<a name="L979" href="source/net/ipv4/fib_semantics.c#L979">979</a>         <a href="ident?i=err">err</a> = -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L980" href="source/net/ipv4/fib_semantics.c#L980">980</a> 
<a name="L981" href="source/net/ipv4/fib_semantics.c#L981">981</a> failure:
<a name="L982" href="source/net/ipv4/fib_semantics.c#L982">982</a>         if (fi) {
<a name="L983" href="source/net/ipv4/fib_semantics.c#L983">983</a>                 fi-&gt;fib_dead = 1;
<a name="L984" href="source/net/ipv4/fib_semantics.c#L984">984</a>                 <a href="ident?i=free_fib_info">free_fib_info</a>(fi);
<a name="L985" href="source/net/ipv4/fib_semantics.c#L985">985</a>         }
<a name="L986" href="source/net/ipv4/fib_semantics.c#L986">986</a> 
<a name="L987" href="source/net/ipv4/fib_semantics.c#L987">987</a>         return <a href="ident?i=ERR_PTR">ERR_PTR</a>(<a href="ident?i=err">err</a>);
<a name="L988" href="source/net/ipv4/fib_semantics.c#L988">988</a> }
<a name="L989" href="source/net/ipv4/fib_semantics.c#L989">989</a> 
<a name="L990" href="source/net/ipv4/fib_semantics.c#L990">990</a> int <a href="ident?i=fib_dump_info">fib_dump_info</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, <a href="ident?i=u32">u32</a> portid, <a href="ident?i=u32">u32</a> <a href="ident?i=seq">seq</a>, int <a href="ident?i=event">event</a>,
<a name="L991" href="source/net/ipv4/fib_semantics.c#L991">991</a>                   <a href="ident?i=u32">u32</a> tb_id, <a href="ident?i=u8">u8</a> <a href="ident?i=type">type</a>, <a href="ident?i=__be32">__be32</a> <a href="ident?i=dst">dst</a>, int dst_len, <a href="ident?i=u8">u8</a> tos,
<a name="L992" href="source/net/ipv4/fib_semantics.c#L992">992</a>                   struct <a href="ident?i=fib_info">fib_info</a> *fi, unsigned int <a href="ident?i=flags">flags</a>)
<a name="L993" href="source/net/ipv4/fib_semantics.c#L993">993</a> {
<a name="L994" href="source/net/ipv4/fib_semantics.c#L994">994</a>         struct <a href="ident?i=nlmsghdr">nlmsghdr</a> *nlh;
<a name="L995" href="source/net/ipv4/fib_semantics.c#L995">995</a>         struct <a href="ident?i=rtmsg">rtmsg</a> *rtm;
<a name="L996" href="source/net/ipv4/fib_semantics.c#L996">996</a> 
<a name="L997" href="source/net/ipv4/fib_semantics.c#L997">997</a>         nlh = <a href="ident?i=nlmsg_put">nlmsg_put</a>(<a href="ident?i=skb">skb</a>, portid, <a href="ident?i=seq">seq</a>, <a href="ident?i=event">event</a>, sizeof(*rtm), <a href="ident?i=flags">flags</a>);
<a name="L998" href="source/net/ipv4/fib_semantics.c#L998">998</a>         if (!nlh)
<a name="L999" href="source/net/ipv4/fib_semantics.c#L999">999</a>                 return -<a href="ident?i=EMSGSIZE">EMSGSIZE</a>;
<a name="L1000" href="source/net/ipv4/fib_semantics.c#L1000">1000</a> 
<a name="L1001" href="source/net/ipv4/fib_semantics.c#L1001">1001</a>         rtm = <a href="ident?i=nlmsg_data">nlmsg_data</a>(nlh);
<a name="L1002" href="source/net/ipv4/fib_semantics.c#L1002">1002</a>         rtm-&gt;rtm_family = <a href="ident?i=AF_INET">AF_INET</a>;
<a name="L1003" href="source/net/ipv4/fib_semantics.c#L1003">1003</a>         rtm-&gt;rtm_dst_len = dst_len;
<a name="L1004" href="source/net/ipv4/fib_semantics.c#L1004">1004</a>         rtm-&gt;rtm_src_len = 0;
<a name="L1005" href="source/net/ipv4/fib_semantics.c#L1005">1005</a>         rtm-&gt;rtm_tos = tos;
<a name="L1006" href="source/net/ipv4/fib_semantics.c#L1006">1006</a>         if (tb_id &lt; 256)
<a name="L1007" href="source/net/ipv4/fib_semantics.c#L1007">1007</a>                 rtm-&gt;rtm_table = tb_id;
<a name="L1008" href="source/net/ipv4/fib_semantics.c#L1008">1008</a>         else
<a name="L1009" href="source/net/ipv4/fib_semantics.c#L1009">1009</a>                 rtm-&gt;rtm_table = RT_TABLE_COMPAT;
<a name="L1010" href="source/net/ipv4/fib_semantics.c#L1010">1010</a>         if (<a href="ident?i=nla_put_u32">nla_put_u32</a>(<a href="ident?i=skb">skb</a>, RTA_TABLE, tb_id))
<a name="L1011" href="source/net/ipv4/fib_semantics.c#L1011">1011</a>                 goto nla_put_failure;
<a name="L1012" href="source/net/ipv4/fib_semantics.c#L1012">1012</a>         rtm-&gt;rtm_type = <a href="ident?i=type">type</a>;
<a name="L1013" href="source/net/ipv4/fib_semantics.c#L1013">1013</a>         rtm-&gt;rtm_flags = fi-&gt;fib_flags;
<a name="L1014" href="source/net/ipv4/fib_semantics.c#L1014">1014</a>         rtm-&gt;rtm_scope = fi-&gt;fib_scope;
<a name="L1015" href="source/net/ipv4/fib_semantics.c#L1015">1015</a>         rtm-&gt;rtm_protocol = fi-&gt;fib_protocol;
<a name="L1016" href="source/net/ipv4/fib_semantics.c#L1016">1016</a> 
<a name="L1017" href="source/net/ipv4/fib_semantics.c#L1017">1017</a>         if (rtm-&gt;rtm_dst_len &amp;&amp;
<a name="L1018" href="source/net/ipv4/fib_semantics.c#L1018">1018</a>             <a href="ident?i=nla_put_in_addr">nla_put_in_addr</a>(<a href="ident?i=skb">skb</a>, RTA_DST, <a href="ident?i=dst">dst</a>))
<a name="L1019" href="source/net/ipv4/fib_semantics.c#L1019">1019</a>                 goto nla_put_failure;
<a name="L1020" href="source/net/ipv4/fib_semantics.c#L1020">1020</a>         if (fi-&gt;fib_priority &amp;&amp;
<a name="L1021" href="source/net/ipv4/fib_semantics.c#L1021">1021</a>             <a href="ident?i=nla_put_u32">nla_put_u32</a>(<a href="ident?i=skb">skb</a>, RTA_PRIORITY, fi-&gt;fib_priority))
<a name="L1022" href="source/net/ipv4/fib_semantics.c#L1022">1022</a>                 goto nla_put_failure;
<a name="L1023" href="source/net/ipv4/fib_semantics.c#L1023">1023</a>         if (<a href="ident?i=rtnetlink_put_metrics">rtnetlink_put_metrics</a>(<a href="ident?i=skb">skb</a>, fi-&gt;fib_metrics) &lt; 0)
<a name="L1024" href="source/net/ipv4/fib_semantics.c#L1024">1024</a>                 goto nla_put_failure;
<a name="L1025" href="source/net/ipv4/fib_semantics.c#L1025">1025</a> 
<a name="L1026" href="source/net/ipv4/fib_semantics.c#L1026">1026</a>         if (fi-&gt;fib_prefsrc &amp;&amp;
<a name="L1027" href="source/net/ipv4/fib_semantics.c#L1027">1027</a>             <a href="ident?i=nla_put_in_addr">nla_put_in_addr</a>(<a href="ident?i=skb">skb</a>, RTA_PREFSRC, fi-&gt;fib_prefsrc))
<a name="L1028" href="source/net/ipv4/fib_semantics.c#L1028">1028</a>                 goto nla_put_failure;
<a name="L1029" href="source/net/ipv4/fib_semantics.c#L1029">1029</a>         if (fi-&gt;fib_nhs == 1) {
<a name="L1030" href="source/net/ipv4/fib_semantics.c#L1030">1030</a>                 if (fi-&gt;<a href="ident?i=fib_nh">fib_nh</a>-&gt;nh_gw &amp;&amp;
<a name="L1031" href="source/net/ipv4/fib_semantics.c#L1031">1031</a>                     <a href="ident?i=nla_put_in_addr">nla_put_in_addr</a>(<a href="ident?i=skb">skb</a>, RTA_GATEWAY, fi-&gt;<a href="ident?i=fib_nh">fib_nh</a>-&gt;nh_gw))
<a name="L1032" href="source/net/ipv4/fib_semantics.c#L1032">1032</a>                         goto nla_put_failure;
<a name="L1033" href="source/net/ipv4/fib_semantics.c#L1033">1033</a>                 if (fi-&gt;<a href="ident?i=fib_nh">fib_nh</a>-&gt;nh_oif &amp;&amp;
<a name="L1034" href="source/net/ipv4/fib_semantics.c#L1034">1034</a>                     <a href="ident?i=nla_put_u32">nla_put_u32</a>(<a href="ident?i=skb">skb</a>, RTA_OIF, fi-&gt;<a href="ident?i=fib_nh">fib_nh</a>-&gt;nh_oif))
<a name="L1035" href="source/net/ipv4/fib_semantics.c#L1035">1035</a>                         goto nla_put_failure;
<a name="L1036" href="source/net/ipv4/fib_semantics.c#L1036">1036</a> #ifdef CONFIG_IP_ROUTE_CLASSID
<a name="L1037" href="source/net/ipv4/fib_semantics.c#L1037">1037</a>                 if (fi-&gt;<a href="ident?i=fib_nh">fib_nh</a>[0].nh_tclassid &amp;&amp;
<a name="L1038" href="source/net/ipv4/fib_semantics.c#L1038">1038</a>                     <a href="ident?i=nla_put_u32">nla_put_u32</a>(<a href="ident?i=skb">skb</a>, RTA_FLOW, fi-&gt;<a href="ident?i=fib_nh">fib_nh</a>[0].nh_tclassid))
<a name="L1039" href="source/net/ipv4/fib_semantics.c#L1039">1039</a>                         goto nla_put_failure;
<a name="L1040" href="source/net/ipv4/fib_semantics.c#L1040">1040</a> #endif
<a name="L1041" href="source/net/ipv4/fib_semantics.c#L1041">1041</a>         }
<a name="L1042" href="source/net/ipv4/fib_semantics.c#L1042">1042</a> #ifdef CONFIG_IP_ROUTE_MULTIPATH
<a name="L1043" href="source/net/ipv4/fib_semantics.c#L1043">1043</a>         if (fi-&gt;fib_nhs &gt; 1) {
<a name="L1044" href="source/net/ipv4/fib_semantics.c#L1044">1044</a>                 struct <a href="ident?i=rtnexthop">rtnexthop</a> *rtnh;
<a name="L1045" href="source/net/ipv4/fib_semantics.c#L1045">1045</a>                 struct <a href="ident?i=nlattr">nlattr</a> *<a href="ident?i=mp">mp</a>;
<a name="L1046" href="source/net/ipv4/fib_semantics.c#L1046">1046</a> 
<a name="L1047" href="source/net/ipv4/fib_semantics.c#L1047">1047</a>                 <a href="ident?i=mp">mp</a> = <a href="ident?i=nla_nest_start">nla_nest_start</a>(<a href="ident?i=skb">skb</a>, RTA_MULTIPATH);
<a name="L1048" href="source/net/ipv4/fib_semantics.c#L1048">1048</a>                 if (!<a href="ident?i=mp">mp</a>)
<a name="L1049" href="source/net/ipv4/fib_semantics.c#L1049">1049</a>                         goto nla_put_failure;
<a name="L1050" href="source/net/ipv4/fib_semantics.c#L1050">1050</a> 
<a name="L1051" href="source/net/ipv4/fib_semantics.c#L1051">1051</a>                 <a href="ident?i=for_nexthops">for_nexthops</a>(fi) {
<a name="L1052" href="source/net/ipv4/fib_semantics.c#L1052">1052</a>                         rtnh = <a href="ident?i=nla_reserve_nohdr">nla_reserve_nohdr</a>(<a href="ident?i=skb">skb</a>, sizeof(*rtnh));
<a name="L1053" href="source/net/ipv4/fib_semantics.c#L1053">1053</a>                         if (!rtnh)
<a name="L1054" href="source/net/ipv4/fib_semantics.c#L1054">1054</a>                                 goto nla_put_failure;
<a name="L1055" href="source/net/ipv4/fib_semantics.c#L1055">1055</a> 
<a name="L1056" href="source/net/ipv4/fib_semantics.c#L1056">1056</a>                         rtnh-&gt;rtnh_flags = nh-&gt;nh_flags &amp; 0xFF;
<a name="L1057" href="source/net/ipv4/fib_semantics.c#L1057">1057</a>                         rtnh-&gt;rtnh_hops = nh-&gt;nh_weight - 1;
<a name="L1058" href="source/net/ipv4/fib_semantics.c#L1058">1058</a>                         rtnh-&gt;rtnh_ifindex = nh-&gt;nh_oif;
<a name="L1059" href="source/net/ipv4/fib_semantics.c#L1059">1059</a> 
<a name="L1060" href="source/net/ipv4/fib_semantics.c#L1060">1060</a>                         if (nh-&gt;nh_gw &amp;&amp;
<a name="L1061" href="source/net/ipv4/fib_semantics.c#L1061">1061</a>                             <a href="ident?i=nla_put_in_addr">nla_put_in_addr</a>(<a href="ident?i=skb">skb</a>, RTA_GATEWAY, nh-&gt;nh_gw))
<a name="L1062" href="source/net/ipv4/fib_semantics.c#L1062">1062</a>                                 goto nla_put_failure;
<a name="L1063" href="source/net/ipv4/fib_semantics.c#L1063">1063</a> #ifdef CONFIG_IP_ROUTE_CLASSID
<a name="L1064" href="source/net/ipv4/fib_semantics.c#L1064">1064</a>                         if (nh-&gt;nh_tclassid &amp;&amp;
<a name="L1065" href="source/net/ipv4/fib_semantics.c#L1065">1065</a>                             <a href="ident?i=nla_put_u32">nla_put_u32</a>(<a href="ident?i=skb">skb</a>, RTA_FLOW, nh-&gt;nh_tclassid))
<a name="L1066" href="source/net/ipv4/fib_semantics.c#L1066">1066</a>                                 goto nla_put_failure;
<a name="L1067" href="source/net/ipv4/fib_semantics.c#L1067">1067</a> #endif
<a name="L1068" href="source/net/ipv4/fib_semantics.c#L1068">1068</a>                         <b><i>/* length of rtnetlink header + attributes */</i></b>
<a name="L1069" href="source/net/ipv4/fib_semantics.c#L1069">1069</a>                         rtnh-&gt;rtnh_len = <a href="ident?i=nlmsg_get_pos">nlmsg_get_pos</a>(<a href="ident?i=skb">skb</a>) - (void *) rtnh;
<a name="L1070" href="source/net/ipv4/fib_semantics.c#L1070">1070</a>                 } <a href="ident?i=endfor_nexthops">endfor_nexthops</a>(fi);
<a name="L1071" href="source/net/ipv4/fib_semantics.c#L1071">1071</a> 
<a name="L1072" href="source/net/ipv4/fib_semantics.c#L1072">1072</a>                 <a href="ident?i=nla_nest_end">nla_nest_end</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=mp">mp</a>);
<a name="L1073" href="source/net/ipv4/fib_semantics.c#L1073">1073</a>         }
<a name="L1074" href="source/net/ipv4/fib_semantics.c#L1074">1074</a> #endif
<a name="L1075" href="source/net/ipv4/fib_semantics.c#L1075">1075</a>         <a href="ident?i=nlmsg_end">nlmsg_end</a>(<a href="ident?i=skb">skb</a>, nlh);
<a name="L1076" href="source/net/ipv4/fib_semantics.c#L1076">1076</a>         return 0;
<a name="L1077" href="source/net/ipv4/fib_semantics.c#L1077">1077</a> 
<a name="L1078" href="source/net/ipv4/fib_semantics.c#L1078">1078</a> nla_put_failure:
<a name="L1079" href="source/net/ipv4/fib_semantics.c#L1079">1079</a>         <a href="ident?i=nlmsg_cancel">nlmsg_cancel</a>(<a href="ident?i=skb">skb</a>, nlh);
<a name="L1080" href="source/net/ipv4/fib_semantics.c#L1080">1080</a>         return -<a href="ident?i=EMSGSIZE">EMSGSIZE</a>;
<a name="L1081" href="source/net/ipv4/fib_semantics.c#L1081">1081</a> }
<a name="L1082" href="source/net/ipv4/fib_semantics.c#L1082">1082</a> 
<a name="L1083" href="source/net/ipv4/fib_semantics.c#L1083">1083</a> <b><i>/*</i></b>
<a name="L1084" href="source/net/ipv4/fib_semantics.c#L1084">1084</a> <b><i> * Update FIB if:</i></b>
<a name="L1085" href="source/net/ipv4/fib_semantics.c#L1085">1085</a> <b><i> * - local address disappeared -&gt; we must delete all the entries</i></b>
<a name="L1086" href="source/net/ipv4/fib_semantics.c#L1086">1086</a> <b><i> *   referring to it.</i></b>
<a name="L1087" href="source/net/ipv4/fib_semantics.c#L1087">1087</a> <b><i> * - device went down -&gt; we must shutdown all nexthops going via it.</i></b>
<a name="L1088" href="source/net/ipv4/fib_semantics.c#L1088">1088</a> <b><i> */</i></b>
<a name="L1089" href="source/net/ipv4/fib_semantics.c#L1089">1089</a> int <a href="ident?i=fib_sync_down_addr">fib_sync_down_addr</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>, <a href="ident?i=__be32">__be32</a> local)
<a name="L1090" href="source/net/ipv4/fib_semantics.c#L1090">1090</a> {
<a name="L1091" href="source/net/ipv4/fib_semantics.c#L1091">1091</a>         int <a href="ident?i=ret">ret</a> = 0;
<a name="L1092" href="source/net/ipv4/fib_semantics.c#L1092">1092</a>         unsigned int <a href="ident?i=hash">hash</a> = <a href="ident?i=fib_laddr_hashfn">fib_laddr_hashfn</a>(local);
<a name="L1093" href="source/net/ipv4/fib_semantics.c#L1093">1093</a>         struct <a href="ident?i=hlist_head">hlist_head</a> *<a href="ident?i=head">head</a> = &amp;<a href="ident?i=fib_info_laddrhash">fib_info_laddrhash</a>[<a href="ident?i=hash">hash</a>];
<a name="L1094" href="source/net/ipv4/fib_semantics.c#L1094">1094</a>         struct <a href="ident?i=fib_info">fib_info</a> *fi;
<a name="L1095" href="source/net/ipv4/fib_semantics.c#L1095">1095</a> 
<a name="L1096" href="source/net/ipv4/fib_semantics.c#L1096">1096</a>         if (!<a href="ident?i=fib_info_laddrhash">fib_info_laddrhash</a> || local == 0)
<a name="L1097" href="source/net/ipv4/fib_semantics.c#L1097">1097</a>                 return 0;
<a name="L1098" href="source/net/ipv4/fib_semantics.c#L1098">1098</a> 
<a name="L1099" href="source/net/ipv4/fib_semantics.c#L1099">1099</a>         <a href="ident?i=hlist_for_each_entry">hlist_for_each_entry</a>(fi, <a href="ident?i=head">head</a>, fib_lhash) {
<a name="L1100" href="source/net/ipv4/fib_semantics.c#L1100">1100</a>                 if (!<a href="ident?i=net_eq">net_eq</a>(fi-&gt;fib_net, <a href="ident?i=net">net</a>))
<a name="L1101" href="source/net/ipv4/fib_semantics.c#L1101">1101</a>                         continue;
<a name="L1102" href="source/net/ipv4/fib_semantics.c#L1102">1102</a>                 if (fi-&gt;fib_prefsrc == local) {
<a name="L1103" href="source/net/ipv4/fib_semantics.c#L1103">1103</a>                         fi-&gt;fib_flags |= <a href="ident?i=RTNH_F_DEAD">RTNH_F_DEAD</a>;
<a name="L1104" href="source/net/ipv4/fib_semantics.c#L1104">1104</a>                         <a href="ident?i=ret">ret</a>++;
<a name="L1105" href="source/net/ipv4/fib_semantics.c#L1105">1105</a>                 }
<a name="L1106" href="source/net/ipv4/fib_semantics.c#L1106">1106</a>         }
<a name="L1107" href="source/net/ipv4/fib_semantics.c#L1107">1107</a>         return <a href="ident?i=ret">ret</a>;
<a name="L1108" href="source/net/ipv4/fib_semantics.c#L1108">1108</a> }
<a name="L1109" href="source/net/ipv4/fib_semantics.c#L1109">1109</a> 
<a name="L1110" href="source/net/ipv4/fib_semantics.c#L1110">1110</a> int <a href="ident?i=fib_sync_down_dev">fib_sync_down_dev</a>(struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>, int <a href="ident?i=force">force</a>)
<a name="L1111" href="source/net/ipv4/fib_semantics.c#L1111">1111</a> {
<a name="L1112" href="source/net/ipv4/fib_semantics.c#L1112">1112</a>         int <a href="ident?i=ret">ret</a> = 0;
<a name="L1113" href="source/net/ipv4/fib_semantics.c#L1113">1113</a>         int <a href="ident?i=scope">scope</a> = RT_SCOPE_NOWHERE;
<a name="L1114" href="source/net/ipv4/fib_semantics.c#L1114">1114</a>         struct <a href="ident?i=fib_info">fib_info</a> *prev_fi = <a href="ident?i=NULL">NULL</a>;
<a name="L1115" href="source/net/ipv4/fib_semantics.c#L1115">1115</a>         unsigned int <a href="ident?i=hash">hash</a> = <a href="ident?i=fib_devindex_hashfn">fib_devindex_hashfn</a>(<a href="ident?i=dev">dev</a>-&gt;ifindex);
<a name="L1116" href="source/net/ipv4/fib_semantics.c#L1116">1116</a>         struct <a href="ident?i=hlist_head">hlist_head</a> *<a href="ident?i=head">head</a> = &amp;<a href="ident?i=fib_info_devhash">fib_info_devhash</a>[<a href="ident?i=hash">hash</a>];
<a name="L1117" href="source/net/ipv4/fib_semantics.c#L1117">1117</a>         struct <a href="ident?i=fib_nh">fib_nh</a> *nh;
<a name="L1118" href="source/net/ipv4/fib_semantics.c#L1118">1118</a> 
<a name="L1119" href="source/net/ipv4/fib_semantics.c#L1119">1119</a>         if (<a href="ident?i=force">force</a>)
<a name="L1120" href="source/net/ipv4/fib_semantics.c#L1120">1120</a>                 <a href="ident?i=scope">scope</a> = -1;
<a name="L1121" href="source/net/ipv4/fib_semantics.c#L1121">1121</a> 
<a name="L1122" href="source/net/ipv4/fib_semantics.c#L1122">1122</a>         <a href="ident?i=hlist_for_each_entry">hlist_for_each_entry</a>(nh, <a href="ident?i=head">head</a>, nh_hash) {
<a name="L1123" href="source/net/ipv4/fib_semantics.c#L1123">1123</a>                 struct <a href="ident?i=fib_info">fib_info</a> *fi = nh-&gt;nh_parent;
<a name="L1124" href="source/net/ipv4/fib_semantics.c#L1124">1124</a>                 int dead;
<a name="L1125" href="source/net/ipv4/fib_semantics.c#L1125">1125</a> 
<a name="L1126" href="source/net/ipv4/fib_semantics.c#L1126">1126</a>                 <a href="ident?i=BUG_ON">BUG_ON</a>(!fi-&gt;fib_nhs);
<a name="L1127" href="source/net/ipv4/fib_semantics.c#L1127">1127</a>                 if (nh-&gt;nh_dev != <a href="ident?i=dev">dev</a> || fi == prev_fi)
<a name="L1128" href="source/net/ipv4/fib_semantics.c#L1128">1128</a>                         continue;
<a name="L1129" href="source/net/ipv4/fib_semantics.c#L1129">1129</a>                 prev_fi = fi;
<a name="L1130" href="source/net/ipv4/fib_semantics.c#L1130">1130</a>                 dead = 0;
<a name="L1131" href="source/net/ipv4/fib_semantics.c#L1131">1131</a>                 <a href="ident?i=change_nexthops">change_nexthops</a>(fi) {
<a name="L1132" href="source/net/ipv4/fib_semantics.c#L1132">1132</a>                         if (nexthop_nh-&gt;nh_flags &amp; <a href="ident?i=RTNH_F_DEAD">RTNH_F_DEAD</a>)
<a name="L1133" href="source/net/ipv4/fib_semantics.c#L1133">1133</a>                                 dead++;
<a name="L1134" href="source/net/ipv4/fib_semantics.c#L1134">1134</a>                         else if (nexthop_nh-&gt;nh_dev == <a href="ident?i=dev">dev</a> &amp;&amp;
<a name="L1135" href="source/net/ipv4/fib_semantics.c#L1135">1135</a>                                  nexthop_nh-&gt;nh_scope != <a href="ident?i=scope">scope</a>) {
<a name="L1136" href="source/net/ipv4/fib_semantics.c#L1136">1136</a>                                 nexthop_nh-&gt;nh_flags |= <a href="ident?i=RTNH_F_DEAD">RTNH_F_DEAD</a>;
<a name="L1137" href="source/net/ipv4/fib_semantics.c#L1137">1137</a> #ifdef CONFIG_IP_ROUTE_MULTIPATH
<a name="L1138" href="source/net/ipv4/fib_semantics.c#L1138">1138</a>                                 <a href="ident?i=spin_lock_bh">spin_lock_bh</a>(&amp;fib_multipath_lock);
<a name="L1139" href="source/net/ipv4/fib_semantics.c#L1139">1139</a>                                 fi-&gt;fib_power -= nexthop_nh-&gt;nh_power;
<a name="L1140" href="source/net/ipv4/fib_semantics.c#L1140">1140</a>                                 nexthop_nh-&gt;nh_power = 0;
<a name="L1141" href="source/net/ipv4/fib_semantics.c#L1141">1141</a>                                 <a href="ident?i=spin_unlock_bh">spin_unlock_bh</a>(&amp;fib_multipath_lock);
<a name="L1142" href="source/net/ipv4/fib_semantics.c#L1142">1142</a> #endif
<a name="L1143" href="source/net/ipv4/fib_semantics.c#L1143">1143</a>                                 dead++;
<a name="L1144" href="source/net/ipv4/fib_semantics.c#L1144">1144</a>                         }
<a name="L1145" href="source/net/ipv4/fib_semantics.c#L1145">1145</a> #ifdef CONFIG_IP_ROUTE_MULTIPATH
<a name="L1146" href="source/net/ipv4/fib_semantics.c#L1146">1146</a>                         if (<a href="ident?i=force">force</a> &gt; 1 &amp;&amp; nexthop_nh-&gt;nh_dev == <a href="ident?i=dev">dev</a>) {
<a name="L1147" href="source/net/ipv4/fib_semantics.c#L1147">1147</a>                                 dead = fi-&gt;fib_nhs;
<a name="L1148" href="source/net/ipv4/fib_semantics.c#L1148">1148</a>                                 break;
<a name="L1149" href="source/net/ipv4/fib_semantics.c#L1149">1149</a>                         }
<a name="L1150" href="source/net/ipv4/fib_semantics.c#L1150">1150</a> #endif
<a name="L1151" href="source/net/ipv4/fib_semantics.c#L1151">1151</a>                 } <a href="ident?i=endfor_nexthops">endfor_nexthops</a>(fi)
<a name="L1152" href="source/net/ipv4/fib_semantics.c#L1152">1152</a>                 if (dead == fi-&gt;fib_nhs) {
<a name="L1153" href="source/net/ipv4/fib_semantics.c#L1153">1153</a>                         fi-&gt;fib_flags |= <a href="ident?i=RTNH_F_DEAD">RTNH_F_DEAD</a>;
<a name="L1154" href="source/net/ipv4/fib_semantics.c#L1154">1154</a>                         <a href="ident?i=ret">ret</a>++;
<a name="L1155" href="source/net/ipv4/fib_semantics.c#L1155">1155</a>                 }
<a name="L1156" href="source/net/ipv4/fib_semantics.c#L1156">1156</a>         }
<a name="L1157" href="source/net/ipv4/fib_semantics.c#L1157">1157</a> 
<a name="L1158" href="source/net/ipv4/fib_semantics.c#L1158">1158</a>         return <a href="ident?i=ret">ret</a>;
<a name="L1159" href="source/net/ipv4/fib_semantics.c#L1159">1159</a> }
<a name="L1160" href="source/net/ipv4/fib_semantics.c#L1160">1160</a> 
<a name="L1161" href="source/net/ipv4/fib_semantics.c#L1161">1161</a> <b><i>/* Must be invoked inside of an RCU protected region.  */</i></b>
<a name="L1162" href="source/net/ipv4/fib_semantics.c#L1162">1162</a> void <a href="ident?i=fib_select_default">fib_select_default</a>(struct <a href="ident?i=fib_result">fib_result</a> *<a href="ident?i=res">res</a>)
<a name="L1163" href="source/net/ipv4/fib_semantics.c#L1163">1163</a> {
<a name="L1164" href="source/net/ipv4/fib_semantics.c#L1164">1164</a>         struct <a href="ident?i=fib_info">fib_info</a> *fi = <a href="ident?i=NULL">NULL</a>, *last_resort = <a href="ident?i=NULL">NULL</a>;
<a name="L1165" href="source/net/ipv4/fib_semantics.c#L1165">1165</a>         struct <a href="ident?i=hlist_head">hlist_head</a> *fa_head = <a href="ident?i=res">res</a>-&gt;fa_head;
<a name="L1166" href="source/net/ipv4/fib_semantics.c#L1166">1166</a>         struct <a href="ident?i=fib_table">fib_table</a> *<a href="ident?i=tb">tb</a> = <a href="ident?i=res">res</a>-&gt;<a href="ident?i=table">table</a>;
<a name="L1167" href="source/net/ipv4/fib_semantics.c#L1167">1167</a>         int order = -1, last_idx = -1;
<a name="L1168" href="source/net/ipv4/fib_semantics.c#L1168">1168</a>         struct <a href="ident?i=fib_alias">fib_alias</a> *fa;
<a name="L1169" href="source/net/ipv4/fib_semantics.c#L1169">1169</a> 
<a name="L1170" href="source/net/ipv4/fib_semantics.c#L1170">1170</a>         <a href="ident?i=hlist_for_each_entry_rcu">hlist_for_each_entry_rcu</a>(fa, fa_head, fa_list) {
<a name="L1171" href="source/net/ipv4/fib_semantics.c#L1171">1171</a>                 struct <a href="ident?i=fib_info">fib_info</a> *next_fi = fa-&gt;fa_info;
<a name="L1172" href="source/net/ipv4/fib_semantics.c#L1172">1172</a> 
<a name="L1173" href="source/net/ipv4/fib_semantics.c#L1173">1173</a>                 if (next_fi-&gt;fib_scope != <a href="ident?i=res">res</a>-&gt;<a href="ident?i=scope">scope</a> ||
<a name="L1174" href="source/net/ipv4/fib_semantics.c#L1174">1174</a>                     fa-&gt;fa_type != RTN_UNICAST)
<a name="L1175" href="source/net/ipv4/fib_semantics.c#L1175">1175</a>                         continue;
<a name="L1176" href="source/net/ipv4/fib_semantics.c#L1176">1176</a> 
<a name="L1177" href="source/net/ipv4/fib_semantics.c#L1177">1177</a>                 if (next_fi-&gt;fib_priority &gt; <a href="ident?i=res">res</a>-&gt;fi-&gt;fib_priority)
<a name="L1178" href="source/net/ipv4/fib_semantics.c#L1178">1178</a>                         break;
<a name="L1179" href="source/net/ipv4/fib_semantics.c#L1179">1179</a>                 if (!next_fi-&gt;<a href="ident?i=fib_nh">fib_nh</a>[0].nh_gw ||
<a name="L1180" href="source/net/ipv4/fib_semantics.c#L1180">1180</a>                     next_fi-&gt;<a href="ident?i=fib_nh">fib_nh</a>[0].nh_scope != RT_SCOPE_LINK)
<a name="L1181" href="source/net/ipv4/fib_semantics.c#L1181">1181</a>                         continue;
<a name="L1182" href="source/net/ipv4/fib_semantics.c#L1182">1182</a> 
<a name="L1183" href="source/net/ipv4/fib_semantics.c#L1183">1183</a>                 <a href="ident?i=fib_alias_accessed">fib_alias_accessed</a>(fa);
<a name="L1184" href="source/net/ipv4/fib_semantics.c#L1184">1184</a> 
<a name="L1185" href="source/net/ipv4/fib_semantics.c#L1185">1185</a>                 if (!fi) {
<a name="L1186" href="source/net/ipv4/fib_semantics.c#L1186">1186</a>                         if (next_fi != <a href="ident?i=res">res</a>-&gt;fi)
<a name="L1187" href="source/net/ipv4/fib_semantics.c#L1187">1187</a>                                 break;
<a name="L1188" href="source/net/ipv4/fib_semantics.c#L1188">1188</a>                 } else if (!<a href="ident?i=fib_detect_death">fib_detect_death</a>(fi, order, &amp;last_resort,
<a name="L1189" href="source/net/ipv4/fib_semantics.c#L1189">1189</a>                                              &amp;last_idx, <a href="ident?i=tb">tb</a>-&gt;tb_default)) {
<a name="L1190" href="source/net/ipv4/fib_semantics.c#L1190">1190</a>                         <a href="ident?i=fib_result_assign">fib_result_assign</a>(<a href="ident?i=res">res</a>, fi);
<a name="L1191" href="source/net/ipv4/fib_semantics.c#L1191">1191</a>                         <a href="ident?i=tb">tb</a>-&gt;tb_default = order;
<a name="L1192" href="source/net/ipv4/fib_semantics.c#L1192">1192</a>                         goto <a href="ident?i=out">out</a>;
<a name="L1193" href="source/net/ipv4/fib_semantics.c#L1193">1193</a>                 }
<a name="L1194" href="source/net/ipv4/fib_semantics.c#L1194">1194</a>                 fi = next_fi;
<a name="L1195" href="source/net/ipv4/fib_semantics.c#L1195">1195</a>                 order++;
<a name="L1196" href="source/net/ipv4/fib_semantics.c#L1196">1196</a>         }
<a name="L1197" href="source/net/ipv4/fib_semantics.c#L1197">1197</a> 
<a name="L1198" href="source/net/ipv4/fib_semantics.c#L1198">1198</a>         if (order &lt;= 0 || !fi) {
<a name="L1199" href="source/net/ipv4/fib_semantics.c#L1199">1199</a>                 <a href="ident?i=tb">tb</a>-&gt;tb_default = -1;
<a name="L1200" href="source/net/ipv4/fib_semantics.c#L1200">1200</a>                 goto <a href="ident?i=out">out</a>;
<a name="L1201" href="source/net/ipv4/fib_semantics.c#L1201">1201</a>         }
<a name="L1202" href="source/net/ipv4/fib_semantics.c#L1202">1202</a> 
<a name="L1203" href="source/net/ipv4/fib_semantics.c#L1203">1203</a>         if (!<a href="ident?i=fib_detect_death">fib_detect_death</a>(fi, order, &amp;last_resort, &amp;last_idx,
<a name="L1204" href="source/net/ipv4/fib_semantics.c#L1204">1204</a>                                 <a href="ident?i=tb">tb</a>-&gt;tb_default)) {
<a name="L1205" href="source/net/ipv4/fib_semantics.c#L1205">1205</a>                 <a href="ident?i=fib_result_assign">fib_result_assign</a>(<a href="ident?i=res">res</a>, fi);
<a name="L1206" href="source/net/ipv4/fib_semantics.c#L1206">1206</a>                 <a href="ident?i=tb">tb</a>-&gt;tb_default = order;
<a name="L1207" href="source/net/ipv4/fib_semantics.c#L1207">1207</a>                 goto <a href="ident?i=out">out</a>;
<a name="L1208" href="source/net/ipv4/fib_semantics.c#L1208">1208</a>         }
<a name="L1209" href="source/net/ipv4/fib_semantics.c#L1209">1209</a> 
<a name="L1210" href="source/net/ipv4/fib_semantics.c#L1210">1210</a>         if (last_idx &gt;= 0)
<a name="L1211" href="source/net/ipv4/fib_semantics.c#L1211">1211</a>                 <a href="ident?i=fib_result_assign">fib_result_assign</a>(<a href="ident?i=res">res</a>, last_resort);
<a name="L1212" href="source/net/ipv4/fib_semantics.c#L1212">1212</a>         <a href="ident?i=tb">tb</a>-&gt;tb_default = last_idx;
<a name="L1213" href="source/net/ipv4/fib_semantics.c#L1213">1213</a> <a href="ident?i=out">out</a>:
<a name="L1214" href="source/net/ipv4/fib_semantics.c#L1214">1214</a>         return;
<a name="L1215" href="source/net/ipv4/fib_semantics.c#L1215">1215</a> }
<a name="L1216" href="source/net/ipv4/fib_semantics.c#L1216">1216</a> 
<a name="L1217" href="source/net/ipv4/fib_semantics.c#L1217">1217</a> #ifdef CONFIG_IP_ROUTE_MULTIPATH
<a name="L1218" href="source/net/ipv4/fib_semantics.c#L1218">1218</a> 
<a name="L1219" href="source/net/ipv4/fib_semantics.c#L1219">1219</a> <b><i>/*</i></b>
<a name="L1220" href="source/net/ipv4/fib_semantics.c#L1220">1220</a> <b><i> * Dead device goes up. We wake up dead nexthops.</i></b>
<a name="L1221" href="source/net/ipv4/fib_semantics.c#L1221">1221</a> <b><i> * It takes sense only on multipath routes.</i></b>
<a name="L1222" href="source/net/ipv4/fib_semantics.c#L1222">1222</a> <b><i> */</i></b>
<a name="L1223" href="source/net/ipv4/fib_semantics.c#L1223">1223</a> int <a href="ident?i=fib_sync_up">fib_sync_up</a>(struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>)
<a name="L1224" href="source/net/ipv4/fib_semantics.c#L1224">1224</a> {
<a name="L1225" href="source/net/ipv4/fib_semantics.c#L1225">1225</a>         struct <a href="ident?i=fib_info">fib_info</a> *prev_fi;
<a name="L1226" href="source/net/ipv4/fib_semantics.c#L1226">1226</a>         unsigned int <a href="ident?i=hash">hash</a>;
<a name="L1227" href="source/net/ipv4/fib_semantics.c#L1227">1227</a>         struct <a href="ident?i=hlist_head">hlist_head</a> *<a href="ident?i=head">head</a>;
<a name="L1228" href="source/net/ipv4/fib_semantics.c#L1228">1228</a>         struct <a href="ident?i=fib_nh">fib_nh</a> *nh;
<a name="L1229" href="source/net/ipv4/fib_semantics.c#L1229">1229</a>         int <a href="ident?i=ret">ret</a>;
<a name="L1230" href="source/net/ipv4/fib_semantics.c#L1230">1230</a> 
<a name="L1231" href="source/net/ipv4/fib_semantics.c#L1231">1231</a>         if (!(<a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=IFF_UP">IFF_UP</a>))
<a name="L1232" href="source/net/ipv4/fib_semantics.c#L1232">1232</a>                 return 0;
<a name="L1233" href="source/net/ipv4/fib_semantics.c#L1233">1233</a> 
<a name="L1234" href="source/net/ipv4/fib_semantics.c#L1234">1234</a>         prev_fi = <a href="ident?i=NULL">NULL</a>;
<a name="L1235" href="source/net/ipv4/fib_semantics.c#L1235">1235</a>         <a href="ident?i=hash">hash</a> = <a href="ident?i=fib_devindex_hashfn">fib_devindex_hashfn</a>(<a href="ident?i=dev">dev</a>-&gt;ifindex);
<a name="L1236" href="source/net/ipv4/fib_semantics.c#L1236">1236</a>         <a href="ident?i=head">head</a> = &amp;<a href="ident?i=fib_info_devhash">fib_info_devhash</a>[<a href="ident?i=hash">hash</a>];
<a name="L1237" href="source/net/ipv4/fib_semantics.c#L1237">1237</a>         <a href="ident?i=ret">ret</a> = 0;
<a name="L1238" href="source/net/ipv4/fib_semantics.c#L1238">1238</a> 
<a name="L1239" href="source/net/ipv4/fib_semantics.c#L1239">1239</a>         <a href="ident?i=hlist_for_each_entry">hlist_for_each_entry</a>(nh, <a href="ident?i=head">head</a>, nh_hash) {
<a name="L1240" href="source/net/ipv4/fib_semantics.c#L1240">1240</a>                 struct <a href="ident?i=fib_info">fib_info</a> *fi = nh-&gt;nh_parent;
<a name="L1241" href="source/net/ipv4/fib_semantics.c#L1241">1241</a>                 int alive;
<a name="L1242" href="source/net/ipv4/fib_semantics.c#L1242">1242</a> 
<a name="L1243" href="source/net/ipv4/fib_semantics.c#L1243">1243</a>                 <a href="ident?i=BUG_ON">BUG_ON</a>(!fi-&gt;fib_nhs);
<a name="L1244" href="source/net/ipv4/fib_semantics.c#L1244">1244</a>                 if (nh-&gt;nh_dev != <a href="ident?i=dev">dev</a> || fi == prev_fi)
<a name="L1245" href="source/net/ipv4/fib_semantics.c#L1245">1245</a>                         continue;
<a name="L1246" href="source/net/ipv4/fib_semantics.c#L1246">1246</a> 
<a name="L1247" href="source/net/ipv4/fib_semantics.c#L1247">1247</a>                 prev_fi = fi;
<a name="L1248" href="source/net/ipv4/fib_semantics.c#L1248">1248</a>                 alive = 0;
<a name="L1249" href="source/net/ipv4/fib_semantics.c#L1249">1249</a>                 <a href="ident?i=change_nexthops">change_nexthops</a>(fi) {
<a name="L1250" href="source/net/ipv4/fib_semantics.c#L1250">1250</a>                         if (!(nexthop_nh-&gt;nh_flags &amp; <a href="ident?i=RTNH_F_DEAD">RTNH_F_DEAD</a>)) {
<a name="L1251" href="source/net/ipv4/fib_semantics.c#L1251">1251</a>                                 alive++;
<a name="L1252" href="source/net/ipv4/fib_semantics.c#L1252">1252</a>                                 continue;
<a name="L1253" href="source/net/ipv4/fib_semantics.c#L1253">1253</a>                         }
<a name="L1254" href="source/net/ipv4/fib_semantics.c#L1254">1254</a>                         if (!nexthop_nh-&gt;nh_dev ||
<a name="L1255" href="source/net/ipv4/fib_semantics.c#L1255">1255</a>                             !(nexthop_nh-&gt;nh_dev-&gt;<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=IFF_UP">IFF_UP</a>))
<a name="L1256" href="source/net/ipv4/fib_semantics.c#L1256">1256</a>                                 continue;
<a name="L1257" href="source/net/ipv4/fib_semantics.c#L1257">1257</a>                         if (nexthop_nh-&gt;nh_dev != <a href="ident?i=dev">dev</a> ||
<a name="L1258" href="source/net/ipv4/fib_semantics.c#L1258">1258</a>                             !<a href="ident?i=__in_dev_get_rtnl">__in_dev_get_rtnl</a>(<a href="ident?i=dev">dev</a>))
<a name="L1259" href="source/net/ipv4/fib_semantics.c#L1259">1259</a>                                 continue;
<a name="L1260" href="source/net/ipv4/fib_semantics.c#L1260">1260</a>                         alive++;
<a name="L1261" href="source/net/ipv4/fib_semantics.c#L1261">1261</a>                         <a href="ident?i=spin_lock_bh">spin_lock_bh</a>(&amp;fib_multipath_lock);
<a name="L1262" href="source/net/ipv4/fib_semantics.c#L1262">1262</a>                         nexthop_nh-&gt;nh_power = 0;
<a name="L1263" href="source/net/ipv4/fib_semantics.c#L1263">1263</a>                         nexthop_nh-&gt;nh_flags &amp;= ~RTNH_F_DEAD;
<a name="L1264" href="source/net/ipv4/fib_semantics.c#L1264">1264</a>                         <a href="ident?i=spin_unlock_bh">spin_unlock_bh</a>(&amp;fib_multipath_lock);
<a name="L1265" href="source/net/ipv4/fib_semantics.c#L1265">1265</a>                 } <a href="ident?i=endfor_nexthops">endfor_nexthops</a>(fi)
<a name="L1266" href="source/net/ipv4/fib_semantics.c#L1266">1266</a> 
<a name="L1267" href="source/net/ipv4/fib_semantics.c#L1267">1267</a>                 if (alive &gt; 0) {
<a name="L1268" href="source/net/ipv4/fib_semantics.c#L1268">1268</a>                         fi-&gt;fib_flags &amp;= ~RTNH_F_DEAD;
<a name="L1269" href="source/net/ipv4/fib_semantics.c#L1269">1269</a>                         <a href="ident?i=ret">ret</a>++;
<a name="L1270" href="source/net/ipv4/fib_semantics.c#L1270">1270</a>                 }
<a name="L1271" href="source/net/ipv4/fib_semantics.c#L1271">1271</a>         }
<a name="L1272" href="source/net/ipv4/fib_semantics.c#L1272">1272</a> 
<a name="L1273" href="source/net/ipv4/fib_semantics.c#L1273">1273</a>         return <a href="ident?i=ret">ret</a>;
<a name="L1274" href="source/net/ipv4/fib_semantics.c#L1274">1274</a> }
<a name="L1275" href="source/net/ipv4/fib_semantics.c#L1275">1275</a> 
<a name="L1276" href="source/net/ipv4/fib_semantics.c#L1276">1276</a> <b><i>/*</i></b>
<a name="L1277" href="source/net/ipv4/fib_semantics.c#L1277">1277</a> <b><i> * The algorithm is suboptimal, but it provides really</i></b>
<a name="L1278" href="source/net/ipv4/fib_semantics.c#L1278">1278</a> <b><i> * fair weighted route distribution.</i></b>
<a name="L1279" href="source/net/ipv4/fib_semantics.c#L1279">1279</a> <b><i> */</i></b>
<a name="L1280" href="source/net/ipv4/fib_semantics.c#L1280">1280</a> void <a href="ident?i=fib_select_multipath">fib_select_multipath</a>(struct <a href="ident?i=fib_result">fib_result</a> *<a href="ident?i=res">res</a>)
<a name="L1281" href="source/net/ipv4/fib_semantics.c#L1281">1281</a> {
<a name="L1282" href="source/net/ipv4/fib_semantics.c#L1282">1282</a>         struct <a href="ident?i=fib_info">fib_info</a> *fi = <a href="ident?i=res">res</a>-&gt;fi;
<a name="L1283" href="source/net/ipv4/fib_semantics.c#L1283">1283</a>         int <a href="ident?i=w">w</a>;
<a name="L1284" href="source/net/ipv4/fib_semantics.c#L1284">1284</a> 
<a name="L1285" href="source/net/ipv4/fib_semantics.c#L1285">1285</a>         <a href="ident?i=spin_lock_bh">spin_lock_bh</a>(&amp;fib_multipath_lock);
<a name="L1286" href="source/net/ipv4/fib_semantics.c#L1286">1286</a>         if (fi-&gt;fib_power &lt;= 0) {
<a name="L1287" href="source/net/ipv4/fib_semantics.c#L1287">1287</a>                 int <a href="ident?i=power">power</a> = 0;
<a name="L1288" href="source/net/ipv4/fib_semantics.c#L1288">1288</a>                 <a href="ident?i=change_nexthops">change_nexthops</a>(fi) {
<a name="L1289" href="source/net/ipv4/fib_semantics.c#L1289">1289</a>                         if (!(nexthop_nh-&gt;nh_flags &amp; <a href="ident?i=RTNH_F_DEAD">RTNH_F_DEAD</a>)) {
<a name="L1290" href="source/net/ipv4/fib_semantics.c#L1290">1290</a>                                 <a href="ident?i=power">power</a> += nexthop_nh-&gt;nh_weight;
<a name="L1291" href="source/net/ipv4/fib_semantics.c#L1291">1291</a>                                 nexthop_nh-&gt;nh_power = nexthop_nh-&gt;nh_weight;
<a name="L1292" href="source/net/ipv4/fib_semantics.c#L1292">1292</a>                         }
<a name="L1293" href="source/net/ipv4/fib_semantics.c#L1293">1293</a>                 } <a href="ident?i=endfor_nexthops">endfor_nexthops</a>(fi);
<a name="L1294" href="source/net/ipv4/fib_semantics.c#L1294">1294</a>                 fi-&gt;fib_power = <a href="ident?i=power">power</a>;
<a name="L1295" href="source/net/ipv4/fib_semantics.c#L1295">1295</a>                 if (<a href="ident?i=power">power</a> &lt;= 0) {
<a name="L1296" href="source/net/ipv4/fib_semantics.c#L1296">1296</a>                         <a href="ident?i=spin_unlock_bh">spin_unlock_bh</a>(&amp;fib_multipath_lock);
<a name="L1297" href="source/net/ipv4/fib_semantics.c#L1297">1297</a>                         <b><i>/* Race condition: route has just become dead. */</i></b>
<a name="L1298" href="source/net/ipv4/fib_semantics.c#L1298">1298</a>                         <a href="ident?i=res">res</a>-&gt;nh_sel = 0;
<a name="L1299" href="source/net/ipv4/fib_semantics.c#L1299">1299</a>                         return;
<a name="L1300" href="source/net/ipv4/fib_semantics.c#L1300">1300</a>                 }
<a name="L1301" href="source/net/ipv4/fib_semantics.c#L1301">1301</a>         }
<a name="L1302" href="source/net/ipv4/fib_semantics.c#L1302">1302</a> 
<a name="L1303" href="source/net/ipv4/fib_semantics.c#L1303">1303</a> 
<a name="L1304" href="source/net/ipv4/fib_semantics.c#L1304">1304</a>         <b><i>/* w should be random number [0..fi-&gt;fib_power-1],</i></b>
<a name="L1305" href="source/net/ipv4/fib_semantics.c#L1305">1305</a> <b><i>         * it is pretty bad approximation.</i></b>
<a name="L1306" href="source/net/ipv4/fib_semantics.c#L1306">1306</a> <b><i>         */</i></b>
<a name="L1307" href="source/net/ipv4/fib_semantics.c#L1307">1307</a> 
<a name="L1308" href="source/net/ipv4/fib_semantics.c#L1308">1308</a>         <a href="ident?i=w">w</a> = <a href="ident?i=jiffies">jiffies</a> % fi-&gt;fib_power;
<a name="L1309" href="source/net/ipv4/fib_semantics.c#L1309">1309</a> 
<a name="L1310" href="source/net/ipv4/fib_semantics.c#L1310">1310</a>         <a href="ident?i=change_nexthops">change_nexthops</a>(fi) {
<a name="L1311" href="source/net/ipv4/fib_semantics.c#L1311">1311</a>                 if (!(nexthop_nh-&gt;nh_flags &amp; <a href="ident?i=RTNH_F_DEAD">RTNH_F_DEAD</a>) &amp;&amp;
<a name="L1312" href="source/net/ipv4/fib_semantics.c#L1312">1312</a>                     nexthop_nh-&gt;nh_power) {
<a name="L1313" href="source/net/ipv4/fib_semantics.c#L1313">1313</a>                         <a href="ident?i=w">w</a> -= nexthop_nh-&gt;nh_power;
<a name="L1314" href="source/net/ipv4/fib_semantics.c#L1314">1314</a>                         if (<a href="ident?i=w">w</a> &lt;= 0) {
<a name="L1315" href="source/net/ipv4/fib_semantics.c#L1315">1315</a>                                 nexthop_nh-&gt;nh_power--;
<a name="L1316" href="source/net/ipv4/fib_semantics.c#L1316">1316</a>                                 fi-&gt;fib_power--;
<a name="L1317" href="source/net/ipv4/fib_semantics.c#L1317">1317</a>                                 <a href="ident?i=res">res</a>-&gt;nh_sel = nhsel;
<a name="L1318" href="source/net/ipv4/fib_semantics.c#L1318">1318</a>                                 <a href="ident?i=spin_unlock_bh">spin_unlock_bh</a>(&amp;fib_multipath_lock);
<a name="L1319" href="source/net/ipv4/fib_semantics.c#L1319">1319</a>                                 return;
<a name="L1320" href="source/net/ipv4/fib_semantics.c#L1320">1320</a>                         }
<a name="L1321" href="source/net/ipv4/fib_semantics.c#L1321">1321</a>                 }
<a name="L1322" href="source/net/ipv4/fib_semantics.c#L1322">1322</a>         } <a href="ident?i=endfor_nexthops">endfor_nexthops</a>(fi);
<a name="L1323" href="source/net/ipv4/fib_semantics.c#L1323">1323</a> 
<a name="L1324" href="source/net/ipv4/fib_semantics.c#L1324">1324</a>         <b><i>/* Race condition: route has just become dead. */</i></b>
<a name="L1325" href="source/net/ipv4/fib_semantics.c#L1325">1325</a>         <a href="ident?i=res">res</a>-&gt;nh_sel = 0;
<a name="L1326" href="source/net/ipv4/fib_semantics.c#L1326">1326</a>         <a href="ident?i=spin_unlock_bh">spin_unlock_bh</a>(&amp;fib_multipath_lock);
<a name="L1327" href="source/net/ipv4/fib_semantics.c#L1327">1327</a> }
<a name="L1328" href="source/net/ipv4/fib_semantics.c#L1328">1328</a> #endif
<a name="L1329" href="source/net/ipv4/fib_semantics.c#L1329">1329</a> </pre></div><p>
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
