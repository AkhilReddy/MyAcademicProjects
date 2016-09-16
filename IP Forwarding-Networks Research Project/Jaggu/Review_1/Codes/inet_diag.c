<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title>Linux/net/ipv4/inet_diag.c - Linux Cross Reference - Free Electrons</title>
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
		 &nbsp;&bull;&nbsp;<b><i>source navigation</i></b> &nbsp;&bull;&nbsp;<a href="diff/net/ipv4/inet_diag.c">diff markup</a> &nbsp;&bull;&nbsp;<a href="ident">identifier search</a> &nbsp;&bull;&nbsp;<a href="search">freetext search</a> &nbsp;&bull;&nbsp;
		</p>
	</div>
</div>

<div id="topbar">
  
  <p>Version: &nbsp;<a href="source/net/ipv4/inet_diag.c?v=2.0.40">2.0.40</a>&nbsp;<a href="source/net/ipv4/inet_diag.c?v=2.2.26">2.2.26</a>&nbsp;<a href="source/net/ipv4/inet_diag.c?v=2.4.37">2.4.37</a>&nbsp;<a href="source/net/ipv4/inet_diag.c?v=3.5">3.5</a>&nbsp;<a href="source/net/ipv4/inet_diag.c?v=3.6">3.6</a>&nbsp;<a href="source/net/ipv4/inet_diag.c?v=3.7">3.7</a>&nbsp;<a href="source/net/ipv4/inet_diag.c?v=3.8">3.8</a>&nbsp;<a href="source/net/ipv4/inet_diag.c?v=3.9">3.9</a>&nbsp;<a href="source/net/ipv4/inet_diag.c?v=3.10">3.10</a>&nbsp;<a href="source/net/ipv4/inet_diag.c?v=3.11">3.11</a>&nbsp;<a href="source/net/ipv4/inet_diag.c?v=3.12">3.12</a>&nbsp;<a href="source/net/ipv4/inet_diag.c?v=3.13">3.13</a>&nbsp;<a href="source/net/ipv4/inet_diag.c?v=3.14">3.14</a>&nbsp;<a href="source/net/ipv4/inet_diag.c?v=3.15">3.15</a>&nbsp;<a href="source/net/ipv4/inet_diag.c?v=3.16">3.16</a>&nbsp;<a href="source/net/ipv4/inet_diag.c?v=3.17">3.17</a>&nbsp;<a href="source/net/ipv4/inet_diag.c?v=3.18">3.18</a>&nbsp;<a href="source/net/ipv4/inet_diag.c?v=3.19">3.19</a>&nbsp;<a href="source/net/ipv4/inet_diag.c?v=4.0">4.0</a>&nbsp;<b><i>4.1</i></b></p>
  
</div>

<h1><a href="source/">Linux</a>/<a href="source/net/">net</a>/<a href="source/net/ipv4/">ipv4</a>/<a href="source/net/ipv4/inet_diag.c">inet_diag.c</a></h1>
<div id="lxrcode"><pre>  <a name="L1" href="source/net/ipv4/inet_diag.c#L1">1</a> <b><i>/*</i></b>
  <a name="L2" href="source/net/ipv4/inet_diag.c#L2">2</a> <b><i> * inet_diag.c  Module for monitoring INET transport protocols sockets.</i></b>
  <a name="L3" href="source/net/ipv4/inet_diag.c#L3">3</a> <b><i> *</i></b>
  <a name="L4" href="source/net/ipv4/inet_diag.c#L4">4</a> <b><i> * Authors:     Alexey Kuznetsov, &lt;kuznet@ms2.inr.ac.ru&gt;</i></b>
  <a name="L5" href="source/net/ipv4/inet_diag.c#L5">5</a> <b><i> *</i></b>
  <a name="L6" href="source/net/ipv4/inet_diag.c#L6">6</a> <b><i> *      This program is free software; you can redistribute it and/or</i></b>
  <a name="L7" href="source/net/ipv4/inet_diag.c#L7">7</a> <b><i> *      modify it under the terms of the GNU General Public License</i></b>
  <a name="L8" href="source/net/ipv4/inet_diag.c#L8">8</a> <b><i> *      as published by the Free Software Foundation; either version</i></b>
  <a name="L9" href="source/net/ipv4/inet_diag.c#L9">9</a> <b><i> *      2 of the License, or (at your option) any later version.</i></b>
 <a name="L10" href="source/net/ipv4/inet_diag.c#L10">10</a> <b><i> */</i></b>
 <a name="L11" href="source/net/ipv4/inet_diag.c#L11">11</a> 
 <a name="L12" href="source/net/ipv4/inet_diag.c#L12">12</a> #include &lt;linux/kernel.h&gt;
 <a name="L13" href="source/net/ipv4/inet_diag.c#L13">13</a> #include &lt;linux/module.h&gt;
 <a name="L14" href="source/net/ipv4/inet_diag.c#L14">14</a> #include &lt;linux/types.h&gt;
 <a name="L15" href="source/net/ipv4/inet_diag.c#L15">15</a> #include &lt;linux/fcntl.h&gt;
 <a name="L16" href="source/net/ipv4/inet_diag.c#L16">16</a> #include &lt;linux/random.h&gt;
 <a name="L17" href="source/net/ipv4/inet_diag.c#L17">17</a> #include &lt;linux/slab.h&gt;
 <a name="L18" href="source/net/ipv4/inet_diag.c#L18">18</a> #include &lt;linux/cache.h&gt;
 <a name="L19" href="source/net/ipv4/inet_diag.c#L19">19</a> #include &lt;linux/init.h&gt;
 <a name="L20" href="source/net/ipv4/inet_diag.c#L20">20</a> #include &lt;linux/time.h&gt;
 <a name="L21" href="source/net/ipv4/inet_diag.c#L21">21</a> 
 <a name="L22" href="source/net/ipv4/inet_diag.c#L22">22</a> #include &lt;net/icmp.h&gt;
 <a name="L23" href="source/net/ipv4/inet_diag.c#L23">23</a> #include &lt;net/tcp.h&gt;
 <a name="L24" href="source/net/ipv4/inet_diag.c#L24">24</a> #include &lt;net/ipv6.h&gt;
 <a name="L25" href="source/net/ipv4/inet_diag.c#L25">25</a> #include &lt;net/inet_common.h&gt;
 <a name="L26" href="source/net/ipv4/inet_diag.c#L26">26</a> #include &lt;net/inet_connection_sock.h&gt;
 <a name="L27" href="source/net/ipv4/inet_diag.c#L27">27</a> #include &lt;net/inet_hashtables.h&gt;
 <a name="L28" href="source/net/ipv4/inet_diag.c#L28">28</a> #include &lt;net/inet_timewait_sock.h&gt;
 <a name="L29" href="source/net/ipv4/inet_diag.c#L29">29</a> #include &lt;net/inet6_hashtables.h&gt;
 <a name="L30" href="source/net/ipv4/inet_diag.c#L30">30</a> #include &lt;net/netlink.h&gt;
 <a name="L31" href="source/net/ipv4/inet_diag.c#L31">31</a> 
 <a name="L32" href="source/net/ipv4/inet_diag.c#L32">32</a> #include &lt;linux/inet.h&gt;
 <a name="L33" href="source/net/ipv4/inet_diag.c#L33">33</a> #include &lt;linux/stddef.h&gt;
 <a name="L34" href="source/net/ipv4/inet_diag.c#L34">34</a> 
 <a name="L35" href="source/net/ipv4/inet_diag.c#L35">35</a> #include &lt;linux/inet_diag.h&gt;
 <a name="L36" href="source/net/ipv4/inet_diag.c#L36">36</a> #include &lt;linux/sock_diag.h&gt;
 <a name="L37" href="source/net/ipv4/inet_diag.c#L37">37</a> 
 <a name="L38" href="source/net/ipv4/inet_diag.c#L38">38</a> static const struct <a href="ident?i=inet_diag_handler">inet_diag_handler</a> **<a href="ident?i=inet_diag_table">inet_diag_table</a>;
 <a name="L39" href="source/net/ipv4/inet_diag.c#L39">39</a> 
 <a name="L40" href="source/net/ipv4/inet_diag.c#L40">40</a> struct <a href="ident?i=inet_diag_entry">inet_diag_entry</a> {
 <a name="L41" href="source/net/ipv4/inet_diag.c#L41">41</a>         const <a href="ident?i=__be32">__be32</a> *<a href="ident?i=saddr">saddr</a>;
 <a name="L42" href="source/net/ipv4/inet_diag.c#L42">42</a>         const <a href="ident?i=__be32">__be32</a> *<a href="ident?i=daddr">daddr</a>;
 <a name="L43" href="source/net/ipv4/inet_diag.c#L43">43</a>         <a href="ident?i=u16">u16</a> sport;
 <a name="L44" href="source/net/ipv4/inet_diag.c#L44">44</a>         <a href="ident?i=u16">u16</a> dport;
 <a name="L45" href="source/net/ipv4/inet_diag.c#L45">45</a>         <a href="ident?i=u16">u16</a> <a href="ident?i=family">family</a>;
 <a name="L46" href="source/net/ipv4/inet_diag.c#L46">46</a>         <a href="ident?i=u16">u16</a> userlocks;
 <a name="L47" href="source/net/ipv4/inet_diag.c#L47">47</a> };
 <a name="L48" href="source/net/ipv4/inet_diag.c#L48">48</a> 
 <a name="L49" href="source/net/ipv4/inet_diag.c#L49">49</a> static <a href="ident?i=DEFINE_MUTEX">DEFINE_MUTEX</a>(inet_diag_table_mutex);
 <a name="L50" href="source/net/ipv4/inet_diag.c#L50">50</a> 
 <a name="L51" href="source/net/ipv4/inet_diag.c#L51">51</a> static const struct <a href="ident?i=inet_diag_handler">inet_diag_handler</a> *<a href="ident?i=inet_diag_lock_handler">inet_diag_lock_handler</a>(int <a href="ident?i=proto">proto</a>)
 <a name="L52" href="source/net/ipv4/inet_diag.c#L52">52</a> {
 <a name="L53" href="source/net/ipv4/inet_diag.c#L53">53</a>         if (!<a href="ident?i=inet_diag_table">inet_diag_table</a>[<a href="ident?i=proto">proto</a>])
 <a name="L54" href="source/net/ipv4/inet_diag.c#L54">54</a>                 <a href="ident?i=request_module">request_module</a>(<i>"net-pf-%d-proto-%d-type-%d-%d"</i>, <a href="ident?i=PF_NETLINK">PF_NETLINK</a>,
 <a name="L55" href="source/net/ipv4/inet_diag.c#L55">55</a>                                <a href="ident?i=NETLINK_SOCK_DIAG">NETLINK_SOCK_DIAG</a>, <a href="ident?i=AF_INET">AF_INET</a>, <a href="ident?i=proto">proto</a>);
 <a name="L56" href="source/net/ipv4/inet_diag.c#L56">56</a> 
 <a name="L57" href="source/net/ipv4/inet_diag.c#L57">57</a>         <a href="ident?i=mutex_lock">mutex_lock</a>(&amp;inet_diag_table_mutex);
 <a name="L58" href="source/net/ipv4/inet_diag.c#L58">58</a>         if (!<a href="ident?i=inet_diag_table">inet_diag_table</a>[<a href="ident?i=proto">proto</a>])
 <a name="L59" href="source/net/ipv4/inet_diag.c#L59">59</a>                 return <a href="ident?i=ERR_PTR">ERR_PTR</a>(-<a href="ident?i=ENOENT">ENOENT</a>);
 <a name="L60" href="source/net/ipv4/inet_diag.c#L60">60</a> 
 <a name="L61" href="source/net/ipv4/inet_diag.c#L61">61</a>         return <a href="ident?i=inet_diag_table">inet_diag_table</a>[<a href="ident?i=proto">proto</a>];
 <a name="L62" href="source/net/ipv4/inet_diag.c#L62">62</a> }
 <a name="L63" href="source/net/ipv4/inet_diag.c#L63">63</a> 
 <a name="L64" href="source/net/ipv4/inet_diag.c#L64">64</a> static void <a href="ident?i=inet_diag_unlock_handler">inet_diag_unlock_handler</a>(const struct <a href="ident?i=inet_diag_handler">inet_diag_handler</a> *<a href="ident?i=handler">handler</a>)
 <a name="L65" href="source/net/ipv4/inet_diag.c#L65">65</a> {
 <a name="L66" href="source/net/ipv4/inet_diag.c#L66">66</a>         <a href="ident?i=mutex_unlock">mutex_unlock</a>(&amp;inet_diag_table_mutex);
 <a name="L67" href="source/net/ipv4/inet_diag.c#L67">67</a> }
 <a name="L68" href="source/net/ipv4/inet_diag.c#L68">68</a> 
 <a name="L69" href="source/net/ipv4/inet_diag.c#L69">69</a> static void <a href="ident?i=inet_diag_msg_common_fill">inet_diag_msg_common_fill</a>(struct <a href="ident?i=inet_diag_msg">inet_diag_msg</a> *<a href="ident?i=r">r</a>, struct <a href="ident?i=sock">sock</a> *sk)
 <a name="L70" href="source/net/ipv4/inet_diag.c#L70">70</a> {
 <a name="L71" href="source/net/ipv4/inet_diag.c#L71">71</a>         <a href="ident?i=r">r</a>-&gt;idiag_family = sk-&gt;<a href="ident?i=sk_family">sk_family</a>;
 <a name="L72" href="source/net/ipv4/inet_diag.c#L72">72</a> 
 <a name="L73" href="source/net/ipv4/inet_diag.c#L73">73</a>         <a href="ident?i=r">r</a>-&gt;<a href="ident?i=id">id</a>.idiag_sport = <a href="ident?i=htons">htons</a>(sk-&gt;<a href="ident?i=sk_num">sk_num</a>);
 <a name="L74" href="source/net/ipv4/inet_diag.c#L74">74</a>         <a href="ident?i=r">r</a>-&gt;<a href="ident?i=id">id</a>.idiag_dport = sk-&gt;<a href="ident?i=sk_dport">sk_dport</a>;
 <a name="L75" href="source/net/ipv4/inet_diag.c#L75">75</a>         <a href="ident?i=r">r</a>-&gt;<a href="ident?i=id">id</a>.idiag_if = sk-&gt;<a href="ident?i=sk_bound_dev_if">sk_bound_dev_if</a>;
 <a name="L76" href="source/net/ipv4/inet_diag.c#L76">76</a>         <a href="ident?i=sock_diag_save_cookie">sock_diag_save_cookie</a>(sk, <a href="ident?i=r">r</a>-&gt;<a href="ident?i=id">id</a>.idiag_cookie);
 <a name="L77" href="source/net/ipv4/inet_diag.c#L77">77</a> 
 <a name="L78" href="source/net/ipv4/inet_diag.c#L78">78</a> #if <a href="ident?i=IS_ENABLED">IS_ENABLED</a>(CONFIG_IPV6)
 <a name="L79" href="source/net/ipv4/inet_diag.c#L79">79</a>         if (sk-&gt;<a href="ident?i=sk_family">sk_family</a> == <a href="ident?i=AF_INET6">AF_INET6</a>) {
 <a name="L80" href="source/net/ipv4/inet_diag.c#L80">80</a>                 *(struct <a href="ident?i=in6_addr">in6_addr</a> *)<a href="ident?i=r">r</a>-&gt;<a href="ident?i=id">id</a>.idiag_src = sk-&gt;<a href="ident?i=sk_v6_rcv_saddr">sk_v6_rcv_saddr</a>;
 <a name="L81" href="source/net/ipv4/inet_diag.c#L81">81</a>                 *(struct <a href="ident?i=in6_addr">in6_addr</a> *)<a href="ident?i=r">r</a>-&gt;<a href="ident?i=id">id</a>.idiag_dst = sk-&gt;<a href="ident?i=sk_v6_daddr">sk_v6_daddr</a>;
 <a name="L82" href="source/net/ipv4/inet_diag.c#L82">82</a>         } else
 <a name="L83" href="source/net/ipv4/inet_diag.c#L83">83</a> #endif
 <a name="L84" href="source/net/ipv4/inet_diag.c#L84">84</a>         {
 <a name="L85" href="source/net/ipv4/inet_diag.c#L85">85</a>         <a href="ident?i=memset">memset</a>(&amp;<a href="ident?i=r">r</a>-&gt;<a href="ident?i=id">id</a>.idiag_src, 0, sizeof(<a href="ident?i=r">r</a>-&gt;<a href="ident?i=id">id</a>.idiag_src));
 <a name="L86" href="source/net/ipv4/inet_diag.c#L86">86</a>         <a href="ident?i=memset">memset</a>(&amp;<a href="ident?i=r">r</a>-&gt;<a href="ident?i=id">id</a>.idiag_dst, 0, sizeof(<a href="ident?i=r">r</a>-&gt;<a href="ident?i=id">id</a>.idiag_dst));
 <a name="L87" href="source/net/ipv4/inet_diag.c#L87">87</a> 
 <a name="L88" href="source/net/ipv4/inet_diag.c#L88">88</a>         <a href="ident?i=r">r</a>-&gt;<a href="ident?i=id">id</a>.idiag_src[0] = sk-&gt;<a href="ident?i=sk_rcv_saddr">sk_rcv_saddr</a>;
 <a name="L89" href="source/net/ipv4/inet_diag.c#L89">89</a>         <a href="ident?i=r">r</a>-&gt;<a href="ident?i=id">id</a>.idiag_dst[0] = sk-&gt;<a href="ident?i=sk_daddr">sk_daddr</a>;
 <a name="L90" href="source/net/ipv4/inet_diag.c#L90">90</a>         }
 <a name="L91" href="source/net/ipv4/inet_diag.c#L91">91</a> }
 <a name="L92" href="source/net/ipv4/inet_diag.c#L92">92</a> 
 <a name="L93" href="source/net/ipv4/inet_diag.c#L93">93</a> static <a href="ident?i=size_t">size_t</a> <a href="ident?i=inet_sk_attr_size">inet_sk_attr_size</a>(void)
 <a name="L94" href="source/net/ipv4/inet_diag.c#L94">94</a> {
 <a name="L95" href="source/net/ipv4/inet_diag.c#L95">95</a>         return    <a href="ident?i=nla_total_size">nla_total_size</a>(sizeof(struct <a href="ident?i=tcp_info">tcp_info</a>))
 <a name="L96" href="source/net/ipv4/inet_diag.c#L96">96</a>                 + <a href="ident?i=nla_total_size">nla_total_size</a>(1) <b><i>/* INET_DIAG_SHUTDOWN */</i></b>
 <a name="L97" href="source/net/ipv4/inet_diag.c#L97">97</a>                 + <a href="ident?i=nla_total_size">nla_total_size</a>(1) <b><i>/* INET_DIAG_TOS */</i></b>
 <a name="L98" href="source/net/ipv4/inet_diag.c#L98">98</a>                 + <a href="ident?i=nla_total_size">nla_total_size</a>(1) <b><i>/* INET_DIAG_TCLASS */</i></b>
 <a name="L99" href="source/net/ipv4/inet_diag.c#L99">99</a>                 + <a href="ident?i=nla_total_size">nla_total_size</a>(sizeof(struct <a href="ident?i=inet_diag_meminfo">inet_diag_meminfo</a>))
<a name="L100" href="source/net/ipv4/inet_diag.c#L100">100</a>                 + <a href="ident?i=nla_total_size">nla_total_size</a>(sizeof(struct <a href="ident?i=inet_diag_msg">inet_diag_msg</a>))
<a name="L101" href="source/net/ipv4/inet_diag.c#L101">101</a>                 + <a href="ident?i=nla_total_size">nla_total_size</a>(SK_MEMINFO_VARS * sizeof(<a href="ident?i=u32">u32</a>))
<a name="L102" href="source/net/ipv4/inet_diag.c#L102">102</a>                 + <a href="ident?i=nla_total_size">nla_total_size</a>(<a href="ident?i=TCP_CA_NAME_MAX">TCP_CA_NAME_MAX</a>)
<a name="L103" href="source/net/ipv4/inet_diag.c#L103">103</a>                 + <a href="ident?i=nla_total_size">nla_total_size</a>(sizeof(struct <a href="ident?i=tcpvegas_info">tcpvegas_info</a>))
<a name="L104" href="source/net/ipv4/inet_diag.c#L104">104</a>                 + 64;
<a name="L105" href="source/net/ipv4/inet_diag.c#L105">105</a> }
<a name="L106" href="source/net/ipv4/inet_diag.c#L106">106</a> 
<a name="L107" href="source/net/ipv4/inet_diag.c#L107">107</a> int <a href="ident?i=inet_sk_diag_fill">inet_sk_diag_fill</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=inet_connection_sock">inet_connection_sock</a> *icsk,
<a name="L108" href="source/net/ipv4/inet_diag.c#L108">108</a>                       struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, const struct <a href="ident?i=inet_diag_req_v2">inet_diag_req_v2</a> *<a href="ident?i=req">req</a>,
<a name="L109" href="source/net/ipv4/inet_diag.c#L109">109</a>                       struct <a href="ident?i=user_namespace">user_namespace</a> *<a href="ident?i=user_ns">user_ns</a>,
<a name="L110" href="source/net/ipv4/inet_diag.c#L110">110</a>                       <a href="ident?i=u32">u32</a> portid, <a href="ident?i=u32">u32</a> <a href="ident?i=seq">seq</a>, <a href="ident?i=u16">u16</a> nlmsg_flags,
<a name="L111" href="source/net/ipv4/inet_diag.c#L111">111</a>                       const struct <a href="ident?i=nlmsghdr">nlmsghdr</a> *unlh)
<a name="L112" href="source/net/ipv4/inet_diag.c#L112">112</a> {
<a name="L113" href="source/net/ipv4/inet_diag.c#L113">113</a>         const struct <a href="ident?i=inet_sock">inet_sock</a> *inet = <a href="ident?i=inet_sk">inet_sk</a>(sk);
<a name="L114" href="source/net/ipv4/inet_diag.c#L114">114</a>         const struct <a href="ident?i=tcp_congestion_ops">tcp_congestion_ops</a> *ca_ops;
<a name="L115" href="source/net/ipv4/inet_diag.c#L115">115</a>         const struct <a href="ident?i=inet_diag_handler">inet_diag_handler</a> *<a href="ident?i=handler">handler</a>;
<a name="L116" href="source/net/ipv4/inet_diag.c#L116">116</a>         int ext = <a href="ident?i=req">req</a>-&gt;idiag_ext;
<a name="L117" href="source/net/ipv4/inet_diag.c#L117">117</a>         struct <a href="ident?i=inet_diag_msg">inet_diag_msg</a> *<a href="ident?i=r">r</a>;
<a name="L118" href="source/net/ipv4/inet_diag.c#L118">118</a>         struct <a href="ident?i=nlmsghdr">nlmsghdr</a>  *nlh;
<a name="L119" href="source/net/ipv4/inet_diag.c#L119">119</a>         struct <a href="ident?i=nlattr">nlattr</a> *<a href="ident?i=attr">attr</a>;
<a name="L120" href="source/net/ipv4/inet_diag.c#L120">120</a>         void *<a href="ident?i=info">info</a> = <a href="ident?i=NULL">NULL</a>;
<a name="L121" href="source/net/ipv4/inet_diag.c#L121">121</a> 
<a name="L122" href="source/net/ipv4/inet_diag.c#L122">122</a>         <a href="ident?i=handler">handler</a> = <a href="ident?i=inet_diag_table">inet_diag_table</a>[<a href="ident?i=req">req</a>-&gt;sdiag_protocol];
<a name="L123" href="source/net/ipv4/inet_diag.c#L123">123</a>         <a href="ident?i=BUG_ON">BUG_ON</a>(!<a href="ident?i=handler">handler</a>);
<a name="L124" href="source/net/ipv4/inet_diag.c#L124">124</a> 
<a name="L125" href="source/net/ipv4/inet_diag.c#L125">125</a>         nlh = <a href="ident?i=nlmsg_put">nlmsg_put</a>(<a href="ident?i=skb">skb</a>, portid, <a href="ident?i=seq">seq</a>, unlh-&gt;nlmsg_type, sizeof(*<a href="ident?i=r">r</a>),
<a name="L126" href="source/net/ipv4/inet_diag.c#L126">126</a>                         nlmsg_flags);
<a name="L127" href="source/net/ipv4/inet_diag.c#L127">127</a>         if (!nlh)
<a name="L128" href="source/net/ipv4/inet_diag.c#L128">128</a>                 return -<a href="ident?i=EMSGSIZE">EMSGSIZE</a>;
<a name="L129" href="source/net/ipv4/inet_diag.c#L129">129</a> 
<a name="L130" href="source/net/ipv4/inet_diag.c#L130">130</a>         <a href="ident?i=r">r</a> = <a href="ident?i=nlmsg_data">nlmsg_data</a>(nlh);
<a name="L131" href="source/net/ipv4/inet_diag.c#L131">131</a>         <a href="ident?i=BUG_ON">BUG_ON</a>(!<a href="ident?i=sk_fullsock">sk_fullsock</a>(sk));
<a name="L132" href="source/net/ipv4/inet_diag.c#L132">132</a> 
<a name="L133" href="source/net/ipv4/inet_diag.c#L133">133</a>         <a href="ident?i=inet_diag_msg_common_fill">inet_diag_msg_common_fill</a>(<a href="ident?i=r">r</a>, sk);
<a name="L134" href="source/net/ipv4/inet_diag.c#L134">134</a>         <a href="ident?i=r">r</a>-&gt;idiag_state = sk-&gt;<a href="ident?i=sk_state">sk_state</a>;
<a name="L135" href="source/net/ipv4/inet_diag.c#L135">135</a>         <a href="ident?i=r">r</a>-&gt;idiag_timer = 0;
<a name="L136" href="source/net/ipv4/inet_diag.c#L136">136</a>         <a href="ident?i=r">r</a>-&gt;idiag_retrans = 0;
<a name="L137" href="source/net/ipv4/inet_diag.c#L137">137</a> 
<a name="L138" href="source/net/ipv4/inet_diag.c#L138">138</a>         if (<a href="ident?i=nla_put_u8">nla_put_u8</a>(<a href="ident?i=skb">skb</a>, INET_DIAG_SHUTDOWN, sk-&gt;sk_shutdown))
<a name="L139" href="source/net/ipv4/inet_diag.c#L139">139</a>                 goto errout;
<a name="L140" href="source/net/ipv4/inet_diag.c#L140">140</a> 
<a name="L141" href="source/net/ipv4/inet_diag.c#L141">141</a>         <b><i>/* IPv6 dual-stack sockets use inet-&gt;tos for IPv4 connections,</i></b>
<a name="L142" href="source/net/ipv4/inet_diag.c#L142">142</a> <b><i>         * hence this needs to be included regardless of socket family.</i></b>
<a name="L143" href="source/net/ipv4/inet_diag.c#L143">143</a> <b><i>         */</i></b>
<a name="L144" href="source/net/ipv4/inet_diag.c#L144">144</a>         if (ext &amp; (1 &lt;&lt; (INET_DIAG_TOS - 1)))
<a name="L145" href="source/net/ipv4/inet_diag.c#L145">145</a>                 if (<a href="ident?i=nla_put_u8">nla_put_u8</a>(<a href="ident?i=skb">skb</a>, INET_DIAG_TOS, inet-&gt;tos) &lt; 0)
<a name="L146" href="source/net/ipv4/inet_diag.c#L146">146</a>                         goto errout;
<a name="L147" href="source/net/ipv4/inet_diag.c#L147">147</a> 
<a name="L148" href="source/net/ipv4/inet_diag.c#L148">148</a> #if <a href="ident?i=IS_ENABLED">IS_ENABLED</a>(CONFIG_IPV6)
<a name="L149" href="source/net/ipv4/inet_diag.c#L149">149</a>         if (<a href="ident?i=r">r</a>-&gt;idiag_family == <a href="ident?i=AF_INET6">AF_INET6</a>) {
<a name="L150" href="source/net/ipv4/inet_diag.c#L150">150</a>                 if (ext &amp; (1 &lt;&lt; (INET_DIAG_TCLASS - 1)))
<a name="L151" href="source/net/ipv4/inet_diag.c#L151">151</a>                         if (<a href="ident?i=nla_put_u8">nla_put_u8</a>(<a href="ident?i=skb">skb</a>, INET_DIAG_TCLASS,
<a name="L152" href="source/net/ipv4/inet_diag.c#L152">152</a>                                        <a href="ident?i=inet6_sk">inet6_sk</a>(sk)-&gt;tclass) &lt; 0)
<a name="L153" href="source/net/ipv4/inet_diag.c#L153">153</a>                                 goto errout;
<a name="L154" href="source/net/ipv4/inet_diag.c#L154">154</a>         }
<a name="L155" href="source/net/ipv4/inet_diag.c#L155">155</a> #endif
<a name="L156" href="source/net/ipv4/inet_diag.c#L156">156</a> 
<a name="L157" href="source/net/ipv4/inet_diag.c#L157">157</a>         <a href="ident?i=r">r</a>-&gt;idiag_uid = <a href="ident?i=from_kuid_munged">from_kuid_munged</a>(<a href="ident?i=user_ns">user_ns</a>, <a href="ident?i=sock_i_uid">sock_i_uid</a>(sk));
<a name="L158" href="source/net/ipv4/inet_diag.c#L158">158</a>         <a href="ident?i=r">r</a>-&gt;idiag_inode = <a href="ident?i=sock_i_ino">sock_i_ino</a>(sk);
<a name="L159" href="source/net/ipv4/inet_diag.c#L159">159</a> 
<a name="L160" href="source/net/ipv4/inet_diag.c#L160">160</a>         if (ext &amp; (1 &lt;&lt; (INET_DIAG_MEMINFO - 1))) {
<a name="L161" href="source/net/ipv4/inet_diag.c#L161">161</a>                 struct <a href="ident?i=inet_diag_meminfo">inet_diag_meminfo</a> <a href="ident?i=minfo">minfo</a> = {
<a name="L162" href="source/net/ipv4/inet_diag.c#L162">162</a>                         .idiag_rmem = <a href="ident?i=sk_rmem_alloc_get">sk_rmem_alloc_get</a>(sk),
<a name="L163" href="source/net/ipv4/inet_diag.c#L163">163</a>                         .idiag_wmem = sk-&gt;sk_wmem_queued,
<a name="L164" href="source/net/ipv4/inet_diag.c#L164">164</a>                         .idiag_fmem = sk-&gt;sk_forward_alloc,
<a name="L165" href="source/net/ipv4/inet_diag.c#L165">165</a>                         .idiag_tmem = <a href="ident?i=sk_wmem_alloc_get">sk_wmem_alloc_get</a>(sk),
<a name="L166" href="source/net/ipv4/inet_diag.c#L166">166</a>                 };
<a name="L167" href="source/net/ipv4/inet_diag.c#L167">167</a> 
<a name="L168" href="source/net/ipv4/inet_diag.c#L168">168</a>                 if (<a href="ident?i=nla_put">nla_put</a>(<a href="ident?i=skb">skb</a>, INET_DIAG_MEMINFO, sizeof(<a href="ident?i=minfo">minfo</a>), &amp;<a href="ident?i=minfo">minfo</a>) &lt; 0)
<a name="L169" href="source/net/ipv4/inet_diag.c#L169">169</a>                         goto errout;
<a name="L170" href="source/net/ipv4/inet_diag.c#L170">170</a>         }
<a name="L171" href="source/net/ipv4/inet_diag.c#L171">171</a> 
<a name="L172" href="source/net/ipv4/inet_diag.c#L172">172</a>         if (ext &amp; (1 &lt;&lt; (INET_DIAG_SKMEMINFO - 1)))
<a name="L173" href="source/net/ipv4/inet_diag.c#L173">173</a>                 if (<a href="ident?i=sock_diag_put_meminfo">sock_diag_put_meminfo</a>(sk, <a href="ident?i=skb">skb</a>, INET_DIAG_SKMEMINFO))
<a name="L174" href="source/net/ipv4/inet_diag.c#L174">174</a>                         goto errout;
<a name="L175" href="source/net/ipv4/inet_diag.c#L175">175</a> 
<a name="L176" href="source/net/ipv4/inet_diag.c#L176">176</a>         if (!icsk) {
<a name="L177" href="source/net/ipv4/inet_diag.c#L177">177</a>                 <a href="ident?i=handler">handler</a>-&gt;idiag_get_info(sk, <a href="ident?i=r">r</a>, <a href="ident?i=NULL">NULL</a>);
<a name="L178" href="source/net/ipv4/inet_diag.c#L178">178</a>                 goto <a href="ident?i=out">out</a>;
<a name="L179" href="source/net/ipv4/inet_diag.c#L179">179</a>         }
<a name="L180" href="source/net/ipv4/inet_diag.c#L180">180</a> 
<a name="L181" href="source/net/ipv4/inet_diag.c#L181">181</a> #define <a href="ident?i=EXPIRES_IN_MS">EXPIRES_IN_MS</a>(tmo)  <a href="ident?i=DIV_ROUND_UP">DIV_ROUND_UP</a>((tmo - <a href="ident?i=jiffies">jiffies</a>) * 1000, <a href="ident?i=HZ">HZ</a>)
<a name="L182" href="source/net/ipv4/inet_diag.c#L182">182</a> 
<a name="L183" href="source/net/ipv4/inet_diag.c#L183">183</a>         if (icsk-&gt;icsk_pending == <a href="ident?i=ICSK_TIME_RETRANS">ICSK_TIME_RETRANS</a> ||
<a name="L184" href="source/net/ipv4/inet_diag.c#L184">184</a>             icsk-&gt;icsk_pending == <a href="ident?i=ICSK_TIME_EARLY_RETRANS">ICSK_TIME_EARLY_RETRANS</a> ||
<a name="L185" href="source/net/ipv4/inet_diag.c#L185">185</a>             icsk-&gt;icsk_pending == <a href="ident?i=ICSK_TIME_LOSS_PROBE">ICSK_TIME_LOSS_PROBE</a>) {
<a name="L186" href="source/net/ipv4/inet_diag.c#L186">186</a>                 <a href="ident?i=r">r</a>-&gt;idiag_timer = 1;
<a name="L187" href="source/net/ipv4/inet_diag.c#L187">187</a>                 <a href="ident?i=r">r</a>-&gt;idiag_retrans = icsk-&gt;icsk_retransmits;
<a name="L188" href="source/net/ipv4/inet_diag.c#L188">188</a>                 <a href="ident?i=r">r</a>-&gt;idiag_expires = <a href="ident?i=EXPIRES_IN_MS">EXPIRES_IN_MS</a>(icsk-&gt;icsk_timeout);
<a name="L189" href="source/net/ipv4/inet_diag.c#L189">189</a>         } else if (icsk-&gt;icsk_pending == <a href="ident?i=ICSK_TIME_PROBE0">ICSK_TIME_PROBE0</a>) {
<a name="L190" href="source/net/ipv4/inet_diag.c#L190">190</a>                 <a href="ident?i=r">r</a>-&gt;idiag_timer = 4;
<a name="L191" href="source/net/ipv4/inet_diag.c#L191">191</a>                 <a href="ident?i=r">r</a>-&gt;idiag_retrans = icsk-&gt;icsk_probes_out;
<a name="L192" href="source/net/ipv4/inet_diag.c#L192">192</a>                 <a href="ident?i=r">r</a>-&gt;idiag_expires = <a href="ident?i=EXPIRES_IN_MS">EXPIRES_IN_MS</a>(icsk-&gt;icsk_timeout);
<a name="L193" href="source/net/ipv4/inet_diag.c#L193">193</a>         } else if (<a href="ident?i=timer_pending">timer_pending</a>(&amp;sk-&gt;sk_timer)) {
<a name="L194" href="source/net/ipv4/inet_diag.c#L194">194</a>                 <a href="ident?i=r">r</a>-&gt;idiag_timer = 2;
<a name="L195" href="source/net/ipv4/inet_diag.c#L195">195</a>                 <a href="ident?i=r">r</a>-&gt;idiag_retrans = icsk-&gt;icsk_probes_out;
<a name="L196" href="source/net/ipv4/inet_diag.c#L196">196</a>                 <a href="ident?i=r">r</a>-&gt;idiag_expires = <a href="ident?i=EXPIRES_IN_MS">EXPIRES_IN_MS</a>(sk-&gt;sk_timer.expires);
<a name="L197" href="source/net/ipv4/inet_diag.c#L197">197</a>         } else {
<a name="L198" href="source/net/ipv4/inet_diag.c#L198">198</a>                 <a href="ident?i=r">r</a>-&gt;idiag_timer = 0;
<a name="L199" href="source/net/ipv4/inet_diag.c#L199">199</a>                 <a href="ident?i=r">r</a>-&gt;idiag_expires = 0;
<a name="L200" href="source/net/ipv4/inet_diag.c#L200">200</a>         }
<a name="L201" href="source/net/ipv4/inet_diag.c#L201">201</a> #undef <a href="ident?i=EXPIRES_IN_MS">EXPIRES_IN_MS</a>
<a name="L202" href="source/net/ipv4/inet_diag.c#L202">202</a> 
<a name="L203" href="source/net/ipv4/inet_diag.c#L203">203</a>         if (ext &amp; (1 &lt;&lt; (INET_DIAG_INFO - 1))) {
<a name="L204" href="source/net/ipv4/inet_diag.c#L204">204</a>                 <a href="ident?i=attr">attr</a> = <a href="ident?i=nla_reserve">nla_reserve</a>(<a href="ident?i=skb">skb</a>, INET_DIAG_INFO,
<a name="L205" href="source/net/ipv4/inet_diag.c#L205">205</a>                                    sizeof(struct <a href="ident?i=tcp_info">tcp_info</a>));
<a name="L206" href="source/net/ipv4/inet_diag.c#L206">206</a>                 if (!<a href="ident?i=attr">attr</a>)
<a name="L207" href="source/net/ipv4/inet_diag.c#L207">207</a>                         goto errout;
<a name="L208" href="source/net/ipv4/inet_diag.c#L208">208</a> 
<a name="L209" href="source/net/ipv4/inet_diag.c#L209">209</a>                 <a href="ident?i=info">info</a> = <a href="ident?i=nla_data">nla_data</a>(<a href="ident?i=attr">attr</a>);
<a name="L210" href="source/net/ipv4/inet_diag.c#L210">210</a>         }
<a name="L211" href="source/net/ipv4/inet_diag.c#L211">211</a> 
<a name="L212" href="source/net/ipv4/inet_diag.c#L212">212</a>         if (ext &amp; (1 &lt;&lt; (INET_DIAG_CONG - 1))) {
<a name="L213" href="source/net/ipv4/inet_diag.c#L213">213</a>                 int <a href="ident?i=err">err</a> = 0;
<a name="L214" href="source/net/ipv4/inet_diag.c#L214">214</a> 
<a name="L215" href="source/net/ipv4/inet_diag.c#L215">215</a>                 <a href="ident?i=rcu_read_lock">rcu_read_lock</a>();
<a name="L216" href="source/net/ipv4/inet_diag.c#L216">216</a>                 ca_ops = <a href="ident?i=READ_ONCE">READ_ONCE</a>(icsk-&gt;icsk_ca_ops);
<a name="L217" href="source/net/ipv4/inet_diag.c#L217">217</a>                 if (ca_ops)
<a name="L218" href="source/net/ipv4/inet_diag.c#L218">218</a>                         <a href="ident?i=err">err</a> = <a href="ident?i=nla_put_string">nla_put_string</a>(<a href="ident?i=skb">skb</a>, INET_DIAG_CONG, ca_ops-&gt;<a href="ident?i=name">name</a>);
<a name="L219" href="source/net/ipv4/inet_diag.c#L219">219</a>                 <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L220" href="source/net/ipv4/inet_diag.c#L220">220</a>                 if (<a href="ident?i=err">err</a> &lt; 0)
<a name="L221" href="source/net/ipv4/inet_diag.c#L221">221</a>                         goto errout;
<a name="L222" href="source/net/ipv4/inet_diag.c#L222">222</a>         }
<a name="L223" href="source/net/ipv4/inet_diag.c#L223">223</a> 
<a name="L224" href="source/net/ipv4/inet_diag.c#L224">224</a>         <a href="ident?i=handler">handler</a>-&gt;idiag_get_info(sk, <a href="ident?i=r">r</a>, <a href="ident?i=info">info</a>);
<a name="L225" href="source/net/ipv4/inet_diag.c#L225">225</a> 
<a name="L226" href="source/net/ipv4/inet_diag.c#L226">226</a>         if (sk-&gt;<a href="ident?i=sk_state">sk_state</a> &lt; TCP_TIME_WAIT) {
<a name="L227" href="source/net/ipv4/inet_diag.c#L227">227</a>                 union <a href="ident?i=tcp_cc_info">tcp_cc_info</a> <a href="ident?i=info">info</a>;
<a name="L228" href="source/net/ipv4/inet_diag.c#L228">228</a>                 <a href="ident?i=size_t">size_t</a> sz = 0;
<a name="L229" href="source/net/ipv4/inet_diag.c#L229">229</a>                 int <a href="ident?i=attr">attr</a>;
<a name="L230" href="source/net/ipv4/inet_diag.c#L230">230</a> 
<a name="L231" href="source/net/ipv4/inet_diag.c#L231">231</a>                 <a href="ident?i=rcu_read_lock">rcu_read_lock</a>();
<a name="L232" href="source/net/ipv4/inet_diag.c#L232">232</a>                 ca_ops = <a href="ident?i=READ_ONCE">READ_ONCE</a>(icsk-&gt;icsk_ca_ops);
<a name="L233" href="source/net/ipv4/inet_diag.c#L233">233</a>                 if (ca_ops &amp;&amp; ca_ops-&gt;<a href="ident?i=get_info">get_info</a>)
<a name="L234" href="source/net/ipv4/inet_diag.c#L234">234</a>                         sz = ca_ops-&gt;<a href="ident?i=get_info">get_info</a>(sk, ext, &amp;<a href="ident?i=attr">attr</a>, &amp;<a href="ident?i=info">info</a>);
<a name="L235" href="source/net/ipv4/inet_diag.c#L235">235</a>                 <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L236" href="source/net/ipv4/inet_diag.c#L236">236</a>                 if (sz &amp;&amp; <a href="ident?i=nla_put">nla_put</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=attr">attr</a>, sz, &amp;<a href="ident?i=info">info</a>) &lt; 0)
<a name="L237" href="source/net/ipv4/inet_diag.c#L237">237</a>                         goto errout;
<a name="L238" href="source/net/ipv4/inet_diag.c#L238">238</a>         }
<a name="L239" href="source/net/ipv4/inet_diag.c#L239">239</a> 
<a name="L240" href="source/net/ipv4/inet_diag.c#L240">240</a> <a href="ident?i=out">out</a>:
<a name="L241" href="source/net/ipv4/inet_diag.c#L241">241</a>         <a href="ident?i=nlmsg_end">nlmsg_end</a>(<a href="ident?i=skb">skb</a>, nlh);
<a name="L242" href="source/net/ipv4/inet_diag.c#L242">242</a>         return 0;
<a name="L243" href="source/net/ipv4/inet_diag.c#L243">243</a> 
<a name="L244" href="source/net/ipv4/inet_diag.c#L244">244</a> errout:
<a name="L245" href="source/net/ipv4/inet_diag.c#L245">245</a>         <a href="ident?i=nlmsg_cancel">nlmsg_cancel</a>(<a href="ident?i=skb">skb</a>, nlh);
<a name="L246" href="source/net/ipv4/inet_diag.c#L246">246</a>         return -<a href="ident?i=EMSGSIZE">EMSGSIZE</a>;
<a name="L247" href="source/net/ipv4/inet_diag.c#L247">247</a> }
<a name="L248" href="source/net/ipv4/inet_diag.c#L248">248</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=inet_sk_diag_fill">inet_sk_diag_fill</a>);
<a name="L249" href="source/net/ipv4/inet_diag.c#L249">249</a> 
<a name="L250" href="source/net/ipv4/inet_diag.c#L250">250</a> static int <a href="ident?i=inet_csk_diag_fill">inet_csk_diag_fill</a>(struct <a href="ident?i=sock">sock</a> *sk,
<a name="L251" href="source/net/ipv4/inet_diag.c#L251">251</a>                               struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
<a name="L252" href="source/net/ipv4/inet_diag.c#L252">252</a>                               const struct <a href="ident?i=inet_diag_req_v2">inet_diag_req_v2</a> *<a href="ident?i=req">req</a>,
<a name="L253" href="source/net/ipv4/inet_diag.c#L253">253</a>                               struct <a href="ident?i=user_namespace">user_namespace</a> *<a href="ident?i=user_ns">user_ns</a>,
<a name="L254" href="source/net/ipv4/inet_diag.c#L254">254</a>                               <a href="ident?i=u32">u32</a> portid, <a href="ident?i=u32">u32</a> <a href="ident?i=seq">seq</a>, <a href="ident?i=u16">u16</a> nlmsg_flags,
<a name="L255" href="source/net/ipv4/inet_diag.c#L255">255</a>                               const struct <a href="ident?i=nlmsghdr">nlmsghdr</a> *unlh)
<a name="L256" href="source/net/ipv4/inet_diag.c#L256">256</a> {
<a name="L257" href="source/net/ipv4/inet_diag.c#L257">257</a>         return <a href="ident?i=inet_sk_diag_fill">inet_sk_diag_fill</a>(sk, <a href="ident?i=inet_csk">inet_csk</a>(sk), <a href="ident?i=skb">skb</a>, <a href="ident?i=req">req</a>,
<a name="L258" href="source/net/ipv4/inet_diag.c#L258">258</a>                                  <a href="ident?i=user_ns">user_ns</a>, portid, <a href="ident?i=seq">seq</a>, nlmsg_flags, unlh);
<a name="L259" href="source/net/ipv4/inet_diag.c#L259">259</a> }
<a name="L260" href="source/net/ipv4/inet_diag.c#L260">260</a> 
<a name="L261" href="source/net/ipv4/inet_diag.c#L261">261</a> static int <a href="ident?i=inet_twsk_diag_fill">inet_twsk_diag_fill</a>(struct <a href="ident?i=sock">sock</a> *sk,
<a name="L262" href="source/net/ipv4/inet_diag.c#L262">262</a>                                struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
<a name="L263" href="source/net/ipv4/inet_diag.c#L263">263</a>                                <a href="ident?i=u32">u32</a> portid, <a href="ident?i=u32">u32</a> <a href="ident?i=seq">seq</a>, <a href="ident?i=u16">u16</a> nlmsg_flags,
<a name="L264" href="source/net/ipv4/inet_diag.c#L264">264</a>                                const struct <a href="ident?i=nlmsghdr">nlmsghdr</a> *unlh)
<a name="L265" href="source/net/ipv4/inet_diag.c#L265">265</a> {
<a name="L266" href="source/net/ipv4/inet_diag.c#L266">266</a>         struct <a href="ident?i=inet_timewait_sock">inet_timewait_sock</a> *<a href="ident?i=tw">tw</a> = <a href="ident?i=inet_twsk">inet_twsk</a>(sk);
<a name="L267" href="source/net/ipv4/inet_diag.c#L267">267</a>         struct <a href="ident?i=inet_diag_msg">inet_diag_msg</a> *<a href="ident?i=r">r</a>;
<a name="L268" href="source/net/ipv4/inet_diag.c#L268">268</a>         struct <a href="ident?i=nlmsghdr">nlmsghdr</a> *nlh;
<a name="L269" href="source/net/ipv4/inet_diag.c#L269">269</a>         long tmo;
<a name="L270" href="source/net/ipv4/inet_diag.c#L270">270</a> 
<a name="L271" href="source/net/ipv4/inet_diag.c#L271">271</a>         nlh = <a href="ident?i=nlmsg_put">nlmsg_put</a>(<a href="ident?i=skb">skb</a>, portid, <a href="ident?i=seq">seq</a>, unlh-&gt;nlmsg_type, sizeof(*<a href="ident?i=r">r</a>),
<a name="L272" href="source/net/ipv4/inet_diag.c#L272">272</a>                         nlmsg_flags);
<a name="L273" href="source/net/ipv4/inet_diag.c#L273">273</a>         if (!nlh)
<a name="L274" href="source/net/ipv4/inet_diag.c#L274">274</a>                 return -<a href="ident?i=EMSGSIZE">EMSGSIZE</a>;
<a name="L275" href="source/net/ipv4/inet_diag.c#L275">275</a> 
<a name="L276" href="source/net/ipv4/inet_diag.c#L276">276</a>         <a href="ident?i=r">r</a> = <a href="ident?i=nlmsg_data">nlmsg_data</a>(nlh);
<a name="L277" href="source/net/ipv4/inet_diag.c#L277">277</a>         <a href="ident?i=BUG_ON">BUG_ON</a>(<a href="ident?i=tw">tw</a>-&gt;<a href="ident?i=tw_state">tw_state</a> != TCP_TIME_WAIT);
<a name="L278" href="source/net/ipv4/inet_diag.c#L278">278</a> 
<a name="L279" href="source/net/ipv4/inet_diag.c#L279">279</a>         tmo = <a href="ident?i=tw">tw</a>-&gt;tw_timer.expires - <a href="ident?i=jiffies">jiffies</a>;
<a name="L280" href="source/net/ipv4/inet_diag.c#L280">280</a>         if (tmo &lt; 0)
<a name="L281" href="source/net/ipv4/inet_diag.c#L281">281</a>                 tmo = 0;
<a name="L282" href="source/net/ipv4/inet_diag.c#L282">282</a> 
<a name="L283" href="source/net/ipv4/inet_diag.c#L283">283</a>         <a href="ident?i=inet_diag_msg_common_fill">inet_diag_msg_common_fill</a>(<a href="ident?i=r">r</a>, sk);
<a name="L284" href="source/net/ipv4/inet_diag.c#L284">284</a>         <a href="ident?i=r">r</a>-&gt;idiag_retrans      = 0;
<a name="L285" href="source/net/ipv4/inet_diag.c#L285">285</a> 
<a name="L286" href="source/net/ipv4/inet_diag.c#L286">286</a>         <a href="ident?i=r">r</a>-&gt;idiag_state        = <a href="ident?i=tw">tw</a>-&gt;tw_substate;
<a name="L287" href="source/net/ipv4/inet_diag.c#L287">287</a>         <a href="ident?i=r">r</a>-&gt;idiag_timer        = 3;
<a name="L288" href="source/net/ipv4/inet_diag.c#L288">288</a>         <a href="ident?i=r">r</a>-&gt;idiag_expires      = <a href="ident?i=jiffies_to_msecs">jiffies_to_msecs</a>(tmo);
<a name="L289" href="source/net/ipv4/inet_diag.c#L289">289</a>         <a href="ident?i=r">r</a>-&gt;idiag_rqueue       = 0;
<a name="L290" href="source/net/ipv4/inet_diag.c#L290">290</a>         <a href="ident?i=r">r</a>-&gt;idiag_wqueue       = 0;
<a name="L291" href="source/net/ipv4/inet_diag.c#L291">291</a>         <a href="ident?i=r">r</a>-&gt;idiag_uid          = 0;
<a name="L292" href="source/net/ipv4/inet_diag.c#L292">292</a>         <a href="ident?i=r">r</a>-&gt;idiag_inode        = 0;
<a name="L293" href="source/net/ipv4/inet_diag.c#L293">293</a> 
<a name="L294" href="source/net/ipv4/inet_diag.c#L294">294</a>         <a href="ident?i=nlmsg_end">nlmsg_end</a>(<a href="ident?i=skb">skb</a>, nlh);
<a name="L295" href="source/net/ipv4/inet_diag.c#L295">295</a>         return 0;
<a name="L296" href="source/net/ipv4/inet_diag.c#L296">296</a> }
<a name="L297" href="source/net/ipv4/inet_diag.c#L297">297</a> 
<a name="L298" href="source/net/ipv4/inet_diag.c#L298">298</a> static int <a href="ident?i=inet_req_diag_fill">inet_req_diag_fill</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
<a name="L299" href="source/net/ipv4/inet_diag.c#L299">299</a>                               <a href="ident?i=u32">u32</a> portid, <a href="ident?i=u32">u32</a> <a href="ident?i=seq">seq</a>, <a href="ident?i=u16">u16</a> nlmsg_flags,
<a name="L300" href="source/net/ipv4/inet_diag.c#L300">300</a>                               const struct <a href="ident?i=nlmsghdr">nlmsghdr</a> *unlh)
<a name="L301" href="source/net/ipv4/inet_diag.c#L301">301</a> {
<a name="L302" href="source/net/ipv4/inet_diag.c#L302">302</a>         struct <a href="ident?i=inet_diag_msg">inet_diag_msg</a> *<a href="ident?i=r">r</a>;
<a name="L303" href="source/net/ipv4/inet_diag.c#L303">303</a>         struct <a href="ident?i=nlmsghdr">nlmsghdr</a> *nlh;
<a name="L304" href="source/net/ipv4/inet_diag.c#L304">304</a>         long tmo;
<a name="L305" href="source/net/ipv4/inet_diag.c#L305">305</a> 
<a name="L306" href="source/net/ipv4/inet_diag.c#L306">306</a>         nlh = <a href="ident?i=nlmsg_put">nlmsg_put</a>(<a href="ident?i=skb">skb</a>, portid, <a href="ident?i=seq">seq</a>, unlh-&gt;nlmsg_type, sizeof(*<a href="ident?i=r">r</a>),
<a name="L307" href="source/net/ipv4/inet_diag.c#L307">307</a>                         nlmsg_flags);
<a name="L308" href="source/net/ipv4/inet_diag.c#L308">308</a>         if (!nlh)
<a name="L309" href="source/net/ipv4/inet_diag.c#L309">309</a>                 return -<a href="ident?i=EMSGSIZE">EMSGSIZE</a>;
<a name="L310" href="source/net/ipv4/inet_diag.c#L310">310</a> 
<a name="L311" href="source/net/ipv4/inet_diag.c#L311">311</a>         <a href="ident?i=r">r</a> = <a href="ident?i=nlmsg_data">nlmsg_data</a>(nlh);
<a name="L312" href="source/net/ipv4/inet_diag.c#L312">312</a>         <a href="ident?i=inet_diag_msg_common_fill">inet_diag_msg_common_fill</a>(<a href="ident?i=r">r</a>, sk);
<a name="L313" href="source/net/ipv4/inet_diag.c#L313">313</a>         <a href="ident?i=r">r</a>-&gt;idiag_state = TCP_SYN_RECV;
<a name="L314" href="source/net/ipv4/inet_diag.c#L314">314</a>         <a href="ident?i=r">r</a>-&gt;idiag_timer = 1;
<a name="L315" href="source/net/ipv4/inet_diag.c#L315">315</a>         <a href="ident?i=r">r</a>-&gt;idiag_retrans = <a href="ident?i=inet_reqsk">inet_reqsk</a>(sk)-&gt;num_retrans;
<a name="L316" href="source/net/ipv4/inet_diag.c#L316">316</a> 
<a name="L317" href="source/net/ipv4/inet_diag.c#L317">317</a>         <a href="ident?i=BUILD_BUG_ON">BUILD_BUG_ON</a>(<a href="ident?i=offsetof">offsetof</a>(struct <a href="ident?i=inet_request_sock">inet_request_sock</a>, <a href="ident?i=ir_cookie">ir_cookie</a>) !=
<a name="L318" href="source/net/ipv4/inet_diag.c#L318">318</a>                      <a href="ident?i=offsetof">offsetof</a>(struct <a href="ident?i=sock">sock</a>, <a href="ident?i=sk_cookie">sk_cookie</a>));
<a name="L319" href="source/net/ipv4/inet_diag.c#L319">319</a> 
<a name="L320" href="source/net/ipv4/inet_diag.c#L320">320</a>         tmo = <a href="ident?i=inet_reqsk">inet_reqsk</a>(sk)-&gt;rsk_timer.expires - <a href="ident?i=jiffies">jiffies</a>;
<a name="L321" href="source/net/ipv4/inet_diag.c#L321">321</a>         <a href="ident?i=r">r</a>-&gt;idiag_expires = (tmo &gt;= 0) ? <a href="ident?i=jiffies_to_msecs">jiffies_to_msecs</a>(tmo) : 0;
<a name="L322" href="source/net/ipv4/inet_diag.c#L322">322</a>         <a href="ident?i=r">r</a>-&gt;idiag_rqueue = 0;
<a name="L323" href="source/net/ipv4/inet_diag.c#L323">323</a>         <a href="ident?i=r">r</a>-&gt;idiag_wqueue = 0;
<a name="L324" href="source/net/ipv4/inet_diag.c#L324">324</a>         <a href="ident?i=r">r</a>-&gt;idiag_uid    = 0;
<a name="L325" href="source/net/ipv4/inet_diag.c#L325">325</a>         <a href="ident?i=r">r</a>-&gt;idiag_inode  = 0;
<a name="L326" href="source/net/ipv4/inet_diag.c#L326">326</a> 
<a name="L327" href="source/net/ipv4/inet_diag.c#L327">327</a>         <a href="ident?i=nlmsg_end">nlmsg_end</a>(<a href="ident?i=skb">skb</a>, nlh);
<a name="L328" href="source/net/ipv4/inet_diag.c#L328">328</a>         return 0;
<a name="L329" href="source/net/ipv4/inet_diag.c#L329">329</a> }
<a name="L330" href="source/net/ipv4/inet_diag.c#L330">330</a> 
<a name="L331" href="source/net/ipv4/inet_diag.c#L331">331</a> static int <a href="ident?i=sk_diag_fill">sk_diag_fill</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
<a name="L332" href="source/net/ipv4/inet_diag.c#L332">332</a>                         const struct <a href="ident?i=inet_diag_req_v2">inet_diag_req_v2</a> *<a href="ident?i=r">r</a>,
<a name="L333" href="source/net/ipv4/inet_diag.c#L333">333</a>                         struct <a href="ident?i=user_namespace">user_namespace</a> *<a href="ident?i=user_ns">user_ns</a>,
<a name="L334" href="source/net/ipv4/inet_diag.c#L334">334</a>                         <a href="ident?i=u32">u32</a> portid, <a href="ident?i=u32">u32</a> <a href="ident?i=seq">seq</a>, <a href="ident?i=u16">u16</a> nlmsg_flags,
<a name="L335" href="source/net/ipv4/inet_diag.c#L335">335</a>                         const struct <a href="ident?i=nlmsghdr">nlmsghdr</a> *unlh)
<a name="L336" href="source/net/ipv4/inet_diag.c#L336">336</a> {
<a name="L337" href="source/net/ipv4/inet_diag.c#L337">337</a>         if (sk-&gt;<a href="ident?i=sk_state">sk_state</a> == TCP_TIME_WAIT)
<a name="L338" href="source/net/ipv4/inet_diag.c#L338">338</a>                 return <a href="ident?i=inet_twsk_diag_fill">inet_twsk_diag_fill</a>(sk, <a href="ident?i=skb">skb</a>, portid, <a href="ident?i=seq">seq</a>,
<a name="L339" href="source/net/ipv4/inet_diag.c#L339">339</a>                                            nlmsg_flags, unlh);
<a name="L340" href="source/net/ipv4/inet_diag.c#L340">340</a> 
<a name="L341" href="source/net/ipv4/inet_diag.c#L341">341</a>         if (sk-&gt;<a href="ident?i=sk_state">sk_state</a> == TCP_NEW_SYN_RECV)
<a name="L342" href="source/net/ipv4/inet_diag.c#L342">342</a>                 return <a href="ident?i=inet_req_diag_fill">inet_req_diag_fill</a>(sk, <a href="ident?i=skb">skb</a>, portid, <a href="ident?i=seq">seq</a>,
<a name="L343" href="source/net/ipv4/inet_diag.c#L343">343</a>                                           nlmsg_flags, unlh);
<a name="L344" href="source/net/ipv4/inet_diag.c#L344">344</a> 
<a name="L345" href="source/net/ipv4/inet_diag.c#L345">345</a>         return <a href="ident?i=inet_csk_diag_fill">inet_csk_diag_fill</a>(sk, <a href="ident?i=skb">skb</a>, <a href="ident?i=r">r</a>, <a href="ident?i=user_ns">user_ns</a>, portid, <a href="ident?i=seq">seq</a>,
<a name="L346" href="source/net/ipv4/inet_diag.c#L346">346</a>                                   nlmsg_flags, unlh);
<a name="L347" href="source/net/ipv4/inet_diag.c#L347">347</a> }
<a name="L348" href="source/net/ipv4/inet_diag.c#L348">348</a> 
<a name="L349" href="source/net/ipv4/inet_diag.c#L349">349</a> int <a href="ident?i=inet_diag_dump_one_icsk">inet_diag_dump_one_icsk</a>(struct <a href="ident?i=inet_hashinfo">inet_hashinfo</a> *hashinfo,
<a name="L350" href="source/net/ipv4/inet_diag.c#L350">350</a>                             struct <a href="ident?i=sk_buff">sk_buff</a> *in_skb,
<a name="L351" href="source/net/ipv4/inet_diag.c#L351">351</a>                             const struct <a href="ident?i=nlmsghdr">nlmsghdr</a> *nlh,
<a name="L352" href="source/net/ipv4/inet_diag.c#L352">352</a>                             const struct <a href="ident?i=inet_diag_req_v2">inet_diag_req_v2</a> *<a href="ident?i=req">req</a>)
<a name="L353" href="source/net/ipv4/inet_diag.c#L353">353</a> {
<a name="L354" href="source/net/ipv4/inet_diag.c#L354">354</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=sock_net">sock_net</a>(in_skb-&gt;sk);
<a name="L355" href="source/net/ipv4/inet_diag.c#L355">355</a>         struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=rep">rep</a>;
<a name="L356" href="source/net/ipv4/inet_diag.c#L356">356</a>         struct <a href="ident?i=sock">sock</a> *sk;
<a name="L357" href="source/net/ipv4/inet_diag.c#L357">357</a>         int <a href="ident?i=err">err</a>;
<a name="L358" href="source/net/ipv4/inet_diag.c#L358">358</a> 
<a name="L359" href="source/net/ipv4/inet_diag.c#L359">359</a>         <a href="ident?i=err">err</a> = -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L360" href="source/net/ipv4/inet_diag.c#L360">360</a>         if (<a href="ident?i=req">req</a>-&gt;sdiag_family == <a href="ident?i=AF_INET">AF_INET</a>)
<a name="L361" href="source/net/ipv4/inet_diag.c#L361">361</a>                 sk = <a href="ident?i=inet_lookup">inet_lookup</a>(<a href="ident?i=net">net</a>, hashinfo, <a href="ident?i=req">req</a>-&gt;<a href="ident?i=id">id</a>.idiag_dst[0],
<a name="L362" href="source/net/ipv4/inet_diag.c#L362">362</a>                                  <a href="ident?i=req">req</a>-&gt;<a href="ident?i=id">id</a>.idiag_dport, <a href="ident?i=req">req</a>-&gt;<a href="ident?i=id">id</a>.idiag_src[0],
<a name="L363" href="source/net/ipv4/inet_diag.c#L363">363</a>                                  <a href="ident?i=req">req</a>-&gt;<a href="ident?i=id">id</a>.idiag_sport, <a href="ident?i=req">req</a>-&gt;<a href="ident?i=id">id</a>.idiag_if);
<a name="L364" href="source/net/ipv4/inet_diag.c#L364">364</a> #if <a href="ident?i=IS_ENABLED">IS_ENABLED</a>(CONFIG_IPV6)
<a name="L365" href="source/net/ipv4/inet_diag.c#L365">365</a>         else if (<a href="ident?i=req">req</a>-&gt;sdiag_family == <a href="ident?i=AF_INET6">AF_INET6</a>)
<a name="L366" href="source/net/ipv4/inet_diag.c#L366">366</a>                 sk = <a href="ident?i=inet6_lookup">inet6_lookup</a>(<a href="ident?i=net">net</a>, hashinfo,
<a name="L367" href="source/net/ipv4/inet_diag.c#L367">367</a>                                   (struct <a href="ident?i=in6_addr">in6_addr</a> *)<a href="ident?i=req">req</a>-&gt;<a href="ident?i=id">id</a>.idiag_dst,
<a name="L368" href="source/net/ipv4/inet_diag.c#L368">368</a>                                   <a href="ident?i=req">req</a>-&gt;<a href="ident?i=id">id</a>.idiag_dport,
<a name="L369" href="source/net/ipv4/inet_diag.c#L369">369</a>                                   (struct <a href="ident?i=in6_addr">in6_addr</a> *)<a href="ident?i=req">req</a>-&gt;<a href="ident?i=id">id</a>.idiag_src,
<a name="L370" href="source/net/ipv4/inet_diag.c#L370">370</a>                                   <a href="ident?i=req">req</a>-&gt;<a href="ident?i=id">id</a>.idiag_sport,
<a name="L371" href="source/net/ipv4/inet_diag.c#L371">371</a>                                   <a href="ident?i=req">req</a>-&gt;<a href="ident?i=id">id</a>.idiag_if);
<a name="L372" href="source/net/ipv4/inet_diag.c#L372">372</a> #endif
<a name="L373" href="source/net/ipv4/inet_diag.c#L373">373</a>         else
<a name="L374" href="source/net/ipv4/inet_diag.c#L374">374</a>                 goto out_nosk;
<a name="L375" href="source/net/ipv4/inet_diag.c#L375">375</a> 
<a name="L376" href="source/net/ipv4/inet_diag.c#L376">376</a>         <a href="ident?i=err">err</a> = -<a href="ident?i=ENOENT">ENOENT</a>;
<a name="L377" href="source/net/ipv4/inet_diag.c#L377">377</a>         if (!sk)
<a name="L378" href="source/net/ipv4/inet_diag.c#L378">378</a>                 goto out_nosk;
<a name="L379" href="source/net/ipv4/inet_diag.c#L379">379</a> 
<a name="L380" href="source/net/ipv4/inet_diag.c#L380">380</a>         <a href="ident?i=err">err</a> = <a href="ident?i=sock_diag_check_cookie">sock_diag_check_cookie</a>(sk, <a href="ident?i=req">req</a>-&gt;<a href="ident?i=id">id</a>.idiag_cookie);
<a name="L381" href="source/net/ipv4/inet_diag.c#L381">381</a>         if (<a href="ident?i=err">err</a>)
<a name="L382" href="source/net/ipv4/inet_diag.c#L382">382</a>                 goto <a href="ident?i=out">out</a>;
<a name="L383" href="source/net/ipv4/inet_diag.c#L383">383</a> 
<a name="L384" href="source/net/ipv4/inet_diag.c#L384">384</a>         <a href="ident?i=rep">rep</a> = <a href="ident?i=nlmsg_new">nlmsg_new</a>(<a href="ident?i=inet_sk_attr_size">inet_sk_attr_size</a>(), <a href="ident?i=GFP_KERNEL">GFP_KERNEL</a>);
<a name="L385" href="source/net/ipv4/inet_diag.c#L385">385</a>         if (!<a href="ident?i=rep">rep</a>) {
<a name="L386" href="source/net/ipv4/inet_diag.c#L386">386</a>                 <a href="ident?i=err">err</a> = -<a href="ident?i=ENOMEM">ENOMEM</a>;
<a name="L387" href="source/net/ipv4/inet_diag.c#L387">387</a>                 goto <a href="ident?i=out">out</a>;
<a name="L388" href="source/net/ipv4/inet_diag.c#L388">388</a>         }
<a name="L389" href="source/net/ipv4/inet_diag.c#L389">389</a> 
<a name="L390" href="source/net/ipv4/inet_diag.c#L390">390</a>         <a href="ident?i=err">err</a> = <a href="ident?i=sk_diag_fill">sk_diag_fill</a>(sk, <a href="ident?i=rep">rep</a>, <a href="ident?i=req">req</a>,
<a name="L391" href="source/net/ipv4/inet_diag.c#L391">391</a>                            <a href="ident?i=sk_user_ns">sk_user_ns</a>(<a href="ident?i=NETLINK_CB">NETLINK_CB</a>(in_skb).sk),
<a name="L392" href="source/net/ipv4/inet_diag.c#L392">392</a>                            <a href="ident?i=NETLINK_CB">NETLINK_CB</a>(in_skb).portid,
<a name="L393" href="source/net/ipv4/inet_diag.c#L393">393</a>                            nlh-&gt;nlmsg_seq, 0, nlh);
<a name="L394" href="source/net/ipv4/inet_diag.c#L394">394</a>         if (<a href="ident?i=err">err</a> &lt; 0) {
<a name="L395" href="source/net/ipv4/inet_diag.c#L395">395</a>                 <a href="ident?i=WARN_ON">WARN_ON</a>(<a href="ident?i=err">err</a> == -<a href="ident?i=EMSGSIZE">EMSGSIZE</a>);
<a name="L396" href="source/net/ipv4/inet_diag.c#L396">396</a>                 <a href="ident?i=nlmsg_free">nlmsg_free</a>(<a href="ident?i=rep">rep</a>);
<a name="L397" href="source/net/ipv4/inet_diag.c#L397">397</a>                 goto <a href="ident?i=out">out</a>;
<a name="L398" href="source/net/ipv4/inet_diag.c#L398">398</a>         }
<a name="L399" href="source/net/ipv4/inet_diag.c#L399">399</a>         <a href="ident?i=err">err</a> = <a href="ident?i=netlink_unicast">netlink_unicast</a>(<a href="ident?i=net">net</a>-&gt;diag_nlsk, <a href="ident?i=rep">rep</a>, <a href="ident?i=NETLINK_CB">NETLINK_CB</a>(in_skb).portid,
<a name="L400" href="source/net/ipv4/inet_diag.c#L400">400</a>                               <a href="ident?i=MSG_DONTWAIT">MSG_DONTWAIT</a>);
<a name="L401" href="source/net/ipv4/inet_diag.c#L401">401</a>         if (<a href="ident?i=err">err</a> &gt; 0)
<a name="L402" href="source/net/ipv4/inet_diag.c#L402">402</a>                 <a href="ident?i=err">err</a> = 0;
<a name="L403" href="source/net/ipv4/inet_diag.c#L403">403</a> 
<a name="L404" href="source/net/ipv4/inet_diag.c#L404">404</a> <a href="ident?i=out">out</a>:
<a name="L405" href="source/net/ipv4/inet_diag.c#L405">405</a>         if (sk)
<a name="L406" href="source/net/ipv4/inet_diag.c#L406">406</a>                 <a href="ident?i=sock_gen_put">sock_gen_put</a>(sk);
<a name="L407" href="source/net/ipv4/inet_diag.c#L407">407</a> 
<a name="L408" href="source/net/ipv4/inet_diag.c#L408">408</a> out_nosk:
<a name="L409" href="source/net/ipv4/inet_diag.c#L409">409</a>         return <a href="ident?i=err">err</a>;
<a name="L410" href="source/net/ipv4/inet_diag.c#L410">410</a> }
<a name="L411" href="source/net/ipv4/inet_diag.c#L411">411</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=inet_diag_dump_one_icsk">inet_diag_dump_one_icsk</a>);
<a name="L412" href="source/net/ipv4/inet_diag.c#L412">412</a> 
<a name="L413" href="source/net/ipv4/inet_diag.c#L413">413</a> static int <a href="ident?i=inet_diag_get_exact">inet_diag_get_exact</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *in_skb,
<a name="L414" href="source/net/ipv4/inet_diag.c#L414">414</a>                                const struct <a href="ident?i=nlmsghdr">nlmsghdr</a> *nlh,
<a name="L415" href="source/net/ipv4/inet_diag.c#L415">415</a>                                const struct <a href="ident?i=inet_diag_req_v2">inet_diag_req_v2</a> *<a href="ident?i=req">req</a>)
<a name="L416" href="source/net/ipv4/inet_diag.c#L416">416</a> {
<a name="L417" href="source/net/ipv4/inet_diag.c#L417">417</a>         const struct <a href="ident?i=inet_diag_handler">inet_diag_handler</a> *<a href="ident?i=handler">handler</a>;
<a name="L418" href="source/net/ipv4/inet_diag.c#L418">418</a>         int <a href="ident?i=err">err</a>;
<a name="L419" href="source/net/ipv4/inet_diag.c#L419">419</a> 
<a name="L420" href="source/net/ipv4/inet_diag.c#L420">420</a>         <a href="ident?i=handler">handler</a> = <a href="ident?i=inet_diag_lock_handler">inet_diag_lock_handler</a>(<a href="ident?i=req">req</a>-&gt;sdiag_protocol);
<a name="L421" href="source/net/ipv4/inet_diag.c#L421">421</a>         if (<a href="ident?i=IS_ERR">IS_ERR</a>(<a href="ident?i=handler">handler</a>))
<a name="L422" href="source/net/ipv4/inet_diag.c#L422">422</a>                 <a href="ident?i=err">err</a> = <a href="ident?i=PTR_ERR">PTR_ERR</a>(<a href="ident?i=handler">handler</a>);
<a name="L423" href="source/net/ipv4/inet_diag.c#L423">423</a>         else
<a name="L424" href="source/net/ipv4/inet_diag.c#L424">424</a>                 <a href="ident?i=err">err</a> = <a href="ident?i=handler">handler</a>-&gt;dump_one(in_skb, nlh, <a href="ident?i=req">req</a>);
<a name="L425" href="source/net/ipv4/inet_diag.c#L425">425</a>         <a href="ident?i=inet_diag_unlock_handler">inet_diag_unlock_handler</a>(<a href="ident?i=handler">handler</a>);
<a name="L426" href="source/net/ipv4/inet_diag.c#L426">426</a> 
<a name="L427" href="source/net/ipv4/inet_diag.c#L427">427</a>         return <a href="ident?i=err">err</a>;
<a name="L428" href="source/net/ipv4/inet_diag.c#L428">428</a> }
<a name="L429" href="source/net/ipv4/inet_diag.c#L429">429</a> 
<a name="L430" href="source/net/ipv4/inet_diag.c#L430">430</a> static int <a href="ident?i=bitstring_match">bitstring_match</a>(const <a href="ident?i=__be32">__be32</a> *<a href="ident?i=a1">a1</a>, const <a href="ident?i=__be32">__be32</a> *<a href="ident?i=a2">a2</a>, int <a href="ident?i=bits">bits</a>)
<a name="L431" href="source/net/ipv4/inet_diag.c#L431">431</a> {
<a name="L432" href="source/net/ipv4/inet_diag.c#L432">432</a>         int <a href="ident?i=words">words</a> = <a href="ident?i=bits">bits</a> &gt;&gt; 5;
<a name="L433" href="source/net/ipv4/inet_diag.c#L433">433</a> 
<a name="L434" href="source/net/ipv4/inet_diag.c#L434">434</a>         <a href="ident?i=bits">bits</a> &amp;= 0x1f;
<a name="L435" href="source/net/ipv4/inet_diag.c#L435">435</a> 
<a name="L436" href="source/net/ipv4/inet_diag.c#L436">436</a>         if (<a href="ident?i=words">words</a>) {
<a name="L437" href="source/net/ipv4/inet_diag.c#L437">437</a>                 if (<a href="ident?i=memcmp">memcmp</a>(<a href="ident?i=a1">a1</a>, <a href="ident?i=a2">a2</a>, <a href="ident?i=words">words</a> &lt;&lt; 2))
<a name="L438" href="source/net/ipv4/inet_diag.c#L438">438</a>                         return 0;
<a name="L439" href="source/net/ipv4/inet_diag.c#L439">439</a>         }
<a name="L440" href="source/net/ipv4/inet_diag.c#L440">440</a>         if (<a href="ident?i=bits">bits</a>) {
<a name="L441" href="source/net/ipv4/inet_diag.c#L441">441</a>                 <a href="ident?i=__be32">__be32</a> <a href="ident?i=w1">w1</a>, <a href="ident?i=w2">w2</a>;
<a name="L442" href="source/net/ipv4/inet_diag.c#L442">442</a>                 <a href="ident?i=__be32">__be32</a> <a href="ident?i=mask">mask</a>;
<a name="L443" href="source/net/ipv4/inet_diag.c#L443">443</a> 
<a name="L444" href="source/net/ipv4/inet_diag.c#L444">444</a>                 <a href="ident?i=w1">w1</a> = <a href="ident?i=a1">a1</a>[<a href="ident?i=words">words</a>];
<a name="L445" href="source/net/ipv4/inet_diag.c#L445">445</a>                 <a href="ident?i=w2">w2</a> = <a href="ident?i=a2">a2</a>[<a href="ident?i=words">words</a>];
<a name="L446" href="source/net/ipv4/inet_diag.c#L446">446</a> 
<a name="L447" href="source/net/ipv4/inet_diag.c#L447">447</a>                 <a href="ident?i=mask">mask</a> = <a href="ident?i=htonl">htonl</a>((0xffffffff) &lt;&lt; (32 - <a href="ident?i=bits">bits</a>));
<a name="L448" href="source/net/ipv4/inet_diag.c#L448">448</a> 
<a name="L449" href="source/net/ipv4/inet_diag.c#L449">449</a>                 if ((<a href="ident?i=w1">w1</a> ^ <a href="ident?i=w2">w2</a>) &amp; <a href="ident?i=mask">mask</a>)
<a name="L450" href="source/net/ipv4/inet_diag.c#L450">450</a>                         return 0;
<a name="L451" href="source/net/ipv4/inet_diag.c#L451">451</a>         }
<a name="L452" href="source/net/ipv4/inet_diag.c#L452">452</a> 
<a name="L453" href="source/net/ipv4/inet_diag.c#L453">453</a>         return 1;
<a name="L454" href="source/net/ipv4/inet_diag.c#L454">454</a> }
<a name="L455" href="source/net/ipv4/inet_diag.c#L455">455</a> 
<a name="L456" href="source/net/ipv4/inet_diag.c#L456">456</a> static int <a href="ident?i=inet_diag_bc_run">inet_diag_bc_run</a>(const struct <a href="ident?i=nlattr">nlattr</a> *_bc,
<a name="L457" href="source/net/ipv4/inet_diag.c#L457">457</a>                             const struct <a href="ident?i=inet_diag_entry">inet_diag_entry</a> *<a href="ident?i=entry">entry</a>)
<a name="L458" href="source/net/ipv4/inet_diag.c#L458">458</a> {
<a name="L459" href="source/net/ipv4/inet_diag.c#L459">459</a>         const void *<a href="ident?i=bc">bc</a> = <a href="ident?i=nla_data">nla_data</a>(_bc);
<a name="L460" href="source/net/ipv4/inet_diag.c#L460">460</a>         int <a href="ident?i=len">len</a> = <a href="ident?i=nla_len">nla_len</a>(_bc);
<a name="L461" href="source/net/ipv4/inet_diag.c#L461">461</a> 
<a name="L462" href="source/net/ipv4/inet_diag.c#L462">462</a>         while (<a href="ident?i=len">len</a> &gt; 0) {
<a name="L463" href="source/net/ipv4/inet_diag.c#L463">463</a>                 int <a href="ident?i=yes">yes</a> = 1;
<a name="L464" href="source/net/ipv4/inet_diag.c#L464">464</a>                 const struct <a href="ident?i=inet_diag_bc_op">inet_diag_bc_op</a> *<a href="ident?i=op">op</a> = <a href="ident?i=bc">bc</a>;
<a name="L465" href="source/net/ipv4/inet_diag.c#L465">465</a> 
<a name="L466" href="source/net/ipv4/inet_diag.c#L466">466</a>                 switch (<a href="ident?i=op">op</a>-&gt;<a href="ident?i=code">code</a>) {
<a name="L467" href="source/net/ipv4/inet_diag.c#L467">467</a>                 case INET_DIAG_BC_NOP:
<a name="L468" href="source/net/ipv4/inet_diag.c#L468">468</a>                         break;
<a name="L469" href="source/net/ipv4/inet_diag.c#L469">469</a>                 case INET_DIAG_BC_JMP:
<a name="L470" href="source/net/ipv4/inet_diag.c#L470">470</a>                         <a href="ident?i=yes">yes</a> = 0;
<a name="L471" href="source/net/ipv4/inet_diag.c#L471">471</a>                         break;
<a name="L472" href="source/net/ipv4/inet_diag.c#L472">472</a>                 case INET_DIAG_BC_S_GE:
<a name="L473" href="source/net/ipv4/inet_diag.c#L473">473</a>                         <a href="ident?i=yes">yes</a> = <a href="ident?i=entry">entry</a>-&gt;sport &gt;= <a href="ident?i=op">op</a>[1].no;
<a name="L474" href="source/net/ipv4/inet_diag.c#L474">474</a>                         break;
<a name="L475" href="source/net/ipv4/inet_diag.c#L475">475</a>                 case INET_DIAG_BC_S_LE:
<a name="L476" href="source/net/ipv4/inet_diag.c#L476">476</a>                         <a href="ident?i=yes">yes</a> = <a href="ident?i=entry">entry</a>-&gt;sport &lt;= <a href="ident?i=op">op</a>[1].no;
<a name="L477" href="source/net/ipv4/inet_diag.c#L477">477</a>                         break;
<a name="L478" href="source/net/ipv4/inet_diag.c#L478">478</a>                 case INET_DIAG_BC_D_GE:
<a name="L479" href="source/net/ipv4/inet_diag.c#L479">479</a>                         <a href="ident?i=yes">yes</a> = <a href="ident?i=entry">entry</a>-&gt;dport &gt;= <a href="ident?i=op">op</a>[1].no;
<a name="L480" href="source/net/ipv4/inet_diag.c#L480">480</a>                         break;
<a name="L481" href="source/net/ipv4/inet_diag.c#L481">481</a>                 case INET_DIAG_BC_D_LE:
<a name="L482" href="source/net/ipv4/inet_diag.c#L482">482</a>                         <a href="ident?i=yes">yes</a> = <a href="ident?i=entry">entry</a>-&gt;dport &lt;= <a href="ident?i=op">op</a>[1].no;
<a name="L483" href="source/net/ipv4/inet_diag.c#L483">483</a>                         break;
<a name="L484" href="source/net/ipv4/inet_diag.c#L484">484</a>                 case INET_DIAG_BC_AUTO:
<a name="L485" href="source/net/ipv4/inet_diag.c#L485">485</a>                         <a href="ident?i=yes">yes</a> = !(<a href="ident?i=entry">entry</a>-&gt;userlocks &amp; <a href="ident?i=SOCK_BINDPORT_LOCK">SOCK_BINDPORT_LOCK</a>);
<a name="L486" href="source/net/ipv4/inet_diag.c#L486">486</a>                         break;
<a name="L487" href="source/net/ipv4/inet_diag.c#L487">487</a>                 case INET_DIAG_BC_S_COND:
<a name="L488" href="source/net/ipv4/inet_diag.c#L488">488</a>                 case INET_DIAG_BC_D_COND: {
<a name="L489" href="source/net/ipv4/inet_diag.c#L489">489</a>                         const struct <a href="ident?i=inet_diag_hostcond">inet_diag_hostcond</a> *<a href="ident?i=cond">cond</a>;
<a name="L490" href="source/net/ipv4/inet_diag.c#L490">490</a>                         const <a href="ident?i=__be32">__be32</a> *<a href="ident?i=addr">addr</a>;
<a name="L491" href="source/net/ipv4/inet_diag.c#L491">491</a> 
<a name="L492" href="source/net/ipv4/inet_diag.c#L492">492</a>                         <a href="ident?i=cond">cond</a> = (const struct <a href="ident?i=inet_diag_hostcond">inet_diag_hostcond</a> *)(<a href="ident?i=op">op</a> + 1);
<a name="L493" href="source/net/ipv4/inet_diag.c#L493">493</a>                         if (<a href="ident?i=cond">cond</a>-&gt;<a href="ident?i=port">port</a> != -1 &amp;&amp;
<a name="L494" href="source/net/ipv4/inet_diag.c#L494">494</a>                             <a href="ident?i=cond">cond</a>-&gt;<a href="ident?i=port">port</a> != (<a href="ident?i=op">op</a>-&gt;<a href="ident?i=code">code</a> == INET_DIAG_BC_S_COND ?
<a name="L495" href="source/net/ipv4/inet_diag.c#L495">495</a>                                              <a href="ident?i=entry">entry</a>-&gt;sport : <a href="ident?i=entry">entry</a>-&gt;dport)) {
<a name="L496" href="source/net/ipv4/inet_diag.c#L496">496</a>                                 <a href="ident?i=yes">yes</a> = 0;
<a name="L497" href="source/net/ipv4/inet_diag.c#L497">497</a>                                 break;
<a name="L498" href="source/net/ipv4/inet_diag.c#L498">498</a>                         }
<a name="L499" href="source/net/ipv4/inet_diag.c#L499">499</a> 
<a name="L500" href="source/net/ipv4/inet_diag.c#L500">500</a>                         if (<a href="ident?i=op">op</a>-&gt;<a href="ident?i=code">code</a> == INET_DIAG_BC_S_COND)
<a name="L501" href="source/net/ipv4/inet_diag.c#L501">501</a>                                 <a href="ident?i=addr">addr</a> = <a href="ident?i=entry">entry</a>-&gt;<a href="ident?i=saddr">saddr</a>;
<a name="L502" href="source/net/ipv4/inet_diag.c#L502">502</a>                         else
<a name="L503" href="source/net/ipv4/inet_diag.c#L503">503</a>                                 <a href="ident?i=addr">addr</a> = <a href="ident?i=entry">entry</a>-&gt;<a href="ident?i=daddr">daddr</a>;
<a name="L504" href="source/net/ipv4/inet_diag.c#L504">504</a> 
<a name="L505" href="source/net/ipv4/inet_diag.c#L505">505</a>                         if (<a href="ident?i=cond">cond</a>-&gt;<a href="ident?i=family">family</a> != <a href="ident?i=AF_UNSPEC">AF_UNSPEC</a> &amp;&amp;
<a name="L506" href="source/net/ipv4/inet_diag.c#L506">506</a>                             <a href="ident?i=cond">cond</a>-&gt;<a href="ident?i=family">family</a> != <a href="ident?i=entry">entry</a>-&gt;<a href="ident?i=family">family</a>) {
<a name="L507" href="source/net/ipv4/inet_diag.c#L507">507</a>                                 if (<a href="ident?i=entry">entry</a>-&gt;<a href="ident?i=family">family</a> == <a href="ident?i=AF_INET6">AF_INET6</a> &amp;&amp;
<a name="L508" href="source/net/ipv4/inet_diag.c#L508">508</a>                                     <a href="ident?i=cond">cond</a>-&gt;<a href="ident?i=family">family</a> == <a href="ident?i=AF_INET">AF_INET</a>) {
<a name="L509" href="source/net/ipv4/inet_diag.c#L509">509</a>                                         if (<a href="ident?i=addr">addr</a>[0] == 0 &amp;&amp; <a href="ident?i=addr">addr</a>[1] == 0 &amp;&amp;
<a name="L510" href="source/net/ipv4/inet_diag.c#L510">510</a>                                             <a href="ident?i=addr">addr</a>[2] == <a href="ident?i=htonl">htonl</a>(0xffff) &amp;&amp;
<a name="L511" href="source/net/ipv4/inet_diag.c#L511">511</a>                                             <a href="ident?i=bitstring_match">bitstring_match</a>(<a href="ident?i=addr">addr</a> + 3,
<a name="L512" href="source/net/ipv4/inet_diag.c#L512">512</a>                                                             <a href="ident?i=cond">cond</a>-&gt;<a href="ident?i=addr">addr</a>,
<a name="L513" href="source/net/ipv4/inet_diag.c#L513">513</a>                                                             <a href="ident?i=cond">cond</a>-&gt;prefix_len))
<a name="L514" href="source/net/ipv4/inet_diag.c#L514">514</a>                                                 break;
<a name="L515" href="source/net/ipv4/inet_diag.c#L515">515</a>                                 }
<a name="L516" href="source/net/ipv4/inet_diag.c#L516">516</a>                                 <a href="ident?i=yes">yes</a> = 0;
<a name="L517" href="source/net/ipv4/inet_diag.c#L517">517</a>                                 break;
<a name="L518" href="source/net/ipv4/inet_diag.c#L518">518</a>                         }
<a name="L519" href="source/net/ipv4/inet_diag.c#L519">519</a> 
<a name="L520" href="source/net/ipv4/inet_diag.c#L520">520</a>                         if (<a href="ident?i=cond">cond</a>-&gt;prefix_len == 0)
<a name="L521" href="source/net/ipv4/inet_diag.c#L521">521</a>                                 break;
<a name="L522" href="source/net/ipv4/inet_diag.c#L522">522</a>                         if (<a href="ident?i=bitstring_match">bitstring_match</a>(<a href="ident?i=addr">addr</a>, <a href="ident?i=cond">cond</a>-&gt;<a href="ident?i=addr">addr</a>,
<a name="L523" href="source/net/ipv4/inet_diag.c#L523">523</a>                                             <a href="ident?i=cond">cond</a>-&gt;prefix_len))
<a name="L524" href="source/net/ipv4/inet_diag.c#L524">524</a>                                 break;
<a name="L525" href="source/net/ipv4/inet_diag.c#L525">525</a>                         <a href="ident?i=yes">yes</a> = 0;
<a name="L526" href="source/net/ipv4/inet_diag.c#L526">526</a>                         break;
<a name="L527" href="source/net/ipv4/inet_diag.c#L527">527</a>                 }
<a name="L528" href="source/net/ipv4/inet_diag.c#L528">528</a>                 }
<a name="L529" href="source/net/ipv4/inet_diag.c#L529">529</a> 
<a name="L530" href="source/net/ipv4/inet_diag.c#L530">530</a>                 if (<a href="ident?i=yes">yes</a>) {
<a name="L531" href="source/net/ipv4/inet_diag.c#L531">531</a>                         <a href="ident?i=len">len</a> -= <a href="ident?i=op">op</a>-&gt;<a href="ident?i=yes">yes</a>;
<a name="L532" href="source/net/ipv4/inet_diag.c#L532">532</a>                         <a href="ident?i=bc">bc</a> += <a href="ident?i=op">op</a>-&gt;<a href="ident?i=yes">yes</a>;
<a name="L533" href="source/net/ipv4/inet_diag.c#L533">533</a>                 } else {
<a name="L534" href="source/net/ipv4/inet_diag.c#L534">534</a>                         <a href="ident?i=len">len</a> -= <a href="ident?i=op">op</a>-&gt;no;
<a name="L535" href="source/net/ipv4/inet_diag.c#L535">535</a>                         <a href="ident?i=bc">bc</a> += <a href="ident?i=op">op</a>-&gt;no;
<a name="L536" href="source/net/ipv4/inet_diag.c#L536">536</a>                 }
<a name="L537" href="source/net/ipv4/inet_diag.c#L537">537</a>         }
<a name="L538" href="source/net/ipv4/inet_diag.c#L538">538</a>         return <a href="ident?i=len">len</a> == 0;
<a name="L539" href="source/net/ipv4/inet_diag.c#L539">539</a> }
<a name="L540" href="source/net/ipv4/inet_diag.c#L540">540</a> 
<a name="L541" href="source/net/ipv4/inet_diag.c#L541">541</a> <b><i>/* This helper is available for all sockets (ESTABLISH, TIMEWAIT, SYN_RECV)</i></b>
<a name="L542" href="source/net/ipv4/inet_diag.c#L542">542</a> <b><i> */</i></b>
<a name="L543" href="source/net/ipv4/inet_diag.c#L543">543</a> static void <a href="ident?i=entry_fill_addrs">entry_fill_addrs</a>(struct <a href="ident?i=inet_diag_entry">inet_diag_entry</a> *<a href="ident?i=entry">entry</a>,
<a name="L544" href="source/net/ipv4/inet_diag.c#L544">544</a>                              const struct <a href="ident?i=sock">sock</a> *sk)
<a name="L545" href="source/net/ipv4/inet_diag.c#L545">545</a> {
<a name="L546" href="source/net/ipv4/inet_diag.c#L546">546</a> #if <a href="ident?i=IS_ENABLED">IS_ENABLED</a>(CONFIG_IPV6)
<a name="L547" href="source/net/ipv4/inet_diag.c#L547">547</a>         if (sk-&gt;<a href="ident?i=sk_family">sk_family</a> == <a href="ident?i=AF_INET6">AF_INET6</a>) {
<a name="L548" href="source/net/ipv4/inet_diag.c#L548">548</a>                 <a href="ident?i=entry">entry</a>-&gt;<a href="ident?i=saddr">saddr</a> = sk-&gt;<a href="ident?i=sk_v6_rcv_saddr">sk_v6_rcv_saddr</a>.<a href="ident?i=s6_addr32">s6_addr32</a>;
<a name="L549" href="source/net/ipv4/inet_diag.c#L549">549</a>                 <a href="ident?i=entry">entry</a>-&gt;<a href="ident?i=daddr">daddr</a> = sk-&gt;<a href="ident?i=sk_v6_daddr">sk_v6_daddr</a>.<a href="ident?i=s6_addr32">s6_addr32</a>;
<a name="L550" href="source/net/ipv4/inet_diag.c#L550">550</a>         } else
<a name="L551" href="source/net/ipv4/inet_diag.c#L551">551</a> #endif
<a name="L552" href="source/net/ipv4/inet_diag.c#L552">552</a>         {
<a name="L553" href="source/net/ipv4/inet_diag.c#L553">553</a>                 <a href="ident?i=entry">entry</a>-&gt;<a href="ident?i=saddr">saddr</a> = &amp;sk-&gt;<a href="ident?i=sk_rcv_saddr">sk_rcv_saddr</a>;
<a name="L554" href="source/net/ipv4/inet_diag.c#L554">554</a>                 <a href="ident?i=entry">entry</a>-&gt;<a href="ident?i=daddr">daddr</a> = &amp;sk-&gt;<a href="ident?i=sk_daddr">sk_daddr</a>;
<a name="L555" href="source/net/ipv4/inet_diag.c#L555">555</a>         }
<a name="L556" href="source/net/ipv4/inet_diag.c#L556">556</a> }
<a name="L557" href="source/net/ipv4/inet_diag.c#L557">557</a> 
<a name="L558" href="source/net/ipv4/inet_diag.c#L558">558</a> int <a href="ident?i=inet_diag_bc_sk">inet_diag_bc_sk</a>(const struct <a href="ident?i=nlattr">nlattr</a> *<a href="ident?i=bc">bc</a>, struct <a href="ident?i=sock">sock</a> *sk)
<a name="L559" href="source/net/ipv4/inet_diag.c#L559">559</a> {
<a name="L560" href="source/net/ipv4/inet_diag.c#L560">560</a>         struct <a href="ident?i=inet_sock">inet_sock</a> *inet = <a href="ident?i=inet_sk">inet_sk</a>(sk);
<a name="L561" href="source/net/ipv4/inet_diag.c#L561">561</a>         struct <a href="ident?i=inet_diag_entry">inet_diag_entry</a> <a href="ident?i=entry">entry</a>;
<a name="L562" href="source/net/ipv4/inet_diag.c#L562">562</a> 
<a name="L563" href="source/net/ipv4/inet_diag.c#L563">563</a>         if (!<a href="ident?i=bc">bc</a>)
<a name="L564" href="source/net/ipv4/inet_diag.c#L564">564</a>                 return 1;
<a name="L565" href="source/net/ipv4/inet_diag.c#L565">565</a> 
<a name="L566" href="source/net/ipv4/inet_diag.c#L566">566</a>         <a href="ident?i=entry">entry</a>.<a href="ident?i=family">family</a> = sk-&gt;<a href="ident?i=sk_family">sk_family</a>;
<a name="L567" href="source/net/ipv4/inet_diag.c#L567">567</a>         <a href="ident?i=entry_fill_addrs">entry_fill_addrs</a>(&amp;<a href="ident?i=entry">entry</a>, sk);
<a name="L568" href="source/net/ipv4/inet_diag.c#L568">568</a>         <a href="ident?i=entry">entry</a>.sport = inet-&gt;<a href="ident?i=inet_num">inet_num</a>;
<a name="L569" href="source/net/ipv4/inet_diag.c#L569">569</a>         <a href="ident?i=entry">entry</a>.dport = <a href="ident?i=ntohs">ntohs</a>(inet-&gt;<a href="ident?i=inet_dport">inet_dport</a>);
<a name="L570" href="source/net/ipv4/inet_diag.c#L570">570</a>         <a href="ident?i=entry">entry</a>.userlocks = <a href="ident?i=sk_fullsock">sk_fullsock</a>(sk) ? sk-&gt;sk_userlocks : 0;
<a name="L571" href="source/net/ipv4/inet_diag.c#L571">571</a> 
<a name="L572" href="source/net/ipv4/inet_diag.c#L572">572</a>         return <a href="ident?i=inet_diag_bc_run">inet_diag_bc_run</a>(<a href="ident?i=bc">bc</a>, &amp;<a href="ident?i=entry">entry</a>);
<a name="L573" href="source/net/ipv4/inet_diag.c#L573">573</a> }
<a name="L574" href="source/net/ipv4/inet_diag.c#L574">574</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=inet_diag_bc_sk">inet_diag_bc_sk</a>);
<a name="L575" href="source/net/ipv4/inet_diag.c#L575">575</a> 
<a name="L576" href="source/net/ipv4/inet_diag.c#L576">576</a> static int <a href="ident?i=valid_cc">valid_cc</a>(const void *<a href="ident?i=bc">bc</a>, int <a href="ident?i=len">len</a>, int <a href="ident?i=cc">cc</a>)
<a name="L577" href="source/net/ipv4/inet_diag.c#L577">577</a> {
<a name="L578" href="source/net/ipv4/inet_diag.c#L578">578</a>         while (<a href="ident?i=len">len</a> &gt;= 0) {
<a name="L579" href="source/net/ipv4/inet_diag.c#L579">579</a>                 const struct <a href="ident?i=inet_diag_bc_op">inet_diag_bc_op</a> *<a href="ident?i=op">op</a> = <a href="ident?i=bc">bc</a>;
<a name="L580" href="source/net/ipv4/inet_diag.c#L580">580</a> 
<a name="L581" href="source/net/ipv4/inet_diag.c#L581">581</a>                 if (<a href="ident?i=cc">cc</a> &gt; <a href="ident?i=len">len</a>)
<a name="L582" href="source/net/ipv4/inet_diag.c#L582">582</a>                         return 0;
<a name="L583" href="source/net/ipv4/inet_diag.c#L583">583</a>                 if (<a href="ident?i=cc">cc</a> == <a href="ident?i=len">len</a>)
<a name="L584" href="source/net/ipv4/inet_diag.c#L584">584</a>                         return 1;
<a name="L585" href="source/net/ipv4/inet_diag.c#L585">585</a>                 if (<a href="ident?i=op">op</a>-&gt;<a href="ident?i=yes">yes</a> &lt; 4 || <a href="ident?i=op">op</a>-&gt;<a href="ident?i=yes">yes</a> &amp; 3)
<a name="L586" href="source/net/ipv4/inet_diag.c#L586">586</a>                         return 0;
<a name="L587" href="source/net/ipv4/inet_diag.c#L587">587</a>                 <a href="ident?i=len">len</a> -= <a href="ident?i=op">op</a>-&gt;<a href="ident?i=yes">yes</a>;
<a name="L588" href="source/net/ipv4/inet_diag.c#L588">588</a>                 <a href="ident?i=bc">bc</a>  += <a href="ident?i=op">op</a>-&gt;<a href="ident?i=yes">yes</a>;
<a name="L589" href="source/net/ipv4/inet_diag.c#L589">589</a>         }
<a name="L590" href="source/net/ipv4/inet_diag.c#L590">590</a>         return 0;
<a name="L591" href="source/net/ipv4/inet_diag.c#L591">591</a> }
<a name="L592" href="source/net/ipv4/inet_diag.c#L592">592</a> 
<a name="L593" href="source/net/ipv4/inet_diag.c#L593">593</a> <b><i>/* Validate an inet_diag_hostcond. */</i></b>
<a name="L594" href="source/net/ipv4/inet_diag.c#L594">594</a> static <a href="ident?i=bool">bool</a> <a href="ident?i=valid_hostcond">valid_hostcond</a>(const struct <a href="ident?i=inet_diag_bc_op">inet_diag_bc_op</a> *<a href="ident?i=op">op</a>, int <a href="ident?i=len">len</a>,
<a name="L595" href="source/net/ipv4/inet_diag.c#L595">595</a>                            int *min_len)
<a name="L596" href="source/net/ipv4/inet_diag.c#L596">596</a> {
<a name="L597" href="source/net/ipv4/inet_diag.c#L597">597</a>         struct <a href="ident?i=inet_diag_hostcond">inet_diag_hostcond</a> *<a href="ident?i=cond">cond</a>;
<a name="L598" href="source/net/ipv4/inet_diag.c#L598">598</a>         int addr_len;
<a name="L599" href="source/net/ipv4/inet_diag.c#L599">599</a> 
<a name="L600" href="source/net/ipv4/inet_diag.c#L600">600</a>         <b><i>/* Check hostcond space. */</i></b>
<a name="L601" href="source/net/ipv4/inet_diag.c#L601">601</a>         *min_len += sizeof(struct <a href="ident?i=inet_diag_hostcond">inet_diag_hostcond</a>);
<a name="L602" href="source/net/ipv4/inet_diag.c#L602">602</a>         if (<a href="ident?i=len">len</a> &lt; *min_len)
<a name="L603" href="source/net/ipv4/inet_diag.c#L603">603</a>                 return <a href="ident?i=false">false</a>;
<a name="L604" href="source/net/ipv4/inet_diag.c#L604">604</a>         <a href="ident?i=cond">cond</a> = (struct <a href="ident?i=inet_diag_hostcond">inet_diag_hostcond</a> *)(<a href="ident?i=op">op</a> + 1);
<a name="L605" href="source/net/ipv4/inet_diag.c#L605">605</a> 
<a name="L606" href="source/net/ipv4/inet_diag.c#L606">606</a>         <b><i>/* Check address family and address length. */</i></b>
<a name="L607" href="source/net/ipv4/inet_diag.c#L607">607</a>         switch (<a href="ident?i=cond">cond</a>-&gt;<a href="ident?i=family">family</a>) {
<a name="L608" href="source/net/ipv4/inet_diag.c#L608">608</a>         case <a href="ident?i=AF_UNSPEC">AF_UNSPEC</a>:
<a name="L609" href="source/net/ipv4/inet_diag.c#L609">609</a>                 addr_len = 0;
<a name="L610" href="source/net/ipv4/inet_diag.c#L610">610</a>                 break;
<a name="L611" href="source/net/ipv4/inet_diag.c#L611">611</a>         case <a href="ident?i=AF_INET">AF_INET</a>:
<a name="L612" href="source/net/ipv4/inet_diag.c#L612">612</a>                 addr_len = sizeof(struct <a href="ident?i=in_addr">in_addr</a>);
<a name="L613" href="source/net/ipv4/inet_diag.c#L613">613</a>                 break;
<a name="L614" href="source/net/ipv4/inet_diag.c#L614">614</a>         case <a href="ident?i=AF_INET6">AF_INET6</a>:
<a name="L615" href="source/net/ipv4/inet_diag.c#L615">615</a>                 addr_len = sizeof(struct <a href="ident?i=in6_addr">in6_addr</a>);
<a name="L616" href="source/net/ipv4/inet_diag.c#L616">616</a>                 break;
<a name="L617" href="source/net/ipv4/inet_diag.c#L617">617</a>         default:
<a name="L618" href="source/net/ipv4/inet_diag.c#L618">618</a>                 return <a href="ident?i=false">false</a>;
<a name="L619" href="source/net/ipv4/inet_diag.c#L619">619</a>         }
<a name="L620" href="source/net/ipv4/inet_diag.c#L620">620</a>         *min_len += addr_len;
<a name="L621" href="source/net/ipv4/inet_diag.c#L621">621</a>         if (<a href="ident?i=len">len</a> &lt; *min_len)
<a name="L622" href="source/net/ipv4/inet_diag.c#L622">622</a>                 return <a href="ident?i=false">false</a>;
<a name="L623" href="source/net/ipv4/inet_diag.c#L623">623</a> 
<a name="L624" href="source/net/ipv4/inet_diag.c#L624">624</a>         <b><i>/* Check prefix length (in bits) vs address length (in bytes). */</i></b>
<a name="L625" href="source/net/ipv4/inet_diag.c#L625">625</a>         if (<a href="ident?i=cond">cond</a>-&gt;prefix_len &gt; 8 * addr_len)
<a name="L626" href="source/net/ipv4/inet_diag.c#L626">626</a>                 return <a href="ident?i=false">false</a>;
<a name="L627" href="source/net/ipv4/inet_diag.c#L627">627</a> 
<a name="L628" href="source/net/ipv4/inet_diag.c#L628">628</a>         return <a href="ident?i=true">true</a>;
<a name="L629" href="source/net/ipv4/inet_diag.c#L629">629</a> }
<a name="L630" href="source/net/ipv4/inet_diag.c#L630">630</a> 
<a name="L631" href="source/net/ipv4/inet_diag.c#L631">631</a> <b><i>/* Validate a port comparison operator. */</i></b>
<a name="L632" href="source/net/ipv4/inet_diag.c#L632">632</a> static <a href="ident?i=bool">bool</a> <a href="ident?i=valid_port_comparison">valid_port_comparison</a>(const struct <a href="ident?i=inet_diag_bc_op">inet_diag_bc_op</a> *<a href="ident?i=op">op</a>,
<a name="L633" href="source/net/ipv4/inet_diag.c#L633">633</a>                                   int <a href="ident?i=len">len</a>, int *min_len)
<a name="L634" href="source/net/ipv4/inet_diag.c#L634">634</a> {
<a name="L635" href="source/net/ipv4/inet_diag.c#L635">635</a>         <b><i>/* Port comparisons put the port in a follow-on inet_diag_bc_op. */</i></b>
<a name="L636" href="source/net/ipv4/inet_diag.c#L636">636</a>         *min_len += sizeof(struct <a href="ident?i=inet_diag_bc_op">inet_diag_bc_op</a>);
<a name="L637" href="source/net/ipv4/inet_diag.c#L637">637</a>         if (<a href="ident?i=len">len</a> &lt; *min_len)
<a name="L638" href="source/net/ipv4/inet_diag.c#L638">638</a>                 return <a href="ident?i=false">false</a>;
<a name="L639" href="source/net/ipv4/inet_diag.c#L639">639</a>         return <a href="ident?i=true">true</a>;
<a name="L640" href="source/net/ipv4/inet_diag.c#L640">640</a> }
<a name="L641" href="source/net/ipv4/inet_diag.c#L641">641</a> 
<a name="L642" href="source/net/ipv4/inet_diag.c#L642">642</a> static int <a href="ident?i=inet_diag_bc_audit">inet_diag_bc_audit</a>(const void *bytecode, int bytecode_len)
<a name="L643" href="source/net/ipv4/inet_diag.c#L643">643</a> {
<a name="L644" href="source/net/ipv4/inet_diag.c#L644">644</a>         const void *<a href="ident?i=bc">bc</a> = bytecode;
<a name="L645" href="source/net/ipv4/inet_diag.c#L645">645</a>         int  <a href="ident?i=len">len</a> = bytecode_len;
<a name="L646" href="source/net/ipv4/inet_diag.c#L646">646</a> 
<a name="L647" href="source/net/ipv4/inet_diag.c#L647">647</a>         while (<a href="ident?i=len">len</a> &gt; 0) {
<a name="L648" href="source/net/ipv4/inet_diag.c#L648">648</a>                 int min_len = sizeof(struct <a href="ident?i=inet_diag_bc_op">inet_diag_bc_op</a>);
<a name="L649" href="source/net/ipv4/inet_diag.c#L649">649</a>                 const struct <a href="ident?i=inet_diag_bc_op">inet_diag_bc_op</a> *<a href="ident?i=op">op</a> = <a href="ident?i=bc">bc</a>;
<a name="L650" href="source/net/ipv4/inet_diag.c#L650">650</a> 
<a name="L651" href="source/net/ipv4/inet_diag.c#L651">651</a>                 switch (<a href="ident?i=op">op</a>-&gt;<a href="ident?i=code">code</a>) {
<a name="L652" href="source/net/ipv4/inet_diag.c#L652">652</a>                 case INET_DIAG_BC_S_COND:
<a name="L653" href="source/net/ipv4/inet_diag.c#L653">653</a>                 case INET_DIAG_BC_D_COND:
<a name="L654" href="source/net/ipv4/inet_diag.c#L654">654</a>                         if (!<a href="ident?i=valid_hostcond">valid_hostcond</a>(<a href="ident?i=bc">bc</a>, <a href="ident?i=len">len</a>, &amp;min_len))
<a name="L655" href="source/net/ipv4/inet_diag.c#L655">655</a>                                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L656" href="source/net/ipv4/inet_diag.c#L656">656</a>                         break;
<a name="L657" href="source/net/ipv4/inet_diag.c#L657">657</a>                 case INET_DIAG_BC_S_GE:
<a name="L658" href="source/net/ipv4/inet_diag.c#L658">658</a>                 case INET_DIAG_BC_S_LE:
<a name="L659" href="source/net/ipv4/inet_diag.c#L659">659</a>                 case INET_DIAG_BC_D_GE:
<a name="L660" href="source/net/ipv4/inet_diag.c#L660">660</a>                 case INET_DIAG_BC_D_LE:
<a name="L661" href="source/net/ipv4/inet_diag.c#L661">661</a>                         if (!<a href="ident?i=valid_port_comparison">valid_port_comparison</a>(<a href="ident?i=bc">bc</a>, <a href="ident?i=len">len</a>, &amp;min_len))
<a name="L662" href="source/net/ipv4/inet_diag.c#L662">662</a>                                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L663" href="source/net/ipv4/inet_diag.c#L663">663</a>                         break;
<a name="L664" href="source/net/ipv4/inet_diag.c#L664">664</a>                 case INET_DIAG_BC_AUTO:
<a name="L665" href="source/net/ipv4/inet_diag.c#L665">665</a>                 case INET_DIAG_BC_JMP:
<a name="L666" href="source/net/ipv4/inet_diag.c#L666">666</a>                 case INET_DIAG_BC_NOP:
<a name="L667" href="source/net/ipv4/inet_diag.c#L667">667</a>                         break;
<a name="L668" href="source/net/ipv4/inet_diag.c#L668">668</a>                 default:
<a name="L669" href="source/net/ipv4/inet_diag.c#L669">669</a>                         return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L670" href="source/net/ipv4/inet_diag.c#L670">670</a>                 }
<a name="L671" href="source/net/ipv4/inet_diag.c#L671">671</a> 
<a name="L672" href="source/net/ipv4/inet_diag.c#L672">672</a>                 if (<a href="ident?i=op">op</a>-&gt;<a href="ident?i=code">code</a> != INET_DIAG_BC_NOP) {
<a name="L673" href="source/net/ipv4/inet_diag.c#L673">673</a>                         if (<a href="ident?i=op">op</a>-&gt;no &lt; min_len || <a href="ident?i=op">op</a>-&gt;no &gt; <a href="ident?i=len">len</a> + 4 || <a href="ident?i=op">op</a>-&gt;no &amp; 3)
<a name="L674" href="source/net/ipv4/inet_diag.c#L674">674</a>                                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L675" href="source/net/ipv4/inet_diag.c#L675">675</a>                         if (<a href="ident?i=op">op</a>-&gt;no &lt; <a href="ident?i=len">len</a> &amp;&amp;
<a name="L676" href="source/net/ipv4/inet_diag.c#L676">676</a>                             !<a href="ident?i=valid_cc">valid_cc</a>(bytecode, bytecode_len, <a href="ident?i=len">len</a> - <a href="ident?i=op">op</a>-&gt;no))
<a name="L677" href="source/net/ipv4/inet_diag.c#L677">677</a>                                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L678" href="source/net/ipv4/inet_diag.c#L678">678</a>                 }
<a name="L679" href="source/net/ipv4/inet_diag.c#L679">679</a> 
<a name="L680" href="source/net/ipv4/inet_diag.c#L680">680</a>                 if (<a href="ident?i=op">op</a>-&gt;<a href="ident?i=yes">yes</a> &lt; min_len || <a href="ident?i=op">op</a>-&gt;<a href="ident?i=yes">yes</a> &gt; <a href="ident?i=len">len</a> + 4 || <a href="ident?i=op">op</a>-&gt;<a href="ident?i=yes">yes</a> &amp; 3)
<a name="L681" href="source/net/ipv4/inet_diag.c#L681">681</a>                         return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L682" href="source/net/ipv4/inet_diag.c#L682">682</a>                 <a href="ident?i=bc">bc</a>  += <a href="ident?i=op">op</a>-&gt;<a href="ident?i=yes">yes</a>;
<a name="L683" href="source/net/ipv4/inet_diag.c#L683">683</a>                 <a href="ident?i=len">len</a> -= <a href="ident?i=op">op</a>-&gt;<a href="ident?i=yes">yes</a>;
<a name="L684" href="source/net/ipv4/inet_diag.c#L684">684</a>         }
<a name="L685" href="source/net/ipv4/inet_diag.c#L685">685</a>         return <a href="ident?i=len">len</a> == 0 ? 0 : -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L686" href="source/net/ipv4/inet_diag.c#L686">686</a> }
<a name="L687" href="source/net/ipv4/inet_diag.c#L687">687</a> 
<a name="L688" href="source/net/ipv4/inet_diag.c#L688">688</a> static int <a href="ident?i=inet_csk_diag_dump">inet_csk_diag_dump</a>(struct <a href="ident?i=sock">sock</a> *sk,
<a name="L689" href="source/net/ipv4/inet_diag.c#L689">689</a>                               struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
<a name="L690" href="source/net/ipv4/inet_diag.c#L690">690</a>                               struct <a href="ident?i=netlink_callback">netlink_callback</a> *<a href="ident?i=cb">cb</a>,
<a name="L691" href="source/net/ipv4/inet_diag.c#L691">691</a>                               const struct <a href="ident?i=inet_diag_req_v2">inet_diag_req_v2</a> *<a href="ident?i=r">r</a>,
<a name="L692" href="source/net/ipv4/inet_diag.c#L692">692</a>                               const struct <a href="ident?i=nlattr">nlattr</a> *<a href="ident?i=bc">bc</a>)
<a name="L693" href="source/net/ipv4/inet_diag.c#L693">693</a> {
<a name="L694" href="source/net/ipv4/inet_diag.c#L694">694</a>         if (!<a href="ident?i=inet_diag_bc_sk">inet_diag_bc_sk</a>(<a href="ident?i=bc">bc</a>, sk))
<a name="L695" href="source/net/ipv4/inet_diag.c#L695">695</a>                 return 0;
<a name="L696" href="source/net/ipv4/inet_diag.c#L696">696</a> 
<a name="L697" href="source/net/ipv4/inet_diag.c#L697">697</a>         return <a href="ident?i=inet_csk_diag_fill">inet_csk_diag_fill</a>(sk, <a href="ident?i=skb">skb</a>, <a href="ident?i=r">r</a>,
<a name="L698" href="source/net/ipv4/inet_diag.c#L698">698</a>                                   <a href="ident?i=sk_user_ns">sk_user_ns</a>(<a href="ident?i=NETLINK_CB">NETLINK_CB</a>(<a href="ident?i=cb">cb</a>-&gt;<a href="ident?i=skb">skb</a>).sk),
<a name="L699" href="source/net/ipv4/inet_diag.c#L699">699</a>                                   <a href="ident?i=NETLINK_CB">NETLINK_CB</a>(<a href="ident?i=cb">cb</a>-&gt;<a href="ident?i=skb">skb</a>).portid,
<a name="L700" href="source/net/ipv4/inet_diag.c#L700">700</a>                                   <a href="ident?i=cb">cb</a>-&gt;nlh-&gt;nlmsg_seq, <a href="ident?i=NLM_F_MULTI">NLM_F_MULTI</a>, <a href="ident?i=cb">cb</a>-&gt;nlh);
<a name="L701" href="source/net/ipv4/inet_diag.c#L701">701</a> }
<a name="L702" href="source/net/ipv4/inet_diag.c#L702">702</a> 
<a name="L703" href="source/net/ipv4/inet_diag.c#L703">703</a> static void <a href="ident?i=twsk_build_assert">twsk_build_assert</a>(void)
<a name="L704" href="source/net/ipv4/inet_diag.c#L704">704</a> {
<a name="L705" href="source/net/ipv4/inet_diag.c#L705">705</a>         <a href="ident?i=BUILD_BUG_ON">BUILD_BUG_ON</a>(<a href="ident?i=offsetof">offsetof</a>(struct <a href="ident?i=inet_timewait_sock">inet_timewait_sock</a>, <a href="ident?i=tw_family">tw_family</a>) !=
<a name="L706" href="source/net/ipv4/inet_diag.c#L706">706</a>                      <a href="ident?i=offsetof">offsetof</a>(struct <a href="ident?i=sock">sock</a>, <a href="ident?i=sk_family">sk_family</a>));
<a name="L707" href="source/net/ipv4/inet_diag.c#L707">707</a> 
<a name="L708" href="source/net/ipv4/inet_diag.c#L708">708</a>         <a href="ident?i=BUILD_BUG_ON">BUILD_BUG_ON</a>(<a href="ident?i=offsetof">offsetof</a>(struct <a href="ident?i=inet_timewait_sock">inet_timewait_sock</a>, <a href="ident?i=tw_num">tw_num</a>) !=
<a name="L709" href="source/net/ipv4/inet_diag.c#L709">709</a>                      <a href="ident?i=offsetof">offsetof</a>(struct <a href="ident?i=inet_sock">inet_sock</a>, <a href="ident?i=inet_num">inet_num</a>));
<a name="L710" href="source/net/ipv4/inet_diag.c#L710">710</a> 
<a name="L711" href="source/net/ipv4/inet_diag.c#L711">711</a>         <a href="ident?i=BUILD_BUG_ON">BUILD_BUG_ON</a>(<a href="ident?i=offsetof">offsetof</a>(struct <a href="ident?i=inet_timewait_sock">inet_timewait_sock</a>, <a href="ident?i=tw_dport">tw_dport</a>) !=
<a name="L712" href="source/net/ipv4/inet_diag.c#L712">712</a>                      <a href="ident?i=offsetof">offsetof</a>(struct <a href="ident?i=inet_sock">inet_sock</a>, <a href="ident?i=inet_dport">inet_dport</a>));
<a name="L713" href="source/net/ipv4/inet_diag.c#L713">713</a> 
<a name="L714" href="source/net/ipv4/inet_diag.c#L714">714</a>         <a href="ident?i=BUILD_BUG_ON">BUILD_BUG_ON</a>(<a href="ident?i=offsetof">offsetof</a>(struct <a href="ident?i=inet_timewait_sock">inet_timewait_sock</a>, <a href="ident?i=tw_rcv_saddr">tw_rcv_saddr</a>) !=
<a name="L715" href="source/net/ipv4/inet_diag.c#L715">715</a>                      <a href="ident?i=offsetof">offsetof</a>(struct <a href="ident?i=inet_sock">inet_sock</a>, <a href="ident?i=inet_rcv_saddr">inet_rcv_saddr</a>));
<a name="L716" href="source/net/ipv4/inet_diag.c#L716">716</a> 
<a name="L717" href="source/net/ipv4/inet_diag.c#L717">717</a>         <a href="ident?i=BUILD_BUG_ON">BUILD_BUG_ON</a>(<a href="ident?i=offsetof">offsetof</a>(struct <a href="ident?i=inet_timewait_sock">inet_timewait_sock</a>, <a href="ident?i=tw_daddr">tw_daddr</a>) !=
<a name="L718" href="source/net/ipv4/inet_diag.c#L718">718</a>                      <a href="ident?i=offsetof">offsetof</a>(struct <a href="ident?i=inet_sock">inet_sock</a>, <a href="ident?i=inet_daddr">inet_daddr</a>));
<a name="L719" href="source/net/ipv4/inet_diag.c#L719">719</a> 
<a name="L720" href="source/net/ipv4/inet_diag.c#L720">720</a> #if <a href="ident?i=IS_ENABLED">IS_ENABLED</a>(CONFIG_IPV6)
<a name="L721" href="source/net/ipv4/inet_diag.c#L721">721</a>         <a href="ident?i=BUILD_BUG_ON">BUILD_BUG_ON</a>(<a href="ident?i=offsetof">offsetof</a>(struct <a href="ident?i=inet_timewait_sock">inet_timewait_sock</a>, <a href="ident?i=tw_v6_rcv_saddr">tw_v6_rcv_saddr</a>) !=
<a name="L722" href="source/net/ipv4/inet_diag.c#L722">722</a>                      <a href="ident?i=offsetof">offsetof</a>(struct <a href="ident?i=sock">sock</a>, <a href="ident?i=sk_v6_rcv_saddr">sk_v6_rcv_saddr</a>));
<a name="L723" href="source/net/ipv4/inet_diag.c#L723">723</a> 
<a name="L724" href="source/net/ipv4/inet_diag.c#L724">724</a>         <a href="ident?i=BUILD_BUG_ON">BUILD_BUG_ON</a>(<a href="ident?i=offsetof">offsetof</a>(struct <a href="ident?i=inet_timewait_sock">inet_timewait_sock</a>, <a href="ident?i=tw_v6_daddr">tw_v6_daddr</a>) !=
<a name="L725" href="source/net/ipv4/inet_diag.c#L725">725</a>                      <a href="ident?i=offsetof">offsetof</a>(struct <a href="ident?i=sock">sock</a>, <a href="ident?i=sk_v6_daddr">sk_v6_daddr</a>));
<a name="L726" href="source/net/ipv4/inet_diag.c#L726">726</a> #endif
<a name="L727" href="source/net/ipv4/inet_diag.c#L727">727</a> }
<a name="L728" href="source/net/ipv4/inet_diag.c#L728">728</a> 
<a name="L729" href="source/net/ipv4/inet_diag.c#L729">729</a> static int <a href="ident?i=inet_diag_dump_reqs">inet_diag_dump_reqs</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, struct <a href="ident?i=sock">sock</a> *sk,
<a name="L730" href="source/net/ipv4/inet_diag.c#L730">730</a>                                struct <a href="ident?i=netlink_callback">netlink_callback</a> *<a href="ident?i=cb">cb</a>,
<a name="L731" href="source/net/ipv4/inet_diag.c#L731">731</a>                                const struct <a href="ident?i=inet_diag_req_v2">inet_diag_req_v2</a> *<a href="ident?i=r">r</a>,
<a name="L732" href="source/net/ipv4/inet_diag.c#L732">732</a>                                const struct <a href="ident?i=nlattr">nlattr</a> *<a href="ident?i=bc">bc</a>)
<a name="L733" href="source/net/ipv4/inet_diag.c#L733">733</a> {
<a name="L734" href="source/net/ipv4/inet_diag.c#L734">734</a>         struct <a href="ident?i=inet_connection_sock">inet_connection_sock</a> *icsk = <a href="ident?i=inet_csk">inet_csk</a>(sk);
<a name="L735" href="source/net/ipv4/inet_diag.c#L735">735</a>         struct <a href="ident?i=inet_sock">inet_sock</a> *inet = <a href="ident?i=inet_sk">inet_sk</a>(sk);
<a name="L736" href="source/net/ipv4/inet_diag.c#L736">736</a>         struct <a href="ident?i=inet_diag_entry">inet_diag_entry</a> <a href="ident?i=entry">entry</a>;
<a name="L737" href="source/net/ipv4/inet_diag.c#L737">737</a>         int j, s_j, reqnum, s_reqnum;
<a name="L738" href="source/net/ipv4/inet_diag.c#L738">738</a>         struct <a href="ident?i=listen_sock">listen_sock</a> *lopt;
<a name="L739" href="source/net/ipv4/inet_diag.c#L739">739</a>         int <a href="ident?i=err">err</a> = 0;
<a name="L740" href="source/net/ipv4/inet_diag.c#L740">740</a> 
<a name="L741" href="source/net/ipv4/inet_diag.c#L741">741</a>         s_j = <a href="ident?i=cb">cb</a>-&gt;<a href="ident?i=args">args</a>[3];
<a name="L742" href="source/net/ipv4/inet_diag.c#L742">742</a>         s_reqnum = <a href="ident?i=cb">cb</a>-&gt;<a href="ident?i=args">args</a>[4];
<a name="L743" href="source/net/ipv4/inet_diag.c#L743">743</a> 
<a name="L744" href="source/net/ipv4/inet_diag.c#L744">744</a>         if (s_j &gt; 0)
<a name="L745" href="source/net/ipv4/inet_diag.c#L745">745</a>                 s_j--;
<a name="L746" href="source/net/ipv4/inet_diag.c#L746">746</a> 
<a name="L747" href="source/net/ipv4/inet_diag.c#L747">747</a>         <a href="ident?i=entry">entry</a>.<a href="ident?i=family">family</a> = sk-&gt;<a href="ident?i=sk_family">sk_family</a>;
<a name="L748" href="source/net/ipv4/inet_diag.c#L748">748</a> 
<a name="L749" href="source/net/ipv4/inet_diag.c#L749">749</a>         <a href="ident?i=spin_lock_bh">spin_lock_bh</a>(&amp;icsk-&gt;icsk_accept_queue.syn_wait_lock);
<a name="L750" href="source/net/ipv4/inet_diag.c#L750">750</a> 
<a name="L751" href="source/net/ipv4/inet_diag.c#L751">751</a>         lopt = icsk-&gt;icsk_accept_queue.listen_opt;
<a name="L752" href="source/net/ipv4/inet_diag.c#L752">752</a>         if (!lopt || !<a href="ident?i=listen_sock_qlen">listen_sock_qlen</a>(lopt))
<a name="L753" href="source/net/ipv4/inet_diag.c#L753">753</a>                 goto <a href="ident?i=out">out</a>;
<a name="L754" href="source/net/ipv4/inet_diag.c#L754">754</a> 
<a name="L755" href="source/net/ipv4/inet_diag.c#L755">755</a>         if (<a href="ident?i=bc">bc</a>) {
<a name="L756" href="source/net/ipv4/inet_diag.c#L756">756</a>                 <a href="ident?i=entry">entry</a>.sport = inet-&gt;<a href="ident?i=inet_num">inet_num</a>;
<a name="L757" href="source/net/ipv4/inet_diag.c#L757">757</a>                 <a href="ident?i=entry">entry</a>.userlocks = sk-&gt;sk_userlocks;
<a name="L758" href="source/net/ipv4/inet_diag.c#L758">758</a>         }
<a name="L759" href="source/net/ipv4/inet_diag.c#L759">759</a> 
<a name="L760" href="source/net/ipv4/inet_diag.c#L760">760</a>         for (j = s_j; j &lt; lopt-&gt;nr_table_entries; j++) {
<a name="L761" href="source/net/ipv4/inet_diag.c#L761">761</a>                 struct <a href="ident?i=request_sock">request_sock</a> *<a href="ident?i=req">req</a>, *<a href="ident?i=head">head</a> = lopt-&gt;syn_table[j];
<a name="L762" href="source/net/ipv4/inet_diag.c#L762">762</a> 
<a name="L763" href="source/net/ipv4/inet_diag.c#L763">763</a>                 reqnum = 0;
<a name="L764" href="source/net/ipv4/inet_diag.c#L764">764</a>                 for (<a href="ident?i=req">req</a> = <a href="ident?i=head">head</a>; <a href="ident?i=req">req</a>; reqnum++, <a href="ident?i=req">req</a> = <a href="ident?i=req">req</a>-&gt;dl_next) {
<a name="L765" href="source/net/ipv4/inet_diag.c#L765">765</a>                         struct <a href="ident?i=inet_request_sock">inet_request_sock</a> *ireq = <a href="ident?i=inet_rsk">inet_rsk</a>(<a href="ident?i=req">req</a>);
<a name="L766" href="source/net/ipv4/inet_diag.c#L766">766</a> 
<a name="L767" href="source/net/ipv4/inet_diag.c#L767">767</a>                         if (reqnum &lt; s_reqnum)
<a name="L768" href="source/net/ipv4/inet_diag.c#L768">768</a>                                 continue;
<a name="L769" href="source/net/ipv4/inet_diag.c#L769">769</a>                         if (<a href="ident?i=r">r</a>-&gt;<a href="ident?i=id">id</a>.idiag_dport != ireq-&gt;<a href="ident?i=ir_rmt_port">ir_rmt_port</a> &amp;&amp;
<a name="L770" href="source/net/ipv4/inet_diag.c#L770">770</a>                             <a href="ident?i=r">r</a>-&gt;<a href="ident?i=id">id</a>.idiag_dport)
<a name="L771" href="source/net/ipv4/inet_diag.c#L771">771</a>                                 continue;
<a name="L772" href="source/net/ipv4/inet_diag.c#L772">772</a> 
<a name="L773" href="source/net/ipv4/inet_diag.c#L773">773</a>                         if (<a href="ident?i=bc">bc</a>) {
<a name="L774" href="source/net/ipv4/inet_diag.c#L774">774</a>                                 <b><i>/* Note: entry.sport and entry.userlocks are already set */</i></b>
<a name="L775" href="source/net/ipv4/inet_diag.c#L775">775</a>                                 <a href="ident?i=entry_fill_addrs">entry_fill_addrs</a>(&amp;<a href="ident?i=entry">entry</a>, <a href="ident?i=req_to_sk">req_to_sk</a>(<a href="ident?i=req">req</a>));
<a name="L776" href="source/net/ipv4/inet_diag.c#L776">776</a>                                 <a href="ident?i=entry">entry</a>.dport = <a href="ident?i=ntohs">ntohs</a>(ireq-&gt;<a href="ident?i=ir_rmt_port">ir_rmt_port</a>);
<a name="L777" href="source/net/ipv4/inet_diag.c#L777">777</a> 
<a name="L778" href="source/net/ipv4/inet_diag.c#L778">778</a>                                 if (!<a href="ident?i=inet_diag_bc_run">inet_diag_bc_run</a>(<a href="ident?i=bc">bc</a>, &amp;<a href="ident?i=entry">entry</a>))
<a name="L779" href="source/net/ipv4/inet_diag.c#L779">779</a>                                         continue;
<a name="L780" href="source/net/ipv4/inet_diag.c#L780">780</a>                         }
<a name="L781" href="source/net/ipv4/inet_diag.c#L781">781</a> 
<a name="L782" href="source/net/ipv4/inet_diag.c#L782">782</a>                         <a href="ident?i=err">err</a> = <a href="ident?i=inet_req_diag_fill">inet_req_diag_fill</a>(<a href="ident?i=req_to_sk">req_to_sk</a>(<a href="ident?i=req">req</a>), <a href="ident?i=skb">skb</a>,
<a name="L783" href="source/net/ipv4/inet_diag.c#L783">783</a>                                                  <a href="ident?i=NETLINK_CB">NETLINK_CB</a>(<a href="ident?i=cb">cb</a>-&gt;<a href="ident?i=skb">skb</a>).portid,
<a name="L784" href="source/net/ipv4/inet_diag.c#L784">784</a>                                                  <a href="ident?i=cb">cb</a>-&gt;nlh-&gt;nlmsg_seq,
<a name="L785" href="source/net/ipv4/inet_diag.c#L785">785</a>                                                  <a href="ident?i=NLM_F_MULTI">NLM_F_MULTI</a>, <a href="ident?i=cb">cb</a>-&gt;nlh);
<a name="L786" href="source/net/ipv4/inet_diag.c#L786">786</a>                         if (<a href="ident?i=err">err</a> &lt; 0) {
<a name="L787" href="source/net/ipv4/inet_diag.c#L787">787</a>                                 <a href="ident?i=cb">cb</a>-&gt;<a href="ident?i=args">args</a>[3] = j + 1;
<a name="L788" href="source/net/ipv4/inet_diag.c#L788">788</a>                                 <a href="ident?i=cb">cb</a>-&gt;<a href="ident?i=args">args</a>[4] = reqnum;
<a name="L789" href="source/net/ipv4/inet_diag.c#L789">789</a>                                 goto <a href="ident?i=out">out</a>;
<a name="L790" href="source/net/ipv4/inet_diag.c#L790">790</a>                         }
<a name="L791" href="source/net/ipv4/inet_diag.c#L791">791</a>                 }
<a name="L792" href="source/net/ipv4/inet_diag.c#L792">792</a> 
<a name="L793" href="source/net/ipv4/inet_diag.c#L793">793</a>                 s_reqnum = 0;
<a name="L794" href="source/net/ipv4/inet_diag.c#L794">794</a>         }
<a name="L795" href="source/net/ipv4/inet_diag.c#L795">795</a> 
<a name="L796" href="source/net/ipv4/inet_diag.c#L796">796</a> <a href="ident?i=out">out</a>:
<a name="L797" href="source/net/ipv4/inet_diag.c#L797">797</a>         <a href="ident?i=spin_unlock_bh">spin_unlock_bh</a>(&amp;icsk-&gt;icsk_accept_queue.syn_wait_lock);
<a name="L798" href="source/net/ipv4/inet_diag.c#L798">798</a> 
<a name="L799" href="source/net/ipv4/inet_diag.c#L799">799</a>         return <a href="ident?i=err">err</a>;
<a name="L800" href="source/net/ipv4/inet_diag.c#L800">800</a> }
<a name="L801" href="source/net/ipv4/inet_diag.c#L801">801</a> 
<a name="L802" href="source/net/ipv4/inet_diag.c#L802">802</a> void <a href="ident?i=inet_diag_dump_icsk">inet_diag_dump_icsk</a>(struct <a href="ident?i=inet_hashinfo">inet_hashinfo</a> *hashinfo, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
<a name="L803" href="source/net/ipv4/inet_diag.c#L803">803</a>                          struct <a href="ident?i=netlink_callback">netlink_callback</a> *<a href="ident?i=cb">cb</a>,
<a name="L804" href="source/net/ipv4/inet_diag.c#L804">804</a>                          const struct <a href="ident?i=inet_diag_req_v2">inet_diag_req_v2</a> *<a href="ident?i=r">r</a>, struct <a href="ident?i=nlattr">nlattr</a> *<a href="ident?i=bc">bc</a>)
<a name="L805" href="source/net/ipv4/inet_diag.c#L805">805</a> {
<a name="L806" href="source/net/ipv4/inet_diag.c#L806">806</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=sock_net">sock_net</a>(<a href="ident?i=skb">skb</a>-&gt;sk);
<a name="L807" href="source/net/ipv4/inet_diag.c#L807">807</a>         int <a href="ident?i=i">i</a>, <a href="ident?i=num">num</a>, s_i, s_num;
<a name="L808" href="source/net/ipv4/inet_diag.c#L808">808</a> 
<a name="L809" href="source/net/ipv4/inet_diag.c#L809">809</a>         s_i = <a href="ident?i=cb">cb</a>-&gt;<a href="ident?i=args">args</a>[1];
<a name="L810" href="source/net/ipv4/inet_diag.c#L810">810</a>         s_num = <a href="ident?i=num">num</a> = <a href="ident?i=cb">cb</a>-&gt;<a href="ident?i=args">args</a>[2];
<a name="L811" href="source/net/ipv4/inet_diag.c#L811">811</a> 
<a name="L812" href="source/net/ipv4/inet_diag.c#L812">812</a>         if (<a href="ident?i=cb">cb</a>-&gt;<a href="ident?i=args">args</a>[0] == 0) {
<a name="L813" href="source/net/ipv4/inet_diag.c#L813">813</a>                 if (!(<a href="ident?i=r">r</a>-&gt;idiag_states &amp; (TCPF_LISTEN | TCPF_SYN_RECV)))
<a name="L814" href="source/net/ipv4/inet_diag.c#L814">814</a>                         goto skip_listen_ht;
<a name="L815" href="source/net/ipv4/inet_diag.c#L815">815</a> 
<a name="L816" href="source/net/ipv4/inet_diag.c#L816">816</a>                 for (<a href="ident?i=i">i</a> = s_i; <a href="ident?i=i">i</a> &lt; <a href="ident?i=INET_LHTABLE_SIZE">INET_LHTABLE_SIZE</a>; <a href="ident?i=i">i</a>++) {
<a name="L817" href="source/net/ipv4/inet_diag.c#L817">817</a>                         struct <a href="ident?i=inet_listen_hashbucket">inet_listen_hashbucket</a> *ilb;
<a name="L818" href="source/net/ipv4/inet_diag.c#L818">818</a>                         struct <a href="ident?i=hlist_nulls_node">hlist_nulls_node</a> *<a href="ident?i=node">node</a>;
<a name="L819" href="source/net/ipv4/inet_diag.c#L819">819</a>                         struct <a href="ident?i=sock">sock</a> *sk;
<a name="L820" href="source/net/ipv4/inet_diag.c#L820">820</a> 
<a name="L821" href="source/net/ipv4/inet_diag.c#L821">821</a>                         <a href="ident?i=num">num</a> = 0;
<a name="L822" href="source/net/ipv4/inet_diag.c#L822">822</a>                         ilb = &amp;hashinfo-&gt;listening_hash[<a href="ident?i=i">i</a>];
<a name="L823" href="source/net/ipv4/inet_diag.c#L823">823</a>                         <a href="ident?i=spin_lock_bh">spin_lock_bh</a>(&amp;ilb-&gt;<a href="ident?i=lock">lock</a>);
<a name="L824" href="source/net/ipv4/inet_diag.c#L824">824</a>                         <a href="ident?i=sk_nulls_for_each">sk_nulls_for_each</a>(sk, <a href="ident?i=node">node</a>, &amp;ilb-&gt;<a href="ident?i=head">head</a>) {
<a name="L825" href="source/net/ipv4/inet_diag.c#L825">825</a>                                 struct <a href="ident?i=inet_sock">inet_sock</a> *inet = <a href="ident?i=inet_sk">inet_sk</a>(sk);
<a name="L826" href="source/net/ipv4/inet_diag.c#L826">826</a> 
<a name="L827" href="source/net/ipv4/inet_diag.c#L827">827</a>                                 if (!<a href="ident?i=net_eq">net_eq</a>(<a href="ident?i=sock_net">sock_net</a>(sk), <a href="ident?i=net">net</a>))
<a name="L828" href="source/net/ipv4/inet_diag.c#L828">828</a>                                         continue;
<a name="L829" href="source/net/ipv4/inet_diag.c#L829">829</a> 
<a name="L830" href="source/net/ipv4/inet_diag.c#L830">830</a>                                 if (<a href="ident?i=num">num</a> &lt; s_num) {
<a name="L831" href="source/net/ipv4/inet_diag.c#L831">831</a>                                         <a href="ident?i=num">num</a>++;
<a name="L832" href="source/net/ipv4/inet_diag.c#L832">832</a>                                         continue;
<a name="L833" href="source/net/ipv4/inet_diag.c#L833">833</a>                                 }
<a name="L834" href="source/net/ipv4/inet_diag.c#L834">834</a> 
<a name="L835" href="source/net/ipv4/inet_diag.c#L835">835</a>                                 if (<a href="ident?i=r">r</a>-&gt;sdiag_family != <a href="ident?i=AF_UNSPEC">AF_UNSPEC</a> &amp;&amp;
<a name="L836" href="source/net/ipv4/inet_diag.c#L836">836</a>                                     sk-&gt;<a href="ident?i=sk_family">sk_family</a> != <a href="ident?i=r">r</a>-&gt;sdiag_family)
<a name="L837" href="source/net/ipv4/inet_diag.c#L837">837</a>                                         goto next_listen;
<a name="L838" href="source/net/ipv4/inet_diag.c#L838">838</a> 
<a name="L839" href="source/net/ipv4/inet_diag.c#L839">839</a>                                 if (<a href="ident?i=r">r</a>-&gt;<a href="ident?i=id">id</a>.idiag_sport != inet-&gt;inet_sport &amp;&amp;
<a name="L840" href="source/net/ipv4/inet_diag.c#L840">840</a>                                     <a href="ident?i=r">r</a>-&gt;<a href="ident?i=id">id</a>.idiag_sport)
<a name="L841" href="source/net/ipv4/inet_diag.c#L841">841</a>                                         goto next_listen;
<a name="L842" href="source/net/ipv4/inet_diag.c#L842">842</a> 
<a name="L843" href="source/net/ipv4/inet_diag.c#L843">843</a>                                 if (!(<a href="ident?i=r">r</a>-&gt;idiag_states &amp; TCPF_LISTEN) ||
<a name="L844" href="source/net/ipv4/inet_diag.c#L844">844</a>                                     <a href="ident?i=r">r</a>-&gt;<a href="ident?i=id">id</a>.idiag_dport ||
<a name="L845" href="source/net/ipv4/inet_diag.c#L845">845</a>                                     <a href="ident?i=cb">cb</a>-&gt;<a href="ident?i=args">args</a>[3] &gt; 0)
<a name="L846" href="source/net/ipv4/inet_diag.c#L846">846</a>                                         goto syn_recv;
<a name="L847" href="source/net/ipv4/inet_diag.c#L847">847</a> 
<a name="L848" href="source/net/ipv4/inet_diag.c#L848">848</a>                                 if (<a href="ident?i=inet_csk_diag_dump">inet_csk_diag_dump</a>(sk, <a href="ident?i=skb">skb</a>, <a href="ident?i=cb">cb</a>, <a href="ident?i=r">r</a>, <a href="ident?i=bc">bc</a>) &lt; 0) {
<a name="L849" href="source/net/ipv4/inet_diag.c#L849">849</a>                                         <a href="ident?i=spin_unlock_bh">spin_unlock_bh</a>(&amp;ilb-&gt;<a href="ident?i=lock">lock</a>);
<a name="L850" href="source/net/ipv4/inet_diag.c#L850">850</a>                                         goto <a href="ident?i=done">done</a>;
<a name="L851" href="source/net/ipv4/inet_diag.c#L851">851</a>                                 }
<a name="L852" href="source/net/ipv4/inet_diag.c#L852">852</a> 
<a name="L853" href="source/net/ipv4/inet_diag.c#L853">853</a> syn_recv:
<a name="L854" href="source/net/ipv4/inet_diag.c#L854">854</a>                                 if (!(<a href="ident?i=r">r</a>-&gt;idiag_states &amp; TCPF_SYN_RECV))
<a name="L855" href="source/net/ipv4/inet_diag.c#L855">855</a>                                         goto next_listen;
<a name="L856" href="source/net/ipv4/inet_diag.c#L856">856</a> 
<a name="L857" href="source/net/ipv4/inet_diag.c#L857">857</a>                                 if (<a href="ident?i=inet_diag_dump_reqs">inet_diag_dump_reqs</a>(<a href="ident?i=skb">skb</a>, sk, <a href="ident?i=cb">cb</a>, <a href="ident?i=r">r</a>, <a href="ident?i=bc">bc</a>) &lt; 0) {
<a name="L858" href="source/net/ipv4/inet_diag.c#L858">858</a>                                         <a href="ident?i=spin_unlock_bh">spin_unlock_bh</a>(&amp;ilb-&gt;<a href="ident?i=lock">lock</a>);
<a name="L859" href="source/net/ipv4/inet_diag.c#L859">859</a>                                         goto <a href="ident?i=done">done</a>;
<a name="L860" href="source/net/ipv4/inet_diag.c#L860">860</a>                                 }
<a name="L861" href="source/net/ipv4/inet_diag.c#L861">861</a> 
<a name="L862" href="source/net/ipv4/inet_diag.c#L862">862</a> next_listen:
<a name="L863" href="source/net/ipv4/inet_diag.c#L863">863</a>                                 <a href="ident?i=cb">cb</a>-&gt;<a href="ident?i=args">args</a>[3] = 0;
<a name="L864" href="source/net/ipv4/inet_diag.c#L864">864</a>                                 <a href="ident?i=cb">cb</a>-&gt;<a href="ident?i=args">args</a>[4] = 0;
<a name="L865" href="source/net/ipv4/inet_diag.c#L865">865</a>                                 ++<a href="ident?i=num">num</a>;
<a name="L866" href="source/net/ipv4/inet_diag.c#L866">866</a>                         }
<a name="L867" href="source/net/ipv4/inet_diag.c#L867">867</a>                         <a href="ident?i=spin_unlock_bh">spin_unlock_bh</a>(&amp;ilb-&gt;<a href="ident?i=lock">lock</a>);
<a name="L868" href="source/net/ipv4/inet_diag.c#L868">868</a> 
<a name="L869" href="source/net/ipv4/inet_diag.c#L869">869</a>                         s_num = 0;
<a name="L870" href="source/net/ipv4/inet_diag.c#L870">870</a>                         <a href="ident?i=cb">cb</a>-&gt;<a href="ident?i=args">args</a>[3] = 0;
<a name="L871" href="source/net/ipv4/inet_diag.c#L871">871</a>                         <a href="ident?i=cb">cb</a>-&gt;<a href="ident?i=args">args</a>[4] = 0;
<a name="L872" href="source/net/ipv4/inet_diag.c#L872">872</a>                 }
<a name="L873" href="source/net/ipv4/inet_diag.c#L873">873</a> skip_listen_ht:
<a name="L874" href="source/net/ipv4/inet_diag.c#L874">874</a>                 <a href="ident?i=cb">cb</a>-&gt;<a href="ident?i=args">args</a>[0] = 1;
<a name="L875" href="source/net/ipv4/inet_diag.c#L875">875</a>                 s_i = <a href="ident?i=num">num</a> = s_num = 0;
<a name="L876" href="source/net/ipv4/inet_diag.c#L876">876</a>         }
<a name="L877" href="source/net/ipv4/inet_diag.c#L877">877</a> 
<a name="L878" href="source/net/ipv4/inet_diag.c#L878">878</a>         if (!(<a href="ident?i=r">r</a>-&gt;idiag_states &amp; ~(TCPF_LISTEN | TCPF_SYN_RECV)))
<a name="L879" href="source/net/ipv4/inet_diag.c#L879">879</a>                 goto <a href="ident?i=out">out</a>;
<a name="L880" href="source/net/ipv4/inet_diag.c#L880">880</a> 
<a name="L881" href="source/net/ipv4/inet_diag.c#L881">881</a>         for (<a href="ident?i=i">i</a> = s_i; <a href="ident?i=i">i</a> &lt;= hashinfo-&gt;ehash_mask; <a href="ident?i=i">i</a>++) {
<a name="L882" href="source/net/ipv4/inet_diag.c#L882">882</a>                 struct <a href="ident?i=inet_ehash_bucket">inet_ehash_bucket</a> *<a href="ident?i=head">head</a> = &amp;hashinfo-&gt;ehash[<a href="ident?i=i">i</a>];
<a name="L883" href="source/net/ipv4/inet_diag.c#L883">883</a>                 <a href="ident?i=spinlock_t">spinlock_t</a> *<a href="ident?i=lock">lock</a> = <a href="ident?i=inet_ehash_lockp">inet_ehash_lockp</a>(hashinfo, <a href="ident?i=i">i</a>);
<a name="L884" href="source/net/ipv4/inet_diag.c#L884">884</a>                 struct <a href="ident?i=hlist_nulls_node">hlist_nulls_node</a> *<a href="ident?i=node">node</a>;
<a name="L885" href="source/net/ipv4/inet_diag.c#L885">885</a>                 struct <a href="ident?i=sock">sock</a> *sk;
<a name="L886" href="source/net/ipv4/inet_diag.c#L886">886</a> 
<a name="L887" href="source/net/ipv4/inet_diag.c#L887">887</a>                 <a href="ident?i=num">num</a> = 0;
<a name="L888" href="source/net/ipv4/inet_diag.c#L888">888</a> 
<a name="L889" href="source/net/ipv4/inet_diag.c#L889">889</a>                 if (<a href="ident?i=hlist_nulls_empty">hlist_nulls_empty</a>(&amp;<a href="ident?i=head">head</a>-&gt;<a href="ident?i=chain">chain</a>))
<a name="L890" href="source/net/ipv4/inet_diag.c#L890">890</a>                         continue;
<a name="L891" href="source/net/ipv4/inet_diag.c#L891">891</a> 
<a name="L892" href="source/net/ipv4/inet_diag.c#L892">892</a>                 if (<a href="ident?i=i">i</a> &gt; s_i)
<a name="L893" href="source/net/ipv4/inet_diag.c#L893">893</a>                         s_num = 0;
<a name="L894" href="source/net/ipv4/inet_diag.c#L894">894</a> 
<a name="L895" href="source/net/ipv4/inet_diag.c#L895">895</a>                 <a href="ident?i=spin_lock_bh">spin_lock_bh</a>(<a href="ident?i=lock">lock</a>);
<a name="L896" href="source/net/ipv4/inet_diag.c#L896">896</a>                 <a href="ident?i=sk_nulls_for_each">sk_nulls_for_each</a>(sk, <a href="ident?i=node">node</a>, &amp;<a href="ident?i=head">head</a>-&gt;<a href="ident?i=chain">chain</a>) {
<a name="L897" href="source/net/ipv4/inet_diag.c#L897">897</a>                         int <a href="ident?i=state">state</a>, <a href="ident?i=res">res</a>;
<a name="L898" href="source/net/ipv4/inet_diag.c#L898">898</a> 
<a name="L899" href="source/net/ipv4/inet_diag.c#L899">899</a>                         if (!<a href="ident?i=net_eq">net_eq</a>(<a href="ident?i=sock_net">sock_net</a>(sk), <a href="ident?i=net">net</a>))
<a name="L900" href="source/net/ipv4/inet_diag.c#L900">900</a>                                 continue;
<a name="L901" href="source/net/ipv4/inet_diag.c#L901">901</a>                         if (<a href="ident?i=num">num</a> &lt; s_num)
<a name="L902" href="source/net/ipv4/inet_diag.c#L902">902</a>                                 goto next_normal;
<a name="L903" href="source/net/ipv4/inet_diag.c#L903">903</a>                         <a href="ident?i=state">state</a> = (sk-&gt;<a href="ident?i=sk_state">sk_state</a> == TCP_TIME_WAIT) ?
<a name="L904" href="source/net/ipv4/inet_diag.c#L904">904</a>                                 <a href="ident?i=inet_twsk">inet_twsk</a>(sk)-&gt;tw_substate : sk-&gt;<a href="ident?i=sk_state">sk_state</a>;
<a name="L905" href="source/net/ipv4/inet_diag.c#L905">905</a>                         if (!(<a href="ident?i=r">r</a>-&gt;idiag_states &amp; (1 &lt;&lt; <a href="ident?i=state">state</a>)))
<a name="L906" href="source/net/ipv4/inet_diag.c#L906">906</a>                                 goto next_normal;
<a name="L907" href="source/net/ipv4/inet_diag.c#L907">907</a>                         if (<a href="ident?i=r">r</a>-&gt;sdiag_family != <a href="ident?i=AF_UNSPEC">AF_UNSPEC</a> &amp;&amp;
<a name="L908" href="source/net/ipv4/inet_diag.c#L908">908</a>                             sk-&gt;<a href="ident?i=sk_family">sk_family</a> != <a href="ident?i=r">r</a>-&gt;sdiag_family)
<a name="L909" href="source/net/ipv4/inet_diag.c#L909">909</a>                                 goto next_normal;
<a name="L910" href="source/net/ipv4/inet_diag.c#L910">910</a>                         if (<a href="ident?i=r">r</a>-&gt;<a href="ident?i=id">id</a>.idiag_sport != <a href="ident?i=htons">htons</a>(sk-&gt;<a href="ident?i=sk_num">sk_num</a>) &amp;&amp;
<a name="L911" href="source/net/ipv4/inet_diag.c#L911">911</a>                             <a href="ident?i=r">r</a>-&gt;<a href="ident?i=id">id</a>.idiag_sport)
<a name="L912" href="source/net/ipv4/inet_diag.c#L912">912</a>                                 goto next_normal;
<a name="L913" href="source/net/ipv4/inet_diag.c#L913">913</a>                         if (<a href="ident?i=r">r</a>-&gt;<a href="ident?i=id">id</a>.idiag_dport != sk-&gt;<a href="ident?i=sk_dport">sk_dport</a> &amp;&amp;
<a name="L914" href="source/net/ipv4/inet_diag.c#L914">914</a>                             <a href="ident?i=r">r</a>-&gt;<a href="ident?i=id">id</a>.idiag_dport)
<a name="L915" href="source/net/ipv4/inet_diag.c#L915">915</a>                                 goto next_normal;
<a name="L916" href="source/net/ipv4/inet_diag.c#L916">916</a>                         <a href="ident?i=twsk_build_assert">twsk_build_assert</a>();
<a name="L917" href="source/net/ipv4/inet_diag.c#L917">917</a> 
<a name="L918" href="source/net/ipv4/inet_diag.c#L918">918</a>                         if (!<a href="ident?i=inet_diag_bc_sk">inet_diag_bc_sk</a>(<a href="ident?i=bc">bc</a>, sk))
<a name="L919" href="source/net/ipv4/inet_diag.c#L919">919</a>                                 goto next_normal;
<a name="L920" href="source/net/ipv4/inet_diag.c#L920">920</a> 
<a name="L921" href="source/net/ipv4/inet_diag.c#L921">921</a>                         <a href="ident?i=res">res</a> = <a href="ident?i=sk_diag_fill">sk_diag_fill</a>(sk, <a href="ident?i=skb">skb</a>, <a href="ident?i=r">r</a>,
<a name="L922" href="source/net/ipv4/inet_diag.c#L922">922</a>                                            <a href="ident?i=sk_user_ns">sk_user_ns</a>(<a href="ident?i=NETLINK_CB">NETLINK_CB</a>(<a href="ident?i=cb">cb</a>-&gt;<a href="ident?i=skb">skb</a>).sk),
<a name="L923" href="source/net/ipv4/inet_diag.c#L923">923</a>                                            <a href="ident?i=NETLINK_CB">NETLINK_CB</a>(<a href="ident?i=cb">cb</a>-&gt;<a href="ident?i=skb">skb</a>).portid,
<a name="L924" href="source/net/ipv4/inet_diag.c#L924">924</a>                                            <a href="ident?i=cb">cb</a>-&gt;nlh-&gt;nlmsg_seq, <a href="ident?i=NLM_F_MULTI">NLM_F_MULTI</a>,
<a name="L925" href="source/net/ipv4/inet_diag.c#L925">925</a>                                            <a href="ident?i=cb">cb</a>-&gt;nlh);
<a name="L926" href="source/net/ipv4/inet_diag.c#L926">926</a>                         if (<a href="ident?i=res">res</a> &lt; 0) {
<a name="L927" href="source/net/ipv4/inet_diag.c#L927">927</a>                                 <a href="ident?i=spin_unlock_bh">spin_unlock_bh</a>(<a href="ident?i=lock">lock</a>);
<a name="L928" href="source/net/ipv4/inet_diag.c#L928">928</a>                                 goto <a href="ident?i=done">done</a>;
<a name="L929" href="source/net/ipv4/inet_diag.c#L929">929</a>                         }
<a name="L930" href="source/net/ipv4/inet_diag.c#L930">930</a> next_normal:
<a name="L931" href="source/net/ipv4/inet_diag.c#L931">931</a>                         ++<a href="ident?i=num">num</a>;
<a name="L932" href="source/net/ipv4/inet_diag.c#L932">932</a>                 }
<a name="L933" href="source/net/ipv4/inet_diag.c#L933">933</a> 
<a name="L934" href="source/net/ipv4/inet_diag.c#L934">934</a>                 <a href="ident?i=spin_unlock_bh">spin_unlock_bh</a>(<a href="ident?i=lock">lock</a>);
<a name="L935" href="source/net/ipv4/inet_diag.c#L935">935</a>         }
<a name="L936" href="source/net/ipv4/inet_diag.c#L936">936</a> 
<a name="L937" href="source/net/ipv4/inet_diag.c#L937">937</a> <a href="ident?i=done">done</a>:
<a name="L938" href="source/net/ipv4/inet_diag.c#L938">938</a>         <a href="ident?i=cb">cb</a>-&gt;<a href="ident?i=args">args</a>[1] = <a href="ident?i=i">i</a>;
<a name="L939" href="source/net/ipv4/inet_diag.c#L939">939</a>         <a href="ident?i=cb">cb</a>-&gt;<a href="ident?i=args">args</a>[2] = <a href="ident?i=num">num</a>;
<a name="L940" href="source/net/ipv4/inet_diag.c#L940">940</a> <a href="ident?i=out">out</a>:
<a name="L941" href="source/net/ipv4/inet_diag.c#L941">941</a>         ;
<a name="L942" href="source/net/ipv4/inet_diag.c#L942">942</a> }
<a name="L943" href="source/net/ipv4/inet_diag.c#L943">943</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=inet_diag_dump_icsk">inet_diag_dump_icsk</a>);
<a name="L944" href="source/net/ipv4/inet_diag.c#L944">944</a> 
<a name="L945" href="source/net/ipv4/inet_diag.c#L945">945</a> static int <a href="ident?i=__inet_diag_dump">__inet_diag_dump</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, struct <a href="ident?i=netlink_callback">netlink_callback</a> *<a href="ident?i=cb">cb</a>,
<a name="L946" href="source/net/ipv4/inet_diag.c#L946">946</a>                             const struct <a href="ident?i=inet_diag_req_v2">inet_diag_req_v2</a> *<a href="ident?i=r">r</a>,
<a name="L947" href="source/net/ipv4/inet_diag.c#L947">947</a>                             struct <a href="ident?i=nlattr">nlattr</a> *<a href="ident?i=bc">bc</a>)
<a name="L948" href="source/net/ipv4/inet_diag.c#L948">948</a> {
<a name="L949" href="source/net/ipv4/inet_diag.c#L949">949</a>         const struct <a href="ident?i=inet_diag_handler">inet_diag_handler</a> *<a href="ident?i=handler">handler</a>;
<a name="L950" href="source/net/ipv4/inet_diag.c#L950">950</a>         int <a href="ident?i=err">err</a> = 0;
<a name="L951" href="source/net/ipv4/inet_diag.c#L951">951</a> 
<a name="L952" href="source/net/ipv4/inet_diag.c#L952">952</a>         <a href="ident?i=handler">handler</a> = <a href="ident?i=inet_diag_lock_handler">inet_diag_lock_handler</a>(<a href="ident?i=r">r</a>-&gt;sdiag_protocol);
<a name="L953" href="source/net/ipv4/inet_diag.c#L953">953</a>         if (!<a href="ident?i=IS_ERR">IS_ERR</a>(<a href="ident?i=handler">handler</a>))
<a name="L954" href="source/net/ipv4/inet_diag.c#L954">954</a>                 <a href="ident?i=handler">handler</a>-&gt;<a href="ident?i=dump">dump</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=cb">cb</a>, <a href="ident?i=r">r</a>, <a href="ident?i=bc">bc</a>);
<a name="L955" href="source/net/ipv4/inet_diag.c#L955">955</a>         else
<a name="L956" href="source/net/ipv4/inet_diag.c#L956">956</a>                 <a href="ident?i=err">err</a> = <a href="ident?i=PTR_ERR">PTR_ERR</a>(<a href="ident?i=handler">handler</a>);
<a name="L957" href="source/net/ipv4/inet_diag.c#L957">957</a>         <a href="ident?i=inet_diag_unlock_handler">inet_diag_unlock_handler</a>(<a href="ident?i=handler">handler</a>);
<a name="L958" href="source/net/ipv4/inet_diag.c#L958">958</a> 
<a name="L959" href="source/net/ipv4/inet_diag.c#L959">959</a>         return <a href="ident?i=err">err</a> ? : <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a>;
<a name="L960" href="source/net/ipv4/inet_diag.c#L960">960</a> }
<a name="L961" href="source/net/ipv4/inet_diag.c#L961">961</a> 
<a name="L962" href="source/net/ipv4/inet_diag.c#L962">962</a> static int <a href="ident?i=inet_diag_dump">inet_diag_dump</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, struct <a href="ident?i=netlink_callback">netlink_callback</a> *<a href="ident?i=cb">cb</a>)
<a name="L963" href="source/net/ipv4/inet_diag.c#L963">963</a> {
<a name="L964" href="source/net/ipv4/inet_diag.c#L964">964</a>         int hdrlen = sizeof(struct <a href="ident?i=inet_diag_req_v2">inet_diag_req_v2</a>);
<a name="L965" href="source/net/ipv4/inet_diag.c#L965">965</a>         struct <a href="ident?i=nlattr">nlattr</a> *<a href="ident?i=bc">bc</a> = <a href="ident?i=NULL">NULL</a>;
<a name="L966" href="source/net/ipv4/inet_diag.c#L966">966</a> 
<a name="L967" href="source/net/ipv4/inet_diag.c#L967">967</a>         if (<a href="ident?i=nlmsg_attrlen">nlmsg_attrlen</a>(<a href="ident?i=cb">cb</a>-&gt;nlh, hdrlen))
<a name="L968" href="source/net/ipv4/inet_diag.c#L968">968</a>                 <a href="ident?i=bc">bc</a> = <a href="ident?i=nlmsg_find_attr">nlmsg_find_attr</a>(<a href="ident?i=cb">cb</a>-&gt;nlh, hdrlen, INET_DIAG_REQ_BYTECODE);
<a name="L969" href="source/net/ipv4/inet_diag.c#L969">969</a> 
<a name="L970" href="source/net/ipv4/inet_diag.c#L970">970</a>         return <a href="ident?i=__inet_diag_dump">__inet_diag_dump</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=cb">cb</a>, <a href="ident?i=nlmsg_data">nlmsg_data</a>(<a href="ident?i=cb">cb</a>-&gt;nlh), <a href="ident?i=bc">bc</a>);
<a name="L971" href="source/net/ipv4/inet_diag.c#L971">971</a> }
<a name="L972" href="source/net/ipv4/inet_diag.c#L972">972</a> 
<a name="L973" href="source/net/ipv4/inet_diag.c#L973">973</a> static int <a href="ident?i=inet_diag_type2proto">inet_diag_type2proto</a>(int <a href="ident?i=type">type</a>)
<a name="L974" href="source/net/ipv4/inet_diag.c#L974">974</a> {
<a name="L975" href="source/net/ipv4/inet_diag.c#L975">975</a>         switch (<a href="ident?i=type">type</a>) {
<a name="L976" href="source/net/ipv4/inet_diag.c#L976">976</a>         case <a href="ident?i=TCPDIAG_GETSOCK">TCPDIAG_GETSOCK</a>:
<a name="L977" href="source/net/ipv4/inet_diag.c#L977">977</a>                 return <a href="ident?i=IPPROTO_TCP">IPPROTO_TCP</a>;
<a name="L978" href="source/net/ipv4/inet_diag.c#L978">978</a>         case <a href="ident?i=DCCPDIAG_GETSOCK">DCCPDIAG_GETSOCK</a>:
<a name="L979" href="source/net/ipv4/inet_diag.c#L979">979</a>                 return <a href="ident?i=IPPROTO_DCCP">IPPROTO_DCCP</a>;
<a name="L980" href="source/net/ipv4/inet_diag.c#L980">980</a>         default:
<a name="L981" href="source/net/ipv4/inet_diag.c#L981">981</a>                 return 0;
<a name="L982" href="source/net/ipv4/inet_diag.c#L982">982</a>         }
<a name="L983" href="source/net/ipv4/inet_diag.c#L983">983</a> }
<a name="L984" href="source/net/ipv4/inet_diag.c#L984">984</a> 
<a name="L985" href="source/net/ipv4/inet_diag.c#L985">985</a> static int <a href="ident?i=inet_diag_dump_compat">inet_diag_dump_compat</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
<a name="L986" href="source/net/ipv4/inet_diag.c#L986">986</a>                                  struct <a href="ident?i=netlink_callback">netlink_callback</a> *<a href="ident?i=cb">cb</a>)
<a name="L987" href="source/net/ipv4/inet_diag.c#L987">987</a> {
<a name="L988" href="source/net/ipv4/inet_diag.c#L988">988</a>         struct <a href="ident?i=inet_diag_req">inet_diag_req</a> *<a href="ident?i=rc">rc</a> = <a href="ident?i=nlmsg_data">nlmsg_data</a>(<a href="ident?i=cb">cb</a>-&gt;nlh);
<a name="L989" href="source/net/ipv4/inet_diag.c#L989">989</a>         int hdrlen = sizeof(struct <a href="ident?i=inet_diag_req">inet_diag_req</a>);
<a name="L990" href="source/net/ipv4/inet_diag.c#L990">990</a>         struct <a href="ident?i=inet_diag_req_v2">inet_diag_req_v2</a> <a href="ident?i=req">req</a>;
<a name="L991" href="source/net/ipv4/inet_diag.c#L991">991</a>         struct <a href="ident?i=nlattr">nlattr</a> *<a href="ident?i=bc">bc</a> = <a href="ident?i=NULL">NULL</a>;
<a name="L992" href="source/net/ipv4/inet_diag.c#L992">992</a> 
<a name="L993" href="source/net/ipv4/inet_diag.c#L993">993</a>         <a href="ident?i=req">req</a>.sdiag_family = <a href="ident?i=AF_UNSPEC">AF_UNSPEC</a>; <b><i>/* compatibility */</i></b>
<a name="L994" href="source/net/ipv4/inet_diag.c#L994">994</a>         <a href="ident?i=req">req</a>.sdiag_protocol = <a href="ident?i=inet_diag_type2proto">inet_diag_type2proto</a>(<a href="ident?i=cb">cb</a>-&gt;nlh-&gt;nlmsg_type);
<a name="L995" href="source/net/ipv4/inet_diag.c#L995">995</a>         <a href="ident?i=req">req</a>.idiag_ext = <a href="ident?i=rc">rc</a>-&gt;idiag_ext;
<a name="L996" href="source/net/ipv4/inet_diag.c#L996">996</a>         <a href="ident?i=req">req</a>.idiag_states = <a href="ident?i=rc">rc</a>-&gt;idiag_states;
<a name="L997" href="source/net/ipv4/inet_diag.c#L997">997</a>         <a href="ident?i=req">req</a>.<a href="ident?i=id">id</a> = <a href="ident?i=rc">rc</a>-&gt;<a href="ident?i=id">id</a>;
<a name="L998" href="source/net/ipv4/inet_diag.c#L998">998</a> 
<a name="L999" href="source/net/ipv4/inet_diag.c#L999">999</a>         if (<a href="ident?i=nlmsg_attrlen">nlmsg_attrlen</a>(<a href="ident?i=cb">cb</a>-&gt;nlh, hdrlen))
<a name="L1000" href="source/net/ipv4/inet_diag.c#L1000">1000</a>                 <a href="ident?i=bc">bc</a> = <a href="ident?i=nlmsg_find_attr">nlmsg_find_attr</a>(<a href="ident?i=cb">cb</a>-&gt;nlh, hdrlen, INET_DIAG_REQ_BYTECODE);
<a name="L1001" href="source/net/ipv4/inet_diag.c#L1001">1001</a> 
<a name="L1002" href="source/net/ipv4/inet_diag.c#L1002">1002</a>         return <a href="ident?i=__inet_diag_dump">__inet_diag_dump</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=cb">cb</a>, &amp;<a href="ident?i=req">req</a>, <a href="ident?i=bc">bc</a>);
<a name="L1003" href="source/net/ipv4/inet_diag.c#L1003">1003</a> }
<a name="L1004" href="source/net/ipv4/inet_diag.c#L1004">1004</a> 
<a name="L1005" href="source/net/ipv4/inet_diag.c#L1005">1005</a> static int <a href="ident?i=inet_diag_get_exact_compat">inet_diag_get_exact_compat</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *in_skb,
<a name="L1006" href="source/net/ipv4/inet_diag.c#L1006">1006</a>                                       const struct <a href="ident?i=nlmsghdr">nlmsghdr</a> *nlh)
<a name="L1007" href="source/net/ipv4/inet_diag.c#L1007">1007</a> {
<a name="L1008" href="source/net/ipv4/inet_diag.c#L1008">1008</a>         struct <a href="ident?i=inet_diag_req">inet_diag_req</a> *<a href="ident?i=rc">rc</a> = <a href="ident?i=nlmsg_data">nlmsg_data</a>(nlh);
<a name="L1009" href="source/net/ipv4/inet_diag.c#L1009">1009</a>         struct <a href="ident?i=inet_diag_req_v2">inet_diag_req_v2</a> <a href="ident?i=req">req</a>;
<a name="L1010" href="source/net/ipv4/inet_diag.c#L1010">1010</a> 
<a name="L1011" href="source/net/ipv4/inet_diag.c#L1011">1011</a>         <a href="ident?i=req">req</a>.sdiag_family = <a href="ident?i=rc">rc</a>-&gt;idiag_family;
<a name="L1012" href="source/net/ipv4/inet_diag.c#L1012">1012</a>         <a href="ident?i=req">req</a>.sdiag_protocol = <a href="ident?i=inet_diag_type2proto">inet_diag_type2proto</a>(nlh-&gt;nlmsg_type);
<a name="L1013" href="source/net/ipv4/inet_diag.c#L1013">1013</a>         <a href="ident?i=req">req</a>.idiag_ext = <a href="ident?i=rc">rc</a>-&gt;idiag_ext;
<a name="L1014" href="source/net/ipv4/inet_diag.c#L1014">1014</a>         <a href="ident?i=req">req</a>.idiag_states = <a href="ident?i=rc">rc</a>-&gt;idiag_states;
<a name="L1015" href="source/net/ipv4/inet_diag.c#L1015">1015</a>         <a href="ident?i=req">req</a>.<a href="ident?i=id">id</a> = <a href="ident?i=rc">rc</a>-&gt;<a href="ident?i=id">id</a>;
<a name="L1016" href="source/net/ipv4/inet_diag.c#L1016">1016</a> 
<a name="L1017" href="source/net/ipv4/inet_diag.c#L1017">1017</a>         return <a href="ident?i=inet_diag_get_exact">inet_diag_get_exact</a>(in_skb, nlh, &amp;<a href="ident?i=req">req</a>);
<a name="L1018" href="source/net/ipv4/inet_diag.c#L1018">1018</a> }
<a name="L1019" href="source/net/ipv4/inet_diag.c#L1019">1019</a> 
<a name="L1020" href="source/net/ipv4/inet_diag.c#L1020">1020</a> static int <a href="ident?i=inet_diag_rcv_msg_compat">inet_diag_rcv_msg_compat</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, struct <a href="ident?i=nlmsghdr">nlmsghdr</a> *nlh)
<a name="L1021" href="source/net/ipv4/inet_diag.c#L1021">1021</a> {
<a name="L1022" href="source/net/ipv4/inet_diag.c#L1022">1022</a>         int hdrlen = sizeof(struct <a href="ident?i=inet_diag_req">inet_diag_req</a>);
<a name="L1023" href="source/net/ipv4/inet_diag.c#L1023">1023</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=sock_net">sock_net</a>(<a href="ident?i=skb">skb</a>-&gt;sk);
<a name="L1024" href="source/net/ipv4/inet_diag.c#L1024">1024</a> 
<a name="L1025" href="source/net/ipv4/inet_diag.c#L1025">1025</a>         if (nlh-&gt;nlmsg_type &gt;= <a href="ident?i=INET_DIAG_GETSOCK_MAX">INET_DIAG_GETSOCK_MAX</a> ||
<a name="L1026" href="source/net/ipv4/inet_diag.c#L1026">1026</a>             <a href="ident?i=nlmsg_len">nlmsg_len</a>(nlh) &lt; hdrlen)
<a name="L1027" href="source/net/ipv4/inet_diag.c#L1027">1027</a>                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L1028" href="source/net/ipv4/inet_diag.c#L1028">1028</a> 
<a name="L1029" href="source/net/ipv4/inet_diag.c#L1029">1029</a>         if (nlh-&gt;nlmsg_flags &amp; <a href="ident?i=NLM_F_DUMP">NLM_F_DUMP</a>) {
<a name="L1030" href="source/net/ipv4/inet_diag.c#L1030">1030</a>                 if (<a href="ident?i=nlmsg_attrlen">nlmsg_attrlen</a>(nlh, hdrlen)) {
<a name="L1031" href="source/net/ipv4/inet_diag.c#L1031">1031</a>                         struct <a href="ident?i=nlattr">nlattr</a> *<a href="ident?i=attr">attr</a>;
<a name="L1032" href="source/net/ipv4/inet_diag.c#L1032">1032</a> 
<a name="L1033" href="source/net/ipv4/inet_diag.c#L1033">1033</a>                         <a href="ident?i=attr">attr</a> = <a href="ident?i=nlmsg_find_attr">nlmsg_find_attr</a>(nlh, hdrlen,
<a name="L1034" href="source/net/ipv4/inet_diag.c#L1034">1034</a>                                                INET_DIAG_REQ_BYTECODE);
<a name="L1035" href="source/net/ipv4/inet_diag.c#L1035">1035</a>                         if (!<a href="ident?i=attr">attr</a> ||
<a name="L1036" href="source/net/ipv4/inet_diag.c#L1036">1036</a>                             <a href="ident?i=nla_len">nla_len</a>(<a href="ident?i=attr">attr</a>) &lt; sizeof(struct <a href="ident?i=inet_diag_bc_op">inet_diag_bc_op</a>) ||
<a name="L1037" href="source/net/ipv4/inet_diag.c#L1037">1037</a>                             <a href="ident?i=inet_diag_bc_audit">inet_diag_bc_audit</a>(<a href="ident?i=nla_data">nla_data</a>(<a href="ident?i=attr">attr</a>), <a href="ident?i=nla_len">nla_len</a>(<a href="ident?i=attr">attr</a>)))
<a name="L1038" href="source/net/ipv4/inet_diag.c#L1038">1038</a>                                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L1039" href="source/net/ipv4/inet_diag.c#L1039">1039</a>                 }
<a name="L1040" href="source/net/ipv4/inet_diag.c#L1040">1040</a>                 {
<a name="L1041" href="source/net/ipv4/inet_diag.c#L1041">1041</a>                         struct <a href="ident?i=netlink_dump_control">netlink_dump_control</a> <a href="ident?i=c">c</a> = {
<a name="L1042" href="source/net/ipv4/inet_diag.c#L1042">1042</a>                                 .<a href="ident?i=dump">dump</a> = <a href="ident?i=inet_diag_dump_compat">inet_diag_dump_compat</a>,
<a name="L1043" href="source/net/ipv4/inet_diag.c#L1043">1043</a>                         };
<a name="L1044" href="source/net/ipv4/inet_diag.c#L1044">1044</a>                         return <a href="ident?i=netlink_dump_start">netlink_dump_start</a>(<a href="ident?i=net">net</a>-&gt;diag_nlsk, <a href="ident?i=skb">skb</a>, nlh, &amp;<a href="ident?i=c">c</a>);
<a name="L1045" href="source/net/ipv4/inet_diag.c#L1045">1045</a>                 }
<a name="L1046" href="source/net/ipv4/inet_diag.c#L1046">1046</a>         }
<a name="L1047" href="source/net/ipv4/inet_diag.c#L1047">1047</a> 
<a name="L1048" href="source/net/ipv4/inet_diag.c#L1048">1048</a>         return <a href="ident?i=inet_diag_get_exact_compat">inet_diag_get_exact_compat</a>(<a href="ident?i=skb">skb</a>, nlh);
<a name="L1049" href="source/net/ipv4/inet_diag.c#L1049">1049</a> }
<a name="L1050" href="source/net/ipv4/inet_diag.c#L1050">1050</a> 
<a name="L1051" href="source/net/ipv4/inet_diag.c#L1051">1051</a> static int <a href="ident?i=inet_diag_handler_dump">inet_diag_handler_dump</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, struct <a href="ident?i=nlmsghdr">nlmsghdr</a> *<a href="ident?i=h">h</a>)
<a name="L1052" href="source/net/ipv4/inet_diag.c#L1052">1052</a> {
<a name="L1053" href="source/net/ipv4/inet_diag.c#L1053">1053</a>         int hdrlen = sizeof(struct <a href="ident?i=inet_diag_req_v2">inet_diag_req_v2</a>);
<a name="L1054" href="source/net/ipv4/inet_diag.c#L1054">1054</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=sock_net">sock_net</a>(<a href="ident?i=skb">skb</a>-&gt;sk);
<a name="L1055" href="source/net/ipv4/inet_diag.c#L1055">1055</a> 
<a name="L1056" href="source/net/ipv4/inet_diag.c#L1056">1056</a>         if (<a href="ident?i=nlmsg_len">nlmsg_len</a>(<a href="ident?i=h">h</a>) &lt; hdrlen)
<a name="L1057" href="source/net/ipv4/inet_diag.c#L1057">1057</a>                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L1058" href="source/net/ipv4/inet_diag.c#L1058">1058</a> 
<a name="L1059" href="source/net/ipv4/inet_diag.c#L1059">1059</a>         if (<a href="ident?i=h">h</a>-&gt;nlmsg_flags &amp; <a href="ident?i=NLM_F_DUMP">NLM_F_DUMP</a>) {
<a name="L1060" href="source/net/ipv4/inet_diag.c#L1060">1060</a>                 if (<a href="ident?i=nlmsg_attrlen">nlmsg_attrlen</a>(<a href="ident?i=h">h</a>, hdrlen)) {
<a name="L1061" href="source/net/ipv4/inet_diag.c#L1061">1061</a>                         struct <a href="ident?i=nlattr">nlattr</a> *<a href="ident?i=attr">attr</a>;
<a name="L1062" href="source/net/ipv4/inet_diag.c#L1062">1062</a> 
<a name="L1063" href="source/net/ipv4/inet_diag.c#L1063">1063</a>                         <a href="ident?i=attr">attr</a> = <a href="ident?i=nlmsg_find_attr">nlmsg_find_attr</a>(<a href="ident?i=h">h</a>, hdrlen,
<a name="L1064" href="source/net/ipv4/inet_diag.c#L1064">1064</a>                                                INET_DIAG_REQ_BYTECODE);
<a name="L1065" href="source/net/ipv4/inet_diag.c#L1065">1065</a>                         if (!<a href="ident?i=attr">attr</a> ||
<a name="L1066" href="source/net/ipv4/inet_diag.c#L1066">1066</a>                             <a href="ident?i=nla_len">nla_len</a>(<a href="ident?i=attr">attr</a>) &lt; sizeof(struct <a href="ident?i=inet_diag_bc_op">inet_diag_bc_op</a>) ||
<a name="L1067" href="source/net/ipv4/inet_diag.c#L1067">1067</a>                             <a href="ident?i=inet_diag_bc_audit">inet_diag_bc_audit</a>(<a href="ident?i=nla_data">nla_data</a>(<a href="ident?i=attr">attr</a>), <a href="ident?i=nla_len">nla_len</a>(<a href="ident?i=attr">attr</a>)))
<a name="L1068" href="source/net/ipv4/inet_diag.c#L1068">1068</a>                                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L1069" href="source/net/ipv4/inet_diag.c#L1069">1069</a>                 }
<a name="L1070" href="source/net/ipv4/inet_diag.c#L1070">1070</a>                 {
<a name="L1071" href="source/net/ipv4/inet_diag.c#L1071">1071</a>                         struct <a href="ident?i=netlink_dump_control">netlink_dump_control</a> <a href="ident?i=c">c</a> = {
<a name="L1072" href="source/net/ipv4/inet_diag.c#L1072">1072</a>                                 .<a href="ident?i=dump">dump</a> = <a href="ident?i=inet_diag_dump">inet_diag_dump</a>,
<a name="L1073" href="source/net/ipv4/inet_diag.c#L1073">1073</a>                         };
<a name="L1074" href="source/net/ipv4/inet_diag.c#L1074">1074</a>                         return <a href="ident?i=netlink_dump_start">netlink_dump_start</a>(<a href="ident?i=net">net</a>-&gt;diag_nlsk, <a href="ident?i=skb">skb</a>, <a href="ident?i=h">h</a>, &amp;<a href="ident?i=c">c</a>);
<a name="L1075" href="source/net/ipv4/inet_diag.c#L1075">1075</a>                 }
<a name="L1076" href="source/net/ipv4/inet_diag.c#L1076">1076</a>         }
<a name="L1077" href="source/net/ipv4/inet_diag.c#L1077">1077</a> 
<a name="L1078" href="source/net/ipv4/inet_diag.c#L1078">1078</a>         return <a href="ident?i=inet_diag_get_exact">inet_diag_get_exact</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=h">h</a>, <a href="ident?i=nlmsg_data">nlmsg_data</a>(<a href="ident?i=h">h</a>));
<a name="L1079" href="source/net/ipv4/inet_diag.c#L1079">1079</a> }
<a name="L1080" href="source/net/ipv4/inet_diag.c#L1080">1080</a> 
<a name="L1081" href="source/net/ipv4/inet_diag.c#L1081">1081</a> static const struct <a href="ident?i=sock_diag_handler">sock_diag_handler</a> <a href="ident?i=inet_diag_handler">inet_diag_handler</a> = {
<a name="L1082" href="source/net/ipv4/inet_diag.c#L1082">1082</a>         .<a href="ident?i=family">family</a> = <a href="ident?i=AF_INET">AF_INET</a>,
<a name="L1083" href="source/net/ipv4/inet_diag.c#L1083">1083</a>         .<a href="ident?i=dump">dump</a> = <a href="ident?i=inet_diag_handler_dump">inet_diag_handler_dump</a>,
<a name="L1084" href="source/net/ipv4/inet_diag.c#L1084">1084</a> };
<a name="L1085" href="source/net/ipv4/inet_diag.c#L1085">1085</a> 
<a name="L1086" href="source/net/ipv4/inet_diag.c#L1086">1086</a> static const struct <a href="ident?i=sock_diag_handler">sock_diag_handler</a> <a href="ident?i=inet6_diag_handler">inet6_diag_handler</a> = {
<a name="L1087" href="source/net/ipv4/inet_diag.c#L1087">1087</a>         .<a href="ident?i=family">family</a> = <a href="ident?i=AF_INET6">AF_INET6</a>,
<a name="L1088" href="source/net/ipv4/inet_diag.c#L1088">1088</a>         .<a href="ident?i=dump">dump</a> = <a href="ident?i=inet_diag_handler_dump">inet_diag_handler_dump</a>,
<a name="L1089" href="source/net/ipv4/inet_diag.c#L1089">1089</a> };
<a name="L1090" href="source/net/ipv4/inet_diag.c#L1090">1090</a> 
<a name="L1091" href="source/net/ipv4/inet_diag.c#L1091">1091</a> int <a href="ident?i=inet_diag_register">inet_diag_register</a>(const struct <a href="ident?i=inet_diag_handler">inet_diag_handler</a> *<a href="ident?i=h">h</a>)
<a name="L1092" href="source/net/ipv4/inet_diag.c#L1092">1092</a> {
<a name="L1093" href="source/net/ipv4/inet_diag.c#L1093">1093</a>         const <a href="ident?i=__u16">__u16</a> <a href="ident?i=type">type</a> = <a href="ident?i=h">h</a>-&gt;idiag_type;
<a name="L1094" href="source/net/ipv4/inet_diag.c#L1094">1094</a>         int <a href="ident?i=err">err</a> = -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L1095" href="source/net/ipv4/inet_diag.c#L1095">1095</a> 
<a name="L1096" href="source/net/ipv4/inet_diag.c#L1096">1096</a>         if (<a href="ident?i=type">type</a> &gt;= IPPROTO_MAX)
<a name="L1097" href="source/net/ipv4/inet_diag.c#L1097">1097</a>                 goto <a href="ident?i=out">out</a>;
<a name="L1098" href="source/net/ipv4/inet_diag.c#L1098">1098</a> 
<a name="L1099" href="source/net/ipv4/inet_diag.c#L1099">1099</a>         <a href="ident?i=mutex_lock">mutex_lock</a>(&amp;inet_diag_table_mutex);
<a name="L1100" href="source/net/ipv4/inet_diag.c#L1100">1100</a>         <a href="ident?i=err">err</a> = -<a href="ident?i=EEXIST">EEXIST</a>;
<a name="L1101" href="source/net/ipv4/inet_diag.c#L1101">1101</a>         if (!<a href="ident?i=inet_diag_table">inet_diag_table</a>[<a href="ident?i=type">type</a>]) {
<a name="L1102" href="source/net/ipv4/inet_diag.c#L1102">1102</a>                 <a href="ident?i=inet_diag_table">inet_diag_table</a>[<a href="ident?i=type">type</a>] = <a href="ident?i=h">h</a>;
<a name="L1103" href="source/net/ipv4/inet_diag.c#L1103">1103</a>                 <a href="ident?i=err">err</a> = 0;
<a name="L1104" href="source/net/ipv4/inet_diag.c#L1104">1104</a>         }
<a name="L1105" href="source/net/ipv4/inet_diag.c#L1105">1105</a>         <a href="ident?i=mutex_unlock">mutex_unlock</a>(&amp;inet_diag_table_mutex);
<a name="L1106" href="source/net/ipv4/inet_diag.c#L1106">1106</a> <a href="ident?i=out">out</a>:
<a name="L1107" href="source/net/ipv4/inet_diag.c#L1107">1107</a>         return <a href="ident?i=err">err</a>;
<a name="L1108" href="source/net/ipv4/inet_diag.c#L1108">1108</a> }
<a name="L1109" href="source/net/ipv4/inet_diag.c#L1109">1109</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=inet_diag_register">inet_diag_register</a>);
<a name="L1110" href="source/net/ipv4/inet_diag.c#L1110">1110</a> 
<a name="L1111" href="source/net/ipv4/inet_diag.c#L1111">1111</a> void <a href="ident?i=inet_diag_unregister">inet_diag_unregister</a>(const struct <a href="ident?i=inet_diag_handler">inet_diag_handler</a> *<a href="ident?i=h">h</a>)
<a name="L1112" href="source/net/ipv4/inet_diag.c#L1112">1112</a> {
<a name="L1113" href="source/net/ipv4/inet_diag.c#L1113">1113</a>         const <a href="ident?i=__u16">__u16</a> <a href="ident?i=type">type</a> = <a href="ident?i=h">h</a>-&gt;idiag_type;
<a name="L1114" href="source/net/ipv4/inet_diag.c#L1114">1114</a> 
<a name="L1115" href="source/net/ipv4/inet_diag.c#L1115">1115</a>         if (<a href="ident?i=type">type</a> &gt;= IPPROTO_MAX)
<a name="L1116" href="source/net/ipv4/inet_diag.c#L1116">1116</a>                 return;
<a name="L1117" href="source/net/ipv4/inet_diag.c#L1117">1117</a> 
<a name="L1118" href="source/net/ipv4/inet_diag.c#L1118">1118</a>         <a href="ident?i=mutex_lock">mutex_lock</a>(&amp;inet_diag_table_mutex);
<a name="L1119" href="source/net/ipv4/inet_diag.c#L1119">1119</a>         <a href="ident?i=inet_diag_table">inet_diag_table</a>[<a href="ident?i=type">type</a>] = <a href="ident?i=NULL">NULL</a>;
<a name="L1120" href="source/net/ipv4/inet_diag.c#L1120">1120</a>         <a href="ident?i=mutex_unlock">mutex_unlock</a>(&amp;inet_diag_table_mutex);
<a name="L1121" href="source/net/ipv4/inet_diag.c#L1121">1121</a> }
<a name="L1122" href="source/net/ipv4/inet_diag.c#L1122">1122</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=inet_diag_unregister">inet_diag_unregister</a>);
<a name="L1123" href="source/net/ipv4/inet_diag.c#L1123">1123</a> 
<a name="L1124" href="source/net/ipv4/inet_diag.c#L1124">1124</a> static int <a href="ident?i=__init">__init</a> <a href="ident?i=inet_diag_init">inet_diag_init</a>(void)
<a name="L1125" href="source/net/ipv4/inet_diag.c#L1125">1125</a> {
<a name="L1126" href="source/net/ipv4/inet_diag.c#L1126">1126</a>         const int inet_diag_table_size = (IPPROTO_MAX *
<a name="L1127" href="source/net/ipv4/inet_diag.c#L1127">1127</a>                                           sizeof(struct <a href="ident?i=inet_diag_handler">inet_diag_handler</a> *));
<a name="L1128" href="source/net/ipv4/inet_diag.c#L1128">1128</a>         int <a href="ident?i=err">err</a> = -<a href="ident?i=ENOMEM">ENOMEM</a>;
<a name="L1129" href="source/net/ipv4/inet_diag.c#L1129">1129</a> 
<a name="L1130" href="source/net/ipv4/inet_diag.c#L1130">1130</a>         <a href="ident?i=inet_diag_table">inet_diag_table</a> = <a href="ident?i=kzalloc">kzalloc</a>(inet_diag_table_size, <a href="ident?i=GFP_KERNEL">GFP_KERNEL</a>);
<a name="L1131" href="source/net/ipv4/inet_diag.c#L1131">1131</a>         if (!<a href="ident?i=inet_diag_table">inet_diag_table</a>)
<a name="L1132" href="source/net/ipv4/inet_diag.c#L1132">1132</a>                 goto <a href="ident?i=out">out</a>;
<a name="L1133" href="source/net/ipv4/inet_diag.c#L1133">1133</a> 
<a name="L1134" href="source/net/ipv4/inet_diag.c#L1134">1134</a>         <a href="ident?i=err">err</a> = <a href="ident?i=sock_diag_register">sock_diag_register</a>(&amp;<a href="ident?i=inet_diag_handler">inet_diag_handler</a>);
<a name="L1135" href="source/net/ipv4/inet_diag.c#L1135">1135</a>         if (<a href="ident?i=err">err</a>)
<a name="L1136" href="source/net/ipv4/inet_diag.c#L1136">1136</a>                 goto out_free_nl;
<a name="L1137" href="source/net/ipv4/inet_diag.c#L1137">1137</a> 
<a name="L1138" href="source/net/ipv4/inet_diag.c#L1138">1138</a>         <a href="ident?i=err">err</a> = <a href="ident?i=sock_diag_register">sock_diag_register</a>(&amp;<a href="ident?i=inet6_diag_handler">inet6_diag_handler</a>);
<a name="L1139" href="source/net/ipv4/inet_diag.c#L1139">1139</a>         if (<a href="ident?i=err">err</a>)
<a name="L1140" href="source/net/ipv4/inet_diag.c#L1140">1140</a>                 goto out_free_inet;
<a name="L1141" href="source/net/ipv4/inet_diag.c#L1141">1141</a> 
<a name="L1142" href="source/net/ipv4/inet_diag.c#L1142">1142</a>         <a href="ident?i=sock_diag_register_inet_compat">sock_diag_register_inet_compat</a>(<a href="ident?i=inet_diag_rcv_msg_compat">inet_diag_rcv_msg_compat</a>);
<a name="L1143" href="source/net/ipv4/inet_diag.c#L1143">1143</a> <a href="ident?i=out">out</a>:
<a name="L1144" href="source/net/ipv4/inet_diag.c#L1144">1144</a>         return <a href="ident?i=err">err</a>;
<a name="L1145" href="source/net/ipv4/inet_diag.c#L1145">1145</a> 
<a name="L1146" href="source/net/ipv4/inet_diag.c#L1146">1146</a> out_free_inet:
<a name="L1147" href="source/net/ipv4/inet_diag.c#L1147">1147</a>         <a href="ident?i=sock_diag_unregister">sock_diag_unregister</a>(&amp;<a href="ident?i=inet_diag_handler">inet_diag_handler</a>);
<a name="L1148" href="source/net/ipv4/inet_diag.c#L1148">1148</a> out_free_nl:
<a name="L1149" href="source/net/ipv4/inet_diag.c#L1149">1149</a>         <a href="ident?i=kfree">kfree</a>(<a href="ident?i=inet_diag_table">inet_diag_table</a>);
<a name="L1150" href="source/net/ipv4/inet_diag.c#L1150">1150</a>         goto <a href="ident?i=out">out</a>;
<a name="L1151" href="source/net/ipv4/inet_diag.c#L1151">1151</a> }
<a name="L1152" href="source/net/ipv4/inet_diag.c#L1152">1152</a> 
<a name="L1153" href="source/net/ipv4/inet_diag.c#L1153">1153</a> static void <a href="ident?i=__exit">__exit</a> <a href="ident?i=inet_diag_exit">inet_diag_exit</a>(void)
<a name="L1154" href="source/net/ipv4/inet_diag.c#L1154">1154</a> {
<a name="L1155" href="source/net/ipv4/inet_diag.c#L1155">1155</a>         <a href="ident?i=sock_diag_unregister">sock_diag_unregister</a>(&amp;<a href="ident?i=inet6_diag_handler">inet6_diag_handler</a>);
<a name="L1156" href="source/net/ipv4/inet_diag.c#L1156">1156</a>         <a href="ident?i=sock_diag_unregister">sock_diag_unregister</a>(&amp;<a href="ident?i=inet_diag_handler">inet_diag_handler</a>);
<a name="L1157" href="source/net/ipv4/inet_diag.c#L1157">1157</a>         <a href="ident?i=sock_diag_unregister_inet_compat">sock_diag_unregister_inet_compat</a>(<a href="ident?i=inet_diag_rcv_msg_compat">inet_diag_rcv_msg_compat</a>);
<a name="L1158" href="source/net/ipv4/inet_diag.c#L1158">1158</a>         <a href="ident?i=kfree">kfree</a>(<a href="ident?i=inet_diag_table">inet_diag_table</a>);
<a name="L1159" href="source/net/ipv4/inet_diag.c#L1159">1159</a> }
<a name="L1160" href="source/net/ipv4/inet_diag.c#L1160">1160</a> 
<a name="L1161" href="source/net/ipv4/inet_diag.c#L1161">1161</a> <a href="ident?i=module_init">module_init</a>(<a href="ident?i=inet_diag_init">inet_diag_init</a>);
<a name="L1162" href="source/net/ipv4/inet_diag.c#L1162">1162</a> <a href="ident?i=module_exit">module_exit</a>(<a href="ident?i=inet_diag_exit">inet_diag_exit</a>);
<a name="L1163" href="source/net/ipv4/inet_diag.c#L1163">1163</a> <a href="ident?i=MODULE_LICENSE">MODULE_LICENSE</a>(<i>"GPL"</i>);
<a name="L1164" href="source/net/ipv4/inet_diag.c#L1164">1164</a> <a href="ident?i=MODULE_ALIAS_NET_PF_PROTO_TYPE">MODULE_ALIAS_NET_PF_PROTO_TYPE</a>(<a href="ident?i=PF_NETLINK">PF_NETLINK</a>, <a href="ident?i=NETLINK_SOCK_DIAG">NETLINK_SOCK_DIAG</a>, 2 <b><i>/* AF_INET */</i></b>);
<a name="L1165" href="source/net/ipv4/inet_diag.c#L1165">1165</a> <a href="ident?i=MODULE_ALIAS_NET_PF_PROTO_TYPE">MODULE_ALIAS_NET_PF_PROTO_TYPE</a>(<a href="ident?i=PF_NETLINK">PF_NETLINK</a>, <a href="ident?i=NETLINK_SOCK_DIAG">NETLINK_SOCK_DIAG</a>, 10 <b><i>/* AF_INET6 */</i></b>);
<a name="L1166" href="source/net/ipv4/inet_diag.c#L1166">1166</a> </pre></div><p>
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
