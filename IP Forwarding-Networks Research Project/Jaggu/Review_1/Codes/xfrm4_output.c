<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title>Linux/net/ipv4/xfrm4_output.c - Linux Cross Reference - Free Electrons</title>
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
		 &nbsp;&bull;&nbsp;<b><i>source navigation</i></b> &nbsp;&bull;&nbsp;<a href="diff/net/ipv4/xfrm4_output.c">diff markup</a> &nbsp;&bull;&nbsp;<a href="ident">identifier search</a> &nbsp;&bull;&nbsp;<a href="search">freetext search</a> &nbsp;&bull;&nbsp;
		</p>
	</div>
</div>

<div id="topbar">
  
  <p>Version: &nbsp;<a href="source/net/ipv4/xfrm4_output.c?v=2.0.40">2.0.40</a>&nbsp;<a href="source/net/ipv4/xfrm4_output.c?v=2.2.26">2.2.26</a>&nbsp;<a href="source/net/ipv4/xfrm4_output.c?v=2.4.37">2.4.37</a>&nbsp;<a href="source/net/ipv4/xfrm4_output.c?v=3.5">3.5</a>&nbsp;<a href="source/net/ipv4/xfrm4_output.c?v=3.6">3.6</a>&nbsp;<a href="source/net/ipv4/xfrm4_output.c?v=3.7">3.7</a>&nbsp;<a href="source/net/ipv4/xfrm4_output.c?v=3.8">3.8</a>&nbsp;<a href="source/net/ipv4/xfrm4_output.c?v=3.9">3.9</a>&nbsp;<a href="source/net/ipv4/xfrm4_output.c?v=3.10">3.10</a>&nbsp;<a href="source/net/ipv4/xfrm4_output.c?v=3.11">3.11</a>&nbsp;<a href="source/net/ipv4/xfrm4_output.c?v=3.12">3.12</a>&nbsp;<a href="source/net/ipv4/xfrm4_output.c?v=3.13">3.13</a>&nbsp;<a href="source/net/ipv4/xfrm4_output.c?v=3.14">3.14</a>&nbsp;<a href="source/net/ipv4/xfrm4_output.c?v=3.15">3.15</a>&nbsp;<a href="source/net/ipv4/xfrm4_output.c?v=3.16">3.16</a>&nbsp;<a href="source/net/ipv4/xfrm4_output.c?v=3.17">3.17</a>&nbsp;<a href="source/net/ipv4/xfrm4_output.c?v=3.18">3.18</a>&nbsp;<a href="source/net/ipv4/xfrm4_output.c?v=3.19">3.19</a>&nbsp;<a href="source/net/ipv4/xfrm4_output.c?v=4.0">4.0</a>&nbsp;<b><i>4.1</i></b></p>
  
</div>

<h1><a href="source/">Linux</a>/<a href="source/net/">net</a>/<a href="source/net/ipv4/">ipv4</a>/<a href="source/net/ipv4/xfrm4_output.c">xfrm4_output.c</a></h1>
<div id="lxrcode"><pre>  <a name="L1" href="source/net/ipv4/xfrm4_output.c#L1">1</a> <b><i>/*</i></b>
  <a name="L2" href="source/net/ipv4/xfrm4_output.c#L2">2</a> <b><i> * xfrm4_output.c - Common IPsec encapsulation code for IPv4.</i></b>
  <a name="L3" href="source/net/ipv4/xfrm4_output.c#L3">3</a> <b><i> * Copyright (c) 2004 Herbert Xu &lt;herbert@gondor.apana.org.au&gt;</i></b>
  <a name="L4" href="source/net/ipv4/xfrm4_output.c#L4">4</a> <b><i> *</i></b>
  <a name="L5" href="source/net/ipv4/xfrm4_output.c#L5">5</a> <b><i> * This program is free software; you can redistribute it and/or</i></b>
  <a name="L6" href="source/net/ipv4/xfrm4_output.c#L6">6</a> <b><i> * modify it under the terms of the GNU General Public License</i></b>
  <a name="L7" href="source/net/ipv4/xfrm4_output.c#L7">7</a> <b><i> * as published by the Free Software Foundation; either version</i></b>
  <a name="L8" href="source/net/ipv4/xfrm4_output.c#L8">8</a> <b><i> * 2 of the License, or (at your option) any later version.</i></b>
  <a name="L9" href="source/net/ipv4/xfrm4_output.c#L9">9</a> <b><i> */</i></b>
 <a name="L10" href="source/net/ipv4/xfrm4_output.c#L10">10</a> 
 <a name="L11" href="source/net/ipv4/xfrm4_output.c#L11">11</a> #include &lt;linux/if_ether.h&gt;
 <a name="L12" href="source/net/ipv4/xfrm4_output.c#L12">12</a> #include &lt;linux/kernel.h&gt;
 <a name="L13" href="source/net/ipv4/xfrm4_output.c#L13">13</a> #include &lt;linux/module.h&gt;
 <a name="L14" href="source/net/ipv4/xfrm4_output.c#L14">14</a> #include &lt;linux/skbuff.h&gt;
 <a name="L15" href="source/net/ipv4/xfrm4_output.c#L15">15</a> #include &lt;linux/netfilter_ipv4.h&gt;
 <a name="L16" href="source/net/ipv4/xfrm4_output.c#L16">16</a> #include &lt;net/dst.h&gt;
 <a name="L17" href="source/net/ipv4/xfrm4_output.c#L17">17</a> #include &lt;net/ip.h&gt;
 <a name="L18" href="source/net/ipv4/xfrm4_output.c#L18">18</a> #include &lt;net/xfrm.h&gt;
 <a name="L19" href="source/net/ipv4/xfrm4_output.c#L19">19</a> #include &lt;net/icmp.h&gt;
 <a name="L20" href="source/net/ipv4/xfrm4_output.c#L20">20</a> 
 <a name="L21" href="source/net/ipv4/xfrm4_output.c#L21">21</a> static int <a href="ident?i=xfrm4_tunnel_check_size">xfrm4_tunnel_check_size</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
 <a name="L22" href="source/net/ipv4/xfrm4_output.c#L22">22</a> {
 <a name="L23" href="source/net/ipv4/xfrm4_output.c#L23">23</a>         int <a href="ident?i=mtu">mtu</a>, <a href="ident?i=ret">ret</a> = 0;
 <a name="L24" href="source/net/ipv4/xfrm4_output.c#L24">24</a> 
 <a name="L25" href="source/net/ipv4/xfrm4_output.c#L25">25</a>         if (<a href="ident?i=IPCB">IPCB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=IPSKB_XFRM_TUNNEL_SIZE">IPSKB_XFRM_TUNNEL_SIZE</a>)
 <a name="L26" href="source/net/ipv4/xfrm4_output.c#L26">26</a>                 goto <a href="ident?i=out">out</a>;
 <a name="L27" href="source/net/ipv4/xfrm4_output.c#L27">27</a> 
 <a name="L28" href="source/net/ipv4/xfrm4_output.c#L28">28</a>         if (!(<a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;frag_off &amp; <a href="ident?i=htons">htons</a>(<a href="ident?i=IP_DF">IP_DF</a>)) || <a href="ident?i=skb">skb</a>-&gt;ignore_df)
 <a name="L29" href="source/net/ipv4/xfrm4_output.c#L29">29</a>                 goto <a href="ident?i=out">out</a>;
 <a name="L30" href="source/net/ipv4/xfrm4_output.c#L30">30</a> 
 <a name="L31" href="source/net/ipv4/xfrm4_output.c#L31">31</a>         <a href="ident?i=mtu">mtu</a> = <a href="ident?i=dst_mtu">dst_mtu</a>(<a href="ident?i=skb_dst">skb_dst</a>(<a href="ident?i=skb">skb</a>));
 <a name="L32" href="source/net/ipv4/xfrm4_output.c#L32">32</a>         if (<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a> &gt; <a href="ident?i=mtu">mtu</a>) {
 <a name="L33" href="source/net/ipv4/xfrm4_output.c#L33">33</a>                 if (<a href="ident?i=skb">skb</a>-&gt;sk)
 <a name="L34" href="source/net/ipv4/xfrm4_output.c#L34">34</a>                         <a href="ident?i=xfrm_local_error">xfrm_local_error</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=mtu">mtu</a>);
 <a name="L35" href="source/net/ipv4/xfrm4_output.c#L35">35</a>                 else
 <a name="L36" href="source/net/ipv4/xfrm4_output.c#L36">36</a>                         <a href="ident?i=icmp_send">icmp_send</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=ICMP_DEST_UNREACH">ICMP_DEST_UNREACH</a>,
 <a name="L37" href="source/net/ipv4/xfrm4_output.c#L37">37</a>                                   <a href="ident?i=ICMP_FRAG_NEEDED">ICMP_FRAG_NEEDED</a>, <a href="ident?i=htonl">htonl</a>(<a href="ident?i=mtu">mtu</a>));
 <a name="L38" href="source/net/ipv4/xfrm4_output.c#L38">38</a>                 <a href="ident?i=ret">ret</a> = -<a href="ident?i=EMSGSIZE">EMSGSIZE</a>;
 <a name="L39" href="source/net/ipv4/xfrm4_output.c#L39">39</a>         }
 <a name="L40" href="source/net/ipv4/xfrm4_output.c#L40">40</a> <a href="ident?i=out">out</a>:
 <a name="L41" href="source/net/ipv4/xfrm4_output.c#L41">41</a>         return <a href="ident?i=ret">ret</a>;
 <a name="L42" href="source/net/ipv4/xfrm4_output.c#L42">42</a> }
 <a name="L43" href="source/net/ipv4/xfrm4_output.c#L43">43</a> 
 <a name="L44" href="source/net/ipv4/xfrm4_output.c#L44">44</a> int <a href="ident?i=xfrm4_extract_output">xfrm4_extract_output</a>(struct <a href="ident?i=xfrm_state">xfrm_state</a> *<a href="ident?i=x">x</a>, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
 <a name="L45" href="source/net/ipv4/xfrm4_output.c#L45">45</a> {
 <a name="L46" href="source/net/ipv4/xfrm4_output.c#L46">46</a>         int <a href="ident?i=err">err</a>;
 <a name="L47" href="source/net/ipv4/xfrm4_output.c#L47">47</a> 
 <a name="L48" href="source/net/ipv4/xfrm4_output.c#L48">48</a>         <a href="ident?i=err">err</a> = <a href="ident?i=xfrm4_tunnel_check_size">xfrm4_tunnel_check_size</a>(<a href="ident?i=skb">skb</a>);
 <a name="L49" href="source/net/ipv4/xfrm4_output.c#L49">49</a>         if (<a href="ident?i=err">err</a>)
 <a name="L50" href="source/net/ipv4/xfrm4_output.c#L50">50</a>                 return <a href="ident?i=err">err</a>;
 <a name="L51" href="source/net/ipv4/xfrm4_output.c#L51">51</a> 
 <a name="L52" href="source/net/ipv4/xfrm4_output.c#L52">52</a>         <a href="ident?i=XFRM_MODE_SKB_CB">XFRM_MODE_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=protocol">protocol</a> = <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=protocol">protocol</a>;
 <a name="L53" href="source/net/ipv4/xfrm4_output.c#L53">53</a> 
 <a name="L54" href="source/net/ipv4/xfrm4_output.c#L54">54</a>         return <a href="ident?i=xfrm4_extract_header">xfrm4_extract_header</a>(<a href="ident?i=skb">skb</a>);
 <a name="L55" href="source/net/ipv4/xfrm4_output.c#L55">55</a> }
 <a name="L56" href="source/net/ipv4/xfrm4_output.c#L56">56</a> 
 <a name="L57" href="source/net/ipv4/xfrm4_output.c#L57">57</a> int <a href="ident?i=xfrm4_prepare_output">xfrm4_prepare_output</a>(struct <a href="ident?i=xfrm_state">xfrm_state</a> *<a href="ident?i=x">x</a>, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
 <a name="L58" href="source/net/ipv4/xfrm4_output.c#L58">58</a> {
 <a name="L59" href="source/net/ipv4/xfrm4_output.c#L59">59</a>         int <a href="ident?i=err">err</a>;
 <a name="L60" href="source/net/ipv4/xfrm4_output.c#L60">60</a> 
 <a name="L61" href="source/net/ipv4/xfrm4_output.c#L61">61</a>         <a href="ident?i=err">err</a> = <a href="ident?i=xfrm_inner_extract_output">xfrm_inner_extract_output</a>(<a href="ident?i=x">x</a>, <a href="ident?i=skb">skb</a>);
 <a name="L62" href="source/net/ipv4/xfrm4_output.c#L62">62</a>         if (<a href="ident?i=err">err</a>)
 <a name="L63" href="source/net/ipv4/xfrm4_output.c#L63">63</a>                 return <a href="ident?i=err">err</a>;
 <a name="L64" href="source/net/ipv4/xfrm4_output.c#L64">64</a> 
 <a name="L65" href="source/net/ipv4/xfrm4_output.c#L65">65</a>         <a href="ident?i=IPCB">IPCB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=flags">flags</a> |= <a href="ident?i=IPSKB_XFRM_TUNNEL_SIZE">IPSKB_XFRM_TUNNEL_SIZE</a>;
 <a name="L66" href="source/net/ipv4/xfrm4_output.c#L66">66</a>         <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=protocol">protocol</a> = <a href="ident?i=htons">htons</a>(<a href="ident?i=ETH_P_IP">ETH_P_IP</a>);
 <a name="L67" href="source/net/ipv4/xfrm4_output.c#L67">67</a> 
 <a name="L68" href="source/net/ipv4/xfrm4_output.c#L68">68</a>         return <a href="ident?i=x">x</a>-&gt;outer_mode-&gt;output2(<a href="ident?i=x">x</a>, <a href="ident?i=skb">skb</a>);
 <a name="L69" href="source/net/ipv4/xfrm4_output.c#L69">69</a> }
 <a name="L70" href="source/net/ipv4/xfrm4_output.c#L70">70</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=xfrm4_prepare_output">xfrm4_prepare_output</a>);
 <a name="L71" href="source/net/ipv4/xfrm4_output.c#L71">71</a> 
 <a name="L72" href="source/net/ipv4/xfrm4_output.c#L72">72</a> int <a href="ident?i=xfrm4_output_finish">xfrm4_output_finish</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
 <a name="L73" href="source/net/ipv4/xfrm4_output.c#L73">73</a> {
 <a name="L74" href="source/net/ipv4/xfrm4_output.c#L74">74</a>         <a href="ident?i=memset">memset</a>(<a href="ident?i=IPCB">IPCB</a>(<a href="ident?i=skb">skb</a>), 0, sizeof(*<a href="ident?i=IPCB">IPCB</a>(<a href="ident?i=skb">skb</a>)));
 <a name="L75" href="source/net/ipv4/xfrm4_output.c#L75">75</a> 
 <a name="L76" href="source/net/ipv4/xfrm4_output.c#L76">76</a> #ifdef CONFIG_NETFILTER
 <a name="L77" href="source/net/ipv4/xfrm4_output.c#L77">77</a>         <a href="ident?i=IPCB">IPCB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=flags">flags</a> |= <a href="ident?i=IPSKB_XFRM_TRANSFORMED">IPSKB_XFRM_TRANSFORMED</a>;
 <a name="L78" href="source/net/ipv4/xfrm4_output.c#L78">78</a> #endif
 <a name="L79" href="source/net/ipv4/xfrm4_output.c#L79">79</a> 
 <a name="L80" href="source/net/ipv4/xfrm4_output.c#L80">80</a>         return <a href="ident?i=xfrm_output">xfrm_output</a>(sk, <a href="ident?i=skb">skb</a>);
 <a name="L81" href="source/net/ipv4/xfrm4_output.c#L81">81</a> }
 <a name="L82" href="source/net/ipv4/xfrm4_output.c#L82">82</a> 
 <a name="L83" href="source/net/ipv4/xfrm4_output.c#L83">83</a> static int <a href="ident?i=__xfrm4_output">__xfrm4_output</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
 <a name="L84" href="source/net/ipv4/xfrm4_output.c#L84">84</a> {
 <a name="L85" href="source/net/ipv4/xfrm4_output.c#L85">85</a>         struct <a href="ident?i=xfrm_state">xfrm_state</a> *<a href="ident?i=x">x</a> = <a href="ident?i=skb_dst">skb_dst</a>(<a href="ident?i=skb">skb</a>)-&gt;xfrm;
 <a name="L86" href="source/net/ipv4/xfrm4_output.c#L86">86</a> 
 <a name="L87" href="source/net/ipv4/xfrm4_output.c#L87">87</a> #ifdef CONFIG_NETFILTER
 <a name="L88" href="source/net/ipv4/xfrm4_output.c#L88">88</a>         if (!<a href="ident?i=x">x</a>) {
 <a name="L89" href="source/net/ipv4/xfrm4_output.c#L89">89</a>                 <a href="ident?i=IPCB">IPCB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=flags">flags</a> |= <a href="ident?i=IPSKB_REROUTED">IPSKB_REROUTED</a>;
 <a name="L90" href="source/net/ipv4/xfrm4_output.c#L90">90</a>                 return <a href="ident?i=dst_output_sk">dst_output_sk</a>(sk, <a href="ident?i=skb">skb</a>);
 <a name="L91" href="source/net/ipv4/xfrm4_output.c#L91">91</a>         }
 <a name="L92" href="source/net/ipv4/xfrm4_output.c#L92">92</a> #endif
 <a name="L93" href="source/net/ipv4/xfrm4_output.c#L93">93</a> 
 <a name="L94" href="source/net/ipv4/xfrm4_output.c#L94">94</a>         return <a href="ident?i=x">x</a>-&gt;outer_mode-&gt;afinfo-&gt;output_finish(sk, <a href="ident?i=skb">skb</a>);
 <a name="L95" href="source/net/ipv4/xfrm4_output.c#L95">95</a> }
 <a name="L96" href="source/net/ipv4/xfrm4_output.c#L96">96</a> 
 <a name="L97" href="source/net/ipv4/xfrm4_output.c#L97">97</a> int <a href="ident?i=xfrm4_output">xfrm4_output</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
 <a name="L98" href="source/net/ipv4/xfrm4_output.c#L98">98</a> {
 <a name="L99" href="source/net/ipv4/xfrm4_output.c#L99">99</a>         return <a href="ident?i=NF_HOOK_COND">NF_HOOK_COND</a>(NFPROTO_IPV4, NF_INET_POST_ROUTING, sk, <a href="ident?i=skb">skb</a>,
<a name="L100" href="source/net/ipv4/xfrm4_output.c#L100">100</a>                             <a href="ident?i=NULL">NULL</a>, <a href="ident?i=skb_dst">skb_dst</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=dev">dev</a>, <a href="ident?i=__xfrm4_output">__xfrm4_output</a>,
<a name="L101" href="source/net/ipv4/xfrm4_output.c#L101">101</a>                             !(<a href="ident?i=IPCB">IPCB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=IPSKB_REROUTED">IPSKB_REROUTED</a>));
<a name="L102" href="source/net/ipv4/xfrm4_output.c#L102">102</a> }
<a name="L103" href="source/net/ipv4/xfrm4_output.c#L103">103</a> 
<a name="L104" href="source/net/ipv4/xfrm4_output.c#L104">104</a> void <a href="ident?i=xfrm4_local_error">xfrm4_local_error</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, <a href="ident?i=u32">u32</a> <a href="ident?i=mtu">mtu</a>)
<a name="L105" href="source/net/ipv4/xfrm4_output.c#L105">105</a> {
<a name="L106" href="source/net/ipv4/xfrm4_output.c#L106">106</a>         struct <a href="ident?i=iphdr">iphdr</a> *<a href="ident?i=hdr">hdr</a>;
<a name="L107" href="source/net/ipv4/xfrm4_output.c#L107">107</a> 
<a name="L108" href="source/net/ipv4/xfrm4_output.c#L108">108</a>         <a href="ident?i=hdr">hdr</a> = <a href="ident?i=skb">skb</a>-&gt;encapsulation ? <a href="ident?i=inner_ip_hdr">inner_ip_hdr</a>(<a href="ident?i=skb">skb</a>) : <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>);
<a name="L109" href="source/net/ipv4/xfrm4_output.c#L109">109</a>         <a href="ident?i=ip_local_error">ip_local_error</a>(<a href="ident?i=skb">skb</a>-&gt;sk, <a href="ident?i=EMSGSIZE">EMSGSIZE</a>, <a href="ident?i=hdr">hdr</a>-&gt;<a href="ident?i=daddr">daddr</a>,
<a name="L110" href="source/net/ipv4/xfrm4_output.c#L110">110</a>                        <a href="ident?i=inet_sk">inet_sk</a>(<a href="ident?i=skb">skb</a>-&gt;sk)-&gt;<a href="ident?i=inet_dport">inet_dport</a>, <a href="ident?i=mtu">mtu</a>);
<a name="L111" href="source/net/ipv4/xfrm4_output.c#L111">111</a> }
<a name="L112" href="source/net/ipv4/xfrm4_output.c#L112">112</a> </pre></div><p>
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
