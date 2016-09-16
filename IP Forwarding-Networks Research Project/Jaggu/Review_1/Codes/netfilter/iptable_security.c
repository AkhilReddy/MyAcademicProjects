<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title>Linux/net/ipv4/netfilter/iptable_security.c - Linux Cross Reference - Free Electrons</title>
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
		 &nbsp;&bull;&nbsp;<b><i>source navigation</i></b> &nbsp;&bull;&nbsp;<a href="diff/net/ipv4/netfilter/iptable_security.c">diff markup</a> &nbsp;&bull;&nbsp;<a href="ident">identifier search</a> &nbsp;&bull;&nbsp;<a href="search">freetext search</a> &nbsp;&bull;&nbsp;
		</p>
	</div>
</div>

<div id="topbar">
  
  <p>Version: &nbsp;<a href="source/net/ipv4/netfilter/iptable_security.c?v=2.0.40">2.0.40</a>&nbsp;<a href="source/net/ipv4/netfilter/iptable_security.c?v=2.2.26">2.2.26</a>&nbsp;<a href="source/net/ipv4/netfilter/iptable_security.c?v=2.4.37">2.4.37</a>&nbsp;<a href="source/net/ipv4/netfilter/iptable_security.c?v=3.5">3.5</a>&nbsp;<a href="source/net/ipv4/netfilter/iptable_security.c?v=3.6">3.6</a>&nbsp;<a href="source/net/ipv4/netfilter/iptable_security.c?v=3.7">3.7</a>&nbsp;<a href="source/net/ipv4/netfilter/iptable_security.c?v=3.8">3.8</a>&nbsp;<a href="source/net/ipv4/netfilter/iptable_security.c?v=3.9">3.9</a>&nbsp;<a href="source/net/ipv4/netfilter/iptable_security.c?v=3.10">3.10</a>&nbsp;<a href="source/net/ipv4/netfilter/iptable_security.c?v=3.11">3.11</a>&nbsp;<a href="source/net/ipv4/netfilter/iptable_security.c?v=3.12">3.12</a>&nbsp;<a href="source/net/ipv4/netfilter/iptable_security.c?v=3.13">3.13</a>&nbsp;<a href="source/net/ipv4/netfilter/iptable_security.c?v=3.14">3.14</a>&nbsp;<a href="source/net/ipv4/netfilter/iptable_security.c?v=3.15">3.15</a>&nbsp;<a href="source/net/ipv4/netfilter/iptable_security.c?v=3.16">3.16</a>&nbsp;<a href="source/net/ipv4/netfilter/iptable_security.c?v=3.17">3.17</a>&nbsp;<a href="source/net/ipv4/netfilter/iptable_security.c?v=3.18">3.18</a>&nbsp;<a href="source/net/ipv4/netfilter/iptable_security.c?v=3.19">3.19</a>&nbsp;<a href="source/net/ipv4/netfilter/iptable_security.c?v=4.0">4.0</a>&nbsp;<b><i>4.1</i></b></p>
  
</div>

<h1><a href="source/">Linux</a>/<a href="source/net/">net</a>/<a href="source/net/ipv4/">ipv4</a>/<a href="source/net/ipv4/netfilter/">netfilter</a>/<a href="source/net/ipv4/netfilter/iptable_security.c">iptable_security.c</a></h1>
<div id="lxrcode"><pre>  <a name="L1" href="source/net/ipv4/netfilter/iptable_security.c#L1">1</a> <b><i>/*</i></b>
  <a name="L2" href="source/net/ipv4/netfilter/iptable_security.c#L2">2</a> <b><i> * "security" table</i></b>
  <a name="L3" href="source/net/ipv4/netfilter/iptable_security.c#L3">3</a> <b><i> *</i></b>
  <a name="L4" href="source/net/ipv4/netfilter/iptable_security.c#L4">4</a> <b><i> * This is for use by Mandatory Access Control (MAC) security models,</i></b>
  <a name="L5" href="source/net/ipv4/netfilter/iptable_security.c#L5">5</a> <b><i> * which need to be able to manage security policy in separate context</i></b>
  <a name="L6" href="source/net/ipv4/netfilter/iptable_security.c#L6">6</a> <b><i> * to DAC.</i></b>
  <a name="L7" href="source/net/ipv4/netfilter/iptable_security.c#L7">7</a> <b><i> *</i></b>
  <a name="L8" href="source/net/ipv4/netfilter/iptable_security.c#L8">8</a> <b><i> * Based on iptable_mangle.c</i></b>
  <a name="L9" href="source/net/ipv4/netfilter/iptable_security.c#L9">9</a> <b><i> *</i></b>
 <a name="L10" href="source/net/ipv4/netfilter/iptable_security.c#L10">10</a> <b><i> * Copyright (C) 1999 Paul `Rusty' Russell &amp; Michael J. Neuling</i></b>
 <a name="L11" href="source/net/ipv4/netfilter/iptable_security.c#L11">11</a> <b><i> * Copyright (C) 2000-2004 Netfilter Core Team &lt;coreteam &lt;at&gt; netfilter.org&gt;</i></b>
 <a name="L12" href="source/net/ipv4/netfilter/iptable_security.c#L12">12</a> <b><i> * Copyright (C) 2008 Red Hat, Inc., James Morris &lt;jmorris &lt;at&gt; redhat.com&gt;</i></b>
 <a name="L13" href="source/net/ipv4/netfilter/iptable_security.c#L13">13</a> <b><i> *</i></b>
 <a name="L14" href="source/net/ipv4/netfilter/iptable_security.c#L14">14</a> <b><i> * This program is free software; you can redistribute it and/or modify</i></b>
 <a name="L15" href="source/net/ipv4/netfilter/iptable_security.c#L15">15</a> <b><i> * it under the terms of the GNU General Public License version 2 as</i></b>
 <a name="L16" href="source/net/ipv4/netfilter/iptable_security.c#L16">16</a> <b><i> * published by the Free Software Foundation.</i></b>
 <a name="L17" href="source/net/ipv4/netfilter/iptable_security.c#L17">17</a> <b><i> */</i></b>
 <a name="L18" href="source/net/ipv4/netfilter/iptable_security.c#L18">18</a> #include &lt;linux/module.h&gt;
 <a name="L19" href="source/net/ipv4/netfilter/iptable_security.c#L19">19</a> #include &lt;linux/netfilter_ipv4/ip_tables.h&gt;
 <a name="L20" href="source/net/ipv4/netfilter/iptable_security.c#L20">20</a> #include &lt;linux/slab.h&gt;
 <a name="L21" href="source/net/ipv4/netfilter/iptable_security.c#L21">21</a> #include &lt;net/ip.h&gt;
 <a name="L22" href="source/net/ipv4/netfilter/iptable_security.c#L22">22</a> 
 <a name="L23" href="source/net/ipv4/netfilter/iptable_security.c#L23">23</a> <a href="ident?i=MODULE_LICENSE">MODULE_LICENSE</a>(<i>"GPL"</i>);
 <a name="L24" href="source/net/ipv4/netfilter/iptable_security.c#L24">24</a> <a href="ident?i=MODULE_AUTHOR">MODULE_AUTHOR</a>(<i>"James Morris &lt;jmorris &lt;at&gt; redhat.com&gt;"</i>);
 <a name="L25" href="source/net/ipv4/netfilter/iptable_security.c#L25">25</a> <a href="ident?i=MODULE_DESCRIPTION">MODULE_DESCRIPTION</a>(<i>"iptables security table, for MAC rules"</i>);
 <a name="L26" href="source/net/ipv4/netfilter/iptable_security.c#L26">26</a> 
 <a name="L27" href="source/net/ipv4/netfilter/iptable_security.c#L27">27</a> #define <a href="ident?i=SECURITY_VALID_HOOKS">SECURITY_VALID_HOOKS</a>    (1 &lt;&lt; NF_INET_LOCAL_IN) | \
 <a name="L28" href="source/net/ipv4/netfilter/iptable_security.c#L28">28</a>                                 (1 &lt;&lt; NF_INET_FORWARD) | \
 <a name="L29" href="source/net/ipv4/netfilter/iptable_security.c#L29">29</a>                                 (1 &lt;&lt; NF_INET_LOCAL_OUT)
 <a name="L30" href="source/net/ipv4/netfilter/iptable_security.c#L30">30</a> 
 <a name="L31" href="source/net/ipv4/netfilter/iptable_security.c#L31">31</a> static const struct <a href="ident?i=xt_table">xt_table</a> <a href="ident?i=security_table">security_table</a> = {
 <a name="L32" href="source/net/ipv4/netfilter/iptable_security.c#L32">32</a>         .<a href="ident?i=name">name</a>           = <i>"security"</i>,
 <a name="L33" href="source/net/ipv4/netfilter/iptable_security.c#L33">33</a>         .valid_hooks    = <a href="ident?i=SECURITY_VALID_HOOKS">SECURITY_VALID_HOOKS</a>,
 <a name="L34" href="source/net/ipv4/netfilter/iptable_security.c#L34">34</a>         .<a href="ident?i=me">me</a>             = <a href="ident?i=THIS_MODULE">THIS_MODULE</a>,
 <a name="L35" href="source/net/ipv4/netfilter/iptable_security.c#L35">35</a>         .<a href="ident?i=af">af</a>             = NFPROTO_IPV4,
 <a name="L36" href="source/net/ipv4/netfilter/iptable_security.c#L36">36</a>         .<a href="ident?i=priority">priority</a>       = NF_IP_PRI_SECURITY,
 <a name="L37" href="source/net/ipv4/netfilter/iptable_security.c#L37">37</a> };
 <a name="L38" href="source/net/ipv4/netfilter/iptable_security.c#L38">38</a> 
 <a name="L39" href="source/net/ipv4/netfilter/iptable_security.c#L39">39</a> static unsigned int
 <a name="L40" href="source/net/ipv4/netfilter/iptable_security.c#L40">40</a> <a href="ident?i=iptable_security_hook">iptable_security_hook</a>(const struct <a href="ident?i=nf_hook_ops">nf_hook_ops</a> *<a href="ident?i=ops">ops</a>, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
 <a name="L41" href="source/net/ipv4/netfilter/iptable_security.c#L41">41</a>                       const struct <a href="ident?i=nf_hook_state">nf_hook_state</a> *<a href="ident?i=state">state</a>)
 <a name="L42" href="source/net/ipv4/netfilter/iptable_security.c#L42">42</a> {
 <a name="L43" href="source/net/ipv4/netfilter/iptable_security.c#L43">43</a>         const struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>;
 <a name="L44" href="source/net/ipv4/netfilter/iptable_security.c#L44">44</a> 
 <a name="L45" href="source/net/ipv4/netfilter/iptable_security.c#L45">45</a>         if (<a href="ident?i=ops">ops</a>-&gt;hooknum == NF_INET_LOCAL_OUT &amp;&amp;
 <a name="L46" href="source/net/ipv4/netfilter/iptable_security.c#L46">46</a>             (<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a> &lt; sizeof(struct <a href="ident?i=iphdr">iphdr</a>) ||
 <a name="L47" href="source/net/ipv4/netfilter/iptable_security.c#L47">47</a>              <a href="ident?i=ip_hdrlen">ip_hdrlen</a>(<a href="ident?i=skb">skb</a>) &lt; sizeof(struct <a href="ident?i=iphdr">iphdr</a>)))
 <a name="L48" href="source/net/ipv4/netfilter/iptable_security.c#L48">48</a>                 <b><i>/* Somebody is playing with raw sockets. */</i></b>
 <a name="L49" href="source/net/ipv4/netfilter/iptable_security.c#L49">49</a>                 return <a href="ident?i=NF_ACCEPT">NF_ACCEPT</a>;
 <a name="L50" href="source/net/ipv4/netfilter/iptable_security.c#L50">50</a> 
 <a name="L51" href="source/net/ipv4/netfilter/iptable_security.c#L51">51</a>         <a href="ident?i=net">net</a> = <a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=state">state</a>-&gt;<a href="ident?i=in">in</a> ? <a href="ident?i=state">state</a>-&gt;<a href="ident?i=in">in</a> : <a href="ident?i=state">state</a>-&gt;<a href="ident?i=out">out</a>);
 <a name="L52" href="source/net/ipv4/netfilter/iptable_security.c#L52">52</a>         return <a href="ident?i=ipt_do_table">ipt_do_table</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=ops">ops</a>-&gt;hooknum, <a href="ident?i=state">state</a>,
 <a name="L53" href="source/net/ipv4/netfilter/iptable_security.c#L53">53</a>                             <a href="ident?i=net">net</a>-&gt;ipv4.iptable_security);
 <a name="L54" href="source/net/ipv4/netfilter/iptable_security.c#L54">54</a> }
 <a name="L55" href="source/net/ipv4/netfilter/iptable_security.c#L55">55</a> 
 <a name="L56" href="source/net/ipv4/netfilter/iptable_security.c#L56">56</a> static struct <a href="ident?i=nf_hook_ops">nf_hook_ops</a> *sectbl_ops <a href="ident?i=__read_mostly">__read_mostly</a>;
 <a name="L57" href="source/net/ipv4/netfilter/iptable_security.c#L57">57</a> 
 <a name="L58" href="source/net/ipv4/netfilter/iptable_security.c#L58">58</a> static int <a href="ident?i=__net_init">__net_init</a> <a href="ident?i=iptable_security_net_init">iptable_security_net_init</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>)
 <a name="L59" href="source/net/ipv4/netfilter/iptable_security.c#L59">59</a> {
 <a name="L60" href="source/net/ipv4/netfilter/iptable_security.c#L60">60</a>         struct <a href="ident?i=ipt_replace">ipt_replace</a> *repl;
 <a name="L61" href="source/net/ipv4/netfilter/iptable_security.c#L61">61</a> 
 <a name="L62" href="source/net/ipv4/netfilter/iptable_security.c#L62">62</a>         repl = <a href="ident?i=ipt_alloc_initial_table">ipt_alloc_initial_table</a>(&amp;<a href="ident?i=security_table">security_table</a>);
 <a name="L63" href="source/net/ipv4/netfilter/iptable_security.c#L63">63</a>         if (repl == <a href="ident?i=NULL">NULL</a>)
 <a name="L64" href="source/net/ipv4/netfilter/iptable_security.c#L64">64</a>                 return -<a href="ident?i=ENOMEM">ENOMEM</a>;
 <a name="L65" href="source/net/ipv4/netfilter/iptable_security.c#L65">65</a>         <a href="ident?i=net">net</a>-&gt;ipv4.iptable_security =
 <a name="L66" href="source/net/ipv4/netfilter/iptable_security.c#L66">66</a>                 <a href="ident?i=ipt_register_table">ipt_register_table</a>(<a href="ident?i=net">net</a>, &amp;<a href="ident?i=security_table">security_table</a>, repl);
 <a name="L67" href="source/net/ipv4/netfilter/iptable_security.c#L67">67</a>         <a href="ident?i=kfree">kfree</a>(repl);
 <a name="L68" href="source/net/ipv4/netfilter/iptable_security.c#L68">68</a>         return <a href="ident?i=PTR_ERR_OR_ZERO">PTR_ERR_OR_ZERO</a>(<a href="ident?i=net">net</a>-&gt;ipv4.iptable_security);
 <a name="L69" href="source/net/ipv4/netfilter/iptable_security.c#L69">69</a> }
 <a name="L70" href="source/net/ipv4/netfilter/iptable_security.c#L70">70</a> 
 <a name="L71" href="source/net/ipv4/netfilter/iptable_security.c#L71">71</a> static void <a href="ident?i=__net_exit">__net_exit</a> <a href="ident?i=iptable_security_net_exit">iptable_security_net_exit</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>)
 <a name="L72" href="source/net/ipv4/netfilter/iptable_security.c#L72">72</a> {
 <a name="L73" href="source/net/ipv4/netfilter/iptable_security.c#L73">73</a>         <a href="ident?i=ipt_unregister_table">ipt_unregister_table</a>(<a href="ident?i=net">net</a>, <a href="ident?i=net">net</a>-&gt;ipv4.iptable_security);
 <a name="L74" href="source/net/ipv4/netfilter/iptable_security.c#L74">74</a> }
 <a name="L75" href="source/net/ipv4/netfilter/iptable_security.c#L75">75</a> 
 <a name="L76" href="source/net/ipv4/netfilter/iptable_security.c#L76">76</a> static struct <a href="ident?i=pernet_operations">pernet_operations</a> <a href="ident?i=iptable_security_net_ops">iptable_security_net_ops</a> = {
 <a name="L77" href="source/net/ipv4/netfilter/iptable_security.c#L77">77</a>         .<a href="ident?i=init">init</a> = <a href="ident?i=iptable_security_net_init">iptable_security_net_init</a>,
 <a name="L78" href="source/net/ipv4/netfilter/iptable_security.c#L78">78</a>         .<a href="ident?i=exit">exit</a> = <a href="ident?i=iptable_security_net_exit">iptable_security_net_exit</a>,
 <a name="L79" href="source/net/ipv4/netfilter/iptable_security.c#L79">79</a> };
 <a name="L80" href="source/net/ipv4/netfilter/iptable_security.c#L80">80</a> 
 <a name="L81" href="source/net/ipv4/netfilter/iptable_security.c#L81">81</a> static int <a href="ident?i=__init">__init</a> <a href="ident?i=iptable_security_init">iptable_security_init</a>(void)
 <a name="L82" href="source/net/ipv4/netfilter/iptable_security.c#L82">82</a> {
 <a name="L83" href="source/net/ipv4/netfilter/iptable_security.c#L83">83</a>         int <a href="ident?i=ret">ret</a>;
 <a name="L84" href="source/net/ipv4/netfilter/iptable_security.c#L84">84</a> 
 <a name="L85" href="source/net/ipv4/netfilter/iptable_security.c#L85">85</a>         <a href="ident?i=ret">ret</a> = <a href="ident?i=register_pernet_subsys">register_pernet_subsys</a>(&amp;<a href="ident?i=iptable_security_net_ops">iptable_security_net_ops</a>);
 <a name="L86" href="source/net/ipv4/netfilter/iptable_security.c#L86">86</a>         if (<a href="ident?i=ret">ret</a> &lt; 0)
 <a name="L87" href="source/net/ipv4/netfilter/iptable_security.c#L87">87</a>                 return <a href="ident?i=ret">ret</a>;
 <a name="L88" href="source/net/ipv4/netfilter/iptable_security.c#L88">88</a> 
 <a name="L89" href="source/net/ipv4/netfilter/iptable_security.c#L89">89</a>         sectbl_ops = <a href="ident?i=xt_hook_link">xt_hook_link</a>(&amp;<a href="ident?i=security_table">security_table</a>, <a href="ident?i=iptable_security_hook">iptable_security_hook</a>);
 <a name="L90" href="source/net/ipv4/netfilter/iptable_security.c#L90">90</a>         if (<a href="ident?i=IS_ERR">IS_ERR</a>(sectbl_ops)) {
 <a name="L91" href="source/net/ipv4/netfilter/iptable_security.c#L91">91</a>                 <a href="ident?i=ret">ret</a> = <a href="ident?i=PTR_ERR">PTR_ERR</a>(sectbl_ops);
 <a name="L92" href="source/net/ipv4/netfilter/iptable_security.c#L92">92</a>                 goto cleanup_table;
 <a name="L93" href="source/net/ipv4/netfilter/iptable_security.c#L93">93</a>         }
 <a name="L94" href="source/net/ipv4/netfilter/iptable_security.c#L94">94</a> 
 <a name="L95" href="source/net/ipv4/netfilter/iptable_security.c#L95">95</a>         return <a href="ident?i=ret">ret</a>;
 <a name="L96" href="source/net/ipv4/netfilter/iptable_security.c#L96">96</a> 
 <a name="L97" href="source/net/ipv4/netfilter/iptable_security.c#L97">97</a> cleanup_table:
 <a name="L98" href="source/net/ipv4/netfilter/iptable_security.c#L98">98</a>         <a href="ident?i=unregister_pernet_subsys">unregister_pernet_subsys</a>(&amp;<a href="ident?i=iptable_security_net_ops">iptable_security_net_ops</a>);
 <a name="L99" href="source/net/ipv4/netfilter/iptable_security.c#L99">99</a>         return <a href="ident?i=ret">ret</a>;
<a name="L100" href="source/net/ipv4/netfilter/iptable_security.c#L100">100</a> }
<a name="L101" href="source/net/ipv4/netfilter/iptable_security.c#L101">101</a> 
<a name="L102" href="source/net/ipv4/netfilter/iptable_security.c#L102">102</a> static void <a href="ident?i=__exit">__exit</a> <a href="ident?i=iptable_security_fini">iptable_security_fini</a>(void)
<a name="L103" href="source/net/ipv4/netfilter/iptable_security.c#L103">103</a> {
<a name="L104" href="source/net/ipv4/netfilter/iptable_security.c#L104">104</a>         <a href="ident?i=xt_hook_unlink">xt_hook_unlink</a>(&amp;<a href="ident?i=security_table">security_table</a>, sectbl_ops);
<a name="L105" href="source/net/ipv4/netfilter/iptable_security.c#L105">105</a>         <a href="ident?i=unregister_pernet_subsys">unregister_pernet_subsys</a>(&amp;<a href="ident?i=iptable_security_net_ops">iptable_security_net_ops</a>);
<a name="L106" href="source/net/ipv4/netfilter/iptable_security.c#L106">106</a> }
<a name="L107" href="source/net/ipv4/netfilter/iptable_security.c#L107">107</a> 
<a name="L108" href="source/net/ipv4/netfilter/iptable_security.c#L108">108</a> <a href="ident?i=module_init">module_init</a>(<a href="ident?i=iptable_security_init">iptable_security_init</a>);
<a name="L109" href="source/net/ipv4/netfilter/iptable_security.c#L109">109</a> <a href="ident?i=module_exit">module_exit</a>(<a href="ident?i=iptable_security_fini">iptable_security_fini</a>);
<a name="L110" href="source/net/ipv4/netfilter/iptable_security.c#L110">110</a> </pre></div><p>
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
