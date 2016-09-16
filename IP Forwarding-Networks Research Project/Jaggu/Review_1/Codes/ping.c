<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title>Linux/net/ipv4/ping.c - Linux Cross Reference - Free Electrons</title>
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
		 &nbsp;&bull;&nbsp;<b><i>source navigation</i></b> &nbsp;&bull;&nbsp;<a href="diff/net/ipv4/ping.c">diff markup</a> &nbsp;&bull;&nbsp;<a href="ident">identifier search</a> &nbsp;&bull;&nbsp;<a href="search">freetext search</a> &nbsp;&bull;&nbsp;
		</p>
	</div>
</div>

<div id="topbar">
  
  <p>Version: &nbsp;<a href="source/net/ipv4/ping.c?v=2.0.40">2.0.40</a>&nbsp;<a href="source/net/ipv4/ping.c?v=2.2.26">2.2.26</a>&nbsp;<a href="source/net/ipv4/ping.c?v=2.4.37">2.4.37</a>&nbsp;<a href="source/net/ipv4/ping.c?v=3.5">3.5</a>&nbsp;<a href="source/net/ipv4/ping.c?v=3.6">3.6</a>&nbsp;<a href="source/net/ipv4/ping.c?v=3.7">3.7</a>&nbsp;<a href="source/net/ipv4/ping.c?v=3.8">3.8</a>&nbsp;<a href="source/net/ipv4/ping.c?v=3.9">3.9</a>&nbsp;<a href="source/net/ipv4/ping.c?v=3.10">3.10</a>&nbsp;<a href="source/net/ipv4/ping.c?v=3.11">3.11</a>&nbsp;<a href="source/net/ipv4/ping.c?v=3.12">3.12</a>&nbsp;<a href="source/net/ipv4/ping.c?v=3.13">3.13</a>&nbsp;<a href="source/net/ipv4/ping.c?v=3.14">3.14</a>&nbsp;<a href="source/net/ipv4/ping.c?v=3.15">3.15</a>&nbsp;<a href="source/net/ipv4/ping.c?v=3.16">3.16</a>&nbsp;<a href="source/net/ipv4/ping.c?v=3.17">3.17</a>&nbsp;<a href="source/net/ipv4/ping.c?v=3.18">3.18</a>&nbsp;<a href="source/net/ipv4/ping.c?v=3.19">3.19</a>&nbsp;<a href="source/net/ipv4/ping.c?v=4.0">4.0</a>&nbsp;<b><i>4.1</i></b></p>
  
</div>

<h1><a href="source/">Linux</a>/<a href="source/net/">net</a>/<a href="source/net/ipv4/">ipv4</a>/<a href="source/net/ipv4/ping.c">ping.c</a></h1>
<div id="lxrcode"><pre>  <a name="L1" href="source/net/ipv4/ping.c#L1">1</a> <b><i>/*</i></b>
  <a name="L2" href="source/net/ipv4/ping.c#L2">2</a> <b><i> * INET         An implementation of the TCP/IP protocol suite for the LINUX</i></b>
  <a name="L3" href="source/net/ipv4/ping.c#L3">3</a> <b><i> *              operating system.  INET is implemented using the  BSD Socket</i></b>
  <a name="L4" href="source/net/ipv4/ping.c#L4">4</a> <b><i> *              interface as the means of communication with the user level.</i></b>
  <a name="L5" href="source/net/ipv4/ping.c#L5">5</a> <b><i> *</i></b>
  <a name="L6" href="source/net/ipv4/ping.c#L6">6</a> <b><i> *              "Ping" sockets</i></b>
  <a name="L7" href="source/net/ipv4/ping.c#L7">7</a> <b><i> *</i></b>
  <a name="L8" href="source/net/ipv4/ping.c#L8">8</a> <b><i> *              This program is free software; you can redistribute it and/or</i></b>
  <a name="L9" href="source/net/ipv4/ping.c#L9">9</a> <b><i> *              modify it under the terms of the GNU General Public License</i></b>
 <a name="L10" href="source/net/ipv4/ping.c#L10">10</a> <b><i> *              as published by the Free Software Foundation; either version</i></b>
 <a name="L11" href="source/net/ipv4/ping.c#L11">11</a> <b><i> *              2 of the License, or (at your option) any later version.</i></b>
 <a name="L12" href="source/net/ipv4/ping.c#L12">12</a> <b><i> *</i></b>
 <a name="L13" href="source/net/ipv4/ping.c#L13">13</a> <b><i> * Based on ipv4/udp.c code.</i></b>
 <a name="L14" href="source/net/ipv4/ping.c#L14">14</a> <b><i> *</i></b>
 <a name="L15" href="source/net/ipv4/ping.c#L15">15</a> <b><i> * Authors:     Vasiliy Kulikov / Openwall (for Linux 2.6),</i></b>
 <a name="L16" href="source/net/ipv4/ping.c#L16">16</a> <b><i> *              Pavel Kankovsky (for Linux 2.4.32)</i></b>
 <a name="L17" href="source/net/ipv4/ping.c#L17">17</a> <b><i> *</i></b>
 <a name="L18" href="source/net/ipv4/ping.c#L18">18</a> <b><i> * Pavel gave all rights to bugs to Vasiliy,</i></b>
 <a name="L19" href="source/net/ipv4/ping.c#L19">19</a> <b><i> * none of the bugs are Pavel's now.</i></b>
 <a name="L20" href="source/net/ipv4/ping.c#L20">20</a> <b><i> *</i></b>
 <a name="L21" href="source/net/ipv4/ping.c#L21">21</a> <b><i> */</i></b>
 <a name="L22" href="source/net/ipv4/ping.c#L22">22</a> 
 <a name="L23" href="source/net/ipv4/ping.c#L23">23</a> #include &lt;linux/uaccess.h&gt;
 <a name="L24" href="source/net/ipv4/ping.c#L24">24</a> #include &lt;linux/types.h&gt;
 <a name="L25" href="source/net/ipv4/ping.c#L25">25</a> #include &lt;linux/fcntl.h&gt;
 <a name="L26" href="source/net/ipv4/ping.c#L26">26</a> #include &lt;linux/socket.h&gt;
 <a name="L27" href="source/net/ipv4/ping.c#L27">27</a> #include &lt;linux/sockios.h&gt;
 <a name="L28" href="source/net/ipv4/ping.c#L28">28</a> #include &lt;linux/in.h&gt;
 <a name="L29" href="source/net/ipv4/ping.c#L29">29</a> #include &lt;linux/errno.h&gt;
 <a name="L30" href="source/net/ipv4/ping.c#L30">30</a> #include &lt;linux/timer.h&gt;
 <a name="L31" href="source/net/ipv4/ping.c#L31">31</a> #include &lt;linux/mm.h&gt;
 <a name="L32" href="source/net/ipv4/ping.c#L32">32</a> #include &lt;linux/inet.h&gt;
 <a name="L33" href="source/net/ipv4/ping.c#L33">33</a> #include &lt;linux/netdevice.h&gt;
 <a name="L34" href="source/net/ipv4/ping.c#L34">34</a> #include &lt;net/snmp.h&gt;
 <a name="L35" href="source/net/ipv4/ping.c#L35">35</a> #include &lt;net/ip.h&gt;
 <a name="L36" href="source/net/ipv4/ping.c#L36">36</a> #include &lt;net/icmp.h&gt;
 <a name="L37" href="source/net/ipv4/ping.c#L37">37</a> #include &lt;net/protocol.h&gt;
 <a name="L38" href="source/net/ipv4/ping.c#L38">38</a> #include &lt;linux/skbuff.h&gt;
 <a name="L39" href="source/net/ipv4/ping.c#L39">39</a> #include &lt;linux/proc_fs.h&gt;
 <a name="L40" href="source/net/ipv4/ping.c#L40">40</a> #include &lt;linux/export.h&gt;
 <a name="L41" href="source/net/ipv4/ping.c#L41">41</a> #include &lt;net/sock.h&gt;
 <a name="L42" href="source/net/ipv4/ping.c#L42">42</a> #include &lt;net/ping.h&gt;
 <a name="L43" href="source/net/ipv4/ping.c#L43">43</a> #include &lt;net/udp.h&gt;
 <a name="L44" href="source/net/ipv4/ping.c#L44">44</a> #include &lt;net/route.h&gt;
 <a name="L45" href="source/net/ipv4/ping.c#L45">45</a> #include &lt;net/inet_common.h&gt;
 <a name="L46" href="source/net/ipv4/ping.c#L46">46</a> #include &lt;net/checksum.h&gt;
 <a name="L47" href="source/net/ipv4/ping.c#L47">47</a> 
 <a name="L48" href="source/net/ipv4/ping.c#L48">48</a> #if <a href="ident?i=IS_ENABLED">IS_ENABLED</a>(CONFIG_IPV6)
 <a name="L49" href="source/net/ipv4/ping.c#L49">49</a> #include &lt;linux/in6.h&gt;
 <a name="L50" href="source/net/ipv4/ping.c#L50">50</a> #include &lt;linux/icmpv6.h&gt;
 <a name="L51" href="source/net/ipv4/ping.c#L51">51</a> #include &lt;net/addrconf.h&gt;
 <a name="L52" href="source/net/ipv4/ping.c#L52">52</a> #include &lt;net/ipv6.h&gt;
 <a name="L53" href="source/net/ipv4/ping.c#L53">53</a> #include &lt;net/transp_v6.h&gt;
 <a name="L54" href="source/net/ipv4/ping.c#L54">54</a> #endif
 <a name="L55" href="source/net/ipv4/ping.c#L55">55</a> 
 <a name="L56" href="source/net/ipv4/ping.c#L56">56</a> struct <a href="ident?i=ping_table">ping_table</a> {
 <a name="L57" href="source/net/ipv4/ping.c#L57">57</a>         struct <a href="ident?i=hlist_nulls_head">hlist_nulls_head</a> <a href="ident?i=hash">hash</a>[<a href="ident?i=PING_HTABLE_SIZE">PING_HTABLE_SIZE</a>];
 <a name="L58" href="source/net/ipv4/ping.c#L58">58</a>         <a href="ident?i=rwlock_t">rwlock_t</a>                <a href="ident?i=lock">lock</a>;
 <a name="L59" href="source/net/ipv4/ping.c#L59">59</a> };
 <a name="L60" href="source/net/ipv4/ping.c#L60">60</a> 
 <a name="L61" href="source/net/ipv4/ping.c#L61">61</a> static struct <a href="ident?i=ping_table">ping_table</a> <a href="ident?i=ping_table">ping_table</a>;
 <a name="L62" href="source/net/ipv4/ping.c#L62">62</a> struct <a href="ident?i=pingv6_ops">pingv6_ops</a> <a href="ident?i=pingv6_ops">pingv6_ops</a>;
 <a name="L63" href="source/net/ipv4/ping.c#L63">63</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=pingv6_ops">pingv6_ops</a>);
 <a name="L64" href="source/net/ipv4/ping.c#L64">64</a> 
 <a name="L65" href="source/net/ipv4/ping.c#L65">65</a> static <a href="ident?i=u16">u16</a> <a href="ident?i=ping_port_rover">ping_port_rover</a>;
 <a name="L66" href="source/net/ipv4/ping.c#L66">66</a> 
 <a name="L67" href="source/net/ipv4/ping.c#L67">67</a> static inline <a href="ident?i=u32">u32</a> <a href="ident?i=ping_hashfn">ping_hashfn</a>(const struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>, <a href="ident?i=u32">u32</a> <a href="ident?i=num">num</a>, <a href="ident?i=u32">u32</a> <a href="ident?i=mask">mask</a>)
 <a name="L68" href="source/net/ipv4/ping.c#L68">68</a> {
 <a name="L69" href="source/net/ipv4/ping.c#L69">69</a>         <a href="ident?i=u32">u32</a> <a href="ident?i=res">res</a> = (<a href="ident?i=num">num</a> + <a href="ident?i=net_hash_mix">net_hash_mix</a>(<a href="ident?i=net">net</a>)) &amp; <a href="ident?i=mask">mask</a>;
 <a name="L70" href="source/net/ipv4/ping.c#L70">70</a> 
 <a name="L71" href="source/net/ipv4/ping.c#L71">71</a>         <a href="ident?i=pr_debug">pr_debug</a>(<i>"hash(%u) = %u\n"</i>, <a href="ident?i=num">num</a>, <a href="ident?i=res">res</a>);
 <a name="L72" href="source/net/ipv4/ping.c#L72">72</a>         return <a href="ident?i=res">res</a>;
 <a name="L73" href="source/net/ipv4/ping.c#L73">73</a> }
 <a name="L74" href="source/net/ipv4/ping.c#L74">74</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=ping_hash">ping_hash</a>);
 <a name="L75" href="source/net/ipv4/ping.c#L75">75</a> 
 <a name="L76" href="source/net/ipv4/ping.c#L76">76</a> static inline struct <a href="ident?i=hlist_nulls_head">hlist_nulls_head</a> *<a href="ident?i=ping_hashslot">ping_hashslot</a>(struct <a href="ident?i=ping_table">ping_table</a> *<a href="ident?i=table">table</a>,
 <a name="L77" href="source/net/ipv4/ping.c#L77">77</a>                                              struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>, unsigned int <a href="ident?i=num">num</a>)
 <a name="L78" href="source/net/ipv4/ping.c#L78">78</a> {
 <a name="L79" href="source/net/ipv4/ping.c#L79">79</a>         return &amp;<a href="ident?i=table">table</a>-&gt;<a href="ident?i=hash">hash</a>[<a href="ident?i=ping_hashfn">ping_hashfn</a>(<a href="ident?i=net">net</a>, <a href="ident?i=num">num</a>, <a href="ident?i=PING_HTABLE_MASK">PING_HTABLE_MASK</a>)];
 <a name="L80" href="source/net/ipv4/ping.c#L80">80</a> }
 <a name="L81" href="source/net/ipv4/ping.c#L81">81</a> 
 <a name="L82" href="source/net/ipv4/ping.c#L82">82</a> int <a href="ident?i=ping_get_port">ping_get_port</a>(struct <a href="ident?i=sock">sock</a> *sk, unsigned short <a href="ident?i=ident">ident</a>)
 <a name="L83" href="source/net/ipv4/ping.c#L83">83</a> {
 <a name="L84" href="source/net/ipv4/ping.c#L84">84</a>         struct <a href="ident?i=hlist_nulls_node">hlist_nulls_node</a> *<a href="ident?i=node">node</a>;
 <a name="L85" href="source/net/ipv4/ping.c#L85">85</a>         struct <a href="ident?i=hlist_nulls_head">hlist_nulls_head</a> *hlist;
 <a name="L86" href="source/net/ipv4/ping.c#L86">86</a>         struct <a href="ident?i=inet_sock">inet_sock</a> *isk, *isk2;
 <a name="L87" href="source/net/ipv4/ping.c#L87">87</a>         struct <a href="ident?i=sock">sock</a> *sk2 = <a href="ident?i=NULL">NULL</a>;
 <a name="L88" href="source/net/ipv4/ping.c#L88">88</a> 
 <a name="L89" href="source/net/ipv4/ping.c#L89">89</a>         isk = <a href="ident?i=inet_sk">inet_sk</a>(sk);
 <a name="L90" href="source/net/ipv4/ping.c#L90">90</a>         <a href="ident?i=write_lock_bh">write_lock_bh</a>(&amp;<a href="ident?i=ping_table">ping_table</a>.<a href="ident?i=lock">lock</a>);
 <a name="L91" href="source/net/ipv4/ping.c#L91">91</a>         if (<a href="ident?i=ident">ident</a> == 0) {
 <a name="L92" href="source/net/ipv4/ping.c#L92">92</a>                 <a href="ident?i=u32">u32</a> <a href="ident?i=i">i</a>;
 <a name="L93" href="source/net/ipv4/ping.c#L93">93</a>                 <a href="ident?i=u16">u16</a> <a href="ident?i=result">result</a> = <a href="ident?i=ping_port_rover">ping_port_rover</a> + 1;
 <a name="L94" href="source/net/ipv4/ping.c#L94">94</a> 
 <a name="L95" href="source/net/ipv4/ping.c#L95">95</a>                 for (<a href="ident?i=i">i</a> = 0; <a href="ident?i=i">i</a> &lt; (1L &lt;&lt; 16); <a href="ident?i=i">i</a>++, <a href="ident?i=result">result</a>++) {
 <a name="L96" href="source/net/ipv4/ping.c#L96">96</a>                         if (!<a href="ident?i=result">result</a>)
 <a name="L97" href="source/net/ipv4/ping.c#L97">97</a>                                 <a href="ident?i=result">result</a>++; <b><i>/* avoid zero */</i></b>
 <a name="L98" href="source/net/ipv4/ping.c#L98">98</a>                         hlist = <a href="ident?i=ping_hashslot">ping_hashslot</a>(&amp;<a href="ident?i=ping_table">ping_table</a>, <a href="ident?i=sock_net">sock_net</a>(sk),
 <a name="L99" href="source/net/ipv4/ping.c#L99">99</a>                                             <a href="ident?i=result">result</a>);
<a name="L100" href="source/net/ipv4/ping.c#L100">100</a>                         <a href="ident?i=ping_portaddr_for_each_entry">ping_portaddr_for_each_entry</a>(sk2, <a href="ident?i=node">node</a>, hlist) {
<a name="L101" href="source/net/ipv4/ping.c#L101">101</a>                                 isk2 = <a href="ident?i=inet_sk">inet_sk</a>(sk2);
<a name="L102" href="source/net/ipv4/ping.c#L102">102</a> 
<a name="L103" href="source/net/ipv4/ping.c#L103">103</a>                                 if (isk2-&gt;<a href="ident?i=inet_num">inet_num</a> == <a href="ident?i=result">result</a>)
<a name="L104" href="source/net/ipv4/ping.c#L104">104</a>                                         goto next_port;
<a name="L105" href="source/net/ipv4/ping.c#L105">105</a>                         }
<a name="L106" href="source/net/ipv4/ping.c#L106">106</a> 
<a name="L107" href="source/net/ipv4/ping.c#L107">107</a>                         <b><i>/* found */</i></b>
<a name="L108" href="source/net/ipv4/ping.c#L108">108</a>                         <a href="ident?i=ping_port_rover">ping_port_rover</a> = <a href="ident?i=ident">ident</a> = <a href="ident?i=result">result</a>;
<a name="L109" href="source/net/ipv4/ping.c#L109">109</a>                         break;
<a name="L110" href="source/net/ipv4/ping.c#L110">110</a> next_port:
<a name="L111" href="source/net/ipv4/ping.c#L111">111</a>                         ;
<a name="L112" href="source/net/ipv4/ping.c#L112">112</a>                 }
<a name="L113" href="source/net/ipv4/ping.c#L113">113</a>                 if (<a href="ident?i=i">i</a> &gt;= (1L &lt;&lt; 16))
<a name="L114" href="source/net/ipv4/ping.c#L114">114</a>                         goto <a href="ident?i=fail">fail</a>;
<a name="L115" href="source/net/ipv4/ping.c#L115">115</a>         } else {
<a name="L116" href="source/net/ipv4/ping.c#L116">116</a>                 hlist = <a href="ident?i=ping_hashslot">ping_hashslot</a>(&amp;<a href="ident?i=ping_table">ping_table</a>, <a href="ident?i=sock_net">sock_net</a>(sk), <a href="ident?i=ident">ident</a>);
<a name="L117" href="source/net/ipv4/ping.c#L117">117</a>                 <a href="ident?i=ping_portaddr_for_each_entry">ping_portaddr_for_each_entry</a>(sk2, <a href="ident?i=node">node</a>, hlist) {
<a name="L118" href="source/net/ipv4/ping.c#L118">118</a>                         isk2 = <a href="ident?i=inet_sk">inet_sk</a>(sk2);
<a name="L119" href="source/net/ipv4/ping.c#L119">119</a> 
<a name="L120" href="source/net/ipv4/ping.c#L120">120</a>                         <b><i>/* BUG? Why is this reuse and not reuseaddr? ping.c</i></b>
<a name="L121" href="source/net/ipv4/ping.c#L121">121</a> <b><i>                         * doesn't turn off SO_REUSEADDR, and it doesn't expect</i></b>
<a name="L122" href="source/net/ipv4/ping.c#L122">122</a> <b><i>                         * that other ping processes can steal its packets.</i></b>
<a name="L123" href="source/net/ipv4/ping.c#L123">123</a> <b><i>                         */</i></b>
<a name="L124" href="source/net/ipv4/ping.c#L124">124</a>                         if ((isk2-&gt;<a href="ident?i=inet_num">inet_num</a> == <a href="ident?i=ident">ident</a>) &amp;&amp;
<a name="L125" href="source/net/ipv4/ping.c#L125">125</a>                             (sk2 != sk) &amp;&amp;
<a name="L126" href="source/net/ipv4/ping.c#L126">126</a>                             (!sk2-&gt;<a href="ident?i=sk_reuse">sk_reuse</a> || !sk-&gt;<a href="ident?i=sk_reuse">sk_reuse</a>))
<a name="L127" href="source/net/ipv4/ping.c#L127">127</a>                                 goto <a href="ident?i=fail">fail</a>;
<a name="L128" href="source/net/ipv4/ping.c#L128">128</a>                 }
<a name="L129" href="source/net/ipv4/ping.c#L129">129</a>         }
<a name="L130" href="source/net/ipv4/ping.c#L130">130</a> 
<a name="L131" href="source/net/ipv4/ping.c#L131">131</a>         <a href="ident?i=pr_debug">pr_debug</a>(<i>"found port/ident = %d\n"</i>, <a href="ident?i=ident">ident</a>);
<a name="L132" href="source/net/ipv4/ping.c#L132">132</a>         isk-&gt;<a href="ident?i=inet_num">inet_num</a> = <a href="ident?i=ident">ident</a>;
<a name="L133" href="source/net/ipv4/ping.c#L133">133</a>         if (<a href="ident?i=sk_unhashed">sk_unhashed</a>(sk)) {
<a name="L134" href="source/net/ipv4/ping.c#L134">134</a>                 <a href="ident?i=pr_debug">pr_debug</a>(<i>"was not hashed\n"</i>);
<a name="L135" href="source/net/ipv4/ping.c#L135">135</a>                 <a href="ident?i=sock_hold">sock_hold</a>(sk);
<a name="L136" href="source/net/ipv4/ping.c#L136">136</a>                 <a href="ident?i=hlist_nulls_add_head">hlist_nulls_add_head</a>(&amp;sk-&gt;<a href="ident?i=sk_nulls_node">sk_nulls_node</a>, hlist);
<a name="L137" href="source/net/ipv4/ping.c#L137">137</a>                 <a href="ident?i=sock_prot_inuse_add">sock_prot_inuse_add</a>(<a href="ident?i=sock_net">sock_net</a>(sk), sk-&gt;<a href="ident?i=sk_prot">sk_prot</a>, 1);
<a name="L138" href="source/net/ipv4/ping.c#L138">138</a>         }
<a name="L139" href="source/net/ipv4/ping.c#L139">139</a>         <a href="ident?i=write_unlock_bh">write_unlock_bh</a>(&amp;<a href="ident?i=ping_table">ping_table</a>.<a href="ident?i=lock">lock</a>);
<a name="L140" href="source/net/ipv4/ping.c#L140">140</a>         return 0;
<a name="L141" href="source/net/ipv4/ping.c#L141">141</a> 
<a name="L142" href="source/net/ipv4/ping.c#L142">142</a> <a href="ident?i=fail">fail</a>:
<a name="L143" href="source/net/ipv4/ping.c#L143">143</a>         <a href="ident?i=write_unlock_bh">write_unlock_bh</a>(&amp;<a href="ident?i=ping_table">ping_table</a>.<a href="ident?i=lock">lock</a>);
<a name="L144" href="source/net/ipv4/ping.c#L144">144</a>         return 1;
<a name="L145" href="source/net/ipv4/ping.c#L145">145</a> }
<a name="L146" href="source/net/ipv4/ping.c#L146">146</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=ping_get_port">ping_get_port</a>);
<a name="L147" href="source/net/ipv4/ping.c#L147">147</a> 
<a name="L148" href="source/net/ipv4/ping.c#L148">148</a> void <a href="ident?i=ping_hash">ping_hash</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L149" href="source/net/ipv4/ping.c#L149">149</a> {
<a name="L150" href="source/net/ipv4/ping.c#L150">150</a>         <a href="ident?i=pr_debug">pr_debug</a>(<i>"ping_hash(sk-&gt;port=%u)\n"</i>, <a href="ident?i=inet_sk">inet_sk</a>(sk)-&gt;<a href="ident?i=inet_num">inet_num</a>);
<a name="L151" href="source/net/ipv4/ping.c#L151">151</a>         <a href="ident?i=BUG">BUG</a>(); <b><i>/* "Please do not press this button again." */</i></b>
<a name="L152" href="source/net/ipv4/ping.c#L152">152</a> }
<a name="L153" href="source/net/ipv4/ping.c#L153">153</a> 
<a name="L154" href="source/net/ipv4/ping.c#L154">154</a> void <a href="ident?i=ping_unhash">ping_unhash</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L155" href="source/net/ipv4/ping.c#L155">155</a> {
<a name="L156" href="source/net/ipv4/ping.c#L156">156</a>         struct <a href="ident?i=inet_sock">inet_sock</a> *isk = <a href="ident?i=inet_sk">inet_sk</a>(sk);
<a name="L157" href="source/net/ipv4/ping.c#L157">157</a>         <a href="ident?i=pr_debug">pr_debug</a>(<i>"ping_unhash(isk=%p,isk-&gt;num=%u)\n"</i>, isk, isk-&gt;<a href="ident?i=inet_num">inet_num</a>);
<a name="L158" href="source/net/ipv4/ping.c#L158">158</a>         if (<a href="ident?i=sk_hashed">sk_hashed</a>(sk)) {
<a name="L159" href="source/net/ipv4/ping.c#L159">159</a>                 <a href="ident?i=write_lock_bh">write_lock_bh</a>(&amp;<a href="ident?i=ping_table">ping_table</a>.<a href="ident?i=lock">lock</a>);
<a name="L160" href="source/net/ipv4/ping.c#L160">160</a>                 <a href="ident?i=hlist_nulls_del">hlist_nulls_del</a>(&amp;sk-&gt;<a href="ident?i=sk_nulls_node">sk_nulls_node</a>);
<a name="L161" href="source/net/ipv4/ping.c#L161">161</a>                 <a href="ident?i=sk_nulls_node_init">sk_nulls_node_init</a>(&amp;sk-&gt;<a href="ident?i=sk_nulls_node">sk_nulls_node</a>);
<a name="L162" href="source/net/ipv4/ping.c#L162">162</a>                 <a href="ident?i=sock_put">sock_put</a>(sk);
<a name="L163" href="source/net/ipv4/ping.c#L163">163</a>                 isk-&gt;<a href="ident?i=inet_num">inet_num</a> = 0;
<a name="L164" href="source/net/ipv4/ping.c#L164">164</a>                 isk-&gt;inet_sport = 0;
<a name="L165" href="source/net/ipv4/ping.c#L165">165</a>                 <a href="ident?i=sock_prot_inuse_add">sock_prot_inuse_add</a>(<a href="ident?i=sock_net">sock_net</a>(sk), sk-&gt;<a href="ident?i=sk_prot">sk_prot</a>, -1);
<a name="L166" href="source/net/ipv4/ping.c#L166">166</a>                 <a href="ident?i=write_unlock_bh">write_unlock_bh</a>(&amp;<a href="ident?i=ping_table">ping_table</a>.<a href="ident?i=lock">lock</a>);
<a name="L167" href="source/net/ipv4/ping.c#L167">167</a>         }
<a name="L168" href="source/net/ipv4/ping.c#L168">168</a> }
<a name="L169" href="source/net/ipv4/ping.c#L169">169</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=ping_unhash">ping_unhash</a>);
<a name="L170" href="source/net/ipv4/ping.c#L170">170</a> 
<a name="L171" href="source/net/ipv4/ping.c#L171">171</a> static struct <a href="ident?i=sock">sock</a> *<a href="ident?i=ping_lookup">ping_lookup</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, <a href="ident?i=u16">u16</a> <a href="ident?i=ident">ident</a>)
<a name="L172" href="source/net/ipv4/ping.c#L172">172</a> {
<a name="L173" href="source/net/ipv4/ping.c#L173">173</a>         struct <a href="ident?i=hlist_nulls_head">hlist_nulls_head</a> *hslot = <a href="ident?i=ping_hashslot">ping_hashslot</a>(&amp;<a href="ident?i=ping_table">ping_table</a>, <a href="ident?i=net">net</a>, <a href="ident?i=ident">ident</a>);
<a name="L174" href="source/net/ipv4/ping.c#L174">174</a>         struct <a href="ident?i=sock">sock</a> *sk = <a href="ident?i=NULL">NULL</a>;
<a name="L175" href="source/net/ipv4/ping.c#L175">175</a>         struct <a href="ident?i=inet_sock">inet_sock</a> *isk;
<a name="L176" href="source/net/ipv4/ping.c#L176">176</a>         struct <a href="ident?i=hlist_nulls_node">hlist_nulls_node</a> *hnode;
<a name="L177" href="source/net/ipv4/ping.c#L177">177</a>         int dif = <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=dev">dev</a>-&gt;ifindex;
<a name="L178" href="source/net/ipv4/ping.c#L178">178</a> 
<a name="L179" href="source/net/ipv4/ping.c#L179">179</a>         if (<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=protocol">protocol</a> == <a href="ident?i=htons">htons</a>(<a href="ident?i=ETH_P_IP">ETH_P_IP</a>)) {
<a name="L180" href="source/net/ipv4/ping.c#L180">180</a>                 <a href="ident?i=pr_debug">pr_debug</a>(<i>"try to find: num = %d, daddr = %pI4, dif = %d\n"</i>,
<a name="L181" href="source/net/ipv4/ping.c#L181">181</a>                          (int)<a href="ident?i=ident">ident</a>, &amp;<a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=daddr">daddr</a>, dif);
<a name="L182" href="source/net/ipv4/ping.c#L182">182</a> #if <a href="ident?i=IS_ENABLED">IS_ENABLED</a>(CONFIG_IPV6)
<a name="L183" href="source/net/ipv4/ping.c#L183">183</a>         } else if (<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=protocol">protocol</a> == <a href="ident?i=htons">htons</a>(<a href="ident?i=ETH_P_IPV6">ETH_P_IPV6</a>)) {
<a name="L184" href="source/net/ipv4/ping.c#L184">184</a>                 <a href="ident?i=pr_debug">pr_debug</a>(<i>"try to find: num = %d, daddr = %pI6c, dif = %d\n"</i>,
<a name="L185" href="source/net/ipv4/ping.c#L185">185</a>                          (int)<a href="ident?i=ident">ident</a>, &amp;<a href="ident?i=ipv6_hdr">ipv6_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=daddr">daddr</a>, dif);
<a name="L186" href="source/net/ipv4/ping.c#L186">186</a> #endif
<a name="L187" href="source/net/ipv4/ping.c#L187">187</a>         }
<a name="L188" href="source/net/ipv4/ping.c#L188">188</a> 
<a name="L189" href="source/net/ipv4/ping.c#L189">189</a>         <a href="ident?i=read_lock_bh">read_lock_bh</a>(&amp;<a href="ident?i=ping_table">ping_table</a>.<a href="ident?i=lock">lock</a>);
<a name="L190" href="source/net/ipv4/ping.c#L190">190</a> 
<a name="L191" href="source/net/ipv4/ping.c#L191">191</a>         <a href="ident?i=ping_portaddr_for_each_entry">ping_portaddr_for_each_entry</a>(sk, hnode, hslot) {
<a name="L192" href="source/net/ipv4/ping.c#L192">192</a>                 isk = <a href="ident?i=inet_sk">inet_sk</a>(sk);
<a name="L193" href="source/net/ipv4/ping.c#L193">193</a> 
<a name="L194" href="source/net/ipv4/ping.c#L194">194</a>                 <a href="ident?i=pr_debug">pr_debug</a>(<i>"iterate\n"</i>);
<a name="L195" href="source/net/ipv4/ping.c#L195">195</a>                 if (isk-&gt;<a href="ident?i=inet_num">inet_num</a> != <a href="ident?i=ident">ident</a>)
<a name="L196" href="source/net/ipv4/ping.c#L196">196</a>                         continue;
<a name="L197" href="source/net/ipv4/ping.c#L197">197</a> 
<a name="L198" href="source/net/ipv4/ping.c#L198">198</a>                 if (<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=protocol">protocol</a> == <a href="ident?i=htons">htons</a>(<a href="ident?i=ETH_P_IP">ETH_P_IP</a>) &amp;&amp;
<a name="L199" href="source/net/ipv4/ping.c#L199">199</a>                     sk-&gt;<a href="ident?i=sk_family">sk_family</a> == <a href="ident?i=AF_INET">AF_INET</a>) {
<a name="L200" href="source/net/ipv4/ping.c#L200">200</a>                         <a href="ident?i=pr_debug">pr_debug</a>(<i>"found: %p: num=%d, daddr=%pI4, dif=%d\n"</i>, sk,
<a name="L201" href="source/net/ipv4/ping.c#L201">201</a>                                  (int) isk-&gt;<a href="ident?i=inet_num">inet_num</a>, &amp;isk-&gt;<a href="ident?i=inet_rcv_saddr">inet_rcv_saddr</a>,
<a name="L202" href="source/net/ipv4/ping.c#L202">202</a>                                  sk-&gt;<a href="ident?i=sk_bound_dev_if">sk_bound_dev_if</a>);
<a name="L203" href="source/net/ipv4/ping.c#L203">203</a> 
<a name="L204" href="source/net/ipv4/ping.c#L204">204</a>                         if (isk-&gt;<a href="ident?i=inet_rcv_saddr">inet_rcv_saddr</a> &amp;&amp;
<a name="L205" href="source/net/ipv4/ping.c#L205">205</a>                             isk-&gt;<a href="ident?i=inet_rcv_saddr">inet_rcv_saddr</a> != <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=daddr">daddr</a>)
<a name="L206" href="source/net/ipv4/ping.c#L206">206</a>                                 continue;
<a name="L207" href="source/net/ipv4/ping.c#L207">207</a> #if <a href="ident?i=IS_ENABLED">IS_ENABLED</a>(CONFIG_IPV6)
<a name="L208" href="source/net/ipv4/ping.c#L208">208</a>                 } else if (<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=protocol">protocol</a> == <a href="ident?i=htons">htons</a>(<a href="ident?i=ETH_P_IPV6">ETH_P_IPV6</a>) &amp;&amp;
<a name="L209" href="source/net/ipv4/ping.c#L209">209</a>                            sk-&gt;<a href="ident?i=sk_family">sk_family</a> == <a href="ident?i=AF_INET6">AF_INET6</a>) {
<a name="L210" href="source/net/ipv4/ping.c#L210">210</a> 
<a name="L211" href="source/net/ipv4/ping.c#L211">211</a>                         <a href="ident?i=pr_debug">pr_debug</a>(<i>"found: %p: num=%d, daddr=%pI6c, dif=%d\n"</i>, sk,
<a name="L212" href="source/net/ipv4/ping.c#L212">212</a>                                  (int) isk-&gt;<a href="ident?i=inet_num">inet_num</a>,
<a name="L213" href="source/net/ipv4/ping.c#L213">213</a>                                  &amp;sk-&gt;<a href="ident?i=sk_v6_rcv_saddr">sk_v6_rcv_saddr</a>,
<a name="L214" href="source/net/ipv4/ping.c#L214">214</a>                                  sk-&gt;<a href="ident?i=sk_bound_dev_if">sk_bound_dev_if</a>);
<a name="L215" href="source/net/ipv4/ping.c#L215">215</a> 
<a name="L216" href="source/net/ipv4/ping.c#L216">216</a>                         if (!<a href="ident?i=ipv6_addr_any">ipv6_addr_any</a>(&amp;sk-&gt;<a href="ident?i=sk_v6_rcv_saddr">sk_v6_rcv_saddr</a>) &amp;&amp;
<a name="L217" href="source/net/ipv4/ping.c#L217">217</a>                             !<a href="ident?i=ipv6_addr_equal">ipv6_addr_equal</a>(&amp;sk-&gt;<a href="ident?i=sk_v6_rcv_saddr">sk_v6_rcv_saddr</a>,
<a name="L218" href="source/net/ipv4/ping.c#L218">218</a>                                              &amp;<a href="ident?i=ipv6_hdr">ipv6_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=daddr">daddr</a>))
<a name="L219" href="source/net/ipv4/ping.c#L219">219</a>                                 continue;
<a name="L220" href="source/net/ipv4/ping.c#L220">220</a> #endif
<a name="L221" href="source/net/ipv4/ping.c#L221">221</a>                 } else {
<a name="L222" href="source/net/ipv4/ping.c#L222">222</a>                         continue;
<a name="L223" href="source/net/ipv4/ping.c#L223">223</a>                 }
<a name="L224" href="source/net/ipv4/ping.c#L224">224</a> 
<a name="L225" href="source/net/ipv4/ping.c#L225">225</a>                 if (sk-&gt;<a href="ident?i=sk_bound_dev_if">sk_bound_dev_if</a> &amp;&amp; sk-&gt;<a href="ident?i=sk_bound_dev_if">sk_bound_dev_if</a> != dif)
<a name="L226" href="source/net/ipv4/ping.c#L226">226</a>                         continue;
<a name="L227" href="source/net/ipv4/ping.c#L227">227</a> 
<a name="L228" href="source/net/ipv4/ping.c#L228">228</a>                 <a href="ident?i=sock_hold">sock_hold</a>(sk);
<a name="L229" href="source/net/ipv4/ping.c#L229">229</a>                 goto <a href="ident?i=exit">exit</a>;
<a name="L230" href="source/net/ipv4/ping.c#L230">230</a>         }
<a name="L231" href="source/net/ipv4/ping.c#L231">231</a> 
<a name="L232" href="source/net/ipv4/ping.c#L232">232</a>         sk = <a href="ident?i=NULL">NULL</a>;
<a name="L233" href="source/net/ipv4/ping.c#L233">233</a> <a href="ident?i=exit">exit</a>:
<a name="L234" href="source/net/ipv4/ping.c#L234">234</a>         <a href="ident?i=read_unlock_bh">read_unlock_bh</a>(&amp;<a href="ident?i=ping_table">ping_table</a>.<a href="ident?i=lock">lock</a>);
<a name="L235" href="source/net/ipv4/ping.c#L235">235</a> 
<a name="L236" href="source/net/ipv4/ping.c#L236">236</a>         return sk;
<a name="L237" href="source/net/ipv4/ping.c#L237">237</a> }
<a name="L238" href="source/net/ipv4/ping.c#L238">238</a> 
<a name="L239" href="source/net/ipv4/ping.c#L239">239</a> static void <a href="ident?i=inet_get_ping_group_range_net">inet_get_ping_group_range_net</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>, <a href="ident?i=kgid_t">kgid_t</a> *low,
<a name="L240" href="source/net/ipv4/ping.c#L240">240</a>                                           <a href="ident?i=kgid_t">kgid_t</a> *<a href="ident?i=high">high</a>)
<a name="L241" href="source/net/ipv4/ping.c#L241">241</a> {
<a name="L242" href="source/net/ipv4/ping.c#L242">242</a>         <a href="ident?i=kgid_t">kgid_t</a> *<a href="ident?i=data">data</a> = <a href="ident?i=net">net</a>-&gt;ipv4.<a href="ident?i=ping_group_range">ping_group_range</a>.<a href="ident?i=range">range</a>;
<a name="L243" href="source/net/ipv4/ping.c#L243">243</a>         unsigned int <a href="ident?i=seq">seq</a>;
<a name="L244" href="source/net/ipv4/ping.c#L244">244</a> 
<a name="L245" href="source/net/ipv4/ping.c#L245">245</a>         do {
<a name="L246" href="source/net/ipv4/ping.c#L246">246</a>                 <a href="ident?i=seq">seq</a> = <a href="ident?i=read_seqbegin">read_seqbegin</a>(&amp;<a href="ident?i=net">net</a>-&gt;ipv4.<a href="ident?i=ping_group_range">ping_group_range</a>.<a href="ident?i=lock">lock</a>);
<a name="L247" href="source/net/ipv4/ping.c#L247">247</a> 
<a name="L248" href="source/net/ipv4/ping.c#L248">248</a>                 *low = <a href="ident?i=data">data</a>[0];
<a name="L249" href="source/net/ipv4/ping.c#L249">249</a>                 *<a href="ident?i=high">high</a> = <a href="ident?i=data">data</a>[1];
<a name="L250" href="source/net/ipv4/ping.c#L250">250</a>         } while (<a href="ident?i=read_seqretry">read_seqretry</a>(&amp;<a href="ident?i=net">net</a>-&gt;ipv4.<a href="ident?i=ping_group_range">ping_group_range</a>.<a href="ident?i=lock">lock</a>, <a href="ident?i=seq">seq</a>));
<a name="L251" href="source/net/ipv4/ping.c#L251">251</a> }
<a name="L252" href="source/net/ipv4/ping.c#L252">252</a> 
<a name="L253" href="source/net/ipv4/ping.c#L253">253</a> 
<a name="L254" href="source/net/ipv4/ping.c#L254">254</a> int <a href="ident?i=ping_init_sock">ping_init_sock</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L255" href="source/net/ipv4/ping.c#L255">255</a> {
<a name="L256" href="source/net/ipv4/ping.c#L256">256</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=sock_net">sock_net</a>(sk);
<a name="L257" href="source/net/ipv4/ping.c#L257">257</a>         <a href="ident?i=kgid_t">kgid_t</a> <a href="ident?i=group">group</a> = <a href="ident?i=current_egid">current_egid</a>();
<a name="L258" href="source/net/ipv4/ping.c#L258">258</a>         struct <a href="ident?i=group_info">group_info</a> *<a href="ident?i=group_info">group_info</a>;
<a name="L259" href="source/net/ipv4/ping.c#L259">259</a>         int <a href="ident?i=i">i</a>, j, <a href="ident?i=count">count</a>;
<a name="L260" href="source/net/ipv4/ping.c#L260">260</a>         <a href="ident?i=kgid_t">kgid_t</a> low, <a href="ident?i=high">high</a>;
<a name="L261" href="source/net/ipv4/ping.c#L261">261</a>         int <a href="ident?i=ret">ret</a> = 0;
<a name="L262" href="source/net/ipv4/ping.c#L262">262</a> 
<a name="L263" href="source/net/ipv4/ping.c#L263">263</a>         if (sk-&gt;<a href="ident?i=sk_family">sk_family</a> == <a href="ident?i=AF_INET6">AF_INET6</a>)
<a name="L264" href="source/net/ipv4/ping.c#L264">264</a>                 sk-&gt;<a href="ident?i=sk_ipv6only">sk_ipv6only</a> = 1;
<a name="L265" href="source/net/ipv4/ping.c#L265">265</a> 
<a name="L266" href="source/net/ipv4/ping.c#L266">266</a>         <a href="ident?i=inet_get_ping_group_range_net">inet_get_ping_group_range_net</a>(<a href="ident?i=net">net</a>, &amp;low, &amp;<a href="ident?i=high">high</a>);
<a name="L267" href="source/net/ipv4/ping.c#L267">267</a>         if (<a href="ident?i=gid_lte">gid_lte</a>(low, <a href="ident?i=group">group</a>) &amp;&amp; <a href="ident?i=gid_lte">gid_lte</a>(<a href="ident?i=group">group</a>, <a href="ident?i=high">high</a>))
<a name="L268" href="source/net/ipv4/ping.c#L268">268</a>                 return 0;
<a name="L269" href="source/net/ipv4/ping.c#L269">269</a> 
<a name="L270" href="source/net/ipv4/ping.c#L270">270</a>         <a href="ident?i=group_info">group_info</a> = <a href="ident?i=get_current_groups">get_current_groups</a>();
<a name="L271" href="source/net/ipv4/ping.c#L271">271</a>         <a href="ident?i=count">count</a> = <a href="ident?i=group_info">group_info</a>-&gt;ngroups;
<a name="L272" href="source/net/ipv4/ping.c#L272">272</a>         for (<a href="ident?i=i">i</a> = 0; <a href="ident?i=i">i</a> &lt; <a href="ident?i=group_info">group_info</a>-&gt;<a href="ident?i=nblocks">nblocks</a>; <a href="ident?i=i">i</a>++) {
<a name="L273" href="source/net/ipv4/ping.c#L273">273</a>                 int cp_count = <a href="ident?i=min_t">min_t</a>(int, <a href="ident?i=NGROUPS_PER_BLOCK">NGROUPS_PER_BLOCK</a>, <a href="ident?i=count">count</a>);
<a name="L274" href="source/net/ipv4/ping.c#L274">274</a>                 for (j = 0; j &lt; cp_count; j++) {
<a name="L275" href="source/net/ipv4/ping.c#L275">275</a>                         <a href="ident?i=kgid_t">kgid_t</a> <a href="ident?i=gid">gid</a> = <a href="ident?i=group_info">group_info</a>-&gt;blocks[<a href="ident?i=i">i</a>][j];
<a name="L276" href="source/net/ipv4/ping.c#L276">276</a>                         if (<a href="ident?i=gid_lte">gid_lte</a>(low, <a href="ident?i=gid">gid</a>) &amp;&amp; <a href="ident?i=gid_lte">gid_lte</a>(<a href="ident?i=gid">gid</a>, <a href="ident?i=high">high</a>))
<a name="L277" href="source/net/ipv4/ping.c#L277">277</a>                                 goto out_release_group;
<a name="L278" href="source/net/ipv4/ping.c#L278">278</a>                 }
<a name="L279" href="source/net/ipv4/ping.c#L279">279</a> 
<a name="L280" href="source/net/ipv4/ping.c#L280">280</a>                 <a href="ident?i=count">count</a> -= cp_count;
<a name="L281" href="source/net/ipv4/ping.c#L281">281</a>         }
<a name="L282" href="source/net/ipv4/ping.c#L282">282</a> 
<a name="L283" href="source/net/ipv4/ping.c#L283">283</a>         <a href="ident?i=ret">ret</a> = -<a href="ident?i=EACCES">EACCES</a>;
<a name="L284" href="source/net/ipv4/ping.c#L284">284</a> 
<a name="L285" href="source/net/ipv4/ping.c#L285">285</a> out_release_group:
<a name="L286" href="source/net/ipv4/ping.c#L286">286</a>         <a href="ident?i=put_group_info">put_group_info</a>(<a href="ident?i=group_info">group_info</a>);
<a name="L287" href="source/net/ipv4/ping.c#L287">287</a>         return <a href="ident?i=ret">ret</a>;
<a name="L288" href="source/net/ipv4/ping.c#L288">288</a> }
<a name="L289" href="source/net/ipv4/ping.c#L289">289</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=ping_init_sock">ping_init_sock</a>);
<a name="L290" href="source/net/ipv4/ping.c#L290">290</a> 
<a name="L291" href="source/net/ipv4/ping.c#L291">291</a> void <a href="ident?i=ping_close">ping_close</a>(struct <a href="ident?i=sock">sock</a> *sk, long <a href="ident?i=timeout">timeout</a>)
<a name="L292" href="source/net/ipv4/ping.c#L292">292</a> {
<a name="L293" href="source/net/ipv4/ping.c#L293">293</a>         <a href="ident?i=pr_debug">pr_debug</a>(<i>"ping_close(sk=%p,sk-&gt;num=%u)\n"</i>,
<a name="L294" href="source/net/ipv4/ping.c#L294">294</a>                  <a href="ident?i=inet_sk">inet_sk</a>(sk), <a href="ident?i=inet_sk">inet_sk</a>(sk)-&gt;<a href="ident?i=inet_num">inet_num</a>);
<a name="L295" href="source/net/ipv4/ping.c#L295">295</a>         <a href="ident?i=pr_debug">pr_debug</a>(<i>"isk-&gt;refcnt = %d\n"</i>, sk-&gt;<a href="ident?i=sk_refcnt">sk_refcnt</a>.<a href="ident?i=counter">counter</a>);
<a name="L296" href="source/net/ipv4/ping.c#L296">296</a> 
<a name="L297" href="source/net/ipv4/ping.c#L297">297</a>         <a href="ident?i=sk_common_release">sk_common_release</a>(sk);
<a name="L298" href="source/net/ipv4/ping.c#L298">298</a> }
<a name="L299" href="source/net/ipv4/ping.c#L299">299</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=ping_close">ping_close</a>);
<a name="L300" href="source/net/ipv4/ping.c#L300">300</a> 
<a name="L301" href="source/net/ipv4/ping.c#L301">301</a> <b><i>/* Checks the bind address and possibly modifies sk-&gt;sk_bound_dev_if. */</i></b>
<a name="L302" href="source/net/ipv4/ping.c#L302">302</a> static int <a href="ident?i=ping_check_bind_addr">ping_check_bind_addr</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=inet_sock">inet_sock</a> *isk,
<a name="L303" href="source/net/ipv4/ping.c#L303">303</a>                                 struct <a href="ident?i=sockaddr">sockaddr</a> *<a href="ident?i=uaddr">uaddr</a>, int addr_len) {
<a name="L304" href="source/net/ipv4/ping.c#L304">304</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=sock_net">sock_net</a>(sk);
<a name="L305" href="source/net/ipv4/ping.c#L305">305</a>         if (sk-&gt;<a href="ident?i=sk_family">sk_family</a> == <a href="ident?i=AF_INET">AF_INET</a>) {
<a name="L306" href="source/net/ipv4/ping.c#L306">306</a>                 struct <a href="ident?i=sockaddr_in">sockaddr_in</a> *<a href="ident?i=addr">addr</a> = (struct <a href="ident?i=sockaddr_in">sockaddr_in</a> *) <a href="ident?i=uaddr">uaddr</a>;
<a name="L307" href="source/net/ipv4/ping.c#L307">307</a>                 int chk_addr_ret;
<a name="L308" href="source/net/ipv4/ping.c#L308">308</a> 
<a name="L309" href="source/net/ipv4/ping.c#L309">309</a>                 if (addr_len &lt; sizeof(*<a href="ident?i=addr">addr</a>))
<a name="L310" href="source/net/ipv4/ping.c#L310">310</a>                         return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L311" href="source/net/ipv4/ping.c#L311">311</a> 
<a name="L312" href="source/net/ipv4/ping.c#L312">312</a>                 if (<a href="ident?i=addr">addr</a>-&gt;sin_family != <a href="ident?i=AF_INET">AF_INET</a> &amp;&amp;
<a name="L313" href="source/net/ipv4/ping.c#L313">313</a>                     !(<a href="ident?i=addr">addr</a>-&gt;sin_family == <a href="ident?i=AF_UNSPEC">AF_UNSPEC</a> &amp;&amp;
<a name="L314" href="source/net/ipv4/ping.c#L314">314</a>                       <a href="ident?i=addr">addr</a>-&gt;sin_addr.s_addr == <a href="ident?i=htonl">htonl</a>(<a href="ident?i=INADDR_ANY">INADDR_ANY</a>)))
<a name="L315" href="source/net/ipv4/ping.c#L315">315</a>                         return -<a href="ident?i=EAFNOSUPPORT">EAFNOSUPPORT</a>;
<a name="L316" href="source/net/ipv4/ping.c#L316">316</a> 
<a name="L317" href="source/net/ipv4/ping.c#L317">317</a>                 <a href="ident?i=pr_debug">pr_debug</a>(<i>"ping_check_bind_addr(sk=%p,addr=%pI4,port=%d)\n"</i>,
<a name="L318" href="source/net/ipv4/ping.c#L318">318</a>                          sk, &amp;<a href="ident?i=addr">addr</a>-&gt;sin_addr.s_addr, <a href="ident?i=ntohs">ntohs</a>(<a href="ident?i=addr">addr</a>-&gt;sin_port));
<a name="L319" href="source/net/ipv4/ping.c#L319">319</a> 
<a name="L320" href="source/net/ipv4/ping.c#L320">320</a>                 chk_addr_ret = <a href="ident?i=inet_addr_type">inet_addr_type</a>(<a href="ident?i=net">net</a>, <a href="ident?i=addr">addr</a>-&gt;sin_addr.s_addr);
<a name="L321" href="source/net/ipv4/ping.c#L321">321</a> 
<a name="L322" href="source/net/ipv4/ping.c#L322">322</a>                 if (<a href="ident?i=addr">addr</a>-&gt;sin_addr.s_addr == <a href="ident?i=htonl">htonl</a>(<a href="ident?i=INADDR_ANY">INADDR_ANY</a>))
<a name="L323" href="source/net/ipv4/ping.c#L323">323</a>                         chk_addr_ret = RTN_LOCAL;
<a name="L324" href="source/net/ipv4/ping.c#L324">324</a> 
<a name="L325" href="source/net/ipv4/ping.c#L325">325</a>                 if ((<a href="ident?i=net">net</a>-&gt;ipv4.sysctl_ip_nonlocal_bind == 0 &amp;&amp;
<a name="L326" href="source/net/ipv4/ping.c#L326">326</a>                     isk-&gt;freebind == 0 &amp;&amp; isk-&gt;transparent == 0 &amp;&amp;
<a name="L327" href="source/net/ipv4/ping.c#L327">327</a>                      chk_addr_ret != RTN_LOCAL) ||
<a name="L328" href="source/net/ipv4/ping.c#L328">328</a>                     chk_addr_ret == RTN_MULTICAST ||
<a name="L329" href="source/net/ipv4/ping.c#L329">329</a>                     chk_addr_ret == RTN_BROADCAST)
<a name="L330" href="source/net/ipv4/ping.c#L330">330</a>                         return -<a href="ident?i=EADDRNOTAVAIL">EADDRNOTAVAIL</a>;
<a name="L331" href="source/net/ipv4/ping.c#L331">331</a> 
<a name="L332" href="source/net/ipv4/ping.c#L332">332</a> #if <a href="ident?i=IS_ENABLED">IS_ENABLED</a>(CONFIG_IPV6)
<a name="L333" href="source/net/ipv4/ping.c#L333">333</a>         } else if (sk-&gt;<a href="ident?i=sk_family">sk_family</a> == <a href="ident?i=AF_INET6">AF_INET6</a>) {
<a name="L334" href="source/net/ipv4/ping.c#L334">334</a>                 struct <a href="ident?i=sockaddr_in6">sockaddr_in6</a> *<a href="ident?i=addr">addr</a> = (struct <a href="ident?i=sockaddr_in6">sockaddr_in6</a> *) <a href="ident?i=uaddr">uaddr</a>;
<a name="L335" href="source/net/ipv4/ping.c#L335">335</a>                 int addr_type, scoped, has_addr;
<a name="L336" href="source/net/ipv4/ping.c#L336">336</a>                 struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a> = <a href="ident?i=NULL">NULL</a>;
<a name="L337" href="source/net/ipv4/ping.c#L337">337</a> 
<a name="L338" href="source/net/ipv4/ping.c#L338">338</a>                 if (addr_len &lt; sizeof(*<a href="ident?i=addr">addr</a>))
<a name="L339" href="source/net/ipv4/ping.c#L339">339</a>                         return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L340" href="source/net/ipv4/ping.c#L340">340</a> 
<a name="L341" href="source/net/ipv4/ping.c#L341">341</a>                 if (<a href="ident?i=addr">addr</a>-&gt;sin6_family != <a href="ident?i=AF_INET6">AF_INET6</a>)
<a name="L342" href="source/net/ipv4/ping.c#L342">342</a>                         return -<a href="ident?i=EAFNOSUPPORT">EAFNOSUPPORT</a>;
<a name="L343" href="source/net/ipv4/ping.c#L343">343</a> 
<a name="L344" href="source/net/ipv4/ping.c#L344">344</a>                 <a href="ident?i=pr_debug">pr_debug</a>(<i>"ping_check_bind_addr(sk=%p,addr=%pI6c,port=%d)\n"</i>,
<a name="L345" href="source/net/ipv4/ping.c#L345">345</a>                          sk, <a href="ident?i=addr">addr</a>-&gt;sin6_addr.<a href="ident?i=s6_addr">s6_addr</a>, <a href="ident?i=ntohs">ntohs</a>(<a href="ident?i=addr">addr</a>-&gt;sin6_port));
<a name="L346" href="source/net/ipv4/ping.c#L346">346</a> 
<a name="L347" href="source/net/ipv4/ping.c#L347">347</a>                 addr_type = <a href="ident?i=ipv6_addr_type">ipv6_addr_type</a>(&amp;<a href="ident?i=addr">addr</a>-&gt;sin6_addr);
<a name="L348" href="source/net/ipv4/ping.c#L348">348</a>                 scoped = <a href="ident?i=__ipv6_addr_needs_scope_id">__ipv6_addr_needs_scope_id</a>(addr_type);
<a name="L349" href="source/net/ipv4/ping.c#L349">349</a>                 if ((addr_type != <a href="ident?i=IPV6_ADDR_ANY">IPV6_ADDR_ANY</a> &amp;&amp;
<a name="L350" href="source/net/ipv4/ping.c#L350">350</a>                      !(addr_type &amp; <a href="ident?i=IPV6_ADDR_UNICAST">IPV6_ADDR_UNICAST</a>)) ||
<a name="L351" href="source/net/ipv4/ping.c#L351">351</a>                     (scoped &amp;&amp; !<a href="ident?i=addr">addr</a>-&gt;sin6_scope_id))
<a name="L352" href="source/net/ipv4/ping.c#L352">352</a>                         return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L353" href="source/net/ipv4/ping.c#L353">353</a> 
<a name="L354" href="source/net/ipv4/ping.c#L354">354</a>                 <a href="ident?i=rcu_read_lock">rcu_read_lock</a>();
<a name="L355" href="source/net/ipv4/ping.c#L355">355</a>                 if (<a href="ident?i=addr">addr</a>-&gt;sin6_scope_id) {
<a name="L356" href="source/net/ipv4/ping.c#L356">356</a>                         <a href="ident?i=dev">dev</a> = <a href="ident?i=dev_get_by_index_rcu">dev_get_by_index_rcu</a>(<a href="ident?i=net">net</a>, <a href="ident?i=addr">addr</a>-&gt;sin6_scope_id);
<a name="L357" href="source/net/ipv4/ping.c#L357">357</a>                         if (!<a href="ident?i=dev">dev</a>) {
<a name="L358" href="source/net/ipv4/ping.c#L358">358</a>                                 <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L359" href="source/net/ipv4/ping.c#L359">359</a>                                 return -<a href="ident?i=ENODEV">ENODEV</a>;
<a name="L360" href="source/net/ipv4/ping.c#L360">360</a>                         }
<a name="L361" href="source/net/ipv4/ping.c#L361">361</a>                 }
<a name="L362" href="source/net/ipv4/ping.c#L362">362</a>                 has_addr = <a href="ident?i=pingv6_ops">pingv6_ops</a>.<a href="ident?i=ipv6_chk_addr">ipv6_chk_addr</a>(<a href="ident?i=net">net</a>, &amp;<a href="ident?i=addr">addr</a>-&gt;sin6_addr, <a href="ident?i=dev">dev</a>,
<a name="L363" href="source/net/ipv4/ping.c#L363">363</a>                                                     scoped);
<a name="L364" href="source/net/ipv4/ping.c#L364">364</a>                 <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L365" href="source/net/ipv4/ping.c#L365">365</a> 
<a name="L366" href="source/net/ipv4/ping.c#L366">366</a>                 if (!(isk-&gt;freebind || isk-&gt;transparent || has_addr ||
<a name="L367" href="source/net/ipv4/ping.c#L367">367</a>                       addr_type == <a href="ident?i=IPV6_ADDR_ANY">IPV6_ADDR_ANY</a>))
<a name="L368" href="source/net/ipv4/ping.c#L368">368</a>                         return -<a href="ident?i=EADDRNOTAVAIL">EADDRNOTAVAIL</a>;
<a name="L369" href="source/net/ipv4/ping.c#L369">369</a> 
<a name="L370" href="source/net/ipv4/ping.c#L370">370</a>                 if (scoped)
<a name="L371" href="source/net/ipv4/ping.c#L371">371</a>                         sk-&gt;<a href="ident?i=sk_bound_dev_if">sk_bound_dev_if</a> = <a href="ident?i=addr">addr</a>-&gt;sin6_scope_id;
<a name="L372" href="source/net/ipv4/ping.c#L372">372</a> #endif
<a name="L373" href="source/net/ipv4/ping.c#L373">373</a>         } else {
<a name="L374" href="source/net/ipv4/ping.c#L374">374</a>                 return -<a href="ident?i=EAFNOSUPPORT">EAFNOSUPPORT</a>;
<a name="L375" href="source/net/ipv4/ping.c#L375">375</a>         }
<a name="L376" href="source/net/ipv4/ping.c#L376">376</a>         return 0;
<a name="L377" href="source/net/ipv4/ping.c#L377">377</a> }
<a name="L378" href="source/net/ipv4/ping.c#L378">378</a> 
<a name="L379" href="source/net/ipv4/ping.c#L379">379</a> static void <a href="ident?i=ping_set_saddr">ping_set_saddr</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=sockaddr">sockaddr</a> *<a href="ident?i=saddr">saddr</a>)
<a name="L380" href="source/net/ipv4/ping.c#L380">380</a> {
<a name="L381" href="source/net/ipv4/ping.c#L381">381</a>         if (<a href="ident?i=saddr">saddr</a>-&gt;sa_family == <a href="ident?i=AF_INET">AF_INET</a>) {
<a name="L382" href="source/net/ipv4/ping.c#L382">382</a>                 struct <a href="ident?i=inet_sock">inet_sock</a> *isk = <a href="ident?i=inet_sk">inet_sk</a>(sk);
<a name="L383" href="source/net/ipv4/ping.c#L383">383</a>                 struct <a href="ident?i=sockaddr_in">sockaddr_in</a> *<a href="ident?i=addr">addr</a> = (struct <a href="ident?i=sockaddr_in">sockaddr_in</a> *) <a href="ident?i=saddr">saddr</a>;
<a name="L384" href="source/net/ipv4/ping.c#L384">384</a>                 isk-&gt;<a href="ident?i=inet_rcv_saddr">inet_rcv_saddr</a> = isk-&gt;inet_saddr = <a href="ident?i=addr">addr</a>-&gt;sin_addr.s_addr;
<a name="L385" href="source/net/ipv4/ping.c#L385">385</a> #if <a href="ident?i=IS_ENABLED">IS_ENABLED</a>(CONFIG_IPV6)
<a name="L386" href="source/net/ipv4/ping.c#L386">386</a>         } else if (<a href="ident?i=saddr">saddr</a>-&gt;sa_family == <a href="ident?i=AF_INET6">AF_INET6</a>) {
<a name="L387" href="source/net/ipv4/ping.c#L387">387</a>                 struct <a href="ident?i=sockaddr_in6">sockaddr_in6</a> *<a href="ident?i=addr">addr</a> = (struct <a href="ident?i=sockaddr_in6">sockaddr_in6</a> *) <a href="ident?i=saddr">saddr</a>;
<a name="L388" href="source/net/ipv4/ping.c#L388">388</a>                 struct <a href="ident?i=ipv6_pinfo">ipv6_pinfo</a> *np = <a href="ident?i=inet6_sk">inet6_sk</a>(sk);
<a name="L389" href="source/net/ipv4/ping.c#L389">389</a>                 sk-&gt;<a href="ident?i=sk_v6_rcv_saddr">sk_v6_rcv_saddr</a> = np-&gt;<a href="ident?i=saddr">saddr</a> = <a href="ident?i=addr">addr</a>-&gt;sin6_addr;
<a name="L390" href="source/net/ipv4/ping.c#L390">390</a> #endif
<a name="L391" href="source/net/ipv4/ping.c#L391">391</a>         }
<a name="L392" href="source/net/ipv4/ping.c#L392">392</a> }
<a name="L393" href="source/net/ipv4/ping.c#L393">393</a> 
<a name="L394" href="source/net/ipv4/ping.c#L394">394</a> static void <a href="ident?i=ping_clear_saddr">ping_clear_saddr</a>(struct <a href="ident?i=sock">sock</a> *sk, int dif)
<a name="L395" href="source/net/ipv4/ping.c#L395">395</a> {
<a name="L396" href="source/net/ipv4/ping.c#L396">396</a>         sk-&gt;<a href="ident?i=sk_bound_dev_if">sk_bound_dev_if</a> = dif;
<a name="L397" href="source/net/ipv4/ping.c#L397">397</a>         if (sk-&gt;<a href="ident?i=sk_family">sk_family</a> == <a href="ident?i=AF_INET">AF_INET</a>) {
<a name="L398" href="source/net/ipv4/ping.c#L398">398</a>                 struct <a href="ident?i=inet_sock">inet_sock</a> *isk = <a href="ident?i=inet_sk">inet_sk</a>(sk);
<a name="L399" href="source/net/ipv4/ping.c#L399">399</a>                 isk-&gt;<a href="ident?i=inet_rcv_saddr">inet_rcv_saddr</a> = isk-&gt;inet_saddr = 0;
<a name="L400" href="source/net/ipv4/ping.c#L400">400</a> #if <a href="ident?i=IS_ENABLED">IS_ENABLED</a>(CONFIG_IPV6)
<a name="L401" href="source/net/ipv4/ping.c#L401">401</a>         } else if (sk-&gt;<a href="ident?i=sk_family">sk_family</a> == <a href="ident?i=AF_INET6">AF_INET6</a>) {
<a name="L402" href="source/net/ipv4/ping.c#L402">402</a>                 struct <a href="ident?i=ipv6_pinfo">ipv6_pinfo</a> *np = <a href="ident?i=inet6_sk">inet6_sk</a>(sk);
<a name="L403" href="source/net/ipv4/ping.c#L403">403</a>                 <a href="ident?i=memset">memset</a>(&amp;sk-&gt;<a href="ident?i=sk_v6_rcv_saddr">sk_v6_rcv_saddr</a>, 0, sizeof(sk-&gt;<a href="ident?i=sk_v6_rcv_saddr">sk_v6_rcv_saddr</a>));
<a name="L404" href="source/net/ipv4/ping.c#L404">404</a>                 <a href="ident?i=memset">memset</a>(&amp;np-&gt;<a href="ident?i=saddr">saddr</a>, 0, sizeof(np-&gt;<a href="ident?i=saddr">saddr</a>));
<a name="L405" href="source/net/ipv4/ping.c#L405">405</a> #endif
<a name="L406" href="source/net/ipv4/ping.c#L406">406</a>         }
<a name="L407" href="source/net/ipv4/ping.c#L407">407</a> }
<a name="L408" href="source/net/ipv4/ping.c#L408">408</a> <b><i>/*</i></b>
<a name="L409" href="source/net/ipv4/ping.c#L409">409</a> <b><i> * We need our own bind because there are no privileged id's == local ports.</i></b>
<a name="L410" href="source/net/ipv4/ping.c#L410">410</a> <b><i> * Moreover, we don't allow binding to multi- and broadcast addresses.</i></b>
<a name="L411" href="source/net/ipv4/ping.c#L411">411</a> <b><i> */</i></b>
<a name="L412" href="source/net/ipv4/ping.c#L412">412</a> 
<a name="L413" href="source/net/ipv4/ping.c#L413">413</a> int <a href="ident?i=ping_bind">ping_bind</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=sockaddr">sockaddr</a> *<a href="ident?i=uaddr">uaddr</a>, int addr_len)
<a name="L414" href="source/net/ipv4/ping.c#L414">414</a> {
<a name="L415" href="source/net/ipv4/ping.c#L415">415</a>         struct <a href="ident?i=inet_sock">inet_sock</a> *isk = <a href="ident?i=inet_sk">inet_sk</a>(sk);
<a name="L416" href="source/net/ipv4/ping.c#L416">416</a>         unsigned short snum;
<a name="L417" href="source/net/ipv4/ping.c#L417">417</a>         int <a href="ident?i=err">err</a>;
<a name="L418" href="source/net/ipv4/ping.c#L418">418</a>         int dif = sk-&gt;<a href="ident?i=sk_bound_dev_if">sk_bound_dev_if</a>;
<a name="L419" href="source/net/ipv4/ping.c#L419">419</a> 
<a name="L420" href="source/net/ipv4/ping.c#L420">420</a>         <a href="ident?i=err">err</a> = <a href="ident?i=ping_check_bind_addr">ping_check_bind_addr</a>(sk, isk, <a href="ident?i=uaddr">uaddr</a>, addr_len);
<a name="L421" href="source/net/ipv4/ping.c#L421">421</a>         if (<a href="ident?i=err">err</a>)
<a name="L422" href="source/net/ipv4/ping.c#L422">422</a>                 return <a href="ident?i=err">err</a>;
<a name="L423" href="source/net/ipv4/ping.c#L423">423</a> 
<a name="L424" href="source/net/ipv4/ping.c#L424">424</a>         <a href="ident?i=lock_sock">lock_sock</a>(sk);
<a name="L425" href="source/net/ipv4/ping.c#L425">425</a> 
<a name="L426" href="source/net/ipv4/ping.c#L426">426</a>         <a href="ident?i=err">err</a> = -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L427" href="source/net/ipv4/ping.c#L427">427</a>         if (isk-&gt;<a href="ident?i=inet_num">inet_num</a> != 0)
<a name="L428" href="source/net/ipv4/ping.c#L428">428</a>                 goto <a href="ident?i=out">out</a>;
<a name="L429" href="source/net/ipv4/ping.c#L429">429</a> 
<a name="L430" href="source/net/ipv4/ping.c#L430">430</a>         <a href="ident?i=err">err</a> = -<a href="ident?i=EADDRINUSE">EADDRINUSE</a>;
<a name="L431" href="source/net/ipv4/ping.c#L431">431</a>         <a href="ident?i=ping_set_saddr">ping_set_saddr</a>(sk, <a href="ident?i=uaddr">uaddr</a>);
<a name="L432" href="source/net/ipv4/ping.c#L432">432</a>         snum = <a href="ident?i=ntohs">ntohs</a>(((struct <a href="ident?i=sockaddr_in">sockaddr_in</a> *)<a href="ident?i=uaddr">uaddr</a>)-&gt;sin_port);
<a name="L433" href="source/net/ipv4/ping.c#L433">433</a>         if (<a href="ident?i=ping_get_port">ping_get_port</a>(sk, snum) != 0) {
<a name="L434" href="source/net/ipv4/ping.c#L434">434</a>                 <a href="ident?i=ping_clear_saddr">ping_clear_saddr</a>(sk, dif);
<a name="L435" href="source/net/ipv4/ping.c#L435">435</a>                 goto <a href="ident?i=out">out</a>;
<a name="L436" href="source/net/ipv4/ping.c#L436">436</a>         }
<a name="L437" href="source/net/ipv4/ping.c#L437">437</a> 
<a name="L438" href="source/net/ipv4/ping.c#L438">438</a>         <a href="ident?i=pr_debug">pr_debug</a>(<i>"after bind(): num = %d, dif = %d\n"</i>,
<a name="L439" href="source/net/ipv4/ping.c#L439">439</a>                  (int)isk-&gt;<a href="ident?i=inet_num">inet_num</a>,
<a name="L440" href="source/net/ipv4/ping.c#L440">440</a>                  (int)sk-&gt;<a href="ident?i=sk_bound_dev_if">sk_bound_dev_if</a>);
<a name="L441" href="source/net/ipv4/ping.c#L441">441</a> 
<a name="L442" href="source/net/ipv4/ping.c#L442">442</a>         <a href="ident?i=err">err</a> = 0;
<a name="L443" href="source/net/ipv4/ping.c#L443">443</a>         if (sk-&gt;<a href="ident?i=sk_family">sk_family</a> == <a href="ident?i=AF_INET">AF_INET</a> &amp;&amp; isk-&gt;<a href="ident?i=inet_rcv_saddr">inet_rcv_saddr</a>)
<a name="L444" href="source/net/ipv4/ping.c#L444">444</a>                 sk-&gt;sk_userlocks |= <a href="ident?i=SOCK_BINDADDR_LOCK">SOCK_BINDADDR_LOCK</a>;
<a name="L445" href="source/net/ipv4/ping.c#L445">445</a> #if <a href="ident?i=IS_ENABLED">IS_ENABLED</a>(CONFIG_IPV6)
<a name="L446" href="source/net/ipv4/ping.c#L446">446</a>         if (sk-&gt;<a href="ident?i=sk_family">sk_family</a> == <a href="ident?i=AF_INET6">AF_INET6</a> &amp;&amp; !<a href="ident?i=ipv6_addr_any">ipv6_addr_any</a>(&amp;sk-&gt;<a href="ident?i=sk_v6_rcv_saddr">sk_v6_rcv_saddr</a>))
<a name="L447" href="source/net/ipv4/ping.c#L447">447</a>                 sk-&gt;sk_userlocks |= <a href="ident?i=SOCK_BINDADDR_LOCK">SOCK_BINDADDR_LOCK</a>;
<a name="L448" href="source/net/ipv4/ping.c#L448">448</a> #endif
<a name="L449" href="source/net/ipv4/ping.c#L449">449</a> 
<a name="L450" href="source/net/ipv4/ping.c#L450">450</a>         if (snum)
<a name="L451" href="source/net/ipv4/ping.c#L451">451</a>                 sk-&gt;sk_userlocks |= <a href="ident?i=SOCK_BINDPORT_LOCK">SOCK_BINDPORT_LOCK</a>;
<a name="L452" href="source/net/ipv4/ping.c#L452">452</a>         isk-&gt;inet_sport = <a href="ident?i=htons">htons</a>(isk-&gt;<a href="ident?i=inet_num">inet_num</a>);
<a name="L453" href="source/net/ipv4/ping.c#L453">453</a>         isk-&gt;<a href="ident?i=inet_daddr">inet_daddr</a> = 0;
<a name="L454" href="source/net/ipv4/ping.c#L454">454</a>         isk-&gt;<a href="ident?i=inet_dport">inet_dport</a> = 0;
<a name="L455" href="source/net/ipv4/ping.c#L455">455</a> 
<a name="L456" href="source/net/ipv4/ping.c#L456">456</a> #if <a href="ident?i=IS_ENABLED">IS_ENABLED</a>(CONFIG_IPV6)
<a name="L457" href="source/net/ipv4/ping.c#L457">457</a>         if (sk-&gt;<a href="ident?i=sk_family">sk_family</a> == <a href="ident?i=AF_INET6">AF_INET6</a>)
<a name="L458" href="source/net/ipv4/ping.c#L458">458</a>                 <a href="ident?i=memset">memset</a>(&amp;sk-&gt;<a href="ident?i=sk_v6_daddr">sk_v6_daddr</a>, 0, sizeof(sk-&gt;<a href="ident?i=sk_v6_daddr">sk_v6_daddr</a>));
<a name="L459" href="source/net/ipv4/ping.c#L459">459</a> #endif
<a name="L460" href="source/net/ipv4/ping.c#L460">460</a> 
<a name="L461" href="source/net/ipv4/ping.c#L461">461</a>         <a href="ident?i=sk_dst_reset">sk_dst_reset</a>(sk);
<a name="L462" href="source/net/ipv4/ping.c#L462">462</a> <a href="ident?i=out">out</a>:
<a name="L463" href="source/net/ipv4/ping.c#L463">463</a>         <a href="ident?i=release_sock">release_sock</a>(sk);
<a name="L464" href="source/net/ipv4/ping.c#L464">464</a>         <a href="ident?i=pr_debug">pr_debug</a>(<i>"ping_v4_bind -&gt; %d\n"</i>, <a href="ident?i=err">err</a>);
<a name="L465" href="source/net/ipv4/ping.c#L465">465</a>         return <a href="ident?i=err">err</a>;
<a name="L466" href="source/net/ipv4/ping.c#L466">466</a> }
<a name="L467" href="source/net/ipv4/ping.c#L467">467</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=ping_bind">ping_bind</a>);
<a name="L468" href="source/net/ipv4/ping.c#L468">468</a> 
<a name="L469" href="source/net/ipv4/ping.c#L469">469</a> <b><i>/*</i></b>
<a name="L470" href="source/net/ipv4/ping.c#L470">470</a> <b><i> * Is this a supported type of ICMP message?</i></b>
<a name="L471" href="source/net/ipv4/ping.c#L471">471</a> <b><i> */</i></b>
<a name="L472" href="source/net/ipv4/ping.c#L472">472</a> 
<a name="L473" href="source/net/ipv4/ping.c#L473">473</a> static inline int <a href="ident?i=ping_supported">ping_supported</a>(int <a href="ident?i=family">family</a>, int <a href="ident?i=type">type</a>, int <a href="ident?i=code">code</a>)
<a name="L474" href="source/net/ipv4/ping.c#L474">474</a> {
<a name="L475" href="source/net/ipv4/ping.c#L475">475</a>         return (<a href="ident?i=family">family</a> == <a href="ident?i=AF_INET">AF_INET</a> &amp;&amp; <a href="ident?i=type">type</a> == <a href="ident?i=ICMP_ECHO">ICMP_ECHO</a> &amp;&amp; <a href="ident?i=code">code</a> == 0) ||
<a name="L476" href="source/net/ipv4/ping.c#L476">476</a>                (<a href="ident?i=family">family</a> == <a href="ident?i=AF_INET6">AF_INET6</a> &amp;&amp; <a href="ident?i=type">type</a> == <a href="ident?i=ICMPV6_ECHO_REQUEST">ICMPV6_ECHO_REQUEST</a> &amp;&amp; <a href="ident?i=code">code</a> == 0);
<a name="L477" href="source/net/ipv4/ping.c#L477">477</a> }
<a name="L478" href="source/net/ipv4/ping.c#L478">478</a> 
<a name="L479" href="source/net/ipv4/ping.c#L479">479</a> <b><i>/*</i></b>
<a name="L480" href="source/net/ipv4/ping.c#L480">480</a> <b><i> * This routine is called by the ICMP module when it gets some</i></b>
<a name="L481" href="source/net/ipv4/ping.c#L481">481</a> <b><i> * sort of error condition.</i></b>
<a name="L482" href="source/net/ipv4/ping.c#L482">482</a> <b><i> */</i></b>
<a name="L483" href="source/net/ipv4/ping.c#L483">483</a> 
<a name="L484" href="source/net/ipv4/ping.c#L484">484</a> void <a href="ident?i=ping_err">ping_err</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, int <a href="ident?i=offset">offset</a>, <a href="ident?i=u32">u32</a> <a href="ident?i=info">info</a>)
<a name="L485" href="source/net/ipv4/ping.c#L485">485</a> {
<a name="L486" href="source/net/ipv4/ping.c#L486">486</a>         int <a href="ident?i=family">family</a>;
<a name="L487" href="source/net/ipv4/ping.c#L487">487</a>         struct <a href="ident?i=icmphdr">icmphdr</a> *icmph;
<a name="L488" href="source/net/ipv4/ping.c#L488">488</a>         struct <a href="ident?i=inet_sock">inet_sock</a> *<a href="ident?i=inet_sock">inet_sock</a>;
<a name="L489" href="source/net/ipv4/ping.c#L489">489</a>         int <a href="ident?i=type">type</a>;
<a name="L490" href="source/net/ipv4/ping.c#L490">490</a>         int <a href="ident?i=code">code</a>;
<a name="L491" href="source/net/ipv4/ping.c#L491">491</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=dev">dev</a>);
<a name="L492" href="source/net/ipv4/ping.c#L492">492</a>         struct <a href="ident?i=sock">sock</a> *sk;
<a name="L493" href="source/net/ipv4/ping.c#L493">493</a>         int harderr;
<a name="L494" href="source/net/ipv4/ping.c#L494">494</a>         int <a href="ident?i=err">err</a>;
<a name="L495" href="source/net/ipv4/ping.c#L495">495</a> 
<a name="L496" href="source/net/ipv4/ping.c#L496">496</a>         if (<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=protocol">protocol</a> == <a href="ident?i=htons">htons</a>(<a href="ident?i=ETH_P_IP">ETH_P_IP</a>)) {
<a name="L497" href="source/net/ipv4/ping.c#L497">497</a>                 <a href="ident?i=family">family</a> = <a href="ident?i=AF_INET">AF_INET</a>;
<a name="L498" href="source/net/ipv4/ping.c#L498">498</a>                 <a href="ident?i=type">type</a> = <a href="ident?i=icmp_hdr">icmp_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=type">type</a>;
<a name="L499" href="source/net/ipv4/ping.c#L499">499</a>                 <a href="ident?i=code">code</a> = <a href="ident?i=icmp_hdr">icmp_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=code">code</a>;
<a name="L500" href="source/net/ipv4/ping.c#L500">500</a>                 icmph = (struct <a href="ident?i=icmphdr">icmphdr</a> *)(<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=data">data</a> + <a href="ident?i=offset">offset</a>);
<a name="L501" href="source/net/ipv4/ping.c#L501">501</a>         } else if (<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=protocol">protocol</a> == <a href="ident?i=htons">htons</a>(<a href="ident?i=ETH_P_IPV6">ETH_P_IPV6</a>)) {
<a name="L502" href="source/net/ipv4/ping.c#L502">502</a>                 <a href="ident?i=family">family</a> = <a href="ident?i=AF_INET6">AF_INET6</a>;
<a name="L503" href="source/net/ipv4/ping.c#L503">503</a>                 <a href="ident?i=type">type</a> = <a href="ident?i=icmp6_hdr">icmp6_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;icmp6_type;
<a name="L504" href="source/net/ipv4/ping.c#L504">504</a>                 <a href="ident?i=code">code</a> = <a href="ident?i=icmp6_hdr">icmp6_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;icmp6_code;
<a name="L505" href="source/net/ipv4/ping.c#L505">505</a>                 icmph = (struct <a href="ident?i=icmphdr">icmphdr</a> *) (<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=data">data</a> + <a href="ident?i=offset">offset</a>);
<a name="L506" href="source/net/ipv4/ping.c#L506">506</a>         } else {
<a name="L507" href="source/net/ipv4/ping.c#L507">507</a>                 <a href="ident?i=BUG">BUG</a>();
<a name="L508" href="source/net/ipv4/ping.c#L508">508</a>         }
<a name="L509" href="source/net/ipv4/ping.c#L509">509</a> 
<a name="L510" href="source/net/ipv4/ping.c#L510">510</a>         <b><i>/* We assume the packet has already been checked by icmp_unreach */</i></b>
<a name="L511" href="source/net/ipv4/ping.c#L511">511</a> 
<a name="L512" href="source/net/ipv4/ping.c#L512">512</a>         if (!<a href="ident?i=ping_supported">ping_supported</a>(<a href="ident?i=family">family</a>, icmph-&gt;<a href="ident?i=type">type</a>, icmph-&gt;<a href="ident?i=code">code</a>))
<a name="L513" href="source/net/ipv4/ping.c#L513">513</a>                 return;
<a name="L514" href="source/net/ipv4/ping.c#L514">514</a> 
<a name="L515" href="source/net/ipv4/ping.c#L515">515</a>         <a href="ident?i=pr_debug">pr_debug</a>(<i>"ping_err(proto=0x%x,type=%d,code=%d,id=%04x,seq=%04x)\n"</i>,
<a name="L516" href="source/net/ipv4/ping.c#L516">516</a>                  <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=protocol">protocol</a>, <a href="ident?i=type">type</a>, <a href="ident?i=code">code</a>, <a href="ident?i=ntohs">ntohs</a>(icmph-&gt;un.<a href="ident?i=echo">echo</a>.<a href="ident?i=id">id</a>),
<a name="L517" href="source/net/ipv4/ping.c#L517">517</a>                  <a href="ident?i=ntohs">ntohs</a>(icmph-&gt;un.<a href="ident?i=echo">echo</a>.<a href="ident?i=sequence">sequence</a>));
<a name="L518" href="source/net/ipv4/ping.c#L518">518</a> 
<a name="L519" href="source/net/ipv4/ping.c#L519">519</a>         sk = <a href="ident?i=ping_lookup">ping_lookup</a>(<a href="ident?i=net">net</a>, <a href="ident?i=skb">skb</a>, <a href="ident?i=ntohs">ntohs</a>(icmph-&gt;un.<a href="ident?i=echo">echo</a>.<a href="ident?i=id">id</a>));
<a name="L520" href="source/net/ipv4/ping.c#L520">520</a>         if (!sk) {
<a name="L521" href="source/net/ipv4/ping.c#L521">521</a>                 <a href="ident?i=pr_debug">pr_debug</a>(<i>"no socket, dropping\n"</i>);
<a name="L522" href="source/net/ipv4/ping.c#L522">522</a>                 return; <b><i>/* No socket for error */</i></b>
<a name="L523" href="source/net/ipv4/ping.c#L523">523</a>         }
<a name="L524" href="source/net/ipv4/ping.c#L524">524</a>         <a href="ident?i=pr_debug">pr_debug</a>(<i>"err on socket %p\n"</i>, sk);
<a name="L525" href="source/net/ipv4/ping.c#L525">525</a> 
<a name="L526" href="source/net/ipv4/ping.c#L526">526</a>         <a href="ident?i=err">err</a> = 0;
<a name="L527" href="source/net/ipv4/ping.c#L527">527</a>         harderr = 0;
<a name="L528" href="source/net/ipv4/ping.c#L528">528</a>         <a href="ident?i=inet_sock">inet_sock</a> = <a href="ident?i=inet_sk">inet_sk</a>(sk);
<a name="L529" href="source/net/ipv4/ping.c#L529">529</a> 
<a name="L530" href="source/net/ipv4/ping.c#L530">530</a>         if (<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=protocol">protocol</a> == <a href="ident?i=htons">htons</a>(<a href="ident?i=ETH_P_IP">ETH_P_IP</a>)) {
<a name="L531" href="source/net/ipv4/ping.c#L531">531</a>                 switch (<a href="ident?i=type">type</a>) {
<a name="L532" href="source/net/ipv4/ping.c#L532">532</a>                 default:
<a name="L533" href="source/net/ipv4/ping.c#L533">533</a>                 case <a href="ident?i=ICMP_TIME_EXCEEDED">ICMP_TIME_EXCEEDED</a>:
<a name="L534" href="source/net/ipv4/ping.c#L534">534</a>                         <a href="ident?i=err">err</a> = <a href="ident?i=EHOSTUNREACH">EHOSTUNREACH</a>;
<a name="L535" href="source/net/ipv4/ping.c#L535">535</a>                         break;
<a name="L536" href="source/net/ipv4/ping.c#L536">536</a>                 case <a href="ident?i=ICMP_SOURCE_QUENCH">ICMP_SOURCE_QUENCH</a>:
<a name="L537" href="source/net/ipv4/ping.c#L537">537</a>                         <b><i>/* This is not a real error but ping wants to see it.</i></b>
<a name="L538" href="source/net/ipv4/ping.c#L538">538</a> <b><i>                         * Report it with some fake errno.</i></b>
<a name="L539" href="source/net/ipv4/ping.c#L539">539</a> <b><i>                         */</i></b>
<a name="L540" href="source/net/ipv4/ping.c#L540">540</a>                         <a href="ident?i=err">err</a> = <a href="ident?i=EREMOTEIO">EREMOTEIO</a>;
<a name="L541" href="source/net/ipv4/ping.c#L541">541</a>                         break;
<a name="L542" href="source/net/ipv4/ping.c#L542">542</a>                 case <a href="ident?i=ICMP_PARAMETERPROB">ICMP_PARAMETERPROB</a>:
<a name="L543" href="source/net/ipv4/ping.c#L543">543</a>                         <a href="ident?i=err">err</a> = <a href="ident?i=EPROTO">EPROTO</a>;
<a name="L544" href="source/net/ipv4/ping.c#L544">544</a>                         harderr = 1;
<a name="L545" href="source/net/ipv4/ping.c#L545">545</a>                         break;
<a name="L546" href="source/net/ipv4/ping.c#L546">546</a>                 case <a href="ident?i=ICMP_DEST_UNREACH">ICMP_DEST_UNREACH</a>:
<a name="L547" href="source/net/ipv4/ping.c#L547">547</a>                         if (<a href="ident?i=code">code</a> == <a href="ident?i=ICMP_FRAG_NEEDED">ICMP_FRAG_NEEDED</a>) { <b><i>/* Path MTU discovery */</i></b>
<a name="L548" href="source/net/ipv4/ping.c#L548">548</a>                                 <a href="ident?i=ipv4_sk_update_pmtu">ipv4_sk_update_pmtu</a>(<a href="ident?i=skb">skb</a>, sk, <a href="ident?i=info">info</a>);
<a name="L549" href="source/net/ipv4/ping.c#L549">549</a>                                 if (<a href="ident?i=inet_sock">inet_sock</a>-&gt;pmtudisc != <a href="ident?i=IP_PMTUDISC_DONT">IP_PMTUDISC_DONT</a>) {
<a name="L550" href="source/net/ipv4/ping.c#L550">550</a>                                         <a href="ident?i=err">err</a> = <a href="ident?i=EMSGSIZE">EMSGSIZE</a>;
<a name="L551" href="source/net/ipv4/ping.c#L551">551</a>                                         harderr = 1;
<a name="L552" href="source/net/ipv4/ping.c#L552">552</a>                                         break;
<a name="L553" href="source/net/ipv4/ping.c#L553">553</a>                                 }
<a name="L554" href="source/net/ipv4/ping.c#L554">554</a>                                 goto <a href="ident?i=out">out</a>;
<a name="L555" href="source/net/ipv4/ping.c#L555">555</a>                         }
<a name="L556" href="source/net/ipv4/ping.c#L556">556</a>                         <a href="ident?i=err">err</a> = <a href="ident?i=EHOSTUNREACH">EHOSTUNREACH</a>;
<a name="L557" href="source/net/ipv4/ping.c#L557">557</a>                         if (<a href="ident?i=code">code</a> &lt;= <a href="ident?i=NR_ICMP_UNREACH">NR_ICMP_UNREACH</a>) {
<a name="L558" href="source/net/ipv4/ping.c#L558">558</a>                                 harderr = <a href="ident?i=icmp_err_convert">icmp_err_convert</a>[<a href="ident?i=code">code</a>].<a href="ident?i=fatal">fatal</a>;
<a name="L559" href="source/net/ipv4/ping.c#L559">559</a>                                 <a href="ident?i=err">err</a> = <a href="ident?i=icmp_err_convert">icmp_err_convert</a>[<a href="ident?i=code">code</a>].<a href="ident?i=errno">errno</a>;
<a name="L560" href="source/net/ipv4/ping.c#L560">560</a>                         }
<a name="L561" href="source/net/ipv4/ping.c#L561">561</a>                         break;
<a name="L562" href="source/net/ipv4/ping.c#L562">562</a>                 case <a href="ident?i=ICMP_REDIRECT">ICMP_REDIRECT</a>:
<a name="L563" href="source/net/ipv4/ping.c#L563">563</a>                         <b><i>/* See ICMP_SOURCE_QUENCH */</i></b>
<a name="L564" href="source/net/ipv4/ping.c#L564">564</a>                         <a href="ident?i=ipv4_sk_redirect">ipv4_sk_redirect</a>(<a href="ident?i=skb">skb</a>, sk);
<a name="L565" href="source/net/ipv4/ping.c#L565">565</a>                         <a href="ident?i=err">err</a> = <a href="ident?i=EREMOTEIO">EREMOTEIO</a>;
<a name="L566" href="source/net/ipv4/ping.c#L566">566</a>                         break;
<a name="L567" href="source/net/ipv4/ping.c#L567">567</a>                 }
<a name="L568" href="source/net/ipv4/ping.c#L568">568</a> #if <a href="ident?i=IS_ENABLED">IS_ENABLED</a>(CONFIG_IPV6)
<a name="L569" href="source/net/ipv4/ping.c#L569">569</a>         } else if (<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=protocol">protocol</a> == <a href="ident?i=htons">htons</a>(<a href="ident?i=ETH_P_IPV6">ETH_P_IPV6</a>)) {
<a name="L570" href="source/net/ipv4/ping.c#L570">570</a>                 harderr = <a href="ident?i=pingv6_ops">pingv6_ops</a>.<a href="ident?i=icmpv6_err_convert">icmpv6_err_convert</a>(<a href="ident?i=type">type</a>, <a href="ident?i=code">code</a>, &amp;<a href="ident?i=err">err</a>);
<a name="L571" href="source/net/ipv4/ping.c#L571">571</a> #endif
<a name="L572" href="source/net/ipv4/ping.c#L572">572</a>         }
<a name="L573" href="source/net/ipv4/ping.c#L573">573</a> 
<a name="L574" href="source/net/ipv4/ping.c#L574">574</a>         <b><i>/*</i></b>
<a name="L575" href="source/net/ipv4/ping.c#L575">575</a> <b><i>         *      RFC1122: OK.  Passes ICMP errors back to application, as per</i></b>
<a name="L576" href="source/net/ipv4/ping.c#L576">576</a> <b><i>         *      4.1.3.3.</i></b>
<a name="L577" href="source/net/ipv4/ping.c#L577">577</a> <b><i>         */</i></b>
<a name="L578" href="source/net/ipv4/ping.c#L578">578</a>         if ((<a href="ident?i=family">family</a> == <a href="ident?i=AF_INET">AF_INET</a> &amp;&amp; !<a href="ident?i=inet_sock">inet_sock</a>-&gt;recverr) ||
<a name="L579" href="source/net/ipv4/ping.c#L579">579</a>             (<a href="ident?i=family">family</a> == <a href="ident?i=AF_INET6">AF_INET6</a> &amp;&amp; !<a href="ident?i=inet6_sk">inet6_sk</a>(sk)-&gt;recverr)) {
<a name="L580" href="source/net/ipv4/ping.c#L580">580</a>                 if (!harderr || sk-&gt;<a href="ident?i=sk_state">sk_state</a> != TCP_ESTABLISHED)
<a name="L581" href="source/net/ipv4/ping.c#L581">581</a>                         goto <a href="ident?i=out">out</a>;
<a name="L582" href="source/net/ipv4/ping.c#L582">582</a>         } else {
<a name="L583" href="source/net/ipv4/ping.c#L583">583</a>                 if (<a href="ident?i=family">family</a> == <a href="ident?i=AF_INET">AF_INET</a>) {
<a name="L584" href="source/net/ipv4/ping.c#L584">584</a>                         <a href="ident?i=ip_icmp_error">ip_icmp_error</a>(sk, <a href="ident?i=skb">skb</a>, <a href="ident?i=err">err</a>, 0 <b><i>/* no remote port */</i></b>,
<a name="L585" href="source/net/ipv4/ping.c#L585">585</a>                                       <a href="ident?i=info">info</a>, (<a href="ident?i=u8">u8</a> *)icmph);
<a name="L586" href="source/net/ipv4/ping.c#L586">586</a> #if <a href="ident?i=IS_ENABLED">IS_ENABLED</a>(CONFIG_IPV6)
<a name="L587" href="source/net/ipv4/ping.c#L587">587</a>                 } else if (<a href="ident?i=family">family</a> == <a href="ident?i=AF_INET6">AF_INET6</a>) {
<a name="L588" href="source/net/ipv4/ping.c#L588">588</a>                         <a href="ident?i=pingv6_ops">pingv6_ops</a>.<a href="ident?i=ipv6_icmp_error">ipv6_icmp_error</a>(sk, <a href="ident?i=skb">skb</a>, <a href="ident?i=err">err</a>, 0,
<a name="L589" href="source/net/ipv4/ping.c#L589">589</a>                                                    <a href="ident?i=info">info</a>, (<a href="ident?i=u8">u8</a> *)icmph);
<a name="L590" href="source/net/ipv4/ping.c#L590">590</a> #endif
<a name="L591" href="source/net/ipv4/ping.c#L591">591</a>                 }
<a name="L592" href="source/net/ipv4/ping.c#L592">592</a>         }
<a name="L593" href="source/net/ipv4/ping.c#L593">593</a>         sk-&gt;sk_err = <a href="ident?i=err">err</a>;
<a name="L594" href="source/net/ipv4/ping.c#L594">594</a>         sk-&gt;sk_error_report(sk);
<a name="L595" href="source/net/ipv4/ping.c#L595">595</a> <a href="ident?i=out">out</a>:
<a name="L596" href="source/net/ipv4/ping.c#L596">596</a>         <a href="ident?i=sock_put">sock_put</a>(sk);
<a name="L597" href="source/net/ipv4/ping.c#L597">597</a> }
<a name="L598" href="source/net/ipv4/ping.c#L598">598</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=ping_err">ping_err</a>);
<a name="L599" href="source/net/ipv4/ping.c#L599">599</a> 
<a name="L600" href="source/net/ipv4/ping.c#L600">600</a> <b><i>/*</i></b>
<a name="L601" href="source/net/ipv4/ping.c#L601">601</a> <b><i> *      Copy and checksum an ICMP Echo packet from user space into a buffer</i></b>
<a name="L602" href="source/net/ipv4/ping.c#L602">602</a> <b><i> *      starting from the payload.</i></b>
<a name="L603" href="source/net/ipv4/ping.c#L603">603</a> <b><i> */</i></b>
<a name="L604" href="source/net/ipv4/ping.c#L604">604</a> 
<a name="L605" href="source/net/ipv4/ping.c#L605">605</a> int <a href="ident?i=ping_getfrag">ping_getfrag</a>(void *from, char *to,
<a name="L606" href="source/net/ipv4/ping.c#L606">606</a>                  int <a href="ident?i=offset">offset</a>, int fraglen, int odd, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L607" href="source/net/ipv4/ping.c#L607">607</a> {
<a name="L608" href="source/net/ipv4/ping.c#L608">608</a>         struct <a href="ident?i=pingfakehdr">pingfakehdr</a> *pfh = (struct <a href="ident?i=pingfakehdr">pingfakehdr</a> *)from;
<a name="L609" href="source/net/ipv4/ping.c#L609">609</a> 
<a name="L610" href="source/net/ipv4/ping.c#L610">610</a>         if (<a href="ident?i=offset">offset</a> == 0) {
<a name="L611" href="source/net/ipv4/ping.c#L611">611</a>                 fraglen -= sizeof(struct <a href="ident?i=icmphdr">icmphdr</a>);
<a name="L612" href="source/net/ipv4/ping.c#L612">612</a>                 if (fraglen &lt; 0)
<a name="L613" href="source/net/ipv4/ping.c#L613">613</a>                         <a href="ident?i=BUG">BUG</a>();
<a name="L614" href="source/net/ipv4/ping.c#L614">614</a>                 if (<a href="ident?i=csum_and_copy_from_iter">csum_and_copy_from_iter</a>(to + sizeof(struct <a href="ident?i=icmphdr">icmphdr</a>),
<a name="L615" href="source/net/ipv4/ping.c#L615">615</a>                             fraglen, &amp;pfh-&gt;wcheck,
<a name="L616" href="source/net/ipv4/ping.c#L616">616</a>                             &amp;pfh-&gt;<a href="ident?i=msg">msg</a>-&gt;msg_iter) != fraglen)
<a name="L617" href="source/net/ipv4/ping.c#L617">617</a>                         return -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L618" href="source/net/ipv4/ping.c#L618">618</a>         } else if (<a href="ident?i=offset">offset</a> &lt; sizeof(struct <a href="ident?i=icmphdr">icmphdr</a>)) {
<a name="L619" href="source/net/ipv4/ping.c#L619">619</a>                         <a href="ident?i=BUG">BUG</a>();
<a name="L620" href="source/net/ipv4/ping.c#L620">620</a>         } else {
<a name="L621" href="source/net/ipv4/ping.c#L621">621</a>                 if (<a href="ident?i=csum_and_copy_from_iter">csum_and_copy_from_iter</a>(to, fraglen, &amp;pfh-&gt;wcheck,
<a name="L622" href="source/net/ipv4/ping.c#L622">622</a>                                             &amp;pfh-&gt;<a href="ident?i=msg">msg</a>-&gt;msg_iter) != fraglen)
<a name="L623" href="source/net/ipv4/ping.c#L623">623</a>                         return -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L624" href="source/net/ipv4/ping.c#L624">624</a>         }
<a name="L625" href="source/net/ipv4/ping.c#L625">625</a> 
<a name="L626" href="source/net/ipv4/ping.c#L626">626</a> #if <a href="ident?i=IS_ENABLED">IS_ENABLED</a>(CONFIG_IPV6)
<a name="L627" href="source/net/ipv4/ping.c#L627">627</a>         <b><i>/* For IPv6, checksum each skb as we go along, as expected by</i></b>
<a name="L628" href="source/net/ipv4/ping.c#L628">628</a> <b><i>         * icmpv6_push_pending_frames. For IPv4, accumulate the checksum in</i></b>
<a name="L629" href="source/net/ipv4/ping.c#L629">629</a> <b><i>         * wcheck, it will be finalized in ping_v4_push_pending_frames.</i></b>
<a name="L630" href="source/net/ipv4/ping.c#L630">630</a> <b><i>         */</i></b>
<a name="L631" href="source/net/ipv4/ping.c#L631">631</a>         if (pfh-&gt;<a href="ident?i=family">family</a> == <a href="ident?i=AF_INET6">AF_INET6</a>) {
<a name="L632" href="source/net/ipv4/ping.c#L632">632</a>                 <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=csum">csum</a> = pfh-&gt;wcheck;
<a name="L633" href="source/net/ipv4/ping.c#L633">633</a>                 <a href="ident?i=skb">skb</a>-&gt;ip_summed = <a href="ident?i=CHECKSUM_NONE">CHECKSUM_NONE</a>;
<a name="L634" href="source/net/ipv4/ping.c#L634">634</a>                 pfh-&gt;wcheck = 0;
<a name="L635" href="source/net/ipv4/ping.c#L635">635</a>         }
<a name="L636" href="source/net/ipv4/ping.c#L636">636</a> #endif
<a name="L637" href="source/net/ipv4/ping.c#L637">637</a> 
<a name="L638" href="source/net/ipv4/ping.c#L638">638</a>         return 0;
<a name="L639" href="source/net/ipv4/ping.c#L639">639</a> }
<a name="L640" href="source/net/ipv4/ping.c#L640">640</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=ping_getfrag">ping_getfrag</a>);
<a name="L641" href="source/net/ipv4/ping.c#L641">641</a> 
<a name="L642" href="source/net/ipv4/ping.c#L642">642</a> static int <a href="ident?i=ping_v4_push_pending_frames">ping_v4_push_pending_frames</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=pingfakehdr">pingfakehdr</a> *pfh,
<a name="L643" href="source/net/ipv4/ping.c#L643">643</a>                                        struct <a href="ident?i=flowi4">flowi4</a> *fl4)
<a name="L644" href="source/net/ipv4/ping.c#L644">644</a> {
<a name="L645" href="source/net/ipv4/ping.c#L645">645</a>         struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a> = <a href="ident?i=skb_peek">skb_peek</a>(&amp;sk-&gt;sk_write_queue);
<a name="L646" href="source/net/ipv4/ping.c#L646">646</a> 
<a name="L647" href="source/net/ipv4/ping.c#L647">647</a>         pfh-&gt;wcheck = <a href="ident?i=csum_partial">csum_partial</a>((char *)&amp;pfh-&gt;icmph,
<a name="L648" href="source/net/ipv4/ping.c#L648">648</a>                 sizeof(struct <a href="ident?i=icmphdr">icmphdr</a>), pfh-&gt;wcheck);
<a name="L649" href="source/net/ipv4/ping.c#L649">649</a>         pfh-&gt;icmph.<a href="ident?i=checksum">checksum</a> = <a href="ident?i=csum_fold">csum_fold</a>(pfh-&gt;wcheck);
<a name="L650" href="source/net/ipv4/ping.c#L650">650</a>         <a href="ident?i=memcpy">memcpy</a>(<a href="ident?i=icmp_hdr">icmp_hdr</a>(<a href="ident?i=skb">skb</a>), &amp;pfh-&gt;icmph, sizeof(struct <a href="ident?i=icmphdr">icmphdr</a>));
<a name="L651" href="source/net/ipv4/ping.c#L651">651</a>         <a href="ident?i=skb">skb</a>-&gt;ip_summed = <a href="ident?i=CHECKSUM_NONE">CHECKSUM_NONE</a>;
<a name="L652" href="source/net/ipv4/ping.c#L652">652</a>         return <a href="ident?i=ip_push_pending_frames">ip_push_pending_frames</a>(sk, fl4);
<a name="L653" href="source/net/ipv4/ping.c#L653">653</a> }
<a name="L654" href="source/net/ipv4/ping.c#L654">654</a> 
<a name="L655" href="source/net/ipv4/ping.c#L655">655</a> int <a href="ident?i=ping_common_sendmsg">ping_common_sendmsg</a>(int <a href="ident?i=family">family</a>, struct <a href="ident?i=msghdr">msghdr</a> *<a href="ident?i=msg">msg</a>, <a href="ident?i=size_t">size_t</a> <a href="ident?i=len">len</a>,
<a name="L656" href="source/net/ipv4/ping.c#L656">656</a>                         void *user_icmph, <a href="ident?i=size_t">size_t</a> icmph_len) {
<a name="L657" href="source/net/ipv4/ping.c#L657">657</a>         <a href="ident?i=u8">u8</a> <a href="ident?i=type">type</a>, <a href="ident?i=code">code</a>;
<a name="L658" href="source/net/ipv4/ping.c#L658">658</a> 
<a name="L659" href="source/net/ipv4/ping.c#L659">659</a>         if (<a href="ident?i=len">len</a> &gt; 0xFFFF)
<a name="L660" href="source/net/ipv4/ping.c#L660">660</a>                 return -<a href="ident?i=EMSGSIZE">EMSGSIZE</a>;
<a name="L661" href="source/net/ipv4/ping.c#L661">661</a> 
<a name="L662" href="source/net/ipv4/ping.c#L662">662</a>         <b><i>/*</i></b>
<a name="L663" href="source/net/ipv4/ping.c#L663">663</a> <b><i>         *      Check the flags.</i></b>
<a name="L664" href="source/net/ipv4/ping.c#L664">664</a> <b><i>         */</i></b>
<a name="L665" href="source/net/ipv4/ping.c#L665">665</a> 
<a name="L666" href="source/net/ipv4/ping.c#L666">666</a>         <b><i>/* Mirror BSD error message compatibility */</i></b>
<a name="L667" href="source/net/ipv4/ping.c#L667">667</a>         if (<a href="ident?i=msg">msg</a>-&gt;msg_flags &amp; <a href="ident?i=MSG_OOB">MSG_OOB</a>)
<a name="L668" href="source/net/ipv4/ping.c#L668">668</a>                 return -<a href="ident?i=EOPNOTSUPP">EOPNOTSUPP</a>;
<a name="L669" href="source/net/ipv4/ping.c#L669">669</a> 
<a name="L670" href="source/net/ipv4/ping.c#L670">670</a>         <b><i>/*</i></b>
<a name="L671" href="source/net/ipv4/ping.c#L671">671</a> <b><i>         *      Fetch the ICMP header provided by the userland.</i></b>
<a name="L672" href="source/net/ipv4/ping.c#L672">672</a> <b><i>         *      iovec is modified! The ICMP header is consumed.</i></b>
<a name="L673" href="source/net/ipv4/ping.c#L673">673</a> <b><i>         */</i></b>
<a name="L674" href="source/net/ipv4/ping.c#L674">674</a>         if (<a href="ident?i=memcpy_from_msg">memcpy_from_msg</a>(user_icmph, <a href="ident?i=msg">msg</a>, icmph_len))
<a name="L675" href="source/net/ipv4/ping.c#L675">675</a>                 return -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L676" href="source/net/ipv4/ping.c#L676">676</a> 
<a name="L677" href="source/net/ipv4/ping.c#L677">677</a>         if (<a href="ident?i=family">family</a> == <a href="ident?i=AF_INET">AF_INET</a>) {
<a name="L678" href="source/net/ipv4/ping.c#L678">678</a>                 <a href="ident?i=type">type</a> = ((struct <a href="ident?i=icmphdr">icmphdr</a> *) user_icmph)-&gt;<a href="ident?i=type">type</a>;
<a name="L679" href="source/net/ipv4/ping.c#L679">679</a>                 <a href="ident?i=code">code</a> = ((struct <a href="ident?i=icmphdr">icmphdr</a> *) user_icmph)-&gt;<a href="ident?i=code">code</a>;
<a name="L680" href="source/net/ipv4/ping.c#L680">680</a> #if <a href="ident?i=IS_ENABLED">IS_ENABLED</a>(CONFIG_IPV6)
<a name="L681" href="source/net/ipv4/ping.c#L681">681</a>         } else if (<a href="ident?i=family">family</a> == <a href="ident?i=AF_INET6">AF_INET6</a>) {
<a name="L682" href="source/net/ipv4/ping.c#L682">682</a>                 <a href="ident?i=type">type</a> = ((struct <a href="ident?i=icmp6hdr">icmp6hdr</a> *) user_icmph)-&gt;icmp6_type;
<a name="L683" href="source/net/ipv4/ping.c#L683">683</a>                 <a href="ident?i=code">code</a> = ((struct <a href="ident?i=icmp6hdr">icmp6hdr</a> *) user_icmph)-&gt;icmp6_code;
<a name="L684" href="source/net/ipv4/ping.c#L684">684</a> #endif
<a name="L685" href="source/net/ipv4/ping.c#L685">685</a>         } else {
<a name="L686" href="source/net/ipv4/ping.c#L686">686</a>                 <a href="ident?i=BUG">BUG</a>();
<a name="L687" href="source/net/ipv4/ping.c#L687">687</a>         }
<a name="L688" href="source/net/ipv4/ping.c#L688">688</a> 
<a name="L689" href="source/net/ipv4/ping.c#L689">689</a>         if (!<a href="ident?i=ping_supported">ping_supported</a>(<a href="ident?i=family">family</a>, <a href="ident?i=type">type</a>, <a href="ident?i=code">code</a>))
<a name="L690" href="source/net/ipv4/ping.c#L690">690</a>                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L691" href="source/net/ipv4/ping.c#L691">691</a> 
<a name="L692" href="source/net/ipv4/ping.c#L692">692</a>         return 0;
<a name="L693" href="source/net/ipv4/ping.c#L693">693</a> }
<a name="L694" href="source/net/ipv4/ping.c#L694">694</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=ping_common_sendmsg">ping_common_sendmsg</a>);
<a name="L695" href="source/net/ipv4/ping.c#L695">695</a> 
<a name="L696" href="source/net/ipv4/ping.c#L696">696</a> static int <a href="ident?i=ping_v4_sendmsg">ping_v4_sendmsg</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=msghdr">msghdr</a> *<a href="ident?i=msg">msg</a>, <a href="ident?i=size_t">size_t</a> <a href="ident?i=len">len</a>)
<a name="L697" href="source/net/ipv4/ping.c#L697">697</a> {
<a name="L698" href="source/net/ipv4/ping.c#L698">698</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=sock_net">sock_net</a>(sk);
<a name="L699" href="source/net/ipv4/ping.c#L699">699</a>         struct <a href="ident?i=flowi4">flowi4</a> fl4;
<a name="L700" href="source/net/ipv4/ping.c#L700">700</a>         struct <a href="ident?i=inet_sock">inet_sock</a> *inet = <a href="ident?i=inet_sk">inet_sk</a>(sk);
<a name="L701" href="source/net/ipv4/ping.c#L701">701</a>         struct <a href="ident?i=ipcm_cookie">ipcm_cookie</a> ipc;
<a name="L702" href="source/net/ipv4/ping.c#L702">702</a>         struct <a href="ident?i=icmphdr">icmphdr</a> user_icmph;
<a name="L703" href="source/net/ipv4/ping.c#L703">703</a>         struct <a href="ident?i=pingfakehdr">pingfakehdr</a> pfh;
<a name="L704" href="source/net/ipv4/ping.c#L704">704</a>         struct <a href="ident?i=rtable">rtable</a> *<a href="ident?i=rt">rt</a> = <a href="ident?i=NULL">NULL</a>;
<a name="L705" href="source/net/ipv4/ping.c#L705">705</a>         struct <a href="ident?i=ip_options_data">ip_options_data</a> opt_copy;
<a name="L706" href="source/net/ipv4/ping.c#L706">706</a>         int <a href="ident?i=free">free</a> = 0;
<a name="L707" href="source/net/ipv4/ping.c#L707">707</a>         <a href="ident?i=__be32">__be32</a> <a href="ident?i=saddr">saddr</a>, <a href="ident?i=daddr">daddr</a>, faddr;
<a name="L708" href="source/net/ipv4/ping.c#L708">708</a>         <a href="ident?i=u8">u8</a>  tos;
<a name="L709" href="source/net/ipv4/ping.c#L709">709</a>         int <a href="ident?i=err">err</a>;
<a name="L710" href="source/net/ipv4/ping.c#L710">710</a> 
<a name="L711" href="source/net/ipv4/ping.c#L711">711</a>         <a href="ident?i=pr_debug">pr_debug</a>(<i>"ping_v4_sendmsg(sk=%p,sk-&gt;num=%u)\n"</i>, inet, inet-&gt;<a href="ident?i=inet_num">inet_num</a>);
<a name="L712" href="source/net/ipv4/ping.c#L712">712</a> 
<a name="L713" href="source/net/ipv4/ping.c#L713">713</a>         <a href="ident?i=err">err</a> = <a href="ident?i=ping_common_sendmsg">ping_common_sendmsg</a>(<a href="ident?i=AF_INET">AF_INET</a>, <a href="ident?i=msg">msg</a>, <a href="ident?i=len">len</a>, &amp;user_icmph,
<a name="L714" href="source/net/ipv4/ping.c#L714">714</a>                                   sizeof(user_icmph));
<a name="L715" href="source/net/ipv4/ping.c#L715">715</a>         if (<a href="ident?i=err">err</a>)
<a name="L716" href="source/net/ipv4/ping.c#L716">716</a>                 return <a href="ident?i=err">err</a>;
<a name="L717" href="source/net/ipv4/ping.c#L717">717</a> 
<a name="L718" href="source/net/ipv4/ping.c#L718">718</a>         <b><i>/*</i></b>
<a name="L719" href="source/net/ipv4/ping.c#L719">719</a> <b><i>         *      Get and verify the address.</i></b>
<a name="L720" href="source/net/ipv4/ping.c#L720">720</a> <b><i>         */</i></b>
<a name="L721" href="source/net/ipv4/ping.c#L721">721</a> 
<a name="L722" href="source/net/ipv4/ping.c#L722">722</a>         if (<a href="ident?i=msg">msg</a>-&gt;msg_name) {
<a name="L723" href="source/net/ipv4/ping.c#L723">723</a>                 <a href="ident?i=DECLARE_SOCKADDR">DECLARE_SOCKADDR</a>(struct <a href="ident?i=sockaddr_in">sockaddr_in</a> *, usin, <a href="ident?i=msg">msg</a>-&gt;msg_name);
<a name="L724" href="source/net/ipv4/ping.c#L724">724</a>                 if (<a href="ident?i=msg">msg</a>-&gt;msg_namelen &lt; sizeof(*usin))
<a name="L725" href="source/net/ipv4/ping.c#L725">725</a>                         return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L726" href="source/net/ipv4/ping.c#L726">726</a>                 if (usin-&gt;sin_family != <a href="ident?i=AF_INET">AF_INET</a>)
<a name="L727" href="source/net/ipv4/ping.c#L727">727</a>                         return -<a href="ident?i=EAFNOSUPPORT">EAFNOSUPPORT</a>;
<a name="L728" href="source/net/ipv4/ping.c#L728">728</a>                 <a href="ident?i=daddr">daddr</a> = usin-&gt;sin_addr.s_addr;
<a name="L729" href="source/net/ipv4/ping.c#L729">729</a>                 <b><i>/* no remote port */</i></b>
<a name="L730" href="source/net/ipv4/ping.c#L730">730</a>         } else {
<a name="L731" href="source/net/ipv4/ping.c#L731">731</a>                 if (sk-&gt;<a href="ident?i=sk_state">sk_state</a> != TCP_ESTABLISHED)
<a name="L732" href="source/net/ipv4/ping.c#L732">732</a>                         return -<a href="ident?i=EDESTADDRREQ">EDESTADDRREQ</a>;
<a name="L733" href="source/net/ipv4/ping.c#L733">733</a>                 <a href="ident?i=daddr">daddr</a> = inet-&gt;<a href="ident?i=inet_daddr">inet_daddr</a>;
<a name="L734" href="source/net/ipv4/ping.c#L734">734</a>                 <b><i>/* no remote port */</i></b>
<a name="L735" href="source/net/ipv4/ping.c#L735">735</a>         }
<a name="L736" href="source/net/ipv4/ping.c#L736">736</a> 
<a name="L737" href="source/net/ipv4/ping.c#L737">737</a>         ipc.<a href="ident?i=addr">addr</a> = inet-&gt;inet_saddr;
<a name="L738" href="source/net/ipv4/ping.c#L738">738</a>         ipc.opt = <a href="ident?i=NULL">NULL</a>;
<a name="L739" href="source/net/ipv4/ping.c#L739">739</a>         ipc.oif = sk-&gt;<a href="ident?i=sk_bound_dev_if">sk_bound_dev_if</a>;
<a name="L740" href="source/net/ipv4/ping.c#L740">740</a>         ipc.tx_flags = 0;
<a name="L741" href="source/net/ipv4/ping.c#L741">741</a>         ipc.<a href="ident?i=ttl">ttl</a> = 0;
<a name="L742" href="source/net/ipv4/ping.c#L742">742</a>         ipc.tos = -1;
<a name="L743" href="source/net/ipv4/ping.c#L743">743</a> 
<a name="L744" href="source/net/ipv4/ping.c#L744">744</a>         <a href="ident?i=sock_tx_timestamp">sock_tx_timestamp</a>(sk, &amp;ipc.tx_flags);
<a name="L745" href="source/net/ipv4/ping.c#L745">745</a> 
<a name="L746" href="source/net/ipv4/ping.c#L746">746</a>         if (<a href="ident?i=msg">msg</a>-&gt;msg_controllen) {
<a name="L747" href="source/net/ipv4/ping.c#L747">747</a>                 <a href="ident?i=err">err</a> = <a href="ident?i=ip_cmsg_send">ip_cmsg_send</a>(<a href="ident?i=sock_net">sock_net</a>(sk), <a href="ident?i=msg">msg</a>, &amp;ipc, <a href="ident?i=false">false</a>);
<a name="L748" href="source/net/ipv4/ping.c#L748">748</a>                 if (<a href="ident?i=err">err</a>)
<a name="L749" href="source/net/ipv4/ping.c#L749">749</a>                         return <a href="ident?i=err">err</a>;
<a name="L750" href="source/net/ipv4/ping.c#L750">750</a>                 if (ipc.opt)
<a name="L751" href="source/net/ipv4/ping.c#L751">751</a>                         <a href="ident?i=free">free</a> = 1;
<a name="L752" href="source/net/ipv4/ping.c#L752">752</a>         }
<a name="L753" href="source/net/ipv4/ping.c#L753">753</a>         if (!ipc.opt) {
<a name="L754" href="source/net/ipv4/ping.c#L754">754</a>                 struct <a href="ident?i=ip_options_rcu">ip_options_rcu</a> *inet_opt;
<a name="L755" href="source/net/ipv4/ping.c#L755">755</a> 
<a name="L756" href="source/net/ipv4/ping.c#L756">756</a>                 <a href="ident?i=rcu_read_lock">rcu_read_lock</a>();
<a name="L757" href="source/net/ipv4/ping.c#L757">757</a>                 inet_opt = <a href="ident?i=rcu_dereference">rcu_dereference</a>(inet-&gt;inet_opt);
<a name="L758" href="source/net/ipv4/ping.c#L758">758</a>                 if (inet_opt) {
<a name="L759" href="source/net/ipv4/ping.c#L759">759</a>                         <a href="ident?i=memcpy">memcpy</a>(&amp;opt_copy, inet_opt,
<a name="L760" href="source/net/ipv4/ping.c#L760">760</a>                                sizeof(*inet_opt) + inet_opt-&gt;opt.<a href="ident?i=optlen">optlen</a>);
<a name="L761" href="source/net/ipv4/ping.c#L761">761</a>                         ipc.opt = &amp;opt_copy.opt;
<a name="L762" href="source/net/ipv4/ping.c#L762">762</a>                 }
<a name="L763" href="source/net/ipv4/ping.c#L763">763</a>                 <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L764" href="source/net/ipv4/ping.c#L764">764</a>         }
<a name="L765" href="source/net/ipv4/ping.c#L765">765</a> 
<a name="L766" href="source/net/ipv4/ping.c#L766">766</a>         <a href="ident?i=saddr">saddr</a> = ipc.<a href="ident?i=addr">addr</a>;
<a name="L767" href="source/net/ipv4/ping.c#L767">767</a>         ipc.<a href="ident?i=addr">addr</a> = faddr = <a href="ident?i=daddr">daddr</a>;
<a name="L768" href="source/net/ipv4/ping.c#L768">768</a> 
<a name="L769" href="source/net/ipv4/ping.c#L769">769</a>         if (ipc.opt &amp;&amp; ipc.opt-&gt;opt.<a href="ident?i=srr">srr</a>) {
<a name="L770" href="source/net/ipv4/ping.c#L770">770</a>                 if (!<a href="ident?i=daddr">daddr</a>)
<a name="L771" href="source/net/ipv4/ping.c#L771">771</a>                         return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L772" href="source/net/ipv4/ping.c#L772">772</a>                 faddr = ipc.opt-&gt;opt.faddr;
<a name="L773" href="source/net/ipv4/ping.c#L773">773</a>         }
<a name="L774" href="source/net/ipv4/ping.c#L774">774</a>         tos = <a href="ident?i=get_rttos">get_rttos</a>(&amp;ipc, inet);
<a name="L775" href="source/net/ipv4/ping.c#L775">775</a>         if (<a href="ident?i=sock_flag">sock_flag</a>(sk, SOCK_LOCALROUTE) ||
<a name="L776" href="source/net/ipv4/ping.c#L776">776</a>             (<a href="ident?i=msg">msg</a>-&gt;msg_flags &amp; <a href="ident?i=MSG_DONTROUTE">MSG_DONTROUTE</a>) ||
<a name="L777" href="source/net/ipv4/ping.c#L777">777</a>             (ipc.opt &amp;&amp; ipc.opt-&gt;opt.is_strictroute)) {
<a name="L778" href="source/net/ipv4/ping.c#L778">778</a>                 tos |= <a href="ident?i=RTO_ONLINK">RTO_ONLINK</a>;
<a name="L779" href="source/net/ipv4/ping.c#L779">779</a>         }
<a name="L780" href="source/net/ipv4/ping.c#L780">780</a> 
<a name="L781" href="source/net/ipv4/ping.c#L781">781</a>         if (<a href="ident?i=ipv4_is_multicast">ipv4_is_multicast</a>(<a href="ident?i=daddr">daddr</a>)) {
<a name="L782" href="source/net/ipv4/ping.c#L782">782</a>                 if (!ipc.oif)
<a name="L783" href="source/net/ipv4/ping.c#L783">783</a>                         ipc.oif = inet-&gt;mc_index;
<a name="L784" href="source/net/ipv4/ping.c#L784">784</a>                 if (!<a href="ident?i=saddr">saddr</a>)
<a name="L785" href="source/net/ipv4/ping.c#L785">785</a>                         <a href="ident?i=saddr">saddr</a> = inet-&gt;mc_addr;
<a name="L786" href="source/net/ipv4/ping.c#L786">786</a>         } else if (!ipc.oif)
<a name="L787" href="source/net/ipv4/ping.c#L787">787</a>                 ipc.oif = inet-&gt;uc_index;
<a name="L788" href="source/net/ipv4/ping.c#L788">788</a> 
<a name="L789" href="source/net/ipv4/ping.c#L789">789</a>         <a href="ident?i=flowi4_init_output">flowi4_init_output</a>(&amp;fl4, ipc.oif, sk-&gt;sk_mark, tos,
<a name="L790" href="source/net/ipv4/ping.c#L790">790</a>                            RT_SCOPE_UNIVERSE, sk-&gt;sk_protocol,
<a name="L791" href="source/net/ipv4/ping.c#L791">791</a>                            <a href="ident?i=inet_sk_flowi_flags">inet_sk_flowi_flags</a>(sk), faddr, <a href="ident?i=saddr">saddr</a>, 0, 0);
<a name="L792" href="source/net/ipv4/ping.c#L792">792</a> 
<a name="L793" href="source/net/ipv4/ping.c#L793">793</a>         <a href="ident?i=security_sk_classify_flow">security_sk_classify_flow</a>(sk, <a href="ident?i=flowi4_to_flowi">flowi4_to_flowi</a>(&amp;fl4));
<a name="L794" href="source/net/ipv4/ping.c#L794">794</a>         <a href="ident?i=rt">rt</a> = <a href="ident?i=ip_route_output_flow">ip_route_output_flow</a>(<a href="ident?i=net">net</a>, &amp;fl4, sk);
<a name="L795" href="source/net/ipv4/ping.c#L795">795</a>         if (<a href="ident?i=IS_ERR">IS_ERR</a>(<a href="ident?i=rt">rt</a>)) {
<a name="L796" href="source/net/ipv4/ping.c#L796">796</a>                 <a href="ident?i=err">err</a> = <a href="ident?i=PTR_ERR">PTR_ERR</a>(<a href="ident?i=rt">rt</a>);
<a name="L797" href="source/net/ipv4/ping.c#L797">797</a>                 <a href="ident?i=rt">rt</a> = <a href="ident?i=NULL">NULL</a>;
<a name="L798" href="source/net/ipv4/ping.c#L798">798</a>                 if (<a href="ident?i=err">err</a> == -<a href="ident?i=ENETUNREACH">ENETUNREACH</a>)
<a name="L799" href="source/net/ipv4/ping.c#L799">799</a>                         <a href="ident?i=IP_INC_STATS">IP_INC_STATS</a>(<a href="ident?i=net">net</a>, IPSTATS_MIB_OUTNOROUTES);
<a name="L800" href="source/net/ipv4/ping.c#L800">800</a>                 goto <a href="ident?i=out">out</a>;
<a name="L801" href="source/net/ipv4/ping.c#L801">801</a>         }
<a name="L802" href="source/net/ipv4/ping.c#L802">802</a> 
<a name="L803" href="source/net/ipv4/ping.c#L803">803</a>         <a href="ident?i=err">err</a> = -<a href="ident?i=EACCES">EACCES</a>;
<a name="L804" href="source/net/ipv4/ping.c#L804">804</a>         if ((<a href="ident?i=rt">rt</a>-&gt;rt_flags &amp; <a href="ident?i=RTCF_BROADCAST">RTCF_BROADCAST</a>) &amp;&amp;
<a name="L805" href="source/net/ipv4/ping.c#L805">805</a>             !<a href="ident?i=sock_flag">sock_flag</a>(sk, SOCK_BROADCAST))
<a name="L806" href="source/net/ipv4/ping.c#L806">806</a>                 goto <a href="ident?i=out">out</a>;
<a name="L807" href="source/net/ipv4/ping.c#L807">807</a> 
<a name="L808" href="source/net/ipv4/ping.c#L808">808</a>         if (<a href="ident?i=msg">msg</a>-&gt;msg_flags &amp; <a href="ident?i=MSG_CONFIRM">MSG_CONFIRM</a>)
<a name="L809" href="source/net/ipv4/ping.c#L809">809</a>                 goto do_confirm;
<a name="L810" href="source/net/ipv4/ping.c#L810">810</a> back_from_confirm:
<a name="L811" href="source/net/ipv4/ping.c#L811">811</a> 
<a name="L812" href="source/net/ipv4/ping.c#L812">812</a>         if (!ipc.<a href="ident?i=addr">addr</a>)
<a name="L813" href="source/net/ipv4/ping.c#L813">813</a>                 ipc.<a href="ident?i=addr">addr</a> = fl4.<a href="ident?i=daddr">daddr</a>;
<a name="L814" href="source/net/ipv4/ping.c#L814">814</a> 
<a name="L815" href="source/net/ipv4/ping.c#L815">815</a>         <a href="ident?i=lock_sock">lock_sock</a>(sk);
<a name="L816" href="source/net/ipv4/ping.c#L816">816</a> 
<a name="L817" href="source/net/ipv4/ping.c#L817">817</a>         pfh.icmph.<a href="ident?i=type">type</a> = user_icmph.<a href="ident?i=type">type</a>; <b><i>/* already checked */</i></b>
<a name="L818" href="source/net/ipv4/ping.c#L818">818</a>         pfh.icmph.<a href="ident?i=code">code</a> = user_icmph.<a href="ident?i=code">code</a>; <b><i>/* ditto */</i></b>
<a name="L819" href="source/net/ipv4/ping.c#L819">819</a>         pfh.icmph.<a href="ident?i=checksum">checksum</a> = 0;
<a name="L820" href="source/net/ipv4/ping.c#L820">820</a>         pfh.icmph.un.<a href="ident?i=echo">echo</a>.<a href="ident?i=id">id</a> = inet-&gt;inet_sport;
<a name="L821" href="source/net/ipv4/ping.c#L821">821</a>         pfh.icmph.un.<a href="ident?i=echo">echo</a>.<a href="ident?i=sequence">sequence</a> = user_icmph.un.<a href="ident?i=echo">echo</a>.<a href="ident?i=sequence">sequence</a>;
<a name="L822" href="source/net/ipv4/ping.c#L822">822</a>         pfh.<a href="ident?i=msg">msg</a> = <a href="ident?i=msg">msg</a>;
<a name="L823" href="source/net/ipv4/ping.c#L823">823</a>         pfh.wcheck = 0;
<a name="L824" href="source/net/ipv4/ping.c#L824">824</a>         pfh.<a href="ident?i=family">family</a> = <a href="ident?i=AF_INET">AF_INET</a>;
<a name="L825" href="source/net/ipv4/ping.c#L825">825</a> 
<a name="L826" href="source/net/ipv4/ping.c#L826">826</a>         <a href="ident?i=err">err</a> = <a href="ident?i=ip_append_data">ip_append_data</a>(sk, &amp;fl4, <a href="ident?i=ping_getfrag">ping_getfrag</a>, &amp;pfh, <a href="ident?i=len">len</a>,
<a name="L827" href="source/net/ipv4/ping.c#L827">827</a>                         0, &amp;ipc, &amp;<a href="ident?i=rt">rt</a>, <a href="ident?i=msg">msg</a>-&gt;msg_flags);
<a name="L828" href="source/net/ipv4/ping.c#L828">828</a>         if (<a href="ident?i=err">err</a>)
<a name="L829" href="source/net/ipv4/ping.c#L829">829</a>                 <a href="ident?i=ip_flush_pending_frames">ip_flush_pending_frames</a>(sk);
<a name="L830" href="source/net/ipv4/ping.c#L830">830</a>         else
<a name="L831" href="source/net/ipv4/ping.c#L831">831</a>                 <a href="ident?i=err">err</a> = <a href="ident?i=ping_v4_push_pending_frames">ping_v4_push_pending_frames</a>(sk, &amp;pfh, &amp;fl4);
<a name="L832" href="source/net/ipv4/ping.c#L832">832</a>         <a href="ident?i=release_sock">release_sock</a>(sk);
<a name="L833" href="source/net/ipv4/ping.c#L833">833</a> 
<a name="L834" href="source/net/ipv4/ping.c#L834">834</a> <a href="ident?i=out">out</a>:
<a name="L835" href="source/net/ipv4/ping.c#L835">835</a>         <a href="ident?i=ip_rt_put">ip_rt_put</a>(<a href="ident?i=rt">rt</a>);
<a name="L836" href="source/net/ipv4/ping.c#L836">836</a>         if (<a href="ident?i=free">free</a>)
<a name="L837" href="source/net/ipv4/ping.c#L837">837</a>                 <a href="ident?i=kfree">kfree</a>(ipc.opt);
<a name="L838" href="source/net/ipv4/ping.c#L838">838</a>         if (!<a href="ident?i=err">err</a>) {
<a name="L839" href="source/net/ipv4/ping.c#L839">839</a>                 <a href="ident?i=icmp_out_count">icmp_out_count</a>(<a href="ident?i=sock_net">sock_net</a>(sk), user_icmph.<a href="ident?i=type">type</a>);
<a name="L840" href="source/net/ipv4/ping.c#L840">840</a>                 return <a href="ident?i=len">len</a>;
<a name="L841" href="source/net/ipv4/ping.c#L841">841</a>         }
<a name="L842" href="source/net/ipv4/ping.c#L842">842</a>         return <a href="ident?i=err">err</a>;
<a name="L843" href="source/net/ipv4/ping.c#L843">843</a> 
<a name="L844" href="source/net/ipv4/ping.c#L844">844</a> do_confirm:
<a name="L845" href="source/net/ipv4/ping.c#L845">845</a>         <a href="ident?i=dst_confirm">dst_confirm</a>(&amp;<a href="ident?i=rt">rt</a>-&gt;<a href="ident?i=dst">dst</a>);
<a name="L846" href="source/net/ipv4/ping.c#L846">846</a>         if (!(<a href="ident?i=msg">msg</a>-&gt;msg_flags &amp; <a href="ident?i=MSG_PROBE">MSG_PROBE</a>) || <a href="ident?i=len">len</a>)
<a name="L847" href="source/net/ipv4/ping.c#L847">847</a>                 goto back_from_confirm;
<a name="L848" href="source/net/ipv4/ping.c#L848">848</a>         <a href="ident?i=err">err</a> = 0;
<a name="L849" href="source/net/ipv4/ping.c#L849">849</a>         goto <a href="ident?i=out">out</a>;
<a name="L850" href="source/net/ipv4/ping.c#L850">850</a> }
<a name="L851" href="source/net/ipv4/ping.c#L851">851</a> 
<a name="L852" href="source/net/ipv4/ping.c#L852">852</a> int <a href="ident?i=ping_recvmsg">ping_recvmsg</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=msghdr">msghdr</a> *<a href="ident?i=msg">msg</a>, <a href="ident?i=size_t">size_t</a> <a href="ident?i=len">len</a>, int noblock,
<a name="L853" href="source/net/ipv4/ping.c#L853">853</a>                  int <a href="ident?i=flags">flags</a>, int *addr_len)
<a name="L854" href="source/net/ipv4/ping.c#L854">854</a> {
<a name="L855" href="source/net/ipv4/ping.c#L855">855</a>         struct <a href="ident?i=inet_sock">inet_sock</a> *isk = <a href="ident?i=inet_sk">inet_sk</a>(sk);
<a name="L856" href="source/net/ipv4/ping.c#L856">856</a>         int <a href="ident?i=family">family</a> = sk-&gt;<a href="ident?i=sk_family">sk_family</a>;
<a name="L857" href="source/net/ipv4/ping.c#L857">857</a>         struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>;
<a name="L858" href="source/net/ipv4/ping.c#L858">858</a>         int copied, <a href="ident?i=err">err</a>;
<a name="L859" href="source/net/ipv4/ping.c#L859">859</a> 
<a name="L860" href="source/net/ipv4/ping.c#L860">860</a>         <a href="ident?i=pr_debug">pr_debug</a>(<i>"ping_recvmsg(sk=%p,sk-&gt;num=%u)\n"</i>, isk, isk-&gt;<a href="ident?i=inet_num">inet_num</a>);
<a name="L861" href="source/net/ipv4/ping.c#L861">861</a> 
<a name="L862" href="source/net/ipv4/ping.c#L862">862</a>         <a href="ident?i=err">err</a> = -<a href="ident?i=EOPNOTSUPP">EOPNOTSUPP</a>;
<a name="L863" href="source/net/ipv4/ping.c#L863">863</a>         if (<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=MSG_OOB">MSG_OOB</a>)
<a name="L864" href="source/net/ipv4/ping.c#L864">864</a>                 goto <a href="ident?i=out">out</a>;
<a name="L865" href="source/net/ipv4/ping.c#L865">865</a> 
<a name="L866" href="source/net/ipv4/ping.c#L866">866</a>         if (<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=MSG_ERRQUEUE">MSG_ERRQUEUE</a>)
<a name="L867" href="source/net/ipv4/ping.c#L867">867</a>                 return <a href="ident?i=inet_recv_error">inet_recv_error</a>(sk, <a href="ident?i=msg">msg</a>, <a href="ident?i=len">len</a>, addr_len);
<a name="L868" href="source/net/ipv4/ping.c#L868">868</a> 
<a name="L869" href="source/net/ipv4/ping.c#L869">869</a>         <a href="ident?i=skb">skb</a> = <a href="ident?i=skb_recv_datagram">skb_recv_datagram</a>(sk, <a href="ident?i=flags">flags</a>, noblock, &amp;<a href="ident?i=err">err</a>);
<a name="L870" href="source/net/ipv4/ping.c#L870">870</a>         if (!<a href="ident?i=skb">skb</a>)
<a name="L871" href="source/net/ipv4/ping.c#L871">871</a>                 goto <a href="ident?i=out">out</a>;
<a name="L872" href="source/net/ipv4/ping.c#L872">872</a> 
<a name="L873" href="source/net/ipv4/ping.c#L873">873</a>         copied = <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a>;
<a name="L874" href="source/net/ipv4/ping.c#L874">874</a>         if (copied &gt; <a href="ident?i=len">len</a>) {
<a name="L875" href="source/net/ipv4/ping.c#L875">875</a>                 <a href="ident?i=msg">msg</a>-&gt;msg_flags |= <a href="ident?i=MSG_TRUNC">MSG_TRUNC</a>;
<a name="L876" href="source/net/ipv4/ping.c#L876">876</a>                 copied = <a href="ident?i=len">len</a>;
<a name="L877" href="source/net/ipv4/ping.c#L877">877</a>         }
<a name="L878" href="source/net/ipv4/ping.c#L878">878</a> 
<a name="L879" href="source/net/ipv4/ping.c#L879">879</a>         <b><i>/* Don't bother checking the checksum */</i></b>
<a name="L880" href="source/net/ipv4/ping.c#L880">880</a>         <a href="ident?i=err">err</a> = <a href="ident?i=skb_copy_datagram_msg">skb_copy_datagram_msg</a>(<a href="ident?i=skb">skb</a>, 0, <a href="ident?i=msg">msg</a>, copied);
<a name="L881" href="source/net/ipv4/ping.c#L881">881</a>         if (<a href="ident?i=err">err</a>)
<a name="L882" href="source/net/ipv4/ping.c#L882">882</a>                 goto <a href="ident?i=done">done</a>;
<a name="L883" href="source/net/ipv4/ping.c#L883">883</a> 
<a name="L884" href="source/net/ipv4/ping.c#L884">884</a>         <a href="ident?i=sock_recv_timestamp">sock_recv_timestamp</a>(<a href="ident?i=msg">msg</a>, sk, <a href="ident?i=skb">skb</a>);
<a name="L885" href="source/net/ipv4/ping.c#L885">885</a> 
<a name="L886" href="source/net/ipv4/ping.c#L886">886</a>         <b><i>/* Copy the address and add cmsg data. */</i></b>
<a name="L887" href="source/net/ipv4/ping.c#L887">887</a>         if (<a href="ident?i=family">family</a> == <a href="ident?i=AF_INET">AF_INET</a>) {
<a name="L888" href="source/net/ipv4/ping.c#L888">888</a>                 <a href="ident?i=DECLARE_SOCKADDR">DECLARE_SOCKADDR</a>(struct <a href="ident?i=sockaddr_in">sockaddr_in</a> *, <a href="ident?i=sin">sin</a>, <a href="ident?i=msg">msg</a>-&gt;msg_name);
<a name="L889" href="source/net/ipv4/ping.c#L889">889</a> 
<a name="L890" href="source/net/ipv4/ping.c#L890">890</a>                 if (<a href="ident?i=sin">sin</a>) {
<a name="L891" href="source/net/ipv4/ping.c#L891">891</a>                         <a href="ident?i=sin">sin</a>-&gt;sin_family = <a href="ident?i=AF_INET">AF_INET</a>;
<a name="L892" href="source/net/ipv4/ping.c#L892">892</a>                         <a href="ident?i=sin">sin</a>-&gt;sin_port = 0 <b><i>/* skb-&gt;h.uh-&gt;source */</i></b>;
<a name="L893" href="source/net/ipv4/ping.c#L893">893</a>                         <a href="ident?i=sin">sin</a>-&gt;sin_addr.s_addr = <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=saddr">saddr</a>;
<a name="L894" href="source/net/ipv4/ping.c#L894">894</a>                         <a href="ident?i=memset">memset</a>(<a href="ident?i=sin">sin</a>-&gt;<a href="ident?i=sin_zero">sin_zero</a>, 0, sizeof(<a href="ident?i=sin">sin</a>-&gt;<a href="ident?i=sin_zero">sin_zero</a>));
<a name="L895" href="source/net/ipv4/ping.c#L895">895</a>                         *addr_len = sizeof(*<a href="ident?i=sin">sin</a>);
<a name="L896" href="source/net/ipv4/ping.c#L896">896</a>                 }
<a name="L897" href="source/net/ipv4/ping.c#L897">897</a> 
<a name="L898" href="source/net/ipv4/ping.c#L898">898</a>                 if (isk-&gt;cmsg_flags)
<a name="L899" href="source/net/ipv4/ping.c#L899">899</a>                         <a href="ident?i=ip_cmsg_recv">ip_cmsg_recv</a>(<a href="ident?i=msg">msg</a>, <a href="ident?i=skb">skb</a>);
<a name="L900" href="source/net/ipv4/ping.c#L900">900</a> 
<a name="L901" href="source/net/ipv4/ping.c#L901">901</a> #if <a href="ident?i=IS_ENABLED">IS_ENABLED</a>(CONFIG_IPV6)
<a name="L902" href="source/net/ipv4/ping.c#L902">902</a>         } else if (<a href="ident?i=family">family</a> == <a href="ident?i=AF_INET6">AF_INET6</a>) {
<a name="L903" href="source/net/ipv4/ping.c#L903">903</a>                 struct <a href="ident?i=ipv6_pinfo">ipv6_pinfo</a> *np = <a href="ident?i=inet6_sk">inet6_sk</a>(sk);
<a name="L904" href="source/net/ipv4/ping.c#L904">904</a>                 struct <a href="ident?i=ipv6hdr">ipv6hdr</a> *ip6 = <a href="ident?i=ipv6_hdr">ipv6_hdr</a>(<a href="ident?i=skb">skb</a>);
<a name="L905" href="source/net/ipv4/ping.c#L905">905</a>                 <a href="ident?i=DECLARE_SOCKADDR">DECLARE_SOCKADDR</a>(struct <a href="ident?i=sockaddr_in6">sockaddr_in6</a> *, sin6, <a href="ident?i=msg">msg</a>-&gt;msg_name);
<a name="L906" href="source/net/ipv4/ping.c#L906">906</a> 
<a name="L907" href="source/net/ipv4/ping.c#L907">907</a>                 if (sin6) {
<a name="L908" href="source/net/ipv4/ping.c#L908">908</a>                         sin6-&gt;sin6_family = <a href="ident?i=AF_INET6">AF_INET6</a>;
<a name="L909" href="source/net/ipv4/ping.c#L909">909</a>                         sin6-&gt;sin6_port = 0;
<a name="L910" href="source/net/ipv4/ping.c#L910">910</a>                         sin6-&gt;sin6_addr = ip6-&gt;<a href="ident?i=saddr">saddr</a>;
<a name="L911" href="source/net/ipv4/ping.c#L911">911</a>                         sin6-&gt;sin6_flowinfo = 0;
<a name="L912" href="source/net/ipv4/ping.c#L912">912</a>                         if (np-&gt;sndflow)
<a name="L913" href="source/net/ipv4/ping.c#L913">913</a>                                 sin6-&gt;sin6_flowinfo = <a href="ident?i=ip6_flowinfo">ip6_flowinfo</a>(ip6);
<a name="L914" href="source/net/ipv4/ping.c#L914">914</a>                         sin6-&gt;sin6_scope_id =
<a name="L915" href="source/net/ipv4/ping.c#L915">915</a>                                 <a href="ident?i=ipv6_iface_scope_id">ipv6_iface_scope_id</a>(&amp;sin6-&gt;sin6_addr,
<a name="L916" href="source/net/ipv4/ping.c#L916">916</a>                                                     <a href="ident?i=inet6_iif">inet6_iif</a>(<a href="ident?i=skb">skb</a>));
<a name="L917" href="source/net/ipv4/ping.c#L917">917</a>                         *addr_len = sizeof(*sin6);
<a name="L918" href="source/net/ipv4/ping.c#L918">918</a>                 }
<a name="L919" href="source/net/ipv4/ping.c#L919">919</a> 
<a name="L920" href="source/net/ipv4/ping.c#L920">920</a>                 if (<a href="ident?i=inet6_sk">inet6_sk</a>(sk)-&gt;rxopt.<a href="ident?i=all">all</a>)
<a name="L921" href="source/net/ipv4/ping.c#L921">921</a>                         <a href="ident?i=pingv6_ops">pingv6_ops</a>.<a href="ident?i=ip6_datagram_recv_common_ctl">ip6_datagram_recv_common_ctl</a>(sk, <a href="ident?i=msg">msg</a>, <a href="ident?i=skb">skb</a>);
<a name="L922" href="source/net/ipv4/ping.c#L922">922</a>                 if (<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=protocol">protocol</a> == <a href="ident?i=htons">htons</a>(<a href="ident?i=ETH_P_IPV6">ETH_P_IPV6</a>) &amp;&amp;
<a name="L923" href="source/net/ipv4/ping.c#L923">923</a>                     <a href="ident?i=inet6_sk">inet6_sk</a>(sk)-&gt;rxopt.<a href="ident?i=all">all</a>)
<a name="L924" href="source/net/ipv4/ping.c#L924">924</a>                         <a href="ident?i=pingv6_ops">pingv6_ops</a>.<a href="ident?i=ip6_datagram_recv_specific_ctl">ip6_datagram_recv_specific_ctl</a>(sk, <a href="ident?i=msg">msg</a>, <a href="ident?i=skb">skb</a>);
<a name="L925" href="source/net/ipv4/ping.c#L925">925</a>                 else if (<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=protocol">protocol</a> == <a href="ident?i=htons">htons</a>(<a href="ident?i=ETH_P_IP">ETH_P_IP</a>) &amp;&amp; isk-&gt;cmsg_flags)
<a name="L926" href="source/net/ipv4/ping.c#L926">926</a>                         <a href="ident?i=ip_cmsg_recv">ip_cmsg_recv</a>(<a href="ident?i=msg">msg</a>, <a href="ident?i=skb">skb</a>);
<a name="L927" href="source/net/ipv4/ping.c#L927">927</a> #endif
<a name="L928" href="source/net/ipv4/ping.c#L928">928</a>         } else {
<a name="L929" href="source/net/ipv4/ping.c#L929">929</a>                 <a href="ident?i=BUG">BUG</a>();
<a name="L930" href="source/net/ipv4/ping.c#L930">930</a>         }
<a name="L931" href="source/net/ipv4/ping.c#L931">931</a> 
<a name="L932" href="source/net/ipv4/ping.c#L932">932</a>         <a href="ident?i=err">err</a> = copied;
<a name="L933" href="source/net/ipv4/ping.c#L933">933</a> 
<a name="L934" href="source/net/ipv4/ping.c#L934">934</a> <a href="ident?i=done">done</a>:
<a name="L935" href="source/net/ipv4/ping.c#L935">935</a>         <a href="ident?i=skb_free_datagram">skb_free_datagram</a>(sk, <a href="ident?i=skb">skb</a>);
<a name="L936" href="source/net/ipv4/ping.c#L936">936</a> <a href="ident?i=out">out</a>:
<a name="L937" href="source/net/ipv4/ping.c#L937">937</a>         <a href="ident?i=pr_debug">pr_debug</a>(<i>"ping_recvmsg -&gt; %d\n"</i>, <a href="ident?i=err">err</a>);
<a name="L938" href="source/net/ipv4/ping.c#L938">938</a>         return <a href="ident?i=err">err</a>;
<a name="L939" href="source/net/ipv4/ping.c#L939">939</a> }
<a name="L940" href="source/net/ipv4/ping.c#L940">940</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=ping_recvmsg">ping_recvmsg</a>);
<a name="L941" href="source/net/ipv4/ping.c#L941">941</a> 
<a name="L942" href="source/net/ipv4/ping.c#L942">942</a> int <a href="ident?i=ping_queue_rcv_skb">ping_queue_rcv_skb</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L943" href="source/net/ipv4/ping.c#L943">943</a> {
<a name="L944" href="source/net/ipv4/ping.c#L944">944</a>         <a href="ident?i=pr_debug">pr_debug</a>(<i>"ping_queue_rcv_skb(sk=%p,sk-&gt;num=%d,skb=%p)\n"</i>,
<a name="L945" href="source/net/ipv4/ping.c#L945">945</a>                  <a href="ident?i=inet_sk">inet_sk</a>(sk), <a href="ident?i=inet_sk">inet_sk</a>(sk)-&gt;<a href="ident?i=inet_num">inet_num</a>, <a href="ident?i=skb">skb</a>);
<a name="L946" href="source/net/ipv4/ping.c#L946">946</a>         if (<a href="ident?i=sock_queue_rcv_skb">sock_queue_rcv_skb</a>(sk, <a href="ident?i=skb">skb</a>) &lt; 0) {
<a name="L947" href="source/net/ipv4/ping.c#L947">947</a>                 <a href="ident?i=kfree_skb">kfree_skb</a>(<a href="ident?i=skb">skb</a>);
<a name="L948" href="source/net/ipv4/ping.c#L948">948</a>                 <a href="ident?i=pr_debug">pr_debug</a>(<i>"ping_queue_rcv_skb -&gt; failed\n"</i>);
<a name="L949" href="source/net/ipv4/ping.c#L949">949</a>                 return -1;
<a name="L950" href="source/net/ipv4/ping.c#L950">950</a>         }
<a name="L951" href="source/net/ipv4/ping.c#L951">951</a>         return 0;
<a name="L952" href="source/net/ipv4/ping.c#L952">952</a> }
<a name="L953" href="source/net/ipv4/ping.c#L953">953</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=ping_queue_rcv_skb">ping_queue_rcv_skb</a>);
<a name="L954" href="source/net/ipv4/ping.c#L954">954</a> 
<a name="L955" href="source/net/ipv4/ping.c#L955">955</a> 
<a name="L956" href="source/net/ipv4/ping.c#L956">956</a> <b><i>/*</i></b>
<a name="L957" href="source/net/ipv4/ping.c#L957">957</a> <b><i> *      All we need to do is get the socket.</i></b>
<a name="L958" href="source/net/ipv4/ping.c#L958">958</a> <b><i> */</i></b>
<a name="L959" href="source/net/ipv4/ping.c#L959">959</a> 
<a name="L960" href="source/net/ipv4/ping.c#L960">960</a> <a href="ident?i=bool">bool</a> <a href="ident?i=ping_rcv">ping_rcv</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L961" href="source/net/ipv4/ping.c#L961">961</a> {
<a name="L962" href="source/net/ipv4/ping.c#L962">962</a>         struct <a href="ident?i=sock">sock</a> *sk;
<a name="L963" href="source/net/ipv4/ping.c#L963">963</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=dev">dev</a>);
<a name="L964" href="source/net/ipv4/ping.c#L964">964</a>         struct <a href="ident?i=icmphdr">icmphdr</a> *icmph = <a href="ident?i=icmp_hdr">icmp_hdr</a>(<a href="ident?i=skb">skb</a>);
<a name="L965" href="source/net/ipv4/ping.c#L965">965</a> 
<a name="L966" href="source/net/ipv4/ping.c#L966">966</a>         <b><i>/* We assume the packet has already been checked by icmp_rcv */</i></b>
<a name="L967" href="source/net/ipv4/ping.c#L967">967</a> 
<a name="L968" href="source/net/ipv4/ping.c#L968">968</a>         <a href="ident?i=pr_debug">pr_debug</a>(<i>"ping_rcv(skb=%p,id=%04x,seq=%04x)\n"</i>,
<a name="L969" href="source/net/ipv4/ping.c#L969">969</a>                  <a href="ident?i=skb">skb</a>, <a href="ident?i=ntohs">ntohs</a>(icmph-&gt;un.<a href="ident?i=echo">echo</a>.<a href="ident?i=id">id</a>), <a href="ident?i=ntohs">ntohs</a>(icmph-&gt;un.<a href="ident?i=echo">echo</a>.<a href="ident?i=sequence">sequence</a>));
<a name="L970" href="source/net/ipv4/ping.c#L970">970</a> 
<a name="L971" href="source/net/ipv4/ping.c#L971">971</a>         <b><i>/* Push ICMP header back */</i></b>
<a name="L972" href="source/net/ipv4/ping.c#L972">972</a>         <a href="ident?i=skb_push">skb_push</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=data">data</a> - (<a href="ident?i=u8">u8</a> *)icmph);
<a name="L973" href="source/net/ipv4/ping.c#L973">973</a> 
<a name="L974" href="source/net/ipv4/ping.c#L974">974</a>         sk = <a href="ident?i=ping_lookup">ping_lookup</a>(<a href="ident?i=net">net</a>, <a href="ident?i=skb">skb</a>, <a href="ident?i=ntohs">ntohs</a>(icmph-&gt;un.<a href="ident?i=echo">echo</a>.<a href="ident?i=id">id</a>));
<a name="L975" href="source/net/ipv4/ping.c#L975">975</a>         if (sk) {
<a name="L976" href="source/net/ipv4/ping.c#L976">976</a>                 struct <a href="ident?i=sk_buff">sk_buff</a> *skb2 = <a href="ident?i=skb_clone">skb_clone</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=GFP_ATOMIC">GFP_ATOMIC</a>);
<a name="L977" href="source/net/ipv4/ping.c#L977">977</a> 
<a name="L978" href="source/net/ipv4/ping.c#L978">978</a>                 <a href="ident?i=pr_debug">pr_debug</a>(<i>"rcv on socket %p\n"</i>, sk);
<a name="L979" href="source/net/ipv4/ping.c#L979">979</a>                 if (skb2)
<a name="L980" href="source/net/ipv4/ping.c#L980">980</a>                         <a href="ident?i=ping_queue_rcv_skb">ping_queue_rcv_skb</a>(sk, skb2);
<a name="L981" href="source/net/ipv4/ping.c#L981">981</a>                 <a href="ident?i=sock_put">sock_put</a>(sk);
<a name="L982" href="source/net/ipv4/ping.c#L982">982</a>                 return <a href="ident?i=true">true</a>;
<a name="L983" href="source/net/ipv4/ping.c#L983">983</a>         }
<a name="L984" href="source/net/ipv4/ping.c#L984">984</a>         <a href="ident?i=pr_debug">pr_debug</a>(<i>"no socket, dropping\n"</i>);
<a name="L985" href="source/net/ipv4/ping.c#L985">985</a> 
<a name="L986" href="source/net/ipv4/ping.c#L986">986</a>         return <a href="ident?i=false">false</a>;
<a name="L987" href="source/net/ipv4/ping.c#L987">987</a> }
<a name="L988" href="source/net/ipv4/ping.c#L988">988</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=ping_rcv">ping_rcv</a>);
<a name="L989" href="source/net/ipv4/ping.c#L989">989</a> 
<a name="L990" href="source/net/ipv4/ping.c#L990">990</a> struct <a href="ident?i=proto">proto</a> <a href="ident?i=ping_prot">ping_prot</a> = {
<a name="L991" href="source/net/ipv4/ping.c#L991">991</a>         .<a href="ident?i=name">name</a> =         <i>"PING"</i>,
<a name="L992" href="source/net/ipv4/ping.c#L992">992</a>         .owner =        <a href="ident?i=THIS_MODULE">THIS_MODULE</a>,
<a name="L993" href="source/net/ipv4/ping.c#L993">993</a>         .<a href="ident?i=init">init</a> =         <a href="ident?i=ping_init_sock">ping_init_sock</a>,
<a name="L994" href="source/net/ipv4/ping.c#L994">994</a>         .<a href="ident?i=close">close</a> =        <a href="ident?i=ping_close">ping_close</a>,
<a name="L995" href="source/net/ipv4/ping.c#L995">995</a>         .<a href="ident?i=connect">connect</a> =      <a href="ident?i=ip4_datagram_connect">ip4_datagram_connect</a>,
<a name="L996" href="source/net/ipv4/ping.c#L996">996</a>         .<a href="ident?i=disconnect">disconnect</a> =   <a href="ident?i=udp_disconnect">udp_disconnect</a>,
<a name="L997" href="source/net/ipv4/ping.c#L997">997</a>         .<a href="ident?i=setsockopt">setsockopt</a> =   <a href="ident?i=ip_setsockopt">ip_setsockopt</a>,
<a name="L998" href="source/net/ipv4/ping.c#L998">998</a>         .getsockopt =   <a href="ident?i=ip_getsockopt">ip_getsockopt</a>,
<a name="L999" href="source/net/ipv4/ping.c#L999">999</a>         .<a href="ident?i=sendmsg">sendmsg</a> =      <a href="ident?i=ping_v4_sendmsg">ping_v4_sendmsg</a>,
<a name="L1000" href="source/net/ipv4/ping.c#L1000">1000</a>         .recvmsg =      <a href="ident?i=ping_recvmsg">ping_recvmsg</a>,
<a name="L1001" href="source/net/ipv4/ping.c#L1001">1001</a>         .bind =         <a href="ident?i=ping_bind">ping_bind</a>,
<a name="L1002" href="source/net/ipv4/ping.c#L1002">1002</a>         .backlog_rcv =  <a href="ident?i=ping_queue_rcv_skb">ping_queue_rcv_skb</a>,
<a name="L1003" href="source/net/ipv4/ping.c#L1003">1003</a>         .release_cb =   <a href="ident?i=ip4_datagram_release_cb">ip4_datagram_release_cb</a>,
<a name="L1004" href="source/net/ipv4/ping.c#L1004">1004</a>         .<a href="ident?i=hash">hash</a> =         <a href="ident?i=ping_hash">ping_hash</a>,
<a name="L1005" href="source/net/ipv4/ping.c#L1005">1005</a>         .unhash =       <a href="ident?i=ping_unhash">ping_unhash</a>,
<a name="L1006" href="source/net/ipv4/ping.c#L1006">1006</a>         .<a href="ident?i=get_port">get_port</a> =     <a href="ident?i=ping_get_port">ping_get_port</a>,
<a name="L1007" href="source/net/ipv4/ping.c#L1007">1007</a>         .obj_size =     sizeof(struct <a href="ident?i=inet_sock">inet_sock</a>),
<a name="L1008" href="source/net/ipv4/ping.c#L1008">1008</a> };
<a name="L1009" href="source/net/ipv4/ping.c#L1009">1009</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=ping_prot">ping_prot</a>);
<a name="L1010" href="source/net/ipv4/ping.c#L1010">1010</a> 
<a name="L1011" href="source/net/ipv4/ping.c#L1011">1011</a> #ifdef CONFIG_PROC_FS
<a name="L1012" href="source/net/ipv4/ping.c#L1012">1012</a> 
<a name="L1013" href="source/net/ipv4/ping.c#L1013">1013</a> static struct <a href="ident?i=sock">sock</a> *<a href="ident?i=ping_get_first">ping_get_first</a>(struct <a href="ident?i=seq_file">seq_file</a> *<a href="ident?i=seq">seq</a>, int <a href="ident?i=start">start</a>)
<a name="L1014" href="source/net/ipv4/ping.c#L1014">1014</a> {
<a name="L1015" href="source/net/ipv4/ping.c#L1015">1015</a>         struct <a href="ident?i=sock">sock</a> *sk;
<a name="L1016" href="source/net/ipv4/ping.c#L1016">1016</a>         struct <a href="ident?i=ping_iter_state">ping_iter_state</a> *<a href="ident?i=state">state</a> = <a href="ident?i=seq">seq</a>-&gt;<a href="ident?i=private">private</a>;
<a name="L1017" href="source/net/ipv4/ping.c#L1017">1017</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=seq_file_net">seq_file_net</a>(<a href="ident?i=seq">seq</a>);
<a name="L1018" href="source/net/ipv4/ping.c#L1018">1018</a> 
<a name="L1019" href="source/net/ipv4/ping.c#L1019">1019</a>         for (<a href="ident?i=state">state</a>-&gt;<a href="ident?i=bucket">bucket</a> = <a href="ident?i=start">start</a>; <a href="ident?i=state">state</a>-&gt;<a href="ident?i=bucket">bucket</a> &lt; <a href="ident?i=PING_HTABLE_SIZE">PING_HTABLE_SIZE</a>;
<a name="L1020" href="source/net/ipv4/ping.c#L1020">1020</a>              ++<a href="ident?i=state">state</a>-&gt;<a href="ident?i=bucket">bucket</a>) {
<a name="L1021" href="source/net/ipv4/ping.c#L1021">1021</a>                 struct <a href="ident?i=hlist_nulls_node">hlist_nulls_node</a> *<a href="ident?i=node">node</a>;
<a name="L1022" href="source/net/ipv4/ping.c#L1022">1022</a>                 struct <a href="ident?i=hlist_nulls_head">hlist_nulls_head</a> *hslot;
<a name="L1023" href="source/net/ipv4/ping.c#L1023">1023</a> 
<a name="L1024" href="source/net/ipv4/ping.c#L1024">1024</a>                 hslot = &amp;<a href="ident?i=ping_table">ping_table</a>.<a href="ident?i=hash">hash</a>[<a href="ident?i=state">state</a>-&gt;<a href="ident?i=bucket">bucket</a>];
<a name="L1025" href="source/net/ipv4/ping.c#L1025">1025</a> 
<a name="L1026" href="source/net/ipv4/ping.c#L1026">1026</a>                 if (<a href="ident?i=hlist_nulls_empty">hlist_nulls_empty</a>(hslot))
<a name="L1027" href="source/net/ipv4/ping.c#L1027">1027</a>                         continue;
<a name="L1028" href="source/net/ipv4/ping.c#L1028">1028</a> 
<a name="L1029" href="source/net/ipv4/ping.c#L1029">1029</a>                 <a href="ident?i=sk_nulls_for_each">sk_nulls_for_each</a>(sk, <a href="ident?i=node">node</a>, hslot) {
<a name="L1030" href="source/net/ipv4/ping.c#L1030">1030</a>                         if (<a href="ident?i=net_eq">net_eq</a>(<a href="ident?i=sock_net">sock_net</a>(sk), <a href="ident?i=net">net</a>) &amp;&amp;
<a name="L1031" href="source/net/ipv4/ping.c#L1031">1031</a>                             sk-&gt;<a href="ident?i=sk_family">sk_family</a> == <a href="ident?i=state">state</a>-&gt;<a href="ident?i=family">family</a>)
<a name="L1032" href="source/net/ipv4/ping.c#L1032">1032</a>                                 goto <a href="ident?i=found">found</a>;
<a name="L1033" href="source/net/ipv4/ping.c#L1033">1033</a>                 }
<a name="L1034" href="source/net/ipv4/ping.c#L1034">1034</a>         }
<a name="L1035" href="source/net/ipv4/ping.c#L1035">1035</a>         sk = <a href="ident?i=NULL">NULL</a>;
<a name="L1036" href="source/net/ipv4/ping.c#L1036">1036</a> <a href="ident?i=found">found</a>:
<a name="L1037" href="source/net/ipv4/ping.c#L1037">1037</a>         return sk;
<a name="L1038" href="source/net/ipv4/ping.c#L1038">1038</a> }
<a name="L1039" href="source/net/ipv4/ping.c#L1039">1039</a> 
<a name="L1040" href="source/net/ipv4/ping.c#L1040">1040</a> static struct <a href="ident?i=sock">sock</a> *<a href="ident?i=ping_get_next">ping_get_next</a>(struct <a href="ident?i=seq_file">seq_file</a> *<a href="ident?i=seq">seq</a>, struct <a href="ident?i=sock">sock</a> *sk)
<a name="L1041" href="source/net/ipv4/ping.c#L1041">1041</a> {
<a name="L1042" href="source/net/ipv4/ping.c#L1042">1042</a>         struct <a href="ident?i=ping_iter_state">ping_iter_state</a> *<a href="ident?i=state">state</a> = <a href="ident?i=seq">seq</a>-&gt;<a href="ident?i=private">private</a>;
<a name="L1043" href="source/net/ipv4/ping.c#L1043">1043</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=seq_file_net">seq_file_net</a>(<a href="ident?i=seq">seq</a>);
<a name="L1044" href="source/net/ipv4/ping.c#L1044">1044</a> 
<a name="L1045" href="source/net/ipv4/ping.c#L1045">1045</a>         do {
<a name="L1046" href="source/net/ipv4/ping.c#L1046">1046</a>                 sk = <a href="ident?i=sk_nulls_next">sk_nulls_next</a>(sk);
<a name="L1047" href="source/net/ipv4/ping.c#L1047">1047</a>         } while (sk &amp;&amp; (!<a href="ident?i=net_eq">net_eq</a>(<a href="ident?i=sock_net">sock_net</a>(sk), <a href="ident?i=net">net</a>)));
<a name="L1048" href="source/net/ipv4/ping.c#L1048">1048</a> 
<a name="L1049" href="source/net/ipv4/ping.c#L1049">1049</a>         if (!sk)
<a name="L1050" href="source/net/ipv4/ping.c#L1050">1050</a>                 return <a href="ident?i=ping_get_first">ping_get_first</a>(<a href="ident?i=seq">seq</a>, <a href="ident?i=state">state</a>-&gt;<a href="ident?i=bucket">bucket</a> + 1);
<a name="L1051" href="source/net/ipv4/ping.c#L1051">1051</a>         return sk;
<a name="L1052" href="source/net/ipv4/ping.c#L1052">1052</a> }
<a name="L1053" href="source/net/ipv4/ping.c#L1053">1053</a> 
<a name="L1054" href="source/net/ipv4/ping.c#L1054">1054</a> static struct <a href="ident?i=sock">sock</a> *<a href="ident?i=ping_get_idx">ping_get_idx</a>(struct <a href="ident?i=seq_file">seq_file</a> *<a href="ident?i=seq">seq</a>, <a href="ident?i=loff_t">loff_t</a> <a href="ident?i=pos">pos</a>)
<a name="L1055" href="source/net/ipv4/ping.c#L1055">1055</a> {
<a name="L1056" href="source/net/ipv4/ping.c#L1056">1056</a>         struct <a href="ident?i=sock">sock</a> *sk = <a href="ident?i=ping_get_first">ping_get_first</a>(<a href="ident?i=seq">seq</a>, 0);
<a name="L1057" href="source/net/ipv4/ping.c#L1057">1057</a> 
<a name="L1058" href="source/net/ipv4/ping.c#L1058">1058</a>         if (sk)
<a name="L1059" href="source/net/ipv4/ping.c#L1059">1059</a>                 while (<a href="ident?i=pos">pos</a> &amp;&amp; (sk = <a href="ident?i=ping_get_next">ping_get_next</a>(<a href="ident?i=seq">seq</a>, sk)) != <a href="ident?i=NULL">NULL</a>)
<a name="L1060" href="source/net/ipv4/ping.c#L1060">1060</a>                         --<a href="ident?i=pos">pos</a>;
<a name="L1061" href="source/net/ipv4/ping.c#L1061">1061</a>         return <a href="ident?i=pos">pos</a> ? <a href="ident?i=NULL">NULL</a> : sk;
<a name="L1062" href="source/net/ipv4/ping.c#L1062">1062</a> }
<a name="L1063" href="source/net/ipv4/ping.c#L1063">1063</a> 
<a name="L1064" href="source/net/ipv4/ping.c#L1064">1064</a> void *<a href="ident?i=ping_seq_start">ping_seq_start</a>(struct <a href="ident?i=seq_file">seq_file</a> *<a href="ident?i=seq">seq</a>, <a href="ident?i=loff_t">loff_t</a> *<a href="ident?i=pos">pos</a>, <a href="ident?i=sa_family_t">sa_family_t</a> <a href="ident?i=family">family</a>)
<a name="L1065" href="source/net/ipv4/ping.c#L1065">1065</a> {
<a name="L1066" href="source/net/ipv4/ping.c#L1066">1066</a>         struct <a href="ident?i=ping_iter_state">ping_iter_state</a> *<a href="ident?i=state">state</a> = <a href="ident?i=seq">seq</a>-&gt;<a href="ident?i=private">private</a>;
<a name="L1067" href="source/net/ipv4/ping.c#L1067">1067</a>         <a href="ident?i=state">state</a>-&gt;<a href="ident?i=bucket">bucket</a> = 0;
<a name="L1068" href="source/net/ipv4/ping.c#L1068">1068</a>         <a href="ident?i=state">state</a>-&gt;<a href="ident?i=family">family</a> = <a href="ident?i=family">family</a>;
<a name="L1069" href="source/net/ipv4/ping.c#L1069">1069</a> 
<a name="L1070" href="source/net/ipv4/ping.c#L1070">1070</a>         <a href="ident?i=read_lock_bh">read_lock_bh</a>(&amp;<a href="ident?i=ping_table">ping_table</a>.<a href="ident?i=lock">lock</a>);
<a name="L1071" href="source/net/ipv4/ping.c#L1071">1071</a> 
<a name="L1072" href="source/net/ipv4/ping.c#L1072">1072</a>         return *<a href="ident?i=pos">pos</a> ? <a href="ident?i=ping_get_idx">ping_get_idx</a>(<a href="ident?i=seq">seq</a>, *<a href="ident?i=pos">pos</a>-1) : <a href="ident?i=SEQ_START_TOKEN">SEQ_START_TOKEN</a>;
<a name="L1073" href="source/net/ipv4/ping.c#L1073">1073</a> }
<a name="L1074" href="source/net/ipv4/ping.c#L1074">1074</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=ping_seq_start">ping_seq_start</a>);
<a name="L1075" href="source/net/ipv4/ping.c#L1075">1075</a> 
<a name="L1076" href="source/net/ipv4/ping.c#L1076">1076</a> static void *<a href="ident?i=ping_v4_seq_start">ping_v4_seq_start</a>(struct <a href="ident?i=seq_file">seq_file</a> *<a href="ident?i=seq">seq</a>, <a href="ident?i=loff_t">loff_t</a> *<a href="ident?i=pos">pos</a>)
<a name="L1077" href="source/net/ipv4/ping.c#L1077">1077</a> {
<a name="L1078" href="source/net/ipv4/ping.c#L1078">1078</a>         return <a href="ident?i=ping_seq_start">ping_seq_start</a>(<a href="ident?i=seq">seq</a>, <a href="ident?i=pos">pos</a>, <a href="ident?i=AF_INET">AF_INET</a>);
<a name="L1079" href="source/net/ipv4/ping.c#L1079">1079</a> }
<a name="L1080" href="source/net/ipv4/ping.c#L1080">1080</a> 
<a name="L1081" href="source/net/ipv4/ping.c#L1081">1081</a> void *<a href="ident?i=ping_seq_next">ping_seq_next</a>(struct <a href="ident?i=seq_file">seq_file</a> *<a href="ident?i=seq">seq</a>, void *<a href="ident?i=v">v</a>, <a href="ident?i=loff_t">loff_t</a> *<a href="ident?i=pos">pos</a>)
<a name="L1082" href="source/net/ipv4/ping.c#L1082">1082</a> {
<a name="L1083" href="source/net/ipv4/ping.c#L1083">1083</a>         struct <a href="ident?i=sock">sock</a> *sk;
<a name="L1084" href="source/net/ipv4/ping.c#L1084">1084</a> 
<a name="L1085" href="source/net/ipv4/ping.c#L1085">1085</a>         if (<a href="ident?i=v">v</a> == <a href="ident?i=SEQ_START_TOKEN">SEQ_START_TOKEN</a>)
<a name="L1086" href="source/net/ipv4/ping.c#L1086">1086</a>                 sk = <a href="ident?i=ping_get_idx">ping_get_idx</a>(<a href="ident?i=seq">seq</a>, 0);
<a name="L1087" href="source/net/ipv4/ping.c#L1087">1087</a>         else
<a name="L1088" href="source/net/ipv4/ping.c#L1088">1088</a>                 sk = <a href="ident?i=ping_get_next">ping_get_next</a>(<a href="ident?i=seq">seq</a>, <a href="ident?i=v">v</a>);
<a name="L1089" href="source/net/ipv4/ping.c#L1089">1089</a> 
<a name="L1090" href="source/net/ipv4/ping.c#L1090">1090</a>         ++*<a href="ident?i=pos">pos</a>;
<a name="L1091" href="source/net/ipv4/ping.c#L1091">1091</a>         return sk;
<a name="L1092" href="source/net/ipv4/ping.c#L1092">1092</a> }
<a name="L1093" href="source/net/ipv4/ping.c#L1093">1093</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=ping_seq_next">ping_seq_next</a>);
<a name="L1094" href="source/net/ipv4/ping.c#L1094">1094</a> 
<a name="L1095" href="source/net/ipv4/ping.c#L1095">1095</a> void <a href="ident?i=ping_seq_stop">ping_seq_stop</a>(struct <a href="ident?i=seq_file">seq_file</a> *<a href="ident?i=seq">seq</a>, void *<a href="ident?i=v">v</a>)
<a name="L1096" href="source/net/ipv4/ping.c#L1096">1096</a> {
<a name="L1097" href="source/net/ipv4/ping.c#L1097">1097</a>         <a href="ident?i=read_unlock_bh">read_unlock_bh</a>(&amp;<a href="ident?i=ping_table">ping_table</a>.<a href="ident?i=lock">lock</a>);
<a name="L1098" href="source/net/ipv4/ping.c#L1098">1098</a> }
<a name="L1099" href="source/net/ipv4/ping.c#L1099">1099</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=ping_seq_stop">ping_seq_stop</a>);
<a name="L1100" href="source/net/ipv4/ping.c#L1100">1100</a> 
<a name="L1101" href="source/net/ipv4/ping.c#L1101">1101</a> static void <a href="ident?i=ping_v4_format_sock">ping_v4_format_sock</a>(struct <a href="ident?i=sock">sock</a> *<a href="ident?i=sp">sp</a>, struct <a href="ident?i=seq_file">seq_file</a> *<a href="ident?i=f">f</a>,
<a name="L1102" href="source/net/ipv4/ping.c#L1102">1102</a>                 int <a href="ident?i=bucket">bucket</a>)
<a name="L1103" href="source/net/ipv4/ping.c#L1103">1103</a> {
<a name="L1104" href="source/net/ipv4/ping.c#L1104">1104</a>         struct <a href="ident?i=inet_sock">inet_sock</a> *inet = <a href="ident?i=inet_sk">inet_sk</a>(<a href="ident?i=sp">sp</a>);
<a name="L1105" href="source/net/ipv4/ping.c#L1105">1105</a>         <a href="ident?i=__be32">__be32</a> <a href="ident?i=dest">dest</a> = inet-&gt;<a href="ident?i=inet_daddr">inet_daddr</a>;
<a name="L1106" href="source/net/ipv4/ping.c#L1106">1106</a>         <a href="ident?i=__be32">__be32</a> <a href="ident?i=src">src</a> = inet-&gt;<a href="ident?i=inet_rcv_saddr">inet_rcv_saddr</a>;
<a name="L1107" href="source/net/ipv4/ping.c#L1107">1107</a>         <a href="ident?i=__u16">__u16</a> destp = <a href="ident?i=ntohs">ntohs</a>(inet-&gt;<a href="ident?i=inet_dport">inet_dport</a>);
<a name="L1108" href="source/net/ipv4/ping.c#L1108">1108</a>         <a href="ident?i=__u16">__u16</a> srcp = <a href="ident?i=ntohs">ntohs</a>(inet-&gt;inet_sport);
<a name="L1109" href="source/net/ipv4/ping.c#L1109">1109</a> 
<a name="L1110" href="source/net/ipv4/ping.c#L1110">1110</a>         <a href="ident?i=seq_printf">seq_printf</a>(<a href="ident?i=f">f</a>, <i>"%5d: %08X:%04X %08X:%04X"</i>
<a name="L1111" href="source/net/ipv4/ping.c#L1111">1111</a>                 <i>" %02X %08X:%08X %02X:%08lX %08X %5u %8d %lu %d %pK %d"</i>,
<a name="L1112" href="source/net/ipv4/ping.c#L1112">1112</a>                 <a href="ident?i=bucket">bucket</a>, <a href="ident?i=src">src</a>, srcp, <a href="ident?i=dest">dest</a>, destp, <a href="ident?i=sp">sp</a>-&gt;<a href="ident?i=sk_state">sk_state</a>,
<a name="L1113" href="source/net/ipv4/ping.c#L1113">1113</a>                 <a href="ident?i=sk_wmem_alloc_get">sk_wmem_alloc_get</a>(<a href="ident?i=sp">sp</a>),
<a name="L1114" href="source/net/ipv4/ping.c#L1114">1114</a>                 <a href="ident?i=sk_rmem_alloc_get">sk_rmem_alloc_get</a>(<a href="ident?i=sp">sp</a>),
<a name="L1115" href="source/net/ipv4/ping.c#L1115">1115</a>                 0, 0L, 0,
<a name="L1116" href="source/net/ipv4/ping.c#L1116">1116</a>                 <a href="ident?i=from_kuid_munged">from_kuid_munged</a>(<a href="ident?i=seq_user_ns">seq_user_ns</a>(<a href="ident?i=f">f</a>), <a href="ident?i=sock_i_uid">sock_i_uid</a>(<a href="ident?i=sp">sp</a>)),
<a name="L1117" href="source/net/ipv4/ping.c#L1117">1117</a>                 0, <a href="ident?i=sock_i_ino">sock_i_ino</a>(<a href="ident?i=sp">sp</a>),
<a name="L1118" href="source/net/ipv4/ping.c#L1118">1118</a>                 <a href="ident?i=atomic_read">atomic_read</a>(&amp;<a href="ident?i=sp">sp</a>-&gt;<a href="ident?i=sk_refcnt">sk_refcnt</a>), <a href="ident?i=sp">sp</a>,
<a name="L1119" href="source/net/ipv4/ping.c#L1119">1119</a>                 <a href="ident?i=atomic_read">atomic_read</a>(&amp;<a href="ident?i=sp">sp</a>-&gt;sk_drops));
<a name="L1120" href="source/net/ipv4/ping.c#L1120">1120</a> }
<a name="L1121" href="source/net/ipv4/ping.c#L1121">1121</a> 
<a name="L1122" href="source/net/ipv4/ping.c#L1122">1122</a> static int <a href="ident?i=ping_v4_seq_show">ping_v4_seq_show</a>(struct <a href="ident?i=seq_file">seq_file</a> *<a href="ident?i=seq">seq</a>, void *<a href="ident?i=v">v</a>)
<a name="L1123" href="source/net/ipv4/ping.c#L1123">1123</a> {
<a name="L1124" href="source/net/ipv4/ping.c#L1124">1124</a>         <a href="ident?i=seq_setwidth">seq_setwidth</a>(<a href="ident?i=seq">seq</a>, 127);
<a name="L1125" href="source/net/ipv4/ping.c#L1125">1125</a>         if (<a href="ident?i=v">v</a> == <a href="ident?i=SEQ_START_TOKEN">SEQ_START_TOKEN</a>)
<a name="L1126" href="source/net/ipv4/ping.c#L1126">1126</a>                 <a href="ident?i=seq_puts">seq_puts</a>(<a href="ident?i=seq">seq</a>, <i>"  sl  local_address rem_address   st tx_queue "</i>
<a name="L1127" href="source/net/ipv4/ping.c#L1127">1127</a>                            <i>"rx_queue tr tm-&gt;when retrnsmt   uid  timeout "</i>
<a name="L1128" href="source/net/ipv4/ping.c#L1128">1128</a>                            <i>"inode ref pointer drops"</i>);
<a name="L1129" href="source/net/ipv4/ping.c#L1129">1129</a>         else {
<a name="L1130" href="source/net/ipv4/ping.c#L1130">1130</a>                 struct <a href="ident?i=ping_iter_state">ping_iter_state</a> *<a href="ident?i=state">state</a> = <a href="ident?i=seq">seq</a>-&gt;<a href="ident?i=private">private</a>;
<a name="L1131" href="source/net/ipv4/ping.c#L1131">1131</a> 
<a name="L1132" href="source/net/ipv4/ping.c#L1132">1132</a>                 <a href="ident?i=ping_v4_format_sock">ping_v4_format_sock</a>(<a href="ident?i=v">v</a>, <a href="ident?i=seq">seq</a>, <a href="ident?i=state">state</a>-&gt;<a href="ident?i=bucket">bucket</a>);
<a name="L1133" href="source/net/ipv4/ping.c#L1133">1133</a>         }
<a name="L1134" href="source/net/ipv4/ping.c#L1134">1134</a>         <a href="ident?i=seq_pad">seq_pad</a>(<a href="ident?i=seq">seq</a>, <i>'\n'</i>);
<a name="L1135" href="source/net/ipv4/ping.c#L1135">1135</a>         return 0;
<a name="L1136" href="source/net/ipv4/ping.c#L1136">1136</a> }
<a name="L1137" href="source/net/ipv4/ping.c#L1137">1137</a> 
<a name="L1138" href="source/net/ipv4/ping.c#L1138">1138</a> static const struct <a href="ident?i=seq_operations">seq_operations</a> <a href="ident?i=ping_v4_seq_ops">ping_v4_seq_ops</a> = {
<a name="L1139" href="source/net/ipv4/ping.c#L1139">1139</a>         .<a href="ident?i=show">show</a>           = <a href="ident?i=ping_v4_seq_show">ping_v4_seq_show</a>,
<a name="L1140" href="source/net/ipv4/ping.c#L1140">1140</a>         .<a href="ident?i=start">start</a>          = <a href="ident?i=ping_v4_seq_start">ping_v4_seq_start</a>,
<a name="L1141" href="source/net/ipv4/ping.c#L1141">1141</a>         .<a href="ident?i=next">next</a>           = <a href="ident?i=ping_seq_next">ping_seq_next</a>,
<a name="L1142" href="source/net/ipv4/ping.c#L1142">1142</a>         .<a href="ident?i=stop">stop</a>           = <a href="ident?i=ping_seq_stop">ping_seq_stop</a>,
<a name="L1143" href="source/net/ipv4/ping.c#L1143">1143</a> };
<a name="L1144" href="source/net/ipv4/ping.c#L1144">1144</a> 
<a name="L1145" href="source/net/ipv4/ping.c#L1145">1145</a> static int <a href="ident?i=ping_seq_open">ping_seq_open</a>(struct <a href="ident?i=inode">inode</a> *<a href="ident?i=inode">inode</a>, struct <a href="ident?i=file">file</a> *<a href="ident?i=file">file</a>)
<a name="L1146" href="source/net/ipv4/ping.c#L1146">1146</a> {
<a name="L1147" href="source/net/ipv4/ping.c#L1147">1147</a>         struct <a href="ident?i=ping_seq_afinfo">ping_seq_afinfo</a> *afinfo = <a href="ident?i=PDE_DATA">PDE_DATA</a>(<a href="ident?i=inode">inode</a>);
<a name="L1148" href="source/net/ipv4/ping.c#L1148">1148</a>         return <a href="ident?i=seq_open_net">seq_open_net</a>(<a href="ident?i=inode">inode</a>, <a href="ident?i=file">file</a>, &amp;afinfo-&gt;seq_ops,
<a name="L1149" href="source/net/ipv4/ping.c#L1149">1149</a>                            sizeof(struct <a href="ident?i=ping_iter_state">ping_iter_state</a>));
<a name="L1150" href="source/net/ipv4/ping.c#L1150">1150</a> }
<a name="L1151" href="source/net/ipv4/ping.c#L1151">1151</a> 
<a name="L1152" href="source/net/ipv4/ping.c#L1152">1152</a> const struct <a href="ident?i=file_operations">file_operations</a> <a href="ident?i=ping_seq_fops">ping_seq_fops</a> = {
<a name="L1153" href="source/net/ipv4/ping.c#L1153">1153</a>         .<a href="ident?i=open">open</a>           = <a href="ident?i=ping_seq_open">ping_seq_open</a>,
<a name="L1154" href="source/net/ipv4/ping.c#L1154">1154</a>         .<a href="ident?i=read">read</a>           = <a href="ident?i=seq_read">seq_read</a>,
<a name="L1155" href="source/net/ipv4/ping.c#L1155">1155</a>         .llseek         = <a href="ident?i=seq_lseek">seq_lseek</a>,
<a name="L1156" href="source/net/ipv4/ping.c#L1156">1156</a>         .<a href="ident?i=release">release</a>        = <a href="ident?i=seq_release_net">seq_release_net</a>,
<a name="L1157" href="source/net/ipv4/ping.c#L1157">1157</a> };
<a name="L1158" href="source/net/ipv4/ping.c#L1158">1158</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=ping_seq_fops">ping_seq_fops</a>);
<a name="L1159" href="source/net/ipv4/ping.c#L1159">1159</a> 
<a name="L1160" href="source/net/ipv4/ping.c#L1160">1160</a> static struct <a href="ident?i=ping_seq_afinfo">ping_seq_afinfo</a> <a href="ident?i=ping_v4_seq_afinfo">ping_v4_seq_afinfo</a> = {
<a name="L1161" href="source/net/ipv4/ping.c#L1161">1161</a>         .<a href="ident?i=name">name</a>           = <i>"icmp"</i>,
<a name="L1162" href="source/net/ipv4/ping.c#L1162">1162</a>         .<a href="ident?i=family">family</a>         = <a href="ident?i=AF_INET">AF_INET</a>,
<a name="L1163" href="source/net/ipv4/ping.c#L1163">1163</a>         .seq_fops       = &amp;<a href="ident?i=ping_seq_fops">ping_seq_fops</a>,
<a name="L1164" href="source/net/ipv4/ping.c#L1164">1164</a>         .seq_ops        = {
<a name="L1165" href="source/net/ipv4/ping.c#L1165">1165</a>                 .<a href="ident?i=start">start</a>          = <a href="ident?i=ping_v4_seq_start">ping_v4_seq_start</a>,
<a name="L1166" href="source/net/ipv4/ping.c#L1166">1166</a>                 .<a href="ident?i=show">show</a>           = <a href="ident?i=ping_v4_seq_show">ping_v4_seq_show</a>,
<a name="L1167" href="source/net/ipv4/ping.c#L1167">1167</a>                 .<a href="ident?i=next">next</a>           = <a href="ident?i=ping_seq_next">ping_seq_next</a>,
<a name="L1168" href="source/net/ipv4/ping.c#L1168">1168</a>                 .<a href="ident?i=stop">stop</a>           = <a href="ident?i=ping_seq_stop">ping_seq_stop</a>,
<a name="L1169" href="source/net/ipv4/ping.c#L1169">1169</a>         },
<a name="L1170" href="source/net/ipv4/ping.c#L1170">1170</a> };
<a name="L1171" href="source/net/ipv4/ping.c#L1171">1171</a> 
<a name="L1172" href="source/net/ipv4/ping.c#L1172">1172</a> int <a href="ident?i=ping_proc_register">ping_proc_register</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>, struct <a href="ident?i=ping_seq_afinfo">ping_seq_afinfo</a> *afinfo)
<a name="L1173" href="source/net/ipv4/ping.c#L1173">1173</a> {
<a name="L1174" href="source/net/ipv4/ping.c#L1174">1174</a>         struct <a href="ident?i=proc_dir_entry">proc_dir_entry</a> *<a href="ident?i=p">p</a>;
<a name="L1175" href="source/net/ipv4/ping.c#L1175">1175</a>         <a href="ident?i=p">p</a> = <a href="ident?i=proc_create_data">proc_create_data</a>(afinfo-&gt;<a href="ident?i=name">name</a>, <a href="ident?i=S_IRUGO">S_IRUGO</a>, <a href="ident?i=net">net</a>-&gt;proc_net,
<a name="L1176" href="source/net/ipv4/ping.c#L1176">1176</a>                              afinfo-&gt;seq_fops, afinfo);
<a name="L1177" href="source/net/ipv4/ping.c#L1177">1177</a>         if (!<a href="ident?i=p">p</a>)
<a name="L1178" href="source/net/ipv4/ping.c#L1178">1178</a>                 return -<a href="ident?i=ENOMEM">ENOMEM</a>;
<a name="L1179" href="source/net/ipv4/ping.c#L1179">1179</a>         return 0;
<a name="L1180" href="source/net/ipv4/ping.c#L1180">1180</a> }
<a name="L1181" href="source/net/ipv4/ping.c#L1181">1181</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=ping_proc_register">ping_proc_register</a>);
<a name="L1182" href="source/net/ipv4/ping.c#L1182">1182</a> 
<a name="L1183" href="source/net/ipv4/ping.c#L1183">1183</a> void <a href="ident?i=ping_proc_unregister">ping_proc_unregister</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>, struct <a href="ident?i=ping_seq_afinfo">ping_seq_afinfo</a> *afinfo)
<a name="L1184" href="source/net/ipv4/ping.c#L1184">1184</a> {
<a name="L1185" href="source/net/ipv4/ping.c#L1185">1185</a>         <a href="ident?i=remove_proc_entry">remove_proc_entry</a>(afinfo-&gt;<a href="ident?i=name">name</a>, <a href="ident?i=net">net</a>-&gt;proc_net);
<a name="L1186" href="source/net/ipv4/ping.c#L1186">1186</a> }
<a name="L1187" href="source/net/ipv4/ping.c#L1187">1187</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=ping_proc_unregister">ping_proc_unregister</a>);
<a name="L1188" href="source/net/ipv4/ping.c#L1188">1188</a> 
<a name="L1189" href="source/net/ipv4/ping.c#L1189">1189</a> static int <a href="ident?i=__net_init">__net_init</a> <a href="ident?i=ping_v4_proc_init_net">ping_v4_proc_init_net</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>)
<a name="L1190" href="source/net/ipv4/ping.c#L1190">1190</a> {
<a name="L1191" href="source/net/ipv4/ping.c#L1191">1191</a>         return <a href="ident?i=ping_proc_register">ping_proc_register</a>(<a href="ident?i=net">net</a>, &amp;<a href="ident?i=ping_v4_seq_afinfo">ping_v4_seq_afinfo</a>);
<a name="L1192" href="source/net/ipv4/ping.c#L1192">1192</a> }
<a name="L1193" href="source/net/ipv4/ping.c#L1193">1193</a> 
<a name="L1194" href="source/net/ipv4/ping.c#L1194">1194</a> static void <a href="ident?i=__net_exit">__net_exit</a> <a href="ident?i=ping_v4_proc_exit_net">ping_v4_proc_exit_net</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>)
<a name="L1195" href="source/net/ipv4/ping.c#L1195">1195</a> {
<a name="L1196" href="source/net/ipv4/ping.c#L1196">1196</a>         <a href="ident?i=ping_proc_unregister">ping_proc_unregister</a>(<a href="ident?i=net">net</a>, &amp;<a href="ident?i=ping_v4_seq_afinfo">ping_v4_seq_afinfo</a>);
<a name="L1197" href="source/net/ipv4/ping.c#L1197">1197</a> }
<a name="L1198" href="source/net/ipv4/ping.c#L1198">1198</a> 
<a name="L1199" href="source/net/ipv4/ping.c#L1199">1199</a> static struct <a href="ident?i=pernet_operations">pernet_operations</a> <a href="ident?i=ping_v4_net_ops">ping_v4_net_ops</a> = {
<a name="L1200" href="source/net/ipv4/ping.c#L1200">1200</a>         .<a href="ident?i=init">init</a> = <a href="ident?i=ping_v4_proc_init_net">ping_v4_proc_init_net</a>,
<a name="L1201" href="source/net/ipv4/ping.c#L1201">1201</a>         .<a href="ident?i=exit">exit</a> = <a href="ident?i=ping_v4_proc_exit_net">ping_v4_proc_exit_net</a>,
<a name="L1202" href="source/net/ipv4/ping.c#L1202">1202</a> };
<a name="L1203" href="source/net/ipv4/ping.c#L1203">1203</a> 
<a name="L1204" href="source/net/ipv4/ping.c#L1204">1204</a> int <a href="ident?i=__init">__init</a> <a href="ident?i=ping_proc_init">ping_proc_init</a>(void)
<a name="L1205" href="source/net/ipv4/ping.c#L1205">1205</a> {
<a name="L1206" href="source/net/ipv4/ping.c#L1206">1206</a>         return <a href="ident?i=register_pernet_subsys">register_pernet_subsys</a>(&amp;<a href="ident?i=ping_v4_net_ops">ping_v4_net_ops</a>);
<a name="L1207" href="source/net/ipv4/ping.c#L1207">1207</a> }
<a name="L1208" href="source/net/ipv4/ping.c#L1208">1208</a> 
<a name="L1209" href="source/net/ipv4/ping.c#L1209">1209</a> void <a href="ident?i=ping_proc_exit">ping_proc_exit</a>(void)
<a name="L1210" href="source/net/ipv4/ping.c#L1210">1210</a> {
<a name="L1211" href="source/net/ipv4/ping.c#L1211">1211</a>         <a href="ident?i=unregister_pernet_subsys">unregister_pernet_subsys</a>(&amp;<a href="ident?i=ping_v4_net_ops">ping_v4_net_ops</a>);
<a name="L1212" href="source/net/ipv4/ping.c#L1212">1212</a> }
<a name="L1213" href="source/net/ipv4/ping.c#L1213">1213</a> 
<a name="L1214" href="source/net/ipv4/ping.c#L1214">1214</a> #endif
<a name="L1215" href="source/net/ipv4/ping.c#L1215">1215</a> 
<a name="L1216" href="source/net/ipv4/ping.c#L1216">1216</a> void <a href="ident?i=__init">__init</a> <a href="ident?i=ping_init">ping_init</a>(void)
<a name="L1217" href="source/net/ipv4/ping.c#L1217">1217</a> {
<a name="L1218" href="source/net/ipv4/ping.c#L1218">1218</a>         int <a href="ident?i=i">i</a>;
<a name="L1219" href="source/net/ipv4/ping.c#L1219">1219</a> 
<a name="L1220" href="source/net/ipv4/ping.c#L1220">1220</a>         for (<a href="ident?i=i">i</a> = 0; <a href="ident?i=i">i</a> &lt; <a href="ident?i=PING_HTABLE_SIZE">PING_HTABLE_SIZE</a>; <a href="ident?i=i">i</a>++)
<a name="L1221" href="source/net/ipv4/ping.c#L1221">1221</a>                 <a href="ident?i=INIT_HLIST_NULLS_HEAD">INIT_HLIST_NULLS_HEAD</a>(&amp;<a href="ident?i=ping_table">ping_table</a>.<a href="ident?i=hash">hash</a>[<a href="ident?i=i">i</a>], <a href="ident?i=i">i</a>);
<a name="L1222" href="source/net/ipv4/ping.c#L1222">1222</a>         <a href="ident?i=rwlock_init">rwlock_init</a>(&amp;<a href="ident?i=ping_table">ping_table</a>.<a href="ident?i=lock">lock</a>);
<a name="L1223" href="source/net/ipv4/ping.c#L1223">1223</a> }
<a name="L1224" href="source/net/ipv4/ping.c#L1224">1224</a> </pre></div><p>
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
