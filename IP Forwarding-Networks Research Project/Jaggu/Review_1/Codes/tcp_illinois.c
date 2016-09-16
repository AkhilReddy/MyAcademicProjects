<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title>Linux/net/ipv4/tcp_illinois.c - Linux Cross Reference - Free Electrons</title>
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
		 &nbsp;&bull;&nbsp;<b><i>source navigation</i></b> &nbsp;&bull;&nbsp;<a href="diff/net/ipv4/tcp_illinois.c">diff markup</a> &nbsp;&bull;&nbsp;<a href="ident">identifier search</a> &nbsp;&bull;&nbsp;<a href="search">freetext search</a> &nbsp;&bull;&nbsp;
		</p>
	</div>
</div>

<div id="topbar">
  
  <p>Version: &nbsp;<a href="source/net/ipv4/tcp_illinois.c?v=2.0.40">2.0.40</a>&nbsp;<a href="source/net/ipv4/tcp_illinois.c?v=2.2.26">2.2.26</a>&nbsp;<a href="source/net/ipv4/tcp_illinois.c?v=2.4.37">2.4.37</a>&nbsp;<a href="source/net/ipv4/tcp_illinois.c?v=3.5">3.5</a>&nbsp;<a href="source/net/ipv4/tcp_illinois.c?v=3.6">3.6</a>&nbsp;<a href="source/net/ipv4/tcp_illinois.c?v=3.7">3.7</a>&nbsp;<a href="source/net/ipv4/tcp_illinois.c?v=3.8">3.8</a>&nbsp;<a href="source/net/ipv4/tcp_illinois.c?v=3.9">3.9</a>&nbsp;<a href="source/net/ipv4/tcp_illinois.c?v=3.10">3.10</a>&nbsp;<a href="source/net/ipv4/tcp_illinois.c?v=3.11">3.11</a>&nbsp;<a href="source/net/ipv4/tcp_illinois.c?v=3.12">3.12</a>&nbsp;<a href="source/net/ipv4/tcp_illinois.c?v=3.13">3.13</a>&nbsp;<a href="source/net/ipv4/tcp_illinois.c?v=3.14">3.14</a>&nbsp;<a href="source/net/ipv4/tcp_illinois.c?v=3.15">3.15</a>&nbsp;<a href="source/net/ipv4/tcp_illinois.c?v=3.16">3.16</a>&nbsp;<a href="source/net/ipv4/tcp_illinois.c?v=3.17">3.17</a>&nbsp;<a href="source/net/ipv4/tcp_illinois.c?v=3.18">3.18</a>&nbsp;<a href="source/net/ipv4/tcp_illinois.c?v=3.19">3.19</a>&nbsp;<a href="source/net/ipv4/tcp_illinois.c?v=4.0">4.0</a>&nbsp;<b><i>4.1</i></b></p>
  
</div>

<h1><a href="source/">Linux</a>/<a href="source/net/">net</a>/<a href="source/net/ipv4/">ipv4</a>/<a href="source/net/ipv4/tcp_illinois.c">tcp_illinois.c</a></h1>
<div id="lxrcode"><pre>  <a name="L1" href="source/net/ipv4/tcp_illinois.c#L1">1</a> <b><i>/*</i></b>
  <a name="L2" href="source/net/ipv4/tcp_illinois.c#L2">2</a> <b><i> * TCP Illinois congestion control.</i></b>
  <a name="L3" href="source/net/ipv4/tcp_illinois.c#L3">3</a> <b><i> * Home page:</i></b>
  <a name="L4" href="source/net/ipv4/tcp_illinois.c#L4">4</a> <b><i> *      <a href="http://www.ews.uiuc.edu/~shaoliu/tcpillinois/index.html">http://www.ews.uiuc.edu/~shaoliu/tcpillinois/index.html</a></i></b>
  <a name="L5" href="source/net/ipv4/tcp_illinois.c#L5">5</a> <b><i> *</i></b>
  <a name="L6" href="source/net/ipv4/tcp_illinois.c#L6">6</a> <b><i> * The algorithm is described in:</i></b>
  <a name="L7" href="source/net/ipv4/tcp_illinois.c#L7">7</a> <b><i> * "TCP-Illinois: A Loss and Delay-Based Congestion Control Algorithm</i></b>
  <a name="L8" href="source/net/ipv4/tcp_illinois.c#L8">8</a> <b><i> *  for High-Speed Networks"</i></b>
  <a name="L9" href="source/net/ipv4/tcp_illinois.c#L9">9</a> <b><i> * <a href="http://www.ifp.illinois.edu/~srikant/Papers/liubassri06perf.pdf">http://www.ifp.illinois.edu/~srikant/Papers/liubassri06perf.pdf</a></i></b>
 <a name="L10" href="source/net/ipv4/tcp_illinois.c#L10">10</a> <b><i> *</i></b>
 <a name="L11" href="source/net/ipv4/tcp_illinois.c#L11">11</a> <b><i> * Implemented from description in paper and ns-2 simulation.</i></b>
 <a name="L12" href="source/net/ipv4/tcp_illinois.c#L12">12</a> <b><i> * Copyright (C) 2007 Stephen Hemminger &lt;shemminger@linux-foundation.org&gt;</i></b>
 <a name="L13" href="source/net/ipv4/tcp_illinois.c#L13">13</a> <b><i> */</i></b>
 <a name="L14" href="source/net/ipv4/tcp_illinois.c#L14">14</a> 
 <a name="L15" href="source/net/ipv4/tcp_illinois.c#L15">15</a> #include &lt;linux/module.h&gt;
 <a name="L16" href="source/net/ipv4/tcp_illinois.c#L16">16</a> #include &lt;linux/skbuff.h&gt;
 <a name="L17" href="source/net/ipv4/tcp_illinois.c#L17">17</a> #include &lt;linux/inet_diag.h&gt;
 <a name="L18" href="source/net/ipv4/tcp_illinois.c#L18">18</a> #include &lt;asm/div64.h&gt;
 <a name="L19" href="source/net/ipv4/tcp_illinois.c#L19">19</a> #include &lt;net/tcp.h&gt;
 <a name="L20" href="source/net/ipv4/tcp_illinois.c#L20">20</a> 
 <a name="L21" href="source/net/ipv4/tcp_illinois.c#L21">21</a> #define <a href="ident?i=ALPHA_SHIFT">ALPHA_SHIFT</a>     7
 <a name="L22" href="source/net/ipv4/tcp_illinois.c#L22">22</a> #define <a href="ident?i=ALPHA_SCALE">ALPHA_SCALE</a>     (1u&lt;&lt;<a href="ident?i=ALPHA_SHIFT">ALPHA_SHIFT</a>)
 <a name="L23" href="source/net/ipv4/tcp_illinois.c#L23">23</a> #define <a href="ident?i=ALPHA_MIN">ALPHA_MIN</a>       ((3*<a href="ident?i=ALPHA_SCALE">ALPHA_SCALE</a>)/10)    <b><i>/* ~0.3 */</i></b>
 <a name="L24" href="source/net/ipv4/tcp_illinois.c#L24">24</a> #define <a href="ident?i=ALPHA_MAX">ALPHA_MAX</a>       (10*<a href="ident?i=ALPHA_SCALE">ALPHA_SCALE</a>)        <b><i>/* 10.0 */</i></b>
 <a name="L25" href="source/net/ipv4/tcp_illinois.c#L25">25</a> #define <a href="ident?i=ALPHA_BASE">ALPHA_BASE</a>      <a href="ident?i=ALPHA_SCALE">ALPHA_SCALE</a>             <b><i>/* 1.0 */</i></b>
 <a name="L26" href="source/net/ipv4/tcp_illinois.c#L26">26</a> #define <a href="ident?i=RTT_MAX">RTT_MAX</a>         (<a href="ident?i=U32_MAX">U32_MAX</a> / <a href="ident?i=ALPHA_MAX">ALPHA_MAX</a>)   <b><i>/* 3.3 secs */</i></b>
 <a name="L27" href="source/net/ipv4/tcp_illinois.c#L27">27</a> 
 <a name="L28" href="source/net/ipv4/tcp_illinois.c#L28">28</a> #define <a href="ident?i=BETA_SHIFT">BETA_SHIFT</a>      6
 <a name="L29" href="source/net/ipv4/tcp_illinois.c#L29">29</a> #define <a href="ident?i=BETA_SCALE">BETA_SCALE</a>      (1u&lt;&lt;<a href="ident?i=BETA_SHIFT">BETA_SHIFT</a>)
 <a name="L30" href="source/net/ipv4/tcp_illinois.c#L30">30</a> #define <a href="ident?i=BETA_MIN">BETA_MIN</a>        (<a href="ident?i=BETA_SCALE">BETA_SCALE</a>/8)          <b><i>/* 0.125 */</i></b>
 <a name="L31" href="source/net/ipv4/tcp_illinois.c#L31">31</a> #define <a href="ident?i=BETA_MAX">BETA_MAX</a>        (<a href="ident?i=BETA_SCALE">BETA_SCALE</a>/2)          <b><i>/* 0.5 */</i></b>
 <a name="L32" href="source/net/ipv4/tcp_illinois.c#L32">32</a> #define <a href="ident?i=BETA_BASE">BETA_BASE</a>       <a href="ident?i=BETA_MAX">BETA_MAX</a>
 <a name="L33" href="source/net/ipv4/tcp_illinois.c#L33">33</a> 
 <a name="L34" href="source/net/ipv4/tcp_illinois.c#L34">34</a> static int win_thresh <a href="ident?i=__read_mostly">__read_mostly</a> = 15;
 <a name="L35" href="source/net/ipv4/tcp_illinois.c#L35">35</a> <a href="ident?i=module_param">module_param</a>(win_thresh, int, 0);
 <a name="L36" href="source/net/ipv4/tcp_illinois.c#L36">36</a> <a href="ident?i=MODULE_PARM_DESC">MODULE_PARM_DESC</a>(win_thresh, <i>"Window threshold for starting adaptive sizing"</i>);
 <a name="L37" href="source/net/ipv4/tcp_illinois.c#L37">37</a> 
 <a name="L38" href="source/net/ipv4/tcp_illinois.c#L38">38</a> static int theta <a href="ident?i=__read_mostly">__read_mostly</a> = 5;
 <a name="L39" href="source/net/ipv4/tcp_illinois.c#L39">39</a> <a href="ident?i=module_param">module_param</a>(theta, int, 0);
 <a name="L40" href="source/net/ipv4/tcp_illinois.c#L40">40</a> <a href="ident?i=MODULE_PARM_DESC">MODULE_PARM_DESC</a>(theta, <i>"# of fast RTT's before full growth"</i>);
 <a name="L41" href="source/net/ipv4/tcp_illinois.c#L41">41</a> 
 <a name="L42" href="source/net/ipv4/tcp_illinois.c#L42">42</a> <b><i>/* TCP Illinois Parameters */</i></b>
 <a name="L43" href="source/net/ipv4/tcp_illinois.c#L43">43</a> struct <a href="ident?i=illinois">illinois</a> {
 <a name="L44" href="source/net/ipv4/tcp_illinois.c#L44">44</a>         <a href="ident?i=u64">u64</a>     sum_rtt;        <b><i>/* sum of rtt's measured within last rtt */</i></b>
 <a name="L45" href="source/net/ipv4/tcp_illinois.c#L45">45</a>         <a href="ident?i=u16">u16</a>     cnt_rtt;        <b><i>/* # of rtts measured within last rtt */</i></b>
 <a name="L46" href="source/net/ipv4/tcp_illinois.c#L46">46</a>         <a href="ident?i=u32">u32</a>     base_rtt;       <b><i>/* min of all rtt in usec */</i></b>
 <a name="L47" href="source/net/ipv4/tcp_illinois.c#L47">47</a>         <a href="ident?i=u32">u32</a>     max_rtt;        <b><i>/* max of all rtt in usec */</i></b>
 <a name="L48" href="source/net/ipv4/tcp_illinois.c#L48">48</a>         <a href="ident?i=u32">u32</a>     end_seq;        <b><i>/* right edge of current RTT */</i></b>
 <a name="L49" href="source/net/ipv4/tcp_illinois.c#L49">49</a>         <a href="ident?i=u32">u32</a>     <a href="ident?i=alpha">alpha</a>;          <b><i>/* Additive increase */</i></b>
 <a name="L50" href="source/net/ipv4/tcp_illinois.c#L50">50</a>         <a href="ident?i=u32">u32</a>     <a href="ident?i=beta">beta</a>;           <b><i>/* Muliplicative decrease */</i></b>
 <a name="L51" href="source/net/ipv4/tcp_illinois.c#L51">51</a>         <a href="ident?i=u16">u16</a>     acked;          <b><i>/* # packets acked by current ACK */</i></b>
 <a name="L52" href="source/net/ipv4/tcp_illinois.c#L52">52</a>         <a href="ident?i=u8">u8</a>      rtt_above;      <b><i>/* average rtt has gone above threshold */</i></b>
 <a name="L53" href="source/net/ipv4/tcp_illinois.c#L53">53</a>         <a href="ident?i=u8">u8</a>      rtt_low;        <b><i>/* # of rtts measurements below threshold */</i></b>
 <a name="L54" href="source/net/ipv4/tcp_illinois.c#L54">54</a> };
 <a name="L55" href="source/net/ipv4/tcp_illinois.c#L55">55</a> 
 <a name="L56" href="source/net/ipv4/tcp_illinois.c#L56">56</a> static void <a href="ident?i=rtt_reset">rtt_reset</a>(struct <a href="ident?i=sock">sock</a> *sk)
 <a name="L57" href="source/net/ipv4/tcp_illinois.c#L57">57</a> {
 <a name="L58" href="source/net/ipv4/tcp_illinois.c#L58">58</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
 <a name="L59" href="source/net/ipv4/tcp_illinois.c#L59">59</a>         struct <a href="ident?i=illinois">illinois</a> *<a href="ident?i=ca">ca</a> = <a href="ident?i=inet_csk_ca">inet_csk_ca</a>(sk);
 <a name="L60" href="source/net/ipv4/tcp_illinois.c#L60">60</a> 
 <a name="L61" href="source/net/ipv4/tcp_illinois.c#L61">61</a>         <a href="ident?i=ca">ca</a>-&gt;end_seq = <a href="ident?i=tp">tp</a>-&gt;snd_nxt;
 <a name="L62" href="source/net/ipv4/tcp_illinois.c#L62">62</a>         <a href="ident?i=ca">ca</a>-&gt;cnt_rtt = 0;
 <a name="L63" href="source/net/ipv4/tcp_illinois.c#L63">63</a>         <a href="ident?i=ca">ca</a>-&gt;sum_rtt = 0;
 <a name="L64" href="source/net/ipv4/tcp_illinois.c#L64">64</a> 
 <a name="L65" href="source/net/ipv4/tcp_illinois.c#L65">65</a>         <b><i>/* TODO: age max_rtt? */</i></b>
 <a name="L66" href="source/net/ipv4/tcp_illinois.c#L66">66</a> }
 <a name="L67" href="source/net/ipv4/tcp_illinois.c#L67">67</a> 
 <a name="L68" href="source/net/ipv4/tcp_illinois.c#L68">68</a> static void <a href="ident?i=tcp_illinois_init">tcp_illinois_init</a>(struct <a href="ident?i=sock">sock</a> *sk)
 <a name="L69" href="source/net/ipv4/tcp_illinois.c#L69">69</a> {
 <a name="L70" href="source/net/ipv4/tcp_illinois.c#L70">70</a>         struct <a href="ident?i=illinois">illinois</a> *<a href="ident?i=ca">ca</a> = <a href="ident?i=inet_csk_ca">inet_csk_ca</a>(sk);
 <a name="L71" href="source/net/ipv4/tcp_illinois.c#L71">71</a> 
 <a name="L72" href="source/net/ipv4/tcp_illinois.c#L72">72</a>         <a href="ident?i=ca">ca</a>-&gt;<a href="ident?i=alpha">alpha</a> = <a href="ident?i=ALPHA_MAX">ALPHA_MAX</a>;
 <a name="L73" href="source/net/ipv4/tcp_illinois.c#L73">73</a>         <a href="ident?i=ca">ca</a>-&gt;<a href="ident?i=beta">beta</a> = <a href="ident?i=BETA_BASE">BETA_BASE</a>;
 <a name="L74" href="source/net/ipv4/tcp_illinois.c#L74">74</a>         <a href="ident?i=ca">ca</a>-&gt;base_rtt = 0x7fffffff;
 <a name="L75" href="source/net/ipv4/tcp_illinois.c#L75">75</a>         <a href="ident?i=ca">ca</a>-&gt;max_rtt = 0;
 <a name="L76" href="source/net/ipv4/tcp_illinois.c#L76">76</a> 
 <a name="L77" href="source/net/ipv4/tcp_illinois.c#L77">77</a>         <a href="ident?i=ca">ca</a>-&gt;acked = 0;
 <a name="L78" href="source/net/ipv4/tcp_illinois.c#L78">78</a>         <a href="ident?i=ca">ca</a>-&gt;rtt_low = 0;
 <a name="L79" href="source/net/ipv4/tcp_illinois.c#L79">79</a>         <a href="ident?i=ca">ca</a>-&gt;rtt_above = 0;
 <a name="L80" href="source/net/ipv4/tcp_illinois.c#L80">80</a> 
 <a name="L81" href="source/net/ipv4/tcp_illinois.c#L81">81</a>         <a href="ident?i=rtt_reset">rtt_reset</a>(sk);
 <a name="L82" href="source/net/ipv4/tcp_illinois.c#L82">82</a> }
 <a name="L83" href="source/net/ipv4/tcp_illinois.c#L83">83</a> 
 <a name="L84" href="source/net/ipv4/tcp_illinois.c#L84">84</a> <b><i>/* Measure RTT for each ack. */</i></b>
 <a name="L85" href="source/net/ipv4/tcp_illinois.c#L85">85</a> static void <a href="ident?i=tcp_illinois_acked">tcp_illinois_acked</a>(struct <a href="ident?i=sock">sock</a> *sk, <a href="ident?i=u32">u32</a> pkts_acked, <a href="ident?i=s32">s32</a> rtt)
 <a name="L86" href="source/net/ipv4/tcp_illinois.c#L86">86</a> {
 <a name="L87" href="source/net/ipv4/tcp_illinois.c#L87">87</a>         struct <a href="ident?i=illinois">illinois</a> *<a href="ident?i=ca">ca</a> = <a href="ident?i=inet_csk_ca">inet_csk_ca</a>(sk);
 <a name="L88" href="source/net/ipv4/tcp_illinois.c#L88">88</a> 
 <a name="L89" href="source/net/ipv4/tcp_illinois.c#L89">89</a>         <a href="ident?i=ca">ca</a>-&gt;acked = pkts_acked;
 <a name="L90" href="source/net/ipv4/tcp_illinois.c#L90">90</a> 
 <a name="L91" href="source/net/ipv4/tcp_illinois.c#L91">91</a>         <b><i>/* dup ack, no rtt sample */</i></b>
 <a name="L92" href="source/net/ipv4/tcp_illinois.c#L92">92</a>         if (rtt &lt; 0)
 <a name="L93" href="source/net/ipv4/tcp_illinois.c#L93">93</a>                 return;
 <a name="L94" href="source/net/ipv4/tcp_illinois.c#L94">94</a> 
 <a name="L95" href="source/net/ipv4/tcp_illinois.c#L95">95</a>         <b><i>/* ignore bogus values, this prevents wraparound in alpha math */</i></b>
 <a name="L96" href="source/net/ipv4/tcp_illinois.c#L96">96</a>         if (rtt &gt; <a href="ident?i=RTT_MAX">RTT_MAX</a>)
 <a name="L97" href="source/net/ipv4/tcp_illinois.c#L97">97</a>                 rtt = <a href="ident?i=RTT_MAX">RTT_MAX</a>;
 <a name="L98" href="source/net/ipv4/tcp_illinois.c#L98">98</a> 
 <a name="L99" href="source/net/ipv4/tcp_illinois.c#L99">99</a>         <b><i>/* keep track of minimum RTT seen so far */</i></b>
<a name="L100" href="source/net/ipv4/tcp_illinois.c#L100">100</a>         if (<a href="ident?i=ca">ca</a>-&gt;base_rtt &gt; rtt)
<a name="L101" href="source/net/ipv4/tcp_illinois.c#L101">101</a>                 <a href="ident?i=ca">ca</a>-&gt;base_rtt = rtt;
<a name="L102" href="source/net/ipv4/tcp_illinois.c#L102">102</a> 
<a name="L103" href="source/net/ipv4/tcp_illinois.c#L103">103</a>         <b><i>/* and max */</i></b>
<a name="L104" href="source/net/ipv4/tcp_illinois.c#L104">104</a>         if (<a href="ident?i=ca">ca</a>-&gt;max_rtt &lt; rtt)
<a name="L105" href="source/net/ipv4/tcp_illinois.c#L105">105</a>                 <a href="ident?i=ca">ca</a>-&gt;max_rtt = rtt;
<a name="L106" href="source/net/ipv4/tcp_illinois.c#L106">106</a> 
<a name="L107" href="source/net/ipv4/tcp_illinois.c#L107">107</a>         ++<a href="ident?i=ca">ca</a>-&gt;cnt_rtt;
<a name="L108" href="source/net/ipv4/tcp_illinois.c#L108">108</a>         <a href="ident?i=ca">ca</a>-&gt;sum_rtt += rtt;
<a name="L109" href="source/net/ipv4/tcp_illinois.c#L109">109</a> }
<a name="L110" href="source/net/ipv4/tcp_illinois.c#L110">110</a> 
<a name="L111" href="source/net/ipv4/tcp_illinois.c#L111">111</a> <b><i>/* Maximum queuing delay */</i></b>
<a name="L112" href="source/net/ipv4/tcp_illinois.c#L112">112</a> static inline <a href="ident?i=u32">u32</a> <a href="ident?i=max_delay">max_delay</a>(const struct <a href="ident?i=illinois">illinois</a> *<a href="ident?i=ca">ca</a>)
<a name="L113" href="source/net/ipv4/tcp_illinois.c#L113">113</a> {
<a name="L114" href="source/net/ipv4/tcp_illinois.c#L114">114</a>         return <a href="ident?i=ca">ca</a>-&gt;max_rtt - <a href="ident?i=ca">ca</a>-&gt;base_rtt;
<a name="L115" href="source/net/ipv4/tcp_illinois.c#L115">115</a> }
<a name="L116" href="source/net/ipv4/tcp_illinois.c#L116">116</a> 
<a name="L117" href="source/net/ipv4/tcp_illinois.c#L117">117</a> <b><i>/* Average queuing delay */</i></b>
<a name="L118" href="source/net/ipv4/tcp_illinois.c#L118">118</a> static inline <a href="ident?i=u32">u32</a> <a href="ident?i=avg_delay">avg_delay</a>(const struct <a href="ident?i=illinois">illinois</a> *<a href="ident?i=ca">ca</a>)
<a name="L119" href="source/net/ipv4/tcp_illinois.c#L119">119</a> {
<a name="L120" href="source/net/ipv4/tcp_illinois.c#L120">120</a>         <a href="ident?i=u64">u64</a> <a href="ident?i=t">t</a> = <a href="ident?i=ca">ca</a>-&gt;sum_rtt;
<a name="L121" href="source/net/ipv4/tcp_illinois.c#L121">121</a> 
<a name="L122" href="source/net/ipv4/tcp_illinois.c#L122">122</a>         <a href="ident?i=do_div">do_div</a>(<a href="ident?i=t">t</a>, <a href="ident?i=ca">ca</a>-&gt;cnt_rtt);
<a name="L123" href="source/net/ipv4/tcp_illinois.c#L123">123</a>         return <a href="ident?i=t">t</a> - <a href="ident?i=ca">ca</a>-&gt;base_rtt;
<a name="L124" href="source/net/ipv4/tcp_illinois.c#L124">124</a> }
<a name="L125" href="source/net/ipv4/tcp_illinois.c#L125">125</a> 
<a name="L126" href="source/net/ipv4/tcp_illinois.c#L126">126</a> <b><i>/*</i></b>
<a name="L127" href="source/net/ipv4/tcp_illinois.c#L127">127</a> <b><i> * Compute value of alpha used for additive increase.</i></b>
<a name="L128" href="source/net/ipv4/tcp_illinois.c#L128">128</a> <b><i> * If small window then use 1.0, equivalent to Reno.</i></b>
<a name="L129" href="source/net/ipv4/tcp_illinois.c#L129">129</a> <b><i> *</i></b>
<a name="L130" href="source/net/ipv4/tcp_illinois.c#L130">130</a> <b><i> * For larger windows, adjust based on average delay.</i></b>
<a name="L131" href="source/net/ipv4/tcp_illinois.c#L131">131</a> <b><i> * A. If average delay is at minimum (we are uncongested),</i></b>
<a name="L132" href="source/net/ipv4/tcp_illinois.c#L132">132</a> <b><i> *    then use large alpha (10.0) to increase faster.</i></b>
<a name="L133" href="source/net/ipv4/tcp_illinois.c#L133">133</a> <b><i> * B. If average delay is at maximum (getting congested)</i></b>
<a name="L134" href="source/net/ipv4/tcp_illinois.c#L134">134</a> <b><i> *    then use small alpha (0.3)</i></b>
<a name="L135" href="source/net/ipv4/tcp_illinois.c#L135">135</a> <b><i> *</i></b>
<a name="L136" href="source/net/ipv4/tcp_illinois.c#L136">136</a> <b><i> * The result is a convex window growth curve.</i></b>
<a name="L137" href="source/net/ipv4/tcp_illinois.c#L137">137</a> <b><i> */</i></b>
<a name="L138" href="source/net/ipv4/tcp_illinois.c#L138">138</a> static <a href="ident?i=u32">u32</a> <a href="ident?i=alpha">alpha</a>(struct <a href="ident?i=illinois">illinois</a> *<a href="ident?i=ca">ca</a>, <a href="ident?i=u32">u32</a> <a href="ident?i=da">da</a>, <a href="ident?i=u32">u32</a> dm)
<a name="L139" href="source/net/ipv4/tcp_illinois.c#L139">139</a> {
<a name="L140" href="source/net/ipv4/tcp_illinois.c#L140">140</a>         <a href="ident?i=u32">u32</a> <a href="ident?i=d1">d1</a> = dm / 100;      <b><i>/* Low threshold */</i></b>
<a name="L141" href="source/net/ipv4/tcp_illinois.c#L141">141</a> 
<a name="L142" href="source/net/ipv4/tcp_illinois.c#L142">142</a>         if (<a href="ident?i=da">da</a> &lt;= <a href="ident?i=d1">d1</a>) {
<a name="L143" href="source/net/ipv4/tcp_illinois.c#L143">143</a>                 <b><i>/* If never got out of low delay zone, then use max */</i></b>
<a name="L144" href="source/net/ipv4/tcp_illinois.c#L144">144</a>                 if (!<a href="ident?i=ca">ca</a>-&gt;rtt_above)
<a name="L145" href="source/net/ipv4/tcp_illinois.c#L145">145</a>                         return <a href="ident?i=ALPHA_MAX">ALPHA_MAX</a>;
<a name="L146" href="source/net/ipv4/tcp_illinois.c#L146">146</a> 
<a name="L147" href="source/net/ipv4/tcp_illinois.c#L147">147</a>                 <b><i>/* Wait for 5 good RTT's before allowing alpha to go alpha max.</i></b>
<a name="L148" href="source/net/ipv4/tcp_illinois.c#L148">148</a> <b><i>                 * This prevents one good RTT from causing sudden window increase.</i></b>
<a name="L149" href="source/net/ipv4/tcp_illinois.c#L149">149</a> <b><i>                 */</i></b>
<a name="L150" href="source/net/ipv4/tcp_illinois.c#L150">150</a>                 if (++<a href="ident?i=ca">ca</a>-&gt;rtt_low &lt; theta)
<a name="L151" href="source/net/ipv4/tcp_illinois.c#L151">151</a>                         return <a href="ident?i=ca">ca</a>-&gt;<a href="ident?i=alpha">alpha</a>;
<a name="L152" href="source/net/ipv4/tcp_illinois.c#L152">152</a> 
<a name="L153" href="source/net/ipv4/tcp_illinois.c#L153">153</a>                 <a href="ident?i=ca">ca</a>-&gt;rtt_low = 0;
<a name="L154" href="source/net/ipv4/tcp_illinois.c#L154">154</a>                 <a href="ident?i=ca">ca</a>-&gt;rtt_above = 0;
<a name="L155" href="source/net/ipv4/tcp_illinois.c#L155">155</a>                 return <a href="ident?i=ALPHA_MAX">ALPHA_MAX</a>;
<a name="L156" href="source/net/ipv4/tcp_illinois.c#L156">156</a>         }
<a name="L157" href="source/net/ipv4/tcp_illinois.c#L157">157</a> 
<a name="L158" href="source/net/ipv4/tcp_illinois.c#L158">158</a>         <a href="ident?i=ca">ca</a>-&gt;rtt_above = 1;
<a name="L159" href="source/net/ipv4/tcp_illinois.c#L159">159</a> 
<a name="L160" href="source/net/ipv4/tcp_illinois.c#L160">160</a>         <b><i>/*</i></b>
<a name="L161" href="source/net/ipv4/tcp_illinois.c#L161">161</a> <b><i>         * Based on:</i></b>
<a name="L162" href="source/net/ipv4/tcp_illinois.c#L162">162</a> <b><i>         *</i></b>
<a name="L163" href="source/net/ipv4/tcp_illinois.c#L163">163</a> <b><i>         *      (dm - d1) amin amax</i></b>
<a name="L164" href="source/net/ipv4/tcp_illinois.c#L164">164</a> <b><i>         * k1 = -------------------</i></b>
<a name="L165" href="source/net/ipv4/tcp_illinois.c#L165">165</a> <b><i>         *         amax - amin</i></b>
<a name="L166" href="source/net/ipv4/tcp_illinois.c#L166">166</a> <b><i>         *</i></b>
<a name="L167" href="source/net/ipv4/tcp_illinois.c#L167">167</a> <b><i>         *       (dm - d1) amin</i></b>
<a name="L168" href="source/net/ipv4/tcp_illinois.c#L168">168</a> <b><i>         * k2 = ----------------  - d1</i></b>
<a name="L169" href="source/net/ipv4/tcp_illinois.c#L169">169</a> <b><i>         *        amax - amin</i></b>
<a name="L170" href="source/net/ipv4/tcp_illinois.c#L170">170</a> <b><i>         *</i></b>
<a name="L171" href="source/net/ipv4/tcp_illinois.c#L171">171</a> <b><i>         *             k1</i></b>
<a name="L172" href="source/net/ipv4/tcp_illinois.c#L172">172</a> <b><i>         * alpha = ----------</i></b>
<a name="L173" href="source/net/ipv4/tcp_illinois.c#L173">173</a> <b><i>         *          k2 + da</i></b>
<a name="L174" href="source/net/ipv4/tcp_illinois.c#L174">174</a> <b><i>         */</i></b>
<a name="L175" href="source/net/ipv4/tcp_illinois.c#L175">175</a> 
<a name="L176" href="source/net/ipv4/tcp_illinois.c#L176">176</a>         dm -= <a href="ident?i=d1">d1</a>;
<a name="L177" href="source/net/ipv4/tcp_illinois.c#L177">177</a>         <a href="ident?i=da">da</a> -= <a href="ident?i=d1">d1</a>;
<a name="L178" href="source/net/ipv4/tcp_illinois.c#L178">178</a>         return (dm * <a href="ident?i=ALPHA_MAX">ALPHA_MAX</a>) /
<a name="L179" href="source/net/ipv4/tcp_illinois.c#L179">179</a>                 (dm + (<a href="ident?i=da">da</a>  * (<a href="ident?i=ALPHA_MAX">ALPHA_MAX</a> - <a href="ident?i=ALPHA_MIN">ALPHA_MIN</a>)) / <a href="ident?i=ALPHA_MIN">ALPHA_MIN</a>);
<a name="L180" href="source/net/ipv4/tcp_illinois.c#L180">180</a> }
<a name="L181" href="source/net/ipv4/tcp_illinois.c#L181">181</a> 
<a name="L182" href="source/net/ipv4/tcp_illinois.c#L182">182</a> <b><i>/*</i></b>
<a name="L183" href="source/net/ipv4/tcp_illinois.c#L183">183</a> <b><i> * Beta used for multiplicative decrease.</i></b>
<a name="L184" href="source/net/ipv4/tcp_illinois.c#L184">184</a> <b><i> * For small window sizes returns same value as Reno (0.5)</i></b>
<a name="L185" href="source/net/ipv4/tcp_illinois.c#L185">185</a> <b><i> *</i></b>
<a name="L186" href="source/net/ipv4/tcp_illinois.c#L186">186</a> <b><i> * If delay is small (10% of max) then beta = 1/8</i></b>
<a name="L187" href="source/net/ipv4/tcp_illinois.c#L187">187</a> <b><i> * If delay is up to 80% of max then beta = 1/2</i></b>
<a name="L188" href="source/net/ipv4/tcp_illinois.c#L188">188</a> <b><i> * In between is a linear function</i></b>
<a name="L189" href="source/net/ipv4/tcp_illinois.c#L189">189</a> <b><i> */</i></b>
<a name="L190" href="source/net/ipv4/tcp_illinois.c#L190">190</a> static <a href="ident?i=u32">u32</a> <a href="ident?i=beta">beta</a>(<a href="ident?i=u32">u32</a> <a href="ident?i=da">da</a>, <a href="ident?i=u32">u32</a> dm)
<a name="L191" href="source/net/ipv4/tcp_illinois.c#L191">191</a> {
<a name="L192" href="source/net/ipv4/tcp_illinois.c#L192">192</a>         <a href="ident?i=u32">u32</a> <a href="ident?i=d2">d2</a>, d3;
<a name="L193" href="source/net/ipv4/tcp_illinois.c#L193">193</a> 
<a name="L194" href="source/net/ipv4/tcp_illinois.c#L194">194</a>         <a href="ident?i=d2">d2</a> = dm / 10;
<a name="L195" href="source/net/ipv4/tcp_illinois.c#L195">195</a>         if (<a href="ident?i=da">da</a> &lt;= <a href="ident?i=d2">d2</a>)
<a name="L196" href="source/net/ipv4/tcp_illinois.c#L196">196</a>                 return <a href="ident?i=BETA_MIN">BETA_MIN</a>;
<a name="L197" href="source/net/ipv4/tcp_illinois.c#L197">197</a> 
<a name="L198" href="source/net/ipv4/tcp_illinois.c#L198">198</a>         d3 = (8 * dm) / 10;
<a name="L199" href="source/net/ipv4/tcp_illinois.c#L199">199</a>         if (<a href="ident?i=da">da</a> &gt;= d3 || d3 &lt;= <a href="ident?i=d2">d2</a>)
<a name="L200" href="source/net/ipv4/tcp_illinois.c#L200">200</a>                 return <a href="ident?i=BETA_MAX">BETA_MAX</a>;
<a name="L201" href="source/net/ipv4/tcp_illinois.c#L201">201</a> 
<a name="L202" href="source/net/ipv4/tcp_illinois.c#L202">202</a>         <b><i>/*</i></b>
<a name="L203" href="source/net/ipv4/tcp_illinois.c#L203">203</a> <b><i>         * Based on:</i></b>
<a name="L204" href="source/net/ipv4/tcp_illinois.c#L204">204</a> <b><i>         *</i></b>
<a name="L205" href="source/net/ipv4/tcp_illinois.c#L205">205</a> <b><i>         *       bmin d3 - bmax d2</i></b>
<a name="L206" href="source/net/ipv4/tcp_illinois.c#L206">206</a> <b><i>         * k3 = -------------------</i></b>
<a name="L207" href="source/net/ipv4/tcp_illinois.c#L207">207</a> <b><i>         *         d3 - d2</i></b>
<a name="L208" href="source/net/ipv4/tcp_illinois.c#L208">208</a> <b><i>         *</i></b>
<a name="L209" href="source/net/ipv4/tcp_illinois.c#L209">209</a> <b><i>         *       bmax - bmin</i></b>
<a name="L210" href="source/net/ipv4/tcp_illinois.c#L210">210</a> <b><i>         * k4 = -------------</i></b>
<a name="L211" href="source/net/ipv4/tcp_illinois.c#L211">211</a> <b><i>         *         d3 - d2</i></b>
<a name="L212" href="source/net/ipv4/tcp_illinois.c#L212">212</a> <b><i>         *</i></b>
<a name="L213" href="source/net/ipv4/tcp_illinois.c#L213">213</a> <b><i>         * b = k3 + k4 da</i></b>
<a name="L214" href="source/net/ipv4/tcp_illinois.c#L214">214</a> <b><i>         */</i></b>
<a name="L215" href="source/net/ipv4/tcp_illinois.c#L215">215</a>         return (<a href="ident?i=BETA_MIN">BETA_MIN</a> * d3 - <a href="ident?i=BETA_MAX">BETA_MAX</a> * <a href="ident?i=d2">d2</a> + (<a href="ident?i=BETA_MAX">BETA_MAX</a> - <a href="ident?i=BETA_MIN">BETA_MIN</a>) * <a href="ident?i=da">da</a>)
<a name="L216" href="source/net/ipv4/tcp_illinois.c#L216">216</a>                 / (d3 - <a href="ident?i=d2">d2</a>);
<a name="L217" href="source/net/ipv4/tcp_illinois.c#L217">217</a> }
<a name="L218" href="source/net/ipv4/tcp_illinois.c#L218">218</a> 
<a name="L219" href="source/net/ipv4/tcp_illinois.c#L219">219</a> <b><i>/* Update alpha and beta values once per RTT */</i></b>
<a name="L220" href="source/net/ipv4/tcp_illinois.c#L220">220</a> static void <a href="ident?i=update_params">update_params</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L221" href="source/net/ipv4/tcp_illinois.c#L221">221</a> {
<a name="L222" href="source/net/ipv4/tcp_illinois.c#L222">222</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L223" href="source/net/ipv4/tcp_illinois.c#L223">223</a>         struct <a href="ident?i=illinois">illinois</a> *<a href="ident?i=ca">ca</a> = <a href="ident?i=inet_csk_ca">inet_csk_ca</a>(sk);
<a name="L224" href="source/net/ipv4/tcp_illinois.c#L224">224</a> 
<a name="L225" href="source/net/ipv4/tcp_illinois.c#L225">225</a>         if (<a href="ident?i=tp">tp</a>-&gt;snd_cwnd &lt; win_thresh) {
<a name="L226" href="source/net/ipv4/tcp_illinois.c#L226">226</a>                 <a href="ident?i=ca">ca</a>-&gt;<a href="ident?i=alpha">alpha</a> = <a href="ident?i=ALPHA_BASE">ALPHA_BASE</a>;
<a name="L227" href="source/net/ipv4/tcp_illinois.c#L227">227</a>                 <a href="ident?i=ca">ca</a>-&gt;<a href="ident?i=beta">beta</a> = <a href="ident?i=BETA_BASE">BETA_BASE</a>;
<a name="L228" href="source/net/ipv4/tcp_illinois.c#L228">228</a>         } else if (<a href="ident?i=ca">ca</a>-&gt;cnt_rtt &gt; 0) {
<a name="L229" href="source/net/ipv4/tcp_illinois.c#L229">229</a>                 <a href="ident?i=u32">u32</a> dm = <a href="ident?i=max_delay">max_delay</a>(<a href="ident?i=ca">ca</a>);
<a name="L230" href="source/net/ipv4/tcp_illinois.c#L230">230</a>                 <a href="ident?i=u32">u32</a> <a href="ident?i=da">da</a> = <a href="ident?i=avg_delay">avg_delay</a>(<a href="ident?i=ca">ca</a>);
<a name="L231" href="source/net/ipv4/tcp_illinois.c#L231">231</a> 
<a name="L232" href="source/net/ipv4/tcp_illinois.c#L232">232</a>                 <a href="ident?i=ca">ca</a>-&gt;<a href="ident?i=alpha">alpha</a> = <a href="ident?i=alpha">alpha</a>(<a href="ident?i=ca">ca</a>, <a href="ident?i=da">da</a>, dm);
<a name="L233" href="source/net/ipv4/tcp_illinois.c#L233">233</a>                 <a href="ident?i=ca">ca</a>-&gt;<a href="ident?i=beta">beta</a> = <a href="ident?i=beta">beta</a>(<a href="ident?i=da">da</a>, dm);
<a name="L234" href="source/net/ipv4/tcp_illinois.c#L234">234</a>         }
<a name="L235" href="source/net/ipv4/tcp_illinois.c#L235">235</a> 
<a name="L236" href="source/net/ipv4/tcp_illinois.c#L236">236</a>         <a href="ident?i=rtt_reset">rtt_reset</a>(sk);
<a name="L237" href="source/net/ipv4/tcp_illinois.c#L237">237</a> }
<a name="L238" href="source/net/ipv4/tcp_illinois.c#L238">238</a> 
<a name="L239" href="source/net/ipv4/tcp_illinois.c#L239">239</a> <b><i>/*</i></b>
<a name="L240" href="source/net/ipv4/tcp_illinois.c#L240">240</a> <b><i> * In case of loss, reset to default values</i></b>
<a name="L241" href="source/net/ipv4/tcp_illinois.c#L241">241</a> <b><i> */</i></b>
<a name="L242" href="source/net/ipv4/tcp_illinois.c#L242">242</a> static void <a href="ident?i=tcp_illinois_state">tcp_illinois_state</a>(struct <a href="ident?i=sock">sock</a> *sk, <a href="ident?i=u8">u8</a> <a href="ident?i=new_state">new_state</a>)
<a name="L243" href="source/net/ipv4/tcp_illinois.c#L243">243</a> {
<a name="L244" href="source/net/ipv4/tcp_illinois.c#L244">244</a>         struct <a href="ident?i=illinois">illinois</a> *<a href="ident?i=ca">ca</a> = <a href="ident?i=inet_csk_ca">inet_csk_ca</a>(sk);
<a name="L245" href="source/net/ipv4/tcp_illinois.c#L245">245</a> 
<a name="L246" href="source/net/ipv4/tcp_illinois.c#L246">246</a>         if (<a href="ident?i=new_state">new_state</a> == TCP_CA_Loss) {
<a name="L247" href="source/net/ipv4/tcp_illinois.c#L247">247</a>                 <a href="ident?i=ca">ca</a>-&gt;<a href="ident?i=alpha">alpha</a> = <a href="ident?i=ALPHA_BASE">ALPHA_BASE</a>;
<a name="L248" href="source/net/ipv4/tcp_illinois.c#L248">248</a>                 <a href="ident?i=ca">ca</a>-&gt;<a href="ident?i=beta">beta</a> = <a href="ident?i=BETA_BASE">BETA_BASE</a>;
<a name="L249" href="source/net/ipv4/tcp_illinois.c#L249">249</a>                 <a href="ident?i=ca">ca</a>-&gt;rtt_low = 0;
<a name="L250" href="source/net/ipv4/tcp_illinois.c#L250">250</a>                 <a href="ident?i=ca">ca</a>-&gt;rtt_above = 0;
<a name="L251" href="source/net/ipv4/tcp_illinois.c#L251">251</a>                 <a href="ident?i=rtt_reset">rtt_reset</a>(sk);
<a name="L252" href="source/net/ipv4/tcp_illinois.c#L252">252</a>         }
<a name="L253" href="source/net/ipv4/tcp_illinois.c#L253">253</a> }
<a name="L254" href="source/net/ipv4/tcp_illinois.c#L254">254</a> 
<a name="L255" href="source/net/ipv4/tcp_illinois.c#L255">255</a> <b><i>/*</i></b>
<a name="L256" href="source/net/ipv4/tcp_illinois.c#L256">256</a> <b><i> * Increase window in response to successful acknowledgment.</i></b>
<a name="L257" href="source/net/ipv4/tcp_illinois.c#L257">257</a> <b><i> */</i></b>
<a name="L258" href="source/net/ipv4/tcp_illinois.c#L258">258</a> static void <a href="ident?i=tcp_illinois_cong_avoid">tcp_illinois_cong_avoid</a>(struct <a href="ident?i=sock">sock</a> *sk, <a href="ident?i=u32">u32</a> ack, <a href="ident?i=u32">u32</a> acked)
<a name="L259" href="source/net/ipv4/tcp_illinois.c#L259">259</a> {
<a name="L260" href="source/net/ipv4/tcp_illinois.c#L260">260</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L261" href="source/net/ipv4/tcp_illinois.c#L261">261</a>         struct <a href="ident?i=illinois">illinois</a> *<a href="ident?i=ca">ca</a> = <a href="ident?i=inet_csk_ca">inet_csk_ca</a>(sk);
<a name="L262" href="source/net/ipv4/tcp_illinois.c#L262">262</a> 
<a name="L263" href="source/net/ipv4/tcp_illinois.c#L263">263</a>         if (<a href="ident?i=after">after</a>(ack, <a href="ident?i=ca">ca</a>-&gt;end_seq))
<a name="L264" href="source/net/ipv4/tcp_illinois.c#L264">264</a>                 <a href="ident?i=update_params">update_params</a>(sk);
<a name="L265" href="source/net/ipv4/tcp_illinois.c#L265">265</a> 
<a name="L266" href="source/net/ipv4/tcp_illinois.c#L266">266</a>         <b><i>/* RFC2861 only increase cwnd if fully utilized */</i></b>
<a name="L267" href="source/net/ipv4/tcp_illinois.c#L267">267</a>         if (!<a href="ident?i=tcp_is_cwnd_limited">tcp_is_cwnd_limited</a>(sk))
<a name="L268" href="source/net/ipv4/tcp_illinois.c#L268">268</a>                 return;
<a name="L269" href="source/net/ipv4/tcp_illinois.c#L269">269</a> 
<a name="L270" href="source/net/ipv4/tcp_illinois.c#L270">270</a>         <b><i>/* In slow start */</i></b>
<a name="L271" href="source/net/ipv4/tcp_illinois.c#L271">271</a>         if (<a href="ident?i=tp">tp</a>-&gt;snd_cwnd &lt;= <a href="ident?i=tp">tp</a>-&gt;snd_ssthresh)
<a name="L272" href="source/net/ipv4/tcp_illinois.c#L272">272</a>                 <a href="ident?i=tcp_slow_start">tcp_slow_start</a>(<a href="ident?i=tp">tp</a>, acked);
<a name="L273" href="source/net/ipv4/tcp_illinois.c#L273">273</a> 
<a name="L274" href="source/net/ipv4/tcp_illinois.c#L274">274</a>         else {
<a name="L275" href="source/net/ipv4/tcp_illinois.c#L275">275</a>                 <a href="ident?i=u32">u32</a> <a href="ident?i=delta">delta</a>;
<a name="L276" href="source/net/ipv4/tcp_illinois.c#L276">276</a> 
<a name="L277" href="source/net/ipv4/tcp_illinois.c#L277">277</a>                 <b><i>/* snd_cwnd_cnt is # of packets since last cwnd increment */</i></b>
<a name="L278" href="source/net/ipv4/tcp_illinois.c#L278">278</a>                 <a href="ident?i=tp">tp</a>-&gt;snd_cwnd_cnt += <a href="ident?i=ca">ca</a>-&gt;acked;
<a name="L279" href="source/net/ipv4/tcp_illinois.c#L279">279</a>                 <a href="ident?i=ca">ca</a>-&gt;acked = 1;
<a name="L280" href="source/net/ipv4/tcp_illinois.c#L280">280</a> 
<a name="L281" href="source/net/ipv4/tcp_illinois.c#L281">281</a>                 <b><i>/* This is close approximation of:</i></b>
<a name="L282" href="source/net/ipv4/tcp_illinois.c#L282">282</a> <b><i>                 * tp-&gt;snd_cwnd += alpha/tp-&gt;snd_cwnd</i></b>
<a name="L283" href="source/net/ipv4/tcp_illinois.c#L283">283</a> <b><i>                */</i></b>
<a name="L284" href="source/net/ipv4/tcp_illinois.c#L284">284</a>                 <a href="ident?i=delta">delta</a> = (<a href="ident?i=tp">tp</a>-&gt;snd_cwnd_cnt * <a href="ident?i=ca">ca</a>-&gt;<a href="ident?i=alpha">alpha</a>) &gt;&gt; <a href="ident?i=ALPHA_SHIFT">ALPHA_SHIFT</a>;
<a name="L285" href="source/net/ipv4/tcp_illinois.c#L285">285</a>                 if (<a href="ident?i=delta">delta</a> &gt;= <a href="ident?i=tp">tp</a>-&gt;snd_cwnd) {
<a name="L286" href="source/net/ipv4/tcp_illinois.c#L286">286</a>                         <a href="ident?i=tp">tp</a>-&gt;snd_cwnd = <a href="ident?i=min">min</a>(<a href="ident?i=tp">tp</a>-&gt;snd_cwnd + <a href="ident?i=delta">delta</a> / <a href="ident?i=tp">tp</a>-&gt;snd_cwnd,
<a name="L287" href="source/net/ipv4/tcp_illinois.c#L287">287</a>                                            (<a href="ident?i=u32">u32</a>)<a href="ident?i=tp">tp</a>-&gt;snd_cwnd_clamp);
<a name="L288" href="source/net/ipv4/tcp_illinois.c#L288">288</a>                         <a href="ident?i=tp">tp</a>-&gt;snd_cwnd_cnt = 0;
<a name="L289" href="source/net/ipv4/tcp_illinois.c#L289">289</a>                 }
<a name="L290" href="source/net/ipv4/tcp_illinois.c#L290">290</a>         }
<a name="L291" href="source/net/ipv4/tcp_illinois.c#L291">291</a> }
<a name="L292" href="source/net/ipv4/tcp_illinois.c#L292">292</a> 
<a name="L293" href="source/net/ipv4/tcp_illinois.c#L293">293</a> static <a href="ident?i=u32">u32</a> <a href="ident?i=tcp_illinois_ssthresh">tcp_illinois_ssthresh</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L294" href="source/net/ipv4/tcp_illinois.c#L294">294</a> {
<a name="L295" href="source/net/ipv4/tcp_illinois.c#L295">295</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L296" href="source/net/ipv4/tcp_illinois.c#L296">296</a>         struct <a href="ident?i=illinois">illinois</a> *<a href="ident?i=ca">ca</a> = <a href="ident?i=inet_csk_ca">inet_csk_ca</a>(sk);
<a name="L297" href="source/net/ipv4/tcp_illinois.c#L297">297</a> 
<a name="L298" href="source/net/ipv4/tcp_illinois.c#L298">298</a>         <b><i>/* Multiplicative decrease */</i></b>
<a name="L299" href="source/net/ipv4/tcp_illinois.c#L299">299</a>         return <a href="ident?i=max">max</a>(<a href="ident?i=tp">tp</a>-&gt;snd_cwnd - ((<a href="ident?i=tp">tp</a>-&gt;snd_cwnd * <a href="ident?i=ca">ca</a>-&gt;<a href="ident?i=beta">beta</a>) &gt;&gt; <a href="ident?i=BETA_SHIFT">BETA_SHIFT</a>), 2U);
<a name="L300" href="source/net/ipv4/tcp_illinois.c#L300">300</a> }
<a name="L301" href="source/net/ipv4/tcp_illinois.c#L301">301</a> 
<a name="L302" href="source/net/ipv4/tcp_illinois.c#L302">302</a> <b><i>/* Extract info for Tcp socket info provided via netlink. */</i></b>
<a name="L303" href="source/net/ipv4/tcp_illinois.c#L303">303</a> static <a href="ident?i=size_t">size_t</a> <a href="ident?i=tcp_illinois_info">tcp_illinois_info</a>(struct <a href="ident?i=sock">sock</a> *sk, <a href="ident?i=u32">u32</a> ext, int *<a href="ident?i=attr">attr</a>,
<a name="L304" href="source/net/ipv4/tcp_illinois.c#L304">304</a>                                 union <a href="ident?i=tcp_cc_info">tcp_cc_info</a> *<a href="ident?i=info">info</a>)
<a name="L305" href="source/net/ipv4/tcp_illinois.c#L305">305</a> {
<a name="L306" href="source/net/ipv4/tcp_illinois.c#L306">306</a>         const struct <a href="ident?i=illinois">illinois</a> *<a href="ident?i=ca">ca</a> = <a href="ident?i=inet_csk_ca">inet_csk_ca</a>(sk);
<a name="L307" href="source/net/ipv4/tcp_illinois.c#L307">307</a> 
<a name="L308" href="source/net/ipv4/tcp_illinois.c#L308">308</a>         if (ext &amp; (1 &lt;&lt; (INET_DIAG_VEGASINFO - 1))) {
<a name="L309" href="source/net/ipv4/tcp_illinois.c#L309">309</a>                 <a href="ident?i=info">info</a>-&gt;<a href="ident?i=vegas">vegas</a>.tcpv_enabled = 1;
<a name="L310" href="source/net/ipv4/tcp_illinois.c#L310">310</a>                 <a href="ident?i=info">info</a>-&gt;<a href="ident?i=vegas">vegas</a>.tcpv_rttcnt = <a href="ident?i=ca">ca</a>-&gt;cnt_rtt;
<a name="L311" href="source/net/ipv4/tcp_illinois.c#L311">311</a>                 <a href="ident?i=info">info</a>-&gt;<a href="ident?i=vegas">vegas</a>.tcpv_minrtt = <a href="ident?i=ca">ca</a>-&gt;base_rtt;
<a name="L312" href="source/net/ipv4/tcp_illinois.c#L312">312</a>                 <a href="ident?i=info">info</a>-&gt;<a href="ident?i=vegas">vegas</a>.tcpv_rtt = 0;
<a name="L313" href="source/net/ipv4/tcp_illinois.c#L313">313</a> 
<a name="L314" href="source/net/ipv4/tcp_illinois.c#L314">314</a>                 if (<a href="ident?i=info">info</a>-&gt;<a href="ident?i=vegas">vegas</a>.tcpv_rttcnt &gt; 0) {
<a name="L315" href="source/net/ipv4/tcp_illinois.c#L315">315</a>                         <a href="ident?i=u64">u64</a> <a href="ident?i=t">t</a> = <a href="ident?i=ca">ca</a>-&gt;sum_rtt;
<a name="L316" href="source/net/ipv4/tcp_illinois.c#L316">316</a> 
<a name="L317" href="source/net/ipv4/tcp_illinois.c#L317">317</a>                         <a href="ident?i=do_div">do_div</a>(<a href="ident?i=t">t</a>, <a href="ident?i=info">info</a>-&gt;<a href="ident?i=vegas">vegas</a>.tcpv_rttcnt);
<a name="L318" href="source/net/ipv4/tcp_illinois.c#L318">318</a>                         <a href="ident?i=info">info</a>-&gt;<a href="ident?i=vegas">vegas</a>.tcpv_rtt = <a href="ident?i=t">t</a>;
<a name="L319" href="source/net/ipv4/tcp_illinois.c#L319">319</a>                 }
<a name="L320" href="source/net/ipv4/tcp_illinois.c#L320">320</a>                 *<a href="ident?i=attr">attr</a> = INET_DIAG_VEGASINFO;
<a name="L321" href="source/net/ipv4/tcp_illinois.c#L321">321</a>                 return sizeof(struct <a href="ident?i=tcpvegas_info">tcpvegas_info</a>);
<a name="L322" href="source/net/ipv4/tcp_illinois.c#L322">322</a>         }
<a name="L323" href="source/net/ipv4/tcp_illinois.c#L323">323</a>         return 0;
<a name="L324" href="source/net/ipv4/tcp_illinois.c#L324">324</a> }
<a name="L325" href="source/net/ipv4/tcp_illinois.c#L325">325</a> 
<a name="L326" href="source/net/ipv4/tcp_illinois.c#L326">326</a> static struct <a href="ident?i=tcp_congestion_ops">tcp_congestion_ops</a> tcp_illinois <a href="ident?i=__read_mostly">__read_mostly</a> = {
<a name="L327" href="source/net/ipv4/tcp_illinois.c#L327">327</a>         .<a href="ident?i=init">init</a>           = <a href="ident?i=tcp_illinois_init">tcp_illinois_init</a>,
<a name="L328" href="source/net/ipv4/tcp_illinois.c#L328">328</a>         .ssthresh       = <a href="ident?i=tcp_illinois_ssthresh">tcp_illinois_ssthresh</a>,
<a name="L329" href="source/net/ipv4/tcp_illinois.c#L329">329</a>         .cong_avoid     = <a href="ident?i=tcp_illinois_cong_avoid">tcp_illinois_cong_avoid</a>,
<a name="L330" href="source/net/ipv4/tcp_illinois.c#L330">330</a>         .<a href="ident?i=set_state">set_state</a>      = <a href="ident?i=tcp_illinois_state">tcp_illinois_state</a>,
<a name="L331" href="source/net/ipv4/tcp_illinois.c#L331">331</a>         .<a href="ident?i=get_info">get_info</a>       = <a href="ident?i=tcp_illinois_info">tcp_illinois_info</a>,
<a name="L332" href="source/net/ipv4/tcp_illinois.c#L332">332</a>         .pkts_acked     = <a href="ident?i=tcp_illinois_acked">tcp_illinois_acked</a>,
<a name="L333" href="source/net/ipv4/tcp_illinois.c#L333">333</a> 
<a name="L334" href="source/net/ipv4/tcp_illinois.c#L334">334</a>         .owner          = <a href="ident?i=THIS_MODULE">THIS_MODULE</a>,
<a name="L335" href="source/net/ipv4/tcp_illinois.c#L335">335</a>         .<a href="ident?i=name">name</a>           = <i>"illinois"</i>,
<a name="L336" href="source/net/ipv4/tcp_illinois.c#L336">336</a> };
<a name="L337" href="source/net/ipv4/tcp_illinois.c#L337">337</a> 
<a name="L338" href="source/net/ipv4/tcp_illinois.c#L338">338</a> static int <a href="ident?i=__init">__init</a> <a href="ident?i=tcp_illinois_register">tcp_illinois_register</a>(void)
<a name="L339" href="source/net/ipv4/tcp_illinois.c#L339">339</a> {
<a name="L340" href="source/net/ipv4/tcp_illinois.c#L340">340</a>         <a href="ident?i=BUILD_BUG_ON">BUILD_BUG_ON</a>(sizeof(struct <a href="ident?i=illinois">illinois</a>) &gt; <a href="ident?i=ICSK_CA_PRIV_SIZE">ICSK_CA_PRIV_SIZE</a>);
<a name="L341" href="source/net/ipv4/tcp_illinois.c#L341">341</a>         return <a href="ident?i=tcp_register_congestion_control">tcp_register_congestion_control</a>(&amp;tcp_illinois);
<a name="L342" href="source/net/ipv4/tcp_illinois.c#L342">342</a> }
<a name="L343" href="source/net/ipv4/tcp_illinois.c#L343">343</a> 
<a name="L344" href="source/net/ipv4/tcp_illinois.c#L344">344</a> static void <a href="ident?i=__exit">__exit</a> <a href="ident?i=tcp_illinois_unregister">tcp_illinois_unregister</a>(void)
<a name="L345" href="source/net/ipv4/tcp_illinois.c#L345">345</a> {
<a name="L346" href="source/net/ipv4/tcp_illinois.c#L346">346</a>         <a href="ident?i=tcp_unregister_congestion_control">tcp_unregister_congestion_control</a>(&amp;tcp_illinois);
<a name="L347" href="source/net/ipv4/tcp_illinois.c#L347">347</a> }
<a name="L348" href="source/net/ipv4/tcp_illinois.c#L348">348</a> 
<a name="L349" href="source/net/ipv4/tcp_illinois.c#L349">349</a> <a href="ident?i=module_init">module_init</a>(<a href="ident?i=tcp_illinois_register">tcp_illinois_register</a>);
<a name="L350" href="source/net/ipv4/tcp_illinois.c#L350">350</a> <a href="ident?i=module_exit">module_exit</a>(<a href="ident?i=tcp_illinois_unregister">tcp_illinois_unregister</a>);
<a name="L351" href="source/net/ipv4/tcp_illinois.c#L351">351</a> 
<a name="L352" href="source/net/ipv4/tcp_illinois.c#L352">352</a> <a href="ident?i=MODULE_AUTHOR">MODULE_AUTHOR</a>(<i>"Stephen Hemminger, Shao Liu"</i>);
<a name="L353" href="source/net/ipv4/tcp_illinois.c#L353">353</a> <a href="ident?i=MODULE_LICENSE">MODULE_LICENSE</a>(<i>"GPL"</i>);
<a name="L354" href="source/net/ipv4/tcp_illinois.c#L354">354</a> <a href="ident?i=MODULE_DESCRIPTION">MODULE_DESCRIPTION</a>(<i>"TCP Illinois"</i>);
<a name="L355" href="source/net/ipv4/tcp_illinois.c#L355">355</a> <a href="ident?i=MODULE_VERSION">MODULE_VERSION</a>(<i>"1.0"</i>);
<a name="L356" href="source/net/ipv4/tcp_illinois.c#L356">356</a> </pre></div><p>
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
