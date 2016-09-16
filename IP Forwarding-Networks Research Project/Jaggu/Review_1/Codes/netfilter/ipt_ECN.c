<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title>Linux/net/ipv4/netfilter/ipt_ECN.c - Linux Cross Reference - Free Electrons</title>
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
		 &nbsp;&bull;&nbsp;<b><i>source navigation</i></b> &nbsp;&bull;&nbsp;<a href="diff/net/ipv4/netfilter/ipt_ECN.c">diff markup</a> &nbsp;&bull;&nbsp;<a href="ident">identifier search</a> &nbsp;&bull;&nbsp;<a href="search">freetext search</a> &nbsp;&bull;&nbsp;
		</p>
	</div>
</div>

<div id="topbar">
  
  <p>Version: &nbsp;<a href="source/net/ipv4/netfilter/ipt_ECN.c?v=2.0.40">2.0.40</a>&nbsp;<a href="source/net/ipv4/netfilter/ipt_ECN.c?v=2.2.26">2.2.26</a>&nbsp;<a href="source/net/ipv4/netfilter/ipt_ECN.c?v=2.4.37">2.4.37</a>&nbsp;<a href="source/net/ipv4/netfilter/ipt_ECN.c?v=3.5">3.5</a>&nbsp;<a href="source/net/ipv4/netfilter/ipt_ECN.c?v=3.6">3.6</a>&nbsp;<a href="source/net/ipv4/netfilter/ipt_ECN.c?v=3.7">3.7</a>&nbsp;<a href="source/net/ipv4/netfilter/ipt_ECN.c?v=3.8">3.8</a>&nbsp;<a href="source/net/ipv4/netfilter/ipt_ECN.c?v=3.9">3.9</a>&nbsp;<a href="source/net/ipv4/netfilter/ipt_ECN.c?v=3.10">3.10</a>&nbsp;<a href="source/net/ipv4/netfilter/ipt_ECN.c?v=3.11">3.11</a>&nbsp;<a href="source/net/ipv4/netfilter/ipt_ECN.c?v=3.12">3.12</a>&nbsp;<a href="source/net/ipv4/netfilter/ipt_ECN.c?v=3.13">3.13</a>&nbsp;<a href="source/net/ipv4/netfilter/ipt_ECN.c?v=3.14">3.14</a>&nbsp;<a href="source/net/ipv4/netfilter/ipt_ECN.c?v=3.15">3.15</a>&nbsp;<a href="source/net/ipv4/netfilter/ipt_ECN.c?v=3.16">3.16</a>&nbsp;<a href="source/net/ipv4/netfilter/ipt_ECN.c?v=3.17">3.17</a>&nbsp;<a href="source/net/ipv4/netfilter/ipt_ECN.c?v=3.18">3.18</a>&nbsp;<a href="source/net/ipv4/netfilter/ipt_ECN.c?v=3.19">3.19</a>&nbsp;<a href="source/net/ipv4/netfilter/ipt_ECN.c?v=4.0">4.0</a>&nbsp;<b><i>4.1</i></b></p>
  
</div>

<h1><a href="source/">Linux</a>/<a href="source/net/">net</a>/<a href="source/net/ipv4/">ipv4</a>/<a href="source/net/ipv4/netfilter/">netfilter</a>/<a href="source/net/ipv4/netfilter/ipt_ECN.c">ipt_ECN.c</a></h1>
<div id="lxrcode"><pre>  <a name="L1" href="source/net/ipv4/netfilter/ipt_ECN.c#L1">1</a> <b><i>/* iptables module for the IPv4 and TCP ECN bits, Version 1.5</i></b>
  <a name="L2" href="source/net/ipv4/netfilter/ipt_ECN.c#L2">2</a> <b><i> *</i></b>
  <a name="L3" href="source/net/ipv4/netfilter/ipt_ECN.c#L3">3</a> <b><i> * (C) 2002 by Harald Welte &lt;laforge@netfilter.org&gt;</i></b>
  <a name="L4" href="source/net/ipv4/netfilter/ipt_ECN.c#L4">4</a> <b><i> *</i></b>
  <a name="L5" href="source/net/ipv4/netfilter/ipt_ECN.c#L5">5</a> <b><i> * This program is free software; you can redistribute it and/or modify</i></b>
  <a name="L6" href="source/net/ipv4/netfilter/ipt_ECN.c#L6">6</a> <b><i> * it under the terms of the GNU General Public License version 2 as</i></b>
  <a name="L7" href="source/net/ipv4/netfilter/ipt_ECN.c#L7">7</a> <b><i> * published by the Free Software Foundation.</i></b>
  <a name="L8" href="source/net/ipv4/netfilter/ipt_ECN.c#L8">8</a> <b><i>*/</i></b>
  <a name="L9" href="source/net/ipv4/netfilter/ipt_ECN.c#L9">9</a> #define <a href="ident?i=pr_fmt">pr_fmt</a>(<a href="ident?i=fmt">fmt</a>) KBUILD_MODNAME <i>": "</i> <a href="ident?i=fmt">fmt</a>
 <a name="L10" href="source/net/ipv4/netfilter/ipt_ECN.c#L10">10</a> #include &lt;linux/in.h&gt;
 <a name="L11" href="source/net/ipv4/netfilter/ipt_ECN.c#L11">11</a> #include &lt;linux/module.h&gt;
 <a name="L12" href="source/net/ipv4/netfilter/ipt_ECN.c#L12">12</a> #include &lt;linux/skbuff.h&gt;
 <a name="L13" href="source/net/ipv4/netfilter/ipt_ECN.c#L13">13</a> #include &lt;linux/ip.h&gt;
 <a name="L14" href="source/net/ipv4/netfilter/ipt_ECN.c#L14">14</a> #include &lt;net/ip.h&gt;
 <a name="L15" href="source/net/ipv4/netfilter/ipt_ECN.c#L15">15</a> #include &lt;linux/tcp.h&gt;
 <a name="L16" href="source/net/ipv4/netfilter/ipt_ECN.c#L16">16</a> #include &lt;net/checksum.h&gt;
 <a name="L17" href="source/net/ipv4/netfilter/ipt_ECN.c#L17">17</a> 
 <a name="L18" href="source/net/ipv4/netfilter/ipt_ECN.c#L18">18</a> #include &lt;linux/netfilter/x_tables.h&gt;
 <a name="L19" href="source/net/ipv4/netfilter/ipt_ECN.c#L19">19</a> #include &lt;linux/netfilter_ipv4/ip_tables.h&gt;
 <a name="L20" href="source/net/ipv4/netfilter/ipt_ECN.c#L20">20</a> #include &lt;linux/netfilter_ipv4/ipt_ECN.h&gt;
 <a name="L21" href="source/net/ipv4/netfilter/ipt_ECN.c#L21">21</a> 
 <a name="L22" href="source/net/ipv4/netfilter/ipt_ECN.c#L22">22</a> <a href="ident?i=MODULE_LICENSE">MODULE_LICENSE</a>(<i>"GPL"</i>);
 <a name="L23" href="source/net/ipv4/netfilter/ipt_ECN.c#L23">23</a> <a href="ident?i=MODULE_AUTHOR">MODULE_AUTHOR</a>(<i>"Harald Welte &lt;laforge@netfilter.org&gt;"</i>);
 <a name="L24" href="source/net/ipv4/netfilter/ipt_ECN.c#L24">24</a> <a href="ident?i=MODULE_DESCRIPTION">MODULE_DESCRIPTION</a>(<i>"Xtables: Explicit Congestion Notification (ECN) flag modification"</i>);
 <a name="L25" href="source/net/ipv4/netfilter/ipt_ECN.c#L25">25</a> 
 <a name="L26" href="source/net/ipv4/netfilter/ipt_ECN.c#L26">26</a> <b><i>/* set ECT codepoint from IP header.</i></b>
 <a name="L27" href="source/net/ipv4/netfilter/ipt_ECN.c#L27">27</a> <b><i> *      return false if there was an error. */</i></b>
 <a name="L28" href="source/net/ipv4/netfilter/ipt_ECN.c#L28">28</a> static inline <a href="ident?i=bool">bool</a>
 <a name="L29" href="source/net/ipv4/netfilter/ipt_ECN.c#L29">29</a> <a href="ident?i=set_ect_ip">set_ect_ip</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, const struct <a href="ident?i=ipt_ECN_info">ipt_ECN_info</a> *einfo)
 <a name="L30" href="source/net/ipv4/netfilter/ipt_ECN.c#L30">30</a> {
 <a name="L31" href="source/net/ipv4/netfilter/ipt_ECN.c#L31">31</a>         struct <a href="ident?i=iphdr">iphdr</a> *iph = <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>);
 <a name="L32" href="source/net/ipv4/netfilter/ipt_ECN.c#L32">32</a> 
 <a name="L33" href="source/net/ipv4/netfilter/ipt_ECN.c#L33">33</a>         if ((iph-&gt;tos &amp; <a href="ident?i=IPT_ECN_IP_MASK">IPT_ECN_IP_MASK</a>) != (einfo-&gt;ip_ect &amp; <a href="ident?i=IPT_ECN_IP_MASK">IPT_ECN_IP_MASK</a>)) {
 <a name="L34" href="source/net/ipv4/netfilter/ipt_ECN.c#L34">34</a>                 <a href="ident?i=__u8">__u8</a> oldtos;
 <a name="L35" href="source/net/ipv4/netfilter/ipt_ECN.c#L35">35</a>                 if (!<a href="ident?i=skb_make_writable">skb_make_writable</a>(<a href="ident?i=skb">skb</a>, sizeof(struct <a href="ident?i=iphdr">iphdr</a>)))
 <a name="L36" href="source/net/ipv4/netfilter/ipt_ECN.c#L36">36</a>                         return <a href="ident?i=false">false</a>;
 <a name="L37" href="source/net/ipv4/netfilter/ipt_ECN.c#L37">37</a>                 iph = <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>);
 <a name="L38" href="source/net/ipv4/netfilter/ipt_ECN.c#L38">38</a>                 oldtos = iph-&gt;tos;
 <a name="L39" href="source/net/ipv4/netfilter/ipt_ECN.c#L39">39</a>                 iph-&gt;tos &amp;= ~IPT_ECN_IP_MASK;
 <a name="L40" href="source/net/ipv4/netfilter/ipt_ECN.c#L40">40</a>                 iph-&gt;tos |= (einfo-&gt;ip_ect &amp; <a href="ident?i=IPT_ECN_IP_MASK">IPT_ECN_IP_MASK</a>);
 <a name="L41" href="source/net/ipv4/netfilter/ipt_ECN.c#L41">41</a>                 <a href="ident?i=csum_replace2">csum_replace2</a>(&amp;iph-&gt;<a href="ident?i=check">check</a>, <a href="ident?i=htons">htons</a>(oldtos), <a href="ident?i=htons">htons</a>(iph-&gt;tos));
 <a name="L42" href="source/net/ipv4/netfilter/ipt_ECN.c#L42">42</a>         }
 <a name="L43" href="source/net/ipv4/netfilter/ipt_ECN.c#L43">43</a>         return <a href="ident?i=true">true</a>;
 <a name="L44" href="source/net/ipv4/netfilter/ipt_ECN.c#L44">44</a> }
 <a name="L45" href="source/net/ipv4/netfilter/ipt_ECN.c#L45">45</a> 
 <a name="L46" href="source/net/ipv4/netfilter/ipt_ECN.c#L46">46</a> <b><i>/* Return false if there was an error. */</i></b>
 <a name="L47" href="source/net/ipv4/netfilter/ipt_ECN.c#L47">47</a> static inline <a href="ident?i=bool">bool</a>
 <a name="L48" href="source/net/ipv4/netfilter/ipt_ECN.c#L48">48</a> <a href="ident?i=set_ect_tcp">set_ect_tcp</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, const struct <a href="ident?i=ipt_ECN_info">ipt_ECN_info</a> *einfo)
 <a name="L49" href="source/net/ipv4/netfilter/ipt_ECN.c#L49">49</a> {
 <a name="L50" href="source/net/ipv4/netfilter/ipt_ECN.c#L50">50</a>         struct <a href="ident?i=tcphdr">tcphdr</a> _tcph, *tcph;
 <a name="L51" href="source/net/ipv4/netfilter/ipt_ECN.c#L51">51</a>         <a href="ident?i=__be16">__be16</a> oldval;
 <a name="L52" href="source/net/ipv4/netfilter/ipt_ECN.c#L52">52</a> 
 <a name="L53" href="source/net/ipv4/netfilter/ipt_ECN.c#L53">53</a>         <b><i>/* Not enough header? */</i></b>
 <a name="L54" href="source/net/ipv4/netfilter/ipt_ECN.c#L54">54</a>         tcph = <a href="ident?i=skb_header_pointer">skb_header_pointer</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=ip_hdrlen">ip_hdrlen</a>(<a href="ident?i=skb">skb</a>), sizeof(_tcph), &amp;_tcph);
 <a name="L55" href="source/net/ipv4/netfilter/ipt_ECN.c#L55">55</a>         if (!tcph)
 <a name="L56" href="source/net/ipv4/netfilter/ipt_ECN.c#L56">56</a>                 return <a href="ident?i=false">false</a>;
 <a name="L57" href="source/net/ipv4/netfilter/ipt_ECN.c#L57">57</a> 
 <a name="L58" href="source/net/ipv4/netfilter/ipt_ECN.c#L58">58</a>         if ((!(einfo-&gt;<a href="ident?i=operation">operation</a> &amp; <a href="ident?i=IPT_ECN_OP_SET_ECE">IPT_ECN_OP_SET_ECE</a>) ||
 <a name="L59" href="source/net/ipv4/netfilter/ipt_ECN.c#L59">59</a>              tcph-&gt;ece == einfo-&gt;<a href="ident?i=proto">proto</a>.tcp.ece) &amp;&amp;
 <a name="L60" href="source/net/ipv4/netfilter/ipt_ECN.c#L60">60</a>             (!(einfo-&gt;<a href="ident?i=operation">operation</a> &amp; <a href="ident?i=IPT_ECN_OP_SET_CWR">IPT_ECN_OP_SET_CWR</a>) ||
 <a name="L61" href="source/net/ipv4/netfilter/ipt_ECN.c#L61">61</a>              tcph-&gt;cwr == einfo-&gt;<a href="ident?i=proto">proto</a>.tcp.cwr))
 <a name="L62" href="source/net/ipv4/netfilter/ipt_ECN.c#L62">62</a>                 return <a href="ident?i=true">true</a>;
 <a name="L63" href="source/net/ipv4/netfilter/ipt_ECN.c#L63">63</a> 
 <a name="L64" href="source/net/ipv4/netfilter/ipt_ECN.c#L64">64</a>         if (!<a href="ident?i=skb_make_writable">skb_make_writable</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=ip_hdrlen">ip_hdrlen</a>(<a href="ident?i=skb">skb</a>) + sizeof(*tcph)))
 <a name="L65" href="source/net/ipv4/netfilter/ipt_ECN.c#L65">65</a>                 return <a href="ident?i=false">false</a>;
 <a name="L66" href="source/net/ipv4/netfilter/ipt_ECN.c#L66">66</a>         tcph = (void *)<a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>) + <a href="ident?i=ip_hdrlen">ip_hdrlen</a>(<a href="ident?i=skb">skb</a>);
 <a name="L67" href="source/net/ipv4/netfilter/ipt_ECN.c#L67">67</a> 
 <a name="L68" href="source/net/ipv4/netfilter/ipt_ECN.c#L68">68</a>         oldval = ((<a href="ident?i=__be16">__be16</a> *)tcph)[6];
 <a name="L69" href="source/net/ipv4/netfilter/ipt_ECN.c#L69">69</a>         if (einfo-&gt;<a href="ident?i=operation">operation</a> &amp; <a href="ident?i=IPT_ECN_OP_SET_ECE">IPT_ECN_OP_SET_ECE</a>)
 <a name="L70" href="source/net/ipv4/netfilter/ipt_ECN.c#L70">70</a>                 tcph-&gt;ece = einfo-&gt;<a href="ident?i=proto">proto</a>.tcp.ece;
 <a name="L71" href="source/net/ipv4/netfilter/ipt_ECN.c#L71">71</a>         if (einfo-&gt;<a href="ident?i=operation">operation</a> &amp; <a href="ident?i=IPT_ECN_OP_SET_CWR">IPT_ECN_OP_SET_CWR</a>)
 <a name="L72" href="source/net/ipv4/netfilter/ipt_ECN.c#L72">72</a>                 tcph-&gt;cwr = einfo-&gt;<a href="ident?i=proto">proto</a>.tcp.cwr;
 <a name="L73" href="source/net/ipv4/netfilter/ipt_ECN.c#L73">73</a> 
 <a name="L74" href="source/net/ipv4/netfilter/ipt_ECN.c#L74">74</a>         <a href="ident?i=inet_proto_csum_replace2">inet_proto_csum_replace2</a>(&amp;tcph-&gt;<a href="ident?i=check">check</a>, <a href="ident?i=skb">skb</a>,
 <a name="L75" href="source/net/ipv4/netfilter/ipt_ECN.c#L75">75</a>                                  oldval, ((<a href="ident?i=__be16">__be16</a> *)tcph)[6], 0);
 <a name="L76" href="source/net/ipv4/netfilter/ipt_ECN.c#L76">76</a>         return <a href="ident?i=true">true</a>;
 <a name="L77" href="source/net/ipv4/netfilter/ipt_ECN.c#L77">77</a> }
 <a name="L78" href="source/net/ipv4/netfilter/ipt_ECN.c#L78">78</a> 
 <a name="L79" href="source/net/ipv4/netfilter/ipt_ECN.c#L79">79</a> static unsigned int
 <a name="L80" href="source/net/ipv4/netfilter/ipt_ECN.c#L80">80</a> <a href="ident?i=ecn_tg">ecn_tg</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, const struct <a href="ident?i=xt_action_param">xt_action_param</a> *<a href="ident?i=par">par</a>)
 <a name="L81" href="source/net/ipv4/netfilter/ipt_ECN.c#L81">81</a> {
 <a name="L82" href="source/net/ipv4/netfilter/ipt_ECN.c#L82">82</a>         const struct <a href="ident?i=ipt_ECN_info">ipt_ECN_info</a> *einfo = <a href="ident?i=par">par</a>-&gt;targinfo;
 <a name="L83" href="source/net/ipv4/netfilter/ipt_ECN.c#L83">83</a> 
 <a name="L84" href="source/net/ipv4/netfilter/ipt_ECN.c#L84">84</a>         if (einfo-&gt;<a href="ident?i=operation">operation</a> &amp; <a href="ident?i=IPT_ECN_OP_SET_IP">IPT_ECN_OP_SET_IP</a>)
 <a name="L85" href="source/net/ipv4/netfilter/ipt_ECN.c#L85">85</a>                 if (!<a href="ident?i=set_ect_ip">set_ect_ip</a>(<a href="ident?i=skb">skb</a>, einfo))
 <a name="L86" href="source/net/ipv4/netfilter/ipt_ECN.c#L86">86</a>                         return <a href="ident?i=NF_DROP">NF_DROP</a>;
 <a name="L87" href="source/net/ipv4/netfilter/ipt_ECN.c#L87">87</a> 
 <a name="L88" href="source/net/ipv4/netfilter/ipt_ECN.c#L88">88</a>         if (einfo-&gt;<a href="ident?i=operation">operation</a> &amp; (<a href="ident?i=IPT_ECN_OP_SET_ECE">IPT_ECN_OP_SET_ECE</a> | <a href="ident?i=IPT_ECN_OP_SET_CWR">IPT_ECN_OP_SET_CWR</a>) &amp;&amp;
 <a name="L89" href="source/net/ipv4/netfilter/ipt_ECN.c#L89">89</a>             <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=protocol">protocol</a> == <a href="ident?i=IPPROTO_TCP">IPPROTO_TCP</a>)
 <a name="L90" href="source/net/ipv4/netfilter/ipt_ECN.c#L90">90</a>                 if (!<a href="ident?i=set_ect_tcp">set_ect_tcp</a>(<a href="ident?i=skb">skb</a>, einfo))
 <a name="L91" href="source/net/ipv4/netfilter/ipt_ECN.c#L91">91</a>                         return <a href="ident?i=NF_DROP">NF_DROP</a>;
 <a name="L92" href="source/net/ipv4/netfilter/ipt_ECN.c#L92">92</a> 
 <a name="L93" href="source/net/ipv4/netfilter/ipt_ECN.c#L93">93</a>         return <a href="ident?i=XT_CONTINUE">XT_CONTINUE</a>;
 <a name="L94" href="source/net/ipv4/netfilter/ipt_ECN.c#L94">94</a> }
 <a name="L95" href="source/net/ipv4/netfilter/ipt_ECN.c#L95">95</a> 
 <a name="L96" href="source/net/ipv4/netfilter/ipt_ECN.c#L96">96</a> static int <a href="ident?i=ecn_tg_check">ecn_tg_check</a>(const struct <a href="ident?i=xt_tgchk_param">xt_tgchk_param</a> *<a href="ident?i=par">par</a>)
 <a name="L97" href="source/net/ipv4/netfilter/ipt_ECN.c#L97">97</a> {
 <a name="L98" href="source/net/ipv4/netfilter/ipt_ECN.c#L98">98</a>         const struct <a href="ident?i=ipt_ECN_info">ipt_ECN_info</a> *einfo = <a href="ident?i=par">par</a>-&gt;targinfo;
 <a name="L99" href="source/net/ipv4/netfilter/ipt_ECN.c#L99">99</a>         const struct <a href="ident?i=ipt_entry">ipt_entry</a> *<a href="ident?i=e">e</a> = <a href="ident?i=par">par</a>-&gt;entryinfo;
<a name="L100" href="source/net/ipv4/netfilter/ipt_ECN.c#L100">100</a> 
<a name="L101" href="source/net/ipv4/netfilter/ipt_ECN.c#L101">101</a>         if (einfo-&gt;<a href="ident?i=operation">operation</a> &amp; <a href="ident?i=IPT_ECN_OP_MASK">IPT_ECN_OP_MASK</a>) {
<a name="L102" href="source/net/ipv4/netfilter/ipt_ECN.c#L102">102</a>                 <a href="ident?i=pr_info">pr_info</a>(<i>"unsupported ECN operation %x\n"</i>, einfo-&gt;<a href="ident?i=operation">operation</a>);
<a name="L103" href="source/net/ipv4/netfilter/ipt_ECN.c#L103">103</a>                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L104" href="source/net/ipv4/netfilter/ipt_ECN.c#L104">104</a>         }
<a name="L105" href="source/net/ipv4/netfilter/ipt_ECN.c#L105">105</a>         if (einfo-&gt;ip_ect &amp; ~IPT_ECN_IP_MASK) {
<a name="L106" href="source/net/ipv4/netfilter/ipt_ECN.c#L106">106</a>                 <a href="ident?i=pr_info">pr_info</a>(<i>"new ECT codepoint %x out of mask\n"</i>, einfo-&gt;ip_ect);
<a name="L107" href="source/net/ipv4/netfilter/ipt_ECN.c#L107">107</a>                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L108" href="source/net/ipv4/netfilter/ipt_ECN.c#L108">108</a>         }
<a name="L109" href="source/net/ipv4/netfilter/ipt_ECN.c#L109">109</a>         if ((einfo-&gt;<a href="ident?i=operation">operation</a> &amp; (<a href="ident?i=IPT_ECN_OP_SET_ECE">IPT_ECN_OP_SET_ECE</a>|<a href="ident?i=IPT_ECN_OP_SET_CWR">IPT_ECN_OP_SET_CWR</a>)) &amp;&amp;
<a name="L110" href="source/net/ipv4/netfilter/ipt_ECN.c#L110">110</a>             (<a href="ident?i=e">e</a>-&gt;<a href="ident?i=ip">ip</a>.<a href="ident?i=proto">proto</a> != <a href="ident?i=IPPROTO_TCP">IPPROTO_TCP</a> || (<a href="ident?i=e">e</a>-&gt;<a href="ident?i=ip">ip</a>.invflags &amp; <a href="ident?i=XT_INV_PROTO">XT_INV_PROTO</a>))) {
<a name="L111" href="source/net/ipv4/netfilter/ipt_ECN.c#L111">111</a>                 <a href="ident?i=pr_info">pr_info</a>(<i>"cannot use TCP operations on a non-tcp rule\n"</i>);
<a name="L112" href="source/net/ipv4/netfilter/ipt_ECN.c#L112">112</a>                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L113" href="source/net/ipv4/netfilter/ipt_ECN.c#L113">113</a>         }
<a name="L114" href="source/net/ipv4/netfilter/ipt_ECN.c#L114">114</a>         return 0;
<a name="L115" href="source/net/ipv4/netfilter/ipt_ECN.c#L115">115</a> }
<a name="L116" href="source/net/ipv4/netfilter/ipt_ECN.c#L116">116</a> 
<a name="L117" href="source/net/ipv4/netfilter/ipt_ECN.c#L117">117</a> static struct <a href="ident?i=xt_target">xt_target</a> ecn_tg_reg <a href="ident?i=__read_mostly">__read_mostly</a> = {
<a name="L118" href="source/net/ipv4/netfilter/ipt_ECN.c#L118">118</a>         .<a href="ident?i=name">name</a>           = <i>"ECN"</i>,
<a name="L119" href="source/net/ipv4/netfilter/ipt_ECN.c#L119">119</a>         .<a href="ident?i=family">family</a>         = NFPROTO_IPV4,
<a name="L120" href="source/net/ipv4/netfilter/ipt_ECN.c#L120">120</a>         .<a href="ident?i=target">target</a>         = <a href="ident?i=ecn_tg">ecn_tg</a>,
<a name="L121" href="source/net/ipv4/netfilter/ipt_ECN.c#L121">121</a>         .targetsize     = sizeof(struct <a href="ident?i=ipt_ECN_info">ipt_ECN_info</a>),
<a name="L122" href="source/net/ipv4/netfilter/ipt_ECN.c#L122">122</a>         .<a href="ident?i=table">table</a>          = <i>"mangle"</i>,
<a name="L123" href="source/net/ipv4/netfilter/ipt_ECN.c#L123">123</a>         .<a href="ident?i=checkentry">checkentry</a>     = <a href="ident?i=ecn_tg_check">ecn_tg_check</a>,
<a name="L124" href="source/net/ipv4/netfilter/ipt_ECN.c#L124">124</a>         .<a href="ident?i=me">me</a>             = <a href="ident?i=THIS_MODULE">THIS_MODULE</a>,
<a name="L125" href="source/net/ipv4/netfilter/ipt_ECN.c#L125">125</a> };
<a name="L126" href="source/net/ipv4/netfilter/ipt_ECN.c#L126">126</a> 
<a name="L127" href="source/net/ipv4/netfilter/ipt_ECN.c#L127">127</a> static int <a href="ident?i=__init">__init</a> <a href="ident?i=ecn_tg_init">ecn_tg_init</a>(void)
<a name="L128" href="source/net/ipv4/netfilter/ipt_ECN.c#L128">128</a> {
<a name="L129" href="source/net/ipv4/netfilter/ipt_ECN.c#L129">129</a>         return <a href="ident?i=xt_register_target">xt_register_target</a>(&amp;ecn_tg_reg);
<a name="L130" href="source/net/ipv4/netfilter/ipt_ECN.c#L130">130</a> }
<a name="L131" href="source/net/ipv4/netfilter/ipt_ECN.c#L131">131</a> 
<a name="L132" href="source/net/ipv4/netfilter/ipt_ECN.c#L132">132</a> static void <a href="ident?i=__exit">__exit</a> <a href="ident?i=ecn_tg_exit">ecn_tg_exit</a>(void)
<a name="L133" href="source/net/ipv4/netfilter/ipt_ECN.c#L133">133</a> {
<a name="L134" href="source/net/ipv4/netfilter/ipt_ECN.c#L134">134</a>         <a href="ident?i=xt_unregister_target">xt_unregister_target</a>(&amp;ecn_tg_reg);
<a name="L135" href="source/net/ipv4/netfilter/ipt_ECN.c#L135">135</a> }
<a name="L136" href="source/net/ipv4/netfilter/ipt_ECN.c#L136">136</a> 
<a name="L137" href="source/net/ipv4/netfilter/ipt_ECN.c#L137">137</a> <a href="ident?i=module_init">module_init</a>(<a href="ident?i=ecn_tg_init">ecn_tg_init</a>);
<a name="L138" href="source/net/ipv4/netfilter/ipt_ECN.c#L138">138</a> <a href="ident?i=module_exit">module_exit</a>(<a href="ident?i=ecn_tg_exit">ecn_tg_exit</a>);
<a name="L139" href="source/net/ipv4/netfilter/ipt_ECN.c#L139">139</a> </pre></div><p>
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
