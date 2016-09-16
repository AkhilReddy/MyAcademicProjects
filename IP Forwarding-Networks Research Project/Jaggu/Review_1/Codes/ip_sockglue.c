<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title>Linux/net/ipv4/ip_sockglue.c - Linux Cross Reference - Free Electrons</title>
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
		 &nbsp;&bull;&nbsp;<b><i>source navigation</i></b> &nbsp;&bull;&nbsp;<a href="diff/net/ipv4/ip_sockglue.c">diff markup</a> &nbsp;&bull;&nbsp;<a href="ident">identifier search</a> &nbsp;&bull;&nbsp;<a href="search">freetext search</a> &nbsp;&bull;&nbsp;
		</p>
	</div>
</div>

<div id="topbar">
  
  <p>Version: &nbsp;<a href="source/net/ipv4/ip_sockglue.c?v=2.0.40">2.0.40</a>&nbsp;<a href="source/net/ipv4/ip_sockglue.c?v=2.2.26">2.2.26</a>&nbsp;<a href="source/net/ipv4/ip_sockglue.c?v=2.4.37">2.4.37</a>&nbsp;<a href="source/net/ipv4/ip_sockglue.c?v=3.5">3.5</a>&nbsp;<a href="source/net/ipv4/ip_sockglue.c?v=3.6">3.6</a>&nbsp;<a href="source/net/ipv4/ip_sockglue.c?v=3.7">3.7</a>&nbsp;<a href="source/net/ipv4/ip_sockglue.c?v=3.8">3.8</a>&nbsp;<a href="source/net/ipv4/ip_sockglue.c?v=3.9">3.9</a>&nbsp;<a href="source/net/ipv4/ip_sockglue.c?v=3.10">3.10</a>&nbsp;<a href="source/net/ipv4/ip_sockglue.c?v=3.11">3.11</a>&nbsp;<a href="source/net/ipv4/ip_sockglue.c?v=3.12">3.12</a>&nbsp;<a href="source/net/ipv4/ip_sockglue.c?v=3.13">3.13</a>&nbsp;<a href="source/net/ipv4/ip_sockglue.c?v=3.14">3.14</a>&nbsp;<a href="source/net/ipv4/ip_sockglue.c?v=3.15">3.15</a>&nbsp;<a href="source/net/ipv4/ip_sockglue.c?v=3.16">3.16</a>&nbsp;<a href="source/net/ipv4/ip_sockglue.c?v=3.17">3.17</a>&nbsp;<a href="source/net/ipv4/ip_sockglue.c?v=3.18">3.18</a>&nbsp;<a href="source/net/ipv4/ip_sockglue.c?v=3.19">3.19</a>&nbsp;<a href="source/net/ipv4/ip_sockglue.c?v=4.0">4.0</a>&nbsp;<b><i>4.1</i></b></p>
  
</div>

<h1><a href="source/">Linux</a>/<a href="source/net/">net</a>/<a href="source/net/ipv4/">ipv4</a>/<a href="source/net/ipv4/ip_sockglue.c">ip_sockglue.c</a></h1>
<div id="lxrcode"><pre>  <a name="L1" href="source/net/ipv4/ip_sockglue.c#L1">1</a> <b><i>/*</i></b>
  <a name="L2" href="source/net/ipv4/ip_sockglue.c#L2">2</a> <b><i> * INET         An implementation of the TCP/IP protocol suite for the LINUX</i></b>
  <a name="L3" href="source/net/ipv4/ip_sockglue.c#L3">3</a> <b><i> *              operating system.  INET is implemented using the  BSD Socket</i></b>
  <a name="L4" href="source/net/ipv4/ip_sockglue.c#L4">4</a> <b><i> *              interface as the means of communication with the user level.</i></b>
  <a name="L5" href="source/net/ipv4/ip_sockglue.c#L5">5</a> <b><i> *</i></b>
  <a name="L6" href="source/net/ipv4/ip_sockglue.c#L6">6</a> <b><i> *              The IP to API glue.</i></b>
  <a name="L7" href="source/net/ipv4/ip_sockglue.c#L7">7</a> <b><i> *</i></b>
  <a name="L8" href="source/net/ipv4/ip_sockglue.c#L8">8</a> <b><i> * Authors:     see ip.c</i></b>
  <a name="L9" href="source/net/ipv4/ip_sockglue.c#L9">9</a> <b><i> *</i></b>
 <a name="L10" href="source/net/ipv4/ip_sockglue.c#L10">10</a> <b><i> * Fixes:</i></b>
 <a name="L11" href="source/net/ipv4/ip_sockglue.c#L11">11</a> <b><i> *              Many            :       Split from ip.c , see ip.c for history.</i></b>
 <a name="L12" href="source/net/ipv4/ip_sockglue.c#L12">12</a> <b><i> *              Martin Mares    :       TOS setting fixed.</i></b>
 <a name="L13" href="source/net/ipv4/ip_sockglue.c#L13">13</a> <b><i> *              Alan Cox        :       Fixed a couple of oopses in Martin's</i></b>
 <a name="L14" href="source/net/ipv4/ip_sockglue.c#L14">14</a> <b><i> *                                      TOS tweaks.</i></b>
 <a name="L15" href="source/net/ipv4/ip_sockglue.c#L15">15</a> <b><i> *              Mike McLagan    :       Routing by source</i></b>
 <a name="L16" href="source/net/ipv4/ip_sockglue.c#L16">16</a> <b><i> */</i></b>
 <a name="L17" href="source/net/ipv4/ip_sockglue.c#L17">17</a> 
 <a name="L18" href="source/net/ipv4/ip_sockglue.c#L18">18</a> #include &lt;linux/module.h&gt;
 <a name="L19" href="source/net/ipv4/ip_sockglue.c#L19">19</a> #include &lt;linux/types.h&gt;
 <a name="L20" href="source/net/ipv4/ip_sockglue.c#L20">20</a> #include &lt;linux/mm.h&gt;
 <a name="L21" href="source/net/ipv4/ip_sockglue.c#L21">21</a> #include &lt;linux/skbuff.h&gt;
 <a name="L22" href="source/net/ipv4/ip_sockglue.c#L22">22</a> #include &lt;linux/ip.h&gt;
 <a name="L23" href="source/net/ipv4/ip_sockglue.c#L23">23</a> #include &lt;linux/icmp.h&gt;
 <a name="L24" href="source/net/ipv4/ip_sockglue.c#L24">24</a> #include &lt;linux/inetdevice.h&gt;
 <a name="L25" href="source/net/ipv4/ip_sockglue.c#L25">25</a> #include &lt;linux/netdevice.h&gt;
 <a name="L26" href="source/net/ipv4/ip_sockglue.c#L26">26</a> #include &lt;linux/slab.h&gt;
 <a name="L27" href="source/net/ipv4/ip_sockglue.c#L27">27</a> #include &lt;net/sock.h&gt;
 <a name="L28" href="source/net/ipv4/ip_sockglue.c#L28">28</a> #include &lt;net/ip.h&gt;
 <a name="L29" href="source/net/ipv4/ip_sockglue.c#L29">29</a> #include &lt;net/icmp.h&gt;
 <a name="L30" href="source/net/ipv4/ip_sockglue.c#L30">30</a> #include &lt;net/tcp_states.h&gt;
 <a name="L31" href="source/net/ipv4/ip_sockglue.c#L31">31</a> #include &lt;linux/udp.h&gt;
 <a name="L32" href="source/net/ipv4/ip_sockglue.c#L32">32</a> #include &lt;linux/igmp.h&gt;
 <a name="L33" href="source/net/ipv4/ip_sockglue.c#L33">33</a> #include &lt;linux/netfilter.h&gt;
 <a name="L34" href="source/net/ipv4/ip_sockglue.c#L34">34</a> #include &lt;linux/route.h&gt;
 <a name="L35" href="source/net/ipv4/ip_sockglue.c#L35">35</a> #include &lt;linux/mroute.h&gt;
 <a name="L36" href="source/net/ipv4/ip_sockglue.c#L36">36</a> #include &lt;net/inet_ecn.h&gt;
 <a name="L37" href="source/net/ipv4/ip_sockglue.c#L37">37</a> #include &lt;net/route.h&gt;
 <a name="L38" href="source/net/ipv4/ip_sockglue.c#L38">38</a> #include &lt;net/xfrm.h&gt;
 <a name="L39" href="source/net/ipv4/ip_sockglue.c#L39">39</a> #include &lt;net/compat.h&gt;
 <a name="L40" href="source/net/ipv4/ip_sockglue.c#L40">40</a> #include &lt;net/checksum.h&gt;
 <a name="L41" href="source/net/ipv4/ip_sockglue.c#L41">41</a> #if <a href="ident?i=IS_ENABLED">IS_ENABLED</a>(CONFIG_IPV6)
 <a name="L42" href="source/net/ipv4/ip_sockglue.c#L42">42</a> #include &lt;net/transp_v6.h&gt;
 <a name="L43" href="source/net/ipv4/ip_sockglue.c#L43">43</a> #endif
 <a name="L44" href="source/net/ipv4/ip_sockglue.c#L44">44</a> #include &lt;net/ip_fib.h&gt;
 <a name="L45" href="source/net/ipv4/ip_sockglue.c#L45">45</a> 
 <a name="L46" href="source/net/ipv4/ip_sockglue.c#L46">46</a> #include &lt;linux/errqueue.h&gt;
 <a name="L47" href="source/net/ipv4/ip_sockglue.c#L47">47</a> #include &lt;asm/uaccess.h&gt;
 <a name="L48" href="source/net/ipv4/ip_sockglue.c#L48">48</a> 
 <a name="L49" href="source/net/ipv4/ip_sockglue.c#L49">49</a> <b><i>/*</i></b>
 <a name="L50" href="source/net/ipv4/ip_sockglue.c#L50">50</a> <b><i> *      SOL_IP control messages.</i></b>
 <a name="L51" href="source/net/ipv4/ip_sockglue.c#L51">51</a> <b><i> */</i></b>
 <a name="L52" href="source/net/ipv4/ip_sockglue.c#L52">52</a> 
 <a name="L53" href="source/net/ipv4/ip_sockglue.c#L53">53</a> static void <a href="ident?i=ip_cmsg_recv_pktinfo">ip_cmsg_recv_pktinfo</a>(struct <a href="ident?i=msghdr">msghdr</a> *<a href="ident?i=msg">msg</a>, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
 <a name="L54" href="source/net/ipv4/ip_sockglue.c#L54">54</a> {
 <a name="L55" href="source/net/ipv4/ip_sockglue.c#L55">55</a>         struct <a href="ident?i=in_pktinfo">in_pktinfo</a> <a href="ident?i=info">info</a> = *<a href="ident?i=PKTINFO_SKB_CB">PKTINFO_SKB_CB</a>(<a href="ident?i=skb">skb</a>);
 <a name="L56" href="source/net/ipv4/ip_sockglue.c#L56">56</a> 
 <a name="L57" href="source/net/ipv4/ip_sockglue.c#L57">57</a>         <a href="ident?i=info">info</a>.ipi_addr.s_addr = <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=daddr">daddr</a>;
 <a name="L58" href="source/net/ipv4/ip_sockglue.c#L58">58</a> 
 <a name="L59" href="source/net/ipv4/ip_sockglue.c#L59">59</a>         <a href="ident?i=put_cmsg">put_cmsg</a>(<a href="ident?i=msg">msg</a>, <a href="ident?i=SOL_IP">SOL_IP</a>, <a href="ident?i=IP_PKTINFO">IP_PKTINFO</a>, sizeof(<a href="ident?i=info">info</a>), &amp;<a href="ident?i=info">info</a>);
 <a name="L60" href="source/net/ipv4/ip_sockglue.c#L60">60</a> }
 <a name="L61" href="source/net/ipv4/ip_sockglue.c#L61">61</a> 
 <a name="L62" href="source/net/ipv4/ip_sockglue.c#L62">62</a> static void <a href="ident?i=ip_cmsg_recv_ttl">ip_cmsg_recv_ttl</a>(struct <a href="ident?i=msghdr">msghdr</a> *<a href="ident?i=msg">msg</a>, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
 <a name="L63" href="source/net/ipv4/ip_sockglue.c#L63">63</a> {
 <a name="L64" href="source/net/ipv4/ip_sockglue.c#L64">64</a>         int <a href="ident?i=ttl">ttl</a> = <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=ttl">ttl</a>;
 <a name="L65" href="source/net/ipv4/ip_sockglue.c#L65">65</a>         <a href="ident?i=put_cmsg">put_cmsg</a>(<a href="ident?i=msg">msg</a>, <a href="ident?i=SOL_IP">SOL_IP</a>, <a href="ident?i=IP_TTL">IP_TTL</a>, sizeof(int), &amp;<a href="ident?i=ttl">ttl</a>);
 <a name="L66" href="source/net/ipv4/ip_sockglue.c#L66">66</a> }
 <a name="L67" href="source/net/ipv4/ip_sockglue.c#L67">67</a> 
 <a name="L68" href="source/net/ipv4/ip_sockglue.c#L68">68</a> static void <a href="ident?i=ip_cmsg_recv_tos">ip_cmsg_recv_tos</a>(struct <a href="ident?i=msghdr">msghdr</a> *<a href="ident?i=msg">msg</a>, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
 <a name="L69" href="source/net/ipv4/ip_sockglue.c#L69">69</a> {
 <a name="L70" href="source/net/ipv4/ip_sockglue.c#L70">70</a>         <a href="ident?i=put_cmsg">put_cmsg</a>(<a href="ident?i=msg">msg</a>, <a href="ident?i=SOL_IP">SOL_IP</a>, <a href="ident?i=IP_TOS">IP_TOS</a>, 1, &amp;<a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;tos);
 <a name="L71" href="source/net/ipv4/ip_sockglue.c#L71">71</a> }
 <a name="L72" href="source/net/ipv4/ip_sockglue.c#L72">72</a> 
 <a name="L73" href="source/net/ipv4/ip_sockglue.c#L73">73</a> static void <a href="ident?i=ip_cmsg_recv_opts">ip_cmsg_recv_opts</a>(struct <a href="ident?i=msghdr">msghdr</a> *<a href="ident?i=msg">msg</a>, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
 <a name="L74" href="source/net/ipv4/ip_sockglue.c#L74">74</a> {
 <a name="L75" href="source/net/ipv4/ip_sockglue.c#L75">75</a>         if (<a href="ident?i=IPCB">IPCB</a>(<a href="ident?i=skb">skb</a>)-&gt;opt.<a href="ident?i=optlen">optlen</a> == 0)
 <a name="L76" href="source/net/ipv4/ip_sockglue.c#L76">76</a>                 return;
 <a name="L77" href="source/net/ipv4/ip_sockglue.c#L77">77</a> 
 <a name="L78" href="source/net/ipv4/ip_sockglue.c#L78">78</a>         <a href="ident?i=put_cmsg">put_cmsg</a>(<a href="ident?i=msg">msg</a>, <a href="ident?i=SOL_IP">SOL_IP</a>, <a href="ident?i=IP_RECVOPTS">IP_RECVOPTS</a>, <a href="ident?i=IPCB">IPCB</a>(<a href="ident?i=skb">skb</a>)-&gt;opt.<a href="ident?i=optlen">optlen</a>,
 <a name="L79" href="source/net/ipv4/ip_sockglue.c#L79">79</a>                  <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>) + 1);
 <a name="L80" href="source/net/ipv4/ip_sockglue.c#L80">80</a> }
 <a name="L81" href="source/net/ipv4/ip_sockglue.c#L81">81</a> 
 <a name="L82" href="source/net/ipv4/ip_sockglue.c#L82">82</a> 
 <a name="L83" href="source/net/ipv4/ip_sockglue.c#L83">83</a> static void <a href="ident?i=ip_cmsg_recv_retopts">ip_cmsg_recv_retopts</a>(struct <a href="ident?i=msghdr">msghdr</a> *<a href="ident?i=msg">msg</a>, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
 <a name="L84" href="source/net/ipv4/ip_sockglue.c#L84">84</a> {
 <a name="L85" href="source/net/ipv4/ip_sockglue.c#L85">85</a>         unsigned char optbuf[sizeof(struct <a href="ident?i=ip_options">ip_options</a>) + 40];
 <a name="L86" href="source/net/ipv4/ip_sockglue.c#L86">86</a>         struct <a href="ident?i=ip_options">ip_options</a> *opt = (struct <a href="ident?i=ip_options">ip_options</a> *)optbuf;
 <a name="L87" href="source/net/ipv4/ip_sockglue.c#L87">87</a> 
 <a name="L88" href="source/net/ipv4/ip_sockglue.c#L88">88</a>         if (<a href="ident?i=IPCB">IPCB</a>(<a href="ident?i=skb">skb</a>)-&gt;opt.<a href="ident?i=optlen">optlen</a> == 0)
 <a name="L89" href="source/net/ipv4/ip_sockglue.c#L89">89</a>                 return;
 <a name="L90" href="source/net/ipv4/ip_sockglue.c#L90">90</a> 
 <a name="L91" href="source/net/ipv4/ip_sockglue.c#L91">91</a>         if (<a href="ident?i=ip_options_echo">ip_options_echo</a>(opt, <a href="ident?i=skb">skb</a>)) {
 <a name="L92" href="source/net/ipv4/ip_sockglue.c#L92">92</a>                 <a href="ident?i=msg">msg</a>-&gt;msg_flags |= <a href="ident?i=MSG_CTRUNC">MSG_CTRUNC</a>;
 <a name="L93" href="source/net/ipv4/ip_sockglue.c#L93">93</a>                 return;
 <a name="L94" href="source/net/ipv4/ip_sockglue.c#L94">94</a>         }
 <a name="L95" href="source/net/ipv4/ip_sockglue.c#L95">95</a>         <a href="ident?i=ip_options_undo">ip_options_undo</a>(opt);
 <a name="L96" href="source/net/ipv4/ip_sockglue.c#L96">96</a> 
 <a name="L97" href="source/net/ipv4/ip_sockglue.c#L97">97</a>         <a href="ident?i=put_cmsg">put_cmsg</a>(<a href="ident?i=msg">msg</a>, <a href="ident?i=SOL_IP">SOL_IP</a>, <a href="ident?i=IP_RETOPTS">IP_RETOPTS</a>, opt-&gt;<a href="ident?i=optlen">optlen</a>, opt-&gt;__data);
 <a name="L98" href="source/net/ipv4/ip_sockglue.c#L98">98</a> }
 <a name="L99" href="source/net/ipv4/ip_sockglue.c#L99">99</a> 
<a name="L100" href="source/net/ipv4/ip_sockglue.c#L100">100</a> static void <a href="ident?i=ip_cmsg_recv_checksum">ip_cmsg_recv_checksum</a>(struct <a href="ident?i=msghdr">msghdr</a> *<a href="ident?i=msg">msg</a>, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
<a name="L101" href="source/net/ipv4/ip_sockglue.c#L101">101</a>                                   int <a href="ident?i=offset">offset</a>)
<a name="L102" href="source/net/ipv4/ip_sockglue.c#L102">102</a> {
<a name="L103" href="source/net/ipv4/ip_sockglue.c#L103">103</a>         <a href="ident?i=__wsum">__wsum</a> <a href="ident?i=csum">csum</a> = <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=csum">csum</a>;
<a name="L104" href="source/net/ipv4/ip_sockglue.c#L104">104</a> 
<a name="L105" href="source/net/ipv4/ip_sockglue.c#L105">105</a>         if (<a href="ident?i=skb">skb</a>-&gt;ip_summed != <a href="ident?i=CHECKSUM_COMPLETE">CHECKSUM_COMPLETE</a>)
<a name="L106" href="source/net/ipv4/ip_sockglue.c#L106">106</a>                 return;
<a name="L107" href="source/net/ipv4/ip_sockglue.c#L107">107</a> 
<a name="L108" href="source/net/ipv4/ip_sockglue.c#L108">108</a>         if (<a href="ident?i=offset">offset</a> != 0)
<a name="L109" href="source/net/ipv4/ip_sockglue.c#L109">109</a>                 <a href="ident?i=csum">csum</a> = <a href="ident?i=csum_sub">csum_sub</a>(<a href="ident?i=csum">csum</a>, <a href="ident?i=csum_partial">csum_partial</a>(<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=data">data</a>, <a href="ident?i=offset">offset</a>, 0));
<a name="L110" href="source/net/ipv4/ip_sockglue.c#L110">110</a> 
<a name="L111" href="source/net/ipv4/ip_sockglue.c#L111">111</a>         <a href="ident?i=put_cmsg">put_cmsg</a>(<a href="ident?i=msg">msg</a>, <a href="ident?i=SOL_IP">SOL_IP</a>, <a href="ident?i=IP_CHECKSUM">IP_CHECKSUM</a>, sizeof(<a href="ident?i=__wsum">__wsum</a>), &amp;<a href="ident?i=csum">csum</a>);
<a name="L112" href="source/net/ipv4/ip_sockglue.c#L112">112</a> }
<a name="L113" href="source/net/ipv4/ip_sockglue.c#L113">113</a> 
<a name="L114" href="source/net/ipv4/ip_sockglue.c#L114">114</a> static void <a href="ident?i=ip_cmsg_recv_security">ip_cmsg_recv_security</a>(struct <a href="ident?i=msghdr">msghdr</a> *<a href="ident?i=msg">msg</a>, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L115" href="source/net/ipv4/ip_sockglue.c#L115">115</a> {
<a name="L116" href="source/net/ipv4/ip_sockglue.c#L116">116</a>         char *secdata;
<a name="L117" href="source/net/ipv4/ip_sockglue.c#L117">117</a>         <a href="ident?i=u32">u32</a> seclen, secid;
<a name="L118" href="source/net/ipv4/ip_sockglue.c#L118">118</a>         int <a href="ident?i=err">err</a>;
<a name="L119" href="source/net/ipv4/ip_sockglue.c#L119">119</a> 
<a name="L120" href="source/net/ipv4/ip_sockglue.c#L120">120</a>         <a href="ident?i=err">err</a> = <a href="ident?i=security_socket_getpeersec_dgram">security_socket_getpeersec_dgram</a>(<a href="ident?i=NULL">NULL</a>, <a href="ident?i=skb">skb</a>, &amp;secid);
<a name="L121" href="source/net/ipv4/ip_sockglue.c#L121">121</a>         if (<a href="ident?i=err">err</a>)
<a name="L122" href="source/net/ipv4/ip_sockglue.c#L122">122</a>                 return;
<a name="L123" href="source/net/ipv4/ip_sockglue.c#L123">123</a> 
<a name="L124" href="source/net/ipv4/ip_sockglue.c#L124">124</a>         <a href="ident?i=err">err</a> = <a href="ident?i=security_secid_to_secctx">security_secid_to_secctx</a>(secid, &amp;secdata, &amp;seclen);
<a name="L125" href="source/net/ipv4/ip_sockglue.c#L125">125</a>         if (<a href="ident?i=err">err</a>)
<a name="L126" href="source/net/ipv4/ip_sockglue.c#L126">126</a>                 return;
<a name="L127" href="source/net/ipv4/ip_sockglue.c#L127">127</a> 
<a name="L128" href="source/net/ipv4/ip_sockglue.c#L128">128</a>         <a href="ident?i=put_cmsg">put_cmsg</a>(<a href="ident?i=msg">msg</a>, <a href="ident?i=SOL_IP">SOL_IP</a>, <a href="ident?i=SCM_SECURITY">SCM_SECURITY</a>, seclen, secdata);
<a name="L129" href="source/net/ipv4/ip_sockglue.c#L129">129</a>         <a href="ident?i=security_release_secctx">security_release_secctx</a>(secdata, seclen);
<a name="L130" href="source/net/ipv4/ip_sockglue.c#L130">130</a> }
<a name="L131" href="source/net/ipv4/ip_sockglue.c#L131">131</a> 
<a name="L132" href="source/net/ipv4/ip_sockglue.c#L132">132</a> static void <a href="ident?i=ip_cmsg_recv_dstaddr">ip_cmsg_recv_dstaddr</a>(struct <a href="ident?i=msghdr">msghdr</a> *<a href="ident?i=msg">msg</a>, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L133" href="source/net/ipv4/ip_sockglue.c#L133">133</a> {
<a name="L134" href="source/net/ipv4/ip_sockglue.c#L134">134</a>         struct <a href="ident?i=sockaddr_in">sockaddr_in</a> <a href="ident?i=sin">sin</a>;
<a name="L135" href="source/net/ipv4/ip_sockglue.c#L135">135</a>         const struct <a href="ident?i=iphdr">iphdr</a> *iph = <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>);
<a name="L136" href="source/net/ipv4/ip_sockglue.c#L136">136</a>         <a href="ident?i=__be16">__be16</a> *<a href="ident?i=ports">ports</a> = (<a href="ident?i=__be16">__be16</a> *)<a href="ident?i=skb_transport_header">skb_transport_header</a>(<a href="ident?i=skb">skb</a>);
<a name="L137" href="source/net/ipv4/ip_sockglue.c#L137">137</a> 
<a name="L138" href="source/net/ipv4/ip_sockglue.c#L138">138</a>         if (<a href="ident?i=skb_transport_offset">skb_transport_offset</a>(<a href="ident?i=skb">skb</a>) + 4 &gt; <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a>)
<a name="L139" href="source/net/ipv4/ip_sockglue.c#L139">139</a>                 return;
<a name="L140" href="source/net/ipv4/ip_sockglue.c#L140">140</a> 
<a name="L141" href="source/net/ipv4/ip_sockglue.c#L141">141</a>         <b><i>/* All current transport protocols have the port numbers in the</i></b>
<a name="L142" href="source/net/ipv4/ip_sockglue.c#L142">142</a> <b><i>         * first four bytes of the transport header and this function is</i></b>
<a name="L143" href="source/net/ipv4/ip_sockglue.c#L143">143</a> <b><i>         * written with this assumption in mind.</i></b>
<a name="L144" href="source/net/ipv4/ip_sockglue.c#L144">144</a> <b><i>         */</i></b>
<a name="L145" href="source/net/ipv4/ip_sockglue.c#L145">145</a> 
<a name="L146" href="source/net/ipv4/ip_sockglue.c#L146">146</a>         <a href="ident?i=sin">sin</a>.sin_family = <a href="ident?i=AF_INET">AF_INET</a>;
<a name="L147" href="source/net/ipv4/ip_sockglue.c#L147">147</a>         <a href="ident?i=sin">sin</a>.sin_addr.s_addr = iph-&gt;<a href="ident?i=daddr">daddr</a>;
<a name="L148" href="source/net/ipv4/ip_sockglue.c#L148">148</a>         <a href="ident?i=sin">sin</a>.sin_port = <a href="ident?i=ports">ports</a>[1];
<a name="L149" href="source/net/ipv4/ip_sockglue.c#L149">149</a>         <a href="ident?i=memset">memset</a>(<a href="ident?i=sin">sin</a>.<a href="ident?i=sin_zero">sin_zero</a>, 0, sizeof(<a href="ident?i=sin">sin</a>.<a href="ident?i=sin_zero">sin_zero</a>));
<a name="L150" href="source/net/ipv4/ip_sockglue.c#L150">150</a> 
<a name="L151" href="source/net/ipv4/ip_sockglue.c#L151">151</a>         <a href="ident?i=put_cmsg">put_cmsg</a>(<a href="ident?i=msg">msg</a>, <a href="ident?i=SOL_IP">SOL_IP</a>, <a href="ident?i=IP_ORIGDSTADDR">IP_ORIGDSTADDR</a>, sizeof(<a href="ident?i=sin">sin</a>), &amp;<a href="ident?i=sin">sin</a>);
<a name="L152" href="source/net/ipv4/ip_sockglue.c#L152">152</a> }
<a name="L153" href="source/net/ipv4/ip_sockglue.c#L153">153</a> 
<a name="L154" href="source/net/ipv4/ip_sockglue.c#L154">154</a> void <a href="ident?i=ip_cmsg_recv_offset">ip_cmsg_recv_offset</a>(struct <a href="ident?i=msghdr">msghdr</a> *<a href="ident?i=msg">msg</a>, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
<a name="L155" href="source/net/ipv4/ip_sockglue.c#L155">155</a>                          int <a href="ident?i=offset">offset</a>)
<a name="L156" href="source/net/ipv4/ip_sockglue.c#L156">156</a> {
<a name="L157" href="source/net/ipv4/ip_sockglue.c#L157">157</a>         struct <a href="ident?i=inet_sock">inet_sock</a> *inet = <a href="ident?i=inet_sk">inet_sk</a>(<a href="ident?i=skb">skb</a>-&gt;sk);
<a name="L158" href="source/net/ipv4/ip_sockglue.c#L158">158</a>         unsigned int <a href="ident?i=flags">flags</a> = inet-&gt;cmsg_flags;
<a name="L159" href="source/net/ipv4/ip_sockglue.c#L159">159</a> 
<a name="L160" href="source/net/ipv4/ip_sockglue.c#L160">160</a>         <b><i>/* Ordered by supposed usage frequency */</i></b>
<a name="L161" href="source/net/ipv4/ip_sockglue.c#L161">161</a>         if (<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=IP_CMSG_PKTINFO">IP_CMSG_PKTINFO</a>) {
<a name="L162" href="source/net/ipv4/ip_sockglue.c#L162">162</a>                 <a href="ident?i=ip_cmsg_recv_pktinfo">ip_cmsg_recv_pktinfo</a>(<a href="ident?i=msg">msg</a>, <a href="ident?i=skb">skb</a>);
<a name="L163" href="source/net/ipv4/ip_sockglue.c#L163">163</a> 
<a name="L164" href="source/net/ipv4/ip_sockglue.c#L164">164</a>                 <a href="ident?i=flags">flags</a> &amp;= ~IP_CMSG_PKTINFO;
<a name="L165" href="source/net/ipv4/ip_sockglue.c#L165">165</a>                 if (!<a href="ident?i=flags">flags</a>)
<a name="L166" href="source/net/ipv4/ip_sockglue.c#L166">166</a>                         return;
<a name="L167" href="source/net/ipv4/ip_sockglue.c#L167">167</a>         }
<a name="L168" href="source/net/ipv4/ip_sockglue.c#L168">168</a> 
<a name="L169" href="source/net/ipv4/ip_sockglue.c#L169">169</a>         if (<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=IP_CMSG_TTL">IP_CMSG_TTL</a>) {
<a name="L170" href="source/net/ipv4/ip_sockglue.c#L170">170</a>                 <a href="ident?i=ip_cmsg_recv_ttl">ip_cmsg_recv_ttl</a>(<a href="ident?i=msg">msg</a>, <a href="ident?i=skb">skb</a>);
<a name="L171" href="source/net/ipv4/ip_sockglue.c#L171">171</a> 
<a name="L172" href="source/net/ipv4/ip_sockglue.c#L172">172</a>                 <a href="ident?i=flags">flags</a> &amp;= ~IP_CMSG_TTL;
<a name="L173" href="source/net/ipv4/ip_sockglue.c#L173">173</a>                 if (!<a href="ident?i=flags">flags</a>)
<a name="L174" href="source/net/ipv4/ip_sockglue.c#L174">174</a>                         return;
<a name="L175" href="source/net/ipv4/ip_sockglue.c#L175">175</a>         }
<a name="L176" href="source/net/ipv4/ip_sockglue.c#L176">176</a> 
<a name="L177" href="source/net/ipv4/ip_sockglue.c#L177">177</a>         if (<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=IP_CMSG_TOS">IP_CMSG_TOS</a>) {
<a name="L178" href="source/net/ipv4/ip_sockglue.c#L178">178</a>                 <a href="ident?i=ip_cmsg_recv_tos">ip_cmsg_recv_tos</a>(<a href="ident?i=msg">msg</a>, <a href="ident?i=skb">skb</a>);
<a name="L179" href="source/net/ipv4/ip_sockglue.c#L179">179</a> 
<a name="L180" href="source/net/ipv4/ip_sockglue.c#L180">180</a>                 <a href="ident?i=flags">flags</a> &amp;= ~IP_CMSG_TOS;
<a name="L181" href="source/net/ipv4/ip_sockglue.c#L181">181</a>                 if (!<a href="ident?i=flags">flags</a>)
<a name="L182" href="source/net/ipv4/ip_sockglue.c#L182">182</a>                         return;
<a name="L183" href="source/net/ipv4/ip_sockglue.c#L183">183</a>         }
<a name="L184" href="source/net/ipv4/ip_sockglue.c#L184">184</a> 
<a name="L185" href="source/net/ipv4/ip_sockglue.c#L185">185</a>         if (<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=IP_CMSG_RECVOPTS">IP_CMSG_RECVOPTS</a>) {
<a name="L186" href="source/net/ipv4/ip_sockglue.c#L186">186</a>                 <a href="ident?i=ip_cmsg_recv_opts">ip_cmsg_recv_opts</a>(<a href="ident?i=msg">msg</a>, <a href="ident?i=skb">skb</a>);
<a name="L187" href="source/net/ipv4/ip_sockglue.c#L187">187</a> 
<a name="L188" href="source/net/ipv4/ip_sockglue.c#L188">188</a>                 <a href="ident?i=flags">flags</a> &amp;= ~IP_CMSG_RECVOPTS;
<a name="L189" href="source/net/ipv4/ip_sockglue.c#L189">189</a>                 if (!<a href="ident?i=flags">flags</a>)
<a name="L190" href="source/net/ipv4/ip_sockglue.c#L190">190</a>                         return;
<a name="L191" href="source/net/ipv4/ip_sockglue.c#L191">191</a>         }
<a name="L192" href="source/net/ipv4/ip_sockglue.c#L192">192</a> 
<a name="L193" href="source/net/ipv4/ip_sockglue.c#L193">193</a>         if (<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=IP_CMSG_RETOPTS">IP_CMSG_RETOPTS</a>) {
<a name="L194" href="source/net/ipv4/ip_sockglue.c#L194">194</a>                 <a href="ident?i=ip_cmsg_recv_retopts">ip_cmsg_recv_retopts</a>(<a href="ident?i=msg">msg</a>, <a href="ident?i=skb">skb</a>);
<a name="L195" href="source/net/ipv4/ip_sockglue.c#L195">195</a> 
<a name="L196" href="source/net/ipv4/ip_sockglue.c#L196">196</a>                 <a href="ident?i=flags">flags</a> &amp;= ~IP_CMSG_RETOPTS;
<a name="L197" href="source/net/ipv4/ip_sockglue.c#L197">197</a>                 if (!<a href="ident?i=flags">flags</a>)
<a name="L198" href="source/net/ipv4/ip_sockglue.c#L198">198</a>                         return;
<a name="L199" href="source/net/ipv4/ip_sockglue.c#L199">199</a>         }
<a name="L200" href="source/net/ipv4/ip_sockglue.c#L200">200</a> 
<a name="L201" href="source/net/ipv4/ip_sockglue.c#L201">201</a>         if (<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=IP_CMSG_PASSSEC">IP_CMSG_PASSSEC</a>) {
<a name="L202" href="source/net/ipv4/ip_sockglue.c#L202">202</a>                 <a href="ident?i=ip_cmsg_recv_security">ip_cmsg_recv_security</a>(<a href="ident?i=msg">msg</a>, <a href="ident?i=skb">skb</a>);
<a name="L203" href="source/net/ipv4/ip_sockglue.c#L203">203</a> 
<a name="L204" href="source/net/ipv4/ip_sockglue.c#L204">204</a>                 <a href="ident?i=flags">flags</a> &amp;= ~IP_CMSG_PASSSEC;
<a name="L205" href="source/net/ipv4/ip_sockglue.c#L205">205</a>                 if (!<a href="ident?i=flags">flags</a>)
<a name="L206" href="source/net/ipv4/ip_sockglue.c#L206">206</a>                         return;
<a name="L207" href="source/net/ipv4/ip_sockglue.c#L207">207</a>         }
<a name="L208" href="source/net/ipv4/ip_sockglue.c#L208">208</a> 
<a name="L209" href="source/net/ipv4/ip_sockglue.c#L209">209</a>         if (<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=IP_CMSG_ORIGDSTADDR">IP_CMSG_ORIGDSTADDR</a>) {
<a name="L210" href="source/net/ipv4/ip_sockglue.c#L210">210</a>                 <a href="ident?i=ip_cmsg_recv_dstaddr">ip_cmsg_recv_dstaddr</a>(<a href="ident?i=msg">msg</a>, <a href="ident?i=skb">skb</a>);
<a name="L211" href="source/net/ipv4/ip_sockglue.c#L211">211</a> 
<a name="L212" href="source/net/ipv4/ip_sockglue.c#L212">212</a>                 <a href="ident?i=flags">flags</a> &amp;= ~IP_CMSG_ORIGDSTADDR;
<a name="L213" href="source/net/ipv4/ip_sockglue.c#L213">213</a>                 if (!<a href="ident?i=flags">flags</a>)
<a name="L214" href="source/net/ipv4/ip_sockglue.c#L214">214</a>                         return;
<a name="L215" href="source/net/ipv4/ip_sockglue.c#L215">215</a>         }
<a name="L216" href="source/net/ipv4/ip_sockglue.c#L216">216</a> 
<a name="L217" href="source/net/ipv4/ip_sockglue.c#L217">217</a>         if (<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=IP_CMSG_CHECKSUM">IP_CMSG_CHECKSUM</a>)
<a name="L218" href="source/net/ipv4/ip_sockglue.c#L218">218</a>                 <a href="ident?i=ip_cmsg_recv_checksum">ip_cmsg_recv_checksum</a>(<a href="ident?i=msg">msg</a>, <a href="ident?i=skb">skb</a>, <a href="ident?i=offset">offset</a>);
<a name="L219" href="source/net/ipv4/ip_sockglue.c#L219">219</a> }
<a name="L220" href="source/net/ipv4/ip_sockglue.c#L220">220</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=ip_cmsg_recv_offset">ip_cmsg_recv_offset</a>);
<a name="L221" href="source/net/ipv4/ip_sockglue.c#L221">221</a> 
<a name="L222" href="source/net/ipv4/ip_sockglue.c#L222">222</a> int <a href="ident?i=ip_cmsg_send">ip_cmsg_send</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>, struct <a href="ident?i=msghdr">msghdr</a> *<a href="ident?i=msg">msg</a>, struct <a href="ident?i=ipcm_cookie">ipcm_cookie</a> *ipc,
<a name="L223" href="source/net/ipv4/ip_sockglue.c#L223">223</a>                  <a href="ident?i=bool">bool</a> allow_ipv6)
<a name="L224" href="source/net/ipv4/ip_sockglue.c#L224">224</a> {
<a name="L225" href="source/net/ipv4/ip_sockglue.c#L225">225</a>         int <a href="ident?i=err">err</a>, <a href="ident?i=val">val</a>;
<a name="L226" href="source/net/ipv4/ip_sockglue.c#L226">226</a>         struct <a href="ident?i=cmsghdr">cmsghdr</a> *<a href="ident?i=cmsg">cmsg</a>;
<a name="L227" href="source/net/ipv4/ip_sockglue.c#L227">227</a> 
<a name="L228" href="source/net/ipv4/ip_sockglue.c#L228">228</a>         <a href="ident?i=for_each_cmsghdr">for_each_cmsghdr</a>(<a href="ident?i=cmsg">cmsg</a>, <a href="ident?i=msg">msg</a>) {
<a name="L229" href="source/net/ipv4/ip_sockglue.c#L229">229</a>                 if (!<a href="ident?i=CMSG_OK">CMSG_OK</a>(<a href="ident?i=msg">msg</a>, <a href="ident?i=cmsg">cmsg</a>))
<a name="L230" href="source/net/ipv4/ip_sockglue.c#L230">230</a>                         return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L231" href="source/net/ipv4/ip_sockglue.c#L231">231</a> #if <a href="ident?i=IS_ENABLED">IS_ENABLED</a>(CONFIG_IPV6)
<a name="L232" href="source/net/ipv4/ip_sockglue.c#L232">232</a>                 if (allow_ipv6 &amp;&amp;
<a name="L233" href="source/net/ipv4/ip_sockglue.c#L233">233</a>                     <a href="ident?i=cmsg">cmsg</a>-&gt;cmsg_level == <a href="ident?i=SOL_IPV6">SOL_IPV6</a> &amp;&amp;
<a name="L234" href="source/net/ipv4/ip_sockglue.c#L234">234</a>                     <a href="ident?i=cmsg">cmsg</a>-&gt;cmsg_type == <a href="ident?i=IPV6_PKTINFO">IPV6_PKTINFO</a>) {
<a name="L235" href="source/net/ipv4/ip_sockglue.c#L235">235</a>                         struct <a href="ident?i=in6_pktinfo">in6_pktinfo</a> *src_info;
<a name="L236" href="source/net/ipv4/ip_sockglue.c#L236">236</a> 
<a name="L237" href="source/net/ipv4/ip_sockglue.c#L237">237</a>                         if (<a href="ident?i=cmsg">cmsg</a>-&gt;cmsg_len &lt; <a href="ident?i=CMSG_LEN">CMSG_LEN</a>(sizeof(*src_info)))
<a name="L238" href="source/net/ipv4/ip_sockglue.c#L238">238</a>                                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L239" href="source/net/ipv4/ip_sockglue.c#L239">239</a>                         src_info = (struct <a href="ident?i=in6_pktinfo">in6_pktinfo</a> *)<a href="ident?i=CMSG_DATA">CMSG_DATA</a>(<a href="ident?i=cmsg">cmsg</a>);
<a name="L240" href="source/net/ipv4/ip_sockglue.c#L240">240</a>                         if (!<a href="ident?i=ipv6_addr_v4mapped">ipv6_addr_v4mapped</a>(&amp;src_info-&gt;ipi6_addr))
<a name="L241" href="source/net/ipv4/ip_sockglue.c#L241">241</a>                                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L242" href="source/net/ipv4/ip_sockglue.c#L242">242</a>                         ipc-&gt;oif = src_info-&gt;ipi6_ifindex;
<a name="L243" href="source/net/ipv4/ip_sockglue.c#L243">243</a>                         ipc-&gt;<a href="ident?i=addr">addr</a> = src_info-&gt;ipi6_addr.<a href="ident?i=s6_addr32">s6_addr32</a>[3];
<a name="L244" href="source/net/ipv4/ip_sockglue.c#L244">244</a>                         continue;
<a name="L245" href="source/net/ipv4/ip_sockglue.c#L245">245</a>                 }
<a name="L246" href="source/net/ipv4/ip_sockglue.c#L246">246</a> #endif
<a name="L247" href="source/net/ipv4/ip_sockglue.c#L247">247</a>                 if (<a href="ident?i=cmsg">cmsg</a>-&gt;cmsg_level != <a href="ident?i=SOL_IP">SOL_IP</a>)
<a name="L248" href="source/net/ipv4/ip_sockglue.c#L248">248</a>                         continue;
<a name="L249" href="source/net/ipv4/ip_sockglue.c#L249">249</a>                 switch (<a href="ident?i=cmsg">cmsg</a>-&gt;cmsg_type) {
<a name="L250" href="source/net/ipv4/ip_sockglue.c#L250">250</a>                 case <a href="ident?i=IP_RETOPTS">IP_RETOPTS</a>:
<a name="L251" href="source/net/ipv4/ip_sockglue.c#L251">251</a>                         <a href="ident?i=err">err</a> = <a href="ident?i=cmsg">cmsg</a>-&gt;cmsg_len - <a href="ident?i=CMSG_ALIGN">CMSG_ALIGN</a>(sizeof(struct <a href="ident?i=cmsghdr">cmsghdr</a>));
<a name="L252" href="source/net/ipv4/ip_sockglue.c#L252">252</a>                         <a href="ident?i=err">err</a> = <a href="ident?i=ip_options_get">ip_options_get</a>(<a href="ident?i=net">net</a>, &amp;ipc-&gt;opt, <a href="ident?i=CMSG_DATA">CMSG_DATA</a>(<a href="ident?i=cmsg">cmsg</a>),
<a name="L253" href="source/net/ipv4/ip_sockglue.c#L253">253</a>                                              <a href="ident?i=err">err</a> &lt; 40 ? <a href="ident?i=err">err</a> : 40);
<a name="L254" href="source/net/ipv4/ip_sockglue.c#L254">254</a>                         if (<a href="ident?i=err">err</a>)
<a name="L255" href="source/net/ipv4/ip_sockglue.c#L255">255</a>                                 return <a href="ident?i=err">err</a>;
<a name="L256" href="source/net/ipv4/ip_sockglue.c#L256">256</a>                         break;
<a name="L257" href="source/net/ipv4/ip_sockglue.c#L257">257</a>                 case <a href="ident?i=IP_PKTINFO">IP_PKTINFO</a>:
<a name="L258" href="source/net/ipv4/ip_sockglue.c#L258">258</a>                 {
<a name="L259" href="source/net/ipv4/ip_sockglue.c#L259">259</a>                         struct <a href="ident?i=in_pktinfo">in_pktinfo</a> *<a href="ident?i=info">info</a>;
<a name="L260" href="source/net/ipv4/ip_sockglue.c#L260">260</a>                         if (<a href="ident?i=cmsg">cmsg</a>-&gt;cmsg_len != <a href="ident?i=CMSG_LEN">CMSG_LEN</a>(sizeof(struct <a href="ident?i=in_pktinfo">in_pktinfo</a>)))
<a name="L261" href="source/net/ipv4/ip_sockglue.c#L261">261</a>                                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L262" href="source/net/ipv4/ip_sockglue.c#L262">262</a>                         <a href="ident?i=info">info</a> = (struct <a href="ident?i=in_pktinfo">in_pktinfo</a> *)<a href="ident?i=CMSG_DATA">CMSG_DATA</a>(<a href="ident?i=cmsg">cmsg</a>);
<a name="L263" href="source/net/ipv4/ip_sockglue.c#L263">263</a>                         ipc-&gt;oif = <a href="ident?i=info">info</a>-&gt;ipi_ifindex;
<a name="L264" href="source/net/ipv4/ip_sockglue.c#L264">264</a>                         ipc-&gt;<a href="ident?i=addr">addr</a> = <a href="ident?i=info">info</a>-&gt;ipi_spec_dst.s_addr;
<a name="L265" href="source/net/ipv4/ip_sockglue.c#L265">265</a>                         break;
<a name="L266" href="source/net/ipv4/ip_sockglue.c#L266">266</a>                 }
<a name="L267" href="source/net/ipv4/ip_sockglue.c#L267">267</a>                 case <a href="ident?i=IP_TTL">IP_TTL</a>:
<a name="L268" href="source/net/ipv4/ip_sockglue.c#L268">268</a>                         if (<a href="ident?i=cmsg">cmsg</a>-&gt;cmsg_len != <a href="ident?i=CMSG_LEN">CMSG_LEN</a>(sizeof(int)))
<a name="L269" href="source/net/ipv4/ip_sockglue.c#L269">269</a>                                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L270" href="source/net/ipv4/ip_sockglue.c#L270">270</a>                         <a href="ident?i=val">val</a> = *(int *)<a href="ident?i=CMSG_DATA">CMSG_DATA</a>(<a href="ident?i=cmsg">cmsg</a>);
<a name="L271" href="source/net/ipv4/ip_sockglue.c#L271">271</a>                         if (<a href="ident?i=val">val</a> &lt; 1 || <a href="ident?i=val">val</a> &gt; 255)
<a name="L272" href="source/net/ipv4/ip_sockglue.c#L272">272</a>                                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L273" href="source/net/ipv4/ip_sockglue.c#L273">273</a>                         ipc-&gt;<a href="ident?i=ttl">ttl</a> = <a href="ident?i=val">val</a>;
<a name="L274" href="source/net/ipv4/ip_sockglue.c#L274">274</a>                         break;
<a name="L275" href="source/net/ipv4/ip_sockglue.c#L275">275</a>                 case <a href="ident?i=IP_TOS">IP_TOS</a>:
<a name="L276" href="source/net/ipv4/ip_sockglue.c#L276">276</a>                         if (<a href="ident?i=cmsg">cmsg</a>-&gt;cmsg_len != <a href="ident?i=CMSG_LEN">CMSG_LEN</a>(sizeof(int)))
<a name="L277" href="source/net/ipv4/ip_sockglue.c#L277">277</a>                                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L278" href="source/net/ipv4/ip_sockglue.c#L278">278</a>                         <a href="ident?i=val">val</a> = *(int *)<a href="ident?i=CMSG_DATA">CMSG_DATA</a>(<a href="ident?i=cmsg">cmsg</a>);
<a name="L279" href="source/net/ipv4/ip_sockglue.c#L279">279</a>                         if (<a href="ident?i=val">val</a> &lt; 0 || <a href="ident?i=val">val</a> &gt; 255)
<a name="L280" href="source/net/ipv4/ip_sockglue.c#L280">280</a>                                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L281" href="source/net/ipv4/ip_sockglue.c#L281">281</a>                         ipc-&gt;tos = <a href="ident?i=val">val</a>;
<a name="L282" href="source/net/ipv4/ip_sockglue.c#L282">282</a>                         ipc-&gt;<a href="ident?i=priority">priority</a> = <a href="ident?i=rt_tos2priority">rt_tos2priority</a>(ipc-&gt;tos);
<a name="L283" href="source/net/ipv4/ip_sockglue.c#L283">283</a>                         break;
<a name="L284" href="source/net/ipv4/ip_sockglue.c#L284">284</a> 
<a name="L285" href="source/net/ipv4/ip_sockglue.c#L285">285</a>                 default:
<a name="L286" href="source/net/ipv4/ip_sockglue.c#L286">286</a>                         return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L287" href="source/net/ipv4/ip_sockglue.c#L287">287</a>                 }
<a name="L288" href="source/net/ipv4/ip_sockglue.c#L288">288</a>         }
<a name="L289" href="source/net/ipv4/ip_sockglue.c#L289">289</a>         return 0;
<a name="L290" href="source/net/ipv4/ip_sockglue.c#L290">290</a> }
<a name="L291" href="source/net/ipv4/ip_sockglue.c#L291">291</a> 
<a name="L292" href="source/net/ipv4/ip_sockglue.c#L292">292</a> 
<a name="L293" href="source/net/ipv4/ip_sockglue.c#L293">293</a> <b><i>/* Special input handler for packets caught by router alert option.</i></b>
<a name="L294" href="source/net/ipv4/ip_sockglue.c#L294">294</a> <b><i>   They are selected only by protocol field, and then processed likely</i></b>
<a name="L295" href="source/net/ipv4/ip_sockglue.c#L295">295</a> <b><i>   local ones; but only if someone wants them! Otherwise, router</i></b>
<a name="L296" href="source/net/ipv4/ip_sockglue.c#L296">296</a> <b><i>   not running rsvpd will kill RSVP.</i></b>
<a name="L297" href="source/net/ipv4/ip_sockglue.c#L297">297</a> <b><i></i></b>
<a name="L298" href="source/net/ipv4/ip_sockglue.c#L298">298</a> <b><i>   It is user level problem, what it will make with them.</i></b>
<a name="L299" href="source/net/ipv4/ip_sockglue.c#L299">299</a> <b><i>   I have no idea, how it will masquearde or NAT them (it is joke, joke :-)),</i></b>
<a name="L300" href="source/net/ipv4/ip_sockglue.c#L300">300</a> <b><i>   but receiver should be enough clever f.e. to forward mtrace requests,</i></b>
<a name="L301" href="source/net/ipv4/ip_sockglue.c#L301">301</a> <b><i>   sent to multicast group to reach destination designated router.</i></b>
<a name="L302" href="source/net/ipv4/ip_sockglue.c#L302">302</a> <b><i> */</i></b>
<a name="L303" href="source/net/ipv4/ip_sockglue.c#L303">303</a> struct <a href="ident?i=ip_ra_chain">ip_ra_chain</a> <a href="ident?i=__rcu">__rcu</a> *<a href="ident?i=ip_ra_chain">ip_ra_chain</a>;
<a name="L304" href="source/net/ipv4/ip_sockglue.c#L304">304</a> static <a href="ident?i=DEFINE_SPINLOCK">DEFINE_SPINLOCK</a>(ip_ra_lock);
<a name="L305" href="source/net/ipv4/ip_sockglue.c#L305">305</a> 
<a name="L306" href="source/net/ipv4/ip_sockglue.c#L306">306</a> 
<a name="L307" href="source/net/ipv4/ip_sockglue.c#L307">307</a> static void <a href="ident?i=ip_ra_destroy_rcu">ip_ra_destroy_rcu</a>(struct <a href="ident?i=rcu_head">rcu_head</a> *<a href="ident?i=head">head</a>)
<a name="L308" href="source/net/ipv4/ip_sockglue.c#L308">308</a> {
<a name="L309" href="source/net/ipv4/ip_sockglue.c#L309">309</a>         struct <a href="ident?i=ip_ra_chain">ip_ra_chain</a> *<a href="ident?i=ra">ra</a> = <a href="ident?i=container_of">container_of</a>(<a href="ident?i=head">head</a>, struct <a href="ident?i=ip_ra_chain">ip_ra_chain</a>, rcu);
<a name="L310" href="source/net/ipv4/ip_sockglue.c#L310">310</a> 
<a name="L311" href="source/net/ipv4/ip_sockglue.c#L311">311</a>         <a href="ident?i=sock_put">sock_put</a>(<a href="ident?i=ra">ra</a>-&gt;saved_sk);
<a name="L312" href="source/net/ipv4/ip_sockglue.c#L312">312</a>         <a href="ident?i=kfree">kfree</a>(<a href="ident?i=ra">ra</a>);
<a name="L313" href="source/net/ipv4/ip_sockglue.c#L313">313</a> }
<a name="L314" href="source/net/ipv4/ip_sockglue.c#L314">314</a> 
<a name="L315" href="source/net/ipv4/ip_sockglue.c#L315">315</a> int <a href="ident?i=ip_ra_control">ip_ra_control</a>(struct <a href="ident?i=sock">sock</a> *sk, unsigned char <a href="ident?i=on">on</a>,
<a name="L316" href="source/net/ipv4/ip_sockglue.c#L316">316</a>                   void (*destructor)(struct <a href="ident?i=sock">sock</a> *))
<a name="L317" href="source/net/ipv4/ip_sockglue.c#L317">317</a> {
<a name="L318" href="source/net/ipv4/ip_sockglue.c#L318">318</a>         struct <a href="ident?i=ip_ra_chain">ip_ra_chain</a> *<a href="ident?i=ra">ra</a>, *new_ra;
<a name="L319" href="source/net/ipv4/ip_sockglue.c#L319">319</a>         struct <a href="ident?i=ip_ra_chain">ip_ra_chain</a> <a href="ident?i=__rcu">__rcu</a> **<a href="ident?i=rap">rap</a>;
<a name="L320" href="source/net/ipv4/ip_sockglue.c#L320">320</a> 
<a name="L321" href="source/net/ipv4/ip_sockglue.c#L321">321</a>         if (sk-&gt;sk_type != SOCK_RAW || <a href="ident?i=inet_sk">inet_sk</a>(sk)-&gt;<a href="ident?i=inet_num">inet_num</a> == <a href="ident?i=IPPROTO_RAW">IPPROTO_RAW</a>)
<a name="L322" href="source/net/ipv4/ip_sockglue.c#L322">322</a>                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L323" href="source/net/ipv4/ip_sockglue.c#L323">323</a> 
<a name="L324" href="source/net/ipv4/ip_sockglue.c#L324">324</a>         new_ra = <a href="ident?i=on">on</a> ? <a href="ident?i=kmalloc">kmalloc</a>(sizeof(*new_ra), <a href="ident?i=GFP_KERNEL">GFP_KERNEL</a>) : <a href="ident?i=NULL">NULL</a>;
<a name="L325" href="source/net/ipv4/ip_sockglue.c#L325">325</a> 
<a name="L326" href="source/net/ipv4/ip_sockglue.c#L326">326</a>         <a href="ident?i=spin_lock_bh">spin_lock_bh</a>(&amp;ip_ra_lock);
<a name="L327" href="source/net/ipv4/ip_sockglue.c#L327">327</a>         for (<a href="ident?i=rap">rap</a> = &amp;<a href="ident?i=ip_ra_chain">ip_ra_chain</a>;
<a name="L328" href="source/net/ipv4/ip_sockglue.c#L328">328</a>              (<a href="ident?i=ra">ra</a> = <a href="ident?i=rcu_dereference_protected">rcu_dereference_protected</a>(*<a href="ident?i=rap">rap</a>,
<a name="L329" href="source/net/ipv4/ip_sockglue.c#L329">329</a>                         <a href="ident?i=lockdep_is_held">lockdep_is_held</a>(&amp;ip_ra_lock))) != <a href="ident?i=NULL">NULL</a>;
<a name="L330" href="source/net/ipv4/ip_sockglue.c#L330">330</a>              <a href="ident?i=rap">rap</a> = &amp;<a href="ident?i=ra">ra</a>-&gt;<a href="ident?i=next">next</a>) {
<a name="L331" href="source/net/ipv4/ip_sockglue.c#L331">331</a>                 if (<a href="ident?i=ra">ra</a>-&gt;sk == sk) {
<a name="L332" href="source/net/ipv4/ip_sockglue.c#L332">332</a>                         if (<a href="ident?i=on">on</a>) {
<a name="L333" href="source/net/ipv4/ip_sockglue.c#L333">333</a>                                 <a href="ident?i=spin_unlock_bh">spin_unlock_bh</a>(&amp;ip_ra_lock);
<a name="L334" href="source/net/ipv4/ip_sockglue.c#L334">334</a>                                 <a href="ident?i=kfree">kfree</a>(new_ra);
<a name="L335" href="source/net/ipv4/ip_sockglue.c#L335">335</a>                                 return -<a href="ident?i=EADDRINUSE">EADDRINUSE</a>;
<a name="L336" href="source/net/ipv4/ip_sockglue.c#L336">336</a>                         }
<a name="L337" href="source/net/ipv4/ip_sockglue.c#L337">337</a>                         <b><i>/* dont let ip_call_ra_chain() use sk again */</i></b>
<a name="L338" href="source/net/ipv4/ip_sockglue.c#L338">338</a>                         <a href="ident?i=ra">ra</a>-&gt;sk = <a href="ident?i=NULL">NULL</a>;
<a name="L339" href="source/net/ipv4/ip_sockglue.c#L339">339</a>                         <a href="ident?i=RCU_INIT_POINTER">RCU_INIT_POINTER</a>(*<a href="ident?i=rap">rap</a>, <a href="ident?i=ra">ra</a>-&gt;<a href="ident?i=next">next</a>);
<a name="L340" href="source/net/ipv4/ip_sockglue.c#L340">340</a>                         <a href="ident?i=spin_unlock_bh">spin_unlock_bh</a>(&amp;ip_ra_lock);
<a name="L341" href="source/net/ipv4/ip_sockglue.c#L341">341</a> 
<a name="L342" href="source/net/ipv4/ip_sockglue.c#L342">342</a>                         if (<a href="ident?i=ra">ra</a>-&gt;destructor)
<a name="L343" href="source/net/ipv4/ip_sockglue.c#L343">343</a>                                 <a href="ident?i=ra">ra</a>-&gt;destructor(sk);
<a name="L344" href="source/net/ipv4/ip_sockglue.c#L344">344</a>                         <b><i>/*</i></b>
<a name="L345" href="source/net/ipv4/ip_sockglue.c#L345">345</a> <b><i>                         * Delay sock_put(sk) and kfree(ra) after one rcu grace</i></b>
<a name="L346" href="source/net/ipv4/ip_sockglue.c#L346">346</a> <b><i>                         * period. This guarantee ip_call_ra_chain() dont need</i></b>
<a name="L347" href="source/net/ipv4/ip_sockglue.c#L347">347</a> <b><i>                         * to mess with socket refcounts.</i></b>
<a name="L348" href="source/net/ipv4/ip_sockglue.c#L348">348</a> <b><i>                         */</i></b>
<a name="L349" href="source/net/ipv4/ip_sockglue.c#L349">349</a>                         <a href="ident?i=ra">ra</a>-&gt;saved_sk = sk;
<a name="L350" href="source/net/ipv4/ip_sockglue.c#L350">350</a>                         <a href="ident?i=call_rcu">call_rcu</a>(&amp;<a href="ident?i=ra">ra</a>-&gt;rcu, <a href="ident?i=ip_ra_destroy_rcu">ip_ra_destroy_rcu</a>);
<a name="L351" href="source/net/ipv4/ip_sockglue.c#L351">351</a>                         return 0;
<a name="L352" href="source/net/ipv4/ip_sockglue.c#L352">352</a>                 }
<a name="L353" href="source/net/ipv4/ip_sockglue.c#L353">353</a>         }
<a name="L354" href="source/net/ipv4/ip_sockglue.c#L354">354</a>         if (!new_ra) {
<a name="L355" href="source/net/ipv4/ip_sockglue.c#L355">355</a>                 <a href="ident?i=spin_unlock_bh">spin_unlock_bh</a>(&amp;ip_ra_lock);
<a name="L356" href="source/net/ipv4/ip_sockglue.c#L356">356</a>                 return -<a href="ident?i=ENOBUFS">ENOBUFS</a>;
<a name="L357" href="source/net/ipv4/ip_sockglue.c#L357">357</a>         }
<a name="L358" href="source/net/ipv4/ip_sockglue.c#L358">358</a>         new_ra-&gt;sk = sk;
<a name="L359" href="source/net/ipv4/ip_sockglue.c#L359">359</a>         new_ra-&gt;destructor = destructor;
<a name="L360" href="source/net/ipv4/ip_sockglue.c#L360">360</a> 
<a name="L361" href="source/net/ipv4/ip_sockglue.c#L361">361</a>         <a href="ident?i=RCU_INIT_POINTER">RCU_INIT_POINTER</a>(new_ra-&gt;<a href="ident?i=next">next</a>, <a href="ident?i=ra">ra</a>);
<a name="L362" href="source/net/ipv4/ip_sockglue.c#L362">362</a>         <a href="ident?i=rcu_assign_pointer">rcu_assign_pointer</a>(*<a href="ident?i=rap">rap</a>, new_ra);
<a name="L363" href="source/net/ipv4/ip_sockglue.c#L363">363</a>         <a href="ident?i=sock_hold">sock_hold</a>(sk);
<a name="L364" href="source/net/ipv4/ip_sockglue.c#L364">364</a>         <a href="ident?i=spin_unlock_bh">spin_unlock_bh</a>(&amp;ip_ra_lock);
<a name="L365" href="source/net/ipv4/ip_sockglue.c#L365">365</a> 
<a name="L366" href="source/net/ipv4/ip_sockglue.c#L366">366</a>         return 0;
<a name="L367" href="source/net/ipv4/ip_sockglue.c#L367">367</a> }
<a name="L368" href="source/net/ipv4/ip_sockglue.c#L368">368</a> 
<a name="L369" href="source/net/ipv4/ip_sockglue.c#L369">369</a> void <a href="ident?i=ip_icmp_error">ip_icmp_error</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, int <a href="ident?i=err">err</a>,
<a name="L370" href="source/net/ipv4/ip_sockglue.c#L370">370</a>                    <a href="ident?i=__be16">__be16</a> <a href="ident?i=port">port</a>, <a href="ident?i=u32">u32</a> <a href="ident?i=info">info</a>, <a href="ident?i=u8">u8</a> *<a href="ident?i=payload">payload</a>)
<a name="L371" href="source/net/ipv4/ip_sockglue.c#L371">371</a> {
<a name="L372" href="source/net/ipv4/ip_sockglue.c#L372">372</a>         struct <a href="ident?i=sock_exterr_skb">sock_exterr_skb</a> *serr;
<a name="L373" href="source/net/ipv4/ip_sockglue.c#L373">373</a> 
<a name="L374" href="source/net/ipv4/ip_sockglue.c#L374">374</a>         <a href="ident?i=skb">skb</a> = <a href="ident?i=skb_clone">skb_clone</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=GFP_ATOMIC">GFP_ATOMIC</a>);
<a name="L375" href="source/net/ipv4/ip_sockglue.c#L375">375</a>         if (!<a href="ident?i=skb">skb</a>)
<a name="L376" href="source/net/ipv4/ip_sockglue.c#L376">376</a>                 return;
<a name="L377" href="source/net/ipv4/ip_sockglue.c#L377">377</a> 
<a name="L378" href="source/net/ipv4/ip_sockglue.c#L378">378</a>         serr = <a href="ident?i=SKB_EXT_ERR">SKB_EXT_ERR</a>(<a href="ident?i=skb">skb</a>);
<a name="L379" href="source/net/ipv4/ip_sockglue.c#L379">379</a>         serr-&gt;ee.ee_errno = <a href="ident?i=err">err</a>;
<a name="L380" href="source/net/ipv4/ip_sockglue.c#L380">380</a>         serr-&gt;ee.ee_origin = <a href="ident?i=SO_EE_ORIGIN_ICMP">SO_EE_ORIGIN_ICMP</a>;
<a name="L381" href="source/net/ipv4/ip_sockglue.c#L381">381</a>         serr-&gt;ee.ee_type = <a href="ident?i=icmp_hdr">icmp_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=type">type</a>;
<a name="L382" href="source/net/ipv4/ip_sockglue.c#L382">382</a>         serr-&gt;ee.ee_code = <a href="ident?i=icmp_hdr">icmp_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=code">code</a>;
<a name="L383" href="source/net/ipv4/ip_sockglue.c#L383">383</a>         serr-&gt;ee.ee_pad = 0;
<a name="L384" href="source/net/ipv4/ip_sockglue.c#L384">384</a>         serr-&gt;ee.ee_info = <a href="ident?i=info">info</a>;
<a name="L385" href="source/net/ipv4/ip_sockglue.c#L385">385</a>         serr-&gt;ee.ee_data = 0;
<a name="L386" href="source/net/ipv4/ip_sockglue.c#L386">386</a>         serr-&gt;addr_offset = (<a href="ident?i=u8">u8</a> *)&amp;(((struct <a href="ident?i=iphdr">iphdr</a> *)(<a href="ident?i=icmp_hdr">icmp_hdr</a>(<a href="ident?i=skb">skb</a>) + 1))-&gt;<a href="ident?i=daddr">daddr</a>) -
<a name="L387" href="source/net/ipv4/ip_sockglue.c#L387">387</a>                                    <a href="ident?i=skb_network_header">skb_network_header</a>(<a href="ident?i=skb">skb</a>);
<a name="L388" href="source/net/ipv4/ip_sockglue.c#L388">388</a>         serr-&gt;<a href="ident?i=port">port</a> = <a href="ident?i=port">port</a>;
<a name="L389" href="source/net/ipv4/ip_sockglue.c#L389">389</a> 
<a name="L390" href="source/net/ipv4/ip_sockglue.c#L390">390</a>         if (<a href="ident?i=skb_pull">skb_pull</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=payload">payload</a> - <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=data">data</a>)) {
<a name="L391" href="source/net/ipv4/ip_sockglue.c#L391">391</a>                 <a href="ident?i=skb_reset_transport_header">skb_reset_transport_header</a>(<a href="ident?i=skb">skb</a>);
<a name="L392" href="source/net/ipv4/ip_sockglue.c#L392">392</a>                 if (<a href="ident?i=sock_queue_err_skb">sock_queue_err_skb</a>(sk, <a href="ident?i=skb">skb</a>) == 0)
<a name="L393" href="source/net/ipv4/ip_sockglue.c#L393">393</a>                         return;
<a name="L394" href="source/net/ipv4/ip_sockglue.c#L394">394</a>         }
<a name="L395" href="source/net/ipv4/ip_sockglue.c#L395">395</a>         <a href="ident?i=kfree_skb">kfree_skb</a>(<a href="ident?i=skb">skb</a>);
<a name="L396" href="source/net/ipv4/ip_sockglue.c#L396">396</a> }
<a name="L397" href="source/net/ipv4/ip_sockglue.c#L397">397</a> 
<a name="L398" href="source/net/ipv4/ip_sockglue.c#L398">398</a> void <a href="ident?i=ip_local_error">ip_local_error</a>(struct <a href="ident?i=sock">sock</a> *sk, int <a href="ident?i=err">err</a>, <a href="ident?i=__be32">__be32</a> <a href="ident?i=daddr">daddr</a>, <a href="ident?i=__be16">__be16</a> <a href="ident?i=port">port</a>, <a href="ident?i=u32">u32</a> <a href="ident?i=info">info</a>)
<a name="L399" href="source/net/ipv4/ip_sockglue.c#L399">399</a> {
<a name="L400" href="source/net/ipv4/ip_sockglue.c#L400">400</a>         struct <a href="ident?i=inet_sock">inet_sock</a> *inet = <a href="ident?i=inet_sk">inet_sk</a>(sk);
<a name="L401" href="source/net/ipv4/ip_sockglue.c#L401">401</a>         struct <a href="ident?i=sock_exterr_skb">sock_exterr_skb</a> *serr;
<a name="L402" href="source/net/ipv4/ip_sockglue.c#L402">402</a>         struct <a href="ident?i=iphdr">iphdr</a> *iph;
<a name="L403" href="source/net/ipv4/ip_sockglue.c#L403">403</a>         struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>;
<a name="L404" href="source/net/ipv4/ip_sockglue.c#L404">404</a> 
<a name="L405" href="source/net/ipv4/ip_sockglue.c#L405">405</a>         if (!inet-&gt;recverr)
<a name="L406" href="source/net/ipv4/ip_sockglue.c#L406">406</a>                 return;
<a name="L407" href="source/net/ipv4/ip_sockglue.c#L407">407</a> 
<a name="L408" href="source/net/ipv4/ip_sockglue.c#L408">408</a>         <a href="ident?i=skb">skb</a> = <a href="ident?i=alloc_skb">alloc_skb</a>(sizeof(struct <a href="ident?i=iphdr">iphdr</a>), <a href="ident?i=GFP_ATOMIC">GFP_ATOMIC</a>);
<a name="L409" href="source/net/ipv4/ip_sockglue.c#L409">409</a>         if (!<a href="ident?i=skb">skb</a>)
<a name="L410" href="source/net/ipv4/ip_sockglue.c#L410">410</a>                 return;
<a name="L411" href="source/net/ipv4/ip_sockglue.c#L411">411</a> 
<a name="L412" href="source/net/ipv4/ip_sockglue.c#L412">412</a>         <a href="ident?i=skb_put">skb_put</a>(<a href="ident?i=skb">skb</a>, sizeof(struct <a href="ident?i=iphdr">iphdr</a>));
<a name="L413" href="source/net/ipv4/ip_sockglue.c#L413">413</a>         <a href="ident?i=skb_reset_network_header">skb_reset_network_header</a>(<a href="ident?i=skb">skb</a>);
<a name="L414" href="source/net/ipv4/ip_sockglue.c#L414">414</a>         iph = <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>);
<a name="L415" href="source/net/ipv4/ip_sockglue.c#L415">415</a>         iph-&gt;<a href="ident?i=daddr">daddr</a> = <a href="ident?i=daddr">daddr</a>;
<a name="L416" href="source/net/ipv4/ip_sockglue.c#L416">416</a> 
<a name="L417" href="source/net/ipv4/ip_sockglue.c#L417">417</a>         serr = <a href="ident?i=SKB_EXT_ERR">SKB_EXT_ERR</a>(<a href="ident?i=skb">skb</a>);
<a name="L418" href="source/net/ipv4/ip_sockglue.c#L418">418</a>         serr-&gt;ee.ee_errno = <a href="ident?i=err">err</a>;
<a name="L419" href="source/net/ipv4/ip_sockglue.c#L419">419</a>         serr-&gt;ee.ee_origin = <a href="ident?i=SO_EE_ORIGIN_LOCAL">SO_EE_ORIGIN_LOCAL</a>;
<a name="L420" href="source/net/ipv4/ip_sockglue.c#L420">420</a>         serr-&gt;ee.ee_type = 0;
<a name="L421" href="source/net/ipv4/ip_sockglue.c#L421">421</a>         serr-&gt;ee.ee_code = 0;
<a name="L422" href="source/net/ipv4/ip_sockglue.c#L422">422</a>         serr-&gt;ee.ee_pad = 0;
<a name="L423" href="source/net/ipv4/ip_sockglue.c#L423">423</a>         serr-&gt;ee.ee_info = <a href="ident?i=info">info</a>;
<a name="L424" href="source/net/ipv4/ip_sockglue.c#L424">424</a>         serr-&gt;ee.ee_data = 0;
<a name="L425" href="source/net/ipv4/ip_sockglue.c#L425">425</a>         serr-&gt;addr_offset = (<a href="ident?i=u8">u8</a> *)&amp;iph-&gt;<a href="ident?i=daddr">daddr</a> - <a href="ident?i=skb_network_header">skb_network_header</a>(<a href="ident?i=skb">skb</a>);
<a name="L426" href="source/net/ipv4/ip_sockglue.c#L426">426</a>         serr-&gt;<a href="ident?i=port">port</a> = <a href="ident?i=port">port</a>;
<a name="L427" href="source/net/ipv4/ip_sockglue.c#L427">427</a> 
<a name="L428" href="source/net/ipv4/ip_sockglue.c#L428">428</a>         <a href="ident?i=__skb_pull">__skb_pull</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=skb_tail_pointer">skb_tail_pointer</a>(<a href="ident?i=skb">skb</a>) - <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=data">data</a>);
<a name="L429" href="source/net/ipv4/ip_sockglue.c#L429">429</a>         <a href="ident?i=skb_reset_transport_header">skb_reset_transport_header</a>(<a href="ident?i=skb">skb</a>);
<a name="L430" href="source/net/ipv4/ip_sockglue.c#L430">430</a> 
<a name="L431" href="source/net/ipv4/ip_sockglue.c#L431">431</a>         if (<a href="ident?i=sock_queue_err_skb">sock_queue_err_skb</a>(sk, <a href="ident?i=skb">skb</a>))
<a name="L432" href="source/net/ipv4/ip_sockglue.c#L432">432</a>                 <a href="ident?i=kfree_skb">kfree_skb</a>(<a href="ident?i=skb">skb</a>);
<a name="L433" href="source/net/ipv4/ip_sockglue.c#L433">433</a> }
<a name="L434" href="source/net/ipv4/ip_sockglue.c#L434">434</a> 
<a name="L435" href="source/net/ipv4/ip_sockglue.c#L435">435</a> <b><i>/* IPv4 supports cmsg on all imcp errors and some timestamps</i></b>
<a name="L436" href="source/net/ipv4/ip_sockglue.c#L436">436</a> <b><i> *</i></b>
<a name="L437" href="source/net/ipv4/ip_sockglue.c#L437">437</a> <b><i> * Timestamp code paths do not initialize the fields expected by cmsg:</i></b>
<a name="L438" href="source/net/ipv4/ip_sockglue.c#L438">438</a> <b><i> * the PKTINFO fields in skb-&gt;cb[]. Fill those in here.</i></b>
<a name="L439" href="source/net/ipv4/ip_sockglue.c#L439">439</a> <b><i> */</i></b>
<a name="L440" href="source/net/ipv4/ip_sockglue.c#L440">440</a> static <a href="ident?i=bool">bool</a> <a href="ident?i=ipv4_datagram_support_cmsg">ipv4_datagram_support_cmsg</a>(const struct <a href="ident?i=sock">sock</a> *sk,
<a name="L441" href="source/net/ipv4/ip_sockglue.c#L441">441</a>                                        struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
<a name="L442" href="source/net/ipv4/ip_sockglue.c#L442">442</a>                                        int ee_origin)
<a name="L443" href="source/net/ipv4/ip_sockglue.c#L443">443</a> {
<a name="L444" href="source/net/ipv4/ip_sockglue.c#L444">444</a>         struct <a href="ident?i=in_pktinfo">in_pktinfo</a> *<a href="ident?i=info">info</a>;
<a name="L445" href="source/net/ipv4/ip_sockglue.c#L445">445</a> 
<a name="L446" href="source/net/ipv4/ip_sockglue.c#L446">446</a>         if (ee_origin == <a href="ident?i=SO_EE_ORIGIN_ICMP">SO_EE_ORIGIN_ICMP</a>)
<a name="L447" href="source/net/ipv4/ip_sockglue.c#L447">447</a>                 return <a href="ident?i=true">true</a>;
<a name="L448" href="source/net/ipv4/ip_sockglue.c#L448">448</a> 
<a name="L449" href="source/net/ipv4/ip_sockglue.c#L449">449</a>         if (ee_origin == <a href="ident?i=SO_EE_ORIGIN_LOCAL">SO_EE_ORIGIN_LOCAL</a>)
<a name="L450" href="source/net/ipv4/ip_sockglue.c#L450">450</a>                 return <a href="ident?i=false">false</a>;
<a name="L451" href="source/net/ipv4/ip_sockglue.c#L451">451</a> 
<a name="L452" href="source/net/ipv4/ip_sockglue.c#L452">452</a>         <b><i>/* Support IP_PKTINFO on tstamp packets if requested, to correlate</i></b>
<a name="L453" href="source/net/ipv4/ip_sockglue.c#L453">453</a> <b><i>         * timestamp with egress dev. Not possible for packets without dev</i></b>
<a name="L454" href="source/net/ipv4/ip_sockglue.c#L454">454</a> <b><i>         * or without payload (SOF_TIMESTAMPING_OPT_TSONLY).</i></b>
<a name="L455" href="source/net/ipv4/ip_sockglue.c#L455">455</a> <b><i>         */</i></b>
<a name="L456" href="source/net/ipv4/ip_sockglue.c#L456">456</a>         if ((!(sk-&gt;sk_tsflags &amp; SOF_TIMESTAMPING_OPT_CMSG)) ||
<a name="L457" href="source/net/ipv4/ip_sockglue.c#L457">457</a>             (!<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=dev">dev</a>))
<a name="L458" href="source/net/ipv4/ip_sockglue.c#L458">458</a>                 return <a href="ident?i=false">false</a>;
<a name="L459" href="source/net/ipv4/ip_sockglue.c#L459">459</a> 
<a name="L460" href="source/net/ipv4/ip_sockglue.c#L460">460</a>         <a href="ident?i=info">info</a> = <a href="ident?i=PKTINFO_SKB_CB">PKTINFO_SKB_CB</a>(<a href="ident?i=skb">skb</a>);
<a name="L461" href="source/net/ipv4/ip_sockglue.c#L461">461</a>         <a href="ident?i=info">info</a>-&gt;ipi_spec_dst.s_addr = <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=saddr">saddr</a>;
<a name="L462" href="source/net/ipv4/ip_sockglue.c#L462">462</a>         <a href="ident?i=info">info</a>-&gt;ipi_ifindex = <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=dev">dev</a>-&gt;ifindex;
<a name="L463" href="source/net/ipv4/ip_sockglue.c#L463">463</a>         return <a href="ident?i=true">true</a>;
<a name="L464" href="source/net/ipv4/ip_sockglue.c#L464">464</a> }
<a name="L465" href="source/net/ipv4/ip_sockglue.c#L465">465</a> 
<a name="L466" href="source/net/ipv4/ip_sockglue.c#L466">466</a> <b><i>/*</i></b>
<a name="L467" href="source/net/ipv4/ip_sockglue.c#L467">467</a> <b><i> *      Handle MSG_ERRQUEUE</i></b>
<a name="L468" href="source/net/ipv4/ip_sockglue.c#L468">468</a> <b><i> */</i></b>
<a name="L469" href="source/net/ipv4/ip_sockglue.c#L469">469</a> int <a href="ident?i=ip_recv_error">ip_recv_error</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=msghdr">msghdr</a> *<a href="ident?i=msg">msg</a>, int <a href="ident?i=len">len</a>, int *addr_len)
<a name="L470" href="source/net/ipv4/ip_sockglue.c#L470">470</a> {
<a name="L471" href="source/net/ipv4/ip_sockglue.c#L471">471</a>         struct <a href="ident?i=sock_exterr_skb">sock_exterr_skb</a> *serr;
<a name="L472" href="source/net/ipv4/ip_sockglue.c#L472">472</a>         struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>;
<a name="L473" href="source/net/ipv4/ip_sockglue.c#L473">473</a>         <a href="ident?i=DECLARE_SOCKADDR">DECLARE_SOCKADDR</a>(struct <a href="ident?i=sockaddr_in">sockaddr_in</a> *, <a href="ident?i=sin">sin</a>, <a href="ident?i=msg">msg</a>-&gt;msg_name);
<a name="L474" href="source/net/ipv4/ip_sockglue.c#L474">474</a>         struct {
<a name="L475" href="source/net/ipv4/ip_sockglue.c#L475">475</a>                 struct <a href="ident?i=sock_extended_err">sock_extended_err</a> ee;
<a name="L476" href="source/net/ipv4/ip_sockglue.c#L476">476</a>                 struct <a href="ident?i=sockaddr_in">sockaddr_in</a>       offender;
<a name="L477" href="source/net/ipv4/ip_sockglue.c#L477">477</a>         } errhdr;
<a name="L478" href="source/net/ipv4/ip_sockglue.c#L478">478</a>         int <a href="ident?i=err">err</a>;
<a name="L479" href="source/net/ipv4/ip_sockglue.c#L479">479</a>         int copied;
<a name="L480" href="source/net/ipv4/ip_sockglue.c#L480">480</a> 
<a name="L481" href="source/net/ipv4/ip_sockglue.c#L481">481</a>         <a href="ident?i=WARN_ON_ONCE">WARN_ON_ONCE</a>(sk-&gt;<a href="ident?i=sk_family">sk_family</a> == <a href="ident?i=AF_INET6">AF_INET6</a>);
<a name="L482" href="source/net/ipv4/ip_sockglue.c#L482">482</a> 
<a name="L483" href="source/net/ipv4/ip_sockglue.c#L483">483</a>         <a href="ident?i=err">err</a> = -<a href="ident?i=EAGAIN">EAGAIN</a>;
<a name="L484" href="source/net/ipv4/ip_sockglue.c#L484">484</a>         <a href="ident?i=skb">skb</a> = <a href="ident?i=sock_dequeue_err_skb">sock_dequeue_err_skb</a>(sk);
<a name="L485" href="source/net/ipv4/ip_sockglue.c#L485">485</a>         if (!<a href="ident?i=skb">skb</a>)
<a name="L486" href="source/net/ipv4/ip_sockglue.c#L486">486</a>                 goto <a href="ident?i=out">out</a>;
<a name="L487" href="source/net/ipv4/ip_sockglue.c#L487">487</a> 
<a name="L488" href="source/net/ipv4/ip_sockglue.c#L488">488</a>         copied = <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a>;
<a name="L489" href="source/net/ipv4/ip_sockglue.c#L489">489</a>         if (copied &gt; <a href="ident?i=len">len</a>) {
<a name="L490" href="source/net/ipv4/ip_sockglue.c#L490">490</a>                 <a href="ident?i=msg">msg</a>-&gt;msg_flags |= <a href="ident?i=MSG_TRUNC">MSG_TRUNC</a>;
<a name="L491" href="source/net/ipv4/ip_sockglue.c#L491">491</a>                 copied = <a href="ident?i=len">len</a>;
<a name="L492" href="source/net/ipv4/ip_sockglue.c#L492">492</a>         }
<a name="L493" href="source/net/ipv4/ip_sockglue.c#L493">493</a>         <a href="ident?i=err">err</a> = <a href="ident?i=skb_copy_datagram_msg">skb_copy_datagram_msg</a>(<a href="ident?i=skb">skb</a>, 0, <a href="ident?i=msg">msg</a>, copied);
<a name="L494" href="source/net/ipv4/ip_sockglue.c#L494">494</a>         if (<a href="ident?i=err">err</a>)
<a name="L495" href="source/net/ipv4/ip_sockglue.c#L495">495</a>                 goto out_free_skb;
<a name="L496" href="source/net/ipv4/ip_sockglue.c#L496">496</a> 
<a name="L497" href="source/net/ipv4/ip_sockglue.c#L497">497</a>         <a href="ident?i=sock_recv_timestamp">sock_recv_timestamp</a>(<a href="ident?i=msg">msg</a>, sk, <a href="ident?i=skb">skb</a>);
<a name="L498" href="source/net/ipv4/ip_sockglue.c#L498">498</a> 
<a name="L499" href="source/net/ipv4/ip_sockglue.c#L499">499</a>         serr = <a href="ident?i=SKB_EXT_ERR">SKB_EXT_ERR</a>(<a href="ident?i=skb">skb</a>);
<a name="L500" href="source/net/ipv4/ip_sockglue.c#L500">500</a> 
<a name="L501" href="source/net/ipv4/ip_sockglue.c#L501">501</a>         if (<a href="ident?i=sin">sin</a> &amp;&amp; serr-&gt;<a href="ident?i=port">port</a>) {
<a name="L502" href="source/net/ipv4/ip_sockglue.c#L502">502</a>                 <a href="ident?i=sin">sin</a>-&gt;sin_family = <a href="ident?i=AF_INET">AF_INET</a>;
<a name="L503" href="source/net/ipv4/ip_sockglue.c#L503">503</a>                 <a href="ident?i=sin">sin</a>-&gt;sin_addr.s_addr = *(<a href="ident?i=__be32">__be32</a> *)(<a href="ident?i=skb_network_header">skb_network_header</a>(<a href="ident?i=skb">skb</a>) +
<a name="L504" href="source/net/ipv4/ip_sockglue.c#L504">504</a>                                                    serr-&gt;addr_offset);
<a name="L505" href="source/net/ipv4/ip_sockglue.c#L505">505</a>                 <a href="ident?i=sin">sin</a>-&gt;sin_port = serr-&gt;<a href="ident?i=port">port</a>;
<a name="L506" href="source/net/ipv4/ip_sockglue.c#L506">506</a>                 <a href="ident?i=memset">memset</a>(&amp;<a href="ident?i=sin">sin</a>-&gt;<a href="ident?i=sin_zero">sin_zero</a>, 0, sizeof(<a href="ident?i=sin">sin</a>-&gt;<a href="ident?i=sin_zero">sin_zero</a>));
<a name="L507" href="source/net/ipv4/ip_sockglue.c#L507">507</a>                 *addr_len = sizeof(*<a href="ident?i=sin">sin</a>);
<a name="L508" href="source/net/ipv4/ip_sockglue.c#L508">508</a>         }
<a name="L509" href="source/net/ipv4/ip_sockglue.c#L509">509</a> 
<a name="L510" href="source/net/ipv4/ip_sockglue.c#L510">510</a>         <a href="ident?i=memcpy">memcpy</a>(&amp;errhdr.ee, &amp;serr-&gt;ee, sizeof(struct <a href="ident?i=sock_extended_err">sock_extended_err</a>));
<a name="L511" href="source/net/ipv4/ip_sockglue.c#L511">511</a>         <a href="ident?i=sin">sin</a> = &amp;errhdr.offender;
<a name="L512" href="source/net/ipv4/ip_sockglue.c#L512">512</a>         <a href="ident?i=memset">memset</a>(<a href="ident?i=sin">sin</a>, 0, sizeof(*<a href="ident?i=sin">sin</a>));
<a name="L513" href="source/net/ipv4/ip_sockglue.c#L513">513</a> 
<a name="L514" href="source/net/ipv4/ip_sockglue.c#L514">514</a>         if (<a href="ident?i=ipv4_datagram_support_cmsg">ipv4_datagram_support_cmsg</a>(sk, <a href="ident?i=skb">skb</a>, serr-&gt;ee.ee_origin)) {
<a name="L515" href="source/net/ipv4/ip_sockglue.c#L515">515</a>                 <a href="ident?i=sin">sin</a>-&gt;sin_family = <a href="ident?i=AF_INET">AF_INET</a>;
<a name="L516" href="source/net/ipv4/ip_sockglue.c#L516">516</a>                 <a href="ident?i=sin">sin</a>-&gt;sin_addr.s_addr = <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=saddr">saddr</a>;
<a name="L517" href="source/net/ipv4/ip_sockglue.c#L517">517</a>                 if (<a href="ident?i=inet_sk">inet_sk</a>(sk)-&gt;cmsg_flags)
<a name="L518" href="source/net/ipv4/ip_sockglue.c#L518">518</a>                         <a href="ident?i=ip_cmsg_recv">ip_cmsg_recv</a>(<a href="ident?i=msg">msg</a>, <a href="ident?i=skb">skb</a>);
<a name="L519" href="source/net/ipv4/ip_sockglue.c#L519">519</a>         }
<a name="L520" href="source/net/ipv4/ip_sockglue.c#L520">520</a> 
<a name="L521" href="source/net/ipv4/ip_sockglue.c#L521">521</a>         <a href="ident?i=put_cmsg">put_cmsg</a>(<a href="ident?i=msg">msg</a>, <a href="ident?i=SOL_IP">SOL_IP</a>, <a href="ident?i=IP_RECVERR">IP_RECVERR</a>, sizeof(errhdr), &amp;errhdr);
<a name="L522" href="source/net/ipv4/ip_sockglue.c#L522">522</a> 
<a name="L523" href="source/net/ipv4/ip_sockglue.c#L523">523</a>         <b><i>/* Now we could try to dump offended packet options */</i></b>
<a name="L524" href="source/net/ipv4/ip_sockglue.c#L524">524</a> 
<a name="L525" href="source/net/ipv4/ip_sockglue.c#L525">525</a>         <a href="ident?i=msg">msg</a>-&gt;msg_flags |= <a href="ident?i=MSG_ERRQUEUE">MSG_ERRQUEUE</a>;
<a name="L526" href="source/net/ipv4/ip_sockglue.c#L526">526</a>         <a href="ident?i=err">err</a> = copied;
<a name="L527" href="source/net/ipv4/ip_sockglue.c#L527">527</a> 
<a name="L528" href="source/net/ipv4/ip_sockglue.c#L528">528</a> out_free_skb:
<a name="L529" href="source/net/ipv4/ip_sockglue.c#L529">529</a>         <a href="ident?i=kfree_skb">kfree_skb</a>(<a href="ident?i=skb">skb</a>);
<a name="L530" href="source/net/ipv4/ip_sockglue.c#L530">530</a> <a href="ident?i=out">out</a>:
<a name="L531" href="source/net/ipv4/ip_sockglue.c#L531">531</a>         return <a href="ident?i=err">err</a>;
<a name="L532" href="source/net/ipv4/ip_sockglue.c#L532">532</a> }
<a name="L533" href="source/net/ipv4/ip_sockglue.c#L533">533</a> 
<a name="L534" href="source/net/ipv4/ip_sockglue.c#L534">534</a> 
<a name="L535" href="source/net/ipv4/ip_sockglue.c#L535">535</a> <b><i>/*</i></b>
<a name="L536" href="source/net/ipv4/ip_sockglue.c#L536">536</a> <b><i> *      Socket option code for IP. This is the end of the line after any</i></b>
<a name="L537" href="source/net/ipv4/ip_sockglue.c#L537">537</a> <b><i> *      TCP,UDP etc options on an IP socket.</i></b>
<a name="L538" href="source/net/ipv4/ip_sockglue.c#L538">538</a> <b><i> */</i></b>
<a name="L539" href="source/net/ipv4/ip_sockglue.c#L539">539</a> static <a href="ident?i=bool">bool</a> <a href="ident?i=setsockopt_needs_rtnl">setsockopt_needs_rtnl</a>(int optname)
<a name="L540" href="source/net/ipv4/ip_sockglue.c#L540">540</a> {
<a name="L541" href="source/net/ipv4/ip_sockglue.c#L541">541</a>         switch (optname) {
<a name="L542" href="source/net/ipv4/ip_sockglue.c#L542">542</a>         case <a href="ident?i=IP_ADD_MEMBERSHIP">IP_ADD_MEMBERSHIP</a>:
<a name="L543" href="source/net/ipv4/ip_sockglue.c#L543">543</a>         case <a href="ident?i=IP_ADD_SOURCE_MEMBERSHIP">IP_ADD_SOURCE_MEMBERSHIP</a>:
<a name="L544" href="source/net/ipv4/ip_sockglue.c#L544">544</a>         case <a href="ident?i=IP_BLOCK_SOURCE">IP_BLOCK_SOURCE</a>:
<a name="L545" href="source/net/ipv4/ip_sockglue.c#L545">545</a>         case <a href="ident?i=IP_DROP_MEMBERSHIP">IP_DROP_MEMBERSHIP</a>:
<a name="L546" href="source/net/ipv4/ip_sockglue.c#L546">546</a>         case <a href="ident?i=IP_DROP_SOURCE_MEMBERSHIP">IP_DROP_SOURCE_MEMBERSHIP</a>:
<a name="L547" href="source/net/ipv4/ip_sockglue.c#L547">547</a>         case <a href="ident?i=IP_MSFILTER">IP_MSFILTER</a>:
<a name="L548" href="source/net/ipv4/ip_sockglue.c#L548">548</a>         case <a href="ident?i=IP_UNBLOCK_SOURCE">IP_UNBLOCK_SOURCE</a>:
<a name="L549" href="source/net/ipv4/ip_sockglue.c#L549">549</a>         case <a href="ident?i=MCAST_BLOCK_SOURCE">MCAST_BLOCK_SOURCE</a>:
<a name="L550" href="source/net/ipv4/ip_sockglue.c#L550">550</a>         case <a href="ident?i=MCAST_MSFILTER">MCAST_MSFILTER</a>:
<a name="L551" href="source/net/ipv4/ip_sockglue.c#L551">551</a>         case <a href="ident?i=MCAST_JOIN_GROUP">MCAST_JOIN_GROUP</a>:
<a name="L552" href="source/net/ipv4/ip_sockglue.c#L552">552</a>         case <a href="ident?i=MCAST_JOIN_SOURCE_GROUP">MCAST_JOIN_SOURCE_GROUP</a>:
<a name="L553" href="source/net/ipv4/ip_sockglue.c#L553">553</a>         case <a href="ident?i=MCAST_LEAVE_GROUP">MCAST_LEAVE_GROUP</a>:
<a name="L554" href="source/net/ipv4/ip_sockglue.c#L554">554</a>         case <a href="ident?i=MCAST_LEAVE_SOURCE_GROUP">MCAST_LEAVE_SOURCE_GROUP</a>:
<a name="L555" href="source/net/ipv4/ip_sockglue.c#L555">555</a>         case <a href="ident?i=MCAST_UNBLOCK_SOURCE">MCAST_UNBLOCK_SOURCE</a>:
<a name="L556" href="source/net/ipv4/ip_sockglue.c#L556">556</a>                 return <a href="ident?i=true">true</a>;
<a name="L557" href="source/net/ipv4/ip_sockglue.c#L557">557</a>         }
<a name="L558" href="source/net/ipv4/ip_sockglue.c#L558">558</a>         return <a href="ident?i=false">false</a>;
<a name="L559" href="source/net/ipv4/ip_sockglue.c#L559">559</a> }
<a name="L560" href="source/net/ipv4/ip_sockglue.c#L560">560</a> 
<a name="L561" href="source/net/ipv4/ip_sockglue.c#L561">561</a> static int <a href="ident?i=do_ip_setsockopt">do_ip_setsockopt</a>(struct <a href="ident?i=sock">sock</a> *sk, int <a href="ident?i=level">level</a>,
<a name="L562" href="source/net/ipv4/ip_sockglue.c#L562">562</a>                             int optname, char <a href="ident?i=__user">__user</a> *optval, unsigned int <a href="ident?i=optlen">optlen</a>)
<a name="L563" href="source/net/ipv4/ip_sockglue.c#L563">563</a> {
<a name="L564" href="source/net/ipv4/ip_sockglue.c#L564">564</a>         struct <a href="ident?i=inet_sock">inet_sock</a> *inet = <a href="ident?i=inet_sk">inet_sk</a>(sk);
<a name="L565" href="source/net/ipv4/ip_sockglue.c#L565">565</a>         int <a href="ident?i=val">val</a> = 0, <a href="ident?i=err">err</a>;
<a name="L566" href="source/net/ipv4/ip_sockglue.c#L566">566</a>         <a href="ident?i=bool">bool</a> needs_rtnl = <a href="ident?i=setsockopt_needs_rtnl">setsockopt_needs_rtnl</a>(optname);
<a name="L567" href="source/net/ipv4/ip_sockglue.c#L567">567</a> 
<a name="L568" href="source/net/ipv4/ip_sockglue.c#L568">568</a>         switch (optname) {
<a name="L569" href="source/net/ipv4/ip_sockglue.c#L569">569</a>         case <a href="ident?i=IP_PKTINFO">IP_PKTINFO</a>:
<a name="L570" href="source/net/ipv4/ip_sockglue.c#L570">570</a>         case <a href="ident?i=IP_RECVTTL">IP_RECVTTL</a>:
<a name="L571" href="source/net/ipv4/ip_sockglue.c#L571">571</a>         case <a href="ident?i=IP_RECVOPTS">IP_RECVOPTS</a>:
<a name="L572" href="source/net/ipv4/ip_sockglue.c#L572">572</a>         case <a href="ident?i=IP_RECVTOS">IP_RECVTOS</a>:
<a name="L573" href="source/net/ipv4/ip_sockglue.c#L573">573</a>         case <a href="ident?i=IP_RETOPTS">IP_RETOPTS</a>:
<a name="L574" href="source/net/ipv4/ip_sockglue.c#L574">574</a>         case <a href="ident?i=IP_TOS">IP_TOS</a>:
<a name="L575" href="source/net/ipv4/ip_sockglue.c#L575">575</a>         case <a href="ident?i=IP_TTL">IP_TTL</a>:
<a name="L576" href="source/net/ipv4/ip_sockglue.c#L576">576</a>         case <a href="ident?i=IP_HDRINCL">IP_HDRINCL</a>:
<a name="L577" href="source/net/ipv4/ip_sockglue.c#L577">577</a>         case <a href="ident?i=IP_MTU_DISCOVER">IP_MTU_DISCOVER</a>:
<a name="L578" href="source/net/ipv4/ip_sockglue.c#L578">578</a>         case <a href="ident?i=IP_RECVERR">IP_RECVERR</a>:
<a name="L579" href="source/net/ipv4/ip_sockglue.c#L579">579</a>         case <a href="ident?i=IP_ROUTER_ALERT">IP_ROUTER_ALERT</a>:
<a name="L580" href="source/net/ipv4/ip_sockglue.c#L580">580</a>         case <a href="ident?i=IP_FREEBIND">IP_FREEBIND</a>:
<a name="L581" href="source/net/ipv4/ip_sockglue.c#L581">581</a>         case <a href="ident?i=IP_PASSSEC">IP_PASSSEC</a>:
<a name="L582" href="source/net/ipv4/ip_sockglue.c#L582">582</a>         case <a href="ident?i=IP_TRANSPARENT">IP_TRANSPARENT</a>:
<a name="L583" href="source/net/ipv4/ip_sockglue.c#L583">583</a>         case <a href="ident?i=IP_MINTTL">IP_MINTTL</a>:
<a name="L584" href="source/net/ipv4/ip_sockglue.c#L584">584</a>         case <a href="ident?i=IP_NODEFRAG">IP_NODEFRAG</a>:
<a name="L585" href="source/net/ipv4/ip_sockglue.c#L585">585</a>         case <a href="ident?i=IP_UNICAST_IF">IP_UNICAST_IF</a>:
<a name="L586" href="source/net/ipv4/ip_sockglue.c#L586">586</a>         case <a href="ident?i=IP_MULTICAST_TTL">IP_MULTICAST_TTL</a>:
<a name="L587" href="source/net/ipv4/ip_sockglue.c#L587">587</a>         case <a href="ident?i=IP_MULTICAST_ALL">IP_MULTICAST_ALL</a>:
<a name="L588" href="source/net/ipv4/ip_sockglue.c#L588">588</a>         case <a href="ident?i=IP_MULTICAST_LOOP">IP_MULTICAST_LOOP</a>:
<a name="L589" href="source/net/ipv4/ip_sockglue.c#L589">589</a>         case <a href="ident?i=IP_RECVORIGDSTADDR">IP_RECVORIGDSTADDR</a>:
<a name="L590" href="source/net/ipv4/ip_sockglue.c#L590">590</a>         case <a href="ident?i=IP_CHECKSUM">IP_CHECKSUM</a>:
<a name="L591" href="source/net/ipv4/ip_sockglue.c#L591">591</a>                 if (<a href="ident?i=optlen">optlen</a> &gt;= sizeof(int)) {
<a name="L592" href="source/net/ipv4/ip_sockglue.c#L592">592</a>                         if (<a href="ident?i=get_user">get_user</a>(<a href="ident?i=val">val</a>, (int <a href="ident?i=__user">__user</a> *) optval))
<a name="L593" href="source/net/ipv4/ip_sockglue.c#L593">593</a>                                 return -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L594" href="source/net/ipv4/ip_sockglue.c#L594">594</a>                 } else if (<a href="ident?i=optlen">optlen</a> &gt;= sizeof(char)) {
<a name="L595" href="source/net/ipv4/ip_sockglue.c#L595">595</a>                         unsigned char ucval;
<a name="L596" href="source/net/ipv4/ip_sockglue.c#L596">596</a> 
<a name="L597" href="source/net/ipv4/ip_sockglue.c#L597">597</a>                         if (<a href="ident?i=get_user">get_user</a>(ucval, (unsigned char <a href="ident?i=__user">__user</a> *) optval))
<a name="L598" href="source/net/ipv4/ip_sockglue.c#L598">598</a>                                 return -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L599" href="source/net/ipv4/ip_sockglue.c#L599">599</a>                         <a href="ident?i=val">val</a> = (int) ucval;
<a name="L600" href="source/net/ipv4/ip_sockglue.c#L600">600</a>                 }
<a name="L601" href="source/net/ipv4/ip_sockglue.c#L601">601</a>         }
<a name="L602" href="source/net/ipv4/ip_sockglue.c#L602">602</a> 
<a name="L603" href="source/net/ipv4/ip_sockglue.c#L603">603</a>         <b><i>/* If optlen==0, it is equivalent to val == 0 */</i></b>
<a name="L604" href="source/net/ipv4/ip_sockglue.c#L604">604</a> 
<a name="L605" href="source/net/ipv4/ip_sockglue.c#L605">605</a>         if (<a href="ident?i=ip_mroute_opt">ip_mroute_opt</a>(optname))
<a name="L606" href="source/net/ipv4/ip_sockglue.c#L606">606</a>                 return <a href="ident?i=ip_mroute_setsockopt">ip_mroute_setsockopt</a>(sk, optname, optval, <a href="ident?i=optlen">optlen</a>);
<a name="L607" href="source/net/ipv4/ip_sockglue.c#L607">607</a> 
<a name="L608" href="source/net/ipv4/ip_sockglue.c#L608">608</a>         <a href="ident?i=err">err</a> = 0;
<a name="L609" href="source/net/ipv4/ip_sockglue.c#L609">609</a>         if (needs_rtnl)
<a name="L610" href="source/net/ipv4/ip_sockglue.c#L610">610</a>                 <a href="ident?i=rtnl_lock">rtnl_lock</a>();
<a name="L611" href="source/net/ipv4/ip_sockglue.c#L611">611</a>         <a href="ident?i=lock_sock">lock_sock</a>(sk);
<a name="L612" href="source/net/ipv4/ip_sockglue.c#L612">612</a> 
<a name="L613" href="source/net/ipv4/ip_sockglue.c#L613">613</a>         switch (optname) {
<a name="L614" href="source/net/ipv4/ip_sockglue.c#L614">614</a>         case <a href="ident?i=IP_OPTIONS">IP_OPTIONS</a>:
<a name="L615" href="source/net/ipv4/ip_sockglue.c#L615">615</a>         {
<a name="L616" href="source/net/ipv4/ip_sockglue.c#L616">616</a>                 struct <a href="ident?i=ip_options_rcu">ip_options_rcu</a> *<a href="ident?i=old">old</a>, *opt = <a href="ident?i=NULL">NULL</a>;
<a name="L617" href="source/net/ipv4/ip_sockglue.c#L617">617</a> 
<a name="L618" href="source/net/ipv4/ip_sockglue.c#L618">618</a>                 if (<a href="ident?i=optlen">optlen</a> &gt; 40)
<a name="L619" href="source/net/ipv4/ip_sockglue.c#L619">619</a>                         goto e_inval;
<a name="L620" href="source/net/ipv4/ip_sockglue.c#L620">620</a>                 <a href="ident?i=err">err</a> = <a href="ident?i=ip_options_get_from_user">ip_options_get_from_user</a>(<a href="ident?i=sock_net">sock_net</a>(sk), &amp;opt,
<a name="L621" href="source/net/ipv4/ip_sockglue.c#L621">621</a>                                                optval, <a href="ident?i=optlen">optlen</a>);
<a name="L622" href="source/net/ipv4/ip_sockglue.c#L622">622</a>                 if (<a href="ident?i=err">err</a>)
<a name="L623" href="source/net/ipv4/ip_sockglue.c#L623">623</a>                         break;
<a name="L624" href="source/net/ipv4/ip_sockglue.c#L624">624</a>                 <a href="ident?i=old">old</a> = <a href="ident?i=rcu_dereference_protected">rcu_dereference_protected</a>(inet-&gt;inet_opt,
<a name="L625" href="source/net/ipv4/ip_sockglue.c#L625">625</a>                                                 <a href="ident?i=sock_owned_by_user">sock_owned_by_user</a>(sk));
<a name="L626" href="source/net/ipv4/ip_sockglue.c#L626">626</a>                 if (inet-&gt;is_icsk) {
<a name="L627" href="source/net/ipv4/ip_sockglue.c#L627">627</a>                         struct <a href="ident?i=inet_connection_sock">inet_connection_sock</a> *icsk = <a href="ident?i=inet_csk">inet_csk</a>(sk);
<a name="L628" href="source/net/ipv4/ip_sockglue.c#L628">628</a> #if <a href="ident?i=IS_ENABLED">IS_ENABLED</a>(CONFIG_IPV6)
<a name="L629" href="source/net/ipv4/ip_sockglue.c#L629">629</a>                         if (sk-&gt;<a href="ident?i=sk_family">sk_family</a> == <a href="ident?i=PF_INET">PF_INET</a> ||
<a name="L630" href="source/net/ipv4/ip_sockglue.c#L630">630</a>                             (!((1 &lt;&lt; sk-&gt;<a href="ident?i=sk_state">sk_state</a>) &amp;
<a name="L631" href="source/net/ipv4/ip_sockglue.c#L631">631</a>                                (TCPF_LISTEN | TCPF_CLOSE)) &amp;&amp;
<a name="L632" href="source/net/ipv4/ip_sockglue.c#L632">632</a>                              inet-&gt;<a href="ident?i=inet_daddr">inet_daddr</a> != <a href="ident?i=LOOPBACK4_IPV6">LOOPBACK4_IPV6</a>)) {
<a name="L633" href="source/net/ipv4/ip_sockglue.c#L633">633</a> #endif
<a name="L634" href="source/net/ipv4/ip_sockglue.c#L634">634</a>                                 if (<a href="ident?i=old">old</a>)
<a name="L635" href="source/net/ipv4/ip_sockglue.c#L635">635</a>                                         icsk-&gt;icsk_ext_hdr_len -= <a href="ident?i=old">old</a>-&gt;opt.<a href="ident?i=optlen">optlen</a>;
<a name="L636" href="source/net/ipv4/ip_sockglue.c#L636">636</a>                                 if (opt)
<a name="L637" href="source/net/ipv4/ip_sockglue.c#L637">637</a>                                         icsk-&gt;icsk_ext_hdr_len += opt-&gt;opt.<a href="ident?i=optlen">optlen</a>;
<a name="L638" href="source/net/ipv4/ip_sockglue.c#L638">638</a>                                 icsk-&gt;icsk_sync_mss(sk, icsk-&gt;icsk_pmtu_cookie);
<a name="L639" href="source/net/ipv4/ip_sockglue.c#L639">639</a> #if <a href="ident?i=IS_ENABLED">IS_ENABLED</a>(CONFIG_IPV6)
<a name="L640" href="source/net/ipv4/ip_sockglue.c#L640">640</a>                         }
<a name="L641" href="source/net/ipv4/ip_sockglue.c#L641">641</a> #endif
<a name="L642" href="source/net/ipv4/ip_sockglue.c#L642">642</a>                 }
<a name="L643" href="source/net/ipv4/ip_sockglue.c#L643">643</a>                 <a href="ident?i=rcu_assign_pointer">rcu_assign_pointer</a>(inet-&gt;inet_opt, opt);
<a name="L644" href="source/net/ipv4/ip_sockglue.c#L644">644</a>                 if (<a href="ident?i=old">old</a>)
<a name="L645" href="source/net/ipv4/ip_sockglue.c#L645">645</a>                         <a href="ident?i=kfree_rcu">kfree_rcu</a>(<a href="ident?i=old">old</a>, rcu);
<a name="L646" href="source/net/ipv4/ip_sockglue.c#L646">646</a>                 break;
<a name="L647" href="source/net/ipv4/ip_sockglue.c#L647">647</a>         }
<a name="L648" href="source/net/ipv4/ip_sockglue.c#L648">648</a>         case <a href="ident?i=IP_PKTINFO">IP_PKTINFO</a>:
<a name="L649" href="source/net/ipv4/ip_sockglue.c#L649">649</a>                 if (<a href="ident?i=val">val</a>)
<a name="L650" href="source/net/ipv4/ip_sockglue.c#L650">650</a>                         inet-&gt;cmsg_flags |= <a href="ident?i=IP_CMSG_PKTINFO">IP_CMSG_PKTINFO</a>;
<a name="L651" href="source/net/ipv4/ip_sockglue.c#L651">651</a>                 else
<a name="L652" href="source/net/ipv4/ip_sockglue.c#L652">652</a>                         inet-&gt;cmsg_flags &amp;= ~IP_CMSG_PKTINFO;
<a name="L653" href="source/net/ipv4/ip_sockglue.c#L653">653</a>                 break;
<a name="L654" href="source/net/ipv4/ip_sockglue.c#L654">654</a>         case <a href="ident?i=IP_RECVTTL">IP_RECVTTL</a>:
<a name="L655" href="source/net/ipv4/ip_sockglue.c#L655">655</a>                 if (<a href="ident?i=val">val</a>)
<a name="L656" href="source/net/ipv4/ip_sockglue.c#L656">656</a>                         inet-&gt;cmsg_flags |=  <a href="ident?i=IP_CMSG_TTL">IP_CMSG_TTL</a>;
<a name="L657" href="source/net/ipv4/ip_sockglue.c#L657">657</a>                 else
<a name="L658" href="source/net/ipv4/ip_sockglue.c#L658">658</a>                         inet-&gt;cmsg_flags &amp;= ~IP_CMSG_TTL;
<a name="L659" href="source/net/ipv4/ip_sockglue.c#L659">659</a>                 break;
<a name="L660" href="source/net/ipv4/ip_sockglue.c#L660">660</a>         case <a href="ident?i=IP_RECVTOS">IP_RECVTOS</a>:
<a name="L661" href="source/net/ipv4/ip_sockglue.c#L661">661</a>                 if (<a href="ident?i=val">val</a>)
<a name="L662" href="source/net/ipv4/ip_sockglue.c#L662">662</a>                         inet-&gt;cmsg_flags |=  <a href="ident?i=IP_CMSG_TOS">IP_CMSG_TOS</a>;
<a name="L663" href="source/net/ipv4/ip_sockglue.c#L663">663</a>                 else
<a name="L664" href="source/net/ipv4/ip_sockglue.c#L664">664</a>                         inet-&gt;cmsg_flags &amp;= ~IP_CMSG_TOS;
<a name="L665" href="source/net/ipv4/ip_sockglue.c#L665">665</a>                 break;
<a name="L666" href="source/net/ipv4/ip_sockglue.c#L666">666</a>         case <a href="ident?i=IP_RECVOPTS">IP_RECVOPTS</a>:
<a name="L667" href="source/net/ipv4/ip_sockglue.c#L667">667</a>                 if (<a href="ident?i=val">val</a>)
<a name="L668" href="source/net/ipv4/ip_sockglue.c#L668">668</a>                         inet-&gt;cmsg_flags |=  <a href="ident?i=IP_CMSG_RECVOPTS">IP_CMSG_RECVOPTS</a>;
<a name="L669" href="source/net/ipv4/ip_sockglue.c#L669">669</a>                 else
<a name="L670" href="source/net/ipv4/ip_sockglue.c#L670">670</a>                         inet-&gt;cmsg_flags &amp;= ~IP_CMSG_RECVOPTS;
<a name="L671" href="source/net/ipv4/ip_sockglue.c#L671">671</a>                 break;
<a name="L672" href="source/net/ipv4/ip_sockglue.c#L672">672</a>         case <a href="ident?i=IP_RETOPTS">IP_RETOPTS</a>:
<a name="L673" href="source/net/ipv4/ip_sockglue.c#L673">673</a>                 if (<a href="ident?i=val">val</a>)
<a name="L674" href="source/net/ipv4/ip_sockglue.c#L674">674</a>                         inet-&gt;cmsg_flags |= <a href="ident?i=IP_CMSG_RETOPTS">IP_CMSG_RETOPTS</a>;
<a name="L675" href="source/net/ipv4/ip_sockglue.c#L675">675</a>                 else
<a name="L676" href="source/net/ipv4/ip_sockglue.c#L676">676</a>                         inet-&gt;cmsg_flags &amp;= ~IP_CMSG_RETOPTS;
<a name="L677" href="source/net/ipv4/ip_sockglue.c#L677">677</a>                 break;
<a name="L678" href="source/net/ipv4/ip_sockglue.c#L678">678</a>         case <a href="ident?i=IP_PASSSEC">IP_PASSSEC</a>:
<a name="L679" href="source/net/ipv4/ip_sockglue.c#L679">679</a>                 if (<a href="ident?i=val">val</a>)
<a name="L680" href="source/net/ipv4/ip_sockglue.c#L680">680</a>                         inet-&gt;cmsg_flags |= <a href="ident?i=IP_CMSG_PASSSEC">IP_CMSG_PASSSEC</a>;
<a name="L681" href="source/net/ipv4/ip_sockglue.c#L681">681</a>                 else
<a name="L682" href="source/net/ipv4/ip_sockglue.c#L682">682</a>                         inet-&gt;cmsg_flags &amp;= ~IP_CMSG_PASSSEC;
<a name="L683" href="source/net/ipv4/ip_sockglue.c#L683">683</a>                 break;
<a name="L684" href="source/net/ipv4/ip_sockglue.c#L684">684</a>         case <a href="ident?i=IP_RECVORIGDSTADDR">IP_RECVORIGDSTADDR</a>:
<a name="L685" href="source/net/ipv4/ip_sockglue.c#L685">685</a>                 if (<a href="ident?i=val">val</a>)
<a name="L686" href="source/net/ipv4/ip_sockglue.c#L686">686</a>                         inet-&gt;cmsg_flags |= <a href="ident?i=IP_CMSG_ORIGDSTADDR">IP_CMSG_ORIGDSTADDR</a>;
<a name="L687" href="source/net/ipv4/ip_sockglue.c#L687">687</a>                 else
<a name="L688" href="source/net/ipv4/ip_sockglue.c#L688">688</a>                         inet-&gt;cmsg_flags &amp;= ~IP_CMSG_ORIGDSTADDR;
<a name="L689" href="source/net/ipv4/ip_sockglue.c#L689">689</a>                 break;
<a name="L690" href="source/net/ipv4/ip_sockglue.c#L690">690</a>         case <a href="ident?i=IP_CHECKSUM">IP_CHECKSUM</a>:
<a name="L691" href="source/net/ipv4/ip_sockglue.c#L691">691</a>                 if (<a href="ident?i=val">val</a>) {
<a name="L692" href="source/net/ipv4/ip_sockglue.c#L692">692</a>                         if (!(inet-&gt;cmsg_flags &amp; <a href="ident?i=IP_CMSG_CHECKSUM">IP_CMSG_CHECKSUM</a>)) {
<a name="L693" href="source/net/ipv4/ip_sockglue.c#L693">693</a>                                 <a href="ident?i=inet_inc_convert_csum">inet_inc_convert_csum</a>(sk);
<a name="L694" href="source/net/ipv4/ip_sockglue.c#L694">694</a>                                 inet-&gt;cmsg_flags |= <a href="ident?i=IP_CMSG_CHECKSUM">IP_CMSG_CHECKSUM</a>;
<a name="L695" href="source/net/ipv4/ip_sockglue.c#L695">695</a>                         }
<a name="L696" href="source/net/ipv4/ip_sockglue.c#L696">696</a>                 } else {
<a name="L697" href="source/net/ipv4/ip_sockglue.c#L697">697</a>                         if (inet-&gt;cmsg_flags &amp; <a href="ident?i=IP_CMSG_CHECKSUM">IP_CMSG_CHECKSUM</a>) {
<a name="L698" href="source/net/ipv4/ip_sockglue.c#L698">698</a>                                 <a href="ident?i=inet_dec_convert_csum">inet_dec_convert_csum</a>(sk);
<a name="L699" href="source/net/ipv4/ip_sockglue.c#L699">699</a>                                 inet-&gt;cmsg_flags &amp;= ~IP_CMSG_CHECKSUM;
<a name="L700" href="source/net/ipv4/ip_sockglue.c#L700">700</a>                         }
<a name="L701" href="source/net/ipv4/ip_sockglue.c#L701">701</a>                 }
<a name="L702" href="source/net/ipv4/ip_sockglue.c#L702">702</a>                 break;
<a name="L703" href="source/net/ipv4/ip_sockglue.c#L703">703</a>         case <a href="ident?i=IP_TOS">IP_TOS</a>:    <b><i>/* This sets both TOS and Precedence */</i></b>
<a name="L704" href="source/net/ipv4/ip_sockglue.c#L704">704</a>                 if (sk-&gt;sk_type == SOCK_STREAM) {
<a name="L705" href="source/net/ipv4/ip_sockglue.c#L705">705</a>                         <a href="ident?i=val">val</a> &amp;= ~INET_ECN_MASK;
<a name="L706" href="source/net/ipv4/ip_sockglue.c#L706">706</a>                         <a href="ident?i=val">val</a> |= inet-&gt;tos &amp; INET_ECN_MASK;
<a name="L707" href="source/net/ipv4/ip_sockglue.c#L707">707</a>                 }
<a name="L708" href="source/net/ipv4/ip_sockglue.c#L708">708</a>                 if (inet-&gt;tos != <a href="ident?i=val">val</a>) {
<a name="L709" href="source/net/ipv4/ip_sockglue.c#L709">709</a>                         inet-&gt;tos = <a href="ident?i=val">val</a>;
<a name="L710" href="source/net/ipv4/ip_sockglue.c#L710">710</a>                         sk-&gt;sk_priority = <a href="ident?i=rt_tos2priority">rt_tos2priority</a>(<a href="ident?i=val">val</a>);
<a name="L711" href="source/net/ipv4/ip_sockglue.c#L711">711</a>                         <a href="ident?i=sk_dst_reset">sk_dst_reset</a>(sk);
<a name="L712" href="source/net/ipv4/ip_sockglue.c#L712">712</a>                 }
<a name="L713" href="source/net/ipv4/ip_sockglue.c#L713">713</a>                 break;
<a name="L714" href="source/net/ipv4/ip_sockglue.c#L714">714</a>         case <a href="ident?i=IP_TTL">IP_TTL</a>:
<a name="L715" href="source/net/ipv4/ip_sockglue.c#L715">715</a>                 if (<a href="ident?i=optlen">optlen</a> &lt; 1)
<a name="L716" href="source/net/ipv4/ip_sockglue.c#L716">716</a>                         goto e_inval;
<a name="L717" href="source/net/ipv4/ip_sockglue.c#L717">717</a>                 if (<a href="ident?i=val">val</a> != -1 &amp;&amp; (<a href="ident?i=val">val</a> &lt; 1 || <a href="ident?i=val">val</a> &gt; 255))
<a name="L718" href="source/net/ipv4/ip_sockglue.c#L718">718</a>                         goto e_inval;
<a name="L719" href="source/net/ipv4/ip_sockglue.c#L719">719</a>                 inet-&gt;uc_ttl = <a href="ident?i=val">val</a>;
<a name="L720" href="source/net/ipv4/ip_sockglue.c#L720">720</a>                 break;
<a name="L721" href="source/net/ipv4/ip_sockglue.c#L721">721</a>         case <a href="ident?i=IP_HDRINCL">IP_HDRINCL</a>:
<a name="L722" href="source/net/ipv4/ip_sockglue.c#L722">722</a>                 if (sk-&gt;sk_type != SOCK_RAW) {
<a name="L723" href="source/net/ipv4/ip_sockglue.c#L723">723</a>                         <a href="ident?i=err">err</a> = -<a href="ident?i=ENOPROTOOPT">ENOPROTOOPT</a>;
<a name="L724" href="source/net/ipv4/ip_sockglue.c#L724">724</a>                         break;
<a name="L725" href="source/net/ipv4/ip_sockglue.c#L725">725</a>                 }
<a name="L726" href="source/net/ipv4/ip_sockglue.c#L726">726</a>                 inet-&gt;hdrincl = <a href="ident?i=val">val</a> ? 1 : 0;
<a name="L727" href="source/net/ipv4/ip_sockglue.c#L727">727</a>                 break;
<a name="L728" href="source/net/ipv4/ip_sockglue.c#L728">728</a>         case <a href="ident?i=IP_NODEFRAG">IP_NODEFRAG</a>:
<a name="L729" href="source/net/ipv4/ip_sockglue.c#L729">729</a>                 if (sk-&gt;sk_type != SOCK_RAW) {
<a name="L730" href="source/net/ipv4/ip_sockglue.c#L730">730</a>                         <a href="ident?i=err">err</a> = -<a href="ident?i=ENOPROTOOPT">ENOPROTOOPT</a>;
<a name="L731" href="source/net/ipv4/ip_sockglue.c#L731">731</a>                         break;
<a name="L732" href="source/net/ipv4/ip_sockglue.c#L732">732</a>                 }
<a name="L733" href="source/net/ipv4/ip_sockglue.c#L733">733</a>                 inet-&gt;nodefrag = <a href="ident?i=val">val</a> ? 1 : 0;
<a name="L734" href="source/net/ipv4/ip_sockglue.c#L734">734</a>                 break;
<a name="L735" href="source/net/ipv4/ip_sockglue.c#L735">735</a>         case <a href="ident?i=IP_MTU_DISCOVER">IP_MTU_DISCOVER</a>:
<a name="L736" href="source/net/ipv4/ip_sockglue.c#L736">736</a>                 if (<a href="ident?i=val">val</a> &lt; <a href="ident?i=IP_PMTUDISC_DONT">IP_PMTUDISC_DONT</a> || <a href="ident?i=val">val</a> &gt; <a href="ident?i=IP_PMTUDISC_OMIT">IP_PMTUDISC_OMIT</a>)
<a name="L737" href="source/net/ipv4/ip_sockglue.c#L737">737</a>                         goto e_inval;
<a name="L738" href="source/net/ipv4/ip_sockglue.c#L738">738</a>                 inet-&gt;pmtudisc = <a href="ident?i=val">val</a>;
<a name="L739" href="source/net/ipv4/ip_sockglue.c#L739">739</a>                 break;
<a name="L740" href="source/net/ipv4/ip_sockglue.c#L740">740</a>         case <a href="ident?i=IP_RECVERR">IP_RECVERR</a>:
<a name="L741" href="source/net/ipv4/ip_sockglue.c#L741">741</a>                 inet-&gt;recverr = !!<a href="ident?i=val">val</a>;
<a name="L742" href="source/net/ipv4/ip_sockglue.c#L742">742</a>                 if (!<a href="ident?i=val">val</a>)
<a name="L743" href="source/net/ipv4/ip_sockglue.c#L743">743</a>                         <a href="ident?i=skb_queue_purge">skb_queue_purge</a>(&amp;sk-&gt;sk_error_queue);
<a name="L744" href="source/net/ipv4/ip_sockglue.c#L744">744</a>                 break;
<a name="L745" href="source/net/ipv4/ip_sockglue.c#L745">745</a>         case <a href="ident?i=IP_MULTICAST_TTL">IP_MULTICAST_TTL</a>:
<a name="L746" href="source/net/ipv4/ip_sockglue.c#L746">746</a>                 if (sk-&gt;sk_type == SOCK_STREAM)
<a name="L747" href="source/net/ipv4/ip_sockglue.c#L747">747</a>                         goto e_inval;
<a name="L748" href="source/net/ipv4/ip_sockglue.c#L748">748</a>                 if (<a href="ident?i=optlen">optlen</a> &lt; 1)
<a name="L749" href="source/net/ipv4/ip_sockglue.c#L749">749</a>                         goto e_inval;
<a name="L750" href="source/net/ipv4/ip_sockglue.c#L750">750</a>                 if (<a href="ident?i=val">val</a> == -1)
<a name="L751" href="source/net/ipv4/ip_sockglue.c#L751">751</a>                         <a href="ident?i=val">val</a> = 1;
<a name="L752" href="source/net/ipv4/ip_sockglue.c#L752">752</a>                 if (<a href="ident?i=val">val</a> &lt; 0 || <a href="ident?i=val">val</a> &gt; 255)
<a name="L753" href="source/net/ipv4/ip_sockglue.c#L753">753</a>                         goto e_inval;
<a name="L754" href="source/net/ipv4/ip_sockglue.c#L754">754</a>                 inet-&gt;mc_ttl = <a href="ident?i=val">val</a>;
<a name="L755" href="source/net/ipv4/ip_sockglue.c#L755">755</a>                 break;
<a name="L756" href="source/net/ipv4/ip_sockglue.c#L756">756</a>         case <a href="ident?i=IP_MULTICAST_LOOP">IP_MULTICAST_LOOP</a>:
<a name="L757" href="source/net/ipv4/ip_sockglue.c#L757">757</a>                 if (<a href="ident?i=optlen">optlen</a> &lt; 1)
<a name="L758" href="source/net/ipv4/ip_sockglue.c#L758">758</a>                         goto e_inval;
<a name="L759" href="source/net/ipv4/ip_sockglue.c#L759">759</a>                 inet-&gt;mc_loop = !!<a href="ident?i=val">val</a>;
<a name="L760" href="source/net/ipv4/ip_sockglue.c#L760">760</a>                 break;
<a name="L761" href="source/net/ipv4/ip_sockglue.c#L761">761</a>         case <a href="ident?i=IP_UNICAST_IF">IP_UNICAST_IF</a>:
<a name="L762" href="source/net/ipv4/ip_sockglue.c#L762">762</a>         {
<a name="L763" href="source/net/ipv4/ip_sockglue.c#L763">763</a>                 struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a> = <a href="ident?i=NULL">NULL</a>;
<a name="L764" href="source/net/ipv4/ip_sockglue.c#L764">764</a>                 int ifindex;
<a name="L765" href="source/net/ipv4/ip_sockglue.c#L765">765</a> 
<a name="L766" href="source/net/ipv4/ip_sockglue.c#L766">766</a>                 if (<a href="ident?i=optlen">optlen</a> != sizeof(int))
<a name="L767" href="source/net/ipv4/ip_sockglue.c#L767">767</a>                         goto e_inval;
<a name="L768" href="source/net/ipv4/ip_sockglue.c#L768">768</a> 
<a name="L769" href="source/net/ipv4/ip_sockglue.c#L769">769</a>                 ifindex = (<a href="ident?i=__force">__force</a> int)<a href="ident?i=ntohl">ntohl</a>((<a href="ident?i=__force">__force</a> <a href="ident?i=__be32">__be32</a>)<a href="ident?i=val">val</a>);
<a name="L770" href="source/net/ipv4/ip_sockglue.c#L770">770</a>                 if (ifindex == 0) {
<a name="L771" href="source/net/ipv4/ip_sockglue.c#L771">771</a>                         inet-&gt;uc_index = 0;
<a name="L772" href="source/net/ipv4/ip_sockglue.c#L772">772</a>                         <a href="ident?i=err">err</a> = 0;
<a name="L773" href="source/net/ipv4/ip_sockglue.c#L773">773</a>                         break;
<a name="L774" href="source/net/ipv4/ip_sockglue.c#L774">774</a>                 }
<a name="L775" href="source/net/ipv4/ip_sockglue.c#L775">775</a> 
<a name="L776" href="source/net/ipv4/ip_sockglue.c#L776">776</a>                 <a href="ident?i=dev">dev</a> = <a href="ident?i=dev_get_by_index">dev_get_by_index</a>(<a href="ident?i=sock_net">sock_net</a>(sk), ifindex);
<a name="L777" href="source/net/ipv4/ip_sockglue.c#L777">777</a>                 <a href="ident?i=err">err</a> = -<a href="ident?i=EADDRNOTAVAIL">EADDRNOTAVAIL</a>;
<a name="L778" href="source/net/ipv4/ip_sockglue.c#L778">778</a>                 if (!<a href="ident?i=dev">dev</a>)
<a name="L779" href="source/net/ipv4/ip_sockglue.c#L779">779</a>                         break;
<a name="L780" href="source/net/ipv4/ip_sockglue.c#L780">780</a>                 <a href="ident?i=dev_put">dev_put</a>(<a href="ident?i=dev">dev</a>);
<a name="L781" href="source/net/ipv4/ip_sockglue.c#L781">781</a> 
<a name="L782" href="source/net/ipv4/ip_sockglue.c#L782">782</a>                 <a href="ident?i=err">err</a> = -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L783" href="source/net/ipv4/ip_sockglue.c#L783">783</a>                 if (sk-&gt;<a href="ident?i=sk_bound_dev_if">sk_bound_dev_if</a>)
<a name="L784" href="source/net/ipv4/ip_sockglue.c#L784">784</a>                         break;
<a name="L785" href="source/net/ipv4/ip_sockglue.c#L785">785</a> 
<a name="L786" href="source/net/ipv4/ip_sockglue.c#L786">786</a>                 inet-&gt;uc_index = ifindex;
<a name="L787" href="source/net/ipv4/ip_sockglue.c#L787">787</a>                 <a href="ident?i=err">err</a> = 0;
<a name="L788" href="source/net/ipv4/ip_sockglue.c#L788">788</a>                 break;
<a name="L789" href="source/net/ipv4/ip_sockglue.c#L789">789</a>         }
<a name="L790" href="source/net/ipv4/ip_sockglue.c#L790">790</a>         case <a href="ident?i=IP_MULTICAST_IF">IP_MULTICAST_IF</a>:
<a name="L791" href="source/net/ipv4/ip_sockglue.c#L791">791</a>         {
<a name="L792" href="source/net/ipv4/ip_sockglue.c#L792">792</a>                 struct <a href="ident?i=ip_mreqn">ip_mreqn</a> mreq;
<a name="L793" href="source/net/ipv4/ip_sockglue.c#L793">793</a>                 struct <a href="ident?i=net_device">net_device</a> *<a href="ident?i=dev">dev</a> = <a href="ident?i=NULL">NULL</a>;
<a name="L794" href="source/net/ipv4/ip_sockglue.c#L794">794</a> 
<a name="L795" href="source/net/ipv4/ip_sockglue.c#L795">795</a>                 if (sk-&gt;sk_type == SOCK_STREAM)
<a name="L796" href="source/net/ipv4/ip_sockglue.c#L796">796</a>                         goto e_inval;
<a name="L797" href="source/net/ipv4/ip_sockglue.c#L797">797</a>                 <b><i>/*</i></b>
<a name="L798" href="source/net/ipv4/ip_sockglue.c#L798">798</a> <b><i>                 *      Check the arguments are allowable</i></b>
<a name="L799" href="source/net/ipv4/ip_sockglue.c#L799">799</a> <b><i>                 */</i></b>
<a name="L800" href="source/net/ipv4/ip_sockglue.c#L800">800</a> 
<a name="L801" href="source/net/ipv4/ip_sockglue.c#L801">801</a>                 if (<a href="ident?i=optlen">optlen</a> &lt; sizeof(struct <a href="ident?i=in_addr">in_addr</a>))
<a name="L802" href="source/net/ipv4/ip_sockglue.c#L802">802</a>                         goto e_inval;
<a name="L803" href="source/net/ipv4/ip_sockglue.c#L803">803</a> 
<a name="L804" href="source/net/ipv4/ip_sockglue.c#L804">804</a>                 <a href="ident?i=err">err</a> = -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L805" href="source/net/ipv4/ip_sockglue.c#L805">805</a>                 if (<a href="ident?i=optlen">optlen</a> &gt;= sizeof(struct <a href="ident?i=ip_mreqn">ip_mreqn</a>)) {
<a name="L806" href="source/net/ipv4/ip_sockglue.c#L806">806</a>                         if (<a href="ident?i=copy_from_user">copy_from_user</a>(&amp;mreq, optval, sizeof(mreq)))
<a name="L807" href="source/net/ipv4/ip_sockglue.c#L807">807</a>                                 break;
<a name="L808" href="source/net/ipv4/ip_sockglue.c#L808">808</a>                 } else {
<a name="L809" href="source/net/ipv4/ip_sockglue.c#L809">809</a>                         <a href="ident?i=memset">memset</a>(&amp;mreq, 0, sizeof(mreq));
<a name="L810" href="source/net/ipv4/ip_sockglue.c#L810">810</a>                         if (<a href="ident?i=optlen">optlen</a> &gt;= sizeof(struct <a href="ident?i=ip_mreq">ip_mreq</a>)) {
<a name="L811" href="source/net/ipv4/ip_sockglue.c#L811">811</a>                                 if (<a href="ident?i=copy_from_user">copy_from_user</a>(&amp;mreq, optval,
<a name="L812" href="source/net/ipv4/ip_sockglue.c#L812">812</a>                                                    sizeof(struct <a href="ident?i=ip_mreq">ip_mreq</a>)))
<a name="L813" href="source/net/ipv4/ip_sockglue.c#L813">813</a>                                         break;
<a name="L814" href="source/net/ipv4/ip_sockglue.c#L814">814</a>                         } else if (<a href="ident?i=optlen">optlen</a> &gt;= sizeof(struct <a href="ident?i=in_addr">in_addr</a>)) {
<a name="L815" href="source/net/ipv4/ip_sockglue.c#L815">815</a>                                 if (<a href="ident?i=copy_from_user">copy_from_user</a>(&amp;mreq.imr_address, optval,
<a name="L816" href="source/net/ipv4/ip_sockglue.c#L816">816</a>                                                    sizeof(struct <a href="ident?i=in_addr">in_addr</a>)))
<a name="L817" href="source/net/ipv4/ip_sockglue.c#L817">817</a>                                         break;
<a name="L818" href="source/net/ipv4/ip_sockglue.c#L818">818</a>                         }
<a name="L819" href="source/net/ipv4/ip_sockglue.c#L819">819</a>                 }
<a name="L820" href="source/net/ipv4/ip_sockglue.c#L820">820</a> 
<a name="L821" href="source/net/ipv4/ip_sockglue.c#L821">821</a>                 if (!mreq.imr_ifindex) {
<a name="L822" href="source/net/ipv4/ip_sockglue.c#L822">822</a>                         if (mreq.imr_address.s_addr == <a href="ident?i=htonl">htonl</a>(<a href="ident?i=INADDR_ANY">INADDR_ANY</a>)) {
<a name="L823" href="source/net/ipv4/ip_sockglue.c#L823">823</a>                                 inet-&gt;mc_index = 0;
<a name="L824" href="source/net/ipv4/ip_sockglue.c#L824">824</a>                                 inet-&gt;mc_addr  = 0;
<a name="L825" href="source/net/ipv4/ip_sockglue.c#L825">825</a>                                 <a href="ident?i=err">err</a> = 0;
<a name="L826" href="source/net/ipv4/ip_sockglue.c#L826">826</a>                                 break;
<a name="L827" href="source/net/ipv4/ip_sockglue.c#L827">827</a>                         }
<a name="L828" href="source/net/ipv4/ip_sockglue.c#L828">828</a>                         <a href="ident?i=dev">dev</a> = <a href="ident?i=ip_dev_find">ip_dev_find</a>(<a href="ident?i=sock_net">sock_net</a>(sk), mreq.imr_address.s_addr);
<a name="L829" href="source/net/ipv4/ip_sockglue.c#L829">829</a>                         if (<a href="ident?i=dev">dev</a>)
<a name="L830" href="source/net/ipv4/ip_sockglue.c#L830">830</a>                                 mreq.imr_ifindex = <a href="ident?i=dev">dev</a>-&gt;ifindex;
<a name="L831" href="source/net/ipv4/ip_sockglue.c#L831">831</a>                 } else
<a name="L832" href="source/net/ipv4/ip_sockglue.c#L832">832</a>                         <a href="ident?i=dev">dev</a> = <a href="ident?i=dev_get_by_index">dev_get_by_index</a>(<a href="ident?i=sock_net">sock_net</a>(sk), mreq.imr_ifindex);
<a name="L833" href="source/net/ipv4/ip_sockglue.c#L833">833</a> 
<a name="L834" href="source/net/ipv4/ip_sockglue.c#L834">834</a> 
<a name="L835" href="source/net/ipv4/ip_sockglue.c#L835">835</a>                 <a href="ident?i=err">err</a> = -<a href="ident?i=EADDRNOTAVAIL">EADDRNOTAVAIL</a>;
<a name="L836" href="source/net/ipv4/ip_sockglue.c#L836">836</a>                 if (!<a href="ident?i=dev">dev</a>)
<a name="L837" href="source/net/ipv4/ip_sockglue.c#L837">837</a>                         break;
<a name="L838" href="source/net/ipv4/ip_sockglue.c#L838">838</a>                 <a href="ident?i=dev_put">dev_put</a>(<a href="ident?i=dev">dev</a>);
<a name="L839" href="source/net/ipv4/ip_sockglue.c#L839">839</a> 
<a name="L840" href="source/net/ipv4/ip_sockglue.c#L840">840</a>                 <a href="ident?i=err">err</a> = -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L841" href="source/net/ipv4/ip_sockglue.c#L841">841</a>                 if (sk-&gt;<a href="ident?i=sk_bound_dev_if">sk_bound_dev_if</a> &amp;&amp;
<a name="L842" href="source/net/ipv4/ip_sockglue.c#L842">842</a>                     mreq.imr_ifindex != sk-&gt;<a href="ident?i=sk_bound_dev_if">sk_bound_dev_if</a>)
<a name="L843" href="source/net/ipv4/ip_sockglue.c#L843">843</a>                         break;
<a name="L844" href="source/net/ipv4/ip_sockglue.c#L844">844</a> 
<a name="L845" href="source/net/ipv4/ip_sockglue.c#L845">845</a>                 inet-&gt;mc_index = mreq.imr_ifindex;
<a name="L846" href="source/net/ipv4/ip_sockglue.c#L846">846</a>                 inet-&gt;mc_addr  = mreq.imr_address.s_addr;
<a name="L847" href="source/net/ipv4/ip_sockglue.c#L847">847</a>                 <a href="ident?i=err">err</a> = 0;
<a name="L848" href="source/net/ipv4/ip_sockglue.c#L848">848</a>                 break;
<a name="L849" href="source/net/ipv4/ip_sockglue.c#L849">849</a>         }
<a name="L850" href="source/net/ipv4/ip_sockglue.c#L850">850</a> 
<a name="L851" href="source/net/ipv4/ip_sockglue.c#L851">851</a>         case <a href="ident?i=IP_ADD_MEMBERSHIP">IP_ADD_MEMBERSHIP</a>:
<a name="L852" href="source/net/ipv4/ip_sockglue.c#L852">852</a>         case <a href="ident?i=IP_DROP_MEMBERSHIP">IP_DROP_MEMBERSHIP</a>:
<a name="L853" href="source/net/ipv4/ip_sockglue.c#L853">853</a>         {
<a name="L854" href="source/net/ipv4/ip_sockglue.c#L854">854</a>                 struct <a href="ident?i=ip_mreqn">ip_mreqn</a> mreq;
<a name="L855" href="source/net/ipv4/ip_sockglue.c#L855">855</a> 
<a name="L856" href="source/net/ipv4/ip_sockglue.c#L856">856</a>                 <a href="ident?i=err">err</a> = -<a href="ident?i=EPROTO">EPROTO</a>;
<a name="L857" href="source/net/ipv4/ip_sockglue.c#L857">857</a>                 if (<a href="ident?i=inet_sk">inet_sk</a>(sk)-&gt;is_icsk)
<a name="L858" href="source/net/ipv4/ip_sockglue.c#L858">858</a>                         break;
<a name="L859" href="source/net/ipv4/ip_sockglue.c#L859">859</a> 
<a name="L860" href="source/net/ipv4/ip_sockglue.c#L860">860</a>                 if (<a href="ident?i=optlen">optlen</a> &lt; sizeof(struct <a href="ident?i=ip_mreq">ip_mreq</a>))
<a name="L861" href="source/net/ipv4/ip_sockglue.c#L861">861</a>                         goto e_inval;
<a name="L862" href="source/net/ipv4/ip_sockglue.c#L862">862</a>                 <a href="ident?i=err">err</a> = -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L863" href="source/net/ipv4/ip_sockglue.c#L863">863</a>                 if (<a href="ident?i=optlen">optlen</a> &gt;= sizeof(struct <a href="ident?i=ip_mreqn">ip_mreqn</a>)) {
<a name="L864" href="source/net/ipv4/ip_sockglue.c#L864">864</a>                         if (<a href="ident?i=copy_from_user">copy_from_user</a>(&amp;mreq, optval, sizeof(mreq)))
<a name="L865" href="source/net/ipv4/ip_sockglue.c#L865">865</a>                                 break;
<a name="L866" href="source/net/ipv4/ip_sockglue.c#L866">866</a>                 } else {
<a name="L867" href="source/net/ipv4/ip_sockglue.c#L867">867</a>                         <a href="ident?i=memset">memset</a>(&amp;mreq, 0, sizeof(mreq));
<a name="L868" href="source/net/ipv4/ip_sockglue.c#L868">868</a>                         if (<a href="ident?i=copy_from_user">copy_from_user</a>(&amp;mreq, optval, sizeof(struct <a href="ident?i=ip_mreq">ip_mreq</a>)))
<a name="L869" href="source/net/ipv4/ip_sockglue.c#L869">869</a>                                 break;
<a name="L870" href="source/net/ipv4/ip_sockglue.c#L870">870</a>                 }
<a name="L871" href="source/net/ipv4/ip_sockglue.c#L871">871</a> 
<a name="L872" href="source/net/ipv4/ip_sockglue.c#L872">872</a>                 if (optname == <a href="ident?i=IP_ADD_MEMBERSHIP">IP_ADD_MEMBERSHIP</a>)
<a name="L873" href="source/net/ipv4/ip_sockglue.c#L873">873</a>                         <a href="ident?i=err">err</a> = <a href="ident?i=ip_mc_join_group">ip_mc_join_group</a>(sk, &amp;mreq);
<a name="L874" href="source/net/ipv4/ip_sockglue.c#L874">874</a>                 else
<a name="L875" href="source/net/ipv4/ip_sockglue.c#L875">875</a>                         <a href="ident?i=err">err</a> = <a href="ident?i=ip_mc_leave_group">ip_mc_leave_group</a>(sk, &amp;mreq);
<a name="L876" href="source/net/ipv4/ip_sockglue.c#L876">876</a>                 break;
<a name="L877" href="source/net/ipv4/ip_sockglue.c#L877">877</a>         }
<a name="L878" href="source/net/ipv4/ip_sockglue.c#L878">878</a>         case <a href="ident?i=IP_MSFILTER">IP_MSFILTER</a>:
<a name="L879" href="source/net/ipv4/ip_sockglue.c#L879">879</a>         {
<a name="L880" href="source/net/ipv4/ip_sockglue.c#L880">880</a>                 struct <a href="ident?i=ip_msfilter">ip_msfilter</a> *msf;
<a name="L881" href="source/net/ipv4/ip_sockglue.c#L881">881</a> 
<a name="L882" href="source/net/ipv4/ip_sockglue.c#L882">882</a>                 if (<a href="ident?i=optlen">optlen</a> &lt; <a href="ident?i=IP_MSFILTER_SIZE">IP_MSFILTER_SIZE</a>(0))
<a name="L883" href="source/net/ipv4/ip_sockglue.c#L883">883</a>                         goto e_inval;
<a name="L884" href="source/net/ipv4/ip_sockglue.c#L884">884</a>                 if (<a href="ident?i=optlen">optlen</a> &gt; <a href="ident?i=sysctl_optmem_max">sysctl_optmem_max</a>) {
<a name="L885" href="source/net/ipv4/ip_sockglue.c#L885">885</a>                         <a href="ident?i=err">err</a> = -<a href="ident?i=ENOBUFS">ENOBUFS</a>;
<a name="L886" href="source/net/ipv4/ip_sockglue.c#L886">886</a>                         break;
<a name="L887" href="source/net/ipv4/ip_sockglue.c#L887">887</a>                 }
<a name="L888" href="source/net/ipv4/ip_sockglue.c#L888">888</a>                 msf = <a href="ident?i=kmalloc">kmalloc</a>(<a href="ident?i=optlen">optlen</a>, <a href="ident?i=GFP_KERNEL">GFP_KERNEL</a>);
<a name="L889" href="source/net/ipv4/ip_sockglue.c#L889">889</a>                 if (!msf) {
<a name="L890" href="source/net/ipv4/ip_sockglue.c#L890">890</a>                         <a href="ident?i=err">err</a> = -<a href="ident?i=ENOBUFS">ENOBUFS</a>;
<a name="L891" href="source/net/ipv4/ip_sockglue.c#L891">891</a>                         break;
<a name="L892" href="source/net/ipv4/ip_sockglue.c#L892">892</a>                 }
<a name="L893" href="source/net/ipv4/ip_sockglue.c#L893">893</a>                 <a href="ident?i=err">err</a> = -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L894" href="source/net/ipv4/ip_sockglue.c#L894">894</a>                 if (<a href="ident?i=copy_from_user">copy_from_user</a>(msf, optval, <a href="ident?i=optlen">optlen</a>)) {
<a name="L895" href="source/net/ipv4/ip_sockglue.c#L895">895</a>                         <a href="ident?i=kfree">kfree</a>(msf);
<a name="L896" href="source/net/ipv4/ip_sockglue.c#L896">896</a>                         break;
<a name="L897" href="source/net/ipv4/ip_sockglue.c#L897">897</a>                 }
<a name="L898" href="source/net/ipv4/ip_sockglue.c#L898">898</a>                 <b><i>/* numsrc &gt;= (1G-4) overflow in 32 bits */</i></b>
<a name="L899" href="source/net/ipv4/ip_sockglue.c#L899">899</a>                 if (msf-&gt;imsf_numsrc &gt;= 0x3ffffffcU ||
<a name="L900" href="source/net/ipv4/ip_sockglue.c#L900">900</a>                     msf-&gt;imsf_numsrc &gt; <a href="ident?i=sysctl_igmp_max_msf">sysctl_igmp_max_msf</a>) {
<a name="L901" href="source/net/ipv4/ip_sockglue.c#L901">901</a>                         <a href="ident?i=kfree">kfree</a>(msf);
<a name="L902" href="source/net/ipv4/ip_sockglue.c#L902">902</a>                         <a href="ident?i=err">err</a> = -<a href="ident?i=ENOBUFS">ENOBUFS</a>;
<a name="L903" href="source/net/ipv4/ip_sockglue.c#L903">903</a>                         break;
<a name="L904" href="source/net/ipv4/ip_sockglue.c#L904">904</a>                 }
<a name="L905" href="source/net/ipv4/ip_sockglue.c#L905">905</a>                 if (<a href="ident?i=IP_MSFILTER_SIZE">IP_MSFILTER_SIZE</a>(msf-&gt;imsf_numsrc) &gt; <a href="ident?i=optlen">optlen</a>) {
<a name="L906" href="source/net/ipv4/ip_sockglue.c#L906">906</a>                         <a href="ident?i=kfree">kfree</a>(msf);
<a name="L907" href="source/net/ipv4/ip_sockglue.c#L907">907</a>                         <a href="ident?i=err">err</a> = -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L908" href="source/net/ipv4/ip_sockglue.c#L908">908</a>                         break;
<a name="L909" href="source/net/ipv4/ip_sockglue.c#L909">909</a>                 }
<a name="L910" href="source/net/ipv4/ip_sockglue.c#L910">910</a>                 <a href="ident?i=err">err</a> = <a href="ident?i=ip_mc_msfilter">ip_mc_msfilter</a>(sk, msf, 0);
<a name="L911" href="source/net/ipv4/ip_sockglue.c#L911">911</a>                 <a href="ident?i=kfree">kfree</a>(msf);
<a name="L912" href="source/net/ipv4/ip_sockglue.c#L912">912</a>                 break;
<a name="L913" href="source/net/ipv4/ip_sockglue.c#L913">913</a>         }
<a name="L914" href="source/net/ipv4/ip_sockglue.c#L914">914</a>         case <a href="ident?i=IP_BLOCK_SOURCE">IP_BLOCK_SOURCE</a>:
<a name="L915" href="source/net/ipv4/ip_sockglue.c#L915">915</a>         case <a href="ident?i=IP_UNBLOCK_SOURCE">IP_UNBLOCK_SOURCE</a>:
<a name="L916" href="source/net/ipv4/ip_sockglue.c#L916">916</a>         case <a href="ident?i=IP_ADD_SOURCE_MEMBERSHIP">IP_ADD_SOURCE_MEMBERSHIP</a>:
<a name="L917" href="source/net/ipv4/ip_sockglue.c#L917">917</a>         case <a href="ident?i=IP_DROP_SOURCE_MEMBERSHIP">IP_DROP_SOURCE_MEMBERSHIP</a>:
<a name="L918" href="source/net/ipv4/ip_sockglue.c#L918">918</a>         {
<a name="L919" href="source/net/ipv4/ip_sockglue.c#L919">919</a>                 struct <a href="ident?i=ip_mreq_source">ip_mreq_source</a> mreqs;
<a name="L920" href="source/net/ipv4/ip_sockglue.c#L920">920</a>                 int omode, add;
<a name="L921" href="source/net/ipv4/ip_sockglue.c#L921">921</a> 
<a name="L922" href="source/net/ipv4/ip_sockglue.c#L922">922</a>                 if (<a href="ident?i=optlen">optlen</a> != sizeof(struct <a href="ident?i=ip_mreq_source">ip_mreq_source</a>))
<a name="L923" href="source/net/ipv4/ip_sockglue.c#L923">923</a>                         goto e_inval;
<a name="L924" href="source/net/ipv4/ip_sockglue.c#L924">924</a>                 if (<a href="ident?i=copy_from_user">copy_from_user</a>(&amp;mreqs, optval, sizeof(mreqs))) {
<a name="L925" href="source/net/ipv4/ip_sockglue.c#L925">925</a>                         <a href="ident?i=err">err</a> = -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L926" href="source/net/ipv4/ip_sockglue.c#L926">926</a>                         break;
<a name="L927" href="source/net/ipv4/ip_sockglue.c#L927">927</a>                 }
<a name="L928" href="source/net/ipv4/ip_sockglue.c#L928">928</a>                 if (optname == <a href="ident?i=IP_BLOCK_SOURCE">IP_BLOCK_SOURCE</a>) {
<a name="L929" href="source/net/ipv4/ip_sockglue.c#L929">929</a>                         omode = <a href="ident?i=MCAST_EXCLUDE">MCAST_EXCLUDE</a>;
<a name="L930" href="source/net/ipv4/ip_sockglue.c#L930">930</a>                         add = 1;
<a name="L931" href="source/net/ipv4/ip_sockglue.c#L931">931</a>                 } else if (optname == <a href="ident?i=IP_UNBLOCK_SOURCE">IP_UNBLOCK_SOURCE</a>) {
<a name="L932" href="source/net/ipv4/ip_sockglue.c#L932">932</a>                         omode = <a href="ident?i=MCAST_EXCLUDE">MCAST_EXCLUDE</a>;
<a name="L933" href="source/net/ipv4/ip_sockglue.c#L933">933</a>                         add = 0;
<a name="L934" href="source/net/ipv4/ip_sockglue.c#L934">934</a>                 } else if (optname == <a href="ident?i=IP_ADD_SOURCE_MEMBERSHIP">IP_ADD_SOURCE_MEMBERSHIP</a>) {
<a name="L935" href="source/net/ipv4/ip_sockglue.c#L935">935</a>                         struct <a href="ident?i=ip_mreqn">ip_mreqn</a> mreq;
<a name="L936" href="source/net/ipv4/ip_sockglue.c#L936">936</a> 
<a name="L937" href="source/net/ipv4/ip_sockglue.c#L937">937</a>                         mreq.imr_multiaddr.s_addr = mreqs.imr_multiaddr;
<a name="L938" href="source/net/ipv4/ip_sockglue.c#L938">938</a>                         mreq.imr_address.s_addr = mreqs.imr_interface;
<a name="L939" href="source/net/ipv4/ip_sockglue.c#L939">939</a>                         mreq.imr_ifindex = 0;
<a name="L940" href="source/net/ipv4/ip_sockglue.c#L940">940</a>                         <a href="ident?i=err">err</a> = <a href="ident?i=ip_mc_join_group">ip_mc_join_group</a>(sk, &amp;mreq);
<a name="L941" href="source/net/ipv4/ip_sockglue.c#L941">941</a>                         if (<a href="ident?i=err">err</a> &amp;&amp; <a href="ident?i=err">err</a> != -<a href="ident?i=EADDRINUSE">EADDRINUSE</a>)
<a name="L942" href="source/net/ipv4/ip_sockglue.c#L942">942</a>                                 break;
<a name="L943" href="source/net/ipv4/ip_sockglue.c#L943">943</a>                         omode = <a href="ident?i=MCAST_INCLUDE">MCAST_INCLUDE</a>;
<a name="L944" href="source/net/ipv4/ip_sockglue.c#L944">944</a>                         add = 1;
<a name="L945" href="source/net/ipv4/ip_sockglue.c#L945">945</a>                 } else <b><i>/* IP_DROP_SOURCE_MEMBERSHIP */</i></b> {
<a name="L946" href="source/net/ipv4/ip_sockglue.c#L946">946</a>                         omode = <a href="ident?i=MCAST_INCLUDE">MCAST_INCLUDE</a>;
<a name="L947" href="source/net/ipv4/ip_sockglue.c#L947">947</a>                         add = 0;
<a name="L948" href="source/net/ipv4/ip_sockglue.c#L948">948</a>                 }
<a name="L949" href="source/net/ipv4/ip_sockglue.c#L949">949</a>                 <a href="ident?i=err">err</a> = <a href="ident?i=ip_mc_source">ip_mc_source</a>(add, omode, sk, &amp;mreqs, 0);
<a name="L950" href="source/net/ipv4/ip_sockglue.c#L950">950</a>                 break;
<a name="L951" href="source/net/ipv4/ip_sockglue.c#L951">951</a>         }
<a name="L952" href="source/net/ipv4/ip_sockglue.c#L952">952</a>         case <a href="ident?i=MCAST_JOIN_GROUP">MCAST_JOIN_GROUP</a>:
<a name="L953" href="source/net/ipv4/ip_sockglue.c#L953">953</a>         case <a href="ident?i=MCAST_LEAVE_GROUP">MCAST_LEAVE_GROUP</a>:
<a name="L954" href="source/net/ipv4/ip_sockglue.c#L954">954</a>         {
<a name="L955" href="source/net/ipv4/ip_sockglue.c#L955">955</a>                 struct <a href="ident?i=group_req">group_req</a> greq;
<a name="L956" href="source/net/ipv4/ip_sockglue.c#L956">956</a>                 struct <a href="ident?i=sockaddr_in">sockaddr_in</a> *psin;
<a name="L957" href="source/net/ipv4/ip_sockglue.c#L957">957</a>                 struct <a href="ident?i=ip_mreqn">ip_mreqn</a> mreq;
<a name="L958" href="source/net/ipv4/ip_sockglue.c#L958">958</a> 
<a name="L959" href="source/net/ipv4/ip_sockglue.c#L959">959</a>                 if (<a href="ident?i=optlen">optlen</a> &lt; sizeof(struct <a href="ident?i=group_req">group_req</a>))
<a name="L960" href="source/net/ipv4/ip_sockglue.c#L960">960</a>                         goto e_inval;
<a name="L961" href="source/net/ipv4/ip_sockglue.c#L961">961</a>                 <a href="ident?i=err">err</a> = -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L962" href="source/net/ipv4/ip_sockglue.c#L962">962</a>                 if (<a href="ident?i=copy_from_user">copy_from_user</a>(&amp;greq, optval, sizeof(greq)))
<a name="L963" href="source/net/ipv4/ip_sockglue.c#L963">963</a>                         break;
<a name="L964" href="source/net/ipv4/ip_sockglue.c#L964">964</a>                 psin = (struct <a href="ident?i=sockaddr_in">sockaddr_in</a> *)&amp;greq.gr_group;
<a name="L965" href="source/net/ipv4/ip_sockglue.c#L965">965</a>                 if (psin-&gt;sin_family != <a href="ident?i=AF_INET">AF_INET</a>)
<a name="L966" href="source/net/ipv4/ip_sockglue.c#L966">966</a>                         goto e_inval;
<a name="L967" href="source/net/ipv4/ip_sockglue.c#L967">967</a>                 <a href="ident?i=memset">memset</a>(&amp;mreq, 0, sizeof(mreq));
<a name="L968" href="source/net/ipv4/ip_sockglue.c#L968">968</a>                 mreq.imr_multiaddr = psin-&gt;sin_addr;
<a name="L969" href="source/net/ipv4/ip_sockglue.c#L969">969</a>                 mreq.imr_ifindex = greq.gr_interface;
<a name="L970" href="source/net/ipv4/ip_sockglue.c#L970">970</a> 
<a name="L971" href="source/net/ipv4/ip_sockglue.c#L971">971</a>                 if (optname == <a href="ident?i=MCAST_JOIN_GROUP">MCAST_JOIN_GROUP</a>)
<a name="L972" href="source/net/ipv4/ip_sockglue.c#L972">972</a>                         <a href="ident?i=err">err</a> = <a href="ident?i=ip_mc_join_group">ip_mc_join_group</a>(sk, &amp;mreq);
<a name="L973" href="source/net/ipv4/ip_sockglue.c#L973">973</a>                 else
<a name="L974" href="source/net/ipv4/ip_sockglue.c#L974">974</a>                         <a href="ident?i=err">err</a> = <a href="ident?i=ip_mc_leave_group">ip_mc_leave_group</a>(sk, &amp;mreq);
<a name="L975" href="source/net/ipv4/ip_sockglue.c#L975">975</a>                 break;
<a name="L976" href="source/net/ipv4/ip_sockglue.c#L976">976</a>         }
<a name="L977" href="source/net/ipv4/ip_sockglue.c#L977">977</a>         case <a href="ident?i=MCAST_JOIN_SOURCE_GROUP">MCAST_JOIN_SOURCE_GROUP</a>:
<a name="L978" href="source/net/ipv4/ip_sockglue.c#L978">978</a>         case <a href="ident?i=MCAST_LEAVE_SOURCE_GROUP">MCAST_LEAVE_SOURCE_GROUP</a>:
<a name="L979" href="source/net/ipv4/ip_sockglue.c#L979">979</a>         case <a href="ident?i=MCAST_BLOCK_SOURCE">MCAST_BLOCK_SOURCE</a>:
<a name="L980" href="source/net/ipv4/ip_sockglue.c#L980">980</a>         case <a href="ident?i=MCAST_UNBLOCK_SOURCE">MCAST_UNBLOCK_SOURCE</a>:
<a name="L981" href="source/net/ipv4/ip_sockglue.c#L981">981</a>         {
<a name="L982" href="source/net/ipv4/ip_sockglue.c#L982">982</a>                 struct <a href="ident?i=group_source_req">group_source_req</a> greqs;
<a name="L983" href="source/net/ipv4/ip_sockglue.c#L983">983</a>                 struct <a href="ident?i=ip_mreq_source">ip_mreq_source</a> mreqs;
<a name="L984" href="source/net/ipv4/ip_sockglue.c#L984">984</a>                 struct <a href="ident?i=sockaddr_in">sockaddr_in</a> *psin;
<a name="L985" href="source/net/ipv4/ip_sockglue.c#L985">985</a>                 int omode, add;
<a name="L986" href="source/net/ipv4/ip_sockglue.c#L986">986</a> 
<a name="L987" href="source/net/ipv4/ip_sockglue.c#L987">987</a>                 if (<a href="ident?i=optlen">optlen</a> != sizeof(struct <a href="ident?i=group_source_req">group_source_req</a>))
<a name="L988" href="source/net/ipv4/ip_sockglue.c#L988">988</a>                         goto e_inval;
<a name="L989" href="source/net/ipv4/ip_sockglue.c#L989">989</a>                 if (<a href="ident?i=copy_from_user">copy_from_user</a>(&amp;greqs, optval, sizeof(greqs))) {
<a name="L990" href="source/net/ipv4/ip_sockglue.c#L990">990</a>                         <a href="ident?i=err">err</a> = -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L991" href="source/net/ipv4/ip_sockglue.c#L991">991</a>                         break;
<a name="L992" href="source/net/ipv4/ip_sockglue.c#L992">992</a>                 }
<a name="L993" href="source/net/ipv4/ip_sockglue.c#L993">993</a>                 if (greqs.gsr_group.ss_family != <a href="ident?i=AF_INET">AF_INET</a> ||
<a name="L994" href="source/net/ipv4/ip_sockglue.c#L994">994</a>                     greqs.gsr_source.ss_family != <a href="ident?i=AF_INET">AF_INET</a>) {
<a name="L995" href="source/net/ipv4/ip_sockglue.c#L995">995</a>                         <a href="ident?i=err">err</a> = -<a href="ident?i=EADDRNOTAVAIL">EADDRNOTAVAIL</a>;
<a name="L996" href="source/net/ipv4/ip_sockglue.c#L996">996</a>                         break;
<a name="L997" href="source/net/ipv4/ip_sockglue.c#L997">997</a>                 }
<a name="L998" href="source/net/ipv4/ip_sockglue.c#L998">998</a>                 psin = (struct <a href="ident?i=sockaddr_in">sockaddr_in</a> *)&amp;greqs.gsr_group;
<a name="L999" href="source/net/ipv4/ip_sockglue.c#L999">999</a>                 mreqs.imr_multiaddr = psin-&gt;sin_addr.s_addr;
<a name="L1000" href="source/net/ipv4/ip_sockglue.c#L1000">1000</a>                 psin = (struct <a href="ident?i=sockaddr_in">sockaddr_in</a> *)&amp;greqs.gsr_source;
<a name="L1001" href="source/net/ipv4/ip_sockglue.c#L1001">1001</a>                 mreqs.imr_sourceaddr = psin-&gt;sin_addr.s_addr;
<a name="L1002" href="source/net/ipv4/ip_sockglue.c#L1002">1002</a>                 mreqs.imr_interface = 0; <b><i>/* use index for mc_source */</i></b>
<a name="L1003" href="source/net/ipv4/ip_sockglue.c#L1003">1003</a> 
<a name="L1004" href="source/net/ipv4/ip_sockglue.c#L1004">1004</a>                 if (optname == <a href="ident?i=MCAST_BLOCK_SOURCE">MCAST_BLOCK_SOURCE</a>) {
<a name="L1005" href="source/net/ipv4/ip_sockglue.c#L1005">1005</a>                         omode = <a href="ident?i=MCAST_EXCLUDE">MCAST_EXCLUDE</a>;
<a name="L1006" href="source/net/ipv4/ip_sockglue.c#L1006">1006</a>                         add = 1;
<a name="L1007" href="source/net/ipv4/ip_sockglue.c#L1007">1007</a>                 } else if (optname == <a href="ident?i=MCAST_UNBLOCK_SOURCE">MCAST_UNBLOCK_SOURCE</a>) {
<a name="L1008" href="source/net/ipv4/ip_sockglue.c#L1008">1008</a>                         omode = <a href="ident?i=MCAST_EXCLUDE">MCAST_EXCLUDE</a>;
<a name="L1009" href="source/net/ipv4/ip_sockglue.c#L1009">1009</a>                         add = 0;
<a name="L1010" href="source/net/ipv4/ip_sockglue.c#L1010">1010</a>                 } else if (optname == <a href="ident?i=MCAST_JOIN_SOURCE_GROUP">MCAST_JOIN_SOURCE_GROUP</a>) {
<a name="L1011" href="source/net/ipv4/ip_sockglue.c#L1011">1011</a>                         struct <a href="ident?i=ip_mreqn">ip_mreqn</a> mreq;
<a name="L1012" href="source/net/ipv4/ip_sockglue.c#L1012">1012</a> 
<a name="L1013" href="source/net/ipv4/ip_sockglue.c#L1013">1013</a>                         psin = (struct <a href="ident?i=sockaddr_in">sockaddr_in</a> *)&amp;greqs.gsr_group;
<a name="L1014" href="source/net/ipv4/ip_sockglue.c#L1014">1014</a>                         mreq.imr_multiaddr = psin-&gt;sin_addr;
<a name="L1015" href="source/net/ipv4/ip_sockglue.c#L1015">1015</a>                         mreq.imr_address.s_addr = 0;
<a name="L1016" href="source/net/ipv4/ip_sockglue.c#L1016">1016</a>                         mreq.imr_ifindex = greqs.gsr_interface;
<a name="L1017" href="source/net/ipv4/ip_sockglue.c#L1017">1017</a>                         <a href="ident?i=err">err</a> = <a href="ident?i=ip_mc_join_group">ip_mc_join_group</a>(sk, &amp;mreq);
<a name="L1018" href="source/net/ipv4/ip_sockglue.c#L1018">1018</a>                         if (<a href="ident?i=err">err</a> &amp;&amp; <a href="ident?i=err">err</a> != -<a href="ident?i=EADDRINUSE">EADDRINUSE</a>)
<a name="L1019" href="source/net/ipv4/ip_sockglue.c#L1019">1019</a>                                 break;
<a name="L1020" href="source/net/ipv4/ip_sockglue.c#L1020">1020</a>                         greqs.gsr_interface = mreq.imr_ifindex;
<a name="L1021" href="source/net/ipv4/ip_sockglue.c#L1021">1021</a>                         omode = <a href="ident?i=MCAST_INCLUDE">MCAST_INCLUDE</a>;
<a name="L1022" href="source/net/ipv4/ip_sockglue.c#L1022">1022</a>                         add = 1;
<a name="L1023" href="source/net/ipv4/ip_sockglue.c#L1023">1023</a>                 } else <b><i>/* MCAST_LEAVE_SOURCE_GROUP */</i></b> {
<a name="L1024" href="source/net/ipv4/ip_sockglue.c#L1024">1024</a>                         omode = <a href="ident?i=MCAST_INCLUDE">MCAST_INCLUDE</a>;
<a name="L1025" href="source/net/ipv4/ip_sockglue.c#L1025">1025</a>                         add = 0;
<a name="L1026" href="source/net/ipv4/ip_sockglue.c#L1026">1026</a>                 }
<a name="L1027" href="source/net/ipv4/ip_sockglue.c#L1027">1027</a>                 <a href="ident?i=err">err</a> = <a href="ident?i=ip_mc_source">ip_mc_source</a>(add, omode, sk, &amp;mreqs,
<a name="L1028" href="source/net/ipv4/ip_sockglue.c#L1028">1028</a>                                    greqs.gsr_interface);
<a name="L1029" href="source/net/ipv4/ip_sockglue.c#L1029">1029</a>                 break;
<a name="L1030" href="source/net/ipv4/ip_sockglue.c#L1030">1030</a>         }
<a name="L1031" href="source/net/ipv4/ip_sockglue.c#L1031">1031</a>         case <a href="ident?i=MCAST_MSFILTER">MCAST_MSFILTER</a>:
<a name="L1032" href="source/net/ipv4/ip_sockglue.c#L1032">1032</a>         {
<a name="L1033" href="source/net/ipv4/ip_sockglue.c#L1033">1033</a>                 struct <a href="ident?i=sockaddr_in">sockaddr_in</a> *psin;
<a name="L1034" href="source/net/ipv4/ip_sockglue.c#L1034">1034</a>                 struct <a href="ident?i=ip_msfilter">ip_msfilter</a> *msf = <a href="ident?i=NULL">NULL</a>;
<a name="L1035" href="source/net/ipv4/ip_sockglue.c#L1035">1035</a>                 struct <a href="ident?i=group_filter">group_filter</a> *gsf = <a href="ident?i=NULL">NULL</a>;
<a name="L1036" href="source/net/ipv4/ip_sockglue.c#L1036">1036</a>                 int <a href="ident?i=msize">msize</a>, <a href="ident?i=i">i</a>, ifindex;
<a name="L1037" href="source/net/ipv4/ip_sockglue.c#L1037">1037</a> 
<a name="L1038" href="source/net/ipv4/ip_sockglue.c#L1038">1038</a>                 if (<a href="ident?i=optlen">optlen</a> &lt; <a href="ident?i=GROUP_FILTER_SIZE">GROUP_FILTER_SIZE</a>(0))
<a name="L1039" href="source/net/ipv4/ip_sockglue.c#L1039">1039</a>                         goto e_inval;
<a name="L1040" href="source/net/ipv4/ip_sockglue.c#L1040">1040</a>                 if (<a href="ident?i=optlen">optlen</a> &gt; <a href="ident?i=sysctl_optmem_max">sysctl_optmem_max</a>) {
<a name="L1041" href="source/net/ipv4/ip_sockglue.c#L1041">1041</a>                         <a href="ident?i=err">err</a> = -<a href="ident?i=ENOBUFS">ENOBUFS</a>;
<a name="L1042" href="source/net/ipv4/ip_sockglue.c#L1042">1042</a>                         break;
<a name="L1043" href="source/net/ipv4/ip_sockglue.c#L1043">1043</a>                 }
<a name="L1044" href="source/net/ipv4/ip_sockglue.c#L1044">1044</a>                 gsf = <a href="ident?i=kmalloc">kmalloc</a>(<a href="ident?i=optlen">optlen</a>, <a href="ident?i=GFP_KERNEL">GFP_KERNEL</a>);
<a name="L1045" href="source/net/ipv4/ip_sockglue.c#L1045">1045</a>                 if (!gsf) {
<a name="L1046" href="source/net/ipv4/ip_sockglue.c#L1046">1046</a>                         <a href="ident?i=err">err</a> = -<a href="ident?i=ENOBUFS">ENOBUFS</a>;
<a name="L1047" href="source/net/ipv4/ip_sockglue.c#L1047">1047</a>                         break;
<a name="L1048" href="source/net/ipv4/ip_sockglue.c#L1048">1048</a>                 }
<a name="L1049" href="source/net/ipv4/ip_sockglue.c#L1049">1049</a>                 <a href="ident?i=err">err</a> = -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L1050" href="source/net/ipv4/ip_sockglue.c#L1050">1050</a>                 if (<a href="ident?i=copy_from_user">copy_from_user</a>(gsf, optval, <a href="ident?i=optlen">optlen</a>))
<a name="L1051" href="source/net/ipv4/ip_sockglue.c#L1051">1051</a>                         goto mc_msf_out;
<a name="L1052" href="source/net/ipv4/ip_sockglue.c#L1052">1052</a> 
<a name="L1053" href="source/net/ipv4/ip_sockglue.c#L1053">1053</a>                 <b><i>/* numsrc &gt;= (4G-140)/128 overflow in 32 bits */</i></b>
<a name="L1054" href="source/net/ipv4/ip_sockglue.c#L1054">1054</a>                 if (gsf-&gt;gf_numsrc &gt;= 0x1ffffff ||
<a name="L1055" href="source/net/ipv4/ip_sockglue.c#L1055">1055</a>                     gsf-&gt;gf_numsrc &gt; <a href="ident?i=sysctl_igmp_max_msf">sysctl_igmp_max_msf</a>) {
<a name="L1056" href="source/net/ipv4/ip_sockglue.c#L1056">1056</a>                         <a href="ident?i=err">err</a> = -<a href="ident?i=ENOBUFS">ENOBUFS</a>;
<a name="L1057" href="source/net/ipv4/ip_sockglue.c#L1057">1057</a>                         goto mc_msf_out;
<a name="L1058" href="source/net/ipv4/ip_sockglue.c#L1058">1058</a>                 }
<a name="L1059" href="source/net/ipv4/ip_sockglue.c#L1059">1059</a>                 if (<a href="ident?i=GROUP_FILTER_SIZE">GROUP_FILTER_SIZE</a>(gsf-&gt;gf_numsrc) &gt; <a href="ident?i=optlen">optlen</a>) {
<a name="L1060" href="source/net/ipv4/ip_sockglue.c#L1060">1060</a>                         <a href="ident?i=err">err</a> = -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L1061" href="source/net/ipv4/ip_sockglue.c#L1061">1061</a>                         goto mc_msf_out;
<a name="L1062" href="source/net/ipv4/ip_sockglue.c#L1062">1062</a>                 }
<a name="L1063" href="source/net/ipv4/ip_sockglue.c#L1063">1063</a>                 <a href="ident?i=msize">msize</a> = <a href="ident?i=IP_MSFILTER_SIZE">IP_MSFILTER_SIZE</a>(gsf-&gt;gf_numsrc);
<a name="L1064" href="source/net/ipv4/ip_sockglue.c#L1064">1064</a>                 msf = <a href="ident?i=kmalloc">kmalloc</a>(<a href="ident?i=msize">msize</a>, <a href="ident?i=GFP_KERNEL">GFP_KERNEL</a>);
<a name="L1065" href="source/net/ipv4/ip_sockglue.c#L1065">1065</a>                 if (!msf) {
<a name="L1066" href="source/net/ipv4/ip_sockglue.c#L1066">1066</a>                         <a href="ident?i=err">err</a> = -<a href="ident?i=ENOBUFS">ENOBUFS</a>;
<a name="L1067" href="source/net/ipv4/ip_sockglue.c#L1067">1067</a>                         goto mc_msf_out;
<a name="L1068" href="source/net/ipv4/ip_sockglue.c#L1068">1068</a>                 }
<a name="L1069" href="source/net/ipv4/ip_sockglue.c#L1069">1069</a>                 ifindex = gsf-&gt;gf_interface;
<a name="L1070" href="source/net/ipv4/ip_sockglue.c#L1070">1070</a>                 psin = (struct <a href="ident?i=sockaddr_in">sockaddr_in</a> *)&amp;gsf-&gt;gf_group;
<a name="L1071" href="source/net/ipv4/ip_sockglue.c#L1071">1071</a>                 if (psin-&gt;sin_family != <a href="ident?i=AF_INET">AF_INET</a>) {
<a name="L1072" href="source/net/ipv4/ip_sockglue.c#L1072">1072</a>                         <a href="ident?i=err">err</a> = -<a href="ident?i=EADDRNOTAVAIL">EADDRNOTAVAIL</a>;
<a name="L1073" href="source/net/ipv4/ip_sockglue.c#L1073">1073</a>                         goto mc_msf_out;
<a name="L1074" href="source/net/ipv4/ip_sockglue.c#L1074">1074</a>                 }
<a name="L1075" href="source/net/ipv4/ip_sockglue.c#L1075">1075</a>                 msf-&gt;imsf_multiaddr = psin-&gt;sin_addr.s_addr;
<a name="L1076" href="source/net/ipv4/ip_sockglue.c#L1076">1076</a>                 msf-&gt;imsf_interface = 0;
<a name="L1077" href="source/net/ipv4/ip_sockglue.c#L1077">1077</a>                 msf-&gt;imsf_fmode = gsf-&gt;gf_fmode;
<a name="L1078" href="source/net/ipv4/ip_sockglue.c#L1078">1078</a>                 msf-&gt;imsf_numsrc = gsf-&gt;gf_numsrc;
<a name="L1079" href="source/net/ipv4/ip_sockglue.c#L1079">1079</a>                 <a href="ident?i=err">err</a> = -<a href="ident?i=EADDRNOTAVAIL">EADDRNOTAVAIL</a>;
<a name="L1080" href="source/net/ipv4/ip_sockglue.c#L1080">1080</a>                 for (<a href="ident?i=i">i</a> = 0; <a href="ident?i=i">i</a> &lt; gsf-&gt;gf_numsrc; ++<a href="ident?i=i">i</a>) {
<a name="L1081" href="source/net/ipv4/ip_sockglue.c#L1081">1081</a>                         psin = (struct <a href="ident?i=sockaddr_in">sockaddr_in</a> *)&amp;gsf-&gt;gf_slist[<a href="ident?i=i">i</a>];
<a name="L1082" href="source/net/ipv4/ip_sockglue.c#L1082">1082</a> 
<a name="L1083" href="source/net/ipv4/ip_sockglue.c#L1083">1083</a>                         if (psin-&gt;sin_family != <a href="ident?i=AF_INET">AF_INET</a>)
<a name="L1084" href="source/net/ipv4/ip_sockglue.c#L1084">1084</a>                                 goto mc_msf_out;
<a name="L1085" href="source/net/ipv4/ip_sockglue.c#L1085">1085</a>                         msf-&gt;imsf_slist[<a href="ident?i=i">i</a>] = psin-&gt;sin_addr.s_addr;
<a name="L1086" href="source/net/ipv4/ip_sockglue.c#L1086">1086</a>                 }
<a name="L1087" href="source/net/ipv4/ip_sockglue.c#L1087">1087</a>                 <a href="ident?i=kfree">kfree</a>(gsf);
<a name="L1088" href="source/net/ipv4/ip_sockglue.c#L1088">1088</a>                 gsf = <a href="ident?i=NULL">NULL</a>;
<a name="L1089" href="source/net/ipv4/ip_sockglue.c#L1089">1089</a> 
<a name="L1090" href="source/net/ipv4/ip_sockglue.c#L1090">1090</a>                 <a href="ident?i=err">err</a> = <a href="ident?i=ip_mc_msfilter">ip_mc_msfilter</a>(sk, msf, ifindex);
<a name="L1091" href="source/net/ipv4/ip_sockglue.c#L1091">1091</a> mc_msf_out:
<a name="L1092" href="source/net/ipv4/ip_sockglue.c#L1092">1092</a>                 <a href="ident?i=kfree">kfree</a>(msf);
<a name="L1093" href="source/net/ipv4/ip_sockglue.c#L1093">1093</a>                 <a href="ident?i=kfree">kfree</a>(gsf);
<a name="L1094" href="source/net/ipv4/ip_sockglue.c#L1094">1094</a>                 break;
<a name="L1095" href="source/net/ipv4/ip_sockglue.c#L1095">1095</a>         }
<a name="L1096" href="source/net/ipv4/ip_sockglue.c#L1096">1096</a>         case <a href="ident?i=IP_MULTICAST_ALL">IP_MULTICAST_ALL</a>:
<a name="L1097" href="source/net/ipv4/ip_sockglue.c#L1097">1097</a>                 if (<a href="ident?i=optlen">optlen</a> &lt; 1)
<a name="L1098" href="source/net/ipv4/ip_sockglue.c#L1098">1098</a>                         goto e_inval;
<a name="L1099" href="source/net/ipv4/ip_sockglue.c#L1099">1099</a>                 if (<a href="ident?i=val">val</a> != 0 &amp;&amp; <a href="ident?i=val">val</a> != 1)
<a name="L1100" href="source/net/ipv4/ip_sockglue.c#L1100">1100</a>                         goto e_inval;
<a name="L1101" href="source/net/ipv4/ip_sockglue.c#L1101">1101</a>                 inet-&gt;mc_all = <a href="ident?i=val">val</a>;
<a name="L1102" href="source/net/ipv4/ip_sockglue.c#L1102">1102</a>                 break;
<a name="L1103" href="source/net/ipv4/ip_sockglue.c#L1103">1103</a>         case <a href="ident?i=IP_ROUTER_ALERT">IP_ROUTER_ALERT</a>:
<a name="L1104" href="source/net/ipv4/ip_sockglue.c#L1104">1104</a>                 <a href="ident?i=err">err</a> = <a href="ident?i=ip_ra_control">ip_ra_control</a>(sk, <a href="ident?i=val">val</a> ? 1 : 0, <a href="ident?i=NULL">NULL</a>);
<a name="L1105" href="source/net/ipv4/ip_sockglue.c#L1105">1105</a>                 break;
<a name="L1106" href="source/net/ipv4/ip_sockglue.c#L1106">1106</a> 
<a name="L1107" href="source/net/ipv4/ip_sockglue.c#L1107">1107</a>         case <a href="ident?i=IP_FREEBIND">IP_FREEBIND</a>:
<a name="L1108" href="source/net/ipv4/ip_sockglue.c#L1108">1108</a>                 if (<a href="ident?i=optlen">optlen</a> &lt; 1)
<a name="L1109" href="source/net/ipv4/ip_sockglue.c#L1109">1109</a>                         goto e_inval;
<a name="L1110" href="source/net/ipv4/ip_sockglue.c#L1110">1110</a>                 inet-&gt;freebind = !!<a href="ident?i=val">val</a>;
<a name="L1111" href="source/net/ipv4/ip_sockglue.c#L1111">1111</a>                 break;
<a name="L1112" href="source/net/ipv4/ip_sockglue.c#L1112">1112</a> 
<a name="L1113" href="source/net/ipv4/ip_sockglue.c#L1113">1113</a>         case <a href="ident?i=IP_IPSEC_POLICY">IP_IPSEC_POLICY</a>:
<a name="L1114" href="source/net/ipv4/ip_sockglue.c#L1114">1114</a>         case <a href="ident?i=IP_XFRM_POLICY">IP_XFRM_POLICY</a>:
<a name="L1115" href="source/net/ipv4/ip_sockglue.c#L1115">1115</a>                 <a href="ident?i=err">err</a> = -<a href="ident?i=EPERM">EPERM</a>;
<a name="L1116" href="source/net/ipv4/ip_sockglue.c#L1116">1116</a>                 if (!<a href="ident?i=ns_capable">ns_capable</a>(<a href="ident?i=sock_net">sock_net</a>(sk)-&gt;<a href="ident?i=user_ns">user_ns</a>, <a href="ident?i=CAP_NET_ADMIN">CAP_NET_ADMIN</a>))
<a name="L1117" href="source/net/ipv4/ip_sockglue.c#L1117">1117</a>                         break;
<a name="L1118" href="source/net/ipv4/ip_sockglue.c#L1118">1118</a>                 <a href="ident?i=err">err</a> = <a href="ident?i=xfrm_user_policy">xfrm_user_policy</a>(sk, optname, optval, <a href="ident?i=optlen">optlen</a>);
<a name="L1119" href="source/net/ipv4/ip_sockglue.c#L1119">1119</a>                 break;
<a name="L1120" href="source/net/ipv4/ip_sockglue.c#L1120">1120</a> 
<a name="L1121" href="source/net/ipv4/ip_sockglue.c#L1121">1121</a>         case <a href="ident?i=IP_TRANSPARENT">IP_TRANSPARENT</a>:
<a name="L1122" href="source/net/ipv4/ip_sockglue.c#L1122">1122</a>                 if (!!<a href="ident?i=val">val</a> &amp;&amp; !<a href="ident?i=ns_capable">ns_capable</a>(<a href="ident?i=sock_net">sock_net</a>(sk)-&gt;<a href="ident?i=user_ns">user_ns</a>, <a href="ident?i=CAP_NET_RAW">CAP_NET_RAW</a>) &amp;&amp;
<a name="L1123" href="source/net/ipv4/ip_sockglue.c#L1123">1123</a>                     !<a href="ident?i=ns_capable">ns_capable</a>(<a href="ident?i=sock_net">sock_net</a>(sk)-&gt;<a href="ident?i=user_ns">user_ns</a>, <a href="ident?i=CAP_NET_ADMIN">CAP_NET_ADMIN</a>)) {
<a name="L1124" href="source/net/ipv4/ip_sockglue.c#L1124">1124</a>                         <a href="ident?i=err">err</a> = -<a href="ident?i=EPERM">EPERM</a>;
<a name="L1125" href="source/net/ipv4/ip_sockglue.c#L1125">1125</a>                         break;
<a name="L1126" href="source/net/ipv4/ip_sockglue.c#L1126">1126</a>                 }
<a name="L1127" href="source/net/ipv4/ip_sockglue.c#L1127">1127</a>                 if (<a href="ident?i=optlen">optlen</a> &lt; 1)
<a name="L1128" href="source/net/ipv4/ip_sockglue.c#L1128">1128</a>                         goto e_inval;
<a name="L1129" href="source/net/ipv4/ip_sockglue.c#L1129">1129</a>                 inet-&gt;transparent = !!<a href="ident?i=val">val</a>;
<a name="L1130" href="source/net/ipv4/ip_sockglue.c#L1130">1130</a>                 break;
<a name="L1131" href="source/net/ipv4/ip_sockglue.c#L1131">1131</a> 
<a name="L1132" href="source/net/ipv4/ip_sockglue.c#L1132">1132</a>         case <a href="ident?i=IP_MINTTL">IP_MINTTL</a>:
<a name="L1133" href="source/net/ipv4/ip_sockglue.c#L1133">1133</a>                 if (<a href="ident?i=optlen">optlen</a> &lt; 1)
<a name="L1134" href="source/net/ipv4/ip_sockglue.c#L1134">1134</a>                         goto e_inval;
<a name="L1135" href="source/net/ipv4/ip_sockglue.c#L1135">1135</a>                 if (<a href="ident?i=val">val</a> &lt; 0 || <a href="ident?i=val">val</a> &gt; 255)
<a name="L1136" href="source/net/ipv4/ip_sockglue.c#L1136">1136</a>                         goto e_inval;
<a name="L1137" href="source/net/ipv4/ip_sockglue.c#L1137">1137</a>                 inet-&gt;<a href="ident?i=min_ttl">min_ttl</a> = <a href="ident?i=val">val</a>;
<a name="L1138" href="source/net/ipv4/ip_sockglue.c#L1138">1138</a>                 break;
<a name="L1139" href="source/net/ipv4/ip_sockglue.c#L1139">1139</a> 
<a name="L1140" href="source/net/ipv4/ip_sockglue.c#L1140">1140</a>         default:
<a name="L1141" href="source/net/ipv4/ip_sockglue.c#L1141">1141</a>                 <a href="ident?i=err">err</a> = -<a href="ident?i=ENOPROTOOPT">ENOPROTOOPT</a>;
<a name="L1142" href="source/net/ipv4/ip_sockglue.c#L1142">1142</a>                 break;
<a name="L1143" href="source/net/ipv4/ip_sockglue.c#L1143">1143</a>         }
<a name="L1144" href="source/net/ipv4/ip_sockglue.c#L1144">1144</a>         <a href="ident?i=release_sock">release_sock</a>(sk);
<a name="L1145" href="source/net/ipv4/ip_sockglue.c#L1145">1145</a>         if (needs_rtnl)
<a name="L1146" href="source/net/ipv4/ip_sockglue.c#L1146">1146</a>                 <a href="ident?i=rtnl_unlock">rtnl_unlock</a>();
<a name="L1147" href="source/net/ipv4/ip_sockglue.c#L1147">1147</a>         return <a href="ident?i=err">err</a>;
<a name="L1148" href="source/net/ipv4/ip_sockglue.c#L1148">1148</a> 
<a name="L1149" href="source/net/ipv4/ip_sockglue.c#L1149">1149</a> e_inval:
<a name="L1150" href="source/net/ipv4/ip_sockglue.c#L1150">1150</a>         <a href="ident?i=release_sock">release_sock</a>(sk);
<a name="L1151" href="source/net/ipv4/ip_sockglue.c#L1151">1151</a>         if (needs_rtnl)
<a name="L1152" href="source/net/ipv4/ip_sockglue.c#L1152">1152</a>                 <a href="ident?i=rtnl_unlock">rtnl_unlock</a>();
<a name="L1153" href="source/net/ipv4/ip_sockglue.c#L1153">1153</a>         return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L1154" href="source/net/ipv4/ip_sockglue.c#L1154">1154</a> }
<a name="L1155" href="source/net/ipv4/ip_sockglue.c#L1155">1155</a> 
<a name="L1156" href="source/net/ipv4/ip_sockglue.c#L1156">1156</a> <b><i>/**</i></b>
<a name="L1157" href="source/net/ipv4/ip_sockglue.c#L1157">1157</a> <b><i> * ipv4_pktinfo_prepare - transfer some info from rtable to skb</i></b>
<a name="L1158" href="source/net/ipv4/ip_sockglue.c#L1158">1158</a> <b><i> * @sk: socket</i></b>
<a name="L1159" href="source/net/ipv4/ip_sockglue.c#L1159">1159</a> <b><i> * @skb: buffer</i></b>
<a name="L1160" href="source/net/ipv4/ip_sockglue.c#L1160">1160</a> <b><i> *</i></b>
<a name="L1161" href="source/net/ipv4/ip_sockglue.c#L1161">1161</a> <b><i> * To support IP_CMSG_PKTINFO option, we store rt_iif and specific</i></b>
<a name="L1162" href="source/net/ipv4/ip_sockglue.c#L1162">1162</a> <b><i> * destination in skb-&gt;cb[] before dst drop.</i></b>
<a name="L1163" href="source/net/ipv4/ip_sockglue.c#L1163">1163</a> <b><i> * This way, receiver doesn't make cache line misses to read rtable.</i></b>
<a name="L1164" href="source/net/ipv4/ip_sockglue.c#L1164">1164</a> <b><i> */</i></b>
<a name="L1165" href="source/net/ipv4/ip_sockglue.c#L1165">1165</a> void <a href="ident?i=ipv4_pktinfo_prepare">ipv4_pktinfo_prepare</a>(const struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L1166" href="source/net/ipv4/ip_sockglue.c#L1166">1166</a> {
<a name="L1167" href="source/net/ipv4/ip_sockglue.c#L1167">1167</a>         struct <a href="ident?i=in_pktinfo">in_pktinfo</a> *pktinfo = <a href="ident?i=PKTINFO_SKB_CB">PKTINFO_SKB_CB</a>(<a href="ident?i=skb">skb</a>);
<a name="L1168" href="source/net/ipv4/ip_sockglue.c#L1168">1168</a>         <a href="ident?i=bool">bool</a> prepare = (<a href="ident?i=inet_sk">inet_sk</a>(sk)-&gt;cmsg_flags &amp; <a href="ident?i=IP_CMSG_PKTINFO">IP_CMSG_PKTINFO</a>) ||
<a name="L1169" href="source/net/ipv4/ip_sockglue.c#L1169">1169</a>                        <a href="ident?i=ipv6_sk_rxinfo">ipv6_sk_rxinfo</a>(sk);
<a name="L1170" href="source/net/ipv4/ip_sockglue.c#L1170">1170</a> 
<a name="L1171" href="source/net/ipv4/ip_sockglue.c#L1171">1171</a>         if (prepare &amp;&amp; <a href="ident?i=skb_rtable">skb_rtable</a>(<a href="ident?i=skb">skb</a>)) {
<a name="L1172" href="source/net/ipv4/ip_sockglue.c#L1172">1172</a>                 pktinfo-&gt;ipi_ifindex = <a href="ident?i=inet_iif">inet_iif</a>(<a href="ident?i=skb">skb</a>);
<a name="L1173" href="source/net/ipv4/ip_sockglue.c#L1173">1173</a>                 pktinfo-&gt;ipi_spec_dst.s_addr = <a href="ident?i=fib_compute_spec_dst">fib_compute_spec_dst</a>(<a href="ident?i=skb">skb</a>);
<a name="L1174" href="source/net/ipv4/ip_sockglue.c#L1174">1174</a>         } else {
<a name="L1175" href="source/net/ipv4/ip_sockglue.c#L1175">1175</a>                 pktinfo-&gt;ipi_ifindex = 0;
<a name="L1176" href="source/net/ipv4/ip_sockglue.c#L1176">1176</a>                 pktinfo-&gt;ipi_spec_dst.s_addr = 0;
<a name="L1177" href="source/net/ipv4/ip_sockglue.c#L1177">1177</a>         }
<a name="L1178" href="source/net/ipv4/ip_sockglue.c#L1178">1178</a>         <a href="ident?i=skb_dst_drop">skb_dst_drop</a>(<a href="ident?i=skb">skb</a>);
<a name="L1179" href="source/net/ipv4/ip_sockglue.c#L1179">1179</a> }
<a name="L1180" href="source/net/ipv4/ip_sockglue.c#L1180">1180</a> 
<a name="L1181" href="source/net/ipv4/ip_sockglue.c#L1181">1181</a> int <a href="ident?i=ip_setsockopt">ip_setsockopt</a>(struct <a href="ident?i=sock">sock</a> *sk, int <a href="ident?i=level">level</a>,
<a name="L1182" href="source/net/ipv4/ip_sockglue.c#L1182">1182</a>                 int optname, char <a href="ident?i=__user">__user</a> *optval, unsigned int <a href="ident?i=optlen">optlen</a>)
<a name="L1183" href="source/net/ipv4/ip_sockglue.c#L1183">1183</a> {
<a name="L1184" href="source/net/ipv4/ip_sockglue.c#L1184">1184</a>         int <a href="ident?i=err">err</a>;
<a name="L1185" href="source/net/ipv4/ip_sockglue.c#L1185">1185</a> 
<a name="L1186" href="source/net/ipv4/ip_sockglue.c#L1186">1186</a>         if (<a href="ident?i=level">level</a> != <a href="ident?i=SOL_IP">SOL_IP</a>)
<a name="L1187" href="source/net/ipv4/ip_sockglue.c#L1187">1187</a>                 return -<a href="ident?i=ENOPROTOOPT">ENOPROTOOPT</a>;
<a name="L1188" href="source/net/ipv4/ip_sockglue.c#L1188">1188</a> 
<a name="L1189" href="source/net/ipv4/ip_sockglue.c#L1189">1189</a>         <a href="ident?i=err">err</a> = <a href="ident?i=do_ip_setsockopt">do_ip_setsockopt</a>(sk, <a href="ident?i=level">level</a>, optname, optval, <a href="ident?i=optlen">optlen</a>);
<a name="L1190" href="source/net/ipv4/ip_sockglue.c#L1190">1190</a> #ifdef CONFIG_NETFILTER
<a name="L1191" href="source/net/ipv4/ip_sockglue.c#L1191">1191</a>         <b><i>/* we need to exclude all possible ENOPROTOOPTs except default case */</i></b>
<a name="L1192" href="source/net/ipv4/ip_sockglue.c#L1192">1192</a>         if (<a href="ident?i=err">err</a> == -<a href="ident?i=ENOPROTOOPT">ENOPROTOOPT</a> &amp;&amp; optname != <a href="ident?i=IP_HDRINCL">IP_HDRINCL</a> &amp;&amp;
<a name="L1193" href="source/net/ipv4/ip_sockglue.c#L1193">1193</a>                         optname != <a href="ident?i=IP_IPSEC_POLICY">IP_IPSEC_POLICY</a> &amp;&amp;
<a name="L1194" href="source/net/ipv4/ip_sockglue.c#L1194">1194</a>                         optname != <a href="ident?i=IP_XFRM_POLICY">IP_XFRM_POLICY</a> &amp;&amp;
<a name="L1195" href="source/net/ipv4/ip_sockglue.c#L1195">1195</a>                         !<a href="ident?i=ip_mroute_opt">ip_mroute_opt</a>(optname)) {
<a name="L1196" href="source/net/ipv4/ip_sockglue.c#L1196">1196</a>                 <a href="ident?i=lock_sock">lock_sock</a>(sk);
<a name="L1197" href="source/net/ipv4/ip_sockglue.c#L1197">1197</a>                 <a href="ident?i=err">err</a> = <a href="ident?i=nf_setsockopt">nf_setsockopt</a>(sk, <a href="ident?i=PF_INET">PF_INET</a>, optname, optval, <a href="ident?i=optlen">optlen</a>);
<a name="L1198" href="source/net/ipv4/ip_sockglue.c#L1198">1198</a>                 <a href="ident?i=release_sock">release_sock</a>(sk);
<a name="L1199" href="source/net/ipv4/ip_sockglue.c#L1199">1199</a>         }
<a name="L1200" href="source/net/ipv4/ip_sockglue.c#L1200">1200</a> #endif
<a name="L1201" href="source/net/ipv4/ip_sockglue.c#L1201">1201</a>         return <a href="ident?i=err">err</a>;
<a name="L1202" href="source/net/ipv4/ip_sockglue.c#L1202">1202</a> }
<a name="L1203" href="source/net/ipv4/ip_sockglue.c#L1203">1203</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=ip_setsockopt">ip_setsockopt</a>);
<a name="L1204" href="source/net/ipv4/ip_sockglue.c#L1204">1204</a> 
<a name="L1205" href="source/net/ipv4/ip_sockglue.c#L1205">1205</a> #ifdef CONFIG_COMPAT
<a name="L1206" href="source/net/ipv4/ip_sockglue.c#L1206">1206</a> int <a href="ident?i=compat_ip_setsockopt">compat_ip_setsockopt</a>(struct <a href="ident?i=sock">sock</a> *sk, int <a href="ident?i=level">level</a>, int optname,
<a name="L1207" href="source/net/ipv4/ip_sockglue.c#L1207">1207</a>                          char <a href="ident?i=__user">__user</a> *optval, unsigned int <a href="ident?i=optlen">optlen</a>)
<a name="L1208" href="source/net/ipv4/ip_sockglue.c#L1208">1208</a> {
<a name="L1209" href="source/net/ipv4/ip_sockglue.c#L1209">1209</a>         int <a href="ident?i=err">err</a>;
<a name="L1210" href="source/net/ipv4/ip_sockglue.c#L1210">1210</a> 
<a name="L1211" href="source/net/ipv4/ip_sockglue.c#L1211">1211</a>         if (<a href="ident?i=level">level</a> != <a href="ident?i=SOL_IP">SOL_IP</a>)
<a name="L1212" href="source/net/ipv4/ip_sockglue.c#L1212">1212</a>                 return -<a href="ident?i=ENOPROTOOPT">ENOPROTOOPT</a>;
<a name="L1213" href="source/net/ipv4/ip_sockglue.c#L1213">1213</a> 
<a name="L1214" href="source/net/ipv4/ip_sockglue.c#L1214">1214</a>         if (optname &gt;= <a href="ident?i=MCAST_JOIN_GROUP">MCAST_JOIN_GROUP</a> &amp;&amp; optname &lt;= <a href="ident?i=MCAST_MSFILTER">MCAST_MSFILTER</a>)
<a name="L1215" href="source/net/ipv4/ip_sockglue.c#L1215">1215</a>                 return <a href="ident?i=compat_mc_setsockopt">compat_mc_setsockopt</a>(sk, <a href="ident?i=level">level</a>, optname, optval, <a href="ident?i=optlen">optlen</a>,
<a name="L1216" href="source/net/ipv4/ip_sockglue.c#L1216">1216</a>                         <a href="ident?i=ip_setsockopt">ip_setsockopt</a>);
<a name="L1217" href="source/net/ipv4/ip_sockglue.c#L1217">1217</a> 
<a name="L1218" href="source/net/ipv4/ip_sockglue.c#L1218">1218</a>         <a href="ident?i=err">err</a> = <a href="ident?i=do_ip_setsockopt">do_ip_setsockopt</a>(sk, <a href="ident?i=level">level</a>, optname, optval, <a href="ident?i=optlen">optlen</a>);
<a name="L1219" href="source/net/ipv4/ip_sockglue.c#L1219">1219</a> #ifdef CONFIG_NETFILTER
<a name="L1220" href="source/net/ipv4/ip_sockglue.c#L1220">1220</a>         <b><i>/* we need to exclude all possible ENOPROTOOPTs except default case */</i></b>
<a name="L1221" href="source/net/ipv4/ip_sockglue.c#L1221">1221</a>         if (<a href="ident?i=err">err</a> == -<a href="ident?i=ENOPROTOOPT">ENOPROTOOPT</a> &amp;&amp; optname != <a href="ident?i=IP_HDRINCL">IP_HDRINCL</a> &amp;&amp;
<a name="L1222" href="source/net/ipv4/ip_sockglue.c#L1222">1222</a>                         optname != <a href="ident?i=IP_IPSEC_POLICY">IP_IPSEC_POLICY</a> &amp;&amp;
<a name="L1223" href="source/net/ipv4/ip_sockglue.c#L1223">1223</a>                         optname != <a href="ident?i=IP_XFRM_POLICY">IP_XFRM_POLICY</a> &amp;&amp;
<a name="L1224" href="source/net/ipv4/ip_sockglue.c#L1224">1224</a>                         !<a href="ident?i=ip_mroute_opt">ip_mroute_opt</a>(optname)) {
<a name="L1225" href="source/net/ipv4/ip_sockglue.c#L1225">1225</a>                 <a href="ident?i=lock_sock">lock_sock</a>(sk);
<a name="L1226" href="source/net/ipv4/ip_sockglue.c#L1226">1226</a>                 <a href="ident?i=err">err</a> = <a href="ident?i=compat_nf_setsockopt">compat_nf_setsockopt</a>(sk, <a href="ident?i=PF_INET">PF_INET</a>, optname,
<a name="L1227" href="source/net/ipv4/ip_sockglue.c#L1227">1227</a>                                            optval, <a href="ident?i=optlen">optlen</a>);
<a name="L1228" href="source/net/ipv4/ip_sockglue.c#L1228">1228</a>                 <a href="ident?i=release_sock">release_sock</a>(sk);
<a name="L1229" href="source/net/ipv4/ip_sockglue.c#L1229">1229</a>         }
<a name="L1230" href="source/net/ipv4/ip_sockglue.c#L1230">1230</a> #endif
<a name="L1231" href="source/net/ipv4/ip_sockglue.c#L1231">1231</a>         return <a href="ident?i=err">err</a>;
<a name="L1232" href="source/net/ipv4/ip_sockglue.c#L1232">1232</a> }
<a name="L1233" href="source/net/ipv4/ip_sockglue.c#L1233">1233</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=compat_ip_setsockopt">compat_ip_setsockopt</a>);
<a name="L1234" href="source/net/ipv4/ip_sockglue.c#L1234">1234</a> #endif
<a name="L1235" href="source/net/ipv4/ip_sockglue.c#L1235">1235</a> 
<a name="L1236" href="source/net/ipv4/ip_sockglue.c#L1236">1236</a> <b><i>/*</i></b>
<a name="L1237" href="source/net/ipv4/ip_sockglue.c#L1237">1237</a> <b><i> *      Get the options. Note for future reference. The GET of IP options gets</i></b>
<a name="L1238" href="source/net/ipv4/ip_sockglue.c#L1238">1238</a> <b><i> *      the _received_ ones. The set sets the _sent_ ones.</i></b>
<a name="L1239" href="source/net/ipv4/ip_sockglue.c#L1239">1239</a> <b><i> */</i></b>
<a name="L1240" href="source/net/ipv4/ip_sockglue.c#L1240">1240</a> 
<a name="L1241" href="source/net/ipv4/ip_sockglue.c#L1241">1241</a> static int <a href="ident?i=do_ip_getsockopt">do_ip_getsockopt</a>(struct <a href="ident?i=sock">sock</a> *sk, int <a href="ident?i=level">level</a>, int optname,
<a name="L1242" href="source/net/ipv4/ip_sockglue.c#L1242">1242</a>                             char <a href="ident?i=__user">__user</a> *optval, int <a href="ident?i=__user">__user</a> *<a href="ident?i=optlen">optlen</a>, unsigned int <a href="ident?i=flags">flags</a>)
<a name="L1243" href="source/net/ipv4/ip_sockglue.c#L1243">1243</a> {
<a name="L1244" href="source/net/ipv4/ip_sockglue.c#L1244">1244</a>         struct <a href="ident?i=inet_sock">inet_sock</a> *inet = <a href="ident?i=inet_sk">inet_sk</a>(sk);
<a name="L1245" href="source/net/ipv4/ip_sockglue.c#L1245">1245</a>         int <a href="ident?i=val">val</a>;
<a name="L1246" href="source/net/ipv4/ip_sockglue.c#L1246">1246</a>         int <a href="ident?i=len">len</a>;
<a name="L1247" href="source/net/ipv4/ip_sockglue.c#L1247">1247</a> 
<a name="L1248" href="source/net/ipv4/ip_sockglue.c#L1248">1248</a>         if (<a href="ident?i=level">level</a> != <a href="ident?i=SOL_IP">SOL_IP</a>)
<a name="L1249" href="source/net/ipv4/ip_sockglue.c#L1249">1249</a>                 return -<a href="ident?i=EOPNOTSUPP">EOPNOTSUPP</a>;
<a name="L1250" href="source/net/ipv4/ip_sockglue.c#L1250">1250</a> 
<a name="L1251" href="source/net/ipv4/ip_sockglue.c#L1251">1251</a>         if (<a href="ident?i=ip_mroute_opt">ip_mroute_opt</a>(optname))
<a name="L1252" href="source/net/ipv4/ip_sockglue.c#L1252">1252</a>                 return <a href="ident?i=ip_mroute_getsockopt">ip_mroute_getsockopt</a>(sk, optname, optval, <a href="ident?i=optlen">optlen</a>);
<a name="L1253" href="source/net/ipv4/ip_sockglue.c#L1253">1253</a> 
<a name="L1254" href="source/net/ipv4/ip_sockglue.c#L1254">1254</a>         if (<a href="ident?i=get_user">get_user</a>(<a href="ident?i=len">len</a>, <a href="ident?i=optlen">optlen</a>))
<a name="L1255" href="source/net/ipv4/ip_sockglue.c#L1255">1255</a>                 return -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L1256" href="source/net/ipv4/ip_sockglue.c#L1256">1256</a>         if (<a href="ident?i=len">len</a> &lt; 0)
<a name="L1257" href="source/net/ipv4/ip_sockglue.c#L1257">1257</a>                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L1258" href="source/net/ipv4/ip_sockglue.c#L1258">1258</a> 
<a name="L1259" href="source/net/ipv4/ip_sockglue.c#L1259">1259</a>         <a href="ident?i=lock_sock">lock_sock</a>(sk);
<a name="L1260" href="source/net/ipv4/ip_sockglue.c#L1260">1260</a> 
<a name="L1261" href="source/net/ipv4/ip_sockglue.c#L1261">1261</a>         switch (optname) {
<a name="L1262" href="source/net/ipv4/ip_sockglue.c#L1262">1262</a>         case <a href="ident?i=IP_OPTIONS">IP_OPTIONS</a>:
<a name="L1263" href="source/net/ipv4/ip_sockglue.c#L1263">1263</a>         {
<a name="L1264" href="source/net/ipv4/ip_sockglue.c#L1264">1264</a>                 unsigned char optbuf[sizeof(struct <a href="ident?i=ip_options">ip_options</a>)+40];
<a name="L1265" href="source/net/ipv4/ip_sockglue.c#L1265">1265</a>                 struct <a href="ident?i=ip_options">ip_options</a> *opt = (struct <a href="ident?i=ip_options">ip_options</a> *)optbuf;
<a name="L1266" href="source/net/ipv4/ip_sockglue.c#L1266">1266</a>                 struct <a href="ident?i=ip_options_rcu">ip_options_rcu</a> *inet_opt;
<a name="L1267" href="source/net/ipv4/ip_sockglue.c#L1267">1267</a> 
<a name="L1268" href="source/net/ipv4/ip_sockglue.c#L1268">1268</a>                 inet_opt = <a href="ident?i=rcu_dereference_protected">rcu_dereference_protected</a>(inet-&gt;inet_opt,
<a name="L1269" href="source/net/ipv4/ip_sockglue.c#L1269">1269</a>                                                      <a href="ident?i=sock_owned_by_user">sock_owned_by_user</a>(sk));
<a name="L1270" href="source/net/ipv4/ip_sockglue.c#L1270">1270</a>                 opt-&gt;<a href="ident?i=optlen">optlen</a> = 0;
<a name="L1271" href="source/net/ipv4/ip_sockglue.c#L1271">1271</a>                 if (inet_opt)
<a name="L1272" href="source/net/ipv4/ip_sockglue.c#L1272">1272</a>                         <a href="ident?i=memcpy">memcpy</a>(optbuf, &amp;inet_opt-&gt;opt,
<a name="L1273" href="source/net/ipv4/ip_sockglue.c#L1273">1273</a>                                sizeof(struct <a href="ident?i=ip_options">ip_options</a>) +
<a name="L1274" href="source/net/ipv4/ip_sockglue.c#L1274">1274</a>                                inet_opt-&gt;opt.<a href="ident?i=optlen">optlen</a>);
<a name="L1275" href="source/net/ipv4/ip_sockglue.c#L1275">1275</a>                 <a href="ident?i=release_sock">release_sock</a>(sk);
<a name="L1276" href="source/net/ipv4/ip_sockglue.c#L1276">1276</a> 
<a name="L1277" href="source/net/ipv4/ip_sockglue.c#L1277">1277</a>                 if (opt-&gt;<a href="ident?i=optlen">optlen</a> == 0)
<a name="L1278" href="source/net/ipv4/ip_sockglue.c#L1278">1278</a>                         return <a href="ident?i=put_user">put_user</a>(0, <a href="ident?i=optlen">optlen</a>);
<a name="L1279" href="source/net/ipv4/ip_sockglue.c#L1279">1279</a> 
<a name="L1280" href="source/net/ipv4/ip_sockglue.c#L1280">1280</a>                 <a href="ident?i=ip_options_undo">ip_options_undo</a>(opt);
<a name="L1281" href="source/net/ipv4/ip_sockglue.c#L1281">1281</a> 
<a name="L1282" href="source/net/ipv4/ip_sockglue.c#L1282">1282</a>                 <a href="ident?i=len">len</a> = <a href="ident?i=min_t">min_t</a>(unsigned int, <a href="ident?i=len">len</a>, opt-&gt;<a href="ident?i=optlen">optlen</a>);
<a name="L1283" href="source/net/ipv4/ip_sockglue.c#L1283">1283</a>                 if (<a href="ident?i=put_user">put_user</a>(<a href="ident?i=len">len</a>, <a href="ident?i=optlen">optlen</a>))
<a name="L1284" href="source/net/ipv4/ip_sockglue.c#L1284">1284</a>                         return -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L1285" href="source/net/ipv4/ip_sockglue.c#L1285">1285</a>                 if (<a href="ident?i=copy_to_user">copy_to_user</a>(optval, opt-&gt;__data, <a href="ident?i=len">len</a>))
<a name="L1286" href="source/net/ipv4/ip_sockglue.c#L1286">1286</a>                         return -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L1287" href="source/net/ipv4/ip_sockglue.c#L1287">1287</a>                 return 0;
<a name="L1288" href="source/net/ipv4/ip_sockglue.c#L1288">1288</a>         }
<a name="L1289" href="source/net/ipv4/ip_sockglue.c#L1289">1289</a>         case <a href="ident?i=IP_PKTINFO">IP_PKTINFO</a>:
<a name="L1290" href="source/net/ipv4/ip_sockglue.c#L1290">1290</a>                 <a href="ident?i=val">val</a> = (inet-&gt;cmsg_flags &amp; <a href="ident?i=IP_CMSG_PKTINFO">IP_CMSG_PKTINFO</a>) != 0;
<a name="L1291" href="source/net/ipv4/ip_sockglue.c#L1291">1291</a>                 break;
<a name="L1292" href="source/net/ipv4/ip_sockglue.c#L1292">1292</a>         case <a href="ident?i=IP_RECVTTL">IP_RECVTTL</a>:
<a name="L1293" href="source/net/ipv4/ip_sockglue.c#L1293">1293</a>                 <a href="ident?i=val">val</a> = (inet-&gt;cmsg_flags &amp; <a href="ident?i=IP_CMSG_TTL">IP_CMSG_TTL</a>) != 0;
<a name="L1294" href="source/net/ipv4/ip_sockglue.c#L1294">1294</a>                 break;
<a name="L1295" href="source/net/ipv4/ip_sockglue.c#L1295">1295</a>         case <a href="ident?i=IP_RECVTOS">IP_RECVTOS</a>:
<a name="L1296" href="source/net/ipv4/ip_sockglue.c#L1296">1296</a>                 <a href="ident?i=val">val</a> = (inet-&gt;cmsg_flags &amp; <a href="ident?i=IP_CMSG_TOS">IP_CMSG_TOS</a>) != 0;
<a name="L1297" href="source/net/ipv4/ip_sockglue.c#L1297">1297</a>                 break;
<a name="L1298" href="source/net/ipv4/ip_sockglue.c#L1298">1298</a>         case <a href="ident?i=IP_RECVOPTS">IP_RECVOPTS</a>:
<a name="L1299" href="source/net/ipv4/ip_sockglue.c#L1299">1299</a>                 <a href="ident?i=val">val</a> = (inet-&gt;cmsg_flags &amp; <a href="ident?i=IP_CMSG_RECVOPTS">IP_CMSG_RECVOPTS</a>) != 0;
<a name="L1300" href="source/net/ipv4/ip_sockglue.c#L1300">1300</a>                 break;
<a name="L1301" href="source/net/ipv4/ip_sockglue.c#L1301">1301</a>         case <a href="ident?i=IP_RETOPTS">IP_RETOPTS</a>:
<a name="L1302" href="source/net/ipv4/ip_sockglue.c#L1302">1302</a>                 <a href="ident?i=val">val</a> = (inet-&gt;cmsg_flags &amp; <a href="ident?i=IP_CMSG_RETOPTS">IP_CMSG_RETOPTS</a>) != 0;
<a name="L1303" href="source/net/ipv4/ip_sockglue.c#L1303">1303</a>                 break;
<a name="L1304" href="source/net/ipv4/ip_sockglue.c#L1304">1304</a>         case <a href="ident?i=IP_PASSSEC">IP_PASSSEC</a>:
<a name="L1305" href="source/net/ipv4/ip_sockglue.c#L1305">1305</a>                 <a href="ident?i=val">val</a> = (inet-&gt;cmsg_flags &amp; <a href="ident?i=IP_CMSG_PASSSEC">IP_CMSG_PASSSEC</a>) != 0;
<a name="L1306" href="source/net/ipv4/ip_sockglue.c#L1306">1306</a>                 break;
<a name="L1307" href="source/net/ipv4/ip_sockglue.c#L1307">1307</a>         case <a href="ident?i=IP_RECVORIGDSTADDR">IP_RECVORIGDSTADDR</a>:
<a name="L1308" href="source/net/ipv4/ip_sockglue.c#L1308">1308</a>                 <a href="ident?i=val">val</a> = (inet-&gt;cmsg_flags &amp; <a href="ident?i=IP_CMSG_ORIGDSTADDR">IP_CMSG_ORIGDSTADDR</a>) != 0;
<a name="L1309" href="source/net/ipv4/ip_sockglue.c#L1309">1309</a>                 break;
<a name="L1310" href="source/net/ipv4/ip_sockglue.c#L1310">1310</a>         case <a href="ident?i=IP_CHECKSUM">IP_CHECKSUM</a>:
<a name="L1311" href="source/net/ipv4/ip_sockglue.c#L1311">1311</a>                 <a href="ident?i=val">val</a> = (inet-&gt;cmsg_flags &amp; <a href="ident?i=IP_CMSG_CHECKSUM">IP_CMSG_CHECKSUM</a>) != 0;
<a name="L1312" href="source/net/ipv4/ip_sockglue.c#L1312">1312</a>                 break;
<a name="L1313" href="source/net/ipv4/ip_sockglue.c#L1313">1313</a>         case <a href="ident?i=IP_TOS">IP_TOS</a>:
<a name="L1314" href="source/net/ipv4/ip_sockglue.c#L1314">1314</a>                 <a href="ident?i=val">val</a> = inet-&gt;tos;
<a name="L1315" href="source/net/ipv4/ip_sockglue.c#L1315">1315</a>                 break;
<a name="L1316" href="source/net/ipv4/ip_sockglue.c#L1316">1316</a>         case <a href="ident?i=IP_TTL">IP_TTL</a>:
<a name="L1317" href="source/net/ipv4/ip_sockglue.c#L1317">1317</a>                 <a href="ident?i=val">val</a> = (inet-&gt;uc_ttl == -1 ?
<a name="L1318" href="source/net/ipv4/ip_sockglue.c#L1318">1318</a>                        <a href="ident?i=sysctl_ip_default_ttl">sysctl_ip_default_ttl</a> :
<a name="L1319" href="source/net/ipv4/ip_sockglue.c#L1319">1319</a>                        inet-&gt;uc_ttl);
<a name="L1320" href="source/net/ipv4/ip_sockglue.c#L1320">1320</a>                 break;
<a name="L1321" href="source/net/ipv4/ip_sockglue.c#L1321">1321</a>         case <a href="ident?i=IP_HDRINCL">IP_HDRINCL</a>:
<a name="L1322" href="source/net/ipv4/ip_sockglue.c#L1322">1322</a>                 <a href="ident?i=val">val</a> = inet-&gt;hdrincl;
<a name="L1323" href="source/net/ipv4/ip_sockglue.c#L1323">1323</a>                 break;
<a name="L1324" href="source/net/ipv4/ip_sockglue.c#L1324">1324</a>         case <a href="ident?i=IP_NODEFRAG">IP_NODEFRAG</a>:
<a name="L1325" href="source/net/ipv4/ip_sockglue.c#L1325">1325</a>                 <a href="ident?i=val">val</a> = inet-&gt;nodefrag;
<a name="L1326" href="source/net/ipv4/ip_sockglue.c#L1326">1326</a>                 break;
<a name="L1327" href="source/net/ipv4/ip_sockglue.c#L1327">1327</a>         case <a href="ident?i=IP_MTU_DISCOVER">IP_MTU_DISCOVER</a>:
<a name="L1328" href="source/net/ipv4/ip_sockglue.c#L1328">1328</a>                 <a href="ident?i=val">val</a> = inet-&gt;pmtudisc;
<a name="L1329" href="source/net/ipv4/ip_sockglue.c#L1329">1329</a>                 break;
<a name="L1330" href="source/net/ipv4/ip_sockglue.c#L1330">1330</a>         case <a href="ident?i=IP_MTU">IP_MTU</a>:
<a name="L1331" href="source/net/ipv4/ip_sockglue.c#L1331">1331</a>         {
<a name="L1332" href="source/net/ipv4/ip_sockglue.c#L1332">1332</a>                 struct <a href="ident?i=dst_entry">dst_entry</a> *<a href="ident?i=dst">dst</a>;
<a name="L1333" href="source/net/ipv4/ip_sockglue.c#L1333">1333</a>                 <a href="ident?i=val">val</a> = 0;
<a name="L1334" href="source/net/ipv4/ip_sockglue.c#L1334">1334</a>                 <a href="ident?i=dst">dst</a> = <a href="ident?i=sk_dst_get">sk_dst_get</a>(sk);
<a name="L1335" href="source/net/ipv4/ip_sockglue.c#L1335">1335</a>                 if (<a href="ident?i=dst">dst</a>) {
<a name="L1336" href="source/net/ipv4/ip_sockglue.c#L1336">1336</a>                         <a href="ident?i=val">val</a> = <a href="ident?i=dst_mtu">dst_mtu</a>(<a href="ident?i=dst">dst</a>);
<a name="L1337" href="source/net/ipv4/ip_sockglue.c#L1337">1337</a>                         <a href="ident?i=dst_release">dst_release</a>(<a href="ident?i=dst">dst</a>);
<a name="L1338" href="source/net/ipv4/ip_sockglue.c#L1338">1338</a>                 }
<a name="L1339" href="source/net/ipv4/ip_sockglue.c#L1339">1339</a>                 if (!<a href="ident?i=val">val</a>) {
<a name="L1340" href="source/net/ipv4/ip_sockglue.c#L1340">1340</a>                         <a href="ident?i=release_sock">release_sock</a>(sk);
<a name="L1341" href="source/net/ipv4/ip_sockglue.c#L1341">1341</a>                         return -<a href="ident?i=ENOTCONN">ENOTCONN</a>;
<a name="L1342" href="source/net/ipv4/ip_sockglue.c#L1342">1342</a>                 }
<a name="L1343" href="source/net/ipv4/ip_sockglue.c#L1343">1343</a>                 break;
<a name="L1344" href="source/net/ipv4/ip_sockglue.c#L1344">1344</a>         }
<a name="L1345" href="source/net/ipv4/ip_sockglue.c#L1345">1345</a>         case <a href="ident?i=IP_RECVERR">IP_RECVERR</a>:
<a name="L1346" href="source/net/ipv4/ip_sockglue.c#L1346">1346</a>                 <a href="ident?i=val">val</a> = inet-&gt;recverr;
<a name="L1347" href="source/net/ipv4/ip_sockglue.c#L1347">1347</a>                 break;
<a name="L1348" href="source/net/ipv4/ip_sockglue.c#L1348">1348</a>         case <a href="ident?i=IP_MULTICAST_TTL">IP_MULTICAST_TTL</a>:
<a name="L1349" href="source/net/ipv4/ip_sockglue.c#L1349">1349</a>                 <a href="ident?i=val">val</a> = inet-&gt;mc_ttl;
<a name="L1350" href="source/net/ipv4/ip_sockglue.c#L1350">1350</a>                 break;
<a name="L1351" href="source/net/ipv4/ip_sockglue.c#L1351">1351</a>         case <a href="ident?i=IP_MULTICAST_LOOP">IP_MULTICAST_LOOP</a>:
<a name="L1352" href="source/net/ipv4/ip_sockglue.c#L1352">1352</a>                 <a href="ident?i=val">val</a> = inet-&gt;mc_loop;
<a name="L1353" href="source/net/ipv4/ip_sockglue.c#L1353">1353</a>                 break;
<a name="L1354" href="source/net/ipv4/ip_sockglue.c#L1354">1354</a>         case <a href="ident?i=IP_UNICAST_IF">IP_UNICAST_IF</a>:
<a name="L1355" href="source/net/ipv4/ip_sockglue.c#L1355">1355</a>                 <a href="ident?i=val">val</a> = (<a href="ident?i=__force">__force</a> int)<a href="ident?i=htonl">htonl</a>((<a href="ident?i=__u32">__u32</a>) inet-&gt;uc_index);
<a name="L1356" href="source/net/ipv4/ip_sockglue.c#L1356">1356</a>                 break;
<a name="L1357" href="source/net/ipv4/ip_sockglue.c#L1357">1357</a>         case <a href="ident?i=IP_MULTICAST_IF">IP_MULTICAST_IF</a>:
<a name="L1358" href="source/net/ipv4/ip_sockglue.c#L1358">1358</a>         {
<a name="L1359" href="source/net/ipv4/ip_sockglue.c#L1359">1359</a>                 struct <a href="ident?i=in_addr">in_addr</a> <a href="ident?i=addr">addr</a>;
<a name="L1360" href="source/net/ipv4/ip_sockglue.c#L1360">1360</a>                 <a href="ident?i=len">len</a> = <a href="ident?i=min_t">min_t</a>(unsigned int, <a href="ident?i=len">len</a>, sizeof(struct <a href="ident?i=in_addr">in_addr</a>));
<a name="L1361" href="source/net/ipv4/ip_sockglue.c#L1361">1361</a>                 <a href="ident?i=addr">addr</a>.s_addr = inet-&gt;mc_addr;
<a name="L1362" href="source/net/ipv4/ip_sockglue.c#L1362">1362</a>                 <a href="ident?i=release_sock">release_sock</a>(sk);
<a name="L1363" href="source/net/ipv4/ip_sockglue.c#L1363">1363</a> 
<a name="L1364" href="source/net/ipv4/ip_sockglue.c#L1364">1364</a>                 if (<a href="ident?i=put_user">put_user</a>(<a href="ident?i=len">len</a>, <a href="ident?i=optlen">optlen</a>))
<a name="L1365" href="source/net/ipv4/ip_sockglue.c#L1365">1365</a>                         return -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L1366" href="source/net/ipv4/ip_sockglue.c#L1366">1366</a>                 if (<a href="ident?i=copy_to_user">copy_to_user</a>(optval, &amp;<a href="ident?i=addr">addr</a>, <a href="ident?i=len">len</a>))
<a name="L1367" href="source/net/ipv4/ip_sockglue.c#L1367">1367</a>                         return -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L1368" href="source/net/ipv4/ip_sockglue.c#L1368">1368</a>                 return 0;
<a name="L1369" href="source/net/ipv4/ip_sockglue.c#L1369">1369</a>         }
<a name="L1370" href="source/net/ipv4/ip_sockglue.c#L1370">1370</a>         case <a href="ident?i=IP_MSFILTER">IP_MSFILTER</a>:
<a name="L1371" href="source/net/ipv4/ip_sockglue.c#L1371">1371</a>         {
<a name="L1372" href="source/net/ipv4/ip_sockglue.c#L1372">1372</a>                 struct <a href="ident?i=ip_msfilter">ip_msfilter</a> msf;
<a name="L1373" href="source/net/ipv4/ip_sockglue.c#L1373">1373</a>                 int <a href="ident?i=err">err</a>;
<a name="L1374" href="source/net/ipv4/ip_sockglue.c#L1374">1374</a> 
<a name="L1375" href="source/net/ipv4/ip_sockglue.c#L1375">1375</a>                 if (<a href="ident?i=len">len</a> &lt; <a href="ident?i=IP_MSFILTER_SIZE">IP_MSFILTER_SIZE</a>(0)) {
<a name="L1376" href="source/net/ipv4/ip_sockglue.c#L1376">1376</a>                         <a href="ident?i=release_sock">release_sock</a>(sk);
<a name="L1377" href="source/net/ipv4/ip_sockglue.c#L1377">1377</a>                         return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L1378" href="source/net/ipv4/ip_sockglue.c#L1378">1378</a>                 }
<a name="L1379" href="source/net/ipv4/ip_sockglue.c#L1379">1379</a>                 if (<a href="ident?i=copy_from_user">copy_from_user</a>(&amp;msf, optval, <a href="ident?i=IP_MSFILTER_SIZE">IP_MSFILTER_SIZE</a>(0))) {
<a name="L1380" href="source/net/ipv4/ip_sockglue.c#L1380">1380</a>                         <a href="ident?i=release_sock">release_sock</a>(sk);
<a name="L1381" href="source/net/ipv4/ip_sockglue.c#L1381">1381</a>                         return -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L1382" href="source/net/ipv4/ip_sockglue.c#L1382">1382</a>                 }
<a name="L1383" href="source/net/ipv4/ip_sockglue.c#L1383">1383</a>                 <a href="ident?i=err">err</a> = <a href="ident?i=ip_mc_msfget">ip_mc_msfget</a>(sk, &amp;msf,
<a name="L1384" href="source/net/ipv4/ip_sockglue.c#L1384">1384</a>                                    (struct <a href="ident?i=ip_msfilter">ip_msfilter</a> <a href="ident?i=__user">__user</a> *)optval, <a href="ident?i=optlen">optlen</a>);
<a name="L1385" href="source/net/ipv4/ip_sockglue.c#L1385">1385</a>                 <a href="ident?i=release_sock">release_sock</a>(sk);
<a name="L1386" href="source/net/ipv4/ip_sockglue.c#L1386">1386</a>                 return <a href="ident?i=err">err</a>;
<a name="L1387" href="source/net/ipv4/ip_sockglue.c#L1387">1387</a>         }
<a name="L1388" href="source/net/ipv4/ip_sockglue.c#L1388">1388</a>         case <a href="ident?i=MCAST_MSFILTER">MCAST_MSFILTER</a>:
<a name="L1389" href="source/net/ipv4/ip_sockglue.c#L1389">1389</a>         {
<a name="L1390" href="source/net/ipv4/ip_sockglue.c#L1390">1390</a>                 struct <a href="ident?i=group_filter">group_filter</a> gsf;
<a name="L1391" href="source/net/ipv4/ip_sockglue.c#L1391">1391</a>                 int <a href="ident?i=err">err</a>;
<a name="L1392" href="source/net/ipv4/ip_sockglue.c#L1392">1392</a> 
<a name="L1393" href="source/net/ipv4/ip_sockglue.c#L1393">1393</a>                 if (<a href="ident?i=len">len</a> &lt; <a href="ident?i=GROUP_FILTER_SIZE">GROUP_FILTER_SIZE</a>(0)) {
<a name="L1394" href="source/net/ipv4/ip_sockglue.c#L1394">1394</a>                         <a href="ident?i=release_sock">release_sock</a>(sk);
<a name="L1395" href="source/net/ipv4/ip_sockglue.c#L1395">1395</a>                         return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L1396" href="source/net/ipv4/ip_sockglue.c#L1396">1396</a>                 }
<a name="L1397" href="source/net/ipv4/ip_sockglue.c#L1397">1397</a>                 if (<a href="ident?i=copy_from_user">copy_from_user</a>(&amp;gsf, optval, <a href="ident?i=GROUP_FILTER_SIZE">GROUP_FILTER_SIZE</a>(0))) {
<a name="L1398" href="source/net/ipv4/ip_sockglue.c#L1398">1398</a>                         <a href="ident?i=release_sock">release_sock</a>(sk);
<a name="L1399" href="source/net/ipv4/ip_sockglue.c#L1399">1399</a>                         return -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L1400" href="source/net/ipv4/ip_sockglue.c#L1400">1400</a>                 }
<a name="L1401" href="source/net/ipv4/ip_sockglue.c#L1401">1401</a>                 <a href="ident?i=err">err</a> = <a href="ident?i=ip_mc_gsfget">ip_mc_gsfget</a>(sk, &amp;gsf,
<a name="L1402" href="source/net/ipv4/ip_sockglue.c#L1402">1402</a>                                    (struct <a href="ident?i=group_filter">group_filter</a> <a href="ident?i=__user">__user</a> *)optval,
<a name="L1403" href="source/net/ipv4/ip_sockglue.c#L1403">1403</a>                                    <a href="ident?i=optlen">optlen</a>);
<a name="L1404" href="source/net/ipv4/ip_sockglue.c#L1404">1404</a>                 <a href="ident?i=release_sock">release_sock</a>(sk);
<a name="L1405" href="source/net/ipv4/ip_sockglue.c#L1405">1405</a>                 return <a href="ident?i=err">err</a>;
<a name="L1406" href="source/net/ipv4/ip_sockglue.c#L1406">1406</a>         }
<a name="L1407" href="source/net/ipv4/ip_sockglue.c#L1407">1407</a>         case <a href="ident?i=IP_MULTICAST_ALL">IP_MULTICAST_ALL</a>:
<a name="L1408" href="source/net/ipv4/ip_sockglue.c#L1408">1408</a>                 <a href="ident?i=val">val</a> = inet-&gt;mc_all;
<a name="L1409" href="source/net/ipv4/ip_sockglue.c#L1409">1409</a>                 break;
<a name="L1410" href="source/net/ipv4/ip_sockglue.c#L1410">1410</a>         case <a href="ident?i=IP_PKTOPTIONS">IP_PKTOPTIONS</a>:
<a name="L1411" href="source/net/ipv4/ip_sockglue.c#L1411">1411</a>         {
<a name="L1412" href="source/net/ipv4/ip_sockglue.c#L1412">1412</a>                 struct <a href="ident?i=msghdr">msghdr</a> <a href="ident?i=msg">msg</a>;
<a name="L1413" href="source/net/ipv4/ip_sockglue.c#L1413">1413</a> 
<a name="L1414" href="source/net/ipv4/ip_sockglue.c#L1414">1414</a>                 <a href="ident?i=release_sock">release_sock</a>(sk);
<a name="L1415" href="source/net/ipv4/ip_sockglue.c#L1415">1415</a> 
<a name="L1416" href="source/net/ipv4/ip_sockglue.c#L1416">1416</a>                 if (sk-&gt;sk_type != SOCK_STREAM)
<a name="L1417" href="source/net/ipv4/ip_sockglue.c#L1417">1417</a>                         return -<a href="ident?i=ENOPROTOOPT">ENOPROTOOPT</a>;
<a name="L1418" href="source/net/ipv4/ip_sockglue.c#L1418">1418</a> 
<a name="L1419" href="source/net/ipv4/ip_sockglue.c#L1419">1419</a>                 <a href="ident?i=msg">msg</a>.msg_control = (<a href="ident?i=__force">__force</a> void *) optval;
<a name="L1420" href="source/net/ipv4/ip_sockglue.c#L1420">1420</a>                 <a href="ident?i=msg">msg</a>.msg_controllen = <a href="ident?i=len">len</a>;
<a name="L1421" href="source/net/ipv4/ip_sockglue.c#L1421">1421</a>                 <a href="ident?i=msg">msg</a>.msg_flags = <a href="ident?i=flags">flags</a>;
<a name="L1422" href="source/net/ipv4/ip_sockglue.c#L1422">1422</a> 
<a name="L1423" href="source/net/ipv4/ip_sockglue.c#L1423">1423</a>                 if (inet-&gt;cmsg_flags &amp; <a href="ident?i=IP_CMSG_PKTINFO">IP_CMSG_PKTINFO</a>) {
<a name="L1424" href="source/net/ipv4/ip_sockglue.c#L1424">1424</a>                         struct <a href="ident?i=in_pktinfo">in_pktinfo</a> <a href="ident?i=info">info</a>;
<a name="L1425" href="source/net/ipv4/ip_sockglue.c#L1425">1425</a> 
<a name="L1426" href="source/net/ipv4/ip_sockglue.c#L1426">1426</a>                         <a href="ident?i=info">info</a>.ipi_addr.s_addr = inet-&gt;<a href="ident?i=inet_rcv_saddr">inet_rcv_saddr</a>;
<a name="L1427" href="source/net/ipv4/ip_sockglue.c#L1427">1427</a>                         <a href="ident?i=info">info</a>.ipi_spec_dst.s_addr = inet-&gt;<a href="ident?i=inet_rcv_saddr">inet_rcv_saddr</a>;
<a name="L1428" href="source/net/ipv4/ip_sockglue.c#L1428">1428</a>                         <a href="ident?i=info">info</a>.ipi_ifindex = inet-&gt;mc_index;
<a name="L1429" href="source/net/ipv4/ip_sockglue.c#L1429">1429</a>                         <a href="ident?i=put_cmsg">put_cmsg</a>(&amp;<a href="ident?i=msg">msg</a>, <a href="ident?i=SOL_IP">SOL_IP</a>, <a href="ident?i=IP_PKTINFO">IP_PKTINFO</a>, sizeof(<a href="ident?i=info">info</a>), &amp;<a href="ident?i=info">info</a>);
<a name="L1430" href="source/net/ipv4/ip_sockglue.c#L1430">1430</a>                 }
<a name="L1431" href="source/net/ipv4/ip_sockglue.c#L1431">1431</a>                 if (inet-&gt;cmsg_flags &amp; <a href="ident?i=IP_CMSG_TTL">IP_CMSG_TTL</a>) {
<a name="L1432" href="source/net/ipv4/ip_sockglue.c#L1432">1432</a>                         int hlim = inet-&gt;mc_ttl;
<a name="L1433" href="source/net/ipv4/ip_sockglue.c#L1433">1433</a>                         <a href="ident?i=put_cmsg">put_cmsg</a>(&amp;<a href="ident?i=msg">msg</a>, <a href="ident?i=SOL_IP">SOL_IP</a>, <a href="ident?i=IP_TTL">IP_TTL</a>, sizeof(hlim), &amp;hlim);
<a name="L1434" href="source/net/ipv4/ip_sockglue.c#L1434">1434</a>                 }
<a name="L1435" href="source/net/ipv4/ip_sockglue.c#L1435">1435</a>                 if (inet-&gt;cmsg_flags &amp; <a href="ident?i=IP_CMSG_TOS">IP_CMSG_TOS</a>) {
<a name="L1436" href="source/net/ipv4/ip_sockglue.c#L1436">1436</a>                         int tos = inet-&gt;rcv_tos;
<a name="L1437" href="source/net/ipv4/ip_sockglue.c#L1437">1437</a>                         <a href="ident?i=put_cmsg">put_cmsg</a>(&amp;<a href="ident?i=msg">msg</a>, <a href="ident?i=SOL_IP">SOL_IP</a>, <a href="ident?i=IP_TOS">IP_TOS</a>, sizeof(tos), &amp;tos);
<a name="L1438" href="source/net/ipv4/ip_sockglue.c#L1438">1438</a>                 }
<a name="L1439" href="source/net/ipv4/ip_sockglue.c#L1439">1439</a>                 <a href="ident?i=len">len</a> -= <a href="ident?i=msg">msg</a>.msg_controllen;
<a name="L1440" href="source/net/ipv4/ip_sockglue.c#L1440">1440</a>                 return <a href="ident?i=put_user">put_user</a>(<a href="ident?i=len">len</a>, <a href="ident?i=optlen">optlen</a>);
<a name="L1441" href="source/net/ipv4/ip_sockglue.c#L1441">1441</a>         }
<a name="L1442" href="source/net/ipv4/ip_sockglue.c#L1442">1442</a>         case <a href="ident?i=IP_FREEBIND">IP_FREEBIND</a>:
<a name="L1443" href="source/net/ipv4/ip_sockglue.c#L1443">1443</a>                 <a href="ident?i=val">val</a> = inet-&gt;freebind;
<a name="L1444" href="source/net/ipv4/ip_sockglue.c#L1444">1444</a>                 break;
<a name="L1445" href="source/net/ipv4/ip_sockglue.c#L1445">1445</a>         case <a href="ident?i=IP_TRANSPARENT">IP_TRANSPARENT</a>:
<a name="L1446" href="source/net/ipv4/ip_sockglue.c#L1446">1446</a>                 <a href="ident?i=val">val</a> = inet-&gt;transparent;
<a name="L1447" href="source/net/ipv4/ip_sockglue.c#L1447">1447</a>                 break;
<a name="L1448" href="source/net/ipv4/ip_sockglue.c#L1448">1448</a>         case <a href="ident?i=IP_MINTTL">IP_MINTTL</a>:
<a name="L1449" href="source/net/ipv4/ip_sockglue.c#L1449">1449</a>                 <a href="ident?i=val">val</a> = inet-&gt;<a href="ident?i=min_ttl">min_ttl</a>;
<a name="L1450" href="source/net/ipv4/ip_sockglue.c#L1450">1450</a>                 break;
<a name="L1451" href="source/net/ipv4/ip_sockglue.c#L1451">1451</a>         default:
<a name="L1452" href="source/net/ipv4/ip_sockglue.c#L1452">1452</a>                 <a href="ident?i=release_sock">release_sock</a>(sk);
<a name="L1453" href="source/net/ipv4/ip_sockglue.c#L1453">1453</a>                 return -<a href="ident?i=ENOPROTOOPT">ENOPROTOOPT</a>;
<a name="L1454" href="source/net/ipv4/ip_sockglue.c#L1454">1454</a>         }
<a name="L1455" href="source/net/ipv4/ip_sockglue.c#L1455">1455</a>         <a href="ident?i=release_sock">release_sock</a>(sk);
<a name="L1456" href="source/net/ipv4/ip_sockglue.c#L1456">1456</a> 
<a name="L1457" href="source/net/ipv4/ip_sockglue.c#L1457">1457</a>         if (<a href="ident?i=len">len</a> &lt; sizeof(int) &amp;&amp; <a href="ident?i=len">len</a> &gt; 0 &amp;&amp; <a href="ident?i=val">val</a> &gt;= 0 &amp;&amp; <a href="ident?i=val">val</a> &lt;= 255) {
<a name="L1458" href="source/net/ipv4/ip_sockglue.c#L1458">1458</a>                 unsigned char ucval = (unsigned char)<a href="ident?i=val">val</a>;
<a name="L1459" href="source/net/ipv4/ip_sockglue.c#L1459">1459</a>                 <a href="ident?i=len">len</a> = 1;
<a name="L1460" href="source/net/ipv4/ip_sockglue.c#L1460">1460</a>                 if (<a href="ident?i=put_user">put_user</a>(<a href="ident?i=len">len</a>, <a href="ident?i=optlen">optlen</a>))
<a name="L1461" href="source/net/ipv4/ip_sockglue.c#L1461">1461</a>                         return -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L1462" href="source/net/ipv4/ip_sockglue.c#L1462">1462</a>                 if (<a href="ident?i=copy_to_user">copy_to_user</a>(optval, &amp;ucval, 1))
<a name="L1463" href="source/net/ipv4/ip_sockglue.c#L1463">1463</a>                         return -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L1464" href="source/net/ipv4/ip_sockglue.c#L1464">1464</a>         } else {
<a name="L1465" href="source/net/ipv4/ip_sockglue.c#L1465">1465</a>                 <a href="ident?i=len">len</a> = <a href="ident?i=min_t">min_t</a>(unsigned int, sizeof(int), <a href="ident?i=len">len</a>);
<a name="L1466" href="source/net/ipv4/ip_sockglue.c#L1466">1466</a>                 if (<a href="ident?i=put_user">put_user</a>(<a href="ident?i=len">len</a>, <a href="ident?i=optlen">optlen</a>))
<a name="L1467" href="source/net/ipv4/ip_sockglue.c#L1467">1467</a>                         return -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L1468" href="source/net/ipv4/ip_sockglue.c#L1468">1468</a>                 if (<a href="ident?i=copy_to_user">copy_to_user</a>(optval, &amp;<a href="ident?i=val">val</a>, <a href="ident?i=len">len</a>))
<a name="L1469" href="source/net/ipv4/ip_sockglue.c#L1469">1469</a>                         return -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L1470" href="source/net/ipv4/ip_sockglue.c#L1470">1470</a>         }
<a name="L1471" href="source/net/ipv4/ip_sockglue.c#L1471">1471</a>         return 0;
<a name="L1472" href="source/net/ipv4/ip_sockglue.c#L1472">1472</a> }
<a name="L1473" href="source/net/ipv4/ip_sockglue.c#L1473">1473</a> 
<a name="L1474" href="source/net/ipv4/ip_sockglue.c#L1474">1474</a> int <a href="ident?i=ip_getsockopt">ip_getsockopt</a>(struct <a href="ident?i=sock">sock</a> *sk, int <a href="ident?i=level">level</a>,
<a name="L1475" href="source/net/ipv4/ip_sockglue.c#L1475">1475</a>                   int optname, char <a href="ident?i=__user">__user</a> *optval, int <a href="ident?i=__user">__user</a> *<a href="ident?i=optlen">optlen</a>)
<a name="L1476" href="source/net/ipv4/ip_sockglue.c#L1476">1476</a> {
<a name="L1477" href="source/net/ipv4/ip_sockglue.c#L1477">1477</a>         int <a href="ident?i=err">err</a>;
<a name="L1478" href="source/net/ipv4/ip_sockglue.c#L1478">1478</a> 
<a name="L1479" href="source/net/ipv4/ip_sockglue.c#L1479">1479</a>         <a href="ident?i=err">err</a> = <a href="ident?i=do_ip_getsockopt">do_ip_getsockopt</a>(sk, <a href="ident?i=level">level</a>, optname, optval, <a href="ident?i=optlen">optlen</a>, 0);
<a name="L1480" href="source/net/ipv4/ip_sockglue.c#L1480">1480</a> #ifdef CONFIG_NETFILTER
<a name="L1481" href="source/net/ipv4/ip_sockglue.c#L1481">1481</a>         <b><i>/* we need to exclude all possible ENOPROTOOPTs except default case */</i></b>
<a name="L1482" href="source/net/ipv4/ip_sockglue.c#L1482">1482</a>         if (<a href="ident?i=err">err</a> == -<a href="ident?i=ENOPROTOOPT">ENOPROTOOPT</a> &amp;&amp; optname != <a href="ident?i=IP_PKTOPTIONS">IP_PKTOPTIONS</a> &amp;&amp;
<a name="L1483" href="source/net/ipv4/ip_sockglue.c#L1483">1483</a>                         !<a href="ident?i=ip_mroute_opt">ip_mroute_opt</a>(optname)) {
<a name="L1484" href="source/net/ipv4/ip_sockglue.c#L1484">1484</a>                 int <a href="ident?i=len">len</a>;
<a name="L1485" href="source/net/ipv4/ip_sockglue.c#L1485">1485</a> 
<a name="L1486" href="source/net/ipv4/ip_sockglue.c#L1486">1486</a>                 if (<a href="ident?i=get_user">get_user</a>(<a href="ident?i=len">len</a>, <a href="ident?i=optlen">optlen</a>))
<a name="L1487" href="source/net/ipv4/ip_sockglue.c#L1487">1487</a>                         return -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L1488" href="source/net/ipv4/ip_sockglue.c#L1488">1488</a> 
<a name="L1489" href="source/net/ipv4/ip_sockglue.c#L1489">1489</a>                 <a href="ident?i=lock_sock">lock_sock</a>(sk);
<a name="L1490" href="source/net/ipv4/ip_sockglue.c#L1490">1490</a>                 <a href="ident?i=err">err</a> = <a href="ident?i=nf_getsockopt">nf_getsockopt</a>(sk, <a href="ident?i=PF_INET">PF_INET</a>, optname, optval,
<a name="L1491" href="source/net/ipv4/ip_sockglue.c#L1491">1491</a>                                 &amp;<a href="ident?i=len">len</a>);
<a name="L1492" href="source/net/ipv4/ip_sockglue.c#L1492">1492</a>                 <a href="ident?i=release_sock">release_sock</a>(sk);
<a name="L1493" href="source/net/ipv4/ip_sockglue.c#L1493">1493</a>                 if (<a href="ident?i=err">err</a> &gt;= 0)
<a name="L1494" href="source/net/ipv4/ip_sockglue.c#L1494">1494</a>                         <a href="ident?i=err">err</a> = <a href="ident?i=put_user">put_user</a>(<a href="ident?i=len">len</a>, <a href="ident?i=optlen">optlen</a>);
<a name="L1495" href="source/net/ipv4/ip_sockglue.c#L1495">1495</a>                 return <a href="ident?i=err">err</a>;
<a name="L1496" href="source/net/ipv4/ip_sockglue.c#L1496">1496</a>         }
<a name="L1497" href="source/net/ipv4/ip_sockglue.c#L1497">1497</a> #endif
<a name="L1498" href="source/net/ipv4/ip_sockglue.c#L1498">1498</a>         return <a href="ident?i=err">err</a>;
<a name="L1499" href="source/net/ipv4/ip_sockglue.c#L1499">1499</a> }
<a name="L1500" href="source/net/ipv4/ip_sockglue.c#L1500">1500</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=ip_getsockopt">ip_getsockopt</a>);
<a name="L1501" href="source/net/ipv4/ip_sockglue.c#L1501">1501</a> 
<a name="L1502" href="source/net/ipv4/ip_sockglue.c#L1502">1502</a> #ifdef CONFIG_COMPAT
<a name="L1503" href="source/net/ipv4/ip_sockglue.c#L1503">1503</a> int <a href="ident?i=compat_ip_getsockopt">compat_ip_getsockopt</a>(struct <a href="ident?i=sock">sock</a> *sk, int <a href="ident?i=level">level</a>, int optname,
<a name="L1504" href="source/net/ipv4/ip_sockglue.c#L1504">1504</a>                          char <a href="ident?i=__user">__user</a> *optval, int <a href="ident?i=__user">__user</a> *<a href="ident?i=optlen">optlen</a>)
<a name="L1505" href="source/net/ipv4/ip_sockglue.c#L1505">1505</a> {
<a name="L1506" href="source/net/ipv4/ip_sockglue.c#L1506">1506</a>         int <a href="ident?i=err">err</a>;
<a name="L1507" href="source/net/ipv4/ip_sockglue.c#L1507">1507</a> 
<a name="L1508" href="source/net/ipv4/ip_sockglue.c#L1508">1508</a>         if (optname == <a href="ident?i=MCAST_MSFILTER">MCAST_MSFILTER</a>)
<a name="L1509" href="source/net/ipv4/ip_sockglue.c#L1509">1509</a>                 return <a href="ident?i=compat_mc_getsockopt">compat_mc_getsockopt</a>(sk, <a href="ident?i=level">level</a>, optname, optval, <a href="ident?i=optlen">optlen</a>,
<a name="L1510" href="source/net/ipv4/ip_sockglue.c#L1510">1510</a>                         <a href="ident?i=ip_getsockopt">ip_getsockopt</a>);
<a name="L1511" href="source/net/ipv4/ip_sockglue.c#L1511">1511</a> 
<a name="L1512" href="source/net/ipv4/ip_sockglue.c#L1512">1512</a>         <a href="ident?i=err">err</a> = <a href="ident?i=do_ip_getsockopt">do_ip_getsockopt</a>(sk, <a href="ident?i=level">level</a>, optname, optval, <a href="ident?i=optlen">optlen</a>,
<a name="L1513" href="source/net/ipv4/ip_sockglue.c#L1513">1513</a>                 <a href="ident?i=MSG_CMSG_COMPAT">MSG_CMSG_COMPAT</a>);
<a name="L1514" href="source/net/ipv4/ip_sockglue.c#L1514">1514</a> 
<a name="L1515" href="source/net/ipv4/ip_sockglue.c#L1515">1515</a> #ifdef CONFIG_NETFILTER
<a name="L1516" href="source/net/ipv4/ip_sockglue.c#L1516">1516</a>         <b><i>/* we need to exclude all possible ENOPROTOOPTs except default case */</i></b>
<a name="L1517" href="source/net/ipv4/ip_sockglue.c#L1517">1517</a>         if (<a href="ident?i=err">err</a> == -<a href="ident?i=ENOPROTOOPT">ENOPROTOOPT</a> &amp;&amp; optname != <a href="ident?i=IP_PKTOPTIONS">IP_PKTOPTIONS</a> &amp;&amp;
<a name="L1518" href="source/net/ipv4/ip_sockglue.c#L1518">1518</a>                         !<a href="ident?i=ip_mroute_opt">ip_mroute_opt</a>(optname)) {
<a name="L1519" href="source/net/ipv4/ip_sockglue.c#L1519">1519</a>                 int <a href="ident?i=len">len</a>;
<a name="L1520" href="source/net/ipv4/ip_sockglue.c#L1520">1520</a> 
<a name="L1521" href="source/net/ipv4/ip_sockglue.c#L1521">1521</a>                 if (<a href="ident?i=get_user">get_user</a>(<a href="ident?i=len">len</a>, <a href="ident?i=optlen">optlen</a>))
<a name="L1522" href="source/net/ipv4/ip_sockglue.c#L1522">1522</a>                         return -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L1523" href="source/net/ipv4/ip_sockglue.c#L1523">1523</a> 
<a name="L1524" href="source/net/ipv4/ip_sockglue.c#L1524">1524</a>                 <a href="ident?i=lock_sock">lock_sock</a>(sk);
<a name="L1525" href="source/net/ipv4/ip_sockglue.c#L1525">1525</a>                 <a href="ident?i=err">err</a> = <a href="ident?i=compat_nf_getsockopt">compat_nf_getsockopt</a>(sk, <a href="ident?i=PF_INET">PF_INET</a>, optname, optval, &amp;<a href="ident?i=len">len</a>);
<a name="L1526" href="source/net/ipv4/ip_sockglue.c#L1526">1526</a>                 <a href="ident?i=release_sock">release_sock</a>(sk);
<a name="L1527" href="source/net/ipv4/ip_sockglue.c#L1527">1527</a>                 if (<a href="ident?i=err">err</a> &gt;= 0)
<a name="L1528" href="source/net/ipv4/ip_sockglue.c#L1528">1528</a>                         <a href="ident?i=err">err</a> = <a href="ident?i=put_user">put_user</a>(<a href="ident?i=len">len</a>, <a href="ident?i=optlen">optlen</a>);
<a name="L1529" href="source/net/ipv4/ip_sockglue.c#L1529">1529</a>                 return <a href="ident?i=err">err</a>;
<a name="L1530" href="source/net/ipv4/ip_sockglue.c#L1530">1530</a>         }
<a name="L1531" href="source/net/ipv4/ip_sockglue.c#L1531">1531</a> #endif
<a name="L1532" href="source/net/ipv4/ip_sockglue.c#L1532">1532</a>         return <a href="ident?i=err">err</a>;
<a name="L1533" href="source/net/ipv4/ip_sockglue.c#L1533">1533</a> }
<a name="L1534" href="source/net/ipv4/ip_sockglue.c#L1534">1534</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=compat_ip_getsockopt">compat_ip_getsockopt</a>);
<a name="L1535" href="source/net/ipv4/ip_sockglue.c#L1535">1535</a> #endif
<a name="L1536" href="source/net/ipv4/ip_sockglue.c#L1536">1536</a> </pre></div><p>
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
