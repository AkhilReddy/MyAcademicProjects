<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title>Linux/net/ipv4/esp4.c - Linux Cross Reference - Free Electrons</title>
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
		 &nbsp;&bull;&nbsp;<b><i>source navigation</i></b> &nbsp;&bull;&nbsp;<a href="diff/net/ipv4/esp4.c">diff markup</a> &nbsp;&bull;&nbsp;<a href="ident">identifier search</a> &nbsp;&bull;&nbsp;<a href="search">freetext search</a> &nbsp;&bull;&nbsp;
		</p>
	</div>
</div>

<div id="topbar">
  
  <p>Version: &nbsp;<a href="source/net/ipv4/esp4.c?v=2.0.40">2.0.40</a>&nbsp;<a href="source/net/ipv4/esp4.c?v=2.2.26">2.2.26</a>&nbsp;<a href="source/net/ipv4/esp4.c?v=2.4.37">2.4.37</a>&nbsp;<a href="source/net/ipv4/esp4.c?v=3.5">3.5</a>&nbsp;<a href="source/net/ipv4/esp4.c?v=3.6">3.6</a>&nbsp;<a href="source/net/ipv4/esp4.c?v=3.7">3.7</a>&nbsp;<a href="source/net/ipv4/esp4.c?v=3.8">3.8</a>&nbsp;<a href="source/net/ipv4/esp4.c?v=3.9">3.9</a>&nbsp;<a href="source/net/ipv4/esp4.c?v=3.10">3.10</a>&nbsp;<a href="source/net/ipv4/esp4.c?v=3.11">3.11</a>&nbsp;<a href="source/net/ipv4/esp4.c?v=3.12">3.12</a>&nbsp;<a href="source/net/ipv4/esp4.c?v=3.13">3.13</a>&nbsp;<a href="source/net/ipv4/esp4.c?v=3.14">3.14</a>&nbsp;<a href="source/net/ipv4/esp4.c?v=3.15">3.15</a>&nbsp;<a href="source/net/ipv4/esp4.c?v=3.16">3.16</a>&nbsp;<a href="source/net/ipv4/esp4.c?v=3.17">3.17</a>&nbsp;<a href="source/net/ipv4/esp4.c?v=3.18">3.18</a>&nbsp;<a href="source/net/ipv4/esp4.c?v=3.19">3.19</a>&nbsp;<a href="source/net/ipv4/esp4.c?v=4.0">4.0</a>&nbsp;<b><i>4.1</i></b></p>
  
</div>

<h1><a href="source/">Linux</a>/<a href="source/net/">net</a>/<a href="source/net/ipv4/">ipv4</a>/<a href="source/net/ipv4/esp4.c">esp4.c</a></h1>
<div id="lxrcode"><pre>  <a name="L1" href="source/net/ipv4/esp4.c#L1">1</a> #define <a href="ident?i=pr_fmt">pr_fmt</a>(<a href="ident?i=fmt">fmt</a>) <i>"IPsec: "</i> <a href="ident?i=fmt">fmt</a>
  <a name="L2" href="source/net/ipv4/esp4.c#L2">2</a> 
  <a name="L3" href="source/net/ipv4/esp4.c#L3">3</a> #include &lt;crypto/aead.h&gt;
  <a name="L4" href="source/net/ipv4/esp4.c#L4">4</a> #include &lt;crypto/authenc.h&gt;
  <a name="L5" href="source/net/ipv4/esp4.c#L5">5</a> #include &lt;linux/err.h&gt;
  <a name="L6" href="source/net/ipv4/esp4.c#L6">6</a> #include &lt;linux/module.h&gt;
  <a name="L7" href="source/net/ipv4/esp4.c#L7">7</a> #include &lt;net/ip.h&gt;
  <a name="L8" href="source/net/ipv4/esp4.c#L8">8</a> #include &lt;net/xfrm.h&gt;
  <a name="L9" href="source/net/ipv4/esp4.c#L9">9</a> #include &lt;net/esp.h&gt;
 <a name="L10" href="source/net/ipv4/esp4.c#L10">10</a> #include &lt;linux/scatterlist.h&gt;
 <a name="L11" href="source/net/ipv4/esp4.c#L11">11</a> #include &lt;linux/kernel.h&gt;
 <a name="L12" href="source/net/ipv4/esp4.c#L12">12</a> #include &lt;linux/pfkeyv2.h&gt;
 <a name="L13" href="source/net/ipv4/esp4.c#L13">13</a> #include &lt;linux/rtnetlink.h&gt;
 <a name="L14" href="source/net/ipv4/esp4.c#L14">14</a> #include &lt;linux/slab.h&gt;
 <a name="L15" href="source/net/ipv4/esp4.c#L15">15</a> #include &lt;linux/spinlock.h&gt;
 <a name="L16" href="source/net/ipv4/esp4.c#L16">16</a> #include &lt;linux/in6.h&gt;
 <a name="L17" href="source/net/ipv4/esp4.c#L17">17</a> #include &lt;net/icmp.h&gt;
 <a name="L18" href="source/net/ipv4/esp4.c#L18">18</a> #include &lt;net/protocol.h&gt;
 <a name="L19" href="source/net/ipv4/esp4.c#L19">19</a> #include &lt;net/udp.h&gt;
 <a name="L20" href="source/net/ipv4/esp4.c#L20">20</a> 
 <a name="L21" href="source/net/ipv4/esp4.c#L21">21</a> struct <a href="ident?i=esp_skb_cb">esp_skb_cb</a> {
 <a name="L22" href="source/net/ipv4/esp4.c#L22">22</a>         struct <a href="ident?i=xfrm_skb_cb">xfrm_skb_cb</a> xfrm;
 <a name="L23" href="source/net/ipv4/esp4.c#L23">23</a>         void *<a href="ident?i=tmp">tmp</a>;
 <a name="L24" href="source/net/ipv4/esp4.c#L24">24</a> };
 <a name="L25" href="source/net/ipv4/esp4.c#L25">25</a> 
 <a name="L26" href="source/net/ipv4/esp4.c#L26">26</a> #define <a href="ident?i=ESP_SKB_CB">ESP_SKB_CB</a>(__skb) ((struct <a href="ident?i=esp_skb_cb">esp_skb_cb</a> *)&amp;((__skb)-&gt;<a href="ident?i=cb">cb</a>[0]))
 <a name="L27" href="source/net/ipv4/esp4.c#L27">27</a> 
 <a name="L28" href="source/net/ipv4/esp4.c#L28">28</a> static <a href="ident?i=u32">u32</a> <a href="ident?i=esp4_get_mtu">esp4_get_mtu</a>(struct <a href="ident?i=xfrm_state">xfrm_state</a> *<a href="ident?i=x">x</a>, int <a href="ident?i=mtu">mtu</a>);
 <a name="L29" href="source/net/ipv4/esp4.c#L29">29</a> 
 <a name="L30" href="source/net/ipv4/esp4.c#L30">30</a> <b><i>/*</i></b>
 <a name="L31" href="source/net/ipv4/esp4.c#L31">31</a> <b><i> * Allocate an AEAD request structure with extra space for SG and IV.</i></b>
 <a name="L32" href="source/net/ipv4/esp4.c#L32">32</a> <b><i> *</i></b>
 <a name="L33" href="source/net/ipv4/esp4.c#L33">33</a> <b><i> * For alignment considerations the IV is placed at the front, followed</i></b>
 <a name="L34" href="source/net/ipv4/esp4.c#L34">34</a> <b><i> * by the request and finally the SG list.</i></b>
 <a name="L35" href="source/net/ipv4/esp4.c#L35">35</a> <b><i> *</i></b>
 <a name="L36" href="source/net/ipv4/esp4.c#L36">36</a> <b><i> * TODO: Use spare space in skb for this where possible.</i></b>
 <a name="L37" href="source/net/ipv4/esp4.c#L37">37</a> <b><i> */</i></b>
 <a name="L38" href="source/net/ipv4/esp4.c#L38">38</a> static void *<a href="ident?i=esp_alloc_tmp">esp_alloc_tmp</a>(struct <a href="ident?i=crypto_aead">crypto_aead</a> *aead, int nfrags, int seqhilen)
 <a name="L39" href="source/net/ipv4/esp4.c#L39">39</a> {
 <a name="L40" href="source/net/ipv4/esp4.c#L40">40</a>         unsigned int <a href="ident?i=len">len</a>;
 <a name="L41" href="source/net/ipv4/esp4.c#L41">41</a> 
 <a name="L42" href="source/net/ipv4/esp4.c#L42">42</a>         <a href="ident?i=len">len</a> = seqhilen;
 <a name="L43" href="source/net/ipv4/esp4.c#L43">43</a> 
 <a name="L44" href="source/net/ipv4/esp4.c#L44">44</a>         <a href="ident?i=len">len</a> += <a href="ident?i=crypto_aead_ivsize">crypto_aead_ivsize</a>(aead);
 <a name="L45" href="source/net/ipv4/esp4.c#L45">45</a> 
 <a name="L46" href="source/net/ipv4/esp4.c#L46">46</a>         if (<a href="ident?i=len">len</a>) {
 <a name="L47" href="source/net/ipv4/esp4.c#L47">47</a>                 <a href="ident?i=len">len</a> += <a href="ident?i=crypto_aead_alignmask">crypto_aead_alignmask</a>(aead) &amp;
 <a name="L48" href="source/net/ipv4/esp4.c#L48">48</a>                        ~(<a href="ident?i=crypto_tfm_ctx_alignment">crypto_tfm_ctx_alignment</a>() - 1);
 <a name="L49" href="source/net/ipv4/esp4.c#L49">49</a>                 <a href="ident?i=len">len</a> = <a href="ident?i=ALIGN">ALIGN</a>(<a href="ident?i=len">len</a>, <a href="ident?i=crypto_tfm_ctx_alignment">crypto_tfm_ctx_alignment</a>());
 <a name="L50" href="source/net/ipv4/esp4.c#L50">50</a>         }
 <a name="L51" href="source/net/ipv4/esp4.c#L51">51</a> 
 <a name="L52" href="source/net/ipv4/esp4.c#L52">52</a>         <a href="ident?i=len">len</a> += sizeof(struct <a href="ident?i=aead_givcrypt_request">aead_givcrypt_request</a>) + <a href="ident?i=crypto_aead_reqsize">crypto_aead_reqsize</a>(aead);
 <a name="L53" href="source/net/ipv4/esp4.c#L53">53</a>         <a href="ident?i=len">len</a> = <a href="ident?i=ALIGN">ALIGN</a>(<a href="ident?i=len">len</a>, __alignof__(struct <a href="ident?i=scatterlist">scatterlist</a>));
 <a name="L54" href="source/net/ipv4/esp4.c#L54">54</a> 
 <a name="L55" href="source/net/ipv4/esp4.c#L55">55</a>         <a href="ident?i=len">len</a> += sizeof(struct <a href="ident?i=scatterlist">scatterlist</a>) * nfrags;
 <a name="L56" href="source/net/ipv4/esp4.c#L56">56</a> 
 <a name="L57" href="source/net/ipv4/esp4.c#L57">57</a>         return <a href="ident?i=kmalloc">kmalloc</a>(<a href="ident?i=len">len</a>, <a href="ident?i=GFP_ATOMIC">GFP_ATOMIC</a>);
 <a name="L58" href="source/net/ipv4/esp4.c#L58">58</a> }
 <a name="L59" href="source/net/ipv4/esp4.c#L59">59</a> 
 <a name="L60" href="source/net/ipv4/esp4.c#L60">60</a> static inline <a href="ident?i=__be32">__be32</a> *<a href="ident?i=esp_tmp_seqhi">esp_tmp_seqhi</a>(void *<a href="ident?i=tmp">tmp</a>)
 <a name="L61" href="source/net/ipv4/esp4.c#L61">61</a> {
 <a name="L62" href="source/net/ipv4/esp4.c#L62">62</a>         return <a href="ident?i=PTR_ALIGN">PTR_ALIGN</a>((<a href="ident?i=__be32">__be32</a> *)<a href="ident?i=tmp">tmp</a>, __alignof__(<a href="ident?i=__be32">__be32</a>));
 <a name="L63" href="source/net/ipv4/esp4.c#L63">63</a> }
 <a name="L64" href="source/net/ipv4/esp4.c#L64">64</a> static inline <a href="ident?i=u8">u8</a> *<a href="ident?i=esp_tmp_iv">esp_tmp_iv</a>(struct <a href="ident?i=crypto_aead">crypto_aead</a> *aead, void *<a href="ident?i=tmp">tmp</a>, int seqhilen)
 <a name="L65" href="source/net/ipv4/esp4.c#L65">65</a> {
 <a name="L66" href="source/net/ipv4/esp4.c#L66">66</a>         return <a href="ident?i=crypto_aead_ivsize">crypto_aead_ivsize</a>(aead) ?
 <a name="L67" href="source/net/ipv4/esp4.c#L67">67</a>                <a href="ident?i=PTR_ALIGN">PTR_ALIGN</a>((<a href="ident?i=u8">u8</a> *)<a href="ident?i=tmp">tmp</a> + seqhilen,
 <a name="L68" href="source/net/ipv4/esp4.c#L68">68</a>                          <a href="ident?i=crypto_aead_alignmask">crypto_aead_alignmask</a>(aead) + 1) : <a href="ident?i=tmp">tmp</a> + seqhilen;
 <a name="L69" href="source/net/ipv4/esp4.c#L69">69</a> }
 <a name="L70" href="source/net/ipv4/esp4.c#L70">70</a> 
 <a name="L71" href="source/net/ipv4/esp4.c#L71">71</a> static inline struct <a href="ident?i=aead_givcrypt_request">aead_givcrypt_request</a> *<a href="ident?i=esp_tmp_givreq">esp_tmp_givreq</a>(
 <a name="L72" href="source/net/ipv4/esp4.c#L72">72</a>         struct <a href="ident?i=crypto_aead">crypto_aead</a> *aead, <a href="ident?i=u8">u8</a> *iv)
 <a name="L73" href="source/net/ipv4/esp4.c#L73">73</a> {
 <a name="L74" href="source/net/ipv4/esp4.c#L74">74</a>         struct <a href="ident?i=aead_givcrypt_request">aead_givcrypt_request</a> *<a href="ident?i=req">req</a>;
 <a name="L75" href="source/net/ipv4/esp4.c#L75">75</a> 
 <a name="L76" href="source/net/ipv4/esp4.c#L76">76</a>         <a href="ident?i=req">req</a> = (void *)<a href="ident?i=PTR_ALIGN">PTR_ALIGN</a>(iv + <a href="ident?i=crypto_aead_ivsize">crypto_aead_ivsize</a>(aead),
 <a name="L77" href="source/net/ipv4/esp4.c#L77">77</a>                                 <a href="ident?i=crypto_tfm_ctx_alignment">crypto_tfm_ctx_alignment</a>());
 <a name="L78" href="source/net/ipv4/esp4.c#L78">78</a>         <a href="ident?i=aead_givcrypt_set_tfm">aead_givcrypt_set_tfm</a>(<a href="ident?i=req">req</a>, aead);
 <a name="L79" href="source/net/ipv4/esp4.c#L79">79</a>         return <a href="ident?i=req">req</a>;
 <a name="L80" href="source/net/ipv4/esp4.c#L80">80</a> }
 <a name="L81" href="source/net/ipv4/esp4.c#L81">81</a> 
 <a name="L82" href="source/net/ipv4/esp4.c#L82">82</a> static inline struct <a href="ident?i=aead_request">aead_request</a> *<a href="ident?i=esp_tmp_req">esp_tmp_req</a>(struct <a href="ident?i=crypto_aead">crypto_aead</a> *aead, <a href="ident?i=u8">u8</a> *iv)
 <a name="L83" href="source/net/ipv4/esp4.c#L83">83</a> {
 <a name="L84" href="source/net/ipv4/esp4.c#L84">84</a>         struct <a href="ident?i=aead_request">aead_request</a> *<a href="ident?i=req">req</a>;
 <a name="L85" href="source/net/ipv4/esp4.c#L85">85</a> 
 <a name="L86" href="source/net/ipv4/esp4.c#L86">86</a>         <a href="ident?i=req">req</a> = (void *)<a href="ident?i=PTR_ALIGN">PTR_ALIGN</a>(iv + <a href="ident?i=crypto_aead_ivsize">crypto_aead_ivsize</a>(aead),
 <a name="L87" href="source/net/ipv4/esp4.c#L87">87</a>                                 <a href="ident?i=crypto_tfm_ctx_alignment">crypto_tfm_ctx_alignment</a>());
 <a name="L88" href="source/net/ipv4/esp4.c#L88">88</a>         <a href="ident?i=aead_request_set_tfm">aead_request_set_tfm</a>(<a href="ident?i=req">req</a>, aead);
 <a name="L89" href="source/net/ipv4/esp4.c#L89">89</a>         return <a href="ident?i=req">req</a>;
 <a name="L90" href="source/net/ipv4/esp4.c#L90">90</a> }
 <a name="L91" href="source/net/ipv4/esp4.c#L91">91</a> 
 <a name="L92" href="source/net/ipv4/esp4.c#L92">92</a> static inline struct <a href="ident?i=scatterlist">scatterlist</a> *<a href="ident?i=esp_req_sg">esp_req_sg</a>(struct <a href="ident?i=crypto_aead">crypto_aead</a> *aead,
 <a name="L93" href="source/net/ipv4/esp4.c#L93">93</a>                                              struct <a href="ident?i=aead_request">aead_request</a> *<a href="ident?i=req">req</a>)
 <a name="L94" href="source/net/ipv4/esp4.c#L94">94</a> {
 <a name="L95" href="source/net/ipv4/esp4.c#L95">95</a>         return (void *)<a href="ident?i=ALIGN">ALIGN</a>((unsigned long)(<a href="ident?i=req">req</a> + 1) +
 <a name="L96" href="source/net/ipv4/esp4.c#L96">96</a>                              <a href="ident?i=crypto_aead_reqsize">crypto_aead_reqsize</a>(aead),
 <a name="L97" href="source/net/ipv4/esp4.c#L97">97</a>                              __alignof__(struct <a href="ident?i=scatterlist">scatterlist</a>));
 <a name="L98" href="source/net/ipv4/esp4.c#L98">98</a> }
 <a name="L99" href="source/net/ipv4/esp4.c#L99">99</a> 
<a name="L100" href="source/net/ipv4/esp4.c#L100">100</a> static inline struct <a href="ident?i=scatterlist">scatterlist</a> *<a href="ident?i=esp_givreq_sg">esp_givreq_sg</a>(
<a name="L101" href="source/net/ipv4/esp4.c#L101">101</a>         struct <a href="ident?i=crypto_aead">crypto_aead</a> *aead, struct <a href="ident?i=aead_givcrypt_request">aead_givcrypt_request</a> *<a href="ident?i=req">req</a>)
<a name="L102" href="source/net/ipv4/esp4.c#L102">102</a> {
<a name="L103" href="source/net/ipv4/esp4.c#L103">103</a>         return (void *)<a href="ident?i=ALIGN">ALIGN</a>((unsigned long)(<a href="ident?i=req">req</a> + 1) +
<a name="L104" href="source/net/ipv4/esp4.c#L104">104</a>                              <a href="ident?i=crypto_aead_reqsize">crypto_aead_reqsize</a>(aead),
<a name="L105" href="source/net/ipv4/esp4.c#L105">105</a>                              __alignof__(struct <a href="ident?i=scatterlist">scatterlist</a>));
<a name="L106" href="source/net/ipv4/esp4.c#L106">106</a> }
<a name="L107" href="source/net/ipv4/esp4.c#L107">107</a> 
<a name="L108" href="source/net/ipv4/esp4.c#L108">108</a> static void <a href="ident?i=esp_output_done">esp_output_done</a>(struct <a href="ident?i=crypto_async_request">crypto_async_request</a> *<a href="ident?i=base">base</a>, int <a href="ident?i=err">err</a>)
<a name="L109" href="source/net/ipv4/esp4.c#L109">109</a> {
<a name="L110" href="source/net/ipv4/esp4.c#L110">110</a>         struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a> = <a href="ident?i=base">base</a>-&gt;<a href="ident?i=data">data</a>;
<a name="L111" href="source/net/ipv4/esp4.c#L111">111</a> 
<a name="L112" href="source/net/ipv4/esp4.c#L112">112</a>         <a href="ident?i=kfree">kfree</a>(<a href="ident?i=ESP_SKB_CB">ESP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=tmp">tmp</a>);
<a name="L113" href="source/net/ipv4/esp4.c#L113">113</a>         <a href="ident?i=xfrm_output_resume">xfrm_output_resume</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=err">err</a>);
<a name="L114" href="source/net/ipv4/esp4.c#L114">114</a> }
<a name="L115" href="source/net/ipv4/esp4.c#L115">115</a> 
<a name="L116" href="source/net/ipv4/esp4.c#L116">116</a> static int <a href="ident?i=esp_output">esp_output</a>(struct <a href="ident?i=xfrm_state">xfrm_state</a> *<a href="ident?i=x">x</a>, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L117" href="source/net/ipv4/esp4.c#L117">117</a> {
<a name="L118" href="source/net/ipv4/esp4.c#L118">118</a>         int <a href="ident?i=err">err</a>;
<a name="L119" href="source/net/ipv4/esp4.c#L119">119</a>         struct <a href="ident?i=ip_esp_hdr">ip_esp_hdr</a> *esph;
<a name="L120" href="source/net/ipv4/esp4.c#L120">120</a>         struct <a href="ident?i=crypto_aead">crypto_aead</a> *aead;
<a name="L121" href="source/net/ipv4/esp4.c#L121">121</a>         struct <a href="ident?i=aead_givcrypt_request">aead_givcrypt_request</a> *<a href="ident?i=req">req</a>;
<a name="L122" href="source/net/ipv4/esp4.c#L122">122</a>         struct <a href="ident?i=scatterlist">scatterlist</a> *sg;
<a name="L123" href="source/net/ipv4/esp4.c#L123">123</a>         struct <a href="ident?i=scatterlist">scatterlist</a> *asg;
<a name="L124" href="source/net/ipv4/esp4.c#L124">124</a>         struct <a href="ident?i=sk_buff">sk_buff</a> *trailer;
<a name="L125" href="source/net/ipv4/esp4.c#L125">125</a>         void *<a href="ident?i=tmp">tmp</a>;
<a name="L126" href="source/net/ipv4/esp4.c#L126">126</a>         <a href="ident?i=u8">u8</a> *iv;
<a name="L127" href="source/net/ipv4/esp4.c#L127">127</a>         <a href="ident?i=u8">u8</a> *<a href="ident?i=tail">tail</a>;
<a name="L128" href="source/net/ipv4/esp4.c#L128">128</a>         int <a href="ident?i=blksize">blksize</a>;
<a name="L129" href="source/net/ipv4/esp4.c#L129">129</a>         int clen;
<a name="L130" href="source/net/ipv4/esp4.c#L130">130</a>         int alen;
<a name="L131" href="source/net/ipv4/esp4.c#L131">131</a>         int plen;
<a name="L132" href="source/net/ipv4/esp4.c#L132">132</a>         int tfclen;
<a name="L133" href="source/net/ipv4/esp4.c#L133">133</a>         int nfrags;
<a name="L134" href="source/net/ipv4/esp4.c#L134">134</a>         int assoclen;
<a name="L135" href="source/net/ipv4/esp4.c#L135">135</a>         int sglists;
<a name="L136" href="source/net/ipv4/esp4.c#L136">136</a>         int seqhilen;
<a name="L137" href="source/net/ipv4/esp4.c#L137">137</a>         <a href="ident?i=__be32">__be32</a> *seqhi;
<a name="L138" href="source/net/ipv4/esp4.c#L138">138</a> 
<a name="L139" href="source/net/ipv4/esp4.c#L139">139</a>         <b><i>/* skb is pure payload to encrypt */</i></b>
<a name="L140" href="source/net/ipv4/esp4.c#L140">140</a> 
<a name="L141" href="source/net/ipv4/esp4.c#L141">141</a>         aead = <a href="ident?i=x">x</a>-&gt;<a href="ident?i=data">data</a>;
<a name="L142" href="source/net/ipv4/esp4.c#L142">142</a>         alen = <a href="ident?i=crypto_aead_authsize">crypto_aead_authsize</a>(aead);
<a name="L143" href="source/net/ipv4/esp4.c#L143">143</a> 
<a name="L144" href="source/net/ipv4/esp4.c#L144">144</a>         tfclen = 0;
<a name="L145" href="source/net/ipv4/esp4.c#L145">145</a>         if (<a href="ident?i=x">x</a>-&gt;tfcpad) {
<a name="L146" href="source/net/ipv4/esp4.c#L146">146</a>                 struct <a href="ident?i=xfrm_dst">xfrm_dst</a> *<a href="ident?i=dst">dst</a> = (struct <a href="ident?i=xfrm_dst">xfrm_dst</a> *)<a href="ident?i=skb_dst">skb_dst</a>(<a href="ident?i=skb">skb</a>);
<a name="L147" href="source/net/ipv4/esp4.c#L147">147</a>                 <a href="ident?i=u32">u32</a> padto;
<a name="L148" href="source/net/ipv4/esp4.c#L148">148</a> 
<a name="L149" href="source/net/ipv4/esp4.c#L149">149</a>                 padto = <a href="ident?i=min">min</a>(<a href="ident?i=x">x</a>-&gt;tfcpad, <a href="ident?i=esp4_get_mtu">esp4_get_mtu</a>(<a href="ident?i=x">x</a>, <a href="ident?i=dst">dst</a>-&gt;child_mtu_cached));
<a name="L150" href="source/net/ipv4/esp4.c#L150">150</a>                 if (<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a> &lt; padto)
<a name="L151" href="source/net/ipv4/esp4.c#L151">151</a>                         tfclen = padto - <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a>;
<a name="L152" href="source/net/ipv4/esp4.c#L152">152</a>         }
<a name="L153" href="source/net/ipv4/esp4.c#L153">153</a>         <a href="ident?i=blksize">blksize</a> = <a href="ident?i=ALIGN">ALIGN</a>(<a href="ident?i=crypto_aead_blocksize">crypto_aead_blocksize</a>(aead), 4);
<a name="L154" href="source/net/ipv4/esp4.c#L154">154</a>         clen = <a href="ident?i=ALIGN">ALIGN</a>(<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a> + 2 + tfclen, <a href="ident?i=blksize">blksize</a>);
<a name="L155" href="source/net/ipv4/esp4.c#L155">155</a>         plen = clen - <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a> - tfclen;
<a name="L156" href="source/net/ipv4/esp4.c#L156">156</a> 
<a name="L157" href="source/net/ipv4/esp4.c#L157">157</a>         <a href="ident?i=err">err</a> = <a href="ident?i=skb_cow_data">skb_cow_data</a>(<a href="ident?i=skb">skb</a>, tfclen + plen + alen, &amp;trailer);
<a name="L158" href="source/net/ipv4/esp4.c#L158">158</a>         if (<a href="ident?i=err">err</a> &lt; 0)
<a name="L159" href="source/net/ipv4/esp4.c#L159">159</a>                 goto <a href="ident?i=error">error</a>;
<a name="L160" href="source/net/ipv4/esp4.c#L160">160</a>         nfrags = <a href="ident?i=err">err</a>;
<a name="L161" href="source/net/ipv4/esp4.c#L161">161</a> 
<a name="L162" href="source/net/ipv4/esp4.c#L162">162</a>         assoclen = sizeof(*esph);
<a name="L163" href="source/net/ipv4/esp4.c#L163">163</a>         sglists = 1;
<a name="L164" href="source/net/ipv4/esp4.c#L164">164</a>         seqhilen = 0;
<a name="L165" href="source/net/ipv4/esp4.c#L165">165</a> 
<a name="L166" href="source/net/ipv4/esp4.c#L166">166</a>         if (<a href="ident?i=x">x</a>-&gt;props.<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=XFRM_STATE_ESN">XFRM_STATE_ESN</a>) {
<a name="L167" href="source/net/ipv4/esp4.c#L167">167</a>                 sglists += 2;
<a name="L168" href="source/net/ipv4/esp4.c#L168">168</a>                 seqhilen += sizeof(<a href="ident?i=__be32">__be32</a>);
<a name="L169" href="source/net/ipv4/esp4.c#L169">169</a>                 assoclen += seqhilen;
<a name="L170" href="source/net/ipv4/esp4.c#L170">170</a>         }
<a name="L171" href="source/net/ipv4/esp4.c#L171">171</a> 
<a name="L172" href="source/net/ipv4/esp4.c#L172">172</a>         <a href="ident?i=tmp">tmp</a> = <a href="ident?i=esp_alloc_tmp">esp_alloc_tmp</a>(aead, nfrags + sglists, seqhilen);
<a name="L173" href="source/net/ipv4/esp4.c#L173">173</a>         if (!<a href="ident?i=tmp">tmp</a>) {
<a name="L174" href="source/net/ipv4/esp4.c#L174">174</a>                 <a href="ident?i=err">err</a> = -<a href="ident?i=ENOMEM">ENOMEM</a>;
<a name="L175" href="source/net/ipv4/esp4.c#L175">175</a>                 goto <a href="ident?i=error">error</a>;
<a name="L176" href="source/net/ipv4/esp4.c#L176">176</a>         }
<a name="L177" href="source/net/ipv4/esp4.c#L177">177</a> 
<a name="L178" href="source/net/ipv4/esp4.c#L178">178</a>         seqhi = <a href="ident?i=esp_tmp_seqhi">esp_tmp_seqhi</a>(<a href="ident?i=tmp">tmp</a>);
<a name="L179" href="source/net/ipv4/esp4.c#L179">179</a>         iv = <a href="ident?i=esp_tmp_iv">esp_tmp_iv</a>(aead, <a href="ident?i=tmp">tmp</a>, seqhilen);
<a name="L180" href="source/net/ipv4/esp4.c#L180">180</a>         <a href="ident?i=req">req</a> = <a href="ident?i=esp_tmp_givreq">esp_tmp_givreq</a>(aead, iv);
<a name="L181" href="source/net/ipv4/esp4.c#L181">181</a>         asg = <a href="ident?i=esp_givreq_sg">esp_givreq_sg</a>(aead, <a href="ident?i=req">req</a>);
<a name="L182" href="source/net/ipv4/esp4.c#L182">182</a>         sg = asg + sglists;
<a name="L183" href="source/net/ipv4/esp4.c#L183">183</a> 
<a name="L184" href="source/net/ipv4/esp4.c#L184">184</a>         <b><i>/* Fill padding... */</i></b>
<a name="L185" href="source/net/ipv4/esp4.c#L185">185</a>         <a href="ident?i=tail">tail</a> = <a href="ident?i=skb_tail_pointer">skb_tail_pointer</a>(trailer);
<a name="L186" href="source/net/ipv4/esp4.c#L186">186</a>         if (tfclen) {
<a name="L187" href="source/net/ipv4/esp4.c#L187">187</a>                 <a href="ident?i=memset">memset</a>(<a href="ident?i=tail">tail</a>, 0, tfclen);
<a name="L188" href="source/net/ipv4/esp4.c#L188">188</a>                 <a href="ident?i=tail">tail</a> += tfclen;
<a name="L189" href="source/net/ipv4/esp4.c#L189">189</a>         }
<a name="L190" href="source/net/ipv4/esp4.c#L190">190</a>         do {
<a name="L191" href="source/net/ipv4/esp4.c#L191">191</a>                 int <a href="ident?i=i">i</a>;
<a name="L192" href="source/net/ipv4/esp4.c#L192">192</a>                 for (<a href="ident?i=i">i</a> = 0; <a href="ident?i=i">i</a> &lt; plen - 2; <a href="ident?i=i">i</a>++)
<a name="L193" href="source/net/ipv4/esp4.c#L193">193</a>                         <a href="ident?i=tail">tail</a>[<a href="ident?i=i">i</a>] = <a href="ident?i=i">i</a> + 1;
<a name="L194" href="source/net/ipv4/esp4.c#L194">194</a>         } while (0);
<a name="L195" href="source/net/ipv4/esp4.c#L195">195</a>         <a href="ident?i=tail">tail</a>[plen - 2] = plen - 2;
<a name="L196" href="source/net/ipv4/esp4.c#L196">196</a>         <a href="ident?i=tail">tail</a>[plen - 1] = *<a href="ident?i=skb_mac_header">skb_mac_header</a>(<a href="ident?i=skb">skb</a>);
<a name="L197" href="source/net/ipv4/esp4.c#L197">197</a>         <a href="ident?i=pskb_put">pskb_put</a>(<a href="ident?i=skb">skb</a>, trailer, clen - <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a> + alen);
<a name="L198" href="source/net/ipv4/esp4.c#L198">198</a> 
<a name="L199" href="source/net/ipv4/esp4.c#L199">199</a>         <a href="ident?i=skb_push">skb_push</a>(<a href="ident?i=skb">skb</a>, -<a href="ident?i=skb_network_offset">skb_network_offset</a>(<a href="ident?i=skb">skb</a>));
<a name="L200" href="source/net/ipv4/esp4.c#L200">200</a>         esph = <a href="ident?i=ip_esp_hdr">ip_esp_hdr</a>(<a href="ident?i=skb">skb</a>);
<a name="L201" href="source/net/ipv4/esp4.c#L201">201</a>         *<a href="ident?i=skb_mac_header">skb_mac_header</a>(<a href="ident?i=skb">skb</a>) = <a href="ident?i=IPPROTO_ESP">IPPROTO_ESP</a>;
<a name="L202" href="source/net/ipv4/esp4.c#L202">202</a> 
<a name="L203" href="source/net/ipv4/esp4.c#L203">203</a>         <b><i>/* this is non-NULL only with UDP Encapsulation */</i></b>
<a name="L204" href="source/net/ipv4/esp4.c#L204">204</a>         if (<a href="ident?i=x">x</a>-&gt;encap) {
<a name="L205" href="source/net/ipv4/esp4.c#L205">205</a>                 struct <a href="ident?i=xfrm_encap_tmpl">xfrm_encap_tmpl</a> *encap = <a href="ident?i=x">x</a>-&gt;encap;
<a name="L206" href="source/net/ipv4/esp4.c#L206">206</a>                 struct <a href="ident?i=udphdr">udphdr</a> *uh;
<a name="L207" href="source/net/ipv4/esp4.c#L207">207</a>                 <a href="ident?i=__be32">__be32</a> *udpdata32;
<a name="L208" href="source/net/ipv4/esp4.c#L208">208</a>                 <a href="ident?i=__be16">__be16</a> sport, dport;
<a name="L209" href="source/net/ipv4/esp4.c#L209">209</a>                 int encap_type;
<a name="L210" href="source/net/ipv4/esp4.c#L210">210</a> 
<a name="L211" href="source/net/ipv4/esp4.c#L211">211</a>                 <a href="ident?i=spin_lock_bh">spin_lock_bh</a>(&amp;<a href="ident?i=x">x</a>-&gt;<a href="ident?i=lock">lock</a>);
<a name="L212" href="source/net/ipv4/esp4.c#L212">212</a>                 sport = encap-&gt;encap_sport;
<a name="L213" href="source/net/ipv4/esp4.c#L213">213</a>                 dport = encap-&gt;encap_dport;
<a name="L214" href="source/net/ipv4/esp4.c#L214">214</a>                 encap_type = encap-&gt;encap_type;
<a name="L215" href="source/net/ipv4/esp4.c#L215">215</a>                 <a href="ident?i=spin_unlock_bh">spin_unlock_bh</a>(&amp;<a href="ident?i=x">x</a>-&gt;<a href="ident?i=lock">lock</a>);
<a name="L216" href="source/net/ipv4/esp4.c#L216">216</a> 
<a name="L217" href="source/net/ipv4/esp4.c#L217">217</a>                 uh = (struct <a href="ident?i=udphdr">udphdr</a> *)esph;
<a name="L218" href="source/net/ipv4/esp4.c#L218">218</a>                 uh-&gt;source = sport;
<a name="L219" href="source/net/ipv4/esp4.c#L219">219</a>                 uh-&gt;<a href="ident?i=dest">dest</a> = dport;
<a name="L220" href="source/net/ipv4/esp4.c#L220">220</a>                 uh-&gt;<a href="ident?i=len">len</a> = <a href="ident?i=htons">htons</a>(<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a> - <a href="ident?i=skb_transport_offset">skb_transport_offset</a>(<a href="ident?i=skb">skb</a>));
<a name="L221" href="source/net/ipv4/esp4.c#L221">221</a>                 uh-&gt;<a href="ident?i=check">check</a> = 0;
<a name="L222" href="source/net/ipv4/esp4.c#L222">222</a> 
<a name="L223" href="source/net/ipv4/esp4.c#L223">223</a>                 switch (encap_type) {
<a name="L224" href="source/net/ipv4/esp4.c#L224">224</a>                 default:
<a name="L225" href="source/net/ipv4/esp4.c#L225">225</a>                 case <a href="ident?i=UDP_ENCAP_ESPINUDP">UDP_ENCAP_ESPINUDP</a>:
<a name="L226" href="source/net/ipv4/esp4.c#L226">226</a>                         esph = (struct <a href="ident?i=ip_esp_hdr">ip_esp_hdr</a> *)(uh + 1);
<a name="L227" href="source/net/ipv4/esp4.c#L227">227</a>                         break;
<a name="L228" href="source/net/ipv4/esp4.c#L228">228</a>                 case <a href="ident?i=UDP_ENCAP_ESPINUDP_NON_IKE">UDP_ENCAP_ESPINUDP_NON_IKE</a>:
<a name="L229" href="source/net/ipv4/esp4.c#L229">229</a>                         udpdata32 = (<a href="ident?i=__be32">__be32</a> *)(uh + 1);
<a name="L230" href="source/net/ipv4/esp4.c#L230">230</a>                         udpdata32[0] = udpdata32[1] = 0;
<a name="L231" href="source/net/ipv4/esp4.c#L231">231</a>                         esph = (struct <a href="ident?i=ip_esp_hdr">ip_esp_hdr</a> *)(udpdata32 + 2);
<a name="L232" href="source/net/ipv4/esp4.c#L232">232</a>                         break;
<a name="L233" href="source/net/ipv4/esp4.c#L233">233</a>                 }
<a name="L234" href="source/net/ipv4/esp4.c#L234">234</a> 
<a name="L235" href="source/net/ipv4/esp4.c#L235">235</a>                 *<a href="ident?i=skb_mac_header">skb_mac_header</a>(<a href="ident?i=skb">skb</a>) = <a href="ident?i=IPPROTO_UDP">IPPROTO_UDP</a>;
<a name="L236" href="source/net/ipv4/esp4.c#L236">236</a>         }
<a name="L237" href="source/net/ipv4/esp4.c#L237">237</a> 
<a name="L238" href="source/net/ipv4/esp4.c#L238">238</a>         esph-&gt;<a href="ident?i=spi">spi</a> = <a href="ident?i=x">x</a>-&gt;<a href="ident?i=id">id</a>.<a href="ident?i=spi">spi</a>;
<a name="L239" href="source/net/ipv4/esp4.c#L239">239</a>         esph-&gt;seq_no = <a href="ident?i=htonl">htonl</a>(<a href="ident?i=XFRM_SKB_CB">XFRM_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=seq">seq</a>.<a href="ident?i=output">output</a>.low);
<a name="L240" href="source/net/ipv4/esp4.c#L240">240</a> 
<a name="L241" href="source/net/ipv4/esp4.c#L241">241</a>         <a href="ident?i=sg_init_table">sg_init_table</a>(sg, nfrags);
<a name="L242" href="source/net/ipv4/esp4.c#L242">242</a>         <a href="ident?i=skb_to_sgvec">skb_to_sgvec</a>(<a href="ident?i=skb">skb</a>, sg,
<a name="L243" href="source/net/ipv4/esp4.c#L243">243</a>                      esph-&gt;enc_data + <a href="ident?i=crypto_aead_ivsize">crypto_aead_ivsize</a>(aead) - <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=data">data</a>,
<a name="L244" href="source/net/ipv4/esp4.c#L244">244</a>                      clen + alen);
<a name="L245" href="source/net/ipv4/esp4.c#L245">245</a> 
<a name="L246" href="source/net/ipv4/esp4.c#L246">246</a>         if ((<a href="ident?i=x">x</a>-&gt;props.<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=XFRM_STATE_ESN">XFRM_STATE_ESN</a>)) {
<a name="L247" href="source/net/ipv4/esp4.c#L247">247</a>                 <a href="ident?i=sg_init_table">sg_init_table</a>(asg, 3);
<a name="L248" href="source/net/ipv4/esp4.c#L248">248</a>                 <a href="ident?i=sg_set_buf">sg_set_buf</a>(asg, &amp;esph-&gt;<a href="ident?i=spi">spi</a>, sizeof(<a href="ident?i=__be32">__be32</a>));
<a name="L249" href="source/net/ipv4/esp4.c#L249">249</a>                 *seqhi = <a href="ident?i=htonl">htonl</a>(<a href="ident?i=XFRM_SKB_CB">XFRM_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=seq">seq</a>.<a href="ident?i=output">output</a>.<a href="ident?i=hi">hi</a>);
<a name="L250" href="source/net/ipv4/esp4.c#L250">250</a>                 <a href="ident?i=sg_set_buf">sg_set_buf</a>(asg + 1, seqhi, seqhilen);
<a name="L251" href="source/net/ipv4/esp4.c#L251">251</a>                 <a href="ident?i=sg_set_buf">sg_set_buf</a>(asg + 2, &amp;esph-&gt;seq_no, sizeof(<a href="ident?i=__be32">__be32</a>));
<a name="L252" href="source/net/ipv4/esp4.c#L252">252</a>         } else
<a name="L253" href="source/net/ipv4/esp4.c#L253">253</a>                 <a href="ident?i=sg_init_one">sg_init_one</a>(asg, esph, sizeof(*esph));
<a name="L254" href="source/net/ipv4/esp4.c#L254">254</a> 
<a name="L255" href="source/net/ipv4/esp4.c#L255">255</a>         <a href="ident?i=aead_givcrypt_set_callback">aead_givcrypt_set_callback</a>(<a href="ident?i=req">req</a>, 0, <a href="ident?i=esp_output_done">esp_output_done</a>, <a href="ident?i=skb">skb</a>);
<a name="L256" href="source/net/ipv4/esp4.c#L256">256</a>         <a href="ident?i=aead_givcrypt_set_crypt">aead_givcrypt_set_crypt</a>(<a href="ident?i=req">req</a>, sg, sg, clen, iv);
<a name="L257" href="source/net/ipv4/esp4.c#L257">257</a>         <a href="ident?i=aead_givcrypt_set_assoc">aead_givcrypt_set_assoc</a>(<a href="ident?i=req">req</a>, asg, assoclen);
<a name="L258" href="source/net/ipv4/esp4.c#L258">258</a>         <a href="ident?i=aead_givcrypt_set_giv">aead_givcrypt_set_giv</a>(<a href="ident?i=req">req</a>, esph-&gt;enc_data,
<a name="L259" href="source/net/ipv4/esp4.c#L259">259</a>                               <a href="ident?i=XFRM_SKB_CB">XFRM_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=seq">seq</a>.<a href="ident?i=output">output</a>.low +
<a name="L260" href="source/net/ipv4/esp4.c#L260">260</a>                               ((<a href="ident?i=u64">u64</a>)<a href="ident?i=XFRM_SKB_CB">XFRM_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=seq">seq</a>.<a href="ident?i=output">output</a>.<a href="ident?i=hi">hi</a> &lt;&lt; 32));
<a name="L261" href="source/net/ipv4/esp4.c#L261">261</a> 
<a name="L262" href="source/net/ipv4/esp4.c#L262">262</a>         <a href="ident?i=ESP_SKB_CB">ESP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=tmp">tmp</a> = <a href="ident?i=tmp">tmp</a>;
<a name="L263" href="source/net/ipv4/esp4.c#L263">263</a>         <a href="ident?i=err">err</a> = <a href="ident?i=crypto_aead_givencrypt">crypto_aead_givencrypt</a>(<a href="ident?i=req">req</a>);
<a name="L264" href="source/net/ipv4/esp4.c#L264">264</a>         if (<a href="ident?i=err">err</a> == -<a href="ident?i=EINPROGRESS">EINPROGRESS</a>)
<a name="L265" href="source/net/ipv4/esp4.c#L265">265</a>                 goto <a href="ident?i=error">error</a>;
<a name="L266" href="source/net/ipv4/esp4.c#L266">266</a> 
<a name="L267" href="source/net/ipv4/esp4.c#L267">267</a>         if (<a href="ident?i=err">err</a> == -<a href="ident?i=EBUSY">EBUSY</a>)
<a name="L268" href="source/net/ipv4/esp4.c#L268">268</a>                 <a href="ident?i=err">err</a> = <a href="ident?i=NET_XMIT_DROP">NET_XMIT_DROP</a>;
<a name="L269" href="source/net/ipv4/esp4.c#L269">269</a> 
<a name="L270" href="source/net/ipv4/esp4.c#L270">270</a>         <a href="ident?i=kfree">kfree</a>(<a href="ident?i=tmp">tmp</a>);
<a name="L271" href="source/net/ipv4/esp4.c#L271">271</a> 
<a name="L272" href="source/net/ipv4/esp4.c#L272">272</a> <a href="ident?i=error">error</a>:
<a name="L273" href="source/net/ipv4/esp4.c#L273">273</a>         return <a href="ident?i=err">err</a>;
<a name="L274" href="source/net/ipv4/esp4.c#L274">274</a> }
<a name="L275" href="source/net/ipv4/esp4.c#L275">275</a> 
<a name="L276" href="source/net/ipv4/esp4.c#L276">276</a> static int <a href="ident?i=esp_input_done2">esp_input_done2</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, int <a href="ident?i=err">err</a>)
<a name="L277" href="source/net/ipv4/esp4.c#L277">277</a> {
<a name="L278" href="source/net/ipv4/esp4.c#L278">278</a>         const struct <a href="ident?i=iphdr">iphdr</a> *iph;
<a name="L279" href="source/net/ipv4/esp4.c#L279">279</a>         struct <a href="ident?i=xfrm_state">xfrm_state</a> *<a href="ident?i=x">x</a> = <a href="ident?i=xfrm_input_state">xfrm_input_state</a>(<a href="ident?i=skb">skb</a>);
<a name="L280" href="source/net/ipv4/esp4.c#L280">280</a>         struct <a href="ident?i=crypto_aead">crypto_aead</a> *aead = <a href="ident?i=x">x</a>-&gt;<a href="ident?i=data">data</a>;
<a name="L281" href="source/net/ipv4/esp4.c#L281">281</a>         int alen = <a href="ident?i=crypto_aead_authsize">crypto_aead_authsize</a>(aead);
<a name="L282" href="source/net/ipv4/esp4.c#L282">282</a>         int hlen = sizeof(struct <a href="ident?i=ip_esp_hdr">ip_esp_hdr</a>) + <a href="ident?i=crypto_aead_ivsize">crypto_aead_ivsize</a>(aead);
<a name="L283" href="source/net/ipv4/esp4.c#L283">283</a>         int elen = <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a> - hlen;
<a name="L284" href="source/net/ipv4/esp4.c#L284">284</a>         int ihl;
<a name="L285" href="source/net/ipv4/esp4.c#L285">285</a>         <a href="ident?i=u8">u8</a> nexthdr[2];
<a name="L286" href="source/net/ipv4/esp4.c#L286">286</a>         int padlen;
<a name="L287" href="source/net/ipv4/esp4.c#L287">287</a> 
<a name="L288" href="source/net/ipv4/esp4.c#L288">288</a>         <a href="ident?i=kfree">kfree</a>(<a href="ident?i=ESP_SKB_CB">ESP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=tmp">tmp</a>);
<a name="L289" href="source/net/ipv4/esp4.c#L289">289</a> 
<a name="L290" href="source/net/ipv4/esp4.c#L290">290</a>         if (<a href="ident?i=unlikely">unlikely</a>(<a href="ident?i=err">err</a>))
<a name="L291" href="source/net/ipv4/esp4.c#L291">291</a>                 goto <a href="ident?i=out">out</a>;
<a name="L292" href="source/net/ipv4/esp4.c#L292">292</a> 
<a name="L293" href="source/net/ipv4/esp4.c#L293">293</a>         if (<a href="ident?i=skb_copy_bits">skb_copy_bits</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a>-alen-2, nexthdr, 2))
<a name="L294" href="source/net/ipv4/esp4.c#L294">294</a>                 <a href="ident?i=BUG">BUG</a>();
<a name="L295" href="source/net/ipv4/esp4.c#L295">295</a> 
<a name="L296" href="source/net/ipv4/esp4.c#L296">296</a>         <a href="ident?i=err">err</a> = -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L297" href="source/net/ipv4/esp4.c#L297">297</a>         padlen = nexthdr[0];
<a name="L298" href="source/net/ipv4/esp4.c#L298">298</a>         if (padlen + 2 + alen &gt;= elen)
<a name="L299" href="source/net/ipv4/esp4.c#L299">299</a>                 goto <a href="ident?i=out">out</a>;
<a name="L300" href="source/net/ipv4/esp4.c#L300">300</a> 
<a name="L301" href="source/net/ipv4/esp4.c#L301">301</a>         <b><i>/* ... check padding bits here. Silly. :-) */</i></b>
<a name="L302" href="source/net/ipv4/esp4.c#L302">302</a> 
<a name="L303" href="source/net/ipv4/esp4.c#L303">303</a>         iph = <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>);
<a name="L304" href="source/net/ipv4/esp4.c#L304">304</a>         ihl = iph-&gt;ihl * 4;
<a name="L305" href="source/net/ipv4/esp4.c#L305">305</a> 
<a name="L306" href="source/net/ipv4/esp4.c#L306">306</a>         if (<a href="ident?i=x">x</a>-&gt;encap) {
<a name="L307" href="source/net/ipv4/esp4.c#L307">307</a>                 struct <a href="ident?i=xfrm_encap_tmpl">xfrm_encap_tmpl</a> *encap = <a href="ident?i=x">x</a>-&gt;encap;
<a name="L308" href="source/net/ipv4/esp4.c#L308">308</a>                 struct <a href="ident?i=udphdr">udphdr</a> *uh = (void *)(<a href="ident?i=skb_network_header">skb_network_header</a>(<a href="ident?i=skb">skb</a>) + ihl);
<a name="L309" href="source/net/ipv4/esp4.c#L309">309</a> 
<a name="L310" href="source/net/ipv4/esp4.c#L310">310</a>                 <b><i>/*</i></b>
<a name="L311" href="source/net/ipv4/esp4.c#L311">311</a> <b><i>                 * 1) if the NAT-T peer's IP or port changed then</i></b>
<a name="L312" href="source/net/ipv4/esp4.c#L312">312</a> <b><i>                 *    advertize the change to the keying daemon.</i></b>
<a name="L313" href="source/net/ipv4/esp4.c#L313">313</a> <b><i>                 *    This is an inbound SA, so just compare</i></b>
<a name="L314" href="source/net/ipv4/esp4.c#L314">314</a> <b><i>                 *    SRC ports.</i></b>
<a name="L315" href="source/net/ipv4/esp4.c#L315">315</a> <b><i>                 */</i></b>
<a name="L316" href="source/net/ipv4/esp4.c#L316">316</a>                 if (iph-&gt;<a href="ident?i=saddr">saddr</a> != <a href="ident?i=x">x</a>-&gt;props.<a href="ident?i=saddr">saddr</a>.<a href="ident?i=a4">a4</a> ||
<a name="L317" href="source/net/ipv4/esp4.c#L317">317</a>                     uh-&gt;source != encap-&gt;encap_sport) {
<a name="L318" href="source/net/ipv4/esp4.c#L318">318</a>                         <a href="ident?i=xfrm_address_t">xfrm_address_t</a> ipaddr;
<a name="L319" href="source/net/ipv4/esp4.c#L319">319</a> 
<a name="L320" href="source/net/ipv4/esp4.c#L320">320</a>                         ipaddr.<a href="ident?i=a4">a4</a> = iph-&gt;<a href="ident?i=saddr">saddr</a>;
<a name="L321" href="source/net/ipv4/esp4.c#L321">321</a>                         <a href="ident?i=km_new_mapping">km_new_mapping</a>(<a href="ident?i=x">x</a>, &amp;ipaddr, uh-&gt;source);
<a name="L322" href="source/net/ipv4/esp4.c#L322">322</a> 
<a name="L323" href="source/net/ipv4/esp4.c#L323">323</a>                         <b><i>/* XXX: perhaps add an extra</i></b>
<a name="L324" href="source/net/ipv4/esp4.c#L324">324</a> <b><i>                         * policy check here, to see</i></b>
<a name="L325" href="source/net/ipv4/esp4.c#L325">325</a> <b><i>                         * if we should allow or</i></b>
<a name="L326" href="source/net/ipv4/esp4.c#L326">326</a> <b><i>                         * reject a packet from a</i></b>
<a name="L327" href="source/net/ipv4/esp4.c#L327">327</a> <b><i>                         * different source</i></b>
<a name="L328" href="source/net/ipv4/esp4.c#L328">328</a> <b><i>                         * address/port.</i></b>
<a name="L329" href="source/net/ipv4/esp4.c#L329">329</a> <b><i>                         */</i></b>
<a name="L330" href="source/net/ipv4/esp4.c#L330">330</a>                 }
<a name="L331" href="source/net/ipv4/esp4.c#L331">331</a> 
<a name="L332" href="source/net/ipv4/esp4.c#L332">332</a>                 <b><i>/*</i></b>
<a name="L333" href="source/net/ipv4/esp4.c#L333">333</a> <b><i>                 * 2) ignore UDP/TCP checksums in case</i></b>
<a name="L334" href="source/net/ipv4/esp4.c#L334">334</a> <b><i>                 *    of NAT-T in Transport Mode, or</i></b>
<a name="L335" href="source/net/ipv4/esp4.c#L335">335</a> <b><i>                 *    perform other post-processing fixes</i></b>
<a name="L336" href="source/net/ipv4/esp4.c#L336">336</a> <b><i>                 *    as per draft-ietf-ipsec-udp-encaps-06,</i></b>
<a name="L337" href="source/net/ipv4/esp4.c#L337">337</a> <b><i>                 *    section 3.1.2</i></b>
<a name="L338" href="source/net/ipv4/esp4.c#L338">338</a> <b><i>                 */</i></b>
<a name="L339" href="source/net/ipv4/esp4.c#L339">339</a>                 if (<a href="ident?i=x">x</a>-&gt;props.<a href="ident?i=mode">mode</a> == <a href="ident?i=XFRM_MODE_TRANSPORT">XFRM_MODE_TRANSPORT</a>)
<a name="L340" href="source/net/ipv4/esp4.c#L340">340</a>                         <a href="ident?i=skb">skb</a>-&gt;ip_summed = <a href="ident?i=CHECKSUM_UNNECESSARY">CHECKSUM_UNNECESSARY</a>;
<a name="L341" href="source/net/ipv4/esp4.c#L341">341</a>         }
<a name="L342" href="source/net/ipv4/esp4.c#L342">342</a> 
<a name="L343" href="source/net/ipv4/esp4.c#L343">343</a>         <a href="ident?i=pskb_trim">pskb_trim</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a> - alen - padlen - 2);
<a name="L344" href="source/net/ipv4/esp4.c#L344">344</a>         <a href="ident?i=__skb_pull">__skb_pull</a>(<a href="ident?i=skb">skb</a>, hlen);
<a name="L345" href="source/net/ipv4/esp4.c#L345">345</a>         if (<a href="ident?i=x">x</a>-&gt;props.<a href="ident?i=mode">mode</a> == <a href="ident?i=XFRM_MODE_TUNNEL">XFRM_MODE_TUNNEL</a>)
<a name="L346" href="source/net/ipv4/esp4.c#L346">346</a>                 <a href="ident?i=skb_reset_transport_header">skb_reset_transport_header</a>(<a href="ident?i=skb">skb</a>);
<a name="L347" href="source/net/ipv4/esp4.c#L347">347</a>         else
<a name="L348" href="source/net/ipv4/esp4.c#L348">348</a>                 <a href="ident?i=skb_set_transport_header">skb_set_transport_header</a>(<a href="ident?i=skb">skb</a>, -ihl);
<a name="L349" href="source/net/ipv4/esp4.c#L349">349</a> 
<a name="L350" href="source/net/ipv4/esp4.c#L350">350</a>         <a href="ident?i=err">err</a> = nexthdr[1];
<a name="L351" href="source/net/ipv4/esp4.c#L351">351</a> 
<a name="L352" href="source/net/ipv4/esp4.c#L352">352</a>         <b><i>/* RFC4303: Drop dummy packets without any error */</i></b>
<a name="L353" href="source/net/ipv4/esp4.c#L353">353</a>         if (<a href="ident?i=err">err</a> == <a href="ident?i=IPPROTO_NONE">IPPROTO_NONE</a>)
<a name="L354" href="source/net/ipv4/esp4.c#L354">354</a>                 <a href="ident?i=err">err</a> = -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L355" href="source/net/ipv4/esp4.c#L355">355</a> 
<a name="L356" href="source/net/ipv4/esp4.c#L356">356</a> <a href="ident?i=out">out</a>:
<a name="L357" href="source/net/ipv4/esp4.c#L357">357</a>         return <a href="ident?i=err">err</a>;
<a name="L358" href="source/net/ipv4/esp4.c#L358">358</a> }
<a name="L359" href="source/net/ipv4/esp4.c#L359">359</a> 
<a name="L360" href="source/net/ipv4/esp4.c#L360">360</a> static void <a href="ident?i=esp_input_done">esp_input_done</a>(struct <a href="ident?i=crypto_async_request">crypto_async_request</a> *<a href="ident?i=base">base</a>, int <a href="ident?i=err">err</a>)
<a name="L361" href="source/net/ipv4/esp4.c#L361">361</a> {
<a name="L362" href="source/net/ipv4/esp4.c#L362">362</a>         struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a> = <a href="ident?i=base">base</a>-&gt;<a href="ident?i=data">data</a>;
<a name="L363" href="source/net/ipv4/esp4.c#L363">363</a> 
<a name="L364" href="source/net/ipv4/esp4.c#L364">364</a>         <a href="ident?i=xfrm_input_resume">xfrm_input_resume</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=esp_input_done2">esp_input_done2</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=err">err</a>));
<a name="L365" href="source/net/ipv4/esp4.c#L365">365</a> }
<a name="L366" href="source/net/ipv4/esp4.c#L366">366</a> 
<a name="L367" href="source/net/ipv4/esp4.c#L367">367</a> <b><i>/*</i></b>
<a name="L368" href="source/net/ipv4/esp4.c#L368">368</a> <b><i> * Note: detecting truncated vs. non-truncated authentication data is very</i></b>
<a name="L369" href="source/net/ipv4/esp4.c#L369">369</a> <b><i> * expensive, so we only support truncated data, which is the recommended</i></b>
<a name="L370" href="source/net/ipv4/esp4.c#L370">370</a> <b><i> * and common case.</i></b>
<a name="L371" href="source/net/ipv4/esp4.c#L371">371</a> <b><i> */</i></b>
<a name="L372" href="source/net/ipv4/esp4.c#L372">372</a> static int <a href="ident?i=esp_input">esp_input</a>(struct <a href="ident?i=xfrm_state">xfrm_state</a> *<a href="ident?i=x">x</a>, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L373" href="source/net/ipv4/esp4.c#L373">373</a> {
<a name="L374" href="source/net/ipv4/esp4.c#L374">374</a>         struct <a href="ident?i=ip_esp_hdr">ip_esp_hdr</a> *esph;
<a name="L375" href="source/net/ipv4/esp4.c#L375">375</a>         struct <a href="ident?i=crypto_aead">crypto_aead</a> *aead = <a href="ident?i=x">x</a>-&gt;<a href="ident?i=data">data</a>;
<a name="L376" href="source/net/ipv4/esp4.c#L376">376</a>         struct <a href="ident?i=aead_request">aead_request</a> *<a href="ident?i=req">req</a>;
<a name="L377" href="source/net/ipv4/esp4.c#L377">377</a>         struct <a href="ident?i=sk_buff">sk_buff</a> *trailer;
<a name="L378" href="source/net/ipv4/esp4.c#L378">378</a>         int elen = <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a> - sizeof(*esph) - <a href="ident?i=crypto_aead_ivsize">crypto_aead_ivsize</a>(aead);
<a name="L379" href="source/net/ipv4/esp4.c#L379">379</a>         int nfrags;
<a name="L380" href="source/net/ipv4/esp4.c#L380">380</a>         int assoclen;
<a name="L381" href="source/net/ipv4/esp4.c#L381">381</a>         int sglists;
<a name="L382" href="source/net/ipv4/esp4.c#L382">382</a>         int seqhilen;
<a name="L383" href="source/net/ipv4/esp4.c#L383">383</a>         <a href="ident?i=__be32">__be32</a> *seqhi;
<a name="L384" href="source/net/ipv4/esp4.c#L384">384</a>         void *<a href="ident?i=tmp">tmp</a>;
<a name="L385" href="source/net/ipv4/esp4.c#L385">385</a>         <a href="ident?i=u8">u8</a> *iv;
<a name="L386" href="source/net/ipv4/esp4.c#L386">386</a>         struct <a href="ident?i=scatterlist">scatterlist</a> *sg;
<a name="L387" href="source/net/ipv4/esp4.c#L387">387</a>         struct <a href="ident?i=scatterlist">scatterlist</a> *asg;
<a name="L388" href="source/net/ipv4/esp4.c#L388">388</a>         int <a href="ident?i=err">err</a> = -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L389" href="source/net/ipv4/esp4.c#L389">389</a> 
<a name="L390" href="source/net/ipv4/esp4.c#L390">390</a>         if (!<a href="ident?i=pskb_may_pull">pskb_may_pull</a>(<a href="ident?i=skb">skb</a>, sizeof(*esph) + <a href="ident?i=crypto_aead_ivsize">crypto_aead_ivsize</a>(aead)))
<a name="L391" href="source/net/ipv4/esp4.c#L391">391</a>                 goto <a href="ident?i=out">out</a>;
<a name="L392" href="source/net/ipv4/esp4.c#L392">392</a> 
<a name="L393" href="source/net/ipv4/esp4.c#L393">393</a>         if (elen &lt;= 0)
<a name="L394" href="source/net/ipv4/esp4.c#L394">394</a>                 goto <a href="ident?i=out">out</a>;
<a name="L395" href="source/net/ipv4/esp4.c#L395">395</a> 
<a name="L396" href="source/net/ipv4/esp4.c#L396">396</a>         <a href="ident?i=err">err</a> = <a href="ident?i=skb_cow_data">skb_cow_data</a>(<a href="ident?i=skb">skb</a>, 0, &amp;trailer);
<a name="L397" href="source/net/ipv4/esp4.c#L397">397</a>         if (<a href="ident?i=err">err</a> &lt; 0)
<a name="L398" href="source/net/ipv4/esp4.c#L398">398</a>                 goto <a href="ident?i=out">out</a>;
<a name="L399" href="source/net/ipv4/esp4.c#L399">399</a> 
<a name="L400" href="source/net/ipv4/esp4.c#L400">400</a>         nfrags = <a href="ident?i=err">err</a>;
<a name="L401" href="source/net/ipv4/esp4.c#L401">401</a> 
<a name="L402" href="source/net/ipv4/esp4.c#L402">402</a>         assoclen = sizeof(*esph);
<a name="L403" href="source/net/ipv4/esp4.c#L403">403</a>         sglists = 1;
<a name="L404" href="source/net/ipv4/esp4.c#L404">404</a>         seqhilen = 0;
<a name="L405" href="source/net/ipv4/esp4.c#L405">405</a> 
<a name="L406" href="source/net/ipv4/esp4.c#L406">406</a>         if (<a href="ident?i=x">x</a>-&gt;props.<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=XFRM_STATE_ESN">XFRM_STATE_ESN</a>) {
<a name="L407" href="source/net/ipv4/esp4.c#L407">407</a>                 sglists += 2;
<a name="L408" href="source/net/ipv4/esp4.c#L408">408</a>                 seqhilen += sizeof(<a href="ident?i=__be32">__be32</a>);
<a name="L409" href="source/net/ipv4/esp4.c#L409">409</a>                 assoclen += seqhilen;
<a name="L410" href="source/net/ipv4/esp4.c#L410">410</a>         }
<a name="L411" href="source/net/ipv4/esp4.c#L411">411</a> 
<a name="L412" href="source/net/ipv4/esp4.c#L412">412</a>         <a href="ident?i=err">err</a> = -<a href="ident?i=ENOMEM">ENOMEM</a>;
<a name="L413" href="source/net/ipv4/esp4.c#L413">413</a>         <a href="ident?i=tmp">tmp</a> = <a href="ident?i=esp_alloc_tmp">esp_alloc_tmp</a>(aead, nfrags + sglists, seqhilen);
<a name="L414" href="source/net/ipv4/esp4.c#L414">414</a>         if (!<a href="ident?i=tmp">tmp</a>)
<a name="L415" href="source/net/ipv4/esp4.c#L415">415</a>                 goto <a href="ident?i=out">out</a>;
<a name="L416" href="source/net/ipv4/esp4.c#L416">416</a> 
<a name="L417" href="source/net/ipv4/esp4.c#L417">417</a>         <a href="ident?i=ESP_SKB_CB">ESP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=tmp">tmp</a> = <a href="ident?i=tmp">tmp</a>;
<a name="L418" href="source/net/ipv4/esp4.c#L418">418</a>         seqhi = <a href="ident?i=esp_tmp_seqhi">esp_tmp_seqhi</a>(<a href="ident?i=tmp">tmp</a>);
<a name="L419" href="source/net/ipv4/esp4.c#L419">419</a>         iv = <a href="ident?i=esp_tmp_iv">esp_tmp_iv</a>(aead, <a href="ident?i=tmp">tmp</a>, seqhilen);
<a name="L420" href="source/net/ipv4/esp4.c#L420">420</a>         <a href="ident?i=req">req</a> = <a href="ident?i=esp_tmp_req">esp_tmp_req</a>(aead, iv);
<a name="L421" href="source/net/ipv4/esp4.c#L421">421</a>         asg = <a href="ident?i=esp_req_sg">esp_req_sg</a>(aead, <a href="ident?i=req">req</a>);
<a name="L422" href="source/net/ipv4/esp4.c#L422">422</a>         sg = asg + sglists;
<a name="L423" href="source/net/ipv4/esp4.c#L423">423</a> 
<a name="L424" href="source/net/ipv4/esp4.c#L424">424</a>         <a href="ident?i=skb">skb</a>-&gt;ip_summed = <a href="ident?i=CHECKSUM_NONE">CHECKSUM_NONE</a>;
<a name="L425" href="source/net/ipv4/esp4.c#L425">425</a> 
<a name="L426" href="source/net/ipv4/esp4.c#L426">426</a>         esph = (struct <a href="ident?i=ip_esp_hdr">ip_esp_hdr</a> *)<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=data">data</a>;
<a name="L427" href="source/net/ipv4/esp4.c#L427">427</a> 
<a name="L428" href="source/net/ipv4/esp4.c#L428">428</a>         <b><i>/* Get ivec. This can be wrong, check against another impls. */</i></b>
<a name="L429" href="source/net/ipv4/esp4.c#L429">429</a>         iv = esph-&gt;enc_data;
<a name="L430" href="source/net/ipv4/esp4.c#L430">430</a> 
<a name="L431" href="source/net/ipv4/esp4.c#L431">431</a>         <a href="ident?i=sg_init_table">sg_init_table</a>(sg, nfrags);
<a name="L432" href="source/net/ipv4/esp4.c#L432">432</a>         <a href="ident?i=skb_to_sgvec">skb_to_sgvec</a>(<a href="ident?i=skb">skb</a>, sg, sizeof(*esph) + <a href="ident?i=crypto_aead_ivsize">crypto_aead_ivsize</a>(aead), elen);
<a name="L433" href="source/net/ipv4/esp4.c#L433">433</a> 
<a name="L434" href="source/net/ipv4/esp4.c#L434">434</a>         if ((<a href="ident?i=x">x</a>-&gt;props.<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=XFRM_STATE_ESN">XFRM_STATE_ESN</a>)) {
<a name="L435" href="source/net/ipv4/esp4.c#L435">435</a>                 <a href="ident?i=sg_init_table">sg_init_table</a>(asg, 3);
<a name="L436" href="source/net/ipv4/esp4.c#L436">436</a>                 <a href="ident?i=sg_set_buf">sg_set_buf</a>(asg, &amp;esph-&gt;<a href="ident?i=spi">spi</a>, sizeof(<a href="ident?i=__be32">__be32</a>));
<a name="L437" href="source/net/ipv4/esp4.c#L437">437</a>                 *seqhi = <a href="ident?i=XFRM_SKB_CB">XFRM_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=seq">seq</a>.<a href="ident?i=input">input</a>.<a href="ident?i=hi">hi</a>;
<a name="L438" href="source/net/ipv4/esp4.c#L438">438</a>                 <a href="ident?i=sg_set_buf">sg_set_buf</a>(asg + 1, seqhi, seqhilen);
<a name="L439" href="source/net/ipv4/esp4.c#L439">439</a>                 <a href="ident?i=sg_set_buf">sg_set_buf</a>(asg + 2, &amp;esph-&gt;seq_no, sizeof(<a href="ident?i=__be32">__be32</a>));
<a name="L440" href="source/net/ipv4/esp4.c#L440">440</a>         } else
<a name="L441" href="source/net/ipv4/esp4.c#L441">441</a>                 <a href="ident?i=sg_init_one">sg_init_one</a>(asg, esph, sizeof(*esph));
<a name="L442" href="source/net/ipv4/esp4.c#L442">442</a> 
<a name="L443" href="source/net/ipv4/esp4.c#L443">443</a>         <a href="ident?i=aead_request_set_callback">aead_request_set_callback</a>(<a href="ident?i=req">req</a>, 0, <a href="ident?i=esp_input_done">esp_input_done</a>, <a href="ident?i=skb">skb</a>);
<a name="L444" href="source/net/ipv4/esp4.c#L444">444</a>         <a href="ident?i=aead_request_set_crypt">aead_request_set_crypt</a>(<a href="ident?i=req">req</a>, sg, sg, elen, iv);
<a name="L445" href="source/net/ipv4/esp4.c#L445">445</a>         <a href="ident?i=aead_request_set_assoc">aead_request_set_assoc</a>(<a href="ident?i=req">req</a>, asg, assoclen);
<a name="L446" href="source/net/ipv4/esp4.c#L446">446</a> 
<a name="L447" href="source/net/ipv4/esp4.c#L447">447</a>         <a href="ident?i=err">err</a> = <a href="ident?i=crypto_aead_decrypt">crypto_aead_decrypt</a>(<a href="ident?i=req">req</a>);
<a name="L448" href="source/net/ipv4/esp4.c#L448">448</a>         if (<a href="ident?i=err">err</a> == -<a href="ident?i=EINPROGRESS">EINPROGRESS</a>)
<a name="L449" href="source/net/ipv4/esp4.c#L449">449</a>                 goto <a href="ident?i=out">out</a>;
<a name="L450" href="source/net/ipv4/esp4.c#L450">450</a> 
<a name="L451" href="source/net/ipv4/esp4.c#L451">451</a>         <a href="ident?i=err">err</a> = <a href="ident?i=esp_input_done2">esp_input_done2</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=err">err</a>);
<a name="L452" href="source/net/ipv4/esp4.c#L452">452</a> 
<a name="L453" href="source/net/ipv4/esp4.c#L453">453</a> <a href="ident?i=out">out</a>:
<a name="L454" href="source/net/ipv4/esp4.c#L454">454</a>         return <a href="ident?i=err">err</a>;
<a name="L455" href="source/net/ipv4/esp4.c#L455">455</a> }
<a name="L456" href="source/net/ipv4/esp4.c#L456">456</a> 
<a name="L457" href="source/net/ipv4/esp4.c#L457">457</a> static <a href="ident?i=u32">u32</a> <a href="ident?i=esp4_get_mtu">esp4_get_mtu</a>(struct <a href="ident?i=xfrm_state">xfrm_state</a> *<a href="ident?i=x">x</a>, int <a href="ident?i=mtu">mtu</a>)
<a name="L458" href="source/net/ipv4/esp4.c#L458">458</a> {
<a name="L459" href="source/net/ipv4/esp4.c#L459">459</a>         struct <a href="ident?i=crypto_aead">crypto_aead</a> *aead = <a href="ident?i=x">x</a>-&gt;<a href="ident?i=data">data</a>;
<a name="L460" href="source/net/ipv4/esp4.c#L460">460</a>         <a href="ident?i=u32">u32</a> <a href="ident?i=blksize">blksize</a> = <a href="ident?i=ALIGN">ALIGN</a>(<a href="ident?i=crypto_aead_blocksize">crypto_aead_blocksize</a>(aead), 4);
<a name="L461" href="source/net/ipv4/esp4.c#L461">461</a>         unsigned int net_adj;
<a name="L462" href="source/net/ipv4/esp4.c#L462">462</a> 
<a name="L463" href="source/net/ipv4/esp4.c#L463">463</a>         switch (<a href="ident?i=x">x</a>-&gt;props.<a href="ident?i=mode">mode</a>) {
<a name="L464" href="source/net/ipv4/esp4.c#L464">464</a>         case <a href="ident?i=XFRM_MODE_TRANSPORT">XFRM_MODE_TRANSPORT</a>:
<a name="L465" href="source/net/ipv4/esp4.c#L465">465</a>         case <a href="ident?i=XFRM_MODE_BEET">XFRM_MODE_BEET</a>:
<a name="L466" href="source/net/ipv4/esp4.c#L466">466</a>                 net_adj = sizeof(struct <a href="ident?i=iphdr">iphdr</a>);
<a name="L467" href="source/net/ipv4/esp4.c#L467">467</a>                 break;
<a name="L468" href="source/net/ipv4/esp4.c#L468">468</a>         case <a href="ident?i=XFRM_MODE_TUNNEL">XFRM_MODE_TUNNEL</a>:
<a name="L469" href="source/net/ipv4/esp4.c#L469">469</a>                 net_adj = 0;
<a name="L470" href="source/net/ipv4/esp4.c#L470">470</a>                 break;
<a name="L471" href="source/net/ipv4/esp4.c#L471">471</a>         default:
<a name="L472" href="source/net/ipv4/esp4.c#L472">472</a>                 <a href="ident?i=BUG">BUG</a>();
<a name="L473" href="source/net/ipv4/esp4.c#L473">473</a>         }
<a name="L474" href="source/net/ipv4/esp4.c#L474">474</a> 
<a name="L475" href="source/net/ipv4/esp4.c#L475">475</a>         return ((<a href="ident?i=mtu">mtu</a> - <a href="ident?i=x">x</a>-&gt;props.<a href="ident?i=header_len">header_len</a> - <a href="ident?i=crypto_aead_authsize">crypto_aead_authsize</a>(aead) -
<a name="L476" href="source/net/ipv4/esp4.c#L476">476</a>                  net_adj) &amp; ~(<a href="ident?i=blksize">blksize</a> - 1)) + net_adj - 2;
<a name="L477" href="source/net/ipv4/esp4.c#L477">477</a> }
<a name="L478" href="source/net/ipv4/esp4.c#L478">478</a> 
<a name="L479" href="source/net/ipv4/esp4.c#L479">479</a> static int <a href="ident?i=esp4_err">esp4_err</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, <a href="ident?i=u32">u32</a> <a href="ident?i=info">info</a>)
<a name="L480" href="source/net/ipv4/esp4.c#L480">480</a> {
<a name="L481" href="source/net/ipv4/esp4.c#L481">481</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=dev">dev</a>);
<a name="L482" href="source/net/ipv4/esp4.c#L482">482</a>         const struct <a href="ident?i=iphdr">iphdr</a> *iph = (const struct <a href="ident?i=iphdr">iphdr</a> *)<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=data">data</a>;
<a name="L483" href="source/net/ipv4/esp4.c#L483">483</a>         struct <a href="ident?i=ip_esp_hdr">ip_esp_hdr</a> *esph = (struct <a href="ident?i=ip_esp_hdr">ip_esp_hdr</a> *)(<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=data">data</a>+(iph-&gt;ihl&lt;&lt;2));
<a name="L484" href="source/net/ipv4/esp4.c#L484">484</a>         struct <a href="ident?i=xfrm_state">xfrm_state</a> *<a href="ident?i=x">x</a>;
<a name="L485" href="source/net/ipv4/esp4.c#L485">485</a> 
<a name="L486" href="source/net/ipv4/esp4.c#L486">486</a>         switch (<a href="ident?i=icmp_hdr">icmp_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=type">type</a>) {
<a name="L487" href="source/net/ipv4/esp4.c#L487">487</a>         case <a href="ident?i=ICMP_DEST_UNREACH">ICMP_DEST_UNREACH</a>:
<a name="L488" href="source/net/ipv4/esp4.c#L488">488</a>                 if (<a href="ident?i=icmp_hdr">icmp_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=code">code</a> != <a href="ident?i=ICMP_FRAG_NEEDED">ICMP_FRAG_NEEDED</a>)
<a name="L489" href="source/net/ipv4/esp4.c#L489">489</a>                         return 0;
<a name="L490" href="source/net/ipv4/esp4.c#L490">490</a>         case <a href="ident?i=ICMP_REDIRECT">ICMP_REDIRECT</a>:
<a name="L491" href="source/net/ipv4/esp4.c#L491">491</a>                 break;
<a name="L492" href="source/net/ipv4/esp4.c#L492">492</a>         default:
<a name="L493" href="source/net/ipv4/esp4.c#L493">493</a>                 return 0;
<a name="L494" href="source/net/ipv4/esp4.c#L494">494</a>         }
<a name="L495" href="source/net/ipv4/esp4.c#L495">495</a> 
<a name="L496" href="source/net/ipv4/esp4.c#L496">496</a>         <a href="ident?i=x">x</a> = <a href="ident?i=xfrm_state_lookup">xfrm_state_lookup</a>(<a href="ident?i=net">net</a>, <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=mark">mark</a>, (const <a href="ident?i=xfrm_address_t">xfrm_address_t</a> *)&amp;iph-&gt;<a href="ident?i=daddr">daddr</a>,
<a name="L497" href="source/net/ipv4/esp4.c#L497">497</a>                               esph-&gt;<a href="ident?i=spi">spi</a>, <a href="ident?i=IPPROTO_ESP">IPPROTO_ESP</a>, <a href="ident?i=AF_INET">AF_INET</a>);
<a name="L498" href="source/net/ipv4/esp4.c#L498">498</a>         if (!<a href="ident?i=x">x</a>)
<a name="L499" href="source/net/ipv4/esp4.c#L499">499</a>                 return 0;
<a name="L500" href="source/net/ipv4/esp4.c#L500">500</a> 
<a name="L501" href="source/net/ipv4/esp4.c#L501">501</a>         if (<a href="ident?i=icmp_hdr">icmp_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=type">type</a> == <a href="ident?i=ICMP_DEST_UNREACH">ICMP_DEST_UNREACH</a>)
<a name="L502" href="source/net/ipv4/esp4.c#L502">502</a>                 <a href="ident?i=ipv4_update_pmtu">ipv4_update_pmtu</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=net">net</a>, <a href="ident?i=info">info</a>, 0, 0, <a href="ident?i=IPPROTO_ESP">IPPROTO_ESP</a>, 0);
<a name="L503" href="source/net/ipv4/esp4.c#L503">503</a>         else
<a name="L504" href="source/net/ipv4/esp4.c#L504">504</a>                 <a href="ident?i=ipv4_redirect">ipv4_redirect</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=net">net</a>, 0, 0, <a href="ident?i=IPPROTO_ESP">IPPROTO_ESP</a>, 0);
<a name="L505" href="source/net/ipv4/esp4.c#L505">505</a>         <a href="ident?i=xfrm_state_put">xfrm_state_put</a>(<a href="ident?i=x">x</a>);
<a name="L506" href="source/net/ipv4/esp4.c#L506">506</a> 
<a name="L507" href="source/net/ipv4/esp4.c#L507">507</a>         return 0;
<a name="L508" href="source/net/ipv4/esp4.c#L508">508</a> }
<a name="L509" href="source/net/ipv4/esp4.c#L509">509</a> 
<a name="L510" href="source/net/ipv4/esp4.c#L510">510</a> static void <a href="ident?i=esp_destroy">esp_destroy</a>(struct <a href="ident?i=xfrm_state">xfrm_state</a> *<a href="ident?i=x">x</a>)
<a name="L511" href="source/net/ipv4/esp4.c#L511">511</a> {
<a name="L512" href="source/net/ipv4/esp4.c#L512">512</a>         struct <a href="ident?i=crypto_aead">crypto_aead</a> *aead = <a href="ident?i=x">x</a>-&gt;<a href="ident?i=data">data</a>;
<a name="L513" href="source/net/ipv4/esp4.c#L513">513</a> 
<a name="L514" href="source/net/ipv4/esp4.c#L514">514</a>         if (!aead)
<a name="L515" href="source/net/ipv4/esp4.c#L515">515</a>                 return;
<a name="L516" href="source/net/ipv4/esp4.c#L516">516</a> 
<a name="L517" href="source/net/ipv4/esp4.c#L517">517</a>         <a href="ident?i=crypto_free_aead">crypto_free_aead</a>(aead);
<a name="L518" href="source/net/ipv4/esp4.c#L518">518</a> }
<a name="L519" href="source/net/ipv4/esp4.c#L519">519</a> 
<a name="L520" href="source/net/ipv4/esp4.c#L520">520</a> static int <a href="ident?i=esp_init_aead">esp_init_aead</a>(struct <a href="ident?i=xfrm_state">xfrm_state</a> *<a href="ident?i=x">x</a>)
<a name="L521" href="source/net/ipv4/esp4.c#L521">521</a> {
<a name="L522" href="source/net/ipv4/esp4.c#L522">522</a>         struct <a href="ident?i=crypto_aead">crypto_aead</a> *aead;
<a name="L523" href="source/net/ipv4/esp4.c#L523">523</a>         int <a href="ident?i=err">err</a>;
<a name="L524" href="source/net/ipv4/esp4.c#L524">524</a> 
<a name="L525" href="source/net/ipv4/esp4.c#L525">525</a>         aead = <a href="ident?i=crypto_alloc_aead">crypto_alloc_aead</a>(<a href="ident?i=x">x</a>-&gt;aead-&gt;alg_name, 0, 0);
<a name="L526" href="source/net/ipv4/esp4.c#L526">526</a>         <a href="ident?i=err">err</a> = <a href="ident?i=PTR_ERR">PTR_ERR</a>(aead);
<a name="L527" href="source/net/ipv4/esp4.c#L527">527</a>         if (<a href="ident?i=IS_ERR">IS_ERR</a>(aead))
<a name="L528" href="source/net/ipv4/esp4.c#L528">528</a>                 goto <a href="ident?i=error">error</a>;
<a name="L529" href="source/net/ipv4/esp4.c#L529">529</a> 
<a name="L530" href="source/net/ipv4/esp4.c#L530">530</a>         <a href="ident?i=x">x</a>-&gt;<a href="ident?i=data">data</a> = aead;
<a name="L531" href="source/net/ipv4/esp4.c#L531">531</a> 
<a name="L532" href="source/net/ipv4/esp4.c#L532">532</a>         <a href="ident?i=err">err</a> = <a href="ident?i=crypto_aead_setkey">crypto_aead_setkey</a>(aead, <a href="ident?i=x">x</a>-&gt;aead-&gt;alg_key,
<a name="L533" href="source/net/ipv4/esp4.c#L533">533</a>                                  (<a href="ident?i=x">x</a>-&gt;aead-&gt;alg_key_len + 7) / 8);
<a name="L534" href="source/net/ipv4/esp4.c#L534">534</a>         if (<a href="ident?i=err">err</a>)
<a name="L535" href="source/net/ipv4/esp4.c#L535">535</a>                 goto <a href="ident?i=error">error</a>;
<a name="L536" href="source/net/ipv4/esp4.c#L536">536</a> 
<a name="L537" href="source/net/ipv4/esp4.c#L537">537</a>         <a href="ident?i=err">err</a> = <a href="ident?i=crypto_aead_setauthsize">crypto_aead_setauthsize</a>(aead, <a href="ident?i=x">x</a>-&gt;aead-&gt;alg_icv_len / 8);
<a name="L538" href="source/net/ipv4/esp4.c#L538">538</a>         if (<a href="ident?i=err">err</a>)
<a name="L539" href="source/net/ipv4/esp4.c#L539">539</a>                 goto <a href="ident?i=error">error</a>;
<a name="L540" href="source/net/ipv4/esp4.c#L540">540</a> 
<a name="L541" href="source/net/ipv4/esp4.c#L541">541</a> <a href="ident?i=error">error</a>:
<a name="L542" href="source/net/ipv4/esp4.c#L542">542</a>         return <a href="ident?i=err">err</a>;
<a name="L543" href="source/net/ipv4/esp4.c#L543">543</a> }
<a name="L544" href="source/net/ipv4/esp4.c#L544">544</a> 
<a name="L545" href="source/net/ipv4/esp4.c#L545">545</a> static int <a href="ident?i=esp_init_authenc">esp_init_authenc</a>(struct <a href="ident?i=xfrm_state">xfrm_state</a> *<a href="ident?i=x">x</a>)
<a name="L546" href="source/net/ipv4/esp4.c#L546">546</a> {
<a name="L547" href="source/net/ipv4/esp4.c#L547">547</a>         struct <a href="ident?i=crypto_aead">crypto_aead</a> *aead;
<a name="L548" href="source/net/ipv4/esp4.c#L548">548</a>         struct <a href="ident?i=crypto_authenc_key_param">crypto_authenc_key_param</a> *<a href="ident?i=param">param</a>;
<a name="L549" href="source/net/ipv4/esp4.c#L549">549</a>         struct <a href="ident?i=rtattr">rtattr</a> *rta;
<a name="L550" href="source/net/ipv4/esp4.c#L550">550</a>         char *<a href="ident?i=key">key</a>;
<a name="L551" href="source/net/ipv4/esp4.c#L551">551</a>         char *<a href="ident?i=p">p</a>;
<a name="L552" href="source/net/ipv4/esp4.c#L552">552</a>         char authenc_name[<a href="ident?i=CRYPTO_MAX_ALG_NAME">CRYPTO_MAX_ALG_NAME</a>];
<a name="L553" href="source/net/ipv4/esp4.c#L553">553</a>         unsigned int keylen;
<a name="L554" href="source/net/ipv4/esp4.c#L554">554</a>         int <a href="ident?i=err">err</a>;
<a name="L555" href="source/net/ipv4/esp4.c#L555">555</a> 
<a name="L556" href="source/net/ipv4/esp4.c#L556">556</a>         <a href="ident?i=err">err</a> = -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L557" href="source/net/ipv4/esp4.c#L557">557</a>         if (!<a href="ident?i=x">x</a>-&gt;ealg)
<a name="L558" href="source/net/ipv4/esp4.c#L558">558</a>                 goto <a href="ident?i=error">error</a>;
<a name="L559" href="source/net/ipv4/esp4.c#L559">559</a> 
<a name="L560" href="source/net/ipv4/esp4.c#L560">560</a>         <a href="ident?i=err">err</a> = -<a href="ident?i=ENAMETOOLONG">ENAMETOOLONG</a>;
<a name="L561" href="source/net/ipv4/esp4.c#L561">561</a> 
<a name="L562" href="source/net/ipv4/esp4.c#L562">562</a>         if ((<a href="ident?i=x">x</a>-&gt;props.<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=XFRM_STATE_ESN">XFRM_STATE_ESN</a>)) {
<a name="L563" href="source/net/ipv4/esp4.c#L563">563</a>                 if (<a href="ident?i=snprintf">snprintf</a>(authenc_name, <a href="ident?i=CRYPTO_MAX_ALG_NAME">CRYPTO_MAX_ALG_NAME</a>,
<a name="L564" href="source/net/ipv4/esp4.c#L564">564</a>                              <i>"authencesn(%s,%s)"</i>,
<a name="L565" href="source/net/ipv4/esp4.c#L565">565</a>                              <a href="ident?i=x">x</a>-&gt;aalg ? <a href="ident?i=x">x</a>-&gt;aalg-&gt;alg_name : <i>"digest_null"</i>,
<a name="L566" href="source/net/ipv4/esp4.c#L566">566</a>                              <a href="ident?i=x">x</a>-&gt;ealg-&gt;alg_name) &gt;= <a href="ident?i=CRYPTO_MAX_ALG_NAME">CRYPTO_MAX_ALG_NAME</a>)
<a name="L567" href="source/net/ipv4/esp4.c#L567">567</a>                         goto <a href="ident?i=error">error</a>;
<a name="L568" href="source/net/ipv4/esp4.c#L568">568</a>         } else {
<a name="L569" href="source/net/ipv4/esp4.c#L569">569</a>                 if (<a href="ident?i=snprintf">snprintf</a>(authenc_name, <a href="ident?i=CRYPTO_MAX_ALG_NAME">CRYPTO_MAX_ALG_NAME</a>,
<a name="L570" href="source/net/ipv4/esp4.c#L570">570</a>                              <i>"authenc(%s,%s)"</i>,
<a name="L571" href="source/net/ipv4/esp4.c#L571">571</a>                              <a href="ident?i=x">x</a>-&gt;aalg ? <a href="ident?i=x">x</a>-&gt;aalg-&gt;alg_name : <i>"digest_null"</i>,
<a name="L572" href="source/net/ipv4/esp4.c#L572">572</a>                              <a href="ident?i=x">x</a>-&gt;ealg-&gt;alg_name) &gt;= <a href="ident?i=CRYPTO_MAX_ALG_NAME">CRYPTO_MAX_ALG_NAME</a>)
<a name="L573" href="source/net/ipv4/esp4.c#L573">573</a>                         goto <a href="ident?i=error">error</a>;
<a name="L574" href="source/net/ipv4/esp4.c#L574">574</a>         }
<a name="L575" href="source/net/ipv4/esp4.c#L575">575</a> 
<a name="L576" href="source/net/ipv4/esp4.c#L576">576</a>         aead = <a href="ident?i=crypto_alloc_aead">crypto_alloc_aead</a>(authenc_name, 0, 0);
<a name="L577" href="source/net/ipv4/esp4.c#L577">577</a>         <a href="ident?i=err">err</a> = <a href="ident?i=PTR_ERR">PTR_ERR</a>(aead);
<a name="L578" href="source/net/ipv4/esp4.c#L578">578</a>         if (<a href="ident?i=IS_ERR">IS_ERR</a>(aead))
<a name="L579" href="source/net/ipv4/esp4.c#L579">579</a>                 goto <a href="ident?i=error">error</a>;
<a name="L580" href="source/net/ipv4/esp4.c#L580">580</a> 
<a name="L581" href="source/net/ipv4/esp4.c#L581">581</a>         <a href="ident?i=x">x</a>-&gt;<a href="ident?i=data">data</a> = aead;
<a name="L582" href="source/net/ipv4/esp4.c#L582">582</a> 
<a name="L583" href="source/net/ipv4/esp4.c#L583">583</a>         keylen = (<a href="ident?i=x">x</a>-&gt;aalg ? (<a href="ident?i=x">x</a>-&gt;aalg-&gt;alg_key_len + 7) / 8 : 0) +
<a name="L584" href="source/net/ipv4/esp4.c#L584">584</a>                  (<a href="ident?i=x">x</a>-&gt;ealg-&gt;alg_key_len + 7) / 8 + <a href="ident?i=RTA_SPACE">RTA_SPACE</a>(sizeof(*<a href="ident?i=param">param</a>));
<a name="L585" href="source/net/ipv4/esp4.c#L585">585</a>         <a href="ident?i=err">err</a> = -<a href="ident?i=ENOMEM">ENOMEM</a>;
<a name="L586" href="source/net/ipv4/esp4.c#L586">586</a>         <a href="ident?i=key">key</a> = <a href="ident?i=kmalloc">kmalloc</a>(keylen, <a href="ident?i=GFP_KERNEL">GFP_KERNEL</a>);
<a name="L587" href="source/net/ipv4/esp4.c#L587">587</a>         if (!<a href="ident?i=key">key</a>)
<a name="L588" href="source/net/ipv4/esp4.c#L588">588</a>                 goto <a href="ident?i=error">error</a>;
<a name="L589" href="source/net/ipv4/esp4.c#L589">589</a> 
<a name="L590" href="source/net/ipv4/esp4.c#L590">590</a>         <a href="ident?i=p">p</a> = <a href="ident?i=key">key</a>;
<a name="L591" href="source/net/ipv4/esp4.c#L591">591</a>         rta = (void *)<a href="ident?i=p">p</a>;
<a name="L592" href="source/net/ipv4/esp4.c#L592">592</a>         rta-&gt;rta_type = CRYPTO_AUTHENC_KEYA_PARAM;
<a name="L593" href="source/net/ipv4/esp4.c#L593">593</a>         rta-&gt;rta_len = <a href="ident?i=RTA_LENGTH">RTA_LENGTH</a>(sizeof(*<a href="ident?i=param">param</a>));
<a name="L594" href="source/net/ipv4/esp4.c#L594">594</a>         <a href="ident?i=param">param</a> = <a href="ident?i=RTA_DATA">RTA_DATA</a>(rta);
<a name="L595" href="source/net/ipv4/esp4.c#L595">595</a>         <a href="ident?i=p">p</a> += <a href="ident?i=RTA_SPACE">RTA_SPACE</a>(sizeof(*<a href="ident?i=param">param</a>));
<a name="L596" href="source/net/ipv4/esp4.c#L596">596</a> 
<a name="L597" href="source/net/ipv4/esp4.c#L597">597</a>         if (<a href="ident?i=x">x</a>-&gt;aalg) {
<a name="L598" href="source/net/ipv4/esp4.c#L598">598</a>                 struct <a href="ident?i=xfrm_algo_desc">xfrm_algo_desc</a> *aalg_desc;
<a name="L599" href="source/net/ipv4/esp4.c#L599">599</a> 
<a name="L600" href="source/net/ipv4/esp4.c#L600">600</a>                 <a href="ident?i=memcpy">memcpy</a>(<a href="ident?i=p">p</a>, <a href="ident?i=x">x</a>-&gt;aalg-&gt;alg_key, (<a href="ident?i=x">x</a>-&gt;aalg-&gt;alg_key_len + 7) / 8);
<a name="L601" href="source/net/ipv4/esp4.c#L601">601</a>                 <a href="ident?i=p">p</a> += (<a href="ident?i=x">x</a>-&gt;aalg-&gt;alg_key_len + 7) / 8;
<a name="L602" href="source/net/ipv4/esp4.c#L602">602</a> 
<a name="L603" href="source/net/ipv4/esp4.c#L603">603</a>                 aalg_desc = <a href="ident?i=xfrm_aalg_get_byname">xfrm_aalg_get_byname</a>(<a href="ident?i=x">x</a>-&gt;aalg-&gt;alg_name, 0);
<a name="L604" href="source/net/ipv4/esp4.c#L604">604</a>                 <a href="ident?i=BUG_ON">BUG_ON</a>(!aalg_desc);
<a name="L605" href="source/net/ipv4/esp4.c#L605">605</a> 
<a name="L606" href="source/net/ipv4/esp4.c#L606">606</a>                 <a href="ident?i=err">err</a> = -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L607" href="source/net/ipv4/esp4.c#L607">607</a>                 if (aalg_desc-&gt;<a href="ident?i=uinfo">uinfo</a>.auth.icv_fullbits / 8 !=
<a name="L608" href="source/net/ipv4/esp4.c#L608">608</a>                     <a href="ident?i=crypto_aead_authsize">crypto_aead_authsize</a>(aead)) {
<a name="L609" href="source/net/ipv4/esp4.c#L609">609</a>                         <a href="ident?i=pr_info">pr_info</a>(<i>"ESP: %s digestsize %u != %hu\n"</i>,
<a name="L610" href="source/net/ipv4/esp4.c#L610">610</a>                                 <a href="ident?i=x">x</a>-&gt;aalg-&gt;alg_name,
<a name="L611" href="source/net/ipv4/esp4.c#L611">611</a>                                 <a href="ident?i=crypto_aead_authsize">crypto_aead_authsize</a>(aead),
<a name="L612" href="source/net/ipv4/esp4.c#L612">612</a>                                 aalg_desc-&gt;<a href="ident?i=uinfo">uinfo</a>.auth.icv_fullbits / 8);
<a name="L613" href="source/net/ipv4/esp4.c#L613">613</a>                         goto free_key;
<a name="L614" href="source/net/ipv4/esp4.c#L614">614</a>                 }
<a name="L615" href="source/net/ipv4/esp4.c#L615">615</a> 
<a name="L616" href="source/net/ipv4/esp4.c#L616">616</a>                 <a href="ident?i=err">err</a> = <a href="ident?i=crypto_aead_setauthsize">crypto_aead_setauthsize</a>(
<a name="L617" href="source/net/ipv4/esp4.c#L617">617</a>                         aead, <a href="ident?i=x">x</a>-&gt;aalg-&gt;alg_trunc_len / 8);
<a name="L618" href="source/net/ipv4/esp4.c#L618">618</a>                 if (<a href="ident?i=err">err</a>)
<a name="L619" href="source/net/ipv4/esp4.c#L619">619</a>                         goto free_key;
<a name="L620" href="source/net/ipv4/esp4.c#L620">620</a>         }
<a name="L621" href="source/net/ipv4/esp4.c#L621">621</a> 
<a name="L622" href="source/net/ipv4/esp4.c#L622">622</a>         <a href="ident?i=param">param</a>-&gt;enckeylen = <a href="ident?i=cpu_to_be32">cpu_to_be32</a>((<a href="ident?i=x">x</a>-&gt;ealg-&gt;alg_key_len + 7) / 8);
<a name="L623" href="source/net/ipv4/esp4.c#L623">623</a>         <a href="ident?i=memcpy">memcpy</a>(<a href="ident?i=p">p</a>, <a href="ident?i=x">x</a>-&gt;ealg-&gt;alg_key, (<a href="ident?i=x">x</a>-&gt;ealg-&gt;alg_key_len + 7) / 8);
<a name="L624" href="source/net/ipv4/esp4.c#L624">624</a> 
<a name="L625" href="source/net/ipv4/esp4.c#L625">625</a>         <a href="ident?i=err">err</a> = <a href="ident?i=crypto_aead_setkey">crypto_aead_setkey</a>(aead, <a href="ident?i=key">key</a>, keylen);
<a name="L626" href="source/net/ipv4/esp4.c#L626">626</a> 
<a name="L627" href="source/net/ipv4/esp4.c#L627">627</a> free_key:
<a name="L628" href="source/net/ipv4/esp4.c#L628">628</a>         <a href="ident?i=kfree">kfree</a>(<a href="ident?i=key">key</a>);
<a name="L629" href="source/net/ipv4/esp4.c#L629">629</a> 
<a name="L630" href="source/net/ipv4/esp4.c#L630">630</a> <a href="ident?i=error">error</a>:
<a name="L631" href="source/net/ipv4/esp4.c#L631">631</a>         return <a href="ident?i=err">err</a>;
<a name="L632" href="source/net/ipv4/esp4.c#L632">632</a> }
<a name="L633" href="source/net/ipv4/esp4.c#L633">633</a> 
<a name="L634" href="source/net/ipv4/esp4.c#L634">634</a> static int <a href="ident?i=esp_init_state">esp_init_state</a>(struct <a href="ident?i=xfrm_state">xfrm_state</a> *<a href="ident?i=x">x</a>)
<a name="L635" href="source/net/ipv4/esp4.c#L635">635</a> {
<a name="L636" href="source/net/ipv4/esp4.c#L636">636</a>         struct <a href="ident?i=crypto_aead">crypto_aead</a> *aead;
<a name="L637" href="source/net/ipv4/esp4.c#L637">637</a>         <a href="ident?i=u32">u32</a> <a href="ident?i=align">align</a>;
<a name="L638" href="source/net/ipv4/esp4.c#L638">638</a>         int <a href="ident?i=err">err</a>;
<a name="L639" href="source/net/ipv4/esp4.c#L639">639</a> 
<a name="L640" href="source/net/ipv4/esp4.c#L640">640</a>         <a href="ident?i=x">x</a>-&gt;<a href="ident?i=data">data</a> = <a href="ident?i=NULL">NULL</a>;
<a name="L641" href="source/net/ipv4/esp4.c#L641">641</a> 
<a name="L642" href="source/net/ipv4/esp4.c#L642">642</a>         if (<a href="ident?i=x">x</a>-&gt;aead)
<a name="L643" href="source/net/ipv4/esp4.c#L643">643</a>                 <a href="ident?i=err">err</a> = <a href="ident?i=esp_init_aead">esp_init_aead</a>(<a href="ident?i=x">x</a>);
<a name="L644" href="source/net/ipv4/esp4.c#L644">644</a>         else
<a name="L645" href="source/net/ipv4/esp4.c#L645">645</a>                 <a href="ident?i=err">err</a> = <a href="ident?i=esp_init_authenc">esp_init_authenc</a>(<a href="ident?i=x">x</a>);
<a name="L646" href="source/net/ipv4/esp4.c#L646">646</a> 
<a name="L647" href="source/net/ipv4/esp4.c#L647">647</a>         if (<a href="ident?i=err">err</a>)
<a name="L648" href="source/net/ipv4/esp4.c#L648">648</a>                 goto <a href="ident?i=error">error</a>;
<a name="L649" href="source/net/ipv4/esp4.c#L649">649</a> 
<a name="L650" href="source/net/ipv4/esp4.c#L650">650</a>         aead = <a href="ident?i=x">x</a>-&gt;<a href="ident?i=data">data</a>;
<a name="L651" href="source/net/ipv4/esp4.c#L651">651</a> 
<a name="L652" href="source/net/ipv4/esp4.c#L652">652</a>         <a href="ident?i=x">x</a>-&gt;props.<a href="ident?i=header_len">header_len</a> = sizeof(struct <a href="ident?i=ip_esp_hdr">ip_esp_hdr</a>) +
<a name="L653" href="source/net/ipv4/esp4.c#L653">653</a>                               <a href="ident?i=crypto_aead_ivsize">crypto_aead_ivsize</a>(aead);
<a name="L654" href="source/net/ipv4/esp4.c#L654">654</a>         if (<a href="ident?i=x">x</a>-&gt;props.<a href="ident?i=mode">mode</a> == <a href="ident?i=XFRM_MODE_TUNNEL">XFRM_MODE_TUNNEL</a>)
<a name="L655" href="source/net/ipv4/esp4.c#L655">655</a>                 <a href="ident?i=x">x</a>-&gt;props.<a href="ident?i=header_len">header_len</a> += sizeof(struct <a href="ident?i=iphdr">iphdr</a>);
<a name="L656" href="source/net/ipv4/esp4.c#L656">656</a>         else if (<a href="ident?i=x">x</a>-&gt;props.<a href="ident?i=mode">mode</a> == <a href="ident?i=XFRM_MODE_BEET">XFRM_MODE_BEET</a> &amp;&amp; <a href="ident?i=x">x</a>-&gt;sel.<a href="ident?i=family">family</a> != <a href="ident?i=AF_INET6">AF_INET6</a>)
<a name="L657" href="source/net/ipv4/esp4.c#L657">657</a>                 <a href="ident?i=x">x</a>-&gt;props.<a href="ident?i=header_len">header_len</a> += <a href="ident?i=IPV4_BEET_PHMAXLEN">IPV4_BEET_PHMAXLEN</a>;
<a name="L658" href="source/net/ipv4/esp4.c#L658">658</a>         if (<a href="ident?i=x">x</a>-&gt;encap) {
<a name="L659" href="source/net/ipv4/esp4.c#L659">659</a>                 struct <a href="ident?i=xfrm_encap_tmpl">xfrm_encap_tmpl</a> *encap = <a href="ident?i=x">x</a>-&gt;encap;
<a name="L660" href="source/net/ipv4/esp4.c#L660">660</a> 
<a name="L661" href="source/net/ipv4/esp4.c#L661">661</a>                 switch (encap-&gt;encap_type) {
<a name="L662" href="source/net/ipv4/esp4.c#L662">662</a>                 default:
<a name="L663" href="source/net/ipv4/esp4.c#L663">663</a>                         goto <a href="ident?i=error">error</a>;
<a name="L664" href="source/net/ipv4/esp4.c#L664">664</a>                 case <a href="ident?i=UDP_ENCAP_ESPINUDP">UDP_ENCAP_ESPINUDP</a>:
<a name="L665" href="source/net/ipv4/esp4.c#L665">665</a>                         <a href="ident?i=x">x</a>-&gt;props.<a href="ident?i=header_len">header_len</a> += sizeof(struct <a href="ident?i=udphdr">udphdr</a>);
<a name="L666" href="source/net/ipv4/esp4.c#L666">666</a>                         break;
<a name="L667" href="source/net/ipv4/esp4.c#L667">667</a>                 case <a href="ident?i=UDP_ENCAP_ESPINUDP_NON_IKE">UDP_ENCAP_ESPINUDP_NON_IKE</a>:
<a name="L668" href="source/net/ipv4/esp4.c#L668">668</a>                         <a href="ident?i=x">x</a>-&gt;props.<a href="ident?i=header_len">header_len</a> += sizeof(struct <a href="ident?i=udphdr">udphdr</a>) + 2 * sizeof(<a href="ident?i=u32">u32</a>);
<a name="L669" href="source/net/ipv4/esp4.c#L669">669</a>                         break;
<a name="L670" href="source/net/ipv4/esp4.c#L670">670</a>                 }
<a name="L671" href="source/net/ipv4/esp4.c#L671">671</a>         }
<a name="L672" href="source/net/ipv4/esp4.c#L672">672</a> 
<a name="L673" href="source/net/ipv4/esp4.c#L673">673</a>         <a href="ident?i=align">align</a> = <a href="ident?i=ALIGN">ALIGN</a>(<a href="ident?i=crypto_aead_blocksize">crypto_aead_blocksize</a>(aead), 4);
<a name="L674" href="source/net/ipv4/esp4.c#L674">674</a>         <a href="ident?i=x">x</a>-&gt;props.trailer_len = <a href="ident?i=align">align</a> + 1 + <a href="ident?i=crypto_aead_authsize">crypto_aead_authsize</a>(aead);
<a name="L675" href="source/net/ipv4/esp4.c#L675">675</a> 
<a name="L676" href="source/net/ipv4/esp4.c#L676">676</a> <a href="ident?i=error">error</a>:
<a name="L677" href="source/net/ipv4/esp4.c#L677">677</a>         return <a href="ident?i=err">err</a>;
<a name="L678" href="source/net/ipv4/esp4.c#L678">678</a> }
<a name="L679" href="source/net/ipv4/esp4.c#L679">679</a> 
<a name="L680" href="source/net/ipv4/esp4.c#L680">680</a> static int <a href="ident?i=esp4_rcv_cb">esp4_rcv_cb</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, int <a href="ident?i=err">err</a>)
<a name="L681" href="source/net/ipv4/esp4.c#L681">681</a> {
<a name="L682" href="source/net/ipv4/esp4.c#L682">682</a>         return 0;
<a name="L683" href="source/net/ipv4/esp4.c#L683">683</a> }
<a name="L684" href="source/net/ipv4/esp4.c#L684">684</a> 
<a name="L685" href="source/net/ipv4/esp4.c#L685">685</a> static const struct <a href="ident?i=xfrm_type">xfrm_type</a> <a href="ident?i=esp_type">esp_type</a> =
<a name="L686" href="source/net/ipv4/esp4.c#L686">686</a> {
<a name="L687" href="source/net/ipv4/esp4.c#L687">687</a>         .description    = <i>"ESP4"</i>,
<a name="L688" href="source/net/ipv4/esp4.c#L688">688</a>         .owner          = <a href="ident?i=THIS_MODULE">THIS_MODULE</a>,
<a name="L689" href="source/net/ipv4/esp4.c#L689">689</a>         .<a href="ident?i=proto">proto</a>          = <a href="ident?i=IPPROTO_ESP">IPPROTO_ESP</a>,
<a name="L690" href="source/net/ipv4/esp4.c#L690">690</a>         .<a href="ident?i=flags">flags</a>          = <a href="ident?i=XFRM_TYPE_REPLAY_PROT">XFRM_TYPE_REPLAY_PROT</a>,
<a name="L691" href="source/net/ipv4/esp4.c#L691">691</a>         .<a href="ident?i=init_state">init_state</a>     = <a href="ident?i=esp_init_state">esp_init_state</a>,
<a name="L692" href="source/net/ipv4/esp4.c#L692">692</a>         .destructor     = <a href="ident?i=esp_destroy">esp_destroy</a>,
<a name="L693" href="source/net/ipv4/esp4.c#L693">693</a>         .get_mtu        = <a href="ident?i=esp4_get_mtu">esp4_get_mtu</a>,
<a name="L694" href="source/net/ipv4/esp4.c#L694">694</a>         .<a href="ident?i=input">input</a>          = <a href="ident?i=esp_input">esp_input</a>,
<a name="L695" href="source/net/ipv4/esp4.c#L695">695</a>         .<a href="ident?i=output">output</a>         = <a href="ident?i=esp_output">esp_output</a>
<a name="L696" href="source/net/ipv4/esp4.c#L696">696</a> };
<a name="L697" href="source/net/ipv4/esp4.c#L697">697</a> 
<a name="L698" href="source/net/ipv4/esp4.c#L698">698</a> static struct <a href="ident?i=xfrm4_protocol">xfrm4_protocol</a> <a href="ident?i=esp4_protocol">esp4_protocol</a> = {
<a name="L699" href="source/net/ipv4/esp4.c#L699">699</a>         .<a href="ident?i=handler">handler</a>        =       <a href="ident?i=xfrm4_rcv">xfrm4_rcv</a>,
<a name="L700" href="source/net/ipv4/esp4.c#L700">700</a>         .<a href="ident?i=input_handler">input_handler</a>  =       <a href="ident?i=xfrm_input">xfrm_input</a>,
<a name="L701" href="source/net/ipv4/esp4.c#L701">701</a>         .cb_handler     =       <a href="ident?i=esp4_rcv_cb">esp4_rcv_cb</a>,
<a name="L702" href="source/net/ipv4/esp4.c#L702">702</a>         .<a href="ident?i=err_handler">err_handler</a>    =       <a href="ident?i=esp4_err">esp4_err</a>,
<a name="L703" href="source/net/ipv4/esp4.c#L703">703</a>         .<a href="ident?i=priority">priority</a>       =       0,
<a name="L704" href="source/net/ipv4/esp4.c#L704">704</a> };
<a name="L705" href="source/net/ipv4/esp4.c#L705">705</a> 
<a name="L706" href="source/net/ipv4/esp4.c#L706">706</a> static int <a href="ident?i=__init">__init</a> <a href="ident?i=esp4_init">esp4_init</a>(void)
<a name="L707" href="source/net/ipv4/esp4.c#L707">707</a> {
<a name="L708" href="source/net/ipv4/esp4.c#L708">708</a>         if (<a href="ident?i=xfrm_register_type">xfrm_register_type</a>(&amp;<a href="ident?i=esp_type">esp_type</a>, <a href="ident?i=AF_INET">AF_INET</a>) &lt; 0) {
<a name="L709" href="source/net/ipv4/esp4.c#L709">709</a>                 <a href="ident?i=pr_info">pr_info</a>(<i>"%s: can't add xfrm type\n"</i>, <a href="ident?i=__func__">__func__</a>);
<a name="L710" href="source/net/ipv4/esp4.c#L710">710</a>                 return -<a href="ident?i=EAGAIN">EAGAIN</a>;
<a name="L711" href="source/net/ipv4/esp4.c#L711">711</a>         }
<a name="L712" href="source/net/ipv4/esp4.c#L712">712</a>         if (<a href="ident?i=xfrm4_protocol_register">xfrm4_protocol_register</a>(&amp;<a href="ident?i=esp4_protocol">esp4_protocol</a>, <a href="ident?i=IPPROTO_ESP">IPPROTO_ESP</a>) &lt; 0) {
<a name="L713" href="source/net/ipv4/esp4.c#L713">713</a>                 <a href="ident?i=pr_info">pr_info</a>(<i>"%s: can't add protocol\n"</i>, <a href="ident?i=__func__">__func__</a>);
<a name="L714" href="source/net/ipv4/esp4.c#L714">714</a>                 <a href="ident?i=xfrm_unregister_type">xfrm_unregister_type</a>(&amp;<a href="ident?i=esp_type">esp_type</a>, <a href="ident?i=AF_INET">AF_INET</a>);
<a name="L715" href="source/net/ipv4/esp4.c#L715">715</a>                 return -<a href="ident?i=EAGAIN">EAGAIN</a>;
<a name="L716" href="source/net/ipv4/esp4.c#L716">716</a>         }
<a name="L717" href="source/net/ipv4/esp4.c#L717">717</a>         return 0;
<a name="L718" href="source/net/ipv4/esp4.c#L718">718</a> }
<a name="L719" href="source/net/ipv4/esp4.c#L719">719</a> 
<a name="L720" href="source/net/ipv4/esp4.c#L720">720</a> static void <a href="ident?i=__exit">__exit</a> <a href="ident?i=esp4_fini">esp4_fini</a>(void)
<a name="L721" href="source/net/ipv4/esp4.c#L721">721</a> {
<a name="L722" href="source/net/ipv4/esp4.c#L722">722</a>         if (<a href="ident?i=xfrm4_protocol_deregister">xfrm4_protocol_deregister</a>(&amp;<a href="ident?i=esp4_protocol">esp4_protocol</a>, <a href="ident?i=IPPROTO_ESP">IPPROTO_ESP</a>) &lt; 0)
<a name="L723" href="source/net/ipv4/esp4.c#L723">723</a>                 <a href="ident?i=pr_info">pr_info</a>(<i>"%s: can't remove protocol\n"</i>, <a href="ident?i=__func__">__func__</a>);
<a name="L724" href="source/net/ipv4/esp4.c#L724">724</a>         if (<a href="ident?i=xfrm_unregister_type">xfrm_unregister_type</a>(&amp;<a href="ident?i=esp_type">esp_type</a>, <a href="ident?i=AF_INET">AF_INET</a>) &lt; 0)
<a name="L725" href="source/net/ipv4/esp4.c#L725">725</a>                 <a href="ident?i=pr_info">pr_info</a>(<i>"%s: can't remove xfrm type\n"</i>, <a href="ident?i=__func__">__func__</a>);
<a name="L726" href="source/net/ipv4/esp4.c#L726">726</a> }
<a name="L727" href="source/net/ipv4/esp4.c#L727">727</a> 
<a name="L728" href="source/net/ipv4/esp4.c#L728">728</a> <a href="ident?i=module_init">module_init</a>(<a href="ident?i=esp4_init">esp4_init</a>);
<a name="L729" href="source/net/ipv4/esp4.c#L729">729</a> <a href="ident?i=module_exit">module_exit</a>(<a href="ident?i=esp4_fini">esp4_fini</a>);
<a name="L730" href="source/net/ipv4/esp4.c#L730">730</a> <a href="ident?i=MODULE_LICENSE">MODULE_LICENSE</a>(<i>"GPL"</i>);
<a name="L731" href="source/net/ipv4/esp4.c#L731">731</a> <a href="ident?i=MODULE_ALIAS_XFRM_TYPE">MODULE_ALIAS_XFRM_TYPE</a>(<a href="ident?i=AF_INET">AF_INET</a>, <a href="ident?i=XFRM_PROTO_ESP">XFRM_PROTO_ESP</a>);
<a name="L732" href="source/net/ipv4/esp4.c#L732">732</a> </pre></div><p>
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
