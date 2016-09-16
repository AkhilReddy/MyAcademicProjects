<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title>Linux/net/ipv4/fib_trie.c - Linux Cross Reference - Free Electrons</title>
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
		 &nbsp;&bull;&nbsp;<b><i>source navigation</i></b> &nbsp;&bull;&nbsp;<a href="diff/net/ipv4/fib_trie.c">diff markup</a> &nbsp;&bull;&nbsp;<a href="ident">identifier search</a> &nbsp;&bull;&nbsp;<a href="search">freetext search</a> &nbsp;&bull;&nbsp;
		</p>
	</div>
</div>

<div id="topbar">
  
  <p>Version: &nbsp;<a href="source/net/ipv4/fib_trie.c?v=2.0.40">2.0.40</a>&nbsp;<a href="source/net/ipv4/fib_trie.c?v=2.2.26">2.2.26</a>&nbsp;<a href="source/net/ipv4/fib_trie.c?v=2.4.37">2.4.37</a>&nbsp;<a href="source/net/ipv4/fib_trie.c?v=3.5">3.5</a>&nbsp;<a href="source/net/ipv4/fib_trie.c?v=3.6">3.6</a>&nbsp;<a href="source/net/ipv4/fib_trie.c?v=3.7">3.7</a>&nbsp;<a href="source/net/ipv4/fib_trie.c?v=3.8">3.8</a>&nbsp;<a href="source/net/ipv4/fib_trie.c?v=3.9">3.9</a>&nbsp;<a href="source/net/ipv4/fib_trie.c?v=3.10">3.10</a>&nbsp;<a href="source/net/ipv4/fib_trie.c?v=3.11">3.11</a>&nbsp;<a href="source/net/ipv4/fib_trie.c?v=3.12">3.12</a>&nbsp;<a href="source/net/ipv4/fib_trie.c?v=3.13">3.13</a>&nbsp;<a href="source/net/ipv4/fib_trie.c?v=3.14">3.14</a>&nbsp;<a href="source/net/ipv4/fib_trie.c?v=3.15">3.15</a>&nbsp;<a href="source/net/ipv4/fib_trie.c?v=3.16">3.16</a>&nbsp;<a href="source/net/ipv4/fib_trie.c?v=3.17">3.17</a>&nbsp;<a href="source/net/ipv4/fib_trie.c?v=3.18">3.18</a>&nbsp;<a href="source/net/ipv4/fib_trie.c?v=3.19">3.19</a>&nbsp;<a href="source/net/ipv4/fib_trie.c?v=4.0">4.0</a>&nbsp;<b><i>4.1</i></b></p>
  
</div>

<h1><a href="source/">Linux</a>/<a href="source/net/">net</a>/<a href="source/net/ipv4/">ipv4</a>/<a href="source/net/ipv4/fib_trie.c">fib_trie.c</a></h1>
<div id="lxrcode"><pre>  <a name="L1" href="source/net/ipv4/fib_trie.c#L1">1</a> <b><i>/*</i></b>
  <a name="L2" href="source/net/ipv4/fib_trie.c#L2">2</a> <b><i> *   This program is free software; you can redistribute it and/or</i></b>
  <a name="L3" href="source/net/ipv4/fib_trie.c#L3">3</a> <b><i> *   modify it under the terms of the GNU General Public License</i></b>
  <a name="L4" href="source/net/ipv4/fib_trie.c#L4">4</a> <b><i> *   as published by the Free Software Foundation; either version</i></b>
  <a name="L5" href="source/net/ipv4/fib_trie.c#L5">5</a> <b><i> *   2 of the License, or (at your option) any later version.</i></b>
  <a name="L6" href="source/net/ipv4/fib_trie.c#L6">6</a> <b><i> *</i></b>
  <a name="L7" href="source/net/ipv4/fib_trie.c#L7">7</a> <b><i> *   Robert Olsson &lt;robert.olsson@its.uu.se&gt; Uppsala Universitet</i></b>
  <a name="L8" href="source/net/ipv4/fib_trie.c#L8">8</a> <b><i> *     &amp; Swedish University of Agricultural Sciences.</i></b>
  <a name="L9" href="source/net/ipv4/fib_trie.c#L9">9</a> <b><i> *</i></b>
 <a name="L10" href="source/net/ipv4/fib_trie.c#L10">10</a> <b><i> *   Jens Laas &lt;jens.laas@data.slu.se&gt; Swedish University of</i></b>
 <a name="L11" href="source/net/ipv4/fib_trie.c#L11">11</a> <b><i> *     Agricultural Sciences.</i></b>
 <a name="L12" href="source/net/ipv4/fib_trie.c#L12">12</a> <b><i> *</i></b>
 <a name="L13" href="source/net/ipv4/fib_trie.c#L13">13</a> <b><i> *   Hans Liss &lt;hans.liss@its.uu.se&gt;  Uppsala Universitet</i></b>
 <a name="L14" href="source/net/ipv4/fib_trie.c#L14">14</a> <b><i> *</i></b>
 <a name="L15" href="source/net/ipv4/fib_trie.c#L15">15</a> <b><i> * This work is based on the LPC-trie which is originally described in:</i></b>
 <a name="L16" href="source/net/ipv4/fib_trie.c#L16">16</a> <b><i> *</i></b>
 <a name="L17" href="source/net/ipv4/fib_trie.c#L17">17</a> <b><i> * An experimental study of compression methods for dynamic tries</i></b>
 <a name="L18" href="source/net/ipv4/fib_trie.c#L18">18</a> <b><i> * Stefan Nilsson and Matti Tikkanen. Algorithmica, 33(1):19-33, 2002.</i></b>
 <a name="L19" href="source/net/ipv4/fib_trie.c#L19">19</a> <b><i> * <a href="http://www.csc.kth.se/~snilsson/software/dyntrie2/">http://www.csc.kth.se/~snilsson/software/dyntrie2/</a></i></b>
 <a name="L20" href="source/net/ipv4/fib_trie.c#L20">20</a> <b><i> *</i></b>
 <a name="L21" href="source/net/ipv4/fib_trie.c#L21">21</a> <b><i> *</i></b>
 <a name="L22" href="source/net/ipv4/fib_trie.c#L22">22</a> <b><i> * IP-address lookup using LC-tries. Stefan Nilsson and Gunnar Karlsson</i></b>
 <a name="L23" href="source/net/ipv4/fib_trie.c#L23">23</a> <b><i> * IEEE Journal on Selected Areas in Communications, 17(6):1083-1092, June 1999</i></b>
 <a name="L24" href="source/net/ipv4/fib_trie.c#L24">24</a> <b><i> *</i></b>
 <a name="L25" href="source/net/ipv4/fib_trie.c#L25">25</a> <b><i> *</i></b>
 <a name="L26" href="source/net/ipv4/fib_trie.c#L26">26</a> <b><i> * Code from fib_hash has been reused which includes the following header:</i></b>
 <a name="L27" href="source/net/ipv4/fib_trie.c#L27">27</a> <b><i> *</i></b>
 <a name="L28" href="source/net/ipv4/fib_trie.c#L28">28</a> <b><i> *</i></b>
 <a name="L29" href="source/net/ipv4/fib_trie.c#L29">29</a> <b><i> * INET         An implementation of the TCP/IP protocol suite for the LINUX</i></b>
 <a name="L30" href="source/net/ipv4/fib_trie.c#L30">30</a> <b><i> *              operating system.  INET is implemented using the  BSD Socket</i></b>
 <a name="L31" href="source/net/ipv4/fib_trie.c#L31">31</a> <b><i> *              interface as the means of communication with the user level.</i></b>
 <a name="L32" href="source/net/ipv4/fib_trie.c#L32">32</a> <b><i> *</i></b>
 <a name="L33" href="source/net/ipv4/fib_trie.c#L33">33</a> <b><i> *              IPv4 FIB: lookup engine and maintenance routines.</i></b>
 <a name="L34" href="source/net/ipv4/fib_trie.c#L34">34</a> <b><i> *</i></b>
 <a name="L35" href="source/net/ipv4/fib_trie.c#L35">35</a> <b><i> *</i></b>
 <a name="L36" href="source/net/ipv4/fib_trie.c#L36">36</a> <b><i> * Authors:     Alexey Kuznetsov, &lt;kuznet@ms2.inr.ac.ru&gt;</i></b>
 <a name="L37" href="source/net/ipv4/fib_trie.c#L37">37</a> <b><i> *</i></b>
 <a name="L38" href="source/net/ipv4/fib_trie.c#L38">38</a> <b><i> *              This program is free software; you can redistribute it and/or</i></b>
 <a name="L39" href="source/net/ipv4/fib_trie.c#L39">39</a> <b><i> *              modify it under the terms of the GNU General Public License</i></b>
 <a name="L40" href="source/net/ipv4/fib_trie.c#L40">40</a> <b><i> *              as published by the Free Software Foundation; either version</i></b>
 <a name="L41" href="source/net/ipv4/fib_trie.c#L41">41</a> <b><i> *              2 of the License, or (at your option) any later version.</i></b>
 <a name="L42" href="source/net/ipv4/fib_trie.c#L42">42</a> <b><i> *</i></b>
 <a name="L43" href="source/net/ipv4/fib_trie.c#L43">43</a> <b><i> * Substantial contributions to this work comes from:</i></b>
 <a name="L44" href="source/net/ipv4/fib_trie.c#L44">44</a> <b><i> *</i></b>
 <a name="L45" href="source/net/ipv4/fib_trie.c#L45">45</a> <b><i> *              David S. Miller, &lt;davem@davemloft.net&gt;</i></b>
 <a name="L46" href="source/net/ipv4/fib_trie.c#L46">46</a> <b><i> *              Stephen Hemminger &lt;shemminger@osdl.org&gt;</i></b>
 <a name="L47" href="source/net/ipv4/fib_trie.c#L47">47</a> <b><i> *              Paul E. McKenney &lt;paulmck@us.ibm.com&gt;</i></b>
 <a name="L48" href="source/net/ipv4/fib_trie.c#L48">48</a> <b><i> *              Patrick McHardy &lt;kaber@trash.net&gt;</i></b>
 <a name="L49" href="source/net/ipv4/fib_trie.c#L49">49</a> <b><i> */</i></b>
 <a name="L50" href="source/net/ipv4/fib_trie.c#L50">50</a> 
 <a name="L51" href="source/net/ipv4/fib_trie.c#L51">51</a> #define <a href="ident?i=VERSION">VERSION</a> <i>"0.409"</i>
 <a name="L52" href="source/net/ipv4/fib_trie.c#L52">52</a> 
 <a name="L53" href="source/net/ipv4/fib_trie.c#L53">53</a> #include &lt;asm/uaccess.h&gt;
 <a name="L54" href="source/net/ipv4/fib_trie.c#L54">54</a> #include &lt;linux/bitops.h&gt;
 <a name="L55" href="source/net/ipv4/fib_trie.c#L55">55</a> #include &lt;linux/types.h&gt;
 <a name="L56" href="source/net/ipv4/fib_trie.c#L56">56</a> #include &lt;linux/kernel.h&gt;
 <a name="L57" href="source/net/ipv4/fib_trie.c#L57">57</a> #include &lt;linux/mm.h&gt;
 <a name="L58" href="source/net/ipv4/fib_trie.c#L58">58</a> #include &lt;linux/string.h&gt;
 <a name="L59" href="source/net/ipv4/fib_trie.c#L59">59</a> #include &lt;linux/socket.h&gt;
 <a name="L60" href="source/net/ipv4/fib_trie.c#L60">60</a> #include &lt;linux/sockios.h&gt;
 <a name="L61" href="source/net/ipv4/fib_trie.c#L61">61</a> #include &lt;linux/errno.h&gt;
 <a name="L62" href="source/net/ipv4/fib_trie.c#L62">62</a> #include &lt;linux/in.h&gt;
 <a name="L63" href="source/net/ipv4/fib_trie.c#L63">63</a> #include &lt;linux/inet.h&gt;
 <a name="L64" href="source/net/ipv4/fib_trie.c#L64">64</a> #include &lt;linux/inetdevice.h&gt;
 <a name="L65" href="source/net/ipv4/fib_trie.c#L65">65</a> #include &lt;linux/netdevice.h&gt;
 <a name="L66" href="source/net/ipv4/fib_trie.c#L66">66</a> #include &lt;linux/if_arp.h&gt;
 <a name="L67" href="source/net/ipv4/fib_trie.c#L67">67</a> #include &lt;linux/proc_fs.h&gt;
 <a name="L68" href="source/net/ipv4/fib_trie.c#L68">68</a> #include &lt;linux/rcupdate.h&gt;
 <a name="L69" href="source/net/ipv4/fib_trie.c#L69">69</a> #include &lt;linux/skbuff.h&gt;
 <a name="L70" href="source/net/ipv4/fib_trie.c#L70">70</a> #include &lt;linux/netlink.h&gt;
 <a name="L71" href="source/net/ipv4/fib_trie.c#L71">71</a> #include &lt;linux/init.h&gt;
 <a name="L72" href="source/net/ipv4/fib_trie.c#L72">72</a> #include &lt;linux/list.h&gt;
 <a name="L73" href="source/net/ipv4/fib_trie.c#L73">73</a> #include &lt;linux/slab.h&gt;
 <a name="L74" href="source/net/ipv4/fib_trie.c#L74">74</a> #include &lt;linux/export.h&gt;
 <a name="L75" href="source/net/ipv4/fib_trie.c#L75">75</a> #include &lt;net/net_namespace.h&gt;
 <a name="L76" href="source/net/ipv4/fib_trie.c#L76">76</a> #include &lt;net/ip.h&gt;
 <a name="L77" href="source/net/ipv4/fib_trie.c#L77">77</a> #include &lt;net/protocol.h&gt;
 <a name="L78" href="source/net/ipv4/fib_trie.c#L78">78</a> #include &lt;net/route.h&gt;
 <a name="L79" href="source/net/ipv4/fib_trie.c#L79">79</a> #include &lt;net/tcp.h&gt;
 <a name="L80" href="source/net/ipv4/fib_trie.c#L80">80</a> #include &lt;net/sock.h&gt;
 <a name="L81" href="source/net/ipv4/fib_trie.c#L81">81</a> #include &lt;net/ip_fib.h&gt;
 <a name="L82" href="source/net/ipv4/fib_trie.c#L82">82</a> #include &lt;net/switchdev.h&gt;
 <a name="L83" href="source/net/ipv4/fib_trie.c#L83">83</a> #include "<a href="source/net/ipv4/fib_lookup.h">fib_lookup.h</a>"
 <a name="L84" href="source/net/ipv4/fib_trie.c#L84">84</a> 
 <a name="L85" href="source/net/ipv4/fib_trie.c#L85">85</a> #define <a href="ident?i=MAX_STAT_DEPTH">MAX_STAT_DEPTH</a> 32
 <a name="L86" href="source/net/ipv4/fib_trie.c#L86">86</a> 
 <a name="L87" href="source/net/ipv4/fib_trie.c#L87">87</a> #define <a href="ident?i=KEYLENGTH">KEYLENGTH</a>       (8*sizeof(<a href="ident?i=t_key">t_key</a>))
 <a name="L88" href="source/net/ipv4/fib_trie.c#L88">88</a> #define <a href="ident?i=KEY_MAX">KEY_MAX</a>         ((<a href="ident?i=t_key">t_key</a>)~0)
 <a name="L89" href="source/net/ipv4/fib_trie.c#L89">89</a> 
 <a name="L90" href="source/net/ipv4/fib_trie.c#L90">90</a> typedef unsigned int <a href="ident?i=t_key">t_key</a>;
 <a name="L91" href="source/net/ipv4/fib_trie.c#L91">91</a> 
 <a name="L92" href="source/net/ipv4/fib_trie.c#L92">92</a> #define <a href="ident?i=IS_TRIE">IS_TRIE</a>(<a href="ident?i=n">n</a>)      ((<a href="ident?i=n">n</a>)-&gt;<a href="ident?i=pos">pos</a> &gt;= <a href="ident?i=KEYLENGTH">KEYLENGTH</a>)
 <a name="L93" href="source/net/ipv4/fib_trie.c#L93">93</a> #define <a href="ident?i=IS_TNODE">IS_TNODE</a>(<a href="ident?i=n">n</a>)     ((<a href="ident?i=n">n</a>)-&gt;<a href="ident?i=bits">bits</a>)
 <a name="L94" href="source/net/ipv4/fib_trie.c#L94">94</a> #define <a href="ident?i=IS_LEAF">IS_LEAF</a>(<a href="ident?i=n">n</a>)      (!(<a href="ident?i=n">n</a>)-&gt;<a href="ident?i=bits">bits</a>)
 <a name="L95" href="source/net/ipv4/fib_trie.c#L95">95</a> 
 <a name="L96" href="source/net/ipv4/fib_trie.c#L96">96</a> struct <a href="ident?i=key_vector">key_vector</a> {
 <a name="L97" href="source/net/ipv4/fib_trie.c#L97">97</a>         <a href="ident?i=t_key">t_key</a> <a href="ident?i=key">key</a>;
 <a name="L98" href="source/net/ipv4/fib_trie.c#L98">98</a>         unsigned char <a href="ident?i=pos">pos</a>;              <b><i>/* 2log(KEYLENGTH) bits needed */</i></b>
 <a name="L99" href="source/net/ipv4/fib_trie.c#L99">99</a>         unsigned char <a href="ident?i=bits">bits</a>;             <b><i>/* 2log(KEYLENGTH) bits needed */</i></b>
<a name="L100" href="source/net/ipv4/fib_trie.c#L100">100</a>         unsigned char slen;
<a name="L101" href="source/net/ipv4/fib_trie.c#L101">101</a>         union {
<a name="L102" href="source/net/ipv4/fib_trie.c#L102">102</a>                 <b><i>/* This list pointer if valid if (pos | bits) == 0 (LEAF) */</i></b>
<a name="L103" href="source/net/ipv4/fib_trie.c#L103">103</a>                 struct <a href="ident?i=hlist_head">hlist_head</a> leaf;
<a name="L104" href="source/net/ipv4/fib_trie.c#L104">104</a>                 <b><i>/* This array is valid if (pos | bits) &gt; 0 (TNODE) */</i></b>
<a name="L105" href="source/net/ipv4/fib_trie.c#L105">105</a>                 struct <a href="ident?i=key_vector">key_vector</a> <a href="ident?i=__rcu">__rcu</a> *<a href="ident?i=tnode">tnode</a>[0];
<a name="L106" href="source/net/ipv4/fib_trie.c#L106">106</a>         };
<a name="L107" href="source/net/ipv4/fib_trie.c#L107">107</a> };
<a name="L108" href="source/net/ipv4/fib_trie.c#L108">108</a> 
<a name="L109" href="source/net/ipv4/fib_trie.c#L109">109</a> struct <a href="ident?i=tnode">tnode</a> {
<a name="L110" href="source/net/ipv4/fib_trie.c#L110">110</a>         struct <a href="ident?i=rcu_head">rcu_head</a> rcu;
<a name="L111" href="source/net/ipv4/fib_trie.c#L111">111</a>         <a href="ident?i=t_key">t_key</a> empty_children;           <b><i>/* KEYLENGTH bits needed */</i></b>
<a name="L112" href="source/net/ipv4/fib_trie.c#L112">112</a>         <a href="ident?i=t_key">t_key</a> full_children;            <b><i>/* KEYLENGTH bits needed */</i></b>
<a name="L113" href="source/net/ipv4/fib_trie.c#L113">113</a>         struct <a href="ident?i=key_vector">key_vector</a> <a href="ident?i=__rcu">__rcu</a> *<a href="ident?i=parent">parent</a>;
<a name="L114" href="source/net/ipv4/fib_trie.c#L114">114</a>         struct <a href="ident?i=key_vector">key_vector</a> kv[1];
<a name="L115" href="source/net/ipv4/fib_trie.c#L115">115</a> #define <a href="ident?i=tn_bits">tn_bits</a> kv[0].<a href="ident?i=bits">bits</a>
<a name="L116" href="source/net/ipv4/fib_trie.c#L116">116</a> };
<a name="L117" href="source/net/ipv4/fib_trie.c#L117">117</a> 
<a name="L118" href="source/net/ipv4/fib_trie.c#L118">118</a> #define <a href="ident?i=TNODE_SIZE">TNODE_SIZE</a>(<a href="ident?i=n">n</a>)   <a href="ident?i=offsetof">offsetof</a>(struct <a href="ident?i=tnode">tnode</a>, kv[0].<a href="ident?i=tnode">tnode</a>[<a href="ident?i=n">n</a>])
<a name="L119" href="source/net/ipv4/fib_trie.c#L119">119</a> #define <a href="ident?i=LEAF_SIZE">LEAF_SIZE</a>       <a href="ident?i=TNODE_SIZE">TNODE_SIZE</a>(1)
<a name="L120" href="source/net/ipv4/fib_trie.c#L120">120</a> 
<a name="L121" href="source/net/ipv4/fib_trie.c#L121">121</a> #ifdef CONFIG_IP_FIB_TRIE_STATS
<a name="L122" href="source/net/ipv4/fib_trie.c#L122">122</a> struct <a href="ident?i=trie_use_stats">trie_use_stats</a> {
<a name="L123" href="source/net/ipv4/fib_trie.c#L123">123</a>         unsigned int gets;
<a name="L124" href="source/net/ipv4/fib_trie.c#L124">124</a>         unsigned int backtrack;
<a name="L125" href="source/net/ipv4/fib_trie.c#L125">125</a>         unsigned int semantic_match_passed;
<a name="L126" href="source/net/ipv4/fib_trie.c#L126">126</a>         unsigned int semantic_match_miss;
<a name="L127" href="source/net/ipv4/fib_trie.c#L127">127</a>         unsigned int null_node_hit;
<a name="L128" href="source/net/ipv4/fib_trie.c#L128">128</a>         unsigned int resize_node_skipped;
<a name="L129" href="source/net/ipv4/fib_trie.c#L129">129</a> };
<a name="L130" href="source/net/ipv4/fib_trie.c#L130">130</a> #endif
<a name="L131" href="source/net/ipv4/fib_trie.c#L131">131</a> 
<a name="L132" href="source/net/ipv4/fib_trie.c#L132">132</a> struct <a href="ident?i=trie_stat">trie_stat</a> {
<a name="L133" href="source/net/ipv4/fib_trie.c#L133">133</a>         unsigned int totdepth;
<a name="L134" href="source/net/ipv4/fib_trie.c#L134">134</a>         unsigned int <a href="ident?i=maxdepth">maxdepth</a>;
<a name="L135" href="source/net/ipv4/fib_trie.c#L135">135</a>         unsigned int tnodes;
<a name="L136" href="source/net/ipv4/fib_trie.c#L136">136</a>         unsigned int leaves;
<a name="L137" href="source/net/ipv4/fib_trie.c#L137">137</a>         unsigned int nullpointers;
<a name="L138" href="source/net/ipv4/fib_trie.c#L138">138</a>         unsigned int prefixes;
<a name="L139" href="source/net/ipv4/fib_trie.c#L139">139</a>         unsigned int nodesizes[<a href="ident?i=MAX_STAT_DEPTH">MAX_STAT_DEPTH</a>];
<a name="L140" href="source/net/ipv4/fib_trie.c#L140">140</a> };
<a name="L141" href="source/net/ipv4/fib_trie.c#L141">141</a> 
<a name="L142" href="source/net/ipv4/fib_trie.c#L142">142</a> struct <a href="ident?i=trie">trie</a> {
<a name="L143" href="source/net/ipv4/fib_trie.c#L143">143</a>         struct <a href="ident?i=key_vector">key_vector</a> kv[1];
<a name="L144" href="source/net/ipv4/fib_trie.c#L144">144</a> #ifdef CONFIG_IP_FIB_TRIE_STATS
<a name="L145" href="source/net/ipv4/fib_trie.c#L145">145</a>         struct <a href="ident?i=trie_use_stats">trie_use_stats</a> <a href="ident?i=__percpu">__percpu</a> *<a href="ident?i=stats">stats</a>;
<a name="L146" href="source/net/ipv4/fib_trie.c#L146">146</a> #endif
<a name="L147" href="source/net/ipv4/fib_trie.c#L147">147</a> };
<a name="L148" href="source/net/ipv4/fib_trie.c#L148">148</a> 
<a name="L149" href="source/net/ipv4/fib_trie.c#L149">149</a> static struct <a href="ident?i=key_vector">key_vector</a> *<a href="ident?i=resize">resize</a>(struct <a href="ident?i=trie">trie</a> *<a href="ident?i=t">t</a>, struct <a href="ident?i=key_vector">key_vector</a> *tn);
<a name="L150" href="source/net/ipv4/fib_trie.c#L150">150</a> static <a href="ident?i=size_t">size_t</a> <a href="ident?i=tnode_free_size">tnode_free_size</a>;
<a name="L151" href="source/net/ipv4/fib_trie.c#L151">151</a> 
<a name="L152" href="source/net/ipv4/fib_trie.c#L152">152</a> <b><i>/*</i></b>
<a name="L153" href="source/net/ipv4/fib_trie.c#L153">153</a> <b><i> * synchronize_rcu after call_rcu for that many pages; it should be especially</i></b>
<a name="L154" href="source/net/ipv4/fib_trie.c#L154">154</a> <b><i> * useful before resizing the root node with PREEMPT_NONE configs; the value was</i></b>
<a name="L155" href="source/net/ipv4/fib_trie.c#L155">155</a> <b><i> * obtained experimentally, aiming to avoid visible slowdown.</i></b>
<a name="L156" href="source/net/ipv4/fib_trie.c#L156">156</a> <b><i> */</i></b>
<a name="L157" href="source/net/ipv4/fib_trie.c#L157">157</a> static const int <a href="ident?i=sync_pages">sync_pages</a> = 128;
<a name="L158" href="source/net/ipv4/fib_trie.c#L158">158</a> 
<a name="L159" href="source/net/ipv4/fib_trie.c#L159">159</a> static struct <a href="ident?i=kmem_cache">kmem_cache</a> *fn_alias_kmem <a href="ident?i=__read_mostly">__read_mostly</a>;
<a name="L160" href="source/net/ipv4/fib_trie.c#L160">160</a> static struct <a href="ident?i=kmem_cache">kmem_cache</a> *trie_leaf_kmem <a href="ident?i=__read_mostly">__read_mostly</a>;
<a name="L161" href="source/net/ipv4/fib_trie.c#L161">161</a> 
<a name="L162" href="source/net/ipv4/fib_trie.c#L162">162</a> static inline struct <a href="ident?i=tnode">tnode</a> *<a href="ident?i=tn_info">tn_info</a>(struct <a href="ident?i=key_vector">key_vector</a> *kv)
<a name="L163" href="source/net/ipv4/fib_trie.c#L163">163</a> {
<a name="L164" href="source/net/ipv4/fib_trie.c#L164">164</a>         return <a href="ident?i=container_of">container_of</a>(kv, struct <a href="ident?i=tnode">tnode</a>, kv[0]);
<a name="L165" href="source/net/ipv4/fib_trie.c#L165">165</a> }
<a name="L166" href="source/net/ipv4/fib_trie.c#L166">166</a> 
<a name="L167" href="source/net/ipv4/fib_trie.c#L167">167</a> <b><i>/* caller must hold RTNL */</i></b>
<a name="L168" href="source/net/ipv4/fib_trie.c#L168">168</a> #define <a href="ident?i=node_parent">node_parent</a>(tn) <a href="ident?i=rtnl_dereference">rtnl_dereference</a>(<a href="ident?i=tn_info">tn_info</a>(tn)-&gt;<a href="ident?i=parent">parent</a>)
<a name="L169" href="source/net/ipv4/fib_trie.c#L169">169</a> #define <a href="ident?i=get_child">get_child</a>(tn, <a href="ident?i=i">i</a>) <a href="ident?i=rtnl_dereference">rtnl_dereference</a>((tn)-&gt;<a href="ident?i=tnode">tnode</a>[<a href="ident?i=i">i</a>])
<a name="L170" href="source/net/ipv4/fib_trie.c#L170">170</a> 
<a name="L171" href="source/net/ipv4/fib_trie.c#L171">171</a> <b><i>/* caller must hold RCU read lock or RTNL */</i></b>
<a name="L172" href="source/net/ipv4/fib_trie.c#L172">172</a> #define <a href="ident?i=node_parent_rcu">node_parent_rcu</a>(tn) <a href="ident?i=rcu_dereference_rtnl">rcu_dereference_rtnl</a>(<a href="ident?i=tn_info">tn_info</a>(tn)-&gt;<a href="ident?i=parent">parent</a>)
<a name="L173" href="source/net/ipv4/fib_trie.c#L173">173</a> #define <a href="ident?i=get_child_rcu">get_child_rcu</a>(tn, <a href="ident?i=i">i</a>) <a href="ident?i=rcu_dereference_rtnl">rcu_dereference_rtnl</a>((tn)-&gt;<a href="ident?i=tnode">tnode</a>[<a href="ident?i=i">i</a>])
<a name="L174" href="source/net/ipv4/fib_trie.c#L174">174</a> 
<a name="L175" href="source/net/ipv4/fib_trie.c#L175">175</a> <b><i>/* wrapper for rcu_assign_pointer */</i></b>
<a name="L176" href="source/net/ipv4/fib_trie.c#L176">176</a> static inline void <a href="ident?i=node_set_parent">node_set_parent</a>(struct <a href="ident?i=key_vector">key_vector</a> *<a href="ident?i=n">n</a>, struct <a href="ident?i=key_vector">key_vector</a> *<a href="ident?i=tp">tp</a>)
<a name="L177" href="source/net/ipv4/fib_trie.c#L177">177</a> {
<a name="L178" href="source/net/ipv4/fib_trie.c#L178">178</a>         if (<a href="ident?i=n">n</a>)
<a name="L179" href="source/net/ipv4/fib_trie.c#L179">179</a>                 <a href="ident?i=rcu_assign_pointer">rcu_assign_pointer</a>(<a href="ident?i=tn_info">tn_info</a>(<a href="ident?i=n">n</a>)-&gt;<a href="ident?i=parent">parent</a>, <a href="ident?i=tp">tp</a>);
<a name="L180" href="source/net/ipv4/fib_trie.c#L180">180</a> }
<a name="L181" href="source/net/ipv4/fib_trie.c#L181">181</a> 
<a name="L182" href="source/net/ipv4/fib_trie.c#L182">182</a> #define <a href="ident?i=NODE_INIT_PARENT">NODE_INIT_PARENT</a>(<a href="ident?i=n">n</a>, <a href="ident?i=p">p</a>) <a href="ident?i=RCU_INIT_POINTER">RCU_INIT_POINTER</a>(<a href="ident?i=tn_info">tn_info</a>(<a href="ident?i=n">n</a>)-&gt;<a href="ident?i=parent">parent</a>, <a href="ident?i=p">p</a>)
<a name="L183" href="source/net/ipv4/fib_trie.c#L183">183</a> 
<a name="L184" href="source/net/ipv4/fib_trie.c#L184">184</a> <b><i>/* This provides us with the number of children in this node, in the case of a</i></b>
<a name="L185" href="source/net/ipv4/fib_trie.c#L185">185</a> <b><i> * leaf this will return 0 meaning none of the children are accessible.</i></b>
<a name="L186" href="source/net/ipv4/fib_trie.c#L186">186</a> <b><i> */</i></b>
<a name="L187" href="source/net/ipv4/fib_trie.c#L187">187</a> static inline unsigned long <a href="ident?i=child_length">child_length</a>(const struct <a href="ident?i=key_vector">key_vector</a> *tn)
<a name="L188" href="source/net/ipv4/fib_trie.c#L188">188</a> {
<a name="L189" href="source/net/ipv4/fib_trie.c#L189">189</a>         return (1ul &lt;&lt; tn-&gt;<a href="ident?i=bits">bits</a>) &amp; ~(1ul);
<a name="L190" href="source/net/ipv4/fib_trie.c#L190">190</a> }
<a name="L191" href="source/net/ipv4/fib_trie.c#L191">191</a> 
<a name="L192" href="source/net/ipv4/fib_trie.c#L192">192</a> #define <a href="ident?i=get_cindex">get_cindex</a>(<a href="ident?i=key">key</a>, kv) (((<a href="ident?i=key">key</a>) ^ (kv)-&gt;<a href="ident?i=key">key</a>) &gt;&gt; (kv)-&gt;<a href="ident?i=pos">pos</a>)
<a name="L193" href="source/net/ipv4/fib_trie.c#L193">193</a> 
<a name="L194" href="source/net/ipv4/fib_trie.c#L194">194</a> static inline unsigned long <a href="ident?i=get_index">get_index</a>(<a href="ident?i=t_key">t_key</a> <a href="ident?i=key">key</a>, struct <a href="ident?i=key_vector">key_vector</a> *kv)
<a name="L195" href="source/net/ipv4/fib_trie.c#L195">195</a> {
<a name="L196" href="source/net/ipv4/fib_trie.c#L196">196</a>         unsigned long <a href="ident?i=index">index</a> = <a href="ident?i=key">key</a> ^ kv-&gt;<a href="ident?i=key">key</a>;
<a name="L197" href="source/net/ipv4/fib_trie.c#L197">197</a> 
<a name="L198" href="source/net/ipv4/fib_trie.c#L198">198</a>         if ((<a href="ident?i=BITS_PER_LONG">BITS_PER_LONG</a> &lt;= <a href="ident?i=KEYLENGTH">KEYLENGTH</a>) &amp;&amp; (<a href="ident?i=KEYLENGTH">KEYLENGTH</a> == kv-&gt;<a href="ident?i=pos">pos</a>))
<a name="L199" href="source/net/ipv4/fib_trie.c#L199">199</a>                 return 0;
<a name="L200" href="source/net/ipv4/fib_trie.c#L200">200</a> 
<a name="L201" href="source/net/ipv4/fib_trie.c#L201">201</a>         return <a href="ident?i=index">index</a> &gt;&gt; kv-&gt;<a href="ident?i=pos">pos</a>;
<a name="L202" href="source/net/ipv4/fib_trie.c#L202">202</a> }
<a name="L203" href="source/net/ipv4/fib_trie.c#L203">203</a> 
<a name="L204" href="source/net/ipv4/fib_trie.c#L204">204</a> <b><i>/* To understand this stuff, an understanding of keys and all their bits is</i></b>
<a name="L205" href="source/net/ipv4/fib_trie.c#L205">205</a> <b><i> * necessary. Every node in the trie has a key associated with it, but not</i></b>
<a name="L206" href="source/net/ipv4/fib_trie.c#L206">206</a> <b><i> * all of the bits in that key are significant.</i></b>
<a name="L207" href="source/net/ipv4/fib_trie.c#L207">207</a> <b><i> *</i></b>
<a name="L208" href="source/net/ipv4/fib_trie.c#L208">208</a> <b><i> * Consider a node 'n' and its parent 'tp'.</i></b>
<a name="L209" href="source/net/ipv4/fib_trie.c#L209">209</a> <b><i> *</i></b>
<a name="L210" href="source/net/ipv4/fib_trie.c#L210">210</a> <b><i> * If n is a leaf, every bit in its key is significant. Its presence is</i></b>
<a name="L211" href="source/net/ipv4/fib_trie.c#L211">211</a> <b><i> * necessitated by path compression, since during a tree traversal (when</i></b>
<a name="L212" href="source/net/ipv4/fib_trie.c#L212">212</a> <b><i> * searching for a leaf - unless we are doing an insertion) we will completely</i></b>
<a name="L213" href="source/net/ipv4/fib_trie.c#L213">213</a> <b><i> * ignore all skipped bits we encounter. Thus we need to verify, at the end of</i></b>
<a name="L214" href="source/net/ipv4/fib_trie.c#L214">214</a> <b><i> * a potentially successful search, that we have indeed been walking the</i></b>
<a name="L215" href="source/net/ipv4/fib_trie.c#L215">215</a> <b><i> * correct key path.</i></b>
<a name="L216" href="source/net/ipv4/fib_trie.c#L216">216</a> <b><i> *</i></b>
<a name="L217" href="source/net/ipv4/fib_trie.c#L217">217</a> <b><i> * Note that we can never "miss" the correct key in the tree if present by</i></b>
<a name="L218" href="source/net/ipv4/fib_trie.c#L218">218</a> <b><i> * following the wrong path. Path compression ensures that segments of the key</i></b>
<a name="L219" href="source/net/ipv4/fib_trie.c#L219">219</a> <b><i> * that are the same for all keys with a given prefix are skipped, but the</i></b>
<a name="L220" href="source/net/ipv4/fib_trie.c#L220">220</a> <b><i> * skipped part *is* identical for each node in the subtrie below the skipped</i></b>
<a name="L221" href="source/net/ipv4/fib_trie.c#L221">221</a> <b><i> * bit! trie_insert() in this implementation takes care of that.</i></b>
<a name="L222" href="source/net/ipv4/fib_trie.c#L222">222</a> <b><i> *</i></b>
<a name="L223" href="source/net/ipv4/fib_trie.c#L223">223</a> <b><i> * if n is an internal node - a 'tnode' here, the various parts of its key</i></b>
<a name="L224" href="source/net/ipv4/fib_trie.c#L224">224</a> <b><i> * have many different meanings.</i></b>
<a name="L225" href="source/net/ipv4/fib_trie.c#L225">225</a> <b><i> *</i></b>
<a name="L226" href="source/net/ipv4/fib_trie.c#L226">226</a> <b><i> * Example:</i></b>
<a name="L227" href="source/net/ipv4/fib_trie.c#L227">227</a> <b><i> * _________________________________________________________________</i></b>
<a name="L228" href="source/net/ipv4/fib_trie.c#L228">228</a> <b><i> * | i | i | i | i | i | i | i | N | N | N | S | S | S | S | S | C |</i></b>
<a name="L229" href="source/net/ipv4/fib_trie.c#L229">229</a> <b><i> * -----------------------------------------------------------------</i></b>
<a name="L230" href="source/net/ipv4/fib_trie.c#L230">230</a> <b><i> *  31  30  29  28  27  26  25  24  23  22  21  20  19  18  17  16</i></b>
<a name="L231" href="source/net/ipv4/fib_trie.c#L231">231</a> <b><i> *</i></b>
<a name="L232" href="source/net/ipv4/fib_trie.c#L232">232</a> <b><i> * _________________________________________________________________</i></b>
<a name="L233" href="source/net/ipv4/fib_trie.c#L233">233</a> <b><i> * | C | C | C | u | u | u | u | u | u | u | u | u | u | u | u | u |</i></b>
<a name="L234" href="source/net/ipv4/fib_trie.c#L234">234</a> <b><i> * -----------------------------------------------------------------</i></b>
<a name="L235" href="source/net/ipv4/fib_trie.c#L235">235</a> <b><i> *  15  14  13  12  11  10   9   8   7   6   5   4   3   2   1   0</i></b>
<a name="L236" href="source/net/ipv4/fib_trie.c#L236">236</a> <b><i> *</i></b>
<a name="L237" href="source/net/ipv4/fib_trie.c#L237">237</a> <b><i> * tp-&gt;pos = 22</i></b>
<a name="L238" href="source/net/ipv4/fib_trie.c#L238">238</a> <b><i> * tp-&gt;bits = 3</i></b>
<a name="L239" href="source/net/ipv4/fib_trie.c#L239">239</a> <b><i> * n-&gt;pos = 13</i></b>
<a name="L240" href="source/net/ipv4/fib_trie.c#L240">240</a> <b><i> * n-&gt;bits = 4</i></b>
<a name="L241" href="source/net/ipv4/fib_trie.c#L241">241</a> <b><i> *</i></b>
<a name="L242" href="source/net/ipv4/fib_trie.c#L242">242</a> <b><i> * First, let's just ignore the bits that come before the parent tp, that is</i></b>
<a name="L243" href="source/net/ipv4/fib_trie.c#L243">243</a> <b><i> * the bits from (tp-&gt;pos + tp-&gt;bits) to 31. They are *known* but at this</i></b>
<a name="L244" href="source/net/ipv4/fib_trie.c#L244">244</a> <b><i> * point we do not use them for anything.</i></b>
<a name="L245" href="source/net/ipv4/fib_trie.c#L245">245</a> <b><i> *</i></b>
<a name="L246" href="source/net/ipv4/fib_trie.c#L246">246</a> <b><i> * The bits from (tp-&gt;pos) to (tp-&gt;pos + tp-&gt;bits - 1) - "N", above - are the</i></b>
<a name="L247" href="source/net/ipv4/fib_trie.c#L247">247</a> <b><i> * index into the parent's child array. That is, they will be used to find</i></b>
<a name="L248" href="source/net/ipv4/fib_trie.c#L248">248</a> <b><i> * 'n' among tp's children.</i></b>
<a name="L249" href="source/net/ipv4/fib_trie.c#L249">249</a> <b><i> *</i></b>
<a name="L250" href="source/net/ipv4/fib_trie.c#L250">250</a> <b><i> * The bits from (n-&gt;pos + n-&gt;bits) to (tn-&gt;pos - 1) - "S" - are skipped bits</i></b>
<a name="L251" href="source/net/ipv4/fib_trie.c#L251">251</a> <b><i> * for the node n.</i></b>
<a name="L252" href="source/net/ipv4/fib_trie.c#L252">252</a> <b><i> *</i></b>
<a name="L253" href="source/net/ipv4/fib_trie.c#L253">253</a> <b><i> * All the bits we have seen so far are significant to the node n. The rest</i></b>
<a name="L254" href="source/net/ipv4/fib_trie.c#L254">254</a> <b><i> * of the bits are really not needed or indeed known in n-&gt;key.</i></b>
<a name="L255" href="source/net/ipv4/fib_trie.c#L255">255</a> <b><i> *</i></b>
<a name="L256" href="source/net/ipv4/fib_trie.c#L256">256</a> <b><i> * The bits from (n-&gt;pos) to (n-&gt;pos + n-&gt;bits - 1) - "C" - are the index into</i></b>
<a name="L257" href="source/net/ipv4/fib_trie.c#L257">257</a> <b><i> * n's child array, and will of course be different for each child.</i></b>
<a name="L258" href="source/net/ipv4/fib_trie.c#L258">258</a> <b><i> *</i></b>
<a name="L259" href="source/net/ipv4/fib_trie.c#L259">259</a> <b><i> * The rest of the bits, from 0 to (n-&gt;pos + n-&gt;bits), are completely unknown</i></b>
<a name="L260" href="source/net/ipv4/fib_trie.c#L260">260</a> <b><i> * at this point.</i></b>
<a name="L261" href="source/net/ipv4/fib_trie.c#L261">261</a> <b><i> */</i></b>
<a name="L262" href="source/net/ipv4/fib_trie.c#L262">262</a> 
<a name="L263" href="source/net/ipv4/fib_trie.c#L263">263</a> static const int <a href="ident?i=halve_threshold">halve_threshold</a> = 25;
<a name="L264" href="source/net/ipv4/fib_trie.c#L264">264</a> static const int <a href="ident?i=inflate_threshold">inflate_threshold</a> = 50;
<a name="L265" href="source/net/ipv4/fib_trie.c#L265">265</a> static const int <a href="ident?i=halve_threshold_root">halve_threshold_root</a> = 15;
<a name="L266" href="source/net/ipv4/fib_trie.c#L266">266</a> static const int <a href="ident?i=inflate_threshold_root">inflate_threshold_root</a> = 30;
<a name="L267" href="source/net/ipv4/fib_trie.c#L267">267</a> 
<a name="L268" href="source/net/ipv4/fib_trie.c#L268">268</a> static void <a href="ident?i=__alias_free_mem">__alias_free_mem</a>(struct <a href="ident?i=rcu_head">rcu_head</a> *<a href="ident?i=head">head</a>)
<a name="L269" href="source/net/ipv4/fib_trie.c#L269">269</a> {
<a name="L270" href="source/net/ipv4/fib_trie.c#L270">270</a>         struct <a href="ident?i=fib_alias">fib_alias</a> *fa = <a href="ident?i=container_of">container_of</a>(<a href="ident?i=head">head</a>, struct <a href="ident?i=fib_alias">fib_alias</a>, rcu);
<a name="L271" href="source/net/ipv4/fib_trie.c#L271">271</a>         <a href="ident?i=kmem_cache_free">kmem_cache_free</a>(fn_alias_kmem, fa);
<a name="L272" href="source/net/ipv4/fib_trie.c#L272">272</a> }
<a name="L273" href="source/net/ipv4/fib_trie.c#L273">273</a> 
<a name="L274" href="source/net/ipv4/fib_trie.c#L274">274</a> static inline void <a href="ident?i=alias_free_mem_rcu">alias_free_mem_rcu</a>(struct <a href="ident?i=fib_alias">fib_alias</a> *fa)
<a name="L275" href="source/net/ipv4/fib_trie.c#L275">275</a> {
<a name="L276" href="source/net/ipv4/fib_trie.c#L276">276</a>         <a href="ident?i=call_rcu">call_rcu</a>(&amp;fa-&gt;rcu, <a href="ident?i=__alias_free_mem">__alias_free_mem</a>);
<a name="L277" href="source/net/ipv4/fib_trie.c#L277">277</a> }
<a name="L278" href="source/net/ipv4/fib_trie.c#L278">278</a> 
<a name="L279" href="source/net/ipv4/fib_trie.c#L279">279</a> #define <a href="ident?i=TNODE_KMALLOC_MAX">TNODE_KMALLOC_MAX</a> \
<a name="L280" href="source/net/ipv4/fib_trie.c#L280">280</a>         <a href="ident?i=ilog2">ilog2</a>((<a href="ident?i=PAGE_SIZE">PAGE_SIZE</a> - <a href="ident?i=TNODE_SIZE">TNODE_SIZE</a>(0)) / sizeof(struct <a href="ident?i=key_vector">key_vector</a> *))
<a name="L281" href="source/net/ipv4/fib_trie.c#L281">281</a> #define <a href="ident?i=TNODE_VMALLOC_MAX">TNODE_VMALLOC_MAX</a> \
<a name="L282" href="source/net/ipv4/fib_trie.c#L282">282</a>         <a href="ident?i=ilog2">ilog2</a>((<a href="ident?i=SIZE_MAX">SIZE_MAX</a> - <a href="ident?i=TNODE_SIZE">TNODE_SIZE</a>(0)) / sizeof(struct <a href="ident?i=key_vector">key_vector</a> *))
<a name="L283" href="source/net/ipv4/fib_trie.c#L283">283</a> 
<a name="L284" href="source/net/ipv4/fib_trie.c#L284">284</a> static void <a href="ident?i=__node_free_rcu">__node_free_rcu</a>(struct <a href="ident?i=rcu_head">rcu_head</a> *<a href="ident?i=head">head</a>)
<a name="L285" href="source/net/ipv4/fib_trie.c#L285">285</a> {
<a name="L286" href="source/net/ipv4/fib_trie.c#L286">286</a>         struct <a href="ident?i=tnode">tnode</a> *<a href="ident?i=n">n</a> = <a href="ident?i=container_of">container_of</a>(<a href="ident?i=head">head</a>, struct <a href="ident?i=tnode">tnode</a>, rcu);
<a name="L287" href="source/net/ipv4/fib_trie.c#L287">287</a> 
<a name="L288" href="source/net/ipv4/fib_trie.c#L288">288</a>         if (!<a href="ident?i=n">n</a>-&gt;<a href="ident?i=tn_bits">tn_bits</a>)
<a name="L289" href="source/net/ipv4/fib_trie.c#L289">289</a>                 <a href="ident?i=kmem_cache_free">kmem_cache_free</a>(trie_leaf_kmem, <a href="ident?i=n">n</a>);
<a name="L290" href="source/net/ipv4/fib_trie.c#L290">290</a>         else if (<a href="ident?i=n">n</a>-&gt;<a href="ident?i=tn_bits">tn_bits</a> &lt;= <a href="ident?i=TNODE_KMALLOC_MAX">TNODE_KMALLOC_MAX</a>)
<a name="L291" href="source/net/ipv4/fib_trie.c#L291">291</a>                 <a href="ident?i=kfree">kfree</a>(<a href="ident?i=n">n</a>);
<a name="L292" href="source/net/ipv4/fib_trie.c#L292">292</a>         else
<a name="L293" href="source/net/ipv4/fib_trie.c#L293">293</a>                 <a href="ident?i=vfree">vfree</a>(<a href="ident?i=n">n</a>);
<a name="L294" href="source/net/ipv4/fib_trie.c#L294">294</a> }
<a name="L295" href="source/net/ipv4/fib_trie.c#L295">295</a> 
<a name="L296" href="source/net/ipv4/fib_trie.c#L296">296</a> #define <a href="ident?i=node_free">node_free</a>(<a href="ident?i=n">n</a>) <a href="ident?i=call_rcu">call_rcu</a>(&amp;<a href="ident?i=tn_info">tn_info</a>(<a href="ident?i=n">n</a>)-&gt;rcu, <a href="ident?i=__node_free_rcu">__node_free_rcu</a>)
<a name="L297" href="source/net/ipv4/fib_trie.c#L297">297</a> 
<a name="L298" href="source/net/ipv4/fib_trie.c#L298">298</a> static struct <a href="ident?i=tnode">tnode</a> *<a href="ident?i=tnode_alloc">tnode_alloc</a>(int <a href="ident?i=bits">bits</a>)
<a name="L299" href="source/net/ipv4/fib_trie.c#L299">299</a> {
<a name="L300" href="source/net/ipv4/fib_trie.c#L300">300</a>         <a href="ident?i=size_t">size_t</a> <a href="ident?i=size">size</a>;
<a name="L301" href="source/net/ipv4/fib_trie.c#L301">301</a> 
<a name="L302" href="source/net/ipv4/fib_trie.c#L302">302</a>         <b><i>/* verify bits is within bounds */</i></b>
<a name="L303" href="source/net/ipv4/fib_trie.c#L303">303</a>         if (<a href="ident?i=bits">bits</a> &gt; <a href="ident?i=TNODE_VMALLOC_MAX">TNODE_VMALLOC_MAX</a>)
<a name="L304" href="source/net/ipv4/fib_trie.c#L304">304</a>                 return <a href="ident?i=NULL">NULL</a>;
<a name="L305" href="source/net/ipv4/fib_trie.c#L305">305</a> 
<a name="L306" href="source/net/ipv4/fib_trie.c#L306">306</a>         <b><i>/* determine size and verify it is non-zero and didn't overflow */</i></b>
<a name="L307" href="source/net/ipv4/fib_trie.c#L307">307</a>         <a href="ident?i=size">size</a> = <a href="ident?i=TNODE_SIZE">TNODE_SIZE</a>(1ul &lt;&lt; <a href="ident?i=bits">bits</a>);
<a name="L308" href="source/net/ipv4/fib_trie.c#L308">308</a> 
<a name="L309" href="source/net/ipv4/fib_trie.c#L309">309</a>         if (<a href="ident?i=size">size</a> &lt;= <a href="ident?i=PAGE_SIZE">PAGE_SIZE</a>)
<a name="L310" href="source/net/ipv4/fib_trie.c#L310">310</a>                 return <a href="ident?i=kzalloc">kzalloc</a>(<a href="ident?i=size">size</a>, <a href="ident?i=GFP_KERNEL">GFP_KERNEL</a>);
<a name="L311" href="source/net/ipv4/fib_trie.c#L311">311</a>         else
<a name="L312" href="source/net/ipv4/fib_trie.c#L312">312</a>                 return <a href="ident?i=vzalloc">vzalloc</a>(<a href="ident?i=size">size</a>);
<a name="L313" href="source/net/ipv4/fib_trie.c#L313">313</a> }
<a name="L314" href="source/net/ipv4/fib_trie.c#L314">314</a> 
<a name="L315" href="source/net/ipv4/fib_trie.c#L315">315</a> static inline void <a href="ident?i=empty_child_inc">empty_child_inc</a>(struct <a href="ident?i=key_vector">key_vector</a> *<a href="ident?i=n">n</a>)
<a name="L316" href="source/net/ipv4/fib_trie.c#L316">316</a> {
<a name="L317" href="source/net/ipv4/fib_trie.c#L317">317</a>         ++<a href="ident?i=tn_info">tn_info</a>(<a href="ident?i=n">n</a>)-&gt;empty_children ? : ++<a href="ident?i=tn_info">tn_info</a>(<a href="ident?i=n">n</a>)-&gt;full_children;
<a name="L318" href="source/net/ipv4/fib_trie.c#L318">318</a> }
<a name="L319" href="source/net/ipv4/fib_trie.c#L319">319</a> 
<a name="L320" href="source/net/ipv4/fib_trie.c#L320">320</a> static inline void <a href="ident?i=empty_child_dec">empty_child_dec</a>(struct <a href="ident?i=key_vector">key_vector</a> *<a href="ident?i=n">n</a>)
<a name="L321" href="source/net/ipv4/fib_trie.c#L321">321</a> {
<a name="L322" href="source/net/ipv4/fib_trie.c#L322">322</a>         <a href="ident?i=tn_info">tn_info</a>(<a href="ident?i=n">n</a>)-&gt;empty_children-- ? : <a href="ident?i=tn_info">tn_info</a>(<a href="ident?i=n">n</a>)-&gt;full_children--;
<a name="L323" href="source/net/ipv4/fib_trie.c#L323">323</a> }
<a name="L324" href="source/net/ipv4/fib_trie.c#L324">324</a> 
<a name="L325" href="source/net/ipv4/fib_trie.c#L325">325</a> static struct <a href="ident?i=key_vector">key_vector</a> *<a href="ident?i=leaf_new">leaf_new</a>(<a href="ident?i=t_key">t_key</a> <a href="ident?i=key">key</a>, struct <a href="ident?i=fib_alias">fib_alias</a> *fa)
<a name="L326" href="source/net/ipv4/fib_trie.c#L326">326</a> {
<a name="L327" href="source/net/ipv4/fib_trie.c#L327">327</a>         struct <a href="ident?i=tnode">tnode</a> *kv = <a href="ident?i=kmem_cache_alloc">kmem_cache_alloc</a>(trie_leaf_kmem, <a href="ident?i=GFP_KERNEL">GFP_KERNEL</a>);
<a name="L328" href="source/net/ipv4/fib_trie.c#L328">328</a>         struct <a href="ident?i=key_vector">key_vector</a> *<a href="ident?i=l">l</a> = kv-&gt;kv;
<a name="L329" href="source/net/ipv4/fib_trie.c#L329">329</a> 
<a name="L330" href="source/net/ipv4/fib_trie.c#L330">330</a>         if (!kv)
<a name="L331" href="source/net/ipv4/fib_trie.c#L331">331</a>                 return <a href="ident?i=NULL">NULL</a>;
<a name="L332" href="source/net/ipv4/fib_trie.c#L332">332</a> 
<a name="L333" href="source/net/ipv4/fib_trie.c#L333">333</a>         <b><i>/* initialize key vector */</i></b>
<a name="L334" href="source/net/ipv4/fib_trie.c#L334">334</a>         <a href="ident?i=l">l</a>-&gt;<a href="ident?i=key">key</a> = <a href="ident?i=key">key</a>;
<a name="L335" href="source/net/ipv4/fib_trie.c#L335">335</a>         <a href="ident?i=l">l</a>-&gt;<a href="ident?i=pos">pos</a> = 0;
<a name="L336" href="source/net/ipv4/fib_trie.c#L336">336</a>         <a href="ident?i=l">l</a>-&gt;<a href="ident?i=bits">bits</a> = 0;
<a name="L337" href="source/net/ipv4/fib_trie.c#L337">337</a>         <a href="ident?i=l">l</a>-&gt;slen = fa-&gt;fa_slen;
<a name="L338" href="source/net/ipv4/fib_trie.c#L338">338</a> 
<a name="L339" href="source/net/ipv4/fib_trie.c#L339">339</a>         <b><i>/* link leaf to fib alias */</i></b>
<a name="L340" href="source/net/ipv4/fib_trie.c#L340">340</a>         <a href="ident?i=INIT_HLIST_HEAD">INIT_HLIST_HEAD</a>(&amp;<a href="ident?i=l">l</a>-&gt;leaf);
<a name="L341" href="source/net/ipv4/fib_trie.c#L341">341</a>         <a href="ident?i=hlist_add_head">hlist_add_head</a>(&amp;fa-&gt;fa_list, &amp;<a href="ident?i=l">l</a>-&gt;leaf);
<a name="L342" href="source/net/ipv4/fib_trie.c#L342">342</a> 
<a name="L343" href="source/net/ipv4/fib_trie.c#L343">343</a>         return <a href="ident?i=l">l</a>;
<a name="L344" href="source/net/ipv4/fib_trie.c#L344">344</a> }
<a name="L345" href="source/net/ipv4/fib_trie.c#L345">345</a> 
<a name="L346" href="source/net/ipv4/fib_trie.c#L346">346</a> static struct <a href="ident?i=key_vector">key_vector</a> *<a href="ident?i=tnode_new">tnode_new</a>(<a href="ident?i=t_key">t_key</a> <a href="ident?i=key">key</a>, int <a href="ident?i=pos">pos</a>, int <a href="ident?i=bits">bits</a>)
<a name="L347" href="source/net/ipv4/fib_trie.c#L347">347</a> {
<a name="L348" href="source/net/ipv4/fib_trie.c#L348">348</a>         struct <a href="ident?i=tnode">tnode</a> *<a href="ident?i=tnode">tnode</a> = <a href="ident?i=tnode_alloc">tnode_alloc</a>(<a href="ident?i=bits">bits</a>);
<a name="L349" href="source/net/ipv4/fib_trie.c#L349">349</a>         unsigned int <a href="ident?i=shift">shift</a> = <a href="ident?i=pos">pos</a> + <a href="ident?i=bits">bits</a>;
<a name="L350" href="source/net/ipv4/fib_trie.c#L350">350</a>         struct <a href="ident?i=key_vector">key_vector</a> *tn = <a href="ident?i=tnode">tnode</a>-&gt;kv;
<a name="L351" href="source/net/ipv4/fib_trie.c#L351">351</a> 
<a name="L352" href="source/net/ipv4/fib_trie.c#L352">352</a>         <b><i>/* verify bits and pos their msb bits clear and values are valid */</i></b>
<a name="L353" href="source/net/ipv4/fib_trie.c#L353">353</a>         <a href="ident?i=BUG_ON">BUG_ON</a>(!<a href="ident?i=bits">bits</a> || (<a href="ident?i=shift">shift</a> &gt; <a href="ident?i=KEYLENGTH">KEYLENGTH</a>));
<a name="L354" href="source/net/ipv4/fib_trie.c#L354">354</a> 
<a name="L355" href="source/net/ipv4/fib_trie.c#L355">355</a>         <a href="ident?i=pr_debug">pr_debug</a>(<i>"AT %p s=%zu %zu\n"</i>, <a href="ident?i=tnode">tnode</a>, <a href="ident?i=TNODE_SIZE">TNODE_SIZE</a>(0),
<a name="L356" href="source/net/ipv4/fib_trie.c#L356">356</a>                  sizeof(struct <a href="ident?i=key_vector">key_vector</a> *) &lt;&lt; <a href="ident?i=bits">bits</a>);
<a name="L357" href="source/net/ipv4/fib_trie.c#L357">357</a> 
<a name="L358" href="source/net/ipv4/fib_trie.c#L358">358</a>         if (!<a href="ident?i=tnode">tnode</a>)
<a name="L359" href="source/net/ipv4/fib_trie.c#L359">359</a>                 return <a href="ident?i=NULL">NULL</a>;
<a name="L360" href="source/net/ipv4/fib_trie.c#L360">360</a> 
<a name="L361" href="source/net/ipv4/fib_trie.c#L361">361</a>         if (<a href="ident?i=bits">bits</a> == <a href="ident?i=KEYLENGTH">KEYLENGTH</a>)
<a name="L362" href="source/net/ipv4/fib_trie.c#L362">362</a>                 <a href="ident?i=tnode">tnode</a>-&gt;full_children = 1;
<a name="L363" href="source/net/ipv4/fib_trie.c#L363">363</a>         else
<a name="L364" href="source/net/ipv4/fib_trie.c#L364">364</a>                 <a href="ident?i=tnode">tnode</a>-&gt;empty_children = 1ul &lt;&lt; <a href="ident?i=bits">bits</a>;
<a name="L365" href="source/net/ipv4/fib_trie.c#L365">365</a> 
<a name="L366" href="source/net/ipv4/fib_trie.c#L366">366</a>         tn-&gt;<a href="ident?i=key">key</a> = (<a href="ident?i=shift">shift</a> &lt; <a href="ident?i=KEYLENGTH">KEYLENGTH</a>) ? (<a href="ident?i=key">key</a> &gt;&gt; <a href="ident?i=shift">shift</a>) &lt;&lt; <a href="ident?i=shift">shift</a> : 0;
<a name="L367" href="source/net/ipv4/fib_trie.c#L367">367</a>         tn-&gt;<a href="ident?i=pos">pos</a> = <a href="ident?i=pos">pos</a>;
<a name="L368" href="source/net/ipv4/fib_trie.c#L368">368</a>         tn-&gt;<a href="ident?i=bits">bits</a> = <a href="ident?i=bits">bits</a>;
<a name="L369" href="source/net/ipv4/fib_trie.c#L369">369</a>         tn-&gt;slen = <a href="ident?i=pos">pos</a>;
<a name="L370" href="source/net/ipv4/fib_trie.c#L370">370</a> 
<a name="L371" href="source/net/ipv4/fib_trie.c#L371">371</a>         return tn;
<a name="L372" href="source/net/ipv4/fib_trie.c#L372">372</a> }
<a name="L373" href="source/net/ipv4/fib_trie.c#L373">373</a> 
<a name="L374" href="source/net/ipv4/fib_trie.c#L374">374</a> <b><i>/* Check whether a tnode 'n' is "full", i.e. it is an internal node</i></b>
<a name="L375" href="source/net/ipv4/fib_trie.c#L375">375</a> <b><i> * and no bits are skipped. See discussion in dyntree paper p. 6</i></b>
<a name="L376" href="source/net/ipv4/fib_trie.c#L376">376</a> <b><i> */</i></b>
<a name="L377" href="source/net/ipv4/fib_trie.c#L377">377</a> static inline int <a href="ident?i=tnode_full">tnode_full</a>(struct <a href="ident?i=key_vector">key_vector</a> *tn, struct <a href="ident?i=key_vector">key_vector</a> *<a href="ident?i=n">n</a>)
<a name="L378" href="source/net/ipv4/fib_trie.c#L378">378</a> {
<a name="L379" href="source/net/ipv4/fib_trie.c#L379">379</a>         return <a href="ident?i=n">n</a> &amp;&amp; ((<a href="ident?i=n">n</a>-&gt;<a href="ident?i=pos">pos</a> + <a href="ident?i=n">n</a>-&gt;<a href="ident?i=bits">bits</a>) == tn-&gt;<a href="ident?i=pos">pos</a>) &amp;&amp; <a href="ident?i=IS_TNODE">IS_TNODE</a>(<a href="ident?i=n">n</a>);
<a name="L380" href="source/net/ipv4/fib_trie.c#L380">380</a> }
<a name="L381" href="source/net/ipv4/fib_trie.c#L381">381</a> 
<a name="L382" href="source/net/ipv4/fib_trie.c#L382">382</a> <b><i>/* Add a child at position i overwriting the old value.</i></b>
<a name="L383" href="source/net/ipv4/fib_trie.c#L383">383</a> <b><i> * Update the value of full_children and empty_children.</i></b>
<a name="L384" href="source/net/ipv4/fib_trie.c#L384">384</a> <b><i> */</i></b>
<a name="L385" href="source/net/ipv4/fib_trie.c#L385">385</a> static void <a href="ident?i=put_child">put_child</a>(struct <a href="ident?i=key_vector">key_vector</a> *tn, unsigned long <a href="ident?i=i">i</a>,
<a name="L386" href="source/net/ipv4/fib_trie.c#L386">386</a>                       struct <a href="ident?i=key_vector">key_vector</a> *<a href="ident?i=n">n</a>)
<a name="L387" href="source/net/ipv4/fib_trie.c#L387">387</a> {
<a name="L388" href="source/net/ipv4/fib_trie.c#L388">388</a>         struct <a href="ident?i=key_vector">key_vector</a> *chi = <a href="ident?i=get_child">get_child</a>(tn, <a href="ident?i=i">i</a>);
<a name="L389" href="source/net/ipv4/fib_trie.c#L389">389</a>         int isfull, wasfull;
<a name="L390" href="source/net/ipv4/fib_trie.c#L390">390</a> 
<a name="L391" href="source/net/ipv4/fib_trie.c#L391">391</a>         <a href="ident?i=BUG_ON">BUG_ON</a>(<a href="ident?i=i">i</a> &gt;= <a href="ident?i=child_length">child_length</a>(tn));
<a name="L392" href="source/net/ipv4/fib_trie.c#L392">392</a> 
<a name="L393" href="source/net/ipv4/fib_trie.c#L393">393</a>         <b><i>/* update emptyChildren, overflow into fullChildren */</i></b>
<a name="L394" href="source/net/ipv4/fib_trie.c#L394">394</a>         if (!<a href="ident?i=n">n</a> &amp;&amp; chi)
<a name="L395" href="source/net/ipv4/fib_trie.c#L395">395</a>                 <a href="ident?i=empty_child_inc">empty_child_inc</a>(tn);
<a name="L396" href="source/net/ipv4/fib_trie.c#L396">396</a>         if (<a href="ident?i=n">n</a> &amp;&amp; !chi)
<a name="L397" href="source/net/ipv4/fib_trie.c#L397">397</a>                 <a href="ident?i=empty_child_dec">empty_child_dec</a>(tn);
<a name="L398" href="source/net/ipv4/fib_trie.c#L398">398</a> 
<a name="L399" href="source/net/ipv4/fib_trie.c#L399">399</a>         <b><i>/* update fullChildren */</i></b>
<a name="L400" href="source/net/ipv4/fib_trie.c#L400">400</a>         wasfull = <a href="ident?i=tnode_full">tnode_full</a>(tn, chi);
<a name="L401" href="source/net/ipv4/fib_trie.c#L401">401</a>         isfull = <a href="ident?i=tnode_full">tnode_full</a>(tn, <a href="ident?i=n">n</a>);
<a name="L402" href="source/net/ipv4/fib_trie.c#L402">402</a> 
<a name="L403" href="source/net/ipv4/fib_trie.c#L403">403</a>         if (wasfull &amp;&amp; !isfull)
<a name="L404" href="source/net/ipv4/fib_trie.c#L404">404</a>                 <a href="ident?i=tn_info">tn_info</a>(tn)-&gt;full_children--;
<a name="L405" href="source/net/ipv4/fib_trie.c#L405">405</a>         else if (!wasfull &amp;&amp; isfull)
<a name="L406" href="source/net/ipv4/fib_trie.c#L406">406</a>                 <a href="ident?i=tn_info">tn_info</a>(tn)-&gt;full_children++;
<a name="L407" href="source/net/ipv4/fib_trie.c#L407">407</a> 
<a name="L408" href="source/net/ipv4/fib_trie.c#L408">408</a>         if (<a href="ident?i=n">n</a> &amp;&amp; (tn-&gt;slen &lt; <a href="ident?i=n">n</a>-&gt;slen))
<a name="L409" href="source/net/ipv4/fib_trie.c#L409">409</a>                 tn-&gt;slen = <a href="ident?i=n">n</a>-&gt;slen;
<a name="L410" href="source/net/ipv4/fib_trie.c#L410">410</a> 
<a name="L411" href="source/net/ipv4/fib_trie.c#L411">411</a>         <a href="ident?i=rcu_assign_pointer">rcu_assign_pointer</a>(tn-&gt;<a href="ident?i=tnode">tnode</a>[<a href="ident?i=i">i</a>], <a href="ident?i=n">n</a>);
<a name="L412" href="source/net/ipv4/fib_trie.c#L412">412</a> }
<a name="L413" href="source/net/ipv4/fib_trie.c#L413">413</a> 
<a name="L414" href="source/net/ipv4/fib_trie.c#L414">414</a> static void <a href="ident?i=update_children">update_children</a>(struct <a href="ident?i=key_vector">key_vector</a> *tn)
<a name="L415" href="source/net/ipv4/fib_trie.c#L415">415</a> {
<a name="L416" href="source/net/ipv4/fib_trie.c#L416">416</a>         unsigned long <a href="ident?i=i">i</a>;
<a name="L417" href="source/net/ipv4/fib_trie.c#L417">417</a> 
<a name="L418" href="source/net/ipv4/fib_trie.c#L418">418</a>         <b><i>/* update all of the child parent pointers */</i></b>
<a name="L419" href="source/net/ipv4/fib_trie.c#L419">419</a>         for (<a href="ident?i=i">i</a> = <a href="ident?i=child_length">child_length</a>(tn); <a href="ident?i=i">i</a>;) {
<a name="L420" href="source/net/ipv4/fib_trie.c#L420">420</a>                 struct <a href="ident?i=key_vector">key_vector</a> *<a href="ident?i=inode">inode</a> = <a href="ident?i=get_child">get_child</a>(tn, --<a href="ident?i=i">i</a>);
<a name="L421" href="source/net/ipv4/fib_trie.c#L421">421</a> 
<a name="L422" href="source/net/ipv4/fib_trie.c#L422">422</a>                 if (!<a href="ident?i=inode">inode</a>)
<a name="L423" href="source/net/ipv4/fib_trie.c#L423">423</a>                         continue;
<a name="L424" href="source/net/ipv4/fib_trie.c#L424">424</a> 
<a name="L425" href="source/net/ipv4/fib_trie.c#L425">425</a>                 <b><i>/* Either update the children of a tnode that</i></b>
<a name="L426" href="source/net/ipv4/fib_trie.c#L426">426</a> <b><i>                 * already belongs to us or update the child</i></b>
<a name="L427" href="source/net/ipv4/fib_trie.c#L427">427</a> <b><i>                 * to point to ourselves.</i></b>
<a name="L428" href="source/net/ipv4/fib_trie.c#L428">428</a> <b><i>                 */</i></b>
<a name="L429" href="source/net/ipv4/fib_trie.c#L429">429</a>                 if (<a href="ident?i=node_parent">node_parent</a>(<a href="ident?i=inode">inode</a>) == tn)
<a name="L430" href="source/net/ipv4/fib_trie.c#L430">430</a>                         <a href="ident?i=update_children">update_children</a>(<a href="ident?i=inode">inode</a>);
<a name="L431" href="source/net/ipv4/fib_trie.c#L431">431</a>                 else
<a name="L432" href="source/net/ipv4/fib_trie.c#L432">432</a>                         <a href="ident?i=node_set_parent">node_set_parent</a>(<a href="ident?i=inode">inode</a>, tn);
<a name="L433" href="source/net/ipv4/fib_trie.c#L433">433</a>         }
<a name="L434" href="source/net/ipv4/fib_trie.c#L434">434</a> }
<a name="L435" href="source/net/ipv4/fib_trie.c#L435">435</a> 
<a name="L436" href="source/net/ipv4/fib_trie.c#L436">436</a> static inline void <a href="ident?i=put_child_root">put_child_root</a>(struct <a href="ident?i=key_vector">key_vector</a> *<a href="ident?i=tp">tp</a>, <a href="ident?i=t_key">t_key</a> <a href="ident?i=key">key</a>,
<a name="L437" href="source/net/ipv4/fib_trie.c#L437">437</a>                                   struct <a href="ident?i=key_vector">key_vector</a> *<a href="ident?i=n">n</a>)
<a name="L438" href="source/net/ipv4/fib_trie.c#L438">438</a> {
<a name="L439" href="source/net/ipv4/fib_trie.c#L439">439</a>         if (<a href="ident?i=IS_TRIE">IS_TRIE</a>(<a href="ident?i=tp">tp</a>))
<a name="L440" href="source/net/ipv4/fib_trie.c#L440">440</a>                 <a href="ident?i=rcu_assign_pointer">rcu_assign_pointer</a>(<a href="ident?i=tp">tp</a>-&gt;<a href="ident?i=tnode">tnode</a>[0], <a href="ident?i=n">n</a>);
<a name="L441" href="source/net/ipv4/fib_trie.c#L441">441</a>         else
<a name="L442" href="source/net/ipv4/fib_trie.c#L442">442</a>                 <a href="ident?i=put_child">put_child</a>(<a href="ident?i=tp">tp</a>, <a href="ident?i=get_index">get_index</a>(<a href="ident?i=key">key</a>, <a href="ident?i=tp">tp</a>), <a href="ident?i=n">n</a>);
<a name="L443" href="source/net/ipv4/fib_trie.c#L443">443</a> }
<a name="L444" href="source/net/ipv4/fib_trie.c#L444">444</a> 
<a name="L445" href="source/net/ipv4/fib_trie.c#L445">445</a> static inline void <a href="ident?i=tnode_free_init">tnode_free_init</a>(struct <a href="ident?i=key_vector">key_vector</a> *tn)
<a name="L446" href="source/net/ipv4/fib_trie.c#L446">446</a> {
<a name="L447" href="source/net/ipv4/fib_trie.c#L447">447</a>         <a href="ident?i=tn_info">tn_info</a>(tn)-&gt;rcu.<a href="ident?i=next">next</a> = <a href="ident?i=NULL">NULL</a>;
<a name="L448" href="source/net/ipv4/fib_trie.c#L448">448</a> }
<a name="L449" href="source/net/ipv4/fib_trie.c#L449">449</a> 
<a name="L450" href="source/net/ipv4/fib_trie.c#L450">450</a> static inline void <a href="ident?i=tnode_free_append">tnode_free_append</a>(struct <a href="ident?i=key_vector">key_vector</a> *tn,
<a name="L451" href="source/net/ipv4/fib_trie.c#L451">451</a>                                      struct <a href="ident?i=key_vector">key_vector</a> *<a href="ident?i=n">n</a>)
<a name="L452" href="source/net/ipv4/fib_trie.c#L452">452</a> {
<a name="L453" href="source/net/ipv4/fib_trie.c#L453">453</a>         <a href="ident?i=tn_info">tn_info</a>(<a href="ident?i=n">n</a>)-&gt;rcu.<a href="ident?i=next">next</a> = <a href="ident?i=tn_info">tn_info</a>(tn)-&gt;rcu.<a href="ident?i=next">next</a>;
<a name="L454" href="source/net/ipv4/fib_trie.c#L454">454</a>         <a href="ident?i=tn_info">tn_info</a>(tn)-&gt;rcu.<a href="ident?i=next">next</a> = &amp;<a href="ident?i=tn_info">tn_info</a>(<a href="ident?i=n">n</a>)-&gt;rcu;
<a name="L455" href="source/net/ipv4/fib_trie.c#L455">455</a> }
<a name="L456" href="source/net/ipv4/fib_trie.c#L456">456</a> 
<a name="L457" href="source/net/ipv4/fib_trie.c#L457">457</a> static void <a href="ident?i=tnode_free">tnode_free</a>(struct <a href="ident?i=key_vector">key_vector</a> *tn)
<a name="L458" href="source/net/ipv4/fib_trie.c#L458">458</a> {
<a name="L459" href="source/net/ipv4/fib_trie.c#L459">459</a>         struct <a href="ident?i=callback_head">callback_head</a> *<a href="ident?i=head">head</a> = &amp;<a href="ident?i=tn_info">tn_info</a>(tn)-&gt;rcu;
<a name="L460" href="source/net/ipv4/fib_trie.c#L460">460</a> 
<a name="L461" href="source/net/ipv4/fib_trie.c#L461">461</a>         while (<a href="ident?i=head">head</a>) {
<a name="L462" href="source/net/ipv4/fib_trie.c#L462">462</a>                 <a href="ident?i=head">head</a> = <a href="ident?i=head">head</a>-&gt;<a href="ident?i=next">next</a>;
<a name="L463" href="source/net/ipv4/fib_trie.c#L463">463</a>                 <a href="ident?i=tnode_free_size">tnode_free_size</a> += <a href="ident?i=TNODE_SIZE">TNODE_SIZE</a>(1ul &lt;&lt; tn-&gt;<a href="ident?i=bits">bits</a>);
<a name="L464" href="source/net/ipv4/fib_trie.c#L464">464</a>                 <a href="ident?i=node_free">node_free</a>(tn);
<a name="L465" href="source/net/ipv4/fib_trie.c#L465">465</a> 
<a name="L466" href="source/net/ipv4/fib_trie.c#L466">466</a>                 tn = <a href="ident?i=container_of">container_of</a>(<a href="ident?i=head">head</a>, struct <a href="ident?i=tnode">tnode</a>, rcu)-&gt;kv;
<a name="L467" href="source/net/ipv4/fib_trie.c#L467">467</a>         }
<a name="L468" href="source/net/ipv4/fib_trie.c#L468">468</a> 
<a name="L469" href="source/net/ipv4/fib_trie.c#L469">469</a>         if (<a href="ident?i=tnode_free_size">tnode_free_size</a> &gt;= <a href="ident?i=PAGE_SIZE">PAGE_SIZE</a> * <a href="ident?i=sync_pages">sync_pages</a>) {
<a name="L470" href="source/net/ipv4/fib_trie.c#L470">470</a>                 <a href="ident?i=tnode_free_size">tnode_free_size</a> = 0;
<a name="L471" href="source/net/ipv4/fib_trie.c#L471">471</a>                 <a href="ident?i=synchronize_rcu">synchronize_rcu</a>();
<a name="L472" href="source/net/ipv4/fib_trie.c#L472">472</a>         }
<a name="L473" href="source/net/ipv4/fib_trie.c#L473">473</a> }
<a name="L474" href="source/net/ipv4/fib_trie.c#L474">474</a> 
<a name="L475" href="source/net/ipv4/fib_trie.c#L475">475</a> static struct <a href="ident?i=key_vector">key_vector</a> *<a href="ident?i=replace">replace</a>(struct <a href="ident?i=trie">trie</a> *<a href="ident?i=t">t</a>,
<a name="L476" href="source/net/ipv4/fib_trie.c#L476">476</a>                                   struct <a href="ident?i=key_vector">key_vector</a> *oldtnode,
<a name="L477" href="source/net/ipv4/fib_trie.c#L477">477</a>                                   struct <a href="ident?i=key_vector">key_vector</a> *tn)
<a name="L478" href="source/net/ipv4/fib_trie.c#L478">478</a> {
<a name="L479" href="source/net/ipv4/fib_trie.c#L479">479</a>         struct <a href="ident?i=key_vector">key_vector</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=node_parent">node_parent</a>(oldtnode);
<a name="L480" href="source/net/ipv4/fib_trie.c#L480">480</a>         unsigned long <a href="ident?i=i">i</a>;
<a name="L481" href="source/net/ipv4/fib_trie.c#L481">481</a> 
<a name="L482" href="source/net/ipv4/fib_trie.c#L482">482</a>         <b><i>/* setup the parent pointer out of and back into this node */</i></b>
<a name="L483" href="source/net/ipv4/fib_trie.c#L483">483</a>         <a href="ident?i=NODE_INIT_PARENT">NODE_INIT_PARENT</a>(tn, <a href="ident?i=tp">tp</a>);
<a name="L484" href="source/net/ipv4/fib_trie.c#L484">484</a>         <a href="ident?i=put_child_root">put_child_root</a>(<a href="ident?i=tp">tp</a>, tn-&gt;<a href="ident?i=key">key</a>, tn);
<a name="L485" href="source/net/ipv4/fib_trie.c#L485">485</a> 
<a name="L486" href="source/net/ipv4/fib_trie.c#L486">486</a>         <b><i>/* update all of the child parent pointers */</i></b>
<a name="L487" href="source/net/ipv4/fib_trie.c#L487">487</a>         <a href="ident?i=update_children">update_children</a>(tn);
<a name="L488" href="source/net/ipv4/fib_trie.c#L488">488</a> 
<a name="L489" href="source/net/ipv4/fib_trie.c#L489">489</a>         <b><i>/* all pointers should be clean so we are done */</i></b>
<a name="L490" href="source/net/ipv4/fib_trie.c#L490">490</a>         <a href="ident?i=tnode_free">tnode_free</a>(oldtnode);
<a name="L491" href="source/net/ipv4/fib_trie.c#L491">491</a> 
<a name="L492" href="source/net/ipv4/fib_trie.c#L492">492</a>         <b><i>/* resize children now that oldtnode is freed */</i></b>
<a name="L493" href="source/net/ipv4/fib_trie.c#L493">493</a>         for (<a href="ident?i=i">i</a> = <a href="ident?i=child_length">child_length</a>(tn); <a href="ident?i=i">i</a>;) {
<a name="L494" href="source/net/ipv4/fib_trie.c#L494">494</a>                 struct <a href="ident?i=key_vector">key_vector</a> *<a href="ident?i=inode">inode</a> = <a href="ident?i=get_child">get_child</a>(tn, --<a href="ident?i=i">i</a>);
<a name="L495" href="source/net/ipv4/fib_trie.c#L495">495</a> 
<a name="L496" href="source/net/ipv4/fib_trie.c#L496">496</a>                 <b><i>/* resize child node */</i></b>
<a name="L497" href="source/net/ipv4/fib_trie.c#L497">497</a>                 if (<a href="ident?i=tnode_full">tnode_full</a>(tn, <a href="ident?i=inode">inode</a>))
<a name="L498" href="source/net/ipv4/fib_trie.c#L498">498</a>                         tn = <a href="ident?i=resize">resize</a>(<a href="ident?i=t">t</a>, <a href="ident?i=inode">inode</a>);
<a name="L499" href="source/net/ipv4/fib_trie.c#L499">499</a>         }
<a name="L500" href="source/net/ipv4/fib_trie.c#L500">500</a> 
<a name="L501" href="source/net/ipv4/fib_trie.c#L501">501</a>         return <a href="ident?i=tp">tp</a>;
<a name="L502" href="source/net/ipv4/fib_trie.c#L502">502</a> }
<a name="L503" href="source/net/ipv4/fib_trie.c#L503">503</a> 
<a name="L504" href="source/net/ipv4/fib_trie.c#L504">504</a> static struct <a href="ident?i=key_vector">key_vector</a> *<a href="ident?i=inflate">inflate</a>(struct <a href="ident?i=trie">trie</a> *<a href="ident?i=t">t</a>,
<a name="L505" href="source/net/ipv4/fib_trie.c#L505">505</a>                                   struct <a href="ident?i=key_vector">key_vector</a> *oldtnode)
<a name="L506" href="source/net/ipv4/fib_trie.c#L506">506</a> {
<a name="L507" href="source/net/ipv4/fib_trie.c#L507">507</a>         struct <a href="ident?i=key_vector">key_vector</a> *tn;
<a name="L508" href="source/net/ipv4/fib_trie.c#L508">508</a>         unsigned long <a href="ident?i=i">i</a>;
<a name="L509" href="source/net/ipv4/fib_trie.c#L509">509</a>         <a href="ident?i=t_key">t_key</a> <a href="ident?i=m">m</a>;
<a name="L510" href="source/net/ipv4/fib_trie.c#L510">510</a> 
<a name="L511" href="source/net/ipv4/fib_trie.c#L511">511</a>         <a href="ident?i=pr_debug">pr_debug</a>(<i>"In inflate\n"</i>);
<a name="L512" href="source/net/ipv4/fib_trie.c#L512">512</a> 
<a name="L513" href="source/net/ipv4/fib_trie.c#L513">513</a>         tn = <a href="ident?i=tnode_new">tnode_new</a>(oldtnode-&gt;<a href="ident?i=key">key</a>, oldtnode-&gt;<a href="ident?i=pos">pos</a> - 1, oldtnode-&gt;<a href="ident?i=bits">bits</a> + 1);
<a name="L514" href="source/net/ipv4/fib_trie.c#L514">514</a>         if (!tn)
<a name="L515" href="source/net/ipv4/fib_trie.c#L515">515</a>                 goto notnode;
<a name="L516" href="source/net/ipv4/fib_trie.c#L516">516</a> 
<a name="L517" href="source/net/ipv4/fib_trie.c#L517">517</a>         <b><i>/* prepare oldtnode to be freed */</i></b>
<a name="L518" href="source/net/ipv4/fib_trie.c#L518">518</a>         <a href="ident?i=tnode_free_init">tnode_free_init</a>(oldtnode);
<a name="L519" href="source/net/ipv4/fib_trie.c#L519">519</a> 
<a name="L520" href="source/net/ipv4/fib_trie.c#L520">520</a>         <b><i>/* Assemble all of the pointers in our cluster, in this case that</i></b>
<a name="L521" href="source/net/ipv4/fib_trie.c#L521">521</a> <b><i>         * represents all of the pointers out of our allocated nodes that</i></b>
<a name="L522" href="source/net/ipv4/fib_trie.c#L522">522</a> <b><i>         * point to existing tnodes and the links between our allocated</i></b>
<a name="L523" href="source/net/ipv4/fib_trie.c#L523">523</a> <b><i>         * nodes.</i></b>
<a name="L524" href="source/net/ipv4/fib_trie.c#L524">524</a> <b><i>         */</i></b>
<a name="L525" href="source/net/ipv4/fib_trie.c#L525">525</a>         for (<a href="ident?i=i">i</a> = <a href="ident?i=child_length">child_length</a>(oldtnode), <a href="ident?i=m">m</a> = 1u &lt;&lt; tn-&gt;<a href="ident?i=pos">pos</a>; <a href="ident?i=i">i</a>;) {
<a name="L526" href="source/net/ipv4/fib_trie.c#L526">526</a>                 struct <a href="ident?i=key_vector">key_vector</a> *<a href="ident?i=inode">inode</a> = <a href="ident?i=get_child">get_child</a>(oldtnode, --<a href="ident?i=i">i</a>);
<a name="L527" href="source/net/ipv4/fib_trie.c#L527">527</a>                 struct <a href="ident?i=key_vector">key_vector</a> *node0, *node1;
<a name="L528" href="source/net/ipv4/fib_trie.c#L528">528</a>                 unsigned long j, k;
<a name="L529" href="source/net/ipv4/fib_trie.c#L529">529</a> 
<a name="L530" href="source/net/ipv4/fib_trie.c#L530">530</a>                 <b><i>/* An empty child */</i></b>
<a name="L531" href="source/net/ipv4/fib_trie.c#L531">531</a>                 if (!<a href="ident?i=inode">inode</a>)
<a name="L532" href="source/net/ipv4/fib_trie.c#L532">532</a>                         continue;
<a name="L533" href="source/net/ipv4/fib_trie.c#L533">533</a> 
<a name="L534" href="source/net/ipv4/fib_trie.c#L534">534</a>                 <b><i>/* A leaf or an internal node with skipped bits */</i></b>
<a name="L535" href="source/net/ipv4/fib_trie.c#L535">535</a>                 if (!<a href="ident?i=tnode_full">tnode_full</a>(oldtnode, <a href="ident?i=inode">inode</a>)) {
<a name="L536" href="source/net/ipv4/fib_trie.c#L536">536</a>                         <a href="ident?i=put_child">put_child</a>(tn, <a href="ident?i=get_index">get_index</a>(<a href="ident?i=inode">inode</a>-&gt;<a href="ident?i=key">key</a>, tn), <a href="ident?i=inode">inode</a>);
<a name="L537" href="source/net/ipv4/fib_trie.c#L537">537</a>                         continue;
<a name="L538" href="source/net/ipv4/fib_trie.c#L538">538</a>                 }
<a name="L539" href="source/net/ipv4/fib_trie.c#L539">539</a> 
<a name="L540" href="source/net/ipv4/fib_trie.c#L540">540</a>                 <b><i>/* drop the node in the old tnode free list */</i></b>
<a name="L541" href="source/net/ipv4/fib_trie.c#L541">541</a>                 <a href="ident?i=tnode_free_append">tnode_free_append</a>(oldtnode, <a href="ident?i=inode">inode</a>);
<a name="L542" href="source/net/ipv4/fib_trie.c#L542">542</a> 
<a name="L543" href="source/net/ipv4/fib_trie.c#L543">543</a>                 <b><i>/* An internal node with two children */</i></b>
<a name="L544" href="source/net/ipv4/fib_trie.c#L544">544</a>                 if (<a href="ident?i=inode">inode</a>-&gt;<a href="ident?i=bits">bits</a> == 1) {
<a name="L545" href="source/net/ipv4/fib_trie.c#L545">545</a>                         <a href="ident?i=put_child">put_child</a>(tn, 2 * <a href="ident?i=i">i</a> + 1, <a href="ident?i=get_child">get_child</a>(<a href="ident?i=inode">inode</a>, 1));
<a name="L546" href="source/net/ipv4/fib_trie.c#L546">546</a>                         <a href="ident?i=put_child">put_child</a>(tn, 2 * <a href="ident?i=i">i</a>, <a href="ident?i=get_child">get_child</a>(<a href="ident?i=inode">inode</a>, 0));
<a name="L547" href="source/net/ipv4/fib_trie.c#L547">547</a>                         continue;
<a name="L548" href="source/net/ipv4/fib_trie.c#L548">548</a>                 }
<a name="L549" href="source/net/ipv4/fib_trie.c#L549">549</a> 
<a name="L550" href="source/net/ipv4/fib_trie.c#L550">550</a>                 <b><i>/* We will replace this node 'inode' with two new</i></b>
<a name="L551" href="source/net/ipv4/fib_trie.c#L551">551</a> <b><i>                 * ones, 'node0' and 'node1', each with half of the</i></b>
<a name="L552" href="source/net/ipv4/fib_trie.c#L552">552</a> <b><i>                 * original children. The two new nodes will have</i></b>
<a name="L553" href="source/net/ipv4/fib_trie.c#L553">553</a> <b><i>                 * a position one bit further down the key and this</i></b>
<a name="L554" href="source/net/ipv4/fib_trie.c#L554">554</a> <b><i>                 * means that the "significant" part of their keys</i></b>
<a name="L555" href="source/net/ipv4/fib_trie.c#L555">555</a> <b><i>                 * (see the discussion near the top of this file)</i></b>
<a name="L556" href="source/net/ipv4/fib_trie.c#L556">556</a> <b><i>                 * will differ by one bit, which will be "" in</i></b>
<a name="L557" href="source/net/ipv4/fib_trie.c#L557">557</a> <b><i>                 * node0's key and "1" in node1's key. Since we are</i></b>
<a name="L558" href="source/net/ipv4/fib_trie.c#L558">558</a> <b><i>                 * moving the key position by one step, the bit that</i></b>
<a name="L559" href="source/net/ipv4/fib_trie.c#L559">559</a> <b><i>                 * we are moving away from - the bit at position</i></b>
<a name="L560" href="source/net/ipv4/fib_trie.c#L560">560</a> <b><i>                 * (tn-&gt;pos) - is the one that will differ between</i></b>
<a name="L561" href="source/net/ipv4/fib_trie.c#L561">561</a> <b><i>                 * node0 and node1. So... we synthesize that bit in the</i></b>
<a name="L562" href="source/net/ipv4/fib_trie.c#L562">562</a> <b><i>                 * two new keys.</i></b>
<a name="L563" href="source/net/ipv4/fib_trie.c#L563">563</a> <b><i>                 */</i></b>
<a name="L564" href="source/net/ipv4/fib_trie.c#L564">564</a>                 node1 = <a href="ident?i=tnode_new">tnode_new</a>(<a href="ident?i=inode">inode</a>-&gt;<a href="ident?i=key">key</a> | <a href="ident?i=m">m</a>, <a href="ident?i=inode">inode</a>-&gt;<a href="ident?i=pos">pos</a>, <a href="ident?i=inode">inode</a>-&gt;<a href="ident?i=bits">bits</a> - 1);
<a name="L565" href="source/net/ipv4/fib_trie.c#L565">565</a>                 if (!node1)
<a name="L566" href="source/net/ipv4/fib_trie.c#L566">566</a>                         goto nomem;
<a name="L567" href="source/net/ipv4/fib_trie.c#L567">567</a>                 node0 = <a href="ident?i=tnode_new">tnode_new</a>(<a href="ident?i=inode">inode</a>-&gt;<a href="ident?i=key">key</a>, <a href="ident?i=inode">inode</a>-&gt;<a href="ident?i=pos">pos</a>, <a href="ident?i=inode">inode</a>-&gt;<a href="ident?i=bits">bits</a> - 1);
<a name="L568" href="source/net/ipv4/fib_trie.c#L568">568</a> 
<a name="L569" href="source/net/ipv4/fib_trie.c#L569">569</a>                 <a href="ident?i=tnode_free_append">tnode_free_append</a>(tn, node1);
<a name="L570" href="source/net/ipv4/fib_trie.c#L570">570</a>                 if (!node0)
<a name="L571" href="source/net/ipv4/fib_trie.c#L571">571</a>                         goto nomem;
<a name="L572" href="source/net/ipv4/fib_trie.c#L572">572</a>                 <a href="ident?i=tnode_free_append">tnode_free_append</a>(tn, node0);
<a name="L573" href="source/net/ipv4/fib_trie.c#L573">573</a> 
<a name="L574" href="source/net/ipv4/fib_trie.c#L574">574</a>                 <b><i>/* populate child pointers in new nodes */</i></b>
<a name="L575" href="source/net/ipv4/fib_trie.c#L575">575</a>                 for (k = <a href="ident?i=child_length">child_length</a>(<a href="ident?i=inode">inode</a>), j = k / 2; j;) {
<a name="L576" href="source/net/ipv4/fib_trie.c#L576">576</a>                         <a href="ident?i=put_child">put_child</a>(node1, --j, <a href="ident?i=get_child">get_child</a>(<a href="ident?i=inode">inode</a>, --k));
<a name="L577" href="source/net/ipv4/fib_trie.c#L577">577</a>                         <a href="ident?i=put_child">put_child</a>(node0, j, <a href="ident?i=get_child">get_child</a>(<a href="ident?i=inode">inode</a>, j));
<a name="L578" href="source/net/ipv4/fib_trie.c#L578">578</a>                         <a href="ident?i=put_child">put_child</a>(node1, --j, <a href="ident?i=get_child">get_child</a>(<a href="ident?i=inode">inode</a>, --k));
<a name="L579" href="source/net/ipv4/fib_trie.c#L579">579</a>                         <a href="ident?i=put_child">put_child</a>(node0, j, <a href="ident?i=get_child">get_child</a>(<a href="ident?i=inode">inode</a>, j));
<a name="L580" href="source/net/ipv4/fib_trie.c#L580">580</a>                 }
<a name="L581" href="source/net/ipv4/fib_trie.c#L581">581</a> 
<a name="L582" href="source/net/ipv4/fib_trie.c#L582">582</a>                 <b><i>/* link new nodes to parent */</i></b>
<a name="L583" href="source/net/ipv4/fib_trie.c#L583">583</a>                 <a href="ident?i=NODE_INIT_PARENT">NODE_INIT_PARENT</a>(node1, tn);
<a name="L584" href="source/net/ipv4/fib_trie.c#L584">584</a>                 <a href="ident?i=NODE_INIT_PARENT">NODE_INIT_PARENT</a>(node0, tn);
<a name="L585" href="source/net/ipv4/fib_trie.c#L585">585</a> 
<a name="L586" href="source/net/ipv4/fib_trie.c#L586">586</a>                 <b><i>/* link parent to nodes */</i></b>
<a name="L587" href="source/net/ipv4/fib_trie.c#L587">587</a>                 <a href="ident?i=put_child">put_child</a>(tn, 2 * <a href="ident?i=i">i</a> + 1, node1);
<a name="L588" href="source/net/ipv4/fib_trie.c#L588">588</a>                 <a href="ident?i=put_child">put_child</a>(tn, 2 * <a href="ident?i=i">i</a>, node0);
<a name="L589" href="source/net/ipv4/fib_trie.c#L589">589</a>         }
<a name="L590" href="source/net/ipv4/fib_trie.c#L590">590</a> 
<a name="L591" href="source/net/ipv4/fib_trie.c#L591">591</a>         <b><i>/* setup the parent pointers into and out of this node */</i></b>
<a name="L592" href="source/net/ipv4/fib_trie.c#L592">592</a>         return <a href="ident?i=replace">replace</a>(<a href="ident?i=t">t</a>, oldtnode, tn);
<a name="L593" href="source/net/ipv4/fib_trie.c#L593">593</a> nomem:
<a name="L594" href="source/net/ipv4/fib_trie.c#L594">594</a>         <b><i>/* all pointers should be clean so we are done */</i></b>
<a name="L595" href="source/net/ipv4/fib_trie.c#L595">595</a>         <a href="ident?i=tnode_free">tnode_free</a>(tn);
<a name="L596" href="source/net/ipv4/fib_trie.c#L596">596</a> notnode:
<a name="L597" href="source/net/ipv4/fib_trie.c#L597">597</a>         return <a href="ident?i=NULL">NULL</a>;
<a name="L598" href="source/net/ipv4/fib_trie.c#L598">598</a> }
<a name="L599" href="source/net/ipv4/fib_trie.c#L599">599</a> 
<a name="L600" href="source/net/ipv4/fib_trie.c#L600">600</a> static struct <a href="ident?i=key_vector">key_vector</a> *<a href="ident?i=halve">halve</a>(struct <a href="ident?i=trie">trie</a> *<a href="ident?i=t">t</a>,
<a name="L601" href="source/net/ipv4/fib_trie.c#L601">601</a>                                 struct <a href="ident?i=key_vector">key_vector</a> *oldtnode)
<a name="L602" href="source/net/ipv4/fib_trie.c#L602">602</a> {
<a name="L603" href="source/net/ipv4/fib_trie.c#L603">603</a>         struct <a href="ident?i=key_vector">key_vector</a> *tn;
<a name="L604" href="source/net/ipv4/fib_trie.c#L604">604</a>         unsigned long <a href="ident?i=i">i</a>;
<a name="L605" href="source/net/ipv4/fib_trie.c#L605">605</a> 
<a name="L606" href="source/net/ipv4/fib_trie.c#L606">606</a>         <a href="ident?i=pr_debug">pr_debug</a>(<i>"In halve\n"</i>);
<a name="L607" href="source/net/ipv4/fib_trie.c#L607">607</a> 
<a name="L608" href="source/net/ipv4/fib_trie.c#L608">608</a>         tn = <a href="ident?i=tnode_new">tnode_new</a>(oldtnode-&gt;<a href="ident?i=key">key</a>, oldtnode-&gt;<a href="ident?i=pos">pos</a> + 1, oldtnode-&gt;<a href="ident?i=bits">bits</a> - 1);
<a name="L609" href="source/net/ipv4/fib_trie.c#L609">609</a>         if (!tn)
<a name="L610" href="source/net/ipv4/fib_trie.c#L610">610</a>                 goto notnode;
<a name="L611" href="source/net/ipv4/fib_trie.c#L611">611</a> 
<a name="L612" href="source/net/ipv4/fib_trie.c#L612">612</a>         <b><i>/* prepare oldtnode to be freed */</i></b>
<a name="L613" href="source/net/ipv4/fib_trie.c#L613">613</a>         <a href="ident?i=tnode_free_init">tnode_free_init</a>(oldtnode);
<a name="L614" href="source/net/ipv4/fib_trie.c#L614">614</a> 
<a name="L615" href="source/net/ipv4/fib_trie.c#L615">615</a>         <b><i>/* Assemble all of the pointers in our cluster, in this case that</i></b>
<a name="L616" href="source/net/ipv4/fib_trie.c#L616">616</a> <b><i>         * represents all of the pointers out of our allocated nodes that</i></b>
<a name="L617" href="source/net/ipv4/fib_trie.c#L617">617</a> <b><i>         * point to existing tnodes and the links between our allocated</i></b>
<a name="L618" href="source/net/ipv4/fib_trie.c#L618">618</a> <b><i>         * nodes.</i></b>
<a name="L619" href="source/net/ipv4/fib_trie.c#L619">619</a> <b><i>         */</i></b>
<a name="L620" href="source/net/ipv4/fib_trie.c#L620">620</a>         for (<a href="ident?i=i">i</a> = <a href="ident?i=child_length">child_length</a>(oldtnode); <a href="ident?i=i">i</a>;) {
<a name="L621" href="source/net/ipv4/fib_trie.c#L621">621</a>                 struct <a href="ident?i=key_vector">key_vector</a> *node1 = <a href="ident?i=get_child">get_child</a>(oldtnode, --<a href="ident?i=i">i</a>);
<a name="L622" href="source/net/ipv4/fib_trie.c#L622">622</a>                 struct <a href="ident?i=key_vector">key_vector</a> *node0 = <a href="ident?i=get_child">get_child</a>(oldtnode, --<a href="ident?i=i">i</a>);
<a name="L623" href="source/net/ipv4/fib_trie.c#L623">623</a>                 struct <a href="ident?i=key_vector">key_vector</a> *<a href="ident?i=inode">inode</a>;
<a name="L624" href="source/net/ipv4/fib_trie.c#L624">624</a> 
<a name="L625" href="source/net/ipv4/fib_trie.c#L625">625</a>                 <b><i>/* At least one of the children is empty */</i></b>
<a name="L626" href="source/net/ipv4/fib_trie.c#L626">626</a>                 if (!node1 || !node0) {
<a name="L627" href="source/net/ipv4/fib_trie.c#L627">627</a>                         <a href="ident?i=put_child">put_child</a>(tn, <a href="ident?i=i">i</a> / 2, node1 ? : node0);
<a name="L628" href="source/net/ipv4/fib_trie.c#L628">628</a>                         continue;
<a name="L629" href="source/net/ipv4/fib_trie.c#L629">629</a>                 }
<a name="L630" href="source/net/ipv4/fib_trie.c#L630">630</a> 
<a name="L631" href="source/net/ipv4/fib_trie.c#L631">631</a>                 <b><i>/* Two nonempty children */</i></b>
<a name="L632" href="source/net/ipv4/fib_trie.c#L632">632</a>                 <a href="ident?i=inode">inode</a> = <a href="ident?i=tnode_new">tnode_new</a>(node0-&gt;<a href="ident?i=key">key</a>, oldtnode-&gt;<a href="ident?i=pos">pos</a>, 1);
<a name="L633" href="source/net/ipv4/fib_trie.c#L633">633</a>                 if (!<a href="ident?i=inode">inode</a>)
<a name="L634" href="source/net/ipv4/fib_trie.c#L634">634</a>                         goto nomem;
<a name="L635" href="source/net/ipv4/fib_trie.c#L635">635</a>                 <a href="ident?i=tnode_free_append">tnode_free_append</a>(tn, <a href="ident?i=inode">inode</a>);
<a name="L636" href="source/net/ipv4/fib_trie.c#L636">636</a> 
<a name="L637" href="source/net/ipv4/fib_trie.c#L637">637</a>                 <b><i>/* initialize pointers out of node */</i></b>
<a name="L638" href="source/net/ipv4/fib_trie.c#L638">638</a>                 <a href="ident?i=put_child">put_child</a>(<a href="ident?i=inode">inode</a>, 1, node1);
<a name="L639" href="source/net/ipv4/fib_trie.c#L639">639</a>                 <a href="ident?i=put_child">put_child</a>(<a href="ident?i=inode">inode</a>, 0, node0);
<a name="L640" href="source/net/ipv4/fib_trie.c#L640">640</a>                 <a href="ident?i=NODE_INIT_PARENT">NODE_INIT_PARENT</a>(<a href="ident?i=inode">inode</a>, tn);
<a name="L641" href="source/net/ipv4/fib_trie.c#L641">641</a> 
<a name="L642" href="source/net/ipv4/fib_trie.c#L642">642</a>                 <b><i>/* link parent to node */</i></b>
<a name="L643" href="source/net/ipv4/fib_trie.c#L643">643</a>                 <a href="ident?i=put_child">put_child</a>(tn, <a href="ident?i=i">i</a> / 2, <a href="ident?i=inode">inode</a>);
<a name="L644" href="source/net/ipv4/fib_trie.c#L644">644</a>         }
<a name="L645" href="source/net/ipv4/fib_trie.c#L645">645</a> 
<a name="L646" href="source/net/ipv4/fib_trie.c#L646">646</a>         <b><i>/* setup the parent pointers into and out of this node */</i></b>
<a name="L647" href="source/net/ipv4/fib_trie.c#L647">647</a>         return <a href="ident?i=replace">replace</a>(<a href="ident?i=t">t</a>, oldtnode, tn);
<a name="L648" href="source/net/ipv4/fib_trie.c#L648">648</a> nomem:
<a name="L649" href="source/net/ipv4/fib_trie.c#L649">649</a>         <b><i>/* all pointers should be clean so we are done */</i></b>
<a name="L650" href="source/net/ipv4/fib_trie.c#L650">650</a>         <a href="ident?i=tnode_free">tnode_free</a>(tn);
<a name="L651" href="source/net/ipv4/fib_trie.c#L651">651</a> notnode:
<a name="L652" href="source/net/ipv4/fib_trie.c#L652">652</a>         return <a href="ident?i=NULL">NULL</a>;
<a name="L653" href="source/net/ipv4/fib_trie.c#L653">653</a> }
<a name="L654" href="source/net/ipv4/fib_trie.c#L654">654</a> 
<a name="L655" href="source/net/ipv4/fib_trie.c#L655">655</a> static struct <a href="ident?i=key_vector">key_vector</a> *<a href="ident?i=collapse">collapse</a>(struct <a href="ident?i=trie">trie</a> *<a href="ident?i=t">t</a>,
<a name="L656" href="source/net/ipv4/fib_trie.c#L656">656</a>                                    struct <a href="ident?i=key_vector">key_vector</a> *oldtnode)
<a name="L657" href="source/net/ipv4/fib_trie.c#L657">657</a> {
<a name="L658" href="source/net/ipv4/fib_trie.c#L658">658</a>         struct <a href="ident?i=key_vector">key_vector</a> *<a href="ident?i=n">n</a>, *<a href="ident?i=tp">tp</a>;
<a name="L659" href="source/net/ipv4/fib_trie.c#L659">659</a>         unsigned long <a href="ident?i=i">i</a>;
<a name="L660" href="source/net/ipv4/fib_trie.c#L660">660</a> 
<a name="L661" href="source/net/ipv4/fib_trie.c#L661">661</a>         <b><i>/* scan the tnode looking for that one child that might still exist */</i></b>
<a name="L662" href="source/net/ipv4/fib_trie.c#L662">662</a>         for (<a href="ident?i=n">n</a> = <a href="ident?i=NULL">NULL</a>, <a href="ident?i=i">i</a> = <a href="ident?i=child_length">child_length</a>(oldtnode); !<a href="ident?i=n">n</a> &amp;&amp; <a href="ident?i=i">i</a>;)
<a name="L663" href="source/net/ipv4/fib_trie.c#L663">663</a>                 <a href="ident?i=n">n</a> = <a href="ident?i=get_child">get_child</a>(oldtnode, --<a href="ident?i=i">i</a>);
<a name="L664" href="source/net/ipv4/fib_trie.c#L664">664</a> 
<a name="L665" href="source/net/ipv4/fib_trie.c#L665">665</a>         <b><i>/* compress one level */</i></b>
<a name="L666" href="source/net/ipv4/fib_trie.c#L666">666</a>         <a href="ident?i=tp">tp</a> = <a href="ident?i=node_parent">node_parent</a>(oldtnode);
<a name="L667" href="source/net/ipv4/fib_trie.c#L667">667</a>         <a href="ident?i=put_child_root">put_child_root</a>(<a href="ident?i=tp">tp</a>, oldtnode-&gt;<a href="ident?i=key">key</a>, <a href="ident?i=n">n</a>);
<a name="L668" href="source/net/ipv4/fib_trie.c#L668">668</a>         <a href="ident?i=node_set_parent">node_set_parent</a>(<a href="ident?i=n">n</a>, <a href="ident?i=tp">tp</a>);
<a name="L669" href="source/net/ipv4/fib_trie.c#L669">669</a> 
<a name="L670" href="source/net/ipv4/fib_trie.c#L670">670</a>         <b><i>/* drop dead node */</i></b>
<a name="L671" href="source/net/ipv4/fib_trie.c#L671">671</a>         <a href="ident?i=node_free">node_free</a>(oldtnode);
<a name="L672" href="source/net/ipv4/fib_trie.c#L672">672</a> 
<a name="L673" href="source/net/ipv4/fib_trie.c#L673">673</a>         return <a href="ident?i=tp">tp</a>;
<a name="L674" href="source/net/ipv4/fib_trie.c#L674">674</a> }
<a name="L675" href="source/net/ipv4/fib_trie.c#L675">675</a> 
<a name="L676" href="source/net/ipv4/fib_trie.c#L676">676</a> static unsigned char <a href="ident?i=update_suffix">update_suffix</a>(struct <a href="ident?i=key_vector">key_vector</a> *tn)
<a name="L677" href="source/net/ipv4/fib_trie.c#L677">677</a> {
<a name="L678" href="source/net/ipv4/fib_trie.c#L678">678</a>         unsigned char slen = tn-&gt;<a href="ident?i=pos">pos</a>;
<a name="L679" href="source/net/ipv4/fib_trie.c#L679">679</a>         unsigned long stride, <a href="ident?i=i">i</a>;
<a name="L680" href="source/net/ipv4/fib_trie.c#L680">680</a> 
<a name="L681" href="source/net/ipv4/fib_trie.c#L681">681</a>         <b><i>/* search though the list of children looking for nodes that might</i></b>
<a name="L682" href="source/net/ipv4/fib_trie.c#L682">682</a> <b><i>         * have a suffix greater than the one we currently have.  This is</i></b>
<a name="L683" href="source/net/ipv4/fib_trie.c#L683">683</a> <b><i>         * why we start with a stride of 2 since a stride of 1 would</i></b>
<a name="L684" href="source/net/ipv4/fib_trie.c#L684">684</a> <b><i>         * represent the nodes with suffix length equal to tn-&gt;pos</i></b>
<a name="L685" href="source/net/ipv4/fib_trie.c#L685">685</a> <b><i>         */</i></b>
<a name="L686" href="source/net/ipv4/fib_trie.c#L686">686</a>         for (<a href="ident?i=i">i</a> = 0, stride = 0x2ul ; <a href="ident?i=i">i</a> &lt; <a href="ident?i=child_length">child_length</a>(tn); <a href="ident?i=i">i</a> += stride) {
<a name="L687" href="source/net/ipv4/fib_trie.c#L687">687</a>                 struct <a href="ident?i=key_vector">key_vector</a> *<a href="ident?i=n">n</a> = <a href="ident?i=get_child">get_child</a>(tn, <a href="ident?i=i">i</a>);
<a name="L688" href="source/net/ipv4/fib_trie.c#L688">688</a> 
<a name="L689" href="source/net/ipv4/fib_trie.c#L689">689</a>                 if (!<a href="ident?i=n">n</a> || (<a href="ident?i=n">n</a>-&gt;slen &lt;= slen))
<a name="L690" href="source/net/ipv4/fib_trie.c#L690">690</a>                         continue;
<a name="L691" href="source/net/ipv4/fib_trie.c#L691">691</a> 
<a name="L692" href="source/net/ipv4/fib_trie.c#L692">692</a>                 <b><i>/* update stride and slen based on new value */</i></b>
<a name="L693" href="source/net/ipv4/fib_trie.c#L693">693</a>                 stride &lt;&lt;= (<a href="ident?i=n">n</a>-&gt;slen - slen);
<a name="L694" href="source/net/ipv4/fib_trie.c#L694">694</a>                 slen = <a href="ident?i=n">n</a>-&gt;slen;
<a name="L695" href="source/net/ipv4/fib_trie.c#L695">695</a>                 <a href="ident?i=i">i</a> &amp;= ~(stride - 1);
<a name="L696" href="source/net/ipv4/fib_trie.c#L696">696</a> 
<a name="L697" href="source/net/ipv4/fib_trie.c#L697">697</a>                 <b><i>/* if slen covers all but the last bit we can stop here</i></b>
<a name="L698" href="source/net/ipv4/fib_trie.c#L698">698</a> <b><i>                 * there will be nothing longer than that since only node</i></b>
<a name="L699" href="source/net/ipv4/fib_trie.c#L699">699</a> <b><i>                 * 0 and 1 &lt;&lt; (bits - 1) could have that as their suffix</i></b>
<a name="L700" href="source/net/ipv4/fib_trie.c#L700">700</a> <b><i>                 * length.</i></b>
<a name="L701" href="source/net/ipv4/fib_trie.c#L701">701</a> <b><i>                 */</i></b>
<a name="L702" href="source/net/ipv4/fib_trie.c#L702">702</a>                 if ((slen + 1) &gt;= (tn-&gt;<a href="ident?i=pos">pos</a> + tn-&gt;<a href="ident?i=bits">bits</a>))
<a name="L703" href="source/net/ipv4/fib_trie.c#L703">703</a>                         break;
<a name="L704" href="source/net/ipv4/fib_trie.c#L704">704</a>         }
<a name="L705" href="source/net/ipv4/fib_trie.c#L705">705</a> 
<a name="L706" href="source/net/ipv4/fib_trie.c#L706">706</a>         tn-&gt;slen = slen;
<a name="L707" href="source/net/ipv4/fib_trie.c#L707">707</a> 
<a name="L708" href="source/net/ipv4/fib_trie.c#L708">708</a>         return slen;
<a name="L709" href="source/net/ipv4/fib_trie.c#L709">709</a> }
<a name="L710" href="source/net/ipv4/fib_trie.c#L710">710</a> 
<a name="L711" href="source/net/ipv4/fib_trie.c#L711">711</a> <b><i>/* From "Implementing a dynamic compressed trie" by Stefan Nilsson of</i></b>
<a name="L712" href="source/net/ipv4/fib_trie.c#L712">712</a> <b><i> * the Helsinki University of Technology and Matti Tikkanen of Nokia</i></b>
<a name="L713" href="source/net/ipv4/fib_trie.c#L713">713</a> <b><i> * Telecommunications, page 6:</i></b>
<a name="L714" href="source/net/ipv4/fib_trie.c#L714">714</a> <b><i> * "A node is doubled if the ratio of non-empty children to all</i></b>
<a name="L715" href="source/net/ipv4/fib_trie.c#L715">715</a> <b><i> * children in the *doubled* node is at least 'high'."</i></b>
<a name="L716" href="source/net/ipv4/fib_trie.c#L716">716</a> <b><i> *</i></b>
<a name="L717" href="source/net/ipv4/fib_trie.c#L717">717</a> <b><i> * 'high' in this instance is the variable 'inflate_threshold'. It</i></b>
<a name="L718" href="source/net/ipv4/fib_trie.c#L718">718</a> <b><i> * is expressed as a percentage, so we multiply it with</i></b>
<a name="L719" href="source/net/ipv4/fib_trie.c#L719">719</a> <b><i> * child_length() and instead of multiplying by 2 (since the</i></b>
<a name="L720" href="source/net/ipv4/fib_trie.c#L720">720</a> <b><i> * child array will be doubled by inflate()) and multiplying</i></b>
<a name="L721" href="source/net/ipv4/fib_trie.c#L721">721</a> <b><i> * the left-hand side by 100 (to handle the percentage thing) we</i></b>
<a name="L722" href="source/net/ipv4/fib_trie.c#L722">722</a> <b><i> * multiply the left-hand side by 50.</i></b>
<a name="L723" href="source/net/ipv4/fib_trie.c#L723">723</a> <b><i> *</i></b>
<a name="L724" href="source/net/ipv4/fib_trie.c#L724">724</a> <b><i> * The left-hand side may look a bit weird: child_length(tn)</i></b>
<a name="L725" href="source/net/ipv4/fib_trie.c#L725">725</a> <b><i> * - tn-&gt;empty_children is of course the number of non-null children</i></b>
<a name="L726" href="source/net/ipv4/fib_trie.c#L726">726</a> <b><i> * in the current node. tn-&gt;full_children is the number of "full"</i></b>
<a name="L727" href="source/net/ipv4/fib_trie.c#L727">727</a> <b><i> * children, that is non-null tnodes with a skip value of 0.</i></b>
<a name="L728" href="source/net/ipv4/fib_trie.c#L728">728</a> <b><i> * All of those will be doubled in the resulting inflated tnode, so</i></b>
<a name="L729" href="source/net/ipv4/fib_trie.c#L729">729</a> <b><i> * we just count them one extra time here.</i></b>
<a name="L730" href="source/net/ipv4/fib_trie.c#L730">730</a> <b><i> *</i></b>
<a name="L731" href="source/net/ipv4/fib_trie.c#L731">731</a> <b><i> * A clearer way to write this would be:</i></b>
<a name="L732" href="source/net/ipv4/fib_trie.c#L732">732</a> <b><i> *</i></b>
<a name="L733" href="source/net/ipv4/fib_trie.c#L733">733</a> <b><i> * to_be_doubled = tn-&gt;full_children;</i></b>
<a name="L734" href="source/net/ipv4/fib_trie.c#L734">734</a> <b><i> * not_to_be_doubled = child_length(tn) - tn-&gt;empty_children -</i></b>
<a name="L735" href="source/net/ipv4/fib_trie.c#L735">735</a> <b><i> *     tn-&gt;full_children;</i></b>
<a name="L736" href="source/net/ipv4/fib_trie.c#L736">736</a> <b><i> *</i></b>
<a name="L737" href="source/net/ipv4/fib_trie.c#L737">737</a> <b><i> * new_child_length = child_length(tn) * 2;</i></b>
<a name="L738" href="source/net/ipv4/fib_trie.c#L738">738</a> <b><i> *</i></b>
<a name="L739" href="source/net/ipv4/fib_trie.c#L739">739</a> <b><i> * new_fill_factor = 100 * (not_to_be_doubled + 2*to_be_doubled) /</i></b>
<a name="L740" href="source/net/ipv4/fib_trie.c#L740">740</a> <b><i> *      new_child_length;</i></b>
<a name="L741" href="source/net/ipv4/fib_trie.c#L741">741</a> <b><i> * if (new_fill_factor &gt;= inflate_threshold)</i></b>
<a name="L742" href="source/net/ipv4/fib_trie.c#L742">742</a> <b><i> *</i></b>
<a name="L743" href="source/net/ipv4/fib_trie.c#L743">743</a> <b><i> * ...and so on, tho it would mess up the while () loop.</i></b>
<a name="L744" href="source/net/ipv4/fib_trie.c#L744">744</a> <b><i> *</i></b>
<a name="L745" href="source/net/ipv4/fib_trie.c#L745">745</a> <b><i> * anyway,</i></b>
<a name="L746" href="source/net/ipv4/fib_trie.c#L746">746</a> <b><i> * 100 * (not_to_be_doubled + 2*to_be_doubled) / new_child_length &gt;=</i></b>
<a name="L747" href="source/net/ipv4/fib_trie.c#L747">747</a> <b><i> *      inflate_threshold</i></b>
<a name="L748" href="source/net/ipv4/fib_trie.c#L748">748</a> <b><i> *</i></b>
<a name="L749" href="source/net/ipv4/fib_trie.c#L749">749</a> <b><i> * avoid a division:</i></b>
<a name="L750" href="source/net/ipv4/fib_trie.c#L750">750</a> <b><i> * 100 * (not_to_be_doubled + 2*to_be_doubled) &gt;=</i></b>
<a name="L751" href="source/net/ipv4/fib_trie.c#L751">751</a> <b><i> *      inflate_threshold * new_child_length</i></b>
<a name="L752" href="source/net/ipv4/fib_trie.c#L752">752</a> <b><i> *</i></b>
<a name="L753" href="source/net/ipv4/fib_trie.c#L753">753</a> <b><i> * expand not_to_be_doubled and to_be_doubled, and shorten:</i></b>
<a name="L754" href="source/net/ipv4/fib_trie.c#L754">754</a> <b><i> * 100 * (child_length(tn) - tn-&gt;empty_children +</i></b>
<a name="L755" href="source/net/ipv4/fib_trie.c#L755">755</a> <b><i> *    tn-&gt;full_children) &gt;= inflate_threshold * new_child_length</i></b>
<a name="L756" href="source/net/ipv4/fib_trie.c#L756">756</a> <b><i> *</i></b>
<a name="L757" href="source/net/ipv4/fib_trie.c#L757">757</a> <b><i> * expand new_child_length:</i></b>
<a name="L758" href="source/net/ipv4/fib_trie.c#L758">758</a> <b><i> * 100 * (child_length(tn) - tn-&gt;empty_children +</i></b>
<a name="L759" href="source/net/ipv4/fib_trie.c#L759">759</a> <b><i> *    tn-&gt;full_children) &gt;=</i></b>
<a name="L760" href="source/net/ipv4/fib_trie.c#L760">760</a> <b><i> *      inflate_threshold * child_length(tn) * 2</i></b>
<a name="L761" href="source/net/ipv4/fib_trie.c#L761">761</a> <b><i> *</i></b>
<a name="L762" href="source/net/ipv4/fib_trie.c#L762">762</a> <b><i> * shorten again:</i></b>
<a name="L763" href="source/net/ipv4/fib_trie.c#L763">763</a> <b><i> * 50 * (tn-&gt;full_children + child_length(tn) -</i></b>
<a name="L764" href="source/net/ipv4/fib_trie.c#L764">764</a> <b><i> *    tn-&gt;empty_children) &gt;= inflate_threshold *</i></b>
<a name="L765" href="source/net/ipv4/fib_trie.c#L765">765</a> <b><i> *    child_length(tn)</i></b>
<a name="L766" href="source/net/ipv4/fib_trie.c#L766">766</a> <b><i> *</i></b>
<a name="L767" href="source/net/ipv4/fib_trie.c#L767">767</a> <b><i> */</i></b>
<a name="L768" href="source/net/ipv4/fib_trie.c#L768">768</a> static inline <a href="ident?i=bool">bool</a> <a href="ident?i=should_inflate">should_inflate</a>(struct <a href="ident?i=key_vector">key_vector</a> *<a href="ident?i=tp">tp</a>, struct <a href="ident?i=key_vector">key_vector</a> *tn)
<a name="L769" href="source/net/ipv4/fib_trie.c#L769">769</a> {
<a name="L770" href="source/net/ipv4/fib_trie.c#L770">770</a>         unsigned long <a href="ident?i=used">used</a> = <a href="ident?i=child_length">child_length</a>(tn);
<a name="L771" href="source/net/ipv4/fib_trie.c#L771">771</a>         unsigned long <a href="ident?i=threshold">threshold</a> = <a href="ident?i=used">used</a>;
<a name="L772" href="source/net/ipv4/fib_trie.c#L772">772</a> 
<a name="L773" href="source/net/ipv4/fib_trie.c#L773">773</a>         <b><i>/* Keep root node larger */</i></b>
<a name="L774" href="source/net/ipv4/fib_trie.c#L774">774</a>         <a href="ident?i=threshold">threshold</a> *= <a href="ident?i=IS_TRIE">IS_TRIE</a>(<a href="ident?i=tp">tp</a>) ? <a href="ident?i=inflate_threshold_root">inflate_threshold_root</a> : <a href="ident?i=inflate_threshold">inflate_threshold</a>;
<a name="L775" href="source/net/ipv4/fib_trie.c#L775">775</a>         <a href="ident?i=used">used</a> -= <a href="ident?i=tn_info">tn_info</a>(tn)-&gt;empty_children;
<a name="L776" href="source/net/ipv4/fib_trie.c#L776">776</a>         <a href="ident?i=used">used</a> += <a href="ident?i=tn_info">tn_info</a>(tn)-&gt;full_children;
<a name="L777" href="source/net/ipv4/fib_trie.c#L777">777</a> 
<a name="L778" href="source/net/ipv4/fib_trie.c#L778">778</a>         <b><i>/* if bits == KEYLENGTH then pos = 0, and will fail below */</i></b>
<a name="L779" href="source/net/ipv4/fib_trie.c#L779">779</a> 
<a name="L780" href="source/net/ipv4/fib_trie.c#L780">780</a>         return (<a href="ident?i=used">used</a> &gt; 1) &amp;&amp; tn-&gt;<a href="ident?i=pos">pos</a> &amp;&amp; ((50 * <a href="ident?i=used">used</a>) &gt;= <a href="ident?i=threshold">threshold</a>);
<a name="L781" href="source/net/ipv4/fib_trie.c#L781">781</a> }
<a name="L782" href="source/net/ipv4/fib_trie.c#L782">782</a> 
<a name="L783" href="source/net/ipv4/fib_trie.c#L783">783</a> static inline <a href="ident?i=bool">bool</a> <a href="ident?i=should_halve">should_halve</a>(struct <a href="ident?i=key_vector">key_vector</a> *<a href="ident?i=tp">tp</a>, struct <a href="ident?i=key_vector">key_vector</a> *tn)
<a name="L784" href="source/net/ipv4/fib_trie.c#L784">784</a> {
<a name="L785" href="source/net/ipv4/fib_trie.c#L785">785</a>         unsigned long <a href="ident?i=used">used</a> = <a href="ident?i=child_length">child_length</a>(tn);
<a name="L786" href="source/net/ipv4/fib_trie.c#L786">786</a>         unsigned long <a href="ident?i=threshold">threshold</a> = <a href="ident?i=used">used</a>;
<a name="L787" href="source/net/ipv4/fib_trie.c#L787">787</a> 
<a name="L788" href="source/net/ipv4/fib_trie.c#L788">788</a>         <b><i>/* Keep root node larger */</i></b>
<a name="L789" href="source/net/ipv4/fib_trie.c#L789">789</a>         <a href="ident?i=threshold">threshold</a> *= <a href="ident?i=IS_TRIE">IS_TRIE</a>(<a href="ident?i=tp">tp</a>) ? <a href="ident?i=halve_threshold_root">halve_threshold_root</a> : <a href="ident?i=halve_threshold">halve_threshold</a>;
<a name="L790" href="source/net/ipv4/fib_trie.c#L790">790</a>         <a href="ident?i=used">used</a> -= <a href="ident?i=tn_info">tn_info</a>(tn)-&gt;empty_children;
<a name="L791" href="source/net/ipv4/fib_trie.c#L791">791</a> 
<a name="L792" href="source/net/ipv4/fib_trie.c#L792">792</a>         <b><i>/* if bits == KEYLENGTH then used = 100% on wrap, and will fail below */</i></b>
<a name="L793" href="source/net/ipv4/fib_trie.c#L793">793</a> 
<a name="L794" href="source/net/ipv4/fib_trie.c#L794">794</a>         return (<a href="ident?i=used">used</a> &gt; 1) &amp;&amp; (tn-&gt;<a href="ident?i=bits">bits</a> &gt; 1) &amp;&amp; ((100 * <a href="ident?i=used">used</a>) &lt; <a href="ident?i=threshold">threshold</a>);
<a name="L795" href="source/net/ipv4/fib_trie.c#L795">795</a> }
<a name="L796" href="source/net/ipv4/fib_trie.c#L796">796</a> 
<a name="L797" href="source/net/ipv4/fib_trie.c#L797">797</a> static inline <a href="ident?i=bool">bool</a> <a href="ident?i=should_collapse">should_collapse</a>(struct <a href="ident?i=key_vector">key_vector</a> *tn)
<a name="L798" href="source/net/ipv4/fib_trie.c#L798">798</a> {
<a name="L799" href="source/net/ipv4/fib_trie.c#L799">799</a>         unsigned long <a href="ident?i=used">used</a> = <a href="ident?i=child_length">child_length</a>(tn);
<a name="L800" href="source/net/ipv4/fib_trie.c#L800">800</a> 
<a name="L801" href="source/net/ipv4/fib_trie.c#L801">801</a>         <a href="ident?i=used">used</a> -= <a href="ident?i=tn_info">tn_info</a>(tn)-&gt;empty_children;
<a name="L802" href="source/net/ipv4/fib_trie.c#L802">802</a> 
<a name="L803" href="source/net/ipv4/fib_trie.c#L803">803</a>         <b><i>/* account for bits == KEYLENGTH case */</i></b>
<a name="L804" href="source/net/ipv4/fib_trie.c#L804">804</a>         if ((tn-&gt;<a href="ident?i=bits">bits</a> == <a href="ident?i=KEYLENGTH">KEYLENGTH</a>) &amp;&amp; <a href="ident?i=tn_info">tn_info</a>(tn)-&gt;full_children)
<a name="L805" href="source/net/ipv4/fib_trie.c#L805">805</a>                 <a href="ident?i=used">used</a> -= <a href="ident?i=KEY_MAX">KEY_MAX</a>;
<a name="L806" href="source/net/ipv4/fib_trie.c#L806">806</a> 
<a name="L807" href="source/net/ipv4/fib_trie.c#L807">807</a>         <b><i>/* One child or none, time to drop us from the trie */</i></b>
<a name="L808" href="source/net/ipv4/fib_trie.c#L808">808</a>         return <a href="ident?i=used">used</a> &lt; 2;
<a name="L809" href="source/net/ipv4/fib_trie.c#L809">809</a> }
<a name="L810" href="source/net/ipv4/fib_trie.c#L810">810</a> 
<a name="L811" href="source/net/ipv4/fib_trie.c#L811">811</a> #define <a href="ident?i=MAX_WORK">MAX_WORK</a> 10
<a name="L812" href="source/net/ipv4/fib_trie.c#L812">812</a> static struct <a href="ident?i=key_vector">key_vector</a> *<a href="ident?i=resize">resize</a>(struct <a href="ident?i=trie">trie</a> *<a href="ident?i=t">t</a>, struct <a href="ident?i=key_vector">key_vector</a> *tn)
<a name="L813" href="source/net/ipv4/fib_trie.c#L813">813</a> {
<a name="L814" href="source/net/ipv4/fib_trie.c#L814">814</a> #ifdef CONFIG_IP_FIB_TRIE_STATS
<a name="L815" href="source/net/ipv4/fib_trie.c#L815">815</a>         struct <a href="ident?i=trie_use_stats">trie_use_stats</a> <a href="ident?i=__percpu">__percpu</a> *<a href="ident?i=stats">stats</a> = <a href="ident?i=t">t</a>-&gt;<a href="ident?i=stats">stats</a>;
<a name="L816" href="source/net/ipv4/fib_trie.c#L816">816</a> #endif
<a name="L817" href="source/net/ipv4/fib_trie.c#L817">817</a>         struct <a href="ident?i=key_vector">key_vector</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=node_parent">node_parent</a>(tn);
<a name="L818" href="source/net/ipv4/fib_trie.c#L818">818</a>         unsigned long cindex = <a href="ident?i=get_index">get_index</a>(tn-&gt;<a href="ident?i=key">key</a>, <a href="ident?i=tp">tp</a>);
<a name="L819" href="source/net/ipv4/fib_trie.c#L819">819</a>         int max_work = <a href="ident?i=MAX_WORK">MAX_WORK</a>;
<a name="L820" href="source/net/ipv4/fib_trie.c#L820">820</a> 
<a name="L821" href="source/net/ipv4/fib_trie.c#L821">821</a>         <a href="ident?i=pr_debug">pr_debug</a>(<i>"In tnode_resize %p inflate_threshold=%d threshold=%d\n"</i>,
<a name="L822" href="source/net/ipv4/fib_trie.c#L822">822</a>                  tn, <a href="ident?i=inflate_threshold">inflate_threshold</a>, <a href="ident?i=halve_threshold">halve_threshold</a>);
<a name="L823" href="source/net/ipv4/fib_trie.c#L823">823</a> 
<a name="L824" href="source/net/ipv4/fib_trie.c#L824">824</a>         <b><i>/* track the tnode via the pointer from the parent instead of</i></b>
<a name="L825" href="source/net/ipv4/fib_trie.c#L825">825</a> <b><i>         * doing it ourselves.  This way we can let RCU fully do its</i></b>
<a name="L826" href="source/net/ipv4/fib_trie.c#L826">826</a> <b><i>         * thing without us interfering</i></b>
<a name="L827" href="source/net/ipv4/fib_trie.c#L827">827</a> <b><i>         */</i></b>
<a name="L828" href="source/net/ipv4/fib_trie.c#L828">828</a>         <a href="ident?i=BUG_ON">BUG_ON</a>(tn != <a href="ident?i=get_child">get_child</a>(<a href="ident?i=tp">tp</a>, cindex));
<a name="L829" href="source/net/ipv4/fib_trie.c#L829">829</a> 
<a name="L830" href="source/net/ipv4/fib_trie.c#L830">830</a>         <b><i>/* Double as long as the resulting node has a number of</i></b>
<a name="L831" href="source/net/ipv4/fib_trie.c#L831">831</a> <b><i>         * nonempty nodes that are above the threshold.</i></b>
<a name="L832" href="source/net/ipv4/fib_trie.c#L832">832</a> <b><i>         */</i></b>
<a name="L833" href="source/net/ipv4/fib_trie.c#L833">833</a>         while (<a href="ident?i=should_inflate">should_inflate</a>(<a href="ident?i=tp">tp</a>, tn) &amp;&amp; max_work) {
<a name="L834" href="source/net/ipv4/fib_trie.c#L834">834</a>                 <a href="ident?i=tp">tp</a> = <a href="ident?i=inflate">inflate</a>(<a href="ident?i=t">t</a>, tn);
<a name="L835" href="source/net/ipv4/fib_trie.c#L835">835</a>                 if (!<a href="ident?i=tp">tp</a>) {
<a name="L836" href="source/net/ipv4/fib_trie.c#L836">836</a> #ifdef CONFIG_IP_FIB_TRIE_STATS
<a name="L837" href="source/net/ipv4/fib_trie.c#L837">837</a>                         <a href="ident?i=this_cpu_inc">this_cpu_inc</a>(<a href="ident?i=stats">stats</a>-&gt;resize_node_skipped);
<a name="L838" href="source/net/ipv4/fib_trie.c#L838">838</a> #endif
<a name="L839" href="source/net/ipv4/fib_trie.c#L839">839</a>                         break;
<a name="L840" href="source/net/ipv4/fib_trie.c#L840">840</a>                 }
<a name="L841" href="source/net/ipv4/fib_trie.c#L841">841</a> 
<a name="L842" href="source/net/ipv4/fib_trie.c#L842">842</a>                 max_work--;
<a name="L843" href="source/net/ipv4/fib_trie.c#L843">843</a>                 tn = <a href="ident?i=get_child">get_child</a>(<a href="ident?i=tp">tp</a>, cindex);
<a name="L844" href="source/net/ipv4/fib_trie.c#L844">844</a>         }
<a name="L845" href="source/net/ipv4/fib_trie.c#L845">845</a> 
<a name="L846" href="source/net/ipv4/fib_trie.c#L846">846</a>         <b><i>/* update parent in case inflate failed */</i></b>
<a name="L847" href="source/net/ipv4/fib_trie.c#L847">847</a>         <a href="ident?i=tp">tp</a> = <a href="ident?i=node_parent">node_parent</a>(tn);
<a name="L848" href="source/net/ipv4/fib_trie.c#L848">848</a> 
<a name="L849" href="source/net/ipv4/fib_trie.c#L849">849</a>         <b><i>/* Return if at least one inflate is run */</i></b>
<a name="L850" href="source/net/ipv4/fib_trie.c#L850">850</a>         if (max_work != <a href="ident?i=MAX_WORK">MAX_WORK</a>)
<a name="L851" href="source/net/ipv4/fib_trie.c#L851">851</a>                 return <a href="ident?i=tp">tp</a>;
<a name="L852" href="source/net/ipv4/fib_trie.c#L852">852</a> 
<a name="L853" href="source/net/ipv4/fib_trie.c#L853">853</a>         <b><i>/* Halve as long as the number of empty children in this</i></b>
<a name="L854" href="source/net/ipv4/fib_trie.c#L854">854</a> <b><i>         * node is above threshold.</i></b>
<a name="L855" href="source/net/ipv4/fib_trie.c#L855">855</a> <b><i>         */</i></b>
<a name="L856" href="source/net/ipv4/fib_trie.c#L856">856</a>         while (<a href="ident?i=should_halve">should_halve</a>(<a href="ident?i=tp">tp</a>, tn) &amp;&amp; max_work) {
<a name="L857" href="source/net/ipv4/fib_trie.c#L857">857</a>                 <a href="ident?i=tp">tp</a> = <a href="ident?i=halve">halve</a>(<a href="ident?i=t">t</a>, tn);
<a name="L858" href="source/net/ipv4/fib_trie.c#L858">858</a>                 if (!<a href="ident?i=tp">tp</a>) {
<a name="L859" href="source/net/ipv4/fib_trie.c#L859">859</a> #ifdef CONFIG_IP_FIB_TRIE_STATS
<a name="L860" href="source/net/ipv4/fib_trie.c#L860">860</a>                         <a href="ident?i=this_cpu_inc">this_cpu_inc</a>(<a href="ident?i=stats">stats</a>-&gt;resize_node_skipped);
<a name="L861" href="source/net/ipv4/fib_trie.c#L861">861</a> #endif
<a name="L862" href="source/net/ipv4/fib_trie.c#L862">862</a>                         break;
<a name="L863" href="source/net/ipv4/fib_trie.c#L863">863</a>                 }
<a name="L864" href="source/net/ipv4/fib_trie.c#L864">864</a> 
<a name="L865" href="source/net/ipv4/fib_trie.c#L865">865</a>                 max_work--;
<a name="L866" href="source/net/ipv4/fib_trie.c#L866">866</a>                 tn = <a href="ident?i=get_child">get_child</a>(<a href="ident?i=tp">tp</a>, cindex);
<a name="L867" href="source/net/ipv4/fib_trie.c#L867">867</a>         }
<a name="L868" href="source/net/ipv4/fib_trie.c#L868">868</a> 
<a name="L869" href="source/net/ipv4/fib_trie.c#L869">869</a>         <b><i>/* Only one child remains */</i></b>
<a name="L870" href="source/net/ipv4/fib_trie.c#L870">870</a>         if (<a href="ident?i=should_collapse">should_collapse</a>(tn))
<a name="L871" href="source/net/ipv4/fib_trie.c#L871">871</a>                 return <a href="ident?i=collapse">collapse</a>(<a href="ident?i=t">t</a>, tn);
<a name="L872" href="source/net/ipv4/fib_trie.c#L872">872</a> 
<a name="L873" href="source/net/ipv4/fib_trie.c#L873">873</a>         <b><i>/* update parent in case halve failed */</i></b>
<a name="L874" href="source/net/ipv4/fib_trie.c#L874">874</a>         <a href="ident?i=tp">tp</a> = <a href="ident?i=node_parent">node_parent</a>(tn);
<a name="L875" href="source/net/ipv4/fib_trie.c#L875">875</a> 
<a name="L876" href="source/net/ipv4/fib_trie.c#L876">876</a>         <b><i>/* Return if at least one deflate was run */</i></b>
<a name="L877" href="source/net/ipv4/fib_trie.c#L877">877</a>         if (max_work != <a href="ident?i=MAX_WORK">MAX_WORK</a>)
<a name="L878" href="source/net/ipv4/fib_trie.c#L878">878</a>                 return <a href="ident?i=tp">tp</a>;
<a name="L879" href="source/net/ipv4/fib_trie.c#L879">879</a> 
<a name="L880" href="source/net/ipv4/fib_trie.c#L880">880</a>         <b><i>/* push the suffix length to the parent node */</i></b>
<a name="L881" href="source/net/ipv4/fib_trie.c#L881">881</a>         if (tn-&gt;slen &gt; tn-&gt;<a href="ident?i=pos">pos</a>) {
<a name="L882" href="source/net/ipv4/fib_trie.c#L882">882</a>                 unsigned char slen = <a href="ident?i=update_suffix">update_suffix</a>(tn);
<a name="L883" href="source/net/ipv4/fib_trie.c#L883">883</a> 
<a name="L884" href="source/net/ipv4/fib_trie.c#L884">884</a>                 if (slen &gt; <a href="ident?i=tp">tp</a>-&gt;slen)
<a name="L885" href="source/net/ipv4/fib_trie.c#L885">885</a>                         <a href="ident?i=tp">tp</a>-&gt;slen = slen;
<a name="L886" href="source/net/ipv4/fib_trie.c#L886">886</a>         }
<a name="L887" href="source/net/ipv4/fib_trie.c#L887">887</a> 
<a name="L888" href="source/net/ipv4/fib_trie.c#L888">888</a>         return <a href="ident?i=tp">tp</a>;
<a name="L889" href="source/net/ipv4/fib_trie.c#L889">889</a> }
<a name="L890" href="source/net/ipv4/fib_trie.c#L890">890</a> 
<a name="L891" href="source/net/ipv4/fib_trie.c#L891">891</a> static void <a href="ident?i=leaf_pull_suffix">leaf_pull_suffix</a>(struct <a href="ident?i=key_vector">key_vector</a> *<a href="ident?i=tp">tp</a>, struct <a href="ident?i=key_vector">key_vector</a> *<a href="ident?i=l">l</a>)
<a name="L892" href="source/net/ipv4/fib_trie.c#L892">892</a> {
<a name="L893" href="source/net/ipv4/fib_trie.c#L893">893</a>         while ((<a href="ident?i=tp">tp</a>-&gt;slen &gt; <a href="ident?i=tp">tp</a>-&gt;<a href="ident?i=pos">pos</a>) &amp;&amp; (<a href="ident?i=tp">tp</a>-&gt;slen &gt; <a href="ident?i=l">l</a>-&gt;slen)) {
<a name="L894" href="source/net/ipv4/fib_trie.c#L894">894</a>                 if (<a href="ident?i=update_suffix">update_suffix</a>(<a href="ident?i=tp">tp</a>) &gt; <a href="ident?i=l">l</a>-&gt;slen)
<a name="L895" href="source/net/ipv4/fib_trie.c#L895">895</a>                         break;
<a name="L896" href="source/net/ipv4/fib_trie.c#L896">896</a>                 <a href="ident?i=tp">tp</a> = <a href="ident?i=node_parent">node_parent</a>(<a href="ident?i=tp">tp</a>);
<a name="L897" href="source/net/ipv4/fib_trie.c#L897">897</a>         }
<a name="L898" href="source/net/ipv4/fib_trie.c#L898">898</a> }
<a name="L899" href="source/net/ipv4/fib_trie.c#L899">899</a> 
<a name="L900" href="source/net/ipv4/fib_trie.c#L900">900</a> static void <a href="ident?i=leaf_push_suffix">leaf_push_suffix</a>(struct <a href="ident?i=key_vector">key_vector</a> *tn, struct <a href="ident?i=key_vector">key_vector</a> *<a href="ident?i=l">l</a>)
<a name="L901" href="source/net/ipv4/fib_trie.c#L901">901</a> {
<a name="L902" href="source/net/ipv4/fib_trie.c#L902">902</a>         <b><i>/* if this is a new leaf then tn will be NULL and we can sort</i></b>
<a name="L903" href="source/net/ipv4/fib_trie.c#L903">903</a> <b><i>         * out parent suffix lengths as a part of trie_rebalance</i></b>
<a name="L904" href="source/net/ipv4/fib_trie.c#L904">904</a> <b><i>         */</i></b>
<a name="L905" href="source/net/ipv4/fib_trie.c#L905">905</a>         while (tn-&gt;slen &lt; <a href="ident?i=l">l</a>-&gt;slen) {
<a name="L906" href="source/net/ipv4/fib_trie.c#L906">906</a>                 tn-&gt;slen = <a href="ident?i=l">l</a>-&gt;slen;
<a name="L907" href="source/net/ipv4/fib_trie.c#L907">907</a>                 tn = <a href="ident?i=node_parent">node_parent</a>(tn);
<a name="L908" href="source/net/ipv4/fib_trie.c#L908">908</a>         }
<a name="L909" href="source/net/ipv4/fib_trie.c#L909">909</a> }
<a name="L910" href="source/net/ipv4/fib_trie.c#L910">910</a> 
<a name="L911" href="source/net/ipv4/fib_trie.c#L911">911</a> <b><i>/* rcu_read_lock needs to be hold by caller from readside */</i></b>
<a name="L912" href="source/net/ipv4/fib_trie.c#L912">912</a> static struct <a href="ident?i=key_vector">key_vector</a> *<a href="ident?i=fib_find_node">fib_find_node</a>(struct <a href="ident?i=trie">trie</a> *<a href="ident?i=t">t</a>,
<a name="L913" href="source/net/ipv4/fib_trie.c#L913">913</a>                                         struct <a href="ident?i=key_vector">key_vector</a> **<a href="ident?i=tp">tp</a>, <a href="ident?i=u32">u32</a> <a href="ident?i=key">key</a>)
<a name="L914" href="source/net/ipv4/fib_trie.c#L914">914</a> {
<a name="L915" href="source/net/ipv4/fib_trie.c#L915">915</a>         struct <a href="ident?i=key_vector">key_vector</a> *pn, *<a href="ident?i=n">n</a> = <a href="ident?i=t">t</a>-&gt;kv;
<a name="L916" href="source/net/ipv4/fib_trie.c#L916">916</a>         unsigned long <a href="ident?i=index">index</a> = 0;
<a name="L917" href="source/net/ipv4/fib_trie.c#L917">917</a> 
<a name="L918" href="source/net/ipv4/fib_trie.c#L918">918</a>         do {
<a name="L919" href="source/net/ipv4/fib_trie.c#L919">919</a>                 pn = <a href="ident?i=n">n</a>;
<a name="L920" href="source/net/ipv4/fib_trie.c#L920">920</a>                 <a href="ident?i=n">n</a> = <a href="ident?i=get_child_rcu">get_child_rcu</a>(<a href="ident?i=n">n</a>, <a href="ident?i=index">index</a>);
<a name="L921" href="source/net/ipv4/fib_trie.c#L921">921</a> 
<a name="L922" href="source/net/ipv4/fib_trie.c#L922">922</a>                 if (!<a href="ident?i=n">n</a>)
<a name="L923" href="source/net/ipv4/fib_trie.c#L923">923</a>                         break;
<a name="L924" href="source/net/ipv4/fib_trie.c#L924">924</a> 
<a name="L925" href="source/net/ipv4/fib_trie.c#L925">925</a>                 <a href="ident?i=index">index</a> = <a href="ident?i=get_cindex">get_cindex</a>(<a href="ident?i=key">key</a>, <a href="ident?i=n">n</a>);
<a name="L926" href="source/net/ipv4/fib_trie.c#L926">926</a> 
<a name="L927" href="source/net/ipv4/fib_trie.c#L927">927</a>                 <b><i>/* This bit of code is a bit tricky but it combines multiple</i></b>
<a name="L928" href="source/net/ipv4/fib_trie.c#L928">928</a> <b><i>                 * checks into a single check.  The prefix consists of the</i></b>
<a name="L929" href="source/net/ipv4/fib_trie.c#L929">929</a> <b><i>                 * prefix plus zeros for the bits in the cindex. The index</i></b>
<a name="L930" href="source/net/ipv4/fib_trie.c#L930">930</a> <b><i>                 * is the difference between the key and this value.  From</i></b>
<a name="L931" href="source/net/ipv4/fib_trie.c#L931">931</a> <b><i>                 * this we can actually derive several pieces of data.</i></b>
<a name="L932" href="source/net/ipv4/fib_trie.c#L932">932</a> <b><i>                 *   if (index &gt;= (1ul &lt;&lt; bits))</i></b>
<a name="L933" href="source/net/ipv4/fib_trie.c#L933">933</a> <b><i>                 *     we have a mismatch in skip bits and failed</i></b>
<a name="L934" href="source/net/ipv4/fib_trie.c#L934">934</a> <b><i>                 *   else</i></b>
<a name="L935" href="source/net/ipv4/fib_trie.c#L935">935</a> <b><i>                 *     we know the value is cindex</i></b>
<a name="L936" href="source/net/ipv4/fib_trie.c#L936">936</a> <b><i>                 *</i></b>
<a name="L937" href="source/net/ipv4/fib_trie.c#L937">937</a> <b><i>                 * This check is safe even if bits == KEYLENGTH due to the</i></b>
<a name="L938" href="source/net/ipv4/fib_trie.c#L938">938</a> <b><i>                 * fact that we can only allocate a node with 32 bits if a</i></b>
<a name="L939" href="source/net/ipv4/fib_trie.c#L939">939</a> <b><i>                 * long is greater than 32 bits.</i></b>
<a name="L940" href="source/net/ipv4/fib_trie.c#L940">940</a> <b><i>                 */</i></b>
<a name="L941" href="source/net/ipv4/fib_trie.c#L941">941</a>                 if (<a href="ident?i=index">index</a> &gt;= (1ul &lt;&lt; <a href="ident?i=n">n</a>-&gt;<a href="ident?i=bits">bits</a>)) {
<a name="L942" href="source/net/ipv4/fib_trie.c#L942">942</a>                         <a href="ident?i=n">n</a> = <a href="ident?i=NULL">NULL</a>;
<a name="L943" href="source/net/ipv4/fib_trie.c#L943">943</a>                         break;
<a name="L944" href="source/net/ipv4/fib_trie.c#L944">944</a>                 }
<a name="L945" href="source/net/ipv4/fib_trie.c#L945">945</a> 
<a name="L946" href="source/net/ipv4/fib_trie.c#L946">946</a>                 <b><i>/* keep searching until we find a perfect match leaf or NULL */</i></b>
<a name="L947" href="source/net/ipv4/fib_trie.c#L947">947</a>         } while (<a href="ident?i=IS_TNODE">IS_TNODE</a>(<a href="ident?i=n">n</a>));
<a name="L948" href="source/net/ipv4/fib_trie.c#L948">948</a> 
<a name="L949" href="source/net/ipv4/fib_trie.c#L949">949</a>         *<a href="ident?i=tp">tp</a> = pn;
<a name="L950" href="source/net/ipv4/fib_trie.c#L950">950</a> 
<a name="L951" href="source/net/ipv4/fib_trie.c#L951">951</a>         return <a href="ident?i=n">n</a>;
<a name="L952" href="source/net/ipv4/fib_trie.c#L952">952</a> }
<a name="L953" href="source/net/ipv4/fib_trie.c#L953">953</a> 
<a name="L954" href="source/net/ipv4/fib_trie.c#L954">954</a> <b><i>/* Return the first fib alias matching TOS with</i></b>
<a name="L955" href="source/net/ipv4/fib_trie.c#L955">955</a> <b><i> * priority less than or equal to PRIO.</i></b>
<a name="L956" href="source/net/ipv4/fib_trie.c#L956">956</a> <b><i> */</i></b>
<a name="L957" href="source/net/ipv4/fib_trie.c#L957">957</a> static struct <a href="ident?i=fib_alias">fib_alias</a> *<a href="ident?i=fib_find_alias">fib_find_alias</a>(struct <a href="ident?i=hlist_head">hlist_head</a> *fah, <a href="ident?i=u8">u8</a> slen,
<a name="L958" href="source/net/ipv4/fib_trie.c#L958">958</a>                                         <a href="ident?i=u8">u8</a> tos, <a href="ident?i=u32">u32</a> prio, <a href="ident?i=u32">u32</a> tb_id)
<a name="L959" href="source/net/ipv4/fib_trie.c#L959">959</a> {
<a name="L960" href="source/net/ipv4/fib_trie.c#L960">960</a>         struct <a href="ident?i=fib_alias">fib_alias</a> *fa;
<a name="L961" href="source/net/ipv4/fib_trie.c#L961">961</a> 
<a name="L962" href="source/net/ipv4/fib_trie.c#L962">962</a>         if (!fah)
<a name="L963" href="source/net/ipv4/fib_trie.c#L963">963</a>                 return <a href="ident?i=NULL">NULL</a>;
<a name="L964" href="source/net/ipv4/fib_trie.c#L964">964</a> 
<a name="L965" href="source/net/ipv4/fib_trie.c#L965">965</a>         <a href="ident?i=hlist_for_each_entry">hlist_for_each_entry</a>(fa, fah, fa_list) {
<a name="L966" href="source/net/ipv4/fib_trie.c#L966">966</a>                 if (fa-&gt;fa_slen &lt; slen)
<a name="L967" href="source/net/ipv4/fib_trie.c#L967">967</a>                         continue;
<a name="L968" href="source/net/ipv4/fib_trie.c#L968">968</a>                 if (fa-&gt;fa_slen != slen)
<a name="L969" href="source/net/ipv4/fib_trie.c#L969">969</a>                         break;
<a name="L970" href="source/net/ipv4/fib_trie.c#L970">970</a>                 if (fa-&gt;tb_id &gt; tb_id)
<a name="L971" href="source/net/ipv4/fib_trie.c#L971">971</a>                         continue;
<a name="L972" href="source/net/ipv4/fib_trie.c#L972">972</a>                 if (fa-&gt;tb_id != tb_id)
<a name="L973" href="source/net/ipv4/fib_trie.c#L973">973</a>                         break;
<a name="L974" href="source/net/ipv4/fib_trie.c#L974">974</a>                 if (fa-&gt;fa_tos &gt; tos)
<a name="L975" href="source/net/ipv4/fib_trie.c#L975">975</a>                         continue;
<a name="L976" href="source/net/ipv4/fib_trie.c#L976">976</a>                 if (fa-&gt;fa_info-&gt;fib_priority &gt;= prio || fa-&gt;fa_tos &lt; tos)
<a name="L977" href="source/net/ipv4/fib_trie.c#L977">977</a>                         return fa;
<a name="L978" href="source/net/ipv4/fib_trie.c#L978">978</a>         }
<a name="L979" href="source/net/ipv4/fib_trie.c#L979">979</a> 
<a name="L980" href="source/net/ipv4/fib_trie.c#L980">980</a>         return <a href="ident?i=NULL">NULL</a>;
<a name="L981" href="source/net/ipv4/fib_trie.c#L981">981</a> }
<a name="L982" href="source/net/ipv4/fib_trie.c#L982">982</a> 
<a name="L983" href="source/net/ipv4/fib_trie.c#L983">983</a> static void <a href="ident?i=trie_rebalance">trie_rebalance</a>(struct <a href="ident?i=trie">trie</a> *<a href="ident?i=t">t</a>, struct <a href="ident?i=key_vector">key_vector</a> *tn)
<a name="L984" href="source/net/ipv4/fib_trie.c#L984">984</a> {
<a name="L985" href="source/net/ipv4/fib_trie.c#L985">985</a>         while (!<a href="ident?i=IS_TRIE">IS_TRIE</a>(tn))
<a name="L986" href="source/net/ipv4/fib_trie.c#L986">986</a>                 tn = <a href="ident?i=resize">resize</a>(<a href="ident?i=t">t</a>, tn);
<a name="L987" href="source/net/ipv4/fib_trie.c#L987">987</a> }
<a name="L988" href="source/net/ipv4/fib_trie.c#L988">988</a> 
<a name="L989" href="source/net/ipv4/fib_trie.c#L989">989</a> static int <a href="ident?i=fib_insert_node">fib_insert_node</a>(struct <a href="ident?i=trie">trie</a> *<a href="ident?i=t">t</a>, struct <a href="ident?i=key_vector">key_vector</a> *<a href="ident?i=tp">tp</a>,
<a name="L990" href="source/net/ipv4/fib_trie.c#L990">990</a>                            struct <a href="ident?i=fib_alias">fib_alias</a> *<a href="ident?i=new">new</a>, <a href="ident?i=t_key">t_key</a> <a href="ident?i=key">key</a>)
<a name="L991" href="source/net/ipv4/fib_trie.c#L991">991</a> {
<a name="L992" href="source/net/ipv4/fib_trie.c#L992">992</a>         struct <a href="ident?i=key_vector">key_vector</a> *<a href="ident?i=n">n</a>, *<a href="ident?i=l">l</a>;
<a name="L993" href="source/net/ipv4/fib_trie.c#L993">993</a> 
<a name="L994" href="source/net/ipv4/fib_trie.c#L994">994</a>         <a href="ident?i=l">l</a> = <a href="ident?i=leaf_new">leaf_new</a>(<a href="ident?i=key">key</a>, <a href="ident?i=new">new</a>);
<a name="L995" href="source/net/ipv4/fib_trie.c#L995">995</a>         if (!<a href="ident?i=l">l</a>)
<a name="L996" href="source/net/ipv4/fib_trie.c#L996">996</a>                 goto noleaf;
<a name="L997" href="source/net/ipv4/fib_trie.c#L997">997</a> 
<a name="L998" href="source/net/ipv4/fib_trie.c#L998">998</a>         <b><i>/* retrieve child from parent node */</i></b>
<a name="L999" href="source/net/ipv4/fib_trie.c#L999">999</a>         <a href="ident?i=n">n</a> = <a href="ident?i=get_child">get_child</a>(<a href="ident?i=tp">tp</a>, <a href="ident?i=get_index">get_index</a>(<a href="ident?i=key">key</a>, <a href="ident?i=tp">tp</a>));
<a name="L1000" href="source/net/ipv4/fib_trie.c#L1000">1000</a> 
<a name="L1001" href="source/net/ipv4/fib_trie.c#L1001">1001</a>         <b><i>/* Case 2: n is a LEAF or a TNODE and the key doesn't match.</i></b>
<a name="L1002" href="source/net/ipv4/fib_trie.c#L1002">1002</a> <b><i>         *</i></b>
<a name="L1003" href="source/net/ipv4/fib_trie.c#L1003">1003</a> <b><i>         *  Add a new tnode here</i></b>
<a name="L1004" href="source/net/ipv4/fib_trie.c#L1004">1004</a> <b><i>         *  first tnode need some special handling</i></b>
<a name="L1005" href="source/net/ipv4/fib_trie.c#L1005">1005</a> <b><i>         *  leaves us in position for handling as case 3</i></b>
<a name="L1006" href="source/net/ipv4/fib_trie.c#L1006">1006</a> <b><i>         */</i></b>
<a name="L1007" href="source/net/ipv4/fib_trie.c#L1007">1007</a>         if (<a href="ident?i=n">n</a>) {
<a name="L1008" href="source/net/ipv4/fib_trie.c#L1008">1008</a>                 struct <a href="ident?i=key_vector">key_vector</a> *tn;
<a name="L1009" href="source/net/ipv4/fib_trie.c#L1009">1009</a> 
<a name="L1010" href="source/net/ipv4/fib_trie.c#L1010">1010</a>                 tn = <a href="ident?i=tnode_new">tnode_new</a>(<a href="ident?i=key">key</a>, <a href="ident?i=__fls">__fls</a>(<a href="ident?i=key">key</a> ^ <a href="ident?i=n">n</a>-&gt;<a href="ident?i=key">key</a>), 1);
<a name="L1011" href="source/net/ipv4/fib_trie.c#L1011">1011</a>                 if (!tn)
<a name="L1012" href="source/net/ipv4/fib_trie.c#L1012">1012</a>                         goto notnode;
<a name="L1013" href="source/net/ipv4/fib_trie.c#L1013">1013</a> 
<a name="L1014" href="source/net/ipv4/fib_trie.c#L1014">1014</a>                 <b><i>/* initialize routes out of node */</i></b>
<a name="L1015" href="source/net/ipv4/fib_trie.c#L1015">1015</a>                 <a href="ident?i=NODE_INIT_PARENT">NODE_INIT_PARENT</a>(tn, <a href="ident?i=tp">tp</a>);
<a name="L1016" href="source/net/ipv4/fib_trie.c#L1016">1016</a>                 <a href="ident?i=put_child">put_child</a>(tn, <a href="ident?i=get_index">get_index</a>(<a href="ident?i=key">key</a>, tn) ^ 1, <a href="ident?i=n">n</a>);
<a name="L1017" href="source/net/ipv4/fib_trie.c#L1017">1017</a> 
<a name="L1018" href="source/net/ipv4/fib_trie.c#L1018">1018</a>                 <b><i>/* start adding routes into the node */</i></b>
<a name="L1019" href="source/net/ipv4/fib_trie.c#L1019">1019</a>                 <a href="ident?i=put_child_root">put_child_root</a>(<a href="ident?i=tp">tp</a>, <a href="ident?i=key">key</a>, tn);
<a name="L1020" href="source/net/ipv4/fib_trie.c#L1020">1020</a>                 <a href="ident?i=node_set_parent">node_set_parent</a>(<a href="ident?i=n">n</a>, tn);
<a name="L1021" href="source/net/ipv4/fib_trie.c#L1021">1021</a> 
<a name="L1022" href="source/net/ipv4/fib_trie.c#L1022">1022</a>                 <b><i>/* parent now has a NULL spot where the leaf can go */</i></b>
<a name="L1023" href="source/net/ipv4/fib_trie.c#L1023">1023</a>                 <a href="ident?i=tp">tp</a> = tn;
<a name="L1024" href="source/net/ipv4/fib_trie.c#L1024">1024</a>         }
<a name="L1025" href="source/net/ipv4/fib_trie.c#L1025">1025</a> 
<a name="L1026" href="source/net/ipv4/fib_trie.c#L1026">1026</a>         <b><i>/* Case 3: n is NULL, and will just insert a new leaf */</i></b>
<a name="L1027" href="source/net/ipv4/fib_trie.c#L1027">1027</a>         <a href="ident?i=NODE_INIT_PARENT">NODE_INIT_PARENT</a>(<a href="ident?i=l">l</a>, <a href="ident?i=tp">tp</a>);
<a name="L1028" href="source/net/ipv4/fib_trie.c#L1028">1028</a>         <a href="ident?i=put_child_root">put_child_root</a>(<a href="ident?i=tp">tp</a>, <a href="ident?i=key">key</a>, <a href="ident?i=l">l</a>);
<a name="L1029" href="source/net/ipv4/fib_trie.c#L1029">1029</a>         <a href="ident?i=trie_rebalance">trie_rebalance</a>(<a href="ident?i=t">t</a>, <a href="ident?i=tp">tp</a>);
<a name="L1030" href="source/net/ipv4/fib_trie.c#L1030">1030</a> 
<a name="L1031" href="source/net/ipv4/fib_trie.c#L1031">1031</a>         return 0;
<a name="L1032" href="source/net/ipv4/fib_trie.c#L1032">1032</a> notnode:
<a name="L1033" href="source/net/ipv4/fib_trie.c#L1033">1033</a>         <a href="ident?i=node_free">node_free</a>(<a href="ident?i=l">l</a>);
<a name="L1034" href="source/net/ipv4/fib_trie.c#L1034">1034</a> noleaf:
<a name="L1035" href="source/net/ipv4/fib_trie.c#L1035">1035</a>         return -<a href="ident?i=ENOMEM">ENOMEM</a>;
<a name="L1036" href="source/net/ipv4/fib_trie.c#L1036">1036</a> }
<a name="L1037" href="source/net/ipv4/fib_trie.c#L1037">1037</a> 
<a name="L1038" href="source/net/ipv4/fib_trie.c#L1038">1038</a> static int <a href="ident?i=fib_insert_alias">fib_insert_alias</a>(struct <a href="ident?i=trie">trie</a> *<a href="ident?i=t">t</a>, struct <a href="ident?i=key_vector">key_vector</a> *<a href="ident?i=tp">tp</a>,
<a name="L1039" href="source/net/ipv4/fib_trie.c#L1039">1039</a>                             struct <a href="ident?i=key_vector">key_vector</a> *<a href="ident?i=l">l</a>, struct <a href="ident?i=fib_alias">fib_alias</a> *<a href="ident?i=new">new</a>,
<a name="L1040" href="source/net/ipv4/fib_trie.c#L1040">1040</a>                             struct <a href="ident?i=fib_alias">fib_alias</a> *fa, <a href="ident?i=t_key">t_key</a> <a href="ident?i=key">key</a>)
<a name="L1041" href="source/net/ipv4/fib_trie.c#L1041">1041</a> {
<a name="L1042" href="source/net/ipv4/fib_trie.c#L1042">1042</a>         if (!<a href="ident?i=l">l</a>)
<a name="L1043" href="source/net/ipv4/fib_trie.c#L1043">1043</a>                 return <a href="ident?i=fib_insert_node">fib_insert_node</a>(<a href="ident?i=t">t</a>, <a href="ident?i=tp">tp</a>, <a href="ident?i=new">new</a>, <a href="ident?i=key">key</a>);
<a name="L1044" href="source/net/ipv4/fib_trie.c#L1044">1044</a> 
<a name="L1045" href="source/net/ipv4/fib_trie.c#L1045">1045</a>         if (fa) {
<a name="L1046" href="source/net/ipv4/fib_trie.c#L1046">1046</a>                 <a href="ident?i=hlist_add_before_rcu">hlist_add_before_rcu</a>(&amp;<a href="ident?i=new">new</a>-&gt;fa_list, &amp;fa-&gt;fa_list);
<a name="L1047" href="source/net/ipv4/fib_trie.c#L1047">1047</a>         } else {
<a name="L1048" href="source/net/ipv4/fib_trie.c#L1048">1048</a>                 struct <a href="ident?i=fib_alias">fib_alias</a> *<a href="ident?i=last">last</a>;
<a name="L1049" href="source/net/ipv4/fib_trie.c#L1049">1049</a> 
<a name="L1050" href="source/net/ipv4/fib_trie.c#L1050">1050</a>                 <a href="ident?i=hlist_for_each_entry">hlist_for_each_entry</a>(<a href="ident?i=last">last</a>, &amp;<a href="ident?i=l">l</a>-&gt;leaf, fa_list) {
<a name="L1051" href="source/net/ipv4/fib_trie.c#L1051">1051</a>                         if (<a href="ident?i=new">new</a>-&gt;fa_slen &lt; <a href="ident?i=last">last</a>-&gt;fa_slen)
<a name="L1052" href="source/net/ipv4/fib_trie.c#L1052">1052</a>                                 break;
<a name="L1053" href="source/net/ipv4/fib_trie.c#L1053">1053</a>                         if ((<a href="ident?i=new">new</a>-&gt;fa_slen == <a href="ident?i=last">last</a>-&gt;fa_slen) &amp;&amp;
<a name="L1054" href="source/net/ipv4/fib_trie.c#L1054">1054</a>                             (<a href="ident?i=new">new</a>-&gt;tb_id &gt; <a href="ident?i=last">last</a>-&gt;tb_id))
<a name="L1055" href="source/net/ipv4/fib_trie.c#L1055">1055</a>                                 break;
<a name="L1056" href="source/net/ipv4/fib_trie.c#L1056">1056</a>                         fa = <a href="ident?i=last">last</a>;
<a name="L1057" href="source/net/ipv4/fib_trie.c#L1057">1057</a>                 }
<a name="L1058" href="source/net/ipv4/fib_trie.c#L1058">1058</a> 
<a name="L1059" href="source/net/ipv4/fib_trie.c#L1059">1059</a>                 if (fa)
<a name="L1060" href="source/net/ipv4/fib_trie.c#L1060">1060</a>                         <a href="ident?i=hlist_add_behind_rcu">hlist_add_behind_rcu</a>(&amp;<a href="ident?i=new">new</a>-&gt;fa_list, &amp;fa-&gt;fa_list);
<a name="L1061" href="source/net/ipv4/fib_trie.c#L1061">1061</a>                 else
<a name="L1062" href="source/net/ipv4/fib_trie.c#L1062">1062</a>                         <a href="ident?i=hlist_add_head_rcu">hlist_add_head_rcu</a>(&amp;<a href="ident?i=new">new</a>-&gt;fa_list, &amp;<a href="ident?i=l">l</a>-&gt;leaf);
<a name="L1063" href="source/net/ipv4/fib_trie.c#L1063">1063</a>         }
<a name="L1064" href="source/net/ipv4/fib_trie.c#L1064">1064</a> 
<a name="L1065" href="source/net/ipv4/fib_trie.c#L1065">1065</a>         <b><i>/* if we added to the tail node then we need to update slen */</i></b>
<a name="L1066" href="source/net/ipv4/fib_trie.c#L1066">1066</a>         if (<a href="ident?i=l">l</a>-&gt;slen &lt; <a href="ident?i=new">new</a>-&gt;fa_slen) {
<a name="L1067" href="source/net/ipv4/fib_trie.c#L1067">1067</a>                 <a href="ident?i=l">l</a>-&gt;slen = <a href="ident?i=new">new</a>-&gt;fa_slen;
<a name="L1068" href="source/net/ipv4/fib_trie.c#L1068">1068</a>                 <a href="ident?i=leaf_push_suffix">leaf_push_suffix</a>(<a href="ident?i=tp">tp</a>, <a href="ident?i=l">l</a>);
<a name="L1069" href="source/net/ipv4/fib_trie.c#L1069">1069</a>         }
<a name="L1070" href="source/net/ipv4/fib_trie.c#L1070">1070</a> 
<a name="L1071" href="source/net/ipv4/fib_trie.c#L1071">1071</a>         return 0;
<a name="L1072" href="source/net/ipv4/fib_trie.c#L1072">1072</a> }
<a name="L1073" href="source/net/ipv4/fib_trie.c#L1073">1073</a> 
<a name="L1074" href="source/net/ipv4/fib_trie.c#L1074">1074</a> <b><i>/* Caller must hold RTNL. */</i></b>
<a name="L1075" href="source/net/ipv4/fib_trie.c#L1075">1075</a> int <a href="ident?i=fib_table_insert">fib_table_insert</a>(struct <a href="ident?i=fib_table">fib_table</a> *<a href="ident?i=tb">tb</a>, struct <a href="ident?i=fib_config">fib_config</a> *<a href="ident?i=cfg">cfg</a>)
<a name="L1076" href="source/net/ipv4/fib_trie.c#L1076">1076</a> {
<a name="L1077" href="source/net/ipv4/fib_trie.c#L1077">1077</a>         struct <a href="ident?i=trie">trie</a> *<a href="ident?i=t">t</a> = (struct <a href="ident?i=trie">trie</a> *)<a href="ident?i=tb">tb</a>-&gt;tb_data;
<a name="L1078" href="source/net/ipv4/fib_trie.c#L1078">1078</a>         struct <a href="ident?i=fib_alias">fib_alias</a> *fa, *new_fa;
<a name="L1079" href="source/net/ipv4/fib_trie.c#L1079">1079</a>         struct <a href="ident?i=key_vector">key_vector</a> *<a href="ident?i=l">l</a>, *<a href="ident?i=tp">tp</a>;
<a name="L1080" href="source/net/ipv4/fib_trie.c#L1080">1080</a>         struct <a href="ident?i=fib_info">fib_info</a> *fi;
<a name="L1081" href="source/net/ipv4/fib_trie.c#L1081">1081</a>         <a href="ident?i=u8">u8</a> plen = <a href="ident?i=cfg">cfg</a>-&gt;fc_dst_len;
<a name="L1082" href="source/net/ipv4/fib_trie.c#L1082">1082</a>         <a href="ident?i=u8">u8</a> slen = <a href="ident?i=KEYLENGTH">KEYLENGTH</a> - plen;
<a name="L1083" href="source/net/ipv4/fib_trie.c#L1083">1083</a>         <a href="ident?i=u8">u8</a> tos = <a href="ident?i=cfg">cfg</a>-&gt;fc_tos;
<a name="L1084" href="source/net/ipv4/fib_trie.c#L1084">1084</a>         <a href="ident?i=u32">u32</a> <a href="ident?i=key">key</a>;
<a name="L1085" href="source/net/ipv4/fib_trie.c#L1085">1085</a>         int <a href="ident?i=err">err</a>;
<a name="L1086" href="source/net/ipv4/fib_trie.c#L1086">1086</a> 
<a name="L1087" href="source/net/ipv4/fib_trie.c#L1087">1087</a>         if (plen &gt; <a href="ident?i=KEYLENGTH">KEYLENGTH</a>)
<a name="L1088" href="source/net/ipv4/fib_trie.c#L1088">1088</a>                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L1089" href="source/net/ipv4/fib_trie.c#L1089">1089</a> 
<a name="L1090" href="source/net/ipv4/fib_trie.c#L1090">1090</a>         <a href="ident?i=key">key</a> = <a href="ident?i=ntohl">ntohl</a>(<a href="ident?i=cfg">cfg</a>-&gt;fc_dst);
<a name="L1091" href="source/net/ipv4/fib_trie.c#L1091">1091</a> 
<a name="L1092" href="source/net/ipv4/fib_trie.c#L1092">1092</a>         <a href="ident?i=pr_debug">pr_debug</a>(<i>"Insert table=%u %08x/%d\n"</i>, <a href="ident?i=tb">tb</a>-&gt;tb_id, <a href="ident?i=key">key</a>, plen);
<a name="L1093" href="source/net/ipv4/fib_trie.c#L1093">1093</a> 
<a name="L1094" href="source/net/ipv4/fib_trie.c#L1094">1094</a>         if ((plen &lt; <a href="ident?i=KEYLENGTH">KEYLENGTH</a>) &amp;&amp; (<a href="ident?i=key">key</a> &lt;&lt; plen))
<a name="L1095" href="source/net/ipv4/fib_trie.c#L1095">1095</a>                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L1096" href="source/net/ipv4/fib_trie.c#L1096">1096</a> 
<a name="L1097" href="source/net/ipv4/fib_trie.c#L1097">1097</a>         fi = <a href="ident?i=fib_create_info">fib_create_info</a>(<a href="ident?i=cfg">cfg</a>);
<a name="L1098" href="source/net/ipv4/fib_trie.c#L1098">1098</a>         if (<a href="ident?i=IS_ERR">IS_ERR</a>(fi)) {
<a name="L1099" href="source/net/ipv4/fib_trie.c#L1099">1099</a>                 <a href="ident?i=err">err</a> = <a href="ident?i=PTR_ERR">PTR_ERR</a>(fi);
<a name="L1100" href="source/net/ipv4/fib_trie.c#L1100">1100</a>                 goto <a href="ident?i=err">err</a>;
<a name="L1101" href="source/net/ipv4/fib_trie.c#L1101">1101</a>         }
<a name="L1102" href="source/net/ipv4/fib_trie.c#L1102">1102</a> 
<a name="L1103" href="source/net/ipv4/fib_trie.c#L1103">1103</a>         <a href="ident?i=l">l</a> = <a href="ident?i=fib_find_node">fib_find_node</a>(<a href="ident?i=t">t</a>, &amp;<a href="ident?i=tp">tp</a>, <a href="ident?i=key">key</a>);
<a name="L1104" href="source/net/ipv4/fib_trie.c#L1104">1104</a>         fa = <a href="ident?i=l">l</a> ? <a href="ident?i=fib_find_alias">fib_find_alias</a>(&amp;<a href="ident?i=l">l</a>-&gt;leaf, slen, tos, fi-&gt;fib_priority,
<a name="L1105" href="source/net/ipv4/fib_trie.c#L1105">1105</a>                                 <a href="ident?i=tb">tb</a>-&gt;tb_id) : <a href="ident?i=NULL">NULL</a>;
<a name="L1106" href="source/net/ipv4/fib_trie.c#L1106">1106</a> 
<a name="L1107" href="source/net/ipv4/fib_trie.c#L1107">1107</a>         <b><i>/* Now fa, if non-NULL, points to the first fib alias</i></b>
<a name="L1108" href="source/net/ipv4/fib_trie.c#L1108">1108</a> <b><i>         * with the same keys [prefix,tos,priority], if such key already</i></b>
<a name="L1109" href="source/net/ipv4/fib_trie.c#L1109">1109</a> <b><i>         * exists or to the node before which we will insert new one.</i></b>
<a name="L1110" href="source/net/ipv4/fib_trie.c#L1110">1110</a> <b><i>         *</i></b>
<a name="L1111" href="source/net/ipv4/fib_trie.c#L1111">1111</a> <b><i>         * If fa is NULL, we will need to allocate a new one and</i></b>
<a name="L1112" href="source/net/ipv4/fib_trie.c#L1112">1112</a> <b><i>         * insert to the tail of the section matching the suffix length</i></b>
<a name="L1113" href="source/net/ipv4/fib_trie.c#L1113">1113</a> <b><i>         * of the new alias.</i></b>
<a name="L1114" href="source/net/ipv4/fib_trie.c#L1114">1114</a> <b><i>         */</i></b>
<a name="L1115" href="source/net/ipv4/fib_trie.c#L1115">1115</a> 
<a name="L1116" href="source/net/ipv4/fib_trie.c#L1116">1116</a>         if (fa &amp;&amp; fa-&gt;fa_tos == tos &amp;&amp;
<a name="L1117" href="source/net/ipv4/fib_trie.c#L1117">1117</a>             fa-&gt;fa_info-&gt;fib_priority == fi-&gt;fib_priority) {
<a name="L1118" href="source/net/ipv4/fib_trie.c#L1118">1118</a>                 struct <a href="ident?i=fib_alias">fib_alias</a> *fa_first, *fa_match;
<a name="L1119" href="source/net/ipv4/fib_trie.c#L1119">1119</a> 
<a name="L1120" href="source/net/ipv4/fib_trie.c#L1120">1120</a>                 <a href="ident?i=err">err</a> = -<a href="ident?i=EEXIST">EEXIST</a>;
<a name="L1121" href="source/net/ipv4/fib_trie.c#L1121">1121</a>                 if (<a href="ident?i=cfg">cfg</a>-&gt;fc_nlflags &amp; <a href="ident?i=NLM_F_EXCL">NLM_F_EXCL</a>)
<a name="L1122" href="source/net/ipv4/fib_trie.c#L1122">1122</a>                         goto <a href="ident?i=out">out</a>;
<a name="L1123" href="source/net/ipv4/fib_trie.c#L1123">1123</a> 
<a name="L1124" href="source/net/ipv4/fib_trie.c#L1124">1124</a>                 <b><i>/* We have 2 goals:</i></b>
<a name="L1125" href="source/net/ipv4/fib_trie.c#L1125">1125</a> <b><i>                 * 1. Find exact match for type, scope, fib_info to avoid</i></b>
<a name="L1126" href="source/net/ipv4/fib_trie.c#L1126">1126</a> <b><i>                 * duplicate routes</i></b>
<a name="L1127" href="source/net/ipv4/fib_trie.c#L1127">1127</a> <b><i>                 * 2. Find next 'fa' (or head), NLM_F_APPEND inserts before it</i></b>
<a name="L1128" href="source/net/ipv4/fib_trie.c#L1128">1128</a> <b><i>                 */</i></b>
<a name="L1129" href="source/net/ipv4/fib_trie.c#L1129">1129</a>                 fa_match = <a href="ident?i=NULL">NULL</a>;
<a name="L1130" href="source/net/ipv4/fib_trie.c#L1130">1130</a>                 fa_first = fa;
<a name="L1131" href="source/net/ipv4/fib_trie.c#L1131">1131</a>                 <a href="ident?i=hlist_for_each_entry_from">hlist_for_each_entry_from</a>(fa, fa_list) {
<a name="L1132" href="source/net/ipv4/fib_trie.c#L1132">1132</a>                         if ((fa-&gt;fa_slen != slen) ||
<a name="L1133" href="source/net/ipv4/fib_trie.c#L1133">1133</a>                             (fa-&gt;tb_id != <a href="ident?i=tb">tb</a>-&gt;tb_id) ||
<a name="L1134" href="source/net/ipv4/fib_trie.c#L1134">1134</a>                             (fa-&gt;fa_tos != tos))
<a name="L1135" href="source/net/ipv4/fib_trie.c#L1135">1135</a>                                 break;
<a name="L1136" href="source/net/ipv4/fib_trie.c#L1136">1136</a>                         if (fa-&gt;fa_info-&gt;fib_priority != fi-&gt;fib_priority)
<a name="L1137" href="source/net/ipv4/fib_trie.c#L1137">1137</a>                                 break;
<a name="L1138" href="source/net/ipv4/fib_trie.c#L1138">1138</a>                         if (fa-&gt;fa_type == <a href="ident?i=cfg">cfg</a>-&gt;<a href="ident?i=fc_type">fc_type</a> &amp;&amp;
<a name="L1139" href="source/net/ipv4/fib_trie.c#L1139">1139</a>                             fa-&gt;fa_info == fi) {
<a name="L1140" href="source/net/ipv4/fib_trie.c#L1140">1140</a>                                 fa_match = fa;
<a name="L1141" href="source/net/ipv4/fib_trie.c#L1141">1141</a>                                 break;
<a name="L1142" href="source/net/ipv4/fib_trie.c#L1142">1142</a>                         }
<a name="L1143" href="source/net/ipv4/fib_trie.c#L1143">1143</a>                 }
<a name="L1144" href="source/net/ipv4/fib_trie.c#L1144">1144</a> 
<a name="L1145" href="source/net/ipv4/fib_trie.c#L1145">1145</a>                 if (<a href="ident?i=cfg">cfg</a>-&gt;fc_nlflags &amp; <a href="ident?i=NLM_F_REPLACE">NLM_F_REPLACE</a>) {
<a name="L1146" href="source/net/ipv4/fib_trie.c#L1146">1146</a>                         struct <a href="ident?i=fib_info">fib_info</a> *fi_drop;
<a name="L1147" href="source/net/ipv4/fib_trie.c#L1147">1147</a>                         <a href="ident?i=u8">u8</a> <a href="ident?i=state">state</a>;
<a name="L1148" href="source/net/ipv4/fib_trie.c#L1148">1148</a> 
<a name="L1149" href="source/net/ipv4/fib_trie.c#L1149">1149</a>                         fa = fa_first;
<a name="L1150" href="source/net/ipv4/fib_trie.c#L1150">1150</a>                         if (fa_match) {
<a name="L1151" href="source/net/ipv4/fib_trie.c#L1151">1151</a>                                 if (fa == fa_match)
<a name="L1152" href="source/net/ipv4/fib_trie.c#L1152">1152</a>                                         <a href="ident?i=err">err</a> = 0;
<a name="L1153" href="source/net/ipv4/fib_trie.c#L1153">1153</a>                                 goto <a href="ident?i=out">out</a>;
<a name="L1154" href="source/net/ipv4/fib_trie.c#L1154">1154</a>                         }
<a name="L1155" href="source/net/ipv4/fib_trie.c#L1155">1155</a>                         <a href="ident?i=err">err</a> = -<a href="ident?i=ENOBUFS">ENOBUFS</a>;
<a name="L1156" href="source/net/ipv4/fib_trie.c#L1156">1156</a>                         new_fa = <a href="ident?i=kmem_cache_alloc">kmem_cache_alloc</a>(fn_alias_kmem, <a href="ident?i=GFP_KERNEL">GFP_KERNEL</a>);
<a name="L1157" href="source/net/ipv4/fib_trie.c#L1157">1157</a>                         if (!new_fa)
<a name="L1158" href="source/net/ipv4/fib_trie.c#L1158">1158</a>                                 goto <a href="ident?i=out">out</a>;
<a name="L1159" href="source/net/ipv4/fib_trie.c#L1159">1159</a> 
<a name="L1160" href="source/net/ipv4/fib_trie.c#L1160">1160</a>                         fi_drop = fa-&gt;fa_info;
<a name="L1161" href="source/net/ipv4/fib_trie.c#L1161">1161</a>                         new_fa-&gt;fa_tos = fa-&gt;fa_tos;
<a name="L1162" href="source/net/ipv4/fib_trie.c#L1162">1162</a>                         new_fa-&gt;fa_info = fi;
<a name="L1163" href="source/net/ipv4/fib_trie.c#L1163">1163</a>                         new_fa-&gt;fa_type = <a href="ident?i=cfg">cfg</a>-&gt;<a href="ident?i=fc_type">fc_type</a>;
<a name="L1164" href="source/net/ipv4/fib_trie.c#L1164">1164</a>                         <a href="ident?i=state">state</a> = fa-&gt;fa_state;
<a name="L1165" href="source/net/ipv4/fib_trie.c#L1165">1165</a>                         new_fa-&gt;fa_state = <a href="ident?i=state">state</a> &amp; ~FA_S_ACCESSED;
<a name="L1166" href="source/net/ipv4/fib_trie.c#L1166">1166</a>                         new_fa-&gt;fa_slen = fa-&gt;fa_slen;
<a name="L1167" href="source/net/ipv4/fib_trie.c#L1167">1167</a>                         new_fa-&gt;tb_id = <a href="ident?i=tb">tb</a>-&gt;tb_id;
<a name="L1168" href="source/net/ipv4/fib_trie.c#L1168">1168</a> 
<a name="L1169" href="source/net/ipv4/fib_trie.c#L1169">1169</a>                         <a href="ident?i=err">err</a> = <a href="ident?i=netdev_switch_fib_ipv4_add">netdev_switch_fib_ipv4_add</a>(<a href="ident?i=key">key</a>, plen, fi,
<a name="L1170" href="source/net/ipv4/fib_trie.c#L1170">1170</a>                                                          new_fa-&gt;fa_tos,
<a name="L1171" href="source/net/ipv4/fib_trie.c#L1171">1171</a>                                                          <a href="ident?i=cfg">cfg</a>-&gt;<a href="ident?i=fc_type">fc_type</a>,
<a name="L1172" href="source/net/ipv4/fib_trie.c#L1172">1172</a>                                                          <a href="ident?i=cfg">cfg</a>-&gt;fc_nlflags,
<a name="L1173" href="source/net/ipv4/fib_trie.c#L1173">1173</a>                                                          <a href="ident?i=tb">tb</a>-&gt;tb_id);
<a name="L1174" href="source/net/ipv4/fib_trie.c#L1174">1174</a>                         if (<a href="ident?i=err">err</a>) {
<a name="L1175" href="source/net/ipv4/fib_trie.c#L1175">1175</a>                                 <a href="ident?i=netdev_switch_fib_ipv4_abort">netdev_switch_fib_ipv4_abort</a>(fi);
<a name="L1176" href="source/net/ipv4/fib_trie.c#L1176">1176</a>                                 <a href="ident?i=kmem_cache_free">kmem_cache_free</a>(fn_alias_kmem, new_fa);
<a name="L1177" href="source/net/ipv4/fib_trie.c#L1177">1177</a>                                 goto <a href="ident?i=out">out</a>;
<a name="L1178" href="source/net/ipv4/fib_trie.c#L1178">1178</a>                         }
<a name="L1179" href="source/net/ipv4/fib_trie.c#L1179">1179</a> 
<a name="L1180" href="source/net/ipv4/fib_trie.c#L1180">1180</a>                         <a href="ident?i=hlist_replace_rcu">hlist_replace_rcu</a>(&amp;fa-&gt;fa_list, &amp;new_fa-&gt;fa_list);
<a name="L1181" href="source/net/ipv4/fib_trie.c#L1181">1181</a> 
<a name="L1182" href="source/net/ipv4/fib_trie.c#L1182">1182</a>                         <a href="ident?i=alias_free_mem_rcu">alias_free_mem_rcu</a>(fa);
<a name="L1183" href="source/net/ipv4/fib_trie.c#L1183">1183</a> 
<a name="L1184" href="source/net/ipv4/fib_trie.c#L1184">1184</a>                         <a href="ident?i=fib_release_info">fib_release_info</a>(fi_drop);
<a name="L1185" href="source/net/ipv4/fib_trie.c#L1185">1185</a>                         if (<a href="ident?i=state">state</a> &amp; <a href="ident?i=FA_S_ACCESSED">FA_S_ACCESSED</a>)
<a name="L1186" href="source/net/ipv4/fib_trie.c#L1186">1186</a>                                 <a href="ident?i=rt_cache_flush">rt_cache_flush</a>(<a href="ident?i=cfg">cfg</a>-&gt;fc_nlinfo.nl_net);
<a name="L1187" href="source/net/ipv4/fib_trie.c#L1187">1187</a>                         <a href="ident?i=rtmsg_fib">rtmsg_fib</a>(<a href="ident?i=RTM_NEWROUTE">RTM_NEWROUTE</a>, <a href="ident?i=htonl">htonl</a>(<a href="ident?i=key">key</a>), new_fa, plen,
<a name="L1188" href="source/net/ipv4/fib_trie.c#L1188">1188</a>                                 <a href="ident?i=tb">tb</a>-&gt;tb_id, &amp;<a href="ident?i=cfg">cfg</a>-&gt;fc_nlinfo, <a href="ident?i=NLM_F_REPLACE">NLM_F_REPLACE</a>);
<a name="L1189" href="source/net/ipv4/fib_trie.c#L1189">1189</a> 
<a name="L1190" href="source/net/ipv4/fib_trie.c#L1190">1190</a>                         goto succeeded;
<a name="L1191" href="source/net/ipv4/fib_trie.c#L1191">1191</a>                 }
<a name="L1192" href="source/net/ipv4/fib_trie.c#L1192">1192</a>                 <b><i>/* Error if we find a perfect match which</i></b>
<a name="L1193" href="source/net/ipv4/fib_trie.c#L1193">1193</a> <b><i>                 * uses the same scope, type, and nexthop</i></b>
<a name="L1194" href="source/net/ipv4/fib_trie.c#L1194">1194</a> <b><i>                 * information.</i></b>
<a name="L1195" href="source/net/ipv4/fib_trie.c#L1195">1195</a> <b><i>                 */</i></b>
<a name="L1196" href="source/net/ipv4/fib_trie.c#L1196">1196</a>                 if (fa_match)
<a name="L1197" href="source/net/ipv4/fib_trie.c#L1197">1197</a>                         goto <a href="ident?i=out">out</a>;
<a name="L1198" href="source/net/ipv4/fib_trie.c#L1198">1198</a> 
<a name="L1199" href="source/net/ipv4/fib_trie.c#L1199">1199</a>                 if (!(<a href="ident?i=cfg">cfg</a>-&gt;fc_nlflags &amp; <a href="ident?i=NLM_F_APPEND">NLM_F_APPEND</a>))
<a name="L1200" href="source/net/ipv4/fib_trie.c#L1200">1200</a>                         fa = fa_first;
<a name="L1201" href="source/net/ipv4/fib_trie.c#L1201">1201</a>         }
<a name="L1202" href="source/net/ipv4/fib_trie.c#L1202">1202</a>         <a href="ident?i=err">err</a> = -<a href="ident?i=ENOENT">ENOENT</a>;
<a name="L1203" href="source/net/ipv4/fib_trie.c#L1203">1203</a>         if (!(<a href="ident?i=cfg">cfg</a>-&gt;fc_nlflags &amp; <a href="ident?i=NLM_F_CREATE">NLM_F_CREATE</a>))
<a name="L1204" href="source/net/ipv4/fib_trie.c#L1204">1204</a>                 goto <a href="ident?i=out">out</a>;
<a name="L1205" href="source/net/ipv4/fib_trie.c#L1205">1205</a> 
<a name="L1206" href="source/net/ipv4/fib_trie.c#L1206">1206</a>         <a href="ident?i=err">err</a> = -<a href="ident?i=ENOBUFS">ENOBUFS</a>;
<a name="L1207" href="source/net/ipv4/fib_trie.c#L1207">1207</a>         new_fa = <a href="ident?i=kmem_cache_alloc">kmem_cache_alloc</a>(fn_alias_kmem, <a href="ident?i=GFP_KERNEL">GFP_KERNEL</a>);
<a name="L1208" href="source/net/ipv4/fib_trie.c#L1208">1208</a>         if (!new_fa)
<a name="L1209" href="source/net/ipv4/fib_trie.c#L1209">1209</a>                 goto <a href="ident?i=out">out</a>;
<a name="L1210" href="source/net/ipv4/fib_trie.c#L1210">1210</a> 
<a name="L1211" href="source/net/ipv4/fib_trie.c#L1211">1211</a>         new_fa-&gt;fa_info = fi;
<a name="L1212" href="source/net/ipv4/fib_trie.c#L1212">1212</a>         new_fa-&gt;fa_tos = tos;
<a name="L1213" href="source/net/ipv4/fib_trie.c#L1213">1213</a>         new_fa-&gt;fa_type = <a href="ident?i=cfg">cfg</a>-&gt;<a href="ident?i=fc_type">fc_type</a>;
<a name="L1214" href="source/net/ipv4/fib_trie.c#L1214">1214</a>         new_fa-&gt;fa_state = 0;
<a name="L1215" href="source/net/ipv4/fib_trie.c#L1215">1215</a>         new_fa-&gt;fa_slen = slen;
<a name="L1216" href="source/net/ipv4/fib_trie.c#L1216">1216</a>         new_fa-&gt;tb_id = <a href="ident?i=tb">tb</a>-&gt;tb_id;
<a name="L1217" href="source/net/ipv4/fib_trie.c#L1217">1217</a> 
<a name="L1218" href="source/net/ipv4/fib_trie.c#L1218">1218</a>         <b><i>/* (Optionally) offload fib entry to switch hardware. */</i></b>
<a name="L1219" href="source/net/ipv4/fib_trie.c#L1219">1219</a>         <a href="ident?i=err">err</a> = <a href="ident?i=netdev_switch_fib_ipv4_add">netdev_switch_fib_ipv4_add</a>(<a href="ident?i=key">key</a>, plen, fi, tos,
<a name="L1220" href="source/net/ipv4/fib_trie.c#L1220">1220</a>                                          <a href="ident?i=cfg">cfg</a>-&gt;<a href="ident?i=fc_type">fc_type</a>,
<a name="L1221" href="source/net/ipv4/fib_trie.c#L1221">1221</a>                                          <a href="ident?i=cfg">cfg</a>-&gt;fc_nlflags,
<a name="L1222" href="source/net/ipv4/fib_trie.c#L1222">1222</a>                                          <a href="ident?i=tb">tb</a>-&gt;tb_id);
<a name="L1223" href="source/net/ipv4/fib_trie.c#L1223">1223</a>         if (<a href="ident?i=err">err</a>) {
<a name="L1224" href="source/net/ipv4/fib_trie.c#L1224">1224</a>                 <a href="ident?i=netdev_switch_fib_ipv4_abort">netdev_switch_fib_ipv4_abort</a>(fi);
<a name="L1225" href="source/net/ipv4/fib_trie.c#L1225">1225</a>                 goto out_free_new_fa;
<a name="L1226" href="source/net/ipv4/fib_trie.c#L1226">1226</a>         }
<a name="L1227" href="source/net/ipv4/fib_trie.c#L1227">1227</a> 
<a name="L1228" href="source/net/ipv4/fib_trie.c#L1228">1228</a>         <b><i>/* Insert new entry to the list. */</i></b>
<a name="L1229" href="source/net/ipv4/fib_trie.c#L1229">1229</a>         <a href="ident?i=err">err</a> = <a href="ident?i=fib_insert_alias">fib_insert_alias</a>(<a href="ident?i=t">t</a>, <a href="ident?i=tp">tp</a>, <a href="ident?i=l">l</a>, new_fa, fa, <a href="ident?i=key">key</a>);
<a name="L1230" href="source/net/ipv4/fib_trie.c#L1230">1230</a>         if (<a href="ident?i=err">err</a>)
<a name="L1231" href="source/net/ipv4/fib_trie.c#L1231">1231</a>                 goto out_sw_fib_del;
<a name="L1232" href="source/net/ipv4/fib_trie.c#L1232">1232</a> 
<a name="L1233" href="source/net/ipv4/fib_trie.c#L1233">1233</a>         if (!plen)
<a name="L1234" href="source/net/ipv4/fib_trie.c#L1234">1234</a>                 <a href="ident?i=tb">tb</a>-&gt;tb_num_default++;
<a name="L1235" href="source/net/ipv4/fib_trie.c#L1235">1235</a> 
<a name="L1236" href="source/net/ipv4/fib_trie.c#L1236">1236</a>         <a href="ident?i=rt_cache_flush">rt_cache_flush</a>(<a href="ident?i=cfg">cfg</a>-&gt;fc_nlinfo.nl_net);
<a name="L1237" href="source/net/ipv4/fib_trie.c#L1237">1237</a>         <a href="ident?i=rtmsg_fib">rtmsg_fib</a>(<a href="ident?i=RTM_NEWROUTE">RTM_NEWROUTE</a>, <a href="ident?i=htonl">htonl</a>(<a href="ident?i=key">key</a>), new_fa, plen, new_fa-&gt;tb_id,
<a name="L1238" href="source/net/ipv4/fib_trie.c#L1238">1238</a>                   &amp;<a href="ident?i=cfg">cfg</a>-&gt;fc_nlinfo, 0);
<a name="L1239" href="source/net/ipv4/fib_trie.c#L1239">1239</a> succeeded:
<a name="L1240" href="source/net/ipv4/fib_trie.c#L1240">1240</a>         return 0;
<a name="L1241" href="source/net/ipv4/fib_trie.c#L1241">1241</a> 
<a name="L1242" href="source/net/ipv4/fib_trie.c#L1242">1242</a> out_sw_fib_del:
<a name="L1243" href="source/net/ipv4/fib_trie.c#L1243">1243</a>         <a href="ident?i=netdev_switch_fib_ipv4_del">netdev_switch_fib_ipv4_del</a>(<a href="ident?i=key">key</a>, plen, fi, tos, <a href="ident?i=cfg">cfg</a>-&gt;<a href="ident?i=fc_type">fc_type</a>, <a href="ident?i=tb">tb</a>-&gt;tb_id);
<a name="L1244" href="source/net/ipv4/fib_trie.c#L1244">1244</a> out_free_new_fa:
<a name="L1245" href="source/net/ipv4/fib_trie.c#L1245">1245</a>         <a href="ident?i=kmem_cache_free">kmem_cache_free</a>(fn_alias_kmem, new_fa);
<a name="L1246" href="source/net/ipv4/fib_trie.c#L1246">1246</a> <a href="ident?i=out">out</a>:
<a name="L1247" href="source/net/ipv4/fib_trie.c#L1247">1247</a>         <a href="ident?i=fib_release_info">fib_release_info</a>(fi);
<a name="L1248" href="source/net/ipv4/fib_trie.c#L1248">1248</a> <a href="ident?i=err">err</a>:
<a name="L1249" href="source/net/ipv4/fib_trie.c#L1249">1249</a>         return <a href="ident?i=err">err</a>;
<a name="L1250" href="source/net/ipv4/fib_trie.c#L1250">1250</a> }
<a name="L1251" href="source/net/ipv4/fib_trie.c#L1251">1251</a> 
<a name="L1252" href="source/net/ipv4/fib_trie.c#L1252">1252</a> static inline <a href="ident?i=t_key">t_key</a> <a href="ident?i=prefix_mismatch">prefix_mismatch</a>(<a href="ident?i=t_key">t_key</a> <a href="ident?i=key">key</a>, struct <a href="ident?i=key_vector">key_vector</a> *<a href="ident?i=n">n</a>)
<a name="L1253" href="source/net/ipv4/fib_trie.c#L1253">1253</a> {
<a name="L1254" href="source/net/ipv4/fib_trie.c#L1254">1254</a>         <a href="ident?i=t_key">t_key</a> <a href="ident?i=prefix">prefix</a> = <a href="ident?i=n">n</a>-&gt;<a href="ident?i=key">key</a>;
<a name="L1255" href="source/net/ipv4/fib_trie.c#L1255">1255</a> 
<a name="L1256" href="source/net/ipv4/fib_trie.c#L1256">1256</a>         return (<a href="ident?i=key">key</a> ^ <a href="ident?i=prefix">prefix</a>) &amp; (<a href="ident?i=prefix">prefix</a> | -<a href="ident?i=prefix">prefix</a>);
<a name="L1257" href="source/net/ipv4/fib_trie.c#L1257">1257</a> }
<a name="L1258" href="source/net/ipv4/fib_trie.c#L1258">1258</a> 
<a name="L1259" href="source/net/ipv4/fib_trie.c#L1259">1259</a> <b><i>/* should be called with rcu_read_lock */</i></b>
<a name="L1260" href="source/net/ipv4/fib_trie.c#L1260">1260</a> int <a href="ident?i=fib_table_lookup">fib_table_lookup</a>(struct <a href="ident?i=fib_table">fib_table</a> *<a href="ident?i=tb">tb</a>, const struct <a href="ident?i=flowi4">flowi4</a> *flp,
<a name="L1261" href="source/net/ipv4/fib_trie.c#L1261">1261</a>                      struct <a href="ident?i=fib_result">fib_result</a> *<a href="ident?i=res">res</a>, int fib_flags)
<a name="L1262" href="source/net/ipv4/fib_trie.c#L1262">1262</a> {
<a name="L1263" href="source/net/ipv4/fib_trie.c#L1263">1263</a>         struct <a href="ident?i=trie">trie</a> *<a href="ident?i=t">t</a> = (struct <a href="ident?i=trie">trie</a> *) <a href="ident?i=tb">tb</a>-&gt;tb_data;
<a name="L1264" href="source/net/ipv4/fib_trie.c#L1264">1264</a> #ifdef CONFIG_IP_FIB_TRIE_STATS
<a name="L1265" href="source/net/ipv4/fib_trie.c#L1265">1265</a>         struct <a href="ident?i=trie_use_stats">trie_use_stats</a> <a href="ident?i=__percpu">__percpu</a> *<a href="ident?i=stats">stats</a> = <a href="ident?i=t">t</a>-&gt;<a href="ident?i=stats">stats</a>;
<a name="L1266" href="source/net/ipv4/fib_trie.c#L1266">1266</a> #endif
<a name="L1267" href="source/net/ipv4/fib_trie.c#L1267">1267</a>         const <a href="ident?i=t_key">t_key</a> <a href="ident?i=key">key</a> = <a href="ident?i=ntohl">ntohl</a>(flp-&gt;<a href="ident?i=daddr">daddr</a>);
<a name="L1268" href="source/net/ipv4/fib_trie.c#L1268">1268</a>         struct <a href="ident?i=key_vector">key_vector</a> *<a href="ident?i=n">n</a>, *pn;
<a name="L1269" href="source/net/ipv4/fib_trie.c#L1269">1269</a>         struct <a href="ident?i=fib_alias">fib_alias</a> *fa;
<a name="L1270" href="source/net/ipv4/fib_trie.c#L1270">1270</a>         unsigned long <a href="ident?i=index">index</a>;
<a name="L1271" href="source/net/ipv4/fib_trie.c#L1271">1271</a>         <a href="ident?i=t_key">t_key</a> cindex;
<a name="L1272" href="source/net/ipv4/fib_trie.c#L1272">1272</a> 
<a name="L1273" href="source/net/ipv4/fib_trie.c#L1273">1273</a>         pn = <a href="ident?i=t">t</a>-&gt;kv;
<a name="L1274" href="source/net/ipv4/fib_trie.c#L1274">1274</a>         cindex = 0;
<a name="L1275" href="source/net/ipv4/fib_trie.c#L1275">1275</a> 
<a name="L1276" href="source/net/ipv4/fib_trie.c#L1276">1276</a>         <a href="ident?i=n">n</a> = <a href="ident?i=get_child_rcu">get_child_rcu</a>(pn, cindex);
<a name="L1277" href="source/net/ipv4/fib_trie.c#L1277">1277</a>         if (!<a href="ident?i=n">n</a>)
<a name="L1278" href="source/net/ipv4/fib_trie.c#L1278">1278</a>                 return -<a href="ident?i=EAGAIN">EAGAIN</a>;
<a name="L1279" href="source/net/ipv4/fib_trie.c#L1279">1279</a> 
<a name="L1280" href="source/net/ipv4/fib_trie.c#L1280">1280</a> #ifdef CONFIG_IP_FIB_TRIE_STATS
<a name="L1281" href="source/net/ipv4/fib_trie.c#L1281">1281</a>         <a href="ident?i=this_cpu_inc">this_cpu_inc</a>(<a href="ident?i=stats">stats</a>-&gt;gets);
<a name="L1282" href="source/net/ipv4/fib_trie.c#L1282">1282</a> #endif
<a name="L1283" href="source/net/ipv4/fib_trie.c#L1283">1283</a> 
<a name="L1284" href="source/net/ipv4/fib_trie.c#L1284">1284</a>         <b><i>/* Step 1: Travel to the longest prefix match in the trie */</i></b>
<a name="L1285" href="source/net/ipv4/fib_trie.c#L1285">1285</a>         for (;;) {
<a name="L1286" href="source/net/ipv4/fib_trie.c#L1286">1286</a>                 <a href="ident?i=index">index</a> = <a href="ident?i=get_cindex">get_cindex</a>(<a href="ident?i=key">key</a>, <a href="ident?i=n">n</a>);
<a name="L1287" href="source/net/ipv4/fib_trie.c#L1287">1287</a> 
<a name="L1288" href="source/net/ipv4/fib_trie.c#L1288">1288</a>                 <b><i>/* This bit of code is a bit tricky but it combines multiple</i></b>
<a name="L1289" href="source/net/ipv4/fib_trie.c#L1289">1289</a> <b><i>                 * checks into a single check.  The prefix consists of the</i></b>
<a name="L1290" href="source/net/ipv4/fib_trie.c#L1290">1290</a> <b><i>                 * prefix plus zeros for the "bits" in the prefix. The index</i></b>
<a name="L1291" href="source/net/ipv4/fib_trie.c#L1291">1291</a> <b><i>                 * is the difference between the key and this value.  From</i></b>
<a name="L1292" href="source/net/ipv4/fib_trie.c#L1292">1292</a> <b><i>                 * this we can actually derive several pieces of data.</i></b>
<a name="L1293" href="source/net/ipv4/fib_trie.c#L1293">1293</a> <b><i>                 *   if (index &gt;= (1ul &lt;&lt; bits))</i></b>
<a name="L1294" href="source/net/ipv4/fib_trie.c#L1294">1294</a> <b><i>                 *     we have a mismatch in skip bits and failed</i></b>
<a name="L1295" href="source/net/ipv4/fib_trie.c#L1295">1295</a> <b><i>                 *   else</i></b>
<a name="L1296" href="source/net/ipv4/fib_trie.c#L1296">1296</a> <b><i>                 *     we know the value is cindex</i></b>
<a name="L1297" href="source/net/ipv4/fib_trie.c#L1297">1297</a> <b><i>                 *</i></b>
<a name="L1298" href="source/net/ipv4/fib_trie.c#L1298">1298</a> <b><i>                 * This check is safe even if bits == KEYLENGTH due to the</i></b>
<a name="L1299" href="source/net/ipv4/fib_trie.c#L1299">1299</a> <b><i>                 * fact that we can only allocate a node with 32 bits if a</i></b>
<a name="L1300" href="source/net/ipv4/fib_trie.c#L1300">1300</a> <b><i>                 * long is greater than 32 bits.</i></b>
<a name="L1301" href="source/net/ipv4/fib_trie.c#L1301">1301</a> <b><i>                 */</i></b>
<a name="L1302" href="source/net/ipv4/fib_trie.c#L1302">1302</a>                 if (<a href="ident?i=index">index</a> &gt;= (1ul &lt;&lt; <a href="ident?i=n">n</a>-&gt;<a href="ident?i=bits">bits</a>))
<a name="L1303" href="source/net/ipv4/fib_trie.c#L1303">1303</a>                         break;
<a name="L1304" href="source/net/ipv4/fib_trie.c#L1304">1304</a> 
<a name="L1305" href="source/net/ipv4/fib_trie.c#L1305">1305</a>                 <b><i>/* we have found a leaf. Prefixes have already been compared */</i></b>
<a name="L1306" href="source/net/ipv4/fib_trie.c#L1306">1306</a>                 if (<a href="ident?i=IS_LEAF">IS_LEAF</a>(<a href="ident?i=n">n</a>))
<a name="L1307" href="source/net/ipv4/fib_trie.c#L1307">1307</a>                         goto <a href="ident?i=found">found</a>;
<a name="L1308" href="source/net/ipv4/fib_trie.c#L1308">1308</a> 
<a name="L1309" href="source/net/ipv4/fib_trie.c#L1309">1309</a>                 <b><i>/* only record pn and cindex if we are going to be chopping</i></b>
<a name="L1310" href="source/net/ipv4/fib_trie.c#L1310">1310</a> <b><i>                 * bits later.  Otherwise we are just wasting cycles.</i></b>
<a name="L1311" href="source/net/ipv4/fib_trie.c#L1311">1311</a> <b><i>                 */</i></b>
<a name="L1312" href="source/net/ipv4/fib_trie.c#L1312">1312</a>                 if (<a href="ident?i=n">n</a>-&gt;slen &gt; <a href="ident?i=n">n</a>-&gt;<a href="ident?i=pos">pos</a>) {
<a name="L1313" href="source/net/ipv4/fib_trie.c#L1313">1313</a>                         pn = <a href="ident?i=n">n</a>;
<a name="L1314" href="source/net/ipv4/fib_trie.c#L1314">1314</a>                         cindex = <a href="ident?i=index">index</a>;
<a name="L1315" href="source/net/ipv4/fib_trie.c#L1315">1315</a>                 }
<a name="L1316" href="source/net/ipv4/fib_trie.c#L1316">1316</a> 
<a name="L1317" href="source/net/ipv4/fib_trie.c#L1317">1317</a>                 <a href="ident?i=n">n</a> = <a href="ident?i=get_child_rcu">get_child_rcu</a>(<a href="ident?i=n">n</a>, <a href="ident?i=index">index</a>);
<a name="L1318" href="source/net/ipv4/fib_trie.c#L1318">1318</a>                 if (<a href="ident?i=unlikely">unlikely</a>(!<a href="ident?i=n">n</a>))
<a name="L1319" href="source/net/ipv4/fib_trie.c#L1319">1319</a>                         goto <a href="ident?i=backtrace">backtrace</a>;
<a name="L1320" href="source/net/ipv4/fib_trie.c#L1320">1320</a>         }
<a name="L1321" href="source/net/ipv4/fib_trie.c#L1321">1321</a> 
<a name="L1322" href="source/net/ipv4/fib_trie.c#L1322">1322</a>         <b><i>/* Step 2: Sort out leaves and begin backtracing for longest prefix */</i></b>
<a name="L1323" href="source/net/ipv4/fib_trie.c#L1323">1323</a>         for (;;) {
<a name="L1324" href="source/net/ipv4/fib_trie.c#L1324">1324</a>                 <b><i>/* record the pointer where our next node pointer is stored */</i></b>
<a name="L1325" href="source/net/ipv4/fib_trie.c#L1325">1325</a>                 struct <a href="ident?i=key_vector">key_vector</a> <a href="ident?i=__rcu">__rcu</a> **cptr = <a href="ident?i=n">n</a>-&gt;<a href="ident?i=tnode">tnode</a>;
<a name="L1326" href="source/net/ipv4/fib_trie.c#L1326">1326</a> 
<a name="L1327" href="source/net/ipv4/fib_trie.c#L1327">1327</a>                 <b><i>/* This test verifies that none of the bits that differ</i></b>
<a name="L1328" href="source/net/ipv4/fib_trie.c#L1328">1328</a> <b><i>                 * between the key and the prefix exist in the region of</i></b>
<a name="L1329" href="source/net/ipv4/fib_trie.c#L1329">1329</a> <b><i>                 * the lsb and higher in the prefix.</i></b>
<a name="L1330" href="source/net/ipv4/fib_trie.c#L1330">1330</a> <b><i>                 */</i></b>
<a name="L1331" href="source/net/ipv4/fib_trie.c#L1331">1331</a>                 if (<a href="ident?i=unlikely">unlikely</a>(<a href="ident?i=prefix_mismatch">prefix_mismatch</a>(<a href="ident?i=key">key</a>, <a href="ident?i=n">n</a>)) || (<a href="ident?i=n">n</a>-&gt;slen == <a href="ident?i=n">n</a>-&gt;<a href="ident?i=pos">pos</a>))
<a name="L1332" href="source/net/ipv4/fib_trie.c#L1332">1332</a>                         goto <a href="ident?i=backtrace">backtrace</a>;
<a name="L1333" href="source/net/ipv4/fib_trie.c#L1333">1333</a> 
<a name="L1334" href="source/net/ipv4/fib_trie.c#L1334">1334</a>                 <b><i>/* exit out and process leaf */</i></b>
<a name="L1335" href="source/net/ipv4/fib_trie.c#L1335">1335</a>                 if (<a href="ident?i=unlikely">unlikely</a>(<a href="ident?i=IS_LEAF">IS_LEAF</a>(<a href="ident?i=n">n</a>)))
<a name="L1336" href="source/net/ipv4/fib_trie.c#L1336">1336</a>                         break;
<a name="L1337" href="source/net/ipv4/fib_trie.c#L1337">1337</a> 
<a name="L1338" href="source/net/ipv4/fib_trie.c#L1338">1338</a>                 <b><i>/* Don't bother recording parent info.  Since we are in</i></b>
<a name="L1339" href="source/net/ipv4/fib_trie.c#L1339">1339</a> <b><i>                 * prefix match mode we will have to come back to wherever</i></b>
<a name="L1340" href="source/net/ipv4/fib_trie.c#L1340">1340</a> <b><i>                 * we started this traversal anyway</i></b>
<a name="L1341" href="source/net/ipv4/fib_trie.c#L1341">1341</a> <b><i>                 */</i></b>
<a name="L1342" href="source/net/ipv4/fib_trie.c#L1342">1342</a> 
<a name="L1343" href="source/net/ipv4/fib_trie.c#L1343">1343</a>                 while ((<a href="ident?i=n">n</a> = <a href="ident?i=rcu_dereference">rcu_dereference</a>(*cptr)) == <a href="ident?i=NULL">NULL</a>) {
<a name="L1344" href="source/net/ipv4/fib_trie.c#L1344">1344</a> <a href="ident?i=backtrace">backtrace</a>:
<a name="L1345" href="source/net/ipv4/fib_trie.c#L1345">1345</a> #ifdef CONFIG_IP_FIB_TRIE_STATS
<a name="L1346" href="source/net/ipv4/fib_trie.c#L1346">1346</a>                         if (!<a href="ident?i=n">n</a>)
<a name="L1347" href="source/net/ipv4/fib_trie.c#L1347">1347</a>                                 <a href="ident?i=this_cpu_inc">this_cpu_inc</a>(<a href="ident?i=stats">stats</a>-&gt;null_node_hit);
<a name="L1348" href="source/net/ipv4/fib_trie.c#L1348">1348</a> #endif
<a name="L1349" href="source/net/ipv4/fib_trie.c#L1349">1349</a>                         <b><i>/* If we are at cindex 0 there are no more bits for</i></b>
<a name="L1350" href="source/net/ipv4/fib_trie.c#L1350">1350</a> <b><i>                         * us to strip at this level so we must ascend back</i></b>
<a name="L1351" href="source/net/ipv4/fib_trie.c#L1351">1351</a> <b><i>                         * up one level to see if there are any more bits to</i></b>
<a name="L1352" href="source/net/ipv4/fib_trie.c#L1352">1352</a> <b><i>                         * be stripped there.</i></b>
<a name="L1353" href="source/net/ipv4/fib_trie.c#L1353">1353</a> <b><i>                         */</i></b>
<a name="L1354" href="source/net/ipv4/fib_trie.c#L1354">1354</a>                         while (!cindex) {
<a name="L1355" href="source/net/ipv4/fib_trie.c#L1355">1355</a>                                 <a href="ident?i=t_key">t_key</a> pkey = pn-&gt;<a href="ident?i=key">key</a>;
<a name="L1356" href="source/net/ipv4/fib_trie.c#L1356">1356</a> 
<a name="L1357" href="source/net/ipv4/fib_trie.c#L1357">1357</a>                                 <b><i>/* If we don't have a parent then there is</i></b>
<a name="L1358" href="source/net/ipv4/fib_trie.c#L1358">1358</a> <b><i>                                 * nothing for us to do as we do not have any</i></b>
<a name="L1359" href="source/net/ipv4/fib_trie.c#L1359">1359</a> <b><i>                                 * further nodes to parse.</i></b>
<a name="L1360" href="source/net/ipv4/fib_trie.c#L1360">1360</a> <b><i>                                 */</i></b>
<a name="L1361" href="source/net/ipv4/fib_trie.c#L1361">1361</a>                                 if (<a href="ident?i=IS_TRIE">IS_TRIE</a>(pn))
<a name="L1362" href="source/net/ipv4/fib_trie.c#L1362">1362</a>                                         return -<a href="ident?i=EAGAIN">EAGAIN</a>;
<a name="L1363" href="source/net/ipv4/fib_trie.c#L1363">1363</a> #ifdef CONFIG_IP_FIB_TRIE_STATS
<a name="L1364" href="source/net/ipv4/fib_trie.c#L1364">1364</a>                                 <a href="ident?i=this_cpu_inc">this_cpu_inc</a>(<a href="ident?i=stats">stats</a>-&gt;backtrack);
<a name="L1365" href="source/net/ipv4/fib_trie.c#L1365">1365</a> #endif
<a name="L1366" href="source/net/ipv4/fib_trie.c#L1366">1366</a>                                 <b><i>/* Get Child's index */</i></b>
<a name="L1367" href="source/net/ipv4/fib_trie.c#L1367">1367</a>                                 pn = <a href="ident?i=node_parent_rcu">node_parent_rcu</a>(pn);
<a name="L1368" href="source/net/ipv4/fib_trie.c#L1368">1368</a>                                 cindex = <a href="ident?i=get_index">get_index</a>(pkey, pn);
<a name="L1369" href="source/net/ipv4/fib_trie.c#L1369">1369</a>                         }
<a name="L1370" href="source/net/ipv4/fib_trie.c#L1370">1370</a> 
<a name="L1371" href="source/net/ipv4/fib_trie.c#L1371">1371</a>                         <b><i>/* strip the least significant bit from the cindex */</i></b>
<a name="L1372" href="source/net/ipv4/fib_trie.c#L1372">1372</a>                         cindex &amp;= cindex - 1;
<a name="L1373" href="source/net/ipv4/fib_trie.c#L1373">1373</a> 
<a name="L1374" href="source/net/ipv4/fib_trie.c#L1374">1374</a>                         <b><i>/* grab pointer for next child node */</i></b>
<a name="L1375" href="source/net/ipv4/fib_trie.c#L1375">1375</a>                         cptr = &amp;pn-&gt;<a href="ident?i=tnode">tnode</a>[cindex];
<a name="L1376" href="source/net/ipv4/fib_trie.c#L1376">1376</a>                 }
<a name="L1377" href="source/net/ipv4/fib_trie.c#L1377">1377</a>         }
<a name="L1378" href="source/net/ipv4/fib_trie.c#L1378">1378</a> 
<a name="L1379" href="source/net/ipv4/fib_trie.c#L1379">1379</a> <a href="ident?i=found">found</a>:
<a name="L1380" href="source/net/ipv4/fib_trie.c#L1380">1380</a>         <b><i>/* this line carries forward the xor from earlier in the function */</i></b>
<a name="L1381" href="source/net/ipv4/fib_trie.c#L1381">1381</a>         <a href="ident?i=index">index</a> = <a href="ident?i=key">key</a> ^ <a href="ident?i=n">n</a>-&gt;<a href="ident?i=key">key</a>;
<a name="L1382" href="source/net/ipv4/fib_trie.c#L1382">1382</a> 
<a name="L1383" href="source/net/ipv4/fib_trie.c#L1383">1383</a>         <b><i>/* Step 3: Process the leaf, if that fails fall back to backtracing */</i></b>
<a name="L1384" href="source/net/ipv4/fib_trie.c#L1384">1384</a>         <a href="ident?i=hlist_for_each_entry_rcu">hlist_for_each_entry_rcu</a>(fa, &amp;<a href="ident?i=n">n</a>-&gt;leaf, fa_list) {
<a name="L1385" href="source/net/ipv4/fib_trie.c#L1385">1385</a>                 struct <a href="ident?i=fib_info">fib_info</a> *fi = fa-&gt;fa_info;
<a name="L1386" href="source/net/ipv4/fib_trie.c#L1386">1386</a>                 int nhsel, <a href="ident?i=err">err</a>;
<a name="L1387" href="source/net/ipv4/fib_trie.c#L1387">1387</a> 
<a name="L1388" href="source/net/ipv4/fib_trie.c#L1388">1388</a>                 if ((<a href="ident?i=index">index</a> &gt;= (1ul &lt;&lt; fa-&gt;fa_slen)) &amp;&amp;
<a name="L1389" href="source/net/ipv4/fib_trie.c#L1389">1389</a>                     ((<a href="ident?i=BITS_PER_LONG">BITS_PER_LONG</a> &gt; <a href="ident?i=KEYLENGTH">KEYLENGTH</a>) || (fa-&gt;fa_slen != <a href="ident?i=KEYLENGTH">KEYLENGTH</a>)))
<a name="L1390" href="source/net/ipv4/fib_trie.c#L1390">1390</a>                         continue;
<a name="L1391" href="source/net/ipv4/fib_trie.c#L1391">1391</a>                 if (fa-&gt;fa_tos &amp;&amp; fa-&gt;fa_tos != flp-&gt;<a href="ident?i=flowi4_tos">flowi4_tos</a>)
<a name="L1392" href="source/net/ipv4/fib_trie.c#L1392">1392</a>                         continue;
<a name="L1393" href="source/net/ipv4/fib_trie.c#L1393">1393</a>                 if (fi-&gt;fib_dead)
<a name="L1394" href="source/net/ipv4/fib_trie.c#L1394">1394</a>                         continue;
<a name="L1395" href="source/net/ipv4/fib_trie.c#L1395">1395</a>                 if (fa-&gt;fa_info-&gt;fib_scope &lt; flp-&gt;<a href="ident?i=flowi4_scope">flowi4_scope</a>)
<a name="L1396" href="source/net/ipv4/fib_trie.c#L1396">1396</a>                         continue;
<a name="L1397" href="source/net/ipv4/fib_trie.c#L1397">1397</a>                 <a href="ident?i=fib_alias_accessed">fib_alias_accessed</a>(fa);
<a name="L1398" href="source/net/ipv4/fib_trie.c#L1398">1398</a>                 <a href="ident?i=err">err</a> = <a href="ident?i=fib_props">fib_props</a>[fa-&gt;fa_type].<a href="ident?i=error">error</a>;
<a name="L1399" href="source/net/ipv4/fib_trie.c#L1399">1399</a>                 if (<a href="ident?i=unlikely">unlikely</a>(<a href="ident?i=err">err</a> &lt; 0)) {
<a name="L1400" href="source/net/ipv4/fib_trie.c#L1400">1400</a> #ifdef CONFIG_IP_FIB_TRIE_STATS
<a name="L1401" href="source/net/ipv4/fib_trie.c#L1401">1401</a>                         <a href="ident?i=this_cpu_inc">this_cpu_inc</a>(<a href="ident?i=stats">stats</a>-&gt;semantic_match_passed);
<a name="L1402" href="source/net/ipv4/fib_trie.c#L1402">1402</a> #endif
<a name="L1403" href="source/net/ipv4/fib_trie.c#L1403">1403</a>                         return <a href="ident?i=err">err</a>;
<a name="L1404" href="source/net/ipv4/fib_trie.c#L1404">1404</a>                 }
<a name="L1405" href="source/net/ipv4/fib_trie.c#L1405">1405</a>                 if (fi-&gt;fib_flags &amp; <a href="ident?i=RTNH_F_DEAD">RTNH_F_DEAD</a>)
<a name="L1406" href="source/net/ipv4/fib_trie.c#L1406">1406</a>                         continue;
<a name="L1407" href="source/net/ipv4/fib_trie.c#L1407">1407</a>                 for (nhsel = 0; nhsel &lt; fi-&gt;fib_nhs; nhsel++) {
<a name="L1408" href="source/net/ipv4/fib_trie.c#L1408">1408</a>                         const struct <a href="ident?i=fib_nh">fib_nh</a> *nh = &amp;fi-&gt;<a href="ident?i=fib_nh">fib_nh</a>[nhsel];
<a name="L1409" href="source/net/ipv4/fib_trie.c#L1409">1409</a> 
<a name="L1410" href="source/net/ipv4/fib_trie.c#L1410">1410</a>                         if (nh-&gt;nh_flags &amp; <a href="ident?i=RTNH_F_DEAD">RTNH_F_DEAD</a>)
<a name="L1411" href="source/net/ipv4/fib_trie.c#L1411">1411</a>                                 continue;
<a name="L1412" href="source/net/ipv4/fib_trie.c#L1412">1412</a>                         if (flp-&gt;<a href="ident?i=flowi4_oif">flowi4_oif</a> &amp;&amp; flp-&gt;<a href="ident?i=flowi4_oif">flowi4_oif</a> != nh-&gt;nh_oif)
<a name="L1413" href="source/net/ipv4/fib_trie.c#L1413">1413</a>                                 continue;
<a name="L1414" href="source/net/ipv4/fib_trie.c#L1414">1414</a> 
<a name="L1415" href="source/net/ipv4/fib_trie.c#L1415">1415</a>                         if (!(fib_flags &amp; <a href="ident?i=FIB_LOOKUP_NOREF">FIB_LOOKUP_NOREF</a>))
<a name="L1416" href="source/net/ipv4/fib_trie.c#L1416">1416</a>                                 <a href="ident?i=atomic_inc">atomic_inc</a>(&amp;fi-&gt;fib_clntref);
<a name="L1417" href="source/net/ipv4/fib_trie.c#L1417">1417</a> 
<a name="L1418" href="source/net/ipv4/fib_trie.c#L1418">1418</a>                         <a href="ident?i=res">res</a>-&gt;prefixlen = <a href="ident?i=KEYLENGTH">KEYLENGTH</a> - fa-&gt;fa_slen;
<a name="L1419" href="source/net/ipv4/fib_trie.c#L1419">1419</a>                         <a href="ident?i=res">res</a>-&gt;nh_sel = nhsel;
<a name="L1420" href="source/net/ipv4/fib_trie.c#L1420">1420</a>                         <a href="ident?i=res">res</a>-&gt;<a href="ident?i=type">type</a> = fa-&gt;fa_type;
<a name="L1421" href="source/net/ipv4/fib_trie.c#L1421">1421</a>                         <a href="ident?i=res">res</a>-&gt;<a href="ident?i=scope">scope</a> = fi-&gt;fib_scope;
<a name="L1422" href="source/net/ipv4/fib_trie.c#L1422">1422</a>                         <a href="ident?i=res">res</a>-&gt;fi = fi;
<a name="L1423" href="source/net/ipv4/fib_trie.c#L1423">1423</a>                         <a href="ident?i=res">res</a>-&gt;<a href="ident?i=table">table</a> = <a href="ident?i=tb">tb</a>;
<a name="L1424" href="source/net/ipv4/fib_trie.c#L1424">1424</a>                         <a href="ident?i=res">res</a>-&gt;fa_head = &amp;<a href="ident?i=n">n</a>-&gt;leaf;
<a name="L1425" href="source/net/ipv4/fib_trie.c#L1425">1425</a> #ifdef CONFIG_IP_FIB_TRIE_STATS
<a name="L1426" href="source/net/ipv4/fib_trie.c#L1426">1426</a>                         <a href="ident?i=this_cpu_inc">this_cpu_inc</a>(<a href="ident?i=stats">stats</a>-&gt;semantic_match_passed);
<a name="L1427" href="source/net/ipv4/fib_trie.c#L1427">1427</a> #endif
<a name="L1428" href="source/net/ipv4/fib_trie.c#L1428">1428</a>                         return <a href="ident?i=err">err</a>;
<a name="L1429" href="source/net/ipv4/fib_trie.c#L1429">1429</a>                 }
<a name="L1430" href="source/net/ipv4/fib_trie.c#L1430">1430</a>         }
<a name="L1431" href="source/net/ipv4/fib_trie.c#L1431">1431</a> #ifdef CONFIG_IP_FIB_TRIE_STATS
<a name="L1432" href="source/net/ipv4/fib_trie.c#L1432">1432</a>         <a href="ident?i=this_cpu_inc">this_cpu_inc</a>(<a href="ident?i=stats">stats</a>-&gt;semantic_match_miss);
<a name="L1433" href="source/net/ipv4/fib_trie.c#L1433">1433</a> #endif
<a name="L1434" href="source/net/ipv4/fib_trie.c#L1434">1434</a>         goto <a href="ident?i=backtrace">backtrace</a>;
<a name="L1435" href="source/net/ipv4/fib_trie.c#L1435">1435</a> }
<a name="L1436" href="source/net/ipv4/fib_trie.c#L1436">1436</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=fib_table_lookup">fib_table_lookup</a>);
<a name="L1437" href="source/net/ipv4/fib_trie.c#L1437">1437</a> 
<a name="L1438" href="source/net/ipv4/fib_trie.c#L1438">1438</a> static void <a href="ident?i=fib_remove_alias">fib_remove_alias</a>(struct <a href="ident?i=trie">trie</a> *<a href="ident?i=t">t</a>, struct <a href="ident?i=key_vector">key_vector</a> *<a href="ident?i=tp">tp</a>,
<a name="L1439" href="source/net/ipv4/fib_trie.c#L1439">1439</a>                              struct <a href="ident?i=key_vector">key_vector</a> *<a href="ident?i=l">l</a>, struct <a href="ident?i=fib_alias">fib_alias</a> *<a href="ident?i=old">old</a>)
<a name="L1440" href="source/net/ipv4/fib_trie.c#L1440">1440</a> {
<a name="L1441" href="source/net/ipv4/fib_trie.c#L1441">1441</a>         <b><i>/* record the location of the previous list_info entry */</i></b>
<a name="L1442" href="source/net/ipv4/fib_trie.c#L1442">1442</a>         struct <a href="ident?i=hlist_node">hlist_node</a> **pprev = <a href="ident?i=old">old</a>-&gt;fa_list.pprev;
<a name="L1443" href="source/net/ipv4/fib_trie.c#L1443">1443</a>         struct <a href="ident?i=fib_alias">fib_alias</a> *fa = <a href="ident?i=hlist_entry">hlist_entry</a>(pprev, typeof(*fa), fa_list.<a href="ident?i=next">next</a>);
<a name="L1444" href="source/net/ipv4/fib_trie.c#L1444">1444</a> 
<a name="L1445" href="source/net/ipv4/fib_trie.c#L1445">1445</a>         <b><i>/* remove the fib_alias from the list */</i></b>
<a name="L1446" href="source/net/ipv4/fib_trie.c#L1446">1446</a>         <a href="ident?i=hlist_del_rcu">hlist_del_rcu</a>(&amp;<a href="ident?i=old">old</a>-&gt;fa_list);
<a name="L1447" href="source/net/ipv4/fib_trie.c#L1447">1447</a> 
<a name="L1448" href="source/net/ipv4/fib_trie.c#L1448">1448</a>         <b><i>/* if we emptied the list this leaf will be freed and we can sort</i></b>
<a name="L1449" href="source/net/ipv4/fib_trie.c#L1449">1449</a> <b><i>         * out parent suffix lengths as a part of trie_rebalance</i></b>
<a name="L1450" href="source/net/ipv4/fib_trie.c#L1450">1450</a> <b><i>         */</i></b>
<a name="L1451" href="source/net/ipv4/fib_trie.c#L1451">1451</a>         if (<a href="ident?i=hlist_empty">hlist_empty</a>(&amp;<a href="ident?i=l">l</a>-&gt;leaf)) {
<a name="L1452" href="source/net/ipv4/fib_trie.c#L1452">1452</a>                 <a href="ident?i=put_child_root">put_child_root</a>(<a href="ident?i=tp">tp</a>, <a href="ident?i=l">l</a>-&gt;<a href="ident?i=key">key</a>, <a href="ident?i=NULL">NULL</a>);
<a name="L1453" href="source/net/ipv4/fib_trie.c#L1453">1453</a>                 <a href="ident?i=node_free">node_free</a>(<a href="ident?i=l">l</a>);
<a name="L1454" href="source/net/ipv4/fib_trie.c#L1454">1454</a>                 <a href="ident?i=trie_rebalance">trie_rebalance</a>(<a href="ident?i=t">t</a>, <a href="ident?i=tp">tp</a>);
<a name="L1455" href="source/net/ipv4/fib_trie.c#L1455">1455</a>                 return;
<a name="L1456" href="source/net/ipv4/fib_trie.c#L1456">1456</a>         }
<a name="L1457" href="source/net/ipv4/fib_trie.c#L1457">1457</a> 
<a name="L1458" href="source/net/ipv4/fib_trie.c#L1458">1458</a>         <b><i>/* only access fa if it is pointing at the last valid hlist_node */</i></b>
<a name="L1459" href="source/net/ipv4/fib_trie.c#L1459">1459</a>         if (*pprev)
<a name="L1460" href="source/net/ipv4/fib_trie.c#L1460">1460</a>                 return;
<a name="L1461" href="source/net/ipv4/fib_trie.c#L1461">1461</a> 
<a name="L1462" href="source/net/ipv4/fib_trie.c#L1462">1462</a>         <b><i>/* update the trie with the latest suffix length */</i></b>
<a name="L1463" href="source/net/ipv4/fib_trie.c#L1463">1463</a>         <a href="ident?i=l">l</a>-&gt;slen = fa-&gt;fa_slen;
<a name="L1464" href="source/net/ipv4/fib_trie.c#L1464">1464</a>         <a href="ident?i=leaf_pull_suffix">leaf_pull_suffix</a>(<a href="ident?i=tp">tp</a>, <a href="ident?i=l">l</a>);
<a name="L1465" href="source/net/ipv4/fib_trie.c#L1465">1465</a> }
<a name="L1466" href="source/net/ipv4/fib_trie.c#L1466">1466</a> 
<a name="L1467" href="source/net/ipv4/fib_trie.c#L1467">1467</a> <b><i>/* Caller must hold RTNL. */</i></b>
<a name="L1468" href="source/net/ipv4/fib_trie.c#L1468">1468</a> int <a href="ident?i=fib_table_delete">fib_table_delete</a>(struct <a href="ident?i=fib_table">fib_table</a> *<a href="ident?i=tb">tb</a>, struct <a href="ident?i=fib_config">fib_config</a> *<a href="ident?i=cfg">cfg</a>)
<a name="L1469" href="source/net/ipv4/fib_trie.c#L1469">1469</a> {
<a name="L1470" href="source/net/ipv4/fib_trie.c#L1470">1470</a>         struct <a href="ident?i=trie">trie</a> *<a href="ident?i=t">t</a> = (struct <a href="ident?i=trie">trie</a> *) <a href="ident?i=tb">tb</a>-&gt;tb_data;
<a name="L1471" href="source/net/ipv4/fib_trie.c#L1471">1471</a>         struct <a href="ident?i=fib_alias">fib_alias</a> *fa, *fa_to_delete;
<a name="L1472" href="source/net/ipv4/fib_trie.c#L1472">1472</a>         struct <a href="ident?i=key_vector">key_vector</a> *<a href="ident?i=l">l</a>, *<a href="ident?i=tp">tp</a>;
<a name="L1473" href="source/net/ipv4/fib_trie.c#L1473">1473</a>         <a href="ident?i=u8">u8</a> plen = <a href="ident?i=cfg">cfg</a>-&gt;fc_dst_len;
<a name="L1474" href="source/net/ipv4/fib_trie.c#L1474">1474</a>         <a href="ident?i=u8">u8</a> slen = <a href="ident?i=KEYLENGTH">KEYLENGTH</a> - plen;
<a name="L1475" href="source/net/ipv4/fib_trie.c#L1475">1475</a>         <a href="ident?i=u8">u8</a> tos = <a href="ident?i=cfg">cfg</a>-&gt;fc_tos;
<a name="L1476" href="source/net/ipv4/fib_trie.c#L1476">1476</a>         <a href="ident?i=u32">u32</a> <a href="ident?i=key">key</a>;
<a name="L1477" href="source/net/ipv4/fib_trie.c#L1477">1477</a> 
<a name="L1478" href="source/net/ipv4/fib_trie.c#L1478">1478</a>         if (plen &gt; <a href="ident?i=KEYLENGTH">KEYLENGTH</a>)
<a name="L1479" href="source/net/ipv4/fib_trie.c#L1479">1479</a>                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L1480" href="source/net/ipv4/fib_trie.c#L1480">1480</a> 
<a name="L1481" href="source/net/ipv4/fib_trie.c#L1481">1481</a>         <a href="ident?i=key">key</a> = <a href="ident?i=ntohl">ntohl</a>(<a href="ident?i=cfg">cfg</a>-&gt;fc_dst);
<a name="L1482" href="source/net/ipv4/fib_trie.c#L1482">1482</a> 
<a name="L1483" href="source/net/ipv4/fib_trie.c#L1483">1483</a>         if ((plen &lt; <a href="ident?i=KEYLENGTH">KEYLENGTH</a>) &amp;&amp; (<a href="ident?i=key">key</a> &lt;&lt; plen))
<a name="L1484" href="source/net/ipv4/fib_trie.c#L1484">1484</a>                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L1485" href="source/net/ipv4/fib_trie.c#L1485">1485</a> 
<a name="L1486" href="source/net/ipv4/fib_trie.c#L1486">1486</a>         <a href="ident?i=l">l</a> = <a href="ident?i=fib_find_node">fib_find_node</a>(<a href="ident?i=t">t</a>, &amp;<a href="ident?i=tp">tp</a>, <a href="ident?i=key">key</a>);
<a name="L1487" href="source/net/ipv4/fib_trie.c#L1487">1487</a>         if (!<a href="ident?i=l">l</a>)
<a name="L1488" href="source/net/ipv4/fib_trie.c#L1488">1488</a>                 return -<a href="ident?i=ESRCH">ESRCH</a>;
<a name="L1489" href="source/net/ipv4/fib_trie.c#L1489">1489</a> 
<a name="L1490" href="source/net/ipv4/fib_trie.c#L1490">1490</a>         fa = <a href="ident?i=fib_find_alias">fib_find_alias</a>(&amp;<a href="ident?i=l">l</a>-&gt;leaf, slen, tos, 0, <a href="ident?i=tb">tb</a>-&gt;tb_id);
<a name="L1491" href="source/net/ipv4/fib_trie.c#L1491">1491</a>         if (!fa)
<a name="L1492" href="source/net/ipv4/fib_trie.c#L1492">1492</a>                 return -<a href="ident?i=ESRCH">ESRCH</a>;
<a name="L1493" href="source/net/ipv4/fib_trie.c#L1493">1493</a> 
<a name="L1494" href="source/net/ipv4/fib_trie.c#L1494">1494</a>         <a href="ident?i=pr_debug">pr_debug</a>(<i>"Deleting %08x/%d tos=%d t=%p\n"</i>, <a href="ident?i=key">key</a>, plen, tos, <a href="ident?i=t">t</a>);
<a name="L1495" href="source/net/ipv4/fib_trie.c#L1495">1495</a> 
<a name="L1496" href="source/net/ipv4/fib_trie.c#L1496">1496</a>         fa_to_delete = <a href="ident?i=NULL">NULL</a>;
<a name="L1497" href="source/net/ipv4/fib_trie.c#L1497">1497</a>         <a href="ident?i=hlist_for_each_entry_from">hlist_for_each_entry_from</a>(fa, fa_list) {
<a name="L1498" href="source/net/ipv4/fib_trie.c#L1498">1498</a>                 struct <a href="ident?i=fib_info">fib_info</a> *fi = fa-&gt;fa_info;
<a name="L1499" href="source/net/ipv4/fib_trie.c#L1499">1499</a> 
<a name="L1500" href="source/net/ipv4/fib_trie.c#L1500">1500</a>                 if ((fa-&gt;fa_slen != slen) ||
<a name="L1501" href="source/net/ipv4/fib_trie.c#L1501">1501</a>                     (fa-&gt;tb_id != <a href="ident?i=tb">tb</a>-&gt;tb_id) ||
<a name="L1502" href="source/net/ipv4/fib_trie.c#L1502">1502</a>                     (fa-&gt;fa_tos != tos))
<a name="L1503" href="source/net/ipv4/fib_trie.c#L1503">1503</a>                         break;
<a name="L1504" href="source/net/ipv4/fib_trie.c#L1504">1504</a> 
<a name="L1505" href="source/net/ipv4/fib_trie.c#L1505">1505</a>                 if ((!<a href="ident?i=cfg">cfg</a>-&gt;<a href="ident?i=fc_type">fc_type</a> || fa-&gt;fa_type == <a href="ident?i=cfg">cfg</a>-&gt;<a href="ident?i=fc_type">fc_type</a>) &amp;&amp;
<a name="L1506" href="source/net/ipv4/fib_trie.c#L1506">1506</a>                     (<a href="ident?i=cfg">cfg</a>-&gt;fc_scope == RT_SCOPE_NOWHERE ||
<a name="L1507" href="source/net/ipv4/fib_trie.c#L1507">1507</a>                      fa-&gt;fa_info-&gt;fib_scope == <a href="ident?i=cfg">cfg</a>-&gt;fc_scope) &amp;&amp;
<a name="L1508" href="source/net/ipv4/fib_trie.c#L1508">1508</a>                     (!<a href="ident?i=cfg">cfg</a>-&gt;fc_prefsrc ||
<a name="L1509" href="source/net/ipv4/fib_trie.c#L1509">1509</a>                      fi-&gt;fib_prefsrc == <a href="ident?i=cfg">cfg</a>-&gt;fc_prefsrc) &amp;&amp;
<a name="L1510" href="source/net/ipv4/fib_trie.c#L1510">1510</a>                     (!<a href="ident?i=cfg">cfg</a>-&gt;fc_protocol ||
<a name="L1511" href="source/net/ipv4/fib_trie.c#L1511">1511</a>                      fi-&gt;fib_protocol == <a href="ident?i=cfg">cfg</a>-&gt;fc_protocol) &amp;&amp;
<a name="L1512" href="source/net/ipv4/fib_trie.c#L1512">1512</a>                     <a href="ident?i=fib_nh_match">fib_nh_match</a>(<a href="ident?i=cfg">cfg</a>, fi) == 0) {
<a name="L1513" href="source/net/ipv4/fib_trie.c#L1513">1513</a>                         fa_to_delete = fa;
<a name="L1514" href="source/net/ipv4/fib_trie.c#L1514">1514</a>                         break;
<a name="L1515" href="source/net/ipv4/fib_trie.c#L1515">1515</a>                 }
<a name="L1516" href="source/net/ipv4/fib_trie.c#L1516">1516</a>         }
<a name="L1517" href="source/net/ipv4/fib_trie.c#L1517">1517</a> 
<a name="L1518" href="source/net/ipv4/fib_trie.c#L1518">1518</a>         if (!fa_to_delete)
<a name="L1519" href="source/net/ipv4/fib_trie.c#L1519">1519</a>                 return -<a href="ident?i=ESRCH">ESRCH</a>;
<a name="L1520" href="source/net/ipv4/fib_trie.c#L1520">1520</a> 
<a name="L1521" href="source/net/ipv4/fib_trie.c#L1521">1521</a>         <a href="ident?i=netdev_switch_fib_ipv4_del">netdev_switch_fib_ipv4_del</a>(<a href="ident?i=key">key</a>, plen, fa_to_delete-&gt;fa_info, tos,
<a name="L1522" href="source/net/ipv4/fib_trie.c#L1522">1522</a>                                    <a href="ident?i=cfg">cfg</a>-&gt;<a href="ident?i=fc_type">fc_type</a>, <a href="ident?i=tb">tb</a>-&gt;tb_id);
<a name="L1523" href="source/net/ipv4/fib_trie.c#L1523">1523</a> 
<a name="L1524" href="source/net/ipv4/fib_trie.c#L1524">1524</a>         <a href="ident?i=rtmsg_fib">rtmsg_fib</a>(<a href="ident?i=RTM_DELROUTE">RTM_DELROUTE</a>, <a href="ident?i=htonl">htonl</a>(<a href="ident?i=key">key</a>), fa_to_delete, plen, <a href="ident?i=tb">tb</a>-&gt;tb_id,
<a name="L1525" href="source/net/ipv4/fib_trie.c#L1525">1525</a>                   &amp;<a href="ident?i=cfg">cfg</a>-&gt;fc_nlinfo, 0);
<a name="L1526" href="source/net/ipv4/fib_trie.c#L1526">1526</a> 
<a name="L1527" href="source/net/ipv4/fib_trie.c#L1527">1527</a>         if (!plen)
<a name="L1528" href="source/net/ipv4/fib_trie.c#L1528">1528</a>                 <a href="ident?i=tb">tb</a>-&gt;tb_num_default--;
<a name="L1529" href="source/net/ipv4/fib_trie.c#L1529">1529</a> 
<a name="L1530" href="source/net/ipv4/fib_trie.c#L1530">1530</a>         <a href="ident?i=fib_remove_alias">fib_remove_alias</a>(<a href="ident?i=t">t</a>, <a href="ident?i=tp">tp</a>, <a href="ident?i=l">l</a>, fa_to_delete);
<a name="L1531" href="source/net/ipv4/fib_trie.c#L1531">1531</a> 
<a name="L1532" href="source/net/ipv4/fib_trie.c#L1532">1532</a>         if (fa_to_delete-&gt;fa_state &amp; <a href="ident?i=FA_S_ACCESSED">FA_S_ACCESSED</a>)
<a name="L1533" href="source/net/ipv4/fib_trie.c#L1533">1533</a>                 <a href="ident?i=rt_cache_flush">rt_cache_flush</a>(<a href="ident?i=cfg">cfg</a>-&gt;fc_nlinfo.nl_net);
<a name="L1534" href="source/net/ipv4/fib_trie.c#L1534">1534</a> 
<a name="L1535" href="source/net/ipv4/fib_trie.c#L1535">1535</a>         <a href="ident?i=fib_release_info">fib_release_info</a>(fa_to_delete-&gt;fa_info);
<a name="L1536" href="source/net/ipv4/fib_trie.c#L1536">1536</a>         <a href="ident?i=alias_free_mem_rcu">alias_free_mem_rcu</a>(fa_to_delete);
<a name="L1537" href="source/net/ipv4/fib_trie.c#L1537">1537</a>         return 0;
<a name="L1538" href="source/net/ipv4/fib_trie.c#L1538">1538</a> }
<a name="L1539" href="source/net/ipv4/fib_trie.c#L1539">1539</a> 
<a name="L1540" href="source/net/ipv4/fib_trie.c#L1540">1540</a> <b><i>/* Scan for the next leaf starting at the provided key value */</i></b>
<a name="L1541" href="source/net/ipv4/fib_trie.c#L1541">1541</a> static struct <a href="ident?i=key_vector">key_vector</a> *<a href="ident?i=leaf_walk_rcu">leaf_walk_rcu</a>(struct <a href="ident?i=key_vector">key_vector</a> **tn, <a href="ident?i=t_key">t_key</a> <a href="ident?i=key">key</a>)
<a name="L1542" href="source/net/ipv4/fib_trie.c#L1542">1542</a> {
<a name="L1543" href="source/net/ipv4/fib_trie.c#L1543">1543</a>         struct <a href="ident?i=key_vector">key_vector</a> *pn, *<a href="ident?i=n">n</a> = *tn;
<a name="L1544" href="source/net/ipv4/fib_trie.c#L1544">1544</a>         unsigned long cindex;
<a name="L1545" href="source/net/ipv4/fib_trie.c#L1545">1545</a> 
<a name="L1546" href="source/net/ipv4/fib_trie.c#L1546">1546</a>         <b><i>/* this loop is meant to try and find the key in the trie */</i></b>
<a name="L1547" href="source/net/ipv4/fib_trie.c#L1547">1547</a>         do {
<a name="L1548" href="source/net/ipv4/fib_trie.c#L1548">1548</a>                 <b><i>/* record parent and next child index */</i></b>
<a name="L1549" href="source/net/ipv4/fib_trie.c#L1549">1549</a>                 pn = <a href="ident?i=n">n</a>;
<a name="L1550" href="source/net/ipv4/fib_trie.c#L1550">1550</a>                 cindex = <a href="ident?i=key">key</a> ? <a href="ident?i=get_index">get_index</a>(<a href="ident?i=key">key</a>, pn) : 0;
<a name="L1551" href="source/net/ipv4/fib_trie.c#L1551">1551</a> 
<a name="L1552" href="source/net/ipv4/fib_trie.c#L1552">1552</a>                 if (cindex &gt;&gt; pn-&gt;<a href="ident?i=bits">bits</a>)
<a name="L1553" href="source/net/ipv4/fib_trie.c#L1553">1553</a>                         break;
<a name="L1554" href="source/net/ipv4/fib_trie.c#L1554">1554</a> 
<a name="L1555" href="source/net/ipv4/fib_trie.c#L1555">1555</a>                 <b><i>/* descend into the next child */</i></b>
<a name="L1556" href="source/net/ipv4/fib_trie.c#L1556">1556</a>                 <a href="ident?i=n">n</a> = <a href="ident?i=get_child_rcu">get_child_rcu</a>(pn, cindex++);
<a name="L1557" href="source/net/ipv4/fib_trie.c#L1557">1557</a>                 if (!<a href="ident?i=n">n</a>)
<a name="L1558" href="source/net/ipv4/fib_trie.c#L1558">1558</a>                         break;
<a name="L1559" href="source/net/ipv4/fib_trie.c#L1559">1559</a> 
<a name="L1560" href="source/net/ipv4/fib_trie.c#L1560">1560</a>                 <b><i>/* guarantee forward progress on the keys */</i></b>
<a name="L1561" href="source/net/ipv4/fib_trie.c#L1561">1561</a>                 if (<a href="ident?i=IS_LEAF">IS_LEAF</a>(<a href="ident?i=n">n</a>) &amp;&amp; (<a href="ident?i=n">n</a>-&gt;<a href="ident?i=key">key</a> &gt;= <a href="ident?i=key">key</a>))
<a name="L1562" href="source/net/ipv4/fib_trie.c#L1562">1562</a>                         goto <a href="ident?i=found">found</a>;
<a name="L1563" href="source/net/ipv4/fib_trie.c#L1563">1563</a>         } while (<a href="ident?i=IS_TNODE">IS_TNODE</a>(<a href="ident?i=n">n</a>));
<a name="L1564" href="source/net/ipv4/fib_trie.c#L1564">1564</a> 
<a name="L1565" href="source/net/ipv4/fib_trie.c#L1565">1565</a>         <b><i>/* this loop will search for the next leaf with a greater key */</i></b>
<a name="L1566" href="source/net/ipv4/fib_trie.c#L1566">1566</a>         while (!<a href="ident?i=IS_TRIE">IS_TRIE</a>(pn)) {
<a name="L1567" href="source/net/ipv4/fib_trie.c#L1567">1567</a>                 <b><i>/* if we exhausted the parent node we will need to climb */</i></b>
<a name="L1568" href="source/net/ipv4/fib_trie.c#L1568">1568</a>                 if (cindex &gt;= (1ul &lt;&lt; pn-&gt;<a href="ident?i=bits">bits</a>)) {
<a name="L1569" href="source/net/ipv4/fib_trie.c#L1569">1569</a>                         <a href="ident?i=t_key">t_key</a> pkey = pn-&gt;<a href="ident?i=key">key</a>;
<a name="L1570" href="source/net/ipv4/fib_trie.c#L1570">1570</a> 
<a name="L1571" href="source/net/ipv4/fib_trie.c#L1571">1571</a>                         pn = <a href="ident?i=node_parent_rcu">node_parent_rcu</a>(pn);
<a name="L1572" href="source/net/ipv4/fib_trie.c#L1572">1572</a>                         cindex = <a href="ident?i=get_index">get_index</a>(pkey, pn) + 1;
<a name="L1573" href="source/net/ipv4/fib_trie.c#L1573">1573</a>                         continue;
<a name="L1574" href="source/net/ipv4/fib_trie.c#L1574">1574</a>                 }
<a name="L1575" href="source/net/ipv4/fib_trie.c#L1575">1575</a> 
<a name="L1576" href="source/net/ipv4/fib_trie.c#L1576">1576</a>                 <b><i>/* grab the next available node */</i></b>
<a name="L1577" href="source/net/ipv4/fib_trie.c#L1577">1577</a>                 <a href="ident?i=n">n</a> = <a href="ident?i=get_child_rcu">get_child_rcu</a>(pn, cindex++);
<a name="L1578" href="source/net/ipv4/fib_trie.c#L1578">1578</a>                 if (!<a href="ident?i=n">n</a>)
<a name="L1579" href="source/net/ipv4/fib_trie.c#L1579">1579</a>                         continue;
<a name="L1580" href="source/net/ipv4/fib_trie.c#L1580">1580</a> 
<a name="L1581" href="source/net/ipv4/fib_trie.c#L1581">1581</a>                 <b><i>/* no need to compare keys since we bumped the index */</i></b>
<a name="L1582" href="source/net/ipv4/fib_trie.c#L1582">1582</a>                 if (<a href="ident?i=IS_LEAF">IS_LEAF</a>(<a href="ident?i=n">n</a>))
<a name="L1583" href="source/net/ipv4/fib_trie.c#L1583">1583</a>                         goto <a href="ident?i=found">found</a>;
<a name="L1584" href="source/net/ipv4/fib_trie.c#L1584">1584</a> 
<a name="L1585" href="source/net/ipv4/fib_trie.c#L1585">1585</a>                 <b><i>/* Rescan start scanning in new node */</i></b>
<a name="L1586" href="source/net/ipv4/fib_trie.c#L1586">1586</a>                 pn = <a href="ident?i=n">n</a>;
<a name="L1587" href="source/net/ipv4/fib_trie.c#L1587">1587</a>                 cindex = 0;
<a name="L1588" href="source/net/ipv4/fib_trie.c#L1588">1588</a>         }
<a name="L1589" href="source/net/ipv4/fib_trie.c#L1589">1589</a> 
<a name="L1590" href="source/net/ipv4/fib_trie.c#L1590">1590</a>         *tn = pn;
<a name="L1591" href="source/net/ipv4/fib_trie.c#L1591">1591</a>         return <a href="ident?i=NULL">NULL</a>; <b><i>/* Root of trie */</i></b>
<a name="L1592" href="source/net/ipv4/fib_trie.c#L1592">1592</a> <a href="ident?i=found">found</a>:
<a name="L1593" href="source/net/ipv4/fib_trie.c#L1593">1593</a>         <b><i>/* if we are at the limit for keys just return NULL for the tnode */</i></b>
<a name="L1594" href="source/net/ipv4/fib_trie.c#L1594">1594</a>         *tn = pn;
<a name="L1595" href="source/net/ipv4/fib_trie.c#L1595">1595</a>         return <a href="ident?i=n">n</a>;
<a name="L1596" href="source/net/ipv4/fib_trie.c#L1596">1596</a> }
<a name="L1597" href="source/net/ipv4/fib_trie.c#L1597">1597</a> 
<a name="L1598" href="source/net/ipv4/fib_trie.c#L1598">1598</a> static void <a href="ident?i=fib_trie_free">fib_trie_free</a>(struct <a href="ident?i=fib_table">fib_table</a> *<a href="ident?i=tb">tb</a>)
<a name="L1599" href="source/net/ipv4/fib_trie.c#L1599">1599</a> {
<a name="L1600" href="source/net/ipv4/fib_trie.c#L1600">1600</a>         struct <a href="ident?i=trie">trie</a> *<a href="ident?i=t">t</a> = (struct <a href="ident?i=trie">trie</a> *)<a href="ident?i=tb">tb</a>-&gt;tb_data;
<a name="L1601" href="source/net/ipv4/fib_trie.c#L1601">1601</a>         struct <a href="ident?i=key_vector">key_vector</a> *pn = <a href="ident?i=t">t</a>-&gt;kv;
<a name="L1602" href="source/net/ipv4/fib_trie.c#L1602">1602</a>         unsigned long cindex = 1;
<a name="L1603" href="source/net/ipv4/fib_trie.c#L1603">1603</a>         struct <a href="ident?i=hlist_node">hlist_node</a> *<a href="ident?i=tmp">tmp</a>;
<a name="L1604" href="source/net/ipv4/fib_trie.c#L1604">1604</a>         struct <a href="ident?i=fib_alias">fib_alias</a> *fa;
<a name="L1605" href="source/net/ipv4/fib_trie.c#L1605">1605</a> 
<a name="L1606" href="source/net/ipv4/fib_trie.c#L1606">1606</a>         <b><i>/* walk trie in reverse order and free everything */</i></b>
<a name="L1607" href="source/net/ipv4/fib_trie.c#L1607">1607</a>         for (;;) {
<a name="L1608" href="source/net/ipv4/fib_trie.c#L1608">1608</a>                 struct <a href="ident?i=key_vector">key_vector</a> *<a href="ident?i=n">n</a>;
<a name="L1609" href="source/net/ipv4/fib_trie.c#L1609">1609</a> 
<a name="L1610" href="source/net/ipv4/fib_trie.c#L1610">1610</a>                 if (!(cindex--)) {
<a name="L1611" href="source/net/ipv4/fib_trie.c#L1611">1611</a>                         <a href="ident?i=t_key">t_key</a> pkey = pn-&gt;<a href="ident?i=key">key</a>;
<a name="L1612" href="source/net/ipv4/fib_trie.c#L1612">1612</a> 
<a name="L1613" href="source/net/ipv4/fib_trie.c#L1613">1613</a>                         if (<a href="ident?i=IS_TRIE">IS_TRIE</a>(pn))
<a name="L1614" href="source/net/ipv4/fib_trie.c#L1614">1614</a>                                 break;
<a name="L1615" href="source/net/ipv4/fib_trie.c#L1615">1615</a> 
<a name="L1616" href="source/net/ipv4/fib_trie.c#L1616">1616</a>                         <a href="ident?i=n">n</a> = pn;
<a name="L1617" href="source/net/ipv4/fib_trie.c#L1617">1617</a>                         pn = <a href="ident?i=node_parent">node_parent</a>(pn);
<a name="L1618" href="source/net/ipv4/fib_trie.c#L1618">1618</a> 
<a name="L1619" href="source/net/ipv4/fib_trie.c#L1619">1619</a>                         <b><i>/* drop emptied tnode */</i></b>
<a name="L1620" href="source/net/ipv4/fib_trie.c#L1620">1620</a>                         <a href="ident?i=put_child_root">put_child_root</a>(pn, <a href="ident?i=n">n</a>-&gt;<a href="ident?i=key">key</a>, <a href="ident?i=NULL">NULL</a>);
<a name="L1621" href="source/net/ipv4/fib_trie.c#L1621">1621</a>                         <a href="ident?i=node_free">node_free</a>(<a href="ident?i=n">n</a>);
<a name="L1622" href="source/net/ipv4/fib_trie.c#L1622">1622</a> 
<a name="L1623" href="source/net/ipv4/fib_trie.c#L1623">1623</a>                         cindex = <a href="ident?i=get_index">get_index</a>(pkey, pn);
<a name="L1624" href="source/net/ipv4/fib_trie.c#L1624">1624</a> 
<a name="L1625" href="source/net/ipv4/fib_trie.c#L1625">1625</a>                         continue;
<a name="L1626" href="source/net/ipv4/fib_trie.c#L1626">1626</a>                 }
<a name="L1627" href="source/net/ipv4/fib_trie.c#L1627">1627</a> 
<a name="L1628" href="source/net/ipv4/fib_trie.c#L1628">1628</a>                 <b><i>/* grab the next available node */</i></b>
<a name="L1629" href="source/net/ipv4/fib_trie.c#L1629">1629</a>                 <a href="ident?i=n">n</a> = <a href="ident?i=get_child">get_child</a>(pn, cindex);
<a name="L1630" href="source/net/ipv4/fib_trie.c#L1630">1630</a>                 if (!<a href="ident?i=n">n</a>)
<a name="L1631" href="source/net/ipv4/fib_trie.c#L1631">1631</a>                         continue;
<a name="L1632" href="source/net/ipv4/fib_trie.c#L1632">1632</a> 
<a name="L1633" href="source/net/ipv4/fib_trie.c#L1633">1633</a>                 if (<a href="ident?i=IS_TNODE">IS_TNODE</a>(<a href="ident?i=n">n</a>)) {
<a name="L1634" href="source/net/ipv4/fib_trie.c#L1634">1634</a>                         <b><i>/* record pn and cindex for leaf walking */</i></b>
<a name="L1635" href="source/net/ipv4/fib_trie.c#L1635">1635</a>                         pn = <a href="ident?i=n">n</a>;
<a name="L1636" href="source/net/ipv4/fib_trie.c#L1636">1636</a>                         cindex = 1ul &lt;&lt; <a href="ident?i=n">n</a>-&gt;<a href="ident?i=bits">bits</a>;
<a name="L1637" href="source/net/ipv4/fib_trie.c#L1637">1637</a> 
<a name="L1638" href="source/net/ipv4/fib_trie.c#L1638">1638</a>                         continue;
<a name="L1639" href="source/net/ipv4/fib_trie.c#L1639">1639</a>                 }
<a name="L1640" href="source/net/ipv4/fib_trie.c#L1640">1640</a> 
<a name="L1641" href="source/net/ipv4/fib_trie.c#L1641">1641</a>                 <a href="ident?i=hlist_for_each_entry_safe">hlist_for_each_entry_safe</a>(fa, <a href="ident?i=tmp">tmp</a>, &amp;<a href="ident?i=n">n</a>-&gt;leaf, fa_list) {
<a name="L1642" href="source/net/ipv4/fib_trie.c#L1642">1642</a>                         <a href="ident?i=hlist_del_rcu">hlist_del_rcu</a>(&amp;fa-&gt;fa_list);
<a name="L1643" href="source/net/ipv4/fib_trie.c#L1643">1643</a>                         <a href="ident?i=alias_free_mem_rcu">alias_free_mem_rcu</a>(fa);
<a name="L1644" href="source/net/ipv4/fib_trie.c#L1644">1644</a>                 }
<a name="L1645" href="source/net/ipv4/fib_trie.c#L1645">1645</a> 
<a name="L1646" href="source/net/ipv4/fib_trie.c#L1646">1646</a>                 <a href="ident?i=put_child_root">put_child_root</a>(pn, <a href="ident?i=n">n</a>-&gt;<a href="ident?i=key">key</a>, <a href="ident?i=NULL">NULL</a>);
<a name="L1647" href="source/net/ipv4/fib_trie.c#L1647">1647</a>                 <a href="ident?i=node_free">node_free</a>(<a href="ident?i=n">n</a>);
<a name="L1648" href="source/net/ipv4/fib_trie.c#L1648">1648</a>         }
<a name="L1649" href="source/net/ipv4/fib_trie.c#L1649">1649</a> 
<a name="L1650" href="source/net/ipv4/fib_trie.c#L1650">1650</a> #ifdef CONFIG_IP_FIB_TRIE_STATS
<a name="L1651" href="source/net/ipv4/fib_trie.c#L1651">1651</a>         <a href="ident?i=free_percpu">free_percpu</a>(<a href="ident?i=t">t</a>-&gt;<a href="ident?i=stats">stats</a>);
<a name="L1652" href="source/net/ipv4/fib_trie.c#L1652">1652</a> #endif
<a name="L1653" href="source/net/ipv4/fib_trie.c#L1653">1653</a>         <a href="ident?i=kfree">kfree</a>(<a href="ident?i=tb">tb</a>);
<a name="L1654" href="source/net/ipv4/fib_trie.c#L1654">1654</a> }
<a name="L1655" href="source/net/ipv4/fib_trie.c#L1655">1655</a> 
<a name="L1656" href="source/net/ipv4/fib_trie.c#L1656">1656</a> struct <a href="ident?i=fib_table">fib_table</a> *<a href="ident?i=fib_trie_unmerge">fib_trie_unmerge</a>(struct <a href="ident?i=fib_table">fib_table</a> *oldtb)
<a name="L1657" href="source/net/ipv4/fib_trie.c#L1657">1657</a> {
<a name="L1658" href="source/net/ipv4/fib_trie.c#L1658">1658</a>         struct <a href="ident?i=trie">trie</a> *ot = (struct <a href="ident?i=trie">trie</a> *)oldtb-&gt;tb_data;
<a name="L1659" href="source/net/ipv4/fib_trie.c#L1659">1659</a>         struct <a href="ident?i=key_vector">key_vector</a> *<a href="ident?i=l">l</a>, *<a href="ident?i=tp">tp</a> = ot-&gt;kv;
<a name="L1660" href="source/net/ipv4/fib_trie.c#L1660">1660</a>         struct <a href="ident?i=fib_table">fib_table</a> *local_tb;
<a name="L1661" href="source/net/ipv4/fib_trie.c#L1661">1661</a>         struct <a href="ident?i=fib_alias">fib_alias</a> *fa;
<a name="L1662" href="source/net/ipv4/fib_trie.c#L1662">1662</a>         struct <a href="ident?i=trie">trie</a> *<a href="ident?i=lt">lt</a>;
<a name="L1663" href="source/net/ipv4/fib_trie.c#L1663">1663</a>         <a href="ident?i=t_key">t_key</a> <a href="ident?i=key">key</a> = 0;
<a name="L1664" href="source/net/ipv4/fib_trie.c#L1664">1664</a> 
<a name="L1665" href="source/net/ipv4/fib_trie.c#L1665">1665</a>         if (oldtb-&gt;tb_data == oldtb-&gt;__data)
<a name="L1666" href="source/net/ipv4/fib_trie.c#L1666">1666</a>                 return oldtb;
<a name="L1667" href="source/net/ipv4/fib_trie.c#L1667">1667</a> 
<a name="L1668" href="source/net/ipv4/fib_trie.c#L1668">1668</a>         local_tb = <a href="ident?i=fib_trie_table">fib_trie_table</a>(RT_TABLE_LOCAL, <a href="ident?i=NULL">NULL</a>);
<a name="L1669" href="source/net/ipv4/fib_trie.c#L1669">1669</a>         if (!local_tb)
<a name="L1670" href="source/net/ipv4/fib_trie.c#L1670">1670</a>                 return <a href="ident?i=NULL">NULL</a>;
<a name="L1671" href="source/net/ipv4/fib_trie.c#L1671">1671</a> 
<a name="L1672" href="source/net/ipv4/fib_trie.c#L1672">1672</a>         <a href="ident?i=lt">lt</a> = (struct <a href="ident?i=trie">trie</a> *)local_tb-&gt;tb_data;
<a name="L1673" href="source/net/ipv4/fib_trie.c#L1673">1673</a> 
<a name="L1674" href="source/net/ipv4/fib_trie.c#L1674">1674</a>         while ((<a href="ident?i=l">l</a> = <a href="ident?i=leaf_walk_rcu">leaf_walk_rcu</a>(&amp;<a href="ident?i=tp">tp</a>, <a href="ident?i=key">key</a>)) != <a href="ident?i=NULL">NULL</a>) {
<a name="L1675" href="source/net/ipv4/fib_trie.c#L1675">1675</a>                 struct <a href="ident?i=key_vector">key_vector</a> *local_l = <a href="ident?i=NULL">NULL</a>, *local_tp;
<a name="L1676" href="source/net/ipv4/fib_trie.c#L1676">1676</a> 
<a name="L1677" href="source/net/ipv4/fib_trie.c#L1677">1677</a>                 <a href="ident?i=hlist_for_each_entry_rcu">hlist_for_each_entry_rcu</a>(fa, &amp;<a href="ident?i=l">l</a>-&gt;leaf, fa_list) {
<a name="L1678" href="source/net/ipv4/fib_trie.c#L1678">1678</a>                         struct <a href="ident?i=fib_alias">fib_alias</a> *new_fa;
<a name="L1679" href="source/net/ipv4/fib_trie.c#L1679">1679</a> 
<a name="L1680" href="source/net/ipv4/fib_trie.c#L1680">1680</a>                         if (local_tb-&gt;tb_id != fa-&gt;tb_id)
<a name="L1681" href="source/net/ipv4/fib_trie.c#L1681">1681</a>                                 continue;
<a name="L1682" href="source/net/ipv4/fib_trie.c#L1682">1682</a> 
<a name="L1683" href="source/net/ipv4/fib_trie.c#L1683">1683</a>                         <b><i>/* clone fa for new local table */</i></b>
<a name="L1684" href="source/net/ipv4/fib_trie.c#L1684">1684</a>                         new_fa = <a href="ident?i=kmem_cache_alloc">kmem_cache_alloc</a>(fn_alias_kmem, <a href="ident?i=GFP_KERNEL">GFP_KERNEL</a>);
<a name="L1685" href="source/net/ipv4/fib_trie.c#L1685">1685</a>                         if (!new_fa)
<a name="L1686" href="source/net/ipv4/fib_trie.c#L1686">1686</a>                                 goto <a href="ident?i=out">out</a>;
<a name="L1687" href="source/net/ipv4/fib_trie.c#L1687">1687</a> 
<a name="L1688" href="source/net/ipv4/fib_trie.c#L1688">1688</a>                         <a href="ident?i=memcpy">memcpy</a>(new_fa, fa, sizeof(*fa));
<a name="L1689" href="source/net/ipv4/fib_trie.c#L1689">1689</a> 
<a name="L1690" href="source/net/ipv4/fib_trie.c#L1690">1690</a>                         <b><i>/* insert clone into table */</i></b>
<a name="L1691" href="source/net/ipv4/fib_trie.c#L1691">1691</a>                         if (!local_l)
<a name="L1692" href="source/net/ipv4/fib_trie.c#L1692">1692</a>                                 local_l = <a href="ident?i=fib_find_node">fib_find_node</a>(<a href="ident?i=lt">lt</a>, &amp;local_tp, <a href="ident?i=l">l</a>-&gt;<a href="ident?i=key">key</a>);
<a name="L1693" href="source/net/ipv4/fib_trie.c#L1693">1693</a> 
<a name="L1694" href="source/net/ipv4/fib_trie.c#L1694">1694</a>                         if (<a href="ident?i=fib_insert_alias">fib_insert_alias</a>(<a href="ident?i=lt">lt</a>, local_tp, local_l, new_fa,
<a name="L1695" href="source/net/ipv4/fib_trie.c#L1695">1695</a>                                              <a href="ident?i=NULL">NULL</a>, <a href="ident?i=l">l</a>-&gt;<a href="ident?i=key">key</a>))
<a name="L1696" href="source/net/ipv4/fib_trie.c#L1696">1696</a>                                 goto <a href="ident?i=out">out</a>;
<a name="L1697" href="source/net/ipv4/fib_trie.c#L1697">1697</a>                 }
<a name="L1698" href="source/net/ipv4/fib_trie.c#L1698">1698</a> 
<a name="L1699" href="source/net/ipv4/fib_trie.c#L1699">1699</a>                 <b><i>/* stop loop if key wrapped back to 0 */</i></b>
<a name="L1700" href="source/net/ipv4/fib_trie.c#L1700">1700</a>                 <a href="ident?i=key">key</a> = <a href="ident?i=l">l</a>-&gt;<a href="ident?i=key">key</a> + 1;
<a name="L1701" href="source/net/ipv4/fib_trie.c#L1701">1701</a>                 if (<a href="ident?i=key">key</a> &lt; <a href="ident?i=l">l</a>-&gt;<a href="ident?i=key">key</a>)
<a name="L1702" href="source/net/ipv4/fib_trie.c#L1702">1702</a>                         break;
<a name="L1703" href="source/net/ipv4/fib_trie.c#L1703">1703</a>         }
<a name="L1704" href="source/net/ipv4/fib_trie.c#L1704">1704</a> 
<a name="L1705" href="source/net/ipv4/fib_trie.c#L1705">1705</a>         return local_tb;
<a name="L1706" href="source/net/ipv4/fib_trie.c#L1706">1706</a> <a href="ident?i=out">out</a>:
<a name="L1707" href="source/net/ipv4/fib_trie.c#L1707">1707</a>         <a href="ident?i=fib_trie_free">fib_trie_free</a>(local_tb);
<a name="L1708" href="source/net/ipv4/fib_trie.c#L1708">1708</a> 
<a name="L1709" href="source/net/ipv4/fib_trie.c#L1709">1709</a>         return <a href="ident?i=NULL">NULL</a>;
<a name="L1710" href="source/net/ipv4/fib_trie.c#L1710">1710</a> }
<a name="L1711" href="source/net/ipv4/fib_trie.c#L1711">1711</a> 
<a name="L1712" href="source/net/ipv4/fib_trie.c#L1712">1712</a> <b><i>/* Caller must hold RTNL */</i></b>
<a name="L1713" href="source/net/ipv4/fib_trie.c#L1713">1713</a> void <a href="ident?i=fib_table_flush_external">fib_table_flush_external</a>(struct <a href="ident?i=fib_table">fib_table</a> *<a href="ident?i=tb">tb</a>)
<a name="L1714" href="source/net/ipv4/fib_trie.c#L1714">1714</a> {
<a name="L1715" href="source/net/ipv4/fib_trie.c#L1715">1715</a>         struct <a href="ident?i=trie">trie</a> *<a href="ident?i=t">t</a> = (struct <a href="ident?i=trie">trie</a> *)<a href="ident?i=tb">tb</a>-&gt;tb_data;
<a name="L1716" href="source/net/ipv4/fib_trie.c#L1716">1716</a>         struct <a href="ident?i=key_vector">key_vector</a> *pn = <a href="ident?i=t">t</a>-&gt;kv;
<a name="L1717" href="source/net/ipv4/fib_trie.c#L1717">1717</a>         unsigned long cindex = 1;
<a name="L1718" href="source/net/ipv4/fib_trie.c#L1718">1718</a>         struct <a href="ident?i=hlist_node">hlist_node</a> *<a href="ident?i=tmp">tmp</a>;
<a name="L1719" href="source/net/ipv4/fib_trie.c#L1719">1719</a>         struct <a href="ident?i=fib_alias">fib_alias</a> *fa;
<a name="L1720" href="source/net/ipv4/fib_trie.c#L1720">1720</a> 
<a name="L1721" href="source/net/ipv4/fib_trie.c#L1721">1721</a>         <b><i>/* walk trie in reverse order */</i></b>
<a name="L1722" href="source/net/ipv4/fib_trie.c#L1722">1722</a>         for (;;) {
<a name="L1723" href="source/net/ipv4/fib_trie.c#L1723">1723</a>                 unsigned char slen = 0;
<a name="L1724" href="source/net/ipv4/fib_trie.c#L1724">1724</a>                 struct <a href="ident?i=key_vector">key_vector</a> *<a href="ident?i=n">n</a>;
<a name="L1725" href="source/net/ipv4/fib_trie.c#L1725">1725</a> 
<a name="L1726" href="source/net/ipv4/fib_trie.c#L1726">1726</a>                 if (!(cindex--)) {
<a name="L1727" href="source/net/ipv4/fib_trie.c#L1727">1727</a>                         <a href="ident?i=t_key">t_key</a> pkey = pn-&gt;<a href="ident?i=key">key</a>;
<a name="L1728" href="source/net/ipv4/fib_trie.c#L1728">1728</a> 
<a name="L1729" href="source/net/ipv4/fib_trie.c#L1729">1729</a>                         <b><i>/* cannot resize the trie vector */</i></b>
<a name="L1730" href="source/net/ipv4/fib_trie.c#L1730">1730</a>                         if (<a href="ident?i=IS_TRIE">IS_TRIE</a>(pn))
<a name="L1731" href="source/net/ipv4/fib_trie.c#L1731">1731</a>                                 break;
<a name="L1732" href="source/net/ipv4/fib_trie.c#L1732">1732</a> 
<a name="L1733" href="source/net/ipv4/fib_trie.c#L1733">1733</a>                         <b><i>/* resize completed node */</i></b>
<a name="L1734" href="source/net/ipv4/fib_trie.c#L1734">1734</a>                         pn = <a href="ident?i=resize">resize</a>(<a href="ident?i=t">t</a>, pn);
<a name="L1735" href="source/net/ipv4/fib_trie.c#L1735">1735</a>                         cindex = <a href="ident?i=get_index">get_index</a>(pkey, pn);
<a name="L1736" href="source/net/ipv4/fib_trie.c#L1736">1736</a> 
<a name="L1737" href="source/net/ipv4/fib_trie.c#L1737">1737</a>                         continue;
<a name="L1738" href="source/net/ipv4/fib_trie.c#L1738">1738</a>                 }
<a name="L1739" href="source/net/ipv4/fib_trie.c#L1739">1739</a> 
<a name="L1740" href="source/net/ipv4/fib_trie.c#L1740">1740</a>                 <b><i>/* grab the next available node */</i></b>
<a name="L1741" href="source/net/ipv4/fib_trie.c#L1741">1741</a>                 <a href="ident?i=n">n</a> = <a href="ident?i=get_child">get_child</a>(pn, cindex);
<a name="L1742" href="source/net/ipv4/fib_trie.c#L1742">1742</a>                 if (!<a href="ident?i=n">n</a>)
<a name="L1743" href="source/net/ipv4/fib_trie.c#L1743">1743</a>                         continue;
<a name="L1744" href="source/net/ipv4/fib_trie.c#L1744">1744</a> 
<a name="L1745" href="source/net/ipv4/fib_trie.c#L1745">1745</a>                 if (<a href="ident?i=IS_TNODE">IS_TNODE</a>(<a href="ident?i=n">n</a>)) {
<a name="L1746" href="source/net/ipv4/fib_trie.c#L1746">1746</a>                         <b><i>/* record pn and cindex for leaf walking */</i></b>
<a name="L1747" href="source/net/ipv4/fib_trie.c#L1747">1747</a>                         pn = <a href="ident?i=n">n</a>;
<a name="L1748" href="source/net/ipv4/fib_trie.c#L1748">1748</a>                         cindex = 1ul &lt;&lt; <a href="ident?i=n">n</a>-&gt;<a href="ident?i=bits">bits</a>;
<a name="L1749" href="source/net/ipv4/fib_trie.c#L1749">1749</a> 
<a name="L1750" href="source/net/ipv4/fib_trie.c#L1750">1750</a>                         continue;
<a name="L1751" href="source/net/ipv4/fib_trie.c#L1751">1751</a>                 }
<a name="L1752" href="source/net/ipv4/fib_trie.c#L1752">1752</a> 
<a name="L1753" href="source/net/ipv4/fib_trie.c#L1753">1753</a>                 <a href="ident?i=hlist_for_each_entry_safe">hlist_for_each_entry_safe</a>(fa, <a href="ident?i=tmp">tmp</a>, &amp;<a href="ident?i=n">n</a>-&gt;leaf, fa_list) {
<a name="L1754" href="source/net/ipv4/fib_trie.c#L1754">1754</a>                         struct <a href="ident?i=fib_info">fib_info</a> *fi = fa-&gt;fa_info;
<a name="L1755" href="source/net/ipv4/fib_trie.c#L1755">1755</a> 
<a name="L1756" href="source/net/ipv4/fib_trie.c#L1756">1756</a>                         <b><i>/* if alias was cloned to local then we just</i></b>
<a name="L1757" href="source/net/ipv4/fib_trie.c#L1757">1757</a> <b><i>                         * need to remove the local copy from main</i></b>
<a name="L1758" href="source/net/ipv4/fib_trie.c#L1758">1758</a> <b><i>                         */</i></b>
<a name="L1759" href="source/net/ipv4/fib_trie.c#L1759">1759</a>                         if (<a href="ident?i=tb">tb</a>-&gt;tb_id != fa-&gt;tb_id) {
<a name="L1760" href="source/net/ipv4/fib_trie.c#L1760">1760</a>                                 <a href="ident?i=hlist_del_rcu">hlist_del_rcu</a>(&amp;fa-&gt;fa_list);
<a name="L1761" href="source/net/ipv4/fib_trie.c#L1761">1761</a>                                 <a href="ident?i=alias_free_mem_rcu">alias_free_mem_rcu</a>(fa);
<a name="L1762" href="source/net/ipv4/fib_trie.c#L1762">1762</a>                                 continue;
<a name="L1763" href="source/net/ipv4/fib_trie.c#L1763">1763</a>                         }
<a name="L1764" href="source/net/ipv4/fib_trie.c#L1764">1764</a> 
<a name="L1765" href="source/net/ipv4/fib_trie.c#L1765">1765</a>                         <b><i>/* record local slen */</i></b>
<a name="L1766" href="source/net/ipv4/fib_trie.c#L1766">1766</a>                         slen = fa-&gt;fa_slen;
<a name="L1767" href="source/net/ipv4/fib_trie.c#L1767">1767</a> 
<a name="L1768" href="source/net/ipv4/fib_trie.c#L1768">1768</a>                         if (!fi || !(fi-&gt;fib_flags &amp; <a href="ident?i=RTNH_F_OFFLOAD">RTNH_F_OFFLOAD</a>))
<a name="L1769" href="source/net/ipv4/fib_trie.c#L1769">1769</a>                                 continue;
<a name="L1770" href="source/net/ipv4/fib_trie.c#L1770">1770</a> 
<a name="L1771" href="source/net/ipv4/fib_trie.c#L1771">1771</a>                         <a href="ident?i=netdev_switch_fib_ipv4_del">netdev_switch_fib_ipv4_del</a>(<a href="ident?i=n">n</a>-&gt;<a href="ident?i=key">key</a>,
<a name="L1772" href="source/net/ipv4/fib_trie.c#L1772">1772</a>                                                    <a href="ident?i=KEYLENGTH">KEYLENGTH</a> - fa-&gt;fa_slen,
<a name="L1773" href="source/net/ipv4/fib_trie.c#L1773">1773</a>                                                    fi, fa-&gt;fa_tos,
<a name="L1774" href="source/net/ipv4/fib_trie.c#L1774">1774</a>                                                    fa-&gt;fa_type, <a href="ident?i=tb">tb</a>-&gt;tb_id);
<a name="L1775" href="source/net/ipv4/fib_trie.c#L1775">1775</a>                 }
<a name="L1776" href="source/net/ipv4/fib_trie.c#L1776">1776</a> 
<a name="L1777" href="source/net/ipv4/fib_trie.c#L1777">1777</a>                 <b><i>/* update leaf slen */</i></b>
<a name="L1778" href="source/net/ipv4/fib_trie.c#L1778">1778</a>                 <a href="ident?i=n">n</a>-&gt;slen = slen;
<a name="L1779" href="source/net/ipv4/fib_trie.c#L1779">1779</a> 
<a name="L1780" href="source/net/ipv4/fib_trie.c#L1780">1780</a>                 if (<a href="ident?i=hlist_empty">hlist_empty</a>(&amp;<a href="ident?i=n">n</a>-&gt;leaf)) {
<a name="L1781" href="source/net/ipv4/fib_trie.c#L1781">1781</a>                         <a href="ident?i=put_child_root">put_child_root</a>(pn, <a href="ident?i=n">n</a>-&gt;<a href="ident?i=key">key</a>, <a href="ident?i=NULL">NULL</a>);
<a name="L1782" href="source/net/ipv4/fib_trie.c#L1782">1782</a>                         <a href="ident?i=node_free">node_free</a>(<a href="ident?i=n">n</a>);
<a name="L1783" href="source/net/ipv4/fib_trie.c#L1783">1783</a>                 } else {
<a name="L1784" href="source/net/ipv4/fib_trie.c#L1784">1784</a>                         <a href="ident?i=leaf_pull_suffix">leaf_pull_suffix</a>(pn, <a href="ident?i=n">n</a>);
<a name="L1785" href="source/net/ipv4/fib_trie.c#L1785">1785</a>                 }
<a name="L1786" href="source/net/ipv4/fib_trie.c#L1786">1786</a>         }
<a name="L1787" href="source/net/ipv4/fib_trie.c#L1787">1787</a> }
<a name="L1788" href="source/net/ipv4/fib_trie.c#L1788">1788</a> 
<a name="L1789" href="source/net/ipv4/fib_trie.c#L1789">1789</a> <b><i>/* Caller must hold RTNL. */</i></b>
<a name="L1790" href="source/net/ipv4/fib_trie.c#L1790">1790</a> int <a href="ident?i=fib_table_flush">fib_table_flush</a>(struct <a href="ident?i=fib_table">fib_table</a> *<a href="ident?i=tb">tb</a>)
<a name="L1791" href="source/net/ipv4/fib_trie.c#L1791">1791</a> {
<a name="L1792" href="source/net/ipv4/fib_trie.c#L1792">1792</a>         struct <a href="ident?i=trie">trie</a> *<a href="ident?i=t">t</a> = (struct <a href="ident?i=trie">trie</a> *)<a href="ident?i=tb">tb</a>-&gt;tb_data;
<a name="L1793" href="source/net/ipv4/fib_trie.c#L1793">1793</a>         struct <a href="ident?i=key_vector">key_vector</a> *pn = <a href="ident?i=t">t</a>-&gt;kv;
<a name="L1794" href="source/net/ipv4/fib_trie.c#L1794">1794</a>         unsigned long cindex = 1;
<a name="L1795" href="source/net/ipv4/fib_trie.c#L1795">1795</a>         struct <a href="ident?i=hlist_node">hlist_node</a> *<a href="ident?i=tmp">tmp</a>;
<a name="L1796" href="source/net/ipv4/fib_trie.c#L1796">1796</a>         struct <a href="ident?i=fib_alias">fib_alias</a> *fa;
<a name="L1797" href="source/net/ipv4/fib_trie.c#L1797">1797</a>         int <a href="ident?i=found">found</a> = 0;
<a name="L1798" href="source/net/ipv4/fib_trie.c#L1798">1798</a> 
<a name="L1799" href="source/net/ipv4/fib_trie.c#L1799">1799</a>         <b><i>/* walk trie in reverse order */</i></b>
<a name="L1800" href="source/net/ipv4/fib_trie.c#L1800">1800</a>         for (;;) {
<a name="L1801" href="source/net/ipv4/fib_trie.c#L1801">1801</a>                 unsigned char slen = 0;
<a name="L1802" href="source/net/ipv4/fib_trie.c#L1802">1802</a>                 struct <a href="ident?i=key_vector">key_vector</a> *<a href="ident?i=n">n</a>;
<a name="L1803" href="source/net/ipv4/fib_trie.c#L1803">1803</a> 
<a name="L1804" href="source/net/ipv4/fib_trie.c#L1804">1804</a>                 if (!(cindex--)) {
<a name="L1805" href="source/net/ipv4/fib_trie.c#L1805">1805</a>                         <a href="ident?i=t_key">t_key</a> pkey = pn-&gt;<a href="ident?i=key">key</a>;
<a name="L1806" href="source/net/ipv4/fib_trie.c#L1806">1806</a> 
<a name="L1807" href="source/net/ipv4/fib_trie.c#L1807">1807</a>                         <b><i>/* cannot resize the trie vector */</i></b>
<a name="L1808" href="source/net/ipv4/fib_trie.c#L1808">1808</a>                         if (<a href="ident?i=IS_TRIE">IS_TRIE</a>(pn))
<a name="L1809" href="source/net/ipv4/fib_trie.c#L1809">1809</a>                                 break;
<a name="L1810" href="source/net/ipv4/fib_trie.c#L1810">1810</a> 
<a name="L1811" href="source/net/ipv4/fib_trie.c#L1811">1811</a>                         <b><i>/* resize completed node */</i></b>
<a name="L1812" href="source/net/ipv4/fib_trie.c#L1812">1812</a>                         pn = <a href="ident?i=resize">resize</a>(<a href="ident?i=t">t</a>, pn);
<a name="L1813" href="source/net/ipv4/fib_trie.c#L1813">1813</a>                         cindex = <a href="ident?i=get_index">get_index</a>(pkey, pn);
<a name="L1814" href="source/net/ipv4/fib_trie.c#L1814">1814</a> 
<a name="L1815" href="source/net/ipv4/fib_trie.c#L1815">1815</a>                         continue;
<a name="L1816" href="source/net/ipv4/fib_trie.c#L1816">1816</a>                 }
<a name="L1817" href="source/net/ipv4/fib_trie.c#L1817">1817</a> 
<a name="L1818" href="source/net/ipv4/fib_trie.c#L1818">1818</a>                 <b><i>/* grab the next available node */</i></b>
<a name="L1819" href="source/net/ipv4/fib_trie.c#L1819">1819</a>                 <a href="ident?i=n">n</a> = <a href="ident?i=get_child">get_child</a>(pn, cindex);
<a name="L1820" href="source/net/ipv4/fib_trie.c#L1820">1820</a>                 if (!<a href="ident?i=n">n</a>)
<a name="L1821" href="source/net/ipv4/fib_trie.c#L1821">1821</a>                         continue;
<a name="L1822" href="source/net/ipv4/fib_trie.c#L1822">1822</a> 
<a name="L1823" href="source/net/ipv4/fib_trie.c#L1823">1823</a>                 if (<a href="ident?i=IS_TNODE">IS_TNODE</a>(<a href="ident?i=n">n</a>)) {
<a name="L1824" href="source/net/ipv4/fib_trie.c#L1824">1824</a>                         <b><i>/* record pn and cindex for leaf walking */</i></b>
<a name="L1825" href="source/net/ipv4/fib_trie.c#L1825">1825</a>                         pn = <a href="ident?i=n">n</a>;
<a name="L1826" href="source/net/ipv4/fib_trie.c#L1826">1826</a>                         cindex = 1ul &lt;&lt; <a href="ident?i=n">n</a>-&gt;<a href="ident?i=bits">bits</a>;
<a name="L1827" href="source/net/ipv4/fib_trie.c#L1827">1827</a> 
<a name="L1828" href="source/net/ipv4/fib_trie.c#L1828">1828</a>                         continue;
<a name="L1829" href="source/net/ipv4/fib_trie.c#L1829">1829</a>                 }
<a name="L1830" href="source/net/ipv4/fib_trie.c#L1830">1830</a> 
<a name="L1831" href="source/net/ipv4/fib_trie.c#L1831">1831</a>                 <a href="ident?i=hlist_for_each_entry_safe">hlist_for_each_entry_safe</a>(fa, <a href="ident?i=tmp">tmp</a>, &amp;<a href="ident?i=n">n</a>-&gt;leaf, fa_list) {
<a name="L1832" href="source/net/ipv4/fib_trie.c#L1832">1832</a>                         struct <a href="ident?i=fib_info">fib_info</a> *fi = fa-&gt;fa_info;
<a name="L1833" href="source/net/ipv4/fib_trie.c#L1833">1833</a> 
<a name="L1834" href="source/net/ipv4/fib_trie.c#L1834">1834</a>                         if (!fi || !(fi-&gt;fib_flags &amp; <a href="ident?i=RTNH_F_DEAD">RTNH_F_DEAD</a>)) {
<a name="L1835" href="source/net/ipv4/fib_trie.c#L1835">1835</a>                                 slen = fa-&gt;fa_slen;
<a name="L1836" href="source/net/ipv4/fib_trie.c#L1836">1836</a>                                 continue;
<a name="L1837" href="source/net/ipv4/fib_trie.c#L1837">1837</a>                         }
<a name="L1838" href="source/net/ipv4/fib_trie.c#L1838">1838</a> 
<a name="L1839" href="source/net/ipv4/fib_trie.c#L1839">1839</a>                         <a href="ident?i=netdev_switch_fib_ipv4_del">netdev_switch_fib_ipv4_del</a>(<a href="ident?i=n">n</a>-&gt;<a href="ident?i=key">key</a>,
<a name="L1840" href="source/net/ipv4/fib_trie.c#L1840">1840</a>                                                    <a href="ident?i=KEYLENGTH">KEYLENGTH</a> - fa-&gt;fa_slen,
<a name="L1841" href="source/net/ipv4/fib_trie.c#L1841">1841</a>                                                    fi, fa-&gt;fa_tos,
<a name="L1842" href="source/net/ipv4/fib_trie.c#L1842">1842</a>                                                    fa-&gt;fa_type, <a href="ident?i=tb">tb</a>-&gt;tb_id);
<a name="L1843" href="source/net/ipv4/fib_trie.c#L1843">1843</a>                         <a href="ident?i=hlist_del_rcu">hlist_del_rcu</a>(&amp;fa-&gt;fa_list);
<a name="L1844" href="source/net/ipv4/fib_trie.c#L1844">1844</a>                         <a href="ident?i=fib_release_info">fib_release_info</a>(fa-&gt;fa_info);
<a name="L1845" href="source/net/ipv4/fib_trie.c#L1845">1845</a>                         <a href="ident?i=alias_free_mem_rcu">alias_free_mem_rcu</a>(fa);
<a name="L1846" href="source/net/ipv4/fib_trie.c#L1846">1846</a>                         <a href="ident?i=found">found</a>++;
<a name="L1847" href="source/net/ipv4/fib_trie.c#L1847">1847</a>                 }
<a name="L1848" href="source/net/ipv4/fib_trie.c#L1848">1848</a> 
<a name="L1849" href="source/net/ipv4/fib_trie.c#L1849">1849</a>                 <b><i>/* update leaf slen */</i></b>
<a name="L1850" href="source/net/ipv4/fib_trie.c#L1850">1850</a>                 <a href="ident?i=n">n</a>-&gt;slen = slen;
<a name="L1851" href="source/net/ipv4/fib_trie.c#L1851">1851</a> 
<a name="L1852" href="source/net/ipv4/fib_trie.c#L1852">1852</a>                 if (<a href="ident?i=hlist_empty">hlist_empty</a>(&amp;<a href="ident?i=n">n</a>-&gt;leaf)) {
<a name="L1853" href="source/net/ipv4/fib_trie.c#L1853">1853</a>                         <a href="ident?i=put_child_root">put_child_root</a>(pn, <a href="ident?i=n">n</a>-&gt;<a href="ident?i=key">key</a>, <a href="ident?i=NULL">NULL</a>);
<a name="L1854" href="source/net/ipv4/fib_trie.c#L1854">1854</a>                         <a href="ident?i=node_free">node_free</a>(<a href="ident?i=n">n</a>);
<a name="L1855" href="source/net/ipv4/fib_trie.c#L1855">1855</a>                 } else {
<a name="L1856" href="source/net/ipv4/fib_trie.c#L1856">1856</a>                         <a href="ident?i=leaf_pull_suffix">leaf_pull_suffix</a>(pn, <a href="ident?i=n">n</a>);
<a name="L1857" href="source/net/ipv4/fib_trie.c#L1857">1857</a>                 }
<a name="L1858" href="source/net/ipv4/fib_trie.c#L1858">1858</a>         }
<a name="L1859" href="source/net/ipv4/fib_trie.c#L1859">1859</a> 
<a name="L1860" href="source/net/ipv4/fib_trie.c#L1860">1860</a>         <a href="ident?i=pr_debug">pr_debug</a>(<i>"trie_flush found=%d\n"</i>, <a href="ident?i=found">found</a>);
<a name="L1861" href="source/net/ipv4/fib_trie.c#L1861">1861</a>         return <a href="ident?i=found">found</a>;
<a name="L1862" href="source/net/ipv4/fib_trie.c#L1862">1862</a> }
<a name="L1863" href="source/net/ipv4/fib_trie.c#L1863">1863</a> 
<a name="L1864" href="source/net/ipv4/fib_trie.c#L1864">1864</a> static void <a href="ident?i=__trie_free_rcu">__trie_free_rcu</a>(struct <a href="ident?i=rcu_head">rcu_head</a> *<a href="ident?i=head">head</a>)
<a name="L1865" href="source/net/ipv4/fib_trie.c#L1865">1865</a> {
<a name="L1866" href="source/net/ipv4/fib_trie.c#L1866">1866</a>         struct <a href="ident?i=fib_table">fib_table</a> *<a href="ident?i=tb">tb</a> = <a href="ident?i=container_of">container_of</a>(<a href="ident?i=head">head</a>, struct <a href="ident?i=fib_table">fib_table</a>, rcu);
<a name="L1867" href="source/net/ipv4/fib_trie.c#L1867">1867</a> #ifdef CONFIG_IP_FIB_TRIE_STATS
<a name="L1868" href="source/net/ipv4/fib_trie.c#L1868">1868</a>         struct <a href="ident?i=trie">trie</a> *<a href="ident?i=t">t</a> = (struct <a href="ident?i=trie">trie</a> *)<a href="ident?i=tb">tb</a>-&gt;tb_data;
<a name="L1869" href="source/net/ipv4/fib_trie.c#L1869">1869</a> 
<a name="L1870" href="source/net/ipv4/fib_trie.c#L1870">1870</a>         if (<a href="ident?i=tb">tb</a>-&gt;tb_data == <a href="ident?i=tb">tb</a>-&gt;__data)
<a name="L1871" href="source/net/ipv4/fib_trie.c#L1871">1871</a>                 <a href="ident?i=free_percpu">free_percpu</a>(<a href="ident?i=t">t</a>-&gt;<a href="ident?i=stats">stats</a>);
<a name="L1872" href="source/net/ipv4/fib_trie.c#L1872">1872</a> #endif <b><i>/* CONFIG_IP_FIB_TRIE_STATS */</i></b>
<a name="L1873" href="source/net/ipv4/fib_trie.c#L1873">1873</a>         <a href="ident?i=kfree">kfree</a>(<a href="ident?i=tb">tb</a>);
<a name="L1874" href="source/net/ipv4/fib_trie.c#L1874">1874</a> }
<a name="L1875" href="source/net/ipv4/fib_trie.c#L1875">1875</a> 
<a name="L1876" href="source/net/ipv4/fib_trie.c#L1876">1876</a> void <a href="ident?i=fib_free_table">fib_free_table</a>(struct <a href="ident?i=fib_table">fib_table</a> *<a href="ident?i=tb">tb</a>)
<a name="L1877" href="source/net/ipv4/fib_trie.c#L1877">1877</a> {
<a name="L1878" href="source/net/ipv4/fib_trie.c#L1878">1878</a>         <a href="ident?i=call_rcu">call_rcu</a>(&amp;<a href="ident?i=tb">tb</a>-&gt;rcu, <a href="ident?i=__trie_free_rcu">__trie_free_rcu</a>);
<a name="L1879" href="source/net/ipv4/fib_trie.c#L1879">1879</a> }
<a name="L1880" href="source/net/ipv4/fib_trie.c#L1880">1880</a> 
<a name="L1881" href="source/net/ipv4/fib_trie.c#L1881">1881</a> static int <a href="ident?i=fn_trie_dump_leaf">fn_trie_dump_leaf</a>(struct <a href="ident?i=key_vector">key_vector</a> *<a href="ident?i=l">l</a>, struct <a href="ident?i=fib_table">fib_table</a> *<a href="ident?i=tb">tb</a>,
<a name="L1882" href="source/net/ipv4/fib_trie.c#L1882">1882</a>                              struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, struct <a href="ident?i=netlink_callback">netlink_callback</a> *<a href="ident?i=cb">cb</a>)
<a name="L1883" href="source/net/ipv4/fib_trie.c#L1883">1883</a> {
<a name="L1884" href="source/net/ipv4/fib_trie.c#L1884">1884</a>         <a href="ident?i=__be32">__be32</a> xkey = <a href="ident?i=htonl">htonl</a>(<a href="ident?i=l">l</a>-&gt;<a href="ident?i=key">key</a>);
<a name="L1885" href="source/net/ipv4/fib_trie.c#L1885">1885</a>         struct <a href="ident?i=fib_alias">fib_alias</a> *fa;
<a name="L1886" href="source/net/ipv4/fib_trie.c#L1886">1886</a>         int <a href="ident?i=i">i</a>, s_i;
<a name="L1887" href="source/net/ipv4/fib_trie.c#L1887">1887</a> 
<a name="L1888" href="source/net/ipv4/fib_trie.c#L1888">1888</a>         s_i = <a href="ident?i=cb">cb</a>-&gt;<a href="ident?i=args">args</a>[4];
<a name="L1889" href="source/net/ipv4/fib_trie.c#L1889">1889</a>         <a href="ident?i=i">i</a> = 0;
<a name="L1890" href="source/net/ipv4/fib_trie.c#L1890">1890</a> 
<a name="L1891" href="source/net/ipv4/fib_trie.c#L1891">1891</a>         <b><i>/* rcu_read_lock is hold by caller */</i></b>
<a name="L1892" href="source/net/ipv4/fib_trie.c#L1892">1892</a>         <a href="ident?i=hlist_for_each_entry_rcu">hlist_for_each_entry_rcu</a>(fa, &amp;<a href="ident?i=l">l</a>-&gt;leaf, fa_list) {
<a name="L1893" href="source/net/ipv4/fib_trie.c#L1893">1893</a>                 if (<a href="ident?i=i">i</a> &lt; s_i) {
<a name="L1894" href="source/net/ipv4/fib_trie.c#L1894">1894</a>                         <a href="ident?i=i">i</a>++;
<a name="L1895" href="source/net/ipv4/fib_trie.c#L1895">1895</a>                         continue;
<a name="L1896" href="source/net/ipv4/fib_trie.c#L1896">1896</a>                 }
<a name="L1897" href="source/net/ipv4/fib_trie.c#L1897">1897</a> 
<a name="L1898" href="source/net/ipv4/fib_trie.c#L1898">1898</a>                 if (<a href="ident?i=tb">tb</a>-&gt;tb_id != fa-&gt;tb_id) {
<a name="L1899" href="source/net/ipv4/fib_trie.c#L1899">1899</a>                         <a href="ident?i=i">i</a>++;
<a name="L1900" href="source/net/ipv4/fib_trie.c#L1900">1900</a>                         continue;
<a name="L1901" href="source/net/ipv4/fib_trie.c#L1901">1901</a>                 }
<a name="L1902" href="source/net/ipv4/fib_trie.c#L1902">1902</a> 
<a name="L1903" href="source/net/ipv4/fib_trie.c#L1903">1903</a>                 if (<a href="ident?i=fib_dump_info">fib_dump_info</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=NETLINK_CB">NETLINK_CB</a>(<a href="ident?i=cb">cb</a>-&gt;<a href="ident?i=skb">skb</a>).portid,
<a name="L1904" href="source/net/ipv4/fib_trie.c#L1904">1904</a>                                   <a href="ident?i=cb">cb</a>-&gt;nlh-&gt;nlmsg_seq,
<a name="L1905" href="source/net/ipv4/fib_trie.c#L1905">1905</a>                                   <a href="ident?i=RTM_NEWROUTE">RTM_NEWROUTE</a>,
<a name="L1906" href="source/net/ipv4/fib_trie.c#L1906">1906</a>                                   <a href="ident?i=tb">tb</a>-&gt;tb_id,
<a name="L1907" href="source/net/ipv4/fib_trie.c#L1907">1907</a>                                   fa-&gt;fa_type,
<a name="L1908" href="source/net/ipv4/fib_trie.c#L1908">1908</a>                                   xkey,
<a name="L1909" href="source/net/ipv4/fib_trie.c#L1909">1909</a>                                   <a href="ident?i=KEYLENGTH">KEYLENGTH</a> - fa-&gt;fa_slen,
<a name="L1910" href="source/net/ipv4/fib_trie.c#L1910">1910</a>                                   fa-&gt;fa_tos,
<a name="L1911" href="source/net/ipv4/fib_trie.c#L1911">1911</a>                                   fa-&gt;fa_info, <a href="ident?i=NLM_F_MULTI">NLM_F_MULTI</a>) &lt; 0) {
<a name="L1912" href="source/net/ipv4/fib_trie.c#L1912">1912</a>                         <a href="ident?i=cb">cb</a>-&gt;<a href="ident?i=args">args</a>[4] = <a href="ident?i=i">i</a>;
<a name="L1913" href="source/net/ipv4/fib_trie.c#L1913">1913</a>                         return -1;
<a name="L1914" href="source/net/ipv4/fib_trie.c#L1914">1914</a>                 }
<a name="L1915" href="source/net/ipv4/fib_trie.c#L1915">1915</a>                 <a href="ident?i=i">i</a>++;
<a name="L1916" href="source/net/ipv4/fib_trie.c#L1916">1916</a>         }
<a name="L1917" href="source/net/ipv4/fib_trie.c#L1917">1917</a> 
<a name="L1918" href="source/net/ipv4/fib_trie.c#L1918">1918</a>         <a href="ident?i=cb">cb</a>-&gt;<a href="ident?i=args">args</a>[4] = <a href="ident?i=i">i</a>;
<a name="L1919" href="source/net/ipv4/fib_trie.c#L1919">1919</a>         return <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a>;
<a name="L1920" href="source/net/ipv4/fib_trie.c#L1920">1920</a> }
<a name="L1921" href="source/net/ipv4/fib_trie.c#L1921">1921</a> 
<a name="L1922" href="source/net/ipv4/fib_trie.c#L1922">1922</a> <b><i>/* rcu_read_lock needs to be hold by caller from readside */</i></b>
<a name="L1923" href="source/net/ipv4/fib_trie.c#L1923">1923</a> int <a href="ident?i=fib_table_dump">fib_table_dump</a>(struct <a href="ident?i=fib_table">fib_table</a> *<a href="ident?i=tb">tb</a>, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
<a name="L1924" href="source/net/ipv4/fib_trie.c#L1924">1924</a>                    struct <a href="ident?i=netlink_callback">netlink_callback</a> *<a href="ident?i=cb">cb</a>)
<a name="L1925" href="source/net/ipv4/fib_trie.c#L1925">1925</a> {
<a name="L1926" href="source/net/ipv4/fib_trie.c#L1926">1926</a>         struct <a href="ident?i=trie">trie</a> *<a href="ident?i=t">t</a> = (struct <a href="ident?i=trie">trie</a> *)<a href="ident?i=tb">tb</a>-&gt;tb_data;
<a name="L1927" href="source/net/ipv4/fib_trie.c#L1927">1927</a>         struct <a href="ident?i=key_vector">key_vector</a> *<a href="ident?i=l">l</a>, *<a href="ident?i=tp">tp</a> = <a href="ident?i=t">t</a>-&gt;kv;
<a name="L1928" href="source/net/ipv4/fib_trie.c#L1928">1928</a>         <b><i>/* Dump starting at last key.</i></b>
<a name="L1929" href="source/net/ipv4/fib_trie.c#L1929">1929</a> <b><i>         * Note: 0.0.0.0/0 (ie default) is first key.</i></b>
<a name="L1930" href="source/net/ipv4/fib_trie.c#L1930">1930</a> <b><i>         */</i></b>
<a name="L1931" href="source/net/ipv4/fib_trie.c#L1931">1931</a>         int <a href="ident?i=count">count</a> = <a href="ident?i=cb">cb</a>-&gt;<a href="ident?i=args">args</a>[2];
<a name="L1932" href="source/net/ipv4/fib_trie.c#L1932">1932</a>         <a href="ident?i=t_key">t_key</a> <a href="ident?i=key">key</a> = <a href="ident?i=cb">cb</a>-&gt;<a href="ident?i=args">args</a>[3];
<a name="L1933" href="source/net/ipv4/fib_trie.c#L1933">1933</a> 
<a name="L1934" href="source/net/ipv4/fib_trie.c#L1934">1934</a>         while ((<a href="ident?i=l">l</a> = <a href="ident?i=leaf_walk_rcu">leaf_walk_rcu</a>(&amp;<a href="ident?i=tp">tp</a>, <a href="ident?i=key">key</a>)) != <a href="ident?i=NULL">NULL</a>) {
<a name="L1935" href="source/net/ipv4/fib_trie.c#L1935">1935</a>                 if (<a href="ident?i=fn_trie_dump_leaf">fn_trie_dump_leaf</a>(<a href="ident?i=l">l</a>, <a href="ident?i=tb">tb</a>, <a href="ident?i=skb">skb</a>, <a href="ident?i=cb">cb</a>) &lt; 0) {
<a name="L1936" href="source/net/ipv4/fib_trie.c#L1936">1936</a>                         <a href="ident?i=cb">cb</a>-&gt;<a href="ident?i=args">args</a>[3] = <a href="ident?i=key">key</a>;
<a name="L1937" href="source/net/ipv4/fib_trie.c#L1937">1937</a>                         <a href="ident?i=cb">cb</a>-&gt;<a href="ident?i=args">args</a>[2] = <a href="ident?i=count">count</a>;
<a name="L1938" href="source/net/ipv4/fib_trie.c#L1938">1938</a>                         return -1;
<a name="L1939" href="source/net/ipv4/fib_trie.c#L1939">1939</a>                 }
<a name="L1940" href="source/net/ipv4/fib_trie.c#L1940">1940</a> 
<a name="L1941" href="source/net/ipv4/fib_trie.c#L1941">1941</a>                 ++<a href="ident?i=count">count</a>;
<a name="L1942" href="source/net/ipv4/fib_trie.c#L1942">1942</a>                 <a href="ident?i=key">key</a> = <a href="ident?i=l">l</a>-&gt;<a href="ident?i=key">key</a> + 1;
<a name="L1943" href="source/net/ipv4/fib_trie.c#L1943">1943</a> 
<a name="L1944" href="source/net/ipv4/fib_trie.c#L1944">1944</a>                 <a href="ident?i=memset">memset</a>(&amp;<a href="ident?i=cb">cb</a>-&gt;<a href="ident?i=args">args</a>[4], 0,
<a name="L1945" href="source/net/ipv4/fib_trie.c#L1945">1945</a>                        sizeof(<a href="ident?i=cb">cb</a>-&gt;<a href="ident?i=args">args</a>) - 4*sizeof(<a href="ident?i=cb">cb</a>-&gt;<a href="ident?i=args">args</a>[0]));
<a name="L1946" href="source/net/ipv4/fib_trie.c#L1946">1946</a> 
<a name="L1947" href="source/net/ipv4/fib_trie.c#L1947">1947</a>                 <b><i>/* stop loop if key wrapped back to 0 */</i></b>
<a name="L1948" href="source/net/ipv4/fib_trie.c#L1948">1948</a>                 if (<a href="ident?i=key">key</a> &lt; <a href="ident?i=l">l</a>-&gt;<a href="ident?i=key">key</a>)
<a name="L1949" href="source/net/ipv4/fib_trie.c#L1949">1949</a>                         break;
<a name="L1950" href="source/net/ipv4/fib_trie.c#L1950">1950</a>         }
<a name="L1951" href="source/net/ipv4/fib_trie.c#L1951">1951</a> 
<a name="L1952" href="source/net/ipv4/fib_trie.c#L1952">1952</a>         <a href="ident?i=cb">cb</a>-&gt;<a href="ident?i=args">args</a>[3] = <a href="ident?i=key">key</a>;
<a name="L1953" href="source/net/ipv4/fib_trie.c#L1953">1953</a>         <a href="ident?i=cb">cb</a>-&gt;<a href="ident?i=args">args</a>[2] = <a href="ident?i=count">count</a>;
<a name="L1954" href="source/net/ipv4/fib_trie.c#L1954">1954</a> 
<a name="L1955" href="source/net/ipv4/fib_trie.c#L1955">1955</a>         return <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a>;
<a name="L1956" href="source/net/ipv4/fib_trie.c#L1956">1956</a> }
<a name="L1957" href="source/net/ipv4/fib_trie.c#L1957">1957</a> 
<a name="L1958" href="source/net/ipv4/fib_trie.c#L1958">1958</a> void <a href="ident?i=__init">__init</a> <a href="ident?i=fib_trie_init">fib_trie_init</a>(void)
<a name="L1959" href="source/net/ipv4/fib_trie.c#L1959">1959</a> {
<a name="L1960" href="source/net/ipv4/fib_trie.c#L1960">1960</a>         fn_alias_kmem = <a href="ident?i=kmem_cache_create">kmem_cache_create</a>(<i>"ip_fib_alias"</i>,
<a name="L1961" href="source/net/ipv4/fib_trie.c#L1961">1961</a>                                           sizeof(struct <a href="ident?i=fib_alias">fib_alias</a>),
<a name="L1962" href="source/net/ipv4/fib_trie.c#L1962">1962</a>                                           0, <a href="ident?i=SLAB_PANIC">SLAB_PANIC</a>, <a href="ident?i=NULL">NULL</a>);
<a name="L1963" href="source/net/ipv4/fib_trie.c#L1963">1963</a> 
<a name="L1964" href="source/net/ipv4/fib_trie.c#L1964">1964</a>         trie_leaf_kmem = <a href="ident?i=kmem_cache_create">kmem_cache_create</a>(<i>"ip_fib_trie"</i>,
<a name="L1965" href="source/net/ipv4/fib_trie.c#L1965">1965</a>                                            <a href="ident?i=LEAF_SIZE">LEAF_SIZE</a>,
<a name="L1966" href="source/net/ipv4/fib_trie.c#L1966">1966</a>                                            0, <a href="ident?i=SLAB_PANIC">SLAB_PANIC</a>, <a href="ident?i=NULL">NULL</a>);
<a name="L1967" href="source/net/ipv4/fib_trie.c#L1967">1967</a> }
<a name="L1968" href="source/net/ipv4/fib_trie.c#L1968">1968</a> 
<a name="L1969" href="source/net/ipv4/fib_trie.c#L1969">1969</a> struct <a href="ident?i=fib_table">fib_table</a> *<a href="ident?i=fib_trie_table">fib_trie_table</a>(<a href="ident?i=u32">u32</a> <a href="ident?i=id">id</a>, struct <a href="ident?i=fib_table">fib_table</a> *<a href="ident?i=alias">alias</a>)
<a name="L1970" href="source/net/ipv4/fib_trie.c#L1970">1970</a> {
<a name="L1971" href="source/net/ipv4/fib_trie.c#L1971">1971</a>         struct <a href="ident?i=fib_table">fib_table</a> *<a href="ident?i=tb">tb</a>;
<a name="L1972" href="source/net/ipv4/fib_trie.c#L1972">1972</a>         struct <a href="ident?i=trie">trie</a> *<a href="ident?i=t">t</a>;
<a name="L1973" href="source/net/ipv4/fib_trie.c#L1973">1973</a>         <a href="ident?i=size_t">size_t</a> sz = sizeof(*<a href="ident?i=tb">tb</a>);
<a name="L1974" href="source/net/ipv4/fib_trie.c#L1974">1974</a> 
<a name="L1975" href="source/net/ipv4/fib_trie.c#L1975">1975</a>         if (!<a href="ident?i=alias">alias</a>)
<a name="L1976" href="source/net/ipv4/fib_trie.c#L1976">1976</a>                 sz += sizeof(struct <a href="ident?i=trie">trie</a>);
<a name="L1977" href="source/net/ipv4/fib_trie.c#L1977">1977</a> 
<a name="L1978" href="source/net/ipv4/fib_trie.c#L1978">1978</a>         <a href="ident?i=tb">tb</a> = <a href="ident?i=kzalloc">kzalloc</a>(sz, <a href="ident?i=GFP_KERNEL">GFP_KERNEL</a>);
<a name="L1979" href="source/net/ipv4/fib_trie.c#L1979">1979</a>         if (!<a href="ident?i=tb">tb</a>)
<a name="L1980" href="source/net/ipv4/fib_trie.c#L1980">1980</a>                 return <a href="ident?i=NULL">NULL</a>;
<a name="L1981" href="source/net/ipv4/fib_trie.c#L1981">1981</a> 
<a name="L1982" href="source/net/ipv4/fib_trie.c#L1982">1982</a>         <a href="ident?i=tb">tb</a>-&gt;tb_id = <a href="ident?i=id">id</a>;
<a name="L1983" href="source/net/ipv4/fib_trie.c#L1983">1983</a>         <a href="ident?i=tb">tb</a>-&gt;tb_default = -1;
<a name="L1984" href="source/net/ipv4/fib_trie.c#L1984">1984</a>         <a href="ident?i=tb">tb</a>-&gt;tb_num_default = 0;
<a name="L1985" href="source/net/ipv4/fib_trie.c#L1985">1985</a>         <a href="ident?i=tb">tb</a>-&gt;tb_data = (<a href="ident?i=alias">alias</a> ? <a href="ident?i=alias">alias</a>-&gt;__data : <a href="ident?i=tb">tb</a>-&gt;__data);
<a name="L1986" href="source/net/ipv4/fib_trie.c#L1986">1986</a> 
<a name="L1987" href="source/net/ipv4/fib_trie.c#L1987">1987</a>         if (<a href="ident?i=alias">alias</a>)
<a name="L1988" href="source/net/ipv4/fib_trie.c#L1988">1988</a>                 return <a href="ident?i=tb">tb</a>;
<a name="L1989" href="source/net/ipv4/fib_trie.c#L1989">1989</a> 
<a name="L1990" href="source/net/ipv4/fib_trie.c#L1990">1990</a>         <a href="ident?i=t">t</a> = (struct <a href="ident?i=trie">trie</a> *) <a href="ident?i=tb">tb</a>-&gt;tb_data;
<a name="L1991" href="source/net/ipv4/fib_trie.c#L1991">1991</a>         <a href="ident?i=t">t</a>-&gt;kv[0].<a href="ident?i=pos">pos</a> = <a href="ident?i=KEYLENGTH">KEYLENGTH</a>;
<a name="L1992" href="source/net/ipv4/fib_trie.c#L1992">1992</a>         <a href="ident?i=t">t</a>-&gt;kv[0].slen = <a href="ident?i=KEYLENGTH">KEYLENGTH</a>;
<a name="L1993" href="source/net/ipv4/fib_trie.c#L1993">1993</a> #ifdef CONFIG_IP_FIB_TRIE_STATS
<a name="L1994" href="source/net/ipv4/fib_trie.c#L1994">1994</a>         <a href="ident?i=t">t</a>-&gt;<a href="ident?i=stats">stats</a> = <a href="ident?i=alloc_percpu">alloc_percpu</a>(struct <a href="ident?i=trie_use_stats">trie_use_stats</a>);
<a name="L1995" href="source/net/ipv4/fib_trie.c#L1995">1995</a>         if (!<a href="ident?i=t">t</a>-&gt;<a href="ident?i=stats">stats</a>) {
<a name="L1996" href="source/net/ipv4/fib_trie.c#L1996">1996</a>                 <a href="ident?i=kfree">kfree</a>(<a href="ident?i=tb">tb</a>);
<a name="L1997" href="source/net/ipv4/fib_trie.c#L1997">1997</a>                 <a href="ident?i=tb">tb</a> = <a href="ident?i=NULL">NULL</a>;
<a name="L1998" href="source/net/ipv4/fib_trie.c#L1998">1998</a>         }
<a name="L1999" href="source/net/ipv4/fib_trie.c#L1999">1999</a> #endif
<a name="L2000" href="source/net/ipv4/fib_trie.c#L2000">2000</a> 
<a name="L2001" href="source/net/ipv4/fib_trie.c#L2001">2001</a>         return <a href="ident?i=tb">tb</a>;
<a name="L2002" href="source/net/ipv4/fib_trie.c#L2002">2002</a> }
<a name="L2003" href="source/net/ipv4/fib_trie.c#L2003">2003</a> 
<a name="L2004" href="source/net/ipv4/fib_trie.c#L2004">2004</a> #ifdef CONFIG_PROC_FS
<a name="L2005" href="source/net/ipv4/fib_trie.c#L2005">2005</a> <b><i>/* Depth first Trie walk iterator */</i></b>
<a name="L2006" href="source/net/ipv4/fib_trie.c#L2006">2006</a> struct <a href="ident?i=fib_trie_iter">fib_trie_iter</a> {
<a name="L2007" href="source/net/ipv4/fib_trie.c#L2007">2007</a>         struct <a href="ident?i=seq_net_private">seq_net_private</a> <a href="ident?i=p">p</a>;
<a name="L2008" href="source/net/ipv4/fib_trie.c#L2008">2008</a>         struct <a href="ident?i=fib_table">fib_table</a> *<a href="ident?i=tb">tb</a>;
<a name="L2009" href="source/net/ipv4/fib_trie.c#L2009">2009</a>         struct <a href="ident?i=key_vector">key_vector</a> *<a href="ident?i=tnode">tnode</a>;
<a name="L2010" href="source/net/ipv4/fib_trie.c#L2010">2010</a>         unsigned int <a href="ident?i=index">index</a>;
<a name="L2011" href="source/net/ipv4/fib_trie.c#L2011">2011</a>         unsigned int <a href="ident?i=depth">depth</a>;
<a name="L2012" href="source/net/ipv4/fib_trie.c#L2012">2012</a> };
<a name="L2013" href="source/net/ipv4/fib_trie.c#L2013">2013</a> 
<a name="L2014" href="source/net/ipv4/fib_trie.c#L2014">2014</a> static struct <a href="ident?i=key_vector">key_vector</a> *<a href="ident?i=fib_trie_get_next">fib_trie_get_next</a>(struct <a href="ident?i=fib_trie_iter">fib_trie_iter</a> *iter)
<a name="L2015" href="source/net/ipv4/fib_trie.c#L2015">2015</a> {
<a name="L2016" href="source/net/ipv4/fib_trie.c#L2016">2016</a>         unsigned long cindex = iter-&gt;<a href="ident?i=index">index</a>;
<a name="L2017" href="source/net/ipv4/fib_trie.c#L2017">2017</a>         struct <a href="ident?i=key_vector">key_vector</a> *pn = iter-&gt;<a href="ident?i=tnode">tnode</a>;
<a name="L2018" href="source/net/ipv4/fib_trie.c#L2018">2018</a>         <a href="ident?i=t_key">t_key</a> pkey;
<a name="L2019" href="source/net/ipv4/fib_trie.c#L2019">2019</a> 
<a name="L2020" href="source/net/ipv4/fib_trie.c#L2020">2020</a>         <a href="ident?i=pr_debug">pr_debug</a>(<i>"get_next iter={node=%p index=%d depth=%d}\n"</i>,
<a name="L2021" href="source/net/ipv4/fib_trie.c#L2021">2021</a>                  iter-&gt;<a href="ident?i=tnode">tnode</a>, iter-&gt;<a href="ident?i=index">index</a>, iter-&gt;<a href="ident?i=depth">depth</a>);
<a name="L2022" href="source/net/ipv4/fib_trie.c#L2022">2022</a> 
<a name="L2023" href="source/net/ipv4/fib_trie.c#L2023">2023</a>         while (!<a href="ident?i=IS_TRIE">IS_TRIE</a>(pn)) {
<a name="L2024" href="source/net/ipv4/fib_trie.c#L2024">2024</a>                 while (cindex &lt; <a href="ident?i=child_length">child_length</a>(pn)) {
<a name="L2025" href="source/net/ipv4/fib_trie.c#L2025">2025</a>                         struct <a href="ident?i=key_vector">key_vector</a> *<a href="ident?i=n">n</a> = <a href="ident?i=get_child_rcu">get_child_rcu</a>(pn, cindex++);
<a name="L2026" href="source/net/ipv4/fib_trie.c#L2026">2026</a> 
<a name="L2027" href="source/net/ipv4/fib_trie.c#L2027">2027</a>                         if (!<a href="ident?i=n">n</a>)
<a name="L2028" href="source/net/ipv4/fib_trie.c#L2028">2028</a>                                 continue;
<a name="L2029" href="source/net/ipv4/fib_trie.c#L2029">2029</a> 
<a name="L2030" href="source/net/ipv4/fib_trie.c#L2030">2030</a>                         if (<a href="ident?i=IS_LEAF">IS_LEAF</a>(<a href="ident?i=n">n</a>)) {
<a name="L2031" href="source/net/ipv4/fib_trie.c#L2031">2031</a>                                 iter-&gt;<a href="ident?i=tnode">tnode</a> = pn;
<a name="L2032" href="source/net/ipv4/fib_trie.c#L2032">2032</a>                                 iter-&gt;<a href="ident?i=index">index</a> = cindex;
<a name="L2033" href="source/net/ipv4/fib_trie.c#L2033">2033</a>                         } else {
<a name="L2034" href="source/net/ipv4/fib_trie.c#L2034">2034</a>                                 <b><i>/* push down one level */</i></b>
<a name="L2035" href="source/net/ipv4/fib_trie.c#L2035">2035</a>                                 iter-&gt;<a href="ident?i=tnode">tnode</a> = <a href="ident?i=n">n</a>;
<a name="L2036" href="source/net/ipv4/fib_trie.c#L2036">2036</a>                                 iter-&gt;<a href="ident?i=index">index</a> = 0;
<a name="L2037" href="source/net/ipv4/fib_trie.c#L2037">2037</a>                                 ++iter-&gt;<a href="ident?i=depth">depth</a>;
<a name="L2038" href="source/net/ipv4/fib_trie.c#L2038">2038</a>                         }
<a name="L2039" href="source/net/ipv4/fib_trie.c#L2039">2039</a> 
<a name="L2040" href="source/net/ipv4/fib_trie.c#L2040">2040</a>                         return <a href="ident?i=n">n</a>;
<a name="L2041" href="source/net/ipv4/fib_trie.c#L2041">2041</a>                 }
<a name="L2042" href="source/net/ipv4/fib_trie.c#L2042">2042</a> 
<a name="L2043" href="source/net/ipv4/fib_trie.c#L2043">2043</a>                 <b><i>/* Current node exhausted, pop back up */</i></b>
<a name="L2044" href="source/net/ipv4/fib_trie.c#L2044">2044</a>                 pkey = pn-&gt;<a href="ident?i=key">key</a>;
<a name="L2045" href="source/net/ipv4/fib_trie.c#L2045">2045</a>                 pn = <a href="ident?i=node_parent_rcu">node_parent_rcu</a>(pn);
<a name="L2046" href="source/net/ipv4/fib_trie.c#L2046">2046</a>                 cindex = <a href="ident?i=get_index">get_index</a>(pkey, pn) + 1;
<a name="L2047" href="source/net/ipv4/fib_trie.c#L2047">2047</a>                 --iter-&gt;<a href="ident?i=depth">depth</a>;
<a name="L2048" href="source/net/ipv4/fib_trie.c#L2048">2048</a>         }
<a name="L2049" href="source/net/ipv4/fib_trie.c#L2049">2049</a> 
<a name="L2050" href="source/net/ipv4/fib_trie.c#L2050">2050</a>         <b><i>/* record root node so further searches know we are done */</i></b>
<a name="L2051" href="source/net/ipv4/fib_trie.c#L2051">2051</a>         iter-&gt;<a href="ident?i=tnode">tnode</a> = pn;
<a name="L2052" href="source/net/ipv4/fib_trie.c#L2052">2052</a>         iter-&gt;<a href="ident?i=index">index</a> = 0;
<a name="L2053" href="source/net/ipv4/fib_trie.c#L2053">2053</a> 
<a name="L2054" href="source/net/ipv4/fib_trie.c#L2054">2054</a>         return <a href="ident?i=NULL">NULL</a>;
<a name="L2055" href="source/net/ipv4/fib_trie.c#L2055">2055</a> }
<a name="L2056" href="source/net/ipv4/fib_trie.c#L2056">2056</a> 
<a name="L2057" href="source/net/ipv4/fib_trie.c#L2057">2057</a> static struct <a href="ident?i=key_vector">key_vector</a> *<a href="ident?i=fib_trie_get_first">fib_trie_get_first</a>(struct <a href="ident?i=fib_trie_iter">fib_trie_iter</a> *iter,
<a name="L2058" href="source/net/ipv4/fib_trie.c#L2058">2058</a>                                              struct <a href="ident?i=trie">trie</a> *<a href="ident?i=t">t</a>)
<a name="L2059" href="source/net/ipv4/fib_trie.c#L2059">2059</a> {
<a name="L2060" href="source/net/ipv4/fib_trie.c#L2060">2060</a>         struct <a href="ident?i=key_vector">key_vector</a> *<a href="ident?i=n">n</a>, *pn = <a href="ident?i=t">t</a>-&gt;kv;
<a name="L2061" href="source/net/ipv4/fib_trie.c#L2061">2061</a> 
<a name="L2062" href="source/net/ipv4/fib_trie.c#L2062">2062</a>         if (!<a href="ident?i=t">t</a>)
<a name="L2063" href="source/net/ipv4/fib_trie.c#L2063">2063</a>                 return <a href="ident?i=NULL">NULL</a>;
<a name="L2064" href="source/net/ipv4/fib_trie.c#L2064">2064</a> 
<a name="L2065" href="source/net/ipv4/fib_trie.c#L2065">2065</a>         <a href="ident?i=n">n</a> = <a href="ident?i=rcu_dereference">rcu_dereference</a>(pn-&gt;<a href="ident?i=tnode">tnode</a>[0]);
<a name="L2066" href="source/net/ipv4/fib_trie.c#L2066">2066</a>         if (!<a href="ident?i=n">n</a>)
<a name="L2067" href="source/net/ipv4/fib_trie.c#L2067">2067</a>                 return <a href="ident?i=NULL">NULL</a>;
<a name="L2068" href="source/net/ipv4/fib_trie.c#L2068">2068</a> 
<a name="L2069" href="source/net/ipv4/fib_trie.c#L2069">2069</a>         if (<a href="ident?i=IS_TNODE">IS_TNODE</a>(<a href="ident?i=n">n</a>)) {
<a name="L2070" href="source/net/ipv4/fib_trie.c#L2070">2070</a>                 iter-&gt;<a href="ident?i=tnode">tnode</a> = <a href="ident?i=n">n</a>;
<a name="L2071" href="source/net/ipv4/fib_trie.c#L2071">2071</a>                 iter-&gt;<a href="ident?i=index">index</a> = 0;
<a name="L2072" href="source/net/ipv4/fib_trie.c#L2072">2072</a>                 iter-&gt;<a href="ident?i=depth">depth</a> = 1;
<a name="L2073" href="source/net/ipv4/fib_trie.c#L2073">2073</a>         } else {
<a name="L2074" href="source/net/ipv4/fib_trie.c#L2074">2074</a>                 iter-&gt;<a href="ident?i=tnode">tnode</a> = pn;
<a name="L2075" href="source/net/ipv4/fib_trie.c#L2075">2075</a>                 iter-&gt;<a href="ident?i=index">index</a> = 0;
<a name="L2076" href="source/net/ipv4/fib_trie.c#L2076">2076</a>                 iter-&gt;<a href="ident?i=depth">depth</a> = 0;
<a name="L2077" href="source/net/ipv4/fib_trie.c#L2077">2077</a>         }
<a name="L2078" href="source/net/ipv4/fib_trie.c#L2078">2078</a> 
<a name="L2079" href="source/net/ipv4/fib_trie.c#L2079">2079</a>         return <a href="ident?i=n">n</a>;
<a name="L2080" href="source/net/ipv4/fib_trie.c#L2080">2080</a> }
<a name="L2081" href="source/net/ipv4/fib_trie.c#L2081">2081</a> 
<a name="L2082" href="source/net/ipv4/fib_trie.c#L2082">2082</a> static void <a href="ident?i=trie_collect_stats">trie_collect_stats</a>(struct <a href="ident?i=trie">trie</a> *<a href="ident?i=t">t</a>, struct <a href="ident?i=trie_stat">trie_stat</a> *<a href="ident?i=s">s</a>)
<a name="L2083" href="source/net/ipv4/fib_trie.c#L2083">2083</a> {
<a name="L2084" href="source/net/ipv4/fib_trie.c#L2084">2084</a>         struct <a href="ident?i=key_vector">key_vector</a> *<a href="ident?i=n">n</a>;
<a name="L2085" href="source/net/ipv4/fib_trie.c#L2085">2085</a>         struct <a href="ident?i=fib_trie_iter">fib_trie_iter</a> iter;
<a name="L2086" href="source/net/ipv4/fib_trie.c#L2086">2086</a> 
<a name="L2087" href="source/net/ipv4/fib_trie.c#L2087">2087</a>         <a href="ident?i=memset">memset</a>(<a href="ident?i=s">s</a>, 0, sizeof(*<a href="ident?i=s">s</a>));
<a name="L2088" href="source/net/ipv4/fib_trie.c#L2088">2088</a> 
<a name="L2089" href="source/net/ipv4/fib_trie.c#L2089">2089</a>         <a href="ident?i=rcu_read_lock">rcu_read_lock</a>();
<a name="L2090" href="source/net/ipv4/fib_trie.c#L2090">2090</a>         for (<a href="ident?i=n">n</a> = <a href="ident?i=fib_trie_get_first">fib_trie_get_first</a>(&amp;iter, <a href="ident?i=t">t</a>); <a href="ident?i=n">n</a>; <a href="ident?i=n">n</a> = <a href="ident?i=fib_trie_get_next">fib_trie_get_next</a>(&amp;iter)) {
<a name="L2091" href="source/net/ipv4/fib_trie.c#L2091">2091</a>                 if (<a href="ident?i=IS_LEAF">IS_LEAF</a>(<a href="ident?i=n">n</a>)) {
<a name="L2092" href="source/net/ipv4/fib_trie.c#L2092">2092</a>                         struct <a href="ident?i=fib_alias">fib_alias</a> *fa;
<a name="L2093" href="source/net/ipv4/fib_trie.c#L2093">2093</a> 
<a name="L2094" href="source/net/ipv4/fib_trie.c#L2094">2094</a>                         <a href="ident?i=s">s</a>-&gt;leaves++;
<a name="L2095" href="source/net/ipv4/fib_trie.c#L2095">2095</a>                         <a href="ident?i=s">s</a>-&gt;totdepth += iter.<a href="ident?i=depth">depth</a>;
<a name="L2096" href="source/net/ipv4/fib_trie.c#L2096">2096</a>                         if (iter.<a href="ident?i=depth">depth</a> &gt; <a href="ident?i=s">s</a>-&gt;<a href="ident?i=maxdepth">maxdepth</a>)
<a name="L2097" href="source/net/ipv4/fib_trie.c#L2097">2097</a>                                 <a href="ident?i=s">s</a>-&gt;<a href="ident?i=maxdepth">maxdepth</a> = iter.<a href="ident?i=depth">depth</a>;
<a name="L2098" href="source/net/ipv4/fib_trie.c#L2098">2098</a> 
<a name="L2099" href="source/net/ipv4/fib_trie.c#L2099">2099</a>                         <a href="ident?i=hlist_for_each_entry_rcu">hlist_for_each_entry_rcu</a>(fa, &amp;<a href="ident?i=n">n</a>-&gt;leaf, fa_list)
<a name="L2100" href="source/net/ipv4/fib_trie.c#L2100">2100</a>                                 ++<a href="ident?i=s">s</a>-&gt;prefixes;
<a name="L2101" href="source/net/ipv4/fib_trie.c#L2101">2101</a>                 } else {
<a name="L2102" href="source/net/ipv4/fib_trie.c#L2102">2102</a>                         <a href="ident?i=s">s</a>-&gt;tnodes++;
<a name="L2103" href="source/net/ipv4/fib_trie.c#L2103">2103</a>                         if (<a href="ident?i=n">n</a>-&gt;<a href="ident?i=bits">bits</a> &lt; <a href="ident?i=MAX_STAT_DEPTH">MAX_STAT_DEPTH</a>)
<a name="L2104" href="source/net/ipv4/fib_trie.c#L2104">2104</a>                                 <a href="ident?i=s">s</a>-&gt;nodesizes[<a href="ident?i=n">n</a>-&gt;<a href="ident?i=bits">bits</a>]++;
<a name="L2105" href="source/net/ipv4/fib_trie.c#L2105">2105</a>                         <a href="ident?i=s">s</a>-&gt;nullpointers += <a href="ident?i=tn_info">tn_info</a>(<a href="ident?i=n">n</a>)-&gt;empty_children;
<a name="L2106" href="source/net/ipv4/fib_trie.c#L2106">2106</a>                 }
<a name="L2107" href="source/net/ipv4/fib_trie.c#L2107">2107</a>         }
<a name="L2108" href="source/net/ipv4/fib_trie.c#L2108">2108</a>         <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L2109" href="source/net/ipv4/fib_trie.c#L2109">2109</a> }
<a name="L2110" href="source/net/ipv4/fib_trie.c#L2110">2110</a> 
<a name="L2111" href="source/net/ipv4/fib_trie.c#L2111">2111</a> <b><i>/*</i></b>
<a name="L2112" href="source/net/ipv4/fib_trie.c#L2112">2112</a> <b><i> *      This outputs /proc/net/fib_triestats</i></b>
<a name="L2113" href="source/net/ipv4/fib_trie.c#L2113">2113</a> <b><i> */</i></b>
<a name="L2114" href="source/net/ipv4/fib_trie.c#L2114">2114</a> static void <a href="ident?i=trie_show_stats">trie_show_stats</a>(struct <a href="ident?i=seq_file">seq_file</a> *<a href="ident?i=seq">seq</a>, struct <a href="ident?i=trie_stat">trie_stat</a> *<a href="ident?i=stat">stat</a>)
<a name="L2115" href="source/net/ipv4/fib_trie.c#L2115">2115</a> {
<a name="L2116" href="source/net/ipv4/fib_trie.c#L2116">2116</a>         unsigned int <a href="ident?i=i">i</a>, <a href="ident?i=max">max</a>, pointers, <a href="ident?i=bytes">bytes</a>, avdepth;
<a name="L2117" href="source/net/ipv4/fib_trie.c#L2117">2117</a> 
<a name="L2118" href="source/net/ipv4/fib_trie.c#L2118">2118</a>         if (<a href="ident?i=stat">stat</a>-&gt;leaves)
<a name="L2119" href="source/net/ipv4/fib_trie.c#L2119">2119</a>                 avdepth = <a href="ident?i=stat">stat</a>-&gt;totdepth*100 / <a href="ident?i=stat">stat</a>-&gt;leaves;
<a name="L2120" href="source/net/ipv4/fib_trie.c#L2120">2120</a>         else
<a name="L2121" href="source/net/ipv4/fib_trie.c#L2121">2121</a>                 avdepth = 0;
<a name="L2122" href="source/net/ipv4/fib_trie.c#L2122">2122</a> 
<a name="L2123" href="source/net/ipv4/fib_trie.c#L2123">2123</a>         <a href="ident?i=seq_printf">seq_printf</a>(<a href="ident?i=seq">seq</a>, <i>"\tAver depth:     %u.%02d\n"</i>,
<a name="L2124" href="source/net/ipv4/fib_trie.c#L2124">2124</a>                    avdepth / 100, avdepth % 100);
<a name="L2125" href="source/net/ipv4/fib_trie.c#L2125">2125</a>         <a href="ident?i=seq_printf">seq_printf</a>(<a href="ident?i=seq">seq</a>, <i>"\tMax depth:      %u\n"</i>, <a href="ident?i=stat">stat</a>-&gt;<a href="ident?i=maxdepth">maxdepth</a>);
<a name="L2126" href="source/net/ipv4/fib_trie.c#L2126">2126</a> 
<a name="L2127" href="source/net/ipv4/fib_trie.c#L2127">2127</a>         <a href="ident?i=seq_printf">seq_printf</a>(<a href="ident?i=seq">seq</a>, <i>"\tLeaves:         %u\n"</i>, <a href="ident?i=stat">stat</a>-&gt;leaves);
<a name="L2128" href="source/net/ipv4/fib_trie.c#L2128">2128</a>         <a href="ident?i=bytes">bytes</a> = <a href="ident?i=LEAF_SIZE">LEAF_SIZE</a> * <a href="ident?i=stat">stat</a>-&gt;leaves;
<a name="L2129" href="source/net/ipv4/fib_trie.c#L2129">2129</a> 
<a name="L2130" href="source/net/ipv4/fib_trie.c#L2130">2130</a>         <a href="ident?i=seq_printf">seq_printf</a>(<a href="ident?i=seq">seq</a>, <i>"\tPrefixes:       %u\n"</i>, <a href="ident?i=stat">stat</a>-&gt;prefixes);
<a name="L2131" href="source/net/ipv4/fib_trie.c#L2131">2131</a>         <a href="ident?i=bytes">bytes</a> += sizeof(struct <a href="ident?i=fib_alias">fib_alias</a>) * <a href="ident?i=stat">stat</a>-&gt;prefixes;
<a name="L2132" href="source/net/ipv4/fib_trie.c#L2132">2132</a> 
<a name="L2133" href="source/net/ipv4/fib_trie.c#L2133">2133</a>         <a href="ident?i=seq_printf">seq_printf</a>(<a href="ident?i=seq">seq</a>, <i>"\tInternal nodes: %u\n\t"</i>, <a href="ident?i=stat">stat</a>-&gt;tnodes);
<a name="L2134" href="source/net/ipv4/fib_trie.c#L2134">2134</a>         <a href="ident?i=bytes">bytes</a> += <a href="ident?i=TNODE_SIZE">TNODE_SIZE</a>(0) * <a href="ident?i=stat">stat</a>-&gt;tnodes;
<a name="L2135" href="source/net/ipv4/fib_trie.c#L2135">2135</a> 
<a name="L2136" href="source/net/ipv4/fib_trie.c#L2136">2136</a>         <a href="ident?i=max">max</a> = <a href="ident?i=MAX_STAT_DEPTH">MAX_STAT_DEPTH</a>;
<a name="L2137" href="source/net/ipv4/fib_trie.c#L2137">2137</a>         while (<a href="ident?i=max">max</a> &gt; 0 &amp;&amp; <a href="ident?i=stat">stat</a>-&gt;nodesizes[<a href="ident?i=max">max</a>-1] == 0)
<a name="L2138" href="source/net/ipv4/fib_trie.c#L2138">2138</a>                 <a href="ident?i=max">max</a>--;
<a name="L2139" href="source/net/ipv4/fib_trie.c#L2139">2139</a> 
<a name="L2140" href="source/net/ipv4/fib_trie.c#L2140">2140</a>         pointers = 0;
<a name="L2141" href="source/net/ipv4/fib_trie.c#L2141">2141</a>         for (<a href="ident?i=i">i</a> = 1; <a href="ident?i=i">i</a> &lt; <a href="ident?i=max">max</a>; <a href="ident?i=i">i</a>++)
<a name="L2142" href="source/net/ipv4/fib_trie.c#L2142">2142</a>                 if (<a href="ident?i=stat">stat</a>-&gt;nodesizes[<a href="ident?i=i">i</a>] != 0) {
<a name="L2143" href="source/net/ipv4/fib_trie.c#L2143">2143</a>                         <a href="ident?i=seq_printf">seq_printf</a>(<a href="ident?i=seq">seq</a>, <i>"  %u: %u"</i>,  <a href="ident?i=i">i</a>, <a href="ident?i=stat">stat</a>-&gt;nodesizes[<a href="ident?i=i">i</a>]);
<a name="L2144" href="source/net/ipv4/fib_trie.c#L2144">2144</a>                         pointers += (1&lt;&lt;<a href="ident?i=i">i</a>) * <a href="ident?i=stat">stat</a>-&gt;nodesizes[<a href="ident?i=i">i</a>];
<a name="L2145" href="source/net/ipv4/fib_trie.c#L2145">2145</a>                 }
<a name="L2146" href="source/net/ipv4/fib_trie.c#L2146">2146</a>         <a href="ident?i=seq_putc">seq_putc</a>(<a href="ident?i=seq">seq</a>, <i>'\n'</i>);
<a name="L2147" href="source/net/ipv4/fib_trie.c#L2147">2147</a>         <a href="ident?i=seq_printf">seq_printf</a>(<a href="ident?i=seq">seq</a>, <i>"\tPointers: %u\n"</i>, pointers);
<a name="L2148" href="source/net/ipv4/fib_trie.c#L2148">2148</a> 
<a name="L2149" href="source/net/ipv4/fib_trie.c#L2149">2149</a>         <a href="ident?i=bytes">bytes</a> += sizeof(struct <a href="ident?i=key_vector">key_vector</a> *) * pointers;
<a name="L2150" href="source/net/ipv4/fib_trie.c#L2150">2150</a>         <a href="ident?i=seq_printf">seq_printf</a>(<a href="ident?i=seq">seq</a>, <i>"Null ptrs: %u\n"</i>, <a href="ident?i=stat">stat</a>-&gt;nullpointers);
<a name="L2151" href="source/net/ipv4/fib_trie.c#L2151">2151</a>         <a href="ident?i=seq_printf">seq_printf</a>(<a href="ident?i=seq">seq</a>, <i>"Total size: %u  kB\n"</i>, (<a href="ident?i=bytes">bytes</a> + 1023) / 1024);
<a name="L2152" href="source/net/ipv4/fib_trie.c#L2152">2152</a> }
<a name="L2153" href="source/net/ipv4/fib_trie.c#L2153">2153</a> 
<a name="L2154" href="source/net/ipv4/fib_trie.c#L2154">2154</a> #ifdef CONFIG_IP_FIB_TRIE_STATS
<a name="L2155" href="source/net/ipv4/fib_trie.c#L2155">2155</a> static void <a href="ident?i=trie_show_usage">trie_show_usage</a>(struct <a href="ident?i=seq_file">seq_file</a> *<a href="ident?i=seq">seq</a>,
<a name="L2156" href="source/net/ipv4/fib_trie.c#L2156">2156</a>                             const struct <a href="ident?i=trie_use_stats">trie_use_stats</a> <a href="ident?i=__percpu">__percpu</a> *<a href="ident?i=stats">stats</a>)
<a name="L2157" href="source/net/ipv4/fib_trie.c#L2157">2157</a> {
<a name="L2158" href="source/net/ipv4/fib_trie.c#L2158">2158</a>         struct <a href="ident?i=trie_use_stats">trie_use_stats</a> <a href="ident?i=s">s</a> = { 0 };
<a name="L2159" href="source/net/ipv4/fib_trie.c#L2159">2159</a>         int <a href="ident?i=cpu">cpu</a>;
<a name="L2160" href="source/net/ipv4/fib_trie.c#L2160">2160</a> 
<a name="L2161" href="source/net/ipv4/fib_trie.c#L2161">2161</a>         <b><i>/* loop through all of the CPUs and gather up the stats */</i></b>
<a name="L2162" href="source/net/ipv4/fib_trie.c#L2162">2162</a>         <a href="ident?i=for_each_possible_cpu">for_each_possible_cpu</a>(<a href="ident?i=cpu">cpu</a>) {
<a name="L2163" href="source/net/ipv4/fib_trie.c#L2163">2163</a>                 const struct <a href="ident?i=trie_use_stats">trie_use_stats</a> *<a href="ident?i=pcpu">pcpu</a> = <a href="ident?i=per_cpu_ptr">per_cpu_ptr</a>(<a href="ident?i=stats">stats</a>, <a href="ident?i=cpu">cpu</a>);
<a name="L2164" href="source/net/ipv4/fib_trie.c#L2164">2164</a> 
<a name="L2165" href="source/net/ipv4/fib_trie.c#L2165">2165</a>                 <a href="ident?i=s">s</a>.gets += <a href="ident?i=pcpu">pcpu</a>-&gt;gets;
<a name="L2166" href="source/net/ipv4/fib_trie.c#L2166">2166</a>                 <a href="ident?i=s">s</a>.backtrack += <a href="ident?i=pcpu">pcpu</a>-&gt;backtrack;
<a name="L2167" href="source/net/ipv4/fib_trie.c#L2167">2167</a>                 <a href="ident?i=s">s</a>.semantic_match_passed += <a href="ident?i=pcpu">pcpu</a>-&gt;semantic_match_passed;
<a name="L2168" href="source/net/ipv4/fib_trie.c#L2168">2168</a>                 <a href="ident?i=s">s</a>.semantic_match_miss += <a href="ident?i=pcpu">pcpu</a>-&gt;semantic_match_miss;
<a name="L2169" href="source/net/ipv4/fib_trie.c#L2169">2169</a>                 <a href="ident?i=s">s</a>.null_node_hit += <a href="ident?i=pcpu">pcpu</a>-&gt;null_node_hit;
<a name="L2170" href="source/net/ipv4/fib_trie.c#L2170">2170</a>                 <a href="ident?i=s">s</a>.resize_node_skipped += <a href="ident?i=pcpu">pcpu</a>-&gt;resize_node_skipped;
<a name="L2171" href="source/net/ipv4/fib_trie.c#L2171">2171</a>         }
<a name="L2172" href="source/net/ipv4/fib_trie.c#L2172">2172</a> 
<a name="L2173" href="source/net/ipv4/fib_trie.c#L2173">2173</a>         <a href="ident?i=seq_printf">seq_printf</a>(<a href="ident?i=seq">seq</a>, <i>"\nCounters:\n---------\n"</i>);
<a name="L2174" href="source/net/ipv4/fib_trie.c#L2174">2174</a>         <a href="ident?i=seq_printf">seq_printf</a>(<a href="ident?i=seq">seq</a>, <i>"gets = %u\n"</i>, <a href="ident?i=s">s</a>.gets);
<a name="L2175" href="source/net/ipv4/fib_trie.c#L2175">2175</a>         <a href="ident?i=seq_printf">seq_printf</a>(<a href="ident?i=seq">seq</a>, <i>"backtracks = %u\n"</i>, <a href="ident?i=s">s</a>.backtrack);
<a name="L2176" href="source/net/ipv4/fib_trie.c#L2176">2176</a>         <a href="ident?i=seq_printf">seq_printf</a>(<a href="ident?i=seq">seq</a>, <i>"semantic match passed = %u\n"</i>,
<a name="L2177" href="source/net/ipv4/fib_trie.c#L2177">2177</a>                    <a href="ident?i=s">s</a>.semantic_match_passed);
<a name="L2178" href="source/net/ipv4/fib_trie.c#L2178">2178</a>         <a href="ident?i=seq_printf">seq_printf</a>(<a href="ident?i=seq">seq</a>, <i>"semantic match miss = %u\n"</i>, <a href="ident?i=s">s</a>.semantic_match_miss);
<a name="L2179" href="source/net/ipv4/fib_trie.c#L2179">2179</a>         <a href="ident?i=seq_printf">seq_printf</a>(<a href="ident?i=seq">seq</a>, <i>"null node hit= %u\n"</i>, <a href="ident?i=s">s</a>.null_node_hit);
<a name="L2180" href="source/net/ipv4/fib_trie.c#L2180">2180</a>         <a href="ident?i=seq_printf">seq_printf</a>(<a href="ident?i=seq">seq</a>, <i>"skipped node resize = %u\n\n"</i>, <a href="ident?i=s">s</a>.resize_node_skipped);
<a name="L2181" href="source/net/ipv4/fib_trie.c#L2181">2181</a> }
<a name="L2182" href="source/net/ipv4/fib_trie.c#L2182">2182</a> #endif <b><i>/*  CONFIG_IP_FIB_TRIE_STATS */</i></b>
<a name="L2183" href="source/net/ipv4/fib_trie.c#L2183">2183</a> 
<a name="L2184" href="source/net/ipv4/fib_trie.c#L2184">2184</a> static void <a href="ident?i=fib_table_print">fib_table_print</a>(struct <a href="ident?i=seq_file">seq_file</a> *<a href="ident?i=seq">seq</a>, struct <a href="ident?i=fib_table">fib_table</a> *<a href="ident?i=tb">tb</a>)
<a name="L2185" href="source/net/ipv4/fib_trie.c#L2185">2185</a> {
<a name="L2186" href="source/net/ipv4/fib_trie.c#L2186">2186</a>         if (<a href="ident?i=tb">tb</a>-&gt;tb_id == RT_TABLE_LOCAL)
<a name="L2187" href="source/net/ipv4/fib_trie.c#L2187">2187</a>                 <a href="ident?i=seq_puts">seq_puts</a>(<a href="ident?i=seq">seq</a>, <i>"Local:\n"</i>);
<a name="L2188" href="source/net/ipv4/fib_trie.c#L2188">2188</a>         else if (<a href="ident?i=tb">tb</a>-&gt;tb_id == RT_TABLE_MAIN)
<a name="L2189" href="source/net/ipv4/fib_trie.c#L2189">2189</a>                 <a href="ident?i=seq_puts">seq_puts</a>(<a href="ident?i=seq">seq</a>, <i>"Main:\n"</i>);
<a name="L2190" href="source/net/ipv4/fib_trie.c#L2190">2190</a>         else
<a name="L2191" href="source/net/ipv4/fib_trie.c#L2191">2191</a>                 <a href="ident?i=seq_printf">seq_printf</a>(<a href="ident?i=seq">seq</a>, <i>"Id %d:\n"</i>, <a href="ident?i=tb">tb</a>-&gt;tb_id);
<a name="L2192" href="source/net/ipv4/fib_trie.c#L2192">2192</a> }
<a name="L2193" href="source/net/ipv4/fib_trie.c#L2193">2193</a> 
<a name="L2194" href="source/net/ipv4/fib_trie.c#L2194">2194</a> 
<a name="L2195" href="source/net/ipv4/fib_trie.c#L2195">2195</a> static int <a href="ident?i=fib_triestat_seq_show">fib_triestat_seq_show</a>(struct <a href="ident?i=seq_file">seq_file</a> *<a href="ident?i=seq">seq</a>, void *<a href="ident?i=v">v</a>)
<a name="L2196" href="source/net/ipv4/fib_trie.c#L2196">2196</a> {
<a name="L2197" href="source/net/ipv4/fib_trie.c#L2197">2197</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = (struct <a href="ident?i=net">net</a> *)<a href="ident?i=seq">seq</a>-&gt;<a href="ident?i=private">private</a>;
<a name="L2198" href="source/net/ipv4/fib_trie.c#L2198">2198</a>         unsigned int <a href="ident?i=h">h</a>;
<a name="L2199" href="source/net/ipv4/fib_trie.c#L2199">2199</a> 
<a name="L2200" href="source/net/ipv4/fib_trie.c#L2200">2200</a>         <a href="ident?i=seq_printf">seq_printf</a>(<a href="ident?i=seq">seq</a>,
<a name="L2201" href="source/net/ipv4/fib_trie.c#L2201">2201</a>                    <i>"Basic info: size of leaf:"</i>
<a name="L2202" href="source/net/ipv4/fib_trie.c#L2202">2202</a>                    <i>" %Zd bytes, size of tnode: %Zd bytes.\n"</i>,
<a name="L2203" href="source/net/ipv4/fib_trie.c#L2203">2203</a>                    <a href="ident?i=LEAF_SIZE">LEAF_SIZE</a>, <a href="ident?i=TNODE_SIZE">TNODE_SIZE</a>(0));
<a name="L2204" href="source/net/ipv4/fib_trie.c#L2204">2204</a> 
<a name="L2205" href="source/net/ipv4/fib_trie.c#L2205">2205</a>         for (<a href="ident?i=h">h</a> = 0; <a href="ident?i=h">h</a> &lt; <a href="ident?i=FIB_TABLE_HASHSZ">FIB_TABLE_HASHSZ</a>; <a href="ident?i=h">h</a>++) {
<a name="L2206" href="source/net/ipv4/fib_trie.c#L2206">2206</a>                 struct <a href="ident?i=hlist_head">hlist_head</a> *<a href="ident?i=head">head</a> = &amp;<a href="ident?i=net">net</a>-&gt;ipv4.fib_table_hash[<a href="ident?i=h">h</a>];
<a name="L2207" href="source/net/ipv4/fib_trie.c#L2207">2207</a>                 struct <a href="ident?i=fib_table">fib_table</a> *<a href="ident?i=tb">tb</a>;
<a name="L2208" href="source/net/ipv4/fib_trie.c#L2208">2208</a> 
<a name="L2209" href="source/net/ipv4/fib_trie.c#L2209">2209</a>                 <a href="ident?i=hlist_for_each_entry_rcu">hlist_for_each_entry_rcu</a>(<a href="ident?i=tb">tb</a>, <a href="ident?i=head">head</a>, tb_hlist) {
<a name="L2210" href="source/net/ipv4/fib_trie.c#L2210">2210</a>                         struct <a href="ident?i=trie">trie</a> *<a href="ident?i=t">t</a> = (struct <a href="ident?i=trie">trie</a> *) <a href="ident?i=tb">tb</a>-&gt;tb_data;
<a name="L2211" href="source/net/ipv4/fib_trie.c#L2211">2211</a>                         struct <a href="ident?i=trie_stat">trie_stat</a> <a href="ident?i=stat">stat</a>;
<a name="L2212" href="source/net/ipv4/fib_trie.c#L2212">2212</a> 
<a name="L2213" href="source/net/ipv4/fib_trie.c#L2213">2213</a>                         if (!<a href="ident?i=t">t</a>)
<a name="L2214" href="source/net/ipv4/fib_trie.c#L2214">2214</a>                                 continue;
<a name="L2215" href="source/net/ipv4/fib_trie.c#L2215">2215</a> 
<a name="L2216" href="source/net/ipv4/fib_trie.c#L2216">2216</a>                         <a href="ident?i=fib_table_print">fib_table_print</a>(<a href="ident?i=seq">seq</a>, <a href="ident?i=tb">tb</a>);
<a name="L2217" href="source/net/ipv4/fib_trie.c#L2217">2217</a> 
<a name="L2218" href="source/net/ipv4/fib_trie.c#L2218">2218</a>                         <a href="ident?i=trie_collect_stats">trie_collect_stats</a>(<a href="ident?i=t">t</a>, &amp;<a href="ident?i=stat">stat</a>);
<a name="L2219" href="source/net/ipv4/fib_trie.c#L2219">2219</a>                         <a href="ident?i=trie_show_stats">trie_show_stats</a>(<a href="ident?i=seq">seq</a>, &amp;<a href="ident?i=stat">stat</a>);
<a name="L2220" href="source/net/ipv4/fib_trie.c#L2220">2220</a> #ifdef CONFIG_IP_FIB_TRIE_STATS
<a name="L2221" href="source/net/ipv4/fib_trie.c#L2221">2221</a>                         <a href="ident?i=trie_show_usage">trie_show_usage</a>(<a href="ident?i=seq">seq</a>, <a href="ident?i=t">t</a>-&gt;<a href="ident?i=stats">stats</a>);
<a name="L2222" href="source/net/ipv4/fib_trie.c#L2222">2222</a> #endif
<a name="L2223" href="source/net/ipv4/fib_trie.c#L2223">2223</a>                 }
<a name="L2224" href="source/net/ipv4/fib_trie.c#L2224">2224</a>         }
<a name="L2225" href="source/net/ipv4/fib_trie.c#L2225">2225</a> 
<a name="L2226" href="source/net/ipv4/fib_trie.c#L2226">2226</a>         return 0;
<a name="L2227" href="source/net/ipv4/fib_trie.c#L2227">2227</a> }
<a name="L2228" href="source/net/ipv4/fib_trie.c#L2228">2228</a> 
<a name="L2229" href="source/net/ipv4/fib_trie.c#L2229">2229</a> static int <a href="ident?i=fib_triestat_seq_open">fib_triestat_seq_open</a>(struct <a href="ident?i=inode">inode</a> *<a href="ident?i=inode">inode</a>, struct <a href="ident?i=file">file</a> *<a href="ident?i=file">file</a>)
<a name="L2230" href="source/net/ipv4/fib_trie.c#L2230">2230</a> {
<a name="L2231" href="source/net/ipv4/fib_trie.c#L2231">2231</a>         return <a href="ident?i=single_open_net">single_open_net</a>(<a href="ident?i=inode">inode</a>, <a href="ident?i=file">file</a>, <a href="ident?i=fib_triestat_seq_show">fib_triestat_seq_show</a>);
<a name="L2232" href="source/net/ipv4/fib_trie.c#L2232">2232</a> }
<a name="L2233" href="source/net/ipv4/fib_trie.c#L2233">2233</a> 
<a name="L2234" href="source/net/ipv4/fib_trie.c#L2234">2234</a> static const struct <a href="ident?i=file_operations">file_operations</a> <a href="ident?i=fib_triestat_fops">fib_triestat_fops</a> = {
<a name="L2235" href="source/net/ipv4/fib_trie.c#L2235">2235</a>         .owner  = <a href="ident?i=THIS_MODULE">THIS_MODULE</a>,
<a name="L2236" href="source/net/ipv4/fib_trie.c#L2236">2236</a>         .<a href="ident?i=open">open</a>   = <a href="ident?i=fib_triestat_seq_open">fib_triestat_seq_open</a>,
<a name="L2237" href="source/net/ipv4/fib_trie.c#L2237">2237</a>         .<a href="ident?i=read">read</a>   = <a href="ident?i=seq_read">seq_read</a>,
<a name="L2238" href="source/net/ipv4/fib_trie.c#L2238">2238</a>         .llseek = <a href="ident?i=seq_lseek">seq_lseek</a>,
<a name="L2239" href="source/net/ipv4/fib_trie.c#L2239">2239</a>         .<a href="ident?i=release">release</a> = <a href="ident?i=single_release_net">single_release_net</a>,
<a name="L2240" href="source/net/ipv4/fib_trie.c#L2240">2240</a> };
<a name="L2241" href="source/net/ipv4/fib_trie.c#L2241">2241</a> 
<a name="L2242" href="source/net/ipv4/fib_trie.c#L2242">2242</a> static struct <a href="ident?i=key_vector">key_vector</a> *<a href="ident?i=fib_trie_get_idx">fib_trie_get_idx</a>(struct <a href="ident?i=seq_file">seq_file</a> *<a href="ident?i=seq">seq</a>, <a href="ident?i=loff_t">loff_t</a> <a href="ident?i=pos">pos</a>)
<a name="L2243" href="source/net/ipv4/fib_trie.c#L2243">2243</a> {
<a name="L2244" href="source/net/ipv4/fib_trie.c#L2244">2244</a>         struct <a href="ident?i=fib_trie_iter">fib_trie_iter</a> *iter = <a href="ident?i=seq">seq</a>-&gt;<a href="ident?i=private">private</a>;
<a name="L2245" href="source/net/ipv4/fib_trie.c#L2245">2245</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=seq_file_net">seq_file_net</a>(<a href="ident?i=seq">seq</a>);
<a name="L2246" href="source/net/ipv4/fib_trie.c#L2246">2246</a>         <a href="ident?i=loff_t">loff_t</a> <a href="ident?i=idx">idx</a> = 0;
<a name="L2247" href="source/net/ipv4/fib_trie.c#L2247">2247</a>         unsigned int <a href="ident?i=h">h</a>;
<a name="L2248" href="source/net/ipv4/fib_trie.c#L2248">2248</a> 
<a name="L2249" href="source/net/ipv4/fib_trie.c#L2249">2249</a>         for (<a href="ident?i=h">h</a> = 0; <a href="ident?i=h">h</a> &lt; <a href="ident?i=FIB_TABLE_HASHSZ">FIB_TABLE_HASHSZ</a>; <a href="ident?i=h">h</a>++) {
<a name="L2250" href="source/net/ipv4/fib_trie.c#L2250">2250</a>                 struct <a href="ident?i=hlist_head">hlist_head</a> *<a href="ident?i=head">head</a> = &amp;<a href="ident?i=net">net</a>-&gt;ipv4.fib_table_hash[<a href="ident?i=h">h</a>];
<a name="L2251" href="source/net/ipv4/fib_trie.c#L2251">2251</a>                 struct <a href="ident?i=fib_table">fib_table</a> *<a href="ident?i=tb">tb</a>;
<a name="L2252" href="source/net/ipv4/fib_trie.c#L2252">2252</a> 
<a name="L2253" href="source/net/ipv4/fib_trie.c#L2253">2253</a>                 <a href="ident?i=hlist_for_each_entry_rcu">hlist_for_each_entry_rcu</a>(<a href="ident?i=tb">tb</a>, <a href="ident?i=head">head</a>, tb_hlist) {
<a name="L2254" href="source/net/ipv4/fib_trie.c#L2254">2254</a>                         struct <a href="ident?i=key_vector">key_vector</a> *<a href="ident?i=n">n</a>;
<a name="L2255" href="source/net/ipv4/fib_trie.c#L2255">2255</a> 
<a name="L2256" href="source/net/ipv4/fib_trie.c#L2256">2256</a>                         for (<a href="ident?i=n">n</a> = <a href="ident?i=fib_trie_get_first">fib_trie_get_first</a>(iter,
<a name="L2257" href="source/net/ipv4/fib_trie.c#L2257">2257</a>                                                     (struct <a href="ident?i=trie">trie</a> *) <a href="ident?i=tb">tb</a>-&gt;tb_data);
<a name="L2258" href="source/net/ipv4/fib_trie.c#L2258">2258</a>                              <a href="ident?i=n">n</a>; <a href="ident?i=n">n</a> = <a href="ident?i=fib_trie_get_next">fib_trie_get_next</a>(iter))
<a name="L2259" href="source/net/ipv4/fib_trie.c#L2259">2259</a>                                 if (<a href="ident?i=pos">pos</a> == <a href="ident?i=idx">idx</a>++) {
<a name="L2260" href="source/net/ipv4/fib_trie.c#L2260">2260</a>                                         iter-&gt;<a href="ident?i=tb">tb</a> = <a href="ident?i=tb">tb</a>;
<a name="L2261" href="source/net/ipv4/fib_trie.c#L2261">2261</a>                                         return <a href="ident?i=n">n</a>;
<a name="L2262" href="source/net/ipv4/fib_trie.c#L2262">2262</a>                                 }
<a name="L2263" href="source/net/ipv4/fib_trie.c#L2263">2263</a>                 }
<a name="L2264" href="source/net/ipv4/fib_trie.c#L2264">2264</a>         }
<a name="L2265" href="source/net/ipv4/fib_trie.c#L2265">2265</a> 
<a name="L2266" href="source/net/ipv4/fib_trie.c#L2266">2266</a>         return <a href="ident?i=NULL">NULL</a>;
<a name="L2267" href="source/net/ipv4/fib_trie.c#L2267">2267</a> }
<a name="L2268" href="source/net/ipv4/fib_trie.c#L2268">2268</a> 
<a name="L2269" href="source/net/ipv4/fib_trie.c#L2269">2269</a> static void *fib_trie_seq_start(struct <a href="ident?i=seq_file">seq_file</a> *<a href="ident?i=seq">seq</a>, <a href="ident?i=loff_t">loff_t</a> *<a href="ident?i=pos">pos</a>)
<a name="L2270" href="source/net/ipv4/fib_trie.c#L2270">2270</a>         <a href="ident?i=__acquires">__acquires</a>(RCU)
<a name="L2271" href="source/net/ipv4/fib_trie.c#L2271">2271</a> {
<a name="L2272" href="source/net/ipv4/fib_trie.c#L2272">2272</a>         <a href="ident?i=rcu_read_lock">rcu_read_lock</a>();
<a name="L2273" href="source/net/ipv4/fib_trie.c#L2273">2273</a>         return <a href="ident?i=fib_trie_get_idx">fib_trie_get_idx</a>(<a href="ident?i=seq">seq</a>, *<a href="ident?i=pos">pos</a>);
<a name="L2274" href="source/net/ipv4/fib_trie.c#L2274">2274</a> }
<a name="L2275" href="source/net/ipv4/fib_trie.c#L2275">2275</a> 
<a name="L2276" href="source/net/ipv4/fib_trie.c#L2276">2276</a> static void *<a href="ident?i=fib_trie_seq_next">fib_trie_seq_next</a>(struct <a href="ident?i=seq_file">seq_file</a> *<a href="ident?i=seq">seq</a>, void *<a href="ident?i=v">v</a>, <a href="ident?i=loff_t">loff_t</a> *<a href="ident?i=pos">pos</a>)
<a name="L2277" href="source/net/ipv4/fib_trie.c#L2277">2277</a> {
<a name="L2278" href="source/net/ipv4/fib_trie.c#L2278">2278</a>         struct <a href="ident?i=fib_trie_iter">fib_trie_iter</a> *iter = <a href="ident?i=seq">seq</a>-&gt;<a href="ident?i=private">private</a>;
<a name="L2279" href="source/net/ipv4/fib_trie.c#L2279">2279</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=seq_file_net">seq_file_net</a>(<a href="ident?i=seq">seq</a>);
<a name="L2280" href="source/net/ipv4/fib_trie.c#L2280">2280</a>         struct <a href="ident?i=fib_table">fib_table</a> *<a href="ident?i=tb">tb</a> = iter-&gt;<a href="ident?i=tb">tb</a>;
<a name="L2281" href="source/net/ipv4/fib_trie.c#L2281">2281</a>         struct <a href="ident?i=hlist_node">hlist_node</a> *tb_node;
<a name="L2282" href="source/net/ipv4/fib_trie.c#L2282">2282</a>         unsigned int <a href="ident?i=h">h</a>;
<a name="L2283" href="source/net/ipv4/fib_trie.c#L2283">2283</a>         struct <a href="ident?i=key_vector">key_vector</a> *<a href="ident?i=n">n</a>;
<a name="L2284" href="source/net/ipv4/fib_trie.c#L2284">2284</a> 
<a name="L2285" href="source/net/ipv4/fib_trie.c#L2285">2285</a>         ++*<a href="ident?i=pos">pos</a>;
<a name="L2286" href="source/net/ipv4/fib_trie.c#L2286">2286</a>         <b><i>/* next node in same table */</i></b>
<a name="L2287" href="source/net/ipv4/fib_trie.c#L2287">2287</a>         <a href="ident?i=n">n</a> = <a href="ident?i=fib_trie_get_next">fib_trie_get_next</a>(iter);
<a name="L2288" href="source/net/ipv4/fib_trie.c#L2288">2288</a>         if (<a href="ident?i=n">n</a>)
<a name="L2289" href="source/net/ipv4/fib_trie.c#L2289">2289</a>                 return <a href="ident?i=n">n</a>;
<a name="L2290" href="source/net/ipv4/fib_trie.c#L2290">2290</a> 
<a name="L2291" href="source/net/ipv4/fib_trie.c#L2291">2291</a>         <b><i>/* walk rest of this hash chain */</i></b>
<a name="L2292" href="source/net/ipv4/fib_trie.c#L2292">2292</a>         <a href="ident?i=h">h</a> = <a href="ident?i=tb">tb</a>-&gt;tb_id &amp; (<a href="ident?i=FIB_TABLE_HASHSZ">FIB_TABLE_HASHSZ</a> - 1);
<a name="L2293" href="source/net/ipv4/fib_trie.c#L2293">2293</a>         while ((tb_node = <a href="ident?i=rcu_dereference">rcu_dereference</a>(<a href="ident?i=hlist_next_rcu">hlist_next_rcu</a>(&amp;<a href="ident?i=tb">tb</a>-&gt;tb_hlist)))) {
<a name="L2294" href="source/net/ipv4/fib_trie.c#L2294">2294</a>                 <a href="ident?i=tb">tb</a> = <a href="ident?i=hlist_entry">hlist_entry</a>(tb_node, struct <a href="ident?i=fib_table">fib_table</a>, tb_hlist);
<a name="L2295" href="source/net/ipv4/fib_trie.c#L2295">2295</a>                 <a href="ident?i=n">n</a> = <a href="ident?i=fib_trie_get_first">fib_trie_get_first</a>(iter, (struct <a href="ident?i=trie">trie</a> *) <a href="ident?i=tb">tb</a>-&gt;tb_data);
<a name="L2296" href="source/net/ipv4/fib_trie.c#L2296">2296</a>                 if (<a href="ident?i=n">n</a>)
<a name="L2297" href="source/net/ipv4/fib_trie.c#L2297">2297</a>                         goto <a href="ident?i=found">found</a>;
<a name="L2298" href="source/net/ipv4/fib_trie.c#L2298">2298</a>         }
<a name="L2299" href="source/net/ipv4/fib_trie.c#L2299">2299</a> 
<a name="L2300" href="source/net/ipv4/fib_trie.c#L2300">2300</a>         <b><i>/* new hash chain */</i></b>
<a name="L2301" href="source/net/ipv4/fib_trie.c#L2301">2301</a>         while (++<a href="ident?i=h">h</a> &lt; <a href="ident?i=FIB_TABLE_HASHSZ">FIB_TABLE_HASHSZ</a>) {
<a name="L2302" href="source/net/ipv4/fib_trie.c#L2302">2302</a>                 struct <a href="ident?i=hlist_head">hlist_head</a> *<a href="ident?i=head">head</a> = &amp;<a href="ident?i=net">net</a>-&gt;ipv4.fib_table_hash[<a href="ident?i=h">h</a>];
<a name="L2303" href="source/net/ipv4/fib_trie.c#L2303">2303</a>                 <a href="ident?i=hlist_for_each_entry_rcu">hlist_for_each_entry_rcu</a>(<a href="ident?i=tb">tb</a>, <a href="ident?i=head">head</a>, tb_hlist) {
<a name="L2304" href="source/net/ipv4/fib_trie.c#L2304">2304</a>                         <a href="ident?i=n">n</a> = <a href="ident?i=fib_trie_get_first">fib_trie_get_first</a>(iter, (struct <a href="ident?i=trie">trie</a> *) <a href="ident?i=tb">tb</a>-&gt;tb_data);
<a name="L2305" href="source/net/ipv4/fib_trie.c#L2305">2305</a>                         if (<a href="ident?i=n">n</a>)
<a name="L2306" href="source/net/ipv4/fib_trie.c#L2306">2306</a>                                 goto <a href="ident?i=found">found</a>;
<a name="L2307" href="source/net/ipv4/fib_trie.c#L2307">2307</a>                 }
<a name="L2308" href="source/net/ipv4/fib_trie.c#L2308">2308</a>         }
<a name="L2309" href="source/net/ipv4/fib_trie.c#L2309">2309</a>         return <a href="ident?i=NULL">NULL</a>;
<a name="L2310" href="source/net/ipv4/fib_trie.c#L2310">2310</a> 
<a name="L2311" href="source/net/ipv4/fib_trie.c#L2311">2311</a> <a href="ident?i=found">found</a>:
<a name="L2312" href="source/net/ipv4/fib_trie.c#L2312">2312</a>         iter-&gt;<a href="ident?i=tb">tb</a> = <a href="ident?i=tb">tb</a>;
<a name="L2313" href="source/net/ipv4/fib_trie.c#L2313">2313</a>         return <a href="ident?i=n">n</a>;
<a name="L2314" href="source/net/ipv4/fib_trie.c#L2314">2314</a> }
<a name="L2315" href="source/net/ipv4/fib_trie.c#L2315">2315</a> 
<a name="L2316" href="source/net/ipv4/fib_trie.c#L2316">2316</a> static void fib_trie_seq_stop(struct <a href="ident?i=seq_file">seq_file</a> *<a href="ident?i=seq">seq</a>, void *<a href="ident?i=v">v</a>)
<a name="L2317" href="source/net/ipv4/fib_trie.c#L2317">2317</a>         <a href="ident?i=__releases">__releases</a>(RCU)
<a name="L2318" href="source/net/ipv4/fib_trie.c#L2318">2318</a> {
<a name="L2319" href="source/net/ipv4/fib_trie.c#L2319">2319</a>         <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L2320" href="source/net/ipv4/fib_trie.c#L2320">2320</a> }
<a name="L2321" href="source/net/ipv4/fib_trie.c#L2321">2321</a> 
<a name="L2322" href="source/net/ipv4/fib_trie.c#L2322">2322</a> static void <a href="ident?i=seq_indent">seq_indent</a>(struct <a href="ident?i=seq_file">seq_file</a> *<a href="ident?i=seq">seq</a>, int <a href="ident?i=n">n</a>)
<a name="L2323" href="source/net/ipv4/fib_trie.c#L2323">2323</a> {
<a name="L2324" href="source/net/ipv4/fib_trie.c#L2324">2324</a>         while (<a href="ident?i=n">n</a>-- &gt; 0)
<a name="L2325" href="source/net/ipv4/fib_trie.c#L2325">2325</a>                 <a href="ident?i=seq_puts">seq_puts</a>(<a href="ident?i=seq">seq</a>, <i>"   "</i>);
<a name="L2326" href="source/net/ipv4/fib_trie.c#L2326">2326</a> }
<a name="L2327" href="source/net/ipv4/fib_trie.c#L2327">2327</a> 
<a name="L2328" href="source/net/ipv4/fib_trie.c#L2328">2328</a> static inline const char *<a href="ident?i=rtn_scope">rtn_scope</a>(char *<a href="ident?i=buf">buf</a>, <a href="ident?i=size_t">size_t</a> <a href="ident?i=len">len</a>, enum <a href="ident?i=rt_scope_t">rt_scope_t</a> <a href="ident?i=s">s</a>)
<a name="L2329" href="source/net/ipv4/fib_trie.c#L2329">2329</a> {
<a name="L2330" href="source/net/ipv4/fib_trie.c#L2330">2330</a>         switch (<a href="ident?i=s">s</a>) {
<a name="L2331" href="source/net/ipv4/fib_trie.c#L2331">2331</a>         case RT_SCOPE_UNIVERSE: return <i>"universe"</i>;
<a name="L2332" href="source/net/ipv4/fib_trie.c#L2332">2332</a>         case RT_SCOPE_SITE:     return <i>"site"</i>;
<a name="L2333" href="source/net/ipv4/fib_trie.c#L2333">2333</a>         case RT_SCOPE_LINK:     return <i>"link"</i>;
<a name="L2334" href="source/net/ipv4/fib_trie.c#L2334">2334</a>         case RT_SCOPE_HOST:     return <i>"host"</i>;
<a name="L2335" href="source/net/ipv4/fib_trie.c#L2335">2335</a>         case RT_SCOPE_NOWHERE:  return <i>"nowhere"</i>;
<a name="L2336" href="source/net/ipv4/fib_trie.c#L2336">2336</a>         default:
<a name="L2337" href="source/net/ipv4/fib_trie.c#L2337">2337</a>                 <a href="ident?i=snprintf">snprintf</a>(<a href="ident?i=buf">buf</a>, <a href="ident?i=len">len</a>, <i>"scope=%d"</i>, <a href="ident?i=s">s</a>);
<a name="L2338" href="source/net/ipv4/fib_trie.c#L2338">2338</a>                 return <a href="ident?i=buf">buf</a>;
<a name="L2339" href="source/net/ipv4/fib_trie.c#L2339">2339</a>         }
<a name="L2340" href="source/net/ipv4/fib_trie.c#L2340">2340</a> }
<a name="L2341" href="source/net/ipv4/fib_trie.c#L2341">2341</a> 
<a name="L2342" href="source/net/ipv4/fib_trie.c#L2342">2342</a> static const char *const <a href="ident?i=rtn_type_names">rtn_type_names</a>[__RTN_MAX] = {
<a name="L2343" href="source/net/ipv4/fib_trie.c#L2343">2343</a>         [RTN_UNSPEC] = <i>"UNSPEC"</i>,
<a name="L2344" href="source/net/ipv4/fib_trie.c#L2344">2344</a>         [RTN_UNICAST] = <i>"UNICAST"</i>,
<a name="L2345" href="source/net/ipv4/fib_trie.c#L2345">2345</a>         [RTN_LOCAL] = <i>"LOCAL"</i>,
<a name="L2346" href="source/net/ipv4/fib_trie.c#L2346">2346</a>         [RTN_BROADCAST] = <i>"BROADCAST"</i>,
<a name="L2347" href="source/net/ipv4/fib_trie.c#L2347">2347</a>         [RTN_ANYCAST] = <i>"ANYCAST"</i>,
<a name="L2348" href="source/net/ipv4/fib_trie.c#L2348">2348</a>         [RTN_MULTICAST] = <i>"MULTICAST"</i>,
<a name="L2349" href="source/net/ipv4/fib_trie.c#L2349">2349</a>         [RTN_BLACKHOLE] = <i>"BLACKHOLE"</i>,
<a name="L2350" href="source/net/ipv4/fib_trie.c#L2350">2350</a>         [RTN_UNREACHABLE] = <i>"UNREACHABLE"</i>,
<a name="L2351" href="source/net/ipv4/fib_trie.c#L2351">2351</a>         [RTN_PROHIBIT] = <i>"PROHIBIT"</i>,
<a name="L2352" href="source/net/ipv4/fib_trie.c#L2352">2352</a>         [RTN_THROW] = <i>"THROW"</i>,
<a name="L2353" href="source/net/ipv4/fib_trie.c#L2353">2353</a>         [RTN_NAT] = <i>"NAT"</i>,
<a name="L2354" href="source/net/ipv4/fib_trie.c#L2354">2354</a>         [RTN_XRESOLVE] = <i>"XRESOLVE"</i>,
<a name="L2355" href="source/net/ipv4/fib_trie.c#L2355">2355</a> };
<a name="L2356" href="source/net/ipv4/fib_trie.c#L2356">2356</a> 
<a name="L2357" href="source/net/ipv4/fib_trie.c#L2357">2357</a> static inline const char *<a href="ident?i=rtn_type">rtn_type</a>(char *<a href="ident?i=buf">buf</a>, <a href="ident?i=size_t">size_t</a> <a href="ident?i=len">len</a>, unsigned int <a href="ident?i=t">t</a>)
<a name="L2358" href="source/net/ipv4/fib_trie.c#L2358">2358</a> {
<a name="L2359" href="source/net/ipv4/fib_trie.c#L2359">2359</a>         if (<a href="ident?i=t">t</a> &lt; __RTN_MAX &amp;&amp; <a href="ident?i=rtn_type_names">rtn_type_names</a>[<a href="ident?i=t">t</a>])
<a name="L2360" href="source/net/ipv4/fib_trie.c#L2360">2360</a>                 return <a href="ident?i=rtn_type_names">rtn_type_names</a>[<a href="ident?i=t">t</a>];
<a name="L2361" href="source/net/ipv4/fib_trie.c#L2361">2361</a>         <a href="ident?i=snprintf">snprintf</a>(<a href="ident?i=buf">buf</a>, <a href="ident?i=len">len</a>, <i>"type %u"</i>, <a href="ident?i=t">t</a>);
<a name="L2362" href="source/net/ipv4/fib_trie.c#L2362">2362</a>         return <a href="ident?i=buf">buf</a>;
<a name="L2363" href="source/net/ipv4/fib_trie.c#L2363">2363</a> }
<a name="L2364" href="source/net/ipv4/fib_trie.c#L2364">2364</a> 
<a name="L2365" href="source/net/ipv4/fib_trie.c#L2365">2365</a> <b><i>/* Pretty print the trie */</i></b>
<a name="L2366" href="source/net/ipv4/fib_trie.c#L2366">2366</a> static int <a href="ident?i=fib_trie_seq_show">fib_trie_seq_show</a>(struct <a href="ident?i=seq_file">seq_file</a> *<a href="ident?i=seq">seq</a>, void *<a href="ident?i=v">v</a>)
<a name="L2367" href="source/net/ipv4/fib_trie.c#L2367">2367</a> {
<a name="L2368" href="source/net/ipv4/fib_trie.c#L2368">2368</a>         const struct <a href="ident?i=fib_trie_iter">fib_trie_iter</a> *iter = <a href="ident?i=seq">seq</a>-&gt;<a href="ident?i=private">private</a>;
<a name="L2369" href="source/net/ipv4/fib_trie.c#L2369">2369</a>         struct <a href="ident?i=key_vector">key_vector</a> *<a href="ident?i=n">n</a> = <a href="ident?i=v">v</a>;
<a name="L2370" href="source/net/ipv4/fib_trie.c#L2370">2370</a> 
<a name="L2371" href="source/net/ipv4/fib_trie.c#L2371">2371</a>         if (<a href="ident?i=IS_TRIE">IS_TRIE</a>(<a href="ident?i=node_parent_rcu">node_parent_rcu</a>(<a href="ident?i=n">n</a>)))
<a name="L2372" href="source/net/ipv4/fib_trie.c#L2372">2372</a>                 <a href="ident?i=fib_table_print">fib_table_print</a>(<a href="ident?i=seq">seq</a>, iter-&gt;<a href="ident?i=tb">tb</a>);
<a name="L2373" href="source/net/ipv4/fib_trie.c#L2373">2373</a> 
<a name="L2374" href="source/net/ipv4/fib_trie.c#L2374">2374</a>         if (<a href="ident?i=IS_TNODE">IS_TNODE</a>(<a href="ident?i=n">n</a>)) {
<a name="L2375" href="source/net/ipv4/fib_trie.c#L2375">2375</a>                 <a href="ident?i=__be32">__be32</a> prf = <a href="ident?i=htonl">htonl</a>(<a href="ident?i=n">n</a>-&gt;<a href="ident?i=key">key</a>);
<a name="L2376" href="source/net/ipv4/fib_trie.c#L2376">2376</a> 
<a name="L2377" href="source/net/ipv4/fib_trie.c#L2377">2377</a>                 <a href="ident?i=seq_indent">seq_indent</a>(<a href="ident?i=seq">seq</a>, iter-&gt;<a href="ident?i=depth">depth</a>-1);
<a name="L2378" href="source/net/ipv4/fib_trie.c#L2378">2378</a>                 <a href="ident?i=seq_printf">seq_printf</a>(<a href="ident?i=seq">seq</a>, <i>"  +-- %pI4/%zu %u %u %u\n"</i>,
<a name="L2379" href="source/net/ipv4/fib_trie.c#L2379">2379</a>                            &amp;prf, <a href="ident?i=KEYLENGTH">KEYLENGTH</a> - <a href="ident?i=n">n</a>-&gt;<a href="ident?i=pos">pos</a> - <a href="ident?i=n">n</a>-&gt;<a href="ident?i=bits">bits</a>, <a href="ident?i=n">n</a>-&gt;<a href="ident?i=bits">bits</a>,
<a name="L2380" href="source/net/ipv4/fib_trie.c#L2380">2380</a>                            <a href="ident?i=tn_info">tn_info</a>(<a href="ident?i=n">n</a>)-&gt;full_children,
<a name="L2381" href="source/net/ipv4/fib_trie.c#L2381">2381</a>                            <a href="ident?i=tn_info">tn_info</a>(<a href="ident?i=n">n</a>)-&gt;empty_children);
<a name="L2382" href="source/net/ipv4/fib_trie.c#L2382">2382</a>         } else {
<a name="L2383" href="source/net/ipv4/fib_trie.c#L2383">2383</a>                 <a href="ident?i=__be32">__be32</a> <a href="ident?i=val">val</a> = <a href="ident?i=htonl">htonl</a>(<a href="ident?i=n">n</a>-&gt;<a href="ident?i=key">key</a>);
<a name="L2384" href="source/net/ipv4/fib_trie.c#L2384">2384</a>                 struct <a href="ident?i=fib_alias">fib_alias</a> *fa;
<a name="L2385" href="source/net/ipv4/fib_trie.c#L2385">2385</a> 
<a name="L2386" href="source/net/ipv4/fib_trie.c#L2386">2386</a>                 <a href="ident?i=seq_indent">seq_indent</a>(<a href="ident?i=seq">seq</a>, iter-&gt;<a href="ident?i=depth">depth</a>);
<a name="L2387" href="source/net/ipv4/fib_trie.c#L2387">2387</a>                 <a href="ident?i=seq_printf">seq_printf</a>(<a href="ident?i=seq">seq</a>, <i>"  |-- %pI4\n"</i>, &amp;<a href="ident?i=val">val</a>);
<a name="L2388" href="source/net/ipv4/fib_trie.c#L2388">2388</a> 
<a name="L2389" href="source/net/ipv4/fib_trie.c#L2389">2389</a>                 <a href="ident?i=hlist_for_each_entry_rcu">hlist_for_each_entry_rcu</a>(fa, &amp;<a href="ident?i=n">n</a>-&gt;leaf, fa_list) {
<a name="L2390" href="source/net/ipv4/fib_trie.c#L2390">2390</a>                         char <a href="ident?i=buf1">buf1</a>[32], <a href="ident?i=buf2">buf2</a>[32];
<a name="L2391" href="source/net/ipv4/fib_trie.c#L2391">2391</a> 
<a name="L2392" href="source/net/ipv4/fib_trie.c#L2392">2392</a>                         <a href="ident?i=seq_indent">seq_indent</a>(<a href="ident?i=seq">seq</a>, iter-&gt;<a href="ident?i=depth">depth</a> + 1);
<a name="L2393" href="source/net/ipv4/fib_trie.c#L2393">2393</a>                         <a href="ident?i=seq_printf">seq_printf</a>(<a href="ident?i=seq">seq</a>, <i>"  /%zu %s %s"</i>,
<a name="L2394" href="source/net/ipv4/fib_trie.c#L2394">2394</a>                                    <a href="ident?i=KEYLENGTH">KEYLENGTH</a> - fa-&gt;fa_slen,
<a name="L2395" href="source/net/ipv4/fib_trie.c#L2395">2395</a>                                    <a href="ident?i=rtn_scope">rtn_scope</a>(<a href="ident?i=buf1">buf1</a>, sizeof(<a href="ident?i=buf1">buf1</a>),
<a name="L2396" href="source/net/ipv4/fib_trie.c#L2396">2396</a>                                              fa-&gt;fa_info-&gt;fib_scope),
<a name="L2397" href="source/net/ipv4/fib_trie.c#L2397">2397</a>                                    <a href="ident?i=rtn_type">rtn_type</a>(<a href="ident?i=buf2">buf2</a>, sizeof(<a href="ident?i=buf2">buf2</a>),
<a name="L2398" href="source/net/ipv4/fib_trie.c#L2398">2398</a>                                             fa-&gt;fa_type));
<a name="L2399" href="source/net/ipv4/fib_trie.c#L2399">2399</a>                         if (fa-&gt;fa_tos)
<a name="L2400" href="source/net/ipv4/fib_trie.c#L2400">2400</a>                                 <a href="ident?i=seq_printf">seq_printf</a>(<a href="ident?i=seq">seq</a>, <i>" tos=%d"</i>, fa-&gt;fa_tos);
<a name="L2401" href="source/net/ipv4/fib_trie.c#L2401">2401</a>                         <a href="ident?i=seq_putc">seq_putc</a>(<a href="ident?i=seq">seq</a>, <i>'\n'</i>);
<a name="L2402" href="source/net/ipv4/fib_trie.c#L2402">2402</a>                 }
<a name="L2403" href="source/net/ipv4/fib_trie.c#L2403">2403</a>         }
<a name="L2404" href="source/net/ipv4/fib_trie.c#L2404">2404</a> 
<a name="L2405" href="source/net/ipv4/fib_trie.c#L2405">2405</a>         return 0;
<a name="L2406" href="source/net/ipv4/fib_trie.c#L2406">2406</a> }
<a name="L2407" href="source/net/ipv4/fib_trie.c#L2407">2407</a> 
<a name="L2408" href="source/net/ipv4/fib_trie.c#L2408">2408</a> static const struct <a href="ident?i=seq_operations">seq_operations</a> <a href="ident?i=fib_trie_seq_ops">fib_trie_seq_ops</a> = {
<a name="L2409" href="source/net/ipv4/fib_trie.c#L2409">2409</a>         .<a href="ident?i=start">start</a>  = fib_trie_seq_start,
<a name="L2410" href="source/net/ipv4/fib_trie.c#L2410">2410</a>         .<a href="ident?i=next">next</a>   = <a href="ident?i=fib_trie_seq_next">fib_trie_seq_next</a>,
<a name="L2411" href="source/net/ipv4/fib_trie.c#L2411">2411</a>         .<a href="ident?i=stop">stop</a>   = fib_trie_seq_stop,
<a name="L2412" href="source/net/ipv4/fib_trie.c#L2412">2412</a>         .<a href="ident?i=show">show</a>   = <a href="ident?i=fib_trie_seq_show">fib_trie_seq_show</a>,
<a name="L2413" href="source/net/ipv4/fib_trie.c#L2413">2413</a> };
<a name="L2414" href="source/net/ipv4/fib_trie.c#L2414">2414</a> 
<a name="L2415" href="source/net/ipv4/fib_trie.c#L2415">2415</a> static int <a href="ident?i=fib_trie_seq_open">fib_trie_seq_open</a>(struct <a href="ident?i=inode">inode</a> *<a href="ident?i=inode">inode</a>, struct <a href="ident?i=file">file</a> *<a href="ident?i=file">file</a>)
<a name="L2416" href="source/net/ipv4/fib_trie.c#L2416">2416</a> {
<a name="L2417" href="source/net/ipv4/fib_trie.c#L2417">2417</a>         return <a href="ident?i=seq_open_net">seq_open_net</a>(<a href="ident?i=inode">inode</a>, <a href="ident?i=file">file</a>, &amp;<a href="ident?i=fib_trie_seq_ops">fib_trie_seq_ops</a>,
<a name="L2418" href="source/net/ipv4/fib_trie.c#L2418">2418</a>                             sizeof(struct <a href="ident?i=fib_trie_iter">fib_trie_iter</a>));
<a name="L2419" href="source/net/ipv4/fib_trie.c#L2419">2419</a> }
<a name="L2420" href="source/net/ipv4/fib_trie.c#L2420">2420</a> 
<a name="L2421" href="source/net/ipv4/fib_trie.c#L2421">2421</a> static const struct <a href="ident?i=file_operations">file_operations</a> <a href="ident?i=fib_trie_fops">fib_trie_fops</a> = {
<a name="L2422" href="source/net/ipv4/fib_trie.c#L2422">2422</a>         .owner  = <a href="ident?i=THIS_MODULE">THIS_MODULE</a>,
<a name="L2423" href="source/net/ipv4/fib_trie.c#L2423">2423</a>         .<a href="ident?i=open">open</a>   = <a href="ident?i=fib_trie_seq_open">fib_trie_seq_open</a>,
<a name="L2424" href="source/net/ipv4/fib_trie.c#L2424">2424</a>         .<a href="ident?i=read">read</a>   = <a href="ident?i=seq_read">seq_read</a>,
<a name="L2425" href="source/net/ipv4/fib_trie.c#L2425">2425</a>         .llseek = <a href="ident?i=seq_lseek">seq_lseek</a>,
<a name="L2426" href="source/net/ipv4/fib_trie.c#L2426">2426</a>         .<a href="ident?i=release">release</a> = <a href="ident?i=seq_release_net">seq_release_net</a>,
<a name="L2427" href="source/net/ipv4/fib_trie.c#L2427">2427</a> };
<a name="L2428" href="source/net/ipv4/fib_trie.c#L2428">2428</a> 
<a name="L2429" href="source/net/ipv4/fib_trie.c#L2429">2429</a> struct <a href="ident?i=fib_route_iter">fib_route_iter</a> {
<a name="L2430" href="source/net/ipv4/fib_trie.c#L2430">2430</a>         struct <a href="ident?i=seq_net_private">seq_net_private</a> <a href="ident?i=p">p</a>;
<a name="L2431" href="source/net/ipv4/fib_trie.c#L2431">2431</a>         struct <a href="ident?i=fib_table">fib_table</a> *main_tb;
<a name="L2432" href="source/net/ipv4/fib_trie.c#L2432">2432</a>         struct <a href="ident?i=key_vector">key_vector</a> *<a href="ident?i=tnode">tnode</a>;
<a name="L2433" href="source/net/ipv4/fib_trie.c#L2433">2433</a>         <a href="ident?i=loff_t">loff_t</a>  <a href="ident?i=pos">pos</a>;
<a name="L2434" href="source/net/ipv4/fib_trie.c#L2434">2434</a>         <a href="ident?i=t_key">t_key</a>   <a href="ident?i=key">key</a>;
<a name="L2435" href="source/net/ipv4/fib_trie.c#L2435">2435</a> };
<a name="L2436" href="source/net/ipv4/fib_trie.c#L2436">2436</a> 
<a name="L2437" href="source/net/ipv4/fib_trie.c#L2437">2437</a> static struct <a href="ident?i=key_vector">key_vector</a> *<a href="ident?i=fib_route_get_idx">fib_route_get_idx</a>(struct <a href="ident?i=fib_route_iter">fib_route_iter</a> *iter,
<a name="L2438" href="source/net/ipv4/fib_trie.c#L2438">2438</a>                                             <a href="ident?i=loff_t">loff_t</a> <a href="ident?i=pos">pos</a>)
<a name="L2439" href="source/net/ipv4/fib_trie.c#L2439">2439</a> {
<a name="L2440" href="source/net/ipv4/fib_trie.c#L2440">2440</a>         struct <a href="ident?i=fib_table">fib_table</a> *<a href="ident?i=tb">tb</a> = iter-&gt;main_tb;
<a name="L2441" href="source/net/ipv4/fib_trie.c#L2441">2441</a>         struct <a href="ident?i=key_vector">key_vector</a> *<a href="ident?i=l">l</a>, **<a href="ident?i=tp">tp</a> = &amp;iter-&gt;<a href="ident?i=tnode">tnode</a>;
<a name="L2442" href="source/net/ipv4/fib_trie.c#L2442">2442</a>         struct <a href="ident?i=trie">trie</a> *<a href="ident?i=t">t</a>;
<a name="L2443" href="source/net/ipv4/fib_trie.c#L2443">2443</a>         <a href="ident?i=t_key">t_key</a> <a href="ident?i=key">key</a>;
<a name="L2444" href="source/net/ipv4/fib_trie.c#L2444">2444</a> 
<a name="L2445" href="source/net/ipv4/fib_trie.c#L2445">2445</a>         <b><i>/* use cache location of next-to-find key */</i></b>
<a name="L2446" href="source/net/ipv4/fib_trie.c#L2446">2446</a>         if (iter-&gt;<a href="ident?i=pos">pos</a> &gt; 0 &amp;&amp; <a href="ident?i=pos">pos</a> &gt;= iter-&gt;<a href="ident?i=pos">pos</a>) {
<a name="L2447" href="source/net/ipv4/fib_trie.c#L2447">2447</a>                 <a href="ident?i=pos">pos</a> -= iter-&gt;<a href="ident?i=pos">pos</a>;
<a name="L2448" href="source/net/ipv4/fib_trie.c#L2448">2448</a>                 <a href="ident?i=key">key</a> = iter-&gt;<a href="ident?i=key">key</a>;
<a name="L2449" href="source/net/ipv4/fib_trie.c#L2449">2449</a>         } else {
<a name="L2450" href="source/net/ipv4/fib_trie.c#L2450">2450</a>                 <a href="ident?i=t">t</a> = (struct <a href="ident?i=trie">trie</a> *)<a href="ident?i=tb">tb</a>-&gt;tb_data;
<a name="L2451" href="source/net/ipv4/fib_trie.c#L2451">2451</a>                 iter-&gt;<a href="ident?i=tnode">tnode</a> = <a href="ident?i=t">t</a>-&gt;kv;
<a name="L2452" href="source/net/ipv4/fib_trie.c#L2452">2452</a>                 iter-&gt;<a href="ident?i=pos">pos</a> = 0;
<a name="L2453" href="source/net/ipv4/fib_trie.c#L2453">2453</a>                 <a href="ident?i=key">key</a> = 0;
<a name="L2454" href="source/net/ipv4/fib_trie.c#L2454">2454</a>         }
<a name="L2455" href="source/net/ipv4/fib_trie.c#L2455">2455</a> 
<a name="L2456" href="source/net/ipv4/fib_trie.c#L2456">2456</a>         while ((<a href="ident?i=l">l</a> = <a href="ident?i=leaf_walk_rcu">leaf_walk_rcu</a>(<a href="ident?i=tp">tp</a>, <a href="ident?i=key">key</a>)) != <a href="ident?i=NULL">NULL</a>) {
<a name="L2457" href="source/net/ipv4/fib_trie.c#L2457">2457</a>                 <a href="ident?i=key">key</a> = <a href="ident?i=l">l</a>-&gt;<a href="ident?i=key">key</a> + 1;
<a name="L2458" href="source/net/ipv4/fib_trie.c#L2458">2458</a>                 iter-&gt;<a href="ident?i=pos">pos</a>++;
<a name="L2459" href="source/net/ipv4/fib_trie.c#L2459">2459</a> 
<a name="L2460" href="source/net/ipv4/fib_trie.c#L2460">2460</a>                 if (<a href="ident?i=pos">pos</a>-- &lt;= 0)
<a name="L2461" href="source/net/ipv4/fib_trie.c#L2461">2461</a>                         break;
<a name="L2462" href="source/net/ipv4/fib_trie.c#L2462">2462</a> 
<a name="L2463" href="source/net/ipv4/fib_trie.c#L2463">2463</a>                 <a href="ident?i=l">l</a> = <a href="ident?i=NULL">NULL</a>;
<a name="L2464" href="source/net/ipv4/fib_trie.c#L2464">2464</a> 
<a name="L2465" href="source/net/ipv4/fib_trie.c#L2465">2465</a>                 <b><i>/* handle unlikely case of a key wrap */</i></b>
<a name="L2466" href="source/net/ipv4/fib_trie.c#L2466">2466</a>                 if (!<a href="ident?i=key">key</a>)
<a name="L2467" href="source/net/ipv4/fib_trie.c#L2467">2467</a>                         break;
<a name="L2468" href="source/net/ipv4/fib_trie.c#L2468">2468</a>         }
<a name="L2469" href="source/net/ipv4/fib_trie.c#L2469">2469</a> 
<a name="L2470" href="source/net/ipv4/fib_trie.c#L2470">2470</a>         if (<a href="ident?i=l">l</a>)
<a name="L2471" href="source/net/ipv4/fib_trie.c#L2471">2471</a>                 iter-&gt;<a href="ident?i=key">key</a> = <a href="ident?i=key">key</a>;        <b><i>/* remember it */</i></b>
<a name="L2472" href="source/net/ipv4/fib_trie.c#L2472">2472</a>         else
<a name="L2473" href="source/net/ipv4/fib_trie.c#L2473">2473</a>                 iter-&gt;<a href="ident?i=pos">pos</a> = 0;          <b><i>/* forget it */</i></b>
<a name="L2474" href="source/net/ipv4/fib_trie.c#L2474">2474</a> 
<a name="L2475" href="source/net/ipv4/fib_trie.c#L2475">2475</a>         return <a href="ident?i=l">l</a>;
<a name="L2476" href="source/net/ipv4/fib_trie.c#L2476">2476</a> }
<a name="L2477" href="source/net/ipv4/fib_trie.c#L2477">2477</a> 
<a name="L2478" href="source/net/ipv4/fib_trie.c#L2478">2478</a> static void *fib_route_seq_start(struct <a href="ident?i=seq_file">seq_file</a> *<a href="ident?i=seq">seq</a>, <a href="ident?i=loff_t">loff_t</a> *<a href="ident?i=pos">pos</a>)
<a name="L2479" href="source/net/ipv4/fib_trie.c#L2479">2479</a>         <a href="ident?i=__acquires">__acquires</a>(RCU)
<a name="L2480" href="source/net/ipv4/fib_trie.c#L2480">2480</a> {
<a name="L2481" href="source/net/ipv4/fib_trie.c#L2481">2481</a>         struct <a href="ident?i=fib_route_iter">fib_route_iter</a> *iter = <a href="ident?i=seq">seq</a>-&gt;<a href="ident?i=private">private</a>;
<a name="L2482" href="source/net/ipv4/fib_trie.c#L2482">2482</a>         struct <a href="ident?i=fib_table">fib_table</a> *<a href="ident?i=tb">tb</a>;
<a name="L2483" href="source/net/ipv4/fib_trie.c#L2483">2483</a>         struct <a href="ident?i=trie">trie</a> *<a href="ident?i=t">t</a>;
<a name="L2484" href="source/net/ipv4/fib_trie.c#L2484">2484</a> 
<a name="L2485" href="source/net/ipv4/fib_trie.c#L2485">2485</a>         <a href="ident?i=rcu_read_lock">rcu_read_lock</a>();
<a name="L2486" href="source/net/ipv4/fib_trie.c#L2486">2486</a> 
<a name="L2487" href="source/net/ipv4/fib_trie.c#L2487">2487</a>         <a href="ident?i=tb">tb</a> = <a href="ident?i=fib_get_table">fib_get_table</a>(<a href="ident?i=seq_file_net">seq_file_net</a>(<a href="ident?i=seq">seq</a>), RT_TABLE_MAIN);
<a name="L2488" href="source/net/ipv4/fib_trie.c#L2488">2488</a>         if (!<a href="ident?i=tb">tb</a>)
<a name="L2489" href="source/net/ipv4/fib_trie.c#L2489">2489</a>                 return <a href="ident?i=NULL">NULL</a>;
<a name="L2490" href="source/net/ipv4/fib_trie.c#L2490">2490</a> 
<a name="L2491" href="source/net/ipv4/fib_trie.c#L2491">2491</a>         iter-&gt;main_tb = <a href="ident?i=tb">tb</a>;
<a name="L2492" href="source/net/ipv4/fib_trie.c#L2492">2492</a> 
<a name="L2493" href="source/net/ipv4/fib_trie.c#L2493">2493</a>         if (*<a href="ident?i=pos">pos</a> != 0)
<a name="L2494" href="source/net/ipv4/fib_trie.c#L2494">2494</a>                 return <a href="ident?i=fib_route_get_idx">fib_route_get_idx</a>(iter, *<a href="ident?i=pos">pos</a>);
<a name="L2495" href="source/net/ipv4/fib_trie.c#L2495">2495</a> 
<a name="L2496" href="source/net/ipv4/fib_trie.c#L2496">2496</a>         <a href="ident?i=t">t</a> = (struct <a href="ident?i=trie">trie</a> *)<a href="ident?i=tb">tb</a>-&gt;tb_data;
<a name="L2497" href="source/net/ipv4/fib_trie.c#L2497">2497</a>         iter-&gt;<a href="ident?i=tnode">tnode</a> = <a href="ident?i=t">t</a>-&gt;kv;
<a name="L2498" href="source/net/ipv4/fib_trie.c#L2498">2498</a>         iter-&gt;<a href="ident?i=pos">pos</a> = 0;
<a name="L2499" href="source/net/ipv4/fib_trie.c#L2499">2499</a>         iter-&gt;<a href="ident?i=key">key</a> = 0;
<a name="L2500" href="source/net/ipv4/fib_trie.c#L2500">2500</a> 
<a name="L2501" href="source/net/ipv4/fib_trie.c#L2501">2501</a>         return <a href="ident?i=SEQ_START_TOKEN">SEQ_START_TOKEN</a>;
<a name="L2502" href="source/net/ipv4/fib_trie.c#L2502">2502</a> }
<a name="L2503" href="source/net/ipv4/fib_trie.c#L2503">2503</a> 
<a name="L2504" href="source/net/ipv4/fib_trie.c#L2504">2504</a> static void *<a href="ident?i=fib_route_seq_next">fib_route_seq_next</a>(struct <a href="ident?i=seq_file">seq_file</a> *<a href="ident?i=seq">seq</a>, void *<a href="ident?i=v">v</a>, <a href="ident?i=loff_t">loff_t</a> *<a href="ident?i=pos">pos</a>)
<a name="L2505" href="source/net/ipv4/fib_trie.c#L2505">2505</a> {
<a name="L2506" href="source/net/ipv4/fib_trie.c#L2506">2506</a>         struct <a href="ident?i=fib_route_iter">fib_route_iter</a> *iter = <a href="ident?i=seq">seq</a>-&gt;<a href="ident?i=private">private</a>;
<a name="L2507" href="source/net/ipv4/fib_trie.c#L2507">2507</a>         struct <a href="ident?i=key_vector">key_vector</a> *<a href="ident?i=l">l</a> = <a href="ident?i=NULL">NULL</a>;
<a name="L2508" href="source/net/ipv4/fib_trie.c#L2508">2508</a>         <a href="ident?i=t_key">t_key</a> <a href="ident?i=key">key</a> = iter-&gt;<a href="ident?i=key">key</a>;
<a name="L2509" href="source/net/ipv4/fib_trie.c#L2509">2509</a> 
<a name="L2510" href="source/net/ipv4/fib_trie.c#L2510">2510</a>         ++*<a href="ident?i=pos">pos</a>;
<a name="L2511" href="source/net/ipv4/fib_trie.c#L2511">2511</a> 
<a name="L2512" href="source/net/ipv4/fib_trie.c#L2512">2512</a>         <b><i>/* only allow key of 0 for start of sequence */</i></b>
<a name="L2513" href="source/net/ipv4/fib_trie.c#L2513">2513</a>         if ((<a href="ident?i=v">v</a> == <a href="ident?i=SEQ_START_TOKEN">SEQ_START_TOKEN</a>) || <a href="ident?i=key">key</a>)
<a name="L2514" href="source/net/ipv4/fib_trie.c#L2514">2514</a>                 <a href="ident?i=l">l</a> = <a href="ident?i=leaf_walk_rcu">leaf_walk_rcu</a>(&amp;iter-&gt;<a href="ident?i=tnode">tnode</a>, <a href="ident?i=key">key</a>);
<a name="L2515" href="source/net/ipv4/fib_trie.c#L2515">2515</a> 
<a name="L2516" href="source/net/ipv4/fib_trie.c#L2516">2516</a>         if (<a href="ident?i=l">l</a>) {
<a name="L2517" href="source/net/ipv4/fib_trie.c#L2517">2517</a>                 iter-&gt;<a href="ident?i=key">key</a> = <a href="ident?i=l">l</a>-&gt;<a href="ident?i=key">key</a> + 1;
<a name="L2518" href="source/net/ipv4/fib_trie.c#L2518">2518</a>                 iter-&gt;<a href="ident?i=pos">pos</a>++;
<a name="L2519" href="source/net/ipv4/fib_trie.c#L2519">2519</a>         } else {
<a name="L2520" href="source/net/ipv4/fib_trie.c#L2520">2520</a>                 iter-&gt;<a href="ident?i=pos">pos</a> = 0;
<a name="L2521" href="source/net/ipv4/fib_trie.c#L2521">2521</a>         }
<a name="L2522" href="source/net/ipv4/fib_trie.c#L2522">2522</a> 
<a name="L2523" href="source/net/ipv4/fib_trie.c#L2523">2523</a>         return <a href="ident?i=l">l</a>;
<a name="L2524" href="source/net/ipv4/fib_trie.c#L2524">2524</a> }
<a name="L2525" href="source/net/ipv4/fib_trie.c#L2525">2525</a> 
<a name="L2526" href="source/net/ipv4/fib_trie.c#L2526">2526</a> static void fib_route_seq_stop(struct <a href="ident?i=seq_file">seq_file</a> *<a href="ident?i=seq">seq</a>, void *<a href="ident?i=v">v</a>)
<a name="L2527" href="source/net/ipv4/fib_trie.c#L2527">2527</a>         <a href="ident?i=__releases">__releases</a>(RCU)
<a name="L2528" href="source/net/ipv4/fib_trie.c#L2528">2528</a> {
<a name="L2529" href="source/net/ipv4/fib_trie.c#L2529">2529</a>         <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L2530" href="source/net/ipv4/fib_trie.c#L2530">2530</a> }
<a name="L2531" href="source/net/ipv4/fib_trie.c#L2531">2531</a> 
<a name="L2532" href="source/net/ipv4/fib_trie.c#L2532">2532</a> static unsigned int <a href="ident?i=fib_flag_trans">fib_flag_trans</a>(int <a href="ident?i=type">type</a>, <a href="ident?i=__be32">__be32</a> <a href="ident?i=mask">mask</a>, const struct <a href="ident?i=fib_info">fib_info</a> *fi)
<a name="L2533" href="source/net/ipv4/fib_trie.c#L2533">2533</a> {
<a name="L2534" href="source/net/ipv4/fib_trie.c#L2534">2534</a>         unsigned int <a href="ident?i=flags">flags</a> = 0;
<a name="L2535" href="source/net/ipv4/fib_trie.c#L2535">2535</a> 
<a name="L2536" href="source/net/ipv4/fib_trie.c#L2536">2536</a>         if (<a href="ident?i=type">type</a> == RTN_UNREACHABLE || <a href="ident?i=type">type</a> == RTN_PROHIBIT)
<a name="L2537" href="source/net/ipv4/fib_trie.c#L2537">2537</a>                 <a href="ident?i=flags">flags</a> = <a href="ident?i=RTF_REJECT">RTF_REJECT</a>;
<a name="L2538" href="source/net/ipv4/fib_trie.c#L2538">2538</a>         if (fi &amp;&amp; fi-&gt;<a href="ident?i=fib_nh">fib_nh</a>-&gt;nh_gw)
<a name="L2539" href="source/net/ipv4/fib_trie.c#L2539">2539</a>                 <a href="ident?i=flags">flags</a> |= <a href="ident?i=RTF_GATEWAY">RTF_GATEWAY</a>;
<a name="L2540" href="source/net/ipv4/fib_trie.c#L2540">2540</a>         if (<a href="ident?i=mask">mask</a> == <a href="ident?i=htonl">htonl</a>(0xFFFFFFFF))
<a name="L2541" href="source/net/ipv4/fib_trie.c#L2541">2541</a>                 <a href="ident?i=flags">flags</a> |= <a href="ident?i=RTF_HOST">RTF_HOST</a>;
<a name="L2542" href="source/net/ipv4/fib_trie.c#L2542">2542</a>         <a href="ident?i=flags">flags</a> |= <a href="ident?i=RTF_UP">RTF_UP</a>;
<a name="L2543" href="source/net/ipv4/fib_trie.c#L2543">2543</a>         return <a href="ident?i=flags">flags</a>;
<a name="L2544" href="source/net/ipv4/fib_trie.c#L2544">2544</a> }
<a name="L2545" href="source/net/ipv4/fib_trie.c#L2545">2545</a> 
<a name="L2546" href="source/net/ipv4/fib_trie.c#L2546">2546</a> <b><i>/*</i></b>
<a name="L2547" href="source/net/ipv4/fib_trie.c#L2547">2547</a> <b><i> *      This outputs /proc/net/route.</i></b>
<a name="L2548" href="source/net/ipv4/fib_trie.c#L2548">2548</a> <b><i> *      The format of the file is not supposed to be changed</i></b>
<a name="L2549" href="source/net/ipv4/fib_trie.c#L2549">2549</a> <b><i> *      and needs to be same as fib_hash output to avoid breaking</i></b>
<a name="L2550" href="source/net/ipv4/fib_trie.c#L2550">2550</a> <b><i> *      legacy utilities</i></b>
<a name="L2551" href="source/net/ipv4/fib_trie.c#L2551">2551</a> <b><i> */</i></b>
<a name="L2552" href="source/net/ipv4/fib_trie.c#L2552">2552</a> static int <a href="ident?i=fib_route_seq_show">fib_route_seq_show</a>(struct <a href="ident?i=seq_file">seq_file</a> *<a href="ident?i=seq">seq</a>, void *<a href="ident?i=v">v</a>)
<a name="L2553" href="source/net/ipv4/fib_trie.c#L2553">2553</a> {
<a name="L2554" href="source/net/ipv4/fib_trie.c#L2554">2554</a>         struct <a href="ident?i=fib_route_iter">fib_route_iter</a> *iter = <a href="ident?i=seq">seq</a>-&gt;<a href="ident?i=private">private</a>;
<a name="L2555" href="source/net/ipv4/fib_trie.c#L2555">2555</a>         struct <a href="ident?i=fib_table">fib_table</a> *<a href="ident?i=tb">tb</a> = iter-&gt;main_tb;
<a name="L2556" href="source/net/ipv4/fib_trie.c#L2556">2556</a>         struct <a href="ident?i=fib_alias">fib_alias</a> *fa;
<a name="L2557" href="source/net/ipv4/fib_trie.c#L2557">2557</a>         struct <a href="ident?i=key_vector">key_vector</a> *<a href="ident?i=l">l</a> = <a href="ident?i=v">v</a>;
<a name="L2558" href="source/net/ipv4/fib_trie.c#L2558">2558</a>         <a href="ident?i=__be32">__be32</a> <a href="ident?i=prefix">prefix</a>;
<a name="L2559" href="source/net/ipv4/fib_trie.c#L2559">2559</a> 
<a name="L2560" href="source/net/ipv4/fib_trie.c#L2560">2560</a>         if (<a href="ident?i=v">v</a> == <a href="ident?i=SEQ_START_TOKEN">SEQ_START_TOKEN</a>) {
<a name="L2561" href="source/net/ipv4/fib_trie.c#L2561">2561</a>                 <a href="ident?i=seq_printf">seq_printf</a>(<a href="ident?i=seq">seq</a>, <i>"%-127s\n"</i>, <i>"Iface\tDestination\tGateway "</i>
<a name="L2562" href="source/net/ipv4/fib_trie.c#L2562">2562</a>                            <i>"\tFlags\tRefCnt\tUse\tMetric\tMask\t\tMTU"</i>
<a name="L2563" href="source/net/ipv4/fib_trie.c#L2563">2563</a>                            <i>"\tWindow\tIRTT"</i>);
<a name="L2564" href="source/net/ipv4/fib_trie.c#L2564">2564</a>                 return 0;
<a name="L2565" href="source/net/ipv4/fib_trie.c#L2565">2565</a>         }
<a name="L2566" href="source/net/ipv4/fib_trie.c#L2566">2566</a> 
<a name="L2567" href="source/net/ipv4/fib_trie.c#L2567">2567</a>         <a href="ident?i=prefix">prefix</a> = <a href="ident?i=htonl">htonl</a>(<a href="ident?i=l">l</a>-&gt;<a href="ident?i=key">key</a>);
<a name="L2568" href="source/net/ipv4/fib_trie.c#L2568">2568</a> 
<a name="L2569" href="source/net/ipv4/fib_trie.c#L2569">2569</a>         <a href="ident?i=hlist_for_each_entry_rcu">hlist_for_each_entry_rcu</a>(fa, &amp;<a href="ident?i=l">l</a>-&gt;leaf, fa_list) {
<a name="L2570" href="source/net/ipv4/fib_trie.c#L2570">2570</a>                 const struct <a href="ident?i=fib_info">fib_info</a> *fi = fa-&gt;fa_info;
<a name="L2571" href="source/net/ipv4/fib_trie.c#L2571">2571</a>                 <a href="ident?i=__be32">__be32</a> <a href="ident?i=mask">mask</a> = <a href="ident?i=inet_make_mask">inet_make_mask</a>(<a href="ident?i=KEYLENGTH">KEYLENGTH</a> - fa-&gt;fa_slen);
<a name="L2572" href="source/net/ipv4/fib_trie.c#L2572">2572</a>                 unsigned int <a href="ident?i=flags">flags</a> = <a href="ident?i=fib_flag_trans">fib_flag_trans</a>(fa-&gt;fa_type, <a href="ident?i=mask">mask</a>, fi);
<a name="L2573" href="source/net/ipv4/fib_trie.c#L2573">2573</a> 
<a name="L2574" href="source/net/ipv4/fib_trie.c#L2574">2574</a>                 if ((fa-&gt;fa_type == RTN_BROADCAST) ||
<a name="L2575" href="source/net/ipv4/fib_trie.c#L2575">2575</a>                     (fa-&gt;fa_type == RTN_MULTICAST))
<a name="L2576" href="source/net/ipv4/fib_trie.c#L2576">2576</a>                         continue;
<a name="L2577" href="source/net/ipv4/fib_trie.c#L2577">2577</a> 
<a name="L2578" href="source/net/ipv4/fib_trie.c#L2578">2578</a>                 if (fa-&gt;tb_id != <a href="ident?i=tb">tb</a>-&gt;tb_id)
<a name="L2579" href="source/net/ipv4/fib_trie.c#L2579">2579</a>                         continue;
<a name="L2580" href="source/net/ipv4/fib_trie.c#L2580">2580</a> 
<a name="L2581" href="source/net/ipv4/fib_trie.c#L2581">2581</a>                 <a href="ident?i=seq_setwidth">seq_setwidth</a>(<a href="ident?i=seq">seq</a>, 127);
<a name="L2582" href="source/net/ipv4/fib_trie.c#L2582">2582</a> 
<a name="L2583" href="source/net/ipv4/fib_trie.c#L2583">2583</a>                 if (fi)
<a name="L2584" href="source/net/ipv4/fib_trie.c#L2584">2584</a>                         <a href="ident?i=seq_printf">seq_printf</a>(<a href="ident?i=seq">seq</a>,
<a name="L2585" href="source/net/ipv4/fib_trie.c#L2585">2585</a>                                    <i>"%s\t%08X\t%08X\t%04X\t%d\t%u\t"</i>
<a name="L2586" href="source/net/ipv4/fib_trie.c#L2586">2586</a>                                    <i>"%d\t%08X\t%d\t%u\t%u"</i>,
<a name="L2587" href="source/net/ipv4/fib_trie.c#L2587">2587</a>                                    fi-&gt;<a href="ident?i=fib_dev">fib_dev</a> ? fi-&gt;<a href="ident?i=fib_dev">fib_dev</a>-&gt;<a href="ident?i=name">name</a> : <i>"*"</i>,
<a name="L2588" href="source/net/ipv4/fib_trie.c#L2588">2588</a>                                    <a href="ident?i=prefix">prefix</a>,
<a name="L2589" href="source/net/ipv4/fib_trie.c#L2589">2589</a>                                    fi-&gt;<a href="ident?i=fib_nh">fib_nh</a>-&gt;nh_gw, <a href="ident?i=flags">flags</a>, 0, 0,
<a name="L2590" href="source/net/ipv4/fib_trie.c#L2590">2590</a>                                    fi-&gt;fib_priority,
<a name="L2591" href="source/net/ipv4/fib_trie.c#L2591">2591</a>                                    <a href="ident?i=mask">mask</a>,
<a name="L2592" href="source/net/ipv4/fib_trie.c#L2592">2592</a>                                    (fi-&gt;<a href="ident?i=fib_advmss">fib_advmss</a> ?
<a name="L2593" href="source/net/ipv4/fib_trie.c#L2593">2593</a>                                     fi-&gt;<a href="ident?i=fib_advmss">fib_advmss</a> + 40 : 0),
<a name="L2594" href="source/net/ipv4/fib_trie.c#L2594">2594</a>                                    fi-&gt;<a href="ident?i=fib_window">fib_window</a>,
<a name="L2595" href="source/net/ipv4/fib_trie.c#L2595">2595</a>                                    fi-&gt;<a href="ident?i=fib_rtt">fib_rtt</a> &gt;&gt; 3);
<a name="L2596" href="source/net/ipv4/fib_trie.c#L2596">2596</a>                 else
<a name="L2597" href="source/net/ipv4/fib_trie.c#L2597">2597</a>                         <a href="ident?i=seq_printf">seq_printf</a>(<a href="ident?i=seq">seq</a>,
<a name="L2598" href="source/net/ipv4/fib_trie.c#L2598">2598</a>                                    <i>"*\t%08X\t%08X\t%04X\t%d\t%u\t"</i>
<a name="L2599" href="source/net/ipv4/fib_trie.c#L2599">2599</a>                                    <i>"%d\t%08X\t%d\t%u\t%u"</i>,
<a name="L2600" href="source/net/ipv4/fib_trie.c#L2600">2600</a>                                    <a href="ident?i=prefix">prefix</a>, 0, <a href="ident?i=flags">flags</a>, 0, 0, 0,
<a name="L2601" href="source/net/ipv4/fib_trie.c#L2601">2601</a>                                    <a href="ident?i=mask">mask</a>, 0, 0, 0);
<a name="L2602" href="source/net/ipv4/fib_trie.c#L2602">2602</a> 
<a name="L2603" href="source/net/ipv4/fib_trie.c#L2603">2603</a>                 <a href="ident?i=seq_pad">seq_pad</a>(<a href="ident?i=seq">seq</a>, <i>'\n'</i>);
<a name="L2604" href="source/net/ipv4/fib_trie.c#L2604">2604</a>         }
<a name="L2605" href="source/net/ipv4/fib_trie.c#L2605">2605</a> 
<a name="L2606" href="source/net/ipv4/fib_trie.c#L2606">2606</a>         return 0;
<a name="L2607" href="source/net/ipv4/fib_trie.c#L2607">2607</a> }
<a name="L2608" href="source/net/ipv4/fib_trie.c#L2608">2608</a> 
<a name="L2609" href="source/net/ipv4/fib_trie.c#L2609">2609</a> static const struct <a href="ident?i=seq_operations">seq_operations</a> <a href="ident?i=fib_route_seq_ops">fib_route_seq_ops</a> = {
<a name="L2610" href="source/net/ipv4/fib_trie.c#L2610">2610</a>         .<a href="ident?i=start">start</a>  = fib_route_seq_start,
<a name="L2611" href="source/net/ipv4/fib_trie.c#L2611">2611</a>         .<a href="ident?i=next">next</a>   = <a href="ident?i=fib_route_seq_next">fib_route_seq_next</a>,
<a name="L2612" href="source/net/ipv4/fib_trie.c#L2612">2612</a>         .<a href="ident?i=stop">stop</a>   = fib_route_seq_stop,
<a name="L2613" href="source/net/ipv4/fib_trie.c#L2613">2613</a>         .<a href="ident?i=show">show</a>   = <a href="ident?i=fib_route_seq_show">fib_route_seq_show</a>,
<a name="L2614" href="source/net/ipv4/fib_trie.c#L2614">2614</a> };
<a name="L2615" href="source/net/ipv4/fib_trie.c#L2615">2615</a> 
<a name="L2616" href="source/net/ipv4/fib_trie.c#L2616">2616</a> static int <a href="ident?i=fib_route_seq_open">fib_route_seq_open</a>(struct <a href="ident?i=inode">inode</a> *<a href="ident?i=inode">inode</a>, struct <a href="ident?i=file">file</a> *<a href="ident?i=file">file</a>)
<a name="L2617" href="source/net/ipv4/fib_trie.c#L2617">2617</a> {
<a name="L2618" href="source/net/ipv4/fib_trie.c#L2618">2618</a>         return <a href="ident?i=seq_open_net">seq_open_net</a>(<a href="ident?i=inode">inode</a>, <a href="ident?i=file">file</a>, &amp;<a href="ident?i=fib_route_seq_ops">fib_route_seq_ops</a>,
<a name="L2619" href="source/net/ipv4/fib_trie.c#L2619">2619</a>                             sizeof(struct <a href="ident?i=fib_route_iter">fib_route_iter</a>));
<a name="L2620" href="source/net/ipv4/fib_trie.c#L2620">2620</a> }
<a name="L2621" href="source/net/ipv4/fib_trie.c#L2621">2621</a> 
<a name="L2622" href="source/net/ipv4/fib_trie.c#L2622">2622</a> static const struct <a href="ident?i=file_operations">file_operations</a> <a href="ident?i=fib_route_fops">fib_route_fops</a> = {
<a name="L2623" href="source/net/ipv4/fib_trie.c#L2623">2623</a>         .owner  = <a href="ident?i=THIS_MODULE">THIS_MODULE</a>,
<a name="L2624" href="source/net/ipv4/fib_trie.c#L2624">2624</a>         .<a href="ident?i=open">open</a>   = <a href="ident?i=fib_route_seq_open">fib_route_seq_open</a>,
<a name="L2625" href="source/net/ipv4/fib_trie.c#L2625">2625</a>         .<a href="ident?i=read">read</a>   = <a href="ident?i=seq_read">seq_read</a>,
<a name="L2626" href="source/net/ipv4/fib_trie.c#L2626">2626</a>         .llseek = <a href="ident?i=seq_lseek">seq_lseek</a>,
<a name="L2627" href="source/net/ipv4/fib_trie.c#L2627">2627</a>         .<a href="ident?i=release">release</a> = <a href="ident?i=seq_release_net">seq_release_net</a>,
<a name="L2628" href="source/net/ipv4/fib_trie.c#L2628">2628</a> };
<a name="L2629" href="source/net/ipv4/fib_trie.c#L2629">2629</a> 
<a name="L2630" href="source/net/ipv4/fib_trie.c#L2630">2630</a> int <a href="ident?i=__net_init">__net_init</a> <a href="ident?i=fib_proc_init">fib_proc_init</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>)
<a name="L2631" href="source/net/ipv4/fib_trie.c#L2631">2631</a> {
<a name="L2632" href="source/net/ipv4/fib_trie.c#L2632">2632</a>         if (!<a href="ident?i=proc_create">proc_create</a>(<i>"fib_trie"</i>, <a href="ident?i=S_IRUGO">S_IRUGO</a>, <a href="ident?i=net">net</a>-&gt;proc_net, &amp;<a href="ident?i=fib_trie_fops">fib_trie_fops</a>))
<a name="L2633" href="source/net/ipv4/fib_trie.c#L2633">2633</a>                 goto out1;
<a name="L2634" href="source/net/ipv4/fib_trie.c#L2634">2634</a> 
<a name="L2635" href="source/net/ipv4/fib_trie.c#L2635">2635</a>         if (!<a href="ident?i=proc_create">proc_create</a>(<i>"fib_triestat"</i>, <a href="ident?i=S_IRUGO">S_IRUGO</a>, <a href="ident?i=net">net</a>-&gt;proc_net,
<a name="L2636" href="source/net/ipv4/fib_trie.c#L2636">2636</a>                          &amp;<a href="ident?i=fib_triestat_fops">fib_triestat_fops</a>))
<a name="L2637" href="source/net/ipv4/fib_trie.c#L2637">2637</a>                 goto out2;
<a name="L2638" href="source/net/ipv4/fib_trie.c#L2638">2638</a> 
<a name="L2639" href="source/net/ipv4/fib_trie.c#L2639">2639</a>         if (!<a href="ident?i=proc_create">proc_create</a>(<i>"route"</i>, <a href="ident?i=S_IRUGO">S_IRUGO</a>, <a href="ident?i=net">net</a>-&gt;proc_net, &amp;<a href="ident?i=fib_route_fops">fib_route_fops</a>))
<a name="L2640" href="source/net/ipv4/fib_trie.c#L2640">2640</a>                 goto out3;
<a name="L2641" href="source/net/ipv4/fib_trie.c#L2641">2641</a> 
<a name="L2642" href="source/net/ipv4/fib_trie.c#L2642">2642</a>         return 0;
<a name="L2643" href="source/net/ipv4/fib_trie.c#L2643">2643</a> 
<a name="L2644" href="source/net/ipv4/fib_trie.c#L2644">2644</a> out3:
<a name="L2645" href="source/net/ipv4/fib_trie.c#L2645">2645</a>         <a href="ident?i=remove_proc_entry">remove_proc_entry</a>(<i>"fib_triestat"</i>, <a href="ident?i=net">net</a>-&gt;proc_net);
<a name="L2646" href="source/net/ipv4/fib_trie.c#L2646">2646</a> out2:
<a name="L2647" href="source/net/ipv4/fib_trie.c#L2647">2647</a>         <a href="ident?i=remove_proc_entry">remove_proc_entry</a>(<i>"fib_trie"</i>, <a href="ident?i=net">net</a>-&gt;proc_net);
<a name="L2648" href="source/net/ipv4/fib_trie.c#L2648">2648</a> out1:
<a name="L2649" href="source/net/ipv4/fib_trie.c#L2649">2649</a>         return -<a href="ident?i=ENOMEM">ENOMEM</a>;
<a name="L2650" href="source/net/ipv4/fib_trie.c#L2650">2650</a> }
<a name="L2651" href="source/net/ipv4/fib_trie.c#L2651">2651</a> 
<a name="L2652" href="source/net/ipv4/fib_trie.c#L2652">2652</a> void <a href="ident?i=__net_exit">__net_exit</a> <a href="ident?i=fib_proc_exit">fib_proc_exit</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>)
<a name="L2653" href="source/net/ipv4/fib_trie.c#L2653">2653</a> {
<a name="L2654" href="source/net/ipv4/fib_trie.c#L2654">2654</a>         <a href="ident?i=remove_proc_entry">remove_proc_entry</a>(<i>"fib_trie"</i>, <a href="ident?i=net">net</a>-&gt;proc_net);
<a name="L2655" href="source/net/ipv4/fib_trie.c#L2655">2655</a>         <a href="ident?i=remove_proc_entry">remove_proc_entry</a>(<i>"fib_triestat"</i>, <a href="ident?i=net">net</a>-&gt;proc_net);
<a name="L2656" href="source/net/ipv4/fib_trie.c#L2656">2656</a>         <a href="ident?i=remove_proc_entry">remove_proc_entry</a>(<i>"route"</i>, <a href="ident?i=net">net</a>-&gt;proc_net);
<a name="L2657" href="source/net/ipv4/fib_trie.c#L2657">2657</a> }
<a name="L2658" href="source/net/ipv4/fib_trie.c#L2658">2658</a> 
<a name="L2659" href="source/net/ipv4/fib_trie.c#L2659">2659</a> #endif <b><i>/* CONFIG_PROC_FS */</i></b>
<a name="L2660" href="source/net/ipv4/fib_trie.c#L2660">2660</a> </pre></div><p>
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
