<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title>Linux/net/ipv4/xfrm4_tunnel.c - Linux Cross Reference - Free Electrons</title>
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
		 &nbsp;&bull;&nbsp;<b><i>source navigation</i></b> &nbsp;&bull;&nbsp;<a href="diff/net/ipv4/xfrm4_tunnel.c">diff markup</a> &nbsp;&bull;&nbsp;<a href="ident">identifier search</a> &nbsp;&bull;&nbsp;<a href="search">freetext search</a> &nbsp;&bull;&nbsp;
		</p>
	</div>
</div>

<div id="topbar">
  
  <p>Version: &nbsp;<a href="source/net/ipv4/xfrm4_tunnel.c?v=2.0.40">2.0.40</a>&nbsp;<a href="source/net/ipv4/xfrm4_tunnel.c?v=2.2.26">2.2.26</a>&nbsp;<a href="source/net/ipv4/xfrm4_tunnel.c?v=2.4.37">2.4.37</a>&nbsp;<a href="source/net/ipv4/xfrm4_tunnel.c?v=3.5">3.5</a>&nbsp;<a href="source/net/ipv4/xfrm4_tunnel.c?v=3.6">3.6</a>&nbsp;<a href="source/net/ipv4/xfrm4_tunnel.c?v=3.7">3.7</a>&nbsp;<a href="source/net/ipv4/xfrm4_tunnel.c?v=3.8">3.8</a>&nbsp;<a href="source/net/ipv4/xfrm4_tunnel.c?v=3.9">3.9</a>&nbsp;<a href="source/net/ipv4/xfrm4_tunnel.c?v=3.10">3.10</a>&nbsp;<a href="source/net/ipv4/xfrm4_tunnel.c?v=3.11">3.11</a>&nbsp;<a href="source/net/ipv4/xfrm4_tunnel.c?v=3.12">3.12</a>&nbsp;<a href="source/net/ipv4/xfrm4_tunnel.c?v=3.13">3.13</a>&nbsp;<a href="source/net/ipv4/xfrm4_tunnel.c?v=3.14">3.14</a>&nbsp;<a href="source/net/ipv4/xfrm4_tunnel.c?v=3.15">3.15</a>&nbsp;<a href="source/net/ipv4/xfrm4_tunnel.c?v=3.16">3.16</a>&nbsp;<a href="source/net/ipv4/xfrm4_tunnel.c?v=3.17">3.17</a>&nbsp;<a href="source/net/ipv4/xfrm4_tunnel.c?v=3.18">3.18</a>&nbsp;<a href="source/net/ipv4/xfrm4_tunnel.c?v=3.19">3.19</a>&nbsp;<a href="source/net/ipv4/xfrm4_tunnel.c?v=4.0">4.0</a>&nbsp;<b><i>4.1</i></b></p>
  
</div>

<h1><a href="source/">Linux</a>/<a href="source/net/">net</a>/<a href="source/net/ipv4/">ipv4</a>/<a href="source/net/ipv4/xfrm4_tunnel.c">xfrm4_tunnel.c</a></h1>
<div id="lxrcode"><pre>  <a name="L1" href="source/net/ipv4/xfrm4_tunnel.c#L1">1</a> <b><i>/* xfrm4_tunnel.c: Generic IP tunnel transformer.</i></b>
  <a name="L2" href="source/net/ipv4/xfrm4_tunnel.c#L2">2</a> <b><i> *</i></b>
  <a name="L3" href="source/net/ipv4/xfrm4_tunnel.c#L3">3</a> <b><i> * Copyright (C) 2003 David S. Miller (davem@redhat.com)</i></b>
  <a name="L4" href="source/net/ipv4/xfrm4_tunnel.c#L4">4</a> <b><i> */</i></b>
  <a name="L5" href="source/net/ipv4/xfrm4_tunnel.c#L5">5</a> 
  <a name="L6" href="source/net/ipv4/xfrm4_tunnel.c#L6">6</a> #define <a href="ident?i=pr_fmt">pr_fmt</a>(<a href="ident?i=fmt">fmt</a>) <i>"IPsec: "</i> <a href="ident?i=fmt">fmt</a>
  <a name="L7" href="source/net/ipv4/xfrm4_tunnel.c#L7">7</a> 
  <a name="L8" href="source/net/ipv4/xfrm4_tunnel.c#L8">8</a> #include &lt;linux/skbuff.h&gt;
  <a name="L9" href="source/net/ipv4/xfrm4_tunnel.c#L9">9</a> #include &lt;linux/module.h&gt;
 <a name="L10" href="source/net/ipv4/xfrm4_tunnel.c#L10">10</a> #include &lt;linux/mutex.h&gt;
 <a name="L11" href="source/net/ipv4/xfrm4_tunnel.c#L11">11</a> #include &lt;net/xfrm.h&gt;
 <a name="L12" href="source/net/ipv4/xfrm4_tunnel.c#L12">12</a> #include &lt;net/ip.h&gt;
 <a name="L13" href="source/net/ipv4/xfrm4_tunnel.c#L13">13</a> #include &lt;net/protocol.h&gt;
 <a name="L14" href="source/net/ipv4/xfrm4_tunnel.c#L14">14</a> 
 <a name="L15" href="source/net/ipv4/xfrm4_tunnel.c#L15">15</a> static int <a href="ident?i=ipip_output">ipip_output</a>(struct <a href="ident?i=xfrm_state">xfrm_state</a> *<a href="ident?i=x">x</a>, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
 <a name="L16" href="source/net/ipv4/xfrm4_tunnel.c#L16">16</a> {
 <a name="L17" href="source/net/ipv4/xfrm4_tunnel.c#L17">17</a>         <a href="ident?i=skb_push">skb_push</a>(<a href="ident?i=skb">skb</a>, -<a href="ident?i=skb_network_offset">skb_network_offset</a>(<a href="ident?i=skb">skb</a>));
 <a name="L18" href="source/net/ipv4/xfrm4_tunnel.c#L18">18</a>         return 0;
 <a name="L19" href="source/net/ipv4/xfrm4_tunnel.c#L19">19</a> }
 <a name="L20" href="source/net/ipv4/xfrm4_tunnel.c#L20">20</a> 
 <a name="L21" href="source/net/ipv4/xfrm4_tunnel.c#L21">21</a> static int <a href="ident?i=ipip_xfrm_rcv">ipip_xfrm_rcv</a>(struct <a href="ident?i=xfrm_state">xfrm_state</a> *<a href="ident?i=x">x</a>, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
 <a name="L22" href="source/net/ipv4/xfrm4_tunnel.c#L22">22</a> {
 <a name="L23" href="source/net/ipv4/xfrm4_tunnel.c#L23">23</a>         return <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=protocol">protocol</a>;
 <a name="L24" href="source/net/ipv4/xfrm4_tunnel.c#L24">24</a> }
 <a name="L25" href="source/net/ipv4/xfrm4_tunnel.c#L25">25</a> 
 <a name="L26" href="source/net/ipv4/xfrm4_tunnel.c#L26">26</a> static int <a href="ident?i=ipip_init_state">ipip_init_state</a>(struct <a href="ident?i=xfrm_state">xfrm_state</a> *<a href="ident?i=x">x</a>)
 <a name="L27" href="source/net/ipv4/xfrm4_tunnel.c#L27">27</a> {
 <a name="L28" href="source/net/ipv4/xfrm4_tunnel.c#L28">28</a>         if (<a href="ident?i=x">x</a>-&gt;props.<a href="ident?i=mode">mode</a> != <a href="ident?i=XFRM_MODE_TUNNEL">XFRM_MODE_TUNNEL</a>)
 <a name="L29" href="source/net/ipv4/xfrm4_tunnel.c#L29">29</a>                 return -<a href="ident?i=EINVAL">EINVAL</a>;
 <a name="L30" href="source/net/ipv4/xfrm4_tunnel.c#L30">30</a> 
 <a name="L31" href="source/net/ipv4/xfrm4_tunnel.c#L31">31</a>         if (<a href="ident?i=x">x</a>-&gt;encap)
 <a name="L32" href="source/net/ipv4/xfrm4_tunnel.c#L32">32</a>                 return -<a href="ident?i=EINVAL">EINVAL</a>;
 <a name="L33" href="source/net/ipv4/xfrm4_tunnel.c#L33">33</a> 
 <a name="L34" href="source/net/ipv4/xfrm4_tunnel.c#L34">34</a>         <a href="ident?i=x">x</a>-&gt;props.<a href="ident?i=header_len">header_len</a> = sizeof(struct <a href="ident?i=iphdr">iphdr</a>);
 <a name="L35" href="source/net/ipv4/xfrm4_tunnel.c#L35">35</a> 
 <a name="L36" href="source/net/ipv4/xfrm4_tunnel.c#L36">36</a>         return 0;
 <a name="L37" href="source/net/ipv4/xfrm4_tunnel.c#L37">37</a> }
 <a name="L38" href="source/net/ipv4/xfrm4_tunnel.c#L38">38</a> 
 <a name="L39" href="source/net/ipv4/xfrm4_tunnel.c#L39">39</a> static void <a href="ident?i=ipip_destroy">ipip_destroy</a>(struct <a href="ident?i=xfrm_state">xfrm_state</a> *<a href="ident?i=x">x</a>)
 <a name="L40" href="source/net/ipv4/xfrm4_tunnel.c#L40">40</a> {
 <a name="L41" href="source/net/ipv4/xfrm4_tunnel.c#L41">41</a> }
 <a name="L42" href="source/net/ipv4/xfrm4_tunnel.c#L42">42</a> 
 <a name="L43" href="source/net/ipv4/xfrm4_tunnel.c#L43">43</a> static const struct <a href="ident?i=xfrm_type">xfrm_type</a> <a href="ident?i=ipip_type">ipip_type</a> = {
 <a name="L44" href="source/net/ipv4/xfrm4_tunnel.c#L44">44</a>         .description    = <i>"IPIP"</i>,
 <a name="L45" href="source/net/ipv4/xfrm4_tunnel.c#L45">45</a>         .owner          = <a href="ident?i=THIS_MODULE">THIS_MODULE</a>,
 <a name="L46" href="source/net/ipv4/xfrm4_tunnel.c#L46">46</a>         .<a href="ident?i=proto">proto</a>          = <a href="ident?i=IPPROTO_IPIP">IPPROTO_IPIP</a>,
 <a name="L47" href="source/net/ipv4/xfrm4_tunnel.c#L47">47</a>         .<a href="ident?i=init_state">init_state</a>     = <a href="ident?i=ipip_init_state">ipip_init_state</a>,
 <a name="L48" href="source/net/ipv4/xfrm4_tunnel.c#L48">48</a>         .destructor     = <a href="ident?i=ipip_destroy">ipip_destroy</a>,
 <a name="L49" href="source/net/ipv4/xfrm4_tunnel.c#L49">49</a>         .<a href="ident?i=input">input</a>          = <a href="ident?i=ipip_xfrm_rcv">ipip_xfrm_rcv</a>,
 <a name="L50" href="source/net/ipv4/xfrm4_tunnel.c#L50">50</a>         .<a href="ident?i=output">output</a>         = <a href="ident?i=ipip_output">ipip_output</a>
 <a name="L51" href="source/net/ipv4/xfrm4_tunnel.c#L51">51</a> };
 <a name="L52" href="source/net/ipv4/xfrm4_tunnel.c#L52">52</a> 
 <a name="L53" href="source/net/ipv4/xfrm4_tunnel.c#L53">53</a> static int <a href="ident?i=xfrm_tunnel_rcv">xfrm_tunnel_rcv</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
 <a name="L54" href="source/net/ipv4/xfrm4_tunnel.c#L54">54</a> {
 <a name="L55" href="source/net/ipv4/xfrm4_tunnel.c#L55">55</a>         return <a href="ident?i=xfrm4_rcv_spi">xfrm4_rcv_spi</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=IPPROTO_IPIP">IPPROTO_IPIP</a>, <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=saddr">saddr</a>);
 <a name="L56" href="source/net/ipv4/xfrm4_tunnel.c#L56">56</a> }
 <a name="L57" href="source/net/ipv4/xfrm4_tunnel.c#L57">57</a> 
 <a name="L58" href="source/net/ipv4/xfrm4_tunnel.c#L58">58</a> static int <a href="ident?i=xfrm_tunnel_err">xfrm_tunnel_err</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, <a href="ident?i=u32">u32</a> <a href="ident?i=info">info</a>)
 <a name="L59" href="source/net/ipv4/xfrm4_tunnel.c#L59">59</a> {
 <a name="L60" href="source/net/ipv4/xfrm4_tunnel.c#L60">60</a>         return -<a href="ident?i=ENOENT">ENOENT</a>;
 <a name="L61" href="source/net/ipv4/xfrm4_tunnel.c#L61">61</a> }
 <a name="L62" href="source/net/ipv4/xfrm4_tunnel.c#L62">62</a> 
 <a name="L63" href="source/net/ipv4/xfrm4_tunnel.c#L63">63</a> static struct <a href="ident?i=xfrm_tunnel">xfrm_tunnel</a> xfrm_tunnel_handler <a href="ident?i=__read_mostly">__read_mostly</a> = {
 <a name="L64" href="source/net/ipv4/xfrm4_tunnel.c#L64">64</a>         .<a href="ident?i=handler">handler</a>        =       <a href="ident?i=xfrm_tunnel_rcv">xfrm_tunnel_rcv</a>,
 <a name="L65" href="source/net/ipv4/xfrm4_tunnel.c#L65">65</a>         .<a href="ident?i=err_handler">err_handler</a>    =       <a href="ident?i=xfrm_tunnel_err">xfrm_tunnel_err</a>,
 <a name="L66" href="source/net/ipv4/xfrm4_tunnel.c#L66">66</a>         .<a href="ident?i=priority">priority</a>       =       3,
 <a name="L67" href="source/net/ipv4/xfrm4_tunnel.c#L67">67</a> };
 <a name="L68" href="source/net/ipv4/xfrm4_tunnel.c#L68">68</a> 
 <a name="L69" href="source/net/ipv4/xfrm4_tunnel.c#L69">69</a> #if <a href="ident?i=IS_ENABLED">IS_ENABLED</a>(CONFIG_IPV6)
 <a name="L70" href="source/net/ipv4/xfrm4_tunnel.c#L70">70</a> static struct <a href="ident?i=xfrm_tunnel">xfrm_tunnel</a> xfrm64_tunnel_handler <a href="ident?i=__read_mostly">__read_mostly</a> = {
 <a name="L71" href="source/net/ipv4/xfrm4_tunnel.c#L71">71</a>         .<a href="ident?i=handler">handler</a>        =       <a href="ident?i=xfrm_tunnel_rcv">xfrm_tunnel_rcv</a>,
 <a name="L72" href="source/net/ipv4/xfrm4_tunnel.c#L72">72</a>         .<a href="ident?i=err_handler">err_handler</a>    =       <a href="ident?i=xfrm_tunnel_err">xfrm_tunnel_err</a>,
 <a name="L73" href="source/net/ipv4/xfrm4_tunnel.c#L73">73</a>         .<a href="ident?i=priority">priority</a>       =       2,
 <a name="L74" href="source/net/ipv4/xfrm4_tunnel.c#L74">74</a> };
 <a name="L75" href="source/net/ipv4/xfrm4_tunnel.c#L75">75</a> #endif
 <a name="L76" href="source/net/ipv4/xfrm4_tunnel.c#L76">76</a> 
 <a name="L77" href="source/net/ipv4/xfrm4_tunnel.c#L77">77</a> static int <a href="ident?i=__init">__init</a> <a href="ident?i=ipip_init">ipip_init</a>(void)
 <a name="L78" href="source/net/ipv4/xfrm4_tunnel.c#L78">78</a> {
 <a name="L79" href="source/net/ipv4/xfrm4_tunnel.c#L79">79</a>         if (<a href="ident?i=xfrm_register_type">xfrm_register_type</a>(&amp;<a href="ident?i=ipip_type">ipip_type</a>, <a href="ident?i=AF_INET">AF_INET</a>) &lt; 0) {
 <a name="L80" href="source/net/ipv4/xfrm4_tunnel.c#L80">80</a>                 <a href="ident?i=pr_info">pr_info</a>(<i>"%s: can't add xfrm type\n"</i>, <a href="ident?i=__func__">__func__</a>);
 <a name="L81" href="source/net/ipv4/xfrm4_tunnel.c#L81">81</a>                 return -<a href="ident?i=EAGAIN">EAGAIN</a>;
 <a name="L82" href="source/net/ipv4/xfrm4_tunnel.c#L82">82</a>         }
 <a name="L83" href="source/net/ipv4/xfrm4_tunnel.c#L83">83</a> 
 <a name="L84" href="source/net/ipv4/xfrm4_tunnel.c#L84">84</a>         if (<a href="ident?i=xfrm4_tunnel_register">xfrm4_tunnel_register</a>(&amp;xfrm_tunnel_handler, <a href="ident?i=AF_INET">AF_INET</a>)) {
 <a name="L85" href="source/net/ipv4/xfrm4_tunnel.c#L85">85</a>                 <a href="ident?i=pr_info">pr_info</a>(<i>"%s: can't add xfrm handler for AF_INET\n"</i>, <a href="ident?i=__func__">__func__</a>);
 <a name="L86" href="source/net/ipv4/xfrm4_tunnel.c#L86">86</a>                 <a href="ident?i=xfrm_unregister_type">xfrm_unregister_type</a>(&amp;<a href="ident?i=ipip_type">ipip_type</a>, <a href="ident?i=AF_INET">AF_INET</a>);
 <a name="L87" href="source/net/ipv4/xfrm4_tunnel.c#L87">87</a>                 return -<a href="ident?i=EAGAIN">EAGAIN</a>;
 <a name="L88" href="source/net/ipv4/xfrm4_tunnel.c#L88">88</a>         }
 <a name="L89" href="source/net/ipv4/xfrm4_tunnel.c#L89">89</a> #if <a href="ident?i=IS_ENABLED">IS_ENABLED</a>(CONFIG_IPV6)
 <a name="L90" href="source/net/ipv4/xfrm4_tunnel.c#L90">90</a>         if (<a href="ident?i=xfrm4_tunnel_register">xfrm4_tunnel_register</a>(&amp;xfrm64_tunnel_handler, <a href="ident?i=AF_INET6">AF_INET6</a>)) {
 <a name="L91" href="source/net/ipv4/xfrm4_tunnel.c#L91">91</a>                 <a href="ident?i=pr_info">pr_info</a>(<i>"%s: can't add xfrm handler for AF_INET6\n"</i>, <a href="ident?i=__func__">__func__</a>);
 <a name="L92" href="source/net/ipv4/xfrm4_tunnel.c#L92">92</a>                 <a href="ident?i=xfrm4_tunnel_deregister">xfrm4_tunnel_deregister</a>(&amp;xfrm_tunnel_handler, <a href="ident?i=AF_INET">AF_INET</a>);
 <a name="L93" href="source/net/ipv4/xfrm4_tunnel.c#L93">93</a>                 <a href="ident?i=xfrm_unregister_type">xfrm_unregister_type</a>(&amp;<a href="ident?i=ipip_type">ipip_type</a>, <a href="ident?i=AF_INET">AF_INET</a>);
 <a name="L94" href="source/net/ipv4/xfrm4_tunnel.c#L94">94</a>                 return -<a href="ident?i=EAGAIN">EAGAIN</a>;
 <a name="L95" href="source/net/ipv4/xfrm4_tunnel.c#L95">95</a>         }
 <a name="L96" href="source/net/ipv4/xfrm4_tunnel.c#L96">96</a> #endif
 <a name="L97" href="source/net/ipv4/xfrm4_tunnel.c#L97">97</a>         return 0;
 <a name="L98" href="source/net/ipv4/xfrm4_tunnel.c#L98">98</a> }
 <a name="L99" href="source/net/ipv4/xfrm4_tunnel.c#L99">99</a> 
<a name="L100" href="source/net/ipv4/xfrm4_tunnel.c#L100">100</a> static void <a href="ident?i=__exit">__exit</a> <a href="ident?i=ipip_fini">ipip_fini</a>(void)
<a name="L101" href="source/net/ipv4/xfrm4_tunnel.c#L101">101</a> {
<a name="L102" href="source/net/ipv4/xfrm4_tunnel.c#L102">102</a> #if <a href="ident?i=IS_ENABLED">IS_ENABLED</a>(CONFIG_IPV6)
<a name="L103" href="source/net/ipv4/xfrm4_tunnel.c#L103">103</a>         if (<a href="ident?i=xfrm4_tunnel_deregister">xfrm4_tunnel_deregister</a>(&amp;xfrm64_tunnel_handler, <a href="ident?i=AF_INET6">AF_INET6</a>))
<a name="L104" href="source/net/ipv4/xfrm4_tunnel.c#L104">104</a>                 <a href="ident?i=pr_info">pr_info</a>(<i>"%s: can't remove xfrm handler for AF_INET6\n"</i>,
<a name="L105" href="source/net/ipv4/xfrm4_tunnel.c#L105">105</a>                         <a href="ident?i=__func__">__func__</a>);
<a name="L106" href="source/net/ipv4/xfrm4_tunnel.c#L106">106</a> #endif
<a name="L107" href="source/net/ipv4/xfrm4_tunnel.c#L107">107</a>         if (<a href="ident?i=xfrm4_tunnel_deregister">xfrm4_tunnel_deregister</a>(&amp;xfrm_tunnel_handler, <a href="ident?i=AF_INET">AF_INET</a>))
<a name="L108" href="source/net/ipv4/xfrm4_tunnel.c#L108">108</a>                 <a href="ident?i=pr_info">pr_info</a>(<i>"%s: can't remove xfrm handler for AF_INET\n"</i>,
<a name="L109" href="source/net/ipv4/xfrm4_tunnel.c#L109">109</a>                         <a href="ident?i=__func__">__func__</a>);
<a name="L110" href="source/net/ipv4/xfrm4_tunnel.c#L110">110</a>         if (<a href="ident?i=xfrm_unregister_type">xfrm_unregister_type</a>(&amp;<a href="ident?i=ipip_type">ipip_type</a>, <a href="ident?i=AF_INET">AF_INET</a>) &lt; 0)
<a name="L111" href="source/net/ipv4/xfrm4_tunnel.c#L111">111</a>                 <a href="ident?i=pr_info">pr_info</a>(<i>"%s: can't remove xfrm type\n"</i>, <a href="ident?i=__func__">__func__</a>);
<a name="L112" href="source/net/ipv4/xfrm4_tunnel.c#L112">112</a> }
<a name="L113" href="source/net/ipv4/xfrm4_tunnel.c#L113">113</a> 
<a name="L114" href="source/net/ipv4/xfrm4_tunnel.c#L114">114</a> <a href="ident?i=module_init">module_init</a>(<a href="ident?i=ipip_init">ipip_init</a>);
<a name="L115" href="source/net/ipv4/xfrm4_tunnel.c#L115">115</a> <a href="ident?i=module_exit">module_exit</a>(<a href="ident?i=ipip_fini">ipip_fini</a>);
<a name="L116" href="source/net/ipv4/xfrm4_tunnel.c#L116">116</a> <a href="ident?i=MODULE_LICENSE">MODULE_LICENSE</a>(<i>"GPL"</i>);
<a name="L117" href="source/net/ipv4/xfrm4_tunnel.c#L117">117</a> <a href="ident?i=MODULE_ALIAS_XFRM_TYPE">MODULE_ALIAS_XFRM_TYPE</a>(<a href="ident?i=AF_INET">AF_INET</a>, <a href="ident?i=XFRM_PROTO_IPIP">XFRM_PROTO_IPIP</a>);
<a name="L118" href="source/net/ipv4/xfrm4_tunnel.c#L118">118</a> </pre></div><p>
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
