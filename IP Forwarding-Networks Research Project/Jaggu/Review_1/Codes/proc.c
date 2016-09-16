<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title>Linux/net/ipv4/proc.c - Linux Cross Reference - Free Electrons</title>
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
		 &nbsp;&bull;&nbsp;<b><i>source navigation</i></b> &nbsp;&bull;&nbsp;<a href="diff/net/ipv4/proc.c">diff markup</a> &nbsp;&bull;&nbsp;<a href="ident">identifier search</a> &nbsp;&bull;&nbsp;<a href="search">freetext search</a> &nbsp;&bull;&nbsp;
		</p>
	</div>
</div>

<div id="topbar">
  
  <p>Version: &nbsp;<a href="source/net/ipv4/proc.c?v=2.0.40">2.0.40</a>&nbsp;<a href="source/net/ipv4/proc.c?v=2.2.26">2.2.26</a>&nbsp;<a href="source/net/ipv4/proc.c?v=2.4.37">2.4.37</a>&nbsp;<a href="source/net/ipv4/proc.c?v=3.5">3.5</a>&nbsp;<a href="source/net/ipv4/proc.c?v=3.6">3.6</a>&nbsp;<a href="source/net/ipv4/proc.c?v=3.7">3.7</a>&nbsp;<a href="source/net/ipv4/proc.c?v=3.8">3.8</a>&nbsp;<a href="source/net/ipv4/proc.c?v=3.9">3.9</a>&nbsp;<a href="source/net/ipv4/proc.c?v=3.10">3.10</a>&nbsp;<a href="source/net/ipv4/proc.c?v=3.11">3.11</a>&nbsp;<a href="source/net/ipv4/proc.c?v=3.12">3.12</a>&nbsp;<a href="source/net/ipv4/proc.c?v=3.13">3.13</a>&nbsp;<a href="source/net/ipv4/proc.c?v=3.14">3.14</a>&nbsp;<a href="source/net/ipv4/proc.c?v=3.15">3.15</a>&nbsp;<a href="source/net/ipv4/proc.c?v=3.16">3.16</a>&nbsp;<a href="source/net/ipv4/proc.c?v=3.17">3.17</a>&nbsp;<a href="source/net/ipv4/proc.c?v=3.18">3.18</a>&nbsp;<a href="source/net/ipv4/proc.c?v=3.19">3.19</a>&nbsp;<a href="source/net/ipv4/proc.c?v=4.0">4.0</a>&nbsp;<b><i>4.1</i></b></p>
  
</div>

<h1><a href="source/">Linux</a>/<a href="source/net/">net</a>/<a href="source/net/ipv4/">ipv4</a>/<a href="source/net/ipv4/proc.c">proc.c</a></h1>
<div id="lxrcode"><pre>  <a name="L1" href="source/net/ipv4/proc.c#L1">1</a> <b><i>/*</i></b>
  <a name="L2" href="source/net/ipv4/proc.c#L2">2</a> <b><i> * INET         An implementation of the TCP/IP protocol suite for the LINUX</i></b>
  <a name="L3" href="source/net/ipv4/proc.c#L3">3</a> <b><i> *              operating system.  INET is implemented using the  BSD Socket</i></b>
  <a name="L4" href="source/net/ipv4/proc.c#L4">4</a> <b><i> *              interface as the means of communication with the user level.</i></b>
  <a name="L5" href="source/net/ipv4/proc.c#L5">5</a> <b><i> *</i></b>
  <a name="L6" href="source/net/ipv4/proc.c#L6">6</a> <b><i> *              This file implements the various access functions for the</i></b>
  <a name="L7" href="source/net/ipv4/proc.c#L7">7</a> <b><i> *              PROC file system.  It is mainly used for debugging and</i></b>
  <a name="L8" href="source/net/ipv4/proc.c#L8">8</a> <b><i> *              statistics.</i></b>
  <a name="L9" href="source/net/ipv4/proc.c#L9">9</a> <b><i> *</i></b>
 <a name="L10" href="source/net/ipv4/proc.c#L10">10</a> <b><i> * Authors:     Fred N. van Kempen, &lt;waltje@uWalt.NL.Mugnet.ORG&gt;</i></b>
 <a name="L11" href="source/net/ipv4/proc.c#L11">11</a> <b><i> *              Gerald J. Heim, &lt;heim@peanuts.informatik.uni-tuebingen.de&gt;</i></b>
 <a name="L12" href="source/net/ipv4/proc.c#L12">12</a> <b><i> *              Fred Baumgarten, &lt;dc6iq@insu1.etec.uni-karlsruhe.de&gt;</i></b>
 <a name="L13" href="source/net/ipv4/proc.c#L13">13</a> <b><i> *              Erik Schoenfelder, &lt;schoenfr@ibr.cs.tu-bs.de&gt;</i></b>
 <a name="L14" href="source/net/ipv4/proc.c#L14">14</a> <b><i> *</i></b>
 <a name="L15" href="source/net/ipv4/proc.c#L15">15</a> <b><i> * Fixes:</i></b>
 <a name="L16" href="source/net/ipv4/proc.c#L16">16</a> <b><i> *              Alan Cox        :       UDP sockets show the rxqueue/txqueue</i></b>
 <a name="L17" href="source/net/ipv4/proc.c#L17">17</a> <b><i> *                                      using hint flag for the netinfo.</i></b>
 <a name="L18" href="source/net/ipv4/proc.c#L18">18</a> <b><i> *      Pauline Middelink       :       identd support</i></b>
 <a name="L19" href="source/net/ipv4/proc.c#L19">19</a> <b><i> *              Alan Cox        :       Make /proc safer.</i></b>
 <a name="L20" href="source/net/ipv4/proc.c#L20">20</a> <b><i> *      Erik Schoenfelder       :       /proc/net/snmp</i></b>
 <a name="L21" href="source/net/ipv4/proc.c#L21">21</a> <b><i> *              Alan Cox        :       Handle dead sockets properly.</i></b>
 <a name="L22" href="source/net/ipv4/proc.c#L22">22</a> <b><i> *      Gerhard Koerting        :       Show both timers</i></b>
 <a name="L23" href="source/net/ipv4/proc.c#L23">23</a> <b><i> *              Alan Cox        :       Allow inode to be NULL (kernel socket)</i></b>
 <a name="L24" href="source/net/ipv4/proc.c#L24">24</a> <b><i> *      Andi Kleen              :       Add support for open_requests and</i></b>
 <a name="L25" href="source/net/ipv4/proc.c#L25">25</a> <b><i> *                                      split functions for more readibility.</i></b>
 <a name="L26" href="source/net/ipv4/proc.c#L26">26</a> <b><i> *      Andi Kleen              :       Add support for /proc/net/netstat</i></b>
 <a name="L27" href="source/net/ipv4/proc.c#L27">27</a> <b><i> *      Arnaldo C. Melo         :       Convert to seq_file</i></b>
 <a name="L28" href="source/net/ipv4/proc.c#L28">28</a> <b><i> *</i></b>
 <a name="L29" href="source/net/ipv4/proc.c#L29">29</a> <b><i> *              This program is free software; you can redistribute it and/or</i></b>
 <a name="L30" href="source/net/ipv4/proc.c#L30">30</a> <b><i> *              modify it under the terms of the GNU General Public License</i></b>
 <a name="L31" href="source/net/ipv4/proc.c#L31">31</a> <b><i> *              as published by the Free Software Foundation; either version</i></b>
 <a name="L32" href="source/net/ipv4/proc.c#L32">32</a> <b><i> *              2 of the License, or (at your option) any later version.</i></b>
 <a name="L33" href="source/net/ipv4/proc.c#L33">33</a> <b><i> */</i></b>
 <a name="L34" href="source/net/ipv4/proc.c#L34">34</a> #include &lt;linux/types.h&gt;
 <a name="L35" href="source/net/ipv4/proc.c#L35">35</a> #include &lt;net/net_namespace.h&gt;
 <a name="L36" href="source/net/ipv4/proc.c#L36">36</a> #include &lt;net/icmp.h&gt;
 <a name="L37" href="source/net/ipv4/proc.c#L37">37</a> #include &lt;net/protocol.h&gt;
 <a name="L38" href="source/net/ipv4/proc.c#L38">38</a> #include &lt;net/tcp.h&gt;
 <a name="L39" href="source/net/ipv4/proc.c#L39">39</a> #include &lt;net/udp.h&gt;
 <a name="L40" href="source/net/ipv4/proc.c#L40">40</a> #include &lt;net/udplite.h&gt;
 <a name="L41" href="source/net/ipv4/proc.c#L41">41</a> #include &lt;linux/bottom_half.h&gt;
 <a name="L42" href="source/net/ipv4/proc.c#L42">42</a> #include &lt;linux/inetdevice.h&gt;
 <a name="L43" href="source/net/ipv4/proc.c#L43">43</a> #include &lt;linux/proc_fs.h&gt;
 <a name="L44" href="source/net/ipv4/proc.c#L44">44</a> #include &lt;linux/seq_file.h&gt;
 <a name="L45" href="source/net/ipv4/proc.c#L45">45</a> #include &lt;linux/export.h&gt;
 <a name="L46" href="source/net/ipv4/proc.c#L46">46</a> #include &lt;net/sock.h&gt;
 <a name="L47" href="source/net/ipv4/proc.c#L47">47</a> #include &lt;net/raw.h&gt;
 <a name="L48" href="source/net/ipv4/proc.c#L48">48</a> 
 <a name="L49" href="source/net/ipv4/proc.c#L49">49</a> <b><i>/*</i></b>
 <a name="L50" href="source/net/ipv4/proc.c#L50">50</a> <b><i> *      Report socket allocation statistics [mea@utu.fi]</i></b>
 <a name="L51" href="source/net/ipv4/proc.c#L51">51</a> <b><i> */</i></b>
 <a name="L52" href="source/net/ipv4/proc.c#L52">52</a> static int <a href="ident?i=sockstat_seq_show">sockstat_seq_show</a>(struct <a href="ident?i=seq_file">seq_file</a> *<a href="ident?i=seq">seq</a>, void *<a href="ident?i=v">v</a>)
 <a name="L53" href="source/net/ipv4/proc.c#L53">53</a> {
 <a name="L54" href="source/net/ipv4/proc.c#L54">54</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=seq">seq</a>-&gt;<a href="ident?i=private">private</a>;
 <a name="L55" href="source/net/ipv4/proc.c#L55">55</a>         unsigned int frag_mem;
 <a name="L56" href="source/net/ipv4/proc.c#L56">56</a>         int orphans, <a href="ident?i=sockets">sockets</a>;
 <a name="L57" href="source/net/ipv4/proc.c#L57">57</a> 
 <a name="L58" href="source/net/ipv4/proc.c#L58">58</a>         <a href="ident?i=local_bh_disable">local_bh_disable</a>();
 <a name="L59" href="source/net/ipv4/proc.c#L59">59</a>         orphans = <a href="ident?i=percpu_counter_sum_positive">percpu_counter_sum_positive</a>(&amp;<a href="ident?i=tcp_orphan_count">tcp_orphan_count</a>);
 <a name="L60" href="source/net/ipv4/proc.c#L60">60</a>         <a href="ident?i=sockets">sockets</a> = <a href="ident?i=proto_sockets_allocated_sum_positive">proto_sockets_allocated_sum_positive</a>(&amp;<a href="ident?i=tcp_prot">tcp_prot</a>);
 <a name="L61" href="source/net/ipv4/proc.c#L61">61</a>         <a href="ident?i=local_bh_enable">local_bh_enable</a>();
 <a name="L62" href="source/net/ipv4/proc.c#L62">62</a> 
 <a name="L63" href="source/net/ipv4/proc.c#L63">63</a>         <a href="ident?i=socket_seq_show">socket_seq_show</a>(<a href="ident?i=seq">seq</a>);
 <a name="L64" href="source/net/ipv4/proc.c#L64">64</a>         <a href="ident?i=seq_printf">seq_printf</a>(<a href="ident?i=seq">seq</a>, <i>"TCP: inuse %d orphan %d tw %d alloc %d mem %ld\n"</i>,
 <a name="L65" href="source/net/ipv4/proc.c#L65">65</a>                    <a href="ident?i=sock_prot_inuse_get">sock_prot_inuse_get</a>(<a href="ident?i=net">net</a>, &amp;<a href="ident?i=tcp_prot">tcp_prot</a>), orphans,
 <a name="L66" href="source/net/ipv4/proc.c#L66">66</a>                    <a href="ident?i=atomic_read">atomic_read</a>(&amp;<a href="ident?i=tcp_death_row">tcp_death_row</a>.tw_count), <a href="ident?i=sockets">sockets</a>,
 <a name="L67" href="source/net/ipv4/proc.c#L67">67</a>                    <a href="ident?i=proto_memory_allocated">proto_memory_allocated</a>(&amp;<a href="ident?i=tcp_prot">tcp_prot</a>));
 <a name="L68" href="source/net/ipv4/proc.c#L68">68</a>         <a href="ident?i=seq_printf">seq_printf</a>(<a href="ident?i=seq">seq</a>, <i>"UDP: inuse %d mem %ld\n"</i>,
 <a name="L69" href="source/net/ipv4/proc.c#L69">69</a>                    <a href="ident?i=sock_prot_inuse_get">sock_prot_inuse_get</a>(<a href="ident?i=net">net</a>, &amp;<a href="ident?i=udp_prot">udp_prot</a>),
 <a name="L70" href="source/net/ipv4/proc.c#L70">70</a>                    <a href="ident?i=proto_memory_allocated">proto_memory_allocated</a>(&amp;<a href="ident?i=udp_prot">udp_prot</a>));
 <a name="L71" href="source/net/ipv4/proc.c#L71">71</a>         <a href="ident?i=seq_printf">seq_printf</a>(<a href="ident?i=seq">seq</a>, <i>"UDPLITE: inuse %d\n"</i>,
 <a name="L72" href="source/net/ipv4/proc.c#L72">72</a>                    <a href="ident?i=sock_prot_inuse_get">sock_prot_inuse_get</a>(<a href="ident?i=net">net</a>, &amp;<a href="ident?i=udplite_prot">udplite_prot</a>));
 <a name="L73" href="source/net/ipv4/proc.c#L73">73</a>         <a href="ident?i=seq_printf">seq_printf</a>(<a href="ident?i=seq">seq</a>, <i>"RAW: inuse %d\n"</i>,
 <a name="L74" href="source/net/ipv4/proc.c#L74">74</a>                    <a href="ident?i=sock_prot_inuse_get">sock_prot_inuse_get</a>(<a href="ident?i=net">net</a>, &amp;<a href="ident?i=raw_prot">raw_prot</a>));
 <a name="L75" href="source/net/ipv4/proc.c#L75">75</a>         frag_mem = <a href="ident?i=ip_frag_mem">ip_frag_mem</a>(<a href="ident?i=net">net</a>);
 <a name="L76" href="source/net/ipv4/proc.c#L76">76</a>         <a href="ident?i=seq_printf">seq_printf</a>(<a href="ident?i=seq">seq</a>,  <i>"FRAG: inuse %u memory %u\n"</i>, !!frag_mem, frag_mem);
 <a name="L77" href="source/net/ipv4/proc.c#L77">77</a>         return 0;
 <a name="L78" href="source/net/ipv4/proc.c#L78">78</a> }
 <a name="L79" href="source/net/ipv4/proc.c#L79">79</a> 
 <a name="L80" href="source/net/ipv4/proc.c#L80">80</a> static int <a href="ident?i=sockstat_seq_open">sockstat_seq_open</a>(struct <a href="ident?i=inode">inode</a> *<a href="ident?i=inode">inode</a>, struct <a href="ident?i=file">file</a> *<a href="ident?i=file">file</a>)
 <a name="L81" href="source/net/ipv4/proc.c#L81">81</a> {
 <a name="L82" href="source/net/ipv4/proc.c#L82">82</a>         return <a href="ident?i=single_open_net">single_open_net</a>(<a href="ident?i=inode">inode</a>, <a href="ident?i=file">file</a>, <a href="ident?i=sockstat_seq_show">sockstat_seq_show</a>);
 <a name="L83" href="source/net/ipv4/proc.c#L83">83</a> }
 <a name="L84" href="source/net/ipv4/proc.c#L84">84</a> 
 <a name="L85" href="source/net/ipv4/proc.c#L85">85</a> static const struct <a href="ident?i=file_operations">file_operations</a> <a href="ident?i=sockstat_seq_fops">sockstat_seq_fops</a> = {
 <a name="L86" href="source/net/ipv4/proc.c#L86">86</a>         .owner   = <a href="ident?i=THIS_MODULE">THIS_MODULE</a>,
 <a name="L87" href="source/net/ipv4/proc.c#L87">87</a>         .<a href="ident?i=open">open</a>    = <a href="ident?i=sockstat_seq_open">sockstat_seq_open</a>,
 <a name="L88" href="source/net/ipv4/proc.c#L88">88</a>         .<a href="ident?i=read">read</a>    = <a href="ident?i=seq_read">seq_read</a>,
 <a name="L89" href="source/net/ipv4/proc.c#L89">89</a>         .llseek  = <a href="ident?i=seq_lseek">seq_lseek</a>,
 <a name="L90" href="source/net/ipv4/proc.c#L90">90</a>         .<a href="ident?i=release">release</a> = <a href="ident?i=single_release_net">single_release_net</a>,
 <a name="L91" href="source/net/ipv4/proc.c#L91">91</a> };
 <a name="L92" href="source/net/ipv4/proc.c#L92">92</a> 
 <a name="L93" href="source/net/ipv4/proc.c#L93">93</a> <b><i>/* snmp items */</i></b>
 <a name="L94" href="source/net/ipv4/proc.c#L94">94</a> static const struct <a href="ident?i=snmp_mib">snmp_mib</a> <a href="ident?i=snmp4_ipstats_list">snmp4_ipstats_list</a>[] = {
 <a name="L95" href="source/net/ipv4/proc.c#L95">95</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"InReceives"</i>, IPSTATS_MIB_INPKTS),
 <a name="L96" href="source/net/ipv4/proc.c#L96">96</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"InHdrErrors"</i>, IPSTATS_MIB_INHDRERRORS),
 <a name="L97" href="source/net/ipv4/proc.c#L97">97</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"InAddrErrors"</i>, IPSTATS_MIB_INADDRERRORS),
 <a name="L98" href="source/net/ipv4/proc.c#L98">98</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"ForwDatagrams"</i>, IPSTATS_MIB_OUTFORWDATAGRAMS),
 <a name="L99" href="source/net/ipv4/proc.c#L99">99</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"InUnknownProtos"</i>, IPSTATS_MIB_INUNKNOWNPROTOS),
<a name="L100" href="source/net/ipv4/proc.c#L100">100</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"InDiscards"</i>, IPSTATS_MIB_INDISCARDS),
<a name="L101" href="source/net/ipv4/proc.c#L101">101</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"InDelivers"</i>, IPSTATS_MIB_INDELIVERS),
<a name="L102" href="source/net/ipv4/proc.c#L102">102</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"OutRequests"</i>, IPSTATS_MIB_OUTPKTS),
<a name="L103" href="source/net/ipv4/proc.c#L103">103</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"OutDiscards"</i>, IPSTATS_MIB_OUTDISCARDS),
<a name="L104" href="source/net/ipv4/proc.c#L104">104</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"OutNoRoutes"</i>, IPSTATS_MIB_OUTNOROUTES),
<a name="L105" href="source/net/ipv4/proc.c#L105">105</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"ReasmTimeout"</i>, IPSTATS_MIB_REASMTIMEOUT),
<a name="L106" href="source/net/ipv4/proc.c#L106">106</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"ReasmReqds"</i>, IPSTATS_MIB_REASMREQDS),
<a name="L107" href="source/net/ipv4/proc.c#L107">107</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"ReasmOKs"</i>, IPSTATS_MIB_REASMOKS),
<a name="L108" href="source/net/ipv4/proc.c#L108">108</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"ReasmFails"</i>, IPSTATS_MIB_REASMFAILS),
<a name="L109" href="source/net/ipv4/proc.c#L109">109</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"FragOKs"</i>, IPSTATS_MIB_FRAGOKS),
<a name="L110" href="source/net/ipv4/proc.c#L110">110</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"FragFails"</i>, IPSTATS_MIB_FRAGFAILS),
<a name="L111" href="source/net/ipv4/proc.c#L111">111</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"FragCreates"</i>, IPSTATS_MIB_FRAGCREATES),
<a name="L112" href="source/net/ipv4/proc.c#L112">112</a>         <a href="ident?i=SNMP_MIB_SENTINEL">SNMP_MIB_SENTINEL</a>
<a name="L113" href="source/net/ipv4/proc.c#L113">113</a> };
<a name="L114" href="source/net/ipv4/proc.c#L114">114</a> 
<a name="L115" href="source/net/ipv4/proc.c#L115">115</a> <b><i>/* Following items are displayed in /proc/net/netstat */</i></b>
<a name="L116" href="source/net/ipv4/proc.c#L116">116</a> static const struct <a href="ident?i=snmp_mib">snmp_mib</a> <a href="ident?i=snmp4_ipextstats_list">snmp4_ipextstats_list</a>[] = {
<a name="L117" href="source/net/ipv4/proc.c#L117">117</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"InNoRoutes"</i>, IPSTATS_MIB_INNOROUTES),
<a name="L118" href="source/net/ipv4/proc.c#L118">118</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"InTruncatedPkts"</i>, IPSTATS_MIB_INTRUNCATEDPKTS),
<a name="L119" href="source/net/ipv4/proc.c#L119">119</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"InMcastPkts"</i>, IPSTATS_MIB_INMCASTPKTS),
<a name="L120" href="source/net/ipv4/proc.c#L120">120</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"OutMcastPkts"</i>, IPSTATS_MIB_OUTMCASTPKTS),
<a name="L121" href="source/net/ipv4/proc.c#L121">121</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"InBcastPkts"</i>, IPSTATS_MIB_INBCASTPKTS),
<a name="L122" href="source/net/ipv4/proc.c#L122">122</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"OutBcastPkts"</i>, IPSTATS_MIB_OUTBCASTPKTS),
<a name="L123" href="source/net/ipv4/proc.c#L123">123</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"InOctets"</i>, IPSTATS_MIB_INOCTETS),
<a name="L124" href="source/net/ipv4/proc.c#L124">124</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"OutOctets"</i>, IPSTATS_MIB_OUTOCTETS),
<a name="L125" href="source/net/ipv4/proc.c#L125">125</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"InMcastOctets"</i>, IPSTATS_MIB_INMCASTOCTETS),
<a name="L126" href="source/net/ipv4/proc.c#L126">126</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"OutMcastOctets"</i>, IPSTATS_MIB_OUTMCASTOCTETS),
<a name="L127" href="source/net/ipv4/proc.c#L127">127</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"InBcastOctets"</i>, IPSTATS_MIB_INBCASTOCTETS),
<a name="L128" href="source/net/ipv4/proc.c#L128">128</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"OutBcastOctets"</i>, IPSTATS_MIB_OUTBCASTOCTETS),
<a name="L129" href="source/net/ipv4/proc.c#L129">129</a>         <b><i>/* Non RFC4293 fields */</i></b>
<a name="L130" href="source/net/ipv4/proc.c#L130">130</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"InCsumErrors"</i>, IPSTATS_MIB_CSUMERRORS),
<a name="L131" href="source/net/ipv4/proc.c#L131">131</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"InNoECTPkts"</i>, IPSTATS_MIB_NOECTPKTS),
<a name="L132" href="source/net/ipv4/proc.c#L132">132</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"InECT1Pkts"</i>, IPSTATS_MIB_ECT1PKTS),
<a name="L133" href="source/net/ipv4/proc.c#L133">133</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"InECT0Pkts"</i>, IPSTATS_MIB_ECT0PKTS),
<a name="L134" href="source/net/ipv4/proc.c#L134">134</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"InCEPkts"</i>, IPSTATS_MIB_CEPKTS),
<a name="L135" href="source/net/ipv4/proc.c#L135">135</a>         <a href="ident?i=SNMP_MIB_SENTINEL">SNMP_MIB_SENTINEL</a>
<a name="L136" href="source/net/ipv4/proc.c#L136">136</a> };
<a name="L137" href="source/net/ipv4/proc.c#L137">137</a> 
<a name="L138" href="source/net/ipv4/proc.c#L138">138</a> static const struct {
<a name="L139" href="source/net/ipv4/proc.c#L139">139</a>         const char *<a href="ident?i=name">name</a>;
<a name="L140" href="source/net/ipv4/proc.c#L140">140</a>         int <a href="ident?i=index">index</a>;
<a name="L141" href="source/net/ipv4/proc.c#L141">141</a> } <a href="ident?i=icmpmibmap">icmpmibmap</a>[] = {
<a name="L142" href="source/net/ipv4/proc.c#L142">142</a>         { <i>"DestUnreachs"</i>, <a href="ident?i=ICMP_DEST_UNREACH">ICMP_DEST_UNREACH</a> },
<a name="L143" href="source/net/ipv4/proc.c#L143">143</a>         { <i>"TimeExcds"</i>, <a href="ident?i=ICMP_TIME_EXCEEDED">ICMP_TIME_EXCEEDED</a> },
<a name="L144" href="source/net/ipv4/proc.c#L144">144</a>         { <i>"ParmProbs"</i>, <a href="ident?i=ICMP_PARAMETERPROB">ICMP_PARAMETERPROB</a> },
<a name="L145" href="source/net/ipv4/proc.c#L145">145</a>         { <i>"SrcQuenchs"</i>, <a href="ident?i=ICMP_SOURCE_QUENCH">ICMP_SOURCE_QUENCH</a> },
<a name="L146" href="source/net/ipv4/proc.c#L146">146</a>         { <i>"Redirects"</i>, <a href="ident?i=ICMP_REDIRECT">ICMP_REDIRECT</a> },
<a name="L147" href="source/net/ipv4/proc.c#L147">147</a>         { <i>"Echos"</i>, <a href="ident?i=ICMP_ECHO">ICMP_ECHO</a> },
<a name="L148" href="source/net/ipv4/proc.c#L148">148</a>         { <i>"EchoReps"</i>, <a href="ident?i=ICMP_ECHOREPLY">ICMP_ECHOREPLY</a> },
<a name="L149" href="source/net/ipv4/proc.c#L149">149</a>         { <i>"Timestamps"</i>, <a href="ident?i=ICMP_TIMESTAMP">ICMP_TIMESTAMP</a> },
<a name="L150" href="source/net/ipv4/proc.c#L150">150</a>         { <i>"TimestampReps"</i>, <a href="ident?i=ICMP_TIMESTAMPREPLY">ICMP_TIMESTAMPREPLY</a> },
<a name="L151" href="source/net/ipv4/proc.c#L151">151</a>         { <i>"AddrMasks"</i>, <a href="ident?i=ICMP_ADDRESS">ICMP_ADDRESS</a> },
<a name="L152" href="source/net/ipv4/proc.c#L152">152</a>         { <i>"AddrMaskReps"</i>, <a href="ident?i=ICMP_ADDRESSREPLY">ICMP_ADDRESSREPLY</a> },
<a name="L153" href="source/net/ipv4/proc.c#L153">153</a>         { <a href="ident?i=NULL">NULL</a>, 0 }
<a name="L154" href="source/net/ipv4/proc.c#L154">154</a> };
<a name="L155" href="source/net/ipv4/proc.c#L155">155</a> 
<a name="L156" href="source/net/ipv4/proc.c#L156">156</a> 
<a name="L157" href="source/net/ipv4/proc.c#L157">157</a> static const struct <a href="ident?i=snmp_mib">snmp_mib</a> <a href="ident?i=snmp4_tcp_list">snmp4_tcp_list</a>[] = {
<a name="L158" href="source/net/ipv4/proc.c#L158">158</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"RtoAlgorithm"</i>, TCP_MIB_RTOALGORITHM),
<a name="L159" href="source/net/ipv4/proc.c#L159">159</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"RtoMin"</i>, TCP_MIB_RTOMIN),
<a name="L160" href="source/net/ipv4/proc.c#L160">160</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"RtoMax"</i>, TCP_MIB_RTOMAX),
<a name="L161" href="source/net/ipv4/proc.c#L161">161</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"MaxConn"</i>, TCP_MIB_MAXCONN),
<a name="L162" href="source/net/ipv4/proc.c#L162">162</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"ActiveOpens"</i>, TCP_MIB_ACTIVEOPENS),
<a name="L163" href="source/net/ipv4/proc.c#L163">163</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"PassiveOpens"</i>, TCP_MIB_PASSIVEOPENS),
<a name="L164" href="source/net/ipv4/proc.c#L164">164</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"AttemptFails"</i>, TCP_MIB_ATTEMPTFAILS),
<a name="L165" href="source/net/ipv4/proc.c#L165">165</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"EstabResets"</i>, TCP_MIB_ESTABRESETS),
<a name="L166" href="source/net/ipv4/proc.c#L166">166</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"CurrEstab"</i>, TCP_MIB_CURRESTAB),
<a name="L167" href="source/net/ipv4/proc.c#L167">167</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"InSegs"</i>, TCP_MIB_INSEGS),
<a name="L168" href="source/net/ipv4/proc.c#L168">168</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"OutSegs"</i>, TCP_MIB_OUTSEGS),
<a name="L169" href="source/net/ipv4/proc.c#L169">169</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"RetransSegs"</i>, TCP_MIB_RETRANSSEGS),
<a name="L170" href="source/net/ipv4/proc.c#L170">170</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"InErrs"</i>, TCP_MIB_INERRS),
<a name="L171" href="source/net/ipv4/proc.c#L171">171</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"OutRsts"</i>, TCP_MIB_OUTRSTS),
<a name="L172" href="source/net/ipv4/proc.c#L172">172</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"InCsumErrors"</i>, TCP_MIB_CSUMERRORS),
<a name="L173" href="source/net/ipv4/proc.c#L173">173</a>         <a href="ident?i=SNMP_MIB_SENTINEL">SNMP_MIB_SENTINEL</a>
<a name="L174" href="source/net/ipv4/proc.c#L174">174</a> };
<a name="L175" href="source/net/ipv4/proc.c#L175">175</a> 
<a name="L176" href="source/net/ipv4/proc.c#L176">176</a> static const struct <a href="ident?i=snmp_mib">snmp_mib</a> <a href="ident?i=snmp4_udp_list">snmp4_udp_list</a>[] = {
<a name="L177" href="source/net/ipv4/proc.c#L177">177</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"InDatagrams"</i>, UDP_MIB_INDATAGRAMS),
<a name="L178" href="source/net/ipv4/proc.c#L178">178</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"NoPorts"</i>, UDP_MIB_NOPORTS),
<a name="L179" href="source/net/ipv4/proc.c#L179">179</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"InErrors"</i>, UDP_MIB_INERRORS),
<a name="L180" href="source/net/ipv4/proc.c#L180">180</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"OutDatagrams"</i>, UDP_MIB_OUTDATAGRAMS),
<a name="L181" href="source/net/ipv4/proc.c#L181">181</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"RcvbufErrors"</i>, UDP_MIB_RCVBUFERRORS),
<a name="L182" href="source/net/ipv4/proc.c#L182">182</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"SndbufErrors"</i>, UDP_MIB_SNDBUFERRORS),
<a name="L183" href="source/net/ipv4/proc.c#L183">183</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"InCsumErrors"</i>, UDP_MIB_CSUMERRORS),
<a name="L184" href="source/net/ipv4/proc.c#L184">184</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"IgnoredMulti"</i>, UDP_MIB_IGNOREDMULTI),
<a name="L185" href="source/net/ipv4/proc.c#L185">185</a>         <a href="ident?i=SNMP_MIB_SENTINEL">SNMP_MIB_SENTINEL</a>
<a name="L186" href="source/net/ipv4/proc.c#L186">186</a> };
<a name="L187" href="source/net/ipv4/proc.c#L187">187</a> 
<a name="L188" href="source/net/ipv4/proc.c#L188">188</a> static const struct <a href="ident?i=snmp_mib">snmp_mib</a> <a href="ident?i=snmp4_net_list">snmp4_net_list</a>[] = {
<a name="L189" href="source/net/ipv4/proc.c#L189">189</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"SyncookiesSent"</i>, LINUX_MIB_SYNCOOKIESSENT),
<a name="L190" href="source/net/ipv4/proc.c#L190">190</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"SyncookiesRecv"</i>, LINUX_MIB_SYNCOOKIESRECV),
<a name="L191" href="source/net/ipv4/proc.c#L191">191</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"SyncookiesFailed"</i>, LINUX_MIB_SYNCOOKIESFAILED),
<a name="L192" href="source/net/ipv4/proc.c#L192">192</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"EmbryonicRsts"</i>, LINUX_MIB_EMBRYONICRSTS),
<a name="L193" href="source/net/ipv4/proc.c#L193">193</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"PruneCalled"</i>, LINUX_MIB_PRUNECALLED),
<a name="L194" href="source/net/ipv4/proc.c#L194">194</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"RcvPruned"</i>, LINUX_MIB_RCVPRUNED),
<a name="L195" href="source/net/ipv4/proc.c#L195">195</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"OfoPruned"</i>, LINUX_MIB_OFOPRUNED),
<a name="L196" href="source/net/ipv4/proc.c#L196">196</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"OutOfWindowIcmps"</i>, LINUX_MIB_OUTOFWINDOWICMPS),
<a name="L197" href="source/net/ipv4/proc.c#L197">197</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"LockDroppedIcmps"</i>, LINUX_MIB_LOCKDROPPEDICMPS),
<a name="L198" href="source/net/ipv4/proc.c#L198">198</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"ArpFilter"</i>, LINUX_MIB_ARPFILTER),
<a name="L199" href="source/net/ipv4/proc.c#L199">199</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"TW"</i>, LINUX_MIB_TIMEWAITED),
<a name="L200" href="source/net/ipv4/proc.c#L200">200</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"TWRecycled"</i>, LINUX_MIB_TIMEWAITRECYCLED),
<a name="L201" href="source/net/ipv4/proc.c#L201">201</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"TWKilled"</i>, LINUX_MIB_TIMEWAITKILLED),
<a name="L202" href="source/net/ipv4/proc.c#L202">202</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"PAWSPassive"</i>, LINUX_MIB_PAWSPASSIVEREJECTED),
<a name="L203" href="source/net/ipv4/proc.c#L203">203</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"PAWSActive"</i>, LINUX_MIB_PAWSACTIVEREJECTED),
<a name="L204" href="source/net/ipv4/proc.c#L204">204</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"PAWSEstab"</i>, LINUX_MIB_PAWSESTABREJECTED),
<a name="L205" href="source/net/ipv4/proc.c#L205">205</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"DelayedACKs"</i>, LINUX_MIB_DELAYEDACKS),
<a name="L206" href="source/net/ipv4/proc.c#L206">206</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"DelayedACKLocked"</i>, LINUX_MIB_DELAYEDACKLOCKED),
<a name="L207" href="source/net/ipv4/proc.c#L207">207</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"DelayedACKLost"</i>, LINUX_MIB_DELAYEDACKLOST),
<a name="L208" href="source/net/ipv4/proc.c#L208">208</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"ListenOverflows"</i>, LINUX_MIB_LISTENOVERFLOWS),
<a name="L209" href="source/net/ipv4/proc.c#L209">209</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"ListenDrops"</i>, LINUX_MIB_LISTENDROPS),
<a name="L210" href="source/net/ipv4/proc.c#L210">210</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"TCPPrequeued"</i>, LINUX_MIB_TCPPREQUEUED),
<a name="L211" href="source/net/ipv4/proc.c#L211">211</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"TCPDirectCopyFromBacklog"</i>, LINUX_MIB_TCPDIRECTCOPYFROMBACKLOG),
<a name="L212" href="source/net/ipv4/proc.c#L212">212</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"TCPDirectCopyFromPrequeue"</i>, LINUX_MIB_TCPDIRECTCOPYFROMPREQUEUE),
<a name="L213" href="source/net/ipv4/proc.c#L213">213</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"TCPPrequeueDropped"</i>, LINUX_MIB_TCPPREQUEUEDROPPED),
<a name="L214" href="source/net/ipv4/proc.c#L214">214</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"TCPHPHits"</i>, LINUX_MIB_TCPHPHITS),
<a name="L215" href="source/net/ipv4/proc.c#L215">215</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"TCPHPHitsToUser"</i>, LINUX_MIB_TCPHPHITSTOUSER),
<a name="L216" href="source/net/ipv4/proc.c#L216">216</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"TCPPureAcks"</i>, LINUX_MIB_TCPPUREACKS),
<a name="L217" href="source/net/ipv4/proc.c#L217">217</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"TCPHPAcks"</i>, LINUX_MIB_TCPHPACKS),
<a name="L218" href="source/net/ipv4/proc.c#L218">218</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"TCPRenoRecovery"</i>, LINUX_MIB_TCPRENORECOVERY),
<a name="L219" href="source/net/ipv4/proc.c#L219">219</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"TCPSackRecovery"</i>, LINUX_MIB_TCPSACKRECOVERY),
<a name="L220" href="source/net/ipv4/proc.c#L220">220</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"TCPSACKReneging"</i>, LINUX_MIB_TCPSACKRENEGING),
<a name="L221" href="source/net/ipv4/proc.c#L221">221</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"TCPFACKReorder"</i>, LINUX_MIB_TCPFACKREORDER),
<a name="L222" href="source/net/ipv4/proc.c#L222">222</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"TCPSACKReorder"</i>, LINUX_MIB_TCPSACKREORDER),
<a name="L223" href="source/net/ipv4/proc.c#L223">223</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"TCPRenoReorder"</i>, LINUX_MIB_TCPRENOREORDER),
<a name="L224" href="source/net/ipv4/proc.c#L224">224</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"TCPTSReorder"</i>, LINUX_MIB_TCPTSREORDER),
<a name="L225" href="source/net/ipv4/proc.c#L225">225</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"TCPFullUndo"</i>, LINUX_MIB_TCPFULLUNDO),
<a name="L226" href="source/net/ipv4/proc.c#L226">226</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"TCPPartialUndo"</i>, LINUX_MIB_TCPPARTIALUNDO),
<a name="L227" href="source/net/ipv4/proc.c#L227">227</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"TCPDSACKUndo"</i>, LINUX_MIB_TCPDSACKUNDO),
<a name="L228" href="source/net/ipv4/proc.c#L228">228</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"TCPLossUndo"</i>, LINUX_MIB_TCPLOSSUNDO),
<a name="L229" href="source/net/ipv4/proc.c#L229">229</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"TCPLostRetransmit"</i>, LINUX_MIB_TCPLOSTRETRANSMIT),
<a name="L230" href="source/net/ipv4/proc.c#L230">230</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"TCPRenoFailures"</i>, LINUX_MIB_TCPRENOFAILURES),
<a name="L231" href="source/net/ipv4/proc.c#L231">231</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"TCPSackFailures"</i>, LINUX_MIB_TCPSACKFAILURES),
<a name="L232" href="source/net/ipv4/proc.c#L232">232</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"TCPLossFailures"</i>, LINUX_MIB_TCPLOSSFAILURES),
<a name="L233" href="source/net/ipv4/proc.c#L233">233</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"TCPFastRetrans"</i>, LINUX_MIB_TCPFASTRETRANS),
<a name="L234" href="source/net/ipv4/proc.c#L234">234</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"TCPForwardRetrans"</i>, LINUX_MIB_TCPFORWARDRETRANS),
<a name="L235" href="source/net/ipv4/proc.c#L235">235</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"TCPSlowStartRetrans"</i>, LINUX_MIB_TCPSLOWSTARTRETRANS),
<a name="L236" href="source/net/ipv4/proc.c#L236">236</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"TCPTimeouts"</i>, LINUX_MIB_TCPTIMEOUTS),
<a name="L237" href="source/net/ipv4/proc.c#L237">237</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"TCPLossProbes"</i>, LINUX_MIB_TCPLOSSPROBES),
<a name="L238" href="source/net/ipv4/proc.c#L238">238</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"TCPLossProbeRecovery"</i>, LINUX_MIB_TCPLOSSPROBERECOVERY),
<a name="L239" href="source/net/ipv4/proc.c#L239">239</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"TCPRenoRecoveryFail"</i>, LINUX_MIB_TCPRENORECOVERYFAIL),
<a name="L240" href="source/net/ipv4/proc.c#L240">240</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"TCPSackRecoveryFail"</i>, LINUX_MIB_TCPSACKRECOVERYFAIL),
<a name="L241" href="source/net/ipv4/proc.c#L241">241</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"TCPSchedulerFailed"</i>, LINUX_MIB_TCPSCHEDULERFAILED),
<a name="L242" href="source/net/ipv4/proc.c#L242">242</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"TCPRcvCollapsed"</i>, LINUX_MIB_TCPRCVCOLLAPSED),
<a name="L243" href="source/net/ipv4/proc.c#L243">243</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"TCPDSACKOldSent"</i>, LINUX_MIB_TCPDSACKOLDSENT),
<a name="L244" href="source/net/ipv4/proc.c#L244">244</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"TCPDSACKOfoSent"</i>, LINUX_MIB_TCPDSACKOFOSENT),
<a name="L245" href="source/net/ipv4/proc.c#L245">245</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"TCPDSACKRecv"</i>, LINUX_MIB_TCPDSACKRECV),
<a name="L246" href="source/net/ipv4/proc.c#L246">246</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"TCPDSACKOfoRecv"</i>, LINUX_MIB_TCPDSACKOFORECV),
<a name="L247" href="source/net/ipv4/proc.c#L247">247</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"TCPAbortOnData"</i>, LINUX_MIB_TCPABORTONDATA),
<a name="L248" href="source/net/ipv4/proc.c#L248">248</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"TCPAbortOnClose"</i>, LINUX_MIB_TCPABORTONCLOSE),
<a name="L249" href="source/net/ipv4/proc.c#L249">249</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"TCPAbortOnMemory"</i>, LINUX_MIB_TCPABORTONMEMORY),
<a name="L250" href="source/net/ipv4/proc.c#L250">250</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"TCPAbortOnTimeout"</i>, LINUX_MIB_TCPABORTONTIMEOUT),
<a name="L251" href="source/net/ipv4/proc.c#L251">251</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"TCPAbortOnLinger"</i>, LINUX_MIB_TCPABORTONLINGER),
<a name="L252" href="source/net/ipv4/proc.c#L252">252</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"TCPAbortFailed"</i>, LINUX_MIB_TCPABORTFAILED),
<a name="L253" href="source/net/ipv4/proc.c#L253">253</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"TCPMemoryPressures"</i>, LINUX_MIB_TCPMEMORYPRESSURES),
<a name="L254" href="source/net/ipv4/proc.c#L254">254</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"TCPSACKDiscard"</i>, LINUX_MIB_TCPSACKDISCARD),
<a name="L255" href="source/net/ipv4/proc.c#L255">255</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"TCPDSACKIgnoredOld"</i>, LINUX_MIB_TCPDSACKIGNOREDOLD),
<a name="L256" href="source/net/ipv4/proc.c#L256">256</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"TCPDSACKIgnoredNoUndo"</i>, LINUX_MIB_TCPDSACKIGNOREDNOUNDO),
<a name="L257" href="source/net/ipv4/proc.c#L257">257</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"TCPSpuriousRTOs"</i>, LINUX_MIB_TCPSPURIOUSRTOS),
<a name="L258" href="source/net/ipv4/proc.c#L258">258</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"TCPMD5NotFound"</i>, LINUX_MIB_TCPMD5NOTFOUND),
<a name="L259" href="source/net/ipv4/proc.c#L259">259</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"TCPMD5Unexpected"</i>, LINUX_MIB_TCPMD5UNEXPECTED),
<a name="L260" href="source/net/ipv4/proc.c#L260">260</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"TCPSackShifted"</i>, LINUX_MIB_SACKSHIFTED),
<a name="L261" href="source/net/ipv4/proc.c#L261">261</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"TCPSackMerged"</i>, LINUX_MIB_SACKMERGED),
<a name="L262" href="source/net/ipv4/proc.c#L262">262</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"TCPSackShiftFallback"</i>, LINUX_MIB_SACKSHIFTFALLBACK),
<a name="L263" href="source/net/ipv4/proc.c#L263">263</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"TCPBacklogDrop"</i>, LINUX_MIB_TCPBACKLOGDROP),
<a name="L264" href="source/net/ipv4/proc.c#L264">264</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"TCPMinTTLDrop"</i>, LINUX_MIB_TCPMINTTLDROP),
<a name="L265" href="source/net/ipv4/proc.c#L265">265</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"TCPDeferAcceptDrop"</i>, LINUX_MIB_TCPDEFERACCEPTDROP),
<a name="L266" href="source/net/ipv4/proc.c#L266">266</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"IPReversePathFilter"</i>, LINUX_MIB_IPRPFILTER),
<a name="L267" href="source/net/ipv4/proc.c#L267">267</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"TCPTimeWaitOverflow"</i>, LINUX_MIB_TCPTIMEWAITOVERFLOW),
<a name="L268" href="source/net/ipv4/proc.c#L268">268</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"TCPReqQFullDoCookies"</i>, LINUX_MIB_TCPREQQFULLDOCOOKIES),
<a name="L269" href="source/net/ipv4/proc.c#L269">269</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"TCPReqQFullDrop"</i>, LINUX_MIB_TCPREQQFULLDROP),
<a name="L270" href="source/net/ipv4/proc.c#L270">270</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"TCPRetransFail"</i>, LINUX_MIB_TCPRETRANSFAIL),
<a name="L271" href="source/net/ipv4/proc.c#L271">271</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"TCPRcvCoalesce"</i>, LINUX_MIB_TCPRCVCOALESCE),
<a name="L272" href="source/net/ipv4/proc.c#L272">272</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"TCPOFOQueue"</i>, LINUX_MIB_TCPOFOQUEUE),
<a name="L273" href="source/net/ipv4/proc.c#L273">273</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"TCPOFODrop"</i>, LINUX_MIB_TCPOFODROP),
<a name="L274" href="source/net/ipv4/proc.c#L274">274</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"TCPOFOMerge"</i>, LINUX_MIB_TCPOFOMERGE),
<a name="L275" href="source/net/ipv4/proc.c#L275">275</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"TCPChallengeACK"</i>, LINUX_MIB_TCPCHALLENGEACK),
<a name="L276" href="source/net/ipv4/proc.c#L276">276</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"TCPSYNChallenge"</i>, LINUX_MIB_TCPSYNCHALLENGE),
<a name="L277" href="source/net/ipv4/proc.c#L277">277</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"TCPFastOpenActive"</i>, LINUX_MIB_TCPFASTOPENACTIVE),
<a name="L278" href="source/net/ipv4/proc.c#L278">278</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"TCPFastOpenActiveFail"</i>, LINUX_MIB_TCPFASTOPENACTIVEFAIL),
<a name="L279" href="source/net/ipv4/proc.c#L279">279</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"TCPFastOpenPassive"</i>, LINUX_MIB_TCPFASTOPENPASSIVE),
<a name="L280" href="source/net/ipv4/proc.c#L280">280</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"TCPFastOpenPassiveFail"</i>, LINUX_MIB_TCPFASTOPENPASSIVEFAIL),
<a name="L281" href="source/net/ipv4/proc.c#L281">281</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"TCPFastOpenListenOverflow"</i>, LINUX_MIB_TCPFASTOPENLISTENOVERFLOW),
<a name="L282" href="source/net/ipv4/proc.c#L282">282</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"TCPFastOpenCookieReqd"</i>, LINUX_MIB_TCPFASTOPENCOOKIEREQD),
<a name="L283" href="source/net/ipv4/proc.c#L283">283</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"TCPSpuriousRtxHostQueues"</i>, LINUX_MIB_TCPSPURIOUS_RTX_HOSTQUEUES),
<a name="L284" href="source/net/ipv4/proc.c#L284">284</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"BusyPollRxPackets"</i>, LINUX_MIB_BUSYPOLLRXPACKETS),
<a name="L285" href="source/net/ipv4/proc.c#L285">285</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"TCPAutoCorking"</i>, LINUX_MIB_TCPAUTOCORKING),
<a name="L286" href="source/net/ipv4/proc.c#L286">286</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"TCPFromZeroWindowAdv"</i>, LINUX_MIB_TCPFROMZEROWINDOWADV),
<a name="L287" href="source/net/ipv4/proc.c#L287">287</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"TCPToZeroWindowAdv"</i>, LINUX_MIB_TCPTOZEROWINDOWADV),
<a name="L288" href="source/net/ipv4/proc.c#L288">288</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"TCPWantZeroWindowAdv"</i>, LINUX_MIB_TCPWANTZEROWINDOWADV),
<a name="L289" href="source/net/ipv4/proc.c#L289">289</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"TCPSynRetrans"</i>, LINUX_MIB_TCPSYNRETRANS),
<a name="L290" href="source/net/ipv4/proc.c#L290">290</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"TCPOrigDataSent"</i>, LINUX_MIB_TCPORIGDATASENT),
<a name="L291" href="source/net/ipv4/proc.c#L291">291</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"TCPHystartTrainDetect"</i>, LINUX_MIB_TCPHYSTARTTRAINDETECT),
<a name="L292" href="source/net/ipv4/proc.c#L292">292</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"TCPHystartTrainCwnd"</i>, LINUX_MIB_TCPHYSTARTTRAINCWND),
<a name="L293" href="source/net/ipv4/proc.c#L293">293</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"TCPHystartDelayDetect"</i>, LINUX_MIB_TCPHYSTARTDELAYDETECT),
<a name="L294" href="source/net/ipv4/proc.c#L294">294</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"TCPHystartDelayCwnd"</i>, LINUX_MIB_TCPHYSTARTDELAYCWND),
<a name="L295" href="source/net/ipv4/proc.c#L295">295</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"TCPACKSkippedSynRecv"</i>, LINUX_MIB_TCPACKSKIPPEDSYNRECV),
<a name="L296" href="source/net/ipv4/proc.c#L296">296</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"TCPACKSkippedPAWS"</i>, LINUX_MIB_TCPACKSKIPPEDPAWS),
<a name="L297" href="source/net/ipv4/proc.c#L297">297</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"TCPACKSkippedSeq"</i>, LINUX_MIB_TCPACKSKIPPEDSEQ),
<a name="L298" href="source/net/ipv4/proc.c#L298">298</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"TCPACKSkippedFinWait2"</i>, LINUX_MIB_TCPACKSKIPPEDFINWAIT2),
<a name="L299" href="source/net/ipv4/proc.c#L299">299</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"TCPACKSkippedTimeWait"</i>, LINUX_MIB_TCPACKSKIPPEDTIMEWAIT),
<a name="L300" href="source/net/ipv4/proc.c#L300">300</a>         <a href="ident?i=SNMP_MIB_ITEM">SNMP_MIB_ITEM</a>(<i>"TCPACKSkippedChallenge"</i>, LINUX_MIB_TCPACKSKIPPEDCHALLENGE),
<a name="L301" href="source/net/ipv4/proc.c#L301">301</a>         <a href="ident?i=SNMP_MIB_SENTINEL">SNMP_MIB_SENTINEL</a>
<a name="L302" href="source/net/ipv4/proc.c#L302">302</a> };
<a name="L303" href="source/net/ipv4/proc.c#L303">303</a> 
<a name="L304" href="source/net/ipv4/proc.c#L304">304</a> static void <a href="ident?i=icmpmsg_put_line">icmpmsg_put_line</a>(struct <a href="ident?i=seq_file">seq_file</a> *<a href="ident?i=seq">seq</a>, unsigned long *vals,
<a name="L305" href="source/net/ipv4/proc.c#L305">305</a>                              unsigned short *<a href="ident?i=type">type</a>, int <a href="ident?i=count">count</a>)
<a name="L306" href="source/net/ipv4/proc.c#L306">306</a> {
<a name="L307" href="source/net/ipv4/proc.c#L307">307</a>         int j;
<a name="L308" href="source/net/ipv4/proc.c#L308">308</a> 
<a name="L309" href="source/net/ipv4/proc.c#L309">309</a>         if (<a href="ident?i=count">count</a>) {
<a name="L310" href="source/net/ipv4/proc.c#L310">310</a>                 <a href="ident?i=seq_puts">seq_puts</a>(<a href="ident?i=seq">seq</a>, <i>"\nIcmpMsg:"</i>);
<a name="L311" href="source/net/ipv4/proc.c#L311">311</a>                 for (j = 0; j &lt; <a href="ident?i=count">count</a>; ++j)
<a name="L312" href="source/net/ipv4/proc.c#L312">312</a>                         <a href="ident?i=seq_printf">seq_printf</a>(<a href="ident?i=seq">seq</a>, <i>" %sType%u"</i>,
<a name="L313" href="source/net/ipv4/proc.c#L313">313</a>                                 <a href="ident?i=type">type</a>[j] &amp; 0x100 ? <i>"Out"</i> : <i>"In"</i>,
<a name="L314" href="source/net/ipv4/proc.c#L314">314</a>                                 <a href="ident?i=type">type</a>[j] &amp; 0xff);
<a name="L315" href="source/net/ipv4/proc.c#L315">315</a>                 <a href="ident?i=seq_puts">seq_puts</a>(<a href="ident?i=seq">seq</a>, <i>"\nIcmpMsg:"</i>);
<a name="L316" href="source/net/ipv4/proc.c#L316">316</a>                 for (j = 0; j &lt; <a href="ident?i=count">count</a>; ++j)
<a name="L317" href="source/net/ipv4/proc.c#L317">317</a>                         <a href="ident?i=seq_printf">seq_printf</a>(<a href="ident?i=seq">seq</a>, <i>" %lu"</i>, vals[j]);
<a name="L318" href="source/net/ipv4/proc.c#L318">318</a>         }
<a name="L319" href="source/net/ipv4/proc.c#L319">319</a> }
<a name="L320" href="source/net/ipv4/proc.c#L320">320</a> 
<a name="L321" href="source/net/ipv4/proc.c#L321">321</a> static void <a href="ident?i=icmpmsg_put">icmpmsg_put</a>(struct <a href="ident?i=seq_file">seq_file</a> *<a href="ident?i=seq">seq</a>)
<a name="L322" href="source/net/ipv4/proc.c#L322">322</a> {
<a name="L323" href="source/net/ipv4/proc.c#L323">323</a> #define <a href="ident?i=PERLINE">PERLINE</a> 16
<a name="L324" href="source/net/ipv4/proc.c#L324">324</a> 
<a name="L325" href="source/net/ipv4/proc.c#L325">325</a>         int <a href="ident?i=i">i</a>, <a href="ident?i=count">count</a>;
<a name="L326" href="source/net/ipv4/proc.c#L326">326</a>         unsigned short <a href="ident?i=type">type</a>[<a href="ident?i=PERLINE">PERLINE</a>];
<a name="L327" href="source/net/ipv4/proc.c#L327">327</a>         unsigned long vals[<a href="ident?i=PERLINE">PERLINE</a>], <a href="ident?i=val">val</a>;
<a name="L328" href="source/net/ipv4/proc.c#L328">328</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=seq">seq</a>-&gt;<a href="ident?i=private">private</a>;
<a name="L329" href="source/net/ipv4/proc.c#L329">329</a> 
<a name="L330" href="source/net/ipv4/proc.c#L330">330</a>         <a href="ident?i=count">count</a> = 0;
<a name="L331" href="source/net/ipv4/proc.c#L331">331</a>         for (<a href="ident?i=i">i</a> = 0; <a href="ident?i=i">i</a> &lt; <a href="ident?i=ICMPMSG_MIB_MAX">ICMPMSG_MIB_MAX</a>; <a href="ident?i=i">i</a>++) {
<a name="L332" href="source/net/ipv4/proc.c#L332">332</a>                 <a href="ident?i=val">val</a> = <a href="ident?i=atomic_long_read">atomic_long_read</a>(&amp;<a href="ident?i=net">net</a>-&gt;mib.icmpmsg_statistics-&gt;mibs[<a href="ident?i=i">i</a>]);
<a name="L333" href="source/net/ipv4/proc.c#L333">333</a>                 if (<a href="ident?i=val">val</a>) {
<a name="L334" href="source/net/ipv4/proc.c#L334">334</a>                         <a href="ident?i=type">type</a>[<a href="ident?i=count">count</a>] = <a href="ident?i=i">i</a>;
<a name="L335" href="source/net/ipv4/proc.c#L335">335</a>                         vals[<a href="ident?i=count">count</a>++] = <a href="ident?i=val">val</a>;
<a name="L336" href="source/net/ipv4/proc.c#L336">336</a>                 }
<a name="L337" href="source/net/ipv4/proc.c#L337">337</a>                 if (<a href="ident?i=count">count</a> == <a href="ident?i=PERLINE">PERLINE</a>) {
<a name="L338" href="source/net/ipv4/proc.c#L338">338</a>                         <a href="ident?i=icmpmsg_put_line">icmpmsg_put_line</a>(<a href="ident?i=seq">seq</a>, vals, <a href="ident?i=type">type</a>, <a href="ident?i=count">count</a>);
<a name="L339" href="source/net/ipv4/proc.c#L339">339</a>                         <a href="ident?i=count">count</a> = 0;
<a name="L340" href="source/net/ipv4/proc.c#L340">340</a>                 }
<a name="L341" href="source/net/ipv4/proc.c#L341">341</a>         }
<a name="L342" href="source/net/ipv4/proc.c#L342">342</a>         <a href="ident?i=icmpmsg_put_line">icmpmsg_put_line</a>(<a href="ident?i=seq">seq</a>, vals, <a href="ident?i=type">type</a>, <a href="ident?i=count">count</a>);
<a name="L343" href="source/net/ipv4/proc.c#L343">343</a> 
<a name="L344" href="source/net/ipv4/proc.c#L344">344</a> #undef <a href="ident?i=PERLINE">PERLINE</a>
<a name="L345" href="source/net/ipv4/proc.c#L345">345</a> }
<a name="L346" href="source/net/ipv4/proc.c#L346">346</a> 
<a name="L347" href="source/net/ipv4/proc.c#L347">347</a> static void <a href="ident?i=icmp_put">icmp_put</a>(struct <a href="ident?i=seq_file">seq_file</a> *<a href="ident?i=seq">seq</a>)
<a name="L348" href="source/net/ipv4/proc.c#L348">348</a> {
<a name="L349" href="source/net/ipv4/proc.c#L349">349</a>         int <a href="ident?i=i">i</a>;
<a name="L350" href="source/net/ipv4/proc.c#L350">350</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=seq">seq</a>-&gt;<a href="ident?i=private">private</a>;
<a name="L351" href="source/net/ipv4/proc.c#L351">351</a>         <a href="ident?i=atomic_long_t">atomic_long_t</a> *<a href="ident?i=ptr">ptr</a> = <a href="ident?i=net">net</a>-&gt;mib.icmpmsg_statistics-&gt;mibs;
<a name="L352" href="source/net/ipv4/proc.c#L352">352</a> 
<a name="L353" href="source/net/ipv4/proc.c#L353">353</a>         <a href="ident?i=seq_puts">seq_puts</a>(<a href="ident?i=seq">seq</a>, <i>"\nIcmp: InMsgs InErrors InCsumErrors"</i>);
<a name="L354" href="source/net/ipv4/proc.c#L354">354</a>         for (<a href="ident?i=i">i</a> = 0; <a href="ident?i=icmpmibmap">icmpmibmap</a>[<a href="ident?i=i">i</a>].<a href="ident?i=name">name</a> != <a href="ident?i=NULL">NULL</a>; <a href="ident?i=i">i</a>++)
<a name="L355" href="source/net/ipv4/proc.c#L355">355</a>                 <a href="ident?i=seq_printf">seq_printf</a>(<a href="ident?i=seq">seq</a>, <i>" In%s"</i>, <a href="ident?i=icmpmibmap">icmpmibmap</a>[<a href="ident?i=i">i</a>].<a href="ident?i=name">name</a>);
<a name="L356" href="source/net/ipv4/proc.c#L356">356</a>         <a href="ident?i=seq_puts">seq_puts</a>(<a href="ident?i=seq">seq</a>, <i>" OutMsgs OutErrors"</i>);
<a name="L357" href="source/net/ipv4/proc.c#L357">357</a>         for (<a href="ident?i=i">i</a> = 0; <a href="ident?i=icmpmibmap">icmpmibmap</a>[<a href="ident?i=i">i</a>].<a href="ident?i=name">name</a> != <a href="ident?i=NULL">NULL</a>; <a href="ident?i=i">i</a>++)
<a name="L358" href="source/net/ipv4/proc.c#L358">358</a>                 <a href="ident?i=seq_printf">seq_printf</a>(<a href="ident?i=seq">seq</a>, <i>" Out%s"</i>, <a href="ident?i=icmpmibmap">icmpmibmap</a>[<a href="ident?i=i">i</a>].<a href="ident?i=name">name</a>);
<a name="L359" href="source/net/ipv4/proc.c#L359">359</a>         <a href="ident?i=seq_printf">seq_printf</a>(<a href="ident?i=seq">seq</a>, <i>"\nIcmp: %lu %lu %lu"</i>,
<a name="L360" href="source/net/ipv4/proc.c#L360">360</a>                 <a href="ident?i=snmp_fold_field">snmp_fold_field</a>(<a href="ident?i=net">net</a>-&gt;mib.icmp_statistics, ICMP_MIB_INMSGS),
<a name="L361" href="source/net/ipv4/proc.c#L361">361</a>                 <a href="ident?i=snmp_fold_field">snmp_fold_field</a>(<a href="ident?i=net">net</a>-&gt;mib.icmp_statistics, ICMP_MIB_INERRORS),
<a name="L362" href="source/net/ipv4/proc.c#L362">362</a>                 <a href="ident?i=snmp_fold_field">snmp_fold_field</a>(<a href="ident?i=net">net</a>-&gt;mib.icmp_statistics, ICMP_MIB_CSUMERRORS));
<a name="L363" href="source/net/ipv4/proc.c#L363">363</a>         for (<a href="ident?i=i">i</a> = 0; <a href="ident?i=icmpmibmap">icmpmibmap</a>[<a href="ident?i=i">i</a>].<a href="ident?i=name">name</a> != <a href="ident?i=NULL">NULL</a>; <a href="ident?i=i">i</a>++)
<a name="L364" href="source/net/ipv4/proc.c#L364">364</a>                 <a href="ident?i=seq_printf">seq_printf</a>(<a href="ident?i=seq">seq</a>, <i>" %lu"</i>,
<a name="L365" href="source/net/ipv4/proc.c#L365">365</a>                            <a href="ident?i=atomic_long_read">atomic_long_read</a>(<a href="ident?i=ptr">ptr</a> + <a href="ident?i=icmpmibmap">icmpmibmap</a>[<a href="ident?i=i">i</a>].<a href="ident?i=index">index</a>));
<a name="L366" href="source/net/ipv4/proc.c#L366">366</a>         <a href="ident?i=seq_printf">seq_printf</a>(<a href="ident?i=seq">seq</a>, <i>" %lu %lu"</i>,
<a name="L367" href="source/net/ipv4/proc.c#L367">367</a>                 <a href="ident?i=snmp_fold_field">snmp_fold_field</a>(<a href="ident?i=net">net</a>-&gt;mib.icmp_statistics, ICMP_MIB_OUTMSGS),
<a name="L368" href="source/net/ipv4/proc.c#L368">368</a>                 <a href="ident?i=snmp_fold_field">snmp_fold_field</a>(<a href="ident?i=net">net</a>-&gt;mib.icmp_statistics, ICMP_MIB_OUTERRORS));
<a name="L369" href="source/net/ipv4/proc.c#L369">369</a>         for (<a href="ident?i=i">i</a> = 0; <a href="ident?i=icmpmibmap">icmpmibmap</a>[<a href="ident?i=i">i</a>].<a href="ident?i=name">name</a> != <a href="ident?i=NULL">NULL</a>; <a href="ident?i=i">i</a>++)
<a name="L370" href="source/net/ipv4/proc.c#L370">370</a>                 <a href="ident?i=seq_printf">seq_printf</a>(<a href="ident?i=seq">seq</a>, <i>" %lu"</i>,
<a name="L371" href="source/net/ipv4/proc.c#L371">371</a>                            <a href="ident?i=atomic_long_read">atomic_long_read</a>(<a href="ident?i=ptr">ptr</a> + (<a href="ident?i=icmpmibmap">icmpmibmap</a>[<a href="ident?i=i">i</a>].<a href="ident?i=index">index</a> | 0x100)));
<a name="L372" href="source/net/ipv4/proc.c#L372">372</a> }
<a name="L373" href="source/net/ipv4/proc.c#L373">373</a> 
<a name="L374" href="source/net/ipv4/proc.c#L374">374</a> <b><i>/*</i></b>
<a name="L375" href="source/net/ipv4/proc.c#L375">375</a> <b><i> *      Called from the PROCfs module. This outputs /proc/net/snmp.</i></b>
<a name="L376" href="source/net/ipv4/proc.c#L376">376</a> <b><i> */</i></b>
<a name="L377" href="source/net/ipv4/proc.c#L377">377</a> static int <a href="ident?i=snmp_seq_show">snmp_seq_show</a>(struct <a href="ident?i=seq_file">seq_file</a> *<a href="ident?i=seq">seq</a>, void *<a href="ident?i=v">v</a>)
<a name="L378" href="source/net/ipv4/proc.c#L378">378</a> {
<a name="L379" href="source/net/ipv4/proc.c#L379">379</a>         int <a href="ident?i=i">i</a>;
<a name="L380" href="source/net/ipv4/proc.c#L380">380</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=seq">seq</a>-&gt;<a href="ident?i=private">private</a>;
<a name="L381" href="source/net/ipv4/proc.c#L381">381</a> 
<a name="L382" href="source/net/ipv4/proc.c#L382">382</a>         <a href="ident?i=seq_puts">seq_puts</a>(<a href="ident?i=seq">seq</a>, <i>"Ip: Forwarding DefaultTTL"</i>);
<a name="L383" href="source/net/ipv4/proc.c#L383">383</a> 
<a name="L384" href="source/net/ipv4/proc.c#L384">384</a>         for (<a href="ident?i=i">i</a> = 0; <a href="ident?i=snmp4_ipstats_list">snmp4_ipstats_list</a>[<a href="ident?i=i">i</a>].<a href="ident?i=name">name</a> != <a href="ident?i=NULL">NULL</a>; <a href="ident?i=i">i</a>++)
<a name="L385" href="source/net/ipv4/proc.c#L385">385</a>                 <a href="ident?i=seq_printf">seq_printf</a>(<a href="ident?i=seq">seq</a>, <i>" %s"</i>, <a href="ident?i=snmp4_ipstats_list">snmp4_ipstats_list</a>[<a href="ident?i=i">i</a>].<a href="ident?i=name">name</a>);
<a name="L386" href="source/net/ipv4/proc.c#L386">386</a> 
<a name="L387" href="source/net/ipv4/proc.c#L387">387</a>         <a href="ident?i=seq_printf">seq_printf</a>(<a href="ident?i=seq">seq</a>, <i>"\nIp: %d %d"</i>,
<a name="L388" href="source/net/ipv4/proc.c#L388">388</a>                    <a href="ident?i=IPV4_DEVCONF_ALL">IPV4_DEVCONF_ALL</a>(<a href="ident?i=net">net</a>, FORWARDING) ? 1 : 2,
<a name="L389" href="source/net/ipv4/proc.c#L389">389</a>                    <a href="ident?i=sysctl_ip_default_ttl">sysctl_ip_default_ttl</a>);
<a name="L390" href="source/net/ipv4/proc.c#L390">390</a> 
<a name="L391" href="source/net/ipv4/proc.c#L391">391</a>         <a href="ident?i=BUILD_BUG_ON">BUILD_BUG_ON</a>(<a href="ident?i=offsetof">offsetof</a>(struct <a href="ident?i=ipstats_mib">ipstats_mib</a>, mibs) != 0);
<a name="L392" href="source/net/ipv4/proc.c#L392">392</a>         for (<a href="ident?i=i">i</a> = 0; <a href="ident?i=snmp4_ipstats_list">snmp4_ipstats_list</a>[<a href="ident?i=i">i</a>].<a href="ident?i=name">name</a> != <a href="ident?i=NULL">NULL</a>; <a href="ident?i=i">i</a>++)
<a name="L393" href="source/net/ipv4/proc.c#L393">393</a>                 <a href="ident?i=seq_printf">seq_printf</a>(<a href="ident?i=seq">seq</a>, <i>" %llu"</i>,
<a name="L394" href="source/net/ipv4/proc.c#L394">394</a>                            <a href="ident?i=snmp_fold_field64">snmp_fold_field64</a>(<a href="ident?i=net">net</a>-&gt;mib.ip_statistics,
<a name="L395" href="source/net/ipv4/proc.c#L395">395</a>                                              <a href="ident?i=snmp4_ipstats_list">snmp4_ipstats_list</a>[<a href="ident?i=i">i</a>].<a href="ident?i=entry">entry</a>,
<a name="L396" href="source/net/ipv4/proc.c#L396">396</a>                                              <a href="ident?i=offsetof">offsetof</a>(struct <a href="ident?i=ipstats_mib">ipstats_mib</a>, syncp)));
<a name="L397" href="source/net/ipv4/proc.c#L397">397</a> 
<a name="L398" href="source/net/ipv4/proc.c#L398">398</a>         <a href="ident?i=icmp_put">icmp_put</a>(<a href="ident?i=seq">seq</a>);  <b><i>/* RFC 2011 compatibility */</i></b>
<a name="L399" href="source/net/ipv4/proc.c#L399">399</a>         <a href="ident?i=icmpmsg_put">icmpmsg_put</a>(<a href="ident?i=seq">seq</a>);
<a name="L400" href="source/net/ipv4/proc.c#L400">400</a> 
<a name="L401" href="source/net/ipv4/proc.c#L401">401</a>         <a href="ident?i=seq_puts">seq_puts</a>(<a href="ident?i=seq">seq</a>, <i>"\nTcp:"</i>);
<a name="L402" href="source/net/ipv4/proc.c#L402">402</a>         for (<a href="ident?i=i">i</a> = 0; <a href="ident?i=snmp4_tcp_list">snmp4_tcp_list</a>[<a href="ident?i=i">i</a>].<a href="ident?i=name">name</a> != <a href="ident?i=NULL">NULL</a>; <a href="ident?i=i">i</a>++)
<a name="L403" href="source/net/ipv4/proc.c#L403">403</a>                 <a href="ident?i=seq_printf">seq_printf</a>(<a href="ident?i=seq">seq</a>, <i>" %s"</i>, <a href="ident?i=snmp4_tcp_list">snmp4_tcp_list</a>[<a href="ident?i=i">i</a>].<a href="ident?i=name">name</a>);
<a name="L404" href="source/net/ipv4/proc.c#L404">404</a> 
<a name="L405" href="source/net/ipv4/proc.c#L405">405</a>         <a href="ident?i=seq_puts">seq_puts</a>(<a href="ident?i=seq">seq</a>, <i>"\nTcp:"</i>);
<a name="L406" href="source/net/ipv4/proc.c#L406">406</a>         for (<a href="ident?i=i">i</a> = 0; <a href="ident?i=snmp4_tcp_list">snmp4_tcp_list</a>[<a href="ident?i=i">i</a>].<a href="ident?i=name">name</a> != <a href="ident?i=NULL">NULL</a>; <a href="ident?i=i">i</a>++) {
<a name="L407" href="source/net/ipv4/proc.c#L407">407</a>                 <b><i>/* MaxConn field is signed, RFC 2012 */</i></b>
<a name="L408" href="source/net/ipv4/proc.c#L408">408</a>                 if (<a href="ident?i=snmp4_tcp_list">snmp4_tcp_list</a>[<a href="ident?i=i">i</a>].<a href="ident?i=entry">entry</a> == TCP_MIB_MAXCONN)
<a name="L409" href="source/net/ipv4/proc.c#L409">409</a>                         <a href="ident?i=seq_printf">seq_printf</a>(<a href="ident?i=seq">seq</a>, <i>" %ld"</i>,
<a name="L410" href="source/net/ipv4/proc.c#L410">410</a>                                    <a href="ident?i=snmp_fold_field">snmp_fold_field</a>(<a href="ident?i=net">net</a>-&gt;mib.tcp_statistics,
<a name="L411" href="source/net/ipv4/proc.c#L411">411</a>                                                    <a href="ident?i=snmp4_tcp_list">snmp4_tcp_list</a>[<a href="ident?i=i">i</a>].<a href="ident?i=entry">entry</a>));
<a name="L412" href="source/net/ipv4/proc.c#L412">412</a>                 else
<a name="L413" href="source/net/ipv4/proc.c#L413">413</a>                         <a href="ident?i=seq_printf">seq_printf</a>(<a href="ident?i=seq">seq</a>, <i>" %lu"</i>,
<a name="L414" href="source/net/ipv4/proc.c#L414">414</a>                                    <a href="ident?i=snmp_fold_field">snmp_fold_field</a>(<a href="ident?i=net">net</a>-&gt;mib.tcp_statistics,
<a name="L415" href="source/net/ipv4/proc.c#L415">415</a>                                                    <a href="ident?i=snmp4_tcp_list">snmp4_tcp_list</a>[<a href="ident?i=i">i</a>].<a href="ident?i=entry">entry</a>));
<a name="L416" href="source/net/ipv4/proc.c#L416">416</a>         }
<a name="L417" href="source/net/ipv4/proc.c#L417">417</a> 
<a name="L418" href="source/net/ipv4/proc.c#L418">418</a>         <a href="ident?i=seq_puts">seq_puts</a>(<a href="ident?i=seq">seq</a>, <i>"\nUdp:"</i>);
<a name="L419" href="source/net/ipv4/proc.c#L419">419</a>         for (<a href="ident?i=i">i</a> = 0; <a href="ident?i=snmp4_udp_list">snmp4_udp_list</a>[<a href="ident?i=i">i</a>].<a href="ident?i=name">name</a> != <a href="ident?i=NULL">NULL</a>; <a href="ident?i=i">i</a>++)
<a name="L420" href="source/net/ipv4/proc.c#L420">420</a>                 <a href="ident?i=seq_printf">seq_printf</a>(<a href="ident?i=seq">seq</a>, <i>" %s"</i>, <a href="ident?i=snmp4_udp_list">snmp4_udp_list</a>[<a href="ident?i=i">i</a>].<a href="ident?i=name">name</a>);
<a name="L421" href="source/net/ipv4/proc.c#L421">421</a> 
<a name="L422" href="source/net/ipv4/proc.c#L422">422</a>         <a href="ident?i=seq_puts">seq_puts</a>(<a href="ident?i=seq">seq</a>, <i>"\nUdp:"</i>);
<a name="L423" href="source/net/ipv4/proc.c#L423">423</a>         for (<a href="ident?i=i">i</a> = 0; <a href="ident?i=snmp4_udp_list">snmp4_udp_list</a>[<a href="ident?i=i">i</a>].<a href="ident?i=name">name</a> != <a href="ident?i=NULL">NULL</a>; <a href="ident?i=i">i</a>++)
<a name="L424" href="source/net/ipv4/proc.c#L424">424</a>                 <a href="ident?i=seq_printf">seq_printf</a>(<a href="ident?i=seq">seq</a>, <i>" %lu"</i>,
<a name="L425" href="source/net/ipv4/proc.c#L425">425</a>                            <a href="ident?i=snmp_fold_field">snmp_fold_field</a>(<a href="ident?i=net">net</a>-&gt;mib.udp_statistics,
<a name="L426" href="source/net/ipv4/proc.c#L426">426</a>                                            <a href="ident?i=snmp4_udp_list">snmp4_udp_list</a>[<a href="ident?i=i">i</a>].<a href="ident?i=entry">entry</a>));
<a name="L427" href="source/net/ipv4/proc.c#L427">427</a> 
<a name="L428" href="source/net/ipv4/proc.c#L428">428</a>         <b><i>/* the UDP and UDP-Lite MIBs are the same */</i></b>
<a name="L429" href="source/net/ipv4/proc.c#L429">429</a>         <a href="ident?i=seq_puts">seq_puts</a>(<a href="ident?i=seq">seq</a>, <i>"\nUdpLite:"</i>);
<a name="L430" href="source/net/ipv4/proc.c#L430">430</a>         for (<a href="ident?i=i">i</a> = 0; <a href="ident?i=snmp4_udp_list">snmp4_udp_list</a>[<a href="ident?i=i">i</a>].<a href="ident?i=name">name</a> != <a href="ident?i=NULL">NULL</a>; <a href="ident?i=i">i</a>++)
<a name="L431" href="source/net/ipv4/proc.c#L431">431</a>                 <a href="ident?i=seq_printf">seq_printf</a>(<a href="ident?i=seq">seq</a>, <i>" %s"</i>, <a href="ident?i=snmp4_udp_list">snmp4_udp_list</a>[<a href="ident?i=i">i</a>].<a href="ident?i=name">name</a>);
<a name="L432" href="source/net/ipv4/proc.c#L432">432</a> 
<a name="L433" href="source/net/ipv4/proc.c#L433">433</a>         <a href="ident?i=seq_puts">seq_puts</a>(<a href="ident?i=seq">seq</a>, <i>"\nUdpLite:"</i>);
<a name="L434" href="source/net/ipv4/proc.c#L434">434</a>         for (<a href="ident?i=i">i</a> = 0; <a href="ident?i=snmp4_udp_list">snmp4_udp_list</a>[<a href="ident?i=i">i</a>].<a href="ident?i=name">name</a> != <a href="ident?i=NULL">NULL</a>; <a href="ident?i=i">i</a>++)
<a name="L435" href="source/net/ipv4/proc.c#L435">435</a>                 <a href="ident?i=seq_printf">seq_printf</a>(<a href="ident?i=seq">seq</a>, <i>" %lu"</i>,
<a name="L436" href="source/net/ipv4/proc.c#L436">436</a>                            <a href="ident?i=snmp_fold_field">snmp_fold_field</a>(<a href="ident?i=net">net</a>-&gt;mib.udplite_statistics,
<a name="L437" href="source/net/ipv4/proc.c#L437">437</a>                                            <a href="ident?i=snmp4_udp_list">snmp4_udp_list</a>[<a href="ident?i=i">i</a>].<a href="ident?i=entry">entry</a>));
<a name="L438" href="source/net/ipv4/proc.c#L438">438</a> 
<a name="L439" href="source/net/ipv4/proc.c#L439">439</a>         <a href="ident?i=seq_putc">seq_putc</a>(<a href="ident?i=seq">seq</a>, <i>'\n'</i>);
<a name="L440" href="source/net/ipv4/proc.c#L440">440</a>         return 0;
<a name="L441" href="source/net/ipv4/proc.c#L441">441</a> }
<a name="L442" href="source/net/ipv4/proc.c#L442">442</a> 
<a name="L443" href="source/net/ipv4/proc.c#L443">443</a> static int <a href="ident?i=snmp_seq_open">snmp_seq_open</a>(struct <a href="ident?i=inode">inode</a> *<a href="ident?i=inode">inode</a>, struct <a href="ident?i=file">file</a> *<a href="ident?i=file">file</a>)
<a name="L444" href="source/net/ipv4/proc.c#L444">444</a> {
<a name="L445" href="source/net/ipv4/proc.c#L445">445</a>         return <a href="ident?i=single_open_net">single_open_net</a>(<a href="ident?i=inode">inode</a>, <a href="ident?i=file">file</a>, <a href="ident?i=snmp_seq_show">snmp_seq_show</a>);
<a name="L446" href="source/net/ipv4/proc.c#L446">446</a> }
<a name="L447" href="source/net/ipv4/proc.c#L447">447</a> 
<a name="L448" href="source/net/ipv4/proc.c#L448">448</a> static const struct <a href="ident?i=file_operations">file_operations</a> <a href="ident?i=snmp_seq_fops">snmp_seq_fops</a> = {
<a name="L449" href="source/net/ipv4/proc.c#L449">449</a>         .owner   = <a href="ident?i=THIS_MODULE">THIS_MODULE</a>,
<a name="L450" href="source/net/ipv4/proc.c#L450">450</a>         .<a href="ident?i=open">open</a>    = <a href="ident?i=snmp_seq_open">snmp_seq_open</a>,
<a name="L451" href="source/net/ipv4/proc.c#L451">451</a>         .<a href="ident?i=read">read</a>    = <a href="ident?i=seq_read">seq_read</a>,
<a name="L452" href="source/net/ipv4/proc.c#L452">452</a>         .llseek  = <a href="ident?i=seq_lseek">seq_lseek</a>,
<a name="L453" href="source/net/ipv4/proc.c#L453">453</a>         .<a href="ident?i=release">release</a> = <a href="ident?i=single_release_net">single_release_net</a>,
<a name="L454" href="source/net/ipv4/proc.c#L454">454</a> };
<a name="L455" href="source/net/ipv4/proc.c#L455">455</a> 
<a name="L456" href="source/net/ipv4/proc.c#L456">456</a> 
<a name="L457" href="source/net/ipv4/proc.c#L457">457</a> 
<a name="L458" href="source/net/ipv4/proc.c#L458">458</a> <b><i>/*</i></b>
<a name="L459" href="source/net/ipv4/proc.c#L459">459</a> <b><i> *      Output /proc/net/netstat</i></b>
<a name="L460" href="source/net/ipv4/proc.c#L460">460</a> <b><i> */</i></b>
<a name="L461" href="source/net/ipv4/proc.c#L461">461</a> static int <a href="ident?i=netstat_seq_show">netstat_seq_show</a>(struct <a href="ident?i=seq_file">seq_file</a> *<a href="ident?i=seq">seq</a>, void *<a href="ident?i=v">v</a>)
<a name="L462" href="source/net/ipv4/proc.c#L462">462</a> {
<a name="L463" href="source/net/ipv4/proc.c#L463">463</a>         int <a href="ident?i=i">i</a>;
<a name="L464" href="source/net/ipv4/proc.c#L464">464</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=seq">seq</a>-&gt;<a href="ident?i=private">private</a>;
<a name="L465" href="source/net/ipv4/proc.c#L465">465</a> 
<a name="L466" href="source/net/ipv4/proc.c#L466">466</a>         <a href="ident?i=seq_puts">seq_puts</a>(<a href="ident?i=seq">seq</a>, <i>"TcpExt:"</i>);
<a name="L467" href="source/net/ipv4/proc.c#L467">467</a>         for (<a href="ident?i=i">i</a> = 0; <a href="ident?i=snmp4_net_list">snmp4_net_list</a>[<a href="ident?i=i">i</a>].<a href="ident?i=name">name</a> != <a href="ident?i=NULL">NULL</a>; <a href="ident?i=i">i</a>++)
<a name="L468" href="source/net/ipv4/proc.c#L468">468</a>                 <a href="ident?i=seq_printf">seq_printf</a>(<a href="ident?i=seq">seq</a>, <i>" %s"</i>, <a href="ident?i=snmp4_net_list">snmp4_net_list</a>[<a href="ident?i=i">i</a>].<a href="ident?i=name">name</a>);
<a name="L469" href="source/net/ipv4/proc.c#L469">469</a> 
<a name="L470" href="source/net/ipv4/proc.c#L470">470</a>         <a href="ident?i=seq_puts">seq_puts</a>(<a href="ident?i=seq">seq</a>, <i>"\nTcpExt:"</i>);
<a name="L471" href="source/net/ipv4/proc.c#L471">471</a>         for (<a href="ident?i=i">i</a> = 0; <a href="ident?i=snmp4_net_list">snmp4_net_list</a>[<a href="ident?i=i">i</a>].<a href="ident?i=name">name</a> != <a href="ident?i=NULL">NULL</a>; <a href="ident?i=i">i</a>++)
<a name="L472" href="source/net/ipv4/proc.c#L472">472</a>                 <a href="ident?i=seq_printf">seq_printf</a>(<a href="ident?i=seq">seq</a>, <i>" %lu"</i>,
<a name="L473" href="source/net/ipv4/proc.c#L473">473</a>                            <a href="ident?i=snmp_fold_field">snmp_fold_field</a>(<a href="ident?i=net">net</a>-&gt;mib.net_statistics,
<a name="L474" href="source/net/ipv4/proc.c#L474">474</a>                                            <a href="ident?i=snmp4_net_list">snmp4_net_list</a>[<a href="ident?i=i">i</a>].<a href="ident?i=entry">entry</a>));
<a name="L475" href="source/net/ipv4/proc.c#L475">475</a> 
<a name="L476" href="source/net/ipv4/proc.c#L476">476</a>         <a href="ident?i=seq_puts">seq_puts</a>(<a href="ident?i=seq">seq</a>, <i>"\nIpExt:"</i>);
<a name="L477" href="source/net/ipv4/proc.c#L477">477</a>         for (<a href="ident?i=i">i</a> = 0; <a href="ident?i=snmp4_ipextstats_list">snmp4_ipextstats_list</a>[<a href="ident?i=i">i</a>].<a href="ident?i=name">name</a> != <a href="ident?i=NULL">NULL</a>; <a href="ident?i=i">i</a>++)
<a name="L478" href="source/net/ipv4/proc.c#L478">478</a>                 <a href="ident?i=seq_printf">seq_printf</a>(<a href="ident?i=seq">seq</a>, <i>" %s"</i>, <a href="ident?i=snmp4_ipextstats_list">snmp4_ipextstats_list</a>[<a href="ident?i=i">i</a>].<a href="ident?i=name">name</a>);
<a name="L479" href="source/net/ipv4/proc.c#L479">479</a> 
<a name="L480" href="source/net/ipv4/proc.c#L480">480</a>         <a href="ident?i=seq_puts">seq_puts</a>(<a href="ident?i=seq">seq</a>, <i>"\nIpExt:"</i>);
<a name="L481" href="source/net/ipv4/proc.c#L481">481</a>         for (<a href="ident?i=i">i</a> = 0; <a href="ident?i=snmp4_ipextstats_list">snmp4_ipextstats_list</a>[<a href="ident?i=i">i</a>].<a href="ident?i=name">name</a> != <a href="ident?i=NULL">NULL</a>; <a href="ident?i=i">i</a>++)
<a name="L482" href="source/net/ipv4/proc.c#L482">482</a>                 <a href="ident?i=seq_printf">seq_printf</a>(<a href="ident?i=seq">seq</a>, <i>" %llu"</i>,
<a name="L483" href="source/net/ipv4/proc.c#L483">483</a>                            <a href="ident?i=snmp_fold_field64">snmp_fold_field64</a>(<a href="ident?i=net">net</a>-&gt;mib.ip_statistics,
<a name="L484" href="source/net/ipv4/proc.c#L484">484</a>                                              <a href="ident?i=snmp4_ipextstats_list">snmp4_ipextstats_list</a>[<a href="ident?i=i">i</a>].<a href="ident?i=entry">entry</a>,
<a name="L485" href="source/net/ipv4/proc.c#L485">485</a>                                              <a href="ident?i=offsetof">offsetof</a>(struct <a href="ident?i=ipstats_mib">ipstats_mib</a>, syncp)));
<a name="L486" href="source/net/ipv4/proc.c#L486">486</a> 
<a name="L487" href="source/net/ipv4/proc.c#L487">487</a>         <a href="ident?i=seq_putc">seq_putc</a>(<a href="ident?i=seq">seq</a>, <i>'\n'</i>);
<a name="L488" href="source/net/ipv4/proc.c#L488">488</a>         return 0;
<a name="L489" href="source/net/ipv4/proc.c#L489">489</a> }
<a name="L490" href="source/net/ipv4/proc.c#L490">490</a> 
<a name="L491" href="source/net/ipv4/proc.c#L491">491</a> static int <a href="ident?i=netstat_seq_open">netstat_seq_open</a>(struct <a href="ident?i=inode">inode</a> *<a href="ident?i=inode">inode</a>, struct <a href="ident?i=file">file</a> *<a href="ident?i=file">file</a>)
<a name="L492" href="source/net/ipv4/proc.c#L492">492</a> {
<a name="L493" href="source/net/ipv4/proc.c#L493">493</a>         return <a href="ident?i=single_open_net">single_open_net</a>(<a href="ident?i=inode">inode</a>, <a href="ident?i=file">file</a>, <a href="ident?i=netstat_seq_show">netstat_seq_show</a>);
<a name="L494" href="source/net/ipv4/proc.c#L494">494</a> }
<a name="L495" href="source/net/ipv4/proc.c#L495">495</a> 
<a name="L496" href="source/net/ipv4/proc.c#L496">496</a> static const struct <a href="ident?i=file_operations">file_operations</a> <a href="ident?i=netstat_seq_fops">netstat_seq_fops</a> = {
<a name="L497" href="source/net/ipv4/proc.c#L497">497</a>         .owner   = <a href="ident?i=THIS_MODULE">THIS_MODULE</a>,
<a name="L498" href="source/net/ipv4/proc.c#L498">498</a>         .<a href="ident?i=open">open</a>    = <a href="ident?i=netstat_seq_open">netstat_seq_open</a>,
<a name="L499" href="source/net/ipv4/proc.c#L499">499</a>         .<a href="ident?i=read">read</a>    = <a href="ident?i=seq_read">seq_read</a>,
<a name="L500" href="source/net/ipv4/proc.c#L500">500</a>         .llseek  = <a href="ident?i=seq_lseek">seq_lseek</a>,
<a name="L501" href="source/net/ipv4/proc.c#L501">501</a>         .<a href="ident?i=release">release</a> = <a href="ident?i=single_release_net">single_release_net</a>,
<a name="L502" href="source/net/ipv4/proc.c#L502">502</a> };
<a name="L503" href="source/net/ipv4/proc.c#L503">503</a> 
<a name="L504" href="source/net/ipv4/proc.c#L504">504</a> static <a href="ident?i=__net_init">__net_init</a> int <a href="ident?i=ip_proc_init_net">ip_proc_init_net</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>)
<a name="L505" href="source/net/ipv4/proc.c#L505">505</a> {
<a name="L506" href="source/net/ipv4/proc.c#L506">506</a>         if (!<a href="ident?i=proc_create">proc_create</a>(<i>"sockstat"</i>, <a href="ident?i=S_IRUGO">S_IRUGO</a>, <a href="ident?i=net">net</a>-&gt;proc_net,
<a name="L507" href="source/net/ipv4/proc.c#L507">507</a>                          &amp;<a href="ident?i=sockstat_seq_fops">sockstat_seq_fops</a>))
<a name="L508" href="source/net/ipv4/proc.c#L508">508</a>                 goto out_sockstat;
<a name="L509" href="source/net/ipv4/proc.c#L509">509</a>         if (!<a href="ident?i=proc_create">proc_create</a>(<i>"netstat"</i>, <a href="ident?i=S_IRUGO">S_IRUGO</a>, <a href="ident?i=net">net</a>-&gt;proc_net, &amp;<a href="ident?i=netstat_seq_fops">netstat_seq_fops</a>))
<a name="L510" href="source/net/ipv4/proc.c#L510">510</a>                 goto out_netstat;
<a name="L511" href="source/net/ipv4/proc.c#L511">511</a>         if (!<a href="ident?i=proc_create">proc_create</a>(<i>"snmp"</i>, <a href="ident?i=S_IRUGO">S_IRUGO</a>, <a href="ident?i=net">net</a>-&gt;proc_net, &amp;<a href="ident?i=snmp_seq_fops">snmp_seq_fops</a>))
<a name="L512" href="source/net/ipv4/proc.c#L512">512</a>                 goto out_snmp;
<a name="L513" href="source/net/ipv4/proc.c#L513">513</a> 
<a name="L514" href="source/net/ipv4/proc.c#L514">514</a>         return 0;
<a name="L515" href="source/net/ipv4/proc.c#L515">515</a> 
<a name="L516" href="source/net/ipv4/proc.c#L516">516</a> out_snmp:
<a name="L517" href="source/net/ipv4/proc.c#L517">517</a>         <a href="ident?i=remove_proc_entry">remove_proc_entry</a>(<i>"netstat"</i>, <a href="ident?i=net">net</a>-&gt;proc_net);
<a name="L518" href="source/net/ipv4/proc.c#L518">518</a> out_netstat:
<a name="L519" href="source/net/ipv4/proc.c#L519">519</a>         <a href="ident?i=remove_proc_entry">remove_proc_entry</a>(<i>"sockstat"</i>, <a href="ident?i=net">net</a>-&gt;proc_net);
<a name="L520" href="source/net/ipv4/proc.c#L520">520</a> out_sockstat:
<a name="L521" href="source/net/ipv4/proc.c#L521">521</a>         return -<a href="ident?i=ENOMEM">ENOMEM</a>;
<a name="L522" href="source/net/ipv4/proc.c#L522">522</a> }
<a name="L523" href="source/net/ipv4/proc.c#L523">523</a> 
<a name="L524" href="source/net/ipv4/proc.c#L524">524</a> static <a href="ident?i=__net_exit">__net_exit</a> void <a href="ident?i=ip_proc_exit_net">ip_proc_exit_net</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>)
<a name="L525" href="source/net/ipv4/proc.c#L525">525</a> {
<a name="L526" href="source/net/ipv4/proc.c#L526">526</a>         <a href="ident?i=remove_proc_entry">remove_proc_entry</a>(<i>"snmp"</i>, <a href="ident?i=net">net</a>-&gt;proc_net);
<a name="L527" href="source/net/ipv4/proc.c#L527">527</a>         <a href="ident?i=remove_proc_entry">remove_proc_entry</a>(<i>"netstat"</i>, <a href="ident?i=net">net</a>-&gt;proc_net);
<a name="L528" href="source/net/ipv4/proc.c#L528">528</a>         <a href="ident?i=remove_proc_entry">remove_proc_entry</a>(<i>"sockstat"</i>, <a href="ident?i=net">net</a>-&gt;proc_net);
<a name="L529" href="source/net/ipv4/proc.c#L529">529</a> }
<a name="L530" href="source/net/ipv4/proc.c#L530">530</a> 
<a name="L531" href="source/net/ipv4/proc.c#L531">531</a> static <a href="ident?i=__net_initdata">__net_initdata</a> struct <a href="ident?i=pernet_operations">pernet_operations</a> <a href="ident?i=ip_proc_ops">ip_proc_ops</a> = {
<a name="L532" href="source/net/ipv4/proc.c#L532">532</a>         .<a href="ident?i=init">init</a> = <a href="ident?i=ip_proc_init_net">ip_proc_init_net</a>,
<a name="L533" href="source/net/ipv4/proc.c#L533">533</a>         .<a href="ident?i=exit">exit</a> = <a href="ident?i=ip_proc_exit_net">ip_proc_exit_net</a>,
<a name="L534" href="source/net/ipv4/proc.c#L534">534</a> };
<a name="L535" href="source/net/ipv4/proc.c#L535">535</a> 
<a name="L536" href="source/net/ipv4/proc.c#L536">536</a> int <a href="ident?i=__init">__init</a> <a href="ident?i=ip_misc_proc_init">ip_misc_proc_init</a>(void)
<a name="L537" href="source/net/ipv4/proc.c#L537">537</a> {
<a name="L538" href="source/net/ipv4/proc.c#L538">538</a>         return <a href="ident?i=register_pernet_subsys">register_pernet_subsys</a>(&amp;<a href="ident?i=ip_proc_ops">ip_proc_ops</a>);
<a name="L539" href="source/net/ipv4/proc.c#L539">539</a> }
<a name="L540" href="source/net/ipv4/proc.c#L540">540</a> 
<a name="L541" href="source/net/ipv4/proc.c#L541">541</a> </pre></div><p>
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
