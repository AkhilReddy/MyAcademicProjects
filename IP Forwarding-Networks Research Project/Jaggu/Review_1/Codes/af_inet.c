<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title>Linux/net/ipv4/af_inet.c - Linux Cross Reference - Free Electrons</title>
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
		 &nbsp;&bull;&nbsp;<b><i>source navigation</i></b> &nbsp;&bull;&nbsp;<a href="diff/net/ipv4/af_inet.c">diff markup</a> &nbsp;&bull;&nbsp;<a href="ident">identifier search</a> &nbsp;&bull;&nbsp;<a href="search">freetext search</a> &nbsp;&bull;&nbsp;
		</p>
	</div>
</div>

<div id="topbar">
  
  <p>Version: &nbsp;<a href="source/net/ipv4/af_inet.c?v=2.0.40">2.0.40</a>&nbsp;<a href="source/net/ipv4/af_inet.c?v=2.2.26">2.2.26</a>&nbsp;<a href="source/net/ipv4/af_inet.c?v=2.4.37">2.4.37</a>&nbsp;<a href="source/net/ipv4/af_inet.c?v=3.5">3.5</a>&nbsp;<a href="source/net/ipv4/af_inet.c?v=3.6">3.6</a>&nbsp;<a href="source/net/ipv4/af_inet.c?v=3.7">3.7</a>&nbsp;<a href="source/net/ipv4/af_inet.c?v=3.8">3.8</a>&nbsp;<a href="source/net/ipv4/af_inet.c?v=3.9">3.9</a>&nbsp;<a href="source/net/ipv4/af_inet.c?v=3.10">3.10</a>&nbsp;<a href="source/net/ipv4/af_inet.c?v=3.11">3.11</a>&nbsp;<a href="source/net/ipv4/af_inet.c?v=3.12">3.12</a>&nbsp;<a href="source/net/ipv4/af_inet.c?v=3.13">3.13</a>&nbsp;<a href="source/net/ipv4/af_inet.c?v=3.14">3.14</a>&nbsp;<a href="source/net/ipv4/af_inet.c?v=3.15">3.15</a>&nbsp;<a href="source/net/ipv4/af_inet.c?v=3.16">3.16</a>&nbsp;<a href="source/net/ipv4/af_inet.c?v=3.17">3.17</a>&nbsp;<a href="source/net/ipv4/af_inet.c?v=3.18">3.18</a>&nbsp;<a href="source/net/ipv4/af_inet.c?v=3.19">3.19</a>&nbsp;<a href="source/net/ipv4/af_inet.c?v=4.0">4.0</a>&nbsp;<b><i>4.1</i></b></p>
  
</div>

<h1><a href="source/">Linux</a>/<a href="source/net/">net</a>/<a href="source/net/ipv4/">ipv4</a>/<a href="source/net/ipv4/af_inet.c">af_inet.c</a></h1>
<div id="lxrcode"><pre>  <a name="L1" href="source/net/ipv4/af_inet.c#L1">1</a> <b><i>/*</i></b>
  <a name="L2" href="source/net/ipv4/af_inet.c#L2">2</a> <b><i> * INET         An implementation of the TCP/IP protocol suite for the LINUX</i></b>
  <a name="L3" href="source/net/ipv4/af_inet.c#L3">3</a> <b><i> *              operating system.  INET is implemented using the  BSD Socket</i></b>
  <a name="L4" href="source/net/ipv4/af_inet.c#L4">4</a> <b><i> *              interface as the means of communication with the user level.</i></b>
  <a name="L5" href="source/net/ipv4/af_inet.c#L5">5</a> <b><i> *</i></b>
  <a name="L6" href="source/net/ipv4/af_inet.c#L6">6</a> <b><i> *              PF_INET protocol family socket handler.</i></b>
  <a name="L7" href="source/net/ipv4/af_inet.c#L7">7</a> <b><i> *</i></b>
  <a name="L8" href="source/net/ipv4/af_inet.c#L8">8</a> <b><i> * Authors:     Ross Biro</i></b>
  <a name="L9" href="source/net/ipv4/af_inet.c#L9">9</a> <b><i> *              Fred N. van Kempen, &lt;waltje@uWalt.NL.Mugnet.ORG&gt;</i></b>
 <a name="L10" href="source/net/ipv4/af_inet.c#L10">10</a> <b><i> *              Florian La Roche, &lt;flla@stud.uni-sb.de&gt;</i></b>
 <a name="L11" href="source/net/ipv4/af_inet.c#L11">11</a> <b><i> *              Alan Cox, &lt;A.Cox@swansea.ac.uk&gt;</i></b>
 <a name="L12" href="source/net/ipv4/af_inet.c#L12">12</a> <b><i> *</i></b>
 <a name="L13" href="source/net/ipv4/af_inet.c#L13">13</a> <b><i> * Changes (see also sock.c)</i></b>
 <a name="L14" href="source/net/ipv4/af_inet.c#L14">14</a> <b><i> *</i></b>
 <a name="L15" href="source/net/ipv4/af_inet.c#L15">15</a> <b><i> *              piggy,</i></b>
 <a name="L16" href="source/net/ipv4/af_inet.c#L16">16</a> <b><i> *              Karl Knutson    :       Socket protocol table</i></b>
 <a name="L17" href="source/net/ipv4/af_inet.c#L17">17</a> <b><i> *              A.N.Kuznetsov   :       Socket death error in accept().</i></b>
 <a name="L18" href="source/net/ipv4/af_inet.c#L18">18</a> <b><i> *              John Richardson :       Fix non blocking error in connect()</i></b>
 <a name="L19" href="source/net/ipv4/af_inet.c#L19">19</a> <b><i> *                                      so sockets that fail to connect</i></b>
 <a name="L20" href="source/net/ipv4/af_inet.c#L20">20</a> <b><i> *                                      don't return -EINPROGRESS.</i></b>
 <a name="L21" href="source/net/ipv4/af_inet.c#L21">21</a> <b><i> *              Alan Cox        :       Asynchronous I/O support</i></b>
 <a name="L22" href="source/net/ipv4/af_inet.c#L22">22</a> <b><i> *              Alan Cox        :       Keep correct socket pointer on sock</i></b>
 <a name="L23" href="source/net/ipv4/af_inet.c#L23">23</a> <b><i> *                                      structures</i></b>
 <a name="L24" href="source/net/ipv4/af_inet.c#L24">24</a> <b><i> *                                      when accept() ed</i></b>
 <a name="L25" href="source/net/ipv4/af_inet.c#L25">25</a> <b><i> *              Alan Cox        :       Semantics of SO_LINGER aren't state</i></b>
 <a name="L26" href="source/net/ipv4/af_inet.c#L26">26</a> <b><i> *                                      moved to close when you look carefully.</i></b>
 <a name="L27" href="source/net/ipv4/af_inet.c#L27">27</a> <b><i> *                                      With this fixed and the accept bug fixed</i></b>
 <a name="L28" href="source/net/ipv4/af_inet.c#L28">28</a> <b><i> *                                      some RPC stuff seems happier.</i></b>
 <a name="L29" href="source/net/ipv4/af_inet.c#L29">29</a> <b><i> *              Niibe Yutaka    :       4.4BSD style write async I/O</i></b>
 <a name="L30" href="source/net/ipv4/af_inet.c#L30">30</a> <b><i> *              Alan Cox,</i></b>
 <a name="L31" href="source/net/ipv4/af_inet.c#L31">31</a> <b><i> *              Tony Gale       :       Fixed reuse semantics.</i></b>
 <a name="L32" href="source/net/ipv4/af_inet.c#L32">32</a> <b><i> *              Alan Cox        :       bind() shouldn't abort existing but dead</i></b>
 <a name="L33" href="source/net/ipv4/af_inet.c#L33">33</a> <b><i> *                                      sockets. Stops FTP netin:.. I hope.</i></b>
 <a name="L34" href="source/net/ipv4/af_inet.c#L34">34</a> <b><i> *              Alan Cox        :       bind() works correctly for RAW sockets.</i></b>
 <a name="L35" href="source/net/ipv4/af_inet.c#L35">35</a> <b><i> *                                      Note that FreeBSD at least was broken</i></b>
 <a name="L36" href="source/net/ipv4/af_inet.c#L36">36</a> <b><i> *                                      in this respect so be careful with</i></b>
 <a name="L37" href="source/net/ipv4/af_inet.c#L37">37</a> <b><i> *                                      compatibility tests...</i></b>
 <a name="L38" href="source/net/ipv4/af_inet.c#L38">38</a> <b><i> *              Alan Cox        :       routing cache support</i></b>
 <a name="L39" href="source/net/ipv4/af_inet.c#L39">39</a> <b><i> *              Alan Cox        :       memzero the socket structure for</i></b>
 <a name="L40" href="source/net/ipv4/af_inet.c#L40">40</a> <b><i> *                                      compactness.</i></b>
 <a name="L41" href="source/net/ipv4/af_inet.c#L41">41</a> <b><i> *              Matt Day        :       nonblock connect error handler</i></b>
 <a name="L42" href="source/net/ipv4/af_inet.c#L42">42</a> <b><i> *              Alan Cox        :       Allow large numbers of pending sockets</i></b>
 <a name="L43" href="source/net/ipv4/af_inet.c#L43">43</a> <b><i> *                                      (eg for big web sites), but only if</i></b>
 <a name="L44" href="source/net/ipv4/af_inet.c#L44">44</a> <b><i> *                                      specifically application requested.</i></b>
 <a name="L45" href="source/net/ipv4/af_inet.c#L45">45</a> <b><i> *              Alan Cox        :       New buffering throughout IP. Used</i></b>
 <a name="L46" href="source/net/ipv4/af_inet.c#L46">46</a> <b><i> *                                      dumbly.</i></b>
 <a name="L47" href="source/net/ipv4/af_inet.c#L47">47</a> <b><i> *              Alan Cox        :       New buffering now used smartly.</i></b>
 <a name="L48" href="source/net/ipv4/af_inet.c#L48">48</a> <b><i> *              Alan Cox        :       BSD rather than common sense</i></b>
 <a name="L49" href="source/net/ipv4/af_inet.c#L49">49</a> <b><i> *                                      interpretation of listen.</i></b>
 <a name="L50" href="source/net/ipv4/af_inet.c#L50">50</a> <b><i> *              Germano Caronni :       Assorted small races.</i></b>
 <a name="L51" href="source/net/ipv4/af_inet.c#L51">51</a> <b><i> *              Alan Cox        :       sendmsg/recvmsg basic support.</i></b>
 <a name="L52" href="source/net/ipv4/af_inet.c#L52">52</a> <b><i> *              Alan Cox        :       Only sendmsg/recvmsg now supported.</i></b>
 <a name="L53" href="source/net/ipv4/af_inet.c#L53">53</a> <b><i> *              Alan Cox        :       Locked down bind (see security list).</i></b>
 <a name="L54" href="source/net/ipv4/af_inet.c#L54">54</a> <b><i> *              Alan Cox        :       Loosened bind a little.</i></b>
 <a name="L55" href="source/net/ipv4/af_inet.c#L55">55</a> <b><i> *              Mike McLagan    :       ADD/DEL DLCI Ioctls</i></b>
 <a name="L56" href="source/net/ipv4/af_inet.c#L56">56</a> <b><i> *      Willy Konynenberg       :       Transparent proxying support.</i></b>
 <a name="L57" href="source/net/ipv4/af_inet.c#L57">57</a> <b><i> *              David S. Miller :       New socket lookup architecture.</i></b>
 <a name="L58" href="source/net/ipv4/af_inet.c#L58">58</a> <b><i> *                                      Some other random speedups.</i></b>
 <a name="L59" href="source/net/ipv4/af_inet.c#L59">59</a> <b><i> *              Cyrus Durgin    :       Cleaned up file for kmod hacks.</i></b>
 <a name="L60" href="source/net/ipv4/af_inet.c#L60">60</a> <b><i> *              Andi Kleen      :       Fix inet_stream_connect TCP race.</i></b>
 <a name="L61" href="source/net/ipv4/af_inet.c#L61">61</a> <b><i> *</i></b>
 <a name="L62" href="source/net/ipv4/af_inet.c#L62">62</a> <b><i> *              This program is free software; you can redistribute it and/or</i></b>
 <a name="L63" href="source/net/ipv4/af_inet.c#L63">63</a> <b><i> *              modify it under the terms of the GNU General Public License</i></b>
 <a name="L64" href="source/net/ipv4/af_inet.c#L64">64</a> <b><i> *              as published by the Free Software Foundation; either version</i></b>
 <a name="L65" href="source/net/ipv4/af_inet.c#L65">65</a> <b><i> *              2 of the License, or (at your option) any later version.</i></b>
 <a name="L66" href="source/net/ipv4/af_inet.c#L66">66</a> <b><i> */</i></b>
 <a name="L67" href="source/net/ipv4/af_inet.c#L67">67</a> 
 <a name="L68" href="source/net/ipv4/af_inet.c#L68">68</a> #define <a href="ident?i=pr_fmt">pr_fmt</a>(<a href="ident?i=fmt">fmt</a>) <i>"IPv4: "</i> <a href="ident?i=fmt">fmt</a>
 <a name="L69" href="source/net/ipv4/af_inet.c#L69">69</a> 
 <a name="L70" href="source/net/ipv4/af_inet.c#L70">70</a> #include &lt;linux/err.h&gt;
 <a name="L71" href="source/net/ipv4/af_inet.c#L71">71</a> #include &lt;linux/errno.h&gt;
 <a name="L72" href="source/net/ipv4/af_inet.c#L72">72</a> #include &lt;linux/types.h&gt;
 <a name="L73" href="source/net/ipv4/af_inet.c#L73">73</a> #include &lt;linux/socket.h&gt;
 <a name="L74" href="source/net/ipv4/af_inet.c#L74">74</a> #include &lt;linux/in.h&gt;
 <a name="L75" href="source/net/ipv4/af_inet.c#L75">75</a> #include &lt;linux/kernel.h&gt;
 <a name="L76" href="source/net/ipv4/af_inet.c#L76">76</a> #include &lt;linux/module.h&gt;
 <a name="L77" href="source/net/ipv4/af_inet.c#L77">77</a> #include &lt;linux/sched.h&gt;
 <a name="L78" href="source/net/ipv4/af_inet.c#L78">78</a> #include &lt;linux/timer.h&gt;
 <a name="L79" href="source/net/ipv4/af_inet.c#L79">79</a> #include &lt;linux/string.h&gt;
 <a name="L80" href="source/net/ipv4/af_inet.c#L80">80</a> #include &lt;linux/sockios.h&gt;
 <a name="L81" href="source/net/ipv4/af_inet.c#L81">81</a> #include &lt;linux/net.h&gt;
 <a name="L82" href="source/net/ipv4/af_inet.c#L82">82</a> #include &lt;linux/capability.h&gt;
 <a name="L83" href="source/net/ipv4/af_inet.c#L83">83</a> #include &lt;linux/fcntl.h&gt;
 <a name="L84" href="source/net/ipv4/af_inet.c#L84">84</a> #include &lt;linux/mm.h&gt;
 <a name="L85" href="source/net/ipv4/af_inet.c#L85">85</a> #include &lt;linux/interrupt.h&gt;
 <a name="L86" href="source/net/ipv4/af_inet.c#L86">86</a> #include &lt;linux/stat.h&gt;
 <a name="L87" href="source/net/ipv4/af_inet.c#L87">87</a> #include &lt;linux/init.h&gt;
 <a name="L88" href="source/net/ipv4/af_inet.c#L88">88</a> #include &lt;linux/poll.h&gt;
 <a name="L89" href="source/net/ipv4/af_inet.c#L89">89</a> #include &lt;linux/netfilter_ipv4.h&gt;
 <a name="L90" href="source/net/ipv4/af_inet.c#L90">90</a> #include &lt;linux/random.h&gt;
 <a name="L91" href="source/net/ipv4/af_inet.c#L91">91</a> #include &lt;linux/slab.h&gt;
 <a name="L92" href="source/net/ipv4/af_inet.c#L92">92</a> 
 <a name="L93" href="source/net/ipv4/af_inet.c#L93">93</a> #include &lt;asm/uaccess.h&gt;
 <a name="L94" href="source/net/ipv4/af_inet.c#L94">94</a> 
 <a name="L95" href="source/net/ipv4/af_inet.c#L95">95</a> #include &lt;linux/inet.h&gt;
 <a name="L96" href="source/net/ipv4/af_inet.c#L96">96</a> #include &lt;linux/igmp.h&gt;
 <a name="L97" href="source/net/ipv4/af_inet.c#L97">97</a> #include &lt;linux/inetdevice.h&gt;
 <a name="L98" href="source/net/ipv4/af_inet.c#L98">98</a> #include &lt;linux/netdevice.h&gt;
 <a name="L99" href="source/net/ipv4/af_inet.c#L99">99</a> #include &lt;net/checksum.h&gt;
<a name="L100" href="source/net/ipv4/af_inet.c#L100">100</a> #include &lt;net/ip.h&gt;
<a name="L101" href="source/net/ipv4/af_inet.c#L101">101</a> #include &lt;net/protocol.h&gt;
<a name="L102" href="source/net/ipv4/af_inet.c#L102">102</a> #include &lt;net/arp.h&gt;
<a name="L103" href="source/net/ipv4/af_inet.c#L103">103</a> #include &lt;net/route.h&gt;
<a name="L104" href="source/net/ipv4/af_inet.c#L104">104</a> #include &lt;net/ip_fib.h&gt;
<a name="L105" href="source/net/ipv4/af_inet.c#L105">105</a> #include &lt;net/inet_connection_sock.h&gt;
<a name="L106" href="source/net/ipv4/af_inet.c#L106">106</a> #include &lt;net/tcp.h&gt;
<a name="L107" href="source/net/ipv4/af_inet.c#L107">107</a> #include &lt;net/udp.h&gt;
<a name="L108" href="source/net/ipv4/af_inet.c#L108">108</a> #include &lt;net/udplite.h&gt;
<a name="L109" href="source/net/ipv4/af_inet.c#L109">109</a> #include &lt;net/ping.h&gt;
<a name="L110" href="source/net/ipv4/af_inet.c#L110">110</a> #include &lt;linux/skbuff.h&gt;
<a name="L111" href="source/net/ipv4/af_inet.c#L111">111</a> #include &lt;net/sock.h&gt;
<a name="L112" href="source/net/ipv4/af_inet.c#L112">112</a> #include &lt;net/raw.h&gt;
<a name="L113" href="source/net/ipv4/af_inet.c#L113">113</a> #include &lt;net/icmp.h&gt;
<a name="L114" href="source/net/ipv4/af_inet.c#L114">114</a> #include &lt;net/inet_common.h&gt;
<a name="L115" href="source/net/ipv4/af_inet.c#L115">115</a> #include &lt;net/xfrm.h&gt;
<a name="L116" href="source/net/ipv4/af_inet.c#L116">116</a> #include &lt;net/net_namespace.h&gt;
<a name="L117" href="source/net/ipv4/af_inet.c#L117">117</a> #include &lt;net/secure_seq.h&gt;
<a name="L118" href="source/net/ipv4/af_inet.c#L118">118</a> #ifdef CONFIG_IP_MROUTE
<a name="L119" href="source/net/ipv4/af_inet.c#L119">119</a> #include &lt;linux/mroute.h&gt;
<a name="L120" href="source/net/ipv4/af_inet.c#L120">120</a> #endif
<a name="L121" href="source/net/ipv4/af_inet.c#L121">121</a> 
<a name="L122" href="source/net/ipv4/af_inet.c#L122">122</a> 
<a name="L123" href="source/net/ipv4/af_inet.c#L123">123</a> <b><i>/* The inetsw table contains everything that inet_create needs to</i></b>
<a name="L124" href="source/net/ipv4/af_inet.c#L124">124</a> <b><i> * build a new socket.</i></b>
<a name="L125" href="source/net/ipv4/af_inet.c#L125">125</a> <b><i> */</i></b>
<a name="L126" href="source/net/ipv4/af_inet.c#L126">126</a> static struct <a href="ident?i=list_head">list_head</a> <a href="ident?i=inetsw">inetsw</a>[<a href="ident?i=SOCK_MAX">SOCK_MAX</a>];
<a name="L127" href="source/net/ipv4/af_inet.c#L127">127</a> static <a href="ident?i=DEFINE_SPINLOCK">DEFINE_SPINLOCK</a>(inetsw_lock);
<a name="L128" href="source/net/ipv4/af_inet.c#L128">128</a> 
<a name="L129" href="source/net/ipv4/af_inet.c#L129">129</a> <b><i>/* New destruction routine */</i></b>
<a name="L130" href="source/net/ipv4/af_inet.c#L130">130</a> 
<a name="L131" href="source/net/ipv4/af_inet.c#L131">131</a> void <a href="ident?i=inet_sock_destruct">inet_sock_destruct</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L132" href="source/net/ipv4/af_inet.c#L132">132</a> {
<a name="L133" href="source/net/ipv4/af_inet.c#L133">133</a>         struct <a href="ident?i=inet_sock">inet_sock</a> *inet = <a href="ident?i=inet_sk">inet_sk</a>(sk);
<a name="L134" href="source/net/ipv4/af_inet.c#L134">134</a> 
<a name="L135" href="source/net/ipv4/af_inet.c#L135">135</a>         <a href="ident?i=__skb_queue_purge">__skb_queue_purge</a>(&amp;sk-&gt;sk_receive_queue);
<a name="L136" href="source/net/ipv4/af_inet.c#L136">136</a>         <a href="ident?i=__skb_queue_purge">__skb_queue_purge</a>(&amp;sk-&gt;sk_error_queue);
<a name="L137" href="source/net/ipv4/af_inet.c#L137">137</a> 
<a name="L138" href="source/net/ipv4/af_inet.c#L138">138</a>         <a href="ident?i=sk_mem_reclaim">sk_mem_reclaim</a>(sk);
<a name="L139" href="source/net/ipv4/af_inet.c#L139">139</a> 
<a name="L140" href="source/net/ipv4/af_inet.c#L140">140</a>         if (sk-&gt;sk_type == SOCK_STREAM &amp;&amp; sk-&gt;<a href="ident?i=sk_state">sk_state</a> != TCP_CLOSE) {
<a name="L141" href="source/net/ipv4/af_inet.c#L141">141</a>                 <a href="ident?i=pr_err">pr_err</a>(<i>"Attempt to release TCP socket in state %d %p\n"</i>,
<a name="L142" href="source/net/ipv4/af_inet.c#L142">142</a>                        sk-&gt;<a href="ident?i=sk_state">sk_state</a>, sk);
<a name="L143" href="source/net/ipv4/af_inet.c#L143">143</a>                 return;
<a name="L144" href="source/net/ipv4/af_inet.c#L144">144</a>         }
<a name="L145" href="source/net/ipv4/af_inet.c#L145">145</a>         if (!<a href="ident?i=sock_flag">sock_flag</a>(sk, SOCK_DEAD)) {
<a name="L146" href="source/net/ipv4/af_inet.c#L146">146</a>                 <a href="ident?i=pr_err">pr_err</a>(<i>"Attempt to release alive inet socket %p\n"</i>, sk);
<a name="L147" href="source/net/ipv4/af_inet.c#L147">147</a>                 return;
<a name="L148" href="source/net/ipv4/af_inet.c#L148">148</a>         }
<a name="L149" href="source/net/ipv4/af_inet.c#L149">149</a> 
<a name="L150" href="source/net/ipv4/af_inet.c#L150">150</a>         <a href="ident?i=WARN_ON">WARN_ON</a>(<a href="ident?i=atomic_read">atomic_read</a>(&amp;sk-&gt;<a href="ident?i=sk_rmem_alloc">sk_rmem_alloc</a>));
<a name="L151" href="source/net/ipv4/af_inet.c#L151">151</a>         <a href="ident?i=WARN_ON">WARN_ON</a>(<a href="ident?i=atomic_read">atomic_read</a>(&amp;sk-&gt;sk_wmem_alloc));
<a name="L152" href="source/net/ipv4/af_inet.c#L152">152</a>         <a href="ident?i=WARN_ON">WARN_ON</a>(sk-&gt;sk_wmem_queued);
<a name="L153" href="source/net/ipv4/af_inet.c#L153">153</a>         <a href="ident?i=WARN_ON">WARN_ON</a>(sk-&gt;sk_forward_alloc);
<a name="L154" href="source/net/ipv4/af_inet.c#L154">154</a> 
<a name="L155" href="source/net/ipv4/af_inet.c#L155">155</a>         <a href="ident?i=kfree">kfree</a>(<a href="ident?i=rcu_dereference_protected">rcu_dereference_protected</a>(inet-&gt;inet_opt, 1));
<a name="L156" href="source/net/ipv4/af_inet.c#L156">156</a>         <a href="ident?i=dst_release">dst_release</a>(<a href="ident?i=rcu_dereference_check">rcu_dereference_check</a>(sk-&gt;sk_dst_cache, 1));
<a name="L157" href="source/net/ipv4/af_inet.c#L157">157</a>         <a href="ident?i=dst_release">dst_release</a>(sk-&gt;sk_rx_dst);
<a name="L158" href="source/net/ipv4/af_inet.c#L158">158</a>         <a href="ident?i=sk_refcnt_debug_dec">sk_refcnt_debug_dec</a>(sk);
<a name="L159" href="source/net/ipv4/af_inet.c#L159">159</a> }
<a name="L160" href="source/net/ipv4/af_inet.c#L160">160</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=inet_sock_destruct">inet_sock_destruct</a>);
<a name="L161" href="source/net/ipv4/af_inet.c#L161">161</a> 
<a name="L162" href="source/net/ipv4/af_inet.c#L162">162</a> <b><i>/*</i></b>
<a name="L163" href="source/net/ipv4/af_inet.c#L163">163</a> <b><i> *      The routines beyond this point handle the behaviour of an AF_INET</i></b>
<a name="L164" href="source/net/ipv4/af_inet.c#L164">164</a> <b><i> *      socket object. Mostly it punts to the subprotocols of IP to do</i></b>
<a name="L165" href="source/net/ipv4/af_inet.c#L165">165</a> <b><i> *      the work.</i></b>
<a name="L166" href="source/net/ipv4/af_inet.c#L166">166</a> <b><i> */</i></b>
<a name="L167" href="source/net/ipv4/af_inet.c#L167">167</a> 
<a name="L168" href="source/net/ipv4/af_inet.c#L168">168</a> <b><i>/*</i></b>
<a name="L169" href="source/net/ipv4/af_inet.c#L169">169</a> <b><i> *      Automatically bind an unbound socket.</i></b>
<a name="L170" href="source/net/ipv4/af_inet.c#L170">170</a> <b><i> */</i></b>
<a name="L171" href="source/net/ipv4/af_inet.c#L171">171</a> 
<a name="L172" href="source/net/ipv4/af_inet.c#L172">172</a> static int <a href="ident?i=inet_autobind">inet_autobind</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L173" href="source/net/ipv4/af_inet.c#L173">173</a> {
<a name="L174" href="source/net/ipv4/af_inet.c#L174">174</a>         struct <a href="ident?i=inet_sock">inet_sock</a> *inet;
<a name="L175" href="source/net/ipv4/af_inet.c#L175">175</a>         <b><i>/* We may need to bind the socket. */</i></b>
<a name="L176" href="source/net/ipv4/af_inet.c#L176">176</a>         <a href="ident?i=lock_sock">lock_sock</a>(sk);
<a name="L177" href="source/net/ipv4/af_inet.c#L177">177</a>         inet = <a href="ident?i=inet_sk">inet_sk</a>(sk);
<a name="L178" href="source/net/ipv4/af_inet.c#L178">178</a>         if (!inet-&gt;<a href="ident?i=inet_num">inet_num</a>) {
<a name="L179" href="source/net/ipv4/af_inet.c#L179">179</a>                 if (sk-&gt;<a href="ident?i=sk_prot">sk_prot</a>-&gt;<a href="ident?i=get_port">get_port</a>(sk, 0)) {
<a name="L180" href="source/net/ipv4/af_inet.c#L180">180</a>                         <a href="ident?i=release_sock">release_sock</a>(sk);
<a name="L181" href="source/net/ipv4/af_inet.c#L181">181</a>                         return -<a href="ident?i=EAGAIN">EAGAIN</a>;
<a name="L182" href="source/net/ipv4/af_inet.c#L182">182</a>                 }
<a name="L183" href="source/net/ipv4/af_inet.c#L183">183</a>                 inet-&gt;inet_sport = <a href="ident?i=htons">htons</a>(inet-&gt;<a href="ident?i=inet_num">inet_num</a>);
<a name="L184" href="source/net/ipv4/af_inet.c#L184">184</a>         }
<a name="L185" href="source/net/ipv4/af_inet.c#L185">185</a>         <a href="ident?i=release_sock">release_sock</a>(sk);
<a name="L186" href="source/net/ipv4/af_inet.c#L186">186</a>         return 0;
<a name="L187" href="source/net/ipv4/af_inet.c#L187">187</a> }
<a name="L188" href="source/net/ipv4/af_inet.c#L188">188</a> 
<a name="L189" href="source/net/ipv4/af_inet.c#L189">189</a> <b><i>/*</i></b>
<a name="L190" href="source/net/ipv4/af_inet.c#L190">190</a> <b><i> *      Move a socket into listening state.</i></b>
<a name="L191" href="source/net/ipv4/af_inet.c#L191">191</a> <b><i> */</i></b>
<a name="L192" href="source/net/ipv4/af_inet.c#L192">192</a> int <a href="ident?i=inet_listen">inet_listen</a>(struct <a href="ident?i=socket">socket</a> *<a href="ident?i=sock">sock</a>, int backlog)
<a name="L193" href="source/net/ipv4/af_inet.c#L193">193</a> {
<a name="L194" href="source/net/ipv4/af_inet.c#L194">194</a>         struct <a href="ident?i=sock">sock</a> *sk = <a href="ident?i=sock">sock</a>-&gt;sk;
<a name="L195" href="source/net/ipv4/af_inet.c#L195">195</a>         unsigned char old_state;
<a name="L196" href="source/net/ipv4/af_inet.c#L196">196</a>         int <a href="ident?i=err">err</a>;
<a name="L197" href="source/net/ipv4/af_inet.c#L197">197</a> 
<a name="L198" href="source/net/ipv4/af_inet.c#L198">198</a>         <a href="ident?i=lock_sock">lock_sock</a>(sk);
<a name="L199" href="source/net/ipv4/af_inet.c#L199">199</a> 
<a name="L200" href="source/net/ipv4/af_inet.c#L200">200</a>         <a href="ident?i=err">err</a> = -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L201" href="source/net/ipv4/af_inet.c#L201">201</a>         if (<a href="ident?i=sock">sock</a>-&gt;<a href="ident?i=state">state</a> != SS_UNCONNECTED || <a href="ident?i=sock">sock</a>-&gt;<a href="ident?i=type">type</a> != SOCK_STREAM)
<a name="L202" href="source/net/ipv4/af_inet.c#L202">202</a>                 goto <a href="ident?i=out">out</a>;
<a name="L203" href="source/net/ipv4/af_inet.c#L203">203</a> 
<a name="L204" href="source/net/ipv4/af_inet.c#L204">204</a>         old_state = sk-&gt;<a href="ident?i=sk_state">sk_state</a>;
<a name="L205" href="source/net/ipv4/af_inet.c#L205">205</a>         if (!((1 &lt;&lt; old_state) &amp; (TCPF_CLOSE | TCPF_LISTEN)))
<a name="L206" href="source/net/ipv4/af_inet.c#L206">206</a>                 goto <a href="ident?i=out">out</a>;
<a name="L207" href="source/net/ipv4/af_inet.c#L207">207</a> 
<a name="L208" href="source/net/ipv4/af_inet.c#L208">208</a>         <b><i>/* Really, if the socket is already in listen state</i></b>
<a name="L209" href="source/net/ipv4/af_inet.c#L209">209</a> <b><i>         * we can only allow the backlog to be adjusted.</i></b>
<a name="L210" href="source/net/ipv4/af_inet.c#L210">210</a> <b><i>         */</i></b>
<a name="L211" href="source/net/ipv4/af_inet.c#L211">211</a>         if (old_state != TCP_LISTEN) {
<a name="L212" href="source/net/ipv4/af_inet.c#L212">212</a>                 <b><i>/* Check special setups for testing purpose to enable TFO w/o</i></b>
<a name="L213" href="source/net/ipv4/af_inet.c#L213">213</a> <b><i>                 * requiring TCP_FASTOPEN sockopt.</i></b>
<a name="L214" href="source/net/ipv4/af_inet.c#L214">214</a> <b><i>                 * Note that only TCP sockets (SOCK_STREAM) will reach here.</i></b>
<a name="L215" href="source/net/ipv4/af_inet.c#L215">215</a> <b><i>                 * Also fastopenq may already been allocated because this</i></b>
<a name="L216" href="source/net/ipv4/af_inet.c#L216">216</a> <b><i>                 * socket was in TCP_LISTEN state previously but was</i></b>
<a name="L217" href="source/net/ipv4/af_inet.c#L217">217</a> <b><i>                 * shutdown() (rather than close()).</i></b>
<a name="L218" href="source/net/ipv4/af_inet.c#L218">218</a> <b><i>                 */</i></b>
<a name="L219" href="source/net/ipv4/af_inet.c#L219">219</a>                 if ((<a href="ident?i=sysctl_tcp_fastopen">sysctl_tcp_fastopen</a> &amp; <a href="ident?i=TFO_SERVER_ENABLE">TFO_SERVER_ENABLE</a>) != 0 &amp;&amp;
<a name="L220" href="source/net/ipv4/af_inet.c#L220">220</a>                     !<a href="ident?i=inet_csk">inet_csk</a>(sk)-&gt;icsk_accept_queue.fastopenq) {
<a name="L221" href="source/net/ipv4/af_inet.c#L221">221</a>                         if ((<a href="ident?i=sysctl_tcp_fastopen">sysctl_tcp_fastopen</a> &amp; <a href="ident?i=TFO_SERVER_WO_SOCKOPT1">TFO_SERVER_WO_SOCKOPT1</a>) != 0)
<a name="L222" href="source/net/ipv4/af_inet.c#L222">222</a>                                 <a href="ident?i=err">err</a> = <a href="ident?i=fastopen_init_queue">fastopen_init_queue</a>(sk, backlog);
<a name="L223" href="source/net/ipv4/af_inet.c#L223">223</a>                         else if ((<a href="ident?i=sysctl_tcp_fastopen">sysctl_tcp_fastopen</a> &amp;
<a name="L224" href="source/net/ipv4/af_inet.c#L224">224</a>                                   <a href="ident?i=TFO_SERVER_WO_SOCKOPT2">TFO_SERVER_WO_SOCKOPT2</a>) != 0)
<a name="L225" href="source/net/ipv4/af_inet.c#L225">225</a>                                 <a href="ident?i=err">err</a> = <a href="ident?i=fastopen_init_queue">fastopen_init_queue</a>(sk,
<a name="L226" href="source/net/ipv4/af_inet.c#L226">226</a>                                     ((<a href="ident?i=uint">uint</a>)<a href="ident?i=sysctl_tcp_fastopen">sysctl_tcp_fastopen</a>) &gt;&gt; 16);
<a name="L227" href="source/net/ipv4/af_inet.c#L227">227</a>                         else
<a name="L228" href="source/net/ipv4/af_inet.c#L228">228</a>                                 <a href="ident?i=err">err</a> = 0;
<a name="L229" href="source/net/ipv4/af_inet.c#L229">229</a>                         if (<a href="ident?i=err">err</a>)
<a name="L230" href="source/net/ipv4/af_inet.c#L230">230</a>                                 goto <a href="ident?i=out">out</a>;
<a name="L231" href="source/net/ipv4/af_inet.c#L231">231</a>                 }
<a name="L232" href="source/net/ipv4/af_inet.c#L232">232</a>                 <a href="ident?i=err">err</a> = <a href="ident?i=inet_csk_listen_start">inet_csk_listen_start</a>(sk, backlog);
<a name="L233" href="source/net/ipv4/af_inet.c#L233">233</a>                 if (<a href="ident?i=err">err</a>)
<a name="L234" href="source/net/ipv4/af_inet.c#L234">234</a>                         goto <a href="ident?i=out">out</a>;
<a name="L235" href="source/net/ipv4/af_inet.c#L235">235</a>         }
<a name="L236" href="source/net/ipv4/af_inet.c#L236">236</a>         sk-&gt;sk_max_ack_backlog = backlog;
<a name="L237" href="source/net/ipv4/af_inet.c#L237">237</a>         <a href="ident?i=err">err</a> = 0;
<a name="L238" href="source/net/ipv4/af_inet.c#L238">238</a> 
<a name="L239" href="source/net/ipv4/af_inet.c#L239">239</a> <a href="ident?i=out">out</a>:
<a name="L240" href="source/net/ipv4/af_inet.c#L240">240</a>         <a href="ident?i=release_sock">release_sock</a>(sk);
<a name="L241" href="source/net/ipv4/af_inet.c#L241">241</a>         return <a href="ident?i=err">err</a>;
<a name="L242" href="source/net/ipv4/af_inet.c#L242">242</a> }
<a name="L243" href="source/net/ipv4/af_inet.c#L243">243</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=inet_listen">inet_listen</a>);
<a name="L244" href="source/net/ipv4/af_inet.c#L244">244</a> 
<a name="L245" href="source/net/ipv4/af_inet.c#L245">245</a> <b><i>/*</i></b>
<a name="L246" href="source/net/ipv4/af_inet.c#L246">246</a> <b><i> *      Create an inet socket.</i></b>
<a name="L247" href="source/net/ipv4/af_inet.c#L247">247</a> <b><i> */</i></b>
<a name="L248" href="source/net/ipv4/af_inet.c#L248">248</a> 
<a name="L249" href="source/net/ipv4/af_inet.c#L249">249</a> static int <a href="ident?i=inet_create">inet_create</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>, struct <a href="ident?i=socket">socket</a> *<a href="ident?i=sock">sock</a>, int <a href="ident?i=protocol">protocol</a>,
<a name="L250" href="source/net/ipv4/af_inet.c#L250">250</a>                        int kern)
<a name="L251" href="source/net/ipv4/af_inet.c#L251">251</a> {
<a name="L252" href="source/net/ipv4/af_inet.c#L252">252</a>         struct <a href="ident?i=sock">sock</a> *sk;
<a name="L253" href="source/net/ipv4/af_inet.c#L253">253</a>         struct <a href="ident?i=inet_protosw">inet_protosw</a> *<a href="ident?i=answer">answer</a>;
<a name="L254" href="source/net/ipv4/af_inet.c#L254">254</a>         struct <a href="ident?i=inet_sock">inet_sock</a> *inet;
<a name="L255" href="source/net/ipv4/af_inet.c#L255">255</a>         struct <a href="ident?i=proto">proto</a> *answer_prot;
<a name="L256" href="source/net/ipv4/af_inet.c#L256">256</a>         unsigned char answer_flags;
<a name="L257" href="source/net/ipv4/af_inet.c#L257">257</a>         int try_loading_module = 0;
<a name="L258" href="source/net/ipv4/af_inet.c#L258">258</a>         int <a href="ident?i=err">err</a>;
<a name="L259" href="source/net/ipv4/af_inet.c#L259">259</a> 
<a name="L260" href="source/net/ipv4/af_inet.c#L260">260</a>         <a href="ident?i=sock">sock</a>-&gt;<a href="ident?i=state">state</a> = SS_UNCONNECTED;
<a name="L261" href="source/net/ipv4/af_inet.c#L261">261</a> 
<a name="L262" href="source/net/ipv4/af_inet.c#L262">262</a>         <b><i>/* Look for the requested type/protocol pair. */</i></b>
<a name="L263" href="source/net/ipv4/af_inet.c#L263">263</a> lookup_protocol:
<a name="L264" href="source/net/ipv4/af_inet.c#L264">264</a>         <a href="ident?i=err">err</a> = -<a href="ident?i=ESOCKTNOSUPPORT">ESOCKTNOSUPPORT</a>;
<a name="L265" href="source/net/ipv4/af_inet.c#L265">265</a>         <a href="ident?i=rcu_read_lock">rcu_read_lock</a>();
<a name="L266" href="source/net/ipv4/af_inet.c#L266">266</a>         <a href="ident?i=list_for_each_entry_rcu">list_for_each_entry_rcu</a>(<a href="ident?i=answer">answer</a>, &amp;<a href="ident?i=inetsw">inetsw</a>[<a href="ident?i=sock">sock</a>-&gt;<a href="ident?i=type">type</a>], <a href="ident?i=list">list</a>) {
<a name="L267" href="source/net/ipv4/af_inet.c#L267">267</a> 
<a name="L268" href="source/net/ipv4/af_inet.c#L268">268</a>                 <a href="ident?i=err">err</a> = 0;
<a name="L269" href="source/net/ipv4/af_inet.c#L269">269</a>                 <b><i>/* Check the non-wild match. */</i></b>
<a name="L270" href="source/net/ipv4/af_inet.c#L270">270</a>                 if (<a href="ident?i=protocol">protocol</a> == <a href="ident?i=answer">answer</a>-&gt;<a href="ident?i=protocol">protocol</a>) {
<a name="L271" href="source/net/ipv4/af_inet.c#L271">271</a>                         if (<a href="ident?i=protocol">protocol</a> != <a href="ident?i=IPPROTO_IP">IPPROTO_IP</a>)
<a name="L272" href="source/net/ipv4/af_inet.c#L272">272</a>                                 break;
<a name="L273" href="source/net/ipv4/af_inet.c#L273">273</a>                 } else {
<a name="L274" href="source/net/ipv4/af_inet.c#L274">274</a>                         <b><i>/* Check for the two wild cases. */</i></b>
<a name="L275" href="source/net/ipv4/af_inet.c#L275">275</a>                         if (<a href="ident?i=IPPROTO_IP">IPPROTO_IP</a> == <a href="ident?i=protocol">protocol</a>) {
<a name="L276" href="source/net/ipv4/af_inet.c#L276">276</a>                                 <a href="ident?i=protocol">protocol</a> = <a href="ident?i=answer">answer</a>-&gt;<a href="ident?i=protocol">protocol</a>;
<a name="L277" href="source/net/ipv4/af_inet.c#L277">277</a>                                 break;
<a name="L278" href="source/net/ipv4/af_inet.c#L278">278</a>                         }
<a name="L279" href="source/net/ipv4/af_inet.c#L279">279</a>                         if (<a href="ident?i=IPPROTO_IP">IPPROTO_IP</a> == <a href="ident?i=answer">answer</a>-&gt;<a href="ident?i=protocol">protocol</a>)
<a name="L280" href="source/net/ipv4/af_inet.c#L280">280</a>                                 break;
<a name="L281" href="source/net/ipv4/af_inet.c#L281">281</a>                 }
<a name="L282" href="source/net/ipv4/af_inet.c#L282">282</a>                 <a href="ident?i=err">err</a> = -<a href="ident?i=EPROTONOSUPPORT">EPROTONOSUPPORT</a>;
<a name="L283" href="source/net/ipv4/af_inet.c#L283">283</a>         }
<a name="L284" href="source/net/ipv4/af_inet.c#L284">284</a> 
<a name="L285" href="source/net/ipv4/af_inet.c#L285">285</a>         if (<a href="ident?i=unlikely">unlikely</a>(<a href="ident?i=err">err</a>)) {
<a name="L286" href="source/net/ipv4/af_inet.c#L286">286</a>                 if (try_loading_module &lt; 2) {
<a name="L287" href="source/net/ipv4/af_inet.c#L287">287</a>                         <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L288" href="source/net/ipv4/af_inet.c#L288">288</a>                         <b><i>/*</i></b>
<a name="L289" href="source/net/ipv4/af_inet.c#L289">289</a> <b><i>                         * Be more specific, e.g. net-pf-2-proto-132-type-1</i></b>
<a name="L290" href="source/net/ipv4/af_inet.c#L290">290</a> <b><i>                         * (net-pf-PF_INET-proto-IPPROTO_SCTP-type-SOCK_STREAM)</i></b>
<a name="L291" href="source/net/ipv4/af_inet.c#L291">291</a> <b><i>                         */</i></b>
<a name="L292" href="source/net/ipv4/af_inet.c#L292">292</a>                         if (++try_loading_module == 1)
<a name="L293" href="source/net/ipv4/af_inet.c#L293">293</a>                                 <a href="ident?i=request_module">request_module</a>(<i>"net-pf-%d-proto-%d-type-%d"</i>,
<a name="L294" href="source/net/ipv4/af_inet.c#L294">294</a>                                                <a href="ident?i=PF_INET">PF_INET</a>, <a href="ident?i=protocol">protocol</a>, <a href="ident?i=sock">sock</a>-&gt;<a href="ident?i=type">type</a>);
<a name="L295" href="source/net/ipv4/af_inet.c#L295">295</a>                         <b><i>/*</i></b>
<a name="L296" href="source/net/ipv4/af_inet.c#L296">296</a> <b><i>                         * Fall back to generic, e.g. net-pf-2-proto-132</i></b>
<a name="L297" href="source/net/ipv4/af_inet.c#L297">297</a> <b><i>                         * (net-pf-PF_INET-proto-IPPROTO_SCTP)</i></b>
<a name="L298" href="source/net/ipv4/af_inet.c#L298">298</a> <b><i>                         */</i></b>
<a name="L299" href="source/net/ipv4/af_inet.c#L299">299</a>                         else
<a name="L300" href="source/net/ipv4/af_inet.c#L300">300</a>                                 <a href="ident?i=request_module">request_module</a>(<i>"net-pf-%d-proto-%d"</i>,
<a name="L301" href="source/net/ipv4/af_inet.c#L301">301</a>                                                <a href="ident?i=PF_INET">PF_INET</a>, <a href="ident?i=protocol">protocol</a>);
<a name="L302" href="source/net/ipv4/af_inet.c#L302">302</a>                         goto lookup_protocol;
<a name="L303" href="source/net/ipv4/af_inet.c#L303">303</a>                 } else
<a name="L304" href="source/net/ipv4/af_inet.c#L304">304</a>                         goto out_rcu_unlock;
<a name="L305" href="source/net/ipv4/af_inet.c#L305">305</a>         }
<a name="L306" href="source/net/ipv4/af_inet.c#L306">306</a> 
<a name="L307" href="source/net/ipv4/af_inet.c#L307">307</a>         <a href="ident?i=err">err</a> = -<a href="ident?i=EPERM">EPERM</a>;
<a name="L308" href="source/net/ipv4/af_inet.c#L308">308</a>         if (<a href="ident?i=sock">sock</a>-&gt;<a href="ident?i=type">type</a> == SOCK_RAW &amp;&amp; !kern &amp;&amp;
<a name="L309" href="source/net/ipv4/af_inet.c#L309">309</a>             !<a href="ident?i=ns_capable">ns_capable</a>(<a href="ident?i=net">net</a>-&gt;<a href="ident?i=user_ns">user_ns</a>, <a href="ident?i=CAP_NET_RAW">CAP_NET_RAW</a>))
<a name="L310" href="source/net/ipv4/af_inet.c#L310">310</a>                 goto out_rcu_unlock;
<a name="L311" href="source/net/ipv4/af_inet.c#L311">311</a> 
<a name="L312" href="source/net/ipv4/af_inet.c#L312">312</a>         <a href="ident?i=sock">sock</a>-&gt;<a href="ident?i=ops">ops</a> = <a href="ident?i=answer">answer</a>-&gt;<a href="ident?i=ops">ops</a>;
<a name="L313" href="source/net/ipv4/af_inet.c#L313">313</a>         answer_prot = <a href="ident?i=answer">answer</a>-&gt;prot;
<a name="L314" href="source/net/ipv4/af_inet.c#L314">314</a>         answer_flags = <a href="ident?i=answer">answer</a>-&gt;<a href="ident?i=flags">flags</a>;
<a name="L315" href="source/net/ipv4/af_inet.c#L315">315</a>         <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L316" href="source/net/ipv4/af_inet.c#L316">316</a> 
<a name="L317" href="source/net/ipv4/af_inet.c#L317">317</a>         <a href="ident?i=WARN_ON">WARN_ON</a>(!answer_prot-&gt;<a href="ident?i=slab">slab</a>);
<a name="L318" href="source/net/ipv4/af_inet.c#L318">318</a> 
<a name="L319" href="source/net/ipv4/af_inet.c#L319">319</a>         <a href="ident?i=err">err</a> = -<a href="ident?i=ENOBUFS">ENOBUFS</a>;
<a name="L320" href="source/net/ipv4/af_inet.c#L320">320</a>         sk = <a href="ident?i=sk_alloc">sk_alloc</a>(<a href="ident?i=net">net</a>, <a href="ident?i=PF_INET">PF_INET</a>, <a href="ident?i=GFP_KERNEL">GFP_KERNEL</a>, answer_prot);
<a name="L321" href="source/net/ipv4/af_inet.c#L321">321</a>         if (!sk)
<a name="L322" href="source/net/ipv4/af_inet.c#L322">322</a>                 goto <a href="ident?i=out">out</a>;
<a name="L323" href="source/net/ipv4/af_inet.c#L323">323</a> 
<a name="L324" href="source/net/ipv4/af_inet.c#L324">324</a>         <a href="ident?i=err">err</a> = 0;
<a name="L325" href="source/net/ipv4/af_inet.c#L325">325</a>         if (<a href="ident?i=INET_PROTOSW_REUSE">INET_PROTOSW_REUSE</a> &amp; answer_flags)
<a name="L326" href="source/net/ipv4/af_inet.c#L326">326</a>                 sk-&gt;<a href="ident?i=sk_reuse">sk_reuse</a> = <a href="ident?i=SK_CAN_REUSE">SK_CAN_REUSE</a>;
<a name="L327" href="source/net/ipv4/af_inet.c#L327">327</a> 
<a name="L328" href="source/net/ipv4/af_inet.c#L328">328</a>         inet = <a href="ident?i=inet_sk">inet_sk</a>(sk);
<a name="L329" href="source/net/ipv4/af_inet.c#L329">329</a>         inet-&gt;is_icsk = (<a href="ident?i=INET_PROTOSW_ICSK">INET_PROTOSW_ICSK</a> &amp; answer_flags) != 0;
<a name="L330" href="source/net/ipv4/af_inet.c#L330">330</a> 
<a name="L331" href="source/net/ipv4/af_inet.c#L331">331</a>         inet-&gt;nodefrag = 0;
<a name="L332" href="source/net/ipv4/af_inet.c#L332">332</a> 
<a name="L333" href="source/net/ipv4/af_inet.c#L333">333</a>         if (SOCK_RAW == <a href="ident?i=sock">sock</a>-&gt;<a href="ident?i=type">type</a>) {
<a name="L334" href="source/net/ipv4/af_inet.c#L334">334</a>                 inet-&gt;<a href="ident?i=inet_num">inet_num</a> = <a href="ident?i=protocol">protocol</a>;
<a name="L335" href="source/net/ipv4/af_inet.c#L335">335</a>                 if (<a href="ident?i=IPPROTO_RAW">IPPROTO_RAW</a> == <a href="ident?i=protocol">protocol</a>)
<a name="L336" href="source/net/ipv4/af_inet.c#L336">336</a>                         inet-&gt;hdrincl = 1;
<a name="L337" href="source/net/ipv4/af_inet.c#L337">337</a>         }
<a name="L338" href="source/net/ipv4/af_inet.c#L338">338</a> 
<a name="L339" href="source/net/ipv4/af_inet.c#L339">339</a>         if (<a href="ident?i=net">net</a>-&gt;ipv4.sysctl_ip_no_pmtu_disc)
<a name="L340" href="source/net/ipv4/af_inet.c#L340">340</a>                 inet-&gt;pmtudisc = <a href="ident?i=IP_PMTUDISC_DONT">IP_PMTUDISC_DONT</a>;
<a name="L341" href="source/net/ipv4/af_inet.c#L341">341</a>         else
<a name="L342" href="source/net/ipv4/af_inet.c#L342">342</a>                 inet-&gt;pmtudisc = <a href="ident?i=IP_PMTUDISC_WANT">IP_PMTUDISC_WANT</a>;
<a name="L343" href="source/net/ipv4/af_inet.c#L343">343</a> 
<a name="L344" href="source/net/ipv4/af_inet.c#L344">344</a>         inet-&gt;inet_id = 0;
<a name="L345" href="source/net/ipv4/af_inet.c#L345">345</a> 
<a name="L346" href="source/net/ipv4/af_inet.c#L346">346</a>         <a href="ident?i=sock_init_data">sock_init_data</a>(<a href="ident?i=sock">sock</a>, sk);
<a name="L347" href="source/net/ipv4/af_inet.c#L347">347</a> 
<a name="L348" href="source/net/ipv4/af_inet.c#L348">348</a>         sk-&gt;sk_destruct    = <a href="ident?i=inet_sock_destruct">inet_sock_destruct</a>;
<a name="L349" href="source/net/ipv4/af_inet.c#L349">349</a>         sk-&gt;sk_protocol    = <a href="ident?i=protocol">protocol</a>;
<a name="L350" href="source/net/ipv4/af_inet.c#L350">350</a>         sk-&gt;<a href="ident?i=sk_backlog_rcv">sk_backlog_rcv</a> = sk-&gt;<a href="ident?i=sk_prot">sk_prot</a>-&gt;backlog_rcv;
<a name="L351" href="source/net/ipv4/af_inet.c#L351">351</a> 
<a name="L352" href="source/net/ipv4/af_inet.c#L352">352</a>         inet-&gt;uc_ttl    = -1;
<a name="L353" href="source/net/ipv4/af_inet.c#L353">353</a>         inet-&gt;mc_loop   = 1;
<a name="L354" href="source/net/ipv4/af_inet.c#L354">354</a>         inet-&gt;mc_ttl    = 1;
<a name="L355" href="source/net/ipv4/af_inet.c#L355">355</a>         inet-&gt;mc_all    = 1;
<a name="L356" href="source/net/ipv4/af_inet.c#L356">356</a>         inet-&gt;mc_index  = 0;
<a name="L357" href="source/net/ipv4/af_inet.c#L357">357</a>         inet-&gt;mc_list   = <a href="ident?i=NULL">NULL</a>;
<a name="L358" href="source/net/ipv4/af_inet.c#L358">358</a>         inet-&gt;rcv_tos   = 0;
<a name="L359" href="source/net/ipv4/af_inet.c#L359">359</a> 
<a name="L360" href="source/net/ipv4/af_inet.c#L360">360</a>         <a href="ident?i=sk_refcnt_debug_inc">sk_refcnt_debug_inc</a>(sk);
<a name="L361" href="source/net/ipv4/af_inet.c#L361">361</a> 
<a name="L362" href="source/net/ipv4/af_inet.c#L362">362</a>         if (inet-&gt;<a href="ident?i=inet_num">inet_num</a>) {
<a name="L363" href="source/net/ipv4/af_inet.c#L363">363</a>                 <b><i>/* It assumes that any protocol which allows</i></b>
<a name="L364" href="source/net/ipv4/af_inet.c#L364">364</a> <b><i>                 * the user to assign a number at socket</i></b>
<a name="L365" href="source/net/ipv4/af_inet.c#L365">365</a> <b><i>                 * creation time automatically</i></b>
<a name="L366" href="source/net/ipv4/af_inet.c#L366">366</a> <b><i>                 * shares.</i></b>
<a name="L367" href="source/net/ipv4/af_inet.c#L367">367</a> <b><i>                 */</i></b>
<a name="L368" href="source/net/ipv4/af_inet.c#L368">368</a>                 inet-&gt;inet_sport = <a href="ident?i=htons">htons</a>(inet-&gt;<a href="ident?i=inet_num">inet_num</a>);
<a name="L369" href="source/net/ipv4/af_inet.c#L369">369</a>                 <b><i>/* Add to protocol hash chains. */</i></b>
<a name="L370" href="source/net/ipv4/af_inet.c#L370">370</a>                 sk-&gt;<a href="ident?i=sk_prot">sk_prot</a>-&gt;<a href="ident?i=hash">hash</a>(sk);
<a name="L371" href="source/net/ipv4/af_inet.c#L371">371</a>         }
<a name="L372" href="source/net/ipv4/af_inet.c#L372">372</a> 
<a name="L373" href="source/net/ipv4/af_inet.c#L373">373</a>         if (sk-&gt;<a href="ident?i=sk_prot">sk_prot</a>-&gt;<a href="ident?i=init">init</a>) {
<a name="L374" href="source/net/ipv4/af_inet.c#L374">374</a>                 <a href="ident?i=err">err</a> = sk-&gt;<a href="ident?i=sk_prot">sk_prot</a>-&gt;<a href="ident?i=init">init</a>(sk);
<a name="L375" href="source/net/ipv4/af_inet.c#L375">375</a>                 if (<a href="ident?i=err">err</a>)
<a name="L376" href="source/net/ipv4/af_inet.c#L376">376</a>                         <a href="ident?i=sk_common_release">sk_common_release</a>(sk);
<a name="L377" href="source/net/ipv4/af_inet.c#L377">377</a>         }
<a name="L378" href="source/net/ipv4/af_inet.c#L378">378</a> <a href="ident?i=out">out</a>:
<a name="L379" href="source/net/ipv4/af_inet.c#L379">379</a>         return <a href="ident?i=err">err</a>;
<a name="L380" href="source/net/ipv4/af_inet.c#L380">380</a> out_rcu_unlock:
<a name="L381" href="source/net/ipv4/af_inet.c#L381">381</a>         <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L382" href="source/net/ipv4/af_inet.c#L382">382</a>         goto <a href="ident?i=out">out</a>;
<a name="L383" href="source/net/ipv4/af_inet.c#L383">383</a> }
<a name="L384" href="source/net/ipv4/af_inet.c#L384">384</a> 
<a name="L385" href="source/net/ipv4/af_inet.c#L385">385</a> 
<a name="L386" href="source/net/ipv4/af_inet.c#L386">386</a> <b><i>/*</i></b>
<a name="L387" href="source/net/ipv4/af_inet.c#L387">387</a> <b><i> *      The peer socket should always be NULL (or else). When we call this</i></b>
<a name="L388" href="source/net/ipv4/af_inet.c#L388">388</a> <b><i> *      function we are destroying the object and from then on nobody</i></b>
<a name="L389" href="source/net/ipv4/af_inet.c#L389">389</a> <b><i> *      should refer to it.</i></b>
<a name="L390" href="source/net/ipv4/af_inet.c#L390">390</a> <b><i> */</i></b>
<a name="L391" href="source/net/ipv4/af_inet.c#L391">391</a> int <a href="ident?i=inet_release">inet_release</a>(struct <a href="ident?i=socket">socket</a> *<a href="ident?i=sock">sock</a>)
<a name="L392" href="source/net/ipv4/af_inet.c#L392">392</a> {
<a name="L393" href="source/net/ipv4/af_inet.c#L393">393</a>         struct <a href="ident?i=sock">sock</a> *sk = <a href="ident?i=sock">sock</a>-&gt;sk;
<a name="L394" href="source/net/ipv4/af_inet.c#L394">394</a> 
<a name="L395" href="source/net/ipv4/af_inet.c#L395">395</a>         if (sk) {
<a name="L396" href="source/net/ipv4/af_inet.c#L396">396</a>                 long <a href="ident?i=timeout">timeout</a>;
<a name="L397" href="source/net/ipv4/af_inet.c#L397">397</a> 
<a name="L398" href="source/net/ipv4/af_inet.c#L398">398</a>                 <b><i>/* Applications forget to leave groups before exiting */</i></b>
<a name="L399" href="source/net/ipv4/af_inet.c#L399">399</a>                 <a href="ident?i=ip_mc_drop_socket">ip_mc_drop_socket</a>(sk);
<a name="L400" href="source/net/ipv4/af_inet.c#L400">400</a> 
<a name="L401" href="source/net/ipv4/af_inet.c#L401">401</a>                 <b><i>/* If linger is set, we don't return until the close</i></b>
<a name="L402" href="source/net/ipv4/af_inet.c#L402">402</a> <b><i>                 * is complete.  Otherwise we return immediately. The</i></b>
<a name="L403" href="source/net/ipv4/af_inet.c#L403">403</a> <b><i>                 * actually closing is done the same either way.</i></b>
<a name="L404" href="source/net/ipv4/af_inet.c#L404">404</a> <b><i>                 *</i></b>
<a name="L405" href="source/net/ipv4/af_inet.c#L405">405</a> <b><i>                 * If the close is due to the process exiting, we never</i></b>
<a name="L406" href="source/net/ipv4/af_inet.c#L406">406</a> <b><i>                 * linger..</i></b>
<a name="L407" href="source/net/ipv4/af_inet.c#L407">407</a> <b><i>                 */</i></b>
<a name="L408" href="source/net/ipv4/af_inet.c#L408">408</a>                 <a href="ident?i=timeout">timeout</a> = 0;
<a name="L409" href="source/net/ipv4/af_inet.c#L409">409</a>                 if (<a href="ident?i=sock_flag">sock_flag</a>(sk, SOCK_LINGER) &amp;&amp;
<a name="L410" href="source/net/ipv4/af_inet.c#L410">410</a>                     !(<a href="ident?i=current">current</a>-&gt;<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=PF_EXITING">PF_EXITING</a>))
<a name="L411" href="source/net/ipv4/af_inet.c#L411">411</a>                         <a href="ident?i=timeout">timeout</a> = sk-&gt;sk_lingertime;
<a name="L412" href="source/net/ipv4/af_inet.c#L412">412</a>                 <a href="ident?i=sock">sock</a>-&gt;sk = <a href="ident?i=NULL">NULL</a>;
<a name="L413" href="source/net/ipv4/af_inet.c#L413">413</a>                 sk-&gt;<a href="ident?i=sk_prot">sk_prot</a>-&gt;<a href="ident?i=close">close</a>(sk, <a href="ident?i=timeout">timeout</a>);
<a name="L414" href="source/net/ipv4/af_inet.c#L414">414</a>         }
<a name="L415" href="source/net/ipv4/af_inet.c#L415">415</a>         return 0;
<a name="L416" href="source/net/ipv4/af_inet.c#L416">416</a> }
<a name="L417" href="source/net/ipv4/af_inet.c#L417">417</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=inet_release">inet_release</a>);
<a name="L418" href="source/net/ipv4/af_inet.c#L418">418</a> 
<a name="L419" href="source/net/ipv4/af_inet.c#L419">419</a> int <a href="ident?i=inet_bind">inet_bind</a>(struct <a href="ident?i=socket">socket</a> *<a href="ident?i=sock">sock</a>, struct <a href="ident?i=sockaddr">sockaddr</a> *<a href="ident?i=uaddr">uaddr</a>, int addr_len)
<a name="L420" href="source/net/ipv4/af_inet.c#L420">420</a> {
<a name="L421" href="source/net/ipv4/af_inet.c#L421">421</a>         struct <a href="ident?i=sockaddr_in">sockaddr_in</a> *<a href="ident?i=addr">addr</a> = (struct <a href="ident?i=sockaddr_in">sockaddr_in</a> *)<a href="ident?i=uaddr">uaddr</a>;
<a name="L422" href="source/net/ipv4/af_inet.c#L422">422</a>         struct <a href="ident?i=sock">sock</a> *sk = <a href="ident?i=sock">sock</a>-&gt;sk;
<a name="L423" href="source/net/ipv4/af_inet.c#L423">423</a>         struct <a href="ident?i=inet_sock">inet_sock</a> *inet = <a href="ident?i=inet_sk">inet_sk</a>(sk);
<a name="L424" href="source/net/ipv4/af_inet.c#L424">424</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=sock_net">sock_net</a>(sk);
<a name="L425" href="source/net/ipv4/af_inet.c#L425">425</a>         unsigned short snum;
<a name="L426" href="source/net/ipv4/af_inet.c#L426">426</a>         int chk_addr_ret;
<a name="L427" href="source/net/ipv4/af_inet.c#L427">427</a>         int <a href="ident?i=err">err</a>;
<a name="L428" href="source/net/ipv4/af_inet.c#L428">428</a> 
<a name="L429" href="source/net/ipv4/af_inet.c#L429">429</a>         <b><i>/* If the socket has its own bind function then use it. (RAW) */</i></b>
<a name="L430" href="source/net/ipv4/af_inet.c#L430">430</a>         if (sk-&gt;<a href="ident?i=sk_prot">sk_prot</a>-&gt;bind) {
<a name="L431" href="source/net/ipv4/af_inet.c#L431">431</a>                 <a href="ident?i=err">err</a> = sk-&gt;<a href="ident?i=sk_prot">sk_prot</a>-&gt;bind(sk, <a href="ident?i=uaddr">uaddr</a>, addr_len);
<a name="L432" href="source/net/ipv4/af_inet.c#L432">432</a>                 goto <a href="ident?i=out">out</a>;
<a name="L433" href="source/net/ipv4/af_inet.c#L433">433</a>         }
<a name="L434" href="source/net/ipv4/af_inet.c#L434">434</a>         <a href="ident?i=err">err</a> = -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L435" href="source/net/ipv4/af_inet.c#L435">435</a>         if (addr_len &lt; sizeof(struct <a href="ident?i=sockaddr_in">sockaddr_in</a>))
<a name="L436" href="source/net/ipv4/af_inet.c#L436">436</a>                 goto <a href="ident?i=out">out</a>;
<a name="L437" href="source/net/ipv4/af_inet.c#L437">437</a> 
<a name="L438" href="source/net/ipv4/af_inet.c#L438">438</a>         if (<a href="ident?i=addr">addr</a>-&gt;sin_family != <a href="ident?i=AF_INET">AF_INET</a>) {
<a name="L439" href="source/net/ipv4/af_inet.c#L439">439</a>                 <b><i>/* Compatibility games : accept AF_UNSPEC (mapped to AF_INET)</i></b>
<a name="L440" href="source/net/ipv4/af_inet.c#L440">440</a> <b><i>                 * only if s_addr is INADDR_ANY.</i></b>
<a name="L441" href="source/net/ipv4/af_inet.c#L441">441</a> <b><i>                 */</i></b>
<a name="L442" href="source/net/ipv4/af_inet.c#L442">442</a>                 <a href="ident?i=err">err</a> = -<a href="ident?i=EAFNOSUPPORT">EAFNOSUPPORT</a>;
<a name="L443" href="source/net/ipv4/af_inet.c#L443">443</a>                 if (<a href="ident?i=addr">addr</a>-&gt;sin_family != <a href="ident?i=AF_UNSPEC">AF_UNSPEC</a> ||
<a name="L444" href="source/net/ipv4/af_inet.c#L444">444</a>                     <a href="ident?i=addr">addr</a>-&gt;sin_addr.s_addr != <a href="ident?i=htonl">htonl</a>(<a href="ident?i=INADDR_ANY">INADDR_ANY</a>))
<a name="L445" href="source/net/ipv4/af_inet.c#L445">445</a>                         goto <a href="ident?i=out">out</a>;
<a name="L446" href="source/net/ipv4/af_inet.c#L446">446</a>         }
<a name="L447" href="source/net/ipv4/af_inet.c#L447">447</a> 
<a name="L448" href="source/net/ipv4/af_inet.c#L448">448</a>         chk_addr_ret = <a href="ident?i=inet_addr_type">inet_addr_type</a>(<a href="ident?i=net">net</a>, <a href="ident?i=addr">addr</a>-&gt;sin_addr.s_addr);
<a name="L449" href="source/net/ipv4/af_inet.c#L449">449</a> 
<a name="L450" href="source/net/ipv4/af_inet.c#L450">450</a>         <b><i>/* Not specified by any standard per-se, however it breaks too</i></b>
<a name="L451" href="source/net/ipv4/af_inet.c#L451">451</a> <b><i>         * many applications when removed.  It is unfortunate since</i></b>
<a name="L452" href="source/net/ipv4/af_inet.c#L452">452</a> <b><i>         * allowing applications to make a non-local bind solves</i></b>
<a name="L453" href="source/net/ipv4/af_inet.c#L453">453</a> <b><i>         * several problems with systems using dynamic addressing.</i></b>
<a name="L454" href="source/net/ipv4/af_inet.c#L454">454</a> <b><i>         * (ie. your servers still start up even if your ISDN link</i></b>
<a name="L455" href="source/net/ipv4/af_inet.c#L455">455</a> <b><i>         *  is temporarily down)</i></b>
<a name="L456" href="source/net/ipv4/af_inet.c#L456">456</a> <b><i>         */</i></b>
<a name="L457" href="source/net/ipv4/af_inet.c#L457">457</a>         <a href="ident?i=err">err</a> = -<a href="ident?i=EADDRNOTAVAIL">EADDRNOTAVAIL</a>;
<a name="L458" href="source/net/ipv4/af_inet.c#L458">458</a>         if (!<a href="ident?i=net">net</a>-&gt;ipv4.sysctl_ip_nonlocal_bind &amp;&amp;
<a name="L459" href="source/net/ipv4/af_inet.c#L459">459</a>             !(inet-&gt;freebind || inet-&gt;transparent) &amp;&amp;
<a name="L460" href="source/net/ipv4/af_inet.c#L460">460</a>             <a href="ident?i=addr">addr</a>-&gt;sin_addr.s_addr != <a href="ident?i=htonl">htonl</a>(<a href="ident?i=INADDR_ANY">INADDR_ANY</a>) &amp;&amp;
<a name="L461" href="source/net/ipv4/af_inet.c#L461">461</a>             chk_addr_ret != RTN_LOCAL &amp;&amp;
<a name="L462" href="source/net/ipv4/af_inet.c#L462">462</a>             chk_addr_ret != RTN_MULTICAST &amp;&amp;
<a name="L463" href="source/net/ipv4/af_inet.c#L463">463</a>             chk_addr_ret != RTN_BROADCAST)
<a name="L464" href="source/net/ipv4/af_inet.c#L464">464</a>                 goto <a href="ident?i=out">out</a>;
<a name="L465" href="source/net/ipv4/af_inet.c#L465">465</a> 
<a name="L466" href="source/net/ipv4/af_inet.c#L466">466</a>         snum = <a href="ident?i=ntohs">ntohs</a>(<a href="ident?i=addr">addr</a>-&gt;sin_port);
<a name="L467" href="source/net/ipv4/af_inet.c#L467">467</a>         <a href="ident?i=err">err</a> = -<a href="ident?i=EACCES">EACCES</a>;
<a name="L468" href="source/net/ipv4/af_inet.c#L468">468</a>         if (snum &amp;&amp; snum &lt; <a href="ident?i=PROT_SOCK">PROT_SOCK</a> &amp;&amp;
<a name="L469" href="source/net/ipv4/af_inet.c#L469">469</a>             !<a href="ident?i=ns_capable">ns_capable</a>(<a href="ident?i=net">net</a>-&gt;<a href="ident?i=user_ns">user_ns</a>, <a href="ident?i=CAP_NET_BIND_SERVICE">CAP_NET_BIND_SERVICE</a>))
<a name="L470" href="source/net/ipv4/af_inet.c#L470">470</a>                 goto <a href="ident?i=out">out</a>;
<a name="L471" href="source/net/ipv4/af_inet.c#L471">471</a> 
<a name="L472" href="source/net/ipv4/af_inet.c#L472">472</a>         <b><i>/*      We keep a pair of addresses. rcv_saddr is the one</i></b>
<a name="L473" href="source/net/ipv4/af_inet.c#L473">473</a> <b><i>         *      used by hash lookups, and saddr is used for transmit.</i></b>
<a name="L474" href="source/net/ipv4/af_inet.c#L474">474</a> <b><i>         *</i></b>
<a name="L475" href="source/net/ipv4/af_inet.c#L475">475</a> <b><i>         *      In the BSD API these are the same except where it</i></b>
<a name="L476" href="source/net/ipv4/af_inet.c#L476">476</a> <b><i>         *      would be illegal to use them (multicast/broadcast) in</i></b>
<a name="L477" href="source/net/ipv4/af_inet.c#L477">477</a> <b><i>         *      which case the sending device address is used.</i></b>
<a name="L478" href="source/net/ipv4/af_inet.c#L478">478</a> <b><i>         */</i></b>
<a name="L479" href="source/net/ipv4/af_inet.c#L479">479</a>         <a href="ident?i=lock_sock">lock_sock</a>(sk);
<a name="L480" href="source/net/ipv4/af_inet.c#L480">480</a> 
<a name="L481" href="source/net/ipv4/af_inet.c#L481">481</a>         <b><i>/* Check these errors (active socket, double bind). */</i></b>
<a name="L482" href="source/net/ipv4/af_inet.c#L482">482</a>         <a href="ident?i=err">err</a> = -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L483" href="source/net/ipv4/af_inet.c#L483">483</a>         if (sk-&gt;<a href="ident?i=sk_state">sk_state</a> != TCP_CLOSE || inet-&gt;<a href="ident?i=inet_num">inet_num</a>)
<a name="L484" href="source/net/ipv4/af_inet.c#L484">484</a>                 goto out_release_sock;
<a name="L485" href="source/net/ipv4/af_inet.c#L485">485</a> 
<a name="L486" href="source/net/ipv4/af_inet.c#L486">486</a>         inet-&gt;<a href="ident?i=inet_rcv_saddr">inet_rcv_saddr</a> = inet-&gt;inet_saddr = <a href="ident?i=addr">addr</a>-&gt;sin_addr.s_addr;
<a name="L487" href="source/net/ipv4/af_inet.c#L487">487</a>         if (chk_addr_ret == RTN_MULTICAST || chk_addr_ret == RTN_BROADCAST)
<a name="L488" href="source/net/ipv4/af_inet.c#L488">488</a>                 inet-&gt;inet_saddr = 0;  <b><i>/* Use device */</i></b>
<a name="L489" href="source/net/ipv4/af_inet.c#L489">489</a> 
<a name="L490" href="source/net/ipv4/af_inet.c#L490">490</a>         <b><i>/* Make sure we are allowed to bind here. */</i></b>
<a name="L491" href="source/net/ipv4/af_inet.c#L491">491</a>         if (sk-&gt;<a href="ident?i=sk_prot">sk_prot</a>-&gt;<a href="ident?i=get_port">get_port</a>(sk, snum)) {
<a name="L492" href="source/net/ipv4/af_inet.c#L492">492</a>                 inet-&gt;inet_saddr = inet-&gt;<a href="ident?i=inet_rcv_saddr">inet_rcv_saddr</a> = 0;
<a name="L493" href="source/net/ipv4/af_inet.c#L493">493</a>                 <a href="ident?i=err">err</a> = -<a href="ident?i=EADDRINUSE">EADDRINUSE</a>;
<a name="L494" href="source/net/ipv4/af_inet.c#L494">494</a>                 goto out_release_sock;
<a name="L495" href="source/net/ipv4/af_inet.c#L495">495</a>         }
<a name="L496" href="source/net/ipv4/af_inet.c#L496">496</a> 
<a name="L497" href="source/net/ipv4/af_inet.c#L497">497</a>         if (inet-&gt;<a href="ident?i=inet_rcv_saddr">inet_rcv_saddr</a>)
<a name="L498" href="source/net/ipv4/af_inet.c#L498">498</a>                 sk-&gt;sk_userlocks |= <a href="ident?i=SOCK_BINDADDR_LOCK">SOCK_BINDADDR_LOCK</a>;
<a name="L499" href="source/net/ipv4/af_inet.c#L499">499</a>         if (snum)
<a name="L500" href="source/net/ipv4/af_inet.c#L500">500</a>                 sk-&gt;sk_userlocks |= <a href="ident?i=SOCK_BINDPORT_LOCK">SOCK_BINDPORT_LOCK</a>;
<a name="L501" href="source/net/ipv4/af_inet.c#L501">501</a>         inet-&gt;inet_sport = <a href="ident?i=htons">htons</a>(inet-&gt;<a href="ident?i=inet_num">inet_num</a>);
<a name="L502" href="source/net/ipv4/af_inet.c#L502">502</a>         inet-&gt;<a href="ident?i=inet_daddr">inet_daddr</a> = 0;
<a name="L503" href="source/net/ipv4/af_inet.c#L503">503</a>         inet-&gt;<a href="ident?i=inet_dport">inet_dport</a> = 0;
<a name="L504" href="source/net/ipv4/af_inet.c#L504">504</a>         <a href="ident?i=sk_dst_reset">sk_dst_reset</a>(sk);
<a name="L505" href="source/net/ipv4/af_inet.c#L505">505</a>         <a href="ident?i=err">err</a> = 0;
<a name="L506" href="source/net/ipv4/af_inet.c#L506">506</a> out_release_sock:
<a name="L507" href="source/net/ipv4/af_inet.c#L507">507</a>         <a href="ident?i=release_sock">release_sock</a>(sk);
<a name="L508" href="source/net/ipv4/af_inet.c#L508">508</a> <a href="ident?i=out">out</a>:
<a name="L509" href="source/net/ipv4/af_inet.c#L509">509</a>         return <a href="ident?i=err">err</a>;
<a name="L510" href="source/net/ipv4/af_inet.c#L510">510</a> }
<a name="L511" href="source/net/ipv4/af_inet.c#L511">511</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=inet_bind">inet_bind</a>);
<a name="L512" href="source/net/ipv4/af_inet.c#L512">512</a> 
<a name="L513" href="source/net/ipv4/af_inet.c#L513">513</a> int <a href="ident?i=inet_dgram_connect">inet_dgram_connect</a>(struct <a href="ident?i=socket">socket</a> *<a href="ident?i=sock">sock</a>, struct <a href="ident?i=sockaddr">sockaddr</a> *<a href="ident?i=uaddr">uaddr</a>,
<a name="L514" href="source/net/ipv4/af_inet.c#L514">514</a>                        int addr_len, int <a href="ident?i=flags">flags</a>)
<a name="L515" href="source/net/ipv4/af_inet.c#L515">515</a> {
<a name="L516" href="source/net/ipv4/af_inet.c#L516">516</a>         struct <a href="ident?i=sock">sock</a> *sk = <a href="ident?i=sock">sock</a>-&gt;sk;
<a name="L517" href="source/net/ipv4/af_inet.c#L517">517</a> 
<a name="L518" href="source/net/ipv4/af_inet.c#L518">518</a>         if (addr_len &lt; sizeof(<a href="ident?i=uaddr">uaddr</a>-&gt;sa_family))
<a name="L519" href="source/net/ipv4/af_inet.c#L519">519</a>                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L520" href="source/net/ipv4/af_inet.c#L520">520</a>         if (<a href="ident?i=uaddr">uaddr</a>-&gt;sa_family == <a href="ident?i=AF_UNSPEC">AF_UNSPEC</a>)
<a name="L521" href="source/net/ipv4/af_inet.c#L521">521</a>                 return sk-&gt;<a href="ident?i=sk_prot">sk_prot</a>-&gt;<a href="ident?i=disconnect">disconnect</a>(sk, <a href="ident?i=flags">flags</a>);
<a name="L522" href="source/net/ipv4/af_inet.c#L522">522</a> 
<a name="L523" href="source/net/ipv4/af_inet.c#L523">523</a>         if (!<a href="ident?i=inet_sk">inet_sk</a>(sk)-&gt;<a href="ident?i=inet_num">inet_num</a> &amp;&amp; <a href="ident?i=inet_autobind">inet_autobind</a>(sk))
<a name="L524" href="source/net/ipv4/af_inet.c#L524">524</a>                 return -<a href="ident?i=EAGAIN">EAGAIN</a>;
<a name="L525" href="source/net/ipv4/af_inet.c#L525">525</a>         return sk-&gt;<a href="ident?i=sk_prot">sk_prot</a>-&gt;<a href="ident?i=connect">connect</a>(sk, <a href="ident?i=uaddr">uaddr</a>, addr_len);
<a name="L526" href="source/net/ipv4/af_inet.c#L526">526</a> }
<a name="L527" href="source/net/ipv4/af_inet.c#L527">527</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=inet_dgram_connect">inet_dgram_connect</a>);
<a name="L528" href="source/net/ipv4/af_inet.c#L528">528</a> 
<a name="L529" href="source/net/ipv4/af_inet.c#L529">529</a> static long <a href="ident?i=inet_wait_for_connect">inet_wait_for_connect</a>(struct <a href="ident?i=sock">sock</a> *sk, long timeo, int writebias)
<a name="L530" href="source/net/ipv4/af_inet.c#L530">530</a> {
<a name="L531" href="source/net/ipv4/af_inet.c#L531">531</a>         <a href="ident?i=DEFINE_WAIT">DEFINE_WAIT</a>(<a href="ident?i=wait">wait</a>);
<a name="L532" href="source/net/ipv4/af_inet.c#L532">532</a> 
<a name="L533" href="source/net/ipv4/af_inet.c#L533">533</a>         <a href="ident?i=prepare_to_wait">prepare_to_wait</a>(<a href="ident?i=sk_sleep">sk_sleep</a>(sk), &amp;<a href="ident?i=wait">wait</a>, <a href="ident?i=TASK_INTERRUPTIBLE">TASK_INTERRUPTIBLE</a>);
<a name="L534" href="source/net/ipv4/af_inet.c#L534">534</a>         sk-&gt;sk_write_pending += writebias;
<a name="L535" href="source/net/ipv4/af_inet.c#L535">535</a> 
<a name="L536" href="source/net/ipv4/af_inet.c#L536">536</a>         <b><i>/* Basic assumption: if someone sets sk-&gt;sk_err, he _must_</i></b>
<a name="L537" href="source/net/ipv4/af_inet.c#L537">537</a> <b><i>         * change state of the socket from TCP_SYN_*.</i></b>
<a name="L538" href="source/net/ipv4/af_inet.c#L538">538</a> <b><i>         * Connect() does not allow to get error notifications</i></b>
<a name="L539" href="source/net/ipv4/af_inet.c#L539">539</a> <b><i>         * without closing the socket.</i></b>
<a name="L540" href="source/net/ipv4/af_inet.c#L540">540</a> <b><i>         */</i></b>
<a name="L541" href="source/net/ipv4/af_inet.c#L541">541</a>         while ((1 &lt;&lt; sk-&gt;<a href="ident?i=sk_state">sk_state</a>) &amp; (TCPF_SYN_SENT | TCPF_SYN_RECV)) {
<a name="L542" href="source/net/ipv4/af_inet.c#L542">542</a>                 <a href="ident?i=release_sock">release_sock</a>(sk);
<a name="L543" href="source/net/ipv4/af_inet.c#L543">543</a>                 timeo = <a href="ident?i=schedule_timeout">schedule_timeout</a>(timeo);
<a name="L544" href="source/net/ipv4/af_inet.c#L544">544</a>                 <a href="ident?i=lock_sock">lock_sock</a>(sk);
<a name="L545" href="source/net/ipv4/af_inet.c#L545">545</a>                 if (<a href="ident?i=signal_pending">signal_pending</a>(<a href="ident?i=current">current</a>) || !timeo)
<a name="L546" href="source/net/ipv4/af_inet.c#L546">546</a>                         break;
<a name="L547" href="source/net/ipv4/af_inet.c#L547">547</a>                 <a href="ident?i=prepare_to_wait">prepare_to_wait</a>(<a href="ident?i=sk_sleep">sk_sleep</a>(sk), &amp;<a href="ident?i=wait">wait</a>, <a href="ident?i=TASK_INTERRUPTIBLE">TASK_INTERRUPTIBLE</a>);
<a name="L548" href="source/net/ipv4/af_inet.c#L548">548</a>         }
<a name="L549" href="source/net/ipv4/af_inet.c#L549">549</a>         <a href="ident?i=finish_wait">finish_wait</a>(<a href="ident?i=sk_sleep">sk_sleep</a>(sk), &amp;<a href="ident?i=wait">wait</a>);
<a name="L550" href="source/net/ipv4/af_inet.c#L550">550</a>         sk-&gt;sk_write_pending -= writebias;
<a name="L551" href="source/net/ipv4/af_inet.c#L551">551</a>         return timeo;
<a name="L552" href="source/net/ipv4/af_inet.c#L552">552</a> }
<a name="L553" href="source/net/ipv4/af_inet.c#L553">553</a> 
<a name="L554" href="source/net/ipv4/af_inet.c#L554">554</a> <b><i>/*</i></b>
<a name="L555" href="source/net/ipv4/af_inet.c#L555">555</a> <b><i> *      Connect to a remote host. There is regrettably still a little</i></b>
<a name="L556" href="source/net/ipv4/af_inet.c#L556">556</a> <b><i> *      TCP 'magic' in here.</i></b>
<a name="L557" href="source/net/ipv4/af_inet.c#L557">557</a> <b><i> */</i></b>
<a name="L558" href="source/net/ipv4/af_inet.c#L558">558</a> int <a href="ident?i=__inet_stream_connect">__inet_stream_connect</a>(struct <a href="ident?i=socket">socket</a> *<a href="ident?i=sock">sock</a>, struct <a href="ident?i=sockaddr">sockaddr</a> *<a href="ident?i=uaddr">uaddr</a>,
<a name="L559" href="source/net/ipv4/af_inet.c#L559">559</a>                           int addr_len, int <a href="ident?i=flags">flags</a>)
<a name="L560" href="source/net/ipv4/af_inet.c#L560">560</a> {
<a name="L561" href="source/net/ipv4/af_inet.c#L561">561</a>         struct <a href="ident?i=sock">sock</a> *sk = <a href="ident?i=sock">sock</a>-&gt;sk;
<a name="L562" href="source/net/ipv4/af_inet.c#L562">562</a>         int <a href="ident?i=err">err</a>;
<a name="L563" href="source/net/ipv4/af_inet.c#L563">563</a>         long timeo;
<a name="L564" href="source/net/ipv4/af_inet.c#L564">564</a> 
<a name="L565" href="source/net/ipv4/af_inet.c#L565">565</a>         if (addr_len &lt; sizeof(<a href="ident?i=uaddr">uaddr</a>-&gt;sa_family))
<a name="L566" href="source/net/ipv4/af_inet.c#L566">566</a>                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L567" href="source/net/ipv4/af_inet.c#L567">567</a> 
<a name="L568" href="source/net/ipv4/af_inet.c#L568">568</a>         if (<a href="ident?i=uaddr">uaddr</a>-&gt;sa_family == <a href="ident?i=AF_UNSPEC">AF_UNSPEC</a>) {
<a name="L569" href="source/net/ipv4/af_inet.c#L569">569</a>                 <a href="ident?i=err">err</a> = sk-&gt;<a href="ident?i=sk_prot">sk_prot</a>-&gt;<a href="ident?i=disconnect">disconnect</a>(sk, <a href="ident?i=flags">flags</a>);
<a name="L570" href="source/net/ipv4/af_inet.c#L570">570</a>                 <a href="ident?i=sock">sock</a>-&gt;<a href="ident?i=state">state</a> = <a href="ident?i=err">err</a> ? SS_DISCONNECTING : SS_UNCONNECTED;
<a name="L571" href="source/net/ipv4/af_inet.c#L571">571</a>                 goto <a href="ident?i=out">out</a>;
<a name="L572" href="source/net/ipv4/af_inet.c#L572">572</a>         }
<a name="L573" href="source/net/ipv4/af_inet.c#L573">573</a> 
<a name="L574" href="source/net/ipv4/af_inet.c#L574">574</a>         switch (<a href="ident?i=sock">sock</a>-&gt;<a href="ident?i=state">state</a>) {
<a name="L575" href="source/net/ipv4/af_inet.c#L575">575</a>         default:
<a name="L576" href="source/net/ipv4/af_inet.c#L576">576</a>                 <a href="ident?i=err">err</a> = -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L577" href="source/net/ipv4/af_inet.c#L577">577</a>                 goto <a href="ident?i=out">out</a>;
<a name="L578" href="source/net/ipv4/af_inet.c#L578">578</a>         case SS_CONNECTED:
<a name="L579" href="source/net/ipv4/af_inet.c#L579">579</a>                 <a href="ident?i=err">err</a> = -<a href="ident?i=EISCONN">EISCONN</a>;
<a name="L580" href="source/net/ipv4/af_inet.c#L580">580</a>                 goto <a href="ident?i=out">out</a>;
<a name="L581" href="source/net/ipv4/af_inet.c#L581">581</a>         case SS_CONNECTING:
<a name="L582" href="source/net/ipv4/af_inet.c#L582">582</a>                 <a href="ident?i=err">err</a> = -<a href="ident?i=EALREADY">EALREADY</a>;
<a name="L583" href="source/net/ipv4/af_inet.c#L583">583</a>                 <b><i>/* Fall out of switch with err, set for this state */</i></b>
<a name="L584" href="source/net/ipv4/af_inet.c#L584">584</a>                 break;
<a name="L585" href="source/net/ipv4/af_inet.c#L585">585</a>         case SS_UNCONNECTED:
<a name="L586" href="source/net/ipv4/af_inet.c#L586">586</a>                 <a href="ident?i=err">err</a> = -<a href="ident?i=EISCONN">EISCONN</a>;
<a name="L587" href="source/net/ipv4/af_inet.c#L587">587</a>                 if (sk-&gt;<a href="ident?i=sk_state">sk_state</a> != TCP_CLOSE)
<a name="L588" href="source/net/ipv4/af_inet.c#L588">588</a>                         goto <a href="ident?i=out">out</a>;
<a name="L589" href="source/net/ipv4/af_inet.c#L589">589</a> 
<a name="L590" href="source/net/ipv4/af_inet.c#L590">590</a>                 <a href="ident?i=err">err</a> = sk-&gt;<a href="ident?i=sk_prot">sk_prot</a>-&gt;<a href="ident?i=connect">connect</a>(sk, <a href="ident?i=uaddr">uaddr</a>, addr_len);
<a name="L591" href="source/net/ipv4/af_inet.c#L591">591</a>                 if (<a href="ident?i=err">err</a> &lt; 0)
<a name="L592" href="source/net/ipv4/af_inet.c#L592">592</a>                         goto <a href="ident?i=out">out</a>;
<a name="L593" href="source/net/ipv4/af_inet.c#L593">593</a> 
<a name="L594" href="source/net/ipv4/af_inet.c#L594">594</a>                 <a href="ident?i=sock">sock</a>-&gt;<a href="ident?i=state">state</a> = SS_CONNECTING;
<a name="L595" href="source/net/ipv4/af_inet.c#L595">595</a> 
<a name="L596" href="source/net/ipv4/af_inet.c#L596">596</a>                 <b><i>/* Just entered SS_CONNECTING state; the only</i></b>
<a name="L597" href="source/net/ipv4/af_inet.c#L597">597</a> <b><i>                 * difference is that return value in non-blocking</i></b>
<a name="L598" href="source/net/ipv4/af_inet.c#L598">598</a> <b><i>                 * case is EINPROGRESS, rather than EALREADY.</i></b>
<a name="L599" href="source/net/ipv4/af_inet.c#L599">599</a> <b><i>                 */</i></b>
<a name="L600" href="source/net/ipv4/af_inet.c#L600">600</a>                 <a href="ident?i=err">err</a> = -<a href="ident?i=EINPROGRESS">EINPROGRESS</a>;
<a name="L601" href="source/net/ipv4/af_inet.c#L601">601</a>                 break;
<a name="L602" href="source/net/ipv4/af_inet.c#L602">602</a>         }
<a name="L603" href="source/net/ipv4/af_inet.c#L603">603</a> 
<a name="L604" href="source/net/ipv4/af_inet.c#L604">604</a>         timeo = <a href="ident?i=sock_sndtimeo">sock_sndtimeo</a>(sk, <a href="ident?i=flags">flags</a> &amp; <a href="ident?i=O_NONBLOCK">O_NONBLOCK</a>);
<a name="L605" href="source/net/ipv4/af_inet.c#L605">605</a> 
<a name="L606" href="source/net/ipv4/af_inet.c#L606">606</a>         if ((1 &lt;&lt; sk-&gt;<a href="ident?i=sk_state">sk_state</a>) &amp; (TCPF_SYN_SENT | TCPF_SYN_RECV)) {
<a name="L607" href="source/net/ipv4/af_inet.c#L607">607</a>                 int writebias = (sk-&gt;sk_protocol == <a href="ident?i=IPPROTO_TCP">IPPROTO_TCP</a>) &amp;&amp;
<a name="L608" href="source/net/ipv4/af_inet.c#L608">608</a>                                 <a href="ident?i=tcp_sk">tcp_sk</a>(sk)-&gt;fastopen_req &amp;&amp;
<a name="L609" href="source/net/ipv4/af_inet.c#L609">609</a>                                 <a href="ident?i=tcp_sk">tcp_sk</a>(sk)-&gt;fastopen_req-&gt;<a href="ident?i=data">data</a> ? 1 : 0;
<a name="L610" href="source/net/ipv4/af_inet.c#L610">610</a> 
<a name="L611" href="source/net/ipv4/af_inet.c#L611">611</a>                 <b><i>/* Error code is set above */</i></b>
<a name="L612" href="source/net/ipv4/af_inet.c#L612">612</a>                 if (!timeo || !<a href="ident?i=inet_wait_for_connect">inet_wait_for_connect</a>(sk, timeo, writebias))
<a name="L613" href="source/net/ipv4/af_inet.c#L613">613</a>                         goto <a href="ident?i=out">out</a>;
<a name="L614" href="source/net/ipv4/af_inet.c#L614">614</a> 
<a name="L615" href="source/net/ipv4/af_inet.c#L615">615</a>                 <a href="ident?i=err">err</a> = <a href="ident?i=sock_intr_errno">sock_intr_errno</a>(timeo);
<a name="L616" href="source/net/ipv4/af_inet.c#L616">616</a>                 if (<a href="ident?i=signal_pending">signal_pending</a>(<a href="ident?i=current">current</a>))
<a name="L617" href="source/net/ipv4/af_inet.c#L617">617</a>                         goto <a href="ident?i=out">out</a>;
<a name="L618" href="source/net/ipv4/af_inet.c#L618">618</a>         }
<a name="L619" href="source/net/ipv4/af_inet.c#L619">619</a> 
<a name="L620" href="source/net/ipv4/af_inet.c#L620">620</a>         <b><i>/* Connection was closed by RST, timeout, ICMP error</i></b>
<a name="L621" href="source/net/ipv4/af_inet.c#L621">621</a> <b><i>         * or another process disconnected us.</i></b>
<a name="L622" href="source/net/ipv4/af_inet.c#L622">622</a> <b><i>         */</i></b>
<a name="L623" href="source/net/ipv4/af_inet.c#L623">623</a>         if (sk-&gt;<a href="ident?i=sk_state">sk_state</a> == TCP_CLOSE)
<a name="L624" href="source/net/ipv4/af_inet.c#L624">624</a>                 goto <a href="ident?i=sock_error">sock_error</a>;
<a name="L625" href="source/net/ipv4/af_inet.c#L625">625</a> 
<a name="L626" href="source/net/ipv4/af_inet.c#L626">626</a>         <b><i>/* sk-&gt;sk_err may be not zero now, if RECVERR was ordered by user</i></b>
<a name="L627" href="source/net/ipv4/af_inet.c#L627">627</a> <b><i>         * and error was received after socket entered established state.</i></b>
<a name="L628" href="source/net/ipv4/af_inet.c#L628">628</a> <b><i>         * Hence, it is handled normally after connect() return successfully.</i></b>
<a name="L629" href="source/net/ipv4/af_inet.c#L629">629</a> <b><i>         */</i></b>
<a name="L630" href="source/net/ipv4/af_inet.c#L630">630</a> 
<a name="L631" href="source/net/ipv4/af_inet.c#L631">631</a>         <a href="ident?i=sock">sock</a>-&gt;<a href="ident?i=state">state</a> = SS_CONNECTED;
<a name="L632" href="source/net/ipv4/af_inet.c#L632">632</a>         <a href="ident?i=err">err</a> = 0;
<a name="L633" href="source/net/ipv4/af_inet.c#L633">633</a> <a href="ident?i=out">out</a>:
<a name="L634" href="source/net/ipv4/af_inet.c#L634">634</a>         return <a href="ident?i=err">err</a>;
<a name="L635" href="source/net/ipv4/af_inet.c#L635">635</a> 
<a name="L636" href="source/net/ipv4/af_inet.c#L636">636</a> <a href="ident?i=sock_error">sock_error</a>:
<a name="L637" href="source/net/ipv4/af_inet.c#L637">637</a>         <a href="ident?i=err">err</a> = <a href="ident?i=sock_error">sock_error</a>(sk) ? : -<a href="ident?i=ECONNABORTED">ECONNABORTED</a>;
<a name="L638" href="source/net/ipv4/af_inet.c#L638">638</a>         <a href="ident?i=sock">sock</a>-&gt;<a href="ident?i=state">state</a> = SS_UNCONNECTED;
<a name="L639" href="source/net/ipv4/af_inet.c#L639">639</a>         if (sk-&gt;<a href="ident?i=sk_prot">sk_prot</a>-&gt;<a href="ident?i=disconnect">disconnect</a>(sk, <a href="ident?i=flags">flags</a>))
<a name="L640" href="source/net/ipv4/af_inet.c#L640">640</a>                 <a href="ident?i=sock">sock</a>-&gt;<a href="ident?i=state">state</a> = SS_DISCONNECTING;
<a name="L641" href="source/net/ipv4/af_inet.c#L641">641</a>         goto <a href="ident?i=out">out</a>;
<a name="L642" href="source/net/ipv4/af_inet.c#L642">642</a> }
<a name="L643" href="source/net/ipv4/af_inet.c#L643">643</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=__inet_stream_connect">__inet_stream_connect</a>);
<a name="L644" href="source/net/ipv4/af_inet.c#L644">644</a> 
<a name="L645" href="source/net/ipv4/af_inet.c#L645">645</a> int <a href="ident?i=inet_stream_connect">inet_stream_connect</a>(struct <a href="ident?i=socket">socket</a> *<a href="ident?i=sock">sock</a>, struct <a href="ident?i=sockaddr">sockaddr</a> *<a href="ident?i=uaddr">uaddr</a>,
<a name="L646" href="source/net/ipv4/af_inet.c#L646">646</a>                         int addr_len, int <a href="ident?i=flags">flags</a>)
<a name="L647" href="source/net/ipv4/af_inet.c#L647">647</a> {
<a name="L648" href="source/net/ipv4/af_inet.c#L648">648</a>         int <a href="ident?i=err">err</a>;
<a name="L649" href="source/net/ipv4/af_inet.c#L649">649</a> 
<a name="L650" href="source/net/ipv4/af_inet.c#L650">650</a>         <a href="ident?i=lock_sock">lock_sock</a>(<a href="ident?i=sock">sock</a>-&gt;sk);
<a name="L651" href="source/net/ipv4/af_inet.c#L651">651</a>         <a href="ident?i=err">err</a> = <a href="ident?i=__inet_stream_connect">__inet_stream_connect</a>(<a href="ident?i=sock">sock</a>, <a href="ident?i=uaddr">uaddr</a>, addr_len, <a href="ident?i=flags">flags</a>);
<a name="L652" href="source/net/ipv4/af_inet.c#L652">652</a>         <a href="ident?i=release_sock">release_sock</a>(<a href="ident?i=sock">sock</a>-&gt;sk);
<a name="L653" href="source/net/ipv4/af_inet.c#L653">653</a>         return <a href="ident?i=err">err</a>;
<a name="L654" href="source/net/ipv4/af_inet.c#L654">654</a> }
<a name="L655" href="source/net/ipv4/af_inet.c#L655">655</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=inet_stream_connect">inet_stream_connect</a>);
<a name="L656" href="source/net/ipv4/af_inet.c#L656">656</a> 
<a name="L657" href="source/net/ipv4/af_inet.c#L657">657</a> <b><i>/*</i></b>
<a name="L658" href="source/net/ipv4/af_inet.c#L658">658</a> <b><i> *      Accept a pending connection. The TCP layer now gives BSD semantics.</i></b>
<a name="L659" href="source/net/ipv4/af_inet.c#L659">659</a> <b><i> */</i></b>
<a name="L660" href="source/net/ipv4/af_inet.c#L660">660</a> 
<a name="L661" href="source/net/ipv4/af_inet.c#L661">661</a> int <a href="ident?i=inet_accept">inet_accept</a>(struct <a href="ident?i=socket">socket</a> *<a href="ident?i=sock">sock</a>, struct <a href="ident?i=socket">socket</a> *newsock, int <a href="ident?i=flags">flags</a>)
<a name="L662" href="source/net/ipv4/af_inet.c#L662">662</a> {
<a name="L663" href="source/net/ipv4/af_inet.c#L663">663</a>         struct <a href="ident?i=sock">sock</a> *sk1 = <a href="ident?i=sock">sock</a>-&gt;sk;
<a name="L664" href="source/net/ipv4/af_inet.c#L664">664</a>         int <a href="ident?i=err">err</a> = -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L665" href="source/net/ipv4/af_inet.c#L665">665</a>         struct <a href="ident?i=sock">sock</a> *sk2 = sk1-&gt;<a href="ident?i=sk_prot">sk_prot</a>-&gt;<a href="ident?i=accept">accept</a>(sk1, <a href="ident?i=flags">flags</a>, &amp;<a href="ident?i=err">err</a>);
<a name="L666" href="source/net/ipv4/af_inet.c#L666">666</a> 
<a name="L667" href="source/net/ipv4/af_inet.c#L667">667</a>         if (!sk2)
<a name="L668" href="source/net/ipv4/af_inet.c#L668">668</a>                 goto do_err;
<a name="L669" href="source/net/ipv4/af_inet.c#L669">669</a> 
<a name="L670" href="source/net/ipv4/af_inet.c#L670">670</a>         <a href="ident?i=lock_sock">lock_sock</a>(sk2);
<a name="L671" href="source/net/ipv4/af_inet.c#L671">671</a> 
<a name="L672" href="source/net/ipv4/af_inet.c#L672">672</a>         <a href="ident?i=sock_rps_record_flow">sock_rps_record_flow</a>(sk2);
<a name="L673" href="source/net/ipv4/af_inet.c#L673">673</a>         <a href="ident?i=WARN_ON">WARN_ON</a>(!((1 &lt;&lt; sk2-&gt;<a href="ident?i=sk_state">sk_state</a>) &amp;
<a name="L674" href="source/net/ipv4/af_inet.c#L674">674</a>                   (TCPF_ESTABLISHED | TCPF_SYN_RECV |
<a name="L675" href="source/net/ipv4/af_inet.c#L675">675</a>                   TCPF_CLOSE_WAIT | TCPF_CLOSE)));
<a name="L676" href="source/net/ipv4/af_inet.c#L676">676</a> 
<a name="L677" href="source/net/ipv4/af_inet.c#L677">677</a>         <a href="ident?i=sock_graft">sock_graft</a>(sk2, newsock);
<a name="L678" href="source/net/ipv4/af_inet.c#L678">678</a> 
<a name="L679" href="source/net/ipv4/af_inet.c#L679">679</a>         newsock-&gt;<a href="ident?i=state">state</a> = SS_CONNECTED;
<a name="L680" href="source/net/ipv4/af_inet.c#L680">680</a>         <a href="ident?i=err">err</a> = 0;
<a name="L681" href="source/net/ipv4/af_inet.c#L681">681</a>         <a href="ident?i=release_sock">release_sock</a>(sk2);
<a name="L682" href="source/net/ipv4/af_inet.c#L682">682</a> do_err:
<a name="L683" href="source/net/ipv4/af_inet.c#L683">683</a>         return <a href="ident?i=err">err</a>;
<a name="L684" href="source/net/ipv4/af_inet.c#L684">684</a> }
<a name="L685" href="source/net/ipv4/af_inet.c#L685">685</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=inet_accept">inet_accept</a>);
<a name="L686" href="source/net/ipv4/af_inet.c#L686">686</a> 
<a name="L687" href="source/net/ipv4/af_inet.c#L687">687</a> 
<a name="L688" href="source/net/ipv4/af_inet.c#L688">688</a> <b><i>/*</i></b>
<a name="L689" href="source/net/ipv4/af_inet.c#L689">689</a> <b><i> *      This does both peername and sockname.</i></b>
<a name="L690" href="source/net/ipv4/af_inet.c#L690">690</a> <b><i> */</i></b>
<a name="L691" href="source/net/ipv4/af_inet.c#L691">691</a> int <a href="ident?i=inet_getname">inet_getname</a>(struct <a href="ident?i=socket">socket</a> *<a href="ident?i=sock">sock</a>, struct <a href="ident?i=sockaddr">sockaddr</a> *<a href="ident?i=uaddr">uaddr</a>,
<a name="L692" href="source/net/ipv4/af_inet.c#L692">692</a>                         int *uaddr_len, int peer)
<a name="L693" href="source/net/ipv4/af_inet.c#L693">693</a> {
<a name="L694" href="source/net/ipv4/af_inet.c#L694">694</a>         struct <a href="ident?i=sock">sock</a> *sk         = <a href="ident?i=sock">sock</a>-&gt;sk;
<a name="L695" href="source/net/ipv4/af_inet.c#L695">695</a>         struct <a href="ident?i=inet_sock">inet_sock</a> *inet  = <a href="ident?i=inet_sk">inet_sk</a>(sk);
<a name="L696" href="source/net/ipv4/af_inet.c#L696">696</a>         <a href="ident?i=DECLARE_SOCKADDR">DECLARE_SOCKADDR</a>(struct <a href="ident?i=sockaddr_in">sockaddr_in</a> *, <a href="ident?i=sin">sin</a>, <a href="ident?i=uaddr">uaddr</a>);
<a name="L697" href="source/net/ipv4/af_inet.c#L697">697</a> 
<a name="L698" href="source/net/ipv4/af_inet.c#L698">698</a>         <a href="ident?i=sin">sin</a>-&gt;sin_family = <a href="ident?i=AF_INET">AF_INET</a>;
<a name="L699" href="source/net/ipv4/af_inet.c#L699">699</a>         if (peer) {
<a name="L700" href="source/net/ipv4/af_inet.c#L700">700</a>                 if (!inet-&gt;<a href="ident?i=inet_dport">inet_dport</a> ||
<a name="L701" href="source/net/ipv4/af_inet.c#L701">701</a>                     (((1 &lt;&lt; sk-&gt;<a href="ident?i=sk_state">sk_state</a>) &amp; (TCPF_CLOSE | TCPF_SYN_SENT)) &amp;&amp;
<a name="L702" href="source/net/ipv4/af_inet.c#L702">702</a>                      peer == 1))
<a name="L703" href="source/net/ipv4/af_inet.c#L703">703</a>                         return -<a href="ident?i=ENOTCONN">ENOTCONN</a>;
<a name="L704" href="source/net/ipv4/af_inet.c#L704">704</a>                 <a href="ident?i=sin">sin</a>-&gt;sin_port = inet-&gt;<a href="ident?i=inet_dport">inet_dport</a>;
<a name="L705" href="source/net/ipv4/af_inet.c#L705">705</a>                 <a href="ident?i=sin">sin</a>-&gt;sin_addr.s_addr = inet-&gt;<a href="ident?i=inet_daddr">inet_daddr</a>;
<a name="L706" href="source/net/ipv4/af_inet.c#L706">706</a>         } else {
<a name="L707" href="source/net/ipv4/af_inet.c#L707">707</a>                 <a href="ident?i=__be32">__be32</a> <a href="ident?i=addr">addr</a> = inet-&gt;<a href="ident?i=inet_rcv_saddr">inet_rcv_saddr</a>;
<a name="L708" href="source/net/ipv4/af_inet.c#L708">708</a>                 if (!<a href="ident?i=addr">addr</a>)
<a name="L709" href="source/net/ipv4/af_inet.c#L709">709</a>                         <a href="ident?i=addr">addr</a> = inet-&gt;inet_saddr;
<a name="L710" href="source/net/ipv4/af_inet.c#L710">710</a>                 <a href="ident?i=sin">sin</a>-&gt;sin_port = inet-&gt;inet_sport;
<a name="L711" href="source/net/ipv4/af_inet.c#L711">711</a>                 <a href="ident?i=sin">sin</a>-&gt;sin_addr.s_addr = <a href="ident?i=addr">addr</a>;
<a name="L712" href="source/net/ipv4/af_inet.c#L712">712</a>         }
<a name="L713" href="source/net/ipv4/af_inet.c#L713">713</a>         <a href="ident?i=memset">memset</a>(<a href="ident?i=sin">sin</a>-&gt;<a href="ident?i=sin_zero">sin_zero</a>, 0, sizeof(<a href="ident?i=sin">sin</a>-&gt;<a href="ident?i=sin_zero">sin_zero</a>));
<a name="L714" href="source/net/ipv4/af_inet.c#L714">714</a>         *uaddr_len = sizeof(*<a href="ident?i=sin">sin</a>);
<a name="L715" href="source/net/ipv4/af_inet.c#L715">715</a>         return 0;
<a name="L716" href="source/net/ipv4/af_inet.c#L716">716</a> }
<a name="L717" href="source/net/ipv4/af_inet.c#L717">717</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=inet_getname">inet_getname</a>);
<a name="L718" href="source/net/ipv4/af_inet.c#L718">718</a> 
<a name="L719" href="source/net/ipv4/af_inet.c#L719">719</a> int <a href="ident?i=inet_sendmsg">inet_sendmsg</a>(struct <a href="ident?i=socket">socket</a> *<a href="ident?i=sock">sock</a>, struct <a href="ident?i=msghdr">msghdr</a> *<a href="ident?i=msg">msg</a>, <a href="ident?i=size_t">size_t</a> <a href="ident?i=size">size</a>)
<a name="L720" href="source/net/ipv4/af_inet.c#L720">720</a> {
<a name="L721" href="source/net/ipv4/af_inet.c#L721">721</a>         struct <a href="ident?i=sock">sock</a> *sk = <a href="ident?i=sock">sock</a>-&gt;sk;
<a name="L722" href="source/net/ipv4/af_inet.c#L722">722</a> 
<a name="L723" href="source/net/ipv4/af_inet.c#L723">723</a>         <a href="ident?i=sock_rps_record_flow">sock_rps_record_flow</a>(sk);
<a name="L724" href="source/net/ipv4/af_inet.c#L724">724</a> 
<a name="L725" href="source/net/ipv4/af_inet.c#L725">725</a>         <b><i>/* We may need to bind the socket. */</i></b>
<a name="L726" href="source/net/ipv4/af_inet.c#L726">726</a>         if (!<a href="ident?i=inet_sk">inet_sk</a>(sk)-&gt;<a href="ident?i=inet_num">inet_num</a> &amp;&amp; !sk-&gt;<a href="ident?i=sk_prot">sk_prot</a>-&gt;no_autobind &amp;&amp;
<a name="L727" href="source/net/ipv4/af_inet.c#L727">727</a>             <a href="ident?i=inet_autobind">inet_autobind</a>(sk))
<a name="L728" href="source/net/ipv4/af_inet.c#L728">728</a>                 return -<a href="ident?i=EAGAIN">EAGAIN</a>;
<a name="L729" href="source/net/ipv4/af_inet.c#L729">729</a> 
<a name="L730" href="source/net/ipv4/af_inet.c#L730">730</a>         return sk-&gt;<a href="ident?i=sk_prot">sk_prot</a>-&gt;<a href="ident?i=sendmsg">sendmsg</a>(sk, <a href="ident?i=msg">msg</a>, <a href="ident?i=size">size</a>);
<a name="L731" href="source/net/ipv4/af_inet.c#L731">731</a> }
<a name="L732" href="source/net/ipv4/af_inet.c#L732">732</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=inet_sendmsg">inet_sendmsg</a>);
<a name="L733" href="source/net/ipv4/af_inet.c#L733">733</a> 
<a name="L734" href="source/net/ipv4/af_inet.c#L734">734</a> <a href="ident?i=ssize_t">ssize_t</a> <a href="ident?i=inet_sendpage">inet_sendpage</a>(struct <a href="ident?i=socket">socket</a> *<a href="ident?i=sock">sock</a>, struct <a href="ident?i=page">page</a> *<a href="ident?i=page">page</a>, int <a href="ident?i=offset">offset</a>,
<a name="L735" href="source/net/ipv4/af_inet.c#L735">735</a>                       <a href="ident?i=size_t">size_t</a> <a href="ident?i=size">size</a>, int <a href="ident?i=flags">flags</a>)
<a name="L736" href="source/net/ipv4/af_inet.c#L736">736</a> {
<a name="L737" href="source/net/ipv4/af_inet.c#L737">737</a>         struct <a href="ident?i=sock">sock</a> *sk = <a href="ident?i=sock">sock</a>-&gt;sk;
<a name="L738" href="source/net/ipv4/af_inet.c#L738">738</a> 
<a name="L739" href="source/net/ipv4/af_inet.c#L739">739</a>         <a href="ident?i=sock_rps_record_flow">sock_rps_record_flow</a>(sk);
<a name="L740" href="source/net/ipv4/af_inet.c#L740">740</a> 
<a name="L741" href="source/net/ipv4/af_inet.c#L741">741</a>         <b><i>/* We may need to bind the socket. */</i></b>
<a name="L742" href="source/net/ipv4/af_inet.c#L742">742</a>         if (!<a href="ident?i=inet_sk">inet_sk</a>(sk)-&gt;<a href="ident?i=inet_num">inet_num</a> &amp;&amp; !sk-&gt;<a href="ident?i=sk_prot">sk_prot</a>-&gt;no_autobind &amp;&amp;
<a name="L743" href="source/net/ipv4/af_inet.c#L743">743</a>             <a href="ident?i=inet_autobind">inet_autobind</a>(sk))
<a name="L744" href="source/net/ipv4/af_inet.c#L744">744</a>                 return -<a href="ident?i=EAGAIN">EAGAIN</a>;
<a name="L745" href="source/net/ipv4/af_inet.c#L745">745</a> 
<a name="L746" href="source/net/ipv4/af_inet.c#L746">746</a>         if (sk-&gt;<a href="ident?i=sk_prot">sk_prot</a>-&gt;sendpage)
<a name="L747" href="source/net/ipv4/af_inet.c#L747">747</a>                 return sk-&gt;<a href="ident?i=sk_prot">sk_prot</a>-&gt;sendpage(sk, <a href="ident?i=page">page</a>, <a href="ident?i=offset">offset</a>, <a href="ident?i=size">size</a>, <a href="ident?i=flags">flags</a>);
<a name="L748" href="source/net/ipv4/af_inet.c#L748">748</a>         return <a href="ident?i=sock_no_sendpage">sock_no_sendpage</a>(<a href="ident?i=sock">sock</a>, <a href="ident?i=page">page</a>, <a href="ident?i=offset">offset</a>, <a href="ident?i=size">size</a>, <a href="ident?i=flags">flags</a>);
<a name="L749" href="source/net/ipv4/af_inet.c#L749">749</a> }
<a name="L750" href="source/net/ipv4/af_inet.c#L750">750</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=inet_sendpage">inet_sendpage</a>);
<a name="L751" href="source/net/ipv4/af_inet.c#L751">751</a> 
<a name="L752" href="source/net/ipv4/af_inet.c#L752">752</a> int <a href="ident?i=inet_recvmsg">inet_recvmsg</a>(struct <a href="ident?i=socket">socket</a> *<a href="ident?i=sock">sock</a>, struct <a href="ident?i=msghdr">msghdr</a> *<a href="ident?i=msg">msg</a>, <a href="ident?i=size_t">size_t</a> <a href="ident?i=size">size</a>,
<a name="L753" href="source/net/ipv4/af_inet.c#L753">753</a>                  int <a href="ident?i=flags">flags</a>)
<a name="L754" href="source/net/ipv4/af_inet.c#L754">754</a> {
<a name="L755" href="source/net/ipv4/af_inet.c#L755">755</a>         struct <a href="ident?i=sock">sock</a> *sk = <a href="ident?i=sock">sock</a>-&gt;sk;
<a name="L756" href="source/net/ipv4/af_inet.c#L756">756</a>         int addr_len = 0;
<a name="L757" href="source/net/ipv4/af_inet.c#L757">757</a>         int <a href="ident?i=err">err</a>;
<a name="L758" href="source/net/ipv4/af_inet.c#L758">758</a> 
<a name="L759" href="source/net/ipv4/af_inet.c#L759">759</a>         <a href="ident?i=sock_rps_record_flow">sock_rps_record_flow</a>(sk);
<a name="L760" href="source/net/ipv4/af_inet.c#L760">760</a> 
<a name="L761" href="source/net/ipv4/af_inet.c#L761">761</a>         <a href="ident?i=err">err</a> = sk-&gt;<a href="ident?i=sk_prot">sk_prot</a>-&gt;recvmsg(sk, <a href="ident?i=msg">msg</a>, <a href="ident?i=size">size</a>, <a href="ident?i=flags">flags</a> &amp; <a href="ident?i=MSG_DONTWAIT">MSG_DONTWAIT</a>,
<a name="L762" href="source/net/ipv4/af_inet.c#L762">762</a>                                    <a href="ident?i=flags">flags</a> &amp; ~MSG_DONTWAIT, &amp;addr_len);
<a name="L763" href="source/net/ipv4/af_inet.c#L763">763</a>         if (<a href="ident?i=err">err</a> &gt;= 0)
<a name="L764" href="source/net/ipv4/af_inet.c#L764">764</a>                 <a href="ident?i=msg">msg</a>-&gt;msg_namelen = addr_len;
<a name="L765" href="source/net/ipv4/af_inet.c#L765">765</a>         return <a href="ident?i=err">err</a>;
<a name="L766" href="source/net/ipv4/af_inet.c#L766">766</a> }
<a name="L767" href="source/net/ipv4/af_inet.c#L767">767</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=inet_recvmsg">inet_recvmsg</a>);
<a name="L768" href="source/net/ipv4/af_inet.c#L768">768</a> 
<a name="L769" href="source/net/ipv4/af_inet.c#L769">769</a> int <a href="ident?i=inet_shutdown">inet_shutdown</a>(struct <a href="ident?i=socket">socket</a> *<a href="ident?i=sock">sock</a>, int how)
<a name="L770" href="source/net/ipv4/af_inet.c#L770">770</a> {
<a name="L771" href="source/net/ipv4/af_inet.c#L771">771</a>         struct <a href="ident?i=sock">sock</a> *sk = <a href="ident?i=sock">sock</a>-&gt;sk;
<a name="L772" href="source/net/ipv4/af_inet.c#L772">772</a>         int <a href="ident?i=err">err</a> = 0;
<a name="L773" href="source/net/ipv4/af_inet.c#L773">773</a> 
<a name="L774" href="source/net/ipv4/af_inet.c#L774">774</a>         <b><i>/* This should really check to make sure</i></b>
<a name="L775" href="source/net/ipv4/af_inet.c#L775">775</a> <b><i>         * the socket is a TCP socket. (WHY AC...)</i></b>
<a name="L776" href="source/net/ipv4/af_inet.c#L776">776</a> <b><i>         */</i></b>
<a name="L777" href="source/net/ipv4/af_inet.c#L777">777</a>         how++; <b><i>/* maps 0-&gt;1 has the advantage of making bit 1 rcvs and</i></b>
<a name="L778" href="source/net/ipv4/af_inet.c#L778">778</a> <b><i>                       1-&gt;2 bit 2 snds.</i></b>
<a name="L779" href="source/net/ipv4/af_inet.c#L779">779</a> <b><i>                       2-&gt;3 */</i></b>
<a name="L780" href="source/net/ipv4/af_inet.c#L780">780</a>         if ((how &amp; ~SHUTDOWN_MASK) || !how)     <b><i>/* MAXINT-&gt;0 */</i></b>
<a name="L781" href="source/net/ipv4/af_inet.c#L781">781</a>                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L782" href="source/net/ipv4/af_inet.c#L782">782</a> 
<a name="L783" href="source/net/ipv4/af_inet.c#L783">783</a>         <a href="ident?i=lock_sock">lock_sock</a>(sk);
<a name="L784" href="source/net/ipv4/af_inet.c#L784">784</a>         if (<a href="ident?i=sock">sock</a>-&gt;<a href="ident?i=state">state</a> == SS_CONNECTING) {
<a name="L785" href="source/net/ipv4/af_inet.c#L785">785</a>                 if ((1 &lt;&lt; sk-&gt;<a href="ident?i=sk_state">sk_state</a>) &amp;
<a name="L786" href="source/net/ipv4/af_inet.c#L786">786</a>                     (TCPF_SYN_SENT | TCPF_SYN_RECV | TCPF_CLOSE))
<a name="L787" href="source/net/ipv4/af_inet.c#L787">787</a>                         <a href="ident?i=sock">sock</a>-&gt;<a href="ident?i=state">state</a> = SS_DISCONNECTING;
<a name="L788" href="source/net/ipv4/af_inet.c#L788">788</a>                 else
<a name="L789" href="source/net/ipv4/af_inet.c#L789">789</a>                         <a href="ident?i=sock">sock</a>-&gt;<a href="ident?i=state">state</a> = SS_CONNECTED;
<a name="L790" href="source/net/ipv4/af_inet.c#L790">790</a>         }
<a name="L791" href="source/net/ipv4/af_inet.c#L791">791</a> 
<a name="L792" href="source/net/ipv4/af_inet.c#L792">792</a>         switch (sk-&gt;<a href="ident?i=sk_state">sk_state</a>) {
<a name="L793" href="source/net/ipv4/af_inet.c#L793">793</a>         case TCP_CLOSE:
<a name="L794" href="source/net/ipv4/af_inet.c#L794">794</a>                 <a href="ident?i=err">err</a> = -<a href="ident?i=ENOTCONN">ENOTCONN</a>;
<a name="L795" href="source/net/ipv4/af_inet.c#L795">795</a>                 <b><i>/* Hack to wake up other listeners, who can poll for</i></b>
<a name="L796" href="source/net/ipv4/af_inet.c#L796">796</a> <b><i>                   POLLHUP, even on eg. unconnected UDP sockets -- RR */</i></b>
<a name="L797" href="source/net/ipv4/af_inet.c#L797">797</a>         default:
<a name="L798" href="source/net/ipv4/af_inet.c#L798">798</a>                 sk-&gt;sk_shutdown |= how;
<a name="L799" href="source/net/ipv4/af_inet.c#L799">799</a>                 if (sk-&gt;<a href="ident?i=sk_prot">sk_prot</a>-&gt;<a href="ident?i=shutdown">shutdown</a>)
<a name="L800" href="source/net/ipv4/af_inet.c#L800">800</a>                         sk-&gt;<a href="ident?i=sk_prot">sk_prot</a>-&gt;<a href="ident?i=shutdown">shutdown</a>(sk, how);
<a name="L801" href="source/net/ipv4/af_inet.c#L801">801</a>                 break;
<a name="L802" href="source/net/ipv4/af_inet.c#L802">802</a> 
<a name="L803" href="source/net/ipv4/af_inet.c#L803">803</a>         <b><i>/* Remaining two branches are temporary solution for missing</i></b>
<a name="L804" href="source/net/ipv4/af_inet.c#L804">804</a> <b><i>         * close() in multithreaded environment. It is _not_ a good idea,</i></b>
<a name="L805" href="source/net/ipv4/af_inet.c#L805">805</a> <b><i>         * but we have no choice until close() is repaired at VFS level.</i></b>
<a name="L806" href="source/net/ipv4/af_inet.c#L806">806</a> <b><i>         */</i></b>
<a name="L807" href="source/net/ipv4/af_inet.c#L807">807</a>         case TCP_LISTEN:
<a name="L808" href="source/net/ipv4/af_inet.c#L808">808</a>                 if (!(how &amp; <a href="ident?i=RCV_SHUTDOWN">RCV_SHUTDOWN</a>))
<a name="L809" href="source/net/ipv4/af_inet.c#L809">809</a>                         break;
<a name="L810" href="source/net/ipv4/af_inet.c#L810">810</a>                 <b><i>/* Fall through */</i></b>
<a name="L811" href="source/net/ipv4/af_inet.c#L811">811</a>         case TCP_SYN_SENT:
<a name="L812" href="source/net/ipv4/af_inet.c#L812">812</a>                 <a href="ident?i=err">err</a> = sk-&gt;<a href="ident?i=sk_prot">sk_prot</a>-&gt;<a href="ident?i=disconnect">disconnect</a>(sk, <a href="ident?i=O_NONBLOCK">O_NONBLOCK</a>);
<a name="L813" href="source/net/ipv4/af_inet.c#L813">813</a>                 <a href="ident?i=sock">sock</a>-&gt;<a href="ident?i=state">state</a> = <a href="ident?i=err">err</a> ? SS_DISCONNECTING : SS_UNCONNECTED;
<a name="L814" href="source/net/ipv4/af_inet.c#L814">814</a>                 break;
<a name="L815" href="source/net/ipv4/af_inet.c#L815">815</a>         }
<a name="L816" href="source/net/ipv4/af_inet.c#L816">816</a> 
<a name="L817" href="source/net/ipv4/af_inet.c#L817">817</a>         <b><i>/* Wake up anyone sleeping in poll. */</i></b>
<a name="L818" href="source/net/ipv4/af_inet.c#L818">818</a>         sk-&gt;sk_state_change(sk);
<a name="L819" href="source/net/ipv4/af_inet.c#L819">819</a>         <a href="ident?i=release_sock">release_sock</a>(sk);
<a name="L820" href="source/net/ipv4/af_inet.c#L820">820</a>         return <a href="ident?i=err">err</a>;
<a name="L821" href="source/net/ipv4/af_inet.c#L821">821</a> }
<a name="L822" href="source/net/ipv4/af_inet.c#L822">822</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=inet_shutdown">inet_shutdown</a>);
<a name="L823" href="source/net/ipv4/af_inet.c#L823">823</a> 
<a name="L824" href="source/net/ipv4/af_inet.c#L824">824</a> <b><i>/*</i></b>
<a name="L825" href="source/net/ipv4/af_inet.c#L825">825</a> <b><i> *      ioctl() calls you can issue on an INET socket. Most of these are</i></b>
<a name="L826" href="source/net/ipv4/af_inet.c#L826">826</a> <b><i> *      device configuration and stuff and very rarely used. Some ioctls</i></b>
<a name="L827" href="source/net/ipv4/af_inet.c#L827">827</a> <b><i> *      pass on to the socket itself.</i></b>
<a name="L828" href="source/net/ipv4/af_inet.c#L828">828</a> <b><i> *</i></b>
<a name="L829" href="source/net/ipv4/af_inet.c#L829">829</a> <b><i> *      NOTE: I like the idea of a module for the config stuff. ie ifconfig</i></b>
<a name="L830" href="source/net/ipv4/af_inet.c#L830">830</a> <b><i> *      loads the devconfigure module does its configuring and unloads it.</i></b>
<a name="L831" href="source/net/ipv4/af_inet.c#L831">831</a> <b><i> *      There's a good 20K of config code hanging around the kernel.</i></b>
<a name="L832" href="source/net/ipv4/af_inet.c#L832">832</a> <b><i> */</i></b>
<a name="L833" href="source/net/ipv4/af_inet.c#L833">833</a> 
<a name="L834" href="source/net/ipv4/af_inet.c#L834">834</a> int <a href="ident?i=inet_ioctl">inet_ioctl</a>(struct <a href="ident?i=socket">socket</a> *<a href="ident?i=sock">sock</a>, unsigned int <a href="ident?i=cmd">cmd</a>, unsigned long <a href="ident?i=arg">arg</a>)
<a name="L835" href="source/net/ipv4/af_inet.c#L835">835</a> {
<a name="L836" href="source/net/ipv4/af_inet.c#L836">836</a>         struct <a href="ident?i=sock">sock</a> *sk = <a href="ident?i=sock">sock</a>-&gt;sk;
<a name="L837" href="source/net/ipv4/af_inet.c#L837">837</a>         int <a href="ident?i=err">err</a> = 0;
<a name="L838" href="source/net/ipv4/af_inet.c#L838">838</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=sock_net">sock_net</a>(sk);
<a name="L839" href="source/net/ipv4/af_inet.c#L839">839</a> 
<a name="L840" href="source/net/ipv4/af_inet.c#L840">840</a>         switch (<a href="ident?i=cmd">cmd</a>) {
<a name="L841" href="source/net/ipv4/af_inet.c#L841">841</a>         case <a href="ident?i=SIOCGSTAMP">SIOCGSTAMP</a>:
<a name="L842" href="source/net/ipv4/af_inet.c#L842">842</a>                 <a href="ident?i=err">err</a> = <a href="ident?i=sock_get_timestamp">sock_get_timestamp</a>(sk, (struct <a href="ident?i=timeval">timeval</a> <a href="ident?i=__user">__user</a> *)<a href="ident?i=arg">arg</a>);
<a name="L843" href="source/net/ipv4/af_inet.c#L843">843</a>                 break;
<a name="L844" href="source/net/ipv4/af_inet.c#L844">844</a>         case <a href="ident?i=SIOCGSTAMPNS">SIOCGSTAMPNS</a>:
<a name="L845" href="source/net/ipv4/af_inet.c#L845">845</a>                 <a href="ident?i=err">err</a> = <a href="ident?i=sock_get_timestampns">sock_get_timestampns</a>(sk, (struct <a href="ident?i=timespec">timespec</a> <a href="ident?i=__user">__user</a> *)<a href="ident?i=arg">arg</a>);
<a name="L846" href="source/net/ipv4/af_inet.c#L846">846</a>                 break;
<a name="L847" href="source/net/ipv4/af_inet.c#L847">847</a>         case <a href="ident?i=SIOCADDRT">SIOCADDRT</a>:
<a name="L848" href="source/net/ipv4/af_inet.c#L848">848</a>         case <a href="ident?i=SIOCDELRT">SIOCDELRT</a>:
<a name="L849" href="source/net/ipv4/af_inet.c#L849">849</a>         case <a href="ident?i=SIOCRTMSG">SIOCRTMSG</a>:
<a name="L850" href="source/net/ipv4/af_inet.c#L850">850</a>                 <a href="ident?i=err">err</a> = <a href="ident?i=ip_rt_ioctl">ip_rt_ioctl</a>(<a href="ident?i=net">net</a>, <a href="ident?i=cmd">cmd</a>, (void <a href="ident?i=__user">__user</a> *)<a href="ident?i=arg">arg</a>);
<a name="L851" href="source/net/ipv4/af_inet.c#L851">851</a>                 break;
<a name="L852" href="source/net/ipv4/af_inet.c#L852">852</a>         case <a href="ident?i=SIOCDARP">SIOCDARP</a>:
<a name="L853" href="source/net/ipv4/af_inet.c#L853">853</a>         case <a href="ident?i=SIOCGARP">SIOCGARP</a>:
<a name="L854" href="source/net/ipv4/af_inet.c#L854">854</a>         case <a href="ident?i=SIOCSARP">SIOCSARP</a>:
<a name="L855" href="source/net/ipv4/af_inet.c#L855">855</a>                 <a href="ident?i=err">err</a> = <a href="ident?i=arp_ioctl">arp_ioctl</a>(<a href="ident?i=net">net</a>, <a href="ident?i=cmd">cmd</a>, (void <a href="ident?i=__user">__user</a> *)<a href="ident?i=arg">arg</a>);
<a name="L856" href="source/net/ipv4/af_inet.c#L856">856</a>                 break;
<a name="L857" href="source/net/ipv4/af_inet.c#L857">857</a>         case <a href="ident?i=SIOCGIFADDR">SIOCGIFADDR</a>:
<a name="L858" href="source/net/ipv4/af_inet.c#L858">858</a>         case <a href="ident?i=SIOCSIFADDR">SIOCSIFADDR</a>:
<a name="L859" href="source/net/ipv4/af_inet.c#L859">859</a>         case <a href="ident?i=SIOCGIFBRDADDR">SIOCGIFBRDADDR</a>:
<a name="L860" href="source/net/ipv4/af_inet.c#L860">860</a>         case <a href="ident?i=SIOCSIFBRDADDR">SIOCSIFBRDADDR</a>:
<a name="L861" href="source/net/ipv4/af_inet.c#L861">861</a>         case <a href="ident?i=SIOCGIFNETMASK">SIOCGIFNETMASK</a>:
<a name="L862" href="source/net/ipv4/af_inet.c#L862">862</a>         case <a href="ident?i=SIOCSIFNETMASK">SIOCSIFNETMASK</a>:
<a name="L863" href="source/net/ipv4/af_inet.c#L863">863</a>         case <a href="ident?i=SIOCGIFDSTADDR">SIOCGIFDSTADDR</a>:
<a name="L864" href="source/net/ipv4/af_inet.c#L864">864</a>         case <a href="ident?i=SIOCSIFDSTADDR">SIOCSIFDSTADDR</a>:
<a name="L865" href="source/net/ipv4/af_inet.c#L865">865</a>         case <a href="ident?i=SIOCSIFPFLAGS">SIOCSIFPFLAGS</a>:
<a name="L866" href="source/net/ipv4/af_inet.c#L866">866</a>         case <a href="ident?i=SIOCGIFPFLAGS">SIOCGIFPFLAGS</a>:
<a name="L867" href="source/net/ipv4/af_inet.c#L867">867</a>         case <a href="ident?i=SIOCSIFFLAGS">SIOCSIFFLAGS</a>:
<a name="L868" href="source/net/ipv4/af_inet.c#L868">868</a>                 <a href="ident?i=err">err</a> = <a href="ident?i=devinet_ioctl">devinet_ioctl</a>(<a href="ident?i=net">net</a>, <a href="ident?i=cmd">cmd</a>, (void <a href="ident?i=__user">__user</a> *)<a href="ident?i=arg">arg</a>);
<a name="L869" href="source/net/ipv4/af_inet.c#L869">869</a>                 break;
<a name="L870" href="source/net/ipv4/af_inet.c#L870">870</a>         default:
<a name="L871" href="source/net/ipv4/af_inet.c#L871">871</a>                 if (sk-&gt;<a href="ident?i=sk_prot">sk_prot</a>-&gt;<a href="ident?i=ioctl">ioctl</a>)
<a name="L872" href="source/net/ipv4/af_inet.c#L872">872</a>                         <a href="ident?i=err">err</a> = sk-&gt;<a href="ident?i=sk_prot">sk_prot</a>-&gt;<a href="ident?i=ioctl">ioctl</a>(sk, <a href="ident?i=cmd">cmd</a>, <a href="ident?i=arg">arg</a>);
<a name="L873" href="source/net/ipv4/af_inet.c#L873">873</a>                 else
<a name="L874" href="source/net/ipv4/af_inet.c#L874">874</a>                         <a href="ident?i=err">err</a> = -<a href="ident?i=ENOIOCTLCMD">ENOIOCTLCMD</a>;
<a name="L875" href="source/net/ipv4/af_inet.c#L875">875</a>                 break;
<a name="L876" href="source/net/ipv4/af_inet.c#L876">876</a>         }
<a name="L877" href="source/net/ipv4/af_inet.c#L877">877</a>         return <a href="ident?i=err">err</a>;
<a name="L878" href="source/net/ipv4/af_inet.c#L878">878</a> }
<a name="L879" href="source/net/ipv4/af_inet.c#L879">879</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=inet_ioctl">inet_ioctl</a>);
<a name="L880" href="source/net/ipv4/af_inet.c#L880">880</a> 
<a name="L881" href="source/net/ipv4/af_inet.c#L881">881</a> #ifdef CONFIG_COMPAT
<a name="L882" href="source/net/ipv4/af_inet.c#L882">882</a> static int <a href="ident?i=inet_compat_ioctl">inet_compat_ioctl</a>(struct <a href="ident?i=socket">socket</a> *<a href="ident?i=sock">sock</a>, unsigned int <a href="ident?i=cmd">cmd</a>, unsigned long <a href="ident?i=arg">arg</a>)
<a name="L883" href="source/net/ipv4/af_inet.c#L883">883</a> {
<a name="L884" href="source/net/ipv4/af_inet.c#L884">884</a>         struct <a href="ident?i=sock">sock</a> *sk = <a href="ident?i=sock">sock</a>-&gt;sk;
<a name="L885" href="source/net/ipv4/af_inet.c#L885">885</a>         int <a href="ident?i=err">err</a> = -<a href="ident?i=ENOIOCTLCMD">ENOIOCTLCMD</a>;
<a name="L886" href="source/net/ipv4/af_inet.c#L886">886</a> 
<a name="L887" href="source/net/ipv4/af_inet.c#L887">887</a>         if (sk-&gt;<a href="ident?i=sk_prot">sk_prot</a>-&gt;compat_ioctl)
<a name="L888" href="source/net/ipv4/af_inet.c#L888">888</a>                 <a href="ident?i=err">err</a> = sk-&gt;<a href="ident?i=sk_prot">sk_prot</a>-&gt;compat_ioctl(sk, <a href="ident?i=cmd">cmd</a>, <a href="ident?i=arg">arg</a>);
<a name="L889" href="source/net/ipv4/af_inet.c#L889">889</a> 
<a name="L890" href="source/net/ipv4/af_inet.c#L890">890</a>         return <a href="ident?i=err">err</a>;
<a name="L891" href="source/net/ipv4/af_inet.c#L891">891</a> }
<a name="L892" href="source/net/ipv4/af_inet.c#L892">892</a> #endif
<a name="L893" href="source/net/ipv4/af_inet.c#L893">893</a> 
<a name="L894" href="source/net/ipv4/af_inet.c#L894">894</a> const struct <a href="ident?i=proto_ops">proto_ops</a> <a href="ident?i=inet_stream_ops">inet_stream_ops</a> = {
<a name="L895" href="source/net/ipv4/af_inet.c#L895">895</a>         .<a href="ident?i=family">family</a>            = <a href="ident?i=PF_INET">PF_INET</a>,
<a name="L896" href="source/net/ipv4/af_inet.c#L896">896</a>         .owner             = <a href="ident?i=THIS_MODULE">THIS_MODULE</a>,
<a name="L897" href="source/net/ipv4/af_inet.c#L897">897</a>         .<a href="ident?i=release">release</a>           = <a href="ident?i=inet_release">inet_release</a>,
<a name="L898" href="source/net/ipv4/af_inet.c#L898">898</a>         .bind              = <a href="ident?i=inet_bind">inet_bind</a>,
<a name="L899" href="source/net/ipv4/af_inet.c#L899">899</a>         .<a href="ident?i=connect">connect</a>           = <a href="ident?i=inet_stream_connect">inet_stream_connect</a>,
<a name="L900" href="source/net/ipv4/af_inet.c#L900">900</a>         .socketpair        = <a href="ident?i=sock_no_socketpair">sock_no_socketpair</a>,
<a name="L901" href="source/net/ipv4/af_inet.c#L901">901</a>         .<a href="ident?i=accept">accept</a>            = <a href="ident?i=inet_accept">inet_accept</a>,
<a name="L902" href="source/net/ipv4/af_inet.c#L902">902</a>         .<a href="ident?i=getname">getname</a>           = <a href="ident?i=inet_getname">inet_getname</a>,
<a name="L903" href="source/net/ipv4/af_inet.c#L903">903</a>         .<a href="ident?i=poll">poll</a>              = <a href="ident?i=tcp_poll">tcp_poll</a>,
<a name="L904" href="source/net/ipv4/af_inet.c#L904">904</a>         .<a href="ident?i=ioctl">ioctl</a>             = <a href="ident?i=inet_ioctl">inet_ioctl</a>,
<a name="L905" href="source/net/ipv4/af_inet.c#L905">905</a>         .listen            = <a href="ident?i=inet_listen">inet_listen</a>,
<a name="L906" href="source/net/ipv4/af_inet.c#L906">906</a>         .<a href="ident?i=shutdown">shutdown</a>          = <a href="ident?i=inet_shutdown">inet_shutdown</a>,
<a name="L907" href="source/net/ipv4/af_inet.c#L907">907</a>         .<a href="ident?i=setsockopt">setsockopt</a>        = <a href="ident?i=sock_common_setsockopt">sock_common_setsockopt</a>,
<a name="L908" href="source/net/ipv4/af_inet.c#L908">908</a>         .getsockopt        = <a href="ident?i=sock_common_getsockopt">sock_common_getsockopt</a>,
<a name="L909" href="source/net/ipv4/af_inet.c#L909">909</a>         .<a href="ident?i=sendmsg">sendmsg</a>           = <a href="ident?i=inet_sendmsg">inet_sendmsg</a>,
<a name="L910" href="source/net/ipv4/af_inet.c#L910">910</a>         .recvmsg           = <a href="ident?i=inet_recvmsg">inet_recvmsg</a>,
<a name="L911" href="source/net/ipv4/af_inet.c#L911">911</a>         .mmap              = <a href="ident?i=sock_no_mmap">sock_no_mmap</a>,
<a name="L912" href="source/net/ipv4/af_inet.c#L912">912</a>         .sendpage          = <a href="ident?i=inet_sendpage">inet_sendpage</a>,
<a name="L913" href="source/net/ipv4/af_inet.c#L913">913</a>         .splice_read       = <a href="ident?i=tcp_splice_read">tcp_splice_read</a>,
<a name="L914" href="source/net/ipv4/af_inet.c#L914">914</a> #ifdef CONFIG_COMPAT
<a name="L915" href="source/net/ipv4/af_inet.c#L915">915</a>         .compat_setsockopt = <a href="ident?i=compat_sock_common_setsockopt">compat_sock_common_setsockopt</a>,
<a name="L916" href="source/net/ipv4/af_inet.c#L916">916</a>         .compat_getsockopt = <a href="ident?i=compat_sock_common_getsockopt">compat_sock_common_getsockopt</a>,
<a name="L917" href="source/net/ipv4/af_inet.c#L917">917</a>         .compat_ioctl      = <a href="ident?i=inet_compat_ioctl">inet_compat_ioctl</a>,
<a name="L918" href="source/net/ipv4/af_inet.c#L918">918</a> #endif
<a name="L919" href="source/net/ipv4/af_inet.c#L919">919</a> };
<a name="L920" href="source/net/ipv4/af_inet.c#L920">920</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=inet_stream_ops">inet_stream_ops</a>);
<a name="L921" href="source/net/ipv4/af_inet.c#L921">921</a> 
<a name="L922" href="source/net/ipv4/af_inet.c#L922">922</a> const struct <a href="ident?i=proto_ops">proto_ops</a> <a href="ident?i=inet_dgram_ops">inet_dgram_ops</a> = {
<a name="L923" href="source/net/ipv4/af_inet.c#L923">923</a>         .<a href="ident?i=family">family</a>            = <a href="ident?i=PF_INET">PF_INET</a>,
<a name="L924" href="source/net/ipv4/af_inet.c#L924">924</a>         .owner             = <a href="ident?i=THIS_MODULE">THIS_MODULE</a>,
<a name="L925" href="source/net/ipv4/af_inet.c#L925">925</a>         .<a href="ident?i=release">release</a>           = <a href="ident?i=inet_release">inet_release</a>,
<a name="L926" href="source/net/ipv4/af_inet.c#L926">926</a>         .bind              = <a href="ident?i=inet_bind">inet_bind</a>,
<a name="L927" href="source/net/ipv4/af_inet.c#L927">927</a>         .<a href="ident?i=connect">connect</a>           = <a href="ident?i=inet_dgram_connect">inet_dgram_connect</a>,
<a name="L928" href="source/net/ipv4/af_inet.c#L928">928</a>         .socketpair        = <a href="ident?i=sock_no_socketpair">sock_no_socketpair</a>,
<a name="L929" href="source/net/ipv4/af_inet.c#L929">929</a>         .<a href="ident?i=accept">accept</a>            = <a href="ident?i=sock_no_accept">sock_no_accept</a>,
<a name="L930" href="source/net/ipv4/af_inet.c#L930">930</a>         .<a href="ident?i=getname">getname</a>           = <a href="ident?i=inet_getname">inet_getname</a>,
<a name="L931" href="source/net/ipv4/af_inet.c#L931">931</a>         .<a href="ident?i=poll">poll</a>              = <a href="ident?i=udp_poll">udp_poll</a>,
<a name="L932" href="source/net/ipv4/af_inet.c#L932">932</a>         .<a href="ident?i=ioctl">ioctl</a>             = <a href="ident?i=inet_ioctl">inet_ioctl</a>,
<a name="L933" href="source/net/ipv4/af_inet.c#L933">933</a>         .listen            = <a href="ident?i=sock_no_listen">sock_no_listen</a>,
<a name="L934" href="source/net/ipv4/af_inet.c#L934">934</a>         .<a href="ident?i=shutdown">shutdown</a>          = <a href="ident?i=inet_shutdown">inet_shutdown</a>,
<a name="L935" href="source/net/ipv4/af_inet.c#L935">935</a>         .<a href="ident?i=setsockopt">setsockopt</a>        = <a href="ident?i=sock_common_setsockopt">sock_common_setsockopt</a>,
<a name="L936" href="source/net/ipv4/af_inet.c#L936">936</a>         .getsockopt        = <a href="ident?i=sock_common_getsockopt">sock_common_getsockopt</a>,
<a name="L937" href="source/net/ipv4/af_inet.c#L937">937</a>         .<a href="ident?i=sendmsg">sendmsg</a>           = <a href="ident?i=inet_sendmsg">inet_sendmsg</a>,
<a name="L938" href="source/net/ipv4/af_inet.c#L938">938</a>         .recvmsg           = <a href="ident?i=inet_recvmsg">inet_recvmsg</a>,
<a name="L939" href="source/net/ipv4/af_inet.c#L939">939</a>         .mmap              = <a href="ident?i=sock_no_mmap">sock_no_mmap</a>,
<a name="L940" href="source/net/ipv4/af_inet.c#L940">940</a>         .sendpage          = <a href="ident?i=inet_sendpage">inet_sendpage</a>,
<a name="L941" href="source/net/ipv4/af_inet.c#L941">941</a> #ifdef CONFIG_COMPAT
<a name="L942" href="source/net/ipv4/af_inet.c#L942">942</a>         .compat_setsockopt = <a href="ident?i=compat_sock_common_setsockopt">compat_sock_common_setsockopt</a>,
<a name="L943" href="source/net/ipv4/af_inet.c#L943">943</a>         .compat_getsockopt = <a href="ident?i=compat_sock_common_getsockopt">compat_sock_common_getsockopt</a>,
<a name="L944" href="source/net/ipv4/af_inet.c#L944">944</a>         .compat_ioctl      = <a href="ident?i=inet_compat_ioctl">inet_compat_ioctl</a>,
<a name="L945" href="source/net/ipv4/af_inet.c#L945">945</a> #endif
<a name="L946" href="source/net/ipv4/af_inet.c#L946">946</a> };
<a name="L947" href="source/net/ipv4/af_inet.c#L947">947</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=inet_dgram_ops">inet_dgram_ops</a>);
<a name="L948" href="source/net/ipv4/af_inet.c#L948">948</a> 
<a name="L949" href="source/net/ipv4/af_inet.c#L949">949</a> <b><i>/*</i></b>
<a name="L950" href="source/net/ipv4/af_inet.c#L950">950</a> <b><i> * For SOCK_RAW sockets; should be the same as inet_dgram_ops but without</i></b>
<a name="L951" href="source/net/ipv4/af_inet.c#L951">951</a> <b><i> * udp_poll</i></b>
<a name="L952" href="source/net/ipv4/af_inet.c#L952">952</a> <b><i> */</i></b>
<a name="L953" href="source/net/ipv4/af_inet.c#L953">953</a> static const struct <a href="ident?i=proto_ops">proto_ops</a> <a href="ident?i=inet_sockraw_ops">inet_sockraw_ops</a> = {
<a name="L954" href="source/net/ipv4/af_inet.c#L954">954</a>         .<a href="ident?i=family">family</a>            = <a href="ident?i=PF_INET">PF_INET</a>,
<a name="L955" href="source/net/ipv4/af_inet.c#L955">955</a>         .owner             = <a href="ident?i=THIS_MODULE">THIS_MODULE</a>,
<a name="L956" href="source/net/ipv4/af_inet.c#L956">956</a>         .<a href="ident?i=release">release</a>           = <a href="ident?i=inet_release">inet_release</a>,
<a name="L957" href="source/net/ipv4/af_inet.c#L957">957</a>         .bind              = <a href="ident?i=inet_bind">inet_bind</a>,
<a name="L958" href="source/net/ipv4/af_inet.c#L958">958</a>         .<a href="ident?i=connect">connect</a>           = <a href="ident?i=inet_dgram_connect">inet_dgram_connect</a>,
<a name="L959" href="source/net/ipv4/af_inet.c#L959">959</a>         .socketpair        = <a href="ident?i=sock_no_socketpair">sock_no_socketpair</a>,
<a name="L960" href="source/net/ipv4/af_inet.c#L960">960</a>         .<a href="ident?i=accept">accept</a>            = <a href="ident?i=sock_no_accept">sock_no_accept</a>,
<a name="L961" href="source/net/ipv4/af_inet.c#L961">961</a>         .<a href="ident?i=getname">getname</a>           = <a href="ident?i=inet_getname">inet_getname</a>,
<a name="L962" href="source/net/ipv4/af_inet.c#L962">962</a>         .<a href="ident?i=poll">poll</a>              = <a href="ident?i=datagram_poll">datagram_poll</a>,
<a name="L963" href="source/net/ipv4/af_inet.c#L963">963</a>         .<a href="ident?i=ioctl">ioctl</a>             = <a href="ident?i=inet_ioctl">inet_ioctl</a>,
<a name="L964" href="source/net/ipv4/af_inet.c#L964">964</a>         .listen            = <a href="ident?i=sock_no_listen">sock_no_listen</a>,
<a name="L965" href="source/net/ipv4/af_inet.c#L965">965</a>         .<a href="ident?i=shutdown">shutdown</a>          = <a href="ident?i=inet_shutdown">inet_shutdown</a>,
<a name="L966" href="source/net/ipv4/af_inet.c#L966">966</a>         .<a href="ident?i=setsockopt">setsockopt</a>        = <a href="ident?i=sock_common_setsockopt">sock_common_setsockopt</a>,
<a name="L967" href="source/net/ipv4/af_inet.c#L967">967</a>         .getsockopt        = <a href="ident?i=sock_common_getsockopt">sock_common_getsockopt</a>,
<a name="L968" href="source/net/ipv4/af_inet.c#L968">968</a>         .<a href="ident?i=sendmsg">sendmsg</a>           = <a href="ident?i=inet_sendmsg">inet_sendmsg</a>,
<a name="L969" href="source/net/ipv4/af_inet.c#L969">969</a>         .recvmsg           = <a href="ident?i=inet_recvmsg">inet_recvmsg</a>,
<a name="L970" href="source/net/ipv4/af_inet.c#L970">970</a>         .mmap              = <a href="ident?i=sock_no_mmap">sock_no_mmap</a>,
<a name="L971" href="source/net/ipv4/af_inet.c#L971">971</a>         .sendpage          = <a href="ident?i=inet_sendpage">inet_sendpage</a>,
<a name="L972" href="source/net/ipv4/af_inet.c#L972">972</a> #ifdef CONFIG_COMPAT
<a name="L973" href="source/net/ipv4/af_inet.c#L973">973</a>         .compat_setsockopt = <a href="ident?i=compat_sock_common_setsockopt">compat_sock_common_setsockopt</a>,
<a name="L974" href="source/net/ipv4/af_inet.c#L974">974</a>         .compat_getsockopt = <a href="ident?i=compat_sock_common_getsockopt">compat_sock_common_getsockopt</a>,
<a name="L975" href="source/net/ipv4/af_inet.c#L975">975</a>         .compat_ioctl      = <a href="ident?i=inet_compat_ioctl">inet_compat_ioctl</a>,
<a name="L976" href="source/net/ipv4/af_inet.c#L976">976</a> #endif
<a name="L977" href="source/net/ipv4/af_inet.c#L977">977</a> };
<a name="L978" href="source/net/ipv4/af_inet.c#L978">978</a> 
<a name="L979" href="source/net/ipv4/af_inet.c#L979">979</a> static const struct <a href="ident?i=net_proto_family">net_proto_family</a> <a href="ident?i=inet_family_ops">inet_family_ops</a> = {
<a name="L980" href="source/net/ipv4/af_inet.c#L980">980</a>         .<a href="ident?i=family">family</a> = <a href="ident?i=PF_INET">PF_INET</a>,
<a name="L981" href="source/net/ipv4/af_inet.c#L981">981</a>         .<a href="ident?i=create">create</a> = <a href="ident?i=inet_create">inet_create</a>,
<a name="L982" href="source/net/ipv4/af_inet.c#L982">982</a>         .owner  = <a href="ident?i=THIS_MODULE">THIS_MODULE</a>,
<a name="L983" href="source/net/ipv4/af_inet.c#L983">983</a> };
<a name="L984" href="source/net/ipv4/af_inet.c#L984">984</a> 
<a name="L985" href="source/net/ipv4/af_inet.c#L985">985</a> <b><i>/* Upon startup we insert all the elements in inetsw_array[] into</i></b>
<a name="L986" href="source/net/ipv4/af_inet.c#L986">986</a> <b><i> * the linked list inetsw.</i></b>
<a name="L987" href="source/net/ipv4/af_inet.c#L987">987</a> <b><i> */</i></b>
<a name="L988" href="source/net/ipv4/af_inet.c#L988">988</a> static struct <a href="ident?i=inet_protosw">inet_protosw</a> <a href="ident?i=inetsw_array">inetsw_array</a>[] =
<a name="L989" href="source/net/ipv4/af_inet.c#L989">989</a> {
<a name="L990" href="source/net/ipv4/af_inet.c#L990">990</a>         {
<a name="L991" href="source/net/ipv4/af_inet.c#L991">991</a>                 .<a href="ident?i=type">type</a> =       SOCK_STREAM,
<a name="L992" href="source/net/ipv4/af_inet.c#L992">992</a>                 .<a href="ident?i=protocol">protocol</a> =   <a href="ident?i=IPPROTO_TCP">IPPROTO_TCP</a>,
<a name="L993" href="source/net/ipv4/af_inet.c#L993">993</a>                 .prot =       &amp;<a href="ident?i=tcp_prot">tcp_prot</a>,
<a name="L994" href="source/net/ipv4/af_inet.c#L994">994</a>                 .<a href="ident?i=ops">ops</a> =        &amp;<a href="ident?i=inet_stream_ops">inet_stream_ops</a>,
<a name="L995" href="source/net/ipv4/af_inet.c#L995">995</a>                 .<a href="ident?i=flags">flags</a> =      <a href="ident?i=INET_PROTOSW_PERMANENT">INET_PROTOSW_PERMANENT</a> |
<a name="L996" href="source/net/ipv4/af_inet.c#L996">996</a>                               <a href="ident?i=INET_PROTOSW_ICSK">INET_PROTOSW_ICSK</a>,
<a name="L997" href="source/net/ipv4/af_inet.c#L997">997</a>         },
<a name="L998" href="source/net/ipv4/af_inet.c#L998">998</a> 
<a name="L999" href="source/net/ipv4/af_inet.c#L999">999</a>         {
<a name="L1000" href="source/net/ipv4/af_inet.c#L1000">1000</a>                 .<a href="ident?i=type">type</a> =       SOCK_DGRAM,
<a name="L1001" href="source/net/ipv4/af_inet.c#L1001">1001</a>                 .<a href="ident?i=protocol">protocol</a> =   <a href="ident?i=IPPROTO_UDP">IPPROTO_UDP</a>,
<a name="L1002" href="source/net/ipv4/af_inet.c#L1002">1002</a>                 .prot =       &amp;<a href="ident?i=udp_prot">udp_prot</a>,
<a name="L1003" href="source/net/ipv4/af_inet.c#L1003">1003</a>                 .<a href="ident?i=ops">ops</a> =        &amp;<a href="ident?i=inet_dgram_ops">inet_dgram_ops</a>,
<a name="L1004" href="source/net/ipv4/af_inet.c#L1004">1004</a>                 .<a href="ident?i=flags">flags</a> =      <a href="ident?i=INET_PROTOSW_PERMANENT">INET_PROTOSW_PERMANENT</a>,
<a name="L1005" href="source/net/ipv4/af_inet.c#L1005">1005</a>        },
<a name="L1006" href="source/net/ipv4/af_inet.c#L1006">1006</a> 
<a name="L1007" href="source/net/ipv4/af_inet.c#L1007">1007</a>        {
<a name="L1008" href="source/net/ipv4/af_inet.c#L1008">1008</a>                 .<a href="ident?i=type">type</a> =       SOCK_DGRAM,
<a name="L1009" href="source/net/ipv4/af_inet.c#L1009">1009</a>                 .<a href="ident?i=protocol">protocol</a> =   <a href="ident?i=IPPROTO_ICMP">IPPROTO_ICMP</a>,
<a name="L1010" href="source/net/ipv4/af_inet.c#L1010">1010</a>                 .prot =       &amp;<a href="ident?i=ping_prot">ping_prot</a>,
<a name="L1011" href="source/net/ipv4/af_inet.c#L1011">1011</a>                 .<a href="ident?i=ops">ops</a> =        &amp;<a href="ident?i=inet_dgram_ops">inet_dgram_ops</a>,
<a name="L1012" href="source/net/ipv4/af_inet.c#L1012">1012</a>                 .<a href="ident?i=flags">flags</a> =      <a href="ident?i=INET_PROTOSW_REUSE">INET_PROTOSW_REUSE</a>,
<a name="L1013" href="source/net/ipv4/af_inet.c#L1013">1013</a>        },
<a name="L1014" href="source/net/ipv4/af_inet.c#L1014">1014</a> 
<a name="L1015" href="source/net/ipv4/af_inet.c#L1015">1015</a>        {
<a name="L1016" href="source/net/ipv4/af_inet.c#L1016">1016</a>                .<a href="ident?i=type">type</a> =       SOCK_RAW,
<a name="L1017" href="source/net/ipv4/af_inet.c#L1017">1017</a>                .<a href="ident?i=protocol">protocol</a> =   <a href="ident?i=IPPROTO_IP">IPPROTO_IP</a>,        <b><i>/* wild card */</i></b>
<a name="L1018" href="source/net/ipv4/af_inet.c#L1018">1018</a>                .prot =       &amp;<a href="ident?i=raw_prot">raw_prot</a>,
<a name="L1019" href="source/net/ipv4/af_inet.c#L1019">1019</a>                .<a href="ident?i=ops">ops</a> =        &amp;<a href="ident?i=inet_sockraw_ops">inet_sockraw_ops</a>,
<a name="L1020" href="source/net/ipv4/af_inet.c#L1020">1020</a>                .<a href="ident?i=flags">flags</a> =      <a href="ident?i=INET_PROTOSW_REUSE">INET_PROTOSW_REUSE</a>,
<a name="L1021" href="source/net/ipv4/af_inet.c#L1021">1021</a>        }
<a name="L1022" href="source/net/ipv4/af_inet.c#L1022">1022</a> };
<a name="L1023" href="source/net/ipv4/af_inet.c#L1023">1023</a> 
<a name="L1024" href="source/net/ipv4/af_inet.c#L1024">1024</a> #define <a href="ident?i=INETSW_ARRAY_LEN">INETSW_ARRAY_LEN</a> <a href="ident?i=ARRAY_SIZE">ARRAY_SIZE</a>(<a href="ident?i=inetsw_array">inetsw_array</a>)
<a name="L1025" href="source/net/ipv4/af_inet.c#L1025">1025</a> 
<a name="L1026" href="source/net/ipv4/af_inet.c#L1026">1026</a> void <a href="ident?i=inet_register_protosw">inet_register_protosw</a>(struct <a href="ident?i=inet_protosw">inet_protosw</a> *<a href="ident?i=p">p</a>)
<a name="L1027" href="source/net/ipv4/af_inet.c#L1027">1027</a> {
<a name="L1028" href="source/net/ipv4/af_inet.c#L1028">1028</a>         struct <a href="ident?i=list_head">list_head</a> *lh;
<a name="L1029" href="source/net/ipv4/af_inet.c#L1029">1029</a>         struct <a href="ident?i=inet_protosw">inet_protosw</a> *<a href="ident?i=answer">answer</a>;
<a name="L1030" href="source/net/ipv4/af_inet.c#L1030">1030</a>         int <a href="ident?i=protocol">protocol</a> = <a href="ident?i=p">p</a>-&gt;<a href="ident?i=protocol">protocol</a>;
<a name="L1031" href="source/net/ipv4/af_inet.c#L1031">1031</a>         struct <a href="ident?i=list_head">list_head</a> *last_perm;
<a name="L1032" href="source/net/ipv4/af_inet.c#L1032">1032</a> 
<a name="L1033" href="source/net/ipv4/af_inet.c#L1033">1033</a>         <a href="ident?i=spin_lock_bh">spin_lock_bh</a>(&amp;inetsw_lock);
<a name="L1034" href="source/net/ipv4/af_inet.c#L1034">1034</a> 
<a name="L1035" href="source/net/ipv4/af_inet.c#L1035">1035</a>         if (<a href="ident?i=p">p</a>-&gt;<a href="ident?i=type">type</a> &gt;= <a href="ident?i=SOCK_MAX">SOCK_MAX</a>)
<a name="L1036" href="source/net/ipv4/af_inet.c#L1036">1036</a>                 goto out_illegal;
<a name="L1037" href="source/net/ipv4/af_inet.c#L1037">1037</a> 
<a name="L1038" href="source/net/ipv4/af_inet.c#L1038">1038</a>         <b><i>/* If we are trying to override a permanent protocol, bail. */</i></b>
<a name="L1039" href="source/net/ipv4/af_inet.c#L1039">1039</a>         <a href="ident?i=answer">answer</a> = <a href="ident?i=NULL">NULL</a>;
<a name="L1040" href="source/net/ipv4/af_inet.c#L1040">1040</a>         last_perm = &amp;<a href="ident?i=inetsw">inetsw</a>[<a href="ident?i=p">p</a>-&gt;<a href="ident?i=type">type</a>];
<a name="L1041" href="source/net/ipv4/af_inet.c#L1041">1041</a>         <a href="ident?i=list_for_each">list_for_each</a>(lh, &amp;<a href="ident?i=inetsw">inetsw</a>[<a href="ident?i=p">p</a>-&gt;<a href="ident?i=type">type</a>]) {
<a name="L1042" href="source/net/ipv4/af_inet.c#L1042">1042</a>                 <a href="ident?i=answer">answer</a> = <a href="ident?i=list_entry">list_entry</a>(lh, struct <a href="ident?i=inet_protosw">inet_protosw</a>, <a href="ident?i=list">list</a>);
<a name="L1043" href="source/net/ipv4/af_inet.c#L1043">1043</a> 
<a name="L1044" href="source/net/ipv4/af_inet.c#L1044">1044</a>                 <b><i>/* Check only the non-wild match. */</i></b>
<a name="L1045" href="source/net/ipv4/af_inet.c#L1045">1045</a>                 if (<a href="ident?i=INET_PROTOSW_PERMANENT">INET_PROTOSW_PERMANENT</a> &amp; <a href="ident?i=answer">answer</a>-&gt;<a href="ident?i=flags">flags</a>) {
<a name="L1046" href="source/net/ipv4/af_inet.c#L1046">1046</a>                         if (<a href="ident?i=protocol">protocol</a> == <a href="ident?i=answer">answer</a>-&gt;<a href="ident?i=protocol">protocol</a>)
<a name="L1047" href="source/net/ipv4/af_inet.c#L1047">1047</a>                                 break;
<a name="L1048" href="source/net/ipv4/af_inet.c#L1048">1048</a>                         last_perm = lh;
<a name="L1049" href="source/net/ipv4/af_inet.c#L1049">1049</a>                 }
<a name="L1050" href="source/net/ipv4/af_inet.c#L1050">1050</a> 
<a name="L1051" href="source/net/ipv4/af_inet.c#L1051">1051</a>                 <a href="ident?i=answer">answer</a> = <a href="ident?i=NULL">NULL</a>;
<a name="L1052" href="source/net/ipv4/af_inet.c#L1052">1052</a>         }
<a name="L1053" href="source/net/ipv4/af_inet.c#L1053">1053</a>         if (<a href="ident?i=answer">answer</a>)
<a name="L1054" href="source/net/ipv4/af_inet.c#L1054">1054</a>                 goto out_permanent;
<a name="L1055" href="source/net/ipv4/af_inet.c#L1055">1055</a> 
<a name="L1056" href="source/net/ipv4/af_inet.c#L1056">1056</a>         <b><i>/* Add the new entry after the last permanent entry if any, so that</i></b>
<a name="L1057" href="source/net/ipv4/af_inet.c#L1057">1057</a> <b><i>         * the new entry does not override a permanent entry when matched with</i></b>
<a name="L1058" href="source/net/ipv4/af_inet.c#L1058">1058</a> <b><i>         * a wild-card protocol. But it is allowed to override any existing</i></b>
<a name="L1059" href="source/net/ipv4/af_inet.c#L1059">1059</a> <b><i>         * non-permanent entry.  This means that when we remove this entry, the</i></b>
<a name="L1060" href="source/net/ipv4/af_inet.c#L1060">1060</a> <b><i>         * system automatically returns to the old behavior.</i></b>
<a name="L1061" href="source/net/ipv4/af_inet.c#L1061">1061</a> <b><i>         */</i></b>
<a name="L1062" href="source/net/ipv4/af_inet.c#L1062">1062</a>         <a href="ident?i=list_add_rcu">list_add_rcu</a>(&amp;<a href="ident?i=p">p</a>-&gt;<a href="ident?i=list">list</a>, last_perm);
<a name="L1063" href="source/net/ipv4/af_inet.c#L1063">1063</a> <a href="ident?i=out">out</a>:
<a name="L1064" href="source/net/ipv4/af_inet.c#L1064">1064</a>         <a href="ident?i=spin_unlock_bh">spin_unlock_bh</a>(&amp;inetsw_lock);
<a name="L1065" href="source/net/ipv4/af_inet.c#L1065">1065</a> 
<a name="L1066" href="source/net/ipv4/af_inet.c#L1066">1066</a>         return;
<a name="L1067" href="source/net/ipv4/af_inet.c#L1067">1067</a> 
<a name="L1068" href="source/net/ipv4/af_inet.c#L1068">1068</a> out_permanent:
<a name="L1069" href="source/net/ipv4/af_inet.c#L1069">1069</a>         <a href="ident?i=pr_err">pr_err</a>(<i>"Attempt to override permanent protocol %d\n"</i>, <a href="ident?i=protocol">protocol</a>);
<a name="L1070" href="source/net/ipv4/af_inet.c#L1070">1070</a>         goto <a href="ident?i=out">out</a>;
<a name="L1071" href="source/net/ipv4/af_inet.c#L1071">1071</a> 
<a name="L1072" href="source/net/ipv4/af_inet.c#L1072">1072</a> out_illegal:
<a name="L1073" href="source/net/ipv4/af_inet.c#L1073">1073</a>         <a href="ident?i=pr_err">pr_err</a>(<i>"Ignoring attempt to register invalid socket type %d\n"</i>,
<a name="L1074" href="source/net/ipv4/af_inet.c#L1074">1074</a>                <a href="ident?i=p">p</a>-&gt;<a href="ident?i=type">type</a>);
<a name="L1075" href="source/net/ipv4/af_inet.c#L1075">1075</a>         goto <a href="ident?i=out">out</a>;
<a name="L1076" href="source/net/ipv4/af_inet.c#L1076">1076</a> }
<a name="L1077" href="source/net/ipv4/af_inet.c#L1077">1077</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=inet_register_protosw">inet_register_protosw</a>);
<a name="L1078" href="source/net/ipv4/af_inet.c#L1078">1078</a> 
<a name="L1079" href="source/net/ipv4/af_inet.c#L1079">1079</a> void <a href="ident?i=inet_unregister_protosw">inet_unregister_protosw</a>(struct <a href="ident?i=inet_protosw">inet_protosw</a> *<a href="ident?i=p">p</a>)
<a name="L1080" href="source/net/ipv4/af_inet.c#L1080">1080</a> {
<a name="L1081" href="source/net/ipv4/af_inet.c#L1081">1081</a>         if (<a href="ident?i=INET_PROTOSW_PERMANENT">INET_PROTOSW_PERMANENT</a> &amp; <a href="ident?i=p">p</a>-&gt;<a href="ident?i=flags">flags</a>) {
<a name="L1082" href="source/net/ipv4/af_inet.c#L1082">1082</a>                 <a href="ident?i=pr_err">pr_err</a>(<i>"Attempt to unregister permanent protocol %d\n"</i>,
<a name="L1083" href="source/net/ipv4/af_inet.c#L1083">1083</a>                        <a href="ident?i=p">p</a>-&gt;<a href="ident?i=protocol">protocol</a>);
<a name="L1084" href="source/net/ipv4/af_inet.c#L1084">1084</a>         } else {
<a name="L1085" href="source/net/ipv4/af_inet.c#L1085">1085</a>                 <a href="ident?i=spin_lock_bh">spin_lock_bh</a>(&amp;inetsw_lock);
<a name="L1086" href="source/net/ipv4/af_inet.c#L1086">1086</a>                 <a href="ident?i=list_del_rcu">list_del_rcu</a>(&amp;<a href="ident?i=p">p</a>-&gt;<a href="ident?i=list">list</a>);
<a name="L1087" href="source/net/ipv4/af_inet.c#L1087">1087</a>                 <a href="ident?i=spin_unlock_bh">spin_unlock_bh</a>(&amp;inetsw_lock);
<a name="L1088" href="source/net/ipv4/af_inet.c#L1088">1088</a> 
<a name="L1089" href="source/net/ipv4/af_inet.c#L1089">1089</a>                 <a href="ident?i=synchronize_net">synchronize_net</a>();
<a name="L1090" href="source/net/ipv4/af_inet.c#L1090">1090</a>         }
<a name="L1091" href="source/net/ipv4/af_inet.c#L1091">1091</a> }
<a name="L1092" href="source/net/ipv4/af_inet.c#L1092">1092</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=inet_unregister_protosw">inet_unregister_protosw</a>);
<a name="L1093" href="source/net/ipv4/af_inet.c#L1093">1093</a> 
<a name="L1094" href="source/net/ipv4/af_inet.c#L1094">1094</a> <b><i>/*</i></b>
<a name="L1095" href="source/net/ipv4/af_inet.c#L1095">1095</a> <b><i> *      Shall we try to damage output packets if routing dev changes?</i></b>
<a name="L1096" href="source/net/ipv4/af_inet.c#L1096">1096</a> <b><i> */</i></b>
<a name="L1097" href="source/net/ipv4/af_inet.c#L1097">1097</a> 
<a name="L1098" href="source/net/ipv4/af_inet.c#L1098">1098</a> int <a href="ident?i=sysctl_ip_dynaddr">sysctl_ip_dynaddr</a> <a href="ident?i=__read_mostly">__read_mostly</a>;
<a name="L1099" href="source/net/ipv4/af_inet.c#L1099">1099</a> 
<a name="L1100" href="source/net/ipv4/af_inet.c#L1100">1100</a> static int <a href="ident?i=inet_sk_reselect_saddr">inet_sk_reselect_saddr</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L1101" href="source/net/ipv4/af_inet.c#L1101">1101</a> {
<a name="L1102" href="source/net/ipv4/af_inet.c#L1102">1102</a>         struct <a href="ident?i=inet_sock">inet_sock</a> *inet = <a href="ident?i=inet_sk">inet_sk</a>(sk);
<a name="L1103" href="source/net/ipv4/af_inet.c#L1103">1103</a>         <a href="ident?i=__be32">__be32</a> old_saddr = inet-&gt;inet_saddr;
<a name="L1104" href="source/net/ipv4/af_inet.c#L1104">1104</a>         <a href="ident?i=__be32">__be32</a> <a href="ident?i=daddr">daddr</a> = inet-&gt;<a href="ident?i=inet_daddr">inet_daddr</a>;
<a name="L1105" href="source/net/ipv4/af_inet.c#L1105">1105</a>         struct <a href="ident?i=flowi4">flowi4</a> *fl4;
<a name="L1106" href="source/net/ipv4/af_inet.c#L1106">1106</a>         struct <a href="ident?i=rtable">rtable</a> *<a href="ident?i=rt">rt</a>;
<a name="L1107" href="source/net/ipv4/af_inet.c#L1107">1107</a>         <a href="ident?i=__be32">__be32</a> new_saddr;
<a name="L1108" href="source/net/ipv4/af_inet.c#L1108">1108</a>         struct <a href="ident?i=ip_options_rcu">ip_options_rcu</a> *inet_opt;
<a name="L1109" href="source/net/ipv4/af_inet.c#L1109">1109</a> 
<a name="L1110" href="source/net/ipv4/af_inet.c#L1110">1110</a>         inet_opt = <a href="ident?i=rcu_dereference_protected">rcu_dereference_protected</a>(inet-&gt;inet_opt,
<a name="L1111" href="source/net/ipv4/af_inet.c#L1111">1111</a>                                              <a href="ident?i=sock_owned_by_user">sock_owned_by_user</a>(sk));
<a name="L1112" href="source/net/ipv4/af_inet.c#L1112">1112</a>         if (inet_opt &amp;&amp; inet_opt-&gt;opt.<a href="ident?i=srr">srr</a>)
<a name="L1113" href="source/net/ipv4/af_inet.c#L1113">1113</a>                 <a href="ident?i=daddr">daddr</a> = inet_opt-&gt;opt.faddr;
<a name="L1114" href="source/net/ipv4/af_inet.c#L1114">1114</a> 
<a name="L1115" href="source/net/ipv4/af_inet.c#L1115">1115</a>         <b><i>/* Query new route. */</i></b>
<a name="L1116" href="source/net/ipv4/af_inet.c#L1116">1116</a>         fl4 = &amp;inet-&gt;cork.fl.u.ip4;
<a name="L1117" href="source/net/ipv4/af_inet.c#L1117">1117</a>         <a href="ident?i=rt">rt</a> = <a href="ident?i=ip_route_connect">ip_route_connect</a>(fl4, <a href="ident?i=daddr">daddr</a>, 0, <a href="ident?i=RT_CONN_FLAGS">RT_CONN_FLAGS</a>(sk),
<a name="L1118" href="source/net/ipv4/af_inet.c#L1118">1118</a>                               sk-&gt;<a href="ident?i=sk_bound_dev_if">sk_bound_dev_if</a>, sk-&gt;sk_protocol,
<a name="L1119" href="source/net/ipv4/af_inet.c#L1119">1119</a>                               inet-&gt;inet_sport, inet-&gt;<a href="ident?i=inet_dport">inet_dport</a>, sk);
<a name="L1120" href="source/net/ipv4/af_inet.c#L1120">1120</a>         if (<a href="ident?i=IS_ERR">IS_ERR</a>(<a href="ident?i=rt">rt</a>))
<a name="L1121" href="source/net/ipv4/af_inet.c#L1121">1121</a>                 return <a href="ident?i=PTR_ERR">PTR_ERR</a>(<a href="ident?i=rt">rt</a>);
<a name="L1122" href="source/net/ipv4/af_inet.c#L1122">1122</a> 
<a name="L1123" href="source/net/ipv4/af_inet.c#L1123">1123</a>         <a href="ident?i=sk_setup_caps">sk_setup_caps</a>(sk, &amp;<a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>);
<a name="L1124" href="source/net/ipv4/af_inet.c#L1124">1124</a> 
<a name="L1125" href="source/net/ipv4/af_inet.c#L1125">1125</a>         new_saddr = fl4-&gt;<a href="ident?i=saddr">saddr</a>;
<a name="L1126" href="source/net/ipv4/af_inet.c#L1126">1126</a> 
<a name="L1127" href="source/net/ipv4/af_inet.c#L1127">1127</a>         if (new_saddr == old_saddr)
<a name="L1128" href="source/net/ipv4/af_inet.c#L1128">1128</a>                 return 0;
<a name="L1129" href="source/net/ipv4/af_inet.c#L1129">1129</a> 
<a name="L1130" href="source/net/ipv4/af_inet.c#L1130">1130</a>         if (<a href="ident?i=sysctl_ip_dynaddr">sysctl_ip_dynaddr</a> &gt; 1) {
<a name="L1131" href="source/net/ipv4/af_inet.c#L1131">1131</a>                 <a href="ident?i=pr_info">pr_info</a>(<i>"%s(): shifting inet-&gt;saddr from %pI4 to %pI4\n"</i>,
<a name="L1132" href="source/net/ipv4/af_inet.c#L1132">1132</a>                         <a href="ident?i=__func__">__func__</a>, &amp;old_saddr, &amp;new_saddr);
<a name="L1133" href="source/net/ipv4/af_inet.c#L1133">1133</a>         }
<a name="L1134" href="source/net/ipv4/af_inet.c#L1134">1134</a> 
<a name="L1135" href="source/net/ipv4/af_inet.c#L1135">1135</a>         inet-&gt;inet_saddr = inet-&gt;<a href="ident?i=inet_rcv_saddr">inet_rcv_saddr</a> = new_saddr;
<a name="L1136" href="source/net/ipv4/af_inet.c#L1136">1136</a> 
<a name="L1137" href="source/net/ipv4/af_inet.c#L1137">1137</a>         <b><i>/*</i></b>
<a name="L1138" href="source/net/ipv4/af_inet.c#L1138">1138</a> <b><i>         * XXX The only one ugly spot where we need to</i></b>
<a name="L1139" href="source/net/ipv4/af_inet.c#L1139">1139</a> <b><i>         * XXX really change the sockets identity after</i></b>
<a name="L1140" href="source/net/ipv4/af_inet.c#L1140">1140</a> <b><i>         * XXX it has entered the hashes. -DaveM</i></b>
<a name="L1141" href="source/net/ipv4/af_inet.c#L1141">1141</a> <b><i>         *</i></b>
<a name="L1142" href="source/net/ipv4/af_inet.c#L1142">1142</a> <b><i>         * Besides that, it does not check for connection</i></b>
<a name="L1143" href="source/net/ipv4/af_inet.c#L1143">1143</a> <b><i>         * uniqueness. Wait for troubles.</i></b>
<a name="L1144" href="source/net/ipv4/af_inet.c#L1144">1144</a> <b><i>         */</i></b>
<a name="L1145" href="source/net/ipv4/af_inet.c#L1145">1145</a>         <a href="ident?i=__sk_prot_rehash">__sk_prot_rehash</a>(sk);
<a name="L1146" href="source/net/ipv4/af_inet.c#L1146">1146</a>         return 0;
<a name="L1147" href="source/net/ipv4/af_inet.c#L1147">1147</a> }
<a name="L1148" href="source/net/ipv4/af_inet.c#L1148">1148</a> 
<a name="L1149" href="source/net/ipv4/af_inet.c#L1149">1149</a> int <a href="ident?i=inet_sk_rebuild_header">inet_sk_rebuild_header</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L1150" href="source/net/ipv4/af_inet.c#L1150">1150</a> {
<a name="L1151" href="source/net/ipv4/af_inet.c#L1151">1151</a>         struct <a href="ident?i=inet_sock">inet_sock</a> *inet = <a href="ident?i=inet_sk">inet_sk</a>(sk);
<a name="L1152" href="source/net/ipv4/af_inet.c#L1152">1152</a>         struct <a href="ident?i=rtable">rtable</a> *<a href="ident?i=rt">rt</a> = (struct <a href="ident?i=rtable">rtable</a> *)<a href="ident?i=__sk_dst_check">__sk_dst_check</a>(sk, 0);
<a name="L1153" href="source/net/ipv4/af_inet.c#L1153">1153</a>         <a href="ident?i=__be32">__be32</a> <a href="ident?i=daddr">daddr</a>;
<a name="L1154" href="source/net/ipv4/af_inet.c#L1154">1154</a>         struct <a href="ident?i=ip_options_rcu">ip_options_rcu</a> *inet_opt;
<a name="L1155" href="source/net/ipv4/af_inet.c#L1155">1155</a>         struct <a href="ident?i=flowi4">flowi4</a> *fl4;
<a name="L1156" href="source/net/ipv4/af_inet.c#L1156">1156</a>         int <a href="ident?i=err">err</a>;
<a name="L1157" href="source/net/ipv4/af_inet.c#L1157">1157</a> 
<a name="L1158" href="source/net/ipv4/af_inet.c#L1158">1158</a>         <b><i>/* Route is OK, nothing to do. */</i></b>
<a name="L1159" href="source/net/ipv4/af_inet.c#L1159">1159</a>         if (<a href="ident?i=rt">rt</a>)
<a name="L1160" href="source/net/ipv4/af_inet.c#L1160">1160</a>                 return 0;
<a name="L1161" href="source/net/ipv4/af_inet.c#L1161">1161</a> 
<a name="L1162" href="source/net/ipv4/af_inet.c#L1162">1162</a>         <b><i>/* Reroute. */</i></b>
<a name="L1163" href="source/net/ipv4/af_inet.c#L1163">1163</a>         <a href="ident?i=rcu_read_lock">rcu_read_lock</a>();
<a name="L1164" href="source/net/ipv4/af_inet.c#L1164">1164</a>         inet_opt = <a href="ident?i=rcu_dereference">rcu_dereference</a>(inet-&gt;inet_opt);
<a name="L1165" href="source/net/ipv4/af_inet.c#L1165">1165</a>         <a href="ident?i=daddr">daddr</a> = inet-&gt;<a href="ident?i=inet_daddr">inet_daddr</a>;
<a name="L1166" href="source/net/ipv4/af_inet.c#L1166">1166</a>         if (inet_opt &amp;&amp; inet_opt-&gt;opt.<a href="ident?i=srr">srr</a>)
<a name="L1167" href="source/net/ipv4/af_inet.c#L1167">1167</a>                 <a href="ident?i=daddr">daddr</a> = inet_opt-&gt;opt.faddr;
<a name="L1168" href="source/net/ipv4/af_inet.c#L1168">1168</a>         <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L1169" href="source/net/ipv4/af_inet.c#L1169">1169</a>         fl4 = &amp;inet-&gt;cork.fl.u.ip4;
<a name="L1170" href="source/net/ipv4/af_inet.c#L1170">1170</a>         <a href="ident?i=rt">rt</a> = <a href="ident?i=ip_route_output_ports">ip_route_output_ports</a>(<a href="ident?i=sock_net">sock_net</a>(sk), fl4, sk, <a href="ident?i=daddr">daddr</a>, inet-&gt;inet_saddr,
<a name="L1171" href="source/net/ipv4/af_inet.c#L1171">1171</a>                                    inet-&gt;<a href="ident?i=inet_dport">inet_dport</a>, inet-&gt;inet_sport,
<a name="L1172" href="source/net/ipv4/af_inet.c#L1172">1172</a>                                    sk-&gt;sk_protocol, <a href="ident?i=RT_CONN_FLAGS">RT_CONN_FLAGS</a>(sk),
<a name="L1173" href="source/net/ipv4/af_inet.c#L1173">1173</a>                                    sk-&gt;<a href="ident?i=sk_bound_dev_if">sk_bound_dev_if</a>);
<a name="L1174" href="source/net/ipv4/af_inet.c#L1174">1174</a>         if (!<a href="ident?i=IS_ERR">IS_ERR</a>(<a href="ident?i=rt">rt</a>)) {
<a name="L1175" href="source/net/ipv4/af_inet.c#L1175">1175</a>                 <a href="ident?i=err">err</a> = 0;
<a name="L1176" href="source/net/ipv4/af_inet.c#L1176">1176</a>                 <a href="ident?i=sk_setup_caps">sk_setup_caps</a>(sk, &amp;<a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>);
<a name="L1177" href="source/net/ipv4/af_inet.c#L1177">1177</a>         } else {
<a name="L1178" href="source/net/ipv4/af_inet.c#L1178">1178</a>                 <a href="ident?i=err">err</a> = <a href="ident?i=PTR_ERR">PTR_ERR</a>(<a href="ident?i=rt">rt</a>);
<a name="L1179" href="source/net/ipv4/af_inet.c#L1179">1179</a> 
<a name="L1180" href="source/net/ipv4/af_inet.c#L1180">1180</a>                 <b><i>/* Routing failed... */</i></b>
<a name="L1181" href="source/net/ipv4/af_inet.c#L1181">1181</a>                 sk-&gt;sk_route_caps = 0;
<a name="L1182" href="source/net/ipv4/af_inet.c#L1182">1182</a>                 <b><i>/*</i></b>
<a name="L1183" href="source/net/ipv4/af_inet.c#L1183">1183</a> <b><i>                 * Other protocols have to map its equivalent state to TCP_SYN_SENT.</i></b>
<a name="L1184" href="source/net/ipv4/af_inet.c#L1184">1184</a> <b><i>                 * DCCP maps its DCCP_REQUESTING state to TCP_SYN_SENT. -acme</i></b>
<a name="L1185" href="source/net/ipv4/af_inet.c#L1185">1185</a> <b><i>                 */</i></b>
<a name="L1186" href="source/net/ipv4/af_inet.c#L1186">1186</a>                 if (!<a href="ident?i=sysctl_ip_dynaddr">sysctl_ip_dynaddr</a> ||
<a name="L1187" href="source/net/ipv4/af_inet.c#L1187">1187</a>                     sk-&gt;<a href="ident?i=sk_state">sk_state</a> != TCP_SYN_SENT ||
<a name="L1188" href="source/net/ipv4/af_inet.c#L1188">1188</a>                     (sk-&gt;sk_userlocks &amp; <a href="ident?i=SOCK_BINDADDR_LOCK">SOCK_BINDADDR_LOCK</a>) ||
<a name="L1189" href="source/net/ipv4/af_inet.c#L1189">1189</a>                     (<a href="ident?i=err">err</a> = <a href="ident?i=inet_sk_reselect_saddr">inet_sk_reselect_saddr</a>(sk)) != 0)
<a name="L1190" href="source/net/ipv4/af_inet.c#L1190">1190</a>                         sk-&gt;sk_err_soft = -<a href="ident?i=err">err</a>;
<a name="L1191" href="source/net/ipv4/af_inet.c#L1191">1191</a>         }
<a name="L1192" href="source/net/ipv4/af_inet.c#L1192">1192</a> 
<a name="L1193" href="source/net/ipv4/af_inet.c#L1193">1193</a>         return <a href="ident?i=err">err</a>;
<a name="L1194" href="source/net/ipv4/af_inet.c#L1194">1194</a> }
<a name="L1195" href="source/net/ipv4/af_inet.c#L1195">1195</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=inet_sk_rebuild_header">inet_sk_rebuild_header</a>);
<a name="L1196" href="source/net/ipv4/af_inet.c#L1196">1196</a> 
<a name="L1197" href="source/net/ipv4/af_inet.c#L1197">1197</a> static struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=inet_gso_segment">inet_gso_segment</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
<a name="L1198" href="source/net/ipv4/af_inet.c#L1198">1198</a>                                         <a href="ident?i=netdev_features_t">netdev_features_t</a> <a href="ident?i=features">features</a>)
<a name="L1199" href="source/net/ipv4/af_inet.c#L1199">1199</a> {
<a name="L1200" href="source/net/ipv4/af_inet.c#L1200">1200</a>         struct <a href="ident?i=sk_buff">sk_buff</a> *segs = <a href="ident?i=ERR_PTR">ERR_PTR</a>(-<a href="ident?i=EINVAL">EINVAL</a>);
<a name="L1201" href="source/net/ipv4/af_inet.c#L1201">1201</a>         const struct <a href="ident?i=net_offload">net_offload</a> *<a href="ident?i=ops">ops</a>;
<a name="L1202" href="source/net/ipv4/af_inet.c#L1202">1202</a>         unsigned int <a href="ident?i=offset">offset</a> = 0;
<a name="L1203" href="source/net/ipv4/af_inet.c#L1203">1203</a>         <a href="ident?i=bool">bool</a> udpfrag, encap;
<a name="L1204" href="source/net/ipv4/af_inet.c#L1204">1204</a>         struct <a href="ident?i=iphdr">iphdr</a> *iph;
<a name="L1205" href="source/net/ipv4/af_inet.c#L1205">1205</a>         int <a href="ident?i=proto">proto</a>;
<a name="L1206" href="source/net/ipv4/af_inet.c#L1206">1206</a>         int nhoff;
<a name="L1207" href="source/net/ipv4/af_inet.c#L1207">1207</a>         int ihl;
<a name="L1208" href="source/net/ipv4/af_inet.c#L1208">1208</a>         int <a href="ident?i=id">id</a>;
<a name="L1209" href="source/net/ipv4/af_inet.c#L1209">1209</a> 
<a name="L1210" href="source/net/ipv4/af_inet.c#L1210">1210</a>         if (<a href="ident?i=unlikely">unlikely</a>(<a href="ident?i=skb_shinfo">skb_shinfo</a>(<a href="ident?i=skb">skb</a>)-&gt;gso_type &amp;
<a name="L1211" href="source/net/ipv4/af_inet.c#L1211">1211</a>                      ~(SKB_GSO_TCPV4 |
<a name="L1212" href="source/net/ipv4/af_inet.c#L1212">1212</a>                        SKB_GSO_UDP |
<a name="L1213" href="source/net/ipv4/af_inet.c#L1213">1213</a>                        SKB_GSO_DODGY |
<a name="L1214" href="source/net/ipv4/af_inet.c#L1214">1214</a>                        SKB_GSO_TCP_ECN |
<a name="L1215" href="source/net/ipv4/af_inet.c#L1215">1215</a>                        SKB_GSO_GRE |
<a name="L1216" href="source/net/ipv4/af_inet.c#L1216">1216</a>                        SKB_GSO_GRE_CSUM |
<a name="L1217" href="source/net/ipv4/af_inet.c#L1217">1217</a>                        SKB_GSO_IPIP |
<a name="L1218" href="source/net/ipv4/af_inet.c#L1218">1218</a>                        SKB_GSO_SIT |
<a name="L1219" href="source/net/ipv4/af_inet.c#L1219">1219</a>                        SKB_GSO_TCPV6 |
<a name="L1220" href="source/net/ipv4/af_inet.c#L1220">1220</a>                        SKB_GSO_UDP_TUNNEL |
<a name="L1221" href="source/net/ipv4/af_inet.c#L1221">1221</a>                        SKB_GSO_UDP_TUNNEL_CSUM |
<a name="L1222" href="source/net/ipv4/af_inet.c#L1222">1222</a>                        SKB_GSO_TUNNEL_REMCSUM |
<a name="L1223" href="source/net/ipv4/af_inet.c#L1223">1223</a>                        0)))
<a name="L1224" href="source/net/ipv4/af_inet.c#L1224">1224</a>                 goto <a href="ident?i=out">out</a>;
<a name="L1225" href="source/net/ipv4/af_inet.c#L1225">1225</a> 
<a name="L1226" href="source/net/ipv4/af_inet.c#L1226">1226</a>         <a href="ident?i=skb_reset_network_header">skb_reset_network_header</a>(<a href="ident?i=skb">skb</a>);
<a name="L1227" href="source/net/ipv4/af_inet.c#L1227">1227</a>         nhoff = <a href="ident?i=skb_network_header">skb_network_header</a>(<a href="ident?i=skb">skb</a>) - <a href="ident?i=skb_mac_header">skb_mac_header</a>(<a href="ident?i=skb">skb</a>);
<a name="L1228" href="source/net/ipv4/af_inet.c#L1228">1228</a>         if (<a href="ident?i=unlikely">unlikely</a>(!<a href="ident?i=pskb_may_pull">pskb_may_pull</a>(<a href="ident?i=skb">skb</a>, sizeof(*iph))))
<a name="L1229" href="source/net/ipv4/af_inet.c#L1229">1229</a>                 goto <a href="ident?i=out">out</a>;
<a name="L1230" href="source/net/ipv4/af_inet.c#L1230">1230</a> 
<a name="L1231" href="source/net/ipv4/af_inet.c#L1231">1231</a>         iph = <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>);
<a name="L1232" href="source/net/ipv4/af_inet.c#L1232">1232</a>         ihl = iph-&gt;ihl * 4;
<a name="L1233" href="source/net/ipv4/af_inet.c#L1233">1233</a>         if (ihl &lt; sizeof(*iph))
<a name="L1234" href="source/net/ipv4/af_inet.c#L1234">1234</a>                 goto <a href="ident?i=out">out</a>;
<a name="L1235" href="source/net/ipv4/af_inet.c#L1235">1235</a> 
<a name="L1236" href="source/net/ipv4/af_inet.c#L1236">1236</a>         <a href="ident?i=id">id</a> = <a href="ident?i=ntohs">ntohs</a>(iph-&gt;<a href="ident?i=id">id</a>);
<a name="L1237" href="source/net/ipv4/af_inet.c#L1237">1237</a>         <a href="ident?i=proto">proto</a> = iph-&gt;<a href="ident?i=protocol">protocol</a>;
<a name="L1238" href="source/net/ipv4/af_inet.c#L1238">1238</a> 
<a name="L1239" href="source/net/ipv4/af_inet.c#L1239">1239</a>         <b><i>/* Warning: after this point, iph might be no longer valid */</i></b>
<a name="L1240" href="source/net/ipv4/af_inet.c#L1240">1240</a>         if (<a href="ident?i=unlikely">unlikely</a>(!<a href="ident?i=pskb_may_pull">pskb_may_pull</a>(<a href="ident?i=skb">skb</a>, ihl)))
<a name="L1241" href="source/net/ipv4/af_inet.c#L1241">1241</a>                 goto <a href="ident?i=out">out</a>;
<a name="L1242" href="source/net/ipv4/af_inet.c#L1242">1242</a>         <a href="ident?i=__skb_pull">__skb_pull</a>(<a href="ident?i=skb">skb</a>, ihl);
<a name="L1243" href="source/net/ipv4/af_inet.c#L1243">1243</a> 
<a name="L1244" href="source/net/ipv4/af_inet.c#L1244">1244</a>         encap = <a href="ident?i=SKB_GSO_CB">SKB_GSO_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;encap_level &gt; 0;
<a name="L1245" href="source/net/ipv4/af_inet.c#L1245">1245</a>         if (encap)
<a name="L1246" href="source/net/ipv4/af_inet.c#L1246">1246</a>                 <a href="ident?i=features">features</a> &amp;= <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=dev">dev</a>-&gt;hw_enc_features;
<a name="L1247" href="source/net/ipv4/af_inet.c#L1247">1247</a>         <a href="ident?i=SKB_GSO_CB">SKB_GSO_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;encap_level += ihl;
<a name="L1248" href="source/net/ipv4/af_inet.c#L1248">1248</a> 
<a name="L1249" href="source/net/ipv4/af_inet.c#L1249">1249</a>         <a href="ident?i=skb_reset_transport_header">skb_reset_transport_header</a>(<a href="ident?i=skb">skb</a>);
<a name="L1250" href="source/net/ipv4/af_inet.c#L1250">1250</a> 
<a name="L1251" href="source/net/ipv4/af_inet.c#L1251">1251</a>         segs = <a href="ident?i=ERR_PTR">ERR_PTR</a>(-<a href="ident?i=EPROTONOSUPPORT">EPROTONOSUPPORT</a>);
<a name="L1252" href="source/net/ipv4/af_inet.c#L1252">1252</a> 
<a name="L1253" href="source/net/ipv4/af_inet.c#L1253">1253</a>         if (<a href="ident?i=skb">skb</a>-&gt;encapsulation &amp;&amp;
<a name="L1254" href="source/net/ipv4/af_inet.c#L1254">1254</a>             <a href="ident?i=skb_shinfo">skb_shinfo</a>(<a href="ident?i=skb">skb</a>)-&gt;gso_type &amp; (SKB_GSO_SIT|SKB_GSO_IPIP))
<a name="L1255" href="source/net/ipv4/af_inet.c#L1255">1255</a>                 udpfrag = <a href="ident?i=proto">proto</a> == <a href="ident?i=IPPROTO_UDP">IPPROTO_UDP</a> &amp;&amp; encap;
<a name="L1256" href="source/net/ipv4/af_inet.c#L1256">1256</a>         else
<a name="L1257" href="source/net/ipv4/af_inet.c#L1257">1257</a>                 udpfrag = <a href="ident?i=proto">proto</a> == <a href="ident?i=IPPROTO_UDP">IPPROTO_UDP</a> &amp;&amp; !<a href="ident?i=skb">skb</a>-&gt;encapsulation;
<a name="L1258" href="source/net/ipv4/af_inet.c#L1258">1258</a> 
<a name="L1259" href="source/net/ipv4/af_inet.c#L1259">1259</a>         <a href="ident?i=ops">ops</a> = <a href="ident?i=rcu_dereference">rcu_dereference</a>(<a href="ident?i=inet_offloads">inet_offloads</a>[<a href="ident?i=proto">proto</a>]);
<a name="L1260" href="source/net/ipv4/af_inet.c#L1260">1260</a>         if (<a href="ident?i=likely">likely</a>(<a href="ident?i=ops">ops</a> &amp;&amp; <a href="ident?i=ops">ops</a>-&gt;<a href="ident?i=callbacks">callbacks</a>.gso_segment))
<a name="L1261" href="source/net/ipv4/af_inet.c#L1261">1261</a>                 segs = <a href="ident?i=ops">ops</a>-&gt;<a href="ident?i=callbacks">callbacks</a>.gso_segment(<a href="ident?i=skb">skb</a>, <a href="ident?i=features">features</a>);
<a name="L1262" href="source/net/ipv4/af_inet.c#L1262">1262</a> 
<a name="L1263" href="source/net/ipv4/af_inet.c#L1263">1263</a>         if (<a href="ident?i=IS_ERR_OR_NULL">IS_ERR_OR_NULL</a>(segs))
<a name="L1264" href="source/net/ipv4/af_inet.c#L1264">1264</a>                 goto <a href="ident?i=out">out</a>;
<a name="L1265" href="source/net/ipv4/af_inet.c#L1265">1265</a> 
<a name="L1266" href="source/net/ipv4/af_inet.c#L1266">1266</a>         <a href="ident?i=skb">skb</a> = segs;
<a name="L1267" href="source/net/ipv4/af_inet.c#L1267">1267</a>         do {
<a name="L1268" href="source/net/ipv4/af_inet.c#L1268">1268</a>                 iph = (struct <a href="ident?i=iphdr">iphdr</a> *)(<a href="ident?i=skb_mac_header">skb_mac_header</a>(<a href="ident?i=skb">skb</a>) + nhoff);
<a name="L1269" href="source/net/ipv4/af_inet.c#L1269">1269</a>                 if (udpfrag) {
<a name="L1270" href="source/net/ipv4/af_inet.c#L1270">1270</a>                         iph-&gt;<a href="ident?i=id">id</a> = <a href="ident?i=htons">htons</a>(<a href="ident?i=id">id</a>);
<a name="L1271" href="source/net/ipv4/af_inet.c#L1271">1271</a>                         iph-&gt;frag_off = <a href="ident?i=htons">htons</a>(<a href="ident?i=offset">offset</a> &gt;&gt; 3);
<a name="L1272" href="source/net/ipv4/af_inet.c#L1272">1272</a>                         if (<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=next">next</a>)
<a name="L1273" href="source/net/ipv4/af_inet.c#L1273">1273</a>                                 iph-&gt;frag_off |= <a href="ident?i=htons">htons</a>(<a href="ident?i=IP_MF">IP_MF</a>);
<a name="L1274" href="source/net/ipv4/af_inet.c#L1274">1274</a>                         <a href="ident?i=offset">offset</a> += <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a> - nhoff - ihl;
<a name="L1275" href="source/net/ipv4/af_inet.c#L1275">1275</a>                 } else {
<a name="L1276" href="source/net/ipv4/af_inet.c#L1276">1276</a>                         iph-&gt;<a href="ident?i=id">id</a> = <a href="ident?i=htons">htons</a>(<a href="ident?i=id">id</a>++);
<a name="L1277" href="source/net/ipv4/af_inet.c#L1277">1277</a>                 }
<a name="L1278" href="source/net/ipv4/af_inet.c#L1278">1278</a>                 iph-&gt;tot_len = <a href="ident?i=htons">htons</a>(<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a> - nhoff);
<a name="L1279" href="source/net/ipv4/af_inet.c#L1279">1279</a>                 <a href="ident?i=ip_send_check">ip_send_check</a>(iph);
<a name="L1280" href="source/net/ipv4/af_inet.c#L1280">1280</a>                 if (encap)
<a name="L1281" href="source/net/ipv4/af_inet.c#L1281">1281</a>                         <a href="ident?i=skb_reset_inner_headers">skb_reset_inner_headers</a>(<a href="ident?i=skb">skb</a>);
<a name="L1282" href="source/net/ipv4/af_inet.c#L1282">1282</a>                 <a href="ident?i=skb">skb</a>-&gt;network_header = (<a href="ident?i=u8">u8</a> *)iph - <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=head">head</a>;
<a name="L1283" href="source/net/ipv4/af_inet.c#L1283">1283</a>         } while ((<a href="ident?i=skb">skb</a> = <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=next">next</a>));
<a name="L1284" href="source/net/ipv4/af_inet.c#L1284">1284</a> 
<a name="L1285" href="source/net/ipv4/af_inet.c#L1285">1285</a> <a href="ident?i=out">out</a>:
<a name="L1286" href="source/net/ipv4/af_inet.c#L1286">1286</a>         return segs;
<a name="L1287" href="source/net/ipv4/af_inet.c#L1287">1287</a> }
<a name="L1288" href="source/net/ipv4/af_inet.c#L1288">1288</a> 
<a name="L1289" href="source/net/ipv4/af_inet.c#L1289">1289</a> static struct <a href="ident?i=sk_buff">sk_buff</a> **<a href="ident?i=inet_gro_receive">inet_gro_receive</a>(struct <a href="ident?i=sk_buff">sk_buff</a> **<a href="ident?i=head">head</a>,
<a name="L1290" href="source/net/ipv4/af_inet.c#L1290">1290</a>                                          struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L1291" href="source/net/ipv4/af_inet.c#L1291">1291</a> {
<a name="L1292" href="source/net/ipv4/af_inet.c#L1292">1292</a>         const struct <a href="ident?i=net_offload">net_offload</a> *<a href="ident?i=ops">ops</a>;
<a name="L1293" href="source/net/ipv4/af_inet.c#L1293">1293</a>         struct <a href="ident?i=sk_buff">sk_buff</a> **pp = <a href="ident?i=NULL">NULL</a>;
<a name="L1294" href="source/net/ipv4/af_inet.c#L1294">1294</a>         struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=p">p</a>;
<a name="L1295" href="source/net/ipv4/af_inet.c#L1295">1295</a>         const struct <a href="ident?i=iphdr">iphdr</a> *iph;
<a name="L1296" href="source/net/ipv4/af_inet.c#L1296">1296</a>         unsigned int hlen;
<a name="L1297" href="source/net/ipv4/af_inet.c#L1297">1297</a>         unsigned int <a href="ident?i=off">off</a>;
<a name="L1298" href="source/net/ipv4/af_inet.c#L1298">1298</a>         unsigned int <a href="ident?i=id">id</a>;
<a name="L1299" href="source/net/ipv4/af_inet.c#L1299">1299</a>         int <a href="ident?i=flush">flush</a> = 1;
<a name="L1300" href="source/net/ipv4/af_inet.c#L1300">1300</a>         int <a href="ident?i=proto">proto</a>;
<a name="L1301" href="source/net/ipv4/af_inet.c#L1301">1301</a> 
<a name="L1302" href="source/net/ipv4/af_inet.c#L1302">1302</a>         <a href="ident?i=off">off</a> = <a href="ident?i=skb_gro_offset">skb_gro_offset</a>(<a href="ident?i=skb">skb</a>);
<a name="L1303" href="source/net/ipv4/af_inet.c#L1303">1303</a>         hlen = <a href="ident?i=off">off</a> + sizeof(*iph);
<a name="L1304" href="source/net/ipv4/af_inet.c#L1304">1304</a>         iph = <a href="ident?i=skb_gro_header_fast">skb_gro_header_fast</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=off">off</a>);
<a name="L1305" href="source/net/ipv4/af_inet.c#L1305">1305</a>         if (<a href="ident?i=skb_gro_header_hard">skb_gro_header_hard</a>(<a href="ident?i=skb">skb</a>, hlen)) {
<a name="L1306" href="source/net/ipv4/af_inet.c#L1306">1306</a>                 iph = <a href="ident?i=skb_gro_header_slow">skb_gro_header_slow</a>(<a href="ident?i=skb">skb</a>, hlen, <a href="ident?i=off">off</a>);
<a name="L1307" href="source/net/ipv4/af_inet.c#L1307">1307</a>                 if (<a href="ident?i=unlikely">unlikely</a>(!iph))
<a name="L1308" href="source/net/ipv4/af_inet.c#L1308">1308</a>                         goto <a href="ident?i=out">out</a>;
<a name="L1309" href="source/net/ipv4/af_inet.c#L1309">1309</a>         }
<a name="L1310" href="source/net/ipv4/af_inet.c#L1310">1310</a> 
<a name="L1311" href="source/net/ipv4/af_inet.c#L1311">1311</a>         <a href="ident?i=proto">proto</a> = iph-&gt;<a href="ident?i=protocol">protocol</a>;
<a name="L1312" href="source/net/ipv4/af_inet.c#L1312">1312</a> 
<a name="L1313" href="source/net/ipv4/af_inet.c#L1313">1313</a>         <a href="ident?i=rcu_read_lock">rcu_read_lock</a>();
<a name="L1314" href="source/net/ipv4/af_inet.c#L1314">1314</a>         <a href="ident?i=ops">ops</a> = <a href="ident?i=rcu_dereference">rcu_dereference</a>(<a href="ident?i=inet_offloads">inet_offloads</a>[<a href="ident?i=proto">proto</a>]);
<a name="L1315" href="source/net/ipv4/af_inet.c#L1315">1315</a>         if (!<a href="ident?i=ops">ops</a> || !<a href="ident?i=ops">ops</a>-&gt;<a href="ident?i=callbacks">callbacks</a>.gro_receive)
<a name="L1316" href="source/net/ipv4/af_inet.c#L1316">1316</a>                 goto out_unlock;
<a name="L1317" href="source/net/ipv4/af_inet.c#L1317">1317</a> 
<a name="L1318" href="source/net/ipv4/af_inet.c#L1318">1318</a>         if (*(<a href="ident?i=u8">u8</a> *)iph != 0x45)
<a name="L1319" href="source/net/ipv4/af_inet.c#L1319">1319</a>                 goto out_unlock;
<a name="L1320" href="source/net/ipv4/af_inet.c#L1320">1320</a> 
<a name="L1321" href="source/net/ipv4/af_inet.c#L1321">1321</a>         if (<a href="ident?i=unlikely">unlikely</a>(<a href="ident?i=ip_fast_csum">ip_fast_csum</a>((<a href="ident?i=u8">u8</a> *)iph, 5)))
<a name="L1322" href="source/net/ipv4/af_inet.c#L1322">1322</a>                 goto out_unlock;
<a name="L1323" href="source/net/ipv4/af_inet.c#L1323">1323</a> 
<a name="L1324" href="source/net/ipv4/af_inet.c#L1324">1324</a>         <a href="ident?i=id">id</a> = <a href="ident?i=ntohl">ntohl</a>(*(<a href="ident?i=__be32">__be32</a> *)&amp;iph-&gt;<a href="ident?i=id">id</a>);
<a name="L1325" href="source/net/ipv4/af_inet.c#L1325">1325</a>         <a href="ident?i=flush">flush</a> = (<a href="ident?i=u16">u16</a>)((<a href="ident?i=ntohl">ntohl</a>(*(<a href="ident?i=__be32">__be32</a> *)iph) ^ <a href="ident?i=skb_gro_len">skb_gro_len</a>(<a href="ident?i=skb">skb</a>)) | (<a href="ident?i=id">id</a> &amp; ~IP_DF));
<a name="L1326" href="source/net/ipv4/af_inet.c#L1326">1326</a>         <a href="ident?i=id">id</a> &gt;&gt;= 16;
<a name="L1327" href="source/net/ipv4/af_inet.c#L1327">1327</a> 
<a name="L1328" href="source/net/ipv4/af_inet.c#L1328">1328</a>         for (<a href="ident?i=p">p</a> = *<a href="ident?i=head">head</a>; <a href="ident?i=p">p</a>; <a href="ident?i=p">p</a> = <a href="ident?i=p">p</a>-&gt;<a href="ident?i=next">next</a>) {
<a name="L1329" href="source/net/ipv4/af_inet.c#L1329">1329</a>                 struct <a href="ident?i=iphdr">iphdr</a> *iph2;
<a name="L1330" href="source/net/ipv4/af_inet.c#L1330">1330</a> 
<a name="L1331" href="source/net/ipv4/af_inet.c#L1331">1331</a>                 if (!<a href="ident?i=NAPI_GRO_CB">NAPI_GRO_CB</a>(<a href="ident?i=p">p</a>)-&gt;same_flow)
<a name="L1332" href="source/net/ipv4/af_inet.c#L1332">1332</a>                         continue;
<a name="L1333" href="source/net/ipv4/af_inet.c#L1333">1333</a> 
<a name="L1334" href="source/net/ipv4/af_inet.c#L1334">1334</a>                 iph2 = (struct <a href="ident?i=iphdr">iphdr</a> *)(<a href="ident?i=p">p</a>-&gt;<a href="ident?i=data">data</a> + <a href="ident?i=off">off</a>);
<a name="L1335" href="source/net/ipv4/af_inet.c#L1335">1335</a>                 <b><i>/* The above works because, with the exception of the top</i></b>
<a name="L1336" href="source/net/ipv4/af_inet.c#L1336">1336</a> <b><i>                 * (inner most) layer, we only aggregate pkts with the same</i></b>
<a name="L1337" href="source/net/ipv4/af_inet.c#L1337">1337</a> <b><i>                 * hdr length so all the hdrs we'll need to verify will start</i></b>
<a name="L1338" href="source/net/ipv4/af_inet.c#L1338">1338</a> <b><i>                 * at the same offset.</i></b>
<a name="L1339" href="source/net/ipv4/af_inet.c#L1339">1339</a> <b><i>                 */</i></b>
<a name="L1340" href="source/net/ipv4/af_inet.c#L1340">1340</a>                 if ((iph-&gt;<a href="ident?i=protocol">protocol</a> ^ iph2-&gt;<a href="ident?i=protocol">protocol</a>) |
<a name="L1341" href="source/net/ipv4/af_inet.c#L1341">1341</a>                     ((<a href="ident?i=__force">__force</a> <a href="ident?i=u32">u32</a>)iph-&gt;<a href="ident?i=saddr">saddr</a> ^ (<a href="ident?i=__force">__force</a> <a href="ident?i=u32">u32</a>)iph2-&gt;<a href="ident?i=saddr">saddr</a>) |
<a name="L1342" href="source/net/ipv4/af_inet.c#L1342">1342</a>                     ((<a href="ident?i=__force">__force</a> <a href="ident?i=u32">u32</a>)iph-&gt;<a href="ident?i=daddr">daddr</a> ^ (<a href="ident?i=__force">__force</a> <a href="ident?i=u32">u32</a>)iph2-&gt;<a href="ident?i=daddr">daddr</a>)) {
<a name="L1343" href="source/net/ipv4/af_inet.c#L1343">1343</a>                         <a href="ident?i=NAPI_GRO_CB">NAPI_GRO_CB</a>(<a href="ident?i=p">p</a>)-&gt;same_flow = 0;
<a name="L1344" href="source/net/ipv4/af_inet.c#L1344">1344</a>                         continue;
<a name="L1345" href="source/net/ipv4/af_inet.c#L1345">1345</a>                 }
<a name="L1346" href="source/net/ipv4/af_inet.c#L1346">1346</a> 
<a name="L1347" href="source/net/ipv4/af_inet.c#L1347">1347</a>                 <b><i>/* All fields must match except length and checksum. */</i></b>
<a name="L1348" href="source/net/ipv4/af_inet.c#L1348">1348</a>                 <a href="ident?i=NAPI_GRO_CB">NAPI_GRO_CB</a>(<a href="ident?i=p">p</a>)-&gt;<a href="ident?i=flush">flush</a> |=
<a name="L1349" href="source/net/ipv4/af_inet.c#L1349">1349</a>                         (iph-&gt;<a href="ident?i=ttl">ttl</a> ^ iph2-&gt;<a href="ident?i=ttl">ttl</a>) |
<a name="L1350" href="source/net/ipv4/af_inet.c#L1350">1350</a>                         (iph-&gt;tos ^ iph2-&gt;tos) |
<a name="L1351" href="source/net/ipv4/af_inet.c#L1351">1351</a>                         ((iph-&gt;frag_off ^ iph2-&gt;frag_off) &amp; <a href="ident?i=htons">htons</a>(<a href="ident?i=IP_DF">IP_DF</a>));
<a name="L1352" href="source/net/ipv4/af_inet.c#L1352">1352</a> 
<a name="L1353" href="source/net/ipv4/af_inet.c#L1353">1353</a>                 <b><i>/* Save the IP ID check to be included later when we get to</i></b>
<a name="L1354" href="source/net/ipv4/af_inet.c#L1354">1354</a> <b><i>                 * the transport layer so only the inner most IP ID is checked.</i></b>
<a name="L1355" href="source/net/ipv4/af_inet.c#L1355">1355</a> <b><i>                 * This is because some GSO/TSO implementations do not</i></b>
<a name="L1356" href="source/net/ipv4/af_inet.c#L1356">1356</a> <b><i>                 * correctly increment the IP ID for the outer hdrs.</i></b>
<a name="L1357" href="source/net/ipv4/af_inet.c#L1357">1357</a> <b><i>                 */</i></b>
<a name="L1358" href="source/net/ipv4/af_inet.c#L1358">1358</a>                 <a href="ident?i=NAPI_GRO_CB">NAPI_GRO_CB</a>(<a href="ident?i=p">p</a>)-&gt;flush_id =
<a name="L1359" href="source/net/ipv4/af_inet.c#L1359">1359</a>                             ((<a href="ident?i=u16">u16</a>)(<a href="ident?i=ntohs">ntohs</a>(iph2-&gt;<a href="ident?i=id">id</a>) + <a href="ident?i=NAPI_GRO_CB">NAPI_GRO_CB</a>(<a href="ident?i=p">p</a>)-&gt;<a href="ident?i=count">count</a>) ^ <a href="ident?i=id">id</a>);
<a name="L1360" href="source/net/ipv4/af_inet.c#L1360">1360</a>                 <a href="ident?i=NAPI_GRO_CB">NAPI_GRO_CB</a>(<a href="ident?i=p">p</a>)-&gt;<a href="ident?i=flush">flush</a> |= <a href="ident?i=flush">flush</a>;
<a name="L1361" href="source/net/ipv4/af_inet.c#L1361">1361</a>         }
<a name="L1362" href="source/net/ipv4/af_inet.c#L1362">1362</a> 
<a name="L1363" href="source/net/ipv4/af_inet.c#L1363">1363</a>         <a href="ident?i=NAPI_GRO_CB">NAPI_GRO_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=flush">flush</a> |= <a href="ident?i=flush">flush</a>;
<a name="L1364" href="source/net/ipv4/af_inet.c#L1364">1364</a>         <a href="ident?i=skb_set_network_header">skb_set_network_header</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=off">off</a>);
<a name="L1365" href="source/net/ipv4/af_inet.c#L1365">1365</a>         <b><i>/* The above will be needed by the transport layer if there is one</i></b>
<a name="L1366" href="source/net/ipv4/af_inet.c#L1366">1366</a> <b><i>         * immediately following this IP hdr.</i></b>
<a name="L1367" href="source/net/ipv4/af_inet.c#L1367">1367</a> <b><i>         */</i></b>
<a name="L1368" href="source/net/ipv4/af_inet.c#L1368">1368</a> 
<a name="L1369" href="source/net/ipv4/af_inet.c#L1369">1369</a>         <b><i>/* Note : No need to call skb_gro_postpull_rcsum() here,</i></b>
<a name="L1370" href="source/net/ipv4/af_inet.c#L1370">1370</a> <b><i>         * as we already checked checksum over ipv4 header was 0</i></b>
<a name="L1371" href="source/net/ipv4/af_inet.c#L1371">1371</a> <b><i>         */</i></b>
<a name="L1372" href="source/net/ipv4/af_inet.c#L1372">1372</a>         <a href="ident?i=skb_gro_pull">skb_gro_pull</a>(<a href="ident?i=skb">skb</a>, sizeof(*iph));
<a name="L1373" href="source/net/ipv4/af_inet.c#L1373">1373</a>         <a href="ident?i=skb_set_transport_header">skb_set_transport_header</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=skb_gro_offset">skb_gro_offset</a>(<a href="ident?i=skb">skb</a>));
<a name="L1374" href="source/net/ipv4/af_inet.c#L1374">1374</a> 
<a name="L1375" href="source/net/ipv4/af_inet.c#L1375">1375</a>         pp = <a href="ident?i=ops">ops</a>-&gt;<a href="ident?i=callbacks">callbacks</a>.gro_receive(<a href="ident?i=head">head</a>, <a href="ident?i=skb">skb</a>);
<a name="L1376" href="source/net/ipv4/af_inet.c#L1376">1376</a> 
<a name="L1377" href="source/net/ipv4/af_inet.c#L1377">1377</a> out_unlock:
<a name="L1378" href="source/net/ipv4/af_inet.c#L1378">1378</a>         <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L1379" href="source/net/ipv4/af_inet.c#L1379">1379</a> 
<a name="L1380" href="source/net/ipv4/af_inet.c#L1380">1380</a> <a href="ident?i=out">out</a>:
<a name="L1381" href="source/net/ipv4/af_inet.c#L1381">1381</a>         <a href="ident?i=NAPI_GRO_CB">NAPI_GRO_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=flush">flush</a> |= <a href="ident?i=flush">flush</a>;
<a name="L1382" href="source/net/ipv4/af_inet.c#L1382">1382</a> 
<a name="L1383" href="source/net/ipv4/af_inet.c#L1383">1383</a>         return pp;
<a name="L1384" href="source/net/ipv4/af_inet.c#L1384">1384</a> }
<a name="L1385" href="source/net/ipv4/af_inet.c#L1385">1385</a> 
<a name="L1386" href="source/net/ipv4/af_inet.c#L1386">1386</a> int <a href="ident?i=inet_recv_error">inet_recv_error</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=msghdr">msghdr</a> *<a href="ident?i=msg">msg</a>, int <a href="ident?i=len">len</a>, int *addr_len)
<a name="L1387" href="source/net/ipv4/af_inet.c#L1387">1387</a> {
<a name="L1388" href="source/net/ipv4/af_inet.c#L1388">1388</a>         if (sk-&gt;<a href="ident?i=sk_family">sk_family</a> == <a href="ident?i=AF_INET">AF_INET</a>)
<a name="L1389" href="source/net/ipv4/af_inet.c#L1389">1389</a>                 return <a href="ident?i=ip_recv_error">ip_recv_error</a>(sk, <a href="ident?i=msg">msg</a>, <a href="ident?i=len">len</a>, addr_len);
<a name="L1390" href="source/net/ipv4/af_inet.c#L1390">1390</a> #if <a href="ident?i=IS_ENABLED">IS_ENABLED</a>(CONFIG_IPV6)
<a name="L1391" href="source/net/ipv4/af_inet.c#L1391">1391</a>         if (sk-&gt;<a href="ident?i=sk_family">sk_family</a> == <a href="ident?i=AF_INET6">AF_INET6</a>)
<a name="L1392" href="source/net/ipv4/af_inet.c#L1392">1392</a>                 return <a href="ident?i=pingv6_ops">pingv6_ops</a>.<a href="ident?i=ipv6_recv_error">ipv6_recv_error</a>(sk, <a href="ident?i=msg">msg</a>, <a href="ident?i=len">len</a>, addr_len);
<a name="L1393" href="source/net/ipv4/af_inet.c#L1393">1393</a> #endif
<a name="L1394" href="source/net/ipv4/af_inet.c#L1394">1394</a>         return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L1395" href="source/net/ipv4/af_inet.c#L1395">1395</a> }
<a name="L1396" href="source/net/ipv4/af_inet.c#L1396">1396</a> 
<a name="L1397" href="source/net/ipv4/af_inet.c#L1397">1397</a> static int <a href="ident?i=inet_gro_complete">inet_gro_complete</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, int nhoff)
<a name="L1398" href="source/net/ipv4/af_inet.c#L1398">1398</a> {
<a name="L1399" href="source/net/ipv4/af_inet.c#L1399">1399</a>         <a href="ident?i=__be16">__be16</a> newlen = <a href="ident?i=htons">htons</a>(<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a> - nhoff);
<a name="L1400" href="source/net/ipv4/af_inet.c#L1400">1400</a>         struct <a href="ident?i=iphdr">iphdr</a> *iph = (struct <a href="ident?i=iphdr">iphdr</a> *)(<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=data">data</a> + nhoff);
<a name="L1401" href="source/net/ipv4/af_inet.c#L1401">1401</a>         const struct <a href="ident?i=net_offload">net_offload</a> *<a href="ident?i=ops">ops</a>;
<a name="L1402" href="source/net/ipv4/af_inet.c#L1402">1402</a>         int <a href="ident?i=proto">proto</a> = iph-&gt;<a href="ident?i=protocol">protocol</a>;
<a name="L1403" href="source/net/ipv4/af_inet.c#L1403">1403</a>         int <a href="ident?i=err">err</a> = -<a href="ident?i=ENOSYS">ENOSYS</a>;
<a name="L1404" href="source/net/ipv4/af_inet.c#L1404">1404</a> 
<a name="L1405" href="source/net/ipv4/af_inet.c#L1405">1405</a>         if (<a href="ident?i=skb">skb</a>-&gt;encapsulation)
<a name="L1406" href="source/net/ipv4/af_inet.c#L1406">1406</a>                 <a href="ident?i=skb_set_inner_network_header">skb_set_inner_network_header</a>(<a href="ident?i=skb">skb</a>, nhoff);
<a name="L1407" href="source/net/ipv4/af_inet.c#L1407">1407</a> 
<a name="L1408" href="source/net/ipv4/af_inet.c#L1408">1408</a>         <a href="ident?i=csum_replace2">csum_replace2</a>(&amp;iph-&gt;<a href="ident?i=check">check</a>, iph-&gt;tot_len, newlen);
<a name="L1409" href="source/net/ipv4/af_inet.c#L1409">1409</a>         iph-&gt;tot_len = newlen;
<a name="L1410" href="source/net/ipv4/af_inet.c#L1410">1410</a> 
<a name="L1411" href="source/net/ipv4/af_inet.c#L1411">1411</a>         <a href="ident?i=rcu_read_lock">rcu_read_lock</a>();
<a name="L1412" href="source/net/ipv4/af_inet.c#L1412">1412</a>         <a href="ident?i=ops">ops</a> = <a href="ident?i=rcu_dereference">rcu_dereference</a>(<a href="ident?i=inet_offloads">inet_offloads</a>[<a href="ident?i=proto">proto</a>]);
<a name="L1413" href="source/net/ipv4/af_inet.c#L1413">1413</a>         if (<a href="ident?i=WARN_ON">WARN_ON</a>(!<a href="ident?i=ops">ops</a> || !<a href="ident?i=ops">ops</a>-&gt;<a href="ident?i=callbacks">callbacks</a>.gro_complete))
<a name="L1414" href="source/net/ipv4/af_inet.c#L1414">1414</a>                 goto out_unlock;
<a name="L1415" href="source/net/ipv4/af_inet.c#L1415">1415</a> 
<a name="L1416" href="source/net/ipv4/af_inet.c#L1416">1416</a>         <b><i>/* Only need to add sizeof(*iph) to get to the next hdr below</i></b>
<a name="L1417" href="source/net/ipv4/af_inet.c#L1417">1417</a> <b><i>         * because any hdr with option will have been flushed in</i></b>
<a name="L1418" href="source/net/ipv4/af_inet.c#L1418">1418</a> <b><i>         * inet_gro_receive().</i></b>
<a name="L1419" href="source/net/ipv4/af_inet.c#L1419">1419</a> <b><i>         */</i></b>
<a name="L1420" href="source/net/ipv4/af_inet.c#L1420">1420</a>         <a href="ident?i=err">err</a> = <a href="ident?i=ops">ops</a>-&gt;<a href="ident?i=callbacks">callbacks</a>.gro_complete(<a href="ident?i=skb">skb</a>, nhoff + sizeof(*iph));
<a name="L1421" href="source/net/ipv4/af_inet.c#L1421">1421</a> 
<a name="L1422" href="source/net/ipv4/af_inet.c#L1422">1422</a> out_unlock:
<a name="L1423" href="source/net/ipv4/af_inet.c#L1423">1423</a>         <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L1424" href="source/net/ipv4/af_inet.c#L1424">1424</a> 
<a name="L1425" href="source/net/ipv4/af_inet.c#L1425">1425</a>         return <a href="ident?i=err">err</a>;
<a name="L1426" href="source/net/ipv4/af_inet.c#L1426">1426</a> }
<a name="L1427" href="source/net/ipv4/af_inet.c#L1427">1427</a> 
<a name="L1428" href="source/net/ipv4/af_inet.c#L1428">1428</a> int <a href="ident?i=inet_ctl_sock_create">inet_ctl_sock_create</a>(struct <a href="ident?i=sock">sock</a> **sk, unsigned short <a href="ident?i=family">family</a>,
<a name="L1429" href="source/net/ipv4/af_inet.c#L1429">1429</a>                          unsigned short <a href="ident?i=type">type</a>, unsigned char <a href="ident?i=protocol">protocol</a>,
<a name="L1430" href="source/net/ipv4/af_inet.c#L1430">1430</a>                          struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>)
<a name="L1431" href="source/net/ipv4/af_inet.c#L1431">1431</a> {
<a name="L1432" href="source/net/ipv4/af_inet.c#L1432">1432</a>         struct <a href="ident?i=socket">socket</a> *<a href="ident?i=sock">sock</a>;
<a name="L1433" href="source/net/ipv4/af_inet.c#L1433">1433</a>         int <a href="ident?i=rc">rc</a> = <a href="ident?i=sock_create_kern">sock_create_kern</a>(<a href="ident?i=family">family</a>, <a href="ident?i=type">type</a>, <a href="ident?i=protocol">protocol</a>, &amp;<a href="ident?i=sock">sock</a>);
<a name="L1434" href="source/net/ipv4/af_inet.c#L1434">1434</a> 
<a name="L1435" href="source/net/ipv4/af_inet.c#L1435">1435</a>         if (<a href="ident?i=rc">rc</a> == 0) {
<a name="L1436" href="source/net/ipv4/af_inet.c#L1436">1436</a>                 *sk = <a href="ident?i=sock">sock</a>-&gt;sk;
<a name="L1437" href="source/net/ipv4/af_inet.c#L1437">1437</a>                 (*sk)-&gt;sk_allocation = <a href="ident?i=GFP_ATOMIC">GFP_ATOMIC</a>;
<a name="L1438" href="source/net/ipv4/af_inet.c#L1438">1438</a>                 <b><i>/*</i></b>
<a name="L1439" href="source/net/ipv4/af_inet.c#L1439">1439</a> <b><i>                 * Unhash it so that IP input processing does not even see it,</i></b>
<a name="L1440" href="source/net/ipv4/af_inet.c#L1440">1440</a> <b><i>                 * we do not wish this socket to see incoming packets.</i></b>
<a name="L1441" href="source/net/ipv4/af_inet.c#L1441">1441</a> <b><i>                 */</i></b>
<a name="L1442" href="source/net/ipv4/af_inet.c#L1442">1442</a>                 (*sk)-&gt;<a href="ident?i=sk_prot">sk_prot</a>-&gt;unhash(*sk);
<a name="L1443" href="source/net/ipv4/af_inet.c#L1443">1443</a> 
<a name="L1444" href="source/net/ipv4/af_inet.c#L1444">1444</a>                 <a href="ident?i=sk_change_net">sk_change_net</a>(*sk, <a href="ident?i=net">net</a>);
<a name="L1445" href="source/net/ipv4/af_inet.c#L1445">1445</a>         }
<a name="L1446" href="source/net/ipv4/af_inet.c#L1446">1446</a>         return <a href="ident?i=rc">rc</a>;
<a name="L1447" href="source/net/ipv4/af_inet.c#L1447">1447</a> }
<a name="L1448" href="source/net/ipv4/af_inet.c#L1448">1448</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=inet_ctl_sock_create">inet_ctl_sock_create</a>);
<a name="L1449" href="source/net/ipv4/af_inet.c#L1449">1449</a> 
<a name="L1450" href="source/net/ipv4/af_inet.c#L1450">1450</a> unsigned long <a href="ident?i=snmp_fold_field">snmp_fold_field</a>(void <a href="ident?i=__percpu">__percpu</a> *mib, int offt)
<a name="L1451" href="source/net/ipv4/af_inet.c#L1451">1451</a> {
<a name="L1452" href="source/net/ipv4/af_inet.c#L1452">1452</a>         unsigned long <a href="ident?i=res">res</a> = 0;
<a name="L1453" href="source/net/ipv4/af_inet.c#L1453">1453</a>         int <a href="ident?i=i">i</a>;
<a name="L1454" href="source/net/ipv4/af_inet.c#L1454">1454</a> 
<a name="L1455" href="source/net/ipv4/af_inet.c#L1455">1455</a>         <a href="ident?i=for_each_possible_cpu">for_each_possible_cpu</a>(<a href="ident?i=i">i</a>)
<a name="L1456" href="source/net/ipv4/af_inet.c#L1456">1456</a>                 <a href="ident?i=res">res</a> += *(((unsigned long *) <a href="ident?i=per_cpu_ptr">per_cpu_ptr</a>(mib, <a href="ident?i=i">i</a>)) + offt);
<a name="L1457" href="source/net/ipv4/af_inet.c#L1457">1457</a>         return <a href="ident?i=res">res</a>;
<a name="L1458" href="source/net/ipv4/af_inet.c#L1458">1458</a> }
<a name="L1459" href="source/net/ipv4/af_inet.c#L1459">1459</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=snmp_fold_field">snmp_fold_field</a>);
<a name="L1460" href="source/net/ipv4/af_inet.c#L1460">1460</a> 
<a name="L1461" href="source/net/ipv4/af_inet.c#L1461">1461</a> #if <a href="ident?i=BITS_PER_LONG">BITS_PER_LONG</a>==32
<a name="L1462" href="source/net/ipv4/af_inet.c#L1462">1462</a> 
<a name="L1463" href="source/net/ipv4/af_inet.c#L1463">1463</a> <a href="ident?i=u64">u64</a> <a href="ident?i=snmp_fold_field64">snmp_fold_field64</a>(void <a href="ident?i=__percpu">__percpu</a> *mib, int offt, <a href="ident?i=size_t">size_t</a> syncp_offset)
<a name="L1464" href="source/net/ipv4/af_inet.c#L1464">1464</a> {
<a name="L1465" href="source/net/ipv4/af_inet.c#L1465">1465</a>         <a href="ident?i=u64">u64</a> <a href="ident?i=res">res</a> = 0;
<a name="L1466" href="source/net/ipv4/af_inet.c#L1466">1466</a>         int <a href="ident?i=cpu">cpu</a>;
<a name="L1467" href="source/net/ipv4/af_inet.c#L1467">1467</a> 
<a name="L1468" href="source/net/ipv4/af_inet.c#L1468">1468</a>         <a href="ident?i=for_each_possible_cpu">for_each_possible_cpu</a>(<a href="ident?i=cpu">cpu</a>) {
<a name="L1469" href="source/net/ipv4/af_inet.c#L1469">1469</a>                 void *bhptr;
<a name="L1470" href="source/net/ipv4/af_inet.c#L1470">1470</a>                 struct <a href="ident?i=u64_stats_sync">u64_stats_sync</a> *syncp;
<a name="L1471" href="source/net/ipv4/af_inet.c#L1471">1471</a>                 <a href="ident?i=u64">u64</a> <a href="ident?i=v">v</a>;
<a name="L1472" href="source/net/ipv4/af_inet.c#L1472">1472</a>                 unsigned int <a href="ident?i=start">start</a>;
<a name="L1473" href="source/net/ipv4/af_inet.c#L1473">1473</a> 
<a name="L1474" href="source/net/ipv4/af_inet.c#L1474">1474</a>                 bhptr = <a href="ident?i=per_cpu_ptr">per_cpu_ptr</a>(mib, <a href="ident?i=cpu">cpu</a>);
<a name="L1475" href="source/net/ipv4/af_inet.c#L1475">1475</a>                 syncp = (struct <a href="ident?i=u64_stats_sync">u64_stats_sync</a> *)(bhptr + syncp_offset);
<a name="L1476" href="source/net/ipv4/af_inet.c#L1476">1476</a>                 do {
<a name="L1477" href="source/net/ipv4/af_inet.c#L1477">1477</a>                         <a href="ident?i=start">start</a> = <a href="ident?i=u64_stats_fetch_begin_irq">u64_stats_fetch_begin_irq</a>(syncp);
<a name="L1478" href="source/net/ipv4/af_inet.c#L1478">1478</a>                         <a href="ident?i=v">v</a> = *(((<a href="ident?i=u64">u64</a> *) bhptr) + offt);
<a name="L1479" href="source/net/ipv4/af_inet.c#L1479">1479</a>                 } while (<a href="ident?i=u64_stats_fetch_retry_irq">u64_stats_fetch_retry_irq</a>(syncp, <a href="ident?i=start">start</a>));
<a name="L1480" href="source/net/ipv4/af_inet.c#L1480">1480</a> 
<a name="L1481" href="source/net/ipv4/af_inet.c#L1481">1481</a>                 <a href="ident?i=res">res</a> += <a href="ident?i=v">v</a>;
<a name="L1482" href="source/net/ipv4/af_inet.c#L1482">1482</a>         }
<a name="L1483" href="source/net/ipv4/af_inet.c#L1483">1483</a>         return <a href="ident?i=res">res</a>;
<a name="L1484" href="source/net/ipv4/af_inet.c#L1484">1484</a> }
<a name="L1485" href="source/net/ipv4/af_inet.c#L1485">1485</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=snmp_fold_field64">snmp_fold_field64</a>);
<a name="L1486" href="source/net/ipv4/af_inet.c#L1486">1486</a> #endif
<a name="L1487" href="source/net/ipv4/af_inet.c#L1487">1487</a> 
<a name="L1488" href="source/net/ipv4/af_inet.c#L1488">1488</a> #ifdef CONFIG_IP_MULTICAST
<a name="L1489" href="source/net/ipv4/af_inet.c#L1489">1489</a> static const struct <a href="ident?i=net_protocol">net_protocol</a> <a href="ident?i=igmp_protocol">igmp_protocol</a> = {
<a name="L1490" href="source/net/ipv4/af_inet.c#L1490">1490</a>         .<a href="ident?i=handler">handler</a> =      <a href="ident?i=igmp_rcv">igmp_rcv</a>,
<a name="L1491" href="source/net/ipv4/af_inet.c#L1491">1491</a>         .netns_ok =     1,
<a name="L1492" href="source/net/ipv4/af_inet.c#L1492">1492</a> };
<a name="L1493" href="source/net/ipv4/af_inet.c#L1493">1493</a> #endif
<a name="L1494" href="source/net/ipv4/af_inet.c#L1494">1494</a> 
<a name="L1495" href="source/net/ipv4/af_inet.c#L1495">1495</a> static const struct <a href="ident?i=net_protocol">net_protocol</a> <a href="ident?i=tcp_protocol">tcp_protocol</a> = {
<a name="L1496" href="source/net/ipv4/af_inet.c#L1496">1496</a>         .early_demux    =       <a href="ident?i=tcp_v4_early_demux">tcp_v4_early_demux</a>,
<a name="L1497" href="source/net/ipv4/af_inet.c#L1497">1497</a>         .<a href="ident?i=handler">handler</a>        =       <a href="ident?i=tcp_v4_rcv">tcp_v4_rcv</a>,
<a name="L1498" href="source/net/ipv4/af_inet.c#L1498">1498</a>         .<a href="ident?i=err_handler">err_handler</a>    =       <a href="ident?i=tcp_v4_err">tcp_v4_err</a>,
<a name="L1499" href="source/net/ipv4/af_inet.c#L1499">1499</a>         .no_policy      =       1,
<a name="L1500" href="source/net/ipv4/af_inet.c#L1500">1500</a>         .netns_ok       =       1,
<a name="L1501" href="source/net/ipv4/af_inet.c#L1501">1501</a>         .icmp_strict_tag_validation = 1,
<a name="L1502" href="source/net/ipv4/af_inet.c#L1502">1502</a> };
<a name="L1503" href="source/net/ipv4/af_inet.c#L1503">1503</a> 
<a name="L1504" href="source/net/ipv4/af_inet.c#L1504">1504</a> static const struct <a href="ident?i=net_protocol">net_protocol</a> <a href="ident?i=udp_protocol">udp_protocol</a> = {
<a name="L1505" href="source/net/ipv4/af_inet.c#L1505">1505</a>         .early_demux =  <a href="ident?i=udp_v4_early_demux">udp_v4_early_demux</a>,
<a name="L1506" href="source/net/ipv4/af_inet.c#L1506">1506</a>         .<a href="ident?i=handler">handler</a> =      <a href="ident?i=udp_rcv">udp_rcv</a>,
<a name="L1507" href="source/net/ipv4/af_inet.c#L1507">1507</a>         .<a href="ident?i=err_handler">err_handler</a> =  <a href="ident?i=udp_err">udp_err</a>,
<a name="L1508" href="source/net/ipv4/af_inet.c#L1508">1508</a>         .no_policy =    1,
<a name="L1509" href="source/net/ipv4/af_inet.c#L1509">1509</a>         .netns_ok =     1,
<a name="L1510" href="source/net/ipv4/af_inet.c#L1510">1510</a> };
<a name="L1511" href="source/net/ipv4/af_inet.c#L1511">1511</a> 
<a name="L1512" href="source/net/ipv4/af_inet.c#L1512">1512</a> static const struct <a href="ident?i=net_protocol">net_protocol</a> <a href="ident?i=icmp_protocol">icmp_protocol</a> = {
<a name="L1513" href="source/net/ipv4/af_inet.c#L1513">1513</a>         .<a href="ident?i=handler">handler</a> =      <a href="ident?i=icmp_rcv">icmp_rcv</a>,
<a name="L1514" href="source/net/ipv4/af_inet.c#L1514">1514</a>         .<a href="ident?i=err_handler">err_handler</a> =  <a href="ident?i=icmp_err">icmp_err</a>,
<a name="L1515" href="source/net/ipv4/af_inet.c#L1515">1515</a>         .no_policy =    1,
<a name="L1516" href="source/net/ipv4/af_inet.c#L1516">1516</a>         .netns_ok =     1,
<a name="L1517" href="source/net/ipv4/af_inet.c#L1517">1517</a> };
<a name="L1518" href="source/net/ipv4/af_inet.c#L1518">1518</a> 
<a name="L1519" href="source/net/ipv4/af_inet.c#L1519">1519</a> static <a href="ident?i=__net_init">__net_init</a> int <a href="ident?i=ipv4_mib_init_net">ipv4_mib_init_net</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>)
<a name="L1520" href="source/net/ipv4/af_inet.c#L1520">1520</a> {
<a name="L1521" href="source/net/ipv4/af_inet.c#L1521">1521</a>         int <a href="ident?i=i">i</a>;
<a name="L1522" href="source/net/ipv4/af_inet.c#L1522">1522</a> 
<a name="L1523" href="source/net/ipv4/af_inet.c#L1523">1523</a>         <a href="ident?i=net">net</a>-&gt;mib.tcp_statistics = <a href="ident?i=alloc_percpu">alloc_percpu</a>(struct <a href="ident?i=tcp_mib">tcp_mib</a>);
<a name="L1524" href="source/net/ipv4/af_inet.c#L1524">1524</a>         if (!<a href="ident?i=net">net</a>-&gt;mib.tcp_statistics)
<a name="L1525" href="source/net/ipv4/af_inet.c#L1525">1525</a>                 goto err_tcp_mib;
<a name="L1526" href="source/net/ipv4/af_inet.c#L1526">1526</a>         <a href="ident?i=net">net</a>-&gt;mib.ip_statistics = <a href="ident?i=alloc_percpu">alloc_percpu</a>(struct <a href="ident?i=ipstats_mib">ipstats_mib</a>);
<a name="L1527" href="source/net/ipv4/af_inet.c#L1527">1527</a>         if (!<a href="ident?i=net">net</a>-&gt;mib.ip_statistics)
<a name="L1528" href="source/net/ipv4/af_inet.c#L1528">1528</a>                 goto err_ip_mib;
<a name="L1529" href="source/net/ipv4/af_inet.c#L1529">1529</a> 
<a name="L1530" href="source/net/ipv4/af_inet.c#L1530">1530</a>         <a href="ident?i=for_each_possible_cpu">for_each_possible_cpu</a>(<a href="ident?i=i">i</a>) {
<a name="L1531" href="source/net/ipv4/af_inet.c#L1531">1531</a>                 struct <a href="ident?i=ipstats_mib">ipstats_mib</a> *af_inet_stats;
<a name="L1532" href="source/net/ipv4/af_inet.c#L1532">1532</a>                 af_inet_stats = <a href="ident?i=per_cpu_ptr">per_cpu_ptr</a>(<a href="ident?i=net">net</a>-&gt;mib.ip_statistics, <a href="ident?i=i">i</a>);
<a name="L1533" href="source/net/ipv4/af_inet.c#L1533">1533</a>                 <a href="ident?i=u64_stats_init">u64_stats_init</a>(&amp;af_inet_stats-&gt;syncp);
<a name="L1534" href="source/net/ipv4/af_inet.c#L1534">1534</a>         }
<a name="L1535" href="source/net/ipv4/af_inet.c#L1535">1535</a> 
<a name="L1536" href="source/net/ipv4/af_inet.c#L1536">1536</a>         <a href="ident?i=net">net</a>-&gt;mib.net_statistics = <a href="ident?i=alloc_percpu">alloc_percpu</a>(struct <a href="ident?i=linux_mib">linux_mib</a>);
<a name="L1537" href="source/net/ipv4/af_inet.c#L1537">1537</a>         if (!<a href="ident?i=net">net</a>-&gt;mib.net_statistics)
<a name="L1538" href="source/net/ipv4/af_inet.c#L1538">1538</a>                 goto err_net_mib;
<a name="L1539" href="source/net/ipv4/af_inet.c#L1539">1539</a>         <a href="ident?i=net">net</a>-&gt;mib.udp_statistics = <a href="ident?i=alloc_percpu">alloc_percpu</a>(struct <a href="ident?i=udp_mib">udp_mib</a>);
<a name="L1540" href="source/net/ipv4/af_inet.c#L1540">1540</a>         if (!<a href="ident?i=net">net</a>-&gt;mib.udp_statistics)
<a name="L1541" href="source/net/ipv4/af_inet.c#L1541">1541</a>                 goto err_udp_mib;
<a name="L1542" href="source/net/ipv4/af_inet.c#L1542">1542</a>         <a href="ident?i=net">net</a>-&gt;mib.udplite_statistics = <a href="ident?i=alloc_percpu">alloc_percpu</a>(struct <a href="ident?i=udp_mib">udp_mib</a>);
<a name="L1543" href="source/net/ipv4/af_inet.c#L1543">1543</a>         if (!<a href="ident?i=net">net</a>-&gt;mib.udplite_statistics)
<a name="L1544" href="source/net/ipv4/af_inet.c#L1544">1544</a>                 goto err_udplite_mib;
<a name="L1545" href="source/net/ipv4/af_inet.c#L1545">1545</a>         <a href="ident?i=net">net</a>-&gt;mib.icmp_statistics = <a href="ident?i=alloc_percpu">alloc_percpu</a>(struct <a href="ident?i=icmp_mib">icmp_mib</a>);
<a name="L1546" href="source/net/ipv4/af_inet.c#L1546">1546</a>         if (!<a href="ident?i=net">net</a>-&gt;mib.icmp_statistics)
<a name="L1547" href="source/net/ipv4/af_inet.c#L1547">1547</a>                 goto err_icmp_mib;
<a name="L1548" href="source/net/ipv4/af_inet.c#L1548">1548</a>         <a href="ident?i=net">net</a>-&gt;mib.icmpmsg_statistics = <a href="ident?i=kzalloc">kzalloc</a>(sizeof(struct <a href="ident?i=icmpmsg_mib">icmpmsg_mib</a>),
<a name="L1549" href="source/net/ipv4/af_inet.c#L1549">1549</a>                                               <a href="ident?i=GFP_KERNEL">GFP_KERNEL</a>);
<a name="L1550" href="source/net/ipv4/af_inet.c#L1550">1550</a>         if (!<a href="ident?i=net">net</a>-&gt;mib.icmpmsg_statistics)
<a name="L1551" href="source/net/ipv4/af_inet.c#L1551">1551</a>                 goto err_icmpmsg_mib;
<a name="L1552" href="source/net/ipv4/af_inet.c#L1552">1552</a> 
<a name="L1553" href="source/net/ipv4/af_inet.c#L1553">1553</a>         <a href="ident?i=tcp_mib_init">tcp_mib_init</a>(<a href="ident?i=net">net</a>);
<a name="L1554" href="source/net/ipv4/af_inet.c#L1554">1554</a>         return 0;
<a name="L1555" href="source/net/ipv4/af_inet.c#L1555">1555</a> 
<a name="L1556" href="source/net/ipv4/af_inet.c#L1556">1556</a> err_icmpmsg_mib:
<a name="L1557" href="source/net/ipv4/af_inet.c#L1557">1557</a>         <a href="ident?i=free_percpu">free_percpu</a>(<a href="ident?i=net">net</a>-&gt;mib.icmp_statistics);
<a name="L1558" href="source/net/ipv4/af_inet.c#L1558">1558</a> err_icmp_mib:
<a name="L1559" href="source/net/ipv4/af_inet.c#L1559">1559</a>         <a href="ident?i=free_percpu">free_percpu</a>(<a href="ident?i=net">net</a>-&gt;mib.udplite_statistics);
<a name="L1560" href="source/net/ipv4/af_inet.c#L1560">1560</a> err_udplite_mib:
<a name="L1561" href="source/net/ipv4/af_inet.c#L1561">1561</a>         <a href="ident?i=free_percpu">free_percpu</a>(<a href="ident?i=net">net</a>-&gt;mib.udp_statistics);
<a name="L1562" href="source/net/ipv4/af_inet.c#L1562">1562</a> err_udp_mib:
<a name="L1563" href="source/net/ipv4/af_inet.c#L1563">1563</a>         <a href="ident?i=free_percpu">free_percpu</a>(<a href="ident?i=net">net</a>-&gt;mib.net_statistics);
<a name="L1564" href="source/net/ipv4/af_inet.c#L1564">1564</a> err_net_mib:
<a name="L1565" href="source/net/ipv4/af_inet.c#L1565">1565</a>         <a href="ident?i=free_percpu">free_percpu</a>(<a href="ident?i=net">net</a>-&gt;mib.ip_statistics);
<a name="L1566" href="source/net/ipv4/af_inet.c#L1566">1566</a> err_ip_mib:
<a name="L1567" href="source/net/ipv4/af_inet.c#L1567">1567</a>         <a href="ident?i=free_percpu">free_percpu</a>(<a href="ident?i=net">net</a>-&gt;mib.tcp_statistics);
<a name="L1568" href="source/net/ipv4/af_inet.c#L1568">1568</a> err_tcp_mib:
<a name="L1569" href="source/net/ipv4/af_inet.c#L1569">1569</a>         return -<a href="ident?i=ENOMEM">ENOMEM</a>;
<a name="L1570" href="source/net/ipv4/af_inet.c#L1570">1570</a> }
<a name="L1571" href="source/net/ipv4/af_inet.c#L1571">1571</a> 
<a name="L1572" href="source/net/ipv4/af_inet.c#L1572">1572</a> static <a href="ident?i=__net_exit">__net_exit</a> void <a href="ident?i=ipv4_mib_exit_net">ipv4_mib_exit_net</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>)
<a name="L1573" href="source/net/ipv4/af_inet.c#L1573">1573</a> {
<a name="L1574" href="source/net/ipv4/af_inet.c#L1574">1574</a>         <a href="ident?i=kfree">kfree</a>(<a href="ident?i=net">net</a>-&gt;mib.icmpmsg_statistics);
<a name="L1575" href="source/net/ipv4/af_inet.c#L1575">1575</a>         <a href="ident?i=free_percpu">free_percpu</a>(<a href="ident?i=net">net</a>-&gt;mib.icmp_statistics);
<a name="L1576" href="source/net/ipv4/af_inet.c#L1576">1576</a>         <a href="ident?i=free_percpu">free_percpu</a>(<a href="ident?i=net">net</a>-&gt;mib.udplite_statistics);
<a name="L1577" href="source/net/ipv4/af_inet.c#L1577">1577</a>         <a href="ident?i=free_percpu">free_percpu</a>(<a href="ident?i=net">net</a>-&gt;mib.udp_statistics);
<a name="L1578" href="source/net/ipv4/af_inet.c#L1578">1578</a>         <a href="ident?i=free_percpu">free_percpu</a>(<a href="ident?i=net">net</a>-&gt;mib.net_statistics);
<a name="L1579" href="source/net/ipv4/af_inet.c#L1579">1579</a>         <a href="ident?i=free_percpu">free_percpu</a>(<a href="ident?i=net">net</a>-&gt;mib.ip_statistics);
<a name="L1580" href="source/net/ipv4/af_inet.c#L1580">1580</a>         <a href="ident?i=free_percpu">free_percpu</a>(<a href="ident?i=net">net</a>-&gt;mib.tcp_statistics);
<a name="L1581" href="source/net/ipv4/af_inet.c#L1581">1581</a> }
<a name="L1582" href="source/net/ipv4/af_inet.c#L1582">1582</a> 
<a name="L1583" href="source/net/ipv4/af_inet.c#L1583">1583</a> static <a href="ident?i=__net_initdata">__net_initdata</a> struct <a href="ident?i=pernet_operations">pernet_operations</a> <a href="ident?i=ipv4_mib_ops">ipv4_mib_ops</a> = {
<a name="L1584" href="source/net/ipv4/af_inet.c#L1584">1584</a>         .<a href="ident?i=init">init</a> = <a href="ident?i=ipv4_mib_init_net">ipv4_mib_init_net</a>,
<a name="L1585" href="source/net/ipv4/af_inet.c#L1585">1585</a>         .<a href="ident?i=exit">exit</a> = <a href="ident?i=ipv4_mib_exit_net">ipv4_mib_exit_net</a>,
<a name="L1586" href="source/net/ipv4/af_inet.c#L1586">1586</a> };
<a name="L1587" href="source/net/ipv4/af_inet.c#L1587">1587</a> 
<a name="L1588" href="source/net/ipv4/af_inet.c#L1588">1588</a> static int <a href="ident?i=__init">__init</a> <a href="ident?i=init_ipv4_mibs">init_ipv4_mibs</a>(void)
<a name="L1589" href="source/net/ipv4/af_inet.c#L1589">1589</a> {
<a name="L1590" href="source/net/ipv4/af_inet.c#L1590">1590</a>         return <a href="ident?i=register_pernet_subsys">register_pernet_subsys</a>(&amp;<a href="ident?i=ipv4_mib_ops">ipv4_mib_ops</a>);
<a name="L1591" href="source/net/ipv4/af_inet.c#L1591">1591</a> }
<a name="L1592" href="source/net/ipv4/af_inet.c#L1592">1592</a> 
<a name="L1593" href="source/net/ipv4/af_inet.c#L1593">1593</a> static <a href="ident?i=__net_init">__net_init</a> int <a href="ident?i=inet_init_net">inet_init_net</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>)
<a name="L1594" href="source/net/ipv4/af_inet.c#L1594">1594</a> {
<a name="L1595" href="source/net/ipv4/af_inet.c#L1595">1595</a>         <b><i>/*</i></b>
<a name="L1596" href="source/net/ipv4/af_inet.c#L1596">1596</a> <b><i>         * Set defaults for local port range</i></b>
<a name="L1597" href="source/net/ipv4/af_inet.c#L1597">1597</a> <b><i>         */</i></b>
<a name="L1598" href="source/net/ipv4/af_inet.c#L1598">1598</a>         <a href="ident?i=seqlock_init">seqlock_init</a>(&amp;<a href="ident?i=net">net</a>-&gt;ipv4.ip_local_ports.<a href="ident?i=lock">lock</a>);
<a name="L1599" href="source/net/ipv4/af_inet.c#L1599">1599</a>         <a href="ident?i=net">net</a>-&gt;ipv4.ip_local_ports.<a href="ident?i=range">range</a>[0] =  32768;
<a name="L1600" href="source/net/ipv4/af_inet.c#L1600">1600</a>         <a href="ident?i=net">net</a>-&gt;ipv4.ip_local_ports.<a href="ident?i=range">range</a>[1] =  61000;
<a name="L1601" href="source/net/ipv4/af_inet.c#L1601">1601</a> 
<a name="L1602" href="source/net/ipv4/af_inet.c#L1602">1602</a>         <a href="ident?i=seqlock_init">seqlock_init</a>(&amp;<a href="ident?i=net">net</a>-&gt;ipv4.<a href="ident?i=ping_group_range">ping_group_range</a>.<a href="ident?i=lock">lock</a>);
<a name="L1603" href="source/net/ipv4/af_inet.c#L1603">1603</a>         <b><i>/*</i></b>
<a name="L1604" href="source/net/ipv4/af_inet.c#L1604">1604</a> <b><i>         * Sane defaults - nobody may create ping sockets.</i></b>
<a name="L1605" href="source/net/ipv4/af_inet.c#L1605">1605</a> <b><i>         * Boot scripts should set this to distro-specific group.</i></b>
<a name="L1606" href="source/net/ipv4/af_inet.c#L1606">1606</a> <b><i>         */</i></b>
<a name="L1607" href="source/net/ipv4/af_inet.c#L1607">1607</a>         <a href="ident?i=net">net</a>-&gt;ipv4.<a href="ident?i=ping_group_range">ping_group_range</a>.<a href="ident?i=range">range</a>[0] = <a href="ident?i=make_kgid">make_kgid</a>(&amp;<a href="ident?i=init_user_ns">init_user_ns</a>, 1);
<a name="L1608" href="source/net/ipv4/af_inet.c#L1608">1608</a>         <a href="ident?i=net">net</a>-&gt;ipv4.<a href="ident?i=ping_group_range">ping_group_range</a>.<a href="ident?i=range">range</a>[1] = <a href="ident?i=make_kgid">make_kgid</a>(&amp;<a href="ident?i=init_user_ns">init_user_ns</a>, 0);
<a name="L1609" href="source/net/ipv4/af_inet.c#L1609">1609</a>         return 0;
<a name="L1610" href="source/net/ipv4/af_inet.c#L1610">1610</a> }
<a name="L1611" href="source/net/ipv4/af_inet.c#L1611">1611</a> 
<a name="L1612" href="source/net/ipv4/af_inet.c#L1612">1612</a> static <a href="ident?i=__net_exit">__net_exit</a> void <a href="ident?i=inet_exit_net">inet_exit_net</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>)
<a name="L1613" href="source/net/ipv4/af_inet.c#L1613">1613</a> {
<a name="L1614" href="source/net/ipv4/af_inet.c#L1614">1614</a> }
<a name="L1615" href="source/net/ipv4/af_inet.c#L1615">1615</a> 
<a name="L1616" href="source/net/ipv4/af_inet.c#L1616">1616</a> static <a href="ident?i=__net_initdata">__net_initdata</a> struct <a href="ident?i=pernet_operations">pernet_operations</a> <a href="ident?i=af_inet_ops">af_inet_ops</a> = {
<a name="L1617" href="source/net/ipv4/af_inet.c#L1617">1617</a>         .<a href="ident?i=init">init</a> = <a href="ident?i=inet_init_net">inet_init_net</a>,
<a name="L1618" href="source/net/ipv4/af_inet.c#L1618">1618</a>         .<a href="ident?i=exit">exit</a> = <a href="ident?i=inet_exit_net">inet_exit_net</a>,
<a name="L1619" href="source/net/ipv4/af_inet.c#L1619">1619</a> };
<a name="L1620" href="source/net/ipv4/af_inet.c#L1620">1620</a> 
<a name="L1621" href="source/net/ipv4/af_inet.c#L1621">1621</a> static int <a href="ident?i=__init">__init</a> <a href="ident?i=init_inet_pernet_ops">init_inet_pernet_ops</a>(void)
<a name="L1622" href="source/net/ipv4/af_inet.c#L1622">1622</a> {
<a name="L1623" href="source/net/ipv4/af_inet.c#L1623">1623</a>         return <a href="ident?i=register_pernet_subsys">register_pernet_subsys</a>(&amp;<a href="ident?i=af_inet_ops">af_inet_ops</a>);
<a name="L1624" href="source/net/ipv4/af_inet.c#L1624">1624</a> }
<a name="L1625" href="source/net/ipv4/af_inet.c#L1625">1625</a> 
<a name="L1626" href="source/net/ipv4/af_inet.c#L1626">1626</a> static int <a href="ident?i=ipv4_proc_init">ipv4_proc_init</a>(void);
<a name="L1627" href="source/net/ipv4/af_inet.c#L1627">1627</a> 
<a name="L1628" href="source/net/ipv4/af_inet.c#L1628">1628</a> <b><i>/*</i></b>
<a name="L1629" href="source/net/ipv4/af_inet.c#L1629">1629</a> <b><i> *      IP protocol layer initialiser</i></b>
<a name="L1630" href="source/net/ipv4/af_inet.c#L1630">1630</a> <b><i> */</i></b>
<a name="L1631" href="source/net/ipv4/af_inet.c#L1631">1631</a> 
<a name="L1632" href="source/net/ipv4/af_inet.c#L1632">1632</a> static struct <a href="ident?i=packet_offload">packet_offload</a> ip_packet_offload <a href="ident?i=__read_mostly">__read_mostly</a> = {
<a name="L1633" href="source/net/ipv4/af_inet.c#L1633">1633</a>         .<a href="ident?i=type">type</a> = <a href="ident?i=cpu_to_be16">cpu_to_be16</a>(<a href="ident?i=ETH_P_IP">ETH_P_IP</a>),
<a name="L1634" href="source/net/ipv4/af_inet.c#L1634">1634</a>         .<a href="ident?i=callbacks">callbacks</a> = {
<a name="L1635" href="source/net/ipv4/af_inet.c#L1635">1635</a>                 .gso_segment = <a href="ident?i=inet_gso_segment">inet_gso_segment</a>,
<a name="L1636" href="source/net/ipv4/af_inet.c#L1636">1636</a>                 .gro_receive = <a href="ident?i=inet_gro_receive">inet_gro_receive</a>,
<a name="L1637" href="source/net/ipv4/af_inet.c#L1637">1637</a>                 .gro_complete = <a href="ident?i=inet_gro_complete">inet_gro_complete</a>,
<a name="L1638" href="source/net/ipv4/af_inet.c#L1638">1638</a>         },
<a name="L1639" href="source/net/ipv4/af_inet.c#L1639">1639</a> };
<a name="L1640" href="source/net/ipv4/af_inet.c#L1640">1640</a> 
<a name="L1641" href="source/net/ipv4/af_inet.c#L1641">1641</a> static const struct <a href="ident?i=net_offload">net_offload</a> <a href="ident?i=ipip_offload">ipip_offload</a> = {
<a name="L1642" href="source/net/ipv4/af_inet.c#L1642">1642</a>         .<a href="ident?i=callbacks">callbacks</a> = {
<a name="L1643" href="source/net/ipv4/af_inet.c#L1643">1643</a>                 .gso_segment    = <a href="ident?i=inet_gso_segment">inet_gso_segment</a>,
<a name="L1644" href="source/net/ipv4/af_inet.c#L1644">1644</a>                 .gro_receive    = <a href="ident?i=inet_gro_receive">inet_gro_receive</a>,
<a name="L1645" href="source/net/ipv4/af_inet.c#L1645">1645</a>                 .gro_complete   = <a href="ident?i=inet_gro_complete">inet_gro_complete</a>,
<a name="L1646" href="source/net/ipv4/af_inet.c#L1646">1646</a>         },
<a name="L1647" href="source/net/ipv4/af_inet.c#L1647">1647</a> };
<a name="L1648" href="source/net/ipv4/af_inet.c#L1648">1648</a> 
<a name="L1649" href="source/net/ipv4/af_inet.c#L1649">1649</a> static int <a href="ident?i=__init">__init</a> <a href="ident?i=ipv4_offload_init">ipv4_offload_init</a>(void)
<a name="L1650" href="source/net/ipv4/af_inet.c#L1650">1650</a> {
<a name="L1651" href="source/net/ipv4/af_inet.c#L1651">1651</a>         <b><i>/*</i></b>
<a name="L1652" href="source/net/ipv4/af_inet.c#L1652">1652</a> <b><i>         * Add offloads</i></b>
<a name="L1653" href="source/net/ipv4/af_inet.c#L1653">1653</a> <b><i>         */</i></b>
<a name="L1654" href="source/net/ipv4/af_inet.c#L1654">1654</a>         if (<a href="ident?i=udpv4_offload_init">udpv4_offload_init</a>() &lt; 0)
<a name="L1655" href="source/net/ipv4/af_inet.c#L1655">1655</a>                 <a href="ident?i=pr_crit">pr_crit</a>(<i>"%s: Cannot add UDP protocol offload\n"</i>, <a href="ident?i=__func__">__func__</a>);
<a name="L1656" href="source/net/ipv4/af_inet.c#L1656">1656</a>         if (<a href="ident?i=tcpv4_offload_init">tcpv4_offload_init</a>() &lt; 0)
<a name="L1657" href="source/net/ipv4/af_inet.c#L1657">1657</a>                 <a href="ident?i=pr_crit">pr_crit</a>(<i>"%s: Cannot add TCP protocol offload\n"</i>, <a href="ident?i=__func__">__func__</a>);
<a name="L1658" href="source/net/ipv4/af_inet.c#L1658">1658</a> 
<a name="L1659" href="source/net/ipv4/af_inet.c#L1659">1659</a>         <a href="ident?i=dev_add_offload">dev_add_offload</a>(&amp;ip_packet_offload);
<a name="L1660" href="source/net/ipv4/af_inet.c#L1660">1660</a>         <a href="ident?i=inet_add_offload">inet_add_offload</a>(&amp;<a href="ident?i=ipip_offload">ipip_offload</a>, <a href="ident?i=IPPROTO_IPIP">IPPROTO_IPIP</a>);
<a name="L1661" href="source/net/ipv4/af_inet.c#L1661">1661</a>         return 0;
<a name="L1662" href="source/net/ipv4/af_inet.c#L1662">1662</a> }
<a name="L1663" href="source/net/ipv4/af_inet.c#L1663">1663</a> 
<a name="L1664" href="source/net/ipv4/af_inet.c#L1664">1664</a> <a href="ident?i=fs_initcall">fs_initcall</a>(<a href="ident?i=ipv4_offload_init">ipv4_offload_init</a>);
<a name="L1665" href="source/net/ipv4/af_inet.c#L1665">1665</a> 
<a name="L1666" href="source/net/ipv4/af_inet.c#L1666">1666</a> static struct <a href="ident?i=packet_type">packet_type</a> ip_packet_type <a href="ident?i=__read_mostly">__read_mostly</a> = {
<a name="L1667" href="source/net/ipv4/af_inet.c#L1667">1667</a>         .<a href="ident?i=type">type</a> = <a href="ident?i=cpu_to_be16">cpu_to_be16</a>(<a href="ident?i=ETH_P_IP">ETH_P_IP</a>),
<a name="L1668" href="source/net/ipv4/af_inet.c#L1668">1668</a>         .<a href="ident?i=func">func</a> = <a href="ident?i=ip_rcv">ip_rcv</a>,
<a name="L1669" href="source/net/ipv4/af_inet.c#L1669">1669</a> };
<a name="L1670" href="source/net/ipv4/af_inet.c#L1670">1670</a> 
<a name="L1671" href="source/net/ipv4/af_inet.c#L1671">1671</a> static int <a href="ident?i=__init">__init</a> <a href="ident?i=inet_init">inet_init</a>(void)
<a name="L1672" href="source/net/ipv4/af_inet.c#L1672">1672</a> {
<a name="L1673" href="source/net/ipv4/af_inet.c#L1673">1673</a>         struct <a href="ident?i=inet_protosw">inet_protosw</a> *q;
<a name="L1674" href="source/net/ipv4/af_inet.c#L1674">1674</a>         struct <a href="ident?i=list_head">list_head</a> *<a href="ident?i=r">r</a>;
<a name="L1675" href="source/net/ipv4/af_inet.c#L1675">1675</a>         int <a href="ident?i=rc">rc</a> = -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L1676" href="source/net/ipv4/af_inet.c#L1676">1676</a> 
<a name="L1677" href="source/net/ipv4/af_inet.c#L1677">1677</a>         <a href="ident?i=sock_skb_cb_check_size">sock_skb_cb_check_size</a>(sizeof(struct <a href="ident?i=inet_skb_parm">inet_skb_parm</a>));
<a name="L1678" href="source/net/ipv4/af_inet.c#L1678">1678</a> 
<a name="L1679" href="source/net/ipv4/af_inet.c#L1679">1679</a>         <a href="ident?i=rc">rc</a> = <a href="ident?i=proto_register">proto_register</a>(&amp;<a href="ident?i=tcp_prot">tcp_prot</a>, 1);
<a name="L1680" href="source/net/ipv4/af_inet.c#L1680">1680</a>         if (<a href="ident?i=rc">rc</a>)
<a name="L1681" href="source/net/ipv4/af_inet.c#L1681">1681</a>                 goto <a href="ident?i=out">out</a>;
<a name="L1682" href="source/net/ipv4/af_inet.c#L1682">1682</a> 
<a name="L1683" href="source/net/ipv4/af_inet.c#L1683">1683</a>         <a href="ident?i=rc">rc</a> = <a href="ident?i=proto_register">proto_register</a>(&amp;<a href="ident?i=udp_prot">udp_prot</a>, 1);
<a name="L1684" href="source/net/ipv4/af_inet.c#L1684">1684</a>         if (<a href="ident?i=rc">rc</a>)
<a name="L1685" href="source/net/ipv4/af_inet.c#L1685">1685</a>                 goto out_unregister_tcp_proto;
<a name="L1686" href="source/net/ipv4/af_inet.c#L1686">1686</a> 
<a name="L1687" href="source/net/ipv4/af_inet.c#L1687">1687</a>         <a href="ident?i=rc">rc</a> = <a href="ident?i=proto_register">proto_register</a>(&amp;<a href="ident?i=raw_prot">raw_prot</a>, 1);
<a name="L1688" href="source/net/ipv4/af_inet.c#L1688">1688</a>         if (<a href="ident?i=rc">rc</a>)
<a name="L1689" href="source/net/ipv4/af_inet.c#L1689">1689</a>                 goto out_unregister_udp_proto;
<a name="L1690" href="source/net/ipv4/af_inet.c#L1690">1690</a> 
<a name="L1691" href="source/net/ipv4/af_inet.c#L1691">1691</a>         <a href="ident?i=rc">rc</a> = <a href="ident?i=proto_register">proto_register</a>(&amp;<a href="ident?i=ping_prot">ping_prot</a>, 1);
<a name="L1692" href="source/net/ipv4/af_inet.c#L1692">1692</a>         if (<a href="ident?i=rc">rc</a>)
<a name="L1693" href="source/net/ipv4/af_inet.c#L1693">1693</a>                 goto out_unregister_raw_proto;
<a name="L1694" href="source/net/ipv4/af_inet.c#L1694">1694</a> 
<a name="L1695" href="source/net/ipv4/af_inet.c#L1695">1695</a>         <b><i>/*</i></b>
<a name="L1696" href="source/net/ipv4/af_inet.c#L1696">1696</a> <b><i>         *      Tell SOCKET that we are alive...</i></b>
<a name="L1697" href="source/net/ipv4/af_inet.c#L1697">1697</a> <b><i>         */</i></b>
<a name="L1698" href="source/net/ipv4/af_inet.c#L1698">1698</a> 
<a name="L1699" href="source/net/ipv4/af_inet.c#L1699">1699</a>         (void)<a href="ident?i=sock_register">sock_register</a>(&amp;<a href="ident?i=inet_family_ops">inet_family_ops</a>);
<a name="L1700" href="source/net/ipv4/af_inet.c#L1700">1700</a> 
<a name="L1701" href="source/net/ipv4/af_inet.c#L1701">1701</a> #ifdef CONFIG_SYSCTL
<a name="L1702" href="source/net/ipv4/af_inet.c#L1702">1702</a>         <a href="ident?i=ip_static_sysctl_init">ip_static_sysctl_init</a>();
<a name="L1703" href="source/net/ipv4/af_inet.c#L1703">1703</a> #endif
<a name="L1704" href="source/net/ipv4/af_inet.c#L1704">1704</a> 
<a name="L1705" href="source/net/ipv4/af_inet.c#L1705">1705</a>         <b><i>/*</i></b>
<a name="L1706" href="source/net/ipv4/af_inet.c#L1706">1706</a> <b><i>         *      Add all the base protocols.</i></b>
<a name="L1707" href="source/net/ipv4/af_inet.c#L1707">1707</a> <b><i>         */</i></b>
<a name="L1708" href="source/net/ipv4/af_inet.c#L1708">1708</a> 
<a name="L1709" href="source/net/ipv4/af_inet.c#L1709">1709</a>         if (<a href="ident?i=inet_add_protocol">inet_add_protocol</a>(&amp;<a href="ident?i=icmp_protocol">icmp_protocol</a>, <a href="ident?i=IPPROTO_ICMP">IPPROTO_ICMP</a>) &lt; 0)
<a name="L1710" href="source/net/ipv4/af_inet.c#L1710">1710</a>                 <a href="ident?i=pr_crit">pr_crit</a>(<i>"%s: Cannot add ICMP protocol\n"</i>, <a href="ident?i=__func__">__func__</a>);
<a name="L1711" href="source/net/ipv4/af_inet.c#L1711">1711</a>         if (<a href="ident?i=inet_add_protocol">inet_add_protocol</a>(&amp;<a href="ident?i=udp_protocol">udp_protocol</a>, <a href="ident?i=IPPROTO_UDP">IPPROTO_UDP</a>) &lt; 0)
<a name="L1712" href="source/net/ipv4/af_inet.c#L1712">1712</a>                 <a href="ident?i=pr_crit">pr_crit</a>(<i>"%s: Cannot add UDP protocol\n"</i>, <a href="ident?i=__func__">__func__</a>);
<a name="L1713" href="source/net/ipv4/af_inet.c#L1713">1713</a>         if (<a href="ident?i=inet_add_protocol">inet_add_protocol</a>(&amp;<a href="ident?i=tcp_protocol">tcp_protocol</a>, <a href="ident?i=IPPROTO_TCP">IPPROTO_TCP</a>) &lt; 0)
<a name="L1714" href="source/net/ipv4/af_inet.c#L1714">1714</a>                 <a href="ident?i=pr_crit">pr_crit</a>(<i>"%s: Cannot add TCP protocol\n"</i>, <a href="ident?i=__func__">__func__</a>);
<a name="L1715" href="source/net/ipv4/af_inet.c#L1715">1715</a> #ifdef CONFIG_IP_MULTICAST
<a name="L1716" href="source/net/ipv4/af_inet.c#L1716">1716</a>         if (<a href="ident?i=inet_add_protocol">inet_add_protocol</a>(&amp;<a href="ident?i=igmp_protocol">igmp_protocol</a>, <a href="ident?i=IPPROTO_IGMP">IPPROTO_IGMP</a>) &lt; 0)
<a name="L1717" href="source/net/ipv4/af_inet.c#L1717">1717</a>                 <a href="ident?i=pr_crit">pr_crit</a>(<i>"%s: Cannot add IGMP protocol\n"</i>, <a href="ident?i=__func__">__func__</a>);
<a name="L1718" href="source/net/ipv4/af_inet.c#L1718">1718</a> #endif
<a name="L1719" href="source/net/ipv4/af_inet.c#L1719">1719</a> 
<a name="L1720" href="source/net/ipv4/af_inet.c#L1720">1720</a>         <b><i>/* Register the socket-side information for inet_create. */</i></b>
<a name="L1721" href="source/net/ipv4/af_inet.c#L1721">1721</a>         for (<a href="ident?i=r">r</a> = &amp;<a href="ident?i=inetsw">inetsw</a>[0]; <a href="ident?i=r">r</a> &lt; &amp;<a href="ident?i=inetsw">inetsw</a>[<a href="ident?i=SOCK_MAX">SOCK_MAX</a>]; ++<a href="ident?i=r">r</a>)
<a name="L1722" href="source/net/ipv4/af_inet.c#L1722">1722</a>                 <a href="ident?i=INIT_LIST_HEAD">INIT_LIST_HEAD</a>(<a href="ident?i=r">r</a>);
<a name="L1723" href="source/net/ipv4/af_inet.c#L1723">1723</a> 
<a name="L1724" href="source/net/ipv4/af_inet.c#L1724">1724</a>         for (q = <a href="ident?i=inetsw_array">inetsw_array</a>; q &lt; &amp;<a href="ident?i=inetsw_array">inetsw_array</a>[<a href="ident?i=INETSW_ARRAY_LEN">INETSW_ARRAY_LEN</a>]; ++q)
<a name="L1725" href="source/net/ipv4/af_inet.c#L1725">1725</a>                 <a href="ident?i=inet_register_protosw">inet_register_protosw</a>(q);
<a name="L1726" href="source/net/ipv4/af_inet.c#L1726">1726</a> 
<a name="L1727" href="source/net/ipv4/af_inet.c#L1727">1727</a>         <b><i>/*</i></b>
<a name="L1728" href="source/net/ipv4/af_inet.c#L1728">1728</a> <b><i>         *      Set the ARP module up</i></b>
<a name="L1729" href="source/net/ipv4/af_inet.c#L1729">1729</a> <b><i>         */</i></b>
<a name="L1730" href="source/net/ipv4/af_inet.c#L1730">1730</a> 
<a name="L1731" href="source/net/ipv4/af_inet.c#L1731">1731</a>         <a href="ident?i=arp_init">arp_init</a>();
<a name="L1732" href="source/net/ipv4/af_inet.c#L1732">1732</a> 
<a name="L1733" href="source/net/ipv4/af_inet.c#L1733">1733</a>         <b><i>/*</i></b>
<a name="L1734" href="source/net/ipv4/af_inet.c#L1734">1734</a> <b><i>         *      Set the IP module up</i></b>
<a name="L1735" href="source/net/ipv4/af_inet.c#L1735">1735</a> <b><i>         */</i></b>
<a name="L1736" href="source/net/ipv4/af_inet.c#L1736">1736</a> 
<a name="L1737" href="source/net/ipv4/af_inet.c#L1737">1737</a>         <a href="ident?i=ip_init">ip_init</a>();
<a name="L1738" href="source/net/ipv4/af_inet.c#L1738">1738</a> 
<a name="L1739" href="source/net/ipv4/af_inet.c#L1739">1739</a>         <a href="ident?i=tcp_v4_init">tcp_v4_init</a>();
<a name="L1740" href="source/net/ipv4/af_inet.c#L1740">1740</a> 
<a name="L1741" href="source/net/ipv4/af_inet.c#L1741">1741</a>         <b><i>/* Setup TCP slab cache for open requests. */</i></b>
<a name="L1742" href="source/net/ipv4/af_inet.c#L1742">1742</a>         <a href="ident?i=tcp_init">tcp_init</a>();
<a name="L1743" href="source/net/ipv4/af_inet.c#L1743">1743</a> 
<a name="L1744" href="source/net/ipv4/af_inet.c#L1744">1744</a>         <b><i>/* Setup UDP memory threshold */</i></b>
<a name="L1745" href="source/net/ipv4/af_inet.c#L1745">1745</a>         <a href="ident?i=udp_init">udp_init</a>();
<a name="L1746" href="source/net/ipv4/af_inet.c#L1746">1746</a> 
<a name="L1747" href="source/net/ipv4/af_inet.c#L1747">1747</a>         <b><i>/* Add UDP-Lite (RFC 3828) */</i></b>
<a name="L1748" href="source/net/ipv4/af_inet.c#L1748">1748</a>         <a href="ident?i=udplite4_register">udplite4_register</a>();
<a name="L1749" href="source/net/ipv4/af_inet.c#L1749">1749</a> 
<a name="L1750" href="source/net/ipv4/af_inet.c#L1750">1750</a>         <a href="ident?i=ping_init">ping_init</a>();
<a name="L1751" href="source/net/ipv4/af_inet.c#L1751">1751</a> 
<a name="L1752" href="source/net/ipv4/af_inet.c#L1752">1752</a>         <b><i>/*</i></b>
<a name="L1753" href="source/net/ipv4/af_inet.c#L1753">1753</a> <b><i>         *      Set the ICMP layer up</i></b>
<a name="L1754" href="source/net/ipv4/af_inet.c#L1754">1754</a> <b><i>         */</i></b>
<a name="L1755" href="source/net/ipv4/af_inet.c#L1755">1755</a> 
<a name="L1756" href="source/net/ipv4/af_inet.c#L1756">1756</a>         if (<a href="ident?i=icmp_init">icmp_init</a>() &lt; 0)
<a name="L1757" href="source/net/ipv4/af_inet.c#L1757">1757</a>                 <a href="ident?i=panic">panic</a>(<i>"Failed to create the ICMP control socket.\n"</i>);
<a name="L1758" href="source/net/ipv4/af_inet.c#L1758">1758</a> 
<a name="L1759" href="source/net/ipv4/af_inet.c#L1759">1759</a>         <b><i>/*</i></b>
<a name="L1760" href="source/net/ipv4/af_inet.c#L1760">1760</a> <b><i>         *      Initialise the multicast router</i></b>
<a name="L1761" href="source/net/ipv4/af_inet.c#L1761">1761</a> <b><i>         */</i></b>
<a name="L1762" href="source/net/ipv4/af_inet.c#L1762">1762</a> #if defined(CONFIG_IP_MROUTE)
<a name="L1763" href="source/net/ipv4/af_inet.c#L1763">1763</a>         if (<a href="ident?i=ip_mr_init">ip_mr_init</a>())
<a name="L1764" href="source/net/ipv4/af_inet.c#L1764">1764</a>                 <a href="ident?i=pr_crit">pr_crit</a>(<i>"%s: Cannot init ipv4 mroute\n"</i>, <a href="ident?i=__func__">__func__</a>);
<a name="L1765" href="source/net/ipv4/af_inet.c#L1765">1765</a> #endif
<a name="L1766" href="source/net/ipv4/af_inet.c#L1766">1766</a> 
<a name="L1767" href="source/net/ipv4/af_inet.c#L1767">1767</a>         if (<a href="ident?i=init_inet_pernet_ops">init_inet_pernet_ops</a>())
<a name="L1768" href="source/net/ipv4/af_inet.c#L1768">1768</a>                 <a href="ident?i=pr_crit">pr_crit</a>(<i>"%s: Cannot init ipv4 inet pernet ops\n"</i>, <a href="ident?i=__func__">__func__</a>);
<a name="L1769" href="source/net/ipv4/af_inet.c#L1769">1769</a>         <b><i>/*</i></b>
<a name="L1770" href="source/net/ipv4/af_inet.c#L1770">1770</a> <b><i>         *      Initialise per-cpu ipv4 mibs</i></b>
<a name="L1771" href="source/net/ipv4/af_inet.c#L1771">1771</a> <b><i>         */</i></b>
<a name="L1772" href="source/net/ipv4/af_inet.c#L1772">1772</a> 
<a name="L1773" href="source/net/ipv4/af_inet.c#L1773">1773</a>         if (<a href="ident?i=init_ipv4_mibs">init_ipv4_mibs</a>())
<a name="L1774" href="source/net/ipv4/af_inet.c#L1774">1774</a>                 <a href="ident?i=pr_crit">pr_crit</a>(<i>"%s: Cannot init ipv4 mibs\n"</i>, <a href="ident?i=__func__">__func__</a>);
<a name="L1775" href="source/net/ipv4/af_inet.c#L1775">1775</a> 
<a name="L1776" href="source/net/ipv4/af_inet.c#L1776">1776</a>         <a href="ident?i=ipv4_proc_init">ipv4_proc_init</a>();
<a name="L1777" href="source/net/ipv4/af_inet.c#L1777">1777</a> 
<a name="L1778" href="source/net/ipv4/af_inet.c#L1778">1778</a>         <a href="ident?i=ipfrag_init">ipfrag_init</a>();
<a name="L1779" href="source/net/ipv4/af_inet.c#L1779">1779</a> 
<a name="L1780" href="source/net/ipv4/af_inet.c#L1780">1780</a>         <a href="ident?i=dev_add_pack">dev_add_pack</a>(&amp;ip_packet_type);
<a name="L1781" href="source/net/ipv4/af_inet.c#L1781">1781</a> 
<a name="L1782" href="source/net/ipv4/af_inet.c#L1782">1782</a>         <a href="ident?i=rc">rc</a> = 0;
<a name="L1783" href="source/net/ipv4/af_inet.c#L1783">1783</a> <a href="ident?i=out">out</a>:
<a name="L1784" href="source/net/ipv4/af_inet.c#L1784">1784</a>         return <a href="ident?i=rc">rc</a>;
<a name="L1785" href="source/net/ipv4/af_inet.c#L1785">1785</a> out_unregister_raw_proto:
<a name="L1786" href="source/net/ipv4/af_inet.c#L1786">1786</a>         <a href="ident?i=proto_unregister">proto_unregister</a>(&amp;<a href="ident?i=raw_prot">raw_prot</a>);
<a name="L1787" href="source/net/ipv4/af_inet.c#L1787">1787</a> out_unregister_udp_proto:
<a name="L1788" href="source/net/ipv4/af_inet.c#L1788">1788</a>         <a href="ident?i=proto_unregister">proto_unregister</a>(&amp;<a href="ident?i=udp_prot">udp_prot</a>);
<a name="L1789" href="source/net/ipv4/af_inet.c#L1789">1789</a> out_unregister_tcp_proto:
<a name="L1790" href="source/net/ipv4/af_inet.c#L1790">1790</a>         <a href="ident?i=proto_unregister">proto_unregister</a>(&amp;<a href="ident?i=tcp_prot">tcp_prot</a>);
<a name="L1791" href="source/net/ipv4/af_inet.c#L1791">1791</a>         goto <a href="ident?i=out">out</a>;
<a name="L1792" href="source/net/ipv4/af_inet.c#L1792">1792</a> }
<a name="L1793" href="source/net/ipv4/af_inet.c#L1793">1793</a> 
<a name="L1794" href="source/net/ipv4/af_inet.c#L1794">1794</a> <a href="ident?i=fs_initcall">fs_initcall</a>(<a href="ident?i=inet_init">inet_init</a>);
<a name="L1795" href="source/net/ipv4/af_inet.c#L1795">1795</a> 
<a name="L1796" href="source/net/ipv4/af_inet.c#L1796">1796</a> <b><i>/* ------------------------------------------------------------------------ */</i></b>
<a name="L1797" href="source/net/ipv4/af_inet.c#L1797">1797</a> 
<a name="L1798" href="source/net/ipv4/af_inet.c#L1798">1798</a> #ifdef CONFIG_PROC_FS
<a name="L1799" href="source/net/ipv4/af_inet.c#L1799">1799</a> static int <a href="ident?i=__init">__init</a> <a href="ident?i=ipv4_proc_init">ipv4_proc_init</a>(void)
<a name="L1800" href="source/net/ipv4/af_inet.c#L1800">1800</a> {
<a name="L1801" href="source/net/ipv4/af_inet.c#L1801">1801</a>         int <a href="ident?i=rc">rc</a> = 0;
<a name="L1802" href="source/net/ipv4/af_inet.c#L1802">1802</a> 
<a name="L1803" href="source/net/ipv4/af_inet.c#L1803">1803</a>         if (<a href="ident?i=raw_proc_init">raw_proc_init</a>())
<a name="L1804" href="source/net/ipv4/af_inet.c#L1804">1804</a>                 goto out_raw;
<a name="L1805" href="source/net/ipv4/af_inet.c#L1805">1805</a>         if (<a href="ident?i=tcp4_proc_init">tcp4_proc_init</a>())
<a name="L1806" href="source/net/ipv4/af_inet.c#L1806">1806</a>                 goto out_tcp;
<a name="L1807" href="source/net/ipv4/af_inet.c#L1807">1807</a>         if (<a href="ident?i=udp4_proc_init">udp4_proc_init</a>())
<a name="L1808" href="source/net/ipv4/af_inet.c#L1808">1808</a>                 goto out_udp;
<a name="L1809" href="source/net/ipv4/af_inet.c#L1809">1809</a>         if (<a href="ident?i=ping_proc_init">ping_proc_init</a>())
<a name="L1810" href="source/net/ipv4/af_inet.c#L1810">1810</a>                 goto out_ping;
<a name="L1811" href="source/net/ipv4/af_inet.c#L1811">1811</a>         if (<a href="ident?i=ip_misc_proc_init">ip_misc_proc_init</a>())
<a name="L1812" href="source/net/ipv4/af_inet.c#L1812">1812</a>                 goto out_misc;
<a name="L1813" href="source/net/ipv4/af_inet.c#L1813">1813</a> <a href="ident?i=out">out</a>:
<a name="L1814" href="source/net/ipv4/af_inet.c#L1814">1814</a>         return <a href="ident?i=rc">rc</a>;
<a name="L1815" href="source/net/ipv4/af_inet.c#L1815">1815</a> out_misc:
<a name="L1816" href="source/net/ipv4/af_inet.c#L1816">1816</a>         <a href="ident?i=ping_proc_exit">ping_proc_exit</a>();
<a name="L1817" href="source/net/ipv4/af_inet.c#L1817">1817</a> out_ping:
<a name="L1818" href="source/net/ipv4/af_inet.c#L1818">1818</a>         <a href="ident?i=udp4_proc_exit">udp4_proc_exit</a>();
<a name="L1819" href="source/net/ipv4/af_inet.c#L1819">1819</a> out_udp:
<a name="L1820" href="source/net/ipv4/af_inet.c#L1820">1820</a>         <a href="ident?i=tcp4_proc_exit">tcp4_proc_exit</a>();
<a name="L1821" href="source/net/ipv4/af_inet.c#L1821">1821</a> out_tcp:
<a name="L1822" href="source/net/ipv4/af_inet.c#L1822">1822</a>         <a href="ident?i=raw_proc_exit">raw_proc_exit</a>();
<a name="L1823" href="source/net/ipv4/af_inet.c#L1823">1823</a> out_raw:
<a name="L1824" href="source/net/ipv4/af_inet.c#L1824">1824</a>         <a href="ident?i=rc">rc</a> = -<a href="ident?i=ENOMEM">ENOMEM</a>;
<a name="L1825" href="source/net/ipv4/af_inet.c#L1825">1825</a>         goto <a href="ident?i=out">out</a>;
<a name="L1826" href="source/net/ipv4/af_inet.c#L1826">1826</a> }
<a name="L1827" href="source/net/ipv4/af_inet.c#L1827">1827</a> 
<a name="L1828" href="source/net/ipv4/af_inet.c#L1828">1828</a> #else <b><i>/* CONFIG_PROC_FS */</i></b>
<a name="L1829" href="source/net/ipv4/af_inet.c#L1829">1829</a> static int <a href="ident?i=__init">__init</a> <a href="ident?i=ipv4_proc_init">ipv4_proc_init</a>(void)
<a name="L1830" href="source/net/ipv4/af_inet.c#L1830">1830</a> {
<a name="L1831" href="source/net/ipv4/af_inet.c#L1831">1831</a>         return 0;
<a name="L1832" href="source/net/ipv4/af_inet.c#L1832">1832</a> }
<a name="L1833" href="source/net/ipv4/af_inet.c#L1833">1833</a> #endif <b><i>/* CONFIG_PROC_FS */</i></b>
<a name="L1834" href="source/net/ipv4/af_inet.c#L1834">1834</a> 
<a name="L1835" href="source/net/ipv4/af_inet.c#L1835">1835</a> <a href="ident?i=MODULE_ALIAS_NETPROTO">MODULE_ALIAS_NETPROTO</a>(<a href="ident?i=PF_INET">PF_INET</a>);
<a name="L1836" href="source/net/ipv4/af_inet.c#L1836">1836</a> 
<a name="L1837" href="source/net/ipv4/af_inet.c#L1837">1837</a> </pre></div><p>
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
