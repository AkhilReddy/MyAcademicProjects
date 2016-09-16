<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title>Linux/net/ipv4/syncookies.c - Linux Cross Reference - Free Electrons</title>
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
		 &nbsp;&bull;&nbsp;<b><i>source navigation</i></b> &nbsp;&bull;&nbsp;<a href="diff/net/ipv4/syncookies.c">diff markup</a> &nbsp;&bull;&nbsp;<a href="ident">identifier search</a> &nbsp;&bull;&nbsp;<a href="search">freetext search</a> &nbsp;&bull;&nbsp;
		</p>
	</div>
</div>

<div id="topbar">
  
  <p>Version: &nbsp;<a href="source/net/ipv4/syncookies.c?v=2.0.40">2.0.40</a>&nbsp;<a href="source/net/ipv4/syncookies.c?v=2.2.26">2.2.26</a>&nbsp;<a href="source/net/ipv4/syncookies.c?v=2.4.37">2.4.37</a>&nbsp;<a href="source/net/ipv4/syncookies.c?v=3.5">3.5</a>&nbsp;<a href="source/net/ipv4/syncookies.c?v=3.6">3.6</a>&nbsp;<a href="source/net/ipv4/syncookies.c?v=3.7">3.7</a>&nbsp;<a href="source/net/ipv4/syncookies.c?v=3.8">3.8</a>&nbsp;<a href="source/net/ipv4/syncookies.c?v=3.9">3.9</a>&nbsp;<a href="source/net/ipv4/syncookies.c?v=3.10">3.10</a>&nbsp;<a href="source/net/ipv4/syncookies.c?v=3.11">3.11</a>&nbsp;<a href="source/net/ipv4/syncookies.c?v=3.12">3.12</a>&nbsp;<a href="source/net/ipv4/syncookies.c?v=3.13">3.13</a>&nbsp;<a href="source/net/ipv4/syncookies.c?v=3.14">3.14</a>&nbsp;<a href="source/net/ipv4/syncookies.c?v=3.15">3.15</a>&nbsp;<a href="source/net/ipv4/syncookies.c?v=3.16">3.16</a>&nbsp;<a href="source/net/ipv4/syncookies.c?v=3.17">3.17</a>&nbsp;<a href="source/net/ipv4/syncookies.c?v=3.18">3.18</a>&nbsp;<a href="source/net/ipv4/syncookies.c?v=3.19">3.19</a>&nbsp;<a href="source/net/ipv4/syncookies.c?v=4.0">4.0</a>&nbsp;<b><i>4.1</i></b></p>
  
</div>

<h1><a href="source/">Linux</a>/<a href="source/net/">net</a>/<a href="source/net/ipv4/">ipv4</a>/<a href="source/net/ipv4/syncookies.c">syncookies.c</a></h1>
<div id="lxrcode"><pre>  <a name="L1" href="source/net/ipv4/syncookies.c#L1">1</a> <b><i>/*</i></b>
  <a name="L2" href="source/net/ipv4/syncookies.c#L2">2</a> <b><i> *  Syncookies implementation for the Linux kernel</i></b>
  <a name="L3" href="source/net/ipv4/syncookies.c#L3">3</a> <b><i> *</i></b>
  <a name="L4" href="source/net/ipv4/syncookies.c#L4">4</a> <b><i> *  Copyright (C) 1997 Andi Kleen</i></b>
  <a name="L5" href="source/net/ipv4/syncookies.c#L5">5</a> <b><i> *  Based on ideas by D.J.Bernstein and Eric Schenk.</i></b>
  <a name="L6" href="source/net/ipv4/syncookies.c#L6">6</a> <b><i> *</i></b>
  <a name="L7" href="source/net/ipv4/syncookies.c#L7">7</a> <b><i> *      This program is free software; you can redistribute it and/or</i></b>
  <a name="L8" href="source/net/ipv4/syncookies.c#L8">8</a> <b><i> *      modify it under the terms of the GNU General Public License</i></b>
  <a name="L9" href="source/net/ipv4/syncookies.c#L9">9</a> <b><i> *      as published by the Free Software Foundation; either version</i></b>
 <a name="L10" href="source/net/ipv4/syncookies.c#L10">10</a> <b><i> *      2 of the License, or (at your option) any later version.</i></b>
 <a name="L11" href="source/net/ipv4/syncookies.c#L11">11</a> <b><i> */</i></b>
 <a name="L12" href="source/net/ipv4/syncookies.c#L12">12</a> 
 <a name="L13" href="source/net/ipv4/syncookies.c#L13">13</a> #include &lt;linux/tcp.h&gt;
 <a name="L14" href="source/net/ipv4/syncookies.c#L14">14</a> #include &lt;linux/slab.h&gt;
 <a name="L15" href="source/net/ipv4/syncookies.c#L15">15</a> #include &lt;linux/random.h&gt;
 <a name="L16" href="source/net/ipv4/syncookies.c#L16">16</a> #include &lt;linux/cryptohash.h&gt;
 <a name="L17" href="source/net/ipv4/syncookies.c#L17">17</a> #include &lt;linux/kernel.h&gt;
 <a name="L18" href="source/net/ipv4/syncookies.c#L18">18</a> #include &lt;linux/export.h&gt;
 <a name="L19" href="source/net/ipv4/syncookies.c#L19">19</a> #include &lt;net/tcp.h&gt;
 <a name="L20" href="source/net/ipv4/syncookies.c#L20">20</a> #include &lt;net/route.h&gt;
 <a name="L21" href="source/net/ipv4/syncookies.c#L21">21</a> 
 <a name="L22" href="source/net/ipv4/syncookies.c#L22">22</a> extern int <a href="ident?i=sysctl_tcp_syncookies">sysctl_tcp_syncookies</a>;
 <a name="L23" href="source/net/ipv4/syncookies.c#L23">23</a> 
 <a name="L24" href="source/net/ipv4/syncookies.c#L24">24</a> static <a href="ident?i=u32">u32</a> syncookie_secret[2][16-4+<a href="ident?i=SHA_DIGEST_WORDS">SHA_DIGEST_WORDS</a>] <a href="ident?i=__read_mostly">__read_mostly</a>;
 <a name="L25" href="source/net/ipv4/syncookies.c#L25">25</a> 
 <a name="L26" href="source/net/ipv4/syncookies.c#L26">26</a> #define <a href="ident?i=COOKIEBITS">COOKIEBITS</a> 24   <b><i>/* Upper bits store count */</i></b>
 <a name="L27" href="source/net/ipv4/syncookies.c#L27">27</a> #define <a href="ident?i=COOKIEMASK">COOKIEMASK</a> (((<a href="ident?i=__u32">__u32</a>)1 &lt;&lt; <a href="ident?i=COOKIEBITS">COOKIEBITS</a>) - 1)
 <a name="L28" href="source/net/ipv4/syncookies.c#L28">28</a> 
 <a name="L29" href="source/net/ipv4/syncookies.c#L29">29</a> <b><i>/* TCP Timestamp: 6 lowest bits of timestamp sent in the cookie SYN-ACK</i></b>
 <a name="L30" href="source/net/ipv4/syncookies.c#L30">30</a> <b><i> * stores TCP options:</i></b>
 <a name="L31" href="source/net/ipv4/syncookies.c#L31">31</a> <b><i> *</i></b>
 <a name="L32" href="source/net/ipv4/syncookies.c#L32">32</a> <b><i> * MSB                               LSB</i></b>
 <a name="L33" href="source/net/ipv4/syncookies.c#L33">33</a> <b><i> * | 31 ...   6 |  5  |  4   | 3 2 1 0 |</i></b>
 <a name="L34" href="source/net/ipv4/syncookies.c#L34">34</a> <b><i> * |  Timestamp | ECN | SACK | WScale  |</i></b>
 <a name="L35" href="source/net/ipv4/syncookies.c#L35">35</a> <b><i> *</i></b>
 <a name="L36" href="source/net/ipv4/syncookies.c#L36">36</a> <b><i> * When we receive a valid cookie-ACK, we look at the echoed tsval (if</i></b>
 <a name="L37" href="source/net/ipv4/syncookies.c#L37">37</a> <b><i> * any) to figure out which TCP options we should use for the rebuilt</i></b>
 <a name="L38" href="source/net/ipv4/syncookies.c#L38">38</a> <b><i> * connection.</i></b>
 <a name="L39" href="source/net/ipv4/syncookies.c#L39">39</a> <b><i> *</i></b>
 <a name="L40" href="source/net/ipv4/syncookies.c#L40">40</a> <b><i> * A WScale setting of '0xf' (which is an invalid scaling value)</i></b>
 <a name="L41" href="source/net/ipv4/syncookies.c#L41">41</a> <b><i> * means that original syn did not include the TCP window scaling option.</i></b>
 <a name="L42" href="source/net/ipv4/syncookies.c#L42">42</a> <b><i> */</i></b>
 <a name="L43" href="source/net/ipv4/syncookies.c#L43">43</a> #define <a href="ident?i=TS_OPT_WSCALE_MASK">TS_OPT_WSCALE_MASK</a>      0xf
 <a name="L44" href="source/net/ipv4/syncookies.c#L44">44</a> #define <a href="ident?i=TS_OPT_SACK">TS_OPT_SACK</a>             <a href="ident?i=BIT">BIT</a>(4)
 <a name="L45" href="source/net/ipv4/syncookies.c#L45">45</a> #define <a href="ident?i=TS_OPT_ECN">TS_OPT_ECN</a>              <a href="ident?i=BIT">BIT</a>(5)
 <a name="L46" href="source/net/ipv4/syncookies.c#L46">46</a> <b><i>/* There is no TS_OPT_TIMESTAMP:</i></b>
 <a name="L47" href="source/net/ipv4/syncookies.c#L47">47</a> <b><i> * if ACK contains timestamp option, we already know it was</i></b>
 <a name="L48" href="source/net/ipv4/syncookies.c#L48">48</a> <b><i> * requested/supported by the syn/synack exchange.</i></b>
 <a name="L49" href="source/net/ipv4/syncookies.c#L49">49</a> <b><i> */</i></b>
 <a name="L50" href="source/net/ipv4/syncookies.c#L50">50</a> #define <a href="ident?i=TSBITS">TSBITS</a>  6
 <a name="L51" href="source/net/ipv4/syncookies.c#L51">51</a> #define <a href="ident?i=TSMASK">TSMASK</a>  (((<a href="ident?i=__u32">__u32</a>)1 &lt;&lt; <a href="ident?i=TSBITS">TSBITS</a>) - 1)
 <a name="L52" href="source/net/ipv4/syncookies.c#L52">52</a> 
 <a name="L53" href="source/net/ipv4/syncookies.c#L53">53</a> static <a href="ident?i=DEFINE_PER_CPU">DEFINE_PER_CPU</a>(<a href="ident?i=__u32">__u32</a> [16 + 5 + <a href="ident?i=SHA_WORKSPACE_WORDS">SHA_WORKSPACE_WORDS</a>],
 <a name="L54" href="source/net/ipv4/syncookies.c#L54">54</a>                       ipv4_cookie_scratch);
 <a name="L55" href="source/net/ipv4/syncookies.c#L55">55</a> 
 <a name="L56" href="source/net/ipv4/syncookies.c#L56">56</a> static <a href="ident?i=u32">u32</a> <a href="ident?i=cookie_hash">cookie_hash</a>(<a href="ident?i=__be32">__be32</a> <a href="ident?i=saddr">saddr</a>, <a href="ident?i=__be32">__be32</a> <a href="ident?i=daddr">daddr</a>, <a href="ident?i=__be16">__be16</a> sport, <a href="ident?i=__be16">__be16</a> dport,
 <a name="L57" href="source/net/ipv4/syncookies.c#L57">57</a>                        <a href="ident?i=u32">u32</a> <a href="ident?i=count">count</a>, int <a href="ident?i=c">c</a>)
 <a name="L58" href="source/net/ipv4/syncookies.c#L58">58</a> {
 <a name="L59" href="source/net/ipv4/syncookies.c#L59">59</a>         <a href="ident?i=__u32">__u32</a> *<a href="ident?i=tmp">tmp</a>;
 <a name="L60" href="source/net/ipv4/syncookies.c#L60">60</a> 
 <a name="L61" href="source/net/ipv4/syncookies.c#L61">61</a>         <a href="ident?i=net_get_random_once">net_get_random_once</a>(syncookie_secret, sizeof(syncookie_secret));
 <a name="L62" href="source/net/ipv4/syncookies.c#L62">62</a> 
 <a name="L63" href="source/net/ipv4/syncookies.c#L63">63</a>         <a href="ident?i=tmp">tmp</a>  = <a href="ident?i=this_cpu_ptr">this_cpu_ptr</a>(ipv4_cookie_scratch);
 <a name="L64" href="source/net/ipv4/syncookies.c#L64">64</a>         <a href="ident?i=memcpy">memcpy</a>(<a href="ident?i=tmp">tmp</a> + 4, syncookie_secret[<a href="ident?i=c">c</a>], sizeof(syncookie_secret[<a href="ident?i=c">c</a>]));
 <a name="L65" href="source/net/ipv4/syncookies.c#L65">65</a>         <a href="ident?i=tmp">tmp</a>[0] = (<a href="ident?i=__force">__force</a> <a href="ident?i=u32">u32</a>)<a href="ident?i=saddr">saddr</a>;
 <a name="L66" href="source/net/ipv4/syncookies.c#L66">66</a>         <a href="ident?i=tmp">tmp</a>[1] = (<a href="ident?i=__force">__force</a> <a href="ident?i=u32">u32</a>)<a href="ident?i=daddr">daddr</a>;
 <a name="L67" href="source/net/ipv4/syncookies.c#L67">67</a>         <a href="ident?i=tmp">tmp</a>[2] = ((<a href="ident?i=__force">__force</a> <a href="ident?i=u32">u32</a>)sport &lt;&lt; 16) + (<a href="ident?i=__force">__force</a> <a href="ident?i=u32">u32</a>)dport;
 <a name="L68" href="source/net/ipv4/syncookies.c#L68">68</a>         <a href="ident?i=tmp">tmp</a>[3] = <a href="ident?i=count">count</a>;
 <a name="L69" href="source/net/ipv4/syncookies.c#L69">69</a>         <a href="ident?i=sha_transform">sha_transform</a>(<a href="ident?i=tmp">tmp</a> + 16, (<a href="ident?i=__u8">__u8</a> *)<a href="ident?i=tmp">tmp</a>, <a href="ident?i=tmp">tmp</a> + 16 + 5);
 <a name="L70" href="source/net/ipv4/syncookies.c#L70">70</a> 
 <a name="L71" href="source/net/ipv4/syncookies.c#L71">71</a>         return <a href="ident?i=tmp">tmp</a>[17];
 <a name="L72" href="source/net/ipv4/syncookies.c#L72">72</a> }
 <a name="L73" href="source/net/ipv4/syncookies.c#L73">73</a> 
 <a name="L74" href="source/net/ipv4/syncookies.c#L74">74</a> 
 <a name="L75" href="source/net/ipv4/syncookies.c#L75">75</a> <b><i>/*</i></b>
 <a name="L76" href="source/net/ipv4/syncookies.c#L76">76</a> <b><i> * when syncookies are in effect and tcp timestamps are enabled we encode</i></b>
 <a name="L77" href="source/net/ipv4/syncookies.c#L77">77</a> <b><i> * tcp options in the lower bits of the timestamp value that will be</i></b>
 <a name="L78" href="source/net/ipv4/syncookies.c#L78">78</a> <b><i> * sent in the syn-ack.</i></b>
 <a name="L79" href="source/net/ipv4/syncookies.c#L79">79</a> <b><i> * Since subsequent timestamps use the normal tcp_time_stamp value, we</i></b>
 <a name="L80" href="source/net/ipv4/syncookies.c#L80">80</a> <b><i> * must make sure that the resulting initial timestamp is &lt;= tcp_time_stamp.</i></b>
 <a name="L81" href="source/net/ipv4/syncookies.c#L81">81</a> <b><i> */</i></b>
 <a name="L82" href="source/net/ipv4/syncookies.c#L82">82</a> <a href="ident?i=__u32">__u32</a> <a href="ident?i=cookie_init_timestamp">cookie_init_timestamp</a>(struct <a href="ident?i=request_sock">request_sock</a> *<a href="ident?i=req">req</a>)
 <a name="L83" href="source/net/ipv4/syncookies.c#L83">83</a> {
 <a name="L84" href="source/net/ipv4/syncookies.c#L84">84</a>         struct <a href="ident?i=inet_request_sock">inet_request_sock</a> *ireq;
 <a name="L85" href="source/net/ipv4/syncookies.c#L85">85</a>         <a href="ident?i=u32">u32</a> <a href="ident?i=ts">ts</a>, ts_now = <a href="ident?i=tcp_time_stamp">tcp_time_stamp</a>;
 <a name="L86" href="source/net/ipv4/syncookies.c#L86">86</a>         <a href="ident?i=u32">u32</a> <a href="ident?i=options">options</a> = 0;
 <a name="L87" href="source/net/ipv4/syncookies.c#L87">87</a> 
 <a name="L88" href="source/net/ipv4/syncookies.c#L88">88</a>         ireq = <a href="ident?i=inet_rsk">inet_rsk</a>(<a href="ident?i=req">req</a>);
 <a name="L89" href="source/net/ipv4/syncookies.c#L89">89</a> 
 <a name="L90" href="source/net/ipv4/syncookies.c#L90">90</a>         <a href="ident?i=options">options</a> = ireq-&gt;wscale_ok ? ireq-&gt;snd_wscale : <a href="ident?i=TS_OPT_WSCALE_MASK">TS_OPT_WSCALE_MASK</a>;
 <a name="L91" href="source/net/ipv4/syncookies.c#L91">91</a>         if (ireq-&gt;sack_ok)
 <a name="L92" href="source/net/ipv4/syncookies.c#L92">92</a>                 <a href="ident?i=options">options</a> |= <a href="ident?i=TS_OPT_SACK">TS_OPT_SACK</a>;
 <a name="L93" href="source/net/ipv4/syncookies.c#L93">93</a>         if (ireq-&gt;ecn_ok)
 <a name="L94" href="source/net/ipv4/syncookies.c#L94">94</a>                 <a href="ident?i=options">options</a> |= <a href="ident?i=TS_OPT_ECN">TS_OPT_ECN</a>;
 <a name="L95" href="source/net/ipv4/syncookies.c#L95">95</a> 
 <a name="L96" href="source/net/ipv4/syncookies.c#L96">96</a>         <a href="ident?i=ts">ts</a> = ts_now &amp; ~TSMASK;
 <a name="L97" href="source/net/ipv4/syncookies.c#L97">97</a>         <a href="ident?i=ts">ts</a> |= <a href="ident?i=options">options</a>;
 <a name="L98" href="source/net/ipv4/syncookies.c#L98">98</a>         if (<a href="ident?i=ts">ts</a> &gt; ts_now) {
 <a name="L99" href="source/net/ipv4/syncookies.c#L99">99</a>                 <a href="ident?i=ts">ts</a> &gt;&gt;= <a href="ident?i=TSBITS">TSBITS</a>;
<a name="L100" href="source/net/ipv4/syncookies.c#L100">100</a>                 <a href="ident?i=ts">ts</a>--;
<a name="L101" href="source/net/ipv4/syncookies.c#L101">101</a>                 <a href="ident?i=ts">ts</a> &lt;&lt;= <a href="ident?i=TSBITS">TSBITS</a>;
<a name="L102" href="source/net/ipv4/syncookies.c#L102">102</a>                 <a href="ident?i=ts">ts</a> |= <a href="ident?i=options">options</a>;
<a name="L103" href="source/net/ipv4/syncookies.c#L103">103</a>         }
<a name="L104" href="source/net/ipv4/syncookies.c#L104">104</a>         return <a href="ident?i=ts">ts</a>;
<a name="L105" href="source/net/ipv4/syncookies.c#L105">105</a> }
<a name="L106" href="source/net/ipv4/syncookies.c#L106">106</a> 
<a name="L107" href="source/net/ipv4/syncookies.c#L107">107</a> 
<a name="L108" href="source/net/ipv4/syncookies.c#L108">108</a> static <a href="ident?i=__u32">__u32</a> <a href="ident?i=secure_tcp_syn_cookie">secure_tcp_syn_cookie</a>(<a href="ident?i=__be32">__be32</a> <a href="ident?i=saddr">saddr</a>, <a href="ident?i=__be32">__be32</a> <a href="ident?i=daddr">daddr</a>, <a href="ident?i=__be16">__be16</a> sport,
<a name="L109" href="source/net/ipv4/syncookies.c#L109">109</a>                                    <a href="ident?i=__be16">__be16</a> dport, <a href="ident?i=__u32">__u32</a> sseq, <a href="ident?i=__u32">__u32</a> <a href="ident?i=data">data</a>)
<a name="L110" href="source/net/ipv4/syncookies.c#L110">110</a> {
<a name="L111" href="source/net/ipv4/syncookies.c#L111">111</a>         <b><i>/*</i></b>
<a name="L112" href="source/net/ipv4/syncookies.c#L112">112</a> <b><i>         * Compute the secure sequence number.</i></b>
<a name="L113" href="source/net/ipv4/syncookies.c#L113">113</a> <b><i>         * The output should be:</i></b>
<a name="L114" href="source/net/ipv4/syncookies.c#L114">114</a> <b><i>         *   HASH(sec1,saddr,sport,daddr,dport,sec1) + sseq + (count * 2^24)</i></b>
<a name="L115" href="source/net/ipv4/syncookies.c#L115">115</a> <b><i>         *      + (HASH(sec2,saddr,sport,daddr,dport,count,sec2) % 2^24).</i></b>
<a name="L116" href="source/net/ipv4/syncookies.c#L116">116</a> <b><i>         * Where sseq is their sequence number and count increases every</i></b>
<a name="L117" href="source/net/ipv4/syncookies.c#L117">117</a> <b><i>         * minute by 1.</i></b>
<a name="L118" href="source/net/ipv4/syncookies.c#L118">118</a> <b><i>         * As an extra hack, we add a small "data" value that encodes the</i></b>
<a name="L119" href="source/net/ipv4/syncookies.c#L119">119</a> <b><i>         * MSS into the second hash value.</i></b>
<a name="L120" href="source/net/ipv4/syncookies.c#L120">120</a> <b><i>         */</i></b>
<a name="L121" href="source/net/ipv4/syncookies.c#L121">121</a>         <a href="ident?i=u32">u32</a> <a href="ident?i=count">count</a> = <a href="ident?i=tcp_cookie_time">tcp_cookie_time</a>();
<a name="L122" href="source/net/ipv4/syncookies.c#L122">122</a>         return (<a href="ident?i=cookie_hash">cookie_hash</a>(<a href="ident?i=saddr">saddr</a>, <a href="ident?i=daddr">daddr</a>, sport, dport, 0, 0) +
<a name="L123" href="source/net/ipv4/syncookies.c#L123">123</a>                 sseq + (<a href="ident?i=count">count</a> &lt;&lt; <a href="ident?i=COOKIEBITS">COOKIEBITS</a>) +
<a name="L124" href="source/net/ipv4/syncookies.c#L124">124</a>                 ((<a href="ident?i=cookie_hash">cookie_hash</a>(<a href="ident?i=saddr">saddr</a>, <a href="ident?i=daddr">daddr</a>, sport, dport, <a href="ident?i=count">count</a>, 1) + <a href="ident?i=data">data</a>)
<a name="L125" href="source/net/ipv4/syncookies.c#L125">125</a>                  &amp; <a href="ident?i=COOKIEMASK">COOKIEMASK</a>));
<a name="L126" href="source/net/ipv4/syncookies.c#L126">126</a> }
<a name="L127" href="source/net/ipv4/syncookies.c#L127">127</a> 
<a name="L128" href="source/net/ipv4/syncookies.c#L128">128</a> <b><i>/*</i></b>
<a name="L129" href="source/net/ipv4/syncookies.c#L129">129</a> <b><i> * This retrieves the small "data" value from the syncookie.</i></b>
<a name="L130" href="source/net/ipv4/syncookies.c#L130">130</a> <b><i> * If the syncookie is bad, the data returned will be out of</i></b>
<a name="L131" href="source/net/ipv4/syncookies.c#L131">131</a> <b><i> * range.  This must be checked by the caller.</i></b>
<a name="L132" href="source/net/ipv4/syncookies.c#L132">132</a> <b><i> *</i></b>
<a name="L133" href="source/net/ipv4/syncookies.c#L133">133</a> <b><i> * The count value used to generate the cookie must be less than</i></b>
<a name="L134" href="source/net/ipv4/syncookies.c#L134">134</a> <b><i> * MAX_SYNCOOKIE_AGE minutes in the past.</i></b>
<a name="L135" href="source/net/ipv4/syncookies.c#L135">135</a> <b><i> * The return value (__u32)-1 if this test fails.</i></b>
<a name="L136" href="source/net/ipv4/syncookies.c#L136">136</a> <b><i> */</i></b>
<a name="L137" href="source/net/ipv4/syncookies.c#L137">137</a> static <a href="ident?i=__u32">__u32</a> <a href="ident?i=check_tcp_syn_cookie">check_tcp_syn_cookie</a>(<a href="ident?i=__u32">__u32</a> cookie, <a href="ident?i=__be32">__be32</a> <a href="ident?i=saddr">saddr</a>, <a href="ident?i=__be32">__be32</a> <a href="ident?i=daddr">daddr</a>,
<a name="L138" href="source/net/ipv4/syncookies.c#L138">138</a>                                   <a href="ident?i=__be16">__be16</a> sport, <a href="ident?i=__be16">__be16</a> dport, <a href="ident?i=__u32">__u32</a> sseq)
<a name="L139" href="source/net/ipv4/syncookies.c#L139">139</a> {
<a name="L140" href="source/net/ipv4/syncookies.c#L140">140</a>         <a href="ident?i=u32">u32</a> diff, <a href="ident?i=count">count</a> = <a href="ident?i=tcp_cookie_time">tcp_cookie_time</a>();
<a name="L141" href="source/net/ipv4/syncookies.c#L141">141</a> 
<a name="L142" href="source/net/ipv4/syncookies.c#L142">142</a>         <b><i>/* Strip away the layers from the cookie */</i></b>
<a name="L143" href="source/net/ipv4/syncookies.c#L143">143</a>         cookie -= <a href="ident?i=cookie_hash">cookie_hash</a>(<a href="ident?i=saddr">saddr</a>, <a href="ident?i=daddr">daddr</a>, sport, dport, 0, 0) + sseq;
<a name="L144" href="source/net/ipv4/syncookies.c#L144">144</a> 
<a name="L145" href="source/net/ipv4/syncookies.c#L145">145</a>         <b><i>/* Cookie is now reduced to (count * 2^24) ^ (hash % 2^24) */</i></b>
<a name="L146" href="source/net/ipv4/syncookies.c#L146">146</a>         diff = (<a href="ident?i=count">count</a> - (cookie &gt;&gt; <a href="ident?i=COOKIEBITS">COOKIEBITS</a>)) &amp; ((<a href="ident?i=__u32">__u32</a>) -1 &gt;&gt; <a href="ident?i=COOKIEBITS">COOKIEBITS</a>);
<a name="L147" href="source/net/ipv4/syncookies.c#L147">147</a>         if (diff &gt;= <a href="ident?i=MAX_SYNCOOKIE_AGE">MAX_SYNCOOKIE_AGE</a>)
<a name="L148" href="source/net/ipv4/syncookies.c#L148">148</a>                 return (<a href="ident?i=__u32">__u32</a>)-1;
<a name="L149" href="source/net/ipv4/syncookies.c#L149">149</a> 
<a name="L150" href="source/net/ipv4/syncookies.c#L150">150</a>         return (cookie -
<a name="L151" href="source/net/ipv4/syncookies.c#L151">151</a>                 <a href="ident?i=cookie_hash">cookie_hash</a>(<a href="ident?i=saddr">saddr</a>, <a href="ident?i=daddr">daddr</a>, sport, dport, <a href="ident?i=count">count</a> - diff, 1))
<a name="L152" href="source/net/ipv4/syncookies.c#L152">152</a>                 &amp; <a href="ident?i=COOKIEMASK">COOKIEMASK</a>;   <b><i>/* Leaving the data behind */</i></b>
<a name="L153" href="source/net/ipv4/syncookies.c#L153">153</a> }
<a name="L154" href="source/net/ipv4/syncookies.c#L154">154</a> 
<a name="L155" href="source/net/ipv4/syncookies.c#L155">155</a> <b><i>/*</i></b>
<a name="L156" href="source/net/ipv4/syncookies.c#L156">156</a> <b><i> * MSS Values are chosen based on the 2011 paper</i></b>
<a name="L157" href="source/net/ipv4/syncookies.c#L157">157</a> <b><i> * 'An Analysis of TCP Maximum Segement Sizes' by S. Alcock and R. Nelson.</i></b>
<a name="L158" href="source/net/ipv4/syncookies.c#L158">158</a> <b><i> * Values ..</i></b>
<a name="L159" href="source/net/ipv4/syncookies.c#L159">159</a> <b><i> *  .. lower than 536 are rare (&lt; 0.2%)</i></b>
<a name="L160" href="source/net/ipv4/syncookies.c#L160">160</a> <b><i> *  .. between 537 and 1299 account for less than &lt; 1.5% of observed values</i></b>
<a name="L161" href="source/net/ipv4/syncookies.c#L161">161</a> <b><i> *  .. in the 1300-1349 range account for about 15 to 20% of observed mss values</i></b>
<a name="L162" href="source/net/ipv4/syncookies.c#L162">162</a> <b><i> *  .. exceeding 1460 are very rare (&lt; 0.04%)</i></b>
<a name="L163" href="source/net/ipv4/syncookies.c#L163">163</a> <b><i> *</i></b>
<a name="L164" href="source/net/ipv4/syncookies.c#L164">164</a> <b><i> *  1460 is the single most frequently announced mss value (30 to 46% depending</i></b>
<a name="L165" href="source/net/ipv4/syncookies.c#L165">165</a> <b><i> *  on monitor location).  Table must be sorted.</i></b>
<a name="L166" href="source/net/ipv4/syncookies.c#L166">166</a> <b><i> */</i></b>
<a name="L167" href="source/net/ipv4/syncookies.c#L167">167</a> static <a href="ident?i=__u16">__u16</a> const <a href="ident?i=msstab">msstab</a>[] = {
<a name="L168" href="source/net/ipv4/syncookies.c#L168">168</a>         536,
<a name="L169" href="source/net/ipv4/syncookies.c#L169">169</a>         1300,
<a name="L170" href="source/net/ipv4/syncookies.c#L170">170</a>         1440,   <b><i>/* 1440, 1452: PPPoE */</i></b>
<a name="L171" href="source/net/ipv4/syncookies.c#L171">171</a>         1460,
<a name="L172" href="source/net/ipv4/syncookies.c#L172">172</a> };
<a name="L173" href="source/net/ipv4/syncookies.c#L173">173</a> 
<a name="L174" href="source/net/ipv4/syncookies.c#L174">174</a> <b><i>/*</i></b>
<a name="L175" href="source/net/ipv4/syncookies.c#L175">175</a> <b><i> * Generate a syncookie.  mssp points to the mss, which is returned</i></b>
<a name="L176" href="source/net/ipv4/syncookies.c#L176">176</a> <b><i> * rounded down to the value encoded in the cookie.</i></b>
<a name="L177" href="source/net/ipv4/syncookies.c#L177">177</a> <b><i> */</i></b>
<a name="L178" href="source/net/ipv4/syncookies.c#L178">178</a> <a href="ident?i=u32">u32</a> <a href="ident?i=__cookie_v4_init_sequence">__cookie_v4_init_sequence</a>(const struct <a href="ident?i=iphdr">iphdr</a> *iph, const struct <a href="ident?i=tcphdr">tcphdr</a> *<a href="ident?i=th">th</a>,
<a name="L179" href="source/net/ipv4/syncookies.c#L179">179</a>                               <a href="ident?i=u16">u16</a> *<a href="ident?i=mssp">mssp</a>)
<a name="L180" href="source/net/ipv4/syncookies.c#L180">180</a> {
<a name="L181" href="source/net/ipv4/syncookies.c#L181">181</a>         int mssind;
<a name="L182" href="source/net/ipv4/syncookies.c#L182">182</a>         const <a href="ident?i=__u16">__u16</a> mss = *<a href="ident?i=mssp">mssp</a>;
<a name="L183" href="source/net/ipv4/syncookies.c#L183">183</a> 
<a name="L184" href="source/net/ipv4/syncookies.c#L184">184</a>         for (mssind = <a href="ident?i=ARRAY_SIZE">ARRAY_SIZE</a>(<a href="ident?i=msstab">msstab</a>) - 1; mssind ; mssind--)
<a name="L185" href="source/net/ipv4/syncookies.c#L185">185</a>                 if (mss &gt;= <a href="ident?i=msstab">msstab</a>[mssind])
<a name="L186" href="source/net/ipv4/syncookies.c#L186">186</a>                         break;
<a name="L187" href="source/net/ipv4/syncookies.c#L187">187</a>         *<a href="ident?i=mssp">mssp</a> = <a href="ident?i=msstab">msstab</a>[mssind];
<a name="L188" href="source/net/ipv4/syncookies.c#L188">188</a> 
<a name="L189" href="source/net/ipv4/syncookies.c#L189">189</a>         return <a href="ident?i=secure_tcp_syn_cookie">secure_tcp_syn_cookie</a>(iph-&gt;<a href="ident?i=saddr">saddr</a>, iph-&gt;<a href="ident?i=daddr">daddr</a>,
<a name="L190" href="source/net/ipv4/syncookies.c#L190">190</a>                                      <a href="ident?i=th">th</a>-&gt;source, <a href="ident?i=th">th</a>-&gt;<a href="ident?i=dest">dest</a>, <a href="ident?i=ntohl">ntohl</a>(<a href="ident?i=th">th</a>-&gt;<a href="ident?i=seq">seq</a>),
<a name="L191" href="source/net/ipv4/syncookies.c#L191">191</a>                                      mssind);
<a name="L192" href="source/net/ipv4/syncookies.c#L192">192</a> }
<a name="L193" href="source/net/ipv4/syncookies.c#L193">193</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=__cookie_v4_init_sequence">__cookie_v4_init_sequence</a>);
<a name="L194" href="source/net/ipv4/syncookies.c#L194">194</a> 
<a name="L195" href="source/net/ipv4/syncookies.c#L195">195</a> <a href="ident?i=__u32">__u32</a> <a href="ident?i=cookie_v4_init_sequence">cookie_v4_init_sequence</a>(struct <a href="ident?i=sock">sock</a> *sk, const struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
<a name="L196" href="source/net/ipv4/syncookies.c#L196">196</a>                               <a href="ident?i=__u16">__u16</a> *<a href="ident?i=mssp">mssp</a>)
<a name="L197" href="source/net/ipv4/syncookies.c#L197">197</a> {
<a name="L198" href="source/net/ipv4/syncookies.c#L198">198</a>         const struct <a href="ident?i=iphdr">iphdr</a> *iph = <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>);
<a name="L199" href="source/net/ipv4/syncookies.c#L199">199</a>         const struct <a href="ident?i=tcphdr">tcphdr</a> *<a href="ident?i=th">th</a> = <a href="ident?i=tcp_hdr">tcp_hdr</a>(<a href="ident?i=skb">skb</a>);
<a name="L200" href="source/net/ipv4/syncookies.c#L200">200</a> 
<a name="L201" href="source/net/ipv4/syncookies.c#L201">201</a>         <a href="ident?i=tcp_synq_overflow">tcp_synq_overflow</a>(sk);
<a name="L202" href="source/net/ipv4/syncookies.c#L202">202</a>         <a href="ident?i=NET_INC_STATS_BH">NET_INC_STATS_BH</a>(<a href="ident?i=sock_net">sock_net</a>(sk), LINUX_MIB_SYNCOOKIESSENT);
<a name="L203" href="source/net/ipv4/syncookies.c#L203">203</a> 
<a name="L204" href="source/net/ipv4/syncookies.c#L204">204</a>         return <a href="ident?i=__cookie_v4_init_sequence">__cookie_v4_init_sequence</a>(iph, <a href="ident?i=th">th</a>, <a href="ident?i=mssp">mssp</a>);
<a name="L205" href="source/net/ipv4/syncookies.c#L205">205</a> }
<a name="L206" href="source/net/ipv4/syncookies.c#L206">206</a> 
<a name="L207" href="source/net/ipv4/syncookies.c#L207">207</a> <b><i>/*</i></b>
<a name="L208" href="source/net/ipv4/syncookies.c#L208">208</a> <b><i> * Check if a ack sequence number is a valid syncookie.</i></b>
<a name="L209" href="source/net/ipv4/syncookies.c#L209">209</a> <b><i> * Return the decoded mss if it is, or 0 if not.</i></b>
<a name="L210" href="source/net/ipv4/syncookies.c#L210">210</a> <b><i> */</i></b>
<a name="L211" href="source/net/ipv4/syncookies.c#L211">211</a> int <a href="ident?i=__cookie_v4_check">__cookie_v4_check</a>(const struct <a href="ident?i=iphdr">iphdr</a> *iph, const struct <a href="ident?i=tcphdr">tcphdr</a> *<a href="ident?i=th">th</a>,
<a name="L212" href="source/net/ipv4/syncookies.c#L212">212</a>                       <a href="ident?i=u32">u32</a> cookie)
<a name="L213" href="source/net/ipv4/syncookies.c#L213">213</a> {
<a name="L214" href="source/net/ipv4/syncookies.c#L214">214</a>         <a href="ident?i=__u32">__u32</a> <a href="ident?i=seq">seq</a> = <a href="ident?i=ntohl">ntohl</a>(<a href="ident?i=th">th</a>-&gt;<a href="ident?i=seq">seq</a>) - 1;
<a name="L215" href="source/net/ipv4/syncookies.c#L215">215</a>         <a href="ident?i=__u32">__u32</a> mssind = <a href="ident?i=check_tcp_syn_cookie">check_tcp_syn_cookie</a>(cookie, iph-&gt;<a href="ident?i=saddr">saddr</a>, iph-&gt;<a href="ident?i=daddr">daddr</a>,
<a name="L216" href="source/net/ipv4/syncookies.c#L216">216</a>                                             <a href="ident?i=th">th</a>-&gt;source, <a href="ident?i=th">th</a>-&gt;<a href="ident?i=dest">dest</a>, <a href="ident?i=seq">seq</a>);
<a name="L217" href="source/net/ipv4/syncookies.c#L217">217</a> 
<a name="L218" href="source/net/ipv4/syncookies.c#L218">218</a>         return mssind &lt; <a href="ident?i=ARRAY_SIZE">ARRAY_SIZE</a>(<a href="ident?i=msstab">msstab</a>) ? <a href="ident?i=msstab">msstab</a>[mssind] : 0;
<a name="L219" href="source/net/ipv4/syncookies.c#L219">219</a> }
<a name="L220" href="source/net/ipv4/syncookies.c#L220">220</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=__cookie_v4_check">__cookie_v4_check</a>);
<a name="L221" href="source/net/ipv4/syncookies.c#L221">221</a> 
<a name="L222" href="source/net/ipv4/syncookies.c#L222">222</a> static struct <a href="ident?i=sock">sock</a> *<a href="ident?i=get_cookie_sock">get_cookie_sock</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
<a name="L223" href="source/net/ipv4/syncookies.c#L223">223</a>                                     struct <a href="ident?i=request_sock">request_sock</a> *<a href="ident?i=req">req</a>,
<a name="L224" href="source/net/ipv4/syncookies.c#L224">224</a>                                     struct <a href="ident?i=dst_entry">dst_entry</a> *<a href="ident?i=dst">dst</a>)
<a name="L225" href="source/net/ipv4/syncookies.c#L225">225</a> {
<a name="L226" href="source/net/ipv4/syncookies.c#L226">226</a>         struct <a href="ident?i=inet_connection_sock">inet_connection_sock</a> *icsk = <a href="ident?i=inet_csk">inet_csk</a>(sk);
<a name="L227" href="source/net/ipv4/syncookies.c#L227">227</a>         struct <a href="ident?i=sock">sock</a> *<a href="ident?i=child">child</a>;
<a name="L228" href="source/net/ipv4/syncookies.c#L228">228</a> 
<a name="L229" href="source/net/ipv4/syncookies.c#L229">229</a>         <a href="ident?i=child">child</a> = icsk-&gt;icsk_af_ops-&gt;syn_recv_sock(sk, <a href="ident?i=skb">skb</a>, <a href="ident?i=req">req</a>, <a href="ident?i=dst">dst</a>);
<a name="L230" href="source/net/ipv4/syncookies.c#L230">230</a>         if (<a href="ident?i=child">child</a>) {
<a name="L231" href="source/net/ipv4/syncookies.c#L231">231</a>                 <a href="ident?i=atomic_set">atomic_set</a>(&amp;<a href="ident?i=req">req</a>-&gt;<a href="ident?i=rsk_refcnt">rsk_refcnt</a>, 1);
<a name="L232" href="source/net/ipv4/syncookies.c#L232">232</a>                 <a href="ident?i=inet_csk_reqsk_queue_add">inet_csk_reqsk_queue_add</a>(sk, <a href="ident?i=req">req</a>, <a href="ident?i=child">child</a>);
<a name="L233" href="source/net/ipv4/syncookies.c#L233">233</a>         } else {
<a name="L234" href="source/net/ipv4/syncookies.c#L234">234</a>                 <a href="ident?i=reqsk_free">reqsk_free</a>(<a href="ident?i=req">req</a>);
<a name="L235" href="source/net/ipv4/syncookies.c#L235">235</a>         }
<a name="L236" href="source/net/ipv4/syncookies.c#L236">236</a>         return <a href="ident?i=child">child</a>;
<a name="L237" href="source/net/ipv4/syncookies.c#L237">237</a> }
<a name="L238" href="source/net/ipv4/syncookies.c#L238">238</a> 
<a name="L239" href="source/net/ipv4/syncookies.c#L239">239</a> 
<a name="L240" href="source/net/ipv4/syncookies.c#L240">240</a> <b><i>/*</i></b>
<a name="L241" href="source/net/ipv4/syncookies.c#L241">241</a> <b><i> * when syncookies are in effect and tcp timestamps are enabled we stored</i></b>
<a name="L242" href="source/net/ipv4/syncookies.c#L242">242</a> <b><i> * additional tcp options in the timestamp.</i></b>
<a name="L243" href="source/net/ipv4/syncookies.c#L243">243</a> <b><i> * This extracts these options from the timestamp echo.</i></b>
<a name="L244" href="source/net/ipv4/syncookies.c#L244">244</a> <b><i> *</i></b>
<a name="L245" href="source/net/ipv4/syncookies.c#L245">245</a> <b><i> * return false if we decode a tcp option that is disabled</i></b>
<a name="L246" href="source/net/ipv4/syncookies.c#L246">246</a> <b><i> * on the host.</i></b>
<a name="L247" href="source/net/ipv4/syncookies.c#L247">247</a> <b><i> */</i></b>
<a name="L248" href="source/net/ipv4/syncookies.c#L248">248</a> <a href="ident?i=bool">bool</a> <a href="ident?i=cookie_timestamp_decode">cookie_timestamp_decode</a>(struct <a href="ident?i=tcp_options_received">tcp_options_received</a> *tcp_opt)
<a name="L249" href="source/net/ipv4/syncookies.c#L249">249</a> {
<a name="L250" href="source/net/ipv4/syncookies.c#L250">250</a>         <b><i>/* echoed timestamp, lowest bits contain options */</i></b>
<a name="L251" href="source/net/ipv4/syncookies.c#L251">251</a>         <a href="ident?i=u32">u32</a> <a href="ident?i=options">options</a> = tcp_opt-&gt;rcv_tsecr;
<a name="L252" href="source/net/ipv4/syncookies.c#L252">252</a> 
<a name="L253" href="source/net/ipv4/syncookies.c#L253">253</a>         if (!tcp_opt-&gt;saw_tstamp)  {
<a name="L254" href="source/net/ipv4/syncookies.c#L254">254</a>                 <a href="ident?i=tcp_clear_options">tcp_clear_options</a>(tcp_opt);
<a name="L255" href="source/net/ipv4/syncookies.c#L255">255</a>                 return <a href="ident?i=true">true</a>;
<a name="L256" href="source/net/ipv4/syncookies.c#L256">256</a>         }
<a name="L257" href="source/net/ipv4/syncookies.c#L257">257</a> 
<a name="L258" href="source/net/ipv4/syncookies.c#L258">258</a>         if (!<a href="ident?i=sysctl_tcp_timestamps">sysctl_tcp_timestamps</a>)
<a name="L259" href="source/net/ipv4/syncookies.c#L259">259</a>                 return <a href="ident?i=false">false</a>;
<a name="L260" href="source/net/ipv4/syncookies.c#L260">260</a> 
<a name="L261" href="source/net/ipv4/syncookies.c#L261">261</a>         tcp_opt-&gt;sack_ok = (<a href="ident?i=options">options</a> &amp; <a href="ident?i=TS_OPT_SACK">TS_OPT_SACK</a>) ? <a href="ident?i=TCP_SACK_SEEN">TCP_SACK_SEEN</a> : 0;
<a name="L262" href="source/net/ipv4/syncookies.c#L262">262</a> 
<a name="L263" href="source/net/ipv4/syncookies.c#L263">263</a>         if (tcp_opt-&gt;sack_ok &amp;&amp; !<a href="ident?i=sysctl_tcp_sack">sysctl_tcp_sack</a>)
<a name="L264" href="source/net/ipv4/syncookies.c#L264">264</a>                 return <a href="ident?i=false">false</a>;
<a name="L265" href="source/net/ipv4/syncookies.c#L265">265</a> 
<a name="L266" href="source/net/ipv4/syncookies.c#L266">266</a>         if ((<a href="ident?i=options">options</a> &amp; <a href="ident?i=TS_OPT_WSCALE_MASK">TS_OPT_WSCALE_MASK</a>) == <a href="ident?i=TS_OPT_WSCALE_MASK">TS_OPT_WSCALE_MASK</a>)
<a name="L267" href="source/net/ipv4/syncookies.c#L267">267</a>                 return <a href="ident?i=true">true</a>; <b><i>/* no window scaling */</i></b>
<a name="L268" href="source/net/ipv4/syncookies.c#L268">268</a> 
<a name="L269" href="source/net/ipv4/syncookies.c#L269">269</a>         tcp_opt-&gt;wscale_ok = 1;
<a name="L270" href="source/net/ipv4/syncookies.c#L270">270</a>         tcp_opt-&gt;snd_wscale = <a href="ident?i=options">options</a> &amp; <a href="ident?i=TS_OPT_WSCALE_MASK">TS_OPT_WSCALE_MASK</a>;
<a name="L271" href="source/net/ipv4/syncookies.c#L271">271</a> 
<a name="L272" href="source/net/ipv4/syncookies.c#L272">272</a>         return <a href="ident?i=sysctl_tcp_window_scaling">sysctl_tcp_window_scaling</a> != 0;
<a name="L273" href="source/net/ipv4/syncookies.c#L273">273</a> }
<a name="L274" href="source/net/ipv4/syncookies.c#L274">274</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=cookie_timestamp_decode">cookie_timestamp_decode</a>);
<a name="L275" href="source/net/ipv4/syncookies.c#L275">275</a> 
<a name="L276" href="source/net/ipv4/syncookies.c#L276">276</a> <a href="ident?i=bool">bool</a> <a href="ident?i=cookie_ecn_ok">cookie_ecn_ok</a>(const struct <a href="ident?i=tcp_options_received">tcp_options_received</a> *tcp_opt,
<a name="L277" href="source/net/ipv4/syncookies.c#L277">277</a>                    const struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>, const struct <a href="ident?i=dst_entry">dst_entry</a> *<a href="ident?i=dst">dst</a>)
<a name="L278" href="source/net/ipv4/syncookies.c#L278">278</a> {
<a name="L279" href="source/net/ipv4/syncookies.c#L279">279</a>         <a href="ident?i=bool">bool</a> ecn_ok = tcp_opt-&gt;rcv_tsecr &amp; <a href="ident?i=TS_OPT_ECN">TS_OPT_ECN</a>;
<a name="L280" href="source/net/ipv4/syncookies.c#L280">280</a> 
<a name="L281" href="source/net/ipv4/syncookies.c#L281">281</a>         if (!ecn_ok)
<a name="L282" href="source/net/ipv4/syncookies.c#L282">282</a>                 return <a href="ident?i=false">false</a>;
<a name="L283" href="source/net/ipv4/syncookies.c#L283">283</a> 
<a name="L284" href="source/net/ipv4/syncookies.c#L284">284</a>         if (<a href="ident?i=net">net</a>-&gt;ipv4.sysctl_tcp_ecn)
<a name="L285" href="source/net/ipv4/syncookies.c#L285">285</a>                 return <a href="ident?i=true">true</a>;
<a name="L286" href="source/net/ipv4/syncookies.c#L286">286</a> 
<a name="L287" href="source/net/ipv4/syncookies.c#L287">287</a>         return <a href="ident?i=dst_feature">dst_feature</a>(<a href="ident?i=dst">dst</a>, <a href="ident?i=RTAX_FEATURE_ECN">RTAX_FEATURE_ECN</a>);
<a name="L288" href="source/net/ipv4/syncookies.c#L288">288</a> }
<a name="L289" href="source/net/ipv4/syncookies.c#L289">289</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=cookie_ecn_ok">cookie_ecn_ok</a>);
<a name="L290" href="source/net/ipv4/syncookies.c#L290">290</a> 
<a name="L291" href="source/net/ipv4/syncookies.c#L291">291</a> struct <a href="ident?i=sock">sock</a> *<a href="ident?i=cookie_v4_check">cookie_v4_check</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L292" href="source/net/ipv4/syncookies.c#L292">292</a> {
<a name="L293" href="source/net/ipv4/syncookies.c#L293">293</a>         struct <a href="ident?i=ip_options">ip_options</a> *opt = &amp;<a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=header">header</a>.h4.opt;
<a name="L294" href="source/net/ipv4/syncookies.c#L294">294</a>         struct <a href="ident?i=tcp_options_received">tcp_options_received</a> tcp_opt;
<a name="L295" href="source/net/ipv4/syncookies.c#L295">295</a>         struct <a href="ident?i=inet_request_sock">inet_request_sock</a> *ireq;
<a name="L296" href="source/net/ipv4/syncookies.c#L296">296</a>         struct <a href="ident?i=tcp_request_sock">tcp_request_sock</a> *treq;
<a name="L297" href="source/net/ipv4/syncookies.c#L297">297</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L298" href="source/net/ipv4/syncookies.c#L298">298</a>         const struct <a href="ident?i=tcphdr">tcphdr</a> *<a href="ident?i=th">th</a> = <a href="ident?i=tcp_hdr">tcp_hdr</a>(<a href="ident?i=skb">skb</a>);
<a name="L299" href="source/net/ipv4/syncookies.c#L299">299</a>         <a href="ident?i=__u32">__u32</a> cookie = <a href="ident?i=ntohl">ntohl</a>(<a href="ident?i=th">th</a>-&gt;ack_seq) - 1;
<a name="L300" href="source/net/ipv4/syncookies.c#L300">300</a>         struct <a href="ident?i=sock">sock</a> *<a href="ident?i=ret">ret</a> = sk;
<a name="L301" href="source/net/ipv4/syncookies.c#L301">301</a>         struct <a href="ident?i=request_sock">request_sock</a> *<a href="ident?i=req">req</a>;
<a name="L302" href="source/net/ipv4/syncookies.c#L302">302</a>         int mss;
<a name="L303" href="source/net/ipv4/syncookies.c#L303">303</a>         struct <a href="ident?i=rtable">rtable</a> *<a href="ident?i=rt">rt</a>;
<a name="L304" href="source/net/ipv4/syncookies.c#L304">304</a>         <a href="ident?i=__u8">__u8</a> rcv_wscale;
<a name="L305" href="source/net/ipv4/syncookies.c#L305">305</a>         struct <a href="ident?i=flowi4">flowi4</a> fl4;
<a name="L306" href="source/net/ipv4/syncookies.c#L306">306</a> 
<a name="L307" href="source/net/ipv4/syncookies.c#L307">307</a>         if (!<a href="ident?i=sysctl_tcp_syncookies">sysctl_tcp_syncookies</a> || !<a href="ident?i=th">th</a>-&gt;ack || <a href="ident?i=th">th</a>-&gt;rst)
<a name="L308" href="source/net/ipv4/syncookies.c#L308">308</a>                 goto <a href="ident?i=out">out</a>;
<a name="L309" href="source/net/ipv4/syncookies.c#L309">309</a> 
<a name="L310" href="source/net/ipv4/syncookies.c#L310">310</a>         if (<a href="ident?i=tcp_synq_no_recent_overflow">tcp_synq_no_recent_overflow</a>(sk))
<a name="L311" href="source/net/ipv4/syncookies.c#L311">311</a>                 goto <a href="ident?i=out">out</a>;
<a name="L312" href="source/net/ipv4/syncookies.c#L312">312</a> 
<a name="L313" href="source/net/ipv4/syncookies.c#L313">313</a>         mss = <a href="ident?i=__cookie_v4_check">__cookie_v4_check</a>(<a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>), <a href="ident?i=th">th</a>, cookie);
<a name="L314" href="source/net/ipv4/syncookies.c#L314">314</a>         if (mss == 0) {
<a name="L315" href="source/net/ipv4/syncookies.c#L315">315</a>                 <a href="ident?i=NET_INC_STATS_BH">NET_INC_STATS_BH</a>(<a href="ident?i=sock_net">sock_net</a>(sk), LINUX_MIB_SYNCOOKIESFAILED);
<a name="L316" href="source/net/ipv4/syncookies.c#L316">316</a>                 goto <a href="ident?i=out">out</a>;
<a name="L317" href="source/net/ipv4/syncookies.c#L317">317</a>         }
<a name="L318" href="source/net/ipv4/syncookies.c#L318">318</a> 
<a name="L319" href="source/net/ipv4/syncookies.c#L319">319</a>         <a href="ident?i=NET_INC_STATS_BH">NET_INC_STATS_BH</a>(<a href="ident?i=sock_net">sock_net</a>(sk), LINUX_MIB_SYNCOOKIESRECV);
<a name="L320" href="source/net/ipv4/syncookies.c#L320">320</a> 
<a name="L321" href="source/net/ipv4/syncookies.c#L321">321</a>         <b><i>/* check for timestamp cookie support */</i></b>
<a name="L322" href="source/net/ipv4/syncookies.c#L322">322</a>         <a href="ident?i=memset">memset</a>(&amp;tcp_opt, 0, sizeof(tcp_opt));
<a name="L323" href="source/net/ipv4/syncookies.c#L323">323</a>         <a href="ident?i=tcp_parse_options">tcp_parse_options</a>(<a href="ident?i=skb">skb</a>, &amp;tcp_opt, 0, <a href="ident?i=NULL">NULL</a>);
<a name="L324" href="source/net/ipv4/syncookies.c#L324">324</a> 
<a name="L325" href="source/net/ipv4/syncookies.c#L325">325</a>         if (!<a href="ident?i=cookie_timestamp_decode">cookie_timestamp_decode</a>(&amp;tcp_opt))
<a name="L326" href="source/net/ipv4/syncookies.c#L326">326</a>                 goto <a href="ident?i=out">out</a>;
<a name="L327" href="source/net/ipv4/syncookies.c#L327">327</a> 
<a name="L328" href="source/net/ipv4/syncookies.c#L328">328</a>         <a href="ident?i=ret">ret</a> = <a href="ident?i=NULL">NULL</a>;
<a name="L329" href="source/net/ipv4/syncookies.c#L329">329</a>         <a href="ident?i=req">req</a> = <a href="ident?i=inet_reqsk_alloc">inet_reqsk_alloc</a>(&amp;<a href="ident?i=tcp_request_sock_ops">tcp_request_sock_ops</a>, sk); <b><i>/* for safety */</i></b>
<a name="L330" href="source/net/ipv4/syncookies.c#L330">330</a>         if (!<a href="ident?i=req">req</a>)
<a name="L331" href="source/net/ipv4/syncookies.c#L331">331</a>                 goto <a href="ident?i=out">out</a>;
<a name="L332" href="source/net/ipv4/syncookies.c#L332">332</a> 
<a name="L333" href="source/net/ipv4/syncookies.c#L333">333</a>         ireq = <a href="ident?i=inet_rsk">inet_rsk</a>(<a href="ident?i=req">req</a>);
<a name="L334" href="source/net/ipv4/syncookies.c#L334">334</a>         treq = <a href="ident?i=tcp_rsk">tcp_rsk</a>(<a href="ident?i=req">req</a>);
<a name="L335" href="source/net/ipv4/syncookies.c#L335">335</a>         treq-&gt;rcv_isn           = <a href="ident?i=ntohl">ntohl</a>(<a href="ident?i=th">th</a>-&gt;<a href="ident?i=seq">seq</a>) - 1;
<a name="L336" href="source/net/ipv4/syncookies.c#L336">336</a>         treq-&gt;snt_isn           = cookie;
<a name="L337" href="source/net/ipv4/syncookies.c#L337">337</a>         <a href="ident?i=req">req</a>-&gt;mss                = mss;
<a name="L338" href="source/net/ipv4/syncookies.c#L338">338</a>         ireq-&gt;<a href="ident?i=ir_num">ir_num</a>            = <a href="ident?i=ntohs">ntohs</a>(<a href="ident?i=th">th</a>-&gt;<a href="ident?i=dest">dest</a>);
<a name="L339" href="source/net/ipv4/syncookies.c#L339">339</a>         ireq-&gt;<a href="ident?i=ir_rmt_port">ir_rmt_port</a>       = <a href="ident?i=th">th</a>-&gt;source;
<a name="L340" href="source/net/ipv4/syncookies.c#L340">340</a>         <a href="ident?i=sk_rcv_saddr_set">sk_rcv_saddr_set</a>(<a href="ident?i=req_to_sk">req_to_sk</a>(<a href="ident?i=req">req</a>), <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=daddr">daddr</a>);
<a name="L341" href="source/net/ipv4/syncookies.c#L341">341</a>         <a href="ident?i=sk_daddr_set">sk_daddr_set</a>(<a href="ident?i=req_to_sk">req_to_sk</a>(<a href="ident?i=req">req</a>), <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=saddr">saddr</a>);
<a name="L342" href="source/net/ipv4/syncookies.c#L342">342</a>         ireq-&gt;ir_mark           = <a href="ident?i=inet_request_mark">inet_request_mark</a>(sk, <a href="ident?i=skb">skb</a>);
<a name="L343" href="source/net/ipv4/syncookies.c#L343">343</a>         ireq-&gt;snd_wscale        = tcp_opt.snd_wscale;
<a name="L344" href="source/net/ipv4/syncookies.c#L344">344</a>         ireq-&gt;sack_ok           = tcp_opt.sack_ok;
<a name="L345" href="source/net/ipv4/syncookies.c#L345">345</a>         ireq-&gt;wscale_ok         = tcp_opt.wscale_ok;
<a name="L346" href="source/net/ipv4/syncookies.c#L346">346</a>         ireq-&gt;tstamp_ok         = tcp_opt.saw_tstamp;
<a name="L347" href="source/net/ipv4/syncookies.c#L347">347</a>         <a href="ident?i=req">req</a>-&gt;ts_recent          = tcp_opt.saw_tstamp ? tcp_opt.rcv_tsval : 0;
<a name="L348" href="source/net/ipv4/syncookies.c#L348">348</a>         treq-&gt;snt_synack        = tcp_opt.saw_tstamp ? tcp_opt.rcv_tsecr : 0;
<a name="L349" href="source/net/ipv4/syncookies.c#L349">349</a>         treq-&gt;tfo_listener      = <a href="ident?i=false">false</a>;
<a name="L350" href="source/net/ipv4/syncookies.c#L350">350</a> 
<a name="L351" href="source/net/ipv4/syncookies.c#L351">351</a>         ireq-&gt;<a href="ident?i=ir_iif">ir_iif</a> = sk-&gt;<a href="ident?i=sk_bound_dev_if">sk_bound_dev_if</a>;
<a name="L352" href="source/net/ipv4/syncookies.c#L352">352</a> 
<a name="L353" href="source/net/ipv4/syncookies.c#L353">353</a>         <b><i>/* We throwed the options of the initial SYN away, so we hope</i></b>
<a name="L354" href="source/net/ipv4/syncookies.c#L354">354</a> <b><i>         * the ACK carries the same options again (see RFC1122 4.2.3.8)</i></b>
<a name="L355" href="source/net/ipv4/syncookies.c#L355">355</a> <b><i>         */</i></b>
<a name="L356" href="source/net/ipv4/syncookies.c#L356">356</a>         ireq-&gt;opt = <a href="ident?i=tcp_v4_save_options">tcp_v4_save_options</a>(<a href="ident?i=skb">skb</a>);
<a name="L357" href="source/net/ipv4/syncookies.c#L357">357</a> 
<a name="L358" href="source/net/ipv4/syncookies.c#L358">358</a>         if (<a href="ident?i=security_inet_conn_request">security_inet_conn_request</a>(sk, <a href="ident?i=skb">skb</a>, <a href="ident?i=req">req</a>)) {
<a name="L359" href="source/net/ipv4/syncookies.c#L359">359</a>                 <a href="ident?i=reqsk_free">reqsk_free</a>(<a href="ident?i=req">req</a>);
<a name="L360" href="source/net/ipv4/syncookies.c#L360">360</a>                 goto <a href="ident?i=out">out</a>;
<a name="L361" href="source/net/ipv4/syncookies.c#L361">361</a>         }
<a name="L362" href="source/net/ipv4/syncookies.c#L362">362</a> 
<a name="L363" href="source/net/ipv4/syncookies.c#L363">363</a>         <a href="ident?i=req">req</a>-&gt;num_retrans = 0;
<a name="L364" href="source/net/ipv4/syncookies.c#L364">364</a> 
<a name="L365" href="source/net/ipv4/syncookies.c#L365">365</a>         <b><i>/*</i></b>
<a name="L366" href="source/net/ipv4/syncookies.c#L366">366</a> <b><i>         * We need to lookup the route here to get at the correct</i></b>
<a name="L367" href="source/net/ipv4/syncookies.c#L367">367</a> <b><i>         * window size. We should better make sure that the window size</i></b>
<a name="L368" href="source/net/ipv4/syncookies.c#L368">368</a> <b><i>         * hasn't changed since we received the original syn, but I see</i></b>
<a name="L369" href="source/net/ipv4/syncookies.c#L369">369</a> <b><i>         * no easy way to do this.</i></b>
<a name="L370" href="source/net/ipv4/syncookies.c#L370">370</a> <b><i>         */</i></b>
<a name="L371" href="source/net/ipv4/syncookies.c#L371">371</a>         <a href="ident?i=flowi4_init_output">flowi4_init_output</a>(&amp;fl4, sk-&gt;<a href="ident?i=sk_bound_dev_if">sk_bound_dev_if</a>, ireq-&gt;ir_mark,
<a name="L372" href="source/net/ipv4/syncookies.c#L372">372</a>                            <a href="ident?i=RT_CONN_FLAGS">RT_CONN_FLAGS</a>(sk), RT_SCOPE_UNIVERSE, <a href="ident?i=IPPROTO_TCP">IPPROTO_TCP</a>,
<a name="L373" href="source/net/ipv4/syncookies.c#L373">373</a>                            <a href="ident?i=inet_sk_flowi_flags">inet_sk_flowi_flags</a>(sk),
<a name="L374" href="source/net/ipv4/syncookies.c#L374">374</a>                            opt-&gt;<a href="ident?i=srr">srr</a> ? opt-&gt;faddr : ireq-&gt;<a href="ident?i=ir_rmt_addr">ir_rmt_addr</a>,
<a name="L375" href="source/net/ipv4/syncookies.c#L375">375</a>                            ireq-&gt;<a href="ident?i=ir_loc_addr">ir_loc_addr</a>, <a href="ident?i=th">th</a>-&gt;source, <a href="ident?i=th">th</a>-&gt;<a href="ident?i=dest">dest</a>);
<a name="L376" href="source/net/ipv4/syncookies.c#L376">376</a>         <a href="ident?i=security_req_classify_flow">security_req_classify_flow</a>(<a href="ident?i=req">req</a>, <a href="ident?i=flowi4_to_flowi">flowi4_to_flowi</a>(&amp;fl4));
<a name="L377" href="source/net/ipv4/syncookies.c#L377">377</a>         <a href="ident?i=rt">rt</a> = <a href="ident?i=ip_route_output_key">ip_route_output_key</a>(<a href="ident?i=sock_net">sock_net</a>(sk), &amp;fl4);
<a name="L378" href="source/net/ipv4/syncookies.c#L378">378</a>         if (<a href="ident?i=IS_ERR">IS_ERR</a>(<a href="ident?i=rt">rt</a>)) {
<a name="L379" href="source/net/ipv4/syncookies.c#L379">379</a>                 <a href="ident?i=reqsk_free">reqsk_free</a>(<a href="ident?i=req">req</a>);
<a name="L380" href="source/net/ipv4/syncookies.c#L380">380</a>                 goto <a href="ident?i=out">out</a>;
<a name="L381" href="source/net/ipv4/syncookies.c#L381">381</a>         }
<a name="L382" href="source/net/ipv4/syncookies.c#L382">382</a> 
<a name="L383" href="source/net/ipv4/syncookies.c#L383">383</a>         <b><i>/* Try to redo what tcp_v4_send_synack did. */</i></b>
<a name="L384" href="source/net/ipv4/syncookies.c#L384">384</a>         <a href="ident?i=req">req</a>-&gt;window_clamp = <a href="ident?i=tp">tp</a>-&gt;window_clamp ? :<a href="ident?i=dst_metric">dst_metric</a>(&amp;<a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>, <a href="ident?i=RTAX_WINDOW">RTAX_WINDOW</a>);
<a name="L385" href="source/net/ipv4/syncookies.c#L385">385</a> 
<a name="L386" href="source/net/ipv4/syncookies.c#L386">386</a>         <a href="ident?i=tcp_select_initial_window">tcp_select_initial_window</a>(<a href="ident?i=tcp_full_space">tcp_full_space</a>(sk), <a href="ident?i=req">req</a>-&gt;mss,
<a name="L387" href="source/net/ipv4/syncookies.c#L387">387</a>                                   &amp;<a href="ident?i=req">req</a>-&gt;rcv_wnd, &amp;<a href="ident?i=req">req</a>-&gt;window_clamp,
<a name="L388" href="source/net/ipv4/syncookies.c#L388">388</a>                                   ireq-&gt;wscale_ok, &amp;rcv_wscale,
<a name="L389" href="source/net/ipv4/syncookies.c#L389">389</a>                                   <a href="ident?i=dst_metric">dst_metric</a>(&amp;<a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>, <a href="ident?i=RTAX_INITRWND">RTAX_INITRWND</a>));
<a name="L390" href="source/net/ipv4/syncookies.c#L390">390</a> 
<a name="L391" href="source/net/ipv4/syncookies.c#L391">391</a>         ireq-&gt;rcv_wscale  = rcv_wscale;
<a name="L392" href="source/net/ipv4/syncookies.c#L392">392</a>         ireq-&gt;ecn_ok = <a href="ident?i=cookie_ecn_ok">cookie_ecn_ok</a>(&amp;tcp_opt, <a href="ident?i=sock_net">sock_net</a>(sk), &amp;<a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>);
<a name="L393" href="source/net/ipv4/syncookies.c#L393">393</a> 
<a name="L394" href="source/net/ipv4/syncookies.c#L394">394</a>         <a href="ident?i=ret">ret</a> = <a href="ident?i=get_cookie_sock">get_cookie_sock</a>(sk, <a href="ident?i=skb">skb</a>, <a href="ident?i=req">req</a>, &amp;<a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>);
<a name="L395" href="source/net/ipv4/syncookies.c#L395">395</a>         <b><i>/* ip_queue_xmit() depends on our flow being setup</i></b>
<a name="L396" href="source/net/ipv4/syncookies.c#L396">396</a> <b><i>         * Normal sockets get it right from inet_csk_route_child_sock()</i></b>
<a name="L397" href="source/net/ipv4/syncookies.c#L397">397</a> <b><i>         */</i></b>
<a name="L398" href="source/net/ipv4/syncookies.c#L398">398</a>         if (<a href="ident?i=ret">ret</a>)
<a name="L399" href="source/net/ipv4/syncookies.c#L399">399</a>                 <a href="ident?i=inet_sk">inet_sk</a>(<a href="ident?i=ret">ret</a>)-&gt;cork.fl.u.ip4 = fl4;
<a name="L400" href="source/net/ipv4/syncookies.c#L400">400</a> <a href="ident?i=out">out</a>:    return <a href="ident?i=ret">ret</a>;
<a name="L401" href="source/net/ipv4/syncookies.c#L401">401</a> }
<a name="L402" href="source/net/ipv4/syncookies.c#L402">402</a> </pre></div><p>
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
