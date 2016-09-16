<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title>Linux/net/ipv4/netfilter/ip_tables.c - Linux Cross Reference - Free Electrons</title>
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
		 &nbsp;&bull;&nbsp;<b><i>source navigation</i></b> &nbsp;&bull;&nbsp;<a href="diff/net/ipv4/netfilter/ip_tables.c">diff markup</a> &nbsp;&bull;&nbsp;<a href="ident">identifier search</a> &nbsp;&bull;&nbsp;<a href="search">freetext search</a> &nbsp;&bull;&nbsp;
		</p>
	</div>
</div>

<div id="topbar">
  
  <p>Version: &nbsp;<a href="source/net/ipv4/netfilter/ip_tables.c?v=2.0.40">2.0.40</a>&nbsp;<a href="source/net/ipv4/netfilter/ip_tables.c?v=2.2.26">2.2.26</a>&nbsp;<a href="source/net/ipv4/netfilter/ip_tables.c?v=2.4.37">2.4.37</a>&nbsp;<a href="source/net/ipv4/netfilter/ip_tables.c?v=3.5">3.5</a>&nbsp;<a href="source/net/ipv4/netfilter/ip_tables.c?v=3.6">3.6</a>&nbsp;<a href="source/net/ipv4/netfilter/ip_tables.c?v=3.7">3.7</a>&nbsp;<a href="source/net/ipv4/netfilter/ip_tables.c?v=3.8">3.8</a>&nbsp;<a href="source/net/ipv4/netfilter/ip_tables.c?v=3.9">3.9</a>&nbsp;<a href="source/net/ipv4/netfilter/ip_tables.c?v=3.10">3.10</a>&nbsp;<a href="source/net/ipv4/netfilter/ip_tables.c?v=3.11">3.11</a>&nbsp;<a href="source/net/ipv4/netfilter/ip_tables.c?v=3.12">3.12</a>&nbsp;<a href="source/net/ipv4/netfilter/ip_tables.c?v=3.13">3.13</a>&nbsp;<a href="source/net/ipv4/netfilter/ip_tables.c?v=3.14">3.14</a>&nbsp;<a href="source/net/ipv4/netfilter/ip_tables.c?v=3.15">3.15</a>&nbsp;<a href="source/net/ipv4/netfilter/ip_tables.c?v=3.16">3.16</a>&nbsp;<a href="source/net/ipv4/netfilter/ip_tables.c?v=3.17">3.17</a>&nbsp;<a href="source/net/ipv4/netfilter/ip_tables.c?v=3.18">3.18</a>&nbsp;<a href="source/net/ipv4/netfilter/ip_tables.c?v=3.19">3.19</a>&nbsp;<a href="source/net/ipv4/netfilter/ip_tables.c?v=4.0">4.0</a>&nbsp;<b><i>4.1</i></b></p>
  
</div>

<h1><a href="source/">Linux</a>/<a href="source/net/">net</a>/<a href="source/net/ipv4/">ipv4</a>/<a href="source/net/ipv4/netfilter/">netfilter</a>/<a href="source/net/ipv4/netfilter/ip_tables.c">ip_tables.c</a></h1>
<div id="lxrcode"><pre>  <a name="L1" href="source/net/ipv4/netfilter/ip_tables.c#L1">1</a> <b><i>/*</i></b>
  <a name="L2" href="source/net/ipv4/netfilter/ip_tables.c#L2">2</a> <b><i> * Packet matching code.</i></b>
  <a name="L3" href="source/net/ipv4/netfilter/ip_tables.c#L3">3</a> <b><i> *</i></b>
  <a name="L4" href="source/net/ipv4/netfilter/ip_tables.c#L4">4</a> <b><i> * Copyright (C) 1999 Paul `Rusty' Russell &amp; Michael J. Neuling</i></b>
  <a name="L5" href="source/net/ipv4/netfilter/ip_tables.c#L5">5</a> <b><i> * Copyright (C) 2000-2005 Netfilter Core Team &lt;coreteam@netfilter.org&gt;</i></b>
  <a name="L6" href="source/net/ipv4/netfilter/ip_tables.c#L6">6</a> <b><i> * Copyright (C) 2006-2010 Patrick McHardy &lt;kaber@trash.net&gt;</i></b>
  <a name="L7" href="source/net/ipv4/netfilter/ip_tables.c#L7">7</a> <b><i> *</i></b>
  <a name="L8" href="source/net/ipv4/netfilter/ip_tables.c#L8">8</a> <b><i> * This program is free software; you can redistribute it and/or modify</i></b>
  <a name="L9" href="source/net/ipv4/netfilter/ip_tables.c#L9">9</a> <b><i> * it under the terms of the GNU General Public License version 2 as</i></b>
 <a name="L10" href="source/net/ipv4/netfilter/ip_tables.c#L10">10</a> <b><i> * published by the Free Software Foundation.</i></b>
 <a name="L11" href="source/net/ipv4/netfilter/ip_tables.c#L11">11</a> <b><i> */</i></b>
 <a name="L12" href="source/net/ipv4/netfilter/ip_tables.c#L12">12</a> #define <a href="ident?i=pr_fmt">pr_fmt</a>(<a href="ident?i=fmt">fmt</a>) KBUILD_MODNAME <i>": "</i> <a href="ident?i=fmt">fmt</a>
 <a name="L13" href="source/net/ipv4/netfilter/ip_tables.c#L13">13</a> #include &lt;linux/cache.h&gt;
 <a name="L14" href="source/net/ipv4/netfilter/ip_tables.c#L14">14</a> #include &lt;linux/capability.h&gt;
 <a name="L15" href="source/net/ipv4/netfilter/ip_tables.c#L15">15</a> #include &lt;linux/skbuff.h&gt;
 <a name="L16" href="source/net/ipv4/netfilter/ip_tables.c#L16">16</a> #include &lt;linux/kmod.h&gt;
 <a name="L17" href="source/net/ipv4/netfilter/ip_tables.c#L17">17</a> #include &lt;linux/vmalloc.h&gt;
 <a name="L18" href="source/net/ipv4/netfilter/ip_tables.c#L18">18</a> #include &lt;linux/netdevice.h&gt;
 <a name="L19" href="source/net/ipv4/netfilter/ip_tables.c#L19">19</a> #include &lt;linux/module.h&gt;
 <a name="L20" href="source/net/ipv4/netfilter/ip_tables.c#L20">20</a> #include &lt;linux/icmp.h&gt;
 <a name="L21" href="source/net/ipv4/netfilter/ip_tables.c#L21">21</a> #include &lt;net/ip.h&gt;
 <a name="L22" href="source/net/ipv4/netfilter/ip_tables.c#L22">22</a> #include &lt;net/compat.h&gt;
 <a name="L23" href="source/net/ipv4/netfilter/ip_tables.c#L23">23</a> #include &lt;asm/uaccess.h&gt;
 <a name="L24" href="source/net/ipv4/netfilter/ip_tables.c#L24">24</a> #include &lt;linux/mutex.h&gt;
 <a name="L25" href="source/net/ipv4/netfilter/ip_tables.c#L25">25</a> #include &lt;linux/proc_fs.h&gt;
 <a name="L26" href="source/net/ipv4/netfilter/ip_tables.c#L26">26</a> #include &lt;linux/err.h&gt;
 <a name="L27" href="source/net/ipv4/netfilter/ip_tables.c#L27">27</a> #include &lt;linux/cpumask.h&gt;
 <a name="L28" href="source/net/ipv4/netfilter/ip_tables.c#L28">28</a> 
 <a name="L29" href="source/net/ipv4/netfilter/ip_tables.c#L29">29</a> #include &lt;linux/netfilter/x_tables.h&gt;
 <a name="L30" href="source/net/ipv4/netfilter/ip_tables.c#L30">30</a> #include &lt;linux/netfilter_ipv4/ip_tables.h&gt;
 <a name="L31" href="source/net/ipv4/netfilter/ip_tables.c#L31">31</a> #include &lt;net/netfilter/nf_log.h&gt;
 <a name="L32" href="source/net/ipv4/netfilter/ip_tables.c#L32">32</a> #include "<a href="source/net/ipv4/netfilter/../../netfilter/xt_repldata.h">../../netfilter/xt_repldata.h</a>"
 <a name="L33" href="source/net/ipv4/netfilter/ip_tables.c#L33">33</a> 
 <a name="L34" href="source/net/ipv4/netfilter/ip_tables.c#L34">34</a> <a href="ident?i=MODULE_LICENSE">MODULE_LICENSE</a>(<i>"GPL"</i>);
 <a name="L35" href="source/net/ipv4/netfilter/ip_tables.c#L35">35</a> <a href="ident?i=MODULE_AUTHOR">MODULE_AUTHOR</a>(<i>"Netfilter Core Team &lt;coreteam@netfilter.org&gt;"</i>);
 <a name="L36" href="source/net/ipv4/netfilter/ip_tables.c#L36">36</a> <a href="ident?i=MODULE_DESCRIPTION">MODULE_DESCRIPTION</a>(<i>"IPv4 packet filter"</i>);
 <a name="L37" href="source/net/ipv4/netfilter/ip_tables.c#L37">37</a> 
 <a name="L38" href="source/net/ipv4/netfilter/ip_tables.c#L38">38</a> <b><i>/*#define DEBUG_IP_FIREWALL*/</i></b>
 <a name="L39" href="source/net/ipv4/netfilter/ip_tables.c#L39">39</a> <b><i>/*#define DEBUG_ALLOW_ALL*/</i></b> <b><i>/* Useful for remote debugging */</i></b>
 <a name="L40" href="source/net/ipv4/netfilter/ip_tables.c#L40">40</a> <b><i>/*#define DEBUG_IP_FIREWALL_USER*/</i></b>
 <a name="L41" href="source/net/ipv4/netfilter/ip_tables.c#L41">41</a> 
 <a name="L42" href="source/net/ipv4/netfilter/ip_tables.c#L42">42</a> #ifdef DEBUG_IP_FIREWALL
 <a name="L43" href="source/net/ipv4/netfilter/ip_tables.c#L43">43</a> #define <a href="ident?i=dprintf">dprintf</a>(<a href="ident?i=format">format</a>, <a href="ident?i=args">args</a>...) <a href="ident?i=pr_info">pr_info</a>(<a href="ident?i=format">format</a> , ## <a href="ident?i=args">args</a>)
 <a name="L44" href="source/net/ipv4/netfilter/ip_tables.c#L44">44</a> #else
 <a name="L45" href="source/net/ipv4/netfilter/ip_tables.c#L45">45</a> #define <a href="ident?i=dprintf">dprintf</a>(<a href="ident?i=format">format</a>, <a href="ident?i=args">args</a>...)
 <a name="L46" href="source/net/ipv4/netfilter/ip_tables.c#L46">46</a> #endif
 <a name="L47" href="source/net/ipv4/netfilter/ip_tables.c#L47">47</a> 
 <a name="L48" href="source/net/ipv4/netfilter/ip_tables.c#L48">48</a> #ifdef DEBUG_IP_FIREWALL_USER
 <a name="L49" href="source/net/ipv4/netfilter/ip_tables.c#L49">49</a> #define <a href="ident?i=duprintf">duprintf</a>(<a href="ident?i=format">format</a>, <a href="ident?i=args">args</a>...) <a href="ident?i=pr_info">pr_info</a>(<a href="ident?i=format">format</a> , ## <a href="ident?i=args">args</a>)
 <a name="L50" href="source/net/ipv4/netfilter/ip_tables.c#L50">50</a> #else
 <a name="L51" href="source/net/ipv4/netfilter/ip_tables.c#L51">51</a> #define <a href="ident?i=duprintf">duprintf</a>(<a href="ident?i=format">format</a>, <a href="ident?i=args">args</a>...)
 <a name="L52" href="source/net/ipv4/netfilter/ip_tables.c#L52">52</a> #endif
 <a name="L53" href="source/net/ipv4/netfilter/ip_tables.c#L53">53</a> 
 <a name="L54" href="source/net/ipv4/netfilter/ip_tables.c#L54">54</a> #ifdef CONFIG_NETFILTER_DEBUG
 <a name="L55" href="source/net/ipv4/netfilter/ip_tables.c#L55">55</a> #define <a href="ident?i=IP_NF_ASSERT">IP_NF_ASSERT</a>(<a href="ident?i=x">x</a>)         <a href="ident?i=WARN_ON">WARN_ON</a>(!(<a href="ident?i=x">x</a>))
 <a name="L56" href="source/net/ipv4/netfilter/ip_tables.c#L56">56</a> #else
 <a name="L57" href="source/net/ipv4/netfilter/ip_tables.c#L57">57</a> #define <a href="ident?i=IP_NF_ASSERT">IP_NF_ASSERT</a>(<a href="ident?i=x">x</a>)
 <a name="L58" href="source/net/ipv4/netfilter/ip_tables.c#L58">58</a> #endif
 <a name="L59" href="source/net/ipv4/netfilter/ip_tables.c#L59">59</a> 
 <a name="L60" href="source/net/ipv4/netfilter/ip_tables.c#L60">60</a> #if 0
 <a name="L61" href="source/net/ipv4/netfilter/ip_tables.c#L61">61</a> <b><i>/* All the better to debug you with... */</i></b>
 <a name="L62" href="source/net/ipv4/netfilter/ip_tables.c#L62">62</a> #define static
 <a name="L63" href="source/net/ipv4/netfilter/ip_tables.c#L63">63</a> #define inline
 <a name="L64" href="source/net/ipv4/netfilter/ip_tables.c#L64">64</a> #endif
 <a name="L65" href="source/net/ipv4/netfilter/ip_tables.c#L65">65</a> 
 <a name="L66" href="source/net/ipv4/netfilter/ip_tables.c#L66">66</a> void *<a href="ident?i=ipt_alloc_initial_table">ipt_alloc_initial_table</a>(const struct <a href="ident?i=xt_table">xt_table</a> *<a href="ident?i=info">info</a>)
 <a name="L67" href="source/net/ipv4/netfilter/ip_tables.c#L67">67</a> {
 <a name="L68" href="source/net/ipv4/netfilter/ip_tables.c#L68">68</a>         return <a href="ident?i=xt_alloc_initial_table">xt_alloc_initial_table</a>(ipt, IPT);
 <a name="L69" href="source/net/ipv4/netfilter/ip_tables.c#L69">69</a> }
 <a name="L70" href="source/net/ipv4/netfilter/ip_tables.c#L70">70</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=ipt_alloc_initial_table">ipt_alloc_initial_table</a>);
 <a name="L71" href="source/net/ipv4/netfilter/ip_tables.c#L71">71</a> 
 <a name="L72" href="source/net/ipv4/netfilter/ip_tables.c#L72">72</a> <b><i>/* Returns whether matches rule or not. */</i></b>
 <a name="L73" href="source/net/ipv4/netfilter/ip_tables.c#L73">73</a> <b><i>/* Performance critical - called for every packet */</i></b>
 <a name="L74" href="source/net/ipv4/netfilter/ip_tables.c#L74">74</a> static inline <a href="ident?i=bool">bool</a>
 <a name="L75" href="source/net/ipv4/netfilter/ip_tables.c#L75">75</a> <a href="ident?i=ip_packet_match">ip_packet_match</a>(const struct <a href="ident?i=iphdr">iphdr</a> *<a href="ident?i=ip">ip</a>,
 <a name="L76" href="source/net/ipv4/netfilter/ip_tables.c#L76">76</a>                 const char *indev,
 <a name="L77" href="source/net/ipv4/netfilter/ip_tables.c#L77">77</a>                 const char *outdev,
 <a name="L78" href="source/net/ipv4/netfilter/ip_tables.c#L78">78</a>                 const struct <a href="ident?i=ipt_ip">ipt_ip</a> *ipinfo,
 <a name="L79" href="source/net/ipv4/netfilter/ip_tables.c#L79">79</a>                 int isfrag)
 <a name="L80" href="source/net/ipv4/netfilter/ip_tables.c#L80">80</a> {
 <a name="L81" href="source/net/ipv4/netfilter/ip_tables.c#L81">81</a>         unsigned long <a href="ident?i=ret">ret</a>;
 <a name="L82" href="source/net/ipv4/netfilter/ip_tables.c#L82">82</a> 
 <a name="L83" href="source/net/ipv4/netfilter/ip_tables.c#L83">83</a> #define <a href="ident?i=FWINV">FWINV</a>(<a href="ident?i=bool">bool</a>, invflg) ((<a href="ident?i=bool">bool</a>) ^ !!(ipinfo-&gt;invflags &amp; (invflg)))
 <a name="L84" href="source/net/ipv4/netfilter/ip_tables.c#L84">84</a> 
 <a name="L85" href="source/net/ipv4/netfilter/ip_tables.c#L85">85</a>         if (<a href="ident?i=FWINV">FWINV</a>((<a href="ident?i=ip">ip</a>-&gt;<a href="ident?i=saddr">saddr</a>&amp;ipinfo-&gt;smsk.s_addr) != ipinfo-&gt;<a href="ident?i=src">src</a>.s_addr,
 <a name="L86" href="source/net/ipv4/netfilter/ip_tables.c#L86">86</a>                   <a href="ident?i=IPT_INV_SRCIP">IPT_INV_SRCIP</a>) ||
 <a name="L87" href="source/net/ipv4/netfilter/ip_tables.c#L87">87</a>             <a href="ident?i=FWINV">FWINV</a>((<a href="ident?i=ip">ip</a>-&gt;<a href="ident?i=daddr">daddr</a>&amp;ipinfo-&gt;dmsk.s_addr) != ipinfo-&gt;<a href="ident?i=dst">dst</a>.s_addr,
 <a name="L88" href="source/net/ipv4/netfilter/ip_tables.c#L88">88</a>                   <a href="ident?i=IPT_INV_DSTIP">IPT_INV_DSTIP</a>)) {
 <a name="L89" href="source/net/ipv4/netfilter/ip_tables.c#L89">89</a>                 <a href="ident?i=dprintf">dprintf</a>(<i>"Source or dest mismatch.\n"</i>);
 <a name="L90" href="source/net/ipv4/netfilter/ip_tables.c#L90">90</a> 
 <a name="L91" href="source/net/ipv4/netfilter/ip_tables.c#L91">91</a>                 <a href="ident?i=dprintf">dprintf</a>(<i>"SRC: %pI4. Mask: %pI4. Target: %pI4.%s\n"</i>,
 <a name="L92" href="source/net/ipv4/netfilter/ip_tables.c#L92">92</a>                         &amp;<a href="ident?i=ip">ip</a>-&gt;<a href="ident?i=saddr">saddr</a>, &amp;ipinfo-&gt;smsk.s_addr, &amp;ipinfo-&gt;<a href="ident?i=src">src</a>.s_addr,
 <a name="L93" href="source/net/ipv4/netfilter/ip_tables.c#L93">93</a>                         ipinfo-&gt;invflags &amp; <a href="ident?i=IPT_INV_SRCIP">IPT_INV_SRCIP</a> ? <i>" (INV)"</i> : <i>""</i>);
 <a name="L94" href="source/net/ipv4/netfilter/ip_tables.c#L94">94</a>                 <a href="ident?i=dprintf">dprintf</a>(<i>"DST: %pI4 Mask: %pI4 Target: %pI4.%s\n"</i>,
 <a name="L95" href="source/net/ipv4/netfilter/ip_tables.c#L95">95</a>                         &amp;<a href="ident?i=ip">ip</a>-&gt;<a href="ident?i=daddr">daddr</a>, &amp;ipinfo-&gt;dmsk.s_addr, &amp;ipinfo-&gt;<a href="ident?i=dst">dst</a>.s_addr,
 <a name="L96" href="source/net/ipv4/netfilter/ip_tables.c#L96">96</a>                         ipinfo-&gt;invflags &amp; <a href="ident?i=IPT_INV_DSTIP">IPT_INV_DSTIP</a> ? <i>" (INV)"</i> : <i>""</i>);
 <a name="L97" href="source/net/ipv4/netfilter/ip_tables.c#L97">97</a>                 return <a href="ident?i=false">false</a>;
 <a name="L98" href="source/net/ipv4/netfilter/ip_tables.c#L98">98</a>         }
 <a name="L99" href="source/net/ipv4/netfilter/ip_tables.c#L99">99</a> 
<a name="L100" href="source/net/ipv4/netfilter/ip_tables.c#L100">100</a>         <a href="ident?i=ret">ret</a> = <a href="ident?i=ifname_compare_aligned">ifname_compare_aligned</a>(indev, ipinfo-&gt;iniface, ipinfo-&gt;iniface_mask);
<a name="L101" href="source/net/ipv4/netfilter/ip_tables.c#L101">101</a> 
<a name="L102" href="source/net/ipv4/netfilter/ip_tables.c#L102">102</a>         if (<a href="ident?i=FWINV">FWINV</a>(<a href="ident?i=ret">ret</a> != 0, <a href="ident?i=IPT_INV_VIA_IN">IPT_INV_VIA_IN</a>)) {
<a name="L103" href="source/net/ipv4/netfilter/ip_tables.c#L103">103</a>                 <a href="ident?i=dprintf">dprintf</a>(<i>"VIA in mismatch (%s vs %s).%s\n"</i>,
<a name="L104" href="source/net/ipv4/netfilter/ip_tables.c#L104">104</a>                         indev, ipinfo-&gt;iniface,
<a name="L105" href="source/net/ipv4/netfilter/ip_tables.c#L105">105</a>                         ipinfo-&gt;invflags&amp;<a href="ident?i=IPT_INV_VIA_IN">IPT_INV_VIA_IN</a> ?<i>" (INV)"</i>:<i>""</i>);
<a name="L106" href="source/net/ipv4/netfilter/ip_tables.c#L106">106</a>                 return <a href="ident?i=false">false</a>;
<a name="L107" href="source/net/ipv4/netfilter/ip_tables.c#L107">107</a>         }
<a name="L108" href="source/net/ipv4/netfilter/ip_tables.c#L108">108</a> 
<a name="L109" href="source/net/ipv4/netfilter/ip_tables.c#L109">109</a>         <a href="ident?i=ret">ret</a> = <a href="ident?i=ifname_compare_aligned">ifname_compare_aligned</a>(outdev, ipinfo-&gt;outiface, ipinfo-&gt;outiface_mask);
<a name="L110" href="source/net/ipv4/netfilter/ip_tables.c#L110">110</a> 
<a name="L111" href="source/net/ipv4/netfilter/ip_tables.c#L111">111</a>         if (<a href="ident?i=FWINV">FWINV</a>(<a href="ident?i=ret">ret</a> != 0, <a href="ident?i=IPT_INV_VIA_OUT">IPT_INV_VIA_OUT</a>)) {
<a name="L112" href="source/net/ipv4/netfilter/ip_tables.c#L112">112</a>                 <a href="ident?i=dprintf">dprintf</a>(<i>"VIA out mismatch (%s vs %s).%s\n"</i>,
<a name="L113" href="source/net/ipv4/netfilter/ip_tables.c#L113">113</a>                         outdev, ipinfo-&gt;outiface,
<a name="L114" href="source/net/ipv4/netfilter/ip_tables.c#L114">114</a>                         ipinfo-&gt;invflags&amp;<a href="ident?i=IPT_INV_VIA_OUT">IPT_INV_VIA_OUT</a> ?<i>" (INV)"</i>:<i>""</i>);
<a name="L115" href="source/net/ipv4/netfilter/ip_tables.c#L115">115</a>                 return <a href="ident?i=false">false</a>;
<a name="L116" href="source/net/ipv4/netfilter/ip_tables.c#L116">116</a>         }
<a name="L117" href="source/net/ipv4/netfilter/ip_tables.c#L117">117</a> 
<a name="L118" href="source/net/ipv4/netfilter/ip_tables.c#L118">118</a>         <b><i>/* Check specific protocol */</i></b>
<a name="L119" href="source/net/ipv4/netfilter/ip_tables.c#L119">119</a>         if (ipinfo-&gt;<a href="ident?i=proto">proto</a> &amp;&amp;
<a name="L120" href="source/net/ipv4/netfilter/ip_tables.c#L120">120</a>             <a href="ident?i=FWINV">FWINV</a>(<a href="ident?i=ip">ip</a>-&gt;<a href="ident?i=protocol">protocol</a> != ipinfo-&gt;<a href="ident?i=proto">proto</a>, <a href="ident?i=IPT_INV_PROTO">IPT_INV_PROTO</a>)) {
<a name="L121" href="source/net/ipv4/netfilter/ip_tables.c#L121">121</a>                 <a href="ident?i=dprintf">dprintf</a>(<i>"Packet protocol %hi does not match %hi.%s\n"</i>,
<a name="L122" href="source/net/ipv4/netfilter/ip_tables.c#L122">122</a>                         <a href="ident?i=ip">ip</a>-&gt;<a href="ident?i=protocol">protocol</a>, ipinfo-&gt;<a href="ident?i=proto">proto</a>,
<a name="L123" href="source/net/ipv4/netfilter/ip_tables.c#L123">123</a>                         ipinfo-&gt;invflags&amp;<a href="ident?i=IPT_INV_PROTO">IPT_INV_PROTO</a> ? <i>" (INV)"</i>:<i>""</i>);
<a name="L124" href="source/net/ipv4/netfilter/ip_tables.c#L124">124</a>                 return <a href="ident?i=false">false</a>;
<a name="L125" href="source/net/ipv4/netfilter/ip_tables.c#L125">125</a>         }
<a name="L126" href="source/net/ipv4/netfilter/ip_tables.c#L126">126</a> 
<a name="L127" href="source/net/ipv4/netfilter/ip_tables.c#L127">127</a>         <b><i>/* If we have a fragment rule but the packet is not a fragment</i></b>
<a name="L128" href="source/net/ipv4/netfilter/ip_tables.c#L128">128</a> <b><i>         * then we return zero */</i></b>
<a name="L129" href="source/net/ipv4/netfilter/ip_tables.c#L129">129</a>         if (<a href="ident?i=FWINV">FWINV</a>((ipinfo-&gt;<a href="ident?i=flags">flags</a>&amp;<a href="ident?i=IPT_F_FRAG">IPT_F_FRAG</a>) &amp;&amp; !isfrag, <a href="ident?i=IPT_INV_FRAG">IPT_INV_FRAG</a>)) {
<a name="L130" href="source/net/ipv4/netfilter/ip_tables.c#L130">130</a>                 <a href="ident?i=dprintf">dprintf</a>(<i>"Fragment rule but not fragment.%s\n"</i>,
<a name="L131" href="source/net/ipv4/netfilter/ip_tables.c#L131">131</a>                         ipinfo-&gt;invflags &amp; <a href="ident?i=IPT_INV_FRAG">IPT_INV_FRAG</a> ? <i>" (INV)"</i> : <i>""</i>);
<a name="L132" href="source/net/ipv4/netfilter/ip_tables.c#L132">132</a>                 return <a href="ident?i=false">false</a>;
<a name="L133" href="source/net/ipv4/netfilter/ip_tables.c#L133">133</a>         }
<a name="L134" href="source/net/ipv4/netfilter/ip_tables.c#L134">134</a> 
<a name="L135" href="source/net/ipv4/netfilter/ip_tables.c#L135">135</a>         return <a href="ident?i=true">true</a>;
<a name="L136" href="source/net/ipv4/netfilter/ip_tables.c#L136">136</a> }
<a name="L137" href="source/net/ipv4/netfilter/ip_tables.c#L137">137</a> 
<a name="L138" href="source/net/ipv4/netfilter/ip_tables.c#L138">138</a> static <a href="ident?i=bool">bool</a>
<a name="L139" href="source/net/ipv4/netfilter/ip_tables.c#L139">139</a> <a href="ident?i=ip_checkentry">ip_checkentry</a>(const struct <a href="ident?i=ipt_ip">ipt_ip</a> *<a href="ident?i=ip">ip</a>)
<a name="L140" href="source/net/ipv4/netfilter/ip_tables.c#L140">140</a> {
<a name="L141" href="source/net/ipv4/netfilter/ip_tables.c#L141">141</a>         if (<a href="ident?i=ip">ip</a>-&gt;<a href="ident?i=flags">flags</a> &amp; ~IPT_F_MASK) {
<a name="L142" href="source/net/ipv4/netfilter/ip_tables.c#L142">142</a>                 <a href="ident?i=duprintf">duprintf</a>(<i>"Unknown flag bits set: %08X\n"</i>,
<a name="L143" href="source/net/ipv4/netfilter/ip_tables.c#L143">143</a>                          <a href="ident?i=ip">ip</a>-&gt;<a href="ident?i=flags">flags</a> &amp; ~IPT_F_MASK);
<a name="L144" href="source/net/ipv4/netfilter/ip_tables.c#L144">144</a>                 return <a href="ident?i=false">false</a>;
<a name="L145" href="source/net/ipv4/netfilter/ip_tables.c#L145">145</a>         }
<a name="L146" href="source/net/ipv4/netfilter/ip_tables.c#L146">146</a>         if (<a href="ident?i=ip">ip</a>-&gt;invflags &amp; ~IPT_INV_MASK) {
<a name="L147" href="source/net/ipv4/netfilter/ip_tables.c#L147">147</a>                 <a href="ident?i=duprintf">duprintf</a>(<i>"Unknown invflag bits set: %08X\n"</i>,
<a name="L148" href="source/net/ipv4/netfilter/ip_tables.c#L148">148</a>                          <a href="ident?i=ip">ip</a>-&gt;invflags &amp; ~IPT_INV_MASK);
<a name="L149" href="source/net/ipv4/netfilter/ip_tables.c#L149">149</a>                 return <a href="ident?i=false">false</a>;
<a name="L150" href="source/net/ipv4/netfilter/ip_tables.c#L150">150</a>         }
<a name="L151" href="source/net/ipv4/netfilter/ip_tables.c#L151">151</a>         return <a href="ident?i=true">true</a>;
<a name="L152" href="source/net/ipv4/netfilter/ip_tables.c#L152">152</a> }
<a name="L153" href="source/net/ipv4/netfilter/ip_tables.c#L153">153</a> 
<a name="L154" href="source/net/ipv4/netfilter/ip_tables.c#L154">154</a> static unsigned int
<a name="L155" href="source/net/ipv4/netfilter/ip_tables.c#L155">155</a> <a href="ident?i=ipt_error">ipt_error</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, const struct <a href="ident?i=xt_action_param">xt_action_param</a> *<a href="ident?i=par">par</a>)
<a name="L156" href="source/net/ipv4/netfilter/ip_tables.c#L156">156</a> {
<a name="L157" href="source/net/ipv4/netfilter/ip_tables.c#L157">157</a>         <a href="ident?i=net_info_ratelimited">net_info_ratelimited</a>(<i>"error: `%s'\n"</i>, (const char *)<a href="ident?i=par">par</a>-&gt;targinfo);
<a name="L158" href="source/net/ipv4/netfilter/ip_tables.c#L158">158</a> 
<a name="L159" href="source/net/ipv4/netfilter/ip_tables.c#L159">159</a>         return <a href="ident?i=NF_DROP">NF_DROP</a>;
<a name="L160" href="source/net/ipv4/netfilter/ip_tables.c#L160">160</a> }
<a name="L161" href="source/net/ipv4/netfilter/ip_tables.c#L161">161</a> 
<a name="L162" href="source/net/ipv4/netfilter/ip_tables.c#L162">162</a> <b><i>/* Performance critical */</i></b>
<a name="L163" href="source/net/ipv4/netfilter/ip_tables.c#L163">163</a> static inline struct <a href="ident?i=ipt_entry">ipt_entry</a> *
<a name="L164" href="source/net/ipv4/netfilter/ip_tables.c#L164">164</a> <a href="ident?i=get_entry">get_entry</a>(const void *<a href="ident?i=base">base</a>, unsigned int <a href="ident?i=offset">offset</a>)
<a name="L165" href="source/net/ipv4/netfilter/ip_tables.c#L165">165</a> {
<a name="L166" href="source/net/ipv4/netfilter/ip_tables.c#L166">166</a>         return (struct <a href="ident?i=ipt_entry">ipt_entry</a> *)(<a href="ident?i=base">base</a> + <a href="ident?i=offset">offset</a>);
<a name="L167" href="source/net/ipv4/netfilter/ip_tables.c#L167">167</a> }
<a name="L168" href="source/net/ipv4/netfilter/ip_tables.c#L168">168</a> 
<a name="L169" href="source/net/ipv4/netfilter/ip_tables.c#L169">169</a> <b><i>/* All zeroes == unconditional rule. */</i></b>
<a name="L170" href="source/net/ipv4/netfilter/ip_tables.c#L170">170</a> <b><i>/* Mildly perf critical (only if packet tracing is on) */</i></b>
<a name="L171" href="source/net/ipv4/netfilter/ip_tables.c#L171">171</a> static inline <a href="ident?i=bool">bool</a> <a href="ident?i=unconditional">unconditional</a>(const struct <a href="ident?i=ipt_ip">ipt_ip</a> *<a href="ident?i=ip">ip</a>)
<a name="L172" href="source/net/ipv4/netfilter/ip_tables.c#L172">172</a> {
<a name="L173" href="source/net/ipv4/netfilter/ip_tables.c#L173">173</a>         static const struct <a href="ident?i=ipt_ip">ipt_ip</a> uncond;
<a name="L174" href="source/net/ipv4/netfilter/ip_tables.c#L174">174</a> 
<a name="L175" href="source/net/ipv4/netfilter/ip_tables.c#L175">175</a>         return <a href="ident?i=memcmp">memcmp</a>(<a href="ident?i=ip">ip</a>, &amp;uncond, sizeof(uncond)) == 0;
<a name="L176" href="source/net/ipv4/netfilter/ip_tables.c#L176">176</a> #undef <a href="ident?i=FWINV">FWINV</a>
<a name="L177" href="source/net/ipv4/netfilter/ip_tables.c#L177">177</a> }
<a name="L178" href="source/net/ipv4/netfilter/ip_tables.c#L178">178</a> 
<a name="L179" href="source/net/ipv4/netfilter/ip_tables.c#L179">179</a> <b><i>/* for const-correctness */</i></b>
<a name="L180" href="source/net/ipv4/netfilter/ip_tables.c#L180">180</a> static inline const struct <a href="ident?i=xt_entry_target">xt_entry_target</a> *
<a name="L181" href="source/net/ipv4/netfilter/ip_tables.c#L181">181</a> <a href="ident?i=ipt_get_target_c">ipt_get_target_c</a>(const struct <a href="ident?i=ipt_entry">ipt_entry</a> *<a href="ident?i=e">e</a>)
<a name="L182" href="source/net/ipv4/netfilter/ip_tables.c#L182">182</a> {
<a name="L183" href="source/net/ipv4/netfilter/ip_tables.c#L183">183</a>         return <a href="ident?i=ipt_get_target">ipt_get_target</a>((struct <a href="ident?i=ipt_entry">ipt_entry</a> *)<a href="ident?i=e">e</a>);
<a name="L184" href="source/net/ipv4/netfilter/ip_tables.c#L184">184</a> }
<a name="L185" href="source/net/ipv4/netfilter/ip_tables.c#L185">185</a> 
<a name="L186" href="source/net/ipv4/netfilter/ip_tables.c#L186">186</a> #if <a href="ident?i=IS_ENABLED">IS_ENABLED</a>(CONFIG_NETFILTER_XT_TARGET_TRACE)
<a name="L187" href="source/net/ipv4/netfilter/ip_tables.c#L187">187</a> static const char *const <a href="ident?i=hooknames">hooknames</a>[] = {
<a name="L188" href="source/net/ipv4/netfilter/ip_tables.c#L188">188</a>         [NF_INET_PRE_ROUTING]           = <i>"PREROUTING"</i>,
<a name="L189" href="source/net/ipv4/netfilter/ip_tables.c#L189">189</a>         [NF_INET_LOCAL_IN]              = <i>"INPUT"</i>,
<a name="L190" href="source/net/ipv4/netfilter/ip_tables.c#L190">190</a>         [NF_INET_FORWARD]               = <i>"FORWARD"</i>,
<a name="L191" href="source/net/ipv4/netfilter/ip_tables.c#L191">191</a>         [NF_INET_LOCAL_OUT]             = <i>"OUTPUT"</i>,
<a name="L192" href="source/net/ipv4/netfilter/ip_tables.c#L192">192</a>         [NF_INET_POST_ROUTING]          = <i>"POSTROUTING"</i>,
<a name="L193" href="source/net/ipv4/netfilter/ip_tables.c#L193">193</a> };
<a name="L194" href="source/net/ipv4/netfilter/ip_tables.c#L194">194</a> 
<a name="L195" href="source/net/ipv4/netfilter/ip_tables.c#L195">195</a> enum <a href="ident?i=nf_ip_trace_comments">nf_ip_trace_comments</a> {
<a name="L196" href="source/net/ipv4/netfilter/ip_tables.c#L196">196</a>         NF_IP_TRACE_COMMENT_RULE,
<a name="L197" href="source/net/ipv4/netfilter/ip_tables.c#L197">197</a>         NF_IP_TRACE_COMMENT_RETURN,
<a name="L198" href="source/net/ipv4/netfilter/ip_tables.c#L198">198</a>         NF_IP_TRACE_COMMENT_POLICY,
<a name="L199" href="source/net/ipv4/netfilter/ip_tables.c#L199">199</a> };
<a name="L200" href="source/net/ipv4/netfilter/ip_tables.c#L200">200</a> 
<a name="L201" href="source/net/ipv4/netfilter/ip_tables.c#L201">201</a> static const char *const <a href="ident?i=comments">comments</a>[] = {
<a name="L202" href="source/net/ipv4/netfilter/ip_tables.c#L202">202</a>         [NF_IP_TRACE_COMMENT_RULE]      = <i>"rule"</i>,
<a name="L203" href="source/net/ipv4/netfilter/ip_tables.c#L203">203</a>         [NF_IP_TRACE_COMMENT_RETURN]    = <i>"return"</i>,
<a name="L204" href="source/net/ipv4/netfilter/ip_tables.c#L204">204</a>         [NF_IP_TRACE_COMMENT_POLICY]    = <i>"policy"</i>,
<a name="L205" href="source/net/ipv4/netfilter/ip_tables.c#L205">205</a> };
<a name="L206" href="source/net/ipv4/netfilter/ip_tables.c#L206">206</a> 
<a name="L207" href="source/net/ipv4/netfilter/ip_tables.c#L207">207</a> static struct <a href="ident?i=nf_loginfo">nf_loginfo</a> <a href="ident?i=trace_loginfo">trace_loginfo</a> = {
<a name="L208" href="source/net/ipv4/netfilter/ip_tables.c#L208">208</a>         .<a href="ident?i=type">type</a> = NF_LOG_TYPE_LOG,
<a name="L209" href="source/net/ipv4/netfilter/ip_tables.c#L209">209</a>         .u = {
<a name="L210" href="source/net/ipv4/netfilter/ip_tables.c#L210">210</a>                 .<a href="ident?i=log">log</a> = {
<a name="L211" href="source/net/ipv4/netfilter/ip_tables.c#L211">211</a>                         .<a href="ident?i=level">level</a> = 4,
<a name="L212" href="source/net/ipv4/netfilter/ip_tables.c#L212">212</a>                         .logflags = <a href="ident?i=NF_LOG_MASK">NF_LOG_MASK</a>,
<a name="L213" href="source/net/ipv4/netfilter/ip_tables.c#L213">213</a>                 },
<a name="L214" href="source/net/ipv4/netfilter/ip_tables.c#L214">214</a>         },
<a name="L215" href="source/net/ipv4/netfilter/ip_tables.c#L215">215</a> };
<a name="L216" href="source/net/ipv4/netfilter/ip_tables.c#L216">216</a> 
<a name="L217" href="source/net/ipv4/netfilter/ip_tables.c#L217">217</a> <b><i>/* Mildly perf critical (only if packet tracing is on) */</i></b>
<a name="L218" href="source/net/ipv4/netfilter/ip_tables.c#L218">218</a> static inline int
<a name="L219" href="source/net/ipv4/netfilter/ip_tables.c#L219">219</a> <a href="ident?i=get_chainname_rulenum">get_chainname_rulenum</a>(const struct <a href="ident?i=ipt_entry">ipt_entry</a> *<a href="ident?i=s">s</a>, const struct <a href="ident?i=ipt_entry">ipt_entry</a> *<a href="ident?i=e">e</a>,
<a name="L220" href="source/net/ipv4/netfilter/ip_tables.c#L220">220</a>                       const char *hookname, const char **chainname,
<a name="L221" href="source/net/ipv4/netfilter/ip_tables.c#L221">221</a>                       const char **comment, unsigned int *rulenum)
<a name="L222" href="source/net/ipv4/netfilter/ip_tables.c#L222">222</a> {
<a name="L223" href="source/net/ipv4/netfilter/ip_tables.c#L223">223</a>         const struct <a href="ident?i=xt_standard_target">xt_standard_target</a> *<a href="ident?i=t">t</a> = (void *)<a href="ident?i=ipt_get_target_c">ipt_get_target_c</a>(<a href="ident?i=s">s</a>);
<a name="L224" href="source/net/ipv4/netfilter/ip_tables.c#L224">224</a> 
<a name="L225" href="source/net/ipv4/netfilter/ip_tables.c#L225">225</a>         if (<a href="ident?i=strcmp">strcmp</a>(<a href="ident?i=t">t</a>-&gt;<a href="ident?i=target">target</a>.u.kernel.<a href="ident?i=target">target</a>-&gt;<a href="ident?i=name">name</a>, <a href="ident?i=XT_ERROR_TARGET">XT_ERROR_TARGET</a>) == 0) {
<a name="L226" href="source/net/ipv4/netfilter/ip_tables.c#L226">226</a>                 <b><i>/* Head of user chain: ERROR target with chainname */</i></b>
<a name="L227" href="source/net/ipv4/netfilter/ip_tables.c#L227">227</a>                 *chainname = <a href="ident?i=t">t</a>-&gt;<a href="ident?i=target">target</a>.<a href="ident?i=data">data</a>;
<a name="L228" href="source/net/ipv4/netfilter/ip_tables.c#L228">228</a>                 (*rulenum) = 0;
<a name="L229" href="source/net/ipv4/netfilter/ip_tables.c#L229">229</a>         } else if (<a href="ident?i=s">s</a> == <a href="ident?i=e">e</a>) {
<a name="L230" href="source/net/ipv4/netfilter/ip_tables.c#L230">230</a>                 (*rulenum)++;
<a name="L231" href="source/net/ipv4/netfilter/ip_tables.c#L231">231</a> 
<a name="L232" href="source/net/ipv4/netfilter/ip_tables.c#L232">232</a>                 if (<a href="ident?i=s">s</a>-&gt;target_offset == sizeof(struct <a href="ident?i=ipt_entry">ipt_entry</a>) &amp;&amp;
<a name="L233" href="source/net/ipv4/netfilter/ip_tables.c#L233">233</a>                     <a href="ident?i=strcmp">strcmp</a>(<a href="ident?i=t">t</a>-&gt;<a href="ident?i=target">target</a>.u.kernel.<a href="ident?i=target">target</a>-&gt;<a href="ident?i=name">name</a>,
<a name="L234" href="source/net/ipv4/netfilter/ip_tables.c#L234">234</a>                            <a href="ident?i=XT_STANDARD_TARGET">XT_STANDARD_TARGET</a>) == 0 &amp;&amp;
<a name="L235" href="source/net/ipv4/netfilter/ip_tables.c#L235">235</a>                    <a href="ident?i=t">t</a>-&gt;verdict &lt; 0 &amp;&amp;
<a name="L236" href="source/net/ipv4/netfilter/ip_tables.c#L236">236</a>                    <a href="ident?i=unconditional">unconditional</a>(&amp;<a href="ident?i=s">s</a>-&gt;<a href="ident?i=ip">ip</a>)) {
<a name="L237" href="source/net/ipv4/netfilter/ip_tables.c#L237">237</a>                         <b><i>/* Tail of chains: STANDARD target (return/policy) */</i></b>
<a name="L238" href="source/net/ipv4/netfilter/ip_tables.c#L238">238</a>                         *comment = *chainname == hookname
<a name="L239" href="source/net/ipv4/netfilter/ip_tables.c#L239">239</a>                                 ? <a href="ident?i=comments">comments</a>[NF_IP_TRACE_COMMENT_POLICY]
<a name="L240" href="source/net/ipv4/netfilter/ip_tables.c#L240">240</a>                                 : <a href="ident?i=comments">comments</a>[NF_IP_TRACE_COMMENT_RETURN];
<a name="L241" href="source/net/ipv4/netfilter/ip_tables.c#L241">241</a>                 }
<a name="L242" href="source/net/ipv4/netfilter/ip_tables.c#L242">242</a>                 return 1;
<a name="L243" href="source/net/ipv4/netfilter/ip_tables.c#L243">243</a>         } else
<a name="L244" href="source/net/ipv4/netfilter/ip_tables.c#L244">244</a>                 (*rulenum)++;
<a name="L245" href="source/net/ipv4/netfilter/ip_tables.c#L245">245</a> 
<a name="L246" href="source/net/ipv4/netfilter/ip_tables.c#L246">246</a>         return 0;
<a name="L247" href="source/net/ipv4/netfilter/ip_tables.c#L247">247</a> }
<a name="L248" href="source/net/ipv4/netfilter/ip_tables.c#L248">248</a> 
<a name="L249" href="source/net/ipv4/netfilter/ip_tables.c#L249">249</a> static void <a href="ident?i=trace_packet">trace_packet</a>(const struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
<a name="L250" href="source/net/ipv4/netfilter/ip_tables.c#L250">250</a>                          unsigned int hook,
<a name="L251" href="source/net/ipv4/netfilter/ip_tables.c#L251">251</a>                          const struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=in">in</a>,
<a name="L252" href="source/net/ipv4/netfilter/ip_tables.c#L252">252</a>                          const struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=out">out</a>,
<a name="L253" href="source/net/ipv4/netfilter/ip_tables.c#L253">253</a>                          const char *tablename,
<a name="L254" href="source/net/ipv4/netfilter/ip_tables.c#L254">254</a>                          const struct <a href="ident?i=xt_table_info">xt_table_info</a> *<a href="ident?i=private">private</a>,
<a name="L255" href="source/net/ipv4/netfilter/ip_tables.c#L255">255</a>                          const struct <a href="ident?i=ipt_entry">ipt_entry</a> *<a href="ident?i=e">e</a>)
<a name="L256" href="source/net/ipv4/netfilter/ip_tables.c#L256">256</a> {
<a name="L257" href="source/net/ipv4/netfilter/ip_tables.c#L257">257</a>         const void *table_base;
<a name="L258" href="source/net/ipv4/netfilter/ip_tables.c#L258">258</a>         const struct <a href="ident?i=ipt_entry">ipt_entry</a> *<a href="ident?i=root">root</a>;
<a name="L259" href="source/net/ipv4/netfilter/ip_tables.c#L259">259</a>         const char *hookname, *chainname, *comment;
<a name="L260" href="source/net/ipv4/netfilter/ip_tables.c#L260">260</a>         const struct <a href="ident?i=ipt_entry">ipt_entry</a> *iter;
<a name="L261" href="source/net/ipv4/netfilter/ip_tables.c#L261">261</a>         unsigned int rulenum = 0;
<a name="L262" href="source/net/ipv4/netfilter/ip_tables.c#L262">262</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=in">in</a> ? <a href="ident?i=in">in</a> : <a href="ident?i=out">out</a>);
<a name="L263" href="source/net/ipv4/netfilter/ip_tables.c#L263">263</a> 
<a name="L264" href="source/net/ipv4/netfilter/ip_tables.c#L264">264</a>         table_base = <a href="ident?i=private">private</a>-&gt;<a href="ident?i=entries">entries</a>[<a href="ident?i=smp_processor_id">smp_processor_id</a>()];
<a name="L265" href="source/net/ipv4/netfilter/ip_tables.c#L265">265</a>         <a href="ident?i=root">root</a> = <a href="ident?i=get_entry">get_entry</a>(table_base, <a href="ident?i=private">private</a>-&gt;hook_entry[hook]);
<a name="L266" href="source/net/ipv4/netfilter/ip_tables.c#L266">266</a> 
<a name="L267" href="source/net/ipv4/netfilter/ip_tables.c#L267">267</a>         hookname = chainname = <a href="ident?i=hooknames">hooknames</a>[hook];
<a name="L268" href="source/net/ipv4/netfilter/ip_tables.c#L268">268</a>         comment = <a href="ident?i=comments">comments</a>[NF_IP_TRACE_COMMENT_RULE];
<a name="L269" href="source/net/ipv4/netfilter/ip_tables.c#L269">269</a> 
<a name="L270" href="source/net/ipv4/netfilter/ip_tables.c#L270">270</a>         <a href="ident?i=xt_entry_foreach">xt_entry_foreach</a>(iter, <a href="ident?i=root">root</a>, <a href="ident?i=private">private</a>-&gt;<a href="ident?i=size">size</a> - <a href="ident?i=private">private</a>-&gt;hook_entry[hook])
<a name="L271" href="source/net/ipv4/netfilter/ip_tables.c#L271">271</a>                 if (<a href="ident?i=get_chainname_rulenum">get_chainname_rulenum</a>(iter, <a href="ident?i=e">e</a>, hookname,
<a name="L272" href="source/net/ipv4/netfilter/ip_tables.c#L272">272</a>                     &amp;chainname, &amp;comment, &amp;rulenum) != 0)
<a name="L273" href="source/net/ipv4/netfilter/ip_tables.c#L273">273</a>                         break;
<a name="L274" href="source/net/ipv4/netfilter/ip_tables.c#L274">274</a> 
<a name="L275" href="source/net/ipv4/netfilter/ip_tables.c#L275">275</a>         <a href="ident?i=nf_log_trace">nf_log_trace</a>(<a href="ident?i=net">net</a>, <a href="ident?i=AF_INET">AF_INET</a>, hook, <a href="ident?i=skb">skb</a>, <a href="ident?i=in">in</a>, <a href="ident?i=out">out</a>, &amp;<a href="ident?i=trace_loginfo">trace_loginfo</a>,
<a name="L276" href="source/net/ipv4/netfilter/ip_tables.c#L276">276</a>                      <i>"TRACE: %s:%s:%s:%u "</i>,
<a name="L277" href="source/net/ipv4/netfilter/ip_tables.c#L277">277</a>                      tablename, chainname, comment, rulenum);
<a name="L278" href="source/net/ipv4/netfilter/ip_tables.c#L278">278</a> }
<a name="L279" href="source/net/ipv4/netfilter/ip_tables.c#L279">279</a> #endif
<a name="L280" href="source/net/ipv4/netfilter/ip_tables.c#L280">280</a> 
<a name="L281" href="source/net/ipv4/netfilter/ip_tables.c#L281">281</a> static inline <a href="ident?i=__pure">__pure</a>
<a name="L282" href="source/net/ipv4/netfilter/ip_tables.c#L282">282</a> struct <a href="ident?i=ipt_entry">ipt_entry</a> *<a href="ident?i=ipt_next_entry">ipt_next_entry</a>(const struct <a href="ident?i=ipt_entry">ipt_entry</a> *<a href="ident?i=entry">entry</a>)
<a name="L283" href="source/net/ipv4/netfilter/ip_tables.c#L283">283</a> {
<a name="L284" href="source/net/ipv4/netfilter/ip_tables.c#L284">284</a>         return (void *)<a href="ident?i=entry">entry</a> + <a href="ident?i=entry">entry</a>-&gt;next_offset;
<a name="L285" href="source/net/ipv4/netfilter/ip_tables.c#L285">285</a> }
<a name="L286" href="source/net/ipv4/netfilter/ip_tables.c#L286">286</a> 
<a name="L287" href="source/net/ipv4/netfilter/ip_tables.c#L287">287</a> <b><i>/* Returns one of the generic firewall policies, like NF_ACCEPT. */</i></b>
<a name="L288" href="source/net/ipv4/netfilter/ip_tables.c#L288">288</a> unsigned int
<a name="L289" href="source/net/ipv4/netfilter/ip_tables.c#L289">289</a> <a href="ident?i=ipt_do_table">ipt_do_table</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
<a name="L290" href="source/net/ipv4/netfilter/ip_tables.c#L290">290</a>              unsigned int hook,
<a name="L291" href="source/net/ipv4/netfilter/ip_tables.c#L291">291</a>              const struct <a href="ident?i=nf_hook_state">nf_hook_state</a> *<a href="ident?i=state">state</a>,
<a name="L292" href="source/net/ipv4/netfilter/ip_tables.c#L292">292</a>              struct <a href="ident?i=xt_table">xt_table</a> *<a href="ident?i=table">table</a>)
<a name="L293" href="source/net/ipv4/netfilter/ip_tables.c#L293">293</a> {
<a name="L294" href="source/net/ipv4/netfilter/ip_tables.c#L294">294</a>         static const char nulldevname[<a href="ident?i=IFNAMSIZ">IFNAMSIZ</a>] <a href="ident?i=__attribute__">__attribute__</a>((aligned(sizeof(long))));
<a name="L295" href="source/net/ipv4/netfilter/ip_tables.c#L295">295</a>         const struct <a href="ident?i=iphdr">iphdr</a> *<a href="ident?i=ip">ip</a>;
<a name="L296" href="source/net/ipv4/netfilter/ip_tables.c#L296">296</a>         <b><i>/* Initializing verdict to NF_DROP keeps gcc happy. */</i></b>
<a name="L297" href="source/net/ipv4/netfilter/ip_tables.c#L297">297</a>         unsigned int verdict = <a href="ident?i=NF_DROP">NF_DROP</a>;
<a name="L298" href="source/net/ipv4/netfilter/ip_tables.c#L298">298</a>         const char *indev, *outdev;
<a name="L299" href="source/net/ipv4/netfilter/ip_tables.c#L299">299</a>         const void *table_base;
<a name="L300" href="source/net/ipv4/netfilter/ip_tables.c#L300">300</a>         struct <a href="ident?i=ipt_entry">ipt_entry</a> *<a href="ident?i=e">e</a>, **jumpstack;
<a name="L301" href="source/net/ipv4/netfilter/ip_tables.c#L301">301</a>         unsigned int *stackptr, origptr, <a href="ident?i=cpu">cpu</a>;
<a name="L302" href="source/net/ipv4/netfilter/ip_tables.c#L302">302</a>         const struct <a href="ident?i=xt_table_info">xt_table_info</a> *<a href="ident?i=private">private</a>;
<a name="L303" href="source/net/ipv4/netfilter/ip_tables.c#L303">303</a>         struct <a href="ident?i=xt_action_param">xt_action_param</a> acpar;
<a name="L304" href="source/net/ipv4/netfilter/ip_tables.c#L304">304</a>         unsigned int addend;
<a name="L305" href="source/net/ipv4/netfilter/ip_tables.c#L305">305</a> 
<a name="L306" href="source/net/ipv4/netfilter/ip_tables.c#L306">306</a>         <b><i>/* Initialization */</i></b>
<a name="L307" href="source/net/ipv4/netfilter/ip_tables.c#L307">307</a>         <a href="ident?i=ip">ip</a> = <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>);
<a name="L308" href="source/net/ipv4/netfilter/ip_tables.c#L308">308</a>         indev = <a href="ident?i=state">state</a>-&gt;<a href="ident?i=in">in</a> ? <a href="ident?i=state">state</a>-&gt;<a href="ident?i=in">in</a>-&gt;<a href="ident?i=name">name</a> : nulldevname;
<a name="L309" href="source/net/ipv4/netfilter/ip_tables.c#L309">309</a>         outdev = <a href="ident?i=state">state</a>-&gt;<a href="ident?i=out">out</a> ? <a href="ident?i=state">state</a>-&gt;<a href="ident?i=out">out</a>-&gt;<a href="ident?i=name">name</a> : nulldevname;
<a name="L310" href="source/net/ipv4/netfilter/ip_tables.c#L310">310</a>         <b><i>/* We handle fragments by dealing with the first fragment as</i></b>
<a name="L311" href="source/net/ipv4/netfilter/ip_tables.c#L311">311</a> <b><i>         * if it was a normal packet.  All other fragments are treated</i></b>
<a name="L312" href="source/net/ipv4/netfilter/ip_tables.c#L312">312</a> <b><i>         * normally, except that they will NEVER match rules that ask</i></b>
<a name="L313" href="source/net/ipv4/netfilter/ip_tables.c#L313">313</a> <b><i>         * things we don't know, ie. tcp syn flag or ports).  If the</i></b>
<a name="L314" href="source/net/ipv4/netfilter/ip_tables.c#L314">314</a> <b><i>         * rule is also a fragment-specific rule, non-fragments won't</i></b>
<a name="L315" href="source/net/ipv4/netfilter/ip_tables.c#L315">315</a> <b><i>         * match it. */</i></b>
<a name="L316" href="source/net/ipv4/netfilter/ip_tables.c#L316">316</a>         acpar.fragoff = <a href="ident?i=ntohs">ntohs</a>(<a href="ident?i=ip">ip</a>-&gt;frag_off) &amp; <a href="ident?i=IP_OFFSET">IP_OFFSET</a>;
<a name="L317" href="source/net/ipv4/netfilter/ip_tables.c#L317">317</a>         acpar.thoff   = <a href="ident?i=ip_hdrlen">ip_hdrlen</a>(<a href="ident?i=skb">skb</a>);
<a name="L318" href="source/net/ipv4/netfilter/ip_tables.c#L318">318</a>         acpar.hotdrop = <a href="ident?i=false">false</a>;
<a name="L319" href="source/net/ipv4/netfilter/ip_tables.c#L319">319</a>         acpar.<a href="ident?i=in">in</a>      = <a href="ident?i=state">state</a>-&gt;<a href="ident?i=in">in</a>;
<a name="L320" href="source/net/ipv4/netfilter/ip_tables.c#L320">320</a>         acpar.<a href="ident?i=out">out</a>     = <a href="ident?i=state">state</a>-&gt;<a href="ident?i=out">out</a>;
<a name="L321" href="source/net/ipv4/netfilter/ip_tables.c#L321">321</a>         acpar.<a href="ident?i=family">family</a>  = NFPROTO_IPV4;
<a name="L322" href="source/net/ipv4/netfilter/ip_tables.c#L322">322</a>         acpar.hooknum = hook;
<a name="L323" href="source/net/ipv4/netfilter/ip_tables.c#L323">323</a> 
<a name="L324" href="source/net/ipv4/netfilter/ip_tables.c#L324">324</a>         <a href="ident?i=IP_NF_ASSERT">IP_NF_ASSERT</a>(<a href="ident?i=table">table</a>-&gt;valid_hooks &amp; (1 &lt;&lt; hook));
<a name="L325" href="source/net/ipv4/netfilter/ip_tables.c#L325">325</a>         <a href="ident?i=local_bh_disable">local_bh_disable</a>();
<a name="L326" href="source/net/ipv4/netfilter/ip_tables.c#L326">326</a>         addend = <a href="ident?i=xt_write_recseq_begin">xt_write_recseq_begin</a>();
<a name="L327" href="source/net/ipv4/netfilter/ip_tables.c#L327">327</a>         <a href="ident?i=private">private</a> = <a href="ident?i=table">table</a>-&gt;<a href="ident?i=private">private</a>;
<a name="L328" href="source/net/ipv4/netfilter/ip_tables.c#L328">328</a>         <a href="ident?i=cpu">cpu</a>        = <a href="ident?i=smp_processor_id">smp_processor_id</a>();
<a name="L329" href="source/net/ipv4/netfilter/ip_tables.c#L329">329</a>         <b><i>/*</i></b>
<a name="L330" href="source/net/ipv4/netfilter/ip_tables.c#L330">330</a> <b><i>         * Ensure we load private-&gt; members after we've fetched the base</i></b>
<a name="L331" href="source/net/ipv4/netfilter/ip_tables.c#L331">331</a> <b><i>         * pointer.</i></b>
<a name="L332" href="source/net/ipv4/netfilter/ip_tables.c#L332">332</a> <b><i>         */</i></b>
<a name="L333" href="source/net/ipv4/netfilter/ip_tables.c#L333">333</a>         <a href="ident?i=smp_read_barrier_depends">smp_read_barrier_depends</a>();
<a name="L334" href="source/net/ipv4/netfilter/ip_tables.c#L334">334</a>         table_base = <a href="ident?i=private">private</a>-&gt;<a href="ident?i=entries">entries</a>[<a href="ident?i=cpu">cpu</a>];
<a name="L335" href="source/net/ipv4/netfilter/ip_tables.c#L335">335</a>         jumpstack  = (struct <a href="ident?i=ipt_entry">ipt_entry</a> **)<a href="ident?i=private">private</a>-&gt;jumpstack[<a href="ident?i=cpu">cpu</a>];
<a name="L336" href="source/net/ipv4/netfilter/ip_tables.c#L336">336</a>         stackptr   = <a href="ident?i=per_cpu_ptr">per_cpu_ptr</a>(<a href="ident?i=private">private</a>-&gt;stackptr, <a href="ident?i=cpu">cpu</a>);
<a name="L337" href="source/net/ipv4/netfilter/ip_tables.c#L337">337</a>         origptr    = *stackptr;
<a name="L338" href="source/net/ipv4/netfilter/ip_tables.c#L338">338</a> 
<a name="L339" href="source/net/ipv4/netfilter/ip_tables.c#L339">339</a>         <a href="ident?i=e">e</a> = <a href="ident?i=get_entry">get_entry</a>(table_base, <a href="ident?i=private">private</a>-&gt;hook_entry[hook]);
<a name="L340" href="source/net/ipv4/netfilter/ip_tables.c#L340">340</a> 
<a name="L341" href="source/net/ipv4/netfilter/ip_tables.c#L341">341</a>         <a href="ident?i=pr_debug">pr_debug</a>(<i>"Entering %s(hook %u); sp at %u (UF %p)\n"</i>,
<a name="L342" href="source/net/ipv4/netfilter/ip_tables.c#L342">342</a>                  <a href="ident?i=table">table</a>-&gt;<a href="ident?i=name">name</a>, hook, origptr,
<a name="L343" href="source/net/ipv4/netfilter/ip_tables.c#L343">343</a>                  <a href="ident?i=get_entry">get_entry</a>(table_base, <a href="ident?i=private">private</a>-&gt;underflow[hook]));
<a name="L344" href="source/net/ipv4/netfilter/ip_tables.c#L344">344</a> 
<a name="L345" href="source/net/ipv4/netfilter/ip_tables.c#L345">345</a>         do {
<a name="L346" href="source/net/ipv4/netfilter/ip_tables.c#L346">346</a>                 const struct <a href="ident?i=xt_entry_target">xt_entry_target</a> *<a href="ident?i=t">t</a>;
<a name="L347" href="source/net/ipv4/netfilter/ip_tables.c#L347">347</a>                 const struct <a href="ident?i=xt_entry_match">xt_entry_match</a> *ematch;
<a name="L348" href="source/net/ipv4/netfilter/ip_tables.c#L348">348</a> 
<a name="L349" href="source/net/ipv4/netfilter/ip_tables.c#L349">349</a>                 <a href="ident?i=IP_NF_ASSERT">IP_NF_ASSERT</a>(<a href="ident?i=e">e</a>);
<a name="L350" href="source/net/ipv4/netfilter/ip_tables.c#L350">350</a>                 if (!<a href="ident?i=ip_packet_match">ip_packet_match</a>(<a href="ident?i=ip">ip</a>, indev, outdev,
<a name="L351" href="source/net/ipv4/netfilter/ip_tables.c#L351">351</a>                     &amp;<a href="ident?i=e">e</a>-&gt;<a href="ident?i=ip">ip</a>, acpar.fragoff)) {
<a name="L352" href="source/net/ipv4/netfilter/ip_tables.c#L352">352</a>  no_match:
<a name="L353" href="source/net/ipv4/netfilter/ip_tables.c#L353">353</a>                         <a href="ident?i=e">e</a> = <a href="ident?i=ipt_next_entry">ipt_next_entry</a>(<a href="ident?i=e">e</a>);
<a name="L354" href="source/net/ipv4/netfilter/ip_tables.c#L354">354</a>                         continue;
<a name="L355" href="source/net/ipv4/netfilter/ip_tables.c#L355">355</a>                 }
<a name="L356" href="source/net/ipv4/netfilter/ip_tables.c#L356">356</a> 
<a name="L357" href="source/net/ipv4/netfilter/ip_tables.c#L357">357</a>                 <a href="ident?i=xt_ematch_foreach">xt_ematch_foreach</a>(ematch, <a href="ident?i=e">e</a>) {
<a name="L358" href="source/net/ipv4/netfilter/ip_tables.c#L358">358</a>                         acpar.<a href="ident?i=match">match</a>     = ematch-&gt;u.kernel.<a href="ident?i=match">match</a>;
<a name="L359" href="source/net/ipv4/netfilter/ip_tables.c#L359">359</a>                         acpar.matchinfo = ematch-&gt;<a href="ident?i=data">data</a>;
<a name="L360" href="source/net/ipv4/netfilter/ip_tables.c#L360">360</a>                         if (!acpar.<a href="ident?i=match">match</a>-&gt;<a href="ident?i=match">match</a>(<a href="ident?i=skb">skb</a>, &amp;acpar))
<a name="L361" href="source/net/ipv4/netfilter/ip_tables.c#L361">361</a>                                 goto no_match;
<a name="L362" href="source/net/ipv4/netfilter/ip_tables.c#L362">362</a>                 }
<a name="L363" href="source/net/ipv4/netfilter/ip_tables.c#L363">363</a> 
<a name="L364" href="source/net/ipv4/netfilter/ip_tables.c#L364">364</a>                 <a href="ident?i=ADD_COUNTER">ADD_COUNTER</a>(<a href="ident?i=e">e</a>-&gt;counters, <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a>, 1);
<a name="L365" href="source/net/ipv4/netfilter/ip_tables.c#L365">365</a> 
<a name="L366" href="source/net/ipv4/netfilter/ip_tables.c#L366">366</a>                 <a href="ident?i=t">t</a> = <a href="ident?i=ipt_get_target">ipt_get_target</a>(<a href="ident?i=e">e</a>);
<a name="L367" href="source/net/ipv4/netfilter/ip_tables.c#L367">367</a>                 <a href="ident?i=IP_NF_ASSERT">IP_NF_ASSERT</a>(<a href="ident?i=t">t</a>-&gt;u.kernel.<a href="ident?i=target">target</a>);
<a name="L368" href="source/net/ipv4/netfilter/ip_tables.c#L368">368</a> 
<a name="L369" href="source/net/ipv4/netfilter/ip_tables.c#L369">369</a> #if <a href="ident?i=IS_ENABLED">IS_ENABLED</a>(CONFIG_NETFILTER_XT_TARGET_TRACE)
<a name="L370" href="source/net/ipv4/netfilter/ip_tables.c#L370">370</a>                 <b><i>/* The packet is traced: log it */</i></b>
<a name="L371" href="source/net/ipv4/netfilter/ip_tables.c#L371">371</a>                 if (<a href="ident?i=unlikely">unlikely</a>(<a href="ident?i=skb">skb</a>-&gt;nf_trace))
<a name="L372" href="source/net/ipv4/netfilter/ip_tables.c#L372">372</a>                         <a href="ident?i=trace_packet">trace_packet</a>(<a href="ident?i=skb">skb</a>, hook, <a href="ident?i=state">state</a>-&gt;<a href="ident?i=in">in</a>, <a href="ident?i=state">state</a>-&gt;<a href="ident?i=out">out</a>,
<a name="L373" href="source/net/ipv4/netfilter/ip_tables.c#L373">373</a>                                      <a href="ident?i=table">table</a>-&gt;<a href="ident?i=name">name</a>, <a href="ident?i=private">private</a>, <a href="ident?i=e">e</a>);
<a name="L374" href="source/net/ipv4/netfilter/ip_tables.c#L374">374</a> #endif
<a name="L375" href="source/net/ipv4/netfilter/ip_tables.c#L375">375</a>                 <b><i>/* Standard target? */</i></b>
<a name="L376" href="source/net/ipv4/netfilter/ip_tables.c#L376">376</a>                 if (!<a href="ident?i=t">t</a>-&gt;u.kernel.<a href="ident?i=target">target</a>-&gt;<a href="ident?i=target">target</a>) {
<a name="L377" href="source/net/ipv4/netfilter/ip_tables.c#L377">377</a>                         int <a href="ident?i=v">v</a>;
<a name="L378" href="source/net/ipv4/netfilter/ip_tables.c#L378">378</a> 
<a name="L379" href="source/net/ipv4/netfilter/ip_tables.c#L379">379</a>                         <a href="ident?i=v">v</a> = ((struct <a href="ident?i=xt_standard_target">xt_standard_target</a> *)<a href="ident?i=t">t</a>)-&gt;verdict;
<a name="L380" href="source/net/ipv4/netfilter/ip_tables.c#L380">380</a>                         if (<a href="ident?i=v">v</a> &lt; 0) {
<a name="L381" href="source/net/ipv4/netfilter/ip_tables.c#L381">381</a>                                 <b><i>/* Pop from stack? */</i></b>
<a name="L382" href="source/net/ipv4/netfilter/ip_tables.c#L382">382</a>                                 if (<a href="ident?i=v">v</a> != <a href="ident?i=XT_RETURN">XT_RETURN</a>) {
<a name="L383" href="source/net/ipv4/netfilter/ip_tables.c#L383">383</a>                                         verdict = (unsigned int)(-<a href="ident?i=v">v</a>) - 1;
<a name="L384" href="source/net/ipv4/netfilter/ip_tables.c#L384">384</a>                                         break;
<a name="L385" href="source/net/ipv4/netfilter/ip_tables.c#L385">385</a>                                 }
<a name="L386" href="source/net/ipv4/netfilter/ip_tables.c#L386">386</a>                                 if (*stackptr &lt;= origptr) {
<a name="L387" href="source/net/ipv4/netfilter/ip_tables.c#L387">387</a>                                         <a href="ident?i=e">e</a> = <a href="ident?i=get_entry">get_entry</a>(table_base,
<a name="L388" href="source/net/ipv4/netfilter/ip_tables.c#L388">388</a>                                             <a href="ident?i=private">private</a>-&gt;underflow[hook]);
<a name="L389" href="source/net/ipv4/netfilter/ip_tables.c#L389">389</a>                                         <a href="ident?i=pr_debug">pr_debug</a>(<i>"Underflow (this is normal) "</i>
<a name="L390" href="source/net/ipv4/netfilter/ip_tables.c#L390">390</a>                                                  <i>"to %p\n"</i>, <a href="ident?i=e">e</a>);
<a name="L391" href="source/net/ipv4/netfilter/ip_tables.c#L391">391</a>                                 } else {
<a name="L392" href="source/net/ipv4/netfilter/ip_tables.c#L392">392</a>                                         <a href="ident?i=e">e</a> = jumpstack[--*stackptr];
<a name="L393" href="source/net/ipv4/netfilter/ip_tables.c#L393">393</a>                                         <a href="ident?i=pr_debug">pr_debug</a>(<i>"Pulled %p out from pos %u\n"</i>,
<a name="L394" href="source/net/ipv4/netfilter/ip_tables.c#L394">394</a>                                                  <a href="ident?i=e">e</a>, *stackptr);
<a name="L395" href="source/net/ipv4/netfilter/ip_tables.c#L395">395</a>                                         <a href="ident?i=e">e</a> = <a href="ident?i=ipt_next_entry">ipt_next_entry</a>(<a href="ident?i=e">e</a>);
<a name="L396" href="source/net/ipv4/netfilter/ip_tables.c#L396">396</a>                                 }
<a name="L397" href="source/net/ipv4/netfilter/ip_tables.c#L397">397</a>                                 continue;
<a name="L398" href="source/net/ipv4/netfilter/ip_tables.c#L398">398</a>                         }
<a name="L399" href="source/net/ipv4/netfilter/ip_tables.c#L399">399</a>                         if (table_base + <a href="ident?i=v">v</a> != <a href="ident?i=ipt_next_entry">ipt_next_entry</a>(<a href="ident?i=e">e</a>) &amp;&amp;
<a name="L400" href="source/net/ipv4/netfilter/ip_tables.c#L400">400</a>                             !(<a href="ident?i=e">e</a>-&gt;<a href="ident?i=ip">ip</a>.<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=IPT_F_GOTO">IPT_F_GOTO</a>)) {
<a name="L401" href="source/net/ipv4/netfilter/ip_tables.c#L401">401</a>                                 if (*stackptr &gt;= <a href="ident?i=private">private</a>-&gt;stacksize) {
<a name="L402" href="source/net/ipv4/netfilter/ip_tables.c#L402">402</a>                                         verdict = <a href="ident?i=NF_DROP">NF_DROP</a>;
<a name="L403" href="source/net/ipv4/netfilter/ip_tables.c#L403">403</a>                                         break;
<a name="L404" href="source/net/ipv4/netfilter/ip_tables.c#L404">404</a>                                 }
<a name="L405" href="source/net/ipv4/netfilter/ip_tables.c#L405">405</a>                                 jumpstack[(*stackptr)++] = <a href="ident?i=e">e</a>;
<a name="L406" href="source/net/ipv4/netfilter/ip_tables.c#L406">406</a>                                 <a href="ident?i=pr_debug">pr_debug</a>(<i>"Pushed %p into pos %u\n"</i>,
<a name="L407" href="source/net/ipv4/netfilter/ip_tables.c#L407">407</a>                                          <a href="ident?i=e">e</a>, *stackptr - 1);
<a name="L408" href="source/net/ipv4/netfilter/ip_tables.c#L408">408</a>                         }
<a name="L409" href="source/net/ipv4/netfilter/ip_tables.c#L409">409</a> 
<a name="L410" href="source/net/ipv4/netfilter/ip_tables.c#L410">410</a>                         <a href="ident?i=e">e</a> = <a href="ident?i=get_entry">get_entry</a>(table_base, <a href="ident?i=v">v</a>);
<a name="L411" href="source/net/ipv4/netfilter/ip_tables.c#L411">411</a>                         continue;
<a name="L412" href="source/net/ipv4/netfilter/ip_tables.c#L412">412</a>                 }
<a name="L413" href="source/net/ipv4/netfilter/ip_tables.c#L413">413</a> 
<a name="L414" href="source/net/ipv4/netfilter/ip_tables.c#L414">414</a>                 acpar.<a href="ident?i=target">target</a>   = <a href="ident?i=t">t</a>-&gt;u.kernel.<a href="ident?i=target">target</a>;
<a name="L415" href="source/net/ipv4/netfilter/ip_tables.c#L415">415</a>                 acpar.targinfo = <a href="ident?i=t">t</a>-&gt;<a href="ident?i=data">data</a>;
<a name="L416" href="source/net/ipv4/netfilter/ip_tables.c#L416">416</a> 
<a name="L417" href="source/net/ipv4/netfilter/ip_tables.c#L417">417</a>                 verdict = <a href="ident?i=t">t</a>-&gt;u.kernel.<a href="ident?i=target">target</a>-&gt;<a href="ident?i=target">target</a>(<a href="ident?i=skb">skb</a>, &amp;acpar);
<a name="L418" href="source/net/ipv4/netfilter/ip_tables.c#L418">418</a>                 <b><i>/* Target might have changed stuff. */</i></b>
<a name="L419" href="source/net/ipv4/netfilter/ip_tables.c#L419">419</a>                 <a href="ident?i=ip">ip</a> = <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>);
<a name="L420" href="source/net/ipv4/netfilter/ip_tables.c#L420">420</a>                 if (verdict == <a href="ident?i=XT_CONTINUE">XT_CONTINUE</a>)
<a name="L421" href="source/net/ipv4/netfilter/ip_tables.c#L421">421</a>                         <a href="ident?i=e">e</a> = <a href="ident?i=ipt_next_entry">ipt_next_entry</a>(<a href="ident?i=e">e</a>);
<a name="L422" href="source/net/ipv4/netfilter/ip_tables.c#L422">422</a>                 else
<a name="L423" href="source/net/ipv4/netfilter/ip_tables.c#L423">423</a>                         <b><i>/* Verdict */</i></b>
<a name="L424" href="source/net/ipv4/netfilter/ip_tables.c#L424">424</a>                         break;
<a name="L425" href="source/net/ipv4/netfilter/ip_tables.c#L425">425</a>         } while (!acpar.hotdrop);
<a name="L426" href="source/net/ipv4/netfilter/ip_tables.c#L426">426</a>         <a href="ident?i=pr_debug">pr_debug</a>(<i>"Exiting %s; resetting sp from %u to %u\n"</i>,
<a name="L427" href="source/net/ipv4/netfilter/ip_tables.c#L427">427</a>                  <a href="ident?i=__func__">__func__</a>, *stackptr, origptr);
<a name="L428" href="source/net/ipv4/netfilter/ip_tables.c#L428">428</a>         *stackptr = origptr;
<a name="L429" href="source/net/ipv4/netfilter/ip_tables.c#L429">429</a>         <a href="ident?i=xt_write_recseq_end">xt_write_recseq_end</a>(addend);
<a name="L430" href="source/net/ipv4/netfilter/ip_tables.c#L430">430</a>         <a href="ident?i=local_bh_enable">local_bh_enable</a>();
<a name="L431" href="source/net/ipv4/netfilter/ip_tables.c#L431">431</a> 
<a name="L432" href="source/net/ipv4/netfilter/ip_tables.c#L432">432</a> #ifdef DEBUG_ALLOW_ALL
<a name="L433" href="source/net/ipv4/netfilter/ip_tables.c#L433">433</a>         return <a href="ident?i=NF_ACCEPT">NF_ACCEPT</a>;
<a name="L434" href="source/net/ipv4/netfilter/ip_tables.c#L434">434</a> #else
<a name="L435" href="source/net/ipv4/netfilter/ip_tables.c#L435">435</a>         if (acpar.hotdrop)
<a name="L436" href="source/net/ipv4/netfilter/ip_tables.c#L436">436</a>                 return <a href="ident?i=NF_DROP">NF_DROP</a>;
<a name="L437" href="source/net/ipv4/netfilter/ip_tables.c#L437">437</a>         else return verdict;
<a name="L438" href="source/net/ipv4/netfilter/ip_tables.c#L438">438</a> #endif
<a name="L439" href="source/net/ipv4/netfilter/ip_tables.c#L439">439</a> }
<a name="L440" href="source/net/ipv4/netfilter/ip_tables.c#L440">440</a> 
<a name="L441" href="source/net/ipv4/netfilter/ip_tables.c#L441">441</a> <b><i>/* Figures out from what hook each rule can be called: returns 0 if</i></b>
<a name="L442" href="source/net/ipv4/netfilter/ip_tables.c#L442">442</a> <b><i>   there are loops.  Puts hook bitmask in comefrom. */</i></b>
<a name="L443" href="source/net/ipv4/netfilter/ip_tables.c#L443">443</a> static int
<a name="L444" href="source/net/ipv4/netfilter/ip_tables.c#L444">444</a> <a href="ident?i=mark_source_chains">mark_source_chains</a>(const struct <a href="ident?i=xt_table_info">xt_table_info</a> *newinfo,
<a name="L445" href="source/net/ipv4/netfilter/ip_tables.c#L445">445</a>                    unsigned int valid_hooks, void *entry0)
<a name="L446" href="source/net/ipv4/netfilter/ip_tables.c#L446">446</a> {
<a name="L447" href="source/net/ipv4/netfilter/ip_tables.c#L447">447</a>         unsigned int hook;
<a name="L448" href="source/net/ipv4/netfilter/ip_tables.c#L448">448</a> 
<a name="L449" href="source/net/ipv4/netfilter/ip_tables.c#L449">449</a>         <b><i>/* No recursion; use packet counter to save back ptrs (reset</i></b>
<a name="L450" href="source/net/ipv4/netfilter/ip_tables.c#L450">450</a> <b><i>           to 0 as we leave), and comefrom to save source hook bitmask */</i></b>
<a name="L451" href="source/net/ipv4/netfilter/ip_tables.c#L451">451</a>         for (hook = 0; hook &lt; NF_INET_NUMHOOKS; hook++) {
<a name="L452" href="source/net/ipv4/netfilter/ip_tables.c#L452">452</a>                 unsigned int <a href="ident?i=pos">pos</a> = newinfo-&gt;hook_entry[hook];
<a name="L453" href="source/net/ipv4/netfilter/ip_tables.c#L453">453</a>                 struct <a href="ident?i=ipt_entry">ipt_entry</a> *<a href="ident?i=e">e</a> = (struct <a href="ident?i=ipt_entry">ipt_entry</a> *)(entry0 + <a href="ident?i=pos">pos</a>);
<a name="L454" href="source/net/ipv4/netfilter/ip_tables.c#L454">454</a> 
<a name="L455" href="source/net/ipv4/netfilter/ip_tables.c#L455">455</a>                 if (!(valid_hooks &amp; (1 &lt;&lt; hook)))
<a name="L456" href="source/net/ipv4/netfilter/ip_tables.c#L456">456</a>                         continue;
<a name="L457" href="source/net/ipv4/netfilter/ip_tables.c#L457">457</a> 
<a name="L458" href="source/net/ipv4/netfilter/ip_tables.c#L458">458</a>                 <b><i>/* Set initial back pointer. */</i></b>
<a name="L459" href="source/net/ipv4/netfilter/ip_tables.c#L459">459</a>                 <a href="ident?i=e">e</a>-&gt;counters.pcnt = <a href="ident?i=pos">pos</a>;
<a name="L460" href="source/net/ipv4/netfilter/ip_tables.c#L460">460</a> 
<a name="L461" href="source/net/ipv4/netfilter/ip_tables.c#L461">461</a>                 for (;;) {
<a name="L462" href="source/net/ipv4/netfilter/ip_tables.c#L462">462</a>                         const struct <a href="ident?i=xt_standard_target">xt_standard_target</a> *<a href="ident?i=t">t</a>
<a name="L463" href="source/net/ipv4/netfilter/ip_tables.c#L463">463</a>                                 = (void *)<a href="ident?i=ipt_get_target_c">ipt_get_target_c</a>(<a href="ident?i=e">e</a>);
<a name="L464" href="source/net/ipv4/netfilter/ip_tables.c#L464">464</a>                         int visited = <a href="ident?i=e">e</a>-&gt;comefrom &amp; (1 &lt;&lt; hook);
<a name="L465" href="source/net/ipv4/netfilter/ip_tables.c#L465">465</a> 
<a name="L466" href="source/net/ipv4/netfilter/ip_tables.c#L466">466</a>                         if (<a href="ident?i=e">e</a>-&gt;comefrom &amp; (1 &lt;&lt; NF_INET_NUMHOOKS)) {
<a name="L467" href="source/net/ipv4/netfilter/ip_tables.c#L467">467</a>                                 <a href="ident?i=pr_err">pr_err</a>(<i>"iptables: loop hook %u pos %u %08X.\n"</i>,
<a name="L468" href="source/net/ipv4/netfilter/ip_tables.c#L468">468</a>                                        hook, <a href="ident?i=pos">pos</a>, <a href="ident?i=e">e</a>-&gt;comefrom);
<a name="L469" href="source/net/ipv4/netfilter/ip_tables.c#L469">469</a>                                 return 0;
<a name="L470" href="source/net/ipv4/netfilter/ip_tables.c#L470">470</a>                         }
<a name="L471" href="source/net/ipv4/netfilter/ip_tables.c#L471">471</a>                         <a href="ident?i=e">e</a>-&gt;comefrom |= ((1 &lt;&lt; hook) | (1 &lt;&lt; NF_INET_NUMHOOKS));
<a name="L472" href="source/net/ipv4/netfilter/ip_tables.c#L472">472</a> 
<a name="L473" href="source/net/ipv4/netfilter/ip_tables.c#L473">473</a>                         <b><i>/* Unconditional return/END. */</i></b>
<a name="L474" href="source/net/ipv4/netfilter/ip_tables.c#L474">474</a>                         if ((<a href="ident?i=e">e</a>-&gt;target_offset == sizeof(struct <a href="ident?i=ipt_entry">ipt_entry</a>) &amp;&amp;
<a name="L475" href="source/net/ipv4/netfilter/ip_tables.c#L475">475</a>                              (<a href="ident?i=strcmp">strcmp</a>(<a href="ident?i=t">t</a>-&gt;<a href="ident?i=target">target</a>.u.<a href="ident?i=user">user</a>.<a href="ident?i=name">name</a>,
<a name="L476" href="source/net/ipv4/netfilter/ip_tables.c#L476">476</a>                                      <a href="ident?i=XT_STANDARD_TARGET">XT_STANDARD_TARGET</a>) == 0) &amp;&amp;
<a name="L477" href="source/net/ipv4/netfilter/ip_tables.c#L477">477</a>                              <a href="ident?i=t">t</a>-&gt;verdict &lt; 0 &amp;&amp; <a href="ident?i=unconditional">unconditional</a>(&amp;<a href="ident?i=e">e</a>-&gt;<a href="ident?i=ip">ip</a>)) ||
<a name="L478" href="source/net/ipv4/netfilter/ip_tables.c#L478">478</a>                             visited) {
<a name="L479" href="source/net/ipv4/netfilter/ip_tables.c#L479">479</a>                                 unsigned int oldpos, <a href="ident?i=size">size</a>;
<a name="L480" href="source/net/ipv4/netfilter/ip_tables.c#L480">480</a> 
<a name="L481" href="source/net/ipv4/netfilter/ip_tables.c#L481">481</a>                                 if ((<a href="ident?i=strcmp">strcmp</a>(<a href="ident?i=t">t</a>-&gt;<a href="ident?i=target">target</a>.u.<a href="ident?i=user">user</a>.<a href="ident?i=name">name</a>,
<a name="L482" href="source/net/ipv4/netfilter/ip_tables.c#L482">482</a>                                             <a href="ident?i=XT_STANDARD_TARGET">XT_STANDARD_TARGET</a>) == 0) &amp;&amp;
<a name="L483" href="source/net/ipv4/netfilter/ip_tables.c#L483">483</a>                                     <a href="ident?i=t">t</a>-&gt;verdict &lt; -<a href="ident?i=NF_MAX_VERDICT">NF_MAX_VERDICT</a> - 1) {
<a name="L484" href="source/net/ipv4/netfilter/ip_tables.c#L484">484</a>                                         <a href="ident?i=duprintf">duprintf</a>(<i>"mark_source_chains: bad "</i>
<a name="L485" href="source/net/ipv4/netfilter/ip_tables.c#L485">485</a>                                                 <i>"negative verdict (%i)\n"</i>,
<a name="L486" href="source/net/ipv4/netfilter/ip_tables.c#L486">486</a>                                                                 <a href="ident?i=t">t</a>-&gt;verdict);
<a name="L487" href="source/net/ipv4/netfilter/ip_tables.c#L487">487</a>                                         return 0;
<a name="L488" href="source/net/ipv4/netfilter/ip_tables.c#L488">488</a>                                 }
<a name="L489" href="source/net/ipv4/netfilter/ip_tables.c#L489">489</a> 
<a name="L490" href="source/net/ipv4/netfilter/ip_tables.c#L490">490</a>                                 <b><i>/* Return: backtrack through the last</i></b>
<a name="L491" href="source/net/ipv4/netfilter/ip_tables.c#L491">491</a> <b><i>                                   big jump. */</i></b>
<a name="L492" href="source/net/ipv4/netfilter/ip_tables.c#L492">492</a>                                 do {
<a name="L493" href="source/net/ipv4/netfilter/ip_tables.c#L493">493</a>                                         <a href="ident?i=e">e</a>-&gt;comefrom ^= (1&lt;&lt;NF_INET_NUMHOOKS);
<a name="L494" href="source/net/ipv4/netfilter/ip_tables.c#L494">494</a> #ifdef DEBUG_IP_FIREWALL_USER
<a name="L495" href="source/net/ipv4/netfilter/ip_tables.c#L495">495</a>                                         if (<a href="ident?i=e">e</a>-&gt;comefrom
<a name="L496" href="source/net/ipv4/netfilter/ip_tables.c#L496">496</a>                                             &amp; (1 &lt;&lt; NF_INET_NUMHOOKS)) {
<a name="L497" href="source/net/ipv4/netfilter/ip_tables.c#L497">497</a>                                                 <a href="ident?i=duprintf">duprintf</a>(<i>"Back unset "</i>
<a name="L498" href="source/net/ipv4/netfilter/ip_tables.c#L498">498</a>                                                          <i>"on hook %u "</i>
<a name="L499" href="source/net/ipv4/netfilter/ip_tables.c#L499">499</a>                                                          <i>"rule %u\n"</i>,
<a name="L500" href="source/net/ipv4/netfilter/ip_tables.c#L500">500</a>                                                          hook, <a href="ident?i=pos">pos</a>);
<a name="L501" href="source/net/ipv4/netfilter/ip_tables.c#L501">501</a>                                         }
<a name="L502" href="source/net/ipv4/netfilter/ip_tables.c#L502">502</a> #endif
<a name="L503" href="source/net/ipv4/netfilter/ip_tables.c#L503">503</a>                                         oldpos = <a href="ident?i=pos">pos</a>;
<a name="L504" href="source/net/ipv4/netfilter/ip_tables.c#L504">504</a>                                         <a href="ident?i=pos">pos</a> = <a href="ident?i=e">e</a>-&gt;counters.pcnt;
<a name="L505" href="source/net/ipv4/netfilter/ip_tables.c#L505">505</a>                                         <a href="ident?i=e">e</a>-&gt;counters.pcnt = 0;
<a name="L506" href="source/net/ipv4/netfilter/ip_tables.c#L506">506</a> 
<a name="L507" href="source/net/ipv4/netfilter/ip_tables.c#L507">507</a>                                         <b><i>/* We're at the start. */</i></b>
<a name="L508" href="source/net/ipv4/netfilter/ip_tables.c#L508">508</a>                                         if (<a href="ident?i=pos">pos</a> == oldpos)
<a name="L509" href="source/net/ipv4/netfilter/ip_tables.c#L509">509</a>                                                 goto <a href="ident?i=next">next</a>;
<a name="L510" href="source/net/ipv4/netfilter/ip_tables.c#L510">510</a> 
<a name="L511" href="source/net/ipv4/netfilter/ip_tables.c#L511">511</a>                                         <a href="ident?i=e">e</a> = (struct <a href="ident?i=ipt_entry">ipt_entry</a> *)
<a name="L512" href="source/net/ipv4/netfilter/ip_tables.c#L512">512</a>                                                 (entry0 + <a href="ident?i=pos">pos</a>);
<a name="L513" href="source/net/ipv4/netfilter/ip_tables.c#L513">513</a>                                 } while (oldpos == <a href="ident?i=pos">pos</a> + <a href="ident?i=e">e</a>-&gt;next_offset);
<a name="L514" href="source/net/ipv4/netfilter/ip_tables.c#L514">514</a> 
<a name="L515" href="source/net/ipv4/netfilter/ip_tables.c#L515">515</a>                                 <b><i>/* Move along one */</i></b>
<a name="L516" href="source/net/ipv4/netfilter/ip_tables.c#L516">516</a>                                 <a href="ident?i=size">size</a> = <a href="ident?i=e">e</a>-&gt;next_offset;
<a name="L517" href="source/net/ipv4/netfilter/ip_tables.c#L517">517</a>                                 <a href="ident?i=e">e</a> = (struct <a href="ident?i=ipt_entry">ipt_entry</a> *)
<a name="L518" href="source/net/ipv4/netfilter/ip_tables.c#L518">518</a>                                         (entry0 + <a href="ident?i=pos">pos</a> + <a href="ident?i=size">size</a>);
<a name="L519" href="source/net/ipv4/netfilter/ip_tables.c#L519">519</a>                                 <a href="ident?i=e">e</a>-&gt;counters.pcnt = <a href="ident?i=pos">pos</a>;
<a name="L520" href="source/net/ipv4/netfilter/ip_tables.c#L520">520</a>                                 <a href="ident?i=pos">pos</a> += <a href="ident?i=size">size</a>;
<a name="L521" href="source/net/ipv4/netfilter/ip_tables.c#L521">521</a>                         } else {
<a name="L522" href="source/net/ipv4/netfilter/ip_tables.c#L522">522</a>                                 int newpos = <a href="ident?i=t">t</a>-&gt;verdict;
<a name="L523" href="source/net/ipv4/netfilter/ip_tables.c#L523">523</a> 
<a name="L524" href="source/net/ipv4/netfilter/ip_tables.c#L524">524</a>                                 if (<a href="ident?i=strcmp">strcmp</a>(<a href="ident?i=t">t</a>-&gt;<a href="ident?i=target">target</a>.u.<a href="ident?i=user">user</a>.<a href="ident?i=name">name</a>,
<a name="L525" href="source/net/ipv4/netfilter/ip_tables.c#L525">525</a>                                            <a href="ident?i=XT_STANDARD_TARGET">XT_STANDARD_TARGET</a>) == 0 &amp;&amp;
<a name="L526" href="source/net/ipv4/netfilter/ip_tables.c#L526">526</a>                                     newpos &gt;= 0) {
<a name="L527" href="source/net/ipv4/netfilter/ip_tables.c#L527">527</a>                                         if (newpos &gt; newinfo-&gt;<a href="ident?i=size">size</a> -
<a name="L528" href="source/net/ipv4/netfilter/ip_tables.c#L528">528</a>                                                 sizeof(struct <a href="ident?i=ipt_entry">ipt_entry</a>)) {
<a name="L529" href="source/net/ipv4/netfilter/ip_tables.c#L529">529</a>                                                 <a href="ident?i=duprintf">duprintf</a>(<i>"mark_source_chains: "</i>
<a name="L530" href="source/net/ipv4/netfilter/ip_tables.c#L530">530</a>                                                         <i>"bad verdict (%i)\n"</i>,
<a name="L531" href="source/net/ipv4/netfilter/ip_tables.c#L531">531</a>                                                                 newpos);
<a name="L532" href="source/net/ipv4/netfilter/ip_tables.c#L532">532</a>                                                 return 0;
<a name="L533" href="source/net/ipv4/netfilter/ip_tables.c#L533">533</a>                                         }
<a name="L534" href="source/net/ipv4/netfilter/ip_tables.c#L534">534</a>                                         <b><i>/* This a jump; chase it. */</i></b>
<a name="L535" href="source/net/ipv4/netfilter/ip_tables.c#L535">535</a>                                         <a href="ident?i=duprintf">duprintf</a>(<i>"Jump rule %u -&gt; %u\n"</i>,
<a name="L536" href="source/net/ipv4/netfilter/ip_tables.c#L536">536</a>                                                  <a href="ident?i=pos">pos</a>, newpos);
<a name="L537" href="source/net/ipv4/netfilter/ip_tables.c#L537">537</a>                                 } else {
<a name="L538" href="source/net/ipv4/netfilter/ip_tables.c#L538">538</a>                                         <b><i>/* ... this is a fallthru */</i></b>
<a name="L539" href="source/net/ipv4/netfilter/ip_tables.c#L539">539</a>                                         newpos = <a href="ident?i=pos">pos</a> + <a href="ident?i=e">e</a>-&gt;next_offset;
<a name="L540" href="source/net/ipv4/netfilter/ip_tables.c#L540">540</a>                                 }
<a name="L541" href="source/net/ipv4/netfilter/ip_tables.c#L541">541</a>                                 <a href="ident?i=e">e</a> = (struct <a href="ident?i=ipt_entry">ipt_entry</a> *)
<a name="L542" href="source/net/ipv4/netfilter/ip_tables.c#L542">542</a>                                         (entry0 + newpos);
<a name="L543" href="source/net/ipv4/netfilter/ip_tables.c#L543">543</a>                                 <a href="ident?i=e">e</a>-&gt;counters.pcnt = <a href="ident?i=pos">pos</a>;
<a name="L544" href="source/net/ipv4/netfilter/ip_tables.c#L544">544</a>                                 <a href="ident?i=pos">pos</a> = newpos;
<a name="L545" href="source/net/ipv4/netfilter/ip_tables.c#L545">545</a>                         }
<a name="L546" href="source/net/ipv4/netfilter/ip_tables.c#L546">546</a>                 }
<a name="L547" href="source/net/ipv4/netfilter/ip_tables.c#L547">547</a>                 <a href="ident?i=next">next</a>:
<a name="L548" href="source/net/ipv4/netfilter/ip_tables.c#L548">548</a>                 <a href="ident?i=duprintf">duprintf</a>(<i>"Finished chain %u\n"</i>, hook);
<a name="L549" href="source/net/ipv4/netfilter/ip_tables.c#L549">549</a>         }
<a name="L550" href="source/net/ipv4/netfilter/ip_tables.c#L550">550</a>         return 1;
<a name="L551" href="source/net/ipv4/netfilter/ip_tables.c#L551">551</a> }
<a name="L552" href="source/net/ipv4/netfilter/ip_tables.c#L552">552</a> 
<a name="L553" href="source/net/ipv4/netfilter/ip_tables.c#L553">553</a> static void <a href="ident?i=cleanup_match">cleanup_match</a>(struct <a href="ident?i=xt_entry_match">xt_entry_match</a> *<a href="ident?i=m">m</a>, struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>)
<a name="L554" href="source/net/ipv4/netfilter/ip_tables.c#L554">554</a> {
<a name="L555" href="source/net/ipv4/netfilter/ip_tables.c#L555">555</a>         struct <a href="ident?i=xt_mtdtor_param">xt_mtdtor_param</a> <a href="ident?i=par">par</a>;
<a name="L556" href="source/net/ipv4/netfilter/ip_tables.c#L556">556</a> 
<a name="L557" href="source/net/ipv4/netfilter/ip_tables.c#L557">557</a>         <a href="ident?i=par">par</a>.<a href="ident?i=net">net</a>       = <a href="ident?i=net">net</a>;
<a name="L558" href="source/net/ipv4/netfilter/ip_tables.c#L558">558</a>         <a href="ident?i=par">par</a>.<a href="ident?i=match">match</a>     = <a href="ident?i=m">m</a>-&gt;u.kernel.<a href="ident?i=match">match</a>;
<a name="L559" href="source/net/ipv4/netfilter/ip_tables.c#L559">559</a>         <a href="ident?i=par">par</a>.matchinfo = <a href="ident?i=m">m</a>-&gt;<a href="ident?i=data">data</a>;
<a name="L560" href="source/net/ipv4/netfilter/ip_tables.c#L560">560</a>         <a href="ident?i=par">par</a>.<a href="ident?i=family">family</a>    = NFPROTO_IPV4;
<a name="L561" href="source/net/ipv4/netfilter/ip_tables.c#L561">561</a>         if (<a href="ident?i=par">par</a>.<a href="ident?i=match">match</a>-&gt;<a href="ident?i=destroy">destroy</a> != <a href="ident?i=NULL">NULL</a>)
<a name="L562" href="source/net/ipv4/netfilter/ip_tables.c#L562">562</a>                 <a href="ident?i=par">par</a>.<a href="ident?i=match">match</a>-&gt;<a href="ident?i=destroy">destroy</a>(&amp;<a href="ident?i=par">par</a>);
<a name="L563" href="source/net/ipv4/netfilter/ip_tables.c#L563">563</a>         <a href="ident?i=module_put">module_put</a>(<a href="ident?i=par">par</a>.<a href="ident?i=match">match</a>-&gt;<a href="ident?i=me">me</a>);
<a name="L564" href="source/net/ipv4/netfilter/ip_tables.c#L564">564</a> }
<a name="L565" href="source/net/ipv4/netfilter/ip_tables.c#L565">565</a> 
<a name="L566" href="source/net/ipv4/netfilter/ip_tables.c#L566">566</a> static int
<a name="L567" href="source/net/ipv4/netfilter/ip_tables.c#L567">567</a> <a href="ident?i=check_entry">check_entry</a>(const struct <a href="ident?i=ipt_entry">ipt_entry</a> *<a href="ident?i=e">e</a>, const char *<a href="ident?i=name">name</a>)
<a name="L568" href="source/net/ipv4/netfilter/ip_tables.c#L568">568</a> {
<a name="L569" href="source/net/ipv4/netfilter/ip_tables.c#L569">569</a>         const struct <a href="ident?i=xt_entry_target">xt_entry_target</a> *<a href="ident?i=t">t</a>;
<a name="L570" href="source/net/ipv4/netfilter/ip_tables.c#L570">570</a> 
<a name="L571" href="source/net/ipv4/netfilter/ip_tables.c#L571">571</a>         if (!<a href="ident?i=ip_checkentry">ip_checkentry</a>(&amp;<a href="ident?i=e">e</a>-&gt;<a href="ident?i=ip">ip</a>)) {
<a name="L572" href="source/net/ipv4/netfilter/ip_tables.c#L572">572</a>                 <a href="ident?i=duprintf">duprintf</a>(<i>"ip check failed %p %s.\n"</i>, <a href="ident?i=e">e</a>, <a href="ident?i=name">name</a>);
<a name="L573" href="source/net/ipv4/netfilter/ip_tables.c#L573">573</a>                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L574" href="source/net/ipv4/netfilter/ip_tables.c#L574">574</a>         }
<a name="L575" href="source/net/ipv4/netfilter/ip_tables.c#L575">575</a> 
<a name="L576" href="source/net/ipv4/netfilter/ip_tables.c#L576">576</a>         if (<a href="ident?i=e">e</a>-&gt;target_offset + sizeof(struct <a href="ident?i=xt_entry_target">xt_entry_target</a>) &gt;
<a name="L577" href="source/net/ipv4/netfilter/ip_tables.c#L577">577</a>             <a href="ident?i=e">e</a>-&gt;next_offset)
<a name="L578" href="source/net/ipv4/netfilter/ip_tables.c#L578">578</a>                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L579" href="source/net/ipv4/netfilter/ip_tables.c#L579">579</a> 
<a name="L580" href="source/net/ipv4/netfilter/ip_tables.c#L580">580</a>         <a href="ident?i=t">t</a> = <a href="ident?i=ipt_get_target_c">ipt_get_target_c</a>(<a href="ident?i=e">e</a>);
<a name="L581" href="source/net/ipv4/netfilter/ip_tables.c#L581">581</a>         if (<a href="ident?i=e">e</a>-&gt;target_offset + <a href="ident?i=t">t</a>-&gt;u.target_size &gt; <a href="ident?i=e">e</a>-&gt;next_offset)
<a name="L582" href="source/net/ipv4/netfilter/ip_tables.c#L582">582</a>                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L583" href="source/net/ipv4/netfilter/ip_tables.c#L583">583</a> 
<a name="L584" href="source/net/ipv4/netfilter/ip_tables.c#L584">584</a>         return 0;
<a name="L585" href="source/net/ipv4/netfilter/ip_tables.c#L585">585</a> }
<a name="L586" href="source/net/ipv4/netfilter/ip_tables.c#L586">586</a> 
<a name="L587" href="source/net/ipv4/netfilter/ip_tables.c#L587">587</a> static int
<a name="L588" href="source/net/ipv4/netfilter/ip_tables.c#L588">588</a> <a href="ident?i=check_match">check_match</a>(struct <a href="ident?i=xt_entry_match">xt_entry_match</a> *<a href="ident?i=m">m</a>, struct <a href="ident?i=xt_mtchk_param">xt_mtchk_param</a> *<a href="ident?i=par">par</a>)
<a name="L589" href="source/net/ipv4/netfilter/ip_tables.c#L589">589</a> {
<a name="L590" href="source/net/ipv4/netfilter/ip_tables.c#L590">590</a>         const struct <a href="ident?i=ipt_ip">ipt_ip</a> *<a href="ident?i=ip">ip</a> = <a href="ident?i=par">par</a>-&gt;entryinfo;
<a name="L591" href="source/net/ipv4/netfilter/ip_tables.c#L591">591</a>         int <a href="ident?i=ret">ret</a>;
<a name="L592" href="source/net/ipv4/netfilter/ip_tables.c#L592">592</a> 
<a name="L593" href="source/net/ipv4/netfilter/ip_tables.c#L593">593</a>         <a href="ident?i=par">par</a>-&gt;<a href="ident?i=match">match</a>     = <a href="ident?i=m">m</a>-&gt;u.kernel.<a href="ident?i=match">match</a>;
<a name="L594" href="source/net/ipv4/netfilter/ip_tables.c#L594">594</a>         <a href="ident?i=par">par</a>-&gt;matchinfo = <a href="ident?i=m">m</a>-&gt;<a href="ident?i=data">data</a>;
<a name="L595" href="source/net/ipv4/netfilter/ip_tables.c#L595">595</a> 
<a name="L596" href="source/net/ipv4/netfilter/ip_tables.c#L596">596</a>         <a href="ident?i=ret">ret</a> = <a href="ident?i=xt_check_match">xt_check_match</a>(<a href="ident?i=par">par</a>, <a href="ident?i=m">m</a>-&gt;u.match_size - sizeof(*<a href="ident?i=m">m</a>),
<a name="L597" href="source/net/ipv4/netfilter/ip_tables.c#L597">597</a>               <a href="ident?i=ip">ip</a>-&gt;<a href="ident?i=proto">proto</a>, <a href="ident?i=ip">ip</a>-&gt;invflags &amp; <a href="ident?i=IPT_INV_PROTO">IPT_INV_PROTO</a>);
<a name="L598" href="source/net/ipv4/netfilter/ip_tables.c#L598">598</a>         if (<a href="ident?i=ret">ret</a> &lt; 0) {
<a name="L599" href="source/net/ipv4/netfilter/ip_tables.c#L599">599</a>                 <a href="ident?i=duprintf">duprintf</a>(<i>"check failed for `%s'.\n"</i>, <a href="ident?i=par">par</a>-&gt;<a href="ident?i=match">match</a>-&gt;<a href="ident?i=name">name</a>);
<a name="L600" href="source/net/ipv4/netfilter/ip_tables.c#L600">600</a>                 return <a href="ident?i=ret">ret</a>;
<a name="L601" href="source/net/ipv4/netfilter/ip_tables.c#L601">601</a>         }
<a name="L602" href="source/net/ipv4/netfilter/ip_tables.c#L602">602</a>         return 0;
<a name="L603" href="source/net/ipv4/netfilter/ip_tables.c#L603">603</a> }
<a name="L604" href="source/net/ipv4/netfilter/ip_tables.c#L604">604</a> 
<a name="L605" href="source/net/ipv4/netfilter/ip_tables.c#L605">605</a> static int
<a name="L606" href="source/net/ipv4/netfilter/ip_tables.c#L606">606</a> <a href="ident?i=find_check_match">find_check_match</a>(struct <a href="ident?i=xt_entry_match">xt_entry_match</a> *<a href="ident?i=m">m</a>, struct <a href="ident?i=xt_mtchk_param">xt_mtchk_param</a> *<a href="ident?i=par">par</a>)
<a name="L607" href="source/net/ipv4/netfilter/ip_tables.c#L607">607</a> {
<a name="L608" href="source/net/ipv4/netfilter/ip_tables.c#L608">608</a>         struct <a href="ident?i=xt_match">xt_match</a> *<a href="ident?i=match">match</a>;
<a name="L609" href="source/net/ipv4/netfilter/ip_tables.c#L609">609</a>         int <a href="ident?i=ret">ret</a>;
<a name="L610" href="source/net/ipv4/netfilter/ip_tables.c#L610">610</a> 
<a name="L611" href="source/net/ipv4/netfilter/ip_tables.c#L611">611</a>         <a href="ident?i=match">match</a> = <a href="ident?i=xt_request_find_match">xt_request_find_match</a>(NFPROTO_IPV4, <a href="ident?i=m">m</a>-&gt;u.<a href="ident?i=user">user</a>.<a href="ident?i=name">name</a>,
<a name="L612" href="source/net/ipv4/netfilter/ip_tables.c#L612">612</a>                                       <a href="ident?i=m">m</a>-&gt;u.<a href="ident?i=user">user</a>.<a href="ident?i=revision">revision</a>);
<a name="L613" href="source/net/ipv4/netfilter/ip_tables.c#L613">613</a>         if (<a href="ident?i=IS_ERR">IS_ERR</a>(<a href="ident?i=match">match</a>)) {
<a name="L614" href="source/net/ipv4/netfilter/ip_tables.c#L614">614</a>                 <a href="ident?i=duprintf">duprintf</a>(<i>"find_check_match: `%s' not found\n"</i>, <a href="ident?i=m">m</a>-&gt;u.<a href="ident?i=user">user</a>.<a href="ident?i=name">name</a>);
<a name="L615" href="source/net/ipv4/netfilter/ip_tables.c#L615">615</a>                 return <a href="ident?i=PTR_ERR">PTR_ERR</a>(<a href="ident?i=match">match</a>);
<a name="L616" href="source/net/ipv4/netfilter/ip_tables.c#L616">616</a>         }
<a name="L617" href="source/net/ipv4/netfilter/ip_tables.c#L617">617</a>         <a href="ident?i=m">m</a>-&gt;u.kernel.<a href="ident?i=match">match</a> = <a href="ident?i=match">match</a>;
<a name="L618" href="source/net/ipv4/netfilter/ip_tables.c#L618">618</a> 
<a name="L619" href="source/net/ipv4/netfilter/ip_tables.c#L619">619</a>         <a href="ident?i=ret">ret</a> = <a href="ident?i=check_match">check_match</a>(<a href="ident?i=m">m</a>, <a href="ident?i=par">par</a>);
<a name="L620" href="source/net/ipv4/netfilter/ip_tables.c#L620">620</a>         if (<a href="ident?i=ret">ret</a>)
<a name="L621" href="source/net/ipv4/netfilter/ip_tables.c#L621">621</a>                 goto <a href="ident?i=err">err</a>;
<a name="L622" href="source/net/ipv4/netfilter/ip_tables.c#L622">622</a> 
<a name="L623" href="source/net/ipv4/netfilter/ip_tables.c#L623">623</a>         return 0;
<a name="L624" href="source/net/ipv4/netfilter/ip_tables.c#L624">624</a> <a href="ident?i=err">err</a>:
<a name="L625" href="source/net/ipv4/netfilter/ip_tables.c#L625">625</a>         <a href="ident?i=module_put">module_put</a>(<a href="ident?i=m">m</a>-&gt;u.kernel.<a href="ident?i=match">match</a>-&gt;<a href="ident?i=me">me</a>);
<a name="L626" href="source/net/ipv4/netfilter/ip_tables.c#L626">626</a>         return <a href="ident?i=ret">ret</a>;
<a name="L627" href="source/net/ipv4/netfilter/ip_tables.c#L627">627</a> }
<a name="L628" href="source/net/ipv4/netfilter/ip_tables.c#L628">628</a> 
<a name="L629" href="source/net/ipv4/netfilter/ip_tables.c#L629">629</a> static int <a href="ident?i=check_target">check_target</a>(struct <a href="ident?i=ipt_entry">ipt_entry</a> *<a href="ident?i=e">e</a>, struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>, const char *<a href="ident?i=name">name</a>)
<a name="L630" href="source/net/ipv4/netfilter/ip_tables.c#L630">630</a> {
<a name="L631" href="source/net/ipv4/netfilter/ip_tables.c#L631">631</a>         struct <a href="ident?i=xt_entry_target">xt_entry_target</a> *<a href="ident?i=t">t</a> = <a href="ident?i=ipt_get_target">ipt_get_target</a>(<a href="ident?i=e">e</a>);
<a name="L632" href="source/net/ipv4/netfilter/ip_tables.c#L632">632</a>         struct <a href="ident?i=xt_tgchk_param">xt_tgchk_param</a> <a href="ident?i=par">par</a> = {
<a name="L633" href="source/net/ipv4/netfilter/ip_tables.c#L633">633</a>                 .<a href="ident?i=net">net</a>       = <a href="ident?i=net">net</a>,
<a name="L634" href="source/net/ipv4/netfilter/ip_tables.c#L634">634</a>                 .<a href="ident?i=table">table</a>     = <a href="ident?i=name">name</a>,
<a name="L635" href="source/net/ipv4/netfilter/ip_tables.c#L635">635</a>                 .entryinfo = <a href="ident?i=e">e</a>,
<a name="L636" href="source/net/ipv4/netfilter/ip_tables.c#L636">636</a>                 .<a href="ident?i=target">target</a>    = <a href="ident?i=t">t</a>-&gt;u.kernel.<a href="ident?i=target">target</a>,
<a name="L637" href="source/net/ipv4/netfilter/ip_tables.c#L637">637</a>                 .targinfo  = <a href="ident?i=t">t</a>-&gt;<a href="ident?i=data">data</a>,
<a name="L638" href="source/net/ipv4/netfilter/ip_tables.c#L638">638</a>                 .hook_mask = <a href="ident?i=e">e</a>-&gt;comefrom,
<a name="L639" href="source/net/ipv4/netfilter/ip_tables.c#L639">639</a>                 .<a href="ident?i=family">family</a>    = NFPROTO_IPV4,
<a name="L640" href="source/net/ipv4/netfilter/ip_tables.c#L640">640</a>         };
<a name="L641" href="source/net/ipv4/netfilter/ip_tables.c#L641">641</a>         int <a href="ident?i=ret">ret</a>;
<a name="L642" href="source/net/ipv4/netfilter/ip_tables.c#L642">642</a> 
<a name="L643" href="source/net/ipv4/netfilter/ip_tables.c#L643">643</a>         <a href="ident?i=ret">ret</a> = <a href="ident?i=xt_check_target">xt_check_target</a>(&amp;<a href="ident?i=par">par</a>, <a href="ident?i=t">t</a>-&gt;u.target_size - sizeof(*<a href="ident?i=t">t</a>),
<a name="L644" href="source/net/ipv4/netfilter/ip_tables.c#L644">644</a>               <a href="ident?i=e">e</a>-&gt;<a href="ident?i=ip">ip</a>.<a href="ident?i=proto">proto</a>, <a href="ident?i=e">e</a>-&gt;<a href="ident?i=ip">ip</a>.invflags &amp; <a href="ident?i=IPT_INV_PROTO">IPT_INV_PROTO</a>);
<a name="L645" href="source/net/ipv4/netfilter/ip_tables.c#L645">645</a>         if (<a href="ident?i=ret">ret</a> &lt; 0) {
<a name="L646" href="source/net/ipv4/netfilter/ip_tables.c#L646">646</a>                 <a href="ident?i=duprintf">duprintf</a>(<i>"check failed for `%s'.\n"</i>,
<a name="L647" href="source/net/ipv4/netfilter/ip_tables.c#L647">647</a>                          <a href="ident?i=t">t</a>-&gt;u.kernel.<a href="ident?i=target">target</a>-&gt;<a href="ident?i=name">name</a>);
<a name="L648" href="source/net/ipv4/netfilter/ip_tables.c#L648">648</a>                 return <a href="ident?i=ret">ret</a>;
<a name="L649" href="source/net/ipv4/netfilter/ip_tables.c#L649">649</a>         }
<a name="L650" href="source/net/ipv4/netfilter/ip_tables.c#L650">650</a>         return 0;
<a name="L651" href="source/net/ipv4/netfilter/ip_tables.c#L651">651</a> }
<a name="L652" href="source/net/ipv4/netfilter/ip_tables.c#L652">652</a> 
<a name="L653" href="source/net/ipv4/netfilter/ip_tables.c#L653">653</a> static int
<a name="L654" href="source/net/ipv4/netfilter/ip_tables.c#L654">654</a> <a href="ident?i=find_check_entry">find_check_entry</a>(struct <a href="ident?i=ipt_entry">ipt_entry</a> *<a href="ident?i=e">e</a>, struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>, const char *<a href="ident?i=name">name</a>,
<a name="L655" href="source/net/ipv4/netfilter/ip_tables.c#L655">655</a>                  unsigned int <a href="ident?i=size">size</a>)
<a name="L656" href="source/net/ipv4/netfilter/ip_tables.c#L656">656</a> {
<a name="L657" href="source/net/ipv4/netfilter/ip_tables.c#L657">657</a>         struct <a href="ident?i=xt_entry_target">xt_entry_target</a> *<a href="ident?i=t">t</a>;
<a name="L658" href="source/net/ipv4/netfilter/ip_tables.c#L658">658</a>         struct <a href="ident?i=xt_target">xt_target</a> *<a href="ident?i=target">target</a>;
<a name="L659" href="source/net/ipv4/netfilter/ip_tables.c#L659">659</a>         int <a href="ident?i=ret">ret</a>;
<a name="L660" href="source/net/ipv4/netfilter/ip_tables.c#L660">660</a>         unsigned int j;
<a name="L661" href="source/net/ipv4/netfilter/ip_tables.c#L661">661</a>         struct <a href="ident?i=xt_mtchk_param">xt_mtchk_param</a> mtpar;
<a name="L662" href="source/net/ipv4/netfilter/ip_tables.c#L662">662</a>         struct <a href="ident?i=xt_entry_match">xt_entry_match</a> *ematch;
<a name="L663" href="source/net/ipv4/netfilter/ip_tables.c#L663">663</a> 
<a name="L664" href="source/net/ipv4/netfilter/ip_tables.c#L664">664</a>         <a href="ident?i=ret">ret</a> = <a href="ident?i=check_entry">check_entry</a>(<a href="ident?i=e">e</a>, <a href="ident?i=name">name</a>);
<a name="L665" href="source/net/ipv4/netfilter/ip_tables.c#L665">665</a>         if (<a href="ident?i=ret">ret</a>)
<a name="L666" href="source/net/ipv4/netfilter/ip_tables.c#L666">666</a>                 return <a href="ident?i=ret">ret</a>;
<a name="L667" href="source/net/ipv4/netfilter/ip_tables.c#L667">667</a> 
<a name="L668" href="source/net/ipv4/netfilter/ip_tables.c#L668">668</a>         j = 0;
<a name="L669" href="source/net/ipv4/netfilter/ip_tables.c#L669">669</a>         mtpar.<a href="ident?i=net">net</a>       = <a href="ident?i=net">net</a>;
<a name="L670" href="source/net/ipv4/netfilter/ip_tables.c#L670">670</a>         mtpar.<a href="ident?i=table">table</a>     = <a href="ident?i=name">name</a>;
<a name="L671" href="source/net/ipv4/netfilter/ip_tables.c#L671">671</a>         mtpar.entryinfo = &amp;<a href="ident?i=e">e</a>-&gt;<a href="ident?i=ip">ip</a>;
<a name="L672" href="source/net/ipv4/netfilter/ip_tables.c#L672">672</a>         mtpar.hook_mask = <a href="ident?i=e">e</a>-&gt;comefrom;
<a name="L673" href="source/net/ipv4/netfilter/ip_tables.c#L673">673</a>         mtpar.<a href="ident?i=family">family</a>    = NFPROTO_IPV4;
<a name="L674" href="source/net/ipv4/netfilter/ip_tables.c#L674">674</a>         <a href="ident?i=xt_ematch_foreach">xt_ematch_foreach</a>(ematch, <a href="ident?i=e">e</a>) {
<a name="L675" href="source/net/ipv4/netfilter/ip_tables.c#L675">675</a>                 <a href="ident?i=ret">ret</a> = <a href="ident?i=find_check_match">find_check_match</a>(ematch, &amp;mtpar);
<a name="L676" href="source/net/ipv4/netfilter/ip_tables.c#L676">676</a>                 if (<a href="ident?i=ret">ret</a> != 0)
<a name="L677" href="source/net/ipv4/netfilter/ip_tables.c#L677">677</a>                         goto cleanup_matches;
<a name="L678" href="source/net/ipv4/netfilter/ip_tables.c#L678">678</a>                 ++j;
<a name="L679" href="source/net/ipv4/netfilter/ip_tables.c#L679">679</a>         }
<a name="L680" href="source/net/ipv4/netfilter/ip_tables.c#L680">680</a> 
<a name="L681" href="source/net/ipv4/netfilter/ip_tables.c#L681">681</a>         <a href="ident?i=t">t</a> = <a href="ident?i=ipt_get_target">ipt_get_target</a>(<a href="ident?i=e">e</a>);
<a name="L682" href="source/net/ipv4/netfilter/ip_tables.c#L682">682</a>         <a href="ident?i=target">target</a> = <a href="ident?i=xt_request_find_target">xt_request_find_target</a>(NFPROTO_IPV4, <a href="ident?i=t">t</a>-&gt;u.<a href="ident?i=user">user</a>.<a href="ident?i=name">name</a>,
<a name="L683" href="source/net/ipv4/netfilter/ip_tables.c#L683">683</a>                                         <a href="ident?i=t">t</a>-&gt;u.<a href="ident?i=user">user</a>.<a href="ident?i=revision">revision</a>);
<a name="L684" href="source/net/ipv4/netfilter/ip_tables.c#L684">684</a>         if (<a href="ident?i=IS_ERR">IS_ERR</a>(<a href="ident?i=target">target</a>)) {
<a name="L685" href="source/net/ipv4/netfilter/ip_tables.c#L685">685</a>                 <a href="ident?i=duprintf">duprintf</a>(<i>"find_check_entry: `%s' not found\n"</i>, <a href="ident?i=t">t</a>-&gt;u.<a href="ident?i=user">user</a>.<a href="ident?i=name">name</a>);
<a name="L686" href="source/net/ipv4/netfilter/ip_tables.c#L686">686</a>                 <a href="ident?i=ret">ret</a> = <a href="ident?i=PTR_ERR">PTR_ERR</a>(<a href="ident?i=target">target</a>);
<a name="L687" href="source/net/ipv4/netfilter/ip_tables.c#L687">687</a>                 goto cleanup_matches;
<a name="L688" href="source/net/ipv4/netfilter/ip_tables.c#L688">688</a>         }
<a name="L689" href="source/net/ipv4/netfilter/ip_tables.c#L689">689</a>         <a href="ident?i=t">t</a>-&gt;u.kernel.<a href="ident?i=target">target</a> = <a href="ident?i=target">target</a>;
<a name="L690" href="source/net/ipv4/netfilter/ip_tables.c#L690">690</a> 
<a name="L691" href="source/net/ipv4/netfilter/ip_tables.c#L691">691</a>         <a href="ident?i=ret">ret</a> = <a href="ident?i=check_target">check_target</a>(<a href="ident?i=e">e</a>, <a href="ident?i=net">net</a>, <a href="ident?i=name">name</a>);
<a name="L692" href="source/net/ipv4/netfilter/ip_tables.c#L692">692</a>         if (<a href="ident?i=ret">ret</a>)
<a name="L693" href="source/net/ipv4/netfilter/ip_tables.c#L693">693</a>                 goto <a href="ident?i=err">err</a>;
<a name="L694" href="source/net/ipv4/netfilter/ip_tables.c#L694">694</a>         return 0;
<a name="L695" href="source/net/ipv4/netfilter/ip_tables.c#L695">695</a>  <a href="ident?i=err">err</a>:
<a name="L696" href="source/net/ipv4/netfilter/ip_tables.c#L696">696</a>         <a href="ident?i=module_put">module_put</a>(<a href="ident?i=t">t</a>-&gt;u.kernel.<a href="ident?i=target">target</a>-&gt;<a href="ident?i=me">me</a>);
<a name="L697" href="source/net/ipv4/netfilter/ip_tables.c#L697">697</a>  cleanup_matches:
<a name="L698" href="source/net/ipv4/netfilter/ip_tables.c#L698">698</a>         <a href="ident?i=xt_ematch_foreach">xt_ematch_foreach</a>(ematch, <a href="ident?i=e">e</a>) {
<a name="L699" href="source/net/ipv4/netfilter/ip_tables.c#L699">699</a>                 if (j-- == 0)
<a name="L700" href="source/net/ipv4/netfilter/ip_tables.c#L700">700</a>                         break;
<a name="L701" href="source/net/ipv4/netfilter/ip_tables.c#L701">701</a>                 <a href="ident?i=cleanup_match">cleanup_match</a>(ematch, <a href="ident?i=net">net</a>);
<a name="L702" href="source/net/ipv4/netfilter/ip_tables.c#L702">702</a>         }
<a name="L703" href="source/net/ipv4/netfilter/ip_tables.c#L703">703</a>         return <a href="ident?i=ret">ret</a>;
<a name="L704" href="source/net/ipv4/netfilter/ip_tables.c#L704">704</a> }
<a name="L705" href="source/net/ipv4/netfilter/ip_tables.c#L705">705</a> 
<a name="L706" href="source/net/ipv4/netfilter/ip_tables.c#L706">706</a> static <a href="ident?i=bool">bool</a> <a href="ident?i=check_underflow">check_underflow</a>(const struct <a href="ident?i=ipt_entry">ipt_entry</a> *<a href="ident?i=e">e</a>)
<a name="L707" href="source/net/ipv4/netfilter/ip_tables.c#L707">707</a> {
<a name="L708" href="source/net/ipv4/netfilter/ip_tables.c#L708">708</a>         const struct <a href="ident?i=xt_entry_target">xt_entry_target</a> *<a href="ident?i=t">t</a>;
<a name="L709" href="source/net/ipv4/netfilter/ip_tables.c#L709">709</a>         unsigned int verdict;
<a name="L710" href="source/net/ipv4/netfilter/ip_tables.c#L710">710</a> 
<a name="L711" href="source/net/ipv4/netfilter/ip_tables.c#L711">711</a>         if (!<a href="ident?i=unconditional">unconditional</a>(&amp;<a href="ident?i=e">e</a>-&gt;<a href="ident?i=ip">ip</a>))
<a name="L712" href="source/net/ipv4/netfilter/ip_tables.c#L712">712</a>                 return <a href="ident?i=false">false</a>;
<a name="L713" href="source/net/ipv4/netfilter/ip_tables.c#L713">713</a>         <a href="ident?i=t">t</a> = <a href="ident?i=ipt_get_target_c">ipt_get_target_c</a>(<a href="ident?i=e">e</a>);
<a name="L714" href="source/net/ipv4/netfilter/ip_tables.c#L714">714</a>         if (<a href="ident?i=strcmp">strcmp</a>(<a href="ident?i=t">t</a>-&gt;u.<a href="ident?i=user">user</a>.<a href="ident?i=name">name</a>, <a href="ident?i=XT_STANDARD_TARGET">XT_STANDARD_TARGET</a>) != 0)
<a name="L715" href="source/net/ipv4/netfilter/ip_tables.c#L715">715</a>                 return <a href="ident?i=false">false</a>;
<a name="L716" href="source/net/ipv4/netfilter/ip_tables.c#L716">716</a>         verdict = ((struct <a href="ident?i=xt_standard_target">xt_standard_target</a> *)<a href="ident?i=t">t</a>)-&gt;verdict;
<a name="L717" href="source/net/ipv4/netfilter/ip_tables.c#L717">717</a>         verdict = -verdict - 1;
<a name="L718" href="source/net/ipv4/netfilter/ip_tables.c#L718">718</a>         return verdict == <a href="ident?i=NF_DROP">NF_DROP</a> || verdict == <a href="ident?i=NF_ACCEPT">NF_ACCEPT</a>;
<a name="L719" href="source/net/ipv4/netfilter/ip_tables.c#L719">719</a> }
<a name="L720" href="source/net/ipv4/netfilter/ip_tables.c#L720">720</a> 
<a name="L721" href="source/net/ipv4/netfilter/ip_tables.c#L721">721</a> static int
<a name="L722" href="source/net/ipv4/netfilter/ip_tables.c#L722">722</a> <a href="ident?i=check_entry_size_and_hooks">check_entry_size_and_hooks</a>(struct <a href="ident?i=ipt_entry">ipt_entry</a> *<a href="ident?i=e">e</a>,
<a name="L723" href="source/net/ipv4/netfilter/ip_tables.c#L723">723</a>                            struct <a href="ident?i=xt_table_info">xt_table_info</a> *newinfo,
<a name="L724" href="source/net/ipv4/netfilter/ip_tables.c#L724">724</a>                            const unsigned char *<a href="ident?i=base">base</a>,
<a name="L725" href="source/net/ipv4/netfilter/ip_tables.c#L725">725</a>                            const unsigned char *<a href="ident?i=limit">limit</a>,
<a name="L726" href="source/net/ipv4/netfilter/ip_tables.c#L726">726</a>                            const unsigned int *hook_entries,
<a name="L727" href="source/net/ipv4/netfilter/ip_tables.c#L727">727</a>                            const unsigned int *underflows,
<a name="L728" href="source/net/ipv4/netfilter/ip_tables.c#L728">728</a>                            unsigned int valid_hooks)
<a name="L729" href="source/net/ipv4/netfilter/ip_tables.c#L729">729</a> {
<a name="L730" href="source/net/ipv4/netfilter/ip_tables.c#L730">730</a>         unsigned int <a href="ident?i=h">h</a>;
<a name="L731" href="source/net/ipv4/netfilter/ip_tables.c#L731">731</a> 
<a name="L732" href="source/net/ipv4/netfilter/ip_tables.c#L732">732</a>         if ((unsigned long)<a href="ident?i=e">e</a> % __alignof__(struct <a href="ident?i=ipt_entry">ipt_entry</a>) != 0 ||
<a name="L733" href="source/net/ipv4/netfilter/ip_tables.c#L733">733</a>             (unsigned char *)<a href="ident?i=e">e</a> + sizeof(struct <a href="ident?i=ipt_entry">ipt_entry</a>) &gt;= <a href="ident?i=limit">limit</a>) {
<a name="L734" href="source/net/ipv4/netfilter/ip_tables.c#L734">734</a>                 <a href="ident?i=duprintf">duprintf</a>(<i>"Bad offset %p\n"</i>, <a href="ident?i=e">e</a>);
<a name="L735" href="source/net/ipv4/netfilter/ip_tables.c#L735">735</a>                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L736" href="source/net/ipv4/netfilter/ip_tables.c#L736">736</a>         }
<a name="L737" href="source/net/ipv4/netfilter/ip_tables.c#L737">737</a> 
<a name="L738" href="source/net/ipv4/netfilter/ip_tables.c#L738">738</a>         if (<a href="ident?i=e">e</a>-&gt;next_offset
<a name="L739" href="source/net/ipv4/netfilter/ip_tables.c#L739">739</a>             &lt; sizeof(struct <a href="ident?i=ipt_entry">ipt_entry</a>) + sizeof(struct <a href="ident?i=xt_entry_target">xt_entry_target</a>)) {
<a name="L740" href="source/net/ipv4/netfilter/ip_tables.c#L740">740</a>                 <a href="ident?i=duprintf">duprintf</a>(<i>"checking: element %p size %u\n"</i>,
<a name="L741" href="source/net/ipv4/netfilter/ip_tables.c#L741">741</a>                          <a href="ident?i=e">e</a>, <a href="ident?i=e">e</a>-&gt;next_offset);
<a name="L742" href="source/net/ipv4/netfilter/ip_tables.c#L742">742</a>                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L743" href="source/net/ipv4/netfilter/ip_tables.c#L743">743</a>         }
<a name="L744" href="source/net/ipv4/netfilter/ip_tables.c#L744">744</a> 
<a name="L745" href="source/net/ipv4/netfilter/ip_tables.c#L745">745</a>         <b><i>/* Check hooks &amp; underflows */</i></b>
<a name="L746" href="source/net/ipv4/netfilter/ip_tables.c#L746">746</a>         for (<a href="ident?i=h">h</a> = 0; <a href="ident?i=h">h</a> &lt; NF_INET_NUMHOOKS; <a href="ident?i=h">h</a>++) {
<a name="L747" href="source/net/ipv4/netfilter/ip_tables.c#L747">747</a>                 if (!(valid_hooks &amp; (1 &lt;&lt; <a href="ident?i=h">h</a>)))
<a name="L748" href="source/net/ipv4/netfilter/ip_tables.c#L748">748</a>                         continue;
<a name="L749" href="source/net/ipv4/netfilter/ip_tables.c#L749">749</a>                 if ((unsigned char *)<a href="ident?i=e">e</a> - <a href="ident?i=base">base</a> == hook_entries[<a href="ident?i=h">h</a>])
<a name="L750" href="source/net/ipv4/netfilter/ip_tables.c#L750">750</a>                         newinfo-&gt;hook_entry[<a href="ident?i=h">h</a>] = hook_entries[<a href="ident?i=h">h</a>];
<a name="L751" href="source/net/ipv4/netfilter/ip_tables.c#L751">751</a>                 if ((unsigned char *)<a href="ident?i=e">e</a> - <a href="ident?i=base">base</a> == underflows[<a href="ident?i=h">h</a>]) {
<a name="L752" href="source/net/ipv4/netfilter/ip_tables.c#L752">752</a>                         if (!<a href="ident?i=check_underflow">check_underflow</a>(<a href="ident?i=e">e</a>)) {
<a name="L753" href="source/net/ipv4/netfilter/ip_tables.c#L753">753</a>                                 <a href="ident?i=pr_err">pr_err</a>(<i>"Underflows must be unconditional and "</i>
<a name="L754" href="source/net/ipv4/netfilter/ip_tables.c#L754">754</a>                                        <i>"use the STANDARD target with "</i>
<a name="L755" href="source/net/ipv4/netfilter/ip_tables.c#L755">755</a>                                        <i>"ACCEPT/DROP\n"</i>);
<a name="L756" href="source/net/ipv4/netfilter/ip_tables.c#L756">756</a>                                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L757" href="source/net/ipv4/netfilter/ip_tables.c#L757">757</a>                         }
<a name="L758" href="source/net/ipv4/netfilter/ip_tables.c#L758">758</a>                         newinfo-&gt;underflow[<a href="ident?i=h">h</a>] = underflows[<a href="ident?i=h">h</a>];
<a name="L759" href="source/net/ipv4/netfilter/ip_tables.c#L759">759</a>                 }
<a name="L760" href="source/net/ipv4/netfilter/ip_tables.c#L760">760</a>         }
<a name="L761" href="source/net/ipv4/netfilter/ip_tables.c#L761">761</a> 
<a name="L762" href="source/net/ipv4/netfilter/ip_tables.c#L762">762</a>         <b><i>/* Clear counters and comefrom */</i></b>
<a name="L763" href="source/net/ipv4/netfilter/ip_tables.c#L763">763</a>         <a href="ident?i=e">e</a>-&gt;counters = ((struct <a href="ident?i=xt_counters">xt_counters</a>) { 0, 0 });
<a name="L764" href="source/net/ipv4/netfilter/ip_tables.c#L764">764</a>         <a href="ident?i=e">e</a>-&gt;comefrom = 0;
<a name="L765" href="source/net/ipv4/netfilter/ip_tables.c#L765">765</a>         return 0;
<a name="L766" href="source/net/ipv4/netfilter/ip_tables.c#L766">766</a> }
<a name="L767" href="source/net/ipv4/netfilter/ip_tables.c#L767">767</a> 
<a name="L768" href="source/net/ipv4/netfilter/ip_tables.c#L768">768</a> static void
<a name="L769" href="source/net/ipv4/netfilter/ip_tables.c#L769">769</a> <a href="ident?i=cleanup_entry">cleanup_entry</a>(struct <a href="ident?i=ipt_entry">ipt_entry</a> *<a href="ident?i=e">e</a>, struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>)
<a name="L770" href="source/net/ipv4/netfilter/ip_tables.c#L770">770</a> {
<a name="L771" href="source/net/ipv4/netfilter/ip_tables.c#L771">771</a>         struct <a href="ident?i=xt_tgdtor_param">xt_tgdtor_param</a> <a href="ident?i=par">par</a>;
<a name="L772" href="source/net/ipv4/netfilter/ip_tables.c#L772">772</a>         struct <a href="ident?i=xt_entry_target">xt_entry_target</a> *<a href="ident?i=t">t</a>;
<a name="L773" href="source/net/ipv4/netfilter/ip_tables.c#L773">773</a>         struct <a href="ident?i=xt_entry_match">xt_entry_match</a> *ematch;
<a name="L774" href="source/net/ipv4/netfilter/ip_tables.c#L774">774</a> 
<a name="L775" href="source/net/ipv4/netfilter/ip_tables.c#L775">775</a>         <b><i>/* Cleanup all matches */</i></b>
<a name="L776" href="source/net/ipv4/netfilter/ip_tables.c#L776">776</a>         <a href="ident?i=xt_ematch_foreach">xt_ematch_foreach</a>(ematch, <a href="ident?i=e">e</a>)
<a name="L777" href="source/net/ipv4/netfilter/ip_tables.c#L777">777</a>                 <a href="ident?i=cleanup_match">cleanup_match</a>(ematch, <a href="ident?i=net">net</a>);
<a name="L778" href="source/net/ipv4/netfilter/ip_tables.c#L778">778</a>         <a href="ident?i=t">t</a> = <a href="ident?i=ipt_get_target">ipt_get_target</a>(<a href="ident?i=e">e</a>);
<a name="L779" href="source/net/ipv4/netfilter/ip_tables.c#L779">779</a> 
<a name="L780" href="source/net/ipv4/netfilter/ip_tables.c#L780">780</a>         <a href="ident?i=par">par</a>.<a href="ident?i=net">net</a>      = <a href="ident?i=net">net</a>;
<a name="L781" href="source/net/ipv4/netfilter/ip_tables.c#L781">781</a>         <a href="ident?i=par">par</a>.<a href="ident?i=target">target</a>   = <a href="ident?i=t">t</a>-&gt;u.kernel.<a href="ident?i=target">target</a>;
<a name="L782" href="source/net/ipv4/netfilter/ip_tables.c#L782">782</a>         <a href="ident?i=par">par</a>.targinfo = <a href="ident?i=t">t</a>-&gt;<a href="ident?i=data">data</a>;
<a name="L783" href="source/net/ipv4/netfilter/ip_tables.c#L783">783</a>         <a href="ident?i=par">par</a>.<a href="ident?i=family">family</a>   = NFPROTO_IPV4;
<a name="L784" href="source/net/ipv4/netfilter/ip_tables.c#L784">784</a>         if (<a href="ident?i=par">par</a>.<a href="ident?i=target">target</a>-&gt;<a href="ident?i=destroy">destroy</a> != <a href="ident?i=NULL">NULL</a>)
<a name="L785" href="source/net/ipv4/netfilter/ip_tables.c#L785">785</a>                 <a href="ident?i=par">par</a>.<a href="ident?i=target">target</a>-&gt;<a href="ident?i=destroy">destroy</a>(&amp;<a href="ident?i=par">par</a>);
<a name="L786" href="source/net/ipv4/netfilter/ip_tables.c#L786">786</a>         <a href="ident?i=module_put">module_put</a>(<a href="ident?i=par">par</a>.<a href="ident?i=target">target</a>-&gt;<a href="ident?i=me">me</a>);
<a name="L787" href="source/net/ipv4/netfilter/ip_tables.c#L787">787</a> }
<a name="L788" href="source/net/ipv4/netfilter/ip_tables.c#L788">788</a> 
<a name="L789" href="source/net/ipv4/netfilter/ip_tables.c#L789">789</a> <b><i>/* Checks and translates the user-supplied table segment (held in</i></b>
<a name="L790" href="source/net/ipv4/netfilter/ip_tables.c#L790">790</a> <b><i>   newinfo) */</i></b>
<a name="L791" href="source/net/ipv4/netfilter/ip_tables.c#L791">791</a> static int
<a name="L792" href="source/net/ipv4/netfilter/ip_tables.c#L792">792</a> <a href="ident?i=translate_table">translate_table</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>, struct <a href="ident?i=xt_table_info">xt_table_info</a> *newinfo, void *entry0,
<a name="L793" href="source/net/ipv4/netfilter/ip_tables.c#L793">793</a>                 const struct <a href="ident?i=ipt_replace">ipt_replace</a> *repl)
<a name="L794" href="source/net/ipv4/netfilter/ip_tables.c#L794">794</a> {
<a name="L795" href="source/net/ipv4/netfilter/ip_tables.c#L795">795</a>         struct <a href="ident?i=ipt_entry">ipt_entry</a> *iter;
<a name="L796" href="source/net/ipv4/netfilter/ip_tables.c#L796">796</a>         unsigned int <a href="ident?i=i">i</a>;
<a name="L797" href="source/net/ipv4/netfilter/ip_tables.c#L797">797</a>         int <a href="ident?i=ret">ret</a> = 0;
<a name="L798" href="source/net/ipv4/netfilter/ip_tables.c#L798">798</a> 
<a name="L799" href="source/net/ipv4/netfilter/ip_tables.c#L799">799</a>         newinfo-&gt;<a href="ident?i=size">size</a> = repl-&gt;<a href="ident?i=size">size</a>;
<a name="L800" href="source/net/ipv4/netfilter/ip_tables.c#L800">800</a>         newinfo-&gt;<a href="ident?i=number">number</a> = repl-&gt;<a href="ident?i=num_entries">num_entries</a>;
<a name="L801" href="source/net/ipv4/netfilter/ip_tables.c#L801">801</a> 
<a name="L802" href="source/net/ipv4/netfilter/ip_tables.c#L802">802</a>         <b><i>/* Init all hooks to impossible value. */</i></b>
<a name="L803" href="source/net/ipv4/netfilter/ip_tables.c#L803">803</a>         for (<a href="ident?i=i">i</a> = 0; <a href="ident?i=i">i</a> &lt; NF_INET_NUMHOOKS; <a href="ident?i=i">i</a>++) {
<a name="L804" href="source/net/ipv4/netfilter/ip_tables.c#L804">804</a>                 newinfo-&gt;hook_entry[<a href="ident?i=i">i</a>] = 0xFFFFFFFF;
<a name="L805" href="source/net/ipv4/netfilter/ip_tables.c#L805">805</a>                 newinfo-&gt;underflow[<a href="ident?i=i">i</a>] = 0xFFFFFFFF;
<a name="L806" href="source/net/ipv4/netfilter/ip_tables.c#L806">806</a>         }
<a name="L807" href="source/net/ipv4/netfilter/ip_tables.c#L807">807</a> 
<a name="L808" href="source/net/ipv4/netfilter/ip_tables.c#L808">808</a>         <a href="ident?i=duprintf">duprintf</a>(<i>"translate_table: size %u\n"</i>, newinfo-&gt;<a href="ident?i=size">size</a>);
<a name="L809" href="source/net/ipv4/netfilter/ip_tables.c#L809">809</a>         <a href="ident?i=i">i</a> = 0;
<a name="L810" href="source/net/ipv4/netfilter/ip_tables.c#L810">810</a>         <b><i>/* Walk through entries, checking offsets. */</i></b>
<a name="L811" href="source/net/ipv4/netfilter/ip_tables.c#L811">811</a>         <a href="ident?i=xt_entry_foreach">xt_entry_foreach</a>(iter, entry0, newinfo-&gt;<a href="ident?i=size">size</a>) {
<a name="L812" href="source/net/ipv4/netfilter/ip_tables.c#L812">812</a>                 <a href="ident?i=ret">ret</a> = <a href="ident?i=check_entry_size_and_hooks">check_entry_size_and_hooks</a>(iter, newinfo, entry0,
<a name="L813" href="source/net/ipv4/netfilter/ip_tables.c#L813">813</a>                                                  entry0 + repl-&gt;<a href="ident?i=size">size</a>,
<a name="L814" href="source/net/ipv4/netfilter/ip_tables.c#L814">814</a>                                                  repl-&gt;hook_entry,
<a name="L815" href="source/net/ipv4/netfilter/ip_tables.c#L815">815</a>                                                  repl-&gt;underflow,
<a name="L816" href="source/net/ipv4/netfilter/ip_tables.c#L816">816</a>                                                  repl-&gt;valid_hooks);
<a name="L817" href="source/net/ipv4/netfilter/ip_tables.c#L817">817</a>                 if (<a href="ident?i=ret">ret</a> != 0)
<a name="L818" href="source/net/ipv4/netfilter/ip_tables.c#L818">818</a>                         return <a href="ident?i=ret">ret</a>;
<a name="L819" href="source/net/ipv4/netfilter/ip_tables.c#L819">819</a>                 ++<a href="ident?i=i">i</a>;
<a name="L820" href="source/net/ipv4/netfilter/ip_tables.c#L820">820</a>                 if (<a href="ident?i=strcmp">strcmp</a>(<a href="ident?i=ipt_get_target">ipt_get_target</a>(iter)-&gt;u.<a href="ident?i=user">user</a>.<a href="ident?i=name">name</a>,
<a name="L821" href="source/net/ipv4/netfilter/ip_tables.c#L821">821</a>                     <a href="ident?i=XT_ERROR_TARGET">XT_ERROR_TARGET</a>) == 0)
<a name="L822" href="source/net/ipv4/netfilter/ip_tables.c#L822">822</a>                         ++newinfo-&gt;stacksize;
<a name="L823" href="source/net/ipv4/netfilter/ip_tables.c#L823">823</a>         }
<a name="L824" href="source/net/ipv4/netfilter/ip_tables.c#L824">824</a> 
<a name="L825" href="source/net/ipv4/netfilter/ip_tables.c#L825">825</a>         if (<a href="ident?i=i">i</a> != repl-&gt;<a href="ident?i=num_entries">num_entries</a>) {
<a name="L826" href="source/net/ipv4/netfilter/ip_tables.c#L826">826</a>                 <a href="ident?i=duprintf">duprintf</a>(<i>"translate_table: %u not %u entries\n"</i>,
<a name="L827" href="source/net/ipv4/netfilter/ip_tables.c#L827">827</a>                          <a href="ident?i=i">i</a>, repl-&gt;<a href="ident?i=num_entries">num_entries</a>);
<a name="L828" href="source/net/ipv4/netfilter/ip_tables.c#L828">828</a>                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L829" href="source/net/ipv4/netfilter/ip_tables.c#L829">829</a>         }
<a name="L830" href="source/net/ipv4/netfilter/ip_tables.c#L830">830</a> 
<a name="L831" href="source/net/ipv4/netfilter/ip_tables.c#L831">831</a>         <b><i>/* Check hooks all assigned */</i></b>
<a name="L832" href="source/net/ipv4/netfilter/ip_tables.c#L832">832</a>         for (<a href="ident?i=i">i</a> = 0; <a href="ident?i=i">i</a> &lt; NF_INET_NUMHOOKS; <a href="ident?i=i">i</a>++) {
<a name="L833" href="source/net/ipv4/netfilter/ip_tables.c#L833">833</a>                 <b><i>/* Only hooks which are valid */</i></b>
<a name="L834" href="source/net/ipv4/netfilter/ip_tables.c#L834">834</a>                 if (!(repl-&gt;valid_hooks &amp; (1 &lt;&lt; <a href="ident?i=i">i</a>)))
<a name="L835" href="source/net/ipv4/netfilter/ip_tables.c#L835">835</a>                         continue;
<a name="L836" href="source/net/ipv4/netfilter/ip_tables.c#L836">836</a>                 if (newinfo-&gt;hook_entry[<a href="ident?i=i">i</a>] == 0xFFFFFFFF) {
<a name="L837" href="source/net/ipv4/netfilter/ip_tables.c#L837">837</a>                         <a href="ident?i=duprintf">duprintf</a>(<i>"Invalid hook entry %u %u\n"</i>,
<a name="L838" href="source/net/ipv4/netfilter/ip_tables.c#L838">838</a>                                  <a href="ident?i=i">i</a>, repl-&gt;hook_entry[<a href="ident?i=i">i</a>]);
<a name="L839" href="source/net/ipv4/netfilter/ip_tables.c#L839">839</a>                         return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L840" href="source/net/ipv4/netfilter/ip_tables.c#L840">840</a>                 }
<a name="L841" href="source/net/ipv4/netfilter/ip_tables.c#L841">841</a>                 if (newinfo-&gt;underflow[<a href="ident?i=i">i</a>] == 0xFFFFFFFF) {
<a name="L842" href="source/net/ipv4/netfilter/ip_tables.c#L842">842</a>                         <a href="ident?i=duprintf">duprintf</a>(<i>"Invalid underflow %u %u\n"</i>,
<a name="L843" href="source/net/ipv4/netfilter/ip_tables.c#L843">843</a>                                  <a href="ident?i=i">i</a>, repl-&gt;underflow[<a href="ident?i=i">i</a>]);
<a name="L844" href="source/net/ipv4/netfilter/ip_tables.c#L844">844</a>                         return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L845" href="source/net/ipv4/netfilter/ip_tables.c#L845">845</a>                 }
<a name="L846" href="source/net/ipv4/netfilter/ip_tables.c#L846">846</a>         }
<a name="L847" href="source/net/ipv4/netfilter/ip_tables.c#L847">847</a> 
<a name="L848" href="source/net/ipv4/netfilter/ip_tables.c#L848">848</a>         if (!<a href="ident?i=mark_source_chains">mark_source_chains</a>(newinfo, repl-&gt;valid_hooks, entry0))
<a name="L849" href="source/net/ipv4/netfilter/ip_tables.c#L849">849</a>                 return -<a href="ident?i=ELOOP">ELOOP</a>;
<a name="L850" href="source/net/ipv4/netfilter/ip_tables.c#L850">850</a> 
<a name="L851" href="source/net/ipv4/netfilter/ip_tables.c#L851">851</a>         <b><i>/* Finally, each sanity check must pass */</i></b>
<a name="L852" href="source/net/ipv4/netfilter/ip_tables.c#L852">852</a>         <a href="ident?i=i">i</a> = 0;
<a name="L853" href="source/net/ipv4/netfilter/ip_tables.c#L853">853</a>         <a href="ident?i=xt_entry_foreach">xt_entry_foreach</a>(iter, entry0, newinfo-&gt;<a href="ident?i=size">size</a>) {
<a name="L854" href="source/net/ipv4/netfilter/ip_tables.c#L854">854</a>                 <a href="ident?i=ret">ret</a> = <a href="ident?i=find_check_entry">find_check_entry</a>(iter, <a href="ident?i=net">net</a>, repl-&gt;<a href="ident?i=name">name</a>, repl-&gt;<a href="ident?i=size">size</a>);
<a name="L855" href="source/net/ipv4/netfilter/ip_tables.c#L855">855</a>                 if (<a href="ident?i=ret">ret</a> != 0)
<a name="L856" href="source/net/ipv4/netfilter/ip_tables.c#L856">856</a>                         break;
<a name="L857" href="source/net/ipv4/netfilter/ip_tables.c#L857">857</a>                 ++<a href="ident?i=i">i</a>;
<a name="L858" href="source/net/ipv4/netfilter/ip_tables.c#L858">858</a>         }
<a name="L859" href="source/net/ipv4/netfilter/ip_tables.c#L859">859</a> 
<a name="L860" href="source/net/ipv4/netfilter/ip_tables.c#L860">860</a>         if (<a href="ident?i=ret">ret</a> != 0) {
<a name="L861" href="source/net/ipv4/netfilter/ip_tables.c#L861">861</a>                 <a href="ident?i=xt_entry_foreach">xt_entry_foreach</a>(iter, entry0, newinfo-&gt;<a href="ident?i=size">size</a>) {
<a name="L862" href="source/net/ipv4/netfilter/ip_tables.c#L862">862</a>                         if (<a href="ident?i=i">i</a>-- == 0)
<a name="L863" href="source/net/ipv4/netfilter/ip_tables.c#L863">863</a>                                 break;
<a name="L864" href="source/net/ipv4/netfilter/ip_tables.c#L864">864</a>                         <a href="ident?i=cleanup_entry">cleanup_entry</a>(iter, <a href="ident?i=net">net</a>);
<a name="L865" href="source/net/ipv4/netfilter/ip_tables.c#L865">865</a>                 }
<a name="L866" href="source/net/ipv4/netfilter/ip_tables.c#L866">866</a>                 return <a href="ident?i=ret">ret</a>;
<a name="L867" href="source/net/ipv4/netfilter/ip_tables.c#L867">867</a>         }
<a name="L868" href="source/net/ipv4/netfilter/ip_tables.c#L868">868</a> 
<a name="L869" href="source/net/ipv4/netfilter/ip_tables.c#L869">869</a>         <b><i>/* And one copy for every other CPU */</i></b>
<a name="L870" href="source/net/ipv4/netfilter/ip_tables.c#L870">870</a>         <a href="ident?i=for_each_possible_cpu">for_each_possible_cpu</a>(<a href="ident?i=i">i</a>) {
<a name="L871" href="source/net/ipv4/netfilter/ip_tables.c#L871">871</a>                 if (newinfo-&gt;<a href="ident?i=entries">entries</a>[<a href="ident?i=i">i</a>] &amp;&amp; newinfo-&gt;<a href="ident?i=entries">entries</a>[<a href="ident?i=i">i</a>] != entry0)
<a name="L872" href="source/net/ipv4/netfilter/ip_tables.c#L872">872</a>                         <a href="ident?i=memcpy">memcpy</a>(newinfo-&gt;<a href="ident?i=entries">entries</a>[<a href="ident?i=i">i</a>], entry0, newinfo-&gt;<a href="ident?i=size">size</a>);
<a name="L873" href="source/net/ipv4/netfilter/ip_tables.c#L873">873</a>         }
<a name="L874" href="source/net/ipv4/netfilter/ip_tables.c#L874">874</a> 
<a name="L875" href="source/net/ipv4/netfilter/ip_tables.c#L875">875</a>         return <a href="ident?i=ret">ret</a>;
<a name="L876" href="source/net/ipv4/netfilter/ip_tables.c#L876">876</a> }
<a name="L877" href="source/net/ipv4/netfilter/ip_tables.c#L877">877</a> 
<a name="L878" href="source/net/ipv4/netfilter/ip_tables.c#L878">878</a> static void
<a name="L879" href="source/net/ipv4/netfilter/ip_tables.c#L879">879</a> <a href="ident?i=get_counters">get_counters</a>(const struct <a href="ident?i=xt_table_info">xt_table_info</a> *<a href="ident?i=t">t</a>,
<a name="L880" href="source/net/ipv4/netfilter/ip_tables.c#L880">880</a>              struct <a href="ident?i=xt_counters">xt_counters</a> counters[])
<a name="L881" href="source/net/ipv4/netfilter/ip_tables.c#L881">881</a> {
<a name="L882" href="source/net/ipv4/netfilter/ip_tables.c#L882">882</a>         struct <a href="ident?i=ipt_entry">ipt_entry</a> *iter;
<a name="L883" href="source/net/ipv4/netfilter/ip_tables.c#L883">883</a>         unsigned int <a href="ident?i=cpu">cpu</a>;
<a name="L884" href="source/net/ipv4/netfilter/ip_tables.c#L884">884</a>         unsigned int <a href="ident?i=i">i</a>;
<a name="L885" href="source/net/ipv4/netfilter/ip_tables.c#L885">885</a> 
<a name="L886" href="source/net/ipv4/netfilter/ip_tables.c#L886">886</a>         <a href="ident?i=for_each_possible_cpu">for_each_possible_cpu</a>(<a href="ident?i=cpu">cpu</a>) {
<a name="L887" href="source/net/ipv4/netfilter/ip_tables.c#L887">887</a>                 <a href="ident?i=seqcount_t">seqcount_t</a> *<a href="ident?i=s">s</a> = &amp;<a href="ident?i=per_cpu">per_cpu</a>(xt_recseq, <a href="ident?i=cpu">cpu</a>);
<a name="L888" href="source/net/ipv4/netfilter/ip_tables.c#L888">888</a> 
<a name="L889" href="source/net/ipv4/netfilter/ip_tables.c#L889">889</a>                 <a href="ident?i=i">i</a> = 0;
<a name="L890" href="source/net/ipv4/netfilter/ip_tables.c#L890">890</a>                 <a href="ident?i=xt_entry_foreach">xt_entry_foreach</a>(iter, <a href="ident?i=t">t</a>-&gt;<a href="ident?i=entries">entries</a>[<a href="ident?i=cpu">cpu</a>], <a href="ident?i=t">t</a>-&gt;<a href="ident?i=size">size</a>) {
<a name="L891" href="source/net/ipv4/netfilter/ip_tables.c#L891">891</a>                         <a href="ident?i=u64">u64</a> bcnt, pcnt;
<a name="L892" href="source/net/ipv4/netfilter/ip_tables.c#L892">892</a>                         unsigned int <a href="ident?i=start">start</a>;
<a name="L893" href="source/net/ipv4/netfilter/ip_tables.c#L893">893</a> 
<a name="L894" href="source/net/ipv4/netfilter/ip_tables.c#L894">894</a>                         do {
<a name="L895" href="source/net/ipv4/netfilter/ip_tables.c#L895">895</a>                                 <a href="ident?i=start">start</a> = <a href="ident?i=read_seqcount_begin">read_seqcount_begin</a>(<a href="ident?i=s">s</a>);
<a name="L896" href="source/net/ipv4/netfilter/ip_tables.c#L896">896</a>                                 bcnt = iter-&gt;counters.bcnt;
<a name="L897" href="source/net/ipv4/netfilter/ip_tables.c#L897">897</a>                                 pcnt = iter-&gt;counters.pcnt;
<a name="L898" href="source/net/ipv4/netfilter/ip_tables.c#L898">898</a>                         } while (<a href="ident?i=read_seqcount_retry">read_seqcount_retry</a>(<a href="ident?i=s">s</a>, <a href="ident?i=start">start</a>));
<a name="L899" href="source/net/ipv4/netfilter/ip_tables.c#L899">899</a> 
<a name="L900" href="source/net/ipv4/netfilter/ip_tables.c#L900">900</a>                         <a href="ident?i=ADD_COUNTER">ADD_COUNTER</a>(counters[<a href="ident?i=i">i</a>], bcnt, pcnt);
<a name="L901" href="source/net/ipv4/netfilter/ip_tables.c#L901">901</a>                         ++<a href="ident?i=i">i</a>; <b><i>/* macro does multi eval of i */</i></b>
<a name="L902" href="source/net/ipv4/netfilter/ip_tables.c#L902">902</a>                 }
<a name="L903" href="source/net/ipv4/netfilter/ip_tables.c#L903">903</a>         }
<a name="L904" href="source/net/ipv4/netfilter/ip_tables.c#L904">904</a> }
<a name="L905" href="source/net/ipv4/netfilter/ip_tables.c#L905">905</a> 
<a name="L906" href="source/net/ipv4/netfilter/ip_tables.c#L906">906</a> static struct <a href="ident?i=xt_counters">xt_counters</a> *<a href="ident?i=alloc_counters">alloc_counters</a>(const struct <a href="ident?i=xt_table">xt_table</a> *<a href="ident?i=table">table</a>)
<a name="L907" href="source/net/ipv4/netfilter/ip_tables.c#L907">907</a> {
<a name="L908" href="source/net/ipv4/netfilter/ip_tables.c#L908">908</a>         unsigned int countersize;
<a name="L909" href="source/net/ipv4/netfilter/ip_tables.c#L909">909</a>         struct <a href="ident?i=xt_counters">xt_counters</a> *counters;
<a name="L910" href="source/net/ipv4/netfilter/ip_tables.c#L910">910</a>         const struct <a href="ident?i=xt_table_info">xt_table_info</a> *<a href="ident?i=private">private</a> = <a href="ident?i=table">table</a>-&gt;<a href="ident?i=private">private</a>;
<a name="L911" href="source/net/ipv4/netfilter/ip_tables.c#L911">911</a> 
<a name="L912" href="source/net/ipv4/netfilter/ip_tables.c#L912">912</a>         <b><i>/* We need atomic snapshot of counters: rest doesn't change</i></b>
<a name="L913" href="source/net/ipv4/netfilter/ip_tables.c#L913">913</a> <b><i>           (other than comefrom, which userspace doesn't care</i></b>
<a name="L914" href="source/net/ipv4/netfilter/ip_tables.c#L914">914</a> <b><i>           about). */</i></b>
<a name="L915" href="source/net/ipv4/netfilter/ip_tables.c#L915">915</a>         countersize = sizeof(struct <a href="ident?i=xt_counters">xt_counters</a>) * <a href="ident?i=private">private</a>-&gt;<a href="ident?i=number">number</a>;
<a name="L916" href="source/net/ipv4/netfilter/ip_tables.c#L916">916</a>         counters = <a href="ident?i=vzalloc">vzalloc</a>(countersize);
<a name="L917" href="source/net/ipv4/netfilter/ip_tables.c#L917">917</a> 
<a name="L918" href="source/net/ipv4/netfilter/ip_tables.c#L918">918</a>         if (counters == <a href="ident?i=NULL">NULL</a>)
<a name="L919" href="source/net/ipv4/netfilter/ip_tables.c#L919">919</a>                 return <a href="ident?i=ERR_PTR">ERR_PTR</a>(-<a href="ident?i=ENOMEM">ENOMEM</a>);
<a name="L920" href="source/net/ipv4/netfilter/ip_tables.c#L920">920</a> 
<a name="L921" href="source/net/ipv4/netfilter/ip_tables.c#L921">921</a>         <a href="ident?i=get_counters">get_counters</a>(<a href="ident?i=private">private</a>, counters);
<a name="L922" href="source/net/ipv4/netfilter/ip_tables.c#L922">922</a> 
<a name="L923" href="source/net/ipv4/netfilter/ip_tables.c#L923">923</a>         return counters;
<a name="L924" href="source/net/ipv4/netfilter/ip_tables.c#L924">924</a> }
<a name="L925" href="source/net/ipv4/netfilter/ip_tables.c#L925">925</a> 
<a name="L926" href="source/net/ipv4/netfilter/ip_tables.c#L926">926</a> static int
<a name="L927" href="source/net/ipv4/netfilter/ip_tables.c#L927">927</a> <a href="ident?i=copy_entries_to_user">copy_entries_to_user</a>(unsigned int <a href="ident?i=total_size">total_size</a>,
<a name="L928" href="source/net/ipv4/netfilter/ip_tables.c#L928">928</a>                      const struct <a href="ident?i=xt_table">xt_table</a> *<a href="ident?i=table">table</a>,
<a name="L929" href="source/net/ipv4/netfilter/ip_tables.c#L929">929</a>                      void <a href="ident?i=__user">__user</a> *userptr)
<a name="L930" href="source/net/ipv4/netfilter/ip_tables.c#L930">930</a> {
<a name="L931" href="source/net/ipv4/netfilter/ip_tables.c#L931">931</a>         unsigned int <a href="ident?i=off">off</a>, <a href="ident?i=num">num</a>;
<a name="L932" href="source/net/ipv4/netfilter/ip_tables.c#L932">932</a>         const struct <a href="ident?i=ipt_entry">ipt_entry</a> *<a href="ident?i=e">e</a>;
<a name="L933" href="source/net/ipv4/netfilter/ip_tables.c#L933">933</a>         struct <a href="ident?i=xt_counters">xt_counters</a> *counters;
<a name="L934" href="source/net/ipv4/netfilter/ip_tables.c#L934">934</a>         const struct <a href="ident?i=xt_table_info">xt_table_info</a> *<a href="ident?i=private">private</a> = <a href="ident?i=table">table</a>-&gt;<a href="ident?i=private">private</a>;
<a name="L935" href="source/net/ipv4/netfilter/ip_tables.c#L935">935</a>         int <a href="ident?i=ret">ret</a> = 0;
<a name="L936" href="source/net/ipv4/netfilter/ip_tables.c#L936">936</a>         const void *loc_cpu_entry;
<a name="L937" href="source/net/ipv4/netfilter/ip_tables.c#L937">937</a> 
<a name="L938" href="source/net/ipv4/netfilter/ip_tables.c#L938">938</a>         counters = <a href="ident?i=alloc_counters">alloc_counters</a>(<a href="ident?i=table">table</a>);
<a name="L939" href="source/net/ipv4/netfilter/ip_tables.c#L939">939</a>         if (<a href="ident?i=IS_ERR">IS_ERR</a>(counters))
<a name="L940" href="source/net/ipv4/netfilter/ip_tables.c#L940">940</a>                 return <a href="ident?i=PTR_ERR">PTR_ERR</a>(counters);
<a name="L941" href="source/net/ipv4/netfilter/ip_tables.c#L941">941</a> 
<a name="L942" href="source/net/ipv4/netfilter/ip_tables.c#L942">942</a>         <b><i>/* choose the copy that is on our node/cpu, ...</i></b>
<a name="L943" href="source/net/ipv4/netfilter/ip_tables.c#L943">943</a> <b><i>         * This choice is lazy (because current thread is</i></b>
<a name="L944" href="source/net/ipv4/netfilter/ip_tables.c#L944">944</a> <b><i>         * allowed to migrate to another cpu)</i></b>
<a name="L945" href="source/net/ipv4/netfilter/ip_tables.c#L945">945</a> <b><i>         */</i></b>
<a name="L946" href="source/net/ipv4/netfilter/ip_tables.c#L946">946</a>         loc_cpu_entry = <a href="ident?i=private">private</a>-&gt;<a href="ident?i=entries">entries</a>[<a href="ident?i=raw_smp_processor_id">raw_smp_processor_id</a>()];
<a name="L947" href="source/net/ipv4/netfilter/ip_tables.c#L947">947</a>         if (<a href="ident?i=copy_to_user">copy_to_user</a>(userptr, loc_cpu_entry, <a href="ident?i=total_size">total_size</a>) != 0) {
<a name="L948" href="source/net/ipv4/netfilter/ip_tables.c#L948">948</a>                 <a href="ident?i=ret">ret</a> = -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L949" href="source/net/ipv4/netfilter/ip_tables.c#L949">949</a>                 goto free_counters;
<a name="L950" href="source/net/ipv4/netfilter/ip_tables.c#L950">950</a>         }
<a name="L951" href="source/net/ipv4/netfilter/ip_tables.c#L951">951</a> 
<a name="L952" href="source/net/ipv4/netfilter/ip_tables.c#L952">952</a>         <b><i>/* FIXME: use iterator macros --RR */</i></b>
<a name="L953" href="source/net/ipv4/netfilter/ip_tables.c#L953">953</a>         <b><i>/* ... then go back and fix counters and names */</i></b>
<a name="L954" href="source/net/ipv4/netfilter/ip_tables.c#L954">954</a>         for (<a href="ident?i=off">off</a> = 0, <a href="ident?i=num">num</a> = 0; <a href="ident?i=off">off</a> &lt; <a href="ident?i=total_size">total_size</a>; <a href="ident?i=off">off</a> += <a href="ident?i=e">e</a>-&gt;next_offset, <a href="ident?i=num">num</a>++){
<a name="L955" href="source/net/ipv4/netfilter/ip_tables.c#L955">955</a>                 unsigned int <a href="ident?i=i">i</a>;
<a name="L956" href="source/net/ipv4/netfilter/ip_tables.c#L956">956</a>                 const struct <a href="ident?i=xt_entry_match">xt_entry_match</a> *<a href="ident?i=m">m</a>;
<a name="L957" href="source/net/ipv4/netfilter/ip_tables.c#L957">957</a>                 const struct <a href="ident?i=xt_entry_target">xt_entry_target</a> *<a href="ident?i=t">t</a>;
<a name="L958" href="source/net/ipv4/netfilter/ip_tables.c#L958">958</a> 
<a name="L959" href="source/net/ipv4/netfilter/ip_tables.c#L959">959</a>                 <a href="ident?i=e">e</a> = (struct <a href="ident?i=ipt_entry">ipt_entry</a> *)(loc_cpu_entry + <a href="ident?i=off">off</a>);
<a name="L960" href="source/net/ipv4/netfilter/ip_tables.c#L960">960</a>                 if (<a href="ident?i=copy_to_user">copy_to_user</a>(userptr + <a href="ident?i=off">off</a>
<a name="L961" href="source/net/ipv4/netfilter/ip_tables.c#L961">961</a>                                  + <a href="ident?i=offsetof">offsetof</a>(struct <a href="ident?i=ipt_entry">ipt_entry</a>, counters),
<a name="L962" href="source/net/ipv4/netfilter/ip_tables.c#L962">962</a>                                  &amp;counters[<a href="ident?i=num">num</a>],
<a name="L963" href="source/net/ipv4/netfilter/ip_tables.c#L963">963</a>                                  sizeof(counters[<a href="ident?i=num">num</a>])) != 0) {
<a name="L964" href="source/net/ipv4/netfilter/ip_tables.c#L964">964</a>                         <a href="ident?i=ret">ret</a> = -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L965" href="source/net/ipv4/netfilter/ip_tables.c#L965">965</a>                         goto free_counters;
<a name="L966" href="source/net/ipv4/netfilter/ip_tables.c#L966">966</a>                 }
<a name="L967" href="source/net/ipv4/netfilter/ip_tables.c#L967">967</a> 
<a name="L968" href="source/net/ipv4/netfilter/ip_tables.c#L968">968</a>                 for (<a href="ident?i=i">i</a> = sizeof(struct <a href="ident?i=ipt_entry">ipt_entry</a>);
<a name="L969" href="source/net/ipv4/netfilter/ip_tables.c#L969">969</a>                      <a href="ident?i=i">i</a> &lt; <a href="ident?i=e">e</a>-&gt;target_offset;
<a name="L970" href="source/net/ipv4/netfilter/ip_tables.c#L970">970</a>                      <a href="ident?i=i">i</a> += <a href="ident?i=m">m</a>-&gt;u.match_size) {
<a name="L971" href="source/net/ipv4/netfilter/ip_tables.c#L971">971</a>                         <a href="ident?i=m">m</a> = (void *)<a href="ident?i=e">e</a> + <a href="ident?i=i">i</a>;
<a name="L972" href="source/net/ipv4/netfilter/ip_tables.c#L972">972</a> 
<a name="L973" href="source/net/ipv4/netfilter/ip_tables.c#L973">973</a>                         if (<a href="ident?i=copy_to_user">copy_to_user</a>(userptr + <a href="ident?i=off">off</a> + <a href="ident?i=i">i</a>
<a name="L974" href="source/net/ipv4/netfilter/ip_tables.c#L974">974</a>                                          + <a href="ident?i=offsetof">offsetof</a>(struct <a href="ident?i=xt_entry_match">xt_entry_match</a>,
<a name="L975" href="source/net/ipv4/netfilter/ip_tables.c#L975">975</a>                                                     u.<a href="ident?i=user">user</a>.<a href="ident?i=name">name</a>),
<a name="L976" href="source/net/ipv4/netfilter/ip_tables.c#L976">976</a>                                          <a href="ident?i=m">m</a>-&gt;u.kernel.<a href="ident?i=match">match</a>-&gt;<a href="ident?i=name">name</a>,
<a name="L977" href="source/net/ipv4/netfilter/ip_tables.c#L977">977</a>                                          <a href="ident?i=strlen">strlen</a>(<a href="ident?i=m">m</a>-&gt;u.kernel.<a href="ident?i=match">match</a>-&gt;<a href="ident?i=name">name</a>)+1)
<a name="L978" href="source/net/ipv4/netfilter/ip_tables.c#L978">978</a>                             != 0) {
<a name="L979" href="source/net/ipv4/netfilter/ip_tables.c#L979">979</a>                                 <a href="ident?i=ret">ret</a> = -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L980" href="source/net/ipv4/netfilter/ip_tables.c#L980">980</a>                                 goto free_counters;
<a name="L981" href="source/net/ipv4/netfilter/ip_tables.c#L981">981</a>                         }
<a name="L982" href="source/net/ipv4/netfilter/ip_tables.c#L982">982</a>                 }
<a name="L983" href="source/net/ipv4/netfilter/ip_tables.c#L983">983</a> 
<a name="L984" href="source/net/ipv4/netfilter/ip_tables.c#L984">984</a>                 <a href="ident?i=t">t</a> = <a href="ident?i=ipt_get_target_c">ipt_get_target_c</a>(<a href="ident?i=e">e</a>);
<a name="L985" href="source/net/ipv4/netfilter/ip_tables.c#L985">985</a>                 if (<a href="ident?i=copy_to_user">copy_to_user</a>(userptr + <a href="ident?i=off">off</a> + <a href="ident?i=e">e</a>-&gt;target_offset
<a name="L986" href="source/net/ipv4/netfilter/ip_tables.c#L986">986</a>                                  + <a href="ident?i=offsetof">offsetof</a>(struct <a href="ident?i=xt_entry_target">xt_entry_target</a>,
<a name="L987" href="source/net/ipv4/netfilter/ip_tables.c#L987">987</a>                                             u.<a href="ident?i=user">user</a>.<a href="ident?i=name">name</a>),
<a name="L988" href="source/net/ipv4/netfilter/ip_tables.c#L988">988</a>                                  <a href="ident?i=t">t</a>-&gt;u.kernel.<a href="ident?i=target">target</a>-&gt;<a href="ident?i=name">name</a>,
<a name="L989" href="source/net/ipv4/netfilter/ip_tables.c#L989">989</a>                                  <a href="ident?i=strlen">strlen</a>(<a href="ident?i=t">t</a>-&gt;u.kernel.<a href="ident?i=target">target</a>-&gt;<a href="ident?i=name">name</a>)+1) != 0) {
<a name="L990" href="source/net/ipv4/netfilter/ip_tables.c#L990">990</a>                         <a href="ident?i=ret">ret</a> = -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L991" href="source/net/ipv4/netfilter/ip_tables.c#L991">991</a>                         goto free_counters;
<a name="L992" href="source/net/ipv4/netfilter/ip_tables.c#L992">992</a>                 }
<a name="L993" href="source/net/ipv4/netfilter/ip_tables.c#L993">993</a>         }
<a name="L994" href="source/net/ipv4/netfilter/ip_tables.c#L994">994</a> 
<a name="L995" href="source/net/ipv4/netfilter/ip_tables.c#L995">995</a>  free_counters:
<a name="L996" href="source/net/ipv4/netfilter/ip_tables.c#L996">996</a>         <a href="ident?i=vfree">vfree</a>(counters);
<a name="L997" href="source/net/ipv4/netfilter/ip_tables.c#L997">997</a>         return <a href="ident?i=ret">ret</a>;
<a name="L998" href="source/net/ipv4/netfilter/ip_tables.c#L998">998</a> }
<a name="L999" href="source/net/ipv4/netfilter/ip_tables.c#L999">999</a> 
<a name="L1000" href="source/net/ipv4/netfilter/ip_tables.c#L1000">1000</a> #ifdef CONFIG_COMPAT
<a name="L1001" href="source/net/ipv4/netfilter/ip_tables.c#L1001">1001</a> static void <a href="ident?i=compat_standard_from_user">compat_standard_from_user</a>(void *<a href="ident?i=dst">dst</a>, const void *<a href="ident?i=src">src</a>)
<a name="L1002" href="source/net/ipv4/netfilter/ip_tables.c#L1002">1002</a> {
<a name="L1003" href="source/net/ipv4/netfilter/ip_tables.c#L1003">1003</a>         int <a href="ident?i=v">v</a> = *(<a href="ident?i=compat_int_t">compat_int_t</a> *)<a href="ident?i=src">src</a>;
<a name="L1004" href="source/net/ipv4/netfilter/ip_tables.c#L1004">1004</a> 
<a name="L1005" href="source/net/ipv4/netfilter/ip_tables.c#L1005">1005</a>         if (<a href="ident?i=v">v</a> &gt; 0)
<a name="L1006" href="source/net/ipv4/netfilter/ip_tables.c#L1006">1006</a>                 <a href="ident?i=v">v</a> += <a href="ident?i=xt_compat_calc_jump">xt_compat_calc_jump</a>(<a href="ident?i=AF_INET">AF_INET</a>, <a href="ident?i=v">v</a>);
<a name="L1007" href="source/net/ipv4/netfilter/ip_tables.c#L1007">1007</a>         <a href="ident?i=memcpy">memcpy</a>(<a href="ident?i=dst">dst</a>, &amp;<a href="ident?i=v">v</a>, sizeof(<a href="ident?i=v">v</a>));
<a name="L1008" href="source/net/ipv4/netfilter/ip_tables.c#L1008">1008</a> }
<a name="L1009" href="source/net/ipv4/netfilter/ip_tables.c#L1009">1009</a> 
<a name="L1010" href="source/net/ipv4/netfilter/ip_tables.c#L1010">1010</a> static int <a href="ident?i=compat_standard_to_user">compat_standard_to_user</a>(void <a href="ident?i=__user">__user</a> *<a href="ident?i=dst">dst</a>, const void *<a href="ident?i=src">src</a>)
<a name="L1011" href="source/net/ipv4/netfilter/ip_tables.c#L1011">1011</a> {
<a name="L1012" href="source/net/ipv4/netfilter/ip_tables.c#L1012">1012</a>         <a href="ident?i=compat_int_t">compat_int_t</a> cv = *(int *)<a href="ident?i=src">src</a>;
<a name="L1013" href="source/net/ipv4/netfilter/ip_tables.c#L1013">1013</a> 
<a name="L1014" href="source/net/ipv4/netfilter/ip_tables.c#L1014">1014</a>         if (cv &gt; 0)
<a name="L1015" href="source/net/ipv4/netfilter/ip_tables.c#L1015">1015</a>                 cv -= <a href="ident?i=xt_compat_calc_jump">xt_compat_calc_jump</a>(<a href="ident?i=AF_INET">AF_INET</a>, cv);
<a name="L1016" href="source/net/ipv4/netfilter/ip_tables.c#L1016">1016</a>         return <a href="ident?i=copy_to_user">copy_to_user</a>(<a href="ident?i=dst">dst</a>, &amp;cv, sizeof(cv)) ? -<a href="ident?i=EFAULT">EFAULT</a> : 0;
<a name="L1017" href="source/net/ipv4/netfilter/ip_tables.c#L1017">1017</a> }
<a name="L1018" href="source/net/ipv4/netfilter/ip_tables.c#L1018">1018</a> 
<a name="L1019" href="source/net/ipv4/netfilter/ip_tables.c#L1019">1019</a> static int <a href="ident?i=compat_calc_entry">compat_calc_entry</a>(const struct <a href="ident?i=ipt_entry">ipt_entry</a> *<a href="ident?i=e">e</a>,
<a name="L1020" href="source/net/ipv4/netfilter/ip_tables.c#L1020">1020</a>                              const struct <a href="ident?i=xt_table_info">xt_table_info</a> *<a href="ident?i=info">info</a>,
<a name="L1021" href="source/net/ipv4/netfilter/ip_tables.c#L1021">1021</a>                              const void *<a href="ident?i=base">base</a>, struct <a href="ident?i=xt_table_info">xt_table_info</a> *newinfo)
<a name="L1022" href="source/net/ipv4/netfilter/ip_tables.c#L1022">1022</a> {
<a name="L1023" href="source/net/ipv4/netfilter/ip_tables.c#L1023">1023</a>         const struct <a href="ident?i=xt_entry_match">xt_entry_match</a> *ematch;
<a name="L1024" href="source/net/ipv4/netfilter/ip_tables.c#L1024">1024</a>         const struct <a href="ident?i=xt_entry_target">xt_entry_target</a> *<a href="ident?i=t">t</a>;
<a name="L1025" href="source/net/ipv4/netfilter/ip_tables.c#L1025">1025</a>         unsigned int entry_offset;
<a name="L1026" href="source/net/ipv4/netfilter/ip_tables.c#L1026">1026</a>         int <a href="ident?i=off">off</a>, <a href="ident?i=i">i</a>, <a href="ident?i=ret">ret</a>;
<a name="L1027" href="source/net/ipv4/netfilter/ip_tables.c#L1027">1027</a> 
<a name="L1028" href="source/net/ipv4/netfilter/ip_tables.c#L1028">1028</a>         <a href="ident?i=off">off</a> = sizeof(struct <a href="ident?i=ipt_entry">ipt_entry</a>) - sizeof(struct <a href="ident?i=compat_ipt_entry">compat_ipt_entry</a>);
<a name="L1029" href="source/net/ipv4/netfilter/ip_tables.c#L1029">1029</a>         entry_offset = (void *)<a href="ident?i=e">e</a> - <a href="ident?i=base">base</a>;
<a name="L1030" href="source/net/ipv4/netfilter/ip_tables.c#L1030">1030</a>         <a href="ident?i=xt_ematch_foreach">xt_ematch_foreach</a>(ematch, <a href="ident?i=e">e</a>)
<a name="L1031" href="source/net/ipv4/netfilter/ip_tables.c#L1031">1031</a>                 <a href="ident?i=off">off</a> += <a href="ident?i=xt_compat_match_offset">xt_compat_match_offset</a>(ematch-&gt;u.kernel.<a href="ident?i=match">match</a>);
<a name="L1032" href="source/net/ipv4/netfilter/ip_tables.c#L1032">1032</a>         <a href="ident?i=t">t</a> = <a href="ident?i=ipt_get_target_c">ipt_get_target_c</a>(<a href="ident?i=e">e</a>);
<a name="L1033" href="source/net/ipv4/netfilter/ip_tables.c#L1033">1033</a>         <a href="ident?i=off">off</a> += <a href="ident?i=xt_compat_target_offset">xt_compat_target_offset</a>(<a href="ident?i=t">t</a>-&gt;u.kernel.<a href="ident?i=target">target</a>);
<a name="L1034" href="source/net/ipv4/netfilter/ip_tables.c#L1034">1034</a>         newinfo-&gt;<a href="ident?i=size">size</a> -= <a href="ident?i=off">off</a>;
<a name="L1035" href="source/net/ipv4/netfilter/ip_tables.c#L1035">1035</a>         <a href="ident?i=ret">ret</a> = <a href="ident?i=xt_compat_add_offset">xt_compat_add_offset</a>(<a href="ident?i=AF_INET">AF_INET</a>, entry_offset, <a href="ident?i=off">off</a>);
<a name="L1036" href="source/net/ipv4/netfilter/ip_tables.c#L1036">1036</a>         if (<a href="ident?i=ret">ret</a>)
<a name="L1037" href="source/net/ipv4/netfilter/ip_tables.c#L1037">1037</a>                 return <a href="ident?i=ret">ret</a>;
<a name="L1038" href="source/net/ipv4/netfilter/ip_tables.c#L1038">1038</a> 
<a name="L1039" href="source/net/ipv4/netfilter/ip_tables.c#L1039">1039</a>         for (<a href="ident?i=i">i</a> = 0; <a href="ident?i=i">i</a> &lt; NF_INET_NUMHOOKS; <a href="ident?i=i">i</a>++) {
<a name="L1040" href="source/net/ipv4/netfilter/ip_tables.c#L1040">1040</a>                 if (<a href="ident?i=info">info</a>-&gt;hook_entry[<a href="ident?i=i">i</a>] &amp;&amp;
<a name="L1041" href="source/net/ipv4/netfilter/ip_tables.c#L1041">1041</a>                     (<a href="ident?i=e">e</a> &lt; (struct <a href="ident?i=ipt_entry">ipt_entry</a> *)(<a href="ident?i=base">base</a> + <a href="ident?i=info">info</a>-&gt;hook_entry[<a href="ident?i=i">i</a>])))
<a name="L1042" href="source/net/ipv4/netfilter/ip_tables.c#L1042">1042</a>                         newinfo-&gt;hook_entry[<a href="ident?i=i">i</a>] -= <a href="ident?i=off">off</a>;
<a name="L1043" href="source/net/ipv4/netfilter/ip_tables.c#L1043">1043</a>                 if (<a href="ident?i=info">info</a>-&gt;underflow[<a href="ident?i=i">i</a>] &amp;&amp;
<a name="L1044" href="source/net/ipv4/netfilter/ip_tables.c#L1044">1044</a>                     (<a href="ident?i=e">e</a> &lt; (struct <a href="ident?i=ipt_entry">ipt_entry</a> *)(<a href="ident?i=base">base</a> + <a href="ident?i=info">info</a>-&gt;underflow[<a href="ident?i=i">i</a>])))
<a name="L1045" href="source/net/ipv4/netfilter/ip_tables.c#L1045">1045</a>                         newinfo-&gt;underflow[<a href="ident?i=i">i</a>] -= <a href="ident?i=off">off</a>;
<a name="L1046" href="source/net/ipv4/netfilter/ip_tables.c#L1046">1046</a>         }
<a name="L1047" href="source/net/ipv4/netfilter/ip_tables.c#L1047">1047</a>         return 0;
<a name="L1048" href="source/net/ipv4/netfilter/ip_tables.c#L1048">1048</a> }
<a name="L1049" href="source/net/ipv4/netfilter/ip_tables.c#L1049">1049</a> 
<a name="L1050" href="source/net/ipv4/netfilter/ip_tables.c#L1050">1050</a> static int <a href="ident?i=compat_table_info">compat_table_info</a>(const struct <a href="ident?i=xt_table_info">xt_table_info</a> *<a href="ident?i=info">info</a>,
<a name="L1051" href="source/net/ipv4/netfilter/ip_tables.c#L1051">1051</a>                              struct <a href="ident?i=xt_table_info">xt_table_info</a> *newinfo)
<a name="L1052" href="source/net/ipv4/netfilter/ip_tables.c#L1052">1052</a> {
<a name="L1053" href="source/net/ipv4/netfilter/ip_tables.c#L1053">1053</a>         struct <a href="ident?i=ipt_entry">ipt_entry</a> *iter;
<a name="L1054" href="source/net/ipv4/netfilter/ip_tables.c#L1054">1054</a>         void *loc_cpu_entry;
<a name="L1055" href="source/net/ipv4/netfilter/ip_tables.c#L1055">1055</a>         int <a href="ident?i=ret">ret</a>;
<a name="L1056" href="source/net/ipv4/netfilter/ip_tables.c#L1056">1056</a> 
<a name="L1057" href="source/net/ipv4/netfilter/ip_tables.c#L1057">1057</a>         if (!newinfo || !<a href="ident?i=info">info</a>)
<a name="L1058" href="source/net/ipv4/netfilter/ip_tables.c#L1058">1058</a>                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L1059" href="source/net/ipv4/netfilter/ip_tables.c#L1059">1059</a> 
<a name="L1060" href="source/net/ipv4/netfilter/ip_tables.c#L1060">1060</a>         <b><i>/* we dont care about newinfo-&gt;entries[] */</i></b>
<a name="L1061" href="source/net/ipv4/netfilter/ip_tables.c#L1061">1061</a>         <a href="ident?i=memcpy">memcpy</a>(newinfo, <a href="ident?i=info">info</a>, <a href="ident?i=offsetof">offsetof</a>(struct <a href="ident?i=xt_table_info">xt_table_info</a>, <a href="ident?i=entries">entries</a>));
<a name="L1062" href="source/net/ipv4/netfilter/ip_tables.c#L1062">1062</a>         newinfo-&gt;initial_entries = 0;
<a name="L1063" href="source/net/ipv4/netfilter/ip_tables.c#L1063">1063</a>         loc_cpu_entry = <a href="ident?i=info">info</a>-&gt;<a href="ident?i=entries">entries</a>[<a href="ident?i=raw_smp_processor_id">raw_smp_processor_id</a>()];
<a name="L1064" href="source/net/ipv4/netfilter/ip_tables.c#L1064">1064</a>         <a href="ident?i=xt_compat_init_offsets">xt_compat_init_offsets</a>(<a href="ident?i=AF_INET">AF_INET</a>, <a href="ident?i=info">info</a>-&gt;<a href="ident?i=number">number</a>);
<a name="L1065" href="source/net/ipv4/netfilter/ip_tables.c#L1065">1065</a>         <a href="ident?i=xt_entry_foreach">xt_entry_foreach</a>(iter, loc_cpu_entry, <a href="ident?i=info">info</a>-&gt;<a href="ident?i=size">size</a>) {
<a name="L1066" href="source/net/ipv4/netfilter/ip_tables.c#L1066">1066</a>                 <a href="ident?i=ret">ret</a> = <a href="ident?i=compat_calc_entry">compat_calc_entry</a>(iter, <a href="ident?i=info">info</a>, loc_cpu_entry, newinfo);
<a name="L1067" href="source/net/ipv4/netfilter/ip_tables.c#L1067">1067</a>                 if (<a href="ident?i=ret">ret</a> != 0)
<a name="L1068" href="source/net/ipv4/netfilter/ip_tables.c#L1068">1068</a>                         return <a href="ident?i=ret">ret</a>;
<a name="L1069" href="source/net/ipv4/netfilter/ip_tables.c#L1069">1069</a>         }
<a name="L1070" href="source/net/ipv4/netfilter/ip_tables.c#L1070">1070</a>         return 0;
<a name="L1071" href="source/net/ipv4/netfilter/ip_tables.c#L1071">1071</a> }
<a name="L1072" href="source/net/ipv4/netfilter/ip_tables.c#L1072">1072</a> #endif
<a name="L1073" href="source/net/ipv4/netfilter/ip_tables.c#L1073">1073</a> 
<a name="L1074" href="source/net/ipv4/netfilter/ip_tables.c#L1074">1074</a> static int <a href="ident?i=get_info">get_info</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>, void <a href="ident?i=__user">__user</a> *<a href="ident?i=user">user</a>,
<a name="L1075" href="source/net/ipv4/netfilter/ip_tables.c#L1075">1075</a>                     const int *<a href="ident?i=len">len</a>, int <a href="ident?i=compat">compat</a>)
<a name="L1076" href="source/net/ipv4/netfilter/ip_tables.c#L1076">1076</a> {
<a name="L1077" href="source/net/ipv4/netfilter/ip_tables.c#L1077">1077</a>         char <a href="ident?i=name">name</a>[<a href="ident?i=XT_TABLE_MAXNAMELEN">XT_TABLE_MAXNAMELEN</a>];
<a name="L1078" href="source/net/ipv4/netfilter/ip_tables.c#L1078">1078</a>         struct <a href="ident?i=xt_table">xt_table</a> *<a href="ident?i=t">t</a>;
<a name="L1079" href="source/net/ipv4/netfilter/ip_tables.c#L1079">1079</a>         int <a href="ident?i=ret">ret</a>;
<a name="L1080" href="source/net/ipv4/netfilter/ip_tables.c#L1080">1080</a> 
<a name="L1081" href="source/net/ipv4/netfilter/ip_tables.c#L1081">1081</a>         if (*<a href="ident?i=len">len</a> != sizeof(struct <a href="ident?i=ipt_getinfo">ipt_getinfo</a>)) {
<a name="L1082" href="source/net/ipv4/netfilter/ip_tables.c#L1082">1082</a>                 <a href="ident?i=duprintf">duprintf</a>(<i>"length %u != %zu\n"</i>, *<a href="ident?i=len">len</a>,
<a name="L1083" href="source/net/ipv4/netfilter/ip_tables.c#L1083">1083</a>                          sizeof(struct <a href="ident?i=ipt_getinfo">ipt_getinfo</a>));
<a name="L1084" href="source/net/ipv4/netfilter/ip_tables.c#L1084">1084</a>                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L1085" href="source/net/ipv4/netfilter/ip_tables.c#L1085">1085</a>         }
<a name="L1086" href="source/net/ipv4/netfilter/ip_tables.c#L1086">1086</a> 
<a name="L1087" href="source/net/ipv4/netfilter/ip_tables.c#L1087">1087</a>         if (<a href="ident?i=copy_from_user">copy_from_user</a>(<a href="ident?i=name">name</a>, <a href="ident?i=user">user</a>, sizeof(<a href="ident?i=name">name</a>)) != 0)
<a name="L1088" href="source/net/ipv4/netfilter/ip_tables.c#L1088">1088</a>                 return -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L1089" href="source/net/ipv4/netfilter/ip_tables.c#L1089">1089</a> 
<a name="L1090" href="source/net/ipv4/netfilter/ip_tables.c#L1090">1090</a>         <a href="ident?i=name">name</a>[<a href="ident?i=XT_TABLE_MAXNAMELEN">XT_TABLE_MAXNAMELEN</a>-1] = <i>'\0'</i>;
<a name="L1091" href="source/net/ipv4/netfilter/ip_tables.c#L1091">1091</a> #ifdef CONFIG_COMPAT
<a name="L1092" href="source/net/ipv4/netfilter/ip_tables.c#L1092">1092</a>         if (<a href="ident?i=compat">compat</a>)
<a name="L1093" href="source/net/ipv4/netfilter/ip_tables.c#L1093">1093</a>                 <a href="ident?i=xt_compat_lock">xt_compat_lock</a>(<a href="ident?i=AF_INET">AF_INET</a>);
<a name="L1094" href="source/net/ipv4/netfilter/ip_tables.c#L1094">1094</a> #endif
<a name="L1095" href="source/net/ipv4/netfilter/ip_tables.c#L1095">1095</a>         <a href="ident?i=t">t</a> = <a href="ident?i=try_then_request_module">try_then_request_module</a>(<a href="ident?i=xt_find_table_lock">xt_find_table_lock</a>(<a href="ident?i=net">net</a>, <a href="ident?i=AF_INET">AF_INET</a>, <a href="ident?i=name">name</a>),
<a name="L1096" href="source/net/ipv4/netfilter/ip_tables.c#L1096">1096</a>                                     <i>"iptable_%s"</i>, <a href="ident?i=name">name</a>);
<a name="L1097" href="source/net/ipv4/netfilter/ip_tables.c#L1097">1097</a>         if (!<a href="ident?i=IS_ERR_OR_NULL">IS_ERR_OR_NULL</a>(<a href="ident?i=t">t</a>)) {
<a name="L1098" href="source/net/ipv4/netfilter/ip_tables.c#L1098">1098</a>                 struct <a href="ident?i=ipt_getinfo">ipt_getinfo</a> <a href="ident?i=info">info</a>;
<a name="L1099" href="source/net/ipv4/netfilter/ip_tables.c#L1099">1099</a>                 const struct <a href="ident?i=xt_table_info">xt_table_info</a> *<a href="ident?i=private">private</a> = <a href="ident?i=t">t</a>-&gt;<a href="ident?i=private">private</a>;
<a name="L1100" href="source/net/ipv4/netfilter/ip_tables.c#L1100">1100</a> #ifdef CONFIG_COMPAT
<a name="L1101" href="source/net/ipv4/netfilter/ip_tables.c#L1101">1101</a>                 struct <a href="ident?i=xt_table_info">xt_table_info</a> <a href="ident?i=tmp">tmp</a>;
<a name="L1102" href="source/net/ipv4/netfilter/ip_tables.c#L1102">1102</a> 
<a name="L1103" href="source/net/ipv4/netfilter/ip_tables.c#L1103">1103</a>                 if (<a href="ident?i=compat">compat</a>) {
<a name="L1104" href="source/net/ipv4/netfilter/ip_tables.c#L1104">1104</a>                         <a href="ident?i=ret">ret</a> = <a href="ident?i=compat_table_info">compat_table_info</a>(<a href="ident?i=private">private</a>, &amp;<a href="ident?i=tmp">tmp</a>);
<a name="L1105" href="source/net/ipv4/netfilter/ip_tables.c#L1105">1105</a>                         <a href="ident?i=xt_compat_flush_offsets">xt_compat_flush_offsets</a>(<a href="ident?i=AF_INET">AF_INET</a>);
<a name="L1106" href="source/net/ipv4/netfilter/ip_tables.c#L1106">1106</a>                         <a href="ident?i=private">private</a> = &amp;<a href="ident?i=tmp">tmp</a>;
<a name="L1107" href="source/net/ipv4/netfilter/ip_tables.c#L1107">1107</a>                 }
<a name="L1108" href="source/net/ipv4/netfilter/ip_tables.c#L1108">1108</a> #endif
<a name="L1109" href="source/net/ipv4/netfilter/ip_tables.c#L1109">1109</a>                 <a href="ident?i=memset">memset</a>(&amp;<a href="ident?i=info">info</a>, 0, sizeof(<a href="ident?i=info">info</a>));
<a name="L1110" href="source/net/ipv4/netfilter/ip_tables.c#L1110">1110</a>                 <a href="ident?i=info">info</a>.valid_hooks = <a href="ident?i=t">t</a>-&gt;valid_hooks;
<a name="L1111" href="source/net/ipv4/netfilter/ip_tables.c#L1111">1111</a>                 <a href="ident?i=memcpy">memcpy</a>(<a href="ident?i=info">info</a>.hook_entry, <a href="ident?i=private">private</a>-&gt;hook_entry,
<a name="L1112" href="source/net/ipv4/netfilter/ip_tables.c#L1112">1112</a>                        sizeof(<a href="ident?i=info">info</a>.hook_entry));
<a name="L1113" href="source/net/ipv4/netfilter/ip_tables.c#L1113">1113</a>                 <a href="ident?i=memcpy">memcpy</a>(<a href="ident?i=info">info</a>.underflow, <a href="ident?i=private">private</a>-&gt;underflow,
<a name="L1114" href="source/net/ipv4/netfilter/ip_tables.c#L1114">1114</a>                        sizeof(<a href="ident?i=info">info</a>.underflow));
<a name="L1115" href="source/net/ipv4/netfilter/ip_tables.c#L1115">1115</a>                 <a href="ident?i=info">info</a>.<a href="ident?i=num_entries">num_entries</a> = <a href="ident?i=private">private</a>-&gt;<a href="ident?i=number">number</a>;
<a name="L1116" href="source/net/ipv4/netfilter/ip_tables.c#L1116">1116</a>                 <a href="ident?i=info">info</a>.<a href="ident?i=size">size</a> = <a href="ident?i=private">private</a>-&gt;<a href="ident?i=size">size</a>;
<a name="L1117" href="source/net/ipv4/netfilter/ip_tables.c#L1117">1117</a>                 <a href="ident?i=strcpy">strcpy</a>(<a href="ident?i=info">info</a>.<a href="ident?i=name">name</a>, <a href="ident?i=name">name</a>);
<a name="L1118" href="source/net/ipv4/netfilter/ip_tables.c#L1118">1118</a> 
<a name="L1119" href="source/net/ipv4/netfilter/ip_tables.c#L1119">1119</a>                 if (<a href="ident?i=copy_to_user">copy_to_user</a>(<a href="ident?i=user">user</a>, &amp;<a href="ident?i=info">info</a>, *<a href="ident?i=len">len</a>) != 0)
<a name="L1120" href="source/net/ipv4/netfilter/ip_tables.c#L1120">1120</a>                         <a href="ident?i=ret">ret</a> = -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L1121" href="source/net/ipv4/netfilter/ip_tables.c#L1121">1121</a>                 else
<a name="L1122" href="source/net/ipv4/netfilter/ip_tables.c#L1122">1122</a>                         <a href="ident?i=ret">ret</a> = 0;
<a name="L1123" href="source/net/ipv4/netfilter/ip_tables.c#L1123">1123</a> 
<a name="L1124" href="source/net/ipv4/netfilter/ip_tables.c#L1124">1124</a>                 <a href="ident?i=xt_table_unlock">xt_table_unlock</a>(<a href="ident?i=t">t</a>);
<a name="L1125" href="source/net/ipv4/netfilter/ip_tables.c#L1125">1125</a>                 <a href="ident?i=module_put">module_put</a>(<a href="ident?i=t">t</a>-&gt;<a href="ident?i=me">me</a>);
<a name="L1126" href="source/net/ipv4/netfilter/ip_tables.c#L1126">1126</a>         } else
<a name="L1127" href="source/net/ipv4/netfilter/ip_tables.c#L1127">1127</a>                 <a href="ident?i=ret">ret</a> = <a href="ident?i=t">t</a> ? <a href="ident?i=PTR_ERR">PTR_ERR</a>(<a href="ident?i=t">t</a>) : -<a href="ident?i=ENOENT">ENOENT</a>;
<a name="L1128" href="source/net/ipv4/netfilter/ip_tables.c#L1128">1128</a> #ifdef CONFIG_COMPAT
<a name="L1129" href="source/net/ipv4/netfilter/ip_tables.c#L1129">1129</a>         if (<a href="ident?i=compat">compat</a>)
<a name="L1130" href="source/net/ipv4/netfilter/ip_tables.c#L1130">1130</a>                 <a href="ident?i=xt_compat_unlock">xt_compat_unlock</a>(<a href="ident?i=AF_INET">AF_INET</a>);
<a name="L1131" href="source/net/ipv4/netfilter/ip_tables.c#L1131">1131</a> #endif
<a name="L1132" href="source/net/ipv4/netfilter/ip_tables.c#L1132">1132</a>         return <a href="ident?i=ret">ret</a>;
<a name="L1133" href="source/net/ipv4/netfilter/ip_tables.c#L1133">1133</a> }
<a name="L1134" href="source/net/ipv4/netfilter/ip_tables.c#L1134">1134</a> 
<a name="L1135" href="source/net/ipv4/netfilter/ip_tables.c#L1135">1135</a> static int
<a name="L1136" href="source/net/ipv4/netfilter/ip_tables.c#L1136">1136</a> <a href="ident?i=get_entries">get_entries</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>, struct <a href="ident?i=ipt_get_entries">ipt_get_entries</a> <a href="ident?i=__user">__user</a> *uptr,
<a name="L1137" href="source/net/ipv4/netfilter/ip_tables.c#L1137">1137</a>             const int *<a href="ident?i=len">len</a>)
<a name="L1138" href="source/net/ipv4/netfilter/ip_tables.c#L1138">1138</a> {
<a name="L1139" href="source/net/ipv4/netfilter/ip_tables.c#L1139">1139</a>         int <a href="ident?i=ret">ret</a>;
<a name="L1140" href="source/net/ipv4/netfilter/ip_tables.c#L1140">1140</a>         struct <a href="ident?i=ipt_get_entries">ipt_get_entries</a> <a href="ident?i=get">get</a>;
<a name="L1141" href="source/net/ipv4/netfilter/ip_tables.c#L1141">1141</a>         struct <a href="ident?i=xt_table">xt_table</a> *<a href="ident?i=t">t</a>;
<a name="L1142" href="source/net/ipv4/netfilter/ip_tables.c#L1142">1142</a> 
<a name="L1143" href="source/net/ipv4/netfilter/ip_tables.c#L1143">1143</a>         if (*<a href="ident?i=len">len</a> &lt; sizeof(<a href="ident?i=get">get</a>)) {
<a name="L1144" href="source/net/ipv4/netfilter/ip_tables.c#L1144">1144</a>                 <a href="ident?i=duprintf">duprintf</a>(<i>"get_entries: %u &lt; %zu\n"</i>, *<a href="ident?i=len">len</a>, sizeof(<a href="ident?i=get">get</a>));
<a name="L1145" href="source/net/ipv4/netfilter/ip_tables.c#L1145">1145</a>                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L1146" href="source/net/ipv4/netfilter/ip_tables.c#L1146">1146</a>         }
<a name="L1147" href="source/net/ipv4/netfilter/ip_tables.c#L1147">1147</a>         if (<a href="ident?i=copy_from_user">copy_from_user</a>(&amp;<a href="ident?i=get">get</a>, uptr, sizeof(<a href="ident?i=get">get</a>)) != 0)
<a name="L1148" href="source/net/ipv4/netfilter/ip_tables.c#L1148">1148</a>                 return -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L1149" href="source/net/ipv4/netfilter/ip_tables.c#L1149">1149</a>         if (*<a href="ident?i=len">len</a> != sizeof(struct <a href="ident?i=ipt_get_entries">ipt_get_entries</a>) + <a href="ident?i=get">get</a>.<a href="ident?i=size">size</a>) {
<a name="L1150" href="source/net/ipv4/netfilter/ip_tables.c#L1150">1150</a>                 <a href="ident?i=duprintf">duprintf</a>(<i>"get_entries: %u != %zu\n"</i>,
<a name="L1151" href="source/net/ipv4/netfilter/ip_tables.c#L1151">1151</a>                          *<a href="ident?i=len">len</a>, sizeof(<a href="ident?i=get">get</a>) + <a href="ident?i=get">get</a>.<a href="ident?i=size">size</a>);
<a name="L1152" href="source/net/ipv4/netfilter/ip_tables.c#L1152">1152</a>                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L1153" href="source/net/ipv4/netfilter/ip_tables.c#L1153">1153</a>         }
<a name="L1154" href="source/net/ipv4/netfilter/ip_tables.c#L1154">1154</a> 
<a name="L1155" href="source/net/ipv4/netfilter/ip_tables.c#L1155">1155</a>         <a href="ident?i=t">t</a> = <a href="ident?i=xt_find_table_lock">xt_find_table_lock</a>(<a href="ident?i=net">net</a>, <a href="ident?i=AF_INET">AF_INET</a>, <a href="ident?i=get">get</a>.<a href="ident?i=name">name</a>);
<a name="L1156" href="source/net/ipv4/netfilter/ip_tables.c#L1156">1156</a>         if (!<a href="ident?i=IS_ERR_OR_NULL">IS_ERR_OR_NULL</a>(<a href="ident?i=t">t</a>)) {
<a name="L1157" href="source/net/ipv4/netfilter/ip_tables.c#L1157">1157</a>                 const struct <a href="ident?i=xt_table_info">xt_table_info</a> *<a href="ident?i=private">private</a> = <a href="ident?i=t">t</a>-&gt;<a href="ident?i=private">private</a>;
<a name="L1158" href="source/net/ipv4/netfilter/ip_tables.c#L1158">1158</a>                 <a href="ident?i=duprintf">duprintf</a>(<i>"t-&gt;private-&gt;number = %u\n"</i>, <a href="ident?i=private">private</a>-&gt;<a href="ident?i=number">number</a>);
<a name="L1159" href="source/net/ipv4/netfilter/ip_tables.c#L1159">1159</a>                 if (<a href="ident?i=get">get</a>.<a href="ident?i=size">size</a> == <a href="ident?i=private">private</a>-&gt;<a href="ident?i=size">size</a>)
<a name="L1160" href="source/net/ipv4/netfilter/ip_tables.c#L1160">1160</a>                         <a href="ident?i=ret">ret</a> = <a href="ident?i=copy_entries_to_user">copy_entries_to_user</a>(<a href="ident?i=private">private</a>-&gt;<a href="ident?i=size">size</a>,
<a name="L1161" href="source/net/ipv4/netfilter/ip_tables.c#L1161">1161</a>                                                    <a href="ident?i=t">t</a>, uptr-&gt;entrytable);
<a name="L1162" href="source/net/ipv4/netfilter/ip_tables.c#L1162">1162</a>                 else {
<a name="L1163" href="source/net/ipv4/netfilter/ip_tables.c#L1163">1163</a>                         <a href="ident?i=duprintf">duprintf</a>(<i>"get_entries: I've got %u not %u!\n"</i>,
<a name="L1164" href="source/net/ipv4/netfilter/ip_tables.c#L1164">1164</a>                                  <a href="ident?i=private">private</a>-&gt;<a href="ident?i=size">size</a>, <a href="ident?i=get">get</a>.<a href="ident?i=size">size</a>);
<a name="L1165" href="source/net/ipv4/netfilter/ip_tables.c#L1165">1165</a>                         <a href="ident?i=ret">ret</a> = -<a href="ident?i=EAGAIN">EAGAIN</a>;
<a name="L1166" href="source/net/ipv4/netfilter/ip_tables.c#L1166">1166</a>                 }
<a name="L1167" href="source/net/ipv4/netfilter/ip_tables.c#L1167">1167</a>                 <a href="ident?i=module_put">module_put</a>(<a href="ident?i=t">t</a>-&gt;<a href="ident?i=me">me</a>);
<a name="L1168" href="source/net/ipv4/netfilter/ip_tables.c#L1168">1168</a>                 <a href="ident?i=xt_table_unlock">xt_table_unlock</a>(<a href="ident?i=t">t</a>);
<a name="L1169" href="source/net/ipv4/netfilter/ip_tables.c#L1169">1169</a>         } else
<a name="L1170" href="source/net/ipv4/netfilter/ip_tables.c#L1170">1170</a>                 <a href="ident?i=ret">ret</a> = <a href="ident?i=t">t</a> ? <a href="ident?i=PTR_ERR">PTR_ERR</a>(<a href="ident?i=t">t</a>) : -<a href="ident?i=ENOENT">ENOENT</a>;
<a name="L1171" href="source/net/ipv4/netfilter/ip_tables.c#L1171">1171</a> 
<a name="L1172" href="source/net/ipv4/netfilter/ip_tables.c#L1172">1172</a>         return <a href="ident?i=ret">ret</a>;
<a name="L1173" href="source/net/ipv4/netfilter/ip_tables.c#L1173">1173</a> }
<a name="L1174" href="source/net/ipv4/netfilter/ip_tables.c#L1174">1174</a> 
<a name="L1175" href="source/net/ipv4/netfilter/ip_tables.c#L1175">1175</a> static int
<a name="L1176" href="source/net/ipv4/netfilter/ip_tables.c#L1176">1176</a> <a href="ident?i=__do_replace">__do_replace</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>, const char *<a href="ident?i=name">name</a>, unsigned int valid_hooks,
<a name="L1177" href="source/net/ipv4/netfilter/ip_tables.c#L1177">1177</a>              struct <a href="ident?i=xt_table_info">xt_table_info</a> *newinfo, unsigned int <a href="ident?i=num_counters">num_counters</a>,
<a name="L1178" href="source/net/ipv4/netfilter/ip_tables.c#L1178">1178</a>              void <a href="ident?i=__user">__user</a> *counters_ptr)
<a name="L1179" href="source/net/ipv4/netfilter/ip_tables.c#L1179">1179</a> {
<a name="L1180" href="source/net/ipv4/netfilter/ip_tables.c#L1180">1180</a>         int <a href="ident?i=ret">ret</a>;
<a name="L1181" href="source/net/ipv4/netfilter/ip_tables.c#L1181">1181</a>         struct <a href="ident?i=xt_table">xt_table</a> *<a href="ident?i=t">t</a>;
<a name="L1182" href="source/net/ipv4/netfilter/ip_tables.c#L1182">1182</a>         struct <a href="ident?i=xt_table_info">xt_table_info</a> *oldinfo;
<a name="L1183" href="source/net/ipv4/netfilter/ip_tables.c#L1183">1183</a>         struct <a href="ident?i=xt_counters">xt_counters</a> *counters;
<a name="L1184" href="source/net/ipv4/netfilter/ip_tables.c#L1184">1184</a>         void *loc_cpu_old_entry;
<a name="L1185" href="source/net/ipv4/netfilter/ip_tables.c#L1185">1185</a>         struct <a href="ident?i=ipt_entry">ipt_entry</a> *iter;
<a name="L1186" href="source/net/ipv4/netfilter/ip_tables.c#L1186">1186</a> 
<a name="L1187" href="source/net/ipv4/netfilter/ip_tables.c#L1187">1187</a>         <a href="ident?i=ret">ret</a> = 0;
<a name="L1188" href="source/net/ipv4/netfilter/ip_tables.c#L1188">1188</a>         counters = <a href="ident?i=vzalloc">vzalloc</a>(<a href="ident?i=num_counters">num_counters</a> * sizeof(struct <a href="ident?i=xt_counters">xt_counters</a>));
<a name="L1189" href="source/net/ipv4/netfilter/ip_tables.c#L1189">1189</a>         if (!counters) {
<a name="L1190" href="source/net/ipv4/netfilter/ip_tables.c#L1190">1190</a>                 <a href="ident?i=ret">ret</a> = -<a href="ident?i=ENOMEM">ENOMEM</a>;
<a name="L1191" href="source/net/ipv4/netfilter/ip_tables.c#L1191">1191</a>                 goto <a href="ident?i=out">out</a>;
<a name="L1192" href="source/net/ipv4/netfilter/ip_tables.c#L1192">1192</a>         }
<a name="L1193" href="source/net/ipv4/netfilter/ip_tables.c#L1193">1193</a> 
<a name="L1194" href="source/net/ipv4/netfilter/ip_tables.c#L1194">1194</a>         <a href="ident?i=t">t</a> = <a href="ident?i=try_then_request_module">try_then_request_module</a>(<a href="ident?i=xt_find_table_lock">xt_find_table_lock</a>(<a href="ident?i=net">net</a>, <a href="ident?i=AF_INET">AF_INET</a>, <a href="ident?i=name">name</a>),
<a name="L1195" href="source/net/ipv4/netfilter/ip_tables.c#L1195">1195</a>                                     <i>"iptable_%s"</i>, <a href="ident?i=name">name</a>);
<a name="L1196" href="source/net/ipv4/netfilter/ip_tables.c#L1196">1196</a>         if (<a href="ident?i=IS_ERR_OR_NULL">IS_ERR_OR_NULL</a>(<a href="ident?i=t">t</a>)) {
<a name="L1197" href="source/net/ipv4/netfilter/ip_tables.c#L1197">1197</a>                 <a href="ident?i=ret">ret</a> = <a href="ident?i=t">t</a> ? <a href="ident?i=PTR_ERR">PTR_ERR</a>(<a href="ident?i=t">t</a>) : -<a href="ident?i=ENOENT">ENOENT</a>;
<a name="L1198" href="source/net/ipv4/netfilter/ip_tables.c#L1198">1198</a>                 goto free_newinfo_counters_untrans;
<a name="L1199" href="source/net/ipv4/netfilter/ip_tables.c#L1199">1199</a>         }
<a name="L1200" href="source/net/ipv4/netfilter/ip_tables.c#L1200">1200</a> 
<a name="L1201" href="source/net/ipv4/netfilter/ip_tables.c#L1201">1201</a>         <b><i>/* You lied! */</i></b>
<a name="L1202" href="source/net/ipv4/netfilter/ip_tables.c#L1202">1202</a>         if (valid_hooks != <a href="ident?i=t">t</a>-&gt;valid_hooks) {
<a name="L1203" href="source/net/ipv4/netfilter/ip_tables.c#L1203">1203</a>                 <a href="ident?i=duprintf">duprintf</a>(<i>"Valid hook crap: %08X vs %08X\n"</i>,
<a name="L1204" href="source/net/ipv4/netfilter/ip_tables.c#L1204">1204</a>                          valid_hooks, <a href="ident?i=t">t</a>-&gt;valid_hooks);
<a name="L1205" href="source/net/ipv4/netfilter/ip_tables.c#L1205">1205</a>                 <a href="ident?i=ret">ret</a> = -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L1206" href="source/net/ipv4/netfilter/ip_tables.c#L1206">1206</a>                 goto put_module;
<a name="L1207" href="source/net/ipv4/netfilter/ip_tables.c#L1207">1207</a>         }
<a name="L1208" href="source/net/ipv4/netfilter/ip_tables.c#L1208">1208</a> 
<a name="L1209" href="source/net/ipv4/netfilter/ip_tables.c#L1209">1209</a>         oldinfo = <a href="ident?i=xt_replace_table">xt_replace_table</a>(<a href="ident?i=t">t</a>, <a href="ident?i=num_counters">num_counters</a>, newinfo, &amp;<a href="ident?i=ret">ret</a>);
<a name="L1210" href="source/net/ipv4/netfilter/ip_tables.c#L1210">1210</a>         if (!oldinfo)
<a name="L1211" href="source/net/ipv4/netfilter/ip_tables.c#L1211">1211</a>                 goto put_module;
<a name="L1212" href="source/net/ipv4/netfilter/ip_tables.c#L1212">1212</a> 
<a name="L1213" href="source/net/ipv4/netfilter/ip_tables.c#L1213">1213</a>         <b><i>/* Update module usage count based on number of rules */</i></b>
<a name="L1214" href="source/net/ipv4/netfilter/ip_tables.c#L1214">1214</a>         <a href="ident?i=duprintf">duprintf</a>(<i>"do_replace: oldnum=%u, initnum=%u, newnum=%u\n"</i>,
<a name="L1215" href="source/net/ipv4/netfilter/ip_tables.c#L1215">1215</a>                 oldinfo-&gt;<a href="ident?i=number">number</a>, oldinfo-&gt;initial_entries, newinfo-&gt;<a href="ident?i=number">number</a>);
<a name="L1216" href="source/net/ipv4/netfilter/ip_tables.c#L1216">1216</a>         if ((oldinfo-&gt;<a href="ident?i=number">number</a> &gt; oldinfo-&gt;initial_entries) ||
<a name="L1217" href="source/net/ipv4/netfilter/ip_tables.c#L1217">1217</a>             (newinfo-&gt;<a href="ident?i=number">number</a> &lt;= oldinfo-&gt;initial_entries))
<a name="L1218" href="source/net/ipv4/netfilter/ip_tables.c#L1218">1218</a>                 <a href="ident?i=module_put">module_put</a>(<a href="ident?i=t">t</a>-&gt;<a href="ident?i=me">me</a>);
<a name="L1219" href="source/net/ipv4/netfilter/ip_tables.c#L1219">1219</a>         if ((oldinfo-&gt;<a href="ident?i=number">number</a> &gt; oldinfo-&gt;initial_entries) &amp;&amp;
<a name="L1220" href="source/net/ipv4/netfilter/ip_tables.c#L1220">1220</a>             (newinfo-&gt;<a href="ident?i=number">number</a> &lt;= oldinfo-&gt;initial_entries))
<a name="L1221" href="source/net/ipv4/netfilter/ip_tables.c#L1221">1221</a>                 <a href="ident?i=module_put">module_put</a>(<a href="ident?i=t">t</a>-&gt;<a href="ident?i=me">me</a>);
<a name="L1222" href="source/net/ipv4/netfilter/ip_tables.c#L1222">1222</a> 
<a name="L1223" href="source/net/ipv4/netfilter/ip_tables.c#L1223">1223</a>         <b><i>/* Get the old counters, and synchronize with replace */</i></b>
<a name="L1224" href="source/net/ipv4/netfilter/ip_tables.c#L1224">1224</a>         <a href="ident?i=get_counters">get_counters</a>(oldinfo, counters);
<a name="L1225" href="source/net/ipv4/netfilter/ip_tables.c#L1225">1225</a> 
<a name="L1226" href="source/net/ipv4/netfilter/ip_tables.c#L1226">1226</a>         <b><i>/* Decrease module usage counts and free resource */</i></b>
<a name="L1227" href="source/net/ipv4/netfilter/ip_tables.c#L1227">1227</a>         loc_cpu_old_entry = oldinfo-&gt;<a href="ident?i=entries">entries</a>[<a href="ident?i=raw_smp_processor_id">raw_smp_processor_id</a>()];
<a name="L1228" href="source/net/ipv4/netfilter/ip_tables.c#L1228">1228</a>         <a href="ident?i=xt_entry_foreach">xt_entry_foreach</a>(iter, loc_cpu_old_entry, oldinfo-&gt;<a href="ident?i=size">size</a>)
<a name="L1229" href="source/net/ipv4/netfilter/ip_tables.c#L1229">1229</a>                 <a href="ident?i=cleanup_entry">cleanup_entry</a>(iter, <a href="ident?i=net">net</a>);
<a name="L1230" href="source/net/ipv4/netfilter/ip_tables.c#L1230">1230</a> 
<a name="L1231" href="source/net/ipv4/netfilter/ip_tables.c#L1231">1231</a>         <a href="ident?i=xt_free_table_info">xt_free_table_info</a>(oldinfo);
<a name="L1232" href="source/net/ipv4/netfilter/ip_tables.c#L1232">1232</a>         if (<a href="ident?i=copy_to_user">copy_to_user</a>(counters_ptr, counters,
<a name="L1233" href="source/net/ipv4/netfilter/ip_tables.c#L1233">1233</a>                          sizeof(struct <a href="ident?i=xt_counters">xt_counters</a>) * <a href="ident?i=num_counters">num_counters</a>) != 0) {
<a name="L1234" href="source/net/ipv4/netfilter/ip_tables.c#L1234">1234</a>                 <b><i>/* Silent error, can't fail, new table is already in place */</i></b>
<a name="L1235" href="source/net/ipv4/netfilter/ip_tables.c#L1235">1235</a>                 <a href="ident?i=net_warn_ratelimited">net_warn_ratelimited</a>(<i>"iptables: counters copy to user failed while replacing table\n"</i>);
<a name="L1236" href="source/net/ipv4/netfilter/ip_tables.c#L1236">1236</a>         }
<a name="L1237" href="source/net/ipv4/netfilter/ip_tables.c#L1237">1237</a>         <a href="ident?i=vfree">vfree</a>(counters);
<a name="L1238" href="source/net/ipv4/netfilter/ip_tables.c#L1238">1238</a>         <a href="ident?i=xt_table_unlock">xt_table_unlock</a>(<a href="ident?i=t">t</a>);
<a name="L1239" href="source/net/ipv4/netfilter/ip_tables.c#L1239">1239</a>         return <a href="ident?i=ret">ret</a>;
<a name="L1240" href="source/net/ipv4/netfilter/ip_tables.c#L1240">1240</a> 
<a name="L1241" href="source/net/ipv4/netfilter/ip_tables.c#L1241">1241</a>  put_module:
<a name="L1242" href="source/net/ipv4/netfilter/ip_tables.c#L1242">1242</a>         <a href="ident?i=module_put">module_put</a>(<a href="ident?i=t">t</a>-&gt;<a href="ident?i=me">me</a>);
<a name="L1243" href="source/net/ipv4/netfilter/ip_tables.c#L1243">1243</a>         <a href="ident?i=xt_table_unlock">xt_table_unlock</a>(<a href="ident?i=t">t</a>);
<a name="L1244" href="source/net/ipv4/netfilter/ip_tables.c#L1244">1244</a>  free_newinfo_counters_untrans:
<a name="L1245" href="source/net/ipv4/netfilter/ip_tables.c#L1245">1245</a>         <a href="ident?i=vfree">vfree</a>(counters);
<a name="L1246" href="source/net/ipv4/netfilter/ip_tables.c#L1246">1246</a>  <a href="ident?i=out">out</a>:
<a name="L1247" href="source/net/ipv4/netfilter/ip_tables.c#L1247">1247</a>         return <a href="ident?i=ret">ret</a>;
<a name="L1248" href="source/net/ipv4/netfilter/ip_tables.c#L1248">1248</a> }
<a name="L1249" href="source/net/ipv4/netfilter/ip_tables.c#L1249">1249</a> 
<a name="L1250" href="source/net/ipv4/netfilter/ip_tables.c#L1250">1250</a> static int
<a name="L1251" href="source/net/ipv4/netfilter/ip_tables.c#L1251">1251</a> <a href="ident?i=do_replace">do_replace</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>, const void <a href="ident?i=__user">__user</a> *<a href="ident?i=user">user</a>, unsigned int <a href="ident?i=len">len</a>)
<a name="L1252" href="source/net/ipv4/netfilter/ip_tables.c#L1252">1252</a> {
<a name="L1253" href="source/net/ipv4/netfilter/ip_tables.c#L1253">1253</a>         int <a href="ident?i=ret">ret</a>;
<a name="L1254" href="source/net/ipv4/netfilter/ip_tables.c#L1254">1254</a>         struct <a href="ident?i=ipt_replace">ipt_replace</a> <a href="ident?i=tmp">tmp</a>;
<a name="L1255" href="source/net/ipv4/netfilter/ip_tables.c#L1255">1255</a>         struct <a href="ident?i=xt_table_info">xt_table_info</a> *newinfo;
<a name="L1256" href="source/net/ipv4/netfilter/ip_tables.c#L1256">1256</a>         void *loc_cpu_entry;
<a name="L1257" href="source/net/ipv4/netfilter/ip_tables.c#L1257">1257</a>         struct <a href="ident?i=ipt_entry">ipt_entry</a> *iter;
<a name="L1258" href="source/net/ipv4/netfilter/ip_tables.c#L1258">1258</a> 
<a name="L1259" href="source/net/ipv4/netfilter/ip_tables.c#L1259">1259</a>         if (<a href="ident?i=copy_from_user">copy_from_user</a>(&amp;<a href="ident?i=tmp">tmp</a>, <a href="ident?i=user">user</a>, sizeof(<a href="ident?i=tmp">tmp</a>)) != 0)
<a name="L1260" href="source/net/ipv4/netfilter/ip_tables.c#L1260">1260</a>                 return -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L1261" href="source/net/ipv4/netfilter/ip_tables.c#L1261">1261</a> 
<a name="L1262" href="source/net/ipv4/netfilter/ip_tables.c#L1262">1262</a>         <b><i>/* overflow check */</i></b>
<a name="L1263" href="source/net/ipv4/netfilter/ip_tables.c#L1263">1263</a>         if (<a href="ident?i=tmp">tmp</a>.<a href="ident?i=num_counters">num_counters</a> &gt;= <a href="ident?i=INT_MAX">INT_MAX</a> / sizeof(struct <a href="ident?i=xt_counters">xt_counters</a>))
<a name="L1264" href="source/net/ipv4/netfilter/ip_tables.c#L1264">1264</a>                 return -<a href="ident?i=ENOMEM">ENOMEM</a>;
<a name="L1265" href="source/net/ipv4/netfilter/ip_tables.c#L1265">1265</a>         if (<a href="ident?i=tmp">tmp</a>.<a href="ident?i=num_counters">num_counters</a> == 0)
<a name="L1266" href="source/net/ipv4/netfilter/ip_tables.c#L1266">1266</a>                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L1267" href="source/net/ipv4/netfilter/ip_tables.c#L1267">1267</a> 
<a name="L1268" href="source/net/ipv4/netfilter/ip_tables.c#L1268">1268</a>         <a href="ident?i=tmp">tmp</a>.<a href="ident?i=name">name</a>[sizeof(<a href="ident?i=tmp">tmp</a>.<a href="ident?i=name">name</a>)-1] = 0;
<a name="L1269" href="source/net/ipv4/netfilter/ip_tables.c#L1269">1269</a> 
<a name="L1270" href="source/net/ipv4/netfilter/ip_tables.c#L1270">1270</a>         newinfo = <a href="ident?i=xt_alloc_table_info">xt_alloc_table_info</a>(<a href="ident?i=tmp">tmp</a>.<a href="ident?i=size">size</a>);
<a name="L1271" href="source/net/ipv4/netfilter/ip_tables.c#L1271">1271</a>         if (!newinfo)
<a name="L1272" href="source/net/ipv4/netfilter/ip_tables.c#L1272">1272</a>                 return -<a href="ident?i=ENOMEM">ENOMEM</a>;
<a name="L1273" href="source/net/ipv4/netfilter/ip_tables.c#L1273">1273</a> 
<a name="L1274" href="source/net/ipv4/netfilter/ip_tables.c#L1274">1274</a>         <b><i>/* choose the copy that is on our node/cpu */</i></b>
<a name="L1275" href="source/net/ipv4/netfilter/ip_tables.c#L1275">1275</a>         loc_cpu_entry = newinfo-&gt;<a href="ident?i=entries">entries</a>[<a href="ident?i=raw_smp_processor_id">raw_smp_processor_id</a>()];
<a name="L1276" href="source/net/ipv4/netfilter/ip_tables.c#L1276">1276</a>         if (<a href="ident?i=copy_from_user">copy_from_user</a>(loc_cpu_entry, <a href="ident?i=user">user</a> + sizeof(<a href="ident?i=tmp">tmp</a>),
<a name="L1277" href="source/net/ipv4/netfilter/ip_tables.c#L1277">1277</a>                            <a href="ident?i=tmp">tmp</a>.<a href="ident?i=size">size</a>) != 0) {
<a name="L1278" href="source/net/ipv4/netfilter/ip_tables.c#L1278">1278</a>                 <a href="ident?i=ret">ret</a> = -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L1279" href="source/net/ipv4/netfilter/ip_tables.c#L1279">1279</a>                 goto free_newinfo;
<a name="L1280" href="source/net/ipv4/netfilter/ip_tables.c#L1280">1280</a>         }
<a name="L1281" href="source/net/ipv4/netfilter/ip_tables.c#L1281">1281</a> 
<a name="L1282" href="source/net/ipv4/netfilter/ip_tables.c#L1282">1282</a>         <a href="ident?i=ret">ret</a> = <a href="ident?i=translate_table">translate_table</a>(<a href="ident?i=net">net</a>, newinfo, loc_cpu_entry, &amp;<a href="ident?i=tmp">tmp</a>);
<a name="L1283" href="source/net/ipv4/netfilter/ip_tables.c#L1283">1283</a>         if (<a href="ident?i=ret">ret</a> != 0)
<a name="L1284" href="source/net/ipv4/netfilter/ip_tables.c#L1284">1284</a>                 goto free_newinfo;
<a name="L1285" href="source/net/ipv4/netfilter/ip_tables.c#L1285">1285</a> 
<a name="L1286" href="source/net/ipv4/netfilter/ip_tables.c#L1286">1286</a>         <a href="ident?i=duprintf">duprintf</a>(<i>"Translated table\n"</i>);
<a name="L1287" href="source/net/ipv4/netfilter/ip_tables.c#L1287">1287</a> 
<a name="L1288" href="source/net/ipv4/netfilter/ip_tables.c#L1288">1288</a>         <a href="ident?i=ret">ret</a> = <a href="ident?i=__do_replace">__do_replace</a>(<a href="ident?i=net">net</a>, <a href="ident?i=tmp">tmp</a>.<a href="ident?i=name">name</a>, <a href="ident?i=tmp">tmp</a>.valid_hooks, newinfo,
<a name="L1289" href="source/net/ipv4/netfilter/ip_tables.c#L1289">1289</a>                            <a href="ident?i=tmp">tmp</a>.<a href="ident?i=num_counters">num_counters</a>, <a href="ident?i=tmp">tmp</a>.counters);
<a name="L1290" href="source/net/ipv4/netfilter/ip_tables.c#L1290">1290</a>         if (<a href="ident?i=ret">ret</a>)
<a name="L1291" href="source/net/ipv4/netfilter/ip_tables.c#L1291">1291</a>                 goto free_newinfo_untrans;
<a name="L1292" href="source/net/ipv4/netfilter/ip_tables.c#L1292">1292</a>         return 0;
<a name="L1293" href="source/net/ipv4/netfilter/ip_tables.c#L1293">1293</a> 
<a name="L1294" href="source/net/ipv4/netfilter/ip_tables.c#L1294">1294</a>  free_newinfo_untrans:
<a name="L1295" href="source/net/ipv4/netfilter/ip_tables.c#L1295">1295</a>         <a href="ident?i=xt_entry_foreach">xt_entry_foreach</a>(iter, loc_cpu_entry, newinfo-&gt;<a href="ident?i=size">size</a>)
<a name="L1296" href="source/net/ipv4/netfilter/ip_tables.c#L1296">1296</a>                 <a href="ident?i=cleanup_entry">cleanup_entry</a>(iter, <a href="ident?i=net">net</a>);
<a name="L1297" href="source/net/ipv4/netfilter/ip_tables.c#L1297">1297</a>  free_newinfo:
<a name="L1298" href="source/net/ipv4/netfilter/ip_tables.c#L1298">1298</a>         <a href="ident?i=xt_free_table_info">xt_free_table_info</a>(newinfo);
<a name="L1299" href="source/net/ipv4/netfilter/ip_tables.c#L1299">1299</a>         return <a href="ident?i=ret">ret</a>;
<a name="L1300" href="source/net/ipv4/netfilter/ip_tables.c#L1300">1300</a> }
<a name="L1301" href="source/net/ipv4/netfilter/ip_tables.c#L1301">1301</a> 
<a name="L1302" href="source/net/ipv4/netfilter/ip_tables.c#L1302">1302</a> static int
<a name="L1303" href="source/net/ipv4/netfilter/ip_tables.c#L1303">1303</a> <a href="ident?i=do_add_counters">do_add_counters</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>, const void <a href="ident?i=__user">__user</a> *<a href="ident?i=user">user</a>,
<a name="L1304" href="source/net/ipv4/netfilter/ip_tables.c#L1304">1304</a>                 unsigned int <a href="ident?i=len">len</a>, int <a href="ident?i=compat">compat</a>)
<a name="L1305" href="source/net/ipv4/netfilter/ip_tables.c#L1305">1305</a> {
<a name="L1306" href="source/net/ipv4/netfilter/ip_tables.c#L1306">1306</a>         unsigned int <a href="ident?i=i">i</a>, curcpu;
<a name="L1307" href="source/net/ipv4/netfilter/ip_tables.c#L1307">1307</a>         struct <a href="ident?i=xt_counters_info">xt_counters_info</a> <a href="ident?i=tmp">tmp</a>;
<a name="L1308" href="source/net/ipv4/netfilter/ip_tables.c#L1308">1308</a>         struct <a href="ident?i=xt_counters">xt_counters</a> *paddc;
<a name="L1309" href="source/net/ipv4/netfilter/ip_tables.c#L1309">1309</a>         unsigned int <a href="ident?i=num_counters">num_counters</a>;
<a name="L1310" href="source/net/ipv4/netfilter/ip_tables.c#L1310">1310</a>         const char *<a href="ident?i=name">name</a>;
<a name="L1311" href="source/net/ipv4/netfilter/ip_tables.c#L1311">1311</a>         int <a href="ident?i=size">size</a>;
<a name="L1312" href="source/net/ipv4/netfilter/ip_tables.c#L1312">1312</a>         void *ptmp;
<a name="L1313" href="source/net/ipv4/netfilter/ip_tables.c#L1313">1313</a>         struct <a href="ident?i=xt_table">xt_table</a> *<a href="ident?i=t">t</a>;
<a name="L1314" href="source/net/ipv4/netfilter/ip_tables.c#L1314">1314</a>         const struct <a href="ident?i=xt_table_info">xt_table_info</a> *<a href="ident?i=private">private</a>;
<a name="L1315" href="source/net/ipv4/netfilter/ip_tables.c#L1315">1315</a>         int <a href="ident?i=ret">ret</a> = 0;
<a name="L1316" href="source/net/ipv4/netfilter/ip_tables.c#L1316">1316</a>         void *loc_cpu_entry;
<a name="L1317" href="source/net/ipv4/netfilter/ip_tables.c#L1317">1317</a>         struct <a href="ident?i=ipt_entry">ipt_entry</a> *iter;
<a name="L1318" href="source/net/ipv4/netfilter/ip_tables.c#L1318">1318</a>         unsigned int addend;
<a name="L1319" href="source/net/ipv4/netfilter/ip_tables.c#L1319">1319</a> #ifdef CONFIG_COMPAT
<a name="L1320" href="source/net/ipv4/netfilter/ip_tables.c#L1320">1320</a>         struct <a href="ident?i=compat_xt_counters_info">compat_xt_counters_info</a> compat_tmp;
<a name="L1321" href="source/net/ipv4/netfilter/ip_tables.c#L1321">1321</a> 
<a name="L1322" href="source/net/ipv4/netfilter/ip_tables.c#L1322">1322</a>         if (<a href="ident?i=compat">compat</a>) {
<a name="L1323" href="source/net/ipv4/netfilter/ip_tables.c#L1323">1323</a>                 ptmp = &amp;compat_tmp;
<a name="L1324" href="source/net/ipv4/netfilter/ip_tables.c#L1324">1324</a>                 <a href="ident?i=size">size</a> = sizeof(struct <a href="ident?i=compat_xt_counters_info">compat_xt_counters_info</a>);
<a name="L1325" href="source/net/ipv4/netfilter/ip_tables.c#L1325">1325</a>         } else
<a name="L1326" href="source/net/ipv4/netfilter/ip_tables.c#L1326">1326</a> #endif
<a name="L1327" href="source/net/ipv4/netfilter/ip_tables.c#L1327">1327</a>         {
<a name="L1328" href="source/net/ipv4/netfilter/ip_tables.c#L1328">1328</a>                 ptmp = &amp;<a href="ident?i=tmp">tmp</a>;
<a name="L1329" href="source/net/ipv4/netfilter/ip_tables.c#L1329">1329</a>                 <a href="ident?i=size">size</a> = sizeof(struct <a href="ident?i=xt_counters_info">xt_counters_info</a>);
<a name="L1330" href="source/net/ipv4/netfilter/ip_tables.c#L1330">1330</a>         }
<a name="L1331" href="source/net/ipv4/netfilter/ip_tables.c#L1331">1331</a> 
<a name="L1332" href="source/net/ipv4/netfilter/ip_tables.c#L1332">1332</a>         if (<a href="ident?i=copy_from_user">copy_from_user</a>(ptmp, <a href="ident?i=user">user</a>, <a href="ident?i=size">size</a>) != 0)
<a name="L1333" href="source/net/ipv4/netfilter/ip_tables.c#L1333">1333</a>                 return -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L1334" href="source/net/ipv4/netfilter/ip_tables.c#L1334">1334</a> 
<a name="L1335" href="source/net/ipv4/netfilter/ip_tables.c#L1335">1335</a> #ifdef CONFIG_COMPAT
<a name="L1336" href="source/net/ipv4/netfilter/ip_tables.c#L1336">1336</a>         if (<a href="ident?i=compat">compat</a>) {
<a name="L1337" href="source/net/ipv4/netfilter/ip_tables.c#L1337">1337</a>                 <a href="ident?i=num_counters">num_counters</a> = compat_tmp.<a href="ident?i=num_counters">num_counters</a>;
<a name="L1338" href="source/net/ipv4/netfilter/ip_tables.c#L1338">1338</a>                 <a href="ident?i=name">name</a> = compat_tmp.<a href="ident?i=name">name</a>;
<a name="L1339" href="source/net/ipv4/netfilter/ip_tables.c#L1339">1339</a>         } else
<a name="L1340" href="source/net/ipv4/netfilter/ip_tables.c#L1340">1340</a> #endif
<a name="L1341" href="source/net/ipv4/netfilter/ip_tables.c#L1341">1341</a>         {
<a name="L1342" href="source/net/ipv4/netfilter/ip_tables.c#L1342">1342</a>                 <a href="ident?i=num_counters">num_counters</a> = <a href="ident?i=tmp">tmp</a>.<a href="ident?i=num_counters">num_counters</a>;
<a name="L1343" href="source/net/ipv4/netfilter/ip_tables.c#L1343">1343</a>                 <a href="ident?i=name">name</a> = <a href="ident?i=tmp">tmp</a>.<a href="ident?i=name">name</a>;
<a name="L1344" href="source/net/ipv4/netfilter/ip_tables.c#L1344">1344</a>         }
<a name="L1345" href="source/net/ipv4/netfilter/ip_tables.c#L1345">1345</a> 
<a name="L1346" href="source/net/ipv4/netfilter/ip_tables.c#L1346">1346</a>         if (<a href="ident?i=len">len</a> != <a href="ident?i=size">size</a> + <a href="ident?i=num_counters">num_counters</a> * sizeof(struct <a href="ident?i=xt_counters">xt_counters</a>))
<a name="L1347" href="source/net/ipv4/netfilter/ip_tables.c#L1347">1347</a>                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L1348" href="source/net/ipv4/netfilter/ip_tables.c#L1348">1348</a> 
<a name="L1349" href="source/net/ipv4/netfilter/ip_tables.c#L1349">1349</a>         paddc = <a href="ident?i=vmalloc">vmalloc</a>(<a href="ident?i=len">len</a> - <a href="ident?i=size">size</a>);
<a name="L1350" href="source/net/ipv4/netfilter/ip_tables.c#L1350">1350</a>         if (!paddc)
<a name="L1351" href="source/net/ipv4/netfilter/ip_tables.c#L1351">1351</a>                 return -<a href="ident?i=ENOMEM">ENOMEM</a>;
<a name="L1352" href="source/net/ipv4/netfilter/ip_tables.c#L1352">1352</a> 
<a name="L1353" href="source/net/ipv4/netfilter/ip_tables.c#L1353">1353</a>         if (<a href="ident?i=copy_from_user">copy_from_user</a>(paddc, <a href="ident?i=user">user</a> + <a href="ident?i=size">size</a>, <a href="ident?i=len">len</a> - <a href="ident?i=size">size</a>) != 0) {
<a name="L1354" href="source/net/ipv4/netfilter/ip_tables.c#L1354">1354</a>                 <a href="ident?i=ret">ret</a> = -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L1355" href="source/net/ipv4/netfilter/ip_tables.c#L1355">1355</a>                 goto <a href="ident?i=free">free</a>;
<a name="L1356" href="source/net/ipv4/netfilter/ip_tables.c#L1356">1356</a>         }
<a name="L1357" href="source/net/ipv4/netfilter/ip_tables.c#L1357">1357</a> 
<a name="L1358" href="source/net/ipv4/netfilter/ip_tables.c#L1358">1358</a>         <a href="ident?i=t">t</a> = <a href="ident?i=xt_find_table_lock">xt_find_table_lock</a>(<a href="ident?i=net">net</a>, <a href="ident?i=AF_INET">AF_INET</a>, <a href="ident?i=name">name</a>);
<a name="L1359" href="source/net/ipv4/netfilter/ip_tables.c#L1359">1359</a>         if (<a href="ident?i=IS_ERR_OR_NULL">IS_ERR_OR_NULL</a>(<a href="ident?i=t">t</a>)) {
<a name="L1360" href="source/net/ipv4/netfilter/ip_tables.c#L1360">1360</a>                 <a href="ident?i=ret">ret</a> = <a href="ident?i=t">t</a> ? <a href="ident?i=PTR_ERR">PTR_ERR</a>(<a href="ident?i=t">t</a>) : -<a href="ident?i=ENOENT">ENOENT</a>;
<a name="L1361" href="source/net/ipv4/netfilter/ip_tables.c#L1361">1361</a>                 goto <a href="ident?i=free">free</a>;
<a name="L1362" href="source/net/ipv4/netfilter/ip_tables.c#L1362">1362</a>         }
<a name="L1363" href="source/net/ipv4/netfilter/ip_tables.c#L1363">1363</a> 
<a name="L1364" href="source/net/ipv4/netfilter/ip_tables.c#L1364">1364</a>         <a href="ident?i=local_bh_disable">local_bh_disable</a>();
<a name="L1365" href="source/net/ipv4/netfilter/ip_tables.c#L1365">1365</a>         <a href="ident?i=private">private</a> = <a href="ident?i=t">t</a>-&gt;<a href="ident?i=private">private</a>;
<a name="L1366" href="source/net/ipv4/netfilter/ip_tables.c#L1366">1366</a>         if (<a href="ident?i=private">private</a>-&gt;<a href="ident?i=number">number</a> != <a href="ident?i=num_counters">num_counters</a>) {
<a name="L1367" href="source/net/ipv4/netfilter/ip_tables.c#L1367">1367</a>                 <a href="ident?i=ret">ret</a> = -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L1368" href="source/net/ipv4/netfilter/ip_tables.c#L1368">1368</a>                 goto unlock_up_free;
<a name="L1369" href="source/net/ipv4/netfilter/ip_tables.c#L1369">1369</a>         }
<a name="L1370" href="source/net/ipv4/netfilter/ip_tables.c#L1370">1370</a> 
<a name="L1371" href="source/net/ipv4/netfilter/ip_tables.c#L1371">1371</a>         <a href="ident?i=i">i</a> = 0;
<a name="L1372" href="source/net/ipv4/netfilter/ip_tables.c#L1372">1372</a>         <b><i>/* Choose the copy that is on our node */</i></b>
<a name="L1373" href="source/net/ipv4/netfilter/ip_tables.c#L1373">1373</a>         curcpu = <a href="ident?i=smp_processor_id">smp_processor_id</a>();
<a name="L1374" href="source/net/ipv4/netfilter/ip_tables.c#L1374">1374</a>         loc_cpu_entry = <a href="ident?i=private">private</a>-&gt;<a href="ident?i=entries">entries</a>[curcpu];
<a name="L1375" href="source/net/ipv4/netfilter/ip_tables.c#L1375">1375</a>         addend = <a href="ident?i=xt_write_recseq_begin">xt_write_recseq_begin</a>();
<a name="L1376" href="source/net/ipv4/netfilter/ip_tables.c#L1376">1376</a>         <a href="ident?i=xt_entry_foreach">xt_entry_foreach</a>(iter, loc_cpu_entry, <a href="ident?i=private">private</a>-&gt;<a href="ident?i=size">size</a>) {
<a name="L1377" href="source/net/ipv4/netfilter/ip_tables.c#L1377">1377</a>                 <a href="ident?i=ADD_COUNTER">ADD_COUNTER</a>(iter-&gt;counters, paddc[<a href="ident?i=i">i</a>].bcnt, paddc[<a href="ident?i=i">i</a>].pcnt);
<a name="L1378" href="source/net/ipv4/netfilter/ip_tables.c#L1378">1378</a>                 ++<a href="ident?i=i">i</a>;
<a name="L1379" href="source/net/ipv4/netfilter/ip_tables.c#L1379">1379</a>         }
<a name="L1380" href="source/net/ipv4/netfilter/ip_tables.c#L1380">1380</a>         <a href="ident?i=xt_write_recseq_end">xt_write_recseq_end</a>(addend);
<a name="L1381" href="source/net/ipv4/netfilter/ip_tables.c#L1381">1381</a>  unlock_up_free:
<a name="L1382" href="source/net/ipv4/netfilter/ip_tables.c#L1382">1382</a>         <a href="ident?i=local_bh_enable">local_bh_enable</a>();
<a name="L1383" href="source/net/ipv4/netfilter/ip_tables.c#L1383">1383</a>         <a href="ident?i=xt_table_unlock">xt_table_unlock</a>(<a href="ident?i=t">t</a>);
<a name="L1384" href="source/net/ipv4/netfilter/ip_tables.c#L1384">1384</a>         <a href="ident?i=module_put">module_put</a>(<a href="ident?i=t">t</a>-&gt;<a href="ident?i=me">me</a>);
<a name="L1385" href="source/net/ipv4/netfilter/ip_tables.c#L1385">1385</a>  <a href="ident?i=free">free</a>:
<a name="L1386" href="source/net/ipv4/netfilter/ip_tables.c#L1386">1386</a>         <a href="ident?i=vfree">vfree</a>(paddc);
<a name="L1387" href="source/net/ipv4/netfilter/ip_tables.c#L1387">1387</a> 
<a name="L1388" href="source/net/ipv4/netfilter/ip_tables.c#L1388">1388</a>         return <a href="ident?i=ret">ret</a>;
<a name="L1389" href="source/net/ipv4/netfilter/ip_tables.c#L1389">1389</a> }
<a name="L1390" href="source/net/ipv4/netfilter/ip_tables.c#L1390">1390</a> 
<a name="L1391" href="source/net/ipv4/netfilter/ip_tables.c#L1391">1391</a> #ifdef CONFIG_COMPAT
<a name="L1392" href="source/net/ipv4/netfilter/ip_tables.c#L1392">1392</a> struct <a href="ident?i=compat_ipt_replace">compat_ipt_replace</a> {
<a name="L1393" href="source/net/ipv4/netfilter/ip_tables.c#L1393">1393</a>         char                    <a href="ident?i=name">name</a>[<a href="ident?i=XT_TABLE_MAXNAMELEN">XT_TABLE_MAXNAMELEN</a>];
<a name="L1394" href="source/net/ipv4/netfilter/ip_tables.c#L1394">1394</a>         <a href="ident?i=u32">u32</a>                     valid_hooks;
<a name="L1395" href="source/net/ipv4/netfilter/ip_tables.c#L1395">1395</a>         <a href="ident?i=u32">u32</a>                     <a href="ident?i=num_entries">num_entries</a>;
<a name="L1396" href="source/net/ipv4/netfilter/ip_tables.c#L1396">1396</a>         <a href="ident?i=u32">u32</a>                     <a href="ident?i=size">size</a>;
<a name="L1397" href="source/net/ipv4/netfilter/ip_tables.c#L1397">1397</a>         <a href="ident?i=u32">u32</a>                     hook_entry[NF_INET_NUMHOOKS];
<a name="L1398" href="source/net/ipv4/netfilter/ip_tables.c#L1398">1398</a>         <a href="ident?i=u32">u32</a>                     underflow[NF_INET_NUMHOOKS];
<a name="L1399" href="source/net/ipv4/netfilter/ip_tables.c#L1399">1399</a>         <a href="ident?i=u32">u32</a>                     <a href="ident?i=num_counters">num_counters</a>;
<a name="L1400" href="source/net/ipv4/netfilter/ip_tables.c#L1400">1400</a>         <a href="ident?i=compat_uptr_t">compat_uptr_t</a>           counters;       <b><i>/* struct xt_counters * */</i></b>
<a name="L1401" href="source/net/ipv4/netfilter/ip_tables.c#L1401">1401</a>         struct <a href="ident?i=compat_ipt_entry">compat_ipt_entry</a> <a href="ident?i=entries">entries</a>[0];
<a name="L1402" href="source/net/ipv4/netfilter/ip_tables.c#L1402">1402</a> };
<a name="L1403" href="source/net/ipv4/netfilter/ip_tables.c#L1403">1403</a> 
<a name="L1404" href="source/net/ipv4/netfilter/ip_tables.c#L1404">1404</a> static int
<a name="L1405" href="source/net/ipv4/netfilter/ip_tables.c#L1405">1405</a> <a href="ident?i=compat_copy_entry_to_user">compat_copy_entry_to_user</a>(struct <a href="ident?i=ipt_entry">ipt_entry</a> *<a href="ident?i=e">e</a>, void <a href="ident?i=__user">__user</a> **<a href="ident?i=dstptr">dstptr</a>,
<a name="L1406" href="source/net/ipv4/netfilter/ip_tables.c#L1406">1406</a>                           unsigned int *<a href="ident?i=size">size</a>, struct <a href="ident?i=xt_counters">xt_counters</a> *counters,
<a name="L1407" href="source/net/ipv4/netfilter/ip_tables.c#L1407">1407</a>                           unsigned int <a href="ident?i=i">i</a>)
<a name="L1408" href="source/net/ipv4/netfilter/ip_tables.c#L1408">1408</a> {
<a name="L1409" href="source/net/ipv4/netfilter/ip_tables.c#L1409">1409</a>         struct <a href="ident?i=xt_entry_target">xt_entry_target</a> *<a href="ident?i=t">t</a>;
<a name="L1410" href="source/net/ipv4/netfilter/ip_tables.c#L1410">1410</a>         struct <a href="ident?i=compat_ipt_entry">compat_ipt_entry</a> <a href="ident?i=__user">__user</a> *ce;
<a name="L1411" href="source/net/ipv4/netfilter/ip_tables.c#L1411">1411</a>         <a href="ident?i=u_int16_t">u_int16_t</a> target_offset, next_offset;
<a name="L1412" href="source/net/ipv4/netfilter/ip_tables.c#L1412">1412</a>         <a href="ident?i=compat_uint_t">compat_uint_t</a> origsize;
<a name="L1413" href="source/net/ipv4/netfilter/ip_tables.c#L1413">1413</a>         const struct <a href="ident?i=xt_entry_match">xt_entry_match</a> *ematch;
<a name="L1414" href="source/net/ipv4/netfilter/ip_tables.c#L1414">1414</a>         int <a href="ident?i=ret">ret</a> = 0;
<a name="L1415" href="source/net/ipv4/netfilter/ip_tables.c#L1415">1415</a> 
<a name="L1416" href="source/net/ipv4/netfilter/ip_tables.c#L1416">1416</a>         origsize = *<a href="ident?i=size">size</a>;
<a name="L1417" href="source/net/ipv4/netfilter/ip_tables.c#L1417">1417</a>         ce = (struct <a href="ident?i=compat_ipt_entry">compat_ipt_entry</a> <a href="ident?i=__user">__user</a> *)*<a href="ident?i=dstptr">dstptr</a>;
<a name="L1418" href="source/net/ipv4/netfilter/ip_tables.c#L1418">1418</a>         if (<a href="ident?i=copy_to_user">copy_to_user</a>(ce, <a href="ident?i=e">e</a>, sizeof(struct <a href="ident?i=ipt_entry">ipt_entry</a>)) != 0 ||
<a name="L1419" href="source/net/ipv4/netfilter/ip_tables.c#L1419">1419</a>             <a href="ident?i=copy_to_user">copy_to_user</a>(&amp;ce-&gt;counters, &amp;counters[<a href="ident?i=i">i</a>],
<a name="L1420" href="source/net/ipv4/netfilter/ip_tables.c#L1420">1420</a>             sizeof(counters[<a href="ident?i=i">i</a>])) != 0)
<a name="L1421" href="source/net/ipv4/netfilter/ip_tables.c#L1421">1421</a>                 return -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L1422" href="source/net/ipv4/netfilter/ip_tables.c#L1422">1422</a> 
<a name="L1423" href="source/net/ipv4/netfilter/ip_tables.c#L1423">1423</a>         *<a href="ident?i=dstptr">dstptr</a> += sizeof(struct <a href="ident?i=compat_ipt_entry">compat_ipt_entry</a>);
<a name="L1424" href="source/net/ipv4/netfilter/ip_tables.c#L1424">1424</a>         *<a href="ident?i=size">size</a> -= sizeof(struct <a href="ident?i=ipt_entry">ipt_entry</a>) - sizeof(struct <a href="ident?i=compat_ipt_entry">compat_ipt_entry</a>);
<a name="L1425" href="source/net/ipv4/netfilter/ip_tables.c#L1425">1425</a> 
<a name="L1426" href="source/net/ipv4/netfilter/ip_tables.c#L1426">1426</a>         <a href="ident?i=xt_ematch_foreach">xt_ematch_foreach</a>(ematch, <a href="ident?i=e">e</a>) {
<a name="L1427" href="source/net/ipv4/netfilter/ip_tables.c#L1427">1427</a>                 <a href="ident?i=ret">ret</a> = <a href="ident?i=xt_compat_match_to_user">xt_compat_match_to_user</a>(ematch, <a href="ident?i=dstptr">dstptr</a>, <a href="ident?i=size">size</a>);
<a name="L1428" href="source/net/ipv4/netfilter/ip_tables.c#L1428">1428</a>                 if (<a href="ident?i=ret">ret</a> != 0)
<a name="L1429" href="source/net/ipv4/netfilter/ip_tables.c#L1429">1429</a>                         return <a href="ident?i=ret">ret</a>;
<a name="L1430" href="source/net/ipv4/netfilter/ip_tables.c#L1430">1430</a>         }
<a name="L1431" href="source/net/ipv4/netfilter/ip_tables.c#L1431">1431</a>         target_offset = <a href="ident?i=e">e</a>-&gt;target_offset - (origsize - *<a href="ident?i=size">size</a>);
<a name="L1432" href="source/net/ipv4/netfilter/ip_tables.c#L1432">1432</a>         <a href="ident?i=t">t</a> = <a href="ident?i=ipt_get_target">ipt_get_target</a>(<a href="ident?i=e">e</a>);
<a name="L1433" href="source/net/ipv4/netfilter/ip_tables.c#L1433">1433</a>         <a href="ident?i=ret">ret</a> = <a href="ident?i=xt_compat_target_to_user">xt_compat_target_to_user</a>(<a href="ident?i=t">t</a>, <a href="ident?i=dstptr">dstptr</a>, <a href="ident?i=size">size</a>);
<a name="L1434" href="source/net/ipv4/netfilter/ip_tables.c#L1434">1434</a>         if (<a href="ident?i=ret">ret</a>)
<a name="L1435" href="source/net/ipv4/netfilter/ip_tables.c#L1435">1435</a>                 return <a href="ident?i=ret">ret</a>;
<a name="L1436" href="source/net/ipv4/netfilter/ip_tables.c#L1436">1436</a>         next_offset = <a href="ident?i=e">e</a>-&gt;next_offset - (origsize - *<a href="ident?i=size">size</a>);
<a name="L1437" href="source/net/ipv4/netfilter/ip_tables.c#L1437">1437</a>         if (<a href="ident?i=put_user">put_user</a>(target_offset, &amp;ce-&gt;target_offset) != 0 ||
<a name="L1438" href="source/net/ipv4/netfilter/ip_tables.c#L1438">1438</a>             <a href="ident?i=put_user">put_user</a>(next_offset, &amp;ce-&gt;next_offset) != 0)
<a name="L1439" href="source/net/ipv4/netfilter/ip_tables.c#L1439">1439</a>                 return -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L1440" href="source/net/ipv4/netfilter/ip_tables.c#L1440">1440</a>         return 0;
<a name="L1441" href="source/net/ipv4/netfilter/ip_tables.c#L1441">1441</a> }
<a name="L1442" href="source/net/ipv4/netfilter/ip_tables.c#L1442">1442</a> 
<a name="L1443" href="source/net/ipv4/netfilter/ip_tables.c#L1443">1443</a> static int
<a name="L1444" href="source/net/ipv4/netfilter/ip_tables.c#L1444">1444</a> <a href="ident?i=compat_find_calc_match">compat_find_calc_match</a>(struct <a href="ident?i=xt_entry_match">xt_entry_match</a> *<a href="ident?i=m">m</a>,
<a name="L1445" href="source/net/ipv4/netfilter/ip_tables.c#L1445">1445</a>                        const char *<a href="ident?i=name">name</a>,
<a name="L1446" href="source/net/ipv4/netfilter/ip_tables.c#L1446">1446</a>                        const struct <a href="ident?i=ipt_ip">ipt_ip</a> *<a href="ident?i=ip">ip</a>,
<a name="L1447" href="source/net/ipv4/netfilter/ip_tables.c#L1447">1447</a>                        unsigned int hookmask,
<a name="L1448" href="source/net/ipv4/netfilter/ip_tables.c#L1448">1448</a>                        int *<a href="ident?i=size">size</a>)
<a name="L1449" href="source/net/ipv4/netfilter/ip_tables.c#L1449">1449</a> {
<a name="L1450" href="source/net/ipv4/netfilter/ip_tables.c#L1450">1450</a>         struct <a href="ident?i=xt_match">xt_match</a> *<a href="ident?i=match">match</a>;
<a name="L1451" href="source/net/ipv4/netfilter/ip_tables.c#L1451">1451</a> 
<a name="L1452" href="source/net/ipv4/netfilter/ip_tables.c#L1452">1452</a>         <a href="ident?i=match">match</a> = <a href="ident?i=xt_request_find_match">xt_request_find_match</a>(NFPROTO_IPV4, <a href="ident?i=m">m</a>-&gt;u.<a href="ident?i=user">user</a>.<a href="ident?i=name">name</a>,
<a name="L1453" href="source/net/ipv4/netfilter/ip_tables.c#L1453">1453</a>                                       <a href="ident?i=m">m</a>-&gt;u.<a href="ident?i=user">user</a>.<a href="ident?i=revision">revision</a>);
<a name="L1454" href="source/net/ipv4/netfilter/ip_tables.c#L1454">1454</a>         if (<a href="ident?i=IS_ERR">IS_ERR</a>(<a href="ident?i=match">match</a>)) {
<a name="L1455" href="source/net/ipv4/netfilter/ip_tables.c#L1455">1455</a>                 <a href="ident?i=duprintf">duprintf</a>(<i>"compat_check_calc_match: `%s' not found\n"</i>,
<a name="L1456" href="source/net/ipv4/netfilter/ip_tables.c#L1456">1456</a>                          <a href="ident?i=m">m</a>-&gt;u.<a href="ident?i=user">user</a>.<a href="ident?i=name">name</a>);
<a name="L1457" href="source/net/ipv4/netfilter/ip_tables.c#L1457">1457</a>                 return <a href="ident?i=PTR_ERR">PTR_ERR</a>(<a href="ident?i=match">match</a>);
<a name="L1458" href="source/net/ipv4/netfilter/ip_tables.c#L1458">1458</a>         }
<a name="L1459" href="source/net/ipv4/netfilter/ip_tables.c#L1459">1459</a>         <a href="ident?i=m">m</a>-&gt;u.kernel.<a href="ident?i=match">match</a> = <a href="ident?i=match">match</a>;
<a name="L1460" href="source/net/ipv4/netfilter/ip_tables.c#L1460">1460</a>         *<a href="ident?i=size">size</a> += <a href="ident?i=xt_compat_match_offset">xt_compat_match_offset</a>(<a href="ident?i=match">match</a>);
<a name="L1461" href="source/net/ipv4/netfilter/ip_tables.c#L1461">1461</a>         return 0;
<a name="L1462" href="source/net/ipv4/netfilter/ip_tables.c#L1462">1462</a> }
<a name="L1463" href="source/net/ipv4/netfilter/ip_tables.c#L1463">1463</a> 
<a name="L1464" href="source/net/ipv4/netfilter/ip_tables.c#L1464">1464</a> static void <a href="ident?i=compat_release_entry">compat_release_entry</a>(struct <a href="ident?i=compat_ipt_entry">compat_ipt_entry</a> *<a href="ident?i=e">e</a>)
<a name="L1465" href="source/net/ipv4/netfilter/ip_tables.c#L1465">1465</a> {
<a name="L1466" href="source/net/ipv4/netfilter/ip_tables.c#L1466">1466</a>         struct <a href="ident?i=xt_entry_target">xt_entry_target</a> *<a href="ident?i=t">t</a>;
<a name="L1467" href="source/net/ipv4/netfilter/ip_tables.c#L1467">1467</a>         struct <a href="ident?i=xt_entry_match">xt_entry_match</a> *ematch;
<a name="L1468" href="source/net/ipv4/netfilter/ip_tables.c#L1468">1468</a> 
<a name="L1469" href="source/net/ipv4/netfilter/ip_tables.c#L1469">1469</a>         <b><i>/* Cleanup all matches */</i></b>
<a name="L1470" href="source/net/ipv4/netfilter/ip_tables.c#L1470">1470</a>         <a href="ident?i=xt_ematch_foreach">xt_ematch_foreach</a>(ematch, <a href="ident?i=e">e</a>)
<a name="L1471" href="source/net/ipv4/netfilter/ip_tables.c#L1471">1471</a>                 <a href="ident?i=module_put">module_put</a>(ematch-&gt;u.kernel.<a href="ident?i=match">match</a>-&gt;<a href="ident?i=me">me</a>);
<a name="L1472" href="source/net/ipv4/netfilter/ip_tables.c#L1472">1472</a>         <a href="ident?i=t">t</a> = <a href="ident?i=compat_ipt_get_target">compat_ipt_get_target</a>(<a href="ident?i=e">e</a>);
<a name="L1473" href="source/net/ipv4/netfilter/ip_tables.c#L1473">1473</a>         <a href="ident?i=module_put">module_put</a>(<a href="ident?i=t">t</a>-&gt;u.kernel.<a href="ident?i=target">target</a>-&gt;<a href="ident?i=me">me</a>);
<a name="L1474" href="source/net/ipv4/netfilter/ip_tables.c#L1474">1474</a> }
<a name="L1475" href="source/net/ipv4/netfilter/ip_tables.c#L1475">1475</a> 
<a name="L1476" href="source/net/ipv4/netfilter/ip_tables.c#L1476">1476</a> static int
<a name="L1477" href="source/net/ipv4/netfilter/ip_tables.c#L1477">1477</a> <a href="ident?i=check_compat_entry_size_and_hooks">check_compat_entry_size_and_hooks</a>(struct <a href="ident?i=compat_ipt_entry">compat_ipt_entry</a> *<a href="ident?i=e">e</a>,
<a name="L1478" href="source/net/ipv4/netfilter/ip_tables.c#L1478">1478</a>                                   struct <a href="ident?i=xt_table_info">xt_table_info</a> *newinfo,
<a name="L1479" href="source/net/ipv4/netfilter/ip_tables.c#L1479">1479</a>                                   unsigned int *<a href="ident?i=size">size</a>,
<a name="L1480" href="source/net/ipv4/netfilter/ip_tables.c#L1480">1480</a>                                   const unsigned char *<a href="ident?i=base">base</a>,
<a name="L1481" href="source/net/ipv4/netfilter/ip_tables.c#L1481">1481</a>                                   const unsigned char *<a href="ident?i=limit">limit</a>,
<a name="L1482" href="source/net/ipv4/netfilter/ip_tables.c#L1482">1482</a>                                   const unsigned int *hook_entries,
<a name="L1483" href="source/net/ipv4/netfilter/ip_tables.c#L1483">1483</a>                                   const unsigned int *underflows,
<a name="L1484" href="source/net/ipv4/netfilter/ip_tables.c#L1484">1484</a>                                   const char *<a href="ident?i=name">name</a>)
<a name="L1485" href="source/net/ipv4/netfilter/ip_tables.c#L1485">1485</a> {
<a name="L1486" href="source/net/ipv4/netfilter/ip_tables.c#L1486">1486</a>         struct <a href="ident?i=xt_entry_match">xt_entry_match</a> *ematch;
<a name="L1487" href="source/net/ipv4/netfilter/ip_tables.c#L1487">1487</a>         struct <a href="ident?i=xt_entry_target">xt_entry_target</a> *<a href="ident?i=t">t</a>;
<a name="L1488" href="source/net/ipv4/netfilter/ip_tables.c#L1488">1488</a>         struct <a href="ident?i=xt_target">xt_target</a> *<a href="ident?i=target">target</a>;
<a name="L1489" href="source/net/ipv4/netfilter/ip_tables.c#L1489">1489</a>         unsigned int entry_offset;
<a name="L1490" href="source/net/ipv4/netfilter/ip_tables.c#L1490">1490</a>         unsigned int j;
<a name="L1491" href="source/net/ipv4/netfilter/ip_tables.c#L1491">1491</a>         int <a href="ident?i=ret">ret</a>, <a href="ident?i=off">off</a>, <a href="ident?i=h">h</a>;
<a name="L1492" href="source/net/ipv4/netfilter/ip_tables.c#L1492">1492</a> 
<a name="L1493" href="source/net/ipv4/netfilter/ip_tables.c#L1493">1493</a>         <a href="ident?i=duprintf">duprintf</a>(<i>"check_compat_entry_size_and_hooks %p\n"</i>, <a href="ident?i=e">e</a>);
<a name="L1494" href="source/net/ipv4/netfilter/ip_tables.c#L1494">1494</a>         if ((unsigned long)<a href="ident?i=e">e</a> % __alignof__(struct <a href="ident?i=compat_ipt_entry">compat_ipt_entry</a>) != 0 ||
<a name="L1495" href="source/net/ipv4/netfilter/ip_tables.c#L1495">1495</a>             (unsigned char *)<a href="ident?i=e">e</a> + sizeof(struct <a href="ident?i=compat_ipt_entry">compat_ipt_entry</a>) &gt;= <a href="ident?i=limit">limit</a>) {
<a name="L1496" href="source/net/ipv4/netfilter/ip_tables.c#L1496">1496</a>                 <a href="ident?i=duprintf">duprintf</a>(<i>"Bad offset %p, limit = %p\n"</i>, <a href="ident?i=e">e</a>, <a href="ident?i=limit">limit</a>);
<a name="L1497" href="source/net/ipv4/netfilter/ip_tables.c#L1497">1497</a>                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L1498" href="source/net/ipv4/netfilter/ip_tables.c#L1498">1498</a>         }
<a name="L1499" href="source/net/ipv4/netfilter/ip_tables.c#L1499">1499</a> 
<a name="L1500" href="source/net/ipv4/netfilter/ip_tables.c#L1500">1500</a>         if (<a href="ident?i=e">e</a>-&gt;next_offset &lt; sizeof(struct <a href="ident?i=compat_ipt_entry">compat_ipt_entry</a>) +
<a name="L1501" href="source/net/ipv4/netfilter/ip_tables.c#L1501">1501</a>                              sizeof(struct <a href="ident?i=compat_xt_entry_target">compat_xt_entry_target</a>)) {
<a name="L1502" href="source/net/ipv4/netfilter/ip_tables.c#L1502">1502</a>                 <a href="ident?i=duprintf">duprintf</a>(<i>"checking: element %p size %u\n"</i>,
<a name="L1503" href="source/net/ipv4/netfilter/ip_tables.c#L1503">1503</a>                          <a href="ident?i=e">e</a>, <a href="ident?i=e">e</a>-&gt;next_offset);
<a name="L1504" href="source/net/ipv4/netfilter/ip_tables.c#L1504">1504</a>                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L1505" href="source/net/ipv4/netfilter/ip_tables.c#L1505">1505</a>         }
<a name="L1506" href="source/net/ipv4/netfilter/ip_tables.c#L1506">1506</a> 
<a name="L1507" href="source/net/ipv4/netfilter/ip_tables.c#L1507">1507</a>         <b><i>/* For purposes of check_entry casting the compat entry is fine */</i></b>
<a name="L1508" href="source/net/ipv4/netfilter/ip_tables.c#L1508">1508</a>         <a href="ident?i=ret">ret</a> = <a href="ident?i=check_entry">check_entry</a>((struct <a href="ident?i=ipt_entry">ipt_entry</a> *)<a href="ident?i=e">e</a>, <a href="ident?i=name">name</a>);
<a name="L1509" href="source/net/ipv4/netfilter/ip_tables.c#L1509">1509</a>         if (<a href="ident?i=ret">ret</a>)
<a name="L1510" href="source/net/ipv4/netfilter/ip_tables.c#L1510">1510</a>                 return <a href="ident?i=ret">ret</a>;
<a name="L1511" href="source/net/ipv4/netfilter/ip_tables.c#L1511">1511</a> 
<a name="L1512" href="source/net/ipv4/netfilter/ip_tables.c#L1512">1512</a>         <a href="ident?i=off">off</a> = sizeof(struct <a href="ident?i=ipt_entry">ipt_entry</a>) - sizeof(struct <a href="ident?i=compat_ipt_entry">compat_ipt_entry</a>);
<a name="L1513" href="source/net/ipv4/netfilter/ip_tables.c#L1513">1513</a>         entry_offset = (void *)<a href="ident?i=e">e</a> - (void *)<a href="ident?i=base">base</a>;
<a name="L1514" href="source/net/ipv4/netfilter/ip_tables.c#L1514">1514</a>         j = 0;
<a name="L1515" href="source/net/ipv4/netfilter/ip_tables.c#L1515">1515</a>         <a href="ident?i=xt_ematch_foreach">xt_ematch_foreach</a>(ematch, <a href="ident?i=e">e</a>) {
<a name="L1516" href="source/net/ipv4/netfilter/ip_tables.c#L1516">1516</a>                 <a href="ident?i=ret">ret</a> = <a href="ident?i=compat_find_calc_match">compat_find_calc_match</a>(ematch, <a href="ident?i=name">name</a>,
<a name="L1517" href="source/net/ipv4/netfilter/ip_tables.c#L1517">1517</a>                                              &amp;<a href="ident?i=e">e</a>-&gt;<a href="ident?i=ip">ip</a>, <a href="ident?i=e">e</a>-&gt;comefrom, &amp;<a href="ident?i=off">off</a>);
<a name="L1518" href="source/net/ipv4/netfilter/ip_tables.c#L1518">1518</a>                 if (<a href="ident?i=ret">ret</a> != 0)
<a name="L1519" href="source/net/ipv4/netfilter/ip_tables.c#L1519">1519</a>                         goto release_matches;
<a name="L1520" href="source/net/ipv4/netfilter/ip_tables.c#L1520">1520</a>                 ++j;
<a name="L1521" href="source/net/ipv4/netfilter/ip_tables.c#L1521">1521</a>         }
<a name="L1522" href="source/net/ipv4/netfilter/ip_tables.c#L1522">1522</a> 
<a name="L1523" href="source/net/ipv4/netfilter/ip_tables.c#L1523">1523</a>         <a href="ident?i=t">t</a> = <a href="ident?i=compat_ipt_get_target">compat_ipt_get_target</a>(<a href="ident?i=e">e</a>);
<a name="L1524" href="source/net/ipv4/netfilter/ip_tables.c#L1524">1524</a>         <a href="ident?i=target">target</a> = <a href="ident?i=xt_request_find_target">xt_request_find_target</a>(NFPROTO_IPV4, <a href="ident?i=t">t</a>-&gt;u.<a href="ident?i=user">user</a>.<a href="ident?i=name">name</a>,
<a name="L1525" href="source/net/ipv4/netfilter/ip_tables.c#L1525">1525</a>                                         <a href="ident?i=t">t</a>-&gt;u.<a href="ident?i=user">user</a>.<a href="ident?i=revision">revision</a>);
<a name="L1526" href="source/net/ipv4/netfilter/ip_tables.c#L1526">1526</a>         if (<a href="ident?i=IS_ERR">IS_ERR</a>(<a href="ident?i=target">target</a>)) {
<a name="L1527" href="source/net/ipv4/netfilter/ip_tables.c#L1527">1527</a>                 <a href="ident?i=duprintf">duprintf</a>(<i>"check_compat_entry_size_and_hooks: `%s' not found\n"</i>,
<a name="L1528" href="source/net/ipv4/netfilter/ip_tables.c#L1528">1528</a>                          <a href="ident?i=t">t</a>-&gt;u.<a href="ident?i=user">user</a>.<a href="ident?i=name">name</a>);
<a name="L1529" href="source/net/ipv4/netfilter/ip_tables.c#L1529">1529</a>                 <a href="ident?i=ret">ret</a> = <a href="ident?i=PTR_ERR">PTR_ERR</a>(<a href="ident?i=target">target</a>);
<a name="L1530" href="source/net/ipv4/netfilter/ip_tables.c#L1530">1530</a>                 goto release_matches;
<a name="L1531" href="source/net/ipv4/netfilter/ip_tables.c#L1531">1531</a>         }
<a name="L1532" href="source/net/ipv4/netfilter/ip_tables.c#L1532">1532</a>         <a href="ident?i=t">t</a>-&gt;u.kernel.<a href="ident?i=target">target</a> = <a href="ident?i=target">target</a>;
<a name="L1533" href="source/net/ipv4/netfilter/ip_tables.c#L1533">1533</a> 
<a name="L1534" href="source/net/ipv4/netfilter/ip_tables.c#L1534">1534</a>         <a href="ident?i=off">off</a> += <a href="ident?i=xt_compat_target_offset">xt_compat_target_offset</a>(<a href="ident?i=target">target</a>);
<a name="L1535" href="source/net/ipv4/netfilter/ip_tables.c#L1535">1535</a>         *<a href="ident?i=size">size</a> += <a href="ident?i=off">off</a>;
<a name="L1536" href="source/net/ipv4/netfilter/ip_tables.c#L1536">1536</a>         <a href="ident?i=ret">ret</a> = <a href="ident?i=xt_compat_add_offset">xt_compat_add_offset</a>(<a href="ident?i=AF_INET">AF_INET</a>, entry_offset, <a href="ident?i=off">off</a>);
<a name="L1537" href="source/net/ipv4/netfilter/ip_tables.c#L1537">1537</a>         if (<a href="ident?i=ret">ret</a>)
<a name="L1538" href="source/net/ipv4/netfilter/ip_tables.c#L1538">1538</a>                 goto <a href="ident?i=out">out</a>;
<a name="L1539" href="source/net/ipv4/netfilter/ip_tables.c#L1539">1539</a> 
<a name="L1540" href="source/net/ipv4/netfilter/ip_tables.c#L1540">1540</a>         <b><i>/* Check hooks &amp; underflows */</i></b>
<a name="L1541" href="source/net/ipv4/netfilter/ip_tables.c#L1541">1541</a>         for (<a href="ident?i=h">h</a> = 0; <a href="ident?i=h">h</a> &lt; NF_INET_NUMHOOKS; <a href="ident?i=h">h</a>++) {
<a name="L1542" href="source/net/ipv4/netfilter/ip_tables.c#L1542">1542</a>                 if ((unsigned char *)<a href="ident?i=e">e</a> - <a href="ident?i=base">base</a> == hook_entries[<a href="ident?i=h">h</a>])
<a name="L1543" href="source/net/ipv4/netfilter/ip_tables.c#L1543">1543</a>                         newinfo-&gt;hook_entry[<a href="ident?i=h">h</a>] = hook_entries[<a href="ident?i=h">h</a>];
<a name="L1544" href="source/net/ipv4/netfilter/ip_tables.c#L1544">1544</a>                 if ((unsigned char *)<a href="ident?i=e">e</a> - <a href="ident?i=base">base</a> == underflows[<a href="ident?i=h">h</a>])
<a name="L1545" href="source/net/ipv4/netfilter/ip_tables.c#L1545">1545</a>                         newinfo-&gt;underflow[<a href="ident?i=h">h</a>] = underflows[<a href="ident?i=h">h</a>];
<a name="L1546" href="source/net/ipv4/netfilter/ip_tables.c#L1546">1546</a>         }
<a name="L1547" href="source/net/ipv4/netfilter/ip_tables.c#L1547">1547</a> 
<a name="L1548" href="source/net/ipv4/netfilter/ip_tables.c#L1548">1548</a>         <b><i>/* Clear counters and comefrom */</i></b>
<a name="L1549" href="source/net/ipv4/netfilter/ip_tables.c#L1549">1549</a>         <a href="ident?i=memset">memset</a>(&amp;<a href="ident?i=e">e</a>-&gt;counters, 0, sizeof(<a href="ident?i=e">e</a>-&gt;counters));
<a name="L1550" href="source/net/ipv4/netfilter/ip_tables.c#L1550">1550</a>         <a href="ident?i=e">e</a>-&gt;comefrom = 0;
<a name="L1551" href="source/net/ipv4/netfilter/ip_tables.c#L1551">1551</a>         return 0;
<a name="L1552" href="source/net/ipv4/netfilter/ip_tables.c#L1552">1552</a> 
<a name="L1553" href="source/net/ipv4/netfilter/ip_tables.c#L1553">1553</a> <a href="ident?i=out">out</a>:
<a name="L1554" href="source/net/ipv4/netfilter/ip_tables.c#L1554">1554</a>         <a href="ident?i=module_put">module_put</a>(<a href="ident?i=t">t</a>-&gt;u.kernel.<a href="ident?i=target">target</a>-&gt;<a href="ident?i=me">me</a>);
<a name="L1555" href="source/net/ipv4/netfilter/ip_tables.c#L1555">1555</a> release_matches:
<a name="L1556" href="source/net/ipv4/netfilter/ip_tables.c#L1556">1556</a>         <a href="ident?i=xt_ematch_foreach">xt_ematch_foreach</a>(ematch, <a href="ident?i=e">e</a>) {
<a name="L1557" href="source/net/ipv4/netfilter/ip_tables.c#L1557">1557</a>                 if (j-- == 0)
<a name="L1558" href="source/net/ipv4/netfilter/ip_tables.c#L1558">1558</a>                         break;
<a name="L1559" href="source/net/ipv4/netfilter/ip_tables.c#L1559">1559</a>                 <a href="ident?i=module_put">module_put</a>(ematch-&gt;u.kernel.<a href="ident?i=match">match</a>-&gt;<a href="ident?i=me">me</a>);
<a name="L1560" href="source/net/ipv4/netfilter/ip_tables.c#L1560">1560</a>         }
<a name="L1561" href="source/net/ipv4/netfilter/ip_tables.c#L1561">1561</a>         return <a href="ident?i=ret">ret</a>;
<a name="L1562" href="source/net/ipv4/netfilter/ip_tables.c#L1562">1562</a> }
<a name="L1563" href="source/net/ipv4/netfilter/ip_tables.c#L1563">1563</a> 
<a name="L1564" href="source/net/ipv4/netfilter/ip_tables.c#L1564">1564</a> static int
<a name="L1565" href="source/net/ipv4/netfilter/ip_tables.c#L1565">1565</a> <a href="ident?i=compat_copy_entry_from_user">compat_copy_entry_from_user</a>(struct <a href="ident?i=compat_ipt_entry">compat_ipt_entry</a> *<a href="ident?i=e">e</a>, void **<a href="ident?i=dstptr">dstptr</a>,
<a name="L1566" href="source/net/ipv4/netfilter/ip_tables.c#L1566">1566</a>                             unsigned int *<a href="ident?i=size">size</a>, const char *<a href="ident?i=name">name</a>,
<a name="L1567" href="source/net/ipv4/netfilter/ip_tables.c#L1567">1567</a>                             struct <a href="ident?i=xt_table_info">xt_table_info</a> *newinfo, unsigned char *<a href="ident?i=base">base</a>)
<a name="L1568" href="source/net/ipv4/netfilter/ip_tables.c#L1568">1568</a> {
<a name="L1569" href="source/net/ipv4/netfilter/ip_tables.c#L1569">1569</a>         struct <a href="ident?i=xt_entry_target">xt_entry_target</a> *<a href="ident?i=t">t</a>;
<a name="L1570" href="source/net/ipv4/netfilter/ip_tables.c#L1570">1570</a>         struct <a href="ident?i=xt_target">xt_target</a> *<a href="ident?i=target">target</a>;
<a name="L1571" href="source/net/ipv4/netfilter/ip_tables.c#L1571">1571</a>         struct <a href="ident?i=ipt_entry">ipt_entry</a> *<a href="ident?i=de">de</a>;
<a name="L1572" href="source/net/ipv4/netfilter/ip_tables.c#L1572">1572</a>         unsigned int origsize;
<a name="L1573" href="source/net/ipv4/netfilter/ip_tables.c#L1573">1573</a>         int <a href="ident?i=ret">ret</a>, <a href="ident?i=h">h</a>;
<a name="L1574" href="source/net/ipv4/netfilter/ip_tables.c#L1574">1574</a>         struct <a href="ident?i=xt_entry_match">xt_entry_match</a> *ematch;
<a name="L1575" href="source/net/ipv4/netfilter/ip_tables.c#L1575">1575</a> 
<a name="L1576" href="source/net/ipv4/netfilter/ip_tables.c#L1576">1576</a>         <a href="ident?i=ret">ret</a> = 0;
<a name="L1577" href="source/net/ipv4/netfilter/ip_tables.c#L1577">1577</a>         origsize = *<a href="ident?i=size">size</a>;
<a name="L1578" href="source/net/ipv4/netfilter/ip_tables.c#L1578">1578</a>         <a href="ident?i=de">de</a> = (struct <a href="ident?i=ipt_entry">ipt_entry</a> *)*<a href="ident?i=dstptr">dstptr</a>;
<a name="L1579" href="source/net/ipv4/netfilter/ip_tables.c#L1579">1579</a>         <a href="ident?i=memcpy">memcpy</a>(<a href="ident?i=de">de</a>, <a href="ident?i=e">e</a>, sizeof(struct <a href="ident?i=ipt_entry">ipt_entry</a>));
<a name="L1580" href="source/net/ipv4/netfilter/ip_tables.c#L1580">1580</a>         <a href="ident?i=memcpy">memcpy</a>(&amp;<a href="ident?i=de">de</a>-&gt;counters, &amp;<a href="ident?i=e">e</a>-&gt;counters, sizeof(<a href="ident?i=e">e</a>-&gt;counters));
<a name="L1581" href="source/net/ipv4/netfilter/ip_tables.c#L1581">1581</a> 
<a name="L1582" href="source/net/ipv4/netfilter/ip_tables.c#L1582">1582</a>         *<a href="ident?i=dstptr">dstptr</a> += sizeof(struct <a href="ident?i=ipt_entry">ipt_entry</a>);
<a name="L1583" href="source/net/ipv4/netfilter/ip_tables.c#L1583">1583</a>         *<a href="ident?i=size">size</a> += sizeof(struct <a href="ident?i=ipt_entry">ipt_entry</a>) - sizeof(struct <a href="ident?i=compat_ipt_entry">compat_ipt_entry</a>);
<a name="L1584" href="source/net/ipv4/netfilter/ip_tables.c#L1584">1584</a> 
<a name="L1585" href="source/net/ipv4/netfilter/ip_tables.c#L1585">1585</a>         <a href="ident?i=xt_ematch_foreach">xt_ematch_foreach</a>(ematch, <a href="ident?i=e">e</a>) {
<a name="L1586" href="source/net/ipv4/netfilter/ip_tables.c#L1586">1586</a>                 <a href="ident?i=ret">ret</a> = <a href="ident?i=xt_compat_match_from_user">xt_compat_match_from_user</a>(ematch, <a href="ident?i=dstptr">dstptr</a>, <a href="ident?i=size">size</a>);
<a name="L1587" href="source/net/ipv4/netfilter/ip_tables.c#L1587">1587</a>                 if (<a href="ident?i=ret">ret</a> != 0)
<a name="L1588" href="source/net/ipv4/netfilter/ip_tables.c#L1588">1588</a>                         return <a href="ident?i=ret">ret</a>;
<a name="L1589" href="source/net/ipv4/netfilter/ip_tables.c#L1589">1589</a>         }
<a name="L1590" href="source/net/ipv4/netfilter/ip_tables.c#L1590">1590</a>         <a href="ident?i=de">de</a>-&gt;target_offset = <a href="ident?i=e">e</a>-&gt;target_offset - (origsize - *<a href="ident?i=size">size</a>);
<a name="L1591" href="source/net/ipv4/netfilter/ip_tables.c#L1591">1591</a>         <a href="ident?i=t">t</a> = <a href="ident?i=compat_ipt_get_target">compat_ipt_get_target</a>(<a href="ident?i=e">e</a>);
<a name="L1592" href="source/net/ipv4/netfilter/ip_tables.c#L1592">1592</a>         <a href="ident?i=target">target</a> = <a href="ident?i=t">t</a>-&gt;u.kernel.<a href="ident?i=target">target</a>;
<a name="L1593" href="source/net/ipv4/netfilter/ip_tables.c#L1593">1593</a>         <a href="ident?i=xt_compat_target_from_user">xt_compat_target_from_user</a>(<a href="ident?i=t">t</a>, <a href="ident?i=dstptr">dstptr</a>, <a href="ident?i=size">size</a>);
<a name="L1594" href="source/net/ipv4/netfilter/ip_tables.c#L1594">1594</a> 
<a name="L1595" href="source/net/ipv4/netfilter/ip_tables.c#L1595">1595</a>         <a href="ident?i=de">de</a>-&gt;next_offset = <a href="ident?i=e">e</a>-&gt;next_offset - (origsize - *<a href="ident?i=size">size</a>);
<a name="L1596" href="source/net/ipv4/netfilter/ip_tables.c#L1596">1596</a>         for (<a href="ident?i=h">h</a> = 0; <a href="ident?i=h">h</a> &lt; NF_INET_NUMHOOKS; <a href="ident?i=h">h</a>++) {
<a name="L1597" href="source/net/ipv4/netfilter/ip_tables.c#L1597">1597</a>                 if ((unsigned char *)<a href="ident?i=de">de</a> - <a href="ident?i=base">base</a> &lt; newinfo-&gt;hook_entry[<a href="ident?i=h">h</a>])
<a name="L1598" href="source/net/ipv4/netfilter/ip_tables.c#L1598">1598</a>                         newinfo-&gt;hook_entry[<a href="ident?i=h">h</a>] -= origsize - *<a href="ident?i=size">size</a>;
<a name="L1599" href="source/net/ipv4/netfilter/ip_tables.c#L1599">1599</a>                 if ((unsigned char *)<a href="ident?i=de">de</a> - <a href="ident?i=base">base</a> &lt; newinfo-&gt;underflow[<a href="ident?i=h">h</a>])
<a name="L1600" href="source/net/ipv4/netfilter/ip_tables.c#L1600">1600</a>                         newinfo-&gt;underflow[<a href="ident?i=h">h</a>] -= origsize - *<a href="ident?i=size">size</a>;
<a name="L1601" href="source/net/ipv4/netfilter/ip_tables.c#L1601">1601</a>         }
<a name="L1602" href="source/net/ipv4/netfilter/ip_tables.c#L1602">1602</a>         return <a href="ident?i=ret">ret</a>;
<a name="L1603" href="source/net/ipv4/netfilter/ip_tables.c#L1603">1603</a> }
<a name="L1604" href="source/net/ipv4/netfilter/ip_tables.c#L1604">1604</a> 
<a name="L1605" href="source/net/ipv4/netfilter/ip_tables.c#L1605">1605</a> static int
<a name="L1606" href="source/net/ipv4/netfilter/ip_tables.c#L1606">1606</a> <a href="ident?i=compat_check_entry">compat_check_entry</a>(struct <a href="ident?i=ipt_entry">ipt_entry</a> *<a href="ident?i=e">e</a>, struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>, const char *<a href="ident?i=name">name</a>)
<a name="L1607" href="source/net/ipv4/netfilter/ip_tables.c#L1607">1607</a> {
<a name="L1608" href="source/net/ipv4/netfilter/ip_tables.c#L1608">1608</a>         struct <a href="ident?i=xt_entry_match">xt_entry_match</a> *ematch;
<a name="L1609" href="source/net/ipv4/netfilter/ip_tables.c#L1609">1609</a>         struct <a href="ident?i=xt_mtchk_param">xt_mtchk_param</a> mtpar;
<a name="L1610" href="source/net/ipv4/netfilter/ip_tables.c#L1610">1610</a>         unsigned int j;
<a name="L1611" href="source/net/ipv4/netfilter/ip_tables.c#L1611">1611</a>         int <a href="ident?i=ret">ret</a> = 0;
<a name="L1612" href="source/net/ipv4/netfilter/ip_tables.c#L1612">1612</a> 
<a name="L1613" href="source/net/ipv4/netfilter/ip_tables.c#L1613">1613</a>         j = 0;
<a name="L1614" href="source/net/ipv4/netfilter/ip_tables.c#L1614">1614</a>         mtpar.<a href="ident?i=net">net</a>       = <a href="ident?i=net">net</a>;
<a name="L1615" href="source/net/ipv4/netfilter/ip_tables.c#L1615">1615</a>         mtpar.<a href="ident?i=table">table</a>     = <a href="ident?i=name">name</a>;
<a name="L1616" href="source/net/ipv4/netfilter/ip_tables.c#L1616">1616</a>         mtpar.entryinfo = &amp;<a href="ident?i=e">e</a>-&gt;<a href="ident?i=ip">ip</a>;
<a name="L1617" href="source/net/ipv4/netfilter/ip_tables.c#L1617">1617</a>         mtpar.hook_mask = <a href="ident?i=e">e</a>-&gt;comefrom;
<a name="L1618" href="source/net/ipv4/netfilter/ip_tables.c#L1618">1618</a>         mtpar.<a href="ident?i=family">family</a>    = NFPROTO_IPV4;
<a name="L1619" href="source/net/ipv4/netfilter/ip_tables.c#L1619">1619</a>         <a href="ident?i=xt_ematch_foreach">xt_ematch_foreach</a>(ematch, <a href="ident?i=e">e</a>) {
<a name="L1620" href="source/net/ipv4/netfilter/ip_tables.c#L1620">1620</a>                 <a href="ident?i=ret">ret</a> = <a href="ident?i=check_match">check_match</a>(ematch, &amp;mtpar);
<a name="L1621" href="source/net/ipv4/netfilter/ip_tables.c#L1621">1621</a>                 if (<a href="ident?i=ret">ret</a> != 0)
<a name="L1622" href="source/net/ipv4/netfilter/ip_tables.c#L1622">1622</a>                         goto cleanup_matches;
<a name="L1623" href="source/net/ipv4/netfilter/ip_tables.c#L1623">1623</a>                 ++j;
<a name="L1624" href="source/net/ipv4/netfilter/ip_tables.c#L1624">1624</a>         }
<a name="L1625" href="source/net/ipv4/netfilter/ip_tables.c#L1625">1625</a> 
<a name="L1626" href="source/net/ipv4/netfilter/ip_tables.c#L1626">1626</a>         <a href="ident?i=ret">ret</a> = <a href="ident?i=check_target">check_target</a>(<a href="ident?i=e">e</a>, <a href="ident?i=net">net</a>, <a href="ident?i=name">name</a>);
<a name="L1627" href="source/net/ipv4/netfilter/ip_tables.c#L1627">1627</a>         if (<a href="ident?i=ret">ret</a>)
<a name="L1628" href="source/net/ipv4/netfilter/ip_tables.c#L1628">1628</a>                 goto cleanup_matches;
<a name="L1629" href="source/net/ipv4/netfilter/ip_tables.c#L1629">1629</a>         return 0;
<a name="L1630" href="source/net/ipv4/netfilter/ip_tables.c#L1630">1630</a> 
<a name="L1631" href="source/net/ipv4/netfilter/ip_tables.c#L1631">1631</a>  cleanup_matches:
<a name="L1632" href="source/net/ipv4/netfilter/ip_tables.c#L1632">1632</a>         <a href="ident?i=xt_ematch_foreach">xt_ematch_foreach</a>(ematch, <a href="ident?i=e">e</a>) {
<a name="L1633" href="source/net/ipv4/netfilter/ip_tables.c#L1633">1633</a>                 if (j-- == 0)
<a name="L1634" href="source/net/ipv4/netfilter/ip_tables.c#L1634">1634</a>                         break;
<a name="L1635" href="source/net/ipv4/netfilter/ip_tables.c#L1635">1635</a>                 <a href="ident?i=cleanup_match">cleanup_match</a>(ematch, <a href="ident?i=net">net</a>);
<a name="L1636" href="source/net/ipv4/netfilter/ip_tables.c#L1636">1636</a>         }
<a name="L1637" href="source/net/ipv4/netfilter/ip_tables.c#L1637">1637</a>         return <a href="ident?i=ret">ret</a>;
<a name="L1638" href="source/net/ipv4/netfilter/ip_tables.c#L1638">1638</a> }
<a name="L1639" href="source/net/ipv4/netfilter/ip_tables.c#L1639">1639</a> 
<a name="L1640" href="source/net/ipv4/netfilter/ip_tables.c#L1640">1640</a> static int
<a name="L1641" href="source/net/ipv4/netfilter/ip_tables.c#L1641">1641</a> <a href="ident?i=translate_compat_table">translate_compat_table</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>,
<a name="L1642" href="source/net/ipv4/netfilter/ip_tables.c#L1642">1642</a>                        const char *<a href="ident?i=name">name</a>,
<a name="L1643" href="source/net/ipv4/netfilter/ip_tables.c#L1643">1643</a>                        unsigned int valid_hooks,
<a name="L1644" href="source/net/ipv4/netfilter/ip_tables.c#L1644">1644</a>                        struct <a href="ident?i=xt_table_info">xt_table_info</a> **pinfo,
<a name="L1645" href="source/net/ipv4/netfilter/ip_tables.c#L1645">1645</a>                        void **pentry0,
<a name="L1646" href="source/net/ipv4/netfilter/ip_tables.c#L1646">1646</a>                        unsigned int <a href="ident?i=total_size">total_size</a>,
<a name="L1647" href="source/net/ipv4/netfilter/ip_tables.c#L1647">1647</a>                        unsigned int <a href="ident?i=number">number</a>,
<a name="L1648" href="source/net/ipv4/netfilter/ip_tables.c#L1648">1648</a>                        unsigned int *hook_entries,
<a name="L1649" href="source/net/ipv4/netfilter/ip_tables.c#L1649">1649</a>                        unsigned int *underflows)
<a name="L1650" href="source/net/ipv4/netfilter/ip_tables.c#L1650">1650</a> {
<a name="L1651" href="source/net/ipv4/netfilter/ip_tables.c#L1651">1651</a>         unsigned int <a href="ident?i=i">i</a>, j;
<a name="L1652" href="source/net/ipv4/netfilter/ip_tables.c#L1652">1652</a>         struct <a href="ident?i=xt_table_info">xt_table_info</a> *newinfo, *<a href="ident?i=info">info</a>;
<a name="L1653" href="source/net/ipv4/netfilter/ip_tables.c#L1653">1653</a>         void *<a href="ident?i=pos">pos</a>, *entry0, *entry1;
<a name="L1654" href="source/net/ipv4/netfilter/ip_tables.c#L1654">1654</a>         struct <a href="ident?i=compat_ipt_entry">compat_ipt_entry</a> *iter0;
<a name="L1655" href="source/net/ipv4/netfilter/ip_tables.c#L1655">1655</a>         struct <a href="ident?i=ipt_entry">ipt_entry</a> *iter1;
<a name="L1656" href="source/net/ipv4/netfilter/ip_tables.c#L1656">1656</a>         unsigned int <a href="ident?i=size">size</a>;
<a name="L1657" href="source/net/ipv4/netfilter/ip_tables.c#L1657">1657</a>         int <a href="ident?i=ret">ret</a>;
<a name="L1658" href="source/net/ipv4/netfilter/ip_tables.c#L1658">1658</a> 
<a name="L1659" href="source/net/ipv4/netfilter/ip_tables.c#L1659">1659</a>         <a href="ident?i=info">info</a> = *pinfo;
<a name="L1660" href="source/net/ipv4/netfilter/ip_tables.c#L1660">1660</a>         entry0 = *pentry0;
<a name="L1661" href="source/net/ipv4/netfilter/ip_tables.c#L1661">1661</a>         <a href="ident?i=size">size</a> = <a href="ident?i=total_size">total_size</a>;
<a name="L1662" href="source/net/ipv4/netfilter/ip_tables.c#L1662">1662</a>         <a href="ident?i=info">info</a>-&gt;<a href="ident?i=number">number</a> = <a href="ident?i=number">number</a>;
<a name="L1663" href="source/net/ipv4/netfilter/ip_tables.c#L1663">1663</a> 
<a name="L1664" href="source/net/ipv4/netfilter/ip_tables.c#L1664">1664</a>         <b><i>/* Init all hooks to impossible value. */</i></b>
<a name="L1665" href="source/net/ipv4/netfilter/ip_tables.c#L1665">1665</a>         for (<a href="ident?i=i">i</a> = 0; <a href="ident?i=i">i</a> &lt; NF_INET_NUMHOOKS; <a href="ident?i=i">i</a>++) {
<a name="L1666" href="source/net/ipv4/netfilter/ip_tables.c#L1666">1666</a>                 <a href="ident?i=info">info</a>-&gt;hook_entry[<a href="ident?i=i">i</a>] = 0xFFFFFFFF;
<a name="L1667" href="source/net/ipv4/netfilter/ip_tables.c#L1667">1667</a>                 <a href="ident?i=info">info</a>-&gt;underflow[<a href="ident?i=i">i</a>] = 0xFFFFFFFF;
<a name="L1668" href="source/net/ipv4/netfilter/ip_tables.c#L1668">1668</a>         }
<a name="L1669" href="source/net/ipv4/netfilter/ip_tables.c#L1669">1669</a> 
<a name="L1670" href="source/net/ipv4/netfilter/ip_tables.c#L1670">1670</a>         <a href="ident?i=duprintf">duprintf</a>(<i>"translate_compat_table: size %u\n"</i>, <a href="ident?i=info">info</a>-&gt;<a href="ident?i=size">size</a>);
<a name="L1671" href="source/net/ipv4/netfilter/ip_tables.c#L1671">1671</a>         j = 0;
<a name="L1672" href="source/net/ipv4/netfilter/ip_tables.c#L1672">1672</a>         <a href="ident?i=xt_compat_lock">xt_compat_lock</a>(<a href="ident?i=AF_INET">AF_INET</a>);
<a name="L1673" href="source/net/ipv4/netfilter/ip_tables.c#L1673">1673</a>         <a href="ident?i=xt_compat_init_offsets">xt_compat_init_offsets</a>(<a href="ident?i=AF_INET">AF_INET</a>, <a href="ident?i=number">number</a>);
<a name="L1674" href="source/net/ipv4/netfilter/ip_tables.c#L1674">1674</a>         <b><i>/* Walk through entries, checking offsets. */</i></b>
<a name="L1675" href="source/net/ipv4/netfilter/ip_tables.c#L1675">1675</a>         <a href="ident?i=xt_entry_foreach">xt_entry_foreach</a>(iter0, entry0, <a href="ident?i=total_size">total_size</a>) {
<a name="L1676" href="source/net/ipv4/netfilter/ip_tables.c#L1676">1676</a>                 <a href="ident?i=ret">ret</a> = <a href="ident?i=check_compat_entry_size_and_hooks">check_compat_entry_size_and_hooks</a>(iter0, <a href="ident?i=info">info</a>, &amp;<a href="ident?i=size">size</a>,
<a name="L1677" href="source/net/ipv4/netfilter/ip_tables.c#L1677">1677</a>                                                         entry0,
<a name="L1678" href="source/net/ipv4/netfilter/ip_tables.c#L1678">1678</a>                                                         entry0 + <a href="ident?i=total_size">total_size</a>,
<a name="L1679" href="source/net/ipv4/netfilter/ip_tables.c#L1679">1679</a>                                                         hook_entries,
<a name="L1680" href="source/net/ipv4/netfilter/ip_tables.c#L1680">1680</a>                                                         underflows,
<a name="L1681" href="source/net/ipv4/netfilter/ip_tables.c#L1681">1681</a>                                                         <a href="ident?i=name">name</a>);
<a name="L1682" href="source/net/ipv4/netfilter/ip_tables.c#L1682">1682</a>                 if (<a href="ident?i=ret">ret</a> != 0)
<a name="L1683" href="source/net/ipv4/netfilter/ip_tables.c#L1683">1683</a>                         goto out_unlock;
<a name="L1684" href="source/net/ipv4/netfilter/ip_tables.c#L1684">1684</a>                 ++j;
<a name="L1685" href="source/net/ipv4/netfilter/ip_tables.c#L1685">1685</a>         }
<a name="L1686" href="source/net/ipv4/netfilter/ip_tables.c#L1686">1686</a> 
<a name="L1687" href="source/net/ipv4/netfilter/ip_tables.c#L1687">1687</a>         <a href="ident?i=ret">ret</a> = -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L1688" href="source/net/ipv4/netfilter/ip_tables.c#L1688">1688</a>         if (j != <a href="ident?i=number">number</a>) {
<a name="L1689" href="source/net/ipv4/netfilter/ip_tables.c#L1689">1689</a>                 <a href="ident?i=duprintf">duprintf</a>(<i>"translate_compat_table: %u not %u entries\n"</i>,
<a name="L1690" href="source/net/ipv4/netfilter/ip_tables.c#L1690">1690</a>                          j, <a href="ident?i=number">number</a>);
<a name="L1691" href="source/net/ipv4/netfilter/ip_tables.c#L1691">1691</a>                 goto out_unlock;
<a name="L1692" href="source/net/ipv4/netfilter/ip_tables.c#L1692">1692</a>         }
<a name="L1693" href="source/net/ipv4/netfilter/ip_tables.c#L1693">1693</a> 
<a name="L1694" href="source/net/ipv4/netfilter/ip_tables.c#L1694">1694</a>         <b><i>/* Check hooks all assigned */</i></b>
<a name="L1695" href="source/net/ipv4/netfilter/ip_tables.c#L1695">1695</a>         for (<a href="ident?i=i">i</a> = 0; <a href="ident?i=i">i</a> &lt; NF_INET_NUMHOOKS; <a href="ident?i=i">i</a>++) {
<a name="L1696" href="source/net/ipv4/netfilter/ip_tables.c#L1696">1696</a>                 <b><i>/* Only hooks which are valid */</i></b>
<a name="L1697" href="source/net/ipv4/netfilter/ip_tables.c#L1697">1697</a>                 if (!(valid_hooks &amp; (1 &lt;&lt; <a href="ident?i=i">i</a>)))
<a name="L1698" href="source/net/ipv4/netfilter/ip_tables.c#L1698">1698</a>                         continue;
<a name="L1699" href="source/net/ipv4/netfilter/ip_tables.c#L1699">1699</a>                 if (<a href="ident?i=info">info</a>-&gt;hook_entry[<a href="ident?i=i">i</a>] == 0xFFFFFFFF) {
<a name="L1700" href="source/net/ipv4/netfilter/ip_tables.c#L1700">1700</a>                         <a href="ident?i=duprintf">duprintf</a>(<i>"Invalid hook entry %u %u\n"</i>,
<a name="L1701" href="source/net/ipv4/netfilter/ip_tables.c#L1701">1701</a>                                  <a href="ident?i=i">i</a>, hook_entries[<a href="ident?i=i">i</a>]);
<a name="L1702" href="source/net/ipv4/netfilter/ip_tables.c#L1702">1702</a>                         goto out_unlock;
<a name="L1703" href="source/net/ipv4/netfilter/ip_tables.c#L1703">1703</a>                 }
<a name="L1704" href="source/net/ipv4/netfilter/ip_tables.c#L1704">1704</a>                 if (<a href="ident?i=info">info</a>-&gt;underflow[<a href="ident?i=i">i</a>] == 0xFFFFFFFF) {
<a name="L1705" href="source/net/ipv4/netfilter/ip_tables.c#L1705">1705</a>                         <a href="ident?i=duprintf">duprintf</a>(<i>"Invalid underflow %u %u\n"</i>,
<a name="L1706" href="source/net/ipv4/netfilter/ip_tables.c#L1706">1706</a>                                  <a href="ident?i=i">i</a>, underflows[<a href="ident?i=i">i</a>]);
<a name="L1707" href="source/net/ipv4/netfilter/ip_tables.c#L1707">1707</a>                         goto out_unlock;
<a name="L1708" href="source/net/ipv4/netfilter/ip_tables.c#L1708">1708</a>                 }
<a name="L1709" href="source/net/ipv4/netfilter/ip_tables.c#L1709">1709</a>         }
<a name="L1710" href="source/net/ipv4/netfilter/ip_tables.c#L1710">1710</a> 
<a name="L1711" href="source/net/ipv4/netfilter/ip_tables.c#L1711">1711</a>         <a href="ident?i=ret">ret</a> = -<a href="ident?i=ENOMEM">ENOMEM</a>;
<a name="L1712" href="source/net/ipv4/netfilter/ip_tables.c#L1712">1712</a>         newinfo = <a href="ident?i=xt_alloc_table_info">xt_alloc_table_info</a>(<a href="ident?i=size">size</a>);
<a name="L1713" href="source/net/ipv4/netfilter/ip_tables.c#L1713">1713</a>         if (!newinfo)
<a name="L1714" href="source/net/ipv4/netfilter/ip_tables.c#L1714">1714</a>                 goto out_unlock;
<a name="L1715" href="source/net/ipv4/netfilter/ip_tables.c#L1715">1715</a> 
<a name="L1716" href="source/net/ipv4/netfilter/ip_tables.c#L1716">1716</a>         newinfo-&gt;<a href="ident?i=number">number</a> = <a href="ident?i=number">number</a>;
<a name="L1717" href="source/net/ipv4/netfilter/ip_tables.c#L1717">1717</a>         for (<a href="ident?i=i">i</a> = 0; <a href="ident?i=i">i</a> &lt; NF_INET_NUMHOOKS; <a href="ident?i=i">i</a>++) {
<a name="L1718" href="source/net/ipv4/netfilter/ip_tables.c#L1718">1718</a>                 newinfo-&gt;hook_entry[<a href="ident?i=i">i</a>] = <a href="ident?i=info">info</a>-&gt;hook_entry[<a href="ident?i=i">i</a>];
<a name="L1719" href="source/net/ipv4/netfilter/ip_tables.c#L1719">1719</a>                 newinfo-&gt;underflow[<a href="ident?i=i">i</a>] = <a href="ident?i=info">info</a>-&gt;underflow[<a href="ident?i=i">i</a>];
<a name="L1720" href="source/net/ipv4/netfilter/ip_tables.c#L1720">1720</a>         }
<a name="L1721" href="source/net/ipv4/netfilter/ip_tables.c#L1721">1721</a>         entry1 = newinfo-&gt;<a href="ident?i=entries">entries</a>[<a href="ident?i=raw_smp_processor_id">raw_smp_processor_id</a>()];
<a name="L1722" href="source/net/ipv4/netfilter/ip_tables.c#L1722">1722</a>         <a href="ident?i=pos">pos</a> = entry1;
<a name="L1723" href="source/net/ipv4/netfilter/ip_tables.c#L1723">1723</a>         <a href="ident?i=size">size</a> = <a href="ident?i=total_size">total_size</a>;
<a name="L1724" href="source/net/ipv4/netfilter/ip_tables.c#L1724">1724</a>         <a href="ident?i=xt_entry_foreach">xt_entry_foreach</a>(iter0, entry0, <a href="ident?i=total_size">total_size</a>) {
<a name="L1725" href="source/net/ipv4/netfilter/ip_tables.c#L1725">1725</a>                 <a href="ident?i=ret">ret</a> = <a href="ident?i=compat_copy_entry_from_user">compat_copy_entry_from_user</a>(iter0, &amp;<a href="ident?i=pos">pos</a>, &amp;<a href="ident?i=size">size</a>,
<a name="L1726" href="source/net/ipv4/netfilter/ip_tables.c#L1726">1726</a>                                                   <a href="ident?i=name">name</a>, newinfo, entry1);
<a name="L1727" href="source/net/ipv4/netfilter/ip_tables.c#L1727">1727</a>                 if (<a href="ident?i=ret">ret</a> != 0)
<a name="L1728" href="source/net/ipv4/netfilter/ip_tables.c#L1728">1728</a>                         break;
<a name="L1729" href="source/net/ipv4/netfilter/ip_tables.c#L1729">1729</a>         }
<a name="L1730" href="source/net/ipv4/netfilter/ip_tables.c#L1730">1730</a>         <a href="ident?i=xt_compat_flush_offsets">xt_compat_flush_offsets</a>(<a href="ident?i=AF_INET">AF_INET</a>);
<a name="L1731" href="source/net/ipv4/netfilter/ip_tables.c#L1731">1731</a>         <a href="ident?i=xt_compat_unlock">xt_compat_unlock</a>(<a href="ident?i=AF_INET">AF_INET</a>);
<a name="L1732" href="source/net/ipv4/netfilter/ip_tables.c#L1732">1732</a>         if (<a href="ident?i=ret">ret</a>)
<a name="L1733" href="source/net/ipv4/netfilter/ip_tables.c#L1733">1733</a>                 goto free_newinfo;
<a name="L1734" href="source/net/ipv4/netfilter/ip_tables.c#L1734">1734</a> 
<a name="L1735" href="source/net/ipv4/netfilter/ip_tables.c#L1735">1735</a>         <a href="ident?i=ret">ret</a> = -<a href="ident?i=ELOOP">ELOOP</a>;
<a name="L1736" href="source/net/ipv4/netfilter/ip_tables.c#L1736">1736</a>         if (!<a href="ident?i=mark_source_chains">mark_source_chains</a>(newinfo, valid_hooks, entry1))
<a name="L1737" href="source/net/ipv4/netfilter/ip_tables.c#L1737">1737</a>                 goto free_newinfo;
<a name="L1738" href="source/net/ipv4/netfilter/ip_tables.c#L1738">1738</a> 
<a name="L1739" href="source/net/ipv4/netfilter/ip_tables.c#L1739">1739</a>         <a href="ident?i=i">i</a> = 0;
<a name="L1740" href="source/net/ipv4/netfilter/ip_tables.c#L1740">1740</a>         <a href="ident?i=xt_entry_foreach">xt_entry_foreach</a>(iter1, entry1, newinfo-&gt;<a href="ident?i=size">size</a>) {
<a name="L1741" href="source/net/ipv4/netfilter/ip_tables.c#L1741">1741</a>                 <a href="ident?i=ret">ret</a> = <a href="ident?i=compat_check_entry">compat_check_entry</a>(iter1, <a href="ident?i=net">net</a>, <a href="ident?i=name">name</a>);
<a name="L1742" href="source/net/ipv4/netfilter/ip_tables.c#L1742">1742</a>                 if (<a href="ident?i=ret">ret</a> != 0)
<a name="L1743" href="source/net/ipv4/netfilter/ip_tables.c#L1743">1743</a>                         break;
<a name="L1744" href="source/net/ipv4/netfilter/ip_tables.c#L1744">1744</a>                 ++<a href="ident?i=i">i</a>;
<a name="L1745" href="source/net/ipv4/netfilter/ip_tables.c#L1745">1745</a>                 if (<a href="ident?i=strcmp">strcmp</a>(<a href="ident?i=ipt_get_target">ipt_get_target</a>(iter1)-&gt;u.<a href="ident?i=user">user</a>.<a href="ident?i=name">name</a>,
<a name="L1746" href="source/net/ipv4/netfilter/ip_tables.c#L1746">1746</a>                     <a href="ident?i=XT_ERROR_TARGET">XT_ERROR_TARGET</a>) == 0)
<a name="L1747" href="source/net/ipv4/netfilter/ip_tables.c#L1747">1747</a>                         ++newinfo-&gt;stacksize;
<a name="L1748" href="source/net/ipv4/netfilter/ip_tables.c#L1748">1748</a>         }
<a name="L1749" href="source/net/ipv4/netfilter/ip_tables.c#L1749">1749</a>         if (<a href="ident?i=ret">ret</a>) {
<a name="L1750" href="source/net/ipv4/netfilter/ip_tables.c#L1750">1750</a>                 <b><i>/*</i></b>
<a name="L1751" href="source/net/ipv4/netfilter/ip_tables.c#L1751">1751</a> <b><i>                 * The first i matches need cleanup_entry (calls -&gt;destroy)</i></b>
<a name="L1752" href="source/net/ipv4/netfilter/ip_tables.c#L1752">1752</a> <b><i>                 * because they had called -&gt;check already. The other j-i</i></b>
<a name="L1753" href="source/net/ipv4/netfilter/ip_tables.c#L1753">1753</a> <b><i>                 * entries need only release.</i></b>
<a name="L1754" href="source/net/ipv4/netfilter/ip_tables.c#L1754">1754</a> <b><i>                 */</i></b>
<a name="L1755" href="source/net/ipv4/netfilter/ip_tables.c#L1755">1755</a>                 int <a href="ident?i=skip">skip</a> = <a href="ident?i=i">i</a>;
<a name="L1756" href="source/net/ipv4/netfilter/ip_tables.c#L1756">1756</a>                 j -= <a href="ident?i=i">i</a>;
<a name="L1757" href="source/net/ipv4/netfilter/ip_tables.c#L1757">1757</a>                 <a href="ident?i=xt_entry_foreach">xt_entry_foreach</a>(iter0, entry0, newinfo-&gt;<a href="ident?i=size">size</a>) {
<a name="L1758" href="source/net/ipv4/netfilter/ip_tables.c#L1758">1758</a>                         if (<a href="ident?i=skip">skip</a>-- &gt; 0)
<a name="L1759" href="source/net/ipv4/netfilter/ip_tables.c#L1759">1759</a>                                 continue;
<a name="L1760" href="source/net/ipv4/netfilter/ip_tables.c#L1760">1760</a>                         if (j-- == 0)
<a name="L1761" href="source/net/ipv4/netfilter/ip_tables.c#L1761">1761</a>                                 break;
<a name="L1762" href="source/net/ipv4/netfilter/ip_tables.c#L1762">1762</a>                         <a href="ident?i=compat_release_entry">compat_release_entry</a>(iter0);
<a name="L1763" href="source/net/ipv4/netfilter/ip_tables.c#L1763">1763</a>                 }
<a name="L1764" href="source/net/ipv4/netfilter/ip_tables.c#L1764">1764</a>                 <a href="ident?i=xt_entry_foreach">xt_entry_foreach</a>(iter1, entry1, newinfo-&gt;<a href="ident?i=size">size</a>) {
<a name="L1765" href="source/net/ipv4/netfilter/ip_tables.c#L1765">1765</a>                         if (<a href="ident?i=i">i</a>-- == 0)
<a name="L1766" href="source/net/ipv4/netfilter/ip_tables.c#L1766">1766</a>                                 break;
<a name="L1767" href="source/net/ipv4/netfilter/ip_tables.c#L1767">1767</a>                         <a href="ident?i=cleanup_entry">cleanup_entry</a>(iter1, <a href="ident?i=net">net</a>);
<a name="L1768" href="source/net/ipv4/netfilter/ip_tables.c#L1768">1768</a>                 }
<a name="L1769" href="source/net/ipv4/netfilter/ip_tables.c#L1769">1769</a>                 <a href="ident?i=xt_free_table_info">xt_free_table_info</a>(newinfo);
<a name="L1770" href="source/net/ipv4/netfilter/ip_tables.c#L1770">1770</a>                 return <a href="ident?i=ret">ret</a>;
<a name="L1771" href="source/net/ipv4/netfilter/ip_tables.c#L1771">1771</a>         }
<a name="L1772" href="source/net/ipv4/netfilter/ip_tables.c#L1772">1772</a> 
<a name="L1773" href="source/net/ipv4/netfilter/ip_tables.c#L1773">1773</a>         <b><i>/* And one copy for every other CPU */</i></b>
<a name="L1774" href="source/net/ipv4/netfilter/ip_tables.c#L1774">1774</a>         <a href="ident?i=for_each_possible_cpu">for_each_possible_cpu</a>(<a href="ident?i=i">i</a>)
<a name="L1775" href="source/net/ipv4/netfilter/ip_tables.c#L1775">1775</a>                 if (newinfo-&gt;<a href="ident?i=entries">entries</a>[<a href="ident?i=i">i</a>] &amp;&amp; newinfo-&gt;<a href="ident?i=entries">entries</a>[<a href="ident?i=i">i</a>] != entry1)
<a name="L1776" href="source/net/ipv4/netfilter/ip_tables.c#L1776">1776</a>                         <a href="ident?i=memcpy">memcpy</a>(newinfo-&gt;<a href="ident?i=entries">entries</a>[<a href="ident?i=i">i</a>], entry1, newinfo-&gt;<a href="ident?i=size">size</a>);
<a name="L1777" href="source/net/ipv4/netfilter/ip_tables.c#L1777">1777</a> 
<a name="L1778" href="source/net/ipv4/netfilter/ip_tables.c#L1778">1778</a>         *pinfo = newinfo;
<a name="L1779" href="source/net/ipv4/netfilter/ip_tables.c#L1779">1779</a>         *pentry0 = entry1;
<a name="L1780" href="source/net/ipv4/netfilter/ip_tables.c#L1780">1780</a>         <a href="ident?i=xt_free_table_info">xt_free_table_info</a>(<a href="ident?i=info">info</a>);
<a name="L1781" href="source/net/ipv4/netfilter/ip_tables.c#L1781">1781</a>         return 0;
<a name="L1782" href="source/net/ipv4/netfilter/ip_tables.c#L1782">1782</a> 
<a name="L1783" href="source/net/ipv4/netfilter/ip_tables.c#L1783">1783</a> free_newinfo:
<a name="L1784" href="source/net/ipv4/netfilter/ip_tables.c#L1784">1784</a>         <a href="ident?i=xt_free_table_info">xt_free_table_info</a>(newinfo);
<a name="L1785" href="source/net/ipv4/netfilter/ip_tables.c#L1785">1785</a> <a href="ident?i=out">out</a>:
<a name="L1786" href="source/net/ipv4/netfilter/ip_tables.c#L1786">1786</a>         <a href="ident?i=xt_entry_foreach">xt_entry_foreach</a>(iter0, entry0, <a href="ident?i=total_size">total_size</a>) {
<a name="L1787" href="source/net/ipv4/netfilter/ip_tables.c#L1787">1787</a>                 if (j-- == 0)
<a name="L1788" href="source/net/ipv4/netfilter/ip_tables.c#L1788">1788</a>                         break;
<a name="L1789" href="source/net/ipv4/netfilter/ip_tables.c#L1789">1789</a>                 <a href="ident?i=compat_release_entry">compat_release_entry</a>(iter0);
<a name="L1790" href="source/net/ipv4/netfilter/ip_tables.c#L1790">1790</a>         }
<a name="L1791" href="source/net/ipv4/netfilter/ip_tables.c#L1791">1791</a>         return <a href="ident?i=ret">ret</a>;
<a name="L1792" href="source/net/ipv4/netfilter/ip_tables.c#L1792">1792</a> out_unlock:
<a name="L1793" href="source/net/ipv4/netfilter/ip_tables.c#L1793">1793</a>         <a href="ident?i=xt_compat_flush_offsets">xt_compat_flush_offsets</a>(<a href="ident?i=AF_INET">AF_INET</a>);
<a name="L1794" href="source/net/ipv4/netfilter/ip_tables.c#L1794">1794</a>         <a href="ident?i=xt_compat_unlock">xt_compat_unlock</a>(<a href="ident?i=AF_INET">AF_INET</a>);
<a name="L1795" href="source/net/ipv4/netfilter/ip_tables.c#L1795">1795</a>         goto <a href="ident?i=out">out</a>;
<a name="L1796" href="source/net/ipv4/netfilter/ip_tables.c#L1796">1796</a> }
<a name="L1797" href="source/net/ipv4/netfilter/ip_tables.c#L1797">1797</a> 
<a name="L1798" href="source/net/ipv4/netfilter/ip_tables.c#L1798">1798</a> static int
<a name="L1799" href="source/net/ipv4/netfilter/ip_tables.c#L1799">1799</a> <a href="ident?i=compat_do_replace">compat_do_replace</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>, void <a href="ident?i=__user">__user</a> *<a href="ident?i=user">user</a>, unsigned int <a href="ident?i=len">len</a>)
<a name="L1800" href="source/net/ipv4/netfilter/ip_tables.c#L1800">1800</a> {
<a name="L1801" href="source/net/ipv4/netfilter/ip_tables.c#L1801">1801</a>         int <a href="ident?i=ret">ret</a>;
<a name="L1802" href="source/net/ipv4/netfilter/ip_tables.c#L1802">1802</a>         struct <a href="ident?i=compat_ipt_replace">compat_ipt_replace</a> <a href="ident?i=tmp">tmp</a>;
<a name="L1803" href="source/net/ipv4/netfilter/ip_tables.c#L1803">1803</a>         struct <a href="ident?i=xt_table_info">xt_table_info</a> *newinfo;
<a name="L1804" href="source/net/ipv4/netfilter/ip_tables.c#L1804">1804</a>         void *loc_cpu_entry;
<a name="L1805" href="source/net/ipv4/netfilter/ip_tables.c#L1805">1805</a>         struct <a href="ident?i=ipt_entry">ipt_entry</a> *iter;
<a name="L1806" href="source/net/ipv4/netfilter/ip_tables.c#L1806">1806</a> 
<a name="L1807" href="source/net/ipv4/netfilter/ip_tables.c#L1807">1807</a>         if (<a href="ident?i=copy_from_user">copy_from_user</a>(&amp;<a href="ident?i=tmp">tmp</a>, <a href="ident?i=user">user</a>, sizeof(<a href="ident?i=tmp">tmp</a>)) != 0)
<a name="L1808" href="source/net/ipv4/netfilter/ip_tables.c#L1808">1808</a>                 return -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L1809" href="source/net/ipv4/netfilter/ip_tables.c#L1809">1809</a> 
<a name="L1810" href="source/net/ipv4/netfilter/ip_tables.c#L1810">1810</a>         <b><i>/* overflow check */</i></b>
<a name="L1811" href="source/net/ipv4/netfilter/ip_tables.c#L1811">1811</a>         if (<a href="ident?i=tmp">tmp</a>.<a href="ident?i=size">size</a> &gt;= <a href="ident?i=INT_MAX">INT_MAX</a> / <a href="ident?i=num_possible_cpus">num_possible_cpus</a>())
<a name="L1812" href="source/net/ipv4/netfilter/ip_tables.c#L1812">1812</a>                 return -<a href="ident?i=ENOMEM">ENOMEM</a>;
<a name="L1813" href="source/net/ipv4/netfilter/ip_tables.c#L1813">1813</a>         if (<a href="ident?i=tmp">tmp</a>.<a href="ident?i=num_counters">num_counters</a> &gt;= <a href="ident?i=INT_MAX">INT_MAX</a> / sizeof(struct <a href="ident?i=xt_counters">xt_counters</a>))
<a name="L1814" href="source/net/ipv4/netfilter/ip_tables.c#L1814">1814</a>                 return -<a href="ident?i=ENOMEM">ENOMEM</a>;
<a name="L1815" href="source/net/ipv4/netfilter/ip_tables.c#L1815">1815</a>         if (<a href="ident?i=tmp">tmp</a>.<a href="ident?i=num_counters">num_counters</a> == 0)
<a name="L1816" href="source/net/ipv4/netfilter/ip_tables.c#L1816">1816</a>                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L1817" href="source/net/ipv4/netfilter/ip_tables.c#L1817">1817</a> 
<a name="L1818" href="source/net/ipv4/netfilter/ip_tables.c#L1818">1818</a>         <a href="ident?i=tmp">tmp</a>.<a href="ident?i=name">name</a>[sizeof(<a href="ident?i=tmp">tmp</a>.<a href="ident?i=name">name</a>)-1] = 0;
<a name="L1819" href="source/net/ipv4/netfilter/ip_tables.c#L1819">1819</a> 
<a name="L1820" href="source/net/ipv4/netfilter/ip_tables.c#L1820">1820</a>         newinfo = <a href="ident?i=xt_alloc_table_info">xt_alloc_table_info</a>(<a href="ident?i=tmp">tmp</a>.<a href="ident?i=size">size</a>);
<a name="L1821" href="source/net/ipv4/netfilter/ip_tables.c#L1821">1821</a>         if (!newinfo)
<a name="L1822" href="source/net/ipv4/netfilter/ip_tables.c#L1822">1822</a>                 return -<a href="ident?i=ENOMEM">ENOMEM</a>;
<a name="L1823" href="source/net/ipv4/netfilter/ip_tables.c#L1823">1823</a> 
<a name="L1824" href="source/net/ipv4/netfilter/ip_tables.c#L1824">1824</a>         <b><i>/* choose the copy that is on our node/cpu */</i></b>
<a name="L1825" href="source/net/ipv4/netfilter/ip_tables.c#L1825">1825</a>         loc_cpu_entry = newinfo-&gt;<a href="ident?i=entries">entries</a>[<a href="ident?i=raw_smp_processor_id">raw_smp_processor_id</a>()];
<a name="L1826" href="source/net/ipv4/netfilter/ip_tables.c#L1826">1826</a>         if (<a href="ident?i=copy_from_user">copy_from_user</a>(loc_cpu_entry, <a href="ident?i=user">user</a> + sizeof(<a href="ident?i=tmp">tmp</a>),
<a name="L1827" href="source/net/ipv4/netfilter/ip_tables.c#L1827">1827</a>                            <a href="ident?i=tmp">tmp</a>.<a href="ident?i=size">size</a>) != 0) {
<a name="L1828" href="source/net/ipv4/netfilter/ip_tables.c#L1828">1828</a>                 <a href="ident?i=ret">ret</a> = -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L1829" href="source/net/ipv4/netfilter/ip_tables.c#L1829">1829</a>                 goto free_newinfo;
<a name="L1830" href="source/net/ipv4/netfilter/ip_tables.c#L1830">1830</a>         }
<a name="L1831" href="source/net/ipv4/netfilter/ip_tables.c#L1831">1831</a> 
<a name="L1832" href="source/net/ipv4/netfilter/ip_tables.c#L1832">1832</a>         <a href="ident?i=ret">ret</a> = <a href="ident?i=translate_compat_table">translate_compat_table</a>(<a href="ident?i=net">net</a>, <a href="ident?i=tmp">tmp</a>.<a href="ident?i=name">name</a>, <a href="ident?i=tmp">tmp</a>.valid_hooks,
<a name="L1833" href="source/net/ipv4/netfilter/ip_tables.c#L1833">1833</a>                                      &amp;newinfo, &amp;loc_cpu_entry, <a href="ident?i=tmp">tmp</a>.<a href="ident?i=size">size</a>,
<a name="L1834" href="source/net/ipv4/netfilter/ip_tables.c#L1834">1834</a>                                      <a href="ident?i=tmp">tmp</a>.<a href="ident?i=num_entries">num_entries</a>, <a href="ident?i=tmp">tmp</a>.hook_entry,
<a name="L1835" href="source/net/ipv4/netfilter/ip_tables.c#L1835">1835</a>                                      <a href="ident?i=tmp">tmp</a>.underflow);
<a name="L1836" href="source/net/ipv4/netfilter/ip_tables.c#L1836">1836</a>         if (<a href="ident?i=ret">ret</a> != 0)
<a name="L1837" href="source/net/ipv4/netfilter/ip_tables.c#L1837">1837</a>                 goto free_newinfo;
<a name="L1838" href="source/net/ipv4/netfilter/ip_tables.c#L1838">1838</a> 
<a name="L1839" href="source/net/ipv4/netfilter/ip_tables.c#L1839">1839</a>         <a href="ident?i=duprintf">duprintf</a>(<i>"compat_do_replace: Translated table\n"</i>);
<a name="L1840" href="source/net/ipv4/netfilter/ip_tables.c#L1840">1840</a> 
<a name="L1841" href="source/net/ipv4/netfilter/ip_tables.c#L1841">1841</a>         <a href="ident?i=ret">ret</a> = <a href="ident?i=__do_replace">__do_replace</a>(<a href="ident?i=net">net</a>, <a href="ident?i=tmp">tmp</a>.<a href="ident?i=name">name</a>, <a href="ident?i=tmp">tmp</a>.valid_hooks, newinfo,
<a name="L1842" href="source/net/ipv4/netfilter/ip_tables.c#L1842">1842</a>                            <a href="ident?i=tmp">tmp</a>.<a href="ident?i=num_counters">num_counters</a>, <a href="ident?i=compat_ptr">compat_ptr</a>(<a href="ident?i=tmp">tmp</a>.counters));
<a name="L1843" href="source/net/ipv4/netfilter/ip_tables.c#L1843">1843</a>         if (<a href="ident?i=ret">ret</a>)
<a name="L1844" href="source/net/ipv4/netfilter/ip_tables.c#L1844">1844</a>                 goto free_newinfo_untrans;
<a name="L1845" href="source/net/ipv4/netfilter/ip_tables.c#L1845">1845</a>         return 0;
<a name="L1846" href="source/net/ipv4/netfilter/ip_tables.c#L1846">1846</a> 
<a name="L1847" href="source/net/ipv4/netfilter/ip_tables.c#L1847">1847</a>  free_newinfo_untrans:
<a name="L1848" href="source/net/ipv4/netfilter/ip_tables.c#L1848">1848</a>         <a href="ident?i=xt_entry_foreach">xt_entry_foreach</a>(iter, loc_cpu_entry, newinfo-&gt;<a href="ident?i=size">size</a>)
<a name="L1849" href="source/net/ipv4/netfilter/ip_tables.c#L1849">1849</a>                 <a href="ident?i=cleanup_entry">cleanup_entry</a>(iter, <a href="ident?i=net">net</a>);
<a name="L1850" href="source/net/ipv4/netfilter/ip_tables.c#L1850">1850</a>  free_newinfo:
<a name="L1851" href="source/net/ipv4/netfilter/ip_tables.c#L1851">1851</a>         <a href="ident?i=xt_free_table_info">xt_free_table_info</a>(newinfo);
<a name="L1852" href="source/net/ipv4/netfilter/ip_tables.c#L1852">1852</a>         return <a href="ident?i=ret">ret</a>;
<a name="L1853" href="source/net/ipv4/netfilter/ip_tables.c#L1853">1853</a> }
<a name="L1854" href="source/net/ipv4/netfilter/ip_tables.c#L1854">1854</a> 
<a name="L1855" href="source/net/ipv4/netfilter/ip_tables.c#L1855">1855</a> static int
<a name="L1856" href="source/net/ipv4/netfilter/ip_tables.c#L1856">1856</a> <a href="ident?i=compat_do_ipt_set_ctl">compat_do_ipt_set_ctl</a>(struct <a href="ident?i=sock">sock</a> *sk,  int <a href="ident?i=cmd">cmd</a>, void <a href="ident?i=__user">__user</a> *<a href="ident?i=user">user</a>,
<a name="L1857" href="source/net/ipv4/netfilter/ip_tables.c#L1857">1857</a>                       unsigned int <a href="ident?i=len">len</a>)
<a name="L1858" href="source/net/ipv4/netfilter/ip_tables.c#L1858">1858</a> {
<a name="L1859" href="source/net/ipv4/netfilter/ip_tables.c#L1859">1859</a>         int <a href="ident?i=ret">ret</a>;
<a name="L1860" href="source/net/ipv4/netfilter/ip_tables.c#L1860">1860</a> 
<a name="L1861" href="source/net/ipv4/netfilter/ip_tables.c#L1861">1861</a>         if (!<a href="ident?i=ns_capable">ns_capable</a>(<a href="ident?i=sock_net">sock_net</a>(sk)-&gt;<a href="ident?i=user_ns">user_ns</a>, <a href="ident?i=CAP_NET_ADMIN">CAP_NET_ADMIN</a>))
<a name="L1862" href="source/net/ipv4/netfilter/ip_tables.c#L1862">1862</a>                 return -<a href="ident?i=EPERM">EPERM</a>;
<a name="L1863" href="source/net/ipv4/netfilter/ip_tables.c#L1863">1863</a> 
<a name="L1864" href="source/net/ipv4/netfilter/ip_tables.c#L1864">1864</a>         switch (<a href="ident?i=cmd">cmd</a>) {
<a name="L1865" href="source/net/ipv4/netfilter/ip_tables.c#L1865">1865</a>         case <a href="ident?i=IPT_SO_SET_REPLACE">IPT_SO_SET_REPLACE</a>:
<a name="L1866" href="source/net/ipv4/netfilter/ip_tables.c#L1866">1866</a>                 <a href="ident?i=ret">ret</a> = <a href="ident?i=compat_do_replace">compat_do_replace</a>(<a href="ident?i=sock_net">sock_net</a>(sk), <a href="ident?i=user">user</a>, <a href="ident?i=len">len</a>);
<a name="L1867" href="source/net/ipv4/netfilter/ip_tables.c#L1867">1867</a>                 break;
<a name="L1868" href="source/net/ipv4/netfilter/ip_tables.c#L1868">1868</a> 
<a name="L1869" href="source/net/ipv4/netfilter/ip_tables.c#L1869">1869</a>         case <a href="ident?i=IPT_SO_SET_ADD_COUNTERS">IPT_SO_SET_ADD_COUNTERS</a>:
<a name="L1870" href="source/net/ipv4/netfilter/ip_tables.c#L1870">1870</a>                 <a href="ident?i=ret">ret</a> = <a href="ident?i=do_add_counters">do_add_counters</a>(<a href="ident?i=sock_net">sock_net</a>(sk), <a href="ident?i=user">user</a>, <a href="ident?i=len">len</a>, 1);
<a name="L1871" href="source/net/ipv4/netfilter/ip_tables.c#L1871">1871</a>                 break;
<a name="L1872" href="source/net/ipv4/netfilter/ip_tables.c#L1872">1872</a> 
<a name="L1873" href="source/net/ipv4/netfilter/ip_tables.c#L1873">1873</a>         default:
<a name="L1874" href="source/net/ipv4/netfilter/ip_tables.c#L1874">1874</a>                 <a href="ident?i=duprintf">duprintf</a>(<i>"do_ipt_set_ctl:  unknown request %i\n"</i>, <a href="ident?i=cmd">cmd</a>);
<a name="L1875" href="source/net/ipv4/netfilter/ip_tables.c#L1875">1875</a>                 <a href="ident?i=ret">ret</a> = -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L1876" href="source/net/ipv4/netfilter/ip_tables.c#L1876">1876</a>         }
<a name="L1877" href="source/net/ipv4/netfilter/ip_tables.c#L1877">1877</a> 
<a name="L1878" href="source/net/ipv4/netfilter/ip_tables.c#L1878">1878</a>         return <a href="ident?i=ret">ret</a>;
<a name="L1879" href="source/net/ipv4/netfilter/ip_tables.c#L1879">1879</a> }
<a name="L1880" href="source/net/ipv4/netfilter/ip_tables.c#L1880">1880</a> 
<a name="L1881" href="source/net/ipv4/netfilter/ip_tables.c#L1881">1881</a> struct <a href="ident?i=compat_ipt_get_entries">compat_ipt_get_entries</a> {
<a name="L1882" href="source/net/ipv4/netfilter/ip_tables.c#L1882">1882</a>         char <a href="ident?i=name">name</a>[<a href="ident?i=XT_TABLE_MAXNAMELEN">XT_TABLE_MAXNAMELEN</a>];
<a name="L1883" href="source/net/ipv4/netfilter/ip_tables.c#L1883">1883</a>         <a href="ident?i=compat_uint_t">compat_uint_t</a> <a href="ident?i=size">size</a>;
<a name="L1884" href="source/net/ipv4/netfilter/ip_tables.c#L1884">1884</a>         struct <a href="ident?i=compat_ipt_entry">compat_ipt_entry</a> entrytable[0];
<a name="L1885" href="source/net/ipv4/netfilter/ip_tables.c#L1885">1885</a> };
<a name="L1886" href="source/net/ipv4/netfilter/ip_tables.c#L1886">1886</a> 
<a name="L1887" href="source/net/ipv4/netfilter/ip_tables.c#L1887">1887</a> static int
<a name="L1888" href="source/net/ipv4/netfilter/ip_tables.c#L1888">1888</a> <a href="ident?i=compat_copy_entries_to_user">compat_copy_entries_to_user</a>(unsigned int <a href="ident?i=total_size">total_size</a>, struct <a href="ident?i=xt_table">xt_table</a> *<a href="ident?i=table">table</a>,
<a name="L1889" href="source/net/ipv4/netfilter/ip_tables.c#L1889">1889</a>                             void <a href="ident?i=__user">__user</a> *userptr)
<a name="L1890" href="source/net/ipv4/netfilter/ip_tables.c#L1890">1890</a> {
<a name="L1891" href="source/net/ipv4/netfilter/ip_tables.c#L1891">1891</a>         struct <a href="ident?i=xt_counters">xt_counters</a> *counters;
<a name="L1892" href="source/net/ipv4/netfilter/ip_tables.c#L1892">1892</a>         const struct <a href="ident?i=xt_table_info">xt_table_info</a> *<a href="ident?i=private">private</a> = <a href="ident?i=table">table</a>-&gt;<a href="ident?i=private">private</a>;
<a name="L1893" href="source/net/ipv4/netfilter/ip_tables.c#L1893">1893</a>         void <a href="ident?i=__user">__user</a> *<a href="ident?i=pos">pos</a>;
<a name="L1894" href="source/net/ipv4/netfilter/ip_tables.c#L1894">1894</a>         unsigned int <a href="ident?i=size">size</a>;
<a name="L1895" href="source/net/ipv4/netfilter/ip_tables.c#L1895">1895</a>         int <a href="ident?i=ret">ret</a> = 0;
<a name="L1896" href="source/net/ipv4/netfilter/ip_tables.c#L1896">1896</a>         const void *loc_cpu_entry;
<a name="L1897" href="source/net/ipv4/netfilter/ip_tables.c#L1897">1897</a>         unsigned int <a href="ident?i=i">i</a> = 0;
<a name="L1898" href="source/net/ipv4/netfilter/ip_tables.c#L1898">1898</a>         struct <a href="ident?i=ipt_entry">ipt_entry</a> *iter;
<a name="L1899" href="source/net/ipv4/netfilter/ip_tables.c#L1899">1899</a> 
<a name="L1900" href="source/net/ipv4/netfilter/ip_tables.c#L1900">1900</a>         counters = <a href="ident?i=alloc_counters">alloc_counters</a>(<a href="ident?i=table">table</a>);
<a name="L1901" href="source/net/ipv4/netfilter/ip_tables.c#L1901">1901</a>         if (<a href="ident?i=IS_ERR">IS_ERR</a>(counters))
<a name="L1902" href="source/net/ipv4/netfilter/ip_tables.c#L1902">1902</a>                 return <a href="ident?i=PTR_ERR">PTR_ERR</a>(counters);
<a name="L1903" href="source/net/ipv4/netfilter/ip_tables.c#L1903">1903</a> 
<a name="L1904" href="source/net/ipv4/netfilter/ip_tables.c#L1904">1904</a>         <b><i>/* choose the copy that is on our node/cpu, ...</i></b>
<a name="L1905" href="source/net/ipv4/netfilter/ip_tables.c#L1905">1905</a> <b><i>         * This choice is lazy (because current thread is</i></b>
<a name="L1906" href="source/net/ipv4/netfilter/ip_tables.c#L1906">1906</a> <b><i>         * allowed to migrate to another cpu)</i></b>
<a name="L1907" href="source/net/ipv4/netfilter/ip_tables.c#L1907">1907</a> <b><i>         */</i></b>
<a name="L1908" href="source/net/ipv4/netfilter/ip_tables.c#L1908">1908</a>         loc_cpu_entry = <a href="ident?i=private">private</a>-&gt;<a href="ident?i=entries">entries</a>[<a href="ident?i=raw_smp_processor_id">raw_smp_processor_id</a>()];
<a name="L1909" href="source/net/ipv4/netfilter/ip_tables.c#L1909">1909</a>         <a href="ident?i=pos">pos</a> = userptr;
<a name="L1910" href="source/net/ipv4/netfilter/ip_tables.c#L1910">1910</a>         <a href="ident?i=size">size</a> = <a href="ident?i=total_size">total_size</a>;
<a name="L1911" href="source/net/ipv4/netfilter/ip_tables.c#L1911">1911</a>         <a href="ident?i=xt_entry_foreach">xt_entry_foreach</a>(iter, loc_cpu_entry, <a href="ident?i=total_size">total_size</a>) {
<a name="L1912" href="source/net/ipv4/netfilter/ip_tables.c#L1912">1912</a>                 <a href="ident?i=ret">ret</a> = <a href="ident?i=compat_copy_entry_to_user">compat_copy_entry_to_user</a>(iter, &amp;<a href="ident?i=pos">pos</a>,
<a name="L1913" href="source/net/ipv4/netfilter/ip_tables.c#L1913">1913</a>                                                 &amp;<a href="ident?i=size">size</a>, counters, <a href="ident?i=i">i</a>++);
<a name="L1914" href="source/net/ipv4/netfilter/ip_tables.c#L1914">1914</a>                 if (<a href="ident?i=ret">ret</a> != 0)
<a name="L1915" href="source/net/ipv4/netfilter/ip_tables.c#L1915">1915</a>                         break;
<a name="L1916" href="source/net/ipv4/netfilter/ip_tables.c#L1916">1916</a>         }
<a name="L1917" href="source/net/ipv4/netfilter/ip_tables.c#L1917">1917</a> 
<a name="L1918" href="source/net/ipv4/netfilter/ip_tables.c#L1918">1918</a>         <a href="ident?i=vfree">vfree</a>(counters);
<a name="L1919" href="source/net/ipv4/netfilter/ip_tables.c#L1919">1919</a>         return <a href="ident?i=ret">ret</a>;
<a name="L1920" href="source/net/ipv4/netfilter/ip_tables.c#L1920">1920</a> }
<a name="L1921" href="source/net/ipv4/netfilter/ip_tables.c#L1921">1921</a> 
<a name="L1922" href="source/net/ipv4/netfilter/ip_tables.c#L1922">1922</a> static int
<a name="L1923" href="source/net/ipv4/netfilter/ip_tables.c#L1923">1923</a> <a href="ident?i=compat_get_entries">compat_get_entries</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>, struct <a href="ident?i=compat_ipt_get_entries">compat_ipt_get_entries</a> <a href="ident?i=__user">__user</a> *uptr,
<a name="L1924" href="source/net/ipv4/netfilter/ip_tables.c#L1924">1924</a>                    int *<a href="ident?i=len">len</a>)
<a name="L1925" href="source/net/ipv4/netfilter/ip_tables.c#L1925">1925</a> {
<a name="L1926" href="source/net/ipv4/netfilter/ip_tables.c#L1926">1926</a>         int <a href="ident?i=ret">ret</a>;
<a name="L1927" href="source/net/ipv4/netfilter/ip_tables.c#L1927">1927</a>         struct <a href="ident?i=compat_ipt_get_entries">compat_ipt_get_entries</a> <a href="ident?i=get">get</a>;
<a name="L1928" href="source/net/ipv4/netfilter/ip_tables.c#L1928">1928</a>         struct <a href="ident?i=xt_table">xt_table</a> *<a href="ident?i=t">t</a>;
<a name="L1929" href="source/net/ipv4/netfilter/ip_tables.c#L1929">1929</a> 
<a name="L1930" href="source/net/ipv4/netfilter/ip_tables.c#L1930">1930</a>         if (*<a href="ident?i=len">len</a> &lt; sizeof(<a href="ident?i=get">get</a>)) {
<a name="L1931" href="source/net/ipv4/netfilter/ip_tables.c#L1931">1931</a>                 <a href="ident?i=duprintf">duprintf</a>(<i>"compat_get_entries: %u &lt; %zu\n"</i>, *<a href="ident?i=len">len</a>, sizeof(<a href="ident?i=get">get</a>));
<a name="L1932" href="source/net/ipv4/netfilter/ip_tables.c#L1932">1932</a>                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L1933" href="source/net/ipv4/netfilter/ip_tables.c#L1933">1933</a>         }
<a name="L1934" href="source/net/ipv4/netfilter/ip_tables.c#L1934">1934</a> 
<a name="L1935" href="source/net/ipv4/netfilter/ip_tables.c#L1935">1935</a>         if (<a href="ident?i=copy_from_user">copy_from_user</a>(&amp;<a href="ident?i=get">get</a>, uptr, sizeof(<a href="ident?i=get">get</a>)) != 0)
<a name="L1936" href="source/net/ipv4/netfilter/ip_tables.c#L1936">1936</a>                 return -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L1937" href="source/net/ipv4/netfilter/ip_tables.c#L1937">1937</a> 
<a name="L1938" href="source/net/ipv4/netfilter/ip_tables.c#L1938">1938</a>         if (*<a href="ident?i=len">len</a> != sizeof(struct <a href="ident?i=compat_ipt_get_entries">compat_ipt_get_entries</a>) + <a href="ident?i=get">get</a>.<a href="ident?i=size">size</a>) {
<a name="L1939" href="source/net/ipv4/netfilter/ip_tables.c#L1939">1939</a>                 <a href="ident?i=duprintf">duprintf</a>(<i>"compat_get_entries: %u != %zu\n"</i>,
<a name="L1940" href="source/net/ipv4/netfilter/ip_tables.c#L1940">1940</a>                          *<a href="ident?i=len">len</a>, sizeof(<a href="ident?i=get">get</a>) + <a href="ident?i=get">get</a>.<a href="ident?i=size">size</a>);
<a name="L1941" href="source/net/ipv4/netfilter/ip_tables.c#L1941">1941</a>                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L1942" href="source/net/ipv4/netfilter/ip_tables.c#L1942">1942</a>         }
<a name="L1943" href="source/net/ipv4/netfilter/ip_tables.c#L1943">1943</a> 
<a name="L1944" href="source/net/ipv4/netfilter/ip_tables.c#L1944">1944</a>         <a href="ident?i=xt_compat_lock">xt_compat_lock</a>(<a href="ident?i=AF_INET">AF_INET</a>);
<a name="L1945" href="source/net/ipv4/netfilter/ip_tables.c#L1945">1945</a>         <a href="ident?i=t">t</a> = <a href="ident?i=xt_find_table_lock">xt_find_table_lock</a>(<a href="ident?i=net">net</a>, <a href="ident?i=AF_INET">AF_INET</a>, <a href="ident?i=get">get</a>.<a href="ident?i=name">name</a>);
<a name="L1946" href="source/net/ipv4/netfilter/ip_tables.c#L1946">1946</a>         if (!<a href="ident?i=IS_ERR_OR_NULL">IS_ERR_OR_NULL</a>(<a href="ident?i=t">t</a>)) {
<a name="L1947" href="source/net/ipv4/netfilter/ip_tables.c#L1947">1947</a>                 const struct <a href="ident?i=xt_table_info">xt_table_info</a> *<a href="ident?i=private">private</a> = <a href="ident?i=t">t</a>-&gt;<a href="ident?i=private">private</a>;
<a name="L1948" href="source/net/ipv4/netfilter/ip_tables.c#L1948">1948</a>                 struct <a href="ident?i=xt_table_info">xt_table_info</a> <a href="ident?i=info">info</a>;
<a name="L1949" href="source/net/ipv4/netfilter/ip_tables.c#L1949">1949</a>                 <a href="ident?i=duprintf">duprintf</a>(<i>"t-&gt;private-&gt;number = %u\n"</i>, <a href="ident?i=private">private</a>-&gt;<a href="ident?i=number">number</a>);
<a name="L1950" href="source/net/ipv4/netfilter/ip_tables.c#L1950">1950</a>                 <a href="ident?i=ret">ret</a> = <a href="ident?i=compat_table_info">compat_table_info</a>(<a href="ident?i=private">private</a>, &amp;<a href="ident?i=info">info</a>);
<a name="L1951" href="source/net/ipv4/netfilter/ip_tables.c#L1951">1951</a>                 if (!<a href="ident?i=ret">ret</a> &amp;&amp; <a href="ident?i=get">get</a>.<a href="ident?i=size">size</a> == <a href="ident?i=info">info</a>.<a href="ident?i=size">size</a>) {
<a name="L1952" href="source/net/ipv4/netfilter/ip_tables.c#L1952">1952</a>                         <a href="ident?i=ret">ret</a> = <a href="ident?i=compat_copy_entries_to_user">compat_copy_entries_to_user</a>(<a href="ident?i=private">private</a>-&gt;<a href="ident?i=size">size</a>,
<a name="L1953" href="source/net/ipv4/netfilter/ip_tables.c#L1953">1953</a>                                                           <a href="ident?i=t">t</a>, uptr-&gt;entrytable);
<a name="L1954" href="source/net/ipv4/netfilter/ip_tables.c#L1954">1954</a>                 } else if (!<a href="ident?i=ret">ret</a>) {
<a name="L1955" href="source/net/ipv4/netfilter/ip_tables.c#L1955">1955</a>                         <a href="ident?i=duprintf">duprintf</a>(<i>"compat_get_entries: I've got %u not %u!\n"</i>,
<a name="L1956" href="source/net/ipv4/netfilter/ip_tables.c#L1956">1956</a>                                  <a href="ident?i=private">private</a>-&gt;<a href="ident?i=size">size</a>, <a href="ident?i=get">get</a>.<a href="ident?i=size">size</a>);
<a name="L1957" href="source/net/ipv4/netfilter/ip_tables.c#L1957">1957</a>                         <a href="ident?i=ret">ret</a> = -<a href="ident?i=EAGAIN">EAGAIN</a>;
<a name="L1958" href="source/net/ipv4/netfilter/ip_tables.c#L1958">1958</a>                 }
<a name="L1959" href="source/net/ipv4/netfilter/ip_tables.c#L1959">1959</a>                 <a href="ident?i=xt_compat_flush_offsets">xt_compat_flush_offsets</a>(<a href="ident?i=AF_INET">AF_INET</a>);
<a name="L1960" href="source/net/ipv4/netfilter/ip_tables.c#L1960">1960</a>                 <a href="ident?i=module_put">module_put</a>(<a href="ident?i=t">t</a>-&gt;<a href="ident?i=me">me</a>);
<a name="L1961" href="source/net/ipv4/netfilter/ip_tables.c#L1961">1961</a>                 <a href="ident?i=xt_table_unlock">xt_table_unlock</a>(<a href="ident?i=t">t</a>);
<a name="L1962" href="source/net/ipv4/netfilter/ip_tables.c#L1962">1962</a>         } else
<a name="L1963" href="source/net/ipv4/netfilter/ip_tables.c#L1963">1963</a>                 <a href="ident?i=ret">ret</a> = <a href="ident?i=t">t</a> ? <a href="ident?i=PTR_ERR">PTR_ERR</a>(<a href="ident?i=t">t</a>) : -<a href="ident?i=ENOENT">ENOENT</a>;
<a name="L1964" href="source/net/ipv4/netfilter/ip_tables.c#L1964">1964</a> 
<a name="L1965" href="source/net/ipv4/netfilter/ip_tables.c#L1965">1965</a>         <a href="ident?i=xt_compat_unlock">xt_compat_unlock</a>(<a href="ident?i=AF_INET">AF_INET</a>);
<a name="L1966" href="source/net/ipv4/netfilter/ip_tables.c#L1966">1966</a>         return <a href="ident?i=ret">ret</a>;
<a name="L1967" href="source/net/ipv4/netfilter/ip_tables.c#L1967">1967</a> }
<a name="L1968" href="source/net/ipv4/netfilter/ip_tables.c#L1968">1968</a> 
<a name="L1969" href="source/net/ipv4/netfilter/ip_tables.c#L1969">1969</a> static int <a href="ident?i=do_ipt_get_ctl">do_ipt_get_ctl</a>(struct <a href="ident?i=sock">sock</a> *, int, void <a href="ident?i=__user">__user</a> *, int *);
<a name="L1970" href="source/net/ipv4/netfilter/ip_tables.c#L1970">1970</a> 
<a name="L1971" href="source/net/ipv4/netfilter/ip_tables.c#L1971">1971</a> static int
<a name="L1972" href="source/net/ipv4/netfilter/ip_tables.c#L1972">1972</a> <a href="ident?i=compat_do_ipt_get_ctl">compat_do_ipt_get_ctl</a>(struct <a href="ident?i=sock">sock</a> *sk, int <a href="ident?i=cmd">cmd</a>, void <a href="ident?i=__user">__user</a> *<a href="ident?i=user">user</a>, int *<a href="ident?i=len">len</a>)
<a name="L1973" href="source/net/ipv4/netfilter/ip_tables.c#L1973">1973</a> {
<a name="L1974" href="source/net/ipv4/netfilter/ip_tables.c#L1974">1974</a>         int <a href="ident?i=ret">ret</a>;
<a name="L1975" href="source/net/ipv4/netfilter/ip_tables.c#L1975">1975</a> 
<a name="L1976" href="source/net/ipv4/netfilter/ip_tables.c#L1976">1976</a>         if (!<a href="ident?i=ns_capable">ns_capable</a>(<a href="ident?i=sock_net">sock_net</a>(sk)-&gt;<a href="ident?i=user_ns">user_ns</a>, <a href="ident?i=CAP_NET_ADMIN">CAP_NET_ADMIN</a>))
<a name="L1977" href="source/net/ipv4/netfilter/ip_tables.c#L1977">1977</a>                 return -<a href="ident?i=EPERM">EPERM</a>;
<a name="L1978" href="source/net/ipv4/netfilter/ip_tables.c#L1978">1978</a> 
<a name="L1979" href="source/net/ipv4/netfilter/ip_tables.c#L1979">1979</a>         switch (<a href="ident?i=cmd">cmd</a>) {
<a name="L1980" href="source/net/ipv4/netfilter/ip_tables.c#L1980">1980</a>         case <a href="ident?i=IPT_SO_GET_INFO">IPT_SO_GET_INFO</a>:
<a name="L1981" href="source/net/ipv4/netfilter/ip_tables.c#L1981">1981</a>                 <a href="ident?i=ret">ret</a> = <a href="ident?i=get_info">get_info</a>(<a href="ident?i=sock_net">sock_net</a>(sk), <a href="ident?i=user">user</a>, <a href="ident?i=len">len</a>, 1);
<a name="L1982" href="source/net/ipv4/netfilter/ip_tables.c#L1982">1982</a>                 break;
<a name="L1983" href="source/net/ipv4/netfilter/ip_tables.c#L1983">1983</a>         case <a href="ident?i=IPT_SO_GET_ENTRIES">IPT_SO_GET_ENTRIES</a>:
<a name="L1984" href="source/net/ipv4/netfilter/ip_tables.c#L1984">1984</a>                 <a href="ident?i=ret">ret</a> = <a href="ident?i=compat_get_entries">compat_get_entries</a>(<a href="ident?i=sock_net">sock_net</a>(sk), <a href="ident?i=user">user</a>, <a href="ident?i=len">len</a>);
<a name="L1985" href="source/net/ipv4/netfilter/ip_tables.c#L1985">1985</a>                 break;
<a name="L1986" href="source/net/ipv4/netfilter/ip_tables.c#L1986">1986</a>         default:
<a name="L1987" href="source/net/ipv4/netfilter/ip_tables.c#L1987">1987</a>                 <a href="ident?i=ret">ret</a> = <a href="ident?i=do_ipt_get_ctl">do_ipt_get_ctl</a>(sk, <a href="ident?i=cmd">cmd</a>, <a href="ident?i=user">user</a>, <a href="ident?i=len">len</a>);
<a name="L1988" href="source/net/ipv4/netfilter/ip_tables.c#L1988">1988</a>         }
<a name="L1989" href="source/net/ipv4/netfilter/ip_tables.c#L1989">1989</a>         return <a href="ident?i=ret">ret</a>;
<a name="L1990" href="source/net/ipv4/netfilter/ip_tables.c#L1990">1990</a> }
<a name="L1991" href="source/net/ipv4/netfilter/ip_tables.c#L1991">1991</a> #endif
<a name="L1992" href="source/net/ipv4/netfilter/ip_tables.c#L1992">1992</a> 
<a name="L1993" href="source/net/ipv4/netfilter/ip_tables.c#L1993">1993</a> static int
<a name="L1994" href="source/net/ipv4/netfilter/ip_tables.c#L1994">1994</a> <a href="ident?i=do_ipt_set_ctl">do_ipt_set_ctl</a>(struct <a href="ident?i=sock">sock</a> *sk, int <a href="ident?i=cmd">cmd</a>, void <a href="ident?i=__user">__user</a> *<a href="ident?i=user">user</a>, unsigned int <a href="ident?i=len">len</a>)
<a name="L1995" href="source/net/ipv4/netfilter/ip_tables.c#L1995">1995</a> {
<a name="L1996" href="source/net/ipv4/netfilter/ip_tables.c#L1996">1996</a>         int <a href="ident?i=ret">ret</a>;
<a name="L1997" href="source/net/ipv4/netfilter/ip_tables.c#L1997">1997</a> 
<a name="L1998" href="source/net/ipv4/netfilter/ip_tables.c#L1998">1998</a>         if (!<a href="ident?i=ns_capable">ns_capable</a>(<a href="ident?i=sock_net">sock_net</a>(sk)-&gt;<a href="ident?i=user_ns">user_ns</a>, <a href="ident?i=CAP_NET_ADMIN">CAP_NET_ADMIN</a>))
<a name="L1999" href="source/net/ipv4/netfilter/ip_tables.c#L1999">1999</a>                 return -<a href="ident?i=EPERM">EPERM</a>;
<a name="L2000" href="source/net/ipv4/netfilter/ip_tables.c#L2000">2000</a> 
<a name="L2001" href="source/net/ipv4/netfilter/ip_tables.c#L2001">2001</a>         switch (<a href="ident?i=cmd">cmd</a>) {
<a name="L2002" href="source/net/ipv4/netfilter/ip_tables.c#L2002">2002</a>         case <a href="ident?i=IPT_SO_SET_REPLACE">IPT_SO_SET_REPLACE</a>:
<a name="L2003" href="source/net/ipv4/netfilter/ip_tables.c#L2003">2003</a>                 <a href="ident?i=ret">ret</a> = <a href="ident?i=do_replace">do_replace</a>(<a href="ident?i=sock_net">sock_net</a>(sk), <a href="ident?i=user">user</a>, <a href="ident?i=len">len</a>);
<a name="L2004" href="source/net/ipv4/netfilter/ip_tables.c#L2004">2004</a>                 break;
<a name="L2005" href="source/net/ipv4/netfilter/ip_tables.c#L2005">2005</a> 
<a name="L2006" href="source/net/ipv4/netfilter/ip_tables.c#L2006">2006</a>         case <a href="ident?i=IPT_SO_SET_ADD_COUNTERS">IPT_SO_SET_ADD_COUNTERS</a>:
<a name="L2007" href="source/net/ipv4/netfilter/ip_tables.c#L2007">2007</a>                 <a href="ident?i=ret">ret</a> = <a href="ident?i=do_add_counters">do_add_counters</a>(<a href="ident?i=sock_net">sock_net</a>(sk), <a href="ident?i=user">user</a>, <a href="ident?i=len">len</a>, 0);
<a name="L2008" href="source/net/ipv4/netfilter/ip_tables.c#L2008">2008</a>                 break;
<a name="L2009" href="source/net/ipv4/netfilter/ip_tables.c#L2009">2009</a> 
<a name="L2010" href="source/net/ipv4/netfilter/ip_tables.c#L2010">2010</a>         default:
<a name="L2011" href="source/net/ipv4/netfilter/ip_tables.c#L2011">2011</a>                 <a href="ident?i=duprintf">duprintf</a>(<i>"do_ipt_set_ctl:  unknown request %i\n"</i>, <a href="ident?i=cmd">cmd</a>);
<a name="L2012" href="source/net/ipv4/netfilter/ip_tables.c#L2012">2012</a>                 <a href="ident?i=ret">ret</a> = -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L2013" href="source/net/ipv4/netfilter/ip_tables.c#L2013">2013</a>         }
<a name="L2014" href="source/net/ipv4/netfilter/ip_tables.c#L2014">2014</a> 
<a name="L2015" href="source/net/ipv4/netfilter/ip_tables.c#L2015">2015</a>         return <a href="ident?i=ret">ret</a>;
<a name="L2016" href="source/net/ipv4/netfilter/ip_tables.c#L2016">2016</a> }
<a name="L2017" href="source/net/ipv4/netfilter/ip_tables.c#L2017">2017</a> 
<a name="L2018" href="source/net/ipv4/netfilter/ip_tables.c#L2018">2018</a> static int
<a name="L2019" href="source/net/ipv4/netfilter/ip_tables.c#L2019">2019</a> <a href="ident?i=do_ipt_get_ctl">do_ipt_get_ctl</a>(struct <a href="ident?i=sock">sock</a> *sk, int <a href="ident?i=cmd">cmd</a>, void <a href="ident?i=__user">__user</a> *<a href="ident?i=user">user</a>, int *<a href="ident?i=len">len</a>)
<a name="L2020" href="source/net/ipv4/netfilter/ip_tables.c#L2020">2020</a> {
<a name="L2021" href="source/net/ipv4/netfilter/ip_tables.c#L2021">2021</a>         int <a href="ident?i=ret">ret</a>;
<a name="L2022" href="source/net/ipv4/netfilter/ip_tables.c#L2022">2022</a> 
<a name="L2023" href="source/net/ipv4/netfilter/ip_tables.c#L2023">2023</a>         if (!<a href="ident?i=ns_capable">ns_capable</a>(<a href="ident?i=sock_net">sock_net</a>(sk)-&gt;<a href="ident?i=user_ns">user_ns</a>, <a href="ident?i=CAP_NET_ADMIN">CAP_NET_ADMIN</a>))
<a name="L2024" href="source/net/ipv4/netfilter/ip_tables.c#L2024">2024</a>                 return -<a href="ident?i=EPERM">EPERM</a>;
<a name="L2025" href="source/net/ipv4/netfilter/ip_tables.c#L2025">2025</a> 
<a name="L2026" href="source/net/ipv4/netfilter/ip_tables.c#L2026">2026</a>         switch (<a href="ident?i=cmd">cmd</a>) {
<a name="L2027" href="source/net/ipv4/netfilter/ip_tables.c#L2027">2027</a>         case <a href="ident?i=IPT_SO_GET_INFO">IPT_SO_GET_INFO</a>:
<a name="L2028" href="source/net/ipv4/netfilter/ip_tables.c#L2028">2028</a>                 <a href="ident?i=ret">ret</a> = <a href="ident?i=get_info">get_info</a>(<a href="ident?i=sock_net">sock_net</a>(sk), <a href="ident?i=user">user</a>, <a href="ident?i=len">len</a>, 0);
<a name="L2029" href="source/net/ipv4/netfilter/ip_tables.c#L2029">2029</a>                 break;
<a name="L2030" href="source/net/ipv4/netfilter/ip_tables.c#L2030">2030</a> 
<a name="L2031" href="source/net/ipv4/netfilter/ip_tables.c#L2031">2031</a>         case <a href="ident?i=IPT_SO_GET_ENTRIES">IPT_SO_GET_ENTRIES</a>:
<a name="L2032" href="source/net/ipv4/netfilter/ip_tables.c#L2032">2032</a>                 <a href="ident?i=ret">ret</a> = <a href="ident?i=get_entries">get_entries</a>(<a href="ident?i=sock_net">sock_net</a>(sk), <a href="ident?i=user">user</a>, <a href="ident?i=len">len</a>);
<a name="L2033" href="source/net/ipv4/netfilter/ip_tables.c#L2033">2033</a>                 break;
<a name="L2034" href="source/net/ipv4/netfilter/ip_tables.c#L2034">2034</a> 
<a name="L2035" href="source/net/ipv4/netfilter/ip_tables.c#L2035">2035</a>         case <a href="ident?i=IPT_SO_GET_REVISION_MATCH">IPT_SO_GET_REVISION_MATCH</a>:
<a name="L2036" href="source/net/ipv4/netfilter/ip_tables.c#L2036">2036</a>         case <a href="ident?i=IPT_SO_GET_REVISION_TARGET">IPT_SO_GET_REVISION_TARGET</a>: {
<a name="L2037" href="source/net/ipv4/netfilter/ip_tables.c#L2037">2037</a>                 struct <a href="ident?i=xt_get_revision">xt_get_revision</a> rev;
<a name="L2038" href="source/net/ipv4/netfilter/ip_tables.c#L2038">2038</a>                 int <a href="ident?i=target">target</a>;
<a name="L2039" href="source/net/ipv4/netfilter/ip_tables.c#L2039">2039</a> 
<a name="L2040" href="source/net/ipv4/netfilter/ip_tables.c#L2040">2040</a>                 if (*<a href="ident?i=len">len</a> != sizeof(rev)) {
<a name="L2041" href="source/net/ipv4/netfilter/ip_tables.c#L2041">2041</a>                         <a href="ident?i=ret">ret</a> = -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L2042" href="source/net/ipv4/netfilter/ip_tables.c#L2042">2042</a>                         break;
<a name="L2043" href="source/net/ipv4/netfilter/ip_tables.c#L2043">2043</a>                 }
<a name="L2044" href="source/net/ipv4/netfilter/ip_tables.c#L2044">2044</a>                 if (<a href="ident?i=copy_from_user">copy_from_user</a>(&amp;rev, <a href="ident?i=user">user</a>, sizeof(rev)) != 0) {
<a name="L2045" href="source/net/ipv4/netfilter/ip_tables.c#L2045">2045</a>                         <a href="ident?i=ret">ret</a> = -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L2046" href="source/net/ipv4/netfilter/ip_tables.c#L2046">2046</a>                         break;
<a name="L2047" href="source/net/ipv4/netfilter/ip_tables.c#L2047">2047</a>                 }
<a name="L2048" href="source/net/ipv4/netfilter/ip_tables.c#L2048">2048</a>                 rev.<a href="ident?i=name">name</a>[sizeof(rev.<a href="ident?i=name">name</a>)-1] = 0;
<a name="L2049" href="source/net/ipv4/netfilter/ip_tables.c#L2049">2049</a> 
<a name="L2050" href="source/net/ipv4/netfilter/ip_tables.c#L2050">2050</a>                 if (<a href="ident?i=cmd">cmd</a> == <a href="ident?i=IPT_SO_GET_REVISION_TARGET">IPT_SO_GET_REVISION_TARGET</a>)
<a name="L2051" href="source/net/ipv4/netfilter/ip_tables.c#L2051">2051</a>                         <a href="ident?i=target">target</a> = 1;
<a name="L2052" href="source/net/ipv4/netfilter/ip_tables.c#L2052">2052</a>                 else
<a name="L2053" href="source/net/ipv4/netfilter/ip_tables.c#L2053">2053</a>                         <a href="ident?i=target">target</a> = 0;
<a name="L2054" href="source/net/ipv4/netfilter/ip_tables.c#L2054">2054</a> 
<a name="L2055" href="source/net/ipv4/netfilter/ip_tables.c#L2055">2055</a>                 <a href="ident?i=try_then_request_module">try_then_request_module</a>(<a href="ident?i=xt_find_revision">xt_find_revision</a>(<a href="ident?i=AF_INET">AF_INET</a>, rev.<a href="ident?i=name">name</a>,
<a name="L2056" href="source/net/ipv4/netfilter/ip_tables.c#L2056">2056</a>                                                          rev.<a href="ident?i=revision">revision</a>,
<a name="L2057" href="source/net/ipv4/netfilter/ip_tables.c#L2057">2057</a>                                                          <a href="ident?i=target">target</a>, &amp;<a href="ident?i=ret">ret</a>),
<a name="L2058" href="source/net/ipv4/netfilter/ip_tables.c#L2058">2058</a>                                         <i>"ipt_%s"</i>, rev.<a href="ident?i=name">name</a>);
<a name="L2059" href="source/net/ipv4/netfilter/ip_tables.c#L2059">2059</a>                 break;
<a name="L2060" href="source/net/ipv4/netfilter/ip_tables.c#L2060">2060</a>         }
<a name="L2061" href="source/net/ipv4/netfilter/ip_tables.c#L2061">2061</a> 
<a name="L2062" href="source/net/ipv4/netfilter/ip_tables.c#L2062">2062</a>         default:
<a name="L2063" href="source/net/ipv4/netfilter/ip_tables.c#L2063">2063</a>                 <a href="ident?i=duprintf">duprintf</a>(<i>"do_ipt_get_ctl: unknown request %i\n"</i>, <a href="ident?i=cmd">cmd</a>);
<a name="L2064" href="source/net/ipv4/netfilter/ip_tables.c#L2064">2064</a>                 <a href="ident?i=ret">ret</a> = -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L2065" href="source/net/ipv4/netfilter/ip_tables.c#L2065">2065</a>         }
<a name="L2066" href="source/net/ipv4/netfilter/ip_tables.c#L2066">2066</a> 
<a name="L2067" href="source/net/ipv4/netfilter/ip_tables.c#L2067">2067</a>         return <a href="ident?i=ret">ret</a>;
<a name="L2068" href="source/net/ipv4/netfilter/ip_tables.c#L2068">2068</a> }
<a name="L2069" href="source/net/ipv4/netfilter/ip_tables.c#L2069">2069</a> 
<a name="L2070" href="source/net/ipv4/netfilter/ip_tables.c#L2070">2070</a> struct <a href="ident?i=xt_table">xt_table</a> *<a href="ident?i=ipt_register_table">ipt_register_table</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>,
<a name="L2071" href="source/net/ipv4/netfilter/ip_tables.c#L2071">2071</a>                                     const struct <a href="ident?i=xt_table">xt_table</a> *<a href="ident?i=table">table</a>,
<a name="L2072" href="source/net/ipv4/netfilter/ip_tables.c#L2072">2072</a>                                     const struct <a href="ident?i=ipt_replace">ipt_replace</a> *repl)
<a name="L2073" href="source/net/ipv4/netfilter/ip_tables.c#L2073">2073</a> {
<a name="L2074" href="source/net/ipv4/netfilter/ip_tables.c#L2074">2074</a>         int <a href="ident?i=ret">ret</a>;
<a name="L2075" href="source/net/ipv4/netfilter/ip_tables.c#L2075">2075</a>         struct <a href="ident?i=xt_table_info">xt_table_info</a> *newinfo;
<a name="L2076" href="source/net/ipv4/netfilter/ip_tables.c#L2076">2076</a>         struct <a href="ident?i=xt_table_info">xt_table_info</a> <a href="ident?i=bootstrap">bootstrap</a> = {0};
<a name="L2077" href="source/net/ipv4/netfilter/ip_tables.c#L2077">2077</a>         void *loc_cpu_entry;
<a name="L2078" href="source/net/ipv4/netfilter/ip_tables.c#L2078">2078</a>         struct <a href="ident?i=xt_table">xt_table</a> *new_table;
<a name="L2079" href="source/net/ipv4/netfilter/ip_tables.c#L2079">2079</a> 
<a name="L2080" href="source/net/ipv4/netfilter/ip_tables.c#L2080">2080</a>         newinfo = <a href="ident?i=xt_alloc_table_info">xt_alloc_table_info</a>(repl-&gt;<a href="ident?i=size">size</a>);
<a name="L2081" href="source/net/ipv4/netfilter/ip_tables.c#L2081">2081</a>         if (!newinfo) {
<a name="L2082" href="source/net/ipv4/netfilter/ip_tables.c#L2082">2082</a>                 <a href="ident?i=ret">ret</a> = -<a href="ident?i=ENOMEM">ENOMEM</a>;
<a name="L2083" href="source/net/ipv4/netfilter/ip_tables.c#L2083">2083</a>                 goto <a href="ident?i=out">out</a>;
<a name="L2084" href="source/net/ipv4/netfilter/ip_tables.c#L2084">2084</a>         }
<a name="L2085" href="source/net/ipv4/netfilter/ip_tables.c#L2085">2085</a> 
<a name="L2086" href="source/net/ipv4/netfilter/ip_tables.c#L2086">2086</a>         <b><i>/* choose the copy on our node/cpu, but dont care about preemption */</i></b>
<a name="L2087" href="source/net/ipv4/netfilter/ip_tables.c#L2087">2087</a>         loc_cpu_entry = newinfo-&gt;<a href="ident?i=entries">entries</a>[<a href="ident?i=raw_smp_processor_id">raw_smp_processor_id</a>()];
<a name="L2088" href="source/net/ipv4/netfilter/ip_tables.c#L2088">2088</a>         <a href="ident?i=memcpy">memcpy</a>(loc_cpu_entry, repl-&gt;<a href="ident?i=entries">entries</a>, repl-&gt;<a href="ident?i=size">size</a>);
<a name="L2089" href="source/net/ipv4/netfilter/ip_tables.c#L2089">2089</a> 
<a name="L2090" href="source/net/ipv4/netfilter/ip_tables.c#L2090">2090</a>         <a href="ident?i=ret">ret</a> = <a href="ident?i=translate_table">translate_table</a>(<a href="ident?i=net">net</a>, newinfo, loc_cpu_entry, repl);
<a name="L2091" href="source/net/ipv4/netfilter/ip_tables.c#L2091">2091</a>         if (<a href="ident?i=ret">ret</a> != 0)
<a name="L2092" href="source/net/ipv4/netfilter/ip_tables.c#L2092">2092</a>                 goto out_free;
<a name="L2093" href="source/net/ipv4/netfilter/ip_tables.c#L2093">2093</a> 
<a name="L2094" href="source/net/ipv4/netfilter/ip_tables.c#L2094">2094</a>         new_table = <a href="ident?i=xt_register_table">xt_register_table</a>(<a href="ident?i=net">net</a>, <a href="ident?i=table">table</a>, &amp;<a href="ident?i=bootstrap">bootstrap</a>, newinfo);
<a name="L2095" href="source/net/ipv4/netfilter/ip_tables.c#L2095">2095</a>         if (<a href="ident?i=IS_ERR">IS_ERR</a>(new_table)) {
<a name="L2096" href="source/net/ipv4/netfilter/ip_tables.c#L2096">2096</a>                 <a href="ident?i=ret">ret</a> = <a href="ident?i=PTR_ERR">PTR_ERR</a>(new_table);
<a name="L2097" href="source/net/ipv4/netfilter/ip_tables.c#L2097">2097</a>                 goto out_free;
<a name="L2098" href="source/net/ipv4/netfilter/ip_tables.c#L2098">2098</a>         }
<a name="L2099" href="source/net/ipv4/netfilter/ip_tables.c#L2099">2099</a> 
<a name="L2100" href="source/net/ipv4/netfilter/ip_tables.c#L2100">2100</a>         return new_table;
<a name="L2101" href="source/net/ipv4/netfilter/ip_tables.c#L2101">2101</a> 
<a name="L2102" href="source/net/ipv4/netfilter/ip_tables.c#L2102">2102</a> out_free:
<a name="L2103" href="source/net/ipv4/netfilter/ip_tables.c#L2103">2103</a>         <a href="ident?i=xt_free_table_info">xt_free_table_info</a>(newinfo);
<a name="L2104" href="source/net/ipv4/netfilter/ip_tables.c#L2104">2104</a> <a href="ident?i=out">out</a>:
<a name="L2105" href="source/net/ipv4/netfilter/ip_tables.c#L2105">2105</a>         return <a href="ident?i=ERR_PTR">ERR_PTR</a>(<a href="ident?i=ret">ret</a>);
<a name="L2106" href="source/net/ipv4/netfilter/ip_tables.c#L2106">2106</a> }
<a name="L2107" href="source/net/ipv4/netfilter/ip_tables.c#L2107">2107</a> 
<a name="L2108" href="source/net/ipv4/netfilter/ip_tables.c#L2108">2108</a> void <a href="ident?i=ipt_unregister_table">ipt_unregister_table</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>, struct <a href="ident?i=xt_table">xt_table</a> *<a href="ident?i=table">table</a>)
<a name="L2109" href="source/net/ipv4/netfilter/ip_tables.c#L2109">2109</a> {
<a name="L2110" href="source/net/ipv4/netfilter/ip_tables.c#L2110">2110</a>         struct <a href="ident?i=xt_table_info">xt_table_info</a> *<a href="ident?i=private">private</a>;
<a name="L2111" href="source/net/ipv4/netfilter/ip_tables.c#L2111">2111</a>         void *loc_cpu_entry;
<a name="L2112" href="source/net/ipv4/netfilter/ip_tables.c#L2112">2112</a>         struct <a href="ident?i=module">module</a> *table_owner = <a href="ident?i=table">table</a>-&gt;<a href="ident?i=me">me</a>;
<a name="L2113" href="source/net/ipv4/netfilter/ip_tables.c#L2113">2113</a>         struct <a href="ident?i=ipt_entry">ipt_entry</a> *iter;
<a name="L2114" href="source/net/ipv4/netfilter/ip_tables.c#L2114">2114</a> 
<a name="L2115" href="source/net/ipv4/netfilter/ip_tables.c#L2115">2115</a>         <a href="ident?i=private">private</a> = <a href="ident?i=xt_unregister_table">xt_unregister_table</a>(<a href="ident?i=table">table</a>);
<a name="L2116" href="source/net/ipv4/netfilter/ip_tables.c#L2116">2116</a> 
<a name="L2117" href="source/net/ipv4/netfilter/ip_tables.c#L2117">2117</a>         <b><i>/* Decrease module usage counts and free resources */</i></b>
<a name="L2118" href="source/net/ipv4/netfilter/ip_tables.c#L2118">2118</a>         loc_cpu_entry = <a href="ident?i=private">private</a>-&gt;<a href="ident?i=entries">entries</a>[<a href="ident?i=raw_smp_processor_id">raw_smp_processor_id</a>()];
<a name="L2119" href="source/net/ipv4/netfilter/ip_tables.c#L2119">2119</a>         <a href="ident?i=xt_entry_foreach">xt_entry_foreach</a>(iter, loc_cpu_entry, <a href="ident?i=private">private</a>-&gt;<a href="ident?i=size">size</a>)
<a name="L2120" href="source/net/ipv4/netfilter/ip_tables.c#L2120">2120</a>                 <a href="ident?i=cleanup_entry">cleanup_entry</a>(iter, <a href="ident?i=net">net</a>);
<a name="L2121" href="source/net/ipv4/netfilter/ip_tables.c#L2121">2121</a>         if (<a href="ident?i=private">private</a>-&gt;<a href="ident?i=number">number</a> &gt; <a href="ident?i=private">private</a>-&gt;initial_entries)
<a name="L2122" href="source/net/ipv4/netfilter/ip_tables.c#L2122">2122</a>                 <a href="ident?i=module_put">module_put</a>(table_owner);
<a name="L2123" href="source/net/ipv4/netfilter/ip_tables.c#L2123">2123</a>         <a href="ident?i=xt_free_table_info">xt_free_table_info</a>(<a href="ident?i=private">private</a>);
<a name="L2124" href="source/net/ipv4/netfilter/ip_tables.c#L2124">2124</a> }
<a name="L2125" href="source/net/ipv4/netfilter/ip_tables.c#L2125">2125</a> 
<a name="L2126" href="source/net/ipv4/netfilter/ip_tables.c#L2126">2126</a> <b><i>/* Returns 1 if the type and code is matched by the range, 0 otherwise */</i></b>
<a name="L2127" href="source/net/ipv4/netfilter/ip_tables.c#L2127">2127</a> static inline <a href="ident?i=bool">bool</a>
<a name="L2128" href="source/net/ipv4/netfilter/ip_tables.c#L2128">2128</a> <a href="ident?i=icmp_type_code_match">icmp_type_code_match</a>(<a href="ident?i=u_int8_t">u_int8_t</a> <a href="ident?i=test_type">test_type</a>, <a href="ident?i=u_int8_t">u_int8_t</a> min_code, <a href="ident?i=u_int8_t">u_int8_t</a> max_code,
<a name="L2129" href="source/net/ipv4/netfilter/ip_tables.c#L2129">2129</a>                      <a href="ident?i=u_int8_t">u_int8_t</a> <a href="ident?i=type">type</a>, <a href="ident?i=u_int8_t">u_int8_t</a> <a href="ident?i=code">code</a>,
<a name="L2130" href="source/net/ipv4/netfilter/ip_tables.c#L2130">2130</a>                      <a href="ident?i=bool">bool</a> <a href="ident?i=invert">invert</a>)
<a name="L2131" href="source/net/ipv4/netfilter/ip_tables.c#L2131">2131</a> {
<a name="L2132" href="source/net/ipv4/netfilter/ip_tables.c#L2132">2132</a>         return ((<a href="ident?i=test_type">test_type</a> == 0xFF) ||
<a name="L2133" href="source/net/ipv4/netfilter/ip_tables.c#L2133">2133</a>                 (<a href="ident?i=type">type</a> == <a href="ident?i=test_type">test_type</a> &amp;&amp; <a href="ident?i=code">code</a> &gt;= min_code &amp;&amp; <a href="ident?i=code">code</a> &lt;= max_code))
<a name="L2134" href="source/net/ipv4/netfilter/ip_tables.c#L2134">2134</a>                 ^ <a href="ident?i=invert">invert</a>;
<a name="L2135" href="source/net/ipv4/netfilter/ip_tables.c#L2135">2135</a> }
<a name="L2136" href="source/net/ipv4/netfilter/ip_tables.c#L2136">2136</a> 
<a name="L2137" href="source/net/ipv4/netfilter/ip_tables.c#L2137">2137</a> static <a href="ident?i=bool">bool</a>
<a name="L2138" href="source/net/ipv4/netfilter/ip_tables.c#L2138">2138</a> <a href="ident?i=icmp_match">icmp_match</a>(const struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, struct <a href="ident?i=xt_action_param">xt_action_param</a> *<a href="ident?i=par">par</a>)
<a name="L2139" href="source/net/ipv4/netfilter/ip_tables.c#L2139">2139</a> {
<a name="L2140" href="source/net/ipv4/netfilter/ip_tables.c#L2140">2140</a>         const struct <a href="ident?i=icmphdr">icmphdr</a> *ic;
<a name="L2141" href="source/net/ipv4/netfilter/ip_tables.c#L2141">2141</a>         struct <a href="ident?i=icmphdr">icmphdr</a> _icmph;
<a name="L2142" href="source/net/ipv4/netfilter/ip_tables.c#L2142">2142</a>         const struct <a href="ident?i=ipt_icmp">ipt_icmp</a> *icmpinfo = <a href="ident?i=par">par</a>-&gt;matchinfo;
<a name="L2143" href="source/net/ipv4/netfilter/ip_tables.c#L2143">2143</a> 
<a name="L2144" href="source/net/ipv4/netfilter/ip_tables.c#L2144">2144</a>         <b><i>/* Must not be a fragment. */</i></b>
<a name="L2145" href="source/net/ipv4/netfilter/ip_tables.c#L2145">2145</a>         if (<a href="ident?i=par">par</a>-&gt;fragoff != 0)
<a name="L2146" href="source/net/ipv4/netfilter/ip_tables.c#L2146">2146</a>                 return <a href="ident?i=false">false</a>;
<a name="L2147" href="source/net/ipv4/netfilter/ip_tables.c#L2147">2147</a> 
<a name="L2148" href="source/net/ipv4/netfilter/ip_tables.c#L2148">2148</a>         ic = <a href="ident?i=skb_header_pointer">skb_header_pointer</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=par">par</a>-&gt;thoff, sizeof(_icmph), &amp;_icmph);
<a name="L2149" href="source/net/ipv4/netfilter/ip_tables.c#L2149">2149</a>         if (ic == <a href="ident?i=NULL">NULL</a>) {
<a name="L2150" href="source/net/ipv4/netfilter/ip_tables.c#L2150">2150</a>                 <b><i>/* We've been asked to examine this packet, and we</i></b>
<a name="L2151" href="source/net/ipv4/netfilter/ip_tables.c#L2151">2151</a> <b><i>                 * can't.  Hence, no choice but to drop.</i></b>
<a name="L2152" href="source/net/ipv4/netfilter/ip_tables.c#L2152">2152</a> <b><i>                 */</i></b>
<a name="L2153" href="source/net/ipv4/netfilter/ip_tables.c#L2153">2153</a>                 <a href="ident?i=duprintf">duprintf</a>(<i>"Dropping evil ICMP tinygram.\n"</i>);
<a name="L2154" href="source/net/ipv4/netfilter/ip_tables.c#L2154">2154</a>                 <a href="ident?i=par">par</a>-&gt;hotdrop = <a href="ident?i=true">true</a>;
<a name="L2155" href="source/net/ipv4/netfilter/ip_tables.c#L2155">2155</a>                 return <a href="ident?i=false">false</a>;
<a name="L2156" href="source/net/ipv4/netfilter/ip_tables.c#L2156">2156</a>         }
<a name="L2157" href="source/net/ipv4/netfilter/ip_tables.c#L2157">2157</a> 
<a name="L2158" href="source/net/ipv4/netfilter/ip_tables.c#L2158">2158</a>         return <a href="ident?i=icmp_type_code_match">icmp_type_code_match</a>(icmpinfo-&gt;<a href="ident?i=type">type</a>,
<a name="L2159" href="source/net/ipv4/netfilter/ip_tables.c#L2159">2159</a>                                     icmpinfo-&gt;<a href="ident?i=code">code</a>[0],
<a name="L2160" href="source/net/ipv4/netfilter/ip_tables.c#L2160">2160</a>                                     icmpinfo-&gt;<a href="ident?i=code">code</a>[1],
<a name="L2161" href="source/net/ipv4/netfilter/ip_tables.c#L2161">2161</a>                                     ic-&gt;<a href="ident?i=type">type</a>, ic-&gt;<a href="ident?i=code">code</a>,
<a name="L2162" href="source/net/ipv4/netfilter/ip_tables.c#L2162">2162</a>                                     !!(icmpinfo-&gt;invflags&amp;<a href="ident?i=IPT_ICMP_INV">IPT_ICMP_INV</a>));
<a name="L2163" href="source/net/ipv4/netfilter/ip_tables.c#L2163">2163</a> }
<a name="L2164" href="source/net/ipv4/netfilter/ip_tables.c#L2164">2164</a> 
<a name="L2165" href="source/net/ipv4/netfilter/ip_tables.c#L2165">2165</a> static int <a href="ident?i=icmp_checkentry">icmp_checkentry</a>(const struct <a href="ident?i=xt_mtchk_param">xt_mtchk_param</a> *<a href="ident?i=par">par</a>)
<a name="L2166" href="source/net/ipv4/netfilter/ip_tables.c#L2166">2166</a> {
<a name="L2167" href="source/net/ipv4/netfilter/ip_tables.c#L2167">2167</a>         const struct <a href="ident?i=ipt_icmp">ipt_icmp</a> *icmpinfo = <a href="ident?i=par">par</a>-&gt;matchinfo;
<a name="L2168" href="source/net/ipv4/netfilter/ip_tables.c#L2168">2168</a> 
<a name="L2169" href="source/net/ipv4/netfilter/ip_tables.c#L2169">2169</a>         <b><i>/* Must specify no unknown invflags */</i></b>
<a name="L2170" href="source/net/ipv4/netfilter/ip_tables.c#L2170">2170</a>         return (icmpinfo-&gt;invflags &amp; ~IPT_ICMP_INV) ? -<a href="ident?i=EINVAL">EINVAL</a> : 0;
<a name="L2171" href="source/net/ipv4/netfilter/ip_tables.c#L2171">2171</a> }
<a name="L2172" href="source/net/ipv4/netfilter/ip_tables.c#L2172">2172</a> 
<a name="L2173" href="source/net/ipv4/netfilter/ip_tables.c#L2173">2173</a> static struct <a href="ident?i=xt_target">xt_target</a> ipt_builtin_tg[] <a href="ident?i=__read_mostly">__read_mostly</a> = {
<a name="L2174" href="source/net/ipv4/netfilter/ip_tables.c#L2174">2174</a>         {
<a name="L2175" href="source/net/ipv4/netfilter/ip_tables.c#L2175">2175</a>                 .<a href="ident?i=name">name</a>             = <a href="ident?i=XT_STANDARD_TARGET">XT_STANDARD_TARGET</a>,
<a name="L2176" href="source/net/ipv4/netfilter/ip_tables.c#L2176">2176</a>                 .targetsize       = sizeof(int),
<a name="L2177" href="source/net/ipv4/netfilter/ip_tables.c#L2177">2177</a>                 .<a href="ident?i=family">family</a>           = NFPROTO_IPV4,
<a name="L2178" href="source/net/ipv4/netfilter/ip_tables.c#L2178">2178</a> #ifdef CONFIG_COMPAT
<a name="L2179" href="source/net/ipv4/netfilter/ip_tables.c#L2179">2179</a>                 .compatsize       = sizeof(<a href="ident?i=compat_int_t">compat_int_t</a>),
<a name="L2180" href="source/net/ipv4/netfilter/ip_tables.c#L2180">2180</a>                 .compat_from_user = <a href="ident?i=compat_standard_from_user">compat_standard_from_user</a>,
<a name="L2181" href="source/net/ipv4/netfilter/ip_tables.c#L2181">2181</a>                 .compat_to_user   = <a href="ident?i=compat_standard_to_user">compat_standard_to_user</a>,
<a name="L2182" href="source/net/ipv4/netfilter/ip_tables.c#L2182">2182</a> #endif
<a name="L2183" href="source/net/ipv4/netfilter/ip_tables.c#L2183">2183</a>         },
<a name="L2184" href="source/net/ipv4/netfilter/ip_tables.c#L2184">2184</a>         {
<a name="L2185" href="source/net/ipv4/netfilter/ip_tables.c#L2185">2185</a>                 .<a href="ident?i=name">name</a>             = <a href="ident?i=XT_ERROR_TARGET">XT_ERROR_TARGET</a>,
<a name="L2186" href="source/net/ipv4/netfilter/ip_tables.c#L2186">2186</a>                 .<a href="ident?i=target">target</a>           = <a href="ident?i=ipt_error">ipt_error</a>,
<a name="L2187" href="source/net/ipv4/netfilter/ip_tables.c#L2187">2187</a>                 .targetsize       = <a href="ident?i=XT_FUNCTION_MAXNAMELEN">XT_FUNCTION_MAXNAMELEN</a>,
<a name="L2188" href="source/net/ipv4/netfilter/ip_tables.c#L2188">2188</a>                 .<a href="ident?i=family">family</a>           = NFPROTO_IPV4,
<a name="L2189" href="source/net/ipv4/netfilter/ip_tables.c#L2189">2189</a>         },
<a name="L2190" href="source/net/ipv4/netfilter/ip_tables.c#L2190">2190</a> };
<a name="L2191" href="source/net/ipv4/netfilter/ip_tables.c#L2191">2191</a> 
<a name="L2192" href="source/net/ipv4/netfilter/ip_tables.c#L2192">2192</a> static struct <a href="ident?i=nf_sockopt_ops">nf_sockopt_ops</a> <a href="ident?i=ipt_sockopts">ipt_sockopts</a> = {
<a name="L2193" href="source/net/ipv4/netfilter/ip_tables.c#L2193">2193</a>         .<a href="ident?i=pf">pf</a>             = <a href="ident?i=PF_INET">PF_INET</a>,
<a name="L2194" href="source/net/ipv4/netfilter/ip_tables.c#L2194">2194</a>         .set_optmin     = <a href="ident?i=IPT_BASE_CTL">IPT_BASE_CTL</a>,
<a name="L2195" href="source/net/ipv4/netfilter/ip_tables.c#L2195">2195</a>         .set_optmax     = <a href="ident?i=IPT_SO_SET_MAX">IPT_SO_SET_MAX</a>+1,
<a name="L2196" href="source/net/ipv4/netfilter/ip_tables.c#L2196">2196</a>         .<a href="ident?i=set">set</a>            = <a href="ident?i=do_ipt_set_ctl">do_ipt_set_ctl</a>,
<a name="L2197" href="source/net/ipv4/netfilter/ip_tables.c#L2197">2197</a> #ifdef CONFIG_COMPAT
<a name="L2198" href="source/net/ipv4/netfilter/ip_tables.c#L2198">2198</a>         .compat_set     = <a href="ident?i=compat_do_ipt_set_ctl">compat_do_ipt_set_ctl</a>,
<a name="L2199" href="source/net/ipv4/netfilter/ip_tables.c#L2199">2199</a> #endif
<a name="L2200" href="source/net/ipv4/netfilter/ip_tables.c#L2200">2200</a>         .get_optmin     = <a href="ident?i=IPT_BASE_CTL">IPT_BASE_CTL</a>,
<a name="L2201" href="source/net/ipv4/netfilter/ip_tables.c#L2201">2201</a>         .get_optmax     = <a href="ident?i=IPT_SO_GET_MAX">IPT_SO_GET_MAX</a>+1,
<a name="L2202" href="source/net/ipv4/netfilter/ip_tables.c#L2202">2202</a>         .<a href="ident?i=get">get</a>            = <a href="ident?i=do_ipt_get_ctl">do_ipt_get_ctl</a>,
<a name="L2203" href="source/net/ipv4/netfilter/ip_tables.c#L2203">2203</a> #ifdef CONFIG_COMPAT
<a name="L2204" href="source/net/ipv4/netfilter/ip_tables.c#L2204">2204</a>         .compat_get     = <a href="ident?i=compat_do_ipt_get_ctl">compat_do_ipt_get_ctl</a>,
<a name="L2205" href="source/net/ipv4/netfilter/ip_tables.c#L2205">2205</a> #endif
<a name="L2206" href="source/net/ipv4/netfilter/ip_tables.c#L2206">2206</a>         .owner          = <a href="ident?i=THIS_MODULE">THIS_MODULE</a>,
<a name="L2207" href="source/net/ipv4/netfilter/ip_tables.c#L2207">2207</a> };
<a name="L2208" href="source/net/ipv4/netfilter/ip_tables.c#L2208">2208</a> 
<a name="L2209" href="source/net/ipv4/netfilter/ip_tables.c#L2209">2209</a> static struct <a href="ident?i=xt_match">xt_match</a> ipt_builtin_mt[] <a href="ident?i=__read_mostly">__read_mostly</a> = {
<a name="L2210" href="source/net/ipv4/netfilter/ip_tables.c#L2210">2210</a>         {
<a name="L2211" href="source/net/ipv4/netfilter/ip_tables.c#L2211">2211</a>                 .<a href="ident?i=name">name</a>       = <i>"icmp"</i>,
<a name="L2212" href="source/net/ipv4/netfilter/ip_tables.c#L2212">2212</a>                 .<a href="ident?i=match">match</a>      = <a href="ident?i=icmp_match">icmp_match</a>,
<a name="L2213" href="source/net/ipv4/netfilter/ip_tables.c#L2213">2213</a>                 .matchsize  = sizeof(struct <a href="ident?i=ipt_icmp">ipt_icmp</a>),
<a name="L2214" href="source/net/ipv4/netfilter/ip_tables.c#L2214">2214</a>                 .<a href="ident?i=checkentry">checkentry</a> = <a href="ident?i=icmp_checkentry">icmp_checkentry</a>,
<a name="L2215" href="source/net/ipv4/netfilter/ip_tables.c#L2215">2215</a>                 .<a href="ident?i=proto">proto</a>      = <a href="ident?i=IPPROTO_ICMP">IPPROTO_ICMP</a>,
<a name="L2216" href="source/net/ipv4/netfilter/ip_tables.c#L2216">2216</a>                 .<a href="ident?i=family">family</a>     = NFPROTO_IPV4,
<a name="L2217" href="source/net/ipv4/netfilter/ip_tables.c#L2217">2217</a>         },
<a name="L2218" href="source/net/ipv4/netfilter/ip_tables.c#L2218">2218</a> };
<a name="L2219" href="source/net/ipv4/netfilter/ip_tables.c#L2219">2219</a> 
<a name="L2220" href="source/net/ipv4/netfilter/ip_tables.c#L2220">2220</a> static int <a href="ident?i=__net_init">__net_init</a> <a href="ident?i=ip_tables_net_init">ip_tables_net_init</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>)
<a name="L2221" href="source/net/ipv4/netfilter/ip_tables.c#L2221">2221</a> {
<a name="L2222" href="source/net/ipv4/netfilter/ip_tables.c#L2222">2222</a>         return <a href="ident?i=xt_proto_init">xt_proto_init</a>(<a href="ident?i=net">net</a>, NFPROTO_IPV4);
<a name="L2223" href="source/net/ipv4/netfilter/ip_tables.c#L2223">2223</a> }
<a name="L2224" href="source/net/ipv4/netfilter/ip_tables.c#L2224">2224</a> 
<a name="L2225" href="source/net/ipv4/netfilter/ip_tables.c#L2225">2225</a> static void <a href="ident?i=__net_exit">__net_exit</a> <a href="ident?i=ip_tables_net_exit">ip_tables_net_exit</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>)
<a name="L2226" href="source/net/ipv4/netfilter/ip_tables.c#L2226">2226</a> {
<a name="L2227" href="source/net/ipv4/netfilter/ip_tables.c#L2227">2227</a>         <a href="ident?i=xt_proto_fini">xt_proto_fini</a>(<a href="ident?i=net">net</a>, NFPROTO_IPV4);
<a name="L2228" href="source/net/ipv4/netfilter/ip_tables.c#L2228">2228</a> }
<a name="L2229" href="source/net/ipv4/netfilter/ip_tables.c#L2229">2229</a> 
<a name="L2230" href="source/net/ipv4/netfilter/ip_tables.c#L2230">2230</a> static struct <a href="ident?i=pernet_operations">pernet_operations</a> <a href="ident?i=ip_tables_net_ops">ip_tables_net_ops</a> = {
<a name="L2231" href="source/net/ipv4/netfilter/ip_tables.c#L2231">2231</a>         .<a href="ident?i=init">init</a> = <a href="ident?i=ip_tables_net_init">ip_tables_net_init</a>,
<a name="L2232" href="source/net/ipv4/netfilter/ip_tables.c#L2232">2232</a>         .<a href="ident?i=exit">exit</a> = <a href="ident?i=ip_tables_net_exit">ip_tables_net_exit</a>,
<a name="L2233" href="source/net/ipv4/netfilter/ip_tables.c#L2233">2233</a> };
<a name="L2234" href="source/net/ipv4/netfilter/ip_tables.c#L2234">2234</a> 
<a name="L2235" href="source/net/ipv4/netfilter/ip_tables.c#L2235">2235</a> static int <a href="ident?i=__init">__init</a> <a href="ident?i=ip_tables_init">ip_tables_init</a>(void)
<a name="L2236" href="source/net/ipv4/netfilter/ip_tables.c#L2236">2236</a> {
<a name="L2237" href="source/net/ipv4/netfilter/ip_tables.c#L2237">2237</a>         int <a href="ident?i=ret">ret</a>;
<a name="L2238" href="source/net/ipv4/netfilter/ip_tables.c#L2238">2238</a> 
<a name="L2239" href="source/net/ipv4/netfilter/ip_tables.c#L2239">2239</a>         <a href="ident?i=ret">ret</a> = <a href="ident?i=register_pernet_subsys">register_pernet_subsys</a>(&amp;<a href="ident?i=ip_tables_net_ops">ip_tables_net_ops</a>);
<a name="L2240" href="source/net/ipv4/netfilter/ip_tables.c#L2240">2240</a>         if (<a href="ident?i=ret">ret</a> &lt; 0)
<a name="L2241" href="source/net/ipv4/netfilter/ip_tables.c#L2241">2241</a>                 goto err1;
<a name="L2242" href="source/net/ipv4/netfilter/ip_tables.c#L2242">2242</a> 
<a name="L2243" href="source/net/ipv4/netfilter/ip_tables.c#L2243">2243</a>         <b><i>/* No one else will be downing sem now, so we won't sleep */</i></b>
<a name="L2244" href="source/net/ipv4/netfilter/ip_tables.c#L2244">2244</a>         <a href="ident?i=ret">ret</a> = <a href="ident?i=xt_register_targets">xt_register_targets</a>(ipt_builtin_tg, <a href="ident?i=ARRAY_SIZE">ARRAY_SIZE</a>(ipt_builtin_tg));
<a name="L2245" href="source/net/ipv4/netfilter/ip_tables.c#L2245">2245</a>         if (<a href="ident?i=ret">ret</a> &lt; 0)
<a name="L2246" href="source/net/ipv4/netfilter/ip_tables.c#L2246">2246</a>                 goto err2;
<a name="L2247" href="source/net/ipv4/netfilter/ip_tables.c#L2247">2247</a>         <a href="ident?i=ret">ret</a> = <a href="ident?i=xt_register_matches">xt_register_matches</a>(ipt_builtin_mt, <a href="ident?i=ARRAY_SIZE">ARRAY_SIZE</a>(ipt_builtin_mt));
<a name="L2248" href="source/net/ipv4/netfilter/ip_tables.c#L2248">2248</a>         if (<a href="ident?i=ret">ret</a> &lt; 0)
<a name="L2249" href="source/net/ipv4/netfilter/ip_tables.c#L2249">2249</a>                 goto err4;
<a name="L2250" href="source/net/ipv4/netfilter/ip_tables.c#L2250">2250</a> 
<a name="L2251" href="source/net/ipv4/netfilter/ip_tables.c#L2251">2251</a>         <b><i>/* Register setsockopt */</i></b>
<a name="L2252" href="source/net/ipv4/netfilter/ip_tables.c#L2252">2252</a>         <a href="ident?i=ret">ret</a> = <a href="ident?i=nf_register_sockopt">nf_register_sockopt</a>(&amp;<a href="ident?i=ipt_sockopts">ipt_sockopts</a>);
<a name="L2253" href="source/net/ipv4/netfilter/ip_tables.c#L2253">2253</a>         if (<a href="ident?i=ret">ret</a> &lt; 0)
<a name="L2254" href="source/net/ipv4/netfilter/ip_tables.c#L2254">2254</a>                 goto err5;
<a name="L2255" href="source/net/ipv4/netfilter/ip_tables.c#L2255">2255</a> 
<a name="L2256" href="source/net/ipv4/netfilter/ip_tables.c#L2256">2256</a>         <a href="ident?i=pr_info">pr_info</a>(<i>"(C) 2000-2006 Netfilter Core Team\n"</i>);
<a name="L2257" href="source/net/ipv4/netfilter/ip_tables.c#L2257">2257</a>         return 0;
<a name="L2258" href="source/net/ipv4/netfilter/ip_tables.c#L2258">2258</a> 
<a name="L2259" href="source/net/ipv4/netfilter/ip_tables.c#L2259">2259</a> err5:
<a name="L2260" href="source/net/ipv4/netfilter/ip_tables.c#L2260">2260</a>         <a href="ident?i=xt_unregister_matches">xt_unregister_matches</a>(ipt_builtin_mt, <a href="ident?i=ARRAY_SIZE">ARRAY_SIZE</a>(ipt_builtin_mt));
<a name="L2261" href="source/net/ipv4/netfilter/ip_tables.c#L2261">2261</a> err4:
<a name="L2262" href="source/net/ipv4/netfilter/ip_tables.c#L2262">2262</a>         <a href="ident?i=xt_unregister_targets">xt_unregister_targets</a>(ipt_builtin_tg, <a href="ident?i=ARRAY_SIZE">ARRAY_SIZE</a>(ipt_builtin_tg));
<a name="L2263" href="source/net/ipv4/netfilter/ip_tables.c#L2263">2263</a> err2:
<a name="L2264" href="source/net/ipv4/netfilter/ip_tables.c#L2264">2264</a>         <a href="ident?i=unregister_pernet_subsys">unregister_pernet_subsys</a>(&amp;<a href="ident?i=ip_tables_net_ops">ip_tables_net_ops</a>);
<a name="L2265" href="source/net/ipv4/netfilter/ip_tables.c#L2265">2265</a> err1:
<a name="L2266" href="source/net/ipv4/netfilter/ip_tables.c#L2266">2266</a>         return <a href="ident?i=ret">ret</a>;
<a name="L2267" href="source/net/ipv4/netfilter/ip_tables.c#L2267">2267</a> }
<a name="L2268" href="source/net/ipv4/netfilter/ip_tables.c#L2268">2268</a> 
<a name="L2269" href="source/net/ipv4/netfilter/ip_tables.c#L2269">2269</a> static void <a href="ident?i=__exit">__exit</a> <a href="ident?i=ip_tables_fini">ip_tables_fini</a>(void)
<a name="L2270" href="source/net/ipv4/netfilter/ip_tables.c#L2270">2270</a> {
<a name="L2271" href="source/net/ipv4/netfilter/ip_tables.c#L2271">2271</a>         <a href="ident?i=nf_unregister_sockopt">nf_unregister_sockopt</a>(&amp;<a href="ident?i=ipt_sockopts">ipt_sockopts</a>);
<a name="L2272" href="source/net/ipv4/netfilter/ip_tables.c#L2272">2272</a> 
<a name="L2273" href="source/net/ipv4/netfilter/ip_tables.c#L2273">2273</a>         <a href="ident?i=xt_unregister_matches">xt_unregister_matches</a>(ipt_builtin_mt, <a href="ident?i=ARRAY_SIZE">ARRAY_SIZE</a>(ipt_builtin_mt));
<a name="L2274" href="source/net/ipv4/netfilter/ip_tables.c#L2274">2274</a>         <a href="ident?i=xt_unregister_targets">xt_unregister_targets</a>(ipt_builtin_tg, <a href="ident?i=ARRAY_SIZE">ARRAY_SIZE</a>(ipt_builtin_tg));
<a name="L2275" href="source/net/ipv4/netfilter/ip_tables.c#L2275">2275</a>         <a href="ident?i=unregister_pernet_subsys">unregister_pernet_subsys</a>(&amp;<a href="ident?i=ip_tables_net_ops">ip_tables_net_ops</a>);
<a name="L2276" href="source/net/ipv4/netfilter/ip_tables.c#L2276">2276</a> }
<a name="L2277" href="source/net/ipv4/netfilter/ip_tables.c#L2277">2277</a> 
<a name="L2278" href="source/net/ipv4/netfilter/ip_tables.c#L2278">2278</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=ipt_register_table">ipt_register_table</a>);
<a name="L2279" href="source/net/ipv4/netfilter/ip_tables.c#L2279">2279</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=ipt_unregister_table">ipt_unregister_table</a>);
<a name="L2280" href="source/net/ipv4/netfilter/ip_tables.c#L2280">2280</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=ipt_do_table">ipt_do_table</a>);
<a name="L2281" href="source/net/ipv4/netfilter/ip_tables.c#L2281">2281</a> <a href="ident?i=module_init">module_init</a>(<a href="ident?i=ip_tables_init">ip_tables_init</a>);
<a name="L2282" href="source/net/ipv4/netfilter/ip_tables.c#L2282">2282</a> <a href="ident?i=module_exit">module_exit</a>(<a href="ident?i=ip_tables_fini">ip_tables_fini</a>);
<a name="L2283" href="source/net/ipv4/netfilter/ip_tables.c#L2283">2283</a> </pre></div><p>
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
