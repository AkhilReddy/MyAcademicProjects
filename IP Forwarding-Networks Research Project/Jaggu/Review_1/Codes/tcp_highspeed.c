<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title>Linux/net/ipv4/tcp_highspeed.c - Linux Cross Reference - Free Electrons</title>
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
		 &nbsp;&bull;&nbsp;<b><i>source navigation</i></b> &nbsp;&bull;&nbsp;<a href="diff/net/ipv4/tcp_highspeed.c">diff markup</a> &nbsp;&bull;&nbsp;<a href="ident">identifier search</a> &nbsp;&bull;&nbsp;<a href="search">freetext search</a> &nbsp;&bull;&nbsp;
		</p>
	</div>
</div>

<div id="topbar">
  
  <p>Version: &nbsp;<a href="source/net/ipv4/tcp_highspeed.c?v=2.0.40">2.0.40</a>&nbsp;<a href="source/net/ipv4/tcp_highspeed.c?v=2.2.26">2.2.26</a>&nbsp;<a href="source/net/ipv4/tcp_highspeed.c?v=2.4.37">2.4.37</a>&nbsp;<a href="source/net/ipv4/tcp_highspeed.c?v=3.5">3.5</a>&nbsp;<a href="source/net/ipv4/tcp_highspeed.c?v=3.6">3.6</a>&nbsp;<a href="source/net/ipv4/tcp_highspeed.c?v=3.7">3.7</a>&nbsp;<a href="source/net/ipv4/tcp_highspeed.c?v=3.8">3.8</a>&nbsp;<a href="source/net/ipv4/tcp_highspeed.c?v=3.9">3.9</a>&nbsp;<a href="source/net/ipv4/tcp_highspeed.c?v=3.10">3.10</a>&nbsp;<a href="source/net/ipv4/tcp_highspeed.c?v=3.11">3.11</a>&nbsp;<a href="source/net/ipv4/tcp_highspeed.c?v=3.12">3.12</a>&nbsp;<a href="source/net/ipv4/tcp_highspeed.c?v=3.13">3.13</a>&nbsp;<a href="source/net/ipv4/tcp_highspeed.c?v=3.14">3.14</a>&nbsp;<a href="source/net/ipv4/tcp_highspeed.c?v=3.15">3.15</a>&nbsp;<a href="source/net/ipv4/tcp_highspeed.c?v=3.16">3.16</a>&nbsp;<a href="source/net/ipv4/tcp_highspeed.c?v=3.17">3.17</a>&nbsp;<a href="source/net/ipv4/tcp_highspeed.c?v=3.18">3.18</a>&nbsp;<a href="source/net/ipv4/tcp_highspeed.c?v=3.19">3.19</a>&nbsp;<a href="source/net/ipv4/tcp_highspeed.c?v=4.0">4.0</a>&nbsp;<b><i>4.1</i></b></p>
  
</div>

<h1><a href="source/">Linux</a>/<a href="source/net/">net</a>/<a href="source/net/ipv4/">ipv4</a>/<a href="source/net/ipv4/tcp_highspeed.c">tcp_highspeed.c</a></h1>
<div id="lxrcode"><pre>  <a name="L1" href="source/net/ipv4/tcp_highspeed.c#L1">1</a> <b><i>/*</i></b>
  <a name="L2" href="source/net/ipv4/tcp_highspeed.c#L2">2</a> <b><i> * Sally Floyd's High Speed TCP (RFC 3649) congestion control</i></b>
  <a name="L3" href="source/net/ipv4/tcp_highspeed.c#L3">3</a> <b><i> *</i></b>
  <a name="L4" href="source/net/ipv4/tcp_highspeed.c#L4">4</a> <b><i> * See <a href="http://www.icir.org/floyd/hstcp.html">http://www.icir.org/floyd/hstcp.html</a></i></b>
  <a name="L5" href="source/net/ipv4/tcp_highspeed.c#L5">5</a> <b><i> *</i></b>
  <a name="L6" href="source/net/ipv4/tcp_highspeed.c#L6">6</a> <b><i> * John Heffner &lt;jheffner@psc.edu&gt;</i></b>
  <a name="L7" href="source/net/ipv4/tcp_highspeed.c#L7">7</a> <b><i> */</i></b>
  <a name="L8" href="source/net/ipv4/tcp_highspeed.c#L8">8</a> 
  <a name="L9" href="source/net/ipv4/tcp_highspeed.c#L9">9</a> #include &lt;linux/module.h&gt;
 <a name="L10" href="source/net/ipv4/tcp_highspeed.c#L10">10</a> #include &lt;net/tcp.h&gt;
 <a name="L11" href="source/net/ipv4/tcp_highspeed.c#L11">11</a> 
 <a name="L12" href="source/net/ipv4/tcp_highspeed.c#L12">12</a> <b><i>/* From AIMD tables from RFC 3649 appendix B,</i></b>
 <a name="L13" href="source/net/ipv4/tcp_highspeed.c#L13">13</a> <b><i> * with fixed-point MD scaled &lt;&lt;8.</i></b>
 <a name="L14" href="source/net/ipv4/tcp_highspeed.c#L14">14</a> <b><i> */</i></b>
 <a name="L15" href="source/net/ipv4/tcp_highspeed.c#L15">15</a> static const struct <a href="ident?i=hstcp_aimd_val">hstcp_aimd_val</a> {
 <a name="L16" href="source/net/ipv4/tcp_highspeed.c#L16">16</a>         unsigned int cwnd;
 <a name="L17" href="source/net/ipv4/tcp_highspeed.c#L17">17</a>         unsigned int md;
 <a name="L18" href="source/net/ipv4/tcp_highspeed.c#L18">18</a> } <a href="ident?i=hstcp_aimd_vals">hstcp_aimd_vals</a>[] = {
 <a name="L19" href="source/net/ipv4/tcp_highspeed.c#L19">19</a>         {     38,  128, <b><i>/*  0.50 */</i></b> },
 <a name="L20" href="source/net/ipv4/tcp_highspeed.c#L20">20</a>         {    118,  112, <b><i>/*  0.44 */</i></b> },
 <a name="L21" href="source/net/ipv4/tcp_highspeed.c#L21">21</a>         {    221,  104, <b><i>/*  0.41 */</i></b> },
 <a name="L22" href="source/net/ipv4/tcp_highspeed.c#L22">22</a>         {    347,   98, <b><i>/*  0.38 */</i></b> },
 <a name="L23" href="source/net/ipv4/tcp_highspeed.c#L23">23</a>         {    495,   93, <b><i>/*  0.37 */</i></b> },
 <a name="L24" href="source/net/ipv4/tcp_highspeed.c#L24">24</a>         {    663,   89, <b><i>/*  0.35 */</i></b> },
 <a name="L25" href="source/net/ipv4/tcp_highspeed.c#L25">25</a>         {    851,   86, <b><i>/*  0.34 */</i></b> },
 <a name="L26" href="source/net/ipv4/tcp_highspeed.c#L26">26</a>         {   1058,   83, <b><i>/*  0.33 */</i></b> },
 <a name="L27" href="source/net/ipv4/tcp_highspeed.c#L27">27</a>         {   1284,   81, <b><i>/*  0.32 */</i></b> },
 <a name="L28" href="source/net/ipv4/tcp_highspeed.c#L28">28</a>         {   1529,   78, <b><i>/*  0.31 */</i></b> },
 <a name="L29" href="source/net/ipv4/tcp_highspeed.c#L29">29</a>         {   1793,   76, <b><i>/*  0.30 */</i></b> },
 <a name="L30" href="source/net/ipv4/tcp_highspeed.c#L30">30</a>         {   2076,   74, <b><i>/*  0.29 */</i></b> },
 <a name="L31" href="source/net/ipv4/tcp_highspeed.c#L31">31</a>         {   2378,   72, <b><i>/*  0.28 */</i></b> },
 <a name="L32" href="source/net/ipv4/tcp_highspeed.c#L32">32</a>         {   2699,   71, <b><i>/*  0.28 */</i></b> },
 <a name="L33" href="source/net/ipv4/tcp_highspeed.c#L33">33</a>         {   3039,   69, <b><i>/*  0.27 */</i></b> },
 <a name="L34" href="source/net/ipv4/tcp_highspeed.c#L34">34</a>         {   3399,   68, <b><i>/*  0.27 */</i></b> },
 <a name="L35" href="source/net/ipv4/tcp_highspeed.c#L35">35</a>         {   3778,   66, <b><i>/*  0.26 */</i></b> },
 <a name="L36" href="source/net/ipv4/tcp_highspeed.c#L36">36</a>         {   4177,   65, <b><i>/*  0.26 */</i></b> },
 <a name="L37" href="source/net/ipv4/tcp_highspeed.c#L37">37</a>         {   4596,   64, <b><i>/*  0.25 */</i></b> },
 <a name="L38" href="source/net/ipv4/tcp_highspeed.c#L38">38</a>         {   5036,   62, <b><i>/*  0.25 */</i></b> },
 <a name="L39" href="source/net/ipv4/tcp_highspeed.c#L39">39</a>         {   5497,   61, <b><i>/*  0.24 */</i></b> },
 <a name="L40" href="source/net/ipv4/tcp_highspeed.c#L40">40</a>         {   5979,   60, <b><i>/*  0.24 */</i></b> },
 <a name="L41" href="source/net/ipv4/tcp_highspeed.c#L41">41</a>         {   6483,   59, <b><i>/*  0.23 */</i></b> },
 <a name="L42" href="source/net/ipv4/tcp_highspeed.c#L42">42</a>         {   7009,   58, <b><i>/*  0.23 */</i></b> },
 <a name="L43" href="source/net/ipv4/tcp_highspeed.c#L43">43</a>         {   7558,   57, <b><i>/*  0.22 */</i></b> },
 <a name="L44" href="source/net/ipv4/tcp_highspeed.c#L44">44</a>         {   8130,   56, <b><i>/*  0.22 */</i></b> },
 <a name="L45" href="source/net/ipv4/tcp_highspeed.c#L45">45</a>         {   8726,   55, <b><i>/*  0.22 */</i></b> },
 <a name="L46" href="source/net/ipv4/tcp_highspeed.c#L46">46</a>         {   9346,   54, <b><i>/*  0.21 */</i></b> },
 <a name="L47" href="source/net/ipv4/tcp_highspeed.c#L47">47</a>         {   9991,   53, <b><i>/*  0.21 */</i></b> },
 <a name="L48" href="source/net/ipv4/tcp_highspeed.c#L48">48</a>         {  10661,   52, <b><i>/*  0.21 */</i></b> },
 <a name="L49" href="source/net/ipv4/tcp_highspeed.c#L49">49</a>         {  11358,   52, <b><i>/*  0.20 */</i></b> },
 <a name="L50" href="source/net/ipv4/tcp_highspeed.c#L50">50</a>         {  12082,   51, <b><i>/*  0.20 */</i></b> },
 <a name="L51" href="source/net/ipv4/tcp_highspeed.c#L51">51</a>         {  12834,   50, <b><i>/*  0.20 */</i></b> },
 <a name="L52" href="source/net/ipv4/tcp_highspeed.c#L52">52</a>         {  13614,   49, <b><i>/*  0.19 */</i></b> },
 <a name="L53" href="source/net/ipv4/tcp_highspeed.c#L53">53</a>         {  14424,   48, <b><i>/*  0.19 */</i></b> },
 <a name="L54" href="source/net/ipv4/tcp_highspeed.c#L54">54</a>         {  15265,   48, <b><i>/*  0.19 */</i></b> },
 <a name="L55" href="source/net/ipv4/tcp_highspeed.c#L55">55</a>         {  16137,   47, <b><i>/*  0.19 */</i></b> },
 <a name="L56" href="source/net/ipv4/tcp_highspeed.c#L56">56</a>         {  17042,   46, <b><i>/*  0.18 */</i></b> },
 <a name="L57" href="source/net/ipv4/tcp_highspeed.c#L57">57</a>         {  17981,   45, <b><i>/*  0.18 */</i></b> },
 <a name="L58" href="source/net/ipv4/tcp_highspeed.c#L58">58</a>         {  18955,   45, <b><i>/*  0.18 */</i></b> },
 <a name="L59" href="source/net/ipv4/tcp_highspeed.c#L59">59</a>         {  19965,   44, <b><i>/*  0.17 */</i></b> },
 <a name="L60" href="source/net/ipv4/tcp_highspeed.c#L60">60</a>         {  21013,   43, <b><i>/*  0.17 */</i></b> },
 <a name="L61" href="source/net/ipv4/tcp_highspeed.c#L61">61</a>         {  22101,   43, <b><i>/*  0.17 */</i></b> },
 <a name="L62" href="source/net/ipv4/tcp_highspeed.c#L62">62</a>         {  23230,   42, <b><i>/*  0.17 */</i></b> },
 <a name="L63" href="source/net/ipv4/tcp_highspeed.c#L63">63</a>         {  24402,   41, <b><i>/*  0.16 */</i></b> },
 <a name="L64" href="source/net/ipv4/tcp_highspeed.c#L64">64</a>         {  25618,   41, <b><i>/*  0.16 */</i></b> },
 <a name="L65" href="source/net/ipv4/tcp_highspeed.c#L65">65</a>         {  26881,   40, <b><i>/*  0.16 */</i></b> },
 <a name="L66" href="source/net/ipv4/tcp_highspeed.c#L66">66</a>         {  28193,   39, <b><i>/*  0.16 */</i></b> },
 <a name="L67" href="source/net/ipv4/tcp_highspeed.c#L67">67</a>         {  29557,   39, <b><i>/*  0.15 */</i></b> },
 <a name="L68" href="source/net/ipv4/tcp_highspeed.c#L68">68</a>         {  30975,   38, <b><i>/*  0.15 */</i></b> },
 <a name="L69" href="source/net/ipv4/tcp_highspeed.c#L69">69</a>         {  32450,   38, <b><i>/*  0.15 */</i></b> },
 <a name="L70" href="source/net/ipv4/tcp_highspeed.c#L70">70</a>         {  33986,   37, <b><i>/*  0.15 */</i></b> },
 <a name="L71" href="source/net/ipv4/tcp_highspeed.c#L71">71</a>         {  35586,   36, <b><i>/*  0.14 */</i></b> },
 <a name="L72" href="source/net/ipv4/tcp_highspeed.c#L72">72</a>         {  37253,   36, <b><i>/*  0.14 */</i></b> },
 <a name="L73" href="source/net/ipv4/tcp_highspeed.c#L73">73</a>         {  38992,   35, <b><i>/*  0.14 */</i></b> },
 <a name="L74" href="source/net/ipv4/tcp_highspeed.c#L74">74</a>         {  40808,   35, <b><i>/*  0.14 */</i></b> },
 <a name="L75" href="source/net/ipv4/tcp_highspeed.c#L75">75</a>         {  42707,   34, <b><i>/*  0.13 */</i></b> },
 <a name="L76" href="source/net/ipv4/tcp_highspeed.c#L76">76</a>         {  44694,   33, <b><i>/*  0.13 */</i></b> },
 <a name="L77" href="source/net/ipv4/tcp_highspeed.c#L77">77</a>         {  46776,   33, <b><i>/*  0.13 */</i></b> },
 <a name="L78" href="source/net/ipv4/tcp_highspeed.c#L78">78</a>         {  48961,   32, <b><i>/*  0.13 */</i></b> },
 <a name="L79" href="source/net/ipv4/tcp_highspeed.c#L79">79</a>         {  51258,   32, <b><i>/*  0.13 */</i></b> },
 <a name="L80" href="source/net/ipv4/tcp_highspeed.c#L80">80</a>         {  53677,   31, <b><i>/*  0.12 */</i></b> },
 <a name="L81" href="source/net/ipv4/tcp_highspeed.c#L81">81</a>         {  56230,   30, <b><i>/*  0.12 */</i></b> },
 <a name="L82" href="source/net/ipv4/tcp_highspeed.c#L82">82</a>         {  58932,   30, <b><i>/*  0.12 */</i></b> },
 <a name="L83" href="source/net/ipv4/tcp_highspeed.c#L83">83</a>         {  61799,   29, <b><i>/*  0.12 */</i></b> },
 <a name="L84" href="source/net/ipv4/tcp_highspeed.c#L84">84</a>         {  64851,   28, <b><i>/*  0.11 */</i></b> },
 <a name="L85" href="source/net/ipv4/tcp_highspeed.c#L85">85</a>         {  68113,   28, <b><i>/*  0.11 */</i></b> },
 <a name="L86" href="source/net/ipv4/tcp_highspeed.c#L86">86</a>         {  71617,   27, <b><i>/*  0.11 */</i></b> },
 <a name="L87" href="source/net/ipv4/tcp_highspeed.c#L87">87</a>         {  75401,   26, <b><i>/*  0.10 */</i></b> },
 <a name="L88" href="source/net/ipv4/tcp_highspeed.c#L88">88</a>         {  79517,   26, <b><i>/*  0.10 */</i></b> },
 <a name="L89" href="source/net/ipv4/tcp_highspeed.c#L89">89</a>         {  84035,   25, <b><i>/*  0.10 */</i></b> },
 <a name="L90" href="source/net/ipv4/tcp_highspeed.c#L90">90</a>         {  89053,   24, <b><i>/*  0.10 */</i></b> },
 <a name="L91" href="source/net/ipv4/tcp_highspeed.c#L91">91</a> };
 <a name="L92" href="source/net/ipv4/tcp_highspeed.c#L92">92</a> 
 <a name="L93" href="source/net/ipv4/tcp_highspeed.c#L93">93</a> #define <a href="ident?i=HSTCP_AIMD_MAX">HSTCP_AIMD_MAX</a>  <a href="ident?i=ARRAY_SIZE">ARRAY_SIZE</a>(<a href="ident?i=hstcp_aimd_vals">hstcp_aimd_vals</a>)
 <a name="L94" href="source/net/ipv4/tcp_highspeed.c#L94">94</a> 
 <a name="L95" href="source/net/ipv4/tcp_highspeed.c#L95">95</a> struct <a href="ident?i=hstcp">hstcp</a> {
 <a name="L96" href="source/net/ipv4/tcp_highspeed.c#L96">96</a>         <a href="ident?i=u32">u32</a>     ai;
 <a name="L97" href="source/net/ipv4/tcp_highspeed.c#L97">97</a> };
 <a name="L98" href="source/net/ipv4/tcp_highspeed.c#L98">98</a> 
 <a name="L99" href="source/net/ipv4/tcp_highspeed.c#L99">99</a> static void <a href="ident?i=hstcp_init">hstcp_init</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L100" href="source/net/ipv4/tcp_highspeed.c#L100">100</a> {
<a name="L101" href="source/net/ipv4/tcp_highspeed.c#L101">101</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L102" href="source/net/ipv4/tcp_highspeed.c#L102">102</a>         struct <a href="ident?i=hstcp">hstcp</a> *<a href="ident?i=ca">ca</a> = <a href="ident?i=inet_csk_ca">inet_csk_ca</a>(sk);
<a name="L103" href="source/net/ipv4/tcp_highspeed.c#L103">103</a> 
<a name="L104" href="source/net/ipv4/tcp_highspeed.c#L104">104</a>         <a href="ident?i=ca">ca</a>-&gt;ai = 0;
<a name="L105" href="source/net/ipv4/tcp_highspeed.c#L105">105</a> 
<a name="L106" href="source/net/ipv4/tcp_highspeed.c#L106">106</a>         <b><i>/* Ensure the MD arithmetic works.  This is somewhat pedantic,</i></b>
<a name="L107" href="source/net/ipv4/tcp_highspeed.c#L107">107</a> <b><i>         * since I don't think we will see a cwnd this large. :) */</i></b>
<a name="L108" href="source/net/ipv4/tcp_highspeed.c#L108">108</a>         <a href="ident?i=tp">tp</a>-&gt;snd_cwnd_clamp = <a href="ident?i=min_t">min_t</a>(<a href="ident?i=u32">u32</a>, <a href="ident?i=tp">tp</a>-&gt;snd_cwnd_clamp, 0xffffffff/128);
<a name="L109" href="source/net/ipv4/tcp_highspeed.c#L109">109</a> }
<a name="L110" href="source/net/ipv4/tcp_highspeed.c#L110">110</a> 
<a name="L111" href="source/net/ipv4/tcp_highspeed.c#L111">111</a> static void <a href="ident?i=hstcp_cong_avoid">hstcp_cong_avoid</a>(struct <a href="ident?i=sock">sock</a> *sk, <a href="ident?i=u32">u32</a> ack, <a href="ident?i=u32">u32</a> acked)
<a name="L112" href="source/net/ipv4/tcp_highspeed.c#L112">112</a> {
<a name="L113" href="source/net/ipv4/tcp_highspeed.c#L113">113</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L114" href="source/net/ipv4/tcp_highspeed.c#L114">114</a>         struct <a href="ident?i=hstcp">hstcp</a> *<a href="ident?i=ca">ca</a> = <a href="ident?i=inet_csk_ca">inet_csk_ca</a>(sk);
<a name="L115" href="source/net/ipv4/tcp_highspeed.c#L115">115</a> 
<a name="L116" href="source/net/ipv4/tcp_highspeed.c#L116">116</a>         if (!<a href="ident?i=tcp_is_cwnd_limited">tcp_is_cwnd_limited</a>(sk))
<a name="L117" href="source/net/ipv4/tcp_highspeed.c#L117">117</a>                 return;
<a name="L118" href="source/net/ipv4/tcp_highspeed.c#L118">118</a> 
<a name="L119" href="source/net/ipv4/tcp_highspeed.c#L119">119</a>         if (<a href="ident?i=tp">tp</a>-&gt;snd_cwnd &lt;= <a href="ident?i=tp">tp</a>-&gt;snd_ssthresh)
<a name="L120" href="source/net/ipv4/tcp_highspeed.c#L120">120</a>                 <a href="ident?i=tcp_slow_start">tcp_slow_start</a>(<a href="ident?i=tp">tp</a>, acked);
<a name="L121" href="source/net/ipv4/tcp_highspeed.c#L121">121</a>         else {
<a name="L122" href="source/net/ipv4/tcp_highspeed.c#L122">122</a>                 <b><i>/* Update AIMD parameters.</i></b>
<a name="L123" href="source/net/ipv4/tcp_highspeed.c#L123">123</a> <b><i>                 *</i></b>
<a name="L124" href="source/net/ipv4/tcp_highspeed.c#L124">124</a> <b><i>                 * We want to guarantee that:</i></b>
<a name="L125" href="source/net/ipv4/tcp_highspeed.c#L125">125</a> <b><i>                 *     hstcp_aimd_vals[ca-&gt;ai-1].cwnd &lt;</i></b>
<a name="L126" href="source/net/ipv4/tcp_highspeed.c#L126">126</a> <b><i>                 *     snd_cwnd &lt;=</i></b>
<a name="L127" href="source/net/ipv4/tcp_highspeed.c#L127">127</a> <b><i>                 *     hstcp_aimd_vals[ca-&gt;ai].cwnd</i></b>
<a name="L128" href="source/net/ipv4/tcp_highspeed.c#L128">128</a> <b><i>                 */</i></b>
<a name="L129" href="source/net/ipv4/tcp_highspeed.c#L129">129</a>                 if (<a href="ident?i=tp">tp</a>-&gt;snd_cwnd &gt; <a href="ident?i=hstcp_aimd_vals">hstcp_aimd_vals</a>[<a href="ident?i=ca">ca</a>-&gt;ai].cwnd) {
<a name="L130" href="source/net/ipv4/tcp_highspeed.c#L130">130</a>                         while (<a href="ident?i=tp">tp</a>-&gt;snd_cwnd &gt; <a href="ident?i=hstcp_aimd_vals">hstcp_aimd_vals</a>[<a href="ident?i=ca">ca</a>-&gt;ai].cwnd &amp;&amp;
<a name="L131" href="source/net/ipv4/tcp_highspeed.c#L131">131</a>                                <a href="ident?i=ca">ca</a>-&gt;ai &lt; <a href="ident?i=HSTCP_AIMD_MAX">HSTCP_AIMD_MAX</a> - 1)
<a name="L132" href="source/net/ipv4/tcp_highspeed.c#L132">132</a>                                 <a href="ident?i=ca">ca</a>-&gt;ai++;
<a name="L133" href="source/net/ipv4/tcp_highspeed.c#L133">133</a>                 } else if (<a href="ident?i=ca">ca</a>-&gt;ai &amp;&amp; <a href="ident?i=tp">tp</a>-&gt;snd_cwnd &lt;= <a href="ident?i=hstcp_aimd_vals">hstcp_aimd_vals</a>[<a href="ident?i=ca">ca</a>-&gt;ai-1].cwnd) {
<a name="L134" href="source/net/ipv4/tcp_highspeed.c#L134">134</a>                         while (<a href="ident?i=ca">ca</a>-&gt;ai &amp;&amp; <a href="ident?i=tp">tp</a>-&gt;snd_cwnd &lt;= <a href="ident?i=hstcp_aimd_vals">hstcp_aimd_vals</a>[<a href="ident?i=ca">ca</a>-&gt;ai-1].cwnd)
<a name="L135" href="source/net/ipv4/tcp_highspeed.c#L135">135</a>                                 <a href="ident?i=ca">ca</a>-&gt;ai--;
<a name="L136" href="source/net/ipv4/tcp_highspeed.c#L136">136</a>                 }
<a name="L137" href="source/net/ipv4/tcp_highspeed.c#L137">137</a> 
<a name="L138" href="source/net/ipv4/tcp_highspeed.c#L138">138</a>                 <b><i>/* Do additive increase */</i></b>
<a name="L139" href="source/net/ipv4/tcp_highspeed.c#L139">139</a>                 if (<a href="ident?i=tp">tp</a>-&gt;snd_cwnd &lt; <a href="ident?i=tp">tp</a>-&gt;snd_cwnd_clamp) {
<a name="L140" href="source/net/ipv4/tcp_highspeed.c#L140">140</a>                         <b><i>/* cwnd = cwnd + a(w) / cwnd */</i></b>
<a name="L141" href="source/net/ipv4/tcp_highspeed.c#L141">141</a>                         <a href="ident?i=tp">tp</a>-&gt;snd_cwnd_cnt += <a href="ident?i=ca">ca</a>-&gt;ai + 1;
<a name="L142" href="source/net/ipv4/tcp_highspeed.c#L142">142</a>                         if (<a href="ident?i=tp">tp</a>-&gt;snd_cwnd_cnt &gt;= <a href="ident?i=tp">tp</a>-&gt;snd_cwnd) {
<a name="L143" href="source/net/ipv4/tcp_highspeed.c#L143">143</a>                                 <a href="ident?i=tp">tp</a>-&gt;snd_cwnd_cnt -= <a href="ident?i=tp">tp</a>-&gt;snd_cwnd;
<a name="L144" href="source/net/ipv4/tcp_highspeed.c#L144">144</a>                                 <a href="ident?i=tp">tp</a>-&gt;snd_cwnd++;
<a name="L145" href="source/net/ipv4/tcp_highspeed.c#L145">145</a>                         }
<a name="L146" href="source/net/ipv4/tcp_highspeed.c#L146">146</a>                 }
<a name="L147" href="source/net/ipv4/tcp_highspeed.c#L147">147</a>         }
<a name="L148" href="source/net/ipv4/tcp_highspeed.c#L148">148</a> }
<a name="L149" href="source/net/ipv4/tcp_highspeed.c#L149">149</a> 
<a name="L150" href="source/net/ipv4/tcp_highspeed.c#L150">150</a> static <a href="ident?i=u32">u32</a> <a href="ident?i=hstcp_ssthresh">hstcp_ssthresh</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L151" href="source/net/ipv4/tcp_highspeed.c#L151">151</a> {
<a name="L152" href="source/net/ipv4/tcp_highspeed.c#L152">152</a>         const struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L153" href="source/net/ipv4/tcp_highspeed.c#L153">153</a>         const struct <a href="ident?i=hstcp">hstcp</a> *<a href="ident?i=ca">ca</a> = <a href="ident?i=inet_csk_ca">inet_csk_ca</a>(sk);
<a name="L154" href="source/net/ipv4/tcp_highspeed.c#L154">154</a> 
<a name="L155" href="source/net/ipv4/tcp_highspeed.c#L155">155</a>         <b><i>/* Do multiplicative decrease */</i></b>
<a name="L156" href="source/net/ipv4/tcp_highspeed.c#L156">156</a>         return <a href="ident?i=max">max</a>(<a href="ident?i=tp">tp</a>-&gt;snd_cwnd - ((<a href="ident?i=tp">tp</a>-&gt;snd_cwnd * <a href="ident?i=hstcp_aimd_vals">hstcp_aimd_vals</a>[<a href="ident?i=ca">ca</a>-&gt;ai].md) &gt;&gt; 8), 2U);
<a name="L157" href="source/net/ipv4/tcp_highspeed.c#L157">157</a> }
<a name="L158" href="source/net/ipv4/tcp_highspeed.c#L158">158</a> 
<a name="L159" href="source/net/ipv4/tcp_highspeed.c#L159">159</a> 
<a name="L160" href="source/net/ipv4/tcp_highspeed.c#L160">160</a> static struct <a href="ident?i=tcp_congestion_ops">tcp_congestion_ops</a> tcp_highspeed <a href="ident?i=__read_mostly">__read_mostly</a> = {
<a name="L161" href="source/net/ipv4/tcp_highspeed.c#L161">161</a>         .<a href="ident?i=init">init</a>           = <a href="ident?i=hstcp_init">hstcp_init</a>,
<a name="L162" href="source/net/ipv4/tcp_highspeed.c#L162">162</a>         .ssthresh       = <a href="ident?i=hstcp_ssthresh">hstcp_ssthresh</a>,
<a name="L163" href="source/net/ipv4/tcp_highspeed.c#L163">163</a>         .cong_avoid     = <a href="ident?i=hstcp_cong_avoid">hstcp_cong_avoid</a>,
<a name="L164" href="source/net/ipv4/tcp_highspeed.c#L164">164</a> 
<a name="L165" href="source/net/ipv4/tcp_highspeed.c#L165">165</a>         .owner          = <a href="ident?i=THIS_MODULE">THIS_MODULE</a>,
<a name="L166" href="source/net/ipv4/tcp_highspeed.c#L166">166</a>         .<a href="ident?i=name">name</a>           = <i>"highspeed"</i>
<a name="L167" href="source/net/ipv4/tcp_highspeed.c#L167">167</a> };
<a name="L168" href="source/net/ipv4/tcp_highspeed.c#L168">168</a> 
<a name="L169" href="source/net/ipv4/tcp_highspeed.c#L169">169</a> static int <a href="ident?i=__init">__init</a> <a href="ident?i=hstcp_register">hstcp_register</a>(void)
<a name="L170" href="source/net/ipv4/tcp_highspeed.c#L170">170</a> {
<a name="L171" href="source/net/ipv4/tcp_highspeed.c#L171">171</a>         <a href="ident?i=BUILD_BUG_ON">BUILD_BUG_ON</a>(sizeof(struct <a href="ident?i=hstcp">hstcp</a>) &gt; <a href="ident?i=ICSK_CA_PRIV_SIZE">ICSK_CA_PRIV_SIZE</a>);
<a name="L172" href="source/net/ipv4/tcp_highspeed.c#L172">172</a>         return <a href="ident?i=tcp_register_congestion_control">tcp_register_congestion_control</a>(&amp;tcp_highspeed);
<a name="L173" href="source/net/ipv4/tcp_highspeed.c#L173">173</a> }
<a name="L174" href="source/net/ipv4/tcp_highspeed.c#L174">174</a> 
<a name="L175" href="source/net/ipv4/tcp_highspeed.c#L175">175</a> static void <a href="ident?i=__exit">__exit</a> <a href="ident?i=hstcp_unregister">hstcp_unregister</a>(void)
<a name="L176" href="source/net/ipv4/tcp_highspeed.c#L176">176</a> {
<a name="L177" href="source/net/ipv4/tcp_highspeed.c#L177">177</a>         <a href="ident?i=tcp_unregister_congestion_control">tcp_unregister_congestion_control</a>(&amp;tcp_highspeed);
<a name="L178" href="source/net/ipv4/tcp_highspeed.c#L178">178</a> }
<a name="L179" href="source/net/ipv4/tcp_highspeed.c#L179">179</a> 
<a name="L180" href="source/net/ipv4/tcp_highspeed.c#L180">180</a> <a href="ident?i=module_init">module_init</a>(<a href="ident?i=hstcp_register">hstcp_register</a>);
<a name="L181" href="source/net/ipv4/tcp_highspeed.c#L181">181</a> <a href="ident?i=module_exit">module_exit</a>(<a href="ident?i=hstcp_unregister">hstcp_unregister</a>);
<a name="L182" href="source/net/ipv4/tcp_highspeed.c#L182">182</a> 
<a name="L183" href="source/net/ipv4/tcp_highspeed.c#L183">183</a> <a href="ident?i=MODULE_AUTHOR">MODULE_AUTHOR</a>(<i>"John Heffner"</i>);
<a name="L184" href="source/net/ipv4/tcp_highspeed.c#L184">184</a> <a href="ident?i=MODULE_LICENSE">MODULE_LICENSE</a>(<i>"GPL"</i>);
<a name="L185" href="source/net/ipv4/tcp_highspeed.c#L185">185</a> <a href="ident?i=MODULE_DESCRIPTION">MODULE_DESCRIPTION</a>(<i>"High Speed TCP"</i>);
<a name="L186" href="source/net/ipv4/tcp_highspeed.c#L186">186</a> </pre></div><p>
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
