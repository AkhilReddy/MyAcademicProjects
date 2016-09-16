<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title>Linux/net/ipv4/ah4.c - Linux Cross Reference - Free Electrons</title>
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
		 &nbsp;&bull;&nbsp;<b><i>source navigation</i></b> &nbsp;&bull;&nbsp;<a href="diff/net/ipv4/ah4.c">diff markup</a> &nbsp;&bull;&nbsp;<a href="ident">identifier search</a> &nbsp;&bull;&nbsp;<a href="search">freetext search</a> &nbsp;&bull;&nbsp;
		</p>
	</div>
</div>

<div id="topbar">
  
  <p>Version: &nbsp;<a href="source/net/ipv4/ah4.c?v=2.0.40">2.0.40</a>&nbsp;<a href="source/net/ipv4/ah4.c?v=2.2.26">2.2.26</a>&nbsp;<a href="source/net/ipv4/ah4.c?v=2.4.37">2.4.37</a>&nbsp;<a href="source/net/ipv4/ah4.c?v=3.5">3.5</a>&nbsp;<a href="source/net/ipv4/ah4.c?v=3.6">3.6</a>&nbsp;<a href="source/net/ipv4/ah4.c?v=3.7">3.7</a>&nbsp;<a href="source/net/ipv4/ah4.c?v=3.8">3.8</a>&nbsp;<a href="source/net/ipv4/ah4.c?v=3.9">3.9</a>&nbsp;<a href="source/net/ipv4/ah4.c?v=3.10">3.10</a>&nbsp;<a href="source/net/ipv4/ah4.c?v=3.11">3.11</a>&nbsp;<a href="source/net/ipv4/ah4.c?v=3.12">3.12</a>&nbsp;<a href="source/net/ipv4/ah4.c?v=3.13">3.13</a>&nbsp;<a href="source/net/ipv4/ah4.c?v=3.14">3.14</a>&nbsp;<a href="source/net/ipv4/ah4.c?v=3.15">3.15</a>&nbsp;<a href="source/net/ipv4/ah4.c?v=3.16">3.16</a>&nbsp;<a href="source/net/ipv4/ah4.c?v=3.17">3.17</a>&nbsp;<a href="source/net/ipv4/ah4.c?v=3.18">3.18</a>&nbsp;<a href="source/net/ipv4/ah4.c?v=3.19">3.19</a>&nbsp;<a href="source/net/ipv4/ah4.c?v=4.0">4.0</a>&nbsp;<b><i>4.1</i></b></p>
  
</div>

<h1><a href="source/">Linux</a>/<a href="source/net/">net</a>/<a href="source/net/ipv4/">ipv4</a>/<a href="source/net/ipv4/ah4.c">ah4.c</a></h1>
<div id="lxrcode"><pre>  <a name="L1" href="source/net/ipv4/ah4.c#L1">1</a> #define <a href="ident?i=pr_fmt">pr_fmt</a>(<a href="ident?i=fmt">fmt</a>) <i>"IPsec: "</i> <a href="ident?i=fmt">fmt</a>
  <a name="L2" href="source/net/ipv4/ah4.c#L2">2</a> 
  <a name="L3" href="source/net/ipv4/ah4.c#L3">3</a> #include &lt;crypto/hash.h&gt;
  <a name="L4" href="source/net/ipv4/ah4.c#L4">4</a> #include &lt;linux/err.h&gt;
  <a name="L5" href="source/net/ipv4/ah4.c#L5">5</a> #include &lt;linux/module.h&gt;
  <a name="L6" href="source/net/ipv4/ah4.c#L6">6</a> #include &lt;linux/slab.h&gt;
  <a name="L7" href="source/net/ipv4/ah4.c#L7">7</a> #include &lt;net/ip.h&gt;
  <a name="L8" href="source/net/ipv4/ah4.c#L8">8</a> #include &lt;net/xfrm.h&gt;
  <a name="L9" href="source/net/ipv4/ah4.c#L9">9</a> #include &lt;net/ah.h&gt;
 <a name="L10" href="source/net/ipv4/ah4.c#L10">10</a> #include &lt;linux/crypto.h&gt;
 <a name="L11" href="source/net/ipv4/ah4.c#L11">11</a> #include &lt;linux/pfkeyv2.h&gt;
 <a name="L12" href="source/net/ipv4/ah4.c#L12">12</a> #include &lt;linux/scatterlist.h&gt;
 <a name="L13" href="source/net/ipv4/ah4.c#L13">13</a> #include &lt;net/icmp.h&gt;
 <a name="L14" href="source/net/ipv4/ah4.c#L14">14</a> #include &lt;net/protocol.h&gt;
 <a name="L15" href="source/net/ipv4/ah4.c#L15">15</a> 
 <a name="L16" href="source/net/ipv4/ah4.c#L16">16</a> struct <a href="ident?i=ah_skb_cb">ah_skb_cb</a> {
 <a name="L17" href="source/net/ipv4/ah4.c#L17">17</a>         struct <a href="ident?i=xfrm_skb_cb">xfrm_skb_cb</a> xfrm;
 <a name="L18" href="source/net/ipv4/ah4.c#L18">18</a>         void *<a href="ident?i=tmp">tmp</a>;
 <a name="L19" href="source/net/ipv4/ah4.c#L19">19</a> };
 <a name="L20" href="source/net/ipv4/ah4.c#L20">20</a> 
 <a name="L21" href="source/net/ipv4/ah4.c#L21">21</a> #define <a href="ident?i=AH_SKB_CB">AH_SKB_CB</a>(__skb) ((struct <a href="ident?i=ah_skb_cb">ah_skb_cb</a> *)&amp;((__skb)-&gt;<a href="ident?i=cb">cb</a>[0]))
 <a name="L22" href="source/net/ipv4/ah4.c#L22">22</a> 
 <a name="L23" href="source/net/ipv4/ah4.c#L23">23</a> static void *<a href="ident?i=ah_alloc_tmp">ah_alloc_tmp</a>(struct <a href="ident?i=crypto_ahash">crypto_ahash</a> *ahash, int nfrags,
 <a name="L24" href="source/net/ipv4/ah4.c#L24">24</a>                           unsigned int <a href="ident?i=size">size</a>)
 <a name="L25" href="source/net/ipv4/ah4.c#L25">25</a> {
 <a name="L26" href="source/net/ipv4/ah4.c#L26">26</a>         unsigned int <a href="ident?i=len">len</a>;
 <a name="L27" href="source/net/ipv4/ah4.c#L27">27</a> 
 <a name="L28" href="source/net/ipv4/ah4.c#L28">28</a>         <a href="ident?i=len">len</a> = <a href="ident?i=size">size</a> + <a href="ident?i=crypto_ahash_digestsize">crypto_ahash_digestsize</a>(ahash) +
 <a name="L29" href="source/net/ipv4/ah4.c#L29">29</a>               (<a href="ident?i=crypto_ahash_alignmask">crypto_ahash_alignmask</a>(ahash) &amp;
 <a name="L30" href="source/net/ipv4/ah4.c#L30">30</a>                ~(<a href="ident?i=crypto_tfm_ctx_alignment">crypto_tfm_ctx_alignment</a>() - 1));
 <a name="L31" href="source/net/ipv4/ah4.c#L31">31</a> 
 <a name="L32" href="source/net/ipv4/ah4.c#L32">32</a>         <a href="ident?i=len">len</a> = <a href="ident?i=ALIGN">ALIGN</a>(<a href="ident?i=len">len</a>, <a href="ident?i=crypto_tfm_ctx_alignment">crypto_tfm_ctx_alignment</a>());
 <a name="L33" href="source/net/ipv4/ah4.c#L33">33</a> 
 <a name="L34" href="source/net/ipv4/ah4.c#L34">34</a>         <a href="ident?i=len">len</a> += sizeof(struct <a href="ident?i=ahash_request">ahash_request</a>) + <a href="ident?i=crypto_ahash_reqsize">crypto_ahash_reqsize</a>(ahash);
 <a name="L35" href="source/net/ipv4/ah4.c#L35">35</a>         <a href="ident?i=len">len</a> = <a href="ident?i=ALIGN">ALIGN</a>(<a href="ident?i=len">len</a>, __alignof__(struct <a href="ident?i=scatterlist">scatterlist</a>));
 <a name="L36" href="source/net/ipv4/ah4.c#L36">36</a> 
 <a name="L37" href="source/net/ipv4/ah4.c#L37">37</a>         <a href="ident?i=len">len</a> += sizeof(struct <a href="ident?i=scatterlist">scatterlist</a>) * nfrags;
 <a name="L38" href="source/net/ipv4/ah4.c#L38">38</a> 
 <a name="L39" href="source/net/ipv4/ah4.c#L39">39</a>         return <a href="ident?i=kmalloc">kmalloc</a>(<a href="ident?i=len">len</a>, <a href="ident?i=GFP_ATOMIC">GFP_ATOMIC</a>);
 <a name="L40" href="source/net/ipv4/ah4.c#L40">40</a> }
 <a name="L41" href="source/net/ipv4/ah4.c#L41">41</a> 
 <a name="L42" href="source/net/ipv4/ah4.c#L42">42</a> static inline <a href="ident?i=u8">u8</a> *<a href="ident?i=ah_tmp_auth">ah_tmp_auth</a>(void *<a href="ident?i=tmp">tmp</a>, unsigned int <a href="ident?i=offset">offset</a>)
 <a name="L43" href="source/net/ipv4/ah4.c#L43">43</a> {
 <a name="L44" href="source/net/ipv4/ah4.c#L44">44</a>         return <a href="ident?i=tmp">tmp</a> + <a href="ident?i=offset">offset</a>;
 <a name="L45" href="source/net/ipv4/ah4.c#L45">45</a> }
 <a name="L46" href="source/net/ipv4/ah4.c#L46">46</a> 
 <a name="L47" href="source/net/ipv4/ah4.c#L47">47</a> static inline <a href="ident?i=u8">u8</a> *<a href="ident?i=ah_tmp_icv">ah_tmp_icv</a>(struct <a href="ident?i=crypto_ahash">crypto_ahash</a> *ahash, void *<a href="ident?i=tmp">tmp</a>,
 <a name="L48" href="source/net/ipv4/ah4.c#L48">48</a>                              unsigned int <a href="ident?i=offset">offset</a>)
 <a name="L49" href="source/net/ipv4/ah4.c#L49">49</a> {
 <a name="L50" href="source/net/ipv4/ah4.c#L50">50</a>         return <a href="ident?i=PTR_ALIGN">PTR_ALIGN</a>((<a href="ident?i=u8">u8</a> *)<a href="ident?i=tmp">tmp</a> + <a href="ident?i=offset">offset</a>, <a href="ident?i=crypto_ahash_alignmask">crypto_ahash_alignmask</a>(ahash) + 1);
 <a name="L51" href="source/net/ipv4/ah4.c#L51">51</a> }
 <a name="L52" href="source/net/ipv4/ah4.c#L52">52</a> 
 <a name="L53" href="source/net/ipv4/ah4.c#L53">53</a> static inline struct <a href="ident?i=ahash_request">ahash_request</a> *<a href="ident?i=ah_tmp_req">ah_tmp_req</a>(struct <a href="ident?i=crypto_ahash">crypto_ahash</a> *ahash,
 <a name="L54" href="source/net/ipv4/ah4.c#L54">54</a>                                                <a href="ident?i=u8">u8</a> *icv)
 <a name="L55" href="source/net/ipv4/ah4.c#L55">55</a> {
 <a name="L56" href="source/net/ipv4/ah4.c#L56">56</a>         struct <a href="ident?i=ahash_request">ahash_request</a> *<a href="ident?i=req">req</a>;
 <a name="L57" href="source/net/ipv4/ah4.c#L57">57</a> 
 <a name="L58" href="source/net/ipv4/ah4.c#L58">58</a>         <a href="ident?i=req">req</a> = (void *)<a href="ident?i=PTR_ALIGN">PTR_ALIGN</a>(icv + <a href="ident?i=crypto_ahash_digestsize">crypto_ahash_digestsize</a>(ahash),
 <a name="L59" href="source/net/ipv4/ah4.c#L59">59</a>                                 <a href="ident?i=crypto_tfm_ctx_alignment">crypto_tfm_ctx_alignment</a>());
 <a name="L60" href="source/net/ipv4/ah4.c#L60">60</a> 
 <a name="L61" href="source/net/ipv4/ah4.c#L61">61</a>         <a href="ident?i=ahash_request_set_tfm">ahash_request_set_tfm</a>(<a href="ident?i=req">req</a>, ahash);
 <a name="L62" href="source/net/ipv4/ah4.c#L62">62</a> 
 <a name="L63" href="source/net/ipv4/ah4.c#L63">63</a>         return <a href="ident?i=req">req</a>;
 <a name="L64" href="source/net/ipv4/ah4.c#L64">64</a> }
 <a name="L65" href="source/net/ipv4/ah4.c#L65">65</a> 
 <a name="L66" href="source/net/ipv4/ah4.c#L66">66</a> static inline struct <a href="ident?i=scatterlist">scatterlist</a> *<a href="ident?i=ah_req_sg">ah_req_sg</a>(struct <a href="ident?i=crypto_ahash">crypto_ahash</a> *ahash,
 <a name="L67" href="source/net/ipv4/ah4.c#L67">67</a>                                              struct <a href="ident?i=ahash_request">ahash_request</a> *<a href="ident?i=req">req</a>)
 <a name="L68" href="source/net/ipv4/ah4.c#L68">68</a> {
 <a name="L69" href="source/net/ipv4/ah4.c#L69">69</a>         return (void *)<a href="ident?i=ALIGN">ALIGN</a>((unsigned long)(<a href="ident?i=req">req</a> + 1) +
 <a name="L70" href="source/net/ipv4/ah4.c#L70">70</a>                              <a href="ident?i=crypto_ahash_reqsize">crypto_ahash_reqsize</a>(ahash),
 <a name="L71" href="source/net/ipv4/ah4.c#L71">71</a>                              __alignof__(struct <a href="ident?i=scatterlist">scatterlist</a>));
 <a name="L72" href="source/net/ipv4/ah4.c#L72">72</a> }
 <a name="L73" href="source/net/ipv4/ah4.c#L73">73</a> 
 <a name="L74" href="source/net/ipv4/ah4.c#L74">74</a> <b><i>/* Clear mutable options and find final destination to substitute</i></b>
 <a name="L75" href="source/net/ipv4/ah4.c#L75">75</a> <b><i> * into IP header for icv calculation. Options are already checked</i></b>
 <a name="L76" href="source/net/ipv4/ah4.c#L76">76</a> <b><i> * for validity, so paranoia is not required. */</i></b>
 <a name="L77" href="source/net/ipv4/ah4.c#L77">77</a> 
 <a name="L78" href="source/net/ipv4/ah4.c#L78">78</a> static int <a href="ident?i=ip_clear_mutable_options">ip_clear_mutable_options</a>(const struct <a href="ident?i=iphdr">iphdr</a> *iph, <a href="ident?i=__be32">__be32</a> *<a href="ident?i=daddr">daddr</a>)
 <a name="L79" href="source/net/ipv4/ah4.c#L79">79</a> {
 <a name="L80" href="source/net/ipv4/ah4.c#L80">80</a>         unsigned char *optptr = (unsigned char *)(iph+1);
 <a name="L81" href="source/net/ipv4/ah4.c#L81">81</a>         int  <a href="ident?i=l">l</a> = iph-&gt;ihl*4 - sizeof(struct <a href="ident?i=iphdr">iphdr</a>);
 <a name="L82" href="source/net/ipv4/ah4.c#L82">82</a>         int  <a href="ident?i=optlen">optlen</a>;
 <a name="L83" href="source/net/ipv4/ah4.c#L83">83</a> 
 <a name="L84" href="source/net/ipv4/ah4.c#L84">84</a>         while (<a href="ident?i=l">l</a> &gt; 0) {
 <a name="L85" href="source/net/ipv4/ah4.c#L85">85</a>                 switch (*optptr) {
 <a name="L86" href="source/net/ipv4/ah4.c#L86">86</a>                 case <a href="ident?i=IPOPT_END">IPOPT_END</a>:
 <a name="L87" href="source/net/ipv4/ah4.c#L87">87</a>                         return 0;
 <a name="L88" href="source/net/ipv4/ah4.c#L88">88</a>                 case <a href="ident?i=IPOPT_NOOP">IPOPT_NOOP</a>:
 <a name="L89" href="source/net/ipv4/ah4.c#L89">89</a>                         <a href="ident?i=l">l</a>--;
 <a name="L90" href="source/net/ipv4/ah4.c#L90">90</a>                         optptr++;
 <a name="L91" href="source/net/ipv4/ah4.c#L91">91</a>                         continue;
 <a name="L92" href="source/net/ipv4/ah4.c#L92">92</a>                 }
 <a name="L93" href="source/net/ipv4/ah4.c#L93">93</a>                 <a href="ident?i=optlen">optlen</a> = optptr[1];
 <a name="L94" href="source/net/ipv4/ah4.c#L94">94</a>                 if (<a href="ident?i=optlen">optlen</a>&lt;2 || <a href="ident?i=optlen">optlen</a>&gt;<a href="ident?i=l">l</a>)
 <a name="L95" href="source/net/ipv4/ah4.c#L95">95</a>                         return -<a href="ident?i=EINVAL">EINVAL</a>;
 <a name="L96" href="source/net/ipv4/ah4.c#L96">96</a>                 switch (*optptr) {
 <a name="L97" href="source/net/ipv4/ah4.c#L97">97</a>                 case <a href="ident?i=IPOPT_SEC">IPOPT_SEC</a>:
 <a name="L98" href="source/net/ipv4/ah4.c#L98">98</a>                 case 0x85:      <b><i>/* Some "Extended Security" crap. */</i></b>
 <a name="L99" href="source/net/ipv4/ah4.c#L99">99</a>                 case <a href="ident?i=IPOPT_CIPSO">IPOPT_CIPSO</a>:
<a name="L100" href="source/net/ipv4/ah4.c#L100">100</a>                 case <a href="ident?i=IPOPT_RA">IPOPT_RA</a>:
<a name="L101" href="source/net/ipv4/ah4.c#L101">101</a>                 case 0x80|21:   <b><i>/* RFC1770 */</i></b>
<a name="L102" href="source/net/ipv4/ah4.c#L102">102</a>                         break;
<a name="L103" href="source/net/ipv4/ah4.c#L103">103</a>                 case <a href="ident?i=IPOPT_LSRR">IPOPT_LSRR</a>:
<a name="L104" href="source/net/ipv4/ah4.c#L104">104</a>                 case <a href="ident?i=IPOPT_SSRR">IPOPT_SSRR</a>:
<a name="L105" href="source/net/ipv4/ah4.c#L105">105</a>                         if (<a href="ident?i=optlen">optlen</a> &lt; 6)
<a name="L106" href="source/net/ipv4/ah4.c#L106">106</a>                                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L107" href="source/net/ipv4/ah4.c#L107">107</a>                         <a href="ident?i=memcpy">memcpy</a>(<a href="ident?i=daddr">daddr</a>, optptr+<a href="ident?i=optlen">optlen</a>-4, 4);
<a name="L108" href="source/net/ipv4/ah4.c#L108">108</a>                         <b><i>/* Fall through */</i></b>
<a name="L109" href="source/net/ipv4/ah4.c#L109">109</a>                 default:
<a name="L110" href="source/net/ipv4/ah4.c#L110">110</a>                         <a href="ident?i=memset">memset</a>(optptr, 0, <a href="ident?i=optlen">optlen</a>);
<a name="L111" href="source/net/ipv4/ah4.c#L111">111</a>                 }
<a name="L112" href="source/net/ipv4/ah4.c#L112">112</a>                 <a href="ident?i=l">l</a> -= <a href="ident?i=optlen">optlen</a>;
<a name="L113" href="source/net/ipv4/ah4.c#L113">113</a>                 optptr += <a href="ident?i=optlen">optlen</a>;
<a name="L114" href="source/net/ipv4/ah4.c#L114">114</a>         }
<a name="L115" href="source/net/ipv4/ah4.c#L115">115</a>         return 0;
<a name="L116" href="source/net/ipv4/ah4.c#L116">116</a> }
<a name="L117" href="source/net/ipv4/ah4.c#L117">117</a> 
<a name="L118" href="source/net/ipv4/ah4.c#L118">118</a> static void <a href="ident?i=ah_output_done">ah_output_done</a>(struct <a href="ident?i=crypto_async_request">crypto_async_request</a> *<a href="ident?i=base">base</a>, int <a href="ident?i=err">err</a>)
<a name="L119" href="source/net/ipv4/ah4.c#L119">119</a> {
<a name="L120" href="source/net/ipv4/ah4.c#L120">120</a>         <a href="ident?i=u8">u8</a> *icv;
<a name="L121" href="source/net/ipv4/ah4.c#L121">121</a>         struct <a href="ident?i=iphdr">iphdr</a> *iph;
<a name="L122" href="source/net/ipv4/ah4.c#L122">122</a>         struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a> = <a href="ident?i=base">base</a>-&gt;<a href="ident?i=data">data</a>;
<a name="L123" href="source/net/ipv4/ah4.c#L123">123</a>         struct <a href="ident?i=xfrm_state">xfrm_state</a> *<a href="ident?i=x">x</a> = <a href="ident?i=skb_dst">skb_dst</a>(<a href="ident?i=skb">skb</a>)-&gt;xfrm;
<a name="L124" href="source/net/ipv4/ah4.c#L124">124</a>         struct <a href="ident?i=ah_data">ah_data</a> *ahp = <a href="ident?i=x">x</a>-&gt;<a href="ident?i=data">data</a>;
<a name="L125" href="source/net/ipv4/ah4.c#L125">125</a>         struct <a href="ident?i=iphdr">iphdr</a> *top_iph = <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>);
<a name="L126" href="source/net/ipv4/ah4.c#L126">126</a>         struct <a href="ident?i=ip_auth_hdr">ip_auth_hdr</a> *ah = <a href="ident?i=ip_auth_hdr">ip_auth_hdr</a>(<a href="ident?i=skb">skb</a>);
<a name="L127" href="source/net/ipv4/ah4.c#L127">127</a>         int ihl = <a href="ident?i=ip_hdrlen">ip_hdrlen</a>(<a href="ident?i=skb">skb</a>);
<a name="L128" href="source/net/ipv4/ah4.c#L128">128</a> 
<a name="L129" href="source/net/ipv4/ah4.c#L129">129</a>         iph = <a href="ident?i=AH_SKB_CB">AH_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=tmp">tmp</a>;
<a name="L130" href="source/net/ipv4/ah4.c#L130">130</a>         icv = <a href="ident?i=ah_tmp_icv">ah_tmp_icv</a>(ahp-&gt;ahash, iph, ihl);
<a name="L131" href="source/net/ipv4/ah4.c#L131">131</a>         <a href="ident?i=memcpy">memcpy</a>(ah-&gt;auth_data, icv, ahp-&gt;icv_trunc_len);
<a name="L132" href="source/net/ipv4/ah4.c#L132">132</a> 
<a name="L133" href="source/net/ipv4/ah4.c#L133">133</a>         top_iph-&gt;tos = iph-&gt;tos;
<a name="L134" href="source/net/ipv4/ah4.c#L134">134</a>         top_iph-&gt;<a href="ident?i=ttl">ttl</a> = iph-&gt;<a href="ident?i=ttl">ttl</a>;
<a name="L135" href="source/net/ipv4/ah4.c#L135">135</a>         top_iph-&gt;frag_off = iph-&gt;frag_off;
<a name="L136" href="source/net/ipv4/ah4.c#L136">136</a>         if (top_iph-&gt;ihl != 5) {
<a name="L137" href="source/net/ipv4/ah4.c#L137">137</a>                 top_iph-&gt;<a href="ident?i=daddr">daddr</a> = iph-&gt;<a href="ident?i=daddr">daddr</a>;
<a name="L138" href="source/net/ipv4/ah4.c#L138">138</a>                 <a href="ident?i=memcpy">memcpy</a>(top_iph+1, iph+1, top_iph-&gt;ihl*4 - sizeof(struct <a href="ident?i=iphdr">iphdr</a>));
<a name="L139" href="source/net/ipv4/ah4.c#L139">139</a>         }
<a name="L140" href="source/net/ipv4/ah4.c#L140">140</a> 
<a name="L141" href="source/net/ipv4/ah4.c#L141">141</a>         <a href="ident?i=kfree">kfree</a>(<a href="ident?i=AH_SKB_CB">AH_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=tmp">tmp</a>);
<a name="L142" href="source/net/ipv4/ah4.c#L142">142</a>         <a href="ident?i=xfrm_output_resume">xfrm_output_resume</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=err">err</a>);
<a name="L143" href="source/net/ipv4/ah4.c#L143">143</a> }
<a name="L144" href="source/net/ipv4/ah4.c#L144">144</a> 
<a name="L145" href="source/net/ipv4/ah4.c#L145">145</a> static int <a href="ident?i=ah_output">ah_output</a>(struct <a href="ident?i=xfrm_state">xfrm_state</a> *<a href="ident?i=x">x</a>, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L146" href="source/net/ipv4/ah4.c#L146">146</a> {
<a name="L147" href="source/net/ipv4/ah4.c#L147">147</a>         int <a href="ident?i=err">err</a>;
<a name="L148" href="source/net/ipv4/ah4.c#L148">148</a>         int nfrags;
<a name="L149" href="source/net/ipv4/ah4.c#L149">149</a>         int ihl;
<a name="L150" href="source/net/ipv4/ah4.c#L150">150</a>         <a href="ident?i=u8">u8</a> *icv;
<a name="L151" href="source/net/ipv4/ah4.c#L151">151</a>         struct <a href="ident?i=sk_buff">sk_buff</a> *trailer;
<a name="L152" href="source/net/ipv4/ah4.c#L152">152</a>         struct <a href="ident?i=crypto_ahash">crypto_ahash</a> *ahash;
<a name="L153" href="source/net/ipv4/ah4.c#L153">153</a>         struct <a href="ident?i=ahash_request">ahash_request</a> *<a href="ident?i=req">req</a>;
<a name="L154" href="source/net/ipv4/ah4.c#L154">154</a>         struct <a href="ident?i=scatterlist">scatterlist</a> *sg;
<a name="L155" href="source/net/ipv4/ah4.c#L155">155</a>         struct <a href="ident?i=iphdr">iphdr</a> *iph, *top_iph;
<a name="L156" href="source/net/ipv4/ah4.c#L156">156</a>         struct <a href="ident?i=ip_auth_hdr">ip_auth_hdr</a> *ah;
<a name="L157" href="source/net/ipv4/ah4.c#L157">157</a>         struct <a href="ident?i=ah_data">ah_data</a> *ahp;
<a name="L158" href="source/net/ipv4/ah4.c#L158">158</a>         int seqhi_len = 0;
<a name="L159" href="source/net/ipv4/ah4.c#L159">159</a>         <a href="ident?i=__be32">__be32</a> *seqhi;
<a name="L160" href="source/net/ipv4/ah4.c#L160">160</a>         int sglists = 0;
<a name="L161" href="source/net/ipv4/ah4.c#L161">161</a>         struct <a href="ident?i=scatterlist">scatterlist</a> *seqhisg;
<a name="L162" href="source/net/ipv4/ah4.c#L162">162</a> 
<a name="L163" href="source/net/ipv4/ah4.c#L163">163</a>         ahp = <a href="ident?i=x">x</a>-&gt;<a href="ident?i=data">data</a>;
<a name="L164" href="source/net/ipv4/ah4.c#L164">164</a>         ahash = ahp-&gt;ahash;
<a name="L165" href="source/net/ipv4/ah4.c#L165">165</a> 
<a name="L166" href="source/net/ipv4/ah4.c#L166">166</a>         if ((<a href="ident?i=err">err</a> = <a href="ident?i=skb_cow_data">skb_cow_data</a>(<a href="ident?i=skb">skb</a>, 0, &amp;trailer)) &lt; 0)
<a name="L167" href="source/net/ipv4/ah4.c#L167">167</a>                 goto <a href="ident?i=out">out</a>;
<a name="L168" href="source/net/ipv4/ah4.c#L168">168</a>         nfrags = <a href="ident?i=err">err</a>;
<a name="L169" href="source/net/ipv4/ah4.c#L169">169</a> 
<a name="L170" href="source/net/ipv4/ah4.c#L170">170</a>         <a href="ident?i=skb_push">skb_push</a>(<a href="ident?i=skb">skb</a>, -<a href="ident?i=skb_network_offset">skb_network_offset</a>(<a href="ident?i=skb">skb</a>));
<a name="L171" href="source/net/ipv4/ah4.c#L171">171</a>         ah = <a href="ident?i=ip_auth_hdr">ip_auth_hdr</a>(<a href="ident?i=skb">skb</a>);
<a name="L172" href="source/net/ipv4/ah4.c#L172">172</a>         ihl = <a href="ident?i=ip_hdrlen">ip_hdrlen</a>(<a href="ident?i=skb">skb</a>);
<a name="L173" href="source/net/ipv4/ah4.c#L173">173</a> 
<a name="L174" href="source/net/ipv4/ah4.c#L174">174</a>         if (<a href="ident?i=x">x</a>-&gt;props.<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=XFRM_STATE_ESN">XFRM_STATE_ESN</a>) {
<a name="L175" href="source/net/ipv4/ah4.c#L175">175</a>                 sglists = 1;
<a name="L176" href="source/net/ipv4/ah4.c#L176">176</a>                 seqhi_len = sizeof(*seqhi);
<a name="L177" href="source/net/ipv4/ah4.c#L177">177</a>         }
<a name="L178" href="source/net/ipv4/ah4.c#L178">178</a>         <a href="ident?i=err">err</a> = -<a href="ident?i=ENOMEM">ENOMEM</a>;
<a name="L179" href="source/net/ipv4/ah4.c#L179">179</a>         iph = <a href="ident?i=ah_alloc_tmp">ah_alloc_tmp</a>(ahash, nfrags + sglists, ihl + seqhi_len);
<a name="L180" href="source/net/ipv4/ah4.c#L180">180</a>         if (!iph)
<a name="L181" href="source/net/ipv4/ah4.c#L181">181</a>                 goto <a href="ident?i=out">out</a>;
<a name="L182" href="source/net/ipv4/ah4.c#L182">182</a>         seqhi = (<a href="ident?i=__be32">__be32</a> *)((char *)iph + ihl);
<a name="L183" href="source/net/ipv4/ah4.c#L183">183</a>         icv = <a href="ident?i=ah_tmp_icv">ah_tmp_icv</a>(ahash, seqhi, seqhi_len);
<a name="L184" href="source/net/ipv4/ah4.c#L184">184</a>         <a href="ident?i=req">req</a> = <a href="ident?i=ah_tmp_req">ah_tmp_req</a>(ahash, icv);
<a name="L185" href="source/net/ipv4/ah4.c#L185">185</a>         sg = <a href="ident?i=ah_req_sg">ah_req_sg</a>(ahash, <a href="ident?i=req">req</a>);
<a name="L186" href="source/net/ipv4/ah4.c#L186">186</a>         seqhisg = sg + nfrags;
<a name="L187" href="source/net/ipv4/ah4.c#L187">187</a> 
<a name="L188" href="source/net/ipv4/ah4.c#L188">188</a>         <a href="ident?i=memset">memset</a>(ah-&gt;auth_data, 0, ahp-&gt;icv_trunc_len);
<a name="L189" href="source/net/ipv4/ah4.c#L189">189</a> 
<a name="L190" href="source/net/ipv4/ah4.c#L190">190</a>         top_iph = <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>);
<a name="L191" href="source/net/ipv4/ah4.c#L191">191</a> 
<a name="L192" href="source/net/ipv4/ah4.c#L192">192</a>         iph-&gt;tos = top_iph-&gt;tos;
<a name="L193" href="source/net/ipv4/ah4.c#L193">193</a>         iph-&gt;<a href="ident?i=ttl">ttl</a> = top_iph-&gt;<a href="ident?i=ttl">ttl</a>;
<a name="L194" href="source/net/ipv4/ah4.c#L194">194</a>         iph-&gt;frag_off = top_iph-&gt;frag_off;
<a name="L195" href="source/net/ipv4/ah4.c#L195">195</a> 
<a name="L196" href="source/net/ipv4/ah4.c#L196">196</a>         if (top_iph-&gt;ihl != 5) {
<a name="L197" href="source/net/ipv4/ah4.c#L197">197</a>                 iph-&gt;<a href="ident?i=daddr">daddr</a> = top_iph-&gt;<a href="ident?i=daddr">daddr</a>;
<a name="L198" href="source/net/ipv4/ah4.c#L198">198</a>                 <a href="ident?i=memcpy">memcpy</a>(iph+1, top_iph+1, top_iph-&gt;ihl*4 - sizeof(struct <a href="ident?i=iphdr">iphdr</a>));
<a name="L199" href="source/net/ipv4/ah4.c#L199">199</a>                 <a href="ident?i=err">err</a> = <a href="ident?i=ip_clear_mutable_options">ip_clear_mutable_options</a>(top_iph, &amp;top_iph-&gt;<a href="ident?i=daddr">daddr</a>);
<a name="L200" href="source/net/ipv4/ah4.c#L200">200</a>                 if (<a href="ident?i=err">err</a>)
<a name="L201" href="source/net/ipv4/ah4.c#L201">201</a>                         goto out_free;
<a name="L202" href="source/net/ipv4/ah4.c#L202">202</a>         }
<a name="L203" href="source/net/ipv4/ah4.c#L203">203</a> 
<a name="L204" href="source/net/ipv4/ah4.c#L204">204</a>         ah-&gt;nexthdr = *<a href="ident?i=skb_mac_header">skb_mac_header</a>(<a href="ident?i=skb">skb</a>);
<a name="L205" href="source/net/ipv4/ah4.c#L205">205</a>         *<a href="ident?i=skb_mac_header">skb_mac_header</a>(<a href="ident?i=skb">skb</a>) = <a href="ident?i=IPPROTO_AH">IPPROTO_AH</a>;
<a name="L206" href="source/net/ipv4/ah4.c#L206">206</a> 
<a name="L207" href="source/net/ipv4/ah4.c#L207">207</a>         top_iph-&gt;tos = 0;
<a name="L208" href="source/net/ipv4/ah4.c#L208">208</a>         top_iph-&gt;tot_len = <a href="ident?i=htons">htons</a>(<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a>);
<a name="L209" href="source/net/ipv4/ah4.c#L209">209</a>         top_iph-&gt;frag_off = 0;
<a name="L210" href="source/net/ipv4/ah4.c#L210">210</a>         top_iph-&gt;<a href="ident?i=ttl">ttl</a> = 0;
<a name="L211" href="source/net/ipv4/ah4.c#L211">211</a>         top_iph-&gt;<a href="ident?i=check">check</a> = 0;
<a name="L212" href="source/net/ipv4/ah4.c#L212">212</a> 
<a name="L213" href="source/net/ipv4/ah4.c#L213">213</a>         if (<a href="ident?i=x">x</a>-&gt;props.<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=XFRM_STATE_ALIGN4">XFRM_STATE_ALIGN4</a>)
<a name="L214" href="source/net/ipv4/ah4.c#L214">214</a>                 ah-&gt;hdrlen  = (<a href="ident?i=XFRM_ALIGN4">XFRM_ALIGN4</a>(sizeof(*ah) + ahp-&gt;icv_trunc_len) &gt;&gt; 2) - 2;
<a name="L215" href="source/net/ipv4/ah4.c#L215">215</a>         else
<a name="L216" href="source/net/ipv4/ah4.c#L216">216</a>                 ah-&gt;hdrlen  = (<a href="ident?i=XFRM_ALIGN8">XFRM_ALIGN8</a>(sizeof(*ah) + ahp-&gt;icv_trunc_len) &gt;&gt; 2) - 2;
<a name="L217" href="source/net/ipv4/ah4.c#L217">217</a> 
<a name="L218" href="source/net/ipv4/ah4.c#L218">218</a>         ah-&gt;<a href="ident?i=reserved">reserved</a> = 0;
<a name="L219" href="source/net/ipv4/ah4.c#L219">219</a>         ah-&gt;<a href="ident?i=spi">spi</a> = <a href="ident?i=x">x</a>-&gt;<a href="ident?i=id">id</a>.<a href="ident?i=spi">spi</a>;
<a name="L220" href="source/net/ipv4/ah4.c#L220">220</a>         ah-&gt;seq_no = <a href="ident?i=htonl">htonl</a>(<a href="ident?i=XFRM_SKB_CB">XFRM_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=seq">seq</a>.<a href="ident?i=output">output</a>.low);
<a name="L221" href="source/net/ipv4/ah4.c#L221">221</a> 
<a name="L222" href="source/net/ipv4/ah4.c#L222">222</a>         <a href="ident?i=sg_init_table">sg_init_table</a>(sg, nfrags + sglists);
<a name="L223" href="source/net/ipv4/ah4.c#L223">223</a>         <a href="ident?i=skb_to_sgvec_nomark">skb_to_sgvec_nomark</a>(<a href="ident?i=skb">skb</a>, sg, 0, <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a>);
<a name="L224" href="source/net/ipv4/ah4.c#L224">224</a> 
<a name="L225" href="source/net/ipv4/ah4.c#L225">225</a>         if (<a href="ident?i=x">x</a>-&gt;props.<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=XFRM_STATE_ESN">XFRM_STATE_ESN</a>) {
<a name="L226" href="source/net/ipv4/ah4.c#L226">226</a>                 <b><i>/* Attach seqhi sg right after packet payload */</i></b>
<a name="L227" href="source/net/ipv4/ah4.c#L227">227</a>                 *seqhi = <a href="ident?i=htonl">htonl</a>(<a href="ident?i=XFRM_SKB_CB">XFRM_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=seq">seq</a>.<a href="ident?i=output">output</a>.<a href="ident?i=hi">hi</a>);
<a name="L228" href="source/net/ipv4/ah4.c#L228">228</a>                 <a href="ident?i=sg_set_buf">sg_set_buf</a>(seqhisg, seqhi, seqhi_len);
<a name="L229" href="source/net/ipv4/ah4.c#L229">229</a>         }
<a name="L230" href="source/net/ipv4/ah4.c#L230">230</a>         <a href="ident?i=ahash_request_set_crypt">ahash_request_set_crypt</a>(<a href="ident?i=req">req</a>, sg, icv, <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a> + seqhi_len);
<a name="L231" href="source/net/ipv4/ah4.c#L231">231</a>         <a href="ident?i=ahash_request_set_callback">ahash_request_set_callback</a>(<a href="ident?i=req">req</a>, 0, <a href="ident?i=ah_output_done">ah_output_done</a>, <a href="ident?i=skb">skb</a>);
<a name="L232" href="source/net/ipv4/ah4.c#L232">232</a> 
<a name="L233" href="source/net/ipv4/ah4.c#L233">233</a>         <a href="ident?i=AH_SKB_CB">AH_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=tmp">tmp</a> = iph;
<a name="L234" href="source/net/ipv4/ah4.c#L234">234</a> 
<a name="L235" href="source/net/ipv4/ah4.c#L235">235</a>         <a href="ident?i=err">err</a> = <a href="ident?i=crypto_ahash_digest">crypto_ahash_digest</a>(<a href="ident?i=req">req</a>);
<a name="L236" href="source/net/ipv4/ah4.c#L236">236</a>         if (<a href="ident?i=err">err</a>) {
<a name="L237" href="source/net/ipv4/ah4.c#L237">237</a>                 if (<a href="ident?i=err">err</a> == -<a href="ident?i=EINPROGRESS">EINPROGRESS</a>)
<a name="L238" href="source/net/ipv4/ah4.c#L238">238</a>                         goto <a href="ident?i=out">out</a>;
<a name="L239" href="source/net/ipv4/ah4.c#L239">239</a> 
<a name="L240" href="source/net/ipv4/ah4.c#L240">240</a>                 if (<a href="ident?i=err">err</a> == -<a href="ident?i=EBUSY">EBUSY</a>)
<a name="L241" href="source/net/ipv4/ah4.c#L241">241</a>                         <a href="ident?i=err">err</a> = <a href="ident?i=NET_XMIT_DROP">NET_XMIT_DROP</a>;
<a name="L242" href="source/net/ipv4/ah4.c#L242">242</a>                 goto out_free;
<a name="L243" href="source/net/ipv4/ah4.c#L243">243</a>         }
<a name="L244" href="source/net/ipv4/ah4.c#L244">244</a> 
<a name="L245" href="source/net/ipv4/ah4.c#L245">245</a>         <a href="ident?i=memcpy">memcpy</a>(ah-&gt;auth_data, icv, ahp-&gt;icv_trunc_len);
<a name="L246" href="source/net/ipv4/ah4.c#L246">246</a> 
<a name="L247" href="source/net/ipv4/ah4.c#L247">247</a>         top_iph-&gt;tos = iph-&gt;tos;
<a name="L248" href="source/net/ipv4/ah4.c#L248">248</a>         top_iph-&gt;<a href="ident?i=ttl">ttl</a> = iph-&gt;<a href="ident?i=ttl">ttl</a>;
<a name="L249" href="source/net/ipv4/ah4.c#L249">249</a>         top_iph-&gt;frag_off = iph-&gt;frag_off;
<a name="L250" href="source/net/ipv4/ah4.c#L250">250</a>         if (top_iph-&gt;ihl != 5) {
<a name="L251" href="source/net/ipv4/ah4.c#L251">251</a>                 top_iph-&gt;<a href="ident?i=daddr">daddr</a> = iph-&gt;<a href="ident?i=daddr">daddr</a>;
<a name="L252" href="source/net/ipv4/ah4.c#L252">252</a>                 <a href="ident?i=memcpy">memcpy</a>(top_iph+1, iph+1, top_iph-&gt;ihl*4 - sizeof(struct <a href="ident?i=iphdr">iphdr</a>));
<a name="L253" href="source/net/ipv4/ah4.c#L253">253</a>         }
<a name="L254" href="source/net/ipv4/ah4.c#L254">254</a> 
<a name="L255" href="source/net/ipv4/ah4.c#L255">255</a> out_free:
<a name="L256" href="source/net/ipv4/ah4.c#L256">256</a>         <a href="ident?i=kfree">kfree</a>(iph);
<a name="L257" href="source/net/ipv4/ah4.c#L257">257</a> <a href="ident?i=out">out</a>:
<a name="L258" href="source/net/ipv4/ah4.c#L258">258</a>         return <a href="ident?i=err">err</a>;
<a name="L259" href="source/net/ipv4/ah4.c#L259">259</a> }
<a name="L260" href="source/net/ipv4/ah4.c#L260">260</a> 
<a name="L261" href="source/net/ipv4/ah4.c#L261">261</a> static void <a href="ident?i=ah_input_done">ah_input_done</a>(struct <a href="ident?i=crypto_async_request">crypto_async_request</a> *<a href="ident?i=base">base</a>, int <a href="ident?i=err">err</a>)
<a name="L262" href="source/net/ipv4/ah4.c#L262">262</a> {
<a name="L263" href="source/net/ipv4/ah4.c#L263">263</a>         <a href="ident?i=u8">u8</a> *auth_data;
<a name="L264" href="source/net/ipv4/ah4.c#L264">264</a>         <a href="ident?i=u8">u8</a> *icv;
<a name="L265" href="source/net/ipv4/ah4.c#L265">265</a>         struct <a href="ident?i=iphdr">iphdr</a> *work_iph;
<a name="L266" href="source/net/ipv4/ah4.c#L266">266</a>         struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a> = <a href="ident?i=base">base</a>-&gt;<a href="ident?i=data">data</a>;
<a name="L267" href="source/net/ipv4/ah4.c#L267">267</a>         struct <a href="ident?i=xfrm_state">xfrm_state</a> *<a href="ident?i=x">x</a> = <a href="ident?i=xfrm_input_state">xfrm_input_state</a>(<a href="ident?i=skb">skb</a>);
<a name="L268" href="source/net/ipv4/ah4.c#L268">268</a>         struct <a href="ident?i=ah_data">ah_data</a> *ahp = <a href="ident?i=x">x</a>-&gt;<a href="ident?i=data">data</a>;
<a name="L269" href="source/net/ipv4/ah4.c#L269">269</a>         struct <a href="ident?i=ip_auth_hdr">ip_auth_hdr</a> *ah = <a href="ident?i=ip_auth_hdr">ip_auth_hdr</a>(<a href="ident?i=skb">skb</a>);
<a name="L270" href="source/net/ipv4/ah4.c#L270">270</a>         int ihl = <a href="ident?i=ip_hdrlen">ip_hdrlen</a>(<a href="ident?i=skb">skb</a>);
<a name="L271" href="source/net/ipv4/ah4.c#L271">271</a>         int ah_hlen = (ah-&gt;hdrlen + 2) &lt;&lt; 2;
<a name="L272" href="source/net/ipv4/ah4.c#L272">272</a> 
<a name="L273" href="source/net/ipv4/ah4.c#L273">273</a>         work_iph = <a href="ident?i=AH_SKB_CB">AH_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=tmp">tmp</a>;
<a name="L274" href="source/net/ipv4/ah4.c#L274">274</a>         auth_data = <a href="ident?i=ah_tmp_auth">ah_tmp_auth</a>(work_iph, ihl);
<a name="L275" href="source/net/ipv4/ah4.c#L275">275</a>         icv = <a href="ident?i=ah_tmp_icv">ah_tmp_icv</a>(ahp-&gt;ahash, auth_data, ahp-&gt;icv_trunc_len);
<a name="L276" href="source/net/ipv4/ah4.c#L276">276</a> 
<a name="L277" href="source/net/ipv4/ah4.c#L277">277</a>         <a href="ident?i=err">err</a> = <a href="ident?i=memcmp">memcmp</a>(icv, auth_data, ahp-&gt;icv_trunc_len) ? -<a href="ident?i=EBADMSG">EBADMSG</a>: 0;
<a name="L278" href="source/net/ipv4/ah4.c#L278">278</a>         if (<a href="ident?i=err">err</a>)
<a name="L279" href="source/net/ipv4/ah4.c#L279">279</a>                 goto <a href="ident?i=out">out</a>;
<a name="L280" href="source/net/ipv4/ah4.c#L280">280</a> 
<a name="L281" href="source/net/ipv4/ah4.c#L281">281</a>         <a href="ident?i=err">err</a> = ah-&gt;nexthdr;
<a name="L282" href="source/net/ipv4/ah4.c#L282">282</a> 
<a name="L283" href="source/net/ipv4/ah4.c#L283">283</a>         <a href="ident?i=skb">skb</a>-&gt;network_header += ah_hlen;
<a name="L284" href="source/net/ipv4/ah4.c#L284">284</a>         <a href="ident?i=memcpy">memcpy</a>(<a href="ident?i=skb_network_header">skb_network_header</a>(<a href="ident?i=skb">skb</a>), work_iph, ihl);
<a name="L285" href="source/net/ipv4/ah4.c#L285">285</a>         <a href="ident?i=__skb_pull">__skb_pull</a>(<a href="ident?i=skb">skb</a>, ah_hlen + ihl);
<a name="L286" href="source/net/ipv4/ah4.c#L286">286</a> 
<a name="L287" href="source/net/ipv4/ah4.c#L287">287</a>         if (<a href="ident?i=x">x</a>-&gt;props.<a href="ident?i=mode">mode</a> == <a href="ident?i=XFRM_MODE_TUNNEL">XFRM_MODE_TUNNEL</a>)
<a name="L288" href="source/net/ipv4/ah4.c#L288">288</a>                 <a href="ident?i=skb_reset_transport_header">skb_reset_transport_header</a>(<a href="ident?i=skb">skb</a>);
<a name="L289" href="source/net/ipv4/ah4.c#L289">289</a>         else
<a name="L290" href="source/net/ipv4/ah4.c#L290">290</a>                 <a href="ident?i=skb_set_transport_header">skb_set_transport_header</a>(<a href="ident?i=skb">skb</a>, -ihl);
<a name="L291" href="source/net/ipv4/ah4.c#L291">291</a> <a href="ident?i=out">out</a>:
<a name="L292" href="source/net/ipv4/ah4.c#L292">292</a>         <a href="ident?i=kfree">kfree</a>(<a href="ident?i=AH_SKB_CB">AH_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=tmp">tmp</a>);
<a name="L293" href="source/net/ipv4/ah4.c#L293">293</a>         <a href="ident?i=xfrm_input_resume">xfrm_input_resume</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=err">err</a>);
<a name="L294" href="source/net/ipv4/ah4.c#L294">294</a> }
<a name="L295" href="source/net/ipv4/ah4.c#L295">295</a> 
<a name="L296" href="source/net/ipv4/ah4.c#L296">296</a> static int <a href="ident?i=ah_input">ah_input</a>(struct <a href="ident?i=xfrm_state">xfrm_state</a> *<a href="ident?i=x">x</a>, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L297" href="source/net/ipv4/ah4.c#L297">297</a> {
<a name="L298" href="source/net/ipv4/ah4.c#L298">298</a>         int ah_hlen;
<a name="L299" href="source/net/ipv4/ah4.c#L299">299</a>         int ihl;
<a name="L300" href="source/net/ipv4/ah4.c#L300">300</a>         int nexthdr;
<a name="L301" href="source/net/ipv4/ah4.c#L301">301</a>         int nfrags;
<a name="L302" href="source/net/ipv4/ah4.c#L302">302</a>         <a href="ident?i=u8">u8</a> *auth_data;
<a name="L303" href="source/net/ipv4/ah4.c#L303">303</a>         <a href="ident?i=u8">u8</a> *icv;
<a name="L304" href="source/net/ipv4/ah4.c#L304">304</a>         struct <a href="ident?i=sk_buff">sk_buff</a> *trailer;
<a name="L305" href="source/net/ipv4/ah4.c#L305">305</a>         struct <a href="ident?i=crypto_ahash">crypto_ahash</a> *ahash;
<a name="L306" href="source/net/ipv4/ah4.c#L306">306</a>         struct <a href="ident?i=ahash_request">ahash_request</a> *<a href="ident?i=req">req</a>;
<a name="L307" href="source/net/ipv4/ah4.c#L307">307</a>         struct <a href="ident?i=scatterlist">scatterlist</a> *sg;
<a name="L308" href="source/net/ipv4/ah4.c#L308">308</a>         struct <a href="ident?i=iphdr">iphdr</a> *iph, *work_iph;
<a name="L309" href="source/net/ipv4/ah4.c#L309">309</a>         struct <a href="ident?i=ip_auth_hdr">ip_auth_hdr</a> *ah;
<a name="L310" href="source/net/ipv4/ah4.c#L310">310</a>         struct <a href="ident?i=ah_data">ah_data</a> *ahp;
<a name="L311" href="source/net/ipv4/ah4.c#L311">311</a>         int <a href="ident?i=err">err</a> = -<a href="ident?i=ENOMEM">ENOMEM</a>;
<a name="L312" href="source/net/ipv4/ah4.c#L312">312</a>         int seqhi_len = 0;
<a name="L313" href="source/net/ipv4/ah4.c#L313">313</a>         <a href="ident?i=__be32">__be32</a> *seqhi;
<a name="L314" href="source/net/ipv4/ah4.c#L314">314</a>         int sglists = 0;
<a name="L315" href="source/net/ipv4/ah4.c#L315">315</a>         struct <a href="ident?i=scatterlist">scatterlist</a> *seqhisg;
<a name="L316" href="source/net/ipv4/ah4.c#L316">316</a> 
<a name="L317" href="source/net/ipv4/ah4.c#L317">317</a>         if (!<a href="ident?i=pskb_may_pull">pskb_may_pull</a>(<a href="ident?i=skb">skb</a>, sizeof(*ah)))
<a name="L318" href="source/net/ipv4/ah4.c#L318">318</a>                 goto <a href="ident?i=out">out</a>;
<a name="L319" href="source/net/ipv4/ah4.c#L319">319</a> 
<a name="L320" href="source/net/ipv4/ah4.c#L320">320</a>         ah = (struct <a href="ident?i=ip_auth_hdr">ip_auth_hdr</a> *)<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=data">data</a>;
<a name="L321" href="source/net/ipv4/ah4.c#L321">321</a>         ahp = <a href="ident?i=x">x</a>-&gt;<a href="ident?i=data">data</a>;
<a name="L322" href="source/net/ipv4/ah4.c#L322">322</a>         ahash = ahp-&gt;ahash;
<a name="L323" href="source/net/ipv4/ah4.c#L323">323</a> 
<a name="L324" href="source/net/ipv4/ah4.c#L324">324</a>         nexthdr = ah-&gt;nexthdr;
<a name="L325" href="source/net/ipv4/ah4.c#L325">325</a>         ah_hlen = (ah-&gt;hdrlen + 2) &lt;&lt; 2;
<a name="L326" href="source/net/ipv4/ah4.c#L326">326</a> 
<a name="L327" href="source/net/ipv4/ah4.c#L327">327</a>         if (<a href="ident?i=x">x</a>-&gt;props.<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=XFRM_STATE_ALIGN4">XFRM_STATE_ALIGN4</a>) {
<a name="L328" href="source/net/ipv4/ah4.c#L328">328</a>                 if (ah_hlen != <a href="ident?i=XFRM_ALIGN4">XFRM_ALIGN4</a>(sizeof(*ah) + ahp-&gt;icv_full_len) &amp;&amp;
<a name="L329" href="source/net/ipv4/ah4.c#L329">329</a>                     ah_hlen != <a href="ident?i=XFRM_ALIGN4">XFRM_ALIGN4</a>(sizeof(*ah) + ahp-&gt;icv_trunc_len))
<a name="L330" href="source/net/ipv4/ah4.c#L330">330</a>                         goto <a href="ident?i=out">out</a>;
<a name="L331" href="source/net/ipv4/ah4.c#L331">331</a>         } else {
<a name="L332" href="source/net/ipv4/ah4.c#L332">332</a>                 if (ah_hlen != <a href="ident?i=XFRM_ALIGN8">XFRM_ALIGN8</a>(sizeof(*ah) + ahp-&gt;icv_full_len) &amp;&amp;
<a name="L333" href="source/net/ipv4/ah4.c#L333">333</a>                     ah_hlen != <a href="ident?i=XFRM_ALIGN8">XFRM_ALIGN8</a>(sizeof(*ah) + ahp-&gt;icv_trunc_len))
<a name="L334" href="source/net/ipv4/ah4.c#L334">334</a>                         goto <a href="ident?i=out">out</a>;
<a name="L335" href="source/net/ipv4/ah4.c#L335">335</a>         }
<a name="L336" href="source/net/ipv4/ah4.c#L336">336</a> 
<a name="L337" href="source/net/ipv4/ah4.c#L337">337</a>         if (!<a href="ident?i=pskb_may_pull">pskb_may_pull</a>(<a href="ident?i=skb">skb</a>, ah_hlen))
<a name="L338" href="source/net/ipv4/ah4.c#L338">338</a>                 goto <a href="ident?i=out">out</a>;
<a name="L339" href="source/net/ipv4/ah4.c#L339">339</a> 
<a name="L340" href="source/net/ipv4/ah4.c#L340">340</a>         <b><i>/* We are going to _remove_ AH header to keep sockets happy,</i></b>
<a name="L341" href="source/net/ipv4/ah4.c#L341">341</a> <b><i>         * so... Later this can change. */</i></b>
<a name="L342" href="source/net/ipv4/ah4.c#L342">342</a>         if (<a href="ident?i=skb_unclone">skb_unclone</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=GFP_ATOMIC">GFP_ATOMIC</a>))
<a name="L343" href="source/net/ipv4/ah4.c#L343">343</a>                 goto <a href="ident?i=out">out</a>;
<a name="L344" href="source/net/ipv4/ah4.c#L344">344</a> 
<a name="L345" href="source/net/ipv4/ah4.c#L345">345</a>         <a href="ident?i=skb">skb</a>-&gt;ip_summed = <a href="ident?i=CHECKSUM_NONE">CHECKSUM_NONE</a>;
<a name="L346" href="source/net/ipv4/ah4.c#L346">346</a> 
<a name="L347" href="source/net/ipv4/ah4.c#L347">347</a> 
<a name="L348" href="source/net/ipv4/ah4.c#L348">348</a>         if ((<a href="ident?i=err">err</a> = <a href="ident?i=skb_cow_data">skb_cow_data</a>(<a href="ident?i=skb">skb</a>, 0, &amp;trailer)) &lt; 0)
<a name="L349" href="source/net/ipv4/ah4.c#L349">349</a>                 goto <a href="ident?i=out">out</a>;
<a name="L350" href="source/net/ipv4/ah4.c#L350">350</a>         nfrags = <a href="ident?i=err">err</a>;
<a name="L351" href="source/net/ipv4/ah4.c#L351">351</a> 
<a name="L352" href="source/net/ipv4/ah4.c#L352">352</a>         ah = (struct <a href="ident?i=ip_auth_hdr">ip_auth_hdr</a> *)<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=data">data</a>;
<a name="L353" href="source/net/ipv4/ah4.c#L353">353</a>         iph = <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>);
<a name="L354" href="source/net/ipv4/ah4.c#L354">354</a>         ihl = <a href="ident?i=ip_hdrlen">ip_hdrlen</a>(<a href="ident?i=skb">skb</a>);
<a name="L355" href="source/net/ipv4/ah4.c#L355">355</a> 
<a name="L356" href="source/net/ipv4/ah4.c#L356">356</a>         if (<a href="ident?i=x">x</a>-&gt;props.<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=XFRM_STATE_ESN">XFRM_STATE_ESN</a>) {
<a name="L357" href="source/net/ipv4/ah4.c#L357">357</a>                 sglists = 1;
<a name="L358" href="source/net/ipv4/ah4.c#L358">358</a>                 seqhi_len = sizeof(*seqhi);
<a name="L359" href="source/net/ipv4/ah4.c#L359">359</a>         }
<a name="L360" href="source/net/ipv4/ah4.c#L360">360</a> 
<a name="L361" href="source/net/ipv4/ah4.c#L361">361</a>         work_iph = <a href="ident?i=ah_alloc_tmp">ah_alloc_tmp</a>(ahash, nfrags + sglists, ihl +
<a name="L362" href="source/net/ipv4/ah4.c#L362">362</a>                                 ahp-&gt;icv_trunc_len + seqhi_len);
<a name="L363" href="source/net/ipv4/ah4.c#L363">363</a>         if (!work_iph)
<a name="L364" href="source/net/ipv4/ah4.c#L364">364</a>                 goto <a href="ident?i=out">out</a>;
<a name="L365" href="source/net/ipv4/ah4.c#L365">365</a> 
<a name="L366" href="source/net/ipv4/ah4.c#L366">366</a>         seqhi = (<a href="ident?i=__be32">__be32</a> *)((char *)work_iph + ihl);
<a name="L367" href="source/net/ipv4/ah4.c#L367">367</a>         auth_data = <a href="ident?i=ah_tmp_auth">ah_tmp_auth</a>(seqhi, seqhi_len);
<a name="L368" href="source/net/ipv4/ah4.c#L368">368</a>         icv = <a href="ident?i=ah_tmp_icv">ah_tmp_icv</a>(ahash, auth_data, ahp-&gt;icv_trunc_len);
<a name="L369" href="source/net/ipv4/ah4.c#L369">369</a>         <a href="ident?i=req">req</a> = <a href="ident?i=ah_tmp_req">ah_tmp_req</a>(ahash, icv);
<a name="L370" href="source/net/ipv4/ah4.c#L370">370</a>         sg = <a href="ident?i=ah_req_sg">ah_req_sg</a>(ahash, <a href="ident?i=req">req</a>);
<a name="L371" href="source/net/ipv4/ah4.c#L371">371</a>         seqhisg = sg + nfrags;
<a name="L372" href="source/net/ipv4/ah4.c#L372">372</a> 
<a name="L373" href="source/net/ipv4/ah4.c#L373">373</a>         <a href="ident?i=memcpy">memcpy</a>(work_iph, iph, ihl);
<a name="L374" href="source/net/ipv4/ah4.c#L374">374</a>         <a href="ident?i=memcpy">memcpy</a>(auth_data, ah-&gt;auth_data, ahp-&gt;icv_trunc_len);
<a name="L375" href="source/net/ipv4/ah4.c#L375">375</a>         <a href="ident?i=memset">memset</a>(ah-&gt;auth_data, 0, ahp-&gt;icv_trunc_len);
<a name="L376" href="source/net/ipv4/ah4.c#L376">376</a> 
<a name="L377" href="source/net/ipv4/ah4.c#L377">377</a>         iph-&gt;<a href="ident?i=ttl">ttl</a> = 0;
<a name="L378" href="source/net/ipv4/ah4.c#L378">378</a>         iph-&gt;tos = 0;
<a name="L379" href="source/net/ipv4/ah4.c#L379">379</a>         iph-&gt;frag_off = 0;
<a name="L380" href="source/net/ipv4/ah4.c#L380">380</a>         iph-&gt;<a href="ident?i=check">check</a> = 0;
<a name="L381" href="source/net/ipv4/ah4.c#L381">381</a>         if (ihl &gt; sizeof(*iph)) {
<a name="L382" href="source/net/ipv4/ah4.c#L382">382</a>                 <a href="ident?i=__be32">__be32</a> <a href="ident?i=dummy">dummy</a>;
<a name="L383" href="source/net/ipv4/ah4.c#L383">383</a>                 <a href="ident?i=err">err</a> = <a href="ident?i=ip_clear_mutable_options">ip_clear_mutable_options</a>(iph, &amp;<a href="ident?i=dummy">dummy</a>);
<a name="L384" href="source/net/ipv4/ah4.c#L384">384</a>                 if (<a href="ident?i=err">err</a>)
<a name="L385" href="source/net/ipv4/ah4.c#L385">385</a>                         goto out_free;
<a name="L386" href="source/net/ipv4/ah4.c#L386">386</a>         }
<a name="L387" href="source/net/ipv4/ah4.c#L387">387</a> 
<a name="L388" href="source/net/ipv4/ah4.c#L388">388</a>         <a href="ident?i=skb_push">skb_push</a>(<a href="ident?i=skb">skb</a>, ihl);
<a name="L389" href="source/net/ipv4/ah4.c#L389">389</a> 
<a name="L390" href="source/net/ipv4/ah4.c#L390">390</a>         <a href="ident?i=sg_init_table">sg_init_table</a>(sg, nfrags + sglists);
<a name="L391" href="source/net/ipv4/ah4.c#L391">391</a>         <a href="ident?i=skb_to_sgvec_nomark">skb_to_sgvec_nomark</a>(<a href="ident?i=skb">skb</a>, sg, 0, <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a>);
<a name="L392" href="source/net/ipv4/ah4.c#L392">392</a> 
<a name="L393" href="source/net/ipv4/ah4.c#L393">393</a>         if (<a href="ident?i=x">x</a>-&gt;props.<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=XFRM_STATE_ESN">XFRM_STATE_ESN</a>) {
<a name="L394" href="source/net/ipv4/ah4.c#L394">394</a>                 <b><i>/* Attach seqhi sg right after packet payload */</i></b>
<a name="L395" href="source/net/ipv4/ah4.c#L395">395</a>                 *seqhi = <a href="ident?i=XFRM_SKB_CB">XFRM_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=seq">seq</a>.<a href="ident?i=input">input</a>.<a href="ident?i=hi">hi</a>;
<a name="L396" href="source/net/ipv4/ah4.c#L396">396</a>                 <a href="ident?i=sg_set_buf">sg_set_buf</a>(seqhisg, seqhi, seqhi_len);
<a name="L397" href="source/net/ipv4/ah4.c#L397">397</a>         }
<a name="L398" href="source/net/ipv4/ah4.c#L398">398</a>         <a href="ident?i=ahash_request_set_crypt">ahash_request_set_crypt</a>(<a href="ident?i=req">req</a>, sg, icv, <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a> + seqhi_len);
<a name="L399" href="source/net/ipv4/ah4.c#L399">399</a>         <a href="ident?i=ahash_request_set_callback">ahash_request_set_callback</a>(<a href="ident?i=req">req</a>, 0, <a href="ident?i=ah_input_done">ah_input_done</a>, <a href="ident?i=skb">skb</a>);
<a name="L400" href="source/net/ipv4/ah4.c#L400">400</a> 
<a name="L401" href="source/net/ipv4/ah4.c#L401">401</a>         <a href="ident?i=AH_SKB_CB">AH_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=tmp">tmp</a> = work_iph;
<a name="L402" href="source/net/ipv4/ah4.c#L402">402</a> 
<a name="L403" href="source/net/ipv4/ah4.c#L403">403</a>         <a href="ident?i=err">err</a> = <a href="ident?i=crypto_ahash_digest">crypto_ahash_digest</a>(<a href="ident?i=req">req</a>);
<a name="L404" href="source/net/ipv4/ah4.c#L404">404</a>         if (<a href="ident?i=err">err</a>) {
<a name="L405" href="source/net/ipv4/ah4.c#L405">405</a>                 if (<a href="ident?i=err">err</a> == -<a href="ident?i=EINPROGRESS">EINPROGRESS</a>)
<a name="L406" href="source/net/ipv4/ah4.c#L406">406</a>                         goto <a href="ident?i=out">out</a>;
<a name="L407" href="source/net/ipv4/ah4.c#L407">407</a> 
<a name="L408" href="source/net/ipv4/ah4.c#L408">408</a>                 goto out_free;
<a name="L409" href="source/net/ipv4/ah4.c#L409">409</a>         }
<a name="L410" href="source/net/ipv4/ah4.c#L410">410</a> 
<a name="L411" href="source/net/ipv4/ah4.c#L411">411</a>         <a href="ident?i=err">err</a> = <a href="ident?i=memcmp">memcmp</a>(icv, auth_data, ahp-&gt;icv_trunc_len) ? -<a href="ident?i=EBADMSG">EBADMSG</a>: 0;
<a name="L412" href="source/net/ipv4/ah4.c#L412">412</a>         if (<a href="ident?i=err">err</a>)
<a name="L413" href="source/net/ipv4/ah4.c#L413">413</a>                 goto out_free;
<a name="L414" href="source/net/ipv4/ah4.c#L414">414</a> 
<a name="L415" href="source/net/ipv4/ah4.c#L415">415</a>         <a href="ident?i=skb">skb</a>-&gt;network_header += ah_hlen;
<a name="L416" href="source/net/ipv4/ah4.c#L416">416</a>         <a href="ident?i=memcpy">memcpy</a>(<a href="ident?i=skb_network_header">skb_network_header</a>(<a href="ident?i=skb">skb</a>), work_iph, ihl);
<a name="L417" href="source/net/ipv4/ah4.c#L417">417</a>         <a href="ident?i=__skb_pull">__skb_pull</a>(<a href="ident?i=skb">skb</a>, ah_hlen + ihl);
<a name="L418" href="source/net/ipv4/ah4.c#L418">418</a>         if (<a href="ident?i=x">x</a>-&gt;props.<a href="ident?i=mode">mode</a> == <a href="ident?i=XFRM_MODE_TUNNEL">XFRM_MODE_TUNNEL</a>)
<a name="L419" href="source/net/ipv4/ah4.c#L419">419</a>                 <a href="ident?i=skb_reset_transport_header">skb_reset_transport_header</a>(<a href="ident?i=skb">skb</a>);
<a name="L420" href="source/net/ipv4/ah4.c#L420">420</a>         else
<a name="L421" href="source/net/ipv4/ah4.c#L421">421</a>                 <a href="ident?i=skb_set_transport_header">skb_set_transport_header</a>(<a href="ident?i=skb">skb</a>, -ihl);
<a name="L422" href="source/net/ipv4/ah4.c#L422">422</a> 
<a name="L423" href="source/net/ipv4/ah4.c#L423">423</a>         <a href="ident?i=err">err</a> = nexthdr;
<a name="L424" href="source/net/ipv4/ah4.c#L424">424</a> 
<a name="L425" href="source/net/ipv4/ah4.c#L425">425</a> out_free:
<a name="L426" href="source/net/ipv4/ah4.c#L426">426</a>         <a href="ident?i=kfree">kfree</a> (work_iph);
<a name="L427" href="source/net/ipv4/ah4.c#L427">427</a> <a href="ident?i=out">out</a>:
<a name="L428" href="source/net/ipv4/ah4.c#L428">428</a>         return <a href="ident?i=err">err</a>;
<a name="L429" href="source/net/ipv4/ah4.c#L429">429</a> }
<a name="L430" href="source/net/ipv4/ah4.c#L430">430</a> 
<a name="L431" href="source/net/ipv4/ah4.c#L431">431</a> static int <a href="ident?i=ah4_err">ah4_err</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, <a href="ident?i=u32">u32</a> <a href="ident?i=info">info</a>)
<a name="L432" href="source/net/ipv4/ah4.c#L432">432</a> {
<a name="L433" href="source/net/ipv4/ah4.c#L433">433</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=dev">dev</a>);
<a name="L434" href="source/net/ipv4/ah4.c#L434">434</a>         const struct <a href="ident?i=iphdr">iphdr</a> *iph = (const struct <a href="ident?i=iphdr">iphdr</a> *)<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=data">data</a>;
<a name="L435" href="source/net/ipv4/ah4.c#L435">435</a>         struct <a href="ident?i=ip_auth_hdr">ip_auth_hdr</a> *ah = (struct <a href="ident?i=ip_auth_hdr">ip_auth_hdr</a> *)(<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=data">data</a>+(iph-&gt;ihl&lt;&lt;2));
<a name="L436" href="source/net/ipv4/ah4.c#L436">436</a>         struct <a href="ident?i=xfrm_state">xfrm_state</a> *<a href="ident?i=x">x</a>;
<a name="L437" href="source/net/ipv4/ah4.c#L437">437</a> 
<a name="L438" href="source/net/ipv4/ah4.c#L438">438</a>         switch (<a href="ident?i=icmp_hdr">icmp_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=type">type</a>) {
<a name="L439" href="source/net/ipv4/ah4.c#L439">439</a>         case <a href="ident?i=ICMP_DEST_UNREACH">ICMP_DEST_UNREACH</a>:
<a name="L440" href="source/net/ipv4/ah4.c#L440">440</a>                 if (<a href="ident?i=icmp_hdr">icmp_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=code">code</a> != <a href="ident?i=ICMP_FRAG_NEEDED">ICMP_FRAG_NEEDED</a>)
<a name="L441" href="source/net/ipv4/ah4.c#L441">441</a>                         return 0;
<a name="L442" href="source/net/ipv4/ah4.c#L442">442</a>         case <a href="ident?i=ICMP_REDIRECT">ICMP_REDIRECT</a>:
<a name="L443" href="source/net/ipv4/ah4.c#L443">443</a>                 break;
<a name="L444" href="source/net/ipv4/ah4.c#L444">444</a>         default:
<a name="L445" href="source/net/ipv4/ah4.c#L445">445</a>                 return 0;
<a name="L446" href="source/net/ipv4/ah4.c#L446">446</a>         }
<a name="L447" href="source/net/ipv4/ah4.c#L447">447</a> 
<a name="L448" href="source/net/ipv4/ah4.c#L448">448</a>         <a href="ident?i=x">x</a> = <a href="ident?i=xfrm_state_lookup">xfrm_state_lookup</a>(<a href="ident?i=net">net</a>, <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=mark">mark</a>, (const <a href="ident?i=xfrm_address_t">xfrm_address_t</a> *)&amp;iph-&gt;<a href="ident?i=daddr">daddr</a>,
<a name="L449" href="source/net/ipv4/ah4.c#L449">449</a>                               ah-&gt;<a href="ident?i=spi">spi</a>, <a href="ident?i=IPPROTO_AH">IPPROTO_AH</a>, <a href="ident?i=AF_INET">AF_INET</a>);
<a name="L450" href="source/net/ipv4/ah4.c#L450">450</a>         if (!<a href="ident?i=x">x</a>)
<a name="L451" href="source/net/ipv4/ah4.c#L451">451</a>                 return 0;
<a name="L452" href="source/net/ipv4/ah4.c#L452">452</a> 
<a name="L453" href="source/net/ipv4/ah4.c#L453">453</a>         if (<a href="ident?i=icmp_hdr">icmp_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=type">type</a> == <a href="ident?i=ICMP_DEST_UNREACH">ICMP_DEST_UNREACH</a>)
<a name="L454" href="source/net/ipv4/ah4.c#L454">454</a>                 <a href="ident?i=ipv4_update_pmtu">ipv4_update_pmtu</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=net">net</a>, <a href="ident?i=info">info</a>, 0, 0, <a href="ident?i=IPPROTO_AH">IPPROTO_AH</a>, 0);
<a name="L455" href="source/net/ipv4/ah4.c#L455">455</a>         else
<a name="L456" href="source/net/ipv4/ah4.c#L456">456</a>                 <a href="ident?i=ipv4_redirect">ipv4_redirect</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=net">net</a>, 0, 0, <a href="ident?i=IPPROTO_AH">IPPROTO_AH</a>, 0);
<a name="L457" href="source/net/ipv4/ah4.c#L457">457</a>         <a href="ident?i=xfrm_state_put">xfrm_state_put</a>(<a href="ident?i=x">x</a>);
<a name="L458" href="source/net/ipv4/ah4.c#L458">458</a> 
<a name="L459" href="source/net/ipv4/ah4.c#L459">459</a>         return 0;
<a name="L460" href="source/net/ipv4/ah4.c#L460">460</a> }
<a name="L461" href="source/net/ipv4/ah4.c#L461">461</a> 
<a name="L462" href="source/net/ipv4/ah4.c#L462">462</a> static int <a href="ident?i=ah_init_state">ah_init_state</a>(struct <a href="ident?i=xfrm_state">xfrm_state</a> *<a href="ident?i=x">x</a>)
<a name="L463" href="source/net/ipv4/ah4.c#L463">463</a> {
<a name="L464" href="source/net/ipv4/ah4.c#L464">464</a>         struct <a href="ident?i=ah_data">ah_data</a> *ahp = <a href="ident?i=NULL">NULL</a>;
<a name="L465" href="source/net/ipv4/ah4.c#L465">465</a>         struct <a href="ident?i=xfrm_algo_desc">xfrm_algo_desc</a> *aalg_desc;
<a name="L466" href="source/net/ipv4/ah4.c#L466">466</a>         struct <a href="ident?i=crypto_ahash">crypto_ahash</a> *ahash;
<a name="L467" href="source/net/ipv4/ah4.c#L467">467</a> 
<a name="L468" href="source/net/ipv4/ah4.c#L468">468</a>         if (!<a href="ident?i=x">x</a>-&gt;aalg)
<a name="L469" href="source/net/ipv4/ah4.c#L469">469</a>                 goto <a href="ident?i=error">error</a>;
<a name="L470" href="source/net/ipv4/ah4.c#L470">470</a> 
<a name="L471" href="source/net/ipv4/ah4.c#L471">471</a>         if (<a href="ident?i=x">x</a>-&gt;encap)
<a name="L472" href="source/net/ipv4/ah4.c#L472">472</a>                 goto <a href="ident?i=error">error</a>;
<a name="L473" href="source/net/ipv4/ah4.c#L473">473</a> 
<a name="L474" href="source/net/ipv4/ah4.c#L474">474</a>         ahp = <a href="ident?i=kzalloc">kzalloc</a>(sizeof(*ahp), <a href="ident?i=GFP_KERNEL">GFP_KERNEL</a>);
<a name="L475" href="source/net/ipv4/ah4.c#L475">475</a>         if (!ahp)
<a name="L476" href="source/net/ipv4/ah4.c#L476">476</a>                 return -<a href="ident?i=ENOMEM">ENOMEM</a>;
<a name="L477" href="source/net/ipv4/ah4.c#L477">477</a> 
<a name="L478" href="source/net/ipv4/ah4.c#L478">478</a>         ahash = <a href="ident?i=crypto_alloc_ahash">crypto_alloc_ahash</a>(<a href="ident?i=x">x</a>-&gt;aalg-&gt;alg_name, 0, 0);
<a name="L479" href="source/net/ipv4/ah4.c#L479">479</a>         if (<a href="ident?i=IS_ERR">IS_ERR</a>(ahash))
<a name="L480" href="source/net/ipv4/ah4.c#L480">480</a>                 goto <a href="ident?i=error">error</a>;
<a name="L481" href="source/net/ipv4/ah4.c#L481">481</a> 
<a name="L482" href="source/net/ipv4/ah4.c#L482">482</a>         ahp-&gt;ahash = ahash;
<a name="L483" href="source/net/ipv4/ah4.c#L483">483</a>         if (<a href="ident?i=crypto_ahash_setkey">crypto_ahash_setkey</a>(ahash, <a href="ident?i=x">x</a>-&gt;aalg-&gt;alg_key,
<a name="L484" href="source/net/ipv4/ah4.c#L484">484</a>                                 (<a href="ident?i=x">x</a>-&gt;aalg-&gt;alg_key_len + 7) / 8))
<a name="L485" href="source/net/ipv4/ah4.c#L485">485</a>                 goto <a href="ident?i=error">error</a>;
<a name="L486" href="source/net/ipv4/ah4.c#L486">486</a> 
<a name="L487" href="source/net/ipv4/ah4.c#L487">487</a>         <b><i>/*</i></b>
<a name="L488" href="source/net/ipv4/ah4.c#L488">488</a> <b><i>         * Lookup the algorithm description maintained by xfrm_algo,</i></b>
<a name="L489" href="source/net/ipv4/ah4.c#L489">489</a> <b><i>         * verify crypto transform properties, and store information</i></b>
<a name="L490" href="source/net/ipv4/ah4.c#L490">490</a> <b><i>         * we need for AH processing.  This lookup cannot fail here</i></b>
<a name="L491" href="source/net/ipv4/ah4.c#L491">491</a> <b><i>         * after a successful crypto_alloc_ahash().</i></b>
<a name="L492" href="source/net/ipv4/ah4.c#L492">492</a> <b><i>         */</i></b>
<a name="L493" href="source/net/ipv4/ah4.c#L493">493</a>         aalg_desc = <a href="ident?i=xfrm_aalg_get_byname">xfrm_aalg_get_byname</a>(<a href="ident?i=x">x</a>-&gt;aalg-&gt;alg_name, 0);
<a name="L494" href="source/net/ipv4/ah4.c#L494">494</a>         <a href="ident?i=BUG_ON">BUG_ON</a>(!aalg_desc);
<a name="L495" href="source/net/ipv4/ah4.c#L495">495</a> 
<a name="L496" href="source/net/ipv4/ah4.c#L496">496</a>         if (aalg_desc-&gt;<a href="ident?i=uinfo">uinfo</a>.auth.icv_fullbits/8 !=
<a name="L497" href="source/net/ipv4/ah4.c#L497">497</a>             <a href="ident?i=crypto_ahash_digestsize">crypto_ahash_digestsize</a>(ahash)) {
<a name="L498" href="source/net/ipv4/ah4.c#L498">498</a>                 <a href="ident?i=pr_info">pr_info</a>(<i>"%s: %s digestsize %u != %hu\n"</i>,
<a name="L499" href="source/net/ipv4/ah4.c#L499">499</a>                         <a href="ident?i=__func__">__func__</a>, <a href="ident?i=x">x</a>-&gt;aalg-&gt;alg_name,
<a name="L500" href="source/net/ipv4/ah4.c#L500">500</a>                         <a href="ident?i=crypto_ahash_digestsize">crypto_ahash_digestsize</a>(ahash),
<a name="L501" href="source/net/ipv4/ah4.c#L501">501</a>                         aalg_desc-&gt;<a href="ident?i=uinfo">uinfo</a>.auth.icv_fullbits / 8);
<a name="L502" href="source/net/ipv4/ah4.c#L502">502</a>                 goto <a href="ident?i=error">error</a>;
<a name="L503" href="source/net/ipv4/ah4.c#L503">503</a>         }
<a name="L504" href="source/net/ipv4/ah4.c#L504">504</a> 
<a name="L505" href="source/net/ipv4/ah4.c#L505">505</a>         ahp-&gt;icv_full_len = aalg_desc-&gt;<a href="ident?i=uinfo">uinfo</a>.auth.icv_fullbits/8;
<a name="L506" href="source/net/ipv4/ah4.c#L506">506</a>         ahp-&gt;icv_trunc_len = <a href="ident?i=x">x</a>-&gt;aalg-&gt;alg_trunc_len/8;
<a name="L507" href="source/net/ipv4/ah4.c#L507">507</a> 
<a name="L508" href="source/net/ipv4/ah4.c#L508">508</a>         if (<a href="ident?i=x">x</a>-&gt;props.<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=XFRM_STATE_ALIGN4">XFRM_STATE_ALIGN4</a>)
<a name="L509" href="source/net/ipv4/ah4.c#L509">509</a>                 <a href="ident?i=x">x</a>-&gt;props.<a href="ident?i=header_len">header_len</a> = <a href="ident?i=XFRM_ALIGN4">XFRM_ALIGN4</a>(sizeof(struct <a href="ident?i=ip_auth_hdr">ip_auth_hdr</a>) +
<a name="L510" href="source/net/ipv4/ah4.c#L510">510</a>                                                   ahp-&gt;icv_trunc_len);
<a name="L511" href="source/net/ipv4/ah4.c#L511">511</a>         else
<a name="L512" href="source/net/ipv4/ah4.c#L512">512</a>                 <a href="ident?i=x">x</a>-&gt;props.<a href="ident?i=header_len">header_len</a> = <a href="ident?i=XFRM_ALIGN8">XFRM_ALIGN8</a>(sizeof(struct <a href="ident?i=ip_auth_hdr">ip_auth_hdr</a>) +
<a name="L513" href="source/net/ipv4/ah4.c#L513">513</a>                                                   ahp-&gt;icv_trunc_len);
<a name="L514" href="source/net/ipv4/ah4.c#L514">514</a>         if (<a href="ident?i=x">x</a>-&gt;props.<a href="ident?i=mode">mode</a> == <a href="ident?i=XFRM_MODE_TUNNEL">XFRM_MODE_TUNNEL</a>)
<a name="L515" href="source/net/ipv4/ah4.c#L515">515</a>                 <a href="ident?i=x">x</a>-&gt;props.<a href="ident?i=header_len">header_len</a> += sizeof(struct <a href="ident?i=iphdr">iphdr</a>);
<a name="L516" href="source/net/ipv4/ah4.c#L516">516</a>         <a href="ident?i=x">x</a>-&gt;<a href="ident?i=data">data</a> = ahp;
<a name="L517" href="source/net/ipv4/ah4.c#L517">517</a> 
<a name="L518" href="source/net/ipv4/ah4.c#L518">518</a>         return 0;
<a name="L519" href="source/net/ipv4/ah4.c#L519">519</a> 
<a name="L520" href="source/net/ipv4/ah4.c#L520">520</a> <a href="ident?i=error">error</a>:
<a name="L521" href="source/net/ipv4/ah4.c#L521">521</a>         if (ahp) {
<a name="L522" href="source/net/ipv4/ah4.c#L522">522</a>                 <a href="ident?i=crypto_free_ahash">crypto_free_ahash</a>(ahp-&gt;ahash);
<a name="L523" href="source/net/ipv4/ah4.c#L523">523</a>                 <a href="ident?i=kfree">kfree</a>(ahp);
<a name="L524" href="source/net/ipv4/ah4.c#L524">524</a>         }
<a name="L525" href="source/net/ipv4/ah4.c#L525">525</a>         return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L526" href="source/net/ipv4/ah4.c#L526">526</a> }
<a name="L527" href="source/net/ipv4/ah4.c#L527">527</a> 
<a name="L528" href="source/net/ipv4/ah4.c#L528">528</a> static void <a href="ident?i=ah_destroy">ah_destroy</a>(struct <a href="ident?i=xfrm_state">xfrm_state</a> *<a href="ident?i=x">x</a>)
<a name="L529" href="source/net/ipv4/ah4.c#L529">529</a> {
<a name="L530" href="source/net/ipv4/ah4.c#L530">530</a>         struct <a href="ident?i=ah_data">ah_data</a> *ahp = <a href="ident?i=x">x</a>-&gt;<a href="ident?i=data">data</a>;
<a name="L531" href="source/net/ipv4/ah4.c#L531">531</a> 
<a name="L532" href="source/net/ipv4/ah4.c#L532">532</a>         if (!ahp)
<a name="L533" href="source/net/ipv4/ah4.c#L533">533</a>                 return;
<a name="L534" href="source/net/ipv4/ah4.c#L534">534</a> 
<a name="L535" href="source/net/ipv4/ah4.c#L535">535</a>         <a href="ident?i=crypto_free_ahash">crypto_free_ahash</a>(ahp-&gt;ahash);
<a name="L536" href="source/net/ipv4/ah4.c#L536">536</a>         <a href="ident?i=kfree">kfree</a>(ahp);
<a name="L537" href="source/net/ipv4/ah4.c#L537">537</a> }
<a name="L538" href="source/net/ipv4/ah4.c#L538">538</a> 
<a name="L539" href="source/net/ipv4/ah4.c#L539">539</a> static int <a href="ident?i=ah4_rcv_cb">ah4_rcv_cb</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, int <a href="ident?i=err">err</a>)
<a name="L540" href="source/net/ipv4/ah4.c#L540">540</a> {
<a name="L541" href="source/net/ipv4/ah4.c#L541">541</a>         return 0;
<a name="L542" href="source/net/ipv4/ah4.c#L542">542</a> }
<a name="L543" href="source/net/ipv4/ah4.c#L543">543</a> 
<a name="L544" href="source/net/ipv4/ah4.c#L544">544</a> static const struct <a href="ident?i=xfrm_type">xfrm_type</a> <a href="ident?i=ah_type">ah_type</a> =
<a name="L545" href="source/net/ipv4/ah4.c#L545">545</a> {
<a name="L546" href="source/net/ipv4/ah4.c#L546">546</a>         .description    = <i>"AH4"</i>,
<a name="L547" href="source/net/ipv4/ah4.c#L547">547</a>         .owner          = <a href="ident?i=THIS_MODULE">THIS_MODULE</a>,
<a name="L548" href="source/net/ipv4/ah4.c#L548">548</a>         .<a href="ident?i=proto">proto</a>          = <a href="ident?i=IPPROTO_AH">IPPROTO_AH</a>,
<a name="L549" href="source/net/ipv4/ah4.c#L549">549</a>         .<a href="ident?i=flags">flags</a>          = <a href="ident?i=XFRM_TYPE_REPLAY_PROT">XFRM_TYPE_REPLAY_PROT</a>,
<a name="L550" href="source/net/ipv4/ah4.c#L550">550</a>         .<a href="ident?i=init_state">init_state</a>     = <a href="ident?i=ah_init_state">ah_init_state</a>,
<a name="L551" href="source/net/ipv4/ah4.c#L551">551</a>         .destructor     = <a href="ident?i=ah_destroy">ah_destroy</a>,
<a name="L552" href="source/net/ipv4/ah4.c#L552">552</a>         .<a href="ident?i=input">input</a>          = <a href="ident?i=ah_input">ah_input</a>,
<a name="L553" href="source/net/ipv4/ah4.c#L553">553</a>         .<a href="ident?i=output">output</a>         = <a href="ident?i=ah_output">ah_output</a>
<a name="L554" href="source/net/ipv4/ah4.c#L554">554</a> };
<a name="L555" href="source/net/ipv4/ah4.c#L555">555</a> 
<a name="L556" href="source/net/ipv4/ah4.c#L556">556</a> static struct <a href="ident?i=xfrm4_protocol">xfrm4_protocol</a> <a href="ident?i=ah4_protocol">ah4_protocol</a> = {
<a name="L557" href="source/net/ipv4/ah4.c#L557">557</a>         .<a href="ident?i=handler">handler</a>        =       <a href="ident?i=xfrm4_rcv">xfrm4_rcv</a>,
<a name="L558" href="source/net/ipv4/ah4.c#L558">558</a>         .<a href="ident?i=input_handler">input_handler</a>  =       <a href="ident?i=xfrm_input">xfrm_input</a>,
<a name="L559" href="source/net/ipv4/ah4.c#L559">559</a>         .cb_handler     =       <a href="ident?i=ah4_rcv_cb">ah4_rcv_cb</a>,
<a name="L560" href="source/net/ipv4/ah4.c#L560">560</a>         .<a href="ident?i=err_handler">err_handler</a>    =       <a href="ident?i=ah4_err">ah4_err</a>,
<a name="L561" href="source/net/ipv4/ah4.c#L561">561</a>         .<a href="ident?i=priority">priority</a>       =       0,
<a name="L562" href="source/net/ipv4/ah4.c#L562">562</a> };
<a name="L563" href="source/net/ipv4/ah4.c#L563">563</a> 
<a name="L564" href="source/net/ipv4/ah4.c#L564">564</a> static int <a href="ident?i=__init">__init</a> <a href="ident?i=ah4_init">ah4_init</a>(void)
<a name="L565" href="source/net/ipv4/ah4.c#L565">565</a> {
<a name="L566" href="source/net/ipv4/ah4.c#L566">566</a>         if (<a href="ident?i=xfrm_register_type">xfrm_register_type</a>(&amp;<a href="ident?i=ah_type">ah_type</a>, <a href="ident?i=AF_INET">AF_INET</a>) &lt; 0) {
<a name="L567" href="source/net/ipv4/ah4.c#L567">567</a>                 <a href="ident?i=pr_info">pr_info</a>(<i>"%s: can't add xfrm type\n"</i>, <a href="ident?i=__func__">__func__</a>);
<a name="L568" href="source/net/ipv4/ah4.c#L568">568</a>                 return -<a href="ident?i=EAGAIN">EAGAIN</a>;
<a name="L569" href="source/net/ipv4/ah4.c#L569">569</a>         }
<a name="L570" href="source/net/ipv4/ah4.c#L570">570</a>         if (<a href="ident?i=xfrm4_protocol_register">xfrm4_protocol_register</a>(&amp;<a href="ident?i=ah4_protocol">ah4_protocol</a>, <a href="ident?i=IPPROTO_AH">IPPROTO_AH</a>) &lt; 0) {
<a name="L571" href="source/net/ipv4/ah4.c#L571">571</a>                 <a href="ident?i=pr_info">pr_info</a>(<i>"%s: can't add protocol\n"</i>, <a href="ident?i=__func__">__func__</a>);
<a name="L572" href="source/net/ipv4/ah4.c#L572">572</a>                 <a href="ident?i=xfrm_unregister_type">xfrm_unregister_type</a>(&amp;<a href="ident?i=ah_type">ah_type</a>, <a href="ident?i=AF_INET">AF_INET</a>);
<a name="L573" href="source/net/ipv4/ah4.c#L573">573</a>                 return -<a href="ident?i=EAGAIN">EAGAIN</a>;
<a name="L574" href="source/net/ipv4/ah4.c#L574">574</a>         }
<a name="L575" href="source/net/ipv4/ah4.c#L575">575</a>         return 0;
<a name="L576" href="source/net/ipv4/ah4.c#L576">576</a> }
<a name="L577" href="source/net/ipv4/ah4.c#L577">577</a> 
<a name="L578" href="source/net/ipv4/ah4.c#L578">578</a> static void <a href="ident?i=__exit">__exit</a> <a href="ident?i=ah4_fini">ah4_fini</a>(void)
<a name="L579" href="source/net/ipv4/ah4.c#L579">579</a> {
<a name="L580" href="source/net/ipv4/ah4.c#L580">580</a>         if (<a href="ident?i=xfrm4_protocol_deregister">xfrm4_protocol_deregister</a>(&amp;<a href="ident?i=ah4_protocol">ah4_protocol</a>, <a href="ident?i=IPPROTO_AH">IPPROTO_AH</a>) &lt; 0)
<a name="L581" href="source/net/ipv4/ah4.c#L581">581</a>                 <a href="ident?i=pr_info">pr_info</a>(<i>"%s: can't remove protocol\n"</i>, <a href="ident?i=__func__">__func__</a>);
<a name="L582" href="source/net/ipv4/ah4.c#L582">582</a>         if (<a href="ident?i=xfrm_unregister_type">xfrm_unregister_type</a>(&amp;<a href="ident?i=ah_type">ah_type</a>, <a href="ident?i=AF_INET">AF_INET</a>) &lt; 0)
<a name="L583" href="source/net/ipv4/ah4.c#L583">583</a>                 <a href="ident?i=pr_info">pr_info</a>(<i>"%s: can't remove xfrm type\n"</i>, <a href="ident?i=__func__">__func__</a>);
<a name="L584" href="source/net/ipv4/ah4.c#L584">584</a> }
<a name="L585" href="source/net/ipv4/ah4.c#L585">585</a> 
<a name="L586" href="source/net/ipv4/ah4.c#L586">586</a> <a href="ident?i=module_init">module_init</a>(<a href="ident?i=ah4_init">ah4_init</a>);
<a name="L587" href="source/net/ipv4/ah4.c#L587">587</a> <a href="ident?i=module_exit">module_exit</a>(<a href="ident?i=ah4_fini">ah4_fini</a>);
<a name="L588" href="source/net/ipv4/ah4.c#L588">588</a> <a href="ident?i=MODULE_LICENSE">MODULE_LICENSE</a>(<i>"GPL"</i>);
<a name="L589" href="source/net/ipv4/ah4.c#L589">589</a> <a href="ident?i=MODULE_ALIAS_XFRM_TYPE">MODULE_ALIAS_XFRM_TYPE</a>(<a href="ident?i=AF_INET">AF_INET</a>, <a href="ident?i=XFRM_PROTO_AH">XFRM_PROTO_AH</a>);
<a name="L590" href="source/net/ipv4/ah4.c#L590">590</a> </pre></div><p>
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
