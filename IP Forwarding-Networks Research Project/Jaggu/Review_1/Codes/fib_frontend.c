<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title>Linux/net/ipv4/fib_frontend.c - Linux Cross Reference - Free Electrons</title>
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
		 &nbsp;&bull;&nbsp;<b><i>source navigation</i></b> &nbsp;&bull;&nbsp;<a href="diff/net/ipv4/fib_frontend.c">diff markup</a> &nbsp;&bull;&nbsp;<a href="ident">identifier search</a> &nbsp;&bull;&nbsp;<a href="search">freetext search</a> &nbsp;&bull;&nbsp;
		</p>
	</div>
</div>

<div id="topbar">
  
  <p>Version: &nbsp;<a href="source/net/ipv4/fib_frontend.c?v=2.0.40">2.0.40</a>&nbsp;<a href="source/net/ipv4/fib_frontend.c?v=2.2.26">2.2.26</a>&nbsp;<a href="source/net/ipv4/fib_frontend.c?v=2.4.37">2.4.37</a>&nbsp;<a href="source/net/ipv4/fib_frontend.c?v=3.5">3.5</a>&nbsp;<a href="source/net/ipv4/fib_frontend.c?v=3.6">3.6</a>&nbsp;<a href="source/net/ipv4/fib_frontend.c?v=3.7">3.7</a>&nbsp;<a href="source/net/ipv4/fib_frontend.c?v=3.8">3.8</a>&nbsp;<a href="source/net/ipv4/fib_frontend.c?v=3.9">3.9</a>&nbsp;<a href="source/net/ipv4/fib_frontend.c?v=3.10">3.10</a>&nbsp;<a href="source/net/ipv4/fib_frontend.c?v=3.11">3.11</a>&nbsp;<a href="source/net/ipv4/fib_frontend.c?v=3.12">3.12</a>&nbsp;<a href="source/net/ipv4/fib_frontend.c?v=3.13">3.13</a>&nbsp;<a href="source/net/ipv4/fib_frontend.c?v=3.14">3.14</a>&nbsp;<a href="source/net/ipv4/fib_frontend.c?v=3.15">3.15</a>&nbsp;<a href="source/net/ipv4/fib_frontend.c?v=3.16">3.16</a>&nbsp;<a href="source/net/ipv4/fib_frontend.c?v=3.17">3.17</a>&nbsp;<a href="source/net/ipv4/fib_frontend.c?v=3.18">3.18</a>&nbsp;<a href="source/net/ipv4/fib_frontend.c?v=3.19">3.19</a>&nbsp;<a href="source/net/ipv4/fib_frontend.c?v=4.0">4.0</a>&nbsp;<b><i>4.1</i></b></p>
  
</div>

<h1><a href="source/">Linux</a>/<a href="source/net/">net</a>/<a href="source/net/ipv4/">ipv4</a>/<a href="source/net/ipv4/fib_frontend.c">fib_frontend.c</a></h1>
<div id="lxrcode"><pre>  <a name="L1" href="source/net/ipv4/fib_frontend.c#L1">1</a> <b><i>/*</i></b>
  <a name="L2" href="source/net/ipv4/fib_frontend.c#L2">2</a> <b><i> * INET         An implementation of the TCP/IP protocol suite for the LINUX</i></b>
  <a name="L3" href="source/net/ipv4/fib_frontend.c#L3">3</a> <b><i> *              operating system.  INET is implemented using the  BSD Socket</i></b>
  <a name="L4" href="source/net/ipv4/fib_frontend.c#L4">4</a> <b><i> *              interface as the means of communication with the user level.</i></b>
  <a name="L5" href="source/net/ipv4/fib_frontend.c#L5">5</a> <b><i> *</i></b>
  <a name="L6" href="source/net/ipv4/fib_frontend.c#L6">6</a> <b><i> *              IPv4 Forwarding Information Base: FIB frontend.</i></b>
  <a name="L7" href="source/net/ipv4/fib_frontend.c#L7">7</a> <b><i> *</i></b>
  <a name="L8" href="source/net/ipv4/fib_frontend.c#L8">8</a> <b><i> * Authors:     Alexey Kuznetsov, &lt;kuznet@ms2.inr.ac.ru&gt;</i></b>
  <a name="L9" href="source/net/ipv4/fib_frontend.c#L9">9</a> <b><i> *</i></b>
 <a name="L10" href="source/net/ipv4/fib_frontend.c#L10">10</a> <b><i> *              This program is free software; you can redistribute it and/or</i></b>
 <a name="L11" href="source/net/ipv4/fib_frontend.c#L11">11</a> <b><i> *              modify it under the terms of the GNU General Public License</i></b>
 <a name="L12" href="source/net/ipv4/fib_frontend.c#L12">12</a> <b><i> *              as published by the Free Software Foundation; either version</i></b>
 <a name="L13" href="source/net/ipv4/fib_frontend.c#L13">13</a> <b><i> *              2 of the License, or (at your option) any later version.</i></b>
 <a name="L14" href="source/net/ipv4/fib_frontend.c#L14">14</a> <b><i> */</i></b>
 <a name="L15" href="source/net/ipv4/fib_frontend.c#L15">15</a> 
 <a name="L16" href="source/net/ipv4/fib_frontend.c#L16">16</a> #include &lt;linux/module.h&gt;
 <a name="L17" href="source/net/ipv4/fib_frontend.c#L17">17</a> #include &lt;asm/uaccess.h&gt;
 <a name="L18" href="source/net/ipv4/fib_frontend.c#L18">18</a> #include &lt;linux/bitops.h&gt;
 <a name="L19" href="source/net/ipv4/fib_frontend.c#L19">19</a> #include &lt;linux/capability.h&gt;
 <a name="L20" href="source/net/ipv4/fib_frontend.c#L20">20</a> #include &lt;linux/types.h&gt;
 <a name="L21" href="source/net/ipv4/fib_frontend.c#L21">21</a> #include &lt;linux/kernel.h&gt;
 <a name="L22" href="source/net/ipv4/fib_frontend.c#L22">22</a> #include &lt;linux/mm.h&gt;
 <a name="L23" href="source/net/ipv4/fib_frontend.c#L23">23</a> #include &lt;linux/string.h&gt;
 <a name="L24" href="source/net/ipv4/fib_frontend.c#L24">24</a> #include &lt;linux/socket.h&gt;
 <a name="L25" href="source/net/ipv4/fib_frontend.c#L25">25</a> #include &lt;linux/sockios.h&gt;
 <a name="L26" href="source/net/ipv4/fib_frontend.c#L26">26</a> #include &lt;linux/errno.h&gt;
 <a name="L27" href="source/net/ipv4/fib_frontend.c#L27">27</a> #include &lt;linux/in.h&gt;
 <a name="L28" href="source/net/ipv4/fib_frontend.c#L28">28</a> #include &lt;linux/inet.h&gt;
 <a name="L29" href="source/net/ipv4/fib_frontend.c#L29">29</a> #include &lt;linux/inetdevice.h&gt;
 <a name="L30" href="source/net/ipv4/fib_frontend.c#L30">30</a> #include &lt;linux/netdevice.h&gt;
 <a name="L31" href="source/net/ipv4/fib_frontend.c#L31">31</a> #include &lt;linux/if_addr.h&gt;
 <a name="L32" href="source/net/ipv4/fib_frontend.c#L32">32</a> #include &lt;linux/if_arp.h&gt;
 <a name="L33" href="source/net/ipv4/fib_frontend.c#L33">33</a> #include &lt;linux/skbuff.h&gt;
 <a name="L34" href="source/net/ipv4/fib_frontend.c#L34">34</a> #include &lt;linux/cache.h&gt;
 <a name="L35" href="source/net/ipv4/fib_frontend.c#L35">35</a> #include &lt;linux/init.h&gt;
 <a name="L36" href="source/net/ipv4/fib_frontend.c#L36">36</a> #include &lt;linux/list.h&gt;
 <a name="L37" href="source/net/ipv4/fib_frontend.c#L37">37</a> #include &lt;linux/slab.h&gt;
 <a name="L38" href="source/net/ipv4/fib_frontend.c#L38">38</a> 
 <a name="L39" href="source/net/ipv4/fib_frontend.c#L39">39</a> #include &lt;net/ip.h&gt;
 <a name="L40" href="source/net/ipv4/fib_frontend.c#L40">40</a> #include &lt;net/protocol.h&gt;
 <a name="L41" href="source/net/ipv4/fib_frontend.c#L41">41</a> #include &lt;net/route.h&gt;
 <a name="L42" href="source/net/ipv4/fib_frontend.c#L42">42</a> #include &lt;net/tcp.h&gt;
 <a name="L43" href="source/net/ipv4/fib_frontend.c#L43">43</a> #include &lt;net/sock.h&gt;
 <a name="L44" href="source/net/ipv4/fib_frontend.c#L44">44</a> #include &lt;net/arp.h&gt;
 <a name="L45" href="source/net/ipv4/fib_frontend.c#L45">45</a> #include &lt;net/ip_fib.h&gt;
 <a name="L46" href="source/net/ipv4/fib_frontend.c#L46">46</a> #include &lt;net/rtnetlink.h&gt;
 <a name="L47" href="source/net/ipv4/fib_frontend.c#L47">47</a> #include &lt;net/xfrm.h&gt;
 <a name="L48" href="source/net/ipv4/fib_frontend.c#L48">48</a> 
 <a name="L49" href="source/net/ipv4/fib_frontend.c#L49">49</a> #ifndef CONFIG_IP_MULTIPLE_TABLES
 <a name="L50" href="source/net/ipv4/fib_frontend.c#L50">50</a> 
 <a name="L51" href="source/net/ipv4/fib_frontend.c#L51">51</a> static int <a href="ident?i=__net_init">__net_init</a> <a href="ident?i=fib4_rules_init">fib4_rules_init</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>)
 <a name="L52" href="source/net/ipv4/fib_frontend.c#L52">52</a> {
 <a name="L53" href="source/net/ipv4/fib_frontend.c#L53">53</a>         struct <a href="ident?i=fib_table">fib_table</a> *local_table, *main_table;
 <a name="L54" href="source/net/ipv4/fib_frontend.c#L54">54</a> 
 <a name="L55" href="source/net/ipv4/fib_frontend.c#L55">55</a>         main_table  = <a href="ident?i=fib_trie_table">fib_trie_table</a>(RT_TABLE_MAIN, <a href="ident?i=NULL">NULL</a>);
 <a name="L56" href="source/net/ipv4/fib_frontend.c#L56">56</a>         if (!main_table)
 <a name="L57" href="source/net/ipv4/fib_frontend.c#L57">57</a>                 return -<a href="ident?i=ENOMEM">ENOMEM</a>;
 <a name="L58" href="source/net/ipv4/fib_frontend.c#L58">58</a> 
 <a name="L59" href="source/net/ipv4/fib_frontend.c#L59">59</a>         local_table = <a href="ident?i=fib_trie_table">fib_trie_table</a>(RT_TABLE_LOCAL, main_table);
 <a name="L60" href="source/net/ipv4/fib_frontend.c#L60">60</a>         if (!local_table)
 <a name="L61" href="source/net/ipv4/fib_frontend.c#L61">61</a>                 goto <a href="ident?i=fail">fail</a>;
 <a name="L62" href="source/net/ipv4/fib_frontend.c#L62">62</a> 
 <a name="L63" href="source/net/ipv4/fib_frontend.c#L63">63</a>         <a href="ident?i=hlist_add_head_rcu">hlist_add_head_rcu</a>(&amp;local_table-&gt;tb_hlist,
 <a name="L64" href="source/net/ipv4/fib_frontend.c#L64">64</a>                                 &amp;<a href="ident?i=net">net</a>-&gt;ipv4.fib_table_hash[<a href="ident?i=TABLE_LOCAL_INDEX">TABLE_LOCAL_INDEX</a>]);
 <a name="L65" href="source/net/ipv4/fib_frontend.c#L65">65</a>         <a href="ident?i=hlist_add_head_rcu">hlist_add_head_rcu</a>(&amp;main_table-&gt;tb_hlist,
 <a name="L66" href="source/net/ipv4/fib_frontend.c#L66">66</a>                                 &amp;<a href="ident?i=net">net</a>-&gt;ipv4.fib_table_hash[<a href="ident?i=TABLE_MAIN_INDEX">TABLE_MAIN_INDEX</a>]);
 <a name="L67" href="source/net/ipv4/fib_frontend.c#L67">67</a>         return 0;
 <a name="L68" href="source/net/ipv4/fib_frontend.c#L68">68</a> 
 <a name="L69" href="source/net/ipv4/fib_frontend.c#L69">69</a> <a href="ident?i=fail">fail</a>:
 <a name="L70" href="source/net/ipv4/fib_frontend.c#L70">70</a>         <a href="ident?i=fib_free_table">fib_free_table</a>(main_table);
 <a name="L71" href="source/net/ipv4/fib_frontend.c#L71">71</a>         return -<a href="ident?i=ENOMEM">ENOMEM</a>;
 <a name="L72" href="source/net/ipv4/fib_frontend.c#L72">72</a> }
 <a name="L73" href="source/net/ipv4/fib_frontend.c#L73">73</a> #else
 <a name="L74" href="source/net/ipv4/fib_frontend.c#L74">74</a> 
 <a name="L75" href="source/net/ipv4/fib_frontend.c#L75">75</a> struct <a href="ident?i=fib_table">fib_table</a> *<a href="ident?i=fib_new_table">fib_new_table</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>, <a href="ident?i=u32">u32</a> <a href="ident?i=id">id</a>)
 <a name="L76" href="source/net/ipv4/fib_frontend.c#L76">76</a> {
 <a name="L77" href="source/net/ipv4/fib_frontend.c#L77">77</a>         struct <a href="ident?i=fib_table">fib_table</a> *<a href="ident?i=tb">tb</a>, *<a href="ident?i=alias">alias</a> = <a href="ident?i=NULL">NULL</a>;
 <a name="L78" href="source/net/ipv4/fib_frontend.c#L78">78</a>         unsigned int <a href="ident?i=h">h</a>;
 <a name="L79" href="source/net/ipv4/fib_frontend.c#L79">79</a> 
 <a name="L80" href="source/net/ipv4/fib_frontend.c#L80">80</a>         if (<a href="ident?i=id">id</a> == 0)
 <a name="L81" href="source/net/ipv4/fib_frontend.c#L81">81</a>                 <a href="ident?i=id">id</a> = RT_TABLE_MAIN;
 <a name="L82" href="source/net/ipv4/fib_frontend.c#L82">82</a>         <a href="ident?i=tb">tb</a> = <a href="ident?i=fib_get_table">fib_get_table</a>(<a href="ident?i=net">net</a>, <a href="ident?i=id">id</a>);
 <a name="L83" href="source/net/ipv4/fib_frontend.c#L83">83</a>         if (<a href="ident?i=tb">tb</a>)
 <a name="L84" href="source/net/ipv4/fib_frontend.c#L84">84</a>                 return <a href="ident?i=tb">tb</a>;
 <a name="L85" href="source/net/ipv4/fib_frontend.c#L85">85</a> 
 <a name="L86" href="source/net/ipv4/fib_frontend.c#L86">86</a>         if (<a href="ident?i=id">id</a> == RT_TABLE_LOCAL)
 <a name="L87" href="source/net/ipv4/fib_frontend.c#L87">87</a>                 <a href="ident?i=alias">alias</a> = <a href="ident?i=fib_new_table">fib_new_table</a>(<a href="ident?i=net">net</a>, RT_TABLE_MAIN);
 <a name="L88" href="source/net/ipv4/fib_frontend.c#L88">88</a> 
 <a name="L89" href="source/net/ipv4/fib_frontend.c#L89">89</a>         <a href="ident?i=tb">tb</a> = <a href="ident?i=fib_trie_table">fib_trie_table</a>(<a href="ident?i=id">id</a>, <a href="ident?i=alias">alias</a>);
 <a name="L90" href="source/net/ipv4/fib_frontend.c#L90">90</a>         if (!<a href="ident?i=tb">tb</a>)
 <a name="L91" href="source/net/ipv4/fib_frontend.c#L91">91</a>                 return <a href="ident?i=NULL">NULL</a>;
 <a name="L92" href="source/net/ipv4/fib_frontend.c#L92">92</a> 
 <a name="L93" href="source/net/ipv4/fib_frontend.c#L93">93</a>         switch (<a href="ident?i=id">id</a>) {
 <a name="L94" href="source/net/ipv4/fib_frontend.c#L94">94</a>         case RT_TABLE_LOCAL:
 <a name="L95" href="source/net/ipv4/fib_frontend.c#L95">95</a>                 <a href="ident?i=rcu_assign_pointer">rcu_assign_pointer</a>(<a href="ident?i=net">net</a>-&gt;ipv4.fib_local, <a href="ident?i=tb">tb</a>);
 <a name="L96" href="source/net/ipv4/fib_frontend.c#L96">96</a>                 break;
 <a name="L97" href="source/net/ipv4/fib_frontend.c#L97">97</a>         case RT_TABLE_MAIN:
 <a name="L98" href="source/net/ipv4/fib_frontend.c#L98">98</a>                 <a href="ident?i=rcu_assign_pointer">rcu_assign_pointer</a>(<a href="ident?i=net">net</a>-&gt;ipv4.fib_main, <a href="ident?i=tb">tb</a>);
 <a name="L99" href="source/net/ipv4/fib_frontend.c#L99">99</a>                 break;
<a name="L100" href="source/net/ipv4/fib_frontend.c#L100">100</a>         case RT_TABLE_DEFAULT:
<a name="L101" href="source/net/ipv4/fib_frontend.c#L101">101</a>                 <a href="ident?i=rcu_assign_pointer">rcu_assign_pointer</a>(<a href="ident?i=net">net</a>-&gt;ipv4.fib_default, <a href="ident?i=tb">tb</a>);
<a name="L102" href="source/net/ipv4/fib_frontend.c#L102">102</a>                 break;
<a name="L103" href="source/net/ipv4/fib_frontend.c#L103">103</a>         default:
<a name="L104" href="source/net/ipv4/fib_frontend.c#L104">104</a>                 break;
<a name="L105" href="source/net/ipv4/fib_frontend.c#L105">105</a>         }
<a name="L106" href="source/net/ipv4/fib_frontend.c#L106">106</a> 
<a name="L107" href="source/net/ipv4/fib_frontend.c#L107">107</a>         <a href="ident?i=h">h</a> = <a href="ident?i=id">id</a> &amp; (<a href="ident?i=FIB_TABLE_HASHSZ">FIB_TABLE_HASHSZ</a> - 1);
<a name="L108" href="source/net/ipv4/fib_frontend.c#L108">108</a>         <a href="ident?i=hlist_add_head_rcu">hlist_add_head_rcu</a>(&amp;<a href="ident?i=tb">tb</a>-&gt;tb_hlist, &amp;<a href="ident?i=net">net</a>-&gt;ipv4.fib_table_hash[<a href="ident?i=h">h</a>]);
<a name="L109" href="source/net/ipv4/fib_frontend.c#L109">109</a>         return <a href="ident?i=tb">tb</a>;
<a name="L110" href="source/net/ipv4/fib_frontend.c#L110">110</a> }
<a name="L111" href="source/net/ipv4/fib_frontend.c#L111">111</a> 
<a name="L112" href="source/net/ipv4/fib_frontend.c#L112">112</a> <b><i>/* caller must hold either rtnl or rcu read lock */</i></b>
<a name="L113" href="source/net/ipv4/fib_frontend.c#L113">113</a> struct <a href="ident?i=fib_table">fib_table</a> *<a href="ident?i=fib_get_table">fib_get_table</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>, <a href="ident?i=u32">u32</a> <a href="ident?i=id">id</a>)
<a name="L114" href="source/net/ipv4/fib_frontend.c#L114">114</a> {
<a name="L115" href="source/net/ipv4/fib_frontend.c#L115">115</a>         struct <a href="ident?i=fib_table">fib_table</a> *<a href="ident?i=tb">tb</a>;
<a name="L116" href="source/net/ipv4/fib_frontend.c#L116">116</a>         struct <a href="ident?i=hlist_head">hlist_head</a> *<a href="ident?i=head">head</a>;
<a name="L117" href="source/net/ipv4/fib_frontend.c#L117">117</a>         unsigned int <a href="ident?i=h">h</a>;
<a name="L118" href="source/net/ipv4/fib_frontend.c#L118">118</a> 
<a name="L119" href="source/net/ipv4/fib_frontend.c#L119">119</a>         if (<a href="ident?i=id">id</a> == 0)
<a name="L120" href="source/net/ipv4/fib_frontend.c#L120">120</a>                 <a href="ident?i=id">id</a> = RT_TABLE_MAIN;
<a name="L121" href="source/net/ipv4/fib_frontend.c#L121">121</a>         <a href="ident?i=h">h</a> = <a href="ident?i=id">id</a> &amp; (<a href="ident?i=FIB_TABLE_HASHSZ">FIB_TABLE_HASHSZ</a> - 1);
<a name="L122" href="source/net/ipv4/fib_frontend.c#L122">122</a> 
<a name="L123" href="source/net/ipv4/fib_frontend.c#L123">123</a>         <a href="ident?i=head">head</a> = &amp;<a href="ident?i=net">net</a>-&gt;ipv4.fib_table_hash[<a href="ident?i=h">h</a>];
<a name="L124" href="source/net/ipv4/fib_frontend.c#L124">124</a>         <a href="ident?i=hlist_for_each_entry_rcu">hlist_for_each_entry_rcu</a>(<a href="ident?i=tb">tb</a>, <a href="ident?i=head">head</a>, tb_hlist) {
<a name="L125" href="source/net/ipv4/fib_frontend.c#L125">125</a>                 if (<a href="ident?i=tb">tb</a>-&gt;tb_id == <a href="ident?i=id">id</a>)
<a name="L126" href="source/net/ipv4/fib_frontend.c#L126">126</a>                         return <a href="ident?i=tb">tb</a>;
<a name="L127" href="source/net/ipv4/fib_frontend.c#L127">127</a>         }
<a name="L128" href="source/net/ipv4/fib_frontend.c#L128">128</a>         return <a href="ident?i=NULL">NULL</a>;
<a name="L129" href="source/net/ipv4/fib_frontend.c#L129">129</a> }
<a name="L130" href="source/net/ipv4/fib_frontend.c#L130">130</a> #endif <b><i>/* CONFIG_IP_MULTIPLE_TABLES */</i></b>
<a name="L131" href="source/net/ipv4/fib_frontend.c#L131">131</a> 
<a name="L132" href="source/net/ipv4/fib_frontend.c#L132">132</a> static void <a href="ident?i=fib_replace_table">fib_replace_table</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>, struct <a href="ident?i=fib_table">fib_table</a> *<a href="ident?i=old">old</a>,
<a name="L133" href="source/net/ipv4/fib_frontend.c#L133">133</a>                               struct <a href="ident?i=fib_table">fib_table</a> *<a href="ident?i=new">new</a>)
<a name="L134" href="source/net/ipv4/fib_frontend.c#L134">134</a> {
<a name="L135" href="source/net/ipv4/fib_frontend.c#L135">135</a> #ifdef CONFIG_IP_MULTIPLE_TABLES
<a name="L136" href="source/net/ipv4/fib_frontend.c#L136">136</a>         switch (<a href="ident?i=new">new</a>-&gt;tb_id) {
<a name="L137" href="source/net/ipv4/fib_frontend.c#L137">137</a>         case RT_TABLE_LOCAL:
<a name="L138" href="source/net/ipv4/fib_frontend.c#L138">138</a>                 <a href="ident?i=rcu_assign_pointer">rcu_assign_pointer</a>(<a href="ident?i=net">net</a>-&gt;ipv4.fib_local, <a href="ident?i=new">new</a>);
<a name="L139" href="source/net/ipv4/fib_frontend.c#L139">139</a>                 break;
<a name="L140" href="source/net/ipv4/fib_frontend.c#L140">140</a>         case RT_TABLE_MAIN:
<a name="L141" href="source/net/ipv4/fib_frontend.c#L141">141</a>                 <a href="ident?i=rcu_assign_pointer">rcu_assign_pointer</a>(<a href="ident?i=net">net</a>-&gt;ipv4.fib_main, <a href="ident?i=new">new</a>);
<a name="L142" href="source/net/ipv4/fib_frontend.c#L142">142</a>                 break;
<a name="L143" href="source/net/ipv4/fib_frontend.c#L143">143</a>         case RT_TABLE_DEFAULT:
<a name="L144" href="source/net/ipv4/fib_frontend.c#L144">144</a>                 <a href="ident?i=rcu_assign_pointer">rcu_assign_pointer</a>(<a href="ident?i=net">net</a>-&gt;ipv4.fib_default, <a href="ident?i=new">new</a>);
<a name="L145" href="source/net/ipv4/fib_frontend.c#L145">145</a>                 break;
<a name="L146" href="source/net/ipv4/fib_frontend.c#L146">146</a>         default:
<a name="L147" href="source/net/ipv4/fib_frontend.c#L147">147</a>                 break;
<a name="L148" href="source/net/ipv4/fib_frontend.c#L148">148</a>         }
<a name="L149" href="source/net/ipv4/fib_frontend.c#L149">149</a> 
<a name="L150" href="source/net/ipv4/fib_frontend.c#L150">150</a> #endif
<a name="L151" href="source/net/ipv4/fib_frontend.c#L151">151</a>         <b><i>/* replace the old table in the hlist */</i></b>
<a name="L152" href="source/net/ipv4/fib_frontend.c#L152">152</a>         <a href="ident?i=hlist_replace_rcu">hlist_replace_rcu</a>(&amp;<a href="ident?i=old">old</a>-&gt;tb_hlist, &amp;<a href="ident?i=new">new</a>-&gt;tb_hlist);
<a name="L153" href="source/net/ipv4/fib_frontend.c#L153">153</a> }
<a name="L154" href="source/net/ipv4/fib_frontend.c#L154">154</a> 
<a name="L155" href="source/net/ipv4/fib_frontend.c#L155">155</a> int <a href="ident?i=fib_unmerge">fib_unmerge</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>)
<a name="L156" href="source/net/ipv4/fib_frontend.c#L156">156</a> {
<a name="L157" href="source/net/ipv4/fib_frontend.c#L157">157</a>         struct <a href="ident?i=fib_table">fib_table</a> *<a href="ident?i=old">old</a>, *<a href="ident?i=new">new</a>;
<a name="L158" href="source/net/ipv4/fib_frontend.c#L158">158</a> 
<a name="L159" href="source/net/ipv4/fib_frontend.c#L159">159</a>         <b><i>/* attempt to fetch local table if it has been allocated */</i></b>
<a name="L160" href="source/net/ipv4/fib_frontend.c#L160">160</a>         <a href="ident?i=old">old</a> = <a href="ident?i=fib_get_table">fib_get_table</a>(<a href="ident?i=net">net</a>, RT_TABLE_LOCAL);
<a name="L161" href="source/net/ipv4/fib_frontend.c#L161">161</a>         if (!<a href="ident?i=old">old</a>)
<a name="L162" href="source/net/ipv4/fib_frontend.c#L162">162</a>                 return 0;
<a name="L163" href="source/net/ipv4/fib_frontend.c#L163">163</a> 
<a name="L164" href="source/net/ipv4/fib_frontend.c#L164">164</a>         <a href="ident?i=new">new</a> = <a href="ident?i=fib_trie_unmerge">fib_trie_unmerge</a>(<a href="ident?i=old">old</a>);
<a name="L165" href="source/net/ipv4/fib_frontend.c#L165">165</a>         if (!<a href="ident?i=new">new</a>)
<a name="L166" href="source/net/ipv4/fib_frontend.c#L166">166</a>                 return -<a href="ident?i=ENOMEM">ENOMEM</a>;
<a name="L167" href="source/net/ipv4/fib_frontend.c#L167">167</a> 
<a name="L168" href="source/net/ipv4/fib_frontend.c#L168">168</a>         <b><i>/* replace merged table with clean table */</i></b>
<a name="L169" href="source/net/ipv4/fib_frontend.c#L169">169</a>         if (<a href="ident?i=new">new</a> != <a href="ident?i=old">old</a>) {
<a name="L170" href="source/net/ipv4/fib_frontend.c#L170">170</a>                 <a href="ident?i=fib_replace_table">fib_replace_table</a>(<a href="ident?i=net">net</a>, <a href="ident?i=old">old</a>, <a href="ident?i=new">new</a>);
<a name="L171" href="source/net/ipv4/fib_frontend.c#L171">171</a>                 <a href="ident?i=fib_free_table">fib_free_table</a>(<a href="ident?i=old">old</a>);
<a name="L172" href="source/net/ipv4/fib_frontend.c#L172">172</a>         }
<a name="L173" href="source/net/ipv4/fib_frontend.c#L173">173</a> 
<a name="L174" href="source/net/ipv4/fib_frontend.c#L174">174</a>         return 0;
<a name="L175" href="source/net/ipv4/fib_frontend.c#L175">175</a> }
<a name="L176" href="source/net/ipv4/fib_frontend.c#L176">176</a> 
<a name="L177" href="source/net/ipv4/fib_frontend.c#L177">177</a> static void <a href="ident?i=fib_flush">fib_flush</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>)
<a name="L178" href="source/net/ipv4/fib_frontend.c#L178">178</a> {
<a name="L179" href="source/net/ipv4/fib_frontend.c#L179">179</a>         int flushed = 0;
<a name="L180" href="source/net/ipv4/fib_frontend.c#L180">180</a>         unsigned int <a href="ident?i=h">h</a>;
<a name="L181" href="source/net/ipv4/fib_frontend.c#L181">181</a> 
<a name="L182" href="source/net/ipv4/fib_frontend.c#L182">182</a>         for (<a href="ident?i=h">h</a> = 0; <a href="ident?i=h">h</a> &lt; <a href="ident?i=FIB_TABLE_HASHSZ">FIB_TABLE_HASHSZ</a>; <a href="ident?i=h">h</a>++) {
<a name="L183" href="source/net/ipv4/fib_frontend.c#L183">183</a>                 struct <a href="ident?i=hlist_head">hlist_head</a> *<a href="ident?i=head">head</a> = &amp;<a href="ident?i=net">net</a>-&gt;ipv4.fib_table_hash[<a href="ident?i=h">h</a>];
<a name="L184" href="source/net/ipv4/fib_frontend.c#L184">184</a>                 struct <a href="ident?i=hlist_node">hlist_node</a> *<a href="ident?i=tmp">tmp</a>;
<a name="L185" href="source/net/ipv4/fib_frontend.c#L185">185</a>                 struct <a href="ident?i=fib_table">fib_table</a> *<a href="ident?i=tb">tb</a>;
<a name="L186" href="source/net/ipv4/fib_frontend.c#L186">186</a> 
<a name="L187" href="source/net/ipv4/fib_frontend.c#L187">187</a>                 <a href="ident?i=hlist_for_each_entry_safe">hlist_for_each_entry_safe</a>(<a href="ident?i=tb">tb</a>, <a href="ident?i=tmp">tmp</a>, <a href="ident?i=head">head</a>, tb_hlist)
<a name="L188" href="source/net/ipv4/fib_frontend.c#L188">188</a>                         flushed += <a href="ident?i=fib_table_flush">fib_table_flush</a>(<a href="ident?i=tb">tb</a>);
<a name="L189" href="source/net/ipv4/fib_frontend.c#L189">189</a>         }
<a name="L190" href="source/net/ipv4/fib_frontend.c#L190">190</a> 
<a name="L191" href="source/net/ipv4/fib_frontend.c#L191">191</a>         if (flushed)
<a name="L192" href="source/net/ipv4/fib_frontend.c#L192">192</a>                 <a href="ident?i=rt_cache_flush">rt_cache_flush</a>(<a href="ident?i=net">net</a>);
<a name="L193" href="source/net/ipv4/fib_frontend.c#L193">193</a> }
<a name="L194" href="source/net/ipv4/fib_frontend.c#L194">194</a> 
<a name="L195" href="source/net/ipv4/fib_frontend.c#L195">195</a> void <a href="ident?i=fib_flush_external">fib_flush_external</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>)
<a name="L196" href="source/net/ipv4/fib_frontend.c#L196">196</a> {
<a name="L197" href="source/net/ipv4/fib_frontend.c#L197">197</a>         struct <a href="ident?i=fib_table">fib_table</a> *<a href="ident?i=tb">tb</a>;
<a name="L198" href="source/net/ipv4/fib_frontend.c#L198">198</a>         struct <a href="ident?i=hlist_head">hlist_head</a> *<a href="ident?i=head">head</a>;
<a name="L199" href="source/net/ipv4/fib_frontend.c#L199">199</a>         unsigned int <a href="ident?i=h">h</a>;
<a name="L200" href="source/net/ipv4/fib_frontend.c#L200">200</a> 
<a name="L201" href="source/net/ipv4/fib_frontend.c#L201">201</a>         for (<a href="ident?i=h">h</a> = 0; <a href="ident?i=h">h</a> &lt; <a href="ident?i=FIB_TABLE_HASHSZ">FIB_TABLE_HASHSZ</a>; <a href="ident?i=h">h</a>++) {
<a name="L202" href="source/net/ipv4/fib_frontend.c#L202">202</a>                 <a href="ident?i=head">head</a> = &amp;<a href="ident?i=net">net</a>-&gt;ipv4.fib_table_hash[<a href="ident?i=h">h</a>];
<a name="L203" href="source/net/ipv4/fib_frontend.c#L203">203</a>                 <a href="ident?i=hlist_for_each_entry">hlist_for_each_entry</a>(<a href="ident?i=tb">tb</a>, <a href="ident?i=head">head</a>, tb_hlist)
<a name="L204" href="source/net/ipv4/fib_frontend.c#L204">204</a>                         <a href="ident?i=fib_table_flush_external">fib_table_flush_external</a>(<a href="ident?i=tb">tb</a>);
<a name="L205" href="source/net/ipv4/fib_frontend.c#L205">205</a>         }
<a name="L206" href="source/net/ipv4/fib_frontend.c#L206">206</a> }
<a name="L207" href="source/net/ipv4/fib_frontend.c#L207">207</a> 
<a name="L208" href="source/net/ipv4/fib_frontend.c#L208">208</a> <b><i>/*</i></b>
<a name="L209" href="source/net/ipv4/fib_frontend.c#L209">209</a> <b><i> * Find address type as if only "dev" was present in the system. If</i></b>
<a name="L210" href="source/net/ipv4/fib_frontend.c#L210">210</a> <b><i> * on_dev is NULL then all interfaces are taken into consideration.</i></b>
<a name="L211" href="source/net/ipv4/fib_frontend.c#L211">211</a> <b><i> */</i></b>
<a name="L212" href="source/net/ipv4/fib_frontend.c#L212">212</a> static inline unsigned int <a href="ident?i=__inet_dev_addr_type">__inet_dev_addr_type</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>,
<a name="L213" href="source/net/ipv4/fib_frontend.c#L213">213</a>                                                 const struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>,
<a name="L214" href="source/net/ipv4/fib_frontend.c#L214">214</a>                                                 <a href="ident?i=__be32">__be32</a> <a href="ident?i=addr">addr</a>)
<a name="L215" href="source/net/ipv4/fib_frontend.c#L215">215</a> {
<a name="L216" href="source/net/ipv4/fib_frontend.c#L216">216</a>         struct <a href="ident?i=flowi4">flowi4</a>           fl4 = { .<a href="ident?i=daddr">daddr</a> = <a href="ident?i=addr">addr</a> };
<a name="L217" href="source/net/ipv4/fib_frontend.c#L217">217</a>         struct <a href="ident?i=fib_result">fib_result</a>       <a href="ident?i=res">res</a>;
<a name="L218" href="source/net/ipv4/fib_frontend.c#L218">218</a>         unsigned int <a href="ident?i=ret">ret</a> = RTN_BROADCAST;
<a name="L219" href="source/net/ipv4/fib_frontend.c#L219">219</a>         struct <a href="ident?i=fib_table">fib_table</a> *local_table;
<a name="L220" href="source/net/ipv4/fib_frontend.c#L220">220</a> 
<a name="L221" href="source/net/ipv4/fib_frontend.c#L221">221</a>         if (<a href="ident?i=ipv4_is_zeronet">ipv4_is_zeronet</a>(<a href="ident?i=addr">addr</a>) || <a href="ident?i=ipv4_is_lbcast">ipv4_is_lbcast</a>(<a href="ident?i=addr">addr</a>))
<a name="L222" href="source/net/ipv4/fib_frontend.c#L222">222</a>                 return RTN_BROADCAST;
<a name="L223" href="source/net/ipv4/fib_frontend.c#L223">223</a>         if (<a href="ident?i=ipv4_is_multicast">ipv4_is_multicast</a>(<a href="ident?i=addr">addr</a>))
<a name="L224" href="source/net/ipv4/fib_frontend.c#L224">224</a>                 return RTN_MULTICAST;
<a name="L225" href="source/net/ipv4/fib_frontend.c#L225">225</a> 
<a name="L226" href="source/net/ipv4/fib_frontend.c#L226">226</a>         <a href="ident?i=rcu_read_lock">rcu_read_lock</a>();
<a name="L227" href="source/net/ipv4/fib_frontend.c#L227">227</a> 
<a name="L228" href="source/net/ipv4/fib_frontend.c#L228">228</a>         local_table = <a href="ident?i=fib_get_table">fib_get_table</a>(<a href="ident?i=net">net</a>, RT_TABLE_LOCAL);
<a name="L229" href="source/net/ipv4/fib_frontend.c#L229">229</a>         if (local_table) {
<a name="L230" href="source/net/ipv4/fib_frontend.c#L230">230</a>                 <a href="ident?i=ret">ret</a> = RTN_UNICAST;
<a name="L231" href="source/net/ipv4/fib_frontend.c#L231">231</a>                 if (!<a href="ident?i=fib_table_lookup">fib_table_lookup</a>(local_table, &amp;fl4, &amp;<a href="ident?i=res">res</a>, <a href="ident?i=FIB_LOOKUP_NOREF">FIB_LOOKUP_NOREF</a>)) {
<a name="L232" href="source/net/ipv4/fib_frontend.c#L232">232</a>                         if (!<a href="ident?i=dev">dev</a> || <a href="ident?i=dev">dev</a> == <a href="ident?i=res">res</a>.fi-&gt;<a href="ident?i=fib_dev">fib_dev</a>)
<a name="L233" href="source/net/ipv4/fib_frontend.c#L233">233</a>                                 <a href="ident?i=ret">ret</a> = <a href="ident?i=res">res</a>.<a href="ident?i=type">type</a>;
<a name="L234" href="source/net/ipv4/fib_frontend.c#L234">234</a>                 }
<a name="L235" href="source/net/ipv4/fib_frontend.c#L235">235</a>         }
<a name="L236" href="source/net/ipv4/fib_frontend.c#L236">236</a> 
<a name="L237" href="source/net/ipv4/fib_frontend.c#L237">237</a>         <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L238" href="source/net/ipv4/fib_frontend.c#L238">238</a>         return <a href="ident?i=ret">ret</a>;
<a name="L239" href="source/net/ipv4/fib_frontend.c#L239">239</a> }
<a name="L240" href="source/net/ipv4/fib_frontend.c#L240">240</a> 
<a name="L241" href="source/net/ipv4/fib_frontend.c#L241">241</a> unsigned int <a href="ident?i=inet_addr_type">inet_addr_type</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>, <a href="ident?i=__be32">__be32</a> <a href="ident?i=addr">addr</a>)
<a name="L242" href="source/net/ipv4/fib_frontend.c#L242">242</a> {
<a name="L243" href="source/net/ipv4/fib_frontend.c#L243">243</a>         return <a href="ident?i=__inet_dev_addr_type">__inet_dev_addr_type</a>(<a href="ident?i=net">net</a>, <a href="ident?i=NULL">NULL</a>, <a href="ident?i=addr">addr</a>);
<a name="L244" href="source/net/ipv4/fib_frontend.c#L244">244</a> }
<a name="L245" href="source/net/ipv4/fib_frontend.c#L245">245</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=inet_addr_type">inet_addr_type</a>);
<a name="L246" href="source/net/ipv4/fib_frontend.c#L246">246</a> 
<a name="L247" href="source/net/ipv4/fib_frontend.c#L247">247</a> unsigned int <a href="ident?i=inet_dev_addr_type">inet_dev_addr_type</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>, const struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>,
<a name="L248" href="source/net/ipv4/fib_frontend.c#L248">248</a>                                 <a href="ident?i=__be32">__be32</a> <a href="ident?i=addr">addr</a>)
<a name="L249" href="source/net/ipv4/fib_frontend.c#L249">249</a> {
<a name="L250" href="source/net/ipv4/fib_frontend.c#L250">250</a>         return <a href="ident?i=__inet_dev_addr_type">__inet_dev_addr_type</a>(<a href="ident?i=net">net</a>, <a href="ident?i=dev">dev</a>, <a href="ident?i=addr">addr</a>);
<a name="L251" href="source/net/ipv4/fib_frontend.c#L251">251</a> }
<a name="L252" href="source/net/ipv4/fib_frontend.c#L252">252</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=inet_dev_addr_type">inet_dev_addr_type</a>);
<a name="L253" href="source/net/ipv4/fib_frontend.c#L253">253</a> 
<a name="L254" href="source/net/ipv4/fib_frontend.c#L254">254</a> <a href="ident?i=__be32">__be32</a> <a href="ident?i=fib_compute_spec_dst">fib_compute_spec_dst</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L255" href="source/net/ipv4/fib_frontend.c#L255">255</a> {
<a name="L256" href="source/net/ipv4/fib_frontend.c#L256">256</a>         struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a> = <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=dev">dev</a>;
<a name="L257" href="source/net/ipv4/fib_frontend.c#L257">257</a>         struct <a href="ident?i=in_device">in_device</a> *in_dev;
<a name="L258" href="source/net/ipv4/fib_frontend.c#L258">258</a>         struct <a href="ident?i=fib_result">fib_result</a> <a href="ident?i=res">res</a>;
<a name="L259" href="source/net/ipv4/fib_frontend.c#L259">259</a>         struct <a href="ident?i=rtable">rtable</a> *<a href="ident?i=rt">rt</a>;
<a name="L260" href="source/net/ipv4/fib_frontend.c#L260">260</a>         struct <a href="ident?i=flowi4">flowi4</a> fl4;
<a name="L261" href="source/net/ipv4/fib_frontend.c#L261">261</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>;
<a name="L262" href="source/net/ipv4/fib_frontend.c#L262">262</a>         int <a href="ident?i=scope">scope</a>;
<a name="L263" href="source/net/ipv4/fib_frontend.c#L263">263</a> 
<a name="L264" href="source/net/ipv4/fib_frontend.c#L264">264</a>         <a href="ident?i=rt">rt</a> = <a href="ident?i=skb_rtable">skb_rtable</a>(<a href="ident?i=skb">skb</a>);
<a name="L265" href="source/net/ipv4/fib_frontend.c#L265">265</a>         if ((<a href="ident?i=rt">rt</a>-&gt;rt_flags &amp; (<a href="ident?i=RTCF_BROADCAST">RTCF_BROADCAST</a> | <a href="ident?i=RTCF_MULTICAST">RTCF_MULTICAST</a> | <a href="ident?i=RTCF_LOCAL">RTCF_LOCAL</a>)) ==
<a name="L266" href="source/net/ipv4/fib_frontend.c#L266">266</a>             <a href="ident?i=RTCF_LOCAL">RTCF_LOCAL</a>)
<a name="L267" href="source/net/ipv4/fib_frontend.c#L267">267</a>                 return <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=daddr">daddr</a>;
<a name="L268" href="source/net/ipv4/fib_frontend.c#L268">268</a> 
<a name="L269" href="source/net/ipv4/fib_frontend.c#L269">269</a>         in_dev = <a href="ident?i=__in_dev_get_rcu">__in_dev_get_rcu</a>(<a href="ident?i=dev">dev</a>);
<a name="L270" href="source/net/ipv4/fib_frontend.c#L270">270</a>         <a href="ident?i=BUG_ON">BUG_ON</a>(!in_dev);
<a name="L271" href="source/net/ipv4/fib_frontend.c#L271">271</a> 
<a name="L272" href="source/net/ipv4/fib_frontend.c#L272">272</a>         <a href="ident?i=net">net</a> = <a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=dev">dev</a>);
<a name="L273" href="source/net/ipv4/fib_frontend.c#L273">273</a> 
<a name="L274" href="source/net/ipv4/fib_frontend.c#L274">274</a>         <a href="ident?i=scope">scope</a> = RT_SCOPE_UNIVERSE;
<a name="L275" href="source/net/ipv4/fib_frontend.c#L275">275</a>         if (!<a href="ident?i=ipv4_is_zeronet">ipv4_is_zeronet</a>(<a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=saddr">saddr</a>)) {
<a name="L276" href="source/net/ipv4/fib_frontend.c#L276">276</a>                 fl4.<a href="ident?i=flowi4_oif">flowi4_oif</a> = 0;
<a name="L277" href="source/net/ipv4/fib_frontend.c#L277">277</a>                 fl4.<a href="ident?i=flowi4_iif">flowi4_iif</a> = <a href="ident?i=LOOPBACK_IFINDEX">LOOPBACK_IFINDEX</a>;
<a name="L278" href="source/net/ipv4/fib_frontend.c#L278">278</a>                 fl4.<a href="ident?i=daddr">daddr</a> = <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=saddr">saddr</a>;
<a name="L279" href="source/net/ipv4/fib_frontend.c#L279">279</a>                 fl4.<a href="ident?i=saddr">saddr</a> = 0;
<a name="L280" href="source/net/ipv4/fib_frontend.c#L280">280</a>                 fl4.<a href="ident?i=flowi4_tos">flowi4_tos</a> = <a href="ident?i=RT_TOS">RT_TOS</a>(<a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;tos);
<a name="L281" href="source/net/ipv4/fib_frontend.c#L281">281</a>                 fl4.<a href="ident?i=flowi4_scope">flowi4_scope</a> = <a href="ident?i=scope">scope</a>;
<a name="L282" href="source/net/ipv4/fib_frontend.c#L282">282</a>                 fl4.<a href="ident?i=flowi4_mark">flowi4_mark</a> = <a href="ident?i=IN_DEV_SRC_VMARK">IN_DEV_SRC_VMARK</a>(in_dev) ? <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=mark">mark</a> : 0;
<a name="L283" href="source/net/ipv4/fib_frontend.c#L283">283</a>                 if (!<a href="ident?i=fib_lookup">fib_lookup</a>(<a href="ident?i=net">net</a>, &amp;fl4, &amp;<a href="ident?i=res">res</a>))
<a name="L284" href="source/net/ipv4/fib_frontend.c#L284">284</a>                         return <a href="ident?i=FIB_RES_PREFSRC">FIB_RES_PREFSRC</a>(<a href="ident?i=net">net</a>, <a href="ident?i=res">res</a>);
<a name="L285" href="source/net/ipv4/fib_frontend.c#L285">285</a>         } else {
<a name="L286" href="source/net/ipv4/fib_frontend.c#L286">286</a>                 <a href="ident?i=scope">scope</a> = RT_SCOPE_LINK;
<a name="L287" href="source/net/ipv4/fib_frontend.c#L287">287</a>         }
<a name="L288" href="source/net/ipv4/fib_frontend.c#L288">288</a> 
<a name="L289" href="source/net/ipv4/fib_frontend.c#L289">289</a>         return <a href="ident?i=inet_select_addr">inet_select_addr</a>(<a href="ident?i=dev">dev</a>, <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=saddr">saddr</a>, <a href="ident?i=scope">scope</a>);
<a name="L290" href="source/net/ipv4/fib_frontend.c#L290">290</a> }
<a name="L291" href="source/net/ipv4/fib_frontend.c#L291">291</a> 
<a name="L292" href="source/net/ipv4/fib_frontend.c#L292">292</a> <b><i>/* Given (packet source, input interface) and optional (dst, oif, tos):</i></b>
<a name="L293" href="source/net/ipv4/fib_frontend.c#L293">293</a> <b><i> * - (main) check, that source is valid i.e. not broadcast or our local</i></b>
<a name="L294" href="source/net/ipv4/fib_frontend.c#L294">294</a> <b><i> *   address.</i></b>
<a name="L295" href="source/net/ipv4/fib_frontend.c#L295">295</a> <b><i> * - figure out what "logical" interface this packet arrived</i></b>
<a name="L296" href="source/net/ipv4/fib_frontend.c#L296">296</a> <b><i> *   and calculate "specific destination" address.</i></b>
<a name="L297" href="source/net/ipv4/fib_frontend.c#L297">297</a> <b><i> * - check, that packet arrived from expected physical interface.</i></b>
<a name="L298" href="source/net/ipv4/fib_frontend.c#L298">298</a> <b><i> * called with rcu_read_lock()</i></b>
<a name="L299" href="source/net/ipv4/fib_frontend.c#L299">299</a> <b><i> */</i></b>
<a name="L300" href="source/net/ipv4/fib_frontend.c#L300">300</a> static int <a href="ident?i=__fib_validate_source">__fib_validate_source</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, <a href="ident?i=__be32">__be32</a> <a href="ident?i=src">src</a>, <a href="ident?i=__be32">__be32</a> <a href="ident?i=dst">dst</a>,
<a name="L301" href="source/net/ipv4/fib_frontend.c#L301">301</a>                                  <a href="ident?i=u8">u8</a> tos, int oif, struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>,
<a name="L302" href="source/net/ipv4/fib_frontend.c#L302">302</a>                                  int rpf, struct <a href="ident?i=in_device">in_device</a> *<a href="ident?i=idev">idev</a>, <a href="ident?i=u32">u32</a> *itag)
<a name="L303" href="source/net/ipv4/fib_frontend.c#L303">303</a> {
<a name="L304" href="source/net/ipv4/fib_frontend.c#L304">304</a>         int <a href="ident?i=ret">ret</a>, no_addr;
<a name="L305" href="source/net/ipv4/fib_frontend.c#L305">305</a>         struct <a href="ident?i=fib_result">fib_result</a> <a href="ident?i=res">res</a>;
<a name="L306" href="source/net/ipv4/fib_frontend.c#L306">306</a>         struct <a href="ident?i=flowi4">flowi4</a> fl4;
<a name="L307" href="source/net/ipv4/fib_frontend.c#L307">307</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>;
<a name="L308" href="source/net/ipv4/fib_frontend.c#L308">308</a>         <a href="ident?i=bool">bool</a> dev_match;
<a name="L309" href="source/net/ipv4/fib_frontend.c#L309">309</a> 
<a name="L310" href="source/net/ipv4/fib_frontend.c#L310">310</a>         fl4.<a href="ident?i=flowi4_oif">flowi4_oif</a> = 0;
<a name="L311" href="source/net/ipv4/fib_frontend.c#L311">311</a>         fl4.<a href="ident?i=flowi4_iif">flowi4_iif</a> = oif ? : <a href="ident?i=LOOPBACK_IFINDEX">LOOPBACK_IFINDEX</a>;
<a name="L312" href="source/net/ipv4/fib_frontend.c#L312">312</a>         fl4.<a href="ident?i=daddr">daddr</a> = <a href="ident?i=src">src</a>;
<a name="L313" href="source/net/ipv4/fib_frontend.c#L313">313</a>         fl4.<a href="ident?i=saddr">saddr</a> = <a href="ident?i=dst">dst</a>;
<a name="L314" href="source/net/ipv4/fib_frontend.c#L314">314</a>         fl4.<a href="ident?i=flowi4_tos">flowi4_tos</a> = tos;
<a name="L315" href="source/net/ipv4/fib_frontend.c#L315">315</a>         fl4.<a href="ident?i=flowi4_scope">flowi4_scope</a> = RT_SCOPE_UNIVERSE;
<a name="L316" href="source/net/ipv4/fib_frontend.c#L316">316</a> 
<a name="L317" href="source/net/ipv4/fib_frontend.c#L317">317</a>         no_addr = <a href="ident?i=idev">idev</a>-&gt;ifa_list == <a href="ident?i=NULL">NULL</a>;
<a name="L318" href="source/net/ipv4/fib_frontend.c#L318">318</a> 
<a name="L319" href="source/net/ipv4/fib_frontend.c#L319">319</a>         fl4.<a href="ident?i=flowi4_mark">flowi4_mark</a> = <a href="ident?i=IN_DEV_SRC_VMARK">IN_DEV_SRC_VMARK</a>(<a href="ident?i=idev">idev</a>) ? <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=mark">mark</a> : 0;
<a name="L320" href="source/net/ipv4/fib_frontend.c#L320">320</a> 
<a name="L321" href="source/net/ipv4/fib_frontend.c#L321">321</a>         <a href="ident?i=net">net</a> = <a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=dev">dev</a>);
<a name="L322" href="source/net/ipv4/fib_frontend.c#L322">322</a>         if (<a href="ident?i=fib_lookup">fib_lookup</a>(<a href="ident?i=net">net</a>, &amp;fl4, &amp;<a href="ident?i=res">res</a>))
<a name="L323" href="source/net/ipv4/fib_frontend.c#L323">323</a>                 goto last_resort;
<a name="L324" href="source/net/ipv4/fib_frontend.c#L324">324</a>         if (<a href="ident?i=res">res</a>.<a href="ident?i=type">type</a> != RTN_UNICAST &amp;&amp;
<a name="L325" href="source/net/ipv4/fib_frontend.c#L325">325</a>             (<a href="ident?i=res">res</a>.<a href="ident?i=type">type</a> != RTN_LOCAL || !<a href="ident?i=IN_DEV_ACCEPT_LOCAL">IN_DEV_ACCEPT_LOCAL</a>(<a href="ident?i=idev">idev</a>)))
<a name="L326" href="source/net/ipv4/fib_frontend.c#L326">326</a>                 goto e_inval;
<a name="L327" href="source/net/ipv4/fib_frontend.c#L327">327</a>         if (!rpf &amp;&amp; !<a href="ident?i=fib_num_tclassid_users">fib_num_tclassid_users</a>(<a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=dev">dev</a>)) &amp;&amp;
<a name="L328" href="source/net/ipv4/fib_frontend.c#L328">328</a>             (<a href="ident?i=dev">dev</a>-&gt;ifindex != oif || !<a href="ident?i=IN_DEV_TX_REDIRECTS">IN_DEV_TX_REDIRECTS</a>(<a href="ident?i=idev">idev</a>)))
<a name="L329" href="source/net/ipv4/fib_frontend.c#L329">329</a>                 goto last_resort;
<a name="L330" href="source/net/ipv4/fib_frontend.c#L330">330</a>         <a href="ident?i=fib_combine_itag">fib_combine_itag</a>(itag, &amp;<a href="ident?i=res">res</a>);
<a name="L331" href="source/net/ipv4/fib_frontend.c#L331">331</a>         dev_match = <a href="ident?i=false">false</a>;
<a name="L332" href="source/net/ipv4/fib_frontend.c#L332">332</a> 
<a name="L333" href="source/net/ipv4/fib_frontend.c#L333">333</a> #ifdef CONFIG_IP_ROUTE_MULTIPATH
<a name="L334" href="source/net/ipv4/fib_frontend.c#L334">334</a>         for (<a href="ident?i=ret">ret</a> = 0; <a href="ident?i=ret">ret</a> &lt; <a href="ident?i=res">res</a>.fi-&gt;fib_nhs; <a href="ident?i=ret">ret</a>++) {
<a name="L335" href="source/net/ipv4/fib_frontend.c#L335">335</a>                 struct <a href="ident?i=fib_nh">fib_nh</a> *nh = &amp;<a href="ident?i=res">res</a>.fi-&gt;<a href="ident?i=fib_nh">fib_nh</a>[<a href="ident?i=ret">ret</a>];
<a name="L336" href="source/net/ipv4/fib_frontend.c#L336">336</a> 
<a name="L337" href="source/net/ipv4/fib_frontend.c#L337">337</a>                 if (nh-&gt;nh_dev == <a href="ident?i=dev">dev</a>) {
<a name="L338" href="source/net/ipv4/fib_frontend.c#L338">338</a>                         dev_match = <a href="ident?i=true">true</a>;
<a name="L339" href="source/net/ipv4/fib_frontend.c#L339">339</a>                         break;
<a name="L340" href="source/net/ipv4/fib_frontend.c#L340">340</a>                 }
<a name="L341" href="source/net/ipv4/fib_frontend.c#L341">341</a>         }
<a name="L342" href="source/net/ipv4/fib_frontend.c#L342">342</a> #else
<a name="L343" href="source/net/ipv4/fib_frontend.c#L343">343</a>         if (<a href="ident?i=FIB_RES_DEV">FIB_RES_DEV</a>(<a href="ident?i=res">res</a>) == <a href="ident?i=dev">dev</a>)
<a name="L344" href="source/net/ipv4/fib_frontend.c#L344">344</a>                 dev_match = <a href="ident?i=true">true</a>;
<a name="L345" href="source/net/ipv4/fib_frontend.c#L345">345</a> #endif
<a name="L346" href="source/net/ipv4/fib_frontend.c#L346">346</a>         if (dev_match) {
<a name="L347" href="source/net/ipv4/fib_frontend.c#L347">347</a>                 <a href="ident?i=ret">ret</a> = <a href="ident?i=FIB_RES_NH">FIB_RES_NH</a>(<a href="ident?i=res">res</a>).nh_scope &gt;= RT_SCOPE_HOST;
<a name="L348" href="source/net/ipv4/fib_frontend.c#L348">348</a>                 return <a href="ident?i=ret">ret</a>;
<a name="L349" href="source/net/ipv4/fib_frontend.c#L349">349</a>         }
<a name="L350" href="source/net/ipv4/fib_frontend.c#L350">350</a>         if (no_addr)
<a name="L351" href="source/net/ipv4/fib_frontend.c#L351">351</a>                 goto last_resort;
<a name="L352" href="source/net/ipv4/fib_frontend.c#L352">352</a>         if (rpf == 1)
<a name="L353" href="source/net/ipv4/fib_frontend.c#L353">353</a>                 goto e_rpf;
<a name="L354" href="source/net/ipv4/fib_frontend.c#L354">354</a>         fl4.<a href="ident?i=flowi4_oif">flowi4_oif</a> = <a href="ident?i=dev">dev</a>-&gt;ifindex;
<a name="L355" href="source/net/ipv4/fib_frontend.c#L355">355</a> 
<a name="L356" href="source/net/ipv4/fib_frontend.c#L356">356</a>         <a href="ident?i=ret">ret</a> = 0;
<a name="L357" href="source/net/ipv4/fib_frontend.c#L357">357</a>         if (<a href="ident?i=fib_lookup">fib_lookup</a>(<a href="ident?i=net">net</a>, &amp;fl4, &amp;<a href="ident?i=res">res</a>) == 0) {
<a name="L358" href="source/net/ipv4/fib_frontend.c#L358">358</a>                 if (<a href="ident?i=res">res</a>.<a href="ident?i=type">type</a> == RTN_UNICAST)
<a name="L359" href="source/net/ipv4/fib_frontend.c#L359">359</a>                         <a href="ident?i=ret">ret</a> = <a href="ident?i=FIB_RES_NH">FIB_RES_NH</a>(<a href="ident?i=res">res</a>).nh_scope &gt;= RT_SCOPE_HOST;
<a name="L360" href="source/net/ipv4/fib_frontend.c#L360">360</a>         }
<a name="L361" href="source/net/ipv4/fib_frontend.c#L361">361</a>         return <a href="ident?i=ret">ret</a>;
<a name="L362" href="source/net/ipv4/fib_frontend.c#L362">362</a> 
<a name="L363" href="source/net/ipv4/fib_frontend.c#L363">363</a> last_resort:
<a name="L364" href="source/net/ipv4/fib_frontend.c#L364">364</a>         if (rpf)
<a name="L365" href="source/net/ipv4/fib_frontend.c#L365">365</a>                 goto e_rpf;
<a name="L366" href="source/net/ipv4/fib_frontend.c#L366">366</a>         *itag = 0;
<a name="L367" href="source/net/ipv4/fib_frontend.c#L367">367</a>         return 0;
<a name="L368" href="source/net/ipv4/fib_frontend.c#L368">368</a> 
<a name="L369" href="source/net/ipv4/fib_frontend.c#L369">369</a> e_inval:
<a name="L370" href="source/net/ipv4/fib_frontend.c#L370">370</a>         return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L371" href="source/net/ipv4/fib_frontend.c#L371">371</a> e_rpf:
<a name="L372" href="source/net/ipv4/fib_frontend.c#L372">372</a>         return -<a href="ident?i=EXDEV">EXDEV</a>;
<a name="L373" href="source/net/ipv4/fib_frontend.c#L373">373</a> }
<a name="L374" href="source/net/ipv4/fib_frontend.c#L374">374</a> 
<a name="L375" href="source/net/ipv4/fib_frontend.c#L375">375</a> <b><i>/* Ignore rp_filter for packets protected by IPsec. */</i></b>
<a name="L376" href="source/net/ipv4/fib_frontend.c#L376">376</a> int <a href="ident?i=fib_validate_source">fib_validate_source</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, <a href="ident?i=__be32">__be32</a> <a href="ident?i=src">src</a>, <a href="ident?i=__be32">__be32</a> <a href="ident?i=dst">dst</a>,
<a name="L377" href="source/net/ipv4/fib_frontend.c#L377">377</a>                         <a href="ident?i=u8">u8</a> tos, int oif, struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>,
<a name="L378" href="source/net/ipv4/fib_frontend.c#L378">378</a>                         struct <a href="ident?i=in_device">in_device</a> *<a href="ident?i=idev">idev</a>, <a href="ident?i=u32">u32</a> *itag)
<a name="L379" href="source/net/ipv4/fib_frontend.c#L379">379</a> {
<a name="L380" href="source/net/ipv4/fib_frontend.c#L380">380</a>         int <a href="ident?i=r">r</a> = <a href="ident?i=secpath_exists">secpath_exists</a>(<a href="ident?i=skb">skb</a>) ? 0 : <a href="ident?i=IN_DEV_RPFILTER">IN_DEV_RPFILTER</a>(<a href="ident?i=idev">idev</a>);
<a name="L381" href="source/net/ipv4/fib_frontend.c#L381">381</a> 
<a name="L382" href="source/net/ipv4/fib_frontend.c#L382">382</a>         if (!<a href="ident?i=r">r</a> &amp;&amp; !<a href="ident?i=fib_num_tclassid_users">fib_num_tclassid_users</a>(<a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=dev">dev</a>)) &amp;&amp;
<a name="L383" href="source/net/ipv4/fib_frontend.c#L383">383</a>             <a href="ident?i=IN_DEV_ACCEPT_LOCAL">IN_DEV_ACCEPT_LOCAL</a>(<a href="ident?i=idev">idev</a>) &amp;&amp;
<a name="L384" href="source/net/ipv4/fib_frontend.c#L384">384</a>             (<a href="ident?i=dev">dev</a>-&gt;ifindex != oif || !<a href="ident?i=IN_DEV_TX_REDIRECTS">IN_DEV_TX_REDIRECTS</a>(<a href="ident?i=idev">idev</a>))) {
<a name="L385" href="source/net/ipv4/fib_frontend.c#L385">385</a>                 *itag = 0;
<a name="L386" href="source/net/ipv4/fib_frontend.c#L386">386</a>                 return 0;
<a name="L387" href="source/net/ipv4/fib_frontend.c#L387">387</a>         }
<a name="L388" href="source/net/ipv4/fib_frontend.c#L388">388</a>         return <a href="ident?i=__fib_validate_source">__fib_validate_source</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=src">src</a>, <a href="ident?i=dst">dst</a>, tos, oif, <a href="ident?i=dev">dev</a>, <a href="ident?i=r">r</a>, <a href="ident?i=idev">idev</a>, itag);
<a name="L389" href="source/net/ipv4/fib_frontend.c#L389">389</a> }
<a name="L390" href="source/net/ipv4/fib_frontend.c#L390">390</a> 
<a name="L391" href="source/net/ipv4/fib_frontend.c#L391">391</a> static inline <a href="ident?i=__be32">__be32</a> <a href="ident?i=sk_extract_addr">sk_extract_addr</a>(struct <a href="ident?i=sockaddr">sockaddr</a> *<a href="ident?i=addr">addr</a>)
<a name="L392" href="source/net/ipv4/fib_frontend.c#L392">392</a> {
<a name="L393" href="source/net/ipv4/fib_frontend.c#L393">393</a>         return ((struct <a href="ident?i=sockaddr_in">sockaddr_in</a> *) <a href="ident?i=addr">addr</a>)-&gt;sin_addr.s_addr;
<a name="L394" href="source/net/ipv4/fib_frontend.c#L394">394</a> }
<a name="L395" href="source/net/ipv4/fib_frontend.c#L395">395</a> 
<a name="L396" href="source/net/ipv4/fib_frontend.c#L396">396</a> static int <a href="ident?i=put_rtax">put_rtax</a>(struct <a href="ident?i=nlattr">nlattr</a> *<a href="ident?i=mx">mx</a>, int <a href="ident?i=len">len</a>, int <a href="ident?i=type">type</a>, <a href="ident?i=u32">u32</a> <a href="ident?i=value">value</a>)
<a name="L397" href="source/net/ipv4/fib_frontend.c#L397">397</a> {
<a name="L398" href="source/net/ipv4/fib_frontend.c#L398">398</a>         struct <a href="ident?i=nlattr">nlattr</a> *nla;
<a name="L399" href="source/net/ipv4/fib_frontend.c#L399">399</a> 
<a name="L400" href="source/net/ipv4/fib_frontend.c#L400">400</a>         nla = (struct <a href="ident?i=nlattr">nlattr</a> *) ((char *) <a href="ident?i=mx">mx</a> + <a href="ident?i=len">len</a>);
<a name="L401" href="source/net/ipv4/fib_frontend.c#L401">401</a>         nla-&gt;<a href="ident?i=nla_type">nla_type</a> = <a href="ident?i=type">type</a>;
<a name="L402" href="source/net/ipv4/fib_frontend.c#L402">402</a>         nla-&gt;<a href="ident?i=nla_len">nla_len</a> = <a href="ident?i=nla_attr_size">nla_attr_size</a>(4);
<a name="L403" href="source/net/ipv4/fib_frontend.c#L403">403</a>         *(<a href="ident?i=u32">u32</a> *) <a href="ident?i=nla_data">nla_data</a>(nla) = <a href="ident?i=value">value</a>;
<a name="L404" href="source/net/ipv4/fib_frontend.c#L404">404</a> 
<a name="L405" href="source/net/ipv4/fib_frontend.c#L405">405</a>         return <a href="ident?i=len">len</a> + <a href="ident?i=nla_total_size">nla_total_size</a>(4);
<a name="L406" href="source/net/ipv4/fib_frontend.c#L406">406</a> }
<a name="L407" href="source/net/ipv4/fib_frontend.c#L407">407</a> 
<a name="L408" href="source/net/ipv4/fib_frontend.c#L408">408</a> static int <a href="ident?i=rtentry_to_fib_config">rtentry_to_fib_config</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>, int <a href="ident?i=cmd">cmd</a>, struct <a href="ident?i=rtentry">rtentry</a> *<a href="ident?i=rt">rt</a>,
<a name="L409" href="source/net/ipv4/fib_frontend.c#L409">409</a>                                  struct <a href="ident?i=fib_config">fib_config</a> *<a href="ident?i=cfg">cfg</a>)
<a name="L410" href="source/net/ipv4/fib_frontend.c#L410">410</a> {
<a name="L411" href="source/net/ipv4/fib_frontend.c#L411">411</a>         <a href="ident?i=__be32">__be32</a> <a href="ident?i=addr">addr</a>;
<a name="L412" href="source/net/ipv4/fib_frontend.c#L412">412</a>         int plen;
<a name="L413" href="source/net/ipv4/fib_frontend.c#L413">413</a> 
<a name="L414" href="source/net/ipv4/fib_frontend.c#L414">414</a>         <a href="ident?i=memset">memset</a>(<a href="ident?i=cfg">cfg</a>, 0, sizeof(*<a href="ident?i=cfg">cfg</a>));
<a name="L415" href="source/net/ipv4/fib_frontend.c#L415">415</a>         <a href="ident?i=cfg">cfg</a>-&gt;fc_nlinfo.nl_net = <a href="ident?i=net">net</a>;
<a name="L416" href="source/net/ipv4/fib_frontend.c#L416">416</a> 
<a name="L417" href="source/net/ipv4/fib_frontend.c#L417">417</a>         if (<a href="ident?i=rt">rt</a>-&gt;rt_dst.sa_family != <a href="ident?i=AF_INET">AF_INET</a>)
<a name="L418" href="source/net/ipv4/fib_frontend.c#L418">418</a>                 return -<a href="ident?i=EAFNOSUPPORT">EAFNOSUPPORT</a>;
<a name="L419" href="source/net/ipv4/fib_frontend.c#L419">419</a> 
<a name="L420" href="source/net/ipv4/fib_frontend.c#L420">420</a>         <b><i>/*</i></b>
<a name="L421" href="source/net/ipv4/fib_frontend.c#L421">421</a> <b><i>         * Check mask for validity:</i></b>
<a name="L422" href="source/net/ipv4/fib_frontend.c#L422">422</a> <b><i>         * a) it must be contiguous.</i></b>
<a name="L423" href="source/net/ipv4/fib_frontend.c#L423">423</a> <b><i>         * b) destination must have all host bits clear.</i></b>
<a name="L424" href="source/net/ipv4/fib_frontend.c#L424">424</a> <b><i>         * c) if application forgot to set correct family (AF_INET),</i></b>
<a name="L425" href="source/net/ipv4/fib_frontend.c#L425">425</a> <b><i>         *    reject request unless it is absolutely clear i.e.</i></b>
<a name="L426" href="source/net/ipv4/fib_frontend.c#L426">426</a> <b><i>         *    both family and mask are zero.</i></b>
<a name="L427" href="source/net/ipv4/fib_frontend.c#L427">427</a> <b><i>         */</i></b>
<a name="L428" href="source/net/ipv4/fib_frontend.c#L428">428</a>         plen = 32;
<a name="L429" href="source/net/ipv4/fib_frontend.c#L429">429</a>         <a href="ident?i=addr">addr</a> = <a href="ident?i=sk_extract_addr">sk_extract_addr</a>(&amp;<a href="ident?i=rt">rt</a>-&gt;rt_dst);
<a name="L430" href="source/net/ipv4/fib_frontend.c#L430">430</a>         if (!(<a href="ident?i=rt">rt</a>-&gt;rt_flags &amp; <a href="ident?i=RTF_HOST">RTF_HOST</a>)) {
<a name="L431" href="source/net/ipv4/fib_frontend.c#L431">431</a>                 <a href="ident?i=__be32">__be32</a> <a href="ident?i=mask">mask</a> = <a href="ident?i=sk_extract_addr">sk_extract_addr</a>(&amp;<a href="ident?i=rt">rt</a>-&gt;rt_genmask);
<a name="L432" href="source/net/ipv4/fib_frontend.c#L432">432</a> 
<a name="L433" href="source/net/ipv4/fib_frontend.c#L433">433</a>                 if (<a href="ident?i=rt">rt</a>-&gt;rt_genmask.sa_family != <a href="ident?i=AF_INET">AF_INET</a>) {
<a name="L434" href="source/net/ipv4/fib_frontend.c#L434">434</a>                         if (<a href="ident?i=mask">mask</a> || <a href="ident?i=rt">rt</a>-&gt;rt_genmask.sa_family)
<a name="L435" href="source/net/ipv4/fib_frontend.c#L435">435</a>                                 return -<a href="ident?i=EAFNOSUPPORT">EAFNOSUPPORT</a>;
<a name="L436" href="source/net/ipv4/fib_frontend.c#L436">436</a>                 }
<a name="L437" href="source/net/ipv4/fib_frontend.c#L437">437</a> 
<a name="L438" href="source/net/ipv4/fib_frontend.c#L438">438</a>                 if (<a href="ident?i=bad_mask">bad_mask</a>(<a href="ident?i=mask">mask</a>, <a href="ident?i=addr">addr</a>))
<a name="L439" href="source/net/ipv4/fib_frontend.c#L439">439</a>                         return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L440" href="source/net/ipv4/fib_frontend.c#L440">440</a> 
<a name="L441" href="source/net/ipv4/fib_frontend.c#L441">441</a>                 plen = <a href="ident?i=inet_mask_len">inet_mask_len</a>(<a href="ident?i=mask">mask</a>);
<a name="L442" href="source/net/ipv4/fib_frontend.c#L442">442</a>         }
<a name="L443" href="source/net/ipv4/fib_frontend.c#L443">443</a> 
<a name="L444" href="source/net/ipv4/fib_frontend.c#L444">444</a>         <a href="ident?i=cfg">cfg</a>-&gt;fc_dst_len = plen;
<a name="L445" href="source/net/ipv4/fib_frontend.c#L445">445</a>         <a href="ident?i=cfg">cfg</a>-&gt;fc_dst = <a href="ident?i=addr">addr</a>;
<a name="L446" href="source/net/ipv4/fib_frontend.c#L446">446</a> 
<a name="L447" href="source/net/ipv4/fib_frontend.c#L447">447</a>         if (<a href="ident?i=cmd">cmd</a> != <a href="ident?i=SIOCDELRT">SIOCDELRT</a>) {
<a name="L448" href="source/net/ipv4/fib_frontend.c#L448">448</a>                 <a href="ident?i=cfg">cfg</a>-&gt;fc_nlflags = <a href="ident?i=NLM_F_CREATE">NLM_F_CREATE</a>;
<a name="L449" href="source/net/ipv4/fib_frontend.c#L449">449</a>                 <a href="ident?i=cfg">cfg</a>-&gt;fc_protocol = <a href="ident?i=RTPROT_BOOT">RTPROT_BOOT</a>;
<a name="L450" href="source/net/ipv4/fib_frontend.c#L450">450</a>         }
<a name="L451" href="source/net/ipv4/fib_frontend.c#L451">451</a> 
<a name="L452" href="source/net/ipv4/fib_frontend.c#L452">452</a>         if (<a href="ident?i=rt">rt</a>-&gt;rt_metric)
<a name="L453" href="source/net/ipv4/fib_frontend.c#L453">453</a>                 <a href="ident?i=cfg">cfg</a>-&gt;fc_priority = <a href="ident?i=rt">rt</a>-&gt;rt_metric - 1;
<a name="L454" href="source/net/ipv4/fib_frontend.c#L454">454</a> 
<a name="L455" href="source/net/ipv4/fib_frontend.c#L455">455</a>         if (<a href="ident?i=rt">rt</a>-&gt;rt_flags &amp; <a href="ident?i=RTF_REJECT">RTF_REJECT</a>) {
<a name="L456" href="source/net/ipv4/fib_frontend.c#L456">456</a>                 <a href="ident?i=cfg">cfg</a>-&gt;fc_scope = RT_SCOPE_HOST;
<a name="L457" href="source/net/ipv4/fib_frontend.c#L457">457</a>                 <a href="ident?i=cfg">cfg</a>-&gt;<a href="ident?i=fc_type">fc_type</a> = RTN_UNREACHABLE;
<a name="L458" href="source/net/ipv4/fib_frontend.c#L458">458</a>                 return 0;
<a name="L459" href="source/net/ipv4/fib_frontend.c#L459">459</a>         }
<a name="L460" href="source/net/ipv4/fib_frontend.c#L460">460</a> 
<a name="L461" href="source/net/ipv4/fib_frontend.c#L461">461</a>         <a href="ident?i=cfg">cfg</a>-&gt;fc_scope = RT_SCOPE_NOWHERE;
<a name="L462" href="source/net/ipv4/fib_frontend.c#L462">462</a>         <a href="ident?i=cfg">cfg</a>-&gt;<a href="ident?i=fc_type">fc_type</a> = RTN_UNICAST;
<a name="L463" href="source/net/ipv4/fib_frontend.c#L463">463</a> 
<a name="L464" href="source/net/ipv4/fib_frontend.c#L464">464</a>         if (<a href="ident?i=rt">rt</a>-&gt;rt_dev) {
<a name="L465" href="source/net/ipv4/fib_frontend.c#L465">465</a>                 char *colon;
<a name="L466" href="source/net/ipv4/fib_frontend.c#L466">466</a>                 struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>;
<a name="L467" href="source/net/ipv4/fib_frontend.c#L467">467</a>                 char <a href="ident?i=devname">devname</a>[<a href="ident?i=IFNAMSIZ">IFNAMSIZ</a>];
<a name="L468" href="source/net/ipv4/fib_frontend.c#L468">468</a> 
<a name="L469" href="source/net/ipv4/fib_frontend.c#L469">469</a>                 if (<a href="ident?i=copy_from_user">copy_from_user</a>(<a href="ident?i=devname">devname</a>, <a href="ident?i=rt">rt</a>-&gt;rt_dev, <a href="ident?i=IFNAMSIZ">IFNAMSIZ</a>-1))
<a name="L470" href="source/net/ipv4/fib_frontend.c#L470">470</a>                         return -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L471" href="source/net/ipv4/fib_frontend.c#L471">471</a> 
<a name="L472" href="source/net/ipv4/fib_frontend.c#L472">472</a>                 <a href="ident?i=devname">devname</a>[<a href="ident?i=IFNAMSIZ">IFNAMSIZ</a>-1] = 0;
<a name="L473" href="source/net/ipv4/fib_frontend.c#L473">473</a>                 colon = <a href="ident?i=strchr">strchr</a>(<a href="ident?i=devname">devname</a>, <i>':'</i>);
<a name="L474" href="source/net/ipv4/fib_frontend.c#L474">474</a>                 if (colon)
<a name="L475" href="source/net/ipv4/fib_frontend.c#L475">475</a>                         *colon = 0;
<a name="L476" href="source/net/ipv4/fib_frontend.c#L476">476</a>                 <a href="ident?i=dev">dev</a> = <a href="ident?i=__dev_get_by_name">__dev_get_by_name</a>(<a href="ident?i=net">net</a>, <a href="ident?i=devname">devname</a>);
<a name="L477" href="source/net/ipv4/fib_frontend.c#L477">477</a>                 if (!<a href="ident?i=dev">dev</a>)
<a name="L478" href="source/net/ipv4/fib_frontend.c#L478">478</a>                         return -<a href="ident?i=ENODEV">ENODEV</a>;
<a name="L479" href="source/net/ipv4/fib_frontend.c#L479">479</a>                 <a href="ident?i=cfg">cfg</a>-&gt;fc_oif = <a href="ident?i=dev">dev</a>-&gt;ifindex;
<a name="L480" href="source/net/ipv4/fib_frontend.c#L480">480</a>                 if (colon) {
<a name="L481" href="source/net/ipv4/fib_frontend.c#L481">481</a>                         struct <a href="ident?i=in_ifaddr">in_ifaddr</a> *<a href="ident?i=ifa">ifa</a>;
<a name="L482" href="source/net/ipv4/fib_frontend.c#L482">482</a>                         struct <a href="ident?i=in_device">in_device</a> *in_dev = <a href="ident?i=__in_dev_get_rtnl">__in_dev_get_rtnl</a>(<a href="ident?i=dev">dev</a>);
<a name="L483" href="source/net/ipv4/fib_frontend.c#L483">483</a>                         if (!in_dev)
<a name="L484" href="source/net/ipv4/fib_frontend.c#L484">484</a>                                 return -<a href="ident?i=ENODEV">ENODEV</a>;
<a name="L485" href="source/net/ipv4/fib_frontend.c#L485">485</a>                         *colon = <i>':'</i>;
<a name="L486" href="source/net/ipv4/fib_frontend.c#L486">486</a>                         for (<a href="ident?i=ifa">ifa</a> = in_dev-&gt;ifa_list; <a href="ident?i=ifa">ifa</a>; <a href="ident?i=ifa">ifa</a> = <a href="ident?i=ifa">ifa</a>-&gt;ifa_next)
<a name="L487" href="source/net/ipv4/fib_frontend.c#L487">487</a>                                 if (<a href="ident?i=strcmp">strcmp</a>(<a href="ident?i=ifa">ifa</a>-&gt;ifa_label, <a href="ident?i=devname">devname</a>) == 0)
<a name="L488" href="source/net/ipv4/fib_frontend.c#L488">488</a>                                         break;
<a name="L489" href="source/net/ipv4/fib_frontend.c#L489">489</a>                         if (!<a href="ident?i=ifa">ifa</a>)
<a name="L490" href="source/net/ipv4/fib_frontend.c#L490">490</a>                                 return -<a href="ident?i=ENODEV">ENODEV</a>;
<a name="L491" href="source/net/ipv4/fib_frontend.c#L491">491</a>                         <a href="ident?i=cfg">cfg</a>-&gt;fc_prefsrc = <a href="ident?i=ifa">ifa</a>-&gt;ifa_local;
<a name="L492" href="source/net/ipv4/fib_frontend.c#L492">492</a>                 }
<a name="L493" href="source/net/ipv4/fib_frontend.c#L493">493</a>         }
<a name="L494" href="source/net/ipv4/fib_frontend.c#L494">494</a> 
<a name="L495" href="source/net/ipv4/fib_frontend.c#L495">495</a>         <a href="ident?i=addr">addr</a> = <a href="ident?i=sk_extract_addr">sk_extract_addr</a>(&amp;<a href="ident?i=rt">rt</a>-&gt;rt_gateway);
<a name="L496" href="source/net/ipv4/fib_frontend.c#L496">496</a>         if (<a href="ident?i=rt">rt</a>-&gt;rt_gateway.sa_family == <a href="ident?i=AF_INET">AF_INET</a> &amp;&amp; <a href="ident?i=addr">addr</a>) {
<a name="L497" href="source/net/ipv4/fib_frontend.c#L497">497</a>                 <a href="ident?i=cfg">cfg</a>-&gt;fc_gw = <a href="ident?i=addr">addr</a>;
<a name="L498" href="source/net/ipv4/fib_frontend.c#L498">498</a>                 if (<a href="ident?i=rt">rt</a>-&gt;rt_flags &amp; <a href="ident?i=RTF_GATEWAY">RTF_GATEWAY</a> &amp;&amp;
<a name="L499" href="source/net/ipv4/fib_frontend.c#L499">499</a>                     <a href="ident?i=inet_addr_type">inet_addr_type</a>(<a href="ident?i=net">net</a>, <a href="ident?i=addr">addr</a>) == RTN_UNICAST)
<a name="L500" href="source/net/ipv4/fib_frontend.c#L500">500</a>                         <a href="ident?i=cfg">cfg</a>-&gt;fc_scope = RT_SCOPE_UNIVERSE;
<a name="L501" href="source/net/ipv4/fib_frontend.c#L501">501</a>         }
<a name="L502" href="source/net/ipv4/fib_frontend.c#L502">502</a> 
<a name="L503" href="source/net/ipv4/fib_frontend.c#L503">503</a>         if (<a href="ident?i=cmd">cmd</a> == <a href="ident?i=SIOCDELRT">SIOCDELRT</a>)
<a name="L504" href="source/net/ipv4/fib_frontend.c#L504">504</a>                 return 0;
<a name="L505" href="source/net/ipv4/fib_frontend.c#L505">505</a> 
<a name="L506" href="source/net/ipv4/fib_frontend.c#L506">506</a>         if (<a href="ident?i=rt">rt</a>-&gt;rt_flags &amp; <a href="ident?i=RTF_GATEWAY">RTF_GATEWAY</a> &amp;&amp; !<a href="ident?i=cfg">cfg</a>-&gt;fc_gw)
<a name="L507" href="source/net/ipv4/fib_frontend.c#L507">507</a>                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L508" href="source/net/ipv4/fib_frontend.c#L508">508</a> 
<a name="L509" href="source/net/ipv4/fib_frontend.c#L509">509</a>         if (<a href="ident?i=cfg">cfg</a>-&gt;fc_scope == RT_SCOPE_NOWHERE)
<a name="L510" href="source/net/ipv4/fib_frontend.c#L510">510</a>                 <a href="ident?i=cfg">cfg</a>-&gt;fc_scope = RT_SCOPE_LINK;
<a name="L511" href="source/net/ipv4/fib_frontend.c#L511">511</a> 
<a name="L512" href="source/net/ipv4/fib_frontend.c#L512">512</a>         if (<a href="ident?i=rt">rt</a>-&gt;rt_flags &amp; (<a href="ident?i=RTF_MTU">RTF_MTU</a> | <a href="ident?i=RTF_WINDOW">RTF_WINDOW</a> | <a href="ident?i=RTF_IRTT">RTF_IRTT</a>)) {
<a name="L513" href="source/net/ipv4/fib_frontend.c#L513">513</a>                 struct <a href="ident?i=nlattr">nlattr</a> *<a href="ident?i=mx">mx</a>;
<a name="L514" href="source/net/ipv4/fib_frontend.c#L514">514</a>                 int <a href="ident?i=len">len</a> = 0;
<a name="L515" href="source/net/ipv4/fib_frontend.c#L515">515</a> 
<a name="L516" href="source/net/ipv4/fib_frontend.c#L516">516</a>                 <a href="ident?i=mx">mx</a> = <a href="ident?i=kzalloc">kzalloc</a>(3 * <a href="ident?i=nla_total_size">nla_total_size</a>(4), <a href="ident?i=GFP_KERNEL">GFP_KERNEL</a>);
<a name="L517" href="source/net/ipv4/fib_frontend.c#L517">517</a>                 if (!<a href="ident?i=mx">mx</a>)
<a name="L518" href="source/net/ipv4/fib_frontend.c#L518">518</a>                         return -<a href="ident?i=ENOMEM">ENOMEM</a>;
<a name="L519" href="source/net/ipv4/fib_frontend.c#L519">519</a> 
<a name="L520" href="source/net/ipv4/fib_frontend.c#L520">520</a>                 if (<a href="ident?i=rt">rt</a>-&gt;rt_flags &amp; <a href="ident?i=RTF_MTU">RTF_MTU</a>)
<a name="L521" href="source/net/ipv4/fib_frontend.c#L521">521</a>                         <a href="ident?i=len">len</a> = <a href="ident?i=put_rtax">put_rtax</a>(<a href="ident?i=mx">mx</a>, <a href="ident?i=len">len</a>, <a href="ident?i=RTAX_ADVMSS">RTAX_ADVMSS</a>, <a href="ident?i=rt">rt</a>-&gt;rt_mtu - 40);
<a name="L522" href="source/net/ipv4/fib_frontend.c#L522">522</a> 
<a name="L523" href="source/net/ipv4/fib_frontend.c#L523">523</a>                 if (<a href="ident?i=rt">rt</a>-&gt;rt_flags &amp; <a href="ident?i=RTF_WINDOW">RTF_WINDOW</a>)
<a name="L524" href="source/net/ipv4/fib_frontend.c#L524">524</a>                         <a href="ident?i=len">len</a> = <a href="ident?i=put_rtax">put_rtax</a>(<a href="ident?i=mx">mx</a>, <a href="ident?i=len">len</a>, <a href="ident?i=RTAX_WINDOW">RTAX_WINDOW</a>, <a href="ident?i=rt">rt</a>-&gt;rt_window);
<a name="L525" href="source/net/ipv4/fib_frontend.c#L525">525</a> 
<a name="L526" href="source/net/ipv4/fib_frontend.c#L526">526</a>                 if (<a href="ident?i=rt">rt</a>-&gt;rt_flags &amp; <a href="ident?i=RTF_IRTT">RTF_IRTT</a>)
<a name="L527" href="source/net/ipv4/fib_frontend.c#L527">527</a>                         <a href="ident?i=len">len</a> = <a href="ident?i=put_rtax">put_rtax</a>(<a href="ident?i=mx">mx</a>, <a href="ident?i=len">len</a>, <a href="ident?i=RTAX_RTT">RTAX_RTT</a>, <a href="ident?i=rt">rt</a>-&gt;rt_irtt &lt;&lt; 3);
<a name="L528" href="source/net/ipv4/fib_frontend.c#L528">528</a> 
<a name="L529" href="source/net/ipv4/fib_frontend.c#L529">529</a>                 <a href="ident?i=cfg">cfg</a>-&gt;fc_mx = <a href="ident?i=mx">mx</a>;
<a name="L530" href="source/net/ipv4/fib_frontend.c#L530">530</a>                 <a href="ident?i=cfg">cfg</a>-&gt;fc_mx_len = <a href="ident?i=len">len</a>;
<a name="L531" href="source/net/ipv4/fib_frontend.c#L531">531</a>         }
<a name="L532" href="source/net/ipv4/fib_frontend.c#L532">532</a> 
<a name="L533" href="source/net/ipv4/fib_frontend.c#L533">533</a>         return 0;
<a name="L534" href="source/net/ipv4/fib_frontend.c#L534">534</a> }
<a name="L535" href="source/net/ipv4/fib_frontend.c#L535">535</a> 
<a name="L536" href="source/net/ipv4/fib_frontend.c#L536">536</a> <b><i>/*</i></b>
<a name="L537" href="source/net/ipv4/fib_frontend.c#L537">537</a> <b><i> * Handle IP routing ioctl calls.</i></b>
<a name="L538" href="source/net/ipv4/fib_frontend.c#L538">538</a> <b><i> * These are used to manipulate the routing tables</i></b>
<a name="L539" href="source/net/ipv4/fib_frontend.c#L539">539</a> <b><i> */</i></b>
<a name="L540" href="source/net/ipv4/fib_frontend.c#L540">540</a> int <a href="ident?i=ip_rt_ioctl">ip_rt_ioctl</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>, unsigned int <a href="ident?i=cmd">cmd</a>, void <a href="ident?i=__user">__user</a> *<a href="ident?i=arg">arg</a>)
<a name="L541" href="source/net/ipv4/fib_frontend.c#L541">541</a> {
<a name="L542" href="source/net/ipv4/fib_frontend.c#L542">542</a>         struct <a href="ident?i=fib_config">fib_config</a> <a href="ident?i=cfg">cfg</a>;
<a name="L543" href="source/net/ipv4/fib_frontend.c#L543">543</a>         struct <a href="ident?i=rtentry">rtentry</a> <a href="ident?i=rt">rt</a>;
<a name="L544" href="source/net/ipv4/fib_frontend.c#L544">544</a>         int <a href="ident?i=err">err</a>;
<a name="L545" href="source/net/ipv4/fib_frontend.c#L545">545</a> 
<a name="L546" href="source/net/ipv4/fib_frontend.c#L546">546</a>         switch (<a href="ident?i=cmd">cmd</a>) {
<a name="L547" href="source/net/ipv4/fib_frontend.c#L547">547</a>         case <a href="ident?i=SIOCADDRT">SIOCADDRT</a>:         <b><i>/* Add a route */</i></b>
<a name="L548" href="source/net/ipv4/fib_frontend.c#L548">548</a>         case <a href="ident?i=SIOCDELRT">SIOCDELRT</a>:         <b><i>/* Delete a route */</i></b>
<a name="L549" href="source/net/ipv4/fib_frontend.c#L549">549</a>                 if (!<a href="ident?i=ns_capable">ns_capable</a>(<a href="ident?i=net">net</a>-&gt;<a href="ident?i=user_ns">user_ns</a>, <a href="ident?i=CAP_NET_ADMIN">CAP_NET_ADMIN</a>))
<a name="L550" href="source/net/ipv4/fib_frontend.c#L550">550</a>                         return -<a href="ident?i=EPERM">EPERM</a>;
<a name="L551" href="source/net/ipv4/fib_frontend.c#L551">551</a> 
<a name="L552" href="source/net/ipv4/fib_frontend.c#L552">552</a>                 if (<a href="ident?i=copy_from_user">copy_from_user</a>(&amp;<a href="ident?i=rt">rt</a>, <a href="ident?i=arg">arg</a>, sizeof(<a href="ident?i=rt">rt</a>)))
<a name="L553" href="source/net/ipv4/fib_frontend.c#L553">553</a>                         return -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L554" href="source/net/ipv4/fib_frontend.c#L554">554</a> 
<a name="L555" href="source/net/ipv4/fib_frontend.c#L555">555</a>                 <a href="ident?i=rtnl_lock">rtnl_lock</a>();
<a name="L556" href="source/net/ipv4/fib_frontend.c#L556">556</a>                 <a href="ident?i=err">err</a> = <a href="ident?i=rtentry_to_fib_config">rtentry_to_fib_config</a>(<a href="ident?i=net">net</a>, <a href="ident?i=cmd">cmd</a>, &amp;<a href="ident?i=rt">rt</a>, &amp;<a href="ident?i=cfg">cfg</a>);
<a name="L557" href="source/net/ipv4/fib_frontend.c#L557">557</a>                 if (<a href="ident?i=err">err</a> == 0) {
<a name="L558" href="source/net/ipv4/fib_frontend.c#L558">558</a>                         struct <a href="ident?i=fib_table">fib_table</a> *<a href="ident?i=tb">tb</a>;
<a name="L559" href="source/net/ipv4/fib_frontend.c#L559">559</a> 
<a name="L560" href="source/net/ipv4/fib_frontend.c#L560">560</a>                         if (<a href="ident?i=cmd">cmd</a> == <a href="ident?i=SIOCDELRT">SIOCDELRT</a>) {
<a name="L561" href="source/net/ipv4/fib_frontend.c#L561">561</a>                                 <a href="ident?i=tb">tb</a> = <a href="ident?i=fib_get_table">fib_get_table</a>(<a href="ident?i=net">net</a>, <a href="ident?i=cfg">cfg</a>.fc_table);
<a name="L562" href="source/net/ipv4/fib_frontend.c#L562">562</a>                                 if (<a href="ident?i=tb">tb</a>)
<a name="L563" href="source/net/ipv4/fib_frontend.c#L563">563</a>                                         <a href="ident?i=err">err</a> = <a href="ident?i=fib_table_delete">fib_table_delete</a>(<a href="ident?i=tb">tb</a>, &amp;<a href="ident?i=cfg">cfg</a>);
<a name="L564" href="source/net/ipv4/fib_frontend.c#L564">564</a>                                 else
<a name="L565" href="source/net/ipv4/fib_frontend.c#L565">565</a>                                         <a href="ident?i=err">err</a> = -<a href="ident?i=ESRCH">ESRCH</a>;
<a name="L566" href="source/net/ipv4/fib_frontend.c#L566">566</a>                         } else {
<a name="L567" href="source/net/ipv4/fib_frontend.c#L567">567</a>                                 <a href="ident?i=tb">tb</a> = <a href="ident?i=fib_new_table">fib_new_table</a>(<a href="ident?i=net">net</a>, <a href="ident?i=cfg">cfg</a>.fc_table);
<a name="L568" href="source/net/ipv4/fib_frontend.c#L568">568</a>                                 if (<a href="ident?i=tb">tb</a>)
<a name="L569" href="source/net/ipv4/fib_frontend.c#L569">569</a>                                         <a href="ident?i=err">err</a> = <a href="ident?i=fib_table_insert">fib_table_insert</a>(<a href="ident?i=tb">tb</a>, &amp;<a href="ident?i=cfg">cfg</a>);
<a name="L570" href="source/net/ipv4/fib_frontend.c#L570">570</a>                                 else
<a name="L571" href="source/net/ipv4/fib_frontend.c#L571">571</a>                                         <a href="ident?i=err">err</a> = -<a href="ident?i=ENOBUFS">ENOBUFS</a>;
<a name="L572" href="source/net/ipv4/fib_frontend.c#L572">572</a>                         }
<a name="L573" href="source/net/ipv4/fib_frontend.c#L573">573</a> 
<a name="L574" href="source/net/ipv4/fib_frontend.c#L574">574</a>                         <b><i>/* allocated by rtentry_to_fib_config() */</i></b>
<a name="L575" href="source/net/ipv4/fib_frontend.c#L575">575</a>                         <a href="ident?i=kfree">kfree</a>(<a href="ident?i=cfg">cfg</a>.fc_mx);
<a name="L576" href="source/net/ipv4/fib_frontend.c#L576">576</a>                 }
<a name="L577" href="source/net/ipv4/fib_frontend.c#L577">577</a>                 <a href="ident?i=rtnl_unlock">rtnl_unlock</a>();
<a name="L578" href="source/net/ipv4/fib_frontend.c#L578">578</a>                 return <a href="ident?i=err">err</a>;
<a name="L579" href="source/net/ipv4/fib_frontend.c#L579">579</a>         }
<a name="L580" href="source/net/ipv4/fib_frontend.c#L580">580</a>         return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L581" href="source/net/ipv4/fib_frontend.c#L581">581</a> }
<a name="L582" href="source/net/ipv4/fib_frontend.c#L582">582</a> 
<a name="L583" href="source/net/ipv4/fib_frontend.c#L583">583</a> const struct <a href="ident?i=nla_policy">nla_policy</a> <a href="ident?i=rtm_ipv4_policy">rtm_ipv4_policy</a>[<a href="ident?i=RTA_MAX">RTA_MAX</a> + 1] = {
<a name="L584" href="source/net/ipv4/fib_frontend.c#L584">584</a>         [RTA_DST]               = { .<a href="ident?i=type">type</a> = NLA_U32 },
<a name="L585" href="source/net/ipv4/fib_frontend.c#L585">585</a>         [RTA_SRC]               = { .<a href="ident?i=type">type</a> = NLA_U32 },
<a name="L586" href="source/net/ipv4/fib_frontend.c#L586">586</a>         [RTA_IIF]               = { .<a href="ident?i=type">type</a> = NLA_U32 },
<a name="L587" href="source/net/ipv4/fib_frontend.c#L587">587</a>         [RTA_OIF]               = { .<a href="ident?i=type">type</a> = NLA_U32 },
<a name="L588" href="source/net/ipv4/fib_frontend.c#L588">588</a>         [RTA_GATEWAY]           = { .<a href="ident?i=type">type</a> = NLA_U32 },
<a name="L589" href="source/net/ipv4/fib_frontend.c#L589">589</a>         [RTA_PRIORITY]          = { .<a href="ident?i=type">type</a> = NLA_U32 },
<a name="L590" href="source/net/ipv4/fib_frontend.c#L590">590</a>         [RTA_PREFSRC]           = { .<a href="ident?i=type">type</a> = NLA_U32 },
<a name="L591" href="source/net/ipv4/fib_frontend.c#L591">591</a>         [RTA_METRICS]           = { .<a href="ident?i=type">type</a> = NLA_NESTED },
<a name="L592" href="source/net/ipv4/fib_frontend.c#L592">592</a>         [RTA_MULTIPATH]         = { .<a href="ident?i=len">len</a> = sizeof(struct <a href="ident?i=rtnexthop">rtnexthop</a>) },
<a name="L593" href="source/net/ipv4/fib_frontend.c#L593">593</a>         [RTA_FLOW]              = { .<a href="ident?i=type">type</a> = NLA_U32 },
<a name="L594" href="source/net/ipv4/fib_frontend.c#L594">594</a> };
<a name="L595" href="source/net/ipv4/fib_frontend.c#L595">595</a> 
<a name="L596" href="source/net/ipv4/fib_frontend.c#L596">596</a> static int <a href="ident?i=rtm_to_fib_config">rtm_to_fib_config</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
<a name="L597" href="source/net/ipv4/fib_frontend.c#L597">597</a>                              struct <a href="ident?i=nlmsghdr">nlmsghdr</a> *nlh, struct <a href="ident?i=fib_config">fib_config</a> *<a href="ident?i=cfg">cfg</a>)
<a name="L598" href="source/net/ipv4/fib_frontend.c#L598">598</a> {
<a name="L599" href="source/net/ipv4/fib_frontend.c#L599">599</a>         struct <a href="ident?i=nlattr">nlattr</a> *<a href="ident?i=attr">attr</a>;
<a name="L600" href="source/net/ipv4/fib_frontend.c#L600">600</a>         int <a href="ident?i=err">err</a>, <a href="ident?i=remaining">remaining</a>;
<a name="L601" href="source/net/ipv4/fib_frontend.c#L601">601</a>         struct <a href="ident?i=rtmsg">rtmsg</a> *rtm;
<a name="L602" href="source/net/ipv4/fib_frontend.c#L602">602</a> 
<a name="L603" href="source/net/ipv4/fib_frontend.c#L603">603</a>         <a href="ident?i=err">err</a> = <a href="ident?i=nlmsg_validate">nlmsg_validate</a>(nlh, sizeof(*rtm), <a href="ident?i=RTA_MAX">RTA_MAX</a>, <a href="ident?i=rtm_ipv4_policy">rtm_ipv4_policy</a>);
<a name="L604" href="source/net/ipv4/fib_frontend.c#L604">604</a>         if (<a href="ident?i=err">err</a> &lt; 0)
<a name="L605" href="source/net/ipv4/fib_frontend.c#L605">605</a>                 goto errout;
<a name="L606" href="source/net/ipv4/fib_frontend.c#L606">606</a> 
<a name="L607" href="source/net/ipv4/fib_frontend.c#L607">607</a>         <a href="ident?i=memset">memset</a>(<a href="ident?i=cfg">cfg</a>, 0, sizeof(*<a href="ident?i=cfg">cfg</a>));
<a name="L608" href="source/net/ipv4/fib_frontend.c#L608">608</a> 
<a name="L609" href="source/net/ipv4/fib_frontend.c#L609">609</a>         rtm = <a href="ident?i=nlmsg_data">nlmsg_data</a>(nlh);
<a name="L610" href="source/net/ipv4/fib_frontend.c#L610">610</a>         <a href="ident?i=cfg">cfg</a>-&gt;fc_dst_len = rtm-&gt;rtm_dst_len;
<a name="L611" href="source/net/ipv4/fib_frontend.c#L611">611</a>         <a href="ident?i=cfg">cfg</a>-&gt;fc_tos = rtm-&gt;rtm_tos;
<a name="L612" href="source/net/ipv4/fib_frontend.c#L612">612</a>         <a href="ident?i=cfg">cfg</a>-&gt;fc_table = rtm-&gt;rtm_table;
<a name="L613" href="source/net/ipv4/fib_frontend.c#L613">613</a>         <a href="ident?i=cfg">cfg</a>-&gt;fc_protocol = rtm-&gt;rtm_protocol;
<a name="L614" href="source/net/ipv4/fib_frontend.c#L614">614</a>         <a href="ident?i=cfg">cfg</a>-&gt;fc_scope = rtm-&gt;rtm_scope;
<a name="L615" href="source/net/ipv4/fib_frontend.c#L615">615</a>         <a href="ident?i=cfg">cfg</a>-&gt;<a href="ident?i=fc_type">fc_type</a> = rtm-&gt;rtm_type;
<a name="L616" href="source/net/ipv4/fib_frontend.c#L616">616</a>         <a href="ident?i=cfg">cfg</a>-&gt;fc_flags = rtm-&gt;rtm_flags;
<a name="L617" href="source/net/ipv4/fib_frontend.c#L617">617</a>         <a href="ident?i=cfg">cfg</a>-&gt;fc_nlflags = nlh-&gt;nlmsg_flags;
<a name="L618" href="source/net/ipv4/fib_frontend.c#L618">618</a> 
<a name="L619" href="source/net/ipv4/fib_frontend.c#L619">619</a>         <a href="ident?i=cfg">cfg</a>-&gt;fc_nlinfo.portid = <a href="ident?i=NETLINK_CB">NETLINK_CB</a>(<a href="ident?i=skb">skb</a>).portid;
<a name="L620" href="source/net/ipv4/fib_frontend.c#L620">620</a>         <a href="ident?i=cfg">cfg</a>-&gt;fc_nlinfo.nlh = nlh;
<a name="L621" href="source/net/ipv4/fib_frontend.c#L621">621</a>         <a href="ident?i=cfg">cfg</a>-&gt;fc_nlinfo.nl_net = <a href="ident?i=net">net</a>;
<a name="L622" href="source/net/ipv4/fib_frontend.c#L622">622</a> 
<a name="L623" href="source/net/ipv4/fib_frontend.c#L623">623</a>         if (<a href="ident?i=cfg">cfg</a>-&gt;<a href="ident?i=fc_type">fc_type</a> &gt; <a href="ident?i=RTN_MAX">RTN_MAX</a>) {
<a name="L624" href="source/net/ipv4/fib_frontend.c#L624">624</a>                 <a href="ident?i=err">err</a> = -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L625" href="source/net/ipv4/fib_frontend.c#L625">625</a>                 goto errout;
<a name="L626" href="source/net/ipv4/fib_frontend.c#L626">626</a>         }
<a name="L627" href="source/net/ipv4/fib_frontend.c#L627">627</a> 
<a name="L628" href="source/net/ipv4/fib_frontend.c#L628">628</a>         <a href="ident?i=nlmsg_for_each_attr">nlmsg_for_each_attr</a>(<a href="ident?i=attr">attr</a>, nlh, sizeof(struct <a href="ident?i=rtmsg">rtmsg</a>), <a href="ident?i=remaining">remaining</a>) {
<a name="L629" href="source/net/ipv4/fib_frontend.c#L629">629</a>                 switch (<a href="ident?i=nla_type">nla_type</a>(<a href="ident?i=attr">attr</a>)) {
<a name="L630" href="source/net/ipv4/fib_frontend.c#L630">630</a>                 case RTA_DST:
<a name="L631" href="source/net/ipv4/fib_frontend.c#L631">631</a>                         <a href="ident?i=cfg">cfg</a>-&gt;fc_dst = <a href="ident?i=nla_get_be32">nla_get_be32</a>(<a href="ident?i=attr">attr</a>);
<a name="L632" href="source/net/ipv4/fib_frontend.c#L632">632</a>                         break;
<a name="L633" href="source/net/ipv4/fib_frontend.c#L633">633</a>                 case RTA_OIF:
<a name="L634" href="source/net/ipv4/fib_frontend.c#L634">634</a>                         <a href="ident?i=cfg">cfg</a>-&gt;fc_oif = <a href="ident?i=nla_get_u32">nla_get_u32</a>(<a href="ident?i=attr">attr</a>);
<a name="L635" href="source/net/ipv4/fib_frontend.c#L635">635</a>                         break;
<a name="L636" href="source/net/ipv4/fib_frontend.c#L636">636</a>                 case RTA_GATEWAY:
<a name="L637" href="source/net/ipv4/fib_frontend.c#L637">637</a>                         <a href="ident?i=cfg">cfg</a>-&gt;fc_gw = <a href="ident?i=nla_get_be32">nla_get_be32</a>(<a href="ident?i=attr">attr</a>);
<a name="L638" href="source/net/ipv4/fib_frontend.c#L638">638</a>                         break;
<a name="L639" href="source/net/ipv4/fib_frontend.c#L639">639</a>                 case RTA_PRIORITY:
<a name="L640" href="source/net/ipv4/fib_frontend.c#L640">640</a>                         <a href="ident?i=cfg">cfg</a>-&gt;fc_priority = <a href="ident?i=nla_get_u32">nla_get_u32</a>(<a href="ident?i=attr">attr</a>);
<a name="L641" href="source/net/ipv4/fib_frontend.c#L641">641</a>                         break;
<a name="L642" href="source/net/ipv4/fib_frontend.c#L642">642</a>                 case RTA_PREFSRC:
<a name="L643" href="source/net/ipv4/fib_frontend.c#L643">643</a>                         <a href="ident?i=cfg">cfg</a>-&gt;fc_prefsrc = <a href="ident?i=nla_get_be32">nla_get_be32</a>(<a href="ident?i=attr">attr</a>);
<a name="L644" href="source/net/ipv4/fib_frontend.c#L644">644</a>                         break;
<a name="L645" href="source/net/ipv4/fib_frontend.c#L645">645</a>                 case RTA_METRICS:
<a name="L646" href="source/net/ipv4/fib_frontend.c#L646">646</a>                         <a href="ident?i=cfg">cfg</a>-&gt;fc_mx = <a href="ident?i=nla_data">nla_data</a>(<a href="ident?i=attr">attr</a>);
<a name="L647" href="source/net/ipv4/fib_frontend.c#L647">647</a>                         <a href="ident?i=cfg">cfg</a>-&gt;fc_mx_len = <a href="ident?i=nla_len">nla_len</a>(<a href="ident?i=attr">attr</a>);
<a name="L648" href="source/net/ipv4/fib_frontend.c#L648">648</a>                         break;
<a name="L649" href="source/net/ipv4/fib_frontend.c#L649">649</a>                 case RTA_MULTIPATH:
<a name="L650" href="source/net/ipv4/fib_frontend.c#L650">650</a>                         <a href="ident?i=cfg">cfg</a>-&gt;fc_mp = <a href="ident?i=nla_data">nla_data</a>(<a href="ident?i=attr">attr</a>);
<a name="L651" href="source/net/ipv4/fib_frontend.c#L651">651</a>                         <a href="ident?i=cfg">cfg</a>-&gt;fc_mp_len = <a href="ident?i=nla_len">nla_len</a>(<a href="ident?i=attr">attr</a>);
<a name="L652" href="source/net/ipv4/fib_frontend.c#L652">652</a>                         break;
<a name="L653" href="source/net/ipv4/fib_frontend.c#L653">653</a>                 case RTA_FLOW:
<a name="L654" href="source/net/ipv4/fib_frontend.c#L654">654</a>                         <a href="ident?i=cfg">cfg</a>-&gt;fc_flow = <a href="ident?i=nla_get_u32">nla_get_u32</a>(<a href="ident?i=attr">attr</a>);
<a name="L655" href="source/net/ipv4/fib_frontend.c#L655">655</a>                         break;
<a name="L656" href="source/net/ipv4/fib_frontend.c#L656">656</a>                 case RTA_TABLE:
<a name="L657" href="source/net/ipv4/fib_frontend.c#L657">657</a>                         <a href="ident?i=cfg">cfg</a>-&gt;fc_table = <a href="ident?i=nla_get_u32">nla_get_u32</a>(<a href="ident?i=attr">attr</a>);
<a name="L658" href="source/net/ipv4/fib_frontend.c#L658">658</a>                         break;
<a name="L659" href="source/net/ipv4/fib_frontend.c#L659">659</a>                 }
<a name="L660" href="source/net/ipv4/fib_frontend.c#L660">660</a>         }
<a name="L661" href="source/net/ipv4/fib_frontend.c#L661">661</a> 
<a name="L662" href="source/net/ipv4/fib_frontend.c#L662">662</a>         return 0;
<a name="L663" href="source/net/ipv4/fib_frontend.c#L663">663</a> errout:
<a name="L664" href="source/net/ipv4/fib_frontend.c#L664">664</a>         return <a href="ident?i=err">err</a>;
<a name="L665" href="source/net/ipv4/fib_frontend.c#L665">665</a> }
<a name="L666" href="source/net/ipv4/fib_frontend.c#L666">666</a> 
<a name="L667" href="source/net/ipv4/fib_frontend.c#L667">667</a> static int <a href="ident?i=inet_rtm_delroute">inet_rtm_delroute</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, struct <a href="ident?i=nlmsghdr">nlmsghdr</a> *nlh)
<a name="L668" href="source/net/ipv4/fib_frontend.c#L668">668</a> {
<a name="L669" href="source/net/ipv4/fib_frontend.c#L669">669</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=sock_net">sock_net</a>(<a href="ident?i=skb">skb</a>-&gt;sk);
<a name="L670" href="source/net/ipv4/fib_frontend.c#L670">670</a>         struct <a href="ident?i=fib_config">fib_config</a> <a href="ident?i=cfg">cfg</a>;
<a name="L671" href="source/net/ipv4/fib_frontend.c#L671">671</a>         struct <a href="ident?i=fib_table">fib_table</a> *<a href="ident?i=tb">tb</a>;
<a name="L672" href="source/net/ipv4/fib_frontend.c#L672">672</a>         int <a href="ident?i=err">err</a>;
<a name="L673" href="source/net/ipv4/fib_frontend.c#L673">673</a> 
<a name="L674" href="source/net/ipv4/fib_frontend.c#L674">674</a>         <a href="ident?i=err">err</a> = <a href="ident?i=rtm_to_fib_config">rtm_to_fib_config</a>(<a href="ident?i=net">net</a>, <a href="ident?i=skb">skb</a>, nlh, &amp;<a href="ident?i=cfg">cfg</a>);
<a name="L675" href="source/net/ipv4/fib_frontend.c#L675">675</a>         if (<a href="ident?i=err">err</a> &lt; 0)
<a name="L676" href="source/net/ipv4/fib_frontend.c#L676">676</a>                 goto errout;
<a name="L677" href="source/net/ipv4/fib_frontend.c#L677">677</a> 
<a name="L678" href="source/net/ipv4/fib_frontend.c#L678">678</a>         <a href="ident?i=tb">tb</a> = <a href="ident?i=fib_get_table">fib_get_table</a>(<a href="ident?i=net">net</a>, <a href="ident?i=cfg">cfg</a>.fc_table);
<a name="L679" href="source/net/ipv4/fib_frontend.c#L679">679</a>         if (!<a href="ident?i=tb">tb</a>) {
<a name="L680" href="source/net/ipv4/fib_frontend.c#L680">680</a>                 <a href="ident?i=err">err</a> = -<a href="ident?i=ESRCH">ESRCH</a>;
<a name="L681" href="source/net/ipv4/fib_frontend.c#L681">681</a>                 goto errout;
<a name="L682" href="source/net/ipv4/fib_frontend.c#L682">682</a>         }
<a name="L683" href="source/net/ipv4/fib_frontend.c#L683">683</a> 
<a name="L684" href="source/net/ipv4/fib_frontend.c#L684">684</a>         <a href="ident?i=err">err</a> = <a href="ident?i=fib_table_delete">fib_table_delete</a>(<a href="ident?i=tb">tb</a>, &amp;<a href="ident?i=cfg">cfg</a>);
<a name="L685" href="source/net/ipv4/fib_frontend.c#L685">685</a> errout:
<a name="L686" href="source/net/ipv4/fib_frontend.c#L686">686</a>         return <a href="ident?i=err">err</a>;
<a name="L687" href="source/net/ipv4/fib_frontend.c#L687">687</a> }
<a name="L688" href="source/net/ipv4/fib_frontend.c#L688">688</a> 
<a name="L689" href="source/net/ipv4/fib_frontend.c#L689">689</a> static int <a href="ident?i=inet_rtm_newroute">inet_rtm_newroute</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, struct <a href="ident?i=nlmsghdr">nlmsghdr</a> *nlh)
<a name="L690" href="source/net/ipv4/fib_frontend.c#L690">690</a> {
<a name="L691" href="source/net/ipv4/fib_frontend.c#L691">691</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=sock_net">sock_net</a>(<a href="ident?i=skb">skb</a>-&gt;sk);
<a name="L692" href="source/net/ipv4/fib_frontend.c#L692">692</a>         struct <a href="ident?i=fib_config">fib_config</a> <a href="ident?i=cfg">cfg</a>;
<a name="L693" href="source/net/ipv4/fib_frontend.c#L693">693</a>         struct <a href="ident?i=fib_table">fib_table</a> *<a href="ident?i=tb">tb</a>;
<a name="L694" href="source/net/ipv4/fib_frontend.c#L694">694</a>         int <a href="ident?i=err">err</a>;
<a name="L695" href="source/net/ipv4/fib_frontend.c#L695">695</a> 
<a name="L696" href="source/net/ipv4/fib_frontend.c#L696">696</a>         <a href="ident?i=err">err</a> = <a href="ident?i=rtm_to_fib_config">rtm_to_fib_config</a>(<a href="ident?i=net">net</a>, <a href="ident?i=skb">skb</a>, nlh, &amp;<a href="ident?i=cfg">cfg</a>);
<a name="L697" href="source/net/ipv4/fib_frontend.c#L697">697</a>         if (<a href="ident?i=err">err</a> &lt; 0)
<a name="L698" href="source/net/ipv4/fib_frontend.c#L698">698</a>                 goto errout;
<a name="L699" href="source/net/ipv4/fib_frontend.c#L699">699</a> 
<a name="L700" href="source/net/ipv4/fib_frontend.c#L700">700</a>         <a href="ident?i=tb">tb</a> = <a href="ident?i=fib_new_table">fib_new_table</a>(<a href="ident?i=net">net</a>, <a href="ident?i=cfg">cfg</a>.fc_table);
<a name="L701" href="source/net/ipv4/fib_frontend.c#L701">701</a>         if (!<a href="ident?i=tb">tb</a>) {
<a name="L702" href="source/net/ipv4/fib_frontend.c#L702">702</a>                 <a href="ident?i=err">err</a> = -<a href="ident?i=ENOBUFS">ENOBUFS</a>;
<a name="L703" href="source/net/ipv4/fib_frontend.c#L703">703</a>                 goto errout;
<a name="L704" href="source/net/ipv4/fib_frontend.c#L704">704</a>         }
<a name="L705" href="source/net/ipv4/fib_frontend.c#L705">705</a> 
<a name="L706" href="source/net/ipv4/fib_frontend.c#L706">706</a>         <a href="ident?i=err">err</a> = <a href="ident?i=fib_table_insert">fib_table_insert</a>(<a href="ident?i=tb">tb</a>, &amp;<a href="ident?i=cfg">cfg</a>);
<a name="L707" href="source/net/ipv4/fib_frontend.c#L707">707</a> errout:
<a name="L708" href="source/net/ipv4/fib_frontend.c#L708">708</a>         return <a href="ident?i=err">err</a>;
<a name="L709" href="source/net/ipv4/fib_frontend.c#L709">709</a> }
<a name="L710" href="source/net/ipv4/fib_frontend.c#L710">710</a> 
<a name="L711" href="source/net/ipv4/fib_frontend.c#L711">711</a> static int <a href="ident?i=inet_dump_fib">inet_dump_fib</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, struct <a href="ident?i=netlink_callback">netlink_callback</a> *<a href="ident?i=cb">cb</a>)
<a name="L712" href="source/net/ipv4/fib_frontend.c#L712">712</a> {
<a name="L713" href="source/net/ipv4/fib_frontend.c#L713">713</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=sock_net">sock_net</a>(<a href="ident?i=skb">skb</a>-&gt;sk);
<a name="L714" href="source/net/ipv4/fib_frontend.c#L714">714</a>         unsigned int <a href="ident?i=h">h</a>, s_h;
<a name="L715" href="source/net/ipv4/fib_frontend.c#L715">715</a>         unsigned int <a href="ident?i=e">e</a> = 0, s_e;
<a name="L716" href="source/net/ipv4/fib_frontend.c#L716">716</a>         struct <a href="ident?i=fib_table">fib_table</a> *<a href="ident?i=tb">tb</a>;
<a name="L717" href="source/net/ipv4/fib_frontend.c#L717">717</a>         struct <a href="ident?i=hlist_head">hlist_head</a> *<a href="ident?i=head">head</a>;
<a name="L718" href="source/net/ipv4/fib_frontend.c#L718">718</a>         int dumped = 0;
<a name="L719" href="source/net/ipv4/fib_frontend.c#L719">719</a> 
<a name="L720" href="source/net/ipv4/fib_frontend.c#L720">720</a>         if (<a href="ident?i=nlmsg_len">nlmsg_len</a>(<a href="ident?i=cb">cb</a>-&gt;nlh) &gt;= sizeof(struct <a href="ident?i=rtmsg">rtmsg</a>) &amp;&amp;
<a name="L721" href="source/net/ipv4/fib_frontend.c#L721">721</a>             ((struct <a href="ident?i=rtmsg">rtmsg</a> *) <a href="ident?i=nlmsg_data">nlmsg_data</a>(<a href="ident?i=cb">cb</a>-&gt;nlh))-&gt;rtm_flags &amp; <a href="ident?i=RTM_F_CLONED">RTM_F_CLONED</a>)
<a name="L722" href="source/net/ipv4/fib_frontend.c#L722">722</a>                 return <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a>;
<a name="L723" href="source/net/ipv4/fib_frontend.c#L723">723</a> 
<a name="L724" href="source/net/ipv4/fib_frontend.c#L724">724</a>         s_h = <a href="ident?i=cb">cb</a>-&gt;<a href="ident?i=args">args</a>[0];
<a name="L725" href="source/net/ipv4/fib_frontend.c#L725">725</a>         s_e = <a href="ident?i=cb">cb</a>-&gt;<a href="ident?i=args">args</a>[1];
<a name="L726" href="source/net/ipv4/fib_frontend.c#L726">726</a> 
<a name="L727" href="source/net/ipv4/fib_frontend.c#L727">727</a>         <a href="ident?i=rcu_read_lock">rcu_read_lock</a>();
<a name="L728" href="source/net/ipv4/fib_frontend.c#L728">728</a> 
<a name="L729" href="source/net/ipv4/fib_frontend.c#L729">729</a>         for (<a href="ident?i=h">h</a> = s_h; <a href="ident?i=h">h</a> &lt; <a href="ident?i=FIB_TABLE_HASHSZ">FIB_TABLE_HASHSZ</a>; <a href="ident?i=h">h</a>++, s_e = 0) {
<a name="L730" href="source/net/ipv4/fib_frontend.c#L730">730</a>                 <a href="ident?i=e">e</a> = 0;
<a name="L731" href="source/net/ipv4/fib_frontend.c#L731">731</a>                 <a href="ident?i=head">head</a> = &amp;<a href="ident?i=net">net</a>-&gt;ipv4.fib_table_hash[<a href="ident?i=h">h</a>];
<a name="L732" href="source/net/ipv4/fib_frontend.c#L732">732</a>                 <a href="ident?i=hlist_for_each_entry_rcu">hlist_for_each_entry_rcu</a>(<a href="ident?i=tb">tb</a>, <a href="ident?i=head">head</a>, tb_hlist) {
<a name="L733" href="source/net/ipv4/fib_frontend.c#L733">733</a>                         if (<a href="ident?i=e">e</a> &lt; s_e)
<a name="L734" href="source/net/ipv4/fib_frontend.c#L734">734</a>                                 goto <a href="ident?i=next">next</a>;
<a name="L735" href="source/net/ipv4/fib_frontend.c#L735">735</a>                         if (dumped)
<a name="L736" href="source/net/ipv4/fib_frontend.c#L736">736</a>                                 <a href="ident?i=memset">memset</a>(&amp;<a href="ident?i=cb">cb</a>-&gt;<a href="ident?i=args">args</a>[2], 0, sizeof(<a href="ident?i=cb">cb</a>-&gt;<a href="ident?i=args">args</a>) -
<a name="L737" href="source/net/ipv4/fib_frontend.c#L737">737</a>                                                  2 * sizeof(<a href="ident?i=cb">cb</a>-&gt;<a href="ident?i=args">args</a>[0]));
<a name="L738" href="source/net/ipv4/fib_frontend.c#L738">738</a>                         if (<a href="ident?i=fib_table_dump">fib_table_dump</a>(<a href="ident?i=tb">tb</a>, <a href="ident?i=skb">skb</a>, <a href="ident?i=cb">cb</a>) &lt; 0)
<a name="L739" href="source/net/ipv4/fib_frontend.c#L739">739</a>                                 goto <a href="ident?i=out">out</a>;
<a name="L740" href="source/net/ipv4/fib_frontend.c#L740">740</a>                         dumped = 1;
<a name="L741" href="source/net/ipv4/fib_frontend.c#L741">741</a> <a href="ident?i=next">next</a>:
<a name="L742" href="source/net/ipv4/fib_frontend.c#L742">742</a>                         <a href="ident?i=e">e</a>++;
<a name="L743" href="source/net/ipv4/fib_frontend.c#L743">743</a>                 }
<a name="L744" href="source/net/ipv4/fib_frontend.c#L744">744</a>         }
<a name="L745" href="source/net/ipv4/fib_frontend.c#L745">745</a> <a href="ident?i=out">out</a>:
<a name="L746" href="source/net/ipv4/fib_frontend.c#L746">746</a>         <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L747" href="source/net/ipv4/fib_frontend.c#L747">747</a> 
<a name="L748" href="source/net/ipv4/fib_frontend.c#L748">748</a>         <a href="ident?i=cb">cb</a>-&gt;<a href="ident?i=args">args</a>[1] = <a href="ident?i=e">e</a>;
<a name="L749" href="source/net/ipv4/fib_frontend.c#L749">749</a>         <a href="ident?i=cb">cb</a>-&gt;<a href="ident?i=args">args</a>[0] = <a href="ident?i=h">h</a>;
<a name="L750" href="source/net/ipv4/fib_frontend.c#L750">750</a> 
<a name="L751" href="source/net/ipv4/fib_frontend.c#L751">751</a>         return <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a>;
<a name="L752" href="source/net/ipv4/fib_frontend.c#L752">752</a> }
<a name="L753" href="source/net/ipv4/fib_frontend.c#L753">753</a> 
<a name="L754" href="source/net/ipv4/fib_frontend.c#L754">754</a> <b><i>/* Prepare and feed intra-kernel routing request.</i></b>
<a name="L755" href="source/net/ipv4/fib_frontend.c#L755">755</a> <b><i> * Really, it should be netlink message, but :-( netlink</i></b>
<a name="L756" href="source/net/ipv4/fib_frontend.c#L756">756</a> <b><i> * can be not configured, so that we feed it directly</i></b>
<a name="L757" href="source/net/ipv4/fib_frontend.c#L757">757</a> <b><i> * to fib engine. It is legal, because all events occur</i></b>
<a name="L758" href="source/net/ipv4/fib_frontend.c#L758">758</a> <b><i> * only when netlink is already locked.</i></b>
<a name="L759" href="source/net/ipv4/fib_frontend.c#L759">759</a> <b><i> */</i></b>
<a name="L760" href="source/net/ipv4/fib_frontend.c#L760">760</a> static void <a href="ident?i=fib_magic">fib_magic</a>(int <a href="ident?i=cmd">cmd</a>, int <a href="ident?i=type">type</a>, <a href="ident?i=__be32">__be32</a> <a href="ident?i=dst">dst</a>, int dst_len, struct <a href="ident?i=in_ifaddr">in_ifaddr</a> *<a href="ident?i=ifa">ifa</a>)
<a name="L761" href="source/net/ipv4/fib_frontend.c#L761">761</a> {
<a name="L762" href="source/net/ipv4/fib_frontend.c#L762">762</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=ifa">ifa</a>-&gt;ifa_dev-&gt;<a href="ident?i=dev">dev</a>);
<a name="L763" href="source/net/ipv4/fib_frontend.c#L763">763</a>         struct <a href="ident?i=fib_table">fib_table</a> *<a href="ident?i=tb">tb</a>;
<a name="L764" href="source/net/ipv4/fib_frontend.c#L764">764</a>         struct <a href="ident?i=fib_config">fib_config</a> <a href="ident?i=cfg">cfg</a> = {
<a name="L765" href="source/net/ipv4/fib_frontend.c#L765">765</a>                 .fc_protocol = <a href="ident?i=RTPROT_KERNEL">RTPROT_KERNEL</a>,
<a name="L766" href="source/net/ipv4/fib_frontend.c#L766">766</a>                 .<a href="ident?i=fc_type">fc_type</a> = <a href="ident?i=type">type</a>,
<a name="L767" href="source/net/ipv4/fib_frontend.c#L767">767</a>                 .fc_dst = <a href="ident?i=dst">dst</a>,
<a name="L768" href="source/net/ipv4/fib_frontend.c#L768">768</a>                 .fc_dst_len = dst_len,
<a name="L769" href="source/net/ipv4/fib_frontend.c#L769">769</a>                 .fc_prefsrc = <a href="ident?i=ifa">ifa</a>-&gt;ifa_local,
<a name="L770" href="source/net/ipv4/fib_frontend.c#L770">770</a>                 .fc_oif = <a href="ident?i=ifa">ifa</a>-&gt;ifa_dev-&gt;<a href="ident?i=dev">dev</a>-&gt;ifindex,
<a name="L771" href="source/net/ipv4/fib_frontend.c#L771">771</a>                 .fc_nlflags = <a href="ident?i=NLM_F_CREATE">NLM_F_CREATE</a> | <a href="ident?i=NLM_F_APPEND">NLM_F_APPEND</a>,
<a name="L772" href="source/net/ipv4/fib_frontend.c#L772">772</a>                 .fc_nlinfo = {
<a name="L773" href="source/net/ipv4/fib_frontend.c#L773">773</a>                         .nl_net = <a href="ident?i=net">net</a>,
<a name="L774" href="source/net/ipv4/fib_frontend.c#L774">774</a>                 },
<a name="L775" href="source/net/ipv4/fib_frontend.c#L775">775</a>         };
<a name="L776" href="source/net/ipv4/fib_frontend.c#L776">776</a> 
<a name="L777" href="source/net/ipv4/fib_frontend.c#L777">777</a>         if (<a href="ident?i=type">type</a> == RTN_UNICAST)
<a name="L778" href="source/net/ipv4/fib_frontend.c#L778">778</a>                 <a href="ident?i=tb">tb</a> = <a href="ident?i=fib_new_table">fib_new_table</a>(<a href="ident?i=net">net</a>, RT_TABLE_MAIN);
<a name="L779" href="source/net/ipv4/fib_frontend.c#L779">779</a>         else
<a name="L780" href="source/net/ipv4/fib_frontend.c#L780">780</a>                 <a href="ident?i=tb">tb</a> = <a href="ident?i=fib_new_table">fib_new_table</a>(<a href="ident?i=net">net</a>, RT_TABLE_LOCAL);
<a name="L781" href="source/net/ipv4/fib_frontend.c#L781">781</a> 
<a name="L782" href="source/net/ipv4/fib_frontend.c#L782">782</a>         if (!<a href="ident?i=tb">tb</a>)
<a name="L783" href="source/net/ipv4/fib_frontend.c#L783">783</a>                 return;
<a name="L784" href="source/net/ipv4/fib_frontend.c#L784">784</a> 
<a name="L785" href="source/net/ipv4/fib_frontend.c#L785">785</a>         <a href="ident?i=cfg">cfg</a>.fc_table = <a href="ident?i=tb">tb</a>-&gt;tb_id;
<a name="L786" href="source/net/ipv4/fib_frontend.c#L786">786</a> 
<a name="L787" href="source/net/ipv4/fib_frontend.c#L787">787</a>         if (<a href="ident?i=type">type</a> != RTN_LOCAL)
<a name="L788" href="source/net/ipv4/fib_frontend.c#L788">788</a>                 <a href="ident?i=cfg">cfg</a>.fc_scope = RT_SCOPE_LINK;
<a name="L789" href="source/net/ipv4/fib_frontend.c#L789">789</a>         else
<a name="L790" href="source/net/ipv4/fib_frontend.c#L790">790</a>                 <a href="ident?i=cfg">cfg</a>.fc_scope = RT_SCOPE_HOST;
<a name="L791" href="source/net/ipv4/fib_frontend.c#L791">791</a> 
<a name="L792" href="source/net/ipv4/fib_frontend.c#L792">792</a>         if (<a href="ident?i=cmd">cmd</a> == <a href="ident?i=RTM_NEWROUTE">RTM_NEWROUTE</a>)
<a name="L793" href="source/net/ipv4/fib_frontend.c#L793">793</a>                 <a href="ident?i=fib_table_insert">fib_table_insert</a>(<a href="ident?i=tb">tb</a>, &amp;<a href="ident?i=cfg">cfg</a>);
<a name="L794" href="source/net/ipv4/fib_frontend.c#L794">794</a>         else
<a name="L795" href="source/net/ipv4/fib_frontend.c#L795">795</a>                 <a href="ident?i=fib_table_delete">fib_table_delete</a>(<a href="ident?i=tb">tb</a>, &amp;<a href="ident?i=cfg">cfg</a>);
<a name="L796" href="source/net/ipv4/fib_frontend.c#L796">796</a> }
<a name="L797" href="source/net/ipv4/fib_frontend.c#L797">797</a> 
<a name="L798" href="source/net/ipv4/fib_frontend.c#L798">798</a> void <a href="ident?i=fib_add_ifaddr">fib_add_ifaddr</a>(struct <a href="ident?i=in_ifaddr">in_ifaddr</a> *<a href="ident?i=ifa">ifa</a>)
<a name="L799" href="source/net/ipv4/fib_frontend.c#L799">799</a> {
<a name="L800" href="source/net/ipv4/fib_frontend.c#L800">800</a>         struct <a href="ident?i=in_device">in_device</a> *in_dev = <a href="ident?i=ifa">ifa</a>-&gt;ifa_dev;
<a name="L801" href="source/net/ipv4/fib_frontend.c#L801">801</a>         struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a> = in_dev-&gt;<a href="ident?i=dev">dev</a>;
<a name="L802" href="source/net/ipv4/fib_frontend.c#L802">802</a>         struct <a href="ident?i=in_ifaddr">in_ifaddr</a> *prim = <a href="ident?i=ifa">ifa</a>;
<a name="L803" href="source/net/ipv4/fib_frontend.c#L803">803</a>         <a href="ident?i=__be32">__be32</a> <a href="ident?i=mask">mask</a> = <a href="ident?i=ifa">ifa</a>-&gt;ifa_mask;
<a name="L804" href="source/net/ipv4/fib_frontend.c#L804">804</a>         <a href="ident?i=__be32">__be32</a> <a href="ident?i=addr">addr</a> = <a href="ident?i=ifa">ifa</a>-&gt;ifa_local;
<a name="L805" href="source/net/ipv4/fib_frontend.c#L805">805</a>         <a href="ident?i=__be32">__be32</a> <a href="ident?i=prefix">prefix</a> = <a href="ident?i=ifa">ifa</a>-&gt;ifa_address &amp; <a href="ident?i=mask">mask</a>;
<a name="L806" href="source/net/ipv4/fib_frontend.c#L806">806</a> 
<a name="L807" href="source/net/ipv4/fib_frontend.c#L807">807</a>         if (<a href="ident?i=ifa">ifa</a>-&gt;ifa_flags &amp; <a href="ident?i=IFA_F_SECONDARY">IFA_F_SECONDARY</a>) {
<a name="L808" href="source/net/ipv4/fib_frontend.c#L808">808</a>                 prim = <a href="ident?i=inet_ifa_byprefix">inet_ifa_byprefix</a>(in_dev, <a href="ident?i=prefix">prefix</a>, <a href="ident?i=mask">mask</a>);
<a name="L809" href="source/net/ipv4/fib_frontend.c#L809">809</a>                 if (!prim) {
<a name="L810" href="source/net/ipv4/fib_frontend.c#L810">810</a>                         <a href="ident?i=pr_warn">pr_warn</a>(<i>"%s: bug: prim == NULL\n"</i>, <a href="ident?i=__func__">__func__</a>);
<a name="L811" href="source/net/ipv4/fib_frontend.c#L811">811</a>                         return;
<a name="L812" href="source/net/ipv4/fib_frontend.c#L812">812</a>                 }
<a name="L813" href="source/net/ipv4/fib_frontend.c#L813">813</a>         }
<a name="L814" href="source/net/ipv4/fib_frontend.c#L814">814</a> 
<a name="L815" href="source/net/ipv4/fib_frontend.c#L815">815</a>         <a href="ident?i=fib_magic">fib_magic</a>(<a href="ident?i=RTM_NEWROUTE">RTM_NEWROUTE</a>, RTN_LOCAL, <a href="ident?i=addr">addr</a>, 32, prim);
<a name="L816" href="source/net/ipv4/fib_frontend.c#L816">816</a> 
<a name="L817" href="source/net/ipv4/fib_frontend.c#L817">817</a>         if (!(<a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=IFF_UP">IFF_UP</a>))
<a name="L818" href="source/net/ipv4/fib_frontend.c#L818">818</a>                 return;
<a name="L819" href="source/net/ipv4/fib_frontend.c#L819">819</a> 
<a name="L820" href="source/net/ipv4/fib_frontend.c#L820">820</a>         <b><i>/* Add broadcast address, if it is explicitly assigned. */</i></b>
<a name="L821" href="source/net/ipv4/fib_frontend.c#L821">821</a>         if (<a href="ident?i=ifa">ifa</a>-&gt;ifa_broadcast &amp;&amp; <a href="ident?i=ifa">ifa</a>-&gt;ifa_broadcast != <a href="ident?i=htonl">htonl</a>(0xFFFFFFFF))
<a name="L822" href="source/net/ipv4/fib_frontend.c#L822">822</a>                 <a href="ident?i=fib_magic">fib_magic</a>(<a href="ident?i=RTM_NEWROUTE">RTM_NEWROUTE</a>, RTN_BROADCAST, <a href="ident?i=ifa">ifa</a>-&gt;ifa_broadcast, 32, prim);
<a name="L823" href="source/net/ipv4/fib_frontend.c#L823">823</a> 
<a name="L824" href="source/net/ipv4/fib_frontend.c#L824">824</a>         if (!<a href="ident?i=ipv4_is_zeronet">ipv4_is_zeronet</a>(<a href="ident?i=prefix">prefix</a>) &amp;&amp; !(<a href="ident?i=ifa">ifa</a>-&gt;ifa_flags &amp; <a href="ident?i=IFA_F_SECONDARY">IFA_F_SECONDARY</a>) &amp;&amp;
<a name="L825" href="source/net/ipv4/fib_frontend.c#L825">825</a>             (<a href="ident?i=prefix">prefix</a> != <a href="ident?i=addr">addr</a> || <a href="ident?i=ifa">ifa</a>-&gt;ifa_prefixlen &lt; 32)) {
<a name="L826" href="source/net/ipv4/fib_frontend.c#L826">826</a>                 <a href="ident?i=fib_magic">fib_magic</a>(<a href="ident?i=RTM_NEWROUTE">RTM_NEWROUTE</a>,
<a name="L827" href="source/net/ipv4/fib_frontend.c#L827">827</a>                           <a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=IFF_LOOPBACK">IFF_LOOPBACK</a> ? RTN_LOCAL : RTN_UNICAST,
<a name="L828" href="source/net/ipv4/fib_frontend.c#L828">828</a>                           <a href="ident?i=prefix">prefix</a>, <a href="ident?i=ifa">ifa</a>-&gt;ifa_prefixlen, prim);
<a name="L829" href="source/net/ipv4/fib_frontend.c#L829">829</a> 
<a name="L830" href="source/net/ipv4/fib_frontend.c#L830">830</a>                 <b><i>/* Add network specific broadcasts, when it takes a sense */</i></b>
<a name="L831" href="source/net/ipv4/fib_frontend.c#L831">831</a>                 if (<a href="ident?i=ifa">ifa</a>-&gt;ifa_prefixlen &lt; 31) {
<a name="L832" href="source/net/ipv4/fib_frontend.c#L832">832</a>                         <a href="ident?i=fib_magic">fib_magic</a>(<a href="ident?i=RTM_NEWROUTE">RTM_NEWROUTE</a>, RTN_BROADCAST, <a href="ident?i=prefix">prefix</a>, 32, prim);
<a name="L833" href="source/net/ipv4/fib_frontend.c#L833">833</a>                         <a href="ident?i=fib_magic">fib_magic</a>(<a href="ident?i=RTM_NEWROUTE">RTM_NEWROUTE</a>, RTN_BROADCAST, <a href="ident?i=prefix">prefix</a> | ~mask,
<a name="L834" href="source/net/ipv4/fib_frontend.c#L834">834</a>                                   32, prim);
<a name="L835" href="source/net/ipv4/fib_frontend.c#L835">835</a>                 }
<a name="L836" href="source/net/ipv4/fib_frontend.c#L836">836</a>         }
<a name="L837" href="source/net/ipv4/fib_frontend.c#L837">837</a> }
<a name="L838" href="source/net/ipv4/fib_frontend.c#L838">838</a> 
<a name="L839" href="source/net/ipv4/fib_frontend.c#L839">839</a> <b><i>/* Delete primary or secondary address.</i></b>
<a name="L840" href="source/net/ipv4/fib_frontend.c#L840">840</a> <b><i> * Optionally, on secondary address promotion consider the addresses</i></b>
<a name="L841" href="source/net/ipv4/fib_frontend.c#L841">841</a> <b><i> * from subnet iprim as deleted, even if they are in device list.</i></b>
<a name="L842" href="source/net/ipv4/fib_frontend.c#L842">842</a> <b><i> * In this case the secondary ifa can be in device list.</i></b>
<a name="L843" href="source/net/ipv4/fib_frontend.c#L843">843</a> <b><i> */</i></b>
<a name="L844" href="source/net/ipv4/fib_frontend.c#L844">844</a> void <a href="ident?i=fib_del_ifaddr">fib_del_ifaddr</a>(struct <a href="ident?i=in_ifaddr">in_ifaddr</a> *<a href="ident?i=ifa">ifa</a>, struct <a href="ident?i=in_ifaddr">in_ifaddr</a> *iprim)
<a name="L845" href="source/net/ipv4/fib_frontend.c#L845">845</a> {
<a name="L846" href="source/net/ipv4/fib_frontend.c#L846">846</a>         struct <a href="ident?i=in_device">in_device</a> *in_dev = <a href="ident?i=ifa">ifa</a>-&gt;ifa_dev;
<a name="L847" href="source/net/ipv4/fib_frontend.c#L847">847</a>         struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a> = in_dev-&gt;<a href="ident?i=dev">dev</a>;
<a name="L848" href="source/net/ipv4/fib_frontend.c#L848">848</a>         struct <a href="ident?i=in_ifaddr">in_ifaddr</a> *ifa1;
<a name="L849" href="source/net/ipv4/fib_frontend.c#L849">849</a>         struct <a href="ident?i=in_ifaddr">in_ifaddr</a> *prim = <a href="ident?i=ifa">ifa</a>, *prim1 = <a href="ident?i=NULL">NULL</a>;
<a name="L850" href="source/net/ipv4/fib_frontend.c#L850">850</a>         <a href="ident?i=__be32">__be32</a> <a href="ident?i=brd">brd</a> = <a href="ident?i=ifa">ifa</a>-&gt;ifa_address | ~ifa-&gt;ifa_mask;
<a name="L851" href="source/net/ipv4/fib_frontend.c#L851">851</a>         <a href="ident?i=__be32">__be32</a> any = <a href="ident?i=ifa">ifa</a>-&gt;ifa_address &amp; <a href="ident?i=ifa">ifa</a>-&gt;ifa_mask;
<a name="L852" href="source/net/ipv4/fib_frontend.c#L852">852</a> #define <a href="ident?i=LOCAL_OK">LOCAL_OK</a>        1
<a name="L853" href="source/net/ipv4/fib_frontend.c#L853">853</a> #define <a href="ident?i=BRD_OK">BRD_OK</a>          2
<a name="L854" href="source/net/ipv4/fib_frontend.c#L854">854</a> #define <a href="ident?i=BRD0_OK">BRD0_OK</a>         4
<a name="L855" href="source/net/ipv4/fib_frontend.c#L855">855</a> #define <a href="ident?i=BRD1_OK">BRD1_OK</a>         8
<a name="L856" href="source/net/ipv4/fib_frontend.c#L856">856</a>         unsigned int <a href="ident?i=ok">ok</a> = 0;
<a name="L857" href="source/net/ipv4/fib_frontend.c#L857">857</a>         int subnet = 0;         <b><i>/* Primary network */</i></b>
<a name="L858" href="source/net/ipv4/fib_frontend.c#L858">858</a>         int gone = 1;           <b><i>/* Address is missing */</i></b>
<a name="L859" href="source/net/ipv4/fib_frontend.c#L859">859</a>         int same_prefsrc = 0;   <b><i>/* Another primary with same IP */</i></b>
<a name="L860" href="source/net/ipv4/fib_frontend.c#L860">860</a> 
<a name="L861" href="source/net/ipv4/fib_frontend.c#L861">861</a>         if (<a href="ident?i=ifa">ifa</a>-&gt;ifa_flags &amp; <a href="ident?i=IFA_F_SECONDARY">IFA_F_SECONDARY</a>) {
<a name="L862" href="source/net/ipv4/fib_frontend.c#L862">862</a>                 prim = <a href="ident?i=inet_ifa_byprefix">inet_ifa_byprefix</a>(in_dev, any, <a href="ident?i=ifa">ifa</a>-&gt;ifa_mask);
<a name="L863" href="source/net/ipv4/fib_frontend.c#L863">863</a>                 if (!prim) {
<a name="L864" href="source/net/ipv4/fib_frontend.c#L864">864</a>                         <a href="ident?i=pr_warn">pr_warn</a>(<i>"%s: bug: prim == NULL\n"</i>, <a href="ident?i=__func__">__func__</a>);
<a name="L865" href="source/net/ipv4/fib_frontend.c#L865">865</a>                         return;
<a name="L866" href="source/net/ipv4/fib_frontend.c#L866">866</a>                 }
<a name="L867" href="source/net/ipv4/fib_frontend.c#L867">867</a>                 if (iprim &amp;&amp; iprim != prim) {
<a name="L868" href="source/net/ipv4/fib_frontend.c#L868">868</a>                         <a href="ident?i=pr_warn">pr_warn</a>(<i>"%s: bug: iprim != prim\n"</i>, <a href="ident?i=__func__">__func__</a>);
<a name="L869" href="source/net/ipv4/fib_frontend.c#L869">869</a>                         return;
<a name="L870" href="source/net/ipv4/fib_frontend.c#L870">870</a>                 }
<a name="L871" href="source/net/ipv4/fib_frontend.c#L871">871</a>         } else if (!<a href="ident?i=ipv4_is_zeronet">ipv4_is_zeronet</a>(any) &amp;&amp;
<a name="L872" href="source/net/ipv4/fib_frontend.c#L872">872</a>                    (any != <a href="ident?i=ifa">ifa</a>-&gt;ifa_local || <a href="ident?i=ifa">ifa</a>-&gt;ifa_prefixlen &lt; 32)) {
<a name="L873" href="source/net/ipv4/fib_frontend.c#L873">873</a>                 <a href="ident?i=fib_magic">fib_magic</a>(<a href="ident?i=RTM_DELROUTE">RTM_DELROUTE</a>,
<a name="L874" href="source/net/ipv4/fib_frontend.c#L874">874</a>                           <a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=IFF_LOOPBACK">IFF_LOOPBACK</a> ? RTN_LOCAL : RTN_UNICAST,
<a name="L875" href="source/net/ipv4/fib_frontend.c#L875">875</a>                           any, <a href="ident?i=ifa">ifa</a>-&gt;ifa_prefixlen, prim);
<a name="L876" href="source/net/ipv4/fib_frontend.c#L876">876</a>                 subnet = 1;
<a name="L877" href="source/net/ipv4/fib_frontend.c#L877">877</a>         }
<a name="L878" href="source/net/ipv4/fib_frontend.c#L878">878</a> 
<a name="L879" href="source/net/ipv4/fib_frontend.c#L879">879</a>         <b><i>/* Deletion is more complicated than add.</i></b>
<a name="L880" href="source/net/ipv4/fib_frontend.c#L880">880</a> <b><i>         * We should take care of not to delete too much :-)</i></b>
<a name="L881" href="source/net/ipv4/fib_frontend.c#L881">881</a> <b><i>         *</i></b>
<a name="L882" href="source/net/ipv4/fib_frontend.c#L882">882</a> <b><i>         * Scan address list to be sure that addresses are really gone.</i></b>
<a name="L883" href="source/net/ipv4/fib_frontend.c#L883">883</a> <b><i>         */</i></b>
<a name="L884" href="source/net/ipv4/fib_frontend.c#L884">884</a> 
<a name="L885" href="source/net/ipv4/fib_frontend.c#L885">885</a>         for (ifa1 = in_dev-&gt;ifa_list; ifa1; ifa1 = ifa1-&gt;ifa_next) {
<a name="L886" href="source/net/ipv4/fib_frontend.c#L886">886</a>                 if (ifa1 == <a href="ident?i=ifa">ifa</a>) {
<a name="L887" href="source/net/ipv4/fib_frontend.c#L887">887</a>                         <b><i>/* promotion, keep the IP */</i></b>
<a name="L888" href="source/net/ipv4/fib_frontend.c#L888">888</a>                         gone = 0;
<a name="L889" href="source/net/ipv4/fib_frontend.c#L889">889</a>                         continue;
<a name="L890" href="source/net/ipv4/fib_frontend.c#L890">890</a>                 }
<a name="L891" href="source/net/ipv4/fib_frontend.c#L891">891</a>                 <b><i>/* Ignore IFAs from our subnet */</i></b>
<a name="L892" href="source/net/ipv4/fib_frontend.c#L892">892</a>                 if (iprim &amp;&amp; ifa1-&gt;ifa_mask == iprim-&gt;ifa_mask &amp;&amp;
<a name="L893" href="source/net/ipv4/fib_frontend.c#L893">893</a>                     <a href="ident?i=inet_ifa_match">inet_ifa_match</a>(ifa1-&gt;ifa_address, iprim))
<a name="L894" href="source/net/ipv4/fib_frontend.c#L894">894</a>                         continue;
<a name="L895" href="source/net/ipv4/fib_frontend.c#L895">895</a> 
<a name="L896" href="source/net/ipv4/fib_frontend.c#L896">896</a>                 <b><i>/* Ignore ifa1 if it uses different primary IP (prefsrc) */</i></b>
<a name="L897" href="source/net/ipv4/fib_frontend.c#L897">897</a>                 if (ifa1-&gt;ifa_flags &amp; <a href="ident?i=IFA_F_SECONDARY">IFA_F_SECONDARY</a>) {
<a name="L898" href="source/net/ipv4/fib_frontend.c#L898">898</a>                         <b><i>/* Another address from our subnet? */</i></b>
<a name="L899" href="source/net/ipv4/fib_frontend.c#L899">899</a>                         if (ifa1-&gt;ifa_mask == prim-&gt;ifa_mask &amp;&amp;
<a name="L900" href="source/net/ipv4/fib_frontend.c#L900">900</a>                             <a href="ident?i=inet_ifa_match">inet_ifa_match</a>(ifa1-&gt;ifa_address, prim))
<a name="L901" href="source/net/ipv4/fib_frontend.c#L901">901</a>                                 prim1 = prim;
<a name="L902" href="source/net/ipv4/fib_frontend.c#L902">902</a>                         else {
<a name="L903" href="source/net/ipv4/fib_frontend.c#L903">903</a>                                 <b><i>/* We reached the secondaries, so</i></b>
<a name="L904" href="source/net/ipv4/fib_frontend.c#L904">904</a> <b><i>                                 * same_prefsrc should be determined.</i></b>
<a name="L905" href="source/net/ipv4/fib_frontend.c#L905">905</a> <b><i>                                 */</i></b>
<a name="L906" href="source/net/ipv4/fib_frontend.c#L906">906</a>                                 if (!same_prefsrc)
<a name="L907" href="source/net/ipv4/fib_frontend.c#L907">907</a>                                         continue;
<a name="L908" href="source/net/ipv4/fib_frontend.c#L908">908</a>                                 <b><i>/* Search new prim1 if ifa1 is not</i></b>
<a name="L909" href="source/net/ipv4/fib_frontend.c#L909">909</a> <b><i>                                 * using the current prim1</i></b>
<a name="L910" href="source/net/ipv4/fib_frontend.c#L910">910</a> <b><i>                                 */</i></b>
<a name="L911" href="source/net/ipv4/fib_frontend.c#L911">911</a>                                 if (!prim1 ||
<a name="L912" href="source/net/ipv4/fib_frontend.c#L912">912</a>                                     ifa1-&gt;ifa_mask != prim1-&gt;ifa_mask ||
<a name="L913" href="source/net/ipv4/fib_frontend.c#L913">913</a>                                     !<a href="ident?i=inet_ifa_match">inet_ifa_match</a>(ifa1-&gt;ifa_address, prim1))
<a name="L914" href="source/net/ipv4/fib_frontend.c#L914">914</a>                                         prim1 = <a href="ident?i=inet_ifa_byprefix">inet_ifa_byprefix</a>(in_dev,
<a name="L915" href="source/net/ipv4/fib_frontend.c#L915">915</a>                                                         ifa1-&gt;ifa_address,
<a name="L916" href="source/net/ipv4/fib_frontend.c#L916">916</a>                                                         ifa1-&gt;ifa_mask);
<a name="L917" href="source/net/ipv4/fib_frontend.c#L917">917</a>                                 if (!prim1)
<a name="L918" href="source/net/ipv4/fib_frontend.c#L918">918</a>                                         continue;
<a name="L919" href="source/net/ipv4/fib_frontend.c#L919">919</a>                                 if (prim1-&gt;ifa_local != prim-&gt;ifa_local)
<a name="L920" href="source/net/ipv4/fib_frontend.c#L920">920</a>                                         continue;
<a name="L921" href="source/net/ipv4/fib_frontend.c#L921">921</a>                         }
<a name="L922" href="source/net/ipv4/fib_frontend.c#L922">922</a>                 } else {
<a name="L923" href="source/net/ipv4/fib_frontend.c#L923">923</a>                         if (prim-&gt;ifa_local != ifa1-&gt;ifa_local)
<a name="L924" href="source/net/ipv4/fib_frontend.c#L924">924</a>                                 continue;
<a name="L925" href="source/net/ipv4/fib_frontend.c#L925">925</a>                         prim1 = ifa1;
<a name="L926" href="source/net/ipv4/fib_frontend.c#L926">926</a>                         if (prim != prim1)
<a name="L927" href="source/net/ipv4/fib_frontend.c#L927">927</a>                                 same_prefsrc = 1;
<a name="L928" href="source/net/ipv4/fib_frontend.c#L928">928</a>                 }
<a name="L929" href="source/net/ipv4/fib_frontend.c#L929">929</a>                 if (<a href="ident?i=ifa">ifa</a>-&gt;ifa_local == ifa1-&gt;ifa_local)
<a name="L930" href="source/net/ipv4/fib_frontend.c#L930">930</a>                         <a href="ident?i=ok">ok</a> |= <a href="ident?i=LOCAL_OK">LOCAL_OK</a>;
<a name="L931" href="source/net/ipv4/fib_frontend.c#L931">931</a>                 if (<a href="ident?i=ifa">ifa</a>-&gt;ifa_broadcast == ifa1-&gt;ifa_broadcast)
<a name="L932" href="source/net/ipv4/fib_frontend.c#L932">932</a>                         <a href="ident?i=ok">ok</a> |= <a href="ident?i=BRD_OK">BRD_OK</a>;
<a name="L933" href="source/net/ipv4/fib_frontend.c#L933">933</a>                 if (<a href="ident?i=brd">brd</a> == ifa1-&gt;ifa_broadcast)
<a name="L934" href="source/net/ipv4/fib_frontend.c#L934">934</a>                         <a href="ident?i=ok">ok</a> |= <a href="ident?i=BRD1_OK">BRD1_OK</a>;
<a name="L935" href="source/net/ipv4/fib_frontend.c#L935">935</a>                 if (any == ifa1-&gt;ifa_broadcast)
<a name="L936" href="source/net/ipv4/fib_frontend.c#L936">936</a>                         <a href="ident?i=ok">ok</a> |= <a href="ident?i=BRD0_OK">BRD0_OK</a>;
<a name="L937" href="source/net/ipv4/fib_frontend.c#L937">937</a>                 <b><i>/* primary has network specific broadcasts */</i></b>
<a name="L938" href="source/net/ipv4/fib_frontend.c#L938">938</a>                 if (prim1 == ifa1 &amp;&amp; ifa1-&gt;ifa_prefixlen &lt; 31) {
<a name="L939" href="source/net/ipv4/fib_frontend.c#L939">939</a>                         <a href="ident?i=__be32">__be32</a> brd1 = ifa1-&gt;ifa_address | ~ifa1-&gt;ifa_mask;
<a name="L940" href="source/net/ipv4/fib_frontend.c#L940">940</a>                         <a href="ident?i=__be32">__be32</a> any1 = ifa1-&gt;ifa_address &amp; ifa1-&gt;ifa_mask;
<a name="L941" href="source/net/ipv4/fib_frontend.c#L941">941</a> 
<a name="L942" href="source/net/ipv4/fib_frontend.c#L942">942</a>                         if (!<a href="ident?i=ipv4_is_zeronet">ipv4_is_zeronet</a>(any1)) {
<a name="L943" href="source/net/ipv4/fib_frontend.c#L943">943</a>                                 if (<a href="ident?i=ifa">ifa</a>-&gt;ifa_broadcast == brd1 ||
<a name="L944" href="source/net/ipv4/fib_frontend.c#L944">944</a>                                     <a href="ident?i=ifa">ifa</a>-&gt;ifa_broadcast == any1)
<a name="L945" href="source/net/ipv4/fib_frontend.c#L945">945</a>                                         <a href="ident?i=ok">ok</a> |= <a href="ident?i=BRD_OK">BRD_OK</a>;
<a name="L946" href="source/net/ipv4/fib_frontend.c#L946">946</a>                                 if (<a href="ident?i=brd">brd</a> == brd1 || <a href="ident?i=brd">brd</a> == any1)
<a name="L947" href="source/net/ipv4/fib_frontend.c#L947">947</a>                                         <a href="ident?i=ok">ok</a> |= <a href="ident?i=BRD1_OK">BRD1_OK</a>;
<a name="L948" href="source/net/ipv4/fib_frontend.c#L948">948</a>                                 if (any == brd1 || any == any1)
<a name="L949" href="source/net/ipv4/fib_frontend.c#L949">949</a>                                         <a href="ident?i=ok">ok</a> |= <a href="ident?i=BRD0_OK">BRD0_OK</a>;
<a name="L950" href="source/net/ipv4/fib_frontend.c#L950">950</a>                         }
<a name="L951" href="source/net/ipv4/fib_frontend.c#L951">951</a>                 }
<a name="L952" href="source/net/ipv4/fib_frontend.c#L952">952</a>         }
<a name="L953" href="source/net/ipv4/fib_frontend.c#L953">953</a> 
<a name="L954" href="source/net/ipv4/fib_frontend.c#L954">954</a>         if (!(<a href="ident?i=ok">ok</a> &amp; <a href="ident?i=BRD_OK">BRD_OK</a>))
<a name="L955" href="source/net/ipv4/fib_frontend.c#L955">955</a>                 <a href="ident?i=fib_magic">fib_magic</a>(<a href="ident?i=RTM_DELROUTE">RTM_DELROUTE</a>, RTN_BROADCAST, <a href="ident?i=ifa">ifa</a>-&gt;ifa_broadcast, 32, prim);
<a name="L956" href="source/net/ipv4/fib_frontend.c#L956">956</a>         if (subnet &amp;&amp; <a href="ident?i=ifa">ifa</a>-&gt;ifa_prefixlen &lt; 31) {
<a name="L957" href="source/net/ipv4/fib_frontend.c#L957">957</a>                 if (!(<a href="ident?i=ok">ok</a> &amp; <a href="ident?i=BRD1_OK">BRD1_OK</a>))
<a name="L958" href="source/net/ipv4/fib_frontend.c#L958">958</a>                         <a href="ident?i=fib_magic">fib_magic</a>(<a href="ident?i=RTM_DELROUTE">RTM_DELROUTE</a>, RTN_BROADCAST, <a href="ident?i=brd">brd</a>, 32, prim);
<a name="L959" href="source/net/ipv4/fib_frontend.c#L959">959</a>                 if (!(<a href="ident?i=ok">ok</a> &amp; <a href="ident?i=BRD0_OK">BRD0_OK</a>))
<a name="L960" href="source/net/ipv4/fib_frontend.c#L960">960</a>                         <a href="ident?i=fib_magic">fib_magic</a>(<a href="ident?i=RTM_DELROUTE">RTM_DELROUTE</a>, RTN_BROADCAST, any, 32, prim);
<a name="L961" href="source/net/ipv4/fib_frontend.c#L961">961</a>         }
<a name="L962" href="source/net/ipv4/fib_frontend.c#L962">962</a>         if (!(<a href="ident?i=ok">ok</a> &amp; <a href="ident?i=LOCAL_OK">LOCAL_OK</a>)) {
<a name="L963" href="source/net/ipv4/fib_frontend.c#L963">963</a>                 <a href="ident?i=fib_magic">fib_magic</a>(<a href="ident?i=RTM_DELROUTE">RTM_DELROUTE</a>, RTN_LOCAL, <a href="ident?i=ifa">ifa</a>-&gt;ifa_local, 32, prim);
<a name="L964" href="source/net/ipv4/fib_frontend.c#L964">964</a> 
<a name="L965" href="source/net/ipv4/fib_frontend.c#L965">965</a>                 <b><i>/* Check, that this local address finally disappeared. */</i></b>
<a name="L966" href="source/net/ipv4/fib_frontend.c#L966">966</a>                 if (gone &amp;&amp;
<a name="L967" href="source/net/ipv4/fib_frontend.c#L967">967</a>                     <a href="ident?i=inet_addr_type">inet_addr_type</a>(<a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=dev">dev</a>), <a href="ident?i=ifa">ifa</a>-&gt;ifa_local) != RTN_LOCAL) {
<a name="L968" href="source/net/ipv4/fib_frontend.c#L968">968</a>                         <b><i>/* And the last, but not the least thing.</i></b>
<a name="L969" href="source/net/ipv4/fib_frontend.c#L969">969</a> <b><i>                         * We must flush stray FIB entries.</i></b>
<a name="L970" href="source/net/ipv4/fib_frontend.c#L970">970</a> <b><i>                         *</i></b>
<a name="L971" href="source/net/ipv4/fib_frontend.c#L971">971</a> <b><i>                         * First of all, we scan fib_info list searching</i></b>
<a name="L972" href="source/net/ipv4/fib_frontend.c#L972">972</a> <b><i>                         * for stray nexthop entries, then ignite fib_flush.</i></b>
<a name="L973" href="source/net/ipv4/fib_frontend.c#L973">973</a> <b><i>                         */</i></b>
<a name="L974" href="source/net/ipv4/fib_frontend.c#L974">974</a>                         if (<a href="ident?i=fib_sync_down_addr">fib_sync_down_addr</a>(<a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=dev">dev</a>), <a href="ident?i=ifa">ifa</a>-&gt;ifa_local))
<a name="L975" href="source/net/ipv4/fib_frontend.c#L975">975</a>                                 <a href="ident?i=fib_flush">fib_flush</a>(<a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=dev">dev</a>));
<a name="L976" href="source/net/ipv4/fib_frontend.c#L976">976</a>                 }
<a name="L977" href="source/net/ipv4/fib_frontend.c#L977">977</a>         }
<a name="L978" href="source/net/ipv4/fib_frontend.c#L978">978</a> #undef <a href="ident?i=LOCAL_OK">LOCAL_OK</a>
<a name="L979" href="source/net/ipv4/fib_frontend.c#L979">979</a> #undef <a href="ident?i=BRD_OK">BRD_OK</a>
<a name="L980" href="source/net/ipv4/fib_frontend.c#L980">980</a> #undef <a href="ident?i=BRD0_OK">BRD0_OK</a>
<a name="L981" href="source/net/ipv4/fib_frontend.c#L981">981</a> #undef <a href="ident?i=BRD1_OK">BRD1_OK</a>
<a name="L982" href="source/net/ipv4/fib_frontend.c#L982">982</a> }
<a name="L983" href="source/net/ipv4/fib_frontend.c#L983">983</a> 
<a name="L984" href="source/net/ipv4/fib_frontend.c#L984">984</a> static void <a href="ident?i=nl_fib_lookup">nl_fib_lookup</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>, struct <a href="ident?i=fib_result_nl">fib_result_nl</a> *frn)
<a name="L985" href="source/net/ipv4/fib_frontend.c#L985">985</a> {
<a name="L986" href="source/net/ipv4/fib_frontend.c#L986">986</a> 
<a name="L987" href="source/net/ipv4/fib_frontend.c#L987">987</a>         struct <a href="ident?i=fib_result">fib_result</a>       <a href="ident?i=res">res</a>;
<a name="L988" href="source/net/ipv4/fib_frontend.c#L988">988</a>         struct <a href="ident?i=flowi4">flowi4</a>           fl4 = {
<a name="L989" href="source/net/ipv4/fib_frontend.c#L989">989</a>                 .<a href="ident?i=flowi4_mark">flowi4_mark</a> = frn-&gt;fl_mark,
<a name="L990" href="source/net/ipv4/fib_frontend.c#L990">990</a>                 .<a href="ident?i=daddr">daddr</a> = frn-&gt;fl_addr,
<a name="L991" href="source/net/ipv4/fib_frontend.c#L991">991</a>                 .<a href="ident?i=flowi4_tos">flowi4_tos</a> = frn-&gt;fl_tos,
<a name="L992" href="source/net/ipv4/fib_frontend.c#L992">992</a>                 .<a href="ident?i=flowi4_scope">flowi4_scope</a> = frn-&gt;fl_scope,
<a name="L993" href="source/net/ipv4/fib_frontend.c#L993">993</a>         };
<a name="L994" href="source/net/ipv4/fib_frontend.c#L994">994</a>         struct <a href="ident?i=fib_table">fib_table</a> *<a href="ident?i=tb">tb</a>;
<a name="L995" href="source/net/ipv4/fib_frontend.c#L995">995</a> 
<a name="L996" href="source/net/ipv4/fib_frontend.c#L996">996</a>         <a href="ident?i=rcu_read_lock">rcu_read_lock</a>();
<a name="L997" href="source/net/ipv4/fib_frontend.c#L997">997</a> 
<a name="L998" href="source/net/ipv4/fib_frontend.c#L998">998</a>         <a href="ident?i=tb">tb</a> = <a href="ident?i=fib_get_table">fib_get_table</a>(<a href="ident?i=net">net</a>, frn-&gt;tb_id_in);
<a name="L999" href="source/net/ipv4/fib_frontend.c#L999">999</a> 
<a name="L1000" href="source/net/ipv4/fib_frontend.c#L1000">1000</a>         frn-&gt;<a href="ident?i=err">err</a> = -<a href="ident?i=ENOENT">ENOENT</a>;
<a name="L1001" href="source/net/ipv4/fib_frontend.c#L1001">1001</a>         if (<a href="ident?i=tb">tb</a>) {
<a name="L1002" href="source/net/ipv4/fib_frontend.c#L1002">1002</a>                 <a href="ident?i=local_bh_disable">local_bh_disable</a>();
<a name="L1003" href="source/net/ipv4/fib_frontend.c#L1003">1003</a> 
<a name="L1004" href="source/net/ipv4/fib_frontend.c#L1004">1004</a>                 frn-&gt;tb_id = <a href="ident?i=tb">tb</a>-&gt;tb_id;
<a name="L1005" href="source/net/ipv4/fib_frontend.c#L1005">1005</a>                 frn-&gt;<a href="ident?i=err">err</a> = <a href="ident?i=fib_table_lookup">fib_table_lookup</a>(<a href="ident?i=tb">tb</a>, &amp;fl4, &amp;<a href="ident?i=res">res</a>, <a href="ident?i=FIB_LOOKUP_NOREF">FIB_LOOKUP_NOREF</a>);
<a name="L1006" href="source/net/ipv4/fib_frontend.c#L1006">1006</a> 
<a name="L1007" href="source/net/ipv4/fib_frontend.c#L1007">1007</a>                 if (!frn-&gt;<a href="ident?i=err">err</a>) {
<a name="L1008" href="source/net/ipv4/fib_frontend.c#L1008">1008</a>                         frn-&gt;prefixlen = <a href="ident?i=res">res</a>.prefixlen;
<a name="L1009" href="source/net/ipv4/fib_frontend.c#L1009">1009</a>                         frn-&gt;nh_sel = <a href="ident?i=res">res</a>.nh_sel;
<a name="L1010" href="source/net/ipv4/fib_frontend.c#L1010">1010</a>                         frn-&gt;<a href="ident?i=type">type</a> = <a href="ident?i=res">res</a>.<a href="ident?i=type">type</a>;
<a name="L1011" href="source/net/ipv4/fib_frontend.c#L1011">1011</a>                         frn-&gt;<a href="ident?i=scope">scope</a> = <a href="ident?i=res">res</a>.<a href="ident?i=scope">scope</a>;
<a name="L1012" href="source/net/ipv4/fib_frontend.c#L1012">1012</a>                 }
<a name="L1013" href="source/net/ipv4/fib_frontend.c#L1013">1013</a>                 <a href="ident?i=local_bh_enable">local_bh_enable</a>();
<a name="L1014" href="source/net/ipv4/fib_frontend.c#L1014">1014</a>         }
<a name="L1015" href="source/net/ipv4/fib_frontend.c#L1015">1015</a> 
<a name="L1016" href="source/net/ipv4/fib_frontend.c#L1016">1016</a>         <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L1017" href="source/net/ipv4/fib_frontend.c#L1017">1017</a> }
<a name="L1018" href="source/net/ipv4/fib_frontend.c#L1018">1018</a> 
<a name="L1019" href="source/net/ipv4/fib_frontend.c#L1019">1019</a> static void <a href="ident?i=nl_fib_input">nl_fib_input</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L1020" href="source/net/ipv4/fib_frontend.c#L1020">1020</a> {
<a name="L1021" href="source/net/ipv4/fib_frontend.c#L1021">1021</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>;
<a name="L1022" href="source/net/ipv4/fib_frontend.c#L1022">1022</a>         struct <a href="ident?i=fib_result_nl">fib_result_nl</a> *frn;
<a name="L1023" href="source/net/ipv4/fib_frontend.c#L1023">1023</a>         struct <a href="ident?i=nlmsghdr">nlmsghdr</a> *nlh;
<a name="L1024" href="source/net/ipv4/fib_frontend.c#L1024">1024</a>         <a href="ident?i=u32">u32</a> portid;
<a name="L1025" href="source/net/ipv4/fib_frontend.c#L1025">1025</a> 
<a name="L1026" href="source/net/ipv4/fib_frontend.c#L1026">1026</a>         <a href="ident?i=net">net</a> = <a href="ident?i=sock_net">sock_net</a>(<a href="ident?i=skb">skb</a>-&gt;sk);
<a name="L1027" href="source/net/ipv4/fib_frontend.c#L1027">1027</a>         nlh = <a href="ident?i=nlmsg_hdr">nlmsg_hdr</a>(<a href="ident?i=skb">skb</a>);
<a name="L1028" href="source/net/ipv4/fib_frontend.c#L1028">1028</a>         if (<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a> &lt; <a href="ident?i=NLMSG_HDRLEN">NLMSG_HDRLEN</a> || <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a> &lt; nlh-&gt;<a href="ident?i=nlmsg_len">nlmsg_len</a> ||
<a name="L1029" href="source/net/ipv4/fib_frontend.c#L1029">1029</a>             <a href="ident?i=nlmsg_len">nlmsg_len</a>(nlh) &lt; sizeof(*frn))
<a name="L1030" href="source/net/ipv4/fib_frontend.c#L1030">1030</a>                 return;
<a name="L1031" href="source/net/ipv4/fib_frontend.c#L1031">1031</a> 
<a name="L1032" href="source/net/ipv4/fib_frontend.c#L1032">1032</a>         <a href="ident?i=skb">skb</a> = <a href="ident?i=netlink_skb_clone">netlink_skb_clone</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=GFP_KERNEL">GFP_KERNEL</a>);
<a name="L1033" href="source/net/ipv4/fib_frontend.c#L1033">1033</a>         if (!<a href="ident?i=skb">skb</a>)
<a name="L1034" href="source/net/ipv4/fib_frontend.c#L1034">1034</a>                 return;
<a name="L1035" href="source/net/ipv4/fib_frontend.c#L1035">1035</a>         nlh = <a href="ident?i=nlmsg_hdr">nlmsg_hdr</a>(<a href="ident?i=skb">skb</a>);
<a name="L1036" href="source/net/ipv4/fib_frontend.c#L1036">1036</a> 
<a name="L1037" href="source/net/ipv4/fib_frontend.c#L1037">1037</a>         frn = (struct <a href="ident?i=fib_result_nl">fib_result_nl</a> *) <a href="ident?i=nlmsg_data">nlmsg_data</a>(nlh);
<a name="L1038" href="source/net/ipv4/fib_frontend.c#L1038">1038</a>         <a href="ident?i=nl_fib_lookup">nl_fib_lookup</a>(<a href="ident?i=net">net</a>, frn);
<a name="L1039" href="source/net/ipv4/fib_frontend.c#L1039">1039</a> 
<a name="L1040" href="source/net/ipv4/fib_frontend.c#L1040">1040</a>         portid = <a href="ident?i=NETLINK_CB">NETLINK_CB</a>(<a href="ident?i=skb">skb</a>).portid;      <b><i>/* netlink portid */</i></b>
<a name="L1041" href="source/net/ipv4/fib_frontend.c#L1041">1041</a>         <a href="ident?i=NETLINK_CB">NETLINK_CB</a>(<a href="ident?i=skb">skb</a>).portid = 0;        <b><i>/* from kernel */</i></b>
<a name="L1042" href="source/net/ipv4/fib_frontend.c#L1042">1042</a>         <a href="ident?i=NETLINK_CB">NETLINK_CB</a>(<a href="ident?i=skb">skb</a>).dst_group = 0;  <b><i>/* unicast */</i></b>
<a name="L1043" href="source/net/ipv4/fib_frontend.c#L1043">1043</a>         <a href="ident?i=netlink_unicast">netlink_unicast</a>(<a href="ident?i=net">net</a>-&gt;ipv4.fibnl, <a href="ident?i=skb">skb</a>, portid, <a href="ident?i=MSG_DONTWAIT">MSG_DONTWAIT</a>);
<a name="L1044" href="source/net/ipv4/fib_frontend.c#L1044">1044</a> }
<a name="L1045" href="source/net/ipv4/fib_frontend.c#L1045">1045</a> 
<a name="L1046" href="source/net/ipv4/fib_frontend.c#L1046">1046</a> static int <a href="ident?i=__net_init">__net_init</a> <a href="ident?i=nl_fib_lookup_init">nl_fib_lookup_init</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>)
<a name="L1047" href="source/net/ipv4/fib_frontend.c#L1047">1047</a> {
<a name="L1048" href="source/net/ipv4/fib_frontend.c#L1048">1048</a>         struct <a href="ident?i=sock">sock</a> *sk;
<a name="L1049" href="source/net/ipv4/fib_frontend.c#L1049">1049</a>         struct <a href="ident?i=netlink_kernel_cfg">netlink_kernel_cfg</a> <a href="ident?i=cfg">cfg</a> = {
<a name="L1050" href="source/net/ipv4/fib_frontend.c#L1050">1050</a>                 .<a href="ident?i=input">input</a>  = <a href="ident?i=nl_fib_input">nl_fib_input</a>,
<a name="L1051" href="source/net/ipv4/fib_frontend.c#L1051">1051</a>         };
<a name="L1052" href="source/net/ipv4/fib_frontend.c#L1052">1052</a> 
<a name="L1053" href="source/net/ipv4/fib_frontend.c#L1053">1053</a>         sk = <a href="ident?i=netlink_kernel_create">netlink_kernel_create</a>(<a href="ident?i=net">net</a>, <a href="ident?i=NETLINK_FIB_LOOKUP">NETLINK_FIB_LOOKUP</a>, &amp;<a href="ident?i=cfg">cfg</a>);
<a name="L1054" href="source/net/ipv4/fib_frontend.c#L1054">1054</a>         if (!sk)
<a name="L1055" href="source/net/ipv4/fib_frontend.c#L1055">1055</a>                 return -<a href="ident?i=EAFNOSUPPORT">EAFNOSUPPORT</a>;
<a name="L1056" href="source/net/ipv4/fib_frontend.c#L1056">1056</a>         <a href="ident?i=net">net</a>-&gt;ipv4.fibnl = sk;
<a name="L1057" href="source/net/ipv4/fib_frontend.c#L1057">1057</a>         return 0;
<a name="L1058" href="source/net/ipv4/fib_frontend.c#L1058">1058</a> }
<a name="L1059" href="source/net/ipv4/fib_frontend.c#L1059">1059</a> 
<a name="L1060" href="source/net/ipv4/fib_frontend.c#L1060">1060</a> static void <a href="ident?i=nl_fib_lookup_exit">nl_fib_lookup_exit</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>)
<a name="L1061" href="source/net/ipv4/fib_frontend.c#L1061">1061</a> {
<a name="L1062" href="source/net/ipv4/fib_frontend.c#L1062">1062</a>         <a href="ident?i=netlink_kernel_release">netlink_kernel_release</a>(<a href="ident?i=net">net</a>-&gt;ipv4.fibnl);
<a name="L1063" href="source/net/ipv4/fib_frontend.c#L1063">1063</a>         <a href="ident?i=net">net</a>-&gt;ipv4.fibnl = <a href="ident?i=NULL">NULL</a>;
<a name="L1064" href="source/net/ipv4/fib_frontend.c#L1064">1064</a> }
<a name="L1065" href="source/net/ipv4/fib_frontend.c#L1065">1065</a> 
<a name="L1066" href="source/net/ipv4/fib_frontend.c#L1066">1066</a> static void <a href="ident?i=fib_disable_ip">fib_disable_ip</a>(struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a>, int <a href="ident?i=force">force</a>)
<a name="L1067" href="source/net/ipv4/fib_frontend.c#L1067">1067</a> {
<a name="L1068" href="source/net/ipv4/fib_frontend.c#L1068">1068</a>         if (<a href="ident?i=fib_sync_down_dev">fib_sync_down_dev</a>(<a href="ident?i=dev">dev</a>, <a href="ident?i=force">force</a>))
<a name="L1069" href="source/net/ipv4/fib_frontend.c#L1069">1069</a>                 <a href="ident?i=fib_flush">fib_flush</a>(<a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=dev">dev</a>));
<a name="L1070" href="source/net/ipv4/fib_frontend.c#L1070">1070</a>         <a href="ident?i=rt_cache_flush">rt_cache_flush</a>(<a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=dev">dev</a>));
<a name="L1071" href="source/net/ipv4/fib_frontend.c#L1071">1071</a>         <a href="ident?i=arp_ifdown">arp_ifdown</a>(<a href="ident?i=dev">dev</a>);
<a name="L1072" href="source/net/ipv4/fib_frontend.c#L1072">1072</a> }
<a name="L1073" href="source/net/ipv4/fib_frontend.c#L1073">1073</a> 
<a name="L1074" href="source/net/ipv4/fib_frontend.c#L1074">1074</a> static int <a href="ident?i=fib_inetaddr_event">fib_inetaddr_event</a>(struct <a href="ident?i=notifier_block">notifier_block</a> *<a href="ident?i=this">this</a>, unsigned long <a href="ident?i=event">event</a>, void *<a href="ident?i=ptr">ptr</a>)
<a name="L1075" href="source/net/ipv4/fib_frontend.c#L1075">1075</a> {
<a name="L1076" href="source/net/ipv4/fib_frontend.c#L1076">1076</a>         struct <a href="ident?i=in_ifaddr">in_ifaddr</a> *<a href="ident?i=ifa">ifa</a> = (struct <a href="ident?i=in_ifaddr">in_ifaddr</a> *)<a href="ident?i=ptr">ptr</a>;
<a name="L1077" href="source/net/ipv4/fib_frontend.c#L1077">1077</a>         struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a> = <a href="ident?i=ifa">ifa</a>-&gt;ifa_dev-&gt;<a href="ident?i=dev">dev</a>;
<a name="L1078" href="source/net/ipv4/fib_frontend.c#L1078">1078</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=dev">dev</a>);
<a name="L1079" href="source/net/ipv4/fib_frontend.c#L1079">1079</a> 
<a name="L1080" href="source/net/ipv4/fib_frontend.c#L1080">1080</a>         switch (<a href="ident?i=event">event</a>) {
<a name="L1081" href="source/net/ipv4/fib_frontend.c#L1081">1081</a>         case <a href="ident?i=NETDEV_UP">NETDEV_UP</a>:
<a name="L1082" href="source/net/ipv4/fib_frontend.c#L1082">1082</a>                 <a href="ident?i=fib_add_ifaddr">fib_add_ifaddr</a>(<a href="ident?i=ifa">ifa</a>);
<a name="L1083" href="source/net/ipv4/fib_frontend.c#L1083">1083</a> #ifdef CONFIG_IP_ROUTE_MULTIPATH
<a name="L1084" href="source/net/ipv4/fib_frontend.c#L1084">1084</a>                 <a href="ident?i=fib_sync_up">fib_sync_up</a>(<a href="ident?i=dev">dev</a>);
<a name="L1085" href="source/net/ipv4/fib_frontend.c#L1085">1085</a> #endif
<a name="L1086" href="source/net/ipv4/fib_frontend.c#L1086">1086</a>                 <a href="ident?i=atomic_inc">atomic_inc</a>(&amp;<a href="ident?i=net">net</a>-&gt;ipv4.dev_addr_genid);
<a name="L1087" href="source/net/ipv4/fib_frontend.c#L1087">1087</a>                 <a href="ident?i=rt_cache_flush">rt_cache_flush</a>(<a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=dev">dev</a>));
<a name="L1088" href="source/net/ipv4/fib_frontend.c#L1088">1088</a>                 break;
<a name="L1089" href="source/net/ipv4/fib_frontend.c#L1089">1089</a>         case <a href="ident?i=NETDEV_DOWN">NETDEV_DOWN</a>:
<a name="L1090" href="source/net/ipv4/fib_frontend.c#L1090">1090</a>                 <a href="ident?i=fib_del_ifaddr">fib_del_ifaddr</a>(<a href="ident?i=ifa">ifa</a>, <a href="ident?i=NULL">NULL</a>);
<a name="L1091" href="source/net/ipv4/fib_frontend.c#L1091">1091</a>                 <a href="ident?i=atomic_inc">atomic_inc</a>(&amp;<a href="ident?i=net">net</a>-&gt;ipv4.dev_addr_genid);
<a name="L1092" href="source/net/ipv4/fib_frontend.c#L1092">1092</a>                 if (!<a href="ident?i=ifa">ifa</a>-&gt;ifa_dev-&gt;ifa_list) {
<a name="L1093" href="source/net/ipv4/fib_frontend.c#L1093">1093</a>                         <b><i>/* Last address was deleted from this interface.</i></b>
<a name="L1094" href="source/net/ipv4/fib_frontend.c#L1094">1094</a> <b><i>                         * Disable IP.</i></b>
<a name="L1095" href="source/net/ipv4/fib_frontend.c#L1095">1095</a> <b><i>                         */</i></b>
<a name="L1096" href="source/net/ipv4/fib_frontend.c#L1096">1096</a>                         <a href="ident?i=fib_disable_ip">fib_disable_ip</a>(<a href="ident?i=dev">dev</a>, 1);
<a name="L1097" href="source/net/ipv4/fib_frontend.c#L1097">1097</a>                 } else {
<a name="L1098" href="source/net/ipv4/fib_frontend.c#L1098">1098</a>                         <a href="ident?i=rt_cache_flush">rt_cache_flush</a>(<a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=dev">dev</a>));
<a name="L1099" href="source/net/ipv4/fib_frontend.c#L1099">1099</a>                 }
<a name="L1100" href="source/net/ipv4/fib_frontend.c#L1100">1100</a>                 break;
<a name="L1101" href="source/net/ipv4/fib_frontend.c#L1101">1101</a>         }
<a name="L1102" href="source/net/ipv4/fib_frontend.c#L1102">1102</a>         return <a href="ident?i=NOTIFY_DONE">NOTIFY_DONE</a>;
<a name="L1103" href="source/net/ipv4/fib_frontend.c#L1103">1103</a> }
<a name="L1104" href="source/net/ipv4/fib_frontend.c#L1104">1104</a> 
<a name="L1105" href="source/net/ipv4/fib_frontend.c#L1105">1105</a> static int <a href="ident?i=fib_netdev_event">fib_netdev_event</a>(struct <a href="ident?i=notifier_block">notifier_block</a> *<a href="ident?i=this">this</a>, unsigned long <a href="ident?i=event">event</a>, void *<a href="ident?i=ptr">ptr</a>)
<a name="L1106" href="source/net/ipv4/fib_frontend.c#L1106">1106</a> {
<a name="L1107" href="source/net/ipv4/fib_frontend.c#L1107">1107</a>         struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a> = <a href="ident?i=netdev_notifier_info_to_dev">netdev_notifier_info_to_dev</a>(<a href="ident?i=ptr">ptr</a>);
<a name="L1108" href="source/net/ipv4/fib_frontend.c#L1108">1108</a>         struct <a href="ident?i=in_device">in_device</a> *in_dev;
<a name="L1109" href="source/net/ipv4/fib_frontend.c#L1109">1109</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=dev">dev</a>);
<a name="L1110" href="source/net/ipv4/fib_frontend.c#L1110">1110</a> 
<a name="L1111" href="source/net/ipv4/fib_frontend.c#L1111">1111</a>         if (<a href="ident?i=event">event</a> == <a href="ident?i=NETDEV_UNREGISTER">NETDEV_UNREGISTER</a>) {
<a name="L1112" href="source/net/ipv4/fib_frontend.c#L1112">1112</a>                 <a href="ident?i=fib_disable_ip">fib_disable_ip</a>(<a href="ident?i=dev">dev</a>, 2);
<a name="L1113" href="source/net/ipv4/fib_frontend.c#L1113">1113</a>                 <a href="ident?i=rt_flush_dev">rt_flush_dev</a>(<a href="ident?i=dev">dev</a>);
<a name="L1114" href="source/net/ipv4/fib_frontend.c#L1114">1114</a>                 return <a href="ident?i=NOTIFY_DONE">NOTIFY_DONE</a>;
<a name="L1115" href="source/net/ipv4/fib_frontend.c#L1115">1115</a>         }
<a name="L1116" href="source/net/ipv4/fib_frontend.c#L1116">1116</a> 
<a name="L1117" href="source/net/ipv4/fib_frontend.c#L1117">1117</a>         in_dev = <a href="ident?i=__in_dev_get_rtnl">__in_dev_get_rtnl</a>(<a href="ident?i=dev">dev</a>);
<a name="L1118" href="source/net/ipv4/fib_frontend.c#L1118">1118</a>         if (!in_dev)
<a name="L1119" href="source/net/ipv4/fib_frontend.c#L1119">1119</a>                 return <a href="ident?i=NOTIFY_DONE">NOTIFY_DONE</a>;
<a name="L1120" href="source/net/ipv4/fib_frontend.c#L1120">1120</a> 
<a name="L1121" href="source/net/ipv4/fib_frontend.c#L1121">1121</a>         switch (<a href="ident?i=event">event</a>) {
<a name="L1122" href="source/net/ipv4/fib_frontend.c#L1122">1122</a>         case <a href="ident?i=NETDEV_UP">NETDEV_UP</a>:
<a name="L1123" href="source/net/ipv4/fib_frontend.c#L1123">1123</a>                 <a href="ident?i=for_ifa">for_ifa</a>(in_dev) {
<a name="L1124" href="source/net/ipv4/fib_frontend.c#L1124">1124</a>                         <a href="ident?i=fib_add_ifaddr">fib_add_ifaddr</a>(<a href="ident?i=ifa">ifa</a>);
<a name="L1125" href="source/net/ipv4/fib_frontend.c#L1125">1125</a>                 } <a href="ident?i=endfor_ifa">endfor_ifa</a>(in_dev);
<a name="L1126" href="source/net/ipv4/fib_frontend.c#L1126">1126</a> #ifdef CONFIG_IP_ROUTE_MULTIPATH
<a name="L1127" href="source/net/ipv4/fib_frontend.c#L1127">1127</a>                 <a href="ident?i=fib_sync_up">fib_sync_up</a>(<a href="ident?i=dev">dev</a>);
<a name="L1128" href="source/net/ipv4/fib_frontend.c#L1128">1128</a> #endif
<a name="L1129" href="source/net/ipv4/fib_frontend.c#L1129">1129</a>                 <a href="ident?i=atomic_inc">atomic_inc</a>(&amp;<a href="ident?i=net">net</a>-&gt;ipv4.dev_addr_genid);
<a name="L1130" href="source/net/ipv4/fib_frontend.c#L1130">1130</a>                 <a href="ident?i=rt_cache_flush">rt_cache_flush</a>(<a href="ident?i=net">net</a>);
<a name="L1131" href="source/net/ipv4/fib_frontend.c#L1131">1131</a>                 break;
<a name="L1132" href="source/net/ipv4/fib_frontend.c#L1132">1132</a>         case <a href="ident?i=NETDEV_DOWN">NETDEV_DOWN</a>:
<a name="L1133" href="source/net/ipv4/fib_frontend.c#L1133">1133</a>                 <a href="ident?i=fib_disable_ip">fib_disable_ip</a>(<a href="ident?i=dev">dev</a>, 0);
<a name="L1134" href="source/net/ipv4/fib_frontend.c#L1134">1134</a>                 break;
<a name="L1135" href="source/net/ipv4/fib_frontend.c#L1135">1135</a>         case <a href="ident?i=NETDEV_CHANGEMTU">NETDEV_CHANGEMTU</a>:
<a name="L1136" href="source/net/ipv4/fib_frontend.c#L1136">1136</a>         case <a href="ident?i=NETDEV_CHANGE">NETDEV_CHANGE</a>:
<a name="L1137" href="source/net/ipv4/fib_frontend.c#L1137">1137</a>                 <a href="ident?i=rt_cache_flush">rt_cache_flush</a>(<a href="ident?i=net">net</a>);
<a name="L1138" href="source/net/ipv4/fib_frontend.c#L1138">1138</a>                 break;
<a name="L1139" href="source/net/ipv4/fib_frontend.c#L1139">1139</a>         }
<a name="L1140" href="source/net/ipv4/fib_frontend.c#L1140">1140</a>         return <a href="ident?i=NOTIFY_DONE">NOTIFY_DONE</a>;
<a name="L1141" href="source/net/ipv4/fib_frontend.c#L1141">1141</a> }
<a name="L1142" href="source/net/ipv4/fib_frontend.c#L1142">1142</a> 
<a name="L1143" href="source/net/ipv4/fib_frontend.c#L1143">1143</a> static struct <a href="ident?i=notifier_block">notifier_block</a> <a href="ident?i=fib_inetaddr_notifier">fib_inetaddr_notifier</a> = {
<a name="L1144" href="source/net/ipv4/fib_frontend.c#L1144">1144</a>         .notifier_call = <a href="ident?i=fib_inetaddr_event">fib_inetaddr_event</a>,
<a name="L1145" href="source/net/ipv4/fib_frontend.c#L1145">1145</a> };
<a name="L1146" href="source/net/ipv4/fib_frontend.c#L1146">1146</a> 
<a name="L1147" href="source/net/ipv4/fib_frontend.c#L1147">1147</a> static struct <a href="ident?i=notifier_block">notifier_block</a> <a href="ident?i=fib_netdev_notifier">fib_netdev_notifier</a> = {
<a name="L1148" href="source/net/ipv4/fib_frontend.c#L1148">1148</a>         .notifier_call = <a href="ident?i=fib_netdev_event">fib_netdev_event</a>,
<a name="L1149" href="source/net/ipv4/fib_frontend.c#L1149">1149</a> };
<a name="L1150" href="source/net/ipv4/fib_frontend.c#L1150">1150</a> 
<a name="L1151" href="source/net/ipv4/fib_frontend.c#L1151">1151</a> static int <a href="ident?i=__net_init">__net_init</a> <a href="ident?i=ip_fib_net_init">ip_fib_net_init</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>)
<a name="L1152" href="source/net/ipv4/fib_frontend.c#L1152">1152</a> {
<a name="L1153" href="source/net/ipv4/fib_frontend.c#L1153">1153</a>         int <a href="ident?i=err">err</a>;
<a name="L1154" href="source/net/ipv4/fib_frontend.c#L1154">1154</a>         <a href="ident?i=size_t">size_t</a> <a href="ident?i=size">size</a> = sizeof(struct <a href="ident?i=hlist_head">hlist_head</a>) * <a href="ident?i=FIB_TABLE_HASHSZ">FIB_TABLE_HASHSZ</a>;
<a name="L1155" href="source/net/ipv4/fib_frontend.c#L1155">1155</a> 
<a name="L1156" href="source/net/ipv4/fib_frontend.c#L1156">1156</a>         <b><i>/* Avoid false sharing : Use at least a full cache line */</i></b>
<a name="L1157" href="source/net/ipv4/fib_frontend.c#L1157">1157</a>         <a href="ident?i=size">size</a> = <a href="ident?i=max_t">max_t</a>(<a href="ident?i=size_t">size_t</a>, <a href="ident?i=size">size</a>, <a href="ident?i=L1_CACHE_BYTES">L1_CACHE_BYTES</a>);
<a name="L1158" href="source/net/ipv4/fib_frontend.c#L1158">1158</a> 
<a name="L1159" href="source/net/ipv4/fib_frontend.c#L1159">1159</a>         <a href="ident?i=net">net</a>-&gt;ipv4.fib_table_hash = <a href="ident?i=kzalloc">kzalloc</a>(<a href="ident?i=size">size</a>, <a href="ident?i=GFP_KERNEL">GFP_KERNEL</a>);
<a name="L1160" href="source/net/ipv4/fib_frontend.c#L1160">1160</a>         if (!<a href="ident?i=net">net</a>-&gt;ipv4.fib_table_hash)
<a name="L1161" href="source/net/ipv4/fib_frontend.c#L1161">1161</a>                 return -<a href="ident?i=ENOMEM">ENOMEM</a>;
<a name="L1162" href="source/net/ipv4/fib_frontend.c#L1162">1162</a> 
<a name="L1163" href="source/net/ipv4/fib_frontend.c#L1163">1163</a>         <a href="ident?i=err">err</a> = <a href="ident?i=fib4_rules_init">fib4_rules_init</a>(<a href="ident?i=net">net</a>);
<a name="L1164" href="source/net/ipv4/fib_frontend.c#L1164">1164</a>         if (<a href="ident?i=err">err</a> &lt; 0)
<a name="L1165" href="source/net/ipv4/fib_frontend.c#L1165">1165</a>                 goto <a href="ident?i=fail">fail</a>;
<a name="L1166" href="source/net/ipv4/fib_frontend.c#L1166">1166</a>         return 0;
<a name="L1167" href="source/net/ipv4/fib_frontend.c#L1167">1167</a> 
<a name="L1168" href="source/net/ipv4/fib_frontend.c#L1168">1168</a> <a href="ident?i=fail">fail</a>:
<a name="L1169" href="source/net/ipv4/fib_frontend.c#L1169">1169</a>         <a href="ident?i=kfree">kfree</a>(<a href="ident?i=net">net</a>-&gt;ipv4.fib_table_hash);
<a name="L1170" href="source/net/ipv4/fib_frontend.c#L1170">1170</a>         return <a href="ident?i=err">err</a>;
<a name="L1171" href="source/net/ipv4/fib_frontend.c#L1171">1171</a> }
<a name="L1172" href="source/net/ipv4/fib_frontend.c#L1172">1172</a> 
<a name="L1173" href="source/net/ipv4/fib_frontend.c#L1173">1173</a> static void <a href="ident?i=ip_fib_net_exit">ip_fib_net_exit</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>)
<a name="L1174" href="source/net/ipv4/fib_frontend.c#L1174">1174</a> {
<a name="L1175" href="source/net/ipv4/fib_frontend.c#L1175">1175</a>         unsigned int <a href="ident?i=i">i</a>;
<a name="L1176" href="source/net/ipv4/fib_frontend.c#L1176">1176</a> 
<a name="L1177" href="source/net/ipv4/fib_frontend.c#L1177">1177</a>         <a href="ident?i=rtnl_lock">rtnl_lock</a>();
<a name="L1178" href="source/net/ipv4/fib_frontend.c#L1178">1178</a> #ifdef CONFIG_IP_MULTIPLE_TABLES
<a name="L1179" href="source/net/ipv4/fib_frontend.c#L1179">1179</a>         <a href="ident?i=RCU_INIT_POINTER">RCU_INIT_POINTER</a>(<a href="ident?i=net">net</a>-&gt;ipv4.fib_local, <a href="ident?i=NULL">NULL</a>);
<a name="L1180" href="source/net/ipv4/fib_frontend.c#L1180">1180</a>         <a href="ident?i=RCU_INIT_POINTER">RCU_INIT_POINTER</a>(<a href="ident?i=net">net</a>-&gt;ipv4.fib_main, <a href="ident?i=NULL">NULL</a>);
<a name="L1181" href="source/net/ipv4/fib_frontend.c#L1181">1181</a>         <a href="ident?i=RCU_INIT_POINTER">RCU_INIT_POINTER</a>(<a href="ident?i=net">net</a>-&gt;ipv4.fib_default, <a href="ident?i=NULL">NULL</a>);
<a name="L1182" href="source/net/ipv4/fib_frontend.c#L1182">1182</a> #endif
<a name="L1183" href="source/net/ipv4/fib_frontend.c#L1183">1183</a>         for (<a href="ident?i=i">i</a> = 0; <a href="ident?i=i">i</a> &lt; <a href="ident?i=FIB_TABLE_HASHSZ">FIB_TABLE_HASHSZ</a>; <a href="ident?i=i">i</a>++) {
<a name="L1184" href="source/net/ipv4/fib_frontend.c#L1184">1184</a>                 struct <a href="ident?i=hlist_head">hlist_head</a> *<a href="ident?i=head">head</a> = &amp;<a href="ident?i=net">net</a>-&gt;ipv4.fib_table_hash[<a href="ident?i=i">i</a>];
<a name="L1185" href="source/net/ipv4/fib_frontend.c#L1185">1185</a>                 struct <a href="ident?i=hlist_node">hlist_node</a> *<a href="ident?i=tmp">tmp</a>;
<a name="L1186" href="source/net/ipv4/fib_frontend.c#L1186">1186</a>                 struct <a href="ident?i=fib_table">fib_table</a> *<a href="ident?i=tb">tb</a>;
<a name="L1187" href="source/net/ipv4/fib_frontend.c#L1187">1187</a> 
<a name="L1188" href="source/net/ipv4/fib_frontend.c#L1188">1188</a>                 <a href="ident?i=hlist_for_each_entry_safe">hlist_for_each_entry_safe</a>(<a href="ident?i=tb">tb</a>, <a href="ident?i=tmp">tmp</a>, <a href="ident?i=head">head</a>, tb_hlist) {
<a name="L1189" href="source/net/ipv4/fib_frontend.c#L1189">1189</a>                         <a href="ident?i=hlist_del">hlist_del</a>(&amp;<a href="ident?i=tb">tb</a>-&gt;tb_hlist);
<a name="L1190" href="source/net/ipv4/fib_frontend.c#L1190">1190</a>                         <a href="ident?i=fib_table_flush">fib_table_flush</a>(<a href="ident?i=tb">tb</a>);
<a name="L1191" href="source/net/ipv4/fib_frontend.c#L1191">1191</a>                         <a href="ident?i=fib_free_table">fib_free_table</a>(<a href="ident?i=tb">tb</a>);
<a name="L1192" href="source/net/ipv4/fib_frontend.c#L1192">1192</a>                 }
<a name="L1193" href="source/net/ipv4/fib_frontend.c#L1193">1193</a>         }
<a name="L1194" href="source/net/ipv4/fib_frontend.c#L1194">1194</a> 
<a name="L1195" href="source/net/ipv4/fib_frontend.c#L1195">1195</a> #ifdef CONFIG_IP_MULTIPLE_TABLES
<a name="L1196" href="source/net/ipv4/fib_frontend.c#L1196">1196</a>         <a href="ident?i=fib4_rules_exit">fib4_rules_exit</a>(<a href="ident?i=net">net</a>);
<a name="L1197" href="source/net/ipv4/fib_frontend.c#L1197">1197</a> #endif
<a name="L1198" href="source/net/ipv4/fib_frontend.c#L1198">1198</a>         <a href="ident?i=rtnl_unlock">rtnl_unlock</a>();
<a name="L1199" href="source/net/ipv4/fib_frontend.c#L1199">1199</a>         <a href="ident?i=kfree">kfree</a>(<a href="ident?i=net">net</a>-&gt;ipv4.fib_table_hash);
<a name="L1200" href="source/net/ipv4/fib_frontend.c#L1200">1200</a> }
<a name="L1201" href="source/net/ipv4/fib_frontend.c#L1201">1201</a> 
<a name="L1202" href="source/net/ipv4/fib_frontend.c#L1202">1202</a> static int <a href="ident?i=__net_init">__net_init</a> <a href="ident?i=fib_net_init">fib_net_init</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>)
<a name="L1203" href="source/net/ipv4/fib_frontend.c#L1203">1203</a> {
<a name="L1204" href="source/net/ipv4/fib_frontend.c#L1204">1204</a>         int <a href="ident?i=error">error</a>;
<a name="L1205" href="source/net/ipv4/fib_frontend.c#L1205">1205</a> 
<a name="L1206" href="source/net/ipv4/fib_frontend.c#L1206">1206</a> #ifdef CONFIG_IP_ROUTE_CLASSID
<a name="L1207" href="source/net/ipv4/fib_frontend.c#L1207">1207</a>         <a href="ident?i=net">net</a>-&gt;ipv4.<a href="ident?i=fib_num_tclassid_users">fib_num_tclassid_users</a> = 0;
<a name="L1208" href="source/net/ipv4/fib_frontend.c#L1208">1208</a> #endif
<a name="L1209" href="source/net/ipv4/fib_frontend.c#L1209">1209</a>         <a href="ident?i=error">error</a> = <a href="ident?i=ip_fib_net_init">ip_fib_net_init</a>(<a href="ident?i=net">net</a>);
<a name="L1210" href="source/net/ipv4/fib_frontend.c#L1210">1210</a>         if (<a href="ident?i=error">error</a> &lt; 0)
<a name="L1211" href="source/net/ipv4/fib_frontend.c#L1211">1211</a>                 goto <a href="ident?i=out">out</a>;
<a name="L1212" href="source/net/ipv4/fib_frontend.c#L1212">1212</a>         <a href="ident?i=error">error</a> = <a href="ident?i=nl_fib_lookup_init">nl_fib_lookup_init</a>(<a href="ident?i=net">net</a>);
<a name="L1213" href="source/net/ipv4/fib_frontend.c#L1213">1213</a>         if (<a href="ident?i=error">error</a> &lt; 0)
<a name="L1214" href="source/net/ipv4/fib_frontend.c#L1214">1214</a>                 goto out_nlfl;
<a name="L1215" href="source/net/ipv4/fib_frontend.c#L1215">1215</a>         <a href="ident?i=error">error</a> = <a href="ident?i=fib_proc_init">fib_proc_init</a>(<a href="ident?i=net">net</a>);
<a name="L1216" href="source/net/ipv4/fib_frontend.c#L1216">1216</a>         if (<a href="ident?i=error">error</a> &lt; 0)
<a name="L1217" href="source/net/ipv4/fib_frontend.c#L1217">1217</a>                 goto out_proc;
<a name="L1218" href="source/net/ipv4/fib_frontend.c#L1218">1218</a> <a href="ident?i=out">out</a>:
<a name="L1219" href="source/net/ipv4/fib_frontend.c#L1219">1219</a>         return <a href="ident?i=error">error</a>;
<a name="L1220" href="source/net/ipv4/fib_frontend.c#L1220">1220</a> 
<a name="L1221" href="source/net/ipv4/fib_frontend.c#L1221">1221</a> out_proc:
<a name="L1222" href="source/net/ipv4/fib_frontend.c#L1222">1222</a>         <a href="ident?i=nl_fib_lookup_exit">nl_fib_lookup_exit</a>(<a href="ident?i=net">net</a>);
<a name="L1223" href="source/net/ipv4/fib_frontend.c#L1223">1223</a> out_nlfl:
<a name="L1224" href="source/net/ipv4/fib_frontend.c#L1224">1224</a>         <a href="ident?i=ip_fib_net_exit">ip_fib_net_exit</a>(<a href="ident?i=net">net</a>);
<a name="L1225" href="source/net/ipv4/fib_frontend.c#L1225">1225</a>         goto <a href="ident?i=out">out</a>;
<a name="L1226" href="source/net/ipv4/fib_frontend.c#L1226">1226</a> }
<a name="L1227" href="source/net/ipv4/fib_frontend.c#L1227">1227</a> 
<a name="L1228" href="source/net/ipv4/fib_frontend.c#L1228">1228</a> static void <a href="ident?i=__net_exit">__net_exit</a> <a href="ident?i=fib_net_exit">fib_net_exit</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>)
<a name="L1229" href="source/net/ipv4/fib_frontend.c#L1229">1229</a> {
<a name="L1230" href="source/net/ipv4/fib_frontend.c#L1230">1230</a>         <a href="ident?i=fib_proc_exit">fib_proc_exit</a>(<a href="ident?i=net">net</a>);
<a name="L1231" href="source/net/ipv4/fib_frontend.c#L1231">1231</a>         <a href="ident?i=nl_fib_lookup_exit">nl_fib_lookup_exit</a>(<a href="ident?i=net">net</a>);
<a name="L1232" href="source/net/ipv4/fib_frontend.c#L1232">1232</a>         <a href="ident?i=ip_fib_net_exit">ip_fib_net_exit</a>(<a href="ident?i=net">net</a>);
<a name="L1233" href="source/net/ipv4/fib_frontend.c#L1233">1233</a> }
<a name="L1234" href="source/net/ipv4/fib_frontend.c#L1234">1234</a> 
<a name="L1235" href="source/net/ipv4/fib_frontend.c#L1235">1235</a> static struct <a href="ident?i=pernet_operations">pernet_operations</a> <a href="ident?i=fib_net_ops">fib_net_ops</a> = {
<a name="L1236" href="source/net/ipv4/fib_frontend.c#L1236">1236</a>         .<a href="ident?i=init">init</a> = <a href="ident?i=fib_net_init">fib_net_init</a>,
<a name="L1237" href="source/net/ipv4/fib_frontend.c#L1237">1237</a>         .<a href="ident?i=exit">exit</a> = <a href="ident?i=fib_net_exit">fib_net_exit</a>,
<a name="L1238" href="source/net/ipv4/fib_frontend.c#L1238">1238</a> };
<a name="L1239" href="source/net/ipv4/fib_frontend.c#L1239">1239</a> 
<a name="L1240" href="source/net/ipv4/fib_frontend.c#L1240">1240</a> void <a href="ident?i=__init">__init</a> <a href="ident?i=ip_fib_init">ip_fib_init</a>(void)
<a name="L1241" href="source/net/ipv4/fib_frontend.c#L1241">1241</a> {
<a name="L1242" href="source/net/ipv4/fib_frontend.c#L1242">1242</a>         <a href="ident?i=rtnl_register">rtnl_register</a>(<a href="ident?i=PF_INET">PF_INET</a>, <a href="ident?i=RTM_NEWROUTE">RTM_NEWROUTE</a>, <a href="ident?i=inet_rtm_newroute">inet_rtm_newroute</a>, <a href="ident?i=NULL">NULL</a>, <a href="ident?i=NULL">NULL</a>);
<a name="L1243" href="source/net/ipv4/fib_frontend.c#L1243">1243</a>         <a href="ident?i=rtnl_register">rtnl_register</a>(<a href="ident?i=PF_INET">PF_INET</a>, <a href="ident?i=RTM_DELROUTE">RTM_DELROUTE</a>, <a href="ident?i=inet_rtm_delroute">inet_rtm_delroute</a>, <a href="ident?i=NULL">NULL</a>, <a href="ident?i=NULL">NULL</a>);
<a name="L1244" href="source/net/ipv4/fib_frontend.c#L1244">1244</a>         <a href="ident?i=rtnl_register">rtnl_register</a>(<a href="ident?i=PF_INET">PF_INET</a>, <a href="ident?i=RTM_GETROUTE">RTM_GETROUTE</a>, <a href="ident?i=NULL">NULL</a>, <a href="ident?i=inet_dump_fib">inet_dump_fib</a>, <a href="ident?i=NULL">NULL</a>);
<a name="L1245" href="source/net/ipv4/fib_frontend.c#L1245">1245</a> 
<a name="L1246" href="source/net/ipv4/fib_frontend.c#L1246">1246</a>         <a href="ident?i=register_pernet_subsys">register_pernet_subsys</a>(&amp;<a href="ident?i=fib_net_ops">fib_net_ops</a>);
<a name="L1247" href="source/net/ipv4/fib_frontend.c#L1247">1247</a>         <a href="ident?i=register_netdevice_notifier">register_netdevice_notifier</a>(&amp;<a href="ident?i=fib_netdev_notifier">fib_netdev_notifier</a>);
<a name="L1248" href="source/net/ipv4/fib_frontend.c#L1248">1248</a>         <a href="ident?i=register_inetaddr_notifier">register_inetaddr_notifier</a>(&amp;<a href="ident?i=fib_inetaddr_notifier">fib_inetaddr_notifier</a>);
<a name="L1249" href="source/net/ipv4/fib_frontend.c#L1249">1249</a> 
<a name="L1250" href="source/net/ipv4/fib_frontend.c#L1250">1250</a>         <a href="ident?i=fib_trie_init">fib_trie_init</a>();
<a name="L1251" href="source/net/ipv4/fib_frontend.c#L1251">1251</a> }
<a name="L1252" href="source/net/ipv4/fib_frontend.c#L1252">1252</a> </pre></div><p>
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
