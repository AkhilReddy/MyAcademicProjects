<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title>Linux/net/ipv4/udp.c - Linux Cross Reference - Free Electrons</title>
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
		 &nbsp;&bull;&nbsp;<b><i>source navigation</i></b> &nbsp;&bull;&nbsp;<a href="diff/net/ipv4/udp.c">diff markup</a> &nbsp;&bull;&nbsp;<a href="ident">identifier search</a> &nbsp;&bull;&nbsp;<a href="search">freetext search</a> &nbsp;&bull;&nbsp;
		</p>
	</div>
</div>

<div id="topbar">
  
  <p>Version: &nbsp;<a href="source/net/ipv4/udp.c?v=2.0.40">2.0.40</a>&nbsp;<a href="source/net/ipv4/udp.c?v=2.2.26">2.2.26</a>&nbsp;<a href="source/net/ipv4/udp.c?v=2.4.37">2.4.37</a>&nbsp;<a href="source/net/ipv4/udp.c?v=3.5">3.5</a>&nbsp;<a href="source/net/ipv4/udp.c?v=3.6">3.6</a>&nbsp;<a href="source/net/ipv4/udp.c?v=3.7">3.7</a>&nbsp;<a href="source/net/ipv4/udp.c?v=3.8">3.8</a>&nbsp;<a href="source/net/ipv4/udp.c?v=3.9">3.9</a>&nbsp;<a href="source/net/ipv4/udp.c?v=3.10">3.10</a>&nbsp;<a href="source/net/ipv4/udp.c?v=3.11">3.11</a>&nbsp;<a href="source/net/ipv4/udp.c?v=3.12">3.12</a>&nbsp;<a href="source/net/ipv4/udp.c?v=3.13">3.13</a>&nbsp;<a href="source/net/ipv4/udp.c?v=3.14">3.14</a>&nbsp;<a href="source/net/ipv4/udp.c?v=3.15">3.15</a>&nbsp;<a href="source/net/ipv4/udp.c?v=3.16">3.16</a>&nbsp;<a href="source/net/ipv4/udp.c?v=3.17">3.17</a>&nbsp;<a href="source/net/ipv4/udp.c?v=3.18">3.18</a>&nbsp;<a href="source/net/ipv4/udp.c?v=3.19">3.19</a>&nbsp;<a href="source/net/ipv4/udp.c?v=4.0">4.0</a>&nbsp;<b><i>4.1</i></b></p>
  
</div>

<h1><a href="source/">Linux</a>/<a href="source/net/">net</a>/<a href="source/net/ipv4/">ipv4</a>/<a href="source/net/ipv4/udp.c">udp.c</a></h1>
<div id="lxrcode"><pre>  <a name="L1" href="source/net/ipv4/udp.c#L1">1</a> <b><i>/*</i></b>
  <a name="L2" href="source/net/ipv4/udp.c#L2">2</a> <b><i> * INET         An implementation of the TCP/IP protocol suite for the LINUX</i></b>
  <a name="L3" href="source/net/ipv4/udp.c#L3">3</a> <b><i> *              operating system.  INET is implemented using the  BSD Socket</i></b>
  <a name="L4" href="source/net/ipv4/udp.c#L4">4</a> <b><i> *              interface as the means of communication with the user level.</i></b>
  <a name="L5" href="source/net/ipv4/udp.c#L5">5</a> <b><i> *</i></b>
  <a name="L6" href="source/net/ipv4/udp.c#L6">6</a> <b><i> *              The User Datagram Protocol (UDP).</i></b>
  <a name="L7" href="source/net/ipv4/udp.c#L7">7</a> <b><i> *</i></b>
  <a name="L8" href="source/net/ipv4/udp.c#L8">8</a> <b><i> * Authors:     Ross Biro</i></b>
  <a name="L9" href="source/net/ipv4/udp.c#L9">9</a> <b><i> *              Fred N. van Kempen, &lt;waltje@uWalt.NL.Mugnet.ORG&gt;</i></b>
 <a name="L10" href="source/net/ipv4/udp.c#L10">10</a> <b><i> *              Arnt Gulbrandsen, &lt;agulbra@nvg.unit.no&gt;</i></b>
 <a name="L11" href="source/net/ipv4/udp.c#L11">11</a> <b><i> *              Alan Cox, &lt;alan@lxorguk.ukuu.org.uk&gt;</i></b>
 <a name="L12" href="source/net/ipv4/udp.c#L12">12</a> <b><i> *              Hirokazu Takahashi, &lt;taka@valinux.co.jp&gt;</i></b>
 <a name="L13" href="source/net/ipv4/udp.c#L13">13</a> <b><i> *</i></b>
 <a name="L14" href="source/net/ipv4/udp.c#L14">14</a> <b><i> * Fixes:</i></b>
 <a name="L15" href="source/net/ipv4/udp.c#L15">15</a> <b><i> *              Alan Cox        :       verify_area() calls</i></b>
 <a name="L16" href="source/net/ipv4/udp.c#L16">16</a> <b><i> *              Alan Cox        :       stopped close while in use off icmp</i></b>
 <a name="L17" href="source/net/ipv4/udp.c#L17">17</a> <b><i> *                                      messages. Not a fix but a botch that</i></b>
 <a name="L18" href="source/net/ipv4/udp.c#L18">18</a> <b><i> *                                      for udp at least is 'valid'.</i></b>
 <a name="L19" href="source/net/ipv4/udp.c#L19">19</a> <b><i> *              Alan Cox        :       Fixed icmp handling properly</i></b>
 <a name="L20" href="source/net/ipv4/udp.c#L20">20</a> <b><i> *              Alan Cox        :       Correct error for oversized datagrams</i></b>
 <a name="L21" href="source/net/ipv4/udp.c#L21">21</a> <b><i> *              Alan Cox        :       Tidied select() semantics.</i></b>
 <a name="L22" href="source/net/ipv4/udp.c#L22">22</a> <b><i> *              Alan Cox        :       udp_err() fixed properly, also now</i></b>
 <a name="L23" href="source/net/ipv4/udp.c#L23">23</a> <b><i> *                                      select and read wake correctly on errors</i></b>
 <a name="L24" href="source/net/ipv4/udp.c#L24">24</a> <b><i> *              Alan Cox        :       udp_send verify_area moved to avoid mem leak</i></b>
 <a name="L25" href="source/net/ipv4/udp.c#L25">25</a> <b><i> *              Alan Cox        :       UDP can count its memory</i></b>
 <a name="L26" href="source/net/ipv4/udp.c#L26">26</a> <b><i> *              Alan Cox        :       send to an unknown connection causes</i></b>
 <a name="L27" href="source/net/ipv4/udp.c#L27">27</a> <b><i> *                                      an ECONNREFUSED off the icmp, but</i></b>
 <a name="L28" href="source/net/ipv4/udp.c#L28">28</a> <b><i> *                                      does NOT close.</i></b>
 <a name="L29" href="source/net/ipv4/udp.c#L29">29</a> <b><i> *              Alan Cox        :       Switched to new sk_buff handlers. No more backlog!</i></b>
 <a name="L30" href="source/net/ipv4/udp.c#L30">30</a> <b><i> *              Alan Cox        :       Using generic datagram code. Even smaller and the PEEK</i></b>
 <a name="L31" href="source/net/ipv4/udp.c#L31">31</a> <b><i> *                                      bug no longer crashes it.</i></b>
 <a name="L32" href="source/net/ipv4/udp.c#L32">32</a> <b><i> *              Fred Van Kempen :       Net2e support for sk-&gt;broadcast.</i></b>
 <a name="L33" href="source/net/ipv4/udp.c#L33">33</a> <b><i> *              Alan Cox        :       Uses skb_free_datagram</i></b>
 <a name="L34" href="source/net/ipv4/udp.c#L34">34</a> <b><i> *              Alan Cox        :       Added get/set sockopt support.</i></b>
 <a name="L35" href="source/net/ipv4/udp.c#L35">35</a> <b><i> *              Alan Cox        :       Broadcasting without option set returns EACCES.</i></b>
 <a name="L36" href="source/net/ipv4/udp.c#L36">36</a> <b><i> *              Alan Cox        :       No wakeup calls. Instead we now use the callbacks.</i></b>
 <a name="L37" href="source/net/ipv4/udp.c#L37">37</a> <b><i> *              Alan Cox        :       Use ip_tos and ip_ttl</i></b>
 <a name="L38" href="source/net/ipv4/udp.c#L38">38</a> <b><i> *              Alan Cox        :       SNMP Mibs</i></b>
 <a name="L39" href="source/net/ipv4/udp.c#L39">39</a> <b><i> *              Alan Cox        :       MSG_DONTROUTE, and 0.0.0.0 support.</i></b>
 <a name="L40" href="source/net/ipv4/udp.c#L40">40</a> <b><i> *              Matt Dillon     :       UDP length checks.</i></b>
 <a name="L41" href="source/net/ipv4/udp.c#L41">41</a> <b><i> *              Alan Cox        :       Smarter af_inet used properly.</i></b>
 <a name="L42" href="source/net/ipv4/udp.c#L42">42</a> <b><i> *              Alan Cox        :       Use new kernel side addressing.</i></b>
 <a name="L43" href="source/net/ipv4/udp.c#L43">43</a> <b><i> *              Alan Cox        :       Incorrect return on truncated datagram receive.</i></b>
 <a name="L44" href="source/net/ipv4/udp.c#L44">44</a> <b><i> *      Arnt Gulbrandsen        :       New udp_send and stuff</i></b>
 <a name="L45" href="source/net/ipv4/udp.c#L45">45</a> <b><i> *              Alan Cox        :       Cache last socket</i></b>
 <a name="L46" href="source/net/ipv4/udp.c#L46">46</a> <b><i> *              Alan Cox        :       Route cache</i></b>
 <a name="L47" href="source/net/ipv4/udp.c#L47">47</a> <b><i> *              Jon Peatfield   :       Minor efficiency fix to sendto().</i></b>
 <a name="L48" href="source/net/ipv4/udp.c#L48">48</a> <b><i> *              Mike Shaver     :       RFC1122 checks.</i></b>
 <a name="L49" href="source/net/ipv4/udp.c#L49">49</a> <b><i> *              Alan Cox        :       Nonblocking error fix.</i></b>
 <a name="L50" href="source/net/ipv4/udp.c#L50">50</a> <b><i> *      Willy Konynenberg       :       Transparent proxying support.</i></b>
 <a name="L51" href="source/net/ipv4/udp.c#L51">51</a> <b><i> *              Mike McLagan    :       Routing by source</i></b>
 <a name="L52" href="source/net/ipv4/udp.c#L52">52</a> <b><i> *              David S. Miller :       New socket lookup architecture.</i></b>
 <a name="L53" href="source/net/ipv4/udp.c#L53">53</a> <b><i> *                                      Last socket cache retained as it</i></b>
 <a name="L54" href="source/net/ipv4/udp.c#L54">54</a> <b><i> *                                      does have a high hit rate.</i></b>
 <a name="L55" href="source/net/ipv4/udp.c#L55">55</a> <b><i> *              Olaf Kirch      :       Don't linearise iovec on sendmsg.</i></b>
 <a name="L56" href="source/net/ipv4/udp.c#L56">56</a> <b><i> *              Andi Kleen      :       Some cleanups, cache destination entry</i></b>
 <a name="L57" href="source/net/ipv4/udp.c#L57">57</a> <b><i> *                                      for connect.</i></b>
 <a name="L58" href="source/net/ipv4/udp.c#L58">58</a> <b><i> *      Vitaly E. Lavrov        :       Transparent proxy revived after year coma.</i></b>
 <a name="L59" href="source/net/ipv4/udp.c#L59">59</a> <b><i> *              Melvin Smith    :       Check msg_name not msg_namelen in sendto(),</i></b>
 <a name="L60" href="source/net/ipv4/udp.c#L60">60</a> <b><i> *                                      return ENOTCONN for unconnected sockets (POSIX)</i></b>
 <a name="L61" href="source/net/ipv4/udp.c#L61">61</a> <b><i> *              Janos Farkas    :       don't deliver multi/broadcasts to a different</i></b>
 <a name="L62" href="source/net/ipv4/udp.c#L62">62</a> <b><i> *                                      bound-to-device socket</i></b>
 <a name="L63" href="source/net/ipv4/udp.c#L63">63</a> <b><i> *      Hirokazu Takahashi      :       HW checksumming for outgoing UDP</i></b>
 <a name="L64" href="source/net/ipv4/udp.c#L64">64</a> <b><i> *                                      datagrams.</i></b>
 <a name="L65" href="source/net/ipv4/udp.c#L65">65</a> <b><i> *      Hirokazu Takahashi      :       sendfile() on UDP works now.</i></b>
 <a name="L66" href="source/net/ipv4/udp.c#L66">66</a> <b><i> *              Arnaldo C. Melo :       convert /proc/net/udp to seq_file</i></b>
 <a name="L67" href="source/net/ipv4/udp.c#L67">67</a> <b><i> *      YOSHIFUJI Hideaki @USAGI and:   Support IPV6_V6ONLY socket option, which</i></b>
 <a name="L68" href="source/net/ipv4/udp.c#L68">68</a> <b><i> *      Alexey Kuznetsov:               allow both IPv4 and IPv6 sockets to bind</i></b>
 <a name="L69" href="source/net/ipv4/udp.c#L69">69</a> <b><i> *                                      a single port at the same time.</i></b>
 <a name="L70" href="source/net/ipv4/udp.c#L70">70</a> <b><i> *      Derek Atkins &lt;derek@ihtfp.com&gt;: Add Encapulation Support</i></b>
 <a name="L71" href="source/net/ipv4/udp.c#L71">71</a> <b><i> *      James Chapman           :       Add L2TP encapsulation type.</i></b>
 <a name="L72" href="source/net/ipv4/udp.c#L72">72</a> <b><i> *</i></b>
 <a name="L73" href="source/net/ipv4/udp.c#L73">73</a> <b><i> *</i></b>
 <a name="L74" href="source/net/ipv4/udp.c#L74">74</a> <b><i> *              This program is free software; you can redistribute it and/or</i></b>
 <a name="L75" href="source/net/ipv4/udp.c#L75">75</a> <b><i> *              modify it under the terms of the GNU General Public License</i></b>
 <a name="L76" href="source/net/ipv4/udp.c#L76">76</a> <b><i> *              as published by the Free Software Foundation; either version</i></b>
 <a name="L77" href="source/net/ipv4/udp.c#L77">77</a> <b><i> *              2 of the License, or (at your option) any later version.</i></b>
 <a name="L78" href="source/net/ipv4/udp.c#L78">78</a> <b><i> */</i></b>
 <a name="L79" href="source/net/ipv4/udp.c#L79">79</a> 
 <a name="L80" href="source/net/ipv4/udp.c#L80">80</a> #define <a href="ident?i=pr_fmt">pr_fmt</a>(<a href="ident?i=fmt">fmt</a>) <i>"UDP: "</i> <a href="ident?i=fmt">fmt</a>
 <a name="L81" href="source/net/ipv4/udp.c#L81">81</a> 
 <a name="L82" href="source/net/ipv4/udp.c#L82">82</a> #include &lt;asm/uaccess.h&gt;
 <a name="L83" href="source/net/ipv4/udp.c#L83">83</a> #include &lt;asm/ioctls.h&gt;
 <a name="L84" href="source/net/ipv4/udp.c#L84">84</a> #include &lt;linux/bootmem.h&gt;
 <a name="L85" href="source/net/ipv4/udp.c#L85">85</a> #include &lt;linux/highmem.h&gt;
 <a name="L86" href="source/net/ipv4/udp.c#L86">86</a> #include &lt;linux/swap.h&gt;
 <a name="L87" href="source/net/ipv4/udp.c#L87">87</a> #include &lt;linux/types.h&gt;
 <a name="L88" href="source/net/ipv4/udp.c#L88">88</a> #include &lt;linux/fcntl.h&gt;
 <a name="L89" href="source/net/ipv4/udp.c#L89">89</a> #include &lt;linux/module.h&gt;
 <a name="L90" href="source/net/ipv4/udp.c#L90">90</a> #include &lt;linux/socket.h&gt;
 <a name="L91" href="source/net/ipv4/udp.c#L91">91</a> #include &lt;linux/sockios.h&gt;
 <a name="L92" href="source/net/ipv4/udp.c#L92">92</a> #include &lt;linux/igmp.h&gt;
 <a name="L93" href="source/net/ipv4/udp.c#L93">93</a> #include &lt;linux/inetdevice.h&gt;
 <a name="L94" href="source/net/ipv4/udp.c#L94">94</a> #include &lt;linux/in.h&gt;
 <a name="L95" href="source/net/ipv4/udp.c#L95">95</a> #include &lt;linux/errno.h&gt;
 <a name="L96" href="source/net/ipv4/udp.c#L96">96</a> #include &lt;linux/timer.h&gt;
 <a name="L97" href="source/net/ipv4/udp.c#L97">97</a> #include &lt;linux/mm.h&gt;
 <a name="L98" href="source/net/ipv4/udp.c#L98">98</a> #include &lt;linux/inet.h&gt;
 <a name="L99" href="source/net/ipv4/udp.c#L99">99</a> #include &lt;linux/netdevice.h&gt;
<a name="L100" href="source/net/ipv4/udp.c#L100">100</a> #include &lt;linux/slab.h&gt;
<a name="L101" href="source/net/ipv4/udp.c#L101">101</a> #include &lt;net/tcp_states.h&gt;
<a name="L102" href="source/net/ipv4/udp.c#L102">102</a> #include &lt;linux/skbuff.h&gt;
<a name="L103" href="source/net/ipv4/udp.c#L103">103</a> #include &lt;linux/netdevice.h&gt;
<a name="L104" href="source/net/ipv4/udp.c#L104">104</a> #include &lt;linux/proc_fs.h&gt;
<a name="L105" href="source/net/ipv4/udp.c#L105">105</a> #include &lt;linux/seq_file.h&gt;
<a name="L106" href="source/net/ipv4/udp.c#L106">106</a> #include &lt;net/net_namespace.h&gt;
<a name="L107" href="source/net/ipv4/udp.c#L107">107</a> #include &lt;net/icmp.h&gt;
<a name="L108" href="source/net/ipv4/udp.c#L108">108</a> #include &lt;net/inet_hashtables.h&gt;
<a name="L109" href="source/net/ipv4/udp.c#L109">109</a> #include &lt;net/route.h&gt;
<a name="L110" href="source/net/ipv4/udp.c#L110">110</a> #include &lt;net/checksum.h&gt;
<a name="L111" href="source/net/ipv4/udp.c#L111">111</a> #include &lt;net/xfrm.h&gt;
<a name="L112" href="source/net/ipv4/udp.c#L112">112</a> #include &lt;trace/events/udp.h&gt;
<a name="L113" href="source/net/ipv4/udp.c#L113">113</a> #include &lt;linux/static_key.h&gt;
<a name="L114" href="source/net/ipv4/udp.c#L114">114</a> #include &lt;trace/events/skb.h&gt;
<a name="L115" href="source/net/ipv4/udp.c#L115">115</a> #include &lt;net/busy_poll.h&gt;
<a name="L116" href="source/net/ipv4/udp.c#L116">116</a> #include "<a href="source/net/ipv4/udp_impl.h">udp_impl.h</a>"
<a name="L117" href="source/net/ipv4/udp.c#L117">117</a> 
<a name="L118" href="source/net/ipv4/udp.c#L118">118</a> struct <a href="ident?i=udp_table">udp_table</a> <a href="ident?i=udp_table">udp_table</a> <a href="ident?i=__read_mostly">__read_mostly</a>;
<a name="L119" href="source/net/ipv4/udp.c#L119">119</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=udp_table">udp_table</a>);
<a name="L120" href="source/net/ipv4/udp.c#L120">120</a> 
<a name="L121" href="source/net/ipv4/udp.c#L121">121</a> long <a href="ident?i=sysctl_udp_mem">sysctl_udp_mem</a>[3] <a href="ident?i=__read_mostly">__read_mostly</a>;
<a name="L122" href="source/net/ipv4/udp.c#L122">122</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=sysctl_udp_mem">sysctl_udp_mem</a>);
<a name="L123" href="source/net/ipv4/udp.c#L123">123</a> 
<a name="L124" href="source/net/ipv4/udp.c#L124">124</a> int <a href="ident?i=sysctl_udp_rmem_min">sysctl_udp_rmem_min</a> <a href="ident?i=__read_mostly">__read_mostly</a>;
<a name="L125" href="source/net/ipv4/udp.c#L125">125</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=sysctl_udp_rmem_min">sysctl_udp_rmem_min</a>);
<a name="L126" href="source/net/ipv4/udp.c#L126">126</a> 
<a name="L127" href="source/net/ipv4/udp.c#L127">127</a> int <a href="ident?i=sysctl_udp_wmem_min">sysctl_udp_wmem_min</a> <a href="ident?i=__read_mostly">__read_mostly</a>;
<a name="L128" href="source/net/ipv4/udp.c#L128">128</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=sysctl_udp_wmem_min">sysctl_udp_wmem_min</a>);
<a name="L129" href="source/net/ipv4/udp.c#L129">129</a> 
<a name="L130" href="source/net/ipv4/udp.c#L130">130</a> <a href="ident?i=atomic_long_t">atomic_long_t</a> <a href="ident?i=udp_memory_allocated">udp_memory_allocated</a>;
<a name="L131" href="source/net/ipv4/udp.c#L131">131</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=udp_memory_allocated">udp_memory_allocated</a>);
<a name="L132" href="source/net/ipv4/udp.c#L132">132</a> 
<a name="L133" href="source/net/ipv4/udp.c#L133">133</a> #define <a href="ident?i=MAX_UDP_PORTS">MAX_UDP_PORTS</a> 65536
<a name="L134" href="source/net/ipv4/udp.c#L134">134</a> #define <a href="ident?i=PORTS_PER_CHAIN">PORTS_PER_CHAIN</a> (<a href="ident?i=MAX_UDP_PORTS">MAX_UDP_PORTS</a> / <a href="ident?i=UDP_HTABLE_SIZE_MIN">UDP_HTABLE_SIZE_MIN</a>)
<a name="L135" href="source/net/ipv4/udp.c#L135">135</a> 
<a name="L136" href="source/net/ipv4/udp.c#L136">136</a> static int <a href="ident?i=udp_lib_lport_inuse">udp_lib_lport_inuse</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>, <a href="ident?i=__u16">__u16</a> <a href="ident?i=num">num</a>,
<a name="L137" href="source/net/ipv4/udp.c#L137">137</a>                                const struct <a href="ident?i=udp_hslot">udp_hslot</a> *hslot,
<a name="L138" href="source/net/ipv4/udp.c#L138">138</a>                                unsigned long *<a href="ident?i=bitmap">bitmap</a>,
<a name="L139" href="source/net/ipv4/udp.c#L139">139</a>                                struct <a href="ident?i=sock">sock</a> *sk,
<a name="L140" href="source/net/ipv4/udp.c#L140">140</a>                                int (*saddr_comp)(const struct <a href="ident?i=sock">sock</a> *sk1,
<a name="L141" href="source/net/ipv4/udp.c#L141">141</a>                                                  const struct <a href="ident?i=sock">sock</a> *sk2),
<a name="L142" href="source/net/ipv4/udp.c#L142">142</a>                                unsigned int <a href="ident?i=log">log</a>)
<a name="L143" href="source/net/ipv4/udp.c#L143">143</a> {
<a name="L144" href="source/net/ipv4/udp.c#L144">144</a>         struct <a href="ident?i=sock">sock</a> *sk2;
<a name="L145" href="source/net/ipv4/udp.c#L145">145</a>         struct <a href="ident?i=hlist_nulls_node">hlist_nulls_node</a> *<a href="ident?i=node">node</a>;
<a name="L146" href="source/net/ipv4/udp.c#L146">146</a>         <a href="ident?i=kuid_t">kuid_t</a> <a href="ident?i=uid">uid</a> = <a href="ident?i=sock_i_uid">sock_i_uid</a>(sk);
<a name="L147" href="source/net/ipv4/udp.c#L147">147</a> 
<a name="L148" href="source/net/ipv4/udp.c#L148">148</a>         <a href="ident?i=sk_nulls_for_each">sk_nulls_for_each</a>(sk2, <a href="ident?i=node">node</a>, &amp;hslot-&gt;<a href="ident?i=head">head</a>) {
<a name="L149" href="source/net/ipv4/udp.c#L149">149</a>                 if (<a href="ident?i=net_eq">net_eq</a>(<a href="ident?i=sock_net">sock_net</a>(sk2), <a href="ident?i=net">net</a>) &amp;&amp;
<a name="L150" href="source/net/ipv4/udp.c#L150">150</a>                     sk2 != sk &amp;&amp;
<a name="L151" href="source/net/ipv4/udp.c#L151">151</a>                     (<a href="ident?i=bitmap">bitmap</a> || <a href="ident?i=udp_sk">udp_sk</a>(sk2)-&gt;<a href="ident?i=udp_port_hash">udp_port_hash</a> == <a href="ident?i=num">num</a>) &amp;&amp;
<a name="L152" href="source/net/ipv4/udp.c#L152">152</a>                     (!sk2-&gt;<a href="ident?i=sk_reuse">sk_reuse</a> || !sk-&gt;<a href="ident?i=sk_reuse">sk_reuse</a>) &amp;&amp;
<a name="L153" href="source/net/ipv4/udp.c#L153">153</a>                     (!sk2-&gt;<a href="ident?i=sk_bound_dev_if">sk_bound_dev_if</a> || !sk-&gt;<a href="ident?i=sk_bound_dev_if">sk_bound_dev_if</a> ||
<a name="L154" href="source/net/ipv4/udp.c#L154">154</a>                      sk2-&gt;<a href="ident?i=sk_bound_dev_if">sk_bound_dev_if</a> == sk-&gt;<a href="ident?i=sk_bound_dev_if">sk_bound_dev_if</a>) &amp;&amp;
<a name="L155" href="source/net/ipv4/udp.c#L155">155</a>                     (!sk2-&gt;<a href="ident?i=sk_reuseport">sk_reuseport</a> || !sk-&gt;<a href="ident?i=sk_reuseport">sk_reuseport</a> ||
<a name="L156" href="source/net/ipv4/udp.c#L156">156</a>                      !<a href="ident?i=uid_eq">uid_eq</a>(<a href="ident?i=uid">uid</a>, <a href="ident?i=sock_i_uid">sock_i_uid</a>(sk2))) &amp;&amp;
<a name="L157" href="source/net/ipv4/udp.c#L157">157</a>                     saddr_comp(sk, sk2)) {
<a name="L158" href="source/net/ipv4/udp.c#L158">158</a>                         if (!<a href="ident?i=bitmap">bitmap</a>)
<a name="L159" href="source/net/ipv4/udp.c#L159">159</a>                                 return 1;
<a name="L160" href="source/net/ipv4/udp.c#L160">160</a>                         <a href="ident?i=__set_bit">__set_bit</a>(<a href="ident?i=udp_sk">udp_sk</a>(sk2)-&gt;<a href="ident?i=udp_port_hash">udp_port_hash</a> &gt;&gt; <a href="ident?i=log">log</a>, <a href="ident?i=bitmap">bitmap</a>);
<a name="L161" href="source/net/ipv4/udp.c#L161">161</a>                 }
<a name="L162" href="source/net/ipv4/udp.c#L162">162</a>         }
<a name="L163" href="source/net/ipv4/udp.c#L163">163</a>         return 0;
<a name="L164" href="source/net/ipv4/udp.c#L164">164</a> }
<a name="L165" href="source/net/ipv4/udp.c#L165">165</a> 
<a name="L166" href="source/net/ipv4/udp.c#L166">166</a> <b><i>/*</i></b>
<a name="L167" href="source/net/ipv4/udp.c#L167">167</a> <b><i> * Note: we still hold spinlock of primary hash chain, so no other writer</i></b>
<a name="L168" href="source/net/ipv4/udp.c#L168">168</a> <b><i> * can insert/delete a socket with local_port == num</i></b>
<a name="L169" href="source/net/ipv4/udp.c#L169">169</a> <b><i> */</i></b>
<a name="L170" href="source/net/ipv4/udp.c#L170">170</a> static int <a href="ident?i=udp_lib_lport_inuse2">udp_lib_lport_inuse2</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>, <a href="ident?i=__u16">__u16</a> <a href="ident?i=num">num</a>,
<a name="L171" href="source/net/ipv4/udp.c#L171">171</a>                                 struct <a href="ident?i=udp_hslot">udp_hslot</a> *hslot2,
<a name="L172" href="source/net/ipv4/udp.c#L172">172</a>                                 struct <a href="ident?i=sock">sock</a> *sk,
<a name="L173" href="source/net/ipv4/udp.c#L173">173</a>                                 int (*saddr_comp)(const struct <a href="ident?i=sock">sock</a> *sk1,
<a name="L174" href="source/net/ipv4/udp.c#L174">174</a>                                                   const struct <a href="ident?i=sock">sock</a> *sk2))
<a name="L175" href="source/net/ipv4/udp.c#L175">175</a> {
<a name="L176" href="source/net/ipv4/udp.c#L176">176</a>         struct <a href="ident?i=sock">sock</a> *sk2;
<a name="L177" href="source/net/ipv4/udp.c#L177">177</a>         struct <a href="ident?i=hlist_nulls_node">hlist_nulls_node</a> *<a href="ident?i=node">node</a>;
<a name="L178" href="source/net/ipv4/udp.c#L178">178</a>         <a href="ident?i=kuid_t">kuid_t</a> <a href="ident?i=uid">uid</a> = <a href="ident?i=sock_i_uid">sock_i_uid</a>(sk);
<a name="L179" href="source/net/ipv4/udp.c#L179">179</a>         int <a href="ident?i=res">res</a> = 0;
<a name="L180" href="source/net/ipv4/udp.c#L180">180</a> 
<a name="L181" href="source/net/ipv4/udp.c#L181">181</a>         <a href="ident?i=spin_lock">spin_lock</a>(&amp;hslot2-&gt;<a href="ident?i=lock">lock</a>);
<a name="L182" href="source/net/ipv4/udp.c#L182">182</a>         <a href="ident?i=udp_portaddr_for_each_entry">udp_portaddr_for_each_entry</a>(sk2, <a href="ident?i=node">node</a>, &amp;hslot2-&gt;<a href="ident?i=head">head</a>) {
<a name="L183" href="source/net/ipv4/udp.c#L183">183</a>                 if (<a href="ident?i=net_eq">net_eq</a>(<a href="ident?i=sock_net">sock_net</a>(sk2), <a href="ident?i=net">net</a>) &amp;&amp;
<a name="L184" href="source/net/ipv4/udp.c#L184">184</a>                     sk2 != sk &amp;&amp;
<a name="L185" href="source/net/ipv4/udp.c#L185">185</a>                     (<a href="ident?i=udp_sk">udp_sk</a>(sk2)-&gt;<a href="ident?i=udp_port_hash">udp_port_hash</a> == <a href="ident?i=num">num</a>) &amp;&amp;
<a name="L186" href="source/net/ipv4/udp.c#L186">186</a>                     (!sk2-&gt;<a href="ident?i=sk_reuse">sk_reuse</a> || !sk-&gt;<a href="ident?i=sk_reuse">sk_reuse</a>) &amp;&amp;
<a name="L187" href="source/net/ipv4/udp.c#L187">187</a>                     (!sk2-&gt;<a href="ident?i=sk_bound_dev_if">sk_bound_dev_if</a> || !sk-&gt;<a href="ident?i=sk_bound_dev_if">sk_bound_dev_if</a> ||
<a name="L188" href="source/net/ipv4/udp.c#L188">188</a>                      sk2-&gt;<a href="ident?i=sk_bound_dev_if">sk_bound_dev_if</a> == sk-&gt;<a href="ident?i=sk_bound_dev_if">sk_bound_dev_if</a>) &amp;&amp;
<a name="L189" href="source/net/ipv4/udp.c#L189">189</a>                     (!sk2-&gt;<a href="ident?i=sk_reuseport">sk_reuseport</a> || !sk-&gt;<a href="ident?i=sk_reuseport">sk_reuseport</a> ||
<a name="L190" href="source/net/ipv4/udp.c#L190">190</a>                      !<a href="ident?i=uid_eq">uid_eq</a>(<a href="ident?i=uid">uid</a>, <a href="ident?i=sock_i_uid">sock_i_uid</a>(sk2))) &amp;&amp;
<a name="L191" href="source/net/ipv4/udp.c#L191">191</a>                     saddr_comp(sk, sk2)) {
<a name="L192" href="source/net/ipv4/udp.c#L192">192</a>                         <a href="ident?i=res">res</a> = 1;
<a name="L193" href="source/net/ipv4/udp.c#L193">193</a>                         break;
<a name="L194" href="source/net/ipv4/udp.c#L194">194</a>                 }
<a name="L195" href="source/net/ipv4/udp.c#L195">195</a>         }
<a name="L196" href="source/net/ipv4/udp.c#L196">196</a>         <a href="ident?i=spin_unlock">spin_unlock</a>(&amp;hslot2-&gt;<a href="ident?i=lock">lock</a>);
<a name="L197" href="source/net/ipv4/udp.c#L197">197</a>         return <a href="ident?i=res">res</a>;
<a name="L198" href="source/net/ipv4/udp.c#L198">198</a> }
<a name="L199" href="source/net/ipv4/udp.c#L199">199</a> 
<a name="L200" href="source/net/ipv4/udp.c#L200">200</a> <b><i>/**</i></b>
<a name="L201" href="source/net/ipv4/udp.c#L201">201</a> <b><i> *  udp_lib_get_port  -  UDP/-Lite port lookup for IPv4 and IPv6</i></b>
<a name="L202" href="source/net/ipv4/udp.c#L202">202</a> <b><i> *</i></b>
<a name="L203" href="source/net/ipv4/udp.c#L203">203</a> <b><i> *  @sk:          socket struct in question</i></b>
<a name="L204" href="source/net/ipv4/udp.c#L204">204</a> <b><i> *  @snum:        port number to look up</i></b>
<a name="L205" href="source/net/ipv4/udp.c#L205">205</a> <b><i> *  @saddr_comp:  AF-dependent comparison of bound local IP addresses</i></b>
<a name="L206" href="source/net/ipv4/udp.c#L206">206</a> <b><i> *  @hash2_nulladdr: AF-dependent hash value in secondary hash chains,</i></b>
<a name="L207" href="source/net/ipv4/udp.c#L207">207</a> <b><i> *                   with NULL address</i></b>
<a name="L208" href="source/net/ipv4/udp.c#L208">208</a> <b><i> */</i></b>
<a name="L209" href="source/net/ipv4/udp.c#L209">209</a> int <a href="ident?i=udp_lib_get_port">udp_lib_get_port</a>(struct <a href="ident?i=sock">sock</a> *sk, unsigned short snum,
<a name="L210" href="source/net/ipv4/udp.c#L210">210</a>                      int (*saddr_comp)(const struct <a href="ident?i=sock">sock</a> *sk1,
<a name="L211" href="source/net/ipv4/udp.c#L211">211</a>                                        const struct <a href="ident?i=sock">sock</a> *sk2),
<a name="L212" href="source/net/ipv4/udp.c#L212">212</a>                      unsigned int hash2_nulladdr)
<a name="L213" href="source/net/ipv4/udp.c#L213">213</a> {
<a name="L214" href="source/net/ipv4/udp.c#L214">214</a>         struct <a href="ident?i=udp_hslot">udp_hslot</a> *hslot, *hslot2;
<a name="L215" href="source/net/ipv4/udp.c#L215">215</a>         struct <a href="ident?i=udp_table">udp_table</a> *udptable = sk-&gt;<a href="ident?i=sk_prot">sk_prot</a>-&gt;<a href="ident?i=h">h</a>.<a href="ident?i=udp_table">udp_table</a>;
<a name="L216" href="source/net/ipv4/udp.c#L216">216</a>         int    <a href="ident?i=error">error</a> = 1;
<a name="L217" href="source/net/ipv4/udp.c#L217">217</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=sock_net">sock_net</a>(sk);
<a name="L218" href="source/net/ipv4/udp.c#L218">218</a> 
<a name="L219" href="source/net/ipv4/udp.c#L219">219</a>         if (!snum) {
<a name="L220" href="source/net/ipv4/udp.c#L220">220</a>                 int low, <a href="ident?i=high">high</a>, <a href="ident?i=remaining">remaining</a>;
<a name="L221" href="source/net/ipv4/udp.c#L221">221</a>                 unsigned int <a href="ident?i=rand">rand</a>;
<a name="L222" href="source/net/ipv4/udp.c#L222">222</a>                 unsigned short <a href="ident?i=first">first</a>, <a href="ident?i=last">last</a>;
<a name="L223" href="source/net/ipv4/udp.c#L223">223</a>                 <a href="ident?i=DECLARE_BITMAP">DECLARE_BITMAP</a>(<a href="ident?i=bitmap">bitmap</a>, <a href="ident?i=PORTS_PER_CHAIN">PORTS_PER_CHAIN</a>);
<a name="L224" href="source/net/ipv4/udp.c#L224">224</a> 
<a name="L225" href="source/net/ipv4/udp.c#L225">225</a>                 <a href="ident?i=inet_get_local_port_range">inet_get_local_port_range</a>(<a href="ident?i=net">net</a>, &amp;low, &amp;<a href="ident?i=high">high</a>);
<a name="L226" href="source/net/ipv4/udp.c#L226">226</a>                 <a href="ident?i=remaining">remaining</a> = (<a href="ident?i=high">high</a> - low) + 1;
<a name="L227" href="source/net/ipv4/udp.c#L227">227</a> 
<a name="L228" href="source/net/ipv4/udp.c#L228">228</a>                 <a href="ident?i=rand">rand</a> = <a href="ident?i=prandom_u32">prandom_u32</a>();
<a name="L229" href="source/net/ipv4/udp.c#L229">229</a>                 <a href="ident?i=first">first</a> = <a href="ident?i=reciprocal_scale">reciprocal_scale</a>(<a href="ident?i=rand">rand</a>, <a href="ident?i=remaining">remaining</a>) + low;
<a name="L230" href="source/net/ipv4/udp.c#L230">230</a>                 <b><i>/*</i></b>
<a name="L231" href="source/net/ipv4/udp.c#L231">231</a> <b><i>                 * force rand to be an odd multiple of UDP_HTABLE_SIZE</i></b>
<a name="L232" href="source/net/ipv4/udp.c#L232">232</a> <b><i>                 */</i></b>
<a name="L233" href="source/net/ipv4/udp.c#L233">233</a>                 <a href="ident?i=rand">rand</a> = (<a href="ident?i=rand">rand</a> | 1) * (udptable-&gt;<a href="ident?i=mask">mask</a> + 1);
<a name="L234" href="source/net/ipv4/udp.c#L234">234</a>                 <a href="ident?i=last">last</a> = <a href="ident?i=first">first</a> + udptable-&gt;<a href="ident?i=mask">mask</a> + 1;
<a name="L235" href="source/net/ipv4/udp.c#L235">235</a>                 do {
<a name="L236" href="source/net/ipv4/udp.c#L236">236</a>                         hslot = <a href="ident?i=udp_hashslot">udp_hashslot</a>(udptable, <a href="ident?i=net">net</a>, <a href="ident?i=first">first</a>);
<a name="L237" href="source/net/ipv4/udp.c#L237">237</a>                         <a href="ident?i=bitmap_zero">bitmap_zero</a>(<a href="ident?i=bitmap">bitmap</a>, <a href="ident?i=PORTS_PER_CHAIN">PORTS_PER_CHAIN</a>);
<a name="L238" href="source/net/ipv4/udp.c#L238">238</a>                         <a href="ident?i=spin_lock_bh">spin_lock_bh</a>(&amp;hslot-&gt;<a href="ident?i=lock">lock</a>);
<a name="L239" href="source/net/ipv4/udp.c#L239">239</a>                         <a href="ident?i=udp_lib_lport_inuse">udp_lib_lport_inuse</a>(<a href="ident?i=net">net</a>, snum, hslot, <a href="ident?i=bitmap">bitmap</a>, sk,
<a name="L240" href="source/net/ipv4/udp.c#L240">240</a>                                             saddr_comp, udptable-&gt;<a href="ident?i=log">log</a>);
<a name="L241" href="source/net/ipv4/udp.c#L241">241</a> 
<a name="L242" href="source/net/ipv4/udp.c#L242">242</a>                         snum = <a href="ident?i=first">first</a>;
<a name="L243" href="source/net/ipv4/udp.c#L243">243</a>                         <b><i>/*</i></b>
<a name="L244" href="source/net/ipv4/udp.c#L244">244</a> <b><i>                         * Iterate on all possible values of snum for this hash.</i></b>
<a name="L245" href="source/net/ipv4/udp.c#L245">245</a> <b><i>                         * Using steps of an odd multiple of UDP_HTABLE_SIZE</i></b>
<a name="L246" href="source/net/ipv4/udp.c#L246">246</a> <b><i>                         * give us randomization and full range coverage.</i></b>
<a name="L247" href="source/net/ipv4/udp.c#L247">247</a> <b><i>                         */</i></b>
<a name="L248" href="source/net/ipv4/udp.c#L248">248</a>                         do {
<a name="L249" href="source/net/ipv4/udp.c#L249">249</a>                                 if (low &lt;= snum &amp;&amp; snum &lt;= <a href="ident?i=high">high</a> &amp;&amp;
<a name="L250" href="source/net/ipv4/udp.c#L250">250</a>                                     !<a href="ident?i=test_bit">test_bit</a>(snum &gt;&gt; udptable-&gt;<a href="ident?i=log">log</a>, <a href="ident?i=bitmap">bitmap</a>) &amp;&amp;
<a name="L251" href="source/net/ipv4/udp.c#L251">251</a>                                     !<a href="ident?i=inet_is_local_reserved_port">inet_is_local_reserved_port</a>(<a href="ident?i=net">net</a>, snum))
<a name="L252" href="source/net/ipv4/udp.c#L252">252</a>                                         goto <a href="ident?i=found">found</a>;
<a name="L253" href="source/net/ipv4/udp.c#L253">253</a>                                 snum += <a href="ident?i=rand">rand</a>;
<a name="L254" href="source/net/ipv4/udp.c#L254">254</a>                         } while (snum != <a href="ident?i=first">first</a>);
<a name="L255" href="source/net/ipv4/udp.c#L255">255</a>                         <a href="ident?i=spin_unlock_bh">spin_unlock_bh</a>(&amp;hslot-&gt;<a href="ident?i=lock">lock</a>);
<a name="L256" href="source/net/ipv4/udp.c#L256">256</a>                 } while (++<a href="ident?i=first">first</a> != <a href="ident?i=last">last</a>);
<a name="L257" href="source/net/ipv4/udp.c#L257">257</a>                 goto <a href="ident?i=fail">fail</a>;
<a name="L258" href="source/net/ipv4/udp.c#L258">258</a>         } else {
<a name="L259" href="source/net/ipv4/udp.c#L259">259</a>                 hslot = <a href="ident?i=udp_hashslot">udp_hashslot</a>(udptable, <a href="ident?i=net">net</a>, snum);
<a name="L260" href="source/net/ipv4/udp.c#L260">260</a>                 <a href="ident?i=spin_lock_bh">spin_lock_bh</a>(&amp;hslot-&gt;<a href="ident?i=lock">lock</a>);
<a name="L261" href="source/net/ipv4/udp.c#L261">261</a>                 if (hslot-&gt;<a href="ident?i=count">count</a> &gt; 10) {
<a name="L262" href="source/net/ipv4/udp.c#L262">262</a>                         int exist;
<a name="L263" href="source/net/ipv4/udp.c#L263">263</a>                         unsigned int slot2 = <a href="ident?i=udp_sk">udp_sk</a>(sk)-&gt;<a href="ident?i=udp_portaddr_hash">udp_portaddr_hash</a> ^ snum;
<a name="L264" href="source/net/ipv4/udp.c#L264">264</a> 
<a name="L265" href="source/net/ipv4/udp.c#L265">265</a>                         slot2          &amp;= udptable-&gt;<a href="ident?i=mask">mask</a>;
<a name="L266" href="source/net/ipv4/udp.c#L266">266</a>                         hash2_nulladdr &amp;= udptable-&gt;<a href="ident?i=mask">mask</a>;
<a name="L267" href="source/net/ipv4/udp.c#L267">267</a> 
<a name="L268" href="source/net/ipv4/udp.c#L268">268</a>                         hslot2 = <a href="ident?i=udp_hashslot2">udp_hashslot2</a>(udptable, slot2);
<a name="L269" href="source/net/ipv4/udp.c#L269">269</a>                         if (hslot-&gt;<a href="ident?i=count">count</a> &lt; hslot2-&gt;<a href="ident?i=count">count</a>)
<a name="L270" href="source/net/ipv4/udp.c#L270">270</a>                                 goto scan_primary_hash;
<a name="L271" href="source/net/ipv4/udp.c#L271">271</a> 
<a name="L272" href="source/net/ipv4/udp.c#L272">272</a>                         exist = <a href="ident?i=udp_lib_lport_inuse2">udp_lib_lport_inuse2</a>(<a href="ident?i=net">net</a>, snum, hslot2,
<a name="L273" href="source/net/ipv4/udp.c#L273">273</a>                                                      sk, saddr_comp);
<a name="L274" href="source/net/ipv4/udp.c#L274">274</a>                         if (!exist &amp;&amp; (hash2_nulladdr != slot2)) {
<a name="L275" href="source/net/ipv4/udp.c#L275">275</a>                                 hslot2 = <a href="ident?i=udp_hashslot2">udp_hashslot2</a>(udptable, hash2_nulladdr);
<a name="L276" href="source/net/ipv4/udp.c#L276">276</a>                                 exist = <a href="ident?i=udp_lib_lport_inuse2">udp_lib_lport_inuse2</a>(<a href="ident?i=net">net</a>, snum, hslot2,
<a name="L277" href="source/net/ipv4/udp.c#L277">277</a>                                                              sk, saddr_comp);
<a name="L278" href="source/net/ipv4/udp.c#L278">278</a>                         }
<a name="L279" href="source/net/ipv4/udp.c#L279">279</a>                         if (exist)
<a name="L280" href="source/net/ipv4/udp.c#L280">280</a>                                 goto fail_unlock;
<a name="L281" href="source/net/ipv4/udp.c#L281">281</a>                         else
<a name="L282" href="source/net/ipv4/udp.c#L282">282</a>                                 goto <a href="ident?i=found">found</a>;
<a name="L283" href="source/net/ipv4/udp.c#L283">283</a>                 }
<a name="L284" href="source/net/ipv4/udp.c#L284">284</a> scan_primary_hash:
<a name="L285" href="source/net/ipv4/udp.c#L285">285</a>                 if (<a href="ident?i=udp_lib_lport_inuse">udp_lib_lport_inuse</a>(<a href="ident?i=net">net</a>, snum, hslot, <a href="ident?i=NULL">NULL</a>, sk,
<a name="L286" href="source/net/ipv4/udp.c#L286">286</a>                                         saddr_comp, 0))
<a name="L287" href="source/net/ipv4/udp.c#L287">287</a>                         goto fail_unlock;
<a name="L288" href="source/net/ipv4/udp.c#L288">288</a>         }
<a name="L289" href="source/net/ipv4/udp.c#L289">289</a> <a href="ident?i=found">found</a>:
<a name="L290" href="source/net/ipv4/udp.c#L290">290</a>         <a href="ident?i=inet_sk">inet_sk</a>(sk)-&gt;<a href="ident?i=inet_num">inet_num</a> = snum;
<a name="L291" href="source/net/ipv4/udp.c#L291">291</a>         <a href="ident?i=udp_sk">udp_sk</a>(sk)-&gt;<a href="ident?i=udp_port_hash">udp_port_hash</a> = snum;
<a name="L292" href="source/net/ipv4/udp.c#L292">292</a>         <a href="ident?i=udp_sk">udp_sk</a>(sk)-&gt;<a href="ident?i=udp_portaddr_hash">udp_portaddr_hash</a> ^= snum;
<a name="L293" href="source/net/ipv4/udp.c#L293">293</a>         if (<a href="ident?i=sk_unhashed">sk_unhashed</a>(sk)) {
<a name="L294" href="source/net/ipv4/udp.c#L294">294</a>                 <a href="ident?i=sk_nulls_add_node_rcu">sk_nulls_add_node_rcu</a>(sk, &amp;hslot-&gt;<a href="ident?i=head">head</a>);
<a name="L295" href="source/net/ipv4/udp.c#L295">295</a>                 hslot-&gt;<a href="ident?i=count">count</a>++;
<a name="L296" href="source/net/ipv4/udp.c#L296">296</a>                 <a href="ident?i=sock_prot_inuse_add">sock_prot_inuse_add</a>(<a href="ident?i=sock_net">sock_net</a>(sk), sk-&gt;<a href="ident?i=sk_prot">sk_prot</a>, 1);
<a name="L297" href="source/net/ipv4/udp.c#L297">297</a> 
<a name="L298" href="source/net/ipv4/udp.c#L298">298</a>                 hslot2 = <a href="ident?i=udp_hashslot2">udp_hashslot2</a>(udptable, <a href="ident?i=udp_sk">udp_sk</a>(sk)-&gt;<a href="ident?i=udp_portaddr_hash">udp_portaddr_hash</a>);
<a name="L299" href="source/net/ipv4/udp.c#L299">299</a>                 <a href="ident?i=spin_lock">spin_lock</a>(&amp;hslot2-&gt;<a href="ident?i=lock">lock</a>);
<a name="L300" href="source/net/ipv4/udp.c#L300">300</a>                 <a href="ident?i=hlist_nulls_add_head_rcu">hlist_nulls_add_head_rcu</a>(&amp;<a href="ident?i=udp_sk">udp_sk</a>(sk)-&gt;<a href="ident?i=udp_portaddr_node">udp_portaddr_node</a>,
<a name="L301" href="source/net/ipv4/udp.c#L301">301</a>                                          &amp;hslot2-&gt;<a href="ident?i=head">head</a>);
<a name="L302" href="source/net/ipv4/udp.c#L302">302</a>                 hslot2-&gt;<a href="ident?i=count">count</a>++;
<a name="L303" href="source/net/ipv4/udp.c#L303">303</a>                 <a href="ident?i=spin_unlock">spin_unlock</a>(&amp;hslot2-&gt;<a href="ident?i=lock">lock</a>);
<a name="L304" href="source/net/ipv4/udp.c#L304">304</a>         }
<a name="L305" href="source/net/ipv4/udp.c#L305">305</a>         <a href="ident?i=error">error</a> = 0;
<a name="L306" href="source/net/ipv4/udp.c#L306">306</a> fail_unlock:
<a name="L307" href="source/net/ipv4/udp.c#L307">307</a>         <a href="ident?i=spin_unlock_bh">spin_unlock_bh</a>(&amp;hslot-&gt;<a href="ident?i=lock">lock</a>);
<a name="L308" href="source/net/ipv4/udp.c#L308">308</a> <a href="ident?i=fail">fail</a>:
<a name="L309" href="source/net/ipv4/udp.c#L309">309</a>         return <a href="ident?i=error">error</a>;
<a name="L310" href="source/net/ipv4/udp.c#L310">310</a> }
<a name="L311" href="source/net/ipv4/udp.c#L311">311</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=udp_lib_get_port">udp_lib_get_port</a>);
<a name="L312" href="source/net/ipv4/udp.c#L312">312</a> 
<a name="L313" href="source/net/ipv4/udp.c#L313">313</a> static int <a href="ident?i=ipv4_rcv_saddr_equal">ipv4_rcv_saddr_equal</a>(const struct <a href="ident?i=sock">sock</a> *sk1, const struct <a href="ident?i=sock">sock</a> *sk2)
<a name="L314" href="source/net/ipv4/udp.c#L314">314</a> {
<a name="L315" href="source/net/ipv4/udp.c#L315">315</a>         struct <a href="ident?i=inet_sock">inet_sock</a> *inet1 = <a href="ident?i=inet_sk">inet_sk</a>(sk1), *inet2 = <a href="ident?i=inet_sk">inet_sk</a>(sk2);
<a name="L316" href="source/net/ipv4/udp.c#L316">316</a> 
<a name="L317" href="source/net/ipv4/udp.c#L317">317</a>         return  (!<a href="ident?i=ipv6_only_sock">ipv6_only_sock</a>(sk2)  &amp;&amp;
<a name="L318" href="source/net/ipv4/udp.c#L318">318</a>                  (!inet1-&gt;<a href="ident?i=inet_rcv_saddr">inet_rcv_saddr</a> || !inet2-&gt;<a href="ident?i=inet_rcv_saddr">inet_rcv_saddr</a> ||
<a name="L319" href="source/net/ipv4/udp.c#L319">319</a>                    inet1-&gt;<a href="ident?i=inet_rcv_saddr">inet_rcv_saddr</a> == inet2-&gt;<a href="ident?i=inet_rcv_saddr">inet_rcv_saddr</a>));
<a name="L320" href="source/net/ipv4/udp.c#L320">320</a> }
<a name="L321" href="source/net/ipv4/udp.c#L321">321</a> 
<a name="L322" href="source/net/ipv4/udp.c#L322">322</a> static <a href="ident?i=u32">u32</a> <a href="ident?i=udp4_portaddr_hash">udp4_portaddr_hash</a>(const struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>, <a href="ident?i=__be32">__be32</a> <a href="ident?i=saddr">saddr</a>,
<a name="L323" href="source/net/ipv4/udp.c#L323">323</a>                               unsigned int <a href="ident?i=port">port</a>)
<a name="L324" href="source/net/ipv4/udp.c#L324">324</a> {
<a name="L325" href="source/net/ipv4/udp.c#L325">325</a>         return <a href="ident?i=jhash_1word">jhash_1word</a>((<a href="ident?i=__force">__force</a> <a href="ident?i=u32">u32</a>)<a href="ident?i=saddr">saddr</a>, <a href="ident?i=net_hash_mix">net_hash_mix</a>(<a href="ident?i=net">net</a>)) ^ <a href="ident?i=port">port</a>;
<a name="L326" href="source/net/ipv4/udp.c#L326">326</a> }
<a name="L327" href="source/net/ipv4/udp.c#L327">327</a> 
<a name="L328" href="source/net/ipv4/udp.c#L328">328</a> int <a href="ident?i=udp_v4_get_port">udp_v4_get_port</a>(struct <a href="ident?i=sock">sock</a> *sk, unsigned short snum)
<a name="L329" href="source/net/ipv4/udp.c#L329">329</a> {
<a name="L330" href="source/net/ipv4/udp.c#L330">330</a>         unsigned int hash2_nulladdr =
<a name="L331" href="source/net/ipv4/udp.c#L331">331</a>                 <a href="ident?i=udp4_portaddr_hash">udp4_portaddr_hash</a>(<a href="ident?i=sock_net">sock_net</a>(sk), <a href="ident?i=htonl">htonl</a>(<a href="ident?i=INADDR_ANY">INADDR_ANY</a>), snum);
<a name="L332" href="source/net/ipv4/udp.c#L332">332</a>         unsigned int hash2_partial =
<a name="L333" href="source/net/ipv4/udp.c#L333">333</a>                 <a href="ident?i=udp4_portaddr_hash">udp4_portaddr_hash</a>(<a href="ident?i=sock_net">sock_net</a>(sk), <a href="ident?i=inet_sk">inet_sk</a>(sk)-&gt;<a href="ident?i=inet_rcv_saddr">inet_rcv_saddr</a>, 0);
<a name="L334" href="source/net/ipv4/udp.c#L334">334</a> 
<a name="L335" href="source/net/ipv4/udp.c#L335">335</a>         <b><i>/* precompute partial secondary hash */</i></b>
<a name="L336" href="source/net/ipv4/udp.c#L336">336</a>         <a href="ident?i=udp_sk">udp_sk</a>(sk)-&gt;<a href="ident?i=udp_portaddr_hash">udp_portaddr_hash</a> = hash2_partial;
<a name="L337" href="source/net/ipv4/udp.c#L337">337</a>         return <a href="ident?i=udp_lib_get_port">udp_lib_get_port</a>(sk, snum, <a href="ident?i=ipv4_rcv_saddr_equal">ipv4_rcv_saddr_equal</a>, hash2_nulladdr);
<a name="L338" href="source/net/ipv4/udp.c#L338">338</a> }
<a name="L339" href="source/net/ipv4/udp.c#L339">339</a> 
<a name="L340" href="source/net/ipv4/udp.c#L340">340</a> static inline int <a href="ident?i=compute_score">compute_score</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>,
<a name="L341" href="source/net/ipv4/udp.c#L341">341</a>                                 <a href="ident?i=__be32">__be32</a> <a href="ident?i=saddr">saddr</a>, unsigned short hnum, <a href="ident?i=__be16">__be16</a> sport,
<a name="L342" href="source/net/ipv4/udp.c#L342">342</a>                                 <a href="ident?i=__be32">__be32</a> <a href="ident?i=daddr">daddr</a>, <a href="ident?i=__be16">__be16</a> dport, int dif)
<a name="L343" href="source/net/ipv4/udp.c#L343">343</a> {
<a name="L344" href="source/net/ipv4/udp.c#L344">344</a>         int <a href="ident?i=score">score</a>;
<a name="L345" href="source/net/ipv4/udp.c#L345">345</a>         struct <a href="ident?i=inet_sock">inet_sock</a> *inet;
<a name="L346" href="source/net/ipv4/udp.c#L346">346</a> 
<a name="L347" href="source/net/ipv4/udp.c#L347">347</a>         if (!<a href="ident?i=net_eq">net_eq</a>(<a href="ident?i=sock_net">sock_net</a>(sk), <a href="ident?i=net">net</a>) ||
<a name="L348" href="source/net/ipv4/udp.c#L348">348</a>             <a href="ident?i=udp_sk">udp_sk</a>(sk)-&gt;<a href="ident?i=udp_port_hash">udp_port_hash</a> != hnum ||
<a name="L349" href="source/net/ipv4/udp.c#L349">349</a>             <a href="ident?i=ipv6_only_sock">ipv6_only_sock</a>(sk))
<a name="L350" href="source/net/ipv4/udp.c#L350">350</a>                 return -1;
<a name="L351" href="source/net/ipv4/udp.c#L351">351</a> 
<a name="L352" href="source/net/ipv4/udp.c#L352">352</a>         <a href="ident?i=score">score</a> = (sk-&gt;<a href="ident?i=sk_family">sk_family</a> == <a href="ident?i=PF_INET">PF_INET</a>) ? 2 : 1;
<a name="L353" href="source/net/ipv4/udp.c#L353">353</a>         inet = <a href="ident?i=inet_sk">inet_sk</a>(sk);
<a name="L354" href="source/net/ipv4/udp.c#L354">354</a> 
<a name="L355" href="source/net/ipv4/udp.c#L355">355</a>         if (inet-&gt;<a href="ident?i=inet_rcv_saddr">inet_rcv_saddr</a>) {
<a name="L356" href="source/net/ipv4/udp.c#L356">356</a>                 if (inet-&gt;<a href="ident?i=inet_rcv_saddr">inet_rcv_saddr</a> != <a href="ident?i=daddr">daddr</a>)
<a name="L357" href="source/net/ipv4/udp.c#L357">357</a>                         return -1;
<a name="L358" href="source/net/ipv4/udp.c#L358">358</a>                 <a href="ident?i=score">score</a> += 4;
<a name="L359" href="source/net/ipv4/udp.c#L359">359</a>         }
<a name="L360" href="source/net/ipv4/udp.c#L360">360</a> 
<a name="L361" href="source/net/ipv4/udp.c#L361">361</a>         if (inet-&gt;<a href="ident?i=inet_daddr">inet_daddr</a>) {
<a name="L362" href="source/net/ipv4/udp.c#L362">362</a>                 if (inet-&gt;<a href="ident?i=inet_daddr">inet_daddr</a> != <a href="ident?i=saddr">saddr</a>)
<a name="L363" href="source/net/ipv4/udp.c#L363">363</a>                         return -1;
<a name="L364" href="source/net/ipv4/udp.c#L364">364</a>                 <a href="ident?i=score">score</a> += 4;
<a name="L365" href="source/net/ipv4/udp.c#L365">365</a>         }
<a name="L366" href="source/net/ipv4/udp.c#L366">366</a> 
<a name="L367" href="source/net/ipv4/udp.c#L367">367</a>         if (inet-&gt;<a href="ident?i=inet_dport">inet_dport</a>) {
<a name="L368" href="source/net/ipv4/udp.c#L368">368</a>                 if (inet-&gt;<a href="ident?i=inet_dport">inet_dport</a> != sport)
<a name="L369" href="source/net/ipv4/udp.c#L369">369</a>                         return -1;
<a name="L370" href="source/net/ipv4/udp.c#L370">370</a>                 <a href="ident?i=score">score</a> += 4;
<a name="L371" href="source/net/ipv4/udp.c#L371">371</a>         }
<a name="L372" href="source/net/ipv4/udp.c#L372">372</a> 
<a name="L373" href="source/net/ipv4/udp.c#L373">373</a>         if (sk-&gt;<a href="ident?i=sk_bound_dev_if">sk_bound_dev_if</a>) {
<a name="L374" href="source/net/ipv4/udp.c#L374">374</a>                 if (sk-&gt;<a href="ident?i=sk_bound_dev_if">sk_bound_dev_if</a> != dif)
<a name="L375" href="source/net/ipv4/udp.c#L375">375</a>                         return -1;
<a name="L376" href="source/net/ipv4/udp.c#L376">376</a>                 <a href="ident?i=score">score</a> += 4;
<a name="L377" href="source/net/ipv4/udp.c#L377">377</a>         }
<a name="L378" href="source/net/ipv4/udp.c#L378">378</a> 
<a name="L379" href="source/net/ipv4/udp.c#L379">379</a>         return <a href="ident?i=score">score</a>;
<a name="L380" href="source/net/ipv4/udp.c#L380">380</a> }
<a name="L381" href="source/net/ipv4/udp.c#L381">381</a> 
<a name="L382" href="source/net/ipv4/udp.c#L382">382</a> <b><i>/*</i></b>
<a name="L383" href="source/net/ipv4/udp.c#L383">383</a> <b><i> * In this second variant, we check (daddr, dport) matches (inet_rcv_sadd, inet_num)</i></b>
<a name="L384" href="source/net/ipv4/udp.c#L384">384</a> <b><i> */</i></b>
<a name="L385" href="source/net/ipv4/udp.c#L385">385</a> static inline int <a href="ident?i=compute_score2">compute_score2</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>,
<a name="L386" href="source/net/ipv4/udp.c#L386">386</a>                                  <a href="ident?i=__be32">__be32</a> <a href="ident?i=saddr">saddr</a>, <a href="ident?i=__be16">__be16</a> sport,
<a name="L387" href="source/net/ipv4/udp.c#L387">387</a>                                  <a href="ident?i=__be32">__be32</a> <a href="ident?i=daddr">daddr</a>, unsigned int hnum, int dif)
<a name="L388" href="source/net/ipv4/udp.c#L388">388</a> {
<a name="L389" href="source/net/ipv4/udp.c#L389">389</a>         int <a href="ident?i=score">score</a>;
<a name="L390" href="source/net/ipv4/udp.c#L390">390</a>         struct <a href="ident?i=inet_sock">inet_sock</a> *inet;
<a name="L391" href="source/net/ipv4/udp.c#L391">391</a> 
<a name="L392" href="source/net/ipv4/udp.c#L392">392</a>         if (!<a href="ident?i=net_eq">net_eq</a>(<a href="ident?i=sock_net">sock_net</a>(sk), <a href="ident?i=net">net</a>) ||
<a name="L393" href="source/net/ipv4/udp.c#L393">393</a>             <a href="ident?i=ipv6_only_sock">ipv6_only_sock</a>(sk))
<a name="L394" href="source/net/ipv4/udp.c#L394">394</a>                 return -1;
<a name="L395" href="source/net/ipv4/udp.c#L395">395</a> 
<a name="L396" href="source/net/ipv4/udp.c#L396">396</a>         inet = <a href="ident?i=inet_sk">inet_sk</a>(sk);
<a name="L397" href="source/net/ipv4/udp.c#L397">397</a> 
<a name="L398" href="source/net/ipv4/udp.c#L398">398</a>         if (inet-&gt;<a href="ident?i=inet_rcv_saddr">inet_rcv_saddr</a> != <a href="ident?i=daddr">daddr</a> ||
<a name="L399" href="source/net/ipv4/udp.c#L399">399</a>             inet-&gt;<a href="ident?i=inet_num">inet_num</a> != hnum)
<a name="L400" href="source/net/ipv4/udp.c#L400">400</a>                 return -1;
<a name="L401" href="source/net/ipv4/udp.c#L401">401</a> 
<a name="L402" href="source/net/ipv4/udp.c#L402">402</a>         <a href="ident?i=score">score</a> = (sk-&gt;<a href="ident?i=sk_family">sk_family</a> == <a href="ident?i=PF_INET">PF_INET</a>) ? 2 : 1;
<a name="L403" href="source/net/ipv4/udp.c#L403">403</a> 
<a name="L404" href="source/net/ipv4/udp.c#L404">404</a>         if (inet-&gt;<a href="ident?i=inet_daddr">inet_daddr</a>) {
<a name="L405" href="source/net/ipv4/udp.c#L405">405</a>                 if (inet-&gt;<a href="ident?i=inet_daddr">inet_daddr</a> != <a href="ident?i=saddr">saddr</a>)
<a name="L406" href="source/net/ipv4/udp.c#L406">406</a>                         return -1;
<a name="L407" href="source/net/ipv4/udp.c#L407">407</a>                 <a href="ident?i=score">score</a> += 4;
<a name="L408" href="source/net/ipv4/udp.c#L408">408</a>         }
<a name="L409" href="source/net/ipv4/udp.c#L409">409</a> 
<a name="L410" href="source/net/ipv4/udp.c#L410">410</a>         if (inet-&gt;<a href="ident?i=inet_dport">inet_dport</a>) {
<a name="L411" href="source/net/ipv4/udp.c#L411">411</a>                 if (inet-&gt;<a href="ident?i=inet_dport">inet_dport</a> != sport)
<a name="L412" href="source/net/ipv4/udp.c#L412">412</a>                         return -1;
<a name="L413" href="source/net/ipv4/udp.c#L413">413</a>                 <a href="ident?i=score">score</a> += 4;
<a name="L414" href="source/net/ipv4/udp.c#L414">414</a>         }
<a name="L415" href="source/net/ipv4/udp.c#L415">415</a> 
<a name="L416" href="source/net/ipv4/udp.c#L416">416</a>         if (sk-&gt;<a href="ident?i=sk_bound_dev_if">sk_bound_dev_if</a>) {
<a name="L417" href="source/net/ipv4/udp.c#L417">417</a>                 if (sk-&gt;<a href="ident?i=sk_bound_dev_if">sk_bound_dev_if</a> != dif)
<a name="L418" href="source/net/ipv4/udp.c#L418">418</a>                         return -1;
<a name="L419" href="source/net/ipv4/udp.c#L419">419</a>                 <a href="ident?i=score">score</a> += 4;
<a name="L420" href="source/net/ipv4/udp.c#L420">420</a>         }
<a name="L421" href="source/net/ipv4/udp.c#L421">421</a> 
<a name="L422" href="source/net/ipv4/udp.c#L422">422</a>         return <a href="ident?i=score">score</a>;
<a name="L423" href="source/net/ipv4/udp.c#L423">423</a> }
<a name="L424" href="source/net/ipv4/udp.c#L424">424</a> 
<a name="L425" href="source/net/ipv4/udp.c#L425">425</a> static <a href="ident?i=u32">u32</a> <a href="ident?i=udp_ehashfn">udp_ehashfn</a>(const struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>, const <a href="ident?i=__be32">__be32</a> <a href="ident?i=laddr">laddr</a>,
<a name="L426" href="source/net/ipv4/udp.c#L426">426</a>                        const <a href="ident?i=__u16">__u16</a> lport, const <a href="ident?i=__be32">__be32</a> faddr,
<a name="L427" href="source/net/ipv4/udp.c#L427">427</a>                        const <a href="ident?i=__be16">__be16</a> fport)
<a name="L428" href="source/net/ipv4/udp.c#L428">428</a> {
<a name="L429" href="source/net/ipv4/udp.c#L429">429</a>         static <a href="ident?i=u32">u32</a> udp_ehash_secret <a href="ident?i=__read_mostly">__read_mostly</a>;
<a name="L430" href="source/net/ipv4/udp.c#L430">430</a> 
<a name="L431" href="source/net/ipv4/udp.c#L431">431</a>         <a href="ident?i=net_get_random_once">net_get_random_once</a>(&amp;udp_ehash_secret, sizeof(udp_ehash_secret));
<a name="L432" href="source/net/ipv4/udp.c#L432">432</a> 
<a name="L433" href="source/net/ipv4/udp.c#L433">433</a>         return <a href="ident?i=__inet_ehashfn">__inet_ehashfn</a>(<a href="ident?i=laddr">laddr</a>, lport, faddr, fport,
<a name="L434" href="source/net/ipv4/udp.c#L434">434</a>                               udp_ehash_secret + <a href="ident?i=net_hash_mix">net_hash_mix</a>(<a href="ident?i=net">net</a>));
<a name="L435" href="source/net/ipv4/udp.c#L435">435</a> }
<a name="L436" href="source/net/ipv4/udp.c#L436">436</a> 
<a name="L437" href="source/net/ipv4/udp.c#L437">437</a> <b><i>/* called with read_rcu_lock() */</i></b>
<a name="L438" href="source/net/ipv4/udp.c#L438">438</a> static struct <a href="ident?i=sock">sock</a> *<a href="ident?i=udp4_lib_lookup2">udp4_lib_lookup2</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>,
<a name="L439" href="source/net/ipv4/udp.c#L439">439</a>                 <a href="ident?i=__be32">__be32</a> <a href="ident?i=saddr">saddr</a>, <a href="ident?i=__be16">__be16</a> sport,
<a name="L440" href="source/net/ipv4/udp.c#L440">440</a>                 <a href="ident?i=__be32">__be32</a> <a href="ident?i=daddr">daddr</a>, unsigned int hnum, int dif,
<a name="L441" href="source/net/ipv4/udp.c#L441">441</a>                 struct <a href="ident?i=udp_hslot">udp_hslot</a> *hslot2, unsigned int slot2)
<a name="L442" href="source/net/ipv4/udp.c#L442">442</a> {
<a name="L443" href="source/net/ipv4/udp.c#L443">443</a>         struct <a href="ident?i=sock">sock</a> *sk, *<a href="ident?i=result">result</a>;
<a name="L444" href="source/net/ipv4/udp.c#L444">444</a>         struct <a href="ident?i=hlist_nulls_node">hlist_nulls_node</a> *<a href="ident?i=node">node</a>;
<a name="L445" href="source/net/ipv4/udp.c#L445">445</a>         int <a href="ident?i=score">score</a>, badness, <a href="ident?i=matches">matches</a> = 0, reuseport = 0;
<a name="L446" href="source/net/ipv4/udp.c#L446">446</a>         <a href="ident?i=u32">u32</a> <a href="ident?i=hash">hash</a> = 0;
<a name="L447" href="source/net/ipv4/udp.c#L447">447</a> 
<a name="L448" href="source/net/ipv4/udp.c#L448">448</a> begin:
<a name="L449" href="source/net/ipv4/udp.c#L449">449</a>         <a href="ident?i=result">result</a> = <a href="ident?i=NULL">NULL</a>;
<a name="L450" href="source/net/ipv4/udp.c#L450">450</a>         badness = 0;
<a name="L451" href="source/net/ipv4/udp.c#L451">451</a>         <a href="ident?i=udp_portaddr_for_each_entry_rcu">udp_portaddr_for_each_entry_rcu</a>(sk, <a href="ident?i=node">node</a>, &amp;hslot2-&gt;<a href="ident?i=head">head</a>) {
<a name="L452" href="source/net/ipv4/udp.c#L452">452</a>                 <a href="ident?i=score">score</a> = <a href="ident?i=compute_score2">compute_score2</a>(sk, <a href="ident?i=net">net</a>, <a href="ident?i=saddr">saddr</a>, sport,
<a name="L453" href="source/net/ipv4/udp.c#L453">453</a>                                       <a href="ident?i=daddr">daddr</a>, hnum, dif);
<a name="L454" href="source/net/ipv4/udp.c#L454">454</a>                 if (<a href="ident?i=score">score</a> &gt; badness) {
<a name="L455" href="source/net/ipv4/udp.c#L455">455</a>                         <a href="ident?i=result">result</a> = sk;
<a name="L456" href="source/net/ipv4/udp.c#L456">456</a>                         badness = <a href="ident?i=score">score</a>;
<a name="L457" href="source/net/ipv4/udp.c#L457">457</a>                         reuseport = sk-&gt;<a href="ident?i=sk_reuseport">sk_reuseport</a>;
<a name="L458" href="source/net/ipv4/udp.c#L458">458</a>                         if (reuseport) {
<a name="L459" href="source/net/ipv4/udp.c#L459">459</a>                                 <a href="ident?i=hash">hash</a> = <a href="ident?i=udp_ehashfn">udp_ehashfn</a>(<a href="ident?i=net">net</a>, <a href="ident?i=daddr">daddr</a>, hnum,
<a name="L460" href="source/net/ipv4/udp.c#L460">460</a>                                                    <a href="ident?i=saddr">saddr</a>, sport);
<a name="L461" href="source/net/ipv4/udp.c#L461">461</a>                                 <a href="ident?i=matches">matches</a> = 1;
<a name="L462" href="source/net/ipv4/udp.c#L462">462</a>                         }
<a name="L463" href="source/net/ipv4/udp.c#L463">463</a>                 } else if (<a href="ident?i=score">score</a> == badness &amp;&amp; reuseport) {
<a name="L464" href="source/net/ipv4/udp.c#L464">464</a>                         <a href="ident?i=matches">matches</a>++;
<a name="L465" href="source/net/ipv4/udp.c#L465">465</a>                         if (<a href="ident?i=reciprocal_scale">reciprocal_scale</a>(<a href="ident?i=hash">hash</a>, <a href="ident?i=matches">matches</a>) == 0)
<a name="L466" href="source/net/ipv4/udp.c#L466">466</a>                                 <a href="ident?i=result">result</a> = sk;
<a name="L467" href="source/net/ipv4/udp.c#L467">467</a>                         <a href="ident?i=hash">hash</a> = <a href="ident?i=next_pseudo_random32">next_pseudo_random32</a>(<a href="ident?i=hash">hash</a>);
<a name="L468" href="source/net/ipv4/udp.c#L468">468</a>                 }
<a name="L469" href="source/net/ipv4/udp.c#L469">469</a>         }
<a name="L470" href="source/net/ipv4/udp.c#L470">470</a>         <b><i>/*</i></b>
<a name="L471" href="source/net/ipv4/udp.c#L471">471</a> <b><i>         * if the nulls value we got at the end of this lookup is</i></b>
<a name="L472" href="source/net/ipv4/udp.c#L472">472</a> <b><i>         * not the expected one, we must restart lookup.</i></b>
<a name="L473" href="source/net/ipv4/udp.c#L473">473</a> <b><i>         * We probably met an item that was moved to another chain.</i></b>
<a name="L474" href="source/net/ipv4/udp.c#L474">474</a> <b><i>         */</i></b>
<a name="L475" href="source/net/ipv4/udp.c#L475">475</a>         if (<a href="ident?i=get_nulls_value">get_nulls_value</a>(<a href="ident?i=node">node</a>) != slot2)
<a name="L476" href="source/net/ipv4/udp.c#L476">476</a>                 goto begin;
<a name="L477" href="source/net/ipv4/udp.c#L477">477</a>         if (<a href="ident?i=result">result</a>) {
<a name="L478" href="source/net/ipv4/udp.c#L478">478</a>                 if (<a href="ident?i=unlikely">unlikely</a>(!<a href="ident?i=atomic_inc_not_zero_hint">atomic_inc_not_zero_hint</a>(&amp;<a href="ident?i=result">result</a>-&gt;<a href="ident?i=sk_refcnt">sk_refcnt</a>, 2)))
<a name="L479" href="source/net/ipv4/udp.c#L479">479</a>                         <a href="ident?i=result">result</a> = <a href="ident?i=NULL">NULL</a>;
<a name="L480" href="source/net/ipv4/udp.c#L480">480</a>                 else if (<a href="ident?i=unlikely">unlikely</a>(<a href="ident?i=compute_score2">compute_score2</a>(<a href="ident?i=result">result</a>, <a href="ident?i=net">net</a>, <a href="ident?i=saddr">saddr</a>, sport,
<a name="L481" href="source/net/ipv4/udp.c#L481">481</a>                                   <a href="ident?i=daddr">daddr</a>, hnum, dif) &lt; badness)) {
<a name="L482" href="source/net/ipv4/udp.c#L482">482</a>                         <a href="ident?i=sock_put">sock_put</a>(<a href="ident?i=result">result</a>);
<a name="L483" href="source/net/ipv4/udp.c#L483">483</a>                         goto begin;
<a name="L484" href="source/net/ipv4/udp.c#L484">484</a>                 }
<a name="L485" href="source/net/ipv4/udp.c#L485">485</a>         }
<a name="L486" href="source/net/ipv4/udp.c#L486">486</a>         return <a href="ident?i=result">result</a>;
<a name="L487" href="source/net/ipv4/udp.c#L487">487</a> }
<a name="L488" href="source/net/ipv4/udp.c#L488">488</a> 
<a name="L489" href="source/net/ipv4/udp.c#L489">489</a> <b><i>/* UDP is nearly always wildcards out the wazoo, it makes no sense to try</i></b>
<a name="L490" href="source/net/ipv4/udp.c#L490">490</a> <b><i> * harder than this. -DaveM</i></b>
<a name="L491" href="source/net/ipv4/udp.c#L491">491</a> <b><i> */</i></b>
<a name="L492" href="source/net/ipv4/udp.c#L492">492</a> struct <a href="ident?i=sock">sock</a> *<a href="ident?i=__udp4_lib_lookup">__udp4_lib_lookup</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>, <a href="ident?i=__be32">__be32</a> <a href="ident?i=saddr">saddr</a>,
<a name="L493" href="source/net/ipv4/udp.c#L493">493</a>                 <a href="ident?i=__be16">__be16</a> sport, <a href="ident?i=__be32">__be32</a> <a href="ident?i=daddr">daddr</a>, <a href="ident?i=__be16">__be16</a> dport,
<a name="L494" href="source/net/ipv4/udp.c#L494">494</a>                 int dif, struct <a href="ident?i=udp_table">udp_table</a> *udptable)
<a name="L495" href="source/net/ipv4/udp.c#L495">495</a> {
<a name="L496" href="source/net/ipv4/udp.c#L496">496</a>         struct <a href="ident?i=sock">sock</a> *sk, *<a href="ident?i=result">result</a>;
<a name="L497" href="source/net/ipv4/udp.c#L497">497</a>         struct <a href="ident?i=hlist_nulls_node">hlist_nulls_node</a> *<a href="ident?i=node">node</a>;
<a name="L498" href="source/net/ipv4/udp.c#L498">498</a>         unsigned short hnum = <a href="ident?i=ntohs">ntohs</a>(dport);
<a name="L499" href="source/net/ipv4/udp.c#L499">499</a>         unsigned int hash2, slot2, <a href="ident?i=slot">slot</a> = <a href="ident?i=udp_hashfn">udp_hashfn</a>(<a href="ident?i=net">net</a>, hnum, udptable-&gt;<a href="ident?i=mask">mask</a>);
<a name="L500" href="source/net/ipv4/udp.c#L500">500</a>         struct <a href="ident?i=udp_hslot">udp_hslot</a> *hslot2, *hslot = &amp;udptable-&gt;<a href="ident?i=hash">hash</a>[<a href="ident?i=slot">slot</a>];
<a name="L501" href="source/net/ipv4/udp.c#L501">501</a>         int <a href="ident?i=score">score</a>, badness, <a href="ident?i=matches">matches</a> = 0, reuseport = 0;
<a name="L502" href="source/net/ipv4/udp.c#L502">502</a>         <a href="ident?i=u32">u32</a> <a href="ident?i=hash">hash</a> = 0;
<a name="L503" href="source/net/ipv4/udp.c#L503">503</a> 
<a name="L504" href="source/net/ipv4/udp.c#L504">504</a>         <a href="ident?i=rcu_read_lock">rcu_read_lock</a>();
<a name="L505" href="source/net/ipv4/udp.c#L505">505</a>         if (hslot-&gt;<a href="ident?i=count">count</a> &gt; 10) {
<a name="L506" href="source/net/ipv4/udp.c#L506">506</a>                 hash2 = <a href="ident?i=udp4_portaddr_hash">udp4_portaddr_hash</a>(<a href="ident?i=net">net</a>, <a href="ident?i=daddr">daddr</a>, hnum);
<a name="L507" href="source/net/ipv4/udp.c#L507">507</a>                 slot2 = hash2 &amp; udptable-&gt;<a href="ident?i=mask">mask</a>;
<a name="L508" href="source/net/ipv4/udp.c#L508">508</a>                 hslot2 = &amp;udptable-&gt;hash2[slot2];
<a name="L509" href="source/net/ipv4/udp.c#L509">509</a>                 if (hslot-&gt;<a href="ident?i=count">count</a> &lt; hslot2-&gt;<a href="ident?i=count">count</a>)
<a name="L510" href="source/net/ipv4/udp.c#L510">510</a>                         goto begin;
<a name="L511" href="source/net/ipv4/udp.c#L511">511</a> 
<a name="L512" href="source/net/ipv4/udp.c#L512">512</a>                 <a href="ident?i=result">result</a> = <a href="ident?i=udp4_lib_lookup2">udp4_lib_lookup2</a>(<a href="ident?i=net">net</a>, <a href="ident?i=saddr">saddr</a>, sport,
<a name="L513" href="source/net/ipv4/udp.c#L513">513</a>                                           <a href="ident?i=daddr">daddr</a>, hnum, dif,
<a name="L514" href="source/net/ipv4/udp.c#L514">514</a>                                           hslot2, slot2);
<a name="L515" href="source/net/ipv4/udp.c#L515">515</a>                 if (!<a href="ident?i=result">result</a>) {
<a name="L516" href="source/net/ipv4/udp.c#L516">516</a>                         hash2 = <a href="ident?i=udp4_portaddr_hash">udp4_portaddr_hash</a>(<a href="ident?i=net">net</a>, <a href="ident?i=htonl">htonl</a>(<a href="ident?i=INADDR_ANY">INADDR_ANY</a>), hnum);
<a name="L517" href="source/net/ipv4/udp.c#L517">517</a>                         slot2 = hash2 &amp; udptable-&gt;<a href="ident?i=mask">mask</a>;
<a name="L518" href="source/net/ipv4/udp.c#L518">518</a>                         hslot2 = &amp;udptable-&gt;hash2[slot2];
<a name="L519" href="source/net/ipv4/udp.c#L519">519</a>                         if (hslot-&gt;<a href="ident?i=count">count</a> &lt; hslot2-&gt;<a href="ident?i=count">count</a>)
<a name="L520" href="source/net/ipv4/udp.c#L520">520</a>                                 goto begin;
<a name="L521" href="source/net/ipv4/udp.c#L521">521</a> 
<a name="L522" href="source/net/ipv4/udp.c#L522">522</a>                         <a href="ident?i=result">result</a> = <a href="ident?i=udp4_lib_lookup2">udp4_lib_lookup2</a>(<a href="ident?i=net">net</a>, <a href="ident?i=saddr">saddr</a>, sport,
<a name="L523" href="source/net/ipv4/udp.c#L523">523</a>                                                   <a href="ident?i=htonl">htonl</a>(<a href="ident?i=INADDR_ANY">INADDR_ANY</a>), hnum, dif,
<a name="L524" href="source/net/ipv4/udp.c#L524">524</a>                                                   hslot2, slot2);
<a name="L525" href="source/net/ipv4/udp.c#L525">525</a>                 }
<a name="L526" href="source/net/ipv4/udp.c#L526">526</a>                 <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L527" href="source/net/ipv4/udp.c#L527">527</a>                 return <a href="ident?i=result">result</a>;
<a name="L528" href="source/net/ipv4/udp.c#L528">528</a>         }
<a name="L529" href="source/net/ipv4/udp.c#L529">529</a> begin:
<a name="L530" href="source/net/ipv4/udp.c#L530">530</a>         <a href="ident?i=result">result</a> = <a href="ident?i=NULL">NULL</a>;
<a name="L531" href="source/net/ipv4/udp.c#L531">531</a>         badness = 0;
<a name="L532" href="source/net/ipv4/udp.c#L532">532</a>         <a href="ident?i=sk_nulls_for_each_rcu">sk_nulls_for_each_rcu</a>(sk, <a href="ident?i=node">node</a>, &amp;hslot-&gt;<a href="ident?i=head">head</a>) {
<a name="L533" href="source/net/ipv4/udp.c#L533">533</a>                 <a href="ident?i=score">score</a> = <a href="ident?i=compute_score">compute_score</a>(sk, <a href="ident?i=net">net</a>, <a href="ident?i=saddr">saddr</a>, hnum, sport,
<a name="L534" href="source/net/ipv4/udp.c#L534">534</a>                                       <a href="ident?i=daddr">daddr</a>, dport, dif);
<a name="L535" href="source/net/ipv4/udp.c#L535">535</a>                 if (<a href="ident?i=score">score</a> &gt; badness) {
<a name="L536" href="source/net/ipv4/udp.c#L536">536</a>                         <a href="ident?i=result">result</a> = sk;
<a name="L537" href="source/net/ipv4/udp.c#L537">537</a>                         badness = <a href="ident?i=score">score</a>;
<a name="L538" href="source/net/ipv4/udp.c#L538">538</a>                         reuseport = sk-&gt;<a href="ident?i=sk_reuseport">sk_reuseport</a>;
<a name="L539" href="source/net/ipv4/udp.c#L539">539</a>                         if (reuseport) {
<a name="L540" href="source/net/ipv4/udp.c#L540">540</a>                                 <a href="ident?i=hash">hash</a> = <a href="ident?i=udp_ehashfn">udp_ehashfn</a>(<a href="ident?i=net">net</a>, <a href="ident?i=daddr">daddr</a>, hnum,
<a name="L541" href="source/net/ipv4/udp.c#L541">541</a>                                                    <a href="ident?i=saddr">saddr</a>, sport);
<a name="L542" href="source/net/ipv4/udp.c#L542">542</a>                                 <a href="ident?i=matches">matches</a> = 1;
<a name="L543" href="source/net/ipv4/udp.c#L543">543</a>                         }
<a name="L544" href="source/net/ipv4/udp.c#L544">544</a>                 } else if (<a href="ident?i=score">score</a> == badness &amp;&amp; reuseport) {
<a name="L545" href="source/net/ipv4/udp.c#L545">545</a>                         <a href="ident?i=matches">matches</a>++;
<a name="L546" href="source/net/ipv4/udp.c#L546">546</a>                         if (<a href="ident?i=reciprocal_scale">reciprocal_scale</a>(<a href="ident?i=hash">hash</a>, <a href="ident?i=matches">matches</a>) == 0)
<a name="L547" href="source/net/ipv4/udp.c#L547">547</a>                                 <a href="ident?i=result">result</a> = sk;
<a name="L548" href="source/net/ipv4/udp.c#L548">548</a>                         <a href="ident?i=hash">hash</a> = <a href="ident?i=next_pseudo_random32">next_pseudo_random32</a>(<a href="ident?i=hash">hash</a>);
<a name="L549" href="source/net/ipv4/udp.c#L549">549</a>                 }
<a name="L550" href="source/net/ipv4/udp.c#L550">550</a>         }
<a name="L551" href="source/net/ipv4/udp.c#L551">551</a>         <b><i>/*</i></b>
<a name="L552" href="source/net/ipv4/udp.c#L552">552</a> <b><i>         * if the nulls value we got at the end of this lookup is</i></b>
<a name="L553" href="source/net/ipv4/udp.c#L553">553</a> <b><i>         * not the expected one, we must restart lookup.</i></b>
<a name="L554" href="source/net/ipv4/udp.c#L554">554</a> <b><i>         * We probably met an item that was moved to another chain.</i></b>
<a name="L555" href="source/net/ipv4/udp.c#L555">555</a> <b><i>         */</i></b>
<a name="L556" href="source/net/ipv4/udp.c#L556">556</a>         if (<a href="ident?i=get_nulls_value">get_nulls_value</a>(<a href="ident?i=node">node</a>) != <a href="ident?i=slot">slot</a>)
<a name="L557" href="source/net/ipv4/udp.c#L557">557</a>                 goto begin;
<a name="L558" href="source/net/ipv4/udp.c#L558">558</a> 
<a name="L559" href="source/net/ipv4/udp.c#L559">559</a>         if (<a href="ident?i=result">result</a>) {
<a name="L560" href="source/net/ipv4/udp.c#L560">560</a>                 if (<a href="ident?i=unlikely">unlikely</a>(!<a href="ident?i=atomic_inc_not_zero_hint">atomic_inc_not_zero_hint</a>(&amp;<a href="ident?i=result">result</a>-&gt;<a href="ident?i=sk_refcnt">sk_refcnt</a>, 2)))
<a name="L561" href="source/net/ipv4/udp.c#L561">561</a>                         <a href="ident?i=result">result</a> = <a href="ident?i=NULL">NULL</a>;
<a name="L562" href="source/net/ipv4/udp.c#L562">562</a>                 else if (<a href="ident?i=unlikely">unlikely</a>(<a href="ident?i=compute_score">compute_score</a>(<a href="ident?i=result">result</a>, <a href="ident?i=net">net</a>, <a href="ident?i=saddr">saddr</a>, hnum, sport,
<a name="L563" href="source/net/ipv4/udp.c#L563">563</a>                                   <a href="ident?i=daddr">daddr</a>, dport, dif) &lt; badness)) {
<a name="L564" href="source/net/ipv4/udp.c#L564">564</a>                         <a href="ident?i=sock_put">sock_put</a>(<a href="ident?i=result">result</a>);
<a name="L565" href="source/net/ipv4/udp.c#L565">565</a>                         goto begin;
<a name="L566" href="source/net/ipv4/udp.c#L566">566</a>                 }
<a name="L567" href="source/net/ipv4/udp.c#L567">567</a>         }
<a name="L568" href="source/net/ipv4/udp.c#L568">568</a>         <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L569" href="source/net/ipv4/udp.c#L569">569</a>         return <a href="ident?i=result">result</a>;
<a name="L570" href="source/net/ipv4/udp.c#L570">570</a> }
<a name="L571" href="source/net/ipv4/udp.c#L571">571</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=__udp4_lib_lookup">__udp4_lib_lookup</a>);
<a name="L572" href="source/net/ipv4/udp.c#L572">572</a> 
<a name="L573" href="source/net/ipv4/udp.c#L573">573</a> static inline struct <a href="ident?i=sock">sock</a> *<a href="ident?i=__udp4_lib_lookup_skb">__udp4_lib_lookup_skb</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
<a name="L574" href="source/net/ipv4/udp.c#L574">574</a>                                                  <a href="ident?i=__be16">__be16</a> sport, <a href="ident?i=__be16">__be16</a> dport,
<a name="L575" href="source/net/ipv4/udp.c#L575">575</a>                                                  struct <a href="ident?i=udp_table">udp_table</a> *udptable)
<a name="L576" href="source/net/ipv4/udp.c#L576">576</a> {
<a name="L577" href="source/net/ipv4/udp.c#L577">577</a>         const struct <a href="ident?i=iphdr">iphdr</a> *iph = <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>);
<a name="L578" href="source/net/ipv4/udp.c#L578">578</a> 
<a name="L579" href="source/net/ipv4/udp.c#L579">579</a>         return <a href="ident?i=__udp4_lib_lookup">__udp4_lib_lookup</a>(<a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=skb_dst">skb_dst</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=dev">dev</a>), iph-&gt;<a href="ident?i=saddr">saddr</a>, sport,
<a name="L580" href="source/net/ipv4/udp.c#L580">580</a>                                  iph-&gt;<a href="ident?i=daddr">daddr</a>, dport, <a href="ident?i=inet_iif">inet_iif</a>(<a href="ident?i=skb">skb</a>),
<a name="L581" href="source/net/ipv4/udp.c#L581">581</a>                                  udptable);
<a name="L582" href="source/net/ipv4/udp.c#L582">582</a> }
<a name="L583" href="source/net/ipv4/udp.c#L583">583</a> 
<a name="L584" href="source/net/ipv4/udp.c#L584">584</a> struct <a href="ident?i=sock">sock</a> *<a href="ident?i=udp4_lib_lookup">udp4_lib_lookup</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>, <a href="ident?i=__be32">__be32</a> <a href="ident?i=saddr">saddr</a>, <a href="ident?i=__be16">__be16</a> sport,
<a name="L585" href="source/net/ipv4/udp.c#L585">585</a>                              <a href="ident?i=__be32">__be32</a> <a href="ident?i=daddr">daddr</a>, <a href="ident?i=__be16">__be16</a> dport, int dif)
<a name="L586" href="source/net/ipv4/udp.c#L586">586</a> {
<a name="L587" href="source/net/ipv4/udp.c#L587">587</a>         return <a href="ident?i=__udp4_lib_lookup">__udp4_lib_lookup</a>(<a href="ident?i=net">net</a>, <a href="ident?i=saddr">saddr</a>, sport, <a href="ident?i=daddr">daddr</a>, dport, dif, &amp;<a href="ident?i=udp_table">udp_table</a>);
<a name="L588" href="source/net/ipv4/udp.c#L588">588</a> }
<a name="L589" href="source/net/ipv4/udp.c#L589">589</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=udp4_lib_lookup">udp4_lib_lookup</a>);
<a name="L590" href="source/net/ipv4/udp.c#L590">590</a> 
<a name="L591" href="source/net/ipv4/udp.c#L591">591</a> static inline <a href="ident?i=bool">bool</a> <a href="ident?i=__udp_is_mcast_sock">__udp_is_mcast_sock</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>, struct <a href="ident?i=sock">sock</a> *sk,
<a name="L592" href="source/net/ipv4/udp.c#L592">592</a>                                        <a href="ident?i=__be16">__be16</a> loc_port, <a href="ident?i=__be32">__be32</a> loc_addr,
<a name="L593" href="source/net/ipv4/udp.c#L593">593</a>                                        <a href="ident?i=__be16">__be16</a> rmt_port, <a href="ident?i=__be32">__be32</a> rmt_addr,
<a name="L594" href="source/net/ipv4/udp.c#L594">594</a>                                        int dif, unsigned short hnum)
<a name="L595" href="source/net/ipv4/udp.c#L595">595</a> {
<a name="L596" href="source/net/ipv4/udp.c#L596">596</a>         struct <a href="ident?i=inet_sock">inet_sock</a> *inet = <a href="ident?i=inet_sk">inet_sk</a>(sk);
<a name="L597" href="source/net/ipv4/udp.c#L597">597</a> 
<a name="L598" href="source/net/ipv4/udp.c#L598">598</a>         if (!<a href="ident?i=net_eq">net_eq</a>(<a href="ident?i=sock_net">sock_net</a>(sk), <a href="ident?i=net">net</a>) ||
<a name="L599" href="source/net/ipv4/udp.c#L599">599</a>             <a href="ident?i=udp_sk">udp_sk</a>(sk)-&gt;<a href="ident?i=udp_port_hash">udp_port_hash</a> != hnum ||
<a name="L600" href="source/net/ipv4/udp.c#L600">600</a>             (inet-&gt;<a href="ident?i=inet_daddr">inet_daddr</a> &amp;&amp; inet-&gt;<a href="ident?i=inet_daddr">inet_daddr</a> != rmt_addr) ||
<a name="L601" href="source/net/ipv4/udp.c#L601">601</a>             (inet-&gt;<a href="ident?i=inet_dport">inet_dport</a> != rmt_port &amp;&amp; inet-&gt;<a href="ident?i=inet_dport">inet_dport</a>) ||
<a name="L602" href="source/net/ipv4/udp.c#L602">602</a>             (inet-&gt;<a href="ident?i=inet_rcv_saddr">inet_rcv_saddr</a> &amp;&amp; inet-&gt;<a href="ident?i=inet_rcv_saddr">inet_rcv_saddr</a> != loc_addr) ||
<a name="L603" href="source/net/ipv4/udp.c#L603">603</a>             <a href="ident?i=ipv6_only_sock">ipv6_only_sock</a>(sk) ||
<a name="L604" href="source/net/ipv4/udp.c#L604">604</a>             (sk-&gt;<a href="ident?i=sk_bound_dev_if">sk_bound_dev_if</a> &amp;&amp; sk-&gt;<a href="ident?i=sk_bound_dev_if">sk_bound_dev_if</a> != dif))
<a name="L605" href="source/net/ipv4/udp.c#L605">605</a>                 return <a href="ident?i=false">false</a>;
<a name="L606" href="source/net/ipv4/udp.c#L606">606</a>         if (!<a href="ident?i=ip_mc_sf_allow">ip_mc_sf_allow</a>(sk, loc_addr, rmt_addr, dif))
<a name="L607" href="source/net/ipv4/udp.c#L607">607</a>                 return <a href="ident?i=false">false</a>;
<a name="L608" href="source/net/ipv4/udp.c#L608">608</a>         return <a href="ident?i=true">true</a>;
<a name="L609" href="source/net/ipv4/udp.c#L609">609</a> }
<a name="L610" href="source/net/ipv4/udp.c#L610">610</a> 
<a name="L611" href="source/net/ipv4/udp.c#L611">611</a> <b><i>/*</i></b>
<a name="L612" href="source/net/ipv4/udp.c#L612">612</a> <b><i> * This routine is called by the ICMP module when it gets some</i></b>
<a name="L613" href="source/net/ipv4/udp.c#L613">613</a> <b><i> * sort of error condition.  If err &lt; 0 then the socket should</i></b>
<a name="L614" href="source/net/ipv4/udp.c#L614">614</a> <b><i> * be closed and the error returned to the user.  If err &gt; 0</i></b>
<a name="L615" href="source/net/ipv4/udp.c#L615">615</a> <b><i> * it's just the icmp type &lt;&lt; 8 | icmp code.</i></b>
<a name="L616" href="source/net/ipv4/udp.c#L616">616</a> <b><i> * Header points to the ip header of the error packet. We move</i></b>
<a name="L617" href="source/net/ipv4/udp.c#L617">617</a> <b><i> * on past this. Then (as it used to claim before adjustment)</i></b>
<a name="L618" href="source/net/ipv4/udp.c#L618">618</a> <b><i> * header points to the first 8 bytes of the udp header.  We need</i></b>
<a name="L619" href="source/net/ipv4/udp.c#L619">619</a> <b><i> * to find the appropriate port.</i></b>
<a name="L620" href="source/net/ipv4/udp.c#L620">620</a> <b><i> */</i></b>
<a name="L621" href="source/net/ipv4/udp.c#L621">621</a> 
<a name="L622" href="source/net/ipv4/udp.c#L622">622</a> void <a href="ident?i=__udp4_lib_err">__udp4_lib_err</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, <a href="ident?i=u32">u32</a> <a href="ident?i=info">info</a>, struct <a href="ident?i=udp_table">udp_table</a> *udptable)
<a name="L623" href="source/net/ipv4/udp.c#L623">623</a> {
<a name="L624" href="source/net/ipv4/udp.c#L624">624</a>         struct <a href="ident?i=inet_sock">inet_sock</a> *inet;
<a name="L625" href="source/net/ipv4/udp.c#L625">625</a>         const struct <a href="ident?i=iphdr">iphdr</a> *iph = (const struct <a href="ident?i=iphdr">iphdr</a> *)<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=data">data</a>;
<a name="L626" href="source/net/ipv4/udp.c#L626">626</a>         struct <a href="ident?i=udphdr">udphdr</a> *uh = (struct <a href="ident?i=udphdr">udphdr</a> *)(<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=data">data</a>+(iph-&gt;ihl&lt;&lt;2));
<a name="L627" href="source/net/ipv4/udp.c#L627">627</a>         const int <a href="ident?i=type">type</a> = <a href="ident?i=icmp_hdr">icmp_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=type">type</a>;
<a name="L628" href="source/net/ipv4/udp.c#L628">628</a>         const int <a href="ident?i=code">code</a> = <a href="ident?i=icmp_hdr">icmp_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=code">code</a>;
<a name="L629" href="source/net/ipv4/udp.c#L629">629</a>         struct <a href="ident?i=sock">sock</a> *sk;
<a name="L630" href="source/net/ipv4/udp.c#L630">630</a>         int harderr;
<a name="L631" href="source/net/ipv4/udp.c#L631">631</a>         int <a href="ident?i=err">err</a>;
<a name="L632" href="source/net/ipv4/udp.c#L632">632</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=dev">dev</a>);
<a name="L633" href="source/net/ipv4/udp.c#L633">633</a> 
<a name="L634" href="source/net/ipv4/udp.c#L634">634</a>         sk = <a href="ident?i=__udp4_lib_lookup">__udp4_lib_lookup</a>(<a href="ident?i=net">net</a>, iph-&gt;<a href="ident?i=daddr">daddr</a>, uh-&gt;<a href="ident?i=dest">dest</a>,
<a name="L635" href="source/net/ipv4/udp.c#L635">635</a>                         iph-&gt;<a href="ident?i=saddr">saddr</a>, uh-&gt;source, <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=dev">dev</a>-&gt;ifindex, udptable);
<a name="L636" href="source/net/ipv4/udp.c#L636">636</a>         if (!sk) {
<a name="L637" href="source/net/ipv4/udp.c#L637">637</a>                 <a href="ident?i=ICMP_INC_STATS_BH">ICMP_INC_STATS_BH</a>(<a href="ident?i=net">net</a>, ICMP_MIB_INERRORS);
<a name="L638" href="source/net/ipv4/udp.c#L638">638</a>                 return; <b><i>/* No socket for error */</i></b>
<a name="L639" href="source/net/ipv4/udp.c#L639">639</a>         }
<a name="L640" href="source/net/ipv4/udp.c#L640">640</a> 
<a name="L641" href="source/net/ipv4/udp.c#L641">641</a>         <a href="ident?i=err">err</a> = 0;
<a name="L642" href="source/net/ipv4/udp.c#L642">642</a>         harderr = 0;
<a name="L643" href="source/net/ipv4/udp.c#L643">643</a>         inet = <a href="ident?i=inet_sk">inet_sk</a>(sk);
<a name="L644" href="source/net/ipv4/udp.c#L644">644</a> 
<a name="L645" href="source/net/ipv4/udp.c#L645">645</a>         switch (<a href="ident?i=type">type</a>) {
<a name="L646" href="source/net/ipv4/udp.c#L646">646</a>         default:
<a name="L647" href="source/net/ipv4/udp.c#L647">647</a>         case <a href="ident?i=ICMP_TIME_EXCEEDED">ICMP_TIME_EXCEEDED</a>:
<a name="L648" href="source/net/ipv4/udp.c#L648">648</a>                 <a href="ident?i=err">err</a> = <a href="ident?i=EHOSTUNREACH">EHOSTUNREACH</a>;
<a name="L649" href="source/net/ipv4/udp.c#L649">649</a>                 break;
<a name="L650" href="source/net/ipv4/udp.c#L650">650</a>         case <a href="ident?i=ICMP_SOURCE_QUENCH">ICMP_SOURCE_QUENCH</a>:
<a name="L651" href="source/net/ipv4/udp.c#L651">651</a>                 goto <a href="ident?i=out">out</a>;
<a name="L652" href="source/net/ipv4/udp.c#L652">652</a>         case <a href="ident?i=ICMP_PARAMETERPROB">ICMP_PARAMETERPROB</a>:
<a name="L653" href="source/net/ipv4/udp.c#L653">653</a>                 <a href="ident?i=err">err</a> = <a href="ident?i=EPROTO">EPROTO</a>;
<a name="L654" href="source/net/ipv4/udp.c#L654">654</a>                 harderr = 1;
<a name="L655" href="source/net/ipv4/udp.c#L655">655</a>                 break;
<a name="L656" href="source/net/ipv4/udp.c#L656">656</a>         case <a href="ident?i=ICMP_DEST_UNREACH">ICMP_DEST_UNREACH</a>:
<a name="L657" href="source/net/ipv4/udp.c#L657">657</a>                 if (<a href="ident?i=code">code</a> == <a href="ident?i=ICMP_FRAG_NEEDED">ICMP_FRAG_NEEDED</a>) { <b><i>/* Path MTU discovery */</i></b>
<a name="L658" href="source/net/ipv4/udp.c#L658">658</a>                         <a href="ident?i=ipv4_sk_update_pmtu">ipv4_sk_update_pmtu</a>(<a href="ident?i=skb">skb</a>, sk, <a href="ident?i=info">info</a>);
<a name="L659" href="source/net/ipv4/udp.c#L659">659</a>                         if (inet-&gt;pmtudisc != <a href="ident?i=IP_PMTUDISC_DONT">IP_PMTUDISC_DONT</a>) {
<a name="L660" href="source/net/ipv4/udp.c#L660">660</a>                                 <a href="ident?i=err">err</a> = <a href="ident?i=EMSGSIZE">EMSGSIZE</a>;
<a name="L661" href="source/net/ipv4/udp.c#L661">661</a>                                 harderr = 1;
<a name="L662" href="source/net/ipv4/udp.c#L662">662</a>                                 break;
<a name="L663" href="source/net/ipv4/udp.c#L663">663</a>                         }
<a name="L664" href="source/net/ipv4/udp.c#L664">664</a>                         goto <a href="ident?i=out">out</a>;
<a name="L665" href="source/net/ipv4/udp.c#L665">665</a>                 }
<a name="L666" href="source/net/ipv4/udp.c#L666">666</a>                 <a href="ident?i=err">err</a> = <a href="ident?i=EHOSTUNREACH">EHOSTUNREACH</a>;
<a name="L667" href="source/net/ipv4/udp.c#L667">667</a>                 if (<a href="ident?i=code">code</a> &lt;= <a href="ident?i=NR_ICMP_UNREACH">NR_ICMP_UNREACH</a>) {
<a name="L668" href="source/net/ipv4/udp.c#L668">668</a>                         harderr = <a href="ident?i=icmp_err_convert">icmp_err_convert</a>[<a href="ident?i=code">code</a>].<a href="ident?i=fatal">fatal</a>;
<a name="L669" href="source/net/ipv4/udp.c#L669">669</a>                         <a href="ident?i=err">err</a> = <a href="ident?i=icmp_err_convert">icmp_err_convert</a>[<a href="ident?i=code">code</a>].<a href="ident?i=errno">errno</a>;
<a name="L670" href="source/net/ipv4/udp.c#L670">670</a>                 }
<a name="L671" href="source/net/ipv4/udp.c#L671">671</a>                 break;
<a name="L672" href="source/net/ipv4/udp.c#L672">672</a>         case <a href="ident?i=ICMP_REDIRECT">ICMP_REDIRECT</a>:
<a name="L673" href="source/net/ipv4/udp.c#L673">673</a>                 <a href="ident?i=ipv4_sk_redirect">ipv4_sk_redirect</a>(<a href="ident?i=skb">skb</a>, sk);
<a name="L674" href="source/net/ipv4/udp.c#L674">674</a>                 goto <a href="ident?i=out">out</a>;
<a name="L675" href="source/net/ipv4/udp.c#L675">675</a>         }
<a name="L676" href="source/net/ipv4/udp.c#L676">676</a> 
<a name="L677" href="source/net/ipv4/udp.c#L677">677</a>         <b><i>/*</i></b>
<a name="L678" href="source/net/ipv4/udp.c#L678">678</a> <b><i>         *      RFC1122: OK.  Passes ICMP errors back to application, as per</i></b>
<a name="L679" href="source/net/ipv4/udp.c#L679">679</a> <b><i>         *      4.1.3.3.</i></b>
<a name="L680" href="source/net/ipv4/udp.c#L680">680</a> <b><i>         */</i></b>
<a name="L681" href="source/net/ipv4/udp.c#L681">681</a>         if (!inet-&gt;recverr) {
<a name="L682" href="source/net/ipv4/udp.c#L682">682</a>                 if (!harderr || sk-&gt;<a href="ident?i=sk_state">sk_state</a> != TCP_ESTABLISHED)
<a name="L683" href="source/net/ipv4/udp.c#L683">683</a>                         goto <a href="ident?i=out">out</a>;
<a name="L684" href="source/net/ipv4/udp.c#L684">684</a>         } else
<a name="L685" href="source/net/ipv4/udp.c#L685">685</a>                 <a href="ident?i=ip_icmp_error">ip_icmp_error</a>(sk, <a href="ident?i=skb">skb</a>, <a href="ident?i=err">err</a>, uh-&gt;<a href="ident?i=dest">dest</a>, <a href="ident?i=info">info</a>, (<a href="ident?i=u8">u8</a> *)(uh+1));
<a name="L686" href="source/net/ipv4/udp.c#L686">686</a> 
<a name="L687" href="source/net/ipv4/udp.c#L687">687</a>         sk-&gt;sk_err = <a href="ident?i=err">err</a>;
<a name="L688" href="source/net/ipv4/udp.c#L688">688</a>         sk-&gt;sk_error_report(sk);
<a name="L689" href="source/net/ipv4/udp.c#L689">689</a> <a href="ident?i=out">out</a>:
<a name="L690" href="source/net/ipv4/udp.c#L690">690</a>         <a href="ident?i=sock_put">sock_put</a>(sk);
<a name="L691" href="source/net/ipv4/udp.c#L691">691</a> }
<a name="L692" href="source/net/ipv4/udp.c#L692">692</a> 
<a name="L693" href="source/net/ipv4/udp.c#L693">693</a> void <a href="ident?i=udp_err">udp_err</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, <a href="ident?i=u32">u32</a> <a href="ident?i=info">info</a>)
<a name="L694" href="source/net/ipv4/udp.c#L694">694</a> {
<a name="L695" href="source/net/ipv4/udp.c#L695">695</a>         <a href="ident?i=__udp4_lib_err">__udp4_lib_err</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=info">info</a>, &amp;<a href="ident?i=udp_table">udp_table</a>);
<a name="L696" href="source/net/ipv4/udp.c#L696">696</a> }
<a name="L697" href="source/net/ipv4/udp.c#L697">697</a> 
<a name="L698" href="source/net/ipv4/udp.c#L698">698</a> <b><i>/*</i></b>
<a name="L699" href="source/net/ipv4/udp.c#L699">699</a> <b><i> * Throw away all pending data and cancel the corking. Socket is locked.</i></b>
<a name="L700" href="source/net/ipv4/udp.c#L700">700</a> <b><i> */</i></b>
<a name="L701" href="source/net/ipv4/udp.c#L701">701</a> void <a href="ident?i=udp_flush_pending_frames">udp_flush_pending_frames</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L702" href="source/net/ipv4/udp.c#L702">702</a> {
<a name="L703" href="source/net/ipv4/udp.c#L703">703</a>         struct <a href="ident?i=udp_sock">udp_sock</a> *<a href="ident?i=up">up</a> = <a href="ident?i=udp_sk">udp_sk</a>(sk);
<a name="L704" href="source/net/ipv4/udp.c#L704">704</a> 
<a name="L705" href="source/net/ipv4/udp.c#L705">705</a>         if (<a href="ident?i=up">up</a>-&gt;<a href="ident?i=pending">pending</a>) {
<a name="L706" href="source/net/ipv4/udp.c#L706">706</a>                 <a href="ident?i=up">up</a>-&gt;<a href="ident?i=len">len</a> = 0;
<a name="L707" href="source/net/ipv4/udp.c#L707">707</a>                 <a href="ident?i=up">up</a>-&gt;<a href="ident?i=pending">pending</a> = 0;
<a name="L708" href="source/net/ipv4/udp.c#L708">708</a>                 <a href="ident?i=ip_flush_pending_frames">ip_flush_pending_frames</a>(sk);
<a name="L709" href="source/net/ipv4/udp.c#L709">709</a>         }
<a name="L710" href="source/net/ipv4/udp.c#L710">710</a> }
<a name="L711" href="source/net/ipv4/udp.c#L711">711</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=udp_flush_pending_frames">udp_flush_pending_frames</a>);
<a name="L712" href="source/net/ipv4/udp.c#L712">712</a> 
<a name="L713" href="source/net/ipv4/udp.c#L713">713</a> <b><i>/**</i></b>
<a name="L714" href="source/net/ipv4/udp.c#L714">714</a> <b><i> *      udp4_hwcsum  -  handle outgoing HW checksumming</i></b>
<a name="L715" href="source/net/ipv4/udp.c#L715">715</a> <b><i> *      @skb:   sk_buff containing the filled-in UDP header</i></b>
<a name="L716" href="source/net/ipv4/udp.c#L716">716</a> <b><i> *              (checksum field must be zeroed out)</i></b>
<a name="L717" href="source/net/ipv4/udp.c#L717">717</a> <b><i> *      @src:   source IP address</i></b>
<a name="L718" href="source/net/ipv4/udp.c#L718">718</a> <b><i> *      @dst:   destination IP address</i></b>
<a name="L719" href="source/net/ipv4/udp.c#L719">719</a> <b><i> */</i></b>
<a name="L720" href="source/net/ipv4/udp.c#L720">720</a> void <a href="ident?i=udp4_hwcsum">udp4_hwcsum</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, <a href="ident?i=__be32">__be32</a> <a href="ident?i=src">src</a>, <a href="ident?i=__be32">__be32</a> <a href="ident?i=dst">dst</a>)
<a name="L721" href="source/net/ipv4/udp.c#L721">721</a> {
<a name="L722" href="source/net/ipv4/udp.c#L722">722</a>         struct <a href="ident?i=udphdr">udphdr</a> *uh = <a href="ident?i=udp_hdr">udp_hdr</a>(<a href="ident?i=skb">skb</a>);
<a name="L723" href="source/net/ipv4/udp.c#L723">723</a>         int <a href="ident?i=offset">offset</a> = <a href="ident?i=skb_transport_offset">skb_transport_offset</a>(<a href="ident?i=skb">skb</a>);
<a name="L724" href="source/net/ipv4/udp.c#L724">724</a>         int <a href="ident?i=len">len</a> = <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a> - <a href="ident?i=offset">offset</a>;
<a name="L725" href="source/net/ipv4/udp.c#L725">725</a>         int hlen = <a href="ident?i=len">len</a>;
<a name="L726" href="source/net/ipv4/udp.c#L726">726</a>         <a href="ident?i=__wsum">__wsum</a> <a href="ident?i=csum">csum</a> = 0;
<a name="L727" href="source/net/ipv4/udp.c#L727">727</a> 
<a name="L728" href="source/net/ipv4/udp.c#L728">728</a>         if (!<a href="ident?i=skb_has_frag_list">skb_has_frag_list</a>(<a href="ident?i=skb">skb</a>)) {
<a name="L729" href="source/net/ipv4/udp.c#L729">729</a>                 <b><i>/*</i></b>
<a name="L730" href="source/net/ipv4/udp.c#L730">730</a> <b><i>                 * Only one fragment on the socket.</i></b>
<a name="L731" href="source/net/ipv4/udp.c#L731">731</a> <b><i>                 */</i></b>
<a name="L732" href="source/net/ipv4/udp.c#L732">732</a>                 <a href="ident?i=skb">skb</a>-&gt;csum_start = <a href="ident?i=skb_transport_header">skb_transport_header</a>(<a href="ident?i=skb">skb</a>) - <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=head">head</a>;
<a name="L733" href="source/net/ipv4/udp.c#L733">733</a>                 <a href="ident?i=skb">skb</a>-&gt;csum_offset = <a href="ident?i=offsetof">offsetof</a>(struct <a href="ident?i=udphdr">udphdr</a>, <a href="ident?i=check">check</a>);
<a name="L734" href="source/net/ipv4/udp.c#L734">734</a>                 uh-&gt;<a href="ident?i=check">check</a> = ~csum_tcpudp_magic(<a href="ident?i=src">src</a>, <a href="ident?i=dst">dst</a>, <a href="ident?i=len">len</a>,
<a name="L735" href="source/net/ipv4/udp.c#L735">735</a>                                                <a href="ident?i=IPPROTO_UDP">IPPROTO_UDP</a>, 0);
<a name="L736" href="source/net/ipv4/udp.c#L736">736</a>         } else {
<a name="L737" href="source/net/ipv4/udp.c#L737">737</a>                 struct <a href="ident?i=sk_buff">sk_buff</a> *frags;
<a name="L738" href="source/net/ipv4/udp.c#L738">738</a> 
<a name="L739" href="source/net/ipv4/udp.c#L739">739</a>                 <b><i>/*</i></b>
<a name="L740" href="source/net/ipv4/udp.c#L740">740</a> <b><i>                 * HW-checksum won't work as there are two or more</i></b>
<a name="L741" href="source/net/ipv4/udp.c#L741">741</a> <b><i>                 * fragments on the socket so that all csums of sk_buffs</i></b>
<a name="L742" href="source/net/ipv4/udp.c#L742">742</a> <b><i>                 * should be together</i></b>
<a name="L743" href="source/net/ipv4/udp.c#L743">743</a> <b><i>                 */</i></b>
<a name="L744" href="source/net/ipv4/udp.c#L744">744</a>                 <a href="ident?i=skb_walk_frags">skb_walk_frags</a>(<a href="ident?i=skb">skb</a>, frags) {
<a name="L745" href="source/net/ipv4/udp.c#L745">745</a>                         <a href="ident?i=csum">csum</a> = <a href="ident?i=csum_add">csum_add</a>(<a href="ident?i=csum">csum</a>, frags-&gt;<a href="ident?i=csum">csum</a>);
<a name="L746" href="source/net/ipv4/udp.c#L746">746</a>                         hlen -= frags-&gt;<a href="ident?i=len">len</a>;
<a name="L747" href="source/net/ipv4/udp.c#L747">747</a>                 }
<a name="L748" href="source/net/ipv4/udp.c#L748">748</a> 
<a name="L749" href="source/net/ipv4/udp.c#L749">749</a>                 <a href="ident?i=csum">csum</a> = <a href="ident?i=skb_checksum">skb_checksum</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=offset">offset</a>, hlen, <a href="ident?i=csum">csum</a>);
<a name="L750" href="source/net/ipv4/udp.c#L750">750</a>                 <a href="ident?i=skb">skb</a>-&gt;ip_summed = <a href="ident?i=CHECKSUM_NONE">CHECKSUM_NONE</a>;
<a name="L751" href="source/net/ipv4/udp.c#L751">751</a> 
<a name="L752" href="source/net/ipv4/udp.c#L752">752</a>                 uh-&gt;<a href="ident?i=check">check</a> = <a href="ident?i=csum_tcpudp_magic">csum_tcpudp_magic</a>(<a href="ident?i=src">src</a>, <a href="ident?i=dst">dst</a>, <a href="ident?i=len">len</a>, <a href="ident?i=IPPROTO_UDP">IPPROTO_UDP</a>, <a href="ident?i=csum">csum</a>);
<a name="L753" href="source/net/ipv4/udp.c#L753">753</a>                 if (uh-&gt;<a href="ident?i=check">check</a> == 0)
<a name="L754" href="source/net/ipv4/udp.c#L754">754</a>                         uh-&gt;<a href="ident?i=check">check</a> = <a href="ident?i=CSUM_MANGLED_0">CSUM_MANGLED_0</a>;
<a name="L755" href="source/net/ipv4/udp.c#L755">755</a>         }
<a name="L756" href="source/net/ipv4/udp.c#L756">756</a> }
<a name="L757" href="source/net/ipv4/udp.c#L757">757</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=udp4_hwcsum">udp4_hwcsum</a>);
<a name="L758" href="source/net/ipv4/udp.c#L758">758</a> 
<a name="L759" href="source/net/ipv4/udp.c#L759">759</a> <b><i>/* Function to set UDP checksum for an IPv4 UDP packet. This is intended</i></b>
<a name="L760" href="source/net/ipv4/udp.c#L760">760</a> <b><i> * for the simple case like when setting the checksum for a UDP tunnel.</i></b>
<a name="L761" href="source/net/ipv4/udp.c#L761">761</a> <b><i> */</i></b>
<a name="L762" href="source/net/ipv4/udp.c#L762">762</a> void <a href="ident?i=udp_set_csum">udp_set_csum</a>(<a href="ident?i=bool">bool</a> nocheck, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
<a name="L763" href="source/net/ipv4/udp.c#L763">763</a>                   <a href="ident?i=__be32">__be32</a> <a href="ident?i=saddr">saddr</a>, <a href="ident?i=__be32">__be32</a> <a href="ident?i=daddr">daddr</a>, int <a href="ident?i=len">len</a>)
<a name="L764" href="source/net/ipv4/udp.c#L764">764</a> {
<a name="L765" href="source/net/ipv4/udp.c#L765">765</a>         struct <a href="ident?i=udphdr">udphdr</a> *uh = <a href="ident?i=udp_hdr">udp_hdr</a>(<a href="ident?i=skb">skb</a>);
<a name="L766" href="source/net/ipv4/udp.c#L766">766</a> 
<a name="L767" href="source/net/ipv4/udp.c#L767">767</a>         if (nocheck)
<a name="L768" href="source/net/ipv4/udp.c#L768">768</a>                 uh-&gt;<a href="ident?i=check">check</a> = 0;
<a name="L769" href="source/net/ipv4/udp.c#L769">769</a>         else if (<a href="ident?i=skb_is_gso">skb_is_gso</a>(<a href="ident?i=skb">skb</a>))
<a name="L770" href="source/net/ipv4/udp.c#L770">770</a>                 uh-&gt;<a href="ident?i=check">check</a> = ~udp_v4_check(<a href="ident?i=len">len</a>, <a href="ident?i=saddr">saddr</a>, <a href="ident?i=daddr">daddr</a>, 0);
<a name="L771" href="source/net/ipv4/udp.c#L771">771</a>         else if (<a href="ident?i=skb_dst">skb_dst</a>(<a href="ident?i=skb">skb</a>) &amp;&amp; <a href="ident?i=skb_dst">skb_dst</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=dev">dev</a> &amp;&amp;
<a name="L772" href="source/net/ipv4/udp.c#L772">772</a>                  (<a href="ident?i=skb_dst">skb_dst</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=dev">dev</a>-&gt;<a href="ident?i=features">features</a> &amp; <a href="ident?i=NETIF_F_V4_CSUM">NETIF_F_V4_CSUM</a>)) {
<a name="L773" href="source/net/ipv4/udp.c#L773">773</a> 
<a name="L774" href="source/net/ipv4/udp.c#L774">774</a>                 <a href="ident?i=BUG_ON">BUG_ON</a>(<a href="ident?i=skb">skb</a>-&gt;ip_summed == <a href="ident?i=CHECKSUM_PARTIAL">CHECKSUM_PARTIAL</a>);
<a name="L775" href="source/net/ipv4/udp.c#L775">775</a> 
<a name="L776" href="source/net/ipv4/udp.c#L776">776</a>                 <a href="ident?i=skb">skb</a>-&gt;ip_summed = <a href="ident?i=CHECKSUM_PARTIAL">CHECKSUM_PARTIAL</a>;
<a name="L777" href="source/net/ipv4/udp.c#L777">777</a>                 <a href="ident?i=skb">skb</a>-&gt;csum_start = <a href="ident?i=skb_transport_header">skb_transport_header</a>(<a href="ident?i=skb">skb</a>) - <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=head">head</a>;
<a name="L778" href="source/net/ipv4/udp.c#L778">778</a>                 <a href="ident?i=skb">skb</a>-&gt;csum_offset = <a href="ident?i=offsetof">offsetof</a>(struct <a href="ident?i=udphdr">udphdr</a>, <a href="ident?i=check">check</a>);
<a name="L779" href="source/net/ipv4/udp.c#L779">779</a>                 uh-&gt;<a href="ident?i=check">check</a> = ~udp_v4_check(<a href="ident?i=len">len</a>, <a href="ident?i=saddr">saddr</a>, <a href="ident?i=daddr">daddr</a>, 0);
<a name="L780" href="source/net/ipv4/udp.c#L780">780</a>         } else {
<a name="L781" href="source/net/ipv4/udp.c#L781">781</a>                 <a href="ident?i=__wsum">__wsum</a> <a href="ident?i=csum">csum</a>;
<a name="L782" href="source/net/ipv4/udp.c#L782">782</a> 
<a name="L783" href="source/net/ipv4/udp.c#L783">783</a>                 <a href="ident?i=BUG_ON">BUG_ON</a>(<a href="ident?i=skb">skb</a>-&gt;ip_summed == <a href="ident?i=CHECKSUM_PARTIAL">CHECKSUM_PARTIAL</a>);
<a name="L784" href="source/net/ipv4/udp.c#L784">784</a> 
<a name="L785" href="source/net/ipv4/udp.c#L785">785</a>                 uh-&gt;<a href="ident?i=check">check</a> = 0;
<a name="L786" href="source/net/ipv4/udp.c#L786">786</a>                 <a href="ident?i=csum">csum</a> = <a href="ident?i=skb_checksum">skb_checksum</a>(<a href="ident?i=skb">skb</a>, 0, <a href="ident?i=len">len</a>, 0);
<a name="L787" href="source/net/ipv4/udp.c#L787">787</a>                 uh-&gt;<a href="ident?i=check">check</a> = <a href="ident?i=udp_v4_check">udp_v4_check</a>(<a href="ident?i=len">len</a>, <a href="ident?i=saddr">saddr</a>, <a href="ident?i=daddr">daddr</a>, <a href="ident?i=csum">csum</a>);
<a name="L788" href="source/net/ipv4/udp.c#L788">788</a>                 if (uh-&gt;<a href="ident?i=check">check</a> == 0)
<a name="L789" href="source/net/ipv4/udp.c#L789">789</a>                         uh-&gt;<a href="ident?i=check">check</a> = <a href="ident?i=CSUM_MANGLED_0">CSUM_MANGLED_0</a>;
<a name="L790" href="source/net/ipv4/udp.c#L790">790</a> 
<a name="L791" href="source/net/ipv4/udp.c#L791">791</a>                 <a href="ident?i=skb">skb</a>-&gt;ip_summed = <a href="ident?i=CHECKSUM_UNNECESSARY">CHECKSUM_UNNECESSARY</a>;
<a name="L792" href="source/net/ipv4/udp.c#L792">792</a>         }
<a name="L793" href="source/net/ipv4/udp.c#L793">793</a> }
<a name="L794" href="source/net/ipv4/udp.c#L794">794</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=udp_set_csum">udp_set_csum</a>);
<a name="L795" href="source/net/ipv4/udp.c#L795">795</a> 
<a name="L796" href="source/net/ipv4/udp.c#L796">796</a> static int <a href="ident?i=udp_send_skb">udp_send_skb</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, struct <a href="ident?i=flowi4">flowi4</a> *fl4)
<a name="L797" href="source/net/ipv4/udp.c#L797">797</a> {
<a name="L798" href="source/net/ipv4/udp.c#L798">798</a>         struct <a href="ident?i=sock">sock</a> *sk = <a href="ident?i=skb">skb</a>-&gt;sk;
<a name="L799" href="source/net/ipv4/udp.c#L799">799</a>         struct <a href="ident?i=inet_sock">inet_sock</a> *inet = <a href="ident?i=inet_sk">inet_sk</a>(sk);
<a name="L800" href="source/net/ipv4/udp.c#L800">800</a>         struct <a href="ident?i=udphdr">udphdr</a> *uh;
<a name="L801" href="source/net/ipv4/udp.c#L801">801</a>         int <a href="ident?i=err">err</a> = 0;
<a name="L802" href="source/net/ipv4/udp.c#L802">802</a>         int is_udplite = <a href="ident?i=IS_UDPLITE">IS_UDPLITE</a>(sk);
<a name="L803" href="source/net/ipv4/udp.c#L803">803</a>         int <a href="ident?i=offset">offset</a> = <a href="ident?i=skb_transport_offset">skb_transport_offset</a>(<a href="ident?i=skb">skb</a>);
<a name="L804" href="source/net/ipv4/udp.c#L804">804</a>         int <a href="ident?i=len">len</a> = <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a> - <a href="ident?i=offset">offset</a>;
<a name="L805" href="source/net/ipv4/udp.c#L805">805</a>         <a href="ident?i=__wsum">__wsum</a> <a href="ident?i=csum">csum</a> = 0;
<a name="L806" href="source/net/ipv4/udp.c#L806">806</a> 
<a name="L807" href="source/net/ipv4/udp.c#L807">807</a>         <b><i>/*</i></b>
<a name="L808" href="source/net/ipv4/udp.c#L808">808</a> <b><i>         * Create a UDP header</i></b>
<a name="L809" href="source/net/ipv4/udp.c#L809">809</a> <b><i>         */</i></b>
<a name="L810" href="source/net/ipv4/udp.c#L810">810</a>         uh = <a href="ident?i=udp_hdr">udp_hdr</a>(<a href="ident?i=skb">skb</a>);
<a name="L811" href="source/net/ipv4/udp.c#L811">811</a>         uh-&gt;source = inet-&gt;inet_sport;
<a name="L812" href="source/net/ipv4/udp.c#L812">812</a>         uh-&gt;<a href="ident?i=dest">dest</a> = fl4-&gt;<a href="ident?i=fl4_dport">fl4_dport</a>;
<a name="L813" href="source/net/ipv4/udp.c#L813">813</a>         uh-&gt;<a href="ident?i=len">len</a> = <a href="ident?i=htons">htons</a>(<a href="ident?i=len">len</a>);
<a name="L814" href="source/net/ipv4/udp.c#L814">814</a>         uh-&gt;<a href="ident?i=check">check</a> = 0;
<a name="L815" href="source/net/ipv4/udp.c#L815">815</a> 
<a name="L816" href="source/net/ipv4/udp.c#L816">816</a>         if (is_udplite)                                  <b><i>/*     UDP-Lite      */</i></b>
<a name="L817" href="source/net/ipv4/udp.c#L817">817</a>                 <a href="ident?i=csum">csum</a> = <a href="ident?i=udplite_csum">udplite_csum</a>(<a href="ident?i=skb">skb</a>);
<a name="L818" href="source/net/ipv4/udp.c#L818">818</a> 
<a name="L819" href="source/net/ipv4/udp.c#L819">819</a>         else if (sk-&gt;sk_no_check_tx) {   <b><i>/* UDP csum disabled */</i></b>
<a name="L820" href="source/net/ipv4/udp.c#L820">820</a> 
<a name="L821" href="source/net/ipv4/udp.c#L821">821</a>                 <a href="ident?i=skb">skb</a>-&gt;ip_summed = <a href="ident?i=CHECKSUM_NONE">CHECKSUM_NONE</a>;
<a name="L822" href="source/net/ipv4/udp.c#L822">822</a>                 goto send;
<a name="L823" href="source/net/ipv4/udp.c#L823">823</a> 
<a name="L824" href="source/net/ipv4/udp.c#L824">824</a>         } else if (<a href="ident?i=skb">skb</a>-&gt;ip_summed == <a href="ident?i=CHECKSUM_PARTIAL">CHECKSUM_PARTIAL</a>) { <b><i>/* UDP hardware csum */</i></b>
<a name="L825" href="source/net/ipv4/udp.c#L825">825</a> 
<a name="L826" href="source/net/ipv4/udp.c#L826">826</a>                 <a href="ident?i=udp4_hwcsum">udp4_hwcsum</a>(<a href="ident?i=skb">skb</a>, fl4-&gt;<a href="ident?i=saddr">saddr</a>, fl4-&gt;<a href="ident?i=daddr">daddr</a>);
<a name="L827" href="source/net/ipv4/udp.c#L827">827</a>                 goto send;
<a name="L828" href="source/net/ipv4/udp.c#L828">828</a> 
<a name="L829" href="source/net/ipv4/udp.c#L829">829</a>         } else
<a name="L830" href="source/net/ipv4/udp.c#L830">830</a>                 <a href="ident?i=csum">csum</a> = <a href="ident?i=udp_csum">udp_csum</a>(<a href="ident?i=skb">skb</a>);
<a name="L831" href="source/net/ipv4/udp.c#L831">831</a> 
<a name="L832" href="source/net/ipv4/udp.c#L832">832</a>         <b><i>/* add protocol-dependent pseudo-header */</i></b>
<a name="L833" href="source/net/ipv4/udp.c#L833">833</a>         uh-&gt;<a href="ident?i=check">check</a> = <a href="ident?i=csum_tcpudp_magic">csum_tcpudp_magic</a>(fl4-&gt;<a href="ident?i=saddr">saddr</a>, fl4-&gt;<a href="ident?i=daddr">daddr</a>, <a href="ident?i=len">len</a>,
<a name="L834" href="source/net/ipv4/udp.c#L834">834</a>                                       sk-&gt;sk_protocol, <a href="ident?i=csum">csum</a>);
<a name="L835" href="source/net/ipv4/udp.c#L835">835</a>         if (uh-&gt;<a href="ident?i=check">check</a> == 0)
<a name="L836" href="source/net/ipv4/udp.c#L836">836</a>                 uh-&gt;<a href="ident?i=check">check</a> = <a href="ident?i=CSUM_MANGLED_0">CSUM_MANGLED_0</a>;
<a name="L837" href="source/net/ipv4/udp.c#L837">837</a> 
<a name="L838" href="source/net/ipv4/udp.c#L838">838</a> send:
<a name="L839" href="source/net/ipv4/udp.c#L839">839</a>         <a href="ident?i=err">err</a> = <a href="ident?i=ip_send_skb">ip_send_skb</a>(<a href="ident?i=sock_net">sock_net</a>(sk), <a href="ident?i=skb">skb</a>);
<a name="L840" href="source/net/ipv4/udp.c#L840">840</a>         if (<a href="ident?i=err">err</a>) {
<a name="L841" href="source/net/ipv4/udp.c#L841">841</a>                 if (<a href="ident?i=err">err</a> == -<a href="ident?i=ENOBUFS">ENOBUFS</a> &amp;&amp; !inet-&gt;recverr) {
<a name="L842" href="source/net/ipv4/udp.c#L842">842</a>                         <a href="ident?i=UDP_INC_STATS_USER">UDP_INC_STATS_USER</a>(<a href="ident?i=sock_net">sock_net</a>(sk),
<a name="L843" href="source/net/ipv4/udp.c#L843">843</a>                                            UDP_MIB_SNDBUFERRORS, is_udplite);
<a name="L844" href="source/net/ipv4/udp.c#L844">844</a>                         <a href="ident?i=err">err</a> = 0;
<a name="L845" href="source/net/ipv4/udp.c#L845">845</a>                 }
<a name="L846" href="source/net/ipv4/udp.c#L846">846</a>         } else
<a name="L847" href="source/net/ipv4/udp.c#L847">847</a>                 <a href="ident?i=UDP_INC_STATS_USER">UDP_INC_STATS_USER</a>(<a href="ident?i=sock_net">sock_net</a>(sk),
<a name="L848" href="source/net/ipv4/udp.c#L848">848</a>                                    UDP_MIB_OUTDATAGRAMS, is_udplite);
<a name="L849" href="source/net/ipv4/udp.c#L849">849</a>         return <a href="ident?i=err">err</a>;
<a name="L850" href="source/net/ipv4/udp.c#L850">850</a> }
<a name="L851" href="source/net/ipv4/udp.c#L851">851</a> 
<a name="L852" href="source/net/ipv4/udp.c#L852">852</a> <b><i>/*</i></b>
<a name="L853" href="source/net/ipv4/udp.c#L853">853</a> <b><i> * Push out all pending data as one UDP datagram. Socket is locked.</i></b>
<a name="L854" href="source/net/ipv4/udp.c#L854">854</a> <b><i> */</i></b>
<a name="L855" href="source/net/ipv4/udp.c#L855">855</a> int <a href="ident?i=udp_push_pending_frames">udp_push_pending_frames</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L856" href="source/net/ipv4/udp.c#L856">856</a> {
<a name="L857" href="source/net/ipv4/udp.c#L857">857</a>         struct <a href="ident?i=udp_sock">udp_sock</a>  *<a href="ident?i=up">up</a> = <a href="ident?i=udp_sk">udp_sk</a>(sk);
<a name="L858" href="source/net/ipv4/udp.c#L858">858</a>         struct <a href="ident?i=inet_sock">inet_sock</a> *inet = <a href="ident?i=inet_sk">inet_sk</a>(sk);
<a name="L859" href="source/net/ipv4/udp.c#L859">859</a>         struct <a href="ident?i=flowi4">flowi4</a> *fl4 = &amp;inet-&gt;cork.fl.u.ip4;
<a name="L860" href="source/net/ipv4/udp.c#L860">860</a>         struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>;
<a name="L861" href="source/net/ipv4/udp.c#L861">861</a>         int <a href="ident?i=err">err</a> = 0;
<a name="L862" href="source/net/ipv4/udp.c#L862">862</a> 
<a name="L863" href="source/net/ipv4/udp.c#L863">863</a>         <a href="ident?i=skb">skb</a> = <a href="ident?i=ip_finish_skb">ip_finish_skb</a>(sk, fl4);
<a name="L864" href="source/net/ipv4/udp.c#L864">864</a>         if (!<a href="ident?i=skb">skb</a>)
<a name="L865" href="source/net/ipv4/udp.c#L865">865</a>                 goto <a href="ident?i=out">out</a>;
<a name="L866" href="source/net/ipv4/udp.c#L866">866</a> 
<a name="L867" href="source/net/ipv4/udp.c#L867">867</a>         <a href="ident?i=err">err</a> = <a href="ident?i=udp_send_skb">udp_send_skb</a>(<a href="ident?i=skb">skb</a>, fl4);
<a name="L868" href="source/net/ipv4/udp.c#L868">868</a> 
<a name="L869" href="source/net/ipv4/udp.c#L869">869</a> <a href="ident?i=out">out</a>:
<a name="L870" href="source/net/ipv4/udp.c#L870">870</a>         <a href="ident?i=up">up</a>-&gt;<a href="ident?i=len">len</a> = 0;
<a name="L871" href="source/net/ipv4/udp.c#L871">871</a>         <a href="ident?i=up">up</a>-&gt;<a href="ident?i=pending">pending</a> = 0;
<a name="L872" href="source/net/ipv4/udp.c#L872">872</a>         return <a href="ident?i=err">err</a>;
<a name="L873" href="source/net/ipv4/udp.c#L873">873</a> }
<a name="L874" href="source/net/ipv4/udp.c#L874">874</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=udp_push_pending_frames">udp_push_pending_frames</a>);
<a name="L875" href="source/net/ipv4/udp.c#L875">875</a> 
<a name="L876" href="source/net/ipv4/udp.c#L876">876</a> int <a href="ident?i=udp_sendmsg">udp_sendmsg</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=msghdr">msghdr</a> *<a href="ident?i=msg">msg</a>, <a href="ident?i=size_t">size_t</a> <a href="ident?i=len">len</a>)
<a name="L877" href="source/net/ipv4/udp.c#L877">877</a> {
<a name="L878" href="source/net/ipv4/udp.c#L878">878</a>         struct <a href="ident?i=inet_sock">inet_sock</a> *inet = <a href="ident?i=inet_sk">inet_sk</a>(sk);
<a name="L879" href="source/net/ipv4/udp.c#L879">879</a>         struct <a href="ident?i=udp_sock">udp_sock</a> *<a href="ident?i=up">up</a> = <a href="ident?i=udp_sk">udp_sk</a>(sk);
<a name="L880" href="source/net/ipv4/udp.c#L880">880</a>         struct <a href="ident?i=flowi4">flowi4</a> fl4_stack;
<a name="L881" href="source/net/ipv4/udp.c#L881">881</a>         struct <a href="ident?i=flowi4">flowi4</a> *fl4;
<a name="L882" href="source/net/ipv4/udp.c#L882">882</a>         int ulen = <a href="ident?i=len">len</a>;
<a name="L883" href="source/net/ipv4/udp.c#L883">883</a>         struct <a href="ident?i=ipcm_cookie">ipcm_cookie</a> ipc;
<a name="L884" href="source/net/ipv4/udp.c#L884">884</a>         struct <a href="ident?i=rtable">rtable</a> *<a href="ident?i=rt">rt</a> = <a href="ident?i=NULL">NULL</a>;
<a name="L885" href="source/net/ipv4/udp.c#L885">885</a>         int <a href="ident?i=free">free</a> = 0;
<a name="L886" href="source/net/ipv4/udp.c#L886">886</a>         int <a href="ident?i=connected">connected</a> = 0;
<a name="L887" href="source/net/ipv4/udp.c#L887">887</a>         <a href="ident?i=__be32">__be32</a> <a href="ident?i=daddr">daddr</a>, faddr, <a href="ident?i=saddr">saddr</a>;
<a name="L888" href="source/net/ipv4/udp.c#L888">888</a>         <a href="ident?i=__be16">__be16</a> dport;
<a name="L889" href="source/net/ipv4/udp.c#L889">889</a>         <a href="ident?i=u8">u8</a>  tos;
<a name="L890" href="source/net/ipv4/udp.c#L890">890</a>         int <a href="ident?i=err">err</a>, is_udplite = <a href="ident?i=IS_UDPLITE">IS_UDPLITE</a>(sk);
<a name="L891" href="source/net/ipv4/udp.c#L891">891</a>         int corkreq = <a href="ident?i=up">up</a>-&gt;corkflag || <a href="ident?i=msg">msg</a>-&gt;msg_flags&amp;<a href="ident?i=MSG_MORE">MSG_MORE</a>;
<a name="L892" href="source/net/ipv4/udp.c#L892">892</a>         int (*getfrag)(void *, char *, int, int, int, struct <a href="ident?i=sk_buff">sk_buff</a> *);
<a name="L893" href="source/net/ipv4/udp.c#L893">893</a>         struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>;
<a name="L894" href="source/net/ipv4/udp.c#L894">894</a>         struct <a href="ident?i=ip_options_data">ip_options_data</a> opt_copy;
<a name="L895" href="source/net/ipv4/udp.c#L895">895</a> 
<a name="L896" href="source/net/ipv4/udp.c#L896">896</a>         if (<a href="ident?i=len">len</a> &gt; 0xFFFF)
<a name="L897" href="source/net/ipv4/udp.c#L897">897</a>                 return -<a href="ident?i=EMSGSIZE">EMSGSIZE</a>;
<a name="L898" href="source/net/ipv4/udp.c#L898">898</a> 
<a name="L899" href="source/net/ipv4/udp.c#L899">899</a>         <b><i>/*</i></b>
<a name="L900" href="source/net/ipv4/udp.c#L900">900</a> <b><i>         *      Check the flags.</i></b>
<a name="L901" href="source/net/ipv4/udp.c#L901">901</a> <b><i>         */</i></b>
<a name="L902" href="source/net/ipv4/udp.c#L902">902</a> 
<a name="L903" href="source/net/ipv4/udp.c#L903">903</a>         if (<a href="ident?i=msg">msg</a>-&gt;msg_flags &amp; <a href="ident?i=MSG_OOB">MSG_OOB</a>) <b><i>/* Mirror BSD error message compatibility */</i></b>
<a name="L904" href="source/net/ipv4/udp.c#L904">904</a>                 return -<a href="ident?i=EOPNOTSUPP">EOPNOTSUPP</a>;
<a name="L905" href="source/net/ipv4/udp.c#L905">905</a> 
<a name="L906" href="source/net/ipv4/udp.c#L906">906</a>         ipc.opt = <a href="ident?i=NULL">NULL</a>;
<a name="L907" href="source/net/ipv4/udp.c#L907">907</a>         ipc.tx_flags = 0;
<a name="L908" href="source/net/ipv4/udp.c#L908">908</a>         ipc.<a href="ident?i=ttl">ttl</a> = 0;
<a name="L909" href="source/net/ipv4/udp.c#L909">909</a>         ipc.tos = -1;
<a name="L910" href="source/net/ipv4/udp.c#L910">910</a> 
<a name="L911" href="source/net/ipv4/udp.c#L911">911</a>         getfrag = is_udplite ? <a href="ident?i=udplite_getfrag">udplite_getfrag</a> : <a href="ident?i=ip_generic_getfrag">ip_generic_getfrag</a>;
<a name="L912" href="source/net/ipv4/udp.c#L912">912</a> 
<a name="L913" href="source/net/ipv4/udp.c#L913">913</a>         fl4 = &amp;inet-&gt;cork.fl.u.ip4;
<a name="L914" href="source/net/ipv4/udp.c#L914">914</a>         if (<a href="ident?i=up">up</a>-&gt;<a href="ident?i=pending">pending</a>) {
<a name="L915" href="source/net/ipv4/udp.c#L915">915</a>                 <b><i>/*</i></b>
<a name="L916" href="source/net/ipv4/udp.c#L916">916</a> <b><i>                 * There are pending frames.</i></b>
<a name="L917" href="source/net/ipv4/udp.c#L917">917</a> <b><i>                 * The socket lock must be held while it's corked.</i></b>
<a name="L918" href="source/net/ipv4/udp.c#L918">918</a> <b><i>                 */</i></b>
<a name="L919" href="source/net/ipv4/udp.c#L919">919</a>                 <a href="ident?i=lock_sock">lock_sock</a>(sk);
<a name="L920" href="source/net/ipv4/udp.c#L920">920</a>                 if (<a href="ident?i=likely">likely</a>(<a href="ident?i=up">up</a>-&gt;<a href="ident?i=pending">pending</a>)) {
<a name="L921" href="source/net/ipv4/udp.c#L921">921</a>                         if (<a href="ident?i=unlikely">unlikely</a>(<a href="ident?i=up">up</a>-&gt;<a href="ident?i=pending">pending</a> != <a href="ident?i=AF_INET">AF_INET</a>)) {
<a name="L922" href="source/net/ipv4/udp.c#L922">922</a>                                 <a href="ident?i=release_sock">release_sock</a>(sk);
<a name="L923" href="source/net/ipv4/udp.c#L923">923</a>                                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L924" href="source/net/ipv4/udp.c#L924">924</a>                         }
<a name="L925" href="source/net/ipv4/udp.c#L925">925</a>                         goto do_append_data;
<a name="L926" href="source/net/ipv4/udp.c#L926">926</a>                 }
<a name="L927" href="source/net/ipv4/udp.c#L927">927</a>                 <a href="ident?i=release_sock">release_sock</a>(sk);
<a name="L928" href="source/net/ipv4/udp.c#L928">928</a>         }
<a name="L929" href="source/net/ipv4/udp.c#L929">929</a>         ulen += sizeof(struct <a href="ident?i=udphdr">udphdr</a>);
<a name="L930" href="source/net/ipv4/udp.c#L930">930</a> 
<a name="L931" href="source/net/ipv4/udp.c#L931">931</a>         <b><i>/*</i></b>
<a name="L932" href="source/net/ipv4/udp.c#L932">932</a> <b><i>         *      Get and verify the address.</i></b>
<a name="L933" href="source/net/ipv4/udp.c#L933">933</a> <b><i>         */</i></b>
<a name="L934" href="source/net/ipv4/udp.c#L934">934</a>         if (<a href="ident?i=msg">msg</a>-&gt;msg_name) {
<a name="L935" href="source/net/ipv4/udp.c#L935">935</a>                 <a href="ident?i=DECLARE_SOCKADDR">DECLARE_SOCKADDR</a>(struct <a href="ident?i=sockaddr_in">sockaddr_in</a> *, usin, <a href="ident?i=msg">msg</a>-&gt;msg_name);
<a name="L936" href="source/net/ipv4/udp.c#L936">936</a>                 if (<a href="ident?i=msg">msg</a>-&gt;msg_namelen &lt; sizeof(*usin))
<a name="L937" href="source/net/ipv4/udp.c#L937">937</a>                         return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L938" href="source/net/ipv4/udp.c#L938">938</a>                 if (usin-&gt;sin_family != <a href="ident?i=AF_INET">AF_INET</a>) {
<a name="L939" href="source/net/ipv4/udp.c#L939">939</a>                         if (usin-&gt;sin_family != <a href="ident?i=AF_UNSPEC">AF_UNSPEC</a>)
<a name="L940" href="source/net/ipv4/udp.c#L940">940</a>                                 return -<a href="ident?i=EAFNOSUPPORT">EAFNOSUPPORT</a>;
<a name="L941" href="source/net/ipv4/udp.c#L941">941</a>                 }
<a name="L942" href="source/net/ipv4/udp.c#L942">942</a> 
<a name="L943" href="source/net/ipv4/udp.c#L943">943</a>                 <a href="ident?i=daddr">daddr</a> = usin-&gt;sin_addr.s_addr;
<a name="L944" href="source/net/ipv4/udp.c#L944">944</a>                 dport = usin-&gt;sin_port;
<a name="L945" href="source/net/ipv4/udp.c#L945">945</a>                 if (dport == 0)
<a name="L946" href="source/net/ipv4/udp.c#L946">946</a>                         return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L947" href="source/net/ipv4/udp.c#L947">947</a>         } else {
<a name="L948" href="source/net/ipv4/udp.c#L948">948</a>                 if (sk-&gt;<a href="ident?i=sk_state">sk_state</a> != TCP_ESTABLISHED)
<a name="L949" href="source/net/ipv4/udp.c#L949">949</a>                         return -<a href="ident?i=EDESTADDRREQ">EDESTADDRREQ</a>;
<a name="L950" href="source/net/ipv4/udp.c#L950">950</a>                 <a href="ident?i=daddr">daddr</a> = inet-&gt;<a href="ident?i=inet_daddr">inet_daddr</a>;
<a name="L951" href="source/net/ipv4/udp.c#L951">951</a>                 dport = inet-&gt;<a href="ident?i=inet_dport">inet_dport</a>;
<a name="L952" href="source/net/ipv4/udp.c#L952">952</a>                 <b><i>/* Open fast path for connected socket.</i></b>
<a name="L953" href="source/net/ipv4/udp.c#L953">953</a> <b><i>                   Route will not be used, if at least one option is set.</i></b>
<a name="L954" href="source/net/ipv4/udp.c#L954">954</a> <b><i>                 */</i></b>
<a name="L955" href="source/net/ipv4/udp.c#L955">955</a>                 <a href="ident?i=connected">connected</a> = 1;
<a name="L956" href="source/net/ipv4/udp.c#L956">956</a>         }
<a name="L957" href="source/net/ipv4/udp.c#L957">957</a>         ipc.<a href="ident?i=addr">addr</a> = inet-&gt;inet_saddr;
<a name="L958" href="source/net/ipv4/udp.c#L958">958</a> 
<a name="L959" href="source/net/ipv4/udp.c#L959">959</a>         ipc.oif = sk-&gt;<a href="ident?i=sk_bound_dev_if">sk_bound_dev_if</a>;
<a name="L960" href="source/net/ipv4/udp.c#L960">960</a> 
<a name="L961" href="source/net/ipv4/udp.c#L961">961</a>         <a href="ident?i=sock_tx_timestamp">sock_tx_timestamp</a>(sk, &amp;ipc.tx_flags);
<a name="L962" href="source/net/ipv4/udp.c#L962">962</a> 
<a name="L963" href="source/net/ipv4/udp.c#L963">963</a>         if (<a href="ident?i=msg">msg</a>-&gt;msg_controllen) {
<a name="L964" href="source/net/ipv4/udp.c#L964">964</a>                 <a href="ident?i=err">err</a> = <a href="ident?i=ip_cmsg_send">ip_cmsg_send</a>(<a href="ident?i=sock_net">sock_net</a>(sk), <a href="ident?i=msg">msg</a>, &amp;ipc,
<a name="L965" href="source/net/ipv4/udp.c#L965">965</a>                                    sk-&gt;<a href="ident?i=sk_family">sk_family</a> == <a href="ident?i=AF_INET6">AF_INET6</a>);
<a name="L966" href="source/net/ipv4/udp.c#L966">966</a>                 if (<a href="ident?i=err">err</a>)
<a name="L967" href="source/net/ipv4/udp.c#L967">967</a>                         return <a href="ident?i=err">err</a>;
<a name="L968" href="source/net/ipv4/udp.c#L968">968</a>                 if (ipc.opt)
<a name="L969" href="source/net/ipv4/udp.c#L969">969</a>                         <a href="ident?i=free">free</a> = 1;
<a name="L970" href="source/net/ipv4/udp.c#L970">970</a>                 <a href="ident?i=connected">connected</a> = 0;
<a name="L971" href="source/net/ipv4/udp.c#L971">971</a>         }
<a name="L972" href="source/net/ipv4/udp.c#L972">972</a>         if (!ipc.opt) {
<a name="L973" href="source/net/ipv4/udp.c#L973">973</a>                 struct <a href="ident?i=ip_options_rcu">ip_options_rcu</a> *inet_opt;
<a name="L974" href="source/net/ipv4/udp.c#L974">974</a> 
<a name="L975" href="source/net/ipv4/udp.c#L975">975</a>                 <a href="ident?i=rcu_read_lock">rcu_read_lock</a>();
<a name="L976" href="source/net/ipv4/udp.c#L976">976</a>                 inet_opt = <a href="ident?i=rcu_dereference">rcu_dereference</a>(inet-&gt;inet_opt);
<a name="L977" href="source/net/ipv4/udp.c#L977">977</a>                 if (inet_opt) {
<a name="L978" href="source/net/ipv4/udp.c#L978">978</a>                         <a href="ident?i=memcpy">memcpy</a>(&amp;opt_copy, inet_opt,
<a name="L979" href="source/net/ipv4/udp.c#L979">979</a>                                sizeof(*inet_opt) + inet_opt-&gt;opt.<a href="ident?i=optlen">optlen</a>);
<a name="L980" href="source/net/ipv4/udp.c#L980">980</a>                         ipc.opt = &amp;opt_copy.opt;
<a name="L981" href="source/net/ipv4/udp.c#L981">981</a>                 }
<a name="L982" href="source/net/ipv4/udp.c#L982">982</a>                 <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L983" href="source/net/ipv4/udp.c#L983">983</a>         }
<a name="L984" href="source/net/ipv4/udp.c#L984">984</a> 
<a name="L985" href="source/net/ipv4/udp.c#L985">985</a>         <a href="ident?i=saddr">saddr</a> = ipc.<a href="ident?i=addr">addr</a>;
<a name="L986" href="source/net/ipv4/udp.c#L986">986</a>         ipc.<a href="ident?i=addr">addr</a> = faddr = <a href="ident?i=daddr">daddr</a>;
<a name="L987" href="source/net/ipv4/udp.c#L987">987</a> 
<a name="L988" href="source/net/ipv4/udp.c#L988">988</a>         if (ipc.opt &amp;&amp; ipc.opt-&gt;opt.<a href="ident?i=srr">srr</a>) {
<a name="L989" href="source/net/ipv4/udp.c#L989">989</a>                 if (!<a href="ident?i=daddr">daddr</a>)
<a name="L990" href="source/net/ipv4/udp.c#L990">990</a>                         return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L991" href="source/net/ipv4/udp.c#L991">991</a>                 faddr = ipc.opt-&gt;opt.faddr;
<a name="L992" href="source/net/ipv4/udp.c#L992">992</a>                 <a href="ident?i=connected">connected</a> = 0;
<a name="L993" href="source/net/ipv4/udp.c#L993">993</a>         }
<a name="L994" href="source/net/ipv4/udp.c#L994">994</a>         tos = <a href="ident?i=get_rttos">get_rttos</a>(&amp;ipc, inet);
<a name="L995" href="source/net/ipv4/udp.c#L995">995</a>         if (<a href="ident?i=sock_flag">sock_flag</a>(sk, SOCK_LOCALROUTE) ||
<a name="L996" href="source/net/ipv4/udp.c#L996">996</a>             (<a href="ident?i=msg">msg</a>-&gt;msg_flags &amp; <a href="ident?i=MSG_DONTROUTE">MSG_DONTROUTE</a>) ||
<a name="L997" href="source/net/ipv4/udp.c#L997">997</a>             (ipc.opt &amp;&amp; ipc.opt-&gt;opt.is_strictroute)) {
<a name="L998" href="source/net/ipv4/udp.c#L998">998</a>                 tos |= <a href="ident?i=RTO_ONLINK">RTO_ONLINK</a>;
<a name="L999" href="source/net/ipv4/udp.c#L999">999</a>                 <a href="ident?i=connected">connected</a> = 0;
<a name="L1000" href="source/net/ipv4/udp.c#L1000">1000</a>         }
<a name="L1001" href="source/net/ipv4/udp.c#L1001">1001</a> 
<a name="L1002" href="source/net/ipv4/udp.c#L1002">1002</a>         if (<a href="ident?i=ipv4_is_multicast">ipv4_is_multicast</a>(<a href="ident?i=daddr">daddr</a>)) {
<a name="L1003" href="source/net/ipv4/udp.c#L1003">1003</a>                 if (!ipc.oif)
<a name="L1004" href="source/net/ipv4/udp.c#L1004">1004</a>                         ipc.oif = inet-&gt;mc_index;
<a name="L1005" href="source/net/ipv4/udp.c#L1005">1005</a>                 if (!<a href="ident?i=saddr">saddr</a>)
<a name="L1006" href="source/net/ipv4/udp.c#L1006">1006</a>                         <a href="ident?i=saddr">saddr</a> = inet-&gt;mc_addr;
<a name="L1007" href="source/net/ipv4/udp.c#L1007">1007</a>                 <a href="ident?i=connected">connected</a> = 0;
<a name="L1008" href="source/net/ipv4/udp.c#L1008">1008</a>         } else if (!ipc.oif)
<a name="L1009" href="source/net/ipv4/udp.c#L1009">1009</a>                 ipc.oif = inet-&gt;uc_index;
<a name="L1010" href="source/net/ipv4/udp.c#L1010">1010</a> 
<a name="L1011" href="source/net/ipv4/udp.c#L1011">1011</a>         if (<a href="ident?i=connected">connected</a>)
<a name="L1012" href="source/net/ipv4/udp.c#L1012">1012</a>                 <a href="ident?i=rt">rt</a> = (struct <a href="ident?i=rtable">rtable</a> *)<a href="ident?i=sk_dst_check">sk_dst_check</a>(sk, 0);
<a name="L1013" href="source/net/ipv4/udp.c#L1013">1013</a> 
<a name="L1014" href="source/net/ipv4/udp.c#L1014">1014</a>         if (!<a href="ident?i=rt">rt</a>) {
<a name="L1015" href="source/net/ipv4/udp.c#L1015">1015</a>                 struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=sock_net">sock_net</a>(sk);
<a name="L1016" href="source/net/ipv4/udp.c#L1016">1016</a> 
<a name="L1017" href="source/net/ipv4/udp.c#L1017">1017</a>                 fl4 = &amp;fl4_stack;
<a name="L1018" href="source/net/ipv4/udp.c#L1018">1018</a>                 <a href="ident?i=flowi4_init_output">flowi4_init_output</a>(fl4, ipc.oif, sk-&gt;sk_mark, tos,
<a name="L1019" href="source/net/ipv4/udp.c#L1019">1019</a>                                    RT_SCOPE_UNIVERSE, sk-&gt;sk_protocol,
<a name="L1020" href="source/net/ipv4/udp.c#L1020">1020</a>                                    <a href="ident?i=inet_sk_flowi_flags">inet_sk_flowi_flags</a>(sk),
<a name="L1021" href="source/net/ipv4/udp.c#L1021">1021</a>                                    faddr, <a href="ident?i=saddr">saddr</a>, dport, inet-&gt;inet_sport);
<a name="L1022" href="source/net/ipv4/udp.c#L1022">1022</a> 
<a name="L1023" href="source/net/ipv4/udp.c#L1023">1023</a>                 <a href="ident?i=security_sk_classify_flow">security_sk_classify_flow</a>(sk, <a href="ident?i=flowi4_to_flowi">flowi4_to_flowi</a>(fl4));
<a name="L1024" href="source/net/ipv4/udp.c#L1024">1024</a>                 <a href="ident?i=rt">rt</a> = <a href="ident?i=ip_route_output_flow">ip_route_output_flow</a>(<a href="ident?i=net">net</a>, fl4, sk);
<a name="L1025" href="source/net/ipv4/udp.c#L1025">1025</a>                 if (<a href="ident?i=IS_ERR">IS_ERR</a>(<a href="ident?i=rt">rt</a>)) {
<a name="L1026" href="source/net/ipv4/udp.c#L1026">1026</a>                         <a href="ident?i=err">err</a> = <a href="ident?i=PTR_ERR">PTR_ERR</a>(<a href="ident?i=rt">rt</a>);
<a name="L1027" href="source/net/ipv4/udp.c#L1027">1027</a>                         <a href="ident?i=rt">rt</a> = <a href="ident?i=NULL">NULL</a>;
<a name="L1028" href="source/net/ipv4/udp.c#L1028">1028</a>                         if (<a href="ident?i=err">err</a> == -<a href="ident?i=ENETUNREACH">ENETUNREACH</a>)
<a name="L1029" href="source/net/ipv4/udp.c#L1029">1029</a>                                 <a href="ident?i=IP_INC_STATS">IP_INC_STATS</a>(<a href="ident?i=net">net</a>, IPSTATS_MIB_OUTNOROUTES);
<a name="L1030" href="source/net/ipv4/udp.c#L1030">1030</a>                         goto <a href="ident?i=out">out</a>;
<a name="L1031" href="source/net/ipv4/udp.c#L1031">1031</a>                 }
<a name="L1032" href="source/net/ipv4/udp.c#L1032">1032</a> 
<a name="L1033" href="source/net/ipv4/udp.c#L1033">1033</a>                 <a href="ident?i=err">err</a> = -<a href="ident?i=EACCES">EACCES</a>;
<a name="L1034" href="source/net/ipv4/udp.c#L1034">1034</a>                 if ((<a href="ident?i=rt">rt</a>-&gt;rt_flags &amp; <a href="ident?i=RTCF_BROADCAST">RTCF_BROADCAST</a>) &amp;&amp;
<a name="L1035" href="source/net/ipv4/udp.c#L1035">1035</a>                     !<a href="ident?i=sock_flag">sock_flag</a>(sk, SOCK_BROADCAST))
<a name="L1036" href="source/net/ipv4/udp.c#L1036">1036</a>                         goto <a href="ident?i=out">out</a>;
<a name="L1037" href="source/net/ipv4/udp.c#L1037">1037</a>                 if (<a href="ident?i=connected">connected</a>)
<a name="L1038" href="source/net/ipv4/udp.c#L1038">1038</a>                         <a href="ident?i=sk_dst_set">sk_dst_set</a>(sk, <a href="ident?i=dst_clone">dst_clone</a>(&amp;<a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>));
<a name="L1039" href="source/net/ipv4/udp.c#L1039">1039</a>         }
<a name="L1040" href="source/net/ipv4/udp.c#L1040">1040</a> 
<a name="L1041" href="source/net/ipv4/udp.c#L1041">1041</a>         if (<a href="ident?i=msg">msg</a>-&gt;msg_flags&amp;<a href="ident?i=MSG_CONFIRM">MSG_CONFIRM</a>)
<a name="L1042" href="source/net/ipv4/udp.c#L1042">1042</a>                 goto do_confirm;
<a name="L1043" href="source/net/ipv4/udp.c#L1043">1043</a> back_from_confirm:
<a name="L1044" href="source/net/ipv4/udp.c#L1044">1044</a> 
<a name="L1045" href="source/net/ipv4/udp.c#L1045">1045</a>         <a href="ident?i=saddr">saddr</a> = fl4-&gt;<a href="ident?i=saddr">saddr</a>;
<a name="L1046" href="source/net/ipv4/udp.c#L1046">1046</a>         if (!ipc.<a href="ident?i=addr">addr</a>)
<a name="L1047" href="source/net/ipv4/udp.c#L1047">1047</a>                 <a href="ident?i=daddr">daddr</a> = ipc.<a href="ident?i=addr">addr</a> = fl4-&gt;<a href="ident?i=daddr">daddr</a>;
<a name="L1048" href="source/net/ipv4/udp.c#L1048">1048</a> 
<a name="L1049" href="source/net/ipv4/udp.c#L1049">1049</a>         <b><i>/* Lockless fast path for the non-corking case. */</i></b>
<a name="L1050" href="source/net/ipv4/udp.c#L1050">1050</a>         if (!corkreq) {
<a name="L1051" href="source/net/ipv4/udp.c#L1051">1051</a>                 <a href="ident?i=skb">skb</a> = <a href="ident?i=ip_make_skb">ip_make_skb</a>(sk, fl4, getfrag, <a href="ident?i=msg">msg</a>, ulen,
<a name="L1052" href="source/net/ipv4/udp.c#L1052">1052</a>                                   sizeof(struct <a href="ident?i=udphdr">udphdr</a>), &amp;ipc, &amp;<a href="ident?i=rt">rt</a>,
<a name="L1053" href="source/net/ipv4/udp.c#L1053">1053</a>                                   <a href="ident?i=msg">msg</a>-&gt;msg_flags);
<a name="L1054" href="source/net/ipv4/udp.c#L1054">1054</a>                 <a href="ident?i=err">err</a> = <a href="ident?i=PTR_ERR">PTR_ERR</a>(<a href="ident?i=skb">skb</a>);
<a name="L1055" href="source/net/ipv4/udp.c#L1055">1055</a>                 if (!<a href="ident?i=IS_ERR_OR_NULL">IS_ERR_OR_NULL</a>(<a href="ident?i=skb">skb</a>))
<a name="L1056" href="source/net/ipv4/udp.c#L1056">1056</a>                         <a href="ident?i=err">err</a> = <a href="ident?i=udp_send_skb">udp_send_skb</a>(<a href="ident?i=skb">skb</a>, fl4);
<a name="L1057" href="source/net/ipv4/udp.c#L1057">1057</a>                 goto <a href="ident?i=out">out</a>;
<a name="L1058" href="source/net/ipv4/udp.c#L1058">1058</a>         }
<a name="L1059" href="source/net/ipv4/udp.c#L1059">1059</a> 
<a name="L1060" href="source/net/ipv4/udp.c#L1060">1060</a>         <a href="ident?i=lock_sock">lock_sock</a>(sk);
<a name="L1061" href="source/net/ipv4/udp.c#L1061">1061</a>         if (<a href="ident?i=unlikely">unlikely</a>(<a href="ident?i=up">up</a>-&gt;<a href="ident?i=pending">pending</a>)) {
<a name="L1062" href="source/net/ipv4/udp.c#L1062">1062</a>                 <b><i>/* The socket is already corked while preparing it. */</i></b>
<a name="L1063" href="source/net/ipv4/udp.c#L1063">1063</a>                 <b><i>/* ... which is an evident application bug. --ANK */</i></b>
<a name="L1064" href="source/net/ipv4/udp.c#L1064">1064</a>                 <a href="ident?i=release_sock">release_sock</a>(sk);
<a name="L1065" href="source/net/ipv4/udp.c#L1065">1065</a> 
<a name="L1066" href="source/net/ipv4/udp.c#L1066">1066</a>                 <a href="ident?i=net_dbg_ratelimited">net_dbg_ratelimited</a>(<i>"cork app bug 2\n"</i>);
<a name="L1067" href="source/net/ipv4/udp.c#L1067">1067</a>                 <a href="ident?i=err">err</a> = -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L1068" href="source/net/ipv4/udp.c#L1068">1068</a>                 goto <a href="ident?i=out">out</a>;
<a name="L1069" href="source/net/ipv4/udp.c#L1069">1069</a>         }
<a name="L1070" href="source/net/ipv4/udp.c#L1070">1070</a>         <b><i>/*</i></b>
<a name="L1071" href="source/net/ipv4/udp.c#L1071">1071</a> <b><i>         *      Now cork the socket to pend data.</i></b>
<a name="L1072" href="source/net/ipv4/udp.c#L1072">1072</a> <b><i>         */</i></b>
<a name="L1073" href="source/net/ipv4/udp.c#L1073">1073</a>         fl4 = &amp;inet-&gt;cork.fl.u.ip4;
<a name="L1074" href="source/net/ipv4/udp.c#L1074">1074</a>         fl4-&gt;<a href="ident?i=daddr">daddr</a> = <a href="ident?i=daddr">daddr</a>;
<a name="L1075" href="source/net/ipv4/udp.c#L1075">1075</a>         fl4-&gt;<a href="ident?i=saddr">saddr</a> = <a href="ident?i=saddr">saddr</a>;
<a name="L1076" href="source/net/ipv4/udp.c#L1076">1076</a>         fl4-&gt;<a href="ident?i=fl4_dport">fl4_dport</a> = dport;
<a name="L1077" href="source/net/ipv4/udp.c#L1077">1077</a>         fl4-&gt;<a href="ident?i=fl4_sport">fl4_sport</a> = inet-&gt;inet_sport;
<a name="L1078" href="source/net/ipv4/udp.c#L1078">1078</a>         <a href="ident?i=up">up</a>-&gt;<a href="ident?i=pending">pending</a> = <a href="ident?i=AF_INET">AF_INET</a>;
<a name="L1079" href="source/net/ipv4/udp.c#L1079">1079</a> 
<a name="L1080" href="source/net/ipv4/udp.c#L1080">1080</a> do_append_data:
<a name="L1081" href="source/net/ipv4/udp.c#L1081">1081</a>         <a href="ident?i=up">up</a>-&gt;<a href="ident?i=len">len</a> += ulen;
<a name="L1082" href="source/net/ipv4/udp.c#L1082">1082</a>         <a href="ident?i=err">err</a> = <a href="ident?i=ip_append_data">ip_append_data</a>(sk, fl4, getfrag, <a href="ident?i=msg">msg</a>, ulen,
<a name="L1083" href="source/net/ipv4/udp.c#L1083">1083</a>                              sizeof(struct <a href="ident?i=udphdr">udphdr</a>), &amp;ipc, &amp;<a href="ident?i=rt">rt</a>,
<a name="L1084" href="source/net/ipv4/udp.c#L1084">1084</a>                              corkreq ? <a href="ident?i=msg">msg</a>-&gt;msg_flags|<a href="ident?i=MSG_MORE">MSG_MORE</a> : <a href="ident?i=msg">msg</a>-&gt;msg_flags);
<a name="L1085" href="source/net/ipv4/udp.c#L1085">1085</a>         if (<a href="ident?i=err">err</a>)
<a name="L1086" href="source/net/ipv4/udp.c#L1086">1086</a>                 <a href="ident?i=udp_flush_pending_frames">udp_flush_pending_frames</a>(sk);
<a name="L1087" href="source/net/ipv4/udp.c#L1087">1087</a>         else if (!corkreq)
<a name="L1088" href="source/net/ipv4/udp.c#L1088">1088</a>                 <a href="ident?i=err">err</a> = <a href="ident?i=udp_push_pending_frames">udp_push_pending_frames</a>(sk);
<a name="L1089" href="source/net/ipv4/udp.c#L1089">1089</a>         else if (<a href="ident?i=unlikely">unlikely</a>(<a href="ident?i=skb_queue_empty">skb_queue_empty</a>(&amp;sk-&gt;sk_write_queue)))
<a name="L1090" href="source/net/ipv4/udp.c#L1090">1090</a>                 <a href="ident?i=up">up</a>-&gt;<a href="ident?i=pending">pending</a> = 0;
<a name="L1091" href="source/net/ipv4/udp.c#L1091">1091</a>         <a href="ident?i=release_sock">release_sock</a>(sk);
<a name="L1092" href="source/net/ipv4/udp.c#L1092">1092</a> 
<a name="L1093" href="source/net/ipv4/udp.c#L1093">1093</a> <a href="ident?i=out">out</a>:
<a name="L1094" href="source/net/ipv4/udp.c#L1094">1094</a>         <a href="ident?i=ip_rt_put">ip_rt_put</a>(<a href="ident?i=rt">rt</a>);
<a name="L1095" href="source/net/ipv4/udp.c#L1095">1095</a>         if (<a href="ident?i=free">free</a>)
<a name="L1096" href="source/net/ipv4/udp.c#L1096">1096</a>                 <a href="ident?i=kfree">kfree</a>(ipc.opt);
<a name="L1097" href="source/net/ipv4/udp.c#L1097">1097</a>         if (!<a href="ident?i=err">err</a>)
<a name="L1098" href="source/net/ipv4/udp.c#L1098">1098</a>                 return <a href="ident?i=len">len</a>;
<a name="L1099" href="source/net/ipv4/udp.c#L1099">1099</a>         <b><i>/*</i></b>
<a name="L1100" href="source/net/ipv4/udp.c#L1100">1100</a> <b><i>         * ENOBUFS = no kernel mem, SOCK_NOSPACE = no sndbuf space.  Reporting</i></b>
<a name="L1101" href="source/net/ipv4/udp.c#L1101">1101</a> <b><i>         * ENOBUFS might not be good (it's not tunable per se), but otherwise</i></b>
<a name="L1102" href="source/net/ipv4/udp.c#L1102">1102</a> <b><i>         * we don't have a good statistic (IpOutDiscards but it can be too many</i></b>
<a name="L1103" href="source/net/ipv4/udp.c#L1103">1103</a> <b><i>         * things).  We could add another new stat but at least for now that</i></b>
<a name="L1104" href="source/net/ipv4/udp.c#L1104">1104</a> <b><i>         * seems like overkill.</i></b>
<a name="L1105" href="source/net/ipv4/udp.c#L1105">1105</a> <b><i>         */</i></b>
<a name="L1106" href="source/net/ipv4/udp.c#L1106">1106</a>         if (<a href="ident?i=err">err</a> == -<a href="ident?i=ENOBUFS">ENOBUFS</a> || <a href="ident?i=test_bit">test_bit</a>(<a href="ident?i=SOCK_NOSPACE">SOCK_NOSPACE</a>, &amp;sk-&gt;sk_socket-&gt;<a href="ident?i=flags">flags</a>)) {
<a name="L1107" href="source/net/ipv4/udp.c#L1107">1107</a>                 <a href="ident?i=UDP_INC_STATS_USER">UDP_INC_STATS_USER</a>(<a href="ident?i=sock_net">sock_net</a>(sk),
<a name="L1108" href="source/net/ipv4/udp.c#L1108">1108</a>                                 UDP_MIB_SNDBUFERRORS, is_udplite);
<a name="L1109" href="source/net/ipv4/udp.c#L1109">1109</a>         }
<a name="L1110" href="source/net/ipv4/udp.c#L1110">1110</a>         return <a href="ident?i=err">err</a>;
<a name="L1111" href="source/net/ipv4/udp.c#L1111">1111</a> 
<a name="L1112" href="source/net/ipv4/udp.c#L1112">1112</a> do_confirm:
<a name="L1113" href="source/net/ipv4/udp.c#L1113">1113</a>         <a href="ident?i=dst_confirm">dst_confirm</a>(&amp;<a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>);
<a name="L1114" href="source/net/ipv4/udp.c#L1114">1114</a>         if (!(<a href="ident?i=msg">msg</a>-&gt;msg_flags&amp;<a href="ident?i=MSG_PROBE">MSG_PROBE</a>) || <a href="ident?i=len">len</a>)
<a name="L1115" href="source/net/ipv4/udp.c#L1115">1115</a>                 goto back_from_confirm;
<a name="L1116" href="source/net/ipv4/udp.c#L1116">1116</a>         <a href="ident?i=err">err</a> = 0;
<a name="L1117" href="source/net/ipv4/udp.c#L1117">1117</a>         goto <a href="ident?i=out">out</a>;
<a name="L1118" href="source/net/ipv4/udp.c#L1118">1118</a> }
<a name="L1119" href="source/net/ipv4/udp.c#L1119">1119</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=udp_sendmsg">udp_sendmsg</a>);
<a name="L1120" href="source/net/ipv4/udp.c#L1120">1120</a> 
<a name="L1121" href="source/net/ipv4/udp.c#L1121">1121</a> int <a href="ident?i=udp_sendpage">udp_sendpage</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=page">page</a> *<a href="ident?i=page">page</a>, int <a href="ident?i=offset">offset</a>,
<a name="L1122" href="source/net/ipv4/udp.c#L1122">1122</a>                  <a href="ident?i=size_t">size_t</a> <a href="ident?i=size">size</a>, int <a href="ident?i=flags">flags</a>)
<a name="L1123" href="source/net/ipv4/udp.c#L1123">1123</a> {
<a name="L1124" href="source/net/ipv4/udp.c#L1124">1124</a>         struct <a href="ident?i=inet_sock">inet_sock</a> *inet = <a href="ident?i=inet_sk">inet_sk</a>(sk);
<a name="L1125" href="source/net/ipv4/udp.c#L1125">1125</a>         struct <a href="ident?i=udp_sock">udp_sock</a> *<a href="ident?i=up">up</a> = <a href="ident?i=udp_sk">udp_sk</a>(sk);
<a name="L1126" href="source/net/ipv4/udp.c#L1126">1126</a>         int <a href="ident?i=ret">ret</a>;
<a name="L1127" href="source/net/ipv4/udp.c#L1127">1127</a> 
<a name="L1128" href="source/net/ipv4/udp.c#L1128">1128</a>         if (<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=MSG_SENDPAGE_NOTLAST">MSG_SENDPAGE_NOTLAST</a>)
<a name="L1129" href="source/net/ipv4/udp.c#L1129">1129</a>                 <a href="ident?i=flags">flags</a> |= <a href="ident?i=MSG_MORE">MSG_MORE</a>;
<a name="L1130" href="source/net/ipv4/udp.c#L1130">1130</a> 
<a name="L1131" href="source/net/ipv4/udp.c#L1131">1131</a>         if (!<a href="ident?i=up">up</a>-&gt;<a href="ident?i=pending">pending</a>) {
<a name="L1132" href="source/net/ipv4/udp.c#L1132">1132</a>                 struct <a href="ident?i=msghdr">msghdr</a> <a href="ident?i=msg">msg</a> = {   .msg_flags = <a href="ident?i=flags">flags</a>|<a href="ident?i=MSG_MORE">MSG_MORE</a> };
<a name="L1133" href="source/net/ipv4/udp.c#L1133">1133</a> 
<a name="L1134" href="source/net/ipv4/udp.c#L1134">1134</a>                 <b><i>/* Call udp_sendmsg to specify destination address which</i></b>
<a name="L1135" href="source/net/ipv4/udp.c#L1135">1135</a> <b><i>                 * sendpage interface can't pass.</i></b>
<a name="L1136" href="source/net/ipv4/udp.c#L1136">1136</a> <b><i>                 * This will succeed only when the socket is connected.</i></b>
<a name="L1137" href="source/net/ipv4/udp.c#L1137">1137</a> <b><i>                 */</i></b>
<a name="L1138" href="source/net/ipv4/udp.c#L1138">1138</a>                 <a href="ident?i=ret">ret</a> = <a href="ident?i=udp_sendmsg">udp_sendmsg</a>(sk, &amp;<a href="ident?i=msg">msg</a>, 0);
<a name="L1139" href="source/net/ipv4/udp.c#L1139">1139</a>                 if (<a href="ident?i=ret">ret</a> &lt; 0)
<a name="L1140" href="source/net/ipv4/udp.c#L1140">1140</a>                         return <a href="ident?i=ret">ret</a>;
<a name="L1141" href="source/net/ipv4/udp.c#L1141">1141</a>         }
<a name="L1142" href="source/net/ipv4/udp.c#L1142">1142</a> 
<a name="L1143" href="source/net/ipv4/udp.c#L1143">1143</a>         <a href="ident?i=lock_sock">lock_sock</a>(sk);
<a name="L1144" href="source/net/ipv4/udp.c#L1144">1144</a> 
<a name="L1145" href="source/net/ipv4/udp.c#L1145">1145</a>         if (<a href="ident?i=unlikely">unlikely</a>(!<a href="ident?i=up">up</a>-&gt;<a href="ident?i=pending">pending</a>)) {
<a name="L1146" href="source/net/ipv4/udp.c#L1146">1146</a>                 <a href="ident?i=release_sock">release_sock</a>(sk);
<a name="L1147" href="source/net/ipv4/udp.c#L1147">1147</a> 
<a name="L1148" href="source/net/ipv4/udp.c#L1148">1148</a>                 <a href="ident?i=net_dbg_ratelimited">net_dbg_ratelimited</a>(<i>"udp cork app bug 3\n"</i>);
<a name="L1149" href="source/net/ipv4/udp.c#L1149">1149</a>                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L1150" href="source/net/ipv4/udp.c#L1150">1150</a>         }
<a name="L1151" href="source/net/ipv4/udp.c#L1151">1151</a> 
<a name="L1152" href="source/net/ipv4/udp.c#L1152">1152</a>         <a href="ident?i=ret">ret</a> = <a href="ident?i=ip_append_page">ip_append_page</a>(sk, &amp;inet-&gt;cork.fl.u.ip4,
<a name="L1153" href="source/net/ipv4/udp.c#L1153">1153</a>                              <a href="ident?i=page">page</a>, <a href="ident?i=offset">offset</a>, <a href="ident?i=size">size</a>, <a href="ident?i=flags">flags</a>);
<a name="L1154" href="source/net/ipv4/udp.c#L1154">1154</a>         if (<a href="ident?i=ret">ret</a> == -<a href="ident?i=EOPNOTSUPP">EOPNOTSUPP</a>) {
<a name="L1155" href="source/net/ipv4/udp.c#L1155">1155</a>                 <a href="ident?i=release_sock">release_sock</a>(sk);
<a name="L1156" href="source/net/ipv4/udp.c#L1156">1156</a>                 return <a href="ident?i=sock_no_sendpage">sock_no_sendpage</a>(sk-&gt;sk_socket, <a href="ident?i=page">page</a>, <a href="ident?i=offset">offset</a>,
<a name="L1157" href="source/net/ipv4/udp.c#L1157">1157</a>                                         <a href="ident?i=size">size</a>, <a href="ident?i=flags">flags</a>);
<a name="L1158" href="source/net/ipv4/udp.c#L1158">1158</a>         }
<a name="L1159" href="source/net/ipv4/udp.c#L1159">1159</a>         if (<a href="ident?i=ret">ret</a> &lt; 0) {
<a name="L1160" href="source/net/ipv4/udp.c#L1160">1160</a>                 <a href="ident?i=udp_flush_pending_frames">udp_flush_pending_frames</a>(sk);
<a name="L1161" href="source/net/ipv4/udp.c#L1161">1161</a>                 goto <a href="ident?i=out">out</a>;
<a name="L1162" href="source/net/ipv4/udp.c#L1162">1162</a>         }
<a name="L1163" href="source/net/ipv4/udp.c#L1163">1163</a> 
<a name="L1164" href="source/net/ipv4/udp.c#L1164">1164</a>         <a href="ident?i=up">up</a>-&gt;<a href="ident?i=len">len</a> += <a href="ident?i=size">size</a>;
<a name="L1165" href="source/net/ipv4/udp.c#L1165">1165</a>         if (!(<a href="ident?i=up">up</a>-&gt;corkflag || (<a href="ident?i=flags">flags</a>&amp;<a href="ident?i=MSG_MORE">MSG_MORE</a>)))
<a name="L1166" href="source/net/ipv4/udp.c#L1166">1166</a>                 <a href="ident?i=ret">ret</a> = <a href="ident?i=udp_push_pending_frames">udp_push_pending_frames</a>(sk);
<a name="L1167" href="source/net/ipv4/udp.c#L1167">1167</a>         if (!<a href="ident?i=ret">ret</a>)
<a name="L1168" href="source/net/ipv4/udp.c#L1168">1168</a>                 <a href="ident?i=ret">ret</a> = <a href="ident?i=size">size</a>;
<a name="L1169" href="source/net/ipv4/udp.c#L1169">1169</a> <a href="ident?i=out">out</a>:
<a name="L1170" href="source/net/ipv4/udp.c#L1170">1170</a>         <a href="ident?i=release_sock">release_sock</a>(sk);
<a name="L1171" href="source/net/ipv4/udp.c#L1171">1171</a>         return <a href="ident?i=ret">ret</a>;
<a name="L1172" href="source/net/ipv4/udp.c#L1172">1172</a> }
<a name="L1173" href="source/net/ipv4/udp.c#L1173">1173</a> 
<a name="L1174" href="source/net/ipv4/udp.c#L1174">1174</a> <b><i>/**</i></b>
<a name="L1175" href="source/net/ipv4/udp.c#L1175">1175</a> <b><i> *      first_packet_length     - return length of first packet in receive queue</i></b>
<a name="L1176" href="source/net/ipv4/udp.c#L1176">1176</a> <b><i> *      @sk: socket</i></b>
<a name="L1177" href="source/net/ipv4/udp.c#L1177">1177</a> <b><i> *</i></b>
<a name="L1178" href="source/net/ipv4/udp.c#L1178">1178</a> <b><i> *      Drops all bad checksum frames, until a valid one is found.</i></b>
<a name="L1179" href="source/net/ipv4/udp.c#L1179">1179</a> <b><i> *      Returns the length of found skb, or 0 if none is found.</i></b>
<a name="L1180" href="source/net/ipv4/udp.c#L1180">1180</a> <b><i> */</i></b>
<a name="L1181" href="source/net/ipv4/udp.c#L1181">1181</a> static unsigned int <a href="ident?i=first_packet_length">first_packet_length</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L1182" href="source/net/ipv4/udp.c#L1182">1182</a> {
<a name="L1183" href="source/net/ipv4/udp.c#L1183">1183</a>         struct <a href="ident?i=sk_buff_head">sk_buff_head</a> list_kill, *rcvq = &amp;sk-&gt;sk_receive_queue;
<a name="L1184" href="source/net/ipv4/udp.c#L1184">1184</a>         struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>;
<a name="L1185" href="source/net/ipv4/udp.c#L1185">1185</a>         unsigned int <a href="ident?i=res">res</a>;
<a name="L1186" href="source/net/ipv4/udp.c#L1186">1186</a> 
<a name="L1187" href="source/net/ipv4/udp.c#L1187">1187</a>         <a href="ident?i=__skb_queue_head_init">__skb_queue_head_init</a>(&amp;list_kill);
<a name="L1188" href="source/net/ipv4/udp.c#L1188">1188</a> 
<a name="L1189" href="source/net/ipv4/udp.c#L1189">1189</a>         <a href="ident?i=spin_lock_bh">spin_lock_bh</a>(&amp;rcvq-&gt;<a href="ident?i=lock">lock</a>);
<a name="L1190" href="source/net/ipv4/udp.c#L1190">1190</a>         while ((<a href="ident?i=skb">skb</a> = <a href="ident?i=skb_peek">skb_peek</a>(rcvq)) != <a href="ident?i=NULL">NULL</a> &amp;&amp;
<a name="L1191" href="source/net/ipv4/udp.c#L1191">1191</a>                 <a href="ident?i=udp_lib_checksum_complete">udp_lib_checksum_complete</a>(<a href="ident?i=skb">skb</a>)) {
<a name="L1192" href="source/net/ipv4/udp.c#L1192">1192</a>                 <a href="ident?i=UDP_INC_STATS_BH">UDP_INC_STATS_BH</a>(<a href="ident?i=sock_net">sock_net</a>(sk), UDP_MIB_CSUMERRORS,
<a name="L1193" href="source/net/ipv4/udp.c#L1193">1193</a>                                  <a href="ident?i=IS_UDPLITE">IS_UDPLITE</a>(sk));
<a name="L1194" href="source/net/ipv4/udp.c#L1194">1194</a>                 <a href="ident?i=UDP_INC_STATS_BH">UDP_INC_STATS_BH</a>(<a href="ident?i=sock_net">sock_net</a>(sk), UDP_MIB_INERRORS,
<a name="L1195" href="source/net/ipv4/udp.c#L1195">1195</a>                                  <a href="ident?i=IS_UDPLITE">IS_UDPLITE</a>(sk));
<a name="L1196" href="source/net/ipv4/udp.c#L1196">1196</a>                 <a href="ident?i=atomic_inc">atomic_inc</a>(&amp;sk-&gt;sk_drops);
<a name="L1197" href="source/net/ipv4/udp.c#L1197">1197</a>                 <a href="ident?i=__skb_unlink">__skb_unlink</a>(<a href="ident?i=skb">skb</a>, rcvq);
<a name="L1198" href="source/net/ipv4/udp.c#L1198">1198</a>                 <a href="ident?i=__skb_queue_tail">__skb_queue_tail</a>(&amp;list_kill, <a href="ident?i=skb">skb</a>);
<a name="L1199" href="source/net/ipv4/udp.c#L1199">1199</a>         }
<a name="L1200" href="source/net/ipv4/udp.c#L1200">1200</a>         <a href="ident?i=res">res</a> = <a href="ident?i=skb">skb</a> ? <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a> : 0;
<a name="L1201" href="source/net/ipv4/udp.c#L1201">1201</a>         <a href="ident?i=spin_unlock_bh">spin_unlock_bh</a>(&amp;rcvq-&gt;<a href="ident?i=lock">lock</a>);
<a name="L1202" href="source/net/ipv4/udp.c#L1202">1202</a> 
<a name="L1203" href="source/net/ipv4/udp.c#L1203">1203</a>         if (!<a href="ident?i=skb_queue_empty">skb_queue_empty</a>(&amp;list_kill)) {
<a name="L1204" href="source/net/ipv4/udp.c#L1204">1204</a>                 <a href="ident?i=bool">bool</a> <a href="ident?i=slow">slow</a> = <a href="ident?i=lock_sock_fast">lock_sock_fast</a>(sk);
<a name="L1205" href="source/net/ipv4/udp.c#L1205">1205</a> 
<a name="L1206" href="source/net/ipv4/udp.c#L1206">1206</a>                 <a href="ident?i=__skb_queue_purge">__skb_queue_purge</a>(&amp;list_kill);
<a name="L1207" href="source/net/ipv4/udp.c#L1207">1207</a>                 <a href="ident?i=sk_mem_reclaim_partial">sk_mem_reclaim_partial</a>(sk);
<a name="L1208" href="source/net/ipv4/udp.c#L1208">1208</a>                 <a href="ident?i=unlock_sock_fast">unlock_sock_fast</a>(sk, <a href="ident?i=slow">slow</a>);
<a name="L1209" href="source/net/ipv4/udp.c#L1209">1209</a>         }
<a name="L1210" href="source/net/ipv4/udp.c#L1210">1210</a>         return <a href="ident?i=res">res</a>;
<a name="L1211" href="source/net/ipv4/udp.c#L1211">1211</a> }
<a name="L1212" href="source/net/ipv4/udp.c#L1212">1212</a> 
<a name="L1213" href="source/net/ipv4/udp.c#L1213">1213</a> <b><i>/*</i></b>
<a name="L1214" href="source/net/ipv4/udp.c#L1214">1214</a> <b><i> *      IOCTL requests applicable to the UDP protocol</i></b>
<a name="L1215" href="source/net/ipv4/udp.c#L1215">1215</a> <b><i> */</i></b>
<a name="L1216" href="source/net/ipv4/udp.c#L1216">1216</a> 
<a name="L1217" href="source/net/ipv4/udp.c#L1217">1217</a> int <a href="ident?i=udp_ioctl">udp_ioctl</a>(struct <a href="ident?i=sock">sock</a> *sk, int <a href="ident?i=cmd">cmd</a>, unsigned long <a href="ident?i=arg">arg</a>)
<a name="L1218" href="source/net/ipv4/udp.c#L1218">1218</a> {
<a name="L1219" href="source/net/ipv4/udp.c#L1219">1219</a>         switch (<a href="ident?i=cmd">cmd</a>) {
<a name="L1220" href="source/net/ipv4/udp.c#L1220">1220</a>         case <a href="ident?i=SIOCOUTQ">SIOCOUTQ</a>:
<a name="L1221" href="source/net/ipv4/udp.c#L1221">1221</a>         {
<a name="L1222" href="source/net/ipv4/udp.c#L1222">1222</a>                 int amount = <a href="ident?i=sk_wmem_alloc_get">sk_wmem_alloc_get</a>(sk);
<a name="L1223" href="source/net/ipv4/udp.c#L1223">1223</a> 
<a name="L1224" href="source/net/ipv4/udp.c#L1224">1224</a>                 return <a href="ident?i=put_user">put_user</a>(amount, (int <a href="ident?i=__user">__user</a> *)<a href="ident?i=arg">arg</a>);
<a name="L1225" href="source/net/ipv4/udp.c#L1225">1225</a>         }
<a name="L1226" href="source/net/ipv4/udp.c#L1226">1226</a> 
<a name="L1227" href="source/net/ipv4/udp.c#L1227">1227</a>         case <a href="ident?i=SIOCINQ">SIOCINQ</a>:
<a name="L1228" href="source/net/ipv4/udp.c#L1228">1228</a>         {
<a name="L1229" href="source/net/ipv4/udp.c#L1229">1229</a>                 unsigned int amount = <a href="ident?i=first_packet_length">first_packet_length</a>(sk);
<a name="L1230" href="source/net/ipv4/udp.c#L1230">1230</a> 
<a name="L1231" href="source/net/ipv4/udp.c#L1231">1231</a>                 if (amount)
<a name="L1232" href="source/net/ipv4/udp.c#L1232">1232</a>                         <b><i>/*</i></b>
<a name="L1233" href="source/net/ipv4/udp.c#L1233">1233</a> <b><i>                         * We will only return the amount</i></b>
<a name="L1234" href="source/net/ipv4/udp.c#L1234">1234</a> <b><i>                         * of this packet since that is all</i></b>
<a name="L1235" href="source/net/ipv4/udp.c#L1235">1235</a> <b><i>                         * that will be read.</i></b>
<a name="L1236" href="source/net/ipv4/udp.c#L1236">1236</a> <b><i>                         */</i></b>
<a name="L1237" href="source/net/ipv4/udp.c#L1237">1237</a>                         amount -= sizeof(struct <a href="ident?i=udphdr">udphdr</a>);
<a name="L1238" href="source/net/ipv4/udp.c#L1238">1238</a> 
<a name="L1239" href="source/net/ipv4/udp.c#L1239">1239</a>                 return <a href="ident?i=put_user">put_user</a>(amount, (int <a href="ident?i=__user">__user</a> *)<a href="ident?i=arg">arg</a>);
<a name="L1240" href="source/net/ipv4/udp.c#L1240">1240</a>         }
<a name="L1241" href="source/net/ipv4/udp.c#L1241">1241</a> 
<a name="L1242" href="source/net/ipv4/udp.c#L1242">1242</a>         default:
<a name="L1243" href="source/net/ipv4/udp.c#L1243">1243</a>                 return -<a href="ident?i=ENOIOCTLCMD">ENOIOCTLCMD</a>;
<a name="L1244" href="source/net/ipv4/udp.c#L1244">1244</a>         }
<a name="L1245" href="source/net/ipv4/udp.c#L1245">1245</a> 
<a name="L1246" href="source/net/ipv4/udp.c#L1246">1246</a>         return 0;
<a name="L1247" href="source/net/ipv4/udp.c#L1247">1247</a> }
<a name="L1248" href="source/net/ipv4/udp.c#L1248">1248</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=udp_ioctl">udp_ioctl</a>);
<a name="L1249" href="source/net/ipv4/udp.c#L1249">1249</a> 
<a name="L1250" href="source/net/ipv4/udp.c#L1250">1250</a> <b><i>/*</i></b>
<a name="L1251" href="source/net/ipv4/udp.c#L1251">1251</a> <b><i> *      This should be easy, if there is something there we</i></b>
<a name="L1252" href="source/net/ipv4/udp.c#L1252">1252</a> <b><i> *      return it, otherwise we block.</i></b>
<a name="L1253" href="source/net/ipv4/udp.c#L1253">1253</a> <b><i> */</i></b>
<a name="L1254" href="source/net/ipv4/udp.c#L1254">1254</a> 
<a name="L1255" href="source/net/ipv4/udp.c#L1255">1255</a> int <a href="ident?i=udp_recvmsg">udp_recvmsg</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=msghdr">msghdr</a> *<a href="ident?i=msg">msg</a>, <a href="ident?i=size_t">size_t</a> <a href="ident?i=len">len</a>, int noblock,
<a name="L1256" href="source/net/ipv4/udp.c#L1256">1256</a>                 int <a href="ident?i=flags">flags</a>, int *addr_len)
<a name="L1257" href="source/net/ipv4/udp.c#L1257">1257</a> {
<a name="L1258" href="source/net/ipv4/udp.c#L1258">1258</a>         struct <a href="ident?i=inet_sock">inet_sock</a> *inet = <a href="ident?i=inet_sk">inet_sk</a>(sk);
<a name="L1259" href="source/net/ipv4/udp.c#L1259">1259</a>         <a href="ident?i=DECLARE_SOCKADDR">DECLARE_SOCKADDR</a>(struct <a href="ident?i=sockaddr_in">sockaddr_in</a> *, <a href="ident?i=sin">sin</a>, <a href="ident?i=msg">msg</a>-&gt;msg_name);
<a name="L1260" href="source/net/ipv4/udp.c#L1260">1260</a>         struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>;
<a name="L1261" href="source/net/ipv4/udp.c#L1261">1261</a>         unsigned int ulen, copied;
<a name="L1262" href="source/net/ipv4/udp.c#L1262">1262</a>         int peeked, <a href="ident?i=off">off</a> = 0;
<a name="L1263" href="source/net/ipv4/udp.c#L1263">1263</a>         int <a href="ident?i=err">err</a>;
<a name="L1264" href="source/net/ipv4/udp.c#L1264">1264</a>         int is_udplite = <a href="ident?i=IS_UDPLITE">IS_UDPLITE</a>(sk);
<a name="L1265" href="source/net/ipv4/udp.c#L1265">1265</a>         <a href="ident?i=bool">bool</a> <a href="ident?i=slow">slow</a>;
<a name="L1266" href="source/net/ipv4/udp.c#L1266">1266</a> 
<a name="L1267" href="source/net/ipv4/udp.c#L1267">1267</a>         if (<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=MSG_ERRQUEUE">MSG_ERRQUEUE</a>)
<a name="L1268" href="source/net/ipv4/udp.c#L1268">1268</a>                 return <a href="ident?i=ip_recv_error">ip_recv_error</a>(sk, <a href="ident?i=msg">msg</a>, <a href="ident?i=len">len</a>, addr_len);
<a name="L1269" href="source/net/ipv4/udp.c#L1269">1269</a> 
<a name="L1270" href="source/net/ipv4/udp.c#L1270">1270</a> try_again:
<a name="L1271" href="source/net/ipv4/udp.c#L1271">1271</a>         <a href="ident?i=skb">skb</a> = <a href="ident?i=__skb_recv_datagram">__skb_recv_datagram</a>(sk, <a href="ident?i=flags">flags</a> | (noblock ? <a href="ident?i=MSG_DONTWAIT">MSG_DONTWAIT</a> : 0),
<a name="L1272" href="source/net/ipv4/udp.c#L1272">1272</a>                                   &amp;peeked, &amp;<a href="ident?i=off">off</a>, &amp;<a href="ident?i=err">err</a>);
<a name="L1273" href="source/net/ipv4/udp.c#L1273">1273</a>         if (!<a href="ident?i=skb">skb</a>)
<a name="L1274" href="source/net/ipv4/udp.c#L1274">1274</a>                 goto <a href="ident?i=out">out</a>;
<a name="L1275" href="source/net/ipv4/udp.c#L1275">1275</a> 
<a name="L1276" href="source/net/ipv4/udp.c#L1276">1276</a>         ulen = <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a> - sizeof(struct <a href="ident?i=udphdr">udphdr</a>);
<a name="L1277" href="source/net/ipv4/udp.c#L1277">1277</a>         copied = <a href="ident?i=len">len</a>;
<a name="L1278" href="source/net/ipv4/udp.c#L1278">1278</a>         if (copied &gt; ulen)
<a name="L1279" href="source/net/ipv4/udp.c#L1279">1279</a>                 copied = ulen;
<a name="L1280" href="source/net/ipv4/udp.c#L1280">1280</a>         else if (copied &lt; ulen)
<a name="L1281" href="source/net/ipv4/udp.c#L1281">1281</a>                 <a href="ident?i=msg">msg</a>-&gt;msg_flags |= <a href="ident?i=MSG_TRUNC">MSG_TRUNC</a>;
<a name="L1282" href="source/net/ipv4/udp.c#L1282">1282</a> 
<a name="L1283" href="source/net/ipv4/udp.c#L1283">1283</a>         <b><i>/*</i></b>
<a name="L1284" href="source/net/ipv4/udp.c#L1284">1284</a> <b><i>         * If checksum is needed at all, try to do it while copying the</i></b>
<a name="L1285" href="source/net/ipv4/udp.c#L1285">1285</a> <b><i>         * data.  If the data is truncated, or if we only want a partial</i></b>
<a name="L1286" href="source/net/ipv4/udp.c#L1286">1286</a> <b><i>         * coverage checksum (UDP-Lite), do it before the copy.</i></b>
<a name="L1287" href="source/net/ipv4/udp.c#L1287">1287</a> <b><i>         */</i></b>
<a name="L1288" href="source/net/ipv4/udp.c#L1288">1288</a> 
<a name="L1289" href="source/net/ipv4/udp.c#L1289">1289</a>         if (copied &lt; ulen || <a href="ident?i=UDP_SKB_CB">UDP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;partial_cov) {
<a name="L1290" href="source/net/ipv4/udp.c#L1290">1290</a>                 if (<a href="ident?i=udp_lib_checksum_complete">udp_lib_checksum_complete</a>(<a href="ident?i=skb">skb</a>))
<a name="L1291" href="source/net/ipv4/udp.c#L1291">1291</a>                         goto csum_copy_err;
<a name="L1292" href="source/net/ipv4/udp.c#L1292">1292</a>         }
<a name="L1293" href="source/net/ipv4/udp.c#L1293">1293</a> 
<a name="L1294" href="source/net/ipv4/udp.c#L1294">1294</a>         if (<a href="ident?i=skb_csum_unnecessary">skb_csum_unnecessary</a>(<a href="ident?i=skb">skb</a>))
<a name="L1295" href="source/net/ipv4/udp.c#L1295">1295</a>                 <a href="ident?i=err">err</a> = <a href="ident?i=skb_copy_datagram_msg">skb_copy_datagram_msg</a>(<a href="ident?i=skb">skb</a>, sizeof(struct <a href="ident?i=udphdr">udphdr</a>),
<a name="L1296" href="source/net/ipv4/udp.c#L1296">1296</a>                                             <a href="ident?i=msg">msg</a>, copied);
<a name="L1297" href="source/net/ipv4/udp.c#L1297">1297</a>         else {
<a name="L1298" href="source/net/ipv4/udp.c#L1298">1298</a>                 <a href="ident?i=err">err</a> = <a href="ident?i=skb_copy_and_csum_datagram_msg">skb_copy_and_csum_datagram_msg</a>(<a href="ident?i=skb">skb</a>, sizeof(struct <a href="ident?i=udphdr">udphdr</a>),
<a name="L1299" href="source/net/ipv4/udp.c#L1299">1299</a>                                                      <a href="ident?i=msg">msg</a>);
<a name="L1300" href="source/net/ipv4/udp.c#L1300">1300</a> 
<a name="L1301" href="source/net/ipv4/udp.c#L1301">1301</a>                 if (<a href="ident?i=err">err</a> == -<a href="ident?i=EINVAL">EINVAL</a>)
<a name="L1302" href="source/net/ipv4/udp.c#L1302">1302</a>                         goto csum_copy_err;
<a name="L1303" href="source/net/ipv4/udp.c#L1303">1303</a>         }
<a name="L1304" href="source/net/ipv4/udp.c#L1304">1304</a> 
<a name="L1305" href="source/net/ipv4/udp.c#L1305">1305</a>         if (<a href="ident?i=unlikely">unlikely</a>(<a href="ident?i=err">err</a>)) {
<a name="L1306" href="source/net/ipv4/udp.c#L1306">1306</a>                 trace_kfree_skb(<a href="ident?i=skb">skb</a>, <a href="ident?i=udp_recvmsg">udp_recvmsg</a>);
<a name="L1307" href="source/net/ipv4/udp.c#L1307">1307</a>                 if (!peeked) {
<a name="L1308" href="source/net/ipv4/udp.c#L1308">1308</a>                         <a href="ident?i=atomic_inc">atomic_inc</a>(&amp;sk-&gt;sk_drops);
<a name="L1309" href="source/net/ipv4/udp.c#L1309">1309</a>                         <a href="ident?i=UDP_INC_STATS_USER">UDP_INC_STATS_USER</a>(<a href="ident?i=sock_net">sock_net</a>(sk),
<a name="L1310" href="source/net/ipv4/udp.c#L1310">1310</a>                                            UDP_MIB_INERRORS, is_udplite);
<a name="L1311" href="source/net/ipv4/udp.c#L1311">1311</a>                 }
<a name="L1312" href="source/net/ipv4/udp.c#L1312">1312</a>                 goto out_free;
<a name="L1313" href="source/net/ipv4/udp.c#L1313">1313</a>         }
<a name="L1314" href="source/net/ipv4/udp.c#L1314">1314</a> 
<a name="L1315" href="source/net/ipv4/udp.c#L1315">1315</a>         if (!peeked)
<a name="L1316" href="source/net/ipv4/udp.c#L1316">1316</a>                 <a href="ident?i=UDP_INC_STATS_USER">UDP_INC_STATS_USER</a>(<a href="ident?i=sock_net">sock_net</a>(sk),
<a name="L1317" href="source/net/ipv4/udp.c#L1317">1317</a>                                 UDP_MIB_INDATAGRAMS, is_udplite);
<a name="L1318" href="source/net/ipv4/udp.c#L1318">1318</a> 
<a name="L1319" href="source/net/ipv4/udp.c#L1319">1319</a>         <a href="ident?i=sock_recv_ts_and_drops">sock_recv_ts_and_drops</a>(<a href="ident?i=msg">msg</a>, sk, <a href="ident?i=skb">skb</a>);
<a name="L1320" href="source/net/ipv4/udp.c#L1320">1320</a> 
<a name="L1321" href="source/net/ipv4/udp.c#L1321">1321</a>         <b><i>/* Copy the address. */</i></b>
<a name="L1322" href="source/net/ipv4/udp.c#L1322">1322</a>         if (<a href="ident?i=sin">sin</a>) {
<a name="L1323" href="source/net/ipv4/udp.c#L1323">1323</a>                 <a href="ident?i=sin">sin</a>-&gt;sin_family = <a href="ident?i=AF_INET">AF_INET</a>;
<a name="L1324" href="source/net/ipv4/udp.c#L1324">1324</a>                 <a href="ident?i=sin">sin</a>-&gt;sin_port = <a href="ident?i=udp_hdr">udp_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;source;
<a name="L1325" href="source/net/ipv4/udp.c#L1325">1325</a>                 <a href="ident?i=sin">sin</a>-&gt;sin_addr.s_addr = <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=saddr">saddr</a>;
<a name="L1326" href="source/net/ipv4/udp.c#L1326">1326</a>                 <a href="ident?i=memset">memset</a>(<a href="ident?i=sin">sin</a>-&gt;<a href="ident?i=sin_zero">sin_zero</a>, 0, sizeof(<a href="ident?i=sin">sin</a>-&gt;<a href="ident?i=sin_zero">sin_zero</a>));
<a name="L1327" href="source/net/ipv4/udp.c#L1327">1327</a>                 *addr_len = sizeof(*<a href="ident?i=sin">sin</a>);
<a name="L1328" href="source/net/ipv4/udp.c#L1328">1328</a>         }
<a name="L1329" href="source/net/ipv4/udp.c#L1329">1329</a>         if (inet-&gt;cmsg_flags)
<a name="L1330" href="source/net/ipv4/udp.c#L1330">1330</a>                 <a href="ident?i=ip_cmsg_recv_offset">ip_cmsg_recv_offset</a>(<a href="ident?i=msg">msg</a>, <a href="ident?i=skb">skb</a>, sizeof(struct <a href="ident?i=udphdr">udphdr</a>));
<a name="L1331" href="source/net/ipv4/udp.c#L1331">1331</a> 
<a name="L1332" href="source/net/ipv4/udp.c#L1332">1332</a>         <a href="ident?i=err">err</a> = copied;
<a name="L1333" href="source/net/ipv4/udp.c#L1333">1333</a>         if (<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=MSG_TRUNC">MSG_TRUNC</a>)
<a name="L1334" href="source/net/ipv4/udp.c#L1334">1334</a>                 <a href="ident?i=err">err</a> = ulen;
<a name="L1335" href="source/net/ipv4/udp.c#L1335">1335</a> 
<a name="L1336" href="source/net/ipv4/udp.c#L1336">1336</a> out_free:
<a name="L1337" href="source/net/ipv4/udp.c#L1337">1337</a>         <a href="ident?i=skb_free_datagram_locked">skb_free_datagram_locked</a>(sk, <a href="ident?i=skb">skb</a>);
<a name="L1338" href="source/net/ipv4/udp.c#L1338">1338</a> <a href="ident?i=out">out</a>:
<a name="L1339" href="source/net/ipv4/udp.c#L1339">1339</a>         return <a href="ident?i=err">err</a>;
<a name="L1340" href="source/net/ipv4/udp.c#L1340">1340</a> 
<a name="L1341" href="source/net/ipv4/udp.c#L1341">1341</a> csum_copy_err:
<a name="L1342" href="source/net/ipv4/udp.c#L1342">1342</a>         <a href="ident?i=slow">slow</a> = <a href="ident?i=lock_sock_fast">lock_sock_fast</a>(sk);
<a name="L1343" href="source/net/ipv4/udp.c#L1343">1343</a>         if (!<a href="ident?i=skb_kill_datagram">skb_kill_datagram</a>(sk, <a href="ident?i=skb">skb</a>, <a href="ident?i=flags">flags</a>)) {
<a name="L1344" href="source/net/ipv4/udp.c#L1344">1344</a>                 <a href="ident?i=UDP_INC_STATS_USER">UDP_INC_STATS_USER</a>(<a href="ident?i=sock_net">sock_net</a>(sk), UDP_MIB_CSUMERRORS, is_udplite);
<a name="L1345" href="source/net/ipv4/udp.c#L1345">1345</a>                 <a href="ident?i=UDP_INC_STATS_USER">UDP_INC_STATS_USER</a>(<a href="ident?i=sock_net">sock_net</a>(sk), UDP_MIB_INERRORS, is_udplite);
<a name="L1346" href="source/net/ipv4/udp.c#L1346">1346</a>         }
<a name="L1347" href="source/net/ipv4/udp.c#L1347">1347</a>         <a href="ident?i=unlock_sock_fast">unlock_sock_fast</a>(sk, <a href="ident?i=slow">slow</a>);
<a name="L1348" href="source/net/ipv4/udp.c#L1348">1348</a> 
<a name="L1349" href="source/net/ipv4/udp.c#L1349">1349</a>         <b><i>/* starting over for a new packet, but check if we need to yield */</i></b>
<a name="L1350" href="source/net/ipv4/udp.c#L1350">1350</a>         <a href="ident?i=cond_resched">cond_resched</a>();
<a name="L1351" href="source/net/ipv4/udp.c#L1351">1351</a>         <a href="ident?i=msg">msg</a>-&gt;msg_flags &amp;= ~MSG_TRUNC;
<a name="L1352" href="source/net/ipv4/udp.c#L1352">1352</a>         goto try_again;
<a name="L1353" href="source/net/ipv4/udp.c#L1353">1353</a> }
<a name="L1354" href="source/net/ipv4/udp.c#L1354">1354</a> 
<a name="L1355" href="source/net/ipv4/udp.c#L1355">1355</a> int <a href="ident?i=udp_disconnect">udp_disconnect</a>(struct <a href="ident?i=sock">sock</a> *sk, int <a href="ident?i=flags">flags</a>)
<a name="L1356" href="source/net/ipv4/udp.c#L1356">1356</a> {
<a name="L1357" href="source/net/ipv4/udp.c#L1357">1357</a>         struct <a href="ident?i=inet_sock">inet_sock</a> *inet = <a href="ident?i=inet_sk">inet_sk</a>(sk);
<a name="L1358" href="source/net/ipv4/udp.c#L1358">1358</a>         <b><i>/*</i></b>
<a name="L1359" href="source/net/ipv4/udp.c#L1359">1359</a> <b><i>         *      1003.1g - break association.</i></b>
<a name="L1360" href="source/net/ipv4/udp.c#L1360">1360</a> <b><i>         */</i></b>
<a name="L1361" href="source/net/ipv4/udp.c#L1361">1361</a> 
<a name="L1362" href="source/net/ipv4/udp.c#L1362">1362</a>         sk-&gt;<a href="ident?i=sk_state">sk_state</a> = TCP_CLOSE;
<a name="L1363" href="source/net/ipv4/udp.c#L1363">1363</a>         inet-&gt;<a href="ident?i=inet_daddr">inet_daddr</a> = 0;
<a name="L1364" href="source/net/ipv4/udp.c#L1364">1364</a>         inet-&gt;<a href="ident?i=inet_dport">inet_dport</a> = 0;
<a name="L1365" href="source/net/ipv4/udp.c#L1365">1365</a>         <a href="ident?i=sock_rps_reset_rxhash">sock_rps_reset_rxhash</a>(sk);
<a name="L1366" href="source/net/ipv4/udp.c#L1366">1366</a>         sk-&gt;<a href="ident?i=sk_bound_dev_if">sk_bound_dev_if</a> = 0;
<a name="L1367" href="source/net/ipv4/udp.c#L1367">1367</a>         if (!(sk-&gt;sk_userlocks &amp; <a href="ident?i=SOCK_BINDADDR_LOCK">SOCK_BINDADDR_LOCK</a>))
<a name="L1368" href="source/net/ipv4/udp.c#L1368">1368</a>                 <a href="ident?i=inet_reset_saddr">inet_reset_saddr</a>(sk);
<a name="L1369" href="source/net/ipv4/udp.c#L1369">1369</a> 
<a name="L1370" href="source/net/ipv4/udp.c#L1370">1370</a>         if (!(sk-&gt;sk_userlocks &amp; <a href="ident?i=SOCK_BINDPORT_LOCK">SOCK_BINDPORT_LOCK</a>)) {
<a name="L1371" href="source/net/ipv4/udp.c#L1371">1371</a>                 sk-&gt;<a href="ident?i=sk_prot">sk_prot</a>-&gt;unhash(sk);
<a name="L1372" href="source/net/ipv4/udp.c#L1372">1372</a>                 inet-&gt;inet_sport = 0;
<a name="L1373" href="source/net/ipv4/udp.c#L1373">1373</a>         }
<a name="L1374" href="source/net/ipv4/udp.c#L1374">1374</a>         <a href="ident?i=sk_dst_reset">sk_dst_reset</a>(sk);
<a name="L1375" href="source/net/ipv4/udp.c#L1375">1375</a>         return 0;
<a name="L1376" href="source/net/ipv4/udp.c#L1376">1376</a> }
<a name="L1377" href="source/net/ipv4/udp.c#L1377">1377</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=udp_disconnect">udp_disconnect</a>);
<a name="L1378" href="source/net/ipv4/udp.c#L1378">1378</a> 
<a name="L1379" href="source/net/ipv4/udp.c#L1379">1379</a> void <a href="ident?i=udp_lib_unhash">udp_lib_unhash</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L1380" href="source/net/ipv4/udp.c#L1380">1380</a> {
<a name="L1381" href="source/net/ipv4/udp.c#L1381">1381</a>         if (<a href="ident?i=sk_hashed">sk_hashed</a>(sk)) {
<a name="L1382" href="source/net/ipv4/udp.c#L1382">1382</a>                 struct <a href="ident?i=udp_table">udp_table</a> *udptable = sk-&gt;<a href="ident?i=sk_prot">sk_prot</a>-&gt;<a href="ident?i=h">h</a>.<a href="ident?i=udp_table">udp_table</a>;
<a name="L1383" href="source/net/ipv4/udp.c#L1383">1383</a>                 struct <a href="ident?i=udp_hslot">udp_hslot</a> *hslot, *hslot2;
<a name="L1384" href="source/net/ipv4/udp.c#L1384">1384</a> 
<a name="L1385" href="source/net/ipv4/udp.c#L1385">1385</a>                 hslot  = <a href="ident?i=udp_hashslot">udp_hashslot</a>(udptable, <a href="ident?i=sock_net">sock_net</a>(sk),
<a name="L1386" href="source/net/ipv4/udp.c#L1386">1386</a>                                       <a href="ident?i=udp_sk">udp_sk</a>(sk)-&gt;<a href="ident?i=udp_port_hash">udp_port_hash</a>);
<a name="L1387" href="source/net/ipv4/udp.c#L1387">1387</a>                 hslot2 = <a href="ident?i=udp_hashslot2">udp_hashslot2</a>(udptable, <a href="ident?i=udp_sk">udp_sk</a>(sk)-&gt;<a href="ident?i=udp_portaddr_hash">udp_portaddr_hash</a>);
<a name="L1388" href="source/net/ipv4/udp.c#L1388">1388</a> 
<a name="L1389" href="source/net/ipv4/udp.c#L1389">1389</a>                 <a href="ident?i=spin_lock_bh">spin_lock_bh</a>(&amp;hslot-&gt;<a href="ident?i=lock">lock</a>);
<a name="L1390" href="source/net/ipv4/udp.c#L1390">1390</a>                 if (<a href="ident?i=sk_nulls_del_node_init_rcu">sk_nulls_del_node_init_rcu</a>(sk)) {
<a name="L1391" href="source/net/ipv4/udp.c#L1391">1391</a>                         hslot-&gt;<a href="ident?i=count">count</a>--;
<a name="L1392" href="source/net/ipv4/udp.c#L1392">1392</a>                         <a href="ident?i=inet_sk">inet_sk</a>(sk)-&gt;<a href="ident?i=inet_num">inet_num</a> = 0;
<a name="L1393" href="source/net/ipv4/udp.c#L1393">1393</a>                         <a href="ident?i=sock_prot_inuse_add">sock_prot_inuse_add</a>(<a href="ident?i=sock_net">sock_net</a>(sk), sk-&gt;<a href="ident?i=sk_prot">sk_prot</a>, -1);
<a name="L1394" href="source/net/ipv4/udp.c#L1394">1394</a> 
<a name="L1395" href="source/net/ipv4/udp.c#L1395">1395</a>                         <a href="ident?i=spin_lock">spin_lock</a>(&amp;hslot2-&gt;<a href="ident?i=lock">lock</a>);
<a name="L1396" href="source/net/ipv4/udp.c#L1396">1396</a>                         <a href="ident?i=hlist_nulls_del_init_rcu">hlist_nulls_del_init_rcu</a>(&amp;<a href="ident?i=udp_sk">udp_sk</a>(sk)-&gt;<a href="ident?i=udp_portaddr_node">udp_portaddr_node</a>);
<a name="L1397" href="source/net/ipv4/udp.c#L1397">1397</a>                         hslot2-&gt;<a href="ident?i=count">count</a>--;
<a name="L1398" href="source/net/ipv4/udp.c#L1398">1398</a>                         <a href="ident?i=spin_unlock">spin_unlock</a>(&amp;hslot2-&gt;<a href="ident?i=lock">lock</a>);
<a name="L1399" href="source/net/ipv4/udp.c#L1399">1399</a>                 }
<a name="L1400" href="source/net/ipv4/udp.c#L1400">1400</a>                 <a href="ident?i=spin_unlock_bh">spin_unlock_bh</a>(&amp;hslot-&gt;<a href="ident?i=lock">lock</a>);
<a name="L1401" href="source/net/ipv4/udp.c#L1401">1401</a>         }
<a name="L1402" href="source/net/ipv4/udp.c#L1402">1402</a> }
<a name="L1403" href="source/net/ipv4/udp.c#L1403">1403</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=udp_lib_unhash">udp_lib_unhash</a>);
<a name="L1404" href="source/net/ipv4/udp.c#L1404">1404</a> 
<a name="L1405" href="source/net/ipv4/udp.c#L1405">1405</a> <b><i>/*</i></b>
<a name="L1406" href="source/net/ipv4/udp.c#L1406">1406</a> <b><i> * inet_rcv_saddr was changed, we must rehash secondary hash</i></b>
<a name="L1407" href="source/net/ipv4/udp.c#L1407">1407</a> <b><i> */</i></b>
<a name="L1408" href="source/net/ipv4/udp.c#L1408">1408</a> void <a href="ident?i=udp_lib_rehash">udp_lib_rehash</a>(struct <a href="ident?i=sock">sock</a> *sk, <a href="ident?i=u16">u16</a> newhash)
<a name="L1409" href="source/net/ipv4/udp.c#L1409">1409</a> {
<a name="L1410" href="source/net/ipv4/udp.c#L1410">1410</a>         if (<a href="ident?i=sk_hashed">sk_hashed</a>(sk)) {
<a name="L1411" href="source/net/ipv4/udp.c#L1411">1411</a>                 struct <a href="ident?i=udp_table">udp_table</a> *udptable = sk-&gt;<a href="ident?i=sk_prot">sk_prot</a>-&gt;<a href="ident?i=h">h</a>.<a href="ident?i=udp_table">udp_table</a>;
<a name="L1412" href="source/net/ipv4/udp.c#L1412">1412</a>                 struct <a href="ident?i=udp_hslot">udp_hslot</a> *hslot, *hslot2, *nhslot2;
<a name="L1413" href="source/net/ipv4/udp.c#L1413">1413</a> 
<a name="L1414" href="source/net/ipv4/udp.c#L1414">1414</a>                 hslot2 = <a href="ident?i=udp_hashslot2">udp_hashslot2</a>(udptable, <a href="ident?i=udp_sk">udp_sk</a>(sk)-&gt;<a href="ident?i=udp_portaddr_hash">udp_portaddr_hash</a>);
<a name="L1415" href="source/net/ipv4/udp.c#L1415">1415</a>                 nhslot2 = <a href="ident?i=udp_hashslot2">udp_hashslot2</a>(udptable, newhash);
<a name="L1416" href="source/net/ipv4/udp.c#L1416">1416</a>                 <a href="ident?i=udp_sk">udp_sk</a>(sk)-&gt;<a href="ident?i=udp_portaddr_hash">udp_portaddr_hash</a> = newhash;
<a name="L1417" href="source/net/ipv4/udp.c#L1417">1417</a>                 if (hslot2 != nhslot2) {
<a name="L1418" href="source/net/ipv4/udp.c#L1418">1418</a>                         hslot = <a href="ident?i=udp_hashslot">udp_hashslot</a>(udptable, <a href="ident?i=sock_net">sock_net</a>(sk),
<a name="L1419" href="source/net/ipv4/udp.c#L1419">1419</a>                                              <a href="ident?i=udp_sk">udp_sk</a>(sk)-&gt;<a href="ident?i=udp_port_hash">udp_port_hash</a>);
<a name="L1420" href="source/net/ipv4/udp.c#L1420">1420</a>                         <b><i>/* we must lock primary chain too */</i></b>
<a name="L1421" href="source/net/ipv4/udp.c#L1421">1421</a>                         <a href="ident?i=spin_lock_bh">spin_lock_bh</a>(&amp;hslot-&gt;<a href="ident?i=lock">lock</a>);
<a name="L1422" href="source/net/ipv4/udp.c#L1422">1422</a> 
<a name="L1423" href="source/net/ipv4/udp.c#L1423">1423</a>                         <a href="ident?i=spin_lock">spin_lock</a>(&amp;hslot2-&gt;<a href="ident?i=lock">lock</a>);
<a name="L1424" href="source/net/ipv4/udp.c#L1424">1424</a>                         <a href="ident?i=hlist_nulls_del_init_rcu">hlist_nulls_del_init_rcu</a>(&amp;<a href="ident?i=udp_sk">udp_sk</a>(sk)-&gt;<a href="ident?i=udp_portaddr_node">udp_portaddr_node</a>);
<a name="L1425" href="source/net/ipv4/udp.c#L1425">1425</a>                         hslot2-&gt;<a href="ident?i=count">count</a>--;
<a name="L1426" href="source/net/ipv4/udp.c#L1426">1426</a>                         <a href="ident?i=spin_unlock">spin_unlock</a>(&amp;hslot2-&gt;<a href="ident?i=lock">lock</a>);
<a name="L1427" href="source/net/ipv4/udp.c#L1427">1427</a> 
<a name="L1428" href="source/net/ipv4/udp.c#L1428">1428</a>                         <a href="ident?i=spin_lock">spin_lock</a>(&amp;nhslot2-&gt;<a href="ident?i=lock">lock</a>);
<a name="L1429" href="source/net/ipv4/udp.c#L1429">1429</a>                         <a href="ident?i=hlist_nulls_add_head_rcu">hlist_nulls_add_head_rcu</a>(&amp;<a href="ident?i=udp_sk">udp_sk</a>(sk)-&gt;<a href="ident?i=udp_portaddr_node">udp_portaddr_node</a>,
<a name="L1430" href="source/net/ipv4/udp.c#L1430">1430</a>                                                  &amp;nhslot2-&gt;<a href="ident?i=head">head</a>);
<a name="L1431" href="source/net/ipv4/udp.c#L1431">1431</a>                         nhslot2-&gt;<a href="ident?i=count">count</a>++;
<a name="L1432" href="source/net/ipv4/udp.c#L1432">1432</a>                         <a href="ident?i=spin_unlock">spin_unlock</a>(&amp;nhslot2-&gt;<a href="ident?i=lock">lock</a>);
<a name="L1433" href="source/net/ipv4/udp.c#L1433">1433</a> 
<a name="L1434" href="source/net/ipv4/udp.c#L1434">1434</a>                         <a href="ident?i=spin_unlock_bh">spin_unlock_bh</a>(&amp;hslot-&gt;<a href="ident?i=lock">lock</a>);
<a name="L1435" href="source/net/ipv4/udp.c#L1435">1435</a>                 }
<a name="L1436" href="source/net/ipv4/udp.c#L1436">1436</a>         }
<a name="L1437" href="source/net/ipv4/udp.c#L1437">1437</a> }
<a name="L1438" href="source/net/ipv4/udp.c#L1438">1438</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=udp_lib_rehash">udp_lib_rehash</a>);
<a name="L1439" href="source/net/ipv4/udp.c#L1439">1439</a> 
<a name="L1440" href="source/net/ipv4/udp.c#L1440">1440</a> static void <a href="ident?i=udp_v4_rehash">udp_v4_rehash</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L1441" href="source/net/ipv4/udp.c#L1441">1441</a> {
<a name="L1442" href="source/net/ipv4/udp.c#L1442">1442</a>         <a href="ident?i=u16">u16</a> new_hash = <a href="ident?i=udp4_portaddr_hash">udp4_portaddr_hash</a>(<a href="ident?i=sock_net">sock_net</a>(sk),
<a name="L1443" href="source/net/ipv4/udp.c#L1443">1443</a>                                           <a href="ident?i=inet_sk">inet_sk</a>(sk)-&gt;<a href="ident?i=inet_rcv_saddr">inet_rcv_saddr</a>,
<a name="L1444" href="source/net/ipv4/udp.c#L1444">1444</a>                                           <a href="ident?i=inet_sk">inet_sk</a>(sk)-&gt;<a href="ident?i=inet_num">inet_num</a>);
<a name="L1445" href="source/net/ipv4/udp.c#L1445">1445</a>         <a href="ident?i=udp_lib_rehash">udp_lib_rehash</a>(sk, new_hash);
<a name="L1446" href="source/net/ipv4/udp.c#L1446">1446</a> }
<a name="L1447" href="source/net/ipv4/udp.c#L1447">1447</a> 
<a name="L1448" href="source/net/ipv4/udp.c#L1448">1448</a> static int <a href="ident?i=__udp_queue_rcv_skb">__udp_queue_rcv_skb</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L1449" href="source/net/ipv4/udp.c#L1449">1449</a> {
<a name="L1450" href="source/net/ipv4/udp.c#L1450">1450</a>         int <a href="ident?i=rc">rc</a>;
<a name="L1451" href="source/net/ipv4/udp.c#L1451">1451</a> 
<a name="L1452" href="source/net/ipv4/udp.c#L1452">1452</a>         if (<a href="ident?i=inet_sk">inet_sk</a>(sk)-&gt;<a href="ident?i=inet_daddr">inet_daddr</a>) {
<a name="L1453" href="source/net/ipv4/udp.c#L1453">1453</a>                 <a href="ident?i=sock_rps_save_rxhash">sock_rps_save_rxhash</a>(sk, <a href="ident?i=skb">skb</a>);
<a name="L1454" href="source/net/ipv4/udp.c#L1454">1454</a>                 <a href="ident?i=sk_mark_napi_id">sk_mark_napi_id</a>(sk, <a href="ident?i=skb">skb</a>);
<a name="L1455" href="source/net/ipv4/udp.c#L1455">1455</a>                 <a href="ident?i=sk_incoming_cpu_update">sk_incoming_cpu_update</a>(sk);
<a name="L1456" href="source/net/ipv4/udp.c#L1456">1456</a>         }
<a name="L1457" href="source/net/ipv4/udp.c#L1457">1457</a> 
<a name="L1458" href="source/net/ipv4/udp.c#L1458">1458</a>         <a href="ident?i=rc">rc</a> = <a href="ident?i=sock_queue_rcv_skb">sock_queue_rcv_skb</a>(sk, <a href="ident?i=skb">skb</a>);
<a name="L1459" href="source/net/ipv4/udp.c#L1459">1459</a>         if (<a href="ident?i=rc">rc</a> &lt; 0) {
<a name="L1460" href="source/net/ipv4/udp.c#L1460">1460</a>                 int is_udplite = <a href="ident?i=IS_UDPLITE">IS_UDPLITE</a>(sk);
<a name="L1461" href="source/net/ipv4/udp.c#L1461">1461</a> 
<a name="L1462" href="source/net/ipv4/udp.c#L1462">1462</a>                 <b><i>/* Note that an ENOMEM error is charged twice */</i></b>
<a name="L1463" href="source/net/ipv4/udp.c#L1463">1463</a>                 if (<a href="ident?i=rc">rc</a> == -<a href="ident?i=ENOMEM">ENOMEM</a>)
<a name="L1464" href="source/net/ipv4/udp.c#L1464">1464</a>                         <a href="ident?i=UDP_INC_STATS_BH">UDP_INC_STATS_BH</a>(<a href="ident?i=sock_net">sock_net</a>(sk), UDP_MIB_RCVBUFERRORS,
<a name="L1465" href="source/net/ipv4/udp.c#L1465">1465</a>                                          is_udplite);
<a name="L1466" href="source/net/ipv4/udp.c#L1466">1466</a>                 <a href="ident?i=UDP_INC_STATS_BH">UDP_INC_STATS_BH</a>(<a href="ident?i=sock_net">sock_net</a>(sk), UDP_MIB_INERRORS, is_udplite);
<a name="L1467" href="source/net/ipv4/udp.c#L1467">1467</a>                 <a href="ident?i=kfree_skb">kfree_skb</a>(<a href="ident?i=skb">skb</a>);
<a name="L1468" href="source/net/ipv4/udp.c#L1468">1468</a>                 trace_udp_fail_queue_rcv_skb(<a href="ident?i=rc">rc</a>, sk);
<a name="L1469" href="source/net/ipv4/udp.c#L1469">1469</a>                 return -1;
<a name="L1470" href="source/net/ipv4/udp.c#L1470">1470</a>         }
<a name="L1471" href="source/net/ipv4/udp.c#L1471">1471</a> 
<a name="L1472" href="source/net/ipv4/udp.c#L1472">1472</a>         return 0;
<a name="L1473" href="source/net/ipv4/udp.c#L1473">1473</a> 
<a name="L1474" href="source/net/ipv4/udp.c#L1474">1474</a> }
<a name="L1475" href="source/net/ipv4/udp.c#L1475">1475</a> 
<a name="L1476" href="source/net/ipv4/udp.c#L1476">1476</a> static struct <a href="ident?i=static_key">static_key</a> udp_encap_needed <a href="ident?i=__read_mostly">__read_mostly</a>;
<a name="L1477" href="source/net/ipv4/udp.c#L1477">1477</a> void <a href="ident?i=udp_encap_enable">udp_encap_enable</a>(void)
<a name="L1478" href="source/net/ipv4/udp.c#L1478">1478</a> {
<a name="L1479" href="source/net/ipv4/udp.c#L1479">1479</a>         if (!<a href="ident?i=static_key_enabled">static_key_enabled</a>(&amp;udp_encap_needed))
<a name="L1480" href="source/net/ipv4/udp.c#L1480">1480</a>                 <a href="ident?i=static_key_slow_inc">static_key_slow_inc</a>(&amp;udp_encap_needed);
<a name="L1481" href="source/net/ipv4/udp.c#L1481">1481</a> }
<a name="L1482" href="source/net/ipv4/udp.c#L1482">1482</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=udp_encap_enable">udp_encap_enable</a>);
<a name="L1483" href="source/net/ipv4/udp.c#L1483">1483</a> 
<a name="L1484" href="source/net/ipv4/udp.c#L1484">1484</a> <b><i>/* returns:</i></b>
<a name="L1485" href="source/net/ipv4/udp.c#L1485">1485</a> <b><i> *  -1: error</i></b>
<a name="L1486" href="source/net/ipv4/udp.c#L1486">1486</a> <b><i> *   0: success</i></b>
<a name="L1487" href="source/net/ipv4/udp.c#L1487">1487</a> <b><i> *  &gt;0: "udp encap" protocol resubmission</i></b>
<a name="L1488" href="source/net/ipv4/udp.c#L1488">1488</a> <b><i> *</i></b>
<a name="L1489" href="source/net/ipv4/udp.c#L1489">1489</a> <b><i> * Note that in the success and error cases, the skb is assumed to</i></b>
<a name="L1490" href="source/net/ipv4/udp.c#L1490">1490</a> <b><i> * have either been requeued or freed.</i></b>
<a name="L1491" href="source/net/ipv4/udp.c#L1491">1491</a> <b><i> */</i></b>
<a name="L1492" href="source/net/ipv4/udp.c#L1492">1492</a> int <a href="ident?i=udp_queue_rcv_skb">udp_queue_rcv_skb</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L1493" href="source/net/ipv4/udp.c#L1493">1493</a> {
<a name="L1494" href="source/net/ipv4/udp.c#L1494">1494</a>         struct <a href="ident?i=udp_sock">udp_sock</a> *<a href="ident?i=up">up</a> = <a href="ident?i=udp_sk">udp_sk</a>(sk);
<a name="L1495" href="source/net/ipv4/udp.c#L1495">1495</a>         int <a href="ident?i=rc">rc</a>;
<a name="L1496" href="source/net/ipv4/udp.c#L1496">1496</a>         int is_udplite = <a href="ident?i=IS_UDPLITE">IS_UDPLITE</a>(sk);
<a name="L1497" href="source/net/ipv4/udp.c#L1497">1497</a> 
<a name="L1498" href="source/net/ipv4/udp.c#L1498">1498</a>         <b><i>/*</i></b>
<a name="L1499" href="source/net/ipv4/udp.c#L1499">1499</a> <b><i>         *      Charge it to the socket, dropping if the queue is full.</i></b>
<a name="L1500" href="source/net/ipv4/udp.c#L1500">1500</a> <b><i>         */</i></b>
<a name="L1501" href="source/net/ipv4/udp.c#L1501">1501</a>         if (!<a href="ident?i=xfrm4_policy_check">xfrm4_policy_check</a>(sk, XFRM_POLICY_IN, <a href="ident?i=skb">skb</a>))
<a name="L1502" href="source/net/ipv4/udp.c#L1502">1502</a>                 goto <a href="ident?i=drop">drop</a>;
<a name="L1503" href="source/net/ipv4/udp.c#L1503">1503</a>         <a href="ident?i=nf_reset">nf_reset</a>(<a href="ident?i=skb">skb</a>);
<a name="L1504" href="source/net/ipv4/udp.c#L1504">1504</a> 
<a name="L1505" href="source/net/ipv4/udp.c#L1505">1505</a>         if (<a href="ident?i=static_key_false">static_key_false</a>(&amp;udp_encap_needed) &amp;&amp; <a href="ident?i=up">up</a>-&gt;encap_type) {
<a name="L1506" href="source/net/ipv4/udp.c#L1506">1506</a>                 int (*encap_rcv)(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>);
<a name="L1507" href="source/net/ipv4/udp.c#L1507">1507</a> 
<a name="L1508" href="source/net/ipv4/udp.c#L1508">1508</a>                 <b><i>/*</i></b>
<a name="L1509" href="source/net/ipv4/udp.c#L1509">1509</a> <b><i>                 * This is an encapsulation socket so pass the skb to</i></b>
<a name="L1510" href="source/net/ipv4/udp.c#L1510">1510</a> <b><i>                 * the socket's udp_encap_rcv() hook. Otherwise, just</i></b>
<a name="L1511" href="source/net/ipv4/udp.c#L1511">1511</a> <b><i>                 * fall through and pass this up the UDP socket.</i></b>
<a name="L1512" href="source/net/ipv4/udp.c#L1512">1512</a> <b><i>                 * up-&gt;encap_rcv() returns the following value:</i></b>
<a name="L1513" href="source/net/ipv4/udp.c#L1513">1513</a> <b><i>                 * =0 if skb was successfully passed to the encap</i></b>
<a name="L1514" href="source/net/ipv4/udp.c#L1514">1514</a> <b><i>                 *    handler or was discarded by it.</i></b>
<a name="L1515" href="source/net/ipv4/udp.c#L1515">1515</a> <b><i>                 * &gt;0 if skb should be passed on to UDP.</i></b>
<a name="L1516" href="source/net/ipv4/udp.c#L1516">1516</a> <b><i>                 * &lt;0 if skb should be resubmitted as proto -N</i></b>
<a name="L1517" href="source/net/ipv4/udp.c#L1517">1517</a> <b><i>                 */</i></b>
<a name="L1518" href="source/net/ipv4/udp.c#L1518">1518</a> 
<a name="L1519" href="source/net/ipv4/udp.c#L1519">1519</a>                 <b><i>/* if we're overly short, let UDP handle it */</i></b>
<a name="L1520" href="source/net/ipv4/udp.c#L1520">1520</a>                 encap_rcv = <a href="ident?i=ACCESS_ONCE">ACCESS_ONCE</a>(<a href="ident?i=up">up</a>-&gt;encap_rcv);
<a name="L1521" href="source/net/ipv4/udp.c#L1521">1521</a>                 if (<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a> &gt; sizeof(struct <a href="ident?i=udphdr">udphdr</a>) &amp;&amp; encap_rcv) {
<a name="L1522" href="source/net/ipv4/udp.c#L1522">1522</a>                         int <a href="ident?i=ret">ret</a>;
<a name="L1523" href="source/net/ipv4/udp.c#L1523">1523</a> 
<a name="L1524" href="source/net/ipv4/udp.c#L1524">1524</a>                         <b><i>/* Verify checksum before giving to encap */</i></b>
<a name="L1525" href="source/net/ipv4/udp.c#L1525">1525</a>                         if (<a href="ident?i=udp_lib_checksum_complete">udp_lib_checksum_complete</a>(<a href="ident?i=skb">skb</a>))
<a name="L1526" href="source/net/ipv4/udp.c#L1526">1526</a>                                 goto csum_error;
<a name="L1527" href="source/net/ipv4/udp.c#L1527">1527</a> 
<a name="L1528" href="source/net/ipv4/udp.c#L1528">1528</a>                         <a href="ident?i=ret">ret</a> = encap_rcv(sk, <a href="ident?i=skb">skb</a>);
<a name="L1529" href="source/net/ipv4/udp.c#L1529">1529</a>                         if (<a href="ident?i=ret">ret</a> &lt;= 0) {
<a name="L1530" href="source/net/ipv4/udp.c#L1530">1530</a>                                 <a href="ident?i=UDP_INC_STATS_BH">UDP_INC_STATS_BH</a>(<a href="ident?i=sock_net">sock_net</a>(sk),
<a name="L1531" href="source/net/ipv4/udp.c#L1531">1531</a>                                                  UDP_MIB_INDATAGRAMS,
<a name="L1532" href="source/net/ipv4/udp.c#L1532">1532</a>                                                  is_udplite);
<a name="L1533" href="source/net/ipv4/udp.c#L1533">1533</a>                                 return -<a href="ident?i=ret">ret</a>;
<a name="L1534" href="source/net/ipv4/udp.c#L1534">1534</a>                         }
<a name="L1535" href="source/net/ipv4/udp.c#L1535">1535</a>                 }
<a name="L1536" href="source/net/ipv4/udp.c#L1536">1536</a> 
<a name="L1537" href="source/net/ipv4/udp.c#L1537">1537</a>                 <b><i>/* FALLTHROUGH -- it's a UDP Packet */</i></b>
<a name="L1538" href="source/net/ipv4/udp.c#L1538">1538</a>         }
<a name="L1539" href="source/net/ipv4/udp.c#L1539">1539</a> 
<a name="L1540" href="source/net/ipv4/udp.c#L1540">1540</a>         <b><i>/*</i></b>
<a name="L1541" href="source/net/ipv4/udp.c#L1541">1541</a> <b><i>         *      UDP-Lite specific tests, ignored on UDP sockets</i></b>
<a name="L1542" href="source/net/ipv4/udp.c#L1542">1542</a> <b><i>         */</i></b>
<a name="L1543" href="source/net/ipv4/udp.c#L1543">1543</a>         if ((is_udplite &amp; <a href="ident?i=UDPLITE_RECV_CC">UDPLITE_RECV_CC</a>)  &amp;&amp;  <a href="ident?i=UDP_SKB_CB">UDP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;partial_cov) {
<a name="L1544" href="source/net/ipv4/udp.c#L1544">1544</a> 
<a name="L1545" href="source/net/ipv4/udp.c#L1545">1545</a>                 <b><i>/*</i></b>
<a name="L1546" href="source/net/ipv4/udp.c#L1546">1546</a> <b><i>                 * MIB statistics other than incrementing the error count are</i></b>
<a name="L1547" href="source/net/ipv4/udp.c#L1547">1547</a> <b><i>                 * disabled for the following two types of errors: these depend</i></b>
<a name="L1548" href="source/net/ipv4/udp.c#L1548">1548</a> <b><i>                 * on the application settings, not on the functioning of the</i></b>
<a name="L1549" href="source/net/ipv4/udp.c#L1549">1549</a> <b><i>                 * protocol stack as such.</i></b>
<a name="L1550" href="source/net/ipv4/udp.c#L1550">1550</a> <b><i>                 *</i></b>
<a name="L1551" href="source/net/ipv4/udp.c#L1551">1551</a> <b><i>                 * RFC 3828 here recommends (sec 3.3): "There should also be a</i></b>
<a name="L1552" href="source/net/ipv4/udp.c#L1552">1552</a> <b><i>                 * way ... to ... at least let the receiving application block</i></b>
<a name="L1553" href="source/net/ipv4/udp.c#L1553">1553</a> <b><i>                 * delivery of packets with coverage values less than a value</i></b>
<a name="L1554" href="source/net/ipv4/udp.c#L1554">1554</a> <b><i>                 * provided by the application."</i></b>
<a name="L1555" href="source/net/ipv4/udp.c#L1555">1555</a> <b><i>                 */</i></b>
<a name="L1556" href="source/net/ipv4/udp.c#L1556">1556</a>                 if (<a href="ident?i=up">up</a>-&gt;pcrlen == 0) {          <b><i>/* full coverage was set  */</i></b>
<a name="L1557" href="source/net/ipv4/udp.c#L1557">1557</a>                         <a href="ident?i=net_dbg_ratelimited">net_dbg_ratelimited</a>(<i>"UDPLite: partial coverage %d while full coverage %d requested\n"</i>,
<a name="L1558" href="source/net/ipv4/udp.c#L1558">1558</a>                                             <a href="ident?i=UDP_SKB_CB">UDP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;cscov, <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a>);
<a name="L1559" href="source/net/ipv4/udp.c#L1559">1559</a>                         goto <a href="ident?i=drop">drop</a>;
<a name="L1560" href="source/net/ipv4/udp.c#L1560">1560</a>                 }
<a name="L1561" href="source/net/ipv4/udp.c#L1561">1561</a>                 <b><i>/* The next case involves violating the min. coverage requested</i></b>
<a name="L1562" href="source/net/ipv4/udp.c#L1562">1562</a> <b><i>                 * by the receiver. This is subtle: if receiver wants x and x is</i></b>
<a name="L1563" href="source/net/ipv4/udp.c#L1563">1563</a> <b><i>                 * greater than the buffersize/MTU then receiver will complain</i></b>
<a name="L1564" href="source/net/ipv4/udp.c#L1564">1564</a> <b><i>                 * that it wants x while sender emits packets of smaller size y.</i></b>
<a name="L1565" href="source/net/ipv4/udp.c#L1565">1565</a> <b><i>                 * Therefore the above ...()-&gt;partial_cov statement is essential.</i></b>
<a name="L1566" href="source/net/ipv4/udp.c#L1566">1566</a> <b><i>                 */</i></b>
<a name="L1567" href="source/net/ipv4/udp.c#L1567">1567</a>                 if (<a href="ident?i=UDP_SKB_CB">UDP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;cscov  &lt;  <a href="ident?i=up">up</a>-&gt;pcrlen) {
<a name="L1568" href="source/net/ipv4/udp.c#L1568">1568</a>                         <a href="ident?i=net_dbg_ratelimited">net_dbg_ratelimited</a>(<i>"UDPLite: coverage %d too small, need min %d\n"</i>,
<a name="L1569" href="source/net/ipv4/udp.c#L1569">1569</a>                                             <a href="ident?i=UDP_SKB_CB">UDP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;cscov, <a href="ident?i=up">up</a>-&gt;pcrlen);
<a name="L1570" href="source/net/ipv4/udp.c#L1570">1570</a>                         goto <a href="ident?i=drop">drop</a>;
<a name="L1571" href="source/net/ipv4/udp.c#L1571">1571</a>                 }
<a name="L1572" href="source/net/ipv4/udp.c#L1572">1572</a>         }
<a name="L1573" href="source/net/ipv4/udp.c#L1573">1573</a> 
<a name="L1574" href="source/net/ipv4/udp.c#L1574">1574</a>         if (<a href="ident?i=rcu_access_pointer">rcu_access_pointer</a>(sk-&gt;<a href="ident?i=sk_filter">sk_filter</a>) &amp;&amp;
<a name="L1575" href="source/net/ipv4/udp.c#L1575">1575</a>             <a href="ident?i=udp_lib_checksum_complete">udp_lib_checksum_complete</a>(<a href="ident?i=skb">skb</a>))
<a name="L1576" href="source/net/ipv4/udp.c#L1576">1576</a>                 goto csum_error;
<a name="L1577" href="source/net/ipv4/udp.c#L1577">1577</a> 
<a name="L1578" href="source/net/ipv4/udp.c#L1578">1578</a>         if (<a href="ident?i=sk_rcvqueues_full">sk_rcvqueues_full</a>(sk, sk-&gt;sk_rcvbuf)) {
<a name="L1579" href="source/net/ipv4/udp.c#L1579">1579</a>                 <a href="ident?i=UDP_INC_STATS_BH">UDP_INC_STATS_BH</a>(<a href="ident?i=sock_net">sock_net</a>(sk), UDP_MIB_RCVBUFERRORS,
<a name="L1580" href="source/net/ipv4/udp.c#L1580">1580</a>                                  is_udplite);
<a name="L1581" href="source/net/ipv4/udp.c#L1581">1581</a>                 goto <a href="ident?i=drop">drop</a>;
<a name="L1582" href="source/net/ipv4/udp.c#L1582">1582</a>         }
<a name="L1583" href="source/net/ipv4/udp.c#L1583">1583</a> 
<a name="L1584" href="source/net/ipv4/udp.c#L1584">1584</a>         <a href="ident?i=rc">rc</a> = 0;
<a name="L1585" href="source/net/ipv4/udp.c#L1585">1585</a> 
<a name="L1586" href="source/net/ipv4/udp.c#L1586">1586</a>         <a href="ident?i=ipv4_pktinfo_prepare">ipv4_pktinfo_prepare</a>(sk, <a href="ident?i=skb">skb</a>);
<a name="L1587" href="source/net/ipv4/udp.c#L1587">1587</a>         <a href="ident?i=bh_lock_sock">bh_lock_sock</a>(sk);
<a name="L1588" href="source/net/ipv4/udp.c#L1588">1588</a>         if (!<a href="ident?i=sock_owned_by_user">sock_owned_by_user</a>(sk))
<a name="L1589" href="source/net/ipv4/udp.c#L1589">1589</a>                 <a href="ident?i=rc">rc</a> = <a href="ident?i=__udp_queue_rcv_skb">__udp_queue_rcv_skb</a>(sk, <a href="ident?i=skb">skb</a>);
<a name="L1590" href="source/net/ipv4/udp.c#L1590">1590</a>         else if (<a href="ident?i=sk_add_backlog">sk_add_backlog</a>(sk, <a href="ident?i=skb">skb</a>, sk-&gt;sk_rcvbuf)) {
<a name="L1591" href="source/net/ipv4/udp.c#L1591">1591</a>                 <a href="ident?i=bh_unlock_sock">bh_unlock_sock</a>(sk);
<a name="L1592" href="source/net/ipv4/udp.c#L1592">1592</a>                 goto <a href="ident?i=drop">drop</a>;
<a name="L1593" href="source/net/ipv4/udp.c#L1593">1593</a>         }
<a name="L1594" href="source/net/ipv4/udp.c#L1594">1594</a>         <a href="ident?i=bh_unlock_sock">bh_unlock_sock</a>(sk);
<a name="L1595" href="source/net/ipv4/udp.c#L1595">1595</a> 
<a name="L1596" href="source/net/ipv4/udp.c#L1596">1596</a>         return <a href="ident?i=rc">rc</a>;
<a name="L1597" href="source/net/ipv4/udp.c#L1597">1597</a> 
<a name="L1598" href="source/net/ipv4/udp.c#L1598">1598</a> csum_error:
<a name="L1599" href="source/net/ipv4/udp.c#L1599">1599</a>         <a href="ident?i=UDP_INC_STATS_BH">UDP_INC_STATS_BH</a>(<a href="ident?i=sock_net">sock_net</a>(sk), UDP_MIB_CSUMERRORS, is_udplite);
<a name="L1600" href="source/net/ipv4/udp.c#L1600">1600</a> <a href="ident?i=drop">drop</a>:
<a name="L1601" href="source/net/ipv4/udp.c#L1601">1601</a>         <a href="ident?i=UDP_INC_STATS_BH">UDP_INC_STATS_BH</a>(<a href="ident?i=sock_net">sock_net</a>(sk), UDP_MIB_INERRORS, is_udplite);
<a name="L1602" href="source/net/ipv4/udp.c#L1602">1602</a>         <a href="ident?i=atomic_inc">atomic_inc</a>(&amp;sk-&gt;sk_drops);
<a name="L1603" href="source/net/ipv4/udp.c#L1603">1603</a>         <a href="ident?i=kfree_skb">kfree_skb</a>(<a href="ident?i=skb">skb</a>);
<a name="L1604" href="source/net/ipv4/udp.c#L1604">1604</a>         return -1;
<a name="L1605" href="source/net/ipv4/udp.c#L1605">1605</a> }
<a name="L1606" href="source/net/ipv4/udp.c#L1606">1606</a> 
<a name="L1607" href="source/net/ipv4/udp.c#L1607">1607</a> static void <a href="ident?i=flush_stack">flush_stack</a>(struct <a href="ident?i=sock">sock</a> **<a href="ident?i=stack">stack</a>, unsigned int <a href="ident?i=count">count</a>,
<a name="L1608" href="source/net/ipv4/udp.c#L1608">1608</a>                         struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, unsigned int final)
<a name="L1609" href="source/net/ipv4/udp.c#L1609">1609</a> {
<a name="L1610" href="source/net/ipv4/udp.c#L1610">1610</a>         unsigned int <a href="ident?i=i">i</a>;
<a name="L1611" href="source/net/ipv4/udp.c#L1611">1611</a>         struct <a href="ident?i=sk_buff">sk_buff</a> *skb1 = <a href="ident?i=NULL">NULL</a>;
<a name="L1612" href="source/net/ipv4/udp.c#L1612">1612</a>         struct <a href="ident?i=sock">sock</a> *sk;
<a name="L1613" href="source/net/ipv4/udp.c#L1613">1613</a> 
<a name="L1614" href="source/net/ipv4/udp.c#L1614">1614</a>         for (<a href="ident?i=i">i</a> = 0; <a href="ident?i=i">i</a> &lt; <a href="ident?i=count">count</a>; <a href="ident?i=i">i</a>++) {
<a name="L1615" href="source/net/ipv4/udp.c#L1615">1615</a>                 sk = <a href="ident?i=stack">stack</a>[<a href="ident?i=i">i</a>];
<a name="L1616" href="source/net/ipv4/udp.c#L1616">1616</a>                 if (<a href="ident?i=likely">likely</a>(!skb1))
<a name="L1617" href="source/net/ipv4/udp.c#L1617">1617</a>                         skb1 = (<a href="ident?i=i">i</a> == final) ? <a href="ident?i=skb">skb</a> : <a href="ident?i=skb_clone">skb_clone</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=GFP_ATOMIC">GFP_ATOMIC</a>);
<a name="L1618" href="source/net/ipv4/udp.c#L1618">1618</a> 
<a name="L1619" href="source/net/ipv4/udp.c#L1619">1619</a>                 if (!skb1) {
<a name="L1620" href="source/net/ipv4/udp.c#L1620">1620</a>                         <a href="ident?i=atomic_inc">atomic_inc</a>(&amp;sk-&gt;sk_drops);
<a name="L1621" href="source/net/ipv4/udp.c#L1621">1621</a>                         <a href="ident?i=UDP_INC_STATS_BH">UDP_INC_STATS_BH</a>(<a href="ident?i=sock_net">sock_net</a>(sk), UDP_MIB_RCVBUFERRORS,
<a name="L1622" href="source/net/ipv4/udp.c#L1622">1622</a>                                          <a href="ident?i=IS_UDPLITE">IS_UDPLITE</a>(sk));
<a name="L1623" href="source/net/ipv4/udp.c#L1623">1623</a>                         <a href="ident?i=UDP_INC_STATS_BH">UDP_INC_STATS_BH</a>(<a href="ident?i=sock_net">sock_net</a>(sk), UDP_MIB_INERRORS,
<a name="L1624" href="source/net/ipv4/udp.c#L1624">1624</a>                                          <a href="ident?i=IS_UDPLITE">IS_UDPLITE</a>(sk));
<a name="L1625" href="source/net/ipv4/udp.c#L1625">1625</a>                 }
<a name="L1626" href="source/net/ipv4/udp.c#L1626">1626</a> 
<a name="L1627" href="source/net/ipv4/udp.c#L1627">1627</a>                 if (skb1 &amp;&amp; <a href="ident?i=udp_queue_rcv_skb">udp_queue_rcv_skb</a>(sk, skb1) &lt;= 0)
<a name="L1628" href="source/net/ipv4/udp.c#L1628">1628</a>                         skb1 = <a href="ident?i=NULL">NULL</a>;
<a name="L1629" href="source/net/ipv4/udp.c#L1629">1629</a> 
<a name="L1630" href="source/net/ipv4/udp.c#L1630">1630</a>                 <a href="ident?i=sock_put">sock_put</a>(sk);
<a name="L1631" href="source/net/ipv4/udp.c#L1631">1631</a>         }
<a name="L1632" href="source/net/ipv4/udp.c#L1632">1632</a>         if (<a href="ident?i=unlikely">unlikely</a>(skb1))
<a name="L1633" href="source/net/ipv4/udp.c#L1633">1633</a>                 <a href="ident?i=kfree_skb">kfree_skb</a>(skb1);
<a name="L1634" href="source/net/ipv4/udp.c#L1634">1634</a> }
<a name="L1635" href="source/net/ipv4/udp.c#L1635">1635</a> 
<a name="L1636" href="source/net/ipv4/udp.c#L1636">1636</a> <b><i>/* For TCP sockets, sk_rx_dst is protected by socket lock</i></b>
<a name="L1637" href="source/net/ipv4/udp.c#L1637">1637</a> <b><i> * For UDP, we use xchg() to guard against concurrent changes.</i></b>
<a name="L1638" href="source/net/ipv4/udp.c#L1638">1638</a> <b><i> */</i></b>
<a name="L1639" href="source/net/ipv4/udp.c#L1639">1639</a> static void <a href="ident?i=udp_sk_rx_dst_set">udp_sk_rx_dst_set</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=dst_entry">dst_entry</a> *<a href="ident?i=dst">dst</a>)
<a name="L1640" href="source/net/ipv4/udp.c#L1640">1640</a> {
<a name="L1641" href="source/net/ipv4/udp.c#L1641">1641</a>         struct <a href="ident?i=dst_entry">dst_entry</a> *<a href="ident?i=old">old</a>;
<a name="L1642" href="source/net/ipv4/udp.c#L1642">1642</a> 
<a name="L1643" href="source/net/ipv4/udp.c#L1643">1643</a>         <a href="ident?i=dst_hold">dst_hold</a>(<a href="ident?i=dst">dst</a>);
<a name="L1644" href="source/net/ipv4/udp.c#L1644">1644</a>         <a href="ident?i=old">old</a> = <a href="ident?i=xchg">xchg</a>(&amp;sk-&gt;sk_rx_dst, <a href="ident?i=dst">dst</a>);
<a name="L1645" href="source/net/ipv4/udp.c#L1645">1645</a>         <a href="ident?i=dst_release">dst_release</a>(<a href="ident?i=old">old</a>);
<a name="L1646" href="source/net/ipv4/udp.c#L1646">1646</a> }
<a name="L1647" href="source/net/ipv4/udp.c#L1647">1647</a> 
<a name="L1648" href="source/net/ipv4/udp.c#L1648">1648</a> <b><i>/*</i></b>
<a name="L1649" href="source/net/ipv4/udp.c#L1649">1649</a> <b><i> *      Multicasts and broadcasts go to each listener.</i></b>
<a name="L1650" href="source/net/ipv4/udp.c#L1650">1650</a> <b><i> *</i></b>
<a name="L1651" href="source/net/ipv4/udp.c#L1651">1651</a> <b><i> *      Note: called only from the BH handler context.</i></b>
<a name="L1652" href="source/net/ipv4/udp.c#L1652">1652</a> <b><i> */</i></b>
<a name="L1653" href="source/net/ipv4/udp.c#L1653">1653</a> static int <a href="ident?i=__udp4_lib_mcast_deliver">__udp4_lib_mcast_deliver</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
<a name="L1654" href="source/net/ipv4/udp.c#L1654">1654</a>                                     struct <a href="ident?i=udphdr">udphdr</a>  *uh,
<a name="L1655" href="source/net/ipv4/udp.c#L1655">1655</a>                                     <a href="ident?i=__be32">__be32</a> <a href="ident?i=saddr">saddr</a>, <a href="ident?i=__be32">__be32</a> <a href="ident?i=daddr">daddr</a>,
<a name="L1656" href="source/net/ipv4/udp.c#L1656">1656</a>                                     struct <a href="ident?i=udp_table">udp_table</a> *udptable,
<a name="L1657" href="source/net/ipv4/udp.c#L1657">1657</a>                                     int <a href="ident?i=proto">proto</a>)
<a name="L1658" href="source/net/ipv4/udp.c#L1658">1658</a> {
<a name="L1659" href="source/net/ipv4/udp.c#L1659">1659</a>         struct <a href="ident?i=sock">sock</a> *sk, *<a href="ident?i=stack">stack</a>[256 / sizeof(struct <a href="ident?i=sock">sock</a> *)];
<a name="L1660" href="source/net/ipv4/udp.c#L1660">1660</a>         struct <a href="ident?i=hlist_nulls_node">hlist_nulls_node</a> *<a href="ident?i=node">node</a>;
<a name="L1661" href="source/net/ipv4/udp.c#L1661">1661</a>         unsigned short hnum = <a href="ident?i=ntohs">ntohs</a>(uh-&gt;<a href="ident?i=dest">dest</a>);
<a name="L1662" href="source/net/ipv4/udp.c#L1662">1662</a>         struct <a href="ident?i=udp_hslot">udp_hslot</a> *hslot = <a href="ident?i=udp_hashslot">udp_hashslot</a>(udptable, <a href="ident?i=net">net</a>, hnum);
<a name="L1663" href="source/net/ipv4/udp.c#L1663">1663</a>         int dif = <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=dev">dev</a>-&gt;ifindex;
<a name="L1664" href="source/net/ipv4/udp.c#L1664">1664</a>         unsigned int <a href="ident?i=count">count</a> = 0, <a href="ident?i=offset">offset</a> = <a href="ident?i=offsetof">offsetof</a>(typeof(*sk), <a href="ident?i=sk_nulls_node">sk_nulls_node</a>);
<a name="L1665" href="source/net/ipv4/udp.c#L1665">1665</a>         unsigned int hash2 = 0, hash2_any = 0, use_hash2 = (hslot-&gt;<a href="ident?i=count">count</a> &gt; 10);
<a name="L1666" href="source/net/ipv4/udp.c#L1666">1666</a>         <a href="ident?i=bool">bool</a> inner_flushed = <a href="ident?i=false">false</a>;
<a name="L1667" href="source/net/ipv4/udp.c#L1667">1667</a> 
<a name="L1668" href="source/net/ipv4/udp.c#L1668">1668</a>         if (use_hash2) {
<a name="L1669" href="source/net/ipv4/udp.c#L1669">1669</a>                 hash2_any = <a href="ident?i=udp4_portaddr_hash">udp4_portaddr_hash</a>(<a href="ident?i=net">net</a>, <a href="ident?i=htonl">htonl</a>(<a href="ident?i=INADDR_ANY">INADDR_ANY</a>), hnum) &amp;
<a name="L1670" href="source/net/ipv4/udp.c#L1670">1670</a>                             <a href="ident?i=udp_table">udp_table</a>.<a href="ident?i=mask">mask</a>;
<a name="L1671" href="source/net/ipv4/udp.c#L1671">1671</a>                 hash2 = <a href="ident?i=udp4_portaddr_hash">udp4_portaddr_hash</a>(<a href="ident?i=net">net</a>, <a href="ident?i=daddr">daddr</a>, hnum) &amp; <a href="ident?i=udp_table">udp_table</a>.<a href="ident?i=mask">mask</a>;
<a name="L1672" href="source/net/ipv4/udp.c#L1672">1672</a> start_lookup:
<a name="L1673" href="source/net/ipv4/udp.c#L1673">1673</a>                 hslot = &amp;<a href="ident?i=udp_table">udp_table</a>.hash2[hash2];
<a name="L1674" href="source/net/ipv4/udp.c#L1674">1674</a>                 <a href="ident?i=offset">offset</a> = <a href="ident?i=offsetof">offsetof</a>(typeof(*sk), __sk_common.skc_portaddr_node);
<a name="L1675" href="source/net/ipv4/udp.c#L1675">1675</a>         }
<a name="L1676" href="source/net/ipv4/udp.c#L1676">1676</a> 
<a name="L1677" href="source/net/ipv4/udp.c#L1677">1677</a>         <a href="ident?i=spin_lock">spin_lock</a>(&amp;hslot-&gt;<a href="ident?i=lock">lock</a>);
<a name="L1678" href="source/net/ipv4/udp.c#L1678">1678</a>         <a href="ident?i=sk_nulls_for_each_entry_offset">sk_nulls_for_each_entry_offset</a>(sk, <a href="ident?i=node">node</a>, &amp;hslot-&gt;<a href="ident?i=head">head</a>, <a href="ident?i=offset">offset</a>) {
<a name="L1679" href="source/net/ipv4/udp.c#L1679">1679</a>                 if (<a href="ident?i=__udp_is_mcast_sock">__udp_is_mcast_sock</a>(<a href="ident?i=net">net</a>, sk,
<a name="L1680" href="source/net/ipv4/udp.c#L1680">1680</a>                                         uh-&gt;<a href="ident?i=dest">dest</a>, <a href="ident?i=daddr">daddr</a>,
<a name="L1681" href="source/net/ipv4/udp.c#L1681">1681</a>                                         uh-&gt;source, <a href="ident?i=saddr">saddr</a>,
<a name="L1682" href="source/net/ipv4/udp.c#L1682">1682</a>                                         dif, hnum)) {
<a name="L1683" href="source/net/ipv4/udp.c#L1683">1683</a>                         if (<a href="ident?i=unlikely">unlikely</a>(<a href="ident?i=count">count</a> == <a href="ident?i=ARRAY_SIZE">ARRAY_SIZE</a>(<a href="ident?i=stack">stack</a>))) {
<a name="L1684" href="source/net/ipv4/udp.c#L1684">1684</a>                                 <a href="ident?i=flush_stack">flush_stack</a>(<a href="ident?i=stack">stack</a>, <a href="ident?i=count">count</a>, <a href="ident?i=skb">skb</a>, ~0);
<a name="L1685" href="source/net/ipv4/udp.c#L1685">1685</a>                                 inner_flushed = <a href="ident?i=true">true</a>;
<a name="L1686" href="source/net/ipv4/udp.c#L1686">1686</a>                                 <a href="ident?i=count">count</a> = 0;
<a name="L1687" href="source/net/ipv4/udp.c#L1687">1687</a>                         }
<a name="L1688" href="source/net/ipv4/udp.c#L1688">1688</a>                         <a href="ident?i=stack">stack</a>[<a href="ident?i=count">count</a>++] = sk;
<a name="L1689" href="source/net/ipv4/udp.c#L1689">1689</a>                         <a href="ident?i=sock_hold">sock_hold</a>(sk);
<a name="L1690" href="source/net/ipv4/udp.c#L1690">1690</a>                 }
<a name="L1691" href="source/net/ipv4/udp.c#L1691">1691</a>         }
<a name="L1692" href="source/net/ipv4/udp.c#L1692">1692</a> 
<a name="L1693" href="source/net/ipv4/udp.c#L1693">1693</a>         <a href="ident?i=spin_unlock">spin_unlock</a>(&amp;hslot-&gt;<a href="ident?i=lock">lock</a>);
<a name="L1694" href="source/net/ipv4/udp.c#L1694">1694</a> 
<a name="L1695" href="source/net/ipv4/udp.c#L1695">1695</a>         <b><i>/* Also lookup *:port if we are using hash2 and haven't done so yet. */</i></b>
<a name="L1696" href="source/net/ipv4/udp.c#L1696">1696</a>         if (use_hash2 &amp;&amp; hash2 != hash2_any) {
<a name="L1697" href="source/net/ipv4/udp.c#L1697">1697</a>                 hash2 = hash2_any;
<a name="L1698" href="source/net/ipv4/udp.c#L1698">1698</a>                 goto start_lookup;
<a name="L1699" href="source/net/ipv4/udp.c#L1699">1699</a>         }
<a name="L1700" href="source/net/ipv4/udp.c#L1700">1700</a> 
<a name="L1701" href="source/net/ipv4/udp.c#L1701">1701</a>         <b><i>/*</i></b>
<a name="L1702" href="source/net/ipv4/udp.c#L1702">1702</a> <b><i>         * do the slow work with no lock held</i></b>
<a name="L1703" href="source/net/ipv4/udp.c#L1703">1703</a> <b><i>         */</i></b>
<a name="L1704" href="source/net/ipv4/udp.c#L1704">1704</a>         if (<a href="ident?i=count">count</a>) {
<a name="L1705" href="source/net/ipv4/udp.c#L1705">1705</a>                 <a href="ident?i=flush_stack">flush_stack</a>(<a href="ident?i=stack">stack</a>, <a href="ident?i=count">count</a>, <a href="ident?i=skb">skb</a>, <a href="ident?i=count">count</a> - 1);
<a name="L1706" href="source/net/ipv4/udp.c#L1706">1706</a>         } else {
<a name="L1707" href="source/net/ipv4/udp.c#L1707">1707</a>                 if (!inner_flushed)
<a name="L1708" href="source/net/ipv4/udp.c#L1708">1708</a>                         <a href="ident?i=UDP_INC_STATS_BH">UDP_INC_STATS_BH</a>(<a href="ident?i=net">net</a>, UDP_MIB_IGNOREDMULTI,
<a name="L1709" href="source/net/ipv4/udp.c#L1709">1709</a>                                          <a href="ident?i=proto">proto</a> == <a href="ident?i=IPPROTO_UDPLITE">IPPROTO_UDPLITE</a>);
<a name="L1710" href="source/net/ipv4/udp.c#L1710">1710</a>                 <a href="ident?i=consume_skb">consume_skb</a>(<a href="ident?i=skb">skb</a>);
<a name="L1711" href="source/net/ipv4/udp.c#L1711">1711</a>         }
<a name="L1712" href="source/net/ipv4/udp.c#L1712">1712</a>         return 0;
<a name="L1713" href="source/net/ipv4/udp.c#L1713">1713</a> }
<a name="L1714" href="source/net/ipv4/udp.c#L1714">1714</a> 
<a name="L1715" href="source/net/ipv4/udp.c#L1715">1715</a> <b><i>/* Initialize UDP checksum. If exited with zero value (success),</i></b>
<a name="L1716" href="source/net/ipv4/udp.c#L1716">1716</a> <b><i> * CHECKSUM_UNNECESSARY means, that no more checks are required.</i></b>
<a name="L1717" href="source/net/ipv4/udp.c#L1717">1717</a> <b><i> * Otherwise, csum completion requires chacksumming packet body,</i></b>
<a name="L1718" href="source/net/ipv4/udp.c#L1718">1718</a> <b><i> * including udp header and folding it to skb-&gt;csum.</i></b>
<a name="L1719" href="source/net/ipv4/udp.c#L1719">1719</a> <b><i> */</i></b>
<a name="L1720" href="source/net/ipv4/udp.c#L1720">1720</a> static inline int <a href="ident?i=udp4_csum_init">udp4_csum_init</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, struct <a href="ident?i=udphdr">udphdr</a> *uh,
<a name="L1721" href="source/net/ipv4/udp.c#L1721">1721</a>                                  int <a href="ident?i=proto">proto</a>)
<a name="L1722" href="source/net/ipv4/udp.c#L1722">1722</a> {
<a name="L1723" href="source/net/ipv4/udp.c#L1723">1723</a>         int <a href="ident?i=err">err</a>;
<a name="L1724" href="source/net/ipv4/udp.c#L1724">1724</a> 
<a name="L1725" href="source/net/ipv4/udp.c#L1725">1725</a>         <a href="ident?i=UDP_SKB_CB">UDP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;partial_cov = 0;
<a name="L1726" href="source/net/ipv4/udp.c#L1726">1726</a>         <a href="ident?i=UDP_SKB_CB">UDP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;cscov = <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a>;
<a name="L1727" href="source/net/ipv4/udp.c#L1727">1727</a> 
<a name="L1728" href="source/net/ipv4/udp.c#L1728">1728</a>         if (<a href="ident?i=proto">proto</a> == <a href="ident?i=IPPROTO_UDPLITE">IPPROTO_UDPLITE</a>) {
<a name="L1729" href="source/net/ipv4/udp.c#L1729">1729</a>                 <a href="ident?i=err">err</a> = <a href="ident?i=udplite_checksum_init">udplite_checksum_init</a>(<a href="ident?i=skb">skb</a>, uh);
<a name="L1730" href="source/net/ipv4/udp.c#L1730">1730</a>                 if (<a href="ident?i=err">err</a>)
<a name="L1731" href="source/net/ipv4/udp.c#L1731">1731</a>                         return <a href="ident?i=err">err</a>;
<a name="L1732" href="source/net/ipv4/udp.c#L1732">1732</a>         }
<a name="L1733" href="source/net/ipv4/udp.c#L1733">1733</a> 
<a name="L1734" href="source/net/ipv4/udp.c#L1734">1734</a>         return <a href="ident?i=skb_checksum_init_zero_check">skb_checksum_init_zero_check</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=proto">proto</a>, uh-&gt;<a href="ident?i=check">check</a>,
<a name="L1735" href="source/net/ipv4/udp.c#L1735">1735</a>                                             <a href="ident?i=inet_compute_pseudo">inet_compute_pseudo</a>);
<a name="L1736" href="source/net/ipv4/udp.c#L1736">1736</a> }
<a name="L1737" href="source/net/ipv4/udp.c#L1737">1737</a> 
<a name="L1738" href="source/net/ipv4/udp.c#L1738">1738</a> <b><i>/*</i></b>
<a name="L1739" href="source/net/ipv4/udp.c#L1739">1739</a> <b><i> *      All we need to do is get the socket, and then do a checksum.</i></b>
<a name="L1740" href="source/net/ipv4/udp.c#L1740">1740</a> <b><i> */</i></b>
<a name="L1741" href="source/net/ipv4/udp.c#L1741">1741</a> 
<a name="L1742" href="source/net/ipv4/udp.c#L1742">1742</a> int <a href="ident?i=__udp4_lib_rcv">__udp4_lib_rcv</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, struct <a href="ident?i=udp_table">udp_table</a> *udptable,
<a name="L1743" href="source/net/ipv4/udp.c#L1743">1743</a>                    int <a href="ident?i=proto">proto</a>)
<a name="L1744" href="source/net/ipv4/udp.c#L1744">1744</a> {
<a name="L1745" href="source/net/ipv4/udp.c#L1745">1745</a>         struct <a href="ident?i=sock">sock</a> *sk;
<a name="L1746" href="source/net/ipv4/udp.c#L1746">1746</a>         struct <a href="ident?i=udphdr">udphdr</a> *uh;
<a name="L1747" href="source/net/ipv4/udp.c#L1747">1747</a>         unsigned short ulen;
<a name="L1748" href="source/net/ipv4/udp.c#L1748">1748</a>         struct <a href="ident?i=rtable">rtable</a> *<a href="ident?i=rt">rt</a> = <a href="ident?i=skb_rtable">skb_rtable</a>(<a href="ident?i=skb">skb</a>);
<a name="L1749" href="source/net/ipv4/udp.c#L1749">1749</a>         <a href="ident?i=__be32">__be32</a> <a href="ident?i=saddr">saddr</a>, <a href="ident?i=daddr">daddr</a>;
<a name="L1750" href="source/net/ipv4/udp.c#L1750">1750</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=dev">dev</a>);
<a name="L1751" href="source/net/ipv4/udp.c#L1751">1751</a> 
<a name="L1752" href="source/net/ipv4/udp.c#L1752">1752</a>         <b><i>/*</i></b>
<a name="L1753" href="source/net/ipv4/udp.c#L1753">1753</a> <b><i>         *  Validate the packet.</i></b>
<a name="L1754" href="source/net/ipv4/udp.c#L1754">1754</a> <b><i>         */</i></b>
<a name="L1755" href="source/net/ipv4/udp.c#L1755">1755</a>         if (!<a href="ident?i=pskb_may_pull">pskb_may_pull</a>(<a href="ident?i=skb">skb</a>, sizeof(struct <a href="ident?i=udphdr">udphdr</a>)))
<a name="L1756" href="source/net/ipv4/udp.c#L1756">1756</a>                 goto <a href="ident?i=drop">drop</a>;              <b><i>/* No space for header. */</i></b>
<a name="L1757" href="source/net/ipv4/udp.c#L1757">1757</a> 
<a name="L1758" href="source/net/ipv4/udp.c#L1758">1758</a>         uh   = <a href="ident?i=udp_hdr">udp_hdr</a>(<a href="ident?i=skb">skb</a>);
<a name="L1759" href="source/net/ipv4/udp.c#L1759">1759</a>         ulen = <a href="ident?i=ntohs">ntohs</a>(uh-&gt;<a href="ident?i=len">len</a>);
<a name="L1760" href="source/net/ipv4/udp.c#L1760">1760</a>         <a href="ident?i=saddr">saddr</a> = <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=saddr">saddr</a>;
<a name="L1761" href="source/net/ipv4/udp.c#L1761">1761</a>         <a href="ident?i=daddr">daddr</a> = <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=daddr">daddr</a>;
<a name="L1762" href="source/net/ipv4/udp.c#L1762">1762</a> 
<a name="L1763" href="source/net/ipv4/udp.c#L1763">1763</a>         if (ulen &gt; <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a>)
<a name="L1764" href="source/net/ipv4/udp.c#L1764">1764</a>                 goto short_packet;
<a name="L1765" href="source/net/ipv4/udp.c#L1765">1765</a> 
<a name="L1766" href="source/net/ipv4/udp.c#L1766">1766</a>         if (<a href="ident?i=proto">proto</a> == <a href="ident?i=IPPROTO_UDP">IPPROTO_UDP</a>) {
<a name="L1767" href="source/net/ipv4/udp.c#L1767">1767</a>                 <b><i>/* UDP validates ulen. */</i></b>
<a name="L1768" href="source/net/ipv4/udp.c#L1768">1768</a>                 if (ulen &lt; sizeof(*uh) || <a href="ident?i=pskb_trim_rcsum">pskb_trim_rcsum</a>(<a href="ident?i=skb">skb</a>, ulen))
<a name="L1769" href="source/net/ipv4/udp.c#L1769">1769</a>                         goto short_packet;
<a name="L1770" href="source/net/ipv4/udp.c#L1770">1770</a>                 uh = <a href="ident?i=udp_hdr">udp_hdr</a>(<a href="ident?i=skb">skb</a>);
<a name="L1771" href="source/net/ipv4/udp.c#L1771">1771</a>         }
<a name="L1772" href="source/net/ipv4/udp.c#L1772">1772</a> 
<a name="L1773" href="source/net/ipv4/udp.c#L1773">1773</a>         if (<a href="ident?i=udp4_csum_init">udp4_csum_init</a>(<a href="ident?i=skb">skb</a>, uh, <a href="ident?i=proto">proto</a>))
<a name="L1774" href="source/net/ipv4/udp.c#L1774">1774</a>                 goto csum_error;
<a name="L1775" href="source/net/ipv4/udp.c#L1775">1775</a> 
<a name="L1776" href="source/net/ipv4/udp.c#L1776">1776</a>         sk = <a href="ident?i=skb_steal_sock">skb_steal_sock</a>(<a href="ident?i=skb">skb</a>);
<a name="L1777" href="source/net/ipv4/udp.c#L1777">1777</a>         if (sk) {
<a name="L1778" href="source/net/ipv4/udp.c#L1778">1778</a>                 struct <a href="ident?i=dst_entry">dst_entry</a> *<a href="ident?i=dst">dst</a> = <a href="ident?i=skb_dst">skb_dst</a>(<a href="ident?i=skb">skb</a>);
<a name="L1779" href="source/net/ipv4/udp.c#L1779">1779</a>                 int <a href="ident?i=ret">ret</a>;
<a name="L1780" href="source/net/ipv4/udp.c#L1780">1780</a> 
<a name="L1781" href="source/net/ipv4/udp.c#L1781">1781</a>                 if (<a href="ident?i=unlikely">unlikely</a>(sk-&gt;sk_rx_dst != <a href="ident?i=dst">dst</a>))
<a name="L1782" href="source/net/ipv4/udp.c#L1782">1782</a>                         <a href="ident?i=udp_sk_rx_dst_set">udp_sk_rx_dst_set</a>(sk, <a href="ident?i=dst">dst</a>);
<a name="L1783" href="source/net/ipv4/udp.c#L1783">1783</a> 
<a name="L1784" href="source/net/ipv4/udp.c#L1784">1784</a>                 <a href="ident?i=ret">ret</a> = <a href="ident?i=udp_queue_rcv_skb">udp_queue_rcv_skb</a>(sk, <a href="ident?i=skb">skb</a>);
<a name="L1785" href="source/net/ipv4/udp.c#L1785">1785</a>                 <a href="ident?i=sock_put">sock_put</a>(sk);
<a name="L1786" href="source/net/ipv4/udp.c#L1786">1786</a>                 <b><i>/* a return value &gt; 0 means to resubmit the input, but</i></b>
<a name="L1787" href="source/net/ipv4/udp.c#L1787">1787</a> <b><i>                 * it wants the return to be -protocol, or 0</i></b>
<a name="L1788" href="source/net/ipv4/udp.c#L1788">1788</a> <b><i>                 */</i></b>
<a name="L1789" href="source/net/ipv4/udp.c#L1789">1789</a>                 if (<a href="ident?i=ret">ret</a> &gt; 0)
<a name="L1790" href="source/net/ipv4/udp.c#L1790">1790</a>                         return -<a href="ident?i=ret">ret</a>;
<a name="L1791" href="source/net/ipv4/udp.c#L1791">1791</a>                 return 0;
<a name="L1792" href="source/net/ipv4/udp.c#L1792">1792</a>         }
<a name="L1793" href="source/net/ipv4/udp.c#L1793">1793</a> 
<a name="L1794" href="source/net/ipv4/udp.c#L1794">1794</a>         if (<a href="ident?i=rt">rt</a>-&gt;rt_flags &amp; (<a href="ident?i=RTCF_BROADCAST">RTCF_BROADCAST</a>|<a href="ident?i=RTCF_MULTICAST">RTCF_MULTICAST</a>))
<a name="L1795" href="source/net/ipv4/udp.c#L1795">1795</a>                 return <a href="ident?i=__udp4_lib_mcast_deliver">__udp4_lib_mcast_deliver</a>(<a href="ident?i=net">net</a>, <a href="ident?i=skb">skb</a>, uh,
<a name="L1796" href="source/net/ipv4/udp.c#L1796">1796</a>                                                 <a href="ident?i=saddr">saddr</a>, <a href="ident?i=daddr">daddr</a>, udptable, <a href="ident?i=proto">proto</a>);
<a name="L1797" href="source/net/ipv4/udp.c#L1797">1797</a> 
<a name="L1798" href="source/net/ipv4/udp.c#L1798">1798</a>         sk = <a href="ident?i=__udp4_lib_lookup_skb">__udp4_lib_lookup_skb</a>(<a href="ident?i=skb">skb</a>, uh-&gt;source, uh-&gt;<a href="ident?i=dest">dest</a>, udptable);
<a name="L1799" href="source/net/ipv4/udp.c#L1799">1799</a>         if (sk) {
<a name="L1800" href="source/net/ipv4/udp.c#L1800">1800</a>                 int <a href="ident?i=ret">ret</a>;
<a name="L1801" href="source/net/ipv4/udp.c#L1801">1801</a> 
<a name="L1802" href="source/net/ipv4/udp.c#L1802">1802</a>                 if (<a href="ident?i=inet_get_convert_csum">inet_get_convert_csum</a>(sk) &amp;&amp; uh-&gt;<a href="ident?i=check">check</a> &amp;&amp; !<a href="ident?i=IS_UDPLITE">IS_UDPLITE</a>(sk))
<a name="L1803" href="source/net/ipv4/udp.c#L1803">1803</a>                         <a href="ident?i=skb_checksum_try_convert">skb_checksum_try_convert</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=IPPROTO_UDP">IPPROTO_UDP</a>, uh-&gt;<a href="ident?i=check">check</a>,
<a name="L1804" href="source/net/ipv4/udp.c#L1804">1804</a>                                                  <a href="ident?i=inet_compute_pseudo">inet_compute_pseudo</a>);
<a name="L1805" href="source/net/ipv4/udp.c#L1805">1805</a> 
<a name="L1806" href="source/net/ipv4/udp.c#L1806">1806</a>                 <a href="ident?i=ret">ret</a> = <a href="ident?i=udp_queue_rcv_skb">udp_queue_rcv_skb</a>(sk, <a href="ident?i=skb">skb</a>);
<a name="L1807" href="source/net/ipv4/udp.c#L1807">1807</a>                 <a href="ident?i=sock_put">sock_put</a>(sk);
<a name="L1808" href="source/net/ipv4/udp.c#L1808">1808</a> 
<a name="L1809" href="source/net/ipv4/udp.c#L1809">1809</a>                 <b><i>/* a return value &gt; 0 means to resubmit the input, but</i></b>
<a name="L1810" href="source/net/ipv4/udp.c#L1810">1810</a> <b><i>                 * it wants the return to be -protocol, or 0</i></b>
<a name="L1811" href="source/net/ipv4/udp.c#L1811">1811</a> <b><i>                 */</i></b>
<a name="L1812" href="source/net/ipv4/udp.c#L1812">1812</a>                 if (<a href="ident?i=ret">ret</a> &gt; 0)
<a name="L1813" href="source/net/ipv4/udp.c#L1813">1813</a>                         return -<a href="ident?i=ret">ret</a>;
<a name="L1814" href="source/net/ipv4/udp.c#L1814">1814</a>                 return 0;
<a name="L1815" href="source/net/ipv4/udp.c#L1815">1815</a>         }
<a name="L1816" href="source/net/ipv4/udp.c#L1816">1816</a> 
<a name="L1817" href="source/net/ipv4/udp.c#L1817">1817</a>         if (!<a href="ident?i=xfrm4_policy_check">xfrm4_policy_check</a>(<a href="ident?i=NULL">NULL</a>, XFRM_POLICY_IN, <a href="ident?i=skb">skb</a>))
<a name="L1818" href="source/net/ipv4/udp.c#L1818">1818</a>                 goto <a href="ident?i=drop">drop</a>;
<a name="L1819" href="source/net/ipv4/udp.c#L1819">1819</a>         <a href="ident?i=nf_reset">nf_reset</a>(<a href="ident?i=skb">skb</a>);
<a name="L1820" href="source/net/ipv4/udp.c#L1820">1820</a> 
<a name="L1821" href="source/net/ipv4/udp.c#L1821">1821</a>         <b><i>/* No socket. Drop packet silently, if checksum is wrong */</i></b>
<a name="L1822" href="source/net/ipv4/udp.c#L1822">1822</a>         if (<a href="ident?i=udp_lib_checksum_complete">udp_lib_checksum_complete</a>(<a href="ident?i=skb">skb</a>))
<a name="L1823" href="source/net/ipv4/udp.c#L1823">1823</a>                 goto csum_error;
<a name="L1824" href="source/net/ipv4/udp.c#L1824">1824</a> 
<a name="L1825" href="source/net/ipv4/udp.c#L1825">1825</a>         <a href="ident?i=UDP_INC_STATS_BH">UDP_INC_STATS_BH</a>(<a href="ident?i=net">net</a>, UDP_MIB_NOPORTS, <a href="ident?i=proto">proto</a> == <a href="ident?i=IPPROTO_UDPLITE">IPPROTO_UDPLITE</a>);
<a name="L1826" href="source/net/ipv4/udp.c#L1826">1826</a>         <a href="ident?i=icmp_send">icmp_send</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=ICMP_DEST_UNREACH">ICMP_DEST_UNREACH</a>, <a href="ident?i=ICMP_PORT_UNREACH">ICMP_PORT_UNREACH</a>, 0);
<a name="L1827" href="source/net/ipv4/udp.c#L1827">1827</a> 
<a name="L1828" href="source/net/ipv4/udp.c#L1828">1828</a>         <b><i>/*</i></b>
<a name="L1829" href="source/net/ipv4/udp.c#L1829">1829</a> <b><i>         * Hmm.  We got an UDP packet to a port to which we</i></b>
<a name="L1830" href="source/net/ipv4/udp.c#L1830">1830</a> <b><i>         * don't wanna listen.  Ignore it.</i></b>
<a name="L1831" href="source/net/ipv4/udp.c#L1831">1831</a> <b><i>         */</i></b>
<a name="L1832" href="source/net/ipv4/udp.c#L1832">1832</a>         <a href="ident?i=kfree_skb">kfree_skb</a>(<a href="ident?i=skb">skb</a>);
<a name="L1833" href="source/net/ipv4/udp.c#L1833">1833</a>         return 0;
<a name="L1834" href="source/net/ipv4/udp.c#L1834">1834</a> 
<a name="L1835" href="source/net/ipv4/udp.c#L1835">1835</a> short_packet:
<a name="L1836" href="source/net/ipv4/udp.c#L1836">1836</a>         <a href="ident?i=net_dbg_ratelimited">net_dbg_ratelimited</a>(<i>"UDP%s: short packet: From %pI4:%u %d/%d to %pI4:%u\n"</i>,
<a name="L1837" href="source/net/ipv4/udp.c#L1837">1837</a>                             <a href="ident?i=proto">proto</a> == <a href="ident?i=IPPROTO_UDPLITE">IPPROTO_UDPLITE</a> ? <i>"Lite"</i> : <i>""</i>,
<a name="L1838" href="source/net/ipv4/udp.c#L1838">1838</a>                             &amp;<a href="ident?i=saddr">saddr</a>, <a href="ident?i=ntohs">ntohs</a>(uh-&gt;source),
<a name="L1839" href="source/net/ipv4/udp.c#L1839">1839</a>                             ulen, <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a>,
<a name="L1840" href="source/net/ipv4/udp.c#L1840">1840</a>                             &amp;<a href="ident?i=daddr">daddr</a>, <a href="ident?i=ntohs">ntohs</a>(uh-&gt;<a href="ident?i=dest">dest</a>));
<a name="L1841" href="source/net/ipv4/udp.c#L1841">1841</a>         goto <a href="ident?i=drop">drop</a>;
<a name="L1842" href="source/net/ipv4/udp.c#L1842">1842</a> 
<a name="L1843" href="source/net/ipv4/udp.c#L1843">1843</a> csum_error:
<a name="L1844" href="source/net/ipv4/udp.c#L1844">1844</a>         <b><i>/*</i></b>
<a name="L1845" href="source/net/ipv4/udp.c#L1845">1845</a> <b><i>         * RFC1122: OK.  Discards the bad packet silently (as far as</i></b>
<a name="L1846" href="source/net/ipv4/udp.c#L1846">1846</a> <b><i>         * the network is concerned, anyway) as per 4.1.3.4 (MUST).</i></b>
<a name="L1847" href="source/net/ipv4/udp.c#L1847">1847</a> <b><i>         */</i></b>
<a name="L1848" href="source/net/ipv4/udp.c#L1848">1848</a>         <a href="ident?i=net_dbg_ratelimited">net_dbg_ratelimited</a>(<i>"UDP%s: bad checksum. From %pI4:%u to %pI4:%u ulen %d\n"</i>,
<a name="L1849" href="source/net/ipv4/udp.c#L1849">1849</a>                             <a href="ident?i=proto">proto</a> == <a href="ident?i=IPPROTO_UDPLITE">IPPROTO_UDPLITE</a> ? <i>"Lite"</i> : <i>""</i>,
<a name="L1850" href="source/net/ipv4/udp.c#L1850">1850</a>                             &amp;<a href="ident?i=saddr">saddr</a>, <a href="ident?i=ntohs">ntohs</a>(uh-&gt;source), &amp;<a href="ident?i=daddr">daddr</a>, <a href="ident?i=ntohs">ntohs</a>(uh-&gt;<a href="ident?i=dest">dest</a>),
<a name="L1851" href="source/net/ipv4/udp.c#L1851">1851</a>                             ulen);
<a name="L1852" href="source/net/ipv4/udp.c#L1852">1852</a>         <a href="ident?i=UDP_INC_STATS_BH">UDP_INC_STATS_BH</a>(<a href="ident?i=net">net</a>, UDP_MIB_CSUMERRORS, <a href="ident?i=proto">proto</a> == <a href="ident?i=IPPROTO_UDPLITE">IPPROTO_UDPLITE</a>);
<a name="L1853" href="source/net/ipv4/udp.c#L1853">1853</a> <a href="ident?i=drop">drop</a>:
<a name="L1854" href="source/net/ipv4/udp.c#L1854">1854</a>         <a href="ident?i=UDP_INC_STATS_BH">UDP_INC_STATS_BH</a>(<a href="ident?i=net">net</a>, UDP_MIB_INERRORS, <a href="ident?i=proto">proto</a> == <a href="ident?i=IPPROTO_UDPLITE">IPPROTO_UDPLITE</a>);
<a name="L1855" href="source/net/ipv4/udp.c#L1855">1855</a>         <a href="ident?i=kfree_skb">kfree_skb</a>(<a href="ident?i=skb">skb</a>);
<a name="L1856" href="source/net/ipv4/udp.c#L1856">1856</a>         return 0;
<a name="L1857" href="source/net/ipv4/udp.c#L1857">1857</a> }
<a name="L1858" href="source/net/ipv4/udp.c#L1858">1858</a> 
<a name="L1859" href="source/net/ipv4/udp.c#L1859">1859</a> <b><i>/* We can only early demux multicast if there is a single matching socket.</i></b>
<a name="L1860" href="source/net/ipv4/udp.c#L1860">1860</a> <b><i> * If more than one socket found returns NULL</i></b>
<a name="L1861" href="source/net/ipv4/udp.c#L1861">1861</a> <b><i> */</i></b>
<a name="L1862" href="source/net/ipv4/udp.c#L1862">1862</a> static struct <a href="ident?i=sock">sock</a> *<a href="ident?i=__udp4_lib_mcast_demux_lookup">__udp4_lib_mcast_demux_lookup</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>,
<a name="L1863" href="source/net/ipv4/udp.c#L1863">1863</a>                                                   <a href="ident?i=__be16">__be16</a> loc_port, <a href="ident?i=__be32">__be32</a> loc_addr,
<a name="L1864" href="source/net/ipv4/udp.c#L1864">1864</a>                                                   <a href="ident?i=__be16">__be16</a> rmt_port, <a href="ident?i=__be32">__be32</a> rmt_addr,
<a name="L1865" href="source/net/ipv4/udp.c#L1865">1865</a>                                                   int dif)
<a name="L1866" href="source/net/ipv4/udp.c#L1866">1866</a> {
<a name="L1867" href="source/net/ipv4/udp.c#L1867">1867</a>         struct <a href="ident?i=sock">sock</a> *sk, *<a href="ident?i=result">result</a>;
<a name="L1868" href="source/net/ipv4/udp.c#L1868">1868</a>         struct <a href="ident?i=hlist_nulls_node">hlist_nulls_node</a> *<a href="ident?i=node">node</a>;
<a name="L1869" href="source/net/ipv4/udp.c#L1869">1869</a>         unsigned short hnum = <a href="ident?i=ntohs">ntohs</a>(loc_port);
<a name="L1870" href="source/net/ipv4/udp.c#L1870">1870</a>         unsigned int <a href="ident?i=count">count</a>, <a href="ident?i=slot">slot</a> = <a href="ident?i=udp_hashfn">udp_hashfn</a>(<a href="ident?i=net">net</a>, hnum, <a href="ident?i=udp_table">udp_table</a>.<a href="ident?i=mask">mask</a>);
<a name="L1871" href="source/net/ipv4/udp.c#L1871">1871</a>         struct <a href="ident?i=udp_hslot">udp_hslot</a> *hslot = &amp;<a href="ident?i=udp_table">udp_table</a>.<a href="ident?i=hash">hash</a>[<a href="ident?i=slot">slot</a>];
<a name="L1872" href="source/net/ipv4/udp.c#L1872">1872</a> 
<a name="L1873" href="source/net/ipv4/udp.c#L1873">1873</a>         <b><i>/* Do not bother scanning a too big list */</i></b>
<a name="L1874" href="source/net/ipv4/udp.c#L1874">1874</a>         if (hslot-&gt;<a href="ident?i=count">count</a> &gt; 10)
<a name="L1875" href="source/net/ipv4/udp.c#L1875">1875</a>                 return <a href="ident?i=NULL">NULL</a>;
<a name="L1876" href="source/net/ipv4/udp.c#L1876">1876</a> 
<a name="L1877" href="source/net/ipv4/udp.c#L1877">1877</a>         <a href="ident?i=rcu_read_lock">rcu_read_lock</a>();
<a name="L1878" href="source/net/ipv4/udp.c#L1878">1878</a> begin:
<a name="L1879" href="source/net/ipv4/udp.c#L1879">1879</a>         <a href="ident?i=count">count</a> = 0;
<a name="L1880" href="source/net/ipv4/udp.c#L1880">1880</a>         <a href="ident?i=result">result</a> = <a href="ident?i=NULL">NULL</a>;
<a name="L1881" href="source/net/ipv4/udp.c#L1881">1881</a>         <a href="ident?i=sk_nulls_for_each_rcu">sk_nulls_for_each_rcu</a>(sk, <a href="ident?i=node">node</a>, &amp;hslot-&gt;<a href="ident?i=head">head</a>) {
<a name="L1882" href="source/net/ipv4/udp.c#L1882">1882</a>                 if (<a href="ident?i=__udp_is_mcast_sock">__udp_is_mcast_sock</a>(<a href="ident?i=net">net</a>, sk,
<a name="L1883" href="source/net/ipv4/udp.c#L1883">1883</a>                                         loc_port, loc_addr,
<a name="L1884" href="source/net/ipv4/udp.c#L1884">1884</a>                                         rmt_port, rmt_addr,
<a name="L1885" href="source/net/ipv4/udp.c#L1885">1885</a>                                         dif, hnum)) {
<a name="L1886" href="source/net/ipv4/udp.c#L1886">1886</a>                         <a href="ident?i=result">result</a> = sk;
<a name="L1887" href="source/net/ipv4/udp.c#L1887">1887</a>                         ++<a href="ident?i=count">count</a>;
<a name="L1888" href="source/net/ipv4/udp.c#L1888">1888</a>                 }
<a name="L1889" href="source/net/ipv4/udp.c#L1889">1889</a>         }
<a name="L1890" href="source/net/ipv4/udp.c#L1890">1890</a>         <b><i>/*</i></b>
<a name="L1891" href="source/net/ipv4/udp.c#L1891">1891</a> <b><i>         * if the nulls value we got at the end of this lookup is</i></b>
<a name="L1892" href="source/net/ipv4/udp.c#L1892">1892</a> <b><i>         * not the expected one, we must restart lookup.</i></b>
<a name="L1893" href="source/net/ipv4/udp.c#L1893">1893</a> <b><i>         * We probably met an item that was moved to another chain.</i></b>
<a name="L1894" href="source/net/ipv4/udp.c#L1894">1894</a> <b><i>         */</i></b>
<a name="L1895" href="source/net/ipv4/udp.c#L1895">1895</a>         if (<a href="ident?i=get_nulls_value">get_nulls_value</a>(<a href="ident?i=node">node</a>) != <a href="ident?i=slot">slot</a>)
<a name="L1896" href="source/net/ipv4/udp.c#L1896">1896</a>                 goto begin;
<a name="L1897" href="source/net/ipv4/udp.c#L1897">1897</a> 
<a name="L1898" href="source/net/ipv4/udp.c#L1898">1898</a>         if (<a href="ident?i=result">result</a>) {
<a name="L1899" href="source/net/ipv4/udp.c#L1899">1899</a>                 if (<a href="ident?i=count">count</a> != 1 ||
<a name="L1900" href="source/net/ipv4/udp.c#L1900">1900</a>                     <a href="ident?i=unlikely">unlikely</a>(!<a href="ident?i=atomic_inc_not_zero_hint">atomic_inc_not_zero_hint</a>(&amp;<a href="ident?i=result">result</a>-&gt;<a href="ident?i=sk_refcnt">sk_refcnt</a>, 2)))
<a name="L1901" href="source/net/ipv4/udp.c#L1901">1901</a>                         <a href="ident?i=result">result</a> = <a href="ident?i=NULL">NULL</a>;
<a name="L1902" href="source/net/ipv4/udp.c#L1902">1902</a>                 else if (<a href="ident?i=unlikely">unlikely</a>(!<a href="ident?i=__udp_is_mcast_sock">__udp_is_mcast_sock</a>(<a href="ident?i=net">net</a>, <a href="ident?i=result">result</a>,
<a name="L1903" href="source/net/ipv4/udp.c#L1903">1903</a>                                                        loc_port, loc_addr,
<a name="L1904" href="source/net/ipv4/udp.c#L1904">1904</a>                                                        rmt_port, rmt_addr,
<a name="L1905" href="source/net/ipv4/udp.c#L1905">1905</a>                                                        dif, hnum))) {
<a name="L1906" href="source/net/ipv4/udp.c#L1906">1906</a>                         <a href="ident?i=sock_put">sock_put</a>(<a href="ident?i=result">result</a>);
<a name="L1907" href="source/net/ipv4/udp.c#L1907">1907</a>                         <a href="ident?i=result">result</a> = <a href="ident?i=NULL">NULL</a>;
<a name="L1908" href="source/net/ipv4/udp.c#L1908">1908</a>                 }
<a name="L1909" href="source/net/ipv4/udp.c#L1909">1909</a>         }
<a name="L1910" href="source/net/ipv4/udp.c#L1910">1910</a>         <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L1911" href="source/net/ipv4/udp.c#L1911">1911</a>         return <a href="ident?i=result">result</a>;
<a name="L1912" href="source/net/ipv4/udp.c#L1912">1912</a> }
<a name="L1913" href="source/net/ipv4/udp.c#L1913">1913</a> 
<a name="L1914" href="source/net/ipv4/udp.c#L1914">1914</a> <b><i>/* For unicast we should only early demux connected sockets or we can</i></b>
<a name="L1915" href="source/net/ipv4/udp.c#L1915">1915</a> <b><i> * break forwarding setups.  The chains here can be long so only check</i></b>
<a name="L1916" href="source/net/ipv4/udp.c#L1916">1916</a> <b><i> * if the first socket is an exact match and if not move on.</i></b>
<a name="L1917" href="source/net/ipv4/udp.c#L1917">1917</a> <b><i> */</i></b>
<a name="L1918" href="source/net/ipv4/udp.c#L1918">1918</a> static struct <a href="ident?i=sock">sock</a> *<a href="ident?i=__udp4_lib_demux_lookup">__udp4_lib_demux_lookup</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>,
<a name="L1919" href="source/net/ipv4/udp.c#L1919">1919</a>                                             <a href="ident?i=__be16">__be16</a> loc_port, <a href="ident?i=__be32">__be32</a> loc_addr,
<a name="L1920" href="source/net/ipv4/udp.c#L1920">1920</a>                                             <a href="ident?i=__be16">__be16</a> rmt_port, <a href="ident?i=__be32">__be32</a> rmt_addr,
<a name="L1921" href="source/net/ipv4/udp.c#L1921">1921</a>                                             int dif)
<a name="L1922" href="source/net/ipv4/udp.c#L1922">1922</a> {
<a name="L1923" href="source/net/ipv4/udp.c#L1923">1923</a>         struct <a href="ident?i=sock">sock</a> *sk, *<a href="ident?i=result">result</a>;
<a name="L1924" href="source/net/ipv4/udp.c#L1924">1924</a>         struct <a href="ident?i=hlist_nulls_node">hlist_nulls_node</a> *<a href="ident?i=node">node</a>;
<a name="L1925" href="source/net/ipv4/udp.c#L1925">1925</a>         unsigned short hnum = <a href="ident?i=ntohs">ntohs</a>(loc_port);
<a name="L1926" href="source/net/ipv4/udp.c#L1926">1926</a>         unsigned int hash2 = <a href="ident?i=udp4_portaddr_hash">udp4_portaddr_hash</a>(<a href="ident?i=net">net</a>, loc_addr, hnum);
<a name="L1927" href="source/net/ipv4/udp.c#L1927">1927</a>         unsigned int slot2 = hash2 &amp; <a href="ident?i=udp_table">udp_table</a>.<a href="ident?i=mask">mask</a>;
<a name="L1928" href="source/net/ipv4/udp.c#L1928">1928</a>         struct <a href="ident?i=udp_hslot">udp_hslot</a> *hslot2 = &amp;<a href="ident?i=udp_table">udp_table</a>.hash2[slot2];
<a name="L1929" href="source/net/ipv4/udp.c#L1929">1929</a>         <a href="ident?i=INET_ADDR_COOKIE">INET_ADDR_COOKIE</a>(acookie, rmt_addr, loc_addr);
<a name="L1930" href="source/net/ipv4/udp.c#L1930">1930</a>         const <a href="ident?i=__portpair">__portpair</a> <a href="ident?i=ports">ports</a> = <a href="ident?i=INET_COMBINED_PORTS">INET_COMBINED_PORTS</a>(rmt_port, hnum);
<a name="L1931" href="source/net/ipv4/udp.c#L1931">1931</a> 
<a name="L1932" href="source/net/ipv4/udp.c#L1932">1932</a>         <a href="ident?i=rcu_read_lock">rcu_read_lock</a>();
<a name="L1933" href="source/net/ipv4/udp.c#L1933">1933</a>         <a href="ident?i=result">result</a> = <a href="ident?i=NULL">NULL</a>;
<a name="L1934" href="source/net/ipv4/udp.c#L1934">1934</a>         <a href="ident?i=udp_portaddr_for_each_entry_rcu">udp_portaddr_for_each_entry_rcu</a>(sk, <a href="ident?i=node">node</a>, &amp;hslot2-&gt;<a href="ident?i=head">head</a>) {
<a name="L1935" href="source/net/ipv4/udp.c#L1935">1935</a>                 if (<a href="ident?i=INET_MATCH">INET_MATCH</a>(sk, <a href="ident?i=net">net</a>, acookie,
<a name="L1936" href="source/net/ipv4/udp.c#L1936">1936</a>                                rmt_addr, loc_addr, <a href="ident?i=ports">ports</a>, dif))
<a name="L1937" href="source/net/ipv4/udp.c#L1937">1937</a>                         <a href="ident?i=result">result</a> = sk;
<a name="L1938" href="source/net/ipv4/udp.c#L1938">1938</a>                 <b><i>/* Only check first socket in chain */</i></b>
<a name="L1939" href="source/net/ipv4/udp.c#L1939">1939</a>                 break;
<a name="L1940" href="source/net/ipv4/udp.c#L1940">1940</a>         }
<a name="L1941" href="source/net/ipv4/udp.c#L1941">1941</a> 
<a name="L1942" href="source/net/ipv4/udp.c#L1942">1942</a>         if (<a href="ident?i=result">result</a>) {
<a name="L1943" href="source/net/ipv4/udp.c#L1943">1943</a>                 if (<a href="ident?i=unlikely">unlikely</a>(!<a href="ident?i=atomic_inc_not_zero_hint">atomic_inc_not_zero_hint</a>(&amp;<a href="ident?i=result">result</a>-&gt;<a href="ident?i=sk_refcnt">sk_refcnt</a>, 2)))
<a name="L1944" href="source/net/ipv4/udp.c#L1944">1944</a>                         <a href="ident?i=result">result</a> = <a href="ident?i=NULL">NULL</a>;
<a name="L1945" href="source/net/ipv4/udp.c#L1945">1945</a>                 else if (<a href="ident?i=unlikely">unlikely</a>(!<a href="ident?i=INET_MATCH">INET_MATCH</a>(sk, <a href="ident?i=net">net</a>, acookie,
<a name="L1946" href="source/net/ipv4/udp.c#L1946">1946</a>                                               rmt_addr, loc_addr,
<a name="L1947" href="source/net/ipv4/udp.c#L1947">1947</a>                                               <a href="ident?i=ports">ports</a>, dif))) {
<a name="L1948" href="source/net/ipv4/udp.c#L1948">1948</a>                         <a href="ident?i=sock_put">sock_put</a>(<a href="ident?i=result">result</a>);
<a name="L1949" href="source/net/ipv4/udp.c#L1949">1949</a>                         <a href="ident?i=result">result</a> = <a href="ident?i=NULL">NULL</a>;
<a name="L1950" href="source/net/ipv4/udp.c#L1950">1950</a>                 }
<a name="L1951" href="source/net/ipv4/udp.c#L1951">1951</a>         }
<a name="L1952" href="source/net/ipv4/udp.c#L1952">1952</a>         <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L1953" href="source/net/ipv4/udp.c#L1953">1953</a>         return <a href="ident?i=result">result</a>;
<a name="L1954" href="source/net/ipv4/udp.c#L1954">1954</a> }
<a name="L1955" href="source/net/ipv4/udp.c#L1955">1955</a> 
<a name="L1956" href="source/net/ipv4/udp.c#L1956">1956</a> void <a href="ident?i=udp_v4_early_demux">udp_v4_early_demux</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L1957" href="source/net/ipv4/udp.c#L1957">1957</a> {
<a name="L1958" href="source/net/ipv4/udp.c#L1958">1958</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=dev">dev</a>);
<a name="L1959" href="source/net/ipv4/udp.c#L1959">1959</a>         const struct <a href="ident?i=iphdr">iphdr</a> *iph;
<a name="L1960" href="source/net/ipv4/udp.c#L1960">1960</a>         const struct <a href="ident?i=udphdr">udphdr</a> *uh;
<a name="L1961" href="source/net/ipv4/udp.c#L1961">1961</a>         struct <a href="ident?i=sock">sock</a> *sk;
<a name="L1962" href="source/net/ipv4/udp.c#L1962">1962</a>         struct <a href="ident?i=dst_entry">dst_entry</a> *<a href="ident?i=dst">dst</a>;
<a name="L1963" href="source/net/ipv4/udp.c#L1963">1963</a>         int dif = <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=dev">dev</a>-&gt;ifindex;
<a name="L1964" href="source/net/ipv4/udp.c#L1964">1964</a>         int ours;
<a name="L1965" href="source/net/ipv4/udp.c#L1965">1965</a> 
<a name="L1966" href="source/net/ipv4/udp.c#L1966">1966</a>         <b><i>/* validate the packet */</i></b>
<a name="L1967" href="source/net/ipv4/udp.c#L1967">1967</a>         if (!<a href="ident?i=pskb_may_pull">pskb_may_pull</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=skb_transport_offset">skb_transport_offset</a>(<a href="ident?i=skb">skb</a>) + sizeof(struct <a href="ident?i=udphdr">udphdr</a>)))
<a name="L1968" href="source/net/ipv4/udp.c#L1968">1968</a>                 return;
<a name="L1969" href="source/net/ipv4/udp.c#L1969">1969</a> 
<a name="L1970" href="source/net/ipv4/udp.c#L1970">1970</a>         iph = <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>);
<a name="L1971" href="source/net/ipv4/udp.c#L1971">1971</a>         uh = <a href="ident?i=udp_hdr">udp_hdr</a>(<a href="ident?i=skb">skb</a>);
<a name="L1972" href="source/net/ipv4/udp.c#L1972">1972</a> 
<a name="L1973" href="source/net/ipv4/udp.c#L1973">1973</a>         if (<a href="ident?i=skb">skb</a>-&gt;pkt_type == <a href="ident?i=PACKET_BROADCAST">PACKET_BROADCAST</a> ||
<a name="L1974" href="source/net/ipv4/udp.c#L1974">1974</a>             <a href="ident?i=skb">skb</a>-&gt;pkt_type == <a href="ident?i=PACKET_MULTICAST">PACKET_MULTICAST</a>) {
<a name="L1975" href="source/net/ipv4/udp.c#L1975">1975</a>                 struct <a href="ident?i=in_device">in_device</a> *in_dev = <a href="ident?i=__in_dev_get_rcu">__in_dev_get_rcu</a>(<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=dev">dev</a>);
<a name="L1976" href="source/net/ipv4/udp.c#L1976">1976</a> 
<a name="L1977" href="source/net/ipv4/udp.c#L1977">1977</a>                 if (!in_dev)
<a name="L1978" href="source/net/ipv4/udp.c#L1978">1978</a>                         return;
<a name="L1979" href="source/net/ipv4/udp.c#L1979">1979</a> 
<a name="L1980" href="source/net/ipv4/udp.c#L1980">1980</a>                 ours = <a href="ident?i=ip_check_mc_rcu">ip_check_mc_rcu</a>(in_dev, iph-&gt;<a href="ident?i=daddr">daddr</a>, iph-&gt;<a href="ident?i=saddr">saddr</a>,
<a name="L1981" href="source/net/ipv4/udp.c#L1981">1981</a>                                        iph-&gt;<a href="ident?i=protocol">protocol</a>);
<a name="L1982" href="source/net/ipv4/udp.c#L1982">1982</a>                 if (!ours)
<a name="L1983" href="source/net/ipv4/udp.c#L1983">1983</a>                         return;
<a name="L1984" href="source/net/ipv4/udp.c#L1984">1984</a>                 sk = <a href="ident?i=__udp4_lib_mcast_demux_lookup">__udp4_lib_mcast_demux_lookup</a>(<a href="ident?i=net">net</a>, uh-&gt;<a href="ident?i=dest">dest</a>, iph-&gt;<a href="ident?i=daddr">daddr</a>,
<a name="L1985" href="source/net/ipv4/udp.c#L1985">1985</a>                                                    uh-&gt;source, iph-&gt;<a href="ident?i=saddr">saddr</a>, dif);
<a name="L1986" href="source/net/ipv4/udp.c#L1986">1986</a>         } else if (<a href="ident?i=skb">skb</a>-&gt;pkt_type == <a href="ident?i=PACKET_HOST">PACKET_HOST</a>) {
<a name="L1987" href="source/net/ipv4/udp.c#L1987">1987</a>                 sk = <a href="ident?i=__udp4_lib_demux_lookup">__udp4_lib_demux_lookup</a>(<a href="ident?i=net">net</a>, uh-&gt;<a href="ident?i=dest">dest</a>, iph-&gt;<a href="ident?i=daddr">daddr</a>,
<a name="L1988" href="source/net/ipv4/udp.c#L1988">1988</a>                                              uh-&gt;source, iph-&gt;<a href="ident?i=saddr">saddr</a>, dif);
<a name="L1989" href="source/net/ipv4/udp.c#L1989">1989</a>         } else {
<a name="L1990" href="source/net/ipv4/udp.c#L1990">1990</a>                 return;
<a name="L1991" href="source/net/ipv4/udp.c#L1991">1991</a>         }
<a name="L1992" href="source/net/ipv4/udp.c#L1992">1992</a> 
<a name="L1993" href="source/net/ipv4/udp.c#L1993">1993</a>         if (!sk)
<a name="L1994" href="source/net/ipv4/udp.c#L1994">1994</a>                 return;
<a name="L1995" href="source/net/ipv4/udp.c#L1995">1995</a> 
<a name="L1996" href="source/net/ipv4/udp.c#L1996">1996</a>         <a href="ident?i=skb">skb</a>-&gt;sk = sk;
<a name="L1997" href="source/net/ipv4/udp.c#L1997">1997</a>         <a href="ident?i=skb">skb</a>-&gt;destructor = <a href="ident?i=sock_efree">sock_efree</a>;
<a name="L1998" href="source/net/ipv4/udp.c#L1998">1998</a>         <a href="ident?i=dst">dst</a> = sk-&gt;sk_rx_dst;
<a name="L1999" href="source/net/ipv4/udp.c#L1999">1999</a> 
<a name="L2000" href="source/net/ipv4/udp.c#L2000">2000</a>         if (<a href="ident?i=dst">dst</a>)
<a name="L2001" href="source/net/ipv4/udp.c#L2001">2001</a>                 <a href="ident?i=dst">dst</a> = <a href="ident?i=dst_check">dst_check</a>(<a href="ident?i=dst">dst</a>, 0);
<a name="L2002" href="source/net/ipv4/udp.c#L2002">2002</a>         if (<a href="ident?i=dst">dst</a>)
<a name="L2003" href="source/net/ipv4/udp.c#L2003">2003</a>                 <a href="ident?i=skb_dst_set_noref">skb_dst_set_noref</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=dst">dst</a>);
<a name="L2004" href="source/net/ipv4/udp.c#L2004">2004</a> }
<a name="L2005" href="source/net/ipv4/udp.c#L2005">2005</a> 
<a name="L2006" href="source/net/ipv4/udp.c#L2006">2006</a> int <a href="ident?i=udp_rcv">udp_rcv</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L2007" href="source/net/ipv4/udp.c#L2007">2007</a> {
<a name="L2008" href="source/net/ipv4/udp.c#L2008">2008</a>         return <a href="ident?i=__udp4_lib_rcv">__udp4_lib_rcv</a>(<a href="ident?i=skb">skb</a>, &amp;<a href="ident?i=udp_table">udp_table</a>, <a href="ident?i=IPPROTO_UDP">IPPROTO_UDP</a>);
<a name="L2009" href="source/net/ipv4/udp.c#L2009">2009</a> }
<a name="L2010" href="source/net/ipv4/udp.c#L2010">2010</a> 
<a name="L2011" href="source/net/ipv4/udp.c#L2011">2011</a> void <a href="ident?i=udp_destroy_sock">udp_destroy_sock</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L2012" href="source/net/ipv4/udp.c#L2012">2012</a> {
<a name="L2013" href="source/net/ipv4/udp.c#L2013">2013</a>         struct <a href="ident?i=udp_sock">udp_sock</a> *<a href="ident?i=up">up</a> = <a href="ident?i=udp_sk">udp_sk</a>(sk);
<a name="L2014" href="source/net/ipv4/udp.c#L2014">2014</a>         <a href="ident?i=bool">bool</a> <a href="ident?i=slow">slow</a> = <a href="ident?i=lock_sock_fast">lock_sock_fast</a>(sk);
<a name="L2015" href="source/net/ipv4/udp.c#L2015">2015</a>         <a href="ident?i=udp_flush_pending_frames">udp_flush_pending_frames</a>(sk);
<a name="L2016" href="source/net/ipv4/udp.c#L2016">2016</a>         <a href="ident?i=unlock_sock_fast">unlock_sock_fast</a>(sk, <a href="ident?i=slow">slow</a>);
<a name="L2017" href="source/net/ipv4/udp.c#L2017">2017</a>         if (<a href="ident?i=static_key_false">static_key_false</a>(&amp;udp_encap_needed) &amp;&amp; <a href="ident?i=up">up</a>-&gt;encap_type) {
<a name="L2018" href="source/net/ipv4/udp.c#L2018">2018</a>                 void (*encap_destroy)(struct <a href="ident?i=sock">sock</a> *sk);
<a name="L2019" href="source/net/ipv4/udp.c#L2019">2019</a>                 encap_destroy = <a href="ident?i=ACCESS_ONCE">ACCESS_ONCE</a>(<a href="ident?i=up">up</a>-&gt;encap_destroy);
<a name="L2020" href="source/net/ipv4/udp.c#L2020">2020</a>                 if (encap_destroy)
<a name="L2021" href="source/net/ipv4/udp.c#L2021">2021</a>                         encap_destroy(sk);
<a name="L2022" href="source/net/ipv4/udp.c#L2022">2022</a>         }
<a name="L2023" href="source/net/ipv4/udp.c#L2023">2023</a> }
<a name="L2024" href="source/net/ipv4/udp.c#L2024">2024</a> 
<a name="L2025" href="source/net/ipv4/udp.c#L2025">2025</a> <b><i>/*</i></b>
<a name="L2026" href="source/net/ipv4/udp.c#L2026">2026</a> <b><i> *      Socket option code for UDP</i></b>
<a name="L2027" href="source/net/ipv4/udp.c#L2027">2027</a> <b><i> */</i></b>
<a name="L2028" href="source/net/ipv4/udp.c#L2028">2028</a> int <a href="ident?i=udp_lib_setsockopt">udp_lib_setsockopt</a>(struct <a href="ident?i=sock">sock</a> *sk, int <a href="ident?i=level">level</a>, int optname,
<a name="L2029" href="source/net/ipv4/udp.c#L2029">2029</a>                        char <a href="ident?i=__user">__user</a> *optval, unsigned int <a href="ident?i=optlen">optlen</a>,
<a name="L2030" href="source/net/ipv4/udp.c#L2030">2030</a>                        int (*push_pending_frames)(struct <a href="ident?i=sock">sock</a> *))
<a name="L2031" href="source/net/ipv4/udp.c#L2031">2031</a> {
<a name="L2032" href="source/net/ipv4/udp.c#L2032">2032</a>         struct <a href="ident?i=udp_sock">udp_sock</a> *<a href="ident?i=up">up</a> = <a href="ident?i=udp_sk">udp_sk</a>(sk);
<a name="L2033" href="source/net/ipv4/udp.c#L2033">2033</a>         int <a href="ident?i=val">val</a>, valbool;
<a name="L2034" href="source/net/ipv4/udp.c#L2034">2034</a>         int <a href="ident?i=err">err</a> = 0;
<a name="L2035" href="source/net/ipv4/udp.c#L2035">2035</a>         int is_udplite = <a href="ident?i=IS_UDPLITE">IS_UDPLITE</a>(sk);
<a name="L2036" href="source/net/ipv4/udp.c#L2036">2036</a> 
<a name="L2037" href="source/net/ipv4/udp.c#L2037">2037</a>         if (<a href="ident?i=optlen">optlen</a> &lt; sizeof(int))
<a name="L2038" href="source/net/ipv4/udp.c#L2038">2038</a>                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L2039" href="source/net/ipv4/udp.c#L2039">2039</a> 
<a name="L2040" href="source/net/ipv4/udp.c#L2040">2040</a>         if (<a href="ident?i=get_user">get_user</a>(<a href="ident?i=val">val</a>, (int <a href="ident?i=__user">__user</a> *)optval))
<a name="L2041" href="source/net/ipv4/udp.c#L2041">2041</a>                 return -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L2042" href="source/net/ipv4/udp.c#L2042">2042</a> 
<a name="L2043" href="source/net/ipv4/udp.c#L2043">2043</a>         valbool = <a href="ident?i=val">val</a> ? 1 : 0;
<a name="L2044" href="source/net/ipv4/udp.c#L2044">2044</a> 
<a name="L2045" href="source/net/ipv4/udp.c#L2045">2045</a>         switch (optname) {
<a name="L2046" href="source/net/ipv4/udp.c#L2046">2046</a>         case <a href="ident?i=UDP_CORK">UDP_CORK</a>:
<a name="L2047" href="source/net/ipv4/udp.c#L2047">2047</a>                 if (<a href="ident?i=val">val</a> != 0) {
<a name="L2048" href="source/net/ipv4/udp.c#L2048">2048</a>                         <a href="ident?i=up">up</a>-&gt;corkflag = 1;
<a name="L2049" href="source/net/ipv4/udp.c#L2049">2049</a>                 } else {
<a name="L2050" href="source/net/ipv4/udp.c#L2050">2050</a>                         <a href="ident?i=up">up</a>-&gt;corkflag = 0;
<a name="L2051" href="source/net/ipv4/udp.c#L2051">2051</a>                         <a href="ident?i=lock_sock">lock_sock</a>(sk);
<a name="L2052" href="source/net/ipv4/udp.c#L2052">2052</a>                         push_pending_frames(sk);
<a name="L2053" href="source/net/ipv4/udp.c#L2053">2053</a>                         <a href="ident?i=release_sock">release_sock</a>(sk);
<a name="L2054" href="source/net/ipv4/udp.c#L2054">2054</a>                 }
<a name="L2055" href="source/net/ipv4/udp.c#L2055">2055</a>                 break;
<a name="L2056" href="source/net/ipv4/udp.c#L2056">2056</a> 
<a name="L2057" href="source/net/ipv4/udp.c#L2057">2057</a>         case <a href="ident?i=UDP_ENCAP">UDP_ENCAP</a>:
<a name="L2058" href="source/net/ipv4/udp.c#L2058">2058</a>                 switch (<a href="ident?i=val">val</a>) {
<a name="L2059" href="source/net/ipv4/udp.c#L2059">2059</a>                 case 0:
<a name="L2060" href="source/net/ipv4/udp.c#L2060">2060</a>                 case <a href="ident?i=UDP_ENCAP_ESPINUDP">UDP_ENCAP_ESPINUDP</a>:
<a name="L2061" href="source/net/ipv4/udp.c#L2061">2061</a>                 case <a href="ident?i=UDP_ENCAP_ESPINUDP_NON_IKE">UDP_ENCAP_ESPINUDP_NON_IKE</a>:
<a name="L2062" href="source/net/ipv4/udp.c#L2062">2062</a>                         <a href="ident?i=up">up</a>-&gt;encap_rcv = <a href="ident?i=xfrm4_udp_encap_rcv">xfrm4_udp_encap_rcv</a>;
<a name="L2063" href="source/net/ipv4/udp.c#L2063">2063</a>                         <b><i>/* FALLTHROUGH */</i></b>
<a name="L2064" href="source/net/ipv4/udp.c#L2064">2064</a>                 case <a href="ident?i=UDP_ENCAP_L2TPINUDP">UDP_ENCAP_L2TPINUDP</a>:
<a name="L2065" href="source/net/ipv4/udp.c#L2065">2065</a>                         <a href="ident?i=up">up</a>-&gt;encap_type = <a href="ident?i=val">val</a>;
<a name="L2066" href="source/net/ipv4/udp.c#L2066">2066</a>                         <a href="ident?i=udp_encap_enable">udp_encap_enable</a>();
<a name="L2067" href="source/net/ipv4/udp.c#L2067">2067</a>                         break;
<a name="L2068" href="source/net/ipv4/udp.c#L2068">2068</a>                 default:
<a name="L2069" href="source/net/ipv4/udp.c#L2069">2069</a>                         <a href="ident?i=err">err</a> = -<a href="ident?i=ENOPROTOOPT">ENOPROTOOPT</a>;
<a name="L2070" href="source/net/ipv4/udp.c#L2070">2070</a>                         break;
<a name="L2071" href="source/net/ipv4/udp.c#L2071">2071</a>                 }
<a name="L2072" href="source/net/ipv4/udp.c#L2072">2072</a>                 break;
<a name="L2073" href="source/net/ipv4/udp.c#L2073">2073</a> 
<a name="L2074" href="source/net/ipv4/udp.c#L2074">2074</a>         case <a href="ident?i=UDP_NO_CHECK6_TX">UDP_NO_CHECK6_TX</a>:
<a name="L2075" href="source/net/ipv4/udp.c#L2075">2075</a>                 <a href="ident?i=up">up</a>-&gt;no_check6_tx = valbool;
<a name="L2076" href="source/net/ipv4/udp.c#L2076">2076</a>                 break;
<a name="L2077" href="source/net/ipv4/udp.c#L2077">2077</a> 
<a name="L2078" href="source/net/ipv4/udp.c#L2078">2078</a>         case <a href="ident?i=UDP_NO_CHECK6_RX">UDP_NO_CHECK6_RX</a>:
<a name="L2079" href="source/net/ipv4/udp.c#L2079">2079</a>                 <a href="ident?i=up">up</a>-&gt;no_check6_rx = valbool;
<a name="L2080" href="source/net/ipv4/udp.c#L2080">2080</a>                 break;
<a name="L2081" href="source/net/ipv4/udp.c#L2081">2081</a> 
<a name="L2082" href="source/net/ipv4/udp.c#L2082">2082</a>         <b><i>/*</i></b>
<a name="L2083" href="source/net/ipv4/udp.c#L2083">2083</a> <b><i>         *      UDP-Lite's partial checksum coverage (RFC 3828).</i></b>
<a name="L2084" href="source/net/ipv4/udp.c#L2084">2084</a> <b><i>         */</i></b>
<a name="L2085" href="source/net/ipv4/udp.c#L2085">2085</a>         <b><i>/* The sender sets actual checksum coverage length via this option.</i></b>
<a name="L2086" href="source/net/ipv4/udp.c#L2086">2086</a> <b><i>         * The case coverage &gt; packet length is handled by send module. */</i></b>
<a name="L2087" href="source/net/ipv4/udp.c#L2087">2087</a>         case <a href="ident?i=UDPLITE_SEND_CSCOV">UDPLITE_SEND_CSCOV</a>:
<a name="L2088" href="source/net/ipv4/udp.c#L2088">2088</a>                 if (!is_udplite)         <b><i>/* Disable the option on UDP sockets */</i></b>
<a name="L2089" href="source/net/ipv4/udp.c#L2089">2089</a>                         return -<a href="ident?i=ENOPROTOOPT">ENOPROTOOPT</a>;
<a name="L2090" href="source/net/ipv4/udp.c#L2090">2090</a>                 if (<a href="ident?i=val">val</a> != 0 &amp;&amp; <a href="ident?i=val">val</a> &lt; 8) <b><i>/* Illegal coverage: use default (8) */</i></b>
<a name="L2091" href="source/net/ipv4/udp.c#L2091">2091</a>                         <a href="ident?i=val">val</a> = 8;
<a name="L2092" href="source/net/ipv4/udp.c#L2092">2092</a>                 else if (<a href="ident?i=val">val</a> &gt; <a href="ident?i=USHRT_MAX">USHRT_MAX</a>)
<a name="L2093" href="source/net/ipv4/udp.c#L2093">2093</a>                         <a href="ident?i=val">val</a> = <a href="ident?i=USHRT_MAX">USHRT_MAX</a>;
<a name="L2094" href="source/net/ipv4/udp.c#L2094">2094</a>                 <a href="ident?i=up">up</a>-&gt;pcslen = <a href="ident?i=val">val</a>;
<a name="L2095" href="source/net/ipv4/udp.c#L2095">2095</a>                 <a href="ident?i=up">up</a>-&gt;pcflag |= <a href="ident?i=UDPLITE_SEND_CC">UDPLITE_SEND_CC</a>;
<a name="L2096" href="source/net/ipv4/udp.c#L2096">2096</a>                 break;
<a name="L2097" href="source/net/ipv4/udp.c#L2097">2097</a> 
<a name="L2098" href="source/net/ipv4/udp.c#L2098">2098</a>         <b><i>/* The receiver specifies a minimum checksum coverage value. To make</i></b>
<a name="L2099" href="source/net/ipv4/udp.c#L2099">2099</a> <b><i>         * sense, this should be set to at least 8 (as done below). If zero is</i></b>
<a name="L2100" href="source/net/ipv4/udp.c#L2100">2100</a> <b><i>         * used, this again means full checksum coverage.                     */</i></b>
<a name="L2101" href="source/net/ipv4/udp.c#L2101">2101</a>         case <a href="ident?i=UDPLITE_RECV_CSCOV">UDPLITE_RECV_CSCOV</a>:
<a name="L2102" href="source/net/ipv4/udp.c#L2102">2102</a>                 if (!is_udplite)         <b><i>/* Disable the option on UDP sockets */</i></b>
<a name="L2103" href="source/net/ipv4/udp.c#L2103">2103</a>                         return -<a href="ident?i=ENOPROTOOPT">ENOPROTOOPT</a>;
<a name="L2104" href="source/net/ipv4/udp.c#L2104">2104</a>                 if (<a href="ident?i=val">val</a> != 0 &amp;&amp; <a href="ident?i=val">val</a> &lt; 8) <b><i>/* Avoid silly minimal values.       */</i></b>
<a name="L2105" href="source/net/ipv4/udp.c#L2105">2105</a>                         <a href="ident?i=val">val</a> = 8;
<a name="L2106" href="source/net/ipv4/udp.c#L2106">2106</a>                 else if (<a href="ident?i=val">val</a> &gt; <a href="ident?i=USHRT_MAX">USHRT_MAX</a>)
<a name="L2107" href="source/net/ipv4/udp.c#L2107">2107</a>                         <a href="ident?i=val">val</a> = <a href="ident?i=USHRT_MAX">USHRT_MAX</a>;
<a name="L2108" href="source/net/ipv4/udp.c#L2108">2108</a>                 <a href="ident?i=up">up</a>-&gt;pcrlen = <a href="ident?i=val">val</a>;
<a name="L2109" href="source/net/ipv4/udp.c#L2109">2109</a>                 <a href="ident?i=up">up</a>-&gt;pcflag |= <a href="ident?i=UDPLITE_RECV_CC">UDPLITE_RECV_CC</a>;
<a name="L2110" href="source/net/ipv4/udp.c#L2110">2110</a>                 break;
<a name="L2111" href="source/net/ipv4/udp.c#L2111">2111</a> 
<a name="L2112" href="source/net/ipv4/udp.c#L2112">2112</a>         default:
<a name="L2113" href="source/net/ipv4/udp.c#L2113">2113</a>                 <a href="ident?i=err">err</a> = -<a href="ident?i=ENOPROTOOPT">ENOPROTOOPT</a>;
<a name="L2114" href="source/net/ipv4/udp.c#L2114">2114</a>                 break;
<a name="L2115" href="source/net/ipv4/udp.c#L2115">2115</a>         }
<a name="L2116" href="source/net/ipv4/udp.c#L2116">2116</a> 
<a name="L2117" href="source/net/ipv4/udp.c#L2117">2117</a>         return <a href="ident?i=err">err</a>;
<a name="L2118" href="source/net/ipv4/udp.c#L2118">2118</a> }
<a name="L2119" href="source/net/ipv4/udp.c#L2119">2119</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=udp_lib_setsockopt">udp_lib_setsockopt</a>);
<a name="L2120" href="source/net/ipv4/udp.c#L2120">2120</a> 
<a name="L2121" href="source/net/ipv4/udp.c#L2121">2121</a> int <a href="ident?i=udp_setsockopt">udp_setsockopt</a>(struct <a href="ident?i=sock">sock</a> *sk, int <a href="ident?i=level">level</a>, int optname,
<a name="L2122" href="source/net/ipv4/udp.c#L2122">2122</a>                    char <a href="ident?i=__user">__user</a> *optval, unsigned int <a href="ident?i=optlen">optlen</a>)
<a name="L2123" href="source/net/ipv4/udp.c#L2123">2123</a> {
<a name="L2124" href="source/net/ipv4/udp.c#L2124">2124</a>         if (<a href="ident?i=level">level</a> == <a href="ident?i=SOL_UDP">SOL_UDP</a>  ||  <a href="ident?i=level">level</a> == <a href="ident?i=SOL_UDPLITE">SOL_UDPLITE</a>)
<a name="L2125" href="source/net/ipv4/udp.c#L2125">2125</a>                 return <a href="ident?i=udp_lib_setsockopt">udp_lib_setsockopt</a>(sk, <a href="ident?i=level">level</a>, optname, optval, <a href="ident?i=optlen">optlen</a>,
<a name="L2126" href="source/net/ipv4/udp.c#L2126">2126</a>                                           <a href="ident?i=udp_push_pending_frames">udp_push_pending_frames</a>);
<a name="L2127" href="source/net/ipv4/udp.c#L2127">2127</a>         return <a href="ident?i=ip_setsockopt">ip_setsockopt</a>(sk, <a href="ident?i=level">level</a>, optname, optval, <a href="ident?i=optlen">optlen</a>);
<a name="L2128" href="source/net/ipv4/udp.c#L2128">2128</a> }
<a name="L2129" href="source/net/ipv4/udp.c#L2129">2129</a> 
<a name="L2130" href="source/net/ipv4/udp.c#L2130">2130</a> #ifdef CONFIG_COMPAT
<a name="L2131" href="source/net/ipv4/udp.c#L2131">2131</a> int <a href="ident?i=compat_udp_setsockopt">compat_udp_setsockopt</a>(struct <a href="ident?i=sock">sock</a> *sk, int <a href="ident?i=level">level</a>, int optname,
<a name="L2132" href="source/net/ipv4/udp.c#L2132">2132</a>                           char <a href="ident?i=__user">__user</a> *optval, unsigned int <a href="ident?i=optlen">optlen</a>)
<a name="L2133" href="source/net/ipv4/udp.c#L2133">2133</a> {
<a name="L2134" href="source/net/ipv4/udp.c#L2134">2134</a>         if (<a href="ident?i=level">level</a> == <a href="ident?i=SOL_UDP">SOL_UDP</a>  ||  <a href="ident?i=level">level</a> == <a href="ident?i=SOL_UDPLITE">SOL_UDPLITE</a>)
<a name="L2135" href="source/net/ipv4/udp.c#L2135">2135</a>                 return <a href="ident?i=udp_lib_setsockopt">udp_lib_setsockopt</a>(sk, <a href="ident?i=level">level</a>, optname, optval, <a href="ident?i=optlen">optlen</a>,
<a name="L2136" href="source/net/ipv4/udp.c#L2136">2136</a>                                           <a href="ident?i=udp_push_pending_frames">udp_push_pending_frames</a>);
<a name="L2137" href="source/net/ipv4/udp.c#L2137">2137</a>         return <a href="ident?i=compat_ip_setsockopt">compat_ip_setsockopt</a>(sk, <a href="ident?i=level">level</a>, optname, optval, <a href="ident?i=optlen">optlen</a>);
<a name="L2138" href="source/net/ipv4/udp.c#L2138">2138</a> }
<a name="L2139" href="source/net/ipv4/udp.c#L2139">2139</a> #endif
<a name="L2140" href="source/net/ipv4/udp.c#L2140">2140</a> 
<a name="L2141" href="source/net/ipv4/udp.c#L2141">2141</a> int <a href="ident?i=udp_lib_getsockopt">udp_lib_getsockopt</a>(struct <a href="ident?i=sock">sock</a> *sk, int <a href="ident?i=level">level</a>, int optname,
<a name="L2142" href="source/net/ipv4/udp.c#L2142">2142</a>                        char <a href="ident?i=__user">__user</a> *optval, int <a href="ident?i=__user">__user</a> *<a href="ident?i=optlen">optlen</a>)
<a name="L2143" href="source/net/ipv4/udp.c#L2143">2143</a> {
<a name="L2144" href="source/net/ipv4/udp.c#L2144">2144</a>         struct <a href="ident?i=udp_sock">udp_sock</a> *<a href="ident?i=up">up</a> = <a href="ident?i=udp_sk">udp_sk</a>(sk);
<a name="L2145" href="source/net/ipv4/udp.c#L2145">2145</a>         int <a href="ident?i=val">val</a>, <a href="ident?i=len">len</a>;
<a name="L2146" href="source/net/ipv4/udp.c#L2146">2146</a> 
<a name="L2147" href="source/net/ipv4/udp.c#L2147">2147</a>         if (<a href="ident?i=get_user">get_user</a>(<a href="ident?i=len">len</a>, <a href="ident?i=optlen">optlen</a>))
<a name="L2148" href="source/net/ipv4/udp.c#L2148">2148</a>                 return -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L2149" href="source/net/ipv4/udp.c#L2149">2149</a> 
<a name="L2150" href="source/net/ipv4/udp.c#L2150">2150</a>         <a href="ident?i=len">len</a> = <a href="ident?i=min_t">min_t</a>(unsigned int, <a href="ident?i=len">len</a>, sizeof(int));
<a name="L2151" href="source/net/ipv4/udp.c#L2151">2151</a> 
<a name="L2152" href="source/net/ipv4/udp.c#L2152">2152</a>         if (<a href="ident?i=len">len</a> &lt; 0)
<a name="L2153" href="source/net/ipv4/udp.c#L2153">2153</a>                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L2154" href="source/net/ipv4/udp.c#L2154">2154</a> 
<a name="L2155" href="source/net/ipv4/udp.c#L2155">2155</a>         switch (optname) {
<a name="L2156" href="source/net/ipv4/udp.c#L2156">2156</a>         case <a href="ident?i=UDP_CORK">UDP_CORK</a>:
<a name="L2157" href="source/net/ipv4/udp.c#L2157">2157</a>                 <a href="ident?i=val">val</a> = <a href="ident?i=up">up</a>-&gt;corkflag;
<a name="L2158" href="source/net/ipv4/udp.c#L2158">2158</a>                 break;
<a name="L2159" href="source/net/ipv4/udp.c#L2159">2159</a> 
<a name="L2160" href="source/net/ipv4/udp.c#L2160">2160</a>         case <a href="ident?i=UDP_ENCAP">UDP_ENCAP</a>:
<a name="L2161" href="source/net/ipv4/udp.c#L2161">2161</a>                 <a href="ident?i=val">val</a> = <a href="ident?i=up">up</a>-&gt;encap_type;
<a name="L2162" href="source/net/ipv4/udp.c#L2162">2162</a>                 break;
<a name="L2163" href="source/net/ipv4/udp.c#L2163">2163</a> 
<a name="L2164" href="source/net/ipv4/udp.c#L2164">2164</a>         case <a href="ident?i=UDP_NO_CHECK6_TX">UDP_NO_CHECK6_TX</a>:
<a name="L2165" href="source/net/ipv4/udp.c#L2165">2165</a>                 <a href="ident?i=val">val</a> = <a href="ident?i=up">up</a>-&gt;no_check6_tx;
<a name="L2166" href="source/net/ipv4/udp.c#L2166">2166</a>                 break;
<a name="L2167" href="source/net/ipv4/udp.c#L2167">2167</a> 
<a name="L2168" href="source/net/ipv4/udp.c#L2168">2168</a>         case <a href="ident?i=UDP_NO_CHECK6_RX">UDP_NO_CHECK6_RX</a>:
<a name="L2169" href="source/net/ipv4/udp.c#L2169">2169</a>                 <a href="ident?i=val">val</a> = <a href="ident?i=up">up</a>-&gt;no_check6_rx;
<a name="L2170" href="source/net/ipv4/udp.c#L2170">2170</a>                 break;
<a name="L2171" href="source/net/ipv4/udp.c#L2171">2171</a> 
<a name="L2172" href="source/net/ipv4/udp.c#L2172">2172</a>         <b><i>/* The following two cannot be changed on UDP sockets, the return is</i></b>
<a name="L2173" href="source/net/ipv4/udp.c#L2173">2173</a> <b><i>         * always 0 (which corresponds to the full checksum coverage of UDP). */</i></b>
<a name="L2174" href="source/net/ipv4/udp.c#L2174">2174</a>         case <a href="ident?i=UDPLITE_SEND_CSCOV">UDPLITE_SEND_CSCOV</a>:
<a name="L2175" href="source/net/ipv4/udp.c#L2175">2175</a>                 <a href="ident?i=val">val</a> = <a href="ident?i=up">up</a>-&gt;pcslen;
<a name="L2176" href="source/net/ipv4/udp.c#L2176">2176</a>                 break;
<a name="L2177" href="source/net/ipv4/udp.c#L2177">2177</a> 
<a name="L2178" href="source/net/ipv4/udp.c#L2178">2178</a>         case <a href="ident?i=UDPLITE_RECV_CSCOV">UDPLITE_RECV_CSCOV</a>:
<a name="L2179" href="source/net/ipv4/udp.c#L2179">2179</a>                 <a href="ident?i=val">val</a> = <a href="ident?i=up">up</a>-&gt;pcrlen;
<a name="L2180" href="source/net/ipv4/udp.c#L2180">2180</a>                 break;
<a name="L2181" href="source/net/ipv4/udp.c#L2181">2181</a> 
<a name="L2182" href="source/net/ipv4/udp.c#L2182">2182</a>         default:
<a name="L2183" href="source/net/ipv4/udp.c#L2183">2183</a>                 return -<a href="ident?i=ENOPROTOOPT">ENOPROTOOPT</a>;
<a name="L2184" href="source/net/ipv4/udp.c#L2184">2184</a>         }
<a name="L2185" href="source/net/ipv4/udp.c#L2185">2185</a> 
<a name="L2186" href="source/net/ipv4/udp.c#L2186">2186</a>         if (<a href="ident?i=put_user">put_user</a>(<a href="ident?i=len">len</a>, <a href="ident?i=optlen">optlen</a>))
<a name="L2187" href="source/net/ipv4/udp.c#L2187">2187</a>                 return -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L2188" href="source/net/ipv4/udp.c#L2188">2188</a>         if (<a href="ident?i=copy_to_user">copy_to_user</a>(optval, &amp;<a href="ident?i=val">val</a>, <a href="ident?i=len">len</a>))
<a name="L2189" href="source/net/ipv4/udp.c#L2189">2189</a>                 return -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L2190" href="source/net/ipv4/udp.c#L2190">2190</a>         return 0;
<a name="L2191" href="source/net/ipv4/udp.c#L2191">2191</a> }
<a name="L2192" href="source/net/ipv4/udp.c#L2192">2192</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=udp_lib_getsockopt">udp_lib_getsockopt</a>);
<a name="L2193" href="source/net/ipv4/udp.c#L2193">2193</a> 
<a name="L2194" href="source/net/ipv4/udp.c#L2194">2194</a> int <a href="ident?i=udp_getsockopt">udp_getsockopt</a>(struct <a href="ident?i=sock">sock</a> *sk, int <a href="ident?i=level">level</a>, int optname,
<a name="L2195" href="source/net/ipv4/udp.c#L2195">2195</a>                    char <a href="ident?i=__user">__user</a> *optval, int <a href="ident?i=__user">__user</a> *<a href="ident?i=optlen">optlen</a>)
<a name="L2196" href="source/net/ipv4/udp.c#L2196">2196</a> {
<a name="L2197" href="source/net/ipv4/udp.c#L2197">2197</a>         if (<a href="ident?i=level">level</a> == <a href="ident?i=SOL_UDP">SOL_UDP</a>  ||  <a href="ident?i=level">level</a> == <a href="ident?i=SOL_UDPLITE">SOL_UDPLITE</a>)
<a name="L2198" href="source/net/ipv4/udp.c#L2198">2198</a>                 return <a href="ident?i=udp_lib_getsockopt">udp_lib_getsockopt</a>(sk, <a href="ident?i=level">level</a>, optname, optval, <a href="ident?i=optlen">optlen</a>);
<a name="L2199" href="source/net/ipv4/udp.c#L2199">2199</a>         return <a href="ident?i=ip_getsockopt">ip_getsockopt</a>(sk, <a href="ident?i=level">level</a>, optname, optval, <a href="ident?i=optlen">optlen</a>);
<a name="L2200" href="source/net/ipv4/udp.c#L2200">2200</a> }
<a name="L2201" href="source/net/ipv4/udp.c#L2201">2201</a> 
<a name="L2202" href="source/net/ipv4/udp.c#L2202">2202</a> #ifdef CONFIG_COMPAT
<a name="L2203" href="source/net/ipv4/udp.c#L2203">2203</a> int <a href="ident?i=compat_udp_getsockopt">compat_udp_getsockopt</a>(struct <a href="ident?i=sock">sock</a> *sk, int <a href="ident?i=level">level</a>, int optname,
<a name="L2204" href="source/net/ipv4/udp.c#L2204">2204</a>                                  char <a href="ident?i=__user">__user</a> *optval, int <a href="ident?i=__user">__user</a> *<a href="ident?i=optlen">optlen</a>)
<a name="L2205" href="source/net/ipv4/udp.c#L2205">2205</a> {
<a name="L2206" href="source/net/ipv4/udp.c#L2206">2206</a>         if (<a href="ident?i=level">level</a> == <a href="ident?i=SOL_UDP">SOL_UDP</a>  ||  <a href="ident?i=level">level</a> == <a href="ident?i=SOL_UDPLITE">SOL_UDPLITE</a>)
<a name="L2207" href="source/net/ipv4/udp.c#L2207">2207</a>                 return <a href="ident?i=udp_lib_getsockopt">udp_lib_getsockopt</a>(sk, <a href="ident?i=level">level</a>, optname, optval, <a href="ident?i=optlen">optlen</a>);
<a name="L2208" href="source/net/ipv4/udp.c#L2208">2208</a>         return <a href="ident?i=compat_ip_getsockopt">compat_ip_getsockopt</a>(sk, <a href="ident?i=level">level</a>, optname, optval, <a href="ident?i=optlen">optlen</a>);
<a name="L2209" href="source/net/ipv4/udp.c#L2209">2209</a> }
<a name="L2210" href="source/net/ipv4/udp.c#L2210">2210</a> #endif
<a name="L2211" href="source/net/ipv4/udp.c#L2211">2211</a> <b><i>/**</i></b>
<a name="L2212" href="source/net/ipv4/udp.c#L2212">2212</a> <b><i> *      udp_poll - wait for a UDP event.</i></b>
<a name="L2213" href="source/net/ipv4/udp.c#L2213">2213</a> <b><i> *      @file - file struct</i></b>
<a name="L2214" href="source/net/ipv4/udp.c#L2214">2214</a> <b><i> *      @sock - socket</i></b>
<a name="L2215" href="source/net/ipv4/udp.c#L2215">2215</a> <b><i> *      @wait - poll table</i></b>
<a name="L2216" href="source/net/ipv4/udp.c#L2216">2216</a> <b><i> *</i></b>
<a name="L2217" href="source/net/ipv4/udp.c#L2217">2217</a> <b><i> *      This is same as datagram poll, except for the special case of</i></b>
<a name="L2218" href="source/net/ipv4/udp.c#L2218">2218</a> <b><i> *      blocking sockets. If application is using a blocking fd</i></b>
<a name="L2219" href="source/net/ipv4/udp.c#L2219">2219</a> <b><i> *      and a packet with checksum error is in the queue;</i></b>
<a name="L2220" href="source/net/ipv4/udp.c#L2220">2220</a> <b><i> *      then it could get return from select indicating data available</i></b>
<a name="L2221" href="source/net/ipv4/udp.c#L2221">2221</a> <b><i> *      but then block when reading it. Add special case code</i></b>
<a name="L2222" href="source/net/ipv4/udp.c#L2222">2222</a> <b><i> *      to work around these arguably broken applications.</i></b>
<a name="L2223" href="source/net/ipv4/udp.c#L2223">2223</a> <b><i> */</i></b>
<a name="L2224" href="source/net/ipv4/udp.c#L2224">2224</a> unsigned int <a href="ident?i=udp_poll">udp_poll</a>(struct <a href="ident?i=file">file</a> *<a href="ident?i=file">file</a>, struct <a href="ident?i=socket">socket</a> *<a href="ident?i=sock">sock</a>, <a href="ident?i=poll_table">poll_table</a> *<a href="ident?i=wait">wait</a>)
<a name="L2225" href="source/net/ipv4/udp.c#L2225">2225</a> {
<a name="L2226" href="source/net/ipv4/udp.c#L2226">2226</a>         unsigned int <a href="ident?i=mask">mask</a> = <a href="ident?i=datagram_poll">datagram_poll</a>(<a href="ident?i=file">file</a>, <a href="ident?i=sock">sock</a>, <a href="ident?i=wait">wait</a>);
<a name="L2227" href="source/net/ipv4/udp.c#L2227">2227</a>         struct <a href="ident?i=sock">sock</a> *sk = <a href="ident?i=sock">sock</a>-&gt;sk;
<a name="L2228" href="source/net/ipv4/udp.c#L2228">2228</a> 
<a name="L2229" href="source/net/ipv4/udp.c#L2229">2229</a>         <a href="ident?i=sock_rps_record_flow">sock_rps_record_flow</a>(sk);
<a name="L2230" href="source/net/ipv4/udp.c#L2230">2230</a> 
<a name="L2231" href="source/net/ipv4/udp.c#L2231">2231</a>         <b><i>/* Check for false positives due to checksum errors */</i></b>
<a name="L2232" href="source/net/ipv4/udp.c#L2232">2232</a>         if ((<a href="ident?i=mask">mask</a> &amp; <a href="ident?i=POLLRDNORM">POLLRDNORM</a>) &amp;&amp; !(<a href="ident?i=file">file</a>-&gt;f_flags &amp; <a href="ident?i=O_NONBLOCK">O_NONBLOCK</a>) &amp;&amp;
<a name="L2233" href="source/net/ipv4/udp.c#L2233">2233</a>             !(sk-&gt;sk_shutdown &amp; <a href="ident?i=RCV_SHUTDOWN">RCV_SHUTDOWN</a>) &amp;&amp; !<a href="ident?i=first_packet_length">first_packet_length</a>(sk))
<a name="L2234" href="source/net/ipv4/udp.c#L2234">2234</a>                 <a href="ident?i=mask">mask</a> &amp;= ~(<a href="ident?i=POLLIN">POLLIN</a> | <a href="ident?i=POLLRDNORM">POLLRDNORM</a>);
<a name="L2235" href="source/net/ipv4/udp.c#L2235">2235</a> 
<a name="L2236" href="source/net/ipv4/udp.c#L2236">2236</a>         return <a href="ident?i=mask">mask</a>;
<a name="L2237" href="source/net/ipv4/udp.c#L2237">2237</a> 
<a name="L2238" href="source/net/ipv4/udp.c#L2238">2238</a> }
<a name="L2239" href="source/net/ipv4/udp.c#L2239">2239</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=udp_poll">udp_poll</a>);
<a name="L2240" href="source/net/ipv4/udp.c#L2240">2240</a> 
<a name="L2241" href="source/net/ipv4/udp.c#L2241">2241</a> struct <a href="ident?i=proto">proto</a> <a href="ident?i=udp_prot">udp_prot</a> = {
<a name="L2242" href="source/net/ipv4/udp.c#L2242">2242</a>         .<a href="ident?i=name">name</a>              = <i>"UDP"</i>,
<a name="L2243" href="source/net/ipv4/udp.c#L2243">2243</a>         .owner             = <a href="ident?i=THIS_MODULE">THIS_MODULE</a>,
<a name="L2244" href="source/net/ipv4/udp.c#L2244">2244</a>         .<a href="ident?i=close">close</a>             = <a href="ident?i=udp_lib_close">udp_lib_close</a>,
<a name="L2245" href="source/net/ipv4/udp.c#L2245">2245</a>         .<a href="ident?i=connect">connect</a>           = <a href="ident?i=ip4_datagram_connect">ip4_datagram_connect</a>,
<a name="L2246" href="source/net/ipv4/udp.c#L2246">2246</a>         .<a href="ident?i=disconnect">disconnect</a>        = <a href="ident?i=udp_disconnect">udp_disconnect</a>,
<a name="L2247" href="source/net/ipv4/udp.c#L2247">2247</a>         .<a href="ident?i=ioctl">ioctl</a>             = <a href="ident?i=udp_ioctl">udp_ioctl</a>,
<a name="L2248" href="source/net/ipv4/udp.c#L2248">2248</a>         .<a href="ident?i=destroy">destroy</a>           = <a href="ident?i=udp_destroy_sock">udp_destroy_sock</a>,
<a name="L2249" href="source/net/ipv4/udp.c#L2249">2249</a>         .<a href="ident?i=setsockopt">setsockopt</a>        = <a href="ident?i=udp_setsockopt">udp_setsockopt</a>,
<a name="L2250" href="source/net/ipv4/udp.c#L2250">2250</a>         .getsockopt        = <a href="ident?i=udp_getsockopt">udp_getsockopt</a>,
<a name="L2251" href="source/net/ipv4/udp.c#L2251">2251</a>         .<a href="ident?i=sendmsg">sendmsg</a>           = <a href="ident?i=udp_sendmsg">udp_sendmsg</a>,
<a name="L2252" href="source/net/ipv4/udp.c#L2252">2252</a>         .recvmsg           = <a href="ident?i=udp_recvmsg">udp_recvmsg</a>,
<a name="L2253" href="source/net/ipv4/udp.c#L2253">2253</a>         .sendpage          = <a href="ident?i=udp_sendpage">udp_sendpage</a>,
<a name="L2254" href="source/net/ipv4/udp.c#L2254">2254</a>         .backlog_rcv       = <a href="ident?i=__udp_queue_rcv_skb">__udp_queue_rcv_skb</a>,
<a name="L2255" href="source/net/ipv4/udp.c#L2255">2255</a>         .release_cb        = <a href="ident?i=ip4_datagram_release_cb">ip4_datagram_release_cb</a>,
<a name="L2256" href="source/net/ipv4/udp.c#L2256">2256</a>         .<a href="ident?i=hash">hash</a>              = <a href="ident?i=udp_lib_hash">udp_lib_hash</a>,
<a name="L2257" href="source/net/ipv4/udp.c#L2257">2257</a>         .unhash            = <a href="ident?i=udp_lib_unhash">udp_lib_unhash</a>,
<a name="L2258" href="source/net/ipv4/udp.c#L2258">2258</a>         .rehash            = <a href="ident?i=udp_v4_rehash">udp_v4_rehash</a>,
<a name="L2259" href="source/net/ipv4/udp.c#L2259">2259</a>         .<a href="ident?i=get_port">get_port</a>          = <a href="ident?i=udp_v4_get_port">udp_v4_get_port</a>,
<a name="L2260" href="source/net/ipv4/udp.c#L2260">2260</a>         .memory_allocated  = &amp;<a href="ident?i=udp_memory_allocated">udp_memory_allocated</a>,
<a name="L2261" href="source/net/ipv4/udp.c#L2261">2261</a>         .sysctl_mem        = <a href="ident?i=sysctl_udp_mem">sysctl_udp_mem</a>,
<a name="L2262" href="source/net/ipv4/udp.c#L2262">2262</a>         .sysctl_wmem       = &amp;<a href="ident?i=sysctl_udp_wmem_min">sysctl_udp_wmem_min</a>,
<a name="L2263" href="source/net/ipv4/udp.c#L2263">2263</a>         .sysctl_rmem       = &amp;<a href="ident?i=sysctl_udp_rmem_min">sysctl_udp_rmem_min</a>,
<a name="L2264" href="source/net/ipv4/udp.c#L2264">2264</a>         .obj_size          = sizeof(struct <a href="ident?i=udp_sock">udp_sock</a>),
<a name="L2265" href="source/net/ipv4/udp.c#L2265">2265</a>         .slab_flags        = <a href="ident?i=SLAB_DESTROY_BY_RCU">SLAB_DESTROY_BY_RCU</a>,
<a name="L2266" href="source/net/ipv4/udp.c#L2266">2266</a>         .<a href="ident?i=h">h</a>.<a href="ident?i=udp_table">udp_table</a>       = &amp;<a href="ident?i=udp_table">udp_table</a>,
<a name="L2267" href="source/net/ipv4/udp.c#L2267">2267</a> #ifdef CONFIG_COMPAT
<a name="L2268" href="source/net/ipv4/udp.c#L2268">2268</a>         .compat_setsockopt = <a href="ident?i=compat_udp_setsockopt">compat_udp_setsockopt</a>,
<a name="L2269" href="source/net/ipv4/udp.c#L2269">2269</a>         .compat_getsockopt = <a href="ident?i=compat_udp_getsockopt">compat_udp_getsockopt</a>,
<a name="L2270" href="source/net/ipv4/udp.c#L2270">2270</a> #endif
<a name="L2271" href="source/net/ipv4/udp.c#L2271">2271</a>         .clear_sk          = <a href="ident?i=sk_prot_clear_portaddr_nulls">sk_prot_clear_portaddr_nulls</a>,
<a name="L2272" href="source/net/ipv4/udp.c#L2272">2272</a> };
<a name="L2273" href="source/net/ipv4/udp.c#L2273">2273</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=udp_prot">udp_prot</a>);
<a name="L2274" href="source/net/ipv4/udp.c#L2274">2274</a> 
<a name="L2275" href="source/net/ipv4/udp.c#L2275">2275</a> <b><i>/* ------------------------------------------------------------------------ */</i></b>
<a name="L2276" href="source/net/ipv4/udp.c#L2276">2276</a> #ifdef CONFIG_PROC_FS
<a name="L2277" href="source/net/ipv4/udp.c#L2277">2277</a> 
<a name="L2278" href="source/net/ipv4/udp.c#L2278">2278</a> static struct <a href="ident?i=sock">sock</a> *<a href="ident?i=udp_get_first">udp_get_first</a>(struct <a href="ident?i=seq_file">seq_file</a> *<a href="ident?i=seq">seq</a>, int <a href="ident?i=start">start</a>)
<a name="L2279" href="source/net/ipv4/udp.c#L2279">2279</a> {
<a name="L2280" href="source/net/ipv4/udp.c#L2280">2280</a>         struct <a href="ident?i=sock">sock</a> *sk;
<a name="L2281" href="source/net/ipv4/udp.c#L2281">2281</a>         struct <a href="ident?i=udp_iter_state">udp_iter_state</a> *<a href="ident?i=state">state</a> = <a href="ident?i=seq">seq</a>-&gt;<a href="ident?i=private">private</a>;
<a name="L2282" href="source/net/ipv4/udp.c#L2282">2282</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=seq_file_net">seq_file_net</a>(<a href="ident?i=seq">seq</a>);
<a name="L2283" href="source/net/ipv4/udp.c#L2283">2283</a> 
<a name="L2284" href="source/net/ipv4/udp.c#L2284">2284</a>         for (<a href="ident?i=state">state</a>-&gt;<a href="ident?i=bucket">bucket</a> = <a href="ident?i=start">start</a>; <a href="ident?i=state">state</a>-&gt;<a href="ident?i=bucket">bucket</a> &lt;= <a href="ident?i=state">state</a>-&gt;<a href="ident?i=udp_table">udp_table</a>-&gt;<a href="ident?i=mask">mask</a>;
<a name="L2285" href="source/net/ipv4/udp.c#L2285">2285</a>              ++<a href="ident?i=state">state</a>-&gt;<a href="ident?i=bucket">bucket</a>) {
<a name="L2286" href="source/net/ipv4/udp.c#L2286">2286</a>                 struct <a href="ident?i=hlist_nulls_node">hlist_nulls_node</a> *<a href="ident?i=node">node</a>;
<a name="L2287" href="source/net/ipv4/udp.c#L2287">2287</a>                 struct <a href="ident?i=udp_hslot">udp_hslot</a> *hslot = &amp;<a href="ident?i=state">state</a>-&gt;<a href="ident?i=udp_table">udp_table</a>-&gt;<a href="ident?i=hash">hash</a>[<a href="ident?i=state">state</a>-&gt;<a href="ident?i=bucket">bucket</a>];
<a name="L2288" href="source/net/ipv4/udp.c#L2288">2288</a> 
<a name="L2289" href="source/net/ipv4/udp.c#L2289">2289</a>                 if (<a href="ident?i=hlist_nulls_empty">hlist_nulls_empty</a>(&amp;hslot-&gt;<a href="ident?i=head">head</a>))
<a name="L2290" href="source/net/ipv4/udp.c#L2290">2290</a>                         continue;
<a name="L2291" href="source/net/ipv4/udp.c#L2291">2291</a> 
<a name="L2292" href="source/net/ipv4/udp.c#L2292">2292</a>                 <a href="ident?i=spin_lock_bh">spin_lock_bh</a>(&amp;hslot-&gt;<a href="ident?i=lock">lock</a>);
<a name="L2293" href="source/net/ipv4/udp.c#L2293">2293</a>                 <a href="ident?i=sk_nulls_for_each">sk_nulls_for_each</a>(sk, <a href="ident?i=node">node</a>, &amp;hslot-&gt;<a href="ident?i=head">head</a>) {
<a name="L2294" href="source/net/ipv4/udp.c#L2294">2294</a>                         if (!<a href="ident?i=net_eq">net_eq</a>(<a href="ident?i=sock_net">sock_net</a>(sk), <a href="ident?i=net">net</a>))
<a name="L2295" href="source/net/ipv4/udp.c#L2295">2295</a>                                 continue;
<a name="L2296" href="source/net/ipv4/udp.c#L2296">2296</a>                         if (sk-&gt;<a href="ident?i=sk_family">sk_family</a> == <a href="ident?i=state">state</a>-&gt;<a href="ident?i=family">family</a>)
<a name="L2297" href="source/net/ipv4/udp.c#L2297">2297</a>                                 goto <a href="ident?i=found">found</a>;
<a name="L2298" href="source/net/ipv4/udp.c#L2298">2298</a>                 }
<a name="L2299" href="source/net/ipv4/udp.c#L2299">2299</a>                 <a href="ident?i=spin_unlock_bh">spin_unlock_bh</a>(&amp;hslot-&gt;<a href="ident?i=lock">lock</a>);
<a name="L2300" href="source/net/ipv4/udp.c#L2300">2300</a>         }
<a name="L2301" href="source/net/ipv4/udp.c#L2301">2301</a>         sk = <a href="ident?i=NULL">NULL</a>;
<a name="L2302" href="source/net/ipv4/udp.c#L2302">2302</a> <a href="ident?i=found">found</a>:
<a name="L2303" href="source/net/ipv4/udp.c#L2303">2303</a>         return sk;
<a name="L2304" href="source/net/ipv4/udp.c#L2304">2304</a> }
<a name="L2305" href="source/net/ipv4/udp.c#L2305">2305</a> 
<a name="L2306" href="source/net/ipv4/udp.c#L2306">2306</a> static struct <a href="ident?i=sock">sock</a> *<a href="ident?i=udp_get_next">udp_get_next</a>(struct <a href="ident?i=seq_file">seq_file</a> *<a href="ident?i=seq">seq</a>, struct <a href="ident?i=sock">sock</a> *sk)
<a name="L2307" href="source/net/ipv4/udp.c#L2307">2307</a> {
<a name="L2308" href="source/net/ipv4/udp.c#L2308">2308</a>         struct <a href="ident?i=udp_iter_state">udp_iter_state</a> *<a href="ident?i=state">state</a> = <a href="ident?i=seq">seq</a>-&gt;<a href="ident?i=private">private</a>;
<a name="L2309" href="source/net/ipv4/udp.c#L2309">2309</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=seq_file_net">seq_file_net</a>(<a href="ident?i=seq">seq</a>);
<a name="L2310" href="source/net/ipv4/udp.c#L2310">2310</a> 
<a name="L2311" href="source/net/ipv4/udp.c#L2311">2311</a>         do {
<a name="L2312" href="source/net/ipv4/udp.c#L2312">2312</a>                 sk = <a href="ident?i=sk_nulls_next">sk_nulls_next</a>(sk);
<a name="L2313" href="source/net/ipv4/udp.c#L2313">2313</a>         } while (sk &amp;&amp; (!<a href="ident?i=net_eq">net_eq</a>(<a href="ident?i=sock_net">sock_net</a>(sk), <a href="ident?i=net">net</a>) || sk-&gt;<a href="ident?i=sk_family">sk_family</a> != <a href="ident?i=state">state</a>-&gt;<a href="ident?i=family">family</a>));
<a name="L2314" href="source/net/ipv4/udp.c#L2314">2314</a> 
<a name="L2315" href="source/net/ipv4/udp.c#L2315">2315</a>         if (!sk) {
<a name="L2316" href="source/net/ipv4/udp.c#L2316">2316</a>                 if (<a href="ident?i=state">state</a>-&gt;<a href="ident?i=bucket">bucket</a> &lt;= <a href="ident?i=state">state</a>-&gt;<a href="ident?i=udp_table">udp_table</a>-&gt;<a href="ident?i=mask">mask</a>)
<a name="L2317" href="source/net/ipv4/udp.c#L2317">2317</a>                         <a href="ident?i=spin_unlock_bh">spin_unlock_bh</a>(&amp;<a href="ident?i=state">state</a>-&gt;<a href="ident?i=udp_table">udp_table</a>-&gt;<a href="ident?i=hash">hash</a>[<a href="ident?i=state">state</a>-&gt;<a href="ident?i=bucket">bucket</a>].<a href="ident?i=lock">lock</a>);
<a name="L2318" href="source/net/ipv4/udp.c#L2318">2318</a>                 return <a href="ident?i=udp_get_first">udp_get_first</a>(<a href="ident?i=seq">seq</a>, <a href="ident?i=state">state</a>-&gt;<a href="ident?i=bucket">bucket</a> + 1);
<a name="L2319" href="source/net/ipv4/udp.c#L2319">2319</a>         }
<a name="L2320" href="source/net/ipv4/udp.c#L2320">2320</a>         return sk;
<a name="L2321" href="source/net/ipv4/udp.c#L2321">2321</a> }
<a name="L2322" href="source/net/ipv4/udp.c#L2322">2322</a> 
<a name="L2323" href="source/net/ipv4/udp.c#L2323">2323</a> static struct <a href="ident?i=sock">sock</a> *<a href="ident?i=udp_get_idx">udp_get_idx</a>(struct <a href="ident?i=seq_file">seq_file</a> *<a href="ident?i=seq">seq</a>, <a href="ident?i=loff_t">loff_t</a> <a href="ident?i=pos">pos</a>)
<a name="L2324" href="source/net/ipv4/udp.c#L2324">2324</a> {
<a name="L2325" href="source/net/ipv4/udp.c#L2325">2325</a>         struct <a href="ident?i=sock">sock</a> *sk = <a href="ident?i=udp_get_first">udp_get_first</a>(<a href="ident?i=seq">seq</a>, 0);
<a name="L2326" href="source/net/ipv4/udp.c#L2326">2326</a> 
<a name="L2327" href="source/net/ipv4/udp.c#L2327">2327</a>         if (sk)
<a name="L2328" href="source/net/ipv4/udp.c#L2328">2328</a>                 while (<a href="ident?i=pos">pos</a> &amp;&amp; (sk = <a href="ident?i=udp_get_next">udp_get_next</a>(<a href="ident?i=seq">seq</a>, sk)) != <a href="ident?i=NULL">NULL</a>)
<a name="L2329" href="source/net/ipv4/udp.c#L2329">2329</a>                         --<a href="ident?i=pos">pos</a>;
<a name="L2330" href="source/net/ipv4/udp.c#L2330">2330</a>         return <a href="ident?i=pos">pos</a> ? <a href="ident?i=NULL">NULL</a> : sk;
<a name="L2331" href="source/net/ipv4/udp.c#L2331">2331</a> }
<a name="L2332" href="source/net/ipv4/udp.c#L2332">2332</a> 
<a name="L2333" href="source/net/ipv4/udp.c#L2333">2333</a> static void *<a href="ident?i=udp_seq_start">udp_seq_start</a>(struct <a href="ident?i=seq_file">seq_file</a> *<a href="ident?i=seq">seq</a>, <a href="ident?i=loff_t">loff_t</a> *<a href="ident?i=pos">pos</a>)
<a name="L2334" href="source/net/ipv4/udp.c#L2334">2334</a> {
<a name="L2335" href="source/net/ipv4/udp.c#L2335">2335</a>         struct <a href="ident?i=udp_iter_state">udp_iter_state</a> *<a href="ident?i=state">state</a> = <a href="ident?i=seq">seq</a>-&gt;<a href="ident?i=private">private</a>;
<a name="L2336" href="source/net/ipv4/udp.c#L2336">2336</a>         <a href="ident?i=state">state</a>-&gt;<a href="ident?i=bucket">bucket</a> = <a href="ident?i=MAX_UDP_PORTS">MAX_UDP_PORTS</a>;
<a name="L2337" href="source/net/ipv4/udp.c#L2337">2337</a> 
<a name="L2338" href="source/net/ipv4/udp.c#L2338">2338</a>         return *<a href="ident?i=pos">pos</a> ? <a href="ident?i=udp_get_idx">udp_get_idx</a>(<a href="ident?i=seq">seq</a>, *<a href="ident?i=pos">pos</a>-1) : <a href="ident?i=SEQ_START_TOKEN">SEQ_START_TOKEN</a>;
<a name="L2339" href="source/net/ipv4/udp.c#L2339">2339</a> }
<a name="L2340" href="source/net/ipv4/udp.c#L2340">2340</a> 
<a name="L2341" href="source/net/ipv4/udp.c#L2341">2341</a> static void *<a href="ident?i=udp_seq_next">udp_seq_next</a>(struct <a href="ident?i=seq_file">seq_file</a> *<a href="ident?i=seq">seq</a>, void *<a href="ident?i=v">v</a>, <a href="ident?i=loff_t">loff_t</a> *<a href="ident?i=pos">pos</a>)
<a name="L2342" href="source/net/ipv4/udp.c#L2342">2342</a> {
<a name="L2343" href="source/net/ipv4/udp.c#L2343">2343</a>         struct <a href="ident?i=sock">sock</a> *sk;
<a name="L2344" href="source/net/ipv4/udp.c#L2344">2344</a> 
<a name="L2345" href="source/net/ipv4/udp.c#L2345">2345</a>         if (<a href="ident?i=v">v</a> == <a href="ident?i=SEQ_START_TOKEN">SEQ_START_TOKEN</a>)
<a name="L2346" href="source/net/ipv4/udp.c#L2346">2346</a>                 sk = <a href="ident?i=udp_get_idx">udp_get_idx</a>(<a href="ident?i=seq">seq</a>, 0);
<a name="L2347" href="source/net/ipv4/udp.c#L2347">2347</a>         else
<a name="L2348" href="source/net/ipv4/udp.c#L2348">2348</a>                 sk = <a href="ident?i=udp_get_next">udp_get_next</a>(<a href="ident?i=seq">seq</a>, <a href="ident?i=v">v</a>);
<a name="L2349" href="source/net/ipv4/udp.c#L2349">2349</a> 
<a name="L2350" href="source/net/ipv4/udp.c#L2350">2350</a>         ++*<a href="ident?i=pos">pos</a>;
<a name="L2351" href="source/net/ipv4/udp.c#L2351">2351</a>         return sk;
<a name="L2352" href="source/net/ipv4/udp.c#L2352">2352</a> }
<a name="L2353" href="source/net/ipv4/udp.c#L2353">2353</a> 
<a name="L2354" href="source/net/ipv4/udp.c#L2354">2354</a> static void <a href="ident?i=udp_seq_stop">udp_seq_stop</a>(struct <a href="ident?i=seq_file">seq_file</a> *<a href="ident?i=seq">seq</a>, void *<a href="ident?i=v">v</a>)
<a name="L2355" href="source/net/ipv4/udp.c#L2355">2355</a> {
<a name="L2356" href="source/net/ipv4/udp.c#L2356">2356</a>         struct <a href="ident?i=udp_iter_state">udp_iter_state</a> *<a href="ident?i=state">state</a> = <a href="ident?i=seq">seq</a>-&gt;<a href="ident?i=private">private</a>;
<a name="L2357" href="source/net/ipv4/udp.c#L2357">2357</a> 
<a name="L2358" href="source/net/ipv4/udp.c#L2358">2358</a>         if (<a href="ident?i=state">state</a>-&gt;<a href="ident?i=bucket">bucket</a> &lt;= <a href="ident?i=state">state</a>-&gt;<a href="ident?i=udp_table">udp_table</a>-&gt;<a href="ident?i=mask">mask</a>)
<a name="L2359" href="source/net/ipv4/udp.c#L2359">2359</a>                 <a href="ident?i=spin_unlock_bh">spin_unlock_bh</a>(&amp;<a href="ident?i=state">state</a>-&gt;<a href="ident?i=udp_table">udp_table</a>-&gt;<a href="ident?i=hash">hash</a>[<a href="ident?i=state">state</a>-&gt;<a href="ident?i=bucket">bucket</a>].<a href="ident?i=lock">lock</a>);
<a name="L2360" href="source/net/ipv4/udp.c#L2360">2360</a> }
<a name="L2361" href="source/net/ipv4/udp.c#L2361">2361</a> 
<a name="L2362" href="source/net/ipv4/udp.c#L2362">2362</a> int <a href="ident?i=udp_seq_open">udp_seq_open</a>(struct <a href="ident?i=inode">inode</a> *<a href="ident?i=inode">inode</a>, struct <a href="ident?i=file">file</a> *<a href="ident?i=file">file</a>)
<a name="L2363" href="source/net/ipv4/udp.c#L2363">2363</a> {
<a name="L2364" href="source/net/ipv4/udp.c#L2364">2364</a>         struct <a href="ident?i=udp_seq_afinfo">udp_seq_afinfo</a> *afinfo = <a href="ident?i=PDE_DATA">PDE_DATA</a>(<a href="ident?i=inode">inode</a>);
<a name="L2365" href="source/net/ipv4/udp.c#L2365">2365</a>         struct <a href="ident?i=udp_iter_state">udp_iter_state</a> *<a href="ident?i=s">s</a>;
<a name="L2366" href="source/net/ipv4/udp.c#L2366">2366</a>         int <a href="ident?i=err">err</a>;
<a name="L2367" href="source/net/ipv4/udp.c#L2367">2367</a> 
<a name="L2368" href="source/net/ipv4/udp.c#L2368">2368</a>         <a href="ident?i=err">err</a> = <a href="ident?i=seq_open_net">seq_open_net</a>(<a href="ident?i=inode">inode</a>, <a href="ident?i=file">file</a>, &amp;afinfo-&gt;seq_ops,
<a name="L2369" href="source/net/ipv4/udp.c#L2369">2369</a>                            sizeof(struct <a href="ident?i=udp_iter_state">udp_iter_state</a>));
<a name="L2370" href="source/net/ipv4/udp.c#L2370">2370</a>         if (<a href="ident?i=err">err</a> &lt; 0)
<a name="L2371" href="source/net/ipv4/udp.c#L2371">2371</a>                 return <a href="ident?i=err">err</a>;
<a name="L2372" href="source/net/ipv4/udp.c#L2372">2372</a> 
<a name="L2373" href="source/net/ipv4/udp.c#L2373">2373</a>         <a href="ident?i=s">s</a> = ((struct <a href="ident?i=seq_file">seq_file</a> *)<a href="ident?i=file">file</a>-&gt;<a href="ident?i=private_data">private_data</a>)-&gt;<a href="ident?i=private">private</a>;
<a name="L2374" href="source/net/ipv4/udp.c#L2374">2374</a>         <a href="ident?i=s">s</a>-&gt;<a href="ident?i=family">family</a>               = afinfo-&gt;<a href="ident?i=family">family</a>;
<a name="L2375" href="source/net/ipv4/udp.c#L2375">2375</a>         <a href="ident?i=s">s</a>-&gt;<a href="ident?i=udp_table">udp_table</a>            = afinfo-&gt;<a href="ident?i=udp_table">udp_table</a>;
<a name="L2376" href="source/net/ipv4/udp.c#L2376">2376</a>         return <a href="ident?i=err">err</a>;
<a name="L2377" href="source/net/ipv4/udp.c#L2377">2377</a> }
<a name="L2378" href="source/net/ipv4/udp.c#L2378">2378</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=udp_seq_open">udp_seq_open</a>);
<a name="L2379" href="source/net/ipv4/udp.c#L2379">2379</a> 
<a name="L2380" href="source/net/ipv4/udp.c#L2380">2380</a> <b><i>/* ------------------------------------------------------------------------ */</i></b>
<a name="L2381" href="source/net/ipv4/udp.c#L2381">2381</a> int <a href="ident?i=udp_proc_register">udp_proc_register</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>, struct <a href="ident?i=udp_seq_afinfo">udp_seq_afinfo</a> *afinfo)
<a name="L2382" href="source/net/ipv4/udp.c#L2382">2382</a> {
<a name="L2383" href="source/net/ipv4/udp.c#L2383">2383</a>         struct <a href="ident?i=proc_dir_entry">proc_dir_entry</a> *<a href="ident?i=p">p</a>;
<a name="L2384" href="source/net/ipv4/udp.c#L2384">2384</a>         int <a href="ident?i=rc">rc</a> = 0;
<a name="L2385" href="source/net/ipv4/udp.c#L2385">2385</a> 
<a name="L2386" href="source/net/ipv4/udp.c#L2386">2386</a>         afinfo-&gt;seq_ops.<a href="ident?i=start">start</a>           = <a href="ident?i=udp_seq_start">udp_seq_start</a>;
<a name="L2387" href="source/net/ipv4/udp.c#L2387">2387</a>         afinfo-&gt;seq_ops.<a href="ident?i=next">next</a>            = <a href="ident?i=udp_seq_next">udp_seq_next</a>;
<a name="L2388" href="source/net/ipv4/udp.c#L2388">2388</a>         afinfo-&gt;seq_ops.<a href="ident?i=stop">stop</a>            = <a href="ident?i=udp_seq_stop">udp_seq_stop</a>;
<a name="L2389" href="source/net/ipv4/udp.c#L2389">2389</a> 
<a name="L2390" href="source/net/ipv4/udp.c#L2390">2390</a>         <a href="ident?i=p">p</a> = <a href="ident?i=proc_create_data">proc_create_data</a>(afinfo-&gt;<a href="ident?i=name">name</a>, <a href="ident?i=S_IRUGO">S_IRUGO</a>, <a href="ident?i=net">net</a>-&gt;proc_net,
<a name="L2391" href="source/net/ipv4/udp.c#L2391">2391</a>                              afinfo-&gt;seq_fops, afinfo);
<a name="L2392" href="source/net/ipv4/udp.c#L2392">2392</a>         if (!<a href="ident?i=p">p</a>)
<a name="L2393" href="source/net/ipv4/udp.c#L2393">2393</a>                 <a href="ident?i=rc">rc</a> = -<a href="ident?i=ENOMEM">ENOMEM</a>;
<a name="L2394" href="source/net/ipv4/udp.c#L2394">2394</a>         return <a href="ident?i=rc">rc</a>;
<a name="L2395" href="source/net/ipv4/udp.c#L2395">2395</a> }
<a name="L2396" href="source/net/ipv4/udp.c#L2396">2396</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=udp_proc_register">udp_proc_register</a>);
<a name="L2397" href="source/net/ipv4/udp.c#L2397">2397</a> 
<a name="L2398" href="source/net/ipv4/udp.c#L2398">2398</a> void <a href="ident?i=udp_proc_unregister">udp_proc_unregister</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>, struct <a href="ident?i=udp_seq_afinfo">udp_seq_afinfo</a> *afinfo)
<a name="L2399" href="source/net/ipv4/udp.c#L2399">2399</a> {
<a name="L2400" href="source/net/ipv4/udp.c#L2400">2400</a>         <a href="ident?i=remove_proc_entry">remove_proc_entry</a>(afinfo-&gt;<a href="ident?i=name">name</a>, <a href="ident?i=net">net</a>-&gt;proc_net);
<a name="L2401" href="source/net/ipv4/udp.c#L2401">2401</a> }
<a name="L2402" href="source/net/ipv4/udp.c#L2402">2402</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=udp_proc_unregister">udp_proc_unregister</a>);
<a name="L2403" href="source/net/ipv4/udp.c#L2403">2403</a> 
<a name="L2404" href="source/net/ipv4/udp.c#L2404">2404</a> <b><i>/* ------------------------------------------------------------------------ */</i></b>
<a name="L2405" href="source/net/ipv4/udp.c#L2405">2405</a> static void <a href="ident?i=udp4_format_sock">udp4_format_sock</a>(struct <a href="ident?i=sock">sock</a> *<a href="ident?i=sp">sp</a>, struct <a href="ident?i=seq_file">seq_file</a> *<a href="ident?i=f">f</a>,
<a name="L2406" href="source/net/ipv4/udp.c#L2406">2406</a>                 int <a href="ident?i=bucket">bucket</a>)
<a name="L2407" href="source/net/ipv4/udp.c#L2407">2407</a> {
<a name="L2408" href="source/net/ipv4/udp.c#L2408">2408</a>         struct <a href="ident?i=inet_sock">inet_sock</a> *inet = <a href="ident?i=inet_sk">inet_sk</a>(<a href="ident?i=sp">sp</a>);
<a name="L2409" href="source/net/ipv4/udp.c#L2409">2409</a>         <a href="ident?i=__be32">__be32</a> <a href="ident?i=dest">dest</a> = inet-&gt;<a href="ident?i=inet_daddr">inet_daddr</a>;
<a name="L2410" href="source/net/ipv4/udp.c#L2410">2410</a>         <a href="ident?i=__be32">__be32</a> <a href="ident?i=src">src</a>  = inet-&gt;<a href="ident?i=inet_rcv_saddr">inet_rcv_saddr</a>;
<a name="L2411" href="source/net/ipv4/udp.c#L2411">2411</a>         <a href="ident?i=__u16">__u16</a> destp       = <a href="ident?i=ntohs">ntohs</a>(inet-&gt;<a href="ident?i=inet_dport">inet_dport</a>);
<a name="L2412" href="source/net/ipv4/udp.c#L2412">2412</a>         <a href="ident?i=__u16">__u16</a> srcp        = <a href="ident?i=ntohs">ntohs</a>(inet-&gt;inet_sport);
<a name="L2413" href="source/net/ipv4/udp.c#L2413">2413</a> 
<a name="L2414" href="source/net/ipv4/udp.c#L2414">2414</a>         <a href="ident?i=seq_printf">seq_printf</a>(<a href="ident?i=f">f</a>, <i>"%5d: %08X:%04X %08X:%04X"</i>
<a name="L2415" href="source/net/ipv4/udp.c#L2415">2415</a>                 <i>" %02X %08X:%08X %02X:%08lX %08X %5u %8d %lu %d %pK %d"</i>,
<a name="L2416" href="source/net/ipv4/udp.c#L2416">2416</a>                 <a href="ident?i=bucket">bucket</a>, <a href="ident?i=src">src</a>, srcp, <a href="ident?i=dest">dest</a>, destp, <a href="ident?i=sp">sp</a>-&gt;<a href="ident?i=sk_state">sk_state</a>,
<a name="L2417" href="source/net/ipv4/udp.c#L2417">2417</a>                 <a href="ident?i=sk_wmem_alloc_get">sk_wmem_alloc_get</a>(<a href="ident?i=sp">sp</a>),
<a name="L2418" href="source/net/ipv4/udp.c#L2418">2418</a>                 <a href="ident?i=sk_rmem_alloc_get">sk_rmem_alloc_get</a>(<a href="ident?i=sp">sp</a>),
<a name="L2419" href="source/net/ipv4/udp.c#L2419">2419</a>                 0, 0L, 0,
<a name="L2420" href="source/net/ipv4/udp.c#L2420">2420</a>                 <a href="ident?i=from_kuid_munged">from_kuid_munged</a>(<a href="ident?i=seq_user_ns">seq_user_ns</a>(<a href="ident?i=f">f</a>), <a href="ident?i=sock_i_uid">sock_i_uid</a>(<a href="ident?i=sp">sp</a>)),
<a name="L2421" href="source/net/ipv4/udp.c#L2421">2421</a>                 0, <a href="ident?i=sock_i_ino">sock_i_ino</a>(<a href="ident?i=sp">sp</a>),
<a name="L2422" href="source/net/ipv4/udp.c#L2422">2422</a>                 <a href="ident?i=atomic_read">atomic_read</a>(&amp;<a href="ident?i=sp">sp</a>-&gt;<a href="ident?i=sk_refcnt">sk_refcnt</a>), <a href="ident?i=sp">sp</a>,
<a name="L2423" href="source/net/ipv4/udp.c#L2423">2423</a>                 <a href="ident?i=atomic_read">atomic_read</a>(&amp;<a href="ident?i=sp">sp</a>-&gt;sk_drops));
<a name="L2424" href="source/net/ipv4/udp.c#L2424">2424</a> }
<a name="L2425" href="source/net/ipv4/udp.c#L2425">2425</a> 
<a name="L2426" href="source/net/ipv4/udp.c#L2426">2426</a> int <a href="ident?i=udp4_seq_show">udp4_seq_show</a>(struct <a href="ident?i=seq_file">seq_file</a> *<a href="ident?i=seq">seq</a>, void *<a href="ident?i=v">v</a>)
<a name="L2427" href="source/net/ipv4/udp.c#L2427">2427</a> {
<a name="L2428" href="source/net/ipv4/udp.c#L2428">2428</a>         <a href="ident?i=seq_setwidth">seq_setwidth</a>(<a href="ident?i=seq">seq</a>, 127);
<a name="L2429" href="source/net/ipv4/udp.c#L2429">2429</a>         if (<a href="ident?i=v">v</a> == <a href="ident?i=SEQ_START_TOKEN">SEQ_START_TOKEN</a>)
<a name="L2430" href="source/net/ipv4/udp.c#L2430">2430</a>                 <a href="ident?i=seq_puts">seq_puts</a>(<a href="ident?i=seq">seq</a>, <i>"  sl  local_address rem_address   st tx_queue "</i>
<a name="L2431" href="source/net/ipv4/udp.c#L2431">2431</a>                            <i>"rx_queue tr tm-&gt;when retrnsmt   uid  timeout "</i>
<a name="L2432" href="source/net/ipv4/udp.c#L2432">2432</a>                            <i>"inode ref pointer drops"</i>);
<a name="L2433" href="source/net/ipv4/udp.c#L2433">2433</a>         else {
<a name="L2434" href="source/net/ipv4/udp.c#L2434">2434</a>                 struct <a href="ident?i=udp_iter_state">udp_iter_state</a> *<a href="ident?i=state">state</a> = <a href="ident?i=seq">seq</a>-&gt;<a href="ident?i=private">private</a>;
<a name="L2435" href="source/net/ipv4/udp.c#L2435">2435</a> 
<a name="L2436" href="source/net/ipv4/udp.c#L2436">2436</a>                 <a href="ident?i=udp4_format_sock">udp4_format_sock</a>(<a href="ident?i=v">v</a>, <a href="ident?i=seq">seq</a>, <a href="ident?i=state">state</a>-&gt;<a href="ident?i=bucket">bucket</a>);
<a name="L2437" href="source/net/ipv4/udp.c#L2437">2437</a>         }
<a name="L2438" href="source/net/ipv4/udp.c#L2438">2438</a>         <a href="ident?i=seq_pad">seq_pad</a>(<a href="ident?i=seq">seq</a>, <i>'\n'</i>);
<a name="L2439" href="source/net/ipv4/udp.c#L2439">2439</a>         return 0;
<a name="L2440" href="source/net/ipv4/udp.c#L2440">2440</a> }
<a name="L2441" href="source/net/ipv4/udp.c#L2441">2441</a> 
<a name="L2442" href="source/net/ipv4/udp.c#L2442">2442</a> static const struct <a href="ident?i=file_operations">file_operations</a> <a href="ident?i=udp_afinfo_seq_fops">udp_afinfo_seq_fops</a> = {
<a name="L2443" href="source/net/ipv4/udp.c#L2443">2443</a>         .owner    = <a href="ident?i=THIS_MODULE">THIS_MODULE</a>,
<a name="L2444" href="source/net/ipv4/udp.c#L2444">2444</a>         .<a href="ident?i=open">open</a>     = <a href="ident?i=udp_seq_open">udp_seq_open</a>,
<a name="L2445" href="source/net/ipv4/udp.c#L2445">2445</a>         .<a href="ident?i=read">read</a>     = <a href="ident?i=seq_read">seq_read</a>,
<a name="L2446" href="source/net/ipv4/udp.c#L2446">2446</a>         .llseek   = <a href="ident?i=seq_lseek">seq_lseek</a>,
<a name="L2447" href="source/net/ipv4/udp.c#L2447">2447</a>         .<a href="ident?i=release">release</a>  = <a href="ident?i=seq_release_net">seq_release_net</a>
<a name="L2448" href="source/net/ipv4/udp.c#L2448">2448</a> };
<a name="L2449" href="source/net/ipv4/udp.c#L2449">2449</a> 
<a name="L2450" href="source/net/ipv4/udp.c#L2450">2450</a> <b><i>/* ------------------------------------------------------------------------ */</i></b>
<a name="L2451" href="source/net/ipv4/udp.c#L2451">2451</a> static struct <a href="ident?i=udp_seq_afinfo">udp_seq_afinfo</a> <a href="ident?i=udp4_seq_afinfo">udp4_seq_afinfo</a> = {
<a name="L2452" href="source/net/ipv4/udp.c#L2452">2452</a>         .<a href="ident?i=name">name</a>           = <i>"udp"</i>,
<a name="L2453" href="source/net/ipv4/udp.c#L2453">2453</a>         .<a href="ident?i=family">family</a>         = <a href="ident?i=AF_INET">AF_INET</a>,
<a name="L2454" href="source/net/ipv4/udp.c#L2454">2454</a>         .<a href="ident?i=udp_table">udp_table</a>      = &amp;<a href="ident?i=udp_table">udp_table</a>,
<a name="L2455" href="source/net/ipv4/udp.c#L2455">2455</a>         .seq_fops       = &amp;<a href="ident?i=udp_afinfo_seq_fops">udp_afinfo_seq_fops</a>,
<a name="L2456" href="source/net/ipv4/udp.c#L2456">2456</a>         .seq_ops        = {
<a name="L2457" href="source/net/ipv4/udp.c#L2457">2457</a>                 .<a href="ident?i=show">show</a>           = <a href="ident?i=udp4_seq_show">udp4_seq_show</a>,
<a name="L2458" href="source/net/ipv4/udp.c#L2458">2458</a>         },
<a name="L2459" href="source/net/ipv4/udp.c#L2459">2459</a> };
<a name="L2460" href="source/net/ipv4/udp.c#L2460">2460</a> 
<a name="L2461" href="source/net/ipv4/udp.c#L2461">2461</a> static int <a href="ident?i=__net_init">__net_init</a> <a href="ident?i=udp4_proc_init_net">udp4_proc_init_net</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>)
<a name="L2462" href="source/net/ipv4/udp.c#L2462">2462</a> {
<a name="L2463" href="source/net/ipv4/udp.c#L2463">2463</a>         return <a href="ident?i=udp_proc_register">udp_proc_register</a>(<a href="ident?i=net">net</a>, &amp;<a href="ident?i=udp4_seq_afinfo">udp4_seq_afinfo</a>);
<a name="L2464" href="source/net/ipv4/udp.c#L2464">2464</a> }
<a name="L2465" href="source/net/ipv4/udp.c#L2465">2465</a> 
<a name="L2466" href="source/net/ipv4/udp.c#L2466">2466</a> static void <a href="ident?i=__net_exit">__net_exit</a> <a href="ident?i=udp4_proc_exit_net">udp4_proc_exit_net</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>)
<a name="L2467" href="source/net/ipv4/udp.c#L2467">2467</a> {
<a name="L2468" href="source/net/ipv4/udp.c#L2468">2468</a>         <a href="ident?i=udp_proc_unregister">udp_proc_unregister</a>(<a href="ident?i=net">net</a>, &amp;<a href="ident?i=udp4_seq_afinfo">udp4_seq_afinfo</a>);
<a name="L2469" href="source/net/ipv4/udp.c#L2469">2469</a> }
<a name="L2470" href="source/net/ipv4/udp.c#L2470">2470</a> 
<a name="L2471" href="source/net/ipv4/udp.c#L2471">2471</a> static struct <a href="ident?i=pernet_operations">pernet_operations</a> <a href="ident?i=udp4_net_ops">udp4_net_ops</a> = {
<a name="L2472" href="source/net/ipv4/udp.c#L2472">2472</a>         .<a href="ident?i=init">init</a> = <a href="ident?i=udp4_proc_init_net">udp4_proc_init_net</a>,
<a name="L2473" href="source/net/ipv4/udp.c#L2473">2473</a>         .<a href="ident?i=exit">exit</a> = <a href="ident?i=udp4_proc_exit_net">udp4_proc_exit_net</a>,
<a name="L2474" href="source/net/ipv4/udp.c#L2474">2474</a> };
<a name="L2475" href="source/net/ipv4/udp.c#L2475">2475</a> 
<a name="L2476" href="source/net/ipv4/udp.c#L2476">2476</a> int <a href="ident?i=__init">__init</a> <a href="ident?i=udp4_proc_init">udp4_proc_init</a>(void)
<a name="L2477" href="source/net/ipv4/udp.c#L2477">2477</a> {
<a name="L2478" href="source/net/ipv4/udp.c#L2478">2478</a>         return <a href="ident?i=register_pernet_subsys">register_pernet_subsys</a>(&amp;<a href="ident?i=udp4_net_ops">udp4_net_ops</a>);
<a name="L2479" href="source/net/ipv4/udp.c#L2479">2479</a> }
<a name="L2480" href="source/net/ipv4/udp.c#L2480">2480</a> 
<a name="L2481" href="source/net/ipv4/udp.c#L2481">2481</a> void <a href="ident?i=udp4_proc_exit">udp4_proc_exit</a>(void)
<a name="L2482" href="source/net/ipv4/udp.c#L2482">2482</a> {
<a name="L2483" href="source/net/ipv4/udp.c#L2483">2483</a>         <a href="ident?i=unregister_pernet_subsys">unregister_pernet_subsys</a>(&amp;<a href="ident?i=udp4_net_ops">udp4_net_ops</a>);
<a name="L2484" href="source/net/ipv4/udp.c#L2484">2484</a> }
<a name="L2485" href="source/net/ipv4/udp.c#L2485">2485</a> #endif <b><i>/* CONFIG_PROC_FS */</i></b>
<a name="L2486" href="source/net/ipv4/udp.c#L2486">2486</a> 
<a name="L2487" href="source/net/ipv4/udp.c#L2487">2487</a> static <a href="ident?i=__initdata">__initdata</a> unsigned long <a href="ident?i=uhash_entries">uhash_entries</a>;
<a name="L2488" href="source/net/ipv4/udp.c#L2488">2488</a> static int <a href="ident?i=__init">__init</a> <a href="ident?i=set_uhash_entries">set_uhash_entries</a>(char *<a href="ident?i=str">str</a>)
<a name="L2489" href="source/net/ipv4/udp.c#L2489">2489</a> {
<a name="L2490" href="source/net/ipv4/udp.c#L2490">2490</a>         <a href="ident?i=ssize_t">ssize_t</a> <a href="ident?i=ret">ret</a>;
<a name="L2491" href="source/net/ipv4/udp.c#L2491">2491</a> 
<a name="L2492" href="source/net/ipv4/udp.c#L2492">2492</a>         if (!<a href="ident?i=str">str</a>)
<a name="L2493" href="source/net/ipv4/udp.c#L2493">2493</a>                 return 0;
<a name="L2494" href="source/net/ipv4/udp.c#L2494">2494</a> 
<a name="L2495" href="source/net/ipv4/udp.c#L2495">2495</a>         <a href="ident?i=ret">ret</a> = <a href="ident?i=kstrtoul">kstrtoul</a>(<a href="ident?i=str">str</a>, 0, &amp;<a href="ident?i=uhash_entries">uhash_entries</a>);
<a name="L2496" href="source/net/ipv4/udp.c#L2496">2496</a>         if (<a href="ident?i=ret">ret</a>)
<a name="L2497" href="source/net/ipv4/udp.c#L2497">2497</a>                 return 0;
<a name="L2498" href="source/net/ipv4/udp.c#L2498">2498</a> 
<a name="L2499" href="source/net/ipv4/udp.c#L2499">2499</a>         if (<a href="ident?i=uhash_entries">uhash_entries</a> &amp;&amp; <a href="ident?i=uhash_entries">uhash_entries</a> &lt; <a href="ident?i=UDP_HTABLE_SIZE_MIN">UDP_HTABLE_SIZE_MIN</a>)
<a name="L2500" href="source/net/ipv4/udp.c#L2500">2500</a>                 <a href="ident?i=uhash_entries">uhash_entries</a> = <a href="ident?i=UDP_HTABLE_SIZE_MIN">UDP_HTABLE_SIZE_MIN</a>;
<a name="L2501" href="source/net/ipv4/udp.c#L2501">2501</a>         return 1;
<a name="L2502" href="source/net/ipv4/udp.c#L2502">2502</a> }
<a name="L2503" href="source/net/ipv4/udp.c#L2503">2503</a> <a href="ident?i=__setup">__setup</a>(<i>"uhash_entries="</i>, <a href="ident?i=set_uhash_entries">set_uhash_entries</a>);
<a name="L2504" href="source/net/ipv4/udp.c#L2504">2504</a> 
<a name="L2505" href="source/net/ipv4/udp.c#L2505">2505</a> void <a href="ident?i=__init">__init</a> <a href="ident?i=udp_table_init">udp_table_init</a>(struct <a href="ident?i=udp_table">udp_table</a> *<a href="ident?i=table">table</a>, const char *<a href="ident?i=name">name</a>)
<a name="L2506" href="source/net/ipv4/udp.c#L2506">2506</a> {
<a name="L2507" href="source/net/ipv4/udp.c#L2507">2507</a>         unsigned int <a href="ident?i=i">i</a>;
<a name="L2508" href="source/net/ipv4/udp.c#L2508">2508</a> 
<a name="L2509" href="source/net/ipv4/udp.c#L2509">2509</a>         <a href="ident?i=table">table</a>-&gt;<a href="ident?i=hash">hash</a> = <a href="ident?i=alloc_large_system_hash">alloc_large_system_hash</a>(<a href="ident?i=name">name</a>,
<a name="L2510" href="source/net/ipv4/udp.c#L2510">2510</a>                                               2 * sizeof(struct <a href="ident?i=udp_hslot">udp_hslot</a>),
<a name="L2511" href="source/net/ipv4/udp.c#L2511">2511</a>                                               <a href="ident?i=uhash_entries">uhash_entries</a>,
<a name="L2512" href="source/net/ipv4/udp.c#L2512">2512</a>                                               21, <b><i>/* one slot per 2 MB */</i></b>
<a name="L2513" href="source/net/ipv4/udp.c#L2513">2513</a>                                               0,
<a name="L2514" href="source/net/ipv4/udp.c#L2514">2514</a>                                               &amp;<a href="ident?i=table">table</a>-&gt;<a href="ident?i=log">log</a>,
<a name="L2515" href="source/net/ipv4/udp.c#L2515">2515</a>                                               &amp;<a href="ident?i=table">table</a>-&gt;<a href="ident?i=mask">mask</a>,
<a name="L2516" href="source/net/ipv4/udp.c#L2516">2516</a>                                               <a href="ident?i=UDP_HTABLE_SIZE_MIN">UDP_HTABLE_SIZE_MIN</a>,
<a name="L2517" href="source/net/ipv4/udp.c#L2517">2517</a>                                               64 * 1024);
<a name="L2518" href="source/net/ipv4/udp.c#L2518">2518</a> 
<a name="L2519" href="source/net/ipv4/udp.c#L2519">2519</a>         <a href="ident?i=table">table</a>-&gt;hash2 = <a href="ident?i=table">table</a>-&gt;<a href="ident?i=hash">hash</a> + (<a href="ident?i=table">table</a>-&gt;<a href="ident?i=mask">mask</a> + 1);
<a name="L2520" href="source/net/ipv4/udp.c#L2520">2520</a>         for (<a href="ident?i=i">i</a> = 0; <a href="ident?i=i">i</a> &lt;= <a href="ident?i=table">table</a>-&gt;<a href="ident?i=mask">mask</a>; <a href="ident?i=i">i</a>++) {
<a name="L2521" href="source/net/ipv4/udp.c#L2521">2521</a>                 <a href="ident?i=INIT_HLIST_NULLS_HEAD">INIT_HLIST_NULLS_HEAD</a>(&amp;<a href="ident?i=table">table</a>-&gt;<a href="ident?i=hash">hash</a>[<a href="ident?i=i">i</a>].<a href="ident?i=head">head</a>, <a href="ident?i=i">i</a>);
<a name="L2522" href="source/net/ipv4/udp.c#L2522">2522</a>                 <a href="ident?i=table">table</a>-&gt;<a href="ident?i=hash">hash</a>[<a href="ident?i=i">i</a>].<a href="ident?i=count">count</a> = 0;
<a name="L2523" href="source/net/ipv4/udp.c#L2523">2523</a>                 <a href="ident?i=spin_lock_init">spin_lock_init</a>(&amp;<a href="ident?i=table">table</a>-&gt;<a href="ident?i=hash">hash</a>[<a href="ident?i=i">i</a>].<a href="ident?i=lock">lock</a>);
<a name="L2524" href="source/net/ipv4/udp.c#L2524">2524</a>         }
<a name="L2525" href="source/net/ipv4/udp.c#L2525">2525</a>         for (<a href="ident?i=i">i</a> = 0; <a href="ident?i=i">i</a> &lt;= <a href="ident?i=table">table</a>-&gt;<a href="ident?i=mask">mask</a>; <a href="ident?i=i">i</a>++) {
<a name="L2526" href="source/net/ipv4/udp.c#L2526">2526</a>                 <a href="ident?i=INIT_HLIST_NULLS_HEAD">INIT_HLIST_NULLS_HEAD</a>(&amp;<a href="ident?i=table">table</a>-&gt;hash2[<a href="ident?i=i">i</a>].<a href="ident?i=head">head</a>, <a href="ident?i=i">i</a>);
<a name="L2527" href="source/net/ipv4/udp.c#L2527">2527</a>                 <a href="ident?i=table">table</a>-&gt;hash2[<a href="ident?i=i">i</a>].<a href="ident?i=count">count</a> = 0;
<a name="L2528" href="source/net/ipv4/udp.c#L2528">2528</a>                 <a href="ident?i=spin_lock_init">spin_lock_init</a>(&amp;<a href="ident?i=table">table</a>-&gt;hash2[<a href="ident?i=i">i</a>].<a href="ident?i=lock">lock</a>);
<a name="L2529" href="source/net/ipv4/udp.c#L2529">2529</a>         }
<a name="L2530" href="source/net/ipv4/udp.c#L2530">2530</a> }
<a name="L2531" href="source/net/ipv4/udp.c#L2531">2531</a> 
<a name="L2532" href="source/net/ipv4/udp.c#L2532">2532</a> <a href="ident?i=u32">u32</a> <a href="ident?i=udp_flow_hashrnd">udp_flow_hashrnd</a>(void)
<a name="L2533" href="source/net/ipv4/udp.c#L2533">2533</a> {
<a name="L2534" href="source/net/ipv4/udp.c#L2534">2534</a>         static <a href="ident?i=u32">u32</a> hashrnd <a href="ident?i=__read_mostly">__read_mostly</a>;
<a name="L2535" href="source/net/ipv4/udp.c#L2535">2535</a> 
<a name="L2536" href="source/net/ipv4/udp.c#L2536">2536</a>         <a href="ident?i=net_get_random_once">net_get_random_once</a>(&amp;hashrnd, sizeof(hashrnd));
<a name="L2537" href="source/net/ipv4/udp.c#L2537">2537</a> 
<a name="L2538" href="source/net/ipv4/udp.c#L2538">2538</a>         return hashrnd;
<a name="L2539" href="source/net/ipv4/udp.c#L2539">2539</a> }
<a name="L2540" href="source/net/ipv4/udp.c#L2540">2540</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=udp_flow_hashrnd">udp_flow_hashrnd</a>);
<a name="L2541" href="source/net/ipv4/udp.c#L2541">2541</a> 
<a name="L2542" href="source/net/ipv4/udp.c#L2542">2542</a> void <a href="ident?i=__init">__init</a> <a href="ident?i=udp_init">udp_init</a>(void)
<a name="L2543" href="source/net/ipv4/udp.c#L2543">2543</a> {
<a name="L2544" href="source/net/ipv4/udp.c#L2544">2544</a>         unsigned long <a href="ident?i=limit">limit</a>;
<a name="L2545" href="source/net/ipv4/udp.c#L2545">2545</a> 
<a name="L2546" href="source/net/ipv4/udp.c#L2546">2546</a>         <a href="ident?i=udp_table_init">udp_table_init</a>(&amp;<a href="ident?i=udp_table">udp_table</a>, <i>"UDP"</i>);
<a name="L2547" href="source/net/ipv4/udp.c#L2547">2547</a>         <a href="ident?i=limit">limit</a> = <a href="ident?i=nr_free_buffer_pages">nr_free_buffer_pages</a>() / 8;
<a name="L2548" href="source/net/ipv4/udp.c#L2548">2548</a>         <a href="ident?i=limit">limit</a> = <a href="ident?i=max">max</a>(<a href="ident?i=limit">limit</a>, 128UL);
<a name="L2549" href="source/net/ipv4/udp.c#L2549">2549</a>         <a href="ident?i=sysctl_udp_mem">sysctl_udp_mem</a>[0] = <a href="ident?i=limit">limit</a> / 4 * 3;
<a name="L2550" href="source/net/ipv4/udp.c#L2550">2550</a>         <a href="ident?i=sysctl_udp_mem">sysctl_udp_mem</a>[1] = <a href="ident?i=limit">limit</a>;
<a name="L2551" href="source/net/ipv4/udp.c#L2551">2551</a>         <a href="ident?i=sysctl_udp_mem">sysctl_udp_mem</a>[2] = <a href="ident?i=sysctl_udp_mem">sysctl_udp_mem</a>[0] * 2;
<a name="L2552" href="source/net/ipv4/udp.c#L2552">2552</a> 
<a name="L2553" href="source/net/ipv4/udp.c#L2553">2553</a>         <a href="ident?i=sysctl_udp_rmem_min">sysctl_udp_rmem_min</a> = <a href="ident?i=SK_MEM_QUANTUM">SK_MEM_QUANTUM</a>;
<a name="L2554" href="source/net/ipv4/udp.c#L2554">2554</a>         <a href="ident?i=sysctl_udp_wmem_min">sysctl_udp_wmem_min</a> = <a href="ident?i=SK_MEM_QUANTUM">SK_MEM_QUANTUM</a>;
<a name="L2555" href="source/net/ipv4/udp.c#L2555">2555</a> }
<a name="L2556" href="source/net/ipv4/udp.c#L2556">2556</a> </pre></div><p>
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
