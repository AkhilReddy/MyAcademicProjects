<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title>Linux/net/ipv4/netfilter/ipt_rpfilter.c - Linux Cross Reference - Free Electrons</title>
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
		 &nbsp;&bull;&nbsp;<b><i>source navigation</i></b> &nbsp;&bull;&nbsp;<a href="diff/net/ipv4/netfilter/ipt_rpfilter.c">diff markup</a> &nbsp;&bull;&nbsp;<a href="ident">identifier search</a> &nbsp;&bull;&nbsp;<a href="search">freetext search</a> &nbsp;&bull;&nbsp;
		</p>
	</div>
</div>

<div id="topbar">
  
  <p>Version: &nbsp;<a href="source/net/ipv4/netfilter/ipt_rpfilter.c?v=2.0.40">2.0.40</a>&nbsp;<a href="source/net/ipv4/netfilter/ipt_rpfilter.c?v=2.2.26">2.2.26</a>&nbsp;<a href="source/net/ipv4/netfilter/ipt_rpfilter.c?v=2.4.37">2.4.37</a>&nbsp;<a href="source/net/ipv4/netfilter/ipt_rpfilter.c?v=3.5">3.5</a>&nbsp;<a href="source/net/ipv4/netfilter/ipt_rpfilter.c?v=3.6">3.6</a>&nbsp;<a href="source/net/ipv4/netfilter/ipt_rpfilter.c?v=3.7">3.7</a>&nbsp;<a href="source/net/ipv4/netfilter/ipt_rpfilter.c?v=3.8">3.8</a>&nbsp;<a href="source/net/ipv4/netfilter/ipt_rpfilter.c?v=3.9">3.9</a>&nbsp;<a href="source/net/ipv4/netfilter/ipt_rpfilter.c?v=3.10">3.10</a>&nbsp;<a href="source/net/ipv4/netfilter/ipt_rpfilter.c?v=3.11">3.11</a>&nbsp;<a href="source/net/ipv4/netfilter/ipt_rpfilter.c?v=3.12">3.12</a>&nbsp;<a href="source/net/ipv4/netfilter/ipt_rpfilter.c?v=3.13">3.13</a>&nbsp;<a href="source/net/ipv4/netfilter/ipt_rpfilter.c?v=3.14">3.14</a>&nbsp;<a href="source/net/ipv4/netfilter/ipt_rpfilter.c?v=3.15">3.15</a>&nbsp;<a href="source/net/ipv4/netfilter/ipt_rpfilter.c?v=3.16">3.16</a>&nbsp;<a href="source/net/ipv4/netfilter/ipt_rpfilter.c?v=3.17">3.17</a>&nbsp;<a href="source/net/ipv4/netfilter/ipt_rpfilter.c?v=3.18">3.18</a>&nbsp;<a href="source/net/ipv4/netfilter/ipt_rpfilter.c?v=3.19">3.19</a>&nbsp;<a href="source/net/ipv4/netfilter/ipt_rpfilter.c?v=4.0">4.0</a>&nbsp;<b><i>4.1</i></b></p>
  
</div>

<h1><a href="source/">Linux</a>/<a href="source/net/">net</a>/<a href="source/net/ipv4/">ipv4</a>/<a href="source/net/ipv4/netfilter/">netfilter</a>/<a href="source/net/ipv4/netfilter/ipt_rpfilter.c">ipt_rpfilter.c</a></h1>
<div id="lxrcode"><pre>  <a name="L1" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L1">1</a> <b><i>/*</i></b>
  <a name="L2" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L2">2</a> <b><i> * Copyright (c) 2011 Florian Westphal &lt;fw@strlen.de&gt;</i></b>
  <a name="L3" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L3">3</a> <b><i> *</i></b>
  <a name="L4" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L4">4</a> <b><i> * This program is free software; you can redistribute it and/or modify</i></b>
  <a name="L5" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L5">5</a> <b><i> * it under the terms of the GNU General Public License version 2 as</i></b>
  <a name="L6" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L6">6</a> <b><i> * published by the Free Software Foundation.</i></b>
  <a name="L7" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L7">7</a> <b><i> *</i></b>
  <a name="L8" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L8">8</a> <b><i> * based on fib_frontend.c; Author: Alexey Kuznetsov, &lt;kuznet@ms2.inr.ac.ru&gt;</i></b>
  <a name="L9" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L9">9</a> <b><i> */</i></b>
 <a name="L10" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L10">10</a> #define <a href="ident?i=pr_fmt">pr_fmt</a>(<a href="ident?i=fmt">fmt</a>) KBUILD_MODNAME <i>": "</i> <a href="ident?i=fmt">fmt</a>
 <a name="L11" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L11">11</a> #include &lt;linux/module.h&gt;
 <a name="L12" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L12">12</a> #include &lt;linux/skbuff.h&gt;
 <a name="L13" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L13">13</a> #include &lt;linux/netdevice.h&gt;
 <a name="L14" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L14">14</a> #include &lt;linux/ip.h&gt;
 <a name="L15" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L15">15</a> #include &lt;net/ip.h&gt;
 <a name="L16" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L16">16</a> #include &lt;net/ip_fib.h&gt;
 <a name="L17" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L17">17</a> #include &lt;net/route.h&gt;
 <a name="L18" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L18">18</a> 
 <a name="L19" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L19">19</a> #include &lt;linux/netfilter/xt_rpfilter.h&gt;
 <a name="L20" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L20">20</a> #include &lt;linux/netfilter/x_tables.h&gt;
 <a name="L21" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L21">21</a> 
 <a name="L22" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L22">22</a> <a href="ident?i=MODULE_LICENSE">MODULE_LICENSE</a>(<i>"GPL"</i>);
 <a name="L23" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L23">23</a> <a href="ident?i=MODULE_AUTHOR">MODULE_AUTHOR</a>(<i>"Florian Westphal &lt;fw@strlen.de&gt;"</i>);
 <a name="L24" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L24">24</a> <a href="ident?i=MODULE_DESCRIPTION">MODULE_DESCRIPTION</a>(<i>"iptables: ipv4 reverse path filter match"</i>);
 <a name="L25" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L25">25</a> 
 <a name="L26" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L26">26</a> <b><i>/* don't try to find route from mcast/bcast/zeronet */</i></b>
 <a name="L27" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L27">27</a> static <a href="ident?i=__be32">__be32</a> <a href="ident?i=rpfilter_get_saddr">rpfilter_get_saddr</a>(<a href="ident?i=__be32">__be32</a> <a href="ident?i=addr">addr</a>)
 <a name="L28" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L28">28</a> {
 <a name="L29" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L29">29</a>         if (<a href="ident?i=ipv4_is_multicast">ipv4_is_multicast</a>(<a href="ident?i=addr">addr</a>) || <a href="ident?i=ipv4_is_lbcast">ipv4_is_lbcast</a>(<a href="ident?i=addr">addr</a>) ||
 <a name="L30" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L30">30</a>             <a href="ident?i=ipv4_is_zeronet">ipv4_is_zeronet</a>(<a href="ident?i=addr">addr</a>))
 <a name="L31" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L31">31</a>                 return 0;
 <a name="L32" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L32">32</a>         return <a href="ident?i=addr">addr</a>;
 <a name="L33" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L33">33</a> }
 <a name="L34" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L34">34</a> 
 <a name="L35" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L35">35</a> static <a href="ident?i=bool">bool</a> <a href="ident?i=rpfilter_lookup_reverse">rpfilter_lookup_reverse</a>(struct <a href="ident?i=flowi4">flowi4</a> *fl4,
 <a name="L36" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L36">36</a>                                 const struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>, <a href="ident?i=u8">u8</a> <a href="ident?i=flags">flags</a>)
 <a name="L37" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L37">37</a> {
 <a name="L38" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L38">38</a>         struct <a href="ident?i=fib_result">fib_result</a> <a href="ident?i=res">res</a>;
 <a name="L39" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L39">39</a>         <a href="ident?i=bool">bool</a> dev_match;
 <a name="L40" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L40">40</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=dev">dev</a>);
 <a name="L41" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L41">41</a>         int <a href="ident?i=ret">ret</a> <a href="ident?i=__maybe_unused">__maybe_unused</a>;
 <a name="L42" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L42">42</a> 
 <a name="L43" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L43">43</a>         if (<a href="ident?i=fib_lookup">fib_lookup</a>(<a href="ident?i=net">net</a>, fl4, &amp;<a href="ident?i=res">res</a>))
 <a name="L44" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L44">44</a>                 return <a href="ident?i=false">false</a>;
 <a name="L45" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L45">45</a> 
 <a name="L46" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L46">46</a>         if (<a href="ident?i=res">res</a>.<a href="ident?i=type">type</a> != RTN_UNICAST) {
 <a name="L47" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L47">47</a>                 if (<a href="ident?i=res">res</a>.<a href="ident?i=type">type</a> != RTN_LOCAL || !(<a href="ident?i=flags">flags</a> &amp; XT_RPFILTER_ACCEPT_LOCAL))
 <a name="L48" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L48">48</a>                         return <a href="ident?i=false">false</a>;
 <a name="L49" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L49">49</a>         }
 <a name="L50" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L50">50</a>         dev_match = <a href="ident?i=false">false</a>;
 <a name="L51" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L51">51</a> #ifdef CONFIG_IP_ROUTE_MULTIPATH
 <a name="L52" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L52">52</a>         for (<a href="ident?i=ret">ret</a> = 0; <a href="ident?i=ret">ret</a> &lt; <a href="ident?i=res">res</a>.fi-&gt;fib_nhs; <a href="ident?i=ret">ret</a>++) {
 <a name="L53" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L53">53</a>                 struct <a href="ident?i=fib_nh">fib_nh</a> *nh = &amp;<a href="ident?i=res">res</a>.fi-&gt;<a href="ident?i=fib_nh">fib_nh</a>[<a href="ident?i=ret">ret</a>];
 <a name="L54" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L54">54</a> 
 <a name="L55" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L55">55</a>                 if (nh-&gt;nh_dev == <a href="ident?i=dev">dev</a>) {
 <a name="L56" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L56">56</a>                         dev_match = <a href="ident?i=true">true</a>;
 <a name="L57" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L57">57</a>                         break;
 <a name="L58" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L58">58</a>                 }
 <a name="L59" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L59">59</a>         }
 <a name="L60" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L60">60</a> #else
 <a name="L61" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L61">61</a>         if (<a href="ident?i=FIB_RES_DEV">FIB_RES_DEV</a>(<a href="ident?i=res">res</a>) == <a href="ident?i=dev">dev</a>)
 <a name="L62" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L62">62</a>                 dev_match = <a href="ident?i=true">true</a>;
 <a name="L63" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L63">63</a> #endif
 <a name="L64" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L64">64</a>         if (dev_match || <a href="ident?i=flags">flags</a> &amp; XT_RPFILTER_LOOSE)
 <a name="L65" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L65">65</a>                 return <a href="ident?i=FIB_RES_NH">FIB_RES_NH</a>(<a href="ident?i=res">res</a>).nh_scope &lt;= RT_SCOPE_HOST;
 <a name="L66" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L66">66</a>         return dev_match;
 <a name="L67" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L67">67</a> }
 <a name="L68" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L68">68</a> 
 <a name="L69" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L69">69</a> static <a href="ident?i=bool">bool</a> <a href="ident?i=rpfilter_is_local">rpfilter_is_local</a>(const struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
 <a name="L70" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L70">70</a> {
 <a name="L71" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L71">71</a>         const struct <a href="ident?i=rtable">rtable</a> *<a href="ident?i=rt">rt</a> = <a href="ident?i=skb_rtable">skb_rtable</a>(<a href="ident?i=skb">skb</a>);
 <a name="L72" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L72">72</a>         return <a href="ident?i=rt">rt</a> &amp;&amp; (<a href="ident?i=rt">rt</a>-&gt;rt_flags &amp; <a href="ident?i=RTCF_LOCAL">RTCF_LOCAL</a>);
 <a name="L73" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L73">73</a> }
 <a name="L74" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L74">74</a> 
 <a name="L75" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L75">75</a> static <a href="ident?i=bool">bool</a> <a href="ident?i=rpfilter_mt">rpfilter_mt</a>(const struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, struct <a href="ident?i=xt_action_param">xt_action_param</a> *<a href="ident?i=par">par</a>)
 <a name="L76" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L76">76</a> {
 <a name="L77" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L77">77</a>         const struct <a href="ident?i=xt_rpfilter_info">xt_rpfilter_info</a> *<a href="ident?i=info">info</a>;
 <a name="L78" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L78">78</a>         const struct <a href="ident?i=iphdr">iphdr</a> *iph;
 <a name="L79" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L79">79</a>         struct <a href="ident?i=flowi4">flowi4</a> <a href="ident?i=flow">flow</a>;
 <a name="L80" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L80">80</a>         <a href="ident?i=bool">bool</a> <a href="ident?i=invert">invert</a>;
 <a name="L81" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L81">81</a> 
 <a name="L82" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L82">82</a>         <a href="ident?i=info">info</a> = <a href="ident?i=par">par</a>-&gt;matchinfo;
 <a name="L83" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L83">83</a>         <a href="ident?i=invert">invert</a> = <a href="ident?i=info">info</a>-&gt;<a href="ident?i=flags">flags</a> &amp; XT_RPFILTER_INVERT;
 <a name="L84" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L84">84</a> 
 <a name="L85" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L85">85</a>         if (<a href="ident?i=rpfilter_is_local">rpfilter_is_local</a>(<a href="ident?i=skb">skb</a>))
 <a name="L86" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L86">86</a>                 return <a href="ident?i=true">true</a> ^ <a href="ident?i=invert">invert</a>;
 <a name="L87" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L87">87</a> 
 <a name="L88" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L88">88</a>         iph = <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>);
 <a name="L89" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L89">89</a>         if (<a href="ident?i=ipv4_is_multicast">ipv4_is_multicast</a>(iph-&gt;<a href="ident?i=daddr">daddr</a>)) {
 <a name="L90" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L90">90</a>                 if (<a href="ident?i=ipv4_is_zeronet">ipv4_is_zeronet</a>(iph-&gt;<a href="ident?i=saddr">saddr</a>))
 <a name="L91" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L91">91</a>                         return <a href="ident?i=ipv4_is_local_multicast">ipv4_is_local_multicast</a>(iph-&gt;<a href="ident?i=daddr">daddr</a>) ^ <a href="ident?i=invert">invert</a>;
 <a name="L92" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L92">92</a>         }
 <a name="L93" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L93">93</a>         <a href="ident?i=flow">flow</a>.<a href="ident?i=flowi4_iif">flowi4_iif</a> = <a href="ident?i=LOOPBACK_IFINDEX">LOOPBACK_IFINDEX</a>;
 <a name="L94" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L94">94</a>         <a href="ident?i=flow">flow</a>.<a href="ident?i=daddr">daddr</a> = iph-&gt;<a href="ident?i=saddr">saddr</a>;
 <a name="L95" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L95">95</a>         <a href="ident?i=flow">flow</a>.<a href="ident?i=saddr">saddr</a> = <a href="ident?i=rpfilter_get_saddr">rpfilter_get_saddr</a>(iph-&gt;<a href="ident?i=daddr">daddr</a>);
 <a name="L96" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L96">96</a>         <a href="ident?i=flow">flow</a>.<a href="ident?i=flowi4_oif">flowi4_oif</a> = 0;
 <a name="L97" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L97">97</a>         <a href="ident?i=flow">flow</a>.<a href="ident?i=flowi4_mark">flowi4_mark</a> = <a href="ident?i=info">info</a>-&gt;<a href="ident?i=flags">flags</a> &amp; XT_RPFILTER_VALID_MARK ? <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=mark">mark</a> : 0;
 <a name="L98" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L98">98</a>         <a href="ident?i=flow">flow</a>.<a href="ident?i=flowi4_tos">flowi4_tos</a> = <a href="ident?i=RT_TOS">RT_TOS</a>(iph-&gt;tos);
 <a name="L99" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L99">99</a>         <a href="ident?i=flow">flow</a>.<a href="ident?i=flowi4_scope">flowi4_scope</a> = RT_SCOPE_UNIVERSE;
<a name="L100" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L100">100</a> 
<a name="L101" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L101">101</a>         return <a href="ident?i=rpfilter_lookup_reverse">rpfilter_lookup_reverse</a>(&amp;<a href="ident?i=flow">flow</a>, <a href="ident?i=par">par</a>-&gt;<a href="ident?i=in">in</a>, <a href="ident?i=info">info</a>-&gt;<a href="ident?i=flags">flags</a>) ^ <a href="ident?i=invert">invert</a>;
<a name="L102" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L102">102</a> }
<a name="L103" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L103">103</a> 
<a name="L104" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L104">104</a> static int <a href="ident?i=rpfilter_check">rpfilter_check</a>(const struct <a href="ident?i=xt_mtchk_param">xt_mtchk_param</a> *<a href="ident?i=par">par</a>)
<a name="L105" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L105">105</a> {
<a name="L106" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L106">106</a>         const struct <a href="ident?i=xt_rpfilter_info">xt_rpfilter_info</a> *<a href="ident?i=info">info</a> = <a href="ident?i=par">par</a>-&gt;matchinfo;
<a name="L107" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L107">107</a>         unsigned int <a href="ident?i=options">options</a> = ~XT_RPFILTER_OPTION_MASK;
<a name="L108" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L108">108</a>         if (<a href="ident?i=info">info</a>-&gt;<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=options">options</a>) {
<a name="L109" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L109">109</a>                 <a href="ident?i=pr_info">pr_info</a>(<i>"unknown options encountered"</i>);
<a name="L110" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L110">110</a>                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L111" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L111">111</a>         }
<a name="L112" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L112">112</a> 
<a name="L113" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L113">113</a>         if (<a href="ident?i=strcmp">strcmp</a>(<a href="ident?i=par">par</a>-&gt;<a href="ident?i=table">table</a>, <i>"mangle"</i>) != 0 &amp;&amp;
<a name="L114" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L114">114</a>             <a href="ident?i=strcmp">strcmp</a>(<a href="ident?i=par">par</a>-&gt;<a href="ident?i=table">table</a>, <i>"raw"</i>) != 0) {
<a name="L115" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L115">115</a>                 <a href="ident?i=pr_info">pr_info</a>(<i>"match only valid in the \'raw\' "</i>
<a name="L116" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L116">116</a>                         <i>"or \'mangle\' tables, not \'%s\'.\n"</i>, <a href="ident?i=par">par</a>-&gt;<a href="ident?i=table">table</a>);
<a name="L117" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L117">117</a>                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L118" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L118">118</a>         }
<a name="L119" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L119">119</a> 
<a name="L120" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L120">120</a>         return 0;
<a name="L121" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L121">121</a> }
<a name="L122" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L122">122</a> 
<a name="L123" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L123">123</a> static struct <a href="ident?i=xt_match">xt_match</a> rpfilter_mt_reg <a href="ident?i=__read_mostly">__read_mostly</a> = {
<a name="L124" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L124">124</a>         .<a href="ident?i=name">name</a>           = <i>"rpfilter"</i>,
<a name="L125" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L125">125</a>         .<a href="ident?i=family">family</a>         = NFPROTO_IPV4,
<a name="L126" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L126">126</a>         .<a href="ident?i=checkentry">checkentry</a>     = <a href="ident?i=rpfilter_check">rpfilter_check</a>,
<a name="L127" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L127">127</a>         .<a href="ident?i=match">match</a>          = <a href="ident?i=rpfilter_mt">rpfilter_mt</a>,
<a name="L128" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L128">128</a>         .matchsize      = sizeof(struct <a href="ident?i=xt_rpfilter_info">xt_rpfilter_info</a>),
<a name="L129" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L129">129</a>         .<a href="ident?i=hooks">hooks</a>          = (1 &lt;&lt; NF_INET_PRE_ROUTING),
<a name="L130" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L130">130</a>         .<a href="ident?i=me">me</a>             = <a href="ident?i=THIS_MODULE">THIS_MODULE</a>
<a name="L131" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L131">131</a> };
<a name="L132" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L132">132</a> 
<a name="L133" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L133">133</a> static int <a href="ident?i=__init">__init</a> <a href="ident?i=rpfilter_mt_init">rpfilter_mt_init</a>(void)
<a name="L134" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L134">134</a> {
<a name="L135" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L135">135</a>         return <a href="ident?i=xt_register_match">xt_register_match</a>(&amp;rpfilter_mt_reg);
<a name="L136" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L136">136</a> }
<a name="L137" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L137">137</a> 
<a name="L138" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L138">138</a> static void <a href="ident?i=__exit">__exit</a> <a href="ident?i=rpfilter_mt_exit">rpfilter_mt_exit</a>(void)
<a name="L139" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L139">139</a> {
<a name="L140" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L140">140</a>         <a href="ident?i=xt_unregister_match">xt_unregister_match</a>(&amp;rpfilter_mt_reg);
<a name="L141" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L141">141</a> }
<a name="L142" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L142">142</a> 
<a name="L143" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L143">143</a> <a href="ident?i=module_init">module_init</a>(<a href="ident?i=rpfilter_mt_init">rpfilter_mt_init</a>);
<a name="L144" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L144">144</a> <a href="ident?i=module_exit">module_exit</a>(<a href="ident?i=rpfilter_mt_exit">rpfilter_mt_exit</a>);
<a name="L145" href="source/net/ipv4/netfilter/ipt_rpfilter.c#L145">145</a> </pre></div><p>
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
