<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title>Linux/net/ipv4/netfilter/nf_log_ipv4.c - Linux Cross Reference - Free Electrons</title>
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
		 &nbsp;&bull;&nbsp;<b><i>source navigation</i></b> &nbsp;&bull;&nbsp;<a href="diff/net/ipv4/netfilter/nf_log_ipv4.c">diff markup</a> &nbsp;&bull;&nbsp;<a href="ident">identifier search</a> &nbsp;&bull;&nbsp;<a href="search">freetext search</a> &nbsp;&bull;&nbsp;
		</p>
	</div>
</div>

<div id="topbar">
  
  <p>Version: &nbsp;<a href="source/net/ipv4/netfilter/nf_log_ipv4.c?v=2.0.40">2.0.40</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_log_ipv4.c?v=2.2.26">2.2.26</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_log_ipv4.c?v=2.4.37">2.4.37</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_log_ipv4.c?v=3.5">3.5</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_log_ipv4.c?v=3.6">3.6</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_log_ipv4.c?v=3.7">3.7</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_log_ipv4.c?v=3.8">3.8</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_log_ipv4.c?v=3.9">3.9</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_log_ipv4.c?v=3.10">3.10</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_log_ipv4.c?v=3.11">3.11</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_log_ipv4.c?v=3.12">3.12</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_log_ipv4.c?v=3.13">3.13</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_log_ipv4.c?v=3.14">3.14</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_log_ipv4.c?v=3.15">3.15</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_log_ipv4.c?v=3.16">3.16</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_log_ipv4.c?v=3.17">3.17</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_log_ipv4.c?v=3.18">3.18</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_log_ipv4.c?v=3.19">3.19</a>&nbsp;<a href="source/net/ipv4/netfilter/nf_log_ipv4.c?v=4.0">4.0</a>&nbsp;<b><i>4.1</i></b></p>
  
</div>

<h1><a href="source/">Linux</a>/<a href="source/net/">net</a>/<a href="source/net/ipv4/">ipv4</a>/<a href="source/net/ipv4/netfilter/">netfilter</a>/<a href="source/net/ipv4/netfilter/nf_log_ipv4.c">nf_log_ipv4.c</a></h1>
<div id="lxrcode"><pre>  <a name="L1" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L1">1</a> <b><i>/* (C) 1999-2001 Paul `Rusty' Russell</i></b>
  <a name="L2" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L2">2</a> <b><i> * (C) 2002-2004 Netfilter Core Team &lt;coreteam@netfilter.org&gt;</i></b>
  <a name="L3" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L3">3</a> <b><i> *</i></b>
  <a name="L4" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L4">4</a> <b><i> * This program is free software; you can redistribute it and/or modify</i></b>
  <a name="L5" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L5">5</a> <b><i> * it under the terms of the GNU General Public License version 2 as</i></b>
  <a name="L6" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L6">6</a> <b><i> * published by the Free Software Foundation.</i></b>
  <a name="L7" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L7">7</a> <b><i> */</i></b>
  <a name="L8" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L8">8</a> 
  <a name="L9" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L9">9</a> #define <a href="ident?i=pr_fmt">pr_fmt</a>(<a href="ident?i=fmt">fmt</a>) KBUILD_MODNAME <i>": "</i> <a href="ident?i=fmt">fmt</a>
 <a name="L10" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L10">10</a> 
 <a name="L11" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L11">11</a> #include &lt;linux/kernel.h&gt;
 <a name="L12" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L12">12</a> #include &lt;linux/module.h&gt;
 <a name="L13" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L13">13</a> #include &lt;linux/spinlock.h&gt;
 <a name="L14" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L14">14</a> #include &lt;linux/skbuff.h&gt;
 <a name="L15" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L15">15</a> #include &lt;linux/if_arp.h&gt;
 <a name="L16" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L16">16</a> #include &lt;linux/ip.h&gt;
 <a name="L17" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L17">17</a> #include &lt;net/ipv6.h&gt;
 <a name="L18" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L18">18</a> #include &lt;net/icmp.h&gt;
 <a name="L19" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L19">19</a> #include &lt;net/udp.h&gt;
 <a name="L20" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L20">20</a> #include &lt;net/tcp.h&gt;
 <a name="L21" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L21">21</a> #include &lt;net/route.h&gt;
 <a name="L22" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L22">22</a> 
 <a name="L23" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L23">23</a> #include &lt;linux/netfilter.h&gt;
 <a name="L24" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L24">24</a> #include &lt;linux/netfilter/xt_LOG.h&gt;
 <a name="L25" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L25">25</a> #include &lt;net/netfilter/nf_log.h&gt;
 <a name="L26" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L26">26</a> 
 <a name="L27" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L27">27</a> static struct <a href="ident?i=nf_loginfo">nf_loginfo</a> <a href="ident?i=default_loginfo">default_loginfo</a> = {
 <a name="L28" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L28">28</a>         .<a href="ident?i=type">type</a>   = NF_LOG_TYPE_LOG,
 <a name="L29" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L29">29</a>         .u = {
 <a name="L30" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L30">30</a>                 .<a href="ident?i=log">log</a> = {
 <a name="L31" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L31">31</a>                         .<a href="ident?i=level">level</a>    = <a href="ident?i=LOGLEVEL_NOTICE">LOGLEVEL_NOTICE</a>,
 <a name="L32" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L32">32</a>                         .logflags = <a href="ident?i=NF_LOG_MASK">NF_LOG_MASK</a>,
 <a name="L33" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L33">33</a>                 },
 <a name="L34" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L34">34</a>         },
 <a name="L35" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L35">35</a> };
 <a name="L36" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L36">36</a> 
 <a name="L37" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L37">37</a> <b><i>/* One level of recursion won't kill us */</i></b>
 <a name="L38" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L38">38</a> static void <a href="ident?i=dump_ipv4_packet">dump_ipv4_packet</a>(struct <a href="ident?i=nf_log_buf">nf_log_buf</a> *<a href="ident?i=m">m</a>,
 <a name="L39" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L39">39</a>                              const struct <a href="ident?i=nf_loginfo">nf_loginfo</a> *<a href="ident?i=info">info</a>,
 <a name="L40" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L40">40</a>                              const struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, unsigned int iphoff)
 <a name="L41" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L41">41</a> {
 <a name="L42" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L42">42</a>         struct <a href="ident?i=iphdr">iphdr</a> _iph;
 <a name="L43" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L43">43</a>         const struct <a href="ident?i=iphdr">iphdr</a> *ih;
 <a name="L44" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L44">44</a>         unsigned int logflags;
 <a name="L45" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L45">45</a> 
 <a name="L46" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L46">46</a>         if (<a href="ident?i=info">info</a>-&gt;<a href="ident?i=type">type</a> == NF_LOG_TYPE_LOG)
 <a name="L47" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L47">47</a>                 logflags = <a href="ident?i=info">info</a>-&gt;u.<a href="ident?i=log">log</a>.logflags;
 <a name="L48" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L48">48</a>         else
 <a name="L49" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L49">49</a>                 logflags = <a href="ident?i=NF_LOG_MASK">NF_LOG_MASK</a>;
 <a name="L50" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L50">50</a> 
 <a name="L51" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L51">51</a>         ih = <a href="ident?i=skb_header_pointer">skb_header_pointer</a>(<a href="ident?i=skb">skb</a>, iphoff, sizeof(_iph), &amp;_iph);
 <a name="L52" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L52">52</a>         if (ih == <a href="ident?i=NULL">NULL</a>) {
 <a name="L53" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L53">53</a>                 <a href="ident?i=nf_log_buf_add">nf_log_buf_add</a>(<a href="ident?i=m">m</a>, <i>"TRUNCATED"</i>);
 <a name="L54" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L54">54</a>                 return;
 <a name="L55" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L55">55</a>         }
 <a name="L56" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L56">56</a> 
 <a name="L57" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L57">57</a>         <b><i>/* Important fields:</i></b>
 <a name="L58" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L58">58</a> <b><i>         * TOS, len, DF/MF, fragment offset, TTL, src, dst, options. */</i></b>
 <a name="L59" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L59">59</a>         <b><i>/* Max length: 40 "SRC=255.255.255.255 DST=255.255.255.255 " */</i></b>
 <a name="L60" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L60">60</a>         <a href="ident?i=nf_log_buf_add">nf_log_buf_add</a>(<a href="ident?i=m">m</a>, <i>"SRC=%pI4 DST=%pI4 "</i>, &amp;ih-&gt;<a href="ident?i=saddr">saddr</a>, &amp;ih-&gt;<a href="ident?i=daddr">daddr</a>);
 <a name="L61" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L61">61</a> 
 <a name="L62" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L62">62</a>         <b><i>/* Max length: 46 "LEN=65535 TOS=0xFF PREC=0xFF TTL=255 ID=65535 " */</i></b>
 <a name="L63" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L63">63</a>         <a href="ident?i=nf_log_buf_add">nf_log_buf_add</a>(<a href="ident?i=m">m</a>, <i>"LEN=%u TOS=0x%02X PREC=0x%02X TTL=%u ID=%u "</i>,
 <a name="L64" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L64">64</a>                        <a href="ident?i=ntohs">ntohs</a>(ih-&gt;tot_len), ih-&gt;tos &amp; <a href="ident?i=IPTOS_TOS_MASK">IPTOS_TOS_MASK</a>,
 <a name="L65" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L65">65</a>                        ih-&gt;tos &amp; <a href="ident?i=IPTOS_PREC_MASK">IPTOS_PREC_MASK</a>, ih-&gt;<a href="ident?i=ttl">ttl</a>, <a href="ident?i=ntohs">ntohs</a>(ih-&gt;<a href="ident?i=id">id</a>));
 <a name="L66" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L66">66</a> 
 <a name="L67" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L67">67</a>         <b><i>/* Max length: 6 "CE DF MF " */</i></b>
 <a name="L68" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L68">68</a>         if (<a href="ident?i=ntohs">ntohs</a>(ih-&gt;frag_off) &amp; <a href="ident?i=IP_CE">IP_CE</a>)
 <a name="L69" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L69">69</a>                 <a href="ident?i=nf_log_buf_add">nf_log_buf_add</a>(<a href="ident?i=m">m</a>, <i>"CE "</i>);
 <a name="L70" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L70">70</a>         if (<a href="ident?i=ntohs">ntohs</a>(ih-&gt;frag_off) &amp; <a href="ident?i=IP_DF">IP_DF</a>)
 <a name="L71" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L71">71</a>                 <a href="ident?i=nf_log_buf_add">nf_log_buf_add</a>(<a href="ident?i=m">m</a>, <i>"DF "</i>);
 <a name="L72" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L72">72</a>         if (<a href="ident?i=ntohs">ntohs</a>(ih-&gt;frag_off) &amp; <a href="ident?i=IP_MF">IP_MF</a>)
 <a name="L73" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L73">73</a>                 <a href="ident?i=nf_log_buf_add">nf_log_buf_add</a>(<a href="ident?i=m">m</a>, <i>"MF "</i>);
 <a name="L74" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L74">74</a> 
 <a name="L75" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L75">75</a>         <b><i>/* Max length: 11 "FRAG:65535 " */</i></b>
 <a name="L76" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L76">76</a>         if (<a href="ident?i=ntohs">ntohs</a>(ih-&gt;frag_off) &amp; <a href="ident?i=IP_OFFSET">IP_OFFSET</a>)
 <a name="L77" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L77">77</a>                 <a href="ident?i=nf_log_buf_add">nf_log_buf_add</a>(<a href="ident?i=m">m</a>, <i>"FRAG:%u "</i>, <a href="ident?i=ntohs">ntohs</a>(ih-&gt;frag_off) &amp; <a href="ident?i=IP_OFFSET">IP_OFFSET</a>);
 <a name="L78" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L78">78</a> 
 <a name="L79" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L79">79</a>         if ((logflags &amp; <a href="ident?i=XT_LOG_IPOPT">XT_LOG_IPOPT</a>) &amp;&amp;
 <a name="L80" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L80">80</a>             ih-&gt;ihl * 4 &gt; sizeof(struct <a href="ident?i=iphdr">iphdr</a>)) {
 <a name="L81" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L81">81</a>                 const unsigned char *<a href="ident?i=op">op</a>;
 <a name="L82" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L82">82</a>                 unsigned char _opt[4 * 15 - sizeof(struct <a href="ident?i=iphdr">iphdr</a>)];
 <a name="L83" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L83">83</a>                 unsigned int <a href="ident?i=i">i</a>, optsize;
 <a name="L84" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L84">84</a> 
 <a name="L85" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L85">85</a>                 optsize = ih-&gt;ihl * 4 - sizeof(struct <a href="ident?i=iphdr">iphdr</a>);
 <a name="L86" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L86">86</a>                 <a href="ident?i=op">op</a> = <a href="ident?i=skb_header_pointer">skb_header_pointer</a>(<a href="ident?i=skb">skb</a>, iphoff+sizeof(_iph),
 <a name="L87" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L87">87</a>                                         optsize, _opt);
 <a name="L88" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L88">88</a>                 if (<a href="ident?i=op">op</a> == <a href="ident?i=NULL">NULL</a>) {
 <a name="L89" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L89">89</a>                         <a href="ident?i=nf_log_buf_add">nf_log_buf_add</a>(<a href="ident?i=m">m</a>, <i>"TRUNCATED"</i>);
 <a name="L90" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L90">90</a>                         return;
 <a name="L91" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L91">91</a>                 }
 <a name="L92" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L92">92</a> 
 <a name="L93" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L93">93</a>                 <b><i>/* Max length: 127 "OPT (" 15*4*2chars ") " */</i></b>
 <a name="L94" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L94">94</a>                 <a href="ident?i=nf_log_buf_add">nf_log_buf_add</a>(<a href="ident?i=m">m</a>, <i>"OPT ("</i>);
 <a name="L95" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L95">95</a>                 for (<a href="ident?i=i">i</a> = 0; <a href="ident?i=i">i</a> &lt; optsize; <a href="ident?i=i">i</a>++)
 <a name="L96" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L96">96</a>                         <a href="ident?i=nf_log_buf_add">nf_log_buf_add</a>(<a href="ident?i=m">m</a>, <i>"%02X"</i>, <a href="ident?i=op">op</a>[<a href="ident?i=i">i</a>]);
 <a name="L97" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L97">97</a>                 <a href="ident?i=nf_log_buf_add">nf_log_buf_add</a>(<a href="ident?i=m">m</a>, <i>") "</i>);
 <a name="L98" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L98">98</a>         }
 <a name="L99" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L99">99</a> 
<a name="L100" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L100">100</a>         switch (ih-&gt;<a href="ident?i=protocol">protocol</a>) {
<a name="L101" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L101">101</a>         case <a href="ident?i=IPPROTO_TCP">IPPROTO_TCP</a>:
<a name="L102" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L102">102</a>                 if (<a href="ident?i=nf_log_dump_tcp_header">nf_log_dump_tcp_header</a>(<a href="ident?i=m">m</a>, <a href="ident?i=skb">skb</a>, ih-&gt;<a href="ident?i=protocol">protocol</a>,
<a name="L103" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L103">103</a>                                            <a href="ident?i=ntohs">ntohs</a>(ih-&gt;frag_off) &amp; <a href="ident?i=IP_OFFSET">IP_OFFSET</a>,
<a name="L104" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L104">104</a>                                            iphoff+ih-&gt;ihl*4, logflags))
<a name="L105" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L105">105</a>                         return;
<a name="L106" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L106">106</a>                 break;
<a name="L107" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L107">107</a>         case <a href="ident?i=IPPROTO_UDP">IPPROTO_UDP</a>:
<a name="L108" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L108">108</a>         case <a href="ident?i=IPPROTO_UDPLITE">IPPROTO_UDPLITE</a>:
<a name="L109" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L109">109</a>                 if (<a href="ident?i=nf_log_dump_udp_header">nf_log_dump_udp_header</a>(<a href="ident?i=m">m</a>, <a href="ident?i=skb">skb</a>, ih-&gt;<a href="ident?i=protocol">protocol</a>,
<a name="L110" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L110">110</a>                                            <a href="ident?i=ntohs">ntohs</a>(ih-&gt;frag_off) &amp; <a href="ident?i=IP_OFFSET">IP_OFFSET</a>,
<a name="L111" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L111">111</a>                                            iphoff+ih-&gt;ihl*4))
<a name="L112" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L112">112</a>                         return;
<a name="L113" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L113">113</a>                 break;
<a name="L114" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L114">114</a>         case <a href="ident?i=IPPROTO_ICMP">IPPROTO_ICMP</a>: {
<a name="L115" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L115">115</a>                 struct <a href="ident?i=icmphdr">icmphdr</a> _icmph;
<a name="L116" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L116">116</a>                 const struct <a href="ident?i=icmphdr">icmphdr</a> *ich;
<a name="L117" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L117">117</a>                 static const <a href="ident?i=size_t">size_t</a> required_len[<a href="ident?i=NR_ICMP_TYPES">NR_ICMP_TYPES</a>+1]
<a name="L118" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L118">118</a>                         = { [<a href="ident?i=ICMP_ECHOREPLY">ICMP_ECHOREPLY</a>] = 4,
<a name="L119" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L119">119</a>                             [<a href="ident?i=ICMP_DEST_UNREACH">ICMP_DEST_UNREACH</a>]
<a name="L120" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L120">120</a>                             = 8 + sizeof(struct <a href="ident?i=iphdr">iphdr</a>),
<a name="L121" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L121">121</a>                             [<a href="ident?i=ICMP_SOURCE_QUENCH">ICMP_SOURCE_QUENCH</a>]
<a name="L122" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L122">122</a>                             = 8 + sizeof(struct <a href="ident?i=iphdr">iphdr</a>),
<a name="L123" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L123">123</a>                             [<a href="ident?i=ICMP_REDIRECT">ICMP_REDIRECT</a>]
<a name="L124" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L124">124</a>                             = 8 + sizeof(struct <a href="ident?i=iphdr">iphdr</a>),
<a name="L125" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L125">125</a>                             [<a href="ident?i=ICMP_ECHO">ICMP_ECHO</a>] = 4,
<a name="L126" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L126">126</a>                             [<a href="ident?i=ICMP_TIME_EXCEEDED">ICMP_TIME_EXCEEDED</a>]
<a name="L127" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L127">127</a>                             = 8 + sizeof(struct <a href="ident?i=iphdr">iphdr</a>),
<a name="L128" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L128">128</a>                             [<a href="ident?i=ICMP_PARAMETERPROB">ICMP_PARAMETERPROB</a>]
<a name="L129" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L129">129</a>                             = 8 + sizeof(struct <a href="ident?i=iphdr">iphdr</a>),
<a name="L130" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L130">130</a>                             [<a href="ident?i=ICMP_TIMESTAMP">ICMP_TIMESTAMP</a>] = 20,
<a name="L131" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L131">131</a>                             [<a href="ident?i=ICMP_TIMESTAMPREPLY">ICMP_TIMESTAMPREPLY</a>] = 20,
<a name="L132" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L132">132</a>                             [<a href="ident?i=ICMP_ADDRESS">ICMP_ADDRESS</a>] = 12,
<a name="L133" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L133">133</a>                             [<a href="ident?i=ICMP_ADDRESSREPLY">ICMP_ADDRESSREPLY</a>] = 12 };
<a name="L134" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L134">134</a> 
<a name="L135" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L135">135</a>                 <b><i>/* Max length: 11 "PROTO=ICMP " */</i></b>
<a name="L136" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L136">136</a>                 <a href="ident?i=nf_log_buf_add">nf_log_buf_add</a>(<a href="ident?i=m">m</a>, <i>"PROTO=ICMP "</i>);
<a name="L137" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L137">137</a> 
<a name="L138" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L138">138</a>                 if (<a href="ident?i=ntohs">ntohs</a>(ih-&gt;frag_off) &amp; <a href="ident?i=IP_OFFSET">IP_OFFSET</a>)
<a name="L139" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L139">139</a>                         break;
<a name="L140" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L140">140</a> 
<a name="L141" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L141">141</a>                 <b><i>/* Max length: 25 "INCOMPLETE [65535 bytes] " */</i></b>
<a name="L142" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L142">142</a>                 ich = <a href="ident?i=skb_header_pointer">skb_header_pointer</a>(<a href="ident?i=skb">skb</a>, iphoff + ih-&gt;ihl * 4,
<a name="L143" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L143">143</a>                                          sizeof(_icmph), &amp;_icmph);
<a name="L144" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L144">144</a>                 if (ich == <a href="ident?i=NULL">NULL</a>) {
<a name="L145" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L145">145</a>                         <a href="ident?i=nf_log_buf_add">nf_log_buf_add</a>(<a href="ident?i=m">m</a>, <i>"INCOMPLETE [%u bytes] "</i>,
<a name="L146" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L146">146</a>                                        <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a> - iphoff - ih-&gt;ihl*4);
<a name="L147" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L147">147</a>                         break;
<a name="L148" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L148">148</a>                 }
<a name="L149" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L149">149</a> 
<a name="L150" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L150">150</a>                 <b><i>/* Max length: 18 "TYPE=255 CODE=255 " */</i></b>
<a name="L151" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L151">151</a>                 <a href="ident?i=nf_log_buf_add">nf_log_buf_add</a>(<a href="ident?i=m">m</a>, <i>"TYPE=%u CODE=%u "</i>, ich-&gt;<a href="ident?i=type">type</a>, ich-&gt;<a href="ident?i=code">code</a>);
<a name="L152" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L152">152</a> 
<a name="L153" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L153">153</a>                 <b><i>/* Max length: 25 "INCOMPLETE [65535 bytes] " */</i></b>
<a name="L154" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L154">154</a>                 if (ich-&gt;<a href="ident?i=type">type</a> &lt;= <a href="ident?i=NR_ICMP_TYPES">NR_ICMP_TYPES</a> &amp;&amp;
<a name="L155" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L155">155</a>                     required_len[ich-&gt;<a href="ident?i=type">type</a>] &amp;&amp;
<a name="L156" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L156">156</a>                     <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a>-iphoff-ih-&gt;ihl*4 &lt; required_len[ich-&gt;<a href="ident?i=type">type</a>]) {
<a name="L157" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L157">157</a>                         <a href="ident?i=nf_log_buf_add">nf_log_buf_add</a>(<a href="ident?i=m">m</a>, <i>"INCOMPLETE [%u bytes] "</i>,
<a name="L158" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L158">158</a>                                        <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a> - iphoff - ih-&gt;ihl*4);
<a name="L159" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L159">159</a>                         break;
<a name="L160" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L160">160</a>                 }
<a name="L161" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L161">161</a> 
<a name="L162" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L162">162</a>                 switch (ich-&gt;<a href="ident?i=type">type</a>) {
<a name="L163" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L163">163</a>                 case <a href="ident?i=ICMP_ECHOREPLY">ICMP_ECHOREPLY</a>:
<a name="L164" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L164">164</a>                 case <a href="ident?i=ICMP_ECHO">ICMP_ECHO</a>:
<a name="L165" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L165">165</a>                         <b><i>/* Max length: 19 "ID=65535 SEQ=65535 " */</i></b>
<a name="L166" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L166">166</a>                         <a href="ident?i=nf_log_buf_add">nf_log_buf_add</a>(<a href="ident?i=m">m</a>, <i>"ID=%u SEQ=%u "</i>,
<a name="L167" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L167">167</a>                                        <a href="ident?i=ntohs">ntohs</a>(ich-&gt;un.<a href="ident?i=echo">echo</a>.<a href="ident?i=id">id</a>),
<a name="L168" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L168">168</a>                                        <a href="ident?i=ntohs">ntohs</a>(ich-&gt;un.<a href="ident?i=echo">echo</a>.<a href="ident?i=sequence">sequence</a>));
<a name="L169" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L169">169</a>                         break;
<a name="L170" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L170">170</a> 
<a name="L171" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L171">171</a>                 case <a href="ident?i=ICMP_PARAMETERPROB">ICMP_PARAMETERPROB</a>:
<a name="L172" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L172">172</a>                         <b><i>/* Max length: 14 "PARAMETER=255 " */</i></b>
<a name="L173" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L173">173</a>                         <a href="ident?i=nf_log_buf_add">nf_log_buf_add</a>(<a href="ident?i=m">m</a>, <i>"PARAMETER=%u "</i>,
<a name="L174" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L174">174</a>                                        <a href="ident?i=ntohl">ntohl</a>(ich-&gt;un.gateway) &gt;&gt; 24);
<a name="L175" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L175">175</a>                         break;
<a name="L176" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L176">176</a>                 case <a href="ident?i=ICMP_REDIRECT">ICMP_REDIRECT</a>:
<a name="L177" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L177">177</a>                         <b><i>/* Max length: 24 "GATEWAY=255.255.255.255 " */</i></b>
<a name="L178" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L178">178</a>                         <a href="ident?i=nf_log_buf_add">nf_log_buf_add</a>(<a href="ident?i=m">m</a>, <i>"GATEWAY=%pI4 "</i>, &amp;ich-&gt;un.gateway);
<a name="L179" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L179">179</a>                         <b><i>/* Fall through */</i></b>
<a name="L180" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L180">180</a>                 case <a href="ident?i=ICMP_DEST_UNREACH">ICMP_DEST_UNREACH</a>:
<a name="L181" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L181">181</a>                 case <a href="ident?i=ICMP_SOURCE_QUENCH">ICMP_SOURCE_QUENCH</a>:
<a name="L182" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L182">182</a>                 case <a href="ident?i=ICMP_TIME_EXCEEDED">ICMP_TIME_EXCEEDED</a>:
<a name="L183" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L183">183</a>                         <b><i>/* Max length: 3+maxlen */</i></b>
<a name="L184" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L184">184</a>                         if (!iphoff) { <b><i>/* Only recurse once. */</i></b>
<a name="L185" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L185">185</a>                                 <a href="ident?i=nf_log_buf_add">nf_log_buf_add</a>(<a href="ident?i=m">m</a>, <i>"["</i>);
<a name="L186" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L186">186</a>                                 <a href="ident?i=dump_ipv4_packet">dump_ipv4_packet</a>(<a href="ident?i=m">m</a>, <a href="ident?i=info">info</a>, <a href="ident?i=skb">skb</a>,
<a name="L187" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L187">187</a>                                             iphoff + ih-&gt;ihl*4+sizeof(_icmph));
<a name="L188" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L188">188</a>                                 <a href="ident?i=nf_log_buf_add">nf_log_buf_add</a>(<a href="ident?i=m">m</a>, <i>"] "</i>);
<a name="L189" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L189">189</a>                         }
<a name="L190" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L190">190</a> 
<a name="L191" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L191">191</a>                         <b><i>/* Max length: 10 "MTU=65535 " */</i></b>
<a name="L192" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L192">192</a>                         if (ich-&gt;<a href="ident?i=type">type</a> == <a href="ident?i=ICMP_DEST_UNREACH">ICMP_DEST_UNREACH</a> &amp;&amp;
<a name="L193" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L193">193</a>                             ich-&gt;<a href="ident?i=code">code</a> == <a href="ident?i=ICMP_FRAG_NEEDED">ICMP_FRAG_NEEDED</a>) {
<a name="L194" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L194">194</a>                                 <a href="ident?i=nf_log_buf_add">nf_log_buf_add</a>(<a href="ident?i=m">m</a>, <i>"MTU=%u "</i>,
<a name="L195" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L195">195</a>                                                <a href="ident?i=ntohs">ntohs</a>(ich-&gt;un.<a href="ident?i=frag">frag</a>.<a href="ident?i=mtu">mtu</a>));
<a name="L196" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L196">196</a>                         }
<a name="L197" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L197">197</a>                 }
<a name="L198" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L198">198</a>                 break;
<a name="L199" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L199">199</a>         }
<a name="L200" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L200">200</a>         <b><i>/* Max Length */</i></b>
<a name="L201" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L201">201</a>         case <a href="ident?i=IPPROTO_AH">IPPROTO_AH</a>: {
<a name="L202" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L202">202</a>                 struct <a href="ident?i=ip_auth_hdr">ip_auth_hdr</a> _ahdr;
<a name="L203" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L203">203</a>                 const struct <a href="ident?i=ip_auth_hdr">ip_auth_hdr</a> *ah;
<a name="L204" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L204">204</a> 
<a name="L205" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L205">205</a>                 if (<a href="ident?i=ntohs">ntohs</a>(ih-&gt;frag_off) &amp; <a href="ident?i=IP_OFFSET">IP_OFFSET</a>)
<a name="L206" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L206">206</a>                         break;
<a name="L207" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L207">207</a> 
<a name="L208" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L208">208</a>                 <b><i>/* Max length: 9 "PROTO=AH " */</i></b>
<a name="L209" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L209">209</a>                 <a href="ident?i=nf_log_buf_add">nf_log_buf_add</a>(<a href="ident?i=m">m</a>, <i>"PROTO=AH "</i>);
<a name="L210" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L210">210</a> 
<a name="L211" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L211">211</a>                 <b><i>/* Max length: 25 "INCOMPLETE [65535 bytes] " */</i></b>
<a name="L212" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L212">212</a>                 ah = <a href="ident?i=skb_header_pointer">skb_header_pointer</a>(<a href="ident?i=skb">skb</a>, iphoff+ih-&gt;ihl*4,
<a name="L213" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L213">213</a>                                         sizeof(_ahdr), &amp;_ahdr);
<a name="L214" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L214">214</a>                 if (ah == <a href="ident?i=NULL">NULL</a>) {
<a name="L215" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L215">215</a>                         <a href="ident?i=nf_log_buf_add">nf_log_buf_add</a>(<a href="ident?i=m">m</a>, <i>"INCOMPLETE [%u bytes] "</i>,
<a name="L216" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L216">216</a>                                        <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a> - iphoff - ih-&gt;ihl*4);
<a name="L217" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L217">217</a>                         break;
<a name="L218" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L218">218</a>                 }
<a name="L219" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L219">219</a> 
<a name="L220" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L220">220</a>                 <b><i>/* Length: 15 "SPI=0xF1234567 " */</i></b>
<a name="L221" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L221">221</a>                 <a href="ident?i=nf_log_buf_add">nf_log_buf_add</a>(<a href="ident?i=m">m</a>, <i>"SPI=0x%x "</i>, <a href="ident?i=ntohl">ntohl</a>(ah-&gt;<a href="ident?i=spi">spi</a>));
<a name="L222" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L222">222</a>                 break;
<a name="L223" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L223">223</a>         }
<a name="L224" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L224">224</a>         case <a href="ident?i=IPPROTO_ESP">IPPROTO_ESP</a>: {
<a name="L225" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L225">225</a>                 struct <a href="ident?i=ip_esp_hdr">ip_esp_hdr</a> _esph;
<a name="L226" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L226">226</a>                 const struct <a href="ident?i=ip_esp_hdr">ip_esp_hdr</a> *eh;
<a name="L227" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L227">227</a> 
<a name="L228" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L228">228</a>                 <b><i>/* Max length: 10 "PROTO=ESP " */</i></b>
<a name="L229" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L229">229</a>                 <a href="ident?i=nf_log_buf_add">nf_log_buf_add</a>(<a href="ident?i=m">m</a>, <i>"PROTO=ESP "</i>);
<a name="L230" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L230">230</a> 
<a name="L231" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L231">231</a>                 if (<a href="ident?i=ntohs">ntohs</a>(ih-&gt;frag_off) &amp; <a href="ident?i=IP_OFFSET">IP_OFFSET</a>)
<a name="L232" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L232">232</a>                         break;
<a name="L233" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L233">233</a> 
<a name="L234" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L234">234</a>                 <b><i>/* Max length: 25 "INCOMPLETE [65535 bytes] " */</i></b>
<a name="L235" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L235">235</a>                 eh = <a href="ident?i=skb_header_pointer">skb_header_pointer</a>(<a href="ident?i=skb">skb</a>, iphoff+ih-&gt;ihl*4,
<a name="L236" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L236">236</a>                                         sizeof(_esph), &amp;_esph);
<a name="L237" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L237">237</a>                 if (eh == <a href="ident?i=NULL">NULL</a>) {
<a name="L238" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L238">238</a>                         <a href="ident?i=nf_log_buf_add">nf_log_buf_add</a>(<a href="ident?i=m">m</a>, <i>"INCOMPLETE [%u bytes] "</i>,
<a name="L239" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L239">239</a>                                        <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a> - iphoff - ih-&gt;ihl*4);
<a name="L240" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L240">240</a>                         break;
<a name="L241" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L241">241</a>                 }
<a name="L242" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L242">242</a> 
<a name="L243" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L243">243</a>                 <b><i>/* Length: 15 "SPI=0xF1234567 " */</i></b>
<a name="L244" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L244">244</a>                 <a href="ident?i=nf_log_buf_add">nf_log_buf_add</a>(<a href="ident?i=m">m</a>, <i>"SPI=0x%x "</i>, <a href="ident?i=ntohl">ntohl</a>(eh-&gt;<a href="ident?i=spi">spi</a>));
<a name="L245" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L245">245</a>                 break;
<a name="L246" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L246">246</a>         }
<a name="L247" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L247">247</a>         <b><i>/* Max length: 10 "PROTO 255 " */</i></b>
<a name="L248" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L248">248</a>         default:
<a name="L249" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L249">249</a>                 <a href="ident?i=nf_log_buf_add">nf_log_buf_add</a>(<a href="ident?i=m">m</a>, <i>"PROTO=%u "</i>, ih-&gt;<a href="ident?i=protocol">protocol</a>);
<a name="L250" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L250">250</a>         }
<a name="L251" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L251">251</a> 
<a name="L252" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L252">252</a>         <b><i>/* Max length: 15 "UID=4294967295 " */</i></b>
<a name="L253" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L253">253</a>         if ((logflags &amp; <a href="ident?i=XT_LOG_UID">XT_LOG_UID</a>) &amp;&amp; !iphoff)
<a name="L254" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L254">254</a>                 <a href="ident?i=nf_log_dump_sk_uid_gid">nf_log_dump_sk_uid_gid</a>(<a href="ident?i=m">m</a>, <a href="ident?i=skb">skb</a>-&gt;sk);
<a name="L255" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L255">255</a> 
<a name="L256" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L256">256</a>         <b><i>/* Max length: 16 "MARK=0xFFFFFFFF " */</i></b>
<a name="L257" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L257">257</a>         if (!iphoff &amp;&amp; <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=mark">mark</a>)
<a name="L258" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L258">258</a>                 <a href="ident?i=nf_log_buf_add">nf_log_buf_add</a>(<a href="ident?i=m">m</a>, <i>"MARK=0x%x "</i>, <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=mark">mark</a>);
<a name="L259" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L259">259</a> 
<a name="L260" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L260">260</a>         <b><i>/* Proto    Max log string length */</i></b>
<a name="L261" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L261">261</a>         <b><i>/* IP:      40+46+6+11+127 = 230 */</i></b>
<a name="L262" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L262">262</a>         <b><i>/* TCP:     10+max(25,20+30+13+9+32+11+127) = 252 */</i></b>
<a name="L263" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L263">263</a>         <b><i>/* UDP:     10+max(25,20) = 35 */</i></b>
<a name="L264" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L264">264</a>         <b><i>/* UDPLITE: 14+max(25,20) = 39 */</i></b>
<a name="L265" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L265">265</a>         <b><i>/* ICMP:    11+max(25, 18+25+max(19,14,24+3+n+10,3+n+10)) = 91+n */</i></b>
<a name="L266" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L266">266</a>         <b><i>/* ESP:     10+max(25)+15 = 50 */</i></b>
<a name="L267" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L267">267</a>         <b><i>/* AH:      9+max(25)+15 = 49 */</i></b>
<a name="L268" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L268">268</a>         <b><i>/* unknown: 10 */</i></b>
<a name="L269" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L269">269</a> 
<a name="L270" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L270">270</a>         <b><i>/* (ICMP allows recursion one level deep) */</i></b>
<a name="L271" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L271">271</a>         <b><i>/* maxlen =  IP + ICMP +  IP + max(TCP,UDP,ICMP,unknown) */</i></b>
<a name="L272" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L272">272</a>         <b><i>/* maxlen = 230+   91  + 230 + 252 = 803 */</i></b>
<a name="L273" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L273">273</a> }
<a name="L274" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L274">274</a> 
<a name="L275" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L275">275</a> static void <a href="ident?i=dump_ipv4_mac_header">dump_ipv4_mac_header</a>(struct <a href="ident?i=nf_log_buf">nf_log_buf</a> *<a href="ident?i=m">m</a>,
<a name="L276" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L276">276</a>                             const struct <a href="ident?i=nf_loginfo">nf_loginfo</a> *<a href="ident?i=info">info</a>,
<a name="L277" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L277">277</a>                             const struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L278" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L278">278</a> {
<a name="L279" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L279">279</a>         struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a> = <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=dev">dev</a>;
<a name="L280" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L280">280</a>         unsigned int logflags = 0;
<a name="L281" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L281">281</a> 
<a name="L282" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L282">282</a>         if (<a href="ident?i=info">info</a>-&gt;<a href="ident?i=type">type</a> == NF_LOG_TYPE_LOG)
<a name="L283" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L283">283</a>                 logflags = <a href="ident?i=info">info</a>-&gt;u.<a href="ident?i=log">log</a>.logflags;
<a name="L284" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L284">284</a> 
<a name="L285" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L285">285</a>         if (!(logflags &amp; <a href="ident?i=XT_LOG_MACDECODE">XT_LOG_MACDECODE</a>))
<a name="L286" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L286">286</a>                 goto fallback;
<a name="L287" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L287">287</a> 
<a name="L288" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L288">288</a>         switch (<a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=type">type</a>) {
<a name="L289" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L289">289</a>         case <a href="ident?i=ARPHRD_ETHER">ARPHRD_ETHER</a>:
<a name="L290" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L290">290</a>                 <a href="ident?i=nf_log_buf_add">nf_log_buf_add</a>(<a href="ident?i=m">m</a>, <i>"MACSRC=%pM MACDST=%pM MACPROTO=%04x "</i>,
<a name="L291" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L291">291</a>                                <a href="ident?i=eth_hdr">eth_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;h_source, <a href="ident?i=eth_hdr">eth_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;h_dest,
<a name="L292" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L292">292</a>                                <a href="ident?i=ntohs">ntohs</a>(<a href="ident?i=eth_hdr">eth_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;h_proto));
<a name="L293" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L293">293</a>                 return;
<a name="L294" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L294">294</a>         default:
<a name="L295" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L295">295</a>                 break;
<a name="L296" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L296">296</a>         }
<a name="L297" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L297">297</a> 
<a name="L298" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L298">298</a> fallback:
<a name="L299" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L299">299</a>         <a href="ident?i=nf_log_buf_add">nf_log_buf_add</a>(<a href="ident?i=m">m</a>, <i>"MAC="</i>);
<a name="L300" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L300">300</a>         if (<a href="ident?i=dev">dev</a>-&gt;hard_header_len &amp;&amp;
<a name="L301" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L301">301</a>             <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=mac_header">mac_header</a> != <a href="ident?i=skb">skb</a>-&gt;network_header) {
<a name="L302" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L302">302</a>                 const unsigned char *<a href="ident?i=p">p</a> = <a href="ident?i=skb_mac_header">skb_mac_header</a>(<a href="ident?i=skb">skb</a>);
<a name="L303" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L303">303</a>                 unsigned int <a href="ident?i=i">i</a>;
<a name="L304" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L304">304</a> 
<a name="L305" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L305">305</a>                 <a href="ident?i=nf_log_buf_add">nf_log_buf_add</a>(<a href="ident?i=m">m</a>, <i>"%02x"</i>, *<a href="ident?i=p">p</a>++);
<a name="L306" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L306">306</a>                 for (<a href="ident?i=i">i</a> = 1; <a href="ident?i=i">i</a> &lt; <a href="ident?i=dev">dev</a>-&gt;hard_header_len; <a href="ident?i=i">i</a>++, <a href="ident?i=p">p</a>++)
<a name="L307" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L307">307</a>                         <a href="ident?i=nf_log_buf_add">nf_log_buf_add</a>(<a href="ident?i=m">m</a>, <i>":%02x"</i>, *<a href="ident?i=p">p</a>);
<a name="L308" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L308">308</a>         }
<a name="L309" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L309">309</a>         <a href="ident?i=nf_log_buf_add">nf_log_buf_add</a>(<a href="ident?i=m">m</a>, <i>" "</i>);
<a name="L310" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L310">310</a> }
<a name="L311" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L311">311</a> 
<a name="L312" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L312">312</a> static void <a href="ident?i=nf_log_ip_packet">nf_log_ip_packet</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>, <a href="ident?i=u_int8_t">u_int8_t</a> <a href="ident?i=pf">pf</a>,
<a name="L313" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L313">313</a>                              unsigned int hooknum, const struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
<a name="L314" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L314">314</a>                              const struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=in">in</a>,
<a name="L315" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L315">315</a>                              const struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=out">out</a>,
<a name="L316" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L316">316</a>                              const struct <a href="ident?i=nf_loginfo">nf_loginfo</a> *loginfo,
<a name="L317" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L317">317</a>                              const char *<a href="ident?i=prefix">prefix</a>)
<a name="L318" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L318">318</a> {
<a name="L319" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L319">319</a>         struct <a href="ident?i=nf_log_buf">nf_log_buf</a> *<a href="ident?i=m">m</a>;
<a name="L320" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L320">320</a> 
<a name="L321" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L321">321</a>         <b><i>/* FIXME: Disabled from containers until syslog ns is supported */</i></b>
<a name="L322" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L322">322</a>         if (!<a href="ident?i=net_eq">net_eq</a>(<a href="ident?i=net">net</a>, &amp;<a href="ident?i=init_net">init_net</a>))
<a name="L323" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L323">323</a>                 return;
<a name="L324" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L324">324</a> 
<a name="L325" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L325">325</a>         <a href="ident?i=m">m</a> = <a href="ident?i=nf_log_buf_open">nf_log_buf_open</a>();
<a name="L326" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L326">326</a> 
<a name="L327" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L327">327</a>         if (!loginfo)
<a name="L328" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L328">328</a>                 loginfo = &amp;<a href="ident?i=default_loginfo">default_loginfo</a>;
<a name="L329" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L329">329</a> 
<a name="L330" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L330">330</a>         <a href="ident?i=nf_log_dump_packet_common">nf_log_dump_packet_common</a>(<a href="ident?i=m">m</a>, <a href="ident?i=pf">pf</a>, hooknum, <a href="ident?i=skb">skb</a>, <a href="ident?i=in">in</a>,
<a name="L331" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L331">331</a>                                   <a href="ident?i=out">out</a>, loginfo, <a href="ident?i=prefix">prefix</a>);
<a name="L332" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L332">332</a> 
<a name="L333" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L333">333</a>         if (<a href="ident?i=in">in</a> != <a href="ident?i=NULL">NULL</a>)
<a name="L334" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L334">334</a>                 <a href="ident?i=dump_ipv4_mac_header">dump_ipv4_mac_header</a>(<a href="ident?i=m">m</a>, loginfo, <a href="ident?i=skb">skb</a>);
<a name="L335" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L335">335</a> 
<a name="L336" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L336">336</a>         <a href="ident?i=dump_ipv4_packet">dump_ipv4_packet</a>(<a href="ident?i=m">m</a>, loginfo, <a href="ident?i=skb">skb</a>, 0);
<a name="L337" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L337">337</a> 
<a name="L338" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L338">338</a>         <a href="ident?i=nf_log_buf_close">nf_log_buf_close</a>(<a href="ident?i=m">m</a>);
<a name="L339" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L339">339</a> }
<a name="L340" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L340">340</a> 
<a name="L341" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L341">341</a> static struct <a href="ident?i=nf_logger">nf_logger</a> nf_ip_logger <a href="ident?i=__read_mostly">__read_mostly</a> = {
<a name="L342" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L342">342</a>         .<a href="ident?i=name">name</a>           = <i>"nf_log_ipv4"</i>,
<a name="L343" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L343">343</a>         .<a href="ident?i=type">type</a>           = NF_LOG_TYPE_LOG,
<a name="L344" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L344">344</a>         .logfn          = <a href="ident?i=nf_log_ip_packet">nf_log_ip_packet</a>,
<a name="L345" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L345">345</a>         .<a href="ident?i=me">me</a>             = <a href="ident?i=THIS_MODULE">THIS_MODULE</a>,
<a name="L346" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L346">346</a> };
<a name="L347" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L347">347</a> 
<a name="L348" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L348">348</a> static int <a href="ident?i=__net_init">__net_init</a> <a href="ident?i=nf_log_ipv4_net_init">nf_log_ipv4_net_init</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>)
<a name="L349" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L349">349</a> {
<a name="L350" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L350">350</a>         <a href="ident?i=nf_log_set">nf_log_set</a>(<a href="ident?i=net">net</a>, NFPROTO_IPV4, &amp;nf_ip_logger);
<a name="L351" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L351">351</a>         return 0;
<a name="L352" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L352">352</a> }
<a name="L353" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L353">353</a> 
<a name="L354" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L354">354</a> static void <a href="ident?i=__net_exit">__net_exit</a> <a href="ident?i=nf_log_ipv4_net_exit">nf_log_ipv4_net_exit</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>)
<a name="L355" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L355">355</a> {
<a name="L356" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L356">356</a>         <a href="ident?i=nf_log_unset">nf_log_unset</a>(<a href="ident?i=net">net</a>, &amp;nf_ip_logger);
<a name="L357" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L357">357</a> }
<a name="L358" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L358">358</a> 
<a name="L359" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L359">359</a> static struct <a href="ident?i=pernet_operations">pernet_operations</a> <a href="ident?i=nf_log_ipv4_net_ops">nf_log_ipv4_net_ops</a> = {
<a name="L360" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L360">360</a>         .<a href="ident?i=init">init</a> = <a href="ident?i=nf_log_ipv4_net_init">nf_log_ipv4_net_init</a>,
<a name="L361" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L361">361</a>         .<a href="ident?i=exit">exit</a> = <a href="ident?i=nf_log_ipv4_net_exit">nf_log_ipv4_net_exit</a>,
<a name="L362" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L362">362</a> };
<a name="L363" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L363">363</a> 
<a name="L364" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L364">364</a> static int <a href="ident?i=__init">__init</a> <a href="ident?i=nf_log_ipv4_init">nf_log_ipv4_init</a>(void)
<a name="L365" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L365">365</a> {
<a name="L366" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L366">366</a>         int <a href="ident?i=ret">ret</a>;
<a name="L367" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L367">367</a> 
<a name="L368" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L368">368</a>         <a href="ident?i=ret">ret</a> = <a href="ident?i=register_pernet_subsys">register_pernet_subsys</a>(&amp;<a href="ident?i=nf_log_ipv4_net_ops">nf_log_ipv4_net_ops</a>);
<a name="L369" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L369">369</a>         if (<a href="ident?i=ret">ret</a> &lt; 0)
<a name="L370" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L370">370</a>                 return <a href="ident?i=ret">ret</a>;
<a name="L371" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L371">371</a> 
<a name="L372" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L372">372</a>         <a href="ident?i=ret">ret</a> = <a href="ident?i=nf_log_register">nf_log_register</a>(NFPROTO_IPV4, &amp;nf_ip_logger);
<a name="L373" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L373">373</a>         if (<a href="ident?i=ret">ret</a> &lt; 0) {
<a name="L374" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L374">374</a>                 <a href="ident?i=pr_err">pr_err</a>(<i>"failed to register logger\n"</i>);
<a name="L375" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L375">375</a>                 goto err1;
<a name="L376" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L376">376</a>         }
<a name="L377" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L377">377</a> 
<a name="L378" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L378">378</a>         return 0;
<a name="L379" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L379">379</a> 
<a name="L380" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L380">380</a> err1:
<a name="L381" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L381">381</a>         <a href="ident?i=unregister_pernet_subsys">unregister_pernet_subsys</a>(&amp;<a href="ident?i=nf_log_ipv4_net_ops">nf_log_ipv4_net_ops</a>);
<a name="L382" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L382">382</a>         return <a href="ident?i=ret">ret</a>;
<a name="L383" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L383">383</a> }
<a name="L384" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L384">384</a> 
<a name="L385" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L385">385</a> static void <a href="ident?i=__exit">__exit</a> <a href="ident?i=nf_log_ipv4_exit">nf_log_ipv4_exit</a>(void)
<a name="L386" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L386">386</a> {
<a name="L387" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L387">387</a>         <a href="ident?i=unregister_pernet_subsys">unregister_pernet_subsys</a>(&amp;<a href="ident?i=nf_log_ipv4_net_ops">nf_log_ipv4_net_ops</a>);
<a name="L388" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L388">388</a>         <a href="ident?i=nf_log_unregister">nf_log_unregister</a>(&amp;nf_ip_logger);
<a name="L389" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L389">389</a> }
<a name="L390" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L390">390</a> 
<a name="L391" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L391">391</a> <a href="ident?i=module_init">module_init</a>(<a href="ident?i=nf_log_ipv4_init">nf_log_ipv4_init</a>);
<a name="L392" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L392">392</a> <a href="ident?i=module_exit">module_exit</a>(<a href="ident?i=nf_log_ipv4_exit">nf_log_ipv4_exit</a>);
<a name="L393" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L393">393</a> 
<a name="L394" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L394">394</a> <a href="ident?i=MODULE_AUTHOR">MODULE_AUTHOR</a>(<i>"Netfilter Core Team &lt;coreteam@netfilter.org&gt;"</i>);
<a name="L395" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L395">395</a> <a href="ident?i=MODULE_DESCRIPTION">MODULE_DESCRIPTION</a>(<i>"Netfilter IPv4 packet logging"</i>);
<a name="L396" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L396">396</a> <a href="ident?i=MODULE_LICENSE">MODULE_LICENSE</a>(<i>"GPL"</i>);
<a name="L397" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L397">397</a> <a href="ident?i=MODULE_ALIAS_NF_LOGGER">MODULE_ALIAS_NF_LOGGER</a>(<a href="ident?i=AF_INET">AF_INET</a>, 0);
<a name="L398" href="source/net/ipv4/netfilter/nf_log_ipv4.c#L398">398</a> </pre></div><p>
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
