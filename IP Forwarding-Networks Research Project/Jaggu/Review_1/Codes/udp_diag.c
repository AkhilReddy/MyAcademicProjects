<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title>Linux/net/ipv4/udp_diag.c - Linux Cross Reference - Free Electrons</title>
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
		 &nbsp;&bull;&nbsp;<b><i>source navigation</i></b> &nbsp;&bull;&nbsp;<a href="diff/net/ipv4/udp_diag.c">diff markup</a> &nbsp;&bull;&nbsp;<a href="ident">identifier search</a> &nbsp;&bull;&nbsp;<a href="search">freetext search</a> &nbsp;&bull;&nbsp;
		</p>
	</div>
</div>

<div id="topbar">
  
  <p>Version: &nbsp;<a href="source/net/ipv4/udp_diag.c?v=2.0.40">2.0.40</a>&nbsp;<a href="source/net/ipv4/udp_diag.c?v=2.2.26">2.2.26</a>&nbsp;<a href="source/net/ipv4/udp_diag.c?v=2.4.37">2.4.37</a>&nbsp;<a href="source/net/ipv4/udp_diag.c?v=3.5">3.5</a>&nbsp;<a href="source/net/ipv4/udp_diag.c?v=3.6">3.6</a>&nbsp;<a href="source/net/ipv4/udp_diag.c?v=3.7">3.7</a>&nbsp;<a href="source/net/ipv4/udp_diag.c?v=3.8">3.8</a>&nbsp;<a href="source/net/ipv4/udp_diag.c?v=3.9">3.9</a>&nbsp;<a href="source/net/ipv4/udp_diag.c?v=3.10">3.10</a>&nbsp;<a href="source/net/ipv4/udp_diag.c?v=3.11">3.11</a>&nbsp;<a href="source/net/ipv4/udp_diag.c?v=3.12">3.12</a>&nbsp;<a href="source/net/ipv4/udp_diag.c?v=3.13">3.13</a>&nbsp;<a href="source/net/ipv4/udp_diag.c?v=3.14">3.14</a>&nbsp;<a href="source/net/ipv4/udp_diag.c?v=3.15">3.15</a>&nbsp;<a href="source/net/ipv4/udp_diag.c?v=3.16">3.16</a>&nbsp;<a href="source/net/ipv4/udp_diag.c?v=3.17">3.17</a>&nbsp;<a href="source/net/ipv4/udp_diag.c?v=3.18">3.18</a>&nbsp;<a href="source/net/ipv4/udp_diag.c?v=3.19">3.19</a>&nbsp;<a href="source/net/ipv4/udp_diag.c?v=4.0">4.0</a>&nbsp;<b><i>4.1</i></b></p>
  
</div>

<h1><a href="source/">Linux</a>/<a href="source/net/">net</a>/<a href="source/net/ipv4/">ipv4</a>/<a href="source/net/ipv4/udp_diag.c">udp_diag.c</a></h1>
<div id="lxrcode"><pre>  <a name="L1" href="source/net/ipv4/udp_diag.c#L1">1</a> <b><i>/*</i></b>
  <a name="L2" href="source/net/ipv4/udp_diag.c#L2">2</a> <b><i> * udp_diag.c   Module for monitoring UDP transport protocols sockets.</i></b>
  <a name="L3" href="source/net/ipv4/udp_diag.c#L3">3</a> <b><i> *</i></b>
  <a name="L4" href="source/net/ipv4/udp_diag.c#L4">4</a> <b><i> * Authors:     Pavel Emelyanov, &lt;xemul@parallels.com&gt;</i></b>
  <a name="L5" href="source/net/ipv4/udp_diag.c#L5">5</a> <b><i> *</i></b>
  <a name="L6" href="source/net/ipv4/udp_diag.c#L6">6</a> <b><i> *      This program is free software; you can redistribute it and/or</i></b>
  <a name="L7" href="source/net/ipv4/udp_diag.c#L7">7</a> <b><i> *      modify it under the terms of the GNU General Public License</i></b>
  <a name="L8" href="source/net/ipv4/udp_diag.c#L8">8</a> <b><i> *      as published by the Free Software Foundation; either version</i></b>
  <a name="L9" href="source/net/ipv4/udp_diag.c#L9">9</a> <b><i> *      2 of the License, or (at your option) any later version.</i></b>
 <a name="L10" href="source/net/ipv4/udp_diag.c#L10">10</a> <b><i> */</i></b>
 <a name="L11" href="source/net/ipv4/udp_diag.c#L11">11</a> 
 <a name="L12" href="source/net/ipv4/udp_diag.c#L12">12</a> 
 <a name="L13" href="source/net/ipv4/udp_diag.c#L13">13</a> #include &lt;linux/module.h&gt;
 <a name="L14" href="source/net/ipv4/udp_diag.c#L14">14</a> #include &lt;linux/inet_diag.h&gt;
 <a name="L15" href="source/net/ipv4/udp_diag.c#L15">15</a> #include &lt;linux/udp.h&gt;
 <a name="L16" href="source/net/ipv4/udp_diag.c#L16">16</a> #include &lt;net/udp.h&gt;
 <a name="L17" href="source/net/ipv4/udp_diag.c#L17">17</a> #include &lt;net/udplite.h&gt;
 <a name="L18" href="source/net/ipv4/udp_diag.c#L18">18</a> #include &lt;linux/sock_diag.h&gt;
 <a name="L19" href="source/net/ipv4/udp_diag.c#L19">19</a> 
 <a name="L20" href="source/net/ipv4/udp_diag.c#L20">20</a> static int <a href="ident?i=sk_diag_dump">sk_diag_dump</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
 <a name="L21" href="source/net/ipv4/udp_diag.c#L21">21</a>                         struct <a href="ident?i=netlink_callback">netlink_callback</a> *<a href="ident?i=cb">cb</a>,
 <a name="L22" href="source/net/ipv4/udp_diag.c#L22">22</a>                         const struct <a href="ident?i=inet_diag_req_v2">inet_diag_req_v2</a> *<a href="ident?i=req">req</a>,
 <a name="L23" href="source/net/ipv4/udp_diag.c#L23">23</a>                         struct <a href="ident?i=nlattr">nlattr</a> *<a href="ident?i=bc">bc</a>)
 <a name="L24" href="source/net/ipv4/udp_diag.c#L24">24</a> {
 <a name="L25" href="source/net/ipv4/udp_diag.c#L25">25</a>         if (!<a href="ident?i=inet_diag_bc_sk">inet_diag_bc_sk</a>(<a href="ident?i=bc">bc</a>, sk))
 <a name="L26" href="source/net/ipv4/udp_diag.c#L26">26</a>                 return 0;
 <a name="L27" href="source/net/ipv4/udp_diag.c#L27">27</a> 
 <a name="L28" href="source/net/ipv4/udp_diag.c#L28">28</a>         return <a href="ident?i=inet_sk_diag_fill">inet_sk_diag_fill</a>(sk, <a href="ident?i=NULL">NULL</a>, <a href="ident?i=skb">skb</a>, <a href="ident?i=req">req</a>,
 <a name="L29" href="source/net/ipv4/udp_diag.c#L29">29</a>                         <a href="ident?i=sk_user_ns">sk_user_ns</a>(<a href="ident?i=NETLINK_CB">NETLINK_CB</a>(<a href="ident?i=cb">cb</a>-&gt;<a href="ident?i=skb">skb</a>).sk),
 <a name="L30" href="source/net/ipv4/udp_diag.c#L30">30</a>                         <a href="ident?i=NETLINK_CB">NETLINK_CB</a>(<a href="ident?i=cb">cb</a>-&gt;<a href="ident?i=skb">skb</a>).portid,
 <a name="L31" href="source/net/ipv4/udp_diag.c#L31">31</a>                         <a href="ident?i=cb">cb</a>-&gt;nlh-&gt;nlmsg_seq, <a href="ident?i=NLM_F_MULTI">NLM_F_MULTI</a>, <a href="ident?i=cb">cb</a>-&gt;nlh);
 <a name="L32" href="source/net/ipv4/udp_diag.c#L32">32</a> }
 <a name="L33" href="source/net/ipv4/udp_diag.c#L33">33</a> 
 <a name="L34" href="source/net/ipv4/udp_diag.c#L34">34</a> static int <a href="ident?i=udp_dump_one">udp_dump_one</a>(struct <a href="ident?i=udp_table">udp_table</a> *tbl, struct <a href="ident?i=sk_buff">sk_buff</a> *in_skb,
 <a name="L35" href="source/net/ipv4/udp_diag.c#L35">35</a>                         const struct <a href="ident?i=nlmsghdr">nlmsghdr</a> *nlh,
 <a name="L36" href="source/net/ipv4/udp_diag.c#L36">36</a>                         const struct <a href="ident?i=inet_diag_req_v2">inet_diag_req_v2</a> *<a href="ident?i=req">req</a>)
 <a name="L37" href="source/net/ipv4/udp_diag.c#L37">37</a> {
 <a name="L38" href="source/net/ipv4/udp_diag.c#L38">38</a>         int <a href="ident?i=err">err</a> = -<a href="ident?i=EINVAL">EINVAL</a>;
 <a name="L39" href="source/net/ipv4/udp_diag.c#L39">39</a>         struct <a href="ident?i=sock">sock</a> *sk;
 <a name="L40" href="source/net/ipv4/udp_diag.c#L40">40</a>         struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=rep">rep</a>;
 <a name="L41" href="source/net/ipv4/udp_diag.c#L41">41</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=sock_net">sock_net</a>(in_skb-&gt;sk);
 <a name="L42" href="source/net/ipv4/udp_diag.c#L42">42</a> 
 <a name="L43" href="source/net/ipv4/udp_diag.c#L43">43</a>         if (<a href="ident?i=req">req</a>-&gt;sdiag_family == <a href="ident?i=AF_INET">AF_INET</a>)
 <a name="L44" href="source/net/ipv4/udp_diag.c#L44">44</a>                 sk = <a href="ident?i=__udp4_lib_lookup">__udp4_lib_lookup</a>(<a href="ident?i=net">net</a>,
 <a name="L45" href="source/net/ipv4/udp_diag.c#L45">45</a>                                 <a href="ident?i=req">req</a>-&gt;<a href="ident?i=id">id</a>.idiag_src[0], <a href="ident?i=req">req</a>-&gt;<a href="ident?i=id">id</a>.idiag_sport,
 <a name="L46" href="source/net/ipv4/udp_diag.c#L46">46</a>                                 <a href="ident?i=req">req</a>-&gt;<a href="ident?i=id">id</a>.idiag_dst[0], <a href="ident?i=req">req</a>-&gt;<a href="ident?i=id">id</a>.idiag_dport,
 <a name="L47" href="source/net/ipv4/udp_diag.c#L47">47</a>                                 <a href="ident?i=req">req</a>-&gt;<a href="ident?i=id">id</a>.idiag_if, tbl);
 <a name="L48" href="source/net/ipv4/udp_diag.c#L48">48</a> #if <a href="ident?i=IS_ENABLED">IS_ENABLED</a>(CONFIG_IPV6)
 <a name="L49" href="source/net/ipv4/udp_diag.c#L49">49</a>         else if (<a href="ident?i=req">req</a>-&gt;sdiag_family == <a href="ident?i=AF_INET6">AF_INET6</a>)
 <a name="L50" href="source/net/ipv4/udp_diag.c#L50">50</a>                 sk = <a href="ident?i=__udp6_lib_lookup">__udp6_lib_lookup</a>(<a href="ident?i=net">net</a>,
 <a name="L51" href="source/net/ipv4/udp_diag.c#L51">51</a>                                 (struct <a href="ident?i=in6_addr">in6_addr</a> *)<a href="ident?i=req">req</a>-&gt;<a href="ident?i=id">id</a>.idiag_src,
 <a name="L52" href="source/net/ipv4/udp_diag.c#L52">52</a>                                 <a href="ident?i=req">req</a>-&gt;<a href="ident?i=id">id</a>.idiag_sport,
 <a name="L53" href="source/net/ipv4/udp_diag.c#L53">53</a>                                 (struct <a href="ident?i=in6_addr">in6_addr</a> *)<a href="ident?i=req">req</a>-&gt;<a href="ident?i=id">id</a>.idiag_dst,
 <a name="L54" href="source/net/ipv4/udp_diag.c#L54">54</a>                                 <a href="ident?i=req">req</a>-&gt;<a href="ident?i=id">id</a>.idiag_dport,
 <a name="L55" href="source/net/ipv4/udp_diag.c#L55">55</a>                                 <a href="ident?i=req">req</a>-&gt;<a href="ident?i=id">id</a>.idiag_if, tbl);
 <a name="L56" href="source/net/ipv4/udp_diag.c#L56">56</a> #endif
 <a name="L57" href="source/net/ipv4/udp_diag.c#L57">57</a>         else
 <a name="L58" href="source/net/ipv4/udp_diag.c#L58">58</a>                 goto out_nosk;
 <a name="L59" href="source/net/ipv4/udp_diag.c#L59">59</a> 
 <a name="L60" href="source/net/ipv4/udp_diag.c#L60">60</a>         <a href="ident?i=err">err</a> = -<a href="ident?i=ENOENT">ENOENT</a>;
 <a name="L61" href="source/net/ipv4/udp_diag.c#L61">61</a>         if (!sk)
 <a name="L62" href="source/net/ipv4/udp_diag.c#L62">62</a>                 goto out_nosk;
 <a name="L63" href="source/net/ipv4/udp_diag.c#L63">63</a> 
 <a name="L64" href="source/net/ipv4/udp_diag.c#L64">64</a>         <a href="ident?i=err">err</a> = <a href="ident?i=sock_diag_check_cookie">sock_diag_check_cookie</a>(sk, <a href="ident?i=req">req</a>-&gt;<a href="ident?i=id">id</a>.idiag_cookie);
 <a name="L65" href="source/net/ipv4/udp_diag.c#L65">65</a>         if (<a href="ident?i=err">err</a>)
 <a name="L66" href="source/net/ipv4/udp_diag.c#L66">66</a>                 goto <a href="ident?i=out">out</a>;
 <a name="L67" href="source/net/ipv4/udp_diag.c#L67">67</a> 
 <a name="L68" href="source/net/ipv4/udp_diag.c#L68">68</a>         <a href="ident?i=err">err</a> = -<a href="ident?i=ENOMEM">ENOMEM</a>;
 <a name="L69" href="source/net/ipv4/udp_diag.c#L69">69</a>         <a href="ident?i=rep">rep</a> = <a href="ident?i=nlmsg_new">nlmsg_new</a>(sizeof(struct <a href="ident?i=inet_diag_msg">inet_diag_msg</a>) +
 <a name="L70" href="source/net/ipv4/udp_diag.c#L70">70</a>                         sizeof(struct <a href="ident?i=inet_diag_meminfo">inet_diag_meminfo</a>) + 64,
 <a name="L71" href="source/net/ipv4/udp_diag.c#L71">71</a>                         <a href="ident?i=GFP_KERNEL">GFP_KERNEL</a>);
 <a name="L72" href="source/net/ipv4/udp_diag.c#L72">72</a>         if (!<a href="ident?i=rep">rep</a>)
 <a name="L73" href="source/net/ipv4/udp_diag.c#L73">73</a>                 goto <a href="ident?i=out">out</a>;
 <a name="L74" href="source/net/ipv4/udp_diag.c#L74">74</a> 
 <a name="L75" href="source/net/ipv4/udp_diag.c#L75">75</a>         <a href="ident?i=err">err</a> = <a href="ident?i=inet_sk_diag_fill">inet_sk_diag_fill</a>(sk, <a href="ident?i=NULL">NULL</a>, <a href="ident?i=rep">rep</a>, <a href="ident?i=req">req</a>,
 <a name="L76" href="source/net/ipv4/udp_diag.c#L76">76</a>                            <a href="ident?i=sk_user_ns">sk_user_ns</a>(<a href="ident?i=NETLINK_CB">NETLINK_CB</a>(in_skb).sk),
 <a name="L77" href="source/net/ipv4/udp_diag.c#L77">77</a>                            <a href="ident?i=NETLINK_CB">NETLINK_CB</a>(in_skb).portid,
 <a name="L78" href="source/net/ipv4/udp_diag.c#L78">78</a>                            nlh-&gt;nlmsg_seq, 0, nlh);
 <a name="L79" href="source/net/ipv4/udp_diag.c#L79">79</a>         if (<a href="ident?i=err">err</a> &lt; 0) {
 <a name="L80" href="source/net/ipv4/udp_diag.c#L80">80</a>                 <a href="ident?i=WARN_ON">WARN_ON</a>(<a href="ident?i=err">err</a> == -<a href="ident?i=EMSGSIZE">EMSGSIZE</a>);
 <a name="L81" href="source/net/ipv4/udp_diag.c#L81">81</a>                 <a href="ident?i=kfree_skb">kfree_skb</a>(<a href="ident?i=rep">rep</a>);
 <a name="L82" href="source/net/ipv4/udp_diag.c#L82">82</a>                 goto <a href="ident?i=out">out</a>;
 <a name="L83" href="source/net/ipv4/udp_diag.c#L83">83</a>         }
 <a name="L84" href="source/net/ipv4/udp_diag.c#L84">84</a>         <a href="ident?i=err">err</a> = <a href="ident?i=netlink_unicast">netlink_unicast</a>(<a href="ident?i=net">net</a>-&gt;diag_nlsk, <a href="ident?i=rep">rep</a>, <a href="ident?i=NETLINK_CB">NETLINK_CB</a>(in_skb).portid,
 <a name="L85" href="source/net/ipv4/udp_diag.c#L85">85</a>                               <a href="ident?i=MSG_DONTWAIT">MSG_DONTWAIT</a>);
 <a name="L86" href="source/net/ipv4/udp_diag.c#L86">86</a>         if (<a href="ident?i=err">err</a> &gt; 0)
 <a name="L87" href="source/net/ipv4/udp_diag.c#L87">87</a>                 <a href="ident?i=err">err</a> = 0;
 <a name="L88" href="source/net/ipv4/udp_diag.c#L88">88</a> <a href="ident?i=out">out</a>:
 <a name="L89" href="source/net/ipv4/udp_diag.c#L89">89</a>         if (sk)
 <a name="L90" href="source/net/ipv4/udp_diag.c#L90">90</a>                 <a href="ident?i=sock_put">sock_put</a>(sk);
 <a name="L91" href="source/net/ipv4/udp_diag.c#L91">91</a> out_nosk:
 <a name="L92" href="source/net/ipv4/udp_diag.c#L92">92</a>         return <a href="ident?i=err">err</a>;
 <a name="L93" href="source/net/ipv4/udp_diag.c#L93">93</a> }
 <a name="L94" href="source/net/ipv4/udp_diag.c#L94">94</a> 
 <a name="L95" href="source/net/ipv4/udp_diag.c#L95">95</a> static void <a href="ident?i=udp_dump">udp_dump</a>(struct <a href="ident?i=udp_table">udp_table</a> *<a href="ident?i=table">table</a>, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
 <a name="L96" href="source/net/ipv4/udp_diag.c#L96">96</a>                      struct <a href="ident?i=netlink_callback">netlink_callback</a> *<a href="ident?i=cb">cb</a>,
 <a name="L97" href="source/net/ipv4/udp_diag.c#L97">97</a>                      const struct <a href="ident?i=inet_diag_req_v2">inet_diag_req_v2</a> *<a href="ident?i=r">r</a>, struct <a href="ident?i=nlattr">nlattr</a> *<a href="ident?i=bc">bc</a>)
 <a name="L98" href="source/net/ipv4/udp_diag.c#L98">98</a> {
 <a name="L99" href="source/net/ipv4/udp_diag.c#L99">99</a>         int <a href="ident?i=num">num</a>, s_num, <a href="ident?i=slot">slot</a>, s_slot;
<a name="L100" href="source/net/ipv4/udp_diag.c#L100">100</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=sock_net">sock_net</a>(<a href="ident?i=skb">skb</a>-&gt;sk);
<a name="L101" href="source/net/ipv4/udp_diag.c#L101">101</a> 
<a name="L102" href="source/net/ipv4/udp_diag.c#L102">102</a>         s_slot = <a href="ident?i=cb">cb</a>-&gt;<a href="ident?i=args">args</a>[0];
<a name="L103" href="source/net/ipv4/udp_diag.c#L103">103</a>         <a href="ident?i=num">num</a> = s_num = <a href="ident?i=cb">cb</a>-&gt;<a href="ident?i=args">args</a>[1];
<a name="L104" href="source/net/ipv4/udp_diag.c#L104">104</a> 
<a name="L105" href="source/net/ipv4/udp_diag.c#L105">105</a>         for (<a href="ident?i=slot">slot</a> = s_slot; <a href="ident?i=slot">slot</a> &lt;= <a href="ident?i=table">table</a>-&gt;<a href="ident?i=mask">mask</a>; s_num = 0, <a href="ident?i=slot">slot</a>++) {
<a name="L106" href="source/net/ipv4/udp_diag.c#L106">106</a>                 struct <a href="ident?i=sock">sock</a> *sk;
<a name="L107" href="source/net/ipv4/udp_diag.c#L107">107</a>                 struct <a href="ident?i=hlist_nulls_node">hlist_nulls_node</a> *<a href="ident?i=node">node</a>;
<a name="L108" href="source/net/ipv4/udp_diag.c#L108">108</a>                 struct <a href="ident?i=udp_hslot">udp_hslot</a> *hslot = &amp;<a href="ident?i=table">table</a>-&gt;<a href="ident?i=hash">hash</a>[<a href="ident?i=slot">slot</a>];
<a name="L109" href="source/net/ipv4/udp_diag.c#L109">109</a> 
<a name="L110" href="source/net/ipv4/udp_diag.c#L110">110</a>                 <a href="ident?i=num">num</a> = 0;
<a name="L111" href="source/net/ipv4/udp_diag.c#L111">111</a> 
<a name="L112" href="source/net/ipv4/udp_diag.c#L112">112</a>                 if (<a href="ident?i=hlist_nulls_empty">hlist_nulls_empty</a>(&amp;hslot-&gt;<a href="ident?i=head">head</a>))
<a name="L113" href="source/net/ipv4/udp_diag.c#L113">113</a>                         continue;
<a name="L114" href="source/net/ipv4/udp_diag.c#L114">114</a> 
<a name="L115" href="source/net/ipv4/udp_diag.c#L115">115</a>                 <a href="ident?i=spin_lock_bh">spin_lock_bh</a>(&amp;hslot-&gt;<a href="ident?i=lock">lock</a>);
<a name="L116" href="source/net/ipv4/udp_diag.c#L116">116</a>                 <a href="ident?i=sk_nulls_for_each">sk_nulls_for_each</a>(sk, <a href="ident?i=node">node</a>, &amp;hslot-&gt;<a href="ident?i=head">head</a>) {
<a name="L117" href="source/net/ipv4/udp_diag.c#L117">117</a>                         struct <a href="ident?i=inet_sock">inet_sock</a> *inet = <a href="ident?i=inet_sk">inet_sk</a>(sk);
<a name="L118" href="source/net/ipv4/udp_diag.c#L118">118</a> 
<a name="L119" href="source/net/ipv4/udp_diag.c#L119">119</a>                         if (!<a href="ident?i=net_eq">net_eq</a>(<a href="ident?i=sock_net">sock_net</a>(sk), <a href="ident?i=net">net</a>))
<a name="L120" href="source/net/ipv4/udp_diag.c#L120">120</a>                                 continue;
<a name="L121" href="source/net/ipv4/udp_diag.c#L121">121</a>                         if (<a href="ident?i=num">num</a> &lt; s_num)
<a name="L122" href="source/net/ipv4/udp_diag.c#L122">122</a>                                 goto <a href="ident?i=next">next</a>;
<a name="L123" href="source/net/ipv4/udp_diag.c#L123">123</a>                         if (!(<a href="ident?i=r">r</a>-&gt;idiag_states &amp; (1 &lt;&lt; sk-&gt;<a href="ident?i=sk_state">sk_state</a>)))
<a name="L124" href="source/net/ipv4/udp_diag.c#L124">124</a>                                 goto <a href="ident?i=next">next</a>;
<a name="L125" href="source/net/ipv4/udp_diag.c#L125">125</a>                         if (<a href="ident?i=r">r</a>-&gt;sdiag_family != <a href="ident?i=AF_UNSPEC">AF_UNSPEC</a> &amp;&amp;
<a name="L126" href="source/net/ipv4/udp_diag.c#L126">126</a>                                         sk-&gt;<a href="ident?i=sk_family">sk_family</a> != <a href="ident?i=r">r</a>-&gt;sdiag_family)
<a name="L127" href="source/net/ipv4/udp_diag.c#L127">127</a>                                 goto <a href="ident?i=next">next</a>;
<a name="L128" href="source/net/ipv4/udp_diag.c#L128">128</a>                         if (<a href="ident?i=r">r</a>-&gt;<a href="ident?i=id">id</a>.idiag_sport != inet-&gt;inet_sport &amp;&amp;
<a name="L129" href="source/net/ipv4/udp_diag.c#L129">129</a>                             <a href="ident?i=r">r</a>-&gt;<a href="ident?i=id">id</a>.idiag_sport)
<a name="L130" href="source/net/ipv4/udp_diag.c#L130">130</a>                                 goto <a href="ident?i=next">next</a>;
<a name="L131" href="source/net/ipv4/udp_diag.c#L131">131</a>                         if (<a href="ident?i=r">r</a>-&gt;<a href="ident?i=id">id</a>.idiag_dport != inet-&gt;<a href="ident?i=inet_dport">inet_dport</a> &amp;&amp;
<a name="L132" href="source/net/ipv4/udp_diag.c#L132">132</a>                             <a href="ident?i=r">r</a>-&gt;<a href="ident?i=id">id</a>.idiag_dport)
<a name="L133" href="source/net/ipv4/udp_diag.c#L133">133</a>                                 goto <a href="ident?i=next">next</a>;
<a name="L134" href="source/net/ipv4/udp_diag.c#L134">134</a> 
<a name="L135" href="source/net/ipv4/udp_diag.c#L135">135</a>                         if (<a href="ident?i=sk_diag_dump">sk_diag_dump</a>(sk, <a href="ident?i=skb">skb</a>, <a href="ident?i=cb">cb</a>, <a href="ident?i=r">r</a>, <a href="ident?i=bc">bc</a>) &lt; 0) {
<a name="L136" href="source/net/ipv4/udp_diag.c#L136">136</a>                                 <a href="ident?i=spin_unlock_bh">spin_unlock_bh</a>(&amp;hslot-&gt;<a href="ident?i=lock">lock</a>);
<a name="L137" href="source/net/ipv4/udp_diag.c#L137">137</a>                                 goto <a href="ident?i=done">done</a>;
<a name="L138" href="source/net/ipv4/udp_diag.c#L138">138</a>                         }
<a name="L139" href="source/net/ipv4/udp_diag.c#L139">139</a> <a href="ident?i=next">next</a>:
<a name="L140" href="source/net/ipv4/udp_diag.c#L140">140</a>                         <a href="ident?i=num">num</a>++;
<a name="L141" href="source/net/ipv4/udp_diag.c#L141">141</a>                 }
<a name="L142" href="source/net/ipv4/udp_diag.c#L142">142</a>                 <a href="ident?i=spin_unlock_bh">spin_unlock_bh</a>(&amp;hslot-&gt;<a href="ident?i=lock">lock</a>);
<a name="L143" href="source/net/ipv4/udp_diag.c#L143">143</a>         }
<a name="L144" href="source/net/ipv4/udp_diag.c#L144">144</a> <a href="ident?i=done">done</a>:
<a name="L145" href="source/net/ipv4/udp_diag.c#L145">145</a>         <a href="ident?i=cb">cb</a>-&gt;<a href="ident?i=args">args</a>[0] = <a href="ident?i=slot">slot</a>;
<a name="L146" href="source/net/ipv4/udp_diag.c#L146">146</a>         <a href="ident?i=cb">cb</a>-&gt;<a href="ident?i=args">args</a>[1] = <a href="ident?i=num">num</a>;
<a name="L147" href="source/net/ipv4/udp_diag.c#L147">147</a> }
<a name="L148" href="source/net/ipv4/udp_diag.c#L148">148</a> 
<a name="L149" href="source/net/ipv4/udp_diag.c#L149">149</a> static void <a href="ident?i=udp_diag_dump">udp_diag_dump</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, struct <a href="ident?i=netlink_callback">netlink_callback</a> *<a href="ident?i=cb">cb</a>,
<a name="L150" href="source/net/ipv4/udp_diag.c#L150">150</a>                           const struct <a href="ident?i=inet_diag_req_v2">inet_diag_req_v2</a> *<a href="ident?i=r">r</a>, struct <a href="ident?i=nlattr">nlattr</a> *<a href="ident?i=bc">bc</a>)
<a name="L151" href="source/net/ipv4/udp_diag.c#L151">151</a> {
<a name="L152" href="source/net/ipv4/udp_diag.c#L152">152</a>         <a href="ident?i=udp_dump">udp_dump</a>(&amp;<a href="ident?i=udp_table">udp_table</a>, <a href="ident?i=skb">skb</a>, <a href="ident?i=cb">cb</a>, <a href="ident?i=r">r</a>, <a href="ident?i=bc">bc</a>);
<a name="L153" href="source/net/ipv4/udp_diag.c#L153">153</a> }
<a name="L154" href="source/net/ipv4/udp_diag.c#L154">154</a> 
<a name="L155" href="source/net/ipv4/udp_diag.c#L155">155</a> static int <a href="ident?i=udp_diag_dump_one">udp_diag_dump_one</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *in_skb, const struct <a href="ident?i=nlmsghdr">nlmsghdr</a> *nlh,
<a name="L156" href="source/net/ipv4/udp_diag.c#L156">156</a>                              const struct <a href="ident?i=inet_diag_req_v2">inet_diag_req_v2</a> *<a href="ident?i=req">req</a>)
<a name="L157" href="source/net/ipv4/udp_diag.c#L157">157</a> {
<a name="L158" href="source/net/ipv4/udp_diag.c#L158">158</a>         return <a href="ident?i=udp_dump_one">udp_dump_one</a>(&amp;<a href="ident?i=udp_table">udp_table</a>, in_skb, nlh, <a href="ident?i=req">req</a>);
<a name="L159" href="source/net/ipv4/udp_diag.c#L159">159</a> }
<a name="L160" href="source/net/ipv4/udp_diag.c#L160">160</a> 
<a name="L161" href="source/net/ipv4/udp_diag.c#L161">161</a> static void <a href="ident?i=udp_diag_get_info">udp_diag_get_info</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=inet_diag_msg">inet_diag_msg</a> *<a href="ident?i=r">r</a>,
<a name="L162" href="source/net/ipv4/udp_diag.c#L162">162</a>                 void *<a href="ident?i=info">info</a>)
<a name="L163" href="source/net/ipv4/udp_diag.c#L163">163</a> {
<a name="L164" href="source/net/ipv4/udp_diag.c#L164">164</a>         <a href="ident?i=r">r</a>-&gt;idiag_rqueue = <a href="ident?i=sk_rmem_alloc_get">sk_rmem_alloc_get</a>(sk);
<a name="L165" href="source/net/ipv4/udp_diag.c#L165">165</a>         <a href="ident?i=r">r</a>-&gt;idiag_wqueue = <a href="ident?i=sk_wmem_alloc_get">sk_wmem_alloc_get</a>(sk);
<a name="L166" href="source/net/ipv4/udp_diag.c#L166">166</a> }
<a name="L167" href="source/net/ipv4/udp_diag.c#L167">167</a> 
<a name="L168" href="source/net/ipv4/udp_diag.c#L168">168</a> static const struct <a href="ident?i=inet_diag_handler">inet_diag_handler</a> <a href="ident?i=udp_diag_handler">udp_diag_handler</a> = {
<a name="L169" href="source/net/ipv4/udp_diag.c#L169">169</a>         .<a href="ident?i=dump">dump</a>            = <a href="ident?i=udp_diag_dump">udp_diag_dump</a>,
<a name="L170" href="source/net/ipv4/udp_diag.c#L170">170</a>         .dump_one        = <a href="ident?i=udp_diag_dump_one">udp_diag_dump_one</a>,
<a name="L171" href="source/net/ipv4/udp_diag.c#L171">171</a>         .idiag_get_info  = <a href="ident?i=udp_diag_get_info">udp_diag_get_info</a>,
<a name="L172" href="source/net/ipv4/udp_diag.c#L172">172</a>         .idiag_type      = <a href="ident?i=IPPROTO_UDP">IPPROTO_UDP</a>,
<a name="L173" href="source/net/ipv4/udp_diag.c#L173">173</a> };
<a name="L174" href="source/net/ipv4/udp_diag.c#L174">174</a> 
<a name="L175" href="source/net/ipv4/udp_diag.c#L175">175</a> static void <a href="ident?i=udplite_diag_dump">udplite_diag_dump</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, struct <a href="ident?i=netlink_callback">netlink_callback</a> *<a href="ident?i=cb">cb</a>,
<a name="L176" href="source/net/ipv4/udp_diag.c#L176">176</a>                               const struct <a href="ident?i=inet_diag_req_v2">inet_diag_req_v2</a> *<a href="ident?i=r">r</a>,
<a name="L177" href="source/net/ipv4/udp_diag.c#L177">177</a>                               struct <a href="ident?i=nlattr">nlattr</a> *<a href="ident?i=bc">bc</a>)
<a name="L178" href="source/net/ipv4/udp_diag.c#L178">178</a> {
<a name="L179" href="source/net/ipv4/udp_diag.c#L179">179</a>         <a href="ident?i=udp_dump">udp_dump</a>(&amp;<a href="ident?i=udplite_table">udplite_table</a>, <a href="ident?i=skb">skb</a>, <a href="ident?i=cb">cb</a>, <a href="ident?i=r">r</a>, <a href="ident?i=bc">bc</a>);
<a name="L180" href="source/net/ipv4/udp_diag.c#L180">180</a> }
<a name="L181" href="source/net/ipv4/udp_diag.c#L181">181</a> 
<a name="L182" href="source/net/ipv4/udp_diag.c#L182">182</a> static int <a href="ident?i=udplite_diag_dump_one">udplite_diag_dump_one</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *in_skb, const struct <a href="ident?i=nlmsghdr">nlmsghdr</a> *nlh,
<a name="L183" href="source/net/ipv4/udp_diag.c#L183">183</a>                                  const struct <a href="ident?i=inet_diag_req_v2">inet_diag_req_v2</a> *<a href="ident?i=req">req</a>)
<a name="L184" href="source/net/ipv4/udp_diag.c#L184">184</a> {
<a name="L185" href="source/net/ipv4/udp_diag.c#L185">185</a>         return <a href="ident?i=udp_dump_one">udp_dump_one</a>(&amp;<a href="ident?i=udplite_table">udplite_table</a>, in_skb, nlh, <a href="ident?i=req">req</a>);
<a name="L186" href="source/net/ipv4/udp_diag.c#L186">186</a> }
<a name="L187" href="source/net/ipv4/udp_diag.c#L187">187</a> 
<a name="L188" href="source/net/ipv4/udp_diag.c#L188">188</a> static const struct <a href="ident?i=inet_diag_handler">inet_diag_handler</a> <a href="ident?i=udplite_diag_handler">udplite_diag_handler</a> = {
<a name="L189" href="source/net/ipv4/udp_diag.c#L189">189</a>         .<a href="ident?i=dump">dump</a>            = <a href="ident?i=udplite_diag_dump">udplite_diag_dump</a>,
<a name="L190" href="source/net/ipv4/udp_diag.c#L190">190</a>         .dump_one        = <a href="ident?i=udplite_diag_dump_one">udplite_diag_dump_one</a>,
<a name="L191" href="source/net/ipv4/udp_diag.c#L191">191</a>         .idiag_get_info  = <a href="ident?i=udp_diag_get_info">udp_diag_get_info</a>,
<a name="L192" href="source/net/ipv4/udp_diag.c#L192">192</a>         .idiag_type      = <a href="ident?i=IPPROTO_UDPLITE">IPPROTO_UDPLITE</a>,
<a name="L193" href="source/net/ipv4/udp_diag.c#L193">193</a> };
<a name="L194" href="source/net/ipv4/udp_diag.c#L194">194</a> 
<a name="L195" href="source/net/ipv4/udp_diag.c#L195">195</a> static int <a href="ident?i=__init">__init</a> <a href="ident?i=udp_diag_init">udp_diag_init</a>(void)
<a name="L196" href="source/net/ipv4/udp_diag.c#L196">196</a> {
<a name="L197" href="source/net/ipv4/udp_diag.c#L197">197</a>         int <a href="ident?i=err">err</a>;
<a name="L198" href="source/net/ipv4/udp_diag.c#L198">198</a> 
<a name="L199" href="source/net/ipv4/udp_diag.c#L199">199</a>         <a href="ident?i=err">err</a> = <a href="ident?i=inet_diag_register">inet_diag_register</a>(&amp;<a href="ident?i=udp_diag_handler">udp_diag_handler</a>);
<a name="L200" href="source/net/ipv4/udp_diag.c#L200">200</a>         if (<a href="ident?i=err">err</a>)
<a name="L201" href="source/net/ipv4/udp_diag.c#L201">201</a>                 goto <a href="ident?i=out">out</a>;
<a name="L202" href="source/net/ipv4/udp_diag.c#L202">202</a>         <a href="ident?i=err">err</a> = <a href="ident?i=inet_diag_register">inet_diag_register</a>(&amp;<a href="ident?i=udplite_diag_handler">udplite_diag_handler</a>);
<a name="L203" href="source/net/ipv4/udp_diag.c#L203">203</a>         if (<a href="ident?i=err">err</a>)
<a name="L204" href="source/net/ipv4/udp_diag.c#L204">204</a>                 goto out_lite;
<a name="L205" href="source/net/ipv4/udp_diag.c#L205">205</a> <a href="ident?i=out">out</a>:
<a name="L206" href="source/net/ipv4/udp_diag.c#L206">206</a>         return <a href="ident?i=err">err</a>;
<a name="L207" href="source/net/ipv4/udp_diag.c#L207">207</a> out_lite:
<a name="L208" href="source/net/ipv4/udp_diag.c#L208">208</a>         <a href="ident?i=inet_diag_unregister">inet_diag_unregister</a>(&amp;<a href="ident?i=udp_diag_handler">udp_diag_handler</a>);
<a name="L209" href="source/net/ipv4/udp_diag.c#L209">209</a>         goto <a href="ident?i=out">out</a>;
<a name="L210" href="source/net/ipv4/udp_diag.c#L210">210</a> }
<a name="L211" href="source/net/ipv4/udp_diag.c#L211">211</a> 
<a name="L212" href="source/net/ipv4/udp_diag.c#L212">212</a> static void <a href="ident?i=__exit">__exit</a> <a href="ident?i=udp_diag_exit">udp_diag_exit</a>(void)
<a name="L213" href="source/net/ipv4/udp_diag.c#L213">213</a> {
<a name="L214" href="source/net/ipv4/udp_diag.c#L214">214</a>         <a href="ident?i=inet_diag_unregister">inet_diag_unregister</a>(&amp;<a href="ident?i=udplite_diag_handler">udplite_diag_handler</a>);
<a name="L215" href="source/net/ipv4/udp_diag.c#L215">215</a>         <a href="ident?i=inet_diag_unregister">inet_diag_unregister</a>(&amp;<a href="ident?i=udp_diag_handler">udp_diag_handler</a>);
<a name="L216" href="source/net/ipv4/udp_diag.c#L216">216</a> }
<a name="L217" href="source/net/ipv4/udp_diag.c#L217">217</a> 
<a name="L218" href="source/net/ipv4/udp_diag.c#L218">218</a> <a href="ident?i=module_init">module_init</a>(<a href="ident?i=udp_diag_init">udp_diag_init</a>);
<a name="L219" href="source/net/ipv4/udp_diag.c#L219">219</a> <a href="ident?i=module_exit">module_exit</a>(<a href="ident?i=udp_diag_exit">udp_diag_exit</a>);
<a name="L220" href="source/net/ipv4/udp_diag.c#L220">220</a> <a href="ident?i=MODULE_LICENSE">MODULE_LICENSE</a>(<i>"GPL"</i>);
<a name="L221" href="source/net/ipv4/udp_diag.c#L221">221</a> <a href="ident?i=MODULE_ALIAS_NET_PF_PROTO_TYPE">MODULE_ALIAS_NET_PF_PROTO_TYPE</a>(<a href="ident?i=PF_NETLINK">PF_NETLINK</a>, <a href="ident?i=NETLINK_SOCK_DIAG">NETLINK_SOCK_DIAG</a>, 2-17 <b><i>/* AF_INET - IPPROTO_UDP */</i></b>);
<a name="L222" href="source/net/ipv4/udp_diag.c#L222">222</a> <a href="ident?i=MODULE_ALIAS_NET_PF_PROTO_TYPE">MODULE_ALIAS_NET_PF_PROTO_TYPE</a>(<a href="ident?i=PF_NETLINK">PF_NETLINK</a>, <a href="ident?i=NETLINK_SOCK_DIAG">NETLINK_SOCK_DIAG</a>, 2-136 <b><i>/* AF_INET - IPPROTO_UDPLITE */</i></b>);
<a name="L223" href="source/net/ipv4/udp_diag.c#L223">223</a> </pre></div><p>
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
