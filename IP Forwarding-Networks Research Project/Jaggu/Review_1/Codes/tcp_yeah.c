<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title>Linux/net/ipv4/tcp_yeah.c - Linux Cross Reference - Free Electrons</title>
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
		 &nbsp;&bull;&nbsp;<b><i>source navigation</i></b> &nbsp;&bull;&nbsp;<a href="diff/net/ipv4/tcp_yeah.c">diff markup</a> &nbsp;&bull;&nbsp;<a href="ident">identifier search</a> &nbsp;&bull;&nbsp;<a href="search">freetext search</a> &nbsp;&bull;&nbsp;
		</p>
	</div>
</div>

<div id="topbar">
  
  <p>Version: &nbsp;<a href="source/net/ipv4/tcp_yeah.c?v=2.0.40">2.0.40</a>&nbsp;<a href="source/net/ipv4/tcp_yeah.c?v=2.2.26">2.2.26</a>&nbsp;<a href="source/net/ipv4/tcp_yeah.c?v=2.4.37">2.4.37</a>&nbsp;<a href="source/net/ipv4/tcp_yeah.c?v=3.5">3.5</a>&nbsp;<a href="source/net/ipv4/tcp_yeah.c?v=3.6">3.6</a>&nbsp;<a href="source/net/ipv4/tcp_yeah.c?v=3.7">3.7</a>&nbsp;<a href="source/net/ipv4/tcp_yeah.c?v=3.8">3.8</a>&nbsp;<a href="source/net/ipv4/tcp_yeah.c?v=3.9">3.9</a>&nbsp;<a href="source/net/ipv4/tcp_yeah.c?v=3.10">3.10</a>&nbsp;<a href="source/net/ipv4/tcp_yeah.c?v=3.11">3.11</a>&nbsp;<a href="source/net/ipv4/tcp_yeah.c?v=3.12">3.12</a>&nbsp;<a href="source/net/ipv4/tcp_yeah.c?v=3.13">3.13</a>&nbsp;<a href="source/net/ipv4/tcp_yeah.c?v=3.14">3.14</a>&nbsp;<a href="source/net/ipv4/tcp_yeah.c?v=3.15">3.15</a>&nbsp;<a href="source/net/ipv4/tcp_yeah.c?v=3.16">3.16</a>&nbsp;<a href="source/net/ipv4/tcp_yeah.c?v=3.17">3.17</a>&nbsp;<a href="source/net/ipv4/tcp_yeah.c?v=3.18">3.18</a>&nbsp;<a href="source/net/ipv4/tcp_yeah.c?v=3.19">3.19</a>&nbsp;<a href="source/net/ipv4/tcp_yeah.c?v=4.0">4.0</a>&nbsp;<b><i>4.1</i></b></p>
  
</div>

<h1><a href="source/">Linux</a>/<a href="source/net/">net</a>/<a href="source/net/ipv4/">ipv4</a>/<a href="source/net/ipv4/tcp_yeah.c">tcp_yeah.c</a></h1>
<div id="lxrcode"><pre>  <a name="L1" href="source/net/ipv4/tcp_yeah.c#L1">1</a> <b><i>/*</i></b>
  <a name="L2" href="source/net/ipv4/tcp_yeah.c#L2">2</a> <b><i> *</i></b>
  <a name="L3" href="source/net/ipv4/tcp_yeah.c#L3">3</a> <b><i> *   YeAH TCP</i></b>
  <a name="L4" href="source/net/ipv4/tcp_yeah.c#L4">4</a> <b><i> *</i></b>
  <a name="L5" href="source/net/ipv4/tcp_yeah.c#L5">5</a> <b><i> * For further details look at:</i></b>
  <a name="L6" href="source/net/ipv4/tcp_yeah.c#L6">6</a> <b><i> *   https://web.archive.org/web/20080316215752/<a href="http://wil.cs.caltech.edu/pfldnet2007/paper/YeAH_TCP.pdf">http://wil.cs.caltech.edu/pfldnet2007/paper/YeAH_TCP.pdf</a></i></b>
  <a name="L7" href="source/net/ipv4/tcp_yeah.c#L7">7</a> <b><i> *</i></b>
  <a name="L8" href="source/net/ipv4/tcp_yeah.c#L8">8</a> <b><i> */</i></b>
  <a name="L9" href="source/net/ipv4/tcp_yeah.c#L9">9</a> #include &lt;linux/mm.h&gt;
 <a name="L10" href="source/net/ipv4/tcp_yeah.c#L10">10</a> #include &lt;linux/module.h&gt;
 <a name="L11" href="source/net/ipv4/tcp_yeah.c#L11">11</a> #include &lt;linux/skbuff.h&gt;
 <a name="L12" href="source/net/ipv4/tcp_yeah.c#L12">12</a> #include &lt;linux/inet_diag.h&gt;
 <a name="L13" href="source/net/ipv4/tcp_yeah.c#L13">13</a> 
 <a name="L14" href="source/net/ipv4/tcp_yeah.c#L14">14</a> #include &lt;net/tcp.h&gt;
 <a name="L15" href="source/net/ipv4/tcp_yeah.c#L15">15</a> 
 <a name="L16" href="source/net/ipv4/tcp_yeah.c#L16">16</a> #include "<a href="source/net/ipv4/tcp_vegas.h">tcp_vegas.h</a>"
 <a name="L17" href="source/net/ipv4/tcp_yeah.c#L17">17</a> 
 <a name="L18" href="source/net/ipv4/tcp_yeah.c#L18">18</a> #define <a href="ident?i=TCP_YEAH_ALPHA">TCP_YEAH_ALPHA</a>       80 <b><i>/* number of packets queued at the bottleneck */</i></b>
 <a name="L19" href="source/net/ipv4/tcp_yeah.c#L19">19</a> #define <a href="ident?i=TCP_YEAH_GAMMA">TCP_YEAH_GAMMA</a>        1 <b><i>/* fraction of queue to be removed per rtt */</i></b>
 <a name="L20" href="source/net/ipv4/tcp_yeah.c#L20">20</a> #define <a href="ident?i=TCP_YEAH_DELTA">TCP_YEAH_DELTA</a>        3 <b><i>/* log minimum fraction of cwnd to be removed on loss */</i></b>
 <a name="L21" href="source/net/ipv4/tcp_yeah.c#L21">21</a> #define <a href="ident?i=TCP_YEAH_EPSILON">TCP_YEAH_EPSILON</a>      1 <b><i>/* log maximum fraction to be removed on early decongestion */</i></b>
 <a name="L22" href="source/net/ipv4/tcp_yeah.c#L22">22</a> #define <a href="ident?i=TCP_YEAH_PHY">TCP_YEAH_PHY</a>          8 <b><i>/* maximum delta from base */</i></b>
 <a name="L23" href="source/net/ipv4/tcp_yeah.c#L23">23</a> #define <a href="ident?i=TCP_YEAH_RHO">TCP_YEAH_RHO</a>         16 <b><i>/* minimum number of consecutive rtt to consider competition on loss */</i></b>
 <a name="L24" href="source/net/ipv4/tcp_yeah.c#L24">24</a> #define <a href="ident?i=TCP_YEAH_ZETA">TCP_YEAH_ZETA</a>        50 <b><i>/* minimum number of state switches to reset reno_count */</i></b>
 <a name="L25" href="source/net/ipv4/tcp_yeah.c#L25">25</a> 
 <a name="L26" href="source/net/ipv4/tcp_yeah.c#L26">26</a> #define <a href="ident?i=TCP_SCALABLE_AI_CNT">TCP_SCALABLE_AI_CNT</a>      100U
 <a name="L27" href="source/net/ipv4/tcp_yeah.c#L27">27</a> 
 <a name="L28" href="source/net/ipv4/tcp_yeah.c#L28">28</a> <b><i>/* YeAH variables */</i></b>
 <a name="L29" href="source/net/ipv4/tcp_yeah.c#L29">29</a> struct <a href="ident?i=yeah">yeah</a> {
 <a name="L30" href="source/net/ipv4/tcp_yeah.c#L30">30</a>         struct <a href="ident?i=vegas">vegas</a> <a href="ident?i=vegas">vegas</a>;     <b><i>/* must be first */</i></b>
 <a name="L31" href="source/net/ipv4/tcp_yeah.c#L31">31</a> 
 <a name="L32" href="source/net/ipv4/tcp_yeah.c#L32">32</a>         <b><i>/* YeAH */</i></b>
 <a name="L33" href="source/net/ipv4/tcp_yeah.c#L33">33</a>         <a href="ident?i=u32">u32</a> lastQ;
 <a name="L34" href="source/net/ipv4/tcp_yeah.c#L34">34</a>         <a href="ident?i=u32">u32</a> doing_reno_now;
 <a name="L35" href="source/net/ipv4/tcp_yeah.c#L35">35</a> 
 <a name="L36" href="source/net/ipv4/tcp_yeah.c#L36">36</a>         <a href="ident?i=u32">u32</a> reno_count;
 <a name="L37" href="source/net/ipv4/tcp_yeah.c#L37">37</a>         <a href="ident?i=u32">u32</a> fast_count;
 <a name="L38" href="source/net/ipv4/tcp_yeah.c#L38">38</a> 
 <a name="L39" href="source/net/ipv4/tcp_yeah.c#L39">39</a>         <a href="ident?i=u32">u32</a> pkts_acked;
 <a name="L40" href="source/net/ipv4/tcp_yeah.c#L40">40</a> };
 <a name="L41" href="source/net/ipv4/tcp_yeah.c#L41">41</a> 
 <a name="L42" href="source/net/ipv4/tcp_yeah.c#L42">42</a> static void <a href="ident?i=tcp_yeah_init">tcp_yeah_init</a>(struct <a href="ident?i=sock">sock</a> *sk)
 <a name="L43" href="source/net/ipv4/tcp_yeah.c#L43">43</a> {
 <a name="L44" href="source/net/ipv4/tcp_yeah.c#L44">44</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
 <a name="L45" href="source/net/ipv4/tcp_yeah.c#L45">45</a>         struct <a href="ident?i=yeah">yeah</a> *<a href="ident?i=yeah">yeah</a> = <a href="ident?i=inet_csk_ca">inet_csk_ca</a>(sk);
 <a name="L46" href="source/net/ipv4/tcp_yeah.c#L46">46</a> 
 <a name="L47" href="source/net/ipv4/tcp_yeah.c#L47">47</a>         <a href="ident?i=tcp_vegas_init">tcp_vegas_init</a>(sk);
 <a name="L48" href="source/net/ipv4/tcp_yeah.c#L48">48</a> 
 <a name="L49" href="source/net/ipv4/tcp_yeah.c#L49">49</a>         <a href="ident?i=yeah">yeah</a>-&gt;doing_reno_now = 0;
 <a name="L50" href="source/net/ipv4/tcp_yeah.c#L50">50</a>         <a href="ident?i=yeah">yeah</a>-&gt;lastQ = 0;
 <a name="L51" href="source/net/ipv4/tcp_yeah.c#L51">51</a> 
 <a name="L52" href="source/net/ipv4/tcp_yeah.c#L52">52</a>         <a href="ident?i=yeah">yeah</a>-&gt;reno_count = 2;
 <a name="L53" href="source/net/ipv4/tcp_yeah.c#L53">53</a> 
 <a name="L54" href="source/net/ipv4/tcp_yeah.c#L54">54</a>         <b><i>/* Ensure the MD arithmetic works.  This is somewhat pedantic,</i></b>
 <a name="L55" href="source/net/ipv4/tcp_yeah.c#L55">55</a> <b><i>         * since I don't think we will see a cwnd this large. :) */</i></b>
 <a name="L56" href="source/net/ipv4/tcp_yeah.c#L56">56</a>         <a href="ident?i=tp">tp</a>-&gt;snd_cwnd_clamp = <a href="ident?i=min_t">min_t</a>(<a href="ident?i=u32">u32</a>, <a href="ident?i=tp">tp</a>-&gt;snd_cwnd_clamp, 0xffffffff/128);
 <a name="L57" href="source/net/ipv4/tcp_yeah.c#L57">57</a> }
 <a name="L58" href="source/net/ipv4/tcp_yeah.c#L58">58</a> 
 <a name="L59" href="source/net/ipv4/tcp_yeah.c#L59">59</a> static void <a href="ident?i=tcp_yeah_pkts_acked">tcp_yeah_pkts_acked</a>(struct <a href="ident?i=sock">sock</a> *sk, <a href="ident?i=u32">u32</a> pkts_acked, <a href="ident?i=s32">s32</a> rtt_us)
 <a name="L60" href="source/net/ipv4/tcp_yeah.c#L60">60</a> {
 <a name="L61" href="source/net/ipv4/tcp_yeah.c#L61">61</a>         const struct <a href="ident?i=inet_connection_sock">inet_connection_sock</a> *icsk = <a href="ident?i=inet_csk">inet_csk</a>(sk);
 <a name="L62" href="source/net/ipv4/tcp_yeah.c#L62">62</a>         struct <a href="ident?i=yeah">yeah</a> *<a href="ident?i=yeah">yeah</a> = <a href="ident?i=inet_csk_ca">inet_csk_ca</a>(sk);
 <a name="L63" href="source/net/ipv4/tcp_yeah.c#L63">63</a> 
 <a name="L64" href="source/net/ipv4/tcp_yeah.c#L64">64</a>         if (icsk-&gt;icsk_ca_state == TCP_CA_Open)
 <a name="L65" href="source/net/ipv4/tcp_yeah.c#L65">65</a>                 <a href="ident?i=yeah">yeah</a>-&gt;pkts_acked = pkts_acked;
 <a name="L66" href="source/net/ipv4/tcp_yeah.c#L66">66</a> 
 <a name="L67" href="source/net/ipv4/tcp_yeah.c#L67">67</a>         <a href="ident?i=tcp_vegas_pkts_acked">tcp_vegas_pkts_acked</a>(sk, pkts_acked, rtt_us);
 <a name="L68" href="source/net/ipv4/tcp_yeah.c#L68">68</a> }
 <a name="L69" href="source/net/ipv4/tcp_yeah.c#L69">69</a> 
 <a name="L70" href="source/net/ipv4/tcp_yeah.c#L70">70</a> static void <a href="ident?i=tcp_yeah_cong_avoid">tcp_yeah_cong_avoid</a>(struct <a href="ident?i=sock">sock</a> *sk, <a href="ident?i=u32">u32</a> ack, <a href="ident?i=u32">u32</a> acked)
 <a name="L71" href="source/net/ipv4/tcp_yeah.c#L71">71</a> {
 <a name="L72" href="source/net/ipv4/tcp_yeah.c#L72">72</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
 <a name="L73" href="source/net/ipv4/tcp_yeah.c#L73">73</a>         struct <a href="ident?i=yeah">yeah</a> *<a href="ident?i=yeah">yeah</a> = <a href="ident?i=inet_csk_ca">inet_csk_ca</a>(sk);
 <a name="L74" href="source/net/ipv4/tcp_yeah.c#L74">74</a> 
 <a name="L75" href="source/net/ipv4/tcp_yeah.c#L75">75</a>         if (!<a href="ident?i=tcp_is_cwnd_limited">tcp_is_cwnd_limited</a>(sk))
 <a name="L76" href="source/net/ipv4/tcp_yeah.c#L76">76</a>                 return;
 <a name="L77" href="source/net/ipv4/tcp_yeah.c#L77">77</a> 
 <a name="L78" href="source/net/ipv4/tcp_yeah.c#L78">78</a>         if (<a href="ident?i=tp">tp</a>-&gt;snd_cwnd &lt;= <a href="ident?i=tp">tp</a>-&gt;snd_ssthresh)
 <a name="L79" href="source/net/ipv4/tcp_yeah.c#L79">79</a>                 <a href="ident?i=tcp_slow_start">tcp_slow_start</a>(<a href="ident?i=tp">tp</a>, acked);
 <a name="L80" href="source/net/ipv4/tcp_yeah.c#L80">80</a> 
 <a name="L81" href="source/net/ipv4/tcp_yeah.c#L81">81</a>         else if (!<a href="ident?i=yeah">yeah</a>-&gt;doing_reno_now) {
 <a name="L82" href="source/net/ipv4/tcp_yeah.c#L82">82</a>                 <b><i>/* Scalable */</i></b>
 <a name="L83" href="source/net/ipv4/tcp_yeah.c#L83">83</a> 
 <a name="L84" href="source/net/ipv4/tcp_yeah.c#L84">84</a>                 <a href="ident?i=tp">tp</a>-&gt;snd_cwnd_cnt += <a href="ident?i=yeah">yeah</a>-&gt;pkts_acked;
 <a name="L85" href="source/net/ipv4/tcp_yeah.c#L85">85</a>                 if (<a href="ident?i=tp">tp</a>-&gt;snd_cwnd_cnt &gt; <a href="ident?i=min">min</a>(<a href="ident?i=tp">tp</a>-&gt;snd_cwnd, <a href="ident?i=TCP_SCALABLE_AI_CNT">TCP_SCALABLE_AI_CNT</a>)) {
 <a name="L86" href="source/net/ipv4/tcp_yeah.c#L86">86</a>                         if (<a href="ident?i=tp">tp</a>-&gt;snd_cwnd &lt; <a href="ident?i=tp">tp</a>-&gt;snd_cwnd_clamp)
 <a name="L87" href="source/net/ipv4/tcp_yeah.c#L87">87</a>                                 <a href="ident?i=tp">tp</a>-&gt;snd_cwnd++;
 <a name="L88" href="source/net/ipv4/tcp_yeah.c#L88">88</a>                         <a href="ident?i=tp">tp</a>-&gt;snd_cwnd_cnt = 0;
 <a name="L89" href="source/net/ipv4/tcp_yeah.c#L89">89</a>                 }
 <a name="L90" href="source/net/ipv4/tcp_yeah.c#L90">90</a> 
 <a name="L91" href="source/net/ipv4/tcp_yeah.c#L91">91</a>                 <a href="ident?i=yeah">yeah</a>-&gt;pkts_acked = 1;
 <a name="L92" href="source/net/ipv4/tcp_yeah.c#L92">92</a> 
 <a name="L93" href="source/net/ipv4/tcp_yeah.c#L93">93</a>         } else {
 <a name="L94" href="source/net/ipv4/tcp_yeah.c#L94">94</a>                 <b><i>/* Reno */</i></b>
 <a name="L95" href="source/net/ipv4/tcp_yeah.c#L95">95</a>                 <a href="ident?i=tcp_cong_avoid_ai">tcp_cong_avoid_ai</a>(<a href="ident?i=tp">tp</a>, <a href="ident?i=tp">tp</a>-&gt;snd_cwnd, 1);
 <a name="L96" href="source/net/ipv4/tcp_yeah.c#L96">96</a>         }
 <a name="L97" href="source/net/ipv4/tcp_yeah.c#L97">97</a> 
 <a name="L98" href="source/net/ipv4/tcp_yeah.c#L98">98</a>         <b><i>/* The key players are v_vegas.beg_snd_una and v_beg_snd_nxt.</i></b>
 <a name="L99" href="source/net/ipv4/tcp_yeah.c#L99">99</a> <b><i>         *</i></b>
<a name="L100" href="source/net/ipv4/tcp_yeah.c#L100">100</a> <b><i>         * These are so named because they represent the approximate values</i></b>
<a name="L101" href="source/net/ipv4/tcp_yeah.c#L101">101</a> <b><i>         * of snd_una and snd_nxt at the beginning of the current RTT. More</i></b>
<a name="L102" href="source/net/ipv4/tcp_yeah.c#L102">102</a> <b><i>         * precisely, they represent the amount of data sent during the RTT.</i></b>
<a name="L103" href="source/net/ipv4/tcp_yeah.c#L103">103</a> <b><i>         * At the end of the RTT, when we receive an ACK for v_beg_snd_nxt,</i></b>
<a name="L104" href="source/net/ipv4/tcp_yeah.c#L104">104</a> <b><i>         * we will calculate that (v_beg_snd_nxt - v_vegas.beg_snd_una) outstanding</i></b>
<a name="L105" href="source/net/ipv4/tcp_yeah.c#L105">105</a> <b><i>         * bytes of data have been ACKed during the course of the RTT, giving</i></b>
<a name="L106" href="source/net/ipv4/tcp_yeah.c#L106">106</a> <b><i>         * an "actual" rate of:</i></b>
<a name="L107" href="source/net/ipv4/tcp_yeah.c#L107">107</a> <b><i>         *</i></b>
<a name="L108" href="source/net/ipv4/tcp_yeah.c#L108">108</a> <b><i>         *     (v_beg_snd_nxt - v_vegas.beg_snd_una) / (rtt duration)</i></b>
<a name="L109" href="source/net/ipv4/tcp_yeah.c#L109">109</a> <b><i>         *</i></b>
<a name="L110" href="source/net/ipv4/tcp_yeah.c#L110">110</a> <b><i>         * Unfortunately, v_vegas.beg_snd_una is not exactly equal to snd_una,</i></b>
<a name="L111" href="source/net/ipv4/tcp_yeah.c#L111">111</a> <b><i>         * because delayed ACKs can cover more than one segment, so they</i></b>
<a name="L112" href="source/net/ipv4/tcp_yeah.c#L112">112</a> <b><i>         * don't line up yeahly with the boundaries of RTTs.</i></b>
<a name="L113" href="source/net/ipv4/tcp_yeah.c#L113">113</a> <b><i>         *</i></b>
<a name="L114" href="source/net/ipv4/tcp_yeah.c#L114">114</a> <b><i>         * Another unfortunate fact of life is that delayed ACKs delay the</i></b>
<a name="L115" href="source/net/ipv4/tcp_yeah.c#L115">115</a> <b><i>         * advance of the left edge of our send window, so that the number</i></b>
<a name="L116" href="source/net/ipv4/tcp_yeah.c#L116">116</a> <b><i>         * of bytes we send in an RTT is often less than our cwnd will allow.</i></b>
<a name="L117" href="source/net/ipv4/tcp_yeah.c#L117">117</a> <b><i>         * So we keep track of our cwnd separately, in v_beg_snd_cwnd.</i></b>
<a name="L118" href="source/net/ipv4/tcp_yeah.c#L118">118</a> <b><i>         */</i></b>
<a name="L119" href="source/net/ipv4/tcp_yeah.c#L119">119</a> 
<a name="L120" href="source/net/ipv4/tcp_yeah.c#L120">120</a>         if (<a href="ident?i=after">after</a>(ack, <a href="ident?i=yeah">yeah</a>-&gt;<a href="ident?i=vegas">vegas</a>.beg_snd_nxt)) {
<a name="L121" href="source/net/ipv4/tcp_yeah.c#L121">121</a>                 <b><i>/* We do the Vegas calculations only if we got enough RTT</i></b>
<a name="L122" href="source/net/ipv4/tcp_yeah.c#L122">122</a> <b><i>                 * samples that we can be reasonably sure that we got</i></b>
<a name="L123" href="source/net/ipv4/tcp_yeah.c#L123">123</a> <b><i>                 * at least one RTT sample that wasn't from a delayed ACK.</i></b>
<a name="L124" href="source/net/ipv4/tcp_yeah.c#L124">124</a> <b><i>                 * If we only had 2 samples total,</i></b>
<a name="L125" href="source/net/ipv4/tcp_yeah.c#L125">125</a> <b><i>                 * then that means we're getting only 1 ACK per RTT, which</i></b>
<a name="L126" href="source/net/ipv4/tcp_yeah.c#L126">126</a> <b><i>                 * means they're almost certainly delayed ACKs.</i></b>
<a name="L127" href="source/net/ipv4/tcp_yeah.c#L127">127</a> <b><i>                 * If  we have 3 samples, we should be OK.</i></b>
<a name="L128" href="source/net/ipv4/tcp_yeah.c#L128">128</a> <b><i>                 */</i></b>
<a name="L129" href="source/net/ipv4/tcp_yeah.c#L129">129</a> 
<a name="L130" href="source/net/ipv4/tcp_yeah.c#L130">130</a>                 if (<a href="ident?i=yeah">yeah</a>-&gt;<a href="ident?i=vegas">vegas</a>.cntRTT &gt; 2) {
<a name="L131" href="source/net/ipv4/tcp_yeah.c#L131">131</a>                         <a href="ident?i=u32">u32</a> rtt, <a href="ident?i=queue">queue</a>;
<a name="L132" href="source/net/ipv4/tcp_yeah.c#L132">132</a>                         <a href="ident?i=u64">u64</a> bw;
<a name="L133" href="source/net/ipv4/tcp_yeah.c#L133">133</a> 
<a name="L134" href="source/net/ipv4/tcp_yeah.c#L134">134</a>                         <b><i>/* We have enough RTT samples, so, using the Vegas</i></b>
<a name="L135" href="source/net/ipv4/tcp_yeah.c#L135">135</a> <b><i>                         * algorithm, we determine if we should increase or</i></b>
<a name="L136" href="source/net/ipv4/tcp_yeah.c#L136">136</a> <b><i>                         * decrease cwnd, and by how much.</i></b>
<a name="L137" href="source/net/ipv4/tcp_yeah.c#L137">137</a> <b><i>                         */</i></b>
<a name="L138" href="source/net/ipv4/tcp_yeah.c#L138">138</a> 
<a name="L139" href="source/net/ipv4/tcp_yeah.c#L139">139</a>                         <b><i>/* Pluck out the RTT we are using for the Vegas</i></b>
<a name="L140" href="source/net/ipv4/tcp_yeah.c#L140">140</a> <b><i>                         * calculations. This is the min RTT seen during the</i></b>
<a name="L141" href="source/net/ipv4/tcp_yeah.c#L141">141</a> <b><i>                         * last RTT. Taking the min filters out the effects</i></b>
<a name="L142" href="source/net/ipv4/tcp_yeah.c#L142">142</a> <b><i>                         * of delayed ACKs, at the cost of noticing congestion</i></b>
<a name="L143" href="source/net/ipv4/tcp_yeah.c#L143">143</a> <b><i>                         * a bit later.</i></b>
<a name="L144" href="source/net/ipv4/tcp_yeah.c#L144">144</a> <b><i>                         */</i></b>
<a name="L145" href="source/net/ipv4/tcp_yeah.c#L145">145</a>                         rtt = <a href="ident?i=yeah">yeah</a>-&gt;<a href="ident?i=vegas">vegas</a>.minRTT;
<a name="L146" href="source/net/ipv4/tcp_yeah.c#L146">146</a> 
<a name="L147" href="source/net/ipv4/tcp_yeah.c#L147">147</a>                         <b><i>/* Compute excess number of packets above bandwidth</i></b>
<a name="L148" href="source/net/ipv4/tcp_yeah.c#L148">148</a> <b><i>                         * Avoid doing full 64 bit divide.</i></b>
<a name="L149" href="source/net/ipv4/tcp_yeah.c#L149">149</a> <b><i>                         */</i></b>
<a name="L150" href="source/net/ipv4/tcp_yeah.c#L150">150</a>                         bw = <a href="ident?i=tp">tp</a>-&gt;snd_cwnd;
<a name="L151" href="source/net/ipv4/tcp_yeah.c#L151">151</a>                         bw *= rtt - <a href="ident?i=yeah">yeah</a>-&gt;<a href="ident?i=vegas">vegas</a>.baseRTT;
<a name="L152" href="source/net/ipv4/tcp_yeah.c#L152">152</a>                         <a href="ident?i=do_div">do_div</a>(bw, rtt);
<a name="L153" href="source/net/ipv4/tcp_yeah.c#L153">153</a>                         <a href="ident?i=queue">queue</a> = bw;
<a name="L154" href="source/net/ipv4/tcp_yeah.c#L154">154</a> 
<a name="L155" href="source/net/ipv4/tcp_yeah.c#L155">155</a>                         if (<a href="ident?i=queue">queue</a> &gt; <a href="ident?i=TCP_YEAH_ALPHA">TCP_YEAH_ALPHA</a> ||
<a name="L156" href="source/net/ipv4/tcp_yeah.c#L156">156</a>                             rtt - <a href="ident?i=yeah">yeah</a>-&gt;<a href="ident?i=vegas">vegas</a>.baseRTT &gt; (<a href="ident?i=yeah">yeah</a>-&gt;<a href="ident?i=vegas">vegas</a>.baseRTT / <a href="ident?i=TCP_YEAH_PHY">TCP_YEAH_PHY</a>)) {
<a name="L157" href="source/net/ipv4/tcp_yeah.c#L157">157</a>                                 if (<a href="ident?i=queue">queue</a> &gt; <a href="ident?i=TCP_YEAH_ALPHA">TCP_YEAH_ALPHA</a> &amp;&amp;
<a name="L158" href="source/net/ipv4/tcp_yeah.c#L158">158</a>                                     <a href="ident?i=tp">tp</a>-&gt;snd_cwnd &gt; <a href="ident?i=yeah">yeah</a>-&gt;reno_count) {
<a name="L159" href="source/net/ipv4/tcp_yeah.c#L159">159</a>                                         <a href="ident?i=u32">u32</a> reduction = <a href="ident?i=min">min</a>(<a href="ident?i=queue">queue</a> / <a href="ident?i=TCP_YEAH_GAMMA">TCP_YEAH_GAMMA</a> ,
<a name="L160" href="source/net/ipv4/tcp_yeah.c#L160">160</a>                                                             <a href="ident?i=tp">tp</a>-&gt;snd_cwnd &gt;&gt; <a href="ident?i=TCP_YEAH_EPSILON">TCP_YEAH_EPSILON</a>);
<a name="L161" href="source/net/ipv4/tcp_yeah.c#L161">161</a> 
<a name="L162" href="source/net/ipv4/tcp_yeah.c#L162">162</a>                                         <a href="ident?i=tp">tp</a>-&gt;snd_cwnd -= reduction;
<a name="L163" href="source/net/ipv4/tcp_yeah.c#L163">163</a> 
<a name="L164" href="source/net/ipv4/tcp_yeah.c#L164">164</a>                                         <a href="ident?i=tp">tp</a>-&gt;snd_cwnd = <a href="ident?i=max">max</a>(<a href="ident?i=tp">tp</a>-&gt;snd_cwnd,
<a name="L165" href="source/net/ipv4/tcp_yeah.c#L165">165</a>                                                            <a href="ident?i=yeah">yeah</a>-&gt;reno_count);
<a name="L166" href="source/net/ipv4/tcp_yeah.c#L166">166</a> 
<a name="L167" href="source/net/ipv4/tcp_yeah.c#L167">167</a>                                         <a href="ident?i=tp">tp</a>-&gt;snd_ssthresh = <a href="ident?i=tp">tp</a>-&gt;snd_cwnd;
<a name="L168" href="source/net/ipv4/tcp_yeah.c#L168">168</a>                                 }
<a name="L169" href="source/net/ipv4/tcp_yeah.c#L169">169</a> 
<a name="L170" href="source/net/ipv4/tcp_yeah.c#L170">170</a>                                 if (<a href="ident?i=yeah">yeah</a>-&gt;reno_count &lt;= 2)
<a name="L171" href="source/net/ipv4/tcp_yeah.c#L171">171</a>                                         <a href="ident?i=yeah">yeah</a>-&gt;reno_count = <a href="ident?i=max">max</a>(<a href="ident?i=tp">tp</a>-&gt;snd_cwnd&gt;&gt;1, 2U);
<a name="L172" href="source/net/ipv4/tcp_yeah.c#L172">172</a>                                 else
<a name="L173" href="source/net/ipv4/tcp_yeah.c#L173">173</a>                                         <a href="ident?i=yeah">yeah</a>-&gt;reno_count++;
<a name="L174" href="source/net/ipv4/tcp_yeah.c#L174">174</a> 
<a name="L175" href="source/net/ipv4/tcp_yeah.c#L175">175</a>                                 <a href="ident?i=yeah">yeah</a>-&gt;doing_reno_now = <a href="ident?i=min">min</a>(<a href="ident?i=yeah">yeah</a>-&gt;doing_reno_now + 1,
<a name="L176" href="source/net/ipv4/tcp_yeah.c#L176">176</a>                                                            0xffffffU);
<a name="L177" href="source/net/ipv4/tcp_yeah.c#L177">177</a>                         } else {
<a name="L178" href="source/net/ipv4/tcp_yeah.c#L178">178</a>                                 <a href="ident?i=yeah">yeah</a>-&gt;fast_count++;
<a name="L179" href="source/net/ipv4/tcp_yeah.c#L179">179</a> 
<a name="L180" href="source/net/ipv4/tcp_yeah.c#L180">180</a>                                 if (<a href="ident?i=yeah">yeah</a>-&gt;fast_count &gt; <a href="ident?i=TCP_YEAH_ZETA">TCP_YEAH_ZETA</a>) {
<a name="L181" href="source/net/ipv4/tcp_yeah.c#L181">181</a>                                         <a href="ident?i=yeah">yeah</a>-&gt;reno_count = 2;
<a name="L182" href="source/net/ipv4/tcp_yeah.c#L182">182</a>                                         <a href="ident?i=yeah">yeah</a>-&gt;fast_count = 0;
<a name="L183" href="source/net/ipv4/tcp_yeah.c#L183">183</a>                                 }
<a name="L184" href="source/net/ipv4/tcp_yeah.c#L184">184</a> 
<a name="L185" href="source/net/ipv4/tcp_yeah.c#L185">185</a>                                 <a href="ident?i=yeah">yeah</a>-&gt;doing_reno_now = 0;
<a name="L186" href="source/net/ipv4/tcp_yeah.c#L186">186</a>                         }
<a name="L187" href="source/net/ipv4/tcp_yeah.c#L187">187</a> 
<a name="L188" href="source/net/ipv4/tcp_yeah.c#L188">188</a>                         <a href="ident?i=yeah">yeah</a>-&gt;lastQ = <a href="ident?i=queue">queue</a>;
<a name="L189" href="source/net/ipv4/tcp_yeah.c#L189">189</a>                 }
<a name="L190" href="source/net/ipv4/tcp_yeah.c#L190">190</a> 
<a name="L191" href="source/net/ipv4/tcp_yeah.c#L191">191</a>                 <b><i>/* Save the extent of the current window so we can use this</i></b>
<a name="L192" href="source/net/ipv4/tcp_yeah.c#L192">192</a> <b><i>                 * at the end of the next RTT.</i></b>
<a name="L193" href="source/net/ipv4/tcp_yeah.c#L193">193</a> <b><i>                 */</i></b>
<a name="L194" href="source/net/ipv4/tcp_yeah.c#L194">194</a>                 <a href="ident?i=yeah">yeah</a>-&gt;<a href="ident?i=vegas">vegas</a>.beg_snd_una  = <a href="ident?i=yeah">yeah</a>-&gt;<a href="ident?i=vegas">vegas</a>.beg_snd_nxt;
<a name="L195" href="source/net/ipv4/tcp_yeah.c#L195">195</a>                 <a href="ident?i=yeah">yeah</a>-&gt;<a href="ident?i=vegas">vegas</a>.beg_snd_nxt  = <a href="ident?i=tp">tp</a>-&gt;snd_nxt;
<a name="L196" href="source/net/ipv4/tcp_yeah.c#L196">196</a>                 <a href="ident?i=yeah">yeah</a>-&gt;<a href="ident?i=vegas">vegas</a>.beg_snd_cwnd = <a href="ident?i=tp">tp</a>-&gt;snd_cwnd;
<a name="L197" href="source/net/ipv4/tcp_yeah.c#L197">197</a> 
<a name="L198" href="source/net/ipv4/tcp_yeah.c#L198">198</a>                 <b><i>/* Wipe the slate clean for the next RTT. */</i></b>
<a name="L199" href="source/net/ipv4/tcp_yeah.c#L199">199</a>                 <a href="ident?i=yeah">yeah</a>-&gt;<a href="ident?i=vegas">vegas</a>.cntRTT = 0;
<a name="L200" href="source/net/ipv4/tcp_yeah.c#L200">200</a>                 <a href="ident?i=yeah">yeah</a>-&gt;<a href="ident?i=vegas">vegas</a>.minRTT = 0x7fffffff;
<a name="L201" href="source/net/ipv4/tcp_yeah.c#L201">201</a>         }
<a name="L202" href="source/net/ipv4/tcp_yeah.c#L202">202</a> }
<a name="L203" href="source/net/ipv4/tcp_yeah.c#L203">203</a> 
<a name="L204" href="source/net/ipv4/tcp_yeah.c#L204">204</a> static <a href="ident?i=u32">u32</a> <a href="ident?i=tcp_yeah_ssthresh">tcp_yeah_ssthresh</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L205" href="source/net/ipv4/tcp_yeah.c#L205">205</a> {
<a name="L206" href="source/net/ipv4/tcp_yeah.c#L206">206</a>         const struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L207" href="source/net/ipv4/tcp_yeah.c#L207">207</a>         struct <a href="ident?i=yeah">yeah</a> *<a href="ident?i=yeah">yeah</a> = <a href="ident?i=inet_csk_ca">inet_csk_ca</a>(sk);
<a name="L208" href="source/net/ipv4/tcp_yeah.c#L208">208</a>         <a href="ident?i=u32">u32</a> reduction;
<a name="L209" href="source/net/ipv4/tcp_yeah.c#L209">209</a> 
<a name="L210" href="source/net/ipv4/tcp_yeah.c#L210">210</a>         if (<a href="ident?i=yeah">yeah</a>-&gt;doing_reno_now &lt; <a href="ident?i=TCP_YEAH_RHO">TCP_YEAH_RHO</a>) {
<a name="L211" href="source/net/ipv4/tcp_yeah.c#L211">211</a>                 reduction = <a href="ident?i=yeah">yeah</a>-&gt;lastQ;
<a name="L212" href="source/net/ipv4/tcp_yeah.c#L212">212</a> 
<a name="L213" href="source/net/ipv4/tcp_yeah.c#L213">213</a>                 reduction = <a href="ident?i=min">min</a>(reduction, <a href="ident?i=max">max</a>(<a href="ident?i=tp">tp</a>-&gt;snd_cwnd&gt;&gt;1, 2U));
<a name="L214" href="source/net/ipv4/tcp_yeah.c#L214">214</a> 
<a name="L215" href="source/net/ipv4/tcp_yeah.c#L215">215</a>                 reduction = <a href="ident?i=max">max</a>(reduction, <a href="ident?i=tp">tp</a>-&gt;snd_cwnd &gt;&gt; <a href="ident?i=TCP_YEAH_DELTA">TCP_YEAH_DELTA</a>);
<a name="L216" href="source/net/ipv4/tcp_yeah.c#L216">216</a>         } else
<a name="L217" href="source/net/ipv4/tcp_yeah.c#L217">217</a>                 reduction = <a href="ident?i=max">max</a>(<a href="ident?i=tp">tp</a>-&gt;snd_cwnd&gt;&gt;1, 2U);
<a name="L218" href="source/net/ipv4/tcp_yeah.c#L218">218</a> 
<a name="L219" href="source/net/ipv4/tcp_yeah.c#L219">219</a>         <a href="ident?i=yeah">yeah</a>-&gt;fast_count = 0;
<a name="L220" href="source/net/ipv4/tcp_yeah.c#L220">220</a>         <a href="ident?i=yeah">yeah</a>-&gt;reno_count = <a href="ident?i=max">max</a>(<a href="ident?i=yeah">yeah</a>-&gt;reno_count&gt;&gt;1, 2U);
<a name="L221" href="source/net/ipv4/tcp_yeah.c#L221">221</a> 
<a name="L222" href="source/net/ipv4/tcp_yeah.c#L222">222</a>         return <a href="ident?i=tp">tp</a>-&gt;snd_cwnd - reduction;
<a name="L223" href="source/net/ipv4/tcp_yeah.c#L223">223</a> }
<a name="L224" href="source/net/ipv4/tcp_yeah.c#L224">224</a> 
<a name="L225" href="source/net/ipv4/tcp_yeah.c#L225">225</a> static struct <a href="ident?i=tcp_congestion_ops">tcp_congestion_ops</a> tcp_yeah <a href="ident?i=__read_mostly">__read_mostly</a> = {
<a name="L226" href="source/net/ipv4/tcp_yeah.c#L226">226</a>         .<a href="ident?i=init">init</a>           = <a href="ident?i=tcp_yeah_init">tcp_yeah_init</a>,
<a name="L227" href="source/net/ipv4/tcp_yeah.c#L227">227</a>         .ssthresh       = <a href="ident?i=tcp_yeah_ssthresh">tcp_yeah_ssthresh</a>,
<a name="L228" href="source/net/ipv4/tcp_yeah.c#L228">228</a>         .cong_avoid     = <a href="ident?i=tcp_yeah_cong_avoid">tcp_yeah_cong_avoid</a>,
<a name="L229" href="source/net/ipv4/tcp_yeah.c#L229">229</a>         .<a href="ident?i=set_state">set_state</a>      = <a href="ident?i=tcp_vegas_state">tcp_vegas_state</a>,
<a name="L230" href="source/net/ipv4/tcp_yeah.c#L230">230</a>         .cwnd_event     = <a href="ident?i=tcp_vegas_cwnd_event">tcp_vegas_cwnd_event</a>,
<a name="L231" href="source/net/ipv4/tcp_yeah.c#L231">231</a>         .<a href="ident?i=get_info">get_info</a>       = <a href="ident?i=tcp_vegas_get_info">tcp_vegas_get_info</a>,
<a name="L232" href="source/net/ipv4/tcp_yeah.c#L232">232</a>         .pkts_acked     = <a href="ident?i=tcp_yeah_pkts_acked">tcp_yeah_pkts_acked</a>,
<a name="L233" href="source/net/ipv4/tcp_yeah.c#L233">233</a> 
<a name="L234" href="source/net/ipv4/tcp_yeah.c#L234">234</a>         .owner          = <a href="ident?i=THIS_MODULE">THIS_MODULE</a>,
<a name="L235" href="source/net/ipv4/tcp_yeah.c#L235">235</a>         .<a href="ident?i=name">name</a>           = <i>"yeah"</i>,
<a name="L236" href="source/net/ipv4/tcp_yeah.c#L236">236</a> };
<a name="L237" href="source/net/ipv4/tcp_yeah.c#L237">237</a> 
<a name="L238" href="source/net/ipv4/tcp_yeah.c#L238">238</a> static int <a href="ident?i=__init">__init</a> <a href="ident?i=tcp_yeah_register">tcp_yeah_register</a>(void)
<a name="L239" href="source/net/ipv4/tcp_yeah.c#L239">239</a> {
<a name="L240" href="source/net/ipv4/tcp_yeah.c#L240">240</a>         <a href="ident?i=BUG_ON">BUG_ON</a>(sizeof(struct <a href="ident?i=yeah">yeah</a>) &gt; <a href="ident?i=ICSK_CA_PRIV_SIZE">ICSK_CA_PRIV_SIZE</a>);
<a name="L241" href="source/net/ipv4/tcp_yeah.c#L241">241</a>         <a href="ident?i=tcp_register_congestion_control">tcp_register_congestion_control</a>(&amp;tcp_yeah);
<a name="L242" href="source/net/ipv4/tcp_yeah.c#L242">242</a>         return 0;
<a name="L243" href="source/net/ipv4/tcp_yeah.c#L243">243</a> }
<a name="L244" href="source/net/ipv4/tcp_yeah.c#L244">244</a> 
<a name="L245" href="source/net/ipv4/tcp_yeah.c#L245">245</a> static void <a href="ident?i=__exit">__exit</a> <a href="ident?i=tcp_yeah_unregister">tcp_yeah_unregister</a>(void)
<a name="L246" href="source/net/ipv4/tcp_yeah.c#L246">246</a> {
<a name="L247" href="source/net/ipv4/tcp_yeah.c#L247">247</a>         <a href="ident?i=tcp_unregister_congestion_control">tcp_unregister_congestion_control</a>(&amp;tcp_yeah);
<a name="L248" href="source/net/ipv4/tcp_yeah.c#L248">248</a> }
<a name="L249" href="source/net/ipv4/tcp_yeah.c#L249">249</a> 
<a name="L250" href="source/net/ipv4/tcp_yeah.c#L250">250</a> <a href="ident?i=module_init">module_init</a>(<a href="ident?i=tcp_yeah_register">tcp_yeah_register</a>);
<a name="L251" href="source/net/ipv4/tcp_yeah.c#L251">251</a> <a href="ident?i=module_exit">module_exit</a>(<a href="ident?i=tcp_yeah_unregister">tcp_yeah_unregister</a>);
<a name="L252" href="source/net/ipv4/tcp_yeah.c#L252">252</a> 
<a name="L253" href="source/net/ipv4/tcp_yeah.c#L253">253</a> <a href="ident?i=MODULE_AUTHOR">MODULE_AUTHOR</a>(<i>"Angelo P. Castellani"</i>);
<a name="L254" href="source/net/ipv4/tcp_yeah.c#L254">254</a> <a href="ident?i=MODULE_LICENSE">MODULE_LICENSE</a>(<i>"GPL"</i>);
<a name="L255" href="source/net/ipv4/tcp_yeah.c#L255">255</a> <a href="ident?i=MODULE_DESCRIPTION">MODULE_DESCRIPTION</a>(<i>"YeAH TCP"</i>);
<a name="L256" href="source/net/ipv4/tcp_yeah.c#L256">256</a> </pre></div><p>
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
