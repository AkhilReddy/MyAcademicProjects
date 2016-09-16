<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title>Linux/net/ipv4/netfilter/ipt_MASQUERADE.c - Linux Cross Reference - Free Electrons</title>
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
		 &nbsp;&bull;&nbsp;<b><i>source navigation</i></b> &nbsp;&bull;&nbsp;<a href="diff/net/ipv4/netfilter/ipt_MASQUERADE.c">diff markup</a> &nbsp;&bull;&nbsp;<a href="ident">identifier search</a> &nbsp;&bull;&nbsp;<a href="search">freetext search</a> &nbsp;&bull;&nbsp;
		</p>
	</div>
</div>

<div id="topbar">
  
  <p>Version: &nbsp;<a href="source/net/ipv4/netfilter/ipt_MASQUERADE.c?v=2.0.40">2.0.40</a>&nbsp;<a href="source/net/ipv4/netfilter/ipt_MASQUERADE.c?v=2.2.26">2.2.26</a>&nbsp;<a href="source/net/ipv4/netfilter/ipt_MASQUERADE.c?v=2.4.37">2.4.37</a>&nbsp;<a href="source/net/ipv4/netfilter/ipt_MASQUERADE.c?v=3.5">3.5</a>&nbsp;<a href="source/net/ipv4/netfilter/ipt_MASQUERADE.c?v=3.6">3.6</a>&nbsp;<a href="source/net/ipv4/netfilter/ipt_MASQUERADE.c?v=3.7">3.7</a>&nbsp;<a href="source/net/ipv4/netfilter/ipt_MASQUERADE.c?v=3.8">3.8</a>&nbsp;<a href="source/net/ipv4/netfilter/ipt_MASQUERADE.c?v=3.9">3.9</a>&nbsp;<a href="source/net/ipv4/netfilter/ipt_MASQUERADE.c?v=3.10">3.10</a>&nbsp;<a href="source/net/ipv4/netfilter/ipt_MASQUERADE.c?v=3.11">3.11</a>&nbsp;<a href="source/net/ipv4/netfilter/ipt_MASQUERADE.c?v=3.12">3.12</a>&nbsp;<a href="source/net/ipv4/netfilter/ipt_MASQUERADE.c?v=3.13">3.13</a>&nbsp;<a href="source/net/ipv4/netfilter/ipt_MASQUERADE.c?v=3.14">3.14</a>&nbsp;<a href="source/net/ipv4/netfilter/ipt_MASQUERADE.c?v=3.15">3.15</a>&nbsp;<a href="source/net/ipv4/netfilter/ipt_MASQUERADE.c?v=3.16">3.16</a>&nbsp;<a href="source/net/ipv4/netfilter/ipt_MASQUERADE.c?v=3.17">3.17</a>&nbsp;<a href="source/net/ipv4/netfilter/ipt_MASQUERADE.c?v=3.18">3.18</a>&nbsp;<a href="source/net/ipv4/netfilter/ipt_MASQUERADE.c?v=3.19">3.19</a>&nbsp;<a href="source/net/ipv4/netfilter/ipt_MASQUERADE.c?v=4.0">4.0</a>&nbsp;<b><i>4.1</i></b></p>
  
</div>

<h1><a href="source/">Linux</a>/<a href="source/net/">net</a>/<a href="source/net/ipv4/">ipv4</a>/<a href="source/net/ipv4/netfilter/">netfilter</a>/<a href="source/net/ipv4/netfilter/ipt_MASQUERADE.c">ipt_MASQUERADE.c</a></h1>
<div id="lxrcode"><pre>  <a name="L1" href="source/net/ipv4/netfilter/ipt_MASQUERADE.c#L1">1</a> <b><i>/* Masquerade.  Simple mapping which alters range to a local IP address</i></b>
  <a name="L2" href="source/net/ipv4/netfilter/ipt_MASQUERADE.c#L2">2</a> <b><i>   (depending on route). */</i></b>
  <a name="L3" href="source/net/ipv4/netfilter/ipt_MASQUERADE.c#L3">3</a> 
  <a name="L4" href="source/net/ipv4/netfilter/ipt_MASQUERADE.c#L4">4</a> <b><i>/* (C) 1999-2001 Paul `Rusty' Russell</i></b>
  <a name="L5" href="source/net/ipv4/netfilter/ipt_MASQUERADE.c#L5">5</a> <b><i> * (C) 2002-2006 Netfilter Core Team &lt;coreteam@netfilter.org&gt;</i></b>
  <a name="L6" href="source/net/ipv4/netfilter/ipt_MASQUERADE.c#L6">6</a> <b><i> *</i></b>
  <a name="L7" href="source/net/ipv4/netfilter/ipt_MASQUERADE.c#L7">7</a> <b><i> * This program is free software; you can redistribute it and/or modify</i></b>
  <a name="L8" href="source/net/ipv4/netfilter/ipt_MASQUERADE.c#L8">8</a> <b><i> * it under the terms of the GNU General Public License version 2 as</i></b>
  <a name="L9" href="source/net/ipv4/netfilter/ipt_MASQUERADE.c#L9">9</a> <b><i> * published by the Free Software Foundation.</i></b>
 <a name="L10" href="source/net/ipv4/netfilter/ipt_MASQUERADE.c#L10">10</a> <b><i> */</i></b>
 <a name="L11" href="source/net/ipv4/netfilter/ipt_MASQUERADE.c#L11">11</a> #define <a href="ident?i=pr_fmt">pr_fmt</a>(<a href="ident?i=fmt">fmt</a>) KBUILD_MODNAME <i>": "</i> <a href="ident?i=fmt">fmt</a>
 <a name="L12" href="source/net/ipv4/netfilter/ipt_MASQUERADE.c#L12">12</a> #include &lt;linux/types.h&gt;
 <a name="L13" href="source/net/ipv4/netfilter/ipt_MASQUERADE.c#L13">13</a> #include &lt;linux/inetdevice.h&gt;
 <a name="L14" href="source/net/ipv4/netfilter/ipt_MASQUERADE.c#L14">14</a> #include &lt;linux/ip.h&gt;
 <a name="L15" href="source/net/ipv4/netfilter/ipt_MASQUERADE.c#L15">15</a> #include &lt;linux/timer.h&gt;
 <a name="L16" href="source/net/ipv4/netfilter/ipt_MASQUERADE.c#L16">16</a> #include &lt;linux/module.h&gt;
 <a name="L17" href="source/net/ipv4/netfilter/ipt_MASQUERADE.c#L17">17</a> #include &lt;linux/netfilter.h&gt;
 <a name="L18" href="source/net/ipv4/netfilter/ipt_MASQUERADE.c#L18">18</a> #include &lt;net/protocol.h&gt;
 <a name="L19" href="source/net/ipv4/netfilter/ipt_MASQUERADE.c#L19">19</a> #include &lt;net/ip.h&gt;
 <a name="L20" href="source/net/ipv4/netfilter/ipt_MASQUERADE.c#L20">20</a> #include &lt;net/checksum.h&gt;
 <a name="L21" href="source/net/ipv4/netfilter/ipt_MASQUERADE.c#L21">21</a> #include &lt;net/route.h&gt;
 <a name="L22" href="source/net/ipv4/netfilter/ipt_MASQUERADE.c#L22">22</a> #include &lt;linux/netfilter_ipv4.h&gt;
 <a name="L23" href="source/net/ipv4/netfilter/ipt_MASQUERADE.c#L23">23</a> #include &lt;linux/netfilter/x_tables.h&gt;
 <a name="L24" href="source/net/ipv4/netfilter/ipt_MASQUERADE.c#L24">24</a> #include &lt;net/netfilter/nf_nat.h&gt;
 <a name="L25" href="source/net/ipv4/netfilter/ipt_MASQUERADE.c#L25">25</a> #include &lt;net/netfilter/ipv4/nf_nat_masquerade.h&gt;
 <a name="L26" href="source/net/ipv4/netfilter/ipt_MASQUERADE.c#L26">26</a> 
 <a name="L27" href="source/net/ipv4/netfilter/ipt_MASQUERADE.c#L27">27</a> <a href="ident?i=MODULE_LICENSE">MODULE_LICENSE</a>(<i>"GPL"</i>);
 <a name="L28" href="source/net/ipv4/netfilter/ipt_MASQUERADE.c#L28">28</a> <a href="ident?i=MODULE_AUTHOR">MODULE_AUTHOR</a>(<i>"Netfilter Core Team &lt;coreteam@netfilter.org&gt;"</i>);
 <a name="L29" href="source/net/ipv4/netfilter/ipt_MASQUERADE.c#L29">29</a> <a href="ident?i=MODULE_DESCRIPTION">MODULE_DESCRIPTION</a>(<i>"Xtables: automatic-address SNAT"</i>);
 <a name="L30" href="source/net/ipv4/netfilter/ipt_MASQUERADE.c#L30">30</a> 
 <a name="L31" href="source/net/ipv4/netfilter/ipt_MASQUERADE.c#L31">31</a> <b><i>/* FIXME: Multiple targets. --RR */</i></b>
 <a name="L32" href="source/net/ipv4/netfilter/ipt_MASQUERADE.c#L32">32</a> static int <a href="ident?i=masquerade_tg_check">masquerade_tg_check</a>(const struct <a href="ident?i=xt_tgchk_param">xt_tgchk_param</a> *<a href="ident?i=par">par</a>)
 <a name="L33" href="source/net/ipv4/netfilter/ipt_MASQUERADE.c#L33">33</a> {
 <a name="L34" href="source/net/ipv4/netfilter/ipt_MASQUERADE.c#L34">34</a>         const struct <a href="ident?i=nf_nat_ipv4_multi_range_compat">nf_nat_ipv4_multi_range_compat</a> *mr = <a href="ident?i=par">par</a>-&gt;targinfo;
 <a name="L35" href="source/net/ipv4/netfilter/ipt_MASQUERADE.c#L35">35</a> 
 <a name="L36" href="source/net/ipv4/netfilter/ipt_MASQUERADE.c#L36">36</a>         if (mr-&gt;<a href="ident?i=range">range</a>[0].<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=NF_NAT_RANGE_MAP_IPS">NF_NAT_RANGE_MAP_IPS</a>) {
 <a name="L37" href="source/net/ipv4/netfilter/ipt_MASQUERADE.c#L37">37</a>                 <a href="ident?i=pr_debug">pr_debug</a>(<i>"bad MAP_IPS.\n"</i>);
 <a name="L38" href="source/net/ipv4/netfilter/ipt_MASQUERADE.c#L38">38</a>                 return -<a href="ident?i=EINVAL">EINVAL</a>;
 <a name="L39" href="source/net/ipv4/netfilter/ipt_MASQUERADE.c#L39">39</a>         }
 <a name="L40" href="source/net/ipv4/netfilter/ipt_MASQUERADE.c#L40">40</a>         if (mr-&gt;rangesize != 1) {
 <a name="L41" href="source/net/ipv4/netfilter/ipt_MASQUERADE.c#L41">41</a>                 <a href="ident?i=pr_debug">pr_debug</a>(<i>"bad rangesize %u\n"</i>, mr-&gt;rangesize);
 <a name="L42" href="source/net/ipv4/netfilter/ipt_MASQUERADE.c#L42">42</a>                 return -<a href="ident?i=EINVAL">EINVAL</a>;
 <a name="L43" href="source/net/ipv4/netfilter/ipt_MASQUERADE.c#L43">43</a>         }
 <a name="L44" href="source/net/ipv4/netfilter/ipt_MASQUERADE.c#L44">44</a>         return 0;
 <a name="L45" href="source/net/ipv4/netfilter/ipt_MASQUERADE.c#L45">45</a> }
 <a name="L46" href="source/net/ipv4/netfilter/ipt_MASQUERADE.c#L46">46</a> 
 <a name="L47" href="source/net/ipv4/netfilter/ipt_MASQUERADE.c#L47">47</a> static unsigned int
 <a name="L48" href="source/net/ipv4/netfilter/ipt_MASQUERADE.c#L48">48</a> <a href="ident?i=masquerade_tg">masquerade_tg</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, const struct <a href="ident?i=xt_action_param">xt_action_param</a> *<a href="ident?i=par">par</a>)
 <a name="L49" href="source/net/ipv4/netfilter/ipt_MASQUERADE.c#L49">49</a> {
 <a name="L50" href="source/net/ipv4/netfilter/ipt_MASQUERADE.c#L50">50</a>         struct <a href="ident?i=nf_nat_range">nf_nat_range</a> <a href="ident?i=range">range</a>;
 <a name="L51" href="source/net/ipv4/netfilter/ipt_MASQUERADE.c#L51">51</a>         const struct <a href="ident?i=nf_nat_ipv4_multi_range_compat">nf_nat_ipv4_multi_range_compat</a> *mr;
 <a name="L52" href="source/net/ipv4/netfilter/ipt_MASQUERADE.c#L52">52</a> 
 <a name="L53" href="source/net/ipv4/netfilter/ipt_MASQUERADE.c#L53">53</a>         mr = <a href="ident?i=par">par</a>-&gt;targinfo;
 <a name="L54" href="source/net/ipv4/netfilter/ipt_MASQUERADE.c#L54">54</a>         <a href="ident?i=range">range</a>.<a href="ident?i=flags">flags</a> = mr-&gt;<a href="ident?i=range">range</a>[0].<a href="ident?i=flags">flags</a>;
 <a name="L55" href="source/net/ipv4/netfilter/ipt_MASQUERADE.c#L55">55</a>         <a href="ident?i=range">range</a>.<a href="ident?i=min_proto">min_proto</a> = mr-&gt;<a href="ident?i=range">range</a>[0].<a href="ident?i=min">min</a>;
 <a name="L56" href="source/net/ipv4/netfilter/ipt_MASQUERADE.c#L56">56</a>         <a href="ident?i=range">range</a>.<a href="ident?i=max_proto">max_proto</a> = mr-&gt;<a href="ident?i=range">range</a>[0].<a href="ident?i=max">max</a>;
 <a name="L57" href="source/net/ipv4/netfilter/ipt_MASQUERADE.c#L57">57</a> 
 <a name="L58" href="source/net/ipv4/netfilter/ipt_MASQUERADE.c#L58">58</a>         return <a href="ident?i=nf_nat_masquerade_ipv4">nf_nat_masquerade_ipv4</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=par">par</a>-&gt;hooknum, &amp;<a href="ident?i=range">range</a>, <a href="ident?i=par">par</a>-&gt;<a href="ident?i=out">out</a>);
 <a name="L59" href="source/net/ipv4/netfilter/ipt_MASQUERADE.c#L59">59</a> }
 <a name="L60" href="source/net/ipv4/netfilter/ipt_MASQUERADE.c#L60">60</a> 
 <a name="L61" href="source/net/ipv4/netfilter/ipt_MASQUERADE.c#L61">61</a> static struct <a href="ident?i=xt_target">xt_target</a> masquerade_tg_reg <a href="ident?i=__read_mostly">__read_mostly</a> = {
 <a name="L62" href="source/net/ipv4/netfilter/ipt_MASQUERADE.c#L62">62</a>         .<a href="ident?i=name">name</a>           = <i>"MASQUERADE"</i>,
 <a name="L63" href="source/net/ipv4/netfilter/ipt_MASQUERADE.c#L63">63</a>         .<a href="ident?i=family">family</a>         = NFPROTO_IPV4,
 <a name="L64" href="source/net/ipv4/netfilter/ipt_MASQUERADE.c#L64">64</a>         .<a href="ident?i=target">target</a>         = <a href="ident?i=masquerade_tg">masquerade_tg</a>,
 <a name="L65" href="source/net/ipv4/netfilter/ipt_MASQUERADE.c#L65">65</a>         .targetsize     = sizeof(struct <a href="ident?i=nf_nat_ipv4_multi_range_compat">nf_nat_ipv4_multi_range_compat</a>),
 <a name="L66" href="source/net/ipv4/netfilter/ipt_MASQUERADE.c#L66">66</a>         .<a href="ident?i=table">table</a>          = <i>"nat"</i>,
 <a name="L67" href="source/net/ipv4/netfilter/ipt_MASQUERADE.c#L67">67</a>         .<a href="ident?i=hooks">hooks</a>          = 1 &lt;&lt; NF_INET_POST_ROUTING,
 <a name="L68" href="source/net/ipv4/netfilter/ipt_MASQUERADE.c#L68">68</a>         .<a href="ident?i=checkentry">checkentry</a>     = <a href="ident?i=masquerade_tg_check">masquerade_tg_check</a>,
 <a name="L69" href="source/net/ipv4/netfilter/ipt_MASQUERADE.c#L69">69</a>         .<a href="ident?i=me">me</a>             = <a href="ident?i=THIS_MODULE">THIS_MODULE</a>,
 <a name="L70" href="source/net/ipv4/netfilter/ipt_MASQUERADE.c#L70">70</a> };
 <a name="L71" href="source/net/ipv4/netfilter/ipt_MASQUERADE.c#L71">71</a> 
 <a name="L72" href="source/net/ipv4/netfilter/ipt_MASQUERADE.c#L72">72</a> static int <a href="ident?i=__init">__init</a> <a href="ident?i=masquerade_tg_init">masquerade_tg_init</a>(void)
 <a name="L73" href="source/net/ipv4/netfilter/ipt_MASQUERADE.c#L73">73</a> {
 <a name="L74" href="source/net/ipv4/netfilter/ipt_MASQUERADE.c#L74">74</a>         int <a href="ident?i=ret">ret</a>;
 <a name="L75" href="source/net/ipv4/netfilter/ipt_MASQUERADE.c#L75">75</a> 
 <a name="L76" href="source/net/ipv4/netfilter/ipt_MASQUERADE.c#L76">76</a>         <a href="ident?i=ret">ret</a> = <a href="ident?i=xt_register_target">xt_register_target</a>(&amp;masquerade_tg_reg);
 <a name="L77" href="source/net/ipv4/netfilter/ipt_MASQUERADE.c#L77">77</a> 
 <a name="L78" href="source/net/ipv4/netfilter/ipt_MASQUERADE.c#L78">78</a>         if (<a href="ident?i=ret">ret</a> == 0)
 <a name="L79" href="source/net/ipv4/netfilter/ipt_MASQUERADE.c#L79">79</a>                 <a href="ident?i=nf_nat_masquerade_ipv4_register_notifier">nf_nat_masquerade_ipv4_register_notifier</a>();
 <a name="L80" href="source/net/ipv4/netfilter/ipt_MASQUERADE.c#L80">80</a> 
 <a name="L81" href="source/net/ipv4/netfilter/ipt_MASQUERADE.c#L81">81</a>         return <a href="ident?i=ret">ret</a>;
 <a name="L82" href="source/net/ipv4/netfilter/ipt_MASQUERADE.c#L82">82</a> }
 <a name="L83" href="source/net/ipv4/netfilter/ipt_MASQUERADE.c#L83">83</a> 
 <a name="L84" href="source/net/ipv4/netfilter/ipt_MASQUERADE.c#L84">84</a> static void <a href="ident?i=__exit">__exit</a> <a href="ident?i=masquerade_tg_exit">masquerade_tg_exit</a>(void)
 <a name="L85" href="source/net/ipv4/netfilter/ipt_MASQUERADE.c#L85">85</a> {
 <a name="L86" href="source/net/ipv4/netfilter/ipt_MASQUERADE.c#L86">86</a>         <a href="ident?i=xt_unregister_target">xt_unregister_target</a>(&amp;masquerade_tg_reg);
 <a name="L87" href="source/net/ipv4/netfilter/ipt_MASQUERADE.c#L87">87</a>         <a href="ident?i=nf_nat_masquerade_ipv4_unregister_notifier">nf_nat_masquerade_ipv4_unregister_notifier</a>();
 <a name="L88" href="source/net/ipv4/netfilter/ipt_MASQUERADE.c#L88">88</a> }
 <a name="L89" href="source/net/ipv4/netfilter/ipt_MASQUERADE.c#L89">89</a> 
 <a name="L90" href="source/net/ipv4/netfilter/ipt_MASQUERADE.c#L90">90</a> <a href="ident?i=module_init">module_init</a>(<a href="ident?i=masquerade_tg_init">masquerade_tg_init</a>);
 <a name="L91" href="source/net/ipv4/netfilter/ipt_MASQUERADE.c#L91">91</a> <a href="ident?i=module_exit">module_exit</a>(<a href="ident?i=masquerade_tg_exit">masquerade_tg_exit</a>);
 <a name="L92" href="source/net/ipv4/netfilter/ipt_MASQUERADE.c#L92">92</a> </pre></div><p>
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
