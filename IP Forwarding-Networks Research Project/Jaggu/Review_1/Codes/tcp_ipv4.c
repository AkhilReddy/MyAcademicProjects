<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title>Linux/net/ipv4/tcp_ipv4.c - Linux Cross Reference - Free Electrons</title>
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
		 &nbsp;&bull;&nbsp;<b><i>source navigation</i></b> &nbsp;&bull;&nbsp;<a href="diff/net/ipv4/tcp_ipv4.c">diff markup</a> &nbsp;&bull;&nbsp;<a href="ident">identifier search</a> &nbsp;&bull;&nbsp;<a href="search">freetext search</a> &nbsp;&bull;&nbsp;
		</p>
	</div>
</div>

<div id="topbar">
  
  <p>Version: &nbsp;<a href="source/net/ipv4/tcp_ipv4.c?v=2.0.40">2.0.40</a>&nbsp;<a href="source/net/ipv4/tcp_ipv4.c?v=2.2.26">2.2.26</a>&nbsp;<a href="source/net/ipv4/tcp_ipv4.c?v=2.4.37">2.4.37</a>&nbsp;<a href="source/net/ipv4/tcp_ipv4.c?v=3.5">3.5</a>&nbsp;<a href="source/net/ipv4/tcp_ipv4.c?v=3.6">3.6</a>&nbsp;<a href="source/net/ipv4/tcp_ipv4.c?v=3.7">3.7</a>&nbsp;<a href="source/net/ipv4/tcp_ipv4.c?v=3.8">3.8</a>&nbsp;<a href="source/net/ipv4/tcp_ipv4.c?v=3.9">3.9</a>&nbsp;<a href="source/net/ipv4/tcp_ipv4.c?v=3.10">3.10</a>&nbsp;<a href="source/net/ipv4/tcp_ipv4.c?v=3.11">3.11</a>&nbsp;<a href="source/net/ipv4/tcp_ipv4.c?v=3.12">3.12</a>&nbsp;<a href="source/net/ipv4/tcp_ipv4.c?v=3.13">3.13</a>&nbsp;<a href="source/net/ipv4/tcp_ipv4.c?v=3.14">3.14</a>&nbsp;<a href="source/net/ipv4/tcp_ipv4.c?v=3.15">3.15</a>&nbsp;<a href="source/net/ipv4/tcp_ipv4.c?v=3.16">3.16</a>&nbsp;<a href="source/net/ipv4/tcp_ipv4.c?v=3.17">3.17</a>&nbsp;<a href="source/net/ipv4/tcp_ipv4.c?v=3.18">3.18</a>&nbsp;<a href="source/net/ipv4/tcp_ipv4.c?v=3.19">3.19</a>&nbsp;<a href="source/net/ipv4/tcp_ipv4.c?v=4.0">4.0</a>&nbsp;<b><i>4.1</i></b></p>
  
</div>

<h1><a href="source/">Linux</a>/<a href="source/net/">net</a>/<a href="source/net/ipv4/">ipv4</a>/<a href="source/net/ipv4/tcp_ipv4.c">tcp_ipv4.c</a></h1>
<div id="lxrcode"><pre>  <a name="L1" href="source/net/ipv4/tcp_ipv4.c#L1">1</a> <b><i>/*</i></b>
  <a name="L2" href="source/net/ipv4/tcp_ipv4.c#L2">2</a> <b><i> * INET         An implementation of the TCP/IP protocol suite for the LINUX</i></b>
  <a name="L3" href="source/net/ipv4/tcp_ipv4.c#L3">3</a> <b><i> *              operating system.  INET is implemented using the  BSD Socket</i></b>
  <a name="L4" href="source/net/ipv4/tcp_ipv4.c#L4">4</a> <b><i> *              interface as the means of communication with the user level.</i></b>
  <a name="L5" href="source/net/ipv4/tcp_ipv4.c#L5">5</a> <b><i> *</i></b>
  <a name="L6" href="source/net/ipv4/tcp_ipv4.c#L6">6</a> <b><i> *              Implementation of the Transmission Control Protocol(TCP).</i></b>
  <a name="L7" href="source/net/ipv4/tcp_ipv4.c#L7">7</a> <b><i> *</i></b>
  <a name="L8" href="source/net/ipv4/tcp_ipv4.c#L8">8</a> <b><i> *              IPv4 specific functions</i></b>
  <a name="L9" href="source/net/ipv4/tcp_ipv4.c#L9">9</a> <b><i> *</i></b>
 <a name="L10" href="source/net/ipv4/tcp_ipv4.c#L10">10</a> <b><i> *</i></b>
 <a name="L11" href="source/net/ipv4/tcp_ipv4.c#L11">11</a> <b><i> *              code split from:</i></b>
 <a name="L12" href="source/net/ipv4/tcp_ipv4.c#L12">12</a> <b><i> *              linux/ipv4/tcp.c</i></b>
 <a name="L13" href="source/net/ipv4/tcp_ipv4.c#L13">13</a> <b><i> *              linux/ipv4/tcp_input.c</i></b>
 <a name="L14" href="source/net/ipv4/tcp_ipv4.c#L14">14</a> <b><i> *              linux/ipv4/tcp_output.c</i></b>
 <a name="L15" href="source/net/ipv4/tcp_ipv4.c#L15">15</a> <b><i> *</i></b>
 <a name="L16" href="source/net/ipv4/tcp_ipv4.c#L16">16</a> <b><i> *              See tcp.c for author information</i></b>
 <a name="L17" href="source/net/ipv4/tcp_ipv4.c#L17">17</a> <b><i> *</i></b>
 <a name="L18" href="source/net/ipv4/tcp_ipv4.c#L18">18</a> <b><i> *      This program is free software; you can redistribute it and/or</i></b>
 <a name="L19" href="source/net/ipv4/tcp_ipv4.c#L19">19</a> <b><i> *      modify it under the terms of the GNU General Public License</i></b>
 <a name="L20" href="source/net/ipv4/tcp_ipv4.c#L20">20</a> <b><i> *      as published by the Free Software Foundation; either version</i></b>
 <a name="L21" href="source/net/ipv4/tcp_ipv4.c#L21">21</a> <b><i> *      2 of the License, or (at your option) any later version.</i></b>
 <a name="L22" href="source/net/ipv4/tcp_ipv4.c#L22">22</a> <b><i> */</i></b>
 <a name="L23" href="source/net/ipv4/tcp_ipv4.c#L23">23</a> 
 <a name="L24" href="source/net/ipv4/tcp_ipv4.c#L24">24</a> <b><i>/*</i></b>
 <a name="L25" href="source/net/ipv4/tcp_ipv4.c#L25">25</a> <b><i> * Changes:</i></b>
 <a name="L26" href="source/net/ipv4/tcp_ipv4.c#L26">26</a> <b><i> *              David S. Miller :       New socket lookup architecture.</i></b>
 <a name="L27" href="source/net/ipv4/tcp_ipv4.c#L27">27</a> <b><i> *                                      This code is dedicated to John Dyson.</i></b>
 <a name="L28" href="source/net/ipv4/tcp_ipv4.c#L28">28</a> <b><i> *              David S. Miller :       Change semantics of established hash,</i></b>
 <a name="L29" href="source/net/ipv4/tcp_ipv4.c#L29">29</a> <b><i> *                                      half is devoted to TIME_WAIT sockets</i></b>
 <a name="L30" href="source/net/ipv4/tcp_ipv4.c#L30">30</a> <b><i> *                                      and the rest go in the other half.</i></b>
 <a name="L31" href="source/net/ipv4/tcp_ipv4.c#L31">31</a> <b><i> *              Andi Kleen :            Add support for syncookies and fixed</i></b>
 <a name="L32" href="source/net/ipv4/tcp_ipv4.c#L32">32</a> <b><i> *                                      some bugs: ip options weren't passed to</i></b>
 <a name="L33" href="source/net/ipv4/tcp_ipv4.c#L33">33</a> <b><i> *                                      the TCP layer, missed a check for an</i></b>
 <a name="L34" href="source/net/ipv4/tcp_ipv4.c#L34">34</a> <b><i> *                                      ACK bit.</i></b>
 <a name="L35" href="source/net/ipv4/tcp_ipv4.c#L35">35</a> <b><i> *              Andi Kleen :            Implemented fast path mtu discovery.</i></b>
 <a name="L36" href="source/net/ipv4/tcp_ipv4.c#L36">36</a> <b><i> *                                      Fixed many serious bugs in the</i></b>
 <a name="L37" href="source/net/ipv4/tcp_ipv4.c#L37">37</a> <b><i> *                                      request_sock handling and moved</i></b>
 <a name="L38" href="source/net/ipv4/tcp_ipv4.c#L38">38</a> <b><i> *                                      most of it into the af independent code.</i></b>
 <a name="L39" href="source/net/ipv4/tcp_ipv4.c#L39">39</a> <b><i> *                                      Added tail drop and some other bugfixes.</i></b>
 <a name="L40" href="source/net/ipv4/tcp_ipv4.c#L40">40</a> <b><i> *                                      Added new listen semantics.</i></b>
 <a name="L41" href="source/net/ipv4/tcp_ipv4.c#L41">41</a> <b><i> *              Mike McLagan    :       Routing by source</i></b>
 <a name="L42" href="source/net/ipv4/tcp_ipv4.c#L42">42</a> <b><i> *      Juan Jose Ciarlante:            ip_dynaddr bits</i></b>
 <a name="L43" href="source/net/ipv4/tcp_ipv4.c#L43">43</a> <b><i> *              Andi Kleen:             various fixes.</i></b>
 <a name="L44" href="source/net/ipv4/tcp_ipv4.c#L44">44</a> <b><i> *      Vitaly E. Lavrov        :       Transparent proxy revived after year</i></b>
 <a name="L45" href="source/net/ipv4/tcp_ipv4.c#L45">45</a> <b><i> *                                      coma.</i></b>
 <a name="L46" href="source/net/ipv4/tcp_ipv4.c#L46">46</a> <b><i> *      Andi Kleen              :       Fix new listen.</i></b>
 <a name="L47" href="source/net/ipv4/tcp_ipv4.c#L47">47</a> <b><i> *      Andi Kleen              :       Fix accept error reporting.</i></b>
 <a name="L48" href="source/net/ipv4/tcp_ipv4.c#L48">48</a> <b><i> *      YOSHIFUJI Hideaki @USAGI and:   Support IPV6_V6ONLY socket option, which</i></b>
 <a name="L49" href="source/net/ipv4/tcp_ipv4.c#L49">49</a> <b><i> *      Alexey Kuznetsov                allow both IPv4 and IPv6 sockets to bind</i></b>
 <a name="L50" href="source/net/ipv4/tcp_ipv4.c#L50">50</a> <b><i> *                                      a single port at the same time.</i></b>
 <a name="L51" href="source/net/ipv4/tcp_ipv4.c#L51">51</a> <b><i> */</i></b>
 <a name="L52" href="source/net/ipv4/tcp_ipv4.c#L52">52</a> 
 <a name="L53" href="source/net/ipv4/tcp_ipv4.c#L53">53</a> #define <a href="ident?i=pr_fmt">pr_fmt</a>(<a href="ident?i=fmt">fmt</a>) <i>"TCP: "</i> <a href="ident?i=fmt">fmt</a>
 <a name="L54" href="source/net/ipv4/tcp_ipv4.c#L54">54</a> 
 <a name="L55" href="source/net/ipv4/tcp_ipv4.c#L55">55</a> #include &lt;linux/bottom_half.h&gt;
 <a name="L56" href="source/net/ipv4/tcp_ipv4.c#L56">56</a> #include &lt;linux/types.h&gt;
 <a name="L57" href="source/net/ipv4/tcp_ipv4.c#L57">57</a> #include &lt;linux/fcntl.h&gt;
 <a name="L58" href="source/net/ipv4/tcp_ipv4.c#L58">58</a> #include &lt;linux/module.h&gt;
 <a name="L59" href="source/net/ipv4/tcp_ipv4.c#L59">59</a> #include &lt;linux/random.h&gt;
 <a name="L60" href="source/net/ipv4/tcp_ipv4.c#L60">60</a> #include &lt;linux/cache.h&gt;
 <a name="L61" href="source/net/ipv4/tcp_ipv4.c#L61">61</a> #include &lt;linux/jhash.h&gt;
 <a name="L62" href="source/net/ipv4/tcp_ipv4.c#L62">62</a> #include &lt;linux/init.h&gt;
 <a name="L63" href="source/net/ipv4/tcp_ipv4.c#L63">63</a> #include &lt;linux/times.h&gt;
 <a name="L64" href="source/net/ipv4/tcp_ipv4.c#L64">64</a> #include &lt;linux/slab.h&gt;
 <a name="L65" href="source/net/ipv4/tcp_ipv4.c#L65">65</a> 
 <a name="L66" href="source/net/ipv4/tcp_ipv4.c#L66">66</a> #include &lt;net/net_namespace.h&gt;
 <a name="L67" href="source/net/ipv4/tcp_ipv4.c#L67">67</a> #include &lt;net/icmp.h&gt;
 <a name="L68" href="source/net/ipv4/tcp_ipv4.c#L68">68</a> #include &lt;net/inet_hashtables.h&gt;
 <a name="L69" href="source/net/ipv4/tcp_ipv4.c#L69">69</a> #include &lt;net/tcp.h&gt;
 <a name="L70" href="source/net/ipv4/tcp_ipv4.c#L70">70</a> #include &lt;net/transp_v6.h&gt;
 <a name="L71" href="source/net/ipv4/tcp_ipv4.c#L71">71</a> #include &lt;net/ipv6.h&gt;
 <a name="L72" href="source/net/ipv4/tcp_ipv4.c#L72">72</a> #include &lt;net/inet_common.h&gt;
 <a name="L73" href="source/net/ipv4/tcp_ipv4.c#L73">73</a> #include &lt;net/timewait_sock.h&gt;
 <a name="L74" href="source/net/ipv4/tcp_ipv4.c#L74">74</a> #include &lt;net/xfrm.h&gt;
 <a name="L75" href="source/net/ipv4/tcp_ipv4.c#L75">75</a> #include &lt;net/secure_seq.h&gt;
 <a name="L76" href="source/net/ipv4/tcp_ipv4.c#L76">76</a> #include &lt;net/tcp_memcontrol.h&gt;
 <a name="L77" href="source/net/ipv4/tcp_ipv4.c#L77">77</a> #include &lt;net/busy_poll.h&gt;
 <a name="L78" href="source/net/ipv4/tcp_ipv4.c#L78">78</a> 
 <a name="L79" href="source/net/ipv4/tcp_ipv4.c#L79">79</a> #include &lt;linux/inet.h&gt;
 <a name="L80" href="source/net/ipv4/tcp_ipv4.c#L80">80</a> #include &lt;linux/ipv6.h&gt;
 <a name="L81" href="source/net/ipv4/tcp_ipv4.c#L81">81</a> #include &lt;linux/stddef.h&gt;
 <a name="L82" href="source/net/ipv4/tcp_ipv4.c#L82">82</a> #include &lt;linux/proc_fs.h&gt;
 <a name="L83" href="source/net/ipv4/tcp_ipv4.c#L83">83</a> #include &lt;linux/seq_file.h&gt;
 <a name="L84" href="source/net/ipv4/tcp_ipv4.c#L84">84</a> 
 <a name="L85" href="source/net/ipv4/tcp_ipv4.c#L85">85</a> #include &lt;linux/crypto.h&gt;
 <a name="L86" href="source/net/ipv4/tcp_ipv4.c#L86">86</a> #include &lt;linux/scatterlist.h&gt;
 <a name="L87" href="source/net/ipv4/tcp_ipv4.c#L87">87</a> 
 <a name="L88" href="source/net/ipv4/tcp_ipv4.c#L88">88</a> int <a href="ident?i=sysctl_tcp_tw_reuse">sysctl_tcp_tw_reuse</a> <a href="ident?i=__read_mostly">__read_mostly</a>;
 <a name="L89" href="source/net/ipv4/tcp_ipv4.c#L89">89</a> int <a href="ident?i=sysctl_tcp_low_latency">sysctl_tcp_low_latency</a> <a href="ident?i=__read_mostly">__read_mostly</a>;
 <a name="L90" href="source/net/ipv4/tcp_ipv4.c#L90">90</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=sysctl_tcp_low_latency">sysctl_tcp_low_latency</a>);
 <a name="L91" href="source/net/ipv4/tcp_ipv4.c#L91">91</a> 
 <a name="L92" href="source/net/ipv4/tcp_ipv4.c#L92">92</a> #ifdef CONFIG_TCP_MD5SIG
 <a name="L93" href="source/net/ipv4/tcp_ipv4.c#L93">93</a> static int <a href="ident?i=tcp_v4_md5_hash_hdr">tcp_v4_md5_hash_hdr</a>(char *md5_hash, const struct <a href="ident?i=tcp_md5sig_key">tcp_md5sig_key</a> *<a href="ident?i=key">key</a>,
 <a name="L94" href="source/net/ipv4/tcp_ipv4.c#L94">94</a>                                <a href="ident?i=__be32">__be32</a> <a href="ident?i=daddr">daddr</a>, <a href="ident?i=__be32">__be32</a> <a href="ident?i=saddr">saddr</a>, const struct <a href="ident?i=tcphdr">tcphdr</a> *<a href="ident?i=th">th</a>);
 <a name="L95" href="source/net/ipv4/tcp_ipv4.c#L95">95</a> #endif
 <a name="L96" href="source/net/ipv4/tcp_ipv4.c#L96">96</a> 
 <a name="L97" href="source/net/ipv4/tcp_ipv4.c#L97">97</a> struct <a href="ident?i=inet_hashinfo">inet_hashinfo</a> <a href="ident?i=tcp_hashinfo">tcp_hashinfo</a>;
 <a name="L98" href="source/net/ipv4/tcp_ipv4.c#L98">98</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=tcp_hashinfo">tcp_hashinfo</a>);
 <a name="L99" href="source/net/ipv4/tcp_ipv4.c#L99">99</a> 
<a name="L100" href="source/net/ipv4/tcp_ipv4.c#L100">100</a> static  <a href="ident?i=__u32">__u32</a> <a href="ident?i=tcp_v4_init_sequence">tcp_v4_init_sequence</a>(const struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L101" href="source/net/ipv4/tcp_ipv4.c#L101">101</a> {
<a name="L102" href="source/net/ipv4/tcp_ipv4.c#L102">102</a>         return <a href="ident?i=secure_tcp_sequence_number">secure_tcp_sequence_number</a>(<a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=daddr">daddr</a>,
<a name="L103" href="source/net/ipv4/tcp_ipv4.c#L103">103</a>                                           <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=saddr">saddr</a>,
<a name="L104" href="source/net/ipv4/tcp_ipv4.c#L104">104</a>                                           <a href="ident?i=tcp_hdr">tcp_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=dest">dest</a>,
<a name="L105" href="source/net/ipv4/tcp_ipv4.c#L105">105</a>                                           <a href="ident?i=tcp_hdr">tcp_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;source);
<a name="L106" href="source/net/ipv4/tcp_ipv4.c#L106">106</a> }
<a name="L107" href="source/net/ipv4/tcp_ipv4.c#L107">107</a> 
<a name="L108" href="source/net/ipv4/tcp_ipv4.c#L108">108</a> int <a href="ident?i=tcp_twsk_unique">tcp_twsk_unique</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=sock">sock</a> *sktw, void *twp)
<a name="L109" href="source/net/ipv4/tcp_ipv4.c#L109">109</a> {
<a name="L110" href="source/net/ipv4/tcp_ipv4.c#L110">110</a>         const struct <a href="ident?i=tcp_timewait_sock">tcp_timewait_sock</a> *tcptw = <a href="ident?i=tcp_twsk">tcp_twsk</a>(sktw);
<a name="L111" href="source/net/ipv4/tcp_ipv4.c#L111">111</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L112" href="source/net/ipv4/tcp_ipv4.c#L112">112</a> 
<a name="L113" href="source/net/ipv4/tcp_ipv4.c#L113">113</a>         <b><i>/* With PAWS, it is safe from the viewpoint</i></b>
<a name="L114" href="source/net/ipv4/tcp_ipv4.c#L114">114</a> <b><i>           of data integrity. Even without PAWS it is safe provided sequence</i></b>
<a name="L115" href="source/net/ipv4/tcp_ipv4.c#L115">115</a> <b><i>           spaces do not overlap i.e. at data rates &lt;= 80Mbit/sec.</i></b>
<a name="L116" href="source/net/ipv4/tcp_ipv4.c#L116">116</a> <b><i></i></b>
<a name="L117" href="source/net/ipv4/tcp_ipv4.c#L117">117</a> <b><i>           Actually, the idea is close to VJ's one, only timestamp cache is</i></b>
<a name="L118" href="source/net/ipv4/tcp_ipv4.c#L118">118</a> <b><i>           held not per host, but per port pair and TW bucket is used as state</i></b>
<a name="L119" href="source/net/ipv4/tcp_ipv4.c#L119">119</a> <b><i>           holder.</i></b>
<a name="L120" href="source/net/ipv4/tcp_ipv4.c#L120">120</a> <b><i></i></b>
<a name="L121" href="source/net/ipv4/tcp_ipv4.c#L121">121</a> <b><i>           If TW bucket has been already destroyed we fall back to VJ's scheme</i></b>
<a name="L122" href="source/net/ipv4/tcp_ipv4.c#L122">122</a> <b><i>           and use initial timestamp retrieved from peer table.</i></b>
<a name="L123" href="source/net/ipv4/tcp_ipv4.c#L123">123</a> <b><i>         */</i></b>
<a name="L124" href="source/net/ipv4/tcp_ipv4.c#L124">124</a>         if (tcptw-&gt;tw_ts_recent_stamp &amp;&amp;
<a name="L125" href="source/net/ipv4/tcp_ipv4.c#L125">125</a>             (!twp || (<a href="ident?i=sysctl_tcp_tw_reuse">sysctl_tcp_tw_reuse</a> &amp;&amp;
<a name="L126" href="source/net/ipv4/tcp_ipv4.c#L126">126</a>                              <a href="ident?i=get_seconds">get_seconds</a>() - tcptw-&gt;tw_ts_recent_stamp &gt; 1))) {
<a name="L127" href="source/net/ipv4/tcp_ipv4.c#L127">127</a>                 <a href="ident?i=tp">tp</a>-&gt;write_seq = tcptw-&gt;tw_snd_nxt + 65535 + 2;
<a name="L128" href="source/net/ipv4/tcp_ipv4.c#L128">128</a>                 if (<a href="ident?i=tp">tp</a>-&gt;write_seq == 0)
<a name="L129" href="source/net/ipv4/tcp_ipv4.c#L129">129</a>                         <a href="ident?i=tp">tp</a>-&gt;write_seq = 1;
<a name="L130" href="source/net/ipv4/tcp_ipv4.c#L130">130</a>                 <a href="ident?i=tp">tp</a>-&gt;rx_opt.ts_recent       = tcptw-&gt;tw_ts_recent;
<a name="L131" href="source/net/ipv4/tcp_ipv4.c#L131">131</a>                 <a href="ident?i=tp">tp</a>-&gt;rx_opt.ts_recent_stamp = tcptw-&gt;tw_ts_recent_stamp;
<a name="L132" href="source/net/ipv4/tcp_ipv4.c#L132">132</a>                 <a href="ident?i=sock_hold">sock_hold</a>(sktw);
<a name="L133" href="source/net/ipv4/tcp_ipv4.c#L133">133</a>                 return 1;
<a name="L134" href="source/net/ipv4/tcp_ipv4.c#L134">134</a>         }
<a name="L135" href="source/net/ipv4/tcp_ipv4.c#L135">135</a> 
<a name="L136" href="source/net/ipv4/tcp_ipv4.c#L136">136</a>         return 0;
<a name="L137" href="source/net/ipv4/tcp_ipv4.c#L137">137</a> }
<a name="L138" href="source/net/ipv4/tcp_ipv4.c#L138">138</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=tcp_twsk_unique">tcp_twsk_unique</a>);
<a name="L139" href="source/net/ipv4/tcp_ipv4.c#L139">139</a> 
<a name="L140" href="source/net/ipv4/tcp_ipv4.c#L140">140</a> <b><i>/* This will initiate an outgoing connection. */</i></b>
<a name="L141" href="source/net/ipv4/tcp_ipv4.c#L141">141</a> int <a href="ident?i=tcp_v4_connect">tcp_v4_connect</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=sockaddr">sockaddr</a> *<a href="ident?i=uaddr">uaddr</a>, int addr_len)
<a name="L142" href="source/net/ipv4/tcp_ipv4.c#L142">142</a> {
<a name="L143" href="source/net/ipv4/tcp_ipv4.c#L143">143</a>         struct <a href="ident?i=sockaddr_in">sockaddr_in</a> *usin = (struct <a href="ident?i=sockaddr_in">sockaddr_in</a> *)<a href="ident?i=uaddr">uaddr</a>;
<a name="L144" href="source/net/ipv4/tcp_ipv4.c#L144">144</a>         struct <a href="ident?i=inet_sock">inet_sock</a> *inet = <a href="ident?i=inet_sk">inet_sk</a>(sk);
<a name="L145" href="source/net/ipv4/tcp_ipv4.c#L145">145</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L146" href="source/net/ipv4/tcp_ipv4.c#L146">146</a>         <a href="ident?i=__be16">__be16</a> orig_sport, orig_dport;
<a name="L147" href="source/net/ipv4/tcp_ipv4.c#L147">147</a>         <a href="ident?i=__be32">__be32</a> <a href="ident?i=daddr">daddr</a>, nexthop;
<a name="L148" href="source/net/ipv4/tcp_ipv4.c#L148">148</a>         struct <a href="ident?i=flowi4">flowi4</a> *fl4;
<a name="L149" href="source/net/ipv4/tcp_ipv4.c#L149">149</a>         struct <a href="ident?i=rtable">rtable</a> *<a href="ident?i=rt">rt</a>;
<a name="L150" href="source/net/ipv4/tcp_ipv4.c#L150">150</a>         int <a href="ident?i=err">err</a>;
<a name="L151" href="source/net/ipv4/tcp_ipv4.c#L151">151</a>         struct <a href="ident?i=ip_options_rcu">ip_options_rcu</a> *inet_opt;
<a name="L152" href="source/net/ipv4/tcp_ipv4.c#L152">152</a> 
<a name="L153" href="source/net/ipv4/tcp_ipv4.c#L153">153</a>         if (addr_len &lt; sizeof(struct <a href="ident?i=sockaddr_in">sockaddr_in</a>))
<a name="L154" href="source/net/ipv4/tcp_ipv4.c#L154">154</a>                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L155" href="source/net/ipv4/tcp_ipv4.c#L155">155</a> 
<a name="L156" href="source/net/ipv4/tcp_ipv4.c#L156">156</a>         if (usin-&gt;sin_family != <a href="ident?i=AF_INET">AF_INET</a>)
<a name="L157" href="source/net/ipv4/tcp_ipv4.c#L157">157</a>                 return -<a href="ident?i=EAFNOSUPPORT">EAFNOSUPPORT</a>;
<a name="L158" href="source/net/ipv4/tcp_ipv4.c#L158">158</a> 
<a name="L159" href="source/net/ipv4/tcp_ipv4.c#L159">159</a>         nexthop = <a href="ident?i=daddr">daddr</a> = usin-&gt;sin_addr.s_addr;
<a name="L160" href="source/net/ipv4/tcp_ipv4.c#L160">160</a>         inet_opt = <a href="ident?i=rcu_dereference_protected">rcu_dereference_protected</a>(inet-&gt;inet_opt,
<a name="L161" href="source/net/ipv4/tcp_ipv4.c#L161">161</a>                                              <a href="ident?i=sock_owned_by_user">sock_owned_by_user</a>(sk));
<a name="L162" href="source/net/ipv4/tcp_ipv4.c#L162">162</a>         if (inet_opt &amp;&amp; inet_opt-&gt;opt.<a href="ident?i=srr">srr</a>) {
<a name="L163" href="source/net/ipv4/tcp_ipv4.c#L163">163</a>                 if (!<a href="ident?i=daddr">daddr</a>)
<a name="L164" href="source/net/ipv4/tcp_ipv4.c#L164">164</a>                         return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L165" href="source/net/ipv4/tcp_ipv4.c#L165">165</a>                 nexthop = inet_opt-&gt;opt.faddr;
<a name="L166" href="source/net/ipv4/tcp_ipv4.c#L166">166</a>         }
<a name="L167" href="source/net/ipv4/tcp_ipv4.c#L167">167</a> 
<a name="L168" href="source/net/ipv4/tcp_ipv4.c#L168">168</a>         orig_sport = inet-&gt;inet_sport;
<a name="L169" href="source/net/ipv4/tcp_ipv4.c#L169">169</a>         orig_dport = usin-&gt;sin_port;
<a name="L170" href="source/net/ipv4/tcp_ipv4.c#L170">170</a>         fl4 = &amp;inet-&gt;cork.fl.u.ip4;
<a name="L171" href="source/net/ipv4/tcp_ipv4.c#L171">171</a>         <a href="ident?i=rt">rt</a> = <a href="ident?i=ip_route_connect">ip_route_connect</a>(fl4, nexthop, inet-&gt;inet_saddr,
<a name="L172" href="source/net/ipv4/tcp_ipv4.c#L172">172</a>                               <a href="ident?i=RT_CONN_FLAGS">RT_CONN_FLAGS</a>(sk), sk-&gt;<a href="ident?i=sk_bound_dev_if">sk_bound_dev_if</a>,
<a name="L173" href="source/net/ipv4/tcp_ipv4.c#L173">173</a>                               <a href="ident?i=IPPROTO_TCP">IPPROTO_TCP</a>,
<a name="L174" href="source/net/ipv4/tcp_ipv4.c#L174">174</a>                               orig_sport, orig_dport, sk);
<a name="L175" href="source/net/ipv4/tcp_ipv4.c#L175">175</a>         if (<a href="ident?i=IS_ERR">IS_ERR</a>(<a href="ident?i=rt">rt</a>)) {
<a name="L176" href="source/net/ipv4/tcp_ipv4.c#L176">176</a>                 <a href="ident?i=err">err</a> = <a href="ident?i=PTR_ERR">PTR_ERR</a>(<a href="ident?i=rt">rt</a>);
<a name="L177" href="source/net/ipv4/tcp_ipv4.c#L177">177</a>                 if (<a href="ident?i=err">err</a> == -<a href="ident?i=ENETUNREACH">ENETUNREACH</a>)
<a name="L178" href="source/net/ipv4/tcp_ipv4.c#L178">178</a>                         <a href="ident?i=IP_INC_STATS">IP_INC_STATS</a>(<a href="ident?i=sock_net">sock_net</a>(sk), IPSTATS_MIB_OUTNOROUTES);
<a name="L179" href="source/net/ipv4/tcp_ipv4.c#L179">179</a>                 return <a href="ident?i=err">err</a>;
<a name="L180" href="source/net/ipv4/tcp_ipv4.c#L180">180</a>         }
<a name="L181" href="source/net/ipv4/tcp_ipv4.c#L181">181</a> 
<a name="L182" href="source/net/ipv4/tcp_ipv4.c#L182">182</a>         if (<a href="ident?i=rt">rt</a>-&gt;rt_flags &amp; (<a href="ident?i=RTCF_MULTICAST">RTCF_MULTICAST</a> | <a href="ident?i=RTCF_BROADCAST">RTCF_BROADCAST</a>)) {
<a name="L183" href="source/net/ipv4/tcp_ipv4.c#L183">183</a>                 <a href="ident?i=ip_rt_put">ip_rt_put</a>(<a href="ident?i=rt">rt</a>);
<a name="L184" href="source/net/ipv4/tcp_ipv4.c#L184">184</a>                 return -<a href="ident?i=ENETUNREACH">ENETUNREACH</a>;
<a name="L185" href="source/net/ipv4/tcp_ipv4.c#L185">185</a>         }
<a name="L186" href="source/net/ipv4/tcp_ipv4.c#L186">186</a> 
<a name="L187" href="source/net/ipv4/tcp_ipv4.c#L187">187</a>         if (!inet_opt || !inet_opt-&gt;opt.<a href="ident?i=srr">srr</a>)
<a name="L188" href="source/net/ipv4/tcp_ipv4.c#L188">188</a>                 <a href="ident?i=daddr">daddr</a> = fl4-&gt;<a href="ident?i=daddr">daddr</a>;
<a name="L189" href="source/net/ipv4/tcp_ipv4.c#L189">189</a> 
<a name="L190" href="source/net/ipv4/tcp_ipv4.c#L190">190</a>         if (!inet-&gt;inet_saddr)
<a name="L191" href="source/net/ipv4/tcp_ipv4.c#L191">191</a>                 inet-&gt;inet_saddr = fl4-&gt;<a href="ident?i=saddr">saddr</a>;
<a name="L192" href="source/net/ipv4/tcp_ipv4.c#L192">192</a>         <a href="ident?i=sk_rcv_saddr_set">sk_rcv_saddr_set</a>(sk, inet-&gt;inet_saddr);
<a name="L193" href="source/net/ipv4/tcp_ipv4.c#L193">193</a> 
<a name="L194" href="source/net/ipv4/tcp_ipv4.c#L194">194</a>         if (<a href="ident?i=tp">tp</a>-&gt;rx_opt.ts_recent_stamp &amp;&amp; inet-&gt;<a href="ident?i=inet_daddr">inet_daddr</a> != <a href="ident?i=daddr">daddr</a>) {
<a name="L195" href="source/net/ipv4/tcp_ipv4.c#L195">195</a>                 <b><i>/* Reset inherited state */</i></b>
<a name="L196" href="source/net/ipv4/tcp_ipv4.c#L196">196</a>                 <a href="ident?i=tp">tp</a>-&gt;rx_opt.ts_recent       = 0;
<a name="L197" href="source/net/ipv4/tcp_ipv4.c#L197">197</a>                 <a href="ident?i=tp">tp</a>-&gt;rx_opt.ts_recent_stamp = 0;
<a name="L198" href="source/net/ipv4/tcp_ipv4.c#L198">198</a>                 if (<a href="ident?i=likely">likely</a>(!<a href="ident?i=tp">tp</a>-&gt;repair))
<a name="L199" href="source/net/ipv4/tcp_ipv4.c#L199">199</a>                         <a href="ident?i=tp">tp</a>-&gt;write_seq      = 0;
<a name="L200" href="source/net/ipv4/tcp_ipv4.c#L200">200</a>         }
<a name="L201" href="source/net/ipv4/tcp_ipv4.c#L201">201</a> 
<a name="L202" href="source/net/ipv4/tcp_ipv4.c#L202">202</a>         if (<a href="ident?i=tcp_death_row">tcp_death_row</a>.sysctl_tw_recycle &amp;&amp;
<a name="L203" href="source/net/ipv4/tcp_ipv4.c#L203">203</a>             !<a href="ident?i=tp">tp</a>-&gt;rx_opt.ts_recent_stamp &amp;&amp; fl4-&gt;<a href="ident?i=daddr">daddr</a> == <a href="ident?i=daddr">daddr</a>)
<a name="L204" href="source/net/ipv4/tcp_ipv4.c#L204">204</a>                 <a href="ident?i=tcp_fetch_timewait_stamp">tcp_fetch_timewait_stamp</a>(sk, &amp;<a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>);
<a name="L205" href="source/net/ipv4/tcp_ipv4.c#L205">205</a> 
<a name="L206" href="source/net/ipv4/tcp_ipv4.c#L206">206</a>         inet-&gt;<a href="ident?i=inet_dport">inet_dport</a> = usin-&gt;sin_port;
<a name="L207" href="source/net/ipv4/tcp_ipv4.c#L207">207</a>         <a href="ident?i=sk_daddr_set">sk_daddr_set</a>(sk, <a href="ident?i=daddr">daddr</a>);
<a name="L208" href="source/net/ipv4/tcp_ipv4.c#L208">208</a> 
<a name="L209" href="source/net/ipv4/tcp_ipv4.c#L209">209</a>         <a href="ident?i=inet_csk">inet_csk</a>(sk)-&gt;icsk_ext_hdr_len = 0;
<a name="L210" href="source/net/ipv4/tcp_ipv4.c#L210">210</a>         if (inet_opt)
<a name="L211" href="source/net/ipv4/tcp_ipv4.c#L211">211</a>                 <a href="ident?i=inet_csk">inet_csk</a>(sk)-&gt;icsk_ext_hdr_len = inet_opt-&gt;opt.<a href="ident?i=optlen">optlen</a>;
<a name="L212" href="source/net/ipv4/tcp_ipv4.c#L212">212</a> 
<a name="L213" href="source/net/ipv4/tcp_ipv4.c#L213">213</a>         <a href="ident?i=tp">tp</a>-&gt;rx_opt.mss_clamp = <a href="ident?i=TCP_MSS_DEFAULT">TCP_MSS_DEFAULT</a>;
<a name="L214" href="source/net/ipv4/tcp_ipv4.c#L214">214</a> 
<a name="L215" href="source/net/ipv4/tcp_ipv4.c#L215">215</a>         <b><i>/* Socket identity is still unknown (sport may be zero).</i></b>
<a name="L216" href="source/net/ipv4/tcp_ipv4.c#L216">216</a> <b><i>         * However we set state to SYN-SENT and not releasing socket</i></b>
<a name="L217" href="source/net/ipv4/tcp_ipv4.c#L217">217</a> <b><i>         * lock select source port, enter ourselves into the hash tables and</i></b>
<a name="L218" href="source/net/ipv4/tcp_ipv4.c#L218">218</a> <b><i>         * complete initialization after this.</i></b>
<a name="L219" href="source/net/ipv4/tcp_ipv4.c#L219">219</a> <b><i>         */</i></b>
<a name="L220" href="source/net/ipv4/tcp_ipv4.c#L220">220</a>         <a href="ident?i=tcp_set_state">tcp_set_state</a>(sk, TCP_SYN_SENT);
<a name="L221" href="source/net/ipv4/tcp_ipv4.c#L221">221</a>         <a href="ident?i=err">err</a> = <a href="ident?i=inet_hash_connect">inet_hash_connect</a>(&amp;<a href="ident?i=tcp_death_row">tcp_death_row</a>, sk);
<a name="L222" href="source/net/ipv4/tcp_ipv4.c#L222">222</a>         if (<a href="ident?i=err">err</a>)
<a name="L223" href="source/net/ipv4/tcp_ipv4.c#L223">223</a>                 goto failure;
<a name="L224" href="source/net/ipv4/tcp_ipv4.c#L224">224</a> 
<a name="L225" href="source/net/ipv4/tcp_ipv4.c#L225">225</a>         <a href="ident?i=inet_set_txhash">inet_set_txhash</a>(sk);
<a name="L226" href="source/net/ipv4/tcp_ipv4.c#L226">226</a> 
<a name="L227" href="source/net/ipv4/tcp_ipv4.c#L227">227</a>         <a href="ident?i=rt">rt</a> = <a href="ident?i=ip_route_newports">ip_route_newports</a>(fl4, <a href="ident?i=rt">rt</a>, orig_sport, orig_dport,
<a name="L228" href="source/net/ipv4/tcp_ipv4.c#L228">228</a>                                inet-&gt;inet_sport, inet-&gt;<a href="ident?i=inet_dport">inet_dport</a>, sk);
<a name="L229" href="source/net/ipv4/tcp_ipv4.c#L229">229</a>         if (<a href="ident?i=IS_ERR">IS_ERR</a>(<a href="ident?i=rt">rt</a>)) {
<a name="L230" href="source/net/ipv4/tcp_ipv4.c#L230">230</a>                 <a href="ident?i=err">err</a> = <a href="ident?i=PTR_ERR">PTR_ERR</a>(<a href="ident?i=rt">rt</a>);
<a name="L231" href="source/net/ipv4/tcp_ipv4.c#L231">231</a>                 <a href="ident?i=rt">rt</a> = <a href="ident?i=NULL">NULL</a>;
<a name="L232" href="source/net/ipv4/tcp_ipv4.c#L232">232</a>                 goto failure;
<a name="L233" href="source/net/ipv4/tcp_ipv4.c#L233">233</a>         }
<a name="L234" href="source/net/ipv4/tcp_ipv4.c#L234">234</a>         <b><i>/* OK, now commit destination to socket.  */</i></b>
<a name="L235" href="source/net/ipv4/tcp_ipv4.c#L235">235</a>         sk-&gt;sk_gso_type = SKB_GSO_TCPV4;
<a name="L236" href="source/net/ipv4/tcp_ipv4.c#L236">236</a>         <a href="ident?i=sk_setup_caps">sk_setup_caps</a>(sk, &amp;<a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>);
<a name="L237" href="source/net/ipv4/tcp_ipv4.c#L237">237</a> 
<a name="L238" href="source/net/ipv4/tcp_ipv4.c#L238">238</a>         if (!<a href="ident?i=tp">tp</a>-&gt;write_seq &amp;&amp; <a href="ident?i=likely">likely</a>(!<a href="ident?i=tp">tp</a>-&gt;repair))
<a name="L239" href="source/net/ipv4/tcp_ipv4.c#L239">239</a>                 <a href="ident?i=tp">tp</a>-&gt;write_seq = <a href="ident?i=secure_tcp_sequence_number">secure_tcp_sequence_number</a>(inet-&gt;inet_saddr,
<a name="L240" href="source/net/ipv4/tcp_ipv4.c#L240">240</a>                                                            inet-&gt;<a href="ident?i=inet_daddr">inet_daddr</a>,
<a name="L241" href="source/net/ipv4/tcp_ipv4.c#L241">241</a>                                                            inet-&gt;inet_sport,
<a name="L242" href="source/net/ipv4/tcp_ipv4.c#L242">242</a>                                                            usin-&gt;sin_port);
<a name="L243" href="source/net/ipv4/tcp_ipv4.c#L243">243</a> 
<a name="L244" href="source/net/ipv4/tcp_ipv4.c#L244">244</a>         inet-&gt;inet_id = <a href="ident?i=tp">tp</a>-&gt;write_seq ^ <a href="ident?i=jiffies">jiffies</a>;
<a name="L245" href="source/net/ipv4/tcp_ipv4.c#L245">245</a> 
<a name="L246" href="source/net/ipv4/tcp_ipv4.c#L246">246</a>         <a href="ident?i=err">err</a> = <a href="ident?i=tcp_connect">tcp_connect</a>(sk);
<a name="L247" href="source/net/ipv4/tcp_ipv4.c#L247">247</a> 
<a name="L248" href="source/net/ipv4/tcp_ipv4.c#L248">248</a>         <a href="ident?i=rt">rt</a> = <a href="ident?i=NULL">NULL</a>;
<a name="L249" href="source/net/ipv4/tcp_ipv4.c#L249">249</a>         if (<a href="ident?i=err">err</a>)
<a name="L250" href="source/net/ipv4/tcp_ipv4.c#L250">250</a>                 goto failure;
<a name="L251" href="source/net/ipv4/tcp_ipv4.c#L251">251</a> 
<a name="L252" href="source/net/ipv4/tcp_ipv4.c#L252">252</a>         return 0;
<a name="L253" href="source/net/ipv4/tcp_ipv4.c#L253">253</a> 
<a name="L254" href="source/net/ipv4/tcp_ipv4.c#L254">254</a> failure:
<a name="L255" href="source/net/ipv4/tcp_ipv4.c#L255">255</a>         <b><i>/*</i></b>
<a name="L256" href="source/net/ipv4/tcp_ipv4.c#L256">256</a> <b><i>         * This unhashes the socket and releases the local port,</i></b>
<a name="L257" href="source/net/ipv4/tcp_ipv4.c#L257">257</a> <b><i>         * if necessary.</i></b>
<a name="L258" href="source/net/ipv4/tcp_ipv4.c#L258">258</a> <b><i>         */</i></b>
<a name="L259" href="source/net/ipv4/tcp_ipv4.c#L259">259</a>         <a href="ident?i=tcp_set_state">tcp_set_state</a>(sk, TCP_CLOSE);
<a name="L260" href="source/net/ipv4/tcp_ipv4.c#L260">260</a>         <a href="ident?i=ip_rt_put">ip_rt_put</a>(<a href="ident?i=rt">rt</a>);
<a name="L261" href="source/net/ipv4/tcp_ipv4.c#L261">261</a>         sk-&gt;sk_route_caps = 0;
<a name="L262" href="source/net/ipv4/tcp_ipv4.c#L262">262</a>         inet-&gt;<a href="ident?i=inet_dport">inet_dport</a> = 0;
<a name="L263" href="source/net/ipv4/tcp_ipv4.c#L263">263</a>         return <a href="ident?i=err">err</a>;
<a name="L264" href="source/net/ipv4/tcp_ipv4.c#L264">264</a> }
<a name="L265" href="source/net/ipv4/tcp_ipv4.c#L265">265</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=tcp_v4_connect">tcp_v4_connect</a>);
<a name="L266" href="source/net/ipv4/tcp_ipv4.c#L266">266</a> 
<a name="L267" href="source/net/ipv4/tcp_ipv4.c#L267">267</a> <b><i>/*</i></b>
<a name="L268" href="source/net/ipv4/tcp_ipv4.c#L268">268</a> <b><i> * This routine reacts to ICMP_FRAG_NEEDED mtu indications as defined in RFC1191.</i></b>
<a name="L269" href="source/net/ipv4/tcp_ipv4.c#L269">269</a> <b><i> * It can be called through tcp_release_cb() if socket was owned by user</i></b>
<a name="L270" href="source/net/ipv4/tcp_ipv4.c#L270">270</a> <b><i> * at the time tcp_v4_err() was called to handle ICMP message.</i></b>
<a name="L271" href="source/net/ipv4/tcp_ipv4.c#L271">271</a> <b><i> */</i></b>
<a name="L272" href="source/net/ipv4/tcp_ipv4.c#L272">272</a> void <a href="ident?i=tcp_v4_mtu_reduced">tcp_v4_mtu_reduced</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L273" href="source/net/ipv4/tcp_ipv4.c#L273">273</a> {
<a name="L274" href="source/net/ipv4/tcp_ipv4.c#L274">274</a>         struct <a href="ident?i=dst_entry">dst_entry</a> *<a href="ident?i=dst">dst</a>;
<a name="L275" href="source/net/ipv4/tcp_ipv4.c#L275">275</a>         struct <a href="ident?i=inet_sock">inet_sock</a> *inet = <a href="ident?i=inet_sk">inet_sk</a>(sk);
<a name="L276" href="source/net/ipv4/tcp_ipv4.c#L276">276</a>         <a href="ident?i=u32">u32</a> <a href="ident?i=mtu">mtu</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk)-&gt;mtu_info;
<a name="L277" href="source/net/ipv4/tcp_ipv4.c#L277">277</a> 
<a name="L278" href="source/net/ipv4/tcp_ipv4.c#L278">278</a>         <a href="ident?i=dst">dst</a> = <a href="ident?i=inet_csk_update_pmtu">inet_csk_update_pmtu</a>(sk, <a href="ident?i=mtu">mtu</a>);
<a name="L279" href="source/net/ipv4/tcp_ipv4.c#L279">279</a>         if (!<a href="ident?i=dst">dst</a>)
<a name="L280" href="source/net/ipv4/tcp_ipv4.c#L280">280</a>                 return;
<a name="L281" href="source/net/ipv4/tcp_ipv4.c#L281">281</a> 
<a name="L282" href="source/net/ipv4/tcp_ipv4.c#L282">282</a>         <b><i>/* Something is about to be wrong... Remember soft error</i></b>
<a name="L283" href="source/net/ipv4/tcp_ipv4.c#L283">283</a> <b><i>         * for the case, if this connection will not able to recover.</i></b>
<a name="L284" href="source/net/ipv4/tcp_ipv4.c#L284">284</a> <b><i>         */</i></b>
<a name="L285" href="source/net/ipv4/tcp_ipv4.c#L285">285</a>         if (<a href="ident?i=mtu">mtu</a> &lt; <a href="ident?i=dst_mtu">dst_mtu</a>(<a href="ident?i=dst">dst</a>) &amp;&amp; <a href="ident?i=ip_dont_fragment">ip_dont_fragment</a>(sk, <a href="ident?i=dst">dst</a>))
<a name="L286" href="source/net/ipv4/tcp_ipv4.c#L286">286</a>                 sk-&gt;sk_err_soft = <a href="ident?i=EMSGSIZE">EMSGSIZE</a>;
<a name="L287" href="source/net/ipv4/tcp_ipv4.c#L287">287</a> 
<a name="L288" href="source/net/ipv4/tcp_ipv4.c#L288">288</a>         <a href="ident?i=mtu">mtu</a> = <a href="ident?i=dst_mtu">dst_mtu</a>(<a href="ident?i=dst">dst</a>);
<a name="L289" href="source/net/ipv4/tcp_ipv4.c#L289">289</a> 
<a name="L290" href="source/net/ipv4/tcp_ipv4.c#L290">290</a>         if (inet-&gt;pmtudisc != <a href="ident?i=IP_PMTUDISC_DONT">IP_PMTUDISC_DONT</a> &amp;&amp;
<a name="L291" href="source/net/ipv4/tcp_ipv4.c#L291">291</a>             <a href="ident?i=ip_sk_accept_pmtu">ip_sk_accept_pmtu</a>(sk) &amp;&amp;
<a name="L292" href="source/net/ipv4/tcp_ipv4.c#L292">292</a>             <a href="ident?i=inet_csk">inet_csk</a>(sk)-&gt;icsk_pmtu_cookie &gt; <a href="ident?i=mtu">mtu</a>) {
<a name="L293" href="source/net/ipv4/tcp_ipv4.c#L293">293</a>                 <a href="ident?i=tcp_sync_mss">tcp_sync_mss</a>(sk, <a href="ident?i=mtu">mtu</a>);
<a name="L294" href="source/net/ipv4/tcp_ipv4.c#L294">294</a> 
<a name="L295" href="source/net/ipv4/tcp_ipv4.c#L295">295</a>                 <b><i>/* Resend the TCP packet because it's</i></b>
<a name="L296" href="source/net/ipv4/tcp_ipv4.c#L296">296</a> <b><i>                 * clear that the old packet has been</i></b>
<a name="L297" href="source/net/ipv4/tcp_ipv4.c#L297">297</a> <b><i>                 * dropped. This is the new "fast" path mtu</i></b>
<a name="L298" href="source/net/ipv4/tcp_ipv4.c#L298">298</a> <b><i>                 * discovery.</i></b>
<a name="L299" href="source/net/ipv4/tcp_ipv4.c#L299">299</a> <b><i>                 */</i></b>
<a name="L300" href="source/net/ipv4/tcp_ipv4.c#L300">300</a>                 <a href="ident?i=tcp_simple_retransmit">tcp_simple_retransmit</a>(sk);
<a name="L301" href="source/net/ipv4/tcp_ipv4.c#L301">301</a>         } <b><i>/* else let the usual retransmit timer handle it */</i></b>
<a name="L302" href="source/net/ipv4/tcp_ipv4.c#L302">302</a> }
<a name="L303" href="source/net/ipv4/tcp_ipv4.c#L303">303</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=tcp_v4_mtu_reduced">tcp_v4_mtu_reduced</a>);
<a name="L304" href="source/net/ipv4/tcp_ipv4.c#L304">304</a> 
<a name="L305" href="source/net/ipv4/tcp_ipv4.c#L305">305</a> static void <a href="ident?i=do_redirect">do_redirect</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, struct <a href="ident?i=sock">sock</a> *sk)
<a name="L306" href="source/net/ipv4/tcp_ipv4.c#L306">306</a> {
<a name="L307" href="source/net/ipv4/tcp_ipv4.c#L307">307</a>         struct <a href="ident?i=dst_entry">dst_entry</a> *<a href="ident?i=dst">dst</a> = <a href="ident?i=__sk_dst_check">__sk_dst_check</a>(sk, 0);
<a name="L308" href="source/net/ipv4/tcp_ipv4.c#L308">308</a> 
<a name="L309" href="source/net/ipv4/tcp_ipv4.c#L309">309</a>         if (<a href="ident?i=dst">dst</a>)
<a name="L310" href="source/net/ipv4/tcp_ipv4.c#L310">310</a>                 <a href="ident?i=dst">dst</a>-&gt;<a href="ident?i=ops">ops</a>-&gt;<a href="ident?i=redirect">redirect</a>(<a href="ident?i=dst">dst</a>, sk, <a href="ident?i=skb">skb</a>);
<a name="L311" href="source/net/ipv4/tcp_ipv4.c#L311">311</a> }
<a name="L312" href="source/net/ipv4/tcp_ipv4.c#L312">312</a> 
<a name="L313" href="source/net/ipv4/tcp_ipv4.c#L313">313</a> 
<a name="L314" href="source/net/ipv4/tcp_ipv4.c#L314">314</a> <b><i>/* handle ICMP messages on TCP_NEW_SYN_RECV request sockets */</i></b>
<a name="L315" href="source/net/ipv4/tcp_ipv4.c#L315">315</a> void <a href="ident?i=tcp_req_err">tcp_req_err</a>(struct <a href="ident?i=sock">sock</a> *sk, <a href="ident?i=u32">u32</a> <a href="ident?i=seq">seq</a>)
<a name="L316" href="source/net/ipv4/tcp_ipv4.c#L316">316</a> {
<a name="L317" href="source/net/ipv4/tcp_ipv4.c#L317">317</a>         struct <a href="ident?i=request_sock">request_sock</a> *<a href="ident?i=req">req</a> = <a href="ident?i=inet_reqsk">inet_reqsk</a>(sk);
<a name="L318" href="source/net/ipv4/tcp_ipv4.c#L318">318</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=sock_net">sock_net</a>(sk);
<a name="L319" href="source/net/ipv4/tcp_ipv4.c#L319">319</a> 
<a name="L320" href="source/net/ipv4/tcp_ipv4.c#L320">320</a>         <b><i>/* ICMPs are not backlogged, hence we cannot get</i></b>
<a name="L321" href="source/net/ipv4/tcp_ipv4.c#L321">321</a> <b><i>         * an established socket here.</i></b>
<a name="L322" href="source/net/ipv4/tcp_ipv4.c#L322">322</a> <b><i>         */</i></b>
<a name="L323" href="source/net/ipv4/tcp_ipv4.c#L323">323</a>         <a href="ident?i=WARN_ON">WARN_ON</a>(<a href="ident?i=req">req</a>-&gt;sk);
<a name="L324" href="source/net/ipv4/tcp_ipv4.c#L324">324</a> 
<a name="L325" href="source/net/ipv4/tcp_ipv4.c#L325">325</a>         if (<a href="ident?i=seq">seq</a> != <a href="ident?i=tcp_rsk">tcp_rsk</a>(<a href="ident?i=req">req</a>)-&gt;snt_isn) {
<a name="L326" href="source/net/ipv4/tcp_ipv4.c#L326">326</a>                 <a href="ident?i=NET_INC_STATS_BH">NET_INC_STATS_BH</a>(<a href="ident?i=net">net</a>, LINUX_MIB_OUTOFWINDOWICMPS);
<a name="L327" href="source/net/ipv4/tcp_ipv4.c#L327">327</a>                 <a href="ident?i=reqsk_put">reqsk_put</a>(<a href="ident?i=req">req</a>);
<a name="L328" href="source/net/ipv4/tcp_ipv4.c#L328">328</a>         } else {
<a name="L329" href="source/net/ipv4/tcp_ipv4.c#L329">329</a>                 <b><i>/*</i></b>
<a name="L330" href="source/net/ipv4/tcp_ipv4.c#L330">330</a> <b><i>                 * Still in SYN_RECV, just remove it silently.</i></b>
<a name="L331" href="source/net/ipv4/tcp_ipv4.c#L331">331</a> <b><i>                 * There is no good way to pass the error to the newly</i></b>
<a name="L332" href="source/net/ipv4/tcp_ipv4.c#L332">332</a> <b><i>                 * created socket, and POSIX does not want network</i></b>
<a name="L333" href="source/net/ipv4/tcp_ipv4.c#L333">333</a> <b><i>                 * errors returned from accept().</i></b>
<a name="L334" href="source/net/ipv4/tcp_ipv4.c#L334">334</a> <b><i>                 */</i></b>
<a name="L335" href="source/net/ipv4/tcp_ipv4.c#L335">335</a>                 <a href="ident?i=NET_INC_STATS_BH">NET_INC_STATS_BH</a>(<a href="ident?i=net">net</a>, LINUX_MIB_LISTENDROPS);
<a name="L336" href="source/net/ipv4/tcp_ipv4.c#L336">336</a>                 <a href="ident?i=inet_csk_reqsk_queue_drop">inet_csk_reqsk_queue_drop</a>(<a href="ident?i=req">req</a>-&gt;rsk_listener, <a href="ident?i=req">req</a>);
<a name="L337" href="source/net/ipv4/tcp_ipv4.c#L337">337</a>         }
<a name="L338" href="source/net/ipv4/tcp_ipv4.c#L338">338</a> }
<a name="L339" href="source/net/ipv4/tcp_ipv4.c#L339">339</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=tcp_req_err">tcp_req_err</a>);
<a name="L340" href="source/net/ipv4/tcp_ipv4.c#L340">340</a> 
<a name="L341" href="source/net/ipv4/tcp_ipv4.c#L341">341</a> <b><i>/*</i></b>
<a name="L342" href="source/net/ipv4/tcp_ipv4.c#L342">342</a> <b><i> * This routine is called by the ICMP module when it gets some</i></b>
<a name="L343" href="source/net/ipv4/tcp_ipv4.c#L343">343</a> <b><i> * sort of error condition.  If err &lt; 0 then the socket should</i></b>
<a name="L344" href="source/net/ipv4/tcp_ipv4.c#L344">344</a> <b><i> * be closed and the error returned to the user.  If err &gt; 0</i></b>
<a name="L345" href="source/net/ipv4/tcp_ipv4.c#L345">345</a> <b><i> * it's just the icmp type &lt;&lt; 8 | icmp code.  After adjustment</i></b>
<a name="L346" href="source/net/ipv4/tcp_ipv4.c#L346">346</a> <b><i> * header points to the first 8 bytes of the tcp header.  We need</i></b>
<a name="L347" href="source/net/ipv4/tcp_ipv4.c#L347">347</a> <b><i> * to find the appropriate port.</i></b>
<a name="L348" href="source/net/ipv4/tcp_ipv4.c#L348">348</a> <b><i> *</i></b>
<a name="L349" href="source/net/ipv4/tcp_ipv4.c#L349">349</a> <b><i> * The locking strategy used here is very "optimistic". When</i></b>
<a name="L350" href="source/net/ipv4/tcp_ipv4.c#L350">350</a> <b><i> * someone else accesses the socket the ICMP is just dropped</i></b>
<a name="L351" href="source/net/ipv4/tcp_ipv4.c#L351">351</a> <b><i> * and for some paths there is no check at all.</i></b>
<a name="L352" href="source/net/ipv4/tcp_ipv4.c#L352">352</a> <b><i> * A more general error queue to queue errors for later handling</i></b>
<a name="L353" href="source/net/ipv4/tcp_ipv4.c#L353">353</a> <b><i> * is probably better.</i></b>
<a name="L354" href="source/net/ipv4/tcp_ipv4.c#L354">354</a> <b><i> *</i></b>
<a name="L355" href="source/net/ipv4/tcp_ipv4.c#L355">355</a> <b><i> */</i></b>
<a name="L356" href="source/net/ipv4/tcp_ipv4.c#L356">356</a> 
<a name="L357" href="source/net/ipv4/tcp_ipv4.c#L357">357</a> void <a href="ident?i=tcp_v4_err">tcp_v4_err</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *icmp_skb, <a href="ident?i=u32">u32</a> <a href="ident?i=info">info</a>)
<a name="L358" href="source/net/ipv4/tcp_ipv4.c#L358">358</a> {
<a name="L359" href="source/net/ipv4/tcp_ipv4.c#L359">359</a>         const struct <a href="ident?i=iphdr">iphdr</a> *iph = (const struct <a href="ident?i=iphdr">iphdr</a> *)icmp_skb-&gt;<a href="ident?i=data">data</a>;
<a name="L360" href="source/net/ipv4/tcp_ipv4.c#L360">360</a>         struct <a href="ident?i=tcphdr">tcphdr</a> *<a href="ident?i=th">th</a> = (struct <a href="ident?i=tcphdr">tcphdr</a> *)(icmp_skb-&gt;<a href="ident?i=data">data</a> + (iph-&gt;ihl &lt;&lt; 2));
<a name="L361" href="source/net/ipv4/tcp_ipv4.c#L361">361</a>         struct <a href="ident?i=inet_connection_sock">inet_connection_sock</a> *icsk;
<a name="L362" href="source/net/ipv4/tcp_ipv4.c#L362">362</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a>;
<a name="L363" href="source/net/ipv4/tcp_ipv4.c#L363">363</a>         struct <a href="ident?i=inet_sock">inet_sock</a> *inet;
<a name="L364" href="source/net/ipv4/tcp_ipv4.c#L364">364</a>         const int <a href="ident?i=type">type</a> = <a href="ident?i=icmp_hdr">icmp_hdr</a>(icmp_skb)-&gt;<a href="ident?i=type">type</a>;
<a name="L365" href="source/net/ipv4/tcp_ipv4.c#L365">365</a>         const int <a href="ident?i=code">code</a> = <a href="ident?i=icmp_hdr">icmp_hdr</a>(icmp_skb)-&gt;<a href="ident?i=code">code</a>;
<a name="L366" href="source/net/ipv4/tcp_ipv4.c#L366">366</a>         struct <a href="ident?i=sock">sock</a> *sk;
<a name="L367" href="source/net/ipv4/tcp_ipv4.c#L367">367</a>         struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>;
<a name="L368" href="source/net/ipv4/tcp_ipv4.c#L368">368</a>         struct <a href="ident?i=request_sock">request_sock</a> *fastopen;
<a name="L369" href="source/net/ipv4/tcp_ipv4.c#L369">369</a>         <a href="ident?i=__u32">__u32</a> <a href="ident?i=seq">seq</a>, snd_una;
<a name="L370" href="source/net/ipv4/tcp_ipv4.c#L370">370</a>         <a href="ident?i=__u32">__u32</a> <a href="ident?i=remaining">remaining</a>;
<a name="L371" href="source/net/ipv4/tcp_ipv4.c#L371">371</a>         int <a href="ident?i=err">err</a>;
<a name="L372" href="source/net/ipv4/tcp_ipv4.c#L372">372</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=dev_net">dev_net</a>(icmp_skb-&gt;<a href="ident?i=dev">dev</a>);
<a name="L373" href="source/net/ipv4/tcp_ipv4.c#L373">373</a> 
<a name="L374" href="source/net/ipv4/tcp_ipv4.c#L374">374</a>         sk = <a href="ident?i=__inet_lookup_established">__inet_lookup_established</a>(<a href="ident?i=net">net</a>, &amp;<a href="ident?i=tcp_hashinfo">tcp_hashinfo</a>, iph-&gt;<a href="ident?i=daddr">daddr</a>,
<a name="L375" href="source/net/ipv4/tcp_ipv4.c#L375">375</a>                                        <a href="ident?i=th">th</a>-&gt;<a href="ident?i=dest">dest</a>, iph-&gt;<a href="ident?i=saddr">saddr</a>, <a href="ident?i=ntohs">ntohs</a>(<a href="ident?i=th">th</a>-&gt;source),
<a name="L376" href="source/net/ipv4/tcp_ipv4.c#L376">376</a>                                        <a href="ident?i=inet_iif">inet_iif</a>(icmp_skb));
<a name="L377" href="source/net/ipv4/tcp_ipv4.c#L377">377</a>         if (!sk) {
<a name="L378" href="source/net/ipv4/tcp_ipv4.c#L378">378</a>                 <a href="ident?i=ICMP_INC_STATS_BH">ICMP_INC_STATS_BH</a>(<a href="ident?i=net">net</a>, ICMP_MIB_INERRORS);
<a name="L379" href="source/net/ipv4/tcp_ipv4.c#L379">379</a>                 return;
<a name="L380" href="source/net/ipv4/tcp_ipv4.c#L380">380</a>         }
<a name="L381" href="source/net/ipv4/tcp_ipv4.c#L381">381</a>         if (sk-&gt;<a href="ident?i=sk_state">sk_state</a> == TCP_TIME_WAIT) {
<a name="L382" href="source/net/ipv4/tcp_ipv4.c#L382">382</a>                 <a href="ident?i=inet_twsk_put">inet_twsk_put</a>(<a href="ident?i=inet_twsk">inet_twsk</a>(sk));
<a name="L383" href="source/net/ipv4/tcp_ipv4.c#L383">383</a>                 return;
<a name="L384" href="source/net/ipv4/tcp_ipv4.c#L384">384</a>         }
<a name="L385" href="source/net/ipv4/tcp_ipv4.c#L385">385</a>         <a href="ident?i=seq">seq</a> = <a href="ident?i=ntohl">ntohl</a>(<a href="ident?i=th">th</a>-&gt;<a href="ident?i=seq">seq</a>);
<a name="L386" href="source/net/ipv4/tcp_ipv4.c#L386">386</a>         if (sk-&gt;<a href="ident?i=sk_state">sk_state</a> == TCP_NEW_SYN_RECV)
<a name="L387" href="source/net/ipv4/tcp_ipv4.c#L387">387</a>                 return <a href="ident?i=tcp_req_err">tcp_req_err</a>(sk, <a href="ident?i=seq">seq</a>);
<a name="L388" href="source/net/ipv4/tcp_ipv4.c#L388">388</a> 
<a name="L389" href="source/net/ipv4/tcp_ipv4.c#L389">389</a>         <a href="ident?i=bh_lock_sock">bh_lock_sock</a>(sk);
<a name="L390" href="source/net/ipv4/tcp_ipv4.c#L390">390</a>         <b><i>/* If too many ICMPs get dropped on busy</i></b>
<a name="L391" href="source/net/ipv4/tcp_ipv4.c#L391">391</a> <b><i>         * servers this needs to be solved differently.</i></b>
<a name="L392" href="source/net/ipv4/tcp_ipv4.c#L392">392</a> <b><i>         * We do take care of PMTU discovery (RFC1191) special case :</i></b>
<a name="L393" href="source/net/ipv4/tcp_ipv4.c#L393">393</a> <b><i>         * we can receive locally generated ICMP messages while socket is held.</i></b>
<a name="L394" href="source/net/ipv4/tcp_ipv4.c#L394">394</a> <b><i>         */</i></b>
<a name="L395" href="source/net/ipv4/tcp_ipv4.c#L395">395</a>         if (<a href="ident?i=sock_owned_by_user">sock_owned_by_user</a>(sk)) {
<a name="L396" href="source/net/ipv4/tcp_ipv4.c#L396">396</a>                 if (!(<a href="ident?i=type">type</a> == <a href="ident?i=ICMP_DEST_UNREACH">ICMP_DEST_UNREACH</a> &amp;&amp; <a href="ident?i=code">code</a> == <a href="ident?i=ICMP_FRAG_NEEDED">ICMP_FRAG_NEEDED</a>))
<a name="L397" href="source/net/ipv4/tcp_ipv4.c#L397">397</a>                         <a href="ident?i=NET_INC_STATS_BH">NET_INC_STATS_BH</a>(<a href="ident?i=net">net</a>, LINUX_MIB_LOCKDROPPEDICMPS);
<a name="L398" href="source/net/ipv4/tcp_ipv4.c#L398">398</a>         }
<a name="L399" href="source/net/ipv4/tcp_ipv4.c#L399">399</a>         if (sk-&gt;<a href="ident?i=sk_state">sk_state</a> == TCP_CLOSE)
<a name="L400" href="source/net/ipv4/tcp_ipv4.c#L400">400</a>                 goto <a href="ident?i=out">out</a>;
<a name="L401" href="source/net/ipv4/tcp_ipv4.c#L401">401</a> 
<a name="L402" href="source/net/ipv4/tcp_ipv4.c#L402">402</a>         if (<a href="ident?i=unlikely">unlikely</a>(iph-&gt;<a href="ident?i=ttl">ttl</a> &lt; <a href="ident?i=inet_sk">inet_sk</a>(sk)-&gt;<a href="ident?i=min_ttl">min_ttl</a>)) {
<a name="L403" href="source/net/ipv4/tcp_ipv4.c#L403">403</a>                 <a href="ident?i=NET_INC_STATS_BH">NET_INC_STATS_BH</a>(<a href="ident?i=net">net</a>, LINUX_MIB_TCPMINTTLDROP);
<a name="L404" href="source/net/ipv4/tcp_ipv4.c#L404">404</a>                 goto <a href="ident?i=out">out</a>;
<a name="L405" href="source/net/ipv4/tcp_ipv4.c#L405">405</a>         }
<a name="L406" href="source/net/ipv4/tcp_ipv4.c#L406">406</a> 
<a name="L407" href="source/net/ipv4/tcp_ipv4.c#L407">407</a>         icsk = <a href="ident?i=inet_csk">inet_csk</a>(sk);
<a name="L408" href="source/net/ipv4/tcp_ipv4.c#L408">408</a>         <a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L409" href="source/net/ipv4/tcp_ipv4.c#L409">409</a>         <b><i>/* XXX (TFO) - tp-&gt;snd_una should be ISN (tcp_create_openreq_child() */</i></b>
<a name="L410" href="source/net/ipv4/tcp_ipv4.c#L410">410</a>         fastopen = <a href="ident?i=tp">tp</a>-&gt;fastopen_rsk;
<a name="L411" href="source/net/ipv4/tcp_ipv4.c#L411">411</a>         snd_una = fastopen ? <a href="ident?i=tcp_rsk">tcp_rsk</a>(fastopen)-&gt;snt_isn : <a href="ident?i=tp">tp</a>-&gt;snd_una;
<a name="L412" href="source/net/ipv4/tcp_ipv4.c#L412">412</a>         if (sk-&gt;<a href="ident?i=sk_state">sk_state</a> != TCP_LISTEN &amp;&amp;
<a name="L413" href="source/net/ipv4/tcp_ipv4.c#L413">413</a>             !<a href="ident?i=between">between</a>(<a href="ident?i=seq">seq</a>, snd_una, <a href="ident?i=tp">tp</a>-&gt;snd_nxt)) {
<a name="L414" href="source/net/ipv4/tcp_ipv4.c#L414">414</a>                 <a href="ident?i=NET_INC_STATS_BH">NET_INC_STATS_BH</a>(<a href="ident?i=net">net</a>, LINUX_MIB_OUTOFWINDOWICMPS);
<a name="L415" href="source/net/ipv4/tcp_ipv4.c#L415">415</a>                 goto <a href="ident?i=out">out</a>;
<a name="L416" href="source/net/ipv4/tcp_ipv4.c#L416">416</a>         }
<a name="L417" href="source/net/ipv4/tcp_ipv4.c#L417">417</a> 
<a name="L418" href="source/net/ipv4/tcp_ipv4.c#L418">418</a>         switch (<a href="ident?i=type">type</a>) {
<a name="L419" href="source/net/ipv4/tcp_ipv4.c#L419">419</a>         case <a href="ident?i=ICMP_REDIRECT">ICMP_REDIRECT</a>:
<a name="L420" href="source/net/ipv4/tcp_ipv4.c#L420">420</a>                 <a href="ident?i=do_redirect">do_redirect</a>(icmp_skb, sk);
<a name="L421" href="source/net/ipv4/tcp_ipv4.c#L421">421</a>                 goto <a href="ident?i=out">out</a>;
<a name="L422" href="source/net/ipv4/tcp_ipv4.c#L422">422</a>         case <a href="ident?i=ICMP_SOURCE_QUENCH">ICMP_SOURCE_QUENCH</a>:
<a name="L423" href="source/net/ipv4/tcp_ipv4.c#L423">423</a>                 <b><i>/* Just silently ignore these. */</i></b>
<a name="L424" href="source/net/ipv4/tcp_ipv4.c#L424">424</a>                 goto <a href="ident?i=out">out</a>;
<a name="L425" href="source/net/ipv4/tcp_ipv4.c#L425">425</a>         case <a href="ident?i=ICMP_PARAMETERPROB">ICMP_PARAMETERPROB</a>:
<a name="L426" href="source/net/ipv4/tcp_ipv4.c#L426">426</a>                 <a href="ident?i=err">err</a> = <a href="ident?i=EPROTO">EPROTO</a>;
<a name="L427" href="source/net/ipv4/tcp_ipv4.c#L427">427</a>                 break;
<a name="L428" href="source/net/ipv4/tcp_ipv4.c#L428">428</a>         case <a href="ident?i=ICMP_DEST_UNREACH">ICMP_DEST_UNREACH</a>:
<a name="L429" href="source/net/ipv4/tcp_ipv4.c#L429">429</a>                 if (<a href="ident?i=code">code</a> &gt; <a href="ident?i=NR_ICMP_UNREACH">NR_ICMP_UNREACH</a>)
<a name="L430" href="source/net/ipv4/tcp_ipv4.c#L430">430</a>                         goto <a href="ident?i=out">out</a>;
<a name="L431" href="source/net/ipv4/tcp_ipv4.c#L431">431</a> 
<a name="L432" href="source/net/ipv4/tcp_ipv4.c#L432">432</a>                 if (<a href="ident?i=code">code</a> == <a href="ident?i=ICMP_FRAG_NEEDED">ICMP_FRAG_NEEDED</a>) { <b><i>/* PMTU discovery (RFC1191) */</i></b>
<a name="L433" href="source/net/ipv4/tcp_ipv4.c#L433">433</a>                         <b><i>/* We are not interested in TCP_LISTEN and open_requests</i></b>
<a name="L434" href="source/net/ipv4/tcp_ipv4.c#L434">434</a> <b><i>                         * (SYN-ACKs send out by Linux are always &lt;576bytes so</i></b>
<a name="L435" href="source/net/ipv4/tcp_ipv4.c#L435">435</a> <b><i>                         * they should go through unfragmented).</i></b>
<a name="L436" href="source/net/ipv4/tcp_ipv4.c#L436">436</a> <b><i>                         */</i></b>
<a name="L437" href="source/net/ipv4/tcp_ipv4.c#L437">437</a>                         if (sk-&gt;<a href="ident?i=sk_state">sk_state</a> == TCP_LISTEN)
<a name="L438" href="source/net/ipv4/tcp_ipv4.c#L438">438</a>                                 goto <a href="ident?i=out">out</a>;
<a name="L439" href="source/net/ipv4/tcp_ipv4.c#L439">439</a> 
<a name="L440" href="source/net/ipv4/tcp_ipv4.c#L440">440</a>                         <a href="ident?i=tp">tp</a>-&gt;mtu_info = <a href="ident?i=info">info</a>;
<a name="L441" href="source/net/ipv4/tcp_ipv4.c#L441">441</a>                         if (!<a href="ident?i=sock_owned_by_user">sock_owned_by_user</a>(sk)) {
<a name="L442" href="source/net/ipv4/tcp_ipv4.c#L442">442</a>                                 <a href="ident?i=tcp_v4_mtu_reduced">tcp_v4_mtu_reduced</a>(sk);
<a name="L443" href="source/net/ipv4/tcp_ipv4.c#L443">443</a>                         } else {
<a name="L444" href="source/net/ipv4/tcp_ipv4.c#L444">444</a>                                 if (!<a href="ident?i=test_and_set_bit">test_and_set_bit</a>(TCP_MTU_REDUCED_DEFERRED, &amp;<a href="ident?i=tp">tp</a>-&gt;<a href="ident?i=tsq_flags">tsq_flags</a>))
<a name="L445" href="source/net/ipv4/tcp_ipv4.c#L445">445</a>                                         <a href="ident?i=sock_hold">sock_hold</a>(sk);
<a name="L446" href="source/net/ipv4/tcp_ipv4.c#L446">446</a>                         }
<a name="L447" href="source/net/ipv4/tcp_ipv4.c#L447">447</a>                         goto <a href="ident?i=out">out</a>;
<a name="L448" href="source/net/ipv4/tcp_ipv4.c#L448">448</a>                 }
<a name="L449" href="source/net/ipv4/tcp_ipv4.c#L449">449</a> 
<a name="L450" href="source/net/ipv4/tcp_ipv4.c#L450">450</a>                 <a href="ident?i=err">err</a> = <a href="ident?i=icmp_err_convert">icmp_err_convert</a>[<a href="ident?i=code">code</a>].<a href="ident?i=errno">errno</a>;
<a name="L451" href="source/net/ipv4/tcp_ipv4.c#L451">451</a>                 <b><i>/* check if icmp_skb allows revert of backoff</i></b>
<a name="L452" href="source/net/ipv4/tcp_ipv4.c#L452">452</a> <b><i>                 * (see draft-zimmermann-tcp-lcd) */</i></b>
<a name="L453" href="source/net/ipv4/tcp_ipv4.c#L453">453</a>                 if (<a href="ident?i=code">code</a> != <a href="ident?i=ICMP_NET_UNREACH">ICMP_NET_UNREACH</a> &amp;&amp; <a href="ident?i=code">code</a> != <a href="ident?i=ICMP_HOST_UNREACH">ICMP_HOST_UNREACH</a>)
<a name="L454" href="source/net/ipv4/tcp_ipv4.c#L454">454</a>                         break;
<a name="L455" href="source/net/ipv4/tcp_ipv4.c#L455">455</a>                 if (<a href="ident?i=seq">seq</a> != <a href="ident?i=tp">tp</a>-&gt;snd_una  || !icsk-&gt;icsk_retransmits ||
<a name="L456" href="source/net/ipv4/tcp_ipv4.c#L456">456</a>                     !icsk-&gt;icsk_backoff || fastopen)
<a name="L457" href="source/net/ipv4/tcp_ipv4.c#L457">457</a>                         break;
<a name="L458" href="source/net/ipv4/tcp_ipv4.c#L458">458</a> 
<a name="L459" href="source/net/ipv4/tcp_ipv4.c#L459">459</a>                 if (<a href="ident?i=sock_owned_by_user">sock_owned_by_user</a>(sk))
<a name="L460" href="source/net/ipv4/tcp_ipv4.c#L460">460</a>                         break;
<a name="L461" href="source/net/ipv4/tcp_ipv4.c#L461">461</a> 
<a name="L462" href="source/net/ipv4/tcp_ipv4.c#L462">462</a>                 icsk-&gt;icsk_backoff--;
<a name="L463" href="source/net/ipv4/tcp_ipv4.c#L463">463</a>                 icsk-&gt;icsk_rto = <a href="ident?i=tp">tp</a>-&gt;srtt_us ? <a href="ident?i=__tcp_set_rto">__tcp_set_rto</a>(<a href="ident?i=tp">tp</a>) :
<a name="L464" href="source/net/ipv4/tcp_ipv4.c#L464">464</a>                                                <a href="ident?i=TCP_TIMEOUT_INIT">TCP_TIMEOUT_INIT</a>;
<a name="L465" href="source/net/ipv4/tcp_ipv4.c#L465">465</a>                 icsk-&gt;icsk_rto = <a href="ident?i=inet_csk_rto_backoff">inet_csk_rto_backoff</a>(icsk, <a href="ident?i=TCP_RTO_MAX">TCP_RTO_MAX</a>);
<a name="L466" href="source/net/ipv4/tcp_ipv4.c#L466">466</a> 
<a name="L467" href="source/net/ipv4/tcp_ipv4.c#L467">467</a>                 <a href="ident?i=skb">skb</a> = <a href="ident?i=tcp_write_queue_head">tcp_write_queue_head</a>(sk);
<a name="L468" href="source/net/ipv4/tcp_ipv4.c#L468">468</a>                 <a href="ident?i=BUG_ON">BUG_ON</a>(!<a href="ident?i=skb">skb</a>);
<a name="L469" href="source/net/ipv4/tcp_ipv4.c#L469">469</a> 
<a name="L470" href="source/net/ipv4/tcp_ipv4.c#L470">470</a>                 <a href="ident?i=remaining">remaining</a> = icsk-&gt;icsk_rto -
<a name="L471" href="source/net/ipv4/tcp_ipv4.c#L471">471</a>                             <a href="ident?i=min">min</a>(icsk-&gt;icsk_rto,
<a name="L472" href="source/net/ipv4/tcp_ipv4.c#L472">472</a>                                 <a href="ident?i=tcp_time_stamp">tcp_time_stamp</a> - <a href="ident?i=tcp_skb_timestamp">tcp_skb_timestamp</a>(<a href="ident?i=skb">skb</a>));
<a name="L473" href="source/net/ipv4/tcp_ipv4.c#L473">473</a> 
<a name="L474" href="source/net/ipv4/tcp_ipv4.c#L474">474</a>                 if (<a href="ident?i=remaining">remaining</a>) {
<a name="L475" href="source/net/ipv4/tcp_ipv4.c#L475">475</a>                         <a href="ident?i=inet_csk_reset_xmit_timer">inet_csk_reset_xmit_timer</a>(sk, <a href="ident?i=ICSK_TIME_RETRANS">ICSK_TIME_RETRANS</a>,
<a name="L476" href="source/net/ipv4/tcp_ipv4.c#L476">476</a>                                                   <a href="ident?i=remaining">remaining</a>, <a href="ident?i=TCP_RTO_MAX">TCP_RTO_MAX</a>);
<a name="L477" href="source/net/ipv4/tcp_ipv4.c#L477">477</a>                 } else {
<a name="L478" href="source/net/ipv4/tcp_ipv4.c#L478">478</a>                         <b><i>/* RTO revert clocked out retransmission.</i></b>
<a name="L479" href="source/net/ipv4/tcp_ipv4.c#L479">479</a> <b><i>                         * Will retransmit now */</i></b>
<a name="L480" href="source/net/ipv4/tcp_ipv4.c#L480">480</a>                         <a href="ident?i=tcp_retransmit_timer">tcp_retransmit_timer</a>(sk);
<a name="L481" href="source/net/ipv4/tcp_ipv4.c#L481">481</a>                 }
<a name="L482" href="source/net/ipv4/tcp_ipv4.c#L482">482</a> 
<a name="L483" href="source/net/ipv4/tcp_ipv4.c#L483">483</a>                 break;
<a name="L484" href="source/net/ipv4/tcp_ipv4.c#L484">484</a>         case <a href="ident?i=ICMP_TIME_EXCEEDED">ICMP_TIME_EXCEEDED</a>:
<a name="L485" href="source/net/ipv4/tcp_ipv4.c#L485">485</a>                 <a href="ident?i=err">err</a> = <a href="ident?i=EHOSTUNREACH">EHOSTUNREACH</a>;
<a name="L486" href="source/net/ipv4/tcp_ipv4.c#L486">486</a>                 break;
<a name="L487" href="source/net/ipv4/tcp_ipv4.c#L487">487</a>         default:
<a name="L488" href="source/net/ipv4/tcp_ipv4.c#L488">488</a>                 goto <a href="ident?i=out">out</a>;
<a name="L489" href="source/net/ipv4/tcp_ipv4.c#L489">489</a>         }
<a name="L490" href="source/net/ipv4/tcp_ipv4.c#L490">490</a> 
<a name="L491" href="source/net/ipv4/tcp_ipv4.c#L491">491</a>         switch (sk-&gt;<a href="ident?i=sk_state">sk_state</a>) {
<a name="L492" href="source/net/ipv4/tcp_ipv4.c#L492">492</a>         case TCP_SYN_SENT:
<a name="L493" href="source/net/ipv4/tcp_ipv4.c#L493">493</a>         case TCP_SYN_RECV:
<a name="L494" href="source/net/ipv4/tcp_ipv4.c#L494">494</a>                 <b><i>/* Only in fast or simultaneous open. If a fast open socket is</i></b>
<a name="L495" href="source/net/ipv4/tcp_ipv4.c#L495">495</a> <b><i>                 * is already accepted it is treated as a connected one below.</i></b>
<a name="L496" href="source/net/ipv4/tcp_ipv4.c#L496">496</a> <b><i>                 */</i></b>
<a name="L497" href="source/net/ipv4/tcp_ipv4.c#L497">497</a>                 if (fastopen &amp;&amp; !fastopen-&gt;sk)
<a name="L498" href="source/net/ipv4/tcp_ipv4.c#L498">498</a>                         break;
<a name="L499" href="source/net/ipv4/tcp_ipv4.c#L499">499</a> 
<a name="L500" href="source/net/ipv4/tcp_ipv4.c#L500">500</a>                 if (!<a href="ident?i=sock_owned_by_user">sock_owned_by_user</a>(sk)) {
<a name="L501" href="source/net/ipv4/tcp_ipv4.c#L501">501</a>                         sk-&gt;sk_err = <a href="ident?i=err">err</a>;
<a name="L502" href="source/net/ipv4/tcp_ipv4.c#L502">502</a> 
<a name="L503" href="source/net/ipv4/tcp_ipv4.c#L503">503</a>                         sk-&gt;sk_error_report(sk);
<a name="L504" href="source/net/ipv4/tcp_ipv4.c#L504">504</a> 
<a name="L505" href="source/net/ipv4/tcp_ipv4.c#L505">505</a>                         <a href="ident?i=tcp_done">tcp_done</a>(sk);
<a name="L506" href="source/net/ipv4/tcp_ipv4.c#L506">506</a>                 } else {
<a name="L507" href="source/net/ipv4/tcp_ipv4.c#L507">507</a>                         sk-&gt;sk_err_soft = <a href="ident?i=err">err</a>;
<a name="L508" href="source/net/ipv4/tcp_ipv4.c#L508">508</a>                 }
<a name="L509" href="source/net/ipv4/tcp_ipv4.c#L509">509</a>                 goto <a href="ident?i=out">out</a>;
<a name="L510" href="source/net/ipv4/tcp_ipv4.c#L510">510</a>         }
<a name="L511" href="source/net/ipv4/tcp_ipv4.c#L511">511</a> 
<a name="L512" href="source/net/ipv4/tcp_ipv4.c#L512">512</a>         <b><i>/* If we've already connected we will keep trying</i></b>
<a name="L513" href="source/net/ipv4/tcp_ipv4.c#L513">513</a> <b><i>         * until we time out, or the user gives up.</i></b>
<a name="L514" href="source/net/ipv4/tcp_ipv4.c#L514">514</a> <b><i>         *</i></b>
<a name="L515" href="source/net/ipv4/tcp_ipv4.c#L515">515</a> <b><i>         * rfc1122 4.2.3.9 allows to consider as hard errors</i></b>
<a name="L516" href="source/net/ipv4/tcp_ipv4.c#L516">516</a> <b><i>         * only PROTO_UNREACH and PORT_UNREACH (well, FRAG_FAILED too,</i></b>
<a name="L517" href="source/net/ipv4/tcp_ipv4.c#L517">517</a> <b><i>         * but it is obsoleted by pmtu discovery).</i></b>
<a name="L518" href="source/net/ipv4/tcp_ipv4.c#L518">518</a> <b><i>         *</i></b>
<a name="L519" href="source/net/ipv4/tcp_ipv4.c#L519">519</a> <b><i>         * Note, that in modern internet, where routing is unreliable</i></b>
<a name="L520" href="source/net/ipv4/tcp_ipv4.c#L520">520</a> <b><i>         * and in each dark corner broken firewalls sit, sending random</i></b>
<a name="L521" href="source/net/ipv4/tcp_ipv4.c#L521">521</a> <b><i>         * errors ordered by their masters even this two messages finally lose</i></b>
<a name="L522" href="source/net/ipv4/tcp_ipv4.c#L522">522</a> <b><i>         * their original sense (even Linux sends invalid PORT_UNREACHs)</i></b>
<a name="L523" href="source/net/ipv4/tcp_ipv4.c#L523">523</a> <b><i>         *</i></b>
<a name="L524" href="source/net/ipv4/tcp_ipv4.c#L524">524</a> <b><i>         * Now we are in compliance with RFCs.</i></b>
<a name="L525" href="source/net/ipv4/tcp_ipv4.c#L525">525</a> <b><i>         *                                                      --ANK (980905)</i></b>
<a name="L526" href="source/net/ipv4/tcp_ipv4.c#L526">526</a> <b><i>         */</i></b>
<a name="L527" href="source/net/ipv4/tcp_ipv4.c#L527">527</a> 
<a name="L528" href="source/net/ipv4/tcp_ipv4.c#L528">528</a>         inet = <a href="ident?i=inet_sk">inet_sk</a>(sk);
<a name="L529" href="source/net/ipv4/tcp_ipv4.c#L529">529</a>         if (!<a href="ident?i=sock_owned_by_user">sock_owned_by_user</a>(sk) &amp;&amp; inet-&gt;recverr) {
<a name="L530" href="source/net/ipv4/tcp_ipv4.c#L530">530</a>                 sk-&gt;sk_err = <a href="ident?i=err">err</a>;
<a name="L531" href="source/net/ipv4/tcp_ipv4.c#L531">531</a>                 sk-&gt;sk_error_report(sk);
<a name="L532" href="source/net/ipv4/tcp_ipv4.c#L532">532</a>         } else  { <b><i>/* Only an error on timeout */</i></b>
<a name="L533" href="source/net/ipv4/tcp_ipv4.c#L533">533</a>                 sk-&gt;sk_err_soft = <a href="ident?i=err">err</a>;
<a name="L534" href="source/net/ipv4/tcp_ipv4.c#L534">534</a>         }
<a name="L535" href="source/net/ipv4/tcp_ipv4.c#L535">535</a> 
<a name="L536" href="source/net/ipv4/tcp_ipv4.c#L536">536</a> <a href="ident?i=out">out</a>:
<a name="L537" href="source/net/ipv4/tcp_ipv4.c#L537">537</a>         <a href="ident?i=bh_unlock_sock">bh_unlock_sock</a>(sk);
<a name="L538" href="source/net/ipv4/tcp_ipv4.c#L538">538</a>         <a href="ident?i=sock_put">sock_put</a>(sk);
<a name="L539" href="source/net/ipv4/tcp_ipv4.c#L539">539</a> }
<a name="L540" href="source/net/ipv4/tcp_ipv4.c#L540">540</a> 
<a name="L541" href="source/net/ipv4/tcp_ipv4.c#L541">541</a> void <a href="ident?i=__tcp_v4_send_check">__tcp_v4_send_check</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, <a href="ident?i=__be32">__be32</a> <a href="ident?i=saddr">saddr</a>, <a href="ident?i=__be32">__be32</a> <a href="ident?i=daddr">daddr</a>)
<a name="L542" href="source/net/ipv4/tcp_ipv4.c#L542">542</a> {
<a name="L543" href="source/net/ipv4/tcp_ipv4.c#L543">543</a>         struct <a href="ident?i=tcphdr">tcphdr</a> *<a href="ident?i=th">th</a> = <a href="ident?i=tcp_hdr">tcp_hdr</a>(<a href="ident?i=skb">skb</a>);
<a name="L544" href="source/net/ipv4/tcp_ipv4.c#L544">544</a> 
<a name="L545" href="source/net/ipv4/tcp_ipv4.c#L545">545</a>         if (<a href="ident?i=skb">skb</a>-&gt;ip_summed == <a href="ident?i=CHECKSUM_PARTIAL">CHECKSUM_PARTIAL</a>) {
<a name="L546" href="source/net/ipv4/tcp_ipv4.c#L546">546</a>                 <a href="ident?i=th">th</a>-&gt;<a href="ident?i=check">check</a> = ~tcp_v4_check(<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a>, <a href="ident?i=saddr">saddr</a>, <a href="ident?i=daddr">daddr</a>, 0);
<a name="L547" href="source/net/ipv4/tcp_ipv4.c#L547">547</a>                 <a href="ident?i=skb">skb</a>-&gt;csum_start = <a href="ident?i=skb_transport_header">skb_transport_header</a>(<a href="ident?i=skb">skb</a>) - <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=head">head</a>;
<a name="L548" href="source/net/ipv4/tcp_ipv4.c#L548">548</a>                 <a href="ident?i=skb">skb</a>-&gt;csum_offset = <a href="ident?i=offsetof">offsetof</a>(struct <a href="ident?i=tcphdr">tcphdr</a>, <a href="ident?i=check">check</a>);
<a name="L549" href="source/net/ipv4/tcp_ipv4.c#L549">549</a>         } else {
<a name="L550" href="source/net/ipv4/tcp_ipv4.c#L550">550</a>                 <a href="ident?i=th">th</a>-&gt;<a href="ident?i=check">check</a> = <a href="ident?i=tcp_v4_check">tcp_v4_check</a>(<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a>, <a href="ident?i=saddr">saddr</a>, <a href="ident?i=daddr">daddr</a>,
<a name="L551" href="source/net/ipv4/tcp_ipv4.c#L551">551</a>                                          <a href="ident?i=csum_partial">csum_partial</a>(<a href="ident?i=th">th</a>,
<a name="L552" href="source/net/ipv4/tcp_ipv4.c#L552">552</a>                                                       <a href="ident?i=th">th</a>-&gt;doff &lt;&lt; 2,
<a name="L553" href="source/net/ipv4/tcp_ipv4.c#L553">553</a>                                                       <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=csum">csum</a>));
<a name="L554" href="source/net/ipv4/tcp_ipv4.c#L554">554</a>         }
<a name="L555" href="source/net/ipv4/tcp_ipv4.c#L555">555</a> }
<a name="L556" href="source/net/ipv4/tcp_ipv4.c#L556">556</a> 
<a name="L557" href="source/net/ipv4/tcp_ipv4.c#L557">557</a> <b><i>/* This routine computes an IPv4 TCP checksum. */</i></b>
<a name="L558" href="source/net/ipv4/tcp_ipv4.c#L558">558</a> void <a href="ident?i=tcp_v4_send_check">tcp_v4_send_check</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L559" href="source/net/ipv4/tcp_ipv4.c#L559">559</a> {
<a name="L560" href="source/net/ipv4/tcp_ipv4.c#L560">560</a>         const struct <a href="ident?i=inet_sock">inet_sock</a> *inet = <a href="ident?i=inet_sk">inet_sk</a>(sk);
<a name="L561" href="source/net/ipv4/tcp_ipv4.c#L561">561</a> 
<a name="L562" href="source/net/ipv4/tcp_ipv4.c#L562">562</a>         <a href="ident?i=__tcp_v4_send_check">__tcp_v4_send_check</a>(<a href="ident?i=skb">skb</a>, inet-&gt;inet_saddr, inet-&gt;<a href="ident?i=inet_daddr">inet_daddr</a>);
<a name="L563" href="source/net/ipv4/tcp_ipv4.c#L563">563</a> }
<a name="L564" href="source/net/ipv4/tcp_ipv4.c#L564">564</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=tcp_v4_send_check">tcp_v4_send_check</a>);
<a name="L565" href="source/net/ipv4/tcp_ipv4.c#L565">565</a> 
<a name="L566" href="source/net/ipv4/tcp_ipv4.c#L566">566</a> <b><i>/*</i></b>
<a name="L567" href="source/net/ipv4/tcp_ipv4.c#L567">567</a> <b><i> *      This routine will send an RST to the other tcp.</i></b>
<a name="L568" href="source/net/ipv4/tcp_ipv4.c#L568">568</a> <b><i> *</i></b>
<a name="L569" href="source/net/ipv4/tcp_ipv4.c#L569">569</a> <b><i> *      Someone asks: why I NEVER use socket parameters (TOS, TTL etc.)</i></b>
<a name="L570" href="source/net/ipv4/tcp_ipv4.c#L570">570</a> <b><i> *                    for reset.</i></b>
<a name="L571" href="source/net/ipv4/tcp_ipv4.c#L571">571</a> <b><i> *      Answer: if a packet caused RST, it is not for a socket</i></b>
<a name="L572" href="source/net/ipv4/tcp_ipv4.c#L572">572</a> <b><i> *              existing in our system, if it is matched to a socket,</i></b>
<a name="L573" href="source/net/ipv4/tcp_ipv4.c#L573">573</a> <b><i> *              it is just duplicate segment or bug in other side's TCP.</i></b>
<a name="L574" href="source/net/ipv4/tcp_ipv4.c#L574">574</a> <b><i> *              So that we build reply only basing on parameters</i></b>
<a name="L575" href="source/net/ipv4/tcp_ipv4.c#L575">575</a> <b><i> *              arrived with segment.</i></b>
<a name="L576" href="source/net/ipv4/tcp_ipv4.c#L576">576</a> <b><i> *      Exception: precedence violation. We do not implement it in any case.</i></b>
<a name="L577" href="source/net/ipv4/tcp_ipv4.c#L577">577</a> <b><i> */</i></b>
<a name="L578" href="source/net/ipv4/tcp_ipv4.c#L578">578</a> 
<a name="L579" href="source/net/ipv4/tcp_ipv4.c#L579">579</a> static void <a href="ident?i=tcp_v4_send_reset">tcp_v4_send_reset</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L580" href="source/net/ipv4/tcp_ipv4.c#L580">580</a> {
<a name="L581" href="source/net/ipv4/tcp_ipv4.c#L581">581</a>         const struct <a href="ident?i=tcphdr">tcphdr</a> *<a href="ident?i=th">th</a> = <a href="ident?i=tcp_hdr">tcp_hdr</a>(<a href="ident?i=skb">skb</a>);
<a name="L582" href="source/net/ipv4/tcp_ipv4.c#L582">582</a>         struct {
<a name="L583" href="source/net/ipv4/tcp_ipv4.c#L583">583</a>                 struct <a href="ident?i=tcphdr">tcphdr</a> <a href="ident?i=th">th</a>;
<a name="L584" href="source/net/ipv4/tcp_ipv4.c#L584">584</a> #ifdef CONFIG_TCP_MD5SIG
<a name="L585" href="source/net/ipv4/tcp_ipv4.c#L585">585</a>                 <a href="ident?i=__be32">__be32</a> opt[(<a href="ident?i=TCPOLEN_MD5SIG_ALIGNED">TCPOLEN_MD5SIG_ALIGNED</a> &gt;&gt; 2)];
<a name="L586" href="source/net/ipv4/tcp_ipv4.c#L586">586</a> #endif
<a name="L587" href="source/net/ipv4/tcp_ipv4.c#L587">587</a>         } <a href="ident?i=rep">rep</a>;
<a name="L588" href="source/net/ipv4/tcp_ipv4.c#L588">588</a>         struct <a href="ident?i=ip_reply_arg">ip_reply_arg</a> <a href="ident?i=arg">arg</a>;
<a name="L589" href="source/net/ipv4/tcp_ipv4.c#L589">589</a> #ifdef CONFIG_TCP_MD5SIG
<a name="L590" href="source/net/ipv4/tcp_ipv4.c#L590">590</a>         struct <a href="ident?i=tcp_md5sig_key">tcp_md5sig_key</a> *<a href="ident?i=key">key</a>;
<a name="L591" href="source/net/ipv4/tcp_ipv4.c#L591">591</a>         const <a href="ident?i=__u8">__u8</a> *hash_location = <a href="ident?i=NULL">NULL</a>;
<a name="L592" href="source/net/ipv4/tcp_ipv4.c#L592">592</a>         unsigned char newhash[16];
<a name="L593" href="source/net/ipv4/tcp_ipv4.c#L593">593</a>         int genhash;
<a name="L594" href="source/net/ipv4/tcp_ipv4.c#L594">594</a>         struct <a href="ident?i=sock">sock</a> *sk1 = <a href="ident?i=NULL">NULL</a>;
<a name="L595" href="source/net/ipv4/tcp_ipv4.c#L595">595</a> #endif
<a name="L596" href="source/net/ipv4/tcp_ipv4.c#L596">596</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>;
<a name="L597" href="source/net/ipv4/tcp_ipv4.c#L597">597</a> 
<a name="L598" href="source/net/ipv4/tcp_ipv4.c#L598">598</a>         <b><i>/* Never send a reset in response to a reset. */</i></b>
<a name="L599" href="source/net/ipv4/tcp_ipv4.c#L599">599</a>         if (<a href="ident?i=th">th</a>-&gt;rst)
<a name="L600" href="source/net/ipv4/tcp_ipv4.c#L600">600</a>                 return;
<a name="L601" href="source/net/ipv4/tcp_ipv4.c#L601">601</a> 
<a name="L602" href="source/net/ipv4/tcp_ipv4.c#L602">602</a>         <b><i>/* If sk not NULL, it means we did a successful lookup and incoming</i></b>
<a name="L603" href="source/net/ipv4/tcp_ipv4.c#L603">603</a> <b><i>         * route had to be correct. prequeue might have dropped our dst.</i></b>
<a name="L604" href="source/net/ipv4/tcp_ipv4.c#L604">604</a> <b><i>         */</i></b>
<a name="L605" href="source/net/ipv4/tcp_ipv4.c#L605">605</a>         if (!sk &amp;&amp; <a href="ident?i=skb_rtable">skb_rtable</a>(<a href="ident?i=skb">skb</a>)-&gt;rt_type != RTN_LOCAL)
<a name="L606" href="source/net/ipv4/tcp_ipv4.c#L606">606</a>                 return;
<a name="L607" href="source/net/ipv4/tcp_ipv4.c#L607">607</a> 
<a name="L608" href="source/net/ipv4/tcp_ipv4.c#L608">608</a>         <b><i>/* Swap the send and the receive. */</i></b>
<a name="L609" href="source/net/ipv4/tcp_ipv4.c#L609">609</a>         <a href="ident?i=memset">memset</a>(&amp;<a href="ident?i=rep">rep</a>, 0, sizeof(<a href="ident?i=rep">rep</a>));
<a name="L610" href="source/net/ipv4/tcp_ipv4.c#L610">610</a>         <a href="ident?i=rep">rep</a>.<a href="ident?i=th">th</a>.<a href="ident?i=dest">dest</a>   = <a href="ident?i=th">th</a>-&gt;source;
<a name="L611" href="source/net/ipv4/tcp_ipv4.c#L611">611</a>         <a href="ident?i=rep">rep</a>.<a href="ident?i=th">th</a>.source = <a href="ident?i=th">th</a>-&gt;<a href="ident?i=dest">dest</a>;
<a name="L612" href="source/net/ipv4/tcp_ipv4.c#L612">612</a>         <a href="ident?i=rep">rep</a>.<a href="ident?i=th">th</a>.doff   = sizeof(struct <a href="ident?i=tcphdr">tcphdr</a>) / 4;
<a name="L613" href="source/net/ipv4/tcp_ipv4.c#L613">613</a>         <a href="ident?i=rep">rep</a>.<a href="ident?i=th">th</a>.rst    = 1;
<a name="L614" href="source/net/ipv4/tcp_ipv4.c#L614">614</a> 
<a name="L615" href="source/net/ipv4/tcp_ipv4.c#L615">615</a>         if (<a href="ident?i=th">th</a>-&gt;ack) {
<a name="L616" href="source/net/ipv4/tcp_ipv4.c#L616">616</a>                 <a href="ident?i=rep">rep</a>.<a href="ident?i=th">th</a>.<a href="ident?i=seq">seq</a> = <a href="ident?i=th">th</a>-&gt;ack_seq;
<a name="L617" href="source/net/ipv4/tcp_ipv4.c#L617">617</a>         } else {
<a name="L618" href="source/net/ipv4/tcp_ipv4.c#L618">618</a>                 <a href="ident?i=rep">rep</a>.<a href="ident?i=th">th</a>.ack = 1;
<a name="L619" href="source/net/ipv4/tcp_ipv4.c#L619">619</a>                 <a href="ident?i=rep">rep</a>.<a href="ident?i=th">th</a>.ack_seq = <a href="ident?i=htonl">htonl</a>(<a href="ident?i=ntohl">ntohl</a>(<a href="ident?i=th">th</a>-&gt;<a href="ident?i=seq">seq</a>) + <a href="ident?i=th">th</a>-&gt;syn + <a href="ident?i=th">th</a>-&gt;fin +
<a name="L620" href="source/net/ipv4/tcp_ipv4.c#L620">620</a>                                        <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a> - (<a href="ident?i=th">th</a>-&gt;doff &lt;&lt; 2));
<a name="L621" href="source/net/ipv4/tcp_ipv4.c#L621">621</a>         }
<a name="L622" href="source/net/ipv4/tcp_ipv4.c#L622">622</a> 
<a name="L623" href="source/net/ipv4/tcp_ipv4.c#L623">623</a>         <a href="ident?i=memset">memset</a>(&amp;<a href="ident?i=arg">arg</a>, 0, sizeof(<a href="ident?i=arg">arg</a>));
<a name="L624" href="source/net/ipv4/tcp_ipv4.c#L624">624</a>         <a href="ident?i=arg">arg</a>.iov[0].iov_base = (unsigned char *)&amp;<a href="ident?i=rep">rep</a>;
<a name="L625" href="source/net/ipv4/tcp_ipv4.c#L625">625</a>         <a href="ident?i=arg">arg</a>.iov[0].iov_len  = sizeof(<a href="ident?i=rep">rep</a>.<a href="ident?i=th">th</a>);
<a name="L626" href="source/net/ipv4/tcp_ipv4.c#L626">626</a> 
<a name="L627" href="source/net/ipv4/tcp_ipv4.c#L627">627</a>         <a href="ident?i=net">net</a> = sk ? <a href="ident?i=sock_net">sock_net</a>(sk) : <a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=skb_dst">skb_dst</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=dev">dev</a>);
<a name="L628" href="source/net/ipv4/tcp_ipv4.c#L628">628</a> #ifdef CONFIG_TCP_MD5SIG
<a name="L629" href="source/net/ipv4/tcp_ipv4.c#L629">629</a>         hash_location = <a href="ident?i=tcp_parse_md5sig_option">tcp_parse_md5sig_option</a>(<a href="ident?i=th">th</a>);
<a name="L630" href="source/net/ipv4/tcp_ipv4.c#L630">630</a>         if (!sk &amp;&amp; hash_location) {
<a name="L631" href="source/net/ipv4/tcp_ipv4.c#L631">631</a>                 <b><i>/*</i></b>
<a name="L632" href="source/net/ipv4/tcp_ipv4.c#L632">632</a> <b><i>                 * active side is lost. Try to find listening socket through</i></b>
<a name="L633" href="source/net/ipv4/tcp_ipv4.c#L633">633</a> <b><i>                 * source port, and then find md5 key through listening socket.</i></b>
<a name="L634" href="source/net/ipv4/tcp_ipv4.c#L634">634</a> <b><i>                 * we are not loose security here:</i></b>
<a name="L635" href="source/net/ipv4/tcp_ipv4.c#L635">635</a> <b><i>                 * Incoming packet is checked with md5 hash with finding key,</i></b>
<a name="L636" href="source/net/ipv4/tcp_ipv4.c#L636">636</a> <b><i>                 * no RST generated if md5 hash doesn't match.</i></b>
<a name="L637" href="source/net/ipv4/tcp_ipv4.c#L637">637</a> <b><i>                 */</i></b>
<a name="L638" href="source/net/ipv4/tcp_ipv4.c#L638">638</a>                 sk1 = <a href="ident?i=__inet_lookup_listener">__inet_lookup_listener</a>(<a href="ident?i=net">net</a>,
<a name="L639" href="source/net/ipv4/tcp_ipv4.c#L639">639</a>                                              &amp;<a href="ident?i=tcp_hashinfo">tcp_hashinfo</a>, <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=saddr">saddr</a>,
<a name="L640" href="source/net/ipv4/tcp_ipv4.c#L640">640</a>                                              <a href="ident?i=th">th</a>-&gt;source, <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=daddr">daddr</a>,
<a name="L641" href="source/net/ipv4/tcp_ipv4.c#L641">641</a>                                              <a href="ident?i=ntohs">ntohs</a>(<a href="ident?i=th">th</a>-&gt;source), <a href="ident?i=inet_iif">inet_iif</a>(<a href="ident?i=skb">skb</a>));
<a name="L642" href="source/net/ipv4/tcp_ipv4.c#L642">642</a>                 <b><i>/* don't send rst if it can't find key */</i></b>
<a name="L643" href="source/net/ipv4/tcp_ipv4.c#L643">643</a>                 if (!sk1)
<a name="L644" href="source/net/ipv4/tcp_ipv4.c#L644">644</a>                         return;
<a name="L645" href="source/net/ipv4/tcp_ipv4.c#L645">645</a>                 <a href="ident?i=rcu_read_lock">rcu_read_lock</a>();
<a name="L646" href="source/net/ipv4/tcp_ipv4.c#L646">646</a>                 <a href="ident?i=key">key</a> = <a href="ident?i=tcp_md5_do_lookup">tcp_md5_do_lookup</a>(sk1, (union <a href="ident?i=tcp_md5_addr">tcp_md5_addr</a> *)
<a name="L647" href="source/net/ipv4/tcp_ipv4.c#L647">647</a>                                         &amp;<a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=saddr">saddr</a>, <a href="ident?i=AF_INET">AF_INET</a>);
<a name="L648" href="source/net/ipv4/tcp_ipv4.c#L648">648</a>                 if (!<a href="ident?i=key">key</a>)
<a name="L649" href="source/net/ipv4/tcp_ipv4.c#L649">649</a>                         goto release_sk1;
<a name="L650" href="source/net/ipv4/tcp_ipv4.c#L650">650</a> 
<a name="L651" href="source/net/ipv4/tcp_ipv4.c#L651">651</a>                 genhash = <a href="ident?i=tcp_v4_md5_hash_skb">tcp_v4_md5_hash_skb</a>(newhash, <a href="ident?i=key">key</a>, <a href="ident?i=NULL">NULL</a>, <a href="ident?i=skb">skb</a>);
<a name="L652" href="source/net/ipv4/tcp_ipv4.c#L652">652</a>                 if (genhash || <a href="ident?i=memcmp">memcmp</a>(hash_location, newhash, 16) != 0)
<a name="L653" href="source/net/ipv4/tcp_ipv4.c#L653">653</a>                         goto release_sk1;
<a name="L654" href="source/net/ipv4/tcp_ipv4.c#L654">654</a>         } else {
<a name="L655" href="source/net/ipv4/tcp_ipv4.c#L655">655</a>                 <a href="ident?i=key">key</a> = sk ? <a href="ident?i=tcp_md5_do_lookup">tcp_md5_do_lookup</a>(sk, (union <a href="ident?i=tcp_md5_addr">tcp_md5_addr</a> *)
<a name="L656" href="source/net/ipv4/tcp_ipv4.c#L656">656</a>                                              &amp;<a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=saddr">saddr</a>,
<a name="L657" href="source/net/ipv4/tcp_ipv4.c#L657">657</a>                                              <a href="ident?i=AF_INET">AF_INET</a>) : <a href="ident?i=NULL">NULL</a>;
<a name="L658" href="source/net/ipv4/tcp_ipv4.c#L658">658</a>         }
<a name="L659" href="source/net/ipv4/tcp_ipv4.c#L659">659</a> 
<a name="L660" href="source/net/ipv4/tcp_ipv4.c#L660">660</a>         if (<a href="ident?i=key">key</a>) {
<a name="L661" href="source/net/ipv4/tcp_ipv4.c#L661">661</a>                 <a href="ident?i=rep">rep</a>.opt[0] = <a href="ident?i=htonl">htonl</a>((<a href="ident?i=TCPOPT_NOP">TCPOPT_NOP</a> &lt;&lt; 24) |
<a name="L662" href="source/net/ipv4/tcp_ipv4.c#L662">662</a>                                    (<a href="ident?i=TCPOPT_NOP">TCPOPT_NOP</a> &lt;&lt; 16) |
<a name="L663" href="source/net/ipv4/tcp_ipv4.c#L663">663</a>                                    (<a href="ident?i=TCPOPT_MD5SIG">TCPOPT_MD5SIG</a> &lt;&lt; 8) |
<a name="L664" href="source/net/ipv4/tcp_ipv4.c#L664">664</a>                                    <a href="ident?i=TCPOLEN_MD5SIG">TCPOLEN_MD5SIG</a>);
<a name="L665" href="source/net/ipv4/tcp_ipv4.c#L665">665</a>                 <b><i>/* Update length and the length the header thinks exists */</i></b>
<a name="L666" href="source/net/ipv4/tcp_ipv4.c#L666">666</a>                 <a href="ident?i=arg">arg</a>.iov[0].iov_len += <a href="ident?i=TCPOLEN_MD5SIG_ALIGNED">TCPOLEN_MD5SIG_ALIGNED</a>;
<a name="L667" href="source/net/ipv4/tcp_ipv4.c#L667">667</a>                 <a href="ident?i=rep">rep</a>.<a href="ident?i=th">th</a>.doff = <a href="ident?i=arg">arg</a>.iov[0].iov_len / 4;
<a name="L668" href="source/net/ipv4/tcp_ipv4.c#L668">668</a> 
<a name="L669" href="source/net/ipv4/tcp_ipv4.c#L669">669</a>                 <a href="ident?i=tcp_v4_md5_hash_hdr">tcp_v4_md5_hash_hdr</a>((<a href="ident?i=__u8">__u8</a> *) &amp;<a href="ident?i=rep">rep</a>.opt[1],
<a name="L670" href="source/net/ipv4/tcp_ipv4.c#L670">670</a>                                      <a href="ident?i=key">key</a>, <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=saddr">saddr</a>,
<a name="L671" href="source/net/ipv4/tcp_ipv4.c#L671">671</a>                                      <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=daddr">daddr</a>, &amp;<a href="ident?i=rep">rep</a>.<a href="ident?i=th">th</a>);
<a name="L672" href="source/net/ipv4/tcp_ipv4.c#L672">672</a>         }
<a name="L673" href="source/net/ipv4/tcp_ipv4.c#L673">673</a> #endif
<a name="L674" href="source/net/ipv4/tcp_ipv4.c#L674">674</a>         <a href="ident?i=arg">arg</a>.<a href="ident?i=csum">csum</a> = <a href="ident?i=csum_tcpudp_nofold">csum_tcpudp_nofold</a>(<a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=daddr">daddr</a>,
<a name="L675" href="source/net/ipv4/tcp_ipv4.c#L675">675</a>                                       <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=saddr">saddr</a>, <b><i>/* XXX */</i></b>
<a name="L676" href="source/net/ipv4/tcp_ipv4.c#L676">676</a>                                       <a href="ident?i=arg">arg</a>.iov[0].iov_len, <a href="ident?i=IPPROTO_TCP">IPPROTO_TCP</a>, 0);
<a name="L677" href="source/net/ipv4/tcp_ipv4.c#L677">677</a>         <a href="ident?i=arg">arg</a>.csumoffset = <a href="ident?i=offsetof">offsetof</a>(struct <a href="ident?i=tcphdr">tcphdr</a>, <a href="ident?i=check">check</a>) / 2;
<a name="L678" href="source/net/ipv4/tcp_ipv4.c#L678">678</a>         <a href="ident?i=arg">arg</a>.<a href="ident?i=flags">flags</a> = (sk &amp;&amp; <a href="ident?i=inet_sk">inet_sk</a>(sk)-&gt;transparent) ? <a href="ident?i=IP_REPLY_ARG_NOSRCCHECK">IP_REPLY_ARG_NOSRCCHECK</a> : 0;
<a name="L679" href="source/net/ipv4/tcp_ipv4.c#L679">679</a>         <b><i>/* When socket is gone, all binding information is lost.</i></b>
<a name="L680" href="source/net/ipv4/tcp_ipv4.c#L680">680</a> <b><i>         * routing might fail in this case. No choice here, if we choose to force</i></b>
<a name="L681" href="source/net/ipv4/tcp_ipv4.c#L681">681</a> <b><i>         * input interface, we will misroute in case of asymmetric route.</i></b>
<a name="L682" href="source/net/ipv4/tcp_ipv4.c#L682">682</a> <b><i>         */</i></b>
<a name="L683" href="source/net/ipv4/tcp_ipv4.c#L683">683</a>         if (sk)
<a name="L684" href="source/net/ipv4/tcp_ipv4.c#L684">684</a>                 <a href="ident?i=arg">arg</a>.bound_dev_if = sk-&gt;<a href="ident?i=sk_bound_dev_if">sk_bound_dev_if</a>;
<a name="L685" href="source/net/ipv4/tcp_ipv4.c#L685">685</a> 
<a name="L686" href="source/net/ipv4/tcp_ipv4.c#L686">686</a>         <a href="ident?i=arg">arg</a>.tos = <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;tos;
<a name="L687" href="source/net/ipv4/tcp_ipv4.c#L687">687</a>         <a href="ident?i=ip_send_unicast_reply">ip_send_unicast_reply</a>(*<a href="ident?i=this_cpu_ptr">this_cpu_ptr</a>(<a href="ident?i=net">net</a>-&gt;ipv4.<a href="ident?i=tcp_sk">tcp_sk</a>),
<a name="L688" href="source/net/ipv4/tcp_ipv4.c#L688">688</a>                               <a href="ident?i=skb">skb</a>, &amp;<a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=header">header</a>.h4.opt,
<a name="L689" href="source/net/ipv4/tcp_ipv4.c#L689">689</a>                               <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=saddr">saddr</a>, <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=daddr">daddr</a>,
<a name="L690" href="source/net/ipv4/tcp_ipv4.c#L690">690</a>                               &amp;<a href="ident?i=arg">arg</a>, <a href="ident?i=arg">arg</a>.iov[0].iov_len);
<a name="L691" href="source/net/ipv4/tcp_ipv4.c#L691">691</a> 
<a name="L692" href="source/net/ipv4/tcp_ipv4.c#L692">692</a>         <a href="ident?i=TCP_INC_STATS_BH">TCP_INC_STATS_BH</a>(<a href="ident?i=net">net</a>, TCP_MIB_OUTSEGS);
<a name="L693" href="source/net/ipv4/tcp_ipv4.c#L693">693</a>         <a href="ident?i=TCP_INC_STATS_BH">TCP_INC_STATS_BH</a>(<a href="ident?i=net">net</a>, TCP_MIB_OUTRSTS);
<a name="L694" href="source/net/ipv4/tcp_ipv4.c#L694">694</a> 
<a name="L695" href="source/net/ipv4/tcp_ipv4.c#L695">695</a> #ifdef CONFIG_TCP_MD5SIG
<a name="L696" href="source/net/ipv4/tcp_ipv4.c#L696">696</a> release_sk1:
<a name="L697" href="source/net/ipv4/tcp_ipv4.c#L697">697</a>         if (sk1) {
<a name="L698" href="source/net/ipv4/tcp_ipv4.c#L698">698</a>                 <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L699" href="source/net/ipv4/tcp_ipv4.c#L699">699</a>                 <a href="ident?i=sock_put">sock_put</a>(sk1);
<a name="L700" href="source/net/ipv4/tcp_ipv4.c#L700">700</a>         }
<a name="L701" href="source/net/ipv4/tcp_ipv4.c#L701">701</a> #endif
<a name="L702" href="source/net/ipv4/tcp_ipv4.c#L702">702</a> }
<a name="L703" href="source/net/ipv4/tcp_ipv4.c#L703">703</a> 
<a name="L704" href="source/net/ipv4/tcp_ipv4.c#L704">704</a> <b><i>/* The code following below sending ACKs in SYN-RECV and TIME-WAIT states</i></b>
<a name="L705" href="source/net/ipv4/tcp_ipv4.c#L705">705</a> <b><i>   outside socket context is ugly, certainly. What can I do?</i></b>
<a name="L706" href="source/net/ipv4/tcp_ipv4.c#L706">706</a> <b><i> */</i></b>
<a name="L707" href="source/net/ipv4/tcp_ipv4.c#L707">707</a> 
<a name="L708" href="source/net/ipv4/tcp_ipv4.c#L708">708</a> static void <a href="ident?i=tcp_v4_send_ack">tcp_v4_send_ack</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, <a href="ident?i=u32">u32</a> <a href="ident?i=seq">seq</a>, <a href="ident?i=u32">u32</a> ack,
<a name="L709" href="source/net/ipv4/tcp_ipv4.c#L709">709</a>                             <a href="ident?i=u32">u32</a> <a href="ident?i=win">win</a>, <a href="ident?i=u32">u32</a> tsval, <a href="ident?i=u32">u32</a> tsecr, int oif,
<a name="L710" href="source/net/ipv4/tcp_ipv4.c#L710">710</a>                             struct <a href="ident?i=tcp_md5sig_key">tcp_md5sig_key</a> *<a href="ident?i=key">key</a>,
<a name="L711" href="source/net/ipv4/tcp_ipv4.c#L711">711</a>                             int reply_flags, <a href="ident?i=u8">u8</a> tos)
<a name="L712" href="source/net/ipv4/tcp_ipv4.c#L712">712</a> {
<a name="L713" href="source/net/ipv4/tcp_ipv4.c#L713">713</a>         const struct <a href="ident?i=tcphdr">tcphdr</a> *<a href="ident?i=th">th</a> = <a href="ident?i=tcp_hdr">tcp_hdr</a>(<a href="ident?i=skb">skb</a>);
<a name="L714" href="source/net/ipv4/tcp_ipv4.c#L714">714</a>         struct {
<a name="L715" href="source/net/ipv4/tcp_ipv4.c#L715">715</a>                 struct <a href="ident?i=tcphdr">tcphdr</a> <a href="ident?i=th">th</a>;
<a name="L716" href="source/net/ipv4/tcp_ipv4.c#L716">716</a>                 <a href="ident?i=__be32">__be32</a> opt[(<a href="ident?i=TCPOLEN_TSTAMP_ALIGNED">TCPOLEN_TSTAMP_ALIGNED</a> &gt;&gt; 2)
<a name="L717" href="source/net/ipv4/tcp_ipv4.c#L717">717</a> #ifdef CONFIG_TCP_MD5SIG
<a name="L718" href="source/net/ipv4/tcp_ipv4.c#L718">718</a>                            + (<a href="ident?i=TCPOLEN_MD5SIG_ALIGNED">TCPOLEN_MD5SIG_ALIGNED</a> &gt;&gt; 2)
<a name="L719" href="source/net/ipv4/tcp_ipv4.c#L719">719</a> #endif
<a name="L720" href="source/net/ipv4/tcp_ipv4.c#L720">720</a>                         ];
<a name="L721" href="source/net/ipv4/tcp_ipv4.c#L721">721</a>         } <a href="ident?i=rep">rep</a>;
<a name="L722" href="source/net/ipv4/tcp_ipv4.c#L722">722</a>         struct <a href="ident?i=ip_reply_arg">ip_reply_arg</a> <a href="ident?i=arg">arg</a>;
<a name="L723" href="source/net/ipv4/tcp_ipv4.c#L723">723</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=skb_dst">skb_dst</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=dev">dev</a>);
<a name="L724" href="source/net/ipv4/tcp_ipv4.c#L724">724</a> 
<a name="L725" href="source/net/ipv4/tcp_ipv4.c#L725">725</a>         <a href="ident?i=memset">memset</a>(&amp;<a href="ident?i=rep">rep</a>.<a href="ident?i=th">th</a>, 0, sizeof(struct <a href="ident?i=tcphdr">tcphdr</a>));
<a name="L726" href="source/net/ipv4/tcp_ipv4.c#L726">726</a>         <a href="ident?i=memset">memset</a>(&amp;<a href="ident?i=arg">arg</a>, 0, sizeof(<a href="ident?i=arg">arg</a>));
<a name="L727" href="source/net/ipv4/tcp_ipv4.c#L727">727</a> 
<a name="L728" href="source/net/ipv4/tcp_ipv4.c#L728">728</a>         <a href="ident?i=arg">arg</a>.iov[0].iov_base = (unsigned char *)&amp;<a href="ident?i=rep">rep</a>;
<a name="L729" href="source/net/ipv4/tcp_ipv4.c#L729">729</a>         <a href="ident?i=arg">arg</a>.iov[0].iov_len  = sizeof(<a href="ident?i=rep">rep</a>.<a href="ident?i=th">th</a>);
<a name="L730" href="source/net/ipv4/tcp_ipv4.c#L730">730</a>         if (tsecr) {
<a name="L731" href="source/net/ipv4/tcp_ipv4.c#L731">731</a>                 <a href="ident?i=rep">rep</a>.opt[0] = <a href="ident?i=htonl">htonl</a>((<a href="ident?i=TCPOPT_NOP">TCPOPT_NOP</a> &lt;&lt; 24) | (<a href="ident?i=TCPOPT_NOP">TCPOPT_NOP</a> &lt;&lt; 16) |
<a name="L732" href="source/net/ipv4/tcp_ipv4.c#L732">732</a>                                    (<a href="ident?i=TCPOPT_TIMESTAMP">TCPOPT_TIMESTAMP</a> &lt;&lt; 8) |
<a name="L733" href="source/net/ipv4/tcp_ipv4.c#L733">733</a>                                    <a href="ident?i=TCPOLEN_TIMESTAMP">TCPOLEN_TIMESTAMP</a>);
<a name="L734" href="source/net/ipv4/tcp_ipv4.c#L734">734</a>                 <a href="ident?i=rep">rep</a>.opt[1] = <a href="ident?i=htonl">htonl</a>(tsval);
<a name="L735" href="source/net/ipv4/tcp_ipv4.c#L735">735</a>                 <a href="ident?i=rep">rep</a>.opt[2] = <a href="ident?i=htonl">htonl</a>(tsecr);
<a name="L736" href="source/net/ipv4/tcp_ipv4.c#L736">736</a>                 <a href="ident?i=arg">arg</a>.iov[0].iov_len += <a href="ident?i=TCPOLEN_TSTAMP_ALIGNED">TCPOLEN_TSTAMP_ALIGNED</a>;
<a name="L737" href="source/net/ipv4/tcp_ipv4.c#L737">737</a>         }
<a name="L738" href="source/net/ipv4/tcp_ipv4.c#L738">738</a> 
<a name="L739" href="source/net/ipv4/tcp_ipv4.c#L739">739</a>         <b><i>/* Swap the send and the receive. */</i></b>
<a name="L740" href="source/net/ipv4/tcp_ipv4.c#L740">740</a>         <a href="ident?i=rep">rep</a>.<a href="ident?i=th">th</a>.<a href="ident?i=dest">dest</a>    = <a href="ident?i=th">th</a>-&gt;source;
<a name="L741" href="source/net/ipv4/tcp_ipv4.c#L741">741</a>         <a href="ident?i=rep">rep</a>.<a href="ident?i=th">th</a>.source  = <a href="ident?i=th">th</a>-&gt;<a href="ident?i=dest">dest</a>;
<a name="L742" href="source/net/ipv4/tcp_ipv4.c#L742">742</a>         <a href="ident?i=rep">rep</a>.<a href="ident?i=th">th</a>.doff    = <a href="ident?i=arg">arg</a>.iov[0].iov_len / 4;
<a name="L743" href="source/net/ipv4/tcp_ipv4.c#L743">743</a>         <a href="ident?i=rep">rep</a>.<a href="ident?i=th">th</a>.<a href="ident?i=seq">seq</a>     = <a href="ident?i=htonl">htonl</a>(<a href="ident?i=seq">seq</a>);
<a name="L744" href="source/net/ipv4/tcp_ipv4.c#L744">744</a>         <a href="ident?i=rep">rep</a>.<a href="ident?i=th">th</a>.ack_seq = <a href="ident?i=htonl">htonl</a>(ack);
<a name="L745" href="source/net/ipv4/tcp_ipv4.c#L745">745</a>         <a href="ident?i=rep">rep</a>.<a href="ident?i=th">th</a>.ack     = 1;
<a name="L746" href="source/net/ipv4/tcp_ipv4.c#L746">746</a>         <a href="ident?i=rep">rep</a>.<a href="ident?i=th">th</a>.<a href="ident?i=window">window</a>  = <a href="ident?i=htons">htons</a>(<a href="ident?i=win">win</a>);
<a name="L747" href="source/net/ipv4/tcp_ipv4.c#L747">747</a> 
<a name="L748" href="source/net/ipv4/tcp_ipv4.c#L748">748</a> #ifdef CONFIG_TCP_MD5SIG
<a name="L749" href="source/net/ipv4/tcp_ipv4.c#L749">749</a>         if (<a href="ident?i=key">key</a>) {
<a name="L750" href="source/net/ipv4/tcp_ipv4.c#L750">750</a>                 int <a href="ident?i=offset">offset</a> = (tsecr) ? 3 : 0;
<a name="L751" href="source/net/ipv4/tcp_ipv4.c#L751">751</a> 
<a name="L752" href="source/net/ipv4/tcp_ipv4.c#L752">752</a>                 <a href="ident?i=rep">rep</a>.opt[<a href="ident?i=offset">offset</a>++] = <a href="ident?i=htonl">htonl</a>((<a href="ident?i=TCPOPT_NOP">TCPOPT_NOP</a> &lt;&lt; 24) |
<a name="L753" href="source/net/ipv4/tcp_ipv4.c#L753">753</a>                                           (<a href="ident?i=TCPOPT_NOP">TCPOPT_NOP</a> &lt;&lt; 16) |
<a name="L754" href="source/net/ipv4/tcp_ipv4.c#L754">754</a>                                           (<a href="ident?i=TCPOPT_MD5SIG">TCPOPT_MD5SIG</a> &lt;&lt; 8) |
<a name="L755" href="source/net/ipv4/tcp_ipv4.c#L755">755</a>                                           <a href="ident?i=TCPOLEN_MD5SIG">TCPOLEN_MD5SIG</a>);
<a name="L756" href="source/net/ipv4/tcp_ipv4.c#L756">756</a>                 <a href="ident?i=arg">arg</a>.iov[0].iov_len += <a href="ident?i=TCPOLEN_MD5SIG_ALIGNED">TCPOLEN_MD5SIG_ALIGNED</a>;
<a name="L757" href="source/net/ipv4/tcp_ipv4.c#L757">757</a>                 <a href="ident?i=rep">rep</a>.<a href="ident?i=th">th</a>.doff = <a href="ident?i=arg">arg</a>.iov[0].iov_len/4;
<a name="L758" href="source/net/ipv4/tcp_ipv4.c#L758">758</a> 
<a name="L759" href="source/net/ipv4/tcp_ipv4.c#L759">759</a>                 <a href="ident?i=tcp_v4_md5_hash_hdr">tcp_v4_md5_hash_hdr</a>((<a href="ident?i=__u8">__u8</a> *) &amp;<a href="ident?i=rep">rep</a>.opt[<a href="ident?i=offset">offset</a>],
<a name="L760" href="source/net/ipv4/tcp_ipv4.c#L760">760</a>                                     <a href="ident?i=key">key</a>, <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=saddr">saddr</a>,
<a name="L761" href="source/net/ipv4/tcp_ipv4.c#L761">761</a>                                     <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=daddr">daddr</a>, &amp;<a href="ident?i=rep">rep</a>.<a href="ident?i=th">th</a>);
<a name="L762" href="source/net/ipv4/tcp_ipv4.c#L762">762</a>         }
<a name="L763" href="source/net/ipv4/tcp_ipv4.c#L763">763</a> #endif
<a name="L764" href="source/net/ipv4/tcp_ipv4.c#L764">764</a>         <a href="ident?i=arg">arg</a>.<a href="ident?i=flags">flags</a> = reply_flags;
<a name="L765" href="source/net/ipv4/tcp_ipv4.c#L765">765</a>         <a href="ident?i=arg">arg</a>.<a href="ident?i=csum">csum</a> = <a href="ident?i=csum_tcpudp_nofold">csum_tcpudp_nofold</a>(<a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=daddr">daddr</a>,
<a name="L766" href="source/net/ipv4/tcp_ipv4.c#L766">766</a>                                       <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=saddr">saddr</a>, <b><i>/* XXX */</i></b>
<a name="L767" href="source/net/ipv4/tcp_ipv4.c#L767">767</a>                                       <a href="ident?i=arg">arg</a>.iov[0].iov_len, <a href="ident?i=IPPROTO_TCP">IPPROTO_TCP</a>, 0);
<a name="L768" href="source/net/ipv4/tcp_ipv4.c#L768">768</a>         <a href="ident?i=arg">arg</a>.csumoffset = <a href="ident?i=offsetof">offsetof</a>(struct <a href="ident?i=tcphdr">tcphdr</a>, <a href="ident?i=check">check</a>) / 2;
<a name="L769" href="source/net/ipv4/tcp_ipv4.c#L769">769</a>         if (oif)
<a name="L770" href="source/net/ipv4/tcp_ipv4.c#L770">770</a>                 <a href="ident?i=arg">arg</a>.bound_dev_if = oif;
<a name="L771" href="source/net/ipv4/tcp_ipv4.c#L771">771</a>         <a href="ident?i=arg">arg</a>.tos = tos;
<a name="L772" href="source/net/ipv4/tcp_ipv4.c#L772">772</a>         <a href="ident?i=ip_send_unicast_reply">ip_send_unicast_reply</a>(*<a href="ident?i=this_cpu_ptr">this_cpu_ptr</a>(<a href="ident?i=net">net</a>-&gt;ipv4.<a href="ident?i=tcp_sk">tcp_sk</a>),
<a name="L773" href="source/net/ipv4/tcp_ipv4.c#L773">773</a>                               <a href="ident?i=skb">skb</a>, &amp;<a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=header">header</a>.h4.opt,
<a name="L774" href="source/net/ipv4/tcp_ipv4.c#L774">774</a>                               <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=saddr">saddr</a>, <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=daddr">daddr</a>,
<a name="L775" href="source/net/ipv4/tcp_ipv4.c#L775">775</a>                               &amp;<a href="ident?i=arg">arg</a>, <a href="ident?i=arg">arg</a>.iov[0].iov_len);
<a name="L776" href="source/net/ipv4/tcp_ipv4.c#L776">776</a> 
<a name="L777" href="source/net/ipv4/tcp_ipv4.c#L777">777</a>         <a href="ident?i=TCP_INC_STATS_BH">TCP_INC_STATS_BH</a>(<a href="ident?i=net">net</a>, TCP_MIB_OUTSEGS);
<a name="L778" href="source/net/ipv4/tcp_ipv4.c#L778">778</a> }
<a name="L779" href="source/net/ipv4/tcp_ipv4.c#L779">779</a> 
<a name="L780" href="source/net/ipv4/tcp_ipv4.c#L780">780</a> static void <a href="ident?i=tcp_v4_timewait_ack">tcp_v4_timewait_ack</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L781" href="source/net/ipv4/tcp_ipv4.c#L781">781</a> {
<a name="L782" href="source/net/ipv4/tcp_ipv4.c#L782">782</a>         struct <a href="ident?i=inet_timewait_sock">inet_timewait_sock</a> *<a href="ident?i=tw">tw</a> = <a href="ident?i=inet_twsk">inet_twsk</a>(sk);
<a name="L783" href="source/net/ipv4/tcp_ipv4.c#L783">783</a>         struct <a href="ident?i=tcp_timewait_sock">tcp_timewait_sock</a> *tcptw = <a href="ident?i=tcp_twsk">tcp_twsk</a>(sk);
<a name="L784" href="source/net/ipv4/tcp_ipv4.c#L784">784</a> 
<a name="L785" href="source/net/ipv4/tcp_ipv4.c#L785">785</a>         <a href="ident?i=tcp_v4_send_ack">tcp_v4_send_ack</a>(<a href="ident?i=skb">skb</a>, tcptw-&gt;tw_snd_nxt, tcptw-&gt;tw_rcv_nxt,
<a name="L786" href="source/net/ipv4/tcp_ipv4.c#L786">786</a>                         tcptw-&gt;tw_rcv_wnd &gt;&gt; <a href="ident?i=tw">tw</a>-&gt;tw_rcv_wscale,
<a name="L787" href="source/net/ipv4/tcp_ipv4.c#L787">787</a>                         <a href="ident?i=tcp_time_stamp">tcp_time_stamp</a> + tcptw-&gt;tw_ts_offset,
<a name="L788" href="source/net/ipv4/tcp_ipv4.c#L788">788</a>                         tcptw-&gt;tw_ts_recent,
<a name="L789" href="source/net/ipv4/tcp_ipv4.c#L789">789</a>                         <a href="ident?i=tw">tw</a>-&gt;<a href="ident?i=tw_bound_dev_if">tw_bound_dev_if</a>,
<a name="L790" href="source/net/ipv4/tcp_ipv4.c#L790">790</a>                         <a href="ident?i=tcp_twsk_md5_key">tcp_twsk_md5_key</a>(tcptw),
<a name="L791" href="source/net/ipv4/tcp_ipv4.c#L791">791</a>                         <a href="ident?i=tw">tw</a>-&gt;tw_transparent ? <a href="ident?i=IP_REPLY_ARG_NOSRCCHECK">IP_REPLY_ARG_NOSRCCHECK</a> : 0,
<a name="L792" href="source/net/ipv4/tcp_ipv4.c#L792">792</a>                         <a href="ident?i=tw">tw</a>-&gt;tw_tos
<a name="L793" href="source/net/ipv4/tcp_ipv4.c#L793">793</a>                         );
<a name="L794" href="source/net/ipv4/tcp_ipv4.c#L794">794</a> 
<a name="L795" href="source/net/ipv4/tcp_ipv4.c#L795">795</a>         <a href="ident?i=inet_twsk_put">inet_twsk_put</a>(<a href="ident?i=tw">tw</a>);
<a name="L796" href="source/net/ipv4/tcp_ipv4.c#L796">796</a> }
<a name="L797" href="source/net/ipv4/tcp_ipv4.c#L797">797</a> 
<a name="L798" href="source/net/ipv4/tcp_ipv4.c#L798">798</a> static void <a href="ident?i=tcp_v4_reqsk_send_ack">tcp_v4_reqsk_send_ack</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
<a name="L799" href="source/net/ipv4/tcp_ipv4.c#L799">799</a>                                   struct <a href="ident?i=request_sock">request_sock</a> *<a href="ident?i=req">req</a>)
<a name="L800" href="source/net/ipv4/tcp_ipv4.c#L800">800</a> {
<a name="L801" href="source/net/ipv4/tcp_ipv4.c#L801">801</a>         <b><i>/* sk-&gt;sk_state == TCP_LISTEN -&gt; for regular TCP_SYN_RECV</i></b>
<a name="L802" href="source/net/ipv4/tcp_ipv4.c#L802">802</a> <b><i>         * sk-&gt;sk_state == TCP_SYN_RECV -&gt; for Fast Open.</i></b>
<a name="L803" href="source/net/ipv4/tcp_ipv4.c#L803">803</a> <b><i>         */</i></b>
<a name="L804" href="source/net/ipv4/tcp_ipv4.c#L804">804</a>         <a href="ident?i=tcp_v4_send_ack">tcp_v4_send_ack</a>(<a href="ident?i=skb">skb</a>, (sk-&gt;<a href="ident?i=sk_state">sk_state</a> == TCP_LISTEN) ?
<a name="L805" href="source/net/ipv4/tcp_ipv4.c#L805">805</a>                         <a href="ident?i=tcp_rsk">tcp_rsk</a>(<a href="ident?i=req">req</a>)-&gt;snt_isn + 1 : <a href="ident?i=tcp_sk">tcp_sk</a>(sk)-&gt;snd_nxt,
<a name="L806" href="source/net/ipv4/tcp_ipv4.c#L806">806</a>                         <a href="ident?i=tcp_rsk">tcp_rsk</a>(<a href="ident?i=req">req</a>)-&gt;rcv_nxt, <a href="ident?i=req">req</a>-&gt;rcv_wnd,
<a name="L807" href="source/net/ipv4/tcp_ipv4.c#L807">807</a>                         <a href="ident?i=tcp_time_stamp">tcp_time_stamp</a>,
<a name="L808" href="source/net/ipv4/tcp_ipv4.c#L808">808</a>                         <a href="ident?i=req">req</a>-&gt;ts_recent,
<a name="L809" href="source/net/ipv4/tcp_ipv4.c#L809">809</a>                         0,
<a name="L810" href="source/net/ipv4/tcp_ipv4.c#L810">810</a>                         <a href="ident?i=tcp_md5_do_lookup">tcp_md5_do_lookup</a>(sk, (union <a href="ident?i=tcp_md5_addr">tcp_md5_addr</a> *)&amp;<a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=daddr">daddr</a>,
<a name="L811" href="source/net/ipv4/tcp_ipv4.c#L811">811</a>                                           <a href="ident?i=AF_INET">AF_INET</a>),
<a name="L812" href="source/net/ipv4/tcp_ipv4.c#L812">812</a>                         <a href="ident?i=inet_rsk">inet_rsk</a>(<a href="ident?i=req">req</a>)-&gt;no_srccheck ? <a href="ident?i=IP_REPLY_ARG_NOSRCCHECK">IP_REPLY_ARG_NOSRCCHECK</a> : 0,
<a name="L813" href="source/net/ipv4/tcp_ipv4.c#L813">813</a>                         <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;tos);
<a name="L814" href="source/net/ipv4/tcp_ipv4.c#L814">814</a> }
<a name="L815" href="source/net/ipv4/tcp_ipv4.c#L815">815</a> 
<a name="L816" href="source/net/ipv4/tcp_ipv4.c#L816">816</a> <b><i>/*</i></b>
<a name="L817" href="source/net/ipv4/tcp_ipv4.c#L817">817</a> <b><i> *      Send a SYN-ACK after having received a SYN.</i></b>
<a name="L818" href="source/net/ipv4/tcp_ipv4.c#L818">818</a> <b><i> *      This still operates on a request_sock only, not on a big</i></b>
<a name="L819" href="source/net/ipv4/tcp_ipv4.c#L819">819</a> <b><i> *      socket.</i></b>
<a name="L820" href="source/net/ipv4/tcp_ipv4.c#L820">820</a> <b><i> */</i></b>
<a name="L821" href="source/net/ipv4/tcp_ipv4.c#L821">821</a> static int <a href="ident?i=tcp_v4_send_synack">tcp_v4_send_synack</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=dst_entry">dst_entry</a> *<a href="ident?i=dst">dst</a>,
<a name="L822" href="source/net/ipv4/tcp_ipv4.c#L822">822</a>                               struct <a href="ident?i=flowi">flowi</a> *fl,
<a name="L823" href="source/net/ipv4/tcp_ipv4.c#L823">823</a>                               struct <a href="ident?i=request_sock">request_sock</a> *<a href="ident?i=req">req</a>,
<a name="L824" href="source/net/ipv4/tcp_ipv4.c#L824">824</a>                               <a href="ident?i=u16">u16</a> queue_mapping,
<a name="L825" href="source/net/ipv4/tcp_ipv4.c#L825">825</a>                               struct <a href="ident?i=tcp_fastopen_cookie">tcp_fastopen_cookie</a> *foc)
<a name="L826" href="source/net/ipv4/tcp_ipv4.c#L826">826</a> {
<a name="L827" href="source/net/ipv4/tcp_ipv4.c#L827">827</a>         const struct <a href="ident?i=inet_request_sock">inet_request_sock</a> *ireq = <a href="ident?i=inet_rsk">inet_rsk</a>(<a href="ident?i=req">req</a>);
<a name="L828" href="source/net/ipv4/tcp_ipv4.c#L828">828</a>         struct <a href="ident?i=flowi4">flowi4</a> fl4;
<a name="L829" href="source/net/ipv4/tcp_ipv4.c#L829">829</a>         int <a href="ident?i=err">err</a> = -1;
<a name="L830" href="source/net/ipv4/tcp_ipv4.c#L830">830</a>         struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>;
<a name="L831" href="source/net/ipv4/tcp_ipv4.c#L831">831</a> 
<a name="L832" href="source/net/ipv4/tcp_ipv4.c#L832">832</a>         <b><i>/* First, grab a route. */</i></b>
<a name="L833" href="source/net/ipv4/tcp_ipv4.c#L833">833</a>         if (!<a href="ident?i=dst">dst</a> &amp;&amp; (<a href="ident?i=dst">dst</a> = <a href="ident?i=inet_csk_route_req">inet_csk_route_req</a>(sk, &amp;fl4, <a href="ident?i=req">req</a>)) == <a href="ident?i=NULL">NULL</a>)
<a name="L834" href="source/net/ipv4/tcp_ipv4.c#L834">834</a>                 return -1;
<a name="L835" href="source/net/ipv4/tcp_ipv4.c#L835">835</a> 
<a name="L836" href="source/net/ipv4/tcp_ipv4.c#L836">836</a>         <a href="ident?i=skb">skb</a> = <a href="ident?i=tcp_make_synack">tcp_make_synack</a>(sk, <a href="ident?i=dst">dst</a>, <a href="ident?i=req">req</a>, foc);
<a name="L837" href="source/net/ipv4/tcp_ipv4.c#L837">837</a> 
<a name="L838" href="source/net/ipv4/tcp_ipv4.c#L838">838</a>         if (<a href="ident?i=skb">skb</a>) {
<a name="L839" href="source/net/ipv4/tcp_ipv4.c#L839">839</a>                 <a href="ident?i=__tcp_v4_send_check">__tcp_v4_send_check</a>(<a href="ident?i=skb">skb</a>, ireq-&gt;<a href="ident?i=ir_loc_addr">ir_loc_addr</a>, ireq-&gt;<a href="ident?i=ir_rmt_addr">ir_rmt_addr</a>);
<a name="L840" href="source/net/ipv4/tcp_ipv4.c#L840">840</a> 
<a name="L841" href="source/net/ipv4/tcp_ipv4.c#L841">841</a>                 <a href="ident?i=skb_set_queue_mapping">skb_set_queue_mapping</a>(<a href="ident?i=skb">skb</a>, queue_mapping);
<a name="L842" href="source/net/ipv4/tcp_ipv4.c#L842">842</a>                 <a href="ident?i=err">err</a> = <a href="ident?i=ip_build_and_send_pkt">ip_build_and_send_pkt</a>(<a href="ident?i=skb">skb</a>, sk, ireq-&gt;<a href="ident?i=ir_loc_addr">ir_loc_addr</a>,
<a name="L843" href="source/net/ipv4/tcp_ipv4.c#L843">843</a>                                             ireq-&gt;<a href="ident?i=ir_rmt_addr">ir_rmt_addr</a>,
<a name="L844" href="source/net/ipv4/tcp_ipv4.c#L844">844</a>                                             ireq-&gt;opt);
<a name="L845" href="source/net/ipv4/tcp_ipv4.c#L845">845</a>                 <a href="ident?i=err">err</a> = <a href="ident?i=net_xmit_eval">net_xmit_eval</a>(<a href="ident?i=err">err</a>);
<a name="L846" href="source/net/ipv4/tcp_ipv4.c#L846">846</a>         }
<a name="L847" href="source/net/ipv4/tcp_ipv4.c#L847">847</a> 
<a name="L848" href="source/net/ipv4/tcp_ipv4.c#L848">848</a>         return <a href="ident?i=err">err</a>;
<a name="L849" href="source/net/ipv4/tcp_ipv4.c#L849">849</a> }
<a name="L850" href="source/net/ipv4/tcp_ipv4.c#L850">850</a> 
<a name="L851" href="source/net/ipv4/tcp_ipv4.c#L851">851</a> <b><i>/*</i></b>
<a name="L852" href="source/net/ipv4/tcp_ipv4.c#L852">852</a> <b><i> *      IPv4 request_sock destructor.</i></b>
<a name="L853" href="source/net/ipv4/tcp_ipv4.c#L853">853</a> <b><i> */</i></b>
<a name="L854" href="source/net/ipv4/tcp_ipv4.c#L854">854</a> static void <a href="ident?i=tcp_v4_reqsk_destructor">tcp_v4_reqsk_destructor</a>(struct <a href="ident?i=request_sock">request_sock</a> *<a href="ident?i=req">req</a>)
<a name="L855" href="source/net/ipv4/tcp_ipv4.c#L855">855</a> {
<a name="L856" href="source/net/ipv4/tcp_ipv4.c#L856">856</a>         <a href="ident?i=kfree">kfree</a>(<a href="ident?i=inet_rsk">inet_rsk</a>(<a href="ident?i=req">req</a>)-&gt;opt);
<a name="L857" href="source/net/ipv4/tcp_ipv4.c#L857">857</a> }
<a name="L858" href="source/net/ipv4/tcp_ipv4.c#L858">858</a> 
<a name="L859" href="source/net/ipv4/tcp_ipv4.c#L859">859</a> 
<a name="L860" href="source/net/ipv4/tcp_ipv4.c#L860">860</a> #ifdef CONFIG_TCP_MD5SIG
<a name="L861" href="source/net/ipv4/tcp_ipv4.c#L861">861</a> <b><i>/*</i></b>
<a name="L862" href="source/net/ipv4/tcp_ipv4.c#L862">862</a> <b><i> * RFC2385 MD5 checksumming requires a mapping of</i></b>
<a name="L863" href="source/net/ipv4/tcp_ipv4.c#L863">863</a> <b><i> * IP address-&gt;MD5 Key.</i></b>
<a name="L864" href="source/net/ipv4/tcp_ipv4.c#L864">864</a> <b><i> * We need to maintain these in the sk structure.</i></b>
<a name="L865" href="source/net/ipv4/tcp_ipv4.c#L865">865</a> <b><i> */</i></b>
<a name="L866" href="source/net/ipv4/tcp_ipv4.c#L866">866</a> 
<a name="L867" href="source/net/ipv4/tcp_ipv4.c#L867">867</a> <b><i>/* Find the Key structure for an address.  */</i></b>
<a name="L868" href="source/net/ipv4/tcp_ipv4.c#L868">868</a> struct <a href="ident?i=tcp_md5sig_key">tcp_md5sig_key</a> *<a href="ident?i=tcp_md5_do_lookup">tcp_md5_do_lookup</a>(struct <a href="ident?i=sock">sock</a> *sk,
<a name="L869" href="source/net/ipv4/tcp_ipv4.c#L869">869</a>                                          const union <a href="ident?i=tcp_md5_addr">tcp_md5_addr</a> *<a href="ident?i=addr">addr</a>,
<a name="L870" href="source/net/ipv4/tcp_ipv4.c#L870">870</a>                                          int <a href="ident?i=family">family</a>)
<a name="L871" href="source/net/ipv4/tcp_ipv4.c#L871">871</a> {
<a name="L872" href="source/net/ipv4/tcp_ipv4.c#L872">872</a>         const struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L873" href="source/net/ipv4/tcp_ipv4.c#L873">873</a>         struct <a href="ident?i=tcp_md5sig_key">tcp_md5sig_key</a> *<a href="ident?i=key">key</a>;
<a name="L874" href="source/net/ipv4/tcp_ipv4.c#L874">874</a>         unsigned int <a href="ident?i=size">size</a> = sizeof(struct <a href="ident?i=in_addr">in_addr</a>);
<a name="L875" href="source/net/ipv4/tcp_ipv4.c#L875">875</a>         const struct <a href="ident?i=tcp_md5sig_info">tcp_md5sig_info</a> *md5sig;
<a name="L876" href="source/net/ipv4/tcp_ipv4.c#L876">876</a> 
<a name="L877" href="source/net/ipv4/tcp_ipv4.c#L877">877</a>         <b><i>/* caller either holds rcu_read_lock() or socket lock */</i></b>
<a name="L878" href="source/net/ipv4/tcp_ipv4.c#L878">878</a>         md5sig = <a href="ident?i=rcu_dereference_check">rcu_dereference_check</a>(<a href="ident?i=tp">tp</a>-&gt;md5sig_info,
<a name="L879" href="source/net/ipv4/tcp_ipv4.c#L879">879</a>                                        <a href="ident?i=sock_owned_by_user">sock_owned_by_user</a>(sk) ||
<a name="L880" href="source/net/ipv4/tcp_ipv4.c#L880">880</a>                                        <a href="ident?i=lockdep_is_held">lockdep_is_held</a>(&amp;sk-&gt;sk_lock.slock));
<a name="L881" href="source/net/ipv4/tcp_ipv4.c#L881">881</a>         if (!md5sig)
<a name="L882" href="source/net/ipv4/tcp_ipv4.c#L882">882</a>                 return <a href="ident?i=NULL">NULL</a>;
<a name="L883" href="source/net/ipv4/tcp_ipv4.c#L883">883</a> #if <a href="ident?i=IS_ENABLED">IS_ENABLED</a>(CONFIG_IPV6)
<a name="L884" href="source/net/ipv4/tcp_ipv4.c#L884">884</a>         if (<a href="ident?i=family">family</a> == <a href="ident?i=AF_INET6">AF_INET6</a>)
<a name="L885" href="source/net/ipv4/tcp_ipv4.c#L885">885</a>                 <a href="ident?i=size">size</a> = sizeof(struct <a href="ident?i=in6_addr">in6_addr</a>);
<a name="L886" href="source/net/ipv4/tcp_ipv4.c#L886">886</a> #endif
<a name="L887" href="source/net/ipv4/tcp_ipv4.c#L887">887</a>         <a href="ident?i=hlist_for_each_entry_rcu">hlist_for_each_entry_rcu</a>(<a href="ident?i=key">key</a>, &amp;md5sig-&gt;<a href="ident?i=head">head</a>, <a href="ident?i=node">node</a>) {
<a name="L888" href="source/net/ipv4/tcp_ipv4.c#L888">888</a>                 if (<a href="ident?i=key">key</a>-&gt;<a href="ident?i=family">family</a> != <a href="ident?i=family">family</a>)
<a name="L889" href="source/net/ipv4/tcp_ipv4.c#L889">889</a>                         continue;
<a name="L890" href="source/net/ipv4/tcp_ipv4.c#L890">890</a>                 if (!<a href="ident?i=memcmp">memcmp</a>(&amp;<a href="ident?i=key">key</a>-&gt;<a href="ident?i=addr">addr</a>, <a href="ident?i=addr">addr</a>, <a href="ident?i=size">size</a>))
<a name="L891" href="source/net/ipv4/tcp_ipv4.c#L891">891</a>                         return <a href="ident?i=key">key</a>;
<a name="L892" href="source/net/ipv4/tcp_ipv4.c#L892">892</a>         }
<a name="L893" href="source/net/ipv4/tcp_ipv4.c#L893">893</a>         return <a href="ident?i=NULL">NULL</a>;
<a name="L894" href="source/net/ipv4/tcp_ipv4.c#L894">894</a> }
<a name="L895" href="source/net/ipv4/tcp_ipv4.c#L895">895</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=tcp_md5_do_lookup">tcp_md5_do_lookup</a>);
<a name="L896" href="source/net/ipv4/tcp_ipv4.c#L896">896</a> 
<a name="L897" href="source/net/ipv4/tcp_ipv4.c#L897">897</a> struct <a href="ident?i=tcp_md5sig_key">tcp_md5sig_key</a> *<a href="ident?i=tcp_v4_md5_lookup">tcp_v4_md5_lookup</a>(struct <a href="ident?i=sock">sock</a> *sk,
<a name="L898" href="source/net/ipv4/tcp_ipv4.c#L898">898</a>                                          const struct <a href="ident?i=sock">sock</a> *addr_sk)
<a name="L899" href="source/net/ipv4/tcp_ipv4.c#L899">899</a> {
<a name="L900" href="source/net/ipv4/tcp_ipv4.c#L900">900</a>         const union <a href="ident?i=tcp_md5_addr">tcp_md5_addr</a> *<a href="ident?i=addr">addr</a>;
<a name="L901" href="source/net/ipv4/tcp_ipv4.c#L901">901</a> 
<a name="L902" href="source/net/ipv4/tcp_ipv4.c#L902">902</a>         <a href="ident?i=addr">addr</a> = (const union <a href="ident?i=tcp_md5_addr">tcp_md5_addr</a> *)&amp;addr_sk-&gt;<a href="ident?i=sk_daddr">sk_daddr</a>;
<a name="L903" href="source/net/ipv4/tcp_ipv4.c#L903">903</a>         return <a href="ident?i=tcp_md5_do_lookup">tcp_md5_do_lookup</a>(sk, <a href="ident?i=addr">addr</a>, <a href="ident?i=AF_INET">AF_INET</a>);
<a name="L904" href="source/net/ipv4/tcp_ipv4.c#L904">904</a> }
<a name="L905" href="source/net/ipv4/tcp_ipv4.c#L905">905</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=tcp_v4_md5_lookup">tcp_v4_md5_lookup</a>);
<a name="L906" href="source/net/ipv4/tcp_ipv4.c#L906">906</a> 
<a name="L907" href="source/net/ipv4/tcp_ipv4.c#L907">907</a> <b><i>/* This can be called on a newly created socket, from other files */</i></b>
<a name="L908" href="source/net/ipv4/tcp_ipv4.c#L908">908</a> int <a href="ident?i=tcp_md5_do_add">tcp_md5_do_add</a>(struct <a href="ident?i=sock">sock</a> *sk, const union <a href="ident?i=tcp_md5_addr">tcp_md5_addr</a> *<a href="ident?i=addr">addr</a>,
<a name="L909" href="source/net/ipv4/tcp_ipv4.c#L909">909</a>                    int <a href="ident?i=family">family</a>, const <a href="ident?i=u8">u8</a> *newkey, <a href="ident?i=u8">u8</a> newkeylen, <a href="ident?i=gfp_t">gfp_t</a> gfp)
<a name="L910" href="source/net/ipv4/tcp_ipv4.c#L910">910</a> {
<a name="L911" href="source/net/ipv4/tcp_ipv4.c#L911">911</a>         <b><i>/* Add Key to the list */</i></b>
<a name="L912" href="source/net/ipv4/tcp_ipv4.c#L912">912</a>         struct <a href="ident?i=tcp_md5sig_key">tcp_md5sig_key</a> *<a href="ident?i=key">key</a>;
<a name="L913" href="source/net/ipv4/tcp_ipv4.c#L913">913</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L914" href="source/net/ipv4/tcp_ipv4.c#L914">914</a>         struct <a href="ident?i=tcp_md5sig_info">tcp_md5sig_info</a> *md5sig;
<a name="L915" href="source/net/ipv4/tcp_ipv4.c#L915">915</a> 
<a name="L916" href="source/net/ipv4/tcp_ipv4.c#L916">916</a>         <a href="ident?i=key">key</a> = <a href="ident?i=tcp_md5_do_lookup">tcp_md5_do_lookup</a>(sk, <a href="ident?i=addr">addr</a>, <a href="ident?i=family">family</a>);
<a name="L917" href="source/net/ipv4/tcp_ipv4.c#L917">917</a>         if (<a href="ident?i=key">key</a>) {
<a name="L918" href="source/net/ipv4/tcp_ipv4.c#L918">918</a>                 <b><i>/* Pre-existing entry - just update that one. */</i></b>
<a name="L919" href="source/net/ipv4/tcp_ipv4.c#L919">919</a>                 <a href="ident?i=memcpy">memcpy</a>(<a href="ident?i=key">key</a>-&gt;<a href="ident?i=key">key</a>, newkey, newkeylen);
<a name="L920" href="source/net/ipv4/tcp_ipv4.c#L920">920</a>                 <a href="ident?i=key">key</a>-&gt;keylen = newkeylen;
<a name="L921" href="source/net/ipv4/tcp_ipv4.c#L921">921</a>                 return 0;
<a name="L922" href="source/net/ipv4/tcp_ipv4.c#L922">922</a>         }
<a name="L923" href="source/net/ipv4/tcp_ipv4.c#L923">923</a> 
<a name="L924" href="source/net/ipv4/tcp_ipv4.c#L924">924</a>         md5sig = <a href="ident?i=rcu_dereference_protected">rcu_dereference_protected</a>(<a href="ident?i=tp">tp</a>-&gt;md5sig_info,
<a name="L925" href="source/net/ipv4/tcp_ipv4.c#L925">925</a>                                            <a href="ident?i=sock_owned_by_user">sock_owned_by_user</a>(sk));
<a name="L926" href="source/net/ipv4/tcp_ipv4.c#L926">926</a>         if (!md5sig) {
<a name="L927" href="source/net/ipv4/tcp_ipv4.c#L927">927</a>                 md5sig = <a href="ident?i=kmalloc">kmalloc</a>(sizeof(*md5sig), gfp);
<a name="L928" href="source/net/ipv4/tcp_ipv4.c#L928">928</a>                 if (!md5sig)
<a name="L929" href="source/net/ipv4/tcp_ipv4.c#L929">929</a>                         return -<a href="ident?i=ENOMEM">ENOMEM</a>;
<a name="L930" href="source/net/ipv4/tcp_ipv4.c#L930">930</a> 
<a name="L931" href="source/net/ipv4/tcp_ipv4.c#L931">931</a>                 <a href="ident?i=sk_nocaps_add">sk_nocaps_add</a>(sk, <a href="ident?i=NETIF_F_GSO_MASK">NETIF_F_GSO_MASK</a>);
<a name="L932" href="source/net/ipv4/tcp_ipv4.c#L932">932</a>                 <a href="ident?i=INIT_HLIST_HEAD">INIT_HLIST_HEAD</a>(&amp;md5sig-&gt;<a href="ident?i=head">head</a>);
<a name="L933" href="source/net/ipv4/tcp_ipv4.c#L933">933</a>                 <a href="ident?i=rcu_assign_pointer">rcu_assign_pointer</a>(<a href="ident?i=tp">tp</a>-&gt;md5sig_info, md5sig);
<a name="L934" href="source/net/ipv4/tcp_ipv4.c#L934">934</a>         }
<a name="L935" href="source/net/ipv4/tcp_ipv4.c#L935">935</a> 
<a name="L936" href="source/net/ipv4/tcp_ipv4.c#L936">936</a>         <a href="ident?i=key">key</a> = <a href="ident?i=sock_kmalloc">sock_kmalloc</a>(sk, sizeof(*<a href="ident?i=key">key</a>), gfp);
<a name="L937" href="source/net/ipv4/tcp_ipv4.c#L937">937</a>         if (!<a href="ident?i=key">key</a>)
<a name="L938" href="source/net/ipv4/tcp_ipv4.c#L938">938</a>                 return -<a href="ident?i=ENOMEM">ENOMEM</a>;
<a name="L939" href="source/net/ipv4/tcp_ipv4.c#L939">939</a>         if (!<a href="ident?i=tcp_alloc_md5sig_pool">tcp_alloc_md5sig_pool</a>()) {
<a name="L940" href="source/net/ipv4/tcp_ipv4.c#L940">940</a>                 <a href="ident?i=sock_kfree_s">sock_kfree_s</a>(sk, <a href="ident?i=key">key</a>, sizeof(*<a href="ident?i=key">key</a>));
<a name="L941" href="source/net/ipv4/tcp_ipv4.c#L941">941</a>                 return -<a href="ident?i=ENOMEM">ENOMEM</a>;
<a name="L942" href="source/net/ipv4/tcp_ipv4.c#L942">942</a>         }
<a name="L943" href="source/net/ipv4/tcp_ipv4.c#L943">943</a> 
<a name="L944" href="source/net/ipv4/tcp_ipv4.c#L944">944</a>         <a href="ident?i=memcpy">memcpy</a>(<a href="ident?i=key">key</a>-&gt;<a href="ident?i=key">key</a>, newkey, newkeylen);
<a name="L945" href="source/net/ipv4/tcp_ipv4.c#L945">945</a>         <a href="ident?i=key">key</a>-&gt;keylen = newkeylen;
<a name="L946" href="source/net/ipv4/tcp_ipv4.c#L946">946</a>         <a href="ident?i=key">key</a>-&gt;<a href="ident?i=family">family</a> = <a href="ident?i=family">family</a>;
<a name="L947" href="source/net/ipv4/tcp_ipv4.c#L947">947</a>         <a href="ident?i=memcpy">memcpy</a>(&amp;<a href="ident?i=key">key</a>-&gt;<a href="ident?i=addr">addr</a>, <a href="ident?i=addr">addr</a>,
<a name="L948" href="source/net/ipv4/tcp_ipv4.c#L948">948</a>                (<a href="ident?i=family">family</a> == <a href="ident?i=AF_INET6">AF_INET6</a>) ? sizeof(struct <a href="ident?i=in6_addr">in6_addr</a>) :
<a name="L949" href="source/net/ipv4/tcp_ipv4.c#L949">949</a>                                       sizeof(struct <a href="ident?i=in_addr">in_addr</a>));
<a name="L950" href="source/net/ipv4/tcp_ipv4.c#L950">950</a>         <a href="ident?i=hlist_add_head_rcu">hlist_add_head_rcu</a>(&amp;<a href="ident?i=key">key</a>-&gt;<a href="ident?i=node">node</a>, &amp;md5sig-&gt;<a href="ident?i=head">head</a>);
<a name="L951" href="source/net/ipv4/tcp_ipv4.c#L951">951</a>         return 0;
<a name="L952" href="source/net/ipv4/tcp_ipv4.c#L952">952</a> }
<a name="L953" href="source/net/ipv4/tcp_ipv4.c#L953">953</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=tcp_md5_do_add">tcp_md5_do_add</a>);
<a name="L954" href="source/net/ipv4/tcp_ipv4.c#L954">954</a> 
<a name="L955" href="source/net/ipv4/tcp_ipv4.c#L955">955</a> int <a href="ident?i=tcp_md5_do_del">tcp_md5_do_del</a>(struct <a href="ident?i=sock">sock</a> *sk, const union <a href="ident?i=tcp_md5_addr">tcp_md5_addr</a> *<a href="ident?i=addr">addr</a>, int <a href="ident?i=family">family</a>)
<a name="L956" href="source/net/ipv4/tcp_ipv4.c#L956">956</a> {
<a name="L957" href="source/net/ipv4/tcp_ipv4.c#L957">957</a>         struct <a href="ident?i=tcp_md5sig_key">tcp_md5sig_key</a> *<a href="ident?i=key">key</a>;
<a name="L958" href="source/net/ipv4/tcp_ipv4.c#L958">958</a> 
<a name="L959" href="source/net/ipv4/tcp_ipv4.c#L959">959</a>         <a href="ident?i=key">key</a> = <a href="ident?i=tcp_md5_do_lookup">tcp_md5_do_lookup</a>(sk, <a href="ident?i=addr">addr</a>, <a href="ident?i=family">family</a>);
<a name="L960" href="source/net/ipv4/tcp_ipv4.c#L960">960</a>         if (!<a href="ident?i=key">key</a>)
<a name="L961" href="source/net/ipv4/tcp_ipv4.c#L961">961</a>                 return -<a href="ident?i=ENOENT">ENOENT</a>;
<a name="L962" href="source/net/ipv4/tcp_ipv4.c#L962">962</a>         <a href="ident?i=hlist_del_rcu">hlist_del_rcu</a>(&amp;<a href="ident?i=key">key</a>-&gt;<a href="ident?i=node">node</a>);
<a name="L963" href="source/net/ipv4/tcp_ipv4.c#L963">963</a>         <a href="ident?i=atomic_sub">atomic_sub</a>(sizeof(*<a href="ident?i=key">key</a>), &amp;sk-&gt;sk_omem_alloc);
<a name="L964" href="source/net/ipv4/tcp_ipv4.c#L964">964</a>         <a href="ident?i=kfree_rcu">kfree_rcu</a>(<a href="ident?i=key">key</a>, rcu);
<a name="L965" href="source/net/ipv4/tcp_ipv4.c#L965">965</a>         return 0;
<a name="L966" href="source/net/ipv4/tcp_ipv4.c#L966">966</a> }
<a name="L967" href="source/net/ipv4/tcp_ipv4.c#L967">967</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=tcp_md5_do_del">tcp_md5_do_del</a>);
<a name="L968" href="source/net/ipv4/tcp_ipv4.c#L968">968</a> 
<a name="L969" href="source/net/ipv4/tcp_ipv4.c#L969">969</a> static void <a href="ident?i=tcp_clear_md5_list">tcp_clear_md5_list</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L970" href="source/net/ipv4/tcp_ipv4.c#L970">970</a> {
<a name="L971" href="source/net/ipv4/tcp_ipv4.c#L971">971</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L972" href="source/net/ipv4/tcp_ipv4.c#L972">972</a>         struct <a href="ident?i=tcp_md5sig_key">tcp_md5sig_key</a> *<a href="ident?i=key">key</a>;
<a name="L973" href="source/net/ipv4/tcp_ipv4.c#L973">973</a>         struct <a href="ident?i=hlist_node">hlist_node</a> *<a href="ident?i=n">n</a>;
<a name="L974" href="source/net/ipv4/tcp_ipv4.c#L974">974</a>         struct <a href="ident?i=tcp_md5sig_info">tcp_md5sig_info</a> *md5sig;
<a name="L975" href="source/net/ipv4/tcp_ipv4.c#L975">975</a> 
<a name="L976" href="source/net/ipv4/tcp_ipv4.c#L976">976</a>         md5sig = <a href="ident?i=rcu_dereference_protected">rcu_dereference_protected</a>(<a href="ident?i=tp">tp</a>-&gt;md5sig_info, 1);
<a name="L977" href="source/net/ipv4/tcp_ipv4.c#L977">977</a> 
<a name="L978" href="source/net/ipv4/tcp_ipv4.c#L978">978</a>         <a href="ident?i=hlist_for_each_entry_safe">hlist_for_each_entry_safe</a>(<a href="ident?i=key">key</a>, <a href="ident?i=n">n</a>, &amp;md5sig-&gt;<a href="ident?i=head">head</a>, <a href="ident?i=node">node</a>) {
<a name="L979" href="source/net/ipv4/tcp_ipv4.c#L979">979</a>                 <a href="ident?i=hlist_del_rcu">hlist_del_rcu</a>(&amp;<a href="ident?i=key">key</a>-&gt;<a href="ident?i=node">node</a>);
<a name="L980" href="source/net/ipv4/tcp_ipv4.c#L980">980</a>                 <a href="ident?i=atomic_sub">atomic_sub</a>(sizeof(*<a href="ident?i=key">key</a>), &amp;sk-&gt;sk_omem_alloc);
<a name="L981" href="source/net/ipv4/tcp_ipv4.c#L981">981</a>                 <a href="ident?i=kfree_rcu">kfree_rcu</a>(<a href="ident?i=key">key</a>, rcu);
<a name="L982" href="source/net/ipv4/tcp_ipv4.c#L982">982</a>         }
<a name="L983" href="source/net/ipv4/tcp_ipv4.c#L983">983</a> }
<a name="L984" href="source/net/ipv4/tcp_ipv4.c#L984">984</a> 
<a name="L985" href="source/net/ipv4/tcp_ipv4.c#L985">985</a> static int <a href="ident?i=tcp_v4_parse_md5_keys">tcp_v4_parse_md5_keys</a>(struct <a href="ident?i=sock">sock</a> *sk, char <a href="ident?i=__user">__user</a> *optval,
<a name="L986" href="source/net/ipv4/tcp_ipv4.c#L986">986</a>                                  int <a href="ident?i=optlen">optlen</a>)
<a name="L987" href="source/net/ipv4/tcp_ipv4.c#L987">987</a> {
<a name="L988" href="source/net/ipv4/tcp_ipv4.c#L988">988</a>         struct <a href="ident?i=tcp_md5sig">tcp_md5sig</a> <a href="ident?i=cmd">cmd</a>;
<a name="L989" href="source/net/ipv4/tcp_ipv4.c#L989">989</a>         struct <a href="ident?i=sockaddr_in">sockaddr_in</a> *<a href="ident?i=sin">sin</a> = (struct <a href="ident?i=sockaddr_in">sockaddr_in</a> *)&amp;<a href="ident?i=cmd">cmd</a>.tcpm_addr;
<a name="L990" href="source/net/ipv4/tcp_ipv4.c#L990">990</a> 
<a name="L991" href="source/net/ipv4/tcp_ipv4.c#L991">991</a>         if (<a href="ident?i=optlen">optlen</a> &lt; sizeof(<a href="ident?i=cmd">cmd</a>))
<a name="L992" href="source/net/ipv4/tcp_ipv4.c#L992">992</a>                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L993" href="source/net/ipv4/tcp_ipv4.c#L993">993</a> 
<a name="L994" href="source/net/ipv4/tcp_ipv4.c#L994">994</a>         if (<a href="ident?i=copy_from_user">copy_from_user</a>(&amp;<a href="ident?i=cmd">cmd</a>, optval, sizeof(<a href="ident?i=cmd">cmd</a>)))
<a name="L995" href="source/net/ipv4/tcp_ipv4.c#L995">995</a>                 return -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L996" href="source/net/ipv4/tcp_ipv4.c#L996">996</a> 
<a name="L997" href="source/net/ipv4/tcp_ipv4.c#L997">997</a>         if (<a href="ident?i=sin">sin</a>-&gt;sin_family != <a href="ident?i=AF_INET">AF_INET</a>)
<a name="L998" href="source/net/ipv4/tcp_ipv4.c#L998">998</a>                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L999" href="source/net/ipv4/tcp_ipv4.c#L999">999</a> 
<a name="L1000" href="source/net/ipv4/tcp_ipv4.c#L1000">1000</a>         if (!<a href="ident?i=cmd">cmd</a>.tcpm_keylen)
<a name="L1001" href="source/net/ipv4/tcp_ipv4.c#L1001">1001</a>                 return <a href="ident?i=tcp_md5_do_del">tcp_md5_do_del</a>(sk, (union <a href="ident?i=tcp_md5_addr">tcp_md5_addr</a> *)&amp;<a href="ident?i=sin">sin</a>-&gt;sin_addr.s_addr,
<a name="L1002" href="source/net/ipv4/tcp_ipv4.c#L1002">1002</a>                                       <a href="ident?i=AF_INET">AF_INET</a>);
<a name="L1003" href="source/net/ipv4/tcp_ipv4.c#L1003">1003</a> 
<a name="L1004" href="source/net/ipv4/tcp_ipv4.c#L1004">1004</a>         if (<a href="ident?i=cmd">cmd</a>.tcpm_keylen &gt; <a href="ident?i=TCP_MD5SIG_MAXKEYLEN">TCP_MD5SIG_MAXKEYLEN</a>)
<a name="L1005" href="source/net/ipv4/tcp_ipv4.c#L1005">1005</a>                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L1006" href="source/net/ipv4/tcp_ipv4.c#L1006">1006</a> 
<a name="L1007" href="source/net/ipv4/tcp_ipv4.c#L1007">1007</a>         return <a href="ident?i=tcp_md5_do_add">tcp_md5_do_add</a>(sk, (union <a href="ident?i=tcp_md5_addr">tcp_md5_addr</a> *)&amp;<a href="ident?i=sin">sin</a>-&gt;sin_addr.s_addr,
<a name="L1008" href="source/net/ipv4/tcp_ipv4.c#L1008">1008</a>                               <a href="ident?i=AF_INET">AF_INET</a>, <a href="ident?i=cmd">cmd</a>.tcpm_key, <a href="ident?i=cmd">cmd</a>.tcpm_keylen,
<a name="L1009" href="source/net/ipv4/tcp_ipv4.c#L1009">1009</a>                               <a href="ident?i=GFP_KERNEL">GFP_KERNEL</a>);
<a name="L1010" href="source/net/ipv4/tcp_ipv4.c#L1010">1010</a> }
<a name="L1011" href="source/net/ipv4/tcp_ipv4.c#L1011">1011</a> 
<a name="L1012" href="source/net/ipv4/tcp_ipv4.c#L1012">1012</a> static int <a href="ident?i=tcp_v4_md5_hash_pseudoheader">tcp_v4_md5_hash_pseudoheader</a>(struct <a href="ident?i=tcp_md5sig_pool">tcp_md5sig_pool</a> *hp,
<a name="L1013" href="source/net/ipv4/tcp_ipv4.c#L1013">1013</a>                                         <a href="ident?i=__be32">__be32</a> <a href="ident?i=daddr">daddr</a>, <a href="ident?i=__be32">__be32</a> <a href="ident?i=saddr">saddr</a>, int nbytes)
<a name="L1014" href="source/net/ipv4/tcp_ipv4.c#L1014">1014</a> {
<a name="L1015" href="source/net/ipv4/tcp_ipv4.c#L1015">1015</a>         struct <a href="ident?i=tcp4_pseudohdr">tcp4_pseudohdr</a> *bp;
<a name="L1016" href="source/net/ipv4/tcp_ipv4.c#L1016">1016</a>         struct <a href="ident?i=scatterlist">scatterlist</a> sg;
<a name="L1017" href="source/net/ipv4/tcp_ipv4.c#L1017">1017</a> 
<a name="L1018" href="source/net/ipv4/tcp_ipv4.c#L1018">1018</a>         bp = &amp;hp-&gt;md5_blk.ip4;
<a name="L1019" href="source/net/ipv4/tcp_ipv4.c#L1019">1019</a> 
<a name="L1020" href="source/net/ipv4/tcp_ipv4.c#L1020">1020</a>         <b><i>/*</i></b>
<a name="L1021" href="source/net/ipv4/tcp_ipv4.c#L1021">1021</a> <b><i>         * 1. the TCP pseudo-header (in the order: source IP address,</i></b>
<a name="L1022" href="source/net/ipv4/tcp_ipv4.c#L1022">1022</a> <b><i>         * destination IP address, zero-padded protocol number, and</i></b>
<a name="L1023" href="source/net/ipv4/tcp_ipv4.c#L1023">1023</a> <b><i>         * segment length)</i></b>
<a name="L1024" href="source/net/ipv4/tcp_ipv4.c#L1024">1024</a> <b><i>         */</i></b>
<a name="L1025" href="source/net/ipv4/tcp_ipv4.c#L1025">1025</a>         bp-&gt;<a href="ident?i=saddr">saddr</a> = <a href="ident?i=saddr">saddr</a>;
<a name="L1026" href="source/net/ipv4/tcp_ipv4.c#L1026">1026</a>         bp-&gt;<a href="ident?i=daddr">daddr</a> = <a href="ident?i=daddr">daddr</a>;
<a name="L1027" href="source/net/ipv4/tcp_ipv4.c#L1027">1027</a>         bp-&gt;<a href="ident?i=pad">pad</a> = 0;
<a name="L1028" href="source/net/ipv4/tcp_ipv4.c#L1028">1028</a>         bp-&gt;<a href="ident?i=protocol">protocol</a> = <a href="ident?i=IPPROTO_TCP">IPPROTO_TCP</a>;
<a name="L1029" href="source/net/ipv4/tcp_ipv4.c#L1029">1029</a>         bp-&gt;<a href="ident?i=len">len</a> = <a href="ident?i=cpu_to_be16">cpu_to_be16</a>(nbytes);
<a name="L1030" href="source/net/ipv4/tcp_ipv4.c#L1030">1030</a> 
<a name="L1031" href="source/net/ipv4/tcp_ipv4.c#L1031">1031</a>         <a href="ident?i=sg_init_one">sg_init_one</a>(&amp;sg, bp, sizeof(*bp));
<a name="L1032" href="source/net/ipv4/tcp_ipv4.c#L1032">1032</a>         return <a href="ident?i=crypto_hash_update">crypto_hash_update</a>(&amp;hp-&gt;md5_desc, &amp;sg, sizeof(*bp));
<a name="L1033" href="source/net/ipv4/tcp_ipv4.c#L1033">1033</a> }
<a name="L1034" href="source/net/ipv4/tcp_ipv4.c#L1034">1034</a> 
<a name="L1035" href="source/net/ipv4/tcp_ipv4.c#L1035">1035</a> static int <a href="ident?i=tcp_v4_md5_hash_hdr">tcp_v4_md5_hash_hdr</a>(char *md5_hash, const struct <a href="ident?i=tcp_md5sig_key">tcp_md5sig_key</a> *<a href="ident?i=key">key</a>,
<a name="L1036" href="source/net/ipv4/tcp_ipv4.c#L1036">1036</a>                                <a href="ident?i=__be32">__be32</a> <a href="ident?i=daddr">daddr</a>, <a href="ident?i=__be32">__be32</a> <a href="ident?i=saddr">saddr</a>, const struct <a href="ident?i=tcphdr">tcphdr</a> *<a href="ident?i=th">th</a>)
<a name="L1037" href="source/net/ipv4/tcp_ipv4.c#L1037">1037</a> {
<a name="L1038" href="source/net/ipv4/tcp_ipv4.c#L1038">1038</a>         struct <a href="ident?i=tcp_md5sig_pool">tcp_md5sig_pool</a> *hp;
<a name="L1039" href="source/net/ipv4/tcp_ipv4.c#L1039">1039</a>         struct <a href="ident?i=hash_desc">hash_desc</a> *<a href="ident?i=desc">desc</a>;
<a name="L1040" href="source/net/ipv4/tcp_ipv4.c#L1040">1040</a> 
<a name="L1041" href="source/net/ipv4/tcp_ipv4.c#L1041">1041</a>         hp = <a href="ident?i=tcp_get_md5sig_pool">tcp_get_md5sig_pool</a>();
<a name="L1042" href="source/net/ipv4/tcp_ipv4.c#L1042">1042</a>         if (!hp)
<a name="L1043" href="source/net/ipv4/tcp_ipv4.c#L1043">1043</a>                 goto clear_hash_noput;
<a name="L1044" href="source/net/ipv4/tcp_ipv4.c#L1044">1044</a>         <a href="ident?i=desc">desc</a> = &amp;hp-&gt;md5_desc;
<a name="L1045" href="source/net/ipv4/tcp_ipv4.c#L1045">1045</a> 
<a name="L1046" href="source/net/ipv4/tcp_ipv4.c#L1046">1046</a>         if (<a href="ident?i=crypto_hash_init">crypto_hash_init</a>(<a href="ident?i=desc">desc</a>))
<a name="L1047" href="source/net/ipv4/tcp_ipv4.c#L1047">1047</a>                 goto clear_hash;
<a name="L1048" href="source/net/ipv4/tcp_ipv4.c#L1048">1048</a>         if (<a href="ident?i=tcp_v4_md5_hash_pseudoheader">tcp_v4_md5_hash_pseudoheader</a>(hp, <a href="ident?i=daddr">daddr</a>, <a href="ident?i=saddr">saddr</a>, <a href="ident?i=th">th</a>-&gt;doff &lt;&lt; 2))
<a name="L1049" href="source/net/ipv4/tcp_ipv4.c#L1049">1049</a>                 goto clear_hash;
<a name="L1050" href="source/net/ipv4/tcp_ipv4.c#L1050">1050</a>         if (<a href="ident?i=tcp_md5_hash_header">tcp_md5_hash_header</a>(hp, <a href="ident?i=th">th</a>))
<a name="L1051" href="source/net/ipv4/tcp_ipv4.c#L1051">1051</a>                 goto clear_hash;
<a name="L1052" href="source/net/ipv4/tcp_ipv4.c#L1052">1052</a>         if (<a href="ident?i=tcp_md5_hash_key">tcp_md5_hash_key</a>(hp, <a href="ident?i=key">key</a>))
<a name="L1053" href="source/net/ipv4/tcp_ipv4.c#L1053">1053</a>                 goto clear_hash;
<a name="L1054" href="source/net/ipv4/tcp_ipv4.c#L1054">1054</a>         if (<a href="ident?i=crypto_hash_final">crypto_hash_final</a>(<a href="ident?i=desc">desc</a>, md5_hash))
<a name="L1055" href="source/net/ipv4/tcp_ipv4.c#L1055">1055</a>                 goto clear_hash;
<a name="L1056" href="source/net/ipv4/tcp_ipv4.c#L1056">1056</a> 
<a name="L1057" href="source/net/ipv4/tcp_ipv4.c#L1057">1057</a>         <a href="ident?i=tcp_put_md5sig_pool">tcp_put_md5sig_pool</a>();
<a name="L1058" href="source/net/ipv4/tcp_ipv4.c#L1058">1058</a>         return 0;
<a name="L1059" href="source/net/ipv4/tcp_ipv4.c#L1059">1059</a> 
<a name="L1060" href="source/net/ipv4/tcp_ipv4.c#L1060">1060</a> clear_hash:
<a name="L1061" href="source/net/ipv4/tcp_ipv4.c#L1061">1061</a>         <a href="ident?i=tcp_put_md5sig_pool">tcp_put_md5sig_pool</a>();
<a name="L1062" href="source/net/ipv4/tcp_ipv4.c#L1062">1062</a> clear_hash_noput:
<a name="L1063" href="source/net/ipv4/tcp_ipv4.c#L1063">1063</a>         <a href="ident?i=memset">memset</a>(md5_hash, 0, 16);
<a name="L1064" href="source/net/ipv4/tcp_ipv4.c#L1064">1064</a>         return 1;
<a name="L1065" href="source/net/ipv4/tcp_ipv4.c#L1065">1065</a> }
<a name="L1066" href="source/net/ipv4/tcp_ipv4.c#L1066">1066</a> 
<a name="L1067" href="source/net/ipv4/tcp_ipv4.c#L1067">1067</a> int <a href="ident?i=tcp_v4_md5_hash_skb">tcp_v4_md5_hash_skb</a>(char *md5_hash, const struct <a href="ident?i=tcp_md5sig_key">tcp_md5sig_key</a> *<a href="ident?i=key">key</a>,
<a name="L1068" href="source/net/ipv4/tcp_ipv4.c#L1068">1068</a>                         const struct <a href="ident?i=sock">sock</a> *sk,
<a name="L1069" href="source/net/ipv4/tcp_ipv4.c#L1069">1069</a>                         const struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L1070" href="source/net/ipv4/tcp_ipv4.c#L1070">1070</a> {
<a name="L1071" href="source/net/ipv4/tcp_ipv4.c#L1071">1071</a>         struct <a href="ident?i=tcp_md5sig_pool">tcp_md5sig_pool</a> *hp;
<a name="L1072" href="source/net/ipv4/tcp_ipv4.c#L1072">1072</a>         struct <a href="ident?i=hash_desc">hash_desc</a> *<a href="ident?i=desc">desc</a>;
<a name="L1073" href="source/net/ipv4/tcp_ipv4.c#L1073">1073</a>         const struct <a href="ident?i=tcphdr">tcphdr</a> *<a href="ident?i=th">th</a> = <a href="ident?i=tcp_hdr">tcp_hdr</a>(<a href="ident?i=skb">skb</a>);
<a name="L1074" href="source/net/ipv4/tcp_ipv4.c#L1074">1074</a>         <a href="ident?i=__be32">__be32</a> <a href="ident?i=saddr">saddr</a>, <a href="ident?i=daddr">daddr</a>;
<a name="L1075" href="source/net/ipv4/tcp_ipv4.c#L1075">1075</a> 
<a name="L1076" href="source/net/ipv4/tcp_ipv4.c#L1076">1076</a>         if (sk) { <b><i>/* valid for establish/request sockets */</i></b>
<a name="L1077" href="source/net/ipv4/tcp_ipv4.c#L1077">1077</a>                 <a href="ident?i=saddr">saddr</a> = sk-&gt;<a href="ident?i=sk_rcv_saddr">sk_rcv_saddr</a>;
<a name="L1078" href="source/net/ipv4/tcp_ipv4.c#L1078">1078</a>                 <a href="ident?i=daddr">daddr</a> = sk-&gt;<a href="ident?i=sk_daddr">sk_daddr</a>;
<a name="L1079" href="source/net/ipv4/tcp_ipv4.c#L1079">1079</a>         } else {
<a name="L1080" href="source/net/ipv4/tcp_ipv4.c#L1080">1080</a>                 const struct <a href="ident?i=iphdr">iphdr</a> *iph = <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>);
<a name="L1081" href="source/net/ipv4/tcp_ipv4.c#L1081">1081</a>                 <a href="ident?i=saddr">saddr</a> = iph-&gt;<a href="ident?i=saddr">saddr</a>;
<a name="L1082" href="source/net/ipv4/tcp_ipv4.c#L1082">1082</a>                 <a href="ident?i=daddr">daddr</a> = iph-&gt;<a href="ident?i=daddr">daddr</a>;
<a name="L1083" href="source/net/ipv4/tcp_ipv4.c#L1083">1083</a>         }
<a name="L1084" href="source/net/ipv4/tcp_ipv4.c#L1084">1084</a> 
<a name="L1085" href="source/net/ipv4/tcp_ipv4.c#L1085">1085</a>         hp = <a href="ident?i=tcp_get_md5sig_pool">tcp_get_md5sig_pool</a>();
<a name="L1086" href="source/net/ipv4/tcp_ipv4.c#L1086">1086</a>         if (!hp)
<a name="L1087" href="source/net/ipv4/tcp_ipv4.c#L1087">1087</a>                 goto clear_hash_noput;
<a name="L1088" href="source/net/ipv4/tcp_ipv4.c#L1088">1088</a>         <a href="ident?i=desc">desc</a> = &amp;hp-&gt;md5_desc;
<a name="L1089" href="source/net/ipv4/tcp_ipv4.c#L1089">1089</a> 
<a name="L1090" href="source/net/ipv4/tcp_ipv4.c#L1090">1090</a>         if (<a href="ident?i=crypto_hash_init">crypto_hash_init</a>(<a href="ident?i=desc">desc</a>))
<a name="L1091" href="source/net/ipv4/tcp_ipv4.c#L1091">1091</a>                 goto clear_hash;
<a name="L1092" href="source/net/ipv4/tcp_ipv4.c#L1092">1092</a> 
<a name="L1093" href="source/net/ipv4/tcp_ipv4.c#L1093">1093</a>         if (<a href="ident?i=tcp_v4_md5_hash_pseudoheader">tcp_v4_md5_hash_pseudoheader</a>(hp, <a href="ident?i=daddr">daddr</a>, <a href="ident?i=saddr">saddr</a>, <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a>))
<a name="L1094" href="source/net/ipv4/tcp_ipv4.c#L1094">1094</a>                 goto clear_hash;
<a name="L1095" href="source/net/ipv4/tcp_ipv4.c#L1095">1095</a>         if (<a href="ident?i=tcp_md5_hash_header">tcp_md5_hash_header</a>(hp, <a href="ident?i=th">th</a>))
<a name="L1096" href="source/net/ipv4/tcp_ipv4.c#L1096">1096</a>                 goto clear_hash;
<a name="L1097" href="source/net/ipv4/tcp_ipv4.c#L1097">1097</a>         if (<a href="ident?i=tcp_md5_hash_skb_data">tcp_md5_hash_skb_data</a>(hp, <a href="ident?i=skb">skb</a>, <a href="ident?i=th">th</a>-&gt;doff &lt;&lt; 2))
<a name="L1098" href="source/net/ipv4/tcp_ipv4.c#L1098">1098</a>                 goto clear_hash;
<a name="L1099" href="source/net/ipv4/tcp_ipv4.c#L1099">1099</a>         if (<a href="ident?i=tcp_md5_hash_key">tcp_md5_hash_key</a>(hp, <a href="ident?i=key">key</a>))
<a name="L1100" href="source/net/ipv4/tcp_ipv4.c#L1100">1100</a>                 goto clear_hash;
<a name="L1101" href="source/net/ipv4/tcp_ipv4.c#L1101">1101</a>         if (<a href="ident?i=crypto_hash_final">crypto_hash_final</a>(<a href="ident?i=desc">desc</a>, md5_hash))
<a name="L1102" href="source/net/ipv4/tcp_ipv4.c#L1102">1102</a>                 goto clear_hash;
<a name="L1103" href="source/net/ipv4/tcp_ipv4.c#L1103">1103</a> 
<a name="L1104" href="source/net/ipv4/tcp_ipv4.c#L1104">1104</a>         <a href="ident?i=tcp_put_md5sig_pool">tcp_put_md5sig_pool</a>();
<a name="L1105" href="source/net/ipv4/tcp_ipv4.c#L1105">1105</a>         return 0;
<a name="L1106" href="source/net/ipv4/tcp_ipv4.c#L1106">1106</a> 
<a name="L1107" href="source/net/ipv4/tcp_ipv4.c#L1107">1107</a> clear_hash:
<a name="L1108" href="source/net/ipv4/tcp_ipv4.c#L1108">1108</a>         <a href="ident?i=tcp_put_md5sig_pool">tcp_put_md5sig_pool</a>();
<a name="L1109" href="source/net/ipv4/tcp_ipv4.c#L1109">1109</a> clear_hash_noput:
<a name="L1110" href="source/net/ipv4/tcp_ipv4.c#L1110">1110</a>         <a href="ident?i=memset">memset</a>(md5_hash, 0, 16);
<a name="L1111" href="source/net/ipv4/tcp_ipv4.c#L1111">1111</a>         return 1;
<a name="L1112" href="source/net/ipv4/tcp_ipv4.c#L1112">1112</a> }
<a name="L1113" href="source/net/ipv4/tcp_ipv4.c#L1113">1113</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=tcp_v4_md5_hash_skb">tcp_v4_md5_hash_skb</a>);
<a name="L1114" href="source/net/ipv4/tcp_ipv4.c#L1114">1114</a> 
<a name="L1115" href="source/net/ipv4/tcp_ipv4.c#L1115">1115</a> <b><i>/* Called with rcu_read_lock() */</i></b>
<a name="L1116" href="source/net/ipv4/tcp_ipv4.c#L1116">1116</a> static <a href="ident?i=bool">bool</a> <a href="ident?i=tcp_v4_inbound_md5_hash">tcp_v4_inbound_md5_hash</a>(struct <a href="ident?i=sock">sock</a> *sk,
<a name="L1117" href="source/net/ipv4/tcp_ipv4.c#L1117">1117</a>                                     const struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L1118" href="source/net/ipv4/tcp_ipv4.c#L1118">1118</a> {
<a name="L1119" href="source/net/ipv4/tcp_ipv4.c#L1119">1119</a>         <b><i>/*</i></b>
<a name="L1120" href="source/net/ipv4/tcp_ipv4.c#L1120">1120</a> <b><i>         * This gets called for each TCP segment that arrives</i></b>
<a name="L1121" href="source/net/ipv4/tcp_ipv4.c#L1121">1121</a> <b><i>         * so we want to be efficient.</i></b>
<a name="L1122" href="source/net/ipv4/tcp_ipv4.c#L1122">1122</a> <b><i>         * We have 3 drop cases:</i></b>
<a name="L1123" href="source/net/ipv4/tcp_ipv4.c#L1123">1123</a> <b><i>         * o No MD5 hash and one expected.</i></b>
<a name="L1124" href="source/net/ipv4/tcp_ipv4.c#L1124">1124</a> <b><i>         * o MD5 hash and we're not expecting one.</i></b>
<a name="L1125" href="source/net/ipv4/tcp_ipv4.c#L1125">1125</a> <b><i>         * o MD5 hash and its wrong.</i></b>
<a name="L1126" href="source/net/ipv4/tcp_ipv4.c#L1126">1126</a> <b><i>         */</i></b>
<a name="L1127" href="source/net/ipv4/tcp_ipv4.c#L1127">1127</a>         const <a href="ident?i=__u8">__u8</a> *hash_location = <a href="ident?i=NULL">NULL</a>;
<a name="L1128" href="source/net/ipv4/tcp_ipv4.c#L1128">1128</a>         struct <a href="ident?i=tcp_md5sig_key">tcp_md5sig_key</a> *hash_expected;
<a name="L1129" href="source/net/ipv4/tcp_ipv4.c#L1129">1129</a>         const struct <a href="ident?i=iphdr">iphdr</a> *iph = <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>);
<a name="L1130" href="source/net/ipv4/tcp_ipv4.c#L1130">1130</a>         const struct <a href="ident?i=tcphdr">tcphdr</a> *<a href="ident?i=th">th</a> = <a href="ident?i=tcp_hdr">tcp_hdr</a>(<a href="ident?i=skb">skb</a>);
<a name="L1131" href="source/net/ipv4/tcp_ipv4.c#L1131">1131</a>         int genhash;
<a name="L1132" href="source/net/ipv4/tcp_ipv4.c#L1132">1132</a>         unsigned char newhash[16];
<a name="L1133" href="source/net/ipv4/tcp_ipv4.c#L1133">1133</a> 
<a name="L1134" href="source/net/ipv4/tcp_ipv4.c#L1134">1134</a>         hash_expected = <a href="ident?i=tcp_md5_do_lookup">tcp_md5_do_lookup</a>(sk, (union <a href="ident?i=tcp_md5_addr">tcp_md5_addr</a> *)&amp;iph-&gt;<a href="ident?i=saddr">saddr</a>,
<a name="L1135" href="source/net/ipv4/tcp_ipv4.c#L1135">1135</a>                                           <a href="ident?i=AF_INET">AF_INET</a>);
<a name="L1136" href="source/net/ipv4/tcp_ipv4.c#L1136">1136</a>         hash_location = <a href="ident?i=tcp_parse_md5sig_option">tcp_parse_md5sig_option</a>(<a href="ident?i=th">th</a>);
<a name="L1137" href="source/net/ipv4/tcp_ipv4.c#L1137">1137</a> 
<a name="L1138" href="source/net/ipv4/tcp_ipv4.c#L1138">1138</a>         <b><i>/* We've parsed the options - do we have a hash? */</i></b>
<a name="L1139" href="source/net/ipv4/tcp_ipv4.c#L1139">1139</a>         if (!hash_expected &amp;&amp; !hash_location)
<a name="L1140" href="source/net/ipv4/tcp_ipv4.c#L1140">1140</a>                 return <a href="ident?i=false">false</a>;
<a name="L1141" href="source/net/ipv4/tcp_ipv4.c#L1141">1141</a> 
<a name="L1142" href="source/net/ipv4/tcp_ipv4.c#L1142">1142</a>         if (hash_expected &amp;&amp; !hash_location) {
<a name="L1143" href="source/net/ipv4/tcp_ipv4.c#L1143">1143</a>                 <a href="ident?i=NET_INC_STATS_BH">NET_INC_STATS_BH</a>(<a href="ident?i=sock_net">sock_net</a>(sk), LINUX_MIB_TCPMD5NOTFOUND);
<a name="L1144" href="source/net/ipv4/tcp_ipv4.c#L1144">1144</a>                 return <a href="ident?i=true">true</a>;
<a name="L1145" href="source/net/ipv4/tcp_ipv4.c#L1145">1145</a>         }
<a name="L1146" href="source/net/ipv4/tcp_ipv4.c#L1146">1146</a> 
<a name="L1147" href="source/net/ipv4/tcp_ipv4.c#L1147">1147</a>         if (!hash_expected &amp;&amp; hash_location) {
<a name="L1148" href="source/net/ipv4/tcp_ipv4.c#L1148">1148</a>                 <a href="ident?i=NET_INC_STATS_BH">NET_INC_STATS_BH</a>(<a href="ident?i=sock_net">sock_net</a>(sk), LINUX_MIB_TCPMD5UNEXPECTED);
<a name="L1149" href="source/net/ipv4/tcp_ipv4.c#L1149">1149</a>                 return <a href="ident?i=true">true</a>;
<a name="L1150" href="source/net/ipv4/tcp_ipv4.c#L1150">1150</a>         }
<a name="L1151" href="source/net/ipv4/tcp_ipv4.c#L1151">1151</a> 
<a name="L1152" href="source/net/ipv4/tcp_ipv4.c#L1152">1152</a>         <b><i>/* Okay, so this is hash_expected and hash_location -</i></b>
<a name="L1153" href="source/net/ipv4/tcp_ipv4.c#L1153">1153</a> <b><i>         * so we need to calculate the checksum.</i></b>
<a name="L1154" href="source/net/ipv4/tcp_ipv4.c#L1154">1154</a> <b><i>         */</i></b>
<a name="L1155" href="source/net/ipv4/tcp_ipv4.c#L1155">1155</a>         genhash = <a href="ident?i=tcp_v4_md5_hash_skb">tcp_v4_md5_hash_skb</a>(newhash,
<a name="L1156" href="source/net/ipv4/tcp_ipv4.c#L1156">1156</a>                                       hash_expected,
<a name="L1157" href="source/net/ipv4/tcp_ipv4.c#L1157">1157</a>                                       <a href="ident?i=NULL">NULL</a>, <a href="ident?i=skb">skb</a>);
<a name="L1158" href="source/net/ipv4/tcp_ipv4.c#L1158">1158</a> 
<a name="L1159" href="source/net/ipv4/tcp_ipv4.c#L1159">1159</a>         if (genhash || <a href="ident?i=memcmp">memcmp</a>(hash_location, newhash, 16) != 0) {
<a name="L1160" href="source/net/ipv4/tcp_ipv4.c#L1160">1160</a>                 <a href="ident?i=net_info_ratelimited">net_info_ratelimited</a>(<i>"MD5 Hash failed for (%pI4, %d)-&gt;(%pI4, %d)%s\n"</i>,
<a name="L1161" href="source/net/ipv4/tcp_ipv4.c#L1161">1161</a>                                      &amp;iph-&gt;<a href="ident?i=saddr">saddr</a>, <a href="ident?i=ntohs">ntohs</a>(<a href="ident?i=th">th</a>-&gt;source),
<a name="L1162" href="source/net/ipv4/tcp_ipv4.c#L1162">1162</a>                                      &amp;iph-&gt;<a href="ident?i=daddr">daddr</a>, <a href="ident?i=ntohs">ntohs</a>(<a href="ident?i=th">th</a>-&gt;<a href="ident?i=dest">dest</a>),
<a name="L1163" href="source/net/ipv4/tcp_ipv4.c#L1163">1163</a>                                      genhash ? <i>" tcp_v4_calc_md5_hash failed"</i>
<a name="L1164" href="source/net/ipv4/tcp_ipv4.c#L1164">1164</a>                                      : <i>""</i>);
<a name="L1165" href="source/net/ipv4/tcp_ipv4.c#L1165">1165</a>                 return <a href="ident?i=true">true</a>;
<a name="L1166" href="source/net/ipv4/tcp_ipv4.c#L1166">1166</a>         }
<a name="L1167" href="source/net/ipv4/tcp_ipv4.c#L1167">1167</a>         return <a href="ident?i=false">false</a>;
<a name="L1168" href="source/net/ipv4/tcp_ipv4.c#L1168">1168</a> }
<a name="L1169" href="source/net/ipv4/tcp_ipv4.c#L1169">1169</a> #endif
<a name="L1170" href="source/net/ipv4/tcp_ipv4.c#L1170">1170</a> 
<a name="L1171" href="source/net/ipv4/tcp_ipv4.c#L1171">1171</a> static void <a href="ident?i=tcp_v4_init_req">tcp_v4_init_req</a>(struct <a href="ident?i=request_sock">request_sock</a> *<a href="ident?i=req">req</a>, struct <a href="ident?i=sock">sock</a> *sk_listener,
<a name="L1172" href="source/net/ipv4/tcp_ipv4.c#L1172">1172</a>                             struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L1173" href="source/net/ipv4/tcp_ipv4.c#L1173">1173</a> {
<a name="L1174" href="source/net/ipv4/tcp_ipv4.c#L1174">1174</a>         struct <a href="ident?i=inet_request_sock">inet_request_sock</a> *ireq = <a href="ident?i=inet_rsk">inet_rsk</a>(<a href="ident?i=req">req</a>);
<a name="L1175" href="source/net/ipv4/tcp_ipv4.c#L1175">1175</a> 
<a name="L1176" href="source/net/ipv4/tcp_ipv4.c#L1176">1176</a>         <a href="ident?i=sk_rcv_saddr_set">sk_rcv_saddr_set</a>(<a href="ident?i=req_to_sk">req_to_sk</a>(<a href="ident?i=req">req</a>), <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=daddr">daddr</a>);
<a name="L1177" href="source/net/ipv4/tcp_ipv4.c#L1177">1177</a>         <a href="ident?i=sk_daddr_set">sk_daddr_set</a>(<a href="ident?i=req_to_sk">req_to_sk</a>(<a href="ident?i=req">req</a>), <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=saddr">saddr</a>);
<a name="L1178" href="source/net/ipv4/tcp_ipv4.c#L1178">1178</a>         ireq-&gt;no_srccheck = <a href="ident?i=inet_sk">inet_sk</a>(sk_listener)-&gt;transparent;
<a name="L1179" href="source/net/ipv4/tcp_ipv4.c#L1179">1179</a>         ireq-&gt;opt = <a href="ident?i=tcp_v4_save_options">tcp_v4_save_options</a>(<a href="ident?i=skb">skb</a>);
<a name="L1180" href="source/net/ipv4/tcp_ipv4.c#L1180">1180</a> }
<a name="L1181" href="source/net/ipv4/tcp_ipv4.c#L1181">1181</a> 
<a name="L1182" href="source/net/ipv4/tcp_ipv4.c#L1182">1182</a> static struct <a href="ident?i=dst_entry">dst_entry</a> *<a href="ident?i=tcp_v4_route_req">tcp_v4_route_req</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=flowi">flowi</a> *fl,
<a name="L1183" href="source/net/ipv4/tcp_ipv4.c#L1183">1183</a>                                           const struct <a href="ident?i=request_sock">request_sock</a> *<a href="ident?i=req">req</a>,
<a name="L1184" href="source/net/ipv4/tcp_ipv4.c#L1184">1184</a>                                           <a href="ident?i=bool">bool</a> *strict)
<a name="L1185" href="source/net/ipv4/tcp_ipv4.c#L1185">1185</a> {
<a name="L1186" href="source/net/ipv4/tcp_ipv4.c#L1186">1186</a>         struct <a href="ident?i=dst_entry">dst_entry</a> *<a href="ident?i=dst">dst</a> = <a href="ident?i=inet_csk_route_req">inet_csk_route_req</a>(sk, &amp;fl-&gt;u.ip4, <a href="ident?i=req">req</a>);
<a name="L1187" href="source/net/ipv4/tcp_ipv4.c#L1187">1187</a> 
<a name="L1188" href="source/net/ipv4/tcp_ipv4.c#L1188">1188</a>         if (strict) {
<a name="L1189" href="source/net/ipv4/tcp_ipv4.c#L1189">1189</a>                 if (fl-&gt;u.ip4.<a href="ident?i=daddr">daddr</a> == <a href="ident?i=inet_rsk">inet_rsk</a>(<a href="ident?i=req">req</a>)-&gt;<a href="ident?i=ir_rmt_addr">ir_rmt_addr</a>)
<a name="L1190" href="source/net/ipv4/tcp_ipv4.c#L1190">1190</a>                         *strict = <a href="ident?i=true">true</a>;
<a name="L1191" href="source/net/ipv4/tcp_ipv4.c#L1191">1191</a>                 else
<a name="L1192" href="source/net/ipv4/tcp_ipv4.c#L1192">1192</a>                         *strict = <a href="ident?i=false">false</a>;
<a name="L1193" href="source/net/ipv4/tcp_ipv4.c#L1193">1193</a>         }
<a name="L1194" href="source/net/ipv4/tcp_ipv4.c#L1194">1194</a> 
<a name="L1195" href="source/net/ipv4/tcp_ipv4.c#L1195">1195</a>         return <a href="ident?i=dst">dst</a>;
<a name="L1196" href="source/net/ipv4/tcp_ipv4.c#L1196">1196</a> }
<a name="L1197" href="source/net/ipv4/tcp_ipv4.c#L1197">1197</a> 
<a name="L1198" href="source/net/ipv4/tcp_ipv4.c#L1198">1198</a> struct <a href="ident?i=request_sock_ops">request_sock_ops</a> <a href="ident?i=tcp_request_sock_ops">tcp_request_sock_ops</a> <a href="ident?i=__read_mostly">__read_mostly</a> = {
<a name="L1199" href="source/net/ipv4/tcp_ipv4.c#L1199">1199</a>         .<a href="ident?i=family">family</a>         =       <a href="ident?i=PF_INET">PF_INET</a>,
<a name="L1200" href="source/net/ipv4/tcp_ipv4.c#L1200">1200</a>         .obj_size       =       sizeof(struct <a href="ident?i=tcp_request_sock">tcp_request_sock</a>),
<a name="L1201" href="source/net/ipv4/tcp_ipv4.c#L1201">1201</a>         .rtx_syn_ack    =       <a href="ident?i=tcp_rtx_synack">tcp_rtx_synack</a>,
<a name="L1202" href="source/net/ipv4/tcp_ipv4.c#L1202">1202</a>         .<a href="ident?i=send_ack">send_ack</a>       =       <a href="ident?i=tcp_v4_reqsk_send_ack">tcp_v4_reqsk_send_ack</a>,
<a name="L1203" href="source/net/ipv4/tcp_ipv4.c#L1203">1203</a>         .destructor     =       <a href="ident?i=tcp_v4_reqsk_destructor">tcp_v4_reqsk_destructor</a>,
<a name="L1204" href="source/net/ipv4/tcp_ipv4.c#L1204">1204</a>         .<a href="ident?i=send_reset">send_reset</a>     =       <a href="ident?i=tcp_v4_send_reset">tcp_v4_send_reset</a>,
<a name="L1205" href="source/net/ipv4/tcp_ipv4.c#L1205">1205</a>         .syn_ack_timeout =      <a href="ident?i=tcp_syn_ack_timeout">tcp_syn_ack_timeout</a>,
<a name="L1206" href="source/net/ipv4/tcp_ipv4.c#L1206">1206</a> };
<a name="L1207" href="source/net/ipv4/tcp_ipv4.c#L1207">1207</a> 
<a name="L1208" href="source/net/ipv4/tcp_ipv4.c#L1208">1208</a> static const struct <a href="ident?i=tcp_request_sock_ops">tcp_request_sock_ops</a> <a href="ident?i=tcp_request_sock_ipv4_ops">tcp_request_sock_ipv4_ops</a> = {
<a name="L1209" href="source/net/ipv4/tcp_ipv4.c#L1209">1209</a>         .mss_clamp      =       <a href="ident?i=TCP_MSS_DEFAULT">TCP_MSS_DEFAULT</a>,
<a name="L1210" href="source/net/ipv4/tcp_ipv4.c#L1210">1210</a> #ifdef CONFIG_TCP_MD5SIG
<a name="L1211" href="source/net/ipv4/tcp_ipv4.c#L1211">1211</a>         .req_md5_lookup =       <a href="ident?i=tcp_v4_md5_lookup">tcp_v4_md5_lookup</a>,
<a name="L1212" href="source/net/ipv4/tcp_ipv4.c#L1212">1212</a>         .calc_md5_hash  =       <a href="ident?i=tcp_v4_md5_hash_skb">tcp_v4_md5_hash_skb</a>,
<a name="L1213" href="source/net/ipv4/tcp_ipv4.c#L1213">1213</a> #endif
<a name="L1214" href="source/net/ipv4/tcp_ipv4.c#L1214">1214</a>         .init_req       =       <a href="ident?i=tcp_v4_init_req">tcp_v4_init_req</a>,
<a name="L1215" href="source/net/ipv4/tcp_ipv4.c#L1215">1215</a> #ifdef CONFIG_SYN_COOKIES
<a name="L1216" href="source/net/ipv4/tcp_ipv4.c#L1216">1216</a>         .cookie_init_seq =      <a href="ident?i=cookie_v4_init_sequence">cookie_v4_init_sequence</a>,
<a name="L1217" href="source/net/ipv4/tcp_ipv4.c#L1217">1217</a> #endif
<a name="L1218" href="source/net/ipv4/tcp_ipv4.c#L1218">1218</a>         .route_req      =       <a href="ident?i=tcp_v4_route_req">tcp_v4_route_req</a>,
<a name="L1219" href="source/net/ipv4/tcp_ipv4.c#L1219">1219</a>         .<a href="ident?i=init_seq">init_seq</a>       =       <a href="ident?i=tcp_v4_init_sequence">tcp_v4_init_sequence</a>,
<a name="L1220" href="source/net/ipv4/tcp_ipv4.c#L1220">1220</a>         .send_synack    =       <a href="ident?i=tcp_v4_send_synack">tcp_v4_send_synack</a>,
<a name="L1221" href="source/net/ipv4/tcp_ipv4.c#L1221">1221</a>         .queue_hash_add =       <a href="ident?i=inet_csk_reqsk_queue_hash_add">inet_csk_reqsk_queue_hash_add</a>,
<a name="L1222" href="source/net/ipv4/tcp_ipv4.c#L1222">1222</a> };
<a name="L1223" href="source/net/ipv4/tcp_ipv4.c#L1223">1223</a> 
<a name="L1224" href="source/net/ipv4/tcp_ipv4.c#L1224">1224</a> int <a href="ident?i=tcp_v4_conn_request">tcp_v4_conn_request</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L1225" href="source/net/ipv4/tcp_ipv4.c#L1225">1225</a> {
<a name="L1226" href="source/net/ipv4/tcp_ipv4.c#L1226">1226</a>         <b><i>/* Never answer to SYNs send to broadcast or multicast */</i></b>
<a name="L1227" href="source/net/ipv4/tcp_ipv4.c#L1227">1227</a>         if (<a href="ident?i=skb_rtable">skb_rtable</a>(<a href="ident?i=skb">skb</a>)-&gt;rt_flags &amp; (<a href="ident?i=RTCF_BROADCAST">RTCF_BROADCAST</a> | <a href="ident?i=RTCF_MULTICAST">RTCF_MULTICAST</a>))
<a name="L1228" href="source/net/ipv4/tcp_ipv4.c#L1228">1228</a>                 goto <a href="ident?i=drop">drop</a>;
<a name="L1229" href="source/net/ipv4/tcp_ipv4.c#L1229">1229</a> 
<a name="L1230" href="source/net/ipv4/tcp_ipv4.c#L1230">1230</a>         return <a href="ident?i=tcp_conn_request">tcp_conn_request</a>(&amp;<a href="ident?i=tcp_request_sock_ops">tcp_request_sock_ops</a>,
<a name="L1231" href="source/net/ipv4/tcp_ipv4.c#L1231">1231</a>                                 &amp;<a href="ident?i=tcp_request_sock_ipv4_ops">tcp_request_sock_ipv4_ops</a>, sk, <a href="ident?i=skb">skb</a>);
<a name="L1232" href="source/net/ipv4/tcp_ipv4.c#L1232">1232</a> 
<a name="L1233" href="source/net/ipv4/tcp_ipv4.c#L1233">1233</a> <a href="ident?i=drop">drop</a>:
<a name="L1234" href="source/net/ipv4/tcp_ipv4.c#L1234">1234</a>         <a href="ident?i=NET_INC_STATS_BH">NET_INC_STATS_BH</a>(<a href="ident?i=sock_net">sock_net</a>(sk), LINUX_MIB_LISTENDROPS);
<a name="L1235" href="source/net/ipv4/tcp_ipv4.c#L1235">1235</a>         return 0;
<a name="L1236" href="source/net/ipv4/tcp_ipv4.c#L1236">1236</a> }
<a name="L1237" href="source/net/ipv4/tcp_ipv4.c#L1237">1237</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=tcp_v4_conn_request">tcp_v4_conn_request</a>);
<a name="L1238" href="source/net/ipv4/tcp_ipv4.c#L1238">1238</a> 
<a name="L1239" href="source/net/ipv4/tcp_ipv4.c#L1239">1239</a> 
<a name="L1240" href="source/net/ipv4/tcp_ipv4.c#L1240">1240</a> <b><i>/*</i></b>
<a name="L1241" href="source/net/ipv4/tcp_ipv4.c#L1241">1241</a> <b><i> * The three way handshake has completed - we got a valid synack -</i></b>
<a name="L1242" href="source/net/ipv4/tcp_ipv4.c#L1242">1242</a> <b><i> * now create the new socket.</i></b>
<a name="L1243" href="source/net/ipv4/tcp_ipv4.c#L1243">1243</a> <b><i> */</i></b>
<a name="L1244" href="source/net/ipv4/tcp_ipv4.c#L1244">1244</a> struct <a href="ident?i=sock">sock</a> *<a href="ident?i=tcp_v4_syn_recv_sock">tcp_v4_syn_recv_sock</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
<a name="L1245" href="source/net/ipv4/tcp_ipv4.c#L1245">1245</a>                                   struct <a href="ident?i=request_sock">request_sock</a> *<a href="ident?i=req">req</a>,
<a name="L1246" href="source/net/ipv4/tcp_ipv4.c#L1246">1246</a>                                   struct <a href="ident?i=dst_entry">dst_entry</a> *<a href="ident?i=dst">dst</a>)
<a name="L1247" href="source/net/ipv4/tcp_ipv4.c#L1247">1247</a> {
<a name="L1248" href="source/net/ipv4/tcp_ipv4.c#L1248">1248</a>         struct <a href="ident?i=inet_request_sock">inet_request_sock</a> *ireq;
<a name="L1249" href="source/net/ipv4/tcp_ipv4.c#L1249">1249</a>         struct <a href="ident?i=inet_sock">inet_sock</a> *newinet;
<a name="L1250" href="source/net/ipv4/tcp_ipv4.c#L1250">1250</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *newtp;
<a name="L1251" href="source/net/ipv4/tcp_ipv4.c#L1251">1251</a>         struct <a href="ident?i=sock">sock</a> *newsk;
<a name="L1252" href="source/net/ipv4/tcp_ipv4.c#L1252">1252</a> #ifdef CONFIG_TCP_MD5SIG
<a name="L1253" href="source/net/ipv4/tcp_ipv4.c#L1253">1253</a>         struct <a href="ident?i=tcp_md5sig_key">tcp_md5sig_key</a> *<a href="ident?i=key">key</a>;
<a name="L1254" href="source/net/ipv4/tcp_ipv4.c#L1254">1254</a> #endif
<a name="L1255" href="source/net/ipv4/tcp_ipv4.c#L1255">1255</a>         struct <a href="ident?i=ip_options_rcu">ip_options_rcu</a> *inet_opt;
<a name="L1256" href="source/net/ipv4/tcp_ipv4.c#L1256">1256</a> 
<a name="L1257" href="source/net/ipv4/tcp_ipv4.c#L1257">1257</a>         if (<a href="ident?i=sk_acceptq_is_full">sk_acceptq_is_full</a>(sk))
<a name="L1258" href="source/net/ipv4/tcp_ipv4.c#L1258">1258</a>                 goto exit_overflow;
<a name="L1259" href="source/net/ipv4/tcp_ipv4.c#L1259">1259</a> 
<a name="L1260" href="source/net/ipv4/tcp_ipv4.c#L1260">1260</a>         newsk = <a href="ident?i=tcp_create_openreq_child">tcp_create_openreq_child</a>(sk, <a href="ident?i=req">req</a>, <a href="ident?i=skb">skb</a>);
<a name="L1261" href="source/net/ipv4/tcp_ipv4.c#L1261">1261</a>         if (!newsk)
<a name="L1262" href="source/net/ipv4/tcp_ipv4.c#L1262">1262</a>                 goto exit_nonewsk;
<a name="L1263" href="source/net/ipv4/tcp_ipv4.c#L1263">1263</a> 
<a name="L1264" href="source/net/ipv4/tcp_ipv4.c#L1264">1264</a>         newsk-&gt;sk_gso_type = SKB_GSO_TCPV4;
<a name="L1265" href="source/net/ipv4/tcp_ipv4.c#L1265">1265</a>         <a href="ident?i=inet_sk_rx_dst_set">inet_sk_rx_dst_set</a>(newsk, <a href="ident?i=skb">skb</a>);
<a name="L1266" href="source/net/ipv4/tcp_ipv4.c#L1266">1266</a> 
<a name="L1267" href="source/net/ipv4/tcp_ipv4.c#L1267">1267</a>         newtp                 = <a href="ident?i=tcp_sk">tcp_sk</a>(newsk);
<a name="L1268" href="source/net/ipv4/tcp_ipv4.c#L1268">1268</a>         newinet               = <a href="ident?i=inet_sk">inet_sk</a>(newsk);
<a name="L1269" href="source/net/ipv4/tcp_ipv4.c#L1269">1269</a>         ireq                  = <a href="ident?i=inet_rsk">inet_rsk</a>(<a href="ident?i=req">req</a>);
<a name="L1270" href="source/net/ipv4/tcp_ipv4.c#L1270">1270</a>         <a href="ident?i=sk_daddr_set">sk_daddr_set</a>(newsk, ireq-&gt;<a href="ident?i=ir_rmt_addr">ir_rmt_addr</a>);
<a name="L1271" href="source/net/ipv4/tcp_ipv4.c#L1271">1271</a>         <a href="ident?i=sk_rcv_saddr_set">sk_rcv_saddr_set</a>(newsk, ireq-&gt;<a href="ident?i=ir_loc_addr">ir_loc_addr</a>);
<a name="L1272" href="source/net/ipv4/tcp_ipv4.c#L1272">1272</a>         newinet-&gt;inet_saddr           = ireq-&gt;<a href="ident?i=ir_loc_addr">ir_loc_addr</a>;
<a name="L1273" href="source/net/ipv4/tcp_ipv4.c#L1273">1273</a>         inet_opt              = ireq-&gt;opt;
<a name="L1274" href="source/net/ipv4/tcp_ipv4.c#L1274">1274</a>         <a href="ident?i=rcu_assign_pointer">rcu_assign_pointer</a>(newinet-&gt;inet_opt, inet_opt);
<a name="L1275" href="source/net/ipv4/tcp_ipv4.c#L1275">1275</a>         ireq-&gt;opt             = <a href="ident?i=NULL">NULL</a>;
<a name="L1276" href="source/net/ipv4/tcp_ipv4.c#L1276">1276</a>         newinet-&gt;mc_index     = <a href="ident?i=inet_iif">inet_iif</a>(<a href="ident?i=skb">skb</a>);
<a name="L1277" href="source/net/ipv4/tcp_ipv4.c#L1277">1277</a>         newinet-&gt;mc_ttl       = <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=ttl">ttl</a>;
<a name="L1278" href="source/net/ipv4/tcp_ipv4.c#L1278">1278</a>         newinet-&gt;rcv_tos      = <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;tos;
<a name="L1279" href="source/net/ipv4/tcp_ipv4.c#L1279">1279</a>         <a href="ident?i=inet_csk">inet_csk</a>(newsk)-&gt;icsk_ext_hdr_len = 0;
<a name="L1280" href="source/net/ipv4/tcp_ipv4.c#L1280">1280</a>         <a href="ident?i=inet_set_txhash">inet_set_txhash</a>(newsk);
<a name="L1281" href="source/net/ipv4/tcp_ipv4.c#L1281">1281</a>         if (inet_opt)
<a name="L1282" href="source/net/ipv4/tcp_ipv4.c#L1282">1282</a>                 <a href="ident?i=inet_csk">inet_csk</a>(newsk)-&gt;icsk_ext_hdr_len = inet_opt-&gt;opt.<a href="ident?i=optlen">optlen</a>;
<a name="L1283" href="source/net/ipv4/tcp_ipv4.c#L1283">1283</a>         newinet-&gt;inet_id = newtp-&gt;write_seq ^ <a href="ident?i=jiffies">jiffies</a>;
<a name="L1284" href="source/net/ipv4/tcp_ipv4.c#L1284">1284</a> 
<a name="L1285" href="source/net/ipv4/tcp_ipv4.c#L1285">1285</a>         if (!<a href="ident?i=dst">dst</a>) {
<a name="L1286" href="source/net/ipv4/tcp_ipv4.c#L1286">1286</a>                 <a href="ident?i=dst">dst</a> = <a href="ident?i=inet_csk_route_child_sock">inet_csk_route_child_sock</a>(sk, newsk, <a href="ident?i=req">req</a>);
<a name="L1287" href="source/net/ipv4/tcp_ipv4.c#L1287">1287</a>                 if (!<a href="ident?i=dst">dst</a>)
<a name="L1288" href="source/net/ipv4/tcp_ipv4.c#L1288">1288</a>                         goto put_and_exit;
<a name="L1289" href="source/net/ipv4/tcp_ipv4.c#L1289">1289</a>         } else {
<a name="L1290" href="source/net/ipv4/tcp_ipv4.c#L1290">1290</a>                 <b><i>/* syncookie case : see end of cookie_v4_check() */</i></b>
<a name="L1291" href="source/net/ipv4/tcp_ipv4.c#L1291">1291</a>         }
<a name="L1292" href="source/net/ipv4/tcp_ipv4.c#L1292">1292</a>         <a href="ident?i=sk_setup_caps">sk_setup_caps</a>(newsk, <a href="ident?i=dst">dst</a>);
<a name="L1293" href="source/net/ipv4/tcp_ipv4.c#L1293">1293</a> 
<a name="L1294" href="source/net/ipv4/tcp_ipv4.c#L1294">1294</a>         <a href="ident?i=tcp_ca_openreq_child">tcp_ca_openreq_child</a>(newsk, <a href="ident?i=dst">dst</a>);
<a name="L1295" href="source/net/ipv4/tcp_ipv4.c#L1295">1295</a> 
<a name="L1296" href="source/net/ipv4/tcp_ipv4.c#L1296">1296</a>         <a href="ident?i=tcp_sync_mss">tcp_sync_mss</a>(newsk, <a href="ident?i=dst_mtu">dst_mtu</a>(<a href="ident?i=dst">dst</a>));
<a name="L1297" href="source/net/ipv4/tcp_ipv4.c#L1297">1297</a>         newtp-&gt;advmss = <a href="ident?i=dst_metric_advmss">dst_metric_advmss</a>(<a href="ident?i=dst">dst</a>);
<a name="L1298" href="source/net/ipv4/tcp_ipv4.c#L1298">1298</a>         if (<a href="ident?i=tcp_sk">tcp_sk</a>(sk)-&gt;rx_opt.user_mss &amp;&amp;
<a name="L1299" href="source/net/ipv4/tcp_ipv4.c#L1299">1299</a>             <a href="ident?i=tcp_sk">tcp_sk</a>(sk)-&gt;rx_opt.user_mss &lt; newtp-&gt;advmss)
<a name="L1300" href="source/net/ipv4/tcp_ipv4.c#L1300">1300</a>                 newtp-&gt;advmss = <a href="ident?i=tcp_sk">tcp_sk</a>(sk)-&gt;rx_opt.user_mss;
<a name="L1301" href="source/net/ipv4/tcp_ipv4.c#L1301">1301</a> 
<a name="L1302" href="source/net/ipv4/tcp_ipv4.c#L1302">1302</a>         <a href="ident?i=tcp_initialize_rcv_mss">tcp_initialize_rcv_mss</a>(newsk);
<a name="L1303" href="source/net/ipv4/tcp_ipv4.c#L1303">1303</a> 
<a name="L1304" href="source/net/ipv4/tcp_ipv4.c#L1304">1304</a> #ifdef CONFIG_TCP_MD5SIG
<a name="L1305" href="source/net/ipv4/tcp_ipv4.c#L1305">1305</a>         <b><i>/* Copy over the MD5 key from the original socket */</i></b>
<a name="L1306" href="source/net/ipv4/tcp_ipv4.c#L1306">1306</a>         <a href="ident?i=key">key</a> = <a href="ident?i=tcp_md5_do_lookup">tcp_md5_do_lookup</a>(sk, (union <a href="ident?i=tcp_md5_addr">tcp_md5_addr</a> *)&amp;newinet-&gt;<a href="ident?i=inet_daddr">inet_daddr</a>,
<a name="L1307" href="source/net/ipv4/tcp_ipv4.c#L1307">1307</a>                                 <a href="ident?i=AF_INET">AF_INET</a>);
<a name="L1308" href="source/net/ipv4/tcp_ipv4.c#L1308">1308</a>         if (<a href="ident?i=key">key</a>) {
<a name="L1309" href="source/net/ipv4/tcp_ipv4.c#L1309">1309</a>                 <b><i>/*</i></b>
<a name="L1310" href="source/net/ipv4/tcp_ipv4.c#L1310">1310</a> <b><i>                 * We're using one, so create a matching key</i></b>
<a name="L1311" href="source/net/ipv4/tcp_ipv4.c#L1311">1311</a> <b><i>                 * on the newsk structure. If we fail to get</i></b>
<a name="L1312" href="source/net/ipv4/tcp_ipv4.c#L1312">1312</a> <b><i>                 * memory, then we end up not copying the key</i></b>
<a name="L1313" href="source/net/ipv4/tcp_ipv4.c#L1313">1313</a> <b><i>                 * across. Shucks.</i></b>
<a name="L1314" href="source/net/ipv4/tcp_ipv4.c#L1314">1314</a> <b><i>                 */</i></b>
<a name="L1315" href="source/net/ipv4/tcp_ipv4.c#L1315">1315</a>                 <a href="ident?i=tcp_md5_do_add">tcp_md5_do_add</a>(newsk, (union <a href="ident?i=tcp_md5_addr">tcp_md5_addr</a> *)&amp;newinet-&gt;<a href="ident?i=inet_daddr">inet_daddr</a>,
<a name="L1316" href="source/net/ipv4/tcp_ipv4.c#L1316">1316</a>                                <a href="ident?i=AF_INET">AF_INET</a>, <a href="ident?i=key">key</a>-&gt;<a href="ident?i=key">key</a>, <a href="ident?i=key">key</a>-&gt;keylen, <a href="ident?i=GFP_ATOMIC">GFP_ATOMIC</a>);
<a name="L1317" href="source/net/ipv4/tcp_ipv4.c#L1317">1317</a>                 <a href="ident?i=sk_nocaps_add">sk_nocaps_add</a>(newsk, <a href="ident?i=NETIF_F_GSO_MASK">NETIF_F_GSO_MASK</a>);
<a name="L1318" href="source/net/ipv4/tcp_ipv4.c#L1318">1318</a>         }
<a name="L1319" href="source/net/ipv4/tcp_ipv4.c#L1319">1319</a> #endif
<a name="L1320" href="source/net/ipv4/tcp_ipv4.c#L1320">1320</a> 
<a name="L1321" href="source/net/ipv4/tcp_ipv4.c#L1321">1321</a>         if (<a href="ident?i=__inet_inherit_port">__inet_inherit_port</a>(sk, newsk) &lt; 0)
<a name="L1322" href="source/net/ipv4/tcp_ipv4.c#L1322">1322</a>                 goto put_and_exit;
<a name="L1323" href="source/net/ipv4/tcp_ipv4.c#L1323">1323</a>         <a href="ident?i=__inet_hash_nolisten">__inet_hash_nolisten</a>(newsk, <a href="ident?i=NULL">NULL</a>);
<a name="L1324" href="source/net/ipv4/tcp_ipv4.c#L1324">1324</a> 
<a name="L1325" href="source/net/ipv4/tcp_ipv4.c#L1325">1325</a>         return newsk;
<a name="L1326" href="source/net/ipv4/tcp_ipv4.c#L1326">1326</a> 
<a name="L1327" href="source/net/ipv4/tcp_ipv4.c#L1327">1327</a> exit_overflow:
<a name="L1328" href="source/net/ipv4/tcp_ipv4.c#L1328">1328</a>         <a href="ident?i=NET_INC_STATS_BH">NET_INC_STATS_BH</a>(<a href="ident?i=sock_net">sock_net</a>(sk), LINUX_MIB_LISTENOVERFLOWS);
<a name="L1329" href="source/net/ipv4/tcp_ipv4.c#L1329">1329</a> exit_nonewsk:
<a name="L1330" href="source/net/ipv4/tcp_ipv4.c#L1330">1330</a>         <a href="ident?i=dst_release">dst_release</a>(<a href="ident?i=dst">dst</a>);
<a name="L1331" href="source/net/ipv4/tcp_ipv4.c#L1331">1331</a> <a href="ident?i=exit">exit</a>:
<a name="L1332" href="source/net/ipv4/tcp_ipv4.c#L1332">1332</a>         <a href="ident?i=NET_INC_STATS_BH">NET_INC_STATS_BH</a>(<a href="ident?i=sock_net">sock_net</a>(sk), LINUX_MIB_LISTENDROPS);
<a name="L1333" href="source/net/ipv4/tcp_ipv4.c#L1333">1333</a>         return <a href="ident?i=NULL">NULL</a>;
<a name="L1334" href="source/net/ipv4/tcp_ipv4.c#L1334">1334</a> put_and_exit:
<a name="L1335" href="source/net/ipv4/tcp_ipv4.c#L1335">1335</a>         <a href="ident?i=inet_csk_prepare_forced_close">inet_csk_prepare_forced_close</a>(newsk);
<a name="L1336" href="source/net/ipv4/tcp_ipv4.c#L1336">1336</a>         <a href="ident?i=tcp_done">tcp_done</a>(newsk);
<a name="L1337" href="source/net/ipv4/tcp_ipv4.c#L1337">1337</a>         goto <a href="ident?i=exit">exit</a>;
<a name="L1338" href="source/net/ipv4/tcp_ipv4.c#L1338">1338</a> }
<a name="L1339" href="source/net/ipv4/tcp_ipv4.c#L1339">1339</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=tcp_v4_syn_recv_sock">tcp_v4_syn_recv_sock</a>);
<a name="L1340" href="source/net/ipv4/tcp_ipv4.c#L1340">1340</a> 
<a name="L1341" href="source/net/ipv4/tcp_ipv4.c#L1341">1341</a> static struct <a href="ident?i=sock">sock</a> *<a href="ident?i=tcp_v4_hnd_req">tcp_v4_hnd_req</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L1342" href="source/net/ipv4/tcp_ipv4.c#L1342">1342</a> {
<a name="L1343" href="source/net/ipv4/tcp_ipv4.c#L1343">1343</a>         const struct <a href="ident?i=tcphdr">tcphdr</a> *<a href="ident?i=th">th</a> = <a href="ident?i=tcp_hdr">tcp_hdr</a>(<a href="ident?i=skb">skb</a>);
<a name="L1344" href="source/net/ipv4/tcp_ipv4.c#L1344">1344</a>         const struct <a href="ident?i=iphdr">iphdr</a> *iph = <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>);
<a name="L1345" href="source/net/ipv4/tcp_ipv4.c#L1345">1345</a>         struct <a href="ident?i=request_sock">request_sock</a> *<a href="ident?i=req">req</a>;
<a name="L1346" href="source/net/ipv4/tcp_ipv4.c#L1346">1346</a>         struct <a href="ident?i=sock">sock</a> *nsk;
<a name="L1347" href="source/net/ipv4/tcp_ipv4.c#L1347">1347</a> 
<a name="L1348" href="source/net/ipv4/tcp_ipv4.c#L1348">1348</a>         <a href="ident?i=req">req</a> = <a href="ident?i=inet_csk_search_req">inet_csk_search_req</a>(sk, <a href="ident?i=th">th</a>-&gt;source, iph-&gt;<a href="ident?i=saddr">saddr</a>, iph-&gt;<a href="ident?i=daddr">daddr</a>);
<a name="L1349" href="source/net/ipv4/tcp_ipv4.c#L1349">1349</a>         if (<a href="ident?i=req">req</a>) {
<a name="L1350" href="source/net/ipv4/tcp_ipv4.c#L1350">1350</a>                 nsk = <a href="ident?i=tcp_check_req">tcp_check_req</a>(sk, <a href="ident?i=skb">skb</a>, <a href="ident?i=req">req</a>, <a href="ident?i=false">false</a>);
<a name="L1351" href="source/net/ipv4/tcp_ipv4.c#L1351">1351</a>                 if (!nsk)
<a name="L1352" href="source/net/ipv4/tcp_ipv4.c#L1352">1352</a>                         <a href="ident?i=reqsk_put">reqsk_put</a>(<a href="ident?i=req">req</a>);
<a name="L1353" href="source/net/ipv4/tcp_ipv4.c#L1353">1353</a>                 return nsk;
<a name="L1354" href="source/net/ipv4/tcp_ipv4.c#L1354">1354</a>         }
<a name="L1355" href="source/net/ipv4/tcp_ipv4.c#L1355">1355</a> 
<a name="L1356" href="source/net/ipv4/tcp_ipv4.c#L1356">1356</a>         nsk = <a href="ident?i=inet_lookup_established">inet_lookup_established</a>(<a href="ident?i=sock_net">sock_net</a>(sk), &amp;<a href="ident?i=tcp_hashinfo">tcp_hashinfo</a>, iph-&gt;<a href="ident?i=saddr">saddr</a>,
<a name="L1357" href="source/net/ipv4/tcp_ipv4.c#L1357">1357</a>                         <a href="ident?i=th">th</a>-&gt;source, iph-&gt;<a href="ident?i=daddr">daddr</a>, <a href="ident?i=th">th</a>-&gt;<a href="ident?i=dest">dest</a>, <a href="ident?i=inet_iif">inet_iif</a>(<a href="ident?i=skb">skb</a>));
<a name="L1358" href="source/net/ipv4/tcp_ipv4.c#L1358">1358</a> 
<a name="L1359" href="source/net/ipv4/tcp_ipv4.c#L1359">1359</a>         if (nsk) {
<a name="L1360" href="source/net/ipv4/tcp_ipv4.c#L1360">1360</a>                 if (nsk-&gt;<a href="ident?i=sk_state">sk_state</a> != TCP_TIME_WAIT) {
<a name="L1361" href="source/net/ipv4/tcp_ipv4.c#L1361">1361</a>                         <a href="ident?i=bh_lock_sock">bh_lock_sock</a>(nsk);
<a name="L1362" href="source/net/ipv4/tcp_ipv4.c#L1362">1362</a>                         return nsk;
<a name="L1363" href="source/net/ipv4/tcp_ipv4.c#L1363">1363</a>                 }
<a name="L1364" href="source/net/ipv4/tcp_ipv4.c#L1364">1364</a>                 <a href="ident?i=inet_twsk_put">inet_twsk_put</a>(<a href="ident?i=inet_twsk">inet_twsk</a>(nsk));
<a name="L1365" href="source/net/ipv4/tcp_ipv4.c#L1365">1365</a>                 return <a href="ident?i=NULL">NULL</a>;
<a name="L1366" href="source/net/ipv4/tcp_ipv4.c#L1366">1366</a>         }
<a name="L1367" href="source/net/ipv4/tcp_ipv4.c#L1367">1367</a> 
<a name="L1368" href="source/net/ipv4/tcp_ipv4.c#L1368">1368</a> #ifdef CONFIG_SYN_COOKIES
<a name="L1369" href="source/net/ipv4/tcp_ipv4.c#L1369">1369</a>         if (!<a href="ident?i=th">th</a>-&gt;syn)
<a name="L1370" href="source/net/ipv4/tcp_ipv4.c#L1370">1370</a>                 sk = <a href="ident?i=cookie_v4_check">cookie_v4_check</a>(sk, <a href="ident?i=skb">skb</a>);
<a name="L1371" href="source/net/ipv4/tcp_ipv4.c#L1371">1371</a> #endif
<a name="L1372" href="source/net/ipv4/tcp_ipv4.c#L1372">1372</a>         return sk;
<a name="L1373" href="source/net/ipv4/tcp_ipv4.c#L1373">1373</a> }
<a name="L1374" href="source/net/ipv4/tcp_ipv4.c#L1374">1374</a> 
<a name="L1375" href="source/net/ipv4/tcp_ipv4.c#L1375">1375</a> <b><i>/* The socket must have it's spinlock held when we get</i></b>
<a name="L1376" href="source/net/ipv4/tcp_ipv4.c#L1376">1376</a> <b><i> * here.</i></b>
<a name="L1377" href="source/net/ipv4/tcp_ipv4.c#L1377">1377</a> <b><i> *</i></b>
<a name="L1378" href="source/net/ipv4/tcp_ipv4.c#L1378">1378</a> <b><i> * We have a potential double-lock case here, so even when</i></b>
<a name="L1379" href="source/net/ipv4/tcp_ipv4.c#L1379">1379</a> <b><i> * doing backlog processing we use the BH locking scheme.</i></b>
<a name="L1380" href="source/net/ipv4/tcp_ipv4.c#L1380">1380</a> <b><i> * This is because we cannot sleep with the original spinlock</i></b>
<a name="L1381" href="source/net/ipv4/tcp_ipv4.c#L1381">1381</a> <b><i> * held.</i></b>
<a name="L1382" href="source/net/ipv4/tcp_ipv4.c#L1382">1382</a> <b><i> */</i></b>
<a name="L1383" href="source/net/ipv4/tcp_ipv4.c#L1383">1383</a> int <a href="ident?i=tcp_v4_do_rcv">tcp_v4_do_rcv</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L1384" href="source/net/ipv4/tcp_ipv4.c#L1384">1384</a> {
<a name="L1385" href="source/net/ipv4/tcp_ipv4.c#L1385">1385</a>         struct <a href="ident?i=sock">sock</a> *rsk;
<a name="L1386" href="source/net/ipv4/tcp_ipv4.c#L1386">1386</a> 
<a name="L1387" href="source/net/ipv4/tcp_ipv4.c#L1387">1387</a>         if (sk-&gt;<a href="ident?i=sk_state">sk_state</a> == TCP_ESTABLISHED) { <b><i>/* Fast path */</i></b>
<a name="L1388" href="source/net/ipv4/tcp_ipv4.c#L1388">1388</a>                 struct <a href="ident?i=dst_entry">dst_entry</a> *<a href="ident?i=dst">dst</a> = sk-&gt;sk_rx_dst;
<a name="L1389" href="source/net/ipv4/tcp_ipv4.c#L1389">1389</a> 
<a name="L1390" href="source/net/ipv4/tcp_ipv4.c#L1390">1390</a>                 <a href="ident?i=sock_rps_save_rxhash">sock_rps_save_rxhash</a>(sk, <a href="ident?i=skb">skb</a>);
<a name="L1391" href="source/net/ipv4/tcp_ipv4.c#L1391">1391</a>                 <a href="ident?i=sk_mark_napi_id">sk_mark_napi_id</a>(sk, <a href="ident?i=skb">skb</a>);
<a name="L1392" href="source/net/ipv4/tcp_ipv4.c#L1392">1392</a>                 if (<a href="ident?i=dst">dst</a>) {
<a name="L1393" href="source/net/ipv4/tcp_ipv4.c#L1393">1393</a>                         if (<a href="ident?i=inet_sk">inet_sk</a>(sk)-&gt;rx_dst_ifindex != <a href="ident?i=skb">skb</a>-&gt;skb_iif ||
<a name="L1394" href="source/net/ipv4/tcp_ipv4.c#L1394">1394</a>                             !<a href="ident?i=dst">dst</a>-&gt;<a href="ident?i=ops">ops</a>-&gt;<a href="ident?i=check">check</a>(<a href="ident?i=dst">dst</a>, 0)) {
<a name="L1395" href="source/net/ipv4/tcp_ipv4.c#L1395">1395</a>                                 <a href="ident?i=dst_release">dst_release</a>(<a href="ident?i=dst">dst</a>);
<a name="L1396" href="source/net/ipv4/tcp_ipv4.c#L1396">1396</a>                                 sk-&gt;sk_rx_dst = <a href="ident?i=NULL">NULL</a>;
<a name="L1397" href="source/net/ipv4/tcp_ipv4.c#L1397">1397</a>                         }
<a name="L1398" href="source/net/ipv4/tcp_ipv4.c#L1398">1398</a>                 }
<a name="L1399" href="source/net/ipv4/tcp_ipv4.c#L1399">1399</a>                 <a href="ident?i=tcp_rcv_established">tcp_rcv_established</a>(sk, <a href="ident?i=skb">skb</a>, <a href="ident?i=tcp_hdr">tcp_hdr</a>(<a href="ident?i=skb">skb</a>), <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a>);
<a name="L1400" href="source/net/ipv4/tcp_ipv4.c#L1400">1400</a>                 return 0;
<a name="L1401" href="source/net/ipv4/tcp_ipv4.c#L1401">1401</a>         }
<a name="L1402" href="source/net/ipv4/tcp_ipv4.c#L1402">1402</a> 
<a name="L1403" href="source/net/ipv4/tcp_ipv4.c#L1403">1403</a>         if (<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a> &lt; <a href="ident?i=tcp_hdrlen">tcp_hdrlen</a>(<a href="ident?i=skb">skb</a>) || <a href="ident?i=tcp_checksum_complete">tcp_checksum_complete</a>(<a href="ident?i=skb">skb</a>))
<a name="L1404" href="source/net/ipv4/tcp_ipv4.c#L1404">1404</a>                 goto csum_err;
<a name="L1405" href="source/net/ipv4/tcp_ipv4.c#L1405">1405</a> 
<a name="L1406" href="source/net/ipv4/tcp_ipv4.c#L1406">1406</a>         if (sk-&gt;<a href="ident?i=sk_state">sk_state</a> == TCP_LISTEN) {
<a name="L1407" href="source/net/ipv4/tcp_ipv4.c#L1407">1407</a>                 struct <a href="ident?i=sock">sock</a> *nsk = <a href="ident?i=tcp_v4_hnd_req">tcp_v4_hnd_req</a>(sk, <a href="ident?i=skb">skb</a>);
<a name="L1408" href="source/net/ipv4/tcp_ipv4.c#L1408">1408</a>                 if (!nsk)
<a name="L1409" href="source/net/ipv4/tcp_ipv4.c#L1409">1409</a>                         goto <a href="ident?i=discard">discard</a>;
<a name="L1410" href="source/net/ipv4/tcp_ipv4.c#L1410">1410</a> 
<a name="L1411" href="source/net/ipv4/tcp_ipv4.c#L1411">1411</a>                 if (nsk != sk) {
<a name="L1412" href="source/net/ipv4/tcp_ipv4.c#L1412">1412</a>                         <a href="ident?i=sock_rps_save_rxhash">sock_rps_save_rxhash</a>(nsk, <a href="ident?i=skb">skb</a>);
<a name="L1413" href="source/net/ipv4/tcp_ipv4.c#L1413">1413</a>                         <a href="ident?i=sk_mark_napi_id">sk_mark_napi_id</a>(sk, <a href="ident?i=skb">skb</a>);
<a name="L1414" href="source/net/ipv4/tcp_ipv4.c#L1414">1414</a>                         if (<a href="ident?i=tcp_child_process">tcp_child_process</a>(sk, nsk, <a href="ident?i=skb">skb</a>)) {
<a name="L1415" href="source/net/ipv4/tcp_ipv4.c#L1415">1415</a>                                 rsk = nsk;
<a name="L1416" href="source/net/ipv4/tcp_ipv4.c#L1416">1416</a>                                 goto <a href="ident?i=reset">reset</a>;
<a name="L1417" href="source/net/ipv4/tcp_ipv4.c#L1417">1417</a>                         }
<a name="L1418" href="source/net/ipv4/tcp_ipv4.c#L1418">1418</a>                         return 0;
<a name="L1419" href="source/net/ipv4/tcp_ipv4.c#L1419">1419</a>                 }
<a name="L1420" href="source/net/ipv4/tcp_ipv4.c#L1420">1420</a>         } else
<a name="L1421" href="source/net/ipv4/tcp_ipv4.c#L1421">1421</a>                 <a href="ident?i=sock_rps_save_rxhash">sock_rps_save_rxhash</a>(sk, <a href="ident?i=skb">skb</a>);
<a name="L1422" href="source/net/ipv4/tcp_ipv4.c#L1422">1422</a> 
<a name="L1423" href="source/net/ipv4/tcp_ipv4.c#L1423">1423</a>         if (<a href="ident?i=tcp_rcv_state_process">tcp_rcv_state_process</a>(sk, <a href="ident?i=skb">skb</a>, <a href="ident?i=tcp_hdr">tcp_hdr</a>(<a href="ident?i=skb">skb</a>), <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a>)) {
<a name="L1424" href="source/net/ipv4/tcp_ipv4.c#L1424">1424</a>                 rsk = sk;
<a name="L1425" href="source/net/ipv4/tcp_ipv4.c#L1425">1425</a>                 goto <a href="ident?i=reset">reset</a>;
<a name="L1426" href="source/net/ipv4/tcp_ipv4.c#L1426">1426</a>         }
<a name="L1427" href="source/net/ipv4/tcp_ipv4.c#L1427">1427</a>         return 0;
<a name="L1428" href="source/net/ipv4/tcp_ipv4.c#L1428">1428</a> 
<a name="L1429" href="source/net/ipv4/tcp_ipv4.c#L1429">1429</a> <a href="ident?i=reset">reset</a>:
<a name="L1430" href="source/net/ipv4/tcp_ipv4.c#L1430">1430</a>         <a href="ident?i=tcp_v4_send_reset">tcp_v4_send_reset</a>(rsk, <a href="ident?i=skb">skb</a>);
<a name="L1431" href="source/net/ipv4/tcp_ipv4.c#L1431">1431</a> <a href="ident?i=discard">discard</a>:
<a name="L1432" href="source/net/ipv4/tcp_ipv4.c#L1432">1432</a>         <a href="ident?i=kfree_skb">kfree_skb</a>(<a href="ident?i=skb">skb</a>);
<a name="L1433" href="source/net/ipv4/tcp_ipv4.c#L1433">1433</a>         <b><i>/* Be careful here. If this function gets more complicated and</i></b>
<a name="L1434" href="source/net/ipv4/tcp_ipv4.c#L1434">1434</a> <b><i>         * gcc suffers from register pressure on the x86, sk (in %ebx)</i></b>
<a name="L1435" href="source/net/ipv4/tcp_ipv4.c#L1435">1435</a> <b><i>         * might be destroyed here. This current version compiles correctly,</i></b>
<a name="L1436" href="source/net/ipv4/tcp_ipv4.c#L1436">1436</a> <b><i>         * but you have been warned.</i></b>
<a name="L1437" href="source/net/ipv4/tcp_ipv4.c#L1437">1437</a> <b><i>         */</i></b>
<a name="L1438" href="source/net/ipv4/tcp_ipv4.c#L1438">1438</a>         return 0;
<a name="L1439" href="source/net/ipv4/tcp_ipv4.c#L1439">1439</a> 
<a name="L1440" href="source/net/ipv4/tcp_ipv4.c#L1440">1440</a> csum_err:
<a name="L1441" href="source/net/ipv4/tcp_ipv4.c#L1441">1441</a>         <a href="ident?i=TCP_INC_STATS_BH">TCP_INC_STATS_BH</a>(<a href="ident?i=sock_net">sock_net</a>(sk), TCP_MIB_CSUMERRORS);
<a name="L1442" href="source/net/ipv4/tcp_ipv4.c#L1442">1442</a>         <a href="ident?i=TCP_INC_STATS_BH">TCP_INC_STATS_BH</a>(<a href="ident?i=sock_net">sock_net</a>(sk), TCP_MIB_INERRS);
<a name="L1443" href="source/net/ipv4/tcp_ipv4.c#L1443">1443</a>         goto <a href="ident?i=discard">discard</a>;
<a name="L1444" href="source/net/ipv4/tcp_ipv4.c#L1444">1444</a> }
<a name="L1445" href="source/net/ipv4/tcp_ipv4.c#L1445">1445</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=tcp_v4_do_rcv">tcp_v4_do_rcv</a>);
<a name="L1446" href="source/net/ipv4/tcp_ipv4.c#L1446">1446</a> 
<a name="L1447" href="source/net/ipv4/tcp_ipv4.c#L1447">1447</a> void <a href="ident?i=tcp_v4_early_demux">tcp_v4_early_demux</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L1448" href="source/net/ipv4/tcp_ipv4.c#L1448">1448</a> {
<a name="L1449" href="source/net/ipv4/tcp_ipv4.c#L1449">1449</a>         const struct <a href="ident?i=iphdr">iphdr</a> *iph;
<a name="L1450" href="source/net/ipv4/tcp_ipv4.c#L1450">1450</a>         const struct <a href="ident?i=tcphdr">tcphdr</a> *<a href="ident?i=th">th</a>;
<a name="L1451" href="source/net/ipv4/tcp_ipv4.c#L1451">1451</a>         struct <a href="ident?i=sock">sock</a> *sk;
<a name="L1452" href="source/net/ipv4/tcp_ipv4.c#L1452">1452</a> 
<a name="L1453" href="source/net/ipv4/tcp_ipv4.c#L1453">1453</a>         if (<a href="ident?i=skb">skb</a>-&gt;pkt_type != <a href="ident?i=PACKET_HOST">PACKET_HOST</a>)
<a name="L1454" href="source/net/ipv4/tcp_ipv4.c#L1454">1454</a>                 return;
<a name="L1455" href="source/net/ipv4/tcp_ipv4.c#L1455">1455</a> 
<a name="L1456" href="source/net/ipv4/tcp_ipv4.c#L1456">1456</a>         if (!<a href="ident?i=pskb_may_pull">pskb_may_pull</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=skb_transport_offset">skb_transport_offset</a>(<a href="ident?i=skb">skb</a>) + sizeof(struct <a href="ident?i=tcphdr">tcphdr</a>)))
<a name="L1457" href="source/net/ipv4/tcp_ipv4.c#L1457">1457</a>                 return;
<a name="L1458" href="source/net/ipv4/tcp_ipv4.c#L1458">1458</a> 
<a name="L1459" href="source/net/ipv4/tcp_ipv4.c#L1459">1459</a>         iph = <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>);
<a name="L1460" href="source/net/ipv4/tcp_ipv4.c#L1460">1460</a>         <a href="ident?i=th">th</a> = <a href="ident?i=tcp_hdr">tcp_hdr</a>(<a href="ident?i=skb">skb</a>);
<a name="L1461" href="source/net/ipv4/tcp_ipv4.c#L1461">1461</a> 
<a name="L1462" href="source/net/ipv4/tcp_ipv4.c#L1462">1462</a>         if (<a href="ident?i=th">th</a>-&gt;doff &lt; sizeof(struct <a href="ident?i=tcphdr">tcphdr</a>) / 4)
<a name="L1463" href="source/net/ipv4/tcp_ipv4.c#L1463">1463</a>                 return;
<a name="L1464" href="source/net/ipv4/tcp_ipv4.c#L1464">1464</a> 
<a name="L1465" href="source/net/ipv4/tcp_ipv4.c#L1465">1465</a>         sk = <a href="ident?i=__inet_lookup_established">__inet_lookup_established</a>(<a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=dev">dev</a>), &amp;<a href="ident?i=tcp_hashinfo">tcp_hashinfo</a>,
<a name="L1466" href="source/net/ipv4/tcp_ipv4.c#L1466">1466</a>                                        iph-&gt;<a href="ident?i=saddr">saddr</a>, <a href="ident?i=th">th</a>-&gt;source,
<a name="L1467" href="source/net/ipv4/tcp_ipv4.c#L1467">1467</a>                                        iph-&gt;<a href="ident?i=daddr">daddr</a>, <a href="ident?i=ntohs">ntohs</a>(<a href="ident?i=th">th</a>-&gt;<a href="ident?i=dest">dest</a>),
<a name="L1468" href="source/net/ipv4/tcp_ipv4.c#L1468">1468</a>                                        <a href="ident?i=skb">skb</a>-&gt;skb_iif);
<a name="L1469" href="source/net/ipv4/tcp_ipv4.c#L1469">1469</a>         if (sk) {
<a name="L1470" href="source/net/ipv4/tcp_ipv4.c#L1470">1470</a>                 <a href="ident?i=skb">skb</a>-&gt;sk = sk;
<a name="L1471" href="source/net/ipv4/tcp_ipv4.c#L1471">1471</a>                 <a href="ident?i=skb">skb</a>-&gt;destructor = <a href="ident?i=sock_edemux">sock_edemux</a>;
<a name="L1472" href="source/net/ipv4/tcp_ipv4.c#L1472">1472</a>                 if (<a href="ident?i=sk_fullsock">sk_fullsock</a>(sk)) {
<a name="L1473" href="source/net/ipv4/tcp_ipv4.c#L1473">1473</a>                         struct <a href="ident?i=dst_entry">dst_entry</a> *<a href="ident?i=dst">dst</a> = <a href="ident?i=READ_ONCE">READ_ONCE</a>(sk-&gt;sk_rx_dst);
<a name="L1474" href="source/net/ipv4/tcp_ipv4.c#L1474">1474</a> 
<a name="L1475" href="source/net/ipv4/tcp_ipv4.c#L1475">1475</a>                         if (<a href="ident?i=dst">dst</a>)
<a name="L1476" href="source/net/ipv4/tcp_ipv4.c#L1476">1476</a>                                 <a href="ident?i=dst">dst</a> = <a href="ident?i=dst_check">dst_check</a>(<a href="ident?i=dst">dst</a>, 0);
<a name="L1477" href="source/net/ipv4/tcp_ipv4.c#L1477">1477</a>                         if (<a href="ident?i=dst">dst</a> &amp;&amp;
<a name="L1478" href="source/net/ipv4/tcp_ipv4.c#L1478">1478</a>                             <a href="ident?i=inet_sk">inet_sk</a>(sk)-&gt;rx_dst_ifindex == <a href="ident?i=skb">skb</a>-&gt;skb_iif)
<a name="L1479" href="source/net/ipv4/tcp_ipv4.c#L1479">1479</a>                                 <a href="ident?i=skb_dst_set_noref">skb_dst_set_noref</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=dst">dst</a>);
<a name="L1480" href="source/net/ipv4/tcp_ipv4.c#L1480">1480</a>                 }
<a name="L1481" href="source/net/ipv4/tcp_ipv4.c#L1481">1481</a>         }
<a name="L1482" href="source/net/ipv4/tcp_ipv4.c#L1482">1482</a> }
<a name="L1483" href="source/net/ipv4/tcp_ipv4.c#L1483">1483</a> 
<a name="L1484" href="source/net/ipv4/tcp_ipv4.c#L1484">1484</a> <b><i>/* Packet is added to VJ-style prequeue for processing in process</i></b>
<a name="L1485" href="source/net/ipv4/tcp_ipv4.c#L1485">1485</a> <b><i> * context, if a reader task is waiting. Apparently, this exciting</i></b>
<a name="L1486" href="source/net/ipv4/tcp_ipv4.c#L1486">1486</a> <b><i> * idea (VJ's mail "Re: query about TCP header on tcp-ip" of 07 Sep 93)</i></b>
<a name="L1487" href="source/net/ipv4/tcp_ipv4.c#L1487">1487</a> <b><i> * failed somewhere. Latency? Burstiness? Well, at least now we will</i></b>
<a name="L1488" href="source/net/ipv4/tcp_ipv4.c#L1488">1488</a> <b><i> * see, why it failed. 8)8)                               --ANK</i></b>
<a name="L1489" href="source/net/ipv4/tcp_ipv4.c#L1489">1489</a> <b><i> *</i></b>
<a name="L1490" href="source/net/ipv4/tcp_ipv4.c#L1490">1490</a> <b><i> */</i></b>
<a name="L1491" href="source/net/ipv4/tcp_ipv4.c#L1491">1491</a> <a href="ident?i=bool">bool</a> <a href="ident?i=tcp_prequeue">tcp_prequeue</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L1492" href="source/net/ipv4/tcp_ipv4.c#L1492">1492</a> {
<a name="L1493" href="source/net/ipv4/tcp_ipv4.c#L1493">1493</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L1494" href="source/net/ipv4/tcp_ipv4.c#L1494">1494</a> 
<a name="L1495" href="source/net/ipv4/tcp_ipv4.c#L1495">1495</a>         if (<a href="ident?i=sysctl_tcp_low_latency">sysctl_tcp_low_latency</a> || !<a href="ident?i=tp">tp</a>-&gt;ucopy.<a href="ident?i=task">task</a>)
<a name="L1496" href="source/net/ipv4/tcp_ipv4.c#L1496">1496</a>                 return <a href="ident?i=false">false</a>;
<a name="L1497" href="source/net/ipv4/tcp_ipv4.c#L1497">1497</a> 
<a name="L1498" href="source/net/ipv4/tcp_ipv4.c#L1498">1498</a>         if (<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a> &lt;= <a href="ident?i=tcp_hdrlen">tcp_hdrlen</a>(<a href="ident?i=skb">skb</a>) &amp;&amp;
<a name="L1499" href="source/net/ipv4/tcp_ipv4.c#L1499">1499</a>             <a href="ident?i=skb_queue_len">skb_queue_len</a>(&amp;<a href="ident?i=tp">tp</a>-&gt;ucopy.prequeue) == 0)
<a name="L1500" href="source/net/ipv4/tcp_ipv4.c#L1500">1500</a>                 return <a href="ident?i=false">false</a>;
<a name="L1501" href="source/net/ipv4/tcp_ipv4.c#L1501">1501</a> 
<a name="L1502" href="source/net/ipv4/tcp_ipv4.c#L1502">1502</a>         <b><i>/* Before escaping RCU protected region, we need to take care of skb</i></b>
<a name="L1503" href="source/net/ipv4/tcp_ipv4.c#L1503">1503</a> <b><i>         * dst. Prequeue is only enabled for established sockets.</i></b>
<a name="L1504" href="source/net/ipv4/tcp_ipv4.c#L1504">1504</a> <b><i>         * For such sockets, we might need the skb dst only to set sk-&gt;sk_rx_dst</i></b>
<a name="L1505" href="source/net/ipv4/tcp_ipv4.c#L1505">1505</a> <b><i>         * Instead of doing full sk_rx_dst validity here, let's perform</i></b>
<a name="L1506" href="source/net/ipv4/tcp_ipv4.c#L1506">1506</a> <b><i>         * an optimistic check.</i></b>
<a name="L1507" href="source/net/ipv4/tcp_ipv4.c#L1507">1507</a> <b><i>         */</i></b>
<a name="L1508" href="source/net/ipv4/tcp_ipv4.c#L1508">1508</a>         if (<a href="ident?i=likely">likely</a>(sk-&gt;sk_rx_dst))
<a name="L1509" href="source/net/ipv4/tcp_ipv4.c#L1509">1509</a>                 <a href="ident?i=skb_dst_drop">skb_dst_drop</a>(<a href="ident?i=skb">skb</a>);
<a name="L1510" href="source/net/ipv4/tcp_ipv4.c#L1510">1510</a>         else
<a name="L1511" href="source/net/ipv4/tcp_ipv4.c#L1511">1511</a>                 <a href="ident?i=skb_dst_force">skb_dst_force</a>(<a href="ident?i=skb">skb</a>);
<a name="L1512" href="source/net/ipv4/tcp_ipv4.c#L1512">1512</a> 
<a name="L1513" href="source/net/ipv4/tcp_ipv4.c#L1513">1513</a>         <a href="ident?i=__skb_queue_tail">__skb_queue_tail</a>(&amp;<a href="ident?i=tp">tp</a>-&gt;ucopy.prequeue, <a href="ident?i=skb">skb</a>);
<a name="L1514" href="source/net/ipv4/tcp_ipv4.c#L1514">1514</a>         <a href="ident?i=tp">tp</a>-&gt;ucopy.<a href="ident?i=memory">memory</a> += <a href="ident?i=skb">skb</a>-&gt;truesize;
<a name="L1515" href="source/net/ipv4/tcp_ipv4.c#L1515">1515</a>         if (<a href="ident?i=tp">tp</a>-&gt;ucopy.<a href="ident?i=memory">memory</a> &gt; sk-&gt;sk_rcvbuf) {
<a name="L1516" href="source/net/ipv4/tcp_ipv4.c#L1516">1516</a>                 struct <a href="ident?i=sk_buff">sk_buff</a> *skb1;
<a name="L1517" href="source/net/ipv4/tcp_ipv4.c#L1517">1517</a> 
<a name="L1518" href="source/net/ipv4/tcp_ipv4.c#L1518">1518</a>                 <a href="ident?i=BUG_ON">BUG_ON</a>(<a href="ident?i=sock_owned_by_user">sock_owned_by_user</a>(sk));
<a name="L1519" href="source/net/ipv4/tcp_ipv4.c#L1519">1519</a> 
<a name="L1520" href="source/net/ipv4/tcp_ipv4.c#L1520">1520</a>                 while ((skb1 = <a href="ident?i=__skb_dequeue">__skb_dequeue</a>(&amp;<a href="ident?i=tp">tp</a>-&gt;ucopy.prequeue)) != <a href="ident?i=NULL">NULL</a>) {
<a name="L1521" href="source/net/ipv4/tcp_ipv4.c#L1521">1521</a>                         <a href="ident?i=sk_backlog_rcv">sk_backlog_rcv</a>(sk, skb1);
<a name="L1522" href="source/net/ipv4/tcp_ipv4.c#L1522">1522</a>                         <a href="ident?i=NET_INC_STATS_BH">NET_INC_STATS_BH</a>(<a href="ident?i=sock_net">sock_net</a>(sk),
<a name="L1523" href="source/net/ipv4/tcp_ipv4.c#L1523">1523</a>                                          LINUX_MIB_TCPPREQUEUEDROPPED);
<a name="L1524" href="source/net/ipv4/tcp_ipv4.c#L1524">1524</a>                 }
<a name="L1525" href="source/net/ipv4/tcp_ipv4.c#L1525">1525</a> 
<a name="L1526" href="source/net/ipv4/tcp_ipv4.c#L1526">1526</a>                 <a href="ident?i=tp">tp</a>-&gt;ucopy.<a href="ident?i=memory">memory</a> = 0;
<a name="L1527" href="source/net/ipv4/tcp_ipv4.c#L1527">1527</a>         } else if (<a href="ident?i=skb_queue_len">skb_queue_len</a>(&amp;<a href="ident?i=tp">tp</a>-&gt;ucopy.prequeue) == 1) {
<a name="L1528" href="source/net/ipv4/tcp_ipv4.c#L1528">1528</a>                 <a href="ident?i=wake_up_interruptible_sync_poll">wake_up_interruptible_sync_poll</a>(<a href="ident?i=sk_sleep">sk_sleep</a>(sk),
<a name="L1529" href="source/net/ipv4/tcp_ipv4.c#L1529">1529</a>                                            <a href="ident?i=POLLIN">POLLIN</a> | <a href="ident?i=POLLRDNORM">POLLRDNORM</a> | <a href="ident?i=POLLRDBAND">POLLRDBAND</a>);
<a name="L1530" href="source/net/ipv4/tcp_ipv4.c#L1530">1530</a>                 if (!<a href="ident?i=inet_csk_ack_scheduled">inet_csk_ack_scheduled</a>(sk))
<a name="L1531" href="source/net/ipv4/tcp_ipv4.c#L1531">1531</a>                         <a href="ident?i=inet_csk_reset_xmit_timer">inet_csk_reset_xmit_timer</a>(sk, <a href="ident?i=ICSK_TIME_DACK">ICSK_TIME_DACK</a>,
<a name="L1532" href="source/net/ipv4/tcp_ipv4.c#L1532">1532</a>                                                   (3 * <a href="ident?i=tcp_rto_min">tcp_rto_min</a>(sk)) / 4,
<a name="L1533" href="source/net/ipv4/tcp_ipv4.c#L1533">1533</a>                                                   <a href="ident?i=TCP_RTO_MAX">TCP_RTO_MAX</a>);
<a name="L1534" href="source/net/ipv4/tcp_ipv4.c#L1534">1534</a>         }
<a name="L1535" href="source/net/ipv4/tcp_ipv4.c#L1535">1535</a>         return <a href="ident?i=true">true</a>;
<a name="L1536" href="source/net/ipv4/tcp_ipv4.c#L1536">1536</a> }
<a name="L1537" href="source/net/ipv4/tcp_ipv4.c#L1537">1537</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=tcp_prequeue">tcp_prequeue</a>);
<a name="L1538" href="source/net/ipv4/tcp_ipv4.c#L1538">1538</a> 
<a name="L1539" href="source/net/ipv4/tcp_ipv4.c#L1539">1539</a> <b><i>/*</i></b>
<a name="L1540" href="source/net/ipv4/tcp_ipv4.c#L1540">1540</a> <b><i> *      From tcp_input.c</i></b>
<a name="L1541" href="source/net/ipv4/tcp_ipv4.c#L1541">1541</a> <b><i> */</i></b>
<a name="L1542" href="source/net/ipv4/tcp_ipv4.c#L1542">1542</a> 
<a name="L1543" href="source/net/ipv4/tcp_ipv4.c#L1543">1543</a> int <a href="ident?i=tcp_v4_rcv">tcp_v4_rcv</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L1544" href="source/net/ipv4/tcp_ipv4.c#L1544">1544</a> {
<a name="L1545" href="source/net/ipv4/tcp_ipv4.c#L1545">1545</a>         const struct <a href="ident?i=iphdr">iphdr</a> *iph;
<a name="L1546" href="source/net/ipv4/tcp_ipv4.c#L1546">1546</a>         const struct <a href="ident?i=tcphdr">tcphdr</a> *<a href="ident?i=th">th</a>;
<a name="L1547" href="source/net/ipv4/tcp_ipv4.c#L1547">1547</a>         struct <a href="ident?i=sock">sock</a> *sk;
<a name="L1548" href="source/net/ipv4/tcp_ipv4.c#L1548">1548</a>         int <a href="ident?i=ret">ret</a>;
<a name="L1549" href="source/net/ipv4/tcp_ipv4.c#L1549">1549</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=dev">dev</a>);
<a name="L1550" href="source/net/ipv4/tcp_ipv4.c#L1550">1550</a> 
<a name="L1551" href="source/net/ipv4/tcp_ipv4.c#L1551">1551</a>         if (<a href="ident?i=skb">skb</a>-&gt;pkt_type != <a href="ident?i=PACKET_HOST">PACKET_HOST</a>)
<a name="L1552" href="source/net/ipv4/tcp_ipv4.c#L1552">1552</a>                 goto discard_it;
<a name="L1553" href="source/net/ipv4/tcp_ipv4.c#L1553">1553</a> 
<a name="L1554" href="source/net/ipv4/tcp_ipv4.c#L1554">1554</a>         <b><i>/* Count it even if it's bad */</i></b>
<a name="L1555" href="source/net/ipv4/tcp_ipv4.c#L1555">1555</a>         <a href="ident?i=TCP_INC_STATS_BH">TCP_INC_STATS_BH</a>(<a href="ident?i=net">net</a>, TCP_MIB_INSEGS);
<a name="L1556" href="source/net/ipv4/tcp_ipv4.c#L1556">1556</a> 
<a name="L1557" href="source/net/ipv4/tcp_ipv4.c#L1557">1557</a>         if (!<a href="ident?i=pskb_may_pull">pskb_may_pull</a>(<a href="ident?i=skb">skb</a>, sizeof(struct <a href="ident?i=tcphdr">tcphdr</a>)))
<a name="L1558" href="source/net/ipv4/tcp_ipv4.c#L1558">1558</a>                 goto discard_it;
<a name="L1559" href="source/net/ipv4/tcp_ipv4.c#L1559">1559</a> 
<a name="L1560" href="source/net/ipv4/tcp_ipv4.c#L1560">1560</a>         <a href="ident?i=th">th</a> = <a href="ident?i=tcp_hdr">tcp_hdr</a>(<a href="ident?i=skb">skb</a>);
<a name="L1561" href="source/net/ipv4/tcp_ipv4.c#L1561">1561</a> 
<a name="L1562" href="source/net/ipv4/tcp_ipv4.c#L1562">1562</a>         if (<a href="ident?i=th">th</a>-&gt;doff &lt; sizeof(struct <a href="ident?i=tcphdr">tcphdr</a>) / 4)
<a name="L1563" href="source/net/ipv4/tcp_ipv4.c#L1563">1563</a>                 goto bad_packet;
<a name="L1564" href="source/net/ipv4/tcp_ipv4.c#L1564">1564</a>         if (!<a href="ident?i=pskb_may_pull">pskb_may_pull</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=th">th</a>-&gt;doff * 4))
<a name="L1565" href="source/net/ipv4/tcp_ipv4.c#L1565">1565</a>                 goto discard_it;
<a name="L1566" href="source/net/ipv4/tcp_ipv4.c#L1566">1566</a> 
<a name="L1567" href="source/net/ipv4/tcp_ipv4.c#L1567">1567</a>         <b><i>/* An explanation is required here, I think.</i></b>
<a name="L1568" href="source/net/ipv4/tcp_ipv4.c#L1568">1568</a> <b><i>         * Packet length and doff are validated by header prediction,</i></b>
<a name="L1569" href="source/net/ipv4/tcp_ipv4.c#L1569">1569</a> <b><i>         * provided case of th-&gt;doff==0 is eliminated.</i></b>
<a name="L1570" href="source/net/ipv4/tcp_ipv4.c#L1570">1570</a> <b><i>         * So, we defer the checks. */</i></b>
<a name="L1571" href="source/net/ipv4/tcp_ipv4.c#L1571">1571</a> 
<a name="L1572" href="source/net/ipv4/tcp_ipv4.c#L1572">1572</a>         if (<a href="ident?i=skb_checksum_init">skb_checksum_init</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=IPPROTO_TCP">IPPROTO_TCP</a>, <a href="ident?i=inet_compute_pseudo">inet_compute_pseudo</a>))
<a name="L1573" href="source/net/ipv4/tcp_ipv4.c#L1573">1573</a>                 goto csum_error;
<a name="L1574" href="source/net/ipv4/tcp_ipv4.c#L1574">1574</a> 
<a name="L1575" href="source/net/ipv4/tcp_ipv4.c#L1575">1575</a>         <a href="ident?i=th">th</a> = <a href="ident?i=tcp_hdr">tcp_hdr</a>(<a href="ident?i=skb">skb</a>);
<a name="L1576" href="source/net/ipv4/tcp_ipv4.c#L1576">1576</a>         iph = <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>);
<a name="L1577" href="source/net/ipv4/tcp_ipv4.c#L1577">1577</a>         <b><i>/* This is tricky : We move IPCB at its correct location into TCP_SKB_CB()</i></b>
<a name="L1578" href="source/net/ipv4/tcp_ipv4.c#L1578">1578</a> <b><i>         * barrier() makes sure compiler wont play fool^Waliasing games.</i></b>
<a name="L1579" href="source/net/ipv4/tcp_ipv4.c#L1579">1579</a> <b><i>         */</i></b>
<a name="L1580" href="source/net/ipv4/tcp_ipv4.c#L1580">1580</a>         <a href="ident?i=memmove">memmove</a>(&amp;<a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=header">header</a>.h4, <a href="ident?i=IPCB">IPCB</a>(<a href="ident?i=skb">skb</a>),
<a name="L1581" href="source/net/ipv4/tcp_ipv4.c#L1581">1581</a>                 sizeof(struct <a href="ident?i=inet_skb_parm">inet_skb_parm</a>));
<a name="L1582" href="source/net/ipv4/tcp_ipv4.c#L1582">1582</a>         <a href="ident?i=barrier">barrier</a>();
<a name="L1583" href="source/net/ipv4/tcp_ipv4.c#L1583">1583</a> 
<a name="L1584" href="source/net/ipv4/tcp_ipv4.c#L1584">1584</a>         <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=seq">seq</a> = <a href="ident?i=ntohl">ntohl</a>(<a href="ident?i=th">th</a>-&gt;<a href="ident?i=seq">seq</a>);
<a name="L1585" href="source/net/ipv4/tcp_ipv4.c#L1585">1585</a>         <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;end_seq = (<a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=seq">seq</a> + <a href="ident?i=th">th</a>-&gt;syn + <a href="ident?i=th">th</a>-&gt;fin +
<a name="L1586" href="source/net/ipv4/tcp_ipv4.c#L1586">1586</a>                                     <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a> - <a href="ident?i=th">th</a>-&gt;doff * 4);
<a name="L1587" href="source/net/ipv4/tcp_ipv4.c#L1587">1587</a>         <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;ack_seq = <a href="ident?i=ntohl">ntohl</a>(<a href="ident?i=th">th</a>-&gt;ack_seq);
<a name="L1588" href="source/net/ipv4/tcp_ipv4.c#L1588">1588</a>         <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;tcp_flags = <a href="ident?i=tcp_flag_byte">tcp_flag_byte</a>(<a href="ident?i=th">th</a>);
<a name="L1589" href="source/net/ipv4/tcp_ipv4.c#L1589">1589</a>         <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;tcp_tw_isn = 0;
<a name="L1590" href="source/net/ipv4/tcp_ipv4.c#L1590">1590</a>         <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;ip_dsfield = <a href="ident?i=ipv4_get_dsfield">ipv4_get_dsfield</a>(iph);
<a name="L1591" href="source/net/ipv4/tcp_ipv4.c#L1591">1591</a>         <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;sacked  = 0;
<a name="L1592" href="source/net/ipv4/tcp_ipv4.c#L1592">1592</a> 
<a name="L1593" href="source/net/ipv4/tcp_ipv4.c#L1593">1593</a>         sk = <a href="ident?i=__inet_lookup_skb">__inet_lookup_skb</a>(&amp;<a href="ident?i=tcp_hashinfo">tcp_hashinfo</a>, <a href="ident?i=skb">skb</a>, <a href="ident?i=th">th</a>-&gt;source, <a href="ident?i=th">th</a>-&gt;<a href="ident?i=dest">dest</a>);
<a name="L1594" href="source/net/ipv4/tcp_ipv4.c#L1594">1594</a>         if (!sk)
<a name="L1595" href="source/net/ipv4/tcp_ipv4.c#L1595">1595</a>                 goto no_tcp_socket;
<a name="L1596" href="source/net/ipv4/tcp_ipv4.c#L1596">1596</a> 
<a name="L1597" href="source/net/ipv4/tcp_ipv4.c#L1597">1597</a> <a href="ident?i=process">process</a>:
<a name="L1598" href="source/net/ipv4/tcp_ipv4.c#L1598">1598</a>         if (sk-&gt;<a href="ident?i=sk_state">sk_state</a> == TCP_TIME_WAIT)
<a name="L1599" href="source/net/ipv4/tcp_ipv4.c#L1599">1599</a>                 goto do_time_wait;
<a name="L1600" href="source/net/ipv4/tcp_ipv4.c#L1600">1600</a> 
<a name="L1601" href="source/net/ipv4/tcp_ipv4.c#L1601">1601</a>         if (<a href="ident?i=unlikely">unlikely</a>(iph-&gt;<a href="ident?i=ttl">ttl</a> &lt; <a href="ident?i=inet_sk">inet_sk</a>(sk)-&gt;<a href="ident?i=min_ttl">min_ttl</a>)) {
<a name="L1602" href="source/net/ipv4/tcp_ipv4.c#L1602">1602</a>                 <a href="ident?i=NET_INC_STATS_BH">NET_INC_STATS_BH</a>(<a href="ident?i=net">net</a>, LINUX_MIB_TCPMINTTLDROP);
<a name="L1603" href="source/net/ipv4/tcp_ipv4.c#L1603">1603</a>                 goto discard_and_relse;
<a name="L1604" href="source/net/ipv4/tcp_ipv4.c#L1604">1604</a>         }
<a name="L1605" href="source/net/ipv4/tcp_ipv4.c#L1605">1605</a> 
<a name="L1606" href="source/net/ipv4/tcp_ipv4.c#L1606">1606</a>         if (!<a href="ident?i=xfrm4_policy_check">xfrm4_policy_check</a>(sk, XFRM_POLICY_IN, <a href="ident?i=skb">skb</a>))
<a name="L1607" href="source/net/ipv4/tcp_ipv4.c#L1607">1607</a>                 goto discard_and_relse;
<a name="L1608" href="source/net/ipv4/tcp_ipv4.c#L1608">1608</a> 
<a name="L1609" href="source/net/ipv4/tcp_ipv4.c#L1609">1609</a> #ifdef CONFIG_TCP_MD5SIG
<a name="L1610" href="source/net/ipv4/tcp_ipv4.c#L1610">1610</a>         <b><i>/*</i></b>
<a name="L1611" href="source/net/ipv4/tcp_ipv4.c#L1611">1611</a> <b><i>         * We really want to reject the packet as early as possible</i></b>
<a name="L1612" href="source/net/ipv4/tcp_ipv4.c#L1612">1612</a> <b><i>         * if:</i></b>
<a name="L1613" href="source/net/ipv4/tcp_ipv4.c#L1613">1613</a> <b><i>         *  o We're expecting an MD5'd packet and this is no MD5 tcp option</i></b>
<a name="L1614" href="source/net/ipv4/tcp_ipv4.c#L1614">1614</a> <b><i>         *  o There is an MD5 option and we're not expecting one</i></b>
<a name="L1615" href="source/net/ipv4/tcp_ipv4.c#L1615">1615</a> <b><i>         */</i></b>
<a name="L1616" href="source/net/ipv4/tcp_ipv4.c#L1616">1616</a>         if (<a href="ident?i=tcp_v4_inbound_md5_hash">tcp_v4_inbound_md5_hash</a>(sk, <a href="ident?i=skb">skb</a>))
<a name="L1617" href="source/net/ipv4/tcp_ipv4.c#L1617">1617</a>                 goto discard_and_relse;
<a name="L1618" href="source/net/ipv4/tcp_ipv4.c#L1618">1618</a> #endif
<a name="L1619" href="source/net/ipv4/tcp_ipv4.c#L1619">1619</a> 
<a name="L1620" href="source/net/ipv4/tcp_ipv4.c#L1620">1620</a>         <a href="ident?i=nf_reset">nf_reset</a>(<a href="ident?i=skb">skb</a>);
<a name="L1621" href="source/net/ipv4/tcp_ipv4.c#L1621">1621</a> 
<a name="L1622" href="source/net/ipv4/tcp_ipv4.c#L1622">1622</a>         if (<a href="ident?i=sk_filter">sk_filter</a>(sk, <a href="ident?i=skb">skb</a>))
<a name="L1623" href="source/net/ipv4/tcp_ipv4.c#L1623">1623</a>                 goto discard_and_relse;
<a name="L1624" href="source/net/ipv4/tcp_ipv4.c#L1624">1624</a> 
<a name="L1625" href="source/net/ipv4/tcp_ipv4.c#L1625">1625</a>         <a href="ident?i=sk_incoming_cpu_update">sk_incoming_cpu_update</a>(sk);
<a name="L1626" href="source/net/ipv4/tcp_ipv4.c#L1626">1626</a>         <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=dev">dev</a> = <a href="ident?i=NULL">NULL</a>;
<a name="L1627" href="source/net/ipv4/tcp_ipv4.c#L1627">1627</a> 
<a name="L1628" href="source/net/ipv4/tcp_ipv4.c#L1628">1628</a>         <a href="ident?i=bh_lock_sock_nested">bh_lock_sock_nested</a>(sk);
<a name="L1629" href="source/net/ipv4/tcp_ipv4.c#L1629">1629</a>         <a href="ident?i=ret">ret</a> = 0;
<a name="L1630" href="source/net/ipv4/tcp_ipv4.c#L1630">1630</a>         if (!<a href="ident?i=sock_owned_by_user">sock_owned_by_user</a>(sk)) {
<a name="L1631" href="source/net/ipv4/tcp_ipv4.c#L1631">1631</a>                 if (!<a href="ident?i=tcp_prequeue">tcp_prequeue</a>(sk, <a href="ident?i=skb">skb</a>))
<a name="L1632" href="source/net/ipv4/tcp_ipv4.c#L1632">1632</a>                         <a href="ident?i=ret">ret</a> = <a href="ident?i=tcp_v4_do_rcv">tcp_v4_do_rcv</a>(sk, <a href="ident?i=skb">skb</a>);
<a name="L1633" href="source/net/ipv4/tcp_ipv4.c#L1633">1633</a>         } else if (<a href="ident?i=unlikely">unlikely</a>(<a href="ident?i=sk_add_backlog">sk_add_backlog</a>(sk, <a href="ident?i=skb">skb</a>,
<a name="L1634" href="source/net/ipv4/tcp_ipv4.c#L1634">1634</a>                                            sk-&gt;sk_rcvbuf + sk-&gt;sk_sndbuf))) {
<a name="L1635" href="source/net/ipv4/tcp_ipv4.c#L1635">1635</a>                 <a href="ident?i=bh_unlock_sock">bh_unlock_sock</a>(sk);
<a name="L1636" href="source/net/ipv4/tcp_ipv4.c#L1636">1636</a>                 <a href="ident?i=NET_INC_STATS_BH">NET_INC_STATS_BH</a>(<a href="ident?i=net">net</a>, LINUX_MIB_TCPBACKLOGDROP);
<a name="L1637" href="source/net/ipv4/tcp_ipv4.c#L1637">1637</a>                 goto discard_and_relse;
<a name="L1638" href="source/net/ipv4/tcp_ipv4.c#L1638">1638</a>         }
<a name="L1639" href="source/net/ipv4/tcp_ipv4.c#L1639">1639</a>         <a href="ident?i=bh_unlock_sock">bh_unlock_sock</a>(sk);
<a name="L1640" href="source/net/ipv4/tcp_ipv4.c#L1640">1640</a> 
<a name="L1641" href="source/net/ipv4/tcp_ipv4.c#L1641">1641</a>         <a href="ident?i=sock_put">sock_put</a>(sk);
<a name="L1642" href="source/net/ipv4/tcp_ipv4.c#L1642">1642</a> 
<a name="L1643" href="source/net/ipv4/tcp_ipv4.c#L1643">1643</a>         return <a href="ident?i=ret">ret</a>;
<a name="L1644" href="source/net/ipv4/tcp_ipv4.c#L1644">1644</a> 
<a name="L1645" href="source/net/ipv4/tcp_ipv4.c#L1645">1645</a> no_tcp_socket:
<a name="L1646" href="source/net/ipv4/tcp_ipv4.c#L1646">1646</a>         if (!<a href="ident?i=xfrm4_policy_check">xfrm4_policy_check</a>(<a href="ident?i=NULL">NULL</a>, XFRM_POLICY_IN, <a href="ident?i=skb">skb</a>))
<a name="L1647" href="source/net/ipv4/tcp_ipv4.c#L1647">1647</a>                 goto discard_it;
<a name="L1648" href="source/net/ipv4/tcp_ipv4.c#L1648">1648</a> 
<a name="L1649" href="source/net/ipv4/tcp_ipv4.c#L1649">1649</a>         if (<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a> &lt; (<a href="ident?i=th">th</a>-&gt;doff &lt;&lt; 2) || <a href="ident?i=tcp_checksum_complete">tcp_checksum_complete</a>(<a href="ident?i=skb">skb</a>)) {
<a name="L1650" href="source/net/ipv4/tcp_ipv4.c#L1650">1650</a> csum_error:
<a name="L1651" href="source/net/ipv4/tcp_ipv4.c#L1651">1651</a>                 <a href="ident?i=TCP_INC_STATS_BH">TCP_INC_STATS_BH</a>(<a href="ident?i=net">net</a>, TCP_MIB_CSUMERRORS);
<a name="L1652" href="source/net/ipv4/tcp_ipv4.c#L1652">1652</a> bad_packet:
<a name="L1653" href="source/net/ipv4/tcp_ipv4.c#L1653">1653</a>                 <a href="ident?i=TCP_INC_STATS_BH">TCP_INC_STATS_BH</a>(<a href="ident?i=net">net</a>, TCP_MIB_INERRS);
<a name="L1654" href="source/net/ipv4/tcp_ipv4.c#L1654">1654</a>         } else {
<a name="L1655" href="source/net/ipv4/tcp_ipv4.c#L1655">1655</a>                 <a href="ident?i=tcp_v4_send_reset">tcp_v4_send_reset</a>(<a href="ident?i=NULL">NULL</a>, <a href="ident?i=skb">skb</a>);
<a name="L1656" href="source/net/ipv4/tcp_ipv4.c#L1656">1656</a>         }
<a name="L1657" href="source/net/ipv4/tcp_ipv4.c#L1657">1657</a> 
<a name="L1658" href="source/net/ipv4/tcp_ipv4.c#L1658">1658</a> discard_it:
<a name="L1659" href="source/net/ipv4/tcp_ipv4.c#L1659">1659</a>         <b><i>/* Discard frame. */</i></b>
<a name="L1660" href="source/net/ipv4/tcp_ipv4.c#L1660">1660</a>         <a href="ident?i=kfree_skb">kfree_skb</a>(<a href="ident?i=skb">skb</a>);
<a name="L1661" href="source/net/ipv4/tcp_ipv4.c#L1661">1661</a>         return 0;
<a name="L1662" href="source/net/ipv4/tcp_ipv4.c#L1662">1662</a> 
<a name="L1663" href="source/net/ipv4/tcp_ipv4.c#L1663">1663</a> discard_and_relse:
<a name="L1664" href="source/net/ipv4/tcp_ipv4.c#L1664">1664</a>         <a href="ident?i=sock_put">sock_put</a>(sk);
<a name="L1665" href="source/net/ipv4/tcp_ipv4.c#L1665">1665</a>         goto discard_it;
<a name="L1666" href="source/net/ipv4/tcp_ipv4.c#L1666">1666</a> 
<a name="L1667" href="source/net/ipv4/tcp_ipv4.c#L1667">1667</a> do_time_wait:
<a name="L1668" href="source/net/ipv4/tcp_ipv4.c#L1668">1668</a>         if (!<a href="ident?i=xfrm4_policy_check">xfrm4_policy_check</a>(<a href="ident?i=NULL">NULL</a>, XFRM_POLICY_IN, <a href="ident?i=skb">skb</a>)) {
<a name="L1669" href="source/net/ipv4/tcp_ipv4.c#L1669">1669</a>                 <a href="ident?i=inet_twsk_put">inet_twsk_put</a>(<a href="ident?i=inet_twsk">inet_twsk</a>(sk));
<a name="L1670" href="source/net/ipv4/tcp_ipv4.c#L1670">1670</a>                 goto discard_it;
<a name="L1671" href="source/net/ipv4/tcp_ipv4.c#L1671">1671</a>         }
<a name="L1672" href="source/net/ipv4/tcp_ipv4.c#L1672">1672</a> 
<a name="L1673" href="source/net/ipv4/tcp_ipv4.c#L1673">1673</a>         if (<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a> &lt; (<a href="ident?i=th">th</a>-&gt;doff &lt;&lt; 2)) {
<a name="L1674" href="source/net/ipv4/tcp_ipv4.c#L1674">1674</a>                 <a href="ident?i=inet_twsk_put">inet_twsk_put</a>(<a href="ident?i=inet_twsk">inet_twsk</a>(sk));
<a name="L1675" href="source/net/ipv4/tcp_ipv4.c#L1675">1675</a>                 goto bad_packet;
<a name="L1676" href="source/net/ipv4/tcp_ipv4.c#L1676">1676</a>         }
<a name="L1677" href="source/net/ipv4/tcp_ipv4.c#L1677">1677</a>         if (<a href="ident?i=tcp_checksum_complete">tcp_checksum_complete</a>(<a href="ident?i=skb">skb</a>)) {
<a name="L1678" href="source/net/ipv4/tcp_ipv4.c#L1678">1678</a>                 <a href="ident?i=inet_twsk_put">inet_twsk_put</a>(<a href="ident?i=inet_twsk">inet_twsk</a>(sk));
<a name="L1679" href="source/net/ipv4/tcp_ipv4.c#L1679">1679</a>                 goto csum_error;
<a name="L1680" href="source/net/ipv4/tcp_ipv4.c#L1680">1680</a>         }
<a name="L1681" href="source/net/ipv4/tcp_ipv4.c#L1681">1681</a>         switch (<a href="ident?i=tcp_timewait_state_process">tcp_timewait_state_process</a>(<a href="ident?i=inet_twsk">inet_twsk</a>(sk), <a href="ident?i=skb">skb</a>, <a href="ident?i=th">th</a>)) {
<a name="L1682" href="source/net/ipv4/tcp_ipv4.c#L1682">1682</a>         case TCP_TW_SYN: {
<a name="L1683" href="source/net/ipv4/tcp_ipv4.c#L1683">1683</a>                 struct <a href="ident?i=sock">sock</a> *sk2 = <a href="ident?i=inet_lookup_listener">inet_lookup_listener</a>(<a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=dev">dev</a>),
<a name="L1684" href="source/net/ipv4/tcp_ipv4.c#L1684">1684</a>                                                         &amp;<a href="ident?i=tcp_hashinfo">tcp_hashinfo</a>,
<a name="L1685" href="source/net/ipv4/tcp_ipv4.c#L1685">1685</a>                                                         iph-&gt;<a href="ident?i=saddr">saddr</a>, <a href="ident?i=th">th</a>-&gt;source,
<a name="L1686" href="source/net/ipv4/tcp_ipv4.c#L1686">1686</a>                                                         iph-&gt;<a href="ident?i=daddr">daddr</a>, <a href="ident?i=th">th</a>-&gt;<a href="ident?i=dest">dest</a>,
<a name="L1687" href="source/net/ipv4/tcp_ipv4.c#L1687">1687</a>                                                         <a href="ident?i=inet_iif">inet_iif</a>(<a href="ident?i=skb">skb</a>));
<a name="L1688" href="source/net/ipv4/tcp_ipv4.c#L1688">1688</a>                 if (sk2) {
<a name="L1689" href="source/net/ipv4/tcp_ipv4.c#L1689">1689</a>                         <a href="ident?i=inet_twsk_deschedule">inet_twsk_deschedule</a>(<a href="ident?i=inet_twsk">inet_twsk</a>(sk));
<a name="L1690" href="source/net/ipv4/tcp_ipv4.c#L1690">1690</a>                         <a href="ident?i=inet_twsk_put">inet_twsk_put</a>(<a href="ident?i=inet_twsk">inet_twsk</a>(sk));
<a name="L1691" href="source/net/ipv4/tcp_ipv4.c#L1691">1691</a>                         sk = sk2;
<a name="L1692" href="source/net/ipv4/tcp_ipv4.c#L1692">1692</a>                         goto <a href="ident?i=process">process</a>;
<a name="L1693" href="source/net/ipv4/tcp_ipv4.c#L1693">1693</a>                 }
<a name="L1694" href="source/net/ipv4/tcp_ipv4.c#L1694">1694</a>                 <b><i>/* Fall through to ACK */</i></b>
<a name="L1695" href="source/net/ipv4/tcp_ipv4.c#L1695">1695</a>         }
<a name="L1696" href="source/net/ipv4/tcp_ipv4.c#L1696">1696</a>         case TCP_TW_ACK:
<a name="L1697" href="source/net/ipv4/tcp_ipv4.c#L1697">1697</a>                 <a href="ident?i=tcp_v4_timewait_ack">tcp_v4_timewait_ack</a>(sk, <a href="ident?i=skb">skb</a>);
<a name="L1698" href="source/net/ipv4/tcp_ipv4.c#L1698">1698</a>                 break;
<a name="L1699" href="source/net/ipv4/tcp_ipv4.c#L1699">1699</a>         case TCP_TW_RST:
<a name="L1700" href="source/net/ipv4/tcp_ipv4.c#L1700">1700</a>                 goto no_tcp_socket;
<a name="L1701" href="source/net/ipv4/tcp_ipv4.c#L1701">1701</a>         case TCP_TW_SUCCESS:;
<a name="L1702" href="source/net/ipv4/tcp_ipv4.c#L1702">1702</a>         }
<a name="L1703" href="source/net/ipv4/tcp_ipv4.c#L1703">1703</a>         goto discard_it;
<a name="L1704" href="source/net/ipv4/tcp_ipv4.c#L1704">1704</a> }
<a name="L1705" href="source/net/ipv4/tcp_ipv4.c#L1705">1705</a> 
<a name="L1706" href="source/net/ipv4/tcp_ipv4.c#L1706">1706</a> static struct <a href="ident?i=timewait_sock_ops">timewait_sock_ops</a> <a href="ident?i=tcp_timewait_sock_ops">tcp_timewait_sock_ops</a> = {
<a name="L1707" href="source/net/ipv4/tcp_ipv4.c#L1707">1707</a>         .twsk_obj_size  = sizeof(struct <a href="ident?i=tcp_timewait_sock">tcp_timewait_sock</a>),
<a name="L1708" href="source/net/ipv4/tcp_ipv4.c#L1708">1708</a>         .<a href="ident?i=twsk_unique">twsk_unique</a>    = <a href="ident?i=tcp_twsk_unique">tcp_twsk_unique</a>,
<a name="L1709" href="source/net/ipv4/tcp_ipv4.c#L1709">1709</a>         .<a href="ident?i=twsk_destructor">twsk_destructor</a>= <a href="ident?i=tcp_twsk_destructor">tcp_twsk_destructor</a>,
<a name="L1710" href="source/net/ipv4/tcp_ipv4.c#L1710">1710</a> };
<a name="L1711" href="source/net/ipv4/tcp_ipv4.c#L1711">1711</a> 
<a name="L1712" href="source/net/ipv4/tcp_ipv4.c#L1712">1712</a> void <a href="ident?i=inet_sk_rx_dst_set">inet_sk_rx_dst_set</a>(struct <a href="ident?i=sock">sock</a> *sk, const struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L1713" href="source/net/ipv4/tcp_ipv4.c#L1713">1713</a> {
<a name="L1714" href="source/net/ipv4/tcp_ipv4.c#L1714">1714</a>         struct <a href="ident?i=dst_entry">dst_entry</a> *<a href="ident?i=dst">dst</a> = <a href="ident?i=skb_dst">skb_dst</a>(<a href="ident?i=skb">skb</a>);
<a name="L1715" href="source/net/ipv4/tcp_ipv4.c#L1715">1715</a> 
<a name="L1716" href="source/net/ipv4/tcp_ipv4.c#L1716">1716</a>         if (<a href="ident?i=dst">dst</a>) {
<a name="L1717" href="source/net/ipv4/tcp_ipv4.c#L1717">1717</a>                 <a href="ident?i=dst_hold">dst_hold</a>(<a href="ident?i=dst">dst</a>);
<a name="L1718" href="source/net/ipv4/tcp_ipv4.c#L1718">1718</a>                 sk-&gt;sk_rx_dst = <a href="ident?i=dst">dst</a>;
<a name="L1719" href="source/net/ipv4/tcp_ipv4.c#L1719">1719</a>                 <a href="ident?i=inet_sk">inet_sk</a>(sk)-&gt;rx_dst_ifindex = <a href="ident?i=skb">skb</a>-&gt;skb_iif;
<a name="L1720" href="source/net/ipv4/tcp_ipv4.c#L1720">1720</a>         }
<a name="L1721" href="source/net/ipv4/tcp_ipv4.c#L1721">1721</a> }
<a name="L1722" href="source/net/ipv4/tcp_ipv4.c#L1722">1722</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=inet_sk_rx_dst_set">inet_sk_rx_dst_set</a>);
<a name="L1723" href="source/net/ipv4/tcp_ipv4.c#L1723">1723</a> 
<a name="L1724" href="source/net/ipv4/tcp_ipv4.c#L1724">1724</a> const struct <a href="ident?i=inet_connection_sock_af_ops">inet_connection_sock_af_ops</a> <a href="ident?i=ipv4_specific">ipv4_specific</a> = {
<a name="L1725" href="source/net/ipv4/tcp_ipv4.c#L1725">1725</a>         .queue_xmit        = <a href="ident?i=ip_queue_xmit">ip_queue_xmit</a>,
<a name="L1726" href="source/net/ipv4/tcp_ipv4.c#L1726">1726</a>         .send_check        = <a href="ident?i=tcp_v4_send_check">tcp_v4_send_check</a>,
<a name="L1727" href="source/net/ipv4/tcp_ipv4.c#L1727">1727</a>         .rebuild_header    = <a href="ident?i=inet_sk_rebuild_header">inet_sk_rebuild_header</a>,
<a name="L1728" href="source/net/ipv4/tcp_ipv4.c#L1728">1728</a>         .sk_rx_dst_set     = <a href="ident?i=inet_sk_rx_dst_set">inet_sk_rx_dst_set</a>,
<a name="L1729" href="source/net/ipv4/tcp_ipv4.c#L1729">1729</a>         .conn_request      = <a href="ident?i=tcp_v4_conn_request">tcp_v4_conn_request</a>,
<a name="L1730" href="source/net/ipv4/tcp_ipv4.c#L1730">1730</a>         .syn_recv_sock     = <a href="ident?i=tcp_v4_syn_recv_sock">tcp_v4_syn_recv_sock</a>,
<a name="L1731" href="source/net/ipv4/tcp_ipv4.c#L1731">1731</a>         .net_header_len    = sizeof(struct <a href="ident?i=iphdr">iphdr</a>),
<a name="L1732" href="source/net/ipv4/tcp_ipv4.c#L1732">1732</a>         .<a href="ident?i=setsockopt">setsockopt</a>        = <a href="ident?i=ip_setsockopt">ip_setsockopt</a>,
<a name="L1733" href="source/net/ipv4/tcp_ipv4.c#L1733">1733</a>         .getsockopt        = <a href="ident?i=ip_getsockopt">ip_getsockopt</a>,
<a name="L1734" href="source/net/ipv4/tcp_ipv4.c#L1734">1734</a>         .addr2sockaddr     = <a href="ident?i=inet_csk_addr2sockaddr">inet_csk_addr2sockaddr</a>,
<a name="L1735" href="source/net/ipv4/tcp_ipv4.c#L1735">1735</a>         .sockaddr_len      = sizeof(struct <a href="ident?i=sockaddr_in">sockaddr_in</a>),
<a name="L1736" href="source/net/ipv4/tcp_ipv4.c#L1736">1736</a>         .bind_conflict     = <a href="ident?i=inet_csk_bind_conflict">inet_csk_bind_conflict</a>,
<a name="L1737" href="source/net/ipv4/tcp_ipv4.c#L1737">1737</a> #ifdef CONFIG_COMPAT
<a name="L1738" href="source/net/ipv4/tcp_ipv4.c#L1738">1738</a>         .compat_setsockopt = <a href="ident?i=compat_ip_setsockopt">compat_ip_setsockopt</a>,
<a name="L1739" href="source/net/ipv4/tcp_ipv4.c#L1739">1739</a>         .compat_getsockopt = <a href="ident?i=compat_ip_getsockopt">compat_ip_getsockopt</a>,
<a name="L1740" href="source/net/ipv4/tcp_ipv4.c#L1740">1740</a> #endif
<a name="L1741" href="source/net/ipv4/tcp_ipv4.c#L1741">1741</a>         .mtu_reduced       = <a href="ident?i=tcp_v4_mtu_reduced">tcp_v4_mtu_reduced</a>,
<a name="L1742" href="source/net/ipv4/tcp_ipv4.c#L1742">1742</a> };
<a name="L1743" href="source/net/ipv4/tcp_ipv4.c#L1743">1743</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=ipv4_specific">ipv4_specific</a>);
<a name="L1744" href="source/net/ipv4/tcp_ipv4.c#L1744">1744</a> 
<a name="L1745" href="source/net/ipv4/tcp_ipv4.c#L1745">1745</a> #ifdef CONFIG_TCP_MD5SIG
<a name="L1746" href="source/net/ipv4/tcp_ipv4.c#L1746">1746</a> static const struct <a href="ident?i=tcp_sock_af_ops">tcp_sock_af_ops</a> <a href="ident?i=tcp_sock_ipv4_specific">tcp_sock_ipv4_specific</a> = {
<a name="L1747" href="source/net/ipv4/tcp_ipv4.c#L1747">1747</a>         .md5_lookup             = <a href="ident?i=tcp_v4_md5_lookup">tcp_v4_md5_lookup</a>,
<a name="L1748" href="source/net/ipv4/tcp_ipv4.c#L1748">1748</a>         .calc_md5_hash          = <a href="ident?i=tcp_v4_md5_hash_skb">tcp_v4_md5_hash_skb</a>,
<a name="L1749" href="source/net/ipv4/tcp_ipv4.c#L1749">1749</a>         .md5_parse              = <a href="ident?i=tcp_v4_parse_md5_keys">tcp_v4_parse_md5_keys</a>,
<a name="L1750" href="source/net/ipv4/tcp_ipv4.c#L1750">1750</a> };
<a name="L1751" href="source/net/ipv4/tcp_ipv4.c#L1751">1751</a> #endif
<a name="L1752" href="source/net/ipv4/tcp_ipv4.c#L1752">1752</a> 
<a name="L1753" href="source/net/ipv4/tcp_ipv4.c#L1753">1753</a> <b><i>/* NOTE: A lot of things set to zero explicitly by call to</i></b>
<a name="L1754" href="source/net/ipv4/tcp_ipv4.c#L1754">1754</a> <b><i> *       sk_alloc() so need not be done here.</i></b>
<a name="L1755" href="source/net/ipv4/tcp_ipv4.c#L1755">1755</a> <b><i> */</i></b>
<a name="L1756" href="source/net/ipv4/tcp_ipv4.c#L1756">1756</a> static int <a href="ident?i=tcp_v4_init_sock">tcp_v4_init_sock</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L1757" href="source/net/ipv4/tcp_ipv4.c#L1757">1757</a> {
<a name="L1758" href="source/net/ipv4/tcp_ipv4.c#L1758">1758</a>         struct <a href="ident?i=inet_connection_sock">inet_connection_sock</a> *icsk = <a href="ident?i=inet_csk">inet_csk</a>(sk);
<a name="L1759" href="source/net/ipv4/tcp_ipv4.c#L1759">1759</a> 
<a name="L1760" href="source/net/ipv4/tcp_ipv4.c#L1760">1760</a>         <a href="ident?i=tcp_init_sock">tcp_init_sock</a>(sk);
<a name="L1761" href="source/net/ipv4/tcp_ipv4.c#L1761">1761</a> 
<a name="L1762" href="source/net/ipv4/tcp_ipv4.c#L1762">1762</a>         icsk-&gt;icsk_af_ops = &amp;<a href="ident?i=ipv4_specific">ipv4_specific</a>;
<a name="L1763" href="source/net/ipv4/tcp_ipv4.c#L1763">1763</a> 
<a name="L1764" href="source/net/ipv4/tcp_ipv4.c#L1764">1764</a> #ifdef CONFIG_TCP_MD5SIG
<a name="L1765" href="source/net/ipv4/tcp_ipv4.c#L1765">1765</a>         <a href="ident?i=tcp_sk">tcp_sk</a>(sk)-&gt;af_specific = &amp;<a href="ident?i=tcp_sock_ipv4_specific">tcp_sock_ipv4_specific</a>;
<a name="L1766" href="source/net/ipv4/tcp_ipv4.c#L1766">1766</a> #endif
<a name="L1767" href="source/net/ipv4/tcp_ipv4.c#L1767">1767</a> 
<a name="L1768" href="source/net/ipv4/tcp_ipv4.c#L1768">1768</a>         return 0;
<a name="L1769" href="source/net/ipv4/tcp_ipv4.c#L1769">1769</a> }
<a name="L1770" href="source/net/ipv4/tcp_ipv4.c#L1770">1770</a> 
<a name="L1771" href="source/net/ipv4/tcp_ipv4.c#L1771">1771</a> void <a href="ident?i=tcp_v4_destroy_sock">tcp_v4_destroy_sock</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L1772" href="source/net/ipv4/tcp_ipv4.c#L1772">1772</a> {
<a name="L1773" href="source/net/ipv4/tcp_ipv4.c#L1773">1773</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L1774" href="source/net/ipv4/tcp_ipv4.c#L1774">1774</a> 
<a name="L1775" href="source/net/ipv4/tcp_ipv4.c#L1775">1775</a>         <a href="ident?i=tcp_clear_xmit_timers">tcp_clear_xmit_timers</a>(sk);
<a name="L1776" href="source/net/ipv4/tcp_ipv4.c#L1776">1776</a> 
<a name="L1777" href="source/net/ipv4/tcp_ipv4.c#L1777">1777</a>         <a href="ident?i=tcp_cleanup_congestion_control">tcp_cleanup_congestion_control</a>(sk);
<a name="L1778" href="source/net/ipv4/tcp_ipv4.c#L1778">1778</a> 
<a name="L1779" href="source/net/ipv4/tcp_ipv4.c#L1779">1779</a>         <b><i>/* Cleanup up the write buffer. */</i></b>
<a name="L1780" href="source/net/ipv4/tcp_ipv4.c#L1780">1780</a>         <a href="ident?i=tcp_write_queue_purge">tcp_write_queue_purge</a>(sk);
<a name="L1781" href="source/net/ipv4/tcp_ipv4.c#L1781">1781</a> 
<a name="L1782" href="source/net/ipv4/tcp_ipv4.c#L1782">1782</a>         <b><i>/* Cleans up our, hopefully empty, out_of_order_queue. */</i></b>
<a name="L1783" href="source/net/ipv4/tcp_ipv4.c#L1783">1783</a>         <a href="ident?i=__skb_queue_purge">__skb_queue_purge</a>(&amp;<a href="ident?i=tp">tp</a>-&gt;out_of_order_queue);
<a name="L1784" href="source/net/ipv4/tcp_ipv4.c#L1784">1784</a> 
<a name="L1785" href="source/net/ipv4/tcp_ipv4.c#L1785">1785</a> #ifdef CONFIG_TCP_MD5SIG
<a name="L1786" href="source/net/ipv4/tcp_ipv4.c#L1786">1786</a>         <b><i>/* Clean up the MD5 key list, if any */</i></b>
<a name="L1787" href="source/net/ipv4/tcp_ipv4.c#L1787">1787</a>         if (<a href="ident?i=tp">tp</a>-&gt;md5sig_info) {
<a name="L1788" href="source/net/ipv4/tcp_ipv4.c#L1788">1788</a>                 <a href="ident?i=tcp_clear_md5_list">tcp_clear_md5_list</a>(sk);
<a name="L1789" href="source/net/ipv4/tcp_ipv4.c#L1789">1789</a>                 <a href="ident?i=kfree_rcu">kfree_rcu</a>(<a href="ident?i=tp">tp</a>-&gt;md5sig_info, rcu);
<a name="L1790" href="source/net/ipv4/tcp_ipv4.c#L1790">1790</a>                 <a href="ident?i=tp">tp</a>-&gt;md5sig_info = <a href="ident?i=NULL">NULL</a>;
<a name="L1791" href="source/net/ipv4/tcp_ipv4.c#L1791">1791</a>         }
<a name="L1792" href="source/net/ipv4/tcp_ipv4.c#L1792">1792</a> #endif
<a name="L1793" href="source/net/ipv4/tcp_ipv4.c#L1793">1793</a> 
<a name="L1794" href="source/net/ipv4/tcp_ipv4.c#L1794">1794</a>         <b><i>/* Clean prequeue, it must be empty really */</i></b>
<a name="L1795" href="source/net/ipv4/tcp_ipv4.c#L1795">1795</a>         <a href="ident?i=__skb_queue_purge">__skb_queue_purge</a>(&amp;<a href="ident?i=tp">tp</a>-&gt;ucopy.prequeue);
<a name="L1796" href="source/net/ipv4/tcp_ipv4.c#L1796">1796</a> 
<a name="L1797" href="source/net/ipv4/tcp_ipv4.c#L1797">1797</a>         <b><i>/* Clean up a referenced TCP bind bucket. */</i></b>
<a name="L1798" href="source/net/ipv4/tcp_ipv4.c#L1798">1798</a>         if (<a href="ident?i=inet_csk">inet_csk</a>(sk)-&gt;icsk_bind_hash)
<a name="L1799" href="source/net/ipv4/tcp_ipv4.c#L1799">1799</a>                 <a href="ident?i=inet_put_port">inet_put_port</a>(sk);
<a name="L1800" href="source/net/ipv4/tcp_ipv4.c#L1800">1800</a> 
<a name="L1801" href="source/net/ipv4/tcp_ipv4.c#L1801">1801</a>         <a href="ident?i=BUG_ON">BUG_ON</a>(<a href="ident?i=tp">tp</a>-&gt;fastopen_rsk);
<a name="L1802" href="source/net/ipv4/tcp_ipv4.c#L1802">1802</a> 
<a name="L1803" href="source/net/ipv4/tcp_ipv4.c#L1803">1803</a>         <b><i>/* If socket is aborted during connect operation */</i></b>
<a name="L1804" href="source/net/ipv4/tcp_ipv4.c#L1804">1804</a>         <a href="ident?i=tcp_free_fastopen_req">tcp_free_fastopen_req</a>(<a href="ident?i=tp">tp</a>);
<a name="L1805" href="source/net/ipv4/tcp_ipv4.c#L1805">1805</a> 
<a name="L1806" href="source/net/ipv4/tcp_ipv4.c#L1806">1806</a>         <a href="ident?i=sk_sockets_allocated_dec">sk_sockets_allocated_dec</a>(sk);
<a name="L1807" href="source/net/ipv4/tcp_ipv4.c#L1807">1807</a>         <a href="ident?i=sock_release_memcg">sock_release_memcg</a>(sk);
<a name="L1808" href="source/net/ipv4/tcp_ipv4.c#L1808">1808</a> }
<a name="L1809" href="source/net/ipv4/tcp_ipv4.c#L1809">1809</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=tcp_v4_destroy_sock">tcp_v4_destroy_sock</a>);
<a name="L1810" href="source/net/ipv4/tcp_ipv4.c#L1810">1810</a> 
<a name="L1811" href="source/net/ipv4/tcp_ipv4.c#L1811">1811</a> #ifdef CONFIG_PROC_FS
<a name="L1812" href="source/net/ipv4/tcp_ipv4.c#L1812">1812</a> <b><i>/* Proc filesystem TCP sock list dumping. */</i></b>
<a name="L1813" href="source/net/ipv4/tcp_ipv4.c#L1813">1813</a> 
<a name="L1814" href="source/net/ipv4/tcp_ipv4.c#L1814">1814</a> <b><i>/*</i></b>
<a name="L1815" href="source/net/ipv4/tcp_ipv4.c#L1815">1815</a> <b><i> * Get next listener socket follow cur.  If cur is NULL, get first socket</i></b>
<a name="L1816" href="source/net/ipv4/tcp_ipv4.c#L1816">1816</a> <b><i> * starting from bucket given in st-&gt;bucket; when st-&gt;bucket is zero the</i></b>
<a name="L1817" href="source/net/ipv4/tcp_ipv4.c#L1817">1817</a> <b><i> * very first socket in the hash table is returned.</i></b>
<a name="L1818" href="source/net/ipv4/tcp_ipv4.c#L1818">1818</a> <b><i> */</i></b>
<a name="L1819" href="source/net/ipv4/tcp_ipv4.c#L1819">1819</a> static void *<a href="ident?i=listening_get_next">listening_get_next</a>(struct <a href="ident?i=seq_file">seq_file</a> *<a href="ident?i=seq">seq</a>, void *cur)
<a name="L1820" href="source/net/ipv4/tcp_ipv4.c#L1820">1820</a> {
<a name="L1821" href="source/net/ipv4/tcp_ipv4.c#L1821">1821</a>         struct <a href="ident?i=inet_connection_sock">inet_connection_sock</a> *icsk;
<a name="L1822" href="source/net/ipv4/tcp_ipv4.c#L1822">1822</a>         struct <a href="ident?i=hlist_nulls_node">hlist_nulls_node</a> *<a href="ident?i=node">node</a>;
<a name="L1823" href="source/net/ipv4/tcp_ipv4.c#L1823">1823</a>         struct <a href="ident?i=sock">sock</a> *sk = cur;
<a name="L1824" href="source/net/ipv4/tcp_ipv4.c#L1824">1824</a>         struct <a href="ident?i=inet_listen_hashbucket">inet_listen_hashbucket</a> *ilb;
<a name="L1825" href="source/net/ipv4/tcp_ipv4.c#L1825">1825</a>         struct <a href="ident?i=tcp_iter_state">tcp_iter_state</a> *<a href="ident?i=st">st</a> = <a href="ident?i=seq">seq</a>-&gt;<a href="ident?i=private">private</a>;
<a name="L1826" href="source/net/ipv4/tcp_ipv4.c#L1826">1826</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=seq_file_net">seq_file_net</a>(<a href="ident?i=seq">seq</a>);
<a name="L1827" href="source/net/ipv4/tcp_ipv4.c#L1827">1827</a> 
<a name="L1828" href="source/net/ipv4/tcp_ipv4.c#L1828">1828</a>         if (!sk) {
<a name="L1829" href="source/net/ipv4/tcp_ipv4.c#L1829">1829</a>                 ilb = &amp;<a href="ident?i=tcp_hashinfo">tcp_hashinfo</a>.listening_hash[<a href="ident?i=st">st</a>-&gt;<a href="ident?i=bucket">bucket</a>];
<a name="L1830" href="source/net/ipv4/tcp_ipv4.c#L1830">1830</a>                 <a href="ident?i=spin_lock_bh">spin_lock_bh</a>(&amp;ilb-&gt;<a href="ident?i=lock">lock</a>);
<a name="L1831" href="source/net/ipv4/tcp_ipv4.c#L1831">1831</a>                 sk = <a href="ident?i=sk_nulls_head">sk_nulls_head</a>(&amp;ilb-&gt;<a href="ident?i=head">head</a>);
<a name="L1832" href="source/net/ipv4/tcp_ipv4.c#L1832">1832</a>                 <a href="ident?i=st">st</a>-&gt;<a href="ident?i=offset">offset</a> = 0;
<a name="L1833" href="source/net/ipv4/tcp_ipv4.c#L1833">1833</a>                 goto get_sk;
<a name="L1834" href="source/net/ipv4/tcp_ipv4.c#L1834">1834</a>         }
<a name="L1835" href="source/net/ipv4/tcp_ipv4.c#L1835">1835</a>         ilb = &amp;<a href="ident?i=tcp_hashinfo">tcp_hashinfo</a>.listening_hash[<a href="ident?i=st">st</a>-&gt;<a href="ident?i=bucket">bucket</a>];
<a name="L1836" href="source/net/ipv4/tcp_ipv4.c#L1836">1836</a>         ++<a href="ident?i=st">st</a>-&gt;<a href="ident?i=num">num</a>;
<a name="L1837" href="source/net/ipv4/tcp_ipv4.c#L1837">1837</a>         ++<a href="ident?i=st">st</a>-&gt;<a href="ident?i=offset">offset</a>;
<a name="L1838" href="source/net/ipv4/tcp_ipv4.c#L1838">1838</a> 
<a name="L1839" href="source/net/ipv4/tcp_ipv4.c#L1839">1839</a>         if (<a href="ident?i=st">st</a>-&gt;<a href="ident?i=state">state</a> == TCP_SEQ_STATE_OPENREQ) {
<a name="L1840" href="source/net/ipv4/tcp_ipv4.c#L1840">1840</a>                 struct <a href="ident?i=request_sock">request_sock</a> *<a href="ident?i=req">req</a> = cur;
<a name="L1841" href="source/net/ipv4/tcp_ipv4.c#L1841">1841</a> 
<a name="L1842" href="source/net/ipv4/tcp_ipv4.c#L1842">1842</a>                 icsk = <a href="ident?i=inet_csk">inet_csk</a>(<a href="ident?i=st">st</a>-&gt;syn_wait_sk);
<a name="L1843" href="source/net/ipv4/tcp_ipv4.c#L1843">1843</a>                 <a href="ident?i=req">req</a> = <a href="ident?i=req">req</a>-&gt;dl_next;
<a name="L1844" href="source/net/ipv4/tcp_ipv4.c#L1844">1844</a>                 while (1) {
<a name="L1845" href="source/net/ipv4/tcp_ipv4.c#L1845">1845</a>                         while (<a href="ident?i=req">req</a>) {
<a name="L1846" href="source/net/ipv4/tcp_ipv4.c#L1846">1846</a>                                 if (<a href="ident?i=req">req</a>-&gt;rsk_ops-&gt;<a href="ident?i=family">family</a> == <a href="ident?i=st">st</a>-&gt;<a href="ident?i=family">family</a>) {
<a name="L1847" href="source/net/ipv4/tcp_ipv4.c#L1847">1847</a>                                         cur = <a href="ident?i=req">req</a>;
<a name="L1848" href="source/net/ipv4/tcp_ipv4.c#L1848">1848</a>                                         goto <a href="ident?i=out">out</a>;
<a name="L1849" href="source/net/ipv4/tcp_ipv4.c#L1849">1849</a>                                 }
<a name="L1850" href="source/net/ipv4/tcp_ipv4.c#L1850">1850</a>                                 <a href="ident?i=req">req</a> = <a href="ident?i=req">req</a>-&gt;dl_next;
<a name="L1851" href="source/net/ipv4/tcp_ipv4.c#L1851">1851</a>                         }
<a name="L1852" href="source/net/ipv4/tcp_ipv4.c#L1852">1852</a>                         if (++<a href="ident?i=st">st</a>-&gt;sbucket &gt;= icsk-&gt;icsk_accept_queue.listen_opt-&gt;nr_table_entries)
<a name="L1853" href="source/net/ipv4/tcp_ipv4.c#L1853">1853</a>                                 break;
<a name="L1854" href="source/net/ipv4/tcp_ipv4.c#L1854">1854</a> <a href="ident?i=get_req">get_req</a>:
<a name="L1855" href="source/net/ipv4/tcp_ipv4.c#L1855">1855</a>                         <a href="ident?i=req">req</a> = icsk-&gt;icsk_accept_queue.listen_opt-&gt;syn_table[<a href="ident?i=st">st</a>-&gt;sbucket];
<a name="L1856" href="source/net/ipv4/tcp_ipv4.c#L1856">1856</a>                 }
<a name="L1857" href="source/net/ipv4/tcp_ipv4.c#L1857">1857</a>                 sk        = <a href="ident?i=sk_nulls_next">sk_nulls_next</a>(<a href="ident?i=st">st</a>-&gt;syn_wait_sk);
<a name="L1858" href="source/net/ipv4/tcp_ipv4.c#L1858">1858</a>                 <a href="ident?i=st">st</a>-&gt;<a href="ident?i=state">state</a> = TCP_SEQ_STATE_LISTENING;
<a name="L1859" href="source/net/ipv4/tcp_ipv4.c#L1859">1859</a>                 <a href="ident?i=spin_unlock_bh">spin_unlock_bh</a>(&amp;icsk-&gt;icsk_accept_queue.syn_wait_lock);
<a name="L1860" href="source/net/ipv4/tcp_ipv4.c#L1860">1860</a>         } else {
<a name="L1861" href="source/net/ipv4/tcp_ipv4.c#L1861">1861</a>                 icsk = <a href="ident?i=inet_csk">inet_csk</a>(sk);
<a name="L1862" href="source/net/ipv4/tcp_ipv4.c#L1862">1862</a>                 <a href="ident?i=spin_lock_bh">spin_lock_bh</a>(&amp;icsk-&gt;icsk_accept_queue.syn_wait_lock);
<a name="L1863" href="source/net/ipv4/tcp_ipv4.c#L1863">1863</a>                 if (<a href="ident?i=reqsk_queue_len">reqsk_queue_len</a>(&amp;icsk-&gt;icsk_accept_queue))
<a name="L1864" href="source/net/ipv4/tcp_ipv4.c#L1864">1864</a>                         goto start_req;
<a name="L1865" href="source/net/ipv4/tcp_ipv4.c#L1865">1865</a>                 <a href="ident?i=spin_unlock_bh">spin_unlock_bh</a>(&amp;icsk-&gt;icsk_accept_queue.syn_wait_lock);
<a name="L1866" href="source/net/ipv4/tcp_ipv4.c#L1866">1866</a>                 sk = <a href="ident?i=sk_nulls_next">sk_nulls_next</a>(sk);
<a name="L1867" href="source/net/ipv4/tcp_ipv4.c#L1867">1867</a>         }
<a name="L1868" href="source/net/ipv4/tcp_ipv4.c#L1868">1868</a> get_sk:
<a name="L1869" href="source/net/ipv4/tcp_ipv4.c#L1869">1869</a>         <a href="ident?i=sk_nulls_for_each_from">sk_nulls_for_each_from</a>(sk, <a href="ident?i=node">node</a>) {
<a name="L1870" href="source/net/ipv4/tcp_ipv4.c#L1870">1870</a>                 if (!<a href="ident?i=net_eq">net_eq</a>(<a href="ident?i=sock_net">sock_net</a>(sk), <a href="ident?i=net">net</a>))
<a name="L1871" href="source/net/ipv4/tcp_ipv4.c#L1871">1871</a>                         continue;
<a name="L1872" href="source/net/ipv4/tcp_ipv4.c#L1872">1872</a>                 if (sk-&gt;<a href="ident?i=sk_family">sk_family</a> == <a href="ident?i=st">st</a>-&gt;<a href="ident?i=family">family</a>) {
<a name="L1873" href="source/net/ipv4/tcp_ipv4.c#L1873">1873</a>                         cur = sk;
<a name="L1874" href="source/net/ipv4/tcp_ipv4.c#L1874">1874</a>                         goto <a href="ident?i=out">out</a>;
<a name="L1875" href="source/net/ipv4/tcp_ipv4.c#L1875">1875</a>                 }
<a name="L1876" href="source/net/ipv4/tcp_ipv4.c#L1876">1876</a>                 icsk = <a href="ident?i=inet_csk">inet_csk</a>(sk);
<a name="L1877" href="source/net/ipv4/tcp_ipv4.c#L1877">1877</a>                 <a href="ident?i=spin_lock_bh">spin_lock_bh</a>(&amp;icsk-&gt;icsk_accept_queue.syn_wait_lock);
<a name="L1878" href="source/net/ipv4/tcp_ipv4.c#L1878">1878</a>                 if (<a href="ident?i=reqsk_queue_len">reqsk_queue_len</a>(&amp;icsk-&gt;icsk_accept_queue)) {
<a name="L1879" href="source/net/ipv4/tcp_ipv4.c#L1879">1879</a> start_req:
<a name="L1880" href="source/net/ipv4/tcp_ipv4.c#L1880">1880</a>                         <a href="ident?i=st">st</a>-&gt;<a href="ident?i=uid">uid</a>         = <a href="ident?i=sock_i_uid">sock_i_uid</a>(sk);
<a name="L1881" href="source/net/ipv4/tcp_ipv4.c#L1881">1881</a>                         <a href="ident?i=st">st</a>-&gt;syn_wait_sk = sk;
<a name="L1882" href="source/net/ipv4/tcp_ipv4.c#L1882">1882</a>                         <a href="ident?i=st">st</a>-&gt;<a href="ident?i=state">state</a>       = TCP_SEQ_STATE_OPENREQ;
<a name="L1883" href="source/net/ipv4/tcp_ipv4.c#L1883">1883</a>                         <a href="ident?i=st">st</a>-&gt;sbucket     = 0;
<a name="L1884" href="source/net/ipv4/tcp_ipv4.c#L1884">1884</a>                         goto <a href="ident?i=get_req">get_req</a>;
<a name="L1885" href="source/net/ipv4/tcp_ipv4.c#L1885">1885</a>                 }
<a name="L1886" href="source/net/ipv4/tcp_ipv4.c#L1886">1886</a>                 <a href="ident?i=spin_unlock_bh">spin_unlock_bh</a>(&amp;icsk-&gt;icsk_accept_queue.syn_wait_lock);
<a name="L1887" href="source/net/ipv4/tcp_ipv4.c#L1887">1887</a>         }
<a name="L1888" href="source/net/ipv4/tcp_ipv4.c#L1888">1888</a>         <a href="ident?i=spin_unlock_bh">spin_unlock_bh</a>(&amp;ilb-&gt;<a href="ident?i=lock">lock</a>);
<a name="L1889" href="source/net/ipv4/tcp_ipv4.c#L1889">1889</a>         <a href="ident?i=st">st</a>-&gt;<a href="ident?i=offset">offset</a> = 0;
<a name="L1890" href="source/net/ipv4/tcp_ipv4.c#L1890">1890</a>         if (++<a href="ident?i=st">st</a>-&gt;<a href="ident?i=bucket">bucket</a> &lt; <a href="ident?i=INET_LHTABLE_SIZE">INET_LHTABLE_SIZE</a>) {
<a name="L1891" href="source/net/ipv4/tcp_ipv4.c#L1891">1891</a>                 ilb = &amp;<a href="ident?i=tcp_hashinfo">tcp_hashinfo</a>.listening_hash[<a href="ident?i=st">st</a>-&gt;<a href="ident?i=bucket">bucket</a>];
<a name="L1892" href="source/net/ipv4/tcp_ipv4.c#L1892">1892</a>                 <a href="ident?i=spin_lock_bh">spin_lock_bh</a>(&amp;ilb-&gt;<a href="ident?i=lock">lock</a>);
<a name="L1893" href="source/net/ipv4/tcp_ipv4.c#L1893">1893</a>                 sk = <a href="ident?i=sk_nulls_head">sk_nulls_head</a>(&amp;ilb-&gt;<a href="ident?i=head">head</a>);
<a name="L1894" href="source/net/ipv4/tcp_ipv4.c#L1894">1894</a>                 goto get_sk;
<a name="L1895" href="source/net/ipv4/tcp_ipv4.c#L1895">1895</a>         }
<a name="L1896" href="source/net/ipv4/tcp_ipv4.c#L1896">1896</a>         cur = <a href="ident?i=NULL">NULL</a>;
<a name="L1897" href="source/net/ipv4/tcp_ipv4.c#L1897">1897</a> <a href="ident?i=out">out</a>:
<a name="L1898" href="source/net/ipv4/tcp_ipv4.c#L1898">1898</a>         return cur;
<a name="L1899" href="source/net/ipv4/tcp_ipv4.c#L1899">1899</a> }
<a name="L1900" href="source/net/ipv4/tcp_ipv4.c#L1900">1900</a> 
<a name="L1901" href="source/net/ipv4/tcp_ipv4.c#L1901">1901</a> static void *<a href="ident?i=listening_get_idx">listening_get_idx</a>(struct <a href="ident?i=seq_file">seq_file</a> *<a href="ident?i=seq">seq</a>, <a href="ident?i=loff_t">loff_t</a> *<a href="ident?i=pos">pos</a>)
<a name="L1902" href="source/net/ipv4/tcp_ipv4.c#L1902">1902</a> {
<a name="L1903" href="source/net/ipv4/tcp_ipv4.c#L1903">1903</a>         struct <a href="ident?i=tcp_iter_state">tcp_iter_state</a> *<a href="ident?i=st">st</a> = <a href="ident?i=seq">seq</a>-&gt;<a href="ident?i=private">private</a>;
<a name="L1904" href="source/net/ipv4/tcp_ipv4.c#L1904">1904</a>         void *<a href="ident?i=rc">rc</a>;
<a name="L1905" href="source/net/ipv4/tcp_ipv4.c#L1905">1905</a> 
<a name="L1906" href="source/net/ipv4/tcp_ipv4.c#L1906">1906</a>         <a href="ident?i=st">st</a>-&gt;<a href="ident?i=bucket">bucket</a> = 0;
<a name="L1907" href="source/net/ipv4/tcp_ipv4.c#L1907">1907</a>         <a href="ident?i=st">st</a>-&gt;<a href="ident?i=offset">offset</a> = 0;
<a name="L1908" href="source/net/ipv4/tcp_ipv4.c#L1908">1908</a>         <a href="ident?i=rc">rc</a> = <a href="ident?i=listening_get_next">listening_get_next</a>(<a href="ident?i=seq">seq</a>, <a href="ident?i=NULL">NULL</a>);
<a name="L1909" href="source/net/ipv4/tcp_ipv4.c#L1909">1909</a> 
<a name="L1910" href="source/net/ipv4/tcp_ipv4.c#L1910">1910</a>         while (<a href="ident?i=rc">rc</a> &amp;&amp; *<a href="ident?i=pos">pos</a>) {
<a name="L1911" href="source/net/ipv4/tcp_ipv4.c#L1911">1911</a>                 <a href="ident?i=rc">rc</a> = <a href="ident?i=listening_get_next">listening_get_next</a>(<a href="ident?i=seq">seq</a>, <a href="ident?i=rc">rc</a>);
<a name="L1912" href="source/net/ipv4/tcp_ipv4.c#L1912">1912</a>                 --*<a href="ident?i=pos">pos</a>;
<a name="L1913" href="source/net/ipv4/tcp_ipv4.c#L1913">1913</a>         }
<a name="L1914" href="source/net/ipv4/tcp_ipv4.c#L1914">1914</a>         return <a href="ident?i=rc">rc</a>;
<a name="L1915" href="source/net/ipv4/tcp_ipv4.c#L1915">1915</a> }
<a name="L1916" href="source/net/ipv4/tcp_ipv4.c#L1916">1916</a> 
<a name="L1917" href="source/net/ipv4/tcp_ipv4.c#L1917">1917</a> static inline <a href="ident?i=bool">bool</a> <a href="ident?i=empty_bucket">empty_bucket</a>(const struct <a href="ident?i=tcp_iter_state">tcp_iter_state</a> *<a href="ident?i=st">st</a>)
<a name="L1918" href="source/net/ipv4/tcp_ipv4.c#L1918">1918</a> {
<a name="L1919" href="source/net/ipv4/tcp_ipv4.c#L1919">1919</a>         return <a href="ident?i=hlist_nulls_empty">hlist_nulls_empty</a>(&amp;<a href="ident?i=tcp_hashinfo">tcp_hashinfo</a>.ehash[<a href="ident?i=st">st</a>-&gt;<a href="ident?i=bucket">bucket</a>].<a href="ident?i=chain">chain</a>);
<a name="L1920" href="source/net/ipv4/tcp_ipv4.c#L1920">1920</a> }
<a name="L1921" href="source/net/ipv4/tcp_ipv4.c#L1921">1921</a> 
<a name="L1922" href="source/net/ipv4/tcp_ipv4.c#L1922">1922</a> <b><i>/*</i></b>
<a name="L1923" href="source/net/ipv4/tcp_ipv4.c#L1923">1923</a> <b><i> * Get first established socket starting from bucket given in st-&gt;bucket.</i></b>
<a name="L1924" href="source/net/ipv4/tcp_ipv4.c#L1924">1924</a> <b><i> * If st-&gt;bucket is zero, the very first socket in the hash is returned.</i></b>
<a name="L1925" href="source/net/ipv4/tcp_ipv4.c#L1925">1925</a> <b><i> */</i></b>
<a name="L1926" href="source/net/ipv4/tcp_ipv4.c#L1926">1926</a> static void *<a href="ident?i=established_get_first">established_get_first</a>(struct <a href="ident?i=seq_file">seq_file</a> *<a href="ident?i=seq">seq</a>)
<a name="L1927" href="source/net/ipv4/tcp_ipv4.c#L1927">1927</a> {
<a name="L1928" href="source/net/ipv4/tcp_ipv4.c#L1928">1928</a>         struct <a href="ident?i=tcp_iter_state">tcp_iter_state</a> *<a href="ident?i=st">st</a> = <a href="ident?i=seq">seq</a>-&gt;<a href="ident?i=private">private</a>;
<a name="L1929" href="source/net/ipv4/tcp_ipv4.c#L1929">1929</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=seq_file_net">seq_file_net</a>(<a href="ident?i=seq">seq</a>);
<a name="L1930" href="source/net/ipv4/tcp_ipv4.c#L1930">1930</a>         void *<a href="ident?i=rc">rc</a> = <a href="ident?i=NULL">NULL</a>;
<a name="L1931" href="source/net/ipv4/tcp_ipv4.c#L1931">1931</a> 
<a name="L1932" href="source/net/ipv4/tcp_ipv4.c#L1932">1932</a>         <a href="ident?i=st">st</a>-&gt;<a href="ident?i=offset">offset</a> = 0;
<a name="L1933" href="source/net/ipv4/tcp_ipv4.c#L1933">1933</a>         for (; <a href="ident?i=st">st</a>-&gt;<a href="ident?i=bucket">bucket</a> &lt;= <a href="ident?i=tcp_hashinfo">tcp_hashinfo</a>.ehash_mask; ++<a href="ident?i=st">st</a>-&gt;<a href="ident?i=bucket">bucket</a>) {
<a name="L1934" href="source/net/ipv4/tcp_ipv4.c#L1934">1934</a>                 struct <a href="ident?i=sock">sock</a> *sk;
<a name="L1935" href="source/net/ipv4/tcp_ipv4.c#L1935">1935</a>                 struct <a href="ident?i=hlist_nulls_node">hlist_nulls_node</a> *<a href="ident?i=node">node</a>;
<a name="L1936" href="source/net/ipv4/tcp_ipv4.c#L1936">1936</a>                 <a href="ident?i=spinlock_t">spinlock_t</a> *<a href="ident?i=lock">lock</a> = <a href="ident?i=inet_ehash_lockp">inet_ehash_lockp</a>(&amp;<a href="ident?i=tcp_hashinfo">tcp_hashinfo</a>, <a href="ident?i=st">st</a>-&gt;<a href="ident?i=bucket">bucket</a>);
<a name="L1937" href="source/net/ipv4/tcp_ipv4.c#L1937">1937</a> 
<a name="L1938" href="source/net/ipv4/tcp_ipv4.c#L1938">1938</a>                 <b><i>/* Lockless fast path for the common case of empty buckets */</i></b>
<a name="L1939" href="source/net/ipv4/tcp_ipv4.c#L1939">1939</a>                 if (<a href="ident?i=empty_bucket">empty_bucket</a>(<a href="ident?i=st">st</a>))
<a name="L1940" href="source/net/ipv4/tcp_ipv4.c#L1940">1940</a>                         continue;
<a name="L1941" href="source/net/ipv4/tcp_ipv4.c#L1941">1941</a> 
<a name="L1942" href="source/net/ipv4/tcp_ipv4.c#L1942">1942</a>                 <a href="ident?i=spin_lock_bh">spin_lock_bh</a>(<a href="ident?i=lock">lock</a>);
<a name="L1943" href="source/net/ipv4/tcp_ipv4.c#L1943">1943</a>                 <a href="ident?i=sk_nulls_for_each">sk_nulls_for_each</a>(sk, <a href="ident?i=node">node</a>, &amp;<a href="ident?i=tcp_hashinfo">tcp_hashinfo</a>.ehash[<a href="ident?i=st">st</a>-&gt;<a href="ident?i=bucket">bucket</a>].<a href="ident?i=chain">chain</a>) {
<a name="L1944" href="source/net/ipv4/tcp_ipv4.c#L1944">1944</a>                         if (sk-&gt;<a href="ident?i=sk_family">sk_family</a> != <a href="ident?i=st">st</a>-&gt;<a href="ident?i=family">family</a> ||
<a name="L1945" href="source/net/ipv4/tcp_ipv4.c#L1945">1945</a>                             !<a href="ident?i=net_eq">net_eq</a>(<a href="ident?i=sock_net">sock_net</a>(sk), <a href="ident?i=net">net</a>)) {
<a name="L1946" href="source/net/ipv4/tcp_ipv4.c#L1946">1946</a>                                 continue;
<a name="L1947" href="source/net/ipv4/tcp_ipv4.c#L1947">1947</a>                         }
<a name="L1948" href="source/net/ipv4/tcp_ipv4.c#L1948">1948</a>                         <a href="ident?i=rc">rc</a> = sk;
<a name="L1949" href="source/net/ipv4/tcp_ipv4.c#L1949">1949</a>                         goto <a href="ident?i=out">out</a>;
<a name="L1950" href="source/net/ipv4/tcp_ipv4.c#L1950">1950</a>                 }
<a name="L1951" href="source/net/ipv4/tcp_ipv4.c#L1951">1951</a>                 <a href="ident?i=spin_unlock_bh">spin_unlock_bh</a>(<a href="ident?i=lock">lock</a>);
<a name="L1952" href="source/net/ipv4/tcp_ipv4.c#L1952">1952</a>         }
<a name="L1953" href="source/net/ipv4/tcp_ipv4.c#L1953">1953</a> <a href="ident?i=out">out</a>:
<a name="L1954" href="source/net/ipv4/tcp_ipv4.c#L1954">1954</a>         return <a href="ident?i=rc">rc</a>;
<a name="L1955" href="source/net/ipv4/tcp_ipv4.c#L1955">1955</a> }
<a name="L1956" href="source/net/ipv4/tcp_ipv4.c#L1956">1956</a> 
<a name="L1957" href="source/net/ipv4/tcp_ipv4.c#L1957">1957</a> static void *<a href="ident?i=established_get_next">established_get_next</a>(struct <a href="ident?i=seq_file">seq_file</a> *<a href="ident?i=seq">seq</a>, void *cur)
<a name="L1958" href="source/net/ipv4/tcp_ipv4.c#L1958">1958</a> {
<a name="L1959" href="source/net/ipv4/tcp_ipv4.c#L1959">1959</a>         struct <a href="ident?i=sock">sock</a> *sk = cur;
<a name="L1960" href="source/net/ipv4/tcp_ipv4.c#L1960">1960</a>         struct <a href="ident?i=hlist_nulls_node">hlist_nulls_node</a> *<a href="ident?i=node">node</a>;
<a name="L1961" href="source/net/ipv4/tcp_ipv4.c#L1961">1961</a>         struct <a href="ident?i=tcp_iter_state">tcp_iter_state</a> *<a href="ident?i=st">st</a> = <a href="ident?i=seq">seq</a>-&gt;<a href="ident?i=private">private</a>;
<a name="L1962" href="source/net/ipv4/tcp_ipv4.c#L1962">1962</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=seq_file_net">seq_file_net</a>(<a href="ident?i=seq">seq</a>);
<a name="L1963" href="source/net/ipv4/tcp_ipv4.c#L1963">1963</a> 
<a name="L1964" href="source/net/ipv4/tcp_ipv4.c#L1964">1964</a>         ++<a href="ident?i=st">st</a>-&gt;<a href="ident?i=num">num</a>;
<a name="L1965" href="source/net/ipv4/tcp_ipv4.c#L1965">1965</a>         ++<a href="ident?i=st">st</a>-&gt;<a href="ident?i=offset">offset</a>;
<a name="L1966" href="source/net/ipv4/tcp_ipv4.c#L1966">1966</a> 
<a name="L1967" href="source/net/ipv4/tcp_ipv4.c#L1967">1967</a>         sk = <a href="ident?i=sk_nulls_next">sk_nulls_next</a>(sk);
<a name="L1968" href="source/net/ipv4/tcp_ipv4.c#L1968">1968</a> 
<a name="L1969" href="source/net/ipv4/tcp_ipv4.c#L1969">1969</a>         <a href="ident?i=sk_nulls_for_each_from">sk_nulls_for_each_from</a>(sk, <a href="ident?i=node">node</a>) {
<a name="L1970" href="source/net/ipv4/tcp_ipv4.c#L1970">1970</a>                 if (sk-&gt;<a href="ident?i=sk_family">sk_family</a> == <a href="ident?i=st">st</a>-&gt;<a href="ident?i=family">family</a> &amp;&amp; <a href="ident?i=net_eq">net_eq</a>(<a href="ident?i=sock_net">sock_net</a>(sk), <a href="ident?i=net">net</a>))
<a name="L1971" href="source/net/ipv4/tcp_ipv4.c#L1971">1971</a>                         return sk;
<a name="L1972" href="source/net/ipv4/tcp_ipv4.c#L1972">1972</a>         }
<a name="L1973" href="source/net/ipv4/tcp_ipv4.c#L1973">1973</a> 
<a name="L1974" href="source/net/ipv4/tcp_ipv4.c#L1974">1974</a>         <a href="ident?i=spin_unlock_bh">spin_unlock_bh</a>(<a href="ident?i=inet_ehash_lockp">inet_ehash_lockp</a>(&amp;<a href="ident?i=tcp_hashinfo">tcp_hashinfo</a>, <a href="ident?i=st">st</a>-&gt;<a href="ident?i=bucket">bucket</a>));
<a name="L1975" href="source/net/ipv4/tcp_ipv4.c#L1975">1975</a>         ++<a href="ident?i=st">st</a>-&gt;<a href="ident?i=bucket">bucket</a>;
<a name="L1976" href="source/net/ipv4/tcp_ipv4.c#L1976">1976</a>         return <a href="ident?i=established_get_first">established_get_first</a>(<a href="ident?i=seq">seq</a>);
<a name="L1977" href="source/net/ipv4/tcp_ipv4.c#L1977">1977</a> }
<a name="L1978" href="source/net/ipv4/tcp_ipv4.c#L1978">1978</a> 
<a name="L1979" href="source/net/ipv4/tcp_ipv4.c#L1979">1979</a> static void *<a href="ident?i=established_get_idx">established_get_idx</a>(struct <a href="ident?i=seq_file">seq_file</a> *<a href="ident?i=seq">seq</a>, <a href="ident?i=loff_t">loff_t</a> <a href="ident?i=pos">pos</a>)
<a name="L1980" href="source/net/ipv4/tcp_ipv4.c#L1980">1980</a> {
<a name="L1981" href="source/net/ipv4/tcp_ipv4.c#L1981">1981</a>         struct <a href="ident?i=tcp_iter_state">tcp_iter_state</a> *<a href="ident?i=st">st</a> = <a href="ident?i=seq">seq</a>-&gt;<a href="ident?i=private">private</a>;
<a name="L1982" href="source/net/ipv4/tcp_ipv4.c#L1982">1982</a>         void *<a href="ident?i=rc">rc</a>;
<a name="L1983" href="source/net/ipv4/tcp_ipv4.c#L1983">1983</a> 
<a name="L1984" href="source/net/ipv4/tcp_ipv4.c#L1984">1984</a>         <a href="ident?i=st">st</a>-&gt;<a href="ident?i=bucket">bucket</a> = 0;
<a name="L1985" href="source/net/ipv4/tcp_ipv4.c#L1985">1985</a>         <a href="ident?i=rc">rc</a> = <a href="ident?i=established_get_first">established_get_first</a>(<a href="ident?i=seq">seq</a>);
<a name="L1986" href="source/net/ipv4/tcp_ipv4.c#L1986">1986</a> 
<a name="L1987" href="source/net/ipv4/tcp_ipv4.c#L1987">1987</a>         while (<a href="ident?i=rc">rc</a> &amp;&amp; <a href="ident?i=pos">pos</a>) {
<a name="L1988" href="source/net/ipv4/tcp_ipv4.c#L1988">1988</a>                 <a href="ident?i=rc">rc</a> = <a href="ident?i=established_get_next">established_get_next</a>(<a href="ident?i=seq">seq</a>, <a href="ident?i=rc">rc</a>);
<a name="L1989" href="source/net/ipv4/tcp_ipv4.c#L1989">1989</a>                 --<a href="ident?i=pos">pos</a>;
<a name="L1990" href="source/net/ipv4/tcp_ipv4.c#L1990">1990</a>         }
<a name="L1991" href="source/net/ipv4/tcp_ipv4.c#L1991">1991</a>         return <a href="ident?i=rc">rc</a>;
<a name="L1992" href="source/net/ipv4/tcp_ipv4.c#L1992">1992</a> }
<a name="L1993" href="source/net/ipv4/tcp_ipv4.c#L1993">1993</a> 
<a name="L1994" href="source/net/ipv4/tcp_ipv4.c#L1994">1994</a> static void *<a href="ident?i=tcp_get_idx">tcp_get_idx</a>(struct <a href="ident?i=seq_file">seq_file</a> *<a href="ident?i=seq">seq</a>, <a href="ident?i=loff_t">loff_t</a> <a href="ident?i=pos">pos</a>)
<a name="L1995" href="source/net/ipv4/tcp_ipv4.c#L1995">1995</a> {
<a name="L1996" href="source/net/ipv4/tcp_ipv4.c#L1996">1996</a>         void *<a href="ident?i=rc">rc</a>;
<a name="L1997" href="source/net/ipv4/tcp_ipv4.c#L1997">1997</a>         struct <a href="ident?i=tcp_iter_state">tcp_iter_state</a> *<a href="ident?i=st">st</a> = <a href="ident?i=seq">seq</a>-&gt;<a href="ident?i=private">private</a>;
<a name="L1998" href="source/net/ipv4/tcp_ipv4.c#L1998">1998</a> 
<a name="L1999" href="source/net/ipv4/tcp_ipv4.c#L1999">1999</a>         <a href="ident?i=st">st</a>-&gt;<a href="ident?i=state">state</a> = TCP_SEQ_STATE_LISTENING;
<a name="L2000" href="source/net/ipv4/tcp_ipv4.c#L2000">2000</a>         <a href="ident?i=rc">rc</a>        = <a href="ident?i=listening_get_idx">listening_get_idx</a>(<a href="ident?i=seq">seq</a>, &amp;<a href="ident?i=pos">pos</a>);
<a name="L2001" href="source/net/ipv4/tcp_ipv4.c#L2001">2001</a> 
<a name="L2002" href="source/net/ipv4/tcp_ipv4.c#L2002">2002</a>         if (!<a href="ident?i=rc">rc</a>) {
<a name="L2003" href="source/net/ipv4/tcp_ipv4.c#L2003">2003</a>                 <a href="ident?i=st">st</a>-&gt;<a href="ident?i=state">state</a> = TCP_SEQ_STATE_ESTABLISHED;
<a name="L2004" href="source/net/ipv4/tcp_ipv4.c#L2004">2004</a>                 <a href="ident?i=rc">rc</a>        = <a href="ident?i=established_get_idx">established_get_idx</a>(<a href="ident?i=seq">seq</a>, <a href="ident?i=pos">pos</a>);
<a name="L2005" href="source/net/ipv4/tcp_ipv4.c#L2005">2005</a>         }
<a name="L2006" href="source/net/ipv4/tcp_ipv4.c#L2006">2006</a> 
<a name="L2007" href="source/net/ipv4/tcp_ipv4.c#L2007">2007</a>         return <a href="ident?i=rc">rc</a>;
<a name="L2008" href="source/net/ipv4/tcp_ipv4.c#L2008">2008</a> }
<a name="L2009" href="source/net/ipv4/tcp_ipv4.c#L2009">2009</a> 
<a name="L2010" href="source/net/ipv4/tcp_ipv4.c#L2010">2010</a> static void *<a href="ident?i=tcp_seek_last_pos">tcp_seek_last_pos</a>(struct <a href="ident?i=seq_file">seq_file</a> *<a href="ident?i=seq">seq</a>)
<a name="L2011" href="source/net/ipv4/tcp_ipv4.c#L2011">2011</a> {
<a name="L2012" href="source/net/ipv4/tcp_ipv4.c#L2012">2012</a>         struct <a href="ident?i=tcp_iter_state">tcp_iter_state</a> *<a href="ident?i=st">st</a> = <a href="ident?i=seq">seq</a>-&gt;<a href="ident?i=private">private</a>;
<a name="L2013" href="source/net/ipv4/tcp_ipv4.c#L2013">2013</a>         int <a href="ident?i=offset">offset</a> = <a href="ident?i=st">st</a>-&gt;<a href="ident?i=offset">offset</a>;
<a name="L2014" href="source/net/ipv4/tcp_ipv4.c#L2014">2014</a>         int orig_num = <a href="ident?i=st">st</a>-&gt;<a href="ident?i=num">num</a>;
<a name="L2015" href="source/net/ipv4/tcp_ipv4.c#L2015">2015</a>         void *<a href="ident?i=rc">rc</a> = <a href="ident?i=NULL">NULL</a>;
<a name="L2016" href="source/net/ipv4/tcp_ipv4.c#L2016">2016</a> 
<a name="L2017" href="source/net/ipv4/tcp_ipv4.c#L2017">2017</a>         switch (<a href="ident?i=st">st</a>-&gt;<a href="ident?i=state">state</a>) {
<a name="L2018" href="source/net/ipv4/tcp_ipv4.c#L2018">2018</a>         case TCP_SEQ_STATE_OPENREQ:
<a name="L2019" href="source/net/ipv4/tcp_ipv4.c#L2019">2019</a>         case TCP_SEQ_STATE_LISTENING:
<a name="L2020" href="source/net/ipv4/tcp_ipv4.c#L2020">2020</a>                 if (<a href="ident?i=st">st</a>-&gt;<a href="ident?i=bucket">bucket</a> &gt;= <a href="ident?i=INET_LHTABLE_SIZE">INET_LHTABLE_SIZE</a>)
<a name="L2021" href="source/net/ipv4/tcp_ipv4.c#L2021">2021</a>                         break;
<a name="L2022" href="source/net/ipv4/tcp_ipv4.c#L2022">2022</a>                 <a href="ident?i=st">st</a>-&gt;<a href="ident?i=state">state</a> = TCP_SEQ_STATE_LISTENING;
<a name="L2023" href="source/net/ipv4/tcp_ipv4.c#L2023">2023</a>                 <a href="ident?i=rc">rc</a> = <a href="ident?i=listening_get_next">listening_get_next</a>(<a href="ident?i=seq">seq</a>, <a href="ident?i=NULL">NULL</a>);
<a name="L2024" href="source/net/ipv4/tcp_ipv4.c#L2024">2024</a>                 while (<a href="ident?i=offset">offset</a>-- &amp;&amp; <a href="ident?i=rc">rc</a>)
<a name="L2025" href="source/net/ipv4/tcp_ipv4.c#L2025">2025</a>                         <a href="ident?i=rc">rc</a> = <a href="ident?i=listening_get_next">listening_get_next</a>(<a href="ident?i=seq">seq</a>, <a href="ident?i=rc">rc</a>);
<a name="L2026" href="source/net/ipv4/tcp_ipv4.c#L2026">2026</a>                 if (<a href="ident?i=rc">rc</a>)
<a name="L2027" href="source/net/ipv4/tcp_ipv4.c#L2027">2027</a>                         break;
<a name="L2028" href="source/net/ipv4/tcp_ipv4.c#L2028">2028</a>                 <a href="ident?i=st">st</a>-&gt;<a href="ident?i=bucket">bucket</a> = 0;
<a name="L2029" href="source/net/ipv4/tcp_ipv4.c#L2029">2029</a>                 <a href="ident?i=st">st</a>-&gt;<a href="ident?i=state">state</a> = TCP_SEQ_STATE_ESTABLISHED;
<a name="L2030" href="source/net/ipv4/tcp_ipv4.c#L2030">2030</a>                 <b><i>/* Fallthrough */</i></b>
<a name="L2031" href="source/net/ipv4/tcp_ipv4.c#L2031">2031</a>         case TCP_SEQ_STATE_ESTABLISHED:
<a name="L2032" href="source/net/ipv4/tcp_ipv4.c#L2032">2032</a>                 if (<a href="ident?i=st">st</a>-&gt;<a href="ident?i=bucket">bucket</a> &gt; <a href="ident?i=tcp_hashinfo">tcp_hashinfo</a>.ehash_mask)
<a name="L2033" href="source/net/ipv4/tcp_ipv4.c#L2033">2033</a>                         break;
<a name="L2034" href="source/net/ipv4/tcp_ipv4.c#L2034">2034</a>                 <a href="ident?i=rc">rc</a> = <a href="ident?i=established_get_first">established_get_first</a>(<a href="ident?i=seq">seq</a>);
<a name="L2035" href="source/net/ipv4/tcp_ipv4.c#L2035">2035</a>                 while (<a href="ident?i=offset">offset</a>-- &amp;&amp; <a href="ident?i=rc">rc</a>)
<a name="L2036" href="source/net/ipv4/tcp_ipv4.c#L2036">2036</a>                         <a href="ident?i=rc">rc</a> = <a href="ident?i=established_get_next">established_get_next</a>(<a href="ident?i=seq">seq</a>, <a href="ident?i=rc">rc</a>);
<a name="L2037" href="source/net/ipv4/tcp_ipv4.c#L2037">2037</a>         }
<a name="L2038" href="source/net/ipv4/tcp_ipv4.c#L2038">2038</a> 
<a name="L2039" href="source/net/ipv4/tcp_ipv4.c#L2039">2039</a>         <a href="ident?i=st">st</a>-&gt;<a href="ident?i=num">num</a> = orig_num;
<a name="L2040" href="source/net/ipv4/tcp_ipv4.c#L2040">2040</a> 
<a name="L2041" href="source/net/ipv4/tcp_ipv4.c#L2041">2041</a>         return <a href="ident?i=rc">rc</a>;
<a name="L2042" href="source/net/ipv4/tcp_ipv4.c#L2042">2042</a> }
<a name="L2043" href="source/net/ipv4/tcp_ipv4.c#L2043">2043</a> 
<a name="L2044" href="source/net/ipv4/tcp_ipv4.c#L2044">2044</a> static void *<a href="ident?i=tcp_seq_start">tcp_seq_start</a>(struct <a href="ident?i=seq_file">seq_file</a> *<a href="ident?i=seq">seq</a>, <a href="ident?i=loff_t">loff_t</a> *<a href="ident?i=pos">pos</a>)
<a name="L2045" href="source/net/ipv4/tcp_ipv4.c#L2045">2045</a> {
<a name="L2046" href="source/net/ipv4/tcp_ipv4.c#L2046">2046</a>         struct <a href="ident?i=tcp_iter_state">tcp_iter_state</a> *<a href="ident?i=st">st</a> = <a href="ident?i=seq">seq</a>-&gt;<a href="ident?i=private">private</a>;
<a name="L2047" href="source/net/ipv4/tcp_ipv4.c#L2047">2047</a>         void *<a href="ident?i=rc">rc</a>;
<a name="L2048" href="source/net/ipv4/tcp_ipv4.c#L2048">2048</a> 
<a name="L2049" href="source/net/ipv4/tcp_ipv4.c#L2049">2049</a>         if (*<a href="ident?i=pos">pos</a> &amp;&amp; *<a href="ident?i=pos">pos</a> == <a href="ident?i=st">st</a>-&gt;last_pos) {
<a name="L2050" href="source/net/ipv4/tcp_ipv4.c#L2050">2050</a>                 <a href="ident?i=rc">rc</a> = <a href="ident?i=tcp_seek_last_pos">tcp_seek_last_pos</a>(<a href="ident?i=seq">seq</a>);
<a name="L2051" href="source/net/ipv4/tcp_ipv4.c#L2051">2051</a>                 if (<a href="ident?i=rc">rc</a>)
<a name="L2052" href="source/net/ipv4/tcp_ipv4.c#L2052">2052</a>                         goto <a href="ident?i=out">out</a>;
<a name="L2053" href="source/net/ipv4/tcp_ipv4.c#L2053">2053</a>         }
<a name="L2054" href="source/net/ipv4/tcp_ipv4.c#L2054">2054</a> 
<a name="L2055" href="source/net/ipv4/tcp_ipv4.c#L2055">2055</a>         <a href="ident?i=st">st</a>-&gt;<a href="ident?i=state">state</a> = TCP_SEQ_STATE_LISTENING;
<a name="L2056" href="source/net/ipv4/tcp_ipv4.c#L2056">2056</a>         <a href="ident?i=st">st</a>-&gt;<a href="ident?i=num">num</a> = 0;
<a name="L2057" href="source/net/ipv4/tcp_ipv4.c#L2057">2057</a>         <a href="ident?i=st">st</a>-&gt;<a href="ident?i=bucket">bucket</a> = 0;
<a name="L2058" href="source/net/ipv4/tcp_ipv4.c#L2058">2058</a>         <a href="ident?i=st">st</a>-&gt;<a href="ident?i=offset">offset</a> = 0;
<a name="L2059" href="source/net/ipv4/tcp_ipv4.c#L2059">2059</a>         <a href="ident?i=rc">rc</a> = *<a href="ident?i=pos">pos</a> ? <a href="ident?i=tcp_get_idx">tcp_get_idx</a>(<a href="ident?i=seq">seq</a>, *<a href="ident?i=pos">pos</a> - 1) : <a href="ident?i=SEQ_START_TOKEN">SEQ_START_TOKEN</a>;
<a name="L2060" href="source/net/ipv4/tcp_ipv4.c#L2060">2060</a> 
<a name="L2061" href="source/net/ipv4/tcp_ipv4.c#L2061">2061</a> <a href="ident?i=out">out</a>:
<a name="L2062" href="source/net/ipv4/tcp_ipv4.c#L2062">2062</a>         <a href="ident?i=st">st</a>-&gt;last_pos = *<a href="ident?i=pos">pos</a>;
<a name="L2063" href="source/net/ipv4/tcp_ipv4.c#L2063">2063</a>         return <a href="ident?i=rc">rc</a>;
<a name="L2064" href="source/net/ipv4/tcp_ipv4.c#L2064">2064</a> }
<a name="L2065" href="source/net/ipv4/tcp_ipv4.c#L2065">2065</a> 
<a name="L2066" href="source/net/ipv4/tcp_ipv4.c#L2066">2066</a> static void *<a href="ident?i=tcp_seq_next">tcp_seq_next</a>(struct <a href="ident?i=seq_file">seq_file</a> *<a href="ident?i=seq">seq</a>, void *<a href="ident?i=v">v</a>, <a href="ident?i=loff_t">loff_t</a> *<a href="ident?i=pos">pos</a>)
<a name="L2067" href="source/net/ipv4/tcp_ipv4.c#L2067">2067</a> {
<a name="L2068" href="source/net/ipv4/tcp_ipv4.c#L2068">2068</a>         struct <a href="ident?i=tcp_iter_state">tcp_iter_state</a> *<a href="ident?i=st">st</a> = <a href="ident?i=seq">seq</a>-&gt;<a href="ident?i=private">private</a>;
<a name="L2069" href="source/net/ipv4/tcp_ipv4.c#L2069">2069</a>         void *<a href="ident?i=rc">rc</a> = <a href="ident?i=NULL">NULL</a>;
<a name="L2070" href="source/net/ipv4/tcp_ipv4.c#L2070">2070</a> 
<a name="L2071" href="source/net/ipv4/tcp_ipv4.c#L2071">2071</a>         if (<a href="ident?i=v">v</a> == <a href="ident?i=SEQ_START_TOKEN">SEQ_START_TOKEN</a>) {
<a name="L2072" href="source/net/ipv4/tcp_ipv4.c#L2072">2072</a>                 <a href="ident?i=rc">rc</a> = <a href="ident?i=tcp_get_idx">tcp_get_idx</a>(<a href="ident?i=seq">seq</a>, 0);
<a name="L2073" href="source/net/ipv4/tcp_ipv4.c#L2073">2073</a>                 goto <a href="ident?i=out">out</a>;
<a name="L2074" href="source/net/ipv4/tcp_ipv4.c#L2074">2074</a>         }
<a name="L2075" href="source/net/ipv4/tcp_ipv4.c#L2075">2075</a> 
<a name="L2076" href="source/net/ipv4/tcp_ipv4.c#L2076">2076</a>         switch (<a href="ident?i=st">st</a>-&gt;<a href="ident?i=state">state</a>) {
<a name="L2077" href="source/net/ipv4/tcp_ipv4.c#L2077">2077</a>         case TCP_SEQ_STATE_OPENREQ:
<a name="L2078" href="source/net/ipv4/tcp_ipv4.c#L2078">2078</a>         case TCP_SEQ_STATE_LISTENING:
<a name="L2079" href="source/net/ipv4/tcp_ipv4.c#L2079">2079</a>                 <a href="ident?i=rc">rc</a> = <a href="ident?i=listening_get_next">listening_get_next</a>(<a href="ident?i=seq">seq</a>, <a href="ident?i=v">v</a>);
<a name="L2080" href="source/net/ipv4/tcp_ipv4.c#L2080">2080</a>                 if (!<a href="ident?i=rc">rc</a>) {
<a name="L2081" href="source/net/ipv4/tcp_ipv4.c#L2081">2081</a>                         <a href="ident?i=st">st</a>-&gt;<a href="ident?i=state">state</a> = TCP_SEQ_STATE_ESTABLISHED;
<a name="L2082" href="source/net/ipv4/tcp_ipv4.c#L2082">2082</a>                         <a href="ident?i=st">st</a>-&gt;<a href="ident?i=bucket">bucket</a> = 0;
<a name="L2083" href="source/net/ipv4/tcp_ipv4.c#L2083">2083</a>                         <a href="ident?i=st">st</a>-&gt;<a href="ident?i=offset">offset</a> = 0;
<a name="L2084" href="source/net/ipv4/tcp_ipv4.c#L2084">2084</a>                         <a href="ident?i=rc">rc</a>        = <a href="ident?i=established_get_first">established_get_first</a>(<a href="ident?i=seq">seq</a>);
<a name="L2085" href="source/net/ipv4/tcp_ipv4.c#L2085">2085</a>                 }
<a name="L2086" href="source/net/ipv4/tcp_ipv4.c#L2086">2086</a>                 break;
<a name="L2087" href="source/net/ipv4/tcp_ipv4.c#L2087">2087</a>         case TCP_SEQ_STATE_ESTABLISHED:
<a name="L2088" href="source/net/ipv4/tcp_ipv4.c#L2088">2088</a>                 <a href="ident?i=rc">rc</a> = <a href="ident?i=established_get_next">established_get_next</a>(<a href="ident?i=seq">seq</a>, <a href="ident?i=v">v</a>);
<a name="L2089" href="source/net/ipv4/tcp_ipv4.c#L2089">2089</a>                 break;
<a name="L2090" href="source/net/ipv4/tcp_ipv4.c#L2090">2090</a>         }
<a name="L2091" href="source/net/ipv4/tcp_ipv4.c#L2091">2091</a> <a href="ident?i=out">out</a>:
<a name="L2092" href="source/net/ipv4/tcp_ipv4.c#L2092">2092</a>         ++*<a href="ident?i=pos">pos</a>;
<a name="L2093" href="source/net/ipv4/tcp_ipv4.c#L2093">2093</a>         <a href="ident?i=st">st</a>-&gt;last_pos = *<a href="ident?i=pos">pos</a>;
<a name="L2094" href="source/net/ipv4/tcp_ipv4.c#L2094">2094</a>         return <a href="ident?i=rc">rc</a>;
<a name="L2095" href="source/net/ipv4/tcp_ipv4.c#L2095">2095</a> }
<a name="L2096" href="source/net/ipv4/tcp_ipv4.c#L2096">2096</a> 
<a name="L2097" href="source/net/ipv4/tcp_ipv4.c#L2097">2097</a> static void <a href="ident?i=tcp_seq_stop">tcp_seq_stop</a>(struct <a href="ident?i=seq_file">seq_file</a> *<a href="ident?i=seq">seq</a>, void *<a href="ident?i=v">v</a>)
<a name="L2098" href="source/net/ipv4/tcp_ipv4.c#L2098">2098</a> {
<a name="L2099" href="source/net/ipv4/tcp_ipv4.c#L2099">2099</a>         struct <a href="ident?i=tcp_iter_state">tcp_iter_state</a> *<a href="ident?i=st">st</a> = <a href="ident?i=seq">seq</a>-&gt;<a href="ident?i=private">private</a>;
<a name="L2100" href="source/net/ipv4/tcp_ipv4.c#L2100">2100</a> 
<a name="L2101" href="source/net/ipv4/tcp_ipv4.c#L2101">2101</a>         switch (<a href="ident?i=st">st</a>-&gt;<a href="ident?i=state">state</a>) {
<a name="L2102" href="source/net/ipv4/tcp_ipv4.c#L2102">2102</a>         case TCP_SEQ_STATE_OPENREQ:
<a name="L2103" href="source/net/ipv4/tcp_ipv4.c#L2103">2103</a>                 if (<a href="ident?i=v">v</a>) {
<a name="L2104" href="source/net/ipv4/tcp_ipv4.c#L2104">2104</a>                         struct <a href="ident?i=inet_connection_sock">inet_connection_sock</a> *icsk = <a href="ident?i=inet_csk">inet_csk</a>(<a href="ident?i=st">st</a>-&gt;syn_wait_sk);
<a name="L2105" href="source/net/ipv4/tcp_ipv4.c#L2105">2105</a>                         <a href="ident?i=spin_unlock_bh">spin_unlock_bh</a>(&amp;icsk-&gt;icsk_accept_queue.syn_wait_lock);
<a name="L2106" href="source/net/ipv4/tcp_ipv4.c#L2106">2106</a>                 }
<a name="L2107" href="source/net/ipv4/tcp_ipv4.c#L2107">2107</a>         case TCP_SEQ_STATE_LISTENING:
<a name="L2108" href="source/net/ipv4/tcp_ipv4.c#L2108">2108</a>                 if (<a href="ident?i=v">v</a> != <a href="ident?i=SEQ_START_TOKEN">SEQ_START_TOKEN</a>)
<a name="L2109" href="source/net/ipv4/tcp_ipv4.c#L2109">2109</a>                         <a href="ident?i=spin_unlock_bh">spin_unlock_bh</a>(&amp;<a href="ident?i=tcp_hashinfo">tcp_hashinfo</a>.listening_hash[<a href="ident?i=st">st</a>-&gt;<a href="ident?i=bucket">bucket</a>].<a href="ident?i=lock">lock</a>);
<a name="L2110" href="source/net/ipv4/tcp_ipv4.c#L2110">2110</a>                 break;
<a name="L2111" href="source/net/ipv4/tcp_ipv4.c#L2111">2111</a>         case TCP_SEQ_STATE_ESTABLISHED:
<a name="L2112" href="source/net/ipv4/tcp_ipv4.c#L2112">2112</a>                 if (<a href="ident?i=v">v</a>)
<a name="L2113" href="source/net/ipv4/tcp_ipv4.c#L2113">2113</a>                         <a href="ident?i=spin_unlock_bh">spin_unlock_bh</a>(<a href="ident?i=inet_ehash_lockp">inet_ehash_lockp</a>(&amp;<a href="ident?i=tcp_hashinfo">tcp_hashinfo</a>, <a href="ident?i=st">st</a>-&gt;<a href="ident?i=bucket">bucket</a>));
<a name="L2114" href="source/net/ipv4/tcp_ipv4.c#L2114">2114</a>                 break;
<a name="L2115" href="source/net/ipv4/tcp_ipv4.c#L2115">2115</a>         }
<a name="L2116" href="source/net/ipv4/tcp_ipv4.c#L2116">2116</a> }
<a name="L2117" href="source/net/ipv4/tcp_ipv4.c#L2117">2117</a> 
<a name="L2118" href="source/net/ipv4/tcp_ipv4.c#L2118">2118</a> int <a href="ident?i=tcp_seq_open">tcp_seq_open</a>(struct <a href="ident?i=inode">inode</a> *<a href="ident?i=inode">inode</a>, struct <a href="ident?i=file">file</a> *<a href="ident?i=file">file</a>)
<a name="L2119" href="source/net/ipv4/tcp_ipv4.c#L2119">2119</a> {
<a name="L2120" href="source/net/ipv4/tcp_ipv4.c#L2120">2120</a>         struct <a href="ident?i=tcp_seq_afinfo">tcp_seq_afinfo</a> *afinfo = <a href="ident?i=PDE_DATA">PDE_DATA</a>(<a href="ident?i=inode">inode</a>);
<a name="L2121" href="source/net/ipv4/tcp_ipv4.c#L2121">2121</a>         struct <a href="ident?i=tcp_iter_state">tcp_iter_state</a> *<a href="ident?i=s">s</a>;
<a name="L2122" href="source/net/ipv4/tcp_ipv4.c#L2122">2122</a>         int <a href="ident?i=err">err</a>;
<a name="L2123" href="source/net/ipv4/tcp_ipv4.c#L2123">2123</a> 
<a name="L2124" href="source/net/ipv4/tcp_ipv4.c#L2124">2124</a>         <a href="ident?i=err">err</a> = <a href="ident?i=seq_open_net">seq_open_net</a>(<a href="ident?i=inode">inode</a>, <a href="ident?i=file">file</a>, &amp;afinfo-&gt;seq_ops,
<a name="L2125" href="source/net/ipv4/tcp_ipv4.c#L2125">2125</a>                           sizeof(struct <a href="ident?i=tcp_iter_state">tcp_iter_state</a>));
<a name="L2126" href="source/net/ipv4/tcp_ipv4.c#L2126">2126</a>         if (<a href="ident?i=err">err</a> &lt; 0)
<a name="L2127" href="source/net/ipv4/tcp_ipv4.c#L2127">2127</a>                 return <a href="ident?i=err">err</a>;
<a name="L2128" href="source/net/ipv4/tcp_ipv4.c#L2128">2128</a> 
<a name="L2129" href="source/net/ipv4/tcp_ipv4.c#L2129">2129</a>         <a href="ident?i=s">s</a> = ((struct <a href="ident?i=seq_file">seq_file</a> *)<a href="ident?i=file">file</a>-&gt;<a href="ident?i=private_data">private_data</a>)-&gt;<a href="ident?i=private">private</a>;
<a name="L2130" href="source/net/ipv4/tcp_ipv4.c#L2130">2130</a>         <a href="ident?i=s">s</a>-&gt;<a href="ident?i=family">family</a>               = afinfo-&gt;<a href="ident?i=family">family</a>;
<a name="L2131" href="source/net/ipv4/tcp_ipv4.c#L2131">2131</a>         <a href="ident?i=s">s</a>-&gt;last_pos             = 0;
<a name="L2132" href="source/net/ipv4/tcp_ipv4.c#L2132">2132</a>         return 0;
<a name="L2133" href="source/net/ipv4/tcp_ipv4.c#L2133">2133</a> }
<a name="L2134" href="source/net/ipv4/tcp_ipv4.c#L2134">2134</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=tcp_seq_open">tcp_seq_open</a>);
<a name="L2135" href="source/net/ipv4/tcp_ipv4.c#L2135">2135</a> 
<a name="L2136" href="source/net/ipv4/tcp_ipv4.c#L2136">2136</a> int <a href="ident?i=tcp_proc_register">tcp_proc_register</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>, struct <a href="ident?i=tcp_seq_afinfo">tcp_seq_afinfo</a> *afinfo)
<a name="L2137" href="source/net/ipv4/tcp_ipv4.c#L2137">2137</a> {
<a name="L2138" href="source/net/ipv4/tcp_ipv4.c#L2138">2138</a>         int <a href="ident?i=rc">rc</a> = 0;
<a name="L2139" href="source/net/ipv4/tcp_ipv4.c#L2139">2139</a>         struct <a href="ident?i=proc_dir_entry">proc_dir_entry</a> *<a href="ident?i=p">p</a>;
<a name="L2140" href="source/net/ipv4/tcp_ipv4.c#L2140">2140</a> 
<a name="L2141" href="source/net/ipv4/tcp_ipv4.c#L2141">2141</a>         afinfo-&gt;seq_ops.<a href="ident?i=start">start</a>           = <a href="ident?i=tcp_seq_start">tcp_seq_start</a>;
<a name="L2142" href="source/net/ipv4/tcp_ipv4.c#L2142">2142</a>         afinfo-&gt;seq_ops.<a href="ident?i=next">next</a>            = <a href="ident?i=tcp_seq_next">tcp_seq_next</a>;
<a name="L2143" href="source/net/ipv4/tcp_ipv4.c#L2143">2143</a>         afinfo-&gt;seq_ops.<a href="ident?i=stop">stop</a>            = <a href="ident?i=tcp_seq_stop">tcp_seq_stop</a>;
<a name="L2144" href="source/net/ipv4/tcp_ipv4.c#L2144">2144</a> 
<a name="L2145" href="source/net/ipv4/tcp_ipv4.c#L2145">2145</a>         <a href="ident?i=p">p</a> = <a href="ident?i=proc_create_data">proc_create_data</a>(afinfo-&gt;<a href="ident?i=name">name</a>, <a href="ident?i=S_IRUGO">S_IRUGO</a>, <a href="ident?i=net">net</a>-&gt;proc_net,
<a name="L2146" href="source/net/ipv4/tcp_ipv4.c#L2146">2146</a>                              afinfo-&gt;seq_fops, afinfo);
<a name="L2147" href="source/net/ipv4/tcp_ipv4.c#L2147">2147</a>         if (!<a href="ident?i=p">p</a>)
<a name="L2148" href="source/net/ipv4/tcp_ipv4.c#L2148">2148</a>                 <a href="ident?i=rc">rc</a> = -<a href="ident?i=ENOMEM">ENOMEM</a>;
<a name="L2149" href="source/net/ipv4/tcp_ipv4.c#L2149">2149</a>         return <a href="ident?i=rc">rc</a>;
<a name="L2150" href="source/net/ipv4/tcp_ipv4.c#L2150">2150</a> }
<a name="L2151" href="source/net/ipv4/tcp_ipv4.c#L2151">2151</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=tcp_proc_register">tcp_proc_register</a>);
<a name="L2152" href="source/net/ipv4/tcp_ipv4.c#L2152">2152</a> 
<a name="L2153" href="source/net/ipv4/tcp_ipv4.c#L2153">2153</a> void <a href="ident?i=tcp_proc_unregister">tcp_proc_unregister</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>, struct <a href="ident?i=tcp_seq_afinfo">tcp_seq_afinfo</a> *afinfo)
<a name="L2154" href="source/net/ipv4/tcp_ipv4.c#L2154">2154</a> {
<a name="L2155" href="source/net/ipv4/tcp_ipv4.c#L2155">2155</a>         <a href="ident?i=remove_proc_entry">remove_proc_entry</a>(afinfo-&gt;<a href="ident?i=name">name</a>, <a href="ident?i=net">net</a>-&gt;proc_net);
<a name="L2156" href="source/net/ipv4/tcp_ipv4.c#L2156">2156</a> }
<a name="L2157" href="source/net/ipv4/tcp_ipv4.c#L2157">2157</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=tcp_proc_unregister">tcp_proc_unregister</a>);
<a name="L2158" href="source/net/ipv4/tcp_ipv4.c#L2158">2158</a> 
<a name="L2159" href="source/net/ipv4/tcp_ipv4.c#L2159">2159</a> static void <a href="ident?i=get_openreq4">get_openreq4</a>(const struct <a href="ident?i=request_sock">request_sock</a> *<a href="ident?i=req">req</a>,
<a name="L2160" href="source/net/ipv4/tcp_ipv4.c#L2160">2160</a>                          struct <a href="ident?i=seq_file">seq_file</a> *<a href="ident?i=f">f</a>, int <a href="ident?i=i">i</a>, <a href="ident?i=kuid_t">kuid_t</a> <a href="ident?i=uid">uid</a>)
<a name="L2161" href="source/net/ipv4/tcp_ipv4.c#L2161">2161</a> {
<a name="L2162" href="source/net/ipv4/tcp_ipv4.c#L2162">2162</a>         const struct <a href="ident?i=inet_request_sock">inet_request_sock</a> *ireq = <a href="ident?i=inet_rsk">inet_rsk</a>(<a href="ident?i=req">req</a>);
<a name="L2163" href="source/net/ipv4/tcp_ipv4.c#L2163">2163</a>         long <a href="ident?i=delta">delta</a> = <a href="ident?i=req">req</a>-&gt;rsk_timer.expires - <a href="ident?i=jiffies">jiffies</a>;
<a name="L2164" href="source/net/ipv4/tcp_ipv4.c#L2164">2164</a> 
<a name="L2165" href="source/net/ipv4/tcp_ipv4.c#L2165">2165</a>         <a href="ident?i=seq_printf">seq_printf</a>(<a href="ident?i=f">f</a>, <i>"%4d: %08X:%04X %08X:%04X"</i>
<a name="L2166" href="source/net/ipv4/tcp_ipv4.c#L2166">2166</a>                 <i>" %02X %08X:%08X %02X:%08lX %08X %5u %8d %u %d %pK"</i>,
<a name="L2167" href="source/net/ipv4/tcp_ipv4.c#L2167">2167</a>                 <a href="ident?i=i">i</a>,
<a name="L2168" href="source/net/ipv4/tcp_ipv4.c#L2168">2168</a>                 ireq-&gt;<a href="ident?i=ir_loc_addr">ir_loc_addr</a>,
<a name="L2169" href="source/net/ipv4/tcp_ipv4.c#L2169">2169</a>                 ireq-&gt;<a href="ident?i=ir_num">ir_num</a>,
<a name="L2170" href="source/net/ipv4/tcp_ipv4.c#L2170">2170</a>                 ireq-&gt;<a href="ident?i=ir_rmt_addr">ir_rmt_addr</a>,
<a name="L2171" href="source/net/ipv4/tcp_ipv4.c#L2171">2171</a>                 <a href="ident?i=ntohs">ntohs</a>(ireq-&gt;<a href="ident?i=ir_rmt_port">ir_rmt_port</a>),
<a name="L2172" href="source/net/ipv4/tcp_ipv4.c#L2172">2172</a>                 TCP_SYN_RECV,
<a name="L2173" href="source/net/ipv4/tcp_ipv4.c#L2173">2173</a>                 0, 0, <b><i>/* could print option size, but that is af dependent. */</i></b>
<a name="L2174" href="source/net/ipv4/tcp_ipv4.c#L2174">2174</a>                 1,    <b><i>/* timers active (only the expire timer) */</i></b>
<a name="L2175" href="source/net/ipv4/tcp_ipv4.c#L2175">2175</a>                 <a href="ident?i=jiffies_delta_to_clock_t">jiffies_delta_to_clock_t</a>(<a href="ident?i=delta">delta</a>),
<a name="L2176" href="source/net/ipv4/tcp_ipv4.c#L2176">2176</a>                 <a href="ident?i=req">req</a>-&gt;num_timeout,
<a name="L2177" href="source/net/ipv4/tcp_ipv4.c#L2177">2177</a>                 <a href="ident?i=from_kuid_munged">from_kuid_munged</a>(<a href="ident?i=seq_user_ns">seq_user_ns</a>(<a href="ident?i=f">f</a>), <a href="ident?i=uid">uid</a>),
<a name="L2178" href="source/net/ipv4/tcp_ipv4.c#L2178">2178</a>                 0,  <b><i>/* non standard timer */</i></b>
<a name="L2179" href="source/net/ipv4/tcp_ipv4.c#L2179">2179</a>                 0, <b><i>/* open_requests have no inode */</i></b>
<a name="L2180" href="source/net/ipv4/tcp_ipv4.c#L2180">2180</a>                 0,
<a name="L2181" href="source/net/ipv4/tcp_ipv4.c#L2181">2181</a>                 <a href="ident?i=req">req</a>);
<a name="L2182" href="source/net/ipv4/tcp_ipv4.c#L2182">2182</a> }
<a name="L2183" href="source/net/ipv4/tcp_ipv4.c#L2183">2183</a> 
<a name="L2184" href="source/net/ipv4/tcp_ipv4.c#L2184">2184</a> static void <a href="ident?i=get_tcp4_sock">get_tcp4_sock</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=seq_file">seq_file</a> *<a href="ident?i=f">f</a>, int <a href="ident?i=i">i</a>)
<a name="L2185" href="source/net/ipv4/tcp_ipv4.c#L2185">2185</a> {
<a name="L2186" href="source/net/ipv4/tcp_ipv4.c#L2186">2186</a>         int timer_active;
<a name="L2187" href="source/net/ipv4/tcp_ipv4.c#L2187">2187</a>         unsigned long timer_expires;
<a name="L2188" href="source/net/ipv4/tcp_ipv4.c#L2188">2188</a>         const struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L2189" href="source/net/ipv4/tcp_ipv4.c#L2189">2189</a>         const struct <a href="ident?i=inet_connection_sock">inet_connection_sock</a> *icsk = <a href="ident?i=inet_csk">inet_csk</a>(sk);
<a name="L2190" href="source/net/ipv4/tcp_ipv4.c#L2190">2190</a>         const struct <a href="ident?i=inet_sock">inet_sock</a> *inet = <a href="ident?i=inet_sk">inet_sk</a>(sk);
<a name="L2191" href="source/net/ipv4/tcp_ipv4.c#L2191">2191</a>         struct <a href="ident?i=fastopen_queue">fastopen_queue</a> *fastopenq = icsk-&gt;icsk_accept_queue.fastopenq;
<a name="L2192" href="source/net/ipv4/tcp_ipv4.c#L2192">2192</a>         <a href="ident?i=__be32">__be32</a> <a href="ident?i=dest">dest</a> = inet-&gt;<a href="ident?i=inet_daddr">inet_daddr</a>;
<a name="L2193" href="source/net/ipv4/tcp_ipv4.c#L2193">2193</a>         <a href="ident?i=__be32">__be32</a> <a href="ident?i=src">src</a> = inet-&gt;<a href="ident?i=inet_rcv_saddr">inet_rcv_saddr</a>;
<a name="L2194" href="source/net/ipv4/tcp_ipv4.c#L2194">2194</a>         <a href="ident?i=__u16">__u16</a> destp = <a href="ident?i=ntohs">ntohs</a>(inet-&gt;<a href="ident?i=inet_dport">inet_dport</a>);
<a name="L2195" href="source/net/ipv4/tcp_ipv4.c#L2195">2195</a>         <a href="ident?i=__u16">__u16</a> srcp = <a href="ident?i=ntohs">ntohs</a>(inet-&gt;inet_sport);
<a name="L2196" href="source/net/ipv4/tcp_ipv4.c#L2196">2196</a>         int <a href="ident?i=rx_queue">rx_queue</a>;
<a name="L2197" href="source/net/ipv4/tcp_ipv4.c#L2197">2197</a> 
<a name="L2198" href="source/net/ipv4/tcp_ipv4.c#L2198">2198</a>         if (icsk-&gt;icsk_pending == <a href="ident?i=ICSK_TIME_RETRANS">ICSK_TIME_RETRANS</a> ||
<a name="L2199" href="source/net/ipv4/tcp_ipv4.c#L2199">2199</a>             icsk-&gt;icsk_pending == <a href="ident?i=ICSK_TIME_EARLY_RETRANS">ICSK_TIME_EARLY_RETRANS</a> ||
<a name="L2200" href="source/net/ipv4/tcp_ipv4.c#L2200">2200</a>             icsk-&gt;icsk_pending == <a href="ident?i=ICSK_TIME_LOSS_PROBE">ICSK_TIME_LOSS_PROBE</a>) {
<a name="L2201" href="source/net/ipv4/tcp_ipv4.c#L2201">2201</a>                 timer_active    = 1;
<a name="L2202" href="source/net/ipv4/tcp_ipv4.c#L2202">2202</a>                 timer_expires   = icsk-&gt;icsk_timeout;
<a name="L2203" href="source/net/ipv4/tcp_ipv4.c#L2203">2203</a>         } else if (icsk-&gt;icsk_pending == <a href="ident?i=ICSK_TIME_PROBE0">ICSK_TIME_PROBE0</a>) {
<a name="L2204" href="source/net/ipv4/tcp_ipv4.c#L2204">2204</a>                 timer_active    = 4;
<a name="L2205" href="source/net/ipv4/tcp_ipv4.c#L2205">2205</a>                 timer_expires   = icsk-&gt;icsk_timeout;
<a name="L2206" href="source/net/ipv4/tcp_ipv4.c#L2206">2206</a>         } else if (<a href="ident?i=timer_pending">timer_pending</a>(&amp;sk-&gt;sk_timer)) {
<a name="L2207" href="source/net/ipv4/tcp_ipv4.c#L2207">2207</a>                 timer_active    = 2;
<a name="L2208" href="source/net/ipv4/tcp_ipv4.c#L2208">2208</a>                 timer_expires   = sk-&gt;sk_timer.expires;
<a name="L2209" href="source/net/ipv4/tcp_ipv4.c#L2209">2209</a>         } else {
<a name="L2210" href="source/net/ipv4/tcp_ipv4.c#L2210">2210</a>                 timer_active    = 0;
<a name="L2211" href="source/net/ipv4/tcp_ipv4.c#L2211">2211</a>                 timer_expires = <a href="ident?i=jiffies">jiffies</a>;
<a name="L2212" href="source/net/ipv4/tcp_ipv4.c#L2212">2212</a>         }
<a name="L2213" href="source/net/ipv4/tcp_ipv4.c#L2213">2213</a> 
<a name="L2214" href="source/net/ipv4/tcp_ipv4.c#L2214">2214</a>         if (sk-&gt;<a href="ident?i=sk_state">sk_state</a> == TCP_LISTEN)
<a name="L2215" href="source/net/ipv4/tcp_ipv4.c#L2215">2215</a>                 <a href="ident?i=rx_queue">rx_queue</a> = sk-&gt;sk_ack_backlog;
<a name="L2216" href="source/net/ipv4/tcp_ipv4.c#L2216">2216</a>         else
<a name="L2217" href="source/net/ipv4/tcp_ipv4.c#L2217">2217</a>                 <b><i>/*</i></b>
<a name="L2218" href="source/net/ipv4/tcp_ipv4.c#L2218">2218</a> <b><i>                 * because we dont lock socket, we might find a transient negative value</i></b>
<a name="L2219" href="source/net/ipv4/tcp_ipv4.c#L2219">2219</a> <b><i>                 */</i></b>
<a name="L2220" href="source/net/ipv4/tcp_ipv4.c#L2220">2220</a>                 <a href="ident?i=rx_queue">rx_queue</a> = <a href="ident?i=max_t">max_t</a>(int, <a href="ident?i=tp">tp</a>-&gt;rcv_nxt - <a href="ident?i=tp">tp</a>-&gt;copied_seq, 0);
<a name="L2221" href="source/net/ipv4/tcp_ipv4.c#L2221">2221</a> 
<a name="L2222" href="source/net/ipv4/tcp_ipv4.c#L2222">2222</a>         <a href="ident?i=seq_printf">seq_printf</a>(<a href="ident?i=f">f</a>, <i>"%4d: %08X:%04X %08X:%04X %02X %08X:%08X %02X:%08lX "</i>
<a name="L2223" href="source/net/ipv4/tcp_ipv4.c#L2223">2223</a>                         <i>"%08X %5u %8d %lu %d %pK %lu %lu %u %u %d"</i>,
<a name="L2224" href="source/net/ipv4/tcp_ipv4.c#L2224">2224</a>                 <a href="ident?i=i">i</a>, <a href="ident?i=src">src</a>, srcp, <a href="ident?i=dest">dest</a>, destp, sk-&gt;<a href="ident?i=sk_state">sk_state</a>,
<a name="L2225" href="source/net/ipv4/tcp_ipv4.c#L2225">2225</a>                 <a href="ident?i=tp">tp</a>-&gt;write_seq - <a href="ident?i=tp">tp</a>-&gt;snd_una,
<a name="L2226" href="source/net/ipv4/tcp_ipv4.c#L2226">2226</a>                 <a href="ident?i=rx_queue">rx_queue</a>,
<a name="L2227" href="source/net/ipv4/tcp_ipv4.c#L2227">2227</a>                 timer_active,
<a name="L2228" href="source/net/ipv4/tcp_ipv4.c#L2228">2228</a>                 <a href="ident?i=jiffies_delta_to_clock_t">jiffies_delta_to_clock_t</a>(timer_expires - <a href="ident?i=jiffies">jiffies</a>),
<a name="L2229" href="source/net/ipv4/tcp_ipv4.c#L2229">2229</a>                 icsk-&gt;icsk_retransmits,
<a name="L2230" href="source/net/ipv4/tcp_ipv4.c#L2230">2230</a>                 <a href="ident?i=from_kuid_munged">from_kuid_munged</a>(<a href="ident?i=seq_user_ns">seq_user_ns</a>(<a href="ident?i=f">f</a>), <a href="ident?i=sock_i_uid">sock_i_uid</a>(sk)),
<a name="L2231" href="source/net/ipv4/tcp_ipv4.c#L2231">2231</a>                 icsk-&gt;icsk_probes_out,
<a name="L2232" href="source/net/ipv4/tcp_ipv4.c#L2232">2232</a>                 <a href="ident?i=sock_i_ino">sock_i_ino</a>(sk),
<a name="L2233" href="source/net/ipv4/tcp_ipv4.c#L2233">2233</a>                 <a href="ident?i=atomic_read">atomic_read</a>(&amp;sk-&gt;<a href="ident?i=sk_refcnt">sk_refcnt</a>), sk,
<a name="L2234" href="source/net/ipv4/tcp_ipv4.c#L2234">2234</a>                 <a href="ident?i=jiffies_to_clock_t">jiffies_to_clock_t</a>(icsk-&gt;icsk_rto),
<a name="L2235" href="source/net/ipv4/tcp_ipv4.c#L2235">2235</a>                 <a href="ident?i=jiffies_to_clock_t">jiffies_to_clock_t</a>(icsk-&gt;icsk_ack.ato),
<a name="L2236" href="source/net/ipv4/tcp_ipv4.c#L2236">2236</a>                 (icsk-&gt;icsk_ack.quick &lt;&lt; 1) | icsk-&gt;icsk_ack.pingpong,
<a name="L2237" href="source/net/ipv4/tcp_ipv4.c#L2237">2237</a>                 <a href="ident?i=tp">tp</a>-&gt;snd_cwnd,
<a name="L2238" href="source/net/ipv4/tcp_ipv4.c#L2238">2238</a>                 sk-&gt;<a href="ident?i=sk_state">sk_state</a> == TCP_LISTEN ?
<a name="L2239" href="source/net/ipv4/tcp_ipv4.c#L2239">2239</a>                     (fastopenq ? fastopenq-&gt;max_qlen : 0) :
<a name="L2240" href="source/net/ipv4/tcp_ipv4.c#L2240">2240</a>                     (<a href="ident?i=tcp_in_initial_slowstart">tcp_in_initial_slowstart</a>(<a href="ident?i=tp">tp</a>) ? -1 : <a href="ident?i=tp">tp</a>-&gt;snd_ssthresh));
<a name="L2241" href="source/net/ipv4/tcp_ipv4.c#L2241">2241</a> }
<a name="L2242" href="source/net/ipv4/tcp_ipv4.c#L2242">2242</a> 
<a name="L2243" href="source/net/ipv4/tcp_ipv4.c#L2243">2243</a> static void <a href="ident?i=get_timewait4_sock">get_timewait4_sock</a>(const struct <a href="ident?i=inet_timewait_sock">inet_timewait_sock</a> *<a href="ident?i=tw">tw</a>,
<a name="L2244" href="source/net/ipv4/tcp_ipv4.c#L2244">2244</a>                                struct <a href="ident?i=seq_file">seq_file</a> *<a href="ident?i=f">f</a>, int <a href="ident?i=i">i</a>)
<a name="L2245" href="source/net/ipv4/tcp_ipv4.c#L2245">2245</a> {
<a name="L2246" href="source/net/ipv4/tcp_ipv4.c#L2246">2246</a>         long <a href="ident?i=delta">delta</a> = <a href="ident?i=tw">tw</a>-&gt;tw_timer.expires - <a href="ident?i=jiffies">jiffies</a>;
<a name="L2247" href="source/net/ipv4/tcp_ipv4.c#L2247">2247</a>         <a href="ident?i=__be32">__be32</a> <a href="ident?i=dest">dest</a>, <a href="ident?i=src">src</a>;
<a name="L2248" href="source/net/ipv4/tcp_ipv4.c#L2248">2248</a>         <a href="ident?i=__u16">__u16</a> destp, srcp;
<a name="L2249" href="source/net/ipv4/tcp_ipv4.c#L2249">2249</a> 
<a name="L2250" href="source/net/ipv4/tcp_ipv4.c#L2250">2250</a>         <a href="ident?i=dest">dest</a>  = <a href="ident?i=tw">tw</a>-&gt;<a href="ident?i=tw_daddr">tw_daddr</a>;
<a name="L2251" href="source/net/ipv4/tcp_ipv4.c#L2251">2251</a>         <a href="ident?i=src">src</a>   = <a href="ident?i=tw">tw</a>-&gt;<a href="ident?i=tw_rcv_saddr">tw_rcv_saddr</a>;
<a name="L2252" href="source/net/ipv4/tcp_ipv4.c#L2252">2252</a>         destp = <a href="ident?i=ntohs">ntohs</a>(<a href="ident?i=tw">tw</a>-&gt;<a href="ident?i=tw_dport">tw_dport</a>);
<a name="L2253" href="source/net/ipv4/tcp_ipv4.c#L2253">2253</a>         srcp  = <a href="ident?i=ntohs">ntohs</a>(<a href="ident?i=tw">tw</a>-&gt;tw_sport);
<a name="L2254" href="source/net/ipv4/tcp_ipv4.c#L2254">2254</a> 
<a name="L2255" href="source/net/ipv4/tcp_ipv4.c#L2255">2255</a>         <a href="ident?i=seq_printf">seq_printf</a>(<a href="ident?i=f">f</a>, <i>"%4d: %08X:%04X %08X:%04X"</i>
<a name="L2256" href="source/net/ipv4/tcp_ipv4.c#L2256">2256</a>                 <i>" %02X %08X:%08X %02X:%08lX %08X %5d %8d %d %d %pK"</i>,
<a name="L2257" href="source/net/ipv4/tcp_ipv4.c#L2257">2257</a>                 <a href="ident?i=i">i</a>, <a href="ident?i=src">src</a>, srcp, <a href="ident?i=dest">dest</a>, destp, <a href="ident?i=tw">tw</a>-&gt;tw_substate, 0, 0,
<a name="L2258" href="source/net/ipv4/tcp_ipv4.c#L2258">2258</a>                 3, <a href="ident?i=jiffies_delta_to_clock_t">jiffies_delta_to_clock_t</a>(<a href="ident?i=delta">delta</a>), 0, 0, 0, 0,
<a name="L2259" href="source/net/ipv4/tcp_ipv4.c#L2259">2259</a>                 <a href="ident?i=atomic_read">atomic_read</a>(&amp;<a href="ident?i=tw">tw</a>-&gt;<a href="ident?i=tw_refcnt">tw_refcnt</a>), <a href="ident?i=tw">tw</a>);
<a name="L2260" href="source/net/ipv4/tcp_ipv4.c#L2260">2260</a> }
<a name="L2261" href="source/net/ipv4/tcp_ipv4.c#L2261">2261</a> 
<a name="L2262" href="source/net/ipv4/tcp_ipv4.c#L2262">2262</a> #define <a href="ident?i=TMPSZ">TMPSZ</a> 150
<a name="L2263" href="source/net/ipv4/tcp_ipv4.c#L2263">2263</a> 
<a name="L2264" href="source/net/ipv4/tcp_ipv4.c#L2264">2264</a> static int <a href="ident?i=tcp4_seq_show">tcp4_seq_show</a>(struct <a href="ident?i=seq_file">seq_file</a> *<a href="ident?i=seq">seq</a>, void *<a href="ident?i=v">v</a>)
<a name="L2265" href="source/net/ipv4/tcp_ipv4.c#L2265">2265</a> {
<a name="L2266" href="source/net/ipv4/tcp_ipv4.c#L2266">2266</a>         struct <a href="ident?i=tcp_iter_state">tcp_iter_state</a> *<a href="ident?i=st">st</a>;
<a name="L2267" href="source/net/ipv4/tcp_ipv4.c#L2267">2267</a>         struct <a href="ident?i=sock">sock</a> *sk = <a href="ident?i=v">v</a>;
<a name="L2268" href="source/net/ipv4/tcp_ipv4.c#L2268">2268</a> 
<a name="L2269" href="source/net/ipv4/tcp_ipv4.c#L2269">2269</a>         <a href="ident?i=seq_setwidth">seq_setwidth</a>(<a href="ident?i=seq">seq</a>, <a href="ident?i=TMPSZ">TMPSZ</a> - 1);
<a name="L2270" href="source/net/ipv4/tcp_ipv4.c#L2270">2270</a>         if (<a href="ident?i=v">v</a> == <a href="ident?i=SEQ_START_TOKEN">SEQ_START_TOKEN</a>) {
<a name="L2271" href="source/net/ipv4/tcp_ipv4.c#L2271">2271</a>                 <a href="ident?i=seq_puts">seq_puts</a>(<a href="ident?i=seq">seq</a>, <i>"  sl  local_address rem_address   st tx_queue "</i>
<a name="L2272" href="source/net/ipv4/tcp_ipv4.c#L2272">2272</a>                            <i>"rx_queue tr tm-&gt;when retrnsmt   uid  timeout "</i>
<a name="L2273" href="source/net/ipv4/tcp_ipv4.c#L2273">2273</a>                            <i>"inode"</i>);
<a name="L2274" href="source/net/ipv4/tcp_ipv4.c#L2274">2274</a>                 goto <a href="ident?i=out">out</a>;
<a name="L2275" href="source/net/ipv4/tcp_ipv4.c#L2275">2275</a>         }
<a name="L2276" href="source/net/ipv4/tcp_ipv4.c#L2276">2276</a>         <a href="ident?i=st">st</a> = <a href="ident?i=seq">seq</a>-&gt;<a href="ident?i=private">private</a>;
<a name="L2277" href="source/net/ipv4/tcp_ipv4.c#L2277">2277</a> 
<a name="L2278" href="source/net/ipv4/tcp_ipv4.c#L2278">2278</a>         switch (<a href="ident?i=st">st</a>-&gt;<a href="ident?i=state">state</a>) {
<a name="L2279" href="source/net/ipv4/tcp_ipv4.c#L2279">2279</a>         case TCP_SEQ_STATE_LISTENING:
<a name="L2280" href="source/net/ipv4/tcp_ipv4.c#L2280">2280</a>         case TCP_SEQ_STATE_ESTABLISHED:
<a name="L2281" href="source/net/ipv4/tcp_ipv4.c#L2281">2281</a>                 if (sk-&gt;<a href="ident?i=sk_state">sk_state</a> == TCP_TIME_WAIT)
<a name="L2282" href="source/net/ipv4/tcp_ipv4.c#L2282">2282</a>                         <a href="ident?i=get_timewait4_sock">get_timewait4_sock</a>(<a href="ident?i=v">v</a>, <a href="ident?i=seq">seq</a>, <a href="ident?i=st">st</a>-&gt;<a href="ident?i=num">num</a>);
<a name="L2283" href="source/net/ipv4/tcp_ipv4.c#L2283">2283</a>                 else
<a name="L2284" href="source/net/ipv4/tcp_ipv4.c#L2284">2284</a>                         <a href="ident?i=get_tcp4_sock">get_tcp4_sock</a>(<a href="ident?i=v">v</a>, <a href="ident?i=seq">seq</a>, <a href="ident?i=st">st</a>-&gt;<a href="ident?i=num">num</a>);
<a name="L2285" href="source/net/ipv4/tcp_ipv4.c#L2285">2285</a>                 break;
<a name="L2286" href="source/net/ipv4/tcp_ipv4.c#L2286">2286</a>         case TCP_SEQ_STATE_OPENREQ:
<a name="L2287" href="source/net/ipv4/tcp_ipv4.c#L2287">2287</a>                 <a href="ident?i=get_openreq4">get_openreq4</a>(<a href="ident?i=v">v</a>, <a href="ident?i=seq">seq</a>, <a href="ident?i=st">st</a>-&gt;<a href="ident?i=num">num</a>, <a href="ident?i=st">st</a>-&gt;<a href="ident?i=uid">uid</a>);
<a name="L2288" href="source/net/ipv4/tcp_ipv4.c#L2288">2288</a>                 break;
<a name="L2289" href="source/net/ipv4/tcp_ipv4.c#L2289">2289</a>         }
<a name="L2290" href="source/net/ipv4/tcp_ipv4.c#L2290">2290</a> <a href="ident?i=out">out</a>:
<a name="L2291" href="source/net/ipv4/tcp_ipv4.c#L2291">2291</a>         <a href="ident?i=seq_pad">seq_pad</a>(<a href="ident?i=seq">seq</a>, <i>'\n'</i>);
<a name="L2292" href="source/net/ipv4/tcp_ipv4.c#L2292">2292</a>         return 0;
<a name="L2293" href="source/net/ipv4/tcp_ipv4.c#L2293">2293</a> }
<a name="L2294" href="source/net/ipv4/tcp_ipv4.c#L2294">2294</a> 
<a name="L2295" href="source/net/ipv4/tcp_ipv4.c#L2295">2295</a> static const struct <a href="ident?i=file_operations">file_operations</a> <a href="ident?i=tcp_afinfo_seq_fops">tcp_afinfo_seq_fops</a> = {
<a name="L2296" href="source/net/ipv4/tcp_ipv4.c#L2296">2296</a>         .owner   = <a href="ident?i=THIS_MODULE">THIS_MODULE</a>,
<a name="L2297" href="source/net/ipv4/tcp_ipv4.c#L2297">2297</a>         .<a href="ident?i=open">open</a>    = <a href="ident?i=tcp_seq_open">tcp_seq_open</a>,
<a name="L2298" href="source/net/ipv4/tcp_ipv4.c#L2298">2298</a>         .<a href="ident?i=read">read</a>    = <a href="ident?i=seq_read">seq_read</a>,
<a name="L2299" href="source/net/ipv4/tcp_ipv4.c#L2299">2299</a>         .llseek  = <a href="ident?i=seq_lseek">seq_lseek</a>,
<a name="L2300" href="source/net/ipv4/tcp_ipv4.c#L2300">2300</a>         .<a href="ident?i=release">release</a> = <a href="ident?i=seq_release_net">seq_release_net</a>
<a name="L2301" href="source/net/ipv4/tcp_ipv4.c#L2301">2301</a> };
<a name="L2302" href="source/net/ipv4/tcp_ipv4.c#L2302">2302</a> 
<a name="L2303" href="source/net/ipv4/tcp_ipv4.c#L2303">2303</a> static struct <a href="ident?i=tcp_seq_afinfo">tcp_seq_afinfo</a> <a href="ident?i=tcp4_seq_afinfo">tcp4_seq_afinfo</a> = {
<a name="L2304" href="source/net/ipv4/tcp_ipv4.c#L2304">2304</a>         .<a href="ident?i=name">name</a>           = <i>"tcp"</i>,
<a name="L2305" href="source/net/ipv4/tcp_ipv4.c#L2305">2305</a>         .<a href="ident?i=family">family</a>         = <a href="ident?i=AF_INET">AF_INET</a>,
<a name="L2306" href="source/net/ipv4/tcp_ipv4.c#L2306">2306</a>         .seq_fops       = &amp;<a href="ident?i=tcp_afinfo_seq_fops">tcp_afinfo_seq_fops</a>,
<a name="L2307" href="source/net/ipv4/tcp_ipv4.c#L2307">2307</a>         .seq_ops        = {
<a name="L2308" href="source/net/ipv4/tcp_ipv4.c#L2308">2308</a>                 .<a href="ident?i=show">show</a>           = <a href="ident?i=tcp4_seq_show">tcp4_seq_show</a>,
<a name="L2309" href="source/net/ipv4/tcp_ipv4.c#L2309">2309</a>         },
<a name="L2310" href="source/net/ipv4/tcp_ipv4.c#L2310">2310</a> };
<a name="L2311" href="source/net/ipv4/tcp_ipv4.c#L2311">2311</a> 
<a name="L2312" href="source/net/ipv4/tcp_ipv4.c#L2312">2312</a> static int <a href="ident?i=__net_init">__net_init</a> <a href="ident?i=tcp4_proc_init_net">tcp4_proc_init_net</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>)
<a name="L2313" href="source/net/ipv4/tcp_ipv4.c#L2313">2313</a> {
<a name="L2314" href="source/net/ipv4/tcp_ipv4.c#L2314">2314</a>         return <a href="ident?i=tcp_proc_register">tcp_proc_register</a>(<a href="ident?i=net">net</a>, &amp;<a href="ident?i=tcp4_seq_afinfo">tcp4_seq_afinfo</a>);
<a name="L2315" href="source/net/ipv4/tcp_ipv4.c#L2315">2315</a> }
<a name="L2316" href="source/net/ipv4/tcp_ipv4.c#L2316">2316</a> 
<a name="L2317" href="source/net/ipv4/tcp_ipv4.c#L2317">2317</a> static void <a href="ident?i=__net_exit">__net_exit</a> <a href="ident?i=tcp4_proc_exit_net">tcp4_proc_exit_net</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>)
<a name="L2318" href="source/net/ipv4/tcp_ipv4.c#L2318">2318</a> {
<a name="L2319" href="source/net/ipv4/tcp_ipv4.c#L2319">2319</a>         <a href="ident?i=tcp_proc_unregister">tcp_proc_unregister</a>(<a href="ident?i=net">net</a>, &amp;<a href="ident?i=tcp4_seq_afinfo">tcp4_seq_afinfo</a>);
<a name="L2320" href="source/net/ipv4/tcp_ipv4.c#L2320">2320</a> }
<a name="L2321" href="source/net/ipv4/tcp_ipv4.c#L2321">2321</a> 
<a name="L2322" href="source/net/ipv4/tcp_ipv4.c#L2322">2322</a> static struct <a href="ident?i=pernet_operations">pernet_operations</a> <a href="ident?i=tcp4_net_ops">tcp4_net_ops</a> = {
<a name="L2323" href="source/net/ipv4/tcp_ipv4.c#L2323">2323</a>         .<a href="ident?i=init">init</a> = <a href="ident?i=tcp4_proc_init_net">tcp4_proc_init_net</a>,
<a name="L2324" href="source/net/ipv4/tcp_ipv4.c#L2324">2324</a>         .<a href="ident?i=exit">exit</a> = <a href="ident?i=tcp4_proc_exit_net">tcp4_proc_exit_net</a>,
<a name="L2325" href="source/net/ipv4/tcp_ipv4.c#L2325">2325</a> };
<a name="L2326" href="source/net/ipv4/tcp_ipv4.c#L2326">2326</a> 
<a name="L2327" href="source/net/ipv4/tcp_ipv4.c#L2327">2327</a> int <a href="ident?i=__init">__init</a> <a href="ident?i=tcp4_proc_init">tcp4_proc_init</a>(void)
<a name="L2328" href="source/net/ipv4/tcp_ipv4.c#L2328">2328</a> {
<a name="L2329" href="source/net/ipv4/tcp_ipv4.c#L2329">2329</a>         return <a href="ident?i=register_pernet_subsys">register_pernet_subsys</a>(&amp;<a href="ident?i=tcp4_net_ops">tcp4_net_ops</a>);
<a name="L2330" href="source/net/ipv4/tcp_ipv4.c#L2330">2330</a> }
<a name="L2331" href="source/net/ipv4/tcp_ipv4.c#L2331">2331</a> 
<a name="L2332" href="source/net/ipv4/tcp_ipv4.c#L2332">2332</a> void <a href="ident?i=tcp4_proc_exit">tcp4_proc_exit</a>(void)
<a name="L2333" href="source/net/ipv4/tcp_ipv4.c#L2333">2333</a> {
<a name="L2334" href="source/net/ipv4/tcp_ipv4.c#L2334">2334</a>         <a href="ident?i=unregister_pernet_subsys">unregister_pernet_subsys</a>(&amp;<a href="ident?i=tcp4_net_ops">tcp4_net_ops</a>);
<a name="L2335" href="source/net/ipv4/tcp_ipv4.c#L2335">2335</a> }
<a name="L2336" href="source/net/ipv4/tcp_ipv4.c#L2336">2336</a> #endif <b><i>/* CONFIG_PROC_FS */</i></b>
<a name="L2337" href="source/net/ipv4/tcp_ipv4.c#L2337">2337</a> 
<a name="L2338" href="source/net/ipv4/tcp_ipv4.c#L2338">2338</a> struct <a href="ident?i=proto">proto</a> <a href="ident?i=tcp_prot">tcp_prot</a> = {
<a name="L2339" href="source/net/ipv4/tcp_ipv4.c#L2339">2339</a>         .<a href="ident?i=name">name</a>                   = <i>"TCP"</i>,
<a name="L2340" href="source/net/ipv4/tcp_ipv4.c#L2340">2340</a>         .owner                  = <a href="ident?i=THIS_MODULE">THIS_MODULE</a>,
<a name="L2341" href="source/net/ipv4/tcp_ipv4.c#L2341">2341</a>         .<a href="ident?i=close">close</a>                  = <a href="ident?i=tcp_close">tcp_close</a>,
<a name="L2342" href="source/net/ipv4/tcp_ipv4.c#L2342">2342</a>         .<a href="ident?i=connect">connect</a>                = <a href="ident?i=tcp_v4_connect">tcp_v4_connect</a>,
<a name="L2343" href="source/net/ipv4/tcp_ipv4.c#L2343">2343</a>         .<a href="ident?i=disconnect">disconnect</a>             = <a href="ident?i=tcp_disconnect">tcp_disconnect</a>,
<a name="L2344" href="source/net/ipv4/tcp_ipv4.c#L2344">2344</a>         .<a href="ident?i=accept">accept</a>                 = <a href="ident?i=inet_csk_accept">inet_csk_accept</a>,
<a name="L2345" href="source/net/ipv4/tcp_ipv4.c#L2345">2345</a>         .<a href="ident?i=ioctl">ioctl</a>                  = <a href="ident?i=tcp_ioctl">tcp_ioctl</a>,
<a name="L2346" href="source/net/ipv4/tcp_ipv4.c#L2346">2346</a>         .<a href="ident?i=init">init</a>                   = <a href="ident?i=tcp_v4_init_sock">tcp_v4_init_sock</a>,
<a name="L2347" href="source/net/ipv4/tcp_ipv4.c#L2347">2347</a>         .<a href="ident?i=destroy">destroy</a>                = <a href="ident?i=tcp_v4_destroy_sock">tcp_v4_destroy_sock</a>,
<a name="L2348" href="source/net/ipv4/tcp_ipv4.c#L2348">2348</a>         .<a href="ident?i=shutdown">shutdown</a>               = <a href="ident?i=tcp_shutdown">tcp_shutdown</a>,
<a name="L2349" href="source/net/ipv4/tcp_ipv4.c#L2349">2349</a>         .<a href="ident?i=setsockopt">setsockopt</a>             = <a href="ident?i=tcp_setsockopt">tcp_setsockopt</a>,
<a name="L2350" href="source/net/ipv4/tcp_ipv4.c#L2350">2350</a>         .getsockopt             = <a href="ident?i=tcp_getsockopt">tcp_getsockopt</a>,
<a name="L2351" href="source/net/ipv4/tcp_ipv4.c#L2351">2351</a>         .recvmsg                = <a href="ident?i=tcp_recvmsg">tcp_recvmsg</a>,
<a name="L2352" href="source/net/ipv4/tcp_ipv4.c#L2352">2352</a>         .<a href="ident?i=sendmsg">sendmsg</a>                = <a href="ident?i=tcp_sendmsg">tcp_sendmsg</a>,
<a name="L2353" href="source/net/ipv4/tcp_ipv4.c#L2353">2353</a>         .sendpage               = <a href="ident?i=tcp_sendpage">tcp_sendpage</a>,
<a name="L2354" href="source/net/ipv4/tcp_ipv4.c#L2354">2354</a>         .backlog_rcv            = <a href="ident?i=tcp_v4_do_rcv">tcp_v4_do_rcv</a>,
<a name="L2355" href="source/net/ipv4/tcp_ipv4.c#L2355">2355</a>         .release_cb             = <a href="ident?i=tcp_release_cb">tcp_release_cb</a>,
<a name="L2356" href="source/net/ipv4/tcp_ipv4.c#L2356">2356</a>         .<a href="ident?i=hash">hash</a>                   = <a href="ident?i=inet_hash">inet_hash</a>,
<a name="L2357" href="source/net/ipv4/tcp_ipv4.c#L2357">2357</a>         .unhash                 = <a href="ident?i=inet_unhash">inet_unhash</a>,
<a name="L2358" href="source/net/ipv4/tcp_ipv4.c#L2358">2358</a>         .<a href="ident?i=get_port">get_port</a>               = <a href="ident?i=inet_csk_get_port">inet_csk_get_port</a>,
<a name="L2359" href="source/net/ipv4/tcp_ipv4.c#L2359">2359</a>         .enter_memory_pressure  = <a href="ident?i=tcp_enter_memory_pressure">tcp_enter_memory_pressure</a>,
<a name="L2360" href="source/net/ipv4/tcp_ipv4.c#L2360">2360</a>         .stream_memory_free     = <a href="ident?i=tcp_stream_memory_free">tcp_stream_memory_free</a>,
<a name="L2361" href="source/net/ipv4/tcp_ipv4.c#L2361">2361</a>         .sockets_allocated      = &amp;<a href="ident?i=tcp_sockets_allocated">tcp_sockets_allocated</a>,
<a name="L2362" href="source/net/ipv4/tcp_ipv4.c#L2362">2362</a>         .orphan_count           = &amp;<a href="ident?i=tcp_orphan_count">tcp_orphan_count</a>,
<a name="L2363" href="source/net/ipv4/tcp_ipv4.c#L2363">2363</a>         .memory_allocated       = &amp;<a href="ident?i=tcp_memory_allocated">tcp_memory_allocated</a>,
<a name="L2364" href="source/net/ipv4/tcp_ipv4.c#L2364">2364</a>         .memory_pressure        = &amp;<a href="ident?i=tcp_memory_pressure">tcp_memory_pressure</a>,
<a name="L2365" href="source/net/ipv4/tcp_ipv4.c#L2365">2365</a>         .sysctl_mem             = <a href="ident?i=sysctl_tcp_mem">sysctl_tcp_mem</a>,
<a name="L2366" href="source/net/ipv4/tcp_ipv4.c#L2366">2366</a>         .sysctl_wmem            = <a href="ident?i=sysctl_tcp_wmem">sysctl_tcp_wmem</a>,
<a name="L2367" href="source/net/ipv4/tcp_ipv4.c#L2367">2367</a>         .sysctl_rmem            = <a href="ident?i=sysctl_tcp_rmem">sysctl_tcp_rmem</a>,
<a name="L2368" href="source/net/ipv4/tcp_ipv4.c#L2368">2368</a>         .max_header             = <a href="ident?i=MAX_TCP_HEADER">MAX_TCP_HEADER</a>,
<a name="L2369" href="source/net/ipv4/tcp_ipv4.c#L2369">2369</a>         .obj_size               = sizeof(struct <a href="ident?i=tcp_sock">tcp_sock</a>),
<a name="L2370" href="source/net/ipv4/tcp_ipv4.c#L2370">2370</a>         .slab_flags             = <a href="ident?i=SLAB_DESTROY_BY_RCU">SLAB_DESTROY_BY_RCU</a>,
<a name="L2371" href="source/net/ipv4/tcp_ipv4.c#L2371">2371</a>         .twsk_prot              = &amp;<a href="ident?i=tcp_timewait_sock_ops">tcp_timewait_sock_ops</a>,
<a name="L2372" href="source/net/ipv4/tcp_ipv4.c#L2372">2372</a>         .rsk_prot               = &amp;<a href="ident?i=tcp_request_sock_ops">tcp_request_sock_ops</a>,
<a name="L2373" href="source/net/ipv4/tcp_ipv4.c#L2373">2373</a>         .<a href="ident?i=h">h</a>.hashinfo             = &amp;<a href="ident?i=tcp_hashinfo">tcp_hashinfo</a>,
<a name="L2374" href="source/net/ipv4/tcp_ipv4.c#L2374">2374</a>         .no_autobind            = <a href="ident?i=true">true</a>,
<a name="L2375" href="source/net/ipv4/tcp_ipv4.c#L2375">2375</a> #ifdef CONFIG_COMPAT
<a name="L2376" href="source/net/ipv4/tcp_ipv4.c#L2376">2376</a>         .compat_setsockopt      = <a href="ident?i=compat_tcp_setsockopt">compat_tcp_setsockopt</a>,
<a name="L2377" href="source/net/ipv4/tcp_ipv4.c#L2377">2377</a>         .compat_getsockopt      = <a href="ident?i=compat_tcp_getsockopt">compat_tcp_getsockopt</a>,
<a name="L2378" href="source/net/ipv4/tcp_ipv4.c#L2378">2378</a> #endif
<a name="L2379" href="source/net/ipv4/tcp_ipv4.c#L2379">2379</a> #ifdef CONFIG_MEMCG_KMEM
<a name="L2380" href="source/net/ipv4/tcp_ipv4.c#L2380">2380</a>         .init_cgroup            = <a href="ident?i=tcp_init_cgroup">tcp_init_cgroup</a>,
<a name="L2381" href="source/net/ipv4/tcp_ipv4.c#L2381">2381</a>         .destroy_cgroup         = <a href="ident?i=tcp_destroy_cgroup">tcp_destroy_cgroup</a>,
<a name="L2382" href="source/net/ipv4/tcp_ipv4.c#L2382">2382</a>         .proto_cgroup           = <a href="ident?i=tcp_proto_cgroup">tcp_proto_cgroup</a>,
<a name="L2383" href="source/net/ipv4/tcp_ipv4.c#L2383">2383</a> #endif
<a name="L2384" href="source/net/ipv4/tcp_ipv4.c#L2384">2384</a> };
<a name="L2385" href="source/net/ipv4/tcp_ipv4.c#L2385">2385</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=tcp_prot">tcp_prot</a>);
<a name="L2386" href="source/net/ipv4/tcp_ipv4.c#L2386">2386</a> 
<a name="L2387" href="source/net/ipv4/tcp_ipv4.c#L2387">2387</a> static void <a href="ident?i=__net_exit">__net_exit</a> <a href="ident?i=tcp_sk_exit">tcp_sk_exit</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>)
<a name="L2388" href="source/net/ipv4/tcp_ipv4.c#L2388">2388</a> {
<a name="L2389" href="source/net/ipv4/tcp_ipv4.c#L2389">2389</a>         int <a href="ident?i=cpu">cpu</a>;
<a name="L2390" href="source/net/ipv4/tcp_ipv4.c#L2390">2390</a> 
<a name="L2391" href="source/net/ipv4/tcp_ipv4.c#L2391">2391</a>         <a href="ident?i=for_each_possible_cpu">for_each_possible_cpu</a>(<a href="ident?i=cpu">cpu</a>)
<a name="L2392" href="source/net/ipv4/tcp_ipv4.c#L2392">2392</a>                 <a href="ident?i=inet_ctl_sock_destroy">inet_ctl_sock_destroy</a>(*<a href="ident?i=per_cpu_ptr">per_cpu_ptr</a>(<a href="ident?i=net">net</a>-&gt;ipv4.<a href="ident?i=tcp_sk">tcp_sk</a>, <a href="ident?i=cpu">cpu</a>));
<a name="L2393" href="source/net/ipv4/tcp_ipv4.c#L2393">2393</a>         <a href="ident?i=free_percpu">free_percpu</a>(<a href="ident?i=net">net</a>-&gt;ipv4.<a href="ident?i=tcp_sk">tcp_sk</a>);
<a name="L2394" href="source/net/ipv4/tcp_ipv4.c#L2394">2394</a> }
<a name="L2395" href="source/net/ipv4/tcp_ipv4.c#L2395">2395</a> 
<a name="L2396" href="source/net/ipv4/tcp_ipv4.c#L2396">2396</a> static int <a href="ident?i=__net_init">__net_init</a> <a href="ident?i=tcp_sk_init">tcp_sk_init</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>)
<a name="L2397" href="source/net/ipv4/tcp_ipv4.c#L2397">2397</a> {
<a name="L2398" href="source/net/ipv4/tcp_ipv4.c#L2398">2398</a>         int <a href="ident?i=res">res</a>, <a href="ident?i=cpu">cpu</a>;
<a name="L2399" href="source/net/ipv4/tcp_ipv4.c#L2399">2399</a> 
<a name="L2400" href="source/net/ipv4/tcp_ipv4.c#L2400">2400</a>         <a href="ident?i=net">net</a>-&gt;ipv4.<a href="ident?i=tcp_sk">tcp_sk</a> = <a href="ident?i=alloc_percpu">alloc_percpu</a>(struct <a href="ident?i=sock">sock</a> *);
<a name="L2401" href="source/net/ipv4/tcp_ipv4.c#L2401">2401</a>         if (!<a href="ident?i=net">net</a>-&gt;ipv4.<a href="ident?i=tcp_sk">tcp_sk</a>)
<a name="L2402" href="source/net/ipv4/tcp_ipv4.c#L2402">2402</a>                 return -<a href="ident?i=ENOMEM">ENOMEM</a>;
<a name="L2403" href="source/net/ipv4/tcp_ipv4.c#L2403">2403</a> 
<a name="L2404" href="source/net/ipv4/tcp_ipv4.c#L2404">2404</a>         <a href="ident?i=for_each_possible_cpu">for_each_possible_cpu</a>(<a href="ident?i=cpu">cpu</a>) {
<a name="L2405" href="source/net/ipv4/tcp_ipv4.c#L2405">2405</a>                 struct <a href="ident?i=sock">sock</a> *sk;
<a name="L2406" href="source/net/ipv4/tcp_ipv4.c#L2406">2406</a> 
<a name="L2407" href="source/net/ipv4/tcp_ipv4.c#L2407">2407</a>                 <a href="ident?i=res">res</a> = <a href="ident?i=inet_ctl_sock_create">inet_ctl_sock_create</a>(&amp;sk, <a href="ident?i=PF_INET">PF_INET</a>, SOCK_RAW,
<a name="L2408" href="source/net/ipv4/tcp_ipv4.c#L2408">2408</a>                                            <a href="ident?i=IPPROTO_TCP">IPPROTO_TCP</a>, <a href="ident?i=net">net</a>);
<a name="L2409" href="source/net/ipv4/tcp_ipv4.c#L2409">2409</a>                 if (<a href="ident?i=res">res</a>)
<a name="L2410" href="source/net/ipv4/tcp_ipv4.c#L2410">2410</a>                         goto <a href="ident?i=fail">fail</a>;
<a name="L2411" href="source/net/ipv4/tcp_ipv4.c#L2411">2411</a>                 *<a href="ident?i=per_cpu_ptr">per_cpu_ptr</a>(<a href="ident?i=net">net</a>-&gt;ipv4.<a href="ident?i=tcp_sk">tcp_sk</a>, <a href="ident?i=cpu">cpu</a>) = sk;
<a name="L2412" href="source/net/ipv4/tcp_ipv4.c#L2412">2412</a>         }
<a name="L2413" href="source/net/ipv4/tcp_ipv4.c#L2413">2413</a>         <a href="ident?i=net">net</a>-&gt;ipv4.sysctl_tcp_ecn = 2;
<a name="L2414" href="source/net/ipv4/tcp_ipv4.c#L2414">2414</a>         <a href="ident?i=net">net</a>-&gt;ipv4.sysctl_tcp_base_mss = <a href="ident?i=TCP_BASE_MSS">TCP_BASE_MSS</a>;
<a name="L2415" href="source/net/ipv4/tcp_ipv4.c#L2415">2415</a>         <a href="ident?i=net">net</a>-&gt;ipv4.sysctl_tcp_probe_threshold = <a href="ident?i=TCP_PROBE_THRESHOLD">TCP_PROBE_THRESHOLD</a>;
<a name="L2416" href="source/net/ipv4/tcp_ipv4.c#L2416">2416</a>         <a href="ident?i=net">net</a>-&gt;ipv4.sysctl_tcp_probe_interval = <a href="ident?i=TCP_PROBE_INTERVAL">TCP_PROBE_INTERVAL</a>;
<a name="L2417" href="source/net/ipv4/tcp_ipv4.c#L2417">2417</a>         return 0;
<a name="L2418" href="source/net/ipv4/tcp_ipv4.c#L2418">2418</a> 
<a name="L2419" href="source/net/ipv4/tcp_ipv4.c#L2419">2419</a> <a href="ident?i=fail">fail</a>:
<a name="L2420" href="source/net/ipv4/tcp_ipv4.c#L2420">2420</a>         <a href="ident?i=tcp_sk_exit">tcp_sk_exit</a>(<a href="ident?i=net">net</a>);
<a name="L2421" href="source/net/ipv4/tcp_ipv4.c#L2421">2421</a> 
<a name="L2422" href="source/net/ipv4/tcp_ipv4.c#L2422">2422</a>         return <a href="ident?i=res">res</a>;
<a name="L2423" href="source/net/ipv4/tcp_ipv4.c#L2423">2423</a> }
<a name="L2424" href="source/net/ipv4/tcp_ipv4.c#L2424">2424</a> 
<a name="L2425" href="source/net/ipv4/tcp_ipv4.c#L2425">2425</a> static void <a href="ident?i=__net_exit">__net_exit</a> <a href="ident?i=tcp_sk_exit_batch">tcp_sk_exit_batch</a>(struct <a href="ident?i=list_head">list_head</a> *net_exit_list)
<a name="L2426" href="source/net/ipv4/tcp_ipv4.c#L2426">2426</a> {
<a name="L2427" href="source/net/ipv4/tcp_ipv4.c#L2427">2427</a>         <a href="ident?i=inet_twsk_purge">inet_twsk_purge</a>(&amp;<a href="ident?i=tcp_hashinfo">tcp_hashinfo</a>, &amp;<a href="ident?i=tcp_death_row">tcp_death_row</a>, <a href="ident?i=AF_INET">AF_INET</a>);
<a name="L2428" href="source/net/ipv4/tcp_ipv4.c#L2428">2428</a> }
<a name="L2429" href="source/net/ipv4/tcp_ipv4.c#L2429">2429</a> 
<a name="L2430" href="source/net/ipv4/tcp_ipv4.c#L2430">2430</a> static struct <a href="ident?i=pernet_operations">pernet_operations</a> <a href="ident?i=__net_initdata">__net_initdata</a> <a href="ident?i=tcp_sk_ops">tcp_sk_ops</a> = {
<a name="L2431" href="source/net/ipv4/tcp_ipv4.c#L2431">2431</a>        .<a href="ident?i=init">init</a>       = <a href="ident?i=tcp_sk_init">tcp_sk_init</a>,
<a name="L2432" href="source/net/ipv4/tcp_ipv4.c#L2432">2432</a>        .<a href="ident?i=exit">exit</a>       = <a href="ident?i=tcp_sk_exit">tcp_sk_exit</a>,
<a name="L2433" href="source/net/ipv4/tcp_ipv4.c#L2433">2433</a>        .exit_batch = <a href="ident?i=tcp_sk_exit_batch">tcp_sk_exit_batch</a>,
<a name="L2434" href="source/net/ipv4/tcp_ipv4.c#L2434">2434</a> };
<a name="L2435" href="source/net/ipv4/tcp_ipv4.c#L2435">2435</a> 
<a name="L2436" href="source/net/ipv4/tcp_ipv4.c#L2436">2436</a> void <a href="ident?i=__init">__init</a> <a href="ident?i=tcp_v4_init">tcp_v4_init</a>(void)
<a name="L2437" href="source/net/ipv4/tcp_ipv4.c#L2437">2437</a> {
<a name="L2438" href="source/net/ipv4/tcp_ipv4.c#L2438">2438</a>         <a href="ident?i=inet_hashinfo_init">inet_hashinfo_init</a>(&amp;<a href="ident?i=tcp_hashinfo">tcp_hashinfo</a>);
<a name="L2439" href="source/net/ipv4/tcp_ipv4.c#L2439">2439</a>         if (<a href="ident?i=register_pernet_subsys">register_pernet_subsys</a>(&amp;<a href="ident?i=tcp_sk_ops">tcp_sk_ops</a>))
<a name="L2440" href="source/net/ipv4/tcp_ipv4.c#L2440">2440</a>                 <a href="ident?i=panic">panic</a>(<i>"Failed to create the TCP control socket.\n"</i>);
<a name="L2441" href="source/net/ipv4/tcp_ipv4.c#L2441">2441</a> }
<a name="L2442" href="source/net/ipv4/tcp_ipv4.c#L2442">2442</a> </pre></div><p>
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
