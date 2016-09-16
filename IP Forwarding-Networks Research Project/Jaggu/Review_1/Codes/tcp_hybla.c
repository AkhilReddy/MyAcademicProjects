<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title>Linux/net/ipv4/tcp_hybla.c - Linux Cross Reference - Free Electrons</title>
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
		 &nbsp;&bull;&nbsp;<b><i>source navigation</i></b> &nbsp;&bull;&nbsp;<a href="diff/net/ipv4/tcp_hybla.c">diff markup</a> &nbsp;&bull;&nbsp;<a href="ident">identifier search</a> &nbsp;&bull;&nbsp;<a href="search">freetext search</a> &nbsp;&bull;&nbsp;
		</p>
	</div>
</div>

<div id="topbar">
  
  <p>Version: &nbsp;<a href="source/net/ipv4/tcp_hybla.c?v=2.0.40">2.0.40</a>&nbsp;<a href="source/net/ipv4/tcp_hybla.c?v=2.2.26">2.2.26</a>&nbsp;<a href="source/net/ipv4/tcp_hybla.c?v=2.4.37">2.4.37</a>&nbsp;<a href="source/net/ipv4/tcp_hybla.c?v=3.5">3.5</a>&nbsp;<a href="source/net/ipv4/tcp_hybla.c?v=3.6">3.6</a>&nbsp;<a href="source/net/ipv4/tcp_hybla.c?v=3.7">3.7</a>&nbsp;<a href="source/net/ipv4/tcp_hybla.c?v=3.8">3.8</a>&nbsp;<a href="source/net/ipv4/tcp_hybla.c?v=3.9">3.9</a>&nbsp;<a href="source/net/ipv4/tcp_hybla.c?v=3.10">3.10</a>&nbsp;<a href="source/net/ipv4/tcp_hybla.c?v=3.11">3.11</a>&nbsp;<a href="source/net/ipv4/tcp_hybla.c?v=3.12">3.12</a>&nbsp;<a href="source/net/ipv4/tcp_hybla.c?v=3.13">3.13</a>&nbsp;<a href="source/net/ipv4/tcp_hybla.c?v=3.14">3.14</a>&nbsp;<a href="source/net/ipv4/tcp_hybla.c?v=3.15">3.15</a>&nbsp;<a href="source/net/ipv4/tcp_hybla.c?v=3.16">3.16</a>&nbsp;<a href="source/net/ipv4/tcp_hybla.c?v=3.17">3.17</a>&nbsp;<a href="source/net/ipv4/tcp_hybla.c?v=3.18">3.18</a>&nbsp;<a href="source/net/ipv4/tcp_hybla.c?v=3.19">3.19</a>&nbsp;<a href="source/net/ipv4/tcp_hybla.c?v=4.0">4.0</a>&nbsp;<b><i>4.1</i></b></p>
  
</div>

<h1><a href="source/">Linux</a>/<a href="source/net/">net</a>/<a href="source/net/ipv4/">ipv4</a>/<a href="source/net/ipv4/tcp_hybla.c">tcp_hybla.c</a></h1>
<div id="lxrcode"><pre>  <a name="L1" href="source/net/ipv4/tcp_hybla.c#L1">1</a> <b><i>/*</i></b>
  <a name="L2" href="source/net/ipv4/tcp_hybla.c#L2">2</a> <b><i> * TCP HYBLA</i></b>
  <a name="L3" href="source/net/ipv4/tcp_hybla.c#L3">3</a> <b><i> *</i></b>
  <a name="L4" href="source/net/ipv4/tcp_hybla.c#L4">4</a> <b><i> * TCP-HYBLA Congestion control algorithm, based on:</i></b>
  <a name="L5" href="source/net/ipv4/tcp_hybla.c#L5">5</a> <b><i> *   C.Caini, R.Firrincieli, "TCP-Hybla: A TCP Enhancement</i></b>
  <a name="L6" href="source/net/ipv4/tcp_hybla.c#L6">6</a> <b><i> *   for Heterogeneous Networks",</i></b>
  <a name="L7" href="source/net/ipv4/tcp_hybla.c#L7">7</a> <b><i> *   International Journal on satellite Communications,</i></b>
  <a name="L8" href="source/net/ipv4/tcp_hybla.c#L8">8</a> <b><i> *                                     September 2004</i></b>
  <a name="L9" href="source/net/ipv4/tcp_hybla.c#L9">9</a> <b><i> *    Daniele Lacamera</i></b>
 <a name="L10" href="source/net/ipv4/tcp_hybla.c#L10">10</a> <b><i> *    root at danielinux.net</i></b>
 <a name="L11" href="source/net/ipv4/tcp_hybla.c#L11">11</a> <b><i> */</i></b>
 <a name="L12" href="source/net/ipv4/tcp_hybla.c#L12">12</a> 
 <a name="L13" href="source/net/ipv4/tcp_hybla.c#L13">13</a> #include &lt;linux/module.h&gt;
 <a name="L14" href="source/net/ipv4/tcp_hybla.c#L14">14</a> #include &lt;net/tcp.h&gt;
 <a name="L15" href="source/net/ipv4/tcp_hybla.c#L15">15</a> 
 <a name="L16" href="source/net/ipv4/tcp_hybla.c#L16">16</a> <b><i>/* Tcp Hybla structure. */</i></b>
 <a name="L17" href="source/net/ipv4/tcp_hybla.c#L17">17</a> struct <a href="ident?i=hybla">hybla</a> {
 <a name="L18" href="source/net/ipv4/tcp_hybla.c#L18">18</a>         <a href="ident?i=bool">bool</a>  hybla_en;
 <a name="L19" href="source/net/ipv4/tcp_hybla.c#L19">19</a>         <a href="ident?i=u32">u32</a>   snd_cwnd_cents; <b><i>/* Keeps increment values when it is &lt;1, &lt;&lt;7 */</i></b>
 <a name="L20" href="source/net/ipv4/tcp_hybla.c#L20">20</a>         <a href="ident?i=u32">u32</a>   rho;            <b><i>/* Rho parameter, integer part  */</i></b>
 <a name="L21" href="source/net/ipv4/tcp_hybla.c#L21">21</a>         <a href="ident?i=u32">u32</a>   rho2;           <b><i>/* Rho * Rho, integer part */</i></b>
 <a name="L22" href="source/net/ipv4/tcp_hybla.c#L22">22</a>         <a href="ident?i=u32">u32</a>   rho_3ls;        <b><i>/* Rho parameter, &lt;&lt;3 */</i></b>
 <a name="L23" href="source/net/ipv4/tcp_hybla.c#L23">23</a>         <a href="ident?i=u32">u32</a>   rho2_7ls;       <b><i>/* Rho^2, &lt;&lt;7     */</i></b>
 <a name="L24" href="source/net/ipv4/tcp_hybla.c#L24">24</a>         <a href="ident?i=u32">u32</a>   minrtt_us;      <b><i>/* Minimum smoothed round trip time value seen */</i></b>
 <a name="L25" href="source/net/ipv4/tcp_hybla.c#L25">25</a> };
 <a name="L26" href="source/net/ipv4/tcp_hybla.c#L26">26</a> 
 <a name="L27" href="source/net/ipv4/tcp_hybla.c#L27">27</a> <b><i>/* Hybla reference round trip time (default= 1/40 sec = 25 ms), in ms */</i></b>
 <a name="L28" href="source/net/ipv4/tcp_hybla.c#L28">28</a> static int <a href="ident?i=rtt0">rtt0</a> = 25;
 <a name="L29" href="source/net/ipv4/tcp_hybla.c#L29">29</a> <a href="ident?i=module_param">module_param</a>(<a href="ident?i=rtt0">rtt0</a>, int, 0644);
 <a name="L30" href="source/net/ipv4/tcp_hybla.c#L30">30</a> <a href="ident?i=MODULE_PARM_DESC">MODULE_PARM_DESC</a>(<a href="ident?i=rtt0">rtt0</a>, <i>"reference rout trip time (ms)"</i>);
 <a name="L31" href="source/net/ipv4/tcp_hybla.c#L31">31</a> 
 <a name="L32" href="source/net/ipv4/tcp_hybla.c#L32">32</a> <b><i>/* This is called to refresh values for hybla parameters */</i></b>
 <a name="L33" href="source/net/ipv4/tcp_hybla.c#L33">33</a> static inline void <a href="ident?i=hybla_recalc_param">hybla_recalc_param</a> (struct <a href="ident?i=sock">sock</a> *sk)
 <a name="L34" href="source/net/ipv4/tcp_hybla.c#L34">34</a> {
 <a name="L35" href="source/net/ipv4/tcp_hybla.c#L35">35</a>         struct <a href="ident?i=hybla">hybla</a> *<a href="ident?i=ca">ca</a> = <a href="ident?i=inet_csk_ca">inet_csk_ca</a>(sk);
 <a name="L36" href="source/net/ipv4/tcp_hybla.c#L36">36</a> 
 <a name="L37" href="source/net/ipv4/tcp_hybla.c#L37">37</a>         <a href="ident?i=ca">ca</a>-&gt;rho_3ls = <a href="ident?i=max_t">max_t</a>(<a href="ident?i=u32">u32</a>,
 <a name="L38" href="source/net/ipv4/tcp_hybla.c#L38">38</a>                             <a href="ident?i=tcp_sk">tcp_sk</a>(sk)-&gt;srtt_us / (<a href="ident?i=rtt0">rtt0</a> * <a href="ident?i=USEC_PER_MSEC">USEC_PER_MSEC</a>),
 <a name="L39" href="source/net/ipv4/tcp_hybla.c#L39">39</a>                             8U);
 <a name="L40" href="source/net/ipv4/tcp_hybla.c#L40">40</a>         <a href="ident?i=ca">ca</a>-&gt;rho = <a href="ident?i=ca">ca</a>-&gt;rho_3ls &gt;&gt; 3;
 <a name="L41" href="source/net/ipv4/tcp_hybla.c#L41">41</a>         <a href="ident?i=ca">ca</a>-&gt;rho2_7ls = (<a href="ident?i=ca">ca</a>-&gt;rho_3ls * <a href="ident?i=ca">ca</a>-&gt;rho_3ls) &lt;&lt; 1;
 <a name="L42" href="source/net/ipv4/tcp_hybla.c#L42">42</a>         <a href="ident?i=ca">ca</a>-&gt;rho2 = <a href="ident?i=ca">ca</a>-&gt;rho2_7ls &gt;&gt; 7;
 <a name="L43" href="source/net/ipv4/tcp_hybla.c#L43">43</a> }
 <a name="L44" href="source/net/ipv4/tcp_hybla.c#L44">44</a> 
 <a name="L45" href="source/net/ipv4/tcp_hybla.c#L45">45</a> static void <a href="ident?i=hybla_init">hybla_init</a>(struct <a href="ident?i=sock">sock</a> *sk)
 <a name="L46" href="source/net/ipv4/tcp_hybla.c#L46">46</a> {
 <a name="L47" href="source/net/ipv4/tcp_hybla.c#L47">47</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
 <a name="L48" href="source/net/ipv4/tcp_hybla.c#L48">48</a>         struct <a href="ident?i=hybla">hybla</a> *<a href="ident?i=ca">ca</a> = <a href="ident?i=inet_csk_ca">inet_csk_ca</a>(sk);
 <a name="L49" href="source/net/ipv4/tcp_hybla.c#L49">49</a> 
 <a name="L50" href="source/net/ipv4/tcp_hybla.c#L50">50</a>         <a href="ident?i=ca">ca</a>-&gt;rho = 0;
 <a name="L51" href="source/net/ipv4/tcp_hybla.c#L51">51</a>         <a href="ident?i=ca">ca</a>-&gt;rho2 = 0;
 <a name="L52" href="source/net/ipv4/tcp_hybla.c#L52">52</a>         <a href="ident?i=ca">ca</a>-&gt;rho_3ls = 0;
 <a name="L53" href="source/net/ipv4/tcp_hybla.c#L53">53</a>         <a href="ident?i=ca">ca</a>-&gt;rho2_7ls = 0;
 <a name="L54" href="source/net/ipv4/tcp_hybla.c#L54">54</a>         <a href="ident?i=ca">ca</a>-&gt;snd_cwnd_cents = 0;
 <a name="L55" href="source/net/ipv4/tcp_hybla.c#L55">55</a>         <a href="ident?i=ca">ca</a>-&gt;hybla_en = <a href="ident?i=true">true</a>;
 <a name="L56" href="source/net/ipv4/tcp_hybla.c#L56">56</a>         <a href="ident?i=tp">tp</a>-&gt;snd_cwnd = 2;
 <a name="L57" href="source/net/ipv4/tcp_hybla.c#L57">57</a>         <a href="ident?i=tp">tp</a>-&gt;snd_cwnd_clamp = 65535;
 <a name="L58" href="source/net/ipv4/tcp_hybla.c#L58">58</a> 
 <a name="L59" href="source/net/ipv4/tcp_hybla.c#L59">59</a>         <b><i>/* 1st Rho measurement based on initial srtt */</i></b>
 <a name="L60" href="source/net/ipv4/tcp_hybla.c#L60">60</a>         <a href="ident?i=hybla_recalc_param">hybla_recalc_param</a>(sk);
 <a name="L61" href="source/net/ipv4/tcp_hybla.c#L61">61</a> 
 <a name="L62" href="source/net/ipv4/tcp_hybla.c#L62">62</a>         <b><i>/* set minimum rtt as this is the 1st ever seen */</i></b>
 <a name="L63" href="source/net/ipv4/tcp_hybla.c#L63">63</a>         <a href="ident?i=ca">ca</a>-&gt;minrtt_us = <a href="ident?i=tp">tp</a>-&gt;srtt_us;
 <a name="L64" href="source/net/ipv4/tcp_hybla.c#L64">64</a>         <a href="ident?i=tp">tp</a>-&gt;snd_cwnd = <a href="ident?i=ca">ca</a>-&gt;rho;
 <a name="L65" href="source/net/ipv4/tcp_hybla.c#L65">65</a> }
 <a name="L66" href="source/net/ipv4/tcp_hybla.c#L66">66</a> 
 <a name="L67" href="source/net/ipv4/tcp_hybla.c#L67">67</a> static void <a href="ident?i=hybla_state">hybla_state</a>(struct <a href="ident?i=sock">sock</a> *sk, <a href="ident?i=u8">u8</a> ca_state)
 <a name="L68" href="source/net/ipv4/tcp_hybla.c#L68">68</a> {
 <a name="L69" href="source/net/ipv4/tcp_hybla.c#L69">69</a>         struct <a href="ident?i=hybla">hybla</a> *<a href="ident?i=ca">ca</a> = <a href="ident?i=inet_csk_ca">inet_csk_ca</a>(sk);
 <a name="L70" href="source/net/ipv4/tcp_hybla.c#L70">70</a> 
 <a name="L71" href="source/net/ipv4/tcp_hybla.c#L71">71</a>         <a href="ident?i=ca">ca</a>-&gt;hybla_en = (ca_state == TCP_CA_Open);
 <a name="L72" href="source/net/ipv4/tcp_hybla.c#L72">72</a> }
 <a name="L73" href="source/net/ipv4/tcp_hybla.c#L73">73</a> 
 <a name="L74" href="source/net/ipv4/tcp_hybla.c#L74">74</a> static inline <a href="ident?i=u32">u32</a> <a href="ident?i=hybla_fraction">hybla_fraction</a>(<a href="ident?i=u32">u32</a> odds)
 <a name="L75" href="source/net/ipv4/tcp_hybla.c#L75">75</a> {
 <a name="L76" href="source/net/ipv4/tcp_hybla.c#L76">76</a>         static const <a href="ident?i=u32">u32</a> fractions[] = {
 <a name="L77" href="source/net/ipv4/tcp_hybla.c#L77">77</a>                 128, 139, 152, 165, 181, 197, 215, 234,
 <a name="L78" href="source/net/ipv4/tcp_hybla.c#L78">78</a>         };
 <a name="L79" href="source/net/ipv4/tcp_hybla.c#L79">79</a> 
 <a name="L80" href="source/net/ipv4/tcp_hybla.c#L80">80</a>         return (odds &lt; <a href="ident?i=ARRAY_SIZE">ARRAY_SIZE</a>(fractions)) ? fractions[odds] : 128;
 <a name="L81" href="source/net/ipv4/tcp_hybla.c#L81">81</a> }
 <a name="L82" href="source/net/ipv4/tcp_hybla.c#L82">82</a> 
 <a name="L83" href="source/net/ipv4/tcp_hybla.c#L83">83</a> <b><i>/* TCP Hybla main routine.</i></b>
 <a name="L84" href="source/net/ipv4/tcp_hybla.c#L84">84</a> <b><i> * This is the algorithm behavior:</i></b>
 <a name="L85" href="source/net/ipv4/tcp_hybla.c#L85">85</a> <b><i> *     o Recalc Hybla parameters if min_rtt has changed</i></b>
 <a name="L86" href="source/net/ipv4/tcp_hybla.c#L86">86</a> <b><i> *     o Give cwnd a new value based on the model proposed</i></b>
 <a name="L87" href="source/net/ipv4/tcp_hybla.c#L87">87</a> <b><i> *     o remember increments &lt;1</i></b>
 <a name="L88" href="source/net/ipv4/tcp_hybla.c#L88">88</a> <b><i> */</i></b>
 <a name="L89" href="source/net/ipv4/tcp_hybla.c#L89">89</a> static void <a href="ident?i=hybla_cong_avoid">hybla_cong_avoid</a>(struct <a href="ident?i=sock">sock</a> *sk, <a href="ident?i=u32">u32</a> ack, <a href="ident?i=u32">u32</a> acked)
 <a name="L90" href="source/net/ipv4/tcp_hybla.c#L90">90</a> {
 <a name="L91" href="source/net/ipv4/tcp_hybla.c#L91">91</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
 <a name="L92" href="source/net/ipv4/tcp_hybla.c#L92">92</a>         struct <a href="ident?i=hybla">hybla</a> *<a href="ident?i=ca">ca</a> = <a href="ident?i=inet_csk_ca">inet_csk_ca</a>(sk);
 <a name="L93" href="source/net/ipv4/tcp_hybla.c#L93">93</a>         <a href="ident?i=u32">u32</a> increment, odd, rho_fractions;
 <a name="L94" href="source/net/ipv4/tcp_hybla.c#L94">94</a>         int is_slowstart = 0;
 <a name="L95" href="source/net/ipv4/tcp_hybla.c#L95">95</a> 
 <a name="L96" href="source/net/ipv4/tcp_hybla.c#L96">96</a>         <b><i>/*  Recalculate rho only if this srtt is the lowest */</i></b>
 <a name="L97" href="source/net/ipv4/tcp_hybla.c#L97">97</a>         if (<a href="ident?i=tp">tp</a>-&gt;srtt_us &lt; <a href="ident?i=ca">ca</a>-&gt;minrtt_us) {
 <a name="L98" href="source/net/ipv4/tcp_hybla.c#L98">98</a>                 <a href="ident?i=hybla_recalc_param">hybla_recalc_param</a>(sk);
 <a name="L99" href="source/net/ipv4/tcp_hybla.c#L99">99</a>                 <a href="ident?i=ca">ca</a>-&gt;minrtt_us = <a href="ident?i=tp">tp</a>-&gt;srtt_us;
<a name="L100" href="source/net/ipv4/tcp_hybla.c#L100">100</a>         }
<a name="L101" href="source/net/ipv4/tcp_hybla.c#L101">101</a> 
<a name="L102" href="source/net/ipv4/tcp_hybla.c#L102">102</a>         if (!<a href="ident?i=tcp_is_cwnd_limited">tcp_is_cwnd_limited</a>(sk))
<a name="L103" href="source/net/ipv4/tcp_hybla.c#L103">103</a>                 return;
<a name="L104" href="source/net/ipv4/tcp_hybla.c#L104">104</a> 
<a name="L105" href="source/net/ipv4/tcp_hybla.c#L105">105</a>         if (!<a href="ident?i=ca">ca</a>-&gt;hybla_en) {
<a name="L106" href="source/net/ipv4/tcp_hybla.c#L106">106</a>                 <a href="ident?i=tcp_reno_cong_avoid">tcp_reno_cong_avoid</a>(sk, ack, acked);
<a name="L107" href="source/net/ipv4/tcp_hybla.c#L107">107</a>                 return;
<a name="L108" href="source/net/ipv4/tcp_hybla.c#L108">108</a>         }
<a name="L109" href="source/net/ipv4/tcp_hybla.c#L109">109</a> 
<a name="L110" href="source/net/ipv4/tcp_hybla.c#L110">110</a>         if (<a href="ident?i=ca">ca</a>-&gt;rho == 0)
<a name="L111" href="source/net/ipv4/tcp_hybla.c#L111">111</a>                 <a href="ident?i=hybla_recalc_param">hybla_recalc_param</a>(sk);
<a name="L112" href="source/net/ipv4/tcp_hybla.c#L112">112</a> 
<a name="L113" href="source/net/ipv4/tcp_hybla.c#L113">113</a>         rho_fractions = <a href="ident?i=ca">ca</a>-&gt;rho_3ls - (<a href="ident?i=ca">ca</a>-&gt;rho &lt;&lt; 3);
<a name="L114" href="source/net/ipv4/tcp_hybla.c#L114">114</a> 
<a name="L115" href="source/net/ipv4/tcp_hybla.c#L115">115</a>         if (<a href="ident?i=tp">tp</a>-&gt;snd_cwnd &lt; <a href="ident?i=tp">tp</a>-&gt;snd_ssthresh) {
<a name="L116" href="source/net/ipv4/tcp_hybla.c#L116">116</a>                 <b><i>/*</i></b>
<a name="L117" href="source/net/ipv4/tcp_hybla.c#L117">117</a> <b><i>                 * slow start</i></b>
<a name="L118" href="source/net/ipv4/tcp_hybla.c#L118">118</a> <b><i>                 *      INC = 2^RHO - 1</i></b>
<a name="L119" href="source/net/ipv4/tcp_hybla.c#L119">119</a> <b><i>                 * This is done by splitting the rho parameter</i></b>
<a name="L120" href="source/net/ipv4/tcp_hybla.c#L120">120</a> <b><i>                 * into 2 parts: an integer part and a fraction part.</i></b>
<a name="L121" href="source/net/ipv4/tcp_hybla.c#L121">121</a> <b><i>                 * Inrement&lt;&lt;7 is estimated by doing:</i></b>
<a name="L122" href="source/net/ipv4/tcp_hybla.c#L122">122</a> <b><i>                 *             [2^(int+fract)]&lt;&lt;7</i></b>
<a name="L123" href="source/net/ipv4/tcp_hybla.c#L123">123</a> <b><i>                 * that is equal to:</i></b>
<a name="L124" href="source/net/ipv4/tcp_hybla.c#L124">124</a> <b><i>                 *             (2^int)  *  [(2^fract) &lt;&lt;7]</i></b>
<a name="L125" href="source/net/ipv4/tcp_hybla.c#L125">125</a> <b><i>                 * 2^int is straightly computed as 1&lt;&lt;int,</i></b>
<a name="L126" href="source/net/ipv4/tcp_hybla.c#L126">126</a> <b><i>                 * while we will use hybla_slowstart_fraction_increment() to</i></b>
<a name="L127" href="source/net/ipv4/tcp_hybla.c#L127">127</a> <b><i>                 * calculate 2^fract in a &lt;&lt;7 value.</i></b>
<a name="L128" href="source/net/ipv4/tcp_hybla.c#L128">128</a> <b><i>                 */</i></b>
<a name="L129" href="source/net/ipv4/tcp_hybla.c#L129">129</a>                 is_slowstart = 1;
<a name="L130" href="source/net/ipv4/tcp_hybla.c#L130">130</a>                 increment = ((1 &lt;&lt; <a href="ident?i=min">min</a>(<a href="ident?i=ca">ca</a>-&gt;rho, 16U)) *
<a name="L131" href="source/net/ipv4/tcp_hybla.c#L131">131</a>                         <a href="ident?i=hybla_fraction">hybla_fraction</a>(rho_fractions)) - 128;
<a name="L132" href="source/net/ipv4/tcp_hybla.c#L132">132</a>         } else {
<a name="L133" href="source/net/ipv4/tcp_hybla.c#L133">133</a>                 <b><i>/*</i></b>
<a name="L134" href="source/net/ipv4/tcp_hybla.c#L134">134</a> <b><i>                 * congestion avoidance</i></b>
<a name="L135" href="source/net/ipv4/tcp_hybla.c#L135">135</a> <b><i>                 * INC = RHO^2 / W</i></b>
<a name="L136" href="source/net/ipv4/tcp_hybla.c#L136">136</a> <b><i>                 * as long as increment is estimated as (rho&lt;&lt;7)/window</i></b>
<a name="L137" href="source/net/ipv4/tcp_hybla.c#L137">137</a> <b><i>                 * it already is &lt;&lt;7 and we can easily count its fractions.</i></b>
<a name="L138" href="source/net/ipv4/tcp_hybla.c#L138">138</a> <b><i>                 */</i></b>
<a name="L139" href="source/net/ipv4/tcp_hybla.c#L139">139</a>                 increment = <a href="ident?i=ca">ca</a>-&gt;rho2_7ls / <a href="ident?i=tp">tp</a>-&gt;snd_cwnd;
<a name="L140" href="source/net/ipv4/tcp_hybla.c#L140">140</a>                 if (increment &lt; 128)
<a name="L141" href="source/net/ipv4/tcp_hybla.c#L141">141</a>                         <a href="ident?i=tp">tp</a>-&gt;snd_cwnd_cnt++;
<a name="L142" href="source/net/ipv4/tcp_hybla.c#L142">142</a>         }
<a name="L143" href="source/net/ipv4/tcp_hybla.c#L143">143</a> 
<a name="L144" href="source/net/ipv4/tcp_hybla.c#L144">144</a>         odd = increment % 128;
<a name="L145" href="source/net/ipv4/tcp_hybla.c#L145">145</a>         <a href="ident?i=tp">tp</a>-&gt;snd_cwnd += increment &gt;&gt; 7;
<a name="L146" href="source/net/ipv4/tcp_hybla.c#L146">146</a>         <a href="ident?i=ca">ca</a>-&gt;snd_cwnd_cents += odd;
<a name="L147" href="source/net/ipv4/tcp_hybla.c#L147">147</a> 
<a name="L148" href="source/net/ipv4/tcp_hybla.c#L148">148</a>         <b><i>/* check when fractions goes &gt;=128 and increase cwnd by 1. */</i></b>
<a name="L149" href="source/net/ipv4/tcp_hybla.c#L149">149</a>         while (<a href="ident?i=ca">ca</a>-&gt;snd_cwnd_cents &gt;= 128) {
<a name="L150" href="source/net/ipv4/tcp_hybla.c#L150">150</a>                 <a href="ident?i=tp">tp</a>-&gt;snd_cwnd++;
<a name="L151" href="source/net/ipv4/tcp_hybla.c#L151">151</a>                 <a href="ident?i=ca">ca</a>-&gt;snd_cwnd_cents -= 128;
<a name="L152" href="source/net/ipv4/tcp_hybla.c#L152">152</a>                 <a href="ident?i=tp">tp</a>-&gt;snd_cwnd_cnt = 0;
<a name="L153" href="source/net/ipv4/tcp_hybla.c#L153">153</a>         }
<a name="L154" href="source/net/ipv4/tcp_hybla.c#L154">154</a>         <b><i>/* check when cwnd has not been incremented for a while */</i></b>
<a name="L155" href="source/net/ipv4/tcp_hybla.c#L155">155</a>         if (increment == 0 &amp;&amp; odd == 0 &amp;&amp; <a href="ident?i=tp">tp</a>-&gt;snd_cwnd_cnt &gt;= <a href="ident?i=tp">tp</a>-&gt;snd_cwnd) {
<a name="L156" href="source/net/ipv4/tcp_hybla.c#L156">156</a>                 <a href="ident?i=tp">tp</a>-&gt;snd_cwnd++;
<a name="L157" href="source/net/ipv4/tcp_hybla.c#L157">157</a>                 <a href="ident?i=tp">tp</a>-&gt;snd_cwnd_cnt = 0;
<a name="L158" href="source/net/ipv4/tcp_hybla.c#L158">158</a>         }
<a name="L159" href="source/net/ipv4/tcp_hybla.c#L159">159</a>         <b><i>/* clamp down slowstart cwnd to ssthresh value. */</i></b>
<a name="L160" href="source/net/ipv4/tcp_hybla.c#L160">160</a>         if (is_slowstart)
<a name="L161" href="source/net/ipv4/tcp_hybla.c#L161">161</a>                 <a href="ident?i=tp">tp</a>-&gt;snd_cwnd = <a href="ident?i=min">min</a>(<a href="ident?i=tp">tp</a>-&gt;snd_cwnd, <a href="ident?i=tp">tp</a>-&gt;snd_ssthresh);
<a name="L162" href="source/net/ipv4/tcp_hybla.c#L162">162</a> 
<a name="L163" href="source/net/ipv4/tcp_hybla.c#L163">163</a>         <a href="ident?i=tp">tp</a>-&gt;snd_cwnd = <a href="ident?i=min_t">min_t</a>(<a href="ident?i=u32">u32</a>, <a href="ident?i=tp">tp</a>-&gt;snd_cwnd, <a href="ident?i=tp">tp</a>-&gt;snd_cwnd_clamp);
<a name="L164" href="source/net/ipv4/tcp_hybla.c#L164">164</a> }
<a name="L165" href="source/net/ipv4/tcp_hybla.c#L165">165</a> 
<a name="L166" href="source/net/ipv4/tcp_hybla.c#L166">166</a> static struct <a href="ident?i=tcp_congestion_ops">tcp_congestion_ops</a> tcp_hybla <a href="ident?i=__read_mostly">__read_mostly</a> = {
<a name="L167" href="source/net/ipv4/tcp_hybla.c#L167">167</a>         .<a href="ident?i=init">init</a>           = <a href="ident?i=hybla_init">hybla_init</a>,
<a name="L168" href="source/net/ipv4/tcp_hybla.c#L168">168</a>         .ssthresh       = <a href="ident?i=tcp_reno_ssthresh">tcp_reno_ssthresh</a>,
<a name="L169" href="source/net/ipv4/tcp_hybla.c#L169">169</a>         .cong_avoid     = <a href="ident?i=hybla_cong_avoid">hybla_cong_avoid</a>,
<a name="L170" href="source/net/ipv4/tcp_hybla.c#L170">170</a>         .<a href="ident?i=set_state">set_state</a>      = <a href="ident?i=hybla_state">hybla_state</a>,
<a name="L171" href="source/net/ipv4/tcp_hybla.c#L171">171</a> 
<a name="L172" href="source/net/ipv4/tcp_hybla.c#L172">172</a>         .owner          = <a href="ident?i=THIS_MODULE">THIS_MODULE</a>,
<a name="L173" href="source/net/ipv4/tcp_hybla.c#L173">173</a>         .<a href="ident?i=name">name</a>           = <i>"hybla"</i>
<a name="L174" href="source/net/ipv4/tcp_hybla.c#L174">174</a> };
<a name="L175" href="source/net/ipv4/tcp_hybla.c#L175">175</a> 
<a name="L176" href="source/net/ipv4/tcp_hybla.c#L176">176</a> static int <a href="ident?i=__init">__init</a> <a href="ident?i=hybla_register">hybla_register</a>(void)
<a name="L177" href="source/net/ipv4/tcp_hybla.c#L177">177</a> {
<a name="L178" href="source/net/ipv4/tcp_hybla.c#L178">178</a>         <a href="ident?i=BUILD_BUG_ON">BUILD_BUG_ON</a>(sizeof(struct <a href="ident?i=hybla">hybla</a>) &gt; <a href="ident?i=ICSK_CA_PRIV_SIZE">ICSK_CA_PRIV_SIZE</a>);
<a name="L179" href="source/net/ipv4/tcp_hybla.c#L179">179</a>         return <a href="ident?i=tcp_register_congestion_control">tcp_register_congestion_control</a>(&amp;tcp_hybla);
<a name="L180" href="source/net/ipv4/tcp_hybla.c#L180">180</a> }
<a name="L181" href="source/net/ipv4/tcp_hybla.c#L181">181</a> 
<a name="L182" href="source/net/ipv4/tcp_hybla.c#L182">182</a> static void <a href="ident?i=__exit">__exit</a> <a href="ident?i=hybla_unregister">hybla_unregister</a>(void)
<a name="L183" href="source/net/ipv4/tcp_hybla.c#L183">183</a> {
<a name="L184" href="source/net/ipv4/tcp_hybla.c#L184">184</a>         <a href="ident?i=tcp_unregister_congestion_control">tcp_unregister_congestion_control</a>(&amp;tcp_hybla);
<a name="L185" href="source/net/ipv4/tcp_hybla.c#L185">185</a> }
<a name="L186" href="source/net/ipv4/tcp_hybla.c#L186">186</a> 
<a name="L187" href="source/net/ipv4/tcp_hybla.c#L187">187</a> <a href="ident?i=module_init">module_init</a>(<a href="ident?i=hybla_register">hybla_register</a>);
<a name="L188" href="source/net/ipv4/tcp_hybla.c#L188">188</a> <a href="ident?i=module_exit">module_exit</a>(<a href="ident?i=hybla_unregister">hybla_unregister</a>);
<a name="L189" href="source/net/ipv4/tcp_hybla.c#L189">189</a> 
<a name="L190" href="source/net/ipv4/tcp_hybla.c#L190">190</a> <a href="ident?i=MODULE_AUTHOR">MODULE_AUTHOR</a>(<i>"Daniele Lacamera"</i>);
<a name="L191" href="source/net/ipv4/tcp_hybla.c#L191">191</a> <a href="ident?i=MODULE_LICENSE">MODULE_LICENSE</a>(<i>"GPL"</i>);
<a name="L192" href="source/net/ipv4/tcp_hybla.c#L192">192</a> <a href="ident?i=MODULE_DESCRIPTION">MODULE_DESCRIPTION</a>(<i>"TCP Hybla"</i>);
<a name="L193" href="source/net/ipv4/tcp_hybla.c#L193">193</a> </pre></div><p>
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
