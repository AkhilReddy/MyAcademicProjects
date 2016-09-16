<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title>Linux/net/ipv4/ip_options.c - Linux Cross Reference - Free Electrons</title>
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
		 &nbsp;&bull;&nbsp;<b><i>source navigation</i></b> &nbsp;&bull;&nbsp;<a href="diff/net/ipv4/ip_options.c">diff markup</a> &nbsp;&bull;&nbsp;<a href="ident">identifier search</a> &nbsp;&bull;&nbsp;<a href="search">freetext search</a> &nbsp;&bull;&nbsp;
		</p>
	</div>
</div>

<div id="topbar">
  
  <p>Version: &nbsp;<a href="source/net/ipv4/ip_options.c?v=2.0.40">2.0.40</a>&nbsp;<a href="source/net/ipv4/ip_options.c?v=2.2.26">2.2.26</a>&nbsp;<a href="source/net/ipv4/ip_options.c?v=2.4.37">2.4.37</a>&nbsp;<a href="source/net/ipv4/ip_options.c?v=3.5">3.5</a>&nbsp;<a href="source/net/ipv4/ip_options.c?v=3.6">3.6</a>&nbsp;<a href="source/net/ipv4/ip_options.c?v=3.7">3.7</a>&nbsp;<a href="source/net/ipv4/ip_options.c?v=3.8">3.8</a>&nbsp;<a href="source/net/ipv4/ip_options.c?v=3.9">3.9</a>&nbsp;<a href="source/net/ipv4/ip_options.c?v=3.10">3.10</a>&nbsp;<a href="source/net/ipv4/ip_options.c?v=3.11">3.11</a>&nbsp;<a href="source/net/ipv4/ip_options.c?v=3.12">3.12</a>&nbsp;<a href="source/net/ipv4/ip_options.c?v=3.13">3.13</a>&nbsp;<a href="source/net/ipv4/ip_options.c?v=3.14">3.14</a>&nbsp;<a href="source/net/ipv4/ip_options.c?v=3.15">3.15</a>&nbsp;<a href="source/net/ipv4/ip_options.c?v=3.16">3.16</a>&nbsp;<a href="source/net/ipv4/ip_options.c?v=3.17">3.17</a>&nbsp;<a href="source/net/ipv4/ip_options.c?v=3.18">3.18</a>&nbsp;<a href="source/net/ipv4/ip_options.c?v=3.19">3.19</a>&nbsp;<a href="source/net/ipv4/ip_options.c?v=4.0">4.0</a>&nbsp;<b><i>4.1</i></b></p>
  
</div>

<h1><a href="source/">Linux</a>/<a href="source/net/">net</a>/<a href="source/net/ipv4/">ipv4</a>/<a href="source/net/ipv4/ip_options.c">ip_options.c</a></h1>
<div id="lxrcode"><pre>  <a name="L1" href="source/net/ipv4/ip_options.c#L1">1</a> <b><i>/*</i></b>
  <a name="L2" href="source/net/ipv4/ip_options.c#L2">2</a> <b><i> * INET         An implementation of the TCP/IP protocol suite for the LINUX</i></b>
  <a name="L3" href="source/net/ipv4/ip_options.c#L3">3</a> <b><i> *              operating system.  INET is implemented using the  BSD Socket</i></b>
  <a name="L4" href="source/net/ipv4/ip_options.c#L4">4</a> <b><i> *              interface as the means of communication with the user level.</i></b>
  <a name="L5" href="source/net/ipv4/ip_options.c#L5">5</a> <b><i> *</i></b>
  <a name="L6" href="source/net/ipv4/ip_options.c#L6">6</a> <b><i> *              The options processing module for ip.c</i></b>
  <a name="L7" href="source/net/ipv4/ip_options.c#L7">7</a> <b><i> *</i></b>
  <a name="L8" href="source/net/ipv4/ip_options.c#L8">8</a> <b><i> * Authors:     A.N.Kuznetsov</i></b>
  <a name="L9" href="source/net/ipv4/ip_options.c#L9">9</a> <b><i> *</i></b>
 <a name="L10" href="source/net/ipv4/ip_options.c#L10">10</a> <b><i> */</i></b>
 <a name="L11" href="source/net/ipv4/ip_options.c#L11">11</a> 
 <a name="L12" href="source/net/ipv4/ip_options.c#L12">12</a> #define <a href="ident?i=pr_fmt">pr_fmt</a>(<a href="ident?i=fmt">fmt</a>) <i>"IPv4: "</i> <a href="ident?i=fmt">fmt</a>
 <a name="L13" href="source/net/ipv4/ip_options.c#L13">13</a> 
 <a name="L14" href="source/net/ipv4/ip_options.c#L14">14</a> #include &lt;linux/capability.h&gt;
 <a name="L15" href="source/net/ipv4/ip_options.c#L15">15</a> #include &lt;linux/module.h&gt;
 <a name="L16" href="source/net/ipv4/ip_options.c#L16">16</a> #include &lt;linux/slab.h&gt;
 <a name="L17" href="source/net/ipv4/ip_options.c#L17">17</a> #include &lt;linux/types.h&gt;
 <a name="L18" href="source/net/ipv4/ip_options.c#L18">18</a> #include &lt;asm/uaccess.h&gt;
 <a name="L19" href="source/net/ipv4/ip_options.c#L19">19</a> #include &lt;asm/unaligned.h&gt;
 <a name="L20" href="source/net/ipv4/ip_options.c#L20">20</a> #include &lt;linux/skbuff.h&gt;
 <a name="L21" href="source/net/ipv4/ip_options.c#L21">21</a> #include &lt;linux/ip.h&gt;
 <a name="L22" href="source/net/ipv4/ip_options.c#L22">22</a> #include &lt;linux/icmp.h&gt;
 <a name="L23" href="source/net/ipv4/ip_options.c#L23">23</a> #include &lt;linux/netdevice.h&gt;
 <a name="L24" href="source/net/ipv4/ip_options.c#L24">24</a> #include &lt;linux/rtnetlink.h&gt;
 <a name="L25" href="source/net/ipv4/ip_options.c#L25">25</a> #include &lt;net/sock.h&gt;
 <a name="L26" href="source/net/ipv4/ip_options.c#L26">26</a> #include &lt;net/ip.h&gt;
 <a name="L27" href="source/net/ipv4/ip_options.c#L27">27</a> #include &lt;net/icmp.h&gt;
 <a name="L28" href="source/net/ipv4/ip_options.c#L28">28</a> #include &lt;net/route.h&gt;
 <a name="L29" href="source/net/ipv4/ip_options.c#L29">29</a> #include &lt;net/cipso_ipv4.h&gt;
 <a name="L30" href="source/net/ipv4/ip_options.c#L30">30</a> #include &lt;net/ip_fib.h&gt;
 <a name="L31" href="source/net/ipv4/ip_options.c#L31">31</a> 
 <a name="L32" href="source/net/ipv4/ip_options.c#L32">32</a> <b><i>/*</i></b>
 <a name="L33" href="source/net/ipv4/ip_options.c#L33">33</a> <b><i> * Write options to IP header, record destination address to</i></b>
 <a name="L34" href="source/net/ipv4/ip_options.c#L34">34</a> <b><i> * source route option, address of outgoing interface</i></b>
 <a name="L35" href="source/net/ipv4/ip_options.c#L35">35</a> <b><i> * (we should already know it, so that this  function is allowed be</i></b>
 <a name="L36" href="source/net/ipv4/ip_options.c#L36">36</a> <b><i> * called only after routing decision) and timestamp,</i></b>
 <a name="L37" href="source/net/ipv4/ip_options.c#L37">37</a> <b><i> * if we originate this datagram.</i></b>
 <a name="L38" href="source/net/ipv4/ip_options.c#L38">38</a> <b><i> *</i></b>
 <a name="L39" href="source/net/ipv4/ip_options.c#L39">39</a> <b><i> * daddr is real destination address, next hop is recorded in IP header.</i></b>
 <a name="L40" href="source/net/ipv4/ip_options.c#L40">40</a> <b><i> * saddr is address of outgoing interface.</i></b>
 <a name="L41" href="source/net/ipv4/ip_options.c#L41">41</a> <b><i> */</i></b>
 <a name="L42" href="source/net/ipv4/ip_options.c#L42">42</a> 
 <a name="L43" href="source/net/ipv4/ip_options.c#L43">43</a> void <a href="ident?i=ip_options_build">ip_options_build</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, struct <a href="ident?i=ip_options">ip_options</a> *opt,
 <a name="L44" href="source/net/ipv4/ip_options.c#L44">44</a>                       <a href="ident?i=__be32">__be32</a> <a href="ident?i=daddr">daddr</a>, struct <a href="ident?i=rtable">rtable</a> *<a href="ident?i=rt">rt</a>, int is_frag)
 <a name="L45" href="source/net/ipv4/ip_options.c#L45">45</a> {
 <a name="L46" href="source/net/ipv4/ip_options.c#L46">46</a>         unsigned char *iph = <a href="ident?i=skb_network_header">skb_network_header</a>(<a href="ident?i=skb">skb</a>);
 <a name="L47" href="source/net/ipv4/ip_options.c#L47">47</a> 
 <a name="L48" href="source/net/ipv4/ip_options.c#L48">48</a>         <a href="ident?i=memcpy">memcpy</a>(&amp;(<a href="ident?i=IPCB">IPCB</a>(<a href="ident?i=skb">skb</a>)-&gt;opt), opt, sizeof(struct <a href="ident?i=ip_options">ip_options</a>));
 <a name="L49" href="source/net/ipv4/ip_options.c#L49">49</a>         <a href="ident?i=memcpy">memcpy</a>(iph+sizeof(struct <a href="ident?i=iphdr">iphdr</a>), opt-&gt;__data, opt-&gt;<a href="ident?i=optlen">optlen</a>);
 <a name="L50" href="source/net/ipv4/ip_options.c#L50">50</a>         opt = &amp;(<a href="ident?i=IPCB">IPCB</a>(<a href="ident?i=skb">skb</a>)-&gt;opt);
 <a name="L51" href="source/net/ipv4/ip_options.c#L51">51</a> 
 <a name="L52" href="source/net/ipv4/ip_options.c#L52">52</a>         if (opt-&gt;<a href="ident?i=srr">srr</a>)
 <a name="L53" href="source/net/ipv4/ip_options.c#L53">53</a>                 <a href="ident?i=memcpy">memcpy</a>(iph+opt-&gt;<a href="ident?i=srr">srr</a>+iph[opt-&gt;<a href="ident?i=srr">srr</a>+1]-4, &amp;<a href="ident?i=daddr">daddr</a>, 4);
 <a name="L54" href="source/net/ipv4/ip_options.c#L54">54</a> 
 <a name="L55" href="source/net/ipv4/ip_options.c#L55">55</a>         if (!is_frag) {
 <a name="L56" href="source/net/ipv4/ip_options.c#L56">56</a>                 if (opt-&gt;rr_needaddr)
 <a name="L57" href="source/net/ipv4/ip_options.c#L57">57</a>                         <a href="ident?i=ip_rt_get_source">ip_rt_get_source</a>(iph+opt-&gt;rr+iph[opt-&gt;rr+2]-5, <a href="ident?i=skb">skb</a>, <a href="ident?i=rt">rt</a>);
 <a name="L58" href="source/net/ipv4/ip_options.c#L58">58</a>                 if (opt-&gt;ts_needaddr)
 <a name="L59" href="source/net/ipv4/ip_options.c#L59">59</a>                         <a href="ident?i=ip_rt_get_source">ip_rt_get_source</a>(iph+opt-&gt;<a href="ident?i=ts">ts</a>+iph[opt-&gt;<a href="ident?i=ts">ts</a>+2]-9, <a href="ident?i=skb">skb</a>, <a href="ident?i=rt">rt</a>);
 <a name="L60" href="source/net/ipv4/ip_options.c#L60">60</a>                 if (opt-&gt;ts_needtime) {
 <a name="L61" href="source/net/ipv4/ip_options.c#L61">61</a>                         struct <a href="ident?i=timespec">timespec</a> tv;
 <a name="L62" href="source/net/ipv4/ip_options.c#L62">62</a>                         <a href="ident?i=__be32">__be32</a> midtime;
 <a name="L63" href="source/net/ipv4/ip_options.c#L63">63</a>                         <a href="ident?i=getnstimeofday">getnstimeofday</a>(&amp;tv);
 <a name="L64" href="source/net/ipv4/ip_options.c#L64">64</a>                         midtime = <a href="ident?i=htonl">htonl</a>((tv.tv_sec % 86400) * <a href="ident?i=MSEC_PER_SEC">MSEC_PER_SEC</a> + tv.tv_nsec / <a href="ident?i=NSEC_PER_MSEC">NSEC_PER_MSEC</a>);
 <a name="L65" href="source/net/ipv4/ip_options.c#L65">65</a>                         <a href="ident?i=memcpy">memcpy</a>(iph+opt-&gt;<a href="ident?i=ts">ts</a>+iph[opt-&gt;<a href="ident?i=ts">ts</a>+2]-5, &amp;midtime, 4);
 <a name="L66" href="source/net/ipv4/ip_options.c#L66">66</a>                 }
 <a name="L67" href="source/net/ipv4/ip_options.c#L67">67</a>                 return;
 <a name="L68" href="source/net/ipv4/ip_options.c#L68">68</a>         }
 <a name="L69" href="source/net/ipv4/ip_options.c#L69">69</a>         if (opt-&gt;rr) {
 <a name="L70" href="source/net/ipv4/ip_options.c#L70">70</a>                 <a href="ident?i=memset">memset</a>(iph+opt-&gt;rr, <a href="ident?i=IPOPT_NOP">IPOPT_NOP</a>, iph[opt-&gt;rr+1]);
 <a name="L71" href="source/net/ipv4/ip_options.c#L71">71</a>                 opt-&gt;rr = 0;
 <a name="L72" href="source/net/ipv4/ip_options.c#L72">72</a>                 opt-&gt;rr_needaddr = 0;
 <a name="L73" href="source/net/ipv4/ip_options.c#L73">73</a>         }
 <a name="L74" href="source/net/ipv4/ip_options.c#L74">74</a>         if (opt-&gt;<a href="ident?i=ts">ts</a>) {
 <a name="L75" href="source/net/ipv4/ip_options.c#L75">75</a>                 <a href="ident?i=memset">memset</a>(iph+opt-&gt;<a href="ident?i=ts">ts</a>, <a href="ident?i=IPOPT_NOP">IPOPT_NOP</a>, iph[opt-&gt;<a href="ident?i=ts">ts</a>+1]);
 <a name="L76" href="source/net/ipv4/ip_options.c#L76">76</a>                 opt-&gt;<a href="ident?i=ts">ts</a> = 0;
 <a name="L77" href="source/net/ipv4/ip_options.c#L77">77</a>                 opt-&gt;ts_needaddr = opt-&gt;ts_needtime = 0;
 <a name="L78" href="source/net/ipv4/ip_options.c#L78">78</a>         }
 <a name="L79" href="source/net/ipv4/ip_options.c#L79">79</a> }
 <a name="L80" href="source/net/ipv4/ip_options.c#L80">80</a> 
 <a name="L81" href="source/net/ipv4/ip_options.c#L81">81</a> <b><i>/*</i></b>
 <a name="L82" href="source/net/ipv4/ip_options.c#L82">82</a> <b><i> * Provided (sopt, skb) points to received options,</i></b>
 <a name="L83" href="source/net/ipv4/ip_options.c#L83">83</a> <b><i> * build in dopt compiled option set appropriate for answering.</i></b>
 <a name="L84" href="source/net/ipv4/ip_options.c#L84">84</a> <b><i> * i.e. invert SRR option, copy anothers,</i></b>
 <a name="L85" href="source/net/ipv4/ip_options.c#L85">85</a> <b><i> * and grab room in RR/TS options.</i></b>
 <a name="L86" href="source/net/ipv4/ip_options.c#L86">86</a> <b><i> *</i></b>
 <a name="L87" href="source/net/ipv4/ip_options.c#L87">87</a> <b><i> * NOTE: dopt cannot point to skb.</i></b>
 <a name="L88" href="source/net/ipv4/ip_options.c#L88">88</a> <b><i> */</i></b>
 <a name="L89" href="source/net/ipv4/ip_options.c#L89">89</a> 
 <a name="L90" href="source/net/ipv4/ip_options.c#L90">90</a> int <a href="ident?i=__ip_options_echo">__ip_options_echo</a>(struct <a href="ident?i=ip_options">ip_options</a> *dopt, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
 <a name="L91" href="source/net/ipv4/ip_options.c#L91">91</a>                       const struct <a href="ident?i=ip_options">ip_options</a> *sopt)
 <a name="L92" href="source/net/ipv4/ip_options.c#L92">92</a> {
 <a name="L93" href="source/net/ipv4/ip_options.c#L93">93</a>         unsigned char *sptr, *dptr;
 <a name="L94" href="source/net/ipv4/ip_options.c#L94">94</a>         int soffset, doffset;
 <a name="L95" href="source/net/ipv4/ip_options.c#L95">95</a>         int     <a href="ident?i=optlen">optlen</a>;
 <a name="L96" href="source/net/ipv4/ip_options.c#L96">96</a> 
 <a name="L97" href="source/net/ipv4/ip_options.c#L97">97</a>         <a href="ident?i=memset">memset</a>(dopt, 0, sizeof(struct <a href="ident?i=ip_options">ip_options</a>));
 <a name="L98" href="source/net/ipv4/ip_options.c#L98">98</a> 
 <a name="L99" href="source/net/ipv4/ip_options.c#L99">99</a>         if (sopt-&gt;<a href="ident?i=optlen">optlen</a> == 0)
<a name="L100" href="source/net/ipv4/ip_options.c#L100">100</a>                 return 0;
<a name="L101" href="source/net/ipv4/ip_options.c#L101">101</a> 
<a name="L102" href="source/net/ipv4/ip_options.c#L102">102</a>         sptr = <a href="ident?i=skb_network_header">skb_network_header</a>(<a href="ident?i=skb">skb</a>);
<a name="L103" href="source/net/ipv4/ip_options.c#L103">103</a>         dptr = dopt-&gt;__data;
<a name="L104" href="source/net/ipv4/ip_options.c#L104">104</a> 
<a name="L105" href="source/net/ipv4/ip_options.c#L105">105</a>         if (sopt-&gt;rr) {
<a name="L106" href="source/net/ipv4/ip_options.c#L106">106</a>                 <a href="ident?i=optlen">optlen</a>  = sptr[sopt-&gt;rr+1];
<a name="L107" href="source/net/ipv4/ip_options.c#L107">107</a>                 soffset = sptr[sopt-&gt;rr+2];
<a name="L108" href="source/net/ipv4/ip_options.c#L108">108</a>                 dopt-&gt;rr = dopt-&gt;<a href="ident?i=optlen">optlen</a> + sizeof(struct <a href="ident?i=iphdr">iphdr</a>);
<a name="L109" href="source/net/ipv4/ip_options.c#L109">109</a>                 <a href="ident?i=memcpy">memcpy</a>(dptr, sptr+sopt-&gt;rr, <a href="ident?i=optlen">optlen</a>);
<a name="L110" href="source/net/ipv4/ip_options.c#L110">110</a>                 if (sopt-&gt;rr_needaddr &amp;&amp; soffset &lt;= <a href="ident?i=optlen">optlen</a>) {
<a name="L111" href="source/net/ipv4/ip_options.c#L111">111</a>                         if (soffset + 3 &gt; <a href="ident?i=optlen">optlen</a>)
<a name="L112" href="source/net/ipv4/ip_options.c#L112">112</a>                                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L113" href="source/net/ipv4/ip_options.c#L113">113</a>                         dptr[2] = soffset + 4;
<a name="L114" href="source/net/ipv4/ip_options.c#L114">114</a>                         dopt-&gt;rr_needaddr = 1;
<a name="L115" href="source/net/ipv4/ip_options.c#L115">115</a>                 }
<a name="L116" href="source/net/ipv4/ip_options.c#L116">116</a>                 dptr += <a href="ident?i=optlen">optlen</a>;
<a name="L117" href="source/net/ipv4/ip_options.c#L117">117</a>                 dopt-&gt;<a href="ident?i=optlen">optlen</a> += <a href="ident?i=optlen">optlen</a>;
<a name="L118" href="source/net/ipv4/ip_options.c#L118">118</a>         }
<a name="L119" href="source/net/ipv4/ip_options.c#L119">119</a>         if (sopt-&gt;<a href="ident?i=ts">ts</a>) {
<a name="L120" href="source/net/ipv4/ip_options.c#L120">120</a>                 <a href="ident?i=optlen">optlen</a> = sptr[sopt-&gt;<a href="ident?i=ts">ts</a>+1];
<a name="L121" href="source/net/ipv4/ip_options.c#L121">121</a>                 soffset = sptr[sopt-&gt;<a href="ident?i=ts">ts</a>+2];
<a name="L122" href="source/net/ipv4/ip_options.c#L122">122</a>                 dopt-&gt;<a href="ident?i=ts">ts</a> = dopt-&gt;<a href="ident?i=optlen">optlen</a> + sizeof(struct <a href="ident?i=iphdr">iphdr</a>);
<a name="L123" href="source/net/ipv4/ip_options.c#L123">123</a>                 <a href="ident?i=memcpy">memcpy</a>(dptr, sptr+sopt-&gt;<a href="ident?i=ts">ts</a>, <a href="ident?i=optlen">optlen</a>);
<a name="L124" href="source/net/ipv4/ip_options.c#L124">124</a>                 if (soffset &lt;= <a href="ident?i=optlen">optlen</a>) {
<a name="L125" href="source/net/ipv4/ip_options.c#L125">125</a>                         if (sopt-&gt;ts_needaddr) {
<a name="L126" href="source/net/ipv4/ip_options.c#L126">126</a>                                 if (soffset + 3 &gt; <a href="ident?i=optlen">optlen</a>)
<a name="L127" href="source/net/ipv4/ip_options.c#L127">127</a>                                         return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L128" href="source/net/ipv4/ip_options.c#L128">128</a>                                 dopt-&gt;ts_needaddr = 1;
<a name="L129" href="source/net/ipv4/ip_options.c#L129">129</a>                                 soffset += 4;
<a name="L130" href="source/net/ipv4/ip_options.c#L130">130</a>                         }
<a name="L131" href="source/net/ipv4/ip_options.c#L131">131</a>                         if (sopt-&gt;ts_needtime) {
<a name="L132" href="source/net/ipv4/ip_options.c#L132">132</a>                                 if (soffset + 3 &gt; <a href="ident?i=optlen">optlen</a>)
<a name="L133" href="source/net/ipv4/ip_options.c#L133">133</a>                                         return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L134" href="source/net/ipv4/ip_options.c#L134">134</a>                                 if ((dptr[3]&amp;0xF) != <a href="ident?i=IPOPT_TS_PRESPEC">IPOPT_TS_PRESPEC</a>) {
<a name="L135" href="source/net/ipv4/ip_options.c#L135">135</a>                                         dopt-&gt;ts_needtime = 1;
<a name="L136" href="source/net/ipv4/ip_options.c#L136">136</a>                                         soffset += 4;
<a name="L137" href="source/net/ipv4/ip_options.c#L137">137</a>                                 } else {
<a name="L138" href="source/net/ipv4/ip_options.c#L138">138</a>                                         dopt-&gt;ts_needtime = 0;
<a name="L139" href="source/net/ipv4/ip_options.c#L139">139</a> 
<a name="L140" href="source/net/ipv4/ip_options.c#L140">140</a>                                         if (soffset + 7 &lt;= <a href="ident?i=optlen">optlen</a>) {
<a name="L141" href="source/net/ipv4/ip_options.c#L141">141</a>                                                 <a href="ident?i=__be32">__be32</a> <a href="ident?i=addr">addr</a>;
<a name="L142" href="source/net/ipv4/ip_options.c#L142">142</a> 
<a name="L143" href="source/net/ipv4/ip_options.c#L143">143</a>                                                 <a href="ident?i=memcpy">memcpy</a>(&amp;<a href="ident?i=addr">addr</a>, dptr+soffset-1, 4);
<a name="L144" href="source/net/ipv4/ip_options.c#L144">144</a>                                                 if (<a href="ident?i=inet_addr_type">inet_addr_type</a>(<a href="ident?i=dev_net">dev_net</a>(<a href="ident?i=skb_dst">skb_dst</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=dev">dev</a>), <a href="ident?i=addr">addr</a>) != RTN_UNICAST) {
<a name="L145" href="source/net/ipv4/ip_options.c#L145">145</a>                                                         dopt-&gt;ts_needtime = 1;
<a name="L146" href="source/net/ipv4/ip_options.c#L146">146</a>                                                         soffset += 8;
<a name="L147" href="source/net/ipv4/ip_options.c#L147">147</a>                                                 }
<a name="L148" href="source/net/ipv4/ip_options.c#L148">148</a>                                         }
<a name="L149" href="source/net/ipv4/ip_options.c#L149">149</a>                                 }
<a name="L150" href="source/net/ipv4/ip_options.c#L150">150</a>                         }
<a name="L151" href="source/net/ipv4/ip_options.c#L151">151</a>                         dptr[2] = soffset;
<a name="L152" href="source/net/ipv4/ip_options.c#L152">152</a>                 }
<a name="L153" href="source/net/ipv4/ip_options.c#L153">153</a>                 dptr += <a href="ident?i=optlen">optlen</a>;
<a name="L154" href="source/net/ipv4/ip_options.c#L154">154</a>                 dopt-&gt;<a href="ident?i=optlen">optlen</a> += <a href="ident?i=optlen">optlen</a>;
<a name="L155" href="source/net/ipv4/ip_options.c#L155">155</a>         }
<a name="L156" href="source/net/ipv4/ip_options.c#L156">156</a>         if (sopt-&gt;<a href="ident?i=srr">srr</a>) {
<a name="L157" href="source/net/ipv4/ip_options.c#L157">157</a>                 unsigned char *<a href="ident?i=start">start</a> = sptr+sopt-&gt;<a href="ident?i=srr">srr</a>;
<a name="L158" href="source/net/ipv4/ip_options.c#L158">158</a>                 <a href="ident?i=__be32">__be32</a> faddr;
<a name="L159" href="source/net/ipv4/ip_options.c#L159">159</a> 
<a name="L160" href="source/net/ipv4/ip_options.c#L160">160</a>                 <a href="ident?i=optlen">optlen</a>  = <a href="ident?i=start">start</a>[1];
<a name="L161" href="source/net/ipv4/ip_options.c#L161">161</a>                 soffset = <a href="ident?i=start">start</a>[2];
<a name="L162" href="source/net/ipv4/ip_options.c#L162">162</a>                 doffset = 0;
<a name="L163" href="source/net/ipv4/ip_options.c#L163">163</a>                 if (soffset &gt; <a href="ident?i=optlen">optlen</a>)
<a name="L164" href="source/net/ipv4/ip_options.c#L164">164</a>                         soffset = <a href="ident?i=optlen">optlen</a> + 1;
<a name="L165" href="source/net/ipv4/ip_options.c#L165">165</a>                 soffset -= 4;
<a name="L166" href="source/net/ipv4/ip_options.c#L166">166</a>                 if (soffset &gt; 3) {
<a name="L167" href="source/net/ipv4/ip_options.c#L167">167</a>                         <a href="ident?i=memcpy">memcpy</a>(&amp;faddr, &amp;<a href="ident?i=start">start</a>[soffset-1], 4);
<a name="L168" href="source/net/ipv4/ip_options.c#L168">168</a>                         for (soffset -= 4, doffset = 4; soffset &gt; 3; soffset -= 4, doffset += 4)
<a name="L169" href="source/net/ipv4/ip_options.c#L169">169</a>                                 <a href="ident?i=memcpy">memcpy</a>(&amp;dptr[doffset-1], &amp;<a href="ident?i=start">start</a>[soffset-1], 4);
<a name="L170" href="source/net/ipv4/ip_options.c#L170">170</a>                         <b><i>/*</i></b>
<a name="L171" href="source/net/ipv4/ip_options.c#L171">171</a> <b><i>                         * RFC1812 requires to fix illegal source routes.</i></b>
<a name="L172" href="source/net/ipv4/ip_options.c#L172">172</a> <b><i>                         */</i></b>
<a name="L173" href="source/net/ipv4/ip_options.c#L173">173</a>                         if (<a href="ident?i=memcmp">memcmp</a>(&amp;<a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=saddr">saddr</a>,
<a name="L174" href="source/net/ipv4/ip_options.c#L174">174</a>                                    &amp;<a href="ident?i=start">start</a>[soffset + 3], 4) == 0)
<a name="L175" href="source/net/ipv4/ip_options.c#L175">175</a>                                 doffset -= 4;
<a name="L176" href="source/net/ipv4/ip_options.c#L176">176</a>                 }
<a name="L177" href="source/net/ipv4/ip_options.c#L177">177</a>                 if (doffset &gt; 3) {
<a name="L178" href="source/net/ipv4/ip_options.c#L178">178</a>                         <a href="ident?i=__be32">__be32</a> <a href="ident?i=daddr">daddr</a> = <a href="ident?i=fib_compute_spec_dst">fib_compute_spec_dst</a>(<a href="ident?i=skb">skb</a>);
<a name="L179" href="source/net/ipv4/ip_options.c#L179">179</a> 
<a name="L180" href="source/net/ipv4/ip_options.c#L180">180</a>                         <a href="ident?i=memcpy">memcpy</a>(&amp;<a href="ident?i=start">start</a>[doffset-1], &amp;<a href="ident?i=daddr">daddr</a>, 4);
<a name="L181" href="source/net/ipv4/ip_options.c#L181">181</a>                         dopt-&gt;faddr = faddr;
<a name="L182" href="source/net/ipv4/ip_options.c#L182">182</a>                         dptr[0] = <a href="ident?i=start">start</a>[0];
<a name="L183" href="source/net/ipv4/ip_options.c#L183">183</a>                         dptr[1] = doffset+3;
<a name="L184" href="source/net/ipv4/ip_options.c#L184">184</a>                         dptr[2] = 4;
<a name="L185" href="source/net/ipv4/ip_options.c#L185">185</a>                         dptr += doffset+3;
<a name="L186" href="source/net/ipv4/ip_options.c#L186">186</a>                         dopt-&gt;<a href="ident?i=srr">srr</a> = dopt-&gt;<a href="ident?i=optlen">optlen</a> + sizeof(struct <a href="ident?i=iphdr">iphdr</a>);
<a name="L187" href="source/net/ipv4/ip_options.c#L187">187</a>                         dopt-&gt;<a href="ident?i=optlen">optlen</a> += doffset+3;
<a name="L188" href="source/net/ipv4/ip_options.c#L188">188</a>                         dopt-&gt;is_strictroute = sopt-&gt;is_strictroute;
<a name="L189" href="source/net/ipv4/ip_options.c#L189">189</a>                 }
<a name="L190" href="source/net/ipv4/ip_options.c#L190">190</a>         }
<a name="L191" href="source/net/ipv4/ip_options.c#L191">191</a>         if (sopt-&gt;cipso) {
<a name="L192" href="source/net/ipv4/ip_options.c#L192">192</a>                 <a href="ident?i=optlen">optlen</a>  = sptr[sopt-&gt;cipso+1];
<a name="L193" href="source/net/ipv4/ip_options.c#L193">193</a>                 dopt-&gt;cipso = dopt-&gt;<a href="ident?i=optlen">optlen</a>+sizeof(struct <a href="ident?i=iphdr">iphdr</a>);
<a name="L194" href="source/net/ipv4/ip_options.c#L194">194</a>                 <a href="ident?i=memcpy">memcpy</a>(dptr, sptr+sopt-&gt;cipso, <a href="ident?i=optlen">optlen</a>);
<a name="L195" href="source/net/ipv4/ip_options.c#L195">195</a>                 dptr += <a href="ident?i=optlen">optlen</a>;
<a name="L196" href="source/net/ipv4/ip_options.c#L196">196</a>                 dopt-&gt;<a href="ident?i=optlen">optlen</a> += <a href="ident?i=optlen">optlen</a>;
<a name="L197" href="source/net/ipv4/ip_options.c#L197">197</a>         }
<a name="L198" href="source/net/ipv4/ip_options.c#L198">198</a>         while (dopt-&gt;<a href="ident?i=optlen">optlen</a> &amp; 3) {
<a name="L199" href="source/net/ipv4/ip_options.c#L199">199</a>                 *dptr++ = <a href="ident?i=IPOPT_END">IPOPT_END</a>;
<a name="L200" href="source/net/ipv4/ip_options.c#L200">200</a>                 dopt-&gt;<a href="ident?i=optlen">optlen</a>++;
<a name="L201" href="source/net/ipv4/ip_options.c#L201">201</a>         }
<a name="L202" href="source/net/ipv4/ip_options.c#L202">202</a>         return 0;
<a name="L203" href="source/net/ipv4/ip_options.c#L203">203</a> }
<a name="L204" href="source/net/ipv4/ip_options.c#L204">204</a> 
<a name="L205" href="source/net/ipv4/ip_options.c#L205">205</a> <b><i>/*</i></b>
<a name="L206" href="source/net/ipv4/ip_options.c#L206">206</a> <b><i> *      Options "fragmenting", just fill options not</i></b>
<a name="L207" href="source/net/ipv4/ip_options.c#L207">207</a> <b><i> *      allowed in fragments with NOOPs.</i></b>
<a name="L208" href="source/net/ipv4/ip_options.c#L208">208</a> <b><i> *      Simple and stupid 8), but the most efficient way.</i></b>
<a name="L209" href="source/net/ipv4/ip_options.c#L209">209</a> <b><i> */</i></b>
<a name="L210" href="source/net/ipv4/ip_options.c#L210">210</a> 
<a name="L211" href="source/net/ipv4/ip_options.c#L211">211</a> void <a href="ident?i=ip_options_fragment">ip_options_fragment</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L212" href="source/net/ipv4/ip_options.c#L212">212</a> {
<a name="L213" href="source/net/ipv4/ip_options.c#L213">213</a>         unsigned char *optptr = <a href="ident?i=skb_network_header">skb_network_header</a>(<a href="ident?i=skb">skb</a>) + sizeof(struct <a href="ident?i=iphdr">iphdr</a>);
<a name="L214" href="source/net/ipv4/ip_options.c#L214">214</a>         struct <a href="ident?i=ip_options">ip_options</a> *opt = &amp;(<a href="ident?i=IPCB">IPCB</a>(<a href="ident?i=skb">skb</a>)-&gt;opt);
<a name="L215" href="source/net/ipv4/ip_options.c#L215">215</a>         int  <a href="ident?i=l">l</a> = opt-&gt;<a href="ident?i=optlen">optlen</a>;
<a name="L216" href="source/net/ipv4/ip_options.c#L216">216</a>         int  <a href="ident?i=optlen">optlen</a>;
<a name="L217" href="source/net/ipv4/ip_options.c#L217">217</a> 
<a name="L218" href="source/net/ipv4/ip_options.c#L218">218</a>         while (<a href="ident?i=l">l</a> &gt; 0) {
<a name="L219" href="source/net/ipv4/ip_options.c#L219">219</a>                 switch (*optptr) {
<a name="L220" href="source/net/ipv4/ip_options.c#L220">220</a>                 case <a href="ident?i=IPOPT_END">IPOPT_END</a>:
<a name="L221" href="source/net/ipv4/ip_options.c#L221">221</a>                         return;
<a name="L222" href="source/net/ipv4/ip_options.c#L222">222</a>                 case <a href="ident?i=IPOPT_NOOP">IPOPT_NOOP</a>:
<a name="L223" href="source/net/ipv4/ip_options.c#L223">223</a>                         <a href="ident?i=l">l</a>--;
<a name="L224" href="source/net/ipv4/ip_options.c#L224">224</a>                         optptr++;
<a name="L225" href="source/net/ipv4/ip_options.c#L225">225</a>                         continue;
<a name="L226" href="source/net/ipv4/ip_options.c#L226">226</a>                 }
<a name="L227" href="source/net/ipv4/ip_options.c#L227">227</a>                 <a href="ident?i=optlen">optlen</a> = optptr[1];
<a name="L228" href="source/net/ipv4/ip_options.c#L228">228</a>                 if (<a href="ident?i=optlen">optlen</a> &lt; 2 || <a href="ident?i=optlen">optlen</a> &gt; <a href="ident?i=l">l</a>)
<a name="L229" href="source/net/ipv4/ip_options.c#L229">229</a>                   return;
<a name="L230" href="source/net/ipv4/ip_options.c#L230">230</a>                 if (!<a href="ident?i=IPOPT_COPIED">IPOPT_COPIED</a>(*optptr))
<a name="L231" href="source/net/ipv4/ip_options.c#L231">231</a>                         <a href="ident?i=memset">memset</a>(optptr, <a href="ident?i=IPOPT_NOOP">IPOPT_NOOP</a>, <a href="ident?i=optlen">optlen</a>);
<a name="L232" href="source/net/ipv4/ip_options.c#L232">232</a>                 <a href="ident?i=l">l</a> -= <a href="ident?i=optlen">optlen</a>;
<a name="L233" href="source/net/ipv4/ip_options.c#L233">233</a>                 optptr += <a href="ident?i=optlen">optlen</a>;
<a name="L234" href="source/net/ipv4/ip_options.c#L234">234</a>         }
<a name="L235" href="source/net/ipv4/ip_options.c#L235">235</a>         opt-&gt;<a href="ident?i=ts">ts</a> = 0;
<a name="L236" href="source/net/ipv4/ip_options.c#L236">236</a>         opt-&gt;rr = 0;
<a name="L237" href="source/net/ipv4/ip_options.c#L237">237</a>         opt-&gt;rr_needaddr = 0;
<a name="L238" href="source/net/ipv4/ip_options.c#L238">238</a>         opt-&gt;ts_needaddr = 0;
<a name="L239" href="source/net/ipv4/ip_options.c#L239">239</a>         opt-&gt;ts_needtime = 0;
<a name="L240" href="source/net/ipv4/ip_options.c#L240">240</a> }
<a name="L241" href="source/net/ipv4/ip_options.c#L241">241</a> 
<a name="L242" href="source/net/ipv4/ip_options.c#L242">242</a> <b><i>/* helper used by ip_options_compile() to call fib_compute_spec_dst()</i></b>
<a name="L243" href="source/net/ipv4/ip_options.c#L243">243</a> <b><i> * at most one time.</i></b>
<a name="L244" href="source/net/ipv4/ip_options.c#L244">244</a> <b><i> */</i></b>
<a name="L245" href="source/net/ipv4/ip_options.c#L245">245</a> static void <a href="ident?i=spec_dst_fill">spec_dst_fill</a>(<a href="ident?i=__be32">__be32</a> *spec_dst, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L246" href="source/net/ipv4/ip_options.c#L246">246</a> {
<a name="L247" href="source/net/ipv4/ip_options.c#L247">247</a>         if (*spec_dst == <a href="ident?i=htonl">htonl</a>(<a href="ident?i=INADDR_ANY">INADDR_ANY</a>))
<a name="L248" href="source/net/ipv4/ip_options.c#L248">248</a>                 *spec_dst = <a href="ident?i=fib_compute_spec_dst">fib_compute_spec_dst</a>(<a href="ident?i=skb">skb</a>);
<a name="L249" href="source/net/ipv4/ip_options.c#L249">249</a> }
<a name="L250" href="source/net/ipv4/ip_options.c#L250">250</a> 
<a name="L251" href="source/net/ipv4/ip_options.c#L251">251</a> <b><i>/*</i></b>
<a name="L252" href="source/net/ipv4/ip_options.c#L252">252</a> <b><i> * Verify options and fill pointers in struct options.</i></b>
<a name="L253" href="source/net/ipv4/ip_options.c#L253">253</a> <b><i> * Caller should clear *opt, and set opt-&gt;data.</i></b>
<a name="L254" href="source/net/ipv4/ip_options.c#L254">254</a> <b><i> * If opt == NULL, then skb-&gt;data should point to IP header.</i></b>
<a name="L255" href="source/net/ipv4/ip_options.c#L255">255</a> <b><i> */</i></b>
<a name="L256" href="source/net/ipv4/ip_options.c#L256">256</a> 
<a name="L257" href="source/net/ipv4/ip_options.c#L257">257</a> int <a href="ident?i=ip_options_compile">ip_options_compile</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>,
<a name="L258" href="source/net/ipv4/ip_options.c#L258">258</a>                        struct <a href="ident?i=ip_options">ip_options</a> *opt, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L259" href="source/net/ipv4/ip_options.c#L259">259</a> {
<a name="L260" href="source/net/ipv4/ip_options.c#L260">260</a>         <a href="ident?i=__be32">__be32</a> spec_dst = <a href="ident?i=htonl">htonl</a>(<a href="ident?i=INADDR_ANY">INADDR_ANY</a>);
<a name="L261" href="source/net/ipv4/ip_options.c#L261">261</a>         unsigned char *pp_ptr = <a href="ident?i=NULL">NULL</a>;
<a name="L262" href="source/net/ipv4/ip_options.c#L262">262</a>         struct <a href="ident?i=rtable">rtable</a> *<a href="ident?i=rt">rt</a> = <a href="ident?i=NULL">NULL</a>;
<a name="L263" href="source/net/ipv4/ip_options.c#L263">263</a>         unsigned char *optptr;
<a name="L264" href="source/net/ipv4/ip_options.c#L264">264</a>         unsigned char *iph;
<a name="L265" href="source/net/ipv4/ip_options.c#L265">265</a>         int <a href="ident?i=optlen">optlen</a>, <a href="ident?i=l">l</a>;
<a name="L266" href="source/net/ipv4/ip_options.c#L266">266</a> 
<a name="L267" href="source/net/ipv4/ip_options.c#L267">267</a>         if (<a href="ident?i=skb">skb</a>) {
<a name="L268" href="source/net/ipv4/ip_options.c#L268">268</a>                 <a href="ident?i=rt">rt</a> = <a href="ident?i=skb_rtable">skb_rtable</a>(<a href="ident?i=skb">skb</a>);
<a name="L269" href="source/net/ipv4/ip_options.c#L269">269</a>                 optptr = (unsigned char *)&amp;(<a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>)[1]);
<a name="L270" href="source/net/ipv4/ip_options.c#L270">270</a>         } else
<a name="L271" href="source/net/ipv4/ip_options.c#L271">271</a>                 optptr = opt-&gt;__data;
<a name="L272" href="source/net/ipv4/ip_options.c#L272">272</a>         iph = optptr - sizeof(struct <a href="ident?i=iphdr">iphdr</a>);
<a name="L273" href="source/net/ipv4/ip_options.c#L273">273</a> 
<a name="L274" href="source/net/ipv4/ip_options.c#L274">274</a>         for (<a href="ident?i=l">l</a> = opt-&gt;<a href="ident?i=optlen">optlen</a>; <a href="ident?i=l">l</a> &gt; 0; ) {
<a name="L275" href="source/net/ipv4/ip_options.c#L275">275</a>                 switch (*optptr) {
<a name="L276" href="source/net/ipv4/ip_options.c#L276">276</a>                 case <a href="ident?i=IPOPT_END">IPOPT_END</a>:
<a name="L277" href="source/net/ipv4/ip_options.c#L277">277</a>                         for (optptr++, <a href="ident?i=l">l</a>--; <a href="ident?i=l">l</a> &gt; 0; optptr++, <a href="ident?i=l">l</a>--) {
<a name="L278" href="source/net/ipv4/ip_options.c#L278">278</a>                                 if (*optptr != <a href="ident?i=IPOPT_END">IPOPT_END</a>) {
<a name="L279" href="source/net/ipv4/ip_options.c#L279">279</a>                                         *optptr = <a href="ident?i=IPOPT_END">IPOPT_END</a>;
<a name="L280" href="source/net/ipv4/ip_options.c#L280">280</a>                                         opt-&gt;is_changed = 1;
<a name="L281" href="source/net/ipv4/ip_options.c#L281">281</a>                                 }
<a name="L282" href="source/net/ipv4/ip_options.c#L282">282</a>                         }
<a name="L283" href="source/net/ipv4/ip_options.c#L283">283</a>                         goto eol;
<a name="L284" href="source/net/ipv4/ip_options.c#L284">284</a>                 case <a href="ident?i=IPOPT_NOOP">IPOPT_NOOP</a>:
<a name="L285" href="source/net/ipv4/ip_options.c#L285">285</a>                         <a href="ident?i=l">l</a>--;
<a name="L286" href="source/net/ipv4/ip_options.c#L286">286</a>                         optptr++;
<a name="L287" href="source/net/ipv4/ip_options.c#L287">287</a>                         continue;
<a name="L288" href="source/net/ipv4/ip_options.c#L288">288</a>                 }
<a name="L289" href="source/net/ipv4/ip_options.c#L289">289</a>                 if (<a href="ident?i=unlikely">unlikely</a>(<a href="ident?i=l">l</a> &lt; 2)) {
<a name="L290" href="source/net/ipv4/ip_options.c#L290">290</a>                         pp_ptr = optptr;
<a name="L291" href="source/net/ipv4/ip_options.c#L291">291</a>                         goto <a href="ident?i=error">error</a>;
<a name="L292" href="source/net/ipv4/ip_options.c#L292">292</a>                 }
<a name="L293" href="source/net/ipv4/ip_options.c#L293">293</a>                 <a href="ident?i=optlen">optlen</a> = optptr[1];
<a name="L294" href="source/net/ipv4/ip_options.c#L294">294</a>                 if (<a href="ident?i=optlen">optlen</a> &lt; 2 || <a href="ident?i=optlen">optlen</a> &gt; <a href="ident?i=l">l</a>) {
<a name="L295" href="source/net/ipv4/ip_options.c#L295">295</a>                         pp_ptr = optptr;
<a name="L296" href="source/net/ipv4/ip_options.c#L296">296</a>                         goto <a href="ident?i=error">error</a>;
<a name="L297" href="source/net/ipv4/ip_options.c#L297">297</a>                 }
<a name="L298" href="source/net/ipv4/ip_options.c#L298">298</a>                 switch (*optptr) {
<a name="L299" href="source/net/ipv4/ip_options.c#L299">299</a>                 case <a href="ident?i=IPOPT_SSRR">IPOPT_SSRR</a>:
<a name="L300" href="source/net/ipv4/ip_options.c#L300">300</a>                 case <a href="ident?i=IPOPT_LSRR">IPOPT_LSRR</a>:
<a name="L301" href="source/net/ipv4/ip_options.c#L301">301</a>                         if (<a href="ident?i=optlen">optlen</a> &lt; 3) {
<a name="L302" href="source/net/ipv4/ip_options.c#L302">302</a>                                 pp_ptr = optptr + 1;
<a name="L303" href="source/net/ipv4/ip_options.c#L303">303</a>                                 goto <a href="ident?i=error">error</a>;
<a name="L304" href="source/net/ipv4/ip_options.c#L304">304</a>                         }
<a name="L305" href="source/net/ipv4/ip_options.c#L305">305</a>                         if (optptr[2] &lt; 4) {
<a name="L306" href="source/net/ipv4/ip_options.c#L306">306</a>                                 pp_ptr = optptr + 2;
<a name="L307" href="source/net/ipv4/ip_options.c#L307">307</a>                                 goto <a href="ident?i=error">error</a>;
<a name="L308" href="source/net/ipv4/ip_options.c#L308">308</a>                         }
<a name="L309" href="source/net/ipv4/ip_options.c#L309">309</a>                         <b><i>/* NB: cf RFC-1812 5.2.4.1 */</i></b>
<a name="L310" href="source/net/ipv4/ip_options.c#L310">310</a>                         if (opt-&gt;<a href="ident?i=srr">srr</a>) {
<a name="L311" href="source/net/ipv4/ip_options.c#L311">311</a>                                 pp_ptr = optptr;
<a name="L312" href="source/net/ipv4/ip_options.c#L312">312</a>                                 goto <a href="ident?i=error">error</a>;
<a name="L313" href="source/net/ipv4/ip_options.c#L313">313</a>                         }
<a name="L314" href="source/net/ipv4/ip_options.c#L314">314</a>                         if (!<a href="ident?i=skb">skb</a>) {
<a name="L315" href="source/net/ipv4/ip_options.c#L315">315</a>                                 if (optptr[2] != 4 || <a href="ident?i=optlen">optlen</a> &lt; 7 || ((<a href="ident?i=optlen">optlen</a>-3) &amp; 3)) {
<a name="L316" href="source/net/ipv4/ip_options.c#L316">316</a>                                         pp_ptr = optptr + 1;
<a name="L317" href="source/net/ipv4/ip_options.c#L317">317</a>                                         goto <a href="ident?i=error">error</a>;
<a name="L318" href="source/net/ipv4/ip_options.c#L318">318</a>                                 }
<a name="L319" href="source/net/ipv4/ip_options.c#L319">319</a>                                 <a href="ident?i=memcpy">memcpy</a>(&amp;opt-&gt;faddr, &amp;optptr[3], 4);
<a name="L320" href="source/net/ipv4/ip_options.c#L320">320</a>                                 if (<a href="ident?i=optlen">optlen</a> &gt; 7)
<a name="L321" href="source/net/ipv4/ip_options.c#L321">321</a>                                         <a href="ident?i=memmove">memmove</a>(&amp;optptr[3], &amp;optptr[7], <a href="ident?i=optlen">optlen</a>-7);
<a name="L322" href="source/net/ipv4/ip_options.c#L322">322</a>                         }
<a name="L323" href="source/net/ipv4/ip_options.c#L323">323</a>                         opt-&gt;is_strictroute = (optptr[0] == <a href="ident?i=IPOPT_SSRR">IPOPT_SSRR</a>);
<a name="L324" href="source/net/ipv4/ip_options.c#L324">324</a>                         opt-&gt;<a href="ident?i=srr">srr</a> = optptr - iph;
<a name="L325" href="source/net/ipv4/ip_options.c#L325">325</a>                         break;
<a name="L326" href="source/net/ipv4/ip_options.c#L326">326</a>                 case <a href="ident?i=IPOPT_RR">IPOPT_RR</a>:
<a name="L327" href="source/net/ipv4/ip_options.c#L327">327</a>                         if (opt-&gt;rr) {
<a name="L328" href="source/net/ipv4/ip_options.c#L328">328</a>                                 pp_ptr = optptr;
<a name="L329" href="source/net/ipv4/ip_options.c#L329">329</a>                                 goto <a href="ident?i=error">error</a>;
<a name="L330" href="source/net/ipv4/ip_options.c#L330">330</a>                         }
<a name="L331" href="source/net/ipv4/ip_options.c#L331">331</a>                         if (<a href="ident?i=optlen">optlen</a> &lt; 3) {
<a name="L332" href="source/net/ipv4/ip_options.c#L332">332</a>                                 pp_ptr = optptr + 1;
<a name="L333" href="source/net/ipv4/ip_options.c#L333">333</a>                                 goto <a href="ident?i=error">error</a>;
<a name="L334" href="source/net/ipv4/ip_options.c#L334">334</a>                         }
<a name="L335" href="source/net/ipv4/ip_options.c#L335">335</a>                         if (optptr[2] &lt; 4) {
<a name="L336" href="source/net/ipv4/ip_options.c#L336">336</a>                                 pp_ptr = optptr + 2;
<a name="L337" href="source/net/ipv4/ip_options.c#L337">337</a>                                 goto <a href="ident?i=error">error</a>;
<a name="L338" href="source/net/ipv4/ip_options.c#L338">338</a>                         }
<a name="L339" href="source/net/ipv4/ip_options.c#L339">339</a>                         if (optptr[2] &lt;= <a href="ident?i=optlen">optlen</a>) {
<a name="L340" href="source/net/ipv4/ip_options.c#L340">340</a>                                 if (optptr[2]+3 &gt; <a href="ident?i=optlen">optlen</a>) {
<a name="L341" href="source/net/ipv4/ip_options.c#L341">341</a>                                         pp_ptr = optptr + 2;
<a name="L342" href="source/net/ipv4/ip_options.c#L342">342</a>                                         goto <a href="ident?i=error">error</a>;
<a name="L343" href="source/net/ipv4/ip_options.c#L343">343</a>                                 }
<a name="L344" href="source/net/ipv4/ip_options.c#L344">344</a>                                 if (<a href="ident?i=rt">rt</a>) {
<a name="L345" href="source/net/ipv4/ip_options.c#L345">345</a>                                         <a href="ident?i=spec_dst_fill">spec_dst_fill</a>(&amp;spec_dst, <a href="ident?i=skb">skb</a>);
<a name="L346" href="source/net/ipv4/ip_options.c#L346">346</a>                                         <a href="ident?i=memcpy">memcpy</a>(&amp;optptr[optptr[2]-1], &amp;spec_dst, 4);
<a name="L347" href="source/net/ipv4/ip_options.c#L347">347</a>                                         opt-&gt;is_changed = 1;
<a name="L348" href="source/net/ipv4/ip_options.c#L348">348</a>                                 }
<a name="L349" href="source/net/ipv4/ip_options.c#L349">349</a>                                 optptr[2] += 4;
<a name="L350" href="source/net/ipv4/ip_options.c#L350">350</a>                                 opt-&gt;rr_needaddr = 1;
<a name="L351" href="source/net/ipv4/ip_options.c#L351">351</a>                         }
<a name="L352" href="source/net/ipv4/ip_options.c#L352">352</a>                         opt-&gt;rr = optptr - iph;
<a name="L353" href="source/net/ipv4/ip_options.c#L353">353</a>                         break;
<a name="L354" href="source/net/ipv4/ip_options.c#L354">354</a>                 case <a href="ident?i=IPOPT_TIMESTAMP">IPOPT_TIMESTAMP</a>:
<a name="L355" href="source/net/ipv4/ip_options.c#L355">355</a>                         if (opt-&gt;<a href="ident?i=ts">ts</a>) {
<a name="L356" href="source/net/ipv4/ip_options.c#L356">356</a>                                 pp_ptr = optptr;
<a name="L357" href="source/net/ipv4/ip_options.c#L357">357</a>                                 goto <a href="ident?i=error">error</a>;
<a name="L358" href="source/net/ipv4/ip_options.c#L358">358</a>                         }
<a name="L359" href="source/net/ipv4/ip_options.c#L359">359</a>                         if (<a href="ident?i=optlen">optlen</a> &lt; 4) {
<a name="L360" href="source/net/ipv4/ip_options.c#L360">360</a>                                 pp_ptr = optptr + 1;
<a name="L361" href="source/net/ipv4/ip_options.c#L361">361</a>                                 goto <a href="ident?i=error">error</a>;
<a name="L362" href="source/net/ipv4/ip_options.c#L362">362</a>                         }
<a name="L363" href="source/net/ipv4/ip_options.c#L363">363</a>                         if (optptr[2] &lt; 5) {
<a name="L364" href="source/net/ipv4/ip_options.c#L364">364</a>                                 pp_ptr = optptr + 2;
<a name="L365" href="source/net/ipv4/ip_options.c#L365">365</a>                                 goto <a href="ident?i=error">error</a>;
<a name="L366" href="source/net/ipv4/ip_options.c#L366">366</a>                         }
<a name="L367" href="source/net/ipv4/ip_options.c#L367">367</a>                         if (optptr[2] &lt;= <a href="ident?i=optlen">optlen</a>) {
<a name="L368" href="source/net/ipv4/ip_options.c#L368">368</a>                                 unsigned char *timeptr = <a href="ident?i=NULL">NULL</a>;
<a name="L369" href="source/net/ipv4/ip_options.c#L369">369</a>                                 if (optptr[2]+3 &gt; <a href="ident?i=optlen">optlen</a>) {
<a name="L370" href="source/net/ipv4/ip_options.c#L370">370</a>                                         pp_ptr = optptr + 2;
<a name="L371" href="source/net/ipv4/ip_options.c#L371">371</a>                                         goto <a href="ident?i=error">error</a>;
<a name="L372" href="source/net/ipv4/ip_options.c#L372">372</a>                                 }
<a name="L373" href="source/net/ipv4/ip_options.c#L373">373</a>                                 switch (optptr[3]&amp;0xF) {
<a name="L374" href="source/net/ipv4/ip_options.c#L374">374</a>                                 case <a href="ident?i=IPOPT_TS_TSONLY">IPOPT_TS_TSONLY</a>:
<a name="L375" href="source/net/ipv4/ip_options.c#L375">375</a>                                         if (<a href="ident?i=skb">skb</a>)
<a name="L376" href="source/net/ipv4/ip_options.c#L376">376</a>                                                 timeptr = &amp;optptr[optptr[2]-1];
<a name="L377" href="source/net/ipv4/ip_options.c#L377">377</a>                                         opt-&gt;ts_needtime = 1;
<a name="L378" href="source/net/ipv4/ip_options.c#L378">378</a>                                         optptr[2] += 4;
<a name="L379" href="source/net/ipv4/ip_options.c#L379">379</a>                                         break;
<a name="L380" href="source/net/ipv4/ip_options.c#L380">380</a>                                 case <a href="ident?i=IPOPT_TS_TSANDADDR">IPOPT_TS_TSANDADDR</a>:
<a name="L381" href="source/net/ipv4/ip_options.c#L381">381</a>                                         if (optptr[2]+7 &gt; <a href="ident?i=optlen">optlen</a>) {
<a name="L382" href="source/net/ipv4/ip_options.c#L382">382</a>                                                 pp_ptr = optptr + 2;
<a name="L383" href="source/net/ipv4/ip_options.c#L383">383</a>                                                 goto <a href="ident?i=error">error</a>;
<a name="L384" href="source/net/ipv4/ip_options.c#L384">384</a>                                         }
<a name="L385" href="source/net/ipv4/ip_options.c#L385">385</a>                                         if (<a href="ident?i=rt">rt</a>)  {
<a name="L386" href="source/net/ipv4/ip_options.c#L386">386</a>                                                 <a href="ident?i=spec_dst_fill">spec_dst_fill</a>(&amp;spec_dst, <a href="ident?i=skb">skb</a>);
<a name="L387" href="source/net/ipv4/ip_options.c#L387">387</a>                                                 <a href="ident?i=memcpy">memcpy</a>(&amp;optptr[optptr[2]-1], &amp;spec_dst, 4);
<a name="L388" href="source/net/ipv4/ip_options.c#L388">388</a>                                                 timeptr = &amp;optptr[optptr[2]+3];
<a name="L389" href="source/net/ipv4/ip_options.c#L389">389</a>                                         }
<a name="L390" href="source/net/ipv4/ip_options.c#L390">390</a>                                         opt-&gt;ts_needaddr = 1;
<a name="L391" href="source/net/ipv4/ip_options.c#L391">391</a>                                         opt-&gt;ts_needtime = 1;
<a name="L392" href="source/net/ipv4/ip_options.c#L392">392</a>                                         optptr[2] += 8;
<a name="L393" href="source/net/ipv4/ip_options.c#L393">393</a>                                         break;
<a name="L394" href="source/net/ipv4/ip_options.c#L394">394</a>                                 case <a href="ident?i=IPOPT_TS_PRESPEC">IPOPT_TS_PRESPEC</a>:
<a name="L395" href="source/net/ipv4/ip_options.c#L395">395</a>                                         if (optptr[2]+7 &gt; <a href="ident?i=optlen">optlen</a>) {
<a name="L396" href="source/net/ipv4/ip_options.c#L396">396</a>                                                 pp_ptr = optptr + 2;
<a name="L397" href="source/net/ipv4/ip_options.c#L397">397</a>                                                 goto <a href="ident?i=error">error</a>;
<a name="L398" href="source/net/ipv4/ip_options.c#L398">398</a>                                         }
<a name="L399" href="source/net/ipv4/ip_options.c#L399">399</a>                                         {
<a name="L400" href="source/net/ipv4/ip_options.c#L400">400</a>                                                 <a href="ident?i=__be32">__be32</a> <a href="ident?i=addr">addr</a>;
<a name="L401" href="source/net/ipv4/ip_options.c#L401">401</a>                                                 <a href="ident?i=memcpy">memcpy</a>(&amp;<a href="ident?i=addr">addr</a>, &amp;optptr[optptr[2]-1], 4);
<a name="L402" href="source/net/ipv4/ip_options.c#L402">402</a>                                                 if (<a href="ident?i=inet_addr_type">inet_addr_type</a>(<a href="ident?i=net">net</a>, <a href="ident?i=addr">addr</a>) == RTN_UNICAST)
<a name="L403" href="source/net/ipv4/ip_options.c#L403">403</a>                                                         break;
<a name="L404" href="source/net/ipv4/ip_options.c#L404">404</a>                                                 if (<a href="ident?i=skb">skb</a>)
<a name="L405" href="source/net/ipv4/ip_options.c#L405">405</a>                                                         timeptr = &amp;optptr[optptr[2]+3];
<a name="L406" href="source/net/ipv4/ip_options.c#L406">406</a>                                         }
<a name="L407" href="source/net/ipv4/ip_options.c#L407">407</a>                                         opt-&gt;ts_needtime = 1;
<a name="L408" href="source/net/ipv4/ip_options.c#L408">408</a>                                         optptr[2] += 8;
<a name="L409" href="source/net/ipv4/ip_options.c#L409">409</a>                                         break;
<a name="L410" href="source/net/ipv4/ip_options.c#L410">410</a>                                 default:
<a name="L411" href="source/net/ipv4/ip_options.c#L411">411</a>                                         if (!<a href="ident?i=skb">skb</a> &amp;&amp; !<a href="ident?i=ns_capable">ns_capable</a>(<a href="ident?i=net">net</a>-&gt;<a href="ident?i=user_ns">user_ns</a>, <a href="ident?i=CAP_NET_RAW">CAP_NET_RAW</a>)) {
<a name="L412" href="source/net/ipv4/ip_options.c#L412">412</a>                                                 pp_ptr = optptr + 3;
<a name="L413" href="source/net/ipv4/ip_options.c#L413">413</a>                                                 goto <a href="ident?i=error">error</a>;
<a name="L414" href="source/net/ipv4/ip_options.c#L414">414</a>                                         }
<a name="L415" href="source/net/ipv4/ip_options.c#L415">415</a>                                         break;
<a name="L416" href="source/net/ipv4/ip_options.c#L416">416</a>                                 }
<a name="L417" href="source/net/ipv4/ip_options.c#L417">417</a>                                 if (timeptr) {
<a name="L418" href="source/net/ipv4/ip_options.c#L418">418</a>                                         struct <a href="ident?i=timespec">timespec</a> tv;
<a name="L419" href="source/net/ipv4/ip_options.c#L419">419</a>                                         <a href="ident?i=u32">u32</a>  midtime;
<a name="L420" href="source/net/ipv4/ip_options.c#L420">420</a>                                         <a href="ident?i=getnstimeofday">getnstimeofday</a>(&amp;tv);
<a name="L421" href="source/net/ipv4/ip_options.c#L421">421</a>                                         midtime = (tv.tv_sec % 86400) * <a href="ident?i=MSEC_PER_SEC">MSEC_PER_SEC</a> + tv.tv_nsec / <a href="ident?i=NSEC_PER_MSEC">NSEC_PER_MSEC</a>;
<a name="L422" href="source/net/ipv4/ip_options.c#L422">422</a>                                         <a href="ident?i=put_unaligned_be32">put_unaligned_be32</a>(midtime, timeptr);
<a name="L423" href="source/net/ipv4/ip_options.c#L423">423</a>                                         opt-&gt;is_changed = 1;
<a name="L424" href="source/net/ipv4/ip_options.c#L424">424</a>                                 }
<a name="L425" href="source/net/ipv4/ip_options.c#L425">425</a>                         } else if ((optptr[3]&amp;0xF) != <a href="ident?i=IPOPT_TS_PRESPEC">IPOPT_TS_PRESPEC</a>) {
<a name="L426" href="source/net/ipv4/ip_options.c#L426">426</a>                                 unsigned int <a href="ident?i=overflow">overflow</a> = optptr[3]&gt;&gt;4;
<a name="L427" href="source/net/ipv4/ip_options.c#L427">427</a>                                 if (<a href="ident?i=overflow">overflow</a> == 15) {
<a name="L428" href="source/net/ipv4/ip_options.c#L428">428</a>                                         pp_ptr = optptr + 3;
<a name="L429" href="source/net/ipv4/ip_options.c#L429">429</a>                                         goto <a href="ident?i=error">error</a>;
<a name="L430" href="source/net/ipv4/ip_options.c#L430">430</a>                                 }
<a name="L431" href="source/net/ipv4/ip_options.c#L431">431</a>                                 if (<a href="ident?i=skb">skb</a>) {
<a name="L432" href="source/net/ipv4/ip_options.c#L432">432</a>                                         optptr[3] = (optptr[3]&amp;0xF)|((<a href="ident?i=overflow">overflow</a>+1)&lt;&lt;4);
<a name="L433" href="source/net/ipv4/ip_options.c#L433">433</a>                                         opt-&gt;is_changed = 1;
<a name="L434" href="source/net/ipv4/ip_options.c#L434">434</a>                                 }
<a name="L435" href="source/net/ipv4/ip_options.c#L435">435</a>                         }
<a name="L436" href="source/net/ipv4/ip_options.c#L436">436</a>                         opt-&gt;<a href="ident?i=ts">ts</a> = optptr - iph;
<a name="L437" href="source/net/ipv4/ip_options.c#L437">437</a>                         break;
<a name="L438" href="source/net/ipv4/ip_options.c#L438">438</a>                 case <a href="ident?i=IPOPT_RA">IPOPT_RA</a>:
<a name="L439" href="source/net/ipv4/ip_options.c#L439">439</a>                         if (<a href="ident?i=optlen">optlen</a> &lt; 4) {
<a name="L440" href="source/net/ipv4/ip_options.c#L440">440</a>                                 pp_ptr = optptr + 1;
<a name="L441" href="source/net/ipv4/ip_options.c#L441">441</a>                                 goto <a href="ident?i=error">error</a>;
<a name="L442" href="source/net/ipv4/ip_options.c#L442">442</a>                         }
<a name="L443" href="source/net/ipv4/ip_options.c#L443">443</a>                         if (optptr[2] == 0 &amp;&amp; optptr[3] == 0)
<a name="L444" href="source/net/ipv4/ip_options.c#L444">444</a>                                 opt-&gt;router_alert = optptr - iph;
<a name="L445" href="source/net/ipv4/ip_options.c#L445">445</a>                         break;
<a name="L446" href="source/net/ipv4/ip_options.c#L446">446</a>                 case <a href="ident?i=IPOPT_CIPSO">IPOPT_CIPSO</a>:
<a name="L447" href="source/net/ipv4/ip_options.c#L447">447</a>                         if ((!<a href="ident?i=skb">skb</a> &amp;&amp; !<a href="ident?i=ns_capable">ns_capable</a>(<a href="ident?i=net">net</a>-&gt;<a href="ident?i=user_ns">user_ns</a>, <a href="ident?i=CAP_NET_RAW">CAP_NET_RAW</a>)) || opt-&gt;cipso) {
<a name="L448" href="source/net/ipv4/ip_options.c#L448">448</a>                                 pp_ptr = optptr;
<a name="L449" href="source/net/ipv4/ip_options.c#L449">449</a>                                 goto <a href="ident?i=error">error</a>;
<a name="L450" href="source/net/ipv4/ip_options.c#L450">450</a>                         }
<a name="L451" href="source/net/ipv4/ip_options.c#L451">451</a>                         opt-&gt;cipso = optptr - iph;
<a name="L452" href="source/net/ipv4/ip_options.c#L452">452</a>                         if (<a href="ident?i=cipso_v4_validate">cipso_v4_validate</a>(<a href="ident?i=skb">skb</a>, &amp;optptr)) {
<a name="L453" href="source/net/ipv4/ip_options.c#L453">453</a>                                 pp_ptr = optptr;
<a name="L454" href="source/net/ipv4/ip_options.c#L454">454</a>                                 goto <a href="ident?i=error">error</a>;
<a name="L455" href="source/net/ipv4/ip_options.c#L455">455</a>                         }
<a name="L456" href="source/net/ipv4/ip_options.c#L456">456</a>                         break;
<a name="L457" href="source/net/ipv4/ip_options.c#L457">457</a>                 case <a href="ident?i=IPOPT_SEC">IPOPT_SEC</a>:
<a name="L458" href="source/net/ipv4/ip_options.c#L458">458</a>                 case <a href="ident?i=IPOPT_SID">IPOPT_SID</a>:
<a name="L459" href="source/net/ipv4/ip_options.c#L459">459</a>                 default:
<a name="L460" href="source/net/ipv4/ip_options.c#L460">460</a>                         if (!<a href="ident?i=skb">skb</a> &amp;&amp; !<a href="ident?i=ns_capable">ns_capable</a>(<a href="ident?i=net">net</a>-&gt;<a href="ident?i=user_ns">user_ns</a>, <a href="ident?i=CAP_NET_RAW">CAP_NET_RAW</a>)) {
<a name="L461" href="source/net/ipv4/ip_options.c#L461">461</a>                                 pp_ptr = optptr;
<a name="L462" href="source/net/ipv4/ip_options.c#L462">462</a>                                 goto <a href="ident?i=error">error</a>;
<a name="L463" href="source/net/ipv4/ip_options.c#L463">463</a>                         }
<a name="L464" href="source/net/ipv4/ip_options.c#L464">464</a>                         break;
<a name="L465" href="source/net/ipv4/ip_options.c#L465">465</a>                 }
<a name="L466" href="source/net/ipv4/ip_options.c#L466">466</a>                 <a href="ident?i=l">l</a> -= <a href="ident?i=optlen">optlen</a>;
<a name="L467" href="source/net/ipv4/ip_options.c#L467">467</a>                 optptr += <a href="ident?i=optlen">optlen</a>;
<a name="L468" href="source/net/ipv4/ip_options.c#L468">468</a>         }
<a name="L469" href="source/net/ipv4/ip_options.c#L469">469</a> 
<a name="L470" href="source/net/ipv4/ip_options.c#L470">470</a> eol:
<a name="L471" href="source/net/ipv4/ip_options.c#L471">471</a>         if (!pp_ptr)
<a name="L472" href="source/net/ipv4/ip_options.c#L472">472</a>                 return 0;
<a name="L473" href="source/net/ipv4/ip_options.c#L473">473</a> 
<a name="L474" href="source/net/ipv4/ip_options.c#L474">474</a> <a href="ident?i=error">error</a>:
<a name="L475" href="source/net/ipv4/ip_options.c#L475">475</a>         if (<a href="ident?i=skb">skb</a>) {
<a name="L476" href="source/net/ipv4/ip_options.c#L476">476</a>                 <a href="ident?i=icmp_send">icmp_send</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=ICMP_PARAMETERPROB">ICMP_PARAMETERPROB</a>, 0, <a href="ident?i=htonl">htonl</a>((pp_ptr-iph)&lt;&lt;24));
<a name="L477" href="source/net/ipv4/ip_options.c#L477">477</a>         }
<a name="L478" href="source/net/ipv4/ip_options.c#L478">478</a>         return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L479" href="source/net/ipv4/ip_options.c#L479">479</a> }
<a name="L480" href="source/net/ipv4/ip_options.c#L480">480</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=ip_options_compile">ip_options_compile</a>);
<a name="L481" href="source/net/ipv4/ip_options.c#L481">481</a> 
<a name="L482" href="source/net/ipv4/ip_options.c#L482">482</a> <b><i>/*</i></b>
<a name="L483" href="source/net/ipv4/ip_options.c#L483">483</a> <b><i> *      Undo all the changes done by ip_options_compile().</i></b>
<a name="L484" href="source/net/ipv4/ip_options.c#L484">484</a> <b><i> */</i></b>
<a name="L485" href="source/net/ipv4/ip_options.c#L485">485</a> 
<a name="L486" href="source/net/ipv4/ip_options.c#L486">486</a> void <a href="ident?i=ip_options_undo">ip_options_undo</a>(struct <a href="ident?i=ip_options">ip_options</a> *opt)
<a name="L487" href="source/net/ipv4/ip_options.c#L487">487</a> {
<a name="L488" href="source/net/ipv4/ip_options.c#L488">488</a>         if (opt-&gt;<a href="ident?i=srr">srr</a>) {
<a name="L489" href="source/net/ipv4/ip_options.c#L489">489</a>                 unsigned  char *optptr = opt-&gt;__data+opt-&gt;<a href="ident?i=srr">srr</a>-sizeof(struct  <a href="ident?i=iphdr">iphdr</a>);
<a name="L490" href="source/net/ipv4/ip_options.c#L490">490</a>                 <a href="ident?i=memmove">memmove</a>(optptr+7, optptr+3, optptr[1]-7);
<a name="L491" href="source/net/ipv4/ip_options.c#L491">491</a>                 <a href="ident?i=memcpy">memcpy</a>(optptr+3, &amp;opt-&gt;faddr, 4);
<a name="L492" href="source/net/ipv4/ip_options.c#L492">492</a>         }
<a name="L493" href="source/net/ipv4/ip_options.c#L493">493</a>         if (opt-&gt;rr_needaddr) {
<a name="L494" href="source/net/ipv4/ip_options.c#L494">494</a>                 unsigned  char *optptr = opt-&gt;__data+opt-&gt;rr-sizeof(struct  <a href="ident?i=iphdr">iphdr</a>);
<a name="L495" href="source/net/ipv4/ip_options.c#L495">495</a>                 optptr[2] -= 4;
<a name="L496" href="source/net/ipv4/ip_options.c#L496">496</a>                 <a href="ident?i=memset">memset</a>(&amp;optptr[optptr[2]-1], 0, 4);
<a name="L497" href="source/net/ipv4/ip_options.c#L497">497</a>         }
<a name="L498" href="source/net/ipv4/ip_options.c#L498">498</a>         if (opt-&gt;<a href="ident?i=ts">ts</a>) {
<a name="L499" href="source/net/ipv4/ip_options.c#L499">499</a>                 unsigned  char *optptr = opt-&gt;__data+opt-&gt;<a href="ident?i=ts">ts</a>-sizeof(struct  <a href="ident?i=iphdr">iphdr</a>);
<a name="L500" href="source/net/ipv4/ip_options.c#L500">500</a>                 if (opt-&gt;ts_needtime) {
<a name="L501" href="source/net/ipv4/ip_options.c#L501">501</a>                         optptr[2] -= 4;
<a name="L502" href="source/net/ipv4/ip_options.c#L502">502</a>                         <a href="ident?i=memset">memset</a>(&amp;optptr[optptr[2]-1], 0, 4);
<a name="L503" href="source/net/ipv4/ip_options.c#L503">503</a>                         if ((optptr[3]&amp;0xF) == <a href="ident?i=IPOPT_TS_PRESPEC">IPOPT_TS_PRESPEC</a>)
<a name="L504" href="source/net/ipv4/ip_options.c#L504">504</a>                                 optptr[2] -= 4;
<a name="L505" href="source/net/ipv4/ip_options.c#L505">505</a>                 }
<a name="L506" href="source/net/ipv4/ip_options.c#L506">506</a>                 if (opt-&gt;ts_needaddr) {
<a name="L507" href="source/net/ipv4/ip_options.c#L507">507</a>                         optptr[2] -= 4;
<a name="L508" href="source/net/ipv4/ip_options.c#L508">508</a>                         <a href="ident?i=memset">memset</a>(&amp;optptr[optptr[2]-1], 0, 4);
<a name="L509" href="source/net/ipv4/ip_options.c#L509">509</a>                 }
<a name="L510" href="source/net/ipv4/ip_options.c#L510">510</a>         }
<a name="L511" href="source/net/ipv4/ip_options.c#L511">511</a> }
<a name="L512" href="source/net/ipv4/ip_options.c#L512">512</a> 
<a name="L513" href="source/net/ipv4/ip_options.c#L513">513</a> static struct <a href="ident?i=ip_options_rcu">ip_options_rcu</a> *<a href="ident?i=ip_options_get_alloc">ip_options_get_alloc</a>(const int <a href="ident?i=optlen">optlen</a>)
<a name="L514" href="source/net/ipv4/ip_options.c#L514">514</a> {
<a name="L515" href="source/net/ipv4/ip_options.c#L515">515</a>         return <a href="ident?i=kzalloc">kzalloc</a>(sizeof(struct <a href="ident?i=ip_options_rcu">ip_options_rcu</a>) + ((<a href="ident?i=optlen">optlen</a> + 3) &amp; ~3),
<a name="L516" href="source/net/ipv4/ip_options.c#L516">516</a>                        <a href="ident?i=GFP_KERNEL">GFP_KERNEL</a>);
<a name="L517" href="source/net/ipv4/ip_options.c#L517">517</a> }
<a name="L518" href="source/net/ipv4/ip_options.c#L518">518</a> 
<a name="L519" href="source/net/ipv4/ip_options.c#L519">519</a> static int <a href="ident?i=ip_options_get_finish">ip_options_get_finish</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>, struct <a href="ident?i=ip_options_rcu">ip_options_rcu</a> **optp,
<a name="L520" href="source/net/ipv4/ip_options.c#L520">520</a>                                  struct <a href="ident?i=ip_options_rcu">ip_options_rcu</a> *opt, int <a href="ident?i=optlen">optlen</a>)
<a name="L521" href="source/net/ipv4/ip_options.c#L521">521</a> {
<a name="L522" href="source/net/ipv4/ip_options.c#L522">522</a>         while (<a href="ident?i=optlen">optlen</a> &amp; 3)
<a name="L523" href="source/net/ipv4/ip_options.c#L523">523</a>                 opt-&gt;opt.__data[<a href="ident?i=optlen">optlen</a>++] = <a href="ident?i=IPOPT_END">IPOPT_END</a>;
<a name="L524" href="source/net/ipv4/ip_options.c#L524">524</a>         opt-&gt;opt.<a href="ident?i=optlen">optlen</a> = <a href="ident?i=optlen">optlen</a>;
<a name="L525" href="source/net/ipv4/ip_options.c#L525">525</a>         if (<a href="ident?i=optlen">optlen</a> &amp;&amp; <a href="ident?i=ip_options_compile">ip_options_compile</a>(<a href="ident?i=net">net</a>, &amp;opt-&gt;opt, <a href="ident?i=NULL">NULL</a>)) {
<a name="L526" href="source/net/ipv4/ip_options.c#L526">526</a>                 <a href="ident?i=kfree">kfree</a>(opt);
<a name="L527" href="source/net/ipv4/ip_options.c#L527">527</a>                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L528" href="source/net/ipv4/ip_options.c#L528">528</a>         }
<a name="L529" href="source/net/ipv4/ip_options.c#L529">529</a>         <a href="ident?i=kfree">kfree</a>(*optp);
<a name="L530" href="source/net/ipv4/ip_options.c#L530">530</a>         *optp = opt;
<a name="L531" href="source/net/ipv4/ip_options.c#L531">531</a>         return 0;
<a name="L532" href="source/net/ipv4/ip_options.c#L532">532</a> }
<a name="L533" href="source/net/ipv4/ip_options.c#L533">533</a> 
<a name="L534" href="source/net/ipv4/ip_options.c#L534">534</a> int <a href="ident?i=ip_options_get_from_user">ip_options_get_from_user</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>, struct <a href="ident?i=ip_options_rcu">ip_options_rcu</a> **optp,
<a name="L535" href="source/net/ipv4/ip_options.c#L535">535</a>                              unsigned char <a href="ident?i=__user">__user</a> *<a href="ident?i=data">data</a>, int <a href="ident?i=optlen">optlen</a>)
<a name="L536" href="source/net/ipv4/ip_options.c#L536">536</a> {
<a name="L537" href="source/net/ipv4/ip_options.c#L537">537</a>         struct <a href="ident?i=ip_options_rcu">ip_options_rcu</a> *opt = <a href="ident?i=ip_options_get_alloc">ip_options_get_alloc</a>(<a href="ident?i=optlen">optlen</a>);
<a name="L538" href="source/net/ipv4/ip_options.c#L538">538</a> 
<a name="L539" href="source/net/ipv4/ip_options.c#L539">539</a>         if (!opt)
<a name="L540" href="source/net/ipv4/ip_options.c#L540">540</a>                 return -<a href="ident?i=ENOMEM">ENOMEM</a>;
<a name="L541" href="source/net/ipv4/ip_options.c#L541">541</a>         if (<a href="ident?i=optlen">optlen</a> &amp;&amp; <a href="ident?i=copy_from_user">copy_from_user</a>(opt-&gt;opt.__data, <a href="ident?i=data">data</a>, <a href="ident?i=optlen">optlen</a>)) {
<a name="L542" href="source/net/ipv4/ip_options.c#L542">542</a>                 <a href="ident?i=kfree">kfree</a>(opt);
<a name="L543" href="source/net/ipv4/ip_options.c#L543">543</a>                 return -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L544" href="source/net/ipv4/ip_options.c#L544">544</a>         }
<a name="L545" href="source/net/ipv4/ip_options.c#L545">545</a>         return <a href="ident?i=ip_options_get_finish">ip_options_get_finish</a>(<a href="ident?i=net">net</a>, optp, opt, <a href="ident?i=optlen">optlen</a>);
<a name="L546" href="source/net/ipv4/ip_options.c#L546">546</a> }
<a name="L547" href="source/net/ipv4/ip_options.c#L547">547</a> 
<a name="L548" href="source/net/ipv4/ip_options.c#L548">548</a> int <a href="ident?i=ip_options_get">ip_options_get</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>, struct <a href="ident?i=ip_options_rcu">ip_options_rcu</a> **optp,
<a name="L549" href="source/net/ipv4/ip_options.c#L549">549</a>                    unsigned char *<a href="ident?i=data">data</a>, int <a href="ident?i=optlen">optlen</a>)
<a name="L550" href="source/net/ipv4/ip_options.c#L550">550</a> {
<a name="L551" href="source/net/ipv4/ip_options.c#L551">551</a>         struct <a href="ident?i=ip_options_rcu">ip_options_rcu</a> *opt = <a href="ident?i=ip_options_get_alloc">ip_options_get_alloc</a>(<a href="ident?i=optlen">optlen</a>);
<a name="L552" href="source/net/ipv4/ip_options.c#L552">552</a> 
<a name="L553" href="source/net/ipv4/ip_options.c#L553">553</a>         if (!opt)
<a name="L554" href="source/net/ipv4/ip_options.c#L554">554</a>                 return -<a href="ident?i=ENOMEM">ENOMEM</a>;
<a name="L555" href="source/net/ipv4/ip_options.c#L555">555</a>         if (<a href="ident?i=optlen">optlen</a>)
<a name="L556" href="source/net/ipv4/ip_options.c#L556">556</a>                 <a href="ident?i=memcpy">memcpy</a>(opt-&gt;opt.__data, <a href="ident?i=data">data</a>, <a href="ident?i=optlen">optlen</a>);
<a name="L557" href="source/net/ipv4/ip_options.c#L557">557</a>         return <a href="ident?i=ip_options_get_finish">ip_options_get_finish</a>(<a href="ident?i=net">net</a>, optp, opt, <a href="ident?i=optlen">optlen</a>);
<a name="L558" href="source/net/ipv4/ip_options.c#L558">558</a> }
<a name="L559" href="source/net/ipv4/ip_options.c#L559">559</a> 
<a name="L560" href="source/net/ipv4/ip_options.c#L560">560</a> void <a href="ident?i=ip_forward_options">ip_forward_options</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L561" href="source/net/ipv4/ip_options.c#L561">561</a> {
<a name="L562" href="source/net/ipv4/ip_options.c#L562">562</a>         struct   <a href="ident?i=ip_options">ip_options</a> *opt        = &amp;(<a href="ident?i=IPCB">IPCB</a>(<a href="ident?i=skb">skb</a>)-&gt;opt);
<a name="L563" href="source/net/ipv4/ip_options.c#L563">563</a>         unsigned char *optptr;
<a name="L564" href="source/net/ipv4/ip_options.c#L564">564</a>         struct <a href="ident?i=rtable">rtable</a> *<a href="ident?i=rt">rt</a> = <a href="ident?i=skb_rtable">skb_rtable</a>(<a href="ident?i=skb">skb</a>);
<a name="L565" href="source/net/ipv4/ip_options.c#L565">565</a>         unsigned char *<a href="ident?i=raw">raw</a> = <a href="ident?i=skb_network_header">skb_network_header</a>(<a href="ident?i=skb">skb</a>);
<a name="L566" href="source/net/ipv4/ip_options.c#L566">566</a> 
<a name="L567" href="source/net/ipv4/ip_options.c#L567">567</a>         if (opt-&gt;rr_needaddr) {
<a name="L568" href="source/net/ipv4/ip_options.c#L568">568</a>                 optptr = (unsigned char *)<a href="ident?i=raw">raw</a> + opt-&gt;rr;
<a name="L569" href="source/net/ipv4/ip_options.c#L569">569</a>                 <a href="ident?i=ip_rt_get_source">ip_rt_get_source</a>(&amp;optptr[optptr[2]-5], <a href="ident?i=skb">skb</a>, <a href="ident?i=rt">rt</a>);
<a name="L570" href="source/net/ipv4/ip_options.c#L570">570</a>                 opt-&gt;is_changed = 1;
<a name="L571" href="source/net/ipv4/ip_options.c#L571">571</a>         }
<a name="L572" href="source/net/ipv4/ip_options.c#L572">572</a>         if (opt-&gt;srr_is_hit) {
<a name="L573" href="source/net/ipv4/ip_options.c#L573">573</a>                 int srrptr, srrspace;
<a name="L574" href="source/net/ipv4/ip_options.c#L574">574</a> 
<a name="L575" href="source/net/ipv4/ip_options.c#L575">575</a>                 optptr = <a href="ident?i=raw">raw</a> + opt-&gt;<a href="ident?i=srr">srr</a>;
<a name="L576" href="source/net/ipv4/ip_options.c#L576">576</a> 
<a name="L577" href="source/net/ipv4/ip_options.c#L577">577</a>                 for ( srrptr = optptr[2], srrspace = optptr[1];
<a name="L578" href="source/net/ipv4/ip_options.c#L578">578</a>                      srrptr &lt;= srrspace;
<a name="L579" href="source/net/ipv4/ip_options.c#L579">579</a>                      srrptr += 4
<a name="L580" href="source/net/ipv4/ip_options.c#L580">580</a>                      ) {
<a name="L581" href="source/net/ipv4/ip_options.c#L581">581</a>                         if (srrptr + 3 &gt; srrspace)
<a name="L582" href="source/net/ipv4/ip_options.c#L582">582</a>                                 break;
<a name="L583" href="source/net/ipv4/ip_options.c#L583">583</a>                         if (<a href="ident?i=memcmp">memcmp</a>(&amp;opt-&gt;nexthop, &amp;optptr[srrptr-1], 4) == 0)
<a name="L584" href="source/net/ipv4/ip_options.c#L584">584</a>                                 break;
<a name="L585" href="source/net/ipv4/ip_options.c#L585">585</a>                 }
<a name="L586" href="source/net/ipv4/ip_options.c#L586">586</a>                 if (srrptr + 3 &lt;= srrspace) {
<a name="L587" href="source/net/ipv4/ip_options.c#L587">587</a>                         opt-&gt;is_changed = 1;
<a name="L588" href="source/net/ipv4/ip_options.c#L588">588</a>                         <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=daddr">daddr</a> = opt-&gt;nexthop;
<a name="L589" href="source/net/ipv4/ip_options.c#L589">589</a>                         <a href="ident?i=ip_rt_get_source">ip_rt_get_source</a>(&amp;optptr[srrptr-1], <a href="ident?i=skb">skb</a>, <a href="ident?i=rt">rt</a>);
<a name="L590" href="source/net/ipv4/ip_options.c#L590">590</a>                         optptr[2] = srrptr+4;
<a name="L591" href="source/net/ipv4/ip_options.c#L591">591</a>                 } else {
<a name="L592" href="source/net/ipv4/ip_options.c#L592">592</a>                         <a href="ident?i=net_crit_ratelimited">net_crit_ratelimited</a>(<i>"%s(): Argh! Destination lost!\n"</i>,
<a name="L593" href="source/net/ipv4/ip_options.c#L593">593</a>                                              <a href="ident?i=__func__">__func__</a>);
<a name="L594" href="source/net/ipv4/ip_options.c#L594">594</a>                 }
<a name="L595" href="source/net/ipv4/ip_options.c#L595">595</a>                 if (opt-&gt;ts_needaddr) {
<a name="L596" href="source/net/ipv4/ip_options.c#L596">596</a>                         optptr = <a href="ident?i=raw">raw</a> + opt-&gt;<a href="ident?i=ts">ts</a>;
<a name="L597" href="source/net/ipv4/ip_options.c#L597">597</a>                         <a href="ident?i=ip_rt_get_source">ip_rt_get_source</a>(&amp;optptr[optptr[2]-9], <a href="ident?i=skb">skb</a>, <a href="ident?i=rt">rt</a>);
<a name="L598" href="source/net/ipv4/ip_options.c#L598">598</a>                         opt-&gt;is_changed = 1;
<a name="L599" href="source/net/ipv4/ip_options.c#L599">599</a>                 }
<a name="L600" href="source/net/ipv4/ip_options.c#L600">600</a>         }
<a name="L601" href="source/net/ipv4/ip_options.c#L601">601</a>         if (opt-&gt;is_changed) {
<a name="L602" href="source/net/ipv4/ip_options.c#L602">602</a>                 opt-&gt;is_changed = 0;
<a name="L603" href="source/net/ipv4/ip_options.c#L603">603</a>                 <a href="ident?i=ip_send_check">ip_send_check</a>(<a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>));
<a name="L604" href="source/net/ipv4/ip_options.c#L604">604</a>         }
<a name="L605" href="source/net/ipv4/ip_options.c#L605">605</a> }
<a name="L606" href="source/net/ipv4/ip_options.c#L606">606</a> 
<a name="L607" href="source/net/ipv4/ip_options.c#L607">607</a> int <a href="ident?i=ip_options_rcv_srr">ip_options_rcv_srr</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L608" href="source/net/ipv4/ip_options.c#L608">608</a> {
<a name="L609" href="source/net/ipv4/ip_options.c#L609">609</a>         struct <a href="ident?i=ip_options">ip_options</a> *opt = &amp;(<a href="ident?i=IPCB">IPCB</a>(<a href="ident?i=skb">skb</a>)-&gt;opt);
<a name="L610" href="source/net/ipv4/ip_options.c#L610">610</a>         int srrspace, srrptr;
<a name="L611" href="source/net/ipv4/ip_options.c#L611">611</a>         <a href="ident?i=__be32">__be32</a> nexthop;
<a name="L612" href="source/net/ipv4/ip_options.c#L612">612</a>         struct <a href="ident?i=iphdr">iphdr</a> *iph = <a href="ident?i=ip_hdr">ip_hdr</a>(<a href="ident?i=skb">skb</a>);
<a name="L613" href="source/net/ipv4/ip_options.c#L613">613</a>         unsigned char *optptr = <a href="ident?i=skb_network_header">skb_network_header</a>(<a href="ident?i=skb">skb</a>) + opt-&gt;<a href="ident?i=srr">srr</a>;
<a name="L614" href="source/net/ipv4/ip_options.c#L614">614</a>         struct <a href="ident?i=rtable">rtable</a> *<a href="ident?i=rt">rt</a> = <a href="ident?i=skb_rtable">skb_rtable</a>(<a href="ident?i=skb">skb</a>);
<a name="L615" href="source/net/ipv4/ip_options.c#L615">615</a>         struct <a href="ident?i=rtable">rtable</a> *rt2;
<a name="L616" href="source/net/ipv4/ip_options.c#L616">616</a>         unsigned long orefdst;
<a name="L617" href="source/net/ipv4/ip_options.c#L617">617</a>         int <a href="ident?i=err">err</a>;
<a name="L618" href="source/net/ipv4/ip_options.c#L618">618</a> 
<a name="L619" href="source/net/ipv4/ip_options.c#L619">619</a>         if (!<a href="ident?i=rt">rt</a>)
<a name="L620" href="source/net/ipv4/ip_options.c#L620">620</a>                 return 0;
<a name="L621" href="source/net/ipv4/ip_options.c#L621">621</a> 
<a name="L622" href="source/net/ipv4/ip_options.c#L622">622</a>         if (<a href="ident?i=skb">skb</a>-&gt;pkt_type != <a href="ident?i=PACKET_HOST">PACKET_HOST</a>)
<a name="L623" href="source/net/ipv4/ip_options.c#L623">623</a>                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L624" href="source/net/ipv4/ip_options.c#L624">624</a>         if (<a href="ident?i=rt">rt</a>-&gt;rt_type == RTN_UNICAST) {
<a name="L625" href="source/net/ipv4/ip_options.c#L625">625</a>                 if (!opt-&gt;is_strictroute)
<a name="L626" href="source/net/ipv4/ip_options.c#L626">626</a>                         return 0;
<a name="L627" href="source/net/ipv4/ip_options.c#L627">627</a>                 <a href="ident?i=icmp_send">icmp_send</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=ICMP_PARAMETERPROB">ICMP_PARAMETERPROB</a>, 0, <a href="ident?i=htonl">htonl</a>(16&lt;&lt;24));
<a name="L628" href="source/net/ipv4/ip_options.c#L628">628</a>                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L629" href="source/net/ipv4/ip_options.c#L629">629</a>         }
<a name="L630" href="source/net/ipv4/ip_options.c#L630">630</a>         if (<a href="ident?i=rt">rt</a>-&gt;rt_type != RTN_LOCAL)
<a name="L631" href="source/net/ipv4/ip_options.c#L631">631</a>                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L632" href="source/net/ipv4/ip_options.c#L632">632</a> 
<a name="L633" href="source/net/ipv4/ip_options.c#L633">633</a>         for (srrptr = optptr[2], srrspace = optptr[1]; srrptr &lt;= srrspace; srrptr += 4) {
<a name="L634" href="source/net/ipv4/ip_options.c#L634">634</a>                 if (srrptr + 3 &gt; srrspace) {
<a name="L635" href="source/net/ipv4/ip_options.c#L635">635</a>                         <a href="ident?i=icmp_send">icmp_send</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=ICMP_PARAMETERPROB">ICMP_PARAMETERPROB</a>, 0, <a href="ident?i=htonl">htonl</a>((opt-&gt;<a href="ident?i=srr">srr</a>+2)&lt;&lt;24));
<a name="L636" href="source/net/ipv4/ip_options.c#L636">636</a>                         return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L637" href="source/net/ipv4/ip_options.c#L637">637</a>                 }
<a name="L638" href="source/net/ipv4/ip_options.c#L638">638</a>                 <a href="ident?i=memcpy">memcpy</a>(&amp;nexthop, &amp;optptr[srrptr-1], 4);
<a name="L639" href="source/net/ipv4/ip_options.c#L639">639</a> 
<a name="L640" href="source/net/ipv4/ip_options.c#L640">640</a>                 orefdst = <a href="ident?i=skb">skb</a>-&gt;_skb_refdst;
<a name="L641" href="source/net/ipv4/ip_options.c#L641">641</a>                 <a href="ident?i=skb_dst_set">skb_dst_set</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=NULL">NULL</a>);
<a name="L642" href="source/net/ipv4/ip_options.c#L642">642</a>                 <a href="ident?i=err">err</a> = <a href="ident?i=ip_route_input">ip_route_input</a>(<a href="ident?i=skb">skb</a>, nexthop, iph-&gt;<a href="ident?i=saddr">saddr</a>, iph-&gt;tos, <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=dev">dev</a>);
<a name="L643" href="source/net/ipv4/ip_options.c#L643">643</a>                 rt2 = <a href="ident?i=skb_rtable">skb_rtable</a>(<a href="ident?i=skb">skb</a>);
<a name="L644" href="source/net/ipv4/ip_options.c#L644">644</a>                 if (<a href="ident?i=err">err</a> || (rt2-&gt;rt_type != RTN_UNICAST &amp;&amp; rt2-&gt;rt_type != RTN_LOCAL)) {
<a name="L645" href="source/net/ipv4/ip_options.c#L645">645</a>                         <a href="ident?i=skb_dst_drop">skb_dst_drop</a>(<a href="ident?i=skb">skb</a>);
<a name="L646" href="source/net/ipv4/ip_options.c#L646">646</a>                         <a href="ident?i=skb">skb</a>-&gt;_skb_refdst = orefdst;
<a name="L647" href="source/net/ipv4/ip_options.c#L647">647</a>                         return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L648" href="source/net/ipv4/ip_options.c#L648">648</a>                 }
<a name="L649" href="source/net/ipv4/ip_options.c#L649">649</a>                 <a href="ident?i=refdst_drop">refdst_drop</a>(orefdst);
<a name="L650" href="source/net/ipv4/ip_options.c#L650">650</a>                 if (rt2-&gt;rt_type != RTN_LOCAL)
<a name="L651" href="source/net/ipv4/ip_options.c#L651">651</a>                         break;
<a name="L652" href="source/net/ipv4/ip_options.c#L652">652</a>                 <b><i>/* Superfast 8) loopback forward */</i></b>
<a name="L653" href="source/net/ipv4/ip_options.c#L653">653</a>                 iph-&gt;<a href="ident?i=daddr">daddr</a> = nexthop;
<a name="L654" href="source/net/ipv4/ip_options.c#L654">654</a>                 opt-&gt;is_changed = 1;
<a name="L655" href="source/net/ipv4/ip_options.c#L655">655</a>         }
<a name="L656" href="source/net/ipv4/ip_options.c#L656">656</a>         if (srrptr &lt;= srrspace) {
<a name="L657" href="source/net/ipv4/ip_options.c#L657">657</a>                 opt-&gt;srr_is_hit = 1;
<a name="L658" href="source/net/ipv4/ip_options.c#L658">658</a>                 opt-&gt;nexthop = nexthop;
<a name="L659" href="source/net/ipv4/ip_options.c#L659">659</a>                 opt-&gt;is_changed = 1;
<a name="L660" href="source/net/ipv4/ip_options.c#L660">660</a>         }
<a name="L661" href="source/net/ipv4/ip_options.c#L661">661</a>         return 0;
<a name="L662" href="source/net/ipv4/ip_options.c#L662">662</a> }
<a name="L663" href="source/net/ipv4/ip_options.c#L663">663</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=ip_options_rcv_srr">ip_options_rcv_srr</a>);
<a name="L664" href="source/net/ipv4/ip_options.c#L664">664</a> </pre></div><p>
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
