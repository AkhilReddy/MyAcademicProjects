<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title>Linux/net/ipv4/tcp_offload.c - Linux Cross Reference - Free Electrons</title>
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
		 &nbsp;&bull;&nbsp;<b><i>source navigation</i></b> &nbsp;&bull;&nbsp;<a href="diff/net/ipv4/tcp_offload.c">diff markup</a> &nbsp;&bull;&nbsp;<a href="ident">identifier search</a> &nbsp;&bull;&nbsp;<a href="search">freetext search</a> &nbsp;&bull;&nbsp;
		</p>
	</div>
</div>

<div id="topbar">
  
  <p>Version: &nbsp;<a href="source/net/ipv4/tcp_offload.c?v=2.0.40">2.0.40</a>&nbsp;<a href="source/net/ipv4/tcp_offload.c?v=2.2.26">2.2.26</a>&nbsp;<a href="source/net/ipv4/tcp_offload.c?v=2.4.37">2.4.37</a>&nbsp;<a href="source/net/ipv4/tcp_offload.c?v=3.5">3.5</a>&nbsp;<a href="source/net/ipv4/tcp_offload.c?v=3.6">3.6</a>&nbsp;<a href="source/net/ipv4/tcp_offload.c?v=3.7">3.7</a>&nbsp;<a href="source/net/ipv4/tcp_offload.c?v=3.8">3.8</a>&nbsp;<a href="source/net/ipv4/tcp_offload.c?v=3.9">3.9</a>&nbsp;<a href="source/net/ipv4/tcp_offload.c?v=3.10">3.10</a>&nbsp;<a href="source/net/ipv4/tcp_offload.c?v=3.11">3.11</a>&nbsp;<a href="source/net/ipv4/tcp_offload.c?v=3.12">3.12</a>&nbsp;<a href="source/net/ipv4/tcp_offload.c?v=3.13">3.13</a>&nbsp;<a href="source/net/ipv4/tcp_offload.c?v=3.14">3.14</a>&nbsp;<a href="source/net/ipv4/tcp_offload.c?v=3.15">3.15</a>&nbsp;<a href="source/net/ipv4/tcp_offload.c?v=3.16">3.16</a>&nbsp;<a href="source/net/ipv4/tcp_offload.c?v=3.17">3.17</a>&nbsp;<a href="source/net/ipv4/tcp_offload.c?v=3.18">3.18</a>&nbsp;<a href="source/net/ipv4/tcp_offload.c?v=3.19">3.19</a>&nbsp;<a href="source/net/ipv4/tcp_offload.c?v=4.0">4.0</a>&nbsp;<b><i>4.1</i></b></p>
  
</div>

<h1><a href="source/">Linux</a>/<a href="source/net/">net</a>/<a href="source/net/ipv4/">ipv4</a>/<a href="source/net/ipv4/tcp_offload.c">tcp_offload.c</a></h1>
<div id="lxrcode"><pre>  <a name="L1" href="source/net/ipv4/tcp_offload.c#L1">1</a> <b><i>/*</i></b>
  <a name="L2" href="source/net/ipv4/tcp_offload.c#L2">2</a> <b><i> *      IPV4 GSO/GRO offload support</i></b>
  <a name="L3" href="source/net/ipv4/tcp_offload.c#L3">3</a> <b><i> *      Linux INET implementation</i></b>
  <a name="L4" href="source/net/ipv4/tcp_offload.c#L4">4</a> <b><i> *</i></b>
  <a name="L5" href="source/net/ipv4/tcp_offload.c#L5">5</a> <b><i> *      This program is free software; you can redistribute it and/or</i></b>
  <a name="L6" href="source/net/ipv4/tcp_offload.c#L6">6</a> <b><i> *      modify it under the terms of the GNU General Public License</i></b>
  <a name="L7" href="source/net/ipv4/tcp_offload.c#L7">7</a> <b><i> *      as published by the Free Software Foundation; either version</i></b>
  <a name="L8" href="source/net/ipv4/tcp_offload.c#L8">8</a> <b><i> *      2 of the License, or (at your option) any later version.</i></b>
  <a name="L9" href="source/net/ipv4/tcp_offload.c#L9">9</a> <b><i> *</i></b>
 <a name="L10" href="source/net/ipv4/tcp_offload.c#L10">10</a> <b><i> *      TCPv4 GSO/GRO support</i></b>
 <a name="L11" href="source/net/ipv4/tcp_offload.c#L11">11</a> <b><i> */</i></b>
 <a name="L12" href="source/net/ipv4/tcp_offload.c#L12">12</a> 
 <a name="L13" href="source/net/ipv4/tcp_offload.c#L13">13</a> #include &lt;linux/skbuff.h&gt;
 <a name="L14" href="source/net/ipv4/tcp_offload.c#L14">14</a> #include &lt;net/tcp.h&gt;
 <a name="L15" href="source/net/ipv4/tcp_offload.c#L15">15</a> #include &lt;net/protocol.h&gt;
 <a name="L16" href="source/net/ipv4/tcp_offload.c#L16">16</a> 
 <a name="L17" href="source/net/ipv4/tcp_offload.c#L17">17</a> static void <a href="ident?i=tcp_gso_tstamp">tcp_gso_tstamp</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, unsigned int ts_seq,
 <a name="L18" href="source/net/ipv4/tcp_offload.c#L18">18</a>                            unsigned int <a href="ident?i=seq">seq</a>, unsigned int mss)
 <a name="L19" href="source/net/ipv4/tcp_offload.c#L19">19</a> {
 <a name="L20" href="source/net/ipv4/tcp_offload.c#L20">20</a>         while (<a href="ident?i=skb">skb</a>) {
 <a name="L21" href="source/net/ipv4/tcp_offload.c#L21">21</a>                 if (<a href="ident?i=before">before</a>(ts_seq, <a href="ident?i=seq">seq</a> + mss)) {
 <a name="L22" href="source/net/ipv4/tcp_offload.c#L22">22</a>                         <a href="ident?i=skb_shinfo">skb_shinfo</a>(<a href="ident?i=skb">skb</a>)-&gt;tx_flags |= SKBTX_SW_TSTAMP;
 <a name="L23" href="source/net/ipv4/tcp_offload.c#L23">23</a>                         <a href="ident?i=skb_shinfo">skb_shinfo</a>(<a href="ident?i=skb">skb</a>)-&gt;tskey = ts_seq;
 <a name="L24" href="source/net/ipv4/tcp_offload.c#L24">24</a>                         return;
 <a name="L25" href="source/net/ipv4/tcp_offload.c#L25">25</a>                 }
 <a name="L26" href="source/net/ipv4/tcp_offload.c#L26">26</a> 
 <a name="L27" href="source/net/ipv4/tcp_offload.c#L27">27</a>                 <a href="ident?i=skb">skb</a> = <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=next">next</a>;
 <a name="L28" href="source/net/ipv4/tcp_offload.c#L28">28</a>                 <a href="ident?i=seq">seq</a> += mss;
 <a name="L29" href="source/net/ipv4/tcp_offload.c#L29">29</a>         }
 <a name="L30" href="source/net/ipv4/tcp_offload.c#L30">30</a> }
 <a name="L31" href="source/net/ipv4/tcp_offload.c#L31">31</a> 
 <a name="L32" href="source/net/ipv4/tcp_offload.c#L32">32</a> static struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=tcp4_gso_segment">tcp4_gso_segment</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
 <a name="L33" href="source/net/ipv4/tcp_offload.c#L33">33</a>                                         <a href="ident?i=netdev_features_t">netdev_features_t</a> <a href="ident?i=features">features</a>)
 <a name="L34" href="source/net/ipv4/tcp_offload.c#L34">34</a> {
 <a name="L35" href="source/net/ipv4/tcp_offload.c#L35">35</a>         if (!<a href="ident?i=pskb_may_pull">pskb_may_pull</a>(<a href="ident?i=skb">skb</a>, sizeof(struct <a href="ident?i=tcphdr">tcphdr</a>)))
 <a name="L36" href="source/net/ipv4/tcp_offload.c#L36">36</a>                 return <a href="ident?i=ERR_PTR">ERR_PTR</a>(-<a href="ident?i=EINVAL">EINVAL</a>);
 <a name="L37" href="source/net/ipv4/tcp_offload.c#L37">37</a> 
 <a name="L38" href="source/net/ipv4/tcp_offload.c#L38">38</a>         if (<a href="ident?i=unlikely">unlikely</a>(<a href="ident?i=skb">skb</a>-&gt;ip_summed != <a href="ident?i=CHECKSUM_PARTIAL">CHECKSUM_PARTIAL</a>)) {
 <a name="L39" href="source/net/ipv4/tcp_offload.c#L39">39</a>                 const struct <a href="ident?i=iphdr">iphdr</a> *iph = <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>);
 <a name="L40" href="source/net/ipv4/tcp_offload.c#L40">40</a>                 struct <a href="ident?i=tcphdr">tcphdr</a> *<a href="ident?i=th">th</a> = <a href="ident?i=tcp_hdr">tcp_hdr</a>(<a href="ident?i=skb">skb</a>);
 <a name="L41" href="source/net/ipv4/tcp_offload.c#L41">41</a> 
 <a name="L42" href="source/net/ipv4/tcp_offload.c#L42">42</a>                 <b><i>/* Set up checksum pseudo header, usually expect stack to</i></b>
 <a name="L43" href="source/net/ipv4/tcp_offload.c#L43">43</a> <b><i>                 * have done this already.</i></b>
 <a name="L44" href="source/net/ipv4/tcp_offload.c#L44">44</a> <b><i>                 */</i></b>
 <a name="L45" href="source/net/ipv4/tcp_offload.c#L45">45</a> 
 <a name="L46" href="source/net/ipv4/tcp_offload.c#L46">46</a>                 <a href="ident?i=th">th</a>-&gt;<a href="ident?i=check">check</a> = 0;
 <a name="L47" href="source/net/ipv4/tcp_offload.c#L47">47</a>                 <a href="ident?i=skb">skb</a>-&gt;ip_summed = <a href="ident?i=CHECKSUM_PARTIAL">CHECKSUM_PARTIAL</a>;
 <a name="L48" href="source/net/ipv4/tcp_offload.c#L48">48</a>                 <a href="ident?i=__tcp_v4_send_check">__tcp_v4_send_check</a>(<a href="ident?i=skb">skb</a>, iph-&gt;<a href="ident?i=saddr">saddr</a>, iph-&gt;<a href="ident?i=daddr">daddr</a>);
 <a name="L49" href="source/net/ipv4/tcp_offload.c#L49">49</a>         }
 <a name="L50" href="source/net/ipv4/tcp_offload.c#L50">50</a> 
 <a name="L51" href="source/net/ipv4/tcp_offload.c#L51">51</a>         return <a href="ident?i=tcp_gso_segment">tcp_gso_segment</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=features">features</a>);
 <a name="L52" href="source/net/ipv4/tcp_offload.c#L52">52</a> }
 <a name="L53" href="source/net/ipv4/tcp_offload.c#L53">53</a> 
 <a name="L54" href="source/net/ipv4/tcp_offload.c#L54">54</a> struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=tcp_gso_segment">tcp_gso_segment</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
 <a name="L55" href="source/net/ipv4/tcp_offload.c#L55">55</a>                                 <a href="ident?i=netdev_features_t">netdev_features_t</a> <a href="ident?i=features">features</a>)
 <a name="L56" href="source/net/ipv4/tcp_offload.c#L56">56</a> {
 <a name="L57" href="source/net/ipv4/tcp_offload.c#L57">57</a>         struct <a href="ident?i=sk_buff">sk_buff</a> *segs = <a href="ident?i=ERR_PTR">ERR_PTR</a>(-<a href="ident?i=EINVAL">EINVAL</a>);
 <a name="L58" href="source/net/ipv4/tcp_offload.c#L58">58</a>         unsigned int sum_truesize = 0;
 <a name="L59" href="source/net/ipv4/tcp_offload.c#L59">59</a>         struct <a href="ident?i=tcphdr">tcphdr</a> *<a href="ident?i=th">th</a>;
 <a name="L60" href="source/net/ipv4/tcp_offload.c#L60">60</a>         unsigned int thlen;
 <a name="L61" href="source/net/ipv4/tcp_offload.c#L61">61</a>         unsigned int <a href="ident?i=seq">seq</a>;
 <a name="L62" href="source/net/ipv4/tcp_offload.c#L62">62</a>         <a href="ident?i=__be32">__be32</a> <a href="ident?i=delta">delta</a>;
 <a name="L63" href="source/net/ipv4/tcp_offload.c#L63">63</a>         unsigned int oldlen;
 <a name="L64" href="source/net/ipv4/tcp_offload.c#L64">64</a>         unsigned int mss;
 <a name="L65" href="source/net/ipv4/tcp_offload.c#L65">65</a>         struct <a href="ident?i=sk_buff">sk_buff</a> *gso_skb = <a href="ident?i=skb">skb</a>;
 <a name="L66" href="source/net/ipv4/tcp_offload.c#L66">66</a>         <a href="ident?i=__sum16">__sum16</a> newcheck;
 <a name="L67" href="source/net/ipv4/tcp_offload.c#L67">67</a>         <a href="ident?i=bool">bool</a> ooo_okay, copy_destructor;
 <a name="L68" href="source/net/ipv4/tcp_offload.c#L68">68</a> 
 <a name="L69" href="source/net/ipv4/tcp_offload.c#L69">69</a>         <a href="ident?i=th">th</a> = <a href="ident?i=tcp_hdr">tcp_hdr</a>(<a href="ident?i=skb">skb</a>);
 <a name="L70" href="source/net/ipv4/tcp_offload.c#L70">70</a>         thlen = <a href="ident?i=th">th</a>-&gt;doff * 4;
 <a name="L71" href="source/net/ipv4/tcp_offload.c#L71">71</a>         if (thlen &lt; sizeof(*<a href="ident?i=th">th</a>))
 <a name="L72" href="source/net/ipv4/tcp_offload.c#L72">72</a>                 goto <a href="ident?i=out">out</a>;
 <a name="L73" href="source/net/ipv4/tcp_offload.c#L73">73</a> 
 <a name="L74" href="source/net/ipv4/tcp_offload.c#L74">74</a>         if (!<a href="ident?i=pskb_may_pull">pskb_may_pull</a>(<a href="ident?i=skb">skb</a>, thlen))
 <a name="L75" href="source/net/ipv4/tcp_offload.c#L75">75</a>                 goto <a href="ident?i=out">out</a>;
 <a name="L76" href="source/net/ipv4/tcp_offload.c#L76">76</a> 
 <a name="L77" href="source/net/ipv4/tcp_offload.c#L77">77</a>         oldlen = (<a href="ident?i=u16">u16</a>)~skb-&gt;<a href="ident?i=len">len</a>;
 <a name="L78" href="source/net/ipv4/tcp_offload.c#L78">78</a>         <a href="ident?i=__skb_pull">__skb_pull</a>(<a href="ident?i=skb">skb</a>, thlen);
 <a name="L79" href="source/net/ipv4/tcp_offload.c#L79">79</a> 
 <a name="L80" href="source/net/ipv4/tcp_offload.c#L80">80</a>         mss = <a href="ident?i=tcp_skb_mss">tcp_skb_mss</a>(<a href="ident?i=skb">skb</a>);
 <a name="L81" href="source/net/ipv4/tcp_offload.c#L81">81</a>         if (<a href="ident?i=unlikely">unlikely</a>(<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a> &lt;= mss))
 <a name="L82" href="source/net/ipv4/tcp_offload.c#L82">82</a>                 goto <a href="ident?i=out">out</a>;
 <a name="L83" href="source/net/ipv4/tcp_offload.c#L83">83</a> 
 <a name="L84" href="source/net/ipv4/tcp_offload.c#L84">84</a>         if (<a href="ident?i=skb_gso_ok">skb_gso_ok</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=features">features</a> | <a href="ident?i=NETIF_F_GSO_ROBUST">NETIF_F_GSO_ROBUST</a>)) {
 <a name="L85" href="source/net/ipv4/tcp_offload.c#L85">85</a>                 <b><i>/* Packet is from an untrusted source, reset gso_segs. */</i></b>
 <a name="L86" href="source/net/ipv4/tcp_offload.c#L86">86</a>                 int <a href="ident?i=type">type</a> = <a href="ident?i=skb_shinfo">skb_shinfo</a>(<a href="ident?i=skb">skb</a>)-&gt;gso_type;
 <a name="L87" href="source/net/ipv4/tcp_offload.c#L87">87</a> 
 <a name="L88" href="source/net/ipv4/tcp_offload.c#L88">88</a>                 if (<a href="ident?i=unlikely">unlikely</a>(<a href="ident?i=type">type</a> &amp;
 <a name="L89" href="source/net/ipv4/tcp_offload.c#L89">89</a>                              ~(SKB_GSO_TCPV4 |
 <a name="L90" href="source/net/ipv4/tcp_offload.c#L90">90</a>                                SKB_GSO_DODGY |
 <a name="L91" href="source/net/ipv4/tcp_offload.c#L91">91</a>                                SKB_GSO_TCP_ECN |
 <a name="L92" href="source/net/ipv4/tcp_offload.c#L92">92</a>                                SKB_GSO_TCPV6 |
 <a name="L93" href="source/net/ipv4/tcp_offload.c#L93">93</a>                                SKB_GSO_GRE |
 <a name="L94" href="source/net/ipv4/tcp_offload.c#L94">94</a>                                SKB_GSO_GRE_CSUM |
 <a name="L95" href="source/net/ipv4/tcp_offload.c#L95">95</a>                                SKB_GSO_IPIP |
 <a name="L96" href="source/net/ipv4/tcp_offload.c#L96">96</a>                                SKB_GSO_SIT |
 <a name="L97" href="source/net/ipv4/tcp_offload.c#L97">97</a>                                SKB_GSO_UDP_TUNNEL |
 <a name="L98" href="source/net/ipv4/tcp_offload.c#L98">98</a>                                SKB_GSO_UDP_TUNNEL_CSUM |
 <a name="L99" href="source/net/ipv4/tcp_offload.c#L99">99</a>                                SKB_GSO_TUNNEL_REMCSUM |
<a name="L100" href="source/net/ipv4/tcp_offload.c#L100">100</a>                                0) ||
<a name="L101" href="source/net/ipv4/tcp_offload.c#L101">101</a>                              !(<a href="ident?i=type">type</a> &amp; (SKB_GSO_TCPV4 | SKB_GSO_TCPV6))))
<a name="L102" href="source/net/ipv4/tcp_offload.c#L102">102</a>                         goto <a href="ident?i=out">out</a>;
<a name="L103" href="source/net/ipv4/tcp_offload.c#L103">103</a> 
<a name="L104" href="source/net/ipv4/tcp_offload.c#L104">104</a>                 <a href="ident?i=skb_shinfo">skb_shinfo</a>(<a href="ident?i=skb">skb</a>)-&gt;gso_segs = <a href="ident?i=DIV_ROUND_UP">DIV_ROUND_UP</a>(<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a>, mss);
<a name="L105" href="source/net/ipv4/tcp_offload.c#L105">105</a> 
<a name="L106" href="source/net/ipv4/tcp_offload.c#L106">106</a>                 segs = <a href="ident?i=NULL">NULL</a>;
<a name="L107" href="source/net/ipv4/tcp_offload.c#L107">107</a>                 goto <a href="ident?i=out">out</a>;
<a name="L108" href="source/net/ipv4/tcp_offload.c#L108">108</a>         }
<a name="L109" href="source/net/ipv4/tcp_offload.c#L109">109</a> 
<a name="L110" href="source/net/ipv4/tcp_offload.c#L110">110</a>         copy_destructor = gso_skb-&gt;destructor == <a href="ident?i=tcp_wfree">tcp_wfree</a>;
<a name="L111" href="source/net/ipv4/tcp_offload.c#L111">111</a>         ooo_okay = gso_skb-&gt;ooo_okay;
<a name="L112" href="source/net/ipv4/tcp_offload.c#L112">112</a>         <b><i>/* All segments but the first should have ooo_okay cleared */</i></b>
<a name="L113" href="source/net/ipv4/tcp_offload.c#L113">113</a>         <a href="ident?i=skb">skb</a>-&gt;ooo_okay = 0;
<a name="L114" href="source/net/ipv4/tcp_offload.c#L114">114</a> 
<a name="L115" href="source/net/ipv4/tcp_offload.c#L115">115</a>         segs = <a href="ident?i=skb_segment">skb_segment</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=features">features</a>);
<a name="L116" href="source/net/ipv4/tcp_offload.c#L116">116</a>         if (<a href="ident?i=IS_ERR">IS_ERR</a>(segs))
<a name="L117" href="source/net/ipv4/tcp_offload.c#L117">117</a>                 goto <a href="ident?i=out">out</a>;
<a name="L118" href="source/net/ipv4/tcp_offload.c#L118">118</a> 
<a name="L119" href="source/net/ipv4/tcp_offload.c#L119">119</a>         <b><i>/* Only first segment might have ooo_okay set */</i></b>
<a name="L120" href="source/net/ipv4/tcp_offload.c#L120">120</a>         segs-&gt;ooo_okay = ooo_okay;
<a name="L121" href="source/net/ipv4/tcp_offload.c#L121">121</a> 
<a name="L122" href="source/net/ipv4/tcp_offload.c#L122">122</a>         <a href="ident?i=delta">delta</a> = <a href="ident?i=htonl">htonl</a>(oldlen + (thlen + mss));
<a name="L123" href="source/net/ipv4/tcp_offload.c#L123">123</a> 
<a name="L124" href="source/net/ipv4/tcp_offload.c#L124">124</a>         <a href="ident?i=skb">skb</a> = segs;
<a name="L125" href="source/net/ipv4/tcp_offload.c#L125">125</a>         <a href="ident?i=th">th</a> = <a href="ident?i=tcp_hdr">tcp_hdr</a>(<a href="ident?i=skb">skb</a>);
<a name="L126" href="source/net/ipv4/tcp_offload.c#L126">126</a>         <a href="ident?i=seq">seq</a> = <a href="ident?i=ntohl">ntohl</a>(<a href="ident?i=th">th</a>-&gt;<a href="ident?i=seq">seq</a>);
<a name="L127" href="source/net/ipv4/tcp_offload.c#L127">127</a> 
<a name="L128" href="source/net/ipv4/tcp_offload.c#L128">128</a>         if (<a href="ident?i=unlikely">unlikely</a>(<a href="ident?i=skb_shinfo">skb_shinfo</a>(gso_skb)-&gt;tx_flags &amp; SKBTX_SW_TSTAMP))
<a name="L129" href="source/net/ipv4/tcp_offload.c#L129">129</a>                 <a href="ident?i=tcp_gso_tstamp">tcp_gso_tstamp</a>(segs, <a href="ident?i=skb_shinfo">skb_shinfo</a>(gso_skb)-&gt;tskey, <a href="ident?i=seq">seq</a>, mss);
<a name="L130" href="source/net/ipv4/tcp_offload.c#L130">130</a> 
<a name="L131" href="source/net/ipv4/tcp_offload.c#L131">131</a>         newcheck = ~csum_fold((<a href="ident?i=__force">__force</a> <a href="ident?i=__wsum">__wsum</a>)((<a href="ident?i=__force">__force</a> <a href="ident?i=u32">u32</a>)<a href="ident?i=th">th</a>-&gt;<a href="ident?i=check">check</a> +
<a name="L132" href="source/net/ipv4/tcp_offload.c#L132">132</a>                                                (<a href="ident?i=__force">__force</a> <a href="ident?i=u32">u32</a>)<a href="ident?i=delta">delta</a>));
<a name="L133" href="source/net/ipv4/tcp_offload.c#L133">133</a> 
<a name="L134" href="source/net/ipv4/tcp_offload.c#L134">134</a>         do {
<a name="L135" href="source/net/ipv4/tcp_offload.c#L135">135</a>                 <a href="ident?i=th">th</a>-&gt;fin = <a href="ident?i=th">th</a>-&gt;psh = 0;
<a name="L136" href="source/net/ipv4/tcp_offload.c#L136">136</a>                 <a href="ident?i=th">th</a>-&gt;<a href="ident?i=check">check</a> = newcheck;
<a name="L137" href="source/net/ipv4/tcp_offload.c#L137">137</a> 
<a name="L138" href="source/net/ipv4/tcp_offload.c#L138">138</a>                 if (<a href="ident?i=skb">skb</a>-&gt;ip_summed != <a href="ident?i=CHECKSUM_PARTIAL">CHECKSUM_PARTIAL</a>)
<a name="L139" href="source/net/ipv4/tcp_offload.c#L139">139</a>                         <a href="ident?i=th">th</a>-&gt;<a href="ident?i=check">check</a> = <a href="ident?i=gso_make_checksum">gso_make_checksum</a>(<a href="ident?i=skb">skb</a>, ~th-&gt;<a href="ident?i=check">check</a>);
<a name="L140" href="source/net/ipv4/tcp_offload.c#L140">140</a> 
<a name="L141" href="source/net/ipv4/tcp_offload.c#L141">141</a>                 <a href="ident?i=seq">seq</a> += mss;
<a name="L142" href="source/net/ipv4/tcp_offload.c#L142">142</a>                 if (copy_destructor) {
<a name="L143" href="source/net/ipv4/tcp_offload.c#L143">143</a>                         <a href="ident?i=skb">skb</a>-&gt;destructor = gso_skb-&gt;destructor;
<a name="L144" href="source/net/ipv4/tcp_offload.c#L144">144</a>                         <a href="ident?i=skb">skb</a>-&gt;sk = gso_skb-&gt;sk;
<a name="L145" href="source/net/ipv4/tcp_offload.c#L145">145</a>                         sum_truesize += <a href="ident?i=skb">skb</a>-&gt;truesize;
<a name="L146" href="source/net/ipv4/tcp_offload.c#L146">146</a>                 }
<a name="L147" href="source/net/ipv4/tcp_offload.c#L147">147</a>                 <a href="ident?i=skb">skb</a> = <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=next">next</a>;
<a name="L148" href="source/net/ipv4/tcp_offload.c#L148">148</a>                 <a href="ident?i=th">th</a> = <a href="ident?i=tcp_hdr">tcp_hdr</a>(<a href="ident?i=skb">skb</a>);
<a name="L149" href="source/net/ipv4/tcp_offload.c#L149">149</a> 
<a name="L150" href="source/net/ipv4/tcp_offload.c#L150">150</a>                 <a href="ident?i=th">th</a>-&gt;<a href="ident?i=seq">seq</a> = <a href="ident?i=htonl">htonl</a>(<a href="ident?i=seq">seq</a>);
<a name="L151" href="source/net/ipv4/tcp_offload.c#L151">151</a>                 <a href="ident?i=th">th</a>-&gt;cwr = 0;
<a name="L152" href="source/net/ipv4/tcp_offload.c#L152">152</a>         } while (<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=next">next</a>);
<a name="L153" href="source/net/ipv4/tcp_offload.c#L153">153</a> 
<a name="L154" href="source/net/ipv4/tcp_offload.c#L154">154</a>         <b><i>/* Following permits TCP Small Queues to work well with GSO :</i></b>
<a name="L155" href="source/net/ipv4/tcp_offload.c#L155">155</a> <b><i>         * The callback to TCP stack will be called at the time last frag</i></b>
<a name="L156" href="source/net/ipv4/tcp_offload.c#L156">156</a> <b><i>         * is freed at TX completion, and not right now when gso_skb</i></b>
<a name="L157" href="source/net/ipv4/tcp_offload.c#L157">157</a> <b><i>         * is freed by GSO engine</i></b>
<a name="L158" href="source/net/ipv4/tcp_offload.c#L158">158</a> <b><i>         */</i></b>
<a name="L159" href="source/net/ipv4/tcp_offload.c#L159">159</a>         if (copy_destructor) {
<a name="L160" href="source/net/ipv4/tcp_offload.c#L160">160</a>                 <a href="ident?i=swap">swap</a>(gso_skb-&gt;sk, <a href="ident?i=skb">skb</a>-&gt;sk);
<a name="L161" href="source/net/ipv4/tcp_offload.c#L161">161</a>                 <a href="ident?i=swap">swap</a>(gso_skb-&gt;destructor, <a href="ident?i=skb">skb</a>-&gt;destructor);
<a name="L162" href="source/net/ipv4/tcp_offload.c#L162">162</a>                 sum_truesize += <a href="ident?i=skb">skb</a>-&gt;truesize;
<a name="L163" href="source/net/ipv4/tcp_offload.c#L163">163</a>                 <a href="ident?i=atomic_add">atomic_add</a>(sum_truesize - gso_skb-&gt;truesize,
<a name="L164" href="source/net/ipv4/tcp_offload.c#L164">164</a>                            &amp;<a href="ident?i=skb">skb</a>-&gt;sk-&gt;sk_wmem_alloc);
<a name="L165" href="source/net/ipv4/tcp_offload.c#L165">165</a>         }
<a name="L166" href="source/net/ipv4/tcp_offload.c#L166">166</a> 
<a name="L167" href="source/net/ipv4/tcp_offload.c#L167">167</a>         <a href="ident?i=delta">delta</a> = <a href="ident?i=htonl">htonl</a>(oldlen + (<a href="ident?i=skb_tail_pointer">skb_tail_pointer</a>(<a href="ident?i=skb">skb</a>) -
<a name="L168" href="source/net/ipv4/tcp_offload.c#L168">168</a>                                 <a href="ident?i=skb_transport_header">skb_transport_header</a>(<a href="ident?i=skb">skb</a>)) +
<a name="L169" href="source/net/ipv4/tcp_offload.c#L169">169</a>                       <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=data_len">data_len</a>);
<a name="L170" href="source/net/ipv4/tcp_offload.c#L170">170</a>         <a href="ident?i=th">th</a>-&gt;<a href="ident?i=check">check</a> = ~csum_fold((<a href="ident?i=__force">__force</a> <a href="ident?i=__wsum">__wsum</a>)((<a href="ident?i=__force">__force</a> <a href="ident?i=u32">u32</a>)<a href="ident?i=th">th</a>-&gt;<a href="ident?i=check">check</a> +
<a name="L171" href="source/net/ipv4/tcp_offload.c#L171">171</a>                                 (<a href="ident?i=__force">__force</a> <a href="ident?i=u32">u32</a>)<a href="ident?i=delta">delta</a>));
<a name="L172" href="source/net/ipv4/tcp_offload.c#L172">172</a>         if (<a href="ident?i=skb">skb</a>-&gt;ip_summed != <a href="ident?i=CHECKSUM_PARTIAL">CHECKSUM_PARTIAL</a>)
<a name="L173" href="source/net/ipv4/tcp_offload.c#L173">173</a>                 <a href="ident?i=th">th</a>-&gt;<a href="ident?i=check">check</a> = <a href="ident?i=gso_make_checksum">gso_make_checksum</a>(<a href="ident?i=skb">skb</a>, ~th-&gt;<a href="ident?i=check">check</a>);
<a name="L174" href="source/net/ipv4/tcp_offload.c#L174">174</a> <a href="ident?i=out">out</a>:
<a name="L175" href="source/net/ipv4/tcp_offload.c#L175">175</a>         return segs;
<a name="L176" href="source/net/ipv4/tcp_offload.c#L176">176</a> }
<a name="L177" href="source/net/ipv4/tcp_offload.c#L177">177</a> 
<a name="L178" href="source/net/ipv4/tcp_offload.c#L178">178</a> struct <a href="ident?i=sk_buff">sk_buff</a> **<a href="ident?i=tcp_gro_receive">tcp_gro_receive</a>(struct <a href="ident?i=sk_buff">sk_buff</a> **<a href="ident?i=head">head</a>, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L179" href="source/net/ipv4/tcp_offload.c#L179">179</a> {
<a name="L180" href="source/net/ipv4/tcp_offload.c#L180">180</a>         struct <a href="ident?i=sk_buff">sk_buff</a> **pp = <a href="ident?i=NULL">NULL</a>;
<a name="L181" href="source/net/ipv4/tcp_offload.c#L181">181</a>         struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=p">p</a>;
<a name="L182" href="source/net/ipv4/tcp_offload.c#L182">182</a>         struct <a href="ident?i=tcphdr">tcphdr</a> *<a href="ident?i=th">th</a>;
<a name="L183" href="source/net/ipv4/tcp_offload.c#L183">183</a>         struct <a href="ident?i=tcphdr">tcphdr</a> *th2;
<a name="L184" href="source/net/ipv4/tcp_offload.c#L184">184</a>         unsigned int <a href="ident?i=len">len</a>;
<a name="L185" href="source/net/ipv4/tcp_offload.c#L185">185</a>         unsigned int thlen;
<a name="L186" href="source/net/ipv4/tcp_offload.c#L186">186</a>         <a href="ident?i=__be32">__be32</a> <a href="ident?i=flags">flags</a>;
<a name="L187" href="source/net/ipv4/tcp_offload.c#L187">187</a>         unsigned int mss = 1;
<a name="L188" href="source/net/ipv4/tcp_offload.c#L188">188</a>         unsigned int hlen;
<a name="L189" href="source/net/ipv4/tcp_offload.c#L189">189</a>         unsigned int <a href="ident?i=off">off</a>;
<a name="L190" href="source/net/ipv4/tcp_offload.c#L190">190</a>         int <a href="ident?i=flush">flush</a> = 1;
<a name="L191" href="source/net/ipv4/tcp_offload.c#L191">191</a>         int <a href="ident?i=i">i</a>;
<a name="L192" href="source/net/ipv4/tcp_offload.c#L192">192</a> 
<a name="L193" href="source/net/ipv4/tcp_offload.c#L193">193</a>         <a href="ident?i=off">off</a> = <a href="ident?i=skb_gro_offset">skb_gro_offset</a>(<a href="ident?i=skb">skb</a>);
<a name="L194" href="source/net/ipv4/tcp_offload.c#L194">194</a>         hlen = <a href="ident?i=off">off</a> + sizeof(*<a href="ident?i=th">th</a>);
<a name="L195" href="source/net/ipv4/tcp_offload.c#L195">195</a>         <a href="ident?i=th">th</a> = <a href="ident?i=skb_gro_header_fast">skb_gro_header_fast</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=off">off</a>);
<a name="L196" href="source/net/ipv4/tcp_offload.c#L196">196</a>         if (<a href="ident?i=skb_gro_header_hard">skb_gro_header_hard</a>(<a href="ident?i=skb">skb</a>, hlen)) {
<a name="L197" href="source/net/ipv4/tcp_offload.c#L197">197</a>                 <a href="ident?i=th">th</a> = <a href="ident?i=skb_gro_header_slow">skb_gro_header_slow</a>(<a href="ident?i=skb">skb</a>, hlen, <a href="ident?i=off">off</a>);
<a name="L198" href="source/net/ipv4/tcp_offload.c#L198">198</a>                 if (<a href="ident?i=unlikely">unlikely</a>(!<a href="ident?i=th">th</a>))
<a name="L199" href="source/net/ipv4/tcp_offload.c#L199">199</a>                         goto <a href="ident?i=out">out</a>;
<a name="L200" href="source/net/ipv4/tcp_offload.c#L200">200</a>         }
<a name="L201" href="source/net/ipv4/tcp_offload.c#L201">201</a> 
<a name="L202" href="source/net/ipv4/tcp_offload.c#L202">202</a>         thlen = <a href="ident?i=th">th</a>-&gt;doff * 4;
<a name="L203" href="source/net/ipv4/tcp_offload.c#L203">203</a>         if (thlen &lt; sizeof(*<a href="ident?i=th">th</a>))
<a name="L204" href="source/net/ipv4/tcp_offload.c#L204">204</a>                 goto <a href="ident?i=out">out</a>;
<a name="L205" href="source/net/ipv4/tcp_offload.c#L205">205</a> 
<a name="L206" href="source/net/ipv4/tcp_offload.c#L206">206</a>         hlen = <a href="ident?i=off">off</a> + thlen;
<a name="L207" href="source/net/ipv4/tcp_offload.c#L207">207</a>         if (<a href="ident?i=skb_gro_header_hard">skb_gro_header_hard</a>(<a href="ident?i=skb">skb</a>, hlen)) {
<a name="L208" href="source/net/ipv4/tcp_offload.c#L208">208</a>                 <a href="ident?i=th">th</a> = <a href="ident?i=skb_gro_header_slow">skb_gro_header_slow</a>(<a href="ident?i=skb">skb</a>, hlen, <a href="ident?i=off">off</a>);
<a name="L209" href="source/net/ipv4/tcp_offload.c#L209">209</a>                 if (<a href="ident?i=unlikely">unlikely</a>(!<a href="ident?i=th">th</a>))
<a name="L210" href="source/net/ipv4/tcp_offload.c#L210">210</a>                         goto <a href="ident?i=out">out</a>;
<a name="L211" href="source/net/ipv4/tcp_offload.c#L211">211</a>         }
<a name="L212" href="source/net/ipv4/tcp_offload.c#L212">212</a> 
<a name="L213" href="source/net/ipv4/tcp_offload.c#L213">213</a>         <a href="ident?i=skb_gro_pull">skb_gro_pull</a>(<a href="ident?i=skb">skb</a>, thlen);
<a name="L214" href="source/net/ipv4/tcp_offload.c#L214">214</a> 
<a name="L215" href="source/net/ipv4/tcp_offload.c#L215">215</a>         <a href="ident?i=len">len</a> = <a href="ident?i=skb_gro_len">skb_gro_len</a>(<a href="ident?i=skb">skb</a>);
<a name="L216" href="source/net/ipv4/tcp_offload.c#L216">216</a>         <a href="ident?i=flags">flags</a> = <a href="ident?i=tcp_flag_word">tcp_flag_word</a>(<a href="ident?i=th">th</a>);
<a name="L217" href="source/net/ipv4/tcp_offload.c#L217">217</a> 
<a name="L218" href="source/net/ipv4/tcp_offload.c#L218">218</a>         for (; (<a href="ident?i=p">p</a> = *<a href="ident?i=head">head</a>); <a href="ident?i=head">head</a> = &amp;<a href="ident?i=p">p</a>-&gt;<a href="ident?i=next">next</a>) {
<a name="L219" href="source/net/ipv4/tcp_offload.c#L219">219</a>                 if (!<a href="ident?i=NAPI_GRO_CB">NAPI_GRO_CB</a>(<a href="ident?i=p">p</a>)-&gt;same_flow)
<a name="L220" href="source/net/ipv4/tcp_offload.c#L220">220</a>                         continue;
<a name="L221" href="source/net/ipv4/tcp_offload.c#L221">221</a> 
<a name="L222" href="source/net/ipv4/tcp_offload.c#L222">222</a>                 th2 = <a href="ident?i=tcp_hdr">tcp_hdr</a>(<a href="ident?i=p">p</a>);
<a name="L223" href="source/net/ipv4/tcp_offload.c#L223">223</a> 
<a name="L224" href="source/net/ipv4/tcp_offload.c#L224">224</a>                 if (*(<a href="ident?i=u32">u32</a> *)&amp;<a href="ident?i=th">th</a>-&gt;source ^ *(<a href="ident?i=u32">u32</a> *)&amp;th2-&gt;source) {
<a name="L225" href="source/net/ipv4/tcp_offload.c#L225">225</a>                         <a href="ident?i=NAPI_GRO_CB">NAPI_GRO_CB</a>(<a href="ident?i=p">p</a>)-&gt;same_flow = 0;
<a name="L226" href="source/net/ipv4/tcp_offload.c#L226">226</a>                         continue;
<a name="L227" href="source/net/ipv4/tcp_offload.c#L227">227</a>                 }
<a name="L228" href="source/net/ipv4/tcp_offload.c#L228">228</a> 
<a name="L229" href="source/net/ipv4/tcp_offload.c#L229">229</a>                 goto <a href="ident?i=found">found</a>;
<a name="L230" href="source/net/ipv4/tcp_offload.c#L230">230</a>         }
<a name="L231" href="source/net/ipv4/tcp_offload.c#L231">231</a> 
<a name="L232" href="source/net/ipv4/tcp_offload.c#L232">232</a>         goto out_check_final;
<a name="L233" href="source/net/ipv4/tcp_offload.c#L233">233</a> 
<a name="L234" href="source/net/ipv4/tcp_offload.c#L234">234</a> <a href="ident?i=found">found</a>:
<a name="L235" href="source/net/ipv4/tcp_offload.c#L235">235</a>         <b><i>/* Include the IP ID check below from the inner most IP hdr */</i></b>
<a name="L236" href="source/net/ipv4/tcp_offload.c#L236">236</a>         <a href="ident?i=flush">flush</a> = <a href="ident?i=NAPI_GRO_CB">NAPI_GRO_CB</a>(<a href="ident?i=p">p</a>)-&gt;<a href="ident?i=flush">flush</a> | <a href="ident?i=NAPI_GRO_CB">NAPI_GRO_CB</a>(<a href="ident?i=p">p</a>)-&gt;flush_id;
<a name="L237" href="source/net/ipv4/tcp_offload.c#L237">237</a>         <a href="ident?i=flush">flush</a> |= (<a href="ident?i=__force">__force</a> int)(<a href="ident?i=flags">flags</a> &amp; TCP_FLAG_CWR);
<a name="L238" href="source/net/ipv4/tcp_offload.c#L238">238</a>         <a href="ident?i=flush">flush</a> |= (<a href="ident?i=__force">__force</a> int)((<a href="ident?i=flags">flags</a> ^ <a href="ident?i=tcp_flag_word">tcp_flag_word</a>(th2)) &amp;
<a name="L239" href="source/net/ipv4/tcp_offload.c#L239">239</a>                   ~(TCP_FLAG_CWR | TCP_FLAG_FIN | TCP_FLAG_PSH));
<a name="L240" href="source/net/ipv4/tcp_offload.c#L240">240</a>         <a href="ident?i=flush">flush</a> |= (<a href="ident?i=__force">__force</a> int)(<a href="ident?i=th">th</a>-&gt;ack_seq ^ th2-&gt;ack_seq);
<a name="L241" href="source/net/ipv4/tcp_offload.c#L241">241</a>         for (<a href="ident?i=i">i</a> = sizeof(*<a href="ident?i=th">th</a>); <a href="ident?i=i">i</a> &lt; thlen; <a href="ident?i=i">i</a> += 4)
<a name="L242" href="source/net/ipv4/tcp_offload.c#L242">242</a>                 <a href="ident?i=flush">flush</a> |= *(<a href="ident?i=u32">u32</a> *)((<a href="ident?i=u8">u8</a> *)<a href="ident?i=th">th</a> + <a href="ident?i=i">i</a>) ^
<a name="L243" href="source/net/ipv4/tcp_offload.c#L243">243</a>                          *(<a href="ident?i=u32">u32</a> *)((<a href="ident?i=u8">u8</a> *)th2 + <a href="ident?i=i">i</a>);
<a name="L244" href="source/net/ipv4/tcp_offload.c#L244">244</a> 
<a name="L245" href="source/net/ipv4/tcp_offload.c#L245">245</a>         mss = <a href="ident?i=tcp_skb_mss">tcp_skb_mss</a>(<a href="ident?i=p">p</a>);
<a name="L246" href="source/net/ipv4/tcp_offload.c#L246">246</a> 
<a name="L247" href="source/net/ipv4/tcp_offload.c#L247">247</a>         <a href="ident?i=flush">flush</a> |= (<a href="ident?i=len">len</a> - 1) &gt;= mss;
<a name="L248" href="source/net/ipv4/tcp_offload.c#L248">248</a>         <a href="ident?i=flush">flush</a> |= (<a href="ident?i=ntohl">ntohl</a>(th2-&gt;<a href="ident?i=seq">seq</a>) + <a href="ident?i=skb_gro_len">skb_gro_len</a>(<a href="ident?i=p">p</a>)) ^ <a href="ident?i=ntohl">ntohl</a>(<a href="ident?i=th">th</a>-&gt;<a href="ident?i=seq">seq</a>);
<a name="L249" href="source/net/ipv4/tcp_offload.c#L249">249</a> 
<a name="L250" href="source/net/ipv4/tcp_offload.c#L250">250</a>         if (<a href="ident?i=flush">flush</a> || <a href="ident?i=skb_gro_receive">skb_gro_receive</a>(<a href="ident?i=head">head</a>, <a href="ident?i=skb">skb</a>)) {
<a name="L251" href="source/net/ipv4/tcp_offload.c#L251">251</a>                 mss = 1;
<a name="L252" href="source/net/ipv4/tcp_offload.c#L252">252</a>                 goto out_check_final;
<a name="L253" href="source/net/ipv4/tcp_offload.c#L253">253</a>         }
<a name="L254" href="source/net/ipv4/tcp_offload.c#L254">254</a> 
<a name="L255" href="source/net/ipv4/tcp_offload.c#L255">255</a>         <a href="ident?i=p">p</a> = *<a href="ident?i=head">head</a>;
<a name="L256" href="source/net/ipv4/tcp_offload.c#L256">256</a>         th2 = <a href="ident?i=tcp_hdr">tcp_hdr</a>(<a href="ident?i=p">p</a>);
<a name="L257" href="source/net/ipv4/tcp_offload.c#L257">257</a>         <a href="ident?i=tcp_flag_word">tcp_flag_word</a>(th2) |= <a href="ident?i=flags">flags</a> &amp; (TCP_FLAG_FIN | TCP_FLAG_PSH);
<a name="L258" href="source/net/ipv4/tcp_offload.c#L258">258</a> 
<a name="L259" href="source/net/ipv4/tcp_offload.c#L259">259</a> out_check_final:
<a name="L260" href="source/net/ipv4/tcp_offload.c#L260">260</a>         <a href="ident?i=flush">flush</a> = <a href="ident?i=len">len</a> &lt; mss;
<a name="L261" href="source/net/ipv4/tcp_offload.c#L261">261</a>         <a href="ident?i=flush">flush</a> |= (<a href="ident?i=__force">__force</a> int)(<a href="ident?i=flags">flags</a> &amp; (TCP_FLAG_URG | TCP_FLAG_PSH |
<a name="L262" href="source/net/ipv4/tcp_offload.c#L262">262</a>                                         TCP_FLAG_RST | TCP_FLAG_SYN |
<a name="L263" href="source/net/ipv4/tcp_offload.c#L263">263</a>                                         TCP_FLAG_FIN));
<a name="L264" href="source/net/ipv4/tcp_offload.c#L264">264</a> 
<a name="L265" href="source/net/ipv4/tcp_offload.c#L265">265</a>         if (<a href="ident?i=p">p</a> &amp;&amp; (!<a href="ident?i=NAPI_GRO_CB">NAPI_GRO_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;same_flow || <a href="ident?i=flush">flush</a>))
<a name="L266" href="source/net/ipv4/tcp_offload.c#L266">266</a>                 pp = <a href="ident?i=head">head</a>;
<a name="L267" href="source/net/ipv4/tcp_offload.c#L267">267</a> 
<a name="L268" href="source/net/ipv4/tcp_offload.c#L268">268</a> <a href="ident?i=out">out</a>:
<a name="L269" href="source/net/ipv4/tcp_offload.c#L269">269</a>         <a href="ident?i=NAPI_GRO_CB">NAPI_GRO_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=flush">flush</a> |= (<a href="ident?i=flush">flush</a> != 0);
<a name="L270" href="source/net/ipv4/tcp_offload.c#L270">270</a> 
<a name="L271" href="source/net/ipv4/tcp_offload.c#L271">271</a>         return pp;
<a name="L272" href="source/net/ipv4/tcp_offload.c#L272">272</a> }
<a name="L273" href="source/net/ipv4/tcp_offload.c#L273">273</a> 
<a name="L274" href="source/net/ipv4/tcp_offload.c#L274">274</a> int <a href="ident?i=tcp_gro_complete">tcp_gro_complete</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L275" href="source/net/ipv4/tcp_offload.c#L275">275</a> {
<a name="L276" href="source/net/ipv4/tcp_offload.c#L276">276</a>         struct <a href="ident?i=tcphdr">tcphdr</a> *<a href="ident?i=th">th</a> = <a href="ident?i=tcp_hdr">tcp_hdr</a>(<a href="ident?i=skb">skb</a>);
<a name="L277" href="source/net/ipv4/tcp_offload.c#L277">277</a> 
<a name="L278" href="source/net/ipv4/tcp_offload.c#L278">278</a>         <a href="ident?i=skb">skb</a>-&gt;csum_start = (unsigned char *)<a href="ident?i=th">th</a> - <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=head">head</a>;
<a name="L279" href="source/net/ipv4/tcp_offload.c#L279">279</a>         <a href="ident?i=skb">skb</a>-&gt;csum_offset = <a href="ident?i=offsetof">offsetof</a>(struct <a href="ident?i=tcphdr">tcphdr</a>, <a href="ident?i=check">check</a>);
<a name="L280" href="source/net/ipv4/tcp_offload.c#L280">280</a>         <a href="ident?i=skb">skb</a>-&gt;ip_summed = <a href="ident?i=CHECKSUM_PARTIAL">CHECKSUM_PARTIAL</a>;
<a name="L281" href="source/net/ipv4/tcp_offload.c#L281">281</a> 
<a name="L282" href="source/net/ipv4/tcp_offload.c#L282">282</a>         <a href="ident?i=skb_shinfo">skb_shinfo</a>(<a href="ident?i=skb">skb</a>)-&gt;gso_segs = <a href="ident?i=NAPI_GRO_CB">NAPI_GRO_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=count">count</a>;
<a name="L283" href="source/net/ipv4/tcp_offload.c#L283">283</a> 
<a name="L284" href="source/net/ipv4/tcp_offload.c#L284">284</a>         if (<a href="ident?i=th">th</a>-&gt;cwr)
<a name="L285" href="source/net/ipv4/tcp_offload.c#L285">285</a>                 <a href="ident?i=skb_shinfo">skb_shinfo</a>(<a href="ident?i=skb">skb</a>)-&gt;gso_type |= SKB_GSO_TCP_ECN;
<a name="L286" href="source/net/ipv4/tcp_offload.c#L286">286</a> 
<a name="L287" href="source/net/ipv4/tcp_offload.c#L287">287</a>         return 0;
<a name="L288" href="source/net/ipv4/tcp_offload.c#L288">288</a> }
<a name="L289" href="source/net/ipv4/tcp_offload.c#L289">289</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=tcp_gro_complete">tcp_gro_complete</a>);
<a name="L290" href="source/net/ipv4/tcp_offload.c#L290">290</a> 
<a name="L291" href="source/net/ipv4/tcp_offload.c#L291">291</a> static struct <a href="ident?i=sk_buff">sk_buff</a> **<a href="ident?i=tcp4_gro_receive">tcp4_gro_receive</a>(struct <a href="ident?i=sk_buff">sk_buff</a> **<a href="ident?i=head">head</a>, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L292" href="source/net/ipv4/tcp_offload.c#L292">292</a> {
<a name="L293" href="source/net/ipv4/tcp_offload.c#L293">293</a>         <b><i>/* Don't bother verifying checksum if we're going to flush anyway. */</i></b>
<a name="L294" href="source/net/ipv4/tcp_offload.c#L294">294</a>         if (!<a href="ident?i=NAPI_GRO_CB">NAPI_GRO_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=flush">flush</a> &amp;&amp;
<a name="L295" href="source/net/ipv4/tcp_offload.c#L295">295</a>             <a href="ident?i=skb_gro_checksum_validate">skb_gro_checksum_validate</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=IPPROTO_TCP">IPPROTO_TCP</a>,
<a name="L296" href="source/net/ipv4/tcp_offload.c#L296">296</a>                                       <a href="ident?i=inet_gro_compute_pseudo">inet_gro_compute_pseudo</a>)) {
<a name="L297" href="source/net/ipv4/tcp_offload.c#L297">297</a>                 <a href="ident?i=NAPI_GRO_CB">NAPI_GRO_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=flush">flush</a> = 1;
<a name="L298" href="source/net/ipv4/tcp_offload.c#L298">298</a>                 return <a href="ident?i=NULL">NULL</a>;
<a name="L299" href="source/net/ipv4/tcp_offload.c#L299">299</a>         }
<a name="L300" href="source/net/ipv4/tcp_offload.c#L300">300</a> 
<a name="L301" href="source/net/ipv4/tcp_offload.c#L301">301</a>         return <a href="ident?i=tcp_gro_receive">tcp_gro_receive</a>(<a href="ident?i=head">head</a>, <a href="ident?i=skb">skb</a>);
<a name="L302" href="source/net/ipv4/tcp_offload.c#L302">302</a> }
<a name="L303" href="source/net/ipv4/tcp_offload.c#L303">303</a> 
<a name="L304" href="source/net/ipv4/tcp_offload.c#L304">304</a> static int <a href="ident?i=tcp4_gro_complete">tcp4_gro_complete</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, int thoff)
<a name="L305" href="source/net/ipv4/tcp_offload.c#L305">305</a> {
<a name="L306" href="source/net/ipv4/tcp_offload.c#L306">306</a>         const struct <a href="ident?i=iphdr">iphdr</a> *iph = <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>);
<a name="L307" href="source/net/ipv4/tcp_offload.c#L307">307</a>         struct <a href="ident?i=tcphdr">tcphdr</a> *<a href="ident?i=th">th</a> = <a href="ident?i=tcp_hdr">tcp_hdr</a>(<a href="ident?i=skb">skb</a>);
<a name="L308" href="source/net/ipv4/tcp_offload.c#L308">308</a> 
<a name="L309" href="source/net/ipv4/tcp_offload.c#L309">309</a>         <a href="ident?i=th">th</a>-&gt;<a href="ident?i=check">check</a> = ~tcp_v4_check(<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a> - thoff, iph-&gt;<a href="ident?i=saddr">saddr</a>,
<a name="L310" href="source/net/ipv4/tcp_offload.c#L310">310</a>                                   iph-&gt;<a href="ident?i=daddr">daddr</a>, 0);
<a name="L311" href="source/net/ipv4/tcp_offload.c#L311">311</a>         <a href="ident?i=skb_shinfo">skb_shinfo</a>(<a href="ident?i=skb">skb</a>)-&gt;gso_type |= SKB_GSO_TCPV4;
<a name="L312" href="source/net/ipv4/tcp_offload.c#L312">312</a> 
<a name="L313" href="source/net/ipv4/tcp_offload.c#L313">313</a>         return <a href="ident?i=tcp_gro_complete">tcp_gro_complete</a>(<a href="ident?i=skb">skb</a>);
<a name="L314" href="source/net/ipv4/tcp_offload.c#L314">314</a> }
<a name="L315" href="source/net/ipv4/tcp_offload.c#L315">315</a> 
<a name="L316" href="source/net/ipv4/tcp_offload.c#L316">316</a> static const struct <a href="ident?i=net_offload">net_offload</a> <a href="ident?i=tcpv4_offload">tcpv4_offload</a> = {
<a name="L317" href="source/net/ipv4/tcp_offload.c#L317">317</a>         .<a href="ident?i=callbacks">callbacks</a> = {
<a name="L318" href="source/net/ipv4/tcp_offload.c#L318">318</a>                 .gso_segment    =       <a href="ident?i=tcp4_gso_segment">tcp4_gso_segment</a>,
<a name="L319" href="source/net/ipv4/tcp_offload.c#L319">319</a>                 .gro_receive    =       <a href="ident?i=tcp4_gro_receive">tcp4_gro_receive</a>,
<a name="L320" href="source/net/ipv4/tcp_offload.c#L320">320</a>                 .gro_complete   =       <a href="ident?i=tcp4_gro_complete">tcp4_gro_complete</a>,
<a name="L321" href="source/net/ipv4/tcp_offload.c#L321">321</a>         },
<a name="L322" href="source/net/ipv4/tcp_offload.c#L322">322</a> };
<a name="L323" href="source/net/ipv4/tcp_offload.c#L323">323</a> 
<a name="L324" href="source/net/ipv4/tcp_offload.c#L324">324</a> int <a href="ident?i=__init">__init</a> <a href="ident?i=tcpv4_offload_init">tcpv4_offload_init</a>(void)
<a name="L325" href="source/net/ipv4/tcp_offload.c#L325">325</a> {
<a name="L326" href="source/net/ipv4/tcp_offload.c#L326">326</a>         return <a href="ident?i=inet_add_offload">inet_add_offload</a>(&amp;<a href="ident?i=tcpv4_offload">tcpv4_offload</a>, <a href="ident?i=IPPROTO_TCP">IPPROTO_TCP</a>);
<a name="L327" href="source/net/ipv4/tcp_offload.c#L327">327</a> }
<a name="L328" href="source/net/ipv4/tcp_offload.c#L328">328</a> </pre></div><p>
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
