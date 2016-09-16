<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title>Linux/net/ipv4/tcp_dctcp.c - Linux Cross Reference - Free Electrons</title>
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
		 &nbsp;&bull;&nbsp;<b><i>source navigation</i></b> &nbsp;&bull;&nbsp;<a href="diff/net/ipv4/tcp_dctcp.c">diff markup</a> &nbsp;&bull;&nbsp;<a href="ident">identifier search</a> &nbsp;&bull;&nbsp;<a href="search">freetext search</a> &nbsp;&bull;&nbsp;
		</p>
	</div>
</div>

<div id="topbar">
  
  <p>Version: &nbsp;<a href="source/net/ipv4/tcp_dctcp.c?v=2.0.40">2.0.40</a>&nbsp;<a href="source/net/ipv4/tcp_dctcp.c?v=2.2.26">2.2.26</a>&nbsp;<a href="source/net/ipv4/tcp_dctcp.c?v=2.4.37">2.4.37</a>&nbsp;<a href="source/net/ipv4/tcp_dctcp.c?v=3.5">3.5</a>&nbsp;<a href="source/net/ipv4/tcp_dctcp.c?v=3.6">3.6</a>&nbsp;<a href="source/net/ipv4/tcp_dctcp.c?v=3.7">3.7</a>&nbsp;<a href="source/net/ipv4/tcp_dctcp.c?v=3.8">3.8</a>&nbsp;<a href="source/net/ipv4/tcp_dctcp.c?v=3.9">3.9</a>&nbsp;<a href="source/net/ipv4/tcp_dctcp.c?v=3.10">3.10</a>&nbsp;<a href="source/net/ipv4/tcp_dctcp.c?v=3.11">3.11</a>&nbsp;<a href="source/net/ipv4/tcp_dctcp.c?v=3.12">3.12</a>&nbsp;<a href="source/net/ipv4/tcp_dctcp.c?v=3.13">3.13</a>&nbsp;<a href="source/net/ipv4/tcp_dctcp.c?v=3.14">3.14</a>&nbsp;<a href="source/net/ipv4/tcp_dctcp.c?v=3.15">3.15</a>&nbsp;<a href="source/net/ipv4/tcp_dctcp.c?v=3.16">3.16</a>&nbsp;<a href="source/net/ipv4/tcp_dctcp.c?v=3.17">3.17</a>&nbsp;<a href="source/net/ipv4/tcp_dctcp.c?v=3.18">3.18</a>&nbsp;<a href="source/net/ipv4/tcp_dctcp.c?v=3.19">3.19</a>&nbsp;<a href="source/net/ipv4/tcp_dctcp.c?v=4.0">4.0</a>&nbsp;<b><i>4.1</i></b></p>
  
</div>

<h1><a href="source/">Linux</a>/<a href="source/net/">net</a>/<a href="source/net/ipv4/">ipv4</a>/<a href="source/net/ipv4/tcp_dctcp.c">tcp_dctcp.c</a></h1>
<div id="lxrcode"><pre>  <a name="L1" href="source/net/ipv4/tcp_dctcp.c#L1">1</a> <b><i>/* DataCenter TCP (DCTCP) congestion control.</i></b>
  <a name="L2" href="source/net/ipv4/tcp_dctcp.c#L2">2</a> <b><i> *</i></b>
  <a name="L3" href="source/net/ipv4/tcp_dctcp.c#L3">3</a> <b><i> * <a href="http://simula.stanford.edu/~alizade/Site/DCTCP.html">http://simula.stanford.edu/~alizade/Site/DCTCP.html</a></i></b>
  <a name="L4" href="source/net/ipv4/tcp_dctcp.c#L4">4</a> <b><i> *</i></b>
  <a name="L5" href="source/net/ipv4/tcp_dctcp.c#L5">5</a> <b><i> * This is an implementation of DCTCP over Reno, an enhancement to the</i></b>
  <a name="L6" href="source/net/ipv4/tcp_dctcp.c#L6">6</a> <b><i> * TCP congestion control algorithm designed for data centers. DCTCP</i></b>
  <a name="L7" href="source/net/ipv4/tcp_dctcp.c#L7">7</a> <b><i> * leverages Explicit Congestion Notification (ECN) in the network to</i></b>
  <a name="L8" href="source/net/ipv4/tcp_dctcp.c#L8">8</a> <b><i> * provide multi-bit feedback to the end hosts. DCTCP's goal is to meet</i></b>
  <a name="L9" href="source/net/ipv4/tcp_dctcp.c#L9">9</a> <b><i> * the following three data center transport requirements:</i></b>
 <a name="L10" href="source/net/ipv4/tcp_dctcp.c#L10">10</a> <b><i> *</i></b>
 <a name="L11" href="source/net/ipv4/tcp_dctcp.c#L11">11</a> <b><i> *  - High burst tolerance (incast due to partition/aggregate)</i></b>
 <a name="L12" href="source/net/ipv4/tcp_dctcp.c#L12">12</a> <b><i> *  - Low latency (short flows, queries)</i></b>
 <a name="L13" href="source/net/ipv4/tcp_dctcp.c#L13">13</a> <b><i> *  - High throughput (continuous data updates, large file transfers)</i></b>
 <a name="L14" href="source/net/ipv4/tcp_dctcp.c#L14">14</a> <b><i> *    with commodity shallow buffered switches</i></b>
 <a name="L15" href="source/net/ipv4/tcp_dctcp.c#L15">15</a> <b><i> *</i></b>
 <a name="L16" href="source/net/ipv4/tcp_dctcp.c#L16">16</a> <b><i> * The algorithm is described in detail in the following two papers:</i></b>
 <a name="L17" href="source/net/ipv4/tcp_dctcp.c#L17">17</a> <b><i> *</i></b>
 <a name="L18" href="source/net/ipv4/tcp_dctcp.c#L18">18</a> <b><i> * 1) Mohammad Alizadeh, Albert Greenberg, David A. Maltz, Jitendra Padhye,</i></b>
 <a name="L19" href="source/net/ipv4/tcp_dctcp.c#L19">19</a> <b><i> *    Parveen Patel, Balaji Prabhakar, Sudipta Sengupta, and Murari Sridharan:</i></b>
 <a name="L20" href="source/net/ipv4/tcp_dctcp.c#L20">20</a> <b><i> *      "Data Center TCP (DCTCP)", Data Center Networks session</i></b>
 <a name="L21" href="source/net/ipv4/tcp_dctcp.c#L21">21</a> <b><i> *      Proc. ACM SIGCOMM, New Delhi, 2010.</i></b>
 <a name="L22" href="source/net/ipv4/tcp_dctcp.c#L22">22</a> <b><i> *   <a href="http://simula.stanford.edu/~alizade/Site/DCTCP_files/dctcp-final.pdf">http://simula.stanford.edu/~alizade/Site/DCTCP_files/dctcp-final.pdf</a></i></b>
 <a name="L23" href="source/net/ipv4/tcp_dctcp.c#L23">23</a> <b><i> *</i></b>
 <a name="L24" href="source/net/ipv4/tcp_dctcp.c#L24">24</a> <b><i> * 2) Mohammad Alizadeh, Adel Javanmard, and Balaji Prabhakar:</i></b>
 <a name="L25" href="source/net/ipv4/tcp_dctcp.c#L25">25</a> <b><i> *      "Analysis of DCTCP: Stability, Convergence, and Fairness"</i></b>
 <a name="L26" href="source/net/ipv4/tcp_dctcp.c#L26">26</a> <b><i> *      Proc. ACM SIGMETRICS, San Jose, 2011.</i></b>
 <a name="L27" href="source/net/ipv4/tcp_dctcp.c#L27">27</a> <b><i> *   <a href="http://simula.stanford.edu/~alizade/Site/DCTCP_files/dctcp_analysis-full.pdf">http://simula.stanford.edu/~alizade/Site/DCTCP_files/dctcp_analysis-full.pdf</a></i></b>
 <a name="L28" href="source/net/ipv4/tcp_dctcp.c#L28">28</a> <b><i> *</i></b>
 <a name="L29" href="source/net/ipv4/tcp_dctcp.c#L29">29</a> <b><i> * Initial prototype from Abdul Kabbani, Masato Yasuda and Mohammad Alizadeh.</i></b>
 <a name="L30" href="source/net/ipv4/tcp_dctcp.c#L30">30</a> <b><i> *</i></b>
 <a name="L31" href="source/net/ipv4/tcp_dctcp.c#L31">31</a> <b><i> * Authors:</i></b>
 <a name="L32" href="source/net/ipv4/tcp_dctcp.c#L32">32</a> <b><i> *</i></b>
 <a name="L33" href="source/net/ipv4/tcp_dctcp.c#L33">33</a> <b><i> *      Daniel Borkmann &lt;dborkman@redhat.com&gt;</i></b>
 <a name="L34" href="source/net/ipv4/tcp_dctcp.c#L34">34</a> <b><i> *      Florian Westphal &lt;fw@strlen.de&gt;</i></b>
 <a name="L35" href="source/net/ipv4/tcp_dctcp.c#L35">35</a> <b><i> *      Glenn Judd &lt;glenn.judd@morganstanley.com&gt;</i></b>
 <a name="L36" href="source/net/ipv4/tcp_dctcp.c#L36">36</a> <b><i> *</i></b>
 <a name="L37" href="source/net/ipv4/tcp_dctcp.c#L37">37</a> <b><i> * This program is free software; you can redistribute it and/or modify</i></b>
 <a name="L38" href="source/net/ipv4/tcp_dctcp.c#L38">38</a> <b><i> * it under the terms of the GNU General Public License as published by</i></b>
 <a name="L39" href="source/net/ipv4/tcp_dctcp.c#L39">39</a> <b><i> * the Free Software Foundation; either version 2 of the License, or (at</i></b>
 <a name="L40" href="source/net/ipv4/tcp_dctcp.c#L40">40</a> <b><i> * your option) any later version.</i></b>
 <a name="L41" href="source/net/ipv4/tcp_dctcp.c#L41">41</a> <b><i> */</i></b>
 <a name="L42" href="source/net/ipv4/tcp_dctcp.c#L42">42</a> 
 <a name="L43" href="source/net/ipv4/tcp_dctcp.c#L43">43</a> #include &lt;linux/module.h&gt;
 <a name="L44" href="source/net/ipv4/tcp_dctcp.c#L44">44</a> #include &lt;linux/mm.h&gt;
 <a name="L45" href="source/net/ipv4/tcp_dctcp.c#L45">45</a> #include &lt;net/tcp.h&gt;
 <a name="L46" href="source/net/ipv4/tcp_dctcp.c#L46">46</a> #include &lt;linux/inet_diag.h&gt;
 <a name="L47" href="source/net/ipv4/tcp_dctcp.c#L47">47</a> 
 <a name="L48" href="source/net/ipv4/tcp_dctcp.c#L48">48</a> #define <a href="ident?i=DCTCP_MAX_ALPHA">DCTCP_MAX_ALPHA</a> 1024U
 <a name="L49" href="source/net/ipv4/tcp_dctcp.c#L49">49</a> 
 <a name="L50" href="source/net/ipv4/tcp_dctcp.c#L50">50</a> struct <a href="ident?i=dctcp">dctcp</a> {
 <a name="L51" href="source/net/ipv4/tcp_dctcp.c#L51">51</a>         <a href="ident?i=u32">u32</a> acked_bytes_ecn;
 <a name="L52" href="source/net/ipv4/tcp_dctcp.c#L52">52</a>         <a href="ident?i=u32">u32</a> acked_bytes_total;
 <a name="L53" href="source/net/ipv4/tcp_dctcp.c#L53">53</a>         <a href="ident?i=u32">u32</a> prior_snd_una;
 <a name="L54" href="source/net/ipv4/tcp_dctcp.c#L54">54</a>         <a href="ident?i=u32">u32</a> prior_rcv_nxt;
 <a name="L55" href="source/net/ipv4/tcp_dctcp.c#L55">55</a>         <a href="ident?i=u32">u32</a> dctcp_alpha;
 <a name="L56" href="source/net/ipv4/tcp_dctcp.c#L56">56</a>         <a href="ident?i=u32">u32</a> next_seq;
 <a name="L57" href="source/net/ipv4/tcp_dctcp.c#L57">57</a>         <a href="ident?i=u32">u32</a> ce_state;
 <a name="L58" href="source/net/ipv4/tcp_dctcp.c#L58">58</a>         <a href="ident?i=u32">u32</a> delayed_ack_reserved;
 <a name="L59" href="source/net/ipv4/tcp_dctcp.c#L59">59</a> };
 <a name="L60" href="source/net/ipv4/tcp_dctcp.c#L60">60</a> 
 <a name="L61" href="source/net/ipv4/tcp_dctcp.c#L61">61</a> static unsigned int dctcp_shift_g <a href="ident?i=__read_mostly">__read_mostly</a> = 4; <b><i>/* g = 1/2^4 */</i></b>
 <a name="L62" href="source/net/ipv4/tcp_dctcp.c#L62">62</a> <a href="ident?i=module_param">module_param</a>(dctcp_shift_g, <a href="ident?i=uint">uint</a>, 0644);
 <a name="L63" href="source/net/ipv4/tcp_dctcp.c#L63">63</a> <a href="ident?i=MODULE_PARM_DESC">MODULE_PARM_DESC</a>(dctcp_shift_g, <i>"parameter g for updating dctcp_alpha"</i>);
 <a name="L64" href="source/net/ipv4/tcp_dctcp.c#L64">64</a> 
 <a name="L65" href="source/net/ipv4/tcp_dctcp.c#L65">65</a> static unsigned int dctcp_alpha_on_init <a href="ident?i=__read_mostly">__read_mostly</a> = <a href="ident?i=DCTCP_MAX_ALPHA">DCTCP_MAX_ALPHA</a>;
 <a name="L66" href="source/net/ipv4/tcp_dctcp.c#L66">66</a> <a href="ident?i=module_param">module_param</a>(dctcp_alpha_on_init, <a href="ident?i=uint">uint</a>, 0644);
 <a name="L67" href="source/net/ipv4/tcp_dctcp.c#L67">67</a> <a href="ident?i=MODULE_PARM_DESC">MODULE_PARM_DESC</a>(dctcp_alpha_on_init, <i>"parameter for initial alpha value"</i>);
 <a name="L68" href="source/net/ipv4/tcp_dctcp.c#L68">68</a> 
 <a name="L69" href="source/net/ipv4/tcp_dctcp.c#L69">69</a> static unsigned int dctcp_clamp_alpha_on_loss <a href="ident?i=__read_mostly">__read_mostly</a>;
 <a name="L70" href="source/net/ipv4/tcp_dctcp.c#L70">70</a> <a href="ident?i=module_param">module_param</a>(dctcp_clamp_alpha_on_loss, <a href="ident?i=uint">uint</a>, 0644);
 <a name="L71" href="source/net/ipv4/tcp_dctcp.c#L71">71</a> <a href="ident?i=MODULE_PARM_DESC">MODULE_PARM_DESC</a>(dctcp_clamp_alpha_on_loss,
 <a name="L72" href="source/net/ipv4/tcp_dctcp.c#L72">72</a>                  <i>"parameter for clamping alpha on loss"</i>);
 <a name="L73" href="source/net/ipv4/tcp_dctcp.c#L73">73</a> 
 <a name="L74" href="source/net/ipv4/tcp_dctcp.c#L74">74</a> static struct <a href="ident?i=tcp_congestion_ops">tcp_congestion_ops</a> <a href="ident?i=dctcp_reno">dctcp_reno</a>;
 <a name="L75" href="source/net/ipv4/tcp_dctcp.c#L75">75</a> 
 <a name="L76" href="source/net/ipv4/tcp_dctcp.c#L76">76</a> static void <a href="ident?i=dctcp_reset">dctcp_reset</a>(const struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a>, struct <a href="ident?i=dctcp">dctcp</a> *<a href="ident?i=ca">ca</a>)
 <a name="L77" href="source/net/ipv4/tcp_dctcp.c#L77">77</a> {
 <a name="L78" href="source/net/ipv4/tcp_dctcp.c#L78">78</a>         <a href="ident?i=ca">ca</a>-&gt;next_seq = <a href="ident?i=tp">tp</a>-&gt;snd_nxt;
 <a name="L79" href="source/net/ipv4/tcp_dctcp.c#L79">79</a> 
 <a name="L80" href="source/net/ipv4/tcp_dctcp.c#L80">80</a>         <a href="ident?i=ca">ca</a>-&gt;acked_bytes_ecn = 0;
 <a name="L81" href="source/net/ipv4/tcp_dctcp.c#L81">81</a>         <a href="ident?i=ca">ca</a>-&gt;acked_bytes_total = 0;
 <a name="L82" href="source/net/ipv4/tcp_dctcp.c#L82">82</a> }
 <a name="L83" href="source/net/ipv4/tcp_dctcp.c#L83">83</a> 
 <a name="L84" href="source/net/ipv4/tcp_dctcp.c#L84">84</a> static void <a href="ident?i=dctcp_init">dctcp_init</a>(struct <a href="ident?i=sock">sock</a> *sk)
 <a name="L85" href="source/net/ipv4/tcp_dctcp.c#L85">85</a> {
 <a name="L86" href="source/net/ipv4/tcp_dctcp.c#L86">86</a>         const struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
 <a name="L87" href="source/net/ipv4/tcp_dctcp.c#L87">87</a> 
 <a name="L88" href="source/net/ipv4/tcp_dctcp.c#L88">88</a>         if ((<a href="ident?i=tp">tp</a>-&gt;ecn_flags &amp; <a href="ident?i=TCP_ECN_OK">TCP_ECN_OK</a>) ||
 <a name="L89" href="source/net/ipv4/tcp_dctcp.c#L89">89</a>             (sk-&gt;<a href="ident?i=sk_state">sk_state</a> == TCP_LISTEN ||
 <a name="L90" href="source/net/ipv4/tcp_dctcp.c#L90">90</a>              sk-&gt;<a href="ident?i=sk_state">sk_state</a> == TCP_CLOSE)) {
 <a name="L91" href="source/net/ipv4/tcp_dctcp.c#L91">91</a>                 struct <a href="ident?i=dctcp">dctcp</a> *<a href="ident?i=ca">ca</a> = <a href="ident?i=inet_csk_ca">inet_csk_ca</a>(sk);
 <a name="L92" href="source/net/ipv4/tcp_dctcp.c#L92">92</a> 
 <a name="L93" href="source/net/ipv4/tcp_dctcp.c#L93">93</a>                 <a href="ident?i=ca">ca</a>-&gt;prior_snd_una = <a href="ident?i=tp">tp</a>-&gt;snd_una;
 <a name="L94" href="source/net/ipv4/tcp_dctcp.c#L94">94</a>                 <a href="ident?i=ca">ca</a>-&gt;prior_rcv_nxt = <a href="ident?i=tp">tp</a>-&gt;rcv_nxt;
 <a name="L95" href="source/net/ipv4/tcp_dctcp.c#L95">95</a> 
 <a name="L96" href="source/net/ipv4/tcp_dctcp.c#L96">96</a>                 <a href="ident?i=ca">ca</a>-&gt;dctcp_alpha = <a href="ident?i=min">min</a>(dctcp_alpha_on_init, <a href="ident?i=DCTCP_MAX_ALPHA">DCTCP_MAX_ALPHA</a>);
 <a name="L97" href="source/net/ipv4/tcp_dctcp.c#L97">97</a> 
 <a name="L98" href="source/net/ipv4/tcp_dctcp.c#L98">98</a>                 <a href="ident?i=ca">ca</a>-&gt;delayed_ack_reserved = 0;
 <a name="L99" href="source/net/ipv4/tcp_dctcp.c#L99">99</a>                 <a href="ident?i=ca">ca</a>-&gt;ce_state = 0;
<a name="L100" href="source/net/ipv4/tcp_dctcp.c#L100">100</a> 
<a name="L101" href="source/net/ipv4/tcp_dctcp.c#L101">101</a>                 <a href="ident?i=dctcp_reset">dctcp_reset</a>(<a href="ident?i=tp">tp</a>, <a href="ident?i=ca">ca</a>);
<a name="L102" href="source/net/ipv4/tcp_dctcp.c#L102">102</a>                 return;
<a name="L103" href="source/net/ipv4/tcp_dctcp.c#L103">103</a>         }
<a name="L104" href="source/net/ipv4/tcp_dctcp.c#L104">104</a> 
<a name="L105" href="source/net/ipv4/tcp_dctcp.c#L105">105</a>         <b><i>/* No ECN support? Fall back to Reno. Also need to clear</i></b>
<a name="L106" href="source/net/ipv4/tcp_dctcp.c#L106">106</a> <b><i>         * ECT from sk since it is set during 3WHS for DCTCP.</i></b>
<a name="L107" href="source/net/ipv4/tcp_dctcp.c#L107">107</a> <b><i>         */</i></b>
<a name="L108" href="source/net/ipv4/tcp_dctcp.c#L108">108</a>         <a href="ident?i=inet_csk">inet_csk</a>(sk)-&gt;icsk_ca_ops = &amp;<a href="ident?i=dctcp_reno">dctcp_reno</a>;
<a name="L109" href="source/net/ipv4/tcp_dctcp.c#L109">109</a>         <a href="ident?i=INET_ECN_dontxmit">INET_ECN_dontxmit</a>(sk);
<a name="L110" href="source/net/ipv4/tcp_dctcp.c#L110">110</a> }
<a name="L111" href="source/net/ipv4/tcp_dctcp.c#L111">111</a> 
<a name="L112" href="source/net/ipv4/tcp_dctcp.c#L112">112</a> static <a href="ident?i=u32">u32</a> <a href="ident?i=dctcp_ssthresh">dctcp_ssthresh</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L113" href="source/net/ipv4/tcp_dctcp.c#L113">113</a> {
<a name="L114" href="source/net/ipv4/tcp_dctcp.c#L114">114</a>         const struct <a href="ident?i=dctcp">dctcp</a> *<a href="ident?i=ca">ca</a> = <a href="ident?i=inet_csk_ca">inet_csk_ca</a>(sk);
<a name="L115" href="source/net/ipv4/tcp_dctcp.c#L115">115</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L116" href="source/net/ipv4/tcp_dctcp.c#L116">116</a> 
<a name="L117" href="source/net/ipv4/tcp_dctcp.c#L117">117</a>         return <a href="ident?i=max">max</a>(<a href="ident?i=tp">tp</a>-&gt;snd_cwnd - ((<a href="ident?i=tp">tp</a>-&gt;snd_cwnd * <a href="ident?i=ca">ca</a>-&gt;dctcp_alpha) &gt;&gt; 11U), 2U);
<a name="L118" href="source/net/ipv4/tcp_dctcp.c#L118">118</a> }
<a name="L119" href="source/net/ipv4/tcp_dctcp.c#L119">119</a> 
<a name="L120" href="source/net/ipv4/tcp_dctcp.c#L120">120</a> <b><i>/* Minimal DCTP CE state machine:</i></b>
<a name="L121" href="source/net/ipv4/tcp_dctcp.c#L121">121</a> <b><i> *</i></b>
<a name="L122" href="source/net/ipv4/tcp_dctcp.c#L122">122</a> <b><i> * S:   0 &lt;- last pkt was non-CE</i></b>
<a name="L123" href="source/net/ipv4/tcp_dctcp.c#L123">123</a> <b><i> *      1 &lt;- last pkt was CE</i></b>
<a name="L124" href="source/net/ipv4/tcp_dctcp.c#L124">124</a> <b><i> */</i></b>
<a name="L125" href="source/net/ipv4/tcp_dctcp.c#L125">125</a> 
<a name="L126" href="source/net/ipv4/tcp_dctcp.c#L126">126</a> static void <a href="ident?i=dctcp_ce_state_0_to_1">dctcp_ce_state_0_to_1</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L127" href="source/net/ipv4/tcp_dctcp.c#L127">127</a> {
<a name="L128" href="source/net/ipv4/tcp_dctcp.c#L128">128</a>         struct <a href="ident?i=dctcp">dctcp</a> *<a href="ident?i=ca">ca</a> = <a href="ident?i=inet_csk_ca">inet_csk_ca</a>(sk);
<a name="L129" href="source/net/ipv4/tcp_dctcp.c#L129">129</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L130" href="source/net/ipv4/tcp_dctcp.c#L130">130</a> 
<a name="L131" href="source/net/ipv4/tcp_dctcp.c#L131">131</a>         <b><i>/* State has changed from CE=0 to CE=1 and delayed</i></b>
<a name="L132" href="source/net/ipv4/tcp_dctcp.c#L132">132</a> <b><i>         * ACK has not sent yet.</i></b>
<a name="L133" href="source/net/ipv4/tcp_dctcp.c#L133">133</a> <b><i>         */</i></b>
<a name="L134" href="source/net/ipv4/tcp_dctcp.c#L134">134</a>         if (!<a href="ident?i=ca">ca</a>-&gt;ce_state &amp;&amp; <a href="ident?i=ca">ca</a>-&gt;delayed_ack_reserved) {
<a name="L135" href="source/net/ipv4/tcp_dctcp.c#L135">135</a>                 <a href="ident?i=u32">u32</a> tmp_rcv_nxt;
<a name="L136" href="source/net/ipv4/tcp_dctcp.c#L136">136</a> 
<a name="L137" href="source/net/ipv4/tcp_dctcp.c#L137">137</a>                 <b><i>/* Save current rcv_nxt. */</i></b>
<a name="L138" href="source/net/ipv4/tcp_dctcp.c#L138">138</a>                 tmp_rcv_nxt = <a href="ident?i=tp">tp</a>-&gt;rcv_nxt;
<a name="L139" href="source/net/ipv4/tcp_dctcp.c#L139">139</a> 
<a name="L140" href="source/net/ipv4/tcp_dctcp.c#L140">140</a>                 <b><i>/* Generate previous ack with CE=0. */</i></b>
<a name="L141" href="source/net/ipv4/tcp_dctcp.c#L141">141</a>                 <a href="ident?i=tp">tp</a>-&gt;ecn_flags &amp;= ~TCP_ECN_DEMAND_CWR;
<a name="L142" href="source/net/ipv4/tcp_dctcp.c#L142">142</a>                 <a href="ident?i=tp">tp</a>-&gt;rcv_nxt = <a href="ident?i=ca">ca</a>-&gt;prior_rcv_nxt;
<a name="L143" href="source/net/ipv4/tcp_dctcp.c#L143">143</a> 
<a name="L144" href="source/net/ipv4/tcp_dctcp.c#L144">144</a>                 <a href="ident?i=tcp_send_ack">tcp_send_ack</a>(sk);
<a name="L145" href="source/net/ipv4/tcp_dctcp.c#L145">145</a> 
<a name="L146" href="source/net/ipv4/tcp_dctcp.c#L146">146</a>                 <b><i>/* Recover current rcv_nxt. */</i></b>
<a name="L147" href="source/net/ipv4/tcp_dctcp.c#L147">147</a>                 <a href="ident?i=tp">tp</a>-&gt;rcv_nxt = tmp_rcv_nxt;
<a name="L148" href="source/net/ipv4/tcp_dctcp.c#L148">148</a>         }
<a name="L149" href="source/net/ipv4/tcp_dctcp.c#L149">149</a> 
<a name="L150" href="source/net/ipv4/tcp_dctcp.c#L150">150</a>         <a href="ident?i=ca">ca</a>-&gt;prior_rcv_nxt = <a href="ident?i=tp">tp</a>-&gt;rcv_nxt;
<a name="L151" href="source/net/ipv4/tcp_dctcp.c#L151">151</a>         <a href="ident?i=ca">ca</a>-&gt;ce_state = 1;
<a name="L152" href="source/net/ipv4/tcp_dctcp.c#L152">152</a> 
<a name="L153" href="source/net/ipv4/tcp_dctcp.c#L153">153</a>         <a href="ident?i=tp">tp</a>-&gt;ecn_flags |= <a href="ident?i=TCP_ECN_DEMAND_CWR">TCP_ECN_DEMAND_CWR</a>;
<a name="L154" href="source/net/ipv4/tcp_dctcp.c#L154">154</a> }
<a name="L155" href="source/net/ipv4/tcp_dctcp.c#L155">155</a> 
<a name="L156" href="source/net/ipv4/tcp_dctcp.c#L156">156</a> static void <a href="ident?i=dctcp_ce_state_1_to_0">dctcp_ce_state_1_to_0</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L157" href="source/net/ipv4/tcp_dctcp.c#L157">157</a> {
<a name="L158" href="source/net/ipv4/tcp_dctcp.c#L158">158</a>         struct <a href="ident?i=dctcp">dctcp</a> *<a href="ident?i=ca">ca</a> = <a href="ident?i=inet_csk_ca">inet_csk_ca</a>(sk);
<a name="L159" href="source/net/ipv4/tcp_dctcp.c#L159">159</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L160" href="source/net/ipv4/tcp_dctcp.c#L160">160</a> 
<a name="L161" href="source/net/ipv4/tcp_dctcp.c#L161">161</a>         <b><i>/* State has changed from CE=1 to CE=0 and delayed</i></b>
<a name="L162" href="source/net/ipv4/tcp_dctcp.c#L162">162</a> <b><i>         * ACK has not sent yet.</i></b>
<a name="L163" href="source/net/ipv4/tcp_dctcp.c#L163">163</a> <b><i>         */</i></b>
<a name="L164" href="source/net/ipv4/tcp_dctcp.c#L164">164</a>         if (<a href="ident?i=ca">ca</a>-&gt;ce_state &amp;&amp; <a href="ident?i=ca">ca</a>-&gt;delayed_ack_reserved) {
<a name="L165" href="source/net/ipv4/tcp_dctcp.c#L165">165</a>                 <a href="ident?i=u32">u32</a> tmp_rcv_nxt;
<a name="L166" href="source/net/ipv4/tcp_dctcp.c#L166">166</a> 
<a name="L167" href="source/net/ipv4/tcp_dctcp.c#L167">167</a>                 <b><i>/* Save current rcv_nxt. */</i></b>
<a name="L168" href="source/net/ipv4/tcp_dctcp.c#L168">168</a>                 tmp_rcv_nxt = <a href="ident?i=tp">tp</a>-&gt;rcv_nxt;
<a name="L169" href="source/net/ipv4/tcp_dctcp.c#L169">169</a> 
<a name="L170" href="source/net/ipv4/tcp_dctcp.c#L170">170</a>                 <b><i>/* Generate previous ack with CE=1. */</i></b>
<a name="L171" href="source/net/ipv4/tcp_dctcp.c#L171">171</a>                 <a href="ident?i=tp">tp</a>-&gt;ecn_flags |= <a href="ident?i=TCP_ECN_DEMAND_CWR">TCP_ECN_DEMAND_CWR</a>;
<a name="L172" href="source/net/ipv4/tcp_dctcp.c#L172">172</a>                 <a href="ident?i=tp">tp</a>-&gt;rcv_nxt = <a href="ident?i=ca">ca</a>-&gt;prior_rcv_nxt;
<a name="L173" href="source/net/ipv4/tcp_dctcp.c#L173">173</a> 
<a name="L174" href="source/net/ipv4/tcp_dctcp.c#L174">174</a>                 <a href="ident?i=tcp_send_ack">tcp_send_ack</a>(sk);
<a name="L175" href="source/net/ipv4/tcp_dctcp.c#L175">175</a> 
<a name="L176" href="source/net/ipv4/tcp_dctcp.c#L176">176</a>                 <b><i>/* Recover current rcv_nxt. */</i></b>
<a name="L177" href="source/net/ipv4/tcp_dctcp.c#L177">177</a>                 <a href="ident?i=tp">tp</a>-&gt;rcv_nxt = tmp_rcv_nxt;
<a name="L178" href="source/net/ipv4/tcp_dctcp.c#L178">178</a>         }
<a name="L179" href="source/net/ipv4/tcp_dctcp.c#L179">179</a> 
<a name="L180" href="source/net/ipv4/tcp_dctcp.c#L180">180</a>         <a href="ident?i=ca">ca</a>-&gt;prior_rcv_nxt = <a href="ident?i=tp">tp</a>-&gt;rcv_nxt;
<a name="L181" href="source/net/ipv4/tcp_dctcp.c#L181">181</a>         <a href="ident?i=ca">ca</a>-&gt;ce_state = 0;
<a name="L182" href="source/net/ipv4/tcp_dctcp.c#L182">182</a> 
<a name="L183" href="source/net/ipv4/tcp_dctcp.c#L183">183</a>         <a href="ident?i=tp">tp</a>-&gt;ecn_flags &amp;= ~TCP_ECN_DEMAND_CWR;
<a name="L184" href="source/net/ipv4/tcp_dctcp.c#L184">184</a> }
<a name="L185" href="source/net/ipv4/tcp_dctcp.c#L185">185</a> 
<a name="L186" href="source/net/ipv4/tcp_dctcp.c#L186">186</a> static void <a href="ident?i=dctcp_update_alpha">dctcp_update_alpha</a>(struct <a href="ident?i=sock">sock</a> *sk, <a href="ident?i=u32">u32</a> <a href="ident?i=flags">flags</a>)
<a name="L187" href="source/net/ipv4/tcp_dctcp.c#L187">187</a> {
<a name="L188" href="source/net/ipv4/tcp_dctcp.c#L188">188</a>         const struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L189" href="source/net/ipv4/tcp_dctcp.c#L189">189</a>         struct <a href="ident?i=dctcp">dctcp</a> *<a href="ident?i=ca">ca</a> = <a href="ident?i=inet_csk_ca">inet_csk_ca</a>(sk);
<a name="L190" href="source/net/ipv4/tcp_dctcp.c#L190">190</a>         <a href="ident?i=u32">u32</a> acked_bytes = <a href="ident?i=tp">tp</a>-&gt;snd_una - <a href="ident?i=ca">ca</a>-&gt;prior_snd_una;
<a name="L191" href="source/net/ipv4/tcp_dctcp.c#L191">191</a> 
<a name="L192" href="source/net/ipv4/tcp_dctcp.c#L192">192</a>         <b><i>/* If ack did not advance snd_una, count dupack as MSS size.</i></b>
<a name="L193" href="source/net/ipv4/tcp_dctcp.c#L193">193</a> <b><i>         * If ack did update window, do not count it at all.</i></b>
<a name="L194" href="source/net/ipv4/tcp_dctcp.c#L194">194</a> <b><i>         */</i></b>
<a name="L195" href="source/net/ipv4/tcp_dctcp.c#L195">195</a>         if (acked_bytes == 0 &amp;&amp; !(<a href="ident?i=flags">flags</a> &amp; CA_ACK_WIN_UPDATE))
<a name="L196" href="source/net/ipv4/tcp_dctcp.c#L196">196</a>                 acked_bytes = <a href="ident?i=inet_csk">inet_csk</a>(sk)-&gt;icsk_ack.rcv_mss;
<a name="L197" href="source/net/ipv4/tcp_dctcp.c#L197">197</a>         if (acked_bytes) {
<a name="L198" href="source/net/ipv4/tcp_dctcp.c#L198">198</a>                 <a href="ident?i=ca">ca</a>-&gt;acked_bytes_total += acked_bytes;
<a name="L199" href="source/net/ipv4/tcp_dctcp.c#L199">199</a>                 <a href="ident?i=ca">ca</a>-&gt;prior_snd_una = <a href="ident?i=tp">tp</a>-&gt;snd_una;
<a name="L200" href="source/net/ipv4/tcp_dctcp.c#L200">200</a> 
<a name="L201" href="source/net/ipv4/tcp_dctcp.c#L201">201</a>                 if (<a href="ident?i=flags">flags</a> &amp; CA_ACK_ECE)
<a name="L202" href="source/net/ipv4/tcp_dctcp.c#L202">202</a>                         <a href="ident?i=ca">ca</a>-&gt;acked_bytes_ecn += acked_bytes;
<a name="L203" href="source/net/ipv4/tcp_dctcp.c#L203">203</a>         }
<a name="L204" href="source/net/ipv4/tcp_dctcp.c#L204">204</a> 
<a name="L205" href="source/net/ipv4/tcp_dctcp.c#L205">205</a>         <b><i>/* Expired RTT */</i></b>
<a name="L206" href="source/net/ipv4/tcp_dctcp.c#L206">206</a>         if (!<a href="ident?i=before">before</a>(<a href="ident?i=tp">tp</a>-&gt;snd_una, <a href="ident?i=ca">ca</a>-&gt;next_seq)) {
<a name="L207" href="source/net/ipv4/tcp_dctcp.c#L207">207</a>                 <b><i>/* For avoiding denominator == 1. */</i></b>
<a name="L208" href="source/net/ipv4/tcp_dctcp.c#L208">208</a>                 if (<a href="ident?i=ca">ca</a>-&gt;acked_bytes_total == 0)
<a name="L209" href="source/net/ipv4/tcp_dctcp.c#L209">209</a>                         <a href="ident?i=ca">ca</a>-&gt;acked_bytes_total = 1;
<a name="L210" href="source/net/ipv4/tcp_dctcp.c#L210">210</a> 
<a name="L211" href="source/net/ipv4/tcp_dctcp.c#L211">211</a>                 <b><i>/* alpha = (1 - g) * alpha + g * F */</i></b>
<a name="L212" href="source/net/ipv4/tcp_dctcp.c#L212">212</a>                 <a href="ident?i=ca">ca</a>-&gt;dctcp_alpha = <a href="ident?i=ca">ca</a>-&gt;dctcp_alpha -
<a name="L213" href="source/net/ipv4/tcp_dctcp.c#L213">213</a>                                   (<a href="ident?i=ca">ca</a>-&gt;dctcp_alpha &gt;&gt; dctcp_shift_g) +
<a name="L214" href="source/net/ipv4/tcp_dctcp.c#L214">214</a>                                   (<a href="ident?i=ca">ca</a>-&gt;acked_bytes_ecn &lt;&lt; (10U - dctcp_shift_g)) /
<a name="L215" href="source/net/ipv4/tcp_dctcp.c#L215">215</a>                                   <a href="ident?i=ca">ca</a>-&gt;acked_bytes_total;
<a name="L216" href="source/net/ipv4/tcp_dctcp.c#L216">216</a> 
<a name="L217" href="source/net/ipv4/tcp_dctcp.c#L217">217</a>                 if (<a href="ident?i=ca">ca</a>-&gt;dctcp_alpha &gt; <a href="ident?i=DCTCP_MAX_ALPHA">DCTCP_MAX_ALPHA</a>)
<a name="L218" href="source/net/ipv4/tcp_dctcp.c#L218">218</a>                         <b><i>/* Clamp dctcp_alpha to max. */</i></b>
<a name="L219" href="source/net/ipv4/tcp_dctcp.c#L219">219</a>                         <a href="ident?i=ca">ca</a>-&gt;dctcp_alpha = <a href="ident?i=DCTCP_MAX_ALPHA">DCTCP_MAX_ALPHA</a>;
<a name="L220" href="source/net/ipv4/tcp_dctcp.c#L220">220</a> 
<a name="L221" href="source/net/ipv4/tcp_dctcp.c#L221">221</a>                 <a href="ident?i=dctcp_reset">dctcp_reset</a>(<a href="ident?i=tp">tp</a>, <a href="ident?i=ca">ca</a>);
<a name="L222" href="source/net/ipv4/tcp_dctcp.c#L222">222</a>         }
<a name="L223" href="source/net/ipv4/tcp_dctcp.c#L223">223</a> }
<a name="L224" href="source/net/ipv4/tcp_dctcp.c#L224">224</a> 
<a name="L225" href="source/net/ipv4/tcp_dctcp.c#L225">225</a> static void <a href="ident?i=dctcp_state">dctcp_state</a>(struct <a href="ident?i=sock">sock</a> *sk, <a href="ident?i=u8">u8</a> <a href="ident?i=new_state">new_state</a>)
<a name="L226" href="source/net/ipv4/tcp_dctcp.c#L226">226</a> {
<a name="L227" href="source/net/ipv4/tcp_dctcp.c#L227">227</a>         if (dctcp_clamp_alpha_on_loss &amp;&amp; <a href="ident?i=new_state">new_state</a> == TCP_CA_Loss) {
<a name="L228" href="source/net/ipv4/tcp_dctcp.c#L228">228</a>                 struct <a href="ident?i=dctcp">dctcp</a> *<a href="ident?i=ca">ca</a> = <a href="ident?i=inet_csk_ca">inet_csk_ca</a>(sk);
<a name="L229" href="source/net/ipv4/tcp_dctcp.c#L229">229</a> 
<a name="L230" href="source/net/ipv4/tcp_dctcp.c#L230">230</a>                 <b><i>/* If this extension is enabled, we clamp dctcp_alpha to</i></b>
<a name="L231" href="source/net/ipv4/tcp_dctcp.c#L231">231</a> <b><i>                 * max on packet loss; the motivation is that dctcp_alpha</i></b>
<a name="L232" href="source/net/ipv4/tcp_dctcp.c#L232">232</a> <b><i>                 * is an indicator to the extend of congestion and packet</i></b>
<a name="L233" href="source/net/ipv4/tcp_dctcp.c#L233">233</a> <b><i>                 * loss is an indicator of extreme congestion; setting</i></b>
<a name="L234" href="source/net/ipv4/tcp_dctcp.c#L234">234</a> <b><i>                 * this in practice turned out to be beneficial, and</i></b>
<a name="L235" href="source/net/ipv4/tcp_dctcp.c#L235">235</a> <b><i>                 * effectively assumes total congestion which reduces the</i></b>
<a name="L236" href="source/net/ipv4/tcp_dctcp.c#L236">236</a> <b><i>                 * window by half.</i></b>
<a name="L237" href="source/net/ipv4/tcp_dctcp.c#L237">237</a> <b><i>                 */</i></b>
<a name="L238" href="source/net/ipv4/tcp_dctcp.c#L238">238</a>                 <a href="ident?i=ca">ca</a>-&gt;dctcp_alpha = <a href="ident?i=DCTCP_MAX_ALPHA">DCTCP_MAX_ALPHA</a>;
<a name="L239" href="source/net/ipv4/tcp_dctcp.c#L239">239</a>         }
<a name="L240" href="source/net/ipv4/tcp_dctcp.c#L240">240</a> }
<a name="L241" href="source/net/ipv4/tcp_dctcp.c#L241">241</a> 
<a name="L242" href="source/net/ipv4/tcp_dctcp.c#L242">242</a> static void <a href="ident?i=dctcp_update_ack_reserved">dctcp_update_ack_reserved</a>(struct <a href="ident?i=sock">sock</a> *sk, enum <a href="ident?i=tcp_ca_event">tcp_ca_event</a> <a href="ident?i=ev">ev</a>)
<a name="L243" href="source/net/ipv4/tcp_dctcp.c#L243">243</a> {
<a name="L244" href="source/net/ipv4/tcp_dctcp.c#L244">244</a>         struct <a href="ident?i=dctcp">dctcp</a> *<a href="ident?i=ca">ca</a> = <a href="ident?i=inet_csk_ca">inet_csk_ca</a>(sk);
<a name="L245" href="source/net/ipv4/tcp_dctcp.c#L245">245</a> 
<a name="L246" href="source/net/ipv4/tcp_dctcp.c#L246">246</a>         switch (<a href="ident?i=ev">ev</a>) {
<a name="L247" href="source/net/ipv4/tcp_dctcp.c#L247">247</a>         case CA_EVENT_DELAYED_ACK:
<a name="L248" href="source/net/ipv4/tcp_dctcp.c#L248">248</a>                 if (!<a href="ident?i=ca">ca</a>-&gt;delayed_ack_reserved)
<a name="L249" href="source/net/ipv4/tcp_dctcp.c#L249">249</a>                         <a href="ident?i=ca">ca</a>-&gt;delayed_ack_reserved = 1;
<a name="L250" href="source/net/ipv4/tcp_dctcp.c#L250">250</a>                 break;
<a name="L251" href="source/net/ipv4/tcp_dctcp.c#L251">251</a>         case CA_EVENT_NON_DELAYED_ACK:
<a name="L252" href="source/net/ipv4/tcp_dctcp.c#L252">252</a>                 if (<a href="ident?i=ca">ca</a>-&gt;delayed_ack_reserved)
<a name="L253" href="source/net/ipv4/tcp_dctcp.c#L253">253</a>                         <a href="ident?i=ca">ca</a>-&gt;delayed_ack_reserved = 0;
<a name="L254" href="source/net/ipv4/tcp_dctcp.c#L254">254</a>                 break;
<a name="L255" href="source/net/ipv4/tcp_dctcp.c#L255">255</a>         default:
<a name="L256" href="source/net/ipv4/tcp_dctcp.c#L256">256</a>                 <b><i>/* Don't care for the rest. */</i></b>
<a name="L257" href="source/net/ipv4/tcp_dctcp.c#L257">257</a>                 break;
<a name="L258" href="source/net/ipv4/tcp_dctcp.c#L258">258</a>         }
<a name="L259" href="source/net/ipv4/tcp_dctcp.c#L259">259</a> }
<a name="L260" href="source/net/ipv4/tcp_dctcp.c#L260">260</a> 
<a name="L261" href="source/net/ipv4/tcp_dctcp.c#L261">261</a> static void <a href="ident?i=dctcp_cwnd_event">dctcp_cwnd_event</a>(struct <a href="ident?i=sock">sock</a> *sk, enum <a href="ident?i=tcp_ca_event">tcp_ca_event</a> <a href="ident?i=ev">ev</a>)
<a name="L262" href="source/net/ipv4/tcp_dctcp.c#L262">262</a> {
<a name="L263" href="source/net/ipv4/tcp_dctcp.c#L263">263</a>         switch (<a href="ident?i=ev">ev</a>) {
<a name="L264" href="source/net/ipv4/tcp_dctcp.c#L264">264</a>         case CA_EVENT_ECN_IS_CE:
<a name="L265" href="source/net/ipv4/tcp_dctcp.c#L265">265</a>                 <a href="ident?i=dctcp_ce_state_0_to_1">dctcp_ce_state_0_to_1</a>(sk);
<a name="L266" href="source/net/ipv4/tcp_dctcp.c#L266">266</a>                 break;
<a name="L267" href="source/net/ipv4/tcp_dctcp.c#L267">267</a>         case CA_EVENT_ECN_NO_CE:
<a name="L268" href="source/net/ipv4/tcp_dctcp.c#L268">268</a>                 <a href="ident?i=dctcp_ce_state_1_to_0">dctcp_ce_state_1_to_0</a>(sk);
<a name="L269" href="source/net/ipv4/tcp_dctcp.c#L269">269</a>                 break;
<a name="L270" href="source/net/ipv4/tcp_dctcp.c#L270">270</a>         case CA_EVENT_DELAYED_ACK:
<a name="L271" href="source/net/ipv4/tcp_dctcp.c#L271">271</a>         case CA_EVENT_NON_DELAYED_ACK:
<a name="L272" href="source/net/ipv4/tcp_dctcp.c#L272">272</a>                 <a href="ident?i=dctcp_update_ack_reserved">dctcp_update_ack_reserved</a>(sk, <a href="ident?i=ev">ev</a>);
<a name="L273" href="source/net/ipv4/tcp_dctcp.c#L273">273</a>                 break;
<a name="L274" href="source/net/ipv4/tcp_dctcp.c#L274">274</a>         default:
<a name="L275" href="source/net/ipv4/tcp_dctcp.c#L275">275</a>                 <b><i>/* Don't care for the rest. */</i></b>
<a name="L276" href="source/net/ipv4/tcp_dctcp.c#L276">276</a>                 break;
<a name="L277" href="source/net/ipv4/tcp_dctcp.c#L277">277</a>         }
<a name="L278" href="source/net/ipv4/tcp_dctcp.c#L278">278</a> }
<a name="L279" href="source/net/ipv4/tcp_dctcp.c#L279">279</a> 
<a name="L280" href="source/net/ipv4/tcp_dctcp.c#L280">280</a> static <a href="ident?i=size_t">size_t</a> <a href="ident?i=dctcp_get_info">dctcp_get_info</a>(struct <a href="ident?i=sock">sock</a> *sk, <a href="ident?i=u32">u32</a> ext, int *<a href="ident?i=attr">attr</a>,
<a name="L281" href="source/net/ipv4/tcp_dctcp.c#L281">281</a>                              union <a href="ident?i=tcp_cc_info">tcp_cc_info</a> *<a href="ident?i=info">info</a>)
<a name="L282" href="source/net/ipv4/tcp_dctcp.c#L282">282</a> {
<a name="L283" href="source/net/ipv4/tcp_dctcp.c#L283">283</a>         const struct <a href="ident?i=dctcp">dctcp</a> *<a href="ident?i=ca">ca</a> = <a href="ident?i=inet_csk_ca">inet_csk_ca</a>(sk);
<a name="L284" href="source/net/ipv4/tcp_dctcp.c#L284">284</a> 
<a name="L285" href="source/net/ipv4/tcp_dctcp.c#L285">285</a>         <b><i>/* Fill it also in case of VEGASINFO due to req struct limits.</i></b>
<a name="L286" href="source/net/ipv4/tcp_dctcp.c#L286">286</a> <b><i>         * We can still correctly retrieve it later.</i></b>
<a name="L287" href="source/net/ipv4/tcp_dctcp.c#L287">287</a> <b><i>         */</i></b>
<a name="L288" href="source/net/ipv4/tcp_dctcp.c#L288">288</a>         if (ext &amp; (1 &lt;&lt; (INET_DIAG_DCTCPINFO - 1)) ||
<a name="L289" href="source/net/ipv4/tcp_dctcp.c#L289">289</a>             ext &amp; (1 &lt;&lt; (INET_DIAG_VEGASINFO - 1))) {
<a name="L290" href="source/net/ipv4/tcp_dctcp.c#L290">290</a>                 <a href="ident?i=memset">memset</a>(<a href="ident?i=info">info</a>, 0, sizeof(struct <a href="ident?i=tcp_dctcp_info">tcp_dctcp_info</a>));
<a name="L291" href="source/net/ipv4/tcp_dctcp.c#L291">291</a>                 if (<a href="ident?i=inet_csk">inet_csk</a>(sk)-&gt;icsk_ca_ops != &amp;<a href="ident?i=dctcp_reno">dctcp_reno</a>) {
<a name="L292" href="source/net/ipv4/tcp_dctcp.c#L292">292</a>                         <a href="ident?i=info">info</a>-&gt;<a href="ident?i=dctcp">dctcp</a>.dctcp_enabled = 1;
<a name="L293" href="source/net/ipv4/tcp_dctcp.c#L293">293</a>                         <a href="ident?i=info">info</a>-&gt;<a href="ident?i=dctcp">dctcp</a>.dctcp_ce_state = (<a href="ident?i=u16">u16</a>) <a href="ident?i=ca">ca</a>-&gt;ce_state;
<a name="L294" href="source/net/ipv4/tcp_dctcp.c#L294">294</a>                         <a href="ident?i=info">info</a>-&gt;<a href="ident?i=dctcp">dctcp</a>.dctcp_alpha = <a href="ident?i=ca">ca</a>-&gt;dctcp_alpha;
<a name="L295" href="source/net/ipv4/tcp_dctcp.c#L295">295</a>                         <a href="ident?i=info">info</a>-&gt;<a href="ident?i=dctcp">dctcp</a>.dctcp_ab_ecn = <a href="ident?i=ca">ca</a>-&gt;acked_bytes_ecn;
<a name="L296" href="source/net/ipv4/tcp_dctcp.c#L296">296</a>                         <a href="ident?i=info">info</a>-&gt;<a href="ident?i=dctcp">dctcp</a>.dctcp_ab_tot = <a href="ident?i=ca">ca</a>-&gt;acked_bytes_total;
<a name="L297" href="source/net/ipv4/tcp_dctcp.c#L297">297</a>                 }
<a name="L298" href="source/net/ipv4/tcp_dctcp.c#L298">298</a> 
<a name="L299" href="source/net/ipv4/tcp_dctcp.c#L299">299</a>                 *<a href="ident?i=attr">attr</a> = INET_DIAG_DCTCPINFO;
<a name="L300" href="source/net/ipv4/tcp_dctcp.c#L300">300</a>                 return sizeof(*<a href="ident?i=info">info</a>);
<a name="L301" href="source/net/ipv4/tcp_dctcp.c#L301">301</a>         }
<a name="L302" href="source/net/ipv4/tcp_dctcp.c#L302">302</a>         return 0;
<a name="L303" href="source/net/ipv4/tcp_dctcp.c#L303">303</a> }
<a name="L304" href="source/net/ipv4/tcp_dctcp.c#L304">304</a> 
<a name="L305" href="source/net/ipv4/tcp_dctcp.c#L305">305</a> static struct <a href="ident?i=tcp_congestion_ops">tcp_congestion_ops</a> <a href="ident?i=dctcp">dctcp</a> <a href="ident?i=__read_mostly">__read_mostly</a> = {
<a name="L306" href="source/net/ipv4/tcp_dctcp.c#L306">306</a>         .<a href="ident?i=init">init</a>           = <a href="ident?i=dctcp_init">dctcp_init</a>,
<a name="L307" href="source/net/ipv4/tcp_dctcp.c#L307">307</a>         .in_ack_event   = <a href="ident?i=dctcp_update_alpha">dctcp_update_alpha</a>,
<a name="L308" href="source/net/ipv4/tcp_dctcp.c#L308">308</a>         .cwnd_event     = <a href="ident?i=dctcp_cwnd_event">dctcp_cwnd_event</a>,
<a name="L309" href="source/net/ipv4/tcp_dctcp.c#L309">309</a>         .ssthresh       = <a href="ident?i=dctcp_ssthresh">dctcp_ssthresh</a>,
<a name="L310" href="source/net/ipv4/tcp_dctcp.c#L310">310</a>         .cong_avoid     = <a href="ident?i=tcp_reno_cong_avoid">tcp_reno_cong_avoid</a>,
<a name="L311" href="source/net/ipv4/tcp_dctcp.c#L311">311</a>         .<a href="ident?i=set_state">set_state</a>      = <a href="ident?i=dctcp_state">dctcp_state</a>,
<a name="L312" href="source/net/ipv4/tcp_dctcp.c#L312">312</a>         .<a href="ident?i=get_info">get_info</a>       = <a href="ident?i=dctcp_get_info">dctcp_get_info</a>,
<a name="L313" href="source/net/ipv4/tcp_dctcp.c#L313">313</a>         .<a href="ident?i=flags">flags</a>          = <a href="ident?i=TCP_CONG_NEEDS_ECN">TCP_CONG_NEEDS_ECN</a>,
<a name="L314" href="source/net/ipv4/tcp_dctcp.c#L314">314</a>         .owner          = <a href="ident?i=THIS_MODULE">THIS_MODULE</a>,
<a name="L315" href="source/net/ipv4/tcp_dctcp.c#L315">315</a>         .<a href="ident?i=name">name</a>           = <i>"dctcp"</i>,
<a name="L316" href="source/net/ipv4/tcp_dctcp.c#L316">316</a> };
<a name="L317" href="source/net/ipv4/tcp_dctcp.c#L317">317</a> 
<a name="L318" href="source/net/ipv4/tcp_dctcp.c#L318">318</a> static struct <a href="ident?i=tcp_congestion_ops">tcp_congestion_ops</a> <a href="ident?i=dctcp_reno">dctcp_reno</a> <a href="ident?i=__read_mostly">__read_mostly</a> = {
<a name="L319" href="source/net/ipv4/tcp_dctcp.c#L319">319</a>         .ssthresh       = <a href="ident?i=tcp_reno_ssthresh">tcp_reno_ssthresh</a>,
<a name="L320" href="source/net/ipv4/tcp_dctcp.c#L320">320</a>         .cong_avoid     = <a href="ident?i=tcp_reno_cong_avoid">tcp_reno_cong_avoid</a>,
<a name="L321" href="source/net/ipv4/tcp_dctcp.c#L321">321</a>         .<a href="ident?i=get_info">get_info</a>       = <a href="ident?i=dctcp_get_info">dctcp_get_info</a>,
<a name="L322" href="source/net/ipv4/tcp_dctcp.c#L322">322</a>         .owner          = <a href="ident?i=THIS_MODULE">THIS_MODULE</a>,
<a name="L323" href="source/net/ipv4/tcp_dctcp.c#L323">323</a>         .<a href="ident?i=name">name</a>           = <i>"dctcp-reno"</i>,
<a name="L324" href="source/net/ipv4/tcp_dctcp.c#L324">324</a> };
<a name="L325" href="source/net/ipv4/tcp_dctcp.c#L325">325</a> 
<a name="L326" href="source/net/ipv4/tcp_dctcp.c#L326">326</a> static int <a href="ident?i=__init">__init</a> <a href="ident?i=dctcp_register">dctcp_register</a>(void)
<a name="L327" href="source/net/ipv4/tcp_dctcp.c#L327">327</a> {
<a name="L328" href="source/net/ipv4/tcp_dctcp.c#L328">328</a>         <a href="ident?i=BUILD_BUG_ON">BUILD_BUG_ON</a>(sizeof(struct <a href="ident?i=dctcp">dctcp</a>) &gt; <a href="ident?i=ICSK_CA_PRIV_SIZE">ICSK_CA_PRIV_SIZE</a>);
<a name="L329" href="source/net/ipv4/tcp_dctcp.c#L329">329</a>         return <a href="ident?i=tcp_register_congestion_control">tcp_register_congestion_control</a>(&amp;<a href="ident?i=dctcp">dctcp</a>);
<a name="L330" href="source/net/ipv4/tcp_dctcp.c#L330">330</a> }
<a name="L331" href="source/net/ipv4/tcp_dctcp.c#L331">331</a> 
<a name="L332" href="source/net/ipv4/tcp_dctcp.c#L332">332</a> static void <a href="ident?i=__exit">__exit</a> <a href="ident?i=dctcp_unregister">dctcp_unregister</a>(void)
<a name="L333" href="source/net/ipv4/tcp_dctcp.c#L333">333</a> {
<a name="L334" href="source/net/ipv4/tcp_dctcp.c#L334">334</a>         <a href="ident?i=tcp_unregister_congestion_control">tcp_unregister_congestion_control</a>(&amp;<a href="ident?i=dctcp">dctcp</a>);
<a name="L335" href="source/net/ipv4/tcp_dctcp.c#L335">335</a> }
<a name="L336" href="source/net/ipv4/tcp_dctcp.c#L336">336</a> 
<a name="L337" href="source/net/ipv4/tcp_dctcp.c#L337">337</a> <a href="ident?i=module_init">module_init</a>(<a href="ident?i=dctcp_register">dctcp_register</a>);
<a name="L338" href="source/net/ipv4/tcp_dctcp.c#L338">338</a> <a href="ident?i=module_exit">module_exit</a>(<a href="ident?i=dctcp_unregister">dctcp_unregister</a>);
<a name="L339" href="source/net/ipv4/tcp_dctcp.c#L339">339</a> 
<a name="L340" href="source/net/ipv4/tcp_dctcp.c#L340">340</a> <a href="ident?i=MODULE_AUTHOR">MODULE_AUTHOR</a>(<i>"Daniel Borkmann &lt;dborkman@redhat.com&gt;"</i>);
<a name="L341" href="source/net/ipv4/tcp_dctcp.c#L341">341</a> <a href="ident?i=MODULE_AUTHOR">MODULE_AUTHOR</a>(<i>"Florian Westphal &lt;fw@strlen.de&gt;"</i>);
<a name="L342" href="source/net/ipv4/tcp_dctcp.c#L342">342</a> <a href="ident?i=MODULE_AUTHOR">MODULE_AUTHOR</a>(<i>"Glenn Judd &lt;glenn.judd@morganstanley.com&gt;"</i>);
<a name="L343" href="source/net/ipv4/tcp_dctcp.c#L343">343</a> 
<a name="L344" href="source/net/ipv4/tcp_dctcp.c#L344">344</a> <a href="ident?i=MODULE_LICENSE">MODULE_LICENSE</a>(<i>"GPL v2"</i>);
<a name="L345" href="source/net/ipv4/tcp_dctcp.c#L345">345</a> <a href="ident?i=MODULE_DESCRIPTION">MODULE_DESCRIPTION</a>(<i>"DataCenter TCP (DCTCP)"</i>);
<a name="L346" href="source/net/ipv4/tcp_dctcp.c#L346">346</a> </pre></div><p>
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
