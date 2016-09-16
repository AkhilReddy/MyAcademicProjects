<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title>Linux/net/ipv4/udplite.c - Linux Cross Reference - Free Electrons</title>
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
		 &nbsp;&bull;&nbsp;<b><i>source navigation</i></b> &nbsp;&bull;&nbsp;<a href="diff/net/ipv4/udplite.c">diff markup</a> &nbsp;&bull;&nbsp;<a href="ident">identifier search</a> &nbsp;&bull;&nbsp;<a href="search">freetext search</a> &nbsp;&bull;&nbsp;
		</p>
	</div>
</div>

<div id="topbar">
  
  <p>Version: &nbsp;<a href="source/net/ipv4/udplite.c?v=2.0.40">2.0.40</a>&nbsp;<a href="source/net/ipv4/udplite.c?v=2.2.26">2.2.26</a>&nbsp;<a href="source/net/ipv4/udplite.c?v=2.4.37">2.4.37</a>&nbsp;<a href="source/net/ipv4/udplite.c?v=3.5">3.5</a>&nbsp;<a href="source/net/ipv4/udplite.c?v=3.6">3.6</a>&nbsp;<a href="source/net/ipv4/udplite.c?v=3.7">3.7</a>&nbsp;<a href="source/net/ipv4/udplite.c?v=3.8">3.8</a>&nbsp;<a href="source/net/ipv4/udplite.c?v=3.9">3.9</a>&nbsp;<a href="source/net/ipv4/udplite.c?v=3.10">3.10</a>&nbsp;<a href="source/net/ipv4/udplite.c?v=3.11">3.11</a>&nbsp;<a href="source/net/ipv4/udplite.c?v=3.12">3.12</a>&nbsp;<a href="source/net/ipv4/udplite.c?v=3.13">3.13</a>&nbsp;<a href="source/net/ipv4/udplite.c?v=3.14">3.14</a>&nbsp;<a href="source/net/ipv4/udplite.c?v=3.15">3.15</a>&nbsp;<a href="source/net/ipv4/udplite.c?v=3.16">3.16</a>&nbsp;<a href="source/net/ipv4/udplite.c?v=3.17">3.17</a>&nbsp;<a href="source/net/ipv4/udplite.c?v=3.18">3.18</a>&nbsp;<a href="source/net/ipv4/udplite.c?v=3.19">3.19</a>&nbsp;<a href="source/net/ipv4/udplite.c?v=4.0">4.0</a>&nbsp;<b><i>4.1</i></b></p>
  
</div>

<h1><a href="source/">Linux</a>/<a href="source/net/">net</a>/<a href="source/net/ipv4/">ipv4</a>/<a href="source/net/ipv4/udplite.c">udplite.c</a></h1>
<div id="lxrcode"><pre>  <a name="L1" href="source/net/ipv4/udplite.c#L1">1</a> <b><i>/*</i></b>
  <a name="L2" href="source/net/ipv4/udplite.c#L2">2</a> <b><i> *  UDPLITE     An implementation of the UDP-Lite protocol (RFC 3828).</i></b>
  <a name="L3" href="source/net/ipv4/udplite.c#L3">3</a> <b><i> *</i></b>
  <a name="L4" href="source/net/ipv4/udplite.c#L4">4</a> <b><i> *  Authors:    Gerrit Renker       &lt;gerrit@erg.abdn.ac.uk&gt;</i></b>
  <a name="L5" href="source/net/ipv4/udplite.c#L5">5</a> <b><i> *</i></b>
  <a name="L6" href="source/net/ipv4/udplite.c#L6">6</a> <b><i> *  Changes:</i></b>
  <a name="L7" href="source/net/ipv4/udplite.c#L7">7</a> <b><i> *  Fixes:</i></b>
  <a name="L8" href="source/net/ipv4/udplite.c#L8">8</a> <b><i> *              This program is free software; you can redistribute it and/or</i></b>
  <a name="L9" href="source/net/ipv4/udplite.c#L9">9</a> <b><i> *              modify it under the terms of the GNU General Public License</i></b>
 <a name="L10" href="source/net/ipv4/udplite.c#L10">10</a> <b><i> *              as published by the Free Software Foundation; either version</i></b>
 <a name="L11" href="source/net/ipv4/udplite.c#L11">11</a> <b><i> *              2 of the License, or (at your option) any later version.</i></b>
 <a name="L12" href="source/net/ipv4/udplite.c#L12">12</a> <b><i> */</i></b>
 <a name="L13" href="source/net/ipv4/udplite.c#L13">13</a> 
 <a name="L14" href="source/net/ipv4/udplite.c#L14">14</a> #define <a href="ident?i=pr_fmt">pr_fmt</a>(<a href="ident?i=fmt">fmt</a>) <i>"UDPLite: "</i> <a href="ident?i=fmt">fmt</a>
 <a name="L15" href="source/net/ipv4/udplite.c#L15">15</a> 
 <a name="L16" href="source/net/ipv4/udplite.c#L16">16</a> #include &lt;linux/export.h&gt;
 <a name="L17" href="source/net/ipv4/udplite.c#L17">17</a> #include "<a href="source/net/ipv4/udp_impl.h">udp_impl.h</a>"
 <a name="L18" href="source/net/ipv4/udplite.c#L18">18</a> 
 <a name="L19" href="source/net/ipv4/udplite.c#L19">19</a> struct <a href="ident?i=udp_table">udp_table</a>        <a href="ident?i=udplite_table">udplite_table</a> <a href="ident?i=__read_mostly">__read_mostly</a>;
 <a name="L20" href="source/net/ipv4/udplite.c#L20">20</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=udplite_table">udplite_table</a>);
 <a name="L21" href="source/net/ipv4/udplite.c#L21">21</a> 
 <a name="L22" href="source/net/ipv4/udplite.c#L22">22</a> static int <a href="ident?i=udplite_rcv">udplite_rcv</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
 <a name="L23" href="source/net/ipv4/udplite.c#L23">23</a> {
 <a name="L24" href="source/net/ipv4/udplite.c#L24">24</a>         return <a href="ident?i=__udp4_lib_rcv">__udp4_lib_rcv</a>(<a href="ident?i=skb">skb</a>, &amp;<a href="ident?i=udplite_table">udplite_table</a>, <a href="ident?i=IPPROTO_UDPLITE">IPPROTO_UDPLITE</a>);
 <a name="L25" href="source/net/ipv4/udplite.c#L25">25</a> }
 <a name="L26" href="source/net/ipv4/udplite.c#L26">26</a> 
 <a name="L27" href="source/net/ipv4/udplite.c#L27">27</a> static void <a href="ident?i=udplite_err">udplite_err</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, <a href="ident?i=u32">u32</a> <a href="ident?i=info">info</a>)
 <a name="L28" href="source/net/ipv4/udplite.c#L28">28</a> {
 <a name="L29" href="source/net/ipv4/udplite.c#L29">29</a>         <a href="ident?i=__udp4_lib_err">__udp4_lib_err</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=info">info</a>, &amp;<a href="ident?i=udplite_table">udplite_table</a>);
 <a name="L30" href="source/net/ipv4/udplite.c#L30">30</a> }
 <a name="L31" href="source/net/ipv4/udplite.c#L31">31</a> 
 <a name="L32" href="source/net/ipv4/udplite.c#L32">32</a> static const struct <a href="ident?i=net_protocol">net_protocol</a> <a href="ident?i=udplite_protocol">udplite_protocol</a> = {
 <a name="L33" href="source/net/ipv4/udplite.c#L33">33</a>         .<a href="ident?i=handler">handler</a>        = <a href="ident?i=udplite_rcv">udplite_rcv</a>,
 <a name="L34" href="source/net/ipv4/udplite.c#L34">34</a>         .<a href="ident?i=err_handler">err_handler</a>    = <a href="ident?i=udplite_err">udplite_err</a>,
 <a name="L35" href="source/net/ipv4/udplite.c#L35">35</a>         .no_policy      = 1,
 <a name="L36" href="source/net/ipv4/udplite.c#L36">36</a>         .netns_ok       = 1,
 <a name="L37" href="source/net/ipv4/udplite.c#L37">37</a> };
 <a name="L38" href="source/net/ipv4/udplite.c#L38">38</a> 
 <a name="L39" href="source/net/ipv4/udplite.c#L39">39</a> struct <a href="ident?i=proto">proto</a>    <a href="ident?i=udplite_prot">udplite_prot</a> = {
 <a name="L40" href="source/net/ipv4/udplite.c#L40">40</a>         .<a href="ident?i=name">name</a>              = <i>"UDP-Lite"</i>,
 <a name="L41" href="source/net/ipv4/udplite.c#L41">41</a>         .owner             = <a href="ident?i=THIS_MODULE">THIS_MODULE</a>,
 <a name="L42" href="source/net/ipv4/udplite.c#L42">42</a>         .<a href="ident?i=close">close</a>             = <a href="ident?i=udp_lib_close">udp_lib_close</a>,
 <a name="L43" href="source/net/ipv4/udplite.c#L43">43</a>         .<a href="ident?i=connect">connect</a>           = <a href="ident?i=ip4_datagram_connect">ip4_datagram_connect</a>,
 <a name="L44" href="source/net/ipv4/udplite.c#L44">44</a>         .<a href="ident?i=disconnect">disconnect</a>        = <a href="ident?i=udp_disconnect">udp_disconnect</a>,
 <a name="L45" href="source/net/ipv4/udplite.c#L45">45</a>         .<a href="ident?i=ioctl">ioctl</a>             = <a href="ident?i=udp_ioctl">udp_ioctl</a>,
 <a name="L46" href="source/net/ipv4/udplite.c#L46">46</a>         .<a href="ident?i=init">init</a>              = <a href="ident?i=udplite_sk_init">udplite_sk_init</a>,
 <a name="L47" href="source/net/ipv4/udplite.c#L47">47</a>         .<a href="ident?i=destroy">destroy</a>           = <a href="ident?i=udp_destroy_sock">udp_destroy_sock</a>,
 <a name="L48" href="source/net/ipv4/udplite.c#L48">48</a>         .<a href="ident?i=setsockopt">setsockopt</a>        = <a href="ident?i=udp_setsockopt">udp_setsockopt</a>,
 <a name="L49" href="source/net/ipv4/udplite.c#L49">49</a>         .getsockopt        = <a href="ident?i=udp_getsockopt">udp_getsockopt</a>,
 <a name="L50" href="source/net/ipv4/udplite.c#L50">50</a>         .<a href="ident?i=sendmsg">sendmsg</a>           = <a href="ident?i=udp_sendmsg">udp_sendmsg</a>,
 <a name="L51" href="source/net/ipv4/udplite.c#L51">51</a>         .recvmsg           = <a href="ident?i=udp_recvmsg">udp_recvmsg</a>,
 <a name="L52" href="source/net/ipv4/udplite.c#L52">52</a>         .sendpage          = <a href="ident?i=udp_sendpage">udp_sendpage</a>,
 <a name="L53" href="source/net/ipv4/udplite.c#L53">53</a>         .backlog_rcv       = <a href="ident?i=udp_queue_rcv_skb">udp_queue_rcv_skb</a>,
 <a name="L54" href="source/net/ipv4/udplite.c#L54">54</a>         .<a href="ident?i=hash">hash</a>              = <a href="ident?i=udp_lib_hash">udp_lib_hash</a>,
 <a name="L55" href="source/net/ipv4/udplite.c#L55">55</a>         .unhash            = <a href="ident?i=udp_lib_unhash">udp_lib_unhash</a>,
 <a name="L56" href="source/net/ipv4/udplite.c#L56">56</a>         .<a href="ident?i=get_port">get_port</a>          = <a href="ident?i=udp_v4_get_port">udp_v4_get_port</a>,
 <a name="L57" href="source/net/ipv4/udplite.c#L57">57</a>         .obj_size          = sizeof(struct <a href="ident?i=udp_sock">udp_sock</a>),
 <a name="L58" href="source/net/ipv4/udplite.c#L58">58</a>         .slab_flags        = <a href="ident?i=SLAB_DESTROY_BY_RCU">SLAB_DESTROY_BY_RCU</a>,
 <a name="L59" href="source/net/ipv4/udplite.c#L59">59</a>         .<a href="ident?i=h">h</a>.<a href="ident?i=udp_table">udp_table</a>       = &amp;<a href="ident?i=udplite_table">udplite_table</a>,
 <a name="L60" href="source/net/ipv4/udplite.c#L60">60</a> #ifdef CONFIG_COMPAT
 <a name="L61" href="source/net/ipv4/udplite.c#L61">61</a>         .compat_setsockopt = <a href="ident?i=compat_udp_setsockopt">compat_udp_setsockopt</a>,
 <a name="L62" href="source/net/ipv4/udplite.c#L62">62</a>         .compat_getsockopt = <a href="ident?i=compat_udp_getsockopt">compat_udp_getsockopt</a>,
 <a name="L63" href="source/net/ipv4/udplite.c#L63">63</a> #endif
 <a name="L64" href="source/net/ipv4/udplite.c#L64">64</a>         .clear_sk          = <a href="ident?i=sk_prot_clear_portaddr_nulls">sk_prot_clear_portaddr_nulls</a>,
 <a name="L65" href="source/net/ipv4/udplite.c#L65">65</a> };
 <a name="L66" href="source/net/ipv4/udplite.c#L66">66</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=udplite_prot">udplite_prot</a>);
 <a name="L67" href="source/net/ipv4/udplite.c#L67">67</a> 
 <a name="L68" href="source/net/ipv4/udplite.c#L68">68</a> static struct <a href="ident?i=inet_protosw">inet_protosw</a> <a href="ident?i=udplite4_protosw">udplite4_protosw</a> = {
 <a name="L69" href="source/net/ipv4/udplite.c#L69">69</a>         .<a href="ident?i=type">type</a>           =  SOCK_DGRAM,
 <a name="L70" href="source/net/ipv4/udplite.c#L70">70</a>         .<a href="ident?i=protocol">protocol</a>       =  <a href="ident?i=IPPROTO_UDPLITE">IPPROTO_UDPLITE</a>,
 <a name="L71" href="source/net/ipv4/udplite.c#L71">71</a>         .prot           =  &amp;<a href="ident?i=udplite_prot">udplite_prot</a>,
 <a name="L72" href="source/net/ipv4/udplite.c#L72">72</a>         .<a href="ident?i=ops">ops</a>            =  &amp;<a href="ident?i=inet_dgram_ops">inet_dgram_ops</a>,
 <a name="L73" href="source/net/ipv4/udplite.c#L73">73</a>         .<a href="ident?i=flags">flags</a>          =  <a href="ident?i=INET_PROTOSW_PERMANENT">INET_PROTOSW_PERMANENT</a>,
 <a name="L74" href="source/net/ipv4/udplite.c#L74">74</a> };
 <a name="L75" href="source/net/ipv4/udplite.c#L75">75</a> 
 <a name="L76" href="source/net/ipv4/udplite.c#L76">76</a> #ifdef CONFIG_PROC_FS
 <a name="L77" href="source/net/ipv4/udplite.c#L77">77</a> 
 <a name="L78" href="source/net/ipv4/udplite.c#L78">78</a> static const struct <a href="ident?i=file_operations">file_operations</a> <a href="ident?i=udplite_afinfo_seq_fops">udplite_afinfo_seq_fops</a> = {
 <a name="L79" href="source/net/ipv4/udplite.c#L79">79</a>         .owner    = <a href="ident?i=THIS_MODULE">THIS_MODULE</a>,
 <a name="L80" href="source/net/ipv4/udplite.c#L80">80</a>         .<a href="ident?i=open">open</a>     = <a href="ident?i=udp_seq_open">udp_seq_open</a>,
 <a name="L81" href="source/net/ipv4/udplite.c#L81">81</a>         .<a href="ident?i=read">read</a>     = <a href="ident?i=seq_read">seq_read</a>,
 <a name="L82" href="source/net/ipv4/udplite.c#L82">82</a>         .llseek   = <a href="ident?i=seq_lseek">seq_lseek</a>,
 <a name="L83" href="source/net/ipv4/udplite.c#L83">83</a>         .<a href="ident?i=release">release</a>  = <a href="ident?i=seq_release_net">seq_release_net</a>
 <a name="L84" href="source/net/ipv4/udplite.c#L84">84</a> };
 <a name="L85" href="source/net/ipv4/udplite.c#L85">85</a> 
 <a name="L86" href="source/net/ipv4/udplite.c#L86">86</a> static struct <a href="ident?i=udp_seq_afinfo">udp_seq_afinfo</a> <a href="ident?i=udplite4_seq_afinfo">udplite4_seq_afinfo</a> = {
 <a name="L87" href="source/net/ipv4/udplite.c#L87">87</a>         .<a href="ident?i=name">name</a>           = <i>"udplite"</i>,
 <a name="L88" href="source/net/ipv4/udplite.c#L88">88</a>         .<a href="ident?i=family">family</a>         = <a href="ident?i=AF_INET">AF_INET</a>,
 <a name="L89" href="source/net/ipv4/udplite.c#L89">89</a>         .<a href="ident?i=udp_table">udp_table</a>      = &amp;<a href="ident?i=udplite_table">udplite_table</a>,
 <a name="L90" href="source/net/ipv4/udplite.c#L90">90</a>         .seq_fops       = &amp;<a href="ident?i=udplite_afinfo_seq_fops">udplite_afinfo_seq_fops</a>,
 <a name="L91" href="source/net/ipv4/udplite.c#L91">91</a>         .seq_ops        = {
 <a name="L92" href="source/net/ipv4/udplite.c#L92">92</a>                 .<a href="ident?i=show">show</a>           = <a href="ident?i=udp4_seq_show">udp4_seq_show</a>,
 <a name="L93" href="source/net/ipv4/udplite.c#L93">93</a>         },
 <a name="L94" href="source/net/ipv4/udplite.c#L94">94</a> };
 <a name="L95" href="source/net/ipv4/udplite.c#L95">95</a> 
 <a name="L96" href="source/net/ipv4/udplite.c#L96">96</a> static int <a href="ident?i=__net_init">__net_init</a> <a href="ident?i=udplite4_proc_init_net">udplite4_proc_init_net</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>)
 <a name="L97" href="source/net/ipv4/udplite.c#L97">97</a> {
 <a name="L98" href="source/net/ipv4/udplite.c#L98">98</a>         return <a href="ident?i=udp_proc_register">udp_proc_register</a>(<a href="ident?i=net">net</a>, &amp;<a href="ident?i=udplite4_seq_afinfo">udplite4_seq_afinfo</a>);
 <a name="L99" href="source/net/ipv4/udplite.c#L99">99</a> }
<a name="L100" href="source/net/ipv4/udplite.c#L100">100</a> 
<a name="L101" href="source/net/ipv4/udplite.c#L101">101</a> static void <a href="ident?i=__net_exit">__net_exit</a> <a href="ident?i=udplite4_proc_exit_net">udplite4_proc_exit_net</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>)
<a name="L102" href="source/net/ipv4/udplite.c#L102">102</a> {
<a name="L103" href="source/net/ipv4/udplite.c#L103">103</a>         <a href="ident?i=udp_proc_unregister">udp_proc_unregister</a>(<a href="ident?i=net">net</a>, &amp;<a href="ident?i=udplite4_seq_afinfo">udplite4_seq_afinfo</a>);
<a name="L104" href="source/net/ipv4/udplite.c#L104">104</a> }
<a name="L105" href="source/net/ipv4/udplite.c#L105">105</a> 
<a name="L106" href="source/net/ipv4/udplite.c#L106">106</a> static struct <a href="ident?i=pernet_operations">pernet_operations</a> <a href="ident?i=udplite4_net_ops">udplite4_net_ops</a> = {
<a name="L107" href="source/net/ipv4/udplite.c#L107">107</a>         .<a href="ident?i=init">init</a> = <a href="ident?i=udplite4_proc_init_net">udplite4_proc_init_net</a>,
<a name="L108" href="source/net/ipv4/udplite.c#L108">108</a>         .<a href="ident?i=exit">exit</a> = <a href="ident?i=udplite4_proc_exit_net">udplite4_proc_exit_net</a>,
<a name="L109" href="source/net/ipv4/udplite.c#L109">109</a> };
<a name="L110" href="source/net/ipv4/udplite.c#L110">110</a> 
<a name="L111" href="source/net/ipv4/udplite.c#L111">111</a> static <a href="ident?i=__init">__init</a> int <a href="ident?i=udplite4_proc_init">udplite4_proc_init</a>(void)
<a name="L112" href="source/net/ipv4/udplite.c#L112">112</a> {
<a name="L113" href="source/net/ipv4/udplite.c#L113">113</a>         return <a href="ident?i=register_pernet_subsys">register_pernet_subsys</a>(&amp;<a href="ident?i=udplite4_net_ops">udplite4_net_ops</a>);
<a name="L114" href="source/net/ipv4/udplite.c#L114">114</a> }
<a name="L115" href="source/net/ipv4/udplite.c#L115">115</a> #else
<a name="L116" href="source/net/ipv4/udplite.c#L116">116</a> static inline int <a href="ident?i=udplite4_proc_init">udplite4_proc_init</a>(void)
<a name="L117" href="source/net/ipv4/udplite.c#L117">117</a> {
<a name="L118" href="source/net/ipv4/udplite.c#L118">118</a>         return 0;
<a name="L119" href="source/net/ipv4/udplite.c#L119">119</a> }
<a name="L120" href="source/net/ipv4/udplite.c#L120">120</a> #endif
<a name="L121" href="source/net/ipv4/udplite.c#L121">121</a> 
<a name="L122" href="source/net/ipv4/udplite.c#L122">122</a> void <a href="ident?i=__init">__init</a> <a href="ident?i=udplite4_register">udplite4_register</a>(void)
<a name="L123" href="source/net/ipv4/udplite.c#L123">123</a> {
<a name="L124" href="source/net/ipv4/udplite.c#L124">124</a>         <a href="ident?i=udp_table_init">udp_table_init</a>(&amp;<a href="ident?i=udplite_table">udplite_table</a>, <i>"UDP-Lite"</i>);
<a name="L125" href="source/net/ipv4/udplite.c#L125">125</a>         if (<a href="ident?i=proto_register">proto_register</a>(&amp;<a href="ident?i=udplite_prot">udplite_prot</a>, 1))
<a name="L126" href="source/net/ipv4/udplite.c#L126">126</a>                 goto out_register_err;
<a name="L127" href="source/net/ipv4/udplite.c#L127">127</a> 
<a name="L128" href="source/net/ipv4/udplite.c#L128">128</a>         if (<a href="ident?i=inet_add_protocol">inet_add_protocol</a>(&amp;<a href="ident?i=udplite_protocol">udplite_protocol</a>, <a href="ident?i=IPPROTO_UDPLITE">IPPROTO_UDPLITE</a>) &lt; 0)
<a name="L129" href="source/net/ipv4/udplite.c#L129">129</a>                 goto out_unregister_proto;
<a name="L130" href="source/net/ipv4/udplite.c#L130">130</a> 
<a name="L131" href="source/net/ipv4/udplite.c#L131">131</a>         <a href="ident?i=inet_register_protosw">inet_register_protosw</a>(&amp;<a href="ident?i=udplite4_protosw">udplite4_protosw</a>);
<a name="L132" href="source/net/ipv4/udplite.c#L132">132</a> 
<a name="L133" href="source/net/ipv4/udplite.c#L133">133</a>         if (<a href="ident?i=udplite4_proc_init">udplite4_proc_init</a>())
<a name="L134" href="source/net/ipv4/udplite.c#L134">134</a>                 <a href="ident?i=pr_err">pr_err</a>(<i>"%s: Cannot register /proc!\n"</i>, <a href="ident?i=__func__">__func__</a>);
<a name="L135" href="source/net/ipv4/udplite.c#L135">135</a>         return;
<a name="L136" href="source/net/ipv4/udplite.c#L136">136</a> 
<a name="L137" href="source/net/ipv4/udplite.c#L137">137</a> out_unregister_proto:
<a name="L138" href="source/net/ipv4/udplite.c#L138">138</a>         <a href="ident?i=proto_unregister">proto_unregister</a>(&amp;<a href="ident?i=udplite_prot">udplite_prot</a>);
<a name="L139" href="source/net/ipv4/udplite.c#L139">139</a> out_register_err:
<a name="L140" href="source/net/ipv4/udplite.c#L140">140</a>         <a href="ident?i=pr_crit">pr_crit</a>(<i>"%s: Cannot add UDP-Lite protocol\n"</i>, <a href="ident?i=__func__">__func__</a>);
<a name="L141" href="source/net/ipv4/udplite.c#L141">141</a> }
<a name="L142" href="source/net/ipv4/udplite.c#L142">142</a> </pre></div><p>
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
