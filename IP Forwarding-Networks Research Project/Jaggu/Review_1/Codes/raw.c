<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title>Linux/net/ipv4/raw.c - Linux Cross Reference - Free Electrons</title>
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
		 &nbsp;&bull;&nbsp;<b><i>source navigation</i></b> &nbsp;&bull;&nbsp;<a href="diff/net/ipv4/raw.c">diff markup</a> &nbsp;&bull;&nbsp;<a href="ident">identifier search</a> &nbsp;&bull;&nbsp;<a href="search">freetext search</a> &nbsp;&bull;&nbsp;
		</p>
	</div>
</div>

<div id="topbar">
  
  <p>Version: &nbsp;<a href="source/net/ipv4/raw.c?v=2.0.40">2.0.40</a>&nbsp;<a href="source/net/ipv4/raw.c?v=2.2.26">2.2.26</a>&nbsp;<a href="source/net/ipv4/raw.c?v=2.4.37">2.4.37</a>&nbsp;<a href="source/net/ipv4/raw.c?v=3.5">3.5</a>&nbsp;<a href="source/net/ipv4/raw.c?v=3.6">3.6</a>&nbsp;<a href="source/net/ipv4/raw.c?v=3.7">3.7</a>&nbsp;<a href="source/net/ipv4/raw.c?v=3.8">3.8</a>&nbsp;<a href="source/net/ipv4/raw.c?v=3.9">3.9</a>&nbsp;<a href="source/net/ipv4/raw.c?v=3.10">3.10</a>&nbsp;<a href="source/net/ipv4/raw.c?v=3.11">3.11</a>&nbsp;<a href="source/net/ipv4/raw.c?v=3.12">3.12</a>&nbsp;<a href="source/net/ipv4/raw.c?v=3.13">3.13</a>&nbsp;<a href="source/net/ipv4/raw.c?v=3.14">3.14</a>&nbsp;<a href="source/net/ipv4/raw.c?v=3.15">3.15</a>&nbsp;<a href="source/net/ipv4/raw.c?v=3.16">3.16</a>&nbsp;<a href="source/net/ipv4/raw.c?v=3.17">3.17</a>&nbsp;<a href="source/net/ipv4/raw.c?v=3.18">3.18</a>&nbsp;<a href="source/net/ipv4/raw.c?v=3.19">3.19</a>&nbsp;<a href="source/net/ipv4/raw.c?v=4.0">4.0</a>&nbsp;<b><i>4.1</i></b></p>
  
</div>

<h1><a href="source/">Linux</a>/<a href="source/net/">net</a>/<a href="source/net/ipv4/">ipv4</a>/<a href="source/net/ipv4/raw.c">raw.c</a></h1>
<div id="lxrcode"><pre>  <a name="L1" href="source/net/ipv4/raw.c#L1">1</a> <b><i>/*</i></b>
  <a name="L2" href="source/net/ipv4/raw.c#L2">2</a> <b><i> * INET         An implementation of the TCP/IP protocol suite for the LINUX</i></b>
  <a name="L3" href="source/net/ipv4/raw.c#L3">3</a> <b><i> *              operating system.  INET is implemented using the  BSD Socket</i></b>
  <a name="L4" href="source/net/ipv4/raw.c#L4">4</a> <b><i> *              interface as the means of communication with the user level.</i></b>
  <a name="L5" href="source/net/ipv4/raw.c#L5">5</a> <b><i> *</i></b>
  <a name="L6" href="source/net/ipv4/raw.c#L6">6</a> <b><i> *              RAW - implementation of IP "raw" sockets.</i></b>
  <a name="L7" href="source/net/ipv4/raw.c#L7">7</a> <b><i> *</i></b>
  <a name="L8" href="source/net/ipv4/raw.c#L8">8</a> <b><i> * Authors:     Ross Biro</i></b>
  <a name="L9" href="source/net/ipv4/raw.c#L9">9</a> <b><i> *              Fred N. van Kempen, &lt;waltje@uWalt.NL.Mugnet.ORG&gt;</i></b>
 <a name="L10" href="source/net/ipv4/raw.c#L10">10</a> <b><i> *</i></b>
 <a name="L11" href="source/net/ipv4/raw.c#L11">11</a> <b><i> * Fixes:</i></b>
 <a name="L12" href="source/net/ipv4/raw.c#L12">12</a> <b><i> *              Alan Cox        :       verify_area() fixed up</i></b>
 <a name="L13" href="source/net/ipv4/raw.c#L13">13</a> <b><i> *              Alan Cox        :       ICMP error handling</i></b>
 <a name="L14" href="source/net/ipv4/raw.c#L14">14</a> <b><i> *              Alan Cox        :       EMSGSIZE if you send too big a packet</i></b>
 <a name="L15" href="source/net/ipv4/raw.c#L15">15</a> <b><i> *              Alan Cox        :       Now uses generic datagrams and shared</i></b>
 <a name="L16" href="source/net/ipv4/raw.c#L16">16</a> <b><i> *                                      skbuff library. No more peek crashes,</i></b>
 <a name="L17" href="source/net/ipv4/raw.c#L17">17</a> <b><i> *                                      no more backlogs</i></b>
 <a name="L18" href="source/net/ipv4/raw.c#L18">18</a> <b><i> *              Alan Cox        :       Checks sk-&gt;broadcast.</i></b>
 <a name="L19" href="source/net/ipv4/raw.c#L19">19</a> <b><i> *              Alan Cox        :       Uses skb_free_datagram/skb_copy_datagram</i></b>
 <a name="L20" href="source/net/ipv4/raw.c#L20">20</a> <b><i> *              Alan Cox        :       Raw passes ip options too</i></b>
 <a name="L21" href="source/net/ipv4/raw.c#L21">21</a> <b><i> *              Alan Cox        :       Setsocketopt added</i></b>
 <a name="L22" href="source/net/ipv4/raw.c#L22">22</a> <b><i> *              Alan Cox        :       Fixed error return for broadcasts</i></b>
 <a name="L23" href="source/net/ipv4/raw.c#L23">23</a> <b><i> *              Alan Cox        :       Removed wake_up calls</i></b>
 <a name="L24" href="source/net/ipv4/raw.c#L24">24</a> <b><i> *              Alan Cox        :       Use ttl/tos</i></b>
 <a name="L25" href="source/net/ipv4/raw.c#L25">25</a> <b><i> *              Alan Cox        :       Cleaned up old debugging</i></b>
 <a name="L26" href="source/net/ipv4/raw.c#L26">26</a> <b><i> *              Alan Cox        :       Use new kernel side addresses</i></b>
 <a name="L27" href="source/net/ipv4/raw.c#L27">27</a> <b><i> *      Arnt Gulbrandsen        :       Fixed MSG_DONTROUTE in raw sockets.</i></b>
 <a name="L28" href="source/net/ipv4/raw.c#L28">28</a> <b><i> *              Alan Cox        :       BSD style RAW socket demultiplexing.</i></b>
 <a name="L29" href="source/net/ipv4/raw.c#L29">29</a> <b><i> *              Alan Cox        :       Beginnings of mrouted support.</i></b>
 <a name="L30" href="source/net/ipv4/raw.c#L30">30</a> <b><i> *              Alan Cox        :       Added IP_HDRINCL option.</i></b>
 <a name="L31" href="source/net/ipv4/raw.c#L31">31</a> <b><i> *              Alan Cox        :       Skip broadcast check if BSDism set.</i></b>
 <a name="L32" href="source/net/ipv4/raw.c#L32">32</a> <b><i> *              David S. Miller :       New socket lookup architecture.</i></b>
 <a name="L33" href="source/net/ipv4/raw.c#L33">33</a> <b><i> *</i></b>
 <a name="L34" href="source/net/ipv4/raw.c#L34">34</a> <b><i> *              This program is free software; you can redistribute it and/or</i></b>
 <a name="L35" href="source/net/ipv4/raw.c#L35">35</a> <b><i> *              modify it under the terms of the GNU General Public License</i></b>
 <a name="L36" href="source/net/ipv4/raw.c#L36">36</a> <b><i> *              as published by the Free Software Foundation; either version</i></b>
 <a name="L37" href="source/net/ipv4/raw.c#L37">37</a> <b><i> *              2 of the License, or (at your option) any later version.</i></b>
 <a name="L38" href="source/net/ipv4/raw.c#L38">38</a> <b><i> */</i></b>
 <a name="L39" href="source/net/ipv4/raw.c#L39">39</a> 
 <a name="L40" href="source/net/ipv4/raw.c#L40">40</a> #include &lt;linux/types.h&gt;
 <a name="L41" href="source/net/ipv4/raw.c#L41">41</a> #include &lt;linux/atomic.h&gt;
 <a name="L42" href="source/net/ipv4/raw.c#L42">42</a> #include &lt;asm/byteorder.h&gt;
 <a name="L43" href="source/net/ipv4/raw.c#L43">43</a> #include &lt;asm/current.h&gt;
 <a name="L44" href="source/net/ipv4/raw.c#L44">44</a> #include &lt;asm/uaccess.h&gt;
 <a name="L45" href="source/net/ipv4/raw.c#L45">45</a> #include &lt;asm/ioctls.h&gt;
 <a name="L46" href="source/net/ipv4/raw.c#L46">46</a> #include &lt;linux/stddef.h&gt;
 <a name="L47" href="source/net/ipv4/raw.c#L47">47</a> #include &lt;linux/slab.h&gt;
 <a name="L48" href="source/net/ipv4/raw.c#L48">48</a> #include &lt;linux/errno.h&gt;
 <a name="L49" href="source/net/ipv4/raw.c#L49">49</a> #include &lt;linux/kernel.h&gt;
 <a name="L50" href="source/net/ipv4/raw.c#L50">50</a> #include &lt;linux/export.h&gt;
 <a name="L51" href="source/net/ipv4/raw.c#L51">51</a> #include &lt;linux/spinlock.h&gt;
 <a name="L52" href="source/net/ipv4/raw.c#L52">52</a> #include &lt;linux/sockios.h&gt;
 <a name="L53" href="source/net/ipv4/raw.c#L53">53</a> #include &lt;linux/socket.h&gt;
 <a name="L54" href="source/net/ipv4/raw.c#L54">54</a> #include &lt;linux/in.h&gt;
 <a name="L55" href="source/net/ipv4/raw.c#L55">55</a> #include &lt;linux/mroute.h&gt;
 <a name="L56" href="source/net/ipv4/raw.c#L56">56</a> #include &lt;linux/netdevice.h&gt;
 <a name="L57" href="source/net/ipv4/raw.c#L57">57</a> #include &lt;linux/in_route.h&gt;
 <a name="L58" href="source/net/ipv4/raw.c#L58">58</a> #include &lt;linux/route.h&gt;
 <a name="L59" href="source/net/ipv4/raw.c#L59">59</a> #include &lt;linux/skbuff.h&gt;
 <a name="L60" href="source/net/ipv4/raw.c#L60">60</a> #include &lt;linux/igmp.h&gt;
 <a name="L61" href="source/net/ipv4/raw.c#L61">61</a> #include &lt;net/net_namespace.h&gt;
 <a name="L62" href="source/net/ipv4/raw.c#L62">62</a> #include &lt;net/dst.h&gt;
 <a name="L63" href="source/net/ipv4/raw.c#L63">63</a> #include &lt;net/sock.h&gt;
 <a name="L64" href="source/net/ipv4/raw.c#L64">64</a> #include &lt;linux/ip.h&gt;
 <a name="L65" href="source/net/ipv4/raw.c#L65">65</a> #include &lt;linux/net.h&gt;
 <a name="L66" href="source/net/ipv4/raw.c#L66">66</a> #include &lt;net/ip.h&gt;
 <a name="L67" href="source/net/ipv4/raw.c#L67">67</a> #include &lt;net/icmp.h&gt;
 <a name="L68" href="source/net/ipv4/raw.c#L68">68</a> #include &lt;net/udp.h&gt;
 <a name="L69" href="source/net/ipv4/raw.c#L69">69</a> #include &lt;net/raw.h&gt;
 <a name="L70" href="source/net/ipv4/raw.c#L70">70</a> #include &lt;net/snmp.h&gt;
 <a name="L71" href="source/net/ipv4/raw.c#L71">71</a> #include &lt;net/tcp_states.h&gt;
 <a name="L72" href="source/net/ipv4/raw.c#L72">72</a> #include &lt;net/inet_common.h&gt;
 <a name="L73" href="source/net/ipv4/raw.c#L73">73</a> #include &lt;net/checksum.h&gt;
 <a name="L74" href="source/net/ipv4/raw.c#L74">74</a> #include &lt;net/xfrm.h&gt;
 <a name="L75" href="source/net/ipv4/raw.c#L75">75</a> #include &lt;linux/rtnetlink.h&gt;
 <a name="L76" href="source/net/ipv4/raw.c#L76">76</a> #include &lt;linux/proc_fs.h&gt;
 <a name="L77" href="source/net/ipv4/raw.c#L77">77</a> #include &lt;linux/seq_file.h&gt;
 <a name="L78" href="source/net/ipv4/raw.c#L78">78</a> #include &lt;linux/netfilter.h&gt;
 <a name="L79" href="source/net/ipv4/raw.c#L79">79</a> #include &lt;linux/netfilter_ipv4.h&gt;
 <a name="L80" href="source/net/ipv4/raw.c#L80">80</a> #include &lt;linux/compat.h&gt;
 <a name="L81" href="source/net/ipv4/raw.c#L81">81</a> #include &lt;linux/uio.h&gt;
 <a name="L82" href="source/net/ipv4/raw.c#L82">82</a> 
 <a name="L83" href="source/net/ipv4/raw.c#L83">83</a> struct <a href="ident?i=raw_frag_vec">raw_frag_vec</a> {
 <a name="L84" href="source/net/ipv4/raw.c#L84">84</a>         struct <a href="ident?i=msghdr">msghdr</a> *<a href="ident?i=msg">msg</a>;
 <a name="L85" href="source/net/ipv4/raw.c#L85">85</a>         union {
 <a name="L86" href="source/net/ipv4/raw.c#L86">86</a>                 struct <a href="ident?i=icmphdr">icmphdr</a> icmph;
 <a name="L87" href="source/net/ipv4/raw.c#L87">87</a>                 char <a href="ident?i=c">c</a>[1];
 <a name="L88" href="source/net/ipv4/raw.c#L88">88</a>         } <a href="ident?i=hdr">hdr</a>;
 <a name="L89" href="source/net/ipv4/raw.c#L89">89</a>         int hlen;
 <a name="L90" href="source/net/ipv4/raw.c#L90">90</a> };
 <a name="L91" href="source/net/ipv4/raw.c#L91">91</a> 
 <a name="L92" href="source/net/ipv4/raw.c#L92">92</a> static struct <a href="ident?i=raw_hashinfo">raw_hashinfo</a> <a href="ident?i=raw_v4_hashinfo">raw_v4_hashinfo</a> = {
 <a name="L93" href="source/net/ipv4/raw.c#L93">93</a>         .<a href="ident?i=lock">lock</a> = <a href="ident?i=__RW_LOCK_UNLOCKED">__RW_LOCK_UNLOCKED</a>(<a href="ident?i=raw_v4_hashinfo">raw_v4_hashinfo</a>.<a href="ident?i=lock">lock</a>),
 <a name="L94" href="source/net/ipv4/raw.c#L94">94</a> };
 <a name="L95" href="source/net/ipv4/raw.c#L95">95</a> 
 <a name="L96" href="source/net/ipv4/raw.c#L96">96</a> void <a href="ident?i=raw_hash_sk">raw_hash_sk</a>(struct <a href="ident?i=sock">sock</a> *sk)
 <a name="L97" href="source/net/ipv4/raw.c#L97">97</a> {
 <a name="L98" href="source/net/ipv4/raw.c#L98">98</a>         struct <a href="ident?i=raw_hashinfo">raw_hashinfo</a> *<a href="ident?i=h">h</a> = sk-&gt;<a href="ident?i=sk_prot">sk_prot</a>-&gt;<a href="ident?i=h">h</a>.<a href="ident?i=raw_hash">raw_hash</a>;
 <a name="L99" href="source/net/ipv4/raw.c#L99">99</a>         struct <a href="ident?i=hlist_head">hlist_head</a> *<a href="ident?i=head">head</a>;
<a name="L100" href="source/net/ipv4/raw.c#L100">100</a> 
<a name="L101" href="source/net/ipv4/raw.c#L101">101</a>         <a href="ident?i=head">head</a> = &amp;<a href="ident?i=h">h</a>-&gt;<a href="ident?i=ht">ht</a>[<a href="ident?i=inet_sk">inet_sk</a>(sk)-&gt;<a href="ident?i=inet_num">inet_num</a> &amp; (<a href="ident?i=RAW_HTABLE_SIZE">RAW_HTABLE_SIZE</a> - 1)];
<a name="L102" href="source/net/ipv4/raw.c#L102">102</a> 
<a name="L103" href="source/net/ipv4/raw.c#L103">103</a>         <a href="ident?i=write_lock_bh">write_lock_bh</a>(&amp;<a href="ident?i=h">h</a>-&gt;<a href="ident?i=lock">lock</a>);
<a name="L104" href="source/net/ipv4/raw.c#L104">104</a>         <a href="ident?i=sk_add_node">sk_add_node</a>(sk, <a href="ident?i=head">head</a>);
<a name="L105" href="source/net/ipv4/raw.c#L105">105</a>         <a href="ident?i=sock_prot_inuse_add">sock_prot_inuse_add</a>(<a href="ident?i=sock_net">sock_net</a>(sk), sk-&gt;<a href="ident?i=sk_prot">sk_prot</a>, 1);
<a name="L106" href="source/net/ipv4/raw.c#L106">106</a>         <a href="ident?i=write_unlock_bh">write_unlock_bh</a>(&amp;<a href="ident?i=h">h</a>-&gt;<a href="ident?i=lock">lock</a>);
<a name="L107" href="source/net/ipv4/raw.c#L107">107</a> }
<a name="L108" href="source/net/ipv4/raw.c#L108">108</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=raw_hash_sk">raw_hash_sk</a>);
<a name="L109" href="source/net/ipv4/raw.c#L109">109</a> 
<a name="L110" href="source/net/ipv4/raw.c#L110">110</a> void <a href="ident?i=raw_unhash_sk">raw_unhash_sk</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L111" href="source/net/ipv4/raw.c#L111">111</a> {
<a name="L112" href="source/net/ipv4/raw.c#L112">112</a>         struct <a href="ident?i=raw_hashinfo">raw_hashinfo</a> *<a href="ident?i=h">h</a> = sk-&gt;<a href="ident?i=sk_prot">sk_prot</a>-&gt;<a href="ident?i=h">h</a>.<a href="ident?i=raw_hash">raw_hash</a>;
<a name="L113" href="source/net/ipv4/raw.c#L113">113</a> 
<a name="L114" href="source/net/ipv4/raw.c#L114">114</a>         <a href="ident?i=write_lock_bh">write_lock_bh</a>(&amp;<a href="ident?i=h">h</a>-&gt;<a href="ident?i=lock">lock</a>);
<a name="L115" href="source/net/ipv4/raw.c#L115">115</a>         if (<a href="ident?i=sk_del_node_init">sk_del_node_init</a>(sk))
<a name="L116" href="source/net/ipv4/raw.c#L116">116</a>                 <a href="ident?i=sock_prot_inuse_add">sock_prot_inuse_add</a>(<a href="ident?i=sock_net">sock_net</a>(sk), sk-&gt;<a href="ident?i=sk_prot">sk_prot</a>, -1);
<a name="L117" href="source/net/ipv4/raw.c#L117">117</a>         <a href="ident?i=write_unlock_bh">write_unlock_bh</a>(&amp;<a href="ident?i=h">h</a>-&gt;<a href="ident?i=lock">lock</a>);
<a name="L118" href="source/net/ipv4/raw.c#L118">118</a> }
<a name="L119" href="source/net/ipv4/raw.c#L119">119</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=raw_unhash_sk">raw_unhash_sk</a>);
<a name="L120" href="source/net/ipv4/raw.c#L120">120</a> 
<a name="L121" href="source/net/ipv4/raw.c#L121">121</a> static struct <a href="ident?i=sock">sock</a> *<a href="ident?i=__raw_v4_lookup">__raw_v4_lookup</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>, struct <a href="ident?i=sock">sock</a> *sk,
<a name="L122" href="source/net/ipv4/raw.c#L122">122</a>                 unsigned short <a href="ident?i=num">num</a>, <a href="ident?i=__be32">__be32</a> raddr, <a href="ident?i=__be32">__be32</a> <a href="ident?i=laddr">laddr</a>, int dif)
<a name="L123" href="source/net/ipv4/raw.c#L123">123</a> {
<a name="L124" href="source/net/ipv4/raw.c#L124">124</a>         <a href="ident?i=sk_for_each_from">sk_for_each_from</a>(sk) {
<a name="L125" href="source/net/ipv4/raw.c#L125">125</a>                 struct <a href="ident?i=inet_sock">inet_sock</a> *inet = <a href="ident?i=inet_sk">inet_sk</a>(sk);
<a name="L126" href="source/net/ipv4/raw.c#L126">126</a> 
<a name="L127" href="source/net/ipv4/raw.c#L127">127</a>                 if (<a href="ident?i=net_eq">net_eq</a>(<a href="ident?i=sock_net">sock_net</a>(sk), <a href="ident?i=net">net</a>) &amp;&amp; inet-&gt;<a href="ident?i=inet_num">inet_num</a> == <a href="ident?i=num">num</a>  &amp;&amp;
<a name="L128" href="source/net/ipv4/raw.c#L128">128</a>                     !(inet-&gt;<a href="ident?i=inet_daddr">inet_daddr</a> &amp;&amp; inet-&gt;<a href="ident?i=inet_daddr">inet_daddr</a> != raddr)    &amp;&amp;
<a name="L129" href="source/net/ipv4/raw.c#L129">129</a>                     !(inet-&gt;<a href="ident?i=inet_rcv_saddr">inet_rcv_saddr</a> &amp;&amp; inet-&gt;<a href="ident?i=inet_rcv_saddr">inet_rcv_saddr</a> != <a href="ident?i=laddr">laddr</a>) &amp;&amp;
<a name="L130" href="source/net/ipv4/raw.c#L130">130</a>                     !(sk-&gt;<a href="ident?i=sk_bound_dev_if">sk_bound_dev_if</a> &amp;&amp; sk-&gt;<a href="ident?i=sk_bound_dev_if">sk_bound_dev_if</a> != dif))
<a name="L131" href="source/net/ipv4/raw.c#L131">131</a>                         goto <a href="ident?i=found">found</a>; <b><i>/* gotcha */</i></b>
<a name="L132" href="source/net/ipv4/raw.c#L132">132</a>         }
<a name="L133" href="source/net/ipv4/raw.c#L133">133</a>         sk = <a href="ident?i=NULL">NULL</a>;
<a name="L134" href="source/net/ipv4/raw.c#L134">134</a> <a href="ident?i=found">found</a>:
<a name="L135" href="source/net/ipv4/raw.c#L135">135</a>         return sk;
<a name="L136" href="source/net/ipv4/raw.c#L136">136</a> }
<a name="L137" href="source/net/ipv4/raw.c#L137">137</a> 
<a name="L138" href="source/net/ipv4/raw.c#L138">138</a> <b><i>/*</i></b>
<a name="L139" href="source/net/ipv4/raw.c#L139">139</a> <b><i> *      0 - deliver</i></b>
<a name="L140" href="source/net/ipv4/raw.c#L140">140</a> <b><i> *      1 - block</i></b>
<a name="L141" href="source/net/ipv4/raw.c#L141">141</a> <b><i> */</i></b>
<a name="L142" href="source/net/ipv4/raw.c#L142">142</a> static int <a href="ident?i=icmp_filter">icmp_filter</a>(const struct <a href="ident?i=sock">sock</a> *sk, const struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L143" href="source/net/ipv4/raw.c#L143">143</a> {
<a name="L144" href="source/net/ipv4/raw.c#L144">144</a>         struct <a href="ident?i=icmphdr">icmphdr</a> _hdr;
<a name="L145" href="source/net/ipv4/raw.c#L145">145</a>         const struct <a href="ident?i=icmphdr">icmphdr</a> *<a href="ident?i=hdr">hdr</a>;
<a name="L146" href="source/net/ipv4/raw.c#L146">146</a> 
<a name="L147" href="source/net/ipv4/raw.c#L147">147</a>         <a href="ident?i=hdr">hdr</a> = <a href="ident?i=skb_header_pointer">skb_header_pointer</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=skb_transport_offset">skb_transport_offset</a>(<a href="ident?i=skb">skb</a>),
<a name="L148" href="source/net/ipv4/raw.c#L148">148</a>                                  sizeof(_hdr), &amp;_hdr);
<a name="L149" href="source/net/ipv4/raw.c#L149">149</a>         if (!<a href="ident?i=hdr">hdr</a>)
<a name="L150" href="source/net/ipv4/raw.c#L150">150</a>                 return 1;
<a name="L151" href="source/net/ipv4/raw.c#L151">151</a> 
<a name="L152" href="source/net/ipv4/raw.c#L152">152</a>         if (<a href="ident?i=hdr">hdr</a>-&gt;<a href="ident?i=type">type</a> &lt; 32) {
<a name="L153" href="source/net/ipv4/raw.c#L153">153</a>                 <a href="ident?i=__u32">__u32</a> <a href="ident?i=data">data</a> = <a href="ident?i=raw_sk">raw_sk</a>(sk)-&gt;<a href="ident?i=filter">filter</a>.<a href="ident?i=data">data</a>;
<a name="L154" href="source/net/ipv4/raw.c#L154">154</a> 
<a name="L155" href="source/net/ipv4/raw.c#L155">155</a>                 return ((1U &lt;&lt; <a href="ident?i=hdr">hdr</a>-&gt;<a href="ident?i=type">type</a>) &amp; <a href="ident?i=data">data</a>) != 0;
<a name="L156" href="source/net/ipv4/raw.c#L156">156</a>         }
<a name="L157" href="source/net/ipv4/raw.c#L157">157</a> 
<a name="L158" href="source/net/ipv4/raw.c#L158">158</a>         <b><i>/* Do not block unknown ICMP types */</i></b>
<a name="L159" href="source/net/ipv4/raw.c#L159">159</a>         return 0;
<a name="L160" href="source/net/ipv4/raw.c#L160">160</a> }
<a name="L161" href="source/net/ipv4/raw.c#L161">161</a> 
<a name="L162" href="source/net/ipv4/raw.c#L162">162</a> <b><i>/* IP input processing comes here for RAW socket delivery.</i></b>
<a name="L163" href="source/net/ipv4/raw.c#L163">163</a> <b><i> * Caller owns SKB, so we must make clones.</i></b>
<a name="L164" href="source/net/ipv4/raw.c#L164">164</a> <b><i> *</i></b>
<a name="L165" href="source/net/ipv4/raw.c#L165">165</a> <b><i> * RFC 1122: SHOULD pass TOS value up to the transport layer.</i></b>
<a name="L166" href="source/net/ipv4/raw.c#L166">166</a> <b><i> * -&gt; It does. And not only TOS, but all IP header.</i></b>
<a name="L167" href="source/net/ipv4/raw.c#L167">167</a> <b><i> */</i></b>
<a name="L168" href="source/net/ipv4/raw.c#L168">168</a> static int <a href="ident?i=raw_v4_input">raw_v4_input</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, const struct <a href="ident?i=iphdr">iphdr</a> *iph, int <a href="ident?i=hash">hash</a>)
<a name="L169" href="source/net/ipv4/raw.c#L169">169</a> {
<a name="L170" href="source/net/ipv4/raw.c#L170">170</a>         struct <a href="ident?i=sock">sock</a> *sk;
<a name="L171" href="source/net/ipv4/raw.c#L171">171</a>         struct <a href="ident?i=hlist_head">hlist_head</a> *<a href="ident?i=head">head</a>;
<a name="L172" href="source/net/ipv4/raw.c#L172">172</a>         int delivered = 0;
<a name="L173" href="source/net/ipv4/raw.c#L173">173</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>;
<a name="L174" href="source/net/ipv4/raw.c#L174">174</a> 
<a name="L175" href="source/net/ipv4/raw.c#L175">175</a>         <a href="ident?i=read_lock">read_lock</a>(&amp;<a href="ident?i=raw_v4_hashinfo">raw_v4_hashinfo</a>.<a href="ident?i=lock">lock</a>);
<a name="L176" href="source/net/ipv4/raw.c#L176">176</a>         <a href="ident?i=head">head</a> = &amp;<a href="ident?i=raw_v4_hashinfo">raw_v4_hashinfo</a>.<a href="ident?i=ht">ht</a>[<a href="ident?i=hash">hash</a>];
<a name="L177" href="source/net/ipv4/raw.c#L177">177</a>         if (<a href="ident?i=hlist_empty">hlist_empty</a>(<a href="ident?i=head">head</a>))
<a name="L178" href="source/net/ipv4/raw.c#L178">178</a>                 goto <a href="ident?i=out">out</a>;
<a name="L179" href="source/net/ipv4/raw.c#L179">179</a> 
<a name="L180" href="source/net/ipv4/raw.c#L180">180</a>         <a href="ident?i=net">net</a> = <a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=dev">dev</a>);
<a name="L181" href="source/net/ipv4/raw.c#L181">181</a>         sk = <a href="ident?i=__raw_v4_lookup">__raw_v4_lookup</a>(<a href="ident?i=net">net</a>, <a href="ident?i=__sk_head">__sk_head</a>(<a href="ident?i=head">head</a>), iph-&gt;<a href="ident?i=protocol">protocol</a>,
<a name="L182" href="source/net/ipv4/raw.c#L182">182</a>                              iph-&gt;<a href="ident?i=saddr">saddr</a>, iph-&gt;<a href="ident?i=daddr">daddr</a>,
<a name="L183" href="source/net/ipv4/raw.c#L183">183</a>                              <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=dev">dev</a>-&gt;ifindex);
<a name="L184" href="source/net/ipv4/raw.c#L184">184</a> 
<a name="L185" href="source/net/ipv4/raw.c#L185">185</a>         while (sk) {
<a name="L186" href="source/net/ipv4/raw.c#L186">186</a>                 delivered = 1;
<a name="L187" href="source/net/ipv4/raw.c#L187">187</a>                 if ((iph-&gt;<a href="ident?i=protocol">protocol</a> != <a href="ident?i=IPPROTO_ICMP">IPPROTO_ICMP</a> || !<a href="ident?i=icmp_filter">icmp_filter</a>(sk, <a href="ident?i=skb">skb</a>)) &amp;&amp;
<a name="L188" href="source/net/ipv4/raw.c#L188">188</a>                     <a href="ident?i=ip_mc_sf_allow">ip_mc_sf_allow</a>(sk, iph-&gt;<a href="ident?i=daddr">daddr</a>, iph-&gt;<a href="ident?i=saddr">saddr</a>,
<a name="L189" href="source/net/ipv4/raw.c#L189">189</a>                                    <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=dev">dev</a>-&gt;ifindex)) {
<a name="L190" href="source/net/ipv4/raw.c#L190">190</a>                         struct <a href="ident?i=sk_buff">sk_buff</a> *clone = <a href="ident?i=skb_clone">skb_clone</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=GFP_ATOMIC">GFP_ATOMIC</a>);
<a name="L191" href="source/net/ipv4/raw.c#L191">191</a> 
<a name="L192" href="source/net/ipv4/raw.c#L192">192</a>                         <b><i>/* Not releasing hash table! */</i></b>
<a name="L193" href="source/net/ipv4/raw.c#L193">193</a>                         if (clone)
<a name="L194" href="source/net/ipv4/raw.c#L194">194</a>                                 <a href="ident?i=raw_rcv">raw_rcv</a>(sk, clone);
<a name="L195" href="source/net/ipv4/raw.c#L195">195</a>                 }
<a name="L196" href="source/net/ipv4/raw.c#L196">196</a>                 sk = <a href="ident?i=__raw_v4_lookup">__raw_v4_lookup</a>(<a href="ident?i=net">net</a>, <a href="ident?i=sk_next">sk_next</a>(sk), iph-&gt;<a href="ident?i=protocol">protocol</a>,
<a name="L197" href="source/net/ipv4/raw.c#L197">197</a>                                      iph-&gt;<a href="ident?i=saddr">saddr</a>, iph-&gt;<a href="ident?i=daddr">daddr</a>,
<a name="L198" href="source/net/ipv4/raw.c#L198">198</a>                                      <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=dev">dev</a>-&gt;ifindex);
<a name="L199" href="source/net/ipv4/raw.c#L199">199</a>         }
<a name="L200" href="source/net/ipv4/raw.c#L200">200</a> <a href="ident?i=out">out</a>:
<a name="L201" href="source/net/ipv4/raw.c#L201">201</a>         <a href="ident?i=read_unlock">read_unlock</a>(&amp;<a href="ident?i=raw_v4_hashinfo">raw_v4_hashinfo</a>.<a href="ident?i=lock">lock</a>);
<a name="L202" href="source/net/ipv4/raw.c#L202">202</a>         return delivered;
<a name="L203" href="source/net/ipv4/raw.c#L203">203</a> }
<a name="L204" href="source/net/ipv4/raw.c#L204">204</a> 
<a name="L205" href="source/net/ipv4/raw.c#L205">205</a> int <a href="ident?i=raw_local_deliver">raw_local_deliver</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, int <a href="ident?i=protocol">protocol</a>)
<a name="L206" href="source/net/ipv4/raw.c#L206">206</a> {
<a name="L207" href="source/net/ipv4/raw.c#L207">207</a>         int <a href="ident?i=hash">hash</a>;
<a name="L208" href="source/net/ipv4/raw.c#L208">208</a>         struct <a href="ident?i=sock">sock</a> *<a href="ident?i=raw_sk">raw_sk</a>;
<a name="L209" href="source/net/ipv4/raw.c#L209">209</a> 
<a name="L210" href="source/net/ipv4/raw.c#L210">210</a>         <a href="ident?i=hash">hash</a> = <a href="ident?i=protocol">protocol</a> &amp; (<a href="ident?i=RAW_HTABLE_SIZE">RAW_HTABLE_SIZE</a> - 1);
<a name="L211" href="source/net/ipv4/raw.c#L211">211</a>         <a href="ident?i=raw_sk">raw_sk</a> = <a href="ident?i=sk_head">sk_head</a>(&amp;<a href="ident?i=raw_v4_hashinfo">raw_v4_hashinfo</a>.<a href="ident?i=ht">ht</a>[<a href="ident?i=hash">hash</a>]);
<a name="L212" href="source/net/ipv4/raw.c#L212">212</a> 
<a name="L213" href="source/net/ipv4/raw.c#L213">213</a>         <b><i>/* If there maybe a raw socket we must check - if not we</i></b>
<a name="L214" href="source/net/ipv4/raw.c#L214">214</a> <b><i>         * don't care less</i></b>
<a name="L215" href="source/net/ipv4/raw.c#L215">215</a> <b><i>         */</i></b>
<a name="L216" href="source/net/ipv4/raw.c#L216">216</a>         if (<a href="ident?i=raw_sk">raw_sk</a> &amp;&amp; !<a href="ident?i=raw_v4_input">raw_v4_input</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>), <a href="ident?i=hash">hash</a>))
<a name="L217" href="source/net/ipv4/raw.c#L217">217</a>                 <a href="ident?i=raw_sk">raw_sk</a> = <a href="ident?i=NULL">NULL</a>;
<a name="L218" href="source/net/ipv4/raw.c#L218">218</a> 
<a name="L219" href="source/net/ipv4/raw.c#L219">219</a>         return <a href="ident?i=raw_sk">raw_sk</a> != <a href="ident?i=NULL">NULL</a>;
<a name="L220" href="source/net/ipv4/raw.c#L220">220</a> 
<a name="L221" href="source/net/ipv4/raw.c#L221">221</a> }
<a name="L222" href="source/net/ipv4/raw.c#L222">222</a> 
<a name="L223" href="source/net/ipv4/raw.c#L223">223</a> static void <a href="ident?i=raw_err">raw_err</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, <a href="ident?i=u32">u32</a> <a href="ident?i=info">info</a>)
<a name="L224" href="source/net/ipv4/raw.c#L224">224</a> {
<a name="L225" href="source/net/ipv4/raw.c#L225">225</a>         struct <a href="ident?i=inet_sock">inet_sock</a> *inet = <a href="ident?i=inet_sk">inet_sk</a>(sk);
<a name="L226" href="source/net/ipv4/raw.c#L226">226</a>         const int <a href="ident?i=type">type</a> = <a href="ident?i=icmp_hdr">icmp_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=type">type</a>;
<a name="L227" href="source/net/ipv4/raw.c#L227">227</a>         const int <a href="ident?i=code">code</a> = <a href="ident?i=icmp_hdr">icmp_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=code">code</a>;
<a name="L228" href="source/net/ipv4/raw.c#L228">228</a>         int <a href="ident?i=err">err</a> = 0;
<a name="L229" href="source/net/ipv4/raw.c#L229">229</a>         int harderr = 0;
<a name="L230" href="source/net/ipv4/raw.c#L230">230</a> 
<a name="L231" href="source/net/ipv4/raw.c#L231">231</a>         if (<a href="ident?i=type">type</a> == <a href="ident?i=ICMP_DEST_UNREACH">ICMP_DEST_UNREACH</a> &amp;&amp; <a href="ident?i=code">code</a> == <a href="ident?i=ICMP_FRAG_NEEDED">ICMP_FRAG_NEEDED</a>)
<a name="L232" href="source/net/ipv4/raw.c#L232">232</a>                 <a href="ident?i=ipv4_sk_update_pmtu">ipv4_sk_update_pmtu</a>(<a href="ident?i=skb">skb</a>, sk, <a href="ident?i=info">info</a>);
<a name="L233" href="source/net/ipv4/raw.c#L233">233</a>         else if (<a href="ident?i=type">type</a> == <a href="ident?i=ICMP_REDIRECT">ICMP_REDIRECT</a>) {
<a name="L234" href="source/net/ipv4/raw.c#L234">234</a>                 <a href="ident?i=ipv4_sk_redirect">ipv4_sk_redirect</a>(<a href="ident?i=skb">skb</a>, sk);
<a name="L235" href="source/net/ipv4/raw.c#L235">235</a>                 return;
<a name="L236" href="source/net/ipv4/raw.c#L236">236</a>         }
<a name="L237" href="source/net/ipv4/raw.c#L237">237</a> 
<a name="L238" href="source/net/ipv4/raw.c#L238">238</a>         <b><i>/* Report error on raw socket, if:</i></b>
<a name="L239" href="source/net/ipv4/raw.c#L239">239</a> <b><i>           1. User requested ip_recverr.</i></b>
<a name="L240" href="source/net/ipv4/raw.c#L240">240</a> <b><i>           2. Socket is connected (otherwise the error indication</i></b>
<a name="L241" href="source/net/ipv4/raw.c#L241">241</a> <b><i>              is useless without ip_recverr and error is hard.</i></b>
<a name="L242" href="source/net/ipv4/raw.c#L242">242</a> <b><i>         */</i></b>
<a name="L243" href="source/net/ipv4/raw.c#L243">243</a>         if (!inet-&gt;recverr &amp;&amp; sk-&gt;<a href="ident?i=sk_state">sk_state</a> != TCP_ESTABLISHED)
<a name="L244" href="source/net/ipv4/raw.c#L244">244</a>                 return;
<a name="L245" href="source/net/ipv4/raw.c#L245">245</a> 
<a name="L246" href="source/net/ipv4/raw.c#L246">246</a>         switch (<a href="ident?i=type">type</a>) {
<a name="L247" href="source/net/ipv4/raw.c#L247">247</a>         default:
<a name="L248" href="source/net/ipv4/raw.c#L248">248</a>         case <a href="ident?i=ICMP_TIME_EXCEEDED">ICMP_TIME_EXCEEDED</a>:
<a name="L249" href="source/net/ipv4/raw.c#L249">249</a>                 <a href="ident?i=err">err</a> = <a href="ident?i=EHOSTUNREACH">EHOSTUNREACH</a>;
<a name="L250" href="source/net/ipv4/raw.c#L250">250</a>                 break;
<a name="L251" href="source/net/ipv4/raw.c#L251">251</a>         case <a href="ident?i=ICMP_SOURCE_QUENCH">ICMP_SOURCE_QUENCH</a>:
<a name="L252" href="source/net/ipv4/raw.c#L252">252</a>                 return;
<a name="L253" href="source/net/ipv4/raw.c#L253">253</a>         case <a href="ident?i=ICMP_PARAMETERPROB">ICMP_PARAMETERPROB</a>:
<a name="L254" href="source/net/ipv4/raw.c#L254">254</a>                 <a href="ident?i=err">err</a> = <a href="ident?i=EPROTO">EPROTO</a>;
<a name="L255" href="source/net/ipv4/raw.c#L255">255</a>                 harderr = 1;
<a name="L256" href="source/net/ipv4/raw.c#L256">256</a>                 break;
<a name="L257" href="source/net/ipv4/raw.c#L257">257</a>         case <a href="ident?i=ICMP_DEST_UNREACH">ICMP_DEST_UNREACH</a>:
<a name="L258" href="source/net/ipv4/raw.c#L258">258</a>                 <a href="ident?i=err">err</a> = <a href="ident?i=EHOSTUNREACH">EHOSTUNREACH</a>;
<a name="L259" href="source/net/ipv4/raw.c#L259">259</a>                 if (<a href="ident?i=code">code</a> &gt; <a href="ident?i=NR_ICMP_UNREACH">NR_ICMP_UNREACH</a>)
<a name="L260" href="source/net/ipv4/raw.c#L260">260</a>                         break;
<a name="L261" href="source/net/ipv4/raw.c#L261">261</a>                 <a href="ident?i=err">err</a> = <a href="ident?i=icmp_err_convert">icmp_err_convert</a>[<a href="ident?i=code">code</a>].<a href="ident?i=errno">errno</a>;
<a name="L262" href="source/net/ipv4/raw.c#L262">262</a>                 harderr = <a href="ident?i=icmp_err_convert">icmp_err_convert</a>[<a href="ident?i=code">code</a>].<a href="ident?i=fatal">fatal</a>;
<a name="L263" href="source/net/ipv4/raw.c#L263">263</a>                 if (<a href="ident?i=code">code</a> == <a href="ident?i=ICMP_FRAG_NEEDED">ICMP_FRAG_NEEDED</a>) {
<a name="L264" href="source/net/ipv4/raw.c#L264">264</a>                         harderr = inet-&gt;pmtudisc != <a href="ident?i=IP_PMTUDISC_DONT">IP_PMTUDISC_DONT</a>;
<a name="L265" href="source/net/ipv4/raw.c#L265">265</a>                         <a href="ident?i=err">err</a> = <a href="ident?i=EMSGSIZE">EMSGSIZE</a>;
<a name="L266" href="source/net/ipv4/raw.c#L266">266</a>                 }
<a name="L267" href="source/net/ipv4/raw.c#L267">267</a>         }
<a name="L268" href="source/net/ipv4/raw.c#L268">268</a> 
<a name="L269" href="source/net/ipv4/raw.c#L269">269</a>         if (inet-&gt;recverr) {
<a name="L270" href="source/net/ipv4/raw.c#L270">270</a>                 const struct <a href="ident?i=iphdr">iphdr</a> *iph = (const struct <a href="ident?i=iphdr">iphdr</a> *)<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=data">data</a>;
<a name="L271" href="source/net/ipv4/raw.c#L271">271</a>                 <a href="ident?i=u8">u8</a> *<a href="ident?i=payload">payload</a> = <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=data">data</a> + (iph-&gt;ihl &lt;&lt; 2);
<a name="L272" href="source/net/ipv4/raw.c#L272">272</a> 
<a name="L273" href="source/net/ipv4/raw.c#L273">273</a>                 if (inet-&gt;hdrincl)
<a name="L274" href="source/net/ipv4/raw.c#L274">274</a>                         <a href="ident?i=payload">payload</a> = <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=data">data</a>;
<a name="L275" href="source/net/ipv4/raw.c#L275">275</a>                 <a href="ident?i=ip_icmp_error">ip_icmp_error</a>(sk, <a href="ident?i=skb">skb</a>, <a href="ident?i=err">err</a>, 0, <a href="ident?i=info">info</a>, <a href="ident?i=payload">payload</a>);
<a name="L276" href="source/net/ipv4/raw.c#L276">276</a>         }
<a name="L277" href="source/net/ipv4/raw.c#L277">277</a> 
<a name="L278" href="source/net/ipv4/raw.c#L278">278</a>         if (inet-&gt;recverr || harderr) {
<a name="L279" href="source/net/ipv4/raw.c#L279">279</a>                 sk-&gt;sk_err = <a href="ident?i=err">err</a>;
<a name="L280" href="source/net/ipv4/raw.c#L280">280</a>                 sk-&gt;sk_error_report(sk);
<a name="L281" href="source/net/ipv4/raw.c#L281">281</a>         }
<a name="L282" href="source/net/ipv4/raw.c#L282">282</a> }
<a name="L283" href="source/net/ipv4/raw.c#L283">283</a> 
<a name="L284" href="source/net/ipv4/raw.c#L284">284</a> void <a href="ident?i=raw_icmp_error">raw_icmp_error</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, int <a href="ident?i=protocol">protocol</a>, <a href="ident?i=u32">u32</a> <a href="ident?i=info">info</a>)
<a name="L285" href="source/net/ipv4/raw.c#L285">285</a> {
<a name="L286" href="source/net/ipv4/raw.c#L286">286</a>         int <a href="ident?i=hash">hash</a>;
<a name="L287" href="source/net/ipv4/raw.c#L287">287</a>         struct <a href="ident?i=sock">sock</a> *<a href="ident?i=raw_sk">raw_sk</a>;
<a name="L288" href="source/net/ipv4/raw.c#L288">288</a>         const struct <a href="ident?i=iphdr">iphdr</a> *iph;
<a name="L289" href="source/net/ipv4/raw.c#L289">289</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>;
<a name="L290" href="source/net/ipv4/raw.c#L290">290</a> 
<a name="L291" href="source/net/ipv4/raw.c#L291">291</a>         <a href="ident?i=hash">hash</a> = <a href="ident?i=protocol">protocol</a> &amp; (<a href="ident?i=RAW_HTABLE_SIZE">RAW_HTABLE_SIZE</a> - 1);
<a name="L292" href="source/net/ipv4/raw.c#L292">292</a> 
<a name="L293" href="source/net/ipv4/raw.c#L293">293</a>         <a href="ident?i=read_lock">read_lock</a>(&amp;<a href="ident?i=raw_v4_hashinfo">raw_v4_hashinfo</a>.<a href="ident?i=lock">lock</a>);
<a name="L294" href="source/net/ipv4/raw.c#L294">294</a>         <a href="ident?i=raw_sk">raw_sk</a> = <a href="ident?i=sk_head">sk_head</a>(&amp;<a href="ident?i=raw_v4_hashinfo">raw_v4_hashinfo</a>.<a href="ident?i=ht">ht</a>[<a href="ident?i=hash">hash</a>]);
<a name="L295" href="source/net/ipv4/raw.c#L295">295</a>         if (<a href="ident?i=raw_sk">raw_sk</a>) {
<a name="L296" href="source/net/ipv4/raw.c#L296">296</a>                 iph = (const struct <a href="ident?i=iphdr">iphdr</a> *)<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=data">data</a>;
<a name="L297" href="source/net/ipv4/raw.c#L297">297</a>                 <a href="ident?i=net">net</a> = <a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=dev">dev</a>);
<a name="L298" href="source/net/ipv4/raw.c#L298">298</a> 
<a name="L299" href="source/net/ipv4/raw.c#L299">299</a>                 while ((<a href="ident?i=raw_sk">raw_sk</a> = <a href="ident?i=__raw_v4_lookup">__raw_v4_lookup</a>(<a href="ident?i=net">net</a>, <a href="ident?i=raw_sk">raw_sk</a>, <a href="ident?i=protocol">protocol</a>,
<a name="L300" href="source/net/ipv4/raw.c#L300">300</a>                                                 iph-&gt;<a href="ident?i=daddr">daddr</a>, iph-&gt;<a href="ident?i=saddr">saddr</a>,
<a name="L301" href="source/net/ipv4/raw.c#L301">301</a>                                                 <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=dev">dev</a>-&gt;ifindex)) != <a href="ident?i=NULL">NULL</a>) {
<a name="L302" href="source/net/ipv4/raw.c#L302">302</a>                         <a href="ident?i=raw_err">raw_err</a>(<a href="ident?i=raw_sk">raw_sk</a>, <a href="ident?i=skb">skb</a>, <a href="ident?i=info">info</a>);
<a name="L303" href="source/net/ipv4/raw.c#L303">303</a>                         <a href="ident?i=raw_sk">raw_sk</a> = <a href="ident?i=sk_next">sk_next</a>(<a href="ident?i=raw_sk">raw_sk</a>);
<a name="L304" href="source/net/ipv4/raw.c#L304">304</a>                         iph = (const struct <a href="ident?i=iphdr">iphdr</a> *)<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=data">data</a>;
<a name="L305" href="source/net/ipv4/raw.c#L305">305</a>                 }
<a name="L306" href="source/net/ipv4/raw.c#L306">306</a>         }
<a name="L307" href="source/net/ipv4/raw.c#L307">307</a>         <a href="ident?i=read_unlock">read_unlock</a>(&amp;<a href="ident?i=raw_v4_hashinfo">raw_v4_hashinfo</a>.<a href="ident?i=lock">lock</a>);
<a name="L308" href="source/net/ipv4/raw.c#L308">308</a> }
<a name="L309" href="source/net/ipv4/raw.c#L309">309</a> 
<a name="L310" href="source/net/ipv4/raw.c#L310">310</a> static int <a href="ident?i=raw_rcv_skb">raw_rcv_skb</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L311" href="source/net/ipv4/raw.c#L311">311</a> {
<a name="L312" href="source/net/ipv4/raw.c#L312">312</a>         <b><i>/* Charge it to the socket. */</i></b>
<a name="L313" href="source/net/ipv4/raw.c#L313">313</a> 
<a name="L314" href="source/net/ipv4/raw.c#L314">314</a>         <a href="ident?i=ipv4_pktinfo_prepare">ipv4_pktinfo_prepare</a>(sk, <a href="ident?i=skb">skb</a>);
<a name="L315" href="source/net/ipv4/raw.c#L315">315</a>         if (<a href="ident?i=sock_queue_rcv_skb">sock_queue_rcv_skb</a>(sk, <a href="ident?i=skb">skb</a>) &lt; 0) {
<a name="L316" href="source/net/ipv4/raw.c#L316">316</a>                 <a href="ident?i=kfree_skb">kfree_skb</a>(<a href="ident?i=skb">skb</a>);
<a name="L317" href="source/net/ipv4/raw.c#L317">317</a>                 return <a href="ident?i=NET_RX_DROP">NET_RX_DROP</a>;
<a name="L318" href="source/net/ipv4/raw.c#L318">318</a>         }
<a name="L319" href="source/net/ipv4/raw.c#L319">319</a> 
<a name="L320" href="source/net/ipv4/raw.c#L320">320</a>         return <a href="ident?i=NET_RX_SUCCESS">NET_RX_SUCCESS</a>;
<a name="L321" href="source/net/ipv4/raw.c#L321">321</a> }
<a name="L322" href="source/net/ipv4/raw.c#L322">322</a> 
<a name="L323" href="source/net/ipv4/raw.c#L323">323</a> int <a href="ident?i=raw_rcv">raw_rcv</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L324" href="source/net/ipv4/raw.c#L324">324</a> {
<a name="L325" href="source/net/ipv4/raw.c#L325">325</a>         if (!<a href="ident?i=xfrm4_policy_check">xfrm4_policy_check</a>(sk, XFRM_POLICY_IN, <a href="ident?i=skb">skb</a>)) {
<a name="L326" href="source/net/ipv4/raw.c#L326">326</a>                 <a href="ident?i=atomic_inc">atomic_inc</a>(&amp;sk-&gt;sk_drops);
<a name="L327" href="source/net/ipv4/raw.c#L327">327</a>                 <a href="ident?i=kfree_skb">kfree_skb</a>(<a href="ident?i=skb">skb</a>);
<a name="L328" href="source/net/ipv4/raw.c#L328">328</a>                 return <a href="ident?i=NET_RX_DROP">NET_RX_DROP</a>;
<a name="L329" href="source/net/ipv4/raw.c#L329">329</a>         }
<a name="L330" href="source/net/ipv4/raw.c#L330">330</a>         <a href="ident?i=nf_reset">nf_reset</a>(<a href="ident?i=skb">skb</a>);
<a name="L331" href="source/net/ipv4/raw.c#L331">331</a> 
<a name="L332" href="source/net/ipv4/raw.c#L332">332</a>         <a href="ident?i=skb_push">skb_push</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=data">data</a> - <a href="ident?i=skb_network_header">skb_network_header</a>(<a href="ident?i=skb">skb</a>));
<a name="L333" href="source/net/ipv4/raw.c#L333">333</a> 
<a name="L334" href="source/net/ipv4/raw.c#L334">334</a>         <a href="ident?i=raw_rcv_skb">raw_rcv_skb</a>(sk, <a href="ident?i=skb">skb</a>);
<a name="L335" href="source/net/ipv4/raw.c#L335">335</a>         return 0;
<a name="L336" href="source/net/ipv4/raw.c#L336">336</a> }
<a name="L337" href="source/net/ipv4/raw.c#L337">337</a> 
<a name="L338" href="source/net/ipv4/raw.c#L338">338</a> static int <a href="ident?i=raw_send_hdrinc">raw_send_hdrinc</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=flowi4">flowi4</a> *fl4,
<a name="L339" href="source/net/ipv4/raw.c#L339">339</a>                            struct <a href="ident?i=msghdr">msghdr</a> *<a href="ident?i=msg">msg</a>, <a href="ident?i=size_t">size_t</a> <a href="ident?i=length">length</a>,
<a name="L340" href="source/net/ipv4/raw.c#L340">340</a>                            struct <a href="ident?i=rtable">rtable</a> **rtp,
<a name="L341" href="source/net/ipv4/raw.c#L341">341</a>                            unsigned int <a href="ident?i=flags">flags</a>)
<a name="L342" href="source/net/ipv4/raw.c#L342">342</a> {
<a name="L343" href="source/net/ipv4/raw.c#L343">343</a>         struct <a href="ident?i=inet_sock">inet_sock</a> *inet = <a href="ident?i=inet_sk">inet_sk</a>(sk);
<a name="L344" href="source/net/ipv4/raw.c#L344">344</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=sock_net">sock_net</a>(sk);
<a name="L345" href="source/net/ipv4/raw.c#L345">345</a>         struct <a href="ident?i=iphdr">iphdr</a> *iph;
<a name="L346" href="source/net/ipv4/raw.c#L346">346</a>         struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>;
<a name="L347" href="source/net/ipv4/raw.c#L347">347</a>         unsigned int iphlen;
<a name="L348" href="source/net/ipv4/raw.c#L348">348</a>         int <a href="ident?i=err">err</a>;
<a name="L349" href="source/net/ipv4/raw.c#L349">349</a>         struct <a href="ident?i=rtable">rtable</a> *<a href="ident?i=rt">rt</a> = *rtp;
<a name="L350" href="source/net/ipv4/raw.c#L350">350</a>         int hlen, tlen;
<a name="L351" href="source/net/ipv4/raw.c#L351">351</a> 
<a name="L352" href="source/net/ipv4/raw.c#L352">352</a>         if (<a href="ident?i=length">length</a> &gt; <a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>.<a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=mtu">mtu</a>) {
<a name="L353" href="source/net/ipv4/raw.c#L353">353</a>                 <a href="ident?i=ip_local_error">ip_local_error</a>(sk, <a href="ident?i=EMSGSIZE">EMSGSIZE</a>, fl4-&gt;<a href="ident?i=daddr">daddr</a>, inet-&gt;<a href="ident?i=inet_dport">inet_dport</a>,
<a name="L354" href="source/net/ipv4/raw.c#L354">354</a>                                <a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>.<a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=mtu">mtu</a>);
<a name="L355" href="source/net/ipv4/raw.c#L355">355</a>                 return -<a href="ident?i=EMSGSIZE">EMSGSIZE</a>;
<a name="L356" href="source/net/ipv4/raw.c#L356">356</a>         }
<a name="L357" href="source/net/ipv4/raw.c#L357">357</a>         if (<a href="ident?i=flags">flags</a>&amp;<a href="ident?i=MSG_PROBE">MSG_PROBE</a>)
<a name="L358" href="source/net/ipv4/raw.c#L358">358</a>                 goto <a href="ident?i=out">out</a>;
<a name="L359" href="source/net/ipv4/raw.c#L359">359</a> 
<a name="L360" href="source/net/ipv4/raw.c#L360">360</a>         hlen = <a href="ident?i=LL_RESERVED_SPACE">LL_RESERVED_SPACE</a>(<a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>.<a href="ident?i=dev">dev</a>);
<a name="L361" href="source/net/ipv4/raw.c#L361">361</a>         tlen = <a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>.<a href="ident?i=dev">dev</a>-&gt;needed_tailroom;
<a name="L362" href="source/net/ipv4/raw.c#L362">362</a>         <a href="ident?i=skb">skb</a> = <a href="ident?i=sock_alloc_send_skb">sock_alloc_send_skb</a>(sk,
<a name="L363" href="source/net/ipv4/raw.c#L363">363</a>                                   <a href="ident?i=length">length</a> + hlen + tlen + 15,
<a name="L364" href="source/net/ipv4/raw.c#L364">364</a>                                   <a href="ident?i=flags">flags</a> &amp; <a href="ident?i=MSG_DONTWAIT">MSG_DONTWAIT</a>, &amp;<a href="ident?i=err">err</a>);
<a name="L365" href="source/net/ipv4/raw.c#L365">365</a>         if (!<a href="ident?i=skb">skb</a>)
<a name="L366" href="source/net/ipv4/raw.c#L366">366</a>                 goto <a href="ident?i=error">error</a>;
<a name="L367" href="source/net/ipv4/raw.c#L367">367</a>         <a href="ident?i=skb_reserve">skb_reserve</a>(<a href="ident?i=skb">skb</a>, hlen);
<a name="L368" href="source/net/ipv4/raw.c#L368">368</a> 
<a name="L369" href="source/net/ipv4/raw.c#L369">369</a>         <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=priority">priority</a> = sk-&gt;sk_priority;
<a name="L370" href="source/net/ipv4/raw.c#L370">370</a>         <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=mark">mark</a> = sk-&gt;sk_mark;
<a name="L371" href="source/net/ipv4/raw.c#L371">371</a>         <a href="ident?i=skb_dst_set">skb_dst_set</a>(<a href="ident?i=skb">skb</a>, &amp;<a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>);
<a name="L372" href="source/net/ipv4/raw.c#L372">372</a>         *rtp = <a href="ident?i=NULL">NULL</a>;
<a name="L373" href="source/net/ipv4/raw.c#L373">373</a> 
<a name="L374" href="source/net/ipv4/raw.c#L374">374</a>         <a href="ident?i=skb_reset_network_header">skb_reset_network_header</a>(<a href="ident?i=skb">skb</a>);
<a name="L375" href="source/net/ipv4/raw.c#L375">375</a>         iph = <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>);
<a name="L376" href="source/net/ipv4/raw.c#L376">376</a>         <a href="ident?i=skb_put">skb_put</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=length">length</a>);
<a name="L377" href="source/net/ipv4/raw.c#L377">377</a> 
<a name="L378" href="source/net/ipv4/raw.c#L378">378</a>         <a href="ident?i=skb">skb</a>-&gt;ip_summed = <a href="ident?i=CHECKSUM_NONE">CHECKSUM_NONE</a>;
<a name="L379" href="source/net/ipv4/raw.c#L379">379</a> 
<a name="L380" href="source/net/ipv4/raw.c#L380">380</a>         <a href="ident?i=sock_tx_timestamp">sock_tx_timestamp</a>(sk, &amp;<a href="ident?i=skb_shinfo">skb_shinfo</a>(<a href="ident?i=skb">skb</a>)-&gt;tx_flags);
<a name="L381" href="source/net/ipv4/raw.c#L381">381</a> 
<a name="L382" href="source/net/ipv4/raw.c#L382">382</a>         <a href="ident?i=skb">skb</a>-&gt;transport_header = <a href="ident?i=skb">skb</a>-&gt;network_header;
<a name="L383" href="source/net/ipv4/raw.c#L383">383</a>         <a href="ident?i=err">err</a> = -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L384" href="source/net/ipv4/raw.c#L384">384</a>         if (<a href="ident?i=memcpy_from_msg">memcpy_from_msg</a>(iph, <a href="ident?i=msg">msg</a>, <a href="ident?i=length">length</a>))
<a name="L385" href="source/net/ipv4/raw.c#L385">385</a>                 goto error_free;
<a name="L386" href="source/net/ipv4/raw.c#L386">386</a> 
<a name="L387" href="source/net/ipv4/raw.c#L387">387</a>         iphlen = iph-&gt;ihl * 4;
<a name="L388" href="source/net/ipv4/raw.c#L388">388</a> 
<a name="L389" href="source/net/ipv4/raw.c#L389">389</a>         <b><i>/*</i></b>
<a name="L390" href="source/net/ipv4/raw.c#L390">390</a> <b><i>         * We don't want to modify the ip header, but we do need to</i></b>
<a name="L391" href="source/net/ipv4/raw.c#L391">391</a> <b><i>         * be sure that it won't cause problems later along the network</i></b>
<a name="L392" href="source/net/ipv4/raw.c#L392">392</a> <b><i>         * stack.  Specifically we want to make sure that iph-&gt;ihl is a</i></b>
<a name="L393" href="source/net/ipv4/raw.c#L393">393</a> <b><i>         * sane value.  If ihl points beyond the length of the buffer passed</i></b>
<a name="L394" href="source/net/ipv4/raw.c#L394">394</a> <b><i>         * in, reject the frame as invalid</i></b>
<a name="L395" href="source/net/ipv4/raw.c#L395">395</a> <b><i>         */</i></b>
<a name="L396" href="source/net/ipv4/raw.c#L396">396</a>         <a href="ident?i=err">err</a> = -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L397" href="source/net/ipv4/raw.c#L397">397</a>         if (iphlen &gt; <a href="ident?i=length">length</a>)
<a name="L398" href="source/net/ipv4/raw.c#L398">398</a>                 goto error_free;
<a name="L399" href="source/net/ipv4/raw.c#L399">399</a> 
<a name="L400" href="source/net/ipv4/raw.c#L400">400</a>         if (iphlen &gt;= sizeof(*iph)) {
<a name="L401" href="source/net/ipv4/raw.c#L401">401</a>                 if (!iph-&gt;<a href="ident?i=saddr">saddr</a>)
<a name="L402" href="source/net/ipv4/raw.c#L402">402</a>                         iph-&gt;<a href="ident?i=saddr">saddr</a> = fl4-&gt;<a href="ident?i=saddr">saddr</a>;
<a name="L403" href="source/net/ipv4/raw.c#L403">403</a>                 iph-&gt;<a href="ident?i=check">check</a>   = 0;
<a name="L404" href="source/net/ipv4/raw.c#L404">404</a>                 iph-&gt;tot_len = <a href="ident?i=htons">htons</a>(<a href="ident?i=length">length</a>);
<a name="L405" href="source/net/ipv4/raw.c#L405">405</a>                 if (!iph-&gt;<a href="ident?i=id">id</a>)
<a name="L406" href="source/net/ipv4/raw.c#L406">406</a>                         <a href="ident?i=ip_select_ident">ip_select_ident</a>(<a href="ident?i=net">net</a>, <a href="ident?i=skb">skb</a>, <a href="ident?i=NULL">NULL</a>);
<a name="L407" href="source/net/ipv4/raw.c#L407">407</a> 
<a name="L408" href="source/net/ipv4/raw.c#L408">408</a>                 iph-&gt;<a href="ident?i=check">check</a> = <a href="ident?i=ip_fast_csum">ip_fast_csum</a>((unsigned char *)iph, iph-&gt;ihl);
<a name="L409" href="source/net/ipv4/raw.c#L409">409</a>         }
<a name="L410" href="source/net/ipv4/raw.c#L410">410</a>         if (iph-&gt;<a href="ident?i=protocol">protocol</a> == <a href="ident?i=IPPROTO_ICMP">IPPROTO_ICMP</a>)
<a name="L411" href="source/net/ipv4/raw.c#L411">411</a>                 <a href="ident?i=icmp_out_count">icmp_out_count</a>(<a href="ident?i=net">net</a>, ((struct <a href="ident?i=icmphdr">icmphdr</a> *)
<a name="L412" href="source/net/ipv4/raw.c#L412">412</a>                         <a href="ident?i=skb_transport_header">skb_transport_header</a>(<a href="ident?i=skb">skb</a>))-&gt;<a href="ident?i=type">type</a>);
<a name="L413" href="source/net/ipv4/raw.c#L413">413</a> 
<a name="L414" href="source/net/ipv4/raw.c#L414">414</a>         <a href="ident?i=err">err</a> = <a href="ident?i=NF_HOOK">NF_HOOK</a>(NFPROTO_IPV4, NF_INET_LOCAL_OUT, sk, <a href="ident?i=skb">skb</a>,
<a name="L415" href="source/net/ipv4/raw.c#L415">415</a>                       <a href="ident?i=NULL">NULL</a>, <a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>.<a href="ident?i=dev">dev</a>, <a href="ident?i=dst_output_sk">dst_output_sk</a>);
<a name="L416" href="source/net/ipv4/raw.c#L416">416</a>         if (<a href="ident?i=err">err</a> &gt; 0)
<a name="L417" href="source/net/ipv4/raw.c#L417">417</a>                 <a href="ident?i=err">err</a> = <a href="ident?i=net_xmit_errno">net_xmit_errno</a>(<a href="ident?i=err">err</a>);
<a name="L418" href="source/net/ipv4/raw.c#L418">418</a>         if (<a href="ident?i=err">err</a>)
<a name="L419" href="source/net/ipv4/raw.c#L419">419</a>                 goto <a href="ident?i=error">error</a>;
<a name="L420" href="source/net/ipv4/raw.c#L420">420</a> <a href="ident?i=out">out</a>:
<a name="L421" href="source/net/ipv4/raw.c#L421">421</a>         return 0;
<a name="L422" href="source/net/ipv4/raw.c#L422">422</a> 
<a name="L423" href="source/net/ipv4/raw.c#L423">423</a> error_free:
<a name="L424" href="source/net/ipv4/raw.c#L424">424</a>         <a href="ident?i=kfree_skb">kfree_skb</a>(<a href="ident?i=skb">skb</a>);
<a name="L425" href="source/net/ipv4/raw.c#L425">425</a> <a href="ident?i=error">error</a>:
<a name="L426" href="source/net/ipv4/raw.c#L426">426</a>         <a href="ident?i=IP_INC_STATS">IP_INC_STATS</a>(<a href="ident?i=net">net</a>, IPSTATS_MIB_OUTDISCARDS);
<a name="L427" href="source/net/ipv4/raw.c#L427">427</a>         if (<a href="ident?i=err">err</a> == -<a href="ident?i=ENOBUFS">ENOBUFS</a> &amp;&amp; !inet-&gt;recverr)
<a name="L428" href="source/net/ipv4/raw.c#L428">428</a>                 <a href="ident?i=err">err</a> = 0;
<a name="L429" href="source/net/ipv4/raw.c#L429">429</a>         return <a href="ident?i=err">err</a>;
<a name="L430" href="source/net/ipv4/raw.c#L430">430</a> }
<a name="L431" href="source/net/ipv4/raw.c#L431">431</a> 
<a name="L432" href="source/net/ipv4/raw.c#L432">432</a> static int <a href="ident?i=raw_probe_proto_opt">raw_probe_proto_opt</a>(struct <a href="ident?i=raw_frag_vec">raw_frag_vec</a> *rfv, struct <a href="ident?i=flowi4">flowi4</a> *fl4)
<a name="L433" href="source/net/ipv4/raw.c#L433">433</a> {
<a name="L434" href="source/net/ipv4/raw.c#L434">434</a>         int <a href="ident?i=err">err</a>;
<a name="L435" href="source/net/ipv4/raw.c#L435">435</a> 
<a name="L436" href="source/net/ipv4/raw.c#L436">436</a>         if (fl4-&gt;<a href="ident?i=flowi4_proto">flowi4_proto</a> != <a href="ident?i=IPPROTO_ICMP">IPPROTO_ICMP</a>)
<a name="L437" href="source/net/ipv4/raw.c#L437">437</a>                 return 0;
<a name="L438" href="source/net/ipv4/raw.c#L438">438</a> 
<a name="L439" href="source/net/ipv4/raw.c#L439">439</a>         <b><i>/* We only need the first two bytes. */</i></b>
<a name="L440" href="source/net/ipv4/raw.c#L440">440</a>         rfv-&gt;hlen = 2;
<a name="L441" href="source/net/ipv4/raw.c#L441">441</a> 
<a name="L442" href="source/net/ipv4/raw.c#L442">442</a>         <a href="ident?i=err">err</a> = <a href="ident?i=memcpy_from_msg">memcpy_from_msg</a>(rfv-&gt;<a href="ident?i=hdr">hdr</a>.<a href="ident?i=c">c</a>, rfv-&gt;<a href="ident?i=msg">msg</a>, rfv-&gt;hlen);
<a name="L443" href="source/net/ipv4/raw.c#L443">443</a>         if (<a href="ident?i=err">err</a>)
<a name="L444" href="source/net/ipv4/raw.c#L444">444</a>                 return <a href="ident?i=err">err</a>;
<a name="L445" href="source/net/ipv4/raw.c#L445">445</a> 
<a name="L446" href="source/net/ipv4/raw.c#L446">446</a>         fl4-&gt;<a href="ident?i=fl4_icmp_type">fl4_icmp_type</a> = rfv-&gt;<a href="ident?i=hdr">hdr</a>.icmph.<a href="ident?i=type">type</a>;
<a name="L447" href="source/net/ipv4/raw.c#L447">447</a>         fl4-&gt;<a href="ident?i=fl4_icmp_code">fl4_icmp_code</a> = rfv-&gt;<a href="ident?i=hdr">hdr</a>.icmph.<a href="ident?i=code">code</a>;
<a name="L448" href="source/net/ipv4/raw.c#L448">448</a> 
<a name="L449" href="source/net/ipv4/raw.c#L449">449</a>         return 0;
<a name="L450" href="source/net/ipv4/raw.c#L450">450</a> }
<a name="L451" href="source/net/ipv4/raw.c#L451">451</a> 
<a name="L452" href="source/net/ipv4/raw.c#L452">452</a> static int <a href="ident?i=raw_getfrag">raw_getfrag</a>(void *from, char *to, int <a href="ident?i=offset">offset</a>, int <a href="ident?i=len">len</a>, int odd,
<a name="L453" href="source/net/ipv4/raw.c#L453">453</a>                        struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L454" href="source/net/ipv4/raw.c#L454">454</a> {
<a name="L455" href="source/net/ipv4/raw.c#L455">455</a>         struct <a href="ident?i=raw_frag_vec">raw_frag_vec</a> *rfv = from;
<a name="L456" href="source/net/ipv4/raw.c#L456">456</a> 
<a name="L457" href="source/net/ipv4/raw.c#L457">457</a>         if (<a href="ident?i=offset">offset</a> &lt; rfv-&gt;hlen) {
<a name="L458" href="source/net/ipv4/raw.c#L458">458</a>                 int <a href="ident?i=copy">copy</a> = <a href="ident?i=min">min</a>(rfv-&gt;hlen - <a href="ident?i=offset">offset</a>, <a href="ident?i=len">len</a>);
<a name="L459" href="source/net/ipv4/raw.c#L459">459</a> 
<a name="L460" href="source/net/ipv4/raw.c#L460">460</a>                 if (<a href="ident?i=skb">skb</a>-&gt;ip_summed == <a href="ident?i=CHECKSUM_PARTIAL">CHECKSUM_PARTIAL</a>)
<a name="L461" href="source/net/ipv4/raw.c#L461">461</a>                         <a href="ident?i=memcpy">memcpy</a>(to, rfv-&gt;<a href="ident?i=hdr">hdr</a>.<a href="ident?i=c">c</a> + <a href="ident?i=offset">offset</a>, <a href="ident?i=copy">copy</a>);
<a name="L462" href="source/net/ipv4/raw.c#L462">462</a>                 else
<a name="L463" href="source/net/ipv4/raw.c#L463">463</a>                         <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=csum">csum</a> = <a href="ident?i=csum_block_add">csum_block_add</a>(
<a name="L464" href="source/net/ipv4/raw.c#L464">464</a>                                 <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=csum">csum</a>,
<a name="L465" href="source/net/ipv4/raw.c#L465">465</a>                                 <a href="ident?i=csum_partial_copy_nocheck">csum_partial_copy_nocheck</a>(rfv-&gt;<a href="ident?i=hdr">hdr</a>.<a href="ident?i=c">c</a> + <a href="ident?i=offset">offset</a>,
<a name="L466" href="source/net/ipv4/raw.c#L466">466</a>                                                           to, <a href="ident?i=copy">copy</a>, 0),
<a name="L467" href="source/net/ipv4/raw.c#L467">467</a>                                 odd);
<a name="L468" href="source/net/ipv4/raw.c#L468">468</a> 
<a name="L469" href="source/net/ipv4/raw.c#L469">469</a>                 odd = 0;
<a name="L470" href="source/net/ipv4/raw.c#L470">470</a>                 <a href="ident?i=offset">offset</a> += <a href="ident?i=copy">copy</a>;
<a name="L471" href="source/net/ipv4/raw.c#L471">471</a>                 to += <a href="ident?i=copy">copy</a>;
<a name="L472" href="source/net/ipv4/raw.c#L472">472</a>                 <a href="ident?i=len">len</a> -= <a href="ident?i=copy">copy</a>;
<a name="L473" href="source/net/ipv4/raw.c#L473">473</a> 
<a name="L474" href="source/net/ipv4/raw.c#L474">474</a>                 if (!<a href="ident?i=len">len</a>)
<a name="L475" href="source/net/ipv4/raw.c#L475">475</a>                         return 0;
<a name="L476" href="source/net/ipv4/raw.c#L476">476</a>         }
<a name="L477" href="source/net/ipv4/raw.c#L477">477</a> 
<a name="L478" href="source/net/ipv4/raw.c#L478">478</a>         <a href="ident?i=offset">offset</a> -= rfv-&gt;hlen;
<a name="L479" href="source/net/ipv4/raw.c#L479">479</a> 
<a name="L480" href="source/net/ipv4/raw.c#L480">480</a>         return <a href="ident?i=ip_generic_getfrag">ip_generic_getfrag</a>(rfv-&gt;<a href="ident?i=msg">msg</a>, to, <a href="ident?i=offset">offset</a>, <a href="ident?i=len">len</a>, odd, <a href="ident?i=skb">skb</a>);
<a name="L481" href="source/net/ipv4/raw.c#L481">481</a> }
<a name="L482" href="source/net/ipv4/raw.c#L482">482</a> 
<a name="L483" href="source/net/ipv4/raw.c#L483">483</a> static int <a href="ident?i=raw_sendmsg">raw_sendmsg</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=msghdr">msghdr</a> *<a href="ident?i=msg">msg</a>, <a href="ident?i=size_t">size_t</a> <a href="ident?i=len">len</a>)
<a name="L484" href="source/net/ipv4/raw.c#L484">484</a> {
<a name="L485" href="source/net/ipv4/raw.c#L485">485</a>         struct <a href="ident?i=inet_sock">inet_sock</a> *inet = <a href="ident?i=inet_sk">inet_sk</a>(sk);
<a name="L486" href="source/net/ipv4/raw.c#L486">486</a>         struct <a href="ident?i=ipcm_cookie">ipcm_cookie</a> ipc;
<a name="L487" href="source/net/ipv4/raw.c#L487">487</a>         struct <a href="ident?i=rtable">rtable</a> *<a href="ident?i=rt">rt</a> = <a href="ident?i=NULL">NULL</a>;
<a name="L488" href="source/net/ipv4/raw.c#L488">488</a>         struct <a href="ident?i=flowi4">flowi4</a> fl4;
<a name="L489" href="source/net/ipv4/raw.c#L489">489</a>         int <a href="ident?i=free">free</a> = 0;
<a name="L490" href="source/net/ipv4/raw.c#L490">490</a>         <a href="ident?i=__be32">__be32</a> <a href="ident?i=daddr">daddr</a>;
<a name="L491" href="source/net/ipv4/raw.c#L491">491</a>         <a href="ident?i=__be32">__be32</a> <a href="ident?i=saddr">saddr</a>;
<a name="L492" href="source/net/ipv4/raw.c#L492">492</a>         <a href="ident?i=u8">u8</a>  tos;
<a name="L493" href="source/net/ipv4/raw.c#L493">493</a>         int <a href="ident?i=err">err</a>;
<a name="L494" href="source/net/ipv4/raw.c#L494">494</a>         struct <a href="ident?i=ip_options_data">ip_options_data</a> opt_copy;
<a name="L495" href="source/net/ipv4/raw.c#L495">495</a>         struct <a href="ident?i=raw_frag_vec">raw_frag_vec</a> rfv;
<a name="L496" href="source/net/ipv4/raw.c#L496">496</a> 
<a name="L497" href="source/net/ipv4/raw.c#L497">497</a>         <a href="ident?i=err">err</a> = -<a href="ident?i=EMSGSIZE">EMSGSIZE</a>;
<a name="L498" href="source/net/ipv4/raw.c#L498">498</a>         if (<a href="ident?i=len">len</a> &gt; 0xFFFF)
<a name="L499" href="source/net/ipv4/raw.c#L499">499</a>                 goto <a href="ident?i=out">out</a>;
<a name="L500" href="source/net/ipv4/raw.c#L500">500</a> 
<a name="L501" href="source/net/ipv4/raw.c#L501">501</a>         <b><i>/*</i></b>
<a name="L502" href="source/net/ipv4/raw.c#L502">502</a> <b><i>         *      Check the flags.</i></b>
<a name="L503" href="source/net/ipv4/raw.c#L503">503</a> <b><i>         */</i></b>
<a name="L504" href="source/net/ipv4/raw.c#L504">504</a> 
<a name="L505" href="source/net/ipv4/raw.c#L505">505</a>         <a href="ident?i=err">err</a> = -<a href="ident?i=EOPNOTSUPP">EOPNOTSUPP</a>;
<a name="L506" href="source/net/ipv4/raw.c#L506">506</a>         if (<a href="ident?i=msg">msg</a>-&gt;msg_flags &amp; <a href="ident?i=MSG_OOB">MSG_OOB</a>)   <b><i>/* Mirror BSD error message */</i></b>
<a name="L507" href="source/net/ipv4/raw.c#L507">507</a>                 goto <a href="ident?i=out">out</a>;               <b><i>/* compatibility */</i></b>
<a name="L508" href="source/net/ipv4/raw.c#L508">508</a> 
<a name="L509" href="source/net/ipv4/raw.c#L509">509</a>         <b><i>/*</i></b>
<a name="L510" href="source/net/ipv4/raw.c#L510">510</a> <b><i>         *      Get and verify the address.</i></b>
<a name="L511" href="source/net/ipv4/raw.c#L511">511</a> <b><i>         */</i></b>
<a name="L512" href="source/net/ipv4/raw.c#L512">512</a> 
<a name="L513" href="source/net/ipv4/raw.c#L513">513</a>         if (<a href="ident?i=msg">msg</a>-&gt;msg_namelen) {
<a name="L514" href="source/net/ipv4/raw.c#L514">514</a>                 <a href="ident?i=DECLARE_SOCKADDR">DECLARE_SOCKADDR</a>(struct <a href="ident?i=sockaddr_in">sockaddr_in</a> *, usin, <a href="ident?i=msg">msg</a>-&gt;msg_name);
<a name="L515" href="source/net/ipv4/raw.c#L515">515</a>                 <a href="ident?i=err">err</a> = -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L516" href="source/net/ipv4/raw.c#L516">516</a>                 if (<a href="ident?i=msg">msg</a>-&gt;msg_namelen &lt; sizeof(*usin))
<a name="L517" href="source/net/ipv4/raw.c#L517">517</a>                         goto <a href="ident?i=out">out</a>;
<a name="L518" href="source/net/ipv4/raw.c#L518">518</a>                 if (usin-&gt;sin_family != <a href="ident?i=AF_INET">AF_INET</a>) {
<a name="L519" href="source/net/ipv4/raw.c#L519">519</a>                         <a href="ident?i=pr_info_once">pr_info_once</a>(<i>"%s: %s forgot to set AF_INET. Fix it!\n"</i>,
<a name="L520" href="source/net/ipv4/raw.c#L520">520</a>                                      <a href="ident?i=__func__">__func__</a>, <a href="ident?i=current">current</a>-&gt;<a href="ident?i=comm">comm</a>);
<a name="L521" href="source/net/ipv4/raw.c#L521">521</a>                         <a href="ident?i=err">err</a> = -<a href="ident?i=EAFNOSUPPORT">EAFNOSUPPORT</a>;
<a name="L522" href="source/net/ipv4/raw.c#L522">522</a>                         if (usin-&gt;sin_family)
<a name="L523" href="source/net/ipv4/raw.c#L523">523</a>                                 goto <a href="ident?i=out">out</a>;
<a name="L524" href="source/net/ipv4/raw.c#L524">524</a>                 }
<a name="L525" href="source/net/ipv4/raw.c#L525">525</a>                 <a href="ident?i=daddr">daddr</a> = usin-&gt;sin_addr.s_addr;
<a name="L526" href="source/net/ipv4/raw.c#L526">526</a>                 <b><i>/* ANK: I did not forget to get protocol from port field.</i></b>
<a name="L527" href="source/net/ipv4/raw.c#L527">527</a> <b><i>                 * I just do not know, who uses this weirdness.</i></b>
<a name="L528" href="source/net/ipv4/raw.c#L528">528</a> <b><i>                 * IP_HDRINCL is much more convenient.</i></b>
<a name="L529" href="source/net/ipv4/raw.c#L529">529</a> <b><i>                 */</i></b>
<a name="L530" href="source/net/ipv4/raw.c#L530">530</a>         } else {
<a name="L531" href="source/net/ipv4/raw.c#L531">531</a>                 <a href="ident?i=err">err</a> = -<a href="ident?i=EDESTADDRREQ">EDESTADDRREQ</a>;
<a name="L532" href="source/net/ipv4/raw.c#L532">532</a>                 if (sk-&gt;<a href="ident?i=sk_state">sk_state</a> != TCP_ESTABLISHED)
<a name="L533" href="source/net/ipv4/raw.c#L533">533</a>                         goto <a href="ident?i=out">out</a>;
<a name="L534" href="source/net/ipv4/raw.c#L534">534</a>                 <a href="ident?i=daddr">daddr</a> = inet-&gt;<a href="ident?i=inet_daddr">inet_daddr</a>;
<a name="L535" href="source/net/ipv4/raw.c#L535">535</a>         }
<a name="L536" href="source/net/ipv4/raw.c#L536">536</a> 
<a name="L537" href="source/net/ipv4/raw.c#L537">537</a>         ipc.<a href="ident?i=addr">addr</a> = inet-&gt;inet_saddr;
<a name="L538" href="source/net/ipv4/raw.c#L538">538</a>         ipc.opt = <a href="ident?i=NULL">NULL</a>;
<a name="L539" href="source/net/ipv4/raw.c#L539">539</a>         ipc.tx_flags = 0;
<a name="L540" href="source/net/ipv4/raw.c#L540">540</a>         ipc.<a href="ident?i=ttl">ttl</a> = 0;
<a name="L541" href="source/net/ipv4/raw.c#L541">541</a>         ipc.tos = -1;
<a name="L542" href="source/net/ipv4/raw.c#L542">542</a>         ipc.oif = sk-&gt;<a href="ident?i=sk_bound_dev_if">sk_bound_dev_if</a>;
<a name="L543" href="source/net/ipv4/raw.c#L543">543</a> 
<a name="L544" href="source/net/ipv4/raw.c#L544">544</a>         if (<a href="ident?i=msg">msg</a>-&gt;msg_controllen) {
<a name="L545" href="source/net/ipv4/raw.c#L545">545</a>                 <a href="ident?i=err">err</a> = <a href="ident?i=ip_cmsg_send">ip_cmsg_send</a>(<a href="ident?i=sock_net">sock_net</a>(sk), <a href="ident?i=msg">msg</a>, &amp;ipc, <a href="ident?i=false">false</a>);
<a name="L546" href="source/net/ipv4/raw.c#L546">546</a>                 if (<a href="ident?i=err">err</a>)
<a name="L547" href="source/net/ipv4/raw.c#L547">547</a>                         goto <a href="ident?i=out">out</a>;
<a name="L548" href="source/net/ipv4/raw.c#L548">548</a>                 if (ipc.opt)
<a name="L549" href="source/net/ipv4/raw.c#L549">549</a>                         <a href="ident?i=free">free</a> = 1;
<a name="L550" href="source/net/ipv4/raw.c#L550">550</a>         }
<a name="L551" href="source/net/ipv4/raw.c#L551">551</a> 
<a name="L552" href="source/net/ipv4/raw.c#L552">552</a>         <a href="ident?i=saddr">saddr</a> = ipc.<a href="ident?i=addr">addr</a>;
<a name="L553" href="source/net/ipv4/raw.c#L553">553</a>         ipc.<a href="ident?i=addr">addr</a> = <a href="ident?i=daddr">daddr</a>;
<a name="L554" href="source/net/ipv4/raw.c#L554">554</a> 
<a name="L555" href="source/net/ipv4/raw.c#L555">555</a>         if (!ipc.opt) {
<a name="L556" href="source/net/ipv4/raw.c#L556">556</a>                 struct <a href="ident?i=ip_options_rcu">ip_options_rcu</a> *inet_opt;
<a name="L557" href="source/net/ipv4/raw.c#L557">557</a> 
<a name="L558" href="source/net/ipv4/raw.c#L558">558</a>                 <a href="ident?i=rcu_read_lock">rcu_read_lock</a>();
<a name="L559" href="source/net/ipv4/raw.c#L559">559</a>                 inet_opt = <a href="ident?i=rcu_dereference">rcu_dereference</a>(inet-&gt;inet_opt);
<a name="L560" href="source/net/ipv4/raw.c#L560">560</a>                 if (inet_opt) {
<a name="L561" href="source/net/ipv4/raw.c#L561">561</a>                         <a href="ident?i=memcpy">memcpy</a>(&amp;opt_copy, inet_opt,
<a name="L562" href="source/net/ipv4/raw.c#L562">562</a>                                sizeof(*inet_opt) + inet_opt-&gt;opt.<a href="ident?i=optlen">optlen</a>);
<a name="L563" href="source/net/ipv4/raw.c#L563">563</a>                         ipc.opt = &amp;opt_copy.opt;
<a name="L564" href="source/net/ipv4/raw.c#L564">564</a>                 }
<a name="L565" href="source/net/ipv4/raw.c#L565">565</a>                 <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L566" href="source/net/ipv4/raw.c#L566">566</a>         }
<a name="L567" href="source/net/ipv4/raw.c#L567">567</a> 
<a name="L568" href="source/net/ipv4/raw.c#L568">568</a>         if (ipc.opt) {
<a name="L569" href="source/net/ipv4/raw.c#L569">569</a>                 <a href="ident?i=err">err</a> = -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L570" href="source/net/ipv4/raw.c#L570">570</a>                 <b><i>/* Linux does not mangle headers on raw sockets,</i></b>
<a name="L571" href="source/net/ipv4/raw.c#L571">571</a> <b><i>                 * so that IP options + IP_HDRINCL is non-sense.</i></b>
<a name="L572" href="source/net/ipv4/raw.c#L572">572</a> <b><i>                 */</i></b>
<a name="L573" href="source/net/ipv4/raw.c#L573">573</a>                 if (inet-&gt;hdrincl)
<a name="L574" href="source/net/ipv4/raw.c#L574">574</a>                         goto <a href="ident?i=done">done</a>;
<a name="L575" href="source/net/ipv4/raw.c#L575">575</a>                 if (ipc.opt-&gt;opt.<a href="ident?i=srr">srr</a>) {
<a name="L576" href="source/net/ipv4/raw.c#L576">576</a>                         if (!<a href="ident?i=daddr">daddr</a>)
<a name="L577" href="source/net/ipv4/raw.c#L577">577</a>                                 goto <a href="ident?i=done">done</a>;
<a name="L578" href="source/net/ipv4/raw.c#L578">578</a>                         <a href="ident?i=daddr">daddr</a> = ipc.opt-&gt;opt.faddr;
<a name="L579" href="source/net/ipv4/raw.c#L579">579</a>                 }
<a name="L580" href="source/net/ipv4/raw.c#L580">580</a>         }
<a name="L581" href="source/net/ipv4/raw.c#L581">581</a>         tos = <a href="ident?i=get_rtconn_flags">get_rtconn_flags</a>(&amp;ipc, sk);
<a name="L582" href="source/net/ipv4/raw.c#L582">582</a>         if (<a href="ident?i=msg">msg</a>-&gt;msg_flags &amp; <a href="ident?i=MSG_DONTROUTE">MSG_DONTROUTE</a>)
<a name="L583" href="source/net/ipv4/raw.c#L583">583</a>                 tos |= <a href="ident?i=RTO_ONLINK">RTO_ONLINK</a>;
<a name="L584" href="source/net/ipv4/raw.c#L584">584</a> 
<a name="L585" href="source/net/ipv4/raw.c#L585">585</a>         if (<a href="ident?i=ipv4_is_multicast">ipv4_is_multicast</a>(<a href="ident?i=daddr">daddr</a>)) {
<a name="L586" href="source/net/ipv4/raw.c#L586">586</a>                 if (!ipc.oif)
<a name="L587" href="source/net/ipv4/raw.c#L587">587</a>                         ipc.oif = inet-&gt;mc_index;
<a name="L588" href="source/net/ipv4/raw.c#L588">588</a>                 if (!<a href="ident?i=saddr">saddr</a>)
<a name="L589" href="source/net/ipv4/raw.c#L589">589</a>                         <a href="ident?i=saddr">saddr</a> = inet-&gt;mc_addr;
<a name="L590" href="source/net/ipv4/raw.c#L590">590</a>         } else if (!ipc.oif)
<a name="L591" href="source/net/ipv4/raw.c#L591">591</a>                 ipc.oif = inet-&gt;uc_index;
<a name="L592" href="source/net/ipv4/raw.c#L592">592</a> 
<a name="L593" href="source/net/ipv4/raw.c#L593">593</a>         <a href="ident?i=flowi4_init_output">flowi4_init_output</a>(&amp;fl4, ipc.oif, sk-&gt;sk_mark, tos,
<a name="L594" href="source/net/ipv4/raw.c#L594">594</a>                            RT_SCOPE_UNIVERSE,
<a name="L595" href="source/net/ipv4/raw.c#L595">595</a>                            inet-&gt;hdrincl ? <a href="ident?i=IPPROTO_RAW">IPPROTO_RAW</a> : sk-&gt;sk_protocol,
<a name="L596" href="source/net/ipv4/raw.c#L596">596</a>                            <a href="ident?i=inet_sk_flowi_flags">inet_sk_flowi_flags</a>(sk) |
<a name="L597" href="source/net/ipv4/raw.c#L597">597</a>                             (inet-&gt;hdrincl ? <a href="ident?i=FLOWI_FLAG_KNOWN_NH">FLOWI_FLAG_KNOWN_NH</a> : 0),
<a name="L598" href="source/net/ipv4/raw.c#L598">598</a>                            <a href="ident?i=daddr">daddr</a>, <a href="ident?i=saddr">saddr</a>, 0, 0);
<a name="L599" href="source/net/ipv4/raw.c#L599">599</a> 
<a name="L600" href="source/net/ipv4/raw.c#L600">600</a>         if (!inet-&gt;hdrincl) {
<a name="L601" href="source/net/ipv4/raw.c#L601">601</a>                 rfv.<a href="ident?i=msg">msg</a> = <a href="ident?i=msg">msg</a>;
<a name="L602" href="source/net/ipv4/raw.c#L602">602</a>                 rfv.hlen = 0;
<a name="L603" href="source/net/ipv4/raw.c#L603">603</a> 
<a name="L604" href="source/net/ipv4/raw.c#L604">604</a>                 <a href="ident?i=err">err</a> = <a href="ident?i=raw_probe_proto_opt">raw_probe_proto_opt</a>(&amp;rfv, &amp;fl4);
<a name="L605" href="source/net/ipv4/raw.c#L605">605</a>                 if (<a href="ident?i=err">err</a>)
<a name="L606" href="source/net/ipv4/raw.c#L606">606</a>                         goto <a href="ident?i=done">done</a>;
<a name="L607" href="source/net/ipv4/raw.c#L607">607</a>         }
<a name="L608" href="source/net/ipv4/raw.c#L608">608</a> 
<a name="L609" href="source/net/ipv4/raw.c#L609">609</a>         <a href="ident?i=security_sk_classify_flow">security_sk_classify_flow</a>(sk, <a href="ident?i=flowi4_to_flowi">flowi4_to_flowi</a>(&amp;fl4));
<a name="L610" href="source/net/ipv4/raw.c#L610">610</a>         <a href="ident?i=rt">rt</a> = <a href="ident?i=ip_route_output_flow">ip_route_output_flow</a>(<a href="ident?i=sock_net">sock_net</a>(sk), &amp;fl4, sk);
<a name="L611" href="source/net/ipv4/raw.c#L611">611</a>         if (<a href="ident?i=IS_ERR">IS_ERR</a>(<a href="ident?i=rt">rt</a>)) {
<a name="L612" href="source/net/ipv4/raw.c#L612">612</a>                 <a href="ident?i=err">err</a> = <a href="ident?i=PTR_ERR">PTR_ERR</a>(<a href="ident?i=rt">rt</a>);
<a name="L613" href="source/net/ipv4/raw.c#L613">613</a>                 <a href="ident?i=rt">rt</a> = <a href="ident?i=NULL">NULL</a>;
<a name="L614" href="source/net/ipv4/raw.c#L614">614</a>                 goto <a href="ident?i=done">done</a>;
<a name="L615" href="source/net/ipv4/raw.c#L615">615</a>         }
<a name="L616" href="source/net/ipv4/raw.c#L616">616</a> 
<a name="L617" href="source/net/ipv4/raw.c#L617">617</a>         <a href="ident?i=err">err</a> = -<a href="ident?i=EACCES">EACCES</a>;
<a name="L618" href="source/net/ipv4/raw.c#L618">618</a>         if (<a href="ident?i=rt">rt</a>-&gt;rt_flags &amp; <a href="ident?i=RTCF_BROADCAST">RTCF_BROADCAST</a> &amp;&amp; !<a href="ident?i=sock_flag">sock_flag</a>(sk, SOCK_BROADCAST))
<a name="L619" href="source/net/ipv4/raw.c#L619">619</a>                 goto <a href="ident?i=done">done</a>;
<a name="L620" href="source/net/ipv4/raw.c#L620">620</a> 
<a name="L621" href="source/net/ipv4/raw.c#L621">621</a>         if (<a href="ident?i=msg">msg</a>-&gt;msg_flags &amp; <a href="ident?i=MSG_CONFIRM">MSG_CONFIRM</a>)
<a name="L622" href="source/net/ipv4/raw.c#L622">622</a>                 goto do_confirm;
<a name="L623" href="source/net/ipv4/raw.c#L623">623</a> back_from_confirm:
<a name="L624" href="source/net/ipv4/raw.c#L624">624</a> 
<a name="L625" href="source/net/ipv4/raw.c#L625">625</a>         if (inet-&gt;hdrincl)
<a name="L626" href="source/net/ipv4/raw.c#L626">626</a>                 <a href="ident?i=err">err</a> = <a href="ident?i=raw_send_hdrinc">raw_send_hdrinc</a>(sk, &amp;fl4, <a href="ident?i=msg">msg</a>, <a href="ident?i=len">len</a>,
<a name="L627" href="source/net/ipv4/raw.c#L627">627</a>                                       &amp;<a href="ident?i=rt">rt</a>, <a href="ident?i=msg">msg</a>-&gt;msg_flags);
<a name="L628" href="source/net/ipv4/raw.c#L628">628</a> 
<a name="L629" href="source/net/ipv4/raw.c#L629">629</a>          else {
<a name="L630" href="source/net/ipv4/raw.c#L630">630</a>                 <a href="ident?i=sock_tx_timestamp">sock_tx_timestamp</a>(sk, &amp;ipc.tx_flags);
<a name="L631" href="source/net/ipv4/raw.c#L631">631</a> 
<a name="L632" href="source/net/ipv4/raw.c#L632">632</a>                 if (!ipc.<a href="ident?i=addr">addr</a>)
<a name="L633" href="source/net/ipv4/raw.c#L633">633</a>                         ipc.<a href="ident?i=addr">addr</a> = fl4.<a href="ident?i=daddr">daddr</a>;
<a name="L634" href="source/net/ipv4/raw.c#L634">634</a>                 <a href="ident?i=lock_sock">lock_sock</a>(sk);
<a name="L635" href="source/net/ipv4/raw.c#L635">635</a>                 <a href="ident?i=err">err</a> = <a href="ident?i=ip_append_data">ip_append_data</a>(sk, &amp;fl4, <a href="ident?i=raw_getfrag">raw_getfrag</a>,
<a name="L636" href="source/net/ipv4/raw.c#L636">636</a>                                      &amp;rfv, <a href="ident?i=len">len</a>, 0,
<a name="L637" href="source/net/ipv4/raw.c#L637">637</a>                                      &amp;ipc, &amp;<a href="ident?i=rt">rt</a>, <a href="ident?i=msg">msg</a>-&gt;msg_flags);
<a name="L638" href="source/net/ipv4/raw.c#L638">638</a>                 if (<a href="ident?i=err">err</a>)
<a name="L639" href="source/net/ipv4/raw.c#L639">639</a>                         <a href="ident?i=ip_flush_pending_frames">ip_flush_pending_frames</a>(sk);
<a name="L640" href="source/net/ipv4/raw.c#L640">640</a>                 else if (!(<a href="ident?i=msg">msg</a>-&gt;msg_flags &amp; <a href="ident?i=MSG_MORE">MSG_MORE</a>)) {
<a name="L641" href="source/net/ipv4/raw.c#L641">641</a>                         <a href="ident?i=err">err</a> = <a href="ident?i=ip_push_pending_frames">ip_push_pending_frames</a>(sk, &amp;fl4);
<a name="L642" href="source/net/ipv4/raw.c#L642">642</a>                         if (<a href="ident?i=err">err</a> == -<a href="ident?i=ENOBUFS">ENOBUFS</a> &amp;&amp; !inet-&gt;recverr)
<a name="L643" href="source/net/ipv4/raw.c#L643">643</a>                                 <a href="ident?i=err">err</a> = 0;
<a name="L644" href="source/net/ipv4/raw.c#L644">644</a>                 }
<a name="L645" href="source/net/ipv4/raw.c#L645">645</a>                 <a href="ident?i=release_sock">release_sock</a>(sk);
<a name="L646" href="source/net/ipv4/raw.c#L646">646</a>         }
<a name="L647" href="source/net/ipv4/raw.c#L647">647</a> <a href="ident?i=done">done</a>:
<a name="L648" href="source/net/ipv4/raw.c#L648">648</a>         if (<a href="ident?i=free">free</a>)
<a name="L649" href="source/net/ipv4/raw.c#L649">649</a>                 <a href="ident?i=kfree">kfree</a>(ipc.opt);
<a name="L650" href="source/net/ipv4/raw.c#L650">650</a>         <a href="ident?i=ip_rt_put">ip_rt_put</a>(<a href="ident?i=rt">rt</a>);
<a name="L651" href="source/net/ipv4/raw.c#L651">651</a> 
<a name="L652" href="source/net/ipv4/raw.c#L652">652</a> <a href="ident?i=out">out</a>:
<a name="L653" href="source/net/ipv4/raw.c#L653">653</a>         if (<a href="ident?i=err">err</a> &lt; 0)
<a name="L654" href="source/net/ipv4/raw.c#L654">654</a>                 return <a href="ident?i=err">err</a>;
<a name="L655" href="source/net/ipv4/raw.c#L655">655</a>         return <a href="ident?i=len">len</a>;
<a name="L656" href="source/net/ipv4/raw.c#L656">656</a> 
<a name="L657" href="source/net/ipv4/raw.c#L657">657</a> do_confirm:
<a name="L658" href="source/net/ipv4/raw.c#L658">658</a>         <a href="ident?i=dst_confirm">dst_confirm</a>(&amp;<a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>);
<a name="L659" href="source/net/ipv4/raw.c#L659">659</a>         if (!(<a href="ident?i=msg">msg</a>-&gt;msg_flags &amp; <a href="ident?i=MSG_PROBE">MSG_PROBE</a>) || <a href="ident?i=len">len</a>)
<a name="L660" href="source/net/ipv4/raw.c#L660">660</a>                 goto back_from_confirm;
<a name="L661" href="source/net/ipv4/raw.c#L661">661</a>         <a href="ident?i=err">err</a> = 0;
<a name="L662" href="source/net/ipv4/raw.c#L662">662</a>         goto <a href="ident?i=done">done</a>;
<a name="L663" href="source/net/ipv4/raw.c#L663">663</a> }
<a name="L664" href="source/net/ipv4/raw.c#L664">664</a> 
<a name="L665" href="source/net/ipv4/raw.c#L665">665</a> static void <a href="ident?i=raw_close">raw_close</a>(struct <a href="ident?i=sock">sock</a> *sk, long <a href="ident?i=timeout">timeout</a>)
<a name="L666" href="source/net/ipv4/raw.c#L666">666</a> {
<a name="L667" href="source/net/ipv4/raw.c#L667">667</a>         <b><i>/*</i></b>
<a name="L668" href="source/net/ipv4/raw.c#L668">668</a> <b><i>         * Raw sockets may have direct kernel references. Kill them.</i></b>
<a name="L669" href="source/net/ipv4/raw.c#L669">669</a> <b><i>         */</i></b>
<a name="L670" href="source/net/ipv4/raw.c#L670">670</a>         <a href="ident?i=ip_ra_control">ip_ra_control</a>(sk, 0, <a href="ident?i=NULL">NULL</a>);
<a name="L671" href="source/net/ipv4/raw.c#L671">671</a> 
<a name="L672" href="source/net/ipv4/raw.c#L672">672</a>         <a href="ident?i=sk_common_release">sk_common_release</a>(sk);
<a name="L673" href="source/net/ipv4/raw.c#L673">673</a> }
<a name="L674" href="source/net/ipv4/raw.c#L674">674</a> 
<a name="L675" href="source/net/ipv4/raw.c#L675">675</a> static void <a href="ident?i=raw_destroy">raw_destroy</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L676" href="source/net/ipv4/raw.c#L676">676</a> {
<a name="L677" href="source/net/ipv4/raw.c#L677">677</a>         <a href="ident?i=lock_sock">lock_sock</a>(sk);
<a name="L678" href="source/net/ipv4/raw.c#L678">678</a>         <a href="ident?i=ip_flush_pending_frames">ip_flush_pending_frames</a>(sk);
<a name="L679" href="source/net/ipv4/raw.c#L679">679</a>         <a href="ident?i=release_sock">release_sock</a>(sk);
<a name="L680" href="source/net/ipv4/raw.c#L680">680</a> }
<a name="L681" href="source/net/ipv4/raw.c#L681">681</a> 
<a name="L682" href="source/net/ipv4/raw.c#L682">682</a> <b><i>/* This gets rid of all the nasties in af_inet. -DaveM */</i></b>
<a name="L683" href="source/net/ipv4/raw.c#L683">683</a> static int <a href="ident?i=raw_bind">raw_bind</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=sockaddr">sockaddr</a> *<a href="ident?i=uaddr">uaddr</a>, int addr_len)
<a name="L684" href="source/net/ipv4/raw.c#L684">684</a> {
<a name="L685" href="source/net/ipv4/raw.c#L685">685</a>         struct <a href="ident?i=inet_sock">inet_sock</a> *inet = <a href="ident?i=inet_sk">inet_sk</a>(sk);
<a name="L686" href="source/net/ipv4/raw.c#L686">686</a>         struct <a href="ident?i=sockaddr_in">sockaddr_in</a> *<a href="ident?i=addr">addr</a> = (struct <a href="ident?i=sockaddr_in">sockaddr_in</a> *) <a href="ident?i=uaddr">uaddr</a>;
<a name="L687" href="source/net/ipv4/raw.c#L687">687</a>         int <a href="ident?i=ret">ret</a> = -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L688" href="source/net/ipv4/raw.c#L688">688</a>         int chk_addr_ret;
<a name="L689" href="source/net/ipv4/raw.c#L689">689</a> 
<a name="L690" href="source/net/ipv4/raw.c#L690">690</a>         if (sk-&gt;<a href="ident?i=sk_state">sk_state</a> != TCP_CLOSE || addr_len &lt; sizeof(struct <a href="ident?i=sockaddr_in">sockaddr_in</a>))
<a name="L691" href="source/net/ipv4/raw.c#L691">691</a>                 goto <a href="ident?i=out">out</a>;
<a name="L692" href="source/net/ipv4/raw.c#L692">692</a>         chk_addr_ret = <a href="ident?i=inet_addr_type">inet_addr_type</a>(<a href="ident?i=sock_net">sock_net</a>(sk), <a href="ident?i=addr">addr</a>-&gt;sin_addr.s_addr);
<a name="L693" href="source/net/ipv4/raw.c#L693">693</a>         <a href="ident?i=ret">ret</a> = -<a href="ident?i=EADDRNOTAVAIL">EADDRNOTAVAIL</a>;
<a name="L694" href="source/net/ipv4/raw.c#L694">694</a>         if (<a href="ident?i=addr">addr</a>-&gt;sin_addr.s_addr &amp;&amp; chk_addr_ret != RTN_LOCAL &amp;&amp;
<a name="L695" href="source/net/ipv4/raw.c#L695">695</a>             chk_addr_ret != RTN_MULTICAST &amp;&amp; chk_addr_ret != RTN_BROADCAST)
<a name="L696" href="source/net/ipv4/raw.c#L696">696</a>                 goto <a href="ident?i=out">out</a>;
<a name="L697" href="source/net/ipv4/raw.c#L697">697</a>         inet-&gt;<a href="ident?i=inet_rcv_saddr">inet_rcv_saddr</a> = inet-&gt;inet_saddr = <a href="ident?i=addr">addr</a>-&gt;sin_addr.s_addr;
<a name="L698" href="source/net/ipv4/raw.c#L698">698</a>         if (chk_addr_ret == RTN_MULTICAST || chk_addr_ret == RTN_BROADCAST)
<a name="L699" href="source/net/ipv4/raw.c#L699">699</a>                 inet-&gt;inet_saddr = 0;  <b><i>/* Use device */</i></b>
<a name="L700" href="source/net/ipv4/raw.c#L700">700</a>         <a href="ident?i=sk_dst_reset">sk_dst_reset</a>(sk);
<a name="L701" href="source/net/ipv4/raw.c#L701">701</a>         <a href="ident?i=ret">ret</a> = 0;
<a name="L702" href="source/net/ipv4/raw.c#L702">702</a> <a href="ident?i=out">out</a>:    return <a href="ident?i=ret">ret</a>;
<a name="L703" href="source/net/ipv4/raw.c#L703">703</a> }
<a name="L704" href="source/net/ipv4/raw.c#L704">704</a> 
<a name="L705" href="source/net/ipv4/raw.c#L705">705</a> <b><i>/*</i></b>
<a name="L706" href="source/net/ipv4/raw.c#L706">706</a> <b><i> *      This should be easy, if there is something there</i></b>
<a name="L707" href="source/net/ipv4/raw.c#L707">707</a> <b><i> *      we return it, otherwise we block.</i></b>
<a name="L708" href="source/net/ipv4/raw.c#L708">708</a> <b><i> */</i></b>
<a name="L709" href="source/net/ipv4/raw.c#L709">709</a> 
<a name="L710" href="source/net/ipv4/raw.c#L710">710</a> static int <a href="ident?i=raw_recvmsg">raw_recvmsg</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=msghdr">msghdr</a> *<a href="ident?i=msg">msg</a>, <a href="ident?i=size_t">size_t</a> <a href="ident?i=len">len</a>,
<a name="L711" href="source/net/ipv4/raw.c#L711">711</a>                        int noblock, int <a href="ident?i=flags">flags</a>, int *addr_len)
<a name="L712" href="source/net/ipv4/raw.c#L712">712</a> {
<a name="L713" href="source/net/ipv4/raw.c#L713">713</a>         struct <a href="ident?i=inet_sock">inet_sock</a> *inet = <a href="ident?i=inet_sk">inet_sk</a>(sk);
<a name="L714" href="source/net/ipv4/raw.c#L714">714</a>         <a href="ident?i=size_t">size_t</a> copied = 0;
<a name="L715" href="source/net/ipv4/raw.c#L715">715</a>         int <a href="ident?i=err">err</a> = -<a href="ident?i=EOPNOTSUPP">EOPNOTSUPP</a>;
<a name="L716" href="source/net/ipv4/raw.c#L716">716</a>         <a href="ident?i=DECLARE_SOCKADDR">DECLARE_SOCKADDR</a>(struct <a href="ident?i=sockaddr_in">sockaddr_in</a> *, <a href="ident?i=sin">sin</a>, <a href="ident?i=msg">msg</a>-&gt;msg_name);
<a name="L717" href="source/net/ipv4/raw.c#L717">717</a>         struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>;
<a name="L718" href="source/net/ipv4/raw.c#L718">718</a> 
<a name="L719" href="source/net/ipv4/raw.c#L719">719</a>         if (<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=MSG_OOB">MSG_OOB</a>)
<a name="L720" href="source/net/ipv4/raw.c#L720">720</a>                 goto <a href="ident?i=out">out</a>;
<a name="L721" href="source/net/ipv4/raw.c#L721">721</a> 
<a name="L722" href="source/net/ipv4/raw.c#L722">722</a>         if (<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=MSG_ERRQUEUE">MSG_ERRQUEUE</a>) {
<a name="L723" href="source/net/ipv4/raw.c#L723">723</a>                 <a href="ident?i=err">err</a> = <a href="ident?i=ip_recv_error">ip_recv_error</a>(sk, <a href="ident?i=msg">msg</a>, <a href="ident?i=len">len</a>, addr_len);
<a name="L724" href="source/net/ipv4/raw.c#L724">724</a>                 goto <a href="ident?i=out">out</a>;
<a name="L725" href="source/net/ipv4/raw.c#L725">725</a>         }
<a name="L726" href="source/net/ipv4/raw.c#L726">726</a> 
<a name="L727" href="source/net/ipv4/raw.c#L727">727</a>         <a href="ident?i=skb">skb</a> = <a href="ident?i=skb_recv_datagram">skb_recv_datagram</a>(sk, <a href="ident?i=flags">flags</a>, noblock, &amp;<a href="ident?i=err">err</a>);
<a name="L728" href="source/net/ipv4/raw.c#L728">728</a>         if (!<a href="ident?i=skb">skb</a>)
<a name="L729" href="source/net/ipv4/raw.c#L729">729</a>                 goto <a href="ident?i=out">out</a>;
<a name="L730" href="source/net/ipv4/raw.c#L730">730</a> 
<a name="L731" href="source/net/ipv4/raw.c#L731">731</a>         copied = <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a>;
<a name="L732" href="source/net/ipv4/raw.c#L732">732</a>         if (<a href="ident?i=len">len</a> &lt; copied) {
<a name="L733" href="source/net/ipv4/raw.c#L733">733</a>                 <a href="ident?i=msg">msg</a>-&gt;msg_flags |= <a href="ident?i=MSG_TRUNC">MSG_TRUNC</a>;
<a name="L734" href="source/net/ipv4/raw.c#L734">734</a>                 copied = <a href="ident?i=len">len</a>;
<a name="L735" href="source/net/ipv4/raw.c#L735">735</a>         }
<a name="L736" href="source/net/ipv4/raw.c#L736">736</a> 
<a name="L737" href="source/net/ipv4/raw.c#L737">737</a>         <a href="ident?i=err">err</a> = <a href="ident?i=skb_copy_datagram_msg">skb_copy_datagram_msg</a>(<a href="ident?i=skb">skb</a>, 0, <a href="ident?i=msg">msg</a>, copied);
<a name="L738" href="source/net/ipv4/raw.c#L738">738</a>         if (<a href="ident?i=err">err</a>)
<a name="L739" href="source/net/ipv4/raw.c#L739">739</a>                 goto <a href="ident?i=done">done</a>;
<a name="L740" href="source/net/ipv4/raw.c#L740">740</a> 
<a name="L741" href="source/net/ipv4/raw.c#L741">741</a>         <a href="ident?i=sock_recv_ts_and_drops">sock_recv_ts_and_drops</a>(<a href="ident?i=msg">msg</a>, sk, <a href="ident?i=skb">skb</a>);
<a name="L742" href="source/net/ipv4/raw.c#L742">742</a> 
<a name="L743" href="source/net/ipv4/raw.c#L743">743</a>         <b><i>/* Copy the address. */</i></b>
<a name="L744" href="source/net/ipv4/raw.c#L744">744</a>         if (<a href="ident?i=sin">sin</a>) {
<a name="L745" href="source/net/ipv4/raw.c#L745">745</a>                 <a href="ident?i=sin">sin</a>-&gt;sin_family = <a href="ident?i=AF_INET">AF_INET</a>;
<a name="L746" href="source/net/ipv4/raw.c#L746">746</a>                 <a href="ident?i=sin">sin</a>-&gt;sin_addr.s_addr = <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=saddr">saddr</a>;
<a name="L747" href="source/net/ipv4/raw.c#L747">747</a>                 <a href="ident?i=sin">sin</a>-&gt;sin_port = 0;
<a name="L748" href="source/net/ipv4/raw.c#L748">748</a>                 <a href="ident?i=memset">memset</a>(&amp;<a href="ident?i=sin">sin</a>-&gt;<a href="ident?i=sin_zero">sin_zero</a>, 0, sizeof(<a href="ident?i=sin">sin</a>-&gt;<a href="ident?i=sin_zero">sin_zero</a>));
<a name="L749" href="source/net/ipv4/raw.c#L749">749</a>                 *addr_len = sizeof(*<a href="ident?i=sin">sin</a>);
<a name="L750" href="source/net/ipv4/raw.c#L750">750</a>         }
<a name="L751" href="source/net/ipv4/raw.c#L751">751</a>         if (inet-&gt;cmsg_flags)
<a name="L752" href="source/net/ipv4/raw.c#L752">752</a>                 <a href="ident?i=ip_cmsg_recv">ip_cmsg_recv</a>(<a href="ident?i=msg">msg</a>, <a href="ident?i=skb">skb</a>);
<a name="L753" href="source/net/ipv4/raw.c#L753">753</a>         if (<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=MSG_TRUNC">MSG_TRUNC</a>)
<a name="L754" href="source/net/ipv4/raw.c#L754">754</a>                 copied = <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a>;
<a name="L755" href="source/net/ipv4/raw.c#L755">755</a> <a href="ident?i=done">done</a>:
<a name="L756" href="source/net/ipv4/raw.c#L756">756</a>         <a href="ident?i=skb_free_datagram">skb_free_datagram</a>(sk, <a href="ident?i=skb">skb</a>);
<a name="L757" href="source/net/ipv4/raw.c#L757">757</a> <a href="ident?i=out">out</a>:
<a name="L758" href="source/net/ipv4/raw.c#L758">758</a>         if (<a href="ident?i=err">err</a>)
<a name="L759" href="source/net/ipv4/raw.c#L759">759</a>                 return <a href="ident?i=err">err</a>;
<a name="L760" href="source/net/ipv4/raw.c#L760">760</a>         return copied;
<a name="L761" href="source/net/ipv4/raw.c#L761">761</a> }
<a name="L762" href="source/net/ipv4/raw.c#L762">762</a> 
<a name="L763" href="source/net/ipv4/raw.c#L763">763</a> static int <a href="ident?i=raw_init">raw_init</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L764" href="source/net/ipv4/raw.c#L764">764</a> {
<a name="L765" href="source/net/ipv4/raw.c#L765">765</a>         struct <a href="ident?i=raw_sock">raw_sock</a> *<a href="ident?i=rp">rp</a> = <a href="ident?i=raw_sk">raw_sk</a>(sk);
<a name="L766" href="source/net/ipv4/raw.c#L766">766</a> 
<a name="L767" href="source/net/ipv4/raw.c#L767">767</a>         if (<a href="ident?i=inet_sk">inet_sk</a>(sk)-&gt;<a href="ident?i=inet_num">inet_num</a> == <a href="ident?i=IPPROTO_ICMP">IPPROTO_ICMP</a>)
<a name="L768" href="source/net/ipv4/raw.c#L768">768</a>                 <a href="ident?i=memset">memset</a>(&amp;<a href="ident?i=rp">rp</a>-&gt;<a href="ident?i=filter">filter</a>, 0, sizeof(<a href="ident?i=rp">rp</a>-&gt;<a href="ident?i=filter">filter</a>));
<a name="L769" href="source/net/ipv4/raw.c#L769">769</a>         return 0;
<a name="L770" href="source/net/ipv4/raw.c#L770">770</a> }
<a name="L771" href="source/net/ipv4/raw.c#L771">771</a> 
<a name="L772" href="source/net/ipv4/raw.c#L772">772</a> static int <a href="ident?i=raw_seticmpfilter">raw_seticmpfilter</a>(struct <a href="ident?i=sock">sock</a> *sk, char <a href="ident?i=__user">__user</a> *optval, int <a href="ident?i=optlen">optlen</a>)
<a name="L773" href="source/net/ipv4/raw.c#L773">773</a> {
<a name="L774" href="source/net/ipv4/raw.c#L774">774</a>         if (<a href="ident?i=optlen">optlen</a> &gt; sizeof(struct <a href="ident?i=icmp_filter">icmp_filter</a>))
<a name="L775" href="source/net/ipv4/raw.c#L775">775</a>                 <a href="ident?i=optlen">optlen</a> = sizeof(struct <a href="ident?i=icmp_filter">icmp_filter</a>);
<a name="L776" href="source/net/ipv4/raw.c#L776">776</a>         if (<a href="ident?i=copy_from_user">copy_from_user</a>(&amp;<a href="ident?i=raw_sk">raw_sk</a>(sk)-&gt;<a href="ident?i=filter">filter</a>, optval, <a href="ident?i=optlen">optlen</a>))
<a name="L777" href="source/net/ipv4/raw.c#L777">777</a>                 return -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L778" href="source/net/ipv4/raw.c#L778">778</a>         return 0;
<a name="L779" href="source/net/ipv4/raw.c#L779">779</a> }
<a name="L780" href="source/net/ipv4/raw.c#L780">780</a> 
<a name="L781" href="source/net/ipv4/raw.c#L781">781</a> static int <a href="ident?i=raw_geticmpfilter">raw_geticmpfilter</a>(struct <a href="ident?i=sock">sock</a> *sk, char <a href="ident?i=__user">__user</a> *optval, int <a href="ident?i=__user">__user</a> *<a href="ident?i=optlen">optlen</a>)
<a name="L782" href="source/net/ipv4/raw.c#L782">782</a> {
<a name="L783" href="source/net/ipv4/raw.c#L783">783</a>         int <a href="ident?i=len">len</a>, <a href="ident?i=ret">ret</a> = -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L784" href="source/net/ipv4/raw.c#L784">784</a> 
<a name="L785" href="source/net/ipv4/raw.c#L785">785</a>         if (<a href="ident?i=get_user">get_user</a>(<a href="ident?i=len">len</a>, <a href="ident?i=optlen">optlen</a>))
<a name="L786" href="source/net/ipv4/raw.c#L786">786</a>                 goto <a href="ident?i=out">out</a>;
<a name="L787" href="source/net/ipv4/raw.c#L787">787</a>         <a href="ident?i=ret">ret</a> = -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L788" href="source/net/ipv4/raw.c#L788">788</a>         if (<a href="ident?i=len">len</a> &lt; 0)
<a name="L789" href="source/net/ipv4/raw.c#L789">789</a>                 goto <a href="ident?i=out">out</a>;
<a name="L790" href="source/net/ipv4/raw.c#L790">790</a>         if (<a href="ident?i=len">len</a> &gt; sizeof(struct <a href="ident?i=icmp_filter">icmp_filter</a>))
<a name="L791" href="source/net/ipv4/raw.c#L791">791</a>                 <a href="ident?i=len">len</a> = sizeof(struct <a href="ident?i=icmp_filter">icmp_filter</a>);
<a name="L792" href="source/net/ipv4/raw.c#L792">792</a>         <a href="ident?i=ret">ret</a> = -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L793" href="source/net/ipv4/raw.c#L793">793</a>         if (<a href="ident?i=put_user">put_user</a>(<a href="ident?i=len">len</a>, <a href="ident?i=optlen">optlen</a>) ||
<a name="L794" href="source/net/ipv4/raw.c#L794">794</a>             <a href="ident?i=copy_to_user">copy_to_user</a>(optval, &amp;<a href="ident?i=raw_sk">raw_sk</a>(sk)-&gt;<a href="ident?i=filter">filter</a>, <a href="ident?i=len">len</a>))
<a name="L795" href="source/net/ipv4/raw.c#L795">795</a>                 goto <a href="ident?i=out">out</a>;
<a name="L796" href="source/net/ipv4/raw.c#L796">796</a>         <a href="ident?i=ret">ret</a> = 0;
<a name="L797" href="source/net/ipv4/raw.c#L797">797</a> <a href="ident?i=out">out</a>:    return <a href="ident?i=ret">ret</a>;
<a name="L798" href="source/net/ipv4/raw.c#L798">798</a> }
<a name="L799" href="source/net/ipv4/raw.c#L799">799</a> 
<a name="L800" href="source/net/ipv4/raw.c#L800">800</a> static int <a href="ident?i=do_raw_setsockopt">do_raw_setsockopt</a>(struct <a href="ident?i=sock">sock</a> *sk, int <a href="ident?i=level">level</a>, int optname,
<a name="L801" href="source/net/ipv4/raw.c#L801">801</a>                           char <a href="ident?i=__user">__user</a> *optval, unsigned int <a href="ident?i=optlen">optlen</a>)
<a name="L802" href="source/net/ipv4/raw.c#L802">802</a> {
<a name="L803" href="source/net/ipv4/raw.c#L803">803</a>         if (optname == <a href="ident?i=ICMP_FILTER">ICMP_FILTER</a>) {
<a name="L804" href="source/net/ipv4/raw.c#L804">804</a>                 if (<a href="ident?i=inet_sk">inet_sk</a>(sk)-&gt;<a href="ident?i=inet_num">inet_num</a> != <a href="ident?i=IPPROTO_ICMP">IPPROTO_ICMP</a>)
<a name="L805" href="source/net/ipv4/raw.c#L805">805</a>                         return -<a href="ident?i=EOPNOTSUPP">EOPNOTSUPP</a>;
<a name="L806" href="source/net/ipv4/raw.c#L806">806</a>                 else
<a name="L807" href="source/net/ipv4/raw.c#L807">807</a>                         return <a href="ident?i=raw_seticmpfilter">raw_seticmpfilter</a>(sk, optval, <a href="ident?i=optlen">optlen</a>);
<a name="L808" href="source/net/ipv4/raw.c#L808">808</a>         }
<a name="L809" href="source/net/ipv4/raw.c#L809">809</a>         return -<a href="ident?i=ENOPROTOOPT">ENOPROTOOPT</a>;
<a name="L810" href="source/net/ipv4/raw.c#L810">810</a> }
<a name="L811" href="source/net/ipv4/raw.c#L811">811</a> 
<a name="L812" href="source/net/ipv4/raw.c#L812">812</a> static int <a href="ident?i=raw_setsockopt">raw_setsockopt</a>(struct <a href="ident?i=sock">sock</a> *sk, int <a href="ident?i=level">level</a>, int optname,
<a name="L813" href="source/net/ipv4/raw.c#L813">813</a>                           char <a href="ident?i=__user">__user</a> *optval, unsigned int <a href="ident?i=optlen">optlen</a>)
<a name="L814" href="source/net/ipv4/raw.c#L814">814</a> {
<a name="L815" href="source/net/ipv4/raw.c#L815">815</a>         if (<a href="ident?i=level">level</a> != <a href="ident?i=SOL_RAW">SOL_RAW</a>)
<a name="L816" href="source/net/ipv4/raw.c#L816">816</a>                 return <a href="ident?i=ip_setsockopt">ip_setsockopt</a>(sk, <a href="ident?i=level">level</a>, optname, optval, <a href="ident?i=optlen">optlen</a>);
<a name="L817" href="source/net/ipv4/raw.c#L817">817</a>         return <a href="ident?i=do_raw_setsockopt">do_raw_setsockopt</a>(sk, <a href="ident?i=level">level</a>, optname, optval, <a href="ident?i=optlen">optlen</a>);
<a name="L818" href="source/net/ipv4/raw.c#L818">818</a> }
<a name="L819" href="source/net/ipv4/raw.c#L819">819</a> 
<a name="L820" href="source/net/ipv4/raw.c#L820">820</a> #ifdef CONFIG_COMPAT
<a name="L821" href="source/net/ipv4/raw.c#L821">821</a> static int <a href="ident?i=compat_raw_setsockopt">compat_raw_setsockopt</a>(struct <a href="ident?i=sock">sock</a> *sk, int <a href="ident?i=level">level</a>, int optname,
<a name="L822" href="source/net/ipv4/raw.c#L822">822</a>                                  char <a href="ident?i=__user">__user</a> *optval, unsigned int <a href="ident?i=optlen">optlen</a>)
<a name="L823" href="source/net/ipv4/raw.c#L823">823</a> {
<a name="L824" href="source/net/ipv4/raw.c#L824">824</a>         if (<a href="ident?i=level">level</a> != <a href="ident?i=SOL_RAW">SOL_RAW</a>)
<a name="L825" href="source/net/ipv4/raw.c#L825">825</a>                 return <a href="ident?i=compat_ip_setsockopt">compat_ip_setsockopt</a>(sk, <a href="ident?i=level">level</a>, optname, optval, <a href="ident?i=optlen">optlen</a>);
<a name="L826" href="source/net/ipv4/raw.c#L826">826</a>         return <a href="ident?i=do_raw_setsockopt">do_raw_setsockopt</a>(sk, <a href="ident?i=level">level</a>, optname, optval, <a href="ident?i=optlen">optlen</a>);
<a name="L827" href="source/net/ipv4/raw.c#L827">827</a> }
<a name="L828" href="source/net/ipv4/raw.c#L828">828</a> #endif
<a name="L829" href="source/net/ipv4/raw.c#L829">829</a> 
<a name="L830" href="source/net/ipv4/raw.c#L830">830</a> static int <a href="ident?i=do_raw_getsockopt">do_raw_getsockopt</a>(struct <a href="ident?i=sock">sock</a> *sk, int <a href="ident?i=level">level</a>, int optname,
<a name="L831" href="source/net/ipv4/raw.c#L831">831</a>                           char <a href="ident?i=__user">__user</a> *optval, int <a href="ident?i=__user">__user</a> *<a href="ident?i=optlen">optlen</a>)
<a name="L832" href="source/net/ipv4/raw.c#L832">832</a> {
<a name="L833" href="source/net/ipv4/raw.c#L833">833</a>         if (optname == <a href="ident?i=ICMP_FILTER">ICMP_FILTER</a>) {
<a name="L834" href="source/net/ipv4/raw.c#L834">834</a>                 if (<a href="ident?i=inet_sk">inet_sk</a>(sk)-&gt;<a href="ident?i=inet_num">inet_num</a> != <a href="ident?i=IPPROTO_ICMP">IPPROTO_ICMP</a>)
<a name="L835" href="source/net/ipv4/raw.c#L835">835</a>                         return -<a href="ident?i=EOPNOTSUPP">EOPNOTSUPP</a>;
<a name="L836" href="source/net/ipv4/raw.c#L836">836</a>                 else
<a name="L837" href="source/net/ipv4/raw.c#L837">837</a>                         return <a href="ident?i=raw_geticmpfilter">raw_geticmpfilter</a>(sk, optval, <a href="ident?i=optlen">optlen</a>);
<a name="L838" href="source/net/ipv4/raw.c#L838">838</a>         }
<a name="L839" href="source/net/ipv4/raw.c#L839">839</a>         return -<a href="ident?i=ENOPROTOOPT">ENOPROTOOPT</a>;
<a name="L840" href="source/net/ipv4/raw.c#L840">840</a> }
<a name="L841" href="source/net/ipv4/raw.c#L841">841</a> 
<a name="L842" href="source/net/ipv4/raw.c#L842">842</a> static int <a href="ident?i=raw_getsockopt">raw_getsockopt</a>(struct <a href="ident?i=sock">sock</a> *sk, int <a href="ident?i=level">level</a>, int optname,
<a name="L843" href="source/net/ipv4/raw.c#L843">843</a>                           char <a href="ident?i=__user">__user</a> *optval, int <a href="ident?i=__user">__user</a> *<a href="ident?i=optlen">optlen</a>)
<a name="L844" href="source/net/ipv4/raw.c#L844">844</a> {
<a name="L845" href="source/net/ipv4/raw.c#L845">845</a>         if (<a href="ident?i=level">level</a> != <a href="ident?i=SOL_RAW">SOL_RAW</a>)
<a name="L846" href="source/net/ipv4/raw.c#L846">846</a>                 return <a href="ident?i=ip_getsockopt">ip_getsockopt</a>(sk, <a href="ident?i=level">level</a>, optname, optval, <a href="ident?i=optlen">optlen</a>);
<a name="L847" href="source/net/ipv4/raw.c#L847">847</a>         return <a href="ident?i=do_raw_getsockopt">do_raw_getsockopt</a>(sk, <a href="ident?i=level">level</a>, optname, optval, <a href="ident?i=optlen">optlen</a>);
<a name="L848" href="source/net/ipv4/raw.c#L848">848</a> }
<a name="L849" href="source/net/ipv4/raw.c#L849">849</a> 
<a name="L850" href="source/net/ipv4/raw.c#L850">850</a> #ifdef CONFIG_COMPAT
<a name="L851" href="source/net/ipv4/raw.c#L851">851</a> static int <a href="ident?i=compat_raw_getsockopt">compat_raw_getsockopt</a>(struct <a href="ident?i=sock">sock</a> *sk, int <a href="ident?i=level">level</a>, int optname,
<a name="L852" href="source/net/ipv4/raw.c#L852">852</a>                                  char <a href="ident?i=__user">__user</a> *optval, int <a href="ident?i=__user">__user</a> *<a href="ident?i=optlen">optlen</a>)
<a name="L853" href="source/net/ipv4/raw.c#L853">853</a> {
<a name="L854" href="source/net/ipv4/raw.c#L854">854</a>         if (<a href="ident?i=level">level</a> != <a href="ident?i=SOL_RAW">SOL_RAW</a>)
<a name="L855" href="source/net/ipv4/raw.c#L855">855</a>                 return <a href="ident?i=compat_ip_getsockopt">compat_ip_getsockopt</a>(sk, <a href="ident?i=level">level</a>, optname, optval, <a href="ident?i=optlen">optlen</a>);
<a name="L856" href="source/net/ipv4/raw.c#L856">856</a>         return <a href="ident?i=do_raw_getsockopt">do_raw_getsockopt</a>(sk, <a href="ident?i=level">level</a>, optname, optval, <a href="ident?i=optlen">optlen</a>);
<a name="L857" href="source/net/ipv4/raw.c#L857">857</a> }
<a name="L858" href="source/net/ipv4/raw.c#L858">858</a> #endif
<a name="L859" href="source/net/ipv4/raw.c#L859">859</a> 
<a name="L860" href="source/net/ipv4/raw.c#L860">860</a> static int <a href="ident?i=raw_ioctl">raw_ioctl</a>(struct <a href="ident?i=sock">sock</a> *sk, int <a href="ident?i=cmd">cmd</a>, unsigned long <a href="ident?i=arg">arg</a>)
<a name="L861" href="source/net/ipv4/raw.c#L861">861</a> {
<a name="L862" href="source/net/ipv4/raw.c#L862">862</a>         switch (<a href="ident?i=cmd">cmd</a>) {
<a name="L863" href="source/net/ipv4/raw.c#L863">863</a>         case <a href="ident?i=SIOCOUTQ">SIOCOUTQ</a>: {
<a name="L864" href="source/net/ipv4/raw.c#L864">864</a>                 int amount = <a href="ident?i=sk_wmem_alloc_get">sk_wmem_alloc_get</a>(sk);
<a name="L865" href="source/net/ipv4/raw.c#L865">865</a> 
<a name="L866" href="source/net/ipv4/raw.c#L866">866</a>                 return <a href="ident?i=put_user">put_user</a>(amount, (int <a href="ident?i=__user">__user</a> *)<a href="ident?i=arg">arg</a>);
<a name="L867" href="source/net/ipv4/raw.c#L867">867</a>         }
<a name="L868" href="source/net/ipv4/raw.c#L868">868</a>         case <a href="ident?i=SIOCINQ">SIOCINQ</a>: {
<a name="L869" href="source/net/ipv4/raw.c#L869">869</a>                 struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>;
<a name="L870" href="source/net/ipv4/raw.c#L870">870</a>                 int amount = 0;
<a name="L871" href="source/net/ipv4/raw.c#L871">871</a> 
<a name="L872" href="source/net/ipv4/raw.c#L872">872</a>                 <a href="ident?i=spin_lock_bh">spin_lock_bh</a>(&amp;sk-&gt;sk_receive_queue.<a href="ident?i=lock">lock</a>);
<a name="L873" href="source/net/ipv4/raw.c#L873">873</a>                 <a href="ident?i=skb">skb</a> = <a href="ident?i=skb_peek">skb_peek</a>(&amp;sk-&gt;sk_receive_queue);
<a name="L874" href="source/net/ipv4/raw.c#L874">874</a>                 if (<a href="ident?i=skb">skb</a>)
<a name="L875" href="source/net/ipv4/raw.c#L875">875</a>                         amount = <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a>;
<a name="L876" href="source/net/ipv4/raw.c#L876">876</a>                 <a href="ident?i=spin_unlock_bh">spin_unlock_bh</a>(&amp;sk-&gt;sk_receive_queue.<a href="ident?i=lock">lock</a>);
<a name="L877" href="source/net/ipv4/raw.c#L877">877</a>                 return <a href="ident?i=put_user">put_user</a>(amount, (int <a href="ident?i=__user">__user</a> *)<a href="ident?i=arg">arg</a>);
<a name="L878" href="source/net/ipv4/raw.c#L878">878</a>         }
<a name="L879" href="source/net/ipv4/raw.c#L879">879</a> 
<a name="L880" href="source/net/ipv4/raw.c#L880">880</a>         default:
<a name="L881" href="source/net/ipv4/raw.c#L881">881</a> #ifdef CONFIG_IP_MROUTE
<a name="L882" href="source/net/ipv4/raw.c#L882">882</a>                 return <a href="ident?i=ipmr_ioctl">ipmr_ioctl</a>(sk, <a href="ident?i=cmd">cmd</a>, (void <a href="ident?i=__user">__user</a> *)<a href="ident?i=arg">arg</a>);
<a name="L883" href="source/net/ipv4/raw.c#L883">883</a> #else
<a name="L884" href="source/net/ipv4/raw.c#L884">884</a>                 return -<a href="ident?i=ENOIOCTLCMD">ENOIOCTLCMD</a>;
<a name="L885" href="source/net/ipv4/raw.c#L885">885</a> #endif
<a name="L886" href="source/net/ipv4/raw.c#L886">886</a>         }
<a name="L887" href="source/net/ipv4/raw.c#L887">887</a> }
<a name="L888" href="source/net/ipv4/raw.c#L888">888</a> 
<a name="L889" href="source/net/ipv4/raw.c#L889">889</a> #ifdef CONFIG_COMPAT
<a name="L890" href="source/net/ipv4/raw.c#L890">890</a> static int <a href="ident?i=compat_raw_ioctl">compat_raw_ioctl</a>(struct <a href="ident?i=sock">sock</a> *sk, unsigned int <a href="ident?i=cmd">cmd</a>, unsigned long <a href="ident?i=arg">arg</a>)
<a name="L891" href="source/net/ipv4/raw.c#L891">891</a> {
<a name="L892" href="source/net/ipv4/raw.c#L892">892</a>         switch (<a href="ident?i=cmd">cmd</a>) {
<a name="L893" href="source/net/ipv4/raw.c#L893">893</a>         case <a href="ident?i=SIOCOUTQ">SIOCOUTQ</a>:
<a name="L894" href="source/net/ipv4/raw.c#L894">894</a>         case <a href="ident?i=SIOCINQ">SIOCINQ</a>:
<a name="L895" href="source/net/ipv4/raw.c#L895">895</a>                 return -<a href="ident?i=ENOIOCTLCMD">ENOIOCTLCMD</a>;
<a name="L896" href="source/net/ipv4/raw.c#L896">896</a>         default:
<a name="L897" href="source/net/ipv4/raw.c#L897">897</a> #ifdef CONFIG_IP_MROUTE
<a name="L898" href="source/net/ipv4/raw.c#L898">898</a>                 return <a href="ident?i=ipmr_compat_ioctl">ipmr_compat_ioctl</a>(sk, <a href="ident?i=cmd">cmd</a>, <a href="ident?i=compat_ptr">compat_ptr</a>(<a href="ident?i=arg">arg</a>));
<a name="L899" href="source/net/ipv4/raw.c#L899">899</a> #else
<a name="L900" href="source/net/ipv4/raw.c#L900">900</a>                 return -<a href="ident?i=ENOIOCTLCMD">ENOIOCTLCMD</a>;
<a name="L901" href="source/net/ipv4/raw.c#L901">901</a> #endif
<a name="L902" href="source/net/ipv4/raw.c#L902">902</a>         }
<a name="L903" href="source/net/ipv4/raw.c#L903">903</a> }
<a name="L904" href="source/net/ipv4/raw.c#L904">904</a> #endif
<a name="L905" href="source/net/ipv4/raw.c#L905">905</a> 
<a name="L906" href="source/net/ipv4/raw.c#L906">906</a> struct <a href="ident?i=proto">proto</a> <a href="ident?i=raw_prot">raw_prot</a> = {
<a name="L907" href="source/net/ipv4/raw.c#L907">907</a>         .<a href="ident?i=name">name</a>              = <i>"RAW"</i>,
<a name="L908" href="source/net/ipv4/raw.c#L908">908</a>         .owner             = <a href="ident?i=THIS_MODULE">THIS_MODULE</a>,
<a name="L909" href="source/net/ipv4/raw.c#L909">909</a>         .<a href="ident?i=close">close</a>             = <a href="ident?i=raw_close">raw_close</a>,
<a name="L910" href="source/net/ipv4/raw.c#L910">910</a>         .<a href="ident?i=destroy">destroy</a>           = <a href="ident?i=raw_destroy">raw_destroy</a>,
<a name="L911" href="source/net/ipv4/raw.c#L911">911</a>         .<a href="ident?i=connect">connect</a>           = <a href="ident?i=ip4_datagram_connect">ip4_datagram_connect</a>,
<a name="L912" href="source/net/ipv4/raw.c#L912">912</a>         .<a href="ident?i=disconnect">disconnect</a>        = <a href="ident?i=udp_disconnect">udp_disconnect</a>,
<a name="L913" href="source/net/ipv4/raw.c#L913">913</a>         .<a href="ident?i=ioctl">ioctl</a>             = <a href="ident?i=raw_ioctl">raw_ioctl</a>,
<a name="L914" href="source/net/ipv4/raw.c#L914">914</a>         .<a href="ident?i=init">init</a>              = <a href="ident?i=raw_init">raw_init</a>,
<a name="L915" href="source/net/ipv4/raw.c#L915">915</a>         .<a href="ident?i=setsockopt">setsockopt</a>        = <a href="ident?i=raw_setsockopt">raw_setsockopt</a>,
<a name="L916" href="source/net/ipv4/raw.c#L916">916</a>         .getsockopt        = <a href="ident?i=raw_getsockopt">raw_getsockopt</a>,
<a name="L917" href="source/net/ipv4/raw.c#L917">917</a>         .<a href="ident?i=sendmsg">sendmsg</a>           = <a href="ident?i=raw_sendmsg">raw_sendmsg</a>,
<a name="L918" href="source/net/ipv4/raw.c#L918">918</a>         .recvmsg           = <a href="ident?i=raw_recvmsg">raw_recvmsg</a>,
<a name="L919" href="source/net/ipv4/raw.c#L919">919</a>         .bind              = <a href="ident?i=raw_bind">raw_bind</a>,
<a name="L920" href="source/net/ipv4/raw.c#L920">920</a>         .backlog_rcv       = <a href="ident?i=raw_rcv_skb">raw_rcv_skb</a>,
<a name="L921" href="source/net/ipv4/raw.c#L921">921</a>         .release_cb        = <a href="ident?i=ip4_datagram_release_cb">ip4_datagram_release_cb</a>,
<a name="L922" href="source/net/ipv4/raw.c#L922">922</a>         .<a href="ident?i=hash">hash</a>              = <a href="ident?i=raw_hash_sk">raw_hash_sk</a>,
<a name="L923" href="source/net/ipv4/raw.c#L923">923</a>         .unhash            = <a href="ident?i=raw_unhash_sk">raw_unhash_sk</a>,
<a name="L924" href="source/net/ipv4/raw.c#L924">924</a>         .obj_size          = sizeof(struct <a href="ident?i=raw_sock">raw_sock</a>),
<a name="L925" href="source/net/ipv4/raw.c#L925">925</a>         .<a href="ident?i=h">h</a>.<a href="ident?i=raw_hash">raw_hash</a>        = &amp;<a href="ident?i=raw_v4_hashinfo">raw_v4_hashinfo</a>,
<a name="L926" href="source/net/ipv4/raw.c#L926">926</a> #ifdef CONFIG_COMPAT
<a name="L927" href="source/net/ipv4/raw.c#L927">927</a>         .compat_setsockopt = <a href="ident?i=compat_raw_setsockopt">compat_raw_setsockopt</a>,
<a name="L928" href="source/net/ipv4/raw.c#L928">928</a>         .compat_getsockopt = <a href="ident?i=compat_raw_getsockopt">compat_raw_getsockopt</a>,
<a name="L929" href="source/net/ipv4/raw.c#L929">929</a>         .compat_ioctl      = <a href="ident?i=compat_raw_ioctl">compat_raw_ioctl</a>,
<a name="L930" href="source/net/ipv4/raw.c#L930">930</a> #endif
<a name="L931" href="source/net/ipv4/raw.c#L931">931</a> };
<a name="L932" href="source/net/ipv4/raw.c#L932">932</a> 
<a name="L933" href="source/net/ipv4/raw.c#L933">933</a> #ifdef CONFIG_PROC_FS
<a name="L934" href="source/net/ipv4/raw.c#L934">934</a> static struct <a href="ident?i=sock">sock</a> *<a href="ident?i=raw_get_first">raw_get_first</a>(struct <a href="ident?i=seq_file">seq_file</a> *<a href="ident?i=seq">seq</a>)
<a name="L935" href="source/net/ipv4/raw.c#L935">935</a> {
<a name="L936" href="source/net/ipv4/raw.c#L936">936</a>         struct <a href="ident?i=sock">sock</a> *sk;
<a name="L937" href="source/net/ipv4/raw.c#L937">937</a>         struct <a href="ident?i=raw_iter_state">raw_iter_state</a> *<a href="ident?i=state">state</a> = <a href="ident?i=raw_seq_private">raw_seq_private</a>(<a href="ident?i=seq">seq</a>);
<a name="L938" href="source/net/ipv4/raw.c#L938">938</a> 
<a name="L939" href="source/net/ipv4/raw.c#L939">939</a>         for (<a href="ident?i=state">state</a>-&gt;<a href="ident?i=bucket">bucket</a> = 0; <a href="ident?i=state">state</a>-&gt;<a href="ident?i=bucket">bucket</a> &lt; <a href="ident?i=RAW_HTABLE_SIZE">RAW_HTABLE_SIZE</a>;
<a name="L940" href="source/net/ipv4/raw.c#L940">940</a>                         ++<a href="ident?i=state">state</a>-&gt;<a href="ident?i=bucket">bucket</a>) {
<a name="L941" href="source/net/ipv4/raw.c#L941">941</a>                 <a href="ident?i=sk_for_each">sk_for_each</a>(sk, &amp;<a href="ident?i=state">state</a>-&gt;<a href="ident?i=h">h</a>-&gt;<a href="ident?i=ht">ht</a>[<a href="ident?i=state">state</a>-&gt;<a href="ident?i=bucket">bucket</a>])
<a name="L942" href="source/net/ipv4/raw.c#L942">942</a>                         if (<a href="ident?i=sock_net">sock_net</a>(sk) == <a href="ident?i=seq_file_net">seq_file_net</a>(<a href="ident?i=seq">seq</a>))
<a name="L943" href="source/net/ipv4/raw.c#L943">943</a>                                 goto <a href="ident?i=found">found</a>;
<a name="L944" href="source/net/ipv4/raw.c#L944">944</a>         }
<a name="L945" href="source/net/ipv4/raw.c#L945">945</a>         sk = <a href="ident?i=NULL">NULL</a>;
<a name="L946" href="source/net/ipv4/raw.c#L946">946</a> <a href="ident?i=found">found</a>:
<a name="L947" href="source/net/ipv4/raw.c#L947">947</a>         return sk;
<a name="L948" href="source/net/ipv4/raw.c#L948">948</a> }
<a name="L949" href="source/net/ipv4/raw.c#L949">949</a> 
<a name="L950" href="source/net/ipv4/raw.c#L950">950</a> static struct <a href="ident?i=sock">sock</a> *<a href="ident?i=raw_get_next">raw_get_next</a>(struct <a href="ident?i=seq_file">seq_file</a> *<a href="ident?i=seq">seq</a>, struct <a href="ident?i=sock">sock</a> *sk)
<a name="L951" href="source/net/ipv4/raw.c#L951">951</a> {
<a name="L952" href="source/net/ipv4/raw.c#L952">952</a>         struct <a href="ident?i=raw_iter_state">raw_iter_state</a> *<a href="ident?i=state">state</a> = <a href="ident?i=raw_seq_private">raw_seq_private</a>(<a href="ident?i=seq">seq</a>);
<a name="L953" href="source/net/ipv4/raw.c#L953">953</a> 
<a name="L954" href="source/net/ipv4/raw.c#L954">954</a>         do {
<a name="L955" href="source/net/ipv4/raw.c#L955">955</a>                 sk = <a href="ident?i=sk_next">sk_next</a>(sk);
<a name="L956" href="source/net/ipv4/raw.c#L956">956</a> try_again:
<a name="L957" href="source/net/ipv4/raw.c#L957">957</a>                 ;
<a name="L958" href="source/net/ipv4/raw.c#L958">958</a>         } while (sk &amp;&amp; <a href="ident?i=sock_net">sock_net</a>(sk) != <a href="ident?i=seq_file_net">seq_file_net</a>(<a href="ident?i=seq">seq</a>));
<a name="L959" href="source/net/ipv4/raw.c#L959">959</a> 
<a name="L960" href="source/net/ipv4/raw.c#L960">960</a>         if (!sk &amp;&amp; ++<a href="ident?i=state">state</a>-&gt;<a href="ident?i=bucket">bucket</a> &lt; <a href="ident?i=RAW_HTABLE_SIZE">RAW_HTABLE_SIZE</a>) {
<a name="L961" href="source/net/ipv4/raw.c#L961">961</a>                 sk = <a href="ident?i=sk_head">sk_head</a>(&amp;<a href="ident?i=state">state</a>-&gt;<a href="ident?i=h">h</a>-&gt;<a href="ident?i=ht">ht</a>[<a href="ident?i=state">state</a>-&gt;<a href="ident?i=bucket">bucket</a>]);
<a name="L962" href="source/net/ipv4/raw.c#L962">962</a>                 goto try_again;
<a name="L963" href="source/net/ipv4/raw.c#L963">963</a>         }
<a name="L964" href="source/net/ipv4/raw.c#L964">964</a>         return sk;
<a name="L965" href="source/net/ipv4/raw.c#L965">965</a> }
<a name="L966" href="source/net/ipv4/raw.c#L966">966</a> 
<a name="L967" href="source/net/ipv4/raw.c#L967">967</a> static struct <a href="ident?i=sock">sock</a> *<a href="ident?i=raw_get_idx">raw_get_idx</a>(struct <a href="ident?i=seq_file">seq_file</a> *<a href="ident?i=seq">seq</a>, <a href="ident?i=loff_t">loff_t</a> <a href="ident?i=pos">pos</a>)
<a name="L968" href="source/net/ipv4/raw.c#L968">968</a> {
<a name="L969" href="source/net/ipv4/raw.c#L969">969</a>         struct <a href="ident?i=sock">sock</a> *sk = <a href="ident?i=raw_get_first">raw_get_first</a>(<a href="ident?i=seq">seq</a>);
<a name="L970" href="source/net/ipv4/raw.c#L970">970</a> 
<a name="L971" href="source/net/ipv4/raw.c#L971">971</a>         if (sk)
<a name="L972" href="source/net/ipv4/raw.c#L972">972</a>                 while (<a href="ident?i=pos">pos</a> &amp;&amp; (sk = <a href="ident?i=raw_get_next">raw_get_next</a>(<a href="ident?i=seq">seq</a>, sk)) != <a href="ident?i=NULL">NULL</a>)
<a name="L973" href="source/net/ipv4/raw.c#L973">973</a>                         --<a href="ident?i=pos">pos</a>;
<a name="L974" href="source/net/ipv4/raw.c#L974">974</a>         return <a href="ident?i=pos">pos</a> ? <a href="ident?i=NULL">NULL</a> : sk;
<a name="L975" href="source/net/ipv4/raw.c#L975">975</a> }
<a name="L976" href="source/net/ipv4/raw.c#L976">976</a> 
<a name="L977" href="source/net/ipv4/raw.c#L977">977</a> void *<a href="ident?i=raw_seq_start">raw_seq_start</a>(struct <a href="ident?i=seq_file">seq_file</a> *<a href="ident?i=seq">seq</a>, <a href="ident?i=loff_t">loff_t</a> *<a href="ident?i=pos">pos</a>)
<a name="L978" href="source/net/ipv4/raw.c#L978">978</a> {
<a name="L979" href="source/net/ipv4/raw.c#L979">979</a>         struct <a href="ident?i=raw_iter_state">raw_iter_state</a> *<a href="ident?i=state">state</a> = <a href="ident?i=raw_seq_private">raw_seq_private</a>(<a href="ident?i=seq">seq</a>);
<a name="L980" href="source/net/ipv4/raw.c#L980">980</a> 
<a name="L981" href="source/net/ipv4/raw.c#L981">981</a>         <a href="ident?i=read_lock">read_lock</a>(&amp;<a href="ident?i=state">state</a>-&gt;<a href="ident?i=h">h</a>-&gt;<a href="ident?i=lock">lock</a>);
<a name="L982" href="source/net/ipv4/raw.c#L982">982</a>         return *<a href="ident?i=pos">pos</a> ? <a href="ident?i=raw_get_idx">raw_get_idx</a>(<a href="ident?i=seq">seq</a>, *<a href="ident?i=pos">pos</a> - 1) : <a href="ident?i=SEQ_START_TOKEN">SEQ_START_TOKEN</a>;
<a name="L983" href="source/net/ipv4/raw.c#L983">983</a> }
<a name="L984" href="source/net/ipv4/raw.c#L984">984</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=raw_seq_start">raw_seq_start</a>);
<a name="L985" href="source/net/ipv4/raw.c#L985">985</a> 
<a name="L986" href="source/net/ipv4/raw.c#L986">986</a> void *<a href="ident?i=raw_seq_next">raw_seq_next</a>(struct <a href="ident?i=seq_file">seq_file</a> *<a href="ident?i=seq">seq</a>, void *<a href="ident?i=v">v</a>, <a href="ident?i=loff_t">loff_t</a> *<a href="ident?i=pos">pos</a>)
<a name="L987" href="source/net/ipv4/raw.c#L987">987</a> {
<a name="L988" href="source/net/ipv4/raw.c#L988">988</a>         struct <a href="ident?i=sock">sock</a> *sk;
<a name="L989" href="source/net/ipv4/raw.c#L989">989</a> 
<a name="L990" href="source/net/ipv4/raw.c#L990">990</a>         if (<a href="ident?i=v">v</a> == <a href="ident?i=SEQ_START_TOKEN">SEQ_START_TOKEN</a>)
<a name="L991" href="source/net/ipv4/raw.c#L991">991</a>                 sk = <a href="ident?i=raw_get_first">raw_get_first</a>(<a href="ident?i=seq">seq</a>);
<a name="L992" href="source/net/ipv4/raw.c#L992">992</a>         else
<a name="L993" href="source/net/ipv4/raw.c#L993">993</a>                 sk = <a href="ident?i=raw_get_next">raw_get_next</a>(<a href="ident?i=seq">seq</a>, <a href="ident?i=v">v</a>);
<a name="L994" href="source/net/ipv4/raw.c#L994">994</a>         ++*<a href="ident?i=pos">pos</a>;
<a name="L995" href="source/net/ipv4/raw.c#L995">995</a>         return sk;
<a name="L996" href="source/net/ipv4/raw.c#L996">996</a> }
<a name="L997" href="source/net/ipv4/raw.c#L997">997</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=raw_seq_next">raw_seq_next</a>);
<a name="L998" href="source/net/ipv4/raw.c#L998">998</a> 
<a name="L999" href="source/net/ipv4/raw.c#L999">999</a> void <a href="ident?i=raw_seq_stop">raw_seq_stop</a>(struct <a href="ident?i=seq_file">seq_file</a> *<a href="ident?i=seq">seq</a>, void *<a href="ident?i=v">v</a>)
<a name="L1000" href="source/net/ipv4/raw.c#L1000">1000</a> {
<a name="L1001" href="source/net/ipv4/raw.c#L1001">1001</a>         struct <a href="ident?i=raw_iter_state">raw_iter_state</a> *<a href="ident?i=state">state</a> = <a href="ident?i=raw_seq_private">raw_seq_private</a>(<a href="ident?i=seq">seq</a>);
<a name="L1002" href="source/net/ipv4/raw.c#L1002">1002</a> 
<a name="L1003" href="source/net/ipv4/raw.c#L1003">1003</a>         <a href="ident?i=read_unlock">read_unlock</a>(&amp;<a href="ident?i=state">state</a>-&gt;<a href="ident?i=h">h</a>-&gt;<a href="ident?i=lock">lock</a>);
<a name="L1004" href="source/net/ipv4/raw.c#L1004">1004</a> }
<a name="L1005" href="source/net/ipv4/raw.c#L1005">1005</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=raw_seq_stop">raw_seq_stop</a>);
<a name="L1006" href="source/net/ipv4/raw.c#L1006">1006</a> 
<a name="L1007" href="source/net/ipv4/raw.c#L1007">1007</a> static void <a href="ident?i=raw_sock_seq_show">raw_sock_seq_show</a>(struct <a href="ident?i=seq_file">seq_file</a> *<a href="ident?i=seq">seq</a>, struct <a href="ident?i=sock">sock</a> *<a href="ident?i=sp">sp</a>, int <a href="ident?i=i">i</a>)
<a name="L1008" href="source/net/ipv4/raw.c#L1008">1008</a> {
<a name="L1009" href="source/net/ipv4/raw.c#L1009">1009</a>         struct <a href="ident?i=inet_sock">inet_sock</a> *inet = <a href="ident?i=inet_sk">inet_sk</a>(<a href="ident?i=sp">sp</a>);
<a name="L1010" href="source/net/ipv4/raw.c#L1010">1010</a>         <a href="ident?i=__be32">__be32</a> <a href="ident?i=dest">dest</a> = inet-&gt;<a href="ident?i=inet_daddr">inet_daddr</a>,
<a name="L1011" href="source/net/ipv4/raw.c#L1011">1011</a>                <a href="ident?i=src">src</a> = inet-&gt;<a href="ident?i=inet_rcv_saddr">inet_rcv_saddr</a>;
<a name="L1012" href="source/net/ipv4/raw.c#L1012">1012</a>         <a href="ident?i=__u16">__u16</a> destp = 0,
<a name="L1013" href="source/net/ipv4/raw.c#L1013">1013</a>               srcp  = inet-&gt;<a href="ident?i=inet_num">inet_num</a>;
<a name="L1014" href="source/net/ipv4/raw.c#L1014">1014</a> 
<a name="L1015" href="source/net/ipv4/raw.c#L1015">1015</a>         <a href="ident?i=seq_printf">seq_printf</a>(<a href="ident?i=seq">seq</a>, <i>"%4d: %08X:%04X %08X:%04X"</i>
<a name="L1016" href="source/net/ipv4/raw.c#L1016">1016</a>                 <i>" %02X %08X:%08X %02X:%08lX %08X %5u %8d %lu %d %pK %d\n"</i>,
<a name="L1017" href="source/net/ipv4/raw.c#L1017">1017</a>                 <a href="ident?i=i">i</a>, <a href="ident?i=src">src</a>, srcp, <a href="ident?i=dest">dest</a>, destp, <a href="ident?i=sp">sp</a>-&gt;<a href="ident?i=sk_state">sk_state</a>,
<a name="L1018" href="source/net/ipv4/raw.c#L1018">1018</a>                 <a href="ident?i=sk_wmem_alloc_get">sk_wmem_alloc_get</a>(<a href="ident?i=sp">sp</a>),
<a name="L1019" href="source/net/ipv4/raw.c#L1019">1019</a>                 <a href="ident?i=sk_rmem_alloc_get">sk_rmem_alloc_get</a>(<a href="ident?i=sp">sp</a>),
<a name="L1020" href="source/net/ipv4/raw.c#L1020">1020</a>                 0, 0L, 0,
<a name="L1021" href="source/net/ipv4/raw.c#L1021">1021</a>                 <a href="ident?i=from_kuid_munged">from_kuid_munged</a>(<a href="ident?i=seq_user_ns">seq_user_ns</a>(<a href="ident?i=seq">seq</a>), <a href="ident?i=sock_i_uid">sock_i_uid</a>(<a href="ident?i=sp">sp</a>)),
<a name="L1022" href="source/net/ipv4/raw.c#L1022">1022</a>                 0, <a href="ident?i=sock_i_ino">sock_i_ino</a>(<a href="ident?i=sp">sp</a>),
<a name="L1023" href="source/net/ipv4/raw.c#L1023">1023</a>                 <a href="ident?i=atomic_read">atomic_read</a>(&amp;<a href="ident?i=sp">sp</a>-&gt;<a href="ident?i=sk_refcnt">sk_refcnt</a>), <a href="ident?i=sp">sp</a>, <a href="ident?i=atomic_read">atomic_read</a>(&amp;<a href="ident?i=sp">sp</a>-&gt;sk_drops));
<a name="L1024" href="source/net/ipv4/raw.c#L1024">1024</a> }
<a name="L1025" href="source/net/ipv4/raw.c#L1025">1025</a> 
<a name="L1026" href="source/net/ipv4/raw.c#L1026">1026</a> static int <a href="ident?i=raw_seq_show">raw_seq_show</a>(struct <a href="ident?i=seq_file">seq_file</a> *<a href="ident?i=seq">seq</a>, void *<a href="ident?i=v">v</a>)
<a name="L1027" href="source/net/ipv4/raw.c#L1027">1027</a> {
<a name="L1028" href="source/net/ipv4/raw.c#L1028">1028</a>         if (<a href="ident?i=v">v</a> == <a href="ident?i=SEQ_START_TOKEN">SEQ_START_TOKEN</a>)
<a name="L1029" href="source/net/ipv4/raw.c#L1029">1029</a>                 <a href="ident?i=seq_printf">seq_printf</a>(<a href="ident?i=seq">seq</a>, <i>"  sl  local_address rem_address   st tx_queue "</i>
<a name="L1030" href="source/net/ipv4/raw.c#L1030">1030</a>                                 <i>"rx_queue tr tm-&gt;when retrnsmt   uid  timeout "</i>
<a name="L1031" href="source/net/ipv4/raw.c#L1031">1031</a>                                 <i>"inode ref pointer drops\n"</i>);
<a name="L1032" href="source/net/ipv4/raw.c#L1032">1032</a>         else
<a name="L1033" href="source/net/ipv4/raw.c#L1033">1033</a>                 <a href="ident?i=raw_sock_seq_show">raw_sock_seq_show</a>(<a href="ident?i=seq">seq</a>, <a href="ident?i=v">v</a>, <a href="ident?i=raw_seq_private">raw_seq_private</a>(<a href="ident?i=seq">seq</a>)-&gt;<a href="ident?i=bucket">bucket</a>);
<a name="L1034" href="source/net/ipv4/raw.c#L1034">1034</a>         return 0;
<a name="L1035" href="source/net/ipv4/raw.c#L1035">1035</a> }
<a name="L1036" href="source/net/ipv4/raw.c#L1036">1036</a> 
<a name="L1037" href="source/net/ipv4/raw.c#L1037">1037</a> static const struct <a href="ident?i=seq_operations">seq_operations</a> <a href="ident?i=raw_seq_ops">raw_seq_ops</a> = {
<a name="L1038" href="source/net/ipv4/raw.c#L1038">1038</a>         .<a href="ident?i=start">start</a> = <a href="ident?i=raw_seq_start">raw_seq_start</a>,
<a name="L1039" href="source/net/ipv4/raw.c#L1039">1039</a>         .<a href="ident?i=next">next</a>  = <a href="ident?i=raw_seq_next">raw_seq_next</a>,
<a name="L1040" href="source/net/ipv4/raw.c#L1040">1040</a>         .<a href="ident?i=stop">stop</a>  = <a href="ident?i=raw_seq_stop">raw_seq_stop</a>,
<a name="L1041" href="source/net/ipv4/raw.c#L1041">1041</a>         .<a href="ident?i=show">show</a>  = <a href="ident?i=raw_seq_show">raw_seq_show</a>,
<a name="L1042" href="source/net/ipv4/raw.c#L1042">1042</a> };
<a name="L1043" href="source/net/ipv4/raw.c#L1043">1043</a> 
<a name="L1044" href="source/net/ipv4/raw.c#L1044">1044</a> int <a href="ident?i=raw_seq_open">raw_seq_open</a>(struct <a href="ident?i=inode">inode</a> *<a href="ident?i=ino">ino</a>, struct <a href="ident?i=file">file</a> *<a href="ident?i=file">file</a>,
<a name="L1045" href="source/net/ipv4/raw.c#L1045">1045</a>                  struct <a href="ident?i=raw_hashinfo">raw_hashinfo</a> *<a href="ident?i=h">h</a>, const struct <a href="ident?i=seq_operations">seq_operations</a> *<a href="ident?i=ops">ops</a>)
<a name="L1046" href="source/net/ipv4/raw.c#L1046">1046</a> {
<a name="L1047" href="source/net/ipv4/raw.c#L1047">1047</a>         int <a href="ident?i=err">err</a>;
<a name="L1048" href="source/net/ipv4/raw.c#L1048">1048</a>         struct <a href="ident?i=raw_iter_state">raw_iter_state</a> *<a href="ident?i=i">i</a>;
<a name="L1049" href="source/net/ipv4/raw.c#L1049">1049</a> 
<a name="L1050" href="source/net/ipv4/raw.c#L1050">1050</a>         <a href="ident?i=err">err</a> = <a href="ident?i=seq_open_net">seq_open_net</a>(<a href="ident?i=ino">ino</a>, <a href="ident?i=file">file</a>, <a href="ident?i=ops">ops</a>, sizeof(struct <a href="ident?i=raw_iter_state">raw_iter_state</a>));
<a name="L1051" href="source/net/ipv4/raw.c#L1051">1051</a>         if (<a href="ident?i=err">err</a> &lt; 0)
<a name="L1052" href="source/net/ipv4/raw.c#L1052">1052</a>                 return <a href="ident?i=err">err</a>;
<a name="L1053" href="source/net/ipv4/raw.c#L1053">1053</a> 
<a name="L1054" href="source/net/ipv4/raw.c#L1054">1054</a>         <a href="ident?i=i">i</a> = <a href="ident?i=raw_seq_private">raw_seq_private</a>((struct <a href="ident?i=seq_file">seq_file</a> *)<a href="ident?i=file">file</a>-&gt;<a href="ident?i=private_data">private_data</a>);
<a name="L1055" href="source/net/ipv4/raw.c#L1055">1055</a>         <a href="ident?i=i">i</a>-&gt;<a href="ident?i=h">h</a> = <a href="ident?i=h">h</a>;
<a name="L1056" href="source/net/ipv4/raw.c#L1056">1056</a>         return 0;
<a name="L1057" href="source/net/ipv4/raw.c#L1057">1057</a> }
<a name="L1058" href="source/net/ipv4/raw.c#L1058">1058</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=raw_seq_open">raw_seq_open</a>);
<a name="L1059" href="source/net/ipv4/raw.c#L1059">1059</a> 
<a name="L1060" href="source/net/ipv4/raw.c#L1060">1060</a> static int <a href="ident?i=raw_v4_seq_open">raw_v4_seq_open</a>(struct <a href="ident?i=inode">inode</a> *<a href="ident?i=inode">inode</a>, struct <a href="ident?i=file">file</a> *<a href="ident?i=file">file</a>)
<a name="L1061" href="source/net/ipv4/raw.c#L1061">1061</a> {
<a name="L1062" href="source/net/ipv4/raw.c#L1062">1062</a>         return <a href="ident?i=raw_seq_open">raw_seq_open</a>(<a href="ident?i=inode">inode</a>, <a href="ident?i=file">file</a>, &amp;<a href="ident?i=raw_v4_hashinfo">raw_v4_hashinfo</a>, &amp;<a href="ident?i=raw_seq_ops">raw_seq_ops</a>);
<a name="L1063" href="source/net/ipv4/raw.c#L1063">1063</a> }
<a name="L1064" href="source/net/ipv4/raw.c#L1064">1064</a> 
<a name="L1065" href="source/net/ipv4/raw.c#L1065">1065</a> static const struct <a href="ident?i=file_operations">file_operations</a> <a href="ident?i=raw_seq_fops">raw_seq_fops</a> = {
<a name="L1066" href="source/net/ipv4/raw.c#L1066">1066</a>         .owner   = <a href="ident?i=THIS_MODULE">THIS_MODULE</a>,
<a name="L1067" href="source/net/ipv4/raw.c#L1067">1067</a>         .<a href="ident?i=open">open</a>    = <a href="ident?i=raw_v4_seq_open">raw_v4_seq_open</a>,
<a name="L1068" href="source/net/ipv4/raw.c#L1068">1068</a>         .<a href="ident?i=read">read</a>    = <a href="ident?i=seq_read">seq_read</a>,
<a name="L1069" href="source/net/ipv4/raw.c#L1069">1069</a>         .llseek  = <a href="ident?i=seq_lseek">seq_lseek</a>,
<a name="L1070" href="source/net/ipv4/raw.c#L1070">1070</a>         .<a href="ident?i=release">release</a> = <a href="ident?i=seq_release_net">seq_release_net</a>,
<a name="L1071" href="source/net/ipv4/raw.c#L1071">1071</a> };
<a name="L1072" href="source/net/ipv4/raw.c#L1072">1072</a> 
<a name="L1073" href="source/net/ipv4/raw.c#L1073">1073</a> static <a href="ident?i=__net_init">__net_init</a> int <a href="ident?i=raw_init_net">raw_init_net</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>)
<a name="L1074" href="source/net/ipv4/raw.c#L1074">1074</a> {
<a name="L1075" href="source/net/ipv4/raw.c#L1075">1075</a>         if (!<a href="ident?i=proc_create">proc_create</a>(<i>"raw"</i>, <a href="ident?i=S_IRUGO">S_IRUGO</a>, <a href="ident?i=net">net</a>-&gt;proc_net, &amp;<a href="ident?i=raw_seq_fops">raw_seq_fops</a>))
<a name="L1076" href="source/net/ipv4/raw.c#L1076">1076</a>                 return -<a href="ident?i=ENOMEM">ENOMEM</a>;
<a name="L1077" href="source/net/ipv4/raw.c#L1077">1077</a> 
<a name="L1078" href="source/net/ipv4/raw.c#L1078">1078</a>         return 0;
<a name="L1079" href="source/net/ipv4/raw.c#L1079">1079</a> }
<a name="L1080" href="source/net/ipv4/raw.c#L1080">1080</a> 
<a name="L1081" href="source/net/ipv4/raw.c#L1081">1081</a> static <a href="ident?i=__net_exit">__net_exit</a> void <a href="ident?i=raw_exit_net">raw_exit_net</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>)
<a name="L1082" href="source/net/ipv4/raw.c#L1082">1082</a> {
<a name="L1083" href="source/net/ipv4/raw.c#L1083">1083</a>         <a href="ident?i=remove_proc_entry">remove_proc_entry</a>(<i>"raw"</i>, <a href="ident?i=net">net</a>-&gt;proc_net);
<a name="L1084" href="source/net/ipv4/raw.c#L1084">1084</a> }
<a name="L1085" href="source/net/ipv4/raw.c#L1085">1085</a> 
<a name="L1086" href="source/net/ipv4/raw.c#L1086">1086</a> static <a href="ident?i=__net_initdata">__net_initdata</a> struct <a href="ident?i=pernet_operations">pernet_operations</a> <a href="ident?i=raw_net_ops">raw_net_ops</a> = {
<a name="L1087" href="source/net/ipv4/raw.c#L1087">1087</a>         .<a href="ident?i=init">init</a> = <a href="ident?i=raw_init_net">raw_init_net</a>,
<a name="L1088" href="source/net/ipv4/raw.c#L1088">1088</a>         .<a href="ident?i=exit">exit</a> = <a href="ident?i=raw_exit_net">raw_exit_net</a>,
<a name="L1089" href="source/net/ipv4/raw.c#L1089">1089</a> };
<a name="L1090" href="source/net/ipv4/raw.c#L1090">1090</a> 
<a name="L1091" href="source/net/ipv4/raw.c#L1091">1091</a> int <a href="ident?i=__init">__init</a> <a href="ident?i=raw_proc_init">raw_proc_init</a>(void)
<a name="L1092" href="source/net/ipv4/raw.c#L1092">1092</a> {
<a name="L1093" href="source/net/ipv4/raw.c#L1093">1093</a>         return <a href="ident?i=register_pernet_subsys">register_pernet_subsys</a>(&amp;<a href="ident?i=raw_net_ops">raw_net_ops</a>);
<a name="L1094" href="source/net/ipv4/raw.c#L1094">1094</a> }
<a name="L1095" href="source/net/ipv4/raw.c#L1095">1095</a> 
<a name="L1096" href="source/net/ipv4/raw.c#L1096">1096</a> void <a href="ident?i=__init">__init</a> <a href="ident?i=raw_proc_exit">raw_proc_exit</a>(void)
<a name="L1097" href="source/net/ipv4/raw.c#L1097">1097</a> {
<a name="L1098" href="source/net/ipv4/raw.c#L1098">1098</a>         <a href="ident?i=unregister_pernet_subsys">unregister_pernet_subsys</a>(&amp;<a href="ident?i=raw_net_ops">raw_net_ops</a>);
<a name="L1099" href="source/net/ipv4/raw.c#L1099">1099</a> }
<a name="L1100" href="source/net/ipv4/raw.c#L1100">1100</a> #endif <b><i>/* CONFIG_PROC_FS */</i></b>
<a name="L1101" href="source/net/ipv4/raw.c#L1101">1101</a> </pre></div><p>
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
