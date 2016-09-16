<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title>Linux/net/ipv4/netfilter/arp_tables.c - Linux Cross Reference - Free Electrons</title>
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
		 &nbsp;&bull;&nbsp;<b><i>source navigation</i></b> &nbsp;&bull;&nbsp;<a href="diff/net/ipv4/netfilter/arp_tables.c">diff markup</a> &nbsp;&bull;&nbsp;<a href="ident">identifier search</a> &nbsp;&bull;&nbsp;<a href="search">freetext search</a> &nbsp;&bull;&nbsp;
		</p>
	</div>
</div>

<div id="topbar">
  
  <p>Version: &nbsp;<a href="source/net/ipv4/netfilter/arp_tables.c?v=2.0.40">2.0.40</a>&nbsp;<a href="source/net/ipv4/netfilter/arp_tables.c?v=2.2.26">2.2.26</a>&nbsp;<a href="source/net/ipv4/netfilter/arp_tables.c?v=2.4.37">2.4.37</a>&nbsp;<a href="source/net/ipv4/netfilter/arp_tables.c?v=3.5">3.5</a>&nbsp;<a href="source/net/ipv4/netfilter/arp_tables.c?v=3.6">3.6</a>&nbsp;<a href="source/net/ipv4/netfilter/arp_tables.c?v=3.7">3.7</a>&nbsp;<a href="source/net/ipv4/netfilter/arp_tables.c?v=3.8">3.8</a>&nbsp;<a href="source/net/ipv4/netfilter/arp_tables.c?v=3.9">3.9</a>&nbsp;<a href="source/net/ipv4/netfilter/arp_tables.c?v=3.10">3.10</a>&nbsp;<a href="source/net/ipv4/netfilter/arp_tables.c?v=3.11">3.11</a>&nbsp;<a href="source/net/ipv4/netfilter/arp_tables.c?v=3.12">3.12</a>&nbsp;<a href="source/net/ipv4/netfilter/arp_tables.c?v=3.13">3.13</a>&nbsp;<a href="source/net/ipv4/netfilter/arp_tables.c?v=3.14">3.14</a>&nbsp;<a href="source/net/ipv4/netfilter/arp_tables.c?v=3.15">3.15</a>&nbsp;<a href="source/net/ipv4/netfilter/arp_tables.c?v=3.16">3.16</a>&nbsp;<a href="source/net/ipv4/netfilter/arp_tables.c?v=3.17">3.17</a>&nbsp;<a href="source/net/ipv4/netfilter/arp_tables.c?v=3.18">3.18</a>&nbsp;<a href="source/net/ipv4/netfilter/arp_tables.c?v=3.19">3.19</a>&nbsp;<a href="source/net/ipv4/netfilter/arp_tables.c?v=4.0">4.0</a>&nbsp;<b><i>4.1</i></b></p>
  
</div>

<h1><a href="source/">Linux</a>/<a href="source/net/">net</a>/<a href="source/net/ipv4/">ipv4</a>/<a href="source/net/ipv4/netfilter/">netfilter</a>/<a href="source/net/ipv4/netfilter/arp_tables.c">arp_tables.c</a></h1>
<div id="lxrcode"><pre>  <a name="L1" href="source/net/ipv4/netfilter/arp_tables.c#L1">1</a> <b><i>/*</i></b>
  <a name="L2" href="source/net/ipv4/netfilter/arp_tables.c#L2">2</a> <b><i> * Packet matching code for ARP packets.</i></b>
  <a name="L3" href="source/net/ipv4/netfilter/arp_tables.c#L3">3</a> <b><i> *</i></b>
  <a name="L4" href="source/net/ipv4/netfilter/arp_tables.c#L4">4</a> <b><i> * Based heavily, if not almost entirely, upon ip_tables.c framework.</i></b>
  <a name="L5" href="source/net/ipv4/netfilter/arp_tables.c#L5">5</a> <b><i> *</i></b>
  <a name="L6" href="source/net/ipv4/netfilter/arp_tables.c#L6">6</a> <b><i> * Some ARP specific bits are:</i></b>
  <a name="L7" href="source/net/ipv4/netfilter/arp_tables.c#L7">7</a> <b><i> *</i></b>
  <a name="L8" href="source/net/ipv4/netfilter/arp_tables.c#L8">8</a> <b><i> * Copyright (C) 2002 David S. Miller (davem@redhat.com)</i></b>
  <a name="L9" href="source/net/ipv4/netfilter/arp_tables.c#L9">9</a> <b><i> * Copyright (C) 2006-2009 Patrick McHardy &lt;kaber@trash.net&gt;</i></b>
 <a name="L10" href="source/net/ipv4/netfilter/arp_tables.c#L10">10</a> <b><i> *</i></b>
 <a name="L11" href="source/net/ipv4/netfilter/arp_tables.c#L11">11</a> <b><i> */</i></b>
 <a name="L12" href="source/net/ipv4/netfilter/arp_tables.c#L12">12</a> #define <a href="ident?i=pr_fmt">pr_fmt</a>(<a href="ident?i=fmt">fmt</a>) KBUILD_MODNAME <i>": "</i> <a href="ident?i=fmt">fmt</a>
 <a name="L13" href="source/net/ipv4/netfilter/arp_tables.c#L13">13</a> #include &lt;linux/kernel.h&gt;
 <a name="L14" href="source/net/ipv4/netfilter/arp_tables.c#L14">14</a> #include &lt;linux/skbuff.h&gt;
 <a name="L15" href="source/net/ipv4/netfilter/arp_tables.c#L15">15</a> #include &lt;linux/netdevice.h&gt;
 <a name="L16" href="source/net/ipv4/netfilter/arp_tables.c#L16">16</a> #include &lt;linux/capability.h&gt;
 <a name="L17" href="source/net/ipv4/netfilter/arp_tables.c#L17">17</a> #include &lt;linux/if_arp.h&gt;
 <a name="L18" href="source/net/ipv4/netfilter/arp_tables.c#L18">18</a> #include &lt;linux/kmod.h&gt;
 <a name="L19" href="source/net/ipv4/netfilter/arp_tables.c#L19">19</a> #include &lt;linux/vmalloc.h&gt;
 <a name="L20" href="source/net/ipv4/netfilter/arp_tables.c#L20">20</a> #include &lt;linux/proc_fs.h&gt;
 <a name="L21" href="source/net/ipv4/netfilter/arp_tables.c#L21">21</a> #include &lt;linux/module.h&gt;
 <a name="L22" href="source/net/ipv4/netfilter/arp_tables.c#L22">22</a> #include &lt;linux/init.h&gt;
 <a name="L23" href="source/net/ipv4/netfilter/arp_tables.c#L23">23</a> #include &lt;linux/mutex.h&gt;
 <a name="L24" href="source/net/ipv4/netfilter/arp_tables.c#L24">24</a> #include &lt;linux/err.h&gt;
 <a name="L25" href="source/net/ipv4/netfilter/arp_tables.c#L25">25</a> #include &lt;net/compat.h&gt;
 <a name="L26" href="source/net/ipv4/netfilter/arp_tables.c#L26">26</a> #include &lt;net/sock.h&gt;
 <a name="L27" href="source/net/ipv4/netfilter/arp_tables.c#L27">27</a> #include &lt;asm/uaccess.h&gt;
 <a name="L28" href="source/net/ipv4/netfilter/arp_tables.c#L28">28</a> 
 <a name="L29" href="source/net/ipv4/netfilter/arp_tables.c#L29">29</a> #include &lt;linux/netfilter/x_tables.h&gt;
 <a name="L30" href="source/net/ipv4/netfilter/arp_tables.c#L30">30</a> #include &lt;linux/netfilter_arp/arp_tables.h&gt;
 <a name="L31" href="source/net/ipv4/netfilter/arp_tables.c#L31">31</a> #include "<a href="source/net/ipv4/netfilter/../../netfilter/xt_repldata.h">../../netfilter/xt_repldata.h</a>"
 <a name="L32" href="source/net/ipv4/netfilter/arp_tables.c#L32">32</a> 
 <a name="L33" href="source/net/ipv4/netfilter/arp_tables.c#L33">33</a> <a href="ident?i=MODULE_LICENSE">MODULE_LICENSE</a>(<i>"GPL"</i>);
 <a name="L34" href="source/net/ipv4/netfilter/arp_tables.c#L34">34</a> <a href="ident?i=MODULE_AUTHOR">MODULE_AUTHOR</a>(<i>"David S. Miller &lt;davem@redhat.com&gt;"</i>);
 <a name="L35" href="source/net/ipv4/netfilter/arp_tables.c#L35">35</a> <a href="ident?i=MODULE_DESCRIPTION">MODULE_DESCRIPTION</a>(<i>"arptables core"</i>);
 <a name="L36" href="source/net/ipv4/netfilter/arp_tables.c#L36">36</a> 
 <a name="L37" href="source/net/ipv4/netfilter/arp_tables.c#L37">37</a> <b><i>/*#define DEBUG_ARP_TABLES*/</i></b>
 <a name="L38" href="source/net/ipv4/netfilter/arp_tables.c#L38">38</a> <b><i>/*#define DEBUG_ARP_TABLES_USER*/</i></b>
 <a name="L39" href="source/net/ipv4/netfilter/arp_tables.c#L39">39</a> 
 <a name="L40" href="source/net/ipv4/netfilter/arp_tables.c#L40">40</a> #ifdef DEBUG_ARP_TABLES
 <a name="L41" href="source/net/ipv4/netfilter/arp_tables.c#L41">41</a> #define <a href="ident?i=dprintf">dprintf</a>(<a href="ident?i=format">format</a>, <a href="ident?i=args">args</a>...)  <a href="ident?i=printk">printk</a>(<a href="ident?i=format">format</a> , ## <a href="ident?i=args">args</a>)
 <a name="L42" href="source/net/ipv4/netfilter/arp_tables.c#L42">42</a> #else
 <a name="L43" href="source/net/ipv4/netfilter/arp_tables.c#L43">43</a> #define <a href="ident?i=dprintf">dprintf</a>(<a href="ident?i=format">format</a>, <a href="ident?i=args">args</a>...)
 <a name="L44" href="source/net/ipv4/netfilter/arp_tables.c#L44">44</a> #endif
 <a name="L45" href="source/net/ipv4/netfilter/arp_tables.c#L45">45</a> 
 <a name="L46" href="source/net/ipv4/netfilter/arp_tables.c#L46">46</a> #ifdef DEBUG_ARP_TABLES_USER
 <a name="L47" href="source/net/ipv4/netfilter/arp_tables.c#L47">47</a> #define <a href="ident?i=duprintf">duprintf</a>(<a href="ident?i=format">format</a>, <a href="ident?i=args">args</a>...) <a href="ident?i=printk">printk</a>(<a href="ident?i=format">format</a> , ## <a href="ident?i=args">args</a>)
 <a name="L48" href="source/net/ipv4/netfilter/arp_tables.c#L48">48</a> #else
 <a name="L49" href="source/net/ipv4/netfilter/arp_tables.c#L49">49</a> #define <a href="ident?i=duprintf">duprintf</a>(<a href="ident?i=format">format</a>, <a href="ident?i=args">args</a>...)
 <a name="L50" href="source/net/ipv4/netfilter/arp_tables.c#L50">50</a> #endif
 <a name="L51" href="source/net/ipv4/netfilter/arp_tables.c#L51">51</a> 
 <a name="L52" href="source/net/ipv4/netfilter/arp_tables.c#L52">52</a> #ifdef CONFIG_NETFILTER_DEBUG
 <a name="L53" href="source/net/ipv4/netfilter/arp_tables.c#L53">53</a> #define <a href="ident?i=ARP_NF_ASSERT">ARP_NF_ASSERT</a>(<a href="ident?i=x">x</a>)        <a href="ident?i=WARN_ON">WARN_ON</a>(!(<a href="ident?i=x">x</a>))
 <a name="L54" href="source/net/ipv4/netfilter/arp_tables.c#L54">54</a> #else
 <a name="L55" href="source/net/ipv4/netfilter/arp_tables.c#L55">55</a> #define <a href="ident?i=ARP_NF_ASSERT">ARP_NF_ASSERT</a>(<a href="ident?i=x">x</a>)
 <a name="L56" href="source/net/ipv4/netfilter/arp_tables.c#L56">56</a> #endif
 <a name="L57" href="source/net/ipv4/netfilter/arp_tables.c#L57">57</a> 
 <a name="L58" href="source/net/ipv4/netfilter/arp_tables.c#L58">58</a> void *<a href="ident?i=arpt_alloc_initial_table">arpt_alloc_initial_table</a>(const struct <a href="ident?i=xt_table">xt_table</a> *<a href="ident?i=info">info</a>)
 <a name="L59" href="source/net/ipv4/netfilter/arp_tables.c#L59">59</a> {
 <a name="L60" href="source/net/ipv4/netfilter/arp_tables.c#L60">60</a>         return <a href="ident?i=xt_alloc_initial_table">xt_alloc_initial_table</a>(arpt, ARPT);
 <a name="L61" href="source/net/ipv4/netfilter/arp_tables.c#L61">61</a> }
 <a name="L62" href="source/net/ipv4/netfilter/arp_tables.c#L62">62</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=arpt_alloc_initial_table">arpt_alloc_initial_table</a>);
 <a name="L63" href="source/net/ipv4/netfilter/arp_tables.c#L63">63</a> 
 <a name="L64" href="source/net/ipv4/netfilter/arp_tables.c#L64">64</a> static inline int <a href="ident?i=arp_devaddr_compare">arp_devaddr_compare</a>(const struct <a href="ident?i=arpt_devaddr_info">arpt_devaddr_info</a> *<a href="ident?i=ap">ap</a>,
 <a name="L65" href="source/net/ipv4/netfilter/arp_tables.c#L65">65</a>                                       const char *<a href="ident?i=hdr_addr">hdr_addr</a>, int <a href="ident?i=len">len</a>)
 <a name="L66" href="source/net/ipv4/netfilter/arp_tables.c#L66">66</a> {
 <a name="L67" href="source/net/ipv4/netfilter/arp_tables.c#L67">67</a>         int <a href="ident?i=i">i</a>, <a href="ident?i=ret">ret</a>;
 <a name="L68" href="source/net/ipv4/netfilter/arp_tables.c#L68">68</a> 
 <a name="L69" href="source/net/ipv4/netfilter/arp_tables.c#L69">69</a>         if (<a href="ident?i=len">len</a> &gt; <a href="ident?i=ARPT_DEV_ADDR_LEN_MAX">ARPT_DEV_ADDR_LEN_MAX</a>)
 <a name="L70" href="source/net/ipv4/netfilter/arp_tables.c#L70">70</a>                 <a href="ident?i=len">len</a> = <a href="ident?i=ARPT_DEV_ADDR_LEN_MAX">ARPT_DEV_ADDR_LEN_MAX</a>;
 <a name="L71" href="source/net/ipv4/netfilter/arp_tables.c#L71">71</a> 
 <a name="L72" href="source/net/ipv4/netfilter/arp_tables.c#L72">72</a>         <a href="ident?i=ret">ret</a> = 0;
 <a name="L73" href="source/net/ipv4/netfilter/arp_tables.c#L73">73</a>         for (<a href="ident?i=i">i</a> = 0; <a href="ident?i=i">i</a> &lt; <a href="ident?i=len">len</a>; <a href="ident?i=i">i</a>++)
 <a name="L74" href="source/net/ipv4/netfilter/arp_tables.c#L74">74</a>                 <a href="ident?i=ret">ret</a> |= (<a href="ident?i=hdr_addr">hdr_addr</a>[<a href="ident?i=i">i</a>] ^ <a href="ident?i=ap">ap</a>-&gt;<a href="ident?i=addr">addr</a>[<a href="ident?i=i">i</a>]) &amp; <a href="ident?i=ap">ap</a>-&gt;<a href="ident?i=mask">mask</a>[<a href="ident?i=i">i</a>];
 <a name="L75" href="source/net/ipv4/netfilter/arp_tables.c#L75">75</a> 
 <a name="L76" href="source/net/ipv4/netfilter/arp_tables.c#L76">76</a>         return <a href="ident?i=ret">ret</a> != 0;
 <a name="L77" href="source/net/ipv4/netfilter/arp_tables.c#L77">77</a> }
 <a name="L78" href="source/net/ipv4/netfilter/arp_tables.c#L78">78</a> 
 <a name="L79" href="source/net/ipv4/netfilter/arp_tables.c#L79">79</a> <b><i>/*</i></b>
 <a name="L80" href="source/net/ipv4/netfilter/arp_tables.c#L80">80</a> <b><i> * Unfortunately, _b and _mask are not aligned to an int (or long int)</i></b>
 <a name="L81" href="source/net/ipv4/netfilter/arp_tables.c#L81">81</a> <b><i> * Some arches dont care, unrolling the loop is a win on them.</i></b>
 <a name="L82" href="source/net/ipv4/netfilter/arp_tables.c#L82">82</a> <b><i> * For other arches, we only have a 16bit alignement.</i></b>
 <a name="L83" href="source/net/ipv4/netfilter/arp_tables.c#L83">83</a> <b><i> */</i></b>
 <a name="L84" href="source/net/ipv4/netfilter/arp_tables.c#L84">84</a> static unsigned long <a href="ident?i=ifname_compare">ifname_compare</a>(const char *_a, const char *_b, const char *_mask)
 <a name="L85" href="source/net/ipv4/netfilter/arp_tables.c#L85">85</a> {
 <a name="L86" href="source/net/ipv4/netfilter/arp_tables.c#L86">86</a> #ifdef CONFIG_HAVE_EFFICIENT_UNALIGNED_ACCESS
 <a name="L87" href="source/net/ipv4/netfilter/arp_tables.c#L87">87</a>         unsigned long <a href="ident?i=ret">ret</a> = <a href="ident?i=ifname_compare_aligned">ifname_compare_aligned</a>(_a, _b, _mask);
 <a name="L88" href="source/net/ipv4/netfilter/arp_tables.c#L88">88</a> #else
 <a name="L89" href="source/net/ipv4/netfilter/arp_tables.c#L89">89</a>         unsigned long <a href="ident?i=ret">ret</a> = 0;
 <a name="L90" href="source/net/ipv4/netfilter/arp_tables.c#L90">90</a>         const <a href="ident?i=u16">u16</a> *<a href="ident?i=a">a</a> = (const <a href="ident?i=u16">u16</a> *)_a;
 <a name="L91" href="source/net/ipv4/netfilter/arp_tables.c#L91">91</a>         const <a href="ident?i=u16">u16</a> *<a href="ident?i=b">b</a> = (const <a href="ident?i=u16">u16</a> *)_b;
 <a name="L92" href="source/net/ipv4/netfilter/arp_tables.c#L92">92</a>         const <a href="ident?i=u16">u16</a> *<a href="ident?i=mask">mask</a> = (const <a href="ident?i=u16">u16</a> *)_mask;
 <a name="L93" href="source/net/ipv4/netfilter/arp_tables.c#L93">93</a>         int <a href="ident?i=i">i</a>;
 <a name="L94" href="source/net/ipv4/netfilter/arp_tables.c#L94">94</a> 
 <a name="L95" href="source/net/ipv4/netfilter/arp_tables.c#L95">95</a>         for (<a href="ident?i=i">i</a> = 0; <a href="ident?i=i">i</a> &lt; <a href="ident?i=IFNAMSIZ">IFNAMSIZ</a>/sizeof(<a href="ident?i=u16">u16</a>); <a href="ident?i=i">i</a>++)
 <a name="L96" href="source/net/ipv4/netfilter/arp_tables.c#L96">96</a>                 <a href="ident?i=ret">ret</a> |= (<a href="ident?i=a">a</a>[<a href="ident?i=i">i</a>] ^ <a href="ident?i=b">b</a>[<a href="ident?i=i">i</a>]) &amp; <a href="ident?i=mask">mask</a>[<a href="ident?i=i">i</a>];
 <a name="L97" href="source/net/ipv4/netfilter/arp_tables.c#L97">97</a> #endif
 <a name="L98" href="source/net/ipv4/netfilter/arp_tables.c#L98">98</a>         return <a href="ident?i=ret">ret</a>;
 <a name="L99" href="source/net/ipv4/netfilter/arp_tables.c#L99">99</a> }
<a name="L100" href="source/net/ipv4/netfilter/arp_tables.c#L100">100</a> 
<a name="L101" href="source/net/ipv4/netfilter/arp_tables.c#L101">101</a> <b><i>/* Returns whether packet matches rule or not. */</i></b>
<a name="L102" href="source/net/ipv4/netfilter/arp_tables.c#L102">102</a> static inline int <a href="ident?i=arp_packet_match">arp_packet_match</a>(const struct <a href="ident?i=arphdr">arphdr</a> *<a href="ident?i=arphdr">arphdr</a>,
<a name="L103" href="source/net/ipv4/netfilter/arp_tables.c#L103">103</a>                                    struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>,
<a name="L104" href="source/net/ipv4/netfilter/arp_tables.c#L104">104</a>                                    const char *indev,
<a name="L105" href="source/net/ipv4/netfilter/arp_tables.c#L105">105</a>                                    const char *outdev,
<a name="L106" href="source/net/ipv4/netfilter/arp_tables.c#L106">106</a>                                    const struct <a href="ident?i=arpt_arp">arpt_arp</a> *arpinfo)
<a name="L107" href="source/net/ipv4/netfilter/arp_tables.c#L107">107</a> {
<a name="L108" href="source/net/ipv4/netfilter/arp_tables.c#L108">108</a>         const char *arpptr = (char *)(<a href="ident?i=arphdr">arphdr</a> + 1);
<a name="L109" href="source/net/ipv4/netfilter/arp_tables.c#L109">109</a>         const char *src_devaddr, *tgt_devaddr;
<a name="L110" href="source/net/ipv4/netfilter/arp_tables.c#L110">110</a>         <a href="ident?i=__be32">__be32</a> src_ipaddr, tgt_ipaddr;
<a name="L111" href="source/net/ipv4/netfilter/arp_tables.c#L111">111</a>         long <a href="ident?i=ret">ret</a>;
<a name="L112" href="source/net/ipv4/netfilter/arp_tables.c#L112">112</a> 
<a name="L113" href="source/net/ipv4/netfilter/arp_tables.c#L113">113</a> #define <a href="ident?i=FWINV">FWINV</a>(<a href="ident?i=bool">bool</a>, invflg) ((<a href="ident?i=bool">bool</a>) ^ !!(arpinfo-&gt;invflags &amp; (invflg)))
<a name="L114" href="source/net/ipv4/netfilter/arp_tables.c#L114">114</a> 
<a name="L115" href="source/net/ipv4/netfilter/arp_tables.c#L115">115</a>         if (<a href="ident?i=FWINV">FWINV</a>((<a href="ident?i=arphdr">arphdr</a>-&gt;ar_op &amp; arpinfo-&gt;arpop_mask) != arpinfo-&gt;arpop,
<a name="L116" href="source/net/ipv4/netfilter/arp_tables.c#L116">116</a>                   <a href="ident?i=ARPT_INV_ARPOP">ARPT_INV_ARPOP</a>)) {
<a name="L117" href="source/net/ipv4/netfilter/arp_tables.c#L117">117</a>                 <a href="ident?i=dprintf">dprintf</a>(<i>"ARP operation field mismatch.\n"</i>);
<a name="L118" href="source/net/ipv4/netfilter/arp_tables.c#L118">118</a>                 <a href="ident?i=dprintf">dprintf</a>(<i>"ar_op: %04x info-&gt;arpop: %04x info-&gt;arpop_mask: %04x\n"</i>,
<a name="L119" href="source/net/ipv4/netfilter/arp_tables.c#L119">119</a>                         <a href="ident?i=arphdr">arphdr</a>-&gt;ar_op, arpinfo-&gt;arpop, arpinfo-&gt;arpop_mask);
<a name="L120" href="source/net/ipv4/netfilter/arp_tables.c#L120">120</a>                 return 0;
<a name="L121" href="source/net/ipv4/netfilter/arp_tables.c#L121">121</a>         }
<a name="L122" href="source/net/ipv4/netfilter/arp_tables.c#L122">122</a> 
<a name="L123" href="source/net/ipv4/netfilter/arp_tables.c#L123">123</a>         if (<a href="ident?i=FWINV">FWINV</a>((<a href="ident?i=arphdr">arphdr</a>-&gt;ar_hrd &amp; arpinfo-&gt;arhrd_mask) != arpinfo-&gt;arhrd,
<a name="L124" href="source/net/ipv4/netfilter/arp_tables.c#L124">124</a>                   <a href="ident?i=ARPT_INV_ARPHRD">ARPT_INV_ARPHRD</a>)) {
<a name="L125" href="source/net/ipv4/netfilter/arp_tables.c#L125">125</a>                 <a href="ident?i=dprintf">dprintf</a>(<i>"ARP hardware address format mismatch.\n"</i>);
<a name="L126" href="source/net/ipv4/netfilter/arp_tables.c#L126">126</a>                 <a href="ident?i=dprintf">dprintf</a>(<i>"ar_hrd: %04x info-&gt;arhrd: %04x info-&gt;arhrd_mask: %04x\n"</i>,
<a name="L127" href="source/net/ipv4/netfilter/arp_tables.c#L127">127</a>                         <a href="ident?i=arphdr">arphdr</a>-&gt;ar_hrd, arpinfo-&gt;arhrd, arpinfo-&gt;arhrd_mask);
<a name="L128" href="source/net/ipv4/netfilter/arp_tables.c#L128">128</a>                 return 0;
<a name="L129" href="source/net/ipv4/netfilter/arp_tables.c#L129">129</a>         }
<a name="L130" href="source/net/ipv4/netfilter/arp_tables.c#L130">130</a> 
<a name="L131" href="source/net/ipv4/netfilter/arp_tables.c#L131">131</a>         if (<a href="ident?i=FWINV">FWINV</a>((<a href="ident?i=arphdr">arphdr</a>-&gt;ar_pro &amp; arpinfo-&gt;arpro_mask) != arpinfo-&gt;arpro,
<a name="L132" href="source/net/ipv4/netfilter/arp_tables.c#L132">132</a>                   <a href="ident?i=ARPT_INV_ARPPRO">ARPT_INV_ARPPRO</a>)) {
<a name="L133" href="source/net/ipv4/netfilter/arp_tables.c#L133">133</a>                 <a href="ident?i=dprintf">dprintf</a>(<i>"ARP protocol address format mismatch.\n"</i>);
<a name="L134" href="source/net/ipv4/netfilter/arp_tables.c#L134">134</a>                 <a href="ident?i=dprintf">dprintf</a>(<i>"ar_pro: %04x info-&gt;arpro: %04x info-&gt;arpro_mask: %04x\n"</i>,
<a name="L135" href="source/net/ipv4/netfilter/arp_tables.c#L135">135</a>                         <a href="ident?i=arphdr">arphdr</a>-&gt;ar_pro, arpinfo-&gt;arpro, arpinfo-&gt;arpro_mask);
<a name="L136" href="source/net/ipv4/netfilter/arp_tables.c#L136">136</a>                 return 0;
<a name="L137" href="source/net/ipv4/netfilter/arp_tables.c#L137">137</a>         }
<a name="L138" href="source/net/ipv4/netfilter/arp_tables.c#L138">138</a> 
<a name="L139" href="source/net/ipv4/netfilter/arp_tables.c#L139">139</a>         if (<a href="ident?i=FWINV">FWINV</a>((<a href="ident?i=arphdr">arphdr</a>-&gt;ar_hln &amp; arpinfo-&gt;arhln_mask) != arpinfo-&gt;arhln,
<a name="L140" href="source/net/ipv4/netfilter/arp_tables.c#L140">140</a>                   <a href="ident?i=ARPT_INV_ARPHLN">ARPT_INV_ARPHLN</a>)) {
<a name="L141" href="source/net/ipv4/netfilter/arp_tables.c#L141">141</a>                 <a href="ident?i=dprintf">dprintf</a>(<i>"ARP hardware address length mismatch.\n"</i>);
<a name="L142" href="source/net/ipv4/netfilter/arp_tables.c#L142">142</a>                 <a href="ident?i=dprintf">dprintf</a>(<i>"ar_hln: %02x info-&gt;arhln: %02x info-&gt;arhln_mask: %02x\n"</i>,
<a name="L143" href="source/net/ipv4/netfilter/arp_tables.c#L143">143</a>                         <a href="ident?i=arphdr">arphdr</a>-&gt;ar_hln, arpinfo-&gt;arhln, arpinfo-&gt;arhln_mask);
<a name="L144" href="source/net/ipv4/netfilter/arp_tables.c#L144">144</a>                 return 0;
<a name="L145" href="source/net/ipv4/netfilter/arp_tables.c#L145">145</a>         }
<a name="L146" href="source/net/ipv4/netfilter/arp_tables.c#L146">146</a> 
<a name="L147" href="source/net/ipv4/netfilter/arp_tables.c#L147">147</a>         src_devaddr = arpptr;
<a name="L148" href="source/net/ipv4/netfilter/arp_tables.c#L148">148</a>         arpptr += <a href="ident?i=dev">dev</a>-&gt;addr_len;
<a name="L149" href="source/net/ipv4/netfilter/arp_tables.c#L149">149</a>         <a href="ident?i=memcpy">memcpy</a>(&amp;src_ipaddr, arpptr, sizeof(<a href="ident?i=u32">u32</a>));
<a name="L150" href="source/net/ipv4/netfilter/arp_tables.c#L150">150</a>         arpptr += sizeof(<a href="ident?i=u32">u32</a>);
<a name="L151" href="source/net/ipv4/netfilter/arp_tables.c#L151">151</a>         tgt_devaddr = arpptr;
<a name="L152" href="source/net/ipv4/netfilter/arp_tables.c#L152">152</a>         arpptr += <a href="ident?i=dev">dev</a>-&gt;addr_len;
<a name="L153" href="source/net/ipv4/netfilter/arp_tables.c#L153">153</a>         <a href="ident?i=memcpy">memcpy</a>(&amp;tgt_ipaddr, arpptr, sizeof(<a href="ident?i=u32">u32</a>));
<a name="L154" href="source/net/ipv4/netfilter/arp_tables.c#L154">154</a> 
<a name="L155" href="source/net/ipv4/netfilter/arp_tables.c#L155">155</a>         if (<a href="ident?i=FWINV">FWINV</a>(<a href="ident?i=arp_devaddr_compare">arp_devaddr_compare</a>(&amp;arpinfo-&gt;src_devaddr, src_devaddr, <a href="ident?i=dev">dev</a>-&gt;addr_len),
<a name="L156" href="source/net/ipv4/netfilter/arp_tables.c#L156">156</a>                   <a href="ident?i=ARPT_INV_SRCDEVADDR">ARPT_INV_SRCDEVADDR</a>) ||
<a name="L157" href="source/net/ipv4/netfilter/arp_tables.c#L157">157</a>             <a href="ident?i=FWINV">FWINV</a>(<a href="ident?i=arp_devaddr_compare">arp_devaddr_compare</a>(&amp;arpinfo-&gt;tgt_devaddr, tgt_devaddr, <a href="ident?i=dev">dev</a>-&gt;addr_len),
<a name="L158" href="source/net/ipv4/netfilter/arp_tables.c#L158">158</a>                   <a href="ident?i=ARPT_INV_TGTDEVADDR">ARPT_INV_TGTDEVADDR</a>)) {
<a name="L159" href="source/net/ipv4/netfilter/arp_tables.c#L159">159</a>                 <a href="ident?i=dprintf">dprintf</a>(<i>"Source or target device address mismatch.\n"</i>);
<a name="L160" href="source/net/ipv4/netfilter/arp_tables.c#L160">160</a> 
<a name="L161" href="source/net/ipv4/netfilter/arp_tables.c#L161">161</a>                 return 0;
<a name="L162" href="source/net/ipv4/netfilter/arp_tables.c#L162">162</a>         }
<a name="L163" href="source/net/ipv4/netfilter/arp_tables.c#L163">163</a> 
<a name="L164" href="source/net/ipv4/netfilter/arp_tables.c#L164">164</a>         if (<a href="ident?i=FWINV">FWINV</a>((src_ipaddr &amp; arpinfo-&gt;smsk.s_addr) != arpinfo-&gt;<a href="ident?i=src">src</a>.s_addr,
<a name="L165" href="source/net/ipv4/netfilter/arp_tables.c#L165">165</a>                   <a href="ident?i=ARPT_INV_SRCIP">ARPT_INV_SRCIP</a>) ||
<a name="L166" href="source/net/ipv4/netfilter/arp_tables.c#L166">166</a>             <a href="ident?i=FWINV">FWINV</a>(((tgt_ipaddr &amp; arpinfo-&gt;tmsk.s_addr) != arpinfo-&gt;tgt.s_addr),
<a name="L167" href="source/net/ipv4/netfilter/arp_tables.c#L167">167</a>                   <a href="ident?i=ARPT_INV_TGTIP">ARPT_INV_TGTIP</a>)) {
<a name="L168" href="source/net/ipv4/netfilter/arp_tables.c#L168">168</a>                 <a href="ident?i=dprintf">dprintf</a>(<i>"Source or target IP address mismatch.\n"</i>);
<a name="L169" href="source/net/ipv4/netfilter/arp_tables.c#L169">169</a> 
<a name="L170" href="source/net/ipv4/netfilter/arp_tables.c#L170">170</a>                 <a href="ident?i=dprintf">dprintf</a>(<i>"SRC: %pI4. Mask: %pI4. Target: %pI4.%s\n"</i>,
<a name="L171" href="source/net/ipv4/netfilter/arp_tables.c#L171">171</a>                         &amp;src_ipaddr,
<a name="L172" href="source/net/ipv4/netfilter/arp_tables.c#L172">172</a>                         &amp;arpinfo-&gt;smsk.s_addr,
<a name="L173" href="source/net/ipv4/netfilter/arp_tables.c#L173">173</a>                         &amp;arpinfo-&gt;<a href="ident?i=src">src</a>.s_addr,
<a name="L174" href="source/net/ipv4/netfilter/arp_tables.c#L174">174</a>                         arpinfo-&gt;invflags &amp; <a href="ident?i=ARPT_INV_SRCIP">ARPT_INV_SRCIP</a> ? <i>" (INV)"</i> : <i>""</i>);
<a name="L175" href="source/net/ipv4/netfilter/arp_tables.c#L175">175</a>                 <a href="ident?i=dprintf">dprintf</a>(<i>"TGT: %pI4 Mask: %pI4 Target: %pI4.%s\n"</i>,
<a name="L176" href="source/net/ipv4/netfilter/arp_tables.c#L176">176</a>                         &amp;tgt_ipaddr,
<a name="L177" href="source/net/ipv4/netfilter/arp_tables.c#L177">177</a>                         &amp;arpinfo-&gt;tmsk.s_addr,
<a name="L178" href="source/net/ipv4/netfilter/arp_tables.c#L178">178</a>                         &amp;arpinfo-&gt;tgt.s_addr,
<a name="L179" href="source/net/ipv4/netfilter/arp_tables.c#L179">179</a>                         arpinfo-&gt;invflags &amp; <a href="ident?i=ARPT_INV_TGTIP">ARPT_INV_TGTIP</a> ? <i>" (INV)"</i> : <i>""</i>);
<a name="L180" href="source/net/ipv4/netfilter/arp_tables.c#L180">180</a>                 return 0;
<a name="L181" href="source/net/ipv4/netfilter/arp_tables.c#L181">181</a>         }
<a name="L182" href="source/net/ipv4/netfilter/arp_tables.c#L182">182</a> 
<a name="L183" href="source/net/ipv4/netfilter/arp_tables.c#L183">183</a>         <b><i>/* Look for ifname matches.  */</i></b>
<a name="L184" href="source/net/ipv4/netfilter/arp_tables.c#L184">184</a>         <a href="ident?i=ret">ret</a> = <a href="ident?i=ifname_compare">ifname_compare</a>(indev, arpinfo-&gt;iniface, arpinfo-&gt;iniface_mask);
<a name="L185" href="source/net/ipv4/netfilter/arp_tables.c#L185">185</a> 
<a name="L186" href="source/net/ipv4/netfilter/arp_tables.c#L186">186</a>         if (<a href="ident?i=FWINV">FWINV</a>(<a href="ident?i=ret">ret</a> != 0, <a href="ident?i=ARPT_INV_VIA_IN">ARPT_INV_VIA_IN</a>)) {
<a name="L187" href="source/net/ipv4/netfilter/arp_tables.c#L187">187</a>                 <a href="ident?i=dprintf">dprintf</a>(<i>"VIA in mismatch (%s vs %s).%s\n"</i>,
<a name="L188" href="source/net/ipv4/netfilter/arp_tables.c#L188">188</a>                         indev, arpinfo-&gt;iniface,
<a name="L189" href="source/net/ipv4/netfilter/arp_tables.c#L189">189</a>                         arpinfo-&gt;invflags&amp;<a href="ident?i=ARPT_INV_VIA_IN">ARPT_INV_VIA_IN</a> ?<i>" (INV)"</i>:<i>""</i>);
<a name="L190" href="source/net/ipv4/netfilter/arp_tables.c#L190">190</a>                 return 0;
<a name="L191" href="source/net/ipv4/netfilter/arp_tables.c#L191">191</a>         }
<a name="L192" href="source/net/ipv4/netfilter/arp_tables.c#L192">192</a> 
<a name="L193" href="source/net/ipv4/netfilter/arp_tables.c#L193">193</a>         <a href="ident?i=ret">ret</a> = <a href="ident?i=ifname_compare">ifname_compare</a>(outdev, arpinfo-&gt;outiface, arpinfo-&gt;outiface_mask);
<a name="L194" href="source/net/ipv4/netfilter/arp_tables.c#L194">194</a> 
<a name="L195" href="source/net/ipv4/netfilter/arp_tables.c#L195">195</a>         if (<a href="ident?i=FWINV">FWINV</a>(<a href="ident?i=ret">ret</a> != 0, <a href="ident?i=ARPT_INV_VIA_OUT">ARPT_INV_VIA_OUT</a>)) {
<a name="L196" href="source/net/ipv4/netfilter/arp_tables.c#L196">196</a>                 <a href="ident?i=dprintf">dprintf</a>(<i>"VIA out mismatch (%s vs %s).%s\n"</i>,
<a name="L197" href="source/net/ipv4/netfilter/arp_tables.c#L197">197</a>                         outdev, arpinfo-&gt;outiface,
<a name="L198" href="source/net/ipv4/netfilter/arp_tables.c#L198">198</a>                         arpinfo-&gt;invflags&amp;<a href="ident?i=ARPT_INV_VIA_OUT">ARPT_INV_VIA_OUT</a> ?<i>" (INV)"</i>:<i>""</i>);
<a name="L199" href="source/net/ipv4/netfilter/arp_tables.c#L199">199</a>                 return 0;
<a name="L200" href="source/net/ipv4/netfilter/arp_tables.c#L200">200</a>         }
<a name="L201" href="source/net/ipv4/netfilter/arp_tables.c#L201">201</a> 
<a name="L202" href="source/net/ipv4/netfilter/arp_tables.c#L202">202</a>         return 1;
<a name="L203" href="source/net/ipv4/netfilter/arp_tables.c#L203">203</a> #undef <a href="ident?i=FWINV">FWINV</a>
<a name="L204" href="source/net/ipv4/netfilter/arp_tables.c#L204">204</a> }
<a name="L205" href="source/net/ipv4/netfilter/arp_tables.c#L205">205</a> 
<a name="L206" href="source/net/ipv4/netfilter/arp_tables.c#L206">206</a> static inline int <a href="ident?i=arp_checkentry">arp_checkentry</a>(const struct <a href="ident?i=arpt_arp">arpt_arp</a> *arp)
<a name="L207" href="source/net/ipv4/netfilter/arp_tables.c#L207">207</a> {
<a name="L208" href="source/net/ipv4/netfilter/arp_tables.c#L208">208</a>         if (arp-&gt;<a href="ident?i=flags">flags</a> &amp; ~ARPT_F_MASK) {
<a name="L209" href="source/net/ipv4/netfilter/arp_tables.c#L209">209</a>                 <a href="ident?i=duprintf">duprintf</a>(<i>"Unknown flag bits set: %08X\n"</i>,
<a name="L210" href="source/net/ipv4/netfilter/arp_tables.c#L210">210</a>                          arp-&gt;<a href="ident?i=flags">flags</a> &amp; ~ARPT_F_MASK);
<a name="L211" href="source/net/ipv4/netfilter/arp_tables.c#L211">211</a>                 return 0;
<a name="L212" href="source/net/ipv4/netfilter/arp_tables.c#L212">212</a>         }
<a name="L213" href="source/net/ipv4/netfilter/arp_tables.c#L213">213</a>         if (arp-&gt;invflags &amp; ~ARPT_INV_MASK) {
<a name="L214" href="source/net/ipv4/netfilter/arp_tables.c#L214">214</a>                 <a href="ident?i=duprintf">duprintf</a>(<i>"Unknown invflag bits set: %08X\n"</i>,
<a name="L215" href="source/net/ipv4/netfilter/arp_tables.c#L215">215</a>                          arp-&gt;invflags &amp; ~ARPT_INV_MASK);
<a name="L216" href="source/net/ipv4/netfilter/arp_tables.c#L216">216</a>                 return 0;
<a name="L217" href="source/net/ipv4/netfilter/arp_tables.c#L217">217</a>         }
<a name="L218" href="source/net/ipv4/netfilter/arp_tables.c#L218">218</a> 
<a name="L219" href="source/net/ipv4/netfilter/arp_tables.c#L219">219</a>         return 1;
<a name="L220" href="source/net/ipv4/netfilter/arp_tables.c#L220">220</a> }
<a name="L221" href="source/net/ipv4/netfilter/arp_tables.c#L221">221</a> 
<a name="L222" href="source/net/ipv4/netfilter/arp_tables.c#L222">222</a> static unsigned int
<a name="L223" href="source/net/ipv4/netfilter/arp_tables.c#L223">223</a> <a href="ident?i=arpt_error">arpt_error</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, const struct <a href="ident?i=xt_action_param">xt_action_param</a> *<a href="ident?i=par">par</a>)
<a name="L224" href="source/net/ipv4/netfilter/arp_tables.c#L224">224</a> {
<a name="L225" href="source/net/ipv4/netfilter/arp_tables.c#L225">225</a>         <a href="ident?i=net_err_ratelimited">net_err_ratelimited</a>(<i>"arp_tables: error: '%s'\n"</i>,
<a name="L226" href="source/net/ipv4/netfilter/arp_tables.c#L226">226</a>                             (const char *)<a href="ident?i=par">par</a>-&gt;targinfo);
<a name="L227" href="source/net/ipv4/netfilter/arp_tables.c#L227">227</a> 
<a name="L228" href="source/net/ipv4/netfilter/arp_tables.c#L228">228</a>         return <a href="ident?i=NF_DROP">NF_DROP</a>;
<a name="L229" href="source/net/ipv4/netfilter/arp_tables.c#L229">229</a> }
<a name="L230" href="source/net/ipv4/netfilter/arp_tables.c#L230">230</a> 
<a name="L231" href="source/net/ipv4/netfilter/arp_tables.c#L231">231</a> static inline const struct <a href="ident?i=xt_entry_target">xt_entry_target</a> *
<a name="L232" href="source/net/ipv4/netfilter/arp_tables.c#L232">232</a> <a href="ident?i=arpt_get_target_c">arpt_get_target_c</a>(const struct <a href="ident?i=arpt_entry">arpt_entry</a> *<a href="ident?i=e">e</a>)
<a name="L233" href="source/net/ipv4/netfilter/arp_tables.c#L233">233</a> {
<a name="L234" href="source/net/ipv4/netfilter/arp_tables.c#L234">234</a>         return <a href="ident?i=arpt_get_target">arpt_get_target</a>((struct <a href="ident?i=arpt_entry">arpt_entry</a> *)<a href="ident?i=e">e</a>);
<a name="L235" href="source/net/ipv4/netfilter/arp_tables.c#L235">235</a> }
<a name="L236" href="source/net/ipv4/netfilter/arp_tables.c#L236">236</a> 
<a name="L237" href="source/net/ipv4/netfilter/arp_tables.c#L237">237</a> static inline struct <a href="ident?i=arpt_entry">arpt_entry</a> *
<a name="L238" href="source/net/ipv4/netfilter/arp_tables.c#L238">238</a> <a href="ident?i=get_entry">get_entry</a>(const void *<a href="ident?i=base">base</a>, unsigned int <a href="ident?i=offset">offset</a>)
<a name="L239" href="source/net/ipv4/netfilter/arp_tables.c#L239">239</a> {
<a name="L240" href="source/net/ipv4/netfilter/arp_tables.c#L240">240</a>         return (struct <a href="ident?i=arpt_entry">arpt_entry</a> *)(<a href="ident?i=base">base</a> + <a href="ident?i=offset">offset</a>);
<a name="L241" href="source/net/ipv4/netfilter/arp_tables.c#L241">241</a> }
<a name="L242" href="source/net/ipv4/netfilter/arp_tables.c#L242">242</a> 
<a name="L243" href="source/net/ipv4/netfilter/arp_tables.c#L243">243</a> static inline <a href="ident?i=__pure">__pure</a>
<a name="L244" href="source/net/ipv4/netfilter/arp_tables.c#L244">244</a> struct <a href="ident?i=arpt_entry">arpt_entry</a> *<a href="ident?i=arpt_next_entry">arpt_next_entry</a>(const struct <a href="ident?i=arpt_entry">arpt_entry</a> *<a href="ident?i=entry">entry</a>)
<a name="L245" href="source/net/ipv4/netfilter/arp_tables.c#L245">245</a> {
<a name="L246" href="source/net/ipv4/netfilter/arp_tables.c#L246">246</a>         return (void *)<a href="ident?i=entry">entry</a> + <a href="ident?i=entry">entry</a>-&gt;next_offset;
<a name="L247" href="source/net/ipv4/netfilter/arp_tables.c#L247">247</a> }
<a name="L248" href="source/net/ipv4/netfilter/arp_tables.c#L248">248</a> 
<a name="L249" href="source/net/ipv4/netfilter/arp_tables.c#L249">249</a> unsigned int <a href="ident?i=arpt_do_table">arpt_do_table</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
<a name="L250" href="source/net/ipv4/netfilter/arp_tables.c#L250">250</a>                            unsigned int hook,
<a name="L251" href="source/net/ipv4/netfilter/arp_tables.c#L251">251</a>                            const struct <a href="ident?i=nf_hook_state">nf_hook_state</a> *<a href="ident?i=state">state</a>,
<a name="L252" href="source/net/ipv4/netfilter/arp_tables.c#L252">252</a>                            struct <a href="ident?i=xt_table">xt_table</a> *<a href="ident?i=table">table</a>)
<a name="L253" href="source/net/ipv4/netfilter/arp_tables.c#L253">253</a> {
<a name="L254" href="source/net/ipv4/netfilter/arp_tables.c#L254">254</a>         static const char nulldevname[<a href="ident?i=IFNAMSIZ">IFNAMSIZ</a>] <a href="ident?i=__attribute__">__attribute__</a>((aligned(sizeof(long))));
<a name="L255" href="source/net/ipv4/netfilter/arp_tables.c#L255">255</a>         unsigned int verdict = <a href="ident?i=NF_DROP">NF_DROP</a>;
<a name="L256" href="source/net/ipv4/netfilter/arp_tables.c#L256">256</a>         const struct <a href="ident?i=arphdr">arphdr</a> *arp;
<a name="L257" href="source/net/ipv4/netfilter/arp_tables.c#L257">257</a>         struct <a href="ident?i=arpt_entry">arpt_entry</a> *<a href="ident?i=e">e</a>, *back;
<a name="L258" href="source/net/ipv4/netfilter/arp_tables.c#L258">258</a>         const char *indev, *outdev;
<a name="L259" href="source/net/ipv4/netfilter/arp_tables.c#L259">259</a>         void *table_base;
<a name="L260" href="source/net/ipv4/netfilter/arp_tables.c#L260">260</a>         const struct <a href="ident?i=xt_table_info">xt_table_info</a> *<a href="ident?i=private">private</a>;
<a name="L261" href="source/net/ipv4/netfilter/arp_tables.c#L261">261</a>         struct <a href="ident?i=xt_action_param">xt_action_param</a> acpar;
<a name="L262" href="source/net/ipv4/netfilter/arp_tables.c#L262">262</a>         unsigned int addend;
<a name="L263" href="source/net/ipv4/netfilter/arp_tables.c#L263">263</a> 
<a name="L264" href="source/net/ipv4/netfilter/arp_tables.c#L264">264</a>         if (!<a href="ident?i=pskb_may_pull">pskb_may_pull</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=arp_hdr_len">arp_hdr_len</a>(<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=dev">dev</a>)))
<a name="L265" href="source/net/ipv4/netfilter/arp_tables.c#L265">265</a>                 return <a href="ident?i=NF_DROP">NF_DROP</a>;
<a name="L266" href="source/net/ipv4/netfilter/arp_tables.c#L266">266</a> 
<a name="L267" href="source/net/ipv4/netfilter/arp_tables.c#L267">267</a>         indev = <a href="ident?i=state">state</a>-&gt;<a href="ident?i=in">in</a> ? <a href="ident?i=state">state</a>-&gt;<a href="ident?i=in">in</a>-&gt;<a href="ident?i=name">name</a> : nulldevname;
<a name="L268" href="source/net/ipv4/netfilter/arp_tables.c#L268">268</a>         outdev = <a href="ident?i=state">state</a>-&gt;<a href="ident?i=out">out</a> ? <a href="ident?i=state">state</a>-&gt;<a href="ident?i=out">out</a>-&gt;<a href="ident?i=name">name</a> : nulldevname;
<a name="L269" href="source/net/ipv4/netfilter/arp_tables.c#L269">269</a> 
<a name="L270" href="source/net/ipv4/netfilter/arp_tables.c#L270">270</a>         <a href="ident?i=local_bh_disable">local_bh_disable</a>();
<a name="L271" href="source/net/ipv4/netfilter/arp_tables.c#L271">271</a>         addend = <a href="ident?i=xt_write_recseq_begin">xt_write_recseq_begin</a>();
<a name="L272" href="source/net/ipv4/netfilter/arp_tables.c#L272">272</a>         <a href="ident?i=private">private</a> = <a href="ident?i=table">table</a>-&gt;<a href="ident?i=private">private</a>;
<a name="L273" href="source/net/ipv4/netfilter/arp_tables.c#L273">273</a>         <b><i>/*</i></b>
<a name="L274" href="source/net/ipv4/netfilter/arp_tables.c#L274">274</a> <b><i>         * Ensure we load private-&gt; members after we've fetched the base</i></b>
<a name="L275" href="source/net/ipv4/netfilter/arp_tables.c#L275">275</a> <b><i>         * pointer.</i></b>
<a name="L276" href="source/net/ipv4/netfilter/arp_tables.c#L276">276</a> <b><i>         */</i></b>
<a name="L277" href="source/net/ipv4/netfilter/arp_tables.c#L277">277</a>         <a href="ident?i=smp_read_barrier_depends">smp_read_barrier_depends</a>();
<a name="L278" href="source/net/ipv4/netfilter/arp_tables.c#L278">278</a>         table_base = <a href="ident?i=private">private</a>-&gt;<a href="ident?i=entries">entries</a>[<a href="ident?i=smp_processor_id">smp_processor_id</a>()];
<a name="L279" href="source/net/ipv4/netfilter/arp_tables.c#L279">279</a> 
<a name="L280" href="source/net/ipv4/netfilter/arp_tables.c#L280">280</a>         <a href="ident?i=e">e</a> = <a href="ident?i=get_entry">get_entry</a>(table_base, <a href="ident?i=private">private</a>-&gt;hook_entry[hook]);
<a name="L281" href="source/net/ipv4/netfilter/arp_tables.c#L281">281</a>         back = <a href="ident?i=get_entry">get_entry</a>(table_base, <a href="ident?i=private">private</a>-&gt;underflow[hook]);
<a name="L282" href="source/net/ipv4/netfilter/arp_tables.c#L282">282</a> 
<a name="L283" href="source/net/ipv4/netfilter/arp_tables.c#L283">283</a>         acpar.<a href="ident?i=in">in</a>      = <a href="ident?i=state">state</a>-&gt;<a href="ident?i=in">in</a>;
<a name="L284" href="source/net/ipv4/netfilter/arp_tables.c#L284">284</a>         acpar.<a href="ident?i=out">out</a>     = <a href="ident?i=state">state</a>-&gt;<a href="ident?i=out">out</a>;
<a name="L285" href="source/net/ipv4/netfilter/arp_tables.c#L285">285</a>         acpar.hooknum = hook;
<a name="L286" href="source/net/ipv4/netfilter/arp_tables.c#L286">286</a>         acpar.<a href="ident?i=family">family</a>  = NFPROTO_ARP;
<a name="L287" href="source/net/ipv4/netfilter/arp_tables.c#L287">287</a>         acpar.hotdrop = <a href="ident?i=false">false</a>;
<a name="L288" href="source/net/ipv4/netfilter/arp_tables.c#L288">288</a> 
<a name="L289" href="source/net/ipv4/netfilter/arp_tables.c#L289">289</a>         arp = <a href="ident?i=arp_hdr">arp_hdr</a>(<a href="ident?i=skb">skb</a>);
<a name="L290" href="source/net/ipv4/netfilter/arp_tables.c#L290">290</a>         do {
<a name="L291" href="source/net/ipv4/netfilter/arp_tables.c#L291">291</a>                 const struct <a href="ident?i=xt_entry_target">xt_entry_target</a> *<a href="ident?i=t">t</a>;
<a name="L292" href="source/net/ipv4/netfilter/arp_tables.c#L292">292</a> 
<a name="L293" href="source/net/ipv4/netfilter/arp_tables.c#L293">293</a>                 if (!<a href="ident?i=arp_packet_match">arp_packet_match</a>(arp, <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=dev">dev</a>, indev, outdev, &amp;<a href="ident?i=e">e</a>-&gt;arp)) {
<a name="L294" href="source/net/ipv4/netfilter/arp_tables.c#L294">294</a>                         <a href="ident?i=e">e</a> = <a href="ident?i=arpt_next_entry">arpt_next_entry</a>(<a href="ident?i=e">e</a>);
<a name="L295" href="source/net/ipv4/netfilter/arp_tables.c#L295">295</a>                         continue;
<a name="L296" href="source/net/ipv4/netfilter/arp_tables.c#L296">296</a>                 }
<a name="L297" href="source/net/ipv4/netfilter/arp_tables.c#L297">297</a> 
<a name="L298" href="source/net/ipv4/netfilter/arp_tables.c#L298">298</a>                 <a href="ident?i=ADD_COUNTER">ADD_COUNTER</a>(<a href="ident?i=e">e</a>-&gt;counters, <a href="ident?i=arp_hdr_len">arp_hdr_len</a>(<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=dev">dev</a>), 1);
<a name="L299" href="source/net/ipv4/netfilter/arp_tables.c#L299">299</a> 
<a name="L300" href="source/net/ipv4/netfilter/arp_tables.c#L300">300</a>                 <a href="ident?i=t">t</a> = <a href="ident?i=arpt_get_target_c">arpt_get_target_c</a>(<a href="ident?i=e">e</a>);
<a name="L301" href="source/net/ipv4/netfilter/arp_tables.c#L301">301</a> 
<a name="L302" href="source/net/ipv4/netfilter/arp_tables.c#L302">302</a>                 <b><i>/* Standard target? */</i></b>
<a name="L303" href="source/net/ipv4/netfilter/arp_tables.c#L303">303</a>                 if (!<a href="ident?i=t">t</a>-&gt;u.kernel.<a href="ident?i=target">target</a>-&gt;<a href="ident?i=target">target</a>) {
<a name="L304" href="source/net/ipv4/netfilter/arp_tables.c#L304">304</a>                         int <a href="ident?i=v">v</a>;
<a name="L305" href="source/net/ipv4/netfilter/arp_tables.c#L305">305</a> 
<a name="L306" href="source/net/ipv4/netfilter/arp_tables.c#L306">306</a>                         <a href="ident?i=v">v</a> = ((struct <a href="ident?i=xt_standard_target">xt_standard_target</a> *)<a href="ident?i=t">t</a>)-&gt;verdict;
<a name="L307" href="source/net/ipv4/netfilter/arp_tables.c#L307">307</a>                         if (<a href="ident?i=v">v</a> &lt; 0) {
<a name="L308" href="source/net/ipv4/netfilter/arp_tables.c#L308">308</a>                                 <b><i>/* Pop from stack? */</i></b>
<a name="L309" href="source/net/ipv4/netfilter/arp_tables.c#L309">309</a>                                 if (<a href="ident?i=v">v</a> != <a href="ident?i=XT_RETURN">XT_RETURN</a>) {
<a name="L310" href="source/net/ipv4/netfilter/arp_tables.c#L310">310</a>                                         verdict = (unsigned int)(-<a href="ident?i=v">v</a>) - 1;
<a name="L311" href="source/net/ipv4/netfilter/arp_tables.c#L311">311</a>                                         break;
<a name="L312" href="source/net/ipv4/netfilter/arp_tables.c#L312">312</a>                                 }
<a name="L313" href="source/net/ipv4/netfilter/arp_tables.c#L313">313</a>                                 <a href="ident?i=e">e</a> = back;
<a name="L314" href="source/net/ipv4/netfilter/arp_tables.c#L314">314</a>                                 back = <a href="ident?i=get_entry">get_entry</a>(table_base, back-&gt;comefrom);
<a name="L315" href="source/net/ipv4/netfilter/arp_tables.c#L315">315</a>                                 continue;
<a name="L316" href="source/net/ipv4/netfilter/arp_tables.c#L316">316</a>                         }
<a name="L317" href="source/net/ipv4/netfilter/arp_tables.c#L317">317</a>                         if (table_base + <a href="ident?i=v">v</a>
<a name="L318" href="source/net/ipv4/netfilter/arp_tables.c#L318">318</a>                             != <a href="ident?i=arpt_next_entry">arpt_next_entry</a>(<a href="ident?i=e">e</a>)) {
<a name="L319" href="source/net/ipv4/netfilter/arp_tables.c#L319">319</a>                                 <b><i>/* Save old back ptr in next entry */</i></b>
<a name="L320" href="source/net/ipv4/netfilter/arp_tables.c#L320">320</a>                                 struct <a href="ident?i=arpt_entry">arpt_entry</a> *<a href="ident?i=next">next</a> = <a href="ident?i=arpt_next_entry">arpt_next_entry</a>(<a href="ident?i=e">e</a>);
<a name="L321" href="source/net/ipv4/netfilter/arp_tables.c#L321">321</a>                                 <a href="ident?i=next">next</a>-&gt;comefrom = (void *)back - table_base;
<a name="L322" href="source/net/ipv4/netfilter/arp_tables.c#L322">322</a> 
<a name="L323" href="source/net/ipv4/netfilter/arp_tables.c#L323">323</a>                                 <b><i>/* set back pointer to next entry */</i></b>
<a name="L324" href="source/net/ipv4/netfilter/arp_tables.c#L324">324</a>                                 back = <a href="ident?i=next">next</a>;
<a name="L325" href="source/net/ipv4/netfilter/arp_tables.c#L325">325</a>                         }
<a name="L326" href="source/net/ipv4/netfilter/arp_tables.c#L326">326</a> 
<a name="L327" href="source/net/ipv4/netfilter/arp_tables.c#L327">327</a>                         <a href="ident?i=e">e</a> = <a href="ident?i=get_entry">get_entry</a>(table_base, <a href="ident?i=v">v</a>);
<a name="L328" href="source/net/ipv4/netfilter/arp_tables.c#L328">328</a>                         continue;
<a name="L329" href="source/net/ipv4/netfilter/arp_tables.c#L329">329</a>                 }
<a name="L330" href="source/net/ipv4/netfilter/arp_tables.c#L330">330</a> 
<a name="L331" href="source/net/ipv4/netfilter/arp_tables.c#L331">331</a>                 <b><i>/* Targets which reenter must return</i></b>
<a name="L332" href="source/net/ipv4/netfilter/arp_tables.c#L332">332</a> <b><i>                 * abs. verdicts</i></b>
<a name="L333" href="source/net/ipv4/netfilter/arp_tables.c#L333">333</a> <b><i>                 */</i></b>
<a name="L334" href="source/net/ipv4/netfilter/arp_tables.c#L334">334</a>                 acpar.<a href="ident?i=target">target</a>   = <a href="ident?i=t">t</a>-&gt;u.kernel.<a href="ident?i=target">target</a>;
<a name="L335" href="source/net/ipv4/netfilter/arp_tables.c#L335">335</a>                 acpar.targinfo = <a href="ident?i=t">t</a>-&gt;<a href="ident?i=data">data</a>;
<a name="L336" href="source/net/ipv4/netfilter/arp_tables.c#L336">336</a>                 verdict = <a href="ident?i=t">t</a>-&gt;u.kernel.<a href="ident?i=target">target</a>-&gt;<a href="ident?i=target">target</a>(<a href="ident?i=skb">skb</a>, &amp;acpar);
<a name="L337" href="source/net/ipv4/netfilter/arp_tables.c#L337">337</a> 
<a name="L338" href="source/net/ipv4/netfilter/arp_tables.c#L338">338</a>                 <b><i>/* Target might have changed stuff. */</i></b>
<a name="L339" href="source/net/ipv4/netfilter/arp_tables.c#L339">339</a>                 arp = <a href="ident?i=arp_hdr">arp_hdr</a>(<a href="ident?i=skb">skb</a>);
<a name="L340" href="source/net/ipv4/netfilter/arp_tables.c#L340">340</a> 
<a name="L341" href="source/net/ipv4/netfilter/arp_tables.c#L341">341</a>                 if (verdict == <a href="ident?i=XT_CONTINUE">XT_CONTINUE</a>)
<a name="L342" href="source/net/ipv4/netfilter/arp_tables.c#L342">342</a>                         <a href="ident?i=e">e</a> = <a href="ident?i=arpt_next_entry">arpt_next_entry</a>(<a href="ident?i=e">e</a>);
<a name="L343" href="source/net/ipv4/netfilter/arp_tables.c#L343">343</a>                 else
<a name="L344" href="source/net/ipv4/netfilter/arp_tables.c#L344">344</a>                         <b><i>/* Verdict */</i></b>
<a name="L345" href="source/net/ipv4/netfilter/arp_tables.c#L345">345</a>                         break;
<a name="L346" href="source/net/ipv4/netfilter/arp_tables.c#L346">346</a>         } while (!acpar.hotdrop);
<a name="L347" href="source/net/ipv4/netfilter/arp_tables.c#L347">347</a>         <a href="ident?i=xt_write_recseq_end">xt_write_recseq_end</a>(addend);
<a name="L348" href="source/net/ipv4/netfilter/arp_tables.c#L348">348</a>         <a href="ident?i=local_bh_enable">local_bh_enable</a>();
<a name="L349" href="source/net/ipv4/netfilter/arp_tables.c#L349">349</a> 
<a name="L350" href="source/net/ipv4/netfilter/arp_tables.c#L350">350</a>         if (acpar.hotdrop)
<a name="L351" href="source/net/ipv4/netfilter/arp_tables.c#L351">351</a>                 return <a href="ident?i=NF_DROP">NF_DROP</a>;
<a name="L352" href="source/net/ipv4/netfilter/arp_tables.c#L352">352</a>         else
<a name="L353" href="source/net/ipv4/netfilter/arp_tables.c#L353">353</a>                 return verdict;
<a name="L354" href="source/net/ipv4/netfilter/arp_tables.c#L354">354</a> }
<a name="L355" href="source/net/ipv4/netfilter/arp_tables.c#L355">355</a> 
<a name="L356" href="source/net/ipv4/netfilter/arp_tables.c#L356">356</a> <b><i>/* All zeroes == unconditional rule. */</i></b>
<a name="L357" href="source/net/ipv4/netfilter/arp_tables.c#L357">357</a> static inline <a href="ident?i=bool">bool</a> <a href="ident?i=unconditional">unconditional</a>(const struct <a href="ident?i=arpt_arp">arpt_arp</a> *arp)
<a name="L358" href="source/net/ipv4/netfilter/arp_tables.c#L358">358</a> {
<a name="L359" href="source/net/ipv4/netfilter/arp_tables.c#L359">359</a>         static const struct <a href="ident?i=arpt_arp">arpt_arp</a> uncond;
<a name="L360" href="source/net/ipv4/netfilter/arp_tables.c#L360">360</a> 
<a name="L361" href="source/net/ipv4/netfilter/arp_tables.c#L361">361</a>         return <a href="ident?i=memcmp">memcmp</a>(arp, &amp;uncond, sizeof(uncond)) == 0;
<a name="L362" href="source/net/ipv4/netfilter/arp_tables.c#L362">362</a> }
<a name="L363" href="source/net/ipv4/netfilter/arp_tables.c#L363">363</a> 
<a name="L364" href="source/net/ipv4/netfilter/arp_tables.c#L364">364</a> <b><i>/* Figures out from what hook each rule can be called: returns 0 if</i></b>
<a name="L365" href="source/net/ipv4/netfilter/arp_tables.c#L365">365</a> <b><i> * there are loops.  Puts hook bitmask in comefrom.</i></b>
<a name="L366" href="source/net/ipv4/netfilter/arp_tables.c#L366">366</a> <b><i> */</i></b>
<a name="L367" href="source/net/ipv4/netfilter/arp_tables.c#L367">367</a> static int <a href="ident?i=mark_source_chains">mark_source_chains</a>(const struct <a href="ident?i=xt_table_info">xt_table_info</a> *newinfo,
<a name="L368" href="source/net/ipv4/netfilter/arp_tables.c#L368">368</a>                               unsigned int valid_hooks, void *entry0)
<a name="L369" href="source/net/ipv4/netfilter/arp_tables.c#L369">369</a> {
<a name="L370" href="source/net/ipv4/netfilter/arp_tables.c#L370">370</a>         unsigned int hook;
<a name="L371" href="source/net/ipv4/netfilter/arp_tables.c#L371">371</a> 
<a name="L372" href="source/net/ipv4/netfilter/arp_tables.c#L372">372</a>         <b><i>/* No recursion; use packet counter to save back ptrs (reset</i></b>
<a name="L373" href="source/net/ipv4/netfilter/arp_tables.c#L373">373</a> <b><i>         * to 0 as we leave), and comefrom to save source hook bitmask.</i></b>
<a name="L374" href="source/net/ipv4/netfilter/arp_tables.c#L374">374</a> <b><i>         */</i></b>
<a name="L375" href="source/net/ipv4/netfilter/arp_tables.c#L375">375</a>         for (hook = 0; hook &lt; <a href="ident?i=NF_ARP_NUMHOOKS">NF_ARP_NUMHOOKS</a>; hook++) {
<a name="L376" href="source/net/ipv4/netfilter/arp_tables.c#L376">376</a>                 unsigned int <a href="ident?i=pos">pos</a> = newinfo-&gt;hook_entry[hook];
<a name="L377" href="source/net/ipv4/netfilter/arp_tables.c#L377">377</a>                 struct <a href="ident?i=arpt_entry">arpt_entry</a> *<a href="ident?i=e">e</a>
<a name="L378" href="source/net/ipv4/netfilter/arp_tables.c#L378">378</a>                         = (struct <a href="ident?i=arpt_entry">arpt_entry</a> *)(entry0 + <a href="ident?i=pos">pos</a>);
<a name="L379" href="source/net/ipv4/netfilter/arp_tables.c#L379">379</a> 
<a name="L380" href="source/net/ipv4/netfilter/arp_tables.c#L380">380</a>                 if (!(valid_hooks &amp; (1 &lt;&lt; hook)))
<a name="L381" href="source/net/ipv4/netfilter/arp_tables.c#L381">381</a>                         continue;
<a name="L382" href="source/net/ipv4/netfilter/arp_tables.c#L382">382</a> 
<a name="L383" href="source/net/ipv4/netfilter/arp_tables.c#L383">383</a>                 <b><i>/* Set initial back pointer. */</i></b>
<a name="L384" href="source/net/ipv4/netfilter/arp_tables.c#L384">384</a>                 <a href="ident?i=e">e</a>-&gt;counters.pcnt = <a href="ident?i=pos">pos</a>;
<a name="L385" href="source/net/ipv4/netfilter/arp_tables.c#L385">385</a> 
<a name="L386" href="source/net/ipv4/netfilter/arp_tables.c#L386">386</a>                 for (;;) {
<a name="L387" href="source/net/ipv4/netfilter/arp_tables.c#L387">387</a>                         const struct <a href="ident?i=xt_standard_target">xt_standard_target</a> *<a href="ident?i=t">t</a>
<a name="L388" href="source/net/ipv4/netfilter/arp_tables.c#L388">388</a>                                 = (void *)<a href="ident?i=arpt_get_target_c">arpt_get_target_c</a>(<a href="ident?i=e">e</a>);
<a name="L389" href="source/net/ipv4/netfilter/arp_tables.c#L389">389</a>                         int visited = <a href="ident?i=e">e</a>-&gt;comefrom &amp; (1 &lt;&lt; hook);
<a name="L390" href="source/net/ipv4/netfilter/arp_tables.c#L390">390</a> 
<a name="L391" href="source/net/ipv4/netfilter/arp_tables.c#L391">391</a>                         if (<a href="ident?i=e">e</a>-&gt;comefrom &amp; (1 &lt;&lt; <a href="ident?i=NF_ARP_NUMHOOKS">NF_ARP_NUMHOOKS</a>)) {
<a name="L392" href="source/net/ipv4/netfilter/arp_tables.c#L392">392</a>                                 <a href="ident?i=pr_notice">pr_notice</a>(<i>"arptables: loop hook %u pos %u %08X.\n"</i>,
<a name="L393" href="source/net/ipv4/netfilter/arp_tables.c#L393">393</a>                                        hook, <a href="ident?i=pos">pos</a>, <a href="ident?i=e">e</a>-&gt;comefrom);
<a name="L394" href="source/net/ipv4/netfilter/arp_tables.c#L394">394</a>                                 return 0;
<a name="L395" href="source/net/ipv4/netfilter/arp_tables.c#L395">395</a>                         }
<a name="L396" href="source/net/ipv4/netfilter/arp_tables.c#L396">396</a>                         <a href="ident?i=e">e</a>-&gt;comefrom
<a name="L397" href="source/net/ipv4/netfilter/arp_tables.c#L397">397</a>                                 |= ((1 &lt;&lt; hook) | (1 &lt;&lt; <a href="ident?i=NF_ARP_NUMHOOKS">NF_ARP_NUMHOOKS</a>));
<a name="L398" href="source/net/ipv4/netfilter/arp_tables.c#L398">398</a> 
<a name="L399" href="source/net/ipv4/netfilter/arp_tables.c#L399">399</a>                         <b><i>/* Unconditional return/END. */</i></b>
<a name="L400" href="source/net/ipv4/netfilter/arp_tables.c#L400">400</a>                         if ((<a href="ident?i=e">e</a>-&gt;target_offset == sizeof(struct <a href="ident?i=arpt_entry">arpt_entry</a>) &amp;&amp;
<a name="L401" href="source/net/ipv4/netfilter/arp_tables.c#L401">401</a>                              (<a href="ident?i=strcmp">strcmp</a>(<a href="ident?i=t">t</a>-&gt;<a href="ident?i=target">target</a>.u.<a href="ident?i=user">user</a>.<a href="ident?i=name">name</a>,
<a name="L402" href="source/net/ipv4/netfilter/arp_tables.c#L402">402</a>                                      <a href="ident?i=XT_STANDARD_TARGET">XT_STANDARD_TARGET</a>) == 0) &amp;&amp;
<a name="L403" href="source/net/ipv4/netfilter/arp_tables.c#L403">403</a>                              <a href="ident?i=t">t</a>-&gt;verdict &lt; 0 &amp;&amp; <a href="ident?i=unconditional">unconditional</a>(&amp;<a href="ident?i=e">e</a>-&gt;arp)) ||
<a name="L404" href="source/net/ipv4/netfilter/arp_tables.c#L404">404</a>                             visited) {
<a name="L405" href="source/net/ipv4/netfilter/arp_tables.c#L405">405</a>                                 unsigned int oldpos, <a href="ident?i=size">size</a>;
<a name="L406" href="source/net/ipv4/netfilter/arp_tables.c#L406">406</a> 
<a name="L407" href="source/net/ipv4/netfilter/arp_tables.c#L407">407</a>                                 if ((<a href="ident?i=strcmp">strcmp</a>(<a href="ident?i=t">t</a>-&gt;<a href="ident?i=target">target</a>.u.<a href="ident?i=user">user</a>.<a href="ident?i=name">name</a>,
<a name="L408" href="source/net/ipv4/netfilter/arp_tables.c#L408">408</a>                                             <a href="ident?i=XT_STANDARD_TARGET">XT_STANDARD_TARGET</a>) == 0) &amp;&amp;
<a name="L409" href="source/net/ipv4/netfilter/arp_tables.c#L409">409</a>                                     <a href="ident?i=t">t</a>-&gt;verdict &lt; -<a href="ident?i=NF_MAX_VERDICT">NF_MAX_VERDICT</a> - 1) {
<a name="L410" href="source/net/ipv4/netfilter/arp_tables.c#L410">410</a>                                         <a href="ident?i=duprintf">duprintf</a>(<i>"mark_source_chains: bad "</i>
<a name="L411" href="source/net/ipv4/netfilter/arp_tables.c#L411">411</a>                                                 <i>"negative verdict (%i)\n"</i>,
<a name="L412" href="source/net/ipv4/netfilter/arp_tables.c#L412">412</a>                                                                 <a href="ident?i=t">t</a>-&gt;verdict);
<a name="L413" href="source/net/ipv4/netfilter/arp_tables.c#L413">413</a>                                         return 0;
<a name="L414" href="source/net/ipv4/netfilter/arp_tables.c#L414">414</a>                                 }
<a name="L415" href="source/net/ipv4/netfilter/arp_tables.c#L415">415</a> 
<a name="L416" href="source/net/ipv4/netfilter/arp_tables.c#L416">416</a>                                 <b><i>/* Return: backtrack through the last</i></b>
<a name="L417" href="source/net/ipv4/netfilter/arp_tables.c#L417">417</a> <b><i>                                 * big jump.</i></b>
<a name="L418" href="source/net/ipv4/netfilter/arp_tables.c#L418">418</a> <b><i>                                 */</i></b>
<a name="L419" href="source/net/ipv4/netfilter/arp_tables.c#L419">419</a>                                 do {
<a name="L420" href="source/net/ipv4/netfilter/arp_tables.c#L420">420</a>                                         <a href="ident?i=e">e</a>-&gt;comefrom ^= (1&lt;&lt;<a href="ident?i=NF_ARP_NUMHOOKS">NF_ARP_NUMHOOKS</a>);
<a name="L421" href="source/net/ipv4/netfilter/arp_tables.c#L421">421</a>                                         oldpos = <a href="ident?i=pos">pos</a>;
<a name="L422" href="source/net/ipv4/netfilter/arp_tables.c#L422">422</a>                                         <a href="ident?i=pos">pos</a> = <a href="ident?i=e">e</a>-&gt;counters.pcnt;
<a name="L423" href="source/net/ipv4/netfilter/arp_tables.c#L423">423</a>                                         <a href="ident?i=e">e</a>-&gt;counters.pcnt = 0;
<a name="L424" href="source/net/ipv4/netfilter/arp_tables.c#L424">424</a> 
<a name="L425" href="source/net/ipv4/netfilter/arp_tables.c#L425">425</a>                                         <b><i>/* We're at the start. */</i></b>
<a name="L426" href="source/net/ipv4/netfilter/arp_tables.c#L426">426</a>                                         if (<a href="ident?i=pos">pos</a> == oldpos)
<a name="L427" href="source/net/ipv4/netfilter/arp_tables.c#L427">427</a>                                                 goto <a href="ident?i=next">next</a>;
<a name="L428" href="source/net/ipv4/netfilter/arp_tables.c#L428">428</a> 
<a name="L429" href="source/net/ipv4/netfilter/arp_tables.c#L429">429</a>                                         <a href="ident?i=e">e</a> = (struct <a href="ident?i=arpt_entry">arpt_entry</a> *)
<a name="L430" href="source/net/ipv4/netfilter/arp_tables.c#L430">430</a>                                                 (entry0 + <a href="ident?i=pos">pos</a>);
<a name="L431" href="source/net/ipv4/netfilter/arp_tables.c#L431">431</a>                                 } while (oldpos == <a href="ident?i=pos">pos</a> + <a href="ident?i=e">e</a>-&gt;next_offset);
<a name="L432" href="source/net/ipv4/netfilter/arp_tables.c#L432">432</a> 
<a name="L433" href="source/net/ipv4/netfilter/arp_tables.c#L433">433</a>                                 <b><i>/* Move along one */</i></b>
<a name="L434" href="source/net/ipv4/netfilter/arp_tables.c#L434">434</a>                                 <a href="ident?i=size">size</a> = <a href="ident?i=e">e</a>-&gt;next_offset;
<a name="L435" href="source/net/ipv4/netfilter/arp_tables.c#L435">435</a>                                 <a href="ident?i=e">e</a> = (struct <a href="ident?i=arpt_entry">arpt_entry</a> *)
<a name="L436" href="source/net/ipv4/netfilter/arp_tables.c#L436">436</a>                                         (entry0 + <a href="ident?i=pos">pos</a> + <a href="ident?i=size">size</a>);
<a name="L437" href="source/net/ipv4/netfilter/arp_tables.c#L437">437</a>                                 <a href="ident?i=e">e</a>-&gt;counters.pcnt = <a href="ident?i=pos">pos</a>;
<a name="L438" href="source/net/ipv4/netfilter/arp_tables.c#L438">438</a>                                 <a href="ident?i=pos">pos</a> += <a href="ident?i=size">size</a>;
<a name="L439" href="source/net/ipv4/netfilter/arp_tables.c#L439">439</a>                         } else {
<a name="L440" href="source/net/ipv4/netfilter/arp_tables.c#L440">440</a>                                 int newpos = <a href="ident?i=t">t</a>-&gt;verdict;
<a name="L441" href="source/net/ipv4/netfilter/arp_tables.c#L441">441</a> 
<a name="L442" href="source/net/ipv4/netfilter/arp_tables.c#L442">442</a>                                 if (<a href="ident?i=strcmp">strcmp</a>(<a href="ident?i=t">t</a>-&gt;<a href="ident?i=target">target</a>.u.<a href="ident?i=user">user</a>.<a href="ident?i=name">name</a>,
<a name="L443" href="source/net/ipv4/netfilter/arp_tables.c#L443">443</a>                                            <a href="ident?i=XT_STANDARD_TARGET">XT_STANDARD_TARGET</a>) == 0 &amp;&amp;
<a name="L444" href="source/net/ipv4/netfilter/arp_tables.c#L444">444</a>                                     newpos &gt;= 0) {
<a name="L445" href="source/net/ipv4/netfilter/arp_tables.c#L445">445</a>                                         if (newpos &gt; newinfo-&gt;<a href="ident?i=size">size</a> -
<a name="L446" href="source/net/ipv4/netfilter/arp_tables.c#L446">446</a>                                                 sizeof(struct <a href="ident?i=arpt_entry">arpt_entry</a>)) {
<a name="L447" href="source/net/ipv4/netfilter/arp_tables.c#L447">447</a>                                                 <a href="ident?i=duprintf">duprintf</a>(<i>"mark_source_chains: "</i>
<a name="L448" href="source/net/ipv4/netfilter/arp_tables.c#L448">448</a>                                                         <i>"bad verdict (%i)\n"</i>,
<a name="L449" href="source/net/ipv4/netfilter/arp_tables.c#L449">449</a>                                                                 newpos);
<a name="L450" href="source/net/ipv4/netfilter/arp_tables.c#L450">450</a>                                                 return 0;
<a name="L451" href="source/net/ipv4/netfilter/arp_tables.c#L451">451</a>                                         }
<a name="L452" href="source/net/ipv4/netfilter/arp_tables.c#L452">452</a> 
<a name="L453" href="source/net/ipv4/netfilter/arp_tables.c#L453">453</a>                                         <b><i>/* This a jump; chase it. */</i></b>
<a name="L454" href="source/net/ipv4/netfilter/arp_tables.c#L454">454</a>                                         <a href="ident?i=duprintf">duprintf</a>(<i>"Jump rule %u -&gt; %u\n"</i>,
<a name="L455" href="source/net/ipv4/netfilter/arp_tables.c#L455">455</a>                                                  <a href="ident?i=pos">pos</a>, newpos);
<a name="L456" href="source/net/ipv4/netfilter/arp_tables.c#L456">456</a>                                 } else {
<a name="L457" href="source/net/ipv4/netfilter/arp_tables.c#L457">457</a>                                         <b><i>/* ... this is a fallthru */</i></b>
<a name="L458" href="source/net/ipv4/netfilter/arp_tables.c#L458">458</a>                                         newpos = <a href="ident?i=pos">pos</a> + <a href="ident?i=e">e</a>-&gt;next_offset;
<a name="L459" href="source/net/ipv4/netfilter/arp_tables.c#L459">459</a>                                 }
<a name="L460" href="source/net/ipv4/netfilter/arp_tables.c#L460">460</a>                                 <a href="ident?i=e">e</a> = (struct <a href="ident?i=arpt_entry">arpt_entry</a> *)
<a name="L461" href="source/net/ipv4/netfilter/arp_tables.c#L461">461</a>                                         (entry0 + newpos);
<a name="L462" href="source/net/ipv4/netfilter/arp_tables.c#L462">462</a>                                 <a href="ident?i=e">e</a>-&gt;counters.pcnt = <a href="ident?i=pos">pos</a>;
<a name="L463" href="source/net/ipv4/netfilter/arp_tables.c#L463">463</a>                                 <a href="ident?i=pos">pos</a> = newpos;
<a name="L464" href="source/net/ipv4/netfilter/arp_tables.c#L464">464</a>                         }
<a name="L465" href="source/net/ipv4/netfilter/arp_tables.c#L465">465</a>                 }
<a name="L466" href="source/net/ipv4/netfilter/arp_tables.c#L466">466</a>                 <a href="ident?i=next">next</a>:
<a name="L467" href="source/net/ipv4/netfilter/arp_tables.c#L467">467</a>                 <a href="ident?i=duprintf">duprintf</a>(<i>"Finished chain %u\n"</i>, hook);
<a name="L468" href="source/net/ipv4/netfilter/arp_tables.c#L468">468</a>         }
<a name="L469" href="source/net/ipv4/netfilter/arp_tables.c#L469">469</a>         return 1;
<a name="L470" href="source/net/ipv4/netfilter/arp_tables.c#L470">470</a> }
<a name="L471" href="source/net/ipv4/netfilter/arp_tables.c#L471">471</a> 
<a name="L472" href="source/net/ipv4/netfilter/arp_tables.c#L472">472</a> static inline int <a href="ident?i=check_entry">check_entry</a>(const struct <a href="ident?i=arpt_entry">arpt_entry</a> *<a href="ident?i=e">e</a>, const char *<a href="ident?i=name">name</a>)
<a name="L473" href="source/net/ipv4/netfilter/arp_tables.c#L473">473</a> {
<a name="L474" href="source/net/ipv4/netfilter/arp_tables.c#L474">474</a>         const struct <a href="ident?i=xt_entry_target">xt_entry_target</a> *<a href="ident?i=t">t</a>;
<a name="L475" href="source/net/ipv4/netfilter/arp_tables.c#L475">475</a> 
<a name="L476" href="source/net/ipv4/netfilter/arp_tables.c#L476">476</a>         if (!<a href="ident?i=arp_checkentry">arp_checkentry</a>(&amp;<a href="ident?i=e">e</a>-&gt;arp)) {
<a name="L477" href="source/net/ipv4/netfilter/arp_tables.c#L477">477</a>                 <a href="ident?i=duprintf">duprintf</a>(<i>"arp_tables: arp check failed %p %s.\n"</i>, <a href="ident?i=e">e</a>, <a href="ident?i=name">name</a>);
<a name="L478" href="source/net/ipv4/netfilter/arp_tables.c#L478">478</a>                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L479" href="source/net/ipv4/netfilter/arp_tables.c#L479">479</a>         }
<a name="L480" href="source/net/ipv4/netfilter/arp_tables.c#L480">480</a> 
<a name="L481" href="source/net/ipv4/netfilter/arp_tables.c#L481">481</a>         if (<a href="ident?i=e">e</a>-&gt;target_offset + sizeof(struct <a href="ident?i=xt_entry_target">xt_entry_target</a>) &gt; <a href="ident?i=e">e</a>-&gt;next_offset)
<a name="L482" href="source/net/ipv4/netfilter/arp_tables.c#L482">482</a>                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L483" href="source/net/ipv4/netfilter/arp_tables.c#L483">483</a> 
<a name="L484" href="source/net/ipv4/netfilter/arp_tables.c#L484">484</a>         <a href="ident?i=t">t</a> = <a href="ident?i=arpt_get_target_c">arpt_get_target_c</a>(<a href="ident?i=e">e</a>);
<a name="L485" href="source/net/ipv4/netfilter/arp_tables.c#L485">485</a>         if (<a href="ident?i=e">e</a>-&gt;target_offset + <a href="ident?i=t">t</a>-&gt;u.target_size &gt; <a href="ident?i=e">e</a>-&gt;next_offset)
<a name="L486" href="source/net/ipv4/netfilter/arp_tables.c#L486">486</a>                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L487" href="source/net/ipv4/netfilter/arp_tables.c#L487">487</a> 
<a name="L488" href="source/net/ipv4/netfilter/arp_tables.c#L488">488</a>         return 0;
<a name="L489" href="source/net/ipv4/netfilter/arp_tables.c#L489">489</a> }
<a name="L490" href="source/net/ipv4/netfilter/arp_tables.c#L490">490</a> 
<a name="L491" href="source/net/ipv4/netfilter/arp_tables.c#L491">491</a> static inline int <a href="ident?i=check_target">check_target</a>(struct <a href="ident?i=arpt_entry">arpt_entry</a> *<a href="ident?i=e">e</a>, const char *<a href="ident?i=name">name</a>)
<a name="L492" href="source/net/ipv4/netfilter/arp_tables.c#L492">492</a> {
<a name="L493" href="source/net/ipv4/netfilter/arp_tables.c#L493">493</a>         struct <a href="ident?i=xt_entry_target">xt_entry_target</a> *<a href="ident?i=t">t</a> = <a href="ident?i=arpt_get_target">arpt_get_target</a>(<a href="ident?i=e">e</a>);
<a name="L494" href="source/net/ipv4/netfilter/arp_tables.c#L494">494</a>         int <a href="ident?i=ret">ret</a>;
<a name="L495" href="source/net/ipv4/netfilter/arp_tables.c#L495">495</a>         struct <a href="ident?i=xt_tgchk_param">xt_tgchk_param</a> <a href="ident?i=par">par</a> = {
<a name="L496" href="source/net/ipv4/netfilter/arp_tables.c#L496">496</a>                 .<a href="ident?i=table">table</a>     = <a href="ident?i=name">name</a>,
<a name="L497" href="source/net/ipv4/netfilter/arp_tables.c#L497">497</a>                 .entryinfo = <a href="ident?i=e">e</a>,
<a name="L498" href="source/net/ipv4/netfilter/arp_tables.c#L498">498</a>                 .<a href="ident?i=target">target</a>    = <a href="ident?i=t">t</a>-&gt;u.kernel.<a href="ident?i=target">target</a>,
<a name="L499" href="source/net/ipv4/netfilter/arp_tables.c#L499">499</a>                 .targinfo  = <a href="ident?i=t">t</a>-&gt;<a href="ident?i=data">data</a>,
<a name="L500" href="source/net/ipv4/netfilter/arp_tables.c#L500">500</a>                 .hook_mask = <a href="ident?i=e">e</a>-&gt;comefrom,
<a name="L501" href="source/net/ipv4/netfilter/arp_tables.c#L501">501</a>                 .<a href="ident?i=family">family</a>    = NFPROTO_ARP,
<a name="L502" href="source/net/ipv4/netfilter/arp_tables.c#L502">502</a>         };
<a name="L503" href="source/net/ipv4/netfilter/arp_tables.c#L503">503</a> 
<a name="L504" href="source/net/ipv4/netfilter/arp_tables.c#L504">504</a>         <a href="ident?i=ret">ret</a> = <a href="ident?i=xt_check_target">xt_check_target</a>(&amp;<a href="ident?i=par">par</a>, <a href="ident?i=t">t</a>-&gt;u.target_size - sizeof(*<a href="ident?i=t">t</a>), 0, <a href="ident?i=false">false</a>);
<a name="L505" href="source/net/ipv4/netfilter/arp_tables.c#L505">505</a>         if (<a href="ident?i=ret">ret</a> &lt; 0) {
<a name="L506" href="source/net/ipv4/netfilter/arp_tables.c#L506">506</a>                 <a href="ident?i=duprintf">duprintf</a>(<i>"arp_tables: check failed for `%s'.\n"</i>,
<a name="L507" href="source/net/ipv4/netfilter/arp_tables.c#L507">507</a>                          <a href="ident?i=t">t</a>-&gt;u.kernel.<a href="ident?i=target">target</a>-&gt;<a href="ident?i=name">name</a>);
<a name="L508" href="source/net/ipv4/netfilter/arp_tables.c#L508">508</a>                 return <a href="ident?i=ret">ret</a>;
<a name="L509" href="source/net/ipv4/netfilter/arp_tables.c#L509">509</a>         }
<a name="L510" href="source/net/ipv4/netfilter/arp_tables.c#L510">510</a>         return 0;
<a name="L511" href="source/net/ipv4/netfilter/arp_tables.c#L511">511</a> }
<a name="L512" href="source/net/ipv4/netfilter/arp_tables.c#L512">512</a> 
<a name="L513" href="source/net/ipv4/netfilter/arp_tables.c#L513">513</a> static inline int
<a name="L514" href="source/net/ipv4/netfilter/arp_tables.c#L514">514</a> <a href="ident?i=find_check_entry">find_check_entry</a>(struct <a href="ident?i=arpt_entry">arpt_entry</a> *<a href="ident?i=e">e</a>, const char *<a href="ident?i=name">name</a>, unsigned int <a href="ident?i=size">size</a>)
<a name="L515" href="source/net/ipv4/netfilter/arp_tables.c#L515">515</a> {
<a name="L516" href="source/net/ipv4/netfilter/arp_tables.c#L516">516</a>         struct <a href="ident?i=xt_entry_target">xt_entry_target</a> *<a href="ident?i=t">t</a>;
<a name="L517" href="source/net/ipv4/netfilter/arp_tables.c#L517">517</a>         struct <a href="ident?i=xt_target">xt_target</a> *<a href="ident?i=target">target</a>;
<a name="L518" href="source/net/ipv4/netfilter/arp_tables.c#L518">518</a>         int <a href="ident?i=ret">ret</a>;
<a name="L519" href="source/net/ipv4/netfilter/arp_tables.c#L519">519</a> 
<a name="L520" href="source/net/ipv4/netfilter/arp_tables.c#L520">520</a>         <a href="ident?i=ret">ret</a> = <a href="ident?i=check_entry">check_entry</a>(<a href="ident?i=e">e</a>, <a href="ident?i=name">name</a>);
<a name="L521" href="source/net/ipv4/netfilter/arp_tables.c#L521">521</a>         if (<a href="ident?i=ret">ret</a>)
<a name="L522" href="source/net/ipv4/netfilter/arp_tables.c#L522">522</a>                 return <a href="ident?i=ret">ret</a>;
<a name="L523" href="source/net/ipv4/netfilter/arp_tables.c#L523">523</a> 
<a name="L524" href="source/net/ipv4/netfilter/arp_tables.c#L524">524</a>         <a href="ident?i=t">t</a> = <a href="ident?i=arpt_get_target">arpt_get_target</a>(<a href="ident?i=e">e</a>);
<a name="L525" href="source/net/ipv4/netfilter/arp_tables.c#L525">525</a>         <a href="ident?i=target">target</a> = <a href="ident?i=xt_request_find_target">xt_request_find_target</a>(NFPROTO_ARP, <a href="ident?i=t">t</a>-&gt;u.<a href="ident?i=user">user</a>.<a href="ident?i=name">name</a>,
<a name="L526" href="source/net/ipv4/netfilter/arp_tables.c#L526">526</a>                                         <a href="ident?i=t">t</a>-&gt;u.<a href="ident?i=user">user</a>.<a href="ident?i=revision">revision</a>);
<a name="L527" href="source/net/ipv4/netfilter/arp_tables.c#L527">527</a>         if (<a href="ident?i=IS_ERR">IS_ERR</a>(<a href="ident?i=target">target</a>)) {
<a name="L528" href="source/net/ipv4/netfilter/arp_tables.c#L528">528</a>                 <a href="ident?i=duprintf">duprintf</a>(<i>"find_check_entry: `%s' not found\n"</i>, <a href="ident?i=t">t</a>-&gt;u.<a href="ident?i=user">user</a>.<a href="ident?i=name">name</a>);
<a name="L529" href="source/net/ipv4/netfilter/arp_tables.c#L529">529</a>                 <a href="ident?i=ret">ret</a> = <a href="ident?i=PTR_ERR">PTR_ERR</a>(<a href="ident?i=target">target</a>);
<a name="L530" href="source/net/ipv4/netfilter/arp_tables.c#L530">530</a>                 goto <a href="ident?i=out">out</a>;
<a name="L531" href="source/net/ipv4/netfilter/arp_tables.c#L531">531</a>         }
<a name="L532" href="source/net/ipv4/netfilter/arp_tables.c#L532">532</a>         <a href="ident?i=t">t</a>-&gt;u.kernel.<a href="ident?i=target">target</a> = <a href="ident?i=target">target</a>;
<a name="L533" href="source/net/ipv4/netfilter/arp_tables.c#L533">533</a> 
<a name="L534" href="source/net/ipv4/netfilter/arp_tables.c#L534">534</a>         <a href="ident?i=ret">ret</a> = <a href="ident?i=check_target">check_target</a>(<a href="ident?i=e">e</a>, <a href="ident?i=name">name</a>);
<a name="L535" href="source/net/ipv4/netfilter/arp_tables.c#L535">535</a>         if (<a href="ident?i=ret">ret</a>)
<a name="L536" href="source/net/ipv4/netfilter/arp_tables.c#L536">536</a>                 goto <a href="ident?i=err">err</a>;
<a name="L537" href="source/net/ipv4/netfilter/arp_tables.c#L537">537</a>         return 0;
<a name="L538" href="source/net/ipv4/netfilter/arp_tables.c#L538">538</a> <a href="ident?i=err">err</a>:
<a name="L539" href="source/net/ipv4/netfilter/arp_tables.c#L539">539</a>         <a href="ident?i=module_put">module_put</a>(<a href="ident?i=t">t</a>-&gt;u.kernel.<a href="ident?i=target">target</a>-&gt;<a href="ident?i=me">me</a>);
<a name="L540" href="source/net/ipv4/netfilter/arp_tables.c#L540">540</a> <a href="ident?i=out">out</a>:
<a name="L541" href="source/net/ipv4/netfilter/arp_tables.c#L541">541</a>         return <a href="ident?i=ret">ret</a>;
<a name="L542" href="source/net/ipv4/netfilter/arp_tables.c#L542">542</a> }
<a name="L543" href="source/net/ipv4/netfilter/arp_tables.c#L543">543</a> 
<a name="L544" href="source/net/ipv4/netfilter/arp_tables.c#L544">544</a> static <a href="ident?i=bool">bool</a> <a href="ident?i=check_underflow">check_underflow</a>(const struct <a href="ident?i=arpt_entry">arpt_entry</a> *<a href="ident?i=e">e</a>)
<a name="L545" href="source/net/ipv4/netfilter/arp_tables.c#L545">545</a> {
<a name="L546" href="source/net/ipv4/netfilter/arp_tables.c#L546">546</a>         const struct <a href="ident?i=xt_entry_target">xt_entry_target</a> *<a href="ident?i=t">t</a>;
<a name="L547" href="source/net/ipv4/netfilter/arp_tables.c#L547">547</a>         unsigned int verdict;
<a name="L548" href="source/net/ipv4/netfilter/arp_tables.c#L548">548</a> 
<a name="L549" href="source/net/ipv4/netfilter/arp_tables.c#L549">549</a>         if (!<a href="ident?i=unconditional">unconditional</a>(&amp;<a href="ident?i=e">e</a>-&gt;arp))
<a name="L550" href="source/net/ipv4/netfilter/arp_tables.c#L550">550</a>                 return <a href="ident?i=false">false</a>;
<a name="L551" href="source/net/ipv4/netfilter/arp_tables.c#L551">551</a>         <a href="ident?i=t">t</a> = <a href="ident?i=arpt_get_target_c">arpt_get_target_c</a>(<a href="ident?i=e">e</a>);
<a name="L552" href="source/net/ipv4/netfilter/arp_tables.c#L552">552</a>         if (<a href="ident?i=strcmp">strcmp</a>(<a href="ident?i=t">t</a>-&gt;u.<a href="ident?i=user">user</a>.<a href="ident?i=name">name</a>, <a href="ident?i=XT_STANDARD_TARGET">XT_STANDARD_TARGET</a>) != 0)
<a name="L553" href="source/net/ipv4/netfilter/arp_tables.c#L553">553</a>                 return <a href="ident?i=false">false</a>;
<a name="L554" href="source/net/ipv4/netfilter/arp_tables.c#L554">554</a>         verdict = ((struct <a href="ident?i=xt_standard_target">xt_standard_target</a> *)<a href="ident?i=t">t</a>)-&gt;verdict;
<a name="L555" href="source/net/ipv4/netfilter/arp_tables.c#L555">555</a>         verdict = -verdict - 1;
<a name="L556" href="source/net/ipv4/netfilter/arp_tables.c#L556">556</a>         return verdict == <a href="ident?i=NF_DROP">NF_DROP</a> || verdict == <a href="ident?i=NF_ACCEPT">NF_ACCEPT</a>;
<a name="L557" href="source/net/ipv4/netfilter/arp_tables.c#L557">557</a> }
<a name="L558" href="source/net/ipv4/netfilter/arp_tables.c#L558">558</a> 
<a name="L559" href="source/net/ipv4/netfilter/arp_tables.c#L559">559</a> static inline int <a href="ident?i=check_entry_size_and_hooks">check_entry_size_and_hooks</a>(struct <a href="ident?i=arpt_entry">arpt_entry</a> *<a href="ident?i=e">e</a>,
<a name="L560" href="source/net/ipv4/netfilter/arp_tables.c#L560">560</a>                                              struct <a href="ident?i=xt_table_info">xt_table_info</a> *newinfo,
<a name="L561" href="source/net/ipv4/netfilter/arp_tables.c#L561">561</a>                                              const unsigned char *<a href="ident?i=base">base</a>,
<a name="L562" href="source/net/ipv4/netfilter/arp_tables.c#L562">562</a>                                              const unsigned char *<a href="ident?i=limit">limit</a>,
<a name="L563" href="source/net/ipv4/netfilter/arp_tables.c#L563">563</a>                                              const unsigned int *hook_entries,
<a name="L564" href="source/net/ipv4/netfilter/arp_tables.c#L564">564</a>                                              const unsigned int *underflows,
<a name="L565" href="source/net/ipv4/netfilter/arp_tables.c#L565">565</a>                                              unsigned int valid_hooks)
<a name="L566" href="source/net/ipv4/netfilter/arp_tables.c#L566">566</a> {
<a name="L567" href="source/net/ipv4/netfilter/arp_tables.c#L567">567</a>         unsigned int <a href="ident?i=h">h</a>;
<a name="L568" href="source/net/ipv4/netfilter/arp_tables.c#L568">568</a> 
<a name="L569" href="source/net/ipv4/netfilter/arp_tables.c#L569">569</a>         if ((unsigned long)<a href="ident?i=e">e</a> % __alignof__(struct <a href="ident?i=arpt_entry">arpt_entry</a>) != 0 ||
<a name="L570" href="source/net/ipv4/netfilter/arp_tables.c#L570">570</a>             (unsigned char *)<a href="ident?i=e">e</a> + sizeof(struct <a href="ident?i=arpt_entry">arpt_entry</a>) &gt;= <a href="ident?i=limit">limit</a>) {
<a name="L571" href="source/net/ipv4/netfilter/arp_tables.c#L571">571</a>                 <a href="ident?i=duprintf">duprintf</a>(<i>"Bad offset %p\n"</i>, <a href="ident?i=e">e</a>);
<a name="L572" href="source/net/ipv4/netfilter/arp_tables.c#L572">572</a>                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L573" href="source/net/ipv4/netfilter/arp_tables.c#L573">573</a>         }
<a name="L574" href="source/net/ipv4/netfilter/arp_tables.c#L574">574</a> 
<a name="L575" href="source/net/ipv4/netfilter/arp_tables.c#L575">575</a>         if (<a href="ident?i=e">e</a>-&gt;next_offset
<a name="L576" href="source/net/ipv4/netfilter/arp_tables.c#L576">576</a>             &lt; sizeof(struct <a href="ident?i=arpt_entry">arpt_entry</a>) + sizeof(struct <a href="ident?i=xt_entry_target">xt_entry_target</a>)) {
<a name="L577" href="source/net/ipv4/netfilter/arp_tables.c#L577">577</a>                 <a href="ident?i=duprintf">duprintf</a>(<i>"checking: element %p size %u\n"</i>,
<a name="L578" href="source/net/ipv4/netfilter/arp_tables.c#L578">578</a>                          <a href="ident?i=e">e</a>, <a href="ident?i=e">e</a>-&gt;next_offset);
<a name="L579" href="source/net/ipv4/netfilter/arp_tables.c#L579">579</a>                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L580" href="source/net/ipv4/netfilter/arp_tables.c#L580">580</a>         }
<a name="L581" href="source/net/ipv4/netfilter/arp_tables.c#L581">581</a> 
<a name="L582" href="source/net/ipv4/netfilter/arp_tables.c#L582">582</a>         <b><i>/* Check hooks &amp; underflows */</i></b>
<a name="L583" href="source/net/ipv4/netfilter/arp_tables.c#L583">583</a>         for (<a href="ident?i=h">h</a> = 0; <a href="ident?i=h">h</a> &lt; <a href="ident?i=NF_ARP_NUMHOOKS">NF_ARP_NUMHOOKS</a>; <a href="ident?i=h">h</a>++) {
<a name="L584" href="source/net/ipv4/netfilter/arp_tables.c#L584">584</a>                 if (!(valid_hooks &amp; (1 &lt;&lt; <a href="ident?i=h">h</a>)))
<a name="L585" href="source/net/ipv4/netfilter/arp_tables.c#L585">585</a>                         continue;
<a name="L586" href="source/net/ipv4/netfilter/arp_tables.c#L586">586</a>                 if ((unsigned char *)<a href="ident?i=e">e</a> - <a href="ident?i=base">base</a> == hook_entries[<a href="ident?i=h">h</a>])
<a name="L587" href="source/net/ipv4/netfilter/arp_tables.c#L587">587</a>                         newinfo-&gt;hook_entry[<a href="ident?i=h">h</a>] = hook_entries[<a href="ident?i=h">h</a>];
<a name="L588" href="source/net/ipv4/netfilter/arp_tables.c#L588">588</a>                 if ((unsigned char *)<a href="ident?i=e">e</a> - <a href="ident?i=base">base</a> == underflows[<a href="ident?i=h">h</a>]) {
<a name="L589" href="source/net/ipv4/netfilter/arp_tables.c#L589">589</a>                         if (!<a href="ident?i=check_underflow">check_underflow</a>(<a href="ident?i=e">e</a>)) {
<a name="L590" href="source/net/ipv4/netfilter/arp_tables.c#L590">590</a>                                 <a href="ident?i=pr_err">pr_err</a>(<i>"Underflows must be unconditional and "</i>
<a name="L591" href="source/net/ipv4/netfilter/arp_tables.c#L591">591</a>                                        <i>"use the STANDARD target with "</i>
<a name="L592" href="source/net/ipv4/netfilter/arp_tables.c#L592">592</a>                                        <i>"ACCEPT/DROP\n"</i>);
<a name="L593" href="source/net/ipv4/netfilter/arp_tables.c#L593">593</a>                                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L594" href="source/net/ipv4/netfilter/arp_tables.c#L594">594</a>                         }
<a name="L595" href="source/net/ipv4/netfilter/arp_tables.c#L595">595</a>                         newinfo-&gt;underflow[<a href="ident?i=h">h</a>] = underflows[<a href="ident?i=h">h</a>];
<a name="L596" href="source/net/ipv4/netfilter/arp_tables.c#L596">596</a>                 }
<a name="L597" href="source/net/ipv4/netfilter/arp_tables.c#L597">597</a>         }
<a name="L598" href="source/net/ipv4/netfilter/arp_tables.c#L598">598</a> 
<a name="L599" href="source/net/ipv4/netfilter/arp_tables.c#L599">599</a>         <b><i>/* Clear counters and comefrom */</i></b>
<a name="L600" href="source/net/ipv4/netfilter/arp_tables.c#L600">600</a>         <a href="ident?i=e">e</a>-&gt;counters = ((struct <a href="ident?i=xt_counters">xt_counters</a>) { 0, 0 });
<a name="L601" href="source/net/ipv4/netfilter/arp_tables.c#L601">601</a>         <a href="ident?i=e">e</a>-&gt;comefrom = 0;
<a name="L602" href="source/net/ipv4/netfilter/arp_tables.c#L602">602</a>         return 0;
<a name="L603" href="source/net/ipv4/netfilter/arp_tables.c#L603">603</a> }
<a name="L604" href="source/net/ipv4/netfilter/arp_tables.c#L604">604</a> 
<a name="L605" href="source/net/ipv4/netfilter/arp_tables.c#L605">605</a> static inline void <a href="ident?i=cleanup_entry">cleanup_entry</a>(struct <a href="ident?i=arpt_entry">arpt_entry</a> *<a href="ident?i=e">e</a>)
<a name="L606" href="source/net/ipv4/netfilter/arp_tables.c#L606">606</a> {
<a name="L607" href="source/net/ipv4/netfilter/arp_tables.c#L607">607</a>         struct <a href="ident?i=xt_tgdtor_param">xt_tgdtor_param</a> <a href="ident?i=par">par</a>;
<a name="L608" href="source/net/ipv4/netfilter/arp_tables.c#L608">608</a>         struct <a href="ident?i=xt_entry_target">xt_entry_target</a> *<a href="ident?i=t">t</a>;
<a name="L609" href="source/net/ipv4/netfilter/arp_tables.c#L609">609</a> 
<a name="L610" href="source/net/ipv4/netfilter/arp_tables.c#L610">610</a>         <a href="ident?i=t">t</a> = <a href="ident?i=arpt_get_target">arpt_get_target</a>(<a href="ident?i=e">e</a>);
<a name="L611" href="source/net/ipv4/netfilter/arp_tables.c#L611">611</a>         <a href="ident?i=par">par</a>.<a href="ident?i=target">target</a>   = <a href="ident?i=t">t</a>-&gt;u.kernel.<a href="ident?i=target">target</a>;
<a name="L612" href="source/net/ipv4/netfilter/arp_tables.c#L612">612</a>         <a href="ident?i=par">par</a>.targinfo = <a href="ident?i=t">t</a>-&gt;<a href="ident?i=data">data</a>;
<a name="L613" href="source/net/ipv4/netfilter/arp_tables.c#L613">613</a>         <a href="ident?i=par">par</a>.<a href="ident?i=family">family</a>   = NFPROTO_ARP;
<a name="L614" href="source/net/ipv4/netfilter/arp_tables.c#L614">614</a>         if (<a href="ident?i=par">par</a>.<a href="ident?i=target">target</a>-&gt;<a href="ident?i=destroy">destroy</a> != <a href="ident?i=NULL">NULL</a>)
<a name="L615" href="source/net/ipv4/netfilter/arp_tables.c#L615">615</a>                 <a href="ident?i=par">par</a>.<a href="ident?i=target">target</a>-&gt;<a href="ident?i=destroy">destroy</a>(&amp;<a href="ident?i=par">par</a>);
<a name="L616" href="source/net/ipv4/netfilter/arp_tables.c#L616">616</a>         <a href="ident?i=module_put">module_put</a>(<a href="ident?i=par">par</a>.<a href="ident?i=target">target</a>-&gt;<a href="ident?i=me">me</a>);
<a name="L617" href="source/net/ipv4/netfilter/arp_tables.c#L617">617</a> }
<a name="L618" href="source/net/ipv4/netfilter/arp_tables.c#L618">618</a> 
<a name="L619" href="source/net/ipv4/netfilter/arp_tables.c#L619">619</a> <b><i>/* Checks and translates the user-supplied table segment (held in</i></b>
<a name="L620" href="source/net/ipv4/netfilter/arp_tables.c#L620">620</a> <b><i> * newinfo).</i></b>
<a name="L621" href="source/net/ipv4/netfilter/arp_tables.c#L621">621</a> <b><i> */</i></b>
<a name="L622" href="source/net/ipv4/netfilter/arp_tables.c#L622">622</a> static int <a href="ident?i=translate_table">translate_table</a>(struct <a href="ident?i=xt_table_info">xt_table_info</a> *newinfo, void *entry0,
<a name="L623" href="source/net/ipv4/netfilter/arp_tables.c#L623">623</a>                            const struct <a href="ident?i=arpt_replace">arpt_replace</a> *repl)
<a name="L624" href="source/net/ipv4/netfilter/arp_tables.c#L624">624</a> {
<a name="L625" href="source/net/ipv4/netfilter/arp_tables.c#L625">625</a>         struct <a href="ident?i=arpt_entry">arpt_entry</a> *iter;
<a name="L626" href="source/net/ipv4/netfilter/arp_tables.c#L626">626</a>         unsigned int <a href="ident?i=i">i</a>;
<a name="L627" href="source/net/ipv4/netfilter/arp_tables.c#L627">627</a>         int <a href="ident?i=ret">ret</a> = 0;
<a name="L628" href="source/net/ipv4/netfilter/arp_tables.c#L628">628</a> 
<a name="L629" href="source/net/ipv4/netfilter/arp_tables.c#L629">629</a>         newinfo-&gt;<a href="ident?i=size">size</a> = repl-&gt;<a href="ident?i=size">size</a>;
<a name="L630" href="source/net/ipv4/netfilter/arp_tables.c#L630">630</a>         newinfo-&gt;<a href="ident?i=number">number</a> = repl-&gt;<a href="ident?i=num_entries">num_entries</a>;
<a name="L631" href="source/net/ipv4/netfilter/arp_tables.c#L631">631</a> 
<a name="L632" href="source/net/ipv4/netfilter/arp_tables.c#L632">632</a>         <b><i>/* Init all hooks to impossible value. */</i></b>
<a name="L633" href="source/net/ipv4/netfilter/arp_tables.c#L633">633</a>         for (<a href="ident?i=i">i</a> = 0; <a href="ident?i=i">i</a> &lt; <a href="ident?i=NF_ARP_NUMHOOKS">NF_ARP_NUMHOOKS</a>; <a href="ident?i=i">i</a>++) {
<a name="L634" href="source/net/ipv4/netfilter/arp_tables.c#L634">634</a>                 newinfo-&gt;hook_entry[<a href="ident?i=i">i</a>] = 0xFFFFFFFF;
<a name="L635" href="source/net/ipv4/netfilter/arp_tables.c#L635">635</a>                 newinfo-&gt;underflow[<a href="ident?i=i">i</a>] = 0xFFFFFFFF;
<a name="L636" href="source/net/ipv4/netfilter/arp_tables.c#L636">636</a>         }
<a name="L637" href="source/net/ipv4/netfilter/arp_tables.c#L637">637</a> 
<a name="L638" href="source/net/ipv4/netfilter/arp_tables.c#L638">638</a>         <a href="ident?i=duprintf">duprintf</a>(<i>"translate_table: size %u\n"</i>, newinfo-&gt;<a href="ident?i=size">size</a>);
<a name="L639" href="source/net/ipv4/netfilter/arp_tables.c#L639">639</a>         <a href="ident?i=i">i</a> = 0;
<a name="L640" href="source/net/ipv4/netfilter/arp_tables.c#L640">640</a> 
<a name="L641" href="source/net/ipv4/netfilter/arp_tables.c#L641">641</a>         <b><i>/* Walk through entries, checking offsets. */</i></b>
<a name="L642" href="source/net/ipv4/netfilter/arp_tables.c#L642">642</a>         <a href="ident?i=xt_entry_foreach">xt_entry_foreach</a>(iter, entry0, newinfo-&gt;<a href="ident?i=size">size</a>) {
<a name="L643" href="source/net/ipv4/netfilter/arp_tables.c#L643">643</a>                 <a href="ident?i=ret">ret</a> = <a href="ident?i=check_entry_size_and_hooks">check_entry_size_and_hooks</a>(iter, newinfo, entry0,
<a name="L644" href="source/net/ipv4/netfilter/arp_tables.c#L644">644</a>                                                  entry0 + repl-&gt;<a href="ident?i=size">size</a>,
<a name="L645" href="source/net/ipv4/netfilter/arp_tables.c#L645">645</a>                                                  repl-&gt;hook_entry,
<a name="L646" href="source/net/ipv4/netfilter/arp_tables.c#L646">646</a>                                                  repl-&gt;underflow,
<a name="L647" href="source/net/ipv4/netfilter/arp_tables.c#L647">647</a>                                                  repl-&gt;valid_hooks);
<a name="L648" href="source/net/ipv4/netfilter/arp_tables.c#L648">648</a>                 if (<a href="ident?i=ret">ret</a> != 0)
<a name="L649" href="source/net/ipv4/netfilter/arp_tables.c#L649">649</a>                         break;
<a name="L650" href="source/net/ipv4/netfilter/arp_tables.c#L650">650</a>                 ++<a href="ident?i=i">i</a>;
<a name="L651" href="source/net/ipv4/netfilter/arp_tables.c#L651">651</a>                 if (<a href="ident?i=strcmp">strcmp</a>(<a href="ident?i=arpt_get_target">arpt_get_target</a>(iter)-&gt;u.<a href="ident?i=user">user</a>.<a href="ident?i=name">name</a>,
<a name="L652" href="source/net/ipv4/netfilter/arp_tables.c#L652">652</a>                     <a href="ident?i=XT_ERROR_TARGET">XT_ERROR_TARGET</a>) == 0)
<a name="L653" href="source/net/ipv4/netfilter/arp_tables.c#L653">653</a>                         ++newinfo-&gt;stacksize;
<a name="L654" href="source/net/ipv4/netfilter/arp_tables.c#L654">654</a>         }
<a name="L655" href="source/net/ipv4/netfilter/arp_tables.c#L655">655</a>         <a href="ident?i=duprintf">duprintf</a>(<i>"translate_table: ARPT_ENTRY_ITERATE gives %d\n"</i>, <a href="ident?i=ret">ret</a>);
<a name="L656" href="source/net/ipv4/netfilter/arp_tables.c#L656">656</a>         if (<a href="ident?i=ret">ret</a> != 0)
<a name="L657" href="source/net/ipv4/netfilter/arp_tables.c#L657">657</a>                 return <a href="ident?i=ret">ret</a>;
<a name="L658" href="source/net/ipv4/netfilter/arp_tables.c#L658">658</a> 
<a name="L659" href="source/net/ipv4/netfilter/arp_tables.c#L659">659</a>         if (<a href="ident?i=i">i</a> != repl-&gt;<a href="ident?i=num_entries">num_entries</a>) {
<a name="L660" href="source/net/ipv4/netfilter/arp_tables.c#L660">660</a>                 <a href="ident?i=duprintf">duprintf</a>(<i>"translate_table: %u not %u entries\n"</i>,
<a name="L661" href="source/net/ipv4/netfilter/arp_tables.c#L661">661</a>                          <a href="ident?i=i">i</a>, repl-&gt;<a href="ident?i=num_entries">num_entries</a>);
<a name="L662" href="source/net/ipv4/netfilter/arp_tables.c#L662">662</a>                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L663" href="source/net/ipv4/netfilter/arp_tables.c#L663">663</a>         }
<a name="L664" href="source/net/ipv4/netfilter/arp_tables.c#L664">664</a> 
<a name="L665" href="source/net/ipv4/netfilter/arp_tables.c#L665">665</a>         <b><i>/* Check hooks all assigned */</i></b>
<a name="L666" href="source/net/ipv4/netfilter/arp_tables.c#L666">666</a>         for (<a href="ident?i=i">i</a> = 0; <a href="ident?i=i">i</a> &lt; <a href="ident?i=NF_ARP_NUMHOOKS">NF_ARP_NUMHOOKS</a>; <a href="ident?i=i">i</a>++) {
<a name="L667" href="source/net/ipv4/netfilter/arp_tables.c#L667">667</a>                 <b><i>/* Only hooks which are valid */</i></b>
<a name="L668" href="source/net/ipv4/netfilter/arp_tables.c#L668">668</a>                 if (!(repl-&gt;valid_hooks &amp; (1 &lt;&lt; <a href="ident?i=i">i</a>)))
<a name="L669" href="source/net/ipv4/netfilter/arp_tables.c#L669">669</a>                         continue;
<a name="L670" href="source/net/ipv4/netfilter/arp_tables.c#L670">670</a>                 if (newinfo-&gt;hook_entry[<a href="ident?i=i">i</a>] == 0xFFFFFFFF) {
<a name="L671" href="source/net/ipv4/netfilter/arp_tables.c#L671">671</a>                         <a href="ident?i=duprintf">duprintf</a>(<i>"Invalid hook entry %u %u\n"</i>,
<a name="L672" href="source/net/ipv4/netfilter/arp_tables.c#L672">672</a>                                  <a href="ident?i=i">i</a>, repl-&gt;hook_entry[<a href="ident?i=i">i</a>]);
<a name="L673" href="source/net/ipv4/netfilter/arp_tables.c#L673">673</a>                         return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L674" href="source/net/ipv4/netfilter/arp_tables.c#L674">674</a>                 }
<a name="L675" href="source/net/ipv4/netfilter/arp_tables.c#L675">675</a>                 if (newinfo-&gt;underflow[<a href="ident?i=i">i</a>] == 0xFFFFFFFF) {
<a name="L676" href="source/net/ipv4/netfilter/arp_tables.c#L676">676</a>                         <a href="ident?i=duprintf">duprintf</a>(<i>"Invalid underflow %u %u\n"</i>,
<a name="L677" href="source/net/ipv4/netfilter/arp_tables.c#L677">677</a>                                  <a href="ident?i=i">i</a>, repl-&gt;underflow[<a href="ident?i=i">i</a>]);
<a name="L678" href="source/net/ipv4/netfilter/arp_tables.c#L678">678</a>                         return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L679" href="source/net/ipv4/netfilter/arp_tables.c#L679">679</a>                 }
<a name="L680" href="source/net/ipv4/netfilter/arp_tables.c#L680">680</a>         }
<a name="L681" href="source/net/ipv4/netfilter/arp_tables.c#L681">681</a> 
<a name="L682" href="source/net/ipv4/netfilter/arp_tables.c#L682">682</a>         if (!<a href="ident?i=mark_source_chains">mark_source_chains</a>(newinfo, repl-&gt;valid_hooks, entry0)) {
<a name="L683" href="source/net/ipv4/netfilter/arp_tables.c#L683">683</a>                 <a href="ident?i=duprintf">duprintf</a>(<i>"Looping hook\n"</i>);
<a name="L684" href="source/net/ipv4/netfilter/arp_tables.c#L684">684</a>                 return -<a href="ident?i=ELOOP">ELOOP</a>;
<a name="L685" href="source/net/ipv4/netfilter/arp_tables.c#L685">685</a>         }
<a name="L686" href="source/net/ipv4/netfilter/arp_tables.c#L686">686</a> 
<a name="L687" href="source/net/ipv4/netfilter/arp_tables.c#L687">687</a>         <b><i>/* Finally, each sanity check must pass */</i></b>
<a name="L688" href="source/net/ipv4/netfilter/arp_tables.c#L688">688</a>         <a href="ident?i=i">i</a> = 0;
<a name="L689" href="source/net/ipv4/netfilter/arp_tables.c#L689">689</a>         <a href="ident?i=xt_entry_foreach">xt_entry_foreach</a>(iter, entry0, newinfo-&gt;<a href="ident?i=size">size</a>) {
<a name="L690" href="source/net/ipv4/netfilter/arp_tables.c#L690">690</a>                 <a href="ident?i=ret">ret</a> = <a href="ident?i=find_check_entry">find_check_entry</a>(iter, repl-&gt;<a href="ident?i=name">name</a>, repl-&gt;<a href="ident?i=size">size</a>);
<a name="L691" href="source/net/ipv4/netfilter/arp_tables.c#L691">691</a>                 if (<a href="ident?i=ret">ret</a> != 0)
<a name="L692" href="source/net/ipv4/netfilter/arp_tables.c#L692">692</a>                         break;
<a name="L693" href="source/net/ipv4/netfilter/arp_tables.c#L693">693</a>                 ++<a href="ident?i=i">i</a>;
<a name="L694" href="source/net/ipv4/netfilter/arp_tables.c#L694">694</a>         }
<a name="L695" href="source/net/ipv4/netfilter/arp_tables.c#L695">695</a> 
<a name="L696" href="source/net/ipv4/netfilter/arp_tables.c#L696">696</a>         if (<a href="ident?i=ret">ret</a> != 0) {
<a name="L697" href="source/net/ipv4/netfilter/arp_tables.c#L697">697</a>                 <a href="ident?i=xt_entry_foreach">xt_entry_foreach</a>(iter, entry0, newinfo-&gt;<a href="ident?i=size">size</a>) {
<a name="L698" href="source/net/ipv4/netfilter/arp_tables.c#L698">698</a>                         if (<a href="ident?i=i">i</a>-- == 0)
<a name="L699" href="source/net/ipv4/netfilter/arp_tables.c#L699">699</a>                                 break;
<a name="L700" href="source/net/ipv4/netfilter/arp_tables.c#L700">700</a>                         <a href="ident?i=cleanup_entry">cleanup_entry</a>(iter);
<a name="L701" href="source/net/ipv4/netfilter/arp_tables.c#L701">701</a>                 }
<a name="L702" href="source/net/ipv4/netfilter/arp_tables.c#L702">702</a>                 return <a href="ident?i=ret">ret</a>;
<a name="L703" href="source/net/ipv4/netfilter/arp_tables.c#L703">703</a>         }
<a name="L704" href="source/net/ipv4/netfilter/arp_tables.c#L704">704</a> 
<a name="L705" href="source/net/ipv4/netfilter/arp_tables.c#L705">705</a>         <b><i>/* And one copy for every other CPU */</i></b>
<a name="L706" href="source/net/ipv4/netfilter/arp_tables.c#L706">706</a>         <a href="ident?i=for_each_possible_cpu">for_each_possible_cpu</a>(<a href="ident?i=i">i</a>) {
<a name="L707" href="source/net/ipv4/netfilter/arp_tables.c#L707">707</a>                 if (newinfo-&gt;<a href="ident?i=entries">entries</a>[<a href="ident?i=i">i</a>] &amp;&amp; newinfo-&gt;<a href="ident?i=entries">entries</a>[<a href="ident?i=i">i</a>] != entry0)
<a name="L708" href="source/net/ipv4/netfilter/arp_tables.c#L708">708</a>                         <a href="ident?i=memcpy">memcpy</a>(newinfo-&gt;<a href="ident?i=entries">entries</a>[<a href="ident?i=i">i</a>], entry0, newinfo-&gt;<a href="ident?i=size">size</a>);
<a name="L709" href="source/net/ipv4/netfilter/arp_tables.c#L709">709</a>         }
<a name="L710" href="source/net/ipv4/netfilter/arp_tables.c#L710">710</a> 
<a name="L711" href="source/net/ipv4/netfilter/arp_tables.c#L711">711</a>         return <a href="ident?i=ret">ret</a>;
<a name="L712" href="source/net/ipv4/netfilter/arp_tables.c#L712">712</a> }
<a name="L713" href="source/net/ipv4/netfilter/arp_tables.c#L713">713</a> 
<a name="L714" href="source/net/ipv4/netfilter/arp_tables.c#L714">714</a> static void <a href="ident?i=get_counters">get_counters</a>(const struct <a href="ident?i=xt_table_info">xt_table_info</a> *<a href="ident?i=t">t</a>,
<a name="L715" href="source/net/ipv4/netfilter/arp_tables.c#L715">715</a>                          struct <a href="ident?i=xt_counters">xt_counters</a> counters[])
<a name="L716" href="source/net/ipv4/netfilter/arp_tables.c#L716">716</a> {
<a name="L717" href="source/net/ipv4/netfilter/arp_tables.c#L717">717</a>         struct <a href="ident?i=arpt_entry">arpt_entry</a> *iter;
<a name="L718" href="source/net/ipv4/netfilter/arp_tables.c#L718">718</a>         unsigned int <a href="ident?i=cpu">cpu</a>;
<a name="L719" href="source/net/ipv4/netfilter/arp_tables.c#L719">719</a>         unsigned int <a href="ident?i=i">i</a>;
<a name="L720" href="source/net/ipv4/netfilter/arp_tables.c#L720">720</a> 
<a name="L721" href="source/net/ipv4/netfilter/arp_tables.c#L721">721</a>         <a href="ident?i=for_each_possible_cpu">for_each_possible_cpu</a>(<a href="ident?i=cpu">cpu</a>) {
<a name="L722" href="source/net/ipv4/netfilter/arp_tables.c#L722">722</a>                 <a href="ident?i=seqcount_t">seqcount_t</a> *<a href="ident?i=s">s</a> = &amp;<a href="ident?i=per_cpu">per_cpu</a>(xt_recseq, <a href="ident?i=cpu">cpu</a>);
<a name="L723" href="source/net/ipv4/netfilter/arp_tables.c#L723">723</a> 
<a name="L724" href="source/net/ipv4/netfilter/arp_tables.c#L724">724</a>                 <a href="ident?i=i">i</a> = 0;
<a name="L725" href="source/net/ipv4/netfilter/arp_tables.c#L725">725</a>                 <a href="ident?i=xt_entry_foreach">xt_entry_foreach</a>(iter, <a href="ident?i=t">t</a>-&gt;<a href="ident?i=entries">entries</a>[<a href="ident?i=cpu">cpu</a>], <a href="ident?i=t">t</a>-&gt;<a href="ident?i=size">size</a>) {
<a name="L726" href="source/net/ipv4/netfilter/arp_tables.c#L726">726</a>                         <a href="ident?i=u64">u64</a> bcnt, pcnt;
<a name="L727" href="source/net/ipv4/netfilter/arp_tables.c#L727">727</a>                         unsigned int <a href="ident?i=start">start</a>;
<a name="L728" href="source/net/ipv4/netfilter/arp_tables.c#L728">728</a> 
<a name="L729" href="source/net/ipv4/netfilter/arp_tables.c#L729">729</a>                         do {
<a name="L730" href="source/net/ipv4/netfilter/arp_tables.c#L730">730</a>                                 <a href="ident?i=start">start</a> = <a href="ident?i=read_seqcount_begin">read_seqcount_begin</a>(<a href="ident?i=s">s</a>);
<a name="L731" href="source/net/ipv4/netfilter/arp_tables.c#L731">731</a>                                 bcnt = iter-&gt;counters.bcnt;
<a name="L732" href="source/net/ipv4/netfilter/arp_tables.c#L732">732</a>                                 pcnt = iter-&gt;counters.pcnt;
<a name="L733" href="source/net/ipv4/netfilter/arp_tables.c#L733">733</a>                         } while (<a href="ident?i=read_seqcount_retry">read_seqcount_retry</a>(<a href="ident?i=s">s</a>, <a href="ident?i=start">start</a>));
<a name="L734" href="source/net/ipv4/netfilter/arp_tables.c#L734">734</a> 
<a name="L735" href="source/net/ipv4/netfilter/arp_tables.c#L735">735</a>                         <a href="ident?i=ADD_COUNTER">ADD_COUNTER</a>(counters[<a href="ident?i=i">i</a>], bcnt, pcnt);
<a name="L736" href="source/net/ipv4/netfilter/arp_tables.c#L736">736</a>                         ++<a href="ident?i=i">i</a>;
<a name="L737" href="source/net/ipv4/netfilter/arp_tables.c#L737">737</a>                 }
<a name="L738" href="source/net/ipv4/netfilter/arp_tables.c#L738">738</a>         }
<a name="L739" href="source/net/ipv4/netfilter/arp_tables.c#L739">739</a> }
<a name="L740" href="source/net/ipv4/netfilter/arp_tables.c#L740">740</a> 
<a name="L741" href="source/net/ipv4/netfilter/arp_tables.c#L741">741</a> static struct <a href="ident?i=xt_counters">xt_counters</a> *<a href="ident?i=alloc_counters">alloc_counters</a>(const struct <a href="ident?i=xt_table">xt_table</a> *<a href="ident?i=table">table</a>)
<a name="L742" href="source/net/ipv4/netfilter/arp_tables.c#L742">742</a> {
<a name="L743" href="source/net/ipv4/netfilter/arp_tables.c#L743">743</a>         unsigned int countersize;
<a name="L744" href="source/net/ipv4/netfilter/arp_tables.c#L744">744</a>         struct <a href="ident?i=xt_counters">xt_counters</a> *counters;
<a name="L745" href="source/net/ipv4/netfilter/arp_tables.c#L745">745</a>         const struct <a href="ident?i=xt_table_info">xt_table_info</a> *<a href="ident?i=private">private</a> = <a href="ident?i=table">table</a>-&gt;<a href="ident?i=private">private</a>;
<a name="L746" href="source/net/ipv4/netfilter/arp_tables.c#L746">746</a> 
<a name="L747" href="source/net/ipv4/netfilter/arp_tables.c#L747">747</a>         <b><i>/* We need atomic snapshot of counters: rest doesn't change</i></b>
<a name="L748" href="source/net/ipv4/netfilter/arp_tables.c#L748">748</a> <b><i>         * (other than comefrom, which userspace doesn't care</i></b>
<a name="L749" href="source/net/ipv4/netfilter/arp_tables.c#L749">749</a> <b><i>         * about).</i></b>
<a name="L750" href="source/net/ipv4/netfilter/arp_tables.c#L750">750</a> <b><i>         */</i></b>
<a name="L751" href="source/net/ipv4/netfilter/arp_tables.c#L751">751</a>         countersize = sizeof(struct <a href="ident?i=xt_counters">xt_counters</a>) * <a href="ident?i=private">private</a>-&gt;<a href="ident?i=number">number</a>;
<a name="L752" href="source/net/ipv4/netfilter/arp_tables.c#L752">752</a>         counters = <a href="ident?i=vzalloc">vzalloc</a>(countersize);
<a name="L753" href="source/net/ipv4/netfilter/arp_tables.c#L753">753</a> 
<a name="L754" href="source/net/ipv4/netfilter/arp_tables.c#L754">754</a>         if (counters == <a href="ident?i=NULL">NULL</a>)
<a name="L755" href="source/net/ipv4/netfilter/arp_tables.c#L755">755</a>                 return <a href="ident?i=ERR_PTR">ERR_PTR</a>(-<a href="ident?i=ENOMEM">ENOMEM</a>);
<a name="L756" href="source/net/ipv4/netfilter/arp_tables.c#L756">756</a> 
<a name="L757" href="source/net/ipv4/netfilter/arp_tables.c#L757">757</a>         <a href="ident?i=get_counters">get_counters</a>(<a href="ident?i=private">private</a>, counters);
<a name="L758" href="source/net/ipv4/netfilter/arp_tables.c#L758">758</a> 
<a name="L759" href="source/net/ipv4/netfilter/arp_tables.c#L759">759</a>         return counters;
<a name="L760" href="source/net/ipv4/netfilter/arp_tables.c#L760">760</a> }
<a name="L761" href="source/net/ipv4/netfilter/arp_tables.c#L761">761</a> 
<a name="L762" href="source/net/ipv4/netfilter/arp_tables.c#L762">762</a> static int <a href="ident?i=copy_entries_to_user">copy_entries_to_user</a>(unsigned int <a href="ident?i=total_size">total_size</a>,
<a name="L763" href="source/net/ipv4/netfilter/arp_tables.c#L763">763</a>                                 const struct <a href="ident?i=xt_table">xt_table</a> *<a href="ident?i=table">table</a>,
<a name="L764" href="source/net/ipv4/netfilter/arp_tables.c#L764">764</a>                                 void <a href="ident?i=__user">__user</a> *userptr)
<a name="L765" href="source/net/ipv4/netfilter/arp_tables.c#L765">765</a> {
<a name="L766" href="source/net/ipv4/netfilter/arp_tables.c#L766">766</a>         unsigned int <a href="ident?i=off">off</a>, <a href="ident?i=num">num</a>;
<a name="L767" href="source/net/ipv4/netfilter/arp_tables.c#L767">767</a>         const struct <a href="ident?i=arpt_entry">arpt_entry</a> *<a href="ident?i=e">e</a>;
<a name="L768" href="source/net/ipv4/netfilter/arp_tables.c#L768">768</a>         struct <a href="ident?i=xt_counters">xt_counters</a> *counters;
<a name="L769" href="source/net/ipv4/netfilter/arp_tables.c#L769">769</a>         struct <a href="ident?i=xt_table_info">xt_table_info</a> *<a href="ident?i=private">private</a> = <a href="ident?i=table">table</a>-&gt;<a href="ident?i=private">private</a>;
<a name="L770" href="source/net/ipv4/netfilter/arp_tables.c#L770">770</a>         int <a href="ident?i=ret">ret</a> = 0;
<a name="L771" href="source/net/ipv4/netfilter/arp_tables.c#L771">771</a>         void *loc_cpu_entry;
<a name="L772" href="source/net/ipv4/netfilter/arp_tables.c#L772">772</a> 
<a name="L773" href="source/net/ipv4/netfilter/arp_tables.c#L773">773</a>         counters = <a href="ident?i=alloc_counters">alloc_counters</a>(<a href="ident?i=table">table</a>);
<a name="L774" href="source/net/ipv4/netfilter/arp_tables.c#L774">774</a>         if (<a href="ident?i=IS_ERR">IS_ERR</a>(counters))
<a name="L775" href="source/net/ipv4/netfilter/arp_tables.c#L775">775</a>                 return <a href="ident?i=PTR_ERR">PTR_ERR</a>(counters);
<a name="L776" href="source/net/ipv4/netfilter/arp_tables.c#L776">776</a> 
<a name="L777" href="source/net/ipv4/netfilter/arp_tables.c#L777">777</a>         loc_cpu_entry = <a href="ident?i=private">private</a>-&gt;<a href="ident?i=entries">entries</a>[<a href="ident?i=raw_smp_processor_id">raw_smp_processor_id</a>()];
<a name="L778" href="source/net/ipv4/netfilter/arp_tables.c#L778">778</a>         <b><i>/* ... then copy entire thing ... */</i></b>
<a name="L779" href="source/net/ipv4/netfilter/arp_tables.c#L779">779</a>         if (<a href="ident?i=copy_to_user">copy_to_user</a>(userptr, loc_cpu_entry, <a href="ident?i=total_size">total_size</a>) != 0) {
<a name="L780" href="source/net/ipv4/netfilter/arp_tables.c#L780">780</a>                 <a href="ident?i=ret">ret</a> = -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L781" href="source/net/ipv4/netfilter/arp_tables.c#L781">781</a>                 goto free_counters;
<a name="L782" href="source/net/ipv4/netfilter/arp_tables.c#L782">782</a>         }
<a name="L783" href="source/net/ipv4/netfilter/arp_tables.c#L783">783</a> 
<a name="L784" href="source/net/ipv4/netfilter/arp_tables.c#L784">784</a>         <b><i>/* FIXME: use iterator macros --RR */</i></b>
<a name="L785" href="source/net/ipv4/netfilter/arp_tables.c#L785">785</a>         <b><i>/* ... then go back and fix counters and names */</i></b>
<a name="L786" href="source/net/ipv4/netfilter/arp_tables.c#L786">786</a>         for (<a href="ident?i=off">off</a> = 0, <a href="ident?i=num">num</a> = 0; <a href="ident?i=off">off</a> &lt; <a href="ident?i=total_size">total_size</a>; <a href="ident?i=off">off</a> += <a href="ident?i=e">e</a>-&gt;next_offset, <a href="ident?i=num">num</a>++){
<a name="L787" href="source/net/ipv4/netfilter/arp_tables.c#L787">787</a>                 const struct <a href="ident?i=xt_entry_target">xt_entry_target</a> *<a href="ident?i=t">t</a>;
<a name="L788" href="source/net/ipv4/netfilter/arp_tables.c#L788">788</a> 
<a name="L789" href="source/net/ipv4/netfilter/arp_tables.c#L789">789</a>                 <a href="ident?i=e">e</a> = (struct <a href="ident?i=arpt_entry">arpt_entry</a> *)(loc_cpu_entry + <a href="ident?i=off">off</a>);
<a name="L790" href="source/net/ipv4/netfilter/arp_tables.c#L790">790</a>                 if (<a href="ident?i=copy_to_user">copy_to_user</a>(userptr + <a href="ident?i=off">off</a>
<a name="L791" href="source/net/ipv4/netfilter/arp_tables.c#L791">791</a>                                  + <a href="ident?i=offsetof">offsetof</a>(struct <a href="ident?i=arpt_entry">arpt_entry</a>, counters),
<a name="L792" href="source/net/ipv4/netfilter/arp_tables.c#L792">792</a>                                  &amp;counters[<a href="ident?i=num">num</a>],
<a name="L793" href="source/net/ipv4/netfilter/arp_tables.c#L793">793</a>                                  sizeof(counters[<a href="ident?i=num">num</a>])) != 0) {
<a name="L794" href="source/net/ipv4/netfilter/arp_tables.c#L794">794</a>                         <a href="ident?i=ret">ret</a> = -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L795" href="source/net/ipv4/netfilter/arp_tables.c#L795">795</a>                         goto free_counters;
<a name="L796" href="source/net/ipv4/netfilter/arp_tables.c#L796">796</a>                 }
<a name="L797" href="source/net/ipv4/netfilter/arp_tables.c#L797">797</a> 
<a name="L798" href="source/net/ipv4/netfilter/arp_tables.c#L798">798</a>                 <a href="ident?i=t">t</a> = <a href="ident?i=arpt_get_target_c">arpt_get_target_c</a>(<a href="ident?i=e">e</a>);
<a name="L799" href="source/net/ipv4/netfilter/arp_tables.c#L799">799</a>                 if (<a href="ident?i=copy_to_user">copy_to_user</a>(userptr + <a href="ident?i=off">off</a> + <a href="ident?i=e">e</a>-&gt;target_offset
<a name="L800" href="source/net/ipv4/netfilter/arp_tables.c#L800">800</a>                                  + <a href="ident?i=offsetof">offsetof</a>(struct <a href="ident?i=xt_entry_target">xt_entry_target</a>,
<a name="L801" href="source/net/ipv4/netfilter/arp_tables.c#L801">801</a>                                             u.<a href="ident?i=user">user</a>.<a href="ident?i=name">name</a>),
<a name="L802" href="source/net/ipv4/netfilter/arp_tables.c#L802">802</a>                                  <a href="ident?i=t">t</a>-&gt;u.kernel.<a href="ident?i=target">target</a>-&gt;<a href="ident?i=name">name</a>,
<a name="L803" href="source/net/ipv4/netfilter/arp_tables.c#L803">803</a>                                  <a href="ident?i=strlen">strlen</a>(<a href="ident?i=t">t</a>-&gt;u.kernel.<a href="ident?i=target">target</a>-&gt;<a href="ident?i=name">name</a>)+1) != 0) {
<a name="L804" href="source/net/ipv4/netfilter/arp_tables.c#L804">804</a>                         <a href="ident?i=ret">ret</a> = -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L805" href="source/net/ipv4/netfilter/arp_tables.c#L805">805</a>                         goto free_counters;
<a name="L806" href="source/net/ipv4/netfilter/arp_tables.c#L806">806</a>                 }
<a name="L807" href="source/net/ipv4/netfilter/arp_tables.c#L807">807</a>         }
<a name="L808" href="source/net/ipv4/netfilter/arp_tables.c#L808">808</a> 
<a name="L809" href="source/net/ipv4/netfilter/arp_tables.c#L809">809</a>  free_counters:
<a name="L810" href="source/net/ipv4/netfilter/arp_tables.c#L810">810</a>         <a href="ident?i=vfree">vfree</a>(counters);
<a name="L811" href="source/net/ipv4/netfilter/arp_tables.c#L811">811</a>         return <a href="ident?i=ret">ret</a>;
<a name="L812" href="source/net/ipv4/netfilter/arp_tables.c#L812">812</a> }
<a name="L813" href="source/net/ipv4/netfilter/arp_tables.c#L813">813</a> 
<a name="L814" href="source/net/ipv4/netfilter/arp_tables.c#L814">814</a> #ifdef CONFIG_COMPAT
<a name="L815" href="source/net/ipv4/netfilter/arp_tables.c#L815">815</a> static void <a href="ident?i=compat_standard_from_user">compat_standard_from_user</a>(void *<a href="ident?i=dst">dst</a>, const void *<a href="ident?i=src">src</a>)
<a name="L816" href="source/net/ipv4/netfilter/arp_tables.c#L816">816</a> {
<a name="L817" href="source/net/ipv4/netfilter/arp_tables.c#L817">817</a>         int <a href="ident?i=v">v</a> = *(<a href="ident?i=compat_int_t">compat_int_t</a> *)<a href="ident?i=src">src</a>;
<a name="L818" href="source/net/ipv4/netfilter/arp_tables.c#L818">818</a> 
<a name="L819" href="source/net/ipv4/netfilter/arp_tables.c#L819">819</a>         if (<a href="ident?i=v">v</a> &gt; 0)
<a name="L820" href="source/net/ipv4/netfilter/arp_tables.c#L820">820</a>                 <a href="ident?i=v">v</a> += <a href="ident?i=xt_compat_calc_jump">xt_compat_calc_jump</a>(NFPROTO_ARP, <a href="ident?i=v">v</a>);
<a name="L821" href="source/net/ipv4/netfilter/arp_tables.c#L821">821</a>         <a href="ident?i=memcpy">memcpy</a>(<a href="ident?i=dst">dst</a>, &amp;<a href="ident?i=v">v</a>, sizeof(<a href="ident?i=v">v</a>));
<a name="L822" href="source/net/ipv4/netfilter/arp_tables.c#L822">822</a> }
<a name="L823" href="source/net/ipv4/netfilter/arp_tables.c#L823">823</a> 
<a name="L824" href="source/net/ipv4/netfilter/arp_tables.c#L824">824</a> static int <a href="ident?i=compat_standard_to_user">compat_standard_to_user</a>(void <a href="ident?i=__user">__user</a> *<a href="ident?i=dst">dst</a>, const void *<a href="ident?i=src">src</a>)
<a name="L825" href="source/net/ipv4/netfilter/arp_tables.c#L825">825</a> {
<a name="L826" href="source/net/ipv4/netfilter/arp_tables.c#L826">826</a>         <a href="ident?i=compat_int_t">compat_int_t</a> cv = *(int *)<a href="ident?i=src">src</a>;
<a name="L827" href="source/net/ipv4/netfilter/arp_tables.c#L827">827</a> 
<a name="L828" href="source/net/ipv4/netfilter/arp_tables.c#L828">828</a>         if (cv &gt; 0)
<a name="L829" href="source/net/ipv4/netfilter/arp_tables.c#L829">829</a>                 cv -= <a href="ident?i=xt_compat_calc_jump">xt_compat_calc_jump</a>(NFPROTO_ARP, cv);
<a name="L830" href="source/net/ipv4/netfilter/arp_tables.c#L830">830</a>         return <a href="ident?i=copy_to_user">copy_to_user</a>(<a href="ident?i=dst">dst</a>, &amp;cv, sizeof(cv)) ? -<a href="ident?i=EFAULT">EFAULT</a> : 0;
<a name="L831" href="source/net/ipv4/netfilter/arp_tables.c#L831">831</a> }
<a name="L832" href="source/net/ipv4/netfilter/arp_tables.c#L832">832</a> 
<a name="L833" href="source/net/ipv4/netfilter/arp_tables.c#L833">833</a> static int <a href="ident?i=compat_calc_entry">compat_calc_entry</a>(const struct <a href="ident?i=arpt_entry">arpt_entry</a> *<a href="ident?i=e">e</a>,
<a name="L834" href="source/net/ipv4/netfilter/arp_tables.c#L834">834</a>                              const struct <a href="ident?i=xt_table_info">xt_table_info</a> *<a href="ident?i=info">info</a>,
<a name="L835" href="source/net/ipv4/netfilter/arp_tables.c#L835">835</a>                              const void *<a href="ident?i=base">base</a>, struct <a href="ident?i=xt_table_info">xt_table_info</a> *newinfo)
<a name="L836" href="source/net/ipv4/netfilter/arp_tables.c#L836">836</a> {
<a name="L837" href="source/net/ipv4/netfilter/arp_tables.c#L837">837</a>         const struct <a href="ident?i=xt_entry_target">xt_entry_target</a> *<a href="ident?i=t">t</a>;
<a name="L838" href="source/net/ipv4/netfilter/arp_tables.c#L838">838</a>         unsigned int entry_offset;
<a name="L839" href="source/net/ipv4/netfilter/arp_tables.c#L839">839</a>         int <a href="ident?i=off">off</a>, <a href="ident?i=i">i</a>, <a href="ident?i=ret">ret</a>;
<a name="L840" href="source/net/ipv4/netfilter/arp_tables.c#L840">840</a> 
<a name="L841" href="source/net/ipv4/netfilter/arp_tables.c#L841">841</a>         <a href="ident?i=off">off</a> = sizeof(struct <a href="ident?i=arpt_entry">arpt_entry</a>) - sizeof(struct <a href="ident?i=compat_arpt_entry">compat_arpt_entry</a>);
<a name="L842" href="source/net/ipv4/netfilter/arp_tables.c#L842">842</a>         entry_offset = (void *)<a href="ident?i=e">e</a> - <a href="ident?i=base">base</a>;
<a name="L843" href="source/net/ipv4/netfilter/arp_tables.c#L843">843</a> 
<a name="L844" href="source/net/ipv4/netfilter/arp_tables.c#L844">844</a>         <a href="ident?i=t">t</a> = <a href="ident?i=arpt_get_target_c">arpt_get_target_c</a>(<a href="ident?i=e">e</a>);
<a name="L845" href="source/net/ipv4/netfilter/arp_tables.c#L845">845</a>         <a href="ident?i=off">off</a> += <a href="ident?i=xt_compat_target_offset">xt_compat_target_offset</a>(<a href="ident?i=t">t</a>-&gt;u.kernel.<a href="ident?i=target">target</a>);
<a name="L846" href="source/net/ipv4/netfilter/arp_tables.c#L846">846</a>         newinfo-&gt;<a href="ident?i=size">size</a> -= <a href="ident?i=off">off</a>;
<a name="L847" href="source/net/ipv4/netfilter/arp_tables.c#L847">847</a>         <a href="ident?i=ret">ret</a> = <a href="ident?i=xt_compat_add_offset">xt_compat_add_offset</a>(NFPROTO_ARP, entry_offset, <a href="ident?i=off">off</a>);
<a name="L848" href="source/net/ipv4/netfilter/arp_tables.c#L848">848</a>         if (<a href="ident?i=ret">ret</a>)
<a name="L849" href="source/net/ipv4/netfilter/arp_tables.c#L849">849</a>                 return <a href="ident?i=ret">ret</a>;
<a name="L850" href="source/net/ipv4/netfilter/arp_tables.c#L850">850</a> 
<a name="L851" href="source/net/ipv4/netfilter/arp_tables.c#L851">851</a>         for (<a href="ident?i=i">i</a> = 0; <a href="ident?i=i">i</a> &lt; <a href="ident?i=NF_ARP_NUMHOOKS">NF_ARP_NUMHOOKS</a>; <a href="ident?i=i">i</a>++) {
<a name="L852" href="source/net/ipv4/netfilter/arp_tables.c#L852">852</a>                 if (<a href="ident?i=info">info</a>-&gt;hook_entry[<a href="ident?i=i">i</a>] &amp;&amp;
<a name="L853" href="source/net/ipv4/netfilter/arp_tables.c#L853">853</a>                     (<a href="ident?i=e">e</a> &lt; (struct <a href="ident?i=arpt_entry">arpt_entry</a> *)(<a href="ident?i=base">base</a> + <a href="ident?i=info">info</a>-&gt;hook_entry[<a href="ident?i=i">i</a>])))
<a name="L854" href="source/net/ipv4/netfilter/arp_tables.c#L854">854</a>                         newinfo-&gt;hook_entry[<a href="ident?i=i">i</a>] -= <a href="ident?i=off">off</a>;
<a name="L855" href="source/net/ipv4/netfilter/arp_tables.c#L855">855</a>                 if (<a href="ident?i=info">info</a>-&gt;underflow[<a href="ident?i=i">i</a>] &amp;&amp;
<a name="L856" href="source/net/ipv4/netfilter/arp_tables.c#L856">856</a>                     (<a href="ident?i=e">e</a> &lt; (struct <a href="ident?i=arpt_entry">arpt_entry</a> *)(<a href="ident?i=base">base</a> + <a href="ident?i=info">info</a>-&gt;underflow[<a href="ident?i=i">i</a>])))
<a name="L857" href="source/net/ipv4/netfilter/arp_tables.c#L857">857</a>                         newinfo-&gt;underflow[<a href="ident?i=i">i</a>] -= <a href="ident?i=off">off</a>;
<a name="L858" href="source/net/ipv4/netfilter/arp_tables.c#L858">858</a>         }
<a name="L859" href="source/net/ipv4/netfilter/arp_tables.c#L859">859</a>         return 0;
<a name="L860" href="source/net/ipv4/netfilter/arp_tables.c#L860">860</a> }
<a name="L861" href="source/net/ipv4/netfilter/arp_tables.c#L861">861</a> 
<a name="L862" href="source/net/ipv4/netfilter/arp_tables.c#L862">862</a> static int <a href="ident?i=compat_table_info">compat_table_info</a>(const struct <a href="ident?i=xt_table_info">xt_table_info</a> *<a href="ident?i=info">info</a>,
<a name="L863" href="source/net/ipv4/netfilter/arp_tables.c#L863">863</a>                              struct <a href="ident?i=xt_table_info">xt_table_info</a> *newinfo)
<a name="L864" href="source/net/ipv4/netfilter/arp_tables.c#L864">864</a> {
<a name="L865" href="source/net/ipv4/netfilter/arp_tables.c#L865">865</a>         struct <a href="ident?i=arpt_entry">arpt_entry</a> *iter;
<a name="L866" href="source/net/ipv4/netfilter/arp_tables.c#L866">866</a>         void *loc_cpu_entry;
<a name="L867" href="source/net/ipv4/netfilter/arp_tables.c#L867">867</a>         int <a href="ident?i=ret">ret</a>;
<a name="L868" href="source/net/ipv4/netfilter/arp_tables.c#L868">868</a> 
<a name="L869" href="source/net/ipv4/netfilter/arp_tables.c#L869">869</a>         if (!newinfo || !<a href="ident?i=info">info</a>)
<a name="L870" href="source/net/ipv4/netfilter/arp_tables.c#L870">870</a>                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L871" href="source/net/ipv4/netfilter/arp_tables.c#L871">871</a> 
<a name="L872" href="source/net/ipv4/netfilter/arp_tables.c#L872">872</a>         <b><i>/* we dont care about newinfo-&gt;entries[] */</i></b>
<a name="L873" href="source/net/ipv4/netfilter/arp_tables.c#L873">873</a>         <a href="ident?i=memcpy">memcpy</a>(newinfo, <a href="ident?i=info">info</a>, <a href="ident?i=offsetof">offsetof</a>(struct <a href="ident?i=xt_table_info">xt_table_info</a>, <a href="ident?i=entries">entries</a>));
<a name="L874" href="source/net/ipv4/netfilter/arp_tables.c#L874">874</a>         newinfo-&gt;initial_entries = 0;
<a name="L875" href="source/net/ipv4/netfilter/arp_tables.c#L875">875</a>         loc_cpu_entry = <a href="ident?i=info">info</a>-&gt;<a href="ident?i=entries">entries</a>[<a href="ident?i=raw_smp_processor_id">raw_smp_processor_id</a>()];
<a name="L876" href="source/net/ipv4/netfilter/arp_tables.c#L876">876</a>         <a href="ident?i=xt_compat_init_offsets">xt_compat_init_offsets</a>(NFPROTO_ARP, <a href="ident?i=info">info</a>-&gt;<a href="ident?i=number">number</a>);
<a name="L877" href="source/net/ipv4/netfilter/arp_tables.c#L877">877</a>         <a href="ident?i=xt_entry_foreach">xt_entry_foreach</a>(iter, loc_cpu_entry, <a href="ident?i=info">info</a>-&gt;<a href="ident?i=size">size</a>) {
<a name="L878" href="source/net/ipv4/netfilter/arp_tables.c#L878">878</a>                 <a href="ident?i=ret">ret</a> = <a href="ident?i=compat_calc_entry">compat_calc_entry</a>(iter, <a href="ident?i=info">info</a>, loc_cpu_entry, newinfo);
<a name="L879" href="source/net/ipv4/netfilter/arp_tables.c#L879">879</a>                 if (<a href="ident?i=ret">ret</a> != 0)
<a name="L880" href="source/net/ipv4/netfilter/arp_tables.c#L880">880</a>                         return <a href="ident?i=ret">ret</a>;
<a name="L881" href="source/net/ipv4/netfilter/arp_tables.c#L881">881</a>         }
<a name="L882" href="source/net/ipv4/netfilter/arp_tables.c#L882">882</a>         return 0;
<a name="L883" href="source/net/ipv4/netfilter/arp_tables.c#L883">883</a> }
<a name="L884" href="source/net/ipv4/netfilter/arp_tables.c#L884">884</a> #endif
<a name="L885" href="source/net/ipv4/netfilter/arp_tables.c#L885">885</a> 
<a name="L886" href="source/net/ipv4/netfilter/arp_tables.c#L886">886</a> static int <a href="ident?i=get_info">get_info</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>, void <a href="ident?i=__user">__user</a> *<a href="ident?i=user">user</a>,
<a name="L887" href="source/net/ipv4/netfilter/arp_tables.c#L887">887</a>                     const int *<a href="ident?i=len">len</a>, int <a href="ident?i=compat">compat</a>)
<a name="L888" href="source/net/ipv4/netfilter/arp_tables.c#L888">888</a> {
<a name="L889" href="source/net/ipv4/netfilter/arp_tables.c#L889">889</a>         char <a href="ident?i=name">name</a>[<a href="ident?i=XT_TABLE_MAXNAMELEN">XT_TABLE_MAXNAMELEN</a>];
<a name="L890" href="source/net/ipv4/netfilter/arp_tables.c#L890">890</a>         struct <a href="ident?i=xt_table">xt_table</a> *<a href="ident?i=t">t</a>;
<a name="L891" href="source/net/ipv4/netfilter/arp_tables.c#L891">891</a>         int <a href="ident?i=ret">ret</a>;
<a name="L892" href="source/net/ipv4/netfilter/arp_tables.c#L892">892</a> 
<a name="L893" href="source/net/ipv4/netfilter/arp_tables.c#L893">893</a>         if (*<a href="ident?i=len">len</a> != sizeof(struct <a href="ident?i=arpt_getinfo">arpt_getinfo</a>)) {
<a name="L894" href="source/net/ipv4/netfilter/arp_tables.c#L894">894</a>                 <a href="ident?i=duprintf">duprintf</a>(<i>"length %u != %Zu\n"</i>, *<a href="ident?i=len">len</a>,
<a name="L895" href="source/net/ipv4/netfilter/arp_tables.c#L895">895</a>                          sizeof(struct <a href="ident?i=arpt_getinfo">arpt_getinfo</a>));
<a name="L896" href="source/net/ipv4/netfilter/arp_tables.c#L896">896</a>                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L897" href="source/net/ipv4/netfilter/arp_tables.c#L897">897</a>         }
<a name="L898" href="source/net/ipv4/netfilter/arp_tables.c#L898">898</a> 
<a name="L899" href="source/net/ipv4/netfilter/arp_tables.c#L899">899</a>         if (<a href="ident?i=copy_from_user">copy_from_user</a>(<a href="ident?i=name">name</a>, <a href="ident?i=user">user</a>, sizeof(<a href="ident?i=name">name</a>)) != 0)
<a name="L900" href="source/net/ipv4/netfilter/arp_tables.c#L900">900</a>                 return -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L901" href="source/net/ipv4/netfilter/arp_tables.c#L901">901</a> 
<a name="L902" href="source/net/ipv4/netfilter/arp_tables.c#L902">902</a>         <a href="ident?i=name">name</a>[<a href="ident?i=XT_TABLE_MAXNAMELEN">XT_TABLE_MAXNAMELEN</a>-1] = <i>'\0'</i>;
<a name="L903" href="source/net/ipv4/netfilter/arp_tables.c#L903">903</a> #ifdef CONFIG_COMPAT
<a name="L904" href="source/net/ipv4/netfilter/arp_tables.c#L904">904</a>         if (<a href="ident?i=compat">compat</a>)
<a name="L905" href="source/net/ipv4/netfilter/arp_tables.c#L905">905</a>                 <a href="ident?i=xt_compat_lock">xt_compat_lock</a>(NFPROTO_ARP);
<a name="L906" href="source/net/ipv4/netfilter/arp_tables.c#L906">906</a> #endif
<a name="L907" href="source/net/ipv4/netfilter/arp_tables.c#L907">907</a>         <a href="ident?i=t">t</a> = <a href="ident?i=try_then_request_module">try_then_request_module</a>(<a href="ident?i=xt_find_table_lock">xt_find_table_lock</a>(<a href="ident?i=net">net</a>, NFPROTO_ARP, <a href="ident?i=name">name</a>),
<a name="L908" href="source/net/ipv4/netfilter/arp_tables.c#L908">908</a>                                     <i>"arptable_%s"</i>, <a href="ident?i=name">name</a>);
<a name="L909" href="source/net/ipv4/netfilter/arp_tables.c#L909">909</a>         if (!<a href="ident?i=IS_ERR_OR_NULL">IS_ERR_OR_NULL</a>(<a href="ident?i=t">t</a>)) {
<a name="L910" href="source/net/ipv4/netfilter/arp_tables.c#L910">910</a>                 struct <a href="ident?i=arpt_getinfo">arpt_getinfo</a> <a href="ident?i=info">info</a>;
<a name="L911" href="source/net/ipv4/netfilter/arp_tables.c#L911">911</a>                 const struct <a href="ident?i=xt_table_info">xt_table_info</a> *<a href="ident?i=private">private</a> = <a href="ident?i=t">t</a>-&gt;<a href="ident?i=private">private</a>;
<a name="L912" href="source/net/ipv4/netfilter/arp_tables.c#L912">912</a> #ifdef CONFIG_COMPAT
<a name="L913" href="source/net/ipv4/netfilter/arp_tables.c#L913">913</a>                 struct <a href="ident?i=xt_table_info">xt_table_info</a> <a href="ident?i=tmp">tmp</a>;
<a name="L914" href="source/net/ipv4/netfilter/arp_tables.c#L914">914</a> 
<a name="L915" href="source/net/ipv4/netfilter/arp_tables.c#L915">915</a>                 if (<a href="ident?i=compat">compat</a>) {
<a name="L916" href="source/net/ipv4/netfilter/arp_tables.c#L916">916</a>                         <a href="ident?i=ret">ret</a> = <a href="ident?i=compat_table_info">compat_table_info</a>(<a href="ident?i=private">private</a>, &amp;<a href="ident?i=tmp">tmp</a>);
<a name="L917" href="source/net/ipv4/netfilter/arp_tables.c#L917">917</a>                         <a href="ident?i=xt_compat_flush_offsets">xt_compat_flush_offsets</a>(NFPROTO_ARP);
<a name="L918" href="source/net/ipv4/netfilter/arp_tables.c#L918">918</a>                         <a href="ident?i=private">private</a> = &amp;<a href="ident?i=tmp">tmp</a>;
<a name="L919" href="source/net/ipv4/netfilter/arp_tables.c#L919">919</a>                 }
<a name="L920" href="source/net/ipv4/netfilter/arp_tables.c#L920">920</a> #endif
<a name="L921" href="source/net/ipv4/netfilter/arp_tables.c#L921">921</a>                 <a href="ident?i=memset">memset</a>(&amp;<a href="ident?i=info">info</a>, 0, sizeof(<a href="ident?i=info">info</a>));
<a name="L922" href="source/net/ipv4/netfilter/arp_tables.c#L922">922</a>                 <a href="ident?i=info">info</a>.valid_hooks = <a href="ident?i=t">t</a>-&gt;valid_hooks;
<a name="L923" href="source/net/ipv4/netfilter/arp_tables.c#L923">923</a>                 <a href="ident?i=memcpy">memcpy</a>(<a href="ident?i=info">info</a>.hook_entry, <a href="ident?i=private">private</a>-&gt;hook_entry,
<a name="L924" href="source/net/ipv4/netfilter/arp_tables.c#L924">924</a>                        sizeof(<a href="ident?i=info">info</a>.hook_entry));
<a name="L925" href="source/net/ipv4/netfilter/arp_tables.c#L925">925</a>                 <a href="ident?i=memcpy">memcpy</a>(<a href="ident?i=info">info</a>.underflow, <a href="ident?i=private">private</a>-&gt;underflow,
<a name="L926" href="source/net/ipv4/netfilter/arp_tables.c#L926">926</a>                        sizeof(<a href="ident?i=info">info</a>.underflow));
<a name="L927" href="source/net/ipv4/netfilter/arp_tables.c#L927">927</a>                 <a href="ident?i=info">info</a>.<a href="ident?i=num_entries">num_entries</a> = <a href="ident?i=private">private</a>-&gt;<a href="ident?i=number">number</a>;
<a name="L928" href="source/net/ipv4/netfilter/arp_tables.c#L928">928</a>                 <a href="ident?i=info">info</a>.<a href="ident?i=size">size</a> = <a href="ident?i=private">private</a>-&gt;<a href="ident?i=size">size</a>;
<a name="L929" href="source/net/ipv4/netfilter/arp_tables.c#L929">929</a>                 <a href="ident?i=strcpy">strcpy</a>(<a href="ident?i=info">info</a>.<a href="ident?i=name">name</a>, <a href="ident?i=name">name</a>);
<a name="L930" href="source/net/ipv4/netfilter/arp_tables.c#L930">930</a> 
<a name="L931" href="source/net/ipv4/netfilter/arp_tables.c#L931">931</a>                 if (<a href="ident?i=copy_to_user">copy_to_user</a>(<a href="ident?i=user">user</a>, &amp;<a href="ident?i=info">info</a>, *<a href="ident?i=len">len</a>) != 0)
<a name="L932" href="source/net/ipv4/netfilter/arp_tables.c#L932">932</a>                         <a href="ident?i=ret">ret</a> = -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L933" href="source/net/ipv4/netfilter/arp_tables.c#L933">933</a>                 else
<a name="L934" href="source/net/ipv4/netfilter/arp_tables.c#L934">934</a>                         <a href="ident?i=ret">ret</a> = 0;
<a name="L935" href="source/net/ipv4/netfilter/arp_tables.c#L935">935</a>                 <a href="ident?i=xt_table_unlock">xt_table_unlock</a>(<a href="ident?i=t">t</a>);
<a name="L936" href="source/net/ipv4/netfilter/arp_tables.c#L936">936</a>                 <a href="ident?i=module_put">module_put</a>(<a href="ident?i=t">t</a>-&gt;<a href="ident?i=me">me</a>);
<a name="L937" href="source/net/ipv4/netfilter/arp_tables.c#L937">937</a>         } else
<a name="L938" href="source/net/ipv4/netfilter/arp_tables.c#L938">938</a>                 <a href="ident?i=ret">ret</a> = <a href="ident?i=t">t</a> ? <a href="ident?i=PTR_ERR">PTR_ERR</a>(<a href="ident?i=t">t</a>) : -<a href="ident?i=ENOENT">ENOENT</a>;
<a name="L939" href="source/net/ipv4/netfilter/arp_tables.c#L939">939</a> #ifdef CONFIG_COMPAT
<a name="L940" href="source/net/ipv4/netfilter/arp_tables.c#L940">940</a>         if (<a href="ident?i=compat">compat</a>)
<a name="L941" href="source/net/ipv4/netfilter/arp_tables.c#L941">941</a>                 <a href="ident?i=xt_compat_unlock">xt_compat_unlock</a>(NFPROTO_ARP);
<a name="L942" href="source/net/ipv4/netfilter/arp_tables.c#L942">942</a> #endif
<a name="L943" href="source/net/ipv4/netfilter/arp_tables.c#L943">943</a>         return <a href="ident?i=ret">ret</a>;
<a name="L944" href="source/net/ipv4/netfilter/arp_tables.c#L944">944</a> }
<a name="L945" href="source/net/ipv4/netfilter/arp_tables.c#L945">945</a> 
<a name="L946" href="source/net/ipv4/netfilter/arp_tables.c#L946">946</a> static int <a href="ident?i=get_entries">get_entries</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>, struct <a href="ident?i=arpt_get_entries">arpt_get_entries</a> <a href="ident?i=__user">__user</a> *uptr,
<a name="L947" href="source/net/ipv4/netfilter/arp_tables.c#L947">947</a>                        const int *<a href="ident?i=len">len</a>)
<a name="L948" href="source/net/ipv4/netfilter/arp_tables.c#L948">948</a> {
<a name="L949" href="source/net/ipv4/netfilter/arp_tables.c#L949">949</a>         int <a href="ident?i=ret">ret</a>;
<a name="L950" href="source/net/ipv4/netfilter/arp_tables.c#L950">950</a>         struct <a href="ident?i=arpt_get_entries">arpt_get_entries</a> <a href="ident?i=get">get</a>;
<a name="L951" href="source/net/ipv4/netfilter/arp_tables.c#L951">951</a>         struct <a href="ident?i=xt_table">xt_table</a> *<a href="ident?i=t">t</a>;
<a name="L952" href="source/net/ipv4/netfilter/arp_tables.c#L952">952</a> 
<a name="L953" href="source/net/ipv4/netfilter/arp_tables.c#L953">953</a>         if (*<a href="ident?i=len">len</a> &lt; sizeof(<a href="ident?i=get">get</a>)) {
<a name="L954" href="source/net/ipv4/netfilter/arp_tables.c#L954">954</a>                 <a href="ident?i=duprintf">duprintf</a>(<i>"get_entries: %u &lt; %Zu\n"</i>, *<a href="ident?i=len">len</a>, sizeof(<a href="ident?i=get">get</a>));
<a name="L955" href="source/net/ipv4/netfilter/arp_tables.c#L955">955</a>                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L956" href="source/net/ipv4/netfilter/arp_tables.c#L956">956</a>         }
<a name="L957" href="source/net/ipv4/netfilter/arp_tables.c#L957">957</a>         if (<a href="ident?i=copy_from_user">copy_from_user</a>(&amp;<a href="ident?i=get">get</a>, uptr, sizeof(<a href="ident?i=get">get</a>)) != 0)
<a name="L958" href="source/net/ipv4/netfilter/arp_tables.c#L958">958</a>                 return -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L959" href="source/net/ipv4/netfilter/arp_tables.c#L959">959</a>         if (*<a href="ident?i=len">len</a> != sizeof(struct <a href="ident?i=arpt_get_entries">arpt_get_entries</a>) + <a href="ident?i=get">get</a>.<a href="ident?i=size">size</a>) {
<a name="L960" href="source/net/ipv4/netfilter/arp_tables.c#L960">960</a>                 <a href="ident?i=duprintf">duprintf</a>(<i>"get_entries: %u != %Zu\n"</i>, *<a href="ident?i=len">len</a>,
<a name="L961" href="source/net/ipv4/netfilter/arp_tables.c#L961">961</a>                          sizeof(struct <a href="ident?i=arpt_get_entries">arpt_get_entries</a>) + <a href="ident?i=get">get</a>.<a href="ident?i=size">size</a>);
<a name="L962" href="source/net/ipv4/netfilter/arp_tables.c#L962">962</a>                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L963" href="source/net/ipv4/netfilter/arp_tables.c#L963">963</a>         }
<a name="L964" href="source/net/ipv4/netfilter/arp_tables.c#L964">964</a> 
<a name="L965" href="source/net/ipv4/netfilter/arp_tables.c#L965">965</a>         <a href="ident?i=t">t</a> = <a href="ident?i=xt_find_table_lock">xt_find_table_lock</a>(<a href="ident?i=net">net</a>, NFPROTO_ARP, <a href="ident?i=get">get</a>.<a href="ident?i=name">name</a>);
<a name="L966" href="source/net/ipv4/netfilter/arp_tables.c#L966">966</a>         if (!<a href="ident?i=IS_ERR_OR_NULL">IS_ERR_OR_NULL</a>(<a href="ident?i=t">t</a>)) {
<a name="L967" href="source/net/ipv4/netfilter/arp_tables.c#L967">967</a>                 const struct <a href="ident?i=xt_table_info">xt_table_info</a> *<a href="ident?i=private">private</a> = <a href="ident?i=t">t</a>-&gt;<a href="ident?i=private">private</a>;
<a name="L968" href="source/net/ipv4/netfilter/arp_tables.c#L968">968</a> 
<a name="L969" href="source/net/ipv4/netfilter/arp_tables.c#L969">969</a>                 <a href="ident?i=duprintf">duprintf</a>(<i>"t-&gt;private-&gt;number = %u\n"</i>,
<a name="L970" href="source/net/ipv4/netfilter/arp_tables.c#L970">970</a>                          <a href="ident?i=private">private</a>-&gt;<a href="ident?i=number">number</a>);
<a name="L971" href="source/net/ipv4/netfilter/arp_tables.c#L971">971</a>                 if (<a href="ident?i=get">get</a>.<a href="ident?i=size">size</a> == <a href="ident?i=private">private</a>-&gt;<a href="ident?i=size">size</a>)
<a name="L972" href="source/net/ipv4/netfilter/arp_tables.c#L972">972</a>                         <a href="ident?i=ret">ret</a> = <a href="ident?i=copy_entries_to_user">copy_entries_to_user</a>(<a href="ident?i=private">private</a>-&gt;<a href="ident?i=size">size</a>,
<a name="L973" href="source/net/ipv4/netfilter/arp_tables.c#L973">973</a>                                                    <a href="ident?i=t">t</a>, uptr-&gt;entrytable);
<a name="L974" href="source/net/ipv4/netfilter/arp_tables.c#L974">974</a>                 else {
<a name="L975" href="source/net/ipv4/netfilter/arp_tables.c#L975">975</a>                         <a href="ident?i=duprintf">duprintf</a>(<i>"get_entries: I've got %u not %u!\n"</i>,
<a name="L976" href="source/net/ipv4/netfilter/arp_tables.c#L976">976</a>                                  <a href="ident?i=private">private</a>-&gt;<a href="ident?i=size">size</a>, <a href="ident?i=get">get</a>.<a href="ident?i=size">size</a>);
<a name="L977" href="source/net/ipv4/netfilter/arp_tables.c#L977">977</a>                         <a href="ident?i=ret">ret</a> = -<a href="ident?i=EAGAIN">EAGAIN</a>;
<a name="L978" href="source/net/ipv4/netfilter/arp_tables.c#L978">978</a>                 }
<a name="L979" href="source/net/ipv4/netfilter/arp_tables.c#L979">979</a>                 <a href="ident?i=module_put">module_put</a>(<a href="ident?i=t">t</a>-&gt;<a href="ident?i=me">me</a>);
<a name="L980" href="source/net/ipv4/netfilter/arp_tables.c#L980">980</a>                 <a href="ident?i=xt_table_unlock">xt_table_unlock</a>(<a href="ident?i=t">t</a>);
<a name="L981" href="source/net/ipv4/netfilter/arp_tables.c#L981">981</a>         } else
<a name="L982" href="source/net/ipv4/netfilter/arp_tables.c#L982">982</a>                 <a href="ident?i=ret">ret</a> = <a href="ident?i=t">t</a> ? <a href="ident?i=PTR_ERR">PTR_ERR</a>(<a href="ident?i=t">t</a>) : -<a href="ident?i=ENOENT">ENOENT</a>;
<a name="L983" href="source/net/ipv4/netfilter/arp_tables.c#L983">983</a> 
<a name="L984" href="source/net/ipv4/netfilter/arp_tables.c#L984">984</a>         return <a href="ident?i=ret">ret</a>;
<a name="L985" href="source/net/ipv4/netfilter/arp_tables.c#L985">985</a> }
<a name="L986" href="source/net/ipv4/netfilter/arp_tables.c#L986">986</a> 
<a name="L987" href="source/net/ipv4/netfilter/arp_tables.c#L987">987</a> static int <a href="ident?i=__do_replace">__do_replace</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>, const char *<a href="ident?i=name">name</a>,
<a name="L988" href="source/net/ipv4/netfilter/arp_tables.c#L988">988</a>                         unsigned int valid_hooks,
<a name="L989" href="source/net/ipv4/netfilter/arp_tables.c#L989">989</a>                         struct <a href="ident?i=xt_table_info">xt_table_info</a> *newinfo,
<a name="L990" href="source/net/ipv4/netfilter/arp_tables.c#L990">990</a>                         unsigned int <a href="ident?i=num_counters">num_counters</a>,
<a name="L991" href="source/net/ipv4/netfilter/arp_tables.c#L991">991</a>                         void <a href="ident?i=__user">__user</a> *counters_ptr)
<a name="L992" href="source/net/ipv4/netfilter/arp_tables.c#L992">992</a> {
<a name="L993" href="source/net/ipv4/netfilter/arp_tables.c#L993">993</a>         int <a href="ident?i=ret">ret</a>;
<a name="L994" href="source/net/ipv4/netfilter/arp_tables.c#L994">994</a>         struct <a href="ident?i=xt_table">xt_table</a> *<a href="ident?i=t">t</a>;
<a name="L995" href="source/net/ipv4/netfilter/arp_tables.c#L995">995</a>         struct <a href="ident?i=xt_table_info">xt_table_info</a> *oldinfo;
<a name="L996" href="source/net/ipv4/netfilter/arp_tables.c#L996">996</a>         struct <a href="ident?i=xt_counters">xt_counters</a> *counters;
<a name="L997" href="source/net/ipv4/netfilter/arp_tables.c#L997">997</a>         void *loc_cpu_old_entry;
<a name="L998" href="source/net/ipv4/netfilter/arp_tables.c#L998">998</a>         struct <a href="ident?i=arpt_entry">arpt_entry</a> *iter;
<a name="L999" href="source/net/ipv4/netfilter/arp_tables.c#L999">999</a> 
<a name="L1000" href="source/net/ipv4/netfilter/arp_tables.c#L1000">1000</a>         <a href="ident?i=ret">ret</a> = 0;
<a name="L1001" href="source/net/ipv4/netfilter/arp_tables.c#L1001">1001</a>         counters = <a href="ident?i=vzalloc">vzalloc</a>(<a href="ident?i=num_counters">num_counters</a> * sizeof(struct <a href="ident?i=xt_counters">xt_counters</a>));
<a name="L1002" href="source/net/ipv4/netfilter/arp_tables.c#L1002">1002</a>         if (!counters) {
<a name="L1003" href="source/net/ipv4/netfilter/arp_tables.c#L1003">1003</a>                 <a href="ident?i=ret">ret</a> = -<a href="ident?i=ENOMEM">ENOMEM</a>;
<a name="L1004" href="source/net/ipv4/netfilter/arp_tables.c#L1004">1004</a>                 goto <a href="ident?i=out">out</a>;
<a name="L1005" href="source/net/ipv4/netfilter/arp_tables.c#L1005">1005</a>         }
<a name="L1006" href="source/net/ipv4/netfilter/arp_tables.c#L1006">1006</a> 
<a name="L1007" href="source/net/ipv4/netfilter/arp_tables.c#L1007">1007</a>         <a href="ident?i=t">t</a> = <a href="ident?i=try_then_request_module">try_then_request_module</a>(<a href="ident?i=xt_find_table_lock">xt_find_table_lock</a>(<a href="ident?i=net">net</a>, NFPROTO_ARP, <a href="ident?i=name">name</a>),
<a name="L1008" href="source/net/ipv4/netfilter/arp_tables.c#L1008">1008</a>                                     <i>"arptable_%s"</i>, <a href="ident?i=name">name</a>);
<a name="L1009" href="source/net/ipv4/netfilter/arp_tables.c#L1009">1009</a>         if (<a href="ident?i=IS_ERR_OR_NULL">IS_ERR_OR_NULL</a>(<a href="ident?i=t">t</a>)) {
<a name="L1010" href="source/net/ipv4/netfilter/arp_tables.c#L1010">1010</a>                 <a href="ident?i=ret">ret</a> = <a href="ident?i=t">t</a> ? <a href="ident?i=PTR_ERR">PTR_ERR</a>(<a href="ident?i=t">t</a>) : -<a href="ident?i=ENOENT">ENOENT</a>;
<a name="L1011" href="source/net/ipv4/netfilter/arp_tables.c#L1011">1011</a>                 goto free_newinfo_counters_untrans;
<a name="L1012" href="source/net/ipv4/netfilter/arp_tables.c#L1012">1012</a>         }
<a name="L1013" href="source/net/ipv4/netfilter/arp_tables.c#L1013">1013</a> 
<a name="L1014" href="source/net/ipv4/netfilter/arp_tables.c#L1014">1014</a>         <b><i>/* You lied! */</i></b>
<a name="L1015" href="source/net/ipv4/netfilter/arp_tables.c#L1015">1015</a>         if (valid_hooks != <a href="ident?i=t">t</a>-&gt;valid_hooks) {
<a name="L1016" href="source/net/ipv4/netfilter/arp_tables.c#L1016">1016</a>                 <a href="ident?i=duprintf">duprintf</a>(<i>"Valid hook crap: %08X vs %08X\n"</i>,
<a name="L1017" href="source/net/ipv4/netfilter/arp_tables.c#L1017">1017</a>                          valid_hooks, <a href="ident?i=t">t</a>-&gt;valid_hooks);
<a name="L1018" href="source/net/ipv4/netfilter/arp_tables.c#L1018">1018</a>                 <a href="ident?i=ret">ret</a> = -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L1019" href="source/net/ipv4/netfilter/arp_tables.c#L1019">1019</a>                 goto put_module;
<a name="L1020" href="source/net/ipv4/netfilter/arp_tables.c#L1020">1020</a>         }
<a name="L1021" href="source/net/ipv4/netfilter/arp_tables.c#L1021">1021</a> 
<a name="L1022" href="source/net/ipv4/netfilter/arp_tables.c#L1022">1022</a>         oldinfo = <a href="ident?i=xt_replace_table">xt_replace_table</a>(<a href="ident?i=t">t</a>, <a href="ident?i=num_counters">num_counters</a>, newinfo, &amp;<a href="ident?i=ret">ret</a>);
<a name="L1023" href="source/net/ipv4/netfilter/arp_tables.c#L1023">1023</a>         if (!oldinfo)
<a name="L1024" href="source/net/ipv4/netfilter/arp_tables.c#L1024">1024</a>                 goto put_module;
<a name="L1025" href="source/net/ipv4/netfilter/arp_tables.c#L1025">1025</a> 
<a name="L1026" href="source/net/ipv4/netfilter/arp_tables.c#L1026">1026</a>         <b><i>/* Update module usage count based on number of rules */</i></b>
<a name="L1027" href="source/net/ipv4/netfilter/arp_tables.c#L1027">1027</a>         <a href="ident?i=duprintf">duprintf</a>(<i>"do_replace: oldnum=%u, initnum=%u, newnum=%u\n"</i>,
<a name="L1028" href="source/net/ipv4/netfilter/arp_tables.c#L1028">1028</a>                 oldinfo-&gt;<a href="ident?i=number">number</a>, oldinfo-&gt;initial_entries, newinfo-&gt;<a href="ident?i=number">number</a>);
<a name="L1029" href="source/net/ipv4/netfilter/arp_tables.c#L1029">1029</a>         if ((oldinfo-&gt;<a href="ident?i=number">number</a> &gt; oldinfo-&gt;initial_entries) ||
<a name="L1030" href="source/net/ipv4/netfilter/arp_tables.c#L1030">1030</a>             (newinfo-&gt;<a href="ident?i=number">number</a> &lt;= oldinfo-&gt;initial_entries))
<a name="L1031" href="source/net/ipv4/netfilter/arp_tables.c#L1031">1031</a>                 <a href="ident?i=module_put">module_put</a>(<a href="ident?i=t">t</a>-&gt;<a href="ident?i=me">me</a>);
<a name="L1032" href="source/net/ipv4/netfilter/arp_tables.c#L1032">1032</a>         if ((oldinfo-&gt;<a href="ident?i=number">number</a> &gt; oldinfo-&gt;initial_entries) &amp;&amp;
<a name="L1033" href="source/net/ipv4/netfilter/arp_tables.c#L1033">1033</a>             (newinfo-&gt;<a href="ident?i=number">number</a> &lt;= oldinfo-&gt;initial_entries))
<a name="L1034" href="source/net/ipv4/netfilter/arp_tables.c#L1034">1034</a>                 <a href="ident?i=module_put">module_put</a>(<a href="ident?i=t">t</a>-&gt;<a href="ident?i=me">me</a>);
<a name="L1035" href="source/net/ipv4/netfilter/arp_tables.c#L1035">1035</a> 
<a name="L1036" href="source/net/ipv4/netfilter/arp_tables.c#L1036">1036</a>         <b><i>/* Get the old counters, and synchronize with replace */</i></b>
<a name="L1037" href="source/net/ipv4/netfilter/arp_tables.c#L1037">1037</a>         <a href="ident?i=get_counters">get_counters</a>(oldinfo, counters);
<a name="L1038" href="source/net/ipv4/netfilter/arp_tables.c#L1038">1038</a> 
<a name="L1039" href="source/net/ipv4/netfilter/arp_tables.c#L1039">1039</a>         <b><i>/* Decrease module usage counts and free resource */</i></b>
<a name="L1040" href="source/net/ipv4/netfilter/arp_tables.c#L1040">1040</a>         loc_cpu_old_entry = oldinfo-&gt;<a href="ident?i=entries">entries</a>[<a href="ident?i=raw_smp_processor_id">raw_smp_processor_id</a>()];
<a name="L1041" href="source/net/ipv4/netfilter/arp_tables.c#L1041">1041</a>         <a href="ident?i=xt_entry_foreach">xt_entry_foreach</a>(iter, loc_cpu_old_entry, oldinfo-&gt;<a href="ident?i=size">size</a>)
<a name="L1042" href="source/net/ipv4/netfilter/arp_tables.c#L1042">1042</a>                 <a href="ident?i=cleanup_entry">cleanup_entry</a>(iter);
<a name="L1043" href="source/net/ipv4/netfilter/arp_tables.c#L1043">1043</a> 
<a name="L1044" href="source/net/ipv4/netfilter/arp_tables.c#L1044">1044</a>         <a href="ident?i=xt_free_table_info">xt_free_table_info</a>(oldinfo);
<a name="L1045" href="source/net/ipv4/netfilter/arp_tables.c#L1045">1045</a>         if (<a href="ident?i=copy_to_user">copy_to_user</a>(counters_ptr, counters,
<a name="L1046" href="source/net/ipv4/netfilter/arp_tables.c#L1046">1046</a>                          sizeof(struct <a href="ident?i=xt_counters">xt_counters</a>) * <a href="ident?i=num_counters">num_counters</a>) != 0) {
<a name="L1047" href="source/net/ipv4/netfilter/arp_tables.c#L1047">1047</a>                 <b><i>/* Silent error, can't fail, new table is already in place */</i></b>
<a name="L1048" href="source/net/ipv4/netfilter/arp_tables.c#L1048">1048</a>                 <a href="ident?i=net_warn_ratelimited">net_warn_ratelimited</a>(<i>"arptables: counters copy to user failed while replacing table\n"</i>);
<a name="L1049" href="source/net/ipv4/netfilter/arp_tables.c#L1049">1049</a>         }
<a name="L1050" href="source/net/ipv4/netfilter/arp_tables.c#L1050">1050</a>         <a href="ident?i=vfree">vfree</a>(counters);
<a name="L1051" href="source/net/ipv4/netfilter/arp_tables.c#L1051">1051</a>         <a href="ident?i=xt_table_unlock">xt_table_unlock</a>(<a href="ident?i=t">t</a>);
<a name="L1052" href="source/net/ipv4/netfilter/arp_tables.c#L1052">1052</a>         return <a href="ident?i=ret">ret</a>;
<a name="L1053" href="source/net/ipv4/netfilter/arp_tables.c#L1053">1053</a> 
<a name="L1054" href="source/net/ipv4/netfilter/arp_tables.c#L1054">1054</a>  put_module:
<a name="L1055" href="source/net/ipv4/netfilter/arp_tables.c#L1055">1055</a>         <a href="ident?i=module_put">module_put</a>(<a href="ident?i=t">t</a>-&gt;<a href="ident?i=me">me</a>);
<a name="L1056" href="source/net/ipv4/netfilter/arp_tables.c#L1056">1056</a>         <a href="ident?i=xt_table_unlock">xt_table_unlock</a>(<a href="ident?i=t">t</a>);
<a name="L1057" href="source/net/ipv4/netfilter/arp_tables.c#L1057">1057</a>  free_newinfo_counters_untrans:
<a name="L1058" href="source/net/ipv4/netfilter/arp_tables.c#L1058">1058</a>         <a href="ident?i=vfree">vfree</a>(counters);
<a name="L1059" href="source/net/ipv4/netfilter/arp_tables.c#L1059">1059</a>  <a href="ident?i=out">out</a>:
<a name="L1060" href="source/net/ipv4/netfilter/arp_tables.c#L1060">1060</a>         return <a href="ident?i=ret">ret</a>;
<a name="L1061" href="source/net/ipv4/netfilter/arp_tables.c#L1061">1061</a> }
<a name="L1062" href="source/net/ipv4/netfilter/arp_tables.c#L1062">1062</a> 
<a name="L1063" href="source/net/ipv4/netfilter/arp_tables.c#L1063">1063</a> static int <a href="ident?i=do_replace">do_replace</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>, const void <a href="ident?i=__user">__user</a> *<a href="ident?i=user">user</a>,
<a name="L1064" href="source/net/ipv4/netfilter/arp_tables.c#L1064">1064</a>                       unsigned int <a href="ident?i=len">len</a>)
<a name="L1065" href="source/net/ipv4/netfilter/arp_tables.c#L1065">1065</a> {
<a name="L1066" href="source/net/ipv4/netfilter/arp_tables.c#L1066">1066</a>         int <a href="ident?i=ret">ret</a>;
<a name="L1067" href="source/net/ipv4/netfilter/arp_tables.c#L1067">1067</a>         struct <a href="ident?i=arpt_replace">arpt_replace</a> <a href="ident?i=tmp">tmp</a>;
<a name="L1068" href="source/net/ipv4/netfilter/arp_tables.c#L1068">1068</a>         struct <a href="ident?i=xt_table_info">xt_table_info</a> *newinfo;
<a name="L1069" href="source/net/ipv4/netfilter/arp_tables.c#L1069">1069</a>         void *loc_cpu_entry;
<a name="L1070" href="source/net/ipv4/netfilter/arp_tables.c#L1070">1070</a>         struct <a href="ident?i=arpt_entry">arpt_entry</a> *iter;
<a name="L1071" href="source/net/ipv4/netfilter/arp_tables.c#L1071">1071</a> 
<a name="L1072" href="source/net/ipv4/netfilter/arp_tables.c#L1072">1072</a>         if (<a href="ident?i=copy_from_user">copy_from_user</a>(&amp;<a href="ident?i=tmp">tmp</a>, <a href="ident?i=user">user</a>, sizeof(<a href="ident?i=tmp">tmp</a>)) != 0)
<a name="L1073" href="source/net/ipv4/netfilter/arp_tables.c#L1073">1073</a>                 return -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L1074" href="source/net/ipv4/netfilter/arp_tables.c#L1074">1074</a> 
<a name="L1075" href="source/net/ipv4/netfilter/arp_tables.c#L1075">1075</a>         <b><i>/* overflow check */</i></b>
<a name="L1076" href="source/net/ipv4/netfilter/arp_tables.c#L1076">1076</a>         if (<a href="ident?i=tmp">tmp</a>.<a href="ident?i=num_counters">num_counters</a> &gt;= <a href="ident?i=INT_MAX">INT_MAX</a> / sizeof(struct <a href="ident?i=xt_counters">xt_counters</a>))
<a name="L1077" href="source/net/ipv4/netfilter/arp_tables.c#L1077">1077</a>                 return -<a href="ident?i=ENOMEM">ENOMEM</a>;
<a name="L1078" href="source/net/ipv4/netfilter/arp_tables.c#L1078">1078</a>         if (<a href="ident?i=tmp">tmp</a>.<a href="ident?i=num_counters">num_counters</a> == 0)
<a name="L1079" href="source/net/ipv4/netfilter/arp_tables.c#L1079">1079</a>                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L1080" href="source/net/ipv4/netfilter/arp_tables.c#L1080">1080</a> 
<a name="L1081" href="source/net/ipv4/netfilter/arp_tables.c#L1081">1081</a>         <a href="ident?i=tmp">tmp</a>.<a href="ident?i=name">name</a>[sizeof(<a href="ident?i=tmp">tmp</a>.<a href="ident?i=name">name</a>)-1] = 0;
<a name="L1082" href="source/net/ipv4/netfilter/arp_tables.c#L1082">1082</a> 
<a name="L1083" href="source/net/ipv4/netfilter/arp_tables.c#L1083">1083</a>         newinfo = <a href="ident?i=xt_alloc_table_info">xt_alloc_table_info</a>(<a href="ident?i=tmp">tmp</a>.<a href="ident?i=size">size</a>);
<a name="L1084" href="source/net/ipv4/netfilter/arp_tables.c#L1084">1084</a>         if (!newinfo)
<a name="L1085" href="source/net/ipv4/netfilter/arp_tables.c#L1085">1085</a>                 return -<a href="ident?i=ENOMEM">ENOMEM</a>;
<a name="L1086" href="source/net/ipv4/netfilter/arp_tables.c#L1086">1086</a> 
<a name="L1087" href="source/net/ipv4/netfilter/arp_tables.c#L1087">1087</a>         <b><i>/* choose the copy that is on our node/cpu */</i></b>
<a name="L1088" href="source/net/ipv4/netfilter/arp_tables.c#L1088">1088</a>         loc_cpu_entry = newinfo-&gt;<a href="ident?i=entries">entries</a>[<a href="ident?i=raw_smp_processor_id">raw_smp_processor_id</a>()];
<a name="L1089" href="source/net/ipv4/netfilter/arp_tables.c#L1089">1089</a>         if (<a href="ident?i=copy_from_user">copy_from_user</a>(loc_cpu_entry, <a href="ident?i=user">user</a> + sizeof(<a href="ident?i=tmp">tmp</a>),
<a name="L1090" href="source/net/ipv4/netfilter/arp_tables.c#L1090">1090</a>                            <a href="ident?i=tmp">tmp</a>.<a href="ident?i=size">size</a>) != 0) {
<a name="L1091" href="source/net/ipv4/netfilter/arp_tables.c#L1091">1091</a>                 <a href="ident?i=ret">ret</a> = -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L1092" href="source/net/ipv4/netfilter/arp_tables.c#L1092">1092</a>                 goto free_newinfo;
<a name="L1093" href="source/net/ipv4/netfilter/arp_tables.c#L1093">1093</a>         }
<a name="L1094" href="source/net/ipv4/netfilter/arp_tables.c#L1094">1094</a> 
<a name="L1095" href="source/net/ipv4/netfilter/arp_tables.c#L1095">1095</a>         <a href="ident?i=ret">ret</a> = <a href="ident?i=translate_table">translate_table</a>(newinfo, loc_cpu_entry, &amp;<a href="ident?i=tmp">tmp</a>);
<a name="L1096" href="source/net/ipv4/netfilter/arp_tables.c#L1096">1096</a>         if (<a href="ident?i=ret">ret</a> != 0)
<a name="L1097" href="source/net/ipv4/netfilter/arp_tables.c#L1097">1097</a>                 goto free_newinfo;
<a name="L1098" href="source/net/ipv4/netfilter/arp_tables.c#L1098">1098</a> 
<a name="L1099" href="source/net/ipv4/netfilter/arp_tables.c#L1099">1099</a>         <a href="ident?i=duprintf">duprintf</a>(<i>"arp_tables: Translated table\n"</i>);
<a name="L1100" href="source/net/ipv4/netfilter/arp_tables.c#L1100">1100</a> 
<a name="L1101" href="source/net/ipv4/netfilter/arp_tables.c#L1101">1101</a>         <a href="ident?i=ret">ret</a> = <a href="ident?i=__do_replace">__do_replace</a>(<a href="ident?i=net">net</a>, <a href="ident?i=tmp">tmp</a>.<a href="ident?i=name">name</a>, <a href="ident?i=tmp">tmp</a>.valid_hooks, newinfo,
<a name="L1102" href="source/net/ipv4/netfilter/arp_tables.c#L1102">1102</a>                            <a href="ident?i=tmp">tmp</a>.<a href="ident?i=num_counters">num_counters</a>, <a href="ident?i=tmp">tmp</a>.counters);
<a name="L1103" href="source/net/ipv4/netfilter/arp_tables.c#L1103">1103</a>         if (<a href="ident?i=ret">ret</a>)
<a name="L1104" href="source/net/ipv4/netfilter/arp_tables.c#L1104">1104</a>                 goto free_newinfo_untrans;
<a name="L1105" href="source/net/ipv4/netfilter/arp_tables.c#L1105">1105</a>         return 0;
<a name="L1106" href="source/net/ipv4/netfilter/arp_tables.c#L1106">1106</a> 
<a name="L1107" href="source/net/ipv4/netfilter/arp_tables.c#L1107">1107</a>  free_newinfo_untrans:
<a name="L1108" href="source/net/ipv4/netfilter/arp_tables.c#L1108">1108</a>         <a href="ident?i=xt_entry_foreach">xt_entry_foreach</a>(iter, loc_cpu_entry, newinfo-&gt;<a href="ident?i=size">size</a>)
<a name="L1109" href="source/net/ipv4/netfilter/arp_tables.c#L1109">1109</a>                 <a href="ident?i=cleanup_entry">cleanup_entry</a>(iter);
<a name="L1110" href="source/net/ipv4/netfilter/arp_tables.c#L1110">1110</a>  free_newinfo:
<a name="L1111" href="source/net/ipv4/netfilter/arp_tables.c#L1111">1111</a>         <a href="ident?i=xt_free_table_info">xt_free_table_info</a>(newinfo);
<a name="L1112" href="source/net/ipv4/netfilter/arp_tables.c#L1112">1112</a>         return <a href="ident?i=ret">ret</a>;
<a name="L1113" href="source/net/ipv4/netfilter/arp_tables.c#L1113">1113</a> }
<a name="L1114" href="source/net/ipv4/netfilter/arp_tables.c#L1114">1114</a> 
<a name="L1115" href="source/net/ipv4/netfilter/arp_tables.c#L1115">1115</a> static int <a href="ident?i=do_add_counters">do_add_counters</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>, const void <a href="ident?i=__user">__user</a> *<a href="ident?i=user">user</a>,
<a name="L1116" href="source/net/ipv4/netfilter/arp_tables.c#L1116">1116</a>                            unsigned int <a href="ident?i=len">len</a>, int <a href="ident?i=compat">compat</a>)
<a name="L1117" href="source/net/ipv4/netfilter/arp_tables.c#L1117">1117</a> {
<a name="L1118" href="source/net/ipv4/netfilter/arp_tables.c#L1118">1118</a>         unsigned int <a href="ident?i=i">i</a>, curcpu;
<a name="L1119" href="source/net/ipv4/netfilter/arp_tables.c#L1119">1119</a>         struct <a href="ident?i=xt_counters_info">xt_counters_info</a> <a href="ident?i=tmp">tmp</a>;
<a name="L1120" href="source/net/ipv4/netfilter/arp_tables.c#L1120">1120</a>         struct <a href="ident?i=xt_counters">xt_counters</a> *paddc;
<a name="L1121" href="source/net/ipv4/netfilter/arp_tables.c#L1121">1121</a>         unsigned int <a href="ident?i=num_counters">num_counters</a>;
<a name="L1122" href="source/net/ipv4/netfilter/arp_tables.c#L1122">1122</a>         const char *<a href="ident?i=name">name</a>;
<a name="L1123" href="source/net/ipv4/netfilter/arp_tables.c#L1123">1123</a>         int <a href="ident?i=size">size</a>;
<a name="L1124" href="source/net/ipv4/netfilter/arp_tables.c#L1124">1124</a>         void *ptmp;
<a name="L1125" href="source/net/ipv4/netfilter/arp_tables.c#L1125">1125</a>         struct <a href="ident?i=xt_table">xt_table</a> *<a href="ident?i=t">t</a>;
<a name="L1126" href="source/net/ipv4/netfilter/arp_tables.c#L1126">1126</a>         const struct <a href="ident?i=xt_table_info">xt_table_info</a> *<a href="ident?i=private">private</a>;
<a name="L1127" href="source/net/ipv4/netfilter/arp_tables.c#L1127">1127</a>         int <a href="ident?i=ret">ret</a> = 0;
<a name="L1128" href="source/net/ipv4/netfilter/arp_tables.c#L1128">1128</a>         void *loc_cpu_entry;
<a name="L1129" href="source/net/ipv4/netfilter/arp_tables.c#L1129">1129</a>         struct <a href="ident?i=arpt_entry">arpt_entry</a> *iter;
<a name="L1130" href="source/net/ipv4/netfilter/arp_tables.c#L1130">1130</a>         unsigned int addend;
<a name="L1131" href="source/net/ipv4/netfilter/arp_tables.c#L1131">1131</a> #ifdef CONFIG_COMPAT
<a name="L1132" href="source/net/ipv4/netfilter/arp_tables.c#L1132">1132</a>         struct <a href="ident?i=compat_xt_counters_info">compat_xt_counters_info</a> compat_tmp;
<a name="L1133" href="source/net/ipv4/netfilter/arp_tables.c#L1133">1133</a> 
<a name="L1134" href="source/net/ipv4/netfilter/arp_tables.c#L1134">1134</a>         if (<a href="ident?i=compat">compat</a>) {
<a name="L1135" href="source/net/ipv4/netfilter/arp_tables.c#L1135">1135</a>                 ptmp = &amp;compat_tmp;
<a name="L1136" href="source/net/ipv4/netfilter/arp_tables.c#L1136">1136</a>                 <a href="ident?i=size">size</a> = sizeof(struct <a href="ident?i=compat_xt_counters_info">compat_xt_counters_info</a>);
<a name="L1137" href="source/net/ipv4/netfilter/arp_tables.c#L1137">1137</a>         } else
<a name="L1138" href="source/net/ipv4/netfilter/arp_tables.c#L1138">1138</a> #endif
<a name="L1139" href="source/net/ipv4/netfilter/arp_tables.c#L1139">1139</a>         {
<a name="L1140" href="source/net/ipv4/netfilter/arp_tables.c#L1140">1140</a>                 ptmp = &amp;<a href="ident?i=tmp">tmp</a>;
<a name="L1141" href="source/net/ipv4/netfilter/arp_tables.c#L1141">1141</a>                 <a href="ident?i=size">size</a> = sizeof(struct <a href="ident?i=xt_counters_info">xt_counters_info</a>);
<a name="L1142" href="source/net/ipv4/netfilter/arp_tables.c#L1142">1142</a>         }
<a name="L1143" href="source/net/ipv4/netfilter/arp_tables.c#L1143">1143</a> 
<a name="L1144" href="source/net/ipv4/netfilter/arp_tables.c#L1144">1144</a>         if (<a href="ident?i=copy_from_user">copy_from_user</a>(ptmp, <a href="ident?i=user">user</a>, <a href="ident?i=size">size</a>) != 0)
<a name="L1145" href="source/net/ipv4/netfilter/arp_tables.c#L1145">1145</a>                 return -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L1146" href="source/net/ipv4/netfilter/arp_tables.c#L1146">1146</a> 
<a name="L1147" href="source/net/ipv4/netfilter/arp_tables.c#L1147">1147</a> #ifdef CONFIG_COMPAT
<a name="L1148" href="source/net/ipv4/netfilter/arp_tables.c#L1148">1148</a>         if (<a href="ident?i=compat">compat</a>) {
<a name="L1149" href="source/net/ipv4/netfilter/arp_tables.c#L1149">1149</a>                 <a href="ident?i=num_counters">num_counters</a> = compat_tmp.<a href="ident?i=num_counters">num_counters</a>;
<a name="L1150" href="source/net/ipv4/netfilter/arp_tables.c#L1150">1150</a>                 <a href="ident?i=name">name</a> = compat_tmp.<a href="ident?i=name">name</a>;
<a name="L1151" href="source/net/ipv4/netfilter/arp_tables.c#L1151">1151</a>         } else
<a name="L1152" href="source/net/ipv4/netfilter/arp_tables.c#L1152">1152</a> #endif
<a name="L1153" href="source/net/ipv4/netfilter/arp_tables.c#L1153">1153</a>         {
<a name="L1154" href="source/net/ipv4/netfilter/arp_tables.c#L1154">1154</a>                 <a href="ident?i=num_counters">num_counters</a> = <a href="ident?i=tmp">tmp</a>.<a href="ident?i=num_counters">num_counters</a>;
<a name="L1155" href="source/net/ipv4/netfilter/arp_tables.c#L1155">1155</a>                 <a href="ident?i=name">name</a> = <a href="ident?i=tmp">tmp</a>.<a href="ident?i=name">name</a>;
<a name="L1156" href="source/net/ipv4/netfilter/arp_tables.c#L1156">1156</a>         }
<a name="L1157" href="source/net/ipv4/netfilter/arp_tables.c#L1157">1157</a> 
<a name="L1158" href="source/net/ipv4/netfilter/arp_tables.c#L1158">1158</a>         if (<a href="ident?i=len">len</a> != <a href="ident?i=size">size</a> + <a href="ident?i=num_counters">num_counters</a> * sizeof(struct <a href="ident?i=xt_counters">xt_counters</a>))
<a name="L1159" href="source/net/ipv4/netfilter/arp_tables.c#L1159">1159</a>                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L1160" href="source/net/ipv4/netfilter/arp_tables.c#L1160">1160</a> 
<a name="L1161" href="source/net/ipv4/netfilter/arp_tables.c#L1161">1161</a>         paddc = <a href="ident?i=vmalloc">vmalloc</a>(<a href="ident?i=len">len</a> - <a href="ident?i=size">size</a>);
<a name="L1162" href="source/net/ipv4/netfilter/arp_tables.c#L1162">1162</a>         if (!paddc)
<a name="L1163" href="source/net/ipv4/netfilter/arp_tables.c#L1163">1163</a>                 return -<a href="ident?i=ENOMEM">ENOMEM</a>;
<a name="L1164" href="source/net/ipv4/netfilter/arp_tables.c#L1164">1164</a> 
<a name="L1165" href="source/net/ipv4/netfilter/arp_tables.c#L1165">1165</a>         if (<a href="ident?i=copy_from_user">copy_from_user</a>(paddc, <a href="ident?i=user">user</a> + <a href="ident?i=size">size</a>, <a href="ident?i=len">len</a> - <a href="ident?i=size">size</a>) != 0) {
<a name="L1166" href="source/net/ipv4/netfilter/arp_tables.c#L1166">1166</a>                 <a href="ident?i=ret">ret</a> = -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L1167" href="source/net/ipv4/netfilter/arp_tables.c#L1167">1167</a>                 goto <a href="ident?i=free">free</a>;
<a name="L1168" href="source/net/ipv4/netfilter/arp_tables.c#L1168">1168</a>         }
<a name="L1169" href="source/net/ipv4/netfilter/arp_tables.c#L1169">1169</a> 
<a name="L1170" href="source/net/ipv4/netfilter/arp_tables.c#L1170">1170</a>         <a href="ident?i=t">t</a> = <a href="ident?i=xt_find_table_lock">xt_find_table_lock</a>(<a href="ident?i=net">net</a>, NFPROTO_ARP, <a href="ident?i=name">name</a>);
<a name="L1171" href="source/net/ipv4/netfilter/arp_tables.c#L1171">1171</a>         if (<a href="ident?i=IS_ERR_OR_NULL">IS_ERR_OR_NULL</a>(<a href="ident?i=t">t</a>)) {
<a name="L1172" href="source/net/ipv4/netfilter/arp_tables.c#L1172">1172</a>                 <a href="ident?i=ret">ret</a> = <a href="ident?i=t">t</a> ? <a href="ident?i=PTR_ERR">PTR_ERR</a>(<a href="ident?i=t">t</a>) : -<a href="ident?i=ENOENT">ENOENT</a>;
<a name="L1173" href="source/net/ipv4/netfilter/arp_tables.c#L1173">1173</a>                 goto <a href="ident?i=free">free</a>;
<a name="L1174" href="source/net/ipv4/netfilter/arp_tables.c#L1174">1174</a>         }
<a name="L1175" href="source/net/ipv4/netfilter/arp_tables.c#L1175">1175</a> 
<a name="L1176" href="source/net/ipv4/netfilter/arp_tables.c#L1176">1176</a>         <a href="ident?i=local_bh_disable">local_bh_disable</a>();
<a name="L1177" href="source/net/ipv4/netfilter/arp_tables.c#L1177">1177</a>         <a href="ident?i=private">private</a> = <a href="ident?i=t">t</a>-&gt;<a href="ident?i=private">private</a>;
<a name="L1178" href="source/net/ipv4/netfilter/arp_tables.c#L1178">1178</a>         if (<a href="ident?i=private">private</a>-&gt;<a href="ident?i=number">number</a> != <a href="ident?i=num_counters">num_counters</a>) {
<a name="L1179" href="source/net/ipv4/netfilter/arp_tables.c#L1179">1179</a>                 <a href="ident?i=ret">ret</a> = -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L1180" href="source/net/ipv4/netfilter/arp_tables.c#L1180">1180</a>                 goto unlock_up_free;
<a name="L1181" href="source/net/ipv4/netfilter/arp_tables.c#L1181">1181</a>         }
<a name="L1182" href="source/net/ipv4/netfilter/arp_tables.c#L1182">1182</a> 
<a name="L1183" href="source/net/ipv4/netfilter/arp_tables.c#L1183">1183</a>         <a href="ident?i=i">i</a> = 0;
<a name="L1184" href="source/net/ipv4/netfilter/arp_tables.c#L1184">1184</a>         <b><i>/* Choose the copy that is on our node */</i></b>
<a name="L1185" href="source/net/ipv4/netfilter/arp_tables.c#L1185">1185</a>         curcpu = <a href="ident?i=smp_processor_id">smp_processor_id</a>();
<a name="L1186" href="source/net/ipv4/netfilter/arp_tables.c#L1186">1186</a>         loc_cpu_entry = <a href="ident?i=private">private</a>-&gt;<a href="ident?i=entries">entries</a>[curcpu];
<a name="L1187" href="source/net/ipv4/netfilter/arp_tables.c#L1187">1187</a>         addend = <a href="ident?i=xt_write_recseq_begin">xt_write_recseq_begin</a>();
<a name="L1188" href="source/net/ipv4/netfilter/arp_tables.c#L1188">1188</a>         <a href="ident?i=xt_entry_foreach">xt_entry_foreach</a>(iter, loc_cpu_entry, <a href="ident?i=private">private</a>-&gt;<a href="ident?i=size">size</a>) {
<a name="L1189" href="source/net/ipv4/netfilter/arp_tables.c#L1189">1189</a>                 <a href="ident?i=ADD_COUNTER">ADD_COUNTER</a>(iter-&gt;counters, paddc[<a href="ident?i=i">i</a>].bcnt, paddc[<a href="ident?i=i">i</a>].pcnt);
<a name="L1190" href="source/net/ipv4/netfilter/arp_tables.c#L1190">1190</a>                 ++<a href="ident?i=i">i</a>;
<a name="L1191" href="source/net/ipv4/netfilter/arp_tables.c#L1191">1191</a>         }
<a name="L1192" href="source/net/ipv4/netfilter/arp_tables.c#L1192">1192</a>         <a href="ident?i=xt_write_recseq_end">xt_write_recseq_end</a>(addend);
<a name="L1193" href="source/net/ipv4/netfilter/arp_tables.c#L1193">1193</a>  unlock_up_free:
<a name="L1194" href="source/net/ipv4/netfilter/arp_tables.c#L1194">1194</a>         <a href="ident?i=local_bh_enable">local_bh_enable</a>();
<a name="L1195" href="source/net/ipv4/netfilter/arp_tables.c#L1195">1195</a>         <a href="ident?i=xt_table_unlock">xt_table_unlock</a>(<a href="ident?i=t">t</a>);
<a name="L1196" href="source/net/ipv4/netfilter/arp_tables.c#L1196">1196</a>         <a href="ident?i=module_put">module_put</a>(<a href="ident?i=t">t</a>-&gt;<a href="ident?i=me">me</a>);
<a name="L1197" href="source/net/ipv4/netfilter/arp_tables.c#L1197">1197</a>  <a href="ident?i=free">free</a>:
<a name="L1198" href="source/net/ipv4/netfilter/arp_tables.c#L1198">1198</a>         <a href="ident?i=vfree">vfree</a>(paddc);
<a name="L1199" href="source/net/ipv4/netfilter/arp_tables.c#L1199">1199</a> 
<a name="L1200" href="source/net/ipv4/netfilter/arp_tables.c#L1200">1200</a>         return <a href="ident?i=ret">ret</a>;
<a name="L1201" href="source/net/ipv4/netfilter/arp_tables.c#L1201">1201</a> }
<a name="L1202" href="source/net/ipv4/netfilter/arp_tables.c#L1202">1202</a> 
<a name="L1203" href="source/net/ipv4/netfilter/arp_tables.c#L1203">1203</a> #ifdef CONFIG_COMPAT
<a name="L1204" href="source/net/ipv4/netfilter/arp_tables.c#L1204">1204</a> static inline void <a href="ident?i=compat_release_entry">compat_release_entry</a>(struct <a href="ident?i=compat_arpt_entry">compat_arpt_entry</a> *<a href="ident?i=e">e</a>)
<a name="L1205" href="source/net/ipv4/netfilter/arp_tables.c#L1205">1205</a> {
<a name="L1206" href="source/net/ipv4/netfilter/arp_tables.c#L1206">1206</a>         struct <a href="ident?i=xt_entry_target">xt_entry_target</a> *<a href="ident?i=t">t</a>;
<a name="L1207" href="source/net/ipv4/netfilter/arp_tables.c#L1207">1207</a> 
<a name="L1208" href="source/net/ipv4/netfilter/arp_tables.c#L1208">1208</a>         <a href="ident?i=t">t</a> = <a href="ident?i=compat_arpt_get_target">compat_arpt_get_target</a>(<a href="ident?i=e">e</a>);
<a name="L1209" href="source/net/ipv4/netfilter/arp_tables.c#L1209">1209</a>         <a href="ident?i=module_put">module_put</a>(<a href="ident?i=t">t</a>-&gt;u.kernel.<a href="ident?i=target">target</a>-&gt;<a href="ident?i=me">me</a>);
<a name="L1210" href="source/net/ipv4/netfilter/arp_tables.c#L1210">1210</a> }
<a name="L1211" href="source/net/ipv4/netfilter/arp_tables.c#L1211">1211</a> 
<a name="L1212" href="source/net/ipv4/netfilter/arp_tables.c#L1212">1212</a> static inline int
<a name="L1213" href="source/net/ipv4/netfilter/arp_tables.c#L1213">1213</a> <a href="ident?i=check_compat_entry_size_and_hooks">check_compat_entry_size_and_hooks</a>(struct <a href="ident?i=compat_arpt_entry">compat_arpt_entry</a> *<a href="ident?i=e">e</a>,
<a name="L1214" href="source/net/ipv4/netfilter/arp_tables.c#L1214">1214</a>                                   struct <a href="ident?i=xt_table_info">xt_table_info</a> *newinfo,
<a name="L1215" href="source/net/ipv4/netfilter/arp_tables.c#L1215">1215</a>                                   unsigned int *<a href="ident?i=size">size</a>,
<a name="L1216" href="source/net/ipv4/netfilter/arp_tables.c#L1216">1216</a>                                   const unsigned char *<a href="ident?i=base">base</a>,
<a name="L1217" href="source/net/ipv4/netfilter/arp_tables.c#L1217">1217</a>                                   const unsigned char *<a href="ident?i=limit">limit</a>,
<a name="L1218" href="source/net/ipv4/netfilter/arp_tables.c#L1218">1218</a>                                   const unsigned int *hook_entries,
<a name="L1219" href="source/net/ipv4/netfilter/arp_tables.c#L1219">1219</a>                                   const unsigned int *underflows,
<a name="L1220" href="source/net/ipv4/netfilter/arp_tables.c#L1220">1220</a>                                   const char *<a href="ident?i=name">name</a>)
<a name="L1221" href="source/net/ipv4/netfilter/arp_tables.c#L1221">1221</a> {
<a name="L1222" href="source/net/ipv4/netfilter/arp_tables.c#L1222">1222</a>         struct <a href="ident?i=xt_entry_target">xt_entry_target</a> *<a href="ident?i=t">t</a>;
<a name="L1223" href="source/net/ipv4/netfilter/arp_tables.c#L1223">1223</a>         struct <a href="ident?i=xt_target">xt_target</a> *<a href="ident?i=target">target</a>;
<a name="L1224" href="source/net/ipv4/netfilter/arp_tables.c#L1224">1224</a>         unsigned int entry_offset;
<a name="L1225" href="source/net/ipv4/netfilter/arp_tables.c#L1225">1225</a>         int <a href="ident?i=ret">ret</a>, <a href="ident?i=off">off</a>, <a href="ident?i=h">h</a>;
<a name="L1226" href="source/net/ipv4/netfilter/arp_tables.c#L1226">1226</a> 
<a name="L1227" href="source/net/ipv4/netfilter/arp_tables.c#L1227">1227</a>         <a href="ident?i=duprintf">duprintf</a>(<i>"check_compat_entry_size_and_hooks %p\n"</i>, <a href="ident?i=e">e</a>);
<a name="L1228" href="source/net/ipv4/netfilter/arp_tables.c#L1228">1228</a>         if ((unsigned long)<a href="ident?i=e">e</a> % __alignof__(struct <a href="ident?i=compat_arpt_entry">compat_arpt_entry</a>) != 0 ||
<a name="L1229" href="source/net/ipv4/netfilter/arp_tables.c#L1229">1229</a>             (unsigned char *)<a href="ident?i=e">e</a> + sizeof(struct <a href="ident?i=compat_arpt_entry">compat_arpt_entry</a>) &gt;= <a href="ident?i=limit">limit</a>) {
<a name="L1230" href="source/net/ipv4/netfilter/arp_tables.c#L1230">1230</a>                 <a href="ident?i=duprintf">duprintf</a>(<i>"Bad offset %p, limit = %p\n"</i>, <a href="ident?i=e">e</a>, <a href="ident?i=limit">limit</a>);
<a name="L1231" href="source/net/ipv4/netfilter/arp_tables.c#L1231">1231</a>                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L1232" href="source/net/ipv4/netfilter/arp_tables.c#L1232">1232</a>         }
<a name="L1233" href="source/net/ipv4/netfilter/arp_tables.c#L1233">1233</a> 
<a name="L1234" href="source/net/ipv4/netfilter/arp_tables.c#L1234">1234</a>         if (<a href="ident?i=e">e</a>-&gt;next_offset &lt; sizeof(struct <a href="ident?i=compat_arpt_entry">compat_arpt_entry</a>) +
<a name="L1235" href="source/net/ipv4/netfilter/arp_tables.c#L1235">1235</a>                              sizeof(struct <a href="ident?i=compat_xt_entry_target">compat_xt_entry_target</a>)) {
<a name="L1236" href="source/net/ipv4/netfilter/arp_tables.c#L1236">1236</a>                 <a href="ident?i=duprintf">duprintf</a>(<i>"checking: element %p size %u\n"</i>,
<a name="L1237" href="source/net/ipv4/netfilter/arp_tables.c#L1237">1237</a>                          <a href="ident?i=e">e</a>, <a href="ident?i=e">e</a>-&gt;next_offset);
<a name="L1238" href="source/net/ipv4/netfilter/arp_tables.c#L1238">1238</a>                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L1239" href="source/net/ipv4/netfilter/arp_tables.c#L1239">1239</a>         }
<a name="L1240" href="source/net/ipv4/netfilter/arp_tables.c#L1240">1240</a> 
<a name="L1241" href="source/net/ipv4/netfilter/arp_tables.c#L1241">1241</a>         <b><i>/* For purposes of check_entry casting the compat entry is fine */</i></b>
<a name="L1242" href="source/net/ipv4/netfilter/arp_tables.c#L1242">1242</a>         <a href="ident?i=ret">ret</a> = <a href="ident?i=check_entry">check_entry</a>((struct <a href="ident?i=arpt_entry">arpt_entry</a> *)<a href="ident?i=e">e</a>, <a href="ident?i=name">name</a>);
<a name="L1243" href="source/net/ipv4/netfilter/arp_tables.c#L1243">1243</a>         if (<a href="ident?i=ret">ret</a>)
<a name="L1244" href="source/net/ipv4/netfilter/arp_tables.c#L1244">1244</a>                 return <a href="ident?i=ret">ret</a>;
<a name="L1245" href="source/net/ipv4/netfilter/arp_tables.c#L1245">1245</a> 
<a name="L1246" href="source/net/ipv4/netfilter/arp_tables.c#L1246">1246</a>         <a href="ident?i=off">off</a> = sizeof(struct <a href="ident?i=arpt_entry">arpt_entry</a>) - sizeof(struct <a href="ident?i=compat_arpt_entry">compat_arpt_entry</a>);
<a name="L1247" href="source/net/ipv4/netfilter/arp_tables.c#L1247">1247</a>         entry_offset = (void *)<a href="ident?i=e">e</a> - (void *)<a href="ident?i=base">base</a>;
<a name="L1248" href="source/net/ipv4/netfilter/arp_tables.c#L1248">1248</a> 
<a name="L1249" href="source/net/ipv4/netfilter/arp_tables.c#L1249">1249</a>         <a href="ident?i=t">t</a> = <a href="ident?i=compat_arpt_get_target">compat_arpt_get_target</a>(<a href="ident?i=e">e</a>);
<a name="L1250" href="source/net/ipv4/netfilter/arp_tables.c#L1250">1250</a>         <a href="ident?i=target">target</a> = <a href="ident?i=xt_request_find_target">xt_request_find_target</a>(NFPROTO_ARP, <a href="ident?i=t">t</a>-&gt;u.<a href="ident?i=user">user</a>.<a href="ident?i=name">name</a>,
<a name="L1251" href="source/net/ipv4/netfilter/arp_tables.c#L1251">1251</a>                                         <a href="ident?i=t">t</a>-&gt;u.<a href="ident?i=user">user</a>.<a href="ident?i=revision">revision</a>);
<a name="L1252" href="source/net/ipv4/netfilter/arp_tables.c#L1252">1252</a>         if (<a href="ident?i=IS_ERR">IS_ERR</a>(<a href="ident?i=target">target</a>)) {
<a name="L1253" href="source/net/ipv4/netfilter/arp_tables.c#L1253">1253</a>                 <a href="ident?i=duprintf">duprintf</a>(<i>"check_compat_entry_size_and_hooks: `%s' not found\n"</i>,
<a name="L1254" href="source/net/ipv4/netfilter/arp_tables.c#L1254">1254</a>                          <a href="ident?i=t">t</a>-&gt;u.<a href="ident?i=user">user</a>.<a href="ident?i=name">name</a>);
<a name="L1255" href="source/net/ipv4/netfilter/arp_tables.c#L1255">1255</a>                 <a href="ident?i=ret">ret</a> = <a href="ident?i=PTR_ERR">PTR_ERR</a>(<a href="ident?i=target">target</a>);
<a name="L1256" href="source/net/ipv4/netfilter/arp_tables.c#L1256">1256</a>                 goto <a href="ident?i=out">out</a>;
<a name="L1257" href="source/net/ipv4/netfilter/arp_tables.c#L1257">1257</a>         }
<a name="L1258" href="source/net/ipv4/netfilter/arp_tables.c#L1258">1258</a>         <a href="ident?i=t">t</a>-&gt;u.kernel.<a href="ident?i=target">target</a> = <a href="ident?i=target">target</a>;
<a name="L1259" href="source/net/ipv4/netfilter/arp_tables.c#L1259">1259</a> 
<a name="L1260" href="source/net/ipv4/netfilter/arp_tables.c#L1260">1260</a>         <a href="ident?i=off">off</a> += <a href="ident?i=xt_compat_target_offset">xt_compat_target_offset</a>(<a href="ident?i=target">target</a>);
<a name="L1261" href="source/net/ipv4/netfilter/arp_tables.c#L1261">1261</a>         *<a href="ident?i=size">size</a> += <a href="ident?i=off">off</a>;
<a name="L1262" href="source/net/ipv4/netfilter/arp_tables.c#L1262">1262</a>         <a href="ident?i=ret">ret</a> = <a href="ident?i=xt_compat_add_offset">xt_compat_add_offset</a>(NFPROTO_ARP, entry_offset, <a href="ident?i=off">off</a>);
<a name="L1263" href="source/net/ipv4/netfilter/arp_tables.c#L1263">1263</a>         if (<a href="ident?i=ret">ret</a>)
<a name="L1264" href="source/net/ipv4/netfilter/arp_tables.c#L1264">1264</a>                 goto release_target;
<a name="L1265" href="source/net/ipv4/netfilter/arp_tables.c#L1265">1265</a> 
<a name="L1266" href="source/net/ipv4/netfilter/arp_tables.c#L1266">1266</a>         <b><i>/* Check hooks &amp; underflows */</i></b>
<a name="L1267" href="source/net/ipv4/netfilter/arp_tables.c#L1267">1267</a>         for (<a href="ident?i=h">h</a> = 0; <a href="ident?i=h">h</a> &lt; <a href="ident?i=NF_ARP_NUMHOOKS">NF_ARP_NUMHOOKS</a>; <a href="ident?i=h">h</a>++) {
<a name="L1268" href="source/net/ipv4/netfilter/arp_tables.c#L1268">1268</a>                 if ((unsigned char *)<a href="ident?i=e">e</a> - <a href="ident?i=base">base</a> == hook_entries[<a href="ident?i=h">h</a>])
<a name="L1269" href="source/net/ipv4/netfilter/arp_tables.c#L1269">1269</a>                         newinfo-&gt;hook_entry[<a href="ident?i=h">h</a>] = hook_entries[<a href="ident?i=h">h</a>];
<a name="L1270" href="source/net/ipv4/netfilter/arp_tables.c#L1270">1270</a>                 if ((unsigned char *)<a href="ident?i=e">e</a> - <a href="ident?i=base">base</a> == underflows[<a href="ident?i=h">h</a>])
<a name="L1271" href="source/net/ipv4/netfilter/arp_tables.c#L1271">1271</a>                         newinfo-&gt;underflow[<a href="ident?i=h">h</a>] = underflows[<a href="ident?i=h">h</a>];
<a name="L1272" href="source/net/ipv4/netfilter/arp_tables.c#L1272">1272</a>         }
<a name="L1273" href="source/net/ipv4/netfilter/arp_tables.c#L1273">1273</a> 
<a name="L1274" href="source/net/ipv4/netfilter/arp_tables.c#L1274">1274</a>         <b><i>/* Clear counters and comefrom */</i></b>
<a name="L1275" href="source/net/ipv4/netfilter/arp_tables.c#L1275">1275</a>         <a href="ident?i=memset">memset</a>(&amp;<a href="ident?i=e">e</a>-&gt;counters, 0, sizeof(<a href="ident?i=e">e</a>-&gt;counters));
<a name="L1276" href="source/net/ipv4/netfilter/arp_tables.c#L1276">1276</a>         <a href="ident?i=e">e</a>-&gt;comefrom = 0;
<a name="L1277" href="source/net/ipv4/netfilter/arp_tables.c#L1277">1277</a>         return 0;
<a name="L1278" href="source/net/ipv4/netfilter/arp_tables.c#L1278">1278</a> 
<a name="L1279" href="source/net/ipv4/netfilter/arp_tables.c#L1279">1279</a> release_target:
<a name="L1280" href="source/net/ipv4/netfilter/arp_tables.c#L1280">1280</a>         <a href="ident?i=module_put">module_put</a>(<a href="ident?i=t">t</a>-&gt;u.kernel.<a href="ident?i=target">target</a>-&gt;<a href="ident?i=me">me</a>);
<a name="L1281" href="source/net/ipv4/netfilter/arp_tables.c#L1281">1281</a> <a href="ident?i=out">out</a>:
<a name="L1282" href="source/net/ipv4/netfilter/arp_tables.c#L1282">1282</a>         return <a href="ident?i=ret">ret</a>;
<a name="L1283" href="source/net/ipv4/netfilter/arp_tables.c#L1283">1283</a> }
<a name="L1284" href="source/net/ipv4/netfilter/arp_tables.c#L1284">1284</a> 
<a name="L1285" href="source/net/ipv4/netfilter/arp_tables.c#L1285">1285</a> static int
<a name="L1286" href="source/net/ipv4/netfilter/arp_tables.c#L1286">1286</a> <a href="ident?i=compat_copy_entry_from_user">compat_copy_entry_from_user</a>(struct <a href="ident?i=compat_arpt_entry">compat_arpt_entry</a> *<a href="ident?i=e">e</a>, void **<a href="ident?i=dstptr">dstptr</a>,
<a name="L1287" href="source/net/ipv4/netfilter/arp_tables.c#L1287">1287</a>                             unsigned int *<a href="ident?i=size">size</a>, const char *<a href="ident?i=name">name</a>,
<a name="L1288" href="source/net/ipv4/netfilter/arp_tables.c#L1288">1288</a>                             struct <a href="ident?i=xt_table_info">xt_table_info</a> *newinfo, unsigned char *<a href="ident?i=base">base</a>)
<a name="L1289" href="source/net/ipv4/netfilter/arp_tables.c#L1289">1289</a> {
<a name="L1290" href="source/net/ipv4/netfilter/arp_tables.c#L1290">1290</a>         struct <a href="ident?i=xt_entry_target">xt_entry_target</a> *<a href="ident?i=t">t</a>;
<a name="L1291" href="source/net/ipv4/netfilter/arp_tables.c#L1291">1291</a>         struct <a href="ident?i=xt_target">xt_target</a> *<a href="ident?i=target">target</a>;
<a name="L1292" href="source/net/ipv4/netfilter/arp_tables.c#L1292">1292</a>         struct <a href="ident?i=arpt_entry">arpt_entry</a> *<a href="ident?i=de">de</a>;
<a name="L1293" href="source/net/ipv4/netfilter/arp_tables.c#L1293">1293</a>         unsigned int origsize;
<a name="L1294" href="source/net/ipv4/netfilter/arp_tables.c#L1294">1294</a>         int <a href="ident?i=ret">ret</a>, <a href="ident?i=h">h</a>;
<a name="L1295" href="source/net/ipv4/netfilter/arp_tables.c#L1295">1295</a> 
<a name="L1296" href="source/net/ipv4/netfilter/arp_tables.c#L1296">1296</a>         <a href="ident?i=ret">ret</a> = 0;
<a name="L1297" href="source/net/ipv4/netfilter/arp_tables.c#L1297">1297</a>         origsize = *<a href="ident?i=size">size</a>;
<a name="L1298" href="source/net/ipv4/netfilter/arp_tables.c#L1298">1298</a>         <a href="ident?i=de">de</a> = (struct <a href="ident?i=arpt_entry">arpt_entry</a> *)*<a href="ident?i=dstptr">dstptr</a>;
<a name="L1299" href="source/net/ipv4/netfilter/arp_tables.c#L1299">1299</a>         <a href="ident?i=memcpy">memcpy</a>(<a href="ident?i=de">de</a>, <a href="ident?i=e">e</a>, sizeof(struct <a href="ident?i=arpt_entry">arpt_entry</a>));
<a name="L1300" href="source/net/ipv4/netfilter/arp_tables.c#L1300">1300</a>         <a href="ident?i=memcpy">memcpy</a>(&amp;<a href="ident?i=de">de</a>-&gt;counters, &amp;<a href="ident?i=e">e</a>-&gt;counters, sizeof(<a href="ident?i=e">e</a>-&gt;counters));
<a name="L1301" href="source/net/ipv4/netfilter/arp_tables.c#L1301">1301</a> 
<a name="L1302" href="source/net/ipv4/netfilter/arp_tables.c#L1302">1302</a>         *<a href="ident?i=dstptr">dstptr</a> += sizeof(struct <a href="ident?i=arpt_entry">arpt_entry</a>);
<a name="L1303" href="source/net/ipv4/netfilter/arp_tables.c#L1303">1303</a>         *<a href="ident?i=size">size</a> += sizeof(struct <a href="ident?i=arpt_entry">arpt_entry</a>) - sizeof(struct <a href="ident?i=compat_arpt_entry">compat_arpt_entry</a>);
<a name="L1304" href="source/net/ipv4/netfilter/arp_tables.c#L1304">1304</a> 
<a name="L1305" href="source/net/ipv4/netfilter/arp_tables.c#L1305">1305</a>         <a href="ident?i=de">de</a>-&gt;target_offset = <a href="ident?i=e">e</a>-&gt;target_offset - (origsize - *<a href="ident?i=size">size</a>);
<a name="L1306" href="source/net/ipv4/netfilter/arp_tables.c#L1306">1306</a>         <a href="ident?i=t">t</a> = <a href="ident?i=compat_arpt_get_target">compat_arpt_get_target</a>(<a href="ident?i=e">e</a>);
<a name="L1307" href="source/net/ipv4/netfilter/arp_tables.c#L1307">1307</a>         <a href="ident?i=target">target</a> = <a href="ident?i=t">t</a>-&gt;u.kernel.<a href="ident?i=target">target</a>;
<a name="L1308" href="source/net/ipv4/netfilter/arp_tables.c#L1308">1308</a>         <a href="ident?i=xt_compat_target_from_user">xt_compat_target_from_user</a>(<a href="ident?i=t">t</a>, <a href="ident?i=dstptr">dstptr</a>, <a href="ident?i=size">size</a>);
<a name="L1309" href="source/net/ipv4/netfilter/arp_tables.c#L1309">1309</a> 
<a name="L1310" href="source/net/ipv4/netfilter/arp_tables.c#L1310">1310</a>         <a href="ident?i=de">de</a>-&gt;next_offset = <a href="ident?i=e">e</a>-&gt;next_offset - (origsize - *<a href="ident?i=size">size</a>);
<a name="L1311" href="source/net/ipv4/netfilter/arp_tables.c#L1311">1311</a>         for (<a href="ident?i=h">h</a> = 0; <a href="ident?i=h">h</a> &lt; <a href="ident?i=NF_ARP_NUMHOOKS">NF_ARP_NUMHOOKS</a>; <a href="ident?i=h">h</a>++) {
<a name="L1312" href="source/net/ipv4/netfilter/arp_tables.c#L1312">1312</a>                 if ((unsigned char *)<a href="ident?i=de">de</a> - <a href="ident?i=base">base</a> &lt; newinfo-&gt;hook_entry[<a href="ident?i=h">h</a>])
<a name="L1313" href="source/net/ipv4/netfilter/arp_tables.c#L1313">1313</a>                         newinfo-&gt;hook_entry[<a href="ident?i=h">h</a>] -= origsize - *<a href="ident?i=size">size</a>;
<a name="L1314" href="source/net/ipv4/netfilter/arp_tables.c#L1314">1314</a>                 if ((unsigned char *)<a href="ident?i=de">de</a> - <a href="ident?i=base">base</a> &lt; newinfo-&gt;underflow[<a href="ident?i=h">h</a>])
<a name="L1315" href="source/net/ipv4/netfilter/arp_tables.c#L1315">1315</a>                         newinfo-&gt;underflow[<a href="ident?i=h">h</a>] -= origsize - *<a href="ident?i=size">size</a>;
<a name="L1316" href="source/net/ipv4/netfilter/arp_tables.c#L1316">1316</a>         }
<a name="L1317" href="source/net/ipv4/netfilter/arp_tables.c#L1317">1317</a>         return <a href="ident?i=ret">ret</a>;
<a name="L1318" href="source/net/ipv4/netfilter/arp_tables.c#L1318">1318</a> }
<a name="L1319" href="source/net/ipv4/netfilter/arp_tables.c#L1319">1319</a> 
<a name="L1320" href="source/net/ipv4/netfilter/arp_tables.c#L1320">1320</a> static int <a href="ident?i=translate_compat_table">translate_compat_table</a>(const char *<a href="ident?i=name">name</a>,
<a name="L1321" href="source/net/ipv4/netfilter/arp_tables.c#L1321">1321</a>                                   unsigned int valid_hooks,
<a name="L1322" href="source/net/ipv4/netfilter/arp_tables.c#L1322">1322</a>                                   struct <a href="ident?i=xt_table_info">xt_table_info</a> **pinfo,
<a name="L1323" href="source/net/ipv4/netfilter/arp_tables.c#L1323">1323</a>                                   void **pentry0,
<a name="L1324" href="source/net/ipv4/netfilter/arp_tables.c#L1324">1324</a>                                   unsigned int <a href="ident?i=total_size">total_size</a>,
<a name="L1325" href="source/net/ipv4/netfilter/arp_tables.c#L1325">1325</a>                                   unsigned int <a href="ident?i=number">number</a>,
<a name="L1326" href="source/net/ipv4/netfilter/arp_tables.c#L1326">1326</a>                                   unsigned int *hook_entries,
<a name="L1327" href="source/net/ipv4/netfilter/arp_tables.c#L1327">1327</a>                                   unsigned int *underflows)
<a name="L1328" href="source/net/ipv4/netfilter/arp_tables.c#L1328">1328</a> {
<a name="L1329" href="source/net/ipv4/netfilter/arp_tables.c#L1329">1329</a>         unsigned int <a href="ident?i=i">i</a>, j;
<a name="L1330" href="source/net/ipv4/netfilter/arp_tables.c#L1330">1330</a>         struct <a href="ident?i=xt_table_info">xt_table_info</a> *newinfo, *<a href="ident?i=info">info</a>;
<a name="L1331" href="source/net/ipv4/netfilter/arp_tables.c#L1331">1331</a>         void *<a href="ident?i=pos">pos</a>, *entry0, *entry1;
<a name="L1332" href="source/net/ipv4/netfilter/arp_tables.c#L1332">1332</a>         struct <a href="ident?i=compat_arpt_entry">compat_arpt_entry</a> *iter0;
<a name="L1333" href="source/net/ipv4/netfilter/arp_tables.c#L1333">1333</a>         struct <a href="ident?i=arpt_entry">arpt_entry</a> *iter1;
<a name="L1334" href="source/net/ipv4/netfilter/arp_tables.c#L1334">1334</a>         unsigned int <a href="ident?i=size">size</a>;
<a name="L1335" href="source/net/ipv4/netfilter/arp_tables.c#L1335">1335</a>         int <a href="ident?i=ret">ret</a> = 0;
<a name="L1336" href="source/net/ipv4/netfilter/arp_tables.c#L1336">1336</a> 
<a name="L1337" href="source/net/ipv4/netfilter/arp_tables.c#L1337">1337</a>         <a href="ident?i=info">info</a> = *pinfo;
<a name="L1338" href="source/net/ipv4/netfilter/arp_tables.c#L1338">1338</a>         entry0 = *pentry0;
<a name="L1339" href="source/net/ipv4/netfilter/arp_tables.c#L1339">1339</a>         <a href="ident?i=size">size</a> = <a href="ident?i=total_size">total_size</a>;
<a name="L1340" href="source/net/ipv4/netfilter/arp_tables.c#L1340">1340</a>         <a href="ident?i=info">info</a>-&gt;<a href="ident?i=number">number</a> = <a href="ident?i=number">number</a>;
<a name="L1341" href="source/net/ipv4/netfilter/arp_tables.c#L1341">1341</a> 
<a name="L1342" href="source/net/ipv4/netfilter/arp_tables.c#L1342">1342</a>         <b><i>/* Init all hooks to impossible value. */</i></b>
<a name="L1343" href="source/net/ipv4/netfilter/arp_tables.c#L1343">1343</a>         for (<a href="ident?i=i">i</a> = 0; <a href="ident?i=i">i</a> &lt; <a href="ident?i=NF_ARP_NUMHOOKS">NF_ARP_NUMHOOKS</a>; <a href="ident?i=i">i</a>++) {
<a name="L1344" href="source/net/ipv4/netfilter/arp_tables.c#L1344">1344</a>                 <a href="ident?i=info">info</a>-&gt;hook_entry[<a href="ident?i=i">i</a>] = 0xFFFFFFFF;
<a name="L1345" href="source/net/ipv4/netfilter/arp_tables.c#L1345">1345</a>                 <a href="ident?i=info">info</a>-&gt;underflow[<a href="ident?i=i">i</a>] = 0xFFFFFFFF;
<a name="L1346" href="source/net/ipv4/netfilter/arp_tables.c#L1346">1346</a>         }
<a name="L1347" href="source/net/ipv4/netfilter/arp_tables.c#L1347">1347</a> 
<a name="L1348" href="source/net/ipv4/netfilter/arp_tables.c#L1348">1348</a>         <a href="ident?i=duprintf">duprintf</a>(<i>"translate_compat_table: size %u\n"</i>, <a href="ident?i=info">info</a>-&gt;<a href="ident?i=size">size</a>);
<a name="L1349" href="source/net/ipv4/netfilter/arp_tables.c#L1349">1349</a>         j = 0;
<a name="L1350" href="source/net/ipv4/netfilter/arp_tables.c#L1350">1350</a>         <a href="ident?i=xt_compat_lock">xt_compat_lock</a>(NFPROTO_ARP);
<a name="L1351" href="source/net/ipv4/netfilter/arp_tables.c#L1351">1351</a>         <a href="ident?i=xt_compat_init_offsets">xt_compat_init_offsets</a>(NFPROTO_ARP, <a href="ident?i=number">number</a>);
<a name="L1352" href="source/net/ipv4/netfilter/arp_tables.c#L1352">1352</a>         <b><i>/* Walk through entries, checking offsets. */</i></b>
<a name="L1353" href="source/net/ipv4/netfilter/arp_tables.c#L1353">1353</a>         <a href="ident?i=xt_entry_foreach">xt_entry_foreach</a>(iter0, entry0, <a href="ident?i=total_size">total_size</a>) {
<a name="L1354" href="source/net/ipv4/netfilter/arp_tables.c#L1354">1354</a>                 <a href="ident?i=ret">ret</a> = <a href="ident?i=check_compat_entry_size_and_hooks">check_compat_entry_size_and_hooks</a>(iter0, <a href="ident?i=info">info</a>, &amp;<a href="ident?i=size">size</a>,
<a name="L1355" href="source/net/ipv4/netfilter/arp_tables.c#L1355">1355</a>                                                         entry0,
<a name="L1356" href="source/net/ipv4/netfilter/arp_tables.c#L1356">1356</a>                                                         entry0 + <a href="ident?i=total_size">total_size</a>,
<a name="L1357" href="source/net/ipv4/netfilter/arp_tables.c#L1357">1357</a>                                                         hook_entries,
<a name="L1358" href="source/net/ipv4/netfilter/arp_tables.c#L1358">1358</a>                                                         underflows,
<a name="L1359" href="source/net/ipv4/netfilter/arp_tables.c#L1359">1359</a>                                                         <a href="ident?i=name">name</a>);
<a name="L1360" href="source/net/ipv4/netfilter/arp_tables.c#L1360">1360</a>                 if (<a href="ident?i=ret">ret</a> != 0)
<a name="L1361" href="source/net/ipv4/netfilter/arp_tables.c#L1361">1361</a>                         goto out_unlock;
<a name="L1362" href="source/net/ipv4/netfilter/arp_tables.c#L1362">1362</a>                 ++j;
<a name="L1363" href="source/net/ipv4/netfilter/arp_tables.c#L1363">1363</a>         }
<a name="L1364" href="source/net/ipv4/netfilter/arp_tables.c#L1364">1364</a> 
<a name="L1365" href="source/net/ipv4/netfilter/arp_tables.c#L1365">1365</a>         <a href="ident?i=ret">ret</a> = -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L1366" href="source/net/ipv4/netfilter/arp_tables.c#L1366">1366</a>         if (j != <a href="ident?i=number">number</a>) {
<a name="L1367" href="source/net/ipv4/netfilter/arp_tables.c#L1367">1367</a>                 <a href="ident?i=duprintf">duprintf</a>(<i>"translate_compat_table: %u not %u entries\n"</i>,
<a name="L1368" href="source/net/ipv4/netfilter/arp_tables.c#L1368">1368</a>                          j, <a href="ident?i=number">number</a>);
<a name="L1369" href="source/net/ipv4/netfilter/arp_tables.c#L1369">1369</a>                 goto out_unlock;
<a name="L1370" href="source/net/ipv4/netfilter/arp_tables.c#L1370">1370</a>         }
<a name="L1371" href="source/net/ipv4/netfilter/arp_tables.c#L1371">1371</a> 
<a name="L1372" href="source/net/ipv4/netfilter/arp_tables.c#L1372">1372</a>         <b><i>/* Check hooks all assigned */</i></b>
<a name="L1373" href="source/net/ipv4/netfilter/arp_tables.c#L1373">1373</a>         for (<a href="ident?i=i">i</a> = 0; <a href="ident?i=i">i</a> &lt; <a href="ident?i=NF_ARP_NUMHOOKS">NF_ARP_NUMHOOKS</a>; <a href="ident?i=i">i</a>++) {
<a name="L1374" href="source/net/ipv4/netfilter/arp_tables.c#L1374">1374</a>                 <b><i>/* Only hooks which are valid */</i></b>
<a name="L1375" href="source/net/ipv4/netfilter/arp_tables.c#L1375">1375</a>                 if (!(valid_hooks &amp; (1 &lt;&lt; <a href="ident?i=i">i</a>)))
<a name="L1376" href="source/net/ipv4/netfilter/arp_tables.c#L1376">1376</a>                         continue;
<a name="L1377" href="source/net/ipv4/netfilter/arp_tables.c#L1377">1377</a>                 if (<a href="ident?i=info">info</a>-&gt;hook_entry[<a href="ident?i=i">i</a>] == 0xFFFFFFFF) {
<a name="L1378" href="source/net/ipv4/netfilter/arp_tables.c#L1378">1378</a>                         <a href="ident?i=duprintf">duprintf</a>(<i>"Invalid hook entry %u %u\n"</i>,
<a name="L1379" href="source/net/ipv4/netfilter/arp_tables.c#L1379">1379</a>                                  <a href="ident?i=i">i</a>, hook_entries[<a href="ident?i=i">i</a>]);
<a name="L1380" href="source/net/ipv4/netfilter/arp_tables.c#L1380">1380</a>                         goto out_unlock;
<a name="L1381" href="source/net/ipv4/netfilter/arp_tables.c#L1381">1381</a>                 }
<a name="L1382" href="source/net/ipv4/netfilter/arp_tables.c#L1382">1382</a>                 if (<a href="ident?i=info">info</a>-&gt;underflow[<a href="ident?i=i">i</a>] == 0xFFFFFFFF) {
<a name="L1383" href="source/net/ipv4/netfilter/arp_tables.c#L1383">1383</a>                         <a href="ident?i=duprintf">duprintf</a>(<i>"Invalid underflow %u %u\n"</i>,
<a name="L1384" href="source/net/ipv4/netfilter/arp_tables.c#L1384">1384</a>                                  <a href="ident?i=i">i</a>, underflows[<a href="ident?i=i">i</a>]);
<a name="L1385" href="source/net/ipv4/netfilter/arp_tables.c#L1385">1385</a>                         goto out_unlock;
<a name="L1386" href="source/net/ipv4/netfilter/arp_tables.c#L1386">1386</a>                 }
<a name="L1387" href="source/net/ipv4/netfilter/arp_tables.c#L1387">1387</a>         }
<a name="L1388" href="source/net/ipv4/netfilter/arp_tables.c#L1388">1388</a> 
<a name="L1389" href="source/net/ipv4/netfilter/arp_tables.c#L1389">1389</a>         <a href="ident?i=ret">ret</a> = -<a href="ident?i=ENOMEM">ENOMEM</a>;
<a name="L1390" href="source/net/ipv4/netfilter/arp_tables.c#L1390">1390</a>         newinfo = <a href="ident?i=xt_alloc_table_info">xt_alloc_table_info</a>(<a href="ident?i=size">size</a>);
<a name="L1391" href="source/net/ipv4/netfilter/arp_tables.c#L1391">1391</a>         if (!newinfo)
<a name="L1392" href="source/net/ipv4/netfilter/arp_tables.c#L1392">1392</a>                 goto out_unlock;
<a name="L1393" href="source/net/ipv4/netfilter/arp_tables.c#L1393">1393</a> 
<a name="L1394" href="source/net/ipv4/netfilter/arp_tables.c#L1394">1394</a>         newinfo-&gt;<a href="ident?i=number">number</a> = <a href="ident?i=number">number</a>;
<a name="L1395" href="source/net/ipv4/netfilter/arp_tables.c#L1395">1395</a>         for (<a href="ident?i=i">i</a> = 0; <a href="ident?i=i">i</a> &lt; <a href="ident?i=NF_ARP_NUMHOOKS">NF_ARP_NUMHOOKS</a>; <a href="ident?i=i">i</a>++) {
<a name="L1396" href="source/net/ipv4/netfilter/arp_tables.c#L1396">1396</a>                 newinfo-&gt;hook_entry[<a href="ident?i=i">i</a>] = <a href="ident?i=info">info</a>-&gt;hook_entry[<a href="ident?i=i">i</a>];
<a name="L1397" href="source/net/ipv4/netfilter/arp_tables.c#L1397">1397</a>                 newinfo-&gt;underflow[<a href="ident?i=i">i</a>] = <a href="ident?i=info">info</a>-&gt;underflow[<a href="ident?i=i">i</a>];
<a name="L1398" href="source/net/ipv4/netfilter/arp_tables.c#L1398">1398</a>         }
<a name="L1399" href="source/net/ipv4/netfilter/arp_tables.c#L1399">1399</a>         entry1 = newinfo-&gt;<a href="ident?i=entries">entries</a>[<a href="ident?i=raw_smp_processor_id">raw_smp_processor_id</a>()];
<a name="L1400" href="source/net/ipv4/netfilter/arp_tables.c#L1400">1400</a>         <a href="ident?i=pos">pos</a> = entry1;
<a name="L1401" href="source/net/ipv4/netfilter/arp_tables.c#L1401">1401</a>         <a href="ident?i=size">size</a> = <a href="ident?i=total_size">total_size</a>;
<a name="L1402" href="source/net/ipv4/netfilter/arp_tables.c#L1402">1402</a>         <a href="ident?i=xt_entry_foreach">xt_entry_foreach</a>(iter0, entry0, <a href="ident?i=total_size">total_size</a>) {
<a name="L1403" href="source/net/ipv4/netfilter/arp_tables.c#L1403">1403</a>                 <a href="ident?i=ret">ret</a> = <a href="ident?i=compat_copy_entry_from_user">compat_copy_entry_from_user</a>(iter0, &amp;<a href="ident?i=pos">pos</a>, &amp;<a href="ident?i=size">size</a>,
<a name="L1404" href="source/net/ipv4/netfilter/arp_tables.c#L1404">1404</a>                                                   <a href="ident?i=name">name</a>, newinfo, entry1);
<a name="L1405" href="source/net/ipv4/netfilter/arp_tables.c#L1405">1405</a>                 if (<a href="ident?i=ret">ret</a> != 0)
<a name="L1406" href="source/net/ipv4/netfilter/arp_tables.c#L1406">1406</a>                         break;
<a name="L1407" href="source/net/ipv4/netfilter/arp_tables.c#L1407">1407</a>         }
<a name="L1408" href="source/net/ipv4/netfilter/arp_tables.c#L1408">1408</a>         <a href="ident?i=xt_compat_flush_offsets">xt_compat_flush_offsets</a>(NFPROTO_ARP);
<a name="L1409" href="source/net/ipv4/netfilter/arp_tables.c#L1409">1409</a>         <a href="ident?i=xt_compat_unlock">xt_compat_unlock</a>(NFPROTO_ARP);
<a name="L1410" href="source/net/ipv4/netfilter/arp_tables.c#L1410">1410</a>         if (<a href="ident?i=ret">ret</a>)
<a name="L1411" href="source/net/ipv4/netfilter/arp_tables.c#L1411">1411</a>                 goto free_newinfo;
<a name="L1412" href="source/net/ipv4/netfilter/arp_tables.c#L1412">1412</a> 
<a name="L1413" href="source/net/ipv4/netfilter/arp_tables.c#L1413">1413</a>         <a href="ident?i=ret">ret</a> = -<a href="ident?i=ELOOP">ELOOP</a>;
<a name="L1414" href="source/net/ipv4/netfilter/arp_tables.c#L1414">1414</a>         if (!<a href="ident?i=mark_source_chains">mark_source_chains</a>(newinfo, valid_hooks, entry1))
<a name="L1415" href="source/net/ipv4/netfilter/arp_tables.c#L1415">1415</a>                 goto free_newinfo;
<a name="L1416" href="source/net/ipv4/netfilter/arp_tables.c#L1416">1416</a> 
<a name="L1417" href="source/net/ipv4/netfilter/arp_tables.c#L1417">1417</a>         <a href="ident?i=i">i</a> = 0;
<a name="L1418" href="source/net/ipv4/netfilter/arp_tables.c#L1418">1418</a>         <a href="ident?i=xt_entry_foreach">xt_entry_foreach</a>(iter1, entry1, newinfo-&gt;<a href="ident?i=size">size</a>) {
<a name="L1419" href="source/net/ipv4/netfilter/arp_tables.c#L1419">1419</a>                 <a href="ident?i=ret">ret</a> = <a href="ident?i=check_target">check_target</a>(iter1, <a href="ident?i=name">name</a>);
<a name="L1420" href="source/net/ipv4/netfilter/arp_tables.c#L1420">1420</a>                 if (<a href="ident?i=ret">ret</a> != 0)
<a name="L1421" href="source/net/ipv4/netfilter/arp_tables.c#L1421">1421</a>                         break;
<a name="L1422" href="source/net/ipv4/netfilter/arp_tables.c#L1422">1422</a>                 ++<a href="ident?i=i">i</a>;
<a name="L1423" href="source/net/ipv4/netfilter/arp_tables.c#L1423">1423</a>                 if (<a href="ident?i=strcmp">strcmp</a>(<a href="ident?i=arpt_get_target">arpt_get_target</a>(iter1)-&gt;u.<a href="ident?i=user">user</a>.<a href="ident?i=name">name</a>,
<a name="L1424" href="source/net/ipv4/netfilter/arp_tables.c#L1424">1424</a>                     <a href="ident?i=XT_ERROR_TARGET">XT_ERROR_TARGET</a>) == 0)
<a name="L1425" href="source/net/ipv4/netfilter/arp_tables.c#L1425">1425</a>                         ++newinfo-&gt;stacksize;
<a name="L1426" href="source/net/ipv4/netfilter/arp_tables.c#L1426">1426</a>         }
<a name="L1427" href="source/net/ipv4/netfilter/arp_tables.c#L1427">1427</a>         if (<a href="ident?i=ret">ret</a>) {
<a name="L1428" href="source/net/ipv4/netfilter/arp_tables.c#L1428">1428</a>                 <b><i>/*</i></b>
<a name="L1429" href="source/net/ipv4/netfilter/arp_tables.c#L1429">1429</a> <b><i>                 * The first i matches need cleanup_entry (calls -&gt;destroy)</i></b>
<a name="L1430" href="source/net/ipv4/netfilter/arp_tables.c#L1430">1430</a> <b><i>                 * because they had called -&gt;check already. The other j-i</i></b>
<a name="L1431" href="source/net/ipv4/netfilter/arp_tables.c#L1431">1431</a> <b><i>                 * entries need only release.</i></b>
<a name="L1432" href="source/net/ipv4/netfilter/arp_tables.c#L1432">1432</a> <b><i>                 */</i></b>
<a name="L1433" href="source/net/ipv4/netfilter/arp_tables.c#L1433">1433</a>                 int <a href="ident?i=skip">skip</a> = <a href="ident?i=i">i</a>;
<a name="L1434" href="source/net/ipv4/netfilter/arp_tables.c#L1434">1434</a>                 j -= <a href="ident?i=i">i</a>;
<a name="L1435" href="source/net/ipv4/netfilter/arp_tables.c#L1435">1435</a>                 <a href="ident?i=xt_entry_foreach">xt_entry_foreach</a>(iter0, entry0, newinfo-&gt;<a href="ident?i=size">size</a>) {
<a name="L1436" href="source/net/ipv4/netfilter/arp_tables.c#L1436">1436</a>                         if (<a href="ident?i=skip">skip</a>-- &gt; 0)
<a name="L1437" href="source/net/ipv4/netfilter/arp_tables.c#L1437">1437</a>                                 continue;
<a name="L1438" href="source/net/ipv4/netfilter/arp_tables.c#L1438">1438</a>                         if (j-- == 0)
<a name="L1439" href="source/net/ipv4/netfilter/arp_tables.c#L1439">1439</a>                                 break;
<a name="L1440" href="source/net/ipv4/netfilter/arp_tables.c#L1440">1440</a>                         <a href="ident?i=compat_release_entry">compat_release_entry</a>(iter0);
<a name="L1441" href="source/net/ipv4/netfilter/arp_tables.c#L1441">1441</a>                 }
<a name="L1442" href="source/net/ipv4/netfilter/arp_tables.c#L1442">1442</a>                 <a href="ident?i=xt_entry_foreach">xt_entry_foreach</a>(iter1, entry1, newinfo-&gt;<a href="ident?i=size">size</a>) {
<a name="L1443" href="source/net/ipv4/netfilter/arp_tables.c#L1443">1443</a>                         if (<a href="ident?i=i">i</a>-- == 0)
<a name="L1444" href="source/net/ipv4/netfilter/arp_tables.c#L1444">1444</a>                                 break;
<a name="L1445" href="source/net/ipv4/netfilter/arp_tables.c#L1445">1445</a>                         <a href="ident?i=cleanup_entry">cleanup_entry</a>(iter1);
<a name="L1446" href="source/net/ipv4/netfilter/arp_tables.c#L1446">1446</a>                 }
<a name="L1447" href="source/net/ipv4/netfilter/arp_tables.c#L1447">1447</a>                 <a href="ident?i=xt_free_table_info">xt_free_table_info</a>(newinfo);
<a name="L1448" href="source/net/ipv4/netfilter/arp_tables.c#L1448">1448</a>                 return <a href="ident?i=ret">ret</a>;
<a name="L1449" href="source/net/ipv4/netfilter/arp_tables.c#L1449">1449</a>         }
<a name="L1450" href="source/net/ipv4/netfilter/arp_tables.c#L1450">1450</a> 
<a name="L1451" href="source/net/ipv4/netfilter/arp_tables.c#L1451">1451</a>         <b><i>/* And one copy for every other CPU */</i></b>
<a name="L1452" href="source/net/ipv4/netfilter/arp_tables.c#L1452">1452</a>         <a href="ident?i=for_each_possible_cpu">for_each_possible_cpu</a>(<a href="ident?i=i">i</a>)
<a name="L1453" href="source/net/ipv4/netfilter/arp_tables.c#L1453">1453</a>                 if (newinfo-&gt;<a href="ident?i=entries">entries</a>[<a href="ident?i=i">i</a>] &amp;&amp; newinfo-&gt;<a href="ident?i=entries">entries</a>[<a href="ident?i=i">i</a>] != entry1)
<a name="L1454" href="source/net/ipv4/netfilter/arp_tables.c#L1454">1454</a>                         <a href="ident?i=memcpy">memcpy</a>(newinfo-&gt;<a href="ident?i=entries">entries</a>[<a href="ident?i=i">i</a>], entry1, newinfo-&gt;<a href="ident?i=size">size</a>);
<a name="L1455" href="source/net/ipv4/netfilter/arp_tables.c#L1455">1455</a> 
<a name="L1456" href="source/net/ipv4/netfilter/arp_tables.c#L1456">1456</a>         *pinfo = newinfo;
<a name="L1457" href="source/net/ipv4/netfilter/arp_tables.c#L1457">1457</a>         *pentry0 = entry1;
<a name="L1458" href="source/net/ipv4/netfilter/arp_tables.c#L1458">1458</a>         <a href="ident?i=xt_free_table_info">xt_free_table_info</a>(<a href="ident?i=info">info</a>);
<a name="L1459" href="source/net/ipv4/netfilter/arp_tables.c#L1459">1459</a>         return 0;
<a name="L1460" href="source/net/ipv4/netfilter/arp_tables.c#L1460">1460</a> 
<a name="L1461" href="source/net/ipv4/netfilter/arp_tables.c#L1461">1461</a> free_newinfo:
<a name="L1462" href="source/net/ipv4/netfilter/arp_tables.c#L1462">1462</a>         <a href="ident?i=xt_free_table_info">xt_free_table_info</a>(newinfo);
<a name="L1463" href="source/net/ipv4/netfilter/arp_tables.c#L1463">1463</a> <a href="ident?i=out">out</a>:
<a name="L1464" href="source/net/ipv4/netfilter/arp_tables.c#L1464">1464</a>         <a href="ident?i=xt_entry_foreach">xt_entry_foreach</a>(iter0, entry0, <a href="ident?i=total_size">total_size</a>) {
<a name="L1465" href="source/net/ipv4/netfilter/arp_tables.c#L1465">1465</a>                 if (j-- == 0)
<a name="L1466" href="source/net/ipv4/netfilter/arp_tables.c#L1466">1466</a>                         break;
<a name="L1467" href="source/net/ipv4/netfilter/arp_tables.c#L1467">1467</a>                 <a href="ident?i=compat_release_entry">compat_release_entry</a>(iter0);
<a name="L1468" href="source/net/ipv4/netfilter/arp_tables.c#L1468">1468</a>         }
<a name="L1469" href="source/net/ipv4/netfilter/arp_tables.c#L1469">1469</a>         return <a href="ident?i=ret">ret</a>;
<a name="L1470" href="source/net/ipv4/netfilter/arp_tables.c#L1470">1470</a> out_unlock:
<a name="L1471" href="source/net/ipv4/netfilter/arp_tables.c#L1471">1471</a>         <a href="ident?i=xt_compat_flush_offsets">xt_compat_flush_offsets</a>(NFPROTO_ARP);
<a name="L1472" href="source/net/ipv4/netfilter/arp_tables.c#L1472">1472</a>         <a href="ident?i=xt_compat_unlock">xt_compat_unlock</a>(NFPROTO_ARP);
<a name="L1473" href="source/net/ipv4/netfilter/arp_tables.c#L1473">1473</a>         goto <a href="ident?i=out">out</a>;
<a name="L1474" href="source/net/ipv4/netfilter/arp_tables.c#L1474">1474</a> }
<a name="L1475" href="source/net/ipv4/netfilter/arp_tables.c#L1475">1475</a> 
<a name="L1476" href="source/net/ipv4/netfilter/arp_tables.c#L1476">1476</a> struct <a href="ident?i=compat_arpt_replace">compat_arpt_replace</a> {
<a name="L1477" href="source/net/ipv4/netfilter/arp_tables.c#L1477">1477</a>         char                            <a href="ident?i=name">name</a>[<a href="ident?i=XT_TABLE_MAXNAMELEN">XT_TABLE_MAXNAMELEN</a>];
<a name="L1478" href="source/net/ipv4/netfilter/arp_tables.c#L1478">1478</a>         <a href="ident?i=u32">u32</a>                             valid_hooks;
<a name="L1479" href="source/net/ipv4/netfilter/arp_tables.c#L1479">1479</a>         <a href="ident?i=u32">u32</a>                             <a href="ident?i=num_entries">num_entries</a>;
<a name="L1480" href="source/net/ipv4/netfilter/arp_tables.c#L1480">1480</a>         <a href="ident?i=u32">u32</a>                             <a href="ident?i=size">size</a>;
<a name="L1481" href="source/net/ipv4/netfilter/arp_tables.c#L1481">1481</a>         <a href="ident?i=u32">u32</a>                             hook_entry[<a href="ident?i=NF_ARP_NUMHOOKS">NF_ARP_NUMHOOKS</a>];
<a name="L1482" href="source/net/ipv4/netfilter/arp_tables.c#L1482">1482</a>         <a href="ident?i=u32">u32</a>                             underflow[<a href="ident?i=NF_ARP_NUMHOOKS">NF_ARP_NUMHOOKS</a>];
<a name="L1483" href="source/net/ipv4/netfilter/arp_tables.c#L1483">1483</a>         <a href="ident?i=u32">u32</a>                             <a href="ident?i=num_counters">num_counters</a>;
<a name="L1484" href="source/net/ipv4/netfilter/arp_tables.c#L1484">1484</a>         <a href="ident?i=compat_uptr_t">compat_uptr_t</a>                   counters;
<a name="L1485" href="source/net/ipv4/netfilter/arp_tables.c#L1485">1485</a>         struct <a href="ident?i=compat_arpt_entry">compat_arpt_entry</a>        <a href="ident?i=entries">entries</a>[0];
<a name="L1486" href="source/net/ipv4/netfilter/arp_tables.c#L1486">1486</a> };
<a name="L1487" href="source/net/ipv4/netfilter/arp_tables.c#L1487">1487</a> 
<a name="L1488" href="source/net/ipv4/netfilter/arp_tables.c#L1488">1488</a> static int <a href="ident?i=compat_do_replace">compat_do_replace</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>, void <a href="ident?i=__user">__user</a> *<a href="ident?i=user">user</a>,
<a name="L1489" href="source/net/ipv4/netfilter/arp_tables.c#L1489">1489</a>                              unsigned int <a href="ident?i=len">len</a>)
<a name="L1490" href="source/net/ipv4/netfilter/arp_tables.c#L1490">1490</a> {
<a name="L1491" href="source/net/ipv4/netfilter/arp_tables.c#L1491">1491</a>         int <a href="ident?i=ret">ret</a>;
<a name="L1492" href="source/net/ipv4/netfilter/arp_tables.c#L1492">1492</a>         struct <a href="ident?i=compat_arpt_replace">compat_arpt_replace</a> <a href="ident?i=tmp">tmp</a>;
<a name="L1493" href="source/net/ipv4/netfilter/arp_tables.c#L1493">1493</a>         struct <a href="ident?i=xt_table_info">xt_table_info</a> *newinfo;
<a name="L1494" href="source/net/ipv4/netfilter/arp_tables.c#L1494">1494</a>         void *loc_cpu_entry;
<a name="L1495" href="source/net/ipv4/netfilter/arp_tables.c#L1495">1495</a>         struct <a href="ident?i=arpt_entry">arpt_entry</a> *iter;
<a name="L1496" href="source/net/ipv4/netfilter/arp_tables.c#L1496">1496</a> 
<a name="L1497" href="source/net/ipv4/netfilter/arp_tables.c#L1497">1497</a>         if (<a href="ident?i=copy_from_user">copy_from_user</a>(&amp;<a href="ident?i=tmp">tmp</a>, <a href="ident?i=user">user</a>, sizeof(<a href="ident?i=tmp">tmp</a>)) != 0)
<a name="L1498" href="source/net/ipv4/netfilter/arp_tables.c#L1498">1498</a>                 return -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L1499" href="source/net/ipv4/netfilter/arp_tables.c#L1499">1499</a> 
<a name="L1500" href="source/net/ipv4/netfilter/arp_tables.c#L1500">1500</a>         <b><i>/* overflow check */</i></b>
<a name="L1501" href="source/net/ipv4/netfilter/arp_tables.c#L1501">1501</a>         if (<a href="ident?i=tmp">tmp</a>.<a href="ident?i=size">size</a> &gt;= <a href="ident?i=INT_MAX">INT_MAX</a> / <a href="ident?i=num_possible_cpus">num_possible_cpus</a>())
<a name="L1502" href="source/net/ipv4/netfilter/arp_tables.c#L1502">1502</a>                 return -<a href="ident?i=ENOMEM">ENOMEM</a>;
<a name="L1503" href="source/net/ipv4/netfilter/arp_tables.c#L1503">1503</a>         if (<a href="ident?i=tmp">tmp</a>.<a href="ident?i=num_counters">num_counters</a> &gt;= <a href="ident?i=INT_MAX">INT_MAX</a> / sizeof(struct <a href="ident?i=xt_counters">xt_counters</a>))
<a name="L1504" href="source/net/ipv4/netfilter/arp_tables.c#L1504">1504</a>                 return -<a href="ident?i=ENOMEM">ENOMEM</a>;
<a name="L1505" href="source/net/ipv4/netfilter/arp_tables.c#L1505">1505</a>         if (<a href="ident?i=tmp">tmp</a>.<a href="ident?i=num_counters">num_counters</a> == 0)
<a name="L1506" href="source/net/ipv4/netfilter/arp_tables.c#L1506">1506</a>                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L1507" href="source/net/ipv4/netfilter/arp_tables.c#L1507">1507</a> 
<a name="L1508" href="source/net/ipv4/netfilter/arp_tables.c#L1508">1508</a>         <a href="ident?i=tmp">tmp</a>.<a href="ident?i=name">name</a>[sizeof(<a href="ident?i=tmp">tmp</a>.<a href="ident?i=name">name</a>)-1] = 0;
<a name="L1509" href="source/net/ipv4/netfilter/arp_tables.c#L1509">1509</a> 
<a name="L1510" href="source/net/ipv4/netfilter/arp_tables.c#L1510">1510</a>         newinfo = <a href="ident?i=xt_alloc_table_info">xt_alloc_table_info</a>(<a href="ident?i=tmp">tmp</a>.<a href="ident?i=size">size</a>);
<a name="L1511" href="source/net/ipv4/netfilter/arp_tables.c#L1511">1511</a>         if (!newinfo)
<a name="L1512" href="source/net/ipv4/netfilter/arp_tables.c#L1512">1512</a>                 return -<a href="ident?i=ENOMEM">ENOMEM</a>;
<a name="L1513" href="source/net/ipv4/netfilter/arp_tables.c#L1513">1513</a> 
<a name="L1514" href="source/net/ipv4/netfilter/arp_tables.c#L1514">1514</a>         <b><i>/* choose the copy that is on our node/cpu */</i></b>
<a name="L1515" href="source/net/ipv4/netfilter/arp_tables.c#L1515">1515</a>         loc_cpu_entry = newinfo-&gt;<a href="ident?i=entries">entries</a>[<a href="ident?i=raw_smp_processor_id">raw_smp_processor_id</a>()];
<a name="L1516" href="source/net/ipv4/netfilter/arp_tables.c#L1516">1516</a>         if (<a href="ident?i=copy_from_user">copy_from_user</a>(loc_cpu_entry, <a href="ident?i=user">user</a> + sizeof(<a href="ident?i=tmp">tmp</a>), <a href="ident?i=tmp">tmp</a>.<a href="ident?i=size">size</a>) != 0) {
<a name="L1517" href="source/net/ipv4/netfilter/arp_tables.c#L1517">1517</a>                 <a href="ident?i=ret">ret</a> = -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L1518" href="source/net/ipv4/netfilter/arp_tables.c#L1518">1518</a>                 goto free_newinfo;
<a name="L1519" href="source/net/ipv4/netfilter/arp_tables.c#L1519">1519</a>         }
<a name="L1520" href="source/net/ipv4/netfilter/arp_tables.c#L1520">1520</a> 
<a name="L1521" href="source/net/ipv4/netfilter/arp_tables.c#L1521">1521</a>         <a href="ident?i=ret">ret</a> = <a href="ident?i=translate_compat_table">translate_compat_table</a>(<a href="ident?i=tmp">tmp</a>.<a href="ident?i=name">name</a>, <a href="ident?i=tmp">tmp</a>.valid_hooks,
<a name="L1522" href="source/net/ipv4/netfilter/arp_tables.c#L1522">1522</a>                                      &amp;newinfo, &amp;loc_cpu_entry, <a href="ident?i=tmp">tmp</a>.<a href="ident?i=size">size</a>,
<a name="L1523" href="source/net/ipv4/netfilter/arp_tables.c#L1523">1523</a>                                      <a href="ident?i=tmp">tmp</a>.<a href="ident?i=num_entries">num_entries</a>, <a href="ident?i=tmp">tmp</a>.hook_entry,
<a name="L1524" href="source/net/ipv4/netfilter/arp_tables.c#L1524">1524</a>                                      <a href="ident?i=tmp">tmp</a>.underflow);
<a name="L1525" href="source/net/ipv4/netfilter/arp_tables.c#L1525">1525</a>         if (<a href="ident?i=ret">ret</a> != 0)
<a name="L1526" href="source/net/ipv4/netfilter/arp_tables.c#L1526">1526</a>                 goto free_newinfo;
<a name="L1527" href="source/net/ipv4/netfilter/arp_tables.c#L1527">1527</a> 
<a name="L1528" href="source/net/ipv4/netfilter/arp_tables.c#L1528">1528</a>         <a href="ident?i=duprintf">duprintf</a>(<i>"compat_do_replace: Translated table\n"</i>);
<a name="L1529" href="source/net/ipv4/netfilter/arp_tables.c#L1529">1529</a> 
<a name="L1530" href="source/net/ipv4/netfilter/arp_tables.c#L1530">1530</a>         <a href="ident?i=ret">ret</a> = <a href="ident?i=__do_replace">__do_replace</a>(<a href="ident?i=net">net</a>, <a href="ident?i=tmp">tmp</a>.<a href="ident?i=name">name</a>, <a href="ident?i=tmp">tmp</a>.valid_hooks, newinfo,
<a name="L1531" href="source/net/ipv4/netfilter/arp_tables.c#L1531">1531</a>                            <a href="ident?i=tmp">tmp</a>.<a href="ident?i=num_counters">num_counters</a>, <a href="ident?i=compat_ptr">compat_ptr</a>(<a href="ident?i=tmp">tmp</a>.counters));
<a name="L1532" href="source/net/ipv4/netfilter/arp_tables.c#L1532">1532</a>         if (<a href="ident?i=ret">ret</a>)
<a name="L1533" href="source/net/ipv4/netfilter/arp_tables.c#L1533">1533</a>                 goto free_newinfo_untrans;
<a name="L1534" href="source/net/ipv4/netfilter/arp_tables.c#L1534">1534</a>         return 0;
<a name="L1535" href="source/net/ipv4/netfilter/arp_tables.c#L1535">1535</a> 
<a name="L1536" href="source/net/ipv4/netfilter/arp_tables.c#L1536">1536</a>  free_newinfo_untrans:
<a name="L1537" href="source/net/ipv4/netfilter/arp_tables.c#L1537">1537</a>         <a href="ident?i=xt_entry_foreach">xt_entry_foreach</a>(iter, loc_cpu_entry, newinfo-&gt;<a href="ident?i=size">size</a>)
<a name="L1538" href="source/net/ipv4/netfilter/arp_tables.c#L1538">1538</a>                 <a href="ident?i=cleanup_entry">cleanup_entry</a>(iter);
<a name="L1539" href="source/net/ipv4/netfilter/arp_tables.c#L1539">1539</a>  free_newinfo:
<a name="L1540" href="source/net/ipv4/netfilter/arp_tables.c#L1540">1540</a>         <a href="ident?i=xt_free_table_info">xt_free_table_info</a>(newinfo);
<a name="L1541" href="source/net/ipv4/netfilter/arp_tables.c#L1541">1541</a>         return <a href="ident?i=ret">ret</a>;
<a name="L1542" href="source/net/ipv4/netfilter/arp_tables.c#L1542">1542</a> }
<a name="L1543" href="source/net/ipv4/netfilter/arp_tables.c#L1543">1543</a> 
<a name="L1544" href="source/net/ipv4/netfilter/arp_tables.c#L1544">1544</a> static int <a href="ident?i=compat_do_arpt_set_ctl">compat_do_arpt_set_ctl</a>(struct <a href="ident?i=sock">sock</a> *sk, int <a href="ident?i=cmd">cmd</a>, void <a href="ident?i=__user">__user</a> *<a href="ident?i=user">user</a>,
<a name="L1545" href="source/net/ipv4/netfilter/arp_tables.c#L1545">1545</a>                                   unsigned int <a href="ident?i=len">len</a>)
<a name="L1546" href="source/net/ipv4/netfilter/arp_tables.c#L1546">1546</a> {
<a name="L1547" href="source/net/ipv4/netfilter/arp_tables.c#L1547">1547</a>         int <a href="ident?i=ret">ret</a>;
<a name="L1548" href="source/net/ipv4/netfilter/arp_tables.c#L1548">1548</a> 
<a name="L1549" href="source/net/ipv4/netfilter/arp_tables.c#L1549">1549</a>         if (!<a href="ident?i=ns_capable">ns_capable</a>(<a href="ident?i=sock_net">sock_net</a>(sk)-&gt;<a href="ident?i=user_ns">user_ns</a>, <a href="ident?i=CAP_NET_ADMIN">CAP_NET_ADMIN</a>))
<a name="L1550" href="source/net/ipv4/netfilter/arp_tables.c#L1550">1550</a>                 return -<a href="ident?i=EPERM">EPERM</a>;
<a name="L1551" href="source/net/ipv4/netfilter/arp_tables.c#L1551">1551</a> 
<a name="L1552" href="source/net/ipv4/netfilter/arp_tables.c#L1552">1552</a>         switch (<a href="ident?i=cmd">cmd</a>) {
<a name="L1553" href="source/net/ipv4/netfilter/arp_tables.c#L1553">1553</a>         case <a href="ident?i=ARPT_SO_SET_REPLACE">ARPT_SO_SET_REPLACE</a>:
<a name="L1554" href="source/net/ipv4/netfilter/arp_tables.c#L1554">1554</a>                 <a href="ident?i=ret">ret</a> = <a href="ident?i=compat_do_replace">compat_do_replace</a>(<a href="ident?i=sock_net">sock_net</a>(sk), <a href="ident?i=user">user</a>, <a href="ident?i=len">len</a>);
<a name="L1555" href="source/net/ipv4/netfilter/arp_tables.c#L1555">1555</a>                 break;
<a name="L1556" href="source/net/ipv4/netfilter/arp_tables.c#L1556">1556</a> 
<a name="L1557" href="source/net/ipv4/netfilter/arp_tables.c#L1557">1557</a>         case <a href="ident?i=ARPT_SO_SET_ADD_COUNTERS">ARPT_SO_SET_ADD_COUNTERS</a>:
<a name="L1558" href="source/net/ipv4/netfilter/arp_tables.c#L1558">1558</a>                 <a href="ident?i=ret">ret</a> = <a href="ident?i=do_add_counters">do_add_counters</a>(<a href="ident?i=sock_net">sock_net</a>(sk), <a href="ident?i=user">user</a>, <a href="ident?i=len">len</a>, 1);
<a name="L1559" href="source/net/ipv4/netfilter/arp_tables.c#L1559">1559</a>                 break;
<a name="L1560" href="source/net/ipv4/netfilter/arp_tables.c#L1560">1560</a> 
<a name="L1561" href="source/net/ipv4/netfilter/arp_tables.c#L1561">1561</a>         default:
<a name="L1562" href="source/net/ipv4/netfilter/arp_tables.c#L1562">1562</a>                 <a href="ident?i=duprintf">duprintf</a>(<i>"do_arpt_set_ctl:  unknown request %i\n"</i>, <a href="ident?i=cmd">cmd</a>);
<a name="L1563" href="source/net/ipv4/netfilter/arp_tables.c#L1563">1563</a>                 <a href="ident?i=ret">ret</a> = -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L1564" href="source/net/ipv4/netfilter/arp_tables.c#L1564">1564</a>         }
<a name="L1565" href="source/net/ipv4/netfilter/arp_tables.c#L1565">1565</a> 
<a name="L1566" href="source/net/ipv4/netfilter/arp_tables.c#L1566">1566</a>         return <a href="ident?i=ret">ret</a>;
<a name="L1567" href="source/net/ipv4/netfilter/arp_tables.c#L1567">1567</a> }
<a name="L1568" href="source/net/ipv4/netfilter/arp_tables.c#L1568">1568</a> 
<a name="L1569" href="source/net/ipv4/netfilter/arp_tables.c#L1569">1569</a> static int <a href="ident?i=compat_copy_entry_to_user">compat_copy_entry_to_user</a>(struct <a href="ident?i=arpt_entry">arpt_entry</a> *<a href="ident?i=e">e</a>, void <a href="ident?i=__user">__user</a> **<a href="ident?i=dstptr">dstptr</a>,
<a name="L1570" href="source/net/ipv4/netfilter/arp_tables.c#L1570">1570</a>                                      <a href="ident?i=compat_uint_t">compat_uint_t</a> *<a href="ident?i=size">size</a>,
<a name="L1571" href="source/net/ipv4/netfilter/arp_tables.c#L1571">1571</a>                                      struct <a href="ident?i=xt_counters">xt_counters</a> *counters,
<a name="L1572" href="source/net/ipv4/netfilter/arp_tables.c#L1572">1572</a>                                      unsigned int <a href="ident?i=i">i</a>)
<a name="L1573" href="source/net/ipv4/netfilter/arp_tables.c#L1573">1573</a> {
<a name="L1574" href="source/net/ipv4/netfilter/arp_tables.c#L1574">1574</a>         struct <a href="ident?i=xt_entry_target">xt_entry_target</a> *<a href="ident?i=t">t</a>;
<a name="L1575" href="source/net/ipv4/netfilter/arp_tables.c#L1575">1575</a>         struct <a href="ident?i=compat_arpt_entry">compat_arpt_entry</a> <a href="ident?i=__user">__user</a> *ce;
<a name="L1576" href="source/net/ipv4/netfilter/arp_tables.c#L1576">1576</a>         <a href="ident?i=u_int16_t">u_int16_t</a> target_offset, next_offset;
<a name="L1577" href="source/net/ipv4/netfilter/arp_tables.c#L1577">1577</a>         <a href="ident?i=compat_uint_t">compat_uint_t</a> origsize;
<a name="L1578" href="source/net/ipv4/netfilter/arp_tables.c#L1578">1578</a>         int <a href="ident?i=ret">ret</a>;
<a name="L1579" href="source/net/ipv4/netfilter/arp_tables.c#L1579">1579</a> 
<a name="L1580" href="source/net/ipv4/netfilter/arp_tables.c#L1580">1580</a>         origsize = *<a href="ident?i=size">size</a>;
<a name="L1581" href="source/net/ipv4/netfilter/arp_tables.c#L1581">1581</a>         ce = (struct <a href="ident?i=compat_arpt_entry">compat_arpt_entry</a> <a href="ident?i=__user">__user</a> *)*<a href="ident?i=dstptr">dstptr</a>;
<a name="L1582" href="source/net/ipv4/netfilter/arp_tables.c#L1582">1582</a>         if (<a href="ident?i=copy_to_user">copy_to_user</a>(ce, <a href="ident?i=e">e</a>, sizeof(struct <a href="ident?i=arpt_entry">arpt_entry</a>)) != 0 ||
<a name="L1583" href="source/net/ipv4/netfilter/arp_tables.c#L1583">1583</a>             <a href="ident?i=copy_to_user">copy_to_user</a>(&amp;ce-&gt;counters, &amp;counters[<a href="ident?i=i">i</a>],
<a name="L1584" href="source/net/ipv4/netfilter/arp_tables.c#L1584">1584</a>             sizeof(counters[<a href="ident?i=i">i</a>])) != 0)
<a name="L1585" href="source/net/ipv4/netfilter/arp_tables.c#L1585">1585</a>                 return -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L1586" href="source/net/ipv4/netfilter/arp_tables.c#L1586">1586</a> 
<a name="L1587" href="source/net/ipv4/netfilter/arp_tables.c#L1587">1587</a>         *<a href="ident?i=dstptr">dstptr</a> += sizeof(struct <a href="ident?i=compat_arpt_entry">compat_arpt_entry</a>);
<a name="L1588" href="source/net/ipv4/netfilter/arp_tables.c#L1588">1588</a>         *<a href="ident?i=size">size</a> -= sizeof(struct <a href="ident?i=arpt_entry">arpt_entry</a>) - sizeof(struct <a href="ident?i=compat_arpt_entry">compat_arpt_entry</a>);
<a name="L1589" href="source/net/ipv4/netfilter/arp_tables.c#L1589">1589</a> 
<a name="L1590" href="source/net/ipv4/netfilter/arp_tables.c#L1590">1590</a>         target_offset = <a href="ident?i=e">e</a>-&gt;target_offset - (origsize - *<a href="ident?i=size">size</a>);
<a name="L1591" href="source/net/ipv4/netfilter/arp_tables.c#L1591">1591</a> 
<a name="L1592" href="source/net/ipv4/netfilter/arp_tables.c#L1592">1592</a>         <a href="ident?i=t">t</a> = <a href="ident?i=arpt_get_target">arpt_get_target</a>(<a href="ident?i=e">e</a>);
<a name="L1593" href="source/net/ipv4/netfilter/arp_tables.c#L1593">1593</a>         <a href="ident?i=ret">ret</a> = <a href="ident?i=xt_compat_target_to_user">xt_compat_target_to_user</a>(<a href="ident?i=t">t</a>, <a href="ident?i=dstptr">dstptr</a>, <a href="ident?i=size">size</a>);
<a name="L1594" href="source/net/ipv4/netfilter/arp_tables.c#L1594">1594</a>         if (<a href="ident?i=ret">ret</a>)
<a name="L1595" href="source/net/ipv4/netfilter/arp_tables.c#L1595">1595</a>                 return <a href="ident?i=ret">ret</a>;
<a name="L1596" href="source/net/ipv4/netfilter/arp_tables.c#L1596">1596</a>         next_offset = <a href="ident?i=e">e</a>-&gt;next_offset - (origsize - *<a href="ident?i=size">size</a>);
<a name="L1597" href="source/net/ipv4/netfilter/arp_tables.c#L1597">1597</a>         if (<a href="ident?i=put_user">put_user</a>(target_offset, &amp;ce-&gt;target_offset) != 0 ||
<a name="L1598" href="source/net/ipv4/netfilter/arp_tables.c#L1598">1598</a>             <a href="ident?i=put_user">put_user</a>(next_offset, &amp;ce-&gt;next_offset) != 0)
<a name="L1599" href="source/net/ipv4/netfilter/arp_tables.c#L1599">1599</a>                 return -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L1600" href="source/net/ipv4/netfilter/arp_tables.c#L1600">1600</a>         return 0;
<a name="L1601" href="source/net/ipv4/netfilter/arp_tables.c#L1601">1601</a> }
<a name="L1602" href="source/net/ipv4/netfilter/arp_tables.c#L1602">1602</a> 
<a name="L1603" href="source/net/ipv4/netfilter/arp_tables.c#L1603">1603</a> static int <a href="ident?i=compat_copy_entries_to_user">compat_copy_entries_to_user</a>(unsigned int <a href="ident?i=total_size">total_size</a>,
<a name="L1604" href="source/net/ipv4/netfilter/arp_tables.c#L1604">1604</a>                                        struct <a href="ident?i=xt_table">xt_table</a> *<a href="ident?i=table">table</a>,
<a name="L1605" href="source/net/ipv4/netfilter/arp_tables.c#L1605">1605</a>                                        void <a href="ident?i=__user">__user</a> *userptr)
<a name="L1606" href="source/net/ipv4/netfilter/arp_tables.c#L1606">1606</a> {
<a name="L1607" href="source/net/ipv4/netfilter/arp_tables.c#L1607">1607</a>         struct <a href="ident?i=xt_counters">xt_counters</a> *counters;
<a name="L1608" href="source/net/ipv4/netfilter/arp_tables.c#L1608">1608</a>         const struct <a href="ident?i=xt_table_info">xt_table_info</a> *<a href="ident?i=private">private</a> = <a href="ident?i=table">table</a>-&gt;<a href="ident?i=private">private</a>;
<a name="L1609" href="source/net/ipv4/netfilter/arp_tables.c#L1609">1609</a>         void <a href="ident?i=__user">__user</a> *<a href="ident?i=pos">pos</a>;
<a name="L1610" href="source/net/ipv4/netfilter/arp_tables.c#L1610">1610</a>         unsigned int <a href="ident?i=size">size</a>;
<a name="L1611" href="source/net/ipv4/netfilter/arp_tables.c#L1611">1611</a>         int <a href="ident?i=ret">ret</a> = 0;
<a name="L1612" href="source/net/ipv4/netfilter/arp_tables.c#L1612">1612</a>         void *loc_cpu_entry;
<a name="L1613" href="source/net/ipv4/netfilter/arp_tables.c#L1613">1613</a>         unsigned int <a href="ident?i=i">i</a> = 0;
<a name="L1614" href="source/net/ipv4/netfilter/arp_tables.c#L1614">1614</a>         struct <a href="ident?i=arpt_entry">arpt_entry</a> *iter;
<a name="L1615" href="source/net/ipv4/netfilter/arp_tables.c#L1615">1615</a> 
<a name="L1616" href="source/net/ipv4/netfilter/arp_tables.c#L1616">1616</a>         counters = <a href="ident?i=alloc_counters">alloc_counters</a>(<a href="ident?i=table">table</a>);
<a name="L1617" href="source/net/ipv4/netfilter/arp_tables.c#L1617">1617</a>         if (<a href="ident?i=IS_ERR">IS_ERR</a>(counters))
<a name="L1618" href="source/net/ipv4/netfilter/arp_tables.c#L1618">1618</a>                 return <a href="ident?i=PTR_ERR">PTR_ERR</a>(counters);
<a name="L1619" href="source/net/ipv4/netfilter/arp_tables.c#L1619">1619</a> 
<a name="L1620" href="source/net/ipv4/netfilter/arp_tables.c#L1620">1620</a>         <b><i>/* choose the copy on our node/cpu */</i></b>
<a name="L1621" href="source/net/ipv4/netfilter/arp_tables.c#L1621">1621</a>         loc_cpu_entry = <a href="ident?i=private">private</a>-&gt;<a href="ident?i=entries">entries</a>[<a href="ident?i=raw_smp_processor_id">raw_smp_processor_id</a>()];
<a name="L1622" href="source/net/ipv4/netfilter/arp_tables.c#L1622">1622</a>         <a href="ident?i=pos">pos</a> = userptr;
<a name="L1623" href="source/net/ipv4/netfilter/arp_tables.c#L1623">1623</a>         <a href="ident?i=size">size</a> = <a href="ident?i=total_size">total_size</a>;
<a name="L1624" href="source/net/ipv4/netfilter/arp_tables.c#L1624">1624</a>         <a href="ident?i=xt_entry_foreach">xt_entry_foreach</a>(iter, loc_cpu_entry, <a href="ident?i=total_size">total_size</a>) {
<a name="L1625" href="source/net/ipv4/netfilter/arp_tables.c#L1625">1625</a>                 <a href="ident?i=ret">ret</a> = <a href="ident?i=compat_copy_entry_to_user">compat_copy_entry_to_user</a>(iter, &amp;<a href="ident?i=pos">pos</a>,
<a name="L1626" href="source/net/ipv4/netfilter/arp_tables.c#L1626">1626</a>                                                 &amp;<a href="ident?i=size">size</a>, counters, <a href="ident?i=i">i</a>++);
<a name="L1627" href="source/net/ipv4/netfilter/arp_tables.c#L1627">1627</a>                 if (<a href="ident?i=ret">ret</a> != 0)
<a name="L1628" href="source/net/ipv4/netfilter/arp_tables.c#L1628">1628</a>                         break;
<a name="L1629" href="source/net/ipv4/netfilter/arp_tables.c#L1629">1629</a>         }
<a name="L1630" href="source/net/ipv4/netfilter/arp_tables.c#L1630">1630</a>         <a href="ident?i=vfree">vfree</a>(counters);
<a name="L1631" href="source/net/ipv4/netfilter/arp_tables.c#L1631">1631</a>         return <a href="ident?i=ret">ret</a>;
<a name="L1632" href="source/net/ipv4/netfilter/arp_tables.c#L1632">1632</a> }
<a name="L1633" href="source/net/ipv4/netfilter/arp_tables.c#L1633">1633</a> 
<a name="L1634" href="source/net/ipv4/netfilter/arp_tables.c#L1634">1634</a> struct <a href="ident?i=compat_arpt_get_entries">compat_arpt_get_entries</a> {
<a name="L1635" href="source/net/ipv4/netfilter/arp_tables.c#L1635">1635</a>         char <a href="ident?i=name">name</a>[<a href="ident?i=XT_TABLE_MAXNAMELEN">XT_TABLE_MAXNAMELEN</a>];
<a name="L1636" href="source/net/ipv4/netfilter/arp_tables.c#L1636">1636</a>         <a href="ident?i=compat_uint_t">compat_uint_t</a> <a href="ident?i=size">size</a>;
<a name="L1637" href="source/net/ipv4/netfilter/arp_tables.c#L1637">1637</a>         struct <a href="ident?i=compat_arpt_entry">compat_arpt_entry</a> entrytable[0];
<a name="L1638" href="source/net/ipv4/netfilter/arp_tables.c#L1638">1638</a> };
<a name="L1639" href="source/net/ipv4/netfilter/arp_tables.c#L1639">1639</a> 
<a name="L1640" href="source/net/ipv4/netfilter/arp_tables.c#L1640">1640</a> static int <a href="ident?i=compat_get_entries">compat_get_entries</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>,
<a name="L1641" href="source/net/ipv4/netfilter/arp_tables.c#L1641">1641</a>                               struct <a href="ident?i=compat_arpt_get_entries">compat_arpt_get_entries</a> <a href="ident?i=__user">__user</a> *uptr,
<a name="L1642" href="source/net/ipv4/netfilter/arp_tables.c#L1642">1642</a>                               int *<a href="ident?i=len">len</a>)
<a name="L1643" href="source/net/ipv4/netfilter/arp_tables.c#L1643">1643</a> {
<a name="L1644" href="source/net/ipv4/netfilter/arp_tables.c#L1644">1644</a>         int <a href="ident?i=ret">ret</a>;
<a name="L1645" href="source/net/ipv4/netfilter/arp_tables.c#L1645">1645</a>         struct <a href="ident?i=compat_arpt_get_entries">compat_arpt_get_entries</a> <a href="ident?i=get">get</a>;
<a name="L1646" href="source/net/ipv4/netfilter/arp_tables.c#L1646">1646</a>         struct <a href="ident?i=xt_table">xt_table</a> *<a href="ident?i=t">t</a>;
<a name="L1647" href="source/net/ipv4/netfilter/arp_tables.c#L1647">1647</a> 
<a name="L1648" href="source/net/ipv4/netfilter/arp_tables.c#L1648">1648</a>         if (*<a href="ident?i=len">len</a> &lt; sizeof(<a href="ident?i=get">get</a>)) {
<a name="L1649" href="source/net/ipv4/netfilter/arp_tables.c#L1649">1649</a>                 <a href="ident?i=duprintf">duprintf</a>(<i>"compat_get_entries: %u &lt; %zu\n"</i>, *<a href="ident?i=len">len</a>, sizeof(<a href="ident?i=get">get</a>));
<a name="L1650" href="source/net/ipv4/netfilter/arp_tables.c#L1650">1650</a>                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L1651" href="source/net/ipv4/netfilter/arp_tables.c#L1651">1651</a>         }
<a name="L1652" href="source/net/ipv4/netfilter/arp_tables.c#L1652">1652</a>         if (<a href="ident?i=copy_from_user">copy_from_user</a>(&amp;<a href="ident?i=get">get</a>, uptr, sizeof(<a href="ident?i=get">get</a>)) != 0)
<a name="L1653" href="source/net/ipv4/netfilter/arp_tables.c#L1653">1653</a>                 return -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L1654" href="source/net/ipv4/netfilter/arp_tables.c#L1654">1654</a>         if (*<a href="ident?i=len">len</a> != sizeof(struct <a href="ident?i=compat_arpt_get_entries">compat_arpt_get_entries</a>) + <a href="ident?i=get">get</a>.<a href="ident?i=size">size</a>) {
<a name="L1655" href="source/net/ipv4/netfilter/arp_tables.c#L1655">1655</a>                 <a href="ident?i=duprintf">duprintf</a>(<i>"compat_get_entries: %u != %zu\n"</i>,
<a name="L1656" href="source/net/ipv4/netfilter/arp_tables.c#L1656">1656</a>                          *<a href="ident?i=len">len</a>, sizeof(<a href="ident?i=get">get</a>) + <a href="ident?i=get">get</a>.<a href="ident?i=size">size</a>);
<a name="L1657" href="source/net/ipv4/netfilter/arp_tables.c#L1657">1657</a>                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L1658" href="source/net/ipv4/netfilter/arp_tables.c#L1658">1658</a>         }
<a name="L1659" href="source/net/ipv4/netfilter/arp_tables.c#L1659">1659</a> 
<a name="L1660" href="source/net/ipv4/netfilter/arp_tables.c#L1660">1660</a>         <a href="ident?i=xt_compat_lock">xt_compat_lock</a>(NFPROTO_ARP);
<a name="L1661" href="source/net/ipv4/netfilter/arp_tables.c#L1661">1661</a>         <a href="ident?i=t">t</a> = <a href="ident?i=xt_find_table_lock">xt_find_table_lock</a>(<a href="ident?i=net">net</a>, NFPROTO_ARP, <a href="ident?i=get">get</a>.<a href="ident?i=name">name</a>);
<a name="L1662" href="source/net/ipv4/netfilter/arp_tables.c#L1662">1662</a>         if (!<a href="ident?i=IS_ERR_OR_NULL">IS_ERR_OR_NULL</a>(<a href="ident?i=t">t</a>)) {
<a name="L1663" href="source/net/ipv4/netfilter/arp_tables.c#L1663">1663</a>                 const struct <a href="ident?i=xt_table_info">xt_table_info</a> *<a href="ident?i=private">private</a> = <a href="ident?i=t">t</a>-&gt;<a href="ident?i=private">private</a>;
<a name="L1664" href="source/net/ipv4/netfilter/arp_tables.c#L1664">1664</a>                 struct <a href="ident?i=xt_table_info">xt_table_info</a> <a href="ident?i=info">info</a>;
<a name="L1665" href="source/net/ipv4/netfilter/arp_tables.c#L1665">1665</a> 
<a name="L1666" href="source/net/ipv4/netfilter/arp_tables.c#L1666">1666</a>                 <a href="ident?i=duprintf">duprintf</a>(<i>"t-&gt;private-&gt;number = %u\n"</i>, <a href="ident?i=private">private</a>-&gt;<a href="ident?i=number">number</a>);
<a name="L1667" href="source/net/ipv4/netfilter/arp_tables.c#L1667">1667</a>                 <a href="ident?i=ret">ret</a> = <a href="ident?i=compat_table_info">compat_table_info</a>(<a href="ident?i=private">private</a>, &amp;<a href="ident?i=info">info</a>);
<a name="L1668" href="source/net/ipv4/netfilter/arp_tables.c#L1668">1668</a>                 if (!<a href="ident?i=ret">ret</a> &amp;&amp; <a href="ident?i=get">get</a>.<a href="ident?i=size">size</a> == <a href="ident?i=info">info</a>.<a href="ident?i=size">size</a>) {
<a name="L1669" href="source/net/ipv4/netfilter/arp_tables.c#L1669">1669</a>                         <a href="ident?i=ret">ret</a> = <a href="ident?i=compat_copy_entries_to_user">compat_copy_entries_to_user</a>(<a href="ident?i=private">private</a>-&gt;<a href="ident?i=size">size</a>,
<a name="L1670" href="source/net/ipv4/netfilter/arp_tables.c#L1670">1670</a>                                                           <a href="ident?i=t">t</a>, uptr-&gt;entrytable);
<a name="L1671" href="source/net/ipv4/netfilter/arp_tables.c#L1671">1671</a>                 } else if (!<a href="ident?i=ret">ret</a>) {
<a name="L1672" href="source/net/ipv4/netfilter/arp_tables.c#L1672">1672</a>                         <a href="ident?i=duprintf">duprintf</a>(<i>"compat_get_entries: I've got %u not %u!\n"</i>,
<a name="L1673" href="source/net/ipv4/netfilter/arp_tables.c#L1673">1673</a>                                  <a href="ident?i=private">private</a>-&gt;<a href="ident?i=size">size</a>, <a href="ident?i=get">get</a>.<a href="ident?i=size">size</a>);
<a name="L1674" href="source/net/ipv4/netfilter/arp_tables.c#L1674">1674</a>                         <a href="ident?i=ret">ret</a> = -<a href="ident?i=EAGAIN">EAGAIN</a>;
<a name="L1675" href="source/net/ipv4/netfilter/arp_tables.c#L1675">1675</a>                 }
<a name="L1676" href="source/net/ipv4/netfilter/arp_tables.c#L1676">1676</a>                 <a href="ident?i=xt_compat_flush_offsets">xt_compat_flush_offsets</a>(NFPROTO_ARP);
<a name="L1677" href="source/net/ipv4/netfilter/arp_tables.c#L1677">1677</a>                 <a href="ident?i=module_put">module_put</a>(<a href="ident?i=t">t</a>-&gt;<a href="ident?i=me">me</a>);
<a name="L1678" href="source/net/ipv4/netfilter/arp_tables.c#L1678">1678</a>                 <a href="ident?i=xt_table_unlock">xt_table_unlock</a>(<a href="ident?i=t">t</a>);
<a name="L1679" href="source/net/ipv4/netfilter/arp_tables.c#L1679">1679</a>         } else
<a name="L1680" href="source/net/ipv4/netfilter/arp_tables.c#L1680">1680</a>                 <a href="ident?i=ret">ret</a> = <a href="ident?i=t">t</a> ? <a href="ident?i=PTR_ERR">PTR_ERR</a>(<a href="ident?i=t">t</a>) : -<a href="ident?i=ENOENT">ENOENT</a>;
<a name="L1681" href="source/net/ipv4/netfilter/arp_tables.c#L1681">1681</a> 
<a name="L1682" href="source/net/ipv4/netfilter/arp_tables.c#L1682">1682</a>         <a href="ident?i=xt_compat_unlock">xt_compat_unlock</a>(NFPROTO_ARP);
<a name="L1683" href="source/net/ipv4/netfilter/arp_tables.c#L1683">1683</a>         return <a href="ident?i=ret">ret</a>;
<a name="L1684" href="source/net/ipv4/netfilter/arp_tables.c#L1684">1684</a> }
<a name="L1685" href="source/net/ipv4/netfilter/arp_tables.c#L1685">1685</a> 
<a name="L1686" href="source/net/ipv4/netfilter/arp_tables.c#L1686">1686</a> static int <a href="ident?i=do_arpt_get_ctl">do_arpt_get_ctl</a>(struct <a href="ident?i=sock">sock</a> *, int, void <a href="ident?i=__user">__user</a> *, int *);
<a name="L1687" href="source/net/ipv4/netfilter/arp_tables.c#L1687">1687</a> 
<a name="L1688" href="source/net/ipv4/netfilter/arp_tables.c#L1688">1688</a> static int <a href="ident?i=compat_do_arpt_get_ctl">compat_do_arpt_get_ctl</a>(struct <a href="ident?i=sock">sock</a> *sk, int <a href="ident?i=cmd">cmd</a>, void <a href="ident?i=__user">__user</a> *<a href="ident?i=user">user</a>,
<a name="L1689" href="source/net/ipv4/netfilter/arp_tables.c#L1689">1689</a>                                   int *<a href="ident?i=len">len</a>)
<a name="L1690" href="source/net/ipv4/netfilter/arp_tables.c#L1690">1690</a> {
<a name="L1691" href="source/net/ipv4/netfilter/arp_tables.c#L1691">1691</a>         int <a href="ident?i=ret">ret</a>;
<a name="L1692" href="source/net/ipv4/netfilter/arp_tables.c#L1692">1692</a> 
<a name="L1693" href="source/net/ipv4/netfilter/arp_tables.c#L1693">1693</a>         if (!<a href="ident?i=ns_capable">ns_capable</a>(<a href="ident?i=sock_net">sock_net</a>(sk)-&gt;<a href="ident?i=user_ns">user_ns</a>, <a href="ident?i=CAP_NET_ADMIN">CAP_NET_ADMIN</a>))
<a name="L1694" href="source/net/ipv4/netfilter/arp_tables.c#L1694">1694</a>                 return -<a href="ident?i=EPERM">EPERM</a>;
<a name="L1695" href="source/net/ipv4/netfilter/arp_tables.c#L1695">1695</a> 
<a name="L1696" href="source/net/ipv4/netfilter/arp_tables.c#L1696">1696</a>         switch (<a href="ident?i=cmd">cmd</a>) {
<a name="L1697" href="source/net/ipv4/netfilter/arp_tables.c#L1697">1697</a>         case <a href="ident?i=ARPT_SO_GET_INFO">ARPT_SO_GET_INFO</a>:
<a name="L1698" href="source/net/ipv4/netfilter/arp_tables.c#L1698">1698</a>                 <a href="ident?i=ret">ret</a> = <a href="ident?i=get_info">get_info</a>(<a href="ident?i=sock_net">sock_net</a>(sk), <a href="ident?i=user">user</a>, <a href="ident?i=len">len</a>, 1);
<a name="L1699" href="source/net/ipv4/netfilter/arp_tables.c#L1699">1699</a>                 break;
<a name="L1700" href="source/net/ipv4/netfilter/arp_tables.c#L1700">1700</a>         case <a href="ident?i=ARPT_SO_GET_ENTRIES">ARPT_SO_GET_ENTRIES</a>:
<a name="L1701" href="source/net/ipv4/netfilter/arp_tables.c#L1701">1701</a>                 <a href="ident?i=ret">ret</a> = <a href="ident?i=compat_get_entries">compat_get_entries</a>(<a href="ident?i=sock_net">sock_net</a>(sk), <a href="ident?i=user">user</a>, <a href="ident?i=len">len</a>);
<a name="L1702" href="source/net/ipv4/netfilter/arp_tables.c#L1702">1702</a>                 break;
<a name="L1703" href="source/net/ipv4/netfilter/arp_tables.c#L1703">1703</a>         default:
<a name="L1704" href="source/net/ipv4/netfilter/arp_tables.c#L1704">1704</a>                 <a href="ident?i=ret">ret</a> = <a href="ident?i=do_arpt_get_ctl">do_arpt_get_ctl</a>(sk, <a href="ident?i=cmd">cmd</a>, <a href="ident?i=user">user</a>, <a href="ident?i=len">len</a>);
<a name="L1705" href="source/net/ipv4/netfilter/arp_tables.c#L1705">1705</a>         }
<a name="L1706" href="source/net/ipv4/netfilter/arp_tables.c#L1706">1706</a>         return <a href="ident?i=ret">ret</a>;
<a name="L1707" href="source/net/ipv4/netfilter/arp_tables.c#L1707">1707</a> }
<a name="L1708" href="source/net/ipv4/netfilter/arp_tables.c#L1708">1708</a> #endif
<a name="L1709" href="source/net/ipv4/netfilter/arp_tables.c#L1709">1709</a> 
<a name="L1710" href="source/net/ipv4/netfilter/arp_tables.c#L1710">1710</a> static int <a href="ident?i=do_arpt_set_ctl">do_arpt_set_ctl</a>(struct <a href="ident?i=sock">sock</a> *sk, int <a href="ident?i=cmd">cmd</a>, void <a href="ident?i=__user">__user</a> *<a href="ident?i=user">user</a>, unsigned int <a href="ident?i=len">len</a>)
<a name="L1711" href="source/net/ipv4/netfilter/arp_tables.c#L1711">1711</a> {
<a name="L1712" href="source/net/ipv4/netfilter/arp_tables.c#L1712">1712</a>         int <a href="ident?i=ret">ret</a>;
<a name="L1713" href="source/net/ipv4/netfilter/arp_tables.c#L1713">1713</a> 
<a name="L1714" href="source/net/ipv4/netfilter/arp_tables.c#L1714">1714</a>         if (!<a href="ident?i=ns_capable">ns_capable</a>(<a href="ident?i=sock_net">sock_net</a>(sk)-&gt;<a href="ident?i=user_ns">user_ns</a>, <a href="ident?i=CAP_NET_ADMIN">CAP_NET_ADMIN</a>))
<a name="L1715" href="source/net/ipv4/netfilter/arp_tables.c#L1715">1715</a>                 return -<a href="ident?i=EPERM">EPERM</a>;
<a name="L1716" href="source/net/ipv4/netfilter/arp_tables.c#L1716">1716</a> 
<a name="L1717" href="source/net/ipv4/netfilter/arp_tables.c#L1717">1717</a>         switch (<a href="ident?i=cmd">cmd</a>) {
<a name="L1718" href="source/net/ipv4/netfilter/arp_tables.c#L1718">1718</a>         case <a href="ident?i=ARPT_SO_SET_REPLACE">ARPT_SO_SET_REPLACE</a>:
<a name="L1719" href="source/net/ipv4/netfilter/arp_tables.c#L1719">1719</a>                 <a href="ident?i=ret">ret</a> = <a href="ident?i=do_replace">do_replace</a>(<a href="ident?i=sock_net">sock_net</a>(sk), <a href="ident?i=user">user</a>, <a href="ident?i=len">len</a>);
<a name="L1720" href="source/net/ipv4/netfilter/arp_tables.c#L1720">1720</a>                 break;
<a name="L1721" href="source/net/ipv4/netfilter/arp_tables.c#L1721">1721</a> 
<a name="L1722" href="source/net/ipv4/netfilter/arp_tables.c#L1722">1722</a>         case <a href="ident?i=ARPT_SO_SET_ADD_COUNTERS">ARPT_SO_SET_ADD_COUNTERS</a>:
<a name="L1723" href="source/net/ipv4/netfilter/arp_tables.c#L1723">1723</a>                 <a href="ident?i=ret">ret</a> = <a href="ident?i=do_add_counters">do_add_counters</a>(<a href="ident?i=sock_net">sock_net</a>(sk), <a href="ident?i=user">user</a>, <a href="ident?i=len">len</a>, 0);
<a name="L1724" href="source/net/ipv4/netfilter/arp_tables.c#L1724">1724</a>                 break;
<a name="L1725" href="source/net/ipv4/netfilter/arp_tables.c#L1725">1725</a> 
<a name="L1726" href="source/net/ipv4/netfilter/arp_tables.c#L1726">1726</a>         default:
<a name="L1727" href="source/net/ipv4/netfilter/arp_tables.c#L1727">1727</a>                 <a href="ident?i=duprintf">duprintf</a>(<i>"do_arpt_set_ctl:  unknown request %i\n"</i>, <a href="ident?i=cmd">cmd</a>);
<a name="L1728" href="source/net/ipv4/netfilter/arp_tables.c#L1728">1728</a>                 <a href="ident?i=ret">ret</a> = -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L1729" href="source/net/ipv4/netfilter/arp_tables.c#L1729">1729</a>         }
<a name="L1730" href="source/net/ipv4/netfilter/arp_tables.c#L1730">1730</a> 
<a name="L1731" href="source/net/ipv4/netfilter/arp_tables.c#L1731">1731</a>         return <a href="ident?i=ret">ret</a>;
<a name="L1732" href="source/net/ipv4/netfilter/arp_tables.c#L1732">1732</a> }
<a name="L1733" href="source/net/ipv4/netfilter/arp_tables.c#L1733">1733</a> 
<a name="L1734" href="source/net/ipv4/netfilter/arp_tables.c#L1734">1734</a> static int <a href="ident?i=do_arpt_get_ctl">do_arpt_get_ctl</a>(struct <a href="ident?i=sock">sock</a> *sk, int <a href="ident?i=cmd">cmd</a>, void <a href="ident?i=__user">__user</a> *<a href="ident?i=user">user</a>, int *<a href="ident?i=len">len</a>)
<a name="L1735" href="source/net/ipv4/netfilter/arp_tables.c#L1735">1735</a> {
<a name="L1736" href="source/net/ipv4/netfilter/arp_tables.c#L1736">1736</a>         int <a href="ident?i=ret">ret</a>;
<a name="L1737" href="source/net/ipv4/netfilter/arp_tables.c#L1737">1737</a> 
<a name="L1738" href="source/net/ipv4/netfilter/arp_tables.c#L1738">1738</a>         if (!<a href="ident?i=ns_capable">ns_capable</a>(<a href="ident?i=sock_net">sock_net</a>(sk)-&gt;<a href="ident?i=user_ns">user_ns</a>, <a href="ident?i=CAP_NET_ADMIN">CAP_NET_ADMIN</a>))
<a name="L1739" href="source/net/ipv4/netfilter/arp_tables.c#L1739">1739</a>                 return -<a href="ident?i=EPERM">EPERM</a>;
<a name="L1740" href="source/net/ipv4/netfilter/arp_tables.c#L1740">1740</a> 
<a name="L1741" href="source/net/ipv4/netfilter/arp_tables.c#L1741">1741</a>         switch (<a href="ident?i=cmd">cmd</a>) {
<a name="L1742" href="source/net/ipv4/netfilter/arp_tables.c#L1742">1742</a>         case <a href="ident?i=ARPT_SO_GET_INFO">ARPT_SO_GET_INFO</a>:
<a name="L1743" href="source/net/ipv4/netfilter/arp_tables.c#L1743">1743</a>                 <a href="ident?i=ret">ret</a> = <a href="ident?i=get_info">get_info</a>(<a href="ident?i=sock_net">sock_net</a>(sk), <a href="ident?i=user">user</a>, <a href="ident?i=len">len</a>, 0);
<a name="L1744" href="source/net/ipv4/netfilter/arp_tables.c#L1744">1744</a>                 break;
<a name="L1745" href="source/net/ipv4/netfilter/arp_tables.c#L1745">1745</a> 
<a name="L1746" href="source/net/ipv4/netfilter/arp_tables.c#L1746">1746</a>         case <a href="ident?i=ARPT_SO_GET_ENTRIES">ARPT_SO_GET_ENTRIES</a>:
<a name="L1747" href="source/net/ipv4/netfilter/arp_tables.c#L1747">1747</a>                 <a href="ident?i=ret">ret</a> = <a href="ident?i=get_entries">get_entries</a>(<a href="ident?i=sock_net">sock_net</a>(sk), <a href="ident?i=user">user</a>, <a href="ident?i=len">len</a>);
<a name="L1748" href="source/net/ipv4/netfilter/arp_tables.c#L1748">1748</a>                 break;
<a name="L1749" href="source/net/ipv4/netfilter/arp_tables.c#L1749">1749</a> 
<a name="L1750" href="source/net/ipv4/netfilter/arp_tables.c#L1750">1750</a>         case <a href="ident?i=ARPT_SO_GET_REVISION_TARGET">ARPT_SO_GET_REVISION_TARGET</a>: {
<a name="L1751" href="source/net/ipv4/netfilter/arp_tables.c#L1751">1751</a>                 struct <a href="ident?i=xt_get_revision">xt_get_revision</a> rev;
<a name="L1752" href="source/net/ipv4/netfilter/arp_tables.c#L1752">1752</a> 
<a name="L1753" href="source/net/ipv4/netfilter/arp_tables.c#L1753">1753</a>                 if (*<a href="ident?i=len">len</a> != sizeof(rev)) {
<a name="L1754" href="source/net/ipv4/netfilter/arp_tables.c#L1754">1754</a>                         <a href="ident?i=ret">ret</a> = -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L1755" href="source/net/ipv4/netfilter/arp_tables.c#L1755">1755</a>                         break;
<a name="L1756" href="source/net/ipv4/netfilter/arp_tables.c#L1756">1756</a>                 }
<a name="L1757" href="source/net/ipv4/netfilter/arp_tables.c#L1757">1757</a>                 if (<a href="ident?i=copy_from_user">copy_from_user</a>(&amp;rev, <a href="ident?i=user">user</a>, sizeof(rev)) != 0) {
<a name="L1758" href="source/net/ipv4/netfilter/arp_tables.c#L1758">1758</a>                         <a href="ident?i=ret">ret</a> = -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L1759" href="source/net/ipv4/netfilter/arp_tables.c#L1759">1759</a>                         break;
<a name="L1760" href="source/net/ipv4/netfilter/arp_tables.c#L1760">1760</a>                 }
<a name="L1761" href="source/net/ipv4/netfilter/arp_tables.c#L1761">1761</a>                 rev.<a href="ident?i=name">name</a>[sizeof(rev.<a href="ident?i=name">name</a>)-1] = 0;
<a name="L1762" href="source/net/ipv4/netfilter/arp_tables.c#L1762">1762</a> 
<a name="L1763" href="source/net/ipv4/netfilter/arp_tables.c#L1763">1763</a>                 <a href="ident?i=try_then_request_module">try_then_request_module</a>(<a href="ident?i=xt_find_revision">xt_find_revision</a>(NFPROTO_ARP, rev.<a href="ident?i=name">name</a>,
<a name="L1764" href="source/net/ipv4/netfilter/arp_tables.c#L1764">1764</a>                                                          rev.<a href="ident?i=revision">revision</a>, 1, &amp;<a href="ident?i=ret">ret</a>),
<a name="L1765" href="source/net/ipv4/netfilter/arp_tables.c#L1765">1765</a>                                         <i>"arpt_%s"</i>, rev.<a href="ident?i=name">name</a>);
<a name="L1766" href="source/net/ipv4/netfilter/arp_tables.c#L1766">1766</a>                 break;
<a name="L1767" href="source/net/ipv4/netfilter/arp_tables.c#L1767">1767</a>         }
<a name="L1768" href="source/net/ipv4/netfilter/arp_tables.c#L1768">1768</a> 
<a name="L1769" href="source/net/ipv4/netfilter/arp_tables.c#L1769">1769</a>         default:
<a name="L1770" href="source/net/ipv4/netfilter/arp_tables.c#L1770">1770</a>                 <a href="ident?i=duprintf">duprintf</a>(<i>"do_arpt_get_ctl: unknown request %i\n"</i>, <a href="ident?i=cmd">cmd</a>);
<a name="L1771" href="source/net/ipv4/netfilter/arp_tables.c#L1771">1771</a>                 <a href="ident?i=ret">ret</a> = -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L1772" href="source/net/ipv4/netfilter/arp_tables.c#L1772">1772</a>         }
<a name="L1773" href="source/net/ipv4/netfilter/arp_tables.c#L1773">1773</a> 
<a name="L1774" href="source/net/ipv4/netfilter/arp_tables.c#L1774">1774</a>         return <a href="ident?i=ret">ret</a>;
<a name="L1775" href="source/net/ipv4/netfilter/arp_tables.c#L1775">1775</a> }
<a name="L1776" href="source/net/ipv4/netfilter/arp_tables.c#L1776">1776</a> 
<a name="L1777" href="source/net/ipv4/netfilter/arp_tables.c#L1777">1777</a> struct <a href="ident?i=xt_table">xt_table</a> *<a href="ident?i=arpt_register_table">arpt_register_table</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>,
<a name="L1778" href="source/net/ipv4/netfilter/arp_tables.c#L1778">1778</a>                                      const struct <a href="ident?i=xt_table">xt_table</a> *<a href="ident?i=table">table</a>,
<a name="L1779" href="source/net/ipv4/netfilter/arp_tables.c#L1779">1779</a>                                      const struct <a href="ident?i=arpt_replace">arpt_replace</a> *repl)
<a name="L1780" href="source/net/ipv4/netfilter/arp_tables.c#L1780">1780</a> {
<a name="L1781" href="source/net/ipv4/netfilter/arp_tables.c#L1781">1781</a>         int <a href="ident?i=ret">ret</a>;
<a name="L1782" href="source/net/ipv4/netfilter/arp_tables.c#L1782">1782</a>         struct <a href="ident?i=xt_table_info">xt_table_info</a> *newinfo;
<a name="L1783" href="source/net/ipv4/netfilter/arp_tables.c#L1783">1783</a>         struct <a href="ident?i=xt_table_info">xt_table_info</a> <a href="ident?i=bootstrap">bootstrap</a> = {0};
<a name="L1784" href="source/net/ipv4/netfilter/arp_tables.c#L1784">1784</a>         void *loc_cpu_entry;
<a name="L1785" href="source/net/ipv4/netfilter/arp_tables.c#L1785">1785</a>         struct <a href="ident?i=xt_table">xt_table</a> *new_table;
<a name="L1786" href="source/net/ipv4/netfilter/arp_tables.c#L1786">1786</a> 
<a name="L1787" href="source/net/ipv4/netfilter/arp_tables.c#L1787">1787</a>         newinfo = <a href="ident?i=xt_alloc_table_info">xt_alloc_table_info</a>(repl-&gt;<a href="ident?i=size">size</a>);
<a name="L1788" href="source/net/ipv4/netfilter/arp_tables.c#L1788">1788</a>         if (!newinfo) {
<a name="L1789" href="source/net/ipv4/netfilter/arp_tables.c#L1789">1789</a>                 <a href="ident?i=ret">ret</a> = -<a href="ident?i=ENOMEM">ENOMEM</a>;
<a name="L1790" href="source/net/ipv4/netfilter/arp_tables.c#L1790">1790</a>                 goto <a href="ident?i=out">out</a>;
<a name="L1791" href="source/net/ipv4/netfilter/arp_tables.c#L1791">1791</a>         }
<a name="L1792" href="source/net/ipv4/netfilter/arp_tables.c#L1792">1792</a> 
<a name="L1793" href="source/net/ipv4/netfilter/arp_tables.c#L1793">1793</a>         <b><i>/* choose the copy on our node/cpu */</i></b>
<a name="L1794" href="source/net/ipv4/netfilter/arp_tables.c#L1794">1794</a>         loc_cpu_entry = newinfo-&gt;<a href="ident?i=entries">entries</a>[<a href="ident?i=raw_smp_processor_id">raw_smp_processor_id</a>()];
<a name="L1795" href="source/net/ipv4/netfilter/arp_tables.c#L1795">1795</a>         <a href="ident?i=memcpy">memcpy</a>(loc_cpu_entry, repl-&gt;<a href="ident?i=entries">entries</a>, repl-&gt;<a href="ident?i=size">size</a>);
<a name="L1796" href="source/net/ipv4/netfilter/arp_tables.c#L1796">1796</a> 
<a name="L1797" href="source/net/ipv4/netfilter/arp_tables.c#L1797">1797</a>         <a href="ident?i=ret">ret</a> = <a href="ident?i=translate_table">translate_table</a>(newinfo, loc_cpu_entry, repl);
<a name="L1798" href="source/net/ipv4/netfilter/arp_tables.c#L1798">1798</a>         <a href="ident?i=duprintf">duprintf</a>(<i>"arpt_register_table: translate table gives %d\n"</i>, <a href="ident?i=ret">ret</a>);
<a name="L1799" href="source/net/ipv4/netfilter/arp_tables.c#L1799">1799</a>         if (<a href="ident?i=ret">ret</a> != 0)
<a name="L1800" href="source/net/ipv4/netfilter/arp_tables.c#L1800">1800</a>                 goto out_free;
<a name="L1801" href="source/net/ipv4/netfilter/arp_tables.c#L1801">1801</a> 
<a name="L1802" href="source/net/ipv4/netfilter/arp_tables.c#L1802">1802</a>         new_table = <a href="ident?i=xt_register_table">xt_register_table</a>(<a href="ident?i=net">net</a>, <a href="ident?i=table">table</a>, &amp;<a href="ident?i=bootstrap">bootstrap</a>, newinfo);
<a name="L1803" href="source/net/ipv4/netfilter/arp_tables.c#L1803">1803</a>         if (<a href="ident?i=IS_ERR">IS_ERR</a>(new_table)) {
<a name="L1804" href="source/net/ipv4/netfilter/arp_tables.c#L1804">1804</a>                 <a href="ident?i=ret">ret</a> = <a href="ident?i=PTR_ERR">PTR_ERR</a>(new_table);
<a name="L1805" href="source/net/ipv4/netfilter/arp_tables.c#L1805">1805</a>                 goto out_free;
<a name="L1806" href="source/net/ipv4/netfilter/arp_tables.c#L1806">1806</a>         }
<a name="L1807" href="source/net/ipv4/netfilter/arp_tables.c#L1807">1807</a>         return new_table;
<a name="L1808" href="source/net/ipv4/netfilter/arp_tables.c#L1808">1808</a> 
<a name="L1809" href="source/net/ipv4/netfilter/arp_tables.c#L1809">1809</a> out_free:
<a name="L1810" href="source/net/ipv4/netfilter/arp_tables.c#L1810">1810</a>         <a href="ident?i=xt_free_table_info">xt_free_table_info</a>(newinfo);
<a name="L1811" href="source/net/ipv4/netfilter/arp_tables.c#L1811">1811</a> <a href="ident?i=out">out</a>:
<a name="L1812" href="source/net/ipv4/netfilter/arp_tables.c#L1812">1812</a>         return <a href="ident?i=ERR_PTR">ERR_PTR</a>(<a href="ident?i=ret">ret</a>);
<a name="L1813" href="source/net/ipv4/netfilter/arp_tables.c#L1813">1813</a> }
<a name="L1814" href="source/net/ipv4/netfilter/arp_tables.c#L1814">1814</a> 
<a name="L1815" href="source/net/ipv4/netfilter/arp_tables.c#L1815">1815</a> void <a href="ident?i=arpt_unregister_table">arpt_unregister_table</a>(struct <a href="ident?i=xt_table">xt_table</a> *<a href="ident?i=table">table</a>)
<a name="L1816" href="source/net/ipv4/netfilter/arp_tables.c#L1816">1816</a> {
<a name="L1817" href="source/net/ipv4/netfilter/arp_tables.c#L1817">1817</a>         struct <a href="ident?i=xt_table_info">xt_table_info</a> *<a href="ident?i=private">private</a>;
<a name="L1818" href="source/net/ipv4/netfilter/arp_tables.c#L1818">1818</a>         void *loc_cpu_entry;
<a name="L1819" href="source/net/ipv4/netfilter/arp_tables.c#L1819">1819</a>         struct <a href="ident?i=module">module</a> *table_owner = <a href="ident?i=table">table</a>-&gt;<a href="ident?i=me">me</a>;
<a name="L1820" href="source/net/ipv4/netfilter/arp_tables.c#L1820">1820</a>         struct <a href="ident?i=arpt_entry">arpt_entry</a> *iter;
<a name="L1821" href="source/net/ipv4/netfilter/arp_tables.c#L1821">1821</a> 
<a name="L1822" href="source/net/ipv4/netfilter/arp_tables.c#L1822">1822</a>         <a href="ident?i=private">private</a> = <a href="ident?i=xt_unregister_table">xt_unregister_table</a>(<a href="ident?i=table">table</a>);
<a name="L1823" href="source/net/ipv4/netfilter/arp_tables.c#L1823">1823</a> 
<a name="L1824" href="source/net/ipv4/netfilter/arp_tables.c#L1824">1824</a>         <b><i>/* Decrease module usage counts and free resources */</i></b>
<a name="L1825" href="source/net/ipv4/netfilter/arp_tables.c#L1825">1825</a>         loc_cpu_entry = <a href="ident?i=private">private</a>-&gt;<a href="ident?i=entries">entries</a>[<a href="ident?i=raw_smp_processor_id">raw_smp_processor_id</a>()];
<a name="L1826" href="source/net/ipv4/netfilter/arp_tables.c#L1826">1826</a>         <a href="ident?i=xt_entry_foreach">xt_entry_foreach</a>(iter, loc_cpu_entry, <a href="ident?i=private">private</a>-&gt;<a href="ident?i=size">size</a>)
<a name="L1827" href="source/net/ipv4/netfilter/arp_tables.c#L1827">1827</a>                 <a href="ident?i=cleanup_entry">cleanup_entry</a>(iter);
<a name="L1828" href="source/net/ipv4/netfilter/arp_tables.c#L1828">1828</a>         if (<a href="ident?i=private">private</a>-&gt;<a href="ident?i=number">number</a> &gt; <a href="ident?i=private">private</a>-&gt;initial_entries)
<a name="L1829" href="source/net/ipv4/netfilter/arp_tables.c#L1829">1829</a>                 <a href="ident?i=module_put">module_put</a>(table_owner);
<a name="L1830" href="source/net/ipv4/netfilter/arp_tables.c#L1830">1830</a>         <a href="ident?i=xt_free_table_info">xt_free_table_info</a>(<a href="ident?i=private">private</a>);
<a name="L1831" href="source/net/ipv4/netfilter/arp_tables.c#L1831">1831</a> }
<a name="L1832" href="source/net/ipv4/netfilter/arp_tables.c#L1832">1832</a> 
<a name="L1833" href="source/net/ipv4/netfilter/arp_tables.c#L1833">1833</a> <b><i>/* The built-in targets: standard (NULL) and error. */</i></b>
<a name="L1834" href="source/net/ipv4/netfilter/arp_tables.c#L1834">1834</a> static struct <a href="ident?i=xt_target">xt_target</a> arpt_builtin_tg[] <a href="ident?i=__read_mostly">__read_mostly</a> = {
<a name="L1835" href="source/net/ipv4/netfilter/arp_tables.c#L1835">1835</a>         {
<a name="L1836" href="source/net/ipv4/netfilter/arp_tables.c#L1836">1836</a>                 .<a href="ident?i=name">name</a>             = <a href="ident?i=XT_STANDARD_TARGET">XT_STANDARD_TARGET</a>,
<a name="L1837" href="source/net/ipv4/netfilter/arp_tables.c#L1837">1837</a>                 .targetsize       = sizeof(int),
<a name="L1838" href="source/net/ipv4/netfilter/arp_tables.c#L1838">1838</a>                 .<a href="ident?i=family">family</a>           = NFPROTO_ARP,
<a name="L1839" href="source/net/ipv4/netfilter/arp_tables.c#L1839">1839</a> #ifdef CONFIG_COMPAT
<a name="L1840" href="source/net/ipv4/netfilter/arp_tables.c#L1840">1840</a>                 .compatsize       = sizeof(<a href="ident?i=compat_int_t">compat_int_t</a>),
<a name="L1841" href="source/net/ipv4/netfilter/arp_tables.c#L1841">1841</a>                 .compat_from_user = <a href="ident?i=compat_standard_from_user">compat_standard_from_user</a>,
<a name="L1842" href="source/net/ipv4/netfilter/arp_tables.c#L1842">1842</a>                 .compat_to_user   = <a href="ident?i=compat_standard_to_user">compat_standard_to_user</a>,
<a name="L1843" href="source/net/ipv4/netfilter/arp_tables.c#L1843">1843</a> #endif
<a name="L1844" href="source/net/ipv4/netfilter/arp_tables.c#L1844">1844</a>         },
<a name="L1845" href="source/net/ipv4/netfilter/arp_tables.c#L1845">1845</a>         {
<a name="L1846" href="source/net/ipv4/netfilter/arp_tables.c#L1846">1846</a>                 .<a href="ident?i=name">name</a>             = <a href="ident?i=XT_ERROR_TARGET">XT_ERROR_TARGET</a>,
<a name="L1847" href="source/net/ipv4/netfilter/arp_tables.c#L1847">1847</a>                 .<a href="ident?i=target">target</a>           = <a href="ident?i=arpt_error">arpt_error</a>,
<a name="L1848" href="source/net/ipv4/netfilter/arp_tables.c#L1848">1848</a>                 .targetsize       = <a href="ident?i=XT_FUNCTION_MAXNAMELEN">XT_FUNCTION_MAXNAMELEN</a>,
<a name="L1849" href="source/net/ipv4/netfilter/arp_tables.c#L1849">1849</a>                 .<a href="ident?i=family">family</a>           = NFPROTO_ARP,
<a name="L1850" href="source/net/ipv4/netfilter/arp_tables.c#L1850">1850</a>         },
<a name="L1851" href="source/net/ipv4/netfilter/arp_tables.c#L1851">1851</a> };
<a name="L1852" href="source/net/ipv4/netfilter/arp_tables.c#L1852">1852</a> 
<a name="L1853" href="source/net/ipv4/netfilter/arp_tables.c#L1853">1853</a> static struct <a href="ident?i=nf_sockopt_ops">nf_sockopt_ops</a> <a href="ident?i=arpt_sockopts">arpt_sockopts</a> = {
<a name="L1854" href="source/net/ipv4/netfilter/arp_tables.c#L1854">1854</a>         .<a href="ident?i=pf">pf</a>             = <a href="ident?i=PF_INET">PF_INET</a>,
<a name="L1855" href="source/net/ipv4/netfilter/arp_tables.c#L1855">1855</a>         .set_optmin     = <a href="ident?i=ARPT_BASE_CTL">ARPT_BASE_CTL</a>,
<a name="L1856" href="source/net/ipv4/netfilter/arp_tables.c#L1856">1856</a>         .set_optmax     = <a href="ident?i=ARPT_SO_SET_MAX">ARPT_SO_SET_MAX</a>+1,
<a name="L1857" href="source/net/ipv4/netfilter/arp_tables.c#L1857">1857</a>         .<a href="ident?i=set">set</a>            = <a href="ident?i=do_arpt_set_ctl">do_arpt_set_ctl</a>,
<a name="L1858" href="source/net/ipv4/netfilter/arp_tables.c#L1858">1858</a> #ifdef CONFIG_COMPAT
<a name="L1859" href="source/net/ipv4/netfilter/arp_tables.c#L1859">1859</a>         .compat_set     = <a href="ident?i=compat_do_arpt_set_ctl">compat_do_arpt_set_ctl</a>,
<a name="L1860" href="source/net/ipv4/netfilter/arp_tables.c#L1860">1860</a> #endif
<a name="L1861" href="source/net/ipv4/netfilter/arp_tables.c#L1861">1861</a>         .get_optmin     = <a href="ident?i=ARPT_BASE_CTL">ARPT_BASE_CTL</a>,
<a name="L1862" href="source/net/ipv4/netfilter/arp_tables.c#L1862">1862</a>         .get_optmax     = <a href="ident?i=ARPT_SO_GET_MAX">ARPT_SO_GET_MAX</a>+1,
<a name="L1863" href="source/net/ipv4/netfilter/arp_tables.c#L1863">1863</a>         .<a href="ident?i=get">get</a>            = <a href="ident?i=do_arpt_get_ctl">do_arpt_get_ctl</a>,
<a name="L1864" href="source/net/ipv4/netfilter/arp_tables.c#L1864">1864</a> #ifdef CONFIG_COMPAT
<a name="L1865" href="source/net/ipv4/netfilter/arp_tables.c#L1865">1865</a>         .compat_get     = <a href="ident?i=compat_do_arpt_get_ctl">compat_do_arpt_get_ctl</a>,
<a name="L1866" href="source/net/ipv4/netfilter/arp_tables.c#L1866">1866</a> #endif
<a name="L1867" href="source/net/ipv4/netfilter/arp_tables.c#L1867">1867</a>         .owner          = <a href="ident?i=THIS_MODULE">THIS_MODULE</a>,
<a name="L1868" href="source/net/ipv4/netfilter/arp_tables.c#L1868">1868</a> };
<a name="L1869" href="source/net/ipv4/netfilter/arp_tables.c#L1869">1869</a> 
<a name="L1870" href="source/net/ipv4/netfilter/arp_tables.c#L1870">1870</a> static int <a href="ident?i=__net_init">__net_init</a> <a href="ident?i=arp_tables_net_init">arp_tables_net_init</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>)
<a name="L1871" href="source/net/ipv4/netfilter/arp_tables.c#L1871">1871</a> {
<a name="L1872" href="source/net/ipv4/netfilter/arp_tables.c#L1872">1872</a>         return <a href="ident?i=xt_proto_init">xt_proto_init</a>(<a href="ident?i=net">net</a>, NFPROTO_ARP);
<a name="L1873" href="source/net/ipv4/netfilter/arp_tables.c#L1873">1873</a> }
<a name="L1874" href="source/net/ipv4/netfilter/arp_tables.c#L1874">1874</a> 
<a name="L1875" href="source/net/ipv4/netfilter/arp_tables.c#L1875">1875</a> static void <a href="ident?i=__net_exit">__net_exit</a> <a href="ident?i=arp_tables_net_exit">arp_tables_net_exit</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>)
<a name="L1876" href="source/net/ipv4/netfilter/arp_tables.c#L1876">1876</a> {
<a name="L1877" href="source/net/ipv4/netfilter/arp_tables.c#L1877">1877</a>         <a href="ident?i=xt_proto_fini">xt_proto_fini</a>(<a href="ident?i=net">net</a>, NFPROTO_ARP);
<a name="L1878" href="source/net/ipv4/netfilter/arp_tables.c#L1878">1878</a> }
<a name="L1879" href="source/net/ipv4/netfilter/arp_tables.c#L1879">1879</a> 
<a name="L1880" href="source/net/ipv4/netfilter/arp_tables.c#L1880">1880</a> static struct <a href="ident?i=pernet_operations">pernet_operations</a> <a href="ident?i=arp_tables_net_ops">arp_tables_net_ops</a> = {
<a name="L1881" href="source/net/ipv4/netfilter/arp_tables.c#L1881">1881</a>         .<a href="ident?i=init">init</a> = <a href="ident?i=arp_tables_net_init">arp_tables_net_init</a>,
<a name="L1882" href="source/net/ipv4/netfilter/arp_tables.c#L1882">1882</a>         .<a href="ident?i=exit">exit</a> = <a href="ident?i=arp_tables_net_exit">arp_tables_net_exit</a>,
<a name="L1883" href="source/net/ipv4/netfilter/arp_tables.c#L1883">1883</a> };
<a name="L1884" href="source/net/ipv4/netfilter/arp_tables.c#L1884">1884</a> 
<a name="L1885" href="source/net/ipv4/netfilter/arp_tables.c#L1885">1885</a> static int <a href="ident?i=__init">__init</a> <a href="ident?i=arp_tables_init">arp_tables_init</a>(void)
<a name="L1886" href="source/net/ipv4/netfilter/arp_tables.c#L1886">1886</a> {
<a name="L1887" href="source/net/ipv4/netfilter/arp_tables.c#L1887">1887</a>         int <a href="ident?i=ret">ret</a>;
<a name="L1888" href="source/net/ipv4/netfilter/arp_tables.c#L1888">1888</a> 
<a name="L1889" href="source/net/ipv4/netfilter/arp_tables.c#L1889">1889</a>         <a href="ident?i=ret">ret</a> = <a href="ident?i=register_pernet_subsys">register_pernet_subsys</a>(&amp;<a href="ident?i=arp_tables_net_ops">arp_tables_net_ops</a>);
<a name="L1890" href="source/net/ipv4/netfilter/arp_tables.c#L1890">1890</a>         if (<a href="ident?i=ret">ret</a> &lt; 0)
<a name="L1891" href="source/net/ipv4/netfilter/arp_tables.c#L1891">1891</a>                 goto err1;
<a name="L1892" href="source/net/ipv4/netfilter/arp_tables.c#L1892">1892</a> 
<a name="L1893" href="source/net/ipv4/netfilter/arp_tables.c#L1893">1893</a>         <b><i>/* No one else will be downing sem now, so we won't sleep */</i></b>
<a name="L1894" href="source/net/ipv4/netfilter/arp_tables.c#L1894">1894</a>         <a href="ident?i=ret">ret</a> = <a href="ident?i=xt_register_targets">xt_register_targets</a>(arpt_builtin_tg, <a href="ident?i=ARRAY_SIZE">ARRAY_SIZE</a>(arpt_builtin_tg));
<a name="L1895" href="source/net/ipv4/netfilter/arp_tables.c#L1895">1895</a>         if (<a href="ident?i=ret">ret</a> &lt; 0)
<a name="L1896" href="source/net/ipv4/netfilter/arp_tables.c#L1896">1896</a>                 goto err2;
<a name="L1897" href="source/net/ipv4/netfilter/arp_tables.c#L1897">1897</a> 
<a name="L1898" href="source/net/ipv4/netfilter/arp_tables.c#L1898">1898</a>         <b><i>/* Register setsockopt */</i></b>
<a name="L1899" href="source/net/ipv4/netfilter/arp_tables.c#L1899">1899</a>         <a href="ident?i=ret">ret</a> = <a href="ident?i=nf_register_sockopt">nf_register_sockopt</a>(&amp;<a href="ident?i=arpt_sockopts">arpt_sockopts</a>);
<a name="L1900" href="source/net/ipv4/netfilter/arp_tables.c#L1900">1900</a>         if (<a href="ident?i=ret">ret</a> &lt; 0)
<a name="L1901" href="source/net/ipv4/netfilter/arp_tables.c#L1901">1901</a>                 goto err4;
<a name="L1902" href="source/net/ipv4/netfilter/arp_tables.c#L1902">1902</a> 
<a name="L1903" href="source/net/ipv4/netfilter/arp_tables.c#L1903">1903</a>         <a href="ident?i=printk">printk</a>(<a href="ident?i=KERN_INFO">KERN_INFO</a> <i>"arp_tables: (C) 2002 David S. Miller\n"</i>);
<a name="L1904" href="source/net/ipv4/netfilter/arp_tables.c#L1904">1904</a>         return 0;
<a name="L1905" href="source/net/ipv4/netfilter/arp_tables.c#L1905">1905</a> 
<a name="L1906" href="source/net/ipv4/netfilter/arp_tables.c#L1906">1906</a> err4:
<a name="L1907" href="source/net/ipv4/netfilter/arp_tables.c#L1907">1907</a>         <a href="ident?i=xt_unregister_targets">xt_unregister_targets</a>(arpt_builtin_tg, <a href="ident?i=ARRAY_SIZE">ARRAY_SIZE</a>(arpt_builtin_tg));
<a name="L1908" href="source/net/ipv4/netfilter/arp_tables.c#L1908">1908</a> err2:
<a name="L1909" href="source/net/ipv4/netfilter/arp_tables.c#L1909">1909</a>         <a href="ident?i=unregister_pernet_subsys">unregister_pernet_subsys</a>(&amp;<a href="ident?i=arp_tables_net_ops">arp_tables_net_ops</a>);
<a name="L1910" href="source/net/ipv4/netfilter/arp_tables.c#L1910">1910</a> err1:
<a name="L1911" href="source/net/ipv4/netfilter/arp_tables.c#L1911">1911</a>         return <a href="ident?i=ret">ret</a>;
<a name="L1912" href="source/net/ipv4/netfilter/arp_tables.c#L1912">1912</a> }
<a name="L1913" href="source/net/ipv4/netfilter/arp_tables.c#L1913">1913</a> 
<a name="L1914" href="source/net/ipv4/netfilter/arp_tables.c#L1914">1914</a> static void <a href="ident?i=__exit">__exit</a> <a href="ident?i=arp_tables_fini">arp_tables_fini</a>(void)
<a name="L1915" href="source/net/ipv4/netfilter/arp_tables.c#L1915">1915</a> {
<a name="L1916" href="source/net/ipv4/netfilter/arp_tables.c#L1916">1916</a>         <a href="ident?i=nf_unregister_sockopt">nf_unregister_sockopt</a>(&amp;<a href="ident?i=arpt_sockopts">arpt_sockopts</a>);
<a name="L1917" href="source/net/ipv4/netfilter/arp_tables.c#L1917">1917</a>         <a href="ident?i=xt_unregister_targets">xt_unregister_targets</a>(arpt_builtin_tg, <a href="ident?i=ARRAY_SIZE">ARRAY_SIZE</a>(arpt_builtin_tg));
<a name="L1918" href="source/net/ipv4/netfilter/arp_tables.c#L1918">1918</a>         <a href="ident?i=unregister_pernet_subsys">unregister_pernet_subsys</a>(&amp;<a href="ident?i=arp_tables_net_ops">arp_tables_net_ops</a>);
<a name="L1919" href="source/net/ipv4/netfilter/arp_tables.c#L1919">1919</a> }
<a name="L1920" href="source/net/ipv4/netfilter/arp_tables.c#L1920">1920</a> 
<a name="L1921" href="source/net/ipv4/netfilter/arp_tables.c#L1921">1921</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=arpt_register_table">arpt_register_table</a>);
<a name="L1922" href="source/net/ipv4/netfilter/arp_tables.c#L1922">1922</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=arpt_unregister_table">arpt_unregister_table</a>);
<a name="L1923" href="source/net/ipv4/netfilter/arp_tables.c#L1923">1923</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=arpt_do_table">arpt_do_table</a>);
<a name="L1924" href="source/net/ipv4/netfilter/arp_tables.c#L1924">1924</a> 
<a name="L1925" href="source/net/ipv4/netfilter/arp_tables.c#L1925">1925</a> <a href="ident?i=module_init">module_init</a>(<a href="ident?i=arp_tables_init">arp_tables_init</a>);
<a name="L1926" href="source/net/ipv4/netfilter/arp_tables.c#L1926">1926</a> <a href="ident?i=module_exit">module_exit</a>(<a href="ident?i=arp_tables_fini">arp_tables_fini</a>);
<a name="L1927" href="source/net/ipv4/netfilter/arp_tables.c#L1927">1927</a> </pre></div><p>
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
