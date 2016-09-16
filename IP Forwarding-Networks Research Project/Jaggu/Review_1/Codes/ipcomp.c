<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title>Linux/net/ipv4/ipcomp.c - Linux Cross Reference - Free Electrons</title>
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
		 &nbsp;&bull;&nbsp;<b><i>source navigation</i></b> &nbsp;&bull;&nbsp;<a href="diff/net/ipv4/ipcomp.c">diff markup</a> &nbsp;&bull;&nbsp;<a href="ident">identifier search</a> &nbsp;&bull;&nbsp;<a href="search">freetext search</a> &nbsp;&bull;&nbsp;
		</p>
	</div>
</div>

<div id="topbar">
  
  <p>Version: &nbsp;<a href="source/net/ipv4/ipcomp.c?v=2.0.40">2.0.40</a>&nbsp;<a href="source/net/ipv4/ipcomp.c?v=2.2.26">2.2.26</a>&nbsp;<a href="source/net/ipv4/ipcomp.c?v=2.4.37">2.4.37</a>&nbsp;<a href="source/net/ipv4/ipcomp.c?v=3.5">3.5</a>&nbsp;<a href="source/net/ipv4/ipcomp.c?v=3.6">3.6</a>&nbsp;<a href="source/net/ipv4/ipcomp.c?v=3.7">3.7</a>&nbsp;<a href="source/net/ipv4/ipcomp.c?v=3.8">3.8</a>&nbsp;<a href="source/net/ipv4/ipcomp.c?v=3.9">3.9</a>&nbsp;<a href="source/net/ipv4/ipcomp.c?v=3.10">3.10</a>&nbsp;<a href="source/net/ipv4/ipcomp.c?v=3.11">3.11</a>&nbsp;<a href="source/net/ipv4/ipcomp.c?v=3.12">3.12</a>&nbsp;<a href="source/net/ipv4/ipcomp.c?v=3.13">3.13</a>&nbsp;<a href="source/net/ipv4/ipcomp.c?v=3.14">3.14</a>&nbsp;<a href="source/net/ipv4/ipcomp.c?v=3.15">3.15</a>&nbsp;<a href="source/net/ipv4/ipcomp.c?v=3.16">3.16</a>&nbsp;<a href="source/net/ipv4/ipcomp.c?v=3.17">3.17</a>&nbsp;<a href="source/net/ipv4/ipcomp.c?v=3.18">3.18</a>&nbsp;<a href="source/net/ipv4/ipcomp.c?v=3.19">3.19</a>&nbsp;<a href="source/net/ipv4/ipcomp.c?v=4.0">4.0</a>&nbsp;<b><i>4.1</i></b></p>
  
</div>

<h1><a href="source/">Linux</a>/<a href="source/net/">net</a>/<a href="source/net/ipv4/">ipv4</a>/<a href="source/net/ipv4/ipcomp.c">ipcomp.c</a></h1>
<div id="lxrcode"><pre>  <a name="L1" href="source/net/ipv4/ipcomp.c#L1">1</a> <b><i>/*</i></b>
  <a name="L2" href="source/net/ipv4/ipcomp.c#L2">2</a> <b><i> * IP Payload Compression Protocol (IPComp) - RFC3173.</i></b>
  <a name="L3" href="source/net/ipv4/ipcomp.c#L3">3</a> <b><i> *</i></b>
  <a name="L4" href="source/net/ipv4/ipcomp.c#L4">4</a> <b><i> * Copyright (c) 2003 James Morris &lt;jmorris@intercode.com.au&gt;</i></b>
  <a name="L5" href="source/net/ipv4/ipcomp.c#L5">5</a> <b><i> *</i></b>
  <a name="L6" href="source/net/ipv4/ipcomp.c#L6">6</a> <b><i> * This program is free software; you can redistribute it and/or modify it</i></b>
  <a name="L7" href="source/net/ipv4/ipcomp.c#L7">7</a> <b><i> * under the terms of the GNU General Public License as published by the Free</i></b>
  <a name="L8" href="source/net/ipv4/ipcomp.c#L8">8</a> <b><i> * Software Foundation; either version 2 of the License, or (at your option)</i></b>
  <a name="L9" href="source/net/ipv4/ipcomp.c#L9">9</a> <b><i> * any later version.</i></b>
 <a name="L10" href="source/net/ipv4/ipcomp.c#L10">10</a> <b><i> *</i></b>
 <a name="L11" href="source/net/ipv4/ipcomp.c#L11">11</a> <b><i> * Todo:</i></b>
 <a name="L12" href="source/net/ipv4/ipcomp.c#L12">12</a> <b><i> *   - Tunable compression parameters.</i></b>
 <a name="L13" href="source/net/ipv4/ipcomp.c#L13">13</a> <b><i> *   - Compression stats.</i></b>
 <a name="L14" href="source/net/ipv4/ipcomp.c#L14">14</a> <b><i> *   - Adaptive compression.</i></b>
 <a name="L15" href="source/net/ipv4/ipcomp.c#L15">15</a> <b><i> */</i></b>
 <a name="L16" href="source/net/ipv4/ipcomp.c#L16">16</a> #include &lt;linux/module.h&gt;
 <a name="L17" href="source/net/ipv4/ipcomp.c#L17">17</a> #include &lt;linux/err.h&gt;
 <a name="L18" href="source/net/ipv4/ipcomp.c#L18">18</a> #include &lt;linux/rtnetlink.h&gt;
 <a name="L19" href="source/net/ipv4/ipcomp.c#L19">19</a> #include &lt;net/ip.h&gt;
 <a name="L20" href="source/net/ipv4/ipcomp.c#L20">20</a> #include &lt;net/xfrm.h&gt;
 <a name="L21" href="source/net/ipv4/ipcomp.c#L21">21</a> #include &lt;net/icmp.h&gt;
 <a name="L22" href="source/net/ipv4/ipcomp.c#L22">22</a> #include &lt;net/ipcomp.h&gt;
 <a name="L23" href="source/net/ipv4/ipcomp.c#L23">23</a> #include &lt;net/protocol.h&gt;
 <a name="L24" href="source/net/ipv4/ipcomp.c#L24">24</a> #include &lt;net/sock.h&gt;
 <a name="L25" href="source/net/ipv4/ipcomp.c#L25">25</a> 
 <a name="L26" href="source/net/ipv4/ipcomp.c#L26">26</a> static int <a href="ident?i=ipcomp4_err">ipcomp4_err</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, <a href="ident?i=u32">u32</a> <a href="ident?i=info">info</a>)
 <a name="L27" href="source/net/ipv4/ipcomp.c#L27">27</a> {
 <a name="L28" href="source/net/ipv4/ipcomp.c#L28">28</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=dev">dev</a>);
 <a name="L29" href="source/net/ipv4/ipcomp.c#L29">29</a>         <a href="ident?i=__be32">__be32</a> <a href="ident?i=spi">spi</a>;
 <a name="L30" href="source/net/ipv4/ipcomp.c#L30">30</a>         const struct <a href="ident?i=iphdr">iphdr</a> *iph = (const struct <a href="ident?i=iphdr">iphdr</a> *)<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=data">data</a>;
 <a name="L31" href="source/net/ipv4/ipcomp.c#L31">31</a>         struct <a href="ident?i=ip_comp_hdr">ip_comp_hdr</a> *ipch = (struct <a href="ident?i=ip_comp_hdr">ip_comp_hdr</a> *)(<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=data">data</a>+(iph-&gt;ihl&lt;&lt;2));
 <a name="L32" href="source/net/ipv4/ipcomp.c#L32">32</a>         struct <a href="ident?i=xfrm_state">xfrm_state</a> *<a href="ident?i=x">x</a>;
 <a name="L33" href="source/net/ipv4/ipcomp.c#L33">33</a> 
 <a name="L34" href="source/net/ipv4/ipcomp.c#L34">34</a>         switch (<a href="ident?i=icmp_hdr">icmp_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=type">type</a>) {
 <a name="L35" href="source/net/ipv4/ipcomp.c#L35">35</a>         case <a href="ident?i=ICMP_DEST_UNREACH">ICMP_DEST_UNREACH</a>:
 <a name="L36" href="source/net/ipv4/ipcomp.c#L36">36</a>                 if (<a href="ident?i=icmp_hdr">icmp_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=code">code</a> != <a href="ident?i=ICMP_FRAG_NEEDED">ICMP_FRAG_NEEDED</a>)
 <a name="L37" href="source/net/ipv4/ipcomp.c#L37">37</a>                         return 0;
 <a name="L38" href="source/net/ipv4/ipcomp.c#L38">38</a>         case <a href="ident?i=ICMP_REDIRECT">ICMP_REDIRECT</a>:
 <a name="L39" href="source/net/ipv4/ipcomp.c#L39">39</a>                 break;
 <a name="L40" href="source/net/ipv4/ipcomp.c#L40">40</a>         default:
 <a name="L41" href="source/net/ipv4/ipcomp.c#L41">41</a>                 return 0;
 <a name="L42" href="source/net/ipv4/ipcomp.c#L42">42</a>         }
 <a name="L43" href="source/net/ipv4/ipcomp.c#L43">43</a> 
 <a name="L44" href="source/net/ipv4/ipcomp.c#L44">44</a>         <a href="ident?i=spi">spi</a> = <a href="ident?i=htonl">htonl</a>(<a href="ident?i=ntohs">ntohs</a>(ipch-&gt;cpi));
 <a name="L45" href="source/net/ipv4/ipcomp.c#L45">45</a>         <a href="ident?i=x">x</a> = <a href="ident?i=xfrm_state_lookup">xfrm_state_lookup</a>(<a href="ident?i=net">net</a>, <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=mark">mark</a>, (const <a href="ident?i=xfrm_address_t">xfrm_address_t</a> *)&amp;iph-&gt;<a href="ident?i=daddr">daddr</a>,
 <a name="L46" href="source/net/ipv4/ipcomp.c#L46">46</a>                               <a href="ident?i=spi">spi</a>, <a href="ident?i=IPPROTO_COMP">IPPROTO_COMP</a>, <a href="ident?i=AF_INET">AF_INET</a>);
 <a name="L47" href="source/net/ipv4/ipcomp.c#L47">47</a>         if (!<a href="ident?i=x">x</a>)
 <a name="L48" href="source/net/ipv4/ipcomp.c#L48">48</a>                 return 0;
 <a name="L49" href="source/net/ipv4/ipcomp.c#L49">49</a> 
 <a name="L50" href="source/net/ipv4/ipcomp.c#L50">50</a>         if (<a href="ident?i=icmp_hdr">icmp_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=type">type</a> == <a href="ident?i=ICMP_DEST_UNREACH">ICMP_DEST_UNREACH</a>)
 <a name="L51" href="source/net/ipv4/ipcomp.c#L51">51</a>                 <a href="ident?i=ipv4_update_pmtu">ipv4_update_pmtu</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=net">net</a>, <a href="ident?i=info">info</a>, 0, 0, <a href="ident?i=IPPROTO_COMP">IPPROTO_COMP</a>, 0);
 <a name="L52" href="source/net/ipv4/ipcomp.c#L52">52</a>         else
 <a name="L53" href="source/net/ipv4/ipcomp.c#L53">53</a>                 <a href="ident?i=ipv4_redirect">ipv4_redirect</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=net">net</a>, 0, 0, <a href="ident?i=IPPROTO_COMP">IPPROTO_COMP</a>, 0);
 <a name="L54" href="source/net/ipv4/ipcomp.c#L54">54</a>         <a href="ident?i=xfrm_state_put">xfrm_state_put</a>(<a href="ident?i=x">x</a>);
 <a name="L55" href="source/net/ipv4/ipcomp.c#L55">55</a> 
 <a name="L56" href="source/net/ipv4/ipcomp.c#L56">56</a>         return 0;
 <a name="L57" href="source/net/ipv4/ipcomp.c#L57">57</a> }
 <a name="L58" href="source/net/ipv4/ipcomp.c#L58">58</a> 
 <a name="L59" href="source/net/ipv4/ipcomp.c#L59">59</a> <b><i>/* We always hold one tunnel user reference to indicate a tunnel */</i></b>
 <a name="L60" href="source/net/ipv4/ipcomp.c#L60">60</a> static struct <a href="ident?i=xfrm_state">xfrm_state</a> *<a href="ident?i=ipcomp_tunnel_create">ipcomp_tunnel_create</a>(struct <a href="ident?i=xfrm_state">xfrm_state</a> *<a href="ident?i=x">x</a>)
 <a name="L61" href="source/net/ipv4/ipcomp.c#L61">61</a> {
 <a name="L62" href="source/net/ipv4/ipcomp.c#L62">62</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=xs_net">xs_net</a>(<a href="ident?i=x">x</a>);
 <a name="L63" href="source/net/ipv4/ipcomp.c#L63">63</a>         struct <a href="ident?i=xfrm_state">xfrm_state</a> *<a href="ident?i=t">t</a>;
 <a name="L64" href="source/net/ipv4/ipcomp.c#L64">64</a> 
 <a name="L65" href="source/net/ipv4/ipcomp.c#L65">65</a>         <a href="ident?i=t">t</a> = <a href="ident?i=xfrm_state_alloc">xfrm_state_alloc</a>(<a href="ident?i=net">net</a>);
 <a name="L66" href="source/net/ipv4/ipcomp.c#L66">66</a>         if (!<a href="ident?i=t">t</a>)
 <a name="L67" href="source/net/ipv4/ipcomp.c#L67">67</a>                 goto <a href="ident?i=out">out</a>;
 <a name="L68" href="source/net/ipv4/ipcomp.c#L68">68</a> 
 <a name="L69" href="source/net/ipv4/ipcomp.c#L69">69</a>         <a href="ident?i=t">t</a>-&gt;<a href="ident?i=id">id</a>.<a href="ident?i=proto">proto</a> = <a href="ident?i=IPPROTO_IPIP">IPPROTO_IPIP</a>;
 <a name="L70" href="source/net/ipv4/ipcomp.c#L70">70</a>         <a href="ident?i=t">t</a>-&gt;<a href="ident?i=id">id</a>.<a href="ident?i=spi">spi</a> = <a href="ident?i=x">x</a>-&gt;props.<a href="ident?i=saddr">saddr</a>.<a href="ident?i=a4">a4</a>;
 <a name="L71" href="source/net/ipv4/ipcomp.c#L71">71</a>         <a href="ident?i=t">t</a>-&gt;<a href="ident?i=id">id</a>.<a href="ident?i=daddr">daddr</a>.<a href="ident?i=a4">a4</a> = <a href="ident?i=x">x</a>-&gt;<a href="ident?i=id">id</a>.<a href="ident?i=daddr">daddr</a>.<a href="ident?i=a4">a4</a>;
 <a name="L72" href="source/net/ipv4/ipcomp.c#L72">72</a>         <a href="ident?i=memcpy">memcpy</a>(&amp;<a href="ident?i=t">t</a>-&gt;sel, &amp;<a href="ident?i=x">x</a>-&gt;sel, sizeof(<a href="ident?i=t">t</a>-&gt;sel));
 <a name="L73" href="source/net/ipv4/ipcomp.c#L73">73</a>         <a href="ident?i=t">t</a>-&gt;props.<a href="ident?i=family">family</a> = <a href="ident?i=AF_INET">AF_INET</a>;
 <a name="L74" href="source/net/ipv4/ipcomp.c#L74">74</a>         <a href="ident?i=t">t</a>-&gt;props.<a href="ident?i=mode">mode</a> = <a href="ident?i=x">x</a>-&gt;props.<a href="ident?i=mode">mode</a>;
 <a name="L75" href="source/net/ipv4/ipcomp.c#L75">75</a>         <a href="ident?i=t">t</a>-&gt;props.<a href="ident?i=saddr">saddr</a>.<a href="ident?i=a4">a4</a> = <a href="ident?i=x">x</a>-&gt;props.<a href="ident?i=saddr">saddr</a>.<a href="ident?i=a4">a4</a>;
 <a name="L76" href="source/net/ipv4/ipcomp.c#L76">76</a>         <a href="ident?i=t">t</a>-&gt;props.<a href="ident?i=flags">flags</a> = <a href="ident?i=x">x</a>-&gt;props.<a href="ident?i=flags">flags</a>;
 <a name="L77" href="source/net/ipv4/ipcomp.c#L77">77</a>         <a href="ident?i=t">t</a>-&gt;props.extra_flags = <a href="ident?i=x">x</a>-&gt;props.extra_flags;
 <a name="L78" href="source/net/ipv4/ipcomp.c#L78">78</a>         <a href="ident?i=memcpy">memcpy</a>(&amp;<a href="ident?i=t">t</a>-&gt;<a href="ident?i=mark">mark</a>, &amp;<a href="ident?i=x">x</a>-&gt;<a href="ident?i=mark">mark</a>, sizeof(<a href="ident?i=t">t</a>-&gt;<a href="ident?i=mark">mark</a>));
 <a name="L79" href="source/net/ipv4/ipcomp.c#L79">79</a> 
 <a name="L80" href="source/net/ipv4/ipcomp.c#L80">80</a>         if (<a href="ident?i=xfrm_init_state">xfrm_init_state</a>(<a href="ident?i=t">t</a>))
 <a name="L81" href="source/net/ipv4/ipcomp.c#L81">81</a>                 goto <a href="ident?i=error">error</a>;
 <a name="L82" href="source/net/ipv4/ipcomp.c#L82">82</a> 
 <a name="L83" href="source/net/ipv4/ipcomp.c#L83">83</a>         <a href="ident?i=atomic_set">atomic_set</a>(&amp;<a href="ident?i=t">t</a>-&gt;tunnel_users, 1);
 <a name="L84" href="source/net/ipv4/ipcomp.c#L84">84</a> <a href="ident?i=out">out</a>:
 <a name="L85" href="source/net/ipv4/ipcomp.c#L85">85</a>         return <a href="ident?i=t">t</a>;
 <a name="L86" href="source/net/ipv4/ipcomp.c#L86">86</a> 
 <a name="L87" href="source/net/ipv4/ipcomp.c#L87">87</a> <a href="ident?i=error">error</a>:
 <a name="L88" href="source/net/ipv4/ipcomp.c#L88">88</a>         <a href="ident?i=t">t</a>-&gt;km.<a href="ident?i=state">state</a> = XFRM_STATE_DEAD;
 <a name="L89" href="source/net/ipv4/ipcomp.c#L89">89</a>         <a href="ident?i=xfrm_state_put">xfrm_state_put</a>(<a href="ident?i=t">t</a>);
 <a name="L90" href="source/net/ipv4/ipcomp.c#L90">90</a>         <a href="ident?i=t">t</a> = <a href="ident?i=NULL">NULL</a>;
 <a name="L91" href="source/net/ipv4/ipcomp.c#L91">91</a>         goto <a href="ident?i=out">out</a>;
 <a name="L92" href="source/net/ipv4/ipcomp.c#L92">92</a> }
 <a name="L93" href="source/net/ipv4/ipcomp.c#L93">93</a> 
 <a name="L94" href="source/net/ipv4/ipcomp.c#L94">94</a> <b><i>/*</i></b>
 <a name="L95" href="source/net/ipv4/ipcomp.c#L95">95</a> <b><i> * Must be protected by xfrm_cfg_mutex.  State and tunnel user references are</i></b>
 <a name="L96" href="source/net/ipv4/ipcomp.c#L96">96</a> <b><i> * always incremented on success.</i></b>
 <a name="L97" href="source/net/ipv4/ipcomp.c#L97">97</a> <b><i> */</i></b>
 <a name="L98" href="source/net/ipv4/ipcomp.c#L98">98</a> static int <a href="ident?i=ipcomp_tunnel_attach">ipcomp_tunnel_attach</a>(struct <a href="ident?i=xfrm_state">xfrm_state</a> *<a href="ident?i=x">x</a>)
 <a name="L99" href="source/net/ipv4/ipcomp.c#L99">99</a> {
<a name="L100" href="source/net/ipv4/ipcomp.c#L100">100</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=xs_net">xs_net</a>(<a href="ident?i=x">x</a>);
<a name="L101" href="source/net/ipv4/ipcomp.c#L101">101</a>         int <a href="ident?i=err">err</a> = 0;
<a name="L102" href="source/net/ipv4/ipcomp.c#L102">102</a>         struct <a href="ident?i=xfrm_state">xfrm_state</a> *<a href="ident?i=t">t</a>;
<a name="L103" href="source/net/ipv4/ipcomp.c#L103">103</a>         <a href="ident?i=u32">u32</a> <a href="ident?i=mark">mark</a> = <a href="ident?i=x">x</a>-&gt;<a href="ident?i=mark">mark</a>.<a href="ident?i=v">v</a> &amp; <a href="ident?i=x">x</a>-&gt;<a href="ident?i=mark">mark</a>.<a href="ident?i=m">m</a>;
<a name="L104" href="source/net/ipv4/ipcomp.c#L104">104</a> 
<a name="L105" href="source/net/ipv4/ipcomp.c#L105">105</a>         <a href="ident?i=t">t</a> = <a href="ident?i=xfrm_state_lookup">xfrm_state_lookup</a>(<a href="ident?i=net">net</a>, <a href="ident?i=mark">mark</a>, (<a href="ident?i=xfrm_address_t">xfrm_address_t</a> *)&amp;<a href="ident?i=x">x</a>-&gt;<a href="ident?i=id">id</a>.<a href="ident?i=daddr">daddr</a>.<a href="ident?i=a4">a4</a>,
<a name="L106" href="source/net/ipv4/ipcomp.c#L106">106</a>                               <a href="ident?i=x">x</a>-&gt;props.<a href="ident?i=saddr">saddr</a>.<a href="ident?i=a4">a4</a>, <a href="ident?i=IPPROTO_IPIP">IPPROTO_IPIP</a>, <a href="ident?i=AF_INET">AF_INET</a>);
<a name="L107" href="source/net/ipv4/ipcomp.c#L107">107</a>         if (!<a href="ident?i=t">t</a>) {
<a name="L108" href="source/net/ipv4/ipcomp.c#L108">108</a>                 <a href="ident?i=t">t</a> = <a href="ident?i=ipcomp_tunnel_create">ipcomp_tunnel_create</a>(<a href="ident?i=x">x</a>);
<a name="L109" href="source/net/ipv4/ipcomp.c#L109">109</a>                 if (!<a href="ident?i=t">t</a>) {
<a name="L110" href="source/net/ipv4/ipcomp.c#L110">110</a>                         <a href="ident?i=err">err</a> = -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L111" href="source/net/ipv4/ipcomp.c#L111">111</a>                         goto <a href="ident?i=out">out</a>;
<a name="L112" href="source/net/ipv4/ipcomp.c#L112">112</a>                 }
<a name="L113" href="source/net/ipv4/ipcomp.c#L113">113</a>                 <a href="ident?i=xfrm_state_insert">xfrm_state_insert</a>(<a href="ident?i=t">t</a>);
<a name="L114" href="source/net/ipv4/ipcomp.c#L114">114</a>                 <a href="ident?i=xfrm_state_hold">xfrm_state_hold</a>(<a href="ident?i=t">t</a>);
<a name="L115" href="source/net/ipv4/ipcomp.c#L115">115</a>         }
<a name="L116" href="source/net/ipv4/ipcomp.c#L116">116</a>         <a href="ident?i=x">x</a>-&gt;tunnel = <a href="ident?i=t">t</a>;
<a name="L117" href="source/net/ipv4/ipcomp.c#L117">117</a>         <a href="ident?i=atomic_inc">atomic_inc</a>(&amp;<a href="ident?i=t">t</a>-&gt;tunnel_users);
<a name="L118" href="source/net/ipv4/ipcomp.c#L118">118</a> <a href="ident?i=out">out</a>:
<a name="L119" href="source/net/ipv4/ipcomp.c#L119">119</a>         return <a href="ident?i=err">err</a>;
<a name="L120" href="source/net/ipv4/ipcomp.c#L120">120</a> }
<a name="L121" href="source/net/ipv4/ipcomp.c#L121">121</a> 
<a name="L122" href="source/net/ipv4/ipcomp.c#L122">122</a> static int <a href="ident?i=ipcomp4_init_state">ipcomp4_init_state</a>(struct <a href="ident?i=xfrm_state">xfrm_state</a> *<a href="ident?i=x">x</a>)
<a name="L123" href="source/net/ipv4/ipcomp.c#L123">123</a> {
<a name="L124" href="source/net/ipv4/ipcomp.c#L124">124</a>         int <a href="ident?i=err">err</a> = -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L125" href="source/net/ipv4/ipcomp.c#L125">125</a> 
<a name="L126" href="source/net/ipv4/ipcomp.c#L126">126</a>         <a href="ident?i=x">x</a>-&gt;props.<a href="ident?i=header_len">header_len</a> = 0;
<a name="L127" href="source/net/ipv4/ipcomp.c#L127">127</a>         switch (<a href="ident?i=x">x</a>-&gt;props.<a href="ident?i=mode">mode</a>) {
<a name="L128" href="source/net/ipv4/ipcomp.c#L128">128</a>         case <a href="ident?i=XFRM_MODE_TRANSPORT">XFRM_MODE_TRANSPORT</a>:
<a name="L129" href="source/net/ipv4/ipcomp.c#L129">129</a>                 break;
<a name="L130" href="source/net/ipv4/ipcomp.c#L130">130</a>         case <a href="ident?i=XFRM_MODE_TUNNEL">XFRM_MODE_TUNNEL</a>:
<a name="L131" href="source/net/ipv4/ipcomp.c#L131">131</a>                 <a href="ident?i=x">x</a>-&gt;props.<a href="ident?i=header_len">header_len</a> += sizeof(struct <a href="ident?i=iphdr">iphdr</a>);
<a name="L132" href="source/net/ipv4/ipcomp.c#L132">132</a>                 break;
<a name="L133" href="source/net/ipv4/ipcomp.c#L133">133</a>         default:
<a name="L134" href="source/net/ipv4/ipcomp.c#L134">134</a>                 goto <a href="ident?i=out">out</a>;
<a name="L135" href="source/net/ipv4/ipcomp.c#L135">135</a>         }
<a name="L136" href="source/net/ipv4/ipcomp.c#L136">136</a> 
<a name="L137" href="source/net/ipv4/ipcomp.c#L137">137</a>         <a href="ident?i=err">err</a> = <a href="ident?i=ipcomp_init_state">ipcomp_init_state</a>(<a href="ident?i=x">x</a>);
<a name="L138" href="source/net/ipv4/ipcomp.c#L138">138</a>         if (<a href="ident?i=err">err</a>)
<a name="L139" href="source/net/ipv4/ipcomp.c#L139">139</a>                 goto <a href="ident?i=out">out</a>;
<a name="L140" href="source/net/ipv4/ipcomp.c#L140">140</a> 
<a name="L141" href="source/net/ipv4/ipcomp.c#L141">141</a>         if (<a href="ident?i=x">x</a>-&gt;props.<a href="ident?i=mode">mode</a> == <a href="ident?i=XFRM_MODE_TUNNEL">XFRM_MODE_TUNNEL</a>) {
<a name="L142" href="source/net/ipv4/ipcomp.c#L142">142</a>                 <a href="ident?i=err">err</a> = <a href="ident?i=ipcomp_tunnel_attach">ipcomp_tunnel_attach</a>(<a href="ident?i=x">x</a>);
<a name="L143" href="source/net/ipv4/ipcomp.c#L143">143</a>                 if (<a href="ident?i=err">err</a>)
<a name="L144" href="source/net/ipv4/ipcomp.c#L144">144</a>                         goto <a href="ident?i=out">out</a>;
<a name="L145" href="source/net/ipv4/ipcomp.c#L145">145</a>         }
<a name="L146" href="source/net/ipv4/ipcomp.c#L146">146</a> 
<a name="L147" href="source/net/ipv4/ipcomp.c#L147">147</a>         <a href="ident?i=err">err</a> = 0;
<a name="L148" href="source/net/ipv4/ipcomp.c#L148">148</a> <a href="ident?i=out">out</a>:
<a name="L149" href="source/net/ipv4/ipcomp.c#L149">149</a>         return <a href="ident?i=err">err</a>;
<a name="L150" href="source/net/ipv4/ipcomp.c#L150">150</a> }
<a name="L151" href="source/net/ipv4/ipcomp.c#L151">151</a> 
<a name="L152" href="source/net/ipv4/ipcomp.c#L152">152</a> static int <a href="ident?i=ipcomp4_rcv_cb">ipcomp4_rcv_cb</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, int <a href="ident?i=err">err</a>)
<a name="L153" href="source/net/ipv4/ipcomp.c#L153">153</a> {
<a name="L154" href="source/net/ipv4/ipcomp.c#L154">154</a>         return 0;
<a name="L155" href="source/net/ipv4/ipcomp.c#L155">155</a> }
<a name="L156" href="source/net/ipv4/ipcomp.c#L156">156</a> 
<a name="L157" href="source/net/ipv4/ipcomp.c#L157">157</a> static const struct <a href="ident?i=xfrm_type">xfrm_type</a> <a href="ident?i=ipcomp_type">ipcomp_type</a> = {
<a name="L158" href="source/net/ipv4/ipcomp.c#L158">158</a>         .description    = <i>"IPCOMP4"</i>,
<a name="L159" href="source/net/ipv4/ipcomp.c#L159">159</a>         .owner          = <a href="ident?i=THIS_MODULE">THIS_MODULE</a>,
<a name="L160" href="source/net/ipv4/ipcomp.c#L160">160</a>         .<a href="ident?i=proto">proto</a>          = <a href="ident?i=IPPROTO_COMP">IPPROTO_COMP</a>,
<a name="L161" href="source/net/ipv4/ipcomp.c#L161">161</a>         .<a href="ident?i=init_state">init_state</a>     = <a href="ident?i=ipcomp4_init_state">ipcomp4_init_state</a>,
<a name="L162" href="source/net/ipv4/ipcomp.c#L162">162</a>         .destructor     = <a href="ident?i=ipcomp_destroy">ipcomp_destroy</a>,
<a name="L163" href="source/net/ipv4/ipcomp.c#L163">163</a>         .<a href="ident?i=input">input</a>          = <a href="ident?i=ipcomp_input">ipcomp_input</a>,
<a name="L164" href="source/net/ipv4/ipcomp.c#L164">164</a>         .<a href="ident?i=output">output</a>         = <a href="ident?i=ipcomp_output">ipcomp_output</a>
<a name="L165" href="source/net/ipv4/ipcomp.c#L165">165</a> };
<a name="L166" href="source/net/ipv4/ipcomp.c#L166">166</a> 
<a name="L167" href="source/net/ipv4/ipcomp.c#L167">167</a> static struct <a href="ident?i=xfrm4_protocol">xfrm4_protocol</a> <a href="ident?i=ipcomp4_protocol">ipcomp4_protocol</a> = {
<a name="L168" href="source/net/ipv4/ipcomp.c#L168">168</a>         .<a href="ident?i=handler">handler</a>        =       <a href="ident?i=xfrm4_rcv">xfrm4_rcv</a>,
<a name="L169" href="source/net/ipv4/ipcomp.c#L169">169</a>         .<a href="ident?i=input_handler">input_handler</a>  =       <a href="ident?i=xfrm_input">xfrm_input</a>,
<a name="L170" href="source/net/ipv4/ipcomp.c#L170">170</a>         .cb_handler     =       <a href="ident?i=ipcomp4_rcv_cb">ipcomp4_rcv_cb</a>,
<a name="L171" href="source/net/ipv4/ipcomp.c#L171">171</a>         .<a href="ident?i=err_handler">err_handler</a>    =       <a href="ident?i=ipcomp4_err">ipcomp4_err</a>,
<a name="L172" href="source/net/ipv4/ipcomp.c#L172">172</a>         .<a href="ident?i=priority">priority</a>       =       0,
<a name="L173" href="source/net/ipv4/ipcomp.c#L173">173</a> };
<a name="L174" href="source/net/ipv4/ipcomp.c#L174">174</a> 
<a name="L175" href="source/net/ipv4/ipcomp.c#L175">175</a> static int <a href="ident?i=__init">__init</a> <a href="ident?i=ipcomp4_init">ipcomp4_init</a>(void)
<a name="L176" href="source/net/ipv4/ipcomp.c#L176">176</a> {
<a name="L177" href="source/net/ipv4/ipcomp.c#L177">177</a>         if (<a href="ident?i=xfrm_register_type">xfrm_register_type</a>(&amp;<a href="ident?i=ipcomp_type">ipcomp_type</a>, <a href="ident?i=AF_INET">AF_INET</a>) &lt; 0) {
<a name="L178" href="source/net/ipv4/ipcomp.c#L178">178</a>                 <a href="ident?i=pr_info">pr_info</a>(<i>"%s: can't add xfrm type\n"</i>, <a href="ident?i=__func__">__func__</a>);
<a name="L179" href="source/net/ipv4/ipcomp.c#L179">179</a>                 return -<a href="ident?i=EAGAIN">EAGAIN</a>;
<a name="L180" href="source/net/ipv4/ipcomp.c#L180">180</a>         }
<a name="L181" href="source/net/ipv4/ipcomp.c#L181">181</a>         if (<a href="ident?i=xfrm4_protocol_register">xfrm4_protocol_register</a>(&amp;<a href="ident?i=ipcomp4_protocol">ipcomp4_protocol</a>, <a href="ident?i=IPPROTO_COMP">IPPROTO_COMP</a>) &lt; 0) {
<a name="L182" href="source/net/ipv4/ipcomp.c#L182">182</a>                 <a href="ident?i=pr_info">pr_info</a>(<i>"%s: can't add protocol\n"</i>, <a href="ident?i=__func__">__func__</a>);
<a name="L183" href="source/net/ipv4/ipcomp.c#L183">183</a>                 <a href="ident?i=xfrm_unregister_type">xfrm_unregister_type</a>(&amp;<a href="ident?i=ipcomp_type">ipcomp_type</a>, <a href="ident?i=AF_INET">AF_INET</a>);
<a name="L184" href="source/net/ipv4/ipcomp.c#L184">184</a>                 return -<a href="ident?i=EAGAIN">EAGAIN</a>;
<a name="L185" href="source/net/ipv4/ipcomp.c#L185">185</a>         }
<a name="L186" href="source/net/ipv4/ipcomp.c#L186">186</a>         return 0;
<a name="L187" href="source/net/ipv4/ipcomp.c#L187">187</a> }
<a name="L188" href="source/net/ipv4/ipcomp.c#L188">188</a> 
<a name="L189" href="source/net/ipv4/ipcomp.c#L189">189</a> static void <a href="ident?i=__exit">__exit</a> <a href="ident?i=ipcomp4_fini">ipcomp4_fini</a>(void)
<a name="L190" href="source/net/ipv4/ipcomp.c#L190">190</a> {
<a name="L191" href="source/net/ipv4/ipcomp.c#L191">191</a>         if (<a href="ident?i=xfrm4_protocol_deregister">xfrm4_protocol_deregister</a>(&amp;<a href="ident?i=ipcomp4_protocol">ipcomp4_protocol</a>, <a href="ident?i=IPPROTO_COMP">IPPROTO_COMP</a>) &lt; 0)
<a name="L192" href="source/net/ipv4/ipcomp.c#L192">192</a>                 <a href="ident?i=pr_info">pr_info</a>(<i>"%s: can't remove protocol\n"</i>, <a href="ident?i=__func__">__func__</a>);
<a name="L193" href="source/net/ipv4/ipcomp.c#L193">193</a>         if (<a href="ident?i=xfrm_unregister_type">xfrm_unregister_type</a>(&amp;<a href="ident?i=ipcomp_type">ipcomp_type</a>, <a href="ident?i=AF_INET">AF_INET</a>) &lt; 0)
<a name="L194" href="source/net/ipv4/ipcomp.c#L194">194</a>                 <a href="ident?i=pr_info">pr_info</a>(<i>"%s: can't remove xfrm type\n"</i>, <a href="ident?i=__func__">__func__</a>);
<a name="L195" href="source/net/ipv4/ipcomp.c#L195">195</a> }
<a name="L196" href="source/net/ipv4/ipcomp.c#L196">196</a> 
<a name="L197" href="source/net/ipv4/ipcomp.c#L197">197</a> <a href="ident?i=module_init">module_init</a>(<a href="ident?i=ipcomp4_init">ipcomp4_init</a>);
<a name="L198" href="source/net/ipv4/ipcomp.c#L198">198</a> <a href="ident?i=module_exit">module_exit</a>(<a href="ident?i=ipcomp4_fini">ipcomp4_fini</a>);
<a name="L199" href="source/net/ipv4/ipcomp.c#L199">199</a> 
<a name="L200" href="source/net/ipv4/ipcomp.c#L200">200</a> <a href="ident?i=MODULE_LICENSE">MODULE_LICENSE</a>(<i>"GPL"</i>);
<a name="L201" href="source/net/ipv4/ipcomp.c#L201">201</a> <a href="ident?i=MODULE_DESCRIPTION">MODULE_DESCRIPTION</a>(<i>"IP Payload Compression Protocol (IPComp/IPv4) - RFC3173"</i>);
<a name="L202" href="source/net/ipv4/ipcomp.c#L202">202</a> <a href="ident?i=MODULE_AUTHOR">MODULE_AUTHOR</a>(<i>"James Morris &lt;jmorris@intercode.com.au&gt;"</i>);
<a name="L203" href="source/net/ipv4/ipcomp.c#L203">203</a> 
<a name="L204" href="source/net/ipv4/ipcomp.c#L204">204</a> <a href="ident?i=MODULE_ALIAS_XFRM_TYPE">MODULE_ALIAS_XFRM_TYPE</a>(<a href="ident?i=AF_INET">AF_INET</a>, <a href="ident?i=XFRM_PROTO_COMP">XFRM_PROTO_COMP</a>);
<a name="L205" href="source/net/ipv4/ipcomp.c#L205">205</a> </pre></div><p>
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
