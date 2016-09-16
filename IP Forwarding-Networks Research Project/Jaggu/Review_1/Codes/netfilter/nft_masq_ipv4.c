<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title>Linux/net/ipv4/netfilter/nft_masq_ipv4.c - Linux Cross Reference - Free Electrons</title>
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
		 &nbsp;&bull;&nbsp;<b><i>source navigation</i></b> &nbsp;&bull;&nbsp;<a href="diff/net/ipv4/netfilter/nft_masq_ipv4.c">diff markup</a> &nbsp;&bull;&nbsp;<a href="ident">identifier search</a> &nbsp;&bull;&nbsp;<a href="search">freetext search</a> &nbsp;&bull;&nbsp;
		</p>
	</div>
</div>

<div id="topbar">
  
  <p>Version: &nbsp;<a href="source/net/ipv4/netfilter/nft_masq_ipv4.c?v=2.0.40">2.0.40</a>&nbsp;<a href="source/net/ipv4/netfilter/nft_masq_ipv4.c?v=2.2.26">2.2.26</a>&nbsp;<a href="source/net/ipv4/netfilter/nft_masq_ipv4.c?v=2.4.37">2.4.37</a>&nbsp;<a href="source/net/ipv4/netfilter/nft_masq_ipv4.c?v=3.5">3.5</a>&nbsp;<a href="source/net/ipv4/netfilter/nft_masq_ipv4.c?v=3.6">3.6</a>&nbsp;<a href="source/net/ipv4/netfilter/nft_masq_ipv4.c?v=3.7">3.7</a>&nbsp;<a href="source/net/ipv4/netfilter/nft_masq_ipv4.c?v=3.8">3.8</a>&nbsp;<a href="source/net/ipv4/netfilter/nft_masq_ipv4.c?v=3.9">3.9</a>&nbsp;<a href="source/net/ipv4/netfilter/nft_masq_ipv4.c?v=3.10">3.10</a>&nbsp;<a href="source/net/ipv4/netfilter/nft_masq_ipv4.c?v=3.11">3.11</a>&nbsp;<a href="source/net/ipv4/netfilter/nft_masq_ipv4.c?v=3.12">3.12</a>&nbsp;<a href="source/net/ipv4/netfilter/nft_masq_ipv4.c?v=3.13">3.13</a>&nbsp;<a href="source/net/ipv4/netfilter/nft_masq_ipv4.c?v=3.14">3.14</a>&nbsp;<a href="source/net/ipv4/netfilter/nft_masq_ipv4.c?v=3.15">3.15</a>&nbsp;<a href="source/net/ipv4/netfilter/nft_masq_ipv4.c?v=3.16">3.16</a>&nbsp;<a href="source/net/ipv4/netfilter/nft_masq_ipv4.c?v=3.17">3.17</a>&nbsp;<a href="source/net/ipv4/netfilter/nft_masq_ipv4.c?v=3.18">3.18</a>&nbsp;<a href="source/net/ipv4/netfilter/nft_masq_ipv4.c?v=3.19">3.19</a>&nbsp;<a href="source/net/ipv4/netfilter/nft_masq_ipv4.c?v=4.0">4.0</a>&nbsp;<b><i>4.1</i></b></p>
  
</div>

<h1><a href="source/">Linux</a>/<a href="source/net/">net</a>/<a href="source/net/ipv4/">ipv4</a>/<a href="source/net/ipv4/netfilter/">netfilter</a>/<a href="source/net/ipv4/netfilter/nft_masq_ipv4.c">nft_masq_ipv4.c</a></h1>
<div id="lxrcode"><pre>  <a name="L1" href="source/net/ipv4/netfilter/nft_masq_ipv4.c#L1">1</a> <b><i>/*</i></b>
  <a name="L2" href="source/net/ipv4/netfilter/nft_masq_ipv4.c#L2">2</a> <b><i> * Copyright (c) 2014 Arturo Borrero Gonzalez &lt;arturo.borrero.glez@gmail.com&gt;</i></b>
  <a name="L3" href="source/net/ipv4/netfilter/nft_masq_ipv4.c#L3">3</a> <b><i> *</i></b>
  <a name="L4" href="source/net/ipv4/netfilter/nft_masq_ipv4.c#L4">4</a> <b><i> * This program is free software; you can redistribute it and/or modify</i></b>
  <a name="L5" href="source/net/ipv4/netfilter/nft_masq_ipv4.c#L5">5</a> <b><i> * it under the terms of the GNU General Public License version 2 as</i></b>
  <a name="L6" href="source/net/ipv4/netfilter/nft_masq_ipv4.c#L6">6</a> <b><i> * published by the Free Software Foundation.</i></b>
  <a name="L7" href="source/net/ipv4/netfilter/nft_masq_ipv4.c#L7">7</a> <b><i> */</i></b>
  <a name="L8" href="source/net/ipv4/netfilter/nft_masq_ipv4.c#L8">8</a> 
  <a name="L9" href="source/net/ipv4/netfilter/nft_masq_ipv4.c#L9">9</a> #include &lt;linux/kernel.h&gt;
 <a name="L10" href="source/net/ipv4/netfilter/nft_masq_ipv4.c#L10">10</a> #include &lt;linux/init.h&gt;
 <a name="L11" href="source/net/ipv4/netfilter/nft_masq_ipv4.c#L11">11</a> #include &lt;linux/module.h&gt;
 <a name="L12" href="source/net/ipv4/netfilter/nft_masq_ipv4.c#L12">12</a> #include &lt;linux/netlink.h&gt;
 <a name="L13" href="source/net/ipv4/netfilter/nft_masq_ipv4.c#L13">13</a> #include &lt;linux/netfilter.h&gt;
 <a name="L14" href="source/net/ipv4/netfilter/nft_masq_ipv4.c#L14">14</a> #include &lt;linux/netfilter/nf_tables.h&gt;
 <a name="L15" href="source/net/ipv4/netfilter/nft_masq_ipv4.c#L15">15</a> #include &lt;net/netfilter/nf_tables.h&gt;
 <a name="L16" href="source/net/ipv4/netfilter/nft_masq_ipv4.c#L16">16</a> #include &lt;net/netfilter/nft_masq.h&gt;
 <a name="L17" href="source/net/ipv4/netfilter/nft_masq_ipv4.c#L17">17</a> #include &lt;net/netfilter/ipv4/nf_nat_masquerade.h&gt;
 <a name="L18" href="source/net/ipv4/netfilter/nft_masq_ipv4.c#L18">18</a> 
 <a name="L19" href="source/net/ipv4/netfilter/nft_masq_ipv4.c#L19">19</a> static void <a href="ident?i=nft_masq_ipv4_eval">nft_masq_ipv4_eval</a>(const struct <a href="ident?i=nft_expr">nft_expr</a> *expr,
 <a name="L20" href="source/net/ipv4/netfilter/nft_masq_ipv4.c#L20">20</a>                                struct <a href="ident?i=nft_regs">nft_regs</a> *<a href="ident?i=regs">regs</a>,
 <a name="L21" href="source/net/ipv4/netfilter/nft_masq_ipv4.c#L21">21</a>                                const struct <a href="ident?i=nft_pktinfo">nft_pktinfo</a> *<a href="ident?i=pkt">pkt</a>)
 <a name="L22" href="source/net/ipv4/netfilter/nft_masq_ipv4.c#L22">22</a> {
 <a name="L23" href="source/net/ipv4/netfilter/nft_masq_ipv4.c#L23">23</a>         struct <a href="ident?i=nft_masq">nft_masq</a> *<a href="ident?i=priv">priv</a> = <a href="ident?i=nft_expr_priv">nft_expr_priv</a>(expr);
 <a name="L24" href="source/net/ipv4/netfilter/nft_masq_ipv4.c#L24">24</a>         struct <a href="ident?i=nf_nat_range">nf_nat_range</a> <a href="ident?i=range">range</a>;
 <a name="L25" href="source/net/ipv4/netfilter/nft_masq_ipv4.c#L25">25</a> 
 <a name="L26" href="source/net/ipv4/netfilter/nft_masq_ipv4.c#L26">26</a>         <a href="ident?i=memset">memset</a>(&amp;<a href="ident?i=range">range</a>, 0, sizeof(<a href="ident?i=range">range</a>));
 <a name="L27" href="source/net/ipv4/netfilter/nft_masq_ipv4.c#L27">27</a>         <a href="ident?i=range">range</a>.<a href="ident?i=flags">flags</a> = <a href="ident?i=priv">priv</a>-&gt;<a href="ident?i=flags">flags</a>;
 <a name="L28" href="source/net/ipv4/netfilter/nft_masq_ipv4.c#L28">28</a> 
 <a name="L29" href="source/net/ipv4/netfilter/nft_masq_ipv4.c#L29">29</a>         <a href="ident?i=regs">regs</a>-&gt;verdict.<a href="ident?i=code">code</a> = <a href="ident?i=nf_nat_masquerade_ipv4">nf_nat_masquerade_ipv4</a>(<a href="ident?i=pkt">pkt</a>-&gt;<a href="ident?i=skb">skb</a>, <a href="ident?i=pkt">pkt</a>-&gt;<a href="ident?i=ops">ops</a>-&gt;hooknum,
 <a name="L30" href="source/net/ipv4/netfilter/nft_masq_ipv4.c#L30">30</a>                                                     &amp;<a href="ident?i=range">range</a>, <a href="ident?i=pkt">pkt</a>-&gt;<a href="ident?i=out">out</a>);
 <a name="L31" href="source/net/ipv4/netfilter/nft_masq_ipv4.c#L31">31</a> }
 <a name="L32" href="source/net/ipv4/netfilter/nft_masq_ipv4.c#L32">32</a> 
 <a name="L33" href="source/net/ipv4/netfilter/nft_masq_ipv4.c#L33">33</a> static struct <a href="ident?i=nft_expr_type">nft_expr_type</a> <a href="ident?i=nft_masq_ipv4_type">nft_masq_ipv4_type</a>;
 <a name="L34" href="source/net/ipv4/netfilter/nft_masq_ipv4.c#L34">34</a> static const struct <a href="ident?i=nft_expr_ops">nft_expr_ops</a> <a href="ident?i=nft_masq_ipv4_ops">nft_masq_ipv4_ops</a> = {
 <a name="L35" href="source/net/ipv4/netfilter/nft_masq_ipv4.c#L35">35</a>         .<a href="ident?i=type">type</a>           = &amp;<a href="ident?i=nft_masq_ipv4_type">nft_masq_ipv4_type</a>,
 <a name="L36" href="source/net/ipv4/netfilter/nft_masq_ipv4.c#L36">36</a>         .<a href="ident?i=size">size</a>           = <a href="ident?i=NFT_EXPR_SIZE">NFT_EXPR_SIZE</a>(sizeof(struct <a href="ident?i=nft_masq">nft_masq</a>)),
 <a name="L37" href="source/net/ipv4/netfilter/nft_masq_ipv4.c#L37">37</a>         .eval           = <a href="ident?i=nft_masq_ipv4_eval">nft_masq_ipv4_eval</a>,
 <a name="L38" href="source/net/ipv4/netfilter/nft_masq_ipv4.c#L38">38</a>         .<a href="ident?i=init">init</a>           = <a href="ident?i=nft_masq_init">nft_masq_init</a>,
 <a name="L39" href="source/net/ipv4/netfilter/nft_masq_ipv4.c#L39">39</a>         .<a href="ident?i=dump">dump</a>           = <a href="ident?i=nft_masq_dump">nft_masq_dump</a>,
 <a name="L40" href="source/net/ipv4/netfilter/nft_masq_ipv4.c#L40">40</a>         .<a href="ident?i=validate">validate</a>       = <a href="ident?i=nft_masq_validate">nft_masq_validate</a>,
 <a name="L41" href="source/net/ipv4/netfilter/nft_masq_ipv4.c#L41">41</a> };
 <a name="L42" href="source/net/ipv4/netfilter/nft_masq_ipv4.c#L42">42</a> 
 <a name="L43" href="source/net/ipv4/netfilter/nft_masq_ipv4.c#L43">43</a> static struct <a href="ident?i=nft_expr_type">nft_expr_type</a> <a href="ident?i=nft_masq_ipv4_type">nft_masq_ipv4_type</a> <a href="ident?i=__read_mostly">__read_mostly</a> = {
 <a name="L44" href="source/net/ipv4/netfilter/nft_masq_ipv4.c#L44">44</a>         .<a href="ident?i=family">family</a>         = NFPROTO_IPV4,
 <a name="L45" href="source/net/ipv4/netfilter/nft_masq_ipv4.c#L45">45</a>         .<a href="ident?i=name">name</a>           = <i>"masq"</i>,
 <a name="L46" href="source/net/ipv4/netfilter/nft_masq_ipv4.c#L46">46</a>         .<a href="ident?i=ops">ops</a>            = &amp;<a href="ident?i=nft_masq_ipv4_ops">nft_masq_ipv4_ops</a>,
 <a name="L47" href="source/net/ipv4/netfilter/nft_masq_ipv4.c#L47">47</a>         .<a href="ident?i=policy">policy</a>         = <a href="ident?i=nft_masq_policy">nft_masq_policy</a>,
 <a name="L48" href="source/net/ipv4/netfilter/nft_masq_ipv4.c#L48">48</a>         .maxattr        = <a href="ident?i=NFTA_MASQ_MAX">NFTA_MASQ_MAX</a>,
 <a name="L49" href="source/net/ipv4/netfilter/nft_masq_ipv4.c#L49">49</a>         .owner          = <a href="ident?i=THIS_MODULE">THIS_MODULE</a>,
 <a name="L50" href="source/net/ipv4/netfilter/nft_masq_ipv4.c#L50">50</a> };
 <a name="L51" href="source/net/ipv4/netfilter/nft_masq_ipv4.c#L51">51</a> 
 <a name="L52" href="source/net/ipv4/netfilter/nft_masq_ipv4.c#L52">52</a> static int <a href="ident?i=__init">__init</a> <a href="ident?i=nft_masq_ipv4_module_init">nft_masq_ipv4_module_init</a>(void)
 <a name="L53" href="source/net/ipv4/netfilter/nft_masq_ipv4.c#L53">53</a> {
 <a name="L54" href="source/net/ipv4/netfilter/nft_masq_ipv4.c#L54">54</a>         int <a href="ident?i=ret">ret</a>;
 <a name="L55" href="source/net/ipv4/netfilter/nft_masq_ipv4.c#L55">55</a> 
 <a name="L56" href="source/net/ipv4/netfilter/nft_masq_ipv4.c#L56">56</a>         <a href="ident?i=ret">ret</a> = <a href="ident?i=nft_register_expr">nft_register_expr</a>(&amp;<a href="ident?i=nft_masq_ipv4_type">nft_masq_ipv4_type</a>);
 <a name="L57" href="source/net/ipv4/netfilter/nft_masq_ipv4.c#L57">57</a>         if (<a href="ident?i=ret">ret</a> &lt; 0)
 <a name="L58" href="source/net/ipv4/netfilter/nft_masq_ipv4.c#L58">58</a>                 return <a href="ident?i=ret">ret</a>;
 <a name="L59" href="source/net/ipv4/netfilter/nft_masq_ipv4.c#L59">59</a> 
 <a name="L60" href="source/net/ipv4/netfilter/nft_masq_ipv4.c#L60">60</a>         <a href="ident?i=nf_nat_masquerade_ipv4_register_notifier">nf_nat_masquerade_ipv4_register_notifier</a>();
 <a name="L61" href="source/net/ipv4/netfilter/nft_masq_ipv4.c#L61">61</a> 
 <a name="L62" href="source/net/ipv4/netfilter/nft_masq_ipv4.c#L62">62</a>         return <a href="ident?i=ret">ret</a>;
 <a name="L63" href="source/net/ipv4/netfilter/nft_masq_ipv4.c#L63">63</a> }
 <a name="L64" href="source/net/ipv4/netfilter/nft_masq_ipv4.c#L64">64</a> 
 <a name="L65" href="source/net/ipv4/netfilter/nft_masq_ipv4.c#L65">65</a> static void <a href="ident?i=__exit">__exit</a> <a href="ident?i=nft_masq_ipv4_module_exit">nft_masq_ipv4_module_exit</a>(void)
 <a name="L66" href="source/net/ipv4/netfilter/nft_masq_ipv4.c#L66">66</a> {
 <a name="L67" href="source/net/ipv4/netfilter/nft_masq_ipv4.c#L67">67</a>         <a href="ident?i=nft_unregister_expr">nft_unregister_expr</a>(&amp;<a href="ident?i=nft_masq_ipv4_type">nft_masq_ipv4_type</a>);
 <a name="L68" href="source/net/ipv4/netfilter/nft_masq_ipv4.c#L68">68</a>         <a href="ident?i=nf_nat_masquerade_ipv4_unregister_notifier">nf_nat_masquerade_ipv4_unregister_notifier</a>();
 <a name="L69" href="source/net/ipv4/netfilter/nft_masq_ipv4.c#L69">69</a> }
 <a name="L70" href="source/net/ipv4/netfilter/nft_masq_ipv4.c#L70">70</a> 
 <a name="L71" href="source/net/ipv4/netfilter/nft_masq_ipv4.c#L71">71</a> <a href="ident?i=module_init">module_init</a>(<a href="ident?i=nft_masq_ipv4_module_init">nft_masq_ipv4_module_init</a>);
 <a name="L72" href="source/net/ipv4/netfilter/nft_masq_ipv4.c#L72">72</a> <a href="ident?i=module_exit">module_exit</a>(<a href="ident?i=nft_masq_ipv4_module_exit">nft_masq_ipv4_module_exit</a>);
 <a name="L73" href="source/net/ipv4/netfilter/nft_masq_ipv4.c#L73">73</a> 
 <a name="L74" href="source/net/ipv4/netfilter/nft_masq_ipv4.c#L74">74</a> <a href="ident?i=MODULE_LICENSE">MODULE_LICENSE</a>(<i>"GPL"</i>);
 <a name="L75" href="source/net/ipv4/netfilter/nft_masq_ipv4.c#L75">75</a> <a href="ident?i=MODULE_AUTHOR">MODULE_AUTHOR</a>(<i>"Arturo Borrero Gonzalez &lt;arturo.borrero.glez@gmail.com&gt;"</i>);
 <a name="L76" href="source/net/ipv4/netfilter/nft_masq_ipv4.c#L76">76</a> <a href="ident?i=MODULE_ALIAS_NFT_AF_EXPR">MODULE_ALIAS_NFT_AF_EXPR</a>(<a href="ident?i=AF_INET">AF_INET</a>, <i>"masq"</i>);
 <a name="L77" href="source/net/ipv4/netfilter/nft_masq_ipv4.c#L77">77</a> </pre></div><p>
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
