<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title>Linux/net/ipv4/netfilter/ipt_REJECT.c - Linux Cross Reference - Free Electrons</title>
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
		 &nbsp;&bull;&nbsp;<b><i>source navigation</i></b> &nbsp;&bull;&nbsp;<a href="diff/net/ipv4/netfilter/ipt_REJECT.c">diff markup</a> &nbsp;&bull;&nbsp;<a href="ident">identifier search</a> &nbsp;&bull;&nbsp;<a href="search">freetext search</a> &nbsp;&bull;&nbsp;
		</p>
	</div>
</div>

<div id="topbar">
  
  <p>Version: &nbsp;<a href="source/net/ipv4/netfilter/ipt_REJECT.c?v=2.0.40">2.0.40</a>&nbsp;<a href="source/net/ipv4/netfilter/ipt_REJECT.c?v=2.2.26">2.2.26</a>&nbsp;<a href="source/net/ipv4/netfilter/ipt_REJECT.c?v=2.4.37">2.4.37</a>&nbsp;<a href="source/net/ipv4/netfilter/ipt_REJECT.c?v=3.5">3.5</a>&nbsp;<a href="source/net/ipv4/netfilter/ipt_REJECT.c?v=3.6">3.6</a>&nbsp;<a href="source/net/ipv4/netfilter/ipt_REJECT.c?v=3.7">3.7</a>&nbsp;<a href="source/net/ipv4/netfilter/ipt_REJECT.c?v=3.8">3.8</a>&nbsp;<a href="source/net/ipv4/netfilter/ipt_REJECT.c?v=3.9">3.9</a>&nbsp;<a href="source/net/ipv4/netfilter/ipt_REJECT.c?v=3.10">3.10</a>&nbsp;<a href="source/net/ipv4/netfilter/ipt_REJECT.c?v=3.11">3.11</a>&nbsp;<a href="source/net/ipv4/netfilter/ipt_REJECT.c?v=3.12">3.12</a>&nbsp;<a href="source/net/ipv4/netfilter/ipt_REJECT.c?v=3.13">3.13</a>&nbsp;<a href="source/net/ipv4/netfilter/ipt_REJECT.c?v=3.14">3.14</a>&nbsp;<a href="source/net/ipv4/netfilter/ipt_REJECT.c?v=3.15">3.15</a>&nbsp;<a href="source/net/ipv4/netfilter/ipt_REJECT.c?v=3.16">3.16</a>&nbsp;<a href="source/net/ipv4/netfilter/ipt_REJECT.c?v=3.17">3.17</a>&nbsp;<a href="source/net/ipv4/netfilter/ipt_REJECT.c?v=3.18">3.18</a>&nbsp;<a href="source/net/ipv4/netfilter/ipt_REJECT.c?v=3.19">3.19</a>&nbsp;<a href="source/net/ipv4/netfilter/ipt_REJECT.c?v=4.0">4.0</a>&nbsp;<b><i>4.1</i></b></p>
  
</div>

<h1><a href="source/">Linux</a>/<a href="source/net/">net</a>/<a href="source/net/ipv4/">ipv4</a>/<a href="source/net/ipv4/netfilter/">netfilter</a>/<a href="source/net/ipv4/netfilter/ipt_REJECT.c">ipt_REJECT.c</a></h1>
<div id="lxrcode"><pre>  <a name="L1" href="source/net/ipv4/netfilter/ipt_REJECT.c#L1">1</a> <b><i>/*</i></b>
  <a name="L2" href="source/net/ipv4/netfilter/ipt_REJECT.c#L2">2</a> <b><i> * This is a module which is used for rejecting packets.</i></b>
  <a name="L3" href="source/net/ipv4/netfilter/ipt_REJECT.c#L3">3</a> <b><i> */</i></b>
  <a name="L4" href="source/net/ipv4/netfilter/ipt_REJECT.c#L4">4</a> 
  <a name="L5" href="source/net/ipv4/netfilter/ipt_REJECT.c#L5">5</a> <b><i>/* (C) 1999-2001 Paul `Rusty' Russell</i></b>
  <a name="L6" href="source/net/ipv4/netfilter/ipt_REJECT.c#L6">6</a> <b><i> * (C) 2002-2004 Netfilter Core Team &lt;coreteam@netfilter.org&gt;</i></b>
  <a name="L7" href="source/net/ipv4/netfilter/ipt_REJECT.c#L7">7</a> <b><i> *</i></b>
  <a name="L8" href="source/net/ipv4/netfilter/ipt_REJECT.c#L8">8</a> <b><i> * This program is free software; you can redistribute it and/or modify</i></b>
  <a name="L9" href="source/net/ipv4/netfilter/ipt_REJECT.c#L9">9</a> <b><i> * it under the terms of the GNU General Public License version 2 as</i></b>
 <a name="L10" href="source/net/ipv4/netfilter/ipt_REJECT.c#L10">10</a> <b><i> * published by the Free Software Foundation.</i></b>
 <a name="L11" href="source/net/ipv4/netfilter/ipt_REJECT.c#L11">11</a> <b><i> */</i></b>
 <a name="L12" href="source/net/ipv4/netfilter/ipt_REJECT.c#L12">12</a> #define <a href="ident?i=pr_fmt">pr_fmt</a>(<a href="ident?i=fmt">fmt</a>) KBUILD_MODNAME <i>": "</i> <a href="ident?i=fmt">fmt</a>
 <a name="L13" href="source/net/ipv4/netfilter/ipt_REJECT.c#L13">13</a> #include &lt;linux/module.h&gt;
 <a name="L14" href="source/net/ipv4/netfilter/ipt_REJECT.c#L14">14</a> #include &lt;linux/skbuff.h&gt;
 <a name="L15" href="source/net/ipv4/netfilter/ipt_REJECT.c#L15">15</a> #include &lt;linux/slab.h&gt;
 <a name="L16" href="source/net/ipv4/netfilter/ipt_REJECT.c#L16">16</a> #include &lt;linux/ip.h&gt;
 <a name="L17" href="source/net/ipv4/netfilter/ipt_REJECT.c#L17">17</a> #include &lt;linux/udp.h&gt;
 <a name="L18" href="source/net/ipv4/netfilter/ipt_REJECT.c#L18">18</a> #include &lt;linux/icmp.h&gt;
 <a name="L19" href="source/net/ipv4/netfilter/ipt_REJECT.c#L19">19</a> #include &lt;net/icmp.h&gt;
 <a name="L20" href="source/net/ipv4/netfilter/ipt_REJECT.c#L20">20</a> #include &lt;linux/netfilter/x_tables.h&gt;
 <a name="L21" href="source/net/ipv4/netfilter/ipt_REJECT.c#L21">21</a> #include &lt;linux/netfilter_ipv4/ip_tables.h&gt;
 <a name="L22" href="source/net/ipv4/netfilter/ipt_REJECT.c#L22">22</a> #include &lt;linux/netfilter_ipv4/ipt_REJECT.h&gt;
 <a name="L23" href="source/net/ipv4/netfilter/ipt_REJECT.c#L23">23</a> #if <a href="ident?i=IS_ENABLED">IS_ENABLED</a>(CONFIG_BRIDGE_NETFILTER)
 <a name="L24" href="source/net/ipv4/netfilter/ipt_REJECT.c#L24">24</a> #include &lt;linux/netfilter_bridge.h&gt;
 <a name="L25" href="source/net/ipv4/netfilter/ipt_REJECT.c#L25">25</a> #endif
 <a name="L26" href="source/net/ipv4/netfilter/ipt_REJECT.c#L26">26</a> 
 <a name="L27" href="source/net/ipv4/netfilter/ipt_REJECT.c#L27">27</a> #include &lt;net/netfilter/ipv4/nf_reject.h&gt;
 <a name="L28" href="source/net/ipv4/netfilter/ipt_REJECT.c#L28">28</a> 
 <a name="L29" href="source/net/ipv4/netfilter/ipt_REJECT.c#L29">29</a> <a href="ident?i=MODULE_LICENSE">MODULE_LICENSE</a>(<i>"GPL"</i>);
 <a name="L30" href="source/net/ipv4/netfilter/ipt_REJECT.c#L30">30</a> <a href="ident?i=MODULE_AUTHOR">MODULE_AUTHOR</a>(<i>"Netfilter Core Team &lt;coreteam@netfilter.org&gt;"</i>);
 <a name="L31" href="source/net/ipv4/netfilter/ipt_REJECT.c#L31">31</a> <a href="ident?i=MODULE_DESCRIPTION">MODULE_DESCRIPTION</a>(<i>"Xtables: packet \"rejection\" target for IPv4"</i>);
 <a name="L32" href="source/net/ipv4/netfilter/ipt_REJECT.c#L32">32</a> 
 <a name="L33" href="source/net/ipv4/netfilter/ipt_REJECT.c#L33">33</a> static unsigned int
 <a name="L34" href="source/net/ipv4/netfilter/ipt_REJECT.c#L34">34</a> <a href="ident?i=reject_tg">reject_tg</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, const struct <a href="ident?i=xt_action_param">xt_action_param</a> *<a href="ident?i=par">par</a>)
 <a name="L35" href="source/net/ipv4/netfilter/ipt_REJECT.c#L35">35</a> {
 <a name="L36" href="source/net/ipv4/netfilter/ipt_REJECT.c#L36">36</a>         const struct <a href="ident?i=ipt_reject_info">ipt_reject_info</a> *reject = <a href="ident?i=par">par</a>-&gt;targinfo;
 <a name="L37" href="source/net/ipv4/netfilter/ipt_REJECT.c#L37">37</a>         int hook = <a href="ident?i=par">par</a>-&gt;hooknum;
 <a name="L38" href="source/net/ipv4/netfilter/ipt_REJECT.c#L38">38</a> 
 <a name="L39" href="source/net/ipv4/netfilter/ipt_REJECT.c#L39">39</a>         switch (reject-&gt;with) {
 <a name="L40" href="source/net/ipv4/netfilter/ipt_REJECT.c#L40">40</a>         case IPT_ICMP_NET_UNREACHABLE:
 <a name="L41" href="source/net/ipv4/netfilter/ipt_REJECT.c#L41">41</a>                 <a href="ident?i=nf_send_unreach">nf_send_unreach</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=ICMP_NET_UNREACH">ICMP_NET_UNREACH</a>, hook);
 <a name="L42" href="source/net/ipv4/netfilter/ipt_REJECT.c#L42">42</a>                 break;
 <a name="L43" href="source/net/ipv4/netfilter/ipt_REJECT.c#L43">43</a>         case IPT_ICMP_HOST_UNREACHABLE:
 <a name="L44" href="source/net/ipv4/netfilter/ipt_REJECT.c#L44">44</a>                 <a href="ident?i=nf_send_unreach">nf_send_unreach</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=ICMP_HOST_UNREACH">ICMP_HOST_UNREACH</a>, hook);
 <a name="L45" href="source/net/ipv4/netfilter/ipt_REJECT.c#L45">45</a>                 break;
 <a name="L46" href="source/net/ipv4/netfilter/ipt_REJECT.c#L46">46</a>         case IPT_ICMP_PROT_UNREACHABLE:
 <a name="L47" href="source/net/ipv4/netfilter/ipt_REJECT.c#L47">47</a>                 <a href="ident?i=nf_send_unreach">nf_send_unreach</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=ICMP_PROT_UNREACH">ICMP_PROT_UNREACH</a>, hook);
 <a name="L48" href="source/net/ipv4/netfilter/ipt_REJECT.c#L48">48</a>                 break;
 <a name="L49" href="source/net/ipv4/netfilter/ipt_REJECT.c#L49">49</a>         case IPT_ICMP_PORT_UNREACHABLE:
 <a name="L50" href="source/net/ipv4/netfilter/ipt_REJECT.c#L50">50</a>                 <a href="ident?i=nf_send_unreach">nf_send_unreach</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=ICMP_PORT_UNREACH">ICMP_PORT_UNREACH</a>, hook);
 <a name="L51" href="source/net/ipv4/netfilter/ipt_REJECT.c#L51">51</a>                 break;
 <a name="L52" href="source/net/ipv4/netfilter/ipt_REJECT.c#L52">52</a>         case IPT_ICMP_NET_PROHIBITED:
 <a name="L53" href="source/net/ipv4/netfilter/ipt_REJECT.c#L53">53</a>                 <a href="ident?i=nf_send_unreach">nf_send_unreach</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=ICMP_NET_ANO">ICMP_NET_ANO</a>, hook);
 <a name="L54" href="source/net/ipv4/netfilter/ipt_REJECT.c#L54">54</a>                 break;
 <a name="L55" href="source/net/ipv4/netfilter/ipt_REJECT.c#L55">55</a>         case IPT_ICMP_HOST_PROHIBITED:
 <a name="L56" href="source/net/ipv4/netfilter/ipt_REJECT.c#L56">56</a>                 <a href="ident?i=nf_send_unreach">nf_send_unreach</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=ICMP_HOST_ANO">ICMP_HOST_ANO</a>, hook);
 <a name="L57" href="source/net/ipv4/netfilter/ipt_REJECT.c#L57">57</a>                 break;
 <a name="L58" href="source/net/ipv4/netfilter/ipt_REJECT.c#L58">58</a>         case IPT_ICMP_ADMIN_PROHIBITED:
 <a name="L59" href="source/net/ipv4/netfilter/ipt_REJECT.c#L59">59</a>                 <a href="ident?i=nf_send_unreach">nf_send_unreach</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=ICMP_PKT_FILTERED">ICMP_PKT_FILTERED</a>, hook);
 <a name="L60" href="source/net/ipv4/netfilter/ipt_REJECT.c#L60">60</a>                 break;
 <a name="L61" href="source/net/ipv4/netfilter/ipt_REJECT.c#L61">61</a>         case IPT_TCP_RESET:
 <a name="L62" href="source/net/ipv4/netfilter/ipt_REJECT.c#L62">62</a>                 <a href="ident?i=nf_send_reset">nf_send_reset</a>(<a href="ident?i=skb">skb</a>, hook);
 <a name="L63" href="source/net/ipv4/netfilter/ipt_REJECT.c#L63">63</a>         case IPT_ICMP_ECHOREPLY:
 <a name="L64" href="source/net/ipv4/netfilter/ipt_REJECT.c#L64">64</a>                 <b><i>/* Doesn't happen. */</i></b>
 <a name="L65" href="source/net/ipv4/netfilter/ipt_REJECT.c#L65">65</a>                 break;
 <a name="L66" href="source/net/ipv4/netfilter/ipt_REJECT.c#L66">66</a>         }
 <a name="L67" href="source/net/ipv4/netfilter/ipt_REJECT.c#L67">67</a> 
 <a name="L68" href="source/net/ipv4/netfilter/ipt_REJECT.c#L68">68</a>         return <a href="ident?i=NF_DROP">NF_DROP</a>;
 <a name="L69" href="source/net/ipv4/netfilter/ipt_REJECT.c#L69">69</a> }
 <a name="L70" href="source/net/ipv4/netfilter/ipt_REJECT.c#L70">70</a> 
 <a name="L71" href="source/net/ipv4/netfilter/ipt_REJECT.c#L71">71</a> static int <a href="ident?i=reject_tg_check">reject_tg_check</a>(const struct <a href="ident?i=xt_tgchk_param">xt_tgchk_param</a> *<a href="ident?i=par">par</a>)
 <a name="L72" href="source/net/ipv4/netfilter/ipt_REJECT.c#L72">72</a> {
 <a name="L73" href="source/net/ipv4/netfilter/ipt_REJECT.c#L73">73</a>         const struct <a href="ident?i=ipt_reject_info">ipt_reject_info</a> *rejinfo = <a href="ident?i=par">par</a>-&gt;targinfo;
 <a name="L74" href="source/net/ipv4/netfilter/ipt_REJECT.c#L74">74</a>         const struct <a href="ident?i=ipt_entry">ipt_entry</a> *<a href="ident?i=e">e</a> = <a href="ident?i=par">par</a>-&gt;entryinfo;
 <a name="L75" href="source/net/ipv4/netfilter/ipt_REJECT.c#L75">75</a> 
 <a name="L76" href="source/net/ipv4/netfilter/ipt_REJECT.c#L76">76</a>         if (rejinfo-&gt;with == IPT_ICMP_ECHOREPLY) {
 <a name="L77" href="source/net/ipv4/netfilter/ipt_REJECT.c#L77">77</a>                 <a href="ident?i=pr_info">pr_info</a>(<i>"ECHOREPLY no longer supported.\n"</i>);
 <a name="L78" href="source/net/ipv4/netfilter/ipt_REJECT.c#L78">78</a>                 return -<a href="ident?i=EINVAL">EINVAL</a>;
 <a name="L79" href="source/net/ipv4/netfilter/ipt_REJECT.c#L79">79</a>         } else if (rejinfo-&gt;with == IPT_TCP_RESET) {
 <a name="L80" href="source/net/ipv4/netfilter/ipt_REJECT.c#L80">80</a>                 <b><i>/* Must specify that it's a TCP packet */</i></b>
 <a name="L81" href="source/net/ipv4/netfilter/ipt_REJECT.c#L81">81</a>                 if (<a href="ident?i=e">e</a>-&gt;<a href="ident?i=ip">ip</a>.<a href="ident?i=proto">proto</a> != <a href="ident?i=IPPROTO_TCP">IPPROTO_TCP</a> ||
 <a name="L82" href="source/net/ipv4/netfilter/ipt_REJECT.c#L82">82</a>                     (<a href="ident?i=e">e</a>-&gt;<a href="ident?i=ip">ip</a>.invflags &amp; <a href="ident?i=XT_INV_PROTO">XT_INV_PROTO</a>)) {
 <a name="L83" href="source/net/ipv4/netfilter/ipt_REJECT.c#L83">83</a>                         <a href="ident?i=pr_info">pr_info</a>(<i>"TCP_RESET invalid for non-tcp\n"</i>);
 <a name="L84" href="source/net/ipv4/netfilter/ipt_REJECT.c#L84">84</a>                         return -<a href="ident?i=EINVAL">EINVAL</a>;
 <a name="L85" href="source/net/ipv4/netfilter/ipt_REJECT.c#L85">85</a>                 }
 <a name="L86" href="source/net/ipv4/netfilter/ipt_REJECT.c#L86">86</a>         }
 <a name="L87" href="source/net/ipv4/netfilter/ipt_REJECT.c#L87">87</a>         return 0;
 <a name="L88" href="source/net/ipv4/netfilter/ipt_REJECT.c#L88">88</a> }
 <a name="L89" href="source/net/ipv4/netfilter/ipt_REJECT.c#L89">89</a> 
 <a name="L90" href="source/net/ipv4/netfilter/ipt_REJECT.c#L90">90</a> static struct <a href="ident?i=xt_target">xt_target</a> reject_tg_reg <a href="ident?i=__read_mostly">__read_mostly</a> = {
 <a name="L91" href="source/net/ipv4/netfilter/ipt_REJECT.c#L91">91</a>         .<a href="ident?i=name">name</a>           = <i>"REJECT"</i>,
 <a name="L92" href="source/net/ipv4/netfilter/ipt_REJECT.c#L92">92</a>         .<a href="ident?i=family">family</a>         = NFPROTO_IPV4,
 <a name="L93" href="source/net/ipv4/netfilter/ipt_REJECT.c#L93">93</a>         .<a href="ident?i=target">target</a>         = <a href="ident?i=reject_tg">reject_tg</a>,
 <a name="L94" href="source/net/ipv4/netfilter/ipt_REJECT.c#L94">94</a>         .targetsize     = sizeof(struct <a href="ident?i=ipt_reject_info">ipt_reject_info</a>),
 <a name="L95" href="source/net/ipv4/netfilter/ipt_REJECT.c#L95">95</a>         .<a href="ident?i=table">table</a>          = <i>"filter"</i>,
 <a name="L96" href="source/net/ipv4/netfilter/ipt_REJECT.c#L96">96</a>         .<a href="ident?i=hooks">hooks</a>          = (1 &lt;&lt; NF_INET_LOCAL_IN) | (1 &lt;&lt; NF_INET_FORWARD) |
 <a name="L97" href="source/net/ipv4/netfilter/ipt_REJECT.c#L97">97</a>                           (1 &lt;&lt; NF_INET_LOCAL_OUT),
 <a name="L98" href="source/net/ipv4/netfilter/ipt_REJECT.c#L98">98</a>         .<a href="ident?i=checkentry">checkentry</a>     = <a href="ident?i=reject_tg_check">reject_tg_check</a>,
 <a name="L99" href="source/net/ipv4/netfilter/ipt_REJECT.c#L99">99</a>         .<a href="ident?i=me">me</a>             = <a href="ident?i=THIS_MODULE">THIS_MODULE</a>,
<a name="L100" href="source/net/ipv4/netfilter/ipt_REJECT.c#L100">100</a> };
<a name="L101" href="source/net/ipv4/netfilter/ipt_REJECT.c#L101">101</a> 
<a name="L102" href="source/net/ipv4/netfilter/ipt_REJECT.c#L102">102</a> static int <a href="ident?i=__init">__init</a> <a href="ident?i=reject_tg_init">reject_tg_init</a>(void)
<a name="L103" href="source/net/ipv4/netfilter/ipt_REJECT.c#L103">103</a> {
<a name="L104" href="source/net/ipv4/netfilter/ipt_REJECT.c#L104">104</a>         return <a href="ident?i=xt_register_target">xt_register_target</a>(&amp;reject_tg_reg);
<a name="L105" href="source/net/ipv4/netfilter/ipt_REJECT.c#L105">105</a> }
<a name="L106" href="source/net/ipv4/netfilter/ipt_REJECT.c#L106">106</a> 
<a name="L107" href="source/net/ipv4/netfilter/ipt_REJECT.c#L107">107</a> static void <a href="ident?i=__exit">__exit</a> <a href="ident?i=reject_tg_exit">reject_tg_exit</a>(void)
<a name="L108" href="source/net/ipv4/netfilter/ipt_REJECT.c#L108">108</a> {
<a name="L109" href="source/net/ipv4/netfilter/ipt_REJECT.c#L109">109</a>         <a href="ident?i=xt_unregister_target">xt_unregister_target</a>(&amp;reject_tg_reg);
<a name="L110" href="source/net/ipv4/netfilter/ipt_REJECT.c#L110">110</a> }
<a name="L111" href="source/net/ipv4/netfilter/ipt_REJECT.c#L111">111</a> 
<a name="L112" href="source/net/ipv4/netfilter/ipt_REJECT.c#L112">112</a> <a href="ident?i=module_init">module_init</a>(<a href="ident?i=reject_tg_init">reject_tg_init</a>);
<a name="L113" href="source/net/ipv4/netfilter/ipt_REJECT.c#L113">113</a> <a href="ident?i=module_exit">module_exit</a>(<a href="ident?i=reject_tg_exit">reject_tg_exit</a>);
<a name="L114" href="source/net/ipv4/netfilter/ipt_REJECT.c#L114">114</a> </pre></div><p>
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
