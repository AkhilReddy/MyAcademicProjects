<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title>Linux/net/ipv4/netfilter/ipt_ah.c - Linux Cross Reference - Free Electrons</title>
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
		 &nbsp;&bull;&nbsp;<b><i>source navigation</i></b> &nbsp;&bull;&nbsp;<a href="diff/net/ipv4/netfilter/ipt_ah.c">diff markup</a> &nbsp;&bull;&nbsp;<a href="ident">identifier search</a> &nbsp;&bull;&nbsp;<a href="search">freetext search</a> &nbsp;&bull;&nbsp;
		</p>
	</div>
</div>

<div id="topbar">
  
  <p>Version: &nbsp;<a href="source/net/ipv4/netfilter/ipt_ah.c?v=2.0.40">2.0.40</a>&nbsp;<a href="source/net/ipv4/netfilter/ipt_ah.c?v=2.2.26">2.2.26</a>&nbsp;<a href="source/net/ipv4/netfilter/ipt_ah.c?v=2.4.37">2.4.37</a>&nbsp;<a href="source/net/ipv4/netfilter/ipt_ah.c?v=3.5">3.5</a>&nbsp;<a href="source/net/ipv4/netfilter/ipt_ah.c?v=3.6">3.6</a>&nbsp;<a href="source/net/ipv4/netfilter/ipt_ah.c?v=3.7">3.7</a>&nbsp;<a href="source/net/ipv4/netfilter/ipt_ah.c?v=3.8">3.8</a>&nbsp;<a href="source/net/ipv4/netfilter/ipt_ah.c?v=3.9">3.9</a>&nbsp;<a href="source/net/ipv4/netfilter/ipt_ah.c?v=3.10">3.10</a>&nbsp;<a href="source/net/ipv4/netfilter/ipt_ah.c?v=3.11">3.11</a>&nbsp;<a href="source/net/ipv4/netfilter/ipt_ah.c?v=3.12">3.12</a>&nbsp;<a href="source/net/ipv4/netfilter/ipt_ah.c?v=3.13">3.13</a>&nbsp;<a href="source/net/ipv4/netfilter/ipt_ah.c?v=3.14">3.14</a>&nbsp;<a href="source/net/ipv4/netfilter/ipt_ah.c?v=3.15">3.15</a>&nbsp;<a href="source/net/ipv4/netfilter/ipt_ah.c?v=3.16">3.16</a>&nbsp;<a href="source/net/ipv4/netfilter/ipt_ah.c?v=3.17">3.17</a>&nbsp;<a href="source/net/ipv4/netfilter/ipt_ah.c?v=3.18">3.18</a>&nbsp;<a href="source/net/ipv4/netfilter/ipt_ah.c?v=3.19">3.19</a>&nbsp;<a href="source/net/ipv4/netfilter/ipt_ah.c?v=4.0">4.0</a>&nbsp;<b><i>4.1</i></b></p>
  
</div>

<h1><a href="source/">Linux</a>/<a href="source/net/">net</a>/<a href="source/net/ipv4/">ipv4</a>/<a href="source/net/ipv4/netfilter/">netfilter</a>/<a href="source/net/ipv4/netfilter/ipt_ah.c">ipt_ah.c</a></h1>
<div id="lxrcode"><pre>  <a name="L1" href="source/net/ipv4/netfilter/ipt_ah.c#L1">1</a> <b><i>/* Kernel module to match AH parameters. */</i></b>
  <a name="L2" href="source/net/ipv4/netfilter/ipt_ah.c#L2">2</a> <b><i>/* (C) 1999-2000 Yon Uriarte &lt;yon@astaro.de&gt;</i></b>
  <a name="L3" href="source/net/ipv4/netfilter/ipt_ah.c#L3">3</a> <b><i> *</i></b>
  <a name="L4" href="source/net/ipv4/netfilter/ipt_ah.c#L4">4</a> <b><i> * This program is free software; you can redistribute it and/or modify</i></b>
  <a name="L5" href="source/net/ipv4/netfilter/ipt_ah.c#L5">5</a> <b><i> * it under the terms of the GNU General Public License version 2 as</i></b>
  <a name="L6" href="source/net/ipv4/netfilter/ipt_ah.c#L6">6</a> <b><i> * published by the Free Software Foundation.</i></b>
  <a name="L7" href="source/net/ipv4/netfilter/ipt_ah.c#L7">7</a> <b><i> */</i></b>
  <a name="L8" href="source/net/ipv4/netfilter/ipt_ah.c#L8">8</a> #define <a href="ident?i=pr_fmt">pr_fmt</a>(<a href="ident?i=fmt">fmt</a>) KBUILD_MODNAME <i>": "</i> <a href="ident?i=fmt">fmt</a>
  <a name="L9" href="source/net/ipv4/netfilter/ipt_ah.c#L9">9</a> #include &lt;linux/in.h&gt;
 <a name="L10" href="source/net/ipv4/netfilter/ipt_ah.c#L10">10</a> #include &lt;linux/module.h&gt;
 <a name="L11" href="source/net/ipv4/netfilter/ipt_ah.c#L11">11</a> #include &lt;linux/skbuff.h&gt;
 <a name="L12" href="source/net/ipv4/netfilter/ipt_ah.c#L12">12</a> #include &lt;linux/ip.h&gt;
 <a name="L13" href="source/net/ipv4/netfilter/ipt_ah.c#L13">13</a> 
 <a name="L14" href="source/net/ipv4/netfilter/ipt_ah.c#L14">14</a> #include &lt;linux/netfilter_ipv4/ipt_ah.h&gt;
 <a name="L15" href="source/net/ipv4/netfilter/ipt_ah.c#L15">15</a> #include &lt;linux/netfilter/x_tables.h&gt;
 <a name="L16" href="source/net/ipv4/netfilter/ipt_ah.c#L16">16</a> 
 <a name="L17" href="source/net/ipv4/netfilter/ipt_ah.c#L17">17</a> <a href="ident?i=MODULE_LICENSE">MODULE_LICENSE</a>(<i>"GPL"</i>);
 <a name="L18" href="source/net/ipv4/netfilter/ipt_ah.c#L18">18</a> <a href="ident?i=MODULE_AUTHOR">MODULE_AUTHOR</a>(<i>"Yon Uriarte &lt;yon@astaro.de&gt;"</i>);
 <a name="L19" href="source/net/ipv4/netfilter/ipt_ah.c#L19">19</a> <a href="ident?i=MODULE_DESCRIPTION">MODULE_DESCRIPTION</a>(<i>"Xtables: IPv4 IPsec-AH SPI match"</i>);
 <a name="L20" href="source/net/ipv4/netfilter/ipt_ah.c#L20">20</a> 
 <a name="L21" href="source/net/ipv4/netfilter/ipt_ah.c#L21">21</a> <b><i>/* Returns 1 if the spi is matched by the range, 0 otherwise */</i></b>
 <a name="L22" href="source/net/ipv4/netfilter/ipt_ah.c#L22">22</a> static inline <a href="ident?i=bool">bool</a>
 <a name="L23" href="source/net/ipv4/netfilter/ipt_ah.c#L23">23</a> <a href="ident?i=spi_match">spi_match</a>(<a href="ident?i=u_int32_t">u_int32_t</a> <a href="ident?i=min">min</a>, <a href="ident?i=u_int32_t">u_int32_t</a> <a href="ident?i=max">max</a>, <a href="ident?i=u_int32_t">u_int32_t</a> <a href="ident?i=spi">spi</a>, <a href="ident?i=bool">bool</a> <a href="ident?i=invert">invert</a>)
 <a name="L24" href="source/net/ipv4/netfilter/ipt_ah.c#L24">24</a> {
 <a name="L25" href="source/net/ipv4/netfilter/ipt_ah.c#L25">25</a>         <a href="ident?i=bool">bool</a> <a href="ident?i=r">r</a>;
 <a name="L26" href="source/net/ipv4/netfilter/ipt_ah.c#L26">26</a>         <a href="ident?i=pr_debug">pr_debug</a>(<i>"spi_match:%c 0x%x &lt;= 0x%x &lt;= 0x%x\n"</i>,
 <a name="L27" href="source/net/ipv4/netfilter/ipt_ah.c#L27">27</a>                  <a href="ident?i=invert">invert</a> ? <i>'!'</i> : <i>' '</i>, <a href="ident?i=min">min</a>, <a href="ident?i=spi">spi</a>, <a href="ident?i=max">max</a>);
 <a name="L28" href="source/net/ipv4/netfilter/ipt_ah.c#L28">28</a>         <a href="ident?i=r">r</a>=(<a href="ident?i=spi">spi</a> &gt;= <a href="ident?i=min">min</a> &amp;&amp; <a href="ident?i=spi">spi</a> &lt;= <a href="ident?i=max">max</a>) ^ <a href="ident?i=invert">invert</a>;
 <a name="L29" href="source/net/ipv4/netfilter/ipt_ah.c#L29">29</a>         <a href="ident?i=pr_debug">pr_debug</a>(<i>" result %s\n"</i>, <a href="ident?i=r">r</a> ? <i>"PASS"</i> : <i>"FAILED"</i>);
 <a name="L30" href="source/net/ipv4/netfilter/ipt_ah.c#L30">30</a>         return <a href="ident?i=r">r</a>;
 <a name="L31" href="source/net/ipv4/netfilter/ipt_ah.c#L31">31</a> }
 <a name="L32" href="source/net/ipv4/netfilter/ipt_ah.c#L32">32</a> 
 <a name="L33" href="source/net/ipv4/netfilter/ipt_ah.c#L33">33</a> static <a href="ident?i=bool">bool</a> <a href="ident?i=ah_mt">ah_mt</a>(const struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, struct <a href="ident?i=xt_action_param">xt_action_param</a> *<a href="ident?i=par">par</a>)
 <a name="L34" href="source/net/ipv4/netfilter/ipt_ah.c#L34">34</a> {
 <a name="L35" href="source/net/ipv4/netfilter/ipt_ah.c#L35">35</a>         struct <a href="ident?i=ip_auth_hdr">ip_auth_hdr</a> _ahdr;
 <a name="L36" href="source/net/ipv4/netfilter/ipt_ah.c#L36">36</a>         const struct <a href="ident?i=ip_auth_hdr">ip_auth_hdr</a> *ah;
 <a name="L37" href="source/net/ipv4/netfilter/ipt_ah.c#L37">37</a>         const struct <a href="ident?i=ipt_ah">ipt_ah</a> *ahinfo = <a href="ident?i=par">par</a>-&gt;matchinfo;
 <a name="L38" href="source/net/ipv4/netfilter/ipt_ah.c#L38">38</a> 
 <a name="L39" href="source/net/ipv4/netfilter/ipt_ah.c#L39">39</a>         <b><i>/* Must not be a fragment. */</i></b>
 <a name="L40" href="source/net/ipv4/netfilter/ipt_ah.c#L40">40</a>         if (<a href="ident?i=par">par</a>-&gt;fragoff != 0)
 <a name="L41" href="source/net/ipv4/netfilter/ipt_ah.c#L41">41</a>                 return <a href="ident?i=false">false</a>;
 <a name="L42" href="source/net/ipv4/netfilter/ipt_ah.c#L42">42</a> 
 <a name="L43" href="source/net/ipv4/netfilter/ipt_ah.c#L43">43</a>         ah = <a href="ident?i=skb_header_pointer">skb_header_pointer</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=par">par</a>-&gt;thoff, sizeof(_ahdr), &amp;_ahdr);
 <a name="L44" href="source/net/ipv4/netfilter/ipt_ah.c#L44">44</a>         if (ah == <a href="ident?i=NULL">NULL</a>) {
 <a name="L45" href="source/net/ipv4/netfilter/ipt_ah.c#L45">45</a>                 <b><i>/* We've been asked to examine this packet, and we</i></b>
 <a name="L46" href="source/net/ipv4/netfilter/ipt_ah.c#L46">46</a> <b><i>                 * can't.  Hence, no choice but to drop.</i></b>
 <a name="L47" href="source/net/ipv4/netfilter/ipt_ah.c#L47">47</a> <b><i>                 */</i></b>
 <a name="L48" href="source/net/ipv4/netfilter/ipt_ah.c#L48">48</a>                 <a href="ident?i=pr_debug">pr_debug</a>(<i>"Dropping evil AH tinygram.\n"</i>);
 <a name="L49" href="source/net/ipv4/netfilter/ipt_ah.c#L49">49</a>                 <a href="ident?i=par">par</a>-&gt;hotdrop = <a href="ident?i=true">true</a>;
 <a name="L50" href="source/net/ipv4/netfilter/ipt_ah.c#L50">50</a>                 return 0;
 <a name="L51" href="source/net/ipv4/netfilter/ipt_ah.c#L51">51</a>         }
 <a name="L52" href="source/net/ipv4/netfilter/ipt_ah.c#L52">52</a> 
 <a name="L53" href="source/net/ipv4/netfilter/ipt_ah.c#L53">53</a>         return <a href="ident?i=spi_match">spi_match</a>(ahinfo-&gt;spis[0], ahinfo-&gt;spis[1],
 <a name="L54" href="source/net/ipv4/netfilter/ipt_ah.c#L54">54</a>                          <a href="ident?i=ntohl">ntohl</a>(ah-&gt;<a href="ident?i=spi">spi</a>),
 <a name="L55" href="source/net/ipv4/netfilter/ipt_ah.c#L55">55</a>                          !!(ahinfo-&gt;invflags &amp; <a href="ident?i=IPT_AH_INV_SPI">IPT_AH_INV_SPI</a>));
 <a name="L56" href="source/net/ipv4/netfilter/ipt_ah.c#L56">56</a> }
 <a name="L57" href="source/net/ipv4/netfilter/ipt_ah.c#L57">57</a> 
 <a name="L58" href="source/net/ipv4/netfilter/ipt_ah.c#L58">58</a> static int <a href="ident?i=ah_mt_check">ah_mt_check</a>(const struct <a href="ident?i=xt_mtchk_param">xt_mtchk_param</a> *<a href="ident?i=par">par</a>)
 <a name="L59" href="source/net/ipv4/netfilter/ipt_ah.c#L59">59</a> {
 <a name="L60" href="source/net/ipv4/netfilter/ipt_ah.c#L60">60</a>         const struct <a href="ident?i=ipt_ah">ipt_ah</a> *ahinfo = <a href="ident?i=par">par</a>-&gt;matchinfo;
 <a name="L61" href="source/net/ipv4/netfilter/ipt_ah.c#L61">61</a> 
 <a name="L62" href="source/net/ipv4/netfilter/ipt_ah.c#L62">62</a>         <b><i>/* Must specify no unknown invflags */</i></b>
 <a name="L63" href="source/net/ipv4/netfilter/ipt_ah.c#L63">63</a>         if (ahinfo-&gt;invflags &amp; ~IPT_AH_INV_MASK) {
 <a name="L64" href="source/net/ipv4/netfilter/ipt_ah.c#L64">64</a>                 <a href="ident?i=pr_debug">pr_debug</a>(<i>"unknown flags %X\n"</i>, ahinfo-&gt;invflags);
 <a name="L65" href="source/net/ipv4/netfilter/ipt_ah.c#L65">65</a>                 return -<a href="ident?i=EINVAL">EINVAL</a>;
 <a name="L66" href="source/net/ipv4/netfilter/ipt_ah.c#L66">66</a>         }
 <a name="L67" href="source/net/ipv4/netfilter/ipt_ah.c#L67">67</a>         return 0;
 <a name="L68" href="source/net/ipv4/netfilter/ipt_ah.c#L68">68</a> }
 <a name="L69" href="source/net/ipv4/netfilter/ipt_ah.c#L69">69</a> 
 <a name="L70" href="source/net/ipv4/netfilter/ipt_ah.c#L70">70</a> static struct <a href="ident?i=xt_match">xt_match</a> ah_mt_reg <a href="ident?i=__read_mostly">__read_mostly</a> = {
 <a name="L71" href="source/net/ipv4/netfilter/ipt_ah.c#L71">71</a>         .<a href="ident?i=name">name</a>           = <i>"ah"</i>,
 <a name="L72" href="source/net/ipv4/netfilter/ipt_ah.c#L72">72</a>         .<a href="ident?i=family">family</a>         = NFPROTO_IPV4,
 <a name="L73" href="source/net/ipv4/netfilter/ipt_ah.c#L73">73</a>         .<a href="ident?i=match">match</a>          = <a href="ident?i=ah_mt">ah_mt</a>,
 <a name="L74" href="source/net/ipv4/netfilter/ipt_ah.c#L74">74</a>         .matchsize      = sizeof(struct <a href="ident?i=ipt_ah">ipt_ah</a>),
 <a name="L75" href="source/net/ipv4/netfilter/ipt_ah.c#L75">75</a>         .<a href="ident?i=proto">proto</a>          = <a href="ident?i=IPPROTO_AH">IPPROTO_AH</a>,
 <a name="L76" href="source/net/ipv4/netfilter/ipt_ah.c#L76">76</a>         .<a href="ident?i=checkentry">checkentry</a>     = <a href="ident?i=ah_mt_check">ah_mt_check</a>,
 <a name="L77" href="source/net/ipv4/netfilter/ipt_ah.c#L77">77</a>         .<a href="ident?i=me">me</a>             = <a href="ident?i=THIS_MODULE">THIS_MODULE</a>,
 <a name="L78" href="source/net/ipv4/netfilter/ipt_ah.c#L78">78</a> };
 <a name="L79" href="source/net/ipv4/netfilter/ipt_ah.c#L79">79</a> 
 <a name="L80" href="source/net/ipv4/netfilter/ipt_ah.c#L80">80</a> static int <a href="ident?i=__init">__init</a> <a href="ident?i=ah_mt_init">ah_mt_init</a>(void)
 <a name="L81" href="source/net/ipv4/netfilter/ipt_ah.c#L81">81</a> {
 <a name="L82" href="source/net/ipv4/netfilter/ipt_ah.c#L82">82</a>         return <a href="ident?i=xt_register_match">xt_register_match</a>(&amp;ah_mt_reg);
 <a name="L83" href="source/net/ipv4/netfilter/ipt_ah.c#L83">83</a> }
 <a name="L84" href="source/net/ipv4/netfilter/ipt_ah.c#L84">84</a> 
 <a name="L85" href="source/net/ipv4/netfilter/ipt_ah.c#L85">85</a> static void <a href="ident?i=__exit">__exit</a> <a href="ident?i=ah_mt_exit">ah_mt_exit</a>(void)
 <a name="L86" href="source/net/ipv4/netfilter/ipt_ah.c#L86">86</a> {
 <a name="L87" href="source/net/ipv4/netfilter/ipt_ah.c#L87">87</a>         <a href="ident?i=xt_unregister_match">xt_unregister_match</a>(&amp;ah_mt_reg);
 <a name="L88" href="source/net/ipv4/netfilter/ipt_ah.c#L88">88</a> }
 <a name="L89" href="source/net/ipv4/netfilter/ipt_ah.c#L89">89</a> 
 <a name="L90" href="source/net/ipv4/netfilter/ipt_ah.c#L90">90</a> <a href="ident?i=module_init">module_init</a>(<a href="ident?i=ah_mt_init">ah_mt_init</a>);
 <a name="L91" href="source/net/ipv4/netfilter/ipt_ah.c#L91">91</a> <a href="ident?i=module_exit">module_exit</a>(<a href="ident?i=ah_mt_exit">ah_mt_exit</a>);
 <a name="L92" href="source/net/ipv4/netfilter/ipt_ah.c#L92">92</a> </pre></div><p>
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
