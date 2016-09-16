<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title>Linux/net/ipv4/xfrm4_protocol.c - Linux Cross Reference - Free Electrons</title>
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
		 &nbsp;&bull;&nbsp;<b><i>source navigation</i></b> &nbsp;&bull;&nbsp;<a href="diff/net/ipv4/xfrm4_protocol.c">diff markup</a> &nbsp;&bull;&nbsp;<a href="ident">identifier search</a> &nbsp;&bull;&nbsp;<a href="search">freetext search</a> &nbsp;&bull;&nbsp;
		</p>
	</div>
</div>

<div id="topbar">
  
  <p>Version: &nbsp;<a href="source/net/ipv4/xfrm4_protocol.c?v=2.0.40">2.0.40</a>&nbsp;<a href="source/net/ipv4/xfrm4_protocol.c?v=2.2.26">2.2.26</a>&nbsp;<a href="source/net/ipv4/xfrm4_protocol.c?v=2.4.37">2.4.37</a>&nbsp;<a href="source/net/ipv4/xfrm4_protocol.c?v=3.5">3.5</a>&nbsp;<a href="source/net/ipv4/xfrm4_protocol.c?v=3.6">3.6</a>&nbsp;<a href="source/net/ipv4/xfrm4_protocol.c?v=3.7">3.7</a>&nbsp;<a href="source/net/ipv4/xfrm4_protocol.c?v=3.8">3.8</a>&nbsp;<a href="source/net/ipv4/xfrm4_protocol.c?v=3.9">3.9</a>&nbsp;<a href="source/net/ipv4/xfrm4_protocol.c?v=3.10">3.10</a>&nbsp;<a href="source/net/ipv4/xfrm4_protocol.c?v=3.11">3.11</a>&nbsp;<a href="source/net/ipv4/xfrm4_protocol.c?v=3.12">3.12</a>&nbsp;<a href="source/net/ipv4/xfrm4_protocol.c?v=3.13">3.13</a>&nbsp;<a href="source/net/ipv4/xfrm4_protocol.c?v=3.14">3.14</a>&nbsp;<a href="source/net/ipv4/xfrm4_protocol.c?v=3.15">3.15</a>&nbsp;<a href="source/net/ipv4/xfrm4_protocol.c?v=3.16">3.16</a>&nbsp;<a href="source/net/ipv4/xfrm4_protocol.c?v=3.17">3.17</a>&nbsp;<a href="source/net/ipv4/xfrm4_protocol.c?v=3.18">3.18</a>&nbsp;<a href="source/net/ipv4/xfrm4_protocol.c?v=3.19">3.19</a>&nbsp;<a href="source/net/ipv4/xfrm4_protocol.c?v=4.0">4.0</a>&nbsp;<b><i>4.1</i></b></p>
  
</div>

<h1><a href="source/">Linux</a>/<a href="source/net/">net</a>/<a href="source/net/ipv4/">ipv4</a>/<a href="source/net/ipv4/xfrm4_protocol.c">xfrm4_protocol.c</a></h1>
<div id="lxrcode"><pre>  <a name="L1" href="source/net/ipv4/xfrm4_protocol.c#L1">1</a> <b><i>/* xfrm4_protocol.c - Generic xfrm protocol multiplexer.</i></b>
  <a name="L2" href="source/net/ipv4/xfrm4_protocol.c#L2">2</a> <b><i> *</i></b>
  <a name="L3" href="source/net/ipv4/xfrm4_protocol.c#L3">3</a> <b><i> * Copyright (C) 2013 secunet Security Networks AG</i></b>
  <a name="L4" href="source/net/ipv4/xfrm4_protocol.c#L4">4</a> <b><i> *</i></b>
  <a name="L5" href="source/net/ipv4/xfrm4_protocol.c#L5">5</a> <b><i> * Author:</i></b>
  <a name="L6" href="source/net/ipv4/xfrm4_protocol.c#L6">6</a> <b><i> * Steffen Klassert &lt;steffen.klassert@secunet.com&gt;</i></b>
  <a name="L7" href="source/net/ipv4/xfrm4_protocol.c#L7">7</a> <b><i> *</i></b>
  <a name="L8" href="source/net/ipv4/xfrm4_protocol.c#L8">8</a> <b><i> * Based on:</i></b>
  <a name="L9" href="source/net/ipv4/xfrm4_protocol.c#L9">9</a> <b><i> * net/ipv4/tunnel4.c</i></b>
 <a name="L10" href="source/net/ipv4/xfrm4_protocol.c#L10">10</a> <b><i> *</i></b>
 <a name="L11" href="source/net/ipv4/xfrm4_protocol.c#L11">11</a> <b><i> *      This program is free software; you can redistribute it and/or</i></b>
 <a name="L12" href="source/net/ipv4/xfrm4_protocol.c#L12">12</a> <b><i> *      modify it under the terms of the GNU General Public License</i></b>
 <a name="L13" href="source/net/ipv4/xfrm4_protocol.c#L13">13</a> <b><i> *      as published by the Free Software Foundation; either version</i></b>
 <a name="L14" href="source/net/ipv4/xfrm4_protocol.c#L14">14</a> <b><i> *      2 of the License, or (at your option) any later version.</i></b>
 <a name="L15" href="source/net/ipv4/xfrm4_protocol.c#L15">15</a> <b><i> */</i></b>
 <a name="L16" href="source/net/ipv4/xfrm4_protocol.c#L16">16</a> 
 <a name="L17" href="source/net/ipv4/xfrm4_protocol.c#L17">17</a> #include &lt;linux/init.h&gt;
 <a name="L18" href="source/net/ipv4/xfrm4_protocol.c#L18">18</a> #include &lt;linux/mutex.h&gt;
 <a name="L19" href="source/net/ipv4/xfrm4_protocol.c#L19">19</a> #include &lt;linux/skbuff.h&gt;
 <a name="L20" href="source/net/ipv4/xfrm4_protocol.c#L20">20</a> #include &lt;net/icmp.h&gt;
 <a name="L21" href="source/net/ipv4/xfrm4_protocol.c#L21">21</a> #include &lt;net/ip.h&gt;
 <a name="L22" href="source/net/ipv4/xfrm4_protocol.c#L22">22</a> #include &lt;net/protocol.h&gt;
 <a name="L23" href="source/net/ipv4/xfrm4_protocol.c#L23">23</a> #include &lt;net/xfrm.h&gt;
 <a name="L24" href="source/net/ipv4/xfrm4_protocol.c#L24">24</a> 
 <a name="L25" href="source/net/ipv4/xfrm4_protocol.c#L25">25</a> static struct <a href="ident?i=xfrm4_protocol">xfrm4_protocol</a> <a href="ident?i=__rcu">__rcu</a> *esp4_handlers <a href="ident?i=__read_mostly">__read_mostly</a>;
 <a name="L26" href="source/net/ipv4/xfrm4_protocol.c#L26">26</a> static struct <a href="ident?i=xfrm4_protocol">xfrm4_protocol</a> <a href="ident?i=__rcu">__rcu</a> *ah4_handlers <a href="ident?i=__read_mostly">__read_mostly</a>;
 <a name="L27" href="source/net/ipv4/xfrm4_protocol.c#L27">27</a> static struct <a href="ident?i=xfrm4_protocol">xfrm4_protocol</a> <a href="ident?i=__rcu">__rcu</a> *ipcomp4_handlers <a href="ident?i=__read_mostly">__read_mostly</a>;
 <a name="L28" href="source/net/ipv4/xfrm4_protocol.c#L28">28</a> static <a href="ident?i=DEFINE_MUTEX">DEFINE_MUTEX</a>(xfrm4_protocol_mutex);
 <a name="L29" href="source/net/ipv4/xfrm4_protocol.c#L29">29</a> 
 <a name="L30" href="source/net/ipv4/xfrm4_protocol.c#L30">30</a> static inline struct <a href="ident?i=xfrm4_protocol">xfrm4_protocol</a> <a href="ident?i=__rcu">__rcu</a> **<a href="ident?i=proto_handlers">proto_handlers</a>(<a href="ident?i=u8">u8</a> <a href="ident?i=protocol">protocol</a>)
 <a name="L31" href="source/net/ipv4/xfrm4_protocol.c#L31">31</a> {
 <a name="L32" href="source/net/ipv4/xfrm4_protocol.c#L32">32</a>         switch (<a href="ident?i=protocol">protocol</a>) {
 <a name="L33" href="source/net/ipv4/xfrm4_protocol.c#L33">33</a>         case <a href="ident?i=IPPROTO_ESP">IPPROTO_ESP</a>:
 <a name="L34" href="source/net/ipv4/xfrm4_protocol.c#L34">34</a>                 return &amp;esp4_handlers;
 <a name="L35" href="source/net/ipv4/xfrm4_protocol.c#L35">35</a>         case <a href="ident?i=IPPROTO_AH">IPPROTO_AH</a>:
 <a name="L36" href="source/net/ipv4/xfrm4_protocol.c#L36">36</a>                 return &amp;ah4_handlers;
 <a name="L37" href="source/net/ipv4/xfrm4_protocol.c#L37">37</a>         case <a href="ident?i=IPPROTO_COMP">IPPROTO_COMP</a>:
 <a name="L38" href="source/net/ipv4/xfrm4_protocol.c#L38">38</a>                 return &amp;ipcomp4_handlers;
 <a name="L39" href="source/net/ipv4/xfrm4_protocol.c#L39">39</a>         }
 <a name="L40" href="source/net/ipv4/xfrm4_protocol.c#L40">40</a> 
 <a name="L41" href="source/net/ipv4/xfrm4_protocol.c#L41">41</a>         return <a href="ident?i=NULL">NULL</a>;
 <a name="L42" href="source/net/ipv4/xfrm4_protocol.c#L42">42</a> }
 <a name="L43" href="source/net/ipv4/xfrm4_protocol.c#L43">43</a> 
 <a name="L44" href="source/net/ipv4/xfrm4_protocol.c#L44">44</a> #define <a href="ident?i=for_each_protocol_rcu">for_each_protocol_rcu</a>(<a href="ident?i=head">head</a>, <a href="ident?i=handler">handler</a>)            \
 <a name="L45" href="source/net/ipv4/xfrm4_protocol.c#L45">45</a>         for (<a href="ident?i=handler">handler</a> = <a href="ident?i=rcu_dereference">rcu_dereference</a>(<a href="ident?i=head">head</a>);           \
 <a name="L46" href="source/net/ipv4/xfrm4_protocol.c#L46">46</a>              <a href="ident?i=handler">handler</a> != <a href="ident?i=NULL">NULL</a>;                           \
 <a name="L47" href="source/net/ipv4/xfrm4_protocol.c#L47">47</a>              <a href="ident?i=handler">handler</a> = <a href="ident?i=rcu_dereference">rcu_dereference</a>(<a href="ident?i=handler">handler</a>-&gt;<a href="ident?i=next">next</a>))  \
 <a name="L48" href="source/net/ipv4/xfrm4_protocol.c#L48">48</a> 
 <a name="L49" href="source/net/ipv4/xfrm4_protocol.c#L49">49</a> int <a href="ident?i=xfrm4_rcv_cb">xfrm4_rcv_cb</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, <a href="ident?i=u8">u8</a> <a href="ident?i=protocol">protocol</a>, int <a href="ident?i=err">err</a>)
 <a name="L50" href="source/net/ipv4/xfrm4_protocol.c#L50">50</a> {
 <a name="L51" href="source/net/ipv4/xfrm4_protocol.c#L51">51</a>         int <a href="ident?i=ret">ret</a>;
 <a name="L52" href="source/net/ipv4/xfrm4_protocol.c#L52">52</a>         struct <a href="ident?i=xfrm4_protocol">xfrm4_protocol</a> *<a href="ident?i=handler">handler</a>;
 <a name="L53" href="source/net/ipv4/xfrm4_protocol.c#L53">53</a>         struct <a href="ident?i=xfrm4_protocol">xfrm4_protocol</a> <a href="ident?i=__rcu">__rcu</a> **<a href="ident?i=head">head</a> = <a href="ident?i=proto_handlers">proto_handlers</a>(<a href="ident?i=protocol">protocol</a>);
 <a name="L54" href="source/net/ipv4/xfrm4_protocol.c#L54">54</a> 
 <a name="L55" href="source/net/ipv4/xfrm4_protocol.c#L55">55</a>         if (!<a href="ident?i=head">head</a>)
 <a name="L56" href="source/net/ipv4/xfrm4_protocol.c#L56">56</a>                 return 0;
 <a name="L57" href="source/net/ipv4/xfrm4_protocol.c#L57">57</a> 
 <a name="L58" href="source/net/ipv4/xfrm4_protocol.c#L58">58</a>         <a href="ident?i=for_each_protocol_rcu">for_each_protocol_rcu</a>(*<a href="ident?i=head">head</a>, <a href="ident?i=handler">handler</a>)
 <a name="L59" href="source/net/ipv4/xfrm4_protocol.c#L59">59</a>                 if ((<a href="ident?i=ret">ret</a> = <a href="ident?i=handler">handler</a>-&gt;cb_handler(<a href="ident?i=skb">skb</a>, <a href="ident?i=err">err</a>)) &lt;= 0)
 <a name="L60" href="source/net/ipv4/xfrm4_protocol.c#L60">60</a>                         return <a href="ident?i=ret">ret</a>;
 <a name="L61" href="source/net/ipv4/xfrm4_protocol.c#L61">61</a> 
 <a name="L62" href="source/net/ipv4/xfrm4_protocol.c#L62">62</a>         return 0;
 <a name="L63" href="source/net/ipv4/xfrm4_protocol.c#L63">63</a> }
 <a name="L64" href="source/net/ipv4/xfrm4_protocol.c#L64">64</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=xfrm4_rcv_cb">xfrm4_rcv_cb</a>);
 <a name="L65" href="source/net/ipv4/xfrm4_protocol.c#L65">65</a> 
 <a name="L66" href="source/net/ipv4/xfrm4_protocol.c#L66">66</a> int <a href="ident?i=xfrm4_rcv_encap">xfrm4_rcv_encap</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, int nexthdr, <a href="ident?i=__be32">__be32</a> <a href="ident?i=spi">spi</a>,
 <a name="L67" href="source/net/ipv4/xfrm4_protocol.c#L67">67</a>                     int encap_type)
 <a name="L68" href="source/net/ipv4/xfrm4_protocol.c#L68">68</a> {
 <a name="L69" href="source/net/ipv4/xfrm4_protocol.c#L69">69</a>         int <a href="ident?i=ret">ret</a>;
 <a name="L70" href="source/net/ipv4/xfrm4_protocol.c#L70">70</a>         struct <a href="ident?i=xfrm4_protocol">xfrm4_protocol</a> *<a href="ident?i=handler">handler</a>;
 <a name="L71" href="source/net/ipv4/xfrm4_protocol.c#L71">71</a>         struct <a href="ident?i=xfrm4_protocol">xfrm4_protocol</a> <a href="ident?i=__rcu">__rcu</a> **<a href="ident?i=head">head</a> = <a href="ident?i=proto_handlers">proto_handlers</a>(nexthdr);
 <a name="L72" href="source/net/ipv4/xfrm4_protocol.c#L72">72</a> 
 <a name="L73" href="source/net/ipv4/xfrm4_protocol.c#L73">73</a>         <a href="ident?i=XFRM_TUNNEL_SKB_CB">XFRM_TUNNEL_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;tunnel.ip4 = <a href="ident?i=NULL">NULL</a>;
 <a name="L74" href="source/net/ipv4/xfrm4_protocol.c#L74">74</a>         <a href="ident?i=XFRM_SPI_SKB_CB">XFRM_SPI_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=family">family</a> = <a href="ident?i=AF_INET">AF_INET</a>;
 <a name="L75" href="source/net/ipv4/xfrm4_protocol.c#L75">75</a>         <a href="ident?i=XFRM_SPI_SKB_CB">XFRM_SPI_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;daddroff = <a href="ident?i=offsetof">offsetof</a>(struct <a href="ident?i=iphdr">iphdr</a>, <a href="ident?i=daddr">daddr</a>);
 <a name="L76" href="source/net/ipv4/xfrm4_protocol.c#L76">76</a> 
 <a name="L77" href="source/net/ipv4/xfrm4_protocol.c#L77">77</a>         if (!<a href="ident?i=head">head</a>)
 <a name="L78" href="source/net/ipv4/xfrm4_protocol.c#L78">78</a>                 goto <a href="ident?i=out">out</a>;
 <a name="L79" href="source/net/ipv4/xfrm4_protocol.c#L79">79</a> 
 <a name="L80" href="source/net/ipv4/xfrm4_protocol.c#L80">80</a>         <a href="ident?i=for_each_protocol_rcu">for_each_protocol_rcu</a>(*<a href="ident?i=head">head</a>, <a href="ident?i=handler">handler</a>)
 <a name="L81" href="source/net/ipv4/xfrm4_protocol.c#L81">81</a>                 if ((<a href="ident?i=ret">ret</a> = <a href="ident?i=handler">handler</a>-&gt;<a href="ident?i=input_handler">input_handler</a>(<a href="ident?i=skb">skb</a>, nexthdr, <a href="ident?i=spi">spi</a>, encap_type)) != -<a href="ident?i=EINVAL">EINVAL</a>)
 <a name="L82" href="source/net/ipv4/xfrm4_protocol.c#L82">82</a>                         return <a href="ident?i=ret">ret</a>;
 <a name="L83" href="source/net/ipv4/xfrm4_protocol.c#L83">83</a> 
 <a name="L84" href="source/net/ipv4/xfrm4_protocol.c#L84">84</a> <a href="ident?i=out">out</a>:
 <a name="L85" href="source/net/ipv4/xfrm4_protocol.c#L85">85</a>         <a href="ident?i=icmp_send">icmp_send</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=ICMP_DEST_UNREACH">ICMP_DEST_UNREACH</a>, <a href="ident?i=ICMP_PORT_UNREACH">ICMP_PORT_UNREACH</a>, 0);
 <a name="L86" href="source/net/ipv4/xfrm4_protocol.c#L86">86</a> 
 <a name="L87" href="source/net/ipv4/xfrm4_protocol.c#L87">87</a>         <a href="ident?i=kfree_skb">kfree_skb</a>(<a href="ident?i=skb">skb</a>);
 <a name="L88" href="source/net/ipv4/xfrm4_protocol.c#L88">88</a>         return 0;
 <a name="L89" href="source/net/ipv4/xfrm4_protocol.c#L89">89</a> }
 <a name="L90" href="source/net/ipv4/xfrm4_protocol.c#L90">90</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=xfrm4_rcv_encap">xfrm4_rcv_encap</a>);
 <a name="L91" href="source/net/ipv4/xfrm4_protocol.c#L91">91</a> 
 <a name="L92" href="source/net/ipv4/xfrm4_protocol.c#L92">92</a> static int <a href="ident?i=xfrm4_esp_rcv">xfrm4_esp_rcv</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
 <a name="L93" href="source/net/ipv4/xfrm4_protocol.c#L93">93</a> {
 <a name="L94" href="source/net/ipv4/xfrm4_protocol.c#L94">94</a>         int <a href="ident?i=ret">ret</a>;
 <a name="L95" href="source/net/ipv4/xfrm4_protocol.c#L95">95</a>         struct <a href="ident?i=xfrm4_protocol">xfrm4_protocol</a> *<a href="ident?i=handler">handler</a>;
 <a name="L96" href="source/net/ipv4/xfrm4_protocol.c#L96">96</a> 
 <a name="L97" href="source/net/ipv4/xfrm4_protocol.c#L97">97</a>         <a href="ident?i=XFRM_TUNNEL_SKB_CB">XFRM_TUNNEL_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;tunnel.ip4 = <a href="ident?i=NULL">NULL</a>;
 <a name="L98" href="source/net/ipv4/xfrm4_protocol.c#L98">98</a> 
 <a name="L99" href="source/net/ipv4/xfrm4_protocol.c#L99">99</a>         <a href="ident?i=for_each_protocol_rcu">for_each_protocol_rcu</a>(esp4_handlers, <a href="ident?i=handler">handler</a>)
<a name="L100" href="source/net/ipv4/xfrm4_protocol.c#L100">100</a>                 if ((<a href="ident?i=ret">ret</a> = <a href="ident?i=handler">handler</a>-&gt;<a href="ident?i=handler">handler</a>(<a href="ident?i=skb">skb</a>)) != -<a href="ident?i=EINVAL">EINVAL</a>)
<a name="L101" href="source/net/ipv4/xfrm4_protocol.c#L101">101</a>                         return <a href="ident?i=ret">ret</a>;
<a name="L102" href="source/net/ipv4/xfrm4_protocol.c#L102">102</a> 
<a name="L103" href="source/net/ipv4/xfrm4_protocol.c#L103">103</a>         <a href="ident?i=icmp_send">icmp_send</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=ICMP_DEST_UNREACH">ICMP_DEST_UNREACH</a>, <a href="ident?i=ICMP_PORT_UNREACH">ICMP_PORT_UNREACH</a>, 0);
<a name="L104" href="source/net/ipv4/xfrm4_protocol.c#L104">104</a> 
<a name="L105" href="source/net/ipv4/xfrm4_protocol.c#L105">105</a>         <a href="ident?i=kfree_skb">kfree_skb</a>(<a href="ident?i=skb">skb</a>);
<a name="L106" href="source/net/ipv4/xfrm4_protocol.c#L106">106</a>         return 0;
<a name="L107" href="source/net/ipv4/xfrm4_protocol.c#L107">107</a> }
<a name="L108" href="source/net/ipv4/xfrm4_protocol.c#L108">108</a> 
<a name="L109" href="source/net/ipv4/xfrm4_protocol.c#L109">109</a> static void <a href="ident?i=xfrm4_esp_err">xfrm4_esp_err</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, <a href="ident?i=u32">u32</a> <a href="ident?i=info">info</a>)
<a name="L110" href="source/net/ipv4/xfrm4_protocol.c#L110">110</a> {
<a name="L111" href="source/net/ipv4/xfrm4_protocol.c#L111">111</a>         struct <a href="ident?i=xfrm4_protocol">xfrm4_protocol</a> *<a href="ident?i=handler">handler</a>;
<a name="L112" href="source/net/ipv4/xfrm4_protocol.c#L112">112</a> 
<a name="L113" href="source/net/ipv4/xfrm4_protocol.c#L113">113</a>         <a href="ident?i=for_each_protocol_rcu">for_each_protocol_rcu</a>(esp4_handlers, <a href="ident?i=handler">handler</a>)
<a name="L114" href="source/net/ipv4/xfrm4_protocol.c#L114">114</a>                 if (!<a href="ident?i=handler">handler</a>-&gt;<a href="ident?i=err_handler">err_handler</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=info">info</a>))
<a name="L115" href="source/net/ipv4/xfrm4_protocol.c#L115">115</a>                         break;
<a name="L116" href="source/net/ipv4/xfrm4_protocol.c#L116">116</a> }
<a name="L117" href="source/net/ipv4/xfrm4_protocol.c#L117">117</a> 
<a name="L118" href="source/net/ipv4/xfrm4_protocol.c#L118">118</a> static int <a href="ident?i=xfrm4_ah_rcv">xfrm4_ah_rcv</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L119" href="source/net/ipv4/xfrm4_protocol.c#L119">119</a> {
<a name="L120" href="source/net/ipv4/xfrm4_protocol.c#L120">120</a>         int <a href="ident?i=ret">ret</a>;
<a name="L121" href="source/net/ipv4/xfrm4_protocol.c#L121">121</a>         struct <a href="ident?i=xfrm4_protocol">xfrm4_protocol</a> *<a href="ident?i=handler">handler</a>;
<a name="L122" href="source/net/ipv4/xfrm4_protocol.c#L122">122</a> 
<a name="L123" href="source/net/ipv4/xfrm4_protocol.c#L123">123</a>         <a href="ident?i=XFRM_TUNNEL_SKB_CB">XFRM_TUNNEL_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;tunnel.ip4 = <a href="ident?i=NULL">NULL</a>;
<a name="L124" href="source/net/ipv4/xfrm4_protocol.c#L124">124</a> 
<a name="L125" href="source/net/ipv4/xfrm4_protocol.c#L125">125</a>         <a href="ident?i=for_each_protocol_rcu">for_each_protocol_rcu</a>(ah4_handlers, <a href="ident?i=handler">handler</a>)
<a name="L126" href="source/net/ipv4/xfrm4_protocol.c#L126">126</a>                 if ((<a href="ident?i=ret">ret</a> = <a href="ident?i=handler">handler</a>-&gt;<a href="ident?i=handler">handler</a>(<a href="ident?i=skb">skb</a>)) != -<a href="ident?i=EINVAL">EINVAL</a>)
<a name="L127" href="source/net/ipv4/xfrm4_protocol.c#L127">127</a>                         return <a href="ident?i=ret">ret</a>;
<a name="L128" href="source/net/ipv4/xfrm4_protocol.c#L128">128</a> 
<a name="L129" href="source/net/ipv4/xfrm4_protocol.c#L129">129</a>         <a href="ident?i=icmp_send">icmp_send</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=ICMP_DEST_UNREACH">ICMP_DEST_UNREACH</a>, <a href="ident?i=ICMP_PORT_UNREACH">ICMP_PORT_UNREACH</a>, 0);
<a name="L130" href="source/net/ipv4/xfrm4_protocol.c#L130">130</a> 
<a name="L131" href="source/net/ipv4/xfrm4_protocol.c#L131">131</a>         <a href="ident?i=kfree_skb">kfree_skb</a>(<a href="ident?i=skb">skb</a>);
<a name="L132" href="source/net/ipv4/xfrm4_protocol.c#L132">132</a>         return 0;
<a name="L133" href="source/net/ipv4/xfrm4_protocol.c#L133">133</a> }
<a name="L134" href="source/net/ipv4/xfrm4_protocol.c#L134">134</a> 
<a name="L135" href="source/net/ipv4/xfrm4_protocol.c#L135">135</a> static void <a href="ident?i=xfrm4_ah_err">xfrm4_ah_err</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, <a href="ident?i=u32">u32</a> <a href="ident?i=info">info</a>)
<a name="L136" href="source/net/ipv4/xfrm4_protocol.c#L136">136</a> {
<a name="L137" href="source/net/ipv4/xfrm4_protocol.c#L137">137</a>         struct <a href="ident?i=xfrm4_protocol">xfrm4_protocol</a> *<a href="ident?i=handler">handler</a>;
<a name="L138" href="source/net/ipv4/xfrm4_protocol.c#L138">138</a> 
<a name="L139" href="source/net/ipv4/xfrm4_protocol.c#L139">139</a>         <a href="ident?i=for_each_protocol_rcu">for_each_protocol_rcu</a>(ah4_handlers, <a href="ident?i=handler">handler</a>)
<a name="L140" href="source/net/ipv4/xfrm4_protocol.c#L140">140</a>                 if (!<a href="ident?i=handler">handler</a>-&gt;<a href="ident?i=err_handler">err_handler</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=info">info</a>))
<a name="L141" href="source/net/ipv4/xfrm4_protocol.c#L141">141</a>                         break;
<a name="L142" href="source/net/ipv4/xfrm4_protocol.c#L142">142</a> }
<a name="L143" href="source/net/ipv4/xfrm4_protocol.c#L143">143</a> 
<a name="L144" href="source/net/ipv4/xfrm4_protocol.c#L144">144</a> static int <a href="ident?i=xfrm4_ipcomp_rcv">xfrm4_ipcomp_rcv</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L145" href="source/net/ipv4/xfrm4_protocol.c#L145">145</a> {
<a name="L146" href="source/net/ipv4/xfrm4_protocol.c#L146">146</a>         int <a href="ident?i=ret">ret</a>;
<a name="L147" href="source/net/ipv4/xfrm4_protocol.c#L147">147</a>         struct <a href="ident?i=xfrm4_protocol">xfrm4_protocol</a> *<a href="ident?i=handler">handler</a>;
<a name="L148" href="source/net/ipv4/xfrm4_protocol.c#L148">148</a> 
<a name="L149" href="source/net/ipv4/xfrm4_protocol.c#L149">149</a>         <a href="ident?i=XFRM_TUNNEL_SKB_CB">XFRM_TUNNEL_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;tunnel.ip4 = <a href="ident?i=NULL">NULL</a>;
<a name="L150" href="source/net/ipv4/xfrm4_protocol.c#L150">150</a> 
<a name="L151" href="source/net/ipv4/xfrm4_protocol.c#L151">151</a>         <a href="ident?i=for_each_protocol_rcu">for_each_protocol_rcu</a>(ipcomp4_handlers, <a href="ident?i=handler">handler</a>)
<a name="L152" href="source/net/ipv4/xfrm4_protocol.c#L152">152</a>                 if ((<a href="ident?i=ret">ret</a> = <a href="ident?i=handler">handler</a>-&gt;<a href="ident?i=handler">handler</a>(<a href="ident?i=skb">skb</a>)) != -<a href="ident?i=EINVAL">EINVAL</a>)
<a name="L153" href="source/net/ipv4/xfrm4_protocol.c#L153">153</a>                         return <a href="ident?i=ret">ret</a>;
<a name="L154" href="source/net/ipv4/xfrm4_protocol.c#L154">154</a> 
<a name="L155" href="source/net/ipv4/xfrm4_protocol.c#L155">155</a>         <a href="ident?i=icmp_send">icmp_send</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=ICMP_DEST_UNREACH">ICMP_DEST_UNREACH</a>, <a href="ident?i=ICMP_PORT_UNREACH">ICMP_PORT_UNREACH</a>, 0);
<a name="L156" href="source/net/ipv4/xfrm4_protocol.c#L156">156</a> 
<a name="L157" href="source/net/ipv4/xfrm4_protocol.c#L157">157</a>         <a href="ident?i=kfree_skb">kfree_skb</a>(<a href="ident?i=skb">skb</a>);
<a name="L158" href="source/net/ipv4/xfrm4_protocol.c#L158">158</a>         return 0;
<a name="L159" href="source/net/ipv4/xfrm4_protocol.c#L159">159</a> }
<a name="L160" href="source/net/ipv4/xfrm4_protocol.c#L160">160</a> 
<a name="L161" href="source/net/ipv4/xfrm4_protocol.c#L161">161</a> static void <a href="ident?i=xfrm4_ipcomp_err">xfrm4_ipcomp_err</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, <a href="ident?i=u32">u32</a> <a href="ident?i=info">info</a>)
<a name="L162" href="source/net/ipv4/xfrm4_protocol.c#L162">162</a> {
<a name="L163" href="source/net/ipv4/xfrm4_protocol.c#L163">163</a>         struct <a href="ident?i=xfrm4_protocol">xfrm4_protocol</a> *<a href="ident?i=handler">handler</a>;
<a name="L164" href="source/net/ipv4/xfrm4_protocol.c#L164">164</a> 
<a name="L165" href="source/net/ipv4/xfrm4_protocol.c#L165">165</a>         <a href="ident?i=for_each_protocol_rcu">for_each_protocol_rcu</a>(ipcomp4_handlers, <a href="ident?i=handler">handler</a>)
<a name="L166" href="source/net/ipv4/xfrm4_protocol.c#L166">166</a>                 if (!<a href="ident?i=handler">handler</a>-&gt;<a href="ident?i=err_handler">err_handler</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=info">info</a>))
<a name="L167" href="source/net/ipv4/xfrm4_protocol.c#L167">167</a>                         break;
<a name="L168" href="source/net/ipv4/xfrm4_protocol.c#L168">168</a> }
<a name="L169" href="source/net/ipv4/xfrm4_protocol.c#L169">169</a> 
<a name="L170" href="source/net/ipv4/xfrm4_protocol.c#L170">170</a> static const struct <a href="ident?i=net_protocol">net_protocol</a> <a href="ident?i=esp4_protocol">esp4_protocol</a> = {
<a name="L171" href="source/net/ipv4/xfrm4_protocol.c#L171">171</a>         .<a href="ident?i=handler">handler</a>        =       <a href="ident?i=xfrm4_esp_rcv">xfrm4_esp_rcv</a>,
<a name="L172" href="source/net/ipv4/xfrm4_protocol.c#L172">172</a>         .<a href="ident?i=err_handler">err_handler</a>    =       <a href="ident?i=xfrm4_esp_err">xfrm4_esp_err</a>,
<a name="L173" href="source/net/ipv4/xfrm4_protocol.c#L173">173</a>         .no_policy      =       1,
<a name="L174" href="source/net/ipv4/xfrm4_protocol.c#L174">174</a>         .netns_ok       =       1,
<a name="L175" href="source/net/ipv4/xfrm4_protocol.c#L175">175</a> };
<a name="L176" href="source/net/ipv4/xfrm4_protocol.c#L176">176</a> 
<a name="L177" href="source/net/ipv4/xfrm4_protocol.c#L177">177</a> static const struct <a href="ident?i=net_protocol">net_protocol</a> <a href="ident?i=ah4_protocol">ah4_protocol</a> = {
<a name="L178" href="source/net/ipv4/xfrm4_protocol.c#L178">178</a>         .<a href="ident?i=handler">handler</a>        =       <a href="ident?i=xfrm4_ah_rcv">xfrm4_ah_rcv</a>,
<a name="L179" href="source/net/ipv4/xfrm4_protocol.c#L179">179</a>         .<a href="ident?i=err_handler">err_handler</a>    =       <a href="ident?i=xfrm4_ah_err">xfrm4_ah_err</a>,
<a name="L180" href="source/net/ipv4/xfrm4_protocol.c#L180">180</a>         .no_policy      =       1,
<a name="L181" href="source/net/ipv4/xfrm4_protocol.c#L181">181</a>         .netns_ok       =       1,
<a name="L182" href="source/net/ipv4/xfrm4_protocol.c#L182">182</a> };
<a name="L183" href="source/net/ipv4/xfrm4_protocol.c#L183">183</a> 
<a name="L184" href="source/net/ipv4/xfrm4_protocol.c#L184">184</a> static const struct <a href="ident?i=net_protocol">net_protocol</a> <a href="ident?i=ipcomp4_protocol">ipcomp4_protocol</a> = {
<a name="L185" href="source/net/ipv4/xfrm4_protocol.c#L185">185</a>         .<a href="ident?i=handler">handler</a>        =       <a href="ident?i=xfrm4_ipcomp_rcv">xfrm4_ipcomp_rcv</a>,
<a name="L186" href="source/net/ipv4/xfrm4_protocol.c#L186">186</a>         .<a href="ident?i=err_handler">err_handler</a>    =       <a href="ident?i=xfrm4_ipcomp_err">xfrm4_ipcomp_err</a>,
<a name="L187" href="source/net/ipv4/xfrm4_protocol.c#L187">187</a>         .no_policy      =       1,
<a name="L188" href="source/net/ipv4/xfrm4_protocol.c#L188">188</a>         .netns_ok       =       1,
<a name="L189" href="source/net/ipv4/xfrm4_protocol.c#L189">189</a> };
<a name="L190" href="source/net/ipv4/xfrm4_protocol.c#L190">190</a> 
<a name="L191" href="source/net/ipv4/xfrm4_protocol.c#L191">191</a> static struct <a href="ident?i=xfrm_input_afinfo">xfrm_input_afinfo</a> <a href="ident?i=xfrm4_input_afinfo">xfrm4_input_afinfo</a> = {
<a name="L192" href="source/net/ipv4/xfrm4_protocol.c#L192">192</a>         .<a href="ident?i=family">family</a>         =       <a href="ident?i=AF_INET">AF_INET</a>,
<a name="L193" href="source/net/ipv4/xfrm4_protocol.c#L193">193</a>         .owner          =       <a href="ident?i=THIS_MODULE">THIS_MODULE</a>,
<a name="L194" href="source/net/ipv4/xfrm4_protocol.c#L194">194</a>         .<a href="ident?i=callback">callback</a>       =       <a href="ident?i=xfrm4_rcv_cb">xfrm4_rcv_cb</a>,
<a name="L195" href="source/net/ipv4/xfrm4_protocol.c#L195">195</a> };
<a name="L196" href="source/net/ipv4/xfrm4_protocol.c#L196">196</a> 
<a name="L197" href="source/net/ipv4/xfrm4_protocol.c#L197">197</a> static inline const struct <a href="ident?i=net_protocol">net_protocol</a> *<a href="ident?i=netproto">netproto</a>(unsigned char <a href="ident?i=protocol">protocol</a>)
<a name="L198" href="source/net/ipv4/xfrm4_protocol.c#L198">198</a> {
<a name="L199" href="source/net/ipv4/xfrm4_protocol.c#L199">199</a>         switch (<a href="ident?i=protocol">protocol</a>) {
<a name="L200" href="source/net/ipv4/xfrm4_protocol.c#L200">200</a>         case <a href="ident?i=IPPROTO_ESP">IPPROTO_ESP</a>:
<a name="L201" href="source/net/ipv4/xfrm4_protocol.c#L201">201</a>                 return &amp;<a href="ident?i=esp4_protocol">esp4_protocol</a>;
<a name="L202" href="source/net/ipv4/xfrm4_protocol.c#L202">202</a>         case <a href="ident?i=IPPROTO_AH">IPPROTO_AH</a>:
<a name="L203" href="source/net/ipv4/xfrm4_protocol.c#L203">203</a>                 return &amp;<a href="ident?i=ah4_protocol">ah4_protocol</a>;
<a name="L204" href="source/net/ipv4/xfrm4_protocol.c#L204">204</a>         case <a href="ident?i=IPPROTO_COMP">IPPROTO_COMP</a>:
<a name="L205" href="source/net/ipv4/xfrm4_protocol.c#L205">205</a>                 return &amp;<a href="ident?i=ipcomp4_protocol">ipcomp4_protocol</a>;
<a name="L206" href="source/net/ipv4/xfrm4_protocol.c#L206">206</a>         }
<a name="L207" href="source/net/ipv4/xfrm4_protocol.c#L207">207</a> 
<a name="L208" href="source/net/ipv4/xfrm4_protocol.c#L208">208</a>         return <a href="ident?i=NULL">NULL</a>;
<a name="L209" href="source/net/ipv4/xfrm4_protocol.c#L209">209</a> }
<a name="L210" href="source/net/ipv4/xfrm4_protocol.c#L210">210</a> 
<a name="L211" href="source/net/ipv4/xfrm4_protocol.c#L211">211</a> int <a href="ident?i=xfrm4_protocol_register">xfrm4_protocol_register</a>(struct <a href="ident?i=xfrm4_protocol">xfrm4_protocol</a> *<a href="ident?i=handler">handler</a>,
<a name="L212" href="source/net/ipv4/xfrm4_protocol.c#L212">212</a>                             unsigned char <a href="ident?i=protocol">protocol</a>)
<a name="L213" href="source/net/ipv4/xfrm4_protocol.c#L213">213</a> {
<a name="L214" href="source/net/ipv4/xfrm4_protocol.c#L214">214</a>         struct <a href="ident?i=xfrm4_protocol">xfrm4_protocol</a> <a href="ident?i=__rcu">__rcu</a> **pprev;
<a name="L215" href="source/net/ipv4/xfrm4_protocol.c#L215">215</a>         struct <a href="ident?i=xfrm4_protocol">xfrm4_protocol</a> *<a href="ident?i=t">t</a>;
<a name="L216" href="source/net/ipv4/xfrm4_protocol.c#L216">216</a>         <a href="ident?i=bool">bool</a> add_netproto = <a href="ident?i=false">false</a>;
<a name="L217" href="source/net/ipv4/xfrm4_protocol.c#L217">217</a>         int <a href="ident?i=ret">ret</a> = -<a href="ident?i=EEXIST">EEXIST</a>;
<a name="L218" href="source/net/ipv4/xfrm4_protocol.c#L218">218</a>         int <a href="ident?i=priority">priority</a> = <a href="ident?i=handler">handler</a>-&gt;<a href="ident?i=priority">priority</a>;
<a name="L219" href="source/net/ipv4/xfrm4_protocol.c#L219">219</a> 
<a name="L220" href="source/net/ipv4/xfrm4_protocol.c#L220">220</a>         if (!<a href="ident?i=proto_handlers">proto_handlers</a>(<a href="ident?i=protocol">protocol</a>) || !<a href="ident?i=netproto">netproto</a>(<a href="ident?i=protocol">protocol</a>))
<a name="L221" href="source/net/ipv4/xfrm4_protocol.c#L221">221</a>                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L222" href="source/net/ipv4/xfrm4_protocol.c#L222">222</a> 
<a name="L223" href="source/net/ipv4/xfrm4_protocol.c#L223">223</a>         <a href="ident?i=mutex_lock">mutex_lock</a>(&amp;xfrm4_protocol_mutex);
<a name="L224" href="source/net/ipv4/xfrm4_protocol.c#L224">224</a> 
<a name="L225" href="source/net/ipv4/xfrm4_protocol.c#L225">225</a>         if (!<a href="ident?i=rcu_dereference_protected">rcu_dereference_protected</a>(*<a href="ident?i=proto_handlers">proto_handlers</a>(<a href="ident?i=protocol">protocol</a>),
<a name="L226" href="source/net/ipv4/xfrm4_protocol.c#L226">226</a>                                        <a href="ident?i=lockdep_is_held">lockdep_is_held</a>(&amp;xfrm4_protocol_mutex)))
<a name="L227" href="source/net/ipv4/xfrm4_protocol.c#L227">227</a>                 add_netproto = <a href="ident?i=true">true</a>;
<a name="L228" href="source/net/ipv4/xfrm4_protocol.c#L228">228</a> 
<a name="L229" href="source/net/ipv4/xfrm4_protocol.c#L229">229</a>         for (pprev = <a href="ident?i=proto_handlers">proto_handlers</a>(<a href="ident?i=protocol">protocol</a>);
<a name="L230" href="source/net/ipv4/xfrm4_protocol.c#L230">230</a>              (<a href="ident?i=t">t</a> = <a href="ident?i=rcu_dereference_protected">rcu_dereference_protected</a>(*pprev,
<a name="L231" href="source/net/ipv4/xfrm4_protocol.c#L231">231</a>                         <a href="ident?i=lockdep_is_held">lockdep_is_held</a>(&amp;xfrm4_protocol_mutex))) != <a href="ident?i=NULL">NULL</a>;
<a name="L232" href="source/net/ipv4/xfrm4_protocol.c#L232">232</a>              pprev = &amp;<a href="ident?i=t">t</a>-&gt;<a href="ident?i=next">next</a>) {
<a name="L233" href="source/net/ipv4/xfrm4_protocol.c#L233">233</a>                 if (<a href="ident?i=t">t</a>-&gt;<a href="ident?i=priority">priority</a> &lt; <a href="ident?i=priority">priority</a>)
<a name="L234" href="source/net/ipv4/xfrm4_protocol.c#L234">234</a>                         break;
<a name="L235" href="source/net/ipv4/xfrm4_protocol.c#L235">235</a>                 if (<a href="ident?i=t">t</a>-&gt;<a href="ident?i=priority">priority</a> == <a href="ident?i=priority">priority</a>)
<a name="L236" href="source/net/ipv4/xfrm4_protocol.c#L236">236</a>                         goto <a href="ident?i=err">err</a>;
<a name="L237" href="source/net/ipv4/xfrm4_protocol.c#L237">237</a>         }
<a name="L238" href="source/net/ipv4/xfrm4_protocol.c#L238">238</a> 
<a name="L239" href="source/net/ipv4/xfrm4_protocol.c#L239">239</a>         <a href="ident?i=handler">handler</a>-&gt;<a href="ident?i=next">next</a> = *pprev;
<a name="L240" href="source/net/ipv4/xfrm4_protocol.c#L240">240</a>         <a href="ident?i=rcu_assign_pointer">rcu_assign_pointer</a>(*pprev, <a href="ident?i=handler">handler</a>);
<a name="L241" href="source/net/ipv4/xfrm4_protocol.c#L241">241</a> 
<a name="L242" href="source/net/ipv4/xfrm4_protocol.c#L242">242</a>         <a href="ident?i=ret">ret</a> = 0;
<a name="L243" href="source/net/ipv4/xfrm4_protocol.c#L243">243</a> 
<a name="L244" href="source/net/ipv4/xfrm4_protocol.c#L244">244</a> <a href="ident?i=err">err</a>:
<a name="L245" href="source/net/ipv4/xfrm4_protocol.c#L245">245</a>         <a href="ident?i=mutex_unlock">mutex_unlock</a>(&amp;xfrm4_protocol_mutex);
<a name="L246" href="source/net/ipv4/xfrm4_protocol.c#L246">246</a> 
<a name="L247" href="source/net/ipv4/xfrm4_protocol.c#L247">247</a>         if (add_netproto) {
<a name="L248" href="source/net/ipv4/xfrm4_protocol.c#L248">248</a>                 if (<a href="ident?i=inet_add_protocol">inet_add_protocol</a>(<a href="ident?i=netproto">netproto</a>(<a href="ident?i=protocol">protocol</a>), <a href="ident?i=protocol">protocol</a>)) {
<a name="L249" href="source/net/ipv4/xfrm4_protocol.c#L249">249</a>                         <a href="ident?i=pr_err">pr_err</a>(<i>"%s: can't add protocol\n"</i>, <a href="ident?i=__func__">__func__</a>);
<a name="L250" href="source/net/ipv4/xfrm4_protocol.c#L250">250</a>                         <a href="ident?i=ret">ret</a> = -<a href="ident?i=EAGAIN">EAGAIN</a>;
<a name="L251" href="source/net/ipv4/xfrm4_protocol.c#L251">251</a>                 }
<a name="L252" href="source/net/ipv4/xfrm4_protocol.c#L252">252</a>         }
<a name="L253" href="source/net/ipv4/xfrm4_protocol.c#L253">253</a> 
<a name="L254" href="source/net/ipv4/xfrm4_protocol.c#L254">254</a>         return <a href="ident?i=ret">ret</a>;
<a name="L255" href="source/net/ipv4/xfrm4_protocol.c#L255">255</a> }
<a name="L256" href="source/net/ipv4/xfrm4_protocol.c#L256">256</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=xfrm4_protocol_register">xfrm4_protocol_register</a>);
<a name="L257" href="source/net/ipv4/xfrm4_protocol.c#L257">257</a> 
<a name="L258" href="source/net/ipv4/xfrm4_protocol.c#L258">258</a> int <a href="ident?i=xfrm4_protocol_deregister">xfrm4_protocol_deregister</a>(struct <a href="ident?i=xfrm4_protocol">xfrm4_protocol</a> *<a href="ident?i=handler">handler</a>,
<a name="L259" href="source/net/ipv4/xfrm4_protocol.c#L259">259</a>                               unsigned char <a href="ident?i=protocol">protocol</a>)
<a name="L260" href="source/net/ipv4/xfrm4_protocol.c#L260">260</a> {
<a name="L261" href="source/net/ipv4/xfrm4_protocol.c#L261">261</a>         struct <a href="ident?i=xfrm4_protocol">xfrm4_protocol</a> <a href="ident?i=__rcu">__rcu</a> **pprev;
<a name="L262" href="source/net/ipv4/xfrm4_protocol.c#L262">262</a>         struct <a href="ident?i=xfrm4_protocol">xfrm4_protocol</a> *<a href="ident?i=t">t</a>;
<a name="L263" href="source/net/ipv4/xfrm4_protocol.c#L263">263</a>         int <a href="ident?i=ret">ret</a> = -<a href="ident?i=ENOENT">ENOENT</a>;
<a name="L264" href="source/net/ipv4/xfrm4_protocol.c#L264">264</a> 
<a name="L265" href="source/net/ipv4/xfrm4_protocol.c#L265">265</a>         if (!<a href="ident?i=proto_handlers">proto_handlers</a>(<a href="ident?i=protocol">protocol</a>) || !<a href="ident?i=netproto">netproto</a>(<a href="ident?i=protocol">protocol</a>))
<a name="L266" href="source/net/ipv4/xfrm4_protocol.c#L266">266</a>                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L267" href="source/net/ipv4/xfrm4_protocol.c#L267">267</a> 
<a name="L268" href="source/net/ipv4/xfrm4_protocol.c#L268">268</a>         <a href="ident?i=mutex_lock">mutex_lock</a>(&amp;xfrm4_protocol_mutex);
<a name="L269" href="source/net/ipv4/xfrm4_protocol.c#L269">269</a> 
<a name="L270" href="source/net/ipv4/xfrm4_protocol.c#L270">270</a>         for (pprev = <a href="ident?i=proto_handlers">proto_handlers</a>(<a href="ident?i=protocol">protocol</a>);
<a name="L271" href="source/net/ipv4/xfrm4_protocol.c#L271">271</a>              (<a href="ident?i=t">t</a> = <a href="ident?i=rcu_dereference_protected">rcu_dereference_protected</a>(*pprev,
<a name="L272" href="source/net/ipv4/xfrm4_protocol.c#L272">272</a>                         <a href="ident?i=lockdep_is_held">lockdep_is_held</a>(&amp;xfrm4_protocol_mutex))) != <a href="ident?i=NULL">NULL</a>;
<a name="L273" href="source/net/ipv4/xfrm4_protocol.c#L273">273</a>              pprev = &amp;<a href="ident?i=t">t</a>-&gt;<a href="ident?i=next">next</a>) {
<a name="L274" href="source/net/ipv4/xfrm4_protocol.c#L274">274</a>                 if (<a href="ident?i=t">t</a> == <a href="ident?i=handler">handler</a>) {
<a name="L275" href="source/net/ipv4/xfrm4_protocol.c#L275">275</a>                         *pprev = <a href="ident?i=handler">handler</a>-&gt;<a href="ident?i=next">next</a>;
<a name="L276" href="source/net/ipv4/xfrm4_protocol.c#L276">276</a>                         <a href="ident?i=ret">ret</a> = 0;
<a name="L277" href="source/net/ipv4/xfrm4_protocol.c#L277">277</a>                         break;
<a name="L278" href="source/net/ipv4/xfrm4_protocol.c#L278">278</a>                 }
<a name="L279" href="source/net/ipv4/xfrm4_protocol.c#L279">279</a>         }
<a name="L280" href="source/net/ipv4/xfrm4_protocol.c#L280">280</a> 
<a name="L281" href="source/net/ipv4/xfrm4_protocol.c#L281">281</a>         if (!<a href="ident?i=rcu_dereference_protected">rcu_dereference_protected</a>(*<a href="ident?i=proto_handlers">proto_handlers</a>(<a href="ident?i=protocol">protocol</a>),
<a name="L282" href="source/net/ipv4/xfrm4_protocol.c#L282">282</a>                                        <a href="ident?i=lockdep_is_held">lockdep_is_held</a>(&amp;xfrm4_protocol_mutex))) {
<a name="L283" href="source/net/ipv4/xfrm4_protocol.c#L283">283</a>                 if (<a href="ident?i=inet_del_protocol">inet_del_protocol</a>(<a href="ident?i=netproto">netproto</a>(<a href="ident?i=protocol">protocol</a>), <a href="ident?i=protocol">protocol</a>) &lt; 0) {
<a name="L284" href="source/net/ipv4/xfrm4_protocol.c#L284">284</a>                         <a href="ident?i=pr_err">pr_err</a>(<i>"%s: can't remove protocol\n"</i>, <a href="ident?i=__func__">__func__</a>);
<a name="L285" href="source/net/ipv4/xfrm4_protocol.c#L285">285</a>                         <a href="ident?i=ret">ret</a> = -<a href="ident?i=EAGAIN">EAGAIN</a>;
<a name="L286" href="source/net/ipv4/xfrm4_protocol.c#L286">286</a>                 }
<a name="L287" href="source/net/ipv4/xfrm4_protocol.c#L287">287</a>         }
<a name="L288" href="source/net/ipv4/xfrm4_protocol.c#L288">288</a> 
<a name="L289" href="source/net/ipv4/xfrm4_protocol.c#L289">289</a>         <a href="ident?i=mutex_unlock">mutex_unlock</a>(&amp;xfrm4_protocol_mutex);
<a name="L290" href="source/net/ipv4/xfrm4_protocol.c#L290">290</a> 
<a name="L291" href="source/net/ipv4/xfrm4_protocol.c#L291">291</a>         <a href="ident?i=synchronize_net">synchronize_net</a>();
<a name="L292" href="source/net/ipv4/xfrm4_protocol.c#L292">292</a> 
<a name="L293" href="source/net/ipv4/xfrm4_protocol.c#L293">293</a>         return <a href="ident?i=ret">ret</a>;
<a name="L294" href="source/net/ipv4/xfrm4_protocol.c#L294">294</a> }
<a name="L295" href="source/net/ipv4/xfrm4_protocol.c#L295">295</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=xfrm4_protocol_deregister">xfrm4_protocol_deregister</a>);
<a name="L296" href="source/net/ipv4/xfrm4_protocol.c#L296">296</a> 
<a name="L297" href="source/net/ipv4/xfrm4_protocol.c#L297">297</a> void <a href="ident?i=__init">__init</a> <a href="ident?i=xfrm4_protocol_init">xfrm4_protocol_init</a>(void)
<a name="L298" href="source/net/ipv4/xfrm4_protocol.c#L298">298</a> {
<a name="L299" href="source/net/ipv4/xfrm4_protocol.c#L299">299</a>         <a href="ident?i=xfrm_input_register_afinfo">xfrm_input_register_afinfo</a>(&amp;<a href="ident?i=xfrm4_input_afinfo">xfrm4_input_afinfo</a>);
<a name="L300" href="source/net/ipv4/xfrm4_protocol.c#L300">300</a> }
<a name="L301" href="source/net/ipv4/xfrm4_protocol.c#L301">301</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=xfrm4_protocol_init">xfrm4_protocol_init</a>);
<a name="L302" href="source/net/ipv4/xfrm4_protocol.c#L302">302</a> </pre></div><p>
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
