<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title>Linux/net/ipv4/inet_fragment.c - Linux Cross Reference - Free Electrons</title>
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
		 &nbsp;&bull;&nbsp;<b><i>source navigation</i></b> &nbsp;&bull;&nbsp;<a href="diff/net/ipv4/inet_fragment.c">diff markup</a> &nbsp;&bull;&nbsp;<a href="ident">identifier search</a> &nbsp;&bull;&nbsp;<a href="search">freetext search</a> &nbsp;&bull;&nbsp;
		</p>
	</div>
</div>

<div id="topbar">
  
  <p>Version: &nbsp;<a href="source/net/ipv4/inet_fragment.c?v=2.0.40">2.0.40</a>&nbsp;<a href="source/net/ipv4/inet_fragment.c?v=2.2.26">2.2.26</a>&nbsp;<a href="source/net/ipv4/inet_fragment.c?v=2.4.37">2.4.37</a>&nbsp;<a href="source/net/ipv4/inet_fragment.c?v=3.5">3.5</a>&nbsp;<a href="source/net/ipv4/inet_fragment.c?v=3.6">3.6</a>&nbsp;<a href="source/net/ipv4/inet_fragment.c?v=3.7">3.7</a>&nbsp;<a href="source/net/ipv4/inet_fragment.c?v=3.8">3.8</a>&nbsp;<a href="source/net/ipv4/inet_fragment.c?v=3.9">3.9</a>&nbsp;<a href="source/net/ipv4/inet_fragment.c?v=3.10">3.10</a>&nbsp;<a href="source/net/ipv4/inet_fragment.c?v=3.11">3.11</a>&nbsp;<a href="source/net/ipv4/inet_fragment.c?v=3.12">3.12</a>&nbsp;<a href="source/net/ipv4/inet_fragment.c?v=3.13">3.13</a>&nbsp;<a href="source/net/ipv4/inet_fragment.c?v=3.14">3.14</a>&nbsp;<a href="source/net/ipv4/inet_fragment.c?v=3.15">3.15</a>&nbsp;<a href="source/net/ipv4/inet_fragment.c?v=3.16">3.16</a>&nbsp;<a href="source/net/ipv4/inet_fragment.c?v=3.17">3.17</a>&nbsp;<a href="source/net/ipv4/inet_fragment.c?v=3.18">3.18</a>&nbsp;<a href="source/net/ipv4/inet_fragment.c?v=3.19">3.19</a>&nbsp;<a href="source/net/ipv4/inet_fragment.c?v=4.0">4.0</a>&nbsp;<b><i>4.1</i></b></p>
  
</div>

<h1><a href="source/">Linux</a>/<a href="source/net/">net</a>/<a href="source/net/ipv4/">ipv4</a>/<a href="source/net/ipv4/inet_fragment.c">inet_fragment.c</a></h1>
<div id="lxrcode"><pre>  <a name="L1" href="source/net/ipv4/inet_fragment.c#L1">1</a> <b><i>/*</i></b>
  <a name="L2" href="source/net/ipv4/inet_fragment.c#L2">2</a> <b><i> * inet fragments management</i></b>
  <a name="L3" href="source/net/ipv4/inet_fragment.c#L3">3</a> <b><i> *</i></b>
  <a name="L4" href="source/net/ipv4/inet_fragment.c#L4">4</a> <b><i> *              This program is free software; you can redistribute it and/or</i></b>
  <a name="L5" href="source/net/ipv4/inet_fragment.c#L5">5</a> <b><i> *              modify it under the terms of the GNU General Public License</i></b>
  <a name="L6" href="source/net/ipv4/inet_fragment.c#L6">6</a> <b><i> *              as published by the Free Software Foundation; either version</i></b>
  <a name="L7" href="source/net/ipv4/inet_fragment.c#L7">7</a> <b><i> *              2 of the License, or (at your option) any later version.</i></b>
  <a name="L8" href="source/net/ipv4/inet_fragment.c#L8">8</a> <b><i> *</i></b>
  <a name="L9" href="source/net/ipv4/inet_fragment.c#L9">9</a> <b><i> *              Authors:        Pavel Emelyanov &lt;xemul@openvz.org&gt;</i></b>
 <a name="L10" href="source/net/ipv4/inet_fragment.c#L10">10</a> <b><i> *                              Started as consolidation of ipv4/ip_fragment.c,</i></b>
 <a name="L11" href="source/net/ipv4/inet_fragment.c#L11">11</a> <b><i> *                              ipv6/reassembly. and ipv6 nf conntrack reassembly</i></b>
 <a name="L12" href="source/net/ipv4/inet_fragment.c#L12">12</a> <b><i> */</i></b>
 <a name="L13" href="source/net/ipv4/inet_fragment.c#L13">13</a> 
 <a name="L14" href="source/net/ipv4/inet_fragment.c#L14">14</a> #include &lt;linux/list.h&gt;
 <a name="L15" href="source/net/ipv4/inet_fragment.c#L15">15</a> #include &lt;linux/spinlock.h&gt;
 <a name="L16" href="source/net/ipv4/inet_fragment.c#L16">16</a> #include &lt;linux/module.h&gt;
 <a name="L17" href="source/net/ipv4/inet_fragment.c#L17">17</a> #include &lt;linux/timer.h&gt;
 <a name="L18" href="source/net/ipv4/inet_fragment.c#L18">18</a> #include &lt;linux/mm.h&gt;
 <a name="L19" href="source/net/ipv4/inet_fragment.c#L19">19</a> #include &lt;linux/random.h&gt;
 <a name="L20" href="source/net/ipv4/inet_fragment.c#L20">20</a> #include &lt;linux/skbuff.h&gt;
 <a name="L21" href="source/net/ipv4/inet_fragment.c#L21">21</a> #include &lt;linux/rtnetlink.h&gt;
 <a name="L22" href="source/net/ipv4/inet_fragment.c#L22">22</a> #include &lt;linux/slab.h&gt;
 <a name="L23" href="source/net/ipv4/inet_fragment.c#L23">23</a> 
 <a name="L24" href="source/net/ipv4/inet_fragment.c#L24">24</a> #include &lt;net/sock.h&gt;
 <a name="L25" href="source/net/ipv4/inet_fragment.c#L25">25</a> #include &lt;net/inet_frag.h&gt;
 <a name="L26" href="source/net/ipv4/inet_fragment.c#L26">26</a> #include &lt;net/inet_ecn.h&gt;
 <a name="L27" href="source/net/ipv4/inet_fragment.c#L27">27</a> 
 <a name="L28" href="source/net/ipv4/inet_fragment.c#L28">28</a> #define <a href="ident?i=INETFRAGS_EVICT_BUCKETS">INETFRAGS_EVICT_BUCKETS</a>   128
 <a name="L29" href="source/net/ipv4/inet_fragment.c#L29">29</a> #define <a href="ident?i=INETFRAGS_EVICT_MAX">INETFRAGS_EVICT_MAX</a>       512
 <a name="L30" href="source/net/ipv4/inet_fragment.c#L30">30</a> 
 <a name="L31" href="source/net/ipv4/inet_fragment.c#L31">31</a> <b><i>/* don't rebuild inetfrag table with new secret more often than this */</i></b>
 <a name="L32" href="source/net/ipv4/inet_fragment.c#L32">32</a> #define <a href="ident?i=INETFRAGS_MIN_REBUILD_INTERVAL">INETFRAGS_MIN_REBUILD_INTERVAL</a> (5 * <a href="ident?i=HZ">HZ</a>)
 <a name="L33" href="source/net/ipv4/inet_fragment.c#L33">33</a> 
 <a name="L34" href="source/net/ipv4/inet_fragment.c#L34">34</a> <b><i>/* Given the OR values of all fragments, apply RFC 3168 5.3 requirements</i></b>
 <a name="L35" href="source/net/ipv4/inet_fragment.c#L35">35</a> <b><i> * Value : 0xff if frame should be dropped.</i></b>
 <a name="L36" href="source/net/ipv4/inet_fragment.c#L36">36</a> <b><i> *         0 or INET_ECN_CE value, to be ORed in to final iph-&gt;tos field</i></b>
 <a name="L37" href="source/net/ipv4/inet_fragment.c#L37">37</a> <b><i> */</i></b>
 <a name="L38" href="source/net/ipv4/inet_fragment.c#L38">38</a> const <a href="ident?i=u8">u8</a> <a href="ident?i=ip_frag_ecn_table">ip_frag_ecn_table</a>[16] = {
 <a name="L39" href="source/net/ipv4/inet_fragment.c#L39">39</a>         <b><i>/* at least one fragment had CE, and others ECT_0 or ECT_1 */</i></b>
 <a name="L40" href="source/net/ipv4/inet_fragment.c#L40">40</a>         [<a href="ident?i=IPFRAG_ECN_CE">IPFRAG_ECN_CE</a> | <a href="ident?i=IPFRAG_ECN_ECT_0">IPFRAG_ECN_ECT_0</a>]                      = INET_ECN_CE,
 <a name="L41" href="source/net/ipv4/inet_fragment.c#L41">41</a>         [<a href="ident?i=IPFRAG_ECN_CE">IPFRAG_ECN_CE</a> | <a href="ident?i=IPFRAG_ECN_ECT_1">IPFRAG_ECN_ECT_1</a>]                      = INET_ECN_CE,
 <a name="L42" href="source/net/ipv4/inet_fragment.c#L42">42</a>         [<a href="ident?i=IPFRAG_ECN_CE">IPFRAG_ECN_CE</a> | <a href="ident?i=IPFRAG_ECN_ECT_0">IPFRAG_ECN_ECT_0</a> | <a href="ident?i=IPFRAG_ECN_ECT_1">IPFRAG_ECN_ECT_1</a>]   = INET_ECN_CE,
 <a name="L43" href="source/net/ipv4/inet_fragment.c#L43">43</a> 
 <a name="L44" href="source/net/ipv4/inet_fragment.c#L44">44</a>         <b><i>/* invalid combinations : drop frame */</i></b>
 <a name="L45" href="source/net/ipv4/inet_fragment.c#L45">45</a>         [<a href="ident?i=IPFRAG_ECN_NOT_ECT">IPFRAG_ECN_NOT_ECT</a> | <a href="ident?i=IPFRAG_ECN_CE">IPFRAG_ECN_CE</a>] = 0xff,
 <a name="L46" href="source/net/ipv4/inet_fragment.c#L46">46</a>         [<a href="ident?i=IPFRAG_ECN_NOT_ECT">IPFRAG_ECN_NOT_ECT</a> | <a href="ident?i=IPFRAG_ECN_ECT_0">IPFRAG_ECN_ECT_0</a>] = 0xff,
 <a name="L47" href="source/net/ipv4/inet_fragment.c#L47">47</a>         [<a href="ident?i=IPFRAG_ECN_NOT_ECT">IPFRAG_ECN_NOT_ECT</a> | <a href="ident?i=IPFRAG_ECN_ECT_1">IPFRAG_ECN_ECT_1</a>] = 0xff,
 <a name="L48" href="source/net/ipv4/inet_fragment.c#L48">48</a>         [<a href="ident?i=IPFRAG_ECN_NOT_ECT">IPFRAG_ECN_NOT_ECT</a> | <a href="ident?i=IPFRAG_ECN_ECT_0">IPFRAG_ECN_ECT_0</a> | <a href="ident?i=IPFRAG_ECN_ECT_1">IPFRAG_ECN_ECT_1</a>] = 0xff,
 <a name="L49" href="source/net/ipv4/inet_fragment.c#L49">49</a>         [<a href="ident?i=IPFRAG_ECN_NOT_ECT">IPFRAG_ECN_NOT_ECT</a> | <a href="ident?i=IPFRAG_ECN_CE">IPFRAG_ECN_CE</a> | <a href="ident?i=IPFRAG_ECN_ECT_0">IPFRAG_ECN_ECT_0</a>] = 0xff,
 <a name="L50" href="source/net/ipv4/inet_fragment.c#L50">50</a>         [<a href="ident?i=IPFRAG_ECN_NOT_ECT">IPFRAG_ECN_NOT_ECT</a> | <a href="ident?i=IPFRAG_ECN_CE">IPFRAG_ECN_CE</a> | <a href="ident?i=IPFRAG_ECN_ECT_1">IPFRAG_ECN_ECT_1</a>] = 0xff,
 <a name="L51" href="source/net/ipv4/inet_fragment.c#L51">51</a>         [<a href="ident?i=IPFRAG_ECN_NOT_ECT">IPFRAG_ECN_NOT_ECT</a> | <a href="ident?i=IPFRAG_ECN_CE">IPFRAG_ECN_CE</a> | <a href="ident?i=IPFRAG_ECN_ECT_0">IPFRAG_ECN_ECT_0</a> | <a href="ident?i=IPFRAG_ECN_ECT_1">IPFRAG_ECN_ECT_1</a>] = 0xff,
 <a name="L52" href="source/net/ipv4/inet_fragment.c#L52">52</a> };
 <a name="L53" href="source/net/ipv4/inet_fragment.c#L53">53</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=ip_frag_ecn_table">ip_frag_ecn_table</a>);
 <a name="L54" href="source/net/ipv4/inet_fragment.c#L54">54</a> 
 <a name="L55" href="source/net/ipv4/inet_fragment.c#L55">55</a> static unsigned int
 <a name="L56" href="source/net/ipv4/inet_fragment.c#L56">56</a> <a href="ident?i=inet_frag_hashfn">inet_frag_hashfn</a>(const struct <a href="ident?i=inet_frags">inet_frags</a> *<a href="ident?i=f">f</a>, const struct <a href="ident?i=inet_frag_queue">inet_frag_queue</a> *q)
 <a name="L57" href="source/net/ipv4/inet_fragment.c#L57">57</a> {
 <a name="L58" href="source/net/ipv4/inet_fragment.c#L58">58</a>         return <a href="ident?i=f">f</a>-&gt;<a href="ident?i=hashfn">hashfn</a>(q) &amp; (<a href="ident?i=INETFRAGS_HASHSZ">INETFRAGS_HASHSZ</a> - 1);
 <a name="L59" href="source/net/ipv4/inet_fragment.c#L59">59</a> }
 <a name="L60" href="source/net/ipv4/inet_fragment.c#L60">60</a> 
 <a name="L61" href="source/net/ipv4/inet_fragment.c#L61">61</a> static <a href="ident?i=bool">bool</a> <a href="ident?i=inet_frag_may_rebuild">inet_frag_may_rebuild</a>(struct <a href="ident?i=inet_frags">inet_frags</a> *<a href="ident?i=f">f</a>)
 <a name="L62" href="source/net/ipv4/inet_fragment.c#L62">62</a> {
 <a name="L63" href="source/net/ipv4/inet_fragment.c#L63">63</a>         return <a href="ident?i=time_after">time_after</a>(<a href="ident?i=jiffies">jiffies</a>,
 <a name="L64" href="source/net/ipv4/inet_fragment.c#L64">64</a>                <a href="ident?i=f">f</a>-&gt;last_rebuild_jiffies + <a href="ident?i=INETFRAGS_MIN_REBUILD_INTERVAL">INETFRAGS_MIN_REBUILD_INTERVAL</a>);
 <a name="L65" href="source/net/ipv4/inet_fragment.c#L65">65</a> }
 <a name="L66" href="source/net/ipv4/inet_fragment.c#L66">66</a> 
 <a name="L67" href="source/net/ipv4/inet_fragment.c#L67">67</a> static void <a href="ident?i=inet_frag_secret_rebuild">inet_frag_secret_rebuild</a>(struct <a href="ident?i=inet_frags">inet_frags</a> *<a href="ident?i=f">f</a>)
 <a name="L68" href="source/net/ipv4/inet_fragment.c#L68">68</a> {
 <a name="L69" href="source/net/ipv4/inet_fragment.c#L69">69</a>         int <a href="ident?i=i">i</a>;
 <a name="L70" href="source/net/ipv4/inet_fragment.c#L70">70</a> 
 <a name="L71" href="source/net/ipv4/inet_fragment.c#L71">71</a>         <a href="ident?i=write_seqlock_bh">write_seqlock_bh</a>(&amp;<a href="ident?i=f">f</a>-&gt;rnd_seqlock);
 <a name="L72" href="source/net/ipv4/inet_fragment.c#L72">72</a> 
 <a name="L73" href="source/net/ipv4/inet_fragment.c#L73">73</a>         if (!<a href="ident?i=inet_frag_may_rebuild">inet_frag_may_rebuild</a>(<a href="ident?i=f">f</a>))
 <a name="L74" href="source/net/ipv4/inet_fragment.c#L74">74</a>                 goto <a href="ident?i=out">out</a>;
 <a name="L75" href="source/net/ipv4/inet_fragment.c#L75">75</a> 
 <a name="L76" href="source/net/ipv4/inet_fragment.c#L76">76</a>         <a href="ident?i=get_random_bytes">get_random_bytes</a>(&amp;<a href="ident?i=f">f</a>-&gt;<a href="ident?i=rnd">rnd</a>, sizeof(<a href="ident?i=u32">u32</a>));
 <a name="L77" href="source/net/ipv4/inet_fragment.c#L77">77</a> 
 <a name="L78" href="source/net/ipv4/inet_fragment.c#L78">78</a>         for (<a href="ident?i=i">i</a> = 0; <a href="ident?i=i">i</a> &lt; <a href="ident?i=INETFRAGS_HASHSZ">INETFRAGS_HASHSZ</a>; <a href="ident?i=i">i</a>++) {
 <a name="L79" href="source/net/ipv4/inet_fragment.c#L79">79</a>                 struct <a href="ident?i=inet_frag_bucket">inet_frag_bucket</a> *hb;
 <a name="L80" href="source/net/ipv4/inet_fragment.c#L80">80</a>                 struct <a href="ident?i=inet_frag_queue">inet_frag_queue</a> *q;
 <a name="L81" href="source/net/ipv4/inet_fragment.c#L81">81</a>                 struct <a href="ident?i=hlist_node">hlist_node</a> *<a href="ident?i=n">n</a>;
 <a name="L82" href="source/net/ipv4/inet_fragment.c#L82">82</a> 
 <a name="L83" href="source/net/ipv4/inet_fragment.c#L83">83</a>                 hb = &amp;<a href="ident?i=f">f</a>-&gt;<a href="ident?i=hash">hash</a>[<a href="ident?i=i">i</a>];
 <a name="L84" href="source/net/ipv4/inet_fragment.c#L84">84</a>                 <a href="ident?i=spin_lock">spin_lock</a>(&amp;hb-&gt;chain_lock);
 <a name="L85" href="source/net/ipv4/inet_fragment.c#L85">85</a> 
 <a name="L86" href="source/net/ipv4/inet_fragment.c#L86">86</a>                 <a href="ident?i=hlist_for_each_entry_safe">hlist_for_each_entry_safe</a>(q, <a href="ident?i=n">n</a>, &amp;hb-&gt;<a href="ident?i=chain">chain</a>, <a href="ident?i=list">list</a>) {
 <a name="L87" href="source/net/ipv4/inet_fragment.c#L87">87</a>                         unsigned int hval = <a href="ident?i=inet_frag_hashfn">inet_frag_hashfn</a>(<a href="ident?i=f">f</a>, q);
 <a name="L88" href="source/net/ipv4/inet_fragment.c#L88">88</a> 
 <a name="L89" href="source/net/ipv4/inet_fragment.c#L89">89</a>                         if (hval != <a href="ident?i=i">i</a>) {
 <a name="L90" href="source/net/ipv4/inet_fragment.c#L90">90</a>                                 struct <a href="ident?i=inet_frag_bucket">inet_frag_bucket</a> *hb_dest;
 <a name="L91" href="source/net/ipv4/inet_fragment.c#L91">91</a> 
 <a name="L92" href="source/net/ipv4/inet_fragment.c#L92">92</a>                                 <a href="ident?i=hlist_del">hlist_del</a>(&amp;q-&gt;<a href="ident?i=list">list</a>);
 <a name="L93" href="source/net/ipv4/inet_fragment.c#L93">93</a> 
 <a name="L94" href="source/net/ipv4/inet_fragment.c#L94">94</a>                                 <b><i>/* Relink to new hash chain. */</i></b>
 <a name="L95" href="source/net/ipv4/inet_fragment.c#L95">95</a>                                 hb_dest = &amp;<a href="ident?i=f">f</a>-&gt;<a href="ident?i=hash">hash</a>[hval];
 <a name="L96" href="source/net/ipv4/inet_fragment.c#L96">96</a> 
 <a name="L97" href="source/net/ipv4/inet_fragment.c#L97">97</a>                                 <b><i>/* This is the only place where we take</i></b>
 <a name="L98" href="source/net/ipv4/inet_fragment.c#L98">98</a> <b><i>                                 * another chain_lock while already holding</i></b>
 <a name="L99" href="source/net/ipv4/inet_fragment.c#L99">99</a> <b><i>                                 * one.  As this will not run concurrently,</i></b>
<a name="L100" href="source/net/ipv4/inet_fragment.c#L100">100</a> <b><i>                                 * we cannot deadlock on hb_dest lock below, if its</i></b>
<a name="L101" href="source/net/ipv4/inet_fragment.c#L101">101</a> <b><i>                                 * already locked it will be released soon since</i></b>
<a name="L102" href="source/net/ipv4/inet_fragment.c#L102">102</a> <b><i>                                 * other caller cannot be waiting for hb lock</i></b>
<a name="L103" href="source/net/ipv4/inet_fragment.c#L103">103</a> <b><i>                                 * that we've taken above.</i></b>
<a name="L104" href="source/net/ipv4/inet_fragment.c#L104">104</a> <b><i>                                 */</i></b>
<a name="L105" href="source/net/ipv4/inet_fragment.c#L105">105</a>                                 <a href="ident?i=spin_lock_nested">spin_lock_nested</a>(&amp;hb_dest-&gt;chain_lock,
<a name="L106" href="source/net/ipv4/inet_fragment.c#L106">106</a>                                                  <a href="ident?i=SINGLE_DEPTH_NESTING">SINGLE_DEPTH_NESTING</a>);
<a name="L107" href="source/net/ipv4/inet_fragment.c#L107">107</a>                                 <a href="ident?i=hlist_add_head">hlist_add_head</a>(&amp;q-&gt;<a href="ident?i=list">list</a>, &amp;hb_dest-&gt;<a href="ident?i=chain">chain</a>);
<a name="L108" href="source/net/ipv4/inet_fragment.c#L108">108</a>                                 <a href="ident?i=spin_unlock">spin_unlock</a>(&amp;hb_dest-&gt;chain_lock);
<a name="L109" href="source/net/ipv4/inet_fragment.c#L109">109</a>                         }
<a name="L110" href="source/net/ipv4/inet_fragment.c#L110">110</a>                 }
<a name="L111" href="source/net/ipv4/inet_fragment.c#L111">111</a>                 <a href="ident?i=spin_unlock">spin_unlock</a>(&amp;hb-&gt;chain_lock);
<a name="L112" href="source/net/ipv4/inet_fragment.c#L112">112</a>         }
<a name="L113" href="source/net/ipv4/inet_fragment.c#L113">113</a> 
<a name="L114" href="source/net/ipv4/inet_fragment.c#L114">114</a>         <a href="ident?i=f">f</a>-&gt;rebuild = <a href="ident?i=false">false</a>;
<a name="L115" href="source/net/ipv4/inet_fragment.c#L115">115</a>         <a href="ident?i=f">f</a>-&gt;last_rebuild_jiffies = <a href="ident?i=jiffies">jiffies</a>;
<a name="L116" href="source/net/ipv4/inet_fragment.c#L116">116</a> <a href="ident?i=out">out</a>:
<a name="L117" href="source/net/ipv4/inet_fragment.c#L117">117</a>         <a href="ident?i=write_sequnlock_bh">write_sequnlock_bh</a>(&amp;<a href="ident?i=f">f</a>-&gt;rnd_seqlock);
<a name="L118" href="source/net/ipv4/inet_fragment.c#L118">118</a> }
<a name="L119" href="source/net/ipv4/inet_fragment.c#L119">119</a> 
<a name="L120" href="source/net/ipv4/inet_fragment.c#L120">120</a> static <a href="ident?i=bool">bool</a> <a href="ident?i=inet_fragq_should_evict">inet_fragq_should_evict</a>(const struct <a href="ident?i=inet_frag_queue">inet_frag_queue</a> *q)
<a name="L121" href="source/net/ipv4/inet_fragment.c#L121">121</a> {
<a name="L122" href="source/net/ipv4/inet_fragment.c#L122">122</a>         return q-&gt;<a href="ident?i=net">net</a>-&gt;low_thresh == 0 ||
<a name="L123" href="source/net/ipv4/inet_fragment.c#L123">123</a>                <a href="ident?i=frag_mem_limit">frag_mem_limit</a>(q-&gt;<a href="ident?i=net">net</a>) &gt;= q-&gt;<a href="ident?i=net">net</a>-&gt;low_thresh;
<a name="L124" href="source/net/ipv4/inet_fragment.c#L124">124</a> }
<a name="L125" href="source/net/ipv4/inet_fragment.c#L125">125</a> 
<a name="L126" href="source/net/ipv4/inet_fragment.c#L126">126</a> static unsigned int
<a name="L127" href="source/net/ipv4/inet_fragment.c#L127">127</a> <a href="ident?i=inet_evict_bucket">inet_evict_bucket</a>(struct <a href="ident?i=inet_frags">inet_frags</a> *<a href="ident?i=f">f</a>, struct <a href="ident?i=inet_frag_bucket">inet_frag_bucket</a> *hb)
<a name="L128" href="source/net/ipv4/inet_fragment.c#L128">128</a> {
<a name="L129" href="source/net/ipv4/inet_fragment.c#L129">129</a>         struct <a href="ident?i=inet_frag_queue">inet_frag_queue</a> *fq;
<a name="L130" href="source/net/ipv4/inet_fragment.c#L130">130</a>         struct <a href="ident?i=hlist_node">hlist_node</a> *<a href="ident?i=n">n</a>;
<a name="L131" href="source/net/ipv4/inet_fragment.c#L131">131</a>         unsigned int evicted = 0;
<a name="L132" href="source/net/ipv4/inet_fragment.c#L132">132</a>         <a href="ident?i=HLIST_HEAD">HLIST_HEAD</a>(<a href="ident?i=expired">expired</a>);
<a name="L133" href="source/net/ipv4/inet_fragment.c#L133">133</a> 
<a name="L134" href="source/net/ipv4/inet_fragment.c#L134">134</a> evict_again:
<a name="L135" href="source/net/ipv4/inet_fragment.c#L135">135</a>         <a href="ident?i=spin_lock">spin_lock</a>(&amp;hb-&gt;chain_lock);
<a name="L136" href="source/net/ipv4/inet_fragment.c#L136">136</a> 
<a name="L137" href="source/net/ipv4/inet_fragment.c#L137">137</a>         <a href="ident?i=hlist_for_each_entry_safe">hlist_for_each_entry_safe</a>(fq, <a href="ident?i=n">n</a>, &amp;hb-&gt;<a href="ident?i=chain">chain</a>, <a href="ident?i=list">list</a>) {
<a name="L138" href="source/net/ipv4/inet_fragment.c#L138">138</a>                 if (!<a href="ident?i=inet_fragq_should_evict">inet_fragq_should_evict</a>(fq))
<a name="L139" href="source/net/ipv4/inet_fragment.c#L139">139</a>                         continue;
<a name="L140" href="source/net/ipv4/inet_fragment.c#L140">140</a> 
<a name="L141" href="source/net/ipv4/inet_fragment.c#L141">141</a>                 if (!<a href="ident?i=del_timer">del_timer</a>(&amp;fq-&gt;<a href="ident?i=timer">timer</a>)) {
<a name="L142" href="source/net/ipv4/inet_fragment.c#L142">142</a>                         <b><i>/* q expiring right now thus increment its refcount so</i></b>
<a name="L143" href="source/net/ipv4/inet_fragment.c#L143">143</a> <b><i>                         * it won't be freed under us and wait until the timer</i></b>
<a name="L144" href="source/net/ipv4/inet_fragment.c#L144">144</a> <b><i>                         * has finished executing then destroy it</i></b>
<a name="L145" href="source/net/ipv4/inet_fragment.c#L145">145</a> <b><i>                         */</i></b>
<a name="L146" href="source/net/ipv4/inet_fragment.c#L146">146</a>                         <a href="ident?i=atomic_inc">atomic_inc</a>(&amp;fq-&gt;refcnt);
<a name="L147" href="source/net/ipv4/inet_fragment.c#L147">147</a>                         <a href="ident?i=spin_unlock">spin_unlock</a>(&amp;hb-&gt;chain_lock);
<a name="L148" href="source/net/ipv4/inet_fragment.c#L148">148</a>                         <a href="ident?i=del_timer_sync">del_timer_sync</a>(&amp;fq-&gt;<a href="ident?i=timer">timer</a>);
<a name="L149" href="source/net/ipv4/inet_fragment.c#L149">149</a>                         <a href="ident?i=inet_frag_put">inet_frag_put</a>(fq, <a href="ident?i=f">f</a>);
<a name="L150" href="source/net/ipv4/inet_fragment.c#L150">150</a>                         goto evict_again;
<a name="L151" href="source/net/ipv4/inet_fragment.c#L151">151</a>                 }
<a name="L152" href="source/net/ipv4/inet_fragment.c#L152">152</a> 
<a name="L153" href="source/net/ipv4/inet_fragment.c#L153">153</a>                 fq-&gt;<a href="ident?i=flags">flags</a> |= INET_FRAG_EVICTED;
<a name="L154" href="source/net/ipv4/inet_fragment.c#L154">154</a>                 <a href="ident?i=hlist_del">hlist_del</a>(&amp;fq-&gt;<a href="ident?i=list">list</a>);
<a name="L155" href="source/net/ipv4/inet_fragment.c#L155">155</a>                 <a href="ident?i=hlist_add_head">hlist_add_head</a>(&amp;fq-&gt;<a href="ident?i=list">list</a>, &amp;<a href="ident?i=expired">expired</a>);
<a name="L156" href="source/net/ipv4/inet_fragment.c#L156">156</a>                 ++evicted;
<a name="L157" href="source/net/ipv4/inet_fragment.c#L157">157</a>         }
<a name="L158" href="source/net/ipv4/inet_fragment.c#L158">158</a> 
<a name="L159" href="source/net/ipv4/inet_fragment.c#L159">159</a>         <a href="ident?i=spin_unlock">spin_unlock</a>(&amp;hb-&gt;chain_lock);
<a name="L160" href="source/net/ipv4/inet_fragment.c#L160">160</a> 
<a name="L161" href="source/net/ipv4/inet_fragment.c#L161">161</a>         <a href="ident?i=hlist_for_each_entry_safe">hlist_for_each_entry_safe</a>(fq, <a href="ident?i=n">n</a>, &amp;<a href="ident?i=expired">expired</a>, <a href="ident?i=list">list</a>)
<a name="L162" href="source/net/ipv4/inet_fragment.c#L162">162</a>                 <a href="ident?i=f">f</a>-&gt;frag_expire((unsigned long) fq);
<a name="L163" href="source/net/ipv4/inet_fragment.c#L163">163</a> 
<a name="L164" href="source/net/ipv4/inet_fragment.c#L164">164</a>         return evicted;
<a name="L165" href="source/net/ipv4/inet_fragment.c#L165">165</a> }
<a name="L166" href="source/net/ipv4/inet_fragment.c#L166">166</a> 
<a name="L167" href="source/net/ipv4/inet_fragment.c#L167">167</a> static void <a href="ident?i=inet_frag_worker">inet_frag_worker</a>(struct <a href="ident?i=work_struct">work_struct</a> *<a href="ident?i=work">work</a>)
<a name="L168" href="source/net/ipv4/inet_fragment.c#L168">168</a> {
<a name="L169" href="source/net/ipv4/inet_fragment.c#L169">169</a>         unsigned int <a href="ident?i=budget">budget</a> = <a href="ident?i=INETFRAGS_EVICT_BUCKETS">INETFRAGS_EVICT_BUCKETS</a>;
<a name="L170" href="source/net/ipv4/inet_fragment.c#L170">170</a>         unsigned int <a href="ident?i=i">i</a>, evicted = 0;
<a name="L171" href="source/net/ipv4/inet_fragment.c#L171">171</a>         struct <a href="ident?i=inet_frags">inet_frags</a> *<a href="ident?i=f">f</a>;
<a name="L172" href="source/net/ipv4/inet_fragment.c#L172">172</a> 
<a name="L173" href="source/net/ipv4/inet_fragment.c#L173">173</a>         <a href="ident?i=f">f</a> = <a href="ident?i=container_of">container_of</a>(<a href="ident?i=work">work</a>, struct <a href="ident?i=inet_frags">inet_frags</a>, frags_work);
<a name="L174" href="source/net/ipv4/inet_fragment.c#L174">174</a> 
<a name="L175" href="source/net/ipv4/inet_fragment.c#L175">175</a>         <a href="ident?i=BUILD_BUG_ON">BUILD_BUG_ON</a>(<a href="ident?i=INETFRAGS_EVICT_BUCKETS">INETFRAGS_EVICT_BUCKETS</a> &gt;= <a href="ident?i=INETFRAGS_HASHSZ">INETFRAGS_HASHSZ</a>);
<a name="L176" href="source/net/ipv4/inet_fragment.c#L176">176</a> 
<a name="L177" href="source/net/ipv4/inet_fragment.c#L177">177</a>         <a href="ident?i=local_bh_disable">local_bh_disable</a>();
<a name="L178" href="source/net/ipv4/inet_fragment.c#L178">178</a> 
<a name="L179" href="source/net/ipv4/inet_fragment.c#L179">179</a>         for (<a href="ident?i=i">i</a> = <a href="ident?i=ACCESS_ONCE">ACCESS_ONCE</a>(<a href="ident?i=f">f</a>-&gt;next_bucket); <a href="ident?i=budget">budget</a>; --<a href="ident?i=budget">budget</a>) {
<a name="L180" href="source/net/ipv4/inet_fragment.c#L180">180</a>                 evicted += <a href="ident?i=inet_evict_bucket">inet_evict_bucket</a>(<a href="ident?i=f">f</a>, &amp;<a href="ident?i=f">f</a>-&gt;<a href="ident?i=hash">hash</a>[<a href="ident?i=i">i</a>]);
<a name="L181" href="source/net/ipv4/inet_fragment.c#L181">181</a>                 <a href="ident?i=i">i</a> = (<a href="ident?i=i">i</a> + 1) &amp; (<a href="ident?i=INETFRAGS_HASHSZ">INETFRAGS_HASHSZ</a> - 1);
<a name="L182" href="source/net/ipv4/inet_fragment.c#L182">182</a>                 if (evicted &gt; <a href="ident?i=INETFRAGS_EVICT_MAX">INETFRAGS_EVICT_MAX</a>)
<a name="L183" href="source/net/ipv4/inet_fragment.c#L183">183</a>                         break;
<a name="L184" href="source/net/ipv4/inet_fragment.c#L184">184</a>         }
<a name="L185" href="source/net/ipv4/inet_fragment.c#L185">185</a> 
<a name="L186" href="source/net/ipv4/inet_fragment.c#L186">186</a>         <a href="ident?i=f">f</a>-&gt;next_bucket = <a href="ident?i=i">i</a>;
<a name="L187" href="source/net/ipv4/inet_fragment.c#L187">187</a> 
<a name="L188" href="source/net/ipv4/inet_fragment.c#L188">188</a>         <a href="ident?i=local_bh_enable">local_bh_enable</a>();
<a name="L189" href="source/net/ipv4/inet_fragment.c#L189">189</a> 
<a name="L190" href="source/net/ipv4/inet_fragment.c#L190">190</a>         if (<a href="ident?i=f">f</a>-&gt;rebuild &amp;&amp; <a href="ident?i=inet_frag_may_rebuild">inet_frag_may_rebuild</a>(<a href="ident?i=f">f</a>))
<a name="L191" href="source/net/ipv4/inet_fragment.c#L191">191</a>                 <a href="ident?i=inet_frag_secret_rebuild">inet_frag_secret_rebuild</a>(<a href="ident?i=f">f</a>);
<a name="L192" href="source/net/ipv4/inet_fragment.c#L192">192</a> }
<a name="L193" href="source/net/ipv4/inet_fragment.c#L193">193</a> 
<a name="L194" href="source/net/ipv4/inet_fragment.c#L194">194</a> static void <a href="ident?i=inet_frag_schedule_worker">inet_frag_schedule_worker</a>(struct <a href="ident?i=inet_frags">inet_frags</a> *<a href="ident?i=f">f</a>)
<a name="L195" href="source/net/ipv4/inet_fragment.c#L195">195</a> {
<a name="L196" href="source/net/ipv4/inet_fragment.c#L196">196</a>         if (<a href="ident?i=unlikely">unlikely</a>(!<a href="ident?i=work_pending">work_pending</a>(&amp;<a href="ident?i=f">f</a>-&gt;frags_work)))
<a name="L197" href="source/net/ipv4/inet_fragment.c#L197">197</a>                 <a href="ident?i=schedule_work">schedule_work</a>(&amp;<a href="ident?i=f">f</a>-&gt;frags_work);
<a name="L198" href="source/net/ipv4/inet_fragment.c#L198">198</a> }
<a name="L199" href="source/net/ipv4/inet_fragment.c#L199">199</a> 
<a name="L200" href="source/net/ipv4/inet_fragment.c#L200">200</a> int <a href="ident?i=inet_frags_init">inet_frags_init</a>(struct <a href="ident?i=inet_frags">inet_frags</a> *<a href="ident?i=f">f</a>)
<a name="L201" href="source/net/ipv4/inet_fragment.c#L201">201</a> {
<a name="L202" href="source/net/ipv4/inet_fragment.c#L202">202</a>         int <a href="ident?i=i">i</a>;
<a name="L203" href="source/net/ipv4/inet_fragment.c#L203">203</a> 
<a name="L204" href="source/net/ipv4/inet_fragment.c#L204">204</a>         <a href="ident?i=INIT_WORK">INIT_WORK</a>(&amp;<a href="ident?i=f">f</a>-&gt;frags_work, <a href="ident?i=inet_frag_worker">inet_frag_worker</a>);
<a name="L205" href="source/net/ipv4/inet_fragment.c#L205">205</a> 
<a name="L206" href="source/net/ipv4/inet_fragment.c#L206">206</a>         for (<a href="ident?i=i">i</a> = 0; <a href="ident?i=i">i</a> &lt; <a href="ident?i=INETFRAGS_HASHSZ">INETFRAGS_HASHSZ</a>; <a href="ident?i=i">i</a>++) {
<a name="L207" href="source/net/ipv4/inet_fragment.c#L207">207</a>                 struct <a href="ident?i=inet_frag_bucket">inet_frag_bucket</a> *hb = &amp;<a href="ident?i=f">f</a>-&gt;<a href="ident?i=hash">hash</a>[<a href="ident?i=i">i</a>];
<a name="L208" href="source/net/ipv4/inet_fragment.c#L208">208</a> 
<a name="L209" href="source/net/ipv4/inet_fragment.c#L209">209</a>                 <a href="ident?i=spin_lock_init">spin_lock_init</a>(&amp;hb-&gt;chain_lock);
<a name="L210" href="source/net/ipv4/inet_fragment.c#L210">210</a>                 <a href="ident?i=INIT_HLIST_HEAD">INIT_HLIST_HEAD</a>(&amp;hb-&gt;<a href="ident?i=chain">chain</a>);
<a name="L211" href="source/net/ipv4/inet_fragment.c#L211">211</a>         }
<a name="L212" href="source/net/ipv4/inet_fragment.c#L212">212</a> 
<a name="L213" href="source/net/ipv4/inet_fragment.c#L213">213</a>         <a href="ident?i=seqlock_init">seqlock_init</a>(&amp;<a href="ident?i=f">f</a>-&gt;rnd_seqlock);
<a name="L214" href="source/net/ipv4/inet_fragment.c#L214">214</a>         <a href="ident?i=f">f</a>-&gt;last_rebuild_jiffies = 0;
<a name="L215" href="source/net/ipv4/inet_fragment.c#L215">215</a>         <a href="ident?i=f">f</a>-&gt;frags_cachep = <a href="ident?i=kmem_cache_create">kmem_cache_create</a>(<a href="ident?i=f">f</a>-&gt;frags_cache_name, <a href="ident?i=f">f</a>-&gt;qsize, 0, 0,
<a name="L216" href="source/net/ipv4/inet_fragment.c#L216">216</a>                                             <a href="ident?i=NULL">NULL</a>);
<a name="L217" href="source/net/ipv4/inet_fragment.c#L217">217</a>         if (!<a href="ident?i=f">f</a>-&gt;frags_cachep)
<a name="L218" href="source/net/ipv4/inet_fragment.c#L218">218</a>                 return -<a href="ident?i=ENOMEM">ENOMEM</a>;
<a name="L219" href="source/net/ipv4/inet_fragment.c#L219">219</a> 
<a name="L220" href="source/net/ipv4/inet_fragment.c#L220">220</a>         return 0;
<a name="L221" href="source/net/ipv4/inet_fragment.c#L221">221</a> }
<a name="L222" href="source/net/ipv4/inet_fragment.c#L222">222</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=inet_frags_init">inet_frags_init</a>);
<a name="L223" href="source/net/ipv4/inet_fragment.c#L223">223</a> 
<a name="L224" href="source/net/ipv4/inet_fragment.c#L224">224</a> void <a href="ident?i=inet_frags_init_net">inet_frags_init_net</a>(struct <a href="ident?i=netns_frags">netns_frags</a> *nf)
<a name="L225" href="source/net/ipv4/inet_fragment.c#L225">225</a> {
<a name="L226" href="source/net/ipv4/inet_fragment.c#L226">226</a>         <a href="ident?i=init_frag_mem_limit">init_frag_mem_limit</a>(nf);
<a name="L227" href="source/net/ipv4/inet_fragment.c#L227">227</a> }
<a name="L228" href="source/net/ipv4/inet_fragment.c#L228">228</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=inet_frags_init_net">inet_frags_init_net</a>);
<a name="L229" href="source/net/ipv4/inet_fragment.c#L229">229</a> 
<a name="L230" href="source/net/ipv4/inet_fragment.c#L230">230</a> void <a href="ident?i=inet_frags_fini">inet_frags_fini</a>(struct <a href="ident?i=inet_frags">inet_frags</a> *<a href="ident?i=f">f</a>)
<a name="L231" href="source/net/ipv4/inet_fragment.c#L231">231</a> {
<a name="L232" href="source/net/ipv4/inet_fragment.c#L232">232</a>         <a href="ident?i=cancel_work_sync">cancel_work_sync</a>(&amp;<a href="ident?i=f">f</a>-&gt;frags_work);
<a name="L233" href="source/net/ipv4/inet_fragment.c#L233">233</a>         <a href="ident?i=kmem_cache_destroy">kmem_cache_destroy</a>(<a href="ident?i=f">f</a>-&gt;frags_cachep);
<a name="L234" href="source/net/ipv4/inet_fragment.c#L234">234</a> }
<a name="L235" href="source/net/ipv4/inet_fragment.c#L235">235</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=inet_frags_fini">inet_frags_fini</a>);
<a name="L236" href="source/net/ipv4/inet_fragment.c#L236">236</a> 
<a name="L237" href="source/net/ipv4/inet_fragment.c#L237">237</a> void <a href="ident?i=inet_frags_exit_net">inet_frags_exit_net</a>(struct <a href="ident?i=netns_frags">netns_frags</a> *nf, struct <a href="ident?i=inet_frags">inet_frags</a> *<a href="ident?i=f">f</a>)
<a name="L238" href="source/net/ipv4/inet_fragment.c#L238">238</a> {
<a name="L239" href="source/net/ipv4/inet_fragment.c#L239">239</a>         unsigned int <a href="ident?i=seq">seq</a>;
<a name="L240" href="source/net/ipv4/inet_fragment.c#L240">240</a>         int <a href="ident?i=i">i</a>;
<a name="L241" href="source/net/ipv4/inet_fragment.c#L241">241</a> 
<a name="L242" href="source/net/ipv4/inet_fragment.c#L242">242</a>         nf-&gt;low_thresh = 0;
<a name="L243" href="source/net/ipv4/inet_fragment.c#L243">243</a>         <a href="ident?i=local_bh_disable">local_bh_disable</a>();
<a name="L244" href="source/net/ipv4/inet_fragment.c#L244">244</a> 
<a name="L245" href="source/net/ipv4/inet_fragment.c#L245">245</a> evict_again:
<a name="L246" href="source/net/ipv4/inet_fragment.c#L246">246</a>         <a href="ident?i=seq">seq</a> = <a href="ident?i=read_seqbegin">read_seqbegin</a>(&amp;<a href="ident?i=f">f</a>-&gt;rnd_seqlock);
<a name="L247" href="source/net/ipv4/inet_fragment.c#L247">247</a> 
<a name="L248" href="source/net/ipv4/inet_fragment.c#L248">248</a>         for (<a href="ident?i=i">i</a> = 0; <a href="ident?i=i">i</a> &lt; <a href="ident?i=INETFRAGS_HASHSZ">INETFRAGS_HASHSZ</a> ; <a href="ident?i=i">i</a>++)
<a name="L249" href="source/net/ipv4/inet_fragment.c#L249">249</a>                 <a href="ident?i=inet_evict_bucket">inet_evict_bucket</a>(<a href="ident?i=f">f</a>, &amp;<a href="ident?i=f">f</a>-&gt;<a href="ident?i=hash">hash</a>[<a href="ident?i=i">i</a>]);
<a name="L250" href="source/net/ipv4/inet_fragment.c#L250">250</a> 
<a name="L251" href="source/net/ipv4/inet_fragment.c#L251">251</a>         if (<a href="ident?i=read_seqretry">read_seqretry</a>(&amp;<a href="ident?i=f">f</a>-&gt;rnd_seqlock, <a href="ident?i=seq">seq</a>))
<a name="L252" href="source/net/ipv4/inet_fragment.c#L252">252</a>                 goto evict_again;
<a name="L253" href="source/net/ipv4/inet_fragment.c#L253">253</a> 
<a name="L254" href="source/net/ipv4/inet_fragment.c#L254">254</a>         <a href="ident?i=local_bh_enable">local_bh_enable</a>();
<a name="L255" href="source/net/ipv4/inet_fragment.c#L255">255</a> 
<a name="L256" href="source/net/ipv4/inet_fragment.c#L256">256</a>         <a href="ident?i=percpu_counter_destroy">percpu_counter_destroy</a>(&amp;nf-&gt;<a href="ident?i=mem">mem</a>);
<a name="L257" href="source/net/ipv4/inet_fragment.c#L257">257</a> }
<a name="L258" href="source/net/ipv4/inet_fragment.c#L258">258</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=inet_frags_exit_net">inet_frags_exit_net</a>);
<a name="L259" href="source/net/ipv4/inet_fragment.c#L259">259</a> 
<a name="L260" href="source/net/ipv4/inet_fragment.c#L260">260</a> static struct <a href="ident?i=inet_frag_bucket">inet_frag_bucket</a> *
<a name="L261" href="source/net/ipv4/inet_fragment.c#L261">261</a> get_frag_bucket_locked(struct <a href="ident?i=inet_frag_queue">inet_frag_queue</a> *fq, struct <a href="ident?i=inet_frags">inet_frags</a> *<a href="ident?i=f">f</a>)
<a name="L262" href="source/net/ipv4/inet_fragment.c#L262">262</a> <a href="ident?i=__acquires">__acquires</a>(hb-&gt;chain_lock)
<a name="L263" href="source/net/ipv4/inet_fragment.c#L263">263</a> {
<a name="L264" href="source/net/ipv4/inet_fragment.c#L264">264</a>         struct <a href="ident?i=inet_frag_bucket">inet_frag_bucket</a> *hb;
<a name="L265" href="source/net/ipv4/inet_fragment.c#L265">265</a>         unsigned int <a href="ident?i=seq">seq</a>, <a href="ident?i=hash">hash</a>;
<a name="L266" href="source/net/ipv4/inet_fragment.c#L266">266</a> 
<a name="L267" href="source/net/ipv4/inet_fragment.c#L267">267</a>  <a href="ident?i=restart">restart</a>:
<a name="L268" href="source/net/ipv4/inet_fragment.c#L268">268</a>         <a href="ident?i=seq">seq</a> = <a href="ident?i=read_seqbegin">read_seqbegin</a>(&amp;<a href="ident?i=f">f</a>-&gt;rnd_seqlock);
<a name="L269" href="source/net/ipv4/inet_fragment.c#L269">269</a> 
<a name="L270" href="source/net/ipv4/inet_fragment.c#L270">270</a>         <a href="ident?i=hash">hash</a> = <a href="ident?i=inet_frag_hashfn">inet_frag_hashfn</a>(<a href="ident?i=f">f</a>, fq);
<a name="L271" href="source/net/ipv4/inet_fragment.c#L271">271</a>         hb = &amp;<a href="ident?i=f">f</a>-&gt;<a href="ident?i=hash">hash</a>[<a href="ident?i=hash">hash</a>];
<a name="L272" href="source/net/ipv4/inet_fragment.c#L272">272</a> 
<a name="L273" href="source/net/ipv4/inet_fragment.c#L273">273</a>         <a href="ident?i=spin_lock">spin_lock</a>(&amp;hb-&gt;chain_lock);
<a name="L274" href="source/net/ipv4/inet_fragment.c#L274">274</a>         if (<a href="ident?i=read_seqretry">read_seqretry</a>(&amp;<a href="ident?i=f">f</a>-&gt;rnd_seqlock, <a href="ident?i=seq">seq</a>)) {
<a name="L275" href="source/net/ipv4/inet_fragment.c#L275">275</a>                 <a href="ident?i=spin_unlock">spin_unlock</a>(&amp;hb-&gt;chain_lock);
<a name="L276" href="source/net/ipv4/inet_fragment.c#L276">276</a>                 goto <a href="ident?i=restart">restart</a>;
<a name="L277" href="source/net/ipv4/inet_fragment.c#L277">277</a>         }
<a name="L278" href="source/net/ipv4/inet_fragment.c#L278">278</a> 
<a name="L279" href="source/net/ipv4/inet_fragment.c#L279">279</a>         return hb;
<a name="L280" href="source/net/ipv4/inet_fragment.c#L280">280</a> }
<a name="L281" href="source/net/ipv4/inet_fragment.c#L281">281</a> 
<a name="L282" href="source/net/ipv4/inet_fragment.c#L282">282</a> static inline void <a href="ident?i=fq_unlink">fq_unlink</a>(struct <a href="ident?i=inet_frag_queue">inet_frag_queue</a> *fq, struct <a href="ident?i=inet_frags">inet_frags</a> *<a href="ident?i=f">f</a>)
<a name="L283" href="source/net/ipv4/inet_fragment.c#L283">283</a> {
<a name="L284" href="source/net/ipv4/inet_fragment.c#L284">284</a>         struct <a href="ident?i=inet_frag_bucket">inet_frag_bucket</a> *hb;
<a name="L285" href="source/net/ipv4/inet_fragment.c#L285">285</a> 
<a name="L286" href="source/net/ipv4/inet_fragment.c#L286">286</a>         hb = get_frag_bucket_locked(fq, <a href="ident?i=f">f</a>);
<a name="L287" href="source/net/ipv4/inet_fragment.c#L287">287</a>         if (!(fq-&gt;<a href="ident?i=flags">flags</a> &amp; INET_FRAG_EVICTED))
<a name="L288" href="source/net/ipv4/inet_fragment.c#L288">288</a>                 <a href="ident?i=hlist_del">hlist_del</a>(&amp;fq-&gt;<a href="ident?i=list">list</a>);
<a name="L289" href="source/net/ipv4/inet_fragment.c#L289">289</a>         <a href="ident?i=spin_unlock">spin_unlock</a>(&amp;hb-&gt;chain_lock);
<a name="L290" href="source/net/ipv4/inet_fragment.c#L290">290</a> }
<a name="L291" href="source/net/ipv4/inet_fragment.c#L291">291</a> 
<a name="L292" href="source/net/ipv4/inet_fragment.c#L292">292</a> void <a href="ident?i=inet_frag_kill">inet_frag_kill</a>(struct <a href="ident?i=inet_frag_queue">inet_frag_queue</a> *fq, struct <a href="ident?i=inet_frags">inet_frags</a> *<a href="ident?i=f">f</a>)
<a name="L293" href="source/net/ipv4/inet_fragment.c#L293">293</a> {
<a name="L294" href="source/net/ipv4/inet_fragment.c#L294">294</a>         if (<a href="ident?i=del_timer">del_timer</a>(&amp;fq-&gt;<a href="ident?i=timer">timer</a>))
<a name="L295" href="source/net/ipv4/inet_fragment.c#L295">295</a>                 <a href="ident?i=atomic_dec">atomic_dec</a>(&amp;fq-&gt;refcnt);
<a name="L296" href="source/net/ipv4/inet_fragment.c#L296">296</a> 
<a name="L297" href="source/net/ipv4/inet_fragment.c#L297">297</a>         if (!(fq-&gt;<a href="ident?i=flags">flags</a> &amp; INET_FRAG_COMPLETE)) {
<a name="L298" href="source/net/ipv4/inet_fragment.c#L298">298</a>                 <a href="ident?i=fq_unlink">fq_unlink</a>(fq, <a href="ident?i=f">f</a>);
<a name="L299" href="source/net/ipv4/inet_fragment.c#L299">299</a>                 <a href="ident?i=atomic_dec">atomic_dec</a>(&amp;fq-&gt;refcnt);
<a name="L300" href="source/net/ipv4/inet_fragment.c#L300">300</a>                 fq-&gt;<a href="ident?i=flags">flags</a> |= INET_FRAG_COMPLETE;
<a name="L301" href="source/net/ipv4/inet_fragment.c#L301">301</a>         }
<a name="L302" href="source/net/ipv4/inet_fragment.c#L302">302</a> }
<a name="L303" href="source/net/ipv4/inet_fragment.c#L303">303</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=inet_frag_kill">inet_frag_kill</a>);
<a name="L304" href="source/net/ipv4/inet_fragment.c#L304">304</a> 
<a name="L305" href="source/net/ipv4/inet_fragment.c#L305">305</a> static inline void <a href="ident?i=frag_kfree_skb">frag_kfree_skb</a>(struct <a href="ident?i=netns_frags">netns_frags</a> *nf, struct <a href="ident?i=inet_frags">inet_frags</a> *<a href="ident?i=f">f</a>,
<a name="L306" href="source/net/ipv4/inet_fragment.c#L306">306</a>                                   struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L307" href="source/net/ipv4/inet_fragment.c#L307">307</a> {
<a name="L308" href="source/net/ipv4/inet_fragment.c#L308">308</a>         if (<a href="ident?i=f">f</a>-&gt;skb_free)
<a name="L309" href="source/net/ipv4/inet_fragment.c#L309">309</a>                 <a href="ident?i=f">f</a>-&gt;skb_free(<a href="ident?i=skb">skb</a>);
<a name="L310" href="source/net/ipv4/inet_fragment.c#L310">310</a>         <a href="ident?i=kfree_skb">kfree_skb</a>(<a href="ident?i=skb">skb</a>);
<a name="L311" href="source/net/ipv4/inet_fragment.c#L311">311</a> }
<a name="L312" href="source/net/ipv4/inet_fragment.c#L312">312</a> 
<a name="L313" href="source/net/ipv4/inet_fragment.c#L313">313</a> void <a href="ident?i=inet_frag_destroy">inet_frag_destroy</a>(struct <a href="ident?i=inet_frag_queue">inet_frag_queue</a> *q, struct <a href="ident?i=inet_frags">inet_frags</a> *<a href="ident?i=f">f</a>)
<a name="L314" href="source/net/ipv4/inet_fragment.c#L314">314</a> {
<a name="L315" href="source/net/ipv4/inet_fragment.c#L315">315</a>         struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=fp">fp</a>;
<a name="L316" href="source/net/ipv4/inet_fragment.c#L316">316</a>         struct <a href="ident?i=netns_frags">netns_frags</a> *nf;
<a name="L317" href="source/net/ipv4/inet_fragment.c#L317">317</a>         unsigned int <a href="ident?i=sum">sum</a>, sum_truesize = 0;
<a name="L318" href="source/net/ipv4/inet_fragment.c#L318">318</a> 
<a name="L319" href="source/net/ipv4/inet_fragment.c#L319">319</a>         <a href="ident?i=WARN_ON">WARN_ON</a>(!(q-&gt;<a href="ident?i=flags">flags</a> &amp; INET_FRAG_COMPLETE));
<a name="L320" href="source/net/ipv4/inet_fragment.c#L320">320</a>         <a href="ident?i=WARN_ON">WARN_ON</a>(<a href="ident?i=del_timer">del_timer</a>(&amp;q-&gt;<a href="ident?i=timer">timer</a>) != 0);
<a name="L321" href="source/net/ipv4/inet_fragment.c#L321">321</a> 
<a name="L322" href="source/net/ipv4/inet_fragment.c#L322">322</a>         <b><i>/* Release all fragment data. */</i></b>
<a name="L323" href="source/net/ipv4/inet_fragment.c#L323">323</a>         <a href="ident?i=fp">fp</a> = q-&gt;fragments;
<a name="L324" href="source/net/ipv4/inet_fragment.c#L324">324</a>         nf = q-&gt;<a href="ident?i=net">net</a>;
<a name="L325" href="source/net/ipv4/inet_fragment.c#L325">325</a>         while (<a href="ident?i=fp">fp</a>) {
<a name="L326" href="source/net/ipv4/inet_fragment.c#L326">326</a>                 struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=xp">xp</a> = <a href="ident?i=fp">fp</a>-&gt;<a href="ident?i=next">next</a>;
<a name="L327" href="source/net/ipv4/inet_fragment.c#L327">327</a> 
<a name="L328" href="source/net/ipv4/inet_fragment.c#L328">328</a>                 sum_truesize += <a href="ident?i=fp">fp</a>-&gt;truesize;
<a name="L329" href="source/net/ipv4/inet_fragment.c#L329">329</a>                 <a href="ident?i=frag_kfree_skb">frag_kfree_skb</a>(nf, <a href="ident?i=f">f</a>, <a href="ident?i=fp">fp</a>);
<a name="L330" href="source/net/ipv4/inet_fragment.c#L330">330</a>                 <a href="ident?i=fp">fp</a> = <a href="ident?i=xp">xp</a>;
<a name="L331" href="source/net/ipv4/inet_fragment.c#L331">331</a>         }
<a name="L332" href="source/net/ipv4/inet_fragment.c#L332">332</a>         <a href="ident?i=sum">sum</a> = sum_truesize + <a href="ident?i=f">f</a>-&gt;qsize;
<a name="L333" href="source/net/ipv4/inet_fragment.c#L333">333</a>         <a href="ident?i=sub_frag_mem_limit">sub_frag_mem_limit</a>(q, <a href="ident?i=sum">sum</a>);
<a name="L334" href="source/net/ipv4/inet_fragment.c#L334">334</a> 
<a name="L335" href="source/net/ipv4/inet_fragment.c#L335">335</a>         if (<a href="ident?i=f">f</a>-&gt;destructor)
<a name="L336" href="source/net/ipv4/inet_fragment.c#L336">336</a>                 <a href="ident?i=f">f</a>-&gt;destructor(q);
<a name="L337" href="source/net/ipv4/inet_fragment.c#L337">337</a>         <a href="ident?i=kmem_cache_free">kmem_cache_free</a>(<a href="ident?i=f">f</a>-&gt;frags_cachep, q);
<a name="L338" href="source/net/ipv4/inet_fragment.c#L338">338</a> }
<a name="L339" href="source/net/ipv4/inet_fragment.c#L339">339</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=inet_frag_destroy">inet_frag_destroy</a>);
<a name="L340" href="source/net/ipv4/inet_fragment.c#L340">340</a> 
<a name="L341" href="source/net/ipv4/inet_fragment.c#L341">341</a> static struct <a href="ident?i=inet_frag_queue">inet_frag_queue</a> *<a href="ident?i=inet_frag_intern">inet_frag_intern</a>(struct <a href="ident?i=netns_frags">netns_frags</a> *nf,
<a name="L342" href="source/net/ipv4/inet_fragment.c#L342">342</a>                                                 struct <a href="ident?i=inet_frag_queue">inet_frag_queue</a> *qp_in,
<a name="L343" href="source/net/ipv4/inet_fragment.c#L343">343</a>                                                 struct <a href="ident?i=inet_frags">inet_frags</a> *<a href="ident?i=f">f</a>,
<a name="L344" href="source/net/ipv4/inet_fragment.c#L344">344</a>                                                 void *<a href="ident?i=arg">arg</a>)
<a name="L345" href="source/net/ipv4/inet_fragment.c#L345">345</a> {
<a name="L346" href="source/net/ipv4/inet_fragment.c#L346">346</a>         struct <a href="ident?i=inet_frag_bucket">inet_frag_bucket</a> *hb = get_frag_bucket_locked(qp_in, <a href="ident?i=f">f</a>);
<a name="L347" href="source/net/ipv4/inet_fragment.c#L347">347</a>         struct <a href="ident?i=inet_frag_queue">inet_frag_queue</a> *<a href="ident?i=qp">qp</a>;
<a name="L348" href="source/net/ipv4/inet_fragment.c#L348">348</a> 
<a name="L349" href="source/net/ipv4/inet_fragment.c#L349">349</a> #ifdef <a href="ident?i=CONFIG_SMP">CONFIG_SMP</a>
<a name="L350" href="source/net/ipv4/inet_fragment.c#L350">350</a>         <b><i>/* With SMP race we have to recheck hash table, because</i></b>
<a name="L351" href="source/net/ipv4/inet_fragment.c#L351">351</a> <b><i>         * such entry could have been created on other cpu before</i></b>
<a name="L352" href="source/net/ipv4/inet_fragment.c#L352">352</a> <b><i>         * we acquired hash bucket lock.</i></b>
<a name="L353" href="source/net/ipv4/inet_fragment.c#L353">353</a> <b><i>         */</i></b>
<a name="L354" href="source/net/ipv4/inet_fragment.c#L354">354</a>         <a href="ident?i=hlist_for_each_entry">hlist_for_each_entry</a>(<a href="ident?i=qp">qp</a>, &amp;hb-&gt;<a href="ident?i=chain">chain</a>, <a href="ident?i=list">list</a>) {
<a name="L355" href="source/net/ipv4/inet_fragment.c#L355">355</a>                 if (<a href="ident?i=qp">qp</a>-&gt;<a href="ident?i=net">net</a> == nf &amp;&amp; <a href="ident?i=f">f</a>-&gt;<a href="ident?i=match">match</a>(<a href="ident?i=qp">qp</a>, <a href="ident?i=arg">arg</a>)) {
<a name="L356" href="source/net/ipv4/inet_fragment.c#L356">356</a>                         <a href="ident?i=atomic_inc">atomic_inc</a>(&amp;<a href="ident?i=qp">qp</a>-&gt;refcnt);
<a name="L357" href="source/net/ipv4/inet_fragment.c#L357">357</a>                         <a href="ident?i=spin_unlock">spin_unlock</a>(&amp;hb-&gt;chain_lock);
<a name="L358" href="source/net/ipv4/inet_fragment.c#L358">358</a>                         qp_in-&gt;<a href="ident?i=flags">flags</a> |= INET_FRAG_COMPLETE;
<a name="L359" href="source/net/ipv4/inet_fragment.c#L359">359</a>                         <a href="ident?i=inet_frag_put">inet_frag_put</a>(qp_in, <a href="ident?i=f">f</a>);
<a name="L360" href="source/net/ipv4/inet_fragment.c#L360">360</a>                         return <a href="ident?i=qp">qp</a>;
<a name="L361" href="source/net/ipv4/inet_fragment.c#L361">361</a>                 }
<a name="L362" href="source/net/ipv4/inet_fragment.c#L362">362</a>         }
<a name="L363" href="source/net/ipv4/inet_fragment.c#L363">363</a> #endif
<a name="L364" href="source/net/ipv4/inet_fragment.c#L364">364</a>         <a href="ident?i=qp">qp</a> = qp_in;
<a name="L365" href="source/net/ipv4/inet_fragment.c#L365">365</a>         if (!<a href="ident?i=mod_timer">mod_timer</a>(&amp;<a href="ident?i=qp">qp</a>-&gt;<a href="ident?i=timer">timer</a>, <a href="ident?i=jiffies">jiffies</a> + nf-&gt;<a href="ident?i=timeout">timeout</a>))
<a name="L366" href="source/net/ipv4/inet_fragment.c#L366">366</a>                 <a href="ident?i=atomic_inc">atomic_inc</a>(&amp;<a href="ident?i=qp">qp</a>-&gt;refcnt);
<a name="L367" href="source/net/ipv4/inet_fragment.c#L367">367</a> 
<a name="L368" href="source/net/ipv4/inet_fragment.c#L368">368</a>         <a href="ident?i=atomic_inc">atomic_inc</a>(&amp;<a href="ident?i=qp">qp</a>-&gt;refcnt);
<a name="L369" href="source/net/ipv4/inet_fragment.c#L369">369</a>         <a href="ident?i=hlist_add_head">hlist_add_head</a>(&amp;<a href="ident?i=qp">qp</a>-&gt;<a href="ident?i=list">list</a>, &amp;hb-&gt;<a href="ident?i=chain">chain</a>);
<a name="L370" href="source/net/ipv4/inet_fragment.c#L370">370</a> 
<a name="L371" href="source/net/ipv4/inet_fragment.c#L371">371</a>         <a href="ident?i=spin_unlock">spin_unlock</a>(&amp;hb-&gt;chain_lock);
<a name="L372" href="source/net/ipv4/inet_fragment.c#L372">372</a> 
<a name="L373" href="source/net/ipv4/inet_fragment.c#L373">373</a>         return <a href="ident?i=qp">qp</a>;
<a name="L374" href="source/net/ipv4/inet_fragment.c#L374">374</a> }
<a name="L375" href="source/net/ipv4/inet_fragment.c#L375">375</a> 
<a name="L376" href="source/net/ipv4/inet_fragment.c#L376">376</a> static struct <a href="ident?i=inet_frag_queue">inet_frag_queue</a> *<a href="ident?i=inet_frag_alloc">inet_frag_alloc</a>(struct <a href="ident?i=netns_frags">netns_frags</a> *nf,
<a name="L377" href="source/net/ipv4/inet_fragment.c#L377">377</a>                                                struct <a href="ident?i=inet_frags">inet_frags</a> *<a href="ident?i=f">f</a>,
<a name="L378" href="source/net/ipv4/inet_fragment.c#L378">378</a>                                                void *<a href="ident?i=arg">arg</a>)
<a name="L379" href="source/net/ipv4/inet_fragment.c#L379">379</a> {
<a name="L380" href="source/net/ipv4/inet_fragment.c#L380">380</a>         struct <a href="ident?i=inet_frag_queue">inet_frag_queue</a> *q;
<a name="L381" href="source/net/ipv4/inet_fragment.c#L381">381</a> 
<a name="L382" href="source/net/ipv4/inet_fragment.c#L382">382</a>         if (<a href="ident?i=frag_mem_limit">frag_mem_limit</a>(nf) &gt; nf-&gt;high_thresh) {
<a name="L383" href="source/net/ipv4/inet_fragment.c#L383">383</a>                 <a href="ident?i=inet_frag_schedule_worker">inet_frag_schedule_worker</a>(<a href="ident?i=f">f</a>);
<a name="L384" href="source/net/ipv4/inet_fragment.c#L384">384</a>                 return <a href="ident?i=NULL">NULL</a>;
<a name="L385" href="source/net/ipv4/inet_fragment.c#L385">385</a>         }
<a name="L386" href="source/net/ipv4/inet_fragment.c#L386">386</a> 
<a name="L387" href="source/net/ipv4/inet_fragment.c#L387">387</a>         q = <a href="ident?i=kmem_cache_zalloc">kmem_cache_zalloc</a>(<a href="ident?i=f">f</a>-&gt;frags_cachep, <a href="ident?i=GFP_ATOMIC">GFP_ATOMIC</a>);
<a name="L388" href="source/net/ipv4/inet_fragment.c#L388">388</a>         if (!q)
<a name="L389" href="source/net/ipv4/inet_fragment.c#L389">389</a>                 return <a href="ident?i=NULL">NULL</a>;
<a name="L390" href="source/net/ipv4/inet_fragment.c#L390">390</a> 
<a name="L391" href="source/net/ipv4/inet_fragment.c#L391">391</a>         q-&gt;<a href="ident?i=net">net</a> = nf;
<a name="L392" href="source/net/ipv4/inet_fragment.c#L392">392</a>         <a href="ident?i=f">f</a>-&gt;constructor(q, <a href="ident?i=arg">arg</a>);
<a name="L393" href="source/net/ipv4/inet_fragment.c#L393">393</a>         <a href="ident?i=add_frag_mem_limit">add_frag_mem_limit</a>(q, <a href="ident?i=f">f</a>-&gt;qsize);
<a name="L394" href="source/net/ipv4/inet_fragment.c#L394">394</a> 
<a name="L395" href="source/net/ipv4/inet_fragment.c#L395">395</a>         <a href="ident?i=setup_timer">setup_timer</a>(&amp;q-&gt;<a href="ident?i=timer">timer</a>, <a href="ident?i=f">f</a>-&gt;frag_expire, (unsigned long)q);
<a name="L396" href="source/net/ipv4/inet_fragment.c#L396">396</a>         <a href="ident?i=spin_lock_init">spin_lock_init</a>(&amp;q-&gt;<a href="ident?i=lock">lock</a>);
<a name="L397" href="source/net/ipv4/inet_fragment.c#L397">397</a>         <a href="ident?i=atomic_set">atomic_set</a>(&amp;q-&gt;refcnt, 1);
<a name="L398" href="source/net/ipv4/inet_fragment.c#L398">398</a> 
<a name="L399" href="source/net/ipv4/inet_fragment.c#L399">399</a>         return q;
<a name="L400" href="source/net/ipv4/inet_fragment.c#L400">400</a> }
<a name="L401" href="source/net/ipv4/inet_fragment.c#L401">401</a> 
<a name="L402" href="source/net/ipv4/inet_fragment.c#L402">402</a> static struct <a href="ident?i=inet_frag_queue">inet_frag_queue</a> *<a href="ident?i=inet_frag_create">inet_frag_create</a>(struct <a href="ident?i=netns_frags">netns_frags</a> *nf,
<a name="L403" href="source/net/ipv4/inet_fragment.c#L403">403</a>                                                 struct <a href="ident?i=inet_frags">inet_frags</a> *<a href="ident?i=f">f</a>,
<a name="L404" href="source/net/ipv4/inet_fragment.c#L404">404</a>                                                 void *<a href="ident?i=arg">arg</a>)
<a name="L405" href="source/net/ipv4/inet_fragment.c#L405">405</a> {
<a name="L406" href="source/net/ipv4/inet_fragment.c#L406">406</a>         struct <a href="ident?i=inet_frag_queue">inet_frag_queue</a> *q;
<a name="L407" href="source/net/ipv4/inet_fragment.c#L407">407</a> 
<a name="L408" href="source/net/ipv4/inet_fragment.c#L408">408</a>         q = <a href="ident?i=inet_frag_alloc">inet_frag_alloc</a>(nf, <a href="ident?i=f">f</a>, <a href="ident?i=arg">arg</a>);
<a name="L409" href="source/net/ipv4/inet_fragment.c#L409">409</a>         if (!q)
<a name="L410" href="source/net/ipv4/inet_fragment.c#L410">410</a>                 return <a href="ident?i=NULL">NULL</a>;
<a name="L411" href="source/net/ipv4/inet_fragment.c#L411">411</a> 
<a name="L412" href="source/net/ipv4/inet_fragment.c#L412">412</a>         return <a href="ident?i=inet_frag_intern">inet_frag_intern</a>(nf, q, <a href="ident?i=f">f</a>, <a href="ident?i=arg">arg</a>);
<a name="L413" href="source/net/ipv4/inet_fragment.c#L413">413</a> }
<a name="L414" href="source/net/ipv4/inet_fragment.c#L414">414</a> 
<a name="L415" href="source/net/ipv4/inet_fragment.c#L415">415</a> struct <a href="ident?i=inet_frag_queue">inet_frag_queue</a> *<a href="ident?i=inet_frag_find">inet_frag_find</a>(struct <a href="ident?i=netns_frags">netns_frags</a> *nf,
<a name="L416" href="source/net/ipv4/inet_fragment.c#L416">416</a>                                        struct <a href="ident?i=inet_frags">inet_frags</a> *<a href="ident?i=f">f</a>, void *<a href="ident?i=key">key</a>,
<a name="L417" href="source/net/ipv4/inet_fragment.c#L417">417</a>                                        unsigned int <a href="ident?i=hash">hash</a>)
<a name="L418" href="source/net/ipv4/inet_fragment.c#L418">418</a> {
<a name="L419" href="source/net/ipv4/inet_fragment.c#L419">419</a>         struct <a href="ident?i=inet_frag_bucket">inet_frag_bucket</a> *hb;
<a name="L420" href="source/net/ipv4/inet_fragment.c#L420">420</a>         struct <a href="ident?i=inet_frag_queue">inet_frag_queue</a> *q;
<a name="L421" href="source/net/ipv4/inet_fragment.c#L421">421</a>         int <a href="ident?i=depth">depth</a> = 0;
<a name="L422" href="source/net/ipv4/inet_fragment.c#L422">422</a> 
<a name="L423" href="source/net/ipv4/inet_fragment.c#L423">423</a>         if (<a href="ident?i=frag_mem_limit">frag_mem_limit</a>(nf) &gt; nf-&gt;low_thresh)
<a name="L424" href="source/net/ipv4/inet_fragment.c#L424">424</a>                 <a href="ident?i=inet_frag_schedule_worker">inet_frag_schedule_worker</a>(<a href="ident?i=f">f</a>);
<a name="L425" href="source/net/ipv4/inet_fragment.c#L425">425</a> 
<a name="L426" href="source/net/ipv4/inet_fragment.c#L426">426</a>         <a href="ident?i=hash">hash</a> &amp;= (<a href="ident?i=INETFRAGS_HASHSZ">INETFRAGS_HASHSZ</a> - 1);
<a name="L427" href="source/net/ipv4/inet_fragment.c#L427">427</a>         hb = &amp;<a href="ident?i=f">f</a>-&gt;<a href="ident?i=hash">hash</a>[<a href="ident?i=hash">hash</a>];
<a name="L428" href="source/net/ipv4/inet_fragment.c#L428">428</a> 
<a name="L429" href="source/net/ipv4/inet_fragment.c#L429">429</a>         <a href="ident?i=spin_lock">spin_lock</a>(&amp;hb-&gt;chain_lock);
<a name="L430" href="source/net/ipv4/inet_fragment.c#L430">430</a>         <a href="ident?i=hlist_for_each_entry">hlist_for_each_entry</a>(q, &amp;hb-&gt;<a href="ident?i=chain">chain</a>, <a href="ident?i=list">list</a>) {
<a name="L431" href="source/net/ipv4/inet_fragment.c#L431">431</a>                 if (q-&gt;<a href="ident?i=net">net</a> == nf &amp;&amp; <a href="ident?i=f">f</a>-&gt;<a href="ident?i=match">match</a>(q, <a href="ident?i=key">key</a>)) {
<a name="L432" href="source/net/ipv4/inet_fragment.c#L432">432</a>                         <a href="ident?i=atomic_inc">atomic_inc</a>(&amp;q-&gt;refcnt);
<a name="L433" href="source/net/ipv4/inet_fragment.c#L433">433</a>                         <a href="ident?i=spin_unlock">spin_unlock</a>(&amp;hb-&gt;chain_lock);
<a name="L434" href="source/net/ipv4/inet_fragment.c#L434">434</a>                         return q;
<a name="L435" href="source/net/ipv4/inet_fragment.c#L435">435</a>                 }
<a name="L436" href="source/net/ipv4/inet_fragment.c#L436">436</a>                 <a href="ident?i=depth">depth</a>++;
<a name="L437" href="source/net/ipv4/inet_fragment.c#L437">437</a>         }
<a name="L438" href="source/net/ipv4/inet_fragment.c#L438">438</a>         <a href="ident?i=spin_unlock">spin_unlock</a>(&amp;hb-&gt;chain_lock);
<a name="L439" href="source/net/ipv4/inet_fragment.c#L439">439</a> 
<a name="L440" href="source/net/ipv4/inet_fragment.c#L440">440</a>         if (<a href="ident?i=depth">depth</a> &lt;= <a href="ident?i=INETFRAGS_MAXDEPTH">INETFRAGS_MAXDEPTH</a>)
<a name="L441" href="source/net/ipv4/inet_fragment.c#L441">441</a>                 return <a href="ident?i=inet_frag_create">inet_frag_create</a>(nf, <a href="ident?i=f">f</a>, <a href="ident?i=key">key</a>);
<a name="L442" href="source/net/ipv4/inet_fragment.c#L442">442</a> 
<a name="L443" href="source/net/ipv4/inet_fragment.c#L443">443</a>         if (<a href="ident?i=inet_frag_may_rebuild">inet_frag_may_rebuild</a>(<a href="ident?i=f">f</a>)) {
<a name="L444" href="source/net/ipv4/inet_fragment.c#L444">444</a>                 if (!<a href="ident?i=f">f</a>-&gt;rebuild)
<a name="L445" href="source/net/ipv4/inet_fragment.c#L445">445</a>                         <a href="ident?i=f">f</a>-&gt;rebuild = <a href="ident?i=true">true</a>;
<a name="L446" href="source/net/ipv4/inet_fragment.c#L446">446</a>                 <a href="ident?i=inet_frag_schedule_worker">inet_frag_schedule_worker</a>(<a href="ident?i=f">f</a>);
<a name="L447" href="source/net/ipv4/inet_fragment.c#L447">447</a>         }
<a name="L448" href="source/net/ipv4/inet_fragment.c#L448">448</a> 
<a name="L449" href="source/net/ipv4/inet_fragment.c#L449">449</a>         return <a href="ident?i=ERR_PTR">ERR_PTR</a>(-<a href="ident?i=ENOBUFS">ENOBUFS</a>);
<a name="L450" href="source/net/ipv4/inet_fragment.c#L450">450</a> }
<a name="L451" href="source/net/ipv4/inet_fragment.c#L451">451</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=inet_frag_find">inet_frag_find</a>);
<a name="L452" href="source/net/ipv4/inet_fragment.c#L452">452</a> 
<a name="L453" href="source/net/ipv4/inet_fragment.c#L453">453</a> void <a href="ident?i=inet_frag_maybe_warn_overflow">inet_frag_maybe_warn_overflow</a>(struct <a href="ident?i=inet_frag_queue">inet_frag_queue</a> *q,
<a name="L454" href="source/net/ipv4/inet_fragment.c#L454">454</a>                                    const char *<a href="ident?i=prefix">prefix</a>)
<a name="L455" href="source/net/ipv4/inet_fragment.c#L455">455</a> {
<a name="L456" href="source/net/ipv4/inet_fragment.c#L456">456</a>         static const char <a href="ident?i=msg">msg</a>[] = <i>"inet_frag_find: Fragment hash bucket"</i>
<a name="L457" href="source/net/ipv4/inet_fragment.c#L457">457</a>                 <i>" list length grew over limit "</i> <a href="ident?i=__stringify">__stringify</a>(<a href="ident?i=INETFRAGS_MAXDEPTH">INETFRAGS_MAXDEPTH</a>)
<a name="L458" href="source/net/ipv4/inet_fragment.c#L458">458</a>                 <i>". Dropping fragment.\n"</i>;
<a name="L459" href="source/net/ipv4/inet_fragment.c#L459">459</a> 
<a name="L460" href="source/net/ipv4/inet_fragment.c#L460">460</a>         if (<a href="ident?i=PTR_ERR">PTR_ERR</a>(q) == -<a href="ident?i=ENOBUFS">ENOBUFS</a>)
<a name="L461" href="source/net/ipv4/inet_fragment.c#L461">461</a>                 <a href="ident?i=net_dbg_ratelimited">net_dbg_ratelimited</a>(<i>"%s%s"</i>, <a href="ident?i=prefix">prefix</a>, <a href="ident?i=msg">msg</a>);
<a name="L462" href="source/net/ipv4/inet_fragment.c#L462">462</a> }
<a name="L463" href="source/net/ipv4/inet_fragment.c#L463">463</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=inet_frag_maybe_warn_overflow">inet_frag_maybe_warn_overflow</a>);
<a name="L464" href="source/net/ipv4/inet_fragment.c#L464">464</a> </pre></div><p>
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
