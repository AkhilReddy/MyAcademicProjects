<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title>Linux/net/ipv4/gre_demux.c - Linux Cross Reference - Free Electrons</title>
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
		 &nbsp;&bull;&nbsp;<b><i>source navigation</i></b> &nbsp;&bull;&nbsp;<a href="diff/net/ipv4/gre_demux.c">diff markup</a> &nbsp;&bull;&nbsp;<a href="ident">identifier search</a> &nbsp;&bull;&nbsp;<a href="search">freetext search</a> &nbsp;&bull;&nbsp;
		</p>
	</div>
</div>

<div id="topbar">
  
  <p>Version: &nbsp;<a href="source/net/ipv4/gre_demux.c?v=2.0.40">2.0.40</a>&nbsp;<a href="source/net/ipv4/gre_demux.c?v=2.2.26">2.2.26</a>&nbsp;<a href="source/net/ipv4/gre_demux.c?v=2.4.37">2.4.37</a>&nbsp;<a href="source/net/ipv4/gre_demux.c?v=3.5">3.5</a>&nbsp;<a href="source/net/ipv4/gre_demux.c?v=3.6">3.6</a>&nbsp;<a href="source/net/ipv4/gre_demux.c?v=3.7">3.7</a>&nbsp;<a href="source/net/ipv4/gre_demux.c?v=3.8">3.8</a>&nbsp;<a href="source/net/ipv4/gre_demux.c?v=3.9">3.9</a>&nbsp;<a href="source/net/ipv4/gre_demux.c?v=3.10">3.10</a>&nbsp;<a href="source/net/ipv4/gre_demux.c?v=3.11">3.11</a>&nbsp;<a href="source/net/ipv4/gre_demux.c?v=3.12">3.12</a>&nbsp;<a href="source/net/ipv4/gre_demux.c?v=3.13">3.13</a>&nbsp;<a href="source/net/ipv4/gre_demux.c?v=3.14">3.14</a>&nbsp;<a href="source/net/ipv4/gre_demux.c?v=3.15">3.15</a>&nbsp;<a href="source/net/ipv4/gre_demux.c?v=3.16">3.16</a>&nbsp;<a href="source/net/ipv4/gre_demux.c?v=3.17">3.17</a>&nbsp;<a href="source/net/ipv4/gre_demux.c?v=3.18">3.18</a>&nbsp;<a href="source/net/ipv4/gre_demux.c?v=3.19">3.19</a>&nbsp;<a href="source/net/ipv4/gre_demux.c?v=4.0">4.0</a>&nbsp;<b><i>4.1</i></b></p>
  
</div>

<h1><a href="source/">Linux</a>/<a href="source/net/">net</a>/<a href="source/net/ipv4/">ipv4</a>/<a href="source/net/ipv4/gre_demux.c">gre_demux.c</a></h1>
<div id="lxrcode"><pre>  <a name="L1" href="source/net/ipv4/gre_demux.c#L1">1</a> <b><i>/*</i></b>
  <a name="L2" href="source/net/ipv4/gre_demux.c#L2">2</a> <b><i> *      GRE over IPv4 demultiplexer driver</i></b>
  <a name="L3" href="source/net/ipv4/gre_demux.c#L3">3</a> <b><i> *</i></b>
  <a name="L4" href="source/net/ipv4/gre_demux.c#L4">4</a> <b><i> *      Authors: Dmitry Kozlov (xeb@mail.ru)</i></b>
  <a name="L5" href="source/net/ipv4/gre_demux.c#L5">5</a> <b><i> *</i></b>
  <a name="L6" href="source/net/ipv4/gre_demux.c#L6">6</a> <b><i> *      This program is free software; you can redistribute it and/or</i></b>
  <a name="L7" href="source/net/ipv4/gre_demux.c#L7">7</a> <b><i> *      modify it under the terms of the GNU General Public License</i></b>
  <a name="L8" href="source/net/ipv4/gre_demux.c#L8">8</a> <b><i> *      as published by the Free Software Foundation; either version</i></b>
  <a name="L9" href="source/net/ipv4/gre_demux.c#L9">9</a> <b><i> *      2 of the License, or (at your option) any later version.</i></b>
 <a name="L10" href="source/net/ipv4/gre_demux.c#L10">10</a> <b><i> *</i></b>
 <a name="L11" href="source/net/ipv4/gre_demux.c#L11">11</a> <b><i> */</i></b>
 <a name="L12" href="source/net/ipv4/gre_demux.c#L12">12</a> 
 <a name="L13" href="source/net/ipv4/gre_demux.c#L13">13</a> #define <a href="ident?i=pr_fmt">pr_fmt</a>(<a href="ident?i=fmt">fmt</a>) KBUILD_MODNAME <i>": "</i> <a href="ident?i=fmt">fmt</a>
 <a name="L14" href="source/net/ipv4/gre_demux.c#L14">14</a> 
 <a name="L15" href="source/net/ipv4/gre_demux.c#L15">15</a> #include &lt;linux/module.h&gt;
 <a name="L16" href="source/net/ipv4/gre_demux.c#L16">16</a> #include &lt;linux/if.h&gt;
 <a name="L17" href="source/net/ipv4/gre_demux.c#L17">17</a> #include &lt;linux/icmp.h&gt;
 <a name="L18" href="source/net/ipv4/gre_demux.c#L18">18</a> #include &lt;linux/kernel.h&gt;
 <a name="L19" href="source/net/ipv4/gre_demux.c#L19">19</a> #include &lt;linux/kmod.h&gt;
 <a name="L20" href="source/net/ipv4/gre_demux.c#L20">20</a> #include &lt;linux/skbuff.h&gt;
 <a name="L21" href="source/net/ipv4/gre_demux.c#L21">21</a> #include &lt;linux/in.h&gt;
 <a name="L22" href="source/net/ipv4/gre_demux.c#L22">22</a> #include &lt;linux/ip.h&gt;
 <a name="L23" href="source/net/ipv4/gre_demux.c#L23">23</a> #include &lt;linux/netdevice.h&gt;
 <a name="L24" href="source/net/ipv4/gre_demux.c#L24">24</a> #include &lt;linux/if_tunnel.h&gt;
 <a name="L25" href="source/net/ipv4/gre_demux.c#L25">25</a> #include &lt;linux/spinlock.h&gt;
 <a name="L26" href="source/net/ipv4/gre_demux.c#L26">26</a> #include &lt;net/protocol.h&gt;
 <a name="L27" href="source/net/ipv4/gre_demux.c#L27">27</a> #include &lt;net/gre.h&gt;
 <a name="L28" href="source/net/ipv4/gre_demux.c#L28">28</a> 
 <a name="L29" href="source/net/ipv4/gre_demux.c#L29">29</a> #include &lt;net/icmp.h&gt;
 <a name="L30" href="source/net/ipv4/gre_demux.c#L30">30</a> #include &lt;net/route.h&gt;
 <a name="L31" href="source/net/ipv4/gre_demux.c#L31">31</a> #include &lt;net/xfrm.h&gt;
 <a name="L32" href="source/net/ipv4/gre_demux.c#L32">32</a> 
 <a name="L33" href="source/net/ipv4/gre_demux.c#L33">33</a> static const struct <a href="ident?i=gre_protocol">gre_protocol</a> <a href="ident?i=__rcu">__rcu</a> *gre_proto[<a href="ident?i=GREPROTO_MAX">GREPROTO_MAX</a>] <a href="ident?i=__read_mostly">__read_mostly</a>;
 <a name="L34" href="source/net/ipv4/gre_demux.c#L34">34</a> static struct <a href="ident?i=gre_cisco_protocol">gre_cisco_protocol</a> <a href="ident?i=__rcu">__rcu</a> *<a href="ident?i=gre_cisco_proto_list">gre_cisco_proto_list</a>[<a href="ident?i=GRE_IP_PROTO_MAX">GRE_IP_PROTO_MAX</a>];
 <a name="L35" href="source/net/ipv4/gre_demux.c#L35">35</a> 
 <a name="L36" href="source/net/ipv4/gre_demux.c#L36">36</a> int <a href="ident?i=gre_add_protocol">gre_add_protocol</a>(const struct <a href="ident?i=gre_protocol">gre_protocol</a> *<a href="ident?i=proto">proto</a>, <a href="ident?i=u8">u8</a> <a href="ident?i=version">version</a>)
 <a name="L37" href="source/net/ipv4/gre_demux.c#L37">37</a> {
 <a name="L38" href="source/net/ipv4/gre_demux.c#L38">38</a>         if (<a href="ident?i=version">version</a> &gt;= <a href="ident?i=GREPROTO_MAX">GREPROTO_MAX</a>)
 <a name="L39" href="source/net/ipv4/gre_demux.c#L39">39</a>                 return -<a href="ident?i=EINVAL">EINVAL</a>;
 <a name="L40" href="source/net/ipv4/gre_demux.c#L40">40</a> 
 <a name="L41" href="source/net/ipv4/gre_demux.c#L41">41</a>         return (<a href="ident?i=cmpxchg">cmpxchg</a>((const struct <a href="ident?i=gre_protocol">gre_protocol</a> **)&amp;gre_proto[<a href="ident?i=version">version</a>], <a href="ident?i=NULL">NULL</a>, <a href="ident?i=proto">proto</a>) == <a href="ident?i=NULL">NULL</a>) ?
 <a name="L42" href="source/net/ipv4/gre_demux.c#L42">42</a>                 0 : -<a href="ident?i=EBUSY">EBUSY</a>;
 <a name="L43" href="source/net/ipv4/gre_demux.c#L43">43</a> }
 <a name="L44" href="source/net/ipv4/gre_demux.c#L44">44</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=gre_add_protocol">gre_add_protocol</a>);
 <a name="L45" href="source/net/ipv4/gre_demux.c#L45">45</a> 
 <a name="L46" href="source/net/ipv4/gre_demux.c#L46">46</a> int <a href="ident?i=gre_del_protocol">gre_del_protocol</a>(const struct <a href="ident?i=gre_protocol">gre_protocol</a> *<a href="ident?i=proto">proto</a>, <a href="ident?i=u8">u8</a> <a href="ident?i=version">version</a>)
 <a name="L47" href="source/net/ipv4/gre_demux.c#L47">47</a> {
 <a name="L48" href="source/net/ipv4/gre_demux.c#L48">48</a>         int <a href="ident?i=ret">ret</a>;
 <a name="L49" href="source/net/ipv4/gre_demux.c#L49">49</a> 
 <a name="L50" href="source/net/ipv4/gre_demux.c#L50">50</a>         if (<a href="ident?i=version">version</a> &gt;= <a href="ident?i=GREPROTO_MAX">GREPROTO_MAX</a>)
 <a name="L51" href="source/net/ipv4/gre_demux.c#L51">51</a>                 return -<a href="ident?i=EINVAL">EINVAL</a>;
 <a name="L52" href="source/net/ipv4/gre_demux.c#L52">52</a> 
 <a name="L53" href="source/net/ipv4/gre_demux.c#L53">53</a>         <a href="ident?i=ret">ret</a> = (<a href="ident?i=cmpxchg">cmpxchg</a>((const struct <a href="ident?i=gre_protocol">gre_protocol</a> **)&amp;gre_proto[<a href="ident?i=version">version</a>], <a href="ident?i=proto">proto</a>, <a href="ident?i=NULL">NULL</a>) == <a href="ident?i=proto">proto</a>) ?
 <a name="L54" href="source/net/ipv4/gre_demux.c#L54">54</a>                 0 : -<a href="ident?i=EBUSY">EBUSY</a>;
 <a name="L55" href="source/net/ipv4/gre_demux.c#L55">55</a> 
 <a name="L56" href="source/net/ipv4/gre_demux.c#L56">56</a>         if (<a href="ident?i=ret">ret</a>)
 <a name="L57" href="source/net/ipv4/gre_demux.c#L57">57</a>                 return <a href="ident?i=ret">ret</a>;
 <a name="L58" href="source/net/ipv4/gre_demux.c#L58">58</a> 
 <a name="L59" href="source/net/ipv4/gre_demux.c#L59">59</a>         <a href="ident?i=synchronize_rcu">synchronize_rcu</a>();
 <a name="L60" href="source/net/ipv4/gre_demux.c#L60">60</a>         return 0;
 <a name="L61" href="source/net/ipv4/gre_demux.c#L61">61</a> }
 <a name="L62" href="source/net/ipv4/gre_demux.c#L62">62</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=gre_del_protocol">gre_del_protocol</a>);
 <a name="L63" href="source/net/ipv4/gre_demux.c#L63">63</a> 
 <a name="L64" href="source/net/ipv4/gre_demux.c#L64">64</a> void <a href="ident?i=gre_build_header">gre_build_header</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, const struct <a href="ident?i=tnl_ptk_info">tnl_ptk_info</a> *<a href="ident?i=tpi">tpi</a>,
 <a name="L65" href="source/net/ipv4/gre_demux.c#L65">65</a>                       int hdr_len)
 <a name="L66" href="source/net/ipv4/gre_demux.c#L66">66</a> {
 <a name="L67" href="source/net/ipv4/gre_demux.c#L67">67</a>         struct <a href="ident?i=gre_base_hdr">gre_base_hdr</a> *greh;
 <a name="L68" href="source/net/ipv4/gre_demux.c#L68">68</a> 
 <a name="L69" href="source/net/ipv4/gre_demux.c#L69">69</a>         <a href="ident?i=skb_push">skb_push</a>(<a href="ident?i=skb">skb</a>, hdr_len);
 <a name="L70" href="source/net/ipv4/gre_demux.c#L70">70</a> 
 <a name="L71" href="source/net/ipv4/gre_demux.c#L71">71</a>         <a href="ident?i=skb_reset_transport_header">skb_reset_transport_header</a>(<a href="ident?i=skb">skb</a>);
 <a name="L72" href="source/net/ipv4/gre_demux.c#L72">72</a>         greh = (struct <a href="ident?i=gre_base_hdr">gre_base_hdr</a> *)<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=data">data</a>;
 <a name="L73" href="source/net/ipv4/gre_demux.c#L73">73</a>         greh-&gt;<a href="ident?i=flags">flags</a> = <a href="ident?i=tnl_flags_to_gre_flags">tnl_flags_to_gre_flags</a>(<a href="ident?i=tpi">tpi</a>-&gt;<a href="ident?i=flags">flags</a>);
 <a name="L74" href="source/net/ipv4/gre_demux.c#L74">74</a>         greh-&gt;<a href="ident?i=protocol">protocol</a> = <a href="ident?i=tpi">tpi</a>-&gt;<a href="ident?i=proto">proto</a>;
 <a name="L75" href="source/net/ipv4/gre_demux.c#L75">75</a> 
 <a name="L76" href="source/net/ipv4/gre_demux.c#L76">76</a>         if (<a href="ident?i=tpi">tpi</a>-&gt;<a href="ident?i=flags">flags</a>&amp;(<a href="ident?i=TUNNEL_KEY">TUNNEL_KEY</a>|<a href="ident?i=TUNNEL_CSUM">TUNNEL_CSUM</a>|<a href="ident?i=TUNNEL_SEQ">TUNNEL_SEQ</a>)) {
 <a name="L77" href="source/net/ipv4/gre_demux.c#L77">77</a>                 <a href="ident?i=__be32">__be32</a> *<a href="ident?i=ptr">ptr</a> = (<a href="ident?i=__be32">__be32</a> *)(((<a href="ident?i=u8">u8</a> *)greh) + hdr_len - 4);
 <a name="L78" href="source/net/ipv4/gre_demux.c#L78">78</a> 
 <a name="L79" href="source/net/ipv4/gre_demux.c#L79">79</a>                 if (<a href="ident?i=tpi">tpi</a>-&gt;<a href="ident?i=flags">flags</a>&amp;<a href="ident?i=TUNNEL_SEQ">TUNNEL_SEQ</a>) {
 <a name="L80" href="source/net/ipv4/gre_demux.c#L80">80</a>                         *<a href="ident?i=ptr">ptr</a> = <a href="ident?i=tpi">tpi</a>-&gt;<a href="ident?i=seq">seq</a>;
 <a name="L81" href="source/net/ipv4/gre_demux.c#L81">81</a>                         <a href="ident?i=ptr">ptr</a>--;
 <a name="L82" href="source/net/ipv4/gre_demux.c#L82">82</a>                 }
 <a name="L83" href="source/net/ipv4/gre_demux.c#L83">83</a>                 if (<a href="ident?i=tpi">tpi</a>-&gt;<a href="ident?i=flags">flags</a>&amp;<a href="ident?i=TUNNEL_KEY">TUNNEL_KEY</a>) {
 <a name="L84" href="source/net/ipv4/gre_demux.c#L84">84</a>                         *<a href="ident?i=ptr">ptr</a> = <a href="ident?i=tpi">tpi</a>-&gt;<a href="ident?i=key">key</a>;
 <a name="L85" href="source/net/ipv4/gre_demux.c#L85">85</a>                         <a href="ident?i=ptr">ptr</a>--;
 <a name="L86" href="source/net/ipv4/gre_demux.c#L86">86</a>                 }
 <a name="L87" href="source/net/ipv4/gre_demux.c#L87">87</a>                 if (<a href="ident?i=tpi">tpi</a>-&gt;<a href="ident?i=flags">flags</a>&amp;<a href="ident?i=TUNNEL_CSUM">TUNNEL_CSUM</a> &amp;&amp;
 <a name="L88" href="source/net/ipv4/gre_demux.c#L88">88</a>                     !(<a href="ident?i=skb_shinfo">skb_shinfo</a>(<a href="ident?i=skb">skb</a>)-&gt;gso_type &amp;
 <a name="L89" href="source/net/ipv4/gre_demux.c#L89">89</a>                       (SKB_GSO_GRE|SKB_GSO_GRE_CSUM))) {
 <a name="L90" href="source/net/ipv4/gre_demux.c#L90">90</a>                         *<a href="ident?i=ptr">ptr</a> = 0;
 <a name="L91" href="source/net/ipv4/gre_demux.c#L91">91</a>                         *(<a href="ident?i=__sum16">__sum16</a> *)<a href="ident?i=ptr">ptr</a> = <a href="ident?i=csum_fold">csum_fold</a>(<a href="ident?i=skb_checksum">skb_checksum</a>(<a href="ident?i=skb">skb</a>, 0,
 <a name="L92" href="source/net/ipv4/gre_demux.c#L92">92</a>                                                                  <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a>, 0));
 <a name="L93" href="source/net/ipv4/gre_demux.c#L93">93</a>                 }
 <a name="L94" href="source/net/ipv4/gre_demux.c#L94">94</a>         }
 <a name="L95" href="source/net/ipv4/gre_demux.c#L95">95</a> }
 <a name="L96" href="source/net/ipv4/gre_demux.c#L96">96</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=gre_build_header">gre_build_header</a>);
 <a name="L97" href="source/net/ipv4/gre_demux.c#L97">97</a> 
 <a name="L98" href="source/net/ipv4/gre_demux.c#L98">98</a> static int <a href="ident?i=parse_gre_header">parse_gre_header</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, struct <a href="ident?i=tnl_ptk_info">tnl_ptk_info</a> *<a href="ident?i=tpi">tpi</a>,
 <a name="L99" href="source/net/ipv4/gre_demux.c#L99">99</a>                             <a href="ident?i=bool">bool</a> *csum_err)
<a name="L100" href="source/net/ipv4/gre_demux.c#L100">100</a> {
<a name="L101" href="source/net/ipv4/gre_demux.c#L101">101</a>         const struct <a href="ident?i=gre_base_hdr">gre_base_hdr</a> *greh;
<a name="L102" href="source/net/ipv4/gre_demux.c#L102">102</a>         <a href="ident?i=__be32">__be32</a> *<a href="ident?i=options">options</a>;
<a name="L103" href="source/net/ipv4/gre_demux.c#L103">103</a>         int hdr_len;
<a name="L104" href="source/net/ipv4/gre_demux.c#L104">104</a> 
<a name="L105" href="source/net/ipv4/gre_demux.c#L105">105</a>         if (<a href="ident?i=unlikely">unlikely</a>(!<a href="ident?i=pskb_may_pull">pskb_may_pull</a>(<a href="ident?i=skb">skb</a>, sizeof(struct <a href="ident?i=gre_base_hdr">gre_base_hdr</a>))))
<a name="L106" href="source/net/ipv4/gre_demux.c#L106">106</a>                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L107" href="source/net/ipv4/gre_demux.c#L107">107</a> 
<a name="L108" href="source/net/ipv4/gre_demux.c#L108">108</a>         greh = (struct <a href="ident?i=gre_base_hdr">gre_base_hdr</a> *)<a href="ident?i=skb_transport_header">skb_transport_header</a>(<a href="ident?i=skb">skb</a>);
<a name="L109" href="source/net/ipv4/gre_demux.c#L109">109</a>         if (<a href="ident?i=unlikely">unlikely</a>(greh-&gt;<a href="ident?i=flags">flags</a> &amp; (<a href="ident?i=GRE_VERSION">GRE_VERSION</a> | <a href="ident?i=GRE_ROUTING">GRE_ROUTING</a>)))
<a name="L110" href="source/net/ipv4/gre_demux.c#L110">110</a>                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L111" href="source/net/ipv4/gre_demux.c#L111">111</a> 
<a name="L112" href="source/net/ipv4/gre_demux.c#L112">112</a>         <a href="ident?i=tpi">tpi</a>-&gt;<a href="ident?i=flags">flags</a> = <a href="ident?i=gre_flags_to_tnl_flags">gre_flags_to_tnl_flags</a>(greh-&gt;<a href="ident?i=flags">flags</a>);
<a name="L113" href="source/net/ipv4/gre_demux.c#L113">113</a>         hdr_len = <a href="ident?i=ip_gre_calc_hlen">ip_gre_calc_hlen</a>(<a href="ident?i=tpi">tpi</a>-&gt;<a href="ident?i=flags">flags</a>);
<a name="L114" href="source/net/ipv4/gre_demux.c#L114">114</a> 
<a name="L115" href="source/net/ipv4/gre_demux.c#L115">115</a>         if (!<a href="ident?i=pskb_may_pull">pskb_may_pull</a>(<a href="ident?i=skb">skb</a>, hdr_len))
<a name="L116" href="source/net/ipv4/gre_demux.c#L116">116</a>                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L117" href="source/net/ipv4/gre_demux.c#L117">117</a> 
<a name="L118" href="source/net/ipv4/gre_demux.c#L118">118</a>         greh = (struct <a href="ident?i=gre_base_hdr">gre_base_hdr</a> *)<a href="ident?i=skb_transport_header">skb_transport_header</a>(<a href="ident?i=skb">skb</a>);
<a name="L119" href="source/net/ipv4/gre_demux.c#L119">119</a>         <a href="ident?i=tpi">tpi</a>-&gt;<a href="ident?i=proto">proto</a> = greh-&gt;<a href="ident?i=protocol">protocol</a>;
<a name="L120" href="source/net/ipv4/gre_demux.c#L120">120</a> 
<a name="L121" href="source/net/ipv4/gre_demux.c#L121">121</a>         <a href="ident?i=options">options</a> = (<a href="ident?i=__be32">__be32</a> *)(greh + 1);
<a name="L122" href="source/net/ipv4/gre_demux.c#L122">122</a>         if (greh-&gt;<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=GRE_CSUM">GRE_CSUM</a>) {
<a name="L123" href="source/net/ipv4/gre_demux.c#L123">123</a>                 if (<a href="ident?i=skb_checksum_simple_validate">skb_checksum_simple_validate</a>(<a href="ident?i=skb">skb</a>)) {
<a name="L124" href="source/net/ipv4/gre_demux.c#L124">124</a>                         *csum_err = <a href="ident?i=true">true</a>;
<a name="L125" href="source/net/ipv4/gre_demux.c#L125">125</a>                         return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L126" href="source/net/ipv4/gre_demux.c#L126">126</a>                 }
<a name="L127" href="source/net/ipv4/gre_demux.c#L127">127</a> 
<a name="L128" href="source/net/ipv4/gre_demux.c#L128">128</a>                 <a href="ident?i=skb_checksum_try_convert">skb_checksum_try_convert</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=IPPROTO_GRE">IPPROTO_GRE</a>, 0,
<a name="L129" href="source/net/ipv4/gre_demux.c#L129">129</a>                                          <a href="ident?i=null_compute_pseudo">null_compute_pseudo</a>);
<a name="L130" href="source/net/ipv4/gre_demux.c#L130">130</a> 
<a name="L131" href="source/net/ipv4/gre_demux.c#L131">131</a>                 <a href="ident?i=options">options</a>++;
<a name="L132" href="source/net/ipv4/gre_demux.c#L132">132</a>         }
<a name="L133" href="source/net/ipv4/gre_demux.c#L133">133</a> 
<a name="L134" href="source/net/ipv4/gre_demux.c#L134">134</a>         if (greh-&gt;<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=GRE_KEY">GRE_KEY</a>) {
<a name="L135" href="source/net/ipv4/gre_demux.c#L135">135</a>                 <a href="ident?i=tpi">tpi</a>-&gt;<a href="ident?i=key">key</a> = *<a href="ident?i=options">options</a>;
<a name="L136" href="source/net/ipv4/gre_demux.c#L136">136</a>                 <a href="ident?i=options">options</a>++;
<a name="L137" href="source/net/ipv4/gre_demux.c#L137">137</a>         } else
<a name="L138" href="source/net/ipv4/gre_demux.c#L138">138</a>                 <a href="ident?i=tpi">tpi</a>-&gt;<a href="ident?i=key">key</a> = 0;
<a name="L139" href="source/net/ipv4/gre_demux.c#L139">139</a> 
<a name="L140" href="source/net/ipv4/gre_demux.c#L140">140</a>         if (<a href="ident?i=unlikely">unlikely</a>(greh-&gt;<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=GRE_SEQ">GRE_SEQ</a>)) {
<a name="L141" href="source/net/ipv4/gre_demux.c#L141">141</a>                 <a href="ident?i=tpi">tpi</a>-&gt;<a href="ident?i=seq">seq</a> = *<a href="ident?i=options">options</a>;
<a name="L142" href="source/net/ipv4/gre_demux.c#L142">142</a>                 <a href="ident?i=options">options</a>++;
<a name="L143" href="source/net/ipv4/gre_demux.c#L143">143</a>         } else
<a name="L144" href="source/net/ipv4/gre_demux.c#L144">144</a>                 <a href="ident?i=tpi">tpi</a>-&gt;<a href="ident?i=seq">seq</a> = 0;
<a name="L145" href="source/net/ipv4/gre_demux.c#L145">145</a> 
<a name="L146" href="source/net/ipv4/gre_demux.c#L146">146</a>         <b><i>/* WCCP version 1 and 2 protocol decoding.</i></b>
<a name="L147" href="source/net/ipv4/gre_demux.c#L147">147</a> <b><i>         * - Change protocol to IP</i></b>
<a name="L148" href="source/net/ipv4/gre_demux.c#L148">148</a> <b><i>         * - When dealing with WCCPv2, Skip extra 4 bytes in GRE header</i></b>
<a name="L149" href="source/net/ipv4/gre_demux.c#L149">149</a> <b><i>         */</i></b>
<a name="L150" href="source/net/ipv4/gre_demux.c#L150">150</a>         if (greh-&gt;<a href="ident?i=flags">flags</a> == 0 &amp;&amp; <a href="ident?i=tpi">tpi</a>-&gt;<a href="ident?i=proto">proto</a> == <a href="ident?i=htons">htons</a>(<a href="ident?i=ETH_P_WCCP">ETH_P_WCCP</a>)) {
<a name="L151" href="source/net/ipv4/gre_demux.c#L151">151</a>                 <a href="ident?i=tpi">tpi</a>-&gt;<a href="ident?i=proto">proto</a> = <a href="ident?i=htons">htons</a>(<a href="ident?i=ETH_P_IP">ETH_P_IP</a>);
<a name="L152" href="source/net/ipv4/gre_demux.c#L152">152</a>                 if ((*(<a href="ident?i=u8">u8</a> *)<a href="ident?i=options">options</a> &amp; 0xF0) != 0x40) {
<a name="L153" href="source/net/ipv4/gre_demux.c#L153">153</a>                         hdr_len += 4;
<a name="L154" href="source/net/ipv4/gre_demux.c#L154">154</a>                         if (!<a href="ident?i=pskb_may_pull">pskb_may_pull</a>(<a href="ident?i=skb">skb</a>, hdr_len))
<a name="L155" href="source/net/ipv4/gre_demux.c#L155">155</a>                                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L156" href="source/net/ipv4/gre_demux.c#L156">156</a>                 }
<a name="L157" href="source/net/ipv4/gre_demux.c#L157">157</a>         }
<a name="L158" href="source/net/ipv4/gre_demux.c#L158">158</a> 
<a name="L159" href="source/net/ipv4/gre_demux.c#L159">159</a>         return <a href="ident?i=iptunnel_pull_header">iptunnel_pull_header</a>(<a href="ident?i=skb">skb</a>, hdr_len, <a href="ident?i=tpi">tpi</a>-&gt;<a href="ident?i=proto">proto</a>);
<a name="L160" href="source/net/ipv4/gre_demux.c#L160">160</a> }
<a name="L161" href="source/net/ipv4/gre_demux.c#L161">161</a> 
<a name="L162" href="source/net/ipv4/gre_demux.c#L162">162</a> static int <a href="ident?i=gre_cisco_rcv">gre_cisco_rcv</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L163" href="source/net/ipv4/gre_demux.c#L163">163</a> {
<a name="L164" href="source/net/ipv4/gre_demux.c#L164">164</a>         struct <a href="ident?i=tnl_ptk_info">tnl_ptk_info</a> <a href="ident?i=tpi">tpi</a>;
<a name="L165" href="source/net/ipv4/gre_demux.c#L165">165</a>         int <a href="ident?i=i">i</a>;
<a name="L166" href="source/net/ipv4/gre_demux.c#L166">166</a>         <a href="ident?i=bool">bool</a> csum_err = <a href="ident?i=false">false</a>;
<a name="L167" href="source/net/ipv4/gre_demux.c#L167">167</a> 
<a name="L168" href="source/net/ipv4/gre_demux.c#L168">168</a> #ifdef CONFIG_NET_IPGRE_BROADCAST
<a name="L169" href="source/net/ipv4/gre_demux.c#L169">169</a>         if (<a href="ident?i=ipv4_is_multicast">ipv4_is_multicast</a>(<a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=daddr">daddr</a>)) {
<a name="L170" href="source/net/ipv4/gre_demux.c#L170">170</a>                 <b><i>/* Looped back packet, drop it! */</i></b>
<a name="L171" href="source/net/ipv4/gre_demux.c#L171">171</a>                 if (<a href="ident?i=rt_is_output_route">rt_is_output_route</a>(<a href="ident?i=skb_rtable">skb_rtable</a>(<a href="ident?i=skb">skb</a>)))
<a name="L172" href="source/net/ipv4/gre_demux.c#L172">172</a>                         goto <a href="ident?i=drop">drop</a>;
<a name="L173" href="source/net/ipv4/gre_demux.c#L173">173</a>         }
<a name="L174" href="source/net/ipv4/gre_demux.c#L174">174</a> #endif
<a name="L175" href="source/net/ipv4/gre_demux.c#L175">175</a> 
<a name="L176" href="source/net/ipv4/gre_demux.c#L176">176</a>         if (<a href="ident?i=parse_gre_header">parse_gre_header</a>(<a href="ident?i=skb">skb</a>, &amp;<a href="ident?i=tpi">tpi</a>, &amp;csum_err) &lt; 0)
<a name="L177" href="source/net/ipv4/gre_demux.c#L177">177</a>                 goto <a href="ident?i=drop">drop</a>;
<a name="L178" href="source/net/ipv4/gre_demux.c#L178">178</a> 
<a name="L179" href="source/net/ipv4/gre_demux.c#L179">179</a>         <a href="ident?i=rcu_read_lock">rcu_read_lock</a>();
<a name="L180" href="source/net/ipv4/gre_demux.c#L180">180</a>         for (<a href="ident?i=i">i</a> = 0; <a href="ident?i=i">i</a> &lt; <a href="ident?i=GRE_IP_PROTO_MAX">GRE_IP_PROTO_MAX</a>; <a href="ident?i=i">i</a>++) {
<a name="L181" href="source/net/ipv4/gre_demux.c#L181">181</a>                 struct <a href="ident?i=gre_cisco_protocol">gre_cisco_protocol</a> *<a href="ident?i=proto">proto</a>;
<a name="L182" href="source/net/ipv4/gre_demux.c#L182">182</a>                 int <a href="ident?i=ret">ret</a>;
<a name="L183" href="source/net/ipv4/gre_demux.c#L183">183</a> 
<a name="L184" href="source/net/ipv4/gre_demux.c#L184">184</a>                 <a href="ident?i=proto">proto</a> = <a href="ident?i=rcu_dereference">rcu_dereference</a>(<a href="ident?i=gre_cisco_proto_list">gre_cisco_proto_list</a>[<a href="ident?i=i">i</a>]);
<a name="L185" href="source/net/ipv4/gre_demux.c#L185">185</a>                 if (!<a href="ident?i=proto">proto</a>)
<a name="L186" href="source/net/ipv4/gre_demux.c#L186">186</a>                         continue;
<a name="L187" href="source/net/ipv4/gre_demux.c#L187">187</a>                 <a href="ident?i=ret">ret</a> = <a href="ident?i=proto">proto</a>-&gt;<a href="ident?i=handler">handler</a>(<a href="ident?i=skb">skb</a>, &amp;<a href="ident?i=tpi">tpi</a>);
<a name="L188" href="source/net/ipv4/gre_demux.c#L188">188</a>                 if (<a href="ident?i=ret">ret</a> == <a href="ident?i=PACKET_RCVD">PACKET_RCVD</a>) {
<a name="L189" href="source/net/ipv4/gre_demux.c#L189">189</a>                         <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L190" href="source/net/ipv4/gre_demux.c#L190">190</a>                         return 0;
<a name="L191" href="source/net/ipv4/gre_demux.c#L191">191</a>                 }
<a name="L192" href="source/net/ipv4/gre_demux.c#L192">192</a>         }
<a name="L193" href="source/net/ipv4/gre_demux.c#L193">193</a>         <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L194" href="source/net/ipv4/gre_demux.c#L194">194</a> 
<a name="L195" href="source/net/ipv4/gre_demux.c#L195">195</a>         <a href="ident?i=icmp_send">icmp_send</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=ICMP_DEST_UNREACH">ICMP_DEST_UNREACH</a>, <a href="ident?i=ICMP_PORT_UNREACH">ICMP_PORT_UNREACH</a>, 0);
<a name="L196" href="source/net/ipv4/gre_demux.c#L196">196</a> <a href="ident?i=drop">drop</a>:
<a name="L197" href="source/net/ipv4/gre_demux.c#L197">197</a>         <a href="ident?i=kfree_skb">kfree_skb</a>(<a href="ident?i=skb">skb</a>);
<a name="L198" href="source/net/ipv4/gre_demux.c#L198">198</a>         return 0;
<a name="L199" href="source/net/ipv4/gre_demux.c#L199">199</a> }
<a name="L200" href="source/net/ipv4/gre_demux.c#L200">200</a> 
<a name="L201" href="source/net/ipv4/gre_demux.c#L201">201</a> static void <a href="ident?i=gre_cisco_err">gre_cisco_err</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, <a href="ident?i=u32">u32</a> <a href="ident?i=info">info</a>)
<a name="L202" href="source/net/ipv4/gre_demux.c#L202">202</a> {
<a name="L203" href="source/net/ipv4/gre_demux.c#L203">203</a>         <b><i>/* All the routers (except for Linux) return only</i></b>
<a name="L204" href="source/net/ipv4/gre_demux.c#L204">204</a> <b><i>         * 8 bytes of packet payload. It means, that precise relaying of</i></b>
<a name="L205" href="source/net/ipv4/gre_demux.c#L205">205</a> <b><i>         * ICMP in the real Internet is absolutely infeasible.</i></b>
<a name="L206" href="source/net/ipv4/gre_demux.c#L206">206</a> <b><i>         *</i></b>
<a name="L207" href="source/net/ipv4/gre_demux.c#L207">207</a> <b><i>         * Moreover, Cisco "wise men" put GRE key to the third word</i></b>
<a name="L208" href="source/net/ipv4/gre_demux.c#L208">208</a> <b><i>         * in GRE header. It makes impossible maintaining even soft</i></b>
<a name="L209" href="source/net/ipv4/gre_demux.c#L209">209</a> <b><i>         * state for keyed</i></b>
<a name="L210" href="source/net/ipv4/gre_demux.c#L210">210</a> <b><i>         * GRE tunnels with enabled checksum. Tell them "thank you".</i></b>
<a name="L211" href="source/net/ipv4/gre_demux.c#L211">211</a> <b><i>         *</i></b>
<a name="L212" href="source/net/ipv4/gre_demux.c#L212">212</a> <b><i>         * Well, I wonder, rfc1812 was written by Cisco employee,</i></b>
<a name="L213" href="source/net/ipv4/gre_demux.c#L213">213</a> <b><i>         * what the hell these idiots break standards established</i></b>
<a name="L214" href="source/net/ipv4/gre_demux.c#L214">214</a> <b><i>         * by themselves???</i></b>
<a name="L215" href="source/net/ipv4/gre_demux.c#L215">215</a> <b><i>         */</i></b>
<a name="L216" href="source/net/ipv4/gre_demux.c#L216">216</a> 
<a name="L217" href="source/net/ipv4/gre_demux.c#L217">217</a>         const int <a href="ident?i=type">type</a> = <a href="ident?i=icmp_hdr">icmp_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=type">type</a>;
<a name="L218" href="source/net/ipv4/gre_demux.c#L218">218</a>         const int <a href="ident?i=code">code</a> = <a href="ident?i=icmp_hdr">icmp_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=code">code</a>;
<a name="L219" href="source/net/ipv4/gre_demux.c#L219">219</a>         struct <a href="ident?i=tnl_ptk_info">tnl_ptk_info</a> <a href="ident?i=tpi">tpi</a>;
<a name="L220" href="source/net/ipv4/gre_demux.c#L220">220</a>         <a href="ident?i=bool">bool</a> csum_err = <a href="ident?i=false">false</a>;
<a name="L221" href="source/net/ipv4/gre_demux.c#L221">221</a>         int <a href="ident?i=i">i</a>;
<a name="L222" href="source/net/ipv4/gre_demux.c#L222">222</a> 
<a name="L223" href="source/net/ipv4/gre_demux.c#L223">223</a>         if (<a href="ident?i=parse_gre_header">parse_gre_header</a>(<a href="ident?i=skb">skb</a>, &amp;<a href="ident?i=tpi">tpi</a>, &amp;csum_err)) {
<a name="L224" href="source/net/ipv4/gre_demux.c#L224">224</a>                 if (!csum_err)          <b><i>/* ignore csum errors. */</i></b>
<a name="L225" href="source/net/ipv4/gre_demux.c#L225">225</a>                         return;
<a name="L226" href="source/net/ipv4/gre_demux.c#L226">226</a>         }
<a name="L227" href="source/net/ipv4/gre_demux.c#L227">227</a> 
<a name="L228" href="source/net/ipv4/gre_demux.c#L228">228</a>         if (<a href="ident?i=type">type</a> == <a href="ident?i=ICMP_DEST_UNREACH">ICMP_DEST_UNREACH</a> &amp;&amp; <a href="ident?i=code">code</a> == <a href="ident?i=ICMP_FRAG_NEEDED">ICMP_FRAG_NEEDED</a>) {
<a name="L229" href="source/net/ipv4/gre_demux.c#L229">229</a>                 <a href="ident?i=ipv4_update_pmtu">ipv4_update_pmtu</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=dev">dev</a>), <a href="ident?i=info">info</a>,
<a name="L230" href="source/net/ipv4/gre_demux.c#L230">230</a>                                 <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=dev">dev</a>-&gt;ifindex, 0, <a href="ident?i=IPPROTO_GRE">IPPROTO_GRE</a>, 0);
<a name="L231" href="source/net/ipv4/gre_demux.c#L231">231</a>                 return;
<a name="L232" href="source/net/ipv4/gre_demux.c#L232">232</a>         }
<a name="L233" href="source/net/ipv4/gre_demux.c#L233">233</a>         if (<a href="ident?i=type">type</a> == <a href="ident?i=ICMP_REDIRECT">ICMP_REDIRECT</a>) {
<a name="L234" href="source/net/ipv4/gre_demux.c#L234">234</a>                 <a href="ident?i=ipv4_redirect">ipv4_redirect</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=dev">dev</a>), <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=dev">dev</a>-&gt;ifindex, 0,
<a name="L235" href="source/net/ipv4/gre_demux.c#L235">235</a>                                 <a href="ident?i=IPPROTO_GRE">IPPROTO_GRE</a>, 0);
<a name="L236" href="source/net/ipv4/gre_demux.c#L236">236</a>                 return;
<a name="L237" href="source/net/ipv4/gre_demux.c#L237">237</a>         }
<a name="L238" href="source/net/ipv4/gre_demux.c#L238">238</a> 
<a name="L239" href="source/net/ipv4/gre_demux.c#L239">239</a>         <a href="ident?i=rcu_read_lock">rcu_read_lock</a>();
<a name="L240" href="source/net/ipv4/gre_demux.c#L240">240</a>         for (<a href="ident?i=i">i</a> = 0; <a href="ident?i=i">i</a> &lt; <a href="ident?i=GRE_IP_PROTO_MAX">GRE_IP_PROTO_MAX</a>; <a href="ident?i=i">i</a>++) {
<a name="L241" href="source/net/ipv4/gre_demux.c#L241">241</a>                 struct <a href="ident?i=gre_cisco_protocol">gre_cisco_protocol</a> *<a href="ident?i=proto">proto</a>;
<a name="L242" href="source/net/ipv4/gre_demux.c#L242">242</a> 
<a name="L243" href="source/net/ipv4/gre_demux.c#L243">243</a>                 <a href="ident?i=proto">proto</a> = <a href="ident?i=rcu_dereference">rcu_dereference</a>(<a href="ident?i=gre_cisco_proto_list">gre_cisco_proto_list</a>[<a href="ident?i=i">i</a>]);
<a name="L244" href="source/net/ipv4/gre_demux.c#L244">244</a>                 if (!<a href="ident?i=proto">proto</a>)
<a name="L245" href="source/net/ipv4/gre_demux.c#L245">245</a>                         continue;
<a name="L246" href="source/net/ipv4/gre_demux.c#L246">246</a> 
<a name="L247" href="source/net/ipv4/gre_demux.c#L247">247</a>                 if (<a href="ident?i=proto">proto</a>-&gt;<a href="ident?i=err_handler">err_handler</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=info">info</a>, &amp;<a href="ident?i=tpi">tpi</a>) == <a href="ident?i=PACKET_RCVD">PACKET_RCVD</a>)
<a name="L248" href="source/net/ipv4/gre_demux.c#L248">248</a>                         goto <a href="ident?i=out">out</a>;
<a name="L249" href="source/net/ipv4/gre_demux.c#L249">249</a> 
<a name="L250" href="source/net/ipv4/gre_demux.c#L250">250</a>         }
<a name="L251" href="source/net/ipv4/gre_demux.c#L251">251</a> <a href="ident?i=out">out</a>:
<a name="L252" href="source/net/ipv4/gre_demux.c#L252">252</a>         <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L253" href="source/net/ipv4/gre_demux.c#L253">253</a> }
<a name="L254" href="source/net/ipv4/gre_demux.c#L254">254</a> 
<a name="L255" href="source/net/ipv4/gre_demux.c#L255">255</a> static int <a href="ident?i=gre_rcv">gre_rcv</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L256" href="source/net/ipv4/gre_demux.c#L256">256</a> {
<a name="L257" href="source/net/ipv4/gre_demux.c#L257">257</a>         const struct <a href="ident?i=gre_protocol">gre_protocol</a> *<a href="ident?i=proto">proto</a>;
<a name="L258" href="source/net/ipv4/gre_demux.c#L258">258</a>         <a href="ident?i=u8">u8</a> ver;
<a name="L259" href="source/net/ipv4/gre_demux.c#L259">259</a>         int <a href="ident?i=ret">ret</a>;
<a name="L260" href="source/net/ipv4/gre_demux.c#L260">260</a> 
<a name="L261" href="source/net/ipv4/gre_demux.c#L261">261</a>         if (!<a href="ident?i=pskb_may_pull">pskb_may_pull</a>(<a href="ident?i=skb">skb</a>, 12))
<a name="L262" href="source/net/ipv4/gre_demux.c#L262">262</a>                 goto <a href="ident?i=drop">drop</a>;
<a name="L263" href="source/net/ipv4/gre_demux.c#L263">263</a> 
<a name="L264" href="source/net/ipv4/gre_demux.c#L264">264</a>         ver = <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=data">data</a>[1]&amp;0x7f;
<a name="L265" href="source/net/ipv4/gre_demux.c#L265">265</a>         if (ver &gt;= <a href="ident?i=GREPROTO_MAX">GREPROTO_MAX</a>)
<a name="L266" href="source/net/ipv4/gre_demux.c#L266">266</a>                 goto <a href="ident?i=drop">drop</a>;
<a name="L267" href="source/net/ipv4/gre_demux.c#L267">267</a> 
<a name="L268" href="source/net/ipv4/gre_demux.c#L268">268</a>         <a href="ident?i=rcu_read_lock">rcu_read_lock</a>();
<a name="L269" href="source/net/ipv4/gre_demux.c#L269">269</a>         <a href="ident?i=proto">proto</a> = <a href="ident?i=rcu_dereference">rcu_dereference</a>(gre_proto[ver]);
<a name="L270" href="source/net/ipv4/gre_demux.c#L270">270</a>         if (!<a href="ident?i=proto">proto</a> || !<a href="ident?i=proto">proto</a>-&gt;<a href="ident?i=handler">handler</a>)
<a name="L271" href="source/net/ipv4/gre_demux.c#L271">271</a>                 goto drop_unlock;
<a name="L272" href="source/net/ipv4/gre_demux.c#L272">272</a>         <a href="ident?i=ret">ret</a> = <a href="ident?i=proto">proto</a>-&gt;<a href="ident?i=handler">handler</a>(<a href="ident?i=skb">skb</a>);
<a name="L273" href="source/net/ipv4/gre_demux.c#L273">273</a>         <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L274" href="source/net/ipv4/gre_demux.c#L274">274</a>         return <a href="ident?i=ret">ret</a>;
<a name="L275" href="source/net/ipv4/gre_demux.c#L275">275</a> 
<a name="L276" href="source/net/ipv4/gre_demux.c#L276">276</a> drop_unlock:
<a name="L277" href="source/net/ipv4/gre_demux.c#L277">277</a>         <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L278" href="source/net/ipv4/gre_demux.c#L278">278</a> <a href="ident?i=drop">drop</a>:
<a name="L279" href="source/net/ipv4/gre_demux.c#L279">279</a>         <a href="ident?i=kfree_skb">kfree_skb</a>(<a href="ident?i=skb">skb</a>);
<a name="L280" href="source/net/ipv4/gre_demux.c#L280">280</a>         return <a href="ident?i=NET_RX_DROP">NET_RX_DROP</a>;
<a name="L281" href="source/net/ipv4/gre_demux.c#L281">281</a> }
<a name="L282" href="source/net/ipv4/gre_demux.c#L282">282</a> 
<a name="L283" href="source/net/ipv4/gre_demux.c#L283">283</a> static void <a href="ident?i=gre_err">gre_err</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, <a href="ident?i=u32">u32</a> <a href="ident?i=info">info</a>)
<a name="L284" href="source/net/ipv4/gre_demux.c#L284">284</a> {
<a name="L285" href="source/net/ipv4/gre_demux.c#L285">285</a>         const struct <a href="ident?i=gre_protocol">gre_protocol</a> *<a href="ident?i=proto">proto</a>;
<a name="L286" href="source/net/ipv4/gre_demux.c#L286">286</a>         const struct <a href="ident?i=iphdr">iphdr</a> *iph = (const struct <a href="ident?i=iphdr">iphdr</a> *)<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=data">data</a>;
<a name="L287" href="source/net/ipv4/gre_demux.c#L287">287</a>         <a href="ident?i=u8">u8</a> ver = <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=data">data</a>[(iph-&gt;ihl&lt;&lt;2) + 1]&amp;0x7f;
<a name="L288" href="source/net/ipv4/gre_demux.c#L288">288</a> 
<a name="L289" href="source/net/ipv4/gre_demux.c#L289">289</a>         if (ver &gt;= <a href="ident?i=GREPROTO_MAX">GREPROTO_MAX</a>)
<a name="L290" href="source/net/ipv4/gre_demux.c#L290">290</a>                 return;
<a name="L291" href="source/net/ipv4/gre_demux.c#L291">291</a> 
<a name="L292" href="source/net/ipv4/gre_demux.c#L292">292</a>         <a href="ident?i=rcu_read_lock">rcu_read_lock</a>();
<a name="L293" href="source/net/ipv4/gre_demux.c#L293">293</a>         <a href="ident?i=proto">proto</a> = <a href="ident?i=rcu_dereference">rcu_dereference</a>(gre_proto[ver]);
<a name="L294" href="source/net/ipv4/gre_demux.c#L294">294</a>         if (<a href="ident?i=proto">proto</a> &amp;&amp; <a href="ident?i=proto">proto</a>-&gt;<a href="ident?i=err_handler">err_handler</a>)
<a name="L295" href="source/net/ipv4/gre_demux.c#L295">295</a>                 <a href="ident?i=proto">proto</a>-&gt;<a href="ident?i=err_handler">err_handler</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=info">info</a>);
<a name="L296" href="source/net/ipv4/gre_demux.c#L296">296</a>         <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L297" href="source/net/ipv4/gre_demux.c#L297">297</a> }
<a name="L298" href="source/net/ipv4/gre_demux.c#L298">298</a> 
<a name="L299" href="source/net/ipv4/gre_demux.c#L299">299</a> static const struct <a href="ident?i=net_protocol">net_protocol</a> <a href="ident?i=net_gre_protocol">net_gre_protocol</a> = {
<a name="L300" href="source/net/ipv4/gre_demux.c#L300">300</a>         .<a href="ident?i=handler">handler</a>     = <a href="ident?i=gre_rcv">gre_rcv</a>,
<a name="L301" href="source/net/ipv4/gre_demux.c#L301">301</a>         .<a href="ident?i=err_handler">err_handler</a> = <a href="ident?i=gre_err">gre_err</a>,
<a name="L302" href="source/net/ipv4/gre_demux.c#L302">302</a>         .netns_ok    = 1,
<a name="L303" href="source/net/ipv4/gre_demux.c#L303">303</a> };
<a name="L304" href="source/net/ipv4/gre_demux.c#L304">304</a> 
<a name="L305" href="source/net/ipv4/gre_demux.c#L305">305</a> static const struct <a href="ident?i=gre_protocol">gre_protocol</a> <a href="ident?i=ipgre_protocol">ipgre_protocol</a> = {
<a name="L306" href="source/net/ipv4/gre_demux.c#L306">306</a>         .<a href="ident?i=handler">handler</a>     = <a href="ident?i=gre_cisco_rcv">gre_cisco_rcv</a>,
<a name="L307" href="source/net/ipv4/gre_demux.c#L307">307</a>         .<a href="ident?i=err_handler">err_handler</a> = <a href="ident?i=gre_cisco_err">gre_cisco_err</a>,
<a name="L308" href="source/net/ipv4/gre_demux.c#L308">308</a> };
<a name="L309" href="source/net/ipv4/gre_demux.c#L309">309</a> 
<a name="L310" href="source/net/ipv4/gre_demux.c#L310">310</a> int <a href="ident?i=gre_cisco_register">gre_cisco_register</a>(struct <a href="ident?i=gre_cisco_protocol">gre_cisco_protocol</a> *newp)
<a name="L311" href="source/net/ipv4/gre_demux.c#L311">311</a> {
<a name="L312" href="source/net/ipv4/gre_demux.c#L312">312</a>         struct <a href="ident?i=gre_cisco_protocol">gre_cisco_protocol</a> **<a href="ident?i=proto">proto</a> = (struct <a href="ident?i=gre_cisco_protocol">gre_cisco_protocol</a> **)
<a name="L313" href="source/net/ipv4/gre_demux.c#L313">313</a>                                             &amp;<a href="ident?i=gre_cisco_proto_list">gre_cisco_proto_list</a>[newp-&gt;<a href="ident?i=priority">priority</a>];
<a name="L314" href="source/net/ipv4/gre_demux.c#L314">314</a> 
<a name="L315" href="source/net/ipv4/gre_demux.c#L315">315</a>         return (<a href="ident?i=cmpxchg">cmpxchg</a>(<a href="ident?i=proto">proto</a>, <a href="ident?i=NULL">NULL</a>, newp) == <a href="ident?i=NULL">NULL</a>) ? 0 : -<a href="ident?i=EBUSY">EBUSY</a>;
<a name="L316" href="source/net/ipv4/gre_demux.c#L316">316</a> }
<a name="L317" href="source/net/ipv4/gre_demux.c#L317">317</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=gre_cisco_register">gre_cisco_register</a>);
<a name="L318" href="source/net/ipv4/gre_demux.c#L318">318</a> 
<a name="L319" href="source/net/ipv4/gre_demux.c#L319">319</a> int <a href="ident?i=gre_cisco_unregister">gre_cisco_unregister</a>(struct <a href="ident?i=gre_cisco_protocol">gre_cisco_protocol</a> *del_proto)
<a name="L320" href="source/net/ipv4/gre_demux.c#L320">320</a> {
<a name="L321" href="source/net/ipv4/gre_demux.c#L321">321</a>         struct <a href="ident?i=gre_cisco_protocol">gre_cisco_protocol</a> **<a href="ident?i=proto">proto</a> = (struct <a href="ident?i=gre_cisco_protocol">gre_cisco_protocol</a> **)
<a name="L322" href="source/net/ipv4/gre_demux.c#L322">322</a>                                             &amp;<a href="ident?i=gre_cisco_proto_list">gre_cisco_proto_list</a>[del_proto-&gt;<a href="ident?i=priority">priority</a>];
<a name="L323" href="source/net/ipv4/gre_demux.c#L323">323</a>         int <a href="ident?i=ret">ret</a>;
<a name="L324" href="source/net/ipv4/gre_demux.c#L324">324</a> 
<a name="L325" href="source/net/ipv4/gre_demux.c#L325">325</a>         <a href="ident?i=ret">ret</a> = (<a href="ident?i=cmpxchg">cmpxchg</a>(<a href="ident?i=proto">proto</a>, del_proto, <a href="ident?i=NULL">NULL</a>) == del_proto) ? 0 : -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L326" href="source/net/ipv4/gre_demux.c#L326">326</a> 
<a name="L327" href="source/net/ipv4/gre_demux.c#L327">327</a>         if (<a href="ident?i=ret">ret</a>)
<a name="L328" href="source/net/ipv4/gre_demux.c#L328">328</a>                 return <a href="ident?i=ret">ret</a>;
<a name="L329" href="source/net/ipv4/gre_demux.c#L329">329</a> 
<a name="L330" href="source/net/ipv4/gre_demux.c#L330">330</a>         <a href="ident?i=synchronize_net">synchronize_net</a>();
<a name="L331" href="source/net/ipv4/gre_demux.c#L331">331</a>         return 0;
<a name="L332" href="source/net/ipv4/gre_demux.c#L332">332</a> }
<a name="L333" href="source/net/ipv4/gre_demux.c#L333">333</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=gre_cisco_unregister">gre_cisco_unregister</a>);
<a name="L334" href="source/net/ipv4/gre_demux.c#L334">334</a> 
<a name="L335" href="source/net/ipv4/gre_demux.c#L335">335</a> static int <a href="ident?i=__init">__init</a> <a href="ident?i=gre_init">gre_init</a>(void)
<a name="L336" href="source/net/ipv4/gre_demux.c#L336">336</a> {
<a name="L337" href="source/net/ipv4/gre_demux.c#L337">337</a>         <a href="ident?i=pr_info">pr_info</a>(<i>"GRE over IPv4 demultiplexor driver\n"</i>);
<a name="L338" href="source/net/ipv4/gre_demux.c#L338">338</a> 
<a name="L339" href="source/net/ipv4/gre_demux.c#L339">339</a>         if (<a href="ident?i=inet_add_protocol">inet_add_protocol</a>(&amp;<a href="ident?i=net_gre_protocol">net_gre_protocol</a>, <a href="ident?i=IPPROTO_GRE">IPPROTO_GRE</a>) &lt; 0) {
<a name="L340" href="source/net/ipv4/gre_demux.c#L340">340</a>                 <a href="ident?i=pr_err">pr_err</a>(<i>"can't add protocol\n"</i>);
<a name="L341" href="source/net/ipv4/gre_demux.c#L341">341</a>                 goto <a href="ident?i=err">err</a>;
<a name="L342" href="source/net/ipv4/gre_demux.c#L342">342</a>         }
<a name="L343" href="source/net/ipv4/gre_demux.c#L343">343</a> 
<a name="L344" href="source/net/ipv4/gre_demux.c#L344">344</a>         if (<a href="ident?i=gre_add_protocol">gre_add_protocol</a>(&amp;<a href="ident?i=ipgre_protocol">ipgre_protocol</a>, <a href="ident?i=GREPROTO_CISCO">GREPROTO_CISCO</a>) &lt; 0) {
<a name="L345" href="source/net/ipv4/gre_demux.c#L345">345</a>                 <a href="ident?i=pr_info">pr_info</a>(<i>"%s: can't add ipgre handler\n"</i>, <a href="ident?i=__func__">__func__</a>);
<a name="L346" href="source/net/ipv4/gre_demux.c#L346">346</a>                 goto err_gre;
<a name="L347" href="source/net/ipv4/gre_demux.c#L347">347</a>         }
<a name="L348" href="source/net/ipv4/gre_demux.c#L348">348</a> 
<a name="L349" href="source/net/ipv4/gre_demux.c#L349">349</a>         return 0;
<a name="L350" href="source/net/ipv4/gre_demux.c#L350">350</a> err_gre:
<a name="L351" href="source/net/ipv4/gre_demux.c#L351">351</a>         <a href="ident?i=inet_del_protocol">inet_del_protocol</a>(&amp;<a href="ident?i=net_gre_protocol">net_gre_protocol</a>, <a href="ident?i=IPPROTO_GRE">IPPROTO_GRE</a>);
<a name="L352" href="source/net/ipv4/gre_demux.c#L352">352</a> <a href="ident?i=err">err</a>:
<a name="L353" href="source/net/ipv4/gre_demux.c#L353">353</a>         return -<a href="ident?i=EAGAIN">EAGAIN</a>;
<a name="L354" href="source/net/ipv4/gre_demux.c#L354">354</a> }
<a name="L355" href="source/net/ipv4/gre_demux.c#L355">355</a> 
<a name="L356" href="source/net/ipv4/gre_demux.c#L356">356</a> static void <a href="ident?i=__exit">__exit</a> <a href="ident?i=gre_exit">gre_exit</a>(void)
<a name="L357" href="source/net/ipv4/gre_demux.c#L357">357</a> {
<a name="L358" href="source/net/ipv4/gre_demux.c#L358">358</a>         <a href="ident?i=gre_del_protocol">gre_del_protocol</a>(&amp;<a href="ident?i=ipgre_protocol">ipgre_protocol</a>, <a href="ident?i=GREPROTO_CISCO">GREPROTO_CISCO</a>);
<a name="L359" href="source/net/ipv4/gre_demux.c#L359">359</a>         <a href="ident?i=inet_del_protocol">inet_del_protocol</a>(&amp;<a href="ident?i=net_gre_protocol">net_gre_protocol</a>, <a href="ident?i=IPPROTO_GRE">IPPROTO_GRE</a>);
<a name="L360" href="source/net/ipv4/gre_demux.c#L360">360</a> }
<a name="L361" href="source/net/ipv4/gre_demux.c#L361">361</a> 
<a name="L362" href="source/net/ipv4/gre_demux.c#L362">362</a> <a href="ident?i=module_init">module_init</a>(<a href="ident?i=gre_init">gre_init</a>);
<a name="L363" href="source/net/ipv4/gre_demux.c#L363">363</a> <a href="ident?i=module_exit">module_exit</a>(<a href="ident?i=gre_exit">gre_exit</a>);
<a name="L364" href="source/net/ipv4/gre_demux.c#L364">364</a> 
<a name="L365" href="source/net/ipv4/gre_demux.c#L365">365</a> <a href="ident?i=MODULE_DESCRIPTION">MODULE_DESCRIPTION</a>(<i>"GRE over IPv4 demultiplexer driver"</i>);
<a name="L366" href="source/net/ipv4/gre_demux.c#L366">366</a> <a href="ident?i=MODULE_AUTHOR">MODULE_AUTHOR</a>(<i>"D. Kozlov (xeb@mail.ru)"</i>);
<a name="L367" href="source/net/ipv4/gre_demux.c#L367">367</a> <a href="ident?i=MODULE_LICENSE">MODULE_LICENSE</a>(<i>"GPL"</i>);
<a name="L368" href="source/net/ipv4/gre_demux.c#L368">368</a> </pre></div><p>
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
