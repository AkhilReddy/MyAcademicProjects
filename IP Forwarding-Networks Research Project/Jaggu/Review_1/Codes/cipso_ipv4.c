<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title>Linux/net/ipv4/cipso_ipv4.c - Linux Cross Reference - Free Electrons</title>
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
		 &nbsp;&bull;&nbsp;<b><i>source navigation</i></b> &nbsp;&bull;&nbsp;<a href="diff/net/ipv4/cipso_ipv4.c">diff markup</a> &nbsp;&bull;&nbsp;<a href="ident">identifier search</a> &nbsp;&bull;&nbsp;<a href="search">freetext search</a> &nbsp;&bull;&nbsp;
		</p>
	</div>
</div>

<div id="topbar">
  
  <p>Version: &nbsp;<a href="source/net/ipv4/cipso_ipv4.c?v=2.0.40">2.0.40</a>&nbsp;<a href="source/net/ipv4/cipso_ipv4.c?v=2.2.26">2.2.26</a>&nbsp;<a href="source/net/ipv4/cipso_ipv4.c?v=2.4.37">2.4.37</a>&nbsp;<a href="source/net/ipv4/cipso_ipv4.c?v=3.5">3.5</a>&nbsp;<a href="source/net/ipv4/cipso_ipv4.c?v=3.6">3.6</a>&nbsp;<a href="source/net/ipv4/cipso_ipv4.c?v=3.7">3.7</a>&nbsp;<a href="source/net/ipv4/cipso_ipv4.c?v=3.8">3.8</a>&nbsp;<a href="source/net/ipv4/cipso_ipv4.c?v=3.9">3.9</a>&nbsp;<a href="source/net/ipv4/cipso_ipv4.c?v=3.10">3.10</a>&nbsp;<a href="source/net/ipv4/cipso_ipv4.c?v=3.11">3.11</a>&nbsp;<a href="source/net/ipv4/cipso_ipv4.c?v=3.12">3.12</a>&nbsp;<a href="source/net/ipv4/cipso_ipv4.c?v=3.13">3.13</a>&nbsp;<a href="source/net/ipv4/cipso_ipv4.c?v=3.14">3.14</a>&nbsp;<a href="source/net/ipv4/cipso_ipv4.c?v=3.15">3.15</a>&nbsp;<a href="source/net/ipv4/cipso_ipv4.c?v=3.16">3.16</a>&nbsp;<a href="source/net/ipv4/cipso_ipv4.c?v=3.17">3.17</a>&nbsp;<a href="source/net/ipv4/cipso_ipv4.c?v=3.18">3.18</a>&nbsp;<a href="source/net/ipv4/cipso_ipv4.c?v=3.19">3.19</a>&nbsp;<a href="source/net/ipv4/cipso_ipv4.c?v=4.0">4.0</a>&nbsp;<b><i>4.1</i></b></p>
  
</div>

<h1><a href="source/">Linux</a>/<a href="source/net/">net</a>/<a href="source/net/ipv4/">ipv4</a>/<a href="source/net/ipv4/cipso_ipv4.c">cipso_ipv4.c</a></h1>
<div id="lxrcode"><pre>  <a name="L1" href="source/net/ipv4/cipso_ipv4.c#L1">1</a> <b><i>/*</i></b>
  <a name="L2" href="source/net/ipv4/cipso_ipv4.c#L2">2</a> <b><i> * CIPSO - Commercial IP Security Option</i></b>
  <a name="L3" href="source/net/ipv4/cipso_ipv4.c#L3">3</a> <b><i> *</i></b>
  <a name="L4" href="source/net/ipv4/cipso_ipv4.c#L4">4</a> <b><i> * This is an implementation of the CIPSO 2.2 protocol as specified in</i></b>
  <a name="L5" href="source/net/ipv4/cipso_ipv4.c#L5">5</a> <b><i> * draft-ietf-cipso-ipsecurity-01.txt with additional tag types as found in</i></b>
  <a name="L6" href="source/net/ipv4/cipso_ipv4.c#L6">6</a> <b><i> * FIPS-188.  While CIPSO never became a full IETF RFC standard many vendors</i></b>
  <a name="L7" href="source/net/ipv4/cipso_ipv4.c#L7">7</a> <b><i> * have chosen to adopt the protocol and over the years it has become a</i></b>
  <a name="L8" href="source/net/ipv4/cipso_ipv4.c#L8">8</a> <b><i> * de-facto standard for labeled networking.</i></b>
  <a name="L9" href="source/net/ipv4/cipso_ipv4.c#L9">9</a> <b><i> *</i></b>
 <a name="L10" href="source/net/ipv4/cipso_ipv4.c#L10">10</a> <b><i> * The CIPSO draft specification can be found in the kernel's Documentation</i></b>
 <a name="L11" href="source/net/ipv4/cipso_ipv4.c#L11">11</a> <b><i> * directory as well as the following URL:</i></b>
 <a name="L12" href="source/net/ipv4/cipso_ipv4.c#L12">12</a> <b><i> *   <a href="http://tools.ietf.org/id/draft-ietf-cipso-ipsecurity-01.txt">http://tools.ietf.org/id/draft-ietf-cipso-ipsecurity-01.txt</a></i></b>
 <a name="L13" href="source/net/ipv4/cipso_ipv4.c#L13">13</a> <b><i> * The FIPS-188 specification can be found at the following URL:</i></b>
 <a name="L14" href="source/net/ipv4/cipso_ipv4.c#L14">14</a> <b><i> *   <a href="http://www.itl.nist.gov/fipspubs/fip188.htm">http://www.itl.nist.gov/fipspubs/fip188.htm</a></i></b>
 <a name="L15" href="source/net/ipv4/cipso_ipv4.c#L15">15</a> <b><i> *</i></b>
 <a name="L16" href="source/net/ipv4/cipso_ipv4.c#L16">16</a> <b><i> * Author: Paul Moore &lt;paul.moore@hp.com&gt;</i></b>
 <a name="L17" href="source/net/ipv4/cipso_ipv4.c#L17">17</a> <b><i> *</i></b>
 <a name="L18" href="source/net/ipv4/cipso_ipv4.c#L18">18</a> <b><i> */</i></b>
 <a name="L19" href="source/net/ipv4/cipso_ipv4.c#L19">19</a> 
 <a name="L20" href="source/net/ipv4/cipso_ipv4.c#L20">20</a> <b><i>/*</i></b>
 <a name="L21" href="source/net/ipv4/cipso_ipv4.c#L21">21</a> <b><i> * (c) Copyright Hewlett-Packard Development Company, L.P., 2006, 2008</i></b>
 <a name="L22" href="source/net/ipv4/cipso_ipv4.c#L22">22</a> <b><i> *</i></b>
 <a name="L23" href="source/net/ipv4/cipso_ipv4.c#L23">23</a> <b><i> * This program is free software;  you can redistribute it and/or modify</i></b>
 <a name="L24" href="source/net/ipv4/cipso_ipv4.c#L24">24</a> <b><i> * it under the terms of the GNU General Public License as published by</i></b>
 <a name="L25" href="source/net/ipv4/cipso_ipv4.c#L25">25</a> <b><i> * the Free Software Foundation; either version 2 of the License, or</i></b>
 <a name="L26" href="source/net/ipv4/cipso_ipv4.c#L26">26</a> <b><i> * (at your option) any later version.</i></b>
 <a name="L27" href="source/net/ipv4/cipso_ipv4.c#L27">27</a> <b><i> *</i></b>
 <a name="L28" href="source/net/ipv4/cipso_ipv4.c#L28">28</a> <b><i> * This program is distributed in the hope that it will be useful,</i></b>
 <a name="L29" href="source/net/ipv4/cipso_ipv4.c#L29">29</a> <b><i> * but WITHOUT ANY WARRANTY;  without even the implied warranty of</i></b>
 <a name="L30" href="source/net/ipv4/cipso_ipv4.c#L30">30</a> <b><i> * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See</i></b>
 <a name="L31" href="source/net/ipv4/cipso_ipv4.c#L31">31</a> <b><i> * the GNU General Public License for more details.</i></b>
 <a name="L32" href="source/net/ipv4/cipso_ipv4.c#L32">32</a> <b><i> *</i></b>
 <a name="L33" href="source/net/ipv4/cipso_ipv4.c#L33">33</a> <b><i> * You should have received a copy of the GNU General Public License</i></b>
 <a name="L34" href="source/net/ipv4/cipso_ipv4.c#L34">34</a> <b><i> * along with this program;  if not, see &lt;<a href="http://www.gnu.org/licenses/&gt;">http://www.gnu.org/licenses/&gt;</a>.</i></b>
 <a name="L35" href="source/net/ipv4/cipso_ipv4.c#L35">35</a> <b><i> *</i></b>
 <a name="L36" href="source/net/ipv4/cipso_ipv4.c#L36">36</a> <b><i> */</i></b>
 <a name="L37" href="source/net/ipv4/cipso_ipv4.c#L37">37</a> 
 <a name="L38" href="source/net/ipv4/cipso_ipv4.c#L38">38</a> #include &lt;linux/init.h&gt;
 <a name="L39" href="source/net/ipv4/cipso_ipv4.c#L39">39</a> #include &lt;linux/types.h&gt;
 <a name="L40" href="source/net/ipv4/cipso_ipv4.c#L40">40</a> #include &lt;linux/rcupdate.h&gt;
 <a name="L41" href="source/net/ipv4/cipso_ipv4.c#L41">41</a> #include &lt;linux/list.h&gt;
 <a name="L42" href="source/net/ipv4/cipso_ipv4.c#L42">42</a> #include &lt;linux/spinlock.h&gt;
 <a name="L43" href="source/net/ipv4/cipso_ipv4.c#L43">43</a> #include &lt;linux/string.h&gt;
 <a name="L44" href="source/net/ipv4/cipso_ipv4.c#L44">44</a> #include &lt;linux/jhash.h&gt;
 <a name="L45" href="source/net/ipv4/cipso_ipv4.c#L45">45</a> #include &lt;linux/audit.h&gt;
 <a name="L46" href="source/net/ipv4/cipso_ipv4.c#L46">46</a> #include &lt;linux/slab.h&gt;
 <a name="L47" href="source/net/ipv4/cipso_ipv4.c#L47">47</a> #include &lt;net/ip.h&gt;
 <a name="L48" href="source/net/ipv4/cipso_ipv4.c#L48">48</a> #include &lt;net/icmp.h&gt;
 <a name="L49" href="source/net/ipv4/cipso_ipv4.c#L49">49</a> #include &lt;net/tcp.h&gt;
 <a name="L50" href="source/net/ipv4/cipso_ipv4.c#L50">50</a> #include &lt;net/netlabel.h&gt;
 <a name="L51" href="source/net/ipv4/cipso_ipv4.c#L51">51</a> #include &lt;net/cipso_ipv4.h&gt;
 <a name="L52" href="source/net/ipv4/cipso_ipv4.c#L52">52</a> #include &lt;linux/atomic.h&gt;
 <a name="L53" href="source/net/ipv4/cipso_ipv4.c#L53">53</a> #include &lt;linux/bug.h&gt;
 <a name="L54" href="source/net/ipv4/cipso_ipv4.c#L54">54</a> #include &lt;asm/unaligned.h&gt;
 <a name="L55" href="source/net/ipv4/cipso_ipv4.c#L55">55</a> 
 <a name="L56" href="source/net/ipv4/cipso_ipv4.c#L56">56</a> <b><i>/* List of available DOI definitions */</i></b>
 <a name="L57" href="source/net/ipv4/cipso_ipv4.c#L57">57</a> <b><i>/* XXX - This currently assumes a minimal number of different DOIs in use,</i></b>
 <a name="L58" href="source/net/ipv4/cipso_ipv4.c#L58">58</a> <b><i> * if in practice there are a lot of different DOIs this list should</i></b>
 <a name="L59" href="source/net/ipv4/cipso_ipv4.c#L59">59</a> <b><i> * probably be turned into a hash table or something similar so we</i></b>
 <a name="L60" href="source/net/ipv4/cipso_ipv4.c#L60">60</a> <b><i> * can do quick lookups. */</i></b>
 <a name="L61" href="source/net/ipv4/cipso_ipv4.c#L61">61</a> static <a href="ident?i=DEFINE_SPINLOCK">DEFINE_SPINLOCK</a>(cipso_v4_doi_list_lock);
 <a name="L62" href="source/net/ipv4/cipso_ipv4.c#L62">62</a> static <a href="ident?i=LIST_HEAD">LIST_HEAD</a>(cipso_v4_doi_list);
 <a name="L63" href="source/net/ipv4/cipso_ipv4.c#L63">63</a> 
 <a name="L64" href="source/net/ipv4/cipso_ipv4.c#L64">64</a> <b><i>/* Label mapping cache */</i></b>
 <a name="L65" href="source/net/ipv4/cipso_ipv4.c#L65">65</a> int <a href="ident?i=cipso_v4_cache_enabled">cipso_v4_cache_enabled</a> = 1;
 <a name="L66" href="source/net/ipv4/cipso_ipv4.c#L66">66</a> int <a href="ident?i=cipso_v4_cache_bucketsize">cipso_v4_cache_bucketsize</a> = 10;
 <a name="L67" href="source/net/ipv4/cipso_ipv4.c#L67">67</a> #define <a href="ident?i=CIPSO_V4_CACHE_BUCKETBITS">CIPSO_V4_CACHE_BUCKETBITS</a>     7
 <a name="L68" href="source/net/ipv4/cipso_ipv4.c#L68">68</a> #define <a href="ident?i=CIPSO_V4_CACHE_BUCKETS">CIPSO_V4_CACHE_BUCKETS</a>        (1 &lt;&lt; <a href="ident?i=CIPSO_V4_CACHE_BUCKETBITS">CIPSO_V4_CACHE_BUCKETBITS</a>)
 <a name="L69" href="source/net/ipv4/cipso_ipv4.c#L69">69</a> #define <a href="ident?i=CIPSO_V4_CACHE_REORDERLIMIT">CIPSO_V4_CACHE_REORDERLIMIT</a>   10
 <a name="L70" href="source/net/ipv4/cipso_ipv4.c#L70">70</a> struct <a href="ident?i=cipso_v4_map_cache_bkt">cipso_v4_map_cache_bkt</a> {
 <a name="L71" href="source/net/ipv4/cipso_ipv4.c#L71">71</a>         <a href="ident?i=spinlock_t">spinlock_t</a> <a href="ident?i=lock">lock</a>;
 <a name="L72" href="source/net/ipv4/cipso_ipv4.c#L72">72</a>         <a href="ident?i=u32">u32</a> <a href="ident?i=size">size</a>;
 <a name="L73" href="source/net/ipv4/cipso_ipv4.c#L73">73</a>         struct <a href="ident?i=list_head">list_head</a> <a href="ident?i=list">list</a>;
 <a name="L74" href="source/net/ipv4/cipso_ipv4.c#L74">74</a> };
 <a name="L75" href="source/net/ipv4/cipso_ipv4.c#L75">75</a> 
 <a name="L76" href="source/net/ipv4/cipso_ipv4.c#L76">76</a> struct <a href="ident?i=cipso_v4_map_cache_entry">cipso_v4_map_cache_entry</a> {
 <a name="L77" href="source/net/ipv4/cipso_ipv4.c#L77">77</a>         <a href="ident?i=u32">u32</a> <a href="ident?i=hash">hash</a>;
 <a name="L78" href="source/net/ipv4/cipso_ipv4.c#L78">78</a>         unsigned char *<a href="ident?i=key">key</a>;
 <a name="L79" href="source/net/ipv4/cipso_ipv4.c#L79">79</a>         <a href="ident?i=size_t">size_t</a> <a href="ident?i=key_len">key_len</a>;
 <a name="L80" href="source/net/ipv4/cipso_ipv4.c#L80">80</a> 
 <a name="L81" href="source/net/ipv4/cipso_ipv4.c#L81">81</a>         struct <a href="ident?i=netlbl_lsm_cache">netlbl_lsm_cache</a> *lsm_data;
 <a name="L82" href="source/net/ipv4/cipso_ipv4.c#L82">82</a> 
 <a name="L83" href="source/net/ipv4/cipso_ipv4.c#L83">83</a>         <a href="ident?i=u32">u32</a> activity;
 <a name="L84" href="source/net/ipv4/cipso_ipv4.c#L84">84</a>         struct <a href="ident?i=list_head">list_head</a> <a href="ident?i=list">list</a>;
 <a name="L85" href="source/net/ipv4/cipso_ipv4.c#L85">85</a> };
 <a name="L86" href="source/net/ipv4/cipso_ipv4.c#L86">86</a> 
 <a name="L87" href="source/net/ipv4/cipso_ipv4.c#L87">87</a> static struct <a href="ident?i=cipso_v4_map_cache_bkt">cipso_v4_map_cache_bkt</a> *<a href="ident?i=cipso_v4_cache">cipso_v4_cache</a>;
 <a name="L88" href="source/net/ipv4/cipso_ipv4.c#L88">88</a> 
 <a name="L89" href="source/net/ipv4/cipso_ipv4.c#L89">89</a> <b><i>/* Restricted bitmap (tag #1) flags */</i></b>
 <a name="L90" href="source/net/ipv4/cipso_ipv4.c#L90">90</a> int <a href="ident?i=cipso_v4_rbm_optfmt">cipso_v4_rbm_optfmt</a> = 0;
 <a name="L91" href="source/net/ipv4/cipso_ipv4.c#L91">91</a> int <a href="ident?i=cipso_v4_rbm_strictvalid">cipso_v4_rbm_strictvalid</a> = 1;
 <a name="L92" href="source/net/ipv4/cipso_ipv4.c#L92">92</a> 
 <a name="L93" href="source/net/ipv4/cipso_ipv4.c#L93">93</a> <b><i>/*</i></b>
 <a name="L94" href="source/net/ipv4/cipso_ipv4.c#L94">94</a> <b><i> * Protocol Constants</i></b>
 <a name="L95" href="source/net/ipv4/cipso_ipv4.c#L95">95</a> <b><i> */</i></b>
 <a name="L96" href="source/net/ipv4/cipso_ipv4.c#L96">96</a> 
 <a name="L97" href="source/net/ipv4/cipso_ipv4.c#L97">97</a> <b><i>/* Maximum size of the CIPSO IP option, derived from the fact that the maximum</i></b>
 <a name="L98" href="source/net/ipv4/cipso_ipv4.c#L98">98</a> <b><i> * IPv4 header size is 60 bytes and the base IPv4 header is 20 bytes long. */</i></b>
 <a name="L99" href="source/net/ipv4/cipso_ipv4.c#L99">99</a> #define <a href="ident?i=CIPSO_V4_OPT_LEN_MAX">CIPSO_V4_OPT_LEN_MAX</a>          40
<a name="L100" href="source/net/ipv4/cipso_ipv4.c#L100">100</a> 
<a name="L101" href="source/net/ipv4/cipso_ipv4.c#L101">101</a> <b><i>/* Length of the base CIPSO option, this includes the option type (1 byte), the</i></b>
<a name="L102" href="source/net/ipv4/cipso_ipv4.c#L102">102</a> <b><i> * option length (1 byte), and the DOI (4 bytes). */</i></b>
<a name="L103" href="source/net/ipv4/cipso_ipv4.c#L103">103</a> #define <a href="ident?i=CIPSO_V4_HDR_LEN">CIPSO_V4_HDR_LEN</a>              6
<a name="L104" href="source/net/ipv4/cipso_ipv4.c#L104">104</a> 
<a name="L105" href="source/net/ipv4/cipso_ipv4.c#L105">105</a> <b><i>/* Base length of the restrictive category bitmap tag (tag #1). */</i></b>
<a name="L106" href="source/net/ipv4/cipso_ipv4.c#L106">106</a> #define <a href="ident?i=CIPSO_V4_TAG_RBM_BLEN">CIPSO_V4_TAG_RBM_BLEN</a>         4
<a name="L107" href="source/net/ipv4/cipso_ipv4.c#L107">107</a> 
<a name="L108" href="source/net/ipv4/cipso_ipv4.c#L108">108</a> <b><i>/* Base length of the enumerated category tag (tag #2). */</i></b>
<a name="L109" href="source/net/ipv4/cipso_ipv4.c#L109">109</a> #define <a href="ident?i=CIPSO_V4_TAG_ENUM_BLEN">CIPSO_V4_TAG_ENUM_BLEN</a>        4
<a name="L110" href="source/net/ipv4/cipso_ipv4.c#L110">110</a> 
<a name="L111" href="source/net/ipv4/cipso_ipv4.c#L111">111</a> <b><i>/* Base length of the ranged categories bitmap tag (tag #5). */</i></b>
<a name="L112" href="source/net/ipv4/cipso_ipv4.c#L112">112</a> #define <a href="ident?i=CIPSO_V4_TAG_RNG_BLEN">CIPSO_V4_TAG_RNG_BLEN</a>         4
<a name="L113" href="source/net/ipv4/cipso_ipv4.c#L113">113</a> <b><i>/* The maximum number of category ranges permitted in the ranged category tag</i></b>
<a name="L114" href="source/net/ipv4/cipso_ipv4.c#L114">114</a> <b><i> * (tag #5).  You may note that the IETF draft states that the maximum number</i></b>
<a name="L115" href="source/net/ipv4/cipso_ipv4.c#L115">115</a> <b><i> * of category ranges is 7, but if the low end of the last category range is</i></b>
<a name="L116" href="source/net/ipv4/cipso_ipv4.c#L116">116</a> <b><i> * zero then it is possible to fit 8 category ranges because the zero should</i></b>
<a name="L117" href="source/net/ipv4/cipso_ipv4.c#L117">117</a> <b><i> * be omitted. */</i></b>
<a name="L118" href="source/net/ipv4/cipso_ipv4.c#L118">118</a> #define <a href="ident?i=CIPSO_V4_TAG_RNG_CAT_MAX">CIPSO_V4_TAG_RNG_CAT_MAX</a>      8
<a name="L119" href="source/net/ipv4/cipso_ipv4.c#L119">119</a> 
<a name="L120" href="source/net/ipv4/cipso_ipv4.c#L120">120</a> <b><i>/* Base length of the local tag (non-standard tag).</i></b>
<a name="L121" href="source/net/ipv4/cipso_ipv4.c#L121">121</a> <b><i> *  Tag definition (may change between kernel versions)</i></b>
<a name="L122" href="source/net/ipv4/cipso_ipv4.c#L122">122</a> <b><i> *</i></b>
<a name="L123" href="source/net/ipv4/cipso_ipv4.c#L123">123</a> <b><i> * 0          8          16         24         32</i></b>
<a name="L124" href="source/net/ipv4/cipso_ipv4.c#L124">124</a> <b><i> * +----------+----------+----------+----------+</i></b>
<a name="L125" href="source/net/ipv4/cipso_ipv4.c#L125">125</a> <b><i> * | 10000000 | 00000110 | 32-bit secid value  |</i></b>
<a name="L126" href="source/net/ipv4/cipso_ipv4.c#L126">126</a> <b><i> * +----------+----------+----------+----------+</i></b>
<a name="L127" href="source/net/ipv4/cipso_ipv4.c#L127">127</a> <b><i> * | in (host byte order)|</i></b>
<a name="L128" href="source/net/ipv4/cipso_ipv4.c#L128">128</a> <b><i> * +----------+----------+</i></b>
<a name="L129" href="source/net/ipv4/cipso_ipv4.c#L129">129</a> <b><i> *</i></b>
<a name="L130" href="source/net/ipv4/cipso_ipv4.c#L130">130</a> <b><i> */</i></b>
<a name="L131" href="source/net/ipv4/cipso_ipv4.c#L131">131</a> #define <a href="ident?i=CIPSO_V4_TAG_LOC_BLEN">CIPSO_V4_TAG_LOC_BLEN</a>         6
<a name="L132" href="source/net/ipv4/cipso_ipv4.c#L132">132</a> 
<a name="L133" href="source/net/ipv4/cipso_ipv4.c#L133">133</a> <b><i>/*</i></b>
<a name="L134" href="source/net/ipv4/cipso_ipv4.c#L134">134</a> <b><i> * Helper Functions</i></b>
<a name="L135" href="source/net/ipv4/cipso_ipv4.c#L135">135</a> <b><i> */</i></b>
<a name="L136" href="source/net/ipv4/cipso_ipv4.c#L136">136</a> 
<a name="L137" href="source/net/ipv4/cipso_ipv4.c#L137">137</a> <b><i>/**</i></b>
<a name="L138" href="source/net/ipv4/cipso_ipv4.c#L138">138</a> <b><i> * cipso_v4_bitmap_walk - Walk a bitmap looking for a bit</i></b>
<a name="L139" href="source/net/ipv4/cipso_ipv4.c#L139">139</a> <b><i> * @bitmap: the bitmap</i></b>
<a name="L140" href="source/net/ipv4/cipso_ipv4.c#L140">140</a> <b><i> * @bitmap_len: length in bits</i></b>
<a name="L141" href="source/net/ipv4/cipso_ipv4.c#L141">141</a> <b><i> * @offset: starting offset</i></b>
<a name="L142" href="source/net/ipv4/cipso_ipv4.c#L142">142</a> <b><i> * @state: if non-zero, look for a set (1) bit else look for a cleared (0) bit</i></b>
<a name="L143" href="source/net/ipv4/cipso_ipv4.c#L143">143</a> <b><i> *</i></b>
<a name="L144" href="source/net/ipv4/cipso_ipv4.c#L144">144</a> <b><i> * Description:</i></b>
<a name="L145" href="source/net/ipv4/cipso_ipv4.c#L145">145</a> <b><i> * Starting at @offset, walk the bitmap from left to right until either the</i></b>
<a name="L146" href="source/net/ipv4/cipso_ipv4.c#L146">146</a> <b><i> * desired bit is found or we reach the end.  Return the bit offset, -1 if</i></b>
<a name="L147" href="source/net/ipv4/cipso_ipv4.c#L147">147</a> <b><i> * not found, or -2 if error.</i></b>
<a name="L148" href="source/net/ipv4/cipso_ipv4.c#L148">148</a> <b><i> */</i></b>
<a name="L149" href="source/net/ipv4/cipso_ipv4.c#L149">149</a> static int <a href="ident?i=cipso_v4_bitmap_walk">cipso_v4_bitmap_walk</a>(const unsigned char *<a href="ident?i=bitmap">bitmap</a>,
<a name="L150" href="source/net/ipv4/cipso_ipv4.c#L150">150</a>                                 <a href="ident?i=u32">u32</a> bitmap_len,
<a name="L151" href="source/net/ipv4/cipso_ipv4.c#L151">151</a>                                 <a href="ident?i=u32">u32</a> <a href="ident?i=offset">offset</a>,
<a name="L152" href="source/net/ipv4/cipso_ipv4.c#L152">152</a>                                 <a href="ident?i=u8">u8</a> <a href="ident?i=state">state</a>)
<a name="L153" href="source/net/ipv4/cipso_ipv4.c#L153">153</a> {
<a name="L154" href="source/net/ipv4/cipso_ipv4.c#L154">154</a>         <a href="ident?i=u32">u32</a> bit_spot;
<a name="L155" href="source/net/ipv4/cipso_ipv4.c#L155">155</a>         <a href="ident?i=u32">u32</a> byte_offset;
<a name="L156" href="source/net/ipv4/cipso_ipv4.c#L156">156</a>         unsigned char <a href="ident?i=bitmask">bitmask</a>;
<a name="L157" href="source/net/ipv4/cipso_ipv4.c#L157">157</a>         unsigned char <a href="ident?i=byte">byte</a>;
<a name="L158" href="source/net/ipv4/cipso_ipv4.c#L158">158</a> 
<a name="L159" href="source/net/ipv4/cipso_ipv4.c#L159">159</a>         <b><i>/* gcc always rounds to zero when doing integer division */</i></b>
<a name="L160" href="source/net/ipv4/cipso_ipv4.c#L160">160</a>         byte_offset = <a href="ident?i=offset">offset</a> / 8;
<a name="L161" href="source/net/ipv4/cipso_ipv4.c#L161">161</a>         <a href="ident?i=byte">byte</a> = <a href="ident?i=bitmap">bitmap</a>[byte_offset];
<a name="L162" href="source/net/ipv4/cipso_ipv4.c#L162">162</a>         bit_spot = <a href="ident?i=offset">offset</a>;
<a name="L163" href="source/net/ipv4/cipso_ipv4.c#L163">163</a>         <a href="ident?i=bitmask">bitmask</a> = 0x80 &gt;&gt; (<a href="ident?i=offset">offset</a> % 8);
<a name="L164" href="source/net/ipv4/cipso_ipv4.c#L164">164</a> 
<a name="L165" href="source/net/ipv4/cipso_ipv4.c#L165">165</a>         while (bit_spot &lt; bitmap_len) {
<a name="L166" href="source/net/ipv4/cipso_ipv4.c#L166">166</a>                 if ((<a href="ident?i=state">state</a> &amp;&amp; (<a href="ident?i=byte">byte</a> &amp; <a href="ident?i=bitmask">bitmask</a>) == <a href="ident?i=bitmask">bitmask</a>) ||
<a name="L167" href="source/net/ipv4/cipso_ipv4.c#L167">167</a>                     (<a href="ident?i=state">state</a> == 0 &amp;&amp; (<a href="ident?i=byte">byte</a> &amp; <a href="ident?i=bitmask">bitmask</a>) == 0))
<a name="L168" href="source/net/ipv4/cipso_ipv4.c#L168">168</a>                         return bit_spot;
<a name="L169" href="source/net/ipv4/cipso_ipv4.c#L169">169</a> 
<a name="L170" href="source/net/ipv4/cipso_ipv4.c#L170">170</a>                 bit_spot++;
<a name="L171" href="source/net/ipv4/cipso_ipv4.c#L171">171</a>                 <a href="ident?i=bitmask">bitmask</a> &gt;&gt;= 1;
<a name="L172" href="source/net/ipv4/cipso_ipv4.c#L172">172</a>                 if (<a href="ident?i=bitmask">bitmask</a> == 0) {
<a name="L173" href="source/net/ipv4/cipso_ipv4.c#L173">173</a>                         <a href="ident?i=byte">byte</a> = <a href="ident?i=bitmap">bitmap</a>[++byte_offset];
<a name="L174" href="source/net/ipv4/cipso_ipv4.c#L174">174</a>                         <a href="ident?i=bitmask">bitmask</a> = 0x80;
<a name="L175" href="source/net/ipv4/cipso_ipv4.c#L175">175</a>                 }
<a name="L176" href="source/net/ipv4/cipso_ipv4.c#L176">176</a>         }
<a name="L177" href="source/net/ipv4/cipso_ipv4.c#L177">177</a> 
<a name="L178" href="source/net/ipv4/cipso_ipv4.c#L178">178</a>         return -1;
<a name="L179" href="source/net/ipv4/cipso_ipv4.c#L179">179</a> }
<a name="L180" href="source/net/ipv4/cipso_ipv4.c#L180">180</a> 
<a name="L181" href="source/net/ipv4/cipso_ipv4.c#L181">181</a> <b><i>/**</i></b>
<a name="L182" href="source/net/ipv4/cipso_ipv4.c#L182">182</a> <b><i> * cipso_v4_bitmap_setbit - Sets a single bit in a bitmap</i></b>
<a name="L183" href="source/net/ipv4/cipso_ipv4.c#L183">183</a> <b><i> * @bitmap: the bitmap</i></b>
<a name="L184" href="source/net/ipv4/cipso_ipv4.c#L184">184</a> <b><i> * @bit: the bit</i></b>
<a name="L185" href="source/net/ipv4/cipso_ipv4.c#L185">185</a> <b><i> * @state: if non-zero, set the bit (1) else clear the bit (0)</i></b>
<a name="L186" href="source/net/ipv4/cipso_ipv4.c#L186">186</a> <b><i> *</i></b>
<a name="L187" href="source/net/ipv4/cipso_ipv4.c#L187">187</a> <b><i> * Description:</i></b>
<a name="L188" href="source/net/ipv4/cipso_ipv4.c#L188">188</a> <b><i> * Set a single bit in the bitmask.  Returns zero on success, negative values</i></b>
<a name="L189" href="source/net/ipv4/cipso_ipv4.c#L189">189</a> <b><i> * on error.</i></b>
<a name="L190" href="source/net/ipv4/cipso_ipv4.c#L190">190</a> <b><i> */</i></b>
<a name="L191" href="source/net/ipv4/cipso_ipv4.c#L191">191</a> static void <a href="ident?i=cipso_v4_bitmap_setbit">cipso_v4_bitmap_setbit</a>(unsigned char *<a href="ident?i=bitmap">bitmap</a>,
<a name="L192" href="source/net/ipv4/cipso_ipv4.c#L192">192</a>                                    <a href="ident?i=u32">u32</a> <a href="ident?i=bit">bit</a>,
<a name="L193" href="source/net/ipv4/cipso_ipv4.c#L193">193</a>                                    <a href="ident?i=u8">u8</a> <a href="ident?i=state">state</a>)
<a name="L194" href="source/net/ipv4/cipso_ipv4.c#L194">194</a> {
<a name="L195" href="source/net/ipv4/cipso_ipv4.c#L195">195</a>         <a href="ident?i=u32">u32</a> byte_spot;
<a name="L196" href="source/net/ipv4/cipso_ipv4.c#L196">196</a>         <a href="ident?i=u8">u8</a> <a href="ident?i=bitmask">bitmask</a>;
<a name="L197" href="source/net/ipv4/cipso_ipv4.c#L197">197</a> 
<a name="L198" href="source/net/ipv4/cipso_ipv4.c#L198">198</a>         <b><i>/* gcc always rounds to zero when doing integer division */</i></b>
<a name="L199" href="source/net/ipv4/cipso_ipv4.c#L199">199</a>         byte_spot = <a href="ident?i=bit">bit</a> / 8;
<a name="L200" href="source/net/ipv4/cipso_ipv4.c#L200">200</a>         <a href="ident?i=bitmask">bitmask</a> = 0x80 &gt;&gt; (<a href="ident?i=bit">bit</a> % 8);
<a name="L201" href="source/net/ipv4/cipso_ipv4.c#L201">201</a>         if (<a href="ident?i=state">state</a>)
<a name="L202" href="source/net/ipv4/cipso_ipv4.c#L202">202</a>                 <a href="ident?i=bitmap">bitmap</a>[byte_spot] |= <a href="ident?i=bitmask">bitmask</a>;
<a name="L203" href="source/net/ipv4/cipso_ipv4.c#L203">203</a>         else
<a name="L204" href="source/net/ipv4/cipso_ipv4.c#L204">204</a>                 <a href="ident?i=bitmap">bitmap</a>[byte_spot] &amp;= ~bitmask;
<a name="L205" href="source/net/ipv4/cipso_ipv4.c#L205">205</a> }
<a name="L206" href="source/net/ipv4/cipso_ipv4.c#L206">206</a> 
<a name="L207" href="source/net/ipv4/cipso_ipv4.c#L207">207</a> <b><i>/**</i></b>
<a name="L208" href="source/net/ipv4/cipso_ipv4.c#L208">208</a> <b><i> * cipso_v4_cache_entry_free - Frees a cache entry</i></b>
<a name="L209" href="source/net/ipv4/cipso_ipv4.c#L209">209</a> <b><i> * @entry: the entry to free</i></b>
<a name="L210" href="source/net/ipv4/cipso_ipv4.c#L210">210</a> <b><i> *</i></b>
<a name="L211" href="source/net/ipv4/cipso_ipv4.c#L211">211</a> <b><i> * Description:</i></b>
<a name="L212" href="source/net/ipv4/cipso_ipv4.c#L212">212</a> <b><i> * This function frees the memory associated with a cache entry including the</i></b>
<a name="L213" href="source/net/ipv4/cipso_ipv4.c#L213">213</a> <b><i> * LSM cache data if there are no longer any users, i.e. reference count == 0.</i></b>
<a name="L214" href="source/net/ipv4/cipso_ipv4.c#L214">214</a> <b><i> *</i></b>
<a name="L215" href="source/net/ipv4/cipso_ipv4.c#L215">215</a> <b><i> */</i></b>
<a name="L216" href="source/net/ipv4/cipso_ipv4.c#L216">216</a> static void <a href="ident?i=cipso_v4_cache_entry_free">cipso_v4_cache_entry_free</a>(struct <a href="ident?i=cipso_v4_map_cache_entry">cipso_v4_map_cache_entry</a> *<a href="ident?i=entry">entry</a>)
<a name="L217" href="source/net/ipv4/cipso_ipv4.c#L217">217</a> {
<a name="L218" href="source/net/ipv4/cipso_ipv4.c#L218">218</a>         if (<a href="ident?i=entry">entry</a>-&gt;lsm_data)
<a name="L219" href="source/net/ipv4/cipso_ipv4.c#L219">219</a>                 <a href="ident?i=netlbl_secattr_cache_free">netlbl_secattr_cache_free</a>(<a href="ident?i=entry">entry</a>-&gt;lsm_data);
<a name="L220" href="source/net/ipv4/cipso_ipv4.c#L220">220</a>         <a href="ident?i=kfree">kfree</a>(<a href="ident?i=entry">entry</a>-&gt;<a href="ident?i=key">key</a>);
<a name="L221" href="source/net/ipv4/cipso_ipv4.c#L221">221</a>         <a href="ident?i=kfree">kfree</a>(<a href="ident?i=entry">entry</a>);
<a name="L222" href="source/net/ipv4/cipso_ipv4.c#L222">222</a> }
<a name="L223" href="source/net/ipv4/cipso_ipv4.c#L223">223</a> 
<a name="L224" href="source/net/ipv4/cipso_ipv4.c#L224">224</a> <b><i>/**</i></b>
<a name="L225" href="source/net/ipv4/cipso_ipv4.c#L225">225</a> <b><i> * cipso_v4_map_cache_hash - Hashing function for the CIPSO cache</i></b>
<a name="L226" href="source/net/ipv4/cipso_ipv4.c#L226">226</a> <b><i> * @key: the hash key</i></b>
<a name="L227" href="source/net/ipv4/cipso_ipv4.c#L227">227</a> <b><i> * @key_len: the length of the key in bytes</i></b>
<a name="L228" href="source/net/ipv4/cipso_ipv4.c#L228">228</a> <b><i> *</i></b>
<a name="L229" href="source/net/ipv4/cipso_ipv4.c#L229">229</a> <b><i> * Description:</i></b>
<a name="L230" href="source/net/ipv4/cipso_ipv4.c#L230">230</a> <b><i> * The CIPSO tag hashing function.  Returns a 32-bit hash value.</i></b>
<a name="L231" href="source/net/ipv4/cipso_ipv4.c#L231">231</a> <b><i> *</i></b>
<a name="L232" href="source/net/ipv4/cipso_ipv4.c#L232">232</a> <b><i> */</i></b>
<a name="L233" href="source/net/ipv4/cipso_ipv4.c#L233">233</a> static <a href="ident?i=u32">u32</a> <a href="ident?i=cipso_v4_map_cache_hash">cipso_v4_map_cache_hash</a>(const unsigned char *<a href="ident?i=key">key</a>, <a href="ident?i=u32">u32</a> <a href="ident?i=key_len">key_len</a>)
<a name="L234" href="source/net/ipv4/cipso_ipv4.c#L234">234</a> {
<a name="L235" href="source/net/ipv4/cipso_ipv4.c#L235">235</a>         return <a href="ident?i=jhash">jhash</a>(<a href="ident?i=key">key</a>, <a href="ident?i=key_len">key_len</a>, 0);
<a name="L236" href="source/net/ipv4/cipso_ipv4.c#L236">236</a> }
<a name="L237" href="source/net/ipv4/cipso_ipv4.c#L237">237</a> 
<a name="L238" href="source/net/ipv4/cipso_ipv4.c#L238">238</a> <b><i>/*</i></b>
<a name="L239" href="source/net/ipv4/cipso_ipv4.c#L239">239</a> <b><i> * Label Mapping Cache Functions</i></b>
<a name="L240" href="source/net/ipv4/cipso_ipv4.c#L240">240</a> <b><i> */</i></b>
<a name="L241" href="source/net/ipv4/cipso_ipv4.c#L241">241</a> 
<a name="L242" href="source/net/ipv4/cipso_ipv4.c#L242">242</a> <b><i>/**</i></b>
<a name="L243" href="source/net/ipv4/cipso_ipv4.c#L243">243</a> <b><i> * cipso_v4_cache_init - Initialize the CIPSO cache</i></b>
<a name="L244" href="source/net/ipv4/cipso_ipv4.c#L244">244</a> <b><i> *</i></b>
<a name="L245" href="source/net/ipv4/cipso_ipv4.c#L245">245</a> <b><i> * Description:</i></b>
<a name="L246" href="source/net/ipv4/cipso_ipv4.c#L246">246</a> <b><i> * Initializes the CIPSO label mapping cache, this function should be called</i></b>
<a name="L247" href="source/net/ipv4/cipso_ipv4.c#L247">247</a> <b><i> * before any of the other functions defined in this file.  Returns zero on</i></b>
<a name="L248" href="source/net/ipv4/cipso_ipv4.c#L248">248</a> <b><i> * success, negative values on error.</i></b>
<a name="L249" href="source/net/ipv4/cipso_ipv4.c#L249">249</a> <b><i> *</i></b>
<a name="L250" href="source/net/ipv4/cipso_ipv4.c#L250">250</a> <b><i> */</i></b>
<a name="L251" href="source/net/ipv4/cipso_ipv4.c#L251">251</a> static int <a href="ident?i=__init">__init</a> <a href="ident?i=cipso_v4_cache_init">cipso_v4_cache_init</a>(void)
<a name="L252" href="source/net/ipv4/cipso_ipv4.c#L252">252</a> {
<a name="L253" href="source/net/ipv4/cipso_ipv4.c#L253">253</a>         <a href="ident?i=u32">u32</a> iter;
<a name="L254" href="source/net/ipv4/cipso_ipv4.c#L254">254</a> 
<a name="L255" href="source/net/ipv4/cipso_ipv4.c#L255">255</a>         <a href="ident?i=cipso_v4_cache">cipso_v4_cache</a> = <a href="ident?i=kcalloc">kcalloc</a>(<a href="ident?i=CIPSO_V4_CACHE_BUCKETS">CIPSO_V4_CACHE_BUCKETS</a>,
<a name="L256" href="source/net/ipv4/cipso_ipv4.c#L256">256</a>                                  sizeof(struct <a href="ident?i=cipso_v4_map_cache_bkt">cipso_v4_map_cache_bkt</a>),
<a name="L257" href="source/net/ipv4/cipso_ipv4.c#L257">257</a>                                  <a href="ident?i=GFP_KERNEL">GFP_KERNEL</a>);
<a name="L258" href="source/net/ipv4/cipso_ipv4.c#L258">258</a>         if (!<a href="ident?i=cipso_v4_cache">cipso_v4_cache</a>)
<a name="L259" href="source/net/ipv4/cipso_ipv4.c#L259">259</a>                 return -<a href="ident?i=ENOMEM">ENOMEM</a>;
<a name="L260" href="source/net/ipv4/cipso_ipv4.c#L260">260</a> 
<a name="L261" href="source/net/ipv4/cipso_ipv4.c#L261">261</a>         for (iter = 0; iter &lt; <a href="ident?i=CIPSO_V4_CACHE_BUCKETS">CIPSO_V4_CACHE_BUCKETS</a>; iter++) {
<a name="L262" href="source/net/ipv4/cipso_ipv4.c#L262">262</a>                 <a href="ident?i=spin_lock_init">spin_lock_init</a>(&amp;<a href="ident?i=cipso_v4_cache">cipso_v4_cache</a>[iter].<a href="ident?i=lock">lock</a>);
<a name="L263" href="source/net/ipv4/cipso_ipv4.c#L263">263</a>                 <a href="ident?i=cipso_v4_cache">cipso_v4_cache</a>[iter].<a href="ident?i=size">size</a> = 0;
<a name="L264" href="source/net/ipv4/cipso_ipv4.c#L264">264</a>                 <a href="ident?i=INIT_LIST_HEAD">INIT_LIST_HEAD</a>(&amp;<a href="ident?i=cipso_v4_cache">cipso_v4_cache</a>[iter].<a href="ident?i=list">list</a>);
<a name="L265" href="source/net/ipv4/cipso_ipv4.c#L265">265</a>         }
<a name="L266" href="source/net/ipv4/cipso_ipv4.c#L266">266</a> 
<a name="L267" href="source/net/ipv4/cipso_ipv4.c#L267">267</a>         return 0;
<a name="L268" href="source/net/ipv4/cipso_ipv4.c#L268">268</a> }
<a name="L269" href="source/net/ipv4/cipso_ipv4.c#L269">269</a> 
<a name="L270" href="source/net/ipv4/cipso_ipv4.c#L270">270</a> <b><i>/**</i></b>
<a name="L271" href="source/net/ipv4/cipso_ipv4.c#L271">271</a> <b><i> * cipso_v4_cache_invalidate - Invalidates the current CIPSO cache</i></b>
<a name="L272" href="source/net/ipv4/cipso_ipv4.c#L272">272</a> <b><i> *</i></b>
<a name="L273" href="source/net/ipv4/cipso_ipv4.c#L273">273</a> <b><i> * Description:</i></b>
<a name="L274" href="source/net/ipv4/cipso_ipv4.c#L274">274</a> <b><i> * Invalidates and frees any entries in the CIPSO cache.  Returns zero on</i></b>
<a name="L275" href="source/net/ipv4/cipso_ipv4.c#L275">275</a> <b><i> * success and negative values on failure.</i></b>
<a name="L276" href="source/net/ipv4/cipso_ipv4.c#L276">276</a> <b><i> *</i></b>
<a name="L277" href="source/net/ipv4/cipso_ipv4.c#L277">277</a> <b><i> */</i></b>
<a name="L278" href="source/net/ipv4/cipso_ipv4.c#L278">278</a> void <a href="ident?i=cipso_v4_cache_invalidate">cipso_v4_cache_invalidate</a>(void)
<a name="L279" href="source/net/ipv4/cipso_ipv4.c#L279">279</a> {
<a name="L280" href="source/net/ipv4/cipso_ipv4.c#L280">280</a>         struct <a href="ident?i=cipso_v4_map_cache_entry">cipso_v4_map_cache_entry</a> *<a href="ident?i=entry">entry</a>, *tmp_entry;
<a name="L281" href="source/net/ipv4/cipso_ipv4.c#L281">281</a>         <a href="ident?i=u32">u32</a> iter;
<a name="L282" href="source/net/ipv4/cipso_ipv4.c#L282">282</a> 
<a name="L283" href="source/net/ipv4/cipso_ipv4.c#L283">283</a>         for (iter = 0; iter &lt; <a href="ident?i=CIPSO_V4_CACHE_BUCKETS">CIPSO_V4_CACHE_BUCKETS</a>; iter++) {
<a name="L284" href="source/net/ipv4/cipso_ipv4.c#L284">284</a>                 <a href="ident?i=spin_lock_bh">spin_lock_bh</a>(&amp;<a href="ident?i=cipso_v4_cache">cipso_v4_cache</a>[iter].<a href="ident?i=lock">lock</a>);
<a name="L285" href="source/net/ipv4/cipso_ipv4.c#L285">285</a>                 <a href="ident?i=list_for_each_entry_safe">list_for_each_entry_safe</a>(<a href="ident?i=entry">entry</a>,
<a name="L286" href="source/net/ipv4/cipso_ipv4.c#L286">286</a>                                          tmp_entry,
<a name="L287" href="source/net/ipv4/cipso_ipv4.c#L287">287</a>                                          &amp;<a href="ident?i=cipso_v4_cache">cipso_v4_cache</a>[iter].<a href="ident?i=list">list</a>, <a href="ident?i=list">list</a>) {
<a name="L288" href="source/net/ipv4/cipso_ipv4.c#L288">288</a>                         <a href="ident?i=list_del">list_del</a>(&amp;<a href="ident?i=entry">entry</a>-&gt;<a href="ident?i=list">list</a>);
<a name="L289" href="source/net/ipv4/cipso_ipv4.c#L289">289</a>                         <a href="ident?i=cipso_v4_cache_entry_free">cipso_v4_cache_entry_free</a>(<a href="ident?i=entry">entry</a>);
<a name="L290" href="source/net/ipv4/cipso_ipv4.c#L290">290</a>                 }
<a name="L291" href="source/net/ipv4/cipso_ipv4.c#L291">291</a>                 <a href="ident?i=cipso_v4_cache">cipso_v4_cache</a>[iter].<a href="ident?i=size">size</a> = 0;
<a name="L292" href="source/net/ipv4/cipso_ipv4.c#L292">292</a>                 <a href="ident?i=spin_unlock_bh">spin_unlock_bh</a>(&amp;<a href="ident?i=cipso_v4_cache">cipso_v4_cache</a>[iter].<a href="ident?i=lock">lock</a>);
<a name="L293" href="source/net/ipv4/cipso_ipv4.c#L293">293</a>         }
<a name="L294" href="source/net/ipv4/cipso_ipv4.c#L294">294</a> }
<a name="L295" href="source/net/ipv4/cipso_ipv4.c#L295">295</a> 
<a name="L296" href="source/net/ipv4/cipso_ipv4.c#L296">296</a> <b><i>/**</i></b>
<a name="L297" href="source/net/ipv4/cipso_ipv4.c#L297">297</a> <b><i> * cipso_v4_cache_check - Check the CIPSO cache for a label mapping</i></b>
<a name="L298" href="source/net/ipv4/cipso_ipv4.c#L298">298</a> <b><i> * @key: the buffer to check</i></b>
<a name="L299" href="source/net/ipv4/cipso_ipv4.c#L299">299</a> <b><i> * @key_len: buffer length in bytes</i></b>
<a name="L300" href="source/net/ipv4/cipso_ipv4.c#L300">300</a> <b><i> * @secattr: the security attribute struct to use</i></b>
<a name="L301" href="source/net/ipv4/cipso_ipv4.c#L301">301</a> <b><i> *</i></b>
<a name="L302" href="source/net/ipv4/cipso_ipv4.c#L302">302</a> <b><i> * Description:</i></b>
<a name="L303" href="source/net/ipv4/cipso_ipv4.c#L303">303</a> <b><i> * This function checks the cache to see if a label mapping already exists for</i></b>
<a name="L304" href="source/net/ipv4/cipso_ipv4.c#L304">304</a> <b><i> * the given key.  If there is a match then the cache is adjusted and the</i></b>
<a name="L305" href="source/net/ipv4/cipso_ipv4.c#L305">305</a> <b><i> * @secattr struct is populated with the correct LSM security attributes.  The</i></b>
<a name="L306" href="source/net/ipv4/cipso_ipv4.c#L306">306</a> <b><i> * cache is adjusted in the following manner if the entry is not already the</i></b>
<a name="L307" href="source/net/ipv4/cipso_ipv4.c#L307">307</a> <b><i> * first in the cache bucket:</i></b>
<a name="L308" href="source/net/ipv4/cipso_ipv4.c#L308">308</a> <b><i> *</i></b>
<a name="L309" href="source/net/ipv4/cipso_ipv4.c#L309">309</a> <b><i> *  1. The cache entry's activity counter is incremented</i></b>
<a name="L310" href="source/net/ipv4/cipso_ipv4.c#L310">310</a> <b><i> *  2. The previous (higher ranking) entry's activity counter is decremented</i></b>
<a name="L311" href="source/net/ipv4/cipso_ipv4.c#L311">311</a> <b><i> *  3. If the difference between the two activity counters is geater than</i></b>
<a name="L312" href="source/net/ipv4/cipso_ipv4.c#L312">312</a> <b><i> *     CIPSO_V4_CACHE_REORDERLIMIT the two entries are swapped</i></b>
<a name="L313" href="source/net/ipv4/cipso_ipv4.c#L313">313</a> <b><i> *</i></b>
<a name="L314" href="source/net/ipv4/cipso_ipv4.c#L314">314</a> <b><i> * Returns zero on success, -ENOENT for a cache miss, and other negative values</i></b>
<a name="L315" href="source/net/ipv4/cipso_ipv4.c#L315">315</a> <b><i> * on error.</i></b>
<a name="L316" href="source/net/ipv4/cipso_ipv4.c#L316">316</a> <b><i> *</i></b>
<a name="L317" href="source/net/ipv4/cipso_ipv4.c#L317">317</a> <b><i> */</i></b>
<a name="L318" href="source/net/ipv4/cipso_ipv4.c#L318">318</a> static int <a href="ident?i=cipso_v4_cache_check">cipso_v4_cache_check</a>(const unsigned char *<a href="ident?i=key">key</a>,
<a name="L319" href="source/net/ipv4/cipso_ipv4.c#L319">319</a>                                 <a href="ident?i=u32">u32</a> <a href="ident?i=key_len">key_len</a>,
<a name="L320" href="source/net/ipv4/cipso_ipv4.c#L320">320</a>                                 struct <a href="ident?i=netlbl_lsm_secattr">netlbl_lsm_secattr</a> *secattr)
<a name="L321" href="source/net/ipv4/cipso_ipv4.c#L321">321</a> {
<a name="L322" href="source/net/ipv4/cipso_ipv4.c#L322">322</a>         <a href="ident?i=u32">u32</a> bkt;
<a name="L323" href="source/net/ipv4/cipso_ipv4.c#L323">323</a>         struct <a href="ident?i=cipso_v4_map_cache_entry">cipso_v4_map_cache_entry</a> *<a href="ident?i=entry">entry</a>;
<a name="L324" href="source/net/ipv4/cipso_ipv4.c#L324">324</a>         struct <a href="ident?i=cipso_v4_map_cache_entry">cipso_v4_map_cache_entry</a> *prev_entry = <a href="ident?i=NULL">NULL</a>;
<a name="L325" href="source/net/ipv4/cipso_ipv4.c#L325">325</a>         <a href="ident?i=u32">u32</a> <a href="ident?i=hash">hash</a>;
<a name="L326" href="source/net/ipv4/cipso_ipv4.c#L326">326</a> 
<a name="L327" href="source/net/ipv4/cipso_ipv4.c#L327">327</a>         if (!<a href="ident?i=cipso_v4_cache_enabled">cipso_v4_cache_enabled</a>)
<a name="L328" href="source/net/ipv4/cipso_ipv4.c#L328">328</a>                 return -<a href="ident?i=ENOENT">ENOENT</a>;
<a name="L329" href="source/net/ipv4/cipso_ipv4.c#L329">329</a> 
<a name="L330" href="source/net/ipv4/cipso_ipv4.c#L330">330</a>         <a href="ident?i=hash">hash</a> = <a href="ident?i=cipso_v4_map_cache_hash">cipso_v4_map_cache_hash</a>(<a href="ident?i=key">key</a>, <a href="ident?i=key_len">key_len</a>);
<a name="L331" href="source/net/ipv4/cipso_ipv4.c#L331">331</a>         bkt = <a href="ident?i=hash">hash</a> &amp; (<a href="ident?i=CIPSO_V4_CACHE_BUCKETS">CIPSO_V4_CACHE_BUCKETS</a> - 1);
<a name="L332" href="source/net/ipv4/cipso_ipv4.c#L332">332</a>         <a href="ident?i=spin_lock_bh">spin_lock_bh</a>(&amp;<a href="ident?i=cipso_v4_cache">cipso_v4_cache</a>[bkt].<a href="ident?i=lock">lock</a>);
<a name="L333" href="source/net/ipv4/cipso_ipv4.c#L333">333</a>         <a href="ident?i=list_for_each_entry">list_for_each_entry</a>(<a href="ident?i=entry">entry</a>, &amp;<a href="ident?i=cipso_v4_cache">cipso_v4_cache</a>[bkt].<a href="ident?i=list">list</a>, <a href="ident?i=list">list</a>) {
<a name="L334" href="source/net/ipv4/cipso_ipv4.c#L334">334</a>                 if (<a href="ident?i=entry">entry</a>-&gt;<a href="ident?i=hash">hash</a> == <a href="ident?i=hash">hash</a> &amp;&amp;
<a name="L335" href="source/net/ipv4/cipso_ipv4.c#L335">335</a>                     <a href="ident?i=entry">entry</a>-&gt;<a href="ident?i=key_len">key_len</a> == <a href="ident?i=key_len">key_len</a> &amp;&amp;
<a name="L336" href="source/net/ipv4/cipso_ipv4.c#L336">336</a>                     <a href="ident?i=memcmp">memcmp</a>(<a href="ident?i=entry">entry</a>-&gt;<a href="ident?i=key">key</a>, <a href="ident?i=key">key</a>, <a href="ident?i=key_len">key_len</a>) == 0) {
<a name="L337" href="source/net/ipv4/cipso_ipv4.c#L337">337</a>                         <a href="ident?i=entry">entry</a>-&gt;activity += 1;
<a name="L338" href="source/net/ipv4/cipso_ipv4.c#L338">338</a>                         <a href="ident?i=atomic_inc">atomic_inc</a>(&amp;<a href="ident?i=entry">entry</a>-&gt;lsm_data-&gt;refcount);
<a name="L339" href="source/net/ipv4/cipso_ipv4.c#L339">339</a>                         secattr-&gt;<a href="ident?i=cache">cache</a> = <a href="ident?i=entry">entry</a>-&gt;lsm_data;
<a name="L340" href="source/net/ipv4/cipso_ipv4.c#L340">340</a>                         secattr-&gt;<a href="ident?i=flags">flags</a> |= <a href="ident?i=NETLBL_SECATTR_CACHE">NETLBL_SECATTR_CACHE</a>;
<a name="L341" href="source/net/ipv4/cipso_ipv4.c#L341">341</a>                         secattr-&gt;<a href="ident?i=type">type</a> = <a href="ident?i=NETLBL_NLTYPE_CIPSOV4">NETLBL_NLTYPE_CIPSOV4</a>;
<a name="L342" href="source/net/ipv4/cipso_ipv4.c#L342">342</a>                         if (!prev_entry) {
<a name="L343" href="source/net/ipv4/cipso_ipv4.c#L343">343</a>                                 <a href="ident?i=spin_unlock_bh">spin_unlock_bh</a>(&amp;<a href="ident?i=cipso_v4_cache">cipso_v4_cache</a>[bkt].<a href="ident?i=lock">lock</a>);
<a name="L344" href="source/net/ipv4/cipso_ipv4.c#L344">344</a>                                 return 0;
<a name="L345" href="source/net/ipv4/cipso_ipv4.c#L345">345</a>                         }
<a name="L346" href="source/net/ipv4/cipso_ipv4.c#L346">346</a> 
<a name="L347" href="source/net/ipv4/cipso_ipv4.c#L347">347</a>                         if (prev_entry-&gt;activity &gt; 0)
<a name="L348" href="source/net/ipv4/cipso_ipv4.c#L348">348</a>                                 prev_entry-&gt;activity -= 1;
<a name="L349" href="source/net/ipv4/cipso_ipv4.c#L349">349</a>                         if (<a href="ident?i=entry">entry</a>-&gt;activity &gt; prev_entry-&gt;activity &amp;&amp;
<a name="L350" href="source/net/ipv4/cipso_ipv4.c#L350">350</a>                             <a href="ident?i=entry">entry</a>-&gt;activity - prev_entry-&gt;activity &gt;
<a name="L351" href="source/net/ipv4/cipso_ipv4.c#L351">351</a>                             <a href="ident?i=CIPSO_V4_CACHE_REORDERLIMIT">CIPSO_V4_CACHE_REORDERLIMIT</a>) {
<a name="L352" href="source/net/ipv4/cipso_ipv4.c#L352">352</a>                                 <a href="ident?i=__list_del">__list_del</a>(<a href="ident?i=entry">entry</a>-&gt;<a href="ident?i=list">list</a>.prev, <a href="ident?i=entry">entry</a>-&gt;<a href="ident?i=list">list</a>.<a href="ident?i=next">next</a>);
<a name="L353" href="source/net/ipv4/cipso_ipv4.c#L353">353</a>                                 <a href="ident?i=__list_add">__list_add</a>(&amp;<a href="ident?i=entry">entry</a>-&gt;<a href="ident?i=list">list</a>,
<a name="L354" href="source/net/ipv4/cipso_ipv4.c#L354">354</a>                                            prev_entry-&gt;<a href="ident?i=list">list</a>.prev,
<a name="L355" href="source/net/ipv4/cipso_ipv4.c#L355">355</a>                                            &amp;prev_entry-&gt;<a href="ident?i=list">list</a>);
<a name="L356" href="source/net/ipv4/cipso_ipv4.c#L356">356</a>                         }
<a name="L357" href="source/net/ipv4/cipso_ipv4.c#L357">357</a> 
<a name="L358" href="source/net/ipv4/cipso_ipv4.c#L358">358</a>                         <a href="ident?i=spin_unlock_bh">spin_unlock_bh</a>(&amp;<a href="ident?i=cipso_v4_cache">cipso_v4_cache</a>[bkt].<a href="ident?i=lock">lock</a>);
<a name="L359" href="source/net/ipv4/cipso_ipv4.c#L359">359</a>                         return 0;
<a name="L360" href="source/net/ipv4/cipso_ipv4.c#L360">360</a>                 }
<a name="L361" href="source/net/ipv4/cipso_ipv4.c#L361">361</a>                 prev_entry = <a href="ident?i=entry">entry</a>;
<a name="L362" href="source/net/ipv4/cipso_ipv4.c#L362">362</a>         }
<a name="L363" href="source/net/ipv4/cipso_ipv4.c#L363">363</a>         <a href="ident?i=spin_unlock_bh">spin_unlock_bh</a>(&amp;<a href="ident?i=cipso_v4_cache">cipso_v4_cache</a>[bkt].<a href="ident?i=lock">lock</a>);
<a name="L364" href="source/net/ipv4/cipso_ipv4.c#L364">364</a> 
<a name="L365" href="source/net/ipv4/cipso_ipv4.c#L365">365</a>         return -<a href="ident?i=ENOENT">ENOENT</a>;
<a name="L366" href="source/net/ipv4/cipso_ipv4.c#L366">366</a> }
<a name="L367" href="source/net/ipv4/cipso_ipv4.c#L367">367</a> 
<a name="L368" href="source/net/ipv4/cipso_ipv4.c#L368">368</a> <b><i>/**</i></b>
<a name="L369" href="source/net/ipv4/cipso_ipv4.c#L369">369</a> <b><i> * cipso_v4_cache_add - Add an entry to the CIPSO cache</i></b>
<a name="L370" href="source/net/ipv4/cipso_ipv4.c#L370">370</a> <b><i> * @skb: the packet</i></b>
<a name="L371" href="source/net/ipv4/cipso_ipv4.c#L371">371</a> <b><i> * @secattr: the packet's security attributes</i></b>
<a name="L372" href="source/net/ipv4/cipso_ipv4.c#L372">372</a> <b><i> *</i></b>
<a name="L373" href="source/net/ipv4/cipso_ipv4.c#L373">373</a> <b><i> * Description:</i></b>
<a name="L374" href="source/net/ipv4/cipso_ipv4.c#L374">374</a> <b><i> * Add a new entry into the CIPSO label mapping cache.  Add the new entry to</i></b>
<a name="L375" href="source/net/ipv4/cipso_ipv4.c#L375">375</a> <b><i> * head of the cache bucket's list, if the cache bucket is out of room remove</i></b>
<a name="L376" href="source/net/ipv4/cipso_ipv4.c#L376">376</a> <b><i> * the last entry in the list first.  It is important to note that there is</i></b>
<a name="L377" href="source/net/ipv4/cipso_ipv4.c#L377">377</a> <b><i> * currently no checking for duplicate keys.  Returns zero on success,</i></b>
<a name="L378" href="source/net/ipv4/cipso_ipv4.c#L378">378</a> <b><i> * negative values on failure.</i></b>
<a name="L379" href="source/net/ipv4/cipso_ipv4.c#L379">379</a> <b><i> *</i></b>
<a name="L380" href="source/net/ipv4/cipso_ipv4.c#L380">380</a> <b><i> */</i></b>
<a name="L381" href="source/net/ipv4/cipso_ipv4.c#L381">381</a> int <a href="ident?i=cipso_v4_cache_add">cipso_v4_cache_add</a>(const unsigned char *cipso_ptr,
<a name="L382" href="source/net/ipv4/cipso_ipv4.c#L382">382</a>                        const struct <a href="ident?i=netlbl_lsm_secattr">netlbl_lsm_secattr</a> *secattr)
<a name="L383" href="source/net/ipv4/cipso_ipv4.c#L383">383</a> {
<a name="L384" href="source/net/ipv4/cipso_ipv4.c#L384">384</a>         int ret_val = -<a href="ident?i=EPERM">EPERM</a>;
<a name="L385" href="source/net/ipv4/cipso_ipv4.c#L385">385</a>         <a href="ident?i=u32">u32</a> bkt;
<a name="L386" href="source/net/ipv4/cipso_ipv4.c#L386">386</a>         struct <a href="ident?i=cipso_v4_map_cache_entry">cipso_v4_map_cache_entry</a> *<a href="ident?i=entry">entry</a> = <a href="ident?i=NULL">NULL</a>;
<a name="L387" href="source/net/ipv4/cipso_ipv4.c#L387">387</a>         struct <a href="ident?i=cipso_v4_map_cache_entry">cipso_v4_map_cache_entry</a> *old_entry = <a href="ident?i=NULL">NULL</a>;
<a name="L388" href="source/net/ipv4/cipso_ipv4.c#L388">388</a>         <a href="ident?i=u32">u32</a> cipso_ptr_len;
<a name="L389" href="source/net/ipv4/cipso_ipv4.c#L389">389</a> 
<a name="L390" href="source/net/ipv4/cipso_ipv4.c#L390">390</a>         if (!<a href="ident?i=cipso_v4_cache_enabled">cipso_v4_cache_enabled</a> || <a href="ident?i=cipso_v4_cache_bucketsize">cipso_v4_cache_bucketsize</a> &lt;= 0)
<a name="L391" href="source/net/ipv4/cipso_ipv4.c#L391">391</a>                 return 0;
<a name="L392" href="source/net/ipv4/cipso_ipv4.c#L392">392</a> 
<a name="L393" href="source/net/ipv4/cipso_ipv4.c#L393">393</a>         cipso_ptr_len = cipso_ptr[1];
<a name="L394" href="source/net/ipv4/cipso_ipv4.c#L394">394</a> 
<a name="L395" href="source/net/ipv4/cipso_ipv4.c#L395">395</a>         <a href="ident?i=entry">entry</a> = <a href="ident?i=kzalloc">kzalloc</a>(sizeof(*<a href="ident?i=entry">entry</a>), <a href="ident?i=GFP_ATOMIC">GFP_ATOMIC</a>);
<a name="L396" href="source/net/ipv4/cipso_ipv4.c#L396">396</a>         if (!<a href="ident?i=entry">entry</a>)
<a name="L397" href="source/net/ipv4/cipso_ipv4.c#L397">397</a>                 return -<a href="ident?i=ENOMEM">ENOMEM</a>;
<a name="L398" href="source/net/ipv4/cipso_ipv4.c#L398">398</a>         <a href="ident?i=entry">entry</a>-&gt;<a href="ident?i=key">key</a> = <a href="ident?i=kmemdup">kmemdup</a>(cipso_ptr, cipso_ptr_len, <a href="ident?i=GFP_ATOMIC">GFP_ATOMIC</a>);
<a name="L399" href="source/net/ipv4/cipso_ipv4.c#L399">399</a>         if (!<a href="ident?i=entry">entry</a>-&gt;<a href="ident?i=key">key</a>) {
<a name="L400" href="source/net/ipv4/cipso_ipv4.c#L400">400</a>                 ret_val = -<a href="ident?i=ENOMEM">ENOMEM</a>;
<a name="L401" href="source/net/ipv4/cipso_ipv4.c#L401">401</a>                 goto cache_add_failure;
<a name="L402" href="source/net/ipv4/cipso_ipv4.c#L402">402</a>         }
<a name="L403" href="source/net/ipv4/cipso_ipv4.c#L403">403</a>         <a href="ident?i=entry">entry</a>-&gt;<a href="ident?i=key_len">key_len</a> = cipso_ptr_len;
<a name="L404" href="source/net/ipv4/cipso_ipv4.c#L404">404</a>         <a href="ident?i=entry">entry</a>-&gt;<a href="ident?i=hash">hash</a> = <a href="ident?i=cipso_v4_map_cache_hash">cipso_v4_map_cache_hash</a>(cipso_ptr, cipso_ptr_len);
<a name="L405" href="source/net/ipv4/cipso_ipv4.c#L405">405</a>         <a href="ident?i=atomic_inc">atomic_inc</a>(&amp;secattr-&gt;<a href="ident?i=cache">cache</a>-&gt;refcount);
<a name="L406" href="source/net/ipv4/cipso_ipv4.c#L406">406</a>         <a href="ident?i=entry">entry</a>-&gt;lsm_data = secattr-&gt;<a href="ident?i=cache">cache</a>;
<a name="L407" href="source/net/ipv4/cipso_ipv4.c#L407">407</a> 
<a name="L408" href="source/net/ipv4/cipso_ipv4.c#L408">408</a>         bkt = <a href="ident?i=entry">entry</a>-&gt;<a href="ident?i=hash">hash</a> &amp; (<a href="ident?i=CIPSO_V4_CACHE_BUCKETS">CIPSO_V4_CACHE_BUCKETS</a> - 1);
<a name="L409" href="source/net/ipv4/cipso_ipv4.c#L409">409</a>         <a href="ident?i=spin_lock_bh">spin_lock_bh</a>(&amp;<a href="ident?i=cipso_v4_cache">cipso_v4_cache</a>[bkt].<a href="ident?i=lock">lock</a>);
<a name="L410" href="source/net/ipv4/cipso_ipv4.c#L410">410</a>         if (<a href="ident?i=cipso_v4_cache">cipso_v4_cache</a>[bkt].<a href="ident?i=size">size</a> &lt; <a href="ident?i=cipso_v4_cache_bucketsize">cipso_v4_cache_bucketsize</a>) {
<a name="L411" href="source/net/ipv4/cipso_ipv4.c#L411">411</a>                 <a href="ident?i=list_add">list_add</a>(&amp;<a href="ident?i=entry">entry</a>-&gt;<a href="ident?i=list">list</a>, &amp;<a href="ident?i=cipso_v4_cache">cipso_v4_cache</a>[bkt].<a href="ident?i=list">list</a>);
<a name="L412" href="source/net/ipv4/cipso_ipv4.c#L412">412</a>                 <a href="ident?i=cipso_v4_cache">cipso_v4_cache</a>[bkt].<a href="ident?i=size">size</a> += 1;
<a name="L413" href="source/net/ipv4/cipso_ipv4.c#L413">413</a>         } else {
<a name="L414" href="source/net/ipv4/cipso_ipv4.c#L414">414</a>                 old_entry = <a href="ident?i=list_entry">list_entry</a>(<a href="ident?i=cipso_v4_cache">cipso_v4_cache</a>[bkt].<a href="ident?i=list">list</a>.prev,
<a name="L415" href="source/net/ipv4/cipso_ipv4.c#L415">415</a>                                        struct <a href="ident?i=cipso_v4_map_cache_entry">cipso_v4_map_cache_entry</a>, <a href="ident?i=list">list</a>);
<a name="L416" href="source/net/ipv4/cipso_ipv4.c#L416">416</a>                 <a href="ident?i=list_del">list_del</a>(&amp;old_entry-&gt;<a href="ident?i=list">list</a>);
<a name="L417" href="source/net/ipv4/cipso_ipv4.c#L417">417</a>                 <a href="ident?i=list_add">list_add</a>(&amp;<a href="ident?i=entry">entry</a>-&gt;<a href="ident?i=list">list</a>, &amp;<a href="ident?i=cipso_v4_cache">cipso_v4_cache</a>[bkt].<a href="ident?i=list">list</a>);
<a name="L418" href="source/net/ipv4/cipso_ipv4.c#L418">418</a>                 <a href="ident?i=cipso_v4_cache_entry_free">cipso_v4_cache_entry_free</a>(old_entry);
<a name="L419" href="source/net/ipv4/cipso_ipv4.c#L419">419</a>         }
<a name="L420" href="source/net/ipv4/cipso_ipv4.c#L420">420</a>         <a href="ident?i=spin_unlock_bh">spin_unlock_bh</a>(&amp;<a href="ident?i=cipso_v4_cache">cipso_v4_cache</a>[bkt].<a href="ident?i=lock">lock</a>);
<a name="L421" href="source/net/ipv4/cipso_ipv4.c#L421">421</a> 
<a name="L422" href="source/net/ipv4/cipso_ipv4.c#L422">422</a>         return 0;
<a name="L423" href="source/net/ipv4/cipso_ipv4.c#L423">423</a> 
<a name="L424" href="source/net/ipv4/cipso_ipv4.c#L424">424</a> cache_add_failure:
<a name="L425" href="source/net/ipv4/cipso_ipv4.c#L425">425</a>         if (<a href="ident?i=entry">entry</a>)
<a name="L426" href="source/net/ipv4/cipso_ipv4.c#L426">426</a>                 <a href="ident?i=cipso_v4_cache_entry_free">cipso_v4_cache_entry_free</a>(<a href="ident?i=entry">entry</a>);
<a name="L427" href="source/net/ipv4/cipso_ipv4.c#L427">427</a>         return ret_val;
<a name="L428" href="source/net/ipv4/cipso_ipv4.c#L428">428</a> }
<a name="L429" href="source/net/ipv4/cipso_ipv4.c#L429">429</a> 
<a name="L430" href="source/net/ipv4/cipso_ipv4.c#L430">430</a> <b><i>/*</i></b>
<a name="L431" href="source/net/ipv4/cipso_ipv4.c#L431">431</a> <b><i> * DOI List Functions</i></b>
<a name="L432" href="source/net/ipv4/cipso_ipv4.c#L432">432</a> <b><i> */</i></b>
<a name="L433" href="source/net/ipv4/cipso_ipv4.c#L433">433</a> 
<a name="L434" href="source/net/ipv4/cipso_ipv4.c#L434">434</a> <b><i>/**</i></b>
<a name="L435" href="source/net/ipv4/cipso_ipv4.c#L435">435</a> <b><i> * cipso_v4_doi_search - Searches for a DOI definition</i></b>
<a name="L436" href="source/net/ipv4/cipso_ipv4.c#L436">436</a> <b><i> * @doi: the DOI to search for</i></b>
<a name="L437" href="source/net/ipv4/cipso_ipv4.c#L437">437</a> <b><i> *</i></b>
<a name="L438" href="source/net/ipv4/cipso_ipv4.c#L438">438</a> <b><i> * Description:</i></b>
<a name="L439" href="source/net/ipv4/cipso_ipv4.c#L439">439</a> <b><i> * Search the DOI definition list for a DOI definition with a DOI value that</i></b>
<a name="L440" href="source/net/ipv4/cipso_ipv4.c#L440">440</a> <b><i> * matches @doi.  The caller is responsible for calling rcu_read_[un]lock().</i></b>
<a name="L441" href="source/net/ipv4/cipso_ipv4.c#L441">441</a> <b><i> * Returns a pointer to the DOI definition on success and NULL on failure.</i></b>
<a name="L442" href="source/net/ipv4/cipso_ipv4.c#L442">442</a> <b><i> */</i></b>
<a name="L443" href="source/net/ipv4/cipso_ipv4.c#L443">443</a> static struct <a href="ident?i=cipso_v4_doi">cipso_v4_doi</a> *<a href="ident?i=cipso_v4_doi_search">cipso_v4_doi_search</a>(<a href="ident?i=u32">u32</a> doi)
<a name="L444" href="source/net/ipv4/cipso_ipv4.c#L444">444</a> {
<a name="L445" href="source/net/ipv4/cipso_ipv4.c#L445">445</a>         struct <a href="ident?i=cipso_v4_doi">cipso_v4_doi</a> *iter;
<a name="L446" href="source/net/ipv4/cipso_ipv4.c#L446">446</a> 
<a name="L447" href="source/net/ipv4/cipso_ipv4.c#L447">447</a>         <a href="ident?i=list_for_each_entry_rcu">list_for_each_entry_rcu</a>(iter, &amp;cipso_v4_doi_list, <a href="ident?i=list">list</a>)
<a name="L448" href="source/net/ipv4/cipso_ipv4.c#L448">448</a>                 if (iter-&gt;doi == doi &amp;&amp; <a href="ident?i=atomic_read">atomic_read</a>(&amp;iter-&gt;refcount))
<a name="L449" href="source/net/ipv4/cipso_ipv4.c#L449">449</a>                         return iter;
<a name="L450" href="source/net/ipv4/cipso_ipv4.c#L450">450</a>         return <a href="ident?i=NULL">NULL</a>;
<a name="L451" href="source/net/ipv4/cipso_ipv4.c#L451">451</a> }
<a name="L452" href="source/net/ipv4/cipso_ipv4.c#L452">452</a> 
<a name="L453" href="source/net/ipv4/cipso_ipv4.c#L453">453</a> <b><i>/**</i></b>
<a name="L454" href="source/net/ipv4/cipso_ipv4.c#L454">454</a> <b><i> * cipso_v4_doi_add - Add a new DOI to the CIPSO protocol engine</i></b>
<a name="L455" href="source/net/ipv4/cipso_ipv4.c#L455">455</a> <b><i> * @doi_def: the DOI structure</i></b>
<a name="L456" href="source/net/ipv4/cipso_ipv4.c#L456">456</a> <b><i> * @audit_info: NetLabel audit information</i></b>
<a name="L457" href="source/net/ipv4/cipso_ipv4.c#L457">457</a> <b><i> *</i></b>
<a name="L458" href="source/net/ipv4/cipso_ipv4.c#L458">458</a> <b><i> * Description:</i></b>
<a name="L459" href="source/net/ipv4/cipso_ipv4.c#L459">459</a> <b><i> * The caller defines a new DOI for use by the CIPSO engine and calls this</i></b>
<a name="L460" href="source/net/ipv4/cipso_ipv4.c#L460">460</a> <b><i> * function to add it to the list of acceptable domains.  The caller must</i></b>
<a name="L461" href="source/net/ipv4/cipso_ipv4.c#L461">461</a> <b><i> * ensure that the mapping table specified in @doi_def-&gt;map meets all of the</i></b>
<a name="L462" href="source/net/ipv4/cipso_ipv4.c#L462">462</a> <b><i> * requirements of the mapping type (see cipso_ipv4.h for details).  Returns</i></b>
<a name="L463" href="source/net/ipv4/cipso_ipv4.c#L463">463</a> <b><i> * zero on success and non-zero on failure.</i></b>
<a name="L464" href="source/net/ipv4/cipso_ipv4.c#L464">464</a> <b><i> *</i></b>
<a name="L465" href="source/net/ipv4/cipso_ipv4.c#L465">465</a> <b><i> */</i></b>
<a name="L466" href="source/net/ipv4/cipso_ipv4.c#L466">466</a> int <a href="ident?i=cipso_v4_doi_add">cipso_v4_doi_add</a>(struct <a href="ident?i=cipso_v4_doi">cipso_v4_doi</a> *doi_def,
<a name="L467" href="source/net/ipv4/cipso_ipv4.c#L467">467</a>                      struct <a href="ident?i=netlbl_audit">netlbl_audit</a> *audit_info)
<a name="L468" href="source/net/ipv4/cipso_ipv4.c#L468">468</a> {
<a name="L469" href="source/net/ipv4/cipso_ipv4.c#L469">469</a>         int ret_val = -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L470" href="source/net/ipv4/cipso_ipv4.c#L470">470</a>         <a href="ident?i=u32">u32</a> iter;
<a name="L471" href="source/net/ipv4/cipso_ipv4.c#L471">471</a>         <a href="ident?i=u32">u32</a> doi;
<a name="L472" href="source/net/ipv4/cipso_ipv4.c#L472">472</a>         <a href="ident?i=u32">u32</a> doi_type;
<a name="L473" href="source/net/ipv4/cipso_ipv4.c#L473">473</a>         struct <a href="ident?i=audit_buffer">audit_buffer</a> *audit_buf;
<a name="L474" href="source/net/ipv4/cipso_ipv4.c#L474">474</a> 
<a name="L475" href="source/net/ipv4/cipso_ipv4.c#L475">475</a>         doi = doi_def-&gt;doi;
<a name="L476" href="source/net/ipv4/cipso_ipv4.c#L476">476</a>         doi_type = doi_def-&gt;<a href="ident?i=type">type</a>;
<a name="L477" href="source/net/ipv4/cipso_ipv4.c#L477">477</a> 
<a name="L478" href="source/net/ipv4/cipso_ipv4.c#L478">478</a>         if (doi_def-&gt;doi == <a href="ident?i=CIPSO_V4_DOI_UNKNOWN">CIPSO_V4_DOI_UNKNOWN</a>)
<a name="L479" href="source/net/ipv4/cipso_ipv4.c#L479">479</a>                 goto doi_add_return;
<a name="L480" href="source/net/ipv4/cipso_ipv4.c#L480">480</a>         for (iter = 0; iter &lt; <a href="ident?i=CIPSO_V4_TAG_MAXCNT">CIPSO_V4_TAG_MAXCNT</a>; iter++) {
<a name="L481" href="source/net/ipv4/cipso_ipv4.c#L481">481</a>                 switch (doi_def-&gt;<a href="ident?i=tags">tags</a>[iter]) {
<a name="L482" href="source/net/ipv4/cipso_ipv4.c#L482">482</a>                 case <a href="ident?i=CIPSO_V4_TAG_RBITMAP">CIPSO_V4_TAG_RBITMAP</a>:
<a name="L483" href="source/net/ipv4/cipso_ipv4.c#L483">483</a>                         break;
<a name="L484" href="source/net/ipv4/cipso_ipv4.c#L484">484</a>                 case <a href="ident?i=CIPSO_V4_TAG_RANGE">CIPSO_V4_TAG_RANGE</a>:
<a name="L485" href="source/net/ipv4/cipso_ipv4.c#L485">485</a>                 case <a href="ident?i=CIPSO_V4_TAG_ENUM">CIPSO_V4_TAG_ENUM</a>:
<a name="L486" href="source/net/ipv4/cipso_ipv4.c#L486">486</a>                         if (doi_def-&gt;<a href="ident?i=type">type</a> != <a href="ident?i=CIPSO_V4_MAP_PASS">CIPSO_V4_MAP_PASS</a>)
<a name="L487" href="source/net/ipv4/cipso_ipv4.c#L487">487</a>                                 goto doi_add_return;
<a name="L488" href="source/net/ipv4/cipso_ipv4.c#L488">488</a>                         break;
<a name="L489" href="source/net/ipv4/cipso_ipv4.c#L489">489</a>                 case <a href="ident?i=CIPSO_V4_TAG_LOCAL">CIPSO_V4_TAG_LOCAL</a>:
<a name="L490" href="source/net/ipv4/cipso_ipv4.c#L490">490</a>                         if (doi_def-&gt;<a href="ident?i=type">type</a> != <a href="ident?i=CIPSO_V4_MAP_LOCAL">CIPSO_V4_MAP_LOCAL</a>)
<a name="L491" href="source/net/ipv4/cipso_ipv4.c#L491">491</a>                                 goto doi_add_return;
<a name="L492" href="source/net/ipv4/cipso_ipv4.c#L492">492</a>                         break;
<a name="L493" href="source/net/ipv4/cipso_ipv4.c#L493">493</a>                 case <a href="ident?i=CIPSO_V4_TAG_INVALID">CIPSO_V4_TAG_INVALID</a>:
<a name="L494" href="source/net/ipv4/cipso_ipv4.c#L494">494</a>                         if (iter == 0)
<a name="L495" href="source/net/ipv4/cipso_ipv4.c#L495">495</a>                                 goto doi_add_return;
<a name="L496" href="source/net/ipv4/cipso_ipv4.c#L496">496</a>                         break;
<a name="L497" href="source/net/ipv4/cipso_ipv4.c#L497">497</a>                 default:
<a name="L498" href="source/net/ipv4/cipso_ipv4.c#L498">498</a>                         goto doi_add_return;
<a name="L499" href="source/net/ipv4/cipso_ipv4.c#L499">499</a>                 }
<a name="L500" href="source/net/ipv4/cipso_ipv4.c#L500">500</a>         }
<a name="L501" href="source/net/ipv4/cipso_ipv4.c#L501">501</a> 
<a name="L502" href="source/net/ipv4/cipso_ipv4.c#L502">502</a>         <a href="ident?i=atomic_set">atomic_set</a>(&amp;doi_def-&gt;refcount, 1);
<a name="L503" href="source/net/ipv4/cipso_ipv4.c#L503">503</a> 
<a name="L504" href="source/net/ipv4/cipso_ipv4.c#L504">504</a>         <a href="ident?i=spin_lock">spin_lock</a>(&amp;cipso_v4_doi_list_lock);
<a name="L505" href="source/net/ipv4/cipso_ipv4.c#L505">505</a>         if (<a href="ident?i=cipso_v4_doi_search">cipso_v4_doi_search</a>(doi_def-&gt;doi)) {
<a name="L506" href="source/net/ipv4/cipso_ipv4.c#L506">506</a>                 <a href="ident?i=spin_unlock">spin_unlock</a>(&amp;cipso_v4_doi_list_lock);
<a name="L507" href="source/net/ipv4/cipso_ipv4.c#L507">507</a>                 ret_val = -<a href="ident?i=EEXIST">EEXIST</a>;
<a name="L508" href="source/net/ipv4/cipso_ipv4.c#L508">508</a>                 goto doi_add_return;
<a name="L509" href="source/net/ipv4/cipso_ipv4.c#L509">509</a>         }
<a name="L510" href="source/net/ipv4/cipso_ipv4.c#L510">510</a>         <a href="ident?i=list_add_tail_rcu">list_add_tail_rcu</a>(&amp;doi_def-&gt;<a href="ident?i=list">list</a>, &amp;cipso_v4_doi_list);
<a name="L511" href="source/net/ipv4/cipso_ipv4.c#L511">511</a>         <a href="ident?i=spin_unlock">spin_unlock</a>(&amp;cipso_v4_doi_list_lock);
<a name="L512" href="source/net/ipv4/cipso_ipv4.c#L512">512</a>         ret_val = 0;
<a name="L513" href="source/net/ipv4/cipso_ipv4.c#L513">513</a> 
<a name="L514" href="source/net/ipv4/cipso_ipv4.c#L514">514</a> doi_add_return:
<a name="L515" href="source/net/ipv4/cipso_ipv4.c#L515">515</a>         audit_buf = <a href="ident?i=netlbl_audit_start">netlbl_audit_start</a>(<a href="ident?i=AUDIT_MAC_CIPSOV4_ADD">AUDIT_MAC_CIPSOV4_ADD</a>, audit_info);
<a name="L516" href="source/net/ipv4/cipso_ipv4.c#L516">516</a>         if (audit_buf) {
<a name="L517" href="source/net/ipv4/cipso_ipv4.c#L517">517</a>                 const char *<a href="ident?i=type_str">type_str</a>;
<a name="L518" href="source/net/ipv4/cipso_ipv4.c#L518">518</a>                 switch (doi_type) {
<a name="L519" href="source/net/ipv4/cipso_ipv4.c#L519">519</a>                 case <a href="ident?i=CIPSO_V4_MAP_TRANS">CIPSO_V4_MAP_TRANS</a>:
<a name="L520" href="source/net/ipv4/cipso_ipv4.c#L520">520</a>                         <a href="ident?i=type_str">type_str</a> = <i>"trans"</i>;
<a name="L521" href="source/net/ipv4/cipso_ipv4.c#L521">521</a>                         break;
<a name="L522" href="source/net/ipv4/cipso_ipv4.c#L522">522</a>                 case <a href="ident?i=CIPSO_V4_MAP_PASS">CIPSO_V4_MAP_PASS</a>:
<a name="L523" href="source/net/ipv4/cipso_ipv4.c#L523">523</a>                         <a href="ident?i=type_str">type_str</a> = <i>"pass"</i>;
<a name="L524" href="source/net/ipv4/cipso_ipv4.c#L524">524</a>                         break;
<a name="L525" href="source/net/ipv4/cipso_ipv4.c#L525">525</a>                 case <a href="ident?i=CIPSO_V4_MAP_LOCAL">CIPSO_V4_MAP_LOCAL</a>:
<a name="L526" href="source/net/ipv4/cipso_ipv4.c#L526">526</a>                         <a href="ident?i=type_str">type_str</a> = <i>"local"</i>;
<a name="L527" href="source/net/ipv4/cipso_ipv4.c#L527">527</a>                         break;
<a name="L528" href="source/net/ipv4/cipso_ipv4.c#L528">528</a>                 default:
<a name="L529" href="source/net/ipv4/cipso_ipv4.c#L529">529</a>                         <a href="ident?i=type_str">type_str</a> = <i>"(unknown)"</i>;
<a name="L530" href="source/net/ipv4/cipso_ipv4.c#L530">530</a>                 }
<a name="L531" href="source/net/ipv4/cipso_ipv4.c#L531">531</a>                 <a href="ident?i=audit_log_format">audit_log_format</a>(audit_buf,
<a name="L532" href="source/net/ipv4/cipso_ipv4.c#L532">532</a>                                  <i>" cipso_doi=%u cipso_type=%s res=%u"</i>,
<a name="L533" href="source/net/ipv4/cipso_ipv4.c#L533">533</a>                                  doi, <a href="ident?i=type_str">type_str</a>, ret_val == 0 ? 1 : 0);
<a name="L534" href="source/net/ipv4/cipso_ipv4.c#L534">534</a>                 <a href="ident?i=audit_log_end">audit_log_end</a>(audit_buf);
<a name="L535" href="source/net/ipv4/cipso_ipv4.c#L535">535</a>         }
<a name="L536" href="source/net/ipv4/cipso_ipv4.c#L536">536</a> 
<a name="L537" href="source/net/ipv4/cipso_ipv4.c#L537">537</a>         return ret_val;
<a name="L538" href="source/net/ipv4/cipso_ipv4.c#L538">538</a> }
<a name="L539" href="source/net/ipv4/cipso_ipv4.c#L539">539</a> 
<a name="L540" href="source/net/ipv4/cipso_ipv4.c#L540">540</a> <b><i>/**</i></b>
<a name="L541" href="source/net/ipv4/cipso_ipv4.c#L541">541</a> <b><i> * cipso_v4_doi_free - Frees a DOI definition</i></b>
<a name="L542" href="source/net/ipv4/cipso_ipv4.c#L542">542</a> <b><i> * @doi_def: the DOI definition</i></b>
<a name="L543" href="source/net/ipv4/cipso_ipv4.c#L543">543</a> <b><i> *</i></b>
<a name="L544" href="source/net/ipv4/cipso_ipv4.c#L544">544</a> <b><i> * Description:</i></b>
<a name="L545" href="source/net/ipv4/cipso_ipv4.c#L545">545</a> <b><i> * This function frees all of the memory associated with a DOI definition.</i></b>
<a name="L546" href="source/net/ipv4/cipso_ipv4.c#L546">546</a> <b><i> *</i></b>
<a name="L547" href="source/net/ipv4/cipso_ipv4.c#L547">547</a> <b><i> */</i></b>
<a name="L548" href="source/net/ipv4/cipso_ipv4.c#L548">548</a> void <a href="ident?i=cipso_v4_doi_free">cipso_v4_doi_free</a>(struct <a href="ident?i=cipso_v4_doi">cipso_v4_doi</a> *doi_def)
<a name="L549" href="source/net/ipv4/cipso_ipv4.c#L549">549</a> {
<a name="L550" href="source/net/ipv4/cipso_ipv4.c#L550">550</a>         if (!doi_def)
<a name="L551" href="source/net/ipv4/cipso_ipv4.c#L551">551</a>                 return;
<a name="L552" href="source/net/ipv4/cipso_ipv4.c#L552">552</a> 
<a name="L553" href="source/net/ipv4/cipso_ipv4.c#L553">553</a>         switch (doi_def-&gt;<a href="ident?i=type">type</a>) {
<a name="L554" href="source/net/ipv4/cipso_ipv4.c#L554">554</a>         case <a href="ident?i=CIPSO_V4_MAP_TRANS">CIPSO_V4_MAP_TRANS</a>:
<a name="L555" href="source/net/ipv4/cipso_ipv4.c#L555">555</a>                 <a href="ident?i=kfree">kfree</a>(doi_def-&gt;<a href="ident?i=map">map</a>.<a href="ident?i=std">std</a>-&gt;lvl.cipso);
<a name="L556" href="source/net/ipv4/cipso_ipv4.c#L556">556</a>                 <a href="ident?i=kfree">kfree</a>(doi_def-&gt;<a href="ident?i=map">map</a>.<a href="ident?i=std">std</a>-&gt;lvl.local);
<a name="L557" href="source/net/ipv4/cipso_ipv4.c#L557">557</a>                 <a href="ident?i=kfree">kfree</a>(doi_def-&gt;<a href="ident?i=map">map</a>.<a href="ident?i=std">std</a>-&gt;cat.cipso);
<a name="L558" href="source/net/ipv4/cipso_ipv4.c#L558">558</a>                 <a href="ident?i=kfree">kfree</a>(doi_def-&gt;<a href="ident?i=map">map</a>.<a href="ident?i=std">std</a>-&gt;cat.local);
<a name="L559" href="source/net/ipv4/cipso_ipv4.c#L559">559</a>                 break;
<a name="L560" href="source/net/ipv4/cipso_ipv4.c#L560">560</a>         }
<a name="L561" href="source/net/ipv4/cipso_ipv4.c#L561">561</a>         <a href="ident?i=kfree">kfree</a>(doi_def);
<a name="L562" href="source/net/ipv4/cipso_ipv4.c#L562">562</a> }
<a name="L563" href="source/net/ipv4/cipso_ipv4.c#L563">563</a> 
<a name="L564" href="source/net/ipv4/cipso_ipv4.c#L564">564</a> <b><i>/**</i></b>
<a name="L565" href="source/net/ipv4/cipso_ipv4.c#L565">565</a> <b><i> * cipso_v4_doi_free_rcu - Frees a DOI definition via the RCU pointer</i></b>
<a name="L566" href="source/net/ipv4/cipso_ipv4.c#L566">566</a> <b><i> * @entry: the entry's RCU field</i></b>
<a name="L567" href="source/net/ipv4/cipso_ipv4.c#L567">567</a> <b><i> *</i></b>
<a name="L568" href="source/net/ipv4/cipso_ipv4.c#L568">568</a> <b><i> * Description:</i></b>
<a name="L569" href="source/net/ipv4/cipso_ipv4.c#L569">569</a> <b><i> * This function is designed to be used as a callback to the call_rcu()</i></b>
<a name="L570" href="source/net/ipv4/cipso_ipv4.c#L570">570</a> <b><i> * function so that the memory allocated to the DOI definition can be released</i></b>
<a name="L571" href="source/net/ipv4/cipso_ipv4.c#L571">571</a> <b><i> * safely.</i></b>
<a name="L572" href="source/net/ipv4/cipso_ipv4.c#L572">572</a> <b><i> *</i></b>
<a name="L573" href="source/net/ipv4/cipso_ipv4.c#L573">573</a> <b><i> */</i></b>
<a name="L574" href="source/net/ipv4/cipso_ipv4.c#L574">574</a> static void <a href="ident?i=cipso_v4_doi_free_rcu">cipso_v4_doi_free_rcu</a>(struct <a href="ident?i=rcu_head">rcu_head</a> *<a href="ident?i=entry">entry</a>)
<a name="L575" href="source/net/ipv4/cipso_ipv4.c#L575">575</a> {
<a name="L576" href="source/net/ipv4/cipso_ipv4.c#L576">576</a>         struct <a href="ident?i=cipso_v4_doi">cipso_v4_doi</a> *doi_def;
<a name="L577" href="source/net/ipv4/cipso_ipv4.c#L577">577</a> 
<a name="L578" href="source/net/ipv4/cipso_ipv4.c#L578">578</a>         doi_def = <a href="ident?i=container_of">container_of</a>(<a href="ident?i=entry">entry</a>, struct <a href="ident?i=cipso_v4_doi">cipso_v4_doi</a>, rcu);
<a name="L579" href="source/net/ipv4/cipso_ipv4.c#L579">579</a>         <a href="ident?i=cipso_v4_doi_free">cipso_v4_doi_free</a>(doi_def);
<a name="L580" href="source/net/ipv4/cipso_ipv4.c#L580">580</a> }
<a name="L581" href="source/net/ipv4/cipso_ipv4.c#L581">581</a> 
<a name="L582" href="source/net/ipv4/cipso_ipv4.c#L582">582</a> <b><i>/**</i></b>
<a name="L583" href="source/net/ipv4/cipso_ipv4.c#L583">583</a> <b><i> * cipso_v4_doi_remove - Remove an existing DOI from the CIPSO protocol engine</i></b>
<a name="L584" href="source/net/ipv4/cipso_ipv4.c#L584">584</a> <b><i> * @doi: the DOI value</i></b>
<a name="L585" href="source/net/ipv4/cipso_ipv4.c#L585">585</a> <b><i> * @audit_secid: the LSM secid to use in the audit message</i></b>
<a name="L586" href="source/net/ipv4/cipso_ipv4.c#L586">586</a> <b><i> *</i></b>
<a name="L587" href="source/net/ipv4/cipso_ipv4.c#L587">587</a> <b><i> * Description:</i></b>
<a name="L588" href="source/net/ipv4/cipso_ipv4.c#L588">588</a> <b><i> * Removes a DOI definition from the CIPSO engine.  The NetLabel routines will</i></b>
<a name="L589" href="source/net/ipv4/cipso_ipv4.c#L589">589</a> <b><i> * be called to release their own LSM domain mappings as well as our own</i></b>
<a name="L590" href="source/net/ipv4/cipso_ipv4.c#L590">590</a> <b><i> * domain list.  Returns zero on success and negative values on failure.</i></b>
<a name="L591" href="source/net/ipv4/cipso_ipv4.c#L591">591</a> <b><i> *</i></b>
<a name="L592" href="source/net/ipv4/cipso_ipv4.c#L592">592</a> <b><i> */</i></b>
<a name="L593" href="source/net/ipv4/cipso_ipv4.c#L593">593</a> int <a href="ident?i=cipso_v4_doi_remove">cipso_v4_doi_remove</a>(<a href="ident?i=u32">u32</a> doi, struct <a href="ident?i=netlbl_audit">netlbl_audit</a> *audit_info)
<a name="L594" href="source/net/ipv4/cipso_ipv4.c#L594">594</a> {
<a name="L595" href="source/net/ipv4/cipso_ipv4.c#L595">595</a>         int ret_val;
<a name="L596" href="source/net/ipv4/cipso_ipv4.c#L596">596</a>         struct <a href="ident?i=cipso_v4_doi">cipso_v4_doi</a> *doi_def;
<a name="L597" href="source/net/ipv4/cipso_ipv4.c#L597">597</a>         struct <a href="ident?i=audit_buffer">audit_buffer</a> *audit_buf;
<a name="L598" href="source/net/ipv4/cipso_ipv4.c#L598">598</a> 
<a name="L599" href="source/net/ipv4/cipso_ipv4.c#L599">599</a>         <a href="ident?i=spin_lock">spin_lock</a>(&amp;cipso_v4_doi_list_lock);
<a name="L600" href="source/net/ipv4/cipso_ipv4.c#L600">600</a>         doi_def = <a href="ident?i=cipso_v4_doi_search">cipso_v4_doi_search</a>(doi);
<a name="L601" href="source/net/ipv4/cipso_ipv4.c#L601">601</a>         if (!doi_def) {
<a name="L602" href="source/net/ipv4/cipso_ipv4.c#L602">602</a>                 <a href="ident?i=spin_unlock">spin_unlock</a>(&amp;cipso_v4_doi_list_lock);
<a name="L603" href="source/net/ipv4/cipso_ipv4.c#L603">603</a>                 ret_val = -<a href="ident?i=ENOENT">ENOENT</a>;
<a name="L604" href="source/net/ipv4/cipso_ipv4.c#L604">604</a>                 goto doi_remove_return;
<a name="L605" href="source/net/ipv4/cipso_ipv4.c#L605">605</a>         }
<a name="L606" href="source/net/ipv4/cipso_ipv4.c#L606">606</a>         if (!<a href="ident?i=atomic_dec_and_test">atomic_dec_and_test</a>(&amp;doi_def-&gt;refcount)) {
<a name="L607" href="source/net/ipv4/cipso_ipv4.c#L607">607</a>                 <a href="ident?i=spin_unlock">spin_unlock</a>(&amp;cipso_v4_doi_list_lock);
<a name="L608" href="source/net/ipv4/cipso_ipv4.c#L608">608</a>                 ret_val = -<a href="ident?i=EBUSY">EBUSY</a>;
<a name="L609" href="source/net/ipv4/cipso_ipv4.c#L609">609</a>                 goto doi_remove_return;
<a name="L610" href="source/net/ipv4/cipso_ipv4.c#L610">610</a>         }
<a name="L611" href="source/net/ipv4/cipso_ipv4.c#L611">611</a>         <a href="ident?i=list_del_rcu">list_del_rcu</a>(&amp;doi_def-&gt;<a href="ident?i=list">list</a>);
<a name="L612" href="source/net/ipv4/cipso_ipv4.c#L612">612</a>         <a href="ident?i=spin_unlock">spin_unlock</a>(&amp;cipso_v4_doi_list_lock);
<a name="L613" href="source/net/ipv4/cipso_ipv4.c#L613">613</a> 
<a name="L614" href="source/net/ipv4/cipso_ipv4.c#L614">614</a>         <a href="ident?i=cipso_v4_cache_invalidate">cipso_v4_cache_invalidate</a>();
<a name="L615" href="source/net/ipv4/cipso_ipv4.c#L615">615</a>         <a href="ident?i=call_rcu">call_rcu</a>(&amp;doi_def-&gt;rcu, <a href="ident?i=cipso_v4_doi_free_rcu">cipso_v4_doi_free_rcu</a>);
<a name="L616" href="source/net/ipv4/cipso_ipv4.c#L616">616</a>         ret_val = 0;
<a name="L617" href="source/net/ipv4/cipso_ipv4.c#L617">617</a> 
<a name="L618" href="source/net/ipv4/cipso_ipv4.c#L618">618</a> doi_remove_return:
<a name="L619" href="source/net/ipv4/cipso_ipv4.c#L619">619</a>         audit_buf = <a href="ident?i=netlbl_audit_start">netlbl_audit_start</a>(<a href="ident?i=AUDIT_MAC_CIPSOV4_DEL">AUDIT_MAC_CIPSOV4_DEL</a>, audit_info);
<a name="L620" href="source/net/ipv4/cipso_ipv4.c#L620">620</a>         if (audit_buf) {
<a name="L621" href="source/net/ipv4/cipso_ipv4.c#L621">621</a>                 <a href="ident?i=audit_log_format">audit_log_format</a>(audit_buf,
<a name="L622" href="source/net/ipv4/cipso_ipv4.c#L622">622</a>                                  <i>" cipso_doi=%u res=%u"</i>,
<a name="L623" href="source/net/ipv4/cipso_ipv4.c#L623">623</a>                                  doi, ret_val == 0 ? 1 : 0);
<a name="L624" href="source/net/ipv4/cipso_ipv4.c#L624">624</a>                 <a href="ident?i=audit_log_end">audit_log_end</a>(audit_buf);
<a name="L625" href="source/net/ipv4/cipso_ipv4.c#L625">625</a>         }
<a name="L626" href="source/net/ipv4/cipso_ipv4.c#L626">626</a> 
<a name="L627" href="source/net/ipv4/cipso_ipv4.c#L627">627</a>         return ret_val;
<a name="L628" href="source/net/ipv4/cipso_ipv4.c#L628">628</a> }
<a name="L629" href="source/net/ipv4/cipso_ipv4.c#L629">629</a> 
<a name="L630" href="source/net/ipv4/cipso_ipv4.c#L630">630</a> <b><i>/**</i></b>
<a name="L631" href="source/net/ipv4/cipso_ipv4.c#L631">631</a> <b><i> * cipso_v4_doi_getdef - Returns a reference to a valid DOI definition</i></b>
<a name="L632" href="source/net/ipv4/cipso_ipv4.c#L632">632</a> <b><i> * @doi: the DOI value</i></b>
<a name="L633" href="source/net/ipv4/cipso_ipv4.c#L633">633</a> <b><i> *</i></b>
<a name="L634" href="source/net/ipv4/cipso_ipv4.c#L634">634</a> <b><i> * Description:</i></b>
<a name="L635" href="source/net/ipv4/cipso_ipv4.c#L635">635</a> <b><i> * Searches for a valid DOI definition and if one is found it is returned to</i></b>
<a name="L636" href="source/net/ipv4/cipso_ipv4.c#L636">636</a> <b><i> * the caller.  Otherwise NULL is returned.  The caller must ensure that</i></b>
<a name="L637" href="source/net/ipv4/cipso_ipv4.c#L637">637</a> <b><i> * rcu_read_lock() is held while accessing the returned definition and the DOI</i></b>
<a name="L638" href="source/net/ipv4/cipso_ipv4.c#L638">638</a> <b><i> * definition reference count is decremented when the caller is done.</i></b>
<a name="L639" href="source/net/ipv4/cipso_ipv4.c#L639">639</a> <b><i> *</i></b>
<a name="L640" href="source/net/ipv4/cipso_ipv4.c#L640">640</a> <b><i> */</i></b>
<a name="L641" href="source/net/ipv4/cipso_ipv4.c#L641">641</a> struct <a href="ident?i=cipso_v4_doi">cipso_v4_doi</a> *<a href="ident?i=cipso_v4_doi_getdef">cipso_v4_doi_getdef</a>(<a href="ident?i=u32">u32</a> doi)
<a name="L642" href="source/net/ipv4/cipso_ipv4.c#L642">642</a> {
<a name="L643" href="source/net/ipv4/cipso_ipv4.c#L643">643</a>         struct <a href="ident?i=cipso_v4_doi">cipso_v4_doi</a> *doi_def;
<a name="L644" href="source/net/ipv4/cipso_ipv4.c#L644">644</a> 
<a name="L645" href="source/net/ipv4/cipso_ipv4.c#L645">645</a>         <a href="ident?i=rcu_read_lock">rcu_read_lock</a>();
<a name="L646" href="source/net/ipv4/cipso_ipv4.c#L646">646</a>         doi_def = <a href="ident?i=cipso_v4_doi_search">cipso_v4_doi_search</a>(doi);
<a name="L647" href="source/net/ipv4/cipso_ipv4.c#L647">647</a>         if (!doi_def)
<a name="L648" href="source/net/ipv4/cipso_ipv4.c#L648">648</a>                 goto doi_getdef_return;
<a name="L649" href="source/net/ipv4/cipso_ipv4.c#L649">649</a>         if (!<a href="ident?i=atomic_inc_not_zero">atomic_inc_not_zero</a>(&amp;doi_def-&gt;refcount))
<a name="L650" href="source/net/ipv4/cipso_ipv4.c#L650">650</a>                 doi_def = <a href="ident?i=NULL">NULL</a>;
<a name="L651" href="source/net/ipv4/cipso_ipv4.c#L651">651</a> 
<a name="L652" href="source/net/ipv4/cipso_ipv4.c#L652">652</a> doi_getdef_return:
<a name="L653" href="source/net/ipv4/cipso_ipv4.c#L653">653</a>         <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L654" href="source/net/ipv4/cipso_ipv4.c#L654">654</a>         return doi_def;
<a name="L655" href="source/net/ipv4/cipso_ipv4.c#L655">655</a> }
<a name="L656" href="source/net/ipv4/cipso_ipv4.c#L656">656</a> 
<a name="L657" href="source/net/ipv4/cipso_ipv4.c#L657">657</a> <b><i>/**</i></b>
<a name="L658" href="source/net/ipv4/cipso_ipv4.c#L658">658</a> <b><i> * cipso_v4_doi_putdef - Releases a reference for the given DOI definition</i></b>
<a name="L659" href="source/net/ipv4/cipso_ipv4.c#L659">659</a> <b><i> * @doi_def: the DOI definition</i></b>
<a name="L660" href="source/net/ipv4/cipso_ipv4.c#L660">660</a> <b><i> *</i></b>
<a name="L661" href="source/net/ipv4/cipso_ipv4.c#L661">661</a> <b><i> * Description:</i></b>
<a name="L662" href="source/net/ipv4/cipso_ipv4.c#L662">662</a> <b><i> * Releases a DOI definition reference obtained from cipso_v4_doi_getdef().</i></b>
<a name="L663" href="source/net/ipv4/cipso_ipv4.c#L663">663</a> <b><i> *</i></b>
<a name="L664" href="source/net/ipv4/cipso_ipv4.c#L664">664</a> <b><i> */</i></b>
<a name="L665" href="source/net/ipv4/cipso_ipv4.c#L665">665</a> void <a href="ident?i=cipso_v4_doi_putdef">cipso_v4_doi_putdef</a>(struct <a href="ident?i=cipso_v4_doi">cipso_v4_doi</a> *doi_def)
<a name="L666" href="source/net/ipv4/cipso_ipv4.c#L666">666</a> {
<a name="L667" href="source/net/ipv4/cipso_ipv4.c#L667">667</a>         if (!doi_def)
<a name="L668" href="source/net/ipv4/cipso_ipv4.c#L668">668</a>                 return;
<a name="L669" href="source/net/ipv4/cipso_ipv4.c#L669">669</a> 
<a name="L670" href="source/net/ipv4/cipso_ipv4.c#L670">670</a>         if (!<a href="ident?i=atomic_dec_and_test">atomic_dec_and_test</a>(&amp;doi_def-&gt;refcount))
<a name="L671" href="source/net/ipv4/cipso_ipv4.c#L671">671</a>                 return;
<a name="L672" href="source/net/ipv4/cipso_ipv4.c#L672">672</a>         <a href="ident?i=spin_lock">spin_lock</a>(&amp;cipso_v4_doi_list_lock);
<a name="L673" href="source/net/ipv4/cipso_ipv4.c#L673">673</a>         <a href="ident?i=list_del_rcu">list_del_rcu</a>(&amp;doi_def-&gt;<a href="ident?i=list">list</a>);
<a name="L674" href="source/net/ipv4/cipso_ipv4.c#L674">674</a>         <a href="ident?i=spin_unlock">spin_unlock</a>(&amp;cipso_v4_doi_list_lock);
<a name="L675" href="source/net/ipv4/cipso_ipv4.c#L675">675</a> 
<a name="L676" href="source/net/ipv4/cipso_ipv4.c#L676">676</a>         <a href="ident?i=cipso_v4_cache_invalidate">cipso_v4_cache_invalidate</a>();
<a name="L677" href="source/net/ipv4/cipso_ipv4.c#L677">677</a>         <a href="ident?i=call_rcu">call_rcu</a>(&amp;doi_def-&gt;rcu, <a href="ident?i=cipso_v4_doi_free_rcu">cipso_v4_doi_free_rcu</a>);
<a name="L678" href="source/net/ipv4/cipso_ipv4.c#L678">678</a> }
<a name="L679" href="source/net/ipv4/cipso_ipv4.c#L679">679</a> 
<a name="L680" href="source/net/ipv4/cipso_ipv4.c#L680">680</a> <b><i>/**</i></b>
<a name="L681" href="source/net/ipv4/cipso_ipv4.c#L681">681</a> <b><i> * cipso_v4_doi_walk - Iterate through the DOI definitions</i></b>
<a name="L682" href="source/net/ipv4/cipso_ipv4.c#L682">682</a> <b><i> * @skip_cnt: skip past this number of DOI definitions, updated</i></b>
<a name="L683" href="source/net/ipv4/cipso_ipv4.c#L683">683</a> <b><i> * @callback: callback for each DOI definition</i></b>
<a name="L684" href="source/net/ipv4/cipso_ipv4.c#L684">684</a> <b><i> * @cb_arg: argument for the callback function</i></b>
<a name="L685" href="source/net/ipv4/cipso_ipv4.c#L685">685</a> <b><i> *</i></b>
<a name="L686" href="source/net/ipv4/cipso_ipv4.c#L686">686</a> <b><i> * Description:</i></b>
<a name="L687" href="source/net/ipv4/cipso_ipv4.c#L687">687</a> <b><i> * Iterate over the DOI definition list, skipping the first @skip_cnt entries.</i></b>
<a name="L688" href="source/net/ipv4/cipso_ipv4.c#L688">688</a> <b><i> * For each entry call @callback, if @callback returns a negative value stop</i></b>
<a name="L689" href="source/net/ipv4/cipso_ipv4.c#L689">689</a> <b><i> * 'walking' through the list and return.  Updates the value in @skip_cnt upon</i></b>
<a name="L690" href="source/net/ipv4/cipso_ipv4.c#L690">690</a> <b><i> * return.  Returns zero on success, negative values on failure.</i></b>
<a name="L691" href="source/net/ipv4/cipso_ipv4.c#L691">691</a> <b><i> *</i></b>
<a name="L692" href="source/net/ipv4/cipso_ipv4.c#L692">692</a> <b><i> */</i></b>
<a name="L693" href="source/net/ipv4/cipso_ipv4.c#L693">693</a> int <a href="ident?i=cipso_v4_doi_walk">cipso_v4_doi_walk</a>(<a href="ident?i=u32">u32</a> *skip_cnt,
<a name="L694" href="source/net/ipv4/cipso_ipv4.c#L694">694</a>                      int (*<a href="ident?i=callback">callback</a>) (struct <a href="ident?i=cipso_v4_doi">cipso_v4_doi</a> *doi_def, void *<a href="ident?i=arg">arg</a>),
<a name="L695" href="source/net/ipv4/cipso_ipv4.c#L695">695</a>                      void *<a href="ident?i=cb_arg">cb_arg</a>)
<a name="L696" href="source/net/ipv4/cipso_ipv4.c#L696">696</a> {
<a name="L697" href="source/net/ipv4/cipso_ipv4.c#L697">697</a>         int ret_val = -<a href="ident?i=ENOENT">ENOENT</a>;
<a name="L698" href="source/net/ipv4/cipso_ipv4.c#L698">698</a>         <a href="ident?i=u32">u32</a> doi_cnt = 0;
<a name="L699" href="source/net/ipv4/cipso_ipv4.c#L699">699</a>         struct <a href="ident?i=cipso_v4_doi">cipso_v4_doi</a> *iter_doi;
<a name="L700" href="source/net/ipv4/cipso_ipv4.c#L700">700</a> 
<a name="L701" href="source/net/ipv4/cipso_ipv4.c#L701">701</a>         <a href="ident?i=rcu_read_lock">rcu_read_lock</a>();
<a name="L702" href="source/net/ipv4/cipso_ipv4.c#L702">702</a>         <a href="ident?i=list_for_each_entry_rcu">list_for_each_entry_rcu</a>(iter_doi, &amp;cipso_v4_doi_list, <a href="ident?i=list">list</a>)
<a name="L703" href="source/net/ipv4/cipso_ipv4.c#L703">703</a>                 if (<a href="ident?i=atomic_read">atomic_read</a>(&amp;iter_doi-&gt;refcount) &gt; 0) {
<a name="L704" href="source/net/ipv4/cipso_ipv4.c#L704">704</a>                         if (doi_cnt++ &lt; *skip_cnt)
<a name="L705" href="source/net/ipv4/cipso_ipv4.c#L705">705</a>                                 continue;
<a name="L706" href="source/net/ipv4/cipso_ipv4.c#L706">706</a>                         ret_val = <a href="ident?i=callback">callback</a>(iter_doi, <a href="ident?i=cb_arg">cb_arg</a>);
<a name="L707" href="source/net/ipv4/cipso_ipv4.c#L707">707</a>                         if (ret_val &lt; 0) {
<a name="L708" href="source/net/ipv4/cipso_ipv4.c#L708">708</a>                                 doi_cnt--;
<a name="L709" href="source/net/ipv4/cipso_ipv4.c#L709">709</a>                                 goto doi_walk_return;
<a name="L710" href="source/net/ipv4/cipso_ipv4.c#L710">710</a>                         }
<a name="L711" href="source/net/ipv4/cipso_ipv4.c#L711">711</a>                 }
<a name="L712" href="source/net/ipv4/cipso_ipv4.c#L712">712</a> 
<a name="L713" href="source/net/ipv4/cipso_ipv4.c#L713">713</a> doi_walk_return:
<a name="L714" href="source/net/ipv4/cipso_ipv4.c#L714">714</a>         <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L715" href="source/net/ipv4/cipso_ipv4.c#L715">715</a>         *skip_cnt = doi_cnt;
<a name="L716" href="source/net/ipv4/cipso_ipv4.c#L716">716</a>         return ret_val;
<a name="L717" href="source/net/ipv4/cipso_ipv4.c#L717">717</a> }
<a name="L718" href="source/net/ipv4/cipso_ipv4.c#L718">718</a> 
<a name="L719" href="source/net/ipv4/cipso_ipv4.c#L719">719</a> <b><i>/*</i></b>
<a name="L720" href="source/net/ipv4/cipso_ipv4.c#L720">720</a> <b><i> * Label Mapping Functions</i></b>
<a name="L721" href="source/net/ipv4/cipso_ipv4.c#L721">721</a> <b><i> */</i></b>
<a name="L722" href="source/net/ipv4/cipso_ipv4.c#L722">722</a> 
<a name="L723" href="source/net/ipv4/cipso_ipv4.c#L723">723</a> <b><i>/**</i></b>
<a name="L724" href="source/net/ipv4/cipso_ipv4.c#L724">724</a> <b><i> * cipso_v4_map_lvl_valid - Checks to see if the given level is understood</i></b>
<a name="L725" href="source/net/ipv4/cipso_ipv4.c#L725">725</a> <b><i> * @doi_def: the DOI definition</i></b>
<a name="L726" href="source/net/ipv4/cipso_ipv4.c#L726">726</a> <b><i> * @level: the level to check</i></b>
<a name="L727" href="source/net/ipv4/cipso_ipv4.c#L727">727</a> <b><i> *</i></b>
<a name="L728" href="source/net/ipv4/cipso_ipv4.c#L728">728</a> <b><i> * Description:</i></b>
<a name="L729" href="source/net/ipv4/cipso_ipv4.c#L729">729</a> <b><i> * Checks the given level against the given DOI definition and returns a</i></b>
<a name="L730" href="source/net/ipv4/cipso_ipv4.c#L730">730</a> <b><i> * negative value if the level does not have a valid mapping and a zero value</i></b>
<a name="L731" href="source/net/ipv4/cipso_ipv4.c#L731">731</a> <b><i> * if the level is defined by the DOI.</i></b>
<a name="L732" href="source/net/ipv4/cipso_ipv4.c#L732">732</a> <b><i> *</i></b>
<a name="L733" href="source/net/ipv4/cipso_ipv4.c#L733">733</a> <b><i> */</i></b>
<a name="L734" href="source/net/ipv4/cipso_ipv4.c#L734">734</a> static int <a href="ident?i=cipso_v4_map_lvl_valid">cipso_v4_map_lvl_valid</a>(const struct <a href="ident?i=cipso_v4_doi">cipso_v4_doi</a> *doi_def, <a href="ident?i=u8">u8</a> <a href="ident?i=level">level</a>)
<a name="L735" href="source/net/ipv4/cipso_ipv4.c#L735">735</a> {
<a name="L736" href="source/net/ipv4/cipso_ipv4.c#L736">736</a>         switch (doi_def-&gt;<a href="ident?i=type">type</a>) {
<a name="L737" href="source/net/ipv4/cipso_ipv4.c#L737">737</a>         case <a href="ident?i=CIPSO_V4_MAP_PASS">CIPSO_V4_MAP_PASS</a>:
<a name="L738" href="source/net/ipv4/cipso_ipv4.c#L738">738</a>                 return 0;
<a name="L739" href="source/net/ipv4/cipso_ipv4.c#L739">739</a>         case <a href="ident?i=CIPSO_V4_MAP_TRANS">CIPSO_V4_MAP_TRANS</a>:
<a name="L740" href="source/net/ipv4/cipso_ipv4.c#L740">740</a>                 if (doi_def-&gt;<a href="ident?i=map">map</a>.<a href="ident?i=std">std</a>-&gt;lvl.cipso[<a href="ident?i=level">level</a>] &lt; <a href="ident?i=CIPSO_V4_INV_LVL">CIPSO_V4_INV_LVL</a>)
<a name="L741" href="source/net/ipv4/cipso_ipv4.c#L741">741</a>                         return 0;
<a name="L742" href="source/net/ipv4/cipso_ipv4.c#L742">742</a>                 break;
<a name="L743" href="source/net/ipv4/cipso_ipv4.c#L743">743</a>         }
<a name="L744" href="source/net/ipv4/cipso_ipv4.c#L744">744</a> 
<a name="L745" href="source/net/ipv4/cipso_ipv4.c#L745">745</a>         return -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L746" href="source/net/ipv4/cipso_ipv4.c#L746">746</a> }
<a name="L747" href="source/net/ipv4/cipso_ipv4.c#L747">747</a> 
<a name="L748" href="source/net/ipv4/cipso_ipv4.c#L748">748</a> <b><i>/**</i></b>
<a name="L749" href="source/net/ipv4/cipso_ipv4.c#L749">749</a> <b><i> * cipso_v4_map_lvl_hton - Perform a level mapping from the host to the network</i></b>
<a name="L750" href="source/net/ipv4/cipso_ipv4.c#L750">750</a> <b><i> * @doi_def: the DOI definition</i></b>
<a name="L751" href="source/net/ipv4/cipso_ipv4.c#L751">751</a> <b><i> * @host_lvl: the host MLS level</i></b>
<a name="L752" href="source/net/ipv4/cipso_ipv4.c#L752">752</a> <b><i> * @net_lvl: the network/CIPSO MLS level</i></b>
<a name="L753" href="source/net/ipv4/cipso_ipv4.c#L753">753</a> <b><i> *</i></b>
<a name="L754" href="source/net/ipv4/cipso_ipv4.c#L754">754</a> <b><i> * Description:</i></b>
<a name="L755" href="source/net/ipv4/cipso_ipv4.c#L755">755</a> <b><i> * Perform a label mapping to translate a local MLS level to the correct</i></b>
<a name="L756" href="source/net/ipv4/cipso_ipv4.c#L756">756</a> <b><i> * CIPSO level using the given DOI definition.  Returns zero on success,</i></b>
<a name="L757" href="source/net/ipv4/cipso_ipv4.c#L757">757</a> <b><i> * negative values otherwise.</i></b>
<a name="L758" href="source/net/ipv4/cipso_ipv4.c#L758">758</a> <b><i> *</i></b>
<a name="L759" href="source/net/ipv4/cipso_ipv4.c#L759">759</a> <b><i> */</i></b>
<a name="L760" href="source/net/ipv4/cipso_ipv4.c#L760">760</a> static int <a href="ident?i=cipso_v4_map_lvl_hton">cipso_v4_map_lvl_hton</a>(const struct <a href="ident?i=cipso_v4_doi">cipso_v4_doi</a> *doi_def,
<a name="L761" href="source/net/ipv4/cipso_ipv4.c#L761">761</a>                                  <a href="ident?i=u32">u32</a> host_lvl,
<a name="L762" href="source/net/ipv4/cipso_ipv4.c#L762">762</a>                                  <a href="ident?i=u32">u32</a> *net_lvl)
<a name="L763" href="source/net/ipv4/cipso_ipv4.c#L763">763</a> {
<a name="L764" href="source/net/ipv4/cipso_ipv4.c#L764">764</a>         switch (doi_def-&gt;<a href="ident?i=type">type</a>) {
<a name="L765" href="source/net/ipv4/cipso_ipv4.c#L765">765</a>         case <a href="ident?i=CIPSO_V4_MAP_PASS">CIPSO_V4_MAP_PASS</a>:
<a name="L766" href="source/net/ipv4/cipso_ipv4.c#L766">766</a>                 *net_lvl = host_lvl;
<a name="L767" href="source/net/ipv4/cipso_ipv4.c#L767">767</a>                 return 0;
<a name="L768" href="source/net/ipv4/cipso_ipv4.c#L768">768</a>         case <a href="ident?i=CIPSO_V4_MAP_TRANS">CIPSO_V4_MAP_TRANS</a>:
<a name="L769" href="source/net/ipv4/cipso_ipv4.c#L769">769</a>                 if (host_lvl &lt; doi_def-&gt;<a href="ident?i=map">map</a>.<a href="ident?i=std">std</a>-&gt;lvl.local_size &amp;&amp;
<a name="L770" href="source/net/ipv4/cipso_ipv4.c#L770">770</a>                     doi_def-&gt;<a href="ident?i=map">map</a>.<a href="ident?i=std">std</a>-&gt;lvl.local[host_lvl] &lt; <a href="ident?i=CIPSO_V4_INV_LVL">CIPSO_V4_INV_LVL</a>) {
<a name="L771" href="source/net/ipv4/cipso_ipv4.c#L771">771</a>                         *net_lvl = doi_def-&gt;<a href="ident?i=map">map</a>.<a href="ident?i=std">std</a>-&gt;lvl.local[host_lvl];
<a name="L772" href="source/net/ipv4/cipso_ipv4.c#L772">772</a>                         return 0;
<a name="L773" href="source/net/ipv4/cipso_ipv4.c#L773">773</a>                 }
<a name="L774" href="source/net/ipv4/cipso_ipv4.c#L774">774</a>                 return -<a href="ident?i=EPERM">EPERM</a>;
<a name="L775" href="source/net/ipv4/cipso_ipv4.c#L775">775</a>         }
<a name="L776" href="source/net/ipv4/cipso_ipv4.c#L776">776</a> 
<a name="L777" href="source/net/ipv4/cipso_ipv4.c#L777">777</a>         return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L778" href="source/net/ipv4/cipso_ipv4.c#L778">778</a> }
<a name="L779" href="source/net/ipv4/cipso_ipv4.c#L779">779</a> 
<a name="L780" href="source/net/ipv4/cipso_ipv4.c#L780">780</a> <b><i>/**</i></b>
<a name="L781" href="source/net/ipv4/cipso_ipv4.c#L781">781</a> <b><i> * cipso_v4_map_lvl_ntoh - Perform a level mapping from the network to the host</i></b>
<a name="L782" href="source/net/ipv4/cipso_ipv4.c#L782">782</a> <b><i> * @doi_def: the DOI definition</i></b>
<a name="L783" href="source/net/ipv4/cipso_ipv4.c#L783">783</a> <b><i> * @net_lvl: the network/CIPSO MLS level</i></b>
<a name="L784" href="source/net/ipv4/cipso_ipv4.c#L784">784</a> <b><i> * @host_lvl: the host MLS level</i></b>
<a name="L785" href="source/net/ipv4/cipso_ipv4.c#L785">785</a> <b><i> *</i></b>
<a name="L786" href="source/net/ipv4/cipso_ipv4.c#L786">786</a> <b><i> * Description:</i></b>
<a name="L787" href="source/net/ipv4/cipso_ipv4.c#L787">787</a> <b><i> * Perform a label mapping to translate a CIPSO level to the correct local MLS</i></b>
<a name="L788" href="source/net/ipv4/cipso_ipv4.c#L788">788</a> <b><i> * level using the given DOI definition.  Returns zero on success, negative</i></b>
<a name="L789" href="source/net/ipv4/cipso_ipv4.c#L789">789</a> <b><i> * values otherwise.</i></b>
<a name="L790" href="source/net/ipv4/cipso_ipv4.c#L790">790</a> <b><i> *</i></b>
<a name="L791" href="source/net/ipv4/cipso_ipv4.c#L791">791</a> <b><i> */</i></b>
<a name="L792" href="source/net/ipv4/cipso_ipv4.c#L792">792</a> static int <a href="ident?i=cipso_v4_map_lvl_ntoh">cipso_v4_map_lvl_ntoh</a>(const struct <a href="ident?i=cipso_v4_doi">cipso_v4_doi</a> *doi_def,
<a name="L793" href="source/net/ipv4/cipso_ipv4.c#L793">793</a>                                  <a href="ident?i=u32">u32</a> net_lvl,
<a name="L794" href="source/net/ipv4/cipso_ipv4.c#L794">794</a>                                  <a href="ident?i=u32">u32</a> *host_lvl)
<a name="L795" href="source/net/ipv4/cipso_ipv4.c#L795">795</a> {
<a name="L796" href="source/net/ipv4/cipso_ipv4.c#L796">796</a>         struct <a href="ident?i=cipso_v4_std_map_tbl">cipso_v4_std_map_tbl</a> *map_tbl;
<a name="L797" href="source/net/ipv4/cipso_ipv4.c#L797">797</a> 
<a name="L798" href="source/net/ipv4/cipso_ipv4.c#L798">798</a>         switch (doi_def-&gt;<a href="ident?i=type">type</a>) {
<a name="L799" href="source/net/ipv4/cipso_ipv4.c#L799">799</a>         case <a href="ident?i=CIPSO_V4_MAP_PASS">CIPSO_V4_MAP_PASS</a>:
<a name="L800" href="source/net/ipv4/cipso_ipv4.c#L800">800</a>                 *host_lvl = net_lvl;
<a name="L801" href="source/net/ipv4/cipso_ipv4.c#L801">801</a>                 return 0;
<a name="L802" href="source/net/ipv4/cipso_ipv4.c#L802">802</a>         case <a href="ident?i=CIPSO_V4_MAP_TRANS">CIPSO_V4_MAP_TRANS</a>:
<a name="L803" href="source/net/ipv4/cipso_ipv4.c#L803">803</a>                 map_tbl = doi_def-&gt;<a href="ident?i=map">map</a>.<a href="ident?i=std">std</a>;
<a name="L804" href="source/net/ipv4/cipso_ipv4.c#L804">804</a>                 if (net_lvl &lt; map_tbl-&gt;lvl.cipso_size &amp;&amp;
<a name="L805" href="source/net/ipv4/cipso_ipv4.c#L805">805</a>                     map_tbl-&gt;lvl.cipso[net_lvl] &lt; <a href="ident?i=CIPSO_V4_INV_LVL">CIPSO_V4_INV_LVL</a>) {
<a name="L806" href="source/net/ipv4/cipso_ipv4.c#L806">806</a>                         *host_lvl = doi_def-&gt;<a href="ident?i=map">map</a>.<a href="ident?i=std">std</a>-&gt;lvl.cipso[net_lvl];
<a name="L807" href="source/net/ipv4/cipso_ipv4.c#L807">807</a>                         return 0;
<a name="L808" href="source/net/ipv4/cipso_ipv4.c#L808">808</a>                 }
<a name="L809" href="source/net/ipv4/cipso_ipv4.c#L809">809</a>                 return -<a href="ident?i=EPERM">EPERM</a>;
<a name="L810" href="source/net/ipv4/cipso_ipv4.c#L810">810</a>         }
<a name="L811" href="source/net/ipv4/cipso_ipv4.c#L811">811</a> 
<a name="L812" href="source/net/ipv4/cipso_ipv4.c#L812">812</a>         return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L813" href="source/net/ipv4/cipso_ipv4.c#L813">813</a> }
<a name="L814" href="source/net/ipv4/cipso_ipv4.c#L814">814</a> 
<a name="L815" href="source/net/ipv4/cipso_ipv4.c#L815">815</a> <b><i>/**</i></b>
<a name="L816" href="source/net/ipv4/cipso_ipv4.c#L816">816</a> <b><i> * cipso_v4_map_cat_rbm_valid - Checks to see if the category bitmap is valid</i></b>
<a name="L817" href="source/net/ipv4/cipso_ipv4.c#L817">817</a> <b><i> * @doi_def: the DOI definition</i></b>
<a name="L818" href="source/net/ipv4/cipso_ipv4.c#L818">818</a> <b><i> * @bitmap: category bitmap</i></b>
<a name="L819" href="source/net/ipv4/cipso_ipv4.c#L819">819</a> <b><i> * @bitmap_len: bitmap length in bytes</i></b>
<a name="L820" href="source/net/ipv4/cipso_ipv4.c#L820">820</a> <b><i> *</i></b>
<a name="L821" href="source/net/ipv4/cipso_ipv4.c#L821">821</a> <b><i> * Description:</i></b>
<a name="L822" href="source/net/ipv4/cipso_ipv4.c#L822">822</a> <b><i> * Checks the given category bitmap against the given DOI definition and</i></b>
<a name="L823" href="source/net/ipv4/cipso_ipv4.c#L823">823</a> <b><i> * returns a negative value if any of the categories in the bitmap do not have</i></b>
<a name="L824" href="source/net/ipv4/cipso_ipv4.c#L824">824</a> <b><i> * a valid mapping and a zero value if all of the categories are valid.</i></b>
<a name="L825" href="source/net/ipv4/cipso_ipv4.c#L825">825</a> <b><i> *</i></b>
<a name="L826" href="source/net/ipv4/cipso_ipv4.c#L826">826</a> <b><i> */</i></b>
<a name="L827" href="source/net/ipv4/cipso_ipv4.c#L827">827</a> static int <a href="ident?i=cipso_v4_map_cat_rbm_valid">cipso_v4_map_cat_rbm_valid</a>(const struct <a href="ident?i=cipso_v4_doi">cipso_v4_doi</a> *doi_def,
<a name="L828" href="source/net/ipv4/cipso_ipv4.c#L828">828</a>                                       const unsigned char *<a href="ident?i=bitmap">bitmap</a>,
<a name="L829" href="source/net/ipv4/cipso_ipv4.c#L829">829</a>                                       <a href="ident?i=u32">u32</a> bitmap_len)
<a name="L830" href="source/net/ipv4/cipso_ipv4.c#L830">830</a> {
<a name="L831" href="source/net/ipv4/cipso_ipv4.c#L831">831</a>         int cat = -1;
<a name="L832" href="source/net/ipv4/cipso_ipv4.c#L832">832</a>         <a href="ident?i=u32">u32</a> bitmap_len_bits = bitmap_len * 8;
<a name="L833" href="source/net/ipv4/cipso_ipv4.c#L833">833</a>         <a href="ident?i=u32">u32</a> cipso_cat_size;
<a name="L834" href="source/net/ipv4/cipso_ipv4.c#L834">834</a>         <a href="ident?i=u32">u32</a> *cipso_array;
<a name="L835" href="source/net/ipv4/cipso_ipv4.c#L835">835</a> 
<a name="L836" href="source/net/ipv4/cipso_ipv4.c#L836">836</a>         switch (doi_def-&gt;<a href="ident?i=type">type</a>) {
<a name="L837" href="source/net/ipv4/cipso_ipv4.c#L837">837</a>         case <a href="ident?i=CIPSO_V4_MAP_PASS">CIPSO_V4_MAP_PASS</a>:
<a name="L838" href="source/net/ipv4/cipso_ipv4.c#L838">838</a>                 return 0;
<a name="L839" href="source/net/ipv4/cipso_ipv4.c#L839">839</a>         case <a href="ident?i=CIPSO_V4_MAP_TRANS">CIPSO_V4_MAP_TRANS</a>:
<a name="L840" href="source/net/ipv4/cipso_ipv4.c#L840">840</a>                 cipso_cat_size = doi_def-&gt;<a href="ident?i=map">map</a>.<a href="ident?i=std">std</a>-&gt;cat.cipso_size;
<a name="L841" href="source/net/ipv4/cipso_ipv4.c#L841">841</a>                 cipso_array = doi_def-&gt;<a href="ident?i=map">map</a>.<a href="ident?i=std">std</a>-&gt;cat.cipso;
<a name="L842" href="source/net/ipv4/cipso_ipv4.c#L842">842</a>                 for (;;) {
<a name="L843" href="source/net/ipv4/cipso_ipv4.c#L843">843</a>                         cat = <a href="ident?i=cipso_v4_bitmap_walk">cipso_v4_bitmap_walk</a>(<a href="ident?i=bitmap">bitmap</a>,
<a name="L844" href="source/net/ipv4/cipso_ipv4.c#L844">844</a>                                                    bitmap_len_bits,
<a name="L845" href="source/net/ipv4/cipso_ipv4.c#L845">845</a>                                                    cat + 1,
<a name="L846" href="source/net/ipv4/cipso_ipv4.c#L846">846</a>                                                    1);
<a name="L847" href="source/net/ipv4/cipso_ipv4.c#L847">847</a>                         if (cat &lt; 0)
<a name="L848" href="source/net/ipv4/cipso_ipv4.c#L848">848</a>                                 break;
<a name="L849" href="source/net/ipv4/cipso_ipv4.c#L849">849</a>                         if (cat &gt;= cipso_cat_size ||
<a name="L850" href="source/net/ipv4/cipso_ipv4.c#L850">850</a>                             cipso_array[cat] &gt;= <a href="ident?i=CIPSO_V4_INV_CAT">CIPSO_V4_INV_CAT</a>)
<a name="L851" href="source/net/ipv4/cipso_ipv4.c#L851">851</a>                                 return -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L852" href="source/net/ipv4/cipso_ipv4.c#L852">852</a>                 }
<a name="L853" href="source/net/ipv4/cipso_ipv4.c#L853">853</a> 
<a name="L854" href="source/net/ipv4/cipso_ipv4.c#L854">854</a>                 if (cat == -1)
<a name="L855" href="source/net/ipv4/cipso_ipv4.c#L855">855</a>                         return 0;
<a name="L856" href="source/net/ipv4/cipso_ipv4.c#L856">856</a>                 break;
<a name="L857" href="source/net/ipv4/cipso_ipv4.c#L857">857</a>         }
<a name="L858" href="source/net/ipv4/cipso_ipv4.c#L858">858</a> 
<a name="L859" href="source/net/ipv4/cipso_ipv4.c#L859">859</a>         return -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L860" href="source/net/ipv4/cipso_ipv4.c#L860">860</a> }
<a name="L861" href="source/net/ipv4/cipso_ipv4.c#L861">861</a> 
<a name="L862" href="source/net/ipv4/cipso_ipv4.c#L862">862</a> <b><i>/**</i></b>
<a name="L863" href="source/net/ipv4/cipso_ipv4.c#L863">863</a> <b><i> * cipso_v4_map_cat_rbm_hton - Perform a category mapping from host to network</i></b>
<a name="L864" href="source/net/ipv4/cipso_ipv4.c#L864">864</a> <b><i> * @doi_def: the DOI definition</i></b>
<a name="L865" href="source/net/ipv4/cipso_ipv4.c#L865">865</a> <b><i> * @secattr: the security attributes</i></b>
<a name="L866" href="source/net/ipv4/cipso_ipv4.c#L866">866</a> <b><i> * @net_cat: the zero'd out category bitmap in network/CIPSO format</i></b>
<a name="L867" href="source/net/ipv4/cipso_ipv4.c#L867">867</a> <b><i> * @net_cat_len: the length of the CIPSO bitmap in bytes</i></b>
<a name="L868" href="source/net/ipv4/cipso_ipv4.c#L868">868</a> <b><i> *</i></b>
<a name="L869" href="source/net/ipv4/cipso_ipv4.c#L869">869</a> <b><i> * Description:</i></b>
<a name="L870" href="source/net/ipv4/cipso_ipv4.c#L870">870</a> <b><i> * Perform a label mapping to translate a local MLS category bitmap to the</i></b>
<a name="L871" href="source/net/ipv4/cipso_ipv4.c#L871">871</a> <b><i> * correct CIPSO bitmap using the given DOI definition.  Returns the minimum</i></b>
<a name="L872" href="source/net/ipv4/cipso_ipv4.c#L872">872</a> <b><i> * size in bytes of the network bitmap on success, negative values otherwise.</i></b>
<a name="L873" href="source/net/ipv4/cipso_ipv4.c#L873">873</a> <b><i> *</i></b>
<a name="L874" href="source/net/ipv4/cipso_ipv4.c#L874">874</a> <b><i> */</i></b>
<a name="L875" href="source/net/ipv4/cipso_ipv4.c#L875">875</a> static int <a href="ident?i=cipso_v4_map_cat_rbm_hton">cipso_v4_map_cat_rbm_hton</a>(const struct <a href="ident?i=cipso_v4_doi">cipso_v4_doi</a> *doi_def,
<a name="L876" href="source/net/ipv4/cipso_ipv4.c#L876">876</a>                                      const struct <a href="ident?i=netlbl_lsm_secattr">netlbl_lsm_secattr</a> *secattr,
<a name="L877" href="source/net/ipv4/cipso_ipv4.c#L877">877</a>                                      unsigned char *net_cat,
<a name="L878" href="source/net/ipv4/cipso_ipv4.c#L878">878</a>                                      <a href="ident?i=u32">u32</a> net_cat_len)
<a name="L879" href="source/net/ipv4/cipso_ipv4.c#L879">879</a> {
<a name="L880" href="source/net/ipv4/cipso_ipv4.c#L880">880</a>         int host_spot = -1;
<a name="L881" href="source/net/ipv4/cipso_ipv4.c#L881">881</a>         <a href="ident?i=u32">u32</a> net_spot = <a href="ident?i=CIPSO_V4_INV_CAT">CIPSO_V4_INV_CAT</a>;
<a name="L882" href="source/net/ipv4/cipso_ipv4.c#L882">882</a>         <a href="ident?i=u32">u32</a> net_spot_max = 0;
<a name="L883" href="source/net/ipv4/cipso_ipv4.c#L883">883</a>         <a href="ident?i=u32">u32</a> net_clen_bits = net_cat_len * 8;
<a name="L884" href="source/net/ipv4/cipso_ipv4.c#L884">884</a>         <a href="ident?i=u32">u32</a> host_cat_size = 0;
<a name="L885" href="source/net/ipv4/cipso_ipv4.c#L885">885</a>         <a href="ident?i=u32">u32</a> *host_cat_array = <a href="ident?i=NULL">NULL</a>;
<a name="L886" href="source/net/ipv4/cipso_ipv4.c#L886">886</a> 
<a name="L887" href="source/net/ipv4/cipso_ipv4.c#L887">887</a>         if (doi_def-&gt;<a href="ident?i=type">type</a> == <a href="ident?i=CIPSO_V4_MAP_TRANS">CIPSO_V4_MAP_TRANS</a>) {
<a name="L888" href="source/net/ipv4/cipso_ipv4.c#L888">888</a>                 host_cat_size = doi_def-&gt;<a href="ident?i=map">map</a>.<a href="ident?i=std">std</a>-&gt;cat.local_size;
<a name="L889" href="source/net/ipv4/cipso_ipv4.c#L889">889</a>                 host_cat_array = doi_def-&gt;<a href="ident?i=map">map</a>.<a href="ident?i=std">std</a>-&gt;cat.local;
<a name="L890" href="source/net/ipv4/cipso_ipv4.c#L890">890</a>         }
<a name="L891" href="source/net/ipv4/cipso_ipv4.c#L891">891</a> 
<a name="L892" href="source/net/ipv4/cipso_ipv4.c#L892">892</a>         for (;;) {
<a name="L893" href="source/net/ipv4/cipso_ipv4.c#L893">893</a>                 host_spot = <a href="ident?i=netlbl_catmap_walk">netlbl_catmap_walk</a>(secattr-&gt;<a href="ident?i=attr">attr</a>.mls.cat,
<a name="L894" href="source/net/ipv4/cipso_ipv4.c#L894">894</a>                                                host_spot + 1);
<a name="L895" href="source/net/ipv4/cipso_ipv4.c#L895">895</a>                 if (host_spot &lt; 0)
<a name="L896" href="source/net/ipv4/cipso_ipv4.c#L896">896</a>                         break;
<a name="L897" href="source/net/ipv4/cipso_ipv4.c#L897">897</a> 
<a name="L898" href="source/net/ipv4/cipso_ipv4.c#L898">898</a>                 switch (doi_def-&gt;<a href="ident?i=type">type</a>) {
<a name="L899" href="source/net/ipv4/cipso_ipv4.c#L899">899</a>                 case <a href="ident?i=CIPSO_V4_MAP_PASS">CIPSO_V4_MAP_PASS</a>:
<a name="L900" href="source/net/ipv4/cipso_ipv4.c#L900">900</a>                         net_spot = host_spot;
<a name="L901" href="source/net/ipv4/cipso_ipv4.c#L901">901</a>                         break;
<a name="L902" href="source/net/ipv4/cipso_ipv4.c#L902">902</a>                 case <a href="ident?i=CIPSO_V4_MAP_TRANS">CIPSO_V4_MAP_TRANS</a>:
<a name="L903" href="source/net/ipv4/cipso_ipv4.c#L903">903</a>                         if (host_spot &gt;= host_cat_size)
<a name="L904" href="source/net/ipv4/cipso_ipv4.c#L904">904</a>                                 return -<a href="ident?i=EPERM">EPERM</a>;
<a name="L905" href="source/net/ipv4/cipso_ipv4.c#L905">905</a>                         net_spot = host_cat_array[host_spot];
<a name="L906" href="source/net/ipv4/cipso_ipv4.c#L906">906</a>                         if (net_spot &gt;= <a href="ident?i=CIPSO_V4_INV_CAT">CIPSO_V4_INV_CAT</a>)
<a name="L907" href="source/net/ipv4/cipso_ipv4.c#L907">907</a>                                 return -<a href="ident?i=EPERM">EPERM</a>;
<a name="L908" href="source/net/ipv4/cipso_ipv4.c#L908">908</a>                         break;
<a name="L909" href="source/net/ipv4/cipso_ipv4.c#L909">909</a>                 }
<a name="L910" href="source/net/ipv4/cipso_ipv4.c#L910">910</a>                 if (net_spot &gt;= net_clen_bits)
<a name="L911" href="source/net/ipv4/cipso_ipv4.c#L911">911</a>                         return -<a href="ident?i=ENOSPC">ENOSPC</a>;
<a name="L912" href="source/net/ipv4/cipso_ipv4.c#L912">912</a>                 <a href="ident?i=cipso_v4_bitmap_setbit">cipso_v4_bitmap_setbit</a>(net_cat, net_spot, 1);
<a name="L913" href="source/net/ipv4/cipso_ipv4.c#L913">913</a> 
<a name="L914" href="source/net/ipv4/cipso_ipv4.c#L914">914</a>                 if (net_spot &gt; net_spot_max)
<a name="L915" href="source/net/ipv4/cipso_ipv4.c#L915">915</a>                         net_spot_max = net_spot;
<a name="L916" href="source/net/ipv4/cipso_ipv4.c#L916">916</a>         }
<a name="L917" href="source/net/ipv4/cipso_ipv4.c#L917">917</a> 
<a name="L918" href="source/net/ipv4/cipso_ipv4.c#L918">918</a>         if (++net_spot_max % 8)
<a name="L919" href="source/net/ipv4/cipso_ipv4.c#L919">919</a>                 return net_spot_max / 8 + 1;
<a name="L920" href="source/net/ipv4/cipso_ipv4.c#L920">920</a>         return net_spot_max / 8;
<a name="L921" href="source/net/ipv4/cipso_ipv4.c#L921">921</a> }
<a name="L922" href="source/net/ipv4/cipso_ipv4.c#L922">922</a> 
<a name="L923" href="source/net/ipv4/cipso_ipv4.c#L923">923</a> <b><i>/**</i></b>
<a name="L924" href="source/net/ipv4/cipso_ipv4.c#L924">924</a> <b><i> * cipso_v4_map_cat_rbm_ntoh - Perform a category mapping from network to host</i></b>
<a name="L925" href="source/net/ipv4/cipso_ipv4.c#L925">925</a> <b><i> * @doi_def: the DOI definition</i></b>
<a name="L926" href="source/net/ipv4/cipso_ipv4.c#L926">926</a> <b><i> * @net_cat: the category bitmap in network/CIPSO format</i></b>
<a name="L927" href="source/net/ipv4/cipso_ipv4.c#L927">927</a> <b><i> * @net_cat_len: the length of the CIPSO bitmap in bytes</i></b>
<a name="L928" href="source/net/ipv4/cipso_ipv4.c#L928">928</a> <b><i> * @secattr: the security attributes</i></b>
<a name="L929" href="source/net/ipv4/cipso_ipv4.c#L929">929</a> <b><i> *</i></b>
<a name="L930" href="source/net/ipv4/cipso_ipv4.c#L930">930</a> <b><i> * Description:</i></b>
<a name="L931" href="source/net/ipv4/cipso_ipv4.c#L931">931</a> <b><i> * Perform a label mapping to translate a CIPSO bitmap to the correct local</i></b>
<a name="L932" href="source/net/ipv4/cipso_ipv4.c#L932">932</a> <b><i> * MLS category bitmap using the given DOI definition.  Returns zero on</i></b>
<a name="L933" href="source/net/ipv4/cipso_ipv4.c#L933">933</a> <b><i> * success, negative values on failure.</i></b>
<a name="L934" href="source/net/ipv4/cipso_ipv4.c#L934">934</a> <b><i> *</i></b>
<a name="L935" href="source/net/ipv4/cipso_ipv4.c#L935">935</a> <b><i> */</i></b>
<a name="L936" href="source/net/ipv4/cipso_ipv4.c#L936">936</a> static int <a href="ident?i=cipso_v4_map_cat_rbm_ntoh">cipso_v4_map_cat_rbm_ntoh</a>(const struct <a href="ident?i=cipso_v4_doi">cipso_v4_doi</a> *doi_def,
<a name="L937" href="source/net/ipv4/cipso_ipv4.c#L937">937</a>                                      const unsigned char *net_cat,
<a name="L938" href="source/net/ipv4/cipso_ipv4.c#L938">938</a>                                      <a href="ident?i=u32">u32</a> net_cat_len,
<a name="L939" href="source/net/ipv4/cipso_ipv4.c#L939">939</a>                                      struct <a href="ident?i=netlbl_lsm_secattr">netlbl_lsm_secattr</a> *secattr)
<a name="L940" href="source/net/ipv4/cipso_ipv4.c#L940">940</a> {
<a name="L941" href="source/net/ipv4/cipso_ipv4.c#L941">941</a>         int ret_val;
<a name="L942" href="source/net/ipv4/cipso_ipv4.c#L942">942</a>         int net_spot = -1;
<a name="L943" href="source/net/ipv4/cipso_ipv4.c#L943">943</a>         <a href="ident?i=u32">u32</a> host_spot = <a href="ident?i=CIPSO_V4_INV_CAT">CIPSO_V4_INV_CAT</a>;
<a name="L944" href="source/net/ipv4/cipso_ipv4.c#L944">944</a>         <a href="ident?i=u32">u32</a> net_clen_bits = net_cat_len * 8;
<a name="L945" href="source/net/ipv4/cipso_ipv4.c#L945">945</a>         <a href="ident?i=u32">u32</a> net_cat_size = 0;
<a name="L946" href="source/net/ipv4/cipso_ipv4.c#L946">946</a>         <a href="ident?i=u32">u32</a> *net_cat_array = <a href="ident?i=NULL">NULL</a>;
<a name="L947" href="source/net/ipv4/cipso_ipv4.c#L947">947</a> 
<a name="L948" href="source/net/ipv4/cipso_ipv4.c#L948">948</a>         if (doi_def-&gt;<a href="ident?i=type">type</a> == <a href="ident?i=CIPSO_V4_MAP_TRANS">CIPSO_V4_MAP_TRANS</a>) {
<a name="L949" href="source/net/ipv4/cipso_ipv4.c#L949">949</a>                 net_cat_size = doi_def-&gt;<a href="ident?i=map">map</a>.<a href="ident?i=std">std</a>-&gt;cat.cipso_size;
<a name="L950" href="source/net/ipv4/cipso_ipv4.c#L950">950</a>                 net_cat_array = doi_def-&gt;<a href="ident?i=map">map</a>.<a href="ident?i=std">std</a>-&gt;cat.cipso;
<a name="L951" href="source/net/ipv4/cipso_ipv4.c#L951">951</a>         }
<a name="L952" href="source/net/ipv4/cipso_ipv4.c#L952">952</a> 
<a name="L953" href="source/net/ipv4/cipso_ipv4.c#L953">953</a>         for (;;) {
<a name="L954" href="source/net/ipv4/cipso_ipv4.c#L954">954</a>                 net_spot = <a href="ident?i=cipso_v4_bitmap_walk">cipso_v4_bitmap_walk</a>(net_cat,
<a name="L955" href="source/net/ipv4/cipso_ipv4.c#L955">955</a>                                                 net_clen_bits,
<a name="L956" href="source/net/ipv4/cipso_ipv4.c#L956">956</a>                                                 net_spot + 1,
<a name="L957" href="source/net/ipv4/cipso_ipv4.c#L957">957</a>                                                 1);
<a name="L958" href="source/net/ipv4/cipso_ipv4.c#L958">958</a>                 if (net_spot &lt; 0) {
<a name="L959" href="source/net/ipv4/cipso_ipv4.c#L959">959</a>                         if (net_spot == -2)
<a name="L960" href="source/net/ipv4/cipso_ipv4.c#L960">960</a>                                 return -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L961" href="source/net/ipv4/cipso_ipv4.c#L961">961</a>                         return 0;
<a name="L962" href="source/net/ipv4/cipso_ipv4.c#L962">962</a>                 }
<a name="L963" href="source/net/ipv4/cipso_ipv4.c#L963">963</a> 
<a name="L964" href="source/net/ipv4/cipso_ipv4.c#L964">964</a>                 switch (doi_def-&gt;<a href="ident?i=type">type</a>) {
<a name="L965" href="source/net/ipv4/cipso_ipv4.c#L965">965</a>                 case <a href="ident?i=CIPSO_V4_MAP_PASS">CIPSO_V4_MAP_PASS</a>:
<a name="L966" href="source/net/ipv4/cipso_ipv4.c#L966">966</a>                         host_spot = net_spot;
<a name="L967" href="source/net/ipv4/cipso_ipv4.c#L967">967</a>                         break;
<a name="L968" href="source/net/ipv4/cipso_ipv4.c#L968">968</a>                 case <a href="ident?i=CIPSO_V4_MAP_TRANS">CIPSO_V4_MAP_TRANS</a>:
<a name="L969" href="source/net/ipv4/cipso_ipv4.c#L969">969</a>                         if (net_spot &gt;= net_cat_size)
<a name="L970" href="source/net/ipv4/cipso_ipv4.c#L970">970</a>                                 return -<a href="ident?i=EPERM">EPERM</a>;
<a name="L971" href="source/net/ipv4/cipso_ipv4.c#L971">971</a>                         host_spot = net_cat_array[net_spot];
<a name="L972" href="source/net/ipv4/cipso_ipv4.c#L972">972</a>                         if (host_spot &gt;= <a href="ident?i=CIPSO_V4_INV_CAT">CIPSO_V4_INV_CAT</a>)
<a name="L973" href="source/net/ipv4/cipso_ipv4.c#L973">973</a>                                 return -<a href="ident?i=EPERM">EPERM</a>;
<a name="L974" href="source/net/ipv4/cipso_ipv4.c#L974">974</a>                         break;
<a name="L975" href="source/net/ipv4/cipso_ipv4.c#L975">975</a>                 }
<a name="L976" href="source/net/ipv4/cipso_ipv4.c#L976">976</a>                 ret_val = <a href="ident?i=netlbl_catmap_setbit">netlbl_catmap_setbit</a>(&amp;secattr-&gt;<a href="ident?i=attr">attr</a>.mls.cat,
<a name="L977" href="source/net/ipv4/cipso_ipv4.c#L977">977</a>                                                        host_spot,
<a name="L978" href="source/net/ipv4/cipso_ipv4.c#L978">978</a>                                                        <a href="ident?i=GFP_ATOMIC">GFP_ATOMIC</a>);
<a name="L979" href="source/net/ipv4/cipso_ipv4.c#L979">979</a>                 if (ret_val != 0)
<a name="L980" href="source/net/ipv4/cipso_ipv4.c#L980">980</a>                         return ret_val;
<a name="L981" href="source/net/ipv4/cipso_ipv4.c#L981">981</a>         }
<a name="L982" href="source/net/ipv4/cipso_ipv4.c#L982">982</a> 
<a name="L983" href="source/net/ipv4/cipso_ipv4.c#L983">983</a>         return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L984" href="source/net/ipv4/cipso_ipv4.c#L984">984</a> }
<a name="L985" href="source/net/ipv4/cipso_ipv4.c#L985">985</a> 
<a name="L986" href="source/net/ipv4/cipso_ipv4.c#L986">986</a> <b><i>/**</i></b>
<a name="L987" href="source/net/ipv4/cipso_ipv4.c#L987">987</a> <b><i> * cipso_v4_map_cat_enum_valid - Checks to see if the categories are valid</i></b>
<a name="L988" href="source/net/ipv4/cipso_ipv4.c#L988">988</a> <b><i> * @doi_def: the DOI definition</i></b>
<a name="L989" href="source/net/ipv4/cipso_ipv4.c#L989">989</a> <b><i> * @enumcat: category list</i></b>
<a name="L990" href="source/net/ipv4/cipso_ipv4.c#L990">990</a> <b><i> * @enumcat_len: length of the category list in bytes</i></b>
<a name="L991" href="source/net/ipv4/cipso_ipv4.c#L991">991</a> <b><i> *</i></b>
<a name="L992" href="source/net/ipv4/cipso_ipv4.c#L992">992</a> <b><i> * Description:</i></b>
<a name="L993" href="source/net/ipv4/cipso_ipv4.c#L993">993</a> <b><i> * Checks the given categories against the given DOI definition and returns a</i></b>
<a name="L994" href="source/net/ipv4/cipso_ipv4.c#L994">994</a> <b><i> * negative value if any of the categories do not have a valid mapping and a</i></b>
<a name="L995" href="source/net/ipv4/cipso_ipv4.c#L995">995</a> <b><i> * zero value if all of the categories are valid.</i></b>
<a name="L996" href="source/net/ipv4/cipso_ipv4.c#L996">996</a> <b><i> *</i></b>
<a name="L997" href="source/net/ipv4/cipso_ipv4.c#L997">997</a> <b><i> */</i></b>
<a name="L998" href="source/net/ipv4/cipso_ipv4.c#L998">998</a> static int <a href="ident?i=cipso_v4_map_cat_enum_valid">cipso_v4_map_cat_enum_valid</a>(const struct <a href="ident?i=cipso_v4_doi">cipso_v4_doi</a> *doi_def,
<a name="L999" href="source/net/ipv4/cipso_ipv4.c#L999">999</a>                                        const unsigned char *enumcat,
<a name="L1000" href="source/net/ipv4/cipso_ipv4.c#L1000">1000</a>                                        <a href="ident?i=u32">u32</a> enumcat_len)
<a name="L1001" href="source/net/ipv4/cipso_ipv4.c#L1001">1001</a> {
<a name="L1002" href="source/net/ipv4/cipso_ipv4.c#L1002">1002</a>         <a href="ident?i=u16">u16</a> cat;
<a name="L1003" href="source/net/ipv4/cipso_ipv4.c#L1003">1003</a>         int cat_prev = -1;
<a name="L1004" href="source/net/ipv4/cipso_ipv4.c#L1004">1004</a>         <a href="ident?i=u32">u32</a> iter;
<a name="L1005" href="source/net/ipv4/cipso_ipv4.c#L1005">1005</a> 
<a name="L1006" href="source/net/ipv4/cipso_ipv4.c#L1006">1006</a>         if (doi_def-&gt;<a href="ident?i=type">type</a> != <a href="ident?i=CIPSO_V4_MAP_PASS">CIPSO_V4_MAP_PASS</a> || enumcat_len &amp; 0x01)
<a name="L1007" href="source/net/ipv4/cipso_ipv4.c#L1007">1007</a>                 return -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L1008" href="source/net/ipv4/cipso_ipv4.c#L1008">1008</a> 
<a name="L1009" href="source/net/ipv4/cipso_ipv4.c#L1009">1009</a>         for (iter = 0; iter &lt; enumcat_len; iter += 2) {
<a name="L1010" href="source/net/ipv4/cipso_ipv4.c#L1010">1010</a>                 cat = <a href="ident?i=get_unaligned_be16">get_unaligned_be16</a>(&amp;enumcat[iter]);
<a name="L1011" href="source/net/ipv4/cipso_ipv4.c#L1011">1011</a>                 if (cat &lt;= cat_prev)
<a name="L1012" href="source/net/ipv4/cipso_ipv4.c#L1012">1012</a>                         return -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L1013" href="source/net/ipv4/cipso_ipv4.c#L1013">1013</a>                 cat_prev = cat;
<a name="L1014" href="source/net/ipv4/cipso_ipv4.c#L1014">1014</a>         }
<a name="L1015" href="source/net/ipv4/cipso_ipv4.c#L1015">1015</a> 
<a name="L1016" href="source/net/ipv4/cipso_ipv4.c#L1016">1016</a>         return 0;
<a name="L1017" href="source/net/ipv4/cipso_ipv4.c#L1017">1017</a> }
<a name="L1018" href="source/net/ipv4/cipso_ipv4.c#L1018">1018</a> 
<a name="L1019" href="source/net/ipv4/cipso_ipv4.c#L1019">1019</a> <b><i>/**</i></b>
<a name="L1020" href="source/net/ipv4/cipso_ipv4.c#L1020">1020</a> <b><i> * cipso_v4_map_cat_enum_hton - Perform a category mapping from host to network</i></b>
<a name="L1021" href="source/net/ipv4/cipso_ipv4.c#L1021">1021</a> <b><i> * @doi_def: the DOI definition</i></b>
<a name="L1022" href="source/net/ipv4/cipso_ipv4.c#L1022">1022</a> <b><i> * @secattr: the security attributes</i></b>
<a name="L1023" href="source/net/ipv4/cipso_ipv4.c#L1023">1023</a> <b><i> * @net_cat: the zero'd out category list in network/CIPSO format</i></b>
<a name="L1024" href="source/net/ipv4/cipso_ipv4.c#L1024">1024</a> <b><i> * @net_cat_len: the length of the CIPSO category list in bytes</i></b>
<a name="L1025" href="source/net/ipv4/cipso_ipv4.c#L1025">1025</a> <b><i> *</i></b>
<a name="L1026" href="source/net/ipv4/cipso_ipv4.c#L1026">1026</a> <b><i> * Description:</i></b>
<a name="L1027" href="source/net/ipv4/cipso_ipv4.c#L1027">1027</a> <b><i> * Perform a label mapping to translate a local MLS category bitmap to the</i></b>
<a name="L1028" href="source/net/ipv4/cipso_ipv4.c#L1028">1028</a> <b><i> * correct CIPSO category list using the given DOI definition.   Returns the</i></b>
<a name="L1029" href="source/net/ipv4/cipso_ipv4.c#L1029">1029</a> <b><i> * size in bytes of the network category bitmap on success, negative values</i></b>
<a name="L1030" href="source/net/ipv4/cipso_ipv4.c#L1030">1030</a> <b><i> * otherwise.</i></b>
<a name="L1031" href="source/net/ipv4/cipso_ipv4.c#L1031">1031</a> <b><i> *</i></b>
<a name="L1032" href="source/net/ipv4/cipso_ipv4.c#L1032">1032</a> <b><i> */</i></b>
<a name="L1033" href="source/net/ipv4/cipso_ipv4.c#L1033">1033</a> static int <a href="ident?i=cipso_v4_map_cat_enum_hton">cipso_v4_map_cat_enum_hton</a>(const struct <a href="ident?i=cipso_v4_doi">cipso_v4_doi</a> *doi_def,
<a name="L1034" href="source/net/ipv4/cipso_ipv4.c#L1034">1034</a>                                       const struct <a href="ident?i=netlbl_lsm_secattr">netlbl_lsm_secattr</a> *secattr,
<a name="L1035" href="source/net/ipv4/cipso_ipv4.c#L1035">1035</a>                                       unsigned char *net_cat,
<a name="L1036" href="source/net/ipv4/cipso_ipv4.c#L1036">1036</a>                                       <a href="ident?i=u32">u32</a> net_cat_len)
<a name="L1037" href="source/net/ipv4/cipso_ipv4.c#L1037">1037</a> {
<a name="L1038" href="source/net/ipv4/cipso_ipv4.c#L1038">1038</a>         int cat = -1;
<a name="L1039" href="source/net/ipv4/cipso_ipv4.c#L1039">1039</a>         <a href="ident?i=u32">u32</a> cat_iter = 0;
<a name="L1040" href="source/net/ipv4/cipso_ipv4.c#L1040">1040</a> 
<a name="L1041" href="source/net/ipv4/cipso_ipv4.c#L1041">1041</a>         for (;;) {
<a name="L1042" href="source/net/ipv4/cipso_ipv4.c#L1042">1042</a>                 cat = <a href="ident?i=netlbl_catmap_walk">netlbl_catmap_walk</a>(secattr-&gt;<a href="ident?i=attr">attr</a>.mls.cat, cat + 1);
<a name="L1043" href="source/net/ipv4/cipso_ipv4.c#L1043">1043</a>                 if (cat &lt; 0)
<a name="L1044" href="source/net/ipv4/cipso_ipv4.c#L1044">1044</a>                         break;
<a name="L1045" href="source/net/ipv4/cipso_ipv4.c#L1045">1045</a>                 if ((cat_iter + 2) &gt; net_cat_len)
<a name="L1046" href="source/net/ipv4/cipso_ipv4.c#L1046">1046</a>                         return -<a href="ident?i=ENOSPC">ENOSPC</a>;
<a name="L1047" href="source/net/ipv4/cipso_ipv4.c#L1047">1047</a> 
<a name="L1048" href="source/net/ipv4/cipso_ipv4.c#L1048">1048</a>                 *((<a href="ident?i=__be16">__be16</a> *)&amp;net_cat[cat_iter]) = <a href="ident?i=htons">htons</a>(cat);
<a name="L1049" href="source/net/ipv4/cipso_ipv4.c#L1049">1049</a>                 cat_iter += 2;
<a name="L1050" href="source/net/ipv4/cipso_ipv4.c#L1050">1050</a>         }
<a name="L1051" href="source/net/ipv4/cipso_ipv4.c#L1051">1051</a> 
<a name="L1052" href="source/net/ipv4/cipso_ipv4.c#L1052">1052</a>         return cat_iter;
<a name="L1053" href="source/net/ipv4/cipso_ipv4.c#L1053">1053</a> }
<a name="L1054" href="source/net/ipv4/cipso_ipv4.c#L1054">1054</a> 
<a name="L1055" href="source/net/ipv4/cipso_ipv4.c#L1055">1055</a> <b><i>/**</i></b>
<a name="L1056" href="source/net/ipv4/cipso_ipv4.c#L1056">1056</a> <b><i> * cipso_v4_map_cat_enum_ntoh - Perform a category mapping from network to host</i></b>
<a name="L1057" href="source/net/ipv4/cipso_ipv4.c#L1057">1057</a> <b><i> * @doi_def: the DOI definition</i></b>
<a name="L1058" href="source/net/ipv4/cipso_ipv4.c#L1058">1058</a> <b><i> * @net_cat: the category list in network/CIPSO format</i></b>
<a name="L1059" href="source/net/ipv4/cipso_ipv4.c#L1059">1059</a> <b><i> * @net_cat_len: the length of the CIPSO bitmap in bytes</i></b>
<a name="L1060" href="source/net/ipv4/cipso_ipv4.c#L1060">1060</a> <b><i> * @secattr: the security attributes</i></b>
<a name="L1061" href="source/net/ipv4/cipso_ipv4.c#L1061">1061</a> <b><i> *</i></b>
<a name="L1062" href="source/net/ipv4/cipso_ipv4.c#L1062">1062</a> <b><i> * Description:</i></b>
<a name="L1063" href="source/net/ipv4/cipso_ipv4.c#L1063">1063</a> <b><i> * Perform a label mapping to translate a CIPSO category list to the correct</i></b>
<a name="L1064" href="source/net/ipv4/cipso_ipv4.c#L1064">1064</a> <b><i> * local MLS category bitmap using the given DOI definition.  Returns zero on</i></b>
<a name="L1065" href="source/net/ipv4/cipso_ipv4.c#L1065">1065</a> <b><i> * success, negative values on failure.</i></b>
<a name="L1066" href="source/net/ipv4/cipso_ipv4.c#L1066">1066</a> <b><i> *</i></b>
<a name="L1067" href="source/net/ipv4/cipso_ipv4.c#L1067">1067</a> <b><i> */</i></b>
<a name="L1068" href="source/net/ipv4/cipso_ipv4.c#L1068">1068</a> static int <a href="ident?i=cipso_v4_map_cat_enum_ntoh">cipso_v4_map_cat_enum_ntoh</a>(const struct <a href="ident?i=cipso_v4_doi">cipso_v4_doi</a> *doi_def,
<a name="L1069" href="source/net/ipv4/cipso_ipv4.c#L1069">1069</a>                                       const unsigned char *net_cat,
<a name="L1070" href="source/net/ipv4/cipso_ipv4.c#L1070">1070</a>                                       <a href="ident?i=u32">u32</a> net_cat_len,
<a name="L1071" href="source/net/ipv4/cipso_ipv4.c#L1071">1071</a>                                       struct <a href="ident?i=netlbl_lsm_secattr">netlbl_lsm_secattr</a> *secattr)
<a name="L1072" href="source/net/ipv4/cipso_ipv4.c#L1072">1072</a> {
<a name="L1073" href="source/net/ipv4/cipso_ipv4.c#L1073">1073</a>         int ret_val;
<a name="L1074" href="source/net/ipv4/cipso_ipv4.c#L1074">1074</a>         <a href="ident?i=u32">u32</a> iter;
<a name="L1075" href="source/net/ipv4/cipso_ipv4.c#L1075">1075</a> 
<a name="L1076" href="source/net/ipv4/cipso_ipv4.c#L1076">1076</a>         for (iter = 0; iter &lt; net_cat_len; iter += 2) {
<a name="L1077" href="source/net/ipv4/cipso_ipv4.c#L1077">1077</a>                 ret_val = <a href="ident?i=netlbl_catmap_setbit">netlbl_catmap_setbit</a>(&amp;secattr-&gt;<a href="ident?i=attr">attr</a>.mls.cat,
<a name="L1078" href="source/net/ipv4/cipso_ipv4.c#L1078">1078</a>                                              <a href="ident?i=get_unaligned_be16">get_unaligned_be16</a>(&amp;net_cat[iter]),
<a name="L1079" href="source/net/ipv4/cipso_ipv4.c#L1079">1079</a>                                              <a href="ident?i=GFP_ATOMIC">GFP_ATOMIC</a>);
<a name="L1080" href="source/net/ipv4/cipso_ipv4.c#L1080">1080</a>                 if (ret_val != 0)
<a name="L1081" href="source/net/ipv4/cipso_ipv4.c#L1081">1081</a>                         return ret_val;
<a name="L1082" href="source/net/ipv4/cipso_ipv4.c#L1082">1082</a>         }
<a name="L1083" href="source/net/ipv4/cipso_ipv4.c#L1083">1083</a> 
<a name="L1084" href="source/net/ipv4/cipso_ipv4.c#L1084">1084</a>         return 0;
<a name="L1085" href="source/net/ipv4/cipso_ipv4.c#L1085">1085</a> }
<a name="L1086" href="source/net/ipv4/cipso_ipv4.c#L1086">1086</a> 
<a name="L1087" href="source/net/ipv4/cipso_ipv4.c#L1087">1087</a> <b><i>/**</i></b>
<a name="L1088" href="source/net/ipv4/cipso_ipv4.c#L1088">1088</a> <b><i> * cipso_v4_map_cat_rng_valid - Checks to see if the categories are valid</i></b>
<a name="L1089" href="source/net/ipv4/cipso_ipv4.c#L1089">1089</a> <b><i> * @doi_def: the DOI definition</i></b>
<a name="L1090" href="source/net/ipv4/cipso_ipv4.c#L1090">1090</a> <b><i> * @rngcat: category list</i></b>
<a name="L1091" href="source/net/ipv4/cipso_ipv4.c#L1091">1091</a> <b><i> * @rngcat_len: length of the category list in bytes</i></b>
<a name="L1092" href="source/net/ipv4/cipso_ipv4.c#L1092">1092</a> <b><i> *</i></b>
<a name="L1093" href="source/net/ipv4/cipso_ipv4.c#L1093">1093</a> <b><i> * Description:</i></b>
<a name="L1094" href="source/net/ipv4/cipso_ipv4.c#L1094">1094</a> <b><i> * Checks the given categories against the given DOI definition and returns a</i></b>
<a name="L1095" href="source/net/ipv4/cipso_ipv4.c#L1095">1095</a> <b><i> * negative value if any of the categories do not have a valid mapping and a</i></b>
<a name="L1096" href="source/net/ipv4/cipso_ipv4.c#L1096">1096</a> <b><i> * zero value if all of the categories are valid.</i></b>
<a name="L1097" href="source/net/ipv4/cipso_ipv4.c#L1097">1097</a> <b><i> *</i></b>
<a name="L1098" href="source/net/ipv4/cipso_ipv4.c#L1098">1098</a> <b><i> */</i></b>
<a name="L1099" href="source/net/ipv4/cipso_ipv4.c#L1099">1099</a> static int <a href="ident?i=cipso_v4_map_cat_rng_valid">cipso_v4_map_cat_rng_valid</a>(const struct <a href="ident?i=cipso_v4_doi">cipso_v4_doi</a> *doi_def,
<a name="L1100" href="source/net/ipv4/cipso_ipv4.c#L1100">1100</a>                                       const unsigned char *rngcat,
<a name="L1101" href="source/net/ipv4/cipso_ipv4.c#L1101">1101</a>                                       <a href="ident?i=u32">u32</a> rngcat_len)
<a name="L1102" href="source/net/ipv4/cipso_ipv4.c#L1102">1102</a> {
<a name="L1103" href="source/net/ipv4/cipso_ipv4.c#L1103">1103</a>         <a href="ident?i=u16">u16</a> cat_high;
<a name="L1104" href="source/net/ipv4/cipso_ipv4.c#L1104">1104</a>         <a href="ident?i=u16">u16</a> cat_low;
<a name="L1105" href="source/net/ipv4/cipso_ipv4.c#L1105">1105</a>         <a href="ident?i=u32">u32</a> cat_prev = <a href="ident?i=CIPSO_V4_MAX_REM_CATS">CIPSO_V4_MAX_REM_CATS</a> + 1;
<a name="L1106" href="source/net/ipv4/cipso_ipv4.c#L1106">1106</a>         <a href="ident?i=u32">u32</a> iter;
<a name="L1107" href="source/net/ipv4/cipso_ipv4.c#L1107">1107</a> 
<a name="L1108" href="source/net/ipv4/cipso_ipv4.c#L1108">1108</a>         if (doi_def-&gt;<a href="ident?i=type">type</a> != <a href="ident?i=CIPSO_V4_MAP_PASS">CIPSO_V4_MAP_PASS</a> || rngcat_len &amp; 0x01)
<a name="L1109" href="source/net/ipv4/cipso_ipv4.c#L1109">1109</a>                 return -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L1110" href="source/net/ipv4/cipso_ipv4.c#L1110">1110</a> 
<a name="L1111" href="source/net/ipv4/cipso_ipv4.c#L1111">1111</a>         for (iter = 0; iter &lt; rngcat_len; iter += 4) {
<a name="L1112" href="source/net/ipv4/cipso_ipv4.c#L1112">1112</a>                 cat_high = <a href="ident?i=get_unaligned_be16">get_unaligned_be16</a>(&amp;rngcat[iter]);
<a name="L1113" href="source/net/ipv4/cipso_ipv4.c#L1113">1113</a>                 if ((iter + 4) &lt;= rngcat_len)
<a name="L1114" href="source/net/ipv4/cipso_ipv4.c#L1114">1114</a>                         cat_low = <a href="ident?i=get_unaligned_be16">get_unaligned_be16</a>(&amp;rngcat[iter + 2]);
<a name="L1115" href="source/net/ipv4/cipso_ipv4.c#L1115">1115</a>                 else
<a name="L1116" href="source/net/ipv4/cipso_ipv4.c#L1116">1116</a>                         cat_low = 0;
<a name="L1117" href="source/net/ipv4/cipso_ipv4.c#L1117">1117</a> 
<a name="L1118" href="source/net/ipv4/cipso_ipv4.c#L1118">1118</a>                 if (cat_high &gt; cat_prev)
<a name="L1119" href="source/net/ipv4/cipso_ipv4.c#L1119">1119</a>                         return -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L1120" href="source/net/ipv4/cipso_ipv4.c#L1120">1120</a> 
<a name="L1121" href="source/net/ipv4/cipso_ipv4.c#L1121">1121</a>                 cat_prev = cat_low;
<a name="L1122" href="source/net/ipv4/cipso_ipv4.c#L1122">1122</a>         }
<a name="L1123" href="source/net/ipv4/cipso_ipv4.c#L1123">1123</a> 
<a name="L1124" href="source/net/ipv4/cipso_ipv4.c#L1124">1124</a>         return 0;
<a name="L1125" href="source/net/ipv4/cipso_ipv4.c#L1125">1125</a> }
<a name="L1126" href="source/net/ipv4/cipso_ipv4.c#L1126">1126</a> 
<a name="L1127" href="source/net/ipv4/cipso_ipv4.c#L1127">1127</a> <b><i>/**</i></b>
<a name="L1128" href="source/net/ipv4/cipso_ipv4.c#L1128">1128</a> <b><i> * cipso_v4_map_cat_rng_hton - Perform a category mapping from host to network</i></b>
<a name="L1129" href="source/net/ipv4/cipso_ipv4.c#L1129">1129</a> <b><i> * @doi_def: the DOI definition</i></b>
<a name="L1130" href="source/net/ipv4/cipso_ipv4.c#L1130">1130</a> <b><i> * @secattr: the security attributes</i></b>
<a name="L1131" href="source/net/ipv4/cipso_ipv4.c#L1131">1131</a> <b><i> * @net_cat: the zero'd out category list in network/CIPSO format</i></b>
<a name="L1132" href="source/net/ipv4/cipso_ipv4.c#L1132">1132</a> <b><i> * @net_cat_len: the length of the CIPSO category list in bytes</i></b>
<a name="L1133" href="source/net/ipv4/cipso_ipv4.c#L1133">1133</a> <b><i> *</i></b>
<a name="L1134" href="source/net/ipv4/cipso_ipv4.c#L1134">1134</a> <b><i> * Description:</i></b>
<a name="L1135" href="source/net/ipv4/cipso_ipv4.c#L1135">1135</a> <b><i> * Perform a label mapping to translate a local MLS category bitmap to the</i></b>
<a name="L1136" href="source/net/ipv4/cipso_ipv4.c#L1136">1136</a> <b><i> * correct CIPSO category list using the given DOI definition.   Returns the</i></b>
<a name="L1137" href="source/net/ipv4/cipso_ipv4.c#L1137">1137</a> <b><i> * size in bytes of the network category bitmap on success, negative values</i></b>
<a name="L1138" href="source/net/ipv4/cipso_ipv4.c#L1138">1138</a> <b><i> * otherwise.</i></b>
<a name="L1139" href="source/net/ipv4/cipso_ipv4.c#L1139">1139</a> <b><i> *</i></b>
<a name="L1140" href="source/net/ipv4/cipso_ipv4.c#L1140">1140</a> <b><i> */</i></b>
<a name="L1141" href="source/net/ipv4/cipso_ipv4.c#L1141">1141</a> static int <a href="ident?i=cipso_v4_map_cat_rng_hton">cipso_v4_map_cat_rng_hton</a>(const struct <a href="ident?i=cipso_v4_doi">cipso_v4_doi</a> *doi_def,
<a name="L1142" href="source/net/ipv4/cipso_ipv4.c#L1142">1142</a>                                      const struct <a href="ident?i=netlbl_lsm_secattr">netlbl_lsm_secattr</a> *secattr,
<a name="L1143" href="source/net/ipv4/cipso_ipv4.c#L1143">1143</a>                                      unsigned char *net_cat,
<a name="L1144" href="source/net/ipv4/cipso_ipv4.c#L1144">1144</a>                                      <a href="ident?i=u32">u32</a> net_cat_len)
<a name="L1145" href="source/net/ipv4/cipso_ipv4.c#L1145">1145</a> {
<a name="L1146" href="source/net/ipv4/cipso_ipv4.c#L1146">1146</a>         int iter = -1;
<a name="L1147" href="source/net/ipv4/cipso_ipv4.c#L1147">1147</a>         <a href="ident?i=u16">u16</a> <a href="ident?i=array">array</a>[<a href="ident?i=CIPSO_V4_TAG_RNG_CAT_MAX">CIPSO_V4_TAG_RNG_CAT_MAX</a> * 2];
<a name="L1148" href="source/net/ipv4/cipso_ipv4.c#L1148">1148</a>         <a href="ident?i=u32">u32</a> array_cnt = 0;
<a name="L1149" href="source/net/ipv4/cipso_ipv4.c#L1149">1149</a>         <a href="ident?i=u32">u32</a> cat_size = 0;
<a name="L1150" href="source/net/ipv4/cipso_ipv4.c#L1150">1150</a> 
<a name="L1151" href="source/net/ipv4/cipso_ipv4.c#L1151">1151</a>         <b><i>/* make sure we don't overflow the 'array[]' variable */</i></b>
<a name="L1152" href="source/net/ipv4/cipso_ipv4.c#L1152">1152</a>         if (net_cat_len &gt;
<a name="L1153" href="source/net/ipv4/cipso_ipv4.c#L1153">1153</a>             (<a href="ident?i=CIPSO_V4_OPT_LEN_MAX">CIPSO_V4_OPT_LEN_MAX</a> - <a href="ident?i=CIPSO_V4_HDR_LEN">CIPSO_V4_HDR_LEN</a> - <a href="ident?i=CIPSO_V4_TAG_RNG_BLEN">CIPSO_V4_TAG_RNG_BLEN</a>))
<a name="L1154" href="source/net/ipv4/cipso_ipv4.c#L1154">1154</a>                 return -<a href="ident?i=ENOSPC">ENOSPC</a>;
<a name="L1155" href="source/net/ipv4/cipso_ipv4.c#L1155">1155</a> 
<a name="L1156" href="source/net/ipv4/cipso_ipv4.c#L1156">1156</a>         for (;;) {
<a name="L1157" href="source/net/ipv4/cipso_ipv4.c#L1157">1157</a>                 iter = <a href="ident?i=netlbl_catmap_walk">netlbl_catmap_walk</a>(secattr-&gt;<a href="ident?i=attr">attr</a>.mls.cat, iter + 1);
<a name="L1158" href="source/net/ipv4/cipso_ipv4.c#L1158">1158</a>                 if (iter &lt; 0)
<a name="L1159" href="source/net/ipv4/cipso_ipv4.c#L1159">1159</a>                         break;
<a name="L1160" href="source/net/ipv4/cipso_ipv4.c#L1160">1160</a>                 cat_size += (iter == 0 ? 0 : sizeof(<a href="ident?i=u16">u16</a>));
<a name="L1161" href="source/net/ipv4/cipso_ipv4.c#L1161">1161</a>                 if (cat_size &gt; net_cat_len)
<a name="L1162" href="source/net/ipv4/cipso_ipv4.c#L1162">1162</a>                         return -<a href="ident?i=ENOSPC">ENOSPC</a>;
<a name="L1163" href="source/net/ipv4/cipso_ipv4.c#L1163">1163</a>                 <a href="ident?i=array">array</a>[array_cnt++] = iter;
<a name="L1164" href="source/net/ipv4/cipso_ipv4.c#L1164">1164</a> 
<a name="L1165" href="source/net/ipv4/cipso_ipv4.c#L1165">1165</a>                 iter = <a href="ident?i=netlbl_catmap_walkrng">netlbl_catmap_walkrng</a>(secattr-&gt;<a href="ident?i=attr">attr</a>.mls.cat, iter);
<a name="L1166" href="source/net/ipv4/cipso_ipv4.c#L1166">1166</a>                 if (iter &lt; 0)
<a name="L1167" href="source/net/ipv4/cipso_ipv4.c#L1167">1167</a>                         return -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L1168" href="source/net/ipv4/cipso_ipv4.c#L1168">1168</a>                 cat_size += sizeof(<a href="ident?i=u16">u16</a>);
<a name="L1169" href="source/net/ipv4/cipso_ipv4.c#L1169">1169</a>                 if (cat_size &gt; net_cat_len)
<a name="L1170" href="source/net/ipv4/cipso_ipv4.c#L1170">1170</a>                         return -<a href="ident?i=ENOSPC">ENOSPC</a>;
<a name="L1171" href="source/net/ipv4/cipso_ipv4.c#L1171">1171</a>                 <a href="ident?i=array">array</a>[array_cnt++] = iter;
<a name="L1172" href="source/net/ipv4/cipso_ipv4.c#L1172">1172</a>         }
<a name="L1173" href="source/net/ipv4/cipso_ipv4.c#L1173">1173</a> 
<a name="L1174" href="source/net/ipv4/cipso_ipv4.c#L1174">1174</a>         for (iter = 0; array_cnt &gt; 0;) {
<a name="L1175" href="source/net/ipv4/cipso_ipv4.c#L1175">1175</a>                 *((<a href="ident?i=__be16">__be16</a> *)&amp;net_cat[iter]) = <a href="ident?i=htons">htons</a>(<a href="ident?i=array">array</a>[--array_cnt]);
<a name="L1176" href="source/net/ipv4/cipso_ipv4.c#L1176">1176</a>                 iter += 2;
<a name="L1177" href="source/net/ipv4/cipso_ipv4.c#L1177">1177</a>                 array_cnt--;
<a name="L1178" href="source/net/ipv4/cipso_ipv4.c#L1178">1178</a>                 if (<a href="ident?i=array">array</a>[array_cnt] != 0) {
<a name="L1179" href="source/net/ipv4/cipso_ipv4.c#L1179">1179</a>                         *((<a href="ident?i=__be16">__be16</a> *)&amp;net_cat[iter]) = <a href="ident?i=htons">htons</a>(<a href="ident?i=array">array</a>[array_cnt]);
<a name="L1180" href="source/net/ipv4/cipso_ipv4.c#L1180">1180</a>                         iter += 2;
<a name="L1181" href="source/net/ipv4/cipso_ipv4.c#L1181">1181</a>                 }
<a name="L1182" href="source/net/ipv4/cipso_ipv4.c#L1182">1182</a>         }
<a name="L1183" href="source/net/ipv4/cipso_ipv4.c#L1183">1183</a> 
<a name="L1184" href="source/net/ipv4/cipso_ipv4.c#L1184">1184</a>         return cat_size;
<a name="L1185" href="source/net/ipv4/cipso_ipv4.c#L1185">1185</a> }
<a name="L1186" href="source/net/ipv4/cipso_ipv4.c#L1186">1186</a> 
<a name="L1187" href="source/net/ipv4/cipso_ipv4.c#L1187">1187</a> <b><i>/**</i></b>
<a name="L1188" href="source/net/ipv4/cipso_ipv4.c#L1188">1188</a> <b><i> * cipso_v4_map_cat_rng_ntoh - Perform a category mapping from network to host</i></b>
<a name="L1189" href="source/net/ipv4/cipso_ipv4.c#L1189">1189</a> <b><i> * @doi_def: the DOI definition</i></b>
<a name="L1190" href="source/net/ipv4/cipso_ipv4.c#L1190">1190</a> <b><i> * @net_cat: the category list in network/CIPSO format</i></b>
<a name="L1191" href="source/net/ipv4/cipso_ipv4.c#L1191">1191</a> <b><i> * @net_cat_len: the length of the CIPSO bitmap in bytes</i></b>
<a name="L1192" href="source/net/ipv4/cipso_ipv4.c#L1192">1192</a> <b><i> * @secattr: the security attributes</i></b>
<a name="L1193" href="source/net/ipv4/cipso_ipv4.c#L1193">1193</a> <b><i> *</i></b>
<a name="L1194" href="source/net/ipv4/cipso_ipv4.c#L1194">1194</a> <b><i> * Description:</i></b>
<a name="L1195" href="source/net/ipv4/cipso_ipv4.c#L1195">1195</a> <b><i> * Perform a label mapping to translate a CIPSO category list to the correct</i></b>
<a name="L1196" href="source/net/ipv4/cipso_ipv4.c#L1196">1196</a> <b><i> * local MLS category bitmap using the given DOI definition.  Returns zero on</i></b>
<a name="L1197" href="source/net/ipv4/cipso_ipv4.c#L1197">1197</a> <b><i> * success, negative values on failure.</i></b>
<a name="L1198" href="source/net/ipv4/cipso_ipv4.c#L1198">1198</a> <b><i> *</i></b>
<a name="L1199" href="source/net/ipv4/cipso_ipv4.c#L1199">1199</a> <b><i> */</i></b>
<a name="L1200" href="source/net/ipv4/cipso_ipv4.c#L1200">1200</a> static int <a href="ident?i=cipso_v4_map_cat_rng_ntoh">cipso_v4_map_cat_rng_ntoh</a>(const struct <a href="ident?i=cipso_v4_doi">cipso_v4_doi</a> *doi_def,
<a name="L1201" href="source/net/ipv4/cipso_ipv4.c#L1201">1201</a>                                      const unsigned char *net_cat,
<a name="L1202" href="source/net/ipv4/cipso_ipv4.c#L1202">1202</a>                                      <a href="ident?i=u32">u32</a> net_cat_len,
<a name="L1203" href="source/net/ipv4/cipso_ipv4.c#L1203">1203</a>                                      struct <a href="ident?i=netlbl_lsm_secattr">netlbl_lsm_secattr</a> *secattr)
<a name="L1204" href="source/net/ipv4/cipso_ipv4.c#L1204">1204</a> {
<a name="L1205" href="source/net/ipv4/cipso_ipv4.c#L1205">1205</a>         int ret_val;
<a name="L1206" href="source/net/ipv4/cipso_ipv4.c#L1206">1206</a>         <a href="ident?i=u32">u32</a> net_iter;
<a name="L1207" href="source/net/ipv4/cipso_ipv4.c#L1207">1207</a>         <a href="ident?i=u16">u16</a> cat_low;
<a name="L1208" href="source/net/ipv4/cipso_ipv4.c#L1208">1208</a>         <a href="ident?i=u16">u16</a> cat_high;
<a name="L1209" href="source/net/ipv4/cipso_ipv4.c#L1209">1209</a> 
<a name="L1210" href="source/net/ipv4/cipso_ipv4.c#L1210">1210</a>         for (net_iter = 0; net_iter &lt; net_cat_len; net_iter += 4) {
<a name="L1211" href="source/net/ipv4/cipso_ipv4.c#L1211">1211</a>                 cat_high = <a href="ident?i=get_unaligned_be16">get_unaligned_be16</a>(&amp;net_cat[net_iter]);
<a name="L1212" href="source/net/ipv4/cipso_ipv4.c#L1212">1212</a>                 if ((net_iter + 4) &lt;= net_cat_len)
<a name="L1213" href="source/net/ipv4/cipso_ipv4.c#L1213">1213</a>                         cat_low = <a href="ident?i=get_unaligned_be16">get_unaligned_be16</a>(&amp;net_cat[net_iter + 2]);
<a name="L1214" href="source/net/ipv4/cipso_ipv4.c#L1214">1214</a>                 else
<a name="L1215" href="source/net/ipv4/cipso_ipv4.c#L1215">1215</a>                         cat_low = 0;
<a name="L1216" href="source/net/ipv4/cipso_ipv4.c#L1216">1216</a> 
<a name="L1217" href="source/net/ipv4/cipso_ipv4.c#L1217">1217</a>                 ret_val = <a href="ident?i=netlbl_catmap_setrng">netlbl_catmap_setrng</a>(&amp;secattr-&gt;<a href="ident?i=attr">attr</a>.mls.cat,
<a name="L1218" href="source/net/ipv4/cipso_ipv4.c#L1218">1218</a>                                                cat_low,
<a name="L1219" href="source/net/ipv4/cipso_ipv4.c#L1219">1219</a>                                                cat_high,
<a name="L1220" href="source/net/ipv4/cipso_ipv4.c#L1220">1220</a>                                                <a href="ident?i=GFP_ATOMIC">GFP_ATOMIC</a>);
<a name="L1221" href="source/net/ipv4/cipso_ipv4.c#L1221">1221</a>                 if (ret_val != 0)
<a name="L1222" href="source/net/ipv4/cipso_ipv4.c#L1222">1222</a>                         return ret_val;
<a name="L1223" href="source/net/ipv4/cipso_ipv4.c#L1223">1223</a>         }
<a name="L1224" href="source/net/ipv4/cipso_ipv4.c#L1224">1224</a> 
<a name="L1225" href="source/net/ipv4/cipso_ipv4.c#L1225">1225</a>         return 0;
<a name="L1226" href="source/net/ipv4/cipso_ipv4.c#L1226">1226</a> }
<a name="L1227" href="source/net/ipv4/cipso_ipv4.c#L1227">1227</a> 
<a name="L1228" href="source/net/ipv4/cipso_ipv4.c#L1228">1228</a> <b><i>/*</i></b>
<a name="L1229" href="source/net/ipv4/cipso_ipv4.c#L1229">1229</a> <b><i> * Protocol Handling Functions</i></b>
<a name="L1230" href="source/net/ipv4/cipso_ipv4.c#L1230">1230</a> <b><i> */</i></b>
<a name="L1231" href="source/net/ipv4/cipso_ipv4.c#L1231">1231</a> 
<a name="L1232" href="source/net/ipv4/cipso_ipv4.c#L1232">1232</a> <b><i>/**</i></b>
<a name="L1233" href="source/net/ipv4/cipso_ipv4.c#L1233">1233</a> <b><i> * cipso_v4_gentag_hdr - Generate a CIPSO option header</i></b>
<a name="L1234" href="source/net/ipv4/cipso_ipv4.c#L1234">1234</a> <b><i> * @doi_def: the DOI definition</i></b>
<a name="L1235" href="source/net/ipv4/cipso_ipv4.c#L1235">1235</a> <b><i> * @len: the total tag length in bytes, not including this header</i></b>
<a name="L1236" href="source/net/ipv4/cipso_ipv4.c#L1236">1236</a> <b><i> * @buf: the CIPSO option buffer</i></b>
<a name="L1237" href="source/net/ipv4/cipso_ipv4.c#L1237">1237</a> <b><i> *</i></b>
<a name="L1238" href="source/net/ipv4/cipso_ipv4.c#L1238">1238</a> <b><i> * Description:</i></b>
<a name="L1239" href="source/net/ipv4/cipso_ipv4.c#L1239">1239</a> <b><i> * Write a CIPSO header into the beginning of @buffer.</i></b>
<a name="L1240" href="source/net/ipv4/cipso_ipv4.c#L1240">1240</a> <b><i> *</i></b>
<a name="L1241" href="source/net/ipv4/cipso_ipv4.c#L1241">1241</a> <b><i> */</i></b>
<a name="L1242" href="source/net/ipv4/cipso_ipv4.c#L1242">1242</a> static void <a href="ident?i=cipso_v4_gentag_hdr">cipso_v4_gentag_hdr</a>(const struct <a href="ident?i=cipso_v4_doi">cipso_v4_doi</a> *doi_def,
<a name="L1243" href="source/net/ipv4/cipso_ipv4.c#L1243">1243</a>                                 unsigned char *<a href="ident?i=buf">buf</a>,
<a name="L1244" href="source/net/ipv4/cipso_ipv4.c#L1244">1244</a>                                 <a href="ident?i=u32">u32</a> <a href="ident?i=len">len</a>)
<a name="L1245" href="source/net/ipv4/cipso_ipv4.c#L1245">1245</a> {
<a name="L1246" href="source/net/ipv4/cipso_ipv4.c#L1246">1246</a>         <a href="ident?i=buf">buf</a>[0] = <a href="ident?i=IPOPT_CIPSO">IPOPT_CIPSO</a>;
<a name="L1247" href="source/net/ipv4/cipso_ipv4.c#L1247">1247</a>         <a href="ident?i=buf">buf</a>[1] = <a href="ident?i=CIPSO_V4_HDR_LEN">CIPSO_V4_HDR_LEN</a> + <a href="ident?i=len">len</a>;
<a name="L1248" href="source/net/ipv4/cipso_ipv4.c#L1248">1248</a>         *(<a href="ident?i=__be32">__be32</a> *)&amp;<a href="ident?i=buf">buf</a>[2] = <a href="ident?i=htonl">htonl</a>(doi_def-&gt;doi);
<a name="L1249" href="source/net/ipv4/cipso_ipv4.c#L1249">1249</a> }
<a name="L1250" href="source/net/ipv4/cipso_ipv4.c#L1250">1250</a> 
<a name="L1251" href="source/net/ipv4/cipso_ipv4.c#L1251">1251</a> <b><i>/**</i></b>
<a name="L1252" href="source/net/ipv4/cipso_ipv4.c#L1252">1252</a> <b><i> * cipso_v4_gentag_rbm - Generate a CIPSO restricted bitmap tag (type #1)</i></b>
<a name="L1253" href="source/net/ipv4/cipso_ipv4.c#L1253">1253</a> <b><i> * @doi_def: the DOI definition</i></b>
<a name="L1254" href="source/net/ipv4/cipso_ipv4.c#L1254">1254</a> <b><i> * @secattr: the security attributes</i></b>
<a name="L1255" href="source/net/ipv4/cipso_ipv4.c#L1255">1255</a> <b><i> * @buffer: the option buffer</i></b>
<a name="L1256" href="source/net/ipv4/cipso_ipv4.c#L1256">1256</a> <b><i> * @buffer_len: length of buffer in bytes</i></b>
<a name="L1257" href="source/net/ipv4/cipso_ipv4.c#L1257">1257</a> <b><i> *</i></b>
<a name="L1258" href="source/net/ipv4/cipso_ipv4.c#L1258">1258</a> <b><i> * Description:</i></b>
<a name="L1259" href="source/net/ipv4/cipso_ipv4.c#L1259">1259</a> <b><i> * Generate a CIPSO option using the restricted bitmap tag, tag type #1.  The</i></b>
<a name="L1260" href="source/net/ipv4/cipso_ipv4.c#L1260">1260</a> <b><i> * actual buffer length may be larger than the indicated size due to</i></b>
<a name="L1261" href="source/net/ipv4/cipso_ipv4.c#L1261">1261</a> <b><i> * translation between host and network category bitmaps.  Returns the size of</i></b>
<a name="L1262" href="source/net/ipv4/cipso_ipv4.c#L1262">1262</a> <b><i> * the tag on success, negative values on failure.</i></b>
<a name="L1263" href="source/net/ipv4/cipso_ipv4.c#L1263">1263</a> <b><i> *</i></b>
<a name="L1264" href="source/net/ipv4/cipso_ipv4.c#L1264">1264</a> <b><i> */</i></b>
<a name="L1265" href="source/net/ipv4/cipso_ipv4.c#L1265">1265</a> static int <a href="ident?i=cipso_v4_gentag_rbm">cipso_v4_gentag_rbm</a>(const struct <a href="ident?i=cipso_v4_doi">cipso_v4_doi</a> *doi_def,
<a name="L1266" href="source/net/ipv4/cipso_ipv4.c#L1266">1266</a>                                const struct <a href="ident?i=netlbl_lsm_secattr">netlbl_lsm_secattr</a> *secattr,
<a name="L1267" href="source/net/ipv4/cipso_ipv4.c#L1267">1267</a>                                unsigned char *<a href="ident?i=buffer">buffer</a>,
<a name="L1268" href="source/net/ipv4/cipso_ipv4.c#L1268">1268</a>                                <a href="ident?i=u32">u32</a> <a href="ident?i=buffer_len">buffer_len</a>)
<a name="L1269" href="source/net/ipv4/cipso_ipv4.c#L1269">1269</a> {
<a name="L1270" href="source/net/ipv4/cipso_ipv4.c#L1270">1270</a>         int ret_val;
<a name="L1271" href="source/net/ipv4/cipso_ipv4.c#L1271">1271</a>         <a href="ident?i=u32">u32</a> tag_len;
<a name="L1272" href="source/net/ipv4/cipso_ipv4.c#L1272">1272</a>         <a href="ident?i=u32">u32</a> <a href="ident?i=level">level</a>;
<a name="L1273" href="source/net/ipv4/cipso_ipv4.c#L1273">1273</a> 
<a name="L1274" href="source/net/ipv4/cipso_ipv4.c#L1274">1274</a>         if ((secattr-&gt;<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=NETLBL_SECATTR_MLS_LVL">NETLBL_SECATTR_MLS_LVL</a>) == 0)
<a name="L1275" href="source/net/ipv4/cipso_ipv4.c#L1275">1275</a>                 return -<a href="ident?i=EPERM">EPERM</a>;
<a name="L1276" href="source/net/ipv4/cipso_ipv4.c#L1276">1276</a> 
<a name="L1277" href="source/net/ipv4/cipso_ipv4.c#L1277">1277</a>         ret_val = <a href="ident?i=cipso_v4_map_lvl_hton">cipso_v4_map_lvl_hton</a>(doi_def,
<a name="L1278" href="source/net/ipv4/cipso_ipv4.c#L1278">1278</a>                                         secattr-&gt;<a href="ident?i=attr">attr</a>.mls.lvl,
<a name="L1279" href="source/net/ipv4/cipso_ipv4.c#L1279">1279</a>                                         &amp;<a href="ident?i=level">level</a>);
<a name="L1280" href="source/net/ipv4/cipso_ipv4.c#L1280">1280</a>         if (ret_val != 0)
<a name="L1281" href="source/net/ipv4/cipso_ipv4.c#L1281">1281</a>                 return ret_val;
<a name="L1282" href="source/net/ipv4/cipso_ipv4.c#L1282">1282</a> 
<a name="L1283" href="source/net/ipv4/cipso_ipv4.c#L1283">1283</a>         if (secattr-&gt;<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=NETLBL_SECATTR_MLS_CAT">NETLBL_SECATTR_MLS_CAT</a>) {
<a name="L1284" href="source/net/ipv4/cipso_ipv4.c#L1284">1284</a>                 ret_val = <a href="ident?i=cipso_v4_map_cat_rbm_hton">cipso_v4_map_cat_rbm_hton</a>(doi_def,
<a name="L1285" href="source/net/ipv4/cipso_ipv4.c#L1285">1285</a>                                                     secattr,
<a name="L1286" href="source/net/ipv4/cipso_ipv4.c#L1286">1286</a>                                                     &amp;<a href="ident?i=buffer">buffer</a>[4],
<a name="L1287" href="source/net/ipv4/cipso_ipv4.c#L1287">1287</a>                                                     <a href="ident?i=buffer_len">buffer_len</a> - 4);
<a name="L1288" href="source/net/ipv4/cipso_ipv4.c#L1288">1288</a>                 if (ret_val &lt; 0)
<a name="L1289" href="source/net/ipv4/cipso_ipv4.c#L1289">1289</a>                         return ret_val;
<a name="L1290" href="source/net/ipv4/cipso_ipv4.c#L1290">1290</a> 
<a name="L1291" href="source/net/ipv4/cipso_ipv4.c#L1291">1291</a>                 <b><i>/* This will send packets using the "optimized" format when</i></b>
<a name="L1292" href="source/net/ipv4/cipso_ipv4.c#L1292">1292</a> <b><i>                 * possible as specified in  section 3.4.2.6 of the</i></b>
<a name="L1293" href="source/net/ipv4/cipso_ipv4.c#L1293">1293</a> <b><i>                 * CIPSO draft. */</i></b>
<a name="L1294" href="source/net/ipv4/cipso_ipv4.c#L1294">1294</a>                 if (<a href="ident?i=cipso_v4_rbm_optfmt">cipso_v4_rbm_optfmt</a> &amp;&amp; ret_val &gt; 0 &amp;&amp; ret_val &lt;= 10)
<a name="L1295" href="source/net/ipv4/cipso_ipv4.c#L1295">1295</a>                         tag_len = 14;
<a name="L1296" href="source/net/ipv4/cipso_ipv4.c#L1296">1296</a>                 else
<a name="L1297" href="source/net/ipv4/cipso_ipv4.c#L1297">1297</a>                         tag_len = 4 + ret_val;
<a name="L1298" href="source/net/ipv4/cipso_ipv4.c#L1298">1298</a>         } else
<a name="L1299" href="source/net/ipv4/cipso_ipv4.c#L1299">1299</a>                 tag_len = 4;
<a name="L1300" href="source/net/ipv4/cipso_ipv4.c#L1300">1300</a> 
<a name="L1301" href="source/net/ipv4/cipso_ipv4.c#L1301">1301</a>         <a href="ident?i=buffer">buffer</a>[0] = <a href="ident?i=CIPSO_V4_TAG_RBITMAP">CIPSO_V4_TAG_RBITMAP</a>;
<a name="L1302" href="source/net/ipv4/cipso_ipv4.c#L1302">1302</a>         <a href="ident?i=buffer">buffer</a>[1] = tag_len;
<a name="L1303" href="source/net/ipv4/cipso_ipv4.c#L1303">1303</a>         <a href="ident?i=buffer">buffer</a>[3] = <a href="ident?i=level">level</a>;
<a name="L1304" href="source/net/ipv4/cipso_ipv4.c#L1304">1304</a> 
<a name="L1305" href="source/net/ipv4/cipso_ipv4.c#L1305">1305</a>         return tag_len;
<a name="L1306" href="source/net/ipv4/cipso_ipv4.c#L1306">1306</a> }
<a name="L1307" href="source/net/ipv4/cipso_ipv4.c#L1307">1307</a> 
<a name="L1308" href="source/net/ipv4/cipso_ipv4.c#L1308">1308</a> <b><i>/**</i></b>
<a name="L1309" href="source/net/ipv4/cipso_ipv4.c#L1309">1309</a> <b><i> * cipso_v4_parsetag_rbm - Parse a CIPSO restricted bitmap tag</i></b>
<a name="L1310" href="source/net/ipv4/cipso_ipv4.c#L1310">1310</a> <b><i> * @doi_def: the DOI definition</i></b>
<a name="L1311" href="source/net/ipv4/cipso_ipv4.c#L1311">1311</a> <b><i> * @tag: the CIPSO tag</i></b>
<a name="L1312" href="source/net/ipv4/cipso_ipv4.c#L1312">1312</a> <b><i> * @secattr: the security attributes</i></b>
<a name="L1313" href="source/net/ipv4/cipso_ipv4.c#L1313">1313</a> <b><i> *</i></b>
<a name="L1314" href="source/net/ipv4/cipso_ipv4.c#L1314">1314</a> <b><i> * Description:</i></b>
<a name="L1315" href="source/net/ipv4/cipso_ipv4.c#L1315">1315</a> <b><i> * Parse a CIPSO restricted bitmap tag (tag type #1) and return the security</i></b>
<a name="L1316" href="source/net/ipv4/cipso_ipv4.c#L1316">1316</a> <b><i> * attributes in @secattr.  Return zero on success, negatives values on</i></b>
<a name="L1317" href="source/net/ipv4/cipso_ipv4.c#L1317">1317</a> <b><i> * failure.</i></b>
<a name="L1318" href="source/net/ipv4/cipso_ipv4.c#L1318">1318</a> <b><i> *</i></b>
<a name="L1319" href="source/net/ipv4/cipso_ipv4.c#L1319">1319</a> <b><i> */</i></b>
<a name="L1320" href="source/net/ipv4/cipso_ipv4.c#L1320">1320</a> static int <a href="ident?i=cipso_v4_parsetag_rbm">cipso_v4_parsetag_rbm</a>(const struct <a href="ident?i=cipso_v4_doi">cipso_v4_doi</a> *doi_def,
<a name="L1321" href="source/net/ipv4/cipso_ipv4.c#L1321">1321</a>                                  const unsigned char *<a href="ident?i=tag">tag</a>,
<a name="L1322" href="source/net/ipv4/cipso_ipv4.c#L1322">1322</a>                                  struct <a href="ident?i=netlbl_lsm_secattr">netlbl_lsm_secattr</a> *secattr)
<a name="L1323" href="source/net/ipv4/cipso_ipv4.c#L1323">1323</a> {
<a name="L1324" href="source/net/ipv4/cipso_ipv4.c#L1324">1324</a>         int ret_val;
<a name="L1325" href="source/net/ipv4/cipso_ipv4.c#L1325">1325</a>         <a href="ident?i=u8">u8</a> tag_len = <a href="ident?i=tag">tag</a>[1];
<a name="L1326" href="source/net/ipv4/cipso_ipv4.c#L1326">1326</a>         <a href="ident?i=u32">u32</a> <a href="ident?i=level">level</a>;
<a name="L1327" href="source/net/ipv4/cipso_ipv4.c#L1327">1327</a> 
<a name="L1328" href="source/net/ipv4/cipso_ipv4.c#L1328">1328</a>         ret_val = <a href="ident?i=cipso_v4_map_lvl_ntoh">cipso_v4_map_lvl_ntoh</a>(doi_def, <a href="ident?i=tag">tag</a>[3], &amp;<a href="ident?i=level">level</a>);
<a name="L1329" href="source/net/ipv4/cipso_ipv4.c#L1329">1329</a>         if (ret_val != 0)
<a name="L1330" href="source/net/ipv4/cipso_ipv4.c#L1330">1330</a>                 return ret_val;
<a name="L1331" href="source/net/ipv4/cipso_ipv4.c#L1331">1331</a>         secattr-&gt;<a href="ident?i=attr">attr</a>.mls.lvl = <a href="ident?i=level">level</a>;
<a name="L1332" href="source/net/ipv4/cipso_ipv4.c#L1332">1332</a>         secattr-&gt;<a href="ident?i=flags">flags</a> |= <a href="ident?i=NETLBL_SECATTR_MLS_LVL">NETLBL_SECATTR_MLS_LVL</a>;
<a name="L1333" href="source/net/ipv4/cipso_ipv4.c#L1333">1333</a> 
<a name="L1334" href="source/net/ipv4/cipso_ipv4.c#L1334">1334</a>         if (tag_len &gt; 4) {
<a name="L1335" href="source/net/ipv4/cipso_ipv4.c#L1335">1335</a>                 ret_val = <a href="ident?i=cipso_v4_map_cat_rbm_ntoh">cipso_v4_map_cat_rbm_ntoh</a>(doi_def,
<a name="L1336" href="source/net/ipv4/cipso_ipv4.c#L1336">1336</a>                                                     &amp;<a href="ident?i=tag">tag</a>[4],
<a name="L1337" href="source/net/ipv4/cipso_ipv4.c#L1337">1337</a>                                                     tag_len - 4,
<a name="L1338" href="source/net/ipv4/cipso_ipv4.c#L1338">1338</a>                                                     secattr);
<a name="L1339" href="source/net/ipv4/cipso_ipv4.c#L1339">1339</a>                 if (ret_val != 0) {
<a name="L1340" href="source/net/ipv4/cipso_ipv4.c#L1340">1340</a>                         <a href="ident?i=netlbl_catmap_free">netlbl_catmap_free</a>(secattr-&gt;<a href="ident?i=attr">attr</a>.mls.cat);
<a name="L1341" href="source/net/ipv4/cipso_ipv4.c#L1341">1341</a>                         return ret_val;
<a name="L1342" href="source/net/ipv4/cipso_ipv4.c#L1342">1342</a>                 }
<a name="L1343" href="source/net/ipv4/cipso_ipv4.c#L1343">1343</a> 
<a name="L1344" href="source/net/ipv4/cipso_ipv4.c#L1344">1344</a>                 secattr-&gt;<a href="ident?i=flags">flags</a> |= <a href="ident?i=NETLBL_SECATTR_MLS_CAT">NETLBL_SECATTR_MLS_CAT</a>;
<a name="L1345" href="source/net/ipv4/cipso_ipv4.c#L1345">1345</a>         }
<a name="L1346" href="source/net/ipv4/cipso_ipv4.c#L1346">1346</a> 
<a name="L1347" href="source/net/ipv4/cipso_ipv4.c#L1347">1347</a>         return 0;
<a name="L1348" href="source/net/ipv4/cipso_ipv4.c#L1348">1348</a> }
<a name="L1349" href="source/net/ipv4/cipso_ipv4.c#L1349">1349</a> 
<a name="L1350" href="source/net/ipv4/cipso_ipv4.c#L1350">1350</a> <b><i>/**</i></b>
<a name="L1351" href="source/net/ipv4/cipso_ipv4.c#L1351">1351</a> <b><i> * cipso_v4_gentag_enum - Generate a CIPSO enumerated tag (type #2)</i></b>
<a name="L1352" href="source/net/ipv4/cipso_ipv4.c#L1352">1352</a> <b><i> * @doi_def: the DOI definition</i></b>
<a name="L1353" href="source/net/ipv4/cipso_ipv4.c#L1353">1353</a> <b><i> * @secattr: the security attributes</i></b>
<a name="L1354" href="source/net/ipv4/cipso_ipv4.c#L1354">1354</a> <b><i> * @buffer: the option buffer</i></b>
<a name="L1355" href="source/net/ipv4/cipso_ipv4.c#L1355">1355</a> <b><i> * @buffer_len: length of buffer in bytes</i></b>
<a name="L1356" href="source/net/ipv4/cipso_ipv4.c#L1356">1356</a> <b><i> *</i></b>
<a name="L1357" href="source/net/ipv4/cipso_ipv4.c#L1357">1357</a> <b><i> * Description:</i></b>
<a name="L1358" href="source/net/ipv4/cipso_ipv4.c#L1358">1358</a> <b><i> * Generate a CIPSO option using the enumerated tag, tag type #2.  Returns the</i></b>
<a name="L1359" href="source/net/ipv4/cipso_ipv4.c#L1359">1359</a> <b><i> * size of the tag on success, negative values on failure.</i></b>
<a name="L1360" href="source/net/ipv4/cipso_ipv4.c#L1360">1360</a> <b><i> *</i></b>
<a name="L1361" href="source/net/ipv4/cipso_ipv4.c#L1361">1361</a> <b><i> */</i></b>
<a name="L1362" href="source/net/ipv4/cipso_ipv4.c#L1362">1362</a> static int <a href="ident?i=cipso_v4_gentag_enum">cipso_v4_gentag_enum</a>(const struct <a href="ident?i=cipso_v4_doi">cipso_v4_doi</a> *doi_def,
<a name="L1363" href="source/net/ipv4/cipso_ipv4.c#L1363">1363</a>                                 const struct <a href="ident?i=netlbl_lsm_secattr">netlbl_lsm_secattr</a> *secattr,
<a name="L1364" href="source/net/ipv4/cipso_ipv4.c#L1364">1364</a>                                 unsigned char *<a href="ident?i=buffer">buffer</a>,
<a name="L1365" href="source/net/ipv4/cipso_ipv4.c#L1365">1365</a>                                 <a href="ident?i=u32">u32</a> <a href="ident?i=buffer_len">buffer_len</a>)
<a name="L1366" href="source/net/ipv4/cipso_ipv4.c#L1366">1366</a> {
<a name="L1367" href="source/net/ipv4/cipso_ipv4.c#L1367">1367</a>         int ret_val;
<a name="L1368" href="source/net/ipv4/cipso_ipv4.c#L1368">1368</a>         <a href="ident?i=u32">u32</a> tag_len;
<a name="L1369" href="source/net/ipv4/cipso_ipv4.c#L1369">1369</a>         <a href="ident?i=u32">u32</a> <a href="ident?i=level">level</a>;
<a name="L1370" href="source/net/ipv4/cipso_ipv4.c#L1370">1370</a> 
<a name="L1371" href="source/net/ipv4/cipso_ipv4.c#L1371">1371</a>         if (!(secattr-&gt;<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=NETLBL_SECATTR_MLS_LVL">NETLBL_SECATTR_MLS_LVL</a>))
<a name="L1372" href="source/net/ipv4/cipso_ipv4.c#L1372">1372</a>                 return -<a href="ident?i=EPERM">EPERM</a>;
<a name="L1373" href="source/net/ipv4/cipso_ipv4.c#L1373">1373</a> 
<a name="L1374" href="source/net/ipv4/cipso_ipv4.c#L1374">1374</a>         ret_val = <a href="ident?i=cipso_v4_map_lvl_hton">cipso_v4_map_lvl_hton</a>(doi_def,
<a name="L1375" href="source/net/ipv4/cipso_ipv4.c#L1375">1375</a>                                         secattr-&gt;<a href="ident?i=attr">attr</a>.mls.lvl,
<a name="L1376" href="source/net/ipv4/cipso_ipv4.c#L1376">1376</a>                                         &amp;<a href="ident?i=level">level</a>);
<a name="L1377" href="source/net/ipv4/cipso_ipv4.c#L1377">1377</a>         if (ret_val != 0)
<a name="L1378" href="source/net/ipv4/cipso_ipv4.c#L1378">1378</a>                 return ret_val;
<a name="L1379" href="source/net/ipv4/cipso_ipv4.c#L1379">1379</a> 
<a name="L1380" href="source/net/ipv4/cipso_ipv4.c#L1380">1380</a>         if (secattr-&gt;<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=NETLBL_SECATTR_MLS_CAT">NETLBL_SECATTR_MLS_CAT</a>) {
<a name="L1381" href="source/net/ipv4/cipso_ipv4.c#L1381">1381</a>                 ret_val = <a href="ident?i=cipso_v4_map_cat_enum_hton">cipso_v4_map_cat_enum_hton</a>(doi_def,
<a name="L1382" href="source/net/ipv4/cipso_ipv4.c#L1382">1382</a>                                                      secattr,
<a name="L1383" href="source/net/ipv4/cipso_ipv4.c#L1383">1383</a>                                                      &amp;<a href="ident?i=buffer">buffer</a>[4],
<a name="L1384" href="source/net/ipv4/cipso_ipv4.c#L1384">1384</a>                                                      <a href="ident?i=buffer_len">buffer_len</a> - 4);
<a name="L1385" href="source/net/ipv4/cipso_ipv4.c#L1385">1385</a>                 if (ret_val &lt; 0)
<a name="L1386" href="source/net/ipv4/cipso_ipv4.c#L1386">1386</a>                         return ret_val;
<a name="L1387" href="source/net/ipv4/cipso_ipv4.c#L1387">1387</a> 
<a name="L1388" href="source/net/ipv4/cipso_ipv4.c#L1388">1388</a>                 tag_len = 4 + ret_val;
<a name="L1389" href="source/net/ipv4/cipso_ipv4.c#L1389">1389</a>         } else
<a name="L1390" href="source/net/ipv4/cipso_ipv4.c#L1390">1390</a>                 tag_len = 4;
<a name="L1391" href="source/net/ipv4/cipso_ipv4.c#L1391">1391</a> 
<a name="L1392" href="source/net/ipv4/cipso_ipv4.c#L1392">1392</a>         <a href="ident?i=buffer">buffer</a>[0] = <a href="ident?i=CIPSO_V4_TAG_ENUM">CIPSO_V4_TAG_ENUM</a>;
<a name="L1393" href="source/net/ipv4/cipso_ipv4.c#L1393">1393</a>         <a href="ident?i=buffer">buffer</a>[1] = tag_len;
<a name="L1394" href="source/net/ipv4/cipso_ipv4.c#L1394">1394</a>         <a href="ident?i=buffer">buffer</a>[3] = <a href="ident?i=level">level</a>;
<a name="L1395" href="source/net/ipv4/cipso_ipv4.c#L1395">1395</a> 
<a name="L1396" href="source/net/ipv4/cipso_ipv4.c#L1396">1396</a>         return tag_len;
<a name="L1397" href="source/net/ipv4/cipso_ipv4.c#L1397">1397</a> }
<a name="L1398" href="source/net/ipv4/cipso_ipv4.c#L1398">1398</a> 
<a name="L1399" href="source/net/ipv4/cipso_ipv4.c#L1399">1399</a> <b><i>/**</i></b>
<a name="L1400" href="source/net/ipv4/cipso_ipv4.c#L1400">1400</a> <b><i> * cipso_v4_parsetag_enum - Parse a CIPSO enumerated tag</i></b>
<a name="L1401" href="source/net/ipv4/cipso_ipv4.c#L1401">1401</a> <b><i> * @doi_def: the DOI definition</i></b>
<a name="L1402" href="source/net/ipv4/cipso_ipv4.c#L1402">1402</a> <b><i> * @tag: the CIPSO tag</i></b>
<a name="L1403" href="source/net/ipv4/cipso_ipv4.c#L1403">1403</a> <b><i> * @secattr: the security attributes</i></b>
<a name="L1404" href="source/net/ipv4/cipso_ipv4.c#L1404">1404</a> <b><i> *</i></b>
<a name="L1405" href="source/net/ipv4/cipso_ipv4.c#L1405">1405</a> <b><i> * Description:</i></b>
<a name="L1406" href="source/net/ipv4/cipso_ipv4.c#L1406">1406</a> <b><i> * Parse a CIPSO enumerated tag (tag type #2) and return the security</i></b>
<a name="L1407" href="source/net/ipv4/cipso_ipv4.c#L1407">1407</a> <b><i> * attributes in @secattr.  Return zero on success, negatives values on</i></b>
<a name="L1408" href="source/net/ipv4/cipso_ipv4.c#L1408">1408</a> <b><i> * failure.</i></b>
<a name="L1409" href="source/net/ipv4/cipso_ipv4.c#L1409">1409</a> <b><i> *</i></b>
<a name="L1410" href="source/net/ipv4/cipso_ipv4.c#L1410">1410</a> <b><i> */</i></b>
<a name="L1411" href="source/net/ipv4/cipso_ipv4.c#L1411">1411</a> static int <a href="ident?i=cipso_v4_parsetag_enum">cipso_v4_parsetag_enum</a>(const struct <a href="ident?i=cipso_v4_doi">cipso_v4_doi</a> *doi_def,
<a name="L1412" href="source/net/ipv4/cipso_ipv4.c#L1412">1412</a>                                   const unsigned char *<a href="ident?i=tag">tag</a>,
<a name="L1413" href="source/net/ipv4/cipso_ipv4.c#L1413">1413</a>                                   struct <a href="ident?i=netlbl_lsm_secattr">netlbl_lsm_secattr</a> *secattr)
<a name="L1414" href="source/net/ipv4/cipso_ipv4.c#L1414">1414</a> {
<a name="L1415" href="source/net/ipv4/cipso_ipv4.c#L1415">1415</a>         int ret_val;
<a name="L1416" href="source/net/ipv4/cipso_ipv4.c#L1416">1416</a>         <a href="ident?i=u8">u8</a> tag_len = <a href="ident?i=tag">tag</a>[1];
<a name="L1417" href="source/net/ipv4/cipso_ipv4.c#L1417">1417</a>         <a href="ident?i=u32">u32</a> <a href="ident?i=level">level</a>;
<a name="L1418" href="source/net/ipv4/cipso_ipv4.c#L1418">1418</a> 
<a name="L1419" href="source/net/ipv4/cipso_ipv4.c#L1419">1419</a>         ret_val = <a href="ident?i=cipso_v4_map_lvl_ntoh">cipso_v4_map_lvl_ntoh</a>(doi_def, <a href="ident?i=tag">tag</a>[3], &amp;<a href="ident?i=level">level</a>);
<a name="L1420" href="source/net/ipv4/cipso_ipv4.c#L1420">1420</a>         if (ret_val != 0)
<a name="L1421" href="source/net/ipv4/cipso_ipv4.c#L1421">1421</a>                 return ret_val;
<a name="L1422" href="source/net/ipv4/cipso_ipv4.c#L1422">1422</a>         secattr-&gt;<a href="ident?i=attr">attr</a>.mls.lvl = <a href="ident?i=level">level</a>;
<a name="L1423" href="source/net/ipv4/cipso_ipv4.c#L1423">1423</a>         secattr-&gt;<a href="ident?i=flags">flags</a> |= <a href="ident?i=NETLBL_SECATTR_MLS_LVL">NETLBL_SECATTR_MLS_LVL</a>;
<a name="L1424" href="source/net/ipv4/cipso_ipv4.c#L1424">1424</a> 
<a name="L1425" href="source/net/ipv4/cipso_ipv4.c#L1425">1425</a>         if (tag_len &gt; 4) {
<a name="L1426" href="source/net/ipv4/cipso_ipv4.c#L1426">1426</a>                 ret_val = <a href="ident?i=cipso_v4_map_cat_enum_ntoh">cipso_v4_map_cat_enum_ntoh</a>(doi_def,
<a name="L1427" href="source/net/ipv4/cipso_ipv4.c#L1427">1427</a>                                                      &amp;<a href="ident?i=tag">tag</a>[4],
<a name="L1428" href="source/net/ipv4/cipso_ipv4.c#L1428">1428</a>                                                      tag_len - 4,
<a name="L1429" href="source/net/ipv4/cipso_ipv4.c#L1429">1429</a>                                                      secattr);
<a name="L1430" href="source/net/ipv4/cipso_ipv4.c#L1430">1430</a>                 if (ret_val != 0) {
<a name="L1431" href="source/net/ipv4/cipso_ipv4.c#L1431">1431</a>                         <a href="ident?i=netlbl_catmap_free">netlbl_catmap_free</a>(secattr-&gt;<a href="ident?i=attr">attr</a>.mls.cat);
<a name="L1432" href="source/net/ipv4/cipso_ipv4.c#L1432">1432</a>                         return ret_val;
<a name="L1433" href="source/net/ipv4/cipso_ipv4.c#L1433">1433</a>                 }
<a name="L1434" href="source/net/ipv4/cipso_ipv4.c#L1434">1434</a> 
<a name="L1435" href="source/net/ipv4/cipso_ipv4.c#L1435">1435</a>                 secattr-&gt;<a href="ident?i=flags">flags</a> |= <a href="ident?i=NETLBL_SECATTR_MLS_CAT">NETLBL_SECATTR_MLS_CAT</a>;
<a name="L1436" href="source/net/ipv4/cipso_ipv4.c#L1436">1436</a>         }
<a name="L1437" href="source/net/ipv4/cipso_ipv4.c#L1437">1437</a> 
<a name="L1438" href="source/net/ipv4/cipso_ipv4.c#L1438">1438</a>         return 0;
<a name="L1439" href="source/net/ipv4/cipso_ipv4.c#L1439">1439</a> }
<a name="L1440" href="source/net/ipv4/cipso_ipv4.c#L1440">1440</a> 
<a name="L1441" href="source/net/ipv4/cipso_ipv4.c#L1441">1441</a> <b><i>/**</i></b>
<a name="L1442" href="source/net/ipv4/cipso_ipv4.c#L1442">1442</a> <b><i> * cipso_v4_gentag_rng - Generate a CIPSO ranged tag (type #5)</i></b>
<a name="L1443" href="source/net/ipv4/cipso_ipv4.c#L1443">1443</a> <b><i> * @doi_def: the DOI definition</i></b>
<a name="L1444" href="source/net/ipv4/cipso_ipv4.c#L1444">1444</a> <b><i> * @secattr: the security attributes</i></b>
<a name="L1445" href="source/net/ipv4/cipso_ipv4.c#L1445">1445</a> <b><i> * @buffer: the option buffer</i></b>
<a name="L1446" href="source/net/ipv4/cipso_ipv4.c#L1446">1446</a> <b><i> * @buffer_len: length of buffer in bytes</i></b>
<a name="L1447" href="source/net/ipv4/cipso_ipv4.c#L1447">1447</a> <b><i> *</i></b>
<a name="L1448" href="source/net/ipv4/cipso_ipv4.c#L1448">1448</a> <b><i> * Description:</i></b>
<a name="L1449" href="source/net/ipv4/cipso_ipv4.c#L1449">1449</a> <b><i> * Generate a CIPSO option using the ranged tag, tag type #5.  Returns the</i></b>
<a name="L1450" href="source/net/ipv4/cipso_ipv4.c#L1450">1450</a> <b><i> * size of the tag on success, negative values on failure.</i></b>
<a name="L1451" href="source/net/ipv4/cipso_ipv4.c#L1451">1451</a> <b><i> *</i></b>
<a name="L1452" href="source/net/ipv4/cipso_ipv4.c#L1452">1452</a> <b><i> */</i></b>
<a name="L1453" href="source/net/ipv4/cipso_ipv4.c#L1453">1453</a> static int <a href="ident?i=cipso_v4_gentag_rng">cipso_v4_gentag_rng</a>(const struct <a href="ident?i=cipso_v4_doi">cipso_v4_doi</a> *doi_def,
<a name="L1454" href="source/net/ipv4/cipso_ipv4.c#L1454">1454</a>                                const struct <a href="ident?i=netlbl_lsm_secattr">netlbl_lsm_secattr</a> *secattr,
<a name="L1455" href="source/net/ipv4/cipso_ipv4.c#L1455">1455</a>                                unsigned char *<a href="ident?i=buffer">buffer</a>,
<a name="L1456" href="source/net/ipv4/cipso_ipv4.c#L1456">1456</a>                                <a href="ident?i=u32">u32</a> <a href="ident?i=buffer_len">buffer_len</a>)
<a name="L1457" href="source/net/ipv4/cipso_ipv4.c#L1457">1457</a> {
<a name="L1458" href="source/net/ipv4/cipso_ipv4.c#L1458">1458</a>         int ret_val;
<a name="L1459" href="source/net/ipv4/cipso_ipv4.c#L1459">1459</a>         <a href="ident?i=u32">u32</a> tag_len;
<a name="L1460" href="source/net/ipv4/cipso_ipv4.c#L1460">1460</a>         <a href="ident?i=u32">u32</a> <a href="ident?i=level">level</a>;
<a name="L1461" href="source/net/ipv4/cipso_ipv4.c#L1461">1461</a> 
<a name="L1462" href="source/net/ipv4/cipso_ipv4.c#L1462">1462</a>         if (!(secattr-&gt;<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=NETLBL_SECATTR_MLS_LVL">NETLBL_SECATTR_MLS_LVL</a>))
<a name="L1463" href="source/net/ipv4/cipso_ipv4.c#L1463">1463</a>                 return -<a href="ident?i=EPERM">EPERM</a>;
<a name="L1464" href="source/net/ipv4/cipso_ipv4.c#L1464">1464</a> 
<a name="L1465" href="source/net/ipv4/cipso_ipv4.c#L1465">1465</a>         ret_val = <a href="ident?i=cipso_v4_map_lvl_hton">cipso_v4_map_lvl_hton</a>(doi_def,
<a name="L1466" href="source/net/ipv4/cipso_ipv4.c#L1466">1466</a>                                         secattr-&gt;<a href="ident?i=attr">attr</a>.mls.lvl,
<a name="L1467" href="source/net/ipv4/cipso_ipv4.c#L1467">1467</a>                                         &amp;<a href="ident?i=level">level</a>);
<a name="L1468" href="source/net/ipv4/cipso_ipv4.c#L1468">1468</a>         if (ret_val != 0)
<a name="L1469" href="source/net/ipv4/cipso_ipv4.c#L1469">1469</a>                 return ret_val;
<a name="L1470" href="source/net/ipv4/cipso_ipv4.c#L1470">1470</a> 
<a name="L1471" href="source/net/ipv4/cipso_ipv4.c#L1471">1471</a>         if (secattr-&gt;<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=NETLBL_SECATTR_MLS_CAT">NETLBL_SECATTR_MLS_CAT</a>) {
<a name="L1472" href="source/net/ipv4/cipso_ipv4.c#L1472">1472</a>                 ret_val = <a href="ident?i=cipso_v4_map_cat_rng_hton">cipso_v4_map_cat_rng_hton</a>(doi_def,
<a name="L1473" href="source/net/ipv4/cipso_ipv4.c#L1473">1473</a>                                                     secattr,
<a name="L1474" href="source/net/ipv4/cipso_ipv4.c#L1474">1474</a>                                                     &amp;<a href="ident?i=buffer">buffer</a>[4],
<a name="L1475" href="source/net/ipv4/cipso_ipv4.c#L1475">1475</a>                                                     <a href="ident?i=buffer_len">buffer_len</a> - 4);
<a name="L1476" href="source/net/ipv4/cipso_ipv4.c#L1476">1476</a>                 if (ret_val &lt; 0)
<a name="L1477" href="source/net/ipv4/cipso_ipv4.c#L1477">1477</a>                         return ret_val;
<a name="L1478" href="source/net/ipv4/cipso_ipv4.c#L1478">1478</a> 
<a name="L1479" href="source/net/ipv4/cipso_ipv4.c#L1479">1479</a>                 tag_len = 4 + ret_val;
<a name="L1480" href="source/net/ipv4/cipso_ipv4.c#L1480">1480</a>         } else
<a name="L1481" href="source/net/ipv4/cipso_ipv4.c#L1481">1481</a>                 tag_len = 4;
<a name="L1482" href="source/net/ipv4/cipso_ipv4.c#L1482">1482</a> 
<a name="L1483" href="source/net/ipv4/cipso_ipv4.c#L1483">1483</a>         <a href="ident?i=buffer">buffer</a>[0] = <a href="ident?i=CIPSO_V4_TAG_RANGE">CIPSO_V4_TAG_RANGE</a>;
<a name="L1484" href="source/net/ipv4/cipso_ipv4.c#L1484">1484</a>         <a href="ident?i=buffer">buffer</a>[1] = tag_len;
<a name="L1485" href="source/net/ipv4/cipso_ipv4.c#L1485">1485</a>         <a href="ident?i=buffer">buffer</a>[3] = <a href="ident?i=level">level</a>;
<a name="L1486" href="source/net/ipv4/cipso_ipv4.c#L1486">1486</a> 
<a name="L1487" href="source/net/ipv4/cipso_ipv4.c#L1487">1487</a>         return tag_len;
<a name="L1488" href="source/net/ipv4/cipso_ipv4.c#L1488">1488</a> }
<a name="L1489" href="source/net/ipv4/cipso_ipv4.c#L1489">1489</a> 
<a name="L1490" href="source/net/ipv4/cipso_ipv4.c#L1490">1490</a> <b><i>/**</i></b>
<a name="L1491" href="source/net/ipv4/cipso_ipv4.c#L1491">1491</a> <b><i> * cipso_v4_parsetag_rng - Parse a CIPSO ranged tag</i></b>
<a name="L1492" href="source/net/ipv4/cipso_ipv4.c#L1492">1492</a> <b><i> * @doi_def: the DOI definition</i></b>
<a name="L1493" href="source/net/ipv4/cipso_ipv4.c#L1493">1493</a> <b><i> * @tag: the CIPSO tag</i></b>
<a name="L1494" href="source/net/ipv4/cipso_ipv4.c#L1494">1494</a> <b><i> * @secattr: the security attributes</i></b>
<a name="L1495" href="source/net/ipv4/cipso_ipv4.c#L1495">1495</a> <b><i> *</i></b>
<a name="L1496" href="source/net/ipv4/cipso_ipv4.c#L1496">1496</a> <b><i> * Description:</i></b>
<a name="L1497" href="source/net/ipv4/cipso_ipv4.c#L1497">1497</a> <b><i> * Parse a CIPSO ranged tag (tag type #5) and return the security attributes</i></b>
<a name="L1498" href="source/net/ipv4/cipso_ipv4.c#L1498">1498</a> <b><i> * in @secattr.  Return zero on success, negatives values on failure.</i></b>
<a name="L1499" href="source/net/ipv4/cipso_ipv4.c#L1499">1499</a> <b><i> *</i></b>
<a name="L1500" href="source/net/ipv4/cipso_ipv4.c#L1500">1500</a> <b><i> */</i></b>
<a name="L1501" href="source/net/ipv4/cipso_ipv4.c#L1501">1501</a> static int <a href="ident?i=cipso_v4_parsetag_rng">cipso_v4_parsetag_rng</a>(const struct <a href="ident?i=cipso_v4_doi">cipso_v4_doi</a> *doi_def,
<a name="L1502" href="source/net/ipv4/cipso_ipv4.c#L1502">1502</a>                                  const unsigned char *<a href="ident?i=tag">tag</a>,
<a name="L1503" href="source/net/ipv4/cipso_ipv4.c#L1503">1503</a>                                  struct <a href="ident?i=netlbl_lsm_secattr">netlbl_lsm_secattr</a> *secattr)
<a name="L1504" href="source/net/ipv4/cipso_ipv4.c#L1504">1504</a> {
<a name="L1505" href="source/net/ipv4/cipso_ipv4.c#L1505">1505</a>         int ret_val;
<a name="L1506" href="source/net/ipv4/cipso_ipv4.c#L1506">1506</a>         <a href="ident?i=u8">u8</a> tag_len = <a href="ident?i=tag">tag</a>[1];
<a name="L1507" href="source/net/ipv4/cipso_ipv4.c#L1507">1507</a>         <a href="ident?i=u32">u32</a> <a href="ident?i=level">level</a>;
<a name="L1508" href="source/net/ipv4/cipso_ipv4.c#L1508">1508</a> 
<a name="L1509" href="source/net/ipv4/cipso_ipv4.c#L1509">1509</a>         ret_val = <a href="ident?i=cipso_v4_map_lvl_ntoh">cipso_v4_map_lvl_ntoh</a>(doi_def, <a href="ident?i=tag">tag</a>[3], &amp;<a href="ident?i=level">level</a>);
<a name="L1510" href="source/net/ipv4/cipso_ipv4.c#L1510">1510</a>         if (ret_val != 0)
<a name="L1511" href="source/net/ipv4/cipso_ipv4.c#L1511">1511</a>                 return ret_val;
<a name="L1512" href="source/net/ipv4/cipso_ipv4.c#L1512">1512</a>         secattr-&gt;<a href="ident?i=attr">attr</a>.mls.lvl = <a href="ident?i=level">level</a>;
<a name="L1513" href="source/net/ipv4/cipso_ipv4.c#L1513">1513</a>         secattr-&gt;<a href="ident?i=flags">flags</a> |= <a href="ident?i=NETLBL_SECATTR_MLS_LVL">NETLBL_SECATTR_MLS_LVL</a>;
<a name="L1514" href="source/net/ipv4/cipso_ipv4.c#L1514">1514</a> 
<a name="L1515" href="source/net/ipv4/cipso_ipv4.c#L1515">1515</a>         if (tag_len &gt; 4) {
<a name="L1516" href="source/net/ipv4/cipso_ipv4.c#L1516">1516</a>                 ret_val = <a href="ident?i=cipso_v4_map_cat_rng_ntoh">cipso_v4_map_cat_rng_ntoh</a>(doi_def,
<a name="L1517" href="source/net/ipv4/cipso_ipv4.c#L1517">1517</a>                                                     &amp;<a href="ident?i=tag">tag</a>[4],
<a name="L1518" href="source/net/ipv4/cipso_ipv4.c#L1518">1518</a>                                                     tag_len - 4,
<a name="L1519" href="source/net/ipv4/cipso_ipv4.c#L1519">1519</a>                                                     secattr);
<a name="L1520" href="source/net/ipv4/cipso_ipv4.c#L1520">1520</a>                 if (ret_val != 0) {
<a name="L1521" href="source/net/ipv4/cipso_ipv4.c#L1521">1521</a>                         <a href="ident?i=netlbl_catmap_free">netlbl_catmap_free</a>(secattr-&gt;<a href="ident?i=attr">attr</a>.mls.cat);
<a name="L1522" href="source/net/ipv4/cipso_ipv4.c#L1522">1522</a>                         return ret_val;
<a name="L1523" href="source/net/ipv4/cipso_ipv4.c#L1523">1523</a>                 }
<a name="L1524" href="source/net/ipv4/cipso_ipv4.c#L1524">1524</a> 
<a name="L1525" href="source/net/ipv4/cipso_ipv4.c#L1525">1525</a>                 secattr-&gt;<a href="ident?i=flags">flags</a> |= <a href="ident?i=NETLBL_SECATTR_MLS_CAT">NETLBL_SECATTR_MLS_CAT</a>;
<a name="L1526" href="source/net/ipv4/cipso_ipv4.c#L1526">1526</a>         }
<a name="L1527" href="source/net/ipv4/cipso_ipv4.c#L1527">1527</a> 
<a name="L1528" href="source/net/ipv4/cipso_ipv4.c#L1528">1528</a>         return 0;
<a name="L1529" href="source/net/ipv4/cipso_ipv4.c#L1529">1529</a> }
<a name="L1530" href="source/net/ipv4/cipso_ipv4.c#L1530">1530</a> 
<a name="L1531" href="source/net/ipv4/cipso_ipv4.c#L1531">1531</a> <b><i>/**</i></b>
<a name="L1532" href="source/net/ipv4/cipso_ipv4.c#L1532">1532</a> <b><i> * cipso_v4_gentag_loc - Generate a CIPSO local tag (non-standard)</i></b>
<a name="L1533" href="source/net/ipv4/cipso_ipv4.c#L1533">1533</a> <b><i> * @doi_def: the DOI definition</i></b>
<a name="L1534" href="source/net/ipv4/cipso_ipv4.c#L1534">1534</a> <b><i> * @secattr: the security attributes</i></b>
<a name="L1535" href="source/net/ipv4/cipso_ipv4.c#L1535">1535</a> <b><i> * @buffer: the option buffer</i></b>
<a name="L1536" href="source/net/ipv4/cipso_ipv4.c#L1536">1536</a> <b><i> * @buffer_len: length of buffer in bytes</i></b>
<a name="L1537" href="source/net/ipv4/cipso_ipv4.c#L1537">1537</a> <b><i> *</i></b>
<a name="L1538" href="source/net/ipv4/cipso_ipv4.c#L1538">1538</a> <b><i> * Description:</i></b>
<a name="L1539" href="source/net/ipv4/cipso_ipv4.c#L1539">1539</a> <b><i> * Generate a CIPSO option using the local tag.  Returns the size of the tag</i></b>
<a name="L1540" href="source/net/ipv4/cipso_ipv4.c#L1540">1540</a> <b><i> * on success, negative values on failure.</i></b>
<a name="L1541" href="source/net/ipv4/cipso_ipv4.c#L1541">1541</a> <b><i> *</i></b>
<a name="L1542" href="source/net/ipv4/cipso_ipv4.c#L1542">1542</a> <b><i> */</i></b>
<a name="L1543" href="source/net/ipv4/cipso_ipv4.c#L1543">1543</a> static int <a href="ident?i=cipso_v4_gentag_loc">cipso_v4_gentag_loc</a>(const struct <a href="ident?i=cipso_v4_doi">cipso_v4_doi</a> *doi_def,
<a name="L1544" href="source/net/ipv4/cipso_ipv4.c#L1544">1544</a>                                const struct <a href="ident?i=netlbl_lsm_secattr">netlbl_lsm_secattr</a> *secattr,
<a name="L1545" href="source/net/ipv4/cipso_ipv4.c#L1545">1545</a>                                unsigned char *<a href="ident?i=buffer">buffer</a>,
<a name="L1546" href="source/net/ipv4/cipso_ipv4.c#L1546">1546</a>                                <a href="ident?i=u32">u32</a> <a href="ident?i=buffer_len">buffer_len</a>)
<a name="L1547" href="source/net/ipv4/cipso_ipv4.c#L1547">1547</a> {
<a name="L1548" href="source/net/ipv4/cipso_ipv4.c#L1548">1548</a>         if (!(secattr-&gt;<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=NETLBL_SECATTR_SECID">NETLBL_SECATTR_SECID</a>))
<a name="L1549" href="source/net/ipv4/cipso_ipv4.c#L1549">1549</a>                 return -<a href="ident?i=EPERM">EPERM</a>;
<a name="L1550" href="source/net/ipv4/cipso_ipv4.c#L1550">1550</a> 
<a name="L1551" href="source/net/ipv4/cipso_ipv4.c#L1551">1551</a>         <a href="ident?i=buffer">buffer</a>[0] = <a href="ident?i=CIPSO_V4_TAG_LOCAL">CIPSO_V4_TAG_LOCAL</a>;
<a name="L1552" href="source/net/ipv4/cipso_ipv4.c#L1552">1552</a>         <a href="ident?i=buffer">buffer</a>[1] = <a href="ident?i=CIPSO_V4_TAG_LOC_BLEN">CIPSO_V4_TAG_LOC_BLEN</a>;
<a name="L1553" href="source/net/ipv4/cipso_ipv4.c#L1553">1553</a>         *(<a href="ident?i=u32">u32</a> *)&amp;<a href="ident?i=buffer">buffer</a>[2] = secattr-&gt;<a href="ident?i=attr">attr</a>.secid;
<a name="L1554" href="source/net/ipv4/cipso_ipv4.c#L1554">1554</a> 
<a name="L1555" href="source/net/ipv4/cipso_ipv4.c#L1555">1555</a>         return <a href="ident?i=CIPSO_V4_TAG_LOC_BLEN">CIPSO_V4_TAG_LOC_BLEN</a>;
<a name="L1556" href="source/net/ipv4/cipso_ipv4.c#L1556">1556</a> }
<a name="L1557" href="source/net/ipv4/cipso_ipv4.c#L1557">1557</a> 
<a name="L1558" href="source/net/ipv4/cipso_ipv4.c#L1558">1558</a> <b><i>/**</i></b>
<a name="L1559" href="source/net/ipv4/cipso_ipv4.c#L1559">1559</a> <b><i> * cipso_v4_parsetag_loc - Parse a CIPSO local tag</i></b>
<a name="L1560" href="source/net/ipv4/cipso_ipv4.c#L1560">1560</a> <b><i> * @doi_def: the DOI definition</i></b>
<a name="L1561" href="source/net/ipv4/cipso_ipv4.c#L1561">1561</a> <b><i> * @tag: the CIPSO tag</i></b>
<a name="L1562" href="source/net/ipv4/cipso_ipv4.c#L1562">1562</a> <b><i> * @secattr: the security attributes</i></b>
<a name="L1563" href="source/net/ipv4/cipso_ipv4.c#L1563">1563</a> <b><i> *</i></b>
<a name="L1564" href="source/net/ipv4/cipso_ipv4.c#L1564">1564</a> <b><i> * Description:</i></b>
<a name="L1565" href="source/net/ipv4/cipso_ipv4.c#L1565">1565</a> <b><i> * Parse a CIPSO local tag and return the security attributes in @secattr.</i></b>
<a name="L1566" href="source/net/ipv4/cipso_ipv4.c#L1566">1566</a> <b><i> * Return zero on success, negatives values on failure.</i></b>
<a name="L1567" href="source/net/ipv4/cipso_ipv4.c#L1567">1567</a> <b><i> *</i></b>
<a name="L1568" href="source/net/ipv4/cipso_ipv4.c#L1568">1568</a> <b><i> */</i></b>
<a name="L1569" href="source/net/ipv4/cipso_ipv4.c#L1569">1569</a> static int <a href="ident?i=cipso_v4_parsetag_loc">cipso_v4_parsetag_loc</a>(const struct <a href="ident?i=cipso_v4_doi">cipso_v4_doi</a> *doi_def,
<a name="L1570" href="source/net/ipv4/cipso_ipv4.c#L1570">1570</a>                                  const unsigned char *<a href="ident?i=tag">tag</a>,
<a name="L1571" href="source/net/ipv4/cipso_ipv4.c#L1571">1571</a>                                  struct <a href="ident?i=netlbl_lsm_secattr">netlbl_lsm_secattr</a> *secattr)
<a name="L1572" href="source/net/ipv4/cipso_ipv4.c#L1572">1572</a> {
<a name="L1573" href="source/net/ipv4/cipso_ipv4.c#L1573">1573</a>         secattr-&gt;<a href="ident?i=attr">attr</a>.secid = *(<a href="ident?i=u32">u32</a> *)&amp;<a href="ident?i=tag">tag</a>[2];
<a name="L1574" href="source/net/ipv4/cipso_ipv4.c#L1574">1574</a>         secattr-&gt;<a href="ident?i=flags">flags</a> |= <a href="ident?i=NETLBL_SECATTR_SECID">NETLBL_SECATTR_SECID</a>;
<a name="L1575" href="source/net/ipv4/cipso_ipv4.c#L1575">1575</a> 
<a name="L1576" href="source/net/ipv4/cipso_ipv4.c#L1576">1576</a>         return 0;
<a name="L1577" href="source/net/ipv4/cipso_ipv4.c#L1577">1577</a> }
<a name="L1578" href="source/net/ipv4/cipso_ipv4.c#L1578">1578</a> 
<a name="L1579" href="source/net/ipv4/cipso_ipv4.c#L1579">1579</a> <b><i>/**</i></b>
<a name="L1580" href="source/net/ipv4/cipso_ipv4.c#L1580">1580</a> <b><i> * cipso_v4_optptr - Find the CIPSO option in the packet</i></b>
<a name="L1581" href="source/net/ipv4/cipso_ipv4.c#L1581">1581</a> <b><i> * @skb: the packet</i></b>
<a name="L1582" href="source/net/ipv4/cipso_ipv4.c#L1582">1582</a> <b><i> *</i></b>
<a name="L1583" href="source/net/ipv4/cipso_ipv4.c#L1583">1583</a> <b><i> * Description:</i></b>
<a name="L1584" href="source/net/ipv4/cipso_ipv4.c#L1584">1584</a> <b><i> * Parse the packet's IP header looking for a CIPSO option.  Returns a pointer</i></b>
<a name="L1585" href="source/net/ipv4/cipso_ipv4.c#L1585">1585</a> <b><i> * to the start of the CIPSO option on success, NULL if one if not found.</i></b>
<a name="L1586" href="source/net/ipv4/cipso_ipv4.c#L1586">1586</a> <b><i> *</i></b>
<a name="L1587" href="source/net/ipv4/cipso_ipv4.c#L1587">1587</a> <b><i> */</i></b>
<a name="L1588" href="source/net/ipv4/cipso_ipv4.c#L1588">1588</a> unsigned char *<a href="ident?i=cipso_v4_optptr">cipso_v4_optptr</a>(const struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L1589" href="source/net/ipv4/cipso_ipv4.c#L1589">1589</a> {
<a name="L1590" href="source/net/ipv4/cipso_ipv4.c#L1590">1590</a>         const struct <a href="ident?i=iphdr">iphdr</a> *iph = <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>);
<a name="L1591" href="source/net/ipv4/cipso_ipv4.c#L1591">1591</a>         unsigned char *optptr = (unsigned char *)&amp;(<a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>)[1]);
<a name="L1592" href="source/net/ipv4/cipso_ipv4.c#L1592">1592</a>         int <a href="ident?i=optlen">optlen</a>;
<a name="L1593" href="source/net/ipv4/cipso_ipv4.c#L1593">1593</a>         int taglen;
<a name="L1594" href="source/net/ipv4/cipso_ipv4.c#L1594">1594</a> 
<a name="L1595" href="source/net/ipv4/cipso_ipv4.c#L1595">1595</a>         for (<a href="ident?i=optlen">optlen</a> = iph-&gt;ihl*4 - sizeof(struct <a href="ident?i=iphdr">iphdr</a>); <a href="ident?i=optlen">optlen</a> &gt; 0; ) {
<a name="L1596" href="source/net/ipv4/cipso_ipv4.c#L1596">1596</a>                 if (optptr[0] == <a href="ident?i=IPOPT_CIPSO">IPOPT_CIPSO</a>)
<a name="L1597" href="source/net/ipv4/cipso_ipv4.c#L1597">1597</a>                         return optptr;
<a name="L1598" href="source/net/ipv4/cipso_ipv4.c#L1598">1598</a>                 taglen = optptr[1];
<a name="L1599" href="source/net/ipv4/cipso_ipv4.c#L1599">1599</a>                 <a href="ident?i=optlen">optlen</a> -= taglen;
<a name="L1600" href="source/net/ipv4/cipso_ipv4.c#L1600">1600</a>                 optptr += taglen;
<a name="L1601" href="source/net/ipv4/cipso_ipv4.c#L1601">1601</a>         }
<a name="L1602" href="source/net/ipv4/cipso_ipv4.c#L1602">1602</a> 
<a name="L1603" href="source/net/ipv4/cipso_ipv4.c#L1603">1603</a>         return <a href="ident?i=NULL">NULL</a>;
<a name="L1604" href="source/net/ipv4/cipso_ipv4.c#L1604">1604</a> }
<a name="L1605" href="source/net/ipv4/cipso_ipv4.c#L1605">1605</a> 
<a name="L1606" href="source/net/ipv4/cipso_ipv4.c#L1606">1606</a> <b><i>/**</i></b>
<a name="L1607" href="source/net/ipv4/cipso_ipv4.c#L1607">1607</a> <b><i> * cipso_v4_validate - Validate a CIPSO option</i></b>
<a name="L1608" href="source/net/ipv4/cipso_ipv4.c#L1608">1608</a> <b><i> * @option: the start of the option, on error it is set to point to the error</i></b>
<a name="L1609" href="source/net/ipv4/cipso_ipv4.c#L1609">1609</a> <b><i> *</i></b>
<a name="L1610" href="source/net/ipv4/cipso_ipv4.c#L1610">1610</a> <b><i> * Description:</i></b>
<a name="L1611" href="source/net/ipv4/cipso_ipv4.c#L1611">1611</a> <b><i> * This routine is called to validate a CIPSO option, it checks all of the</i></b>
<a name="L1612" href="source/net/ipv4/cipso_ipv4.c#L1612">1612</a> <b><i> * fields to ensure that they are at least valid, see the draft snippet below</i></b>
<a name="L1613" href="source/net/ipv4/cipso_ipv4.c#L1613">1613</a> <b><i> * for details.  If the option is valid then a zero value is returned and</i></b>
<a name="L1614" href="source/net/ipv4/cipso_ipv4.c#L1614">1614</a> <b><i> * the value of @option is unchanged.  If the option is invalid then a</i></b>
<a name="L1615" href="source/net/ipv4/cipso_ipv4.c#L1615">1615</a> <b><i> * non-zero value is returned and @option is adjusted to point to the</i></b>
<a name="L1616" href="source/net/ipv4/cipso_ipv4.c#L1616">1616</a> <b><i> * offending portion of the option.  From the IETF draft ...</i></b>
<a name="L1617" href="source/net/ipv4/cipso_ipv4.c#L1617">1617</a> <b><i> *</i></b>
<a name="L1618" href="source/net/ipv4/cipso_ipv4.c#L1618">1618</a> <b><i> *  "If any field within the CIPSO options, such as the DOI identifier, is not</i></b>
<a name="L1619" href="source/net/ipv4/cipso_ipv4.c#L1619">1619</a> <b><i> *   recognized the IP datagram is discarded and an ICMP 'parameter problem'</i></b>
<a name="L1620" href="source/net/ipv4/cipso_ipv4.c#L1620">1620</a> <b><i> *   (type 12) is generated and returned.  The ICMP code field is set to 'bad</i></b>
<a name="L1621" href="source/net/ipv4/cipso_ipv4.c#L1621">1621</a> <b><i> *   parameter' (code 0) and the pointer is set to the start of the CIPSO field</i></b>
<a name="L1622" href="source/net/ipv4/cipso_ipv4.c#L1622">1622</a> <b><i> *   that is unrecognized."</i></b>
<a name="L1623" href="source/net/ipv4/cipso_ipv4.c#L1623">1623</a> <b><i> *</i></b>
<a name="L1624" href="source/net/ipv4/cipso_ipv4.c#L1624">1624</a> <b><i> */</i></b>
<a name="L1625" href="source/net/ipv4/cipso_ipv4.c#L1625">1625</a> int <a href="ident?i=cipso_v4_validate">cipso_v4_validate</a>(const struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, unsigned char **<a href="ident?i=option">option</a>)
<a name="L1626" href="source/net/ipv4/cipso_ipv4.c#L1626">1626</a> {
<a name="L1627" href="source/net/ipv4/cipso_ipv4.c#L1627">1627</a>         unsigned char *opt = *<a href="ident?i=option">option</a>;
<a name="L1628" href="source/net/ipv4/cipso_ipv4.c#L1628">1628</a>         unsigned char *<a href="ident?i=tag">tag</a>;
<a name="L1629" href="source/net/ipv4/cipso_ipv4.c#L1629">1629</a>         unsigned char opt_iter;
<a name="L1630" href="source/net/ipv4/cipso_ipv4.c#L1630">1630</a>         unsigned char err_offset = 0;
<a name="L1631" href="source/net/ipv4/cipso_ipv4.c#L1631">1631</a>         <a href="ident?i=u8">u8</a> opt_len;
<a name="L1632" href="source/net/ipv4/cipso_ipv4.c#L1632">1632</a>         <a href="ident?i=u8">u8</a> tag_len;
<a name="L1633" href="source/net/ipv4/cipso_ipv4.c#L1633">1633</a>         struct <a href="ident?i=cipso_v4_doi">cipso_v4_doi</a> *doi_def = <a href="ident?i=NULL">NULL</a>;
<a name="L1634" href="source/net/ipv4/cipso_ipv4.c#L1634">1634</a>         <a href="ident?i=u32">u32</a> tag_iter;
<a name="L1635" href="source/net/ipv4/cipso_ipv4.c#L1635">1635</a> 
<a name="L1636" href="source/net/ipv4/cipso_ipv4.c#L1636">1636</a>         <b><i>/* caller already checks for length values that are too large */</i></b>
<a name="L1637" href="source/net/ipv4/cipso_ipv4.c#L1637">1637</a>         opt_len = opt[1];
<a name="L1638" href="source/net/ipv4/cipso_ipv4.c#L1638">1638</a>         if (opt_len &lt; 8) {
<a name="L1639" href="source/net/ipv4/cipso_ipv4.c#L1639">1639</a>                 err_offset = 1;
<a name="L1640" href="source/net/ipv4/cipso_ipv4.c#L1640">1640</a>                 goto validate_return;
<a name="L1641" href="source/net/ipv4/cipso_ipv4.c#L1641">1641</a>         }
<a name="L1642" href="source/net/ipv4/cipso_ipv4.c#L1642">1642</a> 
<a name="L1643" href="source/net/ipv4/cipso_ipv4.c#L1643">1643</a>         <a href="ident?i=rcu_read_lock">rcu_read_lock</a>();
<a name="L1644" href="source/net/ipv4/cipso_ipv4.c#L1644">1644</a>         doi_def = <a href="ident?i=cipso_v4_doi_search">cipso_v4_doi_search</a>(<a href="ident?i=get_unaligned_be32">get_unaligned_be32</a>(&amp;opt[2]));
<a name="L1645" href="source/net/ipv4/cipso_ipv4.c#L1645">1645</a>         if (!doi_def) {
<a name="L1646" href="source/net/ipv4/cipso_ipv4.c#L1646">1646</a>                 err_offset = 2;
<a name="L1647" href="source/net/ipv4/cipso_ipv4.c#L1647">1647</a>                 goto validate_return_locked;
<a name="L1648" href="source/net/ipv4/cipso_ipv4.c#L1648">1648</a>         }
<a name="L1649" href="source/net/ipv4/cipso_ipv4.c#L1649">1649</a> 
<a name="L1650" href="source/net/ipv4/cipso_ipv4.c#L1650">1650</a>         opt_iter = <a href="ident?i=CIPSO_V4_HDR_LEN">CIPSO_V4_HDR_LEN</a>;
<a name="L1651" href="source/net/ipv4/cipso_ipv4.c#L1651">1651</a>         <a href="ident?i=tag">tag</a> = opt + opt_iter;
<a name="L1652" href="source/net/ipv4/cipso_ipv4.c#L1652">1652</a>         while (opt_iter &lt; opt_len) {
<a name="L1653" href="source/net/ipv4/cipso_ipv4.c#L1653">1653</a>                 for (tag_iter = 0; doi_def-&gt;<a href="ident?i=tags">tags</a>[tag_iter] != <a href="ident?i=tag">tag</a>[0];)
<a name="L1654" href="source/net/ipv4/cipso_ipv4.c#L1654">1654</a>                         if (doi_def-&gt;<a href="ident?i=tags">tags</a>[tag_iter] == <a href="ident?i=CIPSO_V4_TAG_INVALID">CIPSO_V4_TAG_INVALID</a> ||
<a name="L1655" href="source/net/ipv4/cipso_ipv4.c#L1655">1655</a>                             ++tag_iter == <a href="ident?i=CIPSO_V4_TAG_MAXCNT">CIPSO_V4_TAG_MAXCNT</a>) {
<a name="L1656" href="source/net/ipv4/cipso_ipv4.c#L1656">1656</a>                                 err_offset = opt_iter;
<a name="L1657" href="source/net/ipv4/cipso_ipv4.c#L1657">1657</a>                                 goto validate_return_locked;
<a name="L1658" href="source/net/ipv4/cipso_ipv4.c#L1658">1658</a>                         }
<a name="L1659" href="source/net/ipv4/cipso_ipv4.c#L1659">1659</a> 
<a name="L1660" href="source/net/ipv4/cipso_ipv4.c#L1660">1660</a>                 tag_len = <a href="ident?i=tag">tag</a>[1];
<a name="L1661" href="source/net/ipv4/cipso_ipv4.c#L1661">1661</a>                 if (tag_len &gt; (opt_len - opt_iter)) {
<a name="L1662" href="source/net/ipv4/cipso_ipv4.c#L1662">1662</a>                         err_offset = opt_iter + 1;
<a name="L1663" href="source/net/ipv4/cipso_ipv4.c#L1663">1663</a>                         goto validate_return_locked;
<a name="L1664" href="source/net/ipv4/cipso_ipv4.c#L1664">1664</a>                 }
<a name="L1665" href="source/net/ipv4/cipso_ipv4.c#L1665">1665</a> 
<a name="L1666" href="source/net/ipv4/cipso_ipv4.c#L1666">1666</a>                 switch (<a href="ident?i=tag">tag</a>[0]) {
<a name="L1667" href="source/net/ipv4/cipso_ipv4.c#L1667">1667</a>                 case <a href="ident?i=CIPSO_V4_TAG_RBITMAP">CIPSO_V4_TAG_RBITMAP</a>:
<a name="L1668" href="source/net/ipv4/cipso_ipv4.c#L1668">1668</a>                         if (tag_len &lt; <a href="ident?i=CIPSO_V4_TAG_RBM_BLEN">CIPSO_V4_TAG_RBM_BLEN</a>) {
<a name="L1669" href="source/net/ipv4/cipso_ipv4.c#L1669">1669</a>                                 err_offset = opt_iter + 1;
<a name="L1670" href="source/net/ipv4/cipso_ipv4.c#L1670">1670</a>                                 goto validate_return_locked;
<a name="L1671" href="source/net/ipv4/cipso_ipv4.c#L1671">1671</a>                         }
<a name="L1672" href="source/net/ipv4/cipso_ipv4.c#L1672">1672</a> 
<a name="L1673" href="source/net/ipv4/cipso_ipv4.c#L1673">1673</a>                         <b><i>/* We are already going to do all the verification</i></b>
<a name="L1674" href="source/net/ipv4/cipso_ipv4.c#L1674">1674</a> <b><i>                         * necessary at the socket layer so from our point of</i></b>
<a name="L1675" href="source/net/ipv4/cipso_ipv4.c#L1675">1675</a> <b><i>                         * view it is safe to turn these checks off (and less</i></b>
<a name="L1676" href="source/net/ipv4/cipso_ipv4.c#L1676">1676</a> <b><i>                         * work), however, the CIPSO draft says we should do</i></b>
<a name="L1677" href="source/net/ipv4/cipso_ipv4.c#L1677">1677</a> <b><i>                         * all the CIPSO validations here but it doesn't</i></b>
<a name="L1678" href="source/net/ipv4/cipso_ipv4.c#L1678">1678</a> <b><i>                         * really specify _exactly_ what we need to validate</i></b>
<a name="L1679" href="source/net/ipv4/cipso_ipv4.c#L1679">1679</a> <b><i>                         * ... so, just make it a sysctl tunable. */</i></b>
<a name="L1680" href="source/net/ipv4/cipso_ipv4.c#L1680">1680</a>                         if (<a href="ident?i=cipso_v4_rbm_strictvalid">cipso_v4_rbm_strictvalid</a>) {
<a name="L1681" href="source/net/ipv4/cipso_ipv4.c#L1681">1681</a>                                 if (<a href="ident?i=cipso_v4_map_lvl_valid">cipso_v4_map_lvl_valid</a>(doi_def,
<a name="L1682" href="source/net/ipv4/cipso_ipv4.c#L1682">1682</a>                                                            <a href="ident?i=tag">tag</a>[3]) &lt; 0) {
<a name="L1683" href="source/net/ipv4/cipso_ipv4.c#L1683">1683</a>                                         err_offset = opt_iter + 3;
<a name="L1684" href="source/net/ipv4/cipso_ipv4.c#L1684">1684</a>                                         goto validate_return_locked;
<a name="L1685" href="source/net/ipv4/cipso_ipv4.c#L1685">1685</a>                                 }
<a name="L1686" href="source/net/ipv4/cipso_ipv4.c#L1686">1686</a>                                 if (tag_len &gt; <a href="ident?i=CIPSO_V4_TAG_RBM_BLEN">CIPSO_V4_TAG_RBM_BLEN</a> &amp;&amp;
<a name="L1687" href="source/net/ipv4/cipso_ipv4.c#L1687">1687</a>                                     <a href="ident?i=cipso_v4_map_cat_rbm_valid">cipso_v4_map_cat_rbm_valid</a>(doi_def,
<a name="L1688" href="source/net/ipv4/cipso_ipv4.c#L1688">1688</a>                                                             &amp;<a href="ident?i=tag">tag</a>[4],
<a name="L1689" href="source/net/ipv4/cipso_ipv4.c#L1689">1689</a>                                                             tag_len - 4) &lt; 0) {
<a name="L1690" href="source/net/ipv4/cipso_ipv4.c#L1690">1690</a>                                         err_offset = opt_iter + 4;
<a name="L1691" href="source/net/ipv4/cipso_ipv4.c#L1691">1691</a>                                         goto validate_return_locked;
<a name="L1692" href="source/net/ipv4/cipso_ipv4.c#L1692">1692</a>                                 }
<a name="L1693" href="source/net/ipv4/cipso_ipv4.c#L1693">1693</a>                         }
<a name="L1694" href="source/net/ipv4/cipso_ipv4.c#L1694">1694</a>                         break;
<a name="L1695" href="source/net/ipv4/cipso_ipv4.c#L1695">1695</a>                 case <a href="ident?i=CIPSO_V4_TAG_ENUM">CIPSO_V4_TAG_ENUM</a>:
<a name="L1696" href="source/net/ipv4/cipso_ipv4.c#L1696">1696</a>                         if (tag_len &lt; <a href="ident?i=CIPSO_V4_TAG_ENUM_BLEN">CIPSO_V4_TAG_ENUM_BLEN</a>) {
<a name="L1697" href="source/net/ipv4/cipso_ipv4.c#L1697">1697</a>                                 err_offset = opt_iter + 1;
<a name="L1698" href="source/net/ipv4/cipso_ipv4.c#L1698">1698</a>                                 goto validate_return_locked;
<a name="L1699" href="source/net/ipv4/cipso_ipv4.c#L1699">1699</a>                         }
<a name="L1700" href="source/net/ipv4/cipso_ipv4.c#L1700">1700</a> 
<a name="L1701" href="source/net/ipv4/cipso_ipv4.c#L1701">1701</a>                         if (<a href="ident?i=cipso_v4_map_lvl_valid">cipso_v4_map_lvl_valid</a>(doi_def,
<a name="L1702" href="source/net/ipv4/cipso_ipv4.c#L1702">1702</a>                                                    <a href="ident?i=tag">tag</a>[3]) &lt; 0) {
<a name="L1703" href="source/net/ipv4/cipso_ipv4.c#L1703">1703</a>                                 err_offset = opt_iter + 3;
<a name="L1704" href="source/net/ipv4/cipso_ipv4.c#L1704">1704</a>                                 goto validate_return_locked;
<a name="L1705" href="source/net/ipv4/cipso_ipv4.c#L1705">1705</a>                         }
<a name="L1706" href="source/net/ipv4/cipso_ipv4.c#L1706">1706</a>                         if (tag_len &gt; <a href="ident?i=CIPSO_V4_TAG_ENUM_BLEN">CIPSO_V4_TAG_ENUM_BLEN</a> &amp;&amp;
<a name="L1707" href="source/net/ipv4/cipso_ipv4.c#L1707">1707</a>                             <a href="ident?i=cipso_v4_map_cat_enum_valid">cipso_v4_map_cat_enum_valid</a>(doi_def,
<a name="L1708" href="source/net/ipv4/cipso_ipv4.c#L1708">1708</a>                                                         &amp;<a href="ident?i=tag">tag</a>[4],
<a name="L1709" href="source/net/ipv4/cipso_ipv4.c#L1709">1709</a>                                                         tag_len - 4) &lt; 0) {
<a name="L1710" href="source/net/ipv4/cipso_ipv4.c#L1710">1710</a>                                 err_offset = opt_iter + 4;
<a name="L1711" href="source/net/ipv4/cipso_ipv4.c#L1711">1711</a>                                 goto validate_return_locked;
<a name="L1712" href="source/net/ipv4/cipso_ipv4.c#L1712">1712</a>                         }
<a name="L1713" href="source/net/ipv4/cipso_ipv4.c#L1713">1713</a>                         break;
<a name="L1714" href="source/net/ipv4/cipso_ipv4.c#L1714">1714</a>                 case <a href="ident?i=CIPSO_V4_TAG_RANGE">CIPSO_V4_TAG_RANGE</a>:
<a name="L1715" href="source/net/ipv4/cipso_ipv4.c#L1715">1715</a>                         if (tag_len &lt; <a href="ident?i=CIPSO_V4_TAG_RNG_BLEN">CIPSO_V4_TAG_RNG_BLEN</a>) {
<a name="L1716" href="source/net/ipv4/cipso_ipv4.c#L1716">1716</a>                                 err_offset = opt_iter + 1;
<a name="L1717" href="source/net/ipv4/cipso_ipv4.c#L1717">1717</a>                                 goto validate_return_locked;
<a name="L1718" href="source/net/ipv4/cipso_ipv4.c#L1718">1718</a>                         }
<a name="L1719" href="source/net/ipv4/cipso_ipv4.c#L1719">1719</a> 
<a name="L1720" href="source/net/ipv4/cipso_ipv4.c#L1720">1720</a>                         if (<a href="ident?i=cipso_v4_map_lvl_valid">cipso_v4_map_lvl_valid</a>(doi_def,
<a name="L1721" href="source/net/ipv4/cipso_ipv4.c#L1721">1721</a>                                                    <a href="ident?i=tag">tag</a>[3]) &lt; 0) {
<a name="L1722" href="source/net/ipv4/cipso_ipv4.c#L1722">1722</a>                                 err_offset = opt_iter + 3;
<a name="L1723" href="source/net/ipv4/cipso_ipv4.c#L1723">1723</a>                                 goto validate_return_locked;
<a name="L1724" href="source/net/ipv4/cipso_ipv4.c#L1724">1724</a>                         }
<a name="L1725" href="source/net/ipv4/cipso_ipv4.c#L1725">1725</a>                         if (tag_len &gt; <a href="ident?i=CIPSO_V4_TAG_RNG_BLEN">CIPSO_V4_TAG_RNG_BLEN</a> &amp;&amp;
<a name="L1726" href="source/net/ipv4/cipso_ipv4.c#L1726">1726</a>                             <a href="ident?i=cipso_v4_map_cat_rng_valid">cipso_v4_map_cat_rng_valid</a>(doi_def,
<a name="L1727" href="source/net/ipv4/cipso_ipv4.c#L1727">1727</a>                                                        &amp;<a href="ident?i=tag">tag</a>[4],
<a name="L1728" href="source/net/ipv4/cipso_ipv4.c#L1728">1728</a>                                                        tag_len - 4) &lt; 0) {
<a name="L1729" href="source/net/ipv4/cipso_ipv4.c#L1729">1729</a>                                 err_offset = opt_iter + 4;
<a name="L1730" href="source/net/ipv4/cipso_ipv4.c#L1730">1730</a>                                 goto validate_return_locked;
<a name="L1731" href="source/net/ipv4/cipso_ipv4.c#L1731">1731</a>                         }
<a name="L1732" href="source/net/ipv4/cipso_ipv4.c#L1732">1732</a>                         break;
<a name="L1733" href="source/net/ipv4/cipso_ipv4.c#L1733">1733</a>                 case <a href="ident?i=CIPSO_V4_TAG_LOCAL">CIPSO_V4_TAG_LOCAL</a>:
<a name="L1734" href="source/net/ipv4/cipso_ipv4.c#L1734">1734</a>                         <b><i>/* This is a non-standard tag that we only allow for</i></b>
<a name="L1735" href="source/net/ipv4/cipso_ipv4.c#L1735">1735</a> <b><i>                         * local connections, so if the incoming interface is</i></b>
<a name="L1736" href="source/net/ipv4/cipso_ipv4.c#L1736">1736</a> <b><i>                         * not the loopback device drop the packet. Further,</i></b>
<a name="L1737" href="source/net/ipv4/cipso_ipv4.c#L1737">1737</a> <b><i>                         * there is no legitimate reason for setting this from</i></b>
<a name="L1738" href="source/net/ipv4/cipso_ipv4.c#L1738">1738</a> <b><i>                         * userspace so reject it if skb is NULL. */</i></b>
<a name="L1739" href="source/net/ipv4/cipso_ipv4.c#L1739">1739</a>                         if (!<a href="ident?i=skb">skb</a> || !(<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=IFF_LOOPBACK">IFF_LOOPBACK</a>)) {
<a name="L1740" href="source/net/ipv4/cipso_ipv4.c#L1740">1740</a>                                 err_offset = opt_iter;
<a name="L1741" href="source/net/ipv4/cipso_ipv4.c#L1741">1741</a>                                 goto validate_return_locked;
<a name="L1742" href="source/net/ipv4/cipso_ipv4.c#L1742">1742</a>                         }
<a name="L1743" href="source/net/ipv4/cipso_ipv4.c#L1743">1743</a>                         if (tag_len != <a href="ident?i=CIPSO_V4_TAG_LOC_BLEN">CIPSO_V4_TAG_LOC_BLEN</a>) {
<a name="L1744" href="source/net/ipv4/cipso_ipv4.c#L1744">1744</a>                                 err_offset = opt_iter + 1;
<a name="L1745" href="source/net/ipv4/cipso_ipv4.c#L1745">1745</a>                                 goto validate_return_locked;
<a name="L1746" href="source/net/ipv4/cipso_ipv4.c#L1746">1746</a>                         }
<a name="L1747" href="source/net/ipv4/cipso_ipv4.c#L1747">1747</a>                         break;
<a name="L1748" href="source/net/ipv4/cipso_ipv4.c#L1748">1748</a>                 default:
<a name="L1749" href="source/net/ipv4/cipso_ipv4.c#L1749">1749</a>                         err_offset = opt_iter;
<a name="L1750" href="source/net/ipv4/cipso_ipv4.c#L1750">1750</a>                         goto validate_return_locked;
<a name="L1751" href="source/net/ipv4/cipso_ipv4.c#L1751">1751</a>                 }
<a name="L1752" href="source/net/ipv4/cipso_ipv4.c#L1752">1752</a> 
<a name="L1753" href="source/net/ipv4/cipso_ipv4.c#L1753">1753</a>                 <a href="ident?i=tag">tag</a> += tag_len;
<a name="L1754" href="source/net/ipv4/cipso_ipv4.c#L1754">1754</a>                 opt_iter += tag_len;
<a name="L1755" href="source/net/ipv4/cipso_ipv4.c#L1755">1755</a>         }
<a name="L1756" href="source/net/ipv4/cipso_ipv4.c#L1756">1756</a> 
<a name="L1757" href="source/net/ipv4/cipso_ipv4.c#L1757">1757</a> validate_return_locked:
<a name="L1758" href="source/net/ipv4/cipso_ipv4.c#L1758">1758</a>         <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L1759" href="source/net/ipv4/cipso_ipv4.c#L1759">1759</a> validate_return:
<a name="L1760" href="source/net/ipv4/cipso_ipv4.c#L1760">1760</a>         *<a href="ident?i=option">option</a> = opt + err_offset;
<a name="L1761" href="source/net/ipv4/cipso_ipv4.c#L1761">1761</a>         return err_offset;
<a name="L1762" href="source/net/ipv4/cipso_ipv4.c#L1762">1762</a> }
<a name="L1763" href="source/net/ipv4/cipso_ipv4.c#L1763">1763</a> 
<a name="L1764" href="source/net/ipv4/cipso_ipv4.c#L1764">1764</a> <b><i>/**</i></b>
<a name="L1765" href="source/net/ipv4/cipso_ipv4.c#L1765">1765</a> <b><i> * cipso_v4_error - Send the correct response for a bad packet</i></b>
<a name="L1766" href="source/net/ipv4/cipso_ipv4.c#L1766">1766</a> <b><i> * @skb: the packet</i></b>
<a name="L1767" href="source/net/ipv4/cipso_ipv4.c#L1767">1767</a> <b><i> * @error: the error code</i></b>
<a name="L1768" href="source/net/ipv4/cipso_ipv4.c#L1768">1768</a> <b><i> * @gateway: CIPSO gateway flag</i></b>
<a name="L1769" href="source/net/ipv4/cipso_ipv4.c#L1769">1769</a> <b><i> *</i></b>
<a name="L1770" href="source/net/ipv4/cipso_ipv4.c#L1770">1770</a> <b><i> * Description:</i></b>
<a name="L1771" href="source/net/ipv4/cipso_ipv4.c#L1771">1771</a> <b><i> * Based on the error code given in @error, send an ICMP error message back to</i></b>
<a name="L1772" href="source/net/ipv4/cipso_ipv4.c#L1772">1772</a> <b><i> * the originating host.  From the IETF draft ...</i></b>
<a name="L1773" href="source/net/ipv4/cipso_ipv4.c#L1773">1773</a> <b><i> *</i></b>
<a name="L1774" href="source/net/ipv4/cipso_ipv4.c#L1774">1774</a> <b><i> *  "If the contents of the CIPSO [option] are valid but the security label is</i></b>
<a name="L1775" href="source/net/ipv4/cipso_ipv4.c#L1775">1775</a> <b><i> *   outside of the configured host or port label range, the datagram is</i></b>
<a name="L1776" href="source/net/ipv4/cipso_ipv4.c#L1776">1776</a> <b><i> *   discarded and an ICMP 'destination unreachable' (type 3) is generated and</i></b>
<a name="L1777" href="source/net/ipv4/cipso_ipv4.c#L1777">1777</a> <b><i> *   returned.  The code field of the ICMP is set to 'communication with</i></b>
<a name="L1778" href="source/net/ipv4/cipso_ipv4.c#L1778">1778</a> <b><i> *   destination network administratively prohibited' (code 9) or to</i></b>
<a name="L1779" href="source/net/ipv4/cipso_ipv4.c#L1779">1779</a> <b><i> *   'communication with destination host administratively prohibited'</i></b>
<a name="L1780" href="source/net/ipv4/cipso_ipv4.c#L1780">1780</a> <b><i> *   (code 10).  The value of the code is dependent on whether the originator</i></b>
<a name="L1781" href="source/net/ipv4/cipso_ipv4.c#L1781">1781</a> <b><i> *   of the ICMP message is acting as a CIPSO host or a CIPSO gateway.  The</i></b>
<a name="L1782" href="source/net/ipv4/cipso_ipv4.c#L1782">1782</a> <b><i> *   recipient of the ICMP message MUST be able to handle either value.  The</i></b>
<a name="L1783" href="source/net/ipv4/cipso_ipv4.c#L1783">1783</a> <b><i> *   same procedure is performed if a CIPSO [option] can not be added to an</i></b>
<a name="L1784" href="source/net/ipv4/cipso_ipv4.c#L1784">1784</a> <b><i> *   IP packet because it is too large to fit in the IP options area."</i></b>
<a name="L1785" href="source/net/ipv4/cipso_ipv4.c#L1785">1785</a> <b><i> *</i></b>
<a name="L1786" href="source/net/ipv4/cipso_ipv4.c#L1786">1786</a> <b><i> *  "If the error is triggered by receipt of an ICMP message, the message is</i></b>
<a name="L1787" href="source/net/ipv4/cipso_ipv4.c#L1787">1787</a> <b><i> *   discarded and no response is permitted (consistent with general ICMP</i></b>
<a name="L1788" href="source/net/ipv4/cipso_ipv4.c#L1788">1788</a> <b><i> *   processing rules)."</i></b>
<a name="L1789" href="source/net/ipv4/cipso_ipv4.c#L1789">1789</a> <b><i> *</i></b>
<a name="L1790" href="source/net/ipv4/cipso_ipv4.c#L1790">1790</a> <b><i> */</i></b>
<a name="L1791" href="source/net/ipv4/cipso_ipv4.c#L1791">1791</a> void <a href="ident?i=cipso_v4_error">cipso_v4_error</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, int <a href="ident?i=error">error</a>, <a href="ident?i=u32">u32</a> gateway)
<a name="L1792" href="source/net/ipv4/cipso_ipv4.c#L1792">1792</a> {
<a name="L1793" href="source/net/ipv4/cipso_ipv4.c#L1793">1793</a>         if (<a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=protocol">protocol</a> == <a href="ident?i=IPPROTO_ICMP">IPPROTO_ICMP</a> || <a href="ident?i=error">error</a> != -<a href="ident?i=EACCES">EACCES</a>)
<a name="L1794" href="source/net/ipv4/cipso_ipv4.c#L1794">1794</a>                 return;
<a name="L1795" href="source/net/ipv4/cipso_ipv4.c#L1795">1795</a> 
<a name="L1796" href="source/net/ipv4/cipso_ipv4.c#L1796">1796</a>         if (gateway)
<a name="L1797" href="source/net/ipv4/cipso_ipv4.c#L1797">1797</a>                 <a href="ident?i=icmp_send">icmp_send</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=ICMP_DEST_UNREACH">ICMP_DEST_UNREACH</a>, <a href="ident?i=ICMP_NET_ANO">ICMP_NET_ANO</a>, 0);
<a name="L1798" href="source/net/ipv4/cipso_ipv4.c#L1798">1798</a>         else
<a name="L1799" href="source/net/ipv4/cipso_ipv4.c#L1799">1799</a>                 <a href="ident?i=icmp_send">icmp_send</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=ICMP_DEST_UNREACH">ICMP_DEST_UNREACH</a>, <a href="ident?i=ICMP_HOST_ANO">ICMP_HOST_ANO</a>, 0);
<a name="L1800" href="source/net/ipv4/cipso_ipv4.c#L1800">1800</a> }
<a name="L1801" href="source/net/ipv4/cipso_ipv4.c#L1801">1801</a> 
<a name="L1802" href="source/net/ipv4/cipso_ipv4.c#L1802">1802</a> <b><i>/**</i></b>
<a name="L1803" href="source/net/ipv4/cipso_ipv4.c#L1803">1803</a> <b><i> * cipso_v4_genopt - Generate a CIPSO option</i></b>
<a name="L1804" href="source/net/ipv4/cipso_ipv4.c#L1804">1804</a> <b><i> * @buf: the option buffer</i></b>
<a name="L1805" href="source/net/ipv4/cipso_ipv4.c#L1805">1805</a> <b><i> * @buf_len: the size of opt_buf</i></b>
<a name="L1806" href="source/net/ipv4/cipso_ipv4.c#L1806">1806</a> <b><i> * @doi_def: the CIPSO DOI to use</i></b>
<a name="L1807" href="source/net/ipv4/cipso_ipv4.c#L1807">1807</a> <b><i> * @secattr: the security attributes</i></b>
<a name="L1808" href="source/net/ipv4/cipso_ipv4.c#L1808">1808</a> <b><i> *</i></b>
<a name="L1809" href="source/net/ipv4/cipso_ipv4.c#L1809">1809</a> <b><i> * Description:</i></b>
<a name="L1810" href="source/net/ipv4/cipso_ipv4.c#L1810">1810</a> <b><i> * Generate a CIPSO option using the DOI definition and security attributes</i></b>
<a name="L1811" href="source/net/ipv4/cipso_ipv4.c#L1811">1811</a> <b><i> * passed to the function.  Returns the length of the option on success and</i></b>
<a name="L1812" href="source/net/ipv4/cipso_ipv4.c#L1812">1812</a> <b><i> * negative values on failure.</i></b>
<a name="L1813" href="source/net/ipv4/cipso_ipv4.c#L1813">1813</a> <b><i> *</i></b>
<a name="L1814" href="source/net/ipv4/cipso_ipv4.c#L1814">1814</a> <b><i> */</i></b>
<a name="L1815" href="source/net/ipv4/cipso_ipv4.c#L1815">1815</a> static int <a href="ident?i=cipso_v4_genopt">cipso_v4_genopt</a>(unsigned char *<a href="ident?i=buf">buf</a>, <a href="ident?i=u32">u32</a> <a href="ident?i=buf_len">buf_len</a>,
<a name="L1816" href="source/net/ipv4/cipso_ipv4.c#L1816">1816</a>                            const struct <a href="ident?i=cipso_v4_doi">cipso_v4_doi</a> *doi_def,
<a name="L1817" href="source/net/ipv4/cipso_ipv4.c#L1817">1817</a>                            const struct <a href="ident?i=netlbl_lsm_secattr">netlbl_lsm_secattr</a> *secattr)
<a name="L1818" href="source/net/ipv4/cipso_ipv4.c#L1818">1818</a> {
<a name="L1819" href="source/net/ipv4/cipso_ipv4.c#L1819">1819</a>         int ret_val;
<a name="L1820" href="source/net/ipv4/cipso_ipv4.c#L1820">1820</a>         <a href="ident?i=u32">u32</a> iter;
<a name="L1821" href="source/net/ipv4/cipso_ipv4.c#L1821">1821</a> 
<a name="L1822" href="source/net/ipv4/cipso_ipv4.c#L1822">1822</a>         if (<a href="ident?i=buf_len">buf_len</a> &lt;= <a href="ident?i=CIPSO_V4_HDR_LEN">CIPSO_V4_HDR_LEN</a>)
<a name="L1823" href="source/net/ipv4/cipso_ipv4.c#L1823">1823</a>                 return -<a href="ident?i=ENOSPC">ENOSPC</a>;
<a name="L1824" href="source/net/ipv4/cipso_ipv4.c#L1824">1824</a> 
<a name="L1825" href="source/net/ipv4/cipso_ipv4.c#L1825">1825</a>         <b><i>/* XXX - This code assumes only one tag per CIPSO option which isn't</i></b>
<a name="L1826" href="source/net/ipv4/cipso_ipv4.c#L1826">1826</a> <b><i>         * really a good assumption to make but since we only support the MAC</i></b>
<a name="L1827" href="source/net/ipv4/cipso_ipv4.c#L1827">1827</a> <b><i>         * tags right now it is a safe assumption. */</i></b>
<a name="L1828" href="source/net/ipv4/cipso_ipv4.c#L1828">1828</a>         iter = 0;
<a name="L1829" href="source/net/ipv4/cipso_ipv4.c#L1829">1829</a>         do {
<a name="L1830" href="source/net/ipv4/cipso_ipv4.c#L1830">1830</a>                 <a href="ident?i=memset">memset</a>(<a href="ident?i=buf">buf</a>, 0, <a href="ident?i=buf_len">buf_len</a>);
<a name="L1831" href="source/net/ipv4/cipso_ipv4.c#L1831">1831</a>                 switch (doi_def-&gt;<a href="ident?i=tags">tags</a>[iter]) {
<a name="L1832" href="source/net/ipv4/cipso_ipv4.c#L1832">1832</a>                 case <a href="ident?i=CIPSO_V4_TAG_RBITMAP">CIPSO_V4_TAG_RBITMAP</a>:
<a name="L1833" href="source/net/ipv4/cipso_ipv4.c#L1833">1833</a>                         ret_val = <a href="ident?i=cipso_v4_gentag_rbm">cipso_v4_gentag_rbm</a>(doi_def,
<a name="L1834" href="source/net/ipv4/cipso_ipv4.c#L1834">1834</a>                                                    secattr,
<a name="L1835" href="source/net/ipv4/cipso_ipv4.c#L1835">1835</a>                                                    &amp;<a href="ident?i=buf">buf</a>[<a href="ident?i=CIPSO_V4_HDR_LEN">CIPSO_V4_HDR_LEN</a>],
<a name="L1836" href="source/net/ipv4/cipso_ipv4.c#L1836">1836</a>                                                    <a href="ident?i=buf_len">buf_len</a> - <a href="ident?i=CIPSO_V4_HDR_LEN">CIPSO_V4_HDR_LEN</a>);
<a name="L1837" href="source/net/ipv4/cipso_ipv4.c#L1837">1837</a>                         break;
<a name="L1838" href="source/net/ipv4/cipso_ipv4.c#L1838">1838</a>                 case <a href="ident?i=CIPSO_V4_TAG_ENUM">CIPSO_V4_TAG_ENUM</a>:
<a name="L1839" href="source/net/ipv4/cipso_ipv4.c#L1839">1839</a>                         ret_val = <a href="ident?i=cipso_v4_gentag_enum">cipso_v4_gentag_enum</a>(doi_def,
<a name="L1840" href="source/net/ipv4/cipso_ipv4.c#L1840">1840</a>                                                    secattr,
<a name="L1841" href="source/net/ipv4/cipso_ipv4.c#L1841">1841</a>                                                    &amp;<a href="ident?i=buf">buf</a>[<a href="ident?i=CIPSO_V4_HDR_LEN">CIPSO_V4_HDR_LEN</a>],
<a name="L1842" href="source/net/ipv4/cipso_ipv4.c#L1842">1842</a>                                                    <a href="ident?i=buf_len">buf_len</a> - <a href="ident?i=CIPSO_V4_HDR_LEN">CIPSO_V4_HDR_LEN</a>);
<a name="L1843" href="source/net/ipv4/cipso_ipv4.c#L1843">1843</a>                         break;
<a name="L1844" href="source/net/ipv4/cipso_ipv4.c#L1844">1844</a>                 case <a href="ident?i=CIPSO_V4_TAG_RANGE">CIPSO_V4_TAG_RANGE</a>:
<a name="L1845" href="source/net/ipv4/cipso_ipv4.c#L1845">1845</a>                         ret_val = <a href="ident?i=cipso_v4_gentag_rng">cipso_v4_gentag_rng</a>(doi_def,
<a name="L1846" href="source/net/ipv4/cipso_ipv4.c#L1846">1846</a>                                                    secattr,
<a name="L1847" href="source/net/ipv4/cipso_ipv4.c#L1847">1847</a>                                                    &amp;<a href="ident?i=buf">buf</a>[<a href="ident?i=CIPSO_V4_HDR_LEN">CIPSO_V4_HDR_LEN</a>],
<a name="L1848" href="source/net/ipv4/cipso_ipv4.c#L1848">1848</a>                                                    <a href="ident?i=buf_len">buf_len</a> - <a href="ident?i=CIPSO_V4_HDR_LEN">CIPSO_V4_HDR_LEN</a>);
<a name="L1849" href="source/net/ipv4/cipso_ipv4.c#L1849">1849</a>                         break;
<a name="L1850" href="source/net/ipv4/cipso_ipv4.c#L1850">1850</a>                 case <a href="ident?i=CIPSO_V4_TAG_LOCAL">CIPSO_V4_TAG_LOCAL</a>:
<a name="L1851" href="source/net/ipv4/cipso_ipv4.c#L1851">1851</a>                         ret_val = <a href="ident?i=cipso_v4_gentag_loc">cipso_v4_gentag_loc</a>(doi_def,
<a name="L1852" href="source/net/ipv4/cipso_ipv4.c#L1852">1852</a>                                                    secattr,
<a name="L1853" href="source/net/ipv4/cipso_ipv4.c#L1853">1853</a>                                                    &amp;<a href="ident?i=buf">buf</a>[<a href="ident?i=CIPSO_V4_HDR_LEN">CIPSO_V4_HDR_LEN</a>],
<a name="L1854" href="source/net/ipv4/cipso_ipv4.c#L1854">1854</a>                                                    <a href="ident?i=buf_len">buf_len</a> - <a href="ident?i=CIPSO_V4_HDR_LEN">CIPSO_V4_HDR_LEN</a>);
<a name="L1855" href="source/net/ipv4/cipso_ipv4.c#L1855">1855</a>                         break;
<a name="L1856" href="source/net/ipv4/cipso_ipv4.c#L1856">1856</a>                 default:
<a name="L1857" href="source/net/ipv4/cipso_ipv4.c#L1857">1857</a>                         return -<a href="ident?i=EPERM">EPERM</a>;
<a name="L1858" href="source/net/ipv4/cipso_ipv4.c#L1858">1858</a>                 }
<a name="L1859" href="source/net/ipv4/cipso_ipv4.c#L1859">1859</a> 
<a name="L1860" href="source/net/ipv4/cipso_ipv4.c#L1860">1860</a>                 iter++;
<a name="L1861" href="source/net/ipv4/cipso_ipv4.c#L1861">1861</a>         } while (ret_val &lt; 0 &amp;&amp;
<a name="L1862" href="source/net/ipv4/cipso_ipv4.c#L1862">1862</a>                  iter &lt; <a href="ident?i=CIPSO_V4_TAG_MAXCNT">CIPSO_V4_TAG_MAXCNT</a> &amp;&amp;
<a name="L1863" href="source/net/ipv4/cipso_ipv4.c#L1863">1863</a>                  doi_def-&gt;<a href="ident?i=tags">tags</a>[iter] != <a href="ident?i=CIPSO_V4_TAG_INVALID">CIPSO_V4_TAG_INVALID</a>);
<a name="L1864" href="source/net/ipv4/cipso_ipv4.c#L1864">1864</a>         if (ret_val &lt; 0)
<a name="L1865" href="source/net/ipv4/cipso_ipv4.c#L1865">1865</a>                 return ret_val;
<a name="L1866" href="source/net/ipv4/cipso_ipv4.c#L1866">1866</a>         <a href="ident?i=cipso_v4_gentag_hdr">cipso_v4_gentag_hdr</a>(doi_def, <a href="ident?i=buf">buf</a>, ret_val);
<a name="L1867" href="source/net/ipv4/cipso_ipv4.c#L1867">1867</a>         return <a href="ident?i=CIPSO_V4_HDR_LEN">CIPSO_V4_HDR_LEN</a> + ret_val;
<a name="L1868" href="source/net/ipv4/cipso_ipv4.c#L1868">1868</a> }
<a name="L1869" href="source/net/ipv4/cipso_ipv4.c#L1869">1869</a> 
<a name="L1870" href="source/net/ipv4/cipso_ipv4.c#L1870">1870</a> <b><i>/**</i></b>
<a name="L1871" href="source/net/ipv4/cipso_ipv4.c#L1871">1871</a> <b><i> * cipso_v4_sock_setattr - Add a CIPSO option to a socket</i></b>
<a name="L1872" href="source/net/ipv4/cipso_ipv4.c#L1872">1872</a> <b><i> * @sk: the socket</i></b>
<a name="L1873" href="source/net/ipv4/cipso_ipv4.c#L1873">1873</a> <b><i> * @doi_def: the CIPSO DOI to use</i></b>
<a name="L1874" href="source/net/ipv4/cipso_ipv4.c#L1874">1874</a> <b><i> * @secattr: the specific security attributes of the socket</i></b>
<a name="L1875" href="source/net/ipv4/cipso_ipv4.c#L1875">1875</a> <b><i> *</i></b>
<a name="L1876" href="source/net/ipv4/cipso_ipv4.c#L1876">1876</a> <b><i> * Description:</i></b>
<a name="L1877" href="source/net/ipv4/cipso_ipv4.c#L1877">1877</a> <b><i> * Set the CIPSO option on the given socket using the DOI definition and</i></b>
<a name="L1878" href="source/net/ipv4/cipso_ipv4.c#L1878">1878</a> <b><i> * security attributes passed to the function.  This function requires</i></b>
<a name="L1879" href="source/net/ipv4/cipso_ipv4.c#L1879">1879</a> <b><i> * exclusive access to @sk, which means it either needs to be in the</i></b>
<a name="L1880" href="source/net/ipv4/cipso_ipv4.c#L1880">1880</a> <b><i> * process of being created or locked.  Returns zero on success and negative</i></b>
<a name="L1881" href="source/net/ipv4/cipso_ipv4.c#L1881">1881</a> <b><i> * values on failure.</i></b>
<a name="L1882" href="source/net/ipv4/cipso_ipv4.c#L1882">1882</a> <b><i> *</i></b>
<a name="L1883" href="source/net/ipv4/cipso_ipv4.c#L1883">1883</a> <b><i> */</i></b>
<a name="L1884" href="source/net/ipv4/cipso_ipv4.c#L1884">1884</a> int <a href="ident?i=cipso_v4_sock_setattr">cipso_v4_sock_setattr</a>(struct <a href="ident?i=sock">sock</a> *sk,
<a name="L1885" href="source/net/ipv4/cipso_ipv4.c#L1885">1885</a>                           const struct <a href="ident?i=cipso_v4_doi">cipso_v4_doi</a> *doi_def,
<a name="L1886" href="source/net/ipv4/cipso_ipv4.c#L1886">1886</a>                           const struct <a href="ident?i=netlbl_lsm_secattr">netlbl_lsm_secattr</a> *secattr)
<a name="L1887" href="source/net/ipv4/cipso_ipv4.c#L1887">1887</a> {
<a name="L1888" href="source/net/ipv4/cipso_ipv4.c#L1888">1888</a>         int ret_val = -<a href="ident?i=EPERM">EPERM</a>;
<a name="L1889" href="source/net/ipv4/cipso_ipv4.c#L1889">1889</a>         unsigned char *<a href="ident?i=buf">buf</a> = <a href="ident?i=NULL">NULL</a>;
<a name="L1890" href="source/net/ipv4/cipso_ipv4.c#L1890">1890</a>         <a href="ident?i=u32">u32</a> <a href="ident?i=buf_len">buf_len</a>;
<a name="L1891" href="source/net/ipv4/cipso_ipv4.c#L1891">1891</a>         <a href="ident?i=u32">u32</a> opt_len;
<a name="L1892" href="source/net/ipv4/cipso_ipv4.c#L1892">1892</a>         struct <a href="ident?i=ip_options_rcu">ip_options_rcu</a> *<a href="ident?i=old">old</a>, *opt = <a href="ident?i=NULL">NULL</a>;
<a name="L1893" href="source/net/ipv4/cipso_ipv4.c#L1893">1893</a>         struct <a href="ident?i=inet_sock">inet_sock</a> *sk_inet;
<a name="L1894" href="source/net/ipv4/cipso_ipv4.c#L1894">1894</a>         struct <a href="ident?i=inet_connection_sock">inet_connection_sock</a> *sk_conn;
<a name="L1895" href="source/net/ipv4/cipso_ipv4.c#L1895">1895</a> 
<a name="L1896" href="source/net/ipv4/cipso_ipv4.c#L1896">1896</a>         <b><i>/* In the case of sock_create_lite(), the sock-&gt;sk field is not</i></b>
<a name="L1897" href="source/net/ipv4/cipso_ipv4.c#L1897">1897</a> <b><i>         * defined yet but it is not a problem as the only users of these</i></b>
<a name="L1898" href="source/net/ipv4/cipso_ipv4.c#L1898">1898</a> <b><i>         * "lite" PF_INET sockets are functions which do an accept() call</i></b>
<a name="L1899" href="source/net/ipv4/cipso_ipv4.c#L1899">1899</a> <b><i>         * afterwards so we will label the socket as part of the accept(). */</i></b>
<a name="L1900" href="source/net/ipv4/cipso_ipv4.c#L1900">1900</a>         if (!sk)
<a name="L1901" href="source/net/ipv4/cipso_ipv4.c#L1901">1901</a>                 return 0;
<a name="L1902" href="source/net/ipv4/cipso_ipv4.c#L1902">1902</a> 
<a name="L1903" href="source/net/ipv4/cipso_ipv4.c#L1903">1903</a>         <b><i>/* We allocate the maximum CIPSO option size here so we are probably</i></b>
<a name="L1904" href="source/net/ipv4/cipso_ipv4.c#L1904">1904</a> <b><i>         * being a little wasteful, but it makes our life _much_ easier later</i></b>
<a name="L1905" href="source/net/ipv4/cipso_ipv4.c#L1905">1905</a> <b><i>         * on and after all we are only talking about 40 bytes. */</i></b>
<a name="L1906" href="source/net/ipv4/cipso_ipv4.c#L1906">1906</a>         <a href="ident?i=buf_len">buf_len</a> = <a href="ident?i=CIPSO_V4_OPT_LEN_MAX">CIPSO_V4_OPT_LEN_MAX</a>;
<a name="L1907" href="source/net/ipv4/cipso_ipv4.c#L1907">1907</a>         <a href="ident?i=buf">buf</a> = <a href="ident?i=kmalloc">kmalloc</a>(<a href="ident?i=buf_len">buf_len</a>, <a href="ident?i=GFP_ATOMIC">GFP_ATOMIC</a>);
<a name="L1908" href="source/net/ipv4/cipso_ipv4.c#L1908">1908</a>         if (!<a href="ident?i=buf">buf</a>) {
<a name="L1909" href="source/net/ipv4/cipso_ipv4.c#L1909">1909</a>                 ret_val = -<a href="ident?i=ENOMEM">ENOMEM</a>;
<a name="L1910" href="source/net/ipv4/cipso_ipv4.c#L1910">1910</a>                 goto socket_setattr_failure;
<a name="L1911" href="source/net/ipv4/cipso_ipv4.c#L1911">1911</a>         }
<a name="L1912" href="source/net/ipv4/cipso_ipv4.c#L1912">1912</a> 
<a name="L1913" href="source/net/ipv4/cipso_ipv4.c#L1913">1913</a>         ret_val = <a href="ident?i=cipso_v4_genopt">cipso_v4_genopt</a>(<a href="ident?i=buf">buf</a>, <a href="ident?i=buf_len">buf_len</a>, doi_def, secattr);
<a name="L1914" href="source/net/ipv4/cipso_ipv4.c#L1914">1914</a>         if (ret_val &lt; 0)
<a name="L1915" href="source/net/ipv4/cipso_ipv4.c#L1915">1915</a>                 goto socket_setattr_failure;
<a name="L1916" href="source/net/ipv4/cipso_ipv4.c#L1916">1916</a>         <a href="ident?i=buf_len">buf_len</a> = ret_val;
<a name="L1917" href="source/net/ipv4/cipso_ipv4.c#L1917">1917</a> 
<a name="L1918" href="source/net/ipv4/cipso_ipv4.c#L1918">1918</a>         <b><i>/* We can't use ip_options_get() directly because it makes a call to</i></b>
<a name="L1919" href="source/net/ipv4/cipso_ipv4.c#L1919">1919</a> <b><i>         * ip_options_get_alloc() which allocates memory with GFP_KERNEL and</i></b>
<a name="L1920" href="source/net/ipv4/cipso_ipv4.c#L1920">1920</a> <b><i>         * we won't always have CAP_NET_RAW even though we _always_ want to</i></b>
<a name="L1921" href="source/net/ipv4/cipso_ipv4.c#L1921">1921</a> <b><i>         * set the IPOPT_CIPSO option. */</i></b>
<a name="L1922" href="source/net/ipv4/cipso_ipv4.c#L1922">1922</a>         opt_len = (<a href="ident?i=buf_len">buf_len</a> + 3) &amp; ~3;
<a name="L1923" href="source/net/ipv4/cipso_ipv4.c#L1923">1923</a>         opt = <a href="ident?i=kzalloc">kzalloc</a>(sizeof(*opt) + opt_len, <a href="ident?i=GFP_ATOMIC">GFP_ATOMIC</a>);
<a name="L1924" href="source/net/ipv4/cipso_ipv4.c#L1924">1924</a>         if (!opt) {
<a name="L1925" href="source/net/ipv4/cipso_ipv4.c#L1925">1925</a>                 ret_val = -<a href="ident?i=ENOMEM">ENOMEM</a>;
<a name="L1926" href="source/net/ipv4/cipso_ipv4.c#L1926">1926</a>                 goto socket_setattr_failure;
<a name="L1927" href="source/net/ipv4/cipso_ipv4.c#L1927">1927</a>         }
<a name="L1928" href="source/net/ipv4/cipso_ipv4.c#L1928">1928</a>         <a href="ident?i=memcpy">memcpy</a>(opt-&gt;opt.__data, <a href="ident?i=buf">buf</a>, <a href="ident?i=buf_len">buf_len</a>);
<a name="L1929" href="source/net/ipv4/cipso_ipv4.c#L1929">1929</a>         opt-&gt;opt.<a href="ident?i=optlen">optlen</a> = opt_len;
<a name="L1930" href="source/net/ipv4/cipso_ipv4.c#L1930">1930</a>         opt-&gt;opt.cipso = sizeof(struct <a href="ident?i=iphdr">iphdr</a>);
<a name="L1931" href="source/net/ipv4/cipso_ipv4.c#L1931">1931</a>         <a href="ident?i=kfree">kfree</a>(<a href="ident?i=buf">buf</a>);
<a name="L1932" href="source/net/ipv4/cipso_ipv4.c#L1932">1932</a>         <a href="ident?i=buf">buf</a> = <a href="ident?i=NULL">NULL</a>;
<a name="L1933" href="source/net/ipv4/cipso_ipv4.c#L1933">1933</a> 
<a name="L1934" href="source/net/ipv4/cipso_ipv4.c#L1934">1934</a>         sk_inet = <a href="ident?i=inet_sk">inet_sk</a>(sk);
<a name="L1935" href="source/net/ipv4/cipso_ipv4.c#L1935">1935</a> 
<a name="L1936" href="source/net/ipv4/cipso_ipv4.c#L1936">1936</a>         <a href="ident?i=old">old</a> = <a href="ident?i=rcu_dereference_protected">rcu_dereference_protected</a>(sk_inet-&gt;inet_opt, <a href="ident?i=sock_owned_by_user">sock_owned_by_user</a>(sk));
<a name="L1937" href="source/net/ipv4/cipso_ipv4.c#L1937">1937</a>         if (sk_inet-&gt;is_icsk) {
<a name="L1938" href="source/net/ipv4/cipso_ipv4.c#L1938">1938</a>                 sk_conn = <a href="ident?i=inet_csk">inet_csk</a>(sk);
<a name="L1939" href="source/net/ipv4/cipso_ipv4.c#L1939">1939</a>                 if (<a href="ident?i=old">old</a>)
<a name="L1940" href="source/net/ipv4/cipso_ipv4.c#L1940">1940</a>                         sk_conn-&gt;icsk_ext_hdr_len -= <a href="ident?i=old">old</a>-&gt;opt.<a href="ident?i=optlen">optlen</a>;
<a name="L1941" href="source/net/ipv4/cipso_ipv4.c#L1941">1941</a>                 sk_conn-&gt;icsk_ext_hdr_len += opt-&gt;opt.<a href="ident?i=optlen">optlen</a>;
<a name="L1942" href="source/net/ipv4/cipso_ipv4.c#L1942">1942</a>                 sk_conn-&gt;icsk_sync_mss(sk, sk_conn-&gt;icsk_pmtu_cookie);
<a name="L1943" href="source/net/ipv4/cipso_ipv4.c#L1943">1943</a>         }
<a name="L1944" href="source/net/ipv4/cipso_ipv4.c#L1944">1944</a>         <a href="ident?i=rcu_assign_pointer">rcu_assign_pointer</a>(sk_inet-&gt;inet_opt, opt);
<a name="L1945" href="source/net/ipv4/cipso_ipv4.c#L1945">1945</a>         if (<a href="ident?i=old">old</a>)
<a name="L1946" href="source/net/ipv4/cipso_ipv4.c#L1946">1946</a>                 <a href="ident?i=kfree_rcu">kfree_rcu</a>(<a href="ident?i=old">old</a>, rcu);
<a name="L1947" href="source/net/ipv4/cipso_ipv4.c#L1947">1947</a> 
<a name="L1948" href="source/net/ipv4/cipso_ipv4.c#L1948">1948</a>         return 0;
<a name="L1949" href="source/net/ipv4/cipso_ipv4.c#L1949">1949</a> 
<a name="L1950" href="source/net/ipv4/cipso_ipv4.c#L1950">1950</a> socket_setattr_failure:
<a name="L1951" href="source/net/ipv4/cipso_ipv4.c#L1951">1951</a>         <a href="ident?i=kfree">kfree</a>(<a href="ident?i=buf">buf</a>);
<a name="L1952" href="source/net/ipv4/cipso_ipv4.c#L1952">1952</a>         <a href="ident?i=kfree">kfree</a>(opt);
<a name="L1953" href="source/net/ipv4/cipso_ipv4.c#L1953">1953</a>         return ret_val;
<a name="L1954" href="source/net/ipv4/cipso_ipv4.c#L1954">1954</a> }
<a name="L1955" href="source/net/ipv4/cipso_ipv4.c#L1955">1955</a> 
<a name="L1956" href="source/net/ipv4/cipso_ipv4.c#L1956">1956</a> <b><i>/**</i></b>
<a name="L1957" href="source/net/ipv4/cipso_ipv4.c#L1957">1957</a> <b><i> * cipso_v4_req_setattr - Add a CIPSO option to a connection request socket</i></b>
<a name="L1958" href="source/net/ipv4/cipso_ipv4.c#L1958">1958</a> <b><i> * @req: the connection request socket</i></b>
<a name="L1959" href="source/net/ipv4/cipso_ipv4.c#L1959">1959</a> <b><i> * @doi_def: the CIPSO DOI to use</i></b>
<a name="L1960" href="source/net/ipv4/cipso_ipv4.c#L1960">1960</a> <b><i> * @secattr: the specific security attributes of the socket</i></b>
<a name="L1961" href="source/net/ipv4/cipso_ipv4.c#L1961">1961</a> <b><i> *</i></b>
<a name="L1962" href="source/net/ipv4/cipso_ipv4.c#L1962">1962</a> <b><i> * Description:</i></b>
<a name="L1963" href="source/net/ipv4/cipso_ipv4.c#L1963">1963</a> <b><i> * Set the CIPSO option on the given socket using the DOI definition and</i></b>
<a name="L1964" href="source/net/ipv4/cipso_ipv4.c#L1964">1964</a> <b><i> * security attributes passed to the function.  Returns zero on success and</i></b>
<a name="L1965" href="source/net/ipv4/cipso_ipv4.c#L1965">1965</a> <b><i> * negative values on failure.</i></b>
<a name="L1966" href="source/net/ipv4/cipso_ipv4.c#L1966">1966</a> <b><i> *</i></b>
<a name="L1967" href="source/net/ipv4/cipso_ipv4.c#L1967">1967</a> <b><i> */</i></b>
<a name="L1968" href="source/net/ipv4/cipso_ipv4.c#L1968">1968</a> int <a href="ident?i=cipso_v4_req_setattr">cipso_v4_req_setattr</a>(struct <a href="ident?i=request_sock">request_sock</a> *<a href="ident?i=req">req</a>,
<a name="L1969" href="source/net/ipv4/cipso_ipv4.c#L1969">1969</a>                          const struct <a href="ident?i=cipso_v4_doi">cipso_v4_doi</a> *doi_def,
<a name="L1970" href="source/net/ipv4/cipso_ipv4.c#L1970">1970</a>                          const struct <a href="ident?i=netlbl_lsm_secattr">netlbl_lsm_secattr</a> *secattr)
<a name="L1971" href="source/net/ipv4/cipso_ipv4.c#L1971">1971</a> {
<a name="L1972" href="source/net/ipv4/cipso_ipv4.c#L1972">1972</a>         int ret_val = -<a href="ident?i=EPERM">EPERM</a>;
<a name="L1973" href="source/net/ipv4/cipso_ipv4.c#L1973">1973</a>         unsigned char *<a href="ident?i=buf">buf</a> = <a href="ident?i=NULL">NULL</a>;
<a name="L1974" href="source/net/ipv4/cipso_ipv4.c#L1974">1974</a>         <a href="ident?i=u32">u32</a> <a href="ident?i=buf_len">buf_len</a>;
<a name="L1975" href="source/net/ipv4/cipso_ipv4.c#L1975">1975</a>         <a href="ident?i=u32">u32</a> opt_len;
<a name="L1976" href="source/net/ipv4/cipso_ipv4.c#L1976">1976</a>         struct <a href="ident?i=ip_options_rcu">ip_options_rcu</a> *opt = <a href="ident?i=NULL">NULL</a>;
<a name="L1977" href="source/net/ipv4/cipso_ipv4.c#L1977">1977</a>         struct <a href="ident?i=inet_request_sock">inet_request_sock</a> *req_inet;
<a name="L1978" href="source/net/ipv4/cipso_ipv4.c#L1978">1978</a> 
<a name="L1979" href="source/net/ipv4/cipso_ipv4.c#L1979">1979</a>         <b><i>/* We allocate the maximum CIPSO option size here so we are probably</i></b>
<a name="L1980" href="source/net/ipv4/cipso_ipv4.c#L1980">1980</a> <b><i>         * being a little wasteful, but it makes our life _much_ easier later</i></b>
<a name="L1981" href="source/net/ipv4/cipso_ipv4.c#L1981">1981</a> <b><i>         * on and after all we are only talking about 40 bytes. */</i></b>
<a name="L1982" href="source/net/ipv4/cipso_ipv4.c#L1982">1982</a>         <a href="ident?i=buf_len">buf_len</a> = <a href="ident?i=CIPSO_V4_OPT_LEN_MAX">CIPSO_V4_OPT_LEN_MAX</a>;
<a name="L1983" href="source/net/ipv4/cipso_ipv4.c#L1983">1983</a>         <a href="ident?i=buf">buf</a> = <a href="ident?i=kmalloc">kmalloc</a>(<a href="ident?i=buf_len">buf_len</a>, <a href="ident?i=GFP_ATOMIC">GFP_ATOMIC</a>);
<a name="L1984" href="source/net/ipv4/cipso_ipv4.c#L1984">1984</a>         if (!<a href="ident?i=buf">buf</a>) {
<a name="L1985" href="source/net/ipv4/cipso_ipv4.c#L1985">1985</a>                 ret_val = -<a href="ident?i=ENOMEM">ENOMEM</a>;
<a name="L1986" href="source/net/ipv4/cipso_ipv4.c#L1986">1986</a>                 goto req_setattr_failure;
<a name="L1987" href="source/net/ipv4/cipso_ipv4.c#L1987">1987</a>         }
<a name="L1988" href="source/net/ipv4/cipso_ipv4.c#L1988">1988</a> 
<a name="L1989" href="source/net/ipv4/cipso_ipv4.c#L1989">1989</a>         ret_val = <a href="ident?i=cipso_v4_genopt">cipso_v4_genopt</a>(<a href="ident?i=buf">buf</a>, <a href="ident?i=buf_len">buf_len</a>, doi_def, secattr);
<a name="L1990" href="source/net/ipv4/cipso_ipv4.c#L1990">1990</a>         if (ret_val &lt; 0)
<a name="L1991" href="source/net/ipv4/cipso_ipv4.c#L1991">1991</a>                 goto req_setattr_failure;
<a name="L1992" href="source/net/ipv4/cipso_ipv4.c#L1992">1992</a>         <a href="ident?i=buf_len">buf_len</a> = ret_val;
<a name="L1993" href="source/net/ipv4/cipso_ipv4.c#L1993">1993</a> 
<a name="L1994" href="source/net/ipv4/cipso_ipv4.c#L1994">1994</a>         <b><i>/* We can't use ip_options_get() directly because it makes a call to</i></b>
<a name="L1995" href="source/net/ipv4/cipso_ipv4.c#L1995">1995</a> <b><i>         * ip_options_get_alloc() which allocates memory with GFP_KERNEL and</i></b>
<a name="L1996" href="source/net/ipv4/cipso_ipv4.c#L1996">1996</a> <b><i>         * we won't always have CAP_NET_RAW even though we _always_ want to</i></b>
<a name="L1997" href="source/net/ipv4/cipso_ipv4.c#L1997">1997</a> <b><i>         * set the IPOPT_CIPSO option. */</i></b>
<a name="L1998" href="source/net/ipv4/cipso_ipv4.c#L1998">1998</a>         opt_len = (<a href="ident?i=buf_len">buf_len</a> + 3) &amp; ~3;
<a name="L1999" href="source/net/ipv4/cipso_ipv4.c#L1999">1999</a>         opt = <a href="ident?i=kzalloc">kzalloc</a>(sizeof(*opt) + opt_len, <a href="ident?i=GFP_ATOMIC">GFP_ATOMIC</a>);
<a name="L2000" href="source/net/ipv4/cipso_ipv4.c#L2000">2000</a>         if (!opt) {
<a name="L2001" href="source/net/ipv4/cipso_ipv4.c#L2001">2001</a>                 ret_val = -<a href="ident?i=ENOMEM">ENOMEM</a>;
<a name="L2002" href="source/net/ipv4/cipso_ipv4.c#L2002">2002</a>                 goto req_setattr_failure;
<a name="L2003" href="source/net/ipv4/cipso_ipv4.c#L2003">2003</a>         }
<a name="L2004" href="source/net/ipv4/cipso_ipv4.c#L2004">2004</a>         <a href="ident?i=memcpy">memcpy</a>(opt-&gt;opt.__data, <a href="ident?i=buf">buf</a>, <a href="ident?i=buf_len">buf_len</a>);
<a name="L2005" href="source/net/ipv4/cipso_ipv4.c#L2005">2005</a>         opt-&gt;opt.<a href="ident?i=optlen">optlen</a> = opt_len;
<a name="L2006" href="source/net/ipv4/cipso_ipv4.c#L2006">2006</a>         opt-&gt;opt.cipso = sizeof(struct <a href="ident?i=iphdr">iphdr</a>);
<a name="L2007" href="source/net/ipv4/cipso_ipv4.c#L2007">2007</a>         <a href="ident?i=kfree">kfree</a>(<a href="ident?i=buf">buf</a>);
<a name="L2008" href="source/net/ipv4/cipso_ipv4.c#L2008">2008</a>         <a href="ident?i=buf">buf</a> = <a href="ident?i=NULL">NULL</a>;
<a name="L2009" href="source/net/ipv4/cipso_ipv4.c#L2009">2009</a> 
<a name="L2010" href="source/net/ipv4/cipso_ipv4.c#L2010">2010</a>         req_inet = <a href="ident?i=inet_rsk">inet_rsk</a>(<a href="ident?i=req">req</a>);
<a name="L2011" href="source/net/ipv4/cipso_ipv4.c#L2011">2011</a>         opt = <a href="ident?i=xchg">xchg</a>(&amp;req_inet-&gt;opt, opt);
<a name="L2012" href="source/net/ipv4/cipso_ipv4.c#L2012">2012</a>         if (opt)
<a name="L2013" href="source/net/ipv4/cipso_ipv4.c#L2013">2013</a>                 <a href="ident?i=kfree_rcu">kfree_rcu</a>(opt, rcu);
<a name="L2014" href="source/net/ipv4/cipso_ipv4.c#L2014">2014</a> 
<a name="L2015" href="source/net/ipv4/cipso_ipv4.c#L2015">2015</a>         return 0;
<a name="L2016" href="source/net/ipv4/cipso_ipv4.c#L2016">2016</a> 
<a name="L2017" href="source/net/ipv4/cipso_ipv4.c#L2017">2017</a> req_setattr_failure:
<a name="L2018" href="source/net/ipv4/cipso_ipv4.c#L2018">2018</a>         <a href="ident?i=kfree">kfree</a>(<a href="ident?i=buf">buf</a>);
<a name="L2019" href="source/net/ipv4/cipso_ipv4.c#L2019">2019</a>         <a href="ident?i=kfree">kfree</a>(opt);
<a name="L2020" href="source/net/ipv4/cipso_ipv4.c#L2020">2020</a>         return ret_val;
<a name="L2021" href="source/net/ipv4/cipso_ipv4.c#L2021">2021</a> }
<a name="L2022" href="source/net/ipv4/cipso_ipv4.c#L2022">2022</a> 
<a name="L2023" href="source/net/ipv4/cipso_ipv4.c#L2023">2023</a> <b><i>/**</i></b>
<a name="L2024" href="source/net/ipv4/cipso_ipv4.c#L2024">2024</a> <b><i> * cipso_v4_delopt - Delete the CIPSO option from a set of IP options</i></b>
<a name="L2025" href="source/net/ipv4/cipso_ipv4.c#L2025">2025</a> <b><i> * @opt_ptr: IP option pointer</i></b>
<a name="L2026" href="source/net/ipv4/cipso_ipv4.c#L2026">2026</a> <b><i> *</i></b>
<a name="L2027" href="source/net/ipv4/cipso_ipv4.c#L2027">2027</a> <b><i> * Description:</i></b>
<a name="L2028" href="source/net/ipv4/cipso_ipv4.c#L2028">2028</a> <b><i> * Deletes the CIPSO IP option from a set of IP options and makes the necessary</i></b>
<a name="L2029" href="source/net/ipv4/cipso_ipv4.c#L2029">2029</a> <b><i> * adjustments to the IP option structure.  Returns zero on success, negative</i></b>
<a name="L2030" href="source/net/ipv4/cipso_ipv4.c#L2030">2030</a> <b><i> * values on failure.</i></b>
<a name="L2031" href="source/net/ipv4/cipso_ipv4.c#L2031">2031</a> <b><i> *</i></b>
<a name="L2032" href="source/net/ipv4/cipso_ipv4.c#L2032">2032</a> <b><i> */</i></b>
<a name="L2033" href="source/net/ipv4/cipso_ipv4.c#L2033">2033</a> static int <a href="ident?i=cipso_v4_delopt">cipso_v4_delopt</a>(struct <a href="ident?i=ip_options_rcu">ip_options_rcu</a> **opt_ptr)
<a name="L2034" href="source/net/ipv4/cipso_ipv4.c#L2034">2034</a> {
<a name="L2035" href="source/net/ipv4/cipso_ipv4.c#L2035">2035</a>         int hdr_delta = 0;
<a name="L2036" href="source/net/ipv4/cipso_ipv4.c#L2036">2036</a>         struct <a href="ident?i=ip_options_rcu">ip_options_rcu</a> *opt = *opt_ptr;
<a name="L2037" href="source/net/ipv4/cipso_ipv4.c#L2037">2037</a> 
<a name="L2038" href="source/net/ipv4/cipso_ipv4.c#L2038">2038</a>         if (opt-&gt;opt.<a href="ident?i=srr">srr</a> || opt-&gt;opt.rr || opt-&gt;opt.<a href="ident?i=ts">ts</a> || opt-&gt;opt.router_alert) {
<a name="L2039" href="source/net/ipv4/cipso_ipv4.c#L2039">2039</a>                 <a href="ident?i=u8">u8</a> cipso_len;
<a name="L2040" href="source/net/ipv4/cipso_ipv4.c#L2040">2040</a>                 <a href="ident?i=u8">u8</a> cipso_off;
<a name="L2041" href="source/net/ipv4/cipso_ipv4.c#L2041">2041</a>                 unsigned char *cipso_ptr;
<a name="L2042" href="source/net/ipv4/cipso_ipv4.c#L2042">2042</a>                 int iter;
<a name="L2043" href="source/net/ipv4/cipso_ipv4.c#L2043">2043</a>                 int optlen_new;
<a name="L2044" href="source/net/ipv4/cipso_ipv4.c#L2044">2044</a> 
<a name="L2045" href="source/net/ipv4/cipso_ipv4.c#L2045">2045</a>                 cipso_off = opt-&gt;opt.cipso - sizeof(struct <a href="ident?i=iphdr">iphdr</a>);
<a name="L2046" href="source/net/ipv4/cipso_ipv4.c#L2046">2046</a>                 cipso_ptr = &amp;opt-&gt;opt.__data[cipso_off];
<a name="L2047" href="source/net/ipv4/cipso_ipv4.c#L2047">2047</a>                 cipso_len = cipso_ptr[1];
<a name="L2048" href="source/net/ipv4/cipso_ipv4.c#L2048">2048</a> 
<a name="L2049" href="source/net/ipv4/cipso_ipv4.c#L2049">2049</a>                 if (opt-&gt;opt.<a href="ident?i=srr">srr</a> &gt; opt-&gt;opt.cipso)
<a name="L2050" href="source/net/ipv4/cipso_ipv4.c#L2050">2050</a>                         opt-&gt;opt.<a href="ident?i=srr">srr</a> -= cipso_len;
<a name="L2051" href="source/net/ipv4/cipso_ipv4.c#L2051">2051</a>                 if (opt-&gt;opt.rr &gt; opt-&gt;opt.cipso)
<a name="L2052" href="source/net/ipv4/cipso_ipv4.c#L2052">2052</a>                         opt-&gt;opt.rr -= cipso_len;
<a name="L2053" href="source/net/ipv4/cipso_ipv4.c#L2053">2053</a>                 if (opt-&gt;opt.<a href="ident?i=ts">ts</a> &gt; opt-&gt;opt.cipso)
<a name="L2054" href="source/net/ipv4/cipso_ipv4.c#L2054">2054</a>                         opt-&gt;opt.<a href="ident?i=ts">ts</a> -= cipso_len;
<a name="L2055" href="source/net/ipv4/cipso_ipv4.c#L2055">2055</a>                 if (opt-&gt;opt.router_alert &gt; opt-&gt;opt.cipso)
<a name="L2056" href="source/net/ipv4/cipso_ipv4.c#L2056">2056</a>                         opt-&gt;opt.router_alert -= cipso_len;
<a name="L2057" href="source/net/ipv4/cipso_ipv4.c#L2057">2057</a>                 opt-&gt;opt.cipso = 0;
<a name="L2058" href="source/net/ipv4/cipso_ipv4.c#L2058">2058</a> 
<a name="L2059" href="source/net/ipv4/cipso_ipv4.c#L2059">2059</a>                 <a href="ident?i=memmove">memmove</a>(cipso_ptr, cipso_ptr + cipso_len,
<a name="L2060" href="source/net/ipv4/cipso_ipv4.c#L2060">2060</a>                         opt-&gt;opt.<a href="ident?i=optlen">optlen</a> - cipso_off - cipso_len);
<a name="L2061" href="source/net/ipv4/cipso_ipv4.c#L2061">2061</a> 
<a name="L2062" href="source/net/ipv4/cipso_ipv4.c#L2062">2062</a>                 <b><i>/* determining the new total option length is tricky because of</i></b>
<a name="L2063" href="source/net/ipv4/cipso_ipv4.c#L2063">2063</a> <b><i>                 * the padding necessary, the only thing i can think to do at</i></b>
<a name="L2064" href="source/net/ipv4/cipso_ipv4.c#L2064">2064</a> <b><i>                 * this point is walk the options one-by-one, skipping the</i></b>
<a name="L2065" href="source/net/ipv4/cipso_ipv4.c#L2065">2065</a> <b><i>                 * padding at the end to determine the actual option size and</i></b>
<a name="L2066" href="source/net/ipv4/cipso_ipv4.c#L2066">2066</a> <b><i>                 * from there we can determine the new total option length */</i></b>
<a name="L2067" href="source/net/ipv4/cipso_ipv4.c#L2067">2067</a>                 iter = 0;
<a name="L2068" href="source/net/ipv4/cipso_ipv4.c#L2068">2068</a>                 optlen_new = 0;
<a name="L2069" href="source/net/ipv4/cipso_ipv4.c#L2069">2069</a>                 while (iter &lt; opt-&gt;opt.<a href="ident?i=optlen">optlen</a>)
<a name="L2070" href="source/net/ipv4/cipso_ipv4.c#L2070">2070</a>                         if (opt-&gt;opt.__data[iter] != <a href="ident?i=IPOPT_NOP">IPOPT_NOP</a>) {
<a name="L2071" href="source/net/ipv4/cipso_ipv4.c#L2071">2071</a>                                 iter += opt-&gt;opt.__data[iter + 1];
<a name="L2072" href="source/net/ipv4/cipso_ipv4.c#L2072">2072</a>                                 optlen_new = iter;
<a name="L2073" href="source/net/ipv4/cipso_ipv4.c#L2073">2073</a>                         } else
<a name="L2074" href="source/net/ipv4/cipso_ipv4.c#L2074">2074</a>                                 iter++;
<a name="L2075" href="source/net/ipv4/cipso_ipv4.c#L2075">2075</a>                 hdr_delta = opt-&gt;opt.<a href="ident?i=optlen">optlen</a>;
<a name="L2076" href="source/net/ipv4/cipso_ipv4.c#L2076">2076</a>                 opt-&gt;opt.<a href="ident?i=optlen">optlen</a> = (optlen_new + 3) &amp; ~3;
<a name="L2077" href="source/net/ipv4/cipso_ipv4.c#L2077">2077</a>                 hdr_delta -= opt-&gt;opt.<a href="ident?i=optlen">optlen</a>;
<a name="L2078" href="source/net/ipv4/cipso_ipv4.c#L2078">2078</a>         } else {
<a name="L2079" href="source/net/ipv4/cipso_ipv4.c#L2079">2079</a>                 <b><i>/* only the cipso option was present on the socket so we can</i></b>
<a name="L2080" href="source/net/ipv4/cipso_ipv4.c#L2080">2080</a> <b><i>                 * remove the entire option struct */</i></b>
<a name="L2081" href="source/net/ipv4/cipso_ipv4.c#L2081">2081</a>                 *opt_ptr = <a href="ident?i=NULL">NULL</a>;
<a name="L2082" href="source/net/ipv4/cipso_ipv4.c#L2082">2082</a>                 hdr_delta = opt-&gt;opt.<a href="ident?i=optlen">optlen</a>;
<a name="L2083" href="source/net/ipv4/cipso_ipv4.c#L2083">2083</a>                 <a href="ident?i=kfree_rcu">kfree_rcu</a>(opt, rcu);
<a name="L2084" href="source/net/ipv4/cipso_ipv4.c#L2084">2084</a>         }
<a name="L2085" href="source/net/ipv4/cipso_ipv4.c#L2085">2085</a> 
<a name="L2086" href="source/net/ipv4/cipso_ipv4.c#L2086">2086</a>         return hdr_delta;
<a name="L2087" href="source/net/ipv4/cipso_ipv4.c#L2087">2087</a> }
<a name="L2088" href="source/net/ipv4/cipso_ipv4.c#L2088">2088</a> 
<a name="L2089" href="source/net/ipv4/cipso_ipv4.c#L2089">2089</a> <b><i>/**</i></b>
<a name="L2090" href="source/net/ipv4/cipso_ipv4.c#L2090">2090</a> <b><i> * cipso_v4_sock_delattr - Delete the CIPSO option from a socket</i></b>
<a name="L2091" href="source/net/ipv4/cipso_ipv4.c#L2091">2091</a> <b><i> * @sk: the socket</i></b>
<a name="L2092" href="source/net/ipv4/cipso_ipv4.c#L2092">2092</a> <b><i> *</i></b>
<a name="L2093" href="source/net/ipv4/cipso_ipv4.c#L2093">2093</a> <b><i> * Description:</i></b>
<a name="L2094" href="source/net/ipv4/cipso_ipv4.c#L2094">2094</a> <b><i> * Removes the CIPSO option from a socket, if present.</i></b>
<a name="L2095" href="source/net/ipv4/cipso_ipv4.c#L2095">2095</a> <b><i> *</i></b>
<a name="L2096" href="source/net/ipv4/cipso_ipv4.c#L2096">2096</a> <b><i> */</i></b>
<a name="L2097" href="source/net/ipv4/cipso_ipv4.c#L2097">2097</a> void <a href="ident?i=cipso_v4_sock_delattr">cipso_v4_sock_delattr</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L2098" href="source/net/ipv4/cipso_ipv4.c#L2098">2098</a> {
<a name="L2099" href="source/net/ipv4/cipso_ipv4.c#L2099">2099</a>         int hdr_delta;
<a name="L2100" href="source/net/ipv4/cipso_ipv4.c#L2100">2100</a>         struct <a href="ident?i=ip_options_rcu">ip_options_rcu</a> *opt;
<a name="L2101" href="source/net/ipv4/cipso_ipv4.c#L2101">2101</a>         struct <a href="ident?i=inet_sock">inet_sock</a> *sk_inet;
<a name="L2102" href="source/net/ipv4/cipso_ipv4.c#L2102">2102</a> 
<a name="L2103" href="source/net/ipv4/cipso_ipv4.c#L2103">2103</a>         sk_inet = <a href="ident?i=inet_sk">inet_sk</a>(sk);
<a name="L2104" href="source/net/ipv4/cipso_ipv4.c#L2104">2104</a>         opt = <a href="ident?i=rcu_dereference_protected">rcu_dereference_protected</a>(sk_inet-&gt;inet_opt, 1);
<a name="L2105" href="source/net/ipv4/cipso_ipv4.c#L2105">2105</a>         if (!opt || opt-&gt;opt.cipso == 0)
<a name="L2106" href="source/net/ipv4/cipso_ipv4.c#L2106">2106</a>                 return;
<a name="L2107" href="source/net/ipv4/cipso_ipv4.c#L2107">2107</a> 
<a name="L2108" href="source/net/ipv4/cipso_ipv4.c#L2108">2108</a>         hdr_delta = <a href="ident?i=cipso_v4_delopt">cipso_v4_delopt</a>(&amp;sk_inet-&gt;inet_opt);
<a name="L2109" href="source/net/ipv4/cipso_ipv4.c#L2109">2109</a>         if (sk_inet-&gt;is_icsk &amp;&amp; hdr_delta &gt; 0) {
<a name="L2110" href="source/net/ipv4/cipso_ipv4.c#L2110">2110</a>                 struct <a href="ident?i=inet_connection_sock">inet_connection_sock</a> *sk_conn = <a href="ident?i=inet_csk">inet_csk</a>(sk);
<a name="L2111" href="source/net/ipv4/cipso_ipv4.c#L2111">2111</a>                 sk_conn-&gt;icsk_ext_hdr_len -= hdr_delta;
<a name="L2112" href="source/net/ipv4/cipso_ipv4.c#L2112">2112</a>                 sk_conn-&gt;icsk_sync_mss(sk, sk_conn-&gt;icsk_pmtu_cookie);
<a name="L2113" href="source/net/ipv4/cipso_ipv4.c#L2113">2113</a>         }
<a name="L2114" href="source/net/ipv4/cipso_ipv4.c#L2114">2114</a> }
<a name="L2115" href="source/net/ipv4/cipso_ipv4.c#L2115">2115</a> 
<a name="L2116" href="source/net/ipv4/cipso_ipv4.c#L2116">2116</a> <b><i>/**</i></b>
<a name="L2117" href="source/net/ipv4/cipso_ipv4.c#L2117">2117</a> <b><i> * cipso_v4_req_delattr - Delete the CIPSO option from a request socket</i></b>
<a name="L2118" href="source/net/ipv4/cipso_ipv4.c#L2118">2118</a> <b><i> * @reg: the request socket</i></b>
<a name="L2119" href="source/net/ipv4/cipso_ipv4.c#L2119">2119</a> <b><i> *</i></b>
<a name="L2120" href="source/net/ipv4/cipso_ipv4.c#L2120">2120</a> <b><i> * Description:</i></b>
<a name="L2121" href="source/net/ipv4/cipso_ipv4.c#L2121">2121</a> <b><i> * Removes the CIPSO option from a request socket, if present.</i></b>
<a name="L2122" href="source/net/ipv4/cipso_ipv4.c#L2122">2122</a> <b><i> *</i></b>
<a name="L2123" href="source/net/ipv4/cipso_ipv4.c#L2123">2123</a> <b><i> */</i></b>
<a name="L2124" href="source/net/ipv4/cipso_ipv4.c#L2124">2124</a> void <a href="ident?i=cipso_v4_req_delattr">cipso_v4_req_delattr</a>(struct <a href="ident?i=request_sock">request_sock</a> *<a href="ident?i=req">req</a>)
<a name="L2125" href="source/net/ipv4/cipso_ipv4.c#L2125">2125</a> {
<a name="L2126" href="source/net/ipv4/cipso_ipv4.c#L2126">2126</a>         struct <a href="ident?i=ip_options_rcu">ip_options_rcu</a> *opt;
<a name="L2127" href="source/net/ipv4/cipso_ipv4.c#L2127">2127</a>         struct <a href="ident?i=inet_request_sock">inet_request_sock</a> *req_inet;
<a name="L2128" href="source/net/ipv4/cipso_ipv4.c#L2128">2128</a> 
<a name="L2129" href="source/net/ipv4/cipso_ipv4.c#L2129">2129</a>         req_inet = <a href="ident?i=inet_rsk">inet_rsk</a>(<a href="ident?i=req">req</a>);
<a name="L2130" href="source/net/ipv4/cipso_ipv4.c#L2130">2130</a>         opt = req_inet-&gt;opt;
<a name="L2131" href="source/net/ipv4/cipso_ipv4.c#L2131">2131</a>         if (!opt || opt-&gt;opt.cipso == 0)
<a name="L2132" href="source/net/ipv4/cipso_ipv4.c#L2132">2132</a>                 return;
<a name="L2133" href="source/net/ipv4/cipso_ipv4.c#L2133">2133</a> 
<a name="L2134" href="source/net/ipv4/cipso_ipv4.c#L2134">2134</a>         <a href="ident?i=cipso_v4_delopt">cipso_v4_delopt</a>(&amp;req_inet-&gt;opt);
<a name="L2135" href="source/net/ipv4/cipso_ipv4.c#L2135">2135</a> }
<a name="L2136" href="source/net/ipv4/cipso_ipv4.c#L2136">2136</a> 
<a name="L2137" href="source/net/ipv4/cipso_ipv4.c#L2137">2137</a> <b><i>/**</i></b>
<a name="L2138" href="source/net/ipv4/cipso_ipv4.c#L2138">2138</a> <b><i> * cipso_v4_getattr - Helper function for the cipso_v4_*_getattr functions</i></b>
<a name="L2139" href="source/net/ipv4/cipso_ipv4.c#L2139">2139</a> <b><i> * @cipso: the CIPSO v4 option</i></b>
<a name="L2140" href="source/net/ipv4/cipso_ipv4.c#L2140">2140</a> <b><i> * @secattr: the security attributes</i></b>
<a name="L2141" href="source/net/ipv4/cipso_ipv4.c#L2141">2141</a> <b><i> *</i></b>
<a name="L2142" href="source/net/ipv4/cipso_ipv4.c#L2142">2142</a> <b><i> * Description:</i></b>
<a name="L2143" href="source/net/ipv4/cipso_ipv4.c#L2143">2143</a> <b><i> * Inspect @cipso and return the security attributes in @secattr.  Returns zero</i></b>
<a name="L2144" href="source/net/ipv4/cipso_ipv4.c#L2144">2144</a> <b><i> * on success and negative values on failure.</i></b>
<a name="L2145" href="source/net/ipv4/cipso_ipv4.c#L2145">2145</a> <b><i> *</i></b>
<a name="L2146" href="source/net/ipv4/cipso_ipv4.c#L2146">2146</a> <b><i> */</i></b>
<a name="L2147" href="source/net/ipv4/cipso_ipv4.c#L2147">2147</a> int <a href="ident?i=cipso_v4_getattr">cipso_v4_getattr</a>(const unsigned char *cipso,
<a name="L2148" href="source/net/ipv4/cipso_ipv4.c#L2148">2148</a>                      struct <a href="ident?i=netlbl_lsm_secattr">netlbl_lsm_secattr</a> *secattr)
<a name="L2149" href="source/net/ipv4/cipso_ipv4.c#L2149">2149</a> {
<a name="L2150" href="source/net/ipv4/cipso_ipv4.c#L2150">2150</a>         int ret_val = -<a href="ident?i=ENOMSG">ENOMSG</a>;
<a name="L2151" href="source/net/ipv4/cipso_ipv4.c#L2151">2151</a>         <a href="ident?i=u32">u32</a> doi;
<a name="L2152" href="source/net/ipv4/cipso_ipv4.c#L2152">2152</a>         struct <a href="ident?i=cipso_v4_doi">cipso_v4_doi</a> *doi_def;
<a name="L2153" href="source/net/ipv4/cipso_ipv4.c#L2153">2153</a> 
<a name="L2154" href="source/net/ipv4/cipso_ipv4.c#L2154">2154</a>         if (<a href="ident?i=cipso_v4_cache_check">cipso_v4_cache_check</a>(cipso, cipso[1], secattr) == 0)
<a name="L2155" href="source/net/ipv4/cipso_ipv4.c#L2155">2155</a>                 return 0;
<a name="L2156" href="source/net/ipv4/cipso_ipv4.c#L2156">2156</a> 
<a name="L2157" href="source/net/ipv4/cipso_ipv4.c#L2157">2157</a>         doi = <a href="ident?i=get_unaligned_be32">get_unaligned_be32</a>(&amp;cipso[2]);
<a name="L2158" href="source/net/ipv4/cipso_ipv4.c#L2158">2158</a>         <a href="ident?i=rcu_read_lock">rcu_read_lock</a>();
<a name="L2159" href="source/net/ipv4/cipso_ipv4.c#L2159">2159</a>         doi_def = <a href="ident?i=cipso_v4_doi_search">cipso_v4_doi_search</a>(doi);
<a name="L2160" href="source/net/ipv4/cipso_ipv4.c#L2160">2160</a>         if (!doi_def)
<a name="L2161" href="source/net/ipv4/cipso_ipv4.c#L2161">2161</a>                 goto getattr_return;
<a name="L2162" href="source/net/ipv4/cipso_ipv4.c#L2162">2162</a>         <b><i>/* XXX - This code assumes only one tag per CIPSO option which isn't</i></b>
<a name="L2163" href="source/net/ipv4/cipso_ipv4.c#L2163">2163</a> <b><i>         * really a good assumption to make but since we only support the MAC</i></b>
<a name="L2164" href="source/net/ipv4/cipso_ipv4.c#L2164">2164</a> <b><i>         * tags right now it is a safe assumption. */</i></b>
<a name="L2165" href="source/net/ipv4/cipso_ipv4.c#L2165">2165</a>         switch (cipso[6]) {
<a name="L2166" href="source/net/ipv4/cipso_ipv4.c#L2166">2166</a>         case <a href="ident?i=CIPSO_V4_TAG_RBITMAP">CIPSO_V4_TAG_RBITMAP</a>:
<a name="L2167" href="source/net/ipv4/cipso_ipv4.c#L2167">2167</a>                 ret_val = <a href="ident?i=cipso_v4_parsetag_rbm">cipso_v4_parsetag_rbm</a>(doi_def, &amp;cipso[6], secattr);
<a name="L2168" href="source/net/ipv4/cipso_ipv4.c#L2168">2168</a>                 break;
<a name="L2169" href="source/net/ipv4/cipso_ipv4.c#L2169">2169</a>         case <a href="ident?i=CIPSO_V4_TAG_ENUM">CIPSO_V4_TAG_ENUM</a>:
<a name="L2170" href="source/net/ipv4/cipso_ipv4.c#L2170">2170</a>                 ret_val = <a href="ident?i=cipso_v4_parsetag_enum">cipso_v4_parsetag_enum</a>(doi_def, &amp;cipso[6], secattr);
<a name="L2171" href="source/net/ipv4/cipso_ipv4.c#L2171">2171</a>                 break;
<a name="L2172" href="source/net/ipv4/cipso_ipv4.c#L2172">2172</a>         case <a href="ident?i=CIPSO_V4_TAG_RANGE">CIPSO_V4_TAG_RANGE</a>:
<a name="L2173" href="source/net/ipv4/cipso_ipv4.c#L2173">2173</a>                 ret_val = <a href="ident?i=cipso_v4_parsetag_rng">cipso_v4_parsetag_rng</a>(doi_def, &amp;cipso[6], secattr);
<a name="L2174" href="source/net/ipv4/cipso_ipv4.c#L2174">2174</a>                 break;
<a name="L2175" href="source/net/ipv4/cipso_ipv4.c#L2175">2175</a>         case <a href="ident?i=CIPSO_V4_TAG_LOCAL">CIPSO_V4_TAG_LOCAL</a>:
<a name="L2176" href="source/net/ipv4/cipso_ipv4.c#L2176">2176</a>                 ret_val = <a href="ident?i=cipso_v4_parsetag_loc">cipso_v4_parsetag_loc</a>(doi_def, &amp;cipso[6], secattr);
<a name="L2177" href="source/net/ipv4/cipso_ipv4.c#L2177">2177</a>                 break;
<a name="L2178" href="source/net/ipv4/cipso_ipv4.c#L2178">2178</a>         }
<a name="L2179" href="source/net/ipv4/cipso_ipv4.c#L2179">2179</a>         if (ret_val == 0)
<a name="L2180" href="source/net/ipv4/cipso_ipv4.c#L2180">2180</a>                 secattr-&gt;<a href="ident?i=type">type</a> = <a href="ident?i=NETLBL_NLTYPE_CIPSOV4">NETLBL_NLTYPE_CIPSOV4</a>;
<a name="L2181" href="source/net/ipv4/cipso_ipv4.c#L2181">2181</a> 
<a name="L2182" href="source/net/ipv4/cipso_ipv4.c#L2182">2182</a> getattr_return:
<a name="L2183" href="source/net/ipv4/cipso_ipv4.c#L2183">2183</a>         <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L2184" href="source/net/ipv4/cipso_ipv4.c#L2184">2184</a>         return ret_val;
<a name="L2185" href="source/net/ipv4/cipso_ipv4.c#L2185">2185</a> }
<a name="L2186" href="source/net/ipv4/cipso_ipv4.c#L2186">2186</a> 
<a name="L2187" href="source/net/ipv4/cipso_ipv4.c#L2187">2187</a> <b><i>/**</i></b>
<a name="L2188" href="source/net/ipv4/cipso_ipv4.c#L2188">2188</a> <b><i> * cipso_v4_sock_getattr - Get the security attributes from a sock</i></b>
<a name="L2189" href="source/net/ipv4/cipso_ipv4.c#L2189">2189</a> <b><i> * @sk: the sock</i></b>
<a name="L2190" href="source/net/ipv4/cipso_ipv4.c#L2190">2190</a> <b><i> * @secattr: the security attributes</i></b>
<a name="L2191" href="source/net/ipv4/cipso_ipv4.c#L2191">2191</a> <b><i> *</i></b>
<a name="L2192" href="source/net/ipv4/cipso_ipv4.c#L2192">2192</a> <b><i> * Description:</i></b>
<a name="L2193" href="source/net/ipv4/cipso_ipv4.c#L2193">2193</a> <b><i> * Query @sk to see if there is a CIPSO option attached to the sock and if</i></b>
<a name="L2194" href="source/net/ipv4/cipso_ipv4.c#L2194">2194</a> <b><i> * there is return the CIPSO security attributes in @secattr.  This function</i></b>
<a name="L2195" href="source/net/ipv4/cipso_ipv4.c#L2195">2195</a> <b><i> * requires that @sk be locked, or privately held, but it does not do any</i></b>
<a name="L2196" href="source/net/ipv4/cipso_ipv4.c#L2196">2196</a> <b><i> * locking itself.  Returns zero on success and negative values on failure.</i></b>
<a name="L2197" href="source/net/ipv4/cipso_ipv4.c#L2197">2197</a> <b><i> *</i></b>
<a name="L2198" href="source/net/ipv4/cipso_ipv4.c#L2198">2198</a> <b><i> */</i></b>
<a name="L2199" href="source/net/ipv4/cipso_ipv4.c#L2199">2199</a> int <a href="ident?i=cipso_v4_sock_getattr">cipso_v4_sock_getattr</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=netlbl_lsm_secattr">netlbl_lsm_secattr</a> *secattr)
<a name="L2200" href="source/net/ipv4/cipso_ipv4.c#L2200">2200</a> {
<a name="L2201" href="source/net/ipv4/cipso_ipv4.c#L2201">2201</a>         struct <a href="ident?i=ip_options_rcu">ip_options_rcu</a> *opt;
<a name="L2202" href="source/net/ipv4/cipso_ipv4.c#L2202">2202</a>         int <a href="ident?i=res">res</a> = -<a href="ident?i=ENOMSG">ENOMSG</a>;
<a name="L2203" href="source/net/ipv4/cipso_ipv4.c#L2203">2203</a> 
<a name="L2204" href="source/net/ipv4/cipso_ipv4.c#L2204">2204</a>         <a href="ident?i=rcu_read_lock">rcu_read_lock</a>();
<a name="L2205" href="source/net/ipv4/cipso_ipv4.c#L2205">2205</a>         opt = <a href="ident?i=rcu_dereference">rcu_dereference</a>(<a href="ident?i=inet_sk">inet_sk</a>(sk)-&gt;inet_opt);
<a name="L2206" href="source/net/ipv4/cipso_ipv4.c#L2206">2206</a>         if (opt &amp;&amp; opt-&gt;opt.cipso)
<a name="L2207" href="source/net/ipv4/cipso_ipv4.c#L2207">2207</a>                 <a href="ident?i=res">res</a> = <a href="ident?i=cipso_v4_getattr">cipso_v4_getattr</a>(opt-&gt;opt.__data +
<a name="L2208" href="source/net/ipv4/cipso_ipv4.c#L2208">2208</a>                                                 opt-&gt;opt.cipso -
<a name="L2209" href="source/net/ipv4/cipso_ipv4.c#L2209">2209</a>                                                 sizeof(struct <a href="ident?i=iphdr">iphdr</a>),
<a name="L2210" href="source/net/ipv4/cipso_ipv4.c#L2210">2210</a>                                        secattr);
<a name="L2211" href="source/net/ipv4/cipso_ipv4.c#L2211">2211</a>         <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L2212" href="source/net/ipv4/cipso_ipv4.c#L2212">2212</a>         return <a href="ident?i=res">res</a>;
<a name="L2213" href="source/net/ipv4/cipso_ipv4.c#L2213">2213</a> }
<a name="L2214" href="source/net/ipv4/cipso_ipv4.c#L2214">2214</a> 
<a name="L2215" href="source/net/ipv4/cipso_ipv4.c#L2215">2215</a> <b><i>/**</i></b>
<a name="L2216" href="source/net/ipv4/cipso_ipv4.c#L2216">2216</a> <b><i> * cipso_v4_skbuff_setattr - Set the CIPSO option on a packet</i></b>
<a name="L2217" href="source/net/ipv4/cipso_ipv4.c#L2217">2217</a> <b><i> * @skb: the packet</i></b>
<a name="L2218" href="source/net/ipv4/cipso_ipv4.c#L2218">2218</a> <b><i> * @secattr: the security attributes</i></b>
<a name="L2219" href="source/net/ipv4/cipso_ipv4.c#L2219">2219</a> <b><i> *</i></b>
<a name="L2220" href="source/net/ipv4/cipso_ipv4.c#L2220">2220</a> <b><i> * Description:</i></b>
<a name="L2221" href="source/net/ipv4/cipso_ipv4.c#L2221">2221</a> <b><i> * Set the CIPSO option on the given packet based on the security attributes.</i></b>
<a name="L2222" href="source/net/ipv4/cipso_ipv4.c#L2222">2222</a> <b><i> * Returns a pointer to the IP header on success and NULL on failure.</i></b>
<a name="L2223" href="source/net/ipv4/cipso_ipv4.c#L2223">2223</a> <b><i> *</i></b>
<a name="L2224" href="source/net/ipv4/cipso_ipv4.c#L2224">2224</a> <b><i> */</i></b>
<a name="L2225" href="source/net/ipv4/cipso_ipv4.c#L2225">2225</a> int <a href="ident?i=cipso_v4_skbuff_setattr">cipso_v4_skbuff_setattr</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
<a name="L2226" href="source/net/ipv4/cipso_ipv4.c#L2226">2226</a>                             const struct <a href="ident?i=cipso_v4_doi">cipso_v4_doi</a> *doi_def,
<a name="L2227" href="source/net/ipv4/cipso_ipv4.c#L2227">2227</a>                             const struct <a href="ident?i=netlbl_lsm_secattr">netlbl_lsm_secattr</a> *secattr)
<a name="L2228" href="source/net/ipv4/cipso_ipv4.c#L2228">2228</a> {
<a name="L2229" href="source/net/ipv4/cipso_ipv4.c#L2229">2229</a>         int ret_val;
<a name="L2230" href="source/net/ipv4/cipso_ipv4.c#L2230">2230</a>         struct <a href="ident?i=iphdr">iphdr</a> *iph;
<a name="L2231" href="source/net/ipv4/cipso_ipv4.c#L2231">2231</a>         struct <a href="ident?i=ip_options">ip_options</a> *opt = &amp;<a href="ident?i=IPCB">IPCB</a>(<a href="ident?i=skb">skb</a>)-&gt;opt;
<a name="L2232" href="source/net/ipv4/cipso_ipv4.c#L2232">2232</a>         unsigned char <a href="ident?i=buf">buf</a>[<a href="ident?i=CIPSO_V4_OPT_LEN_MAX">CIPSO_V4_OPT_LEN_MAX</a>];
<a name="L2233" href="source/net/ipv4/cipso_ipv4.c#L2233">2233</a>         <a href="ident?i=u32">u32</a> <a href="ident?i=buf_len">buf_len</a> = <a href="ident?i=CIPSO_V4_OPT_LEN_MAX">CIPSO_V4_OPT_LEN_MAX</a>;
<a name="L2234" href="source/net/ipv4/cipso_ipv4.c#L2234">2234</a>         <a href="ident?i=u32">u32</a> opt_len;
<a name="L2235" href="source/net/ipv4/cipso_ipv4.c#L2235">2235</a>         int len_delta;
<a name="L2236" href="source/net/ipv4/cipso_ipv4.c#L2236">2236</a> 
<a name="L2237" href="source/net/ipv4/cipso_ipv4.c#L2237">2237</a>         ret_val = <a href="ident?i=cipso_v4_genopt">cipso_v4_genopt</a>(<a href="ident?i=buf">buf</a>, <a href="ident?i=buf_len">buf_len</a>, doi_def, secattr);
<a name="L2238" href="source/net/ipv4/cipso_ipv4.c#L2238">2238</a>         if (ret_val &lt; 0)
<a name="L2239" href="source/net/ipv4/cipso_ipv4.c#L2239">2239</a>                 return ret_val;
<a name="L2240" href="source/net/ipv4/cipso_ipv4.c#L2240">2240</a>         <a href="ident?i=buf_len">buf_len</a> = ret_val;
<a name="L2241" href="source/net/ipv4/cipso_ipv4.c#L2241">2241</a>         opt_len = (<a href="ident?i=buf_len">buf_len</a> + 3) &amp; ~3;
<a name="L2242" href="source/net/ipv4/cipso_ipv4.c#L2242">2242</a> 
<a name="L2243" href="source/net/ipv4/cipso_ipv4.c#L2243">2243</a>         <b><i>/* we overwrite any existing options to ensure that we have enough</i></b>
<a name="L2244" href="source/net/ipv4/cipso_ipv4.c#L2244">2244</a> <b><i>         * room for the CIPSO option, the reason is that we _need_ to guarantee</i></b>
<a name="L2245" href="source/net/ipv4/cipso_ipv4.c#L2245">2245</a> <b><i>         * that the security label is applied to the packet - we do the same</i></b>
<a name="L2246" href="source/net/ipv4/cipso_ipv4.c#L2246">2246</a> <b><i>         * thing when using the socket options and it hasn't caused a problem,</i></b>
<a name="L2247" href="source/net/ipv4/cipso_ipv4.c#L2247">2247</a> <b><i>         * if we need to we can always revisit this choice later */</i></b>
<a name="L2248" href="source/net/ipv4/cipso_ipv4.c#L2248">2248</a> 
<a name="L2249" href="source/net/ipv4/cipso_ipv4.c#L2249">2249</a>         len_delta = opt_len - opt-&gt;<a href="ident?i=optlen">optlen</a>;
<a name="L2250" href="source/net/ipv4/cipso_ipv4.c#L2250">2250</a>         <b><i>/* if we don't ensure enough headroom we could panic on the skb_push()</i></b>
<a name="L2251" href="source/net/ipv4/cipso_ipv4.c#L2251">2251</a> <b><i>         * call below so make sure we have enough, we are also "mangling" the</i></b>
<a name="L2252" href="source/net/ipv4/cipso_ipv4.c#L2252">2252</a> <b><i>         * packet so we should probably do a copy-on-write call anyway */</i></b>
<a name="L2253" href="source/net/ipv4/cipso_ipv4.c#L2253">2253</a>         ret_val = <a href="ident?i=skb_cow">skb_cow</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=skb_headroom">skb_headroom</a>(<a href="ident?i=skb">skb</a>) + len_delta);
<a name="L2254" href="source/net/ipv4/cipso_ipv4.c#L2254">2254</a>         if (ret_val &lt; 0)
<a name="L2255" href="source/net/ipv4/cipso_ipv4.c#L2255">2255</a>                 return ret_val;
<a name="L2256" href="source/net/ipv4/cipso_ipv4.c#L2256">2256</a> 
<a name="L2257" href="source/net/ipv4/cipso_ipv4.c#L2257">2257</a>         if (len_delta &gt; 0) {
<a name="L2258" href="source/net/ipv4/cipso_ipv4.c#L2258">2258</a>                 <b><i>/* we assume that the header + opt-&gt;optlen have already been</i></b>
<a name="L2259" href="source/net/ipv4/cipso_ipv4.c#L2259">2259</a> <b><i>                 * "pushed" in ip_options_build() or similar */</i></b>
<a name="L2260" href="source/net/ipv4/cipso_ipv4.c#L2260">2260</a>                 iph = <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>);
<a name="L2261" href="source/net/ipv4/cipso_ipv4.c#L2261">2261</a>                 <a href="ident?i=skb_push">skb_push</a>(<a href="ident?i=skb">skb</a>, len_delta);
<a name="L2262" href="source/net/ipv4/cipso_ipv4.c#L2262">2262</a>                 <a href="ident?i=memmove">memmove</a>((char *)iph - len_delta, iph, iph-&gt;ihl &lt;&lt; 2);
<a name="L2263" href="source/net/ipv4/cipso_ipv4.c#L2263">2263</a>                 <a href="ident?i=skb_reset_network_header">skb_reset_network_header</a>(<a href="ident?i=skb">skb</a>);
<a name="L2264" href="source/net/ipv4/cipso_ipv4.c#L2264">2264</a>                 iph = <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>);
<a name="L2265" href="source/net/ipv4/cipso_ipv4.c#L2265">2265</a>         } else if (len_delta &lt; 0) {
<a name="L2266" href="source/net/ipv4/cipso_ipv4.c#L2266">2266</a>                 iph = <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>);
<a name="L2267" href="source/net/ipv4/cipso_ipv4.c#L2267">2267</a>                 <a href="ident?i=memset">memset</a>(iph + 1, <a href="ident?i=IPOPT_NOP">IPOPT_NOP</a>, opt-&gt;<a href="ident?i=optlen">optlen</a>);
<a name="L2268" href="source/net/ipv4/cipso_ipv4.c#L2268">2268</a>         } else
<a name="L2269" href="source/net/ipv4/cipso_ipv4.c#L2269">2269</a>                 iph = <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>);
<a name="L2270" href="source/net/ipv4/cipso_ipv4.c#L2270">2270</a> 
<a name="L2271" href="source/net/ipv4/cipso_ipv4.c#L2271">2271</a>         if (opt-&gt;<a href="ident?i=optlen">optlen</a> &gt; 0)
<a name="L2272" href="source/net/ipv4/cipso_ipv4.c#L2272">2272</a>                 <a href="ident?i=memset">memset</a>(opt, 0, sizeof(*opt));
<a name="L2273" href="source/net/ipv4/cipso_ipv4.c#L2273">2273</a>         opt-&gt;<a href="ident?i=optlen">optlen</a> = opt_len;
<a name="L2274" href="source/net/ipv4/cipso_ipv4.c#L2274">2274</a>         opt-&gt;cipso = sizeof(struct <a href="ident?i=iphdr">iphdr</a>);
<a name="L2275" href="source/net/ipv4/cipso_ipv4.c#L2275">2275</a>         opt-&gt;is_changed = 1;
<a name="L2276" href="source/net/ipv4/cipso_ipv4.c#L2276">2276</a> 
<a name="L2277" href="source/net/ipv4/cipso_ipv4.c#L2277">2277</a>         <b><i>/* we have to do the following because we are being called from a</i></b>
<a name="L2278" href="source/net/ipv4/cipso_ipv4.c#L2278">2278</a> <b><i>         * netfilter hook which means the packet already has had the header</i></b>
<a name="L2279" href="source/net/ipv4/cipso_ipv4.c#L2279">2279</a> <b><i>         * fields populated and the checksum calculated - yes this means we</i></b>
<a name="L2280" href="source/net/ipv4/cipso_ipv4.c#L2280">2280</a> <b><i>         * are doing more work than needed but we do it to keep the core</i></b>
<a name="L2281" href="source/net/ipv4/cipso_ipv4.c#L2281">2281</a> <b><i>         * stack clean and tidy */</i></b>
<a name="L2282" href="source/net/ipv4/cipso_ipv4.c#L2282">2282</a>         <a href="ident?i=memcpy">memcpy</a>(iph + 1, <a href="ident?i=buf">buf</a>, <a href="ident?i=buf_len">buf_len</a>);
<a name="L2283" href="source/net/ipv4/cipso_ipv4.c#L2283">2283</a>         if (opt_len &gt; <a href="ident?i=buf_len">buf_len</a>)
<a name="L2284" href="source/net/ipv4/cipso_ipv4.c#L2284">2284</a>                 <a href="ident?i=memset">memset</a>((char *)(iph + 1) + <a href="ident?i=buf_len">buf_len</a>, 0, opt_len - <a href="ident?i=buf_len">buf_len</a>);
<a name="L2285" href="source/net/ipv4/cipso_ipv4.c#L2285">2285</a>         if (len_delta != 0) {
<a name="L2286" href="source/net/ipv4/cipso_ipv4.c#L2286">2286</a>                 iph-&gt;ihl = 5 + (opt_len &gt;&gt; 2);
<a name="L2287" href="source/net/ipv4/cipso_ipv4.c#L2287">2287</a>                 iph-&gt;tot_len = <a href="ident?i=htons">htons</a>(<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a>);
<a name="L2288" href="source/net/ipv4/cipso_ipv4.c#L2288">2288</a>         }
<a name="L2289" href="source/net/ipv4/cipso_ipv4.c#L2289">2289</a>         <a href="ident?i=ip_send_check">ip_send_check</a>(iph);
<a name="L2290" href="source/net/ipv4/cipso_ipv4.c#L2290">2290</a> 
<a name="L2291" href="source/net/ipv4/cipso_ipv4.c#L2291">2291</a>         return 0;
<a name="L2292" href="source/net/ipv4/cipso_ipv4.c#L2292">2292</a> }
<a name="L2293" href="source/net/ipv4/cipso_ipv4.c#L2293">2293</a> 
<a name="L2294" href="source/net/ipv4/cipso_ipv4.c#L2294">2294</a> <b><i>/**</i></b>
<a name="L2295" href="source/net/ipv4/cipso_ipv4.c#L2295">2295</a> <b><i> * cipso_v4_skbuff_delattr - Delete any CIPSO options from a packet</i></b>
<a name="L2296" href="source/net/ipv4/cipso_ipv4.c#L2296">2296</a> <b><i> * @skb: the packet</i></b>
<a name="L2297" href="source/net/ipv4/cipso_ipv4.c#L2297">2297</a> <b><i> *</i></b>
<a name="L2298" href="source/net/ipv4/cipso_ipv4.c#L2298">2298</a> <b><i> * Description:</i></b>
<a name="L2299" href="source/net/ipv4/cipso_ipv4.c#L2299">2299</a> <b><i> * Removes any and all CIPSO options from the given packet.  Returns zero on</i></b>
<a name="L2300" href="source/net/ipv4/cipso_ipv4.c#L2300">2300</a> <b><i> * success, negative values on failure.</i></b>
<a name="L2301" href="source/net/ipv4/cipso_ipv4.c#L2301">2301</a> <b><i> *</i></b>
<a name="L2302" href="source/net/ipv4/cipso_ipv4.c#L2302">2302</a> <b><i> */</i></b>
<a name="L2303" href="source/net/ipv4/cipso_ipv4.c#L2303">2303</a> int <a href="ident?i=cipso_v4_skbuff_delattr">cipso_v4_skbuff_delattr</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L2304" href="source/net/ipv4/cipso_ipv4.c#L2304">2304</a> {
<a name="L2305" href="source/net/ipv4/cipso_ipv4.c#L2305">2305</a>         int ret_val;
<a name="L2306" href="source/net/ipv4/cipso_ipv4.c#L2306">2306</a>         struct <a href="ident?i=iphdr">iphdr</a> *iph;
<a name="L2307" href="source/net/ipv4/cipso_ipv4.c#L2307">2307</a>         struct <a href="ident?i=ip_options">ip_options</a> *opt = &amp;<a href="ident?i=IPCB">IPCB</a>(<a href="ident?i=skb">skb</a>)-&gt;opt;
<a name="L2308" href="source/net/ipv4/cipso_ipv4.c#L2308">2308</a>         unsigned char *cipso_ptr;
<a name="L2309" href="source/net/ipv4/cipso_ipv4.c#L2309">2309</a> 
<a name="L2310" href="source/net/ipv4/cipso_ipv4.c#L2310">2310</a>         if (opt-&gt;cipso == 0)
<a name="L2311" href="source/net/ipv4/cipso_ipv4.c#L2311">2311</a>                 return 0;
<a name="L2312" href="source/net/ipv4/cipso_ipv4.c#L2312">2312</a> 
<a name="L2313" href="source/net/ipv4/cipso_ipv4.c#L2313">2313</a>         <b><i>/* since we are changing the packet we should make a copy */</i></b>
<a name="L2314" href="source/net/ipv4/cipso_ipv4.c#L2314">2314</a>         ret_val = <a href="ident?i=skb_cow">skb_cow</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=skb_headroom">skb_headroom</a>(<a href="ident?i=skb">skb</a>));
<a name="L2315" href="source/net/ipv4/cipso_ipv4.c#L2315">2315</a>         if (ret_val &lt; 0)
<a name="L2316" href="source/net/ipv4/cipso_ipv4.c#L2316">2316</a>                 return ret_val;
<a name="L2317" href="source/net/ipv4/cipso_ipv4.c#L2317">2317</a> 
<a name="L2318" href="source/net/ipv4/cipso_ipv4.c#L2318">2318</a>         <b><i>/* the easiest thing to do is just replace the cipso option with noop</i></b>
<a name="L2319" href="source/net/ipv4/cipso_ipv4.c#L2319">2319</a> <b><i>         * options since we don't change the size of the packet, although we</i></b>
<a name="L2320" href="source/net/ipv4/cipso_ipv4.c#L2320">2320</a> <b><i>         * still need to recalculate the checksum */</i></b>
<a name="L2321" href="source/net/ipv4/cipso_ipv4.c#L2321">2321</a> 
<a name="L2322" href="source/net/ipv4/cipso_ipv4.c#L2322">2322</a>         iph = <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>);
<a name="L2323" href="source/net/ipv4/cipso_ipv4.c#L2323">2323</a>         cipso_ptr = (unsigned char *)iph + opt-&gt;cipso;
<a name="L2324" href="source/net/ipv4/cipso_ipv4.c#L2324">2324</a>         <a href="ident?i=memset">memset</a>(cipso_ptr, <a href="ident?i=IPOPT_NOOP">IPOPT_NOOP</a>, cipso_ptr[1]);
<a name="L2325" href="source/net/ipv4/cipso_ipv4.c#L2325">2325</a>         opt-&gt;cipso = 0;
<a name="L2326" href="source/net/ipv4/cipso_ipv4.c#L2326">2326</a>         opt-&gt;is_changed = 1;
<a name="L2327" href="source/net/ipv4/cipso_ipv4.c#L2327">2327</a> 
<a name="L2328" href="source/net/ipv4/cipso_ipv4.c#L2328">2328</a>         <a href="ident?i=ip_send_check">ip_send_check</a>(iph);
<a name="L2329" href="source/net/ipv4/cipso_ipv4.c#L2329">2329</a> 
<a name="L2330" href="source/net/ipv4/cipso_ipv4.c#L2330">2330</a>         return 0;
<a name="L2331" href="source/net/ipv4/cipso_ipv4.c#L2331">2331</a> }
<a name="L2332" href="source/net/ipv4/cipso_ipv4.c#L2332">2332</a> 
<a name="L2333" href="source/net/ipv4/cipso_ipv4.c#L2333">2333</a> <b><i>/*</i></b>
<a name="L2334" href="source/net/ipv4/cipso_ipv4.c#L2334">2334</a> <b><i> * Setup Functions</i></b>
<a name="L2335" href="source/net/ipv4/cipso_ipv4.c#L2335">2335</a> <b><i> */</i></b>
<a name="L2336" href="source/net/ipv4/cipso_ipv4.c#L2336">2336</a> 
<a name="L2337" href="source/net/ipv4/cipso_ipv4.c#L2337">2337</a> <b><i>/**</i></b>
<a name="L2338" href="source/net/ipv4/cipso_ipv4.c#L2338">2338</a> <b><i> * cipso_v4_init - Initialize the CIPSO module</i></b>
<a name="L2339" href="source/net/ipv4/cipso_ipv4.c#L2339">2339</a> <b><i> *</i></b>
<a name="L2340" href="source/net/ipv4/cipso_ipv4.c#L2340">2340</a> <b><i> * Description:</i></b>
<a name="L2341" href="source/net/ipv4/cipso_ipv4.c#L2341">2341</a> <b><i> * Initialize the CIPSO module and prepare it for use.  Returns zero on success</i></b>
<a name="L2342" href="source/net/ipv4/cipso_ipv4.c#L2342">2342</a> <b><i> * and negative values on failure.</i></b>
<a name="L2343" href="source/net/ipv4/cipso_ipv4.c#L2343">2343</a> <b><i> *</i></b>
<a name="L2344" href="source/net/ipv4/cipso_ipv4.c#L2344">2344</a> <b><i> */</i></b>
<a name="L2345" href="source/net/ipv4/cipso_ipv4.c#L2345">2345</a> static int <a href="ident?i=__init">__init</a> <a href="ident?i=cipso_v4_init">cipso_v4_init</a>(void)
<a name="L2346" href="source/net/ipv4/cipso_ipv4.c#L2346">2346</a> {
<a name="L2347" href="source/net/ipv4/cipso_ipv4.c#L2347">2347</a>         int ret_val;
<a name="L2348" href="source/net/ipv4/cipso_ipv4.c#L2348">2348</a> 
<a name="L2349" href="source/net/ipv4/cipso_ipv4.c#L2349">2349</a>         ret_val = <a href="ident?i=cipso_v4_cache_init">cipso_v4_cache_init</a>();
<a name="L2350" href="source/net/ipv4/cipso_ipv4.c#L2350">2350</a>         if (ret_val != 0)
<a name="L2351" href="source/net/ipv4/cipso_ipv4.c#L2351">2351</a>                 <a href="ident?i=panic">panic</a>(<i>"Failed to initialize the CIPSO/IPv4 cache (%d)\n"</i>,
<a name="L2352" href="source/net/ipv4/cipso_ipv4.c#L2352">2352</a>                       ret_val);
<a name="L2353" href="source/net/ipv4/cipso_ipv4.c#L2353">2353</a> 
<a name="L2354" href="source/net/ipv4/cipso_ipv4.c#L2354">2354</a>         return 0;
<a name="L2355" href="source/net/ipv4/cipso_ipv4.c#L2355">2355</a> }
<a name="L2356" href="source/net/ipv4/cipso_ipv4.c#L2356">2356</a> 
<a name="L2357" href="source/net/ipv4/cipso_ipv4.c#L2357">2357</a> <a href="ident?i=subsys_initcall">subsys_initcall</a>(<a href="ident?i=cipso_v4_init">cipso_v4_init</a>);
<a name="L2358" href="source/net/ipv4/cipso_ipv4.c#L2358">2358</a> </pre></div><p>
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
