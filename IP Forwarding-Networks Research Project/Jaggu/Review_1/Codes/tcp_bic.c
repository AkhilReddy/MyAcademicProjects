<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title>Linux/net/ipv4/tcp_bic.c - Linux Cross Reference - Free Electrons</title>
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
		 &nbsp;&bull;&nbsp;<b><i>source navigation</i></b> &nbsp;&bull;&nbsp;<a href="diff/net/ipv4/tcp_bic.c">diff markup</a> &nbsp;&bull;&nbsp;<a href="ident">identifier search</a> &nbsp;&bull;&nbsp;<a href="search">freetext search</a> &nbsp;&bull;&nbsp;
		</p>
	</div>
</div>

<div id="topbar">
  
  <p>Version: &nbsp;<a href="source/net/ipv4/tcp_bic.c?v=2.0.40">2.0.40</a>&nbsp;<a href="source/net/ipv4/tcp_bic.c?v=2.2.26">2.2.26</a>&nbsp;<a href="source/net/ipv4/tcp_bic.c?v=2.4.37">2.4.37</a>&nbsp;<a href="source/net/ipv4/tcp_bic.c?v=3.5">3.5</a>&nbsp;<a href="source/net/ipv4/tcp_bic.c?v=3.6">3.6</a>&nbsp;<a href="source/net/ipv4/tcp_bic.c?v=3.7">3.7</a>&nbsp;<a href="source/net/ipv4/tcp_bic.c?v=3.8">3.8</a>&nbsp;<a href="source/net/ipv4/tcp_bic.c?v=3.9">3.9</a>&nbsp;<a href="source/net/ipv4/tcp_bic.c?v=3.10">3.10</a>&nbsp;<a href="source/net/ipv4/tcp_bic.c?v=3.11">3.11</a>&nbsp;<a href="source/net/ipv4/tcp_bic.c?v=3.12">3.12</a>&nbsp;<a href="source/net/ipv4/tcp_bic.c?v=3.13">3.13</a>&nbsp;<a href="source/net/ipv4/tcp_bic.c?v=3.14">3.14</a>&nbsp;<a href="source/net/ipv4/tcp_bic.c?v=3.15">3.15</a>&nbsp;<a href="source/net/ipv4/tcp_bic.c?v=3.16">3.16</a>&nbsp;<a href="source/net/ipv4/tcp_bic.c?v=3.17">3.17</a>&nbsp;<a href="source/net/ipv4/tcp_bic.c?v=3.18">3.18</a>&nbsp;<a href="source/net/ipv4/tcp_bic.c?v=3.19">3.19</a>&nbsp;<a href="source/net/ipv4/tcp_bic.c?v=4.0">4.0</a>&nbsp;<b><i>4.1</i></b></p>
  
</div>

<h1><a href="source/">Linux</a>/<a href="source/net/">net</a>/<a href="source/net/ipv4/">ipv4</a>/<a href="source/net/ipv4/tcp_bic.c">tcp_bic.c</a></h1>
<div id="lxrcode"><pre>  <a name="L1" href="source/net/ipv4/tcp_bic.c#L1">1</a> <b><i>/*</i></b>
  <a name="L2" href="source/net/ipv4/tcp_bic.c#L2">2</a> <b><i> * Binary Increase Congestion control for TCP</i></b>
  <a name="L3" href="source/net/ipv4/tcp_bic.c#L3">3</a> <b><i> * Home page:</i></b>
  <a name="L4" href="source/net/ipv4/tcp_bic.c#L4">4</a> <b><i> *      <a href="http://netsrv.csc.ncsu.edu/twiki/bin/view/Main/BIC">http://netsrv.csc.ncsu.edu/twiki/bin/view/Main/BIC</a></i></b>
  <a name="L5" href="source/net/ipv4/tcp_bic.c#L5">5</a> <b><i> * This is from the implementation of BICTCP in</i></b>
  <a name="L6" href="source/net/ipv4/tcp_bic.c#L6">6</a> <b><i> * Lison-Xu, Kahaled Harfoush, and Injong Rhee.</i></b>
  <a name="L7" href="source/net/ipv4/tcp_bic.c#L7">7</a> <b><i> *  "Binary Increase Congestion Control for Fast, Long Distance</i></b>
  <a name="L8" href="source/net/ipv4/tcp_bic.c#L8">8</a> <b><i> *  Networks" in InfoComm 2004</i></b>
  <a name="L9" href="source/net/ipv4/tcp_bic.c#L9">9</a> <b><i> * Available from:</i></b>
 <a name="L10" href="source/net/ipv4/tcp_bic.c#L10">10</a> <b><i> *  <a href="http://netsrv.csc.ncsu.edu/export/bitcp.pdf">http://netsrv.csc.ncsu.edu/export/bitcp.pdf</a></i></b>
 <a name="L11" href="source/net/ipv4/tcp_bic.c#L11">11</a> <b><i> *</i></b>
 <a name="L12" href="source/net/ipv4/tcp_bic.c#L12">12</a> <b><i> * Unless BIC is enabled and congestion window is large</i></b>
 <a name="L13" href="source/net/ipv4/tcp_bic.c#L13">13</a> <b><i> * this behaves the same as the original Reno.</i></b>
 <a name="L14" href="source/net/ipv4/tcp_bic.c#L14">14</a> <b><i> */</i></b>
 <a name="L15" href="source/net/ipv4/tcp_bic.c#L15">15</a> 
 <a name="L16" href="source/net/ipv4/tcp_bic.c#L16">16</a> #include &lt;linux/mm.h&gt;
 <a name="L17" href="source/net/ipv4/tcp_bic.c#L17">17</a> #include &lt;linux/module.h&gt;
 <a name="L18" href="source/net/ipv4/tcp_bic.c#L18">18</a> #include &lt;net/tcp.h&gt;
 <a name="L19" href="source/net/ipv4/tcp_bic.c#L19">19</a> 
 <a name="L20" href="source/net/ipv4/tcp_bic.c#L20">20</a> #define <a href="ident?i=BICTCP_BETA_SCALE">BICTCP_BETA_SCALE</a>    1024       <b><i>/* Scale factor beta calculation</i></b>
 <a name="L21" href="source/net/ipv4/tcp_bic.c#L21">21</a> <b><i>                                         * max_cwnd = snd_cwnd * beta</i></b>
 <a name="L22" href="source/net/ipv4/tcp_bic.c#L22">22</a> <b><i>                                         */</i></b>
 <a name="L23" href="source/net/ipv4/tcp_bic.c#L23">23</a> #define <a href="ident?i=BICTCP_B">BICTCP_B</a>                4        <b><i>/*</i></b>
 <a name="L24" href="source/net/ipv4/tcp_bic.c#L24">24</a> <b><i>                                          * In binary search,</i></b>
 <a name="L25" href="source/net/ipv4/tcp_bic.c#L25">25</a> <b><i>                                          * go to point (max+min)/N</i></b>
 <a name="L26" href="source/net/ipv4/tcp_bic.c#L26">26</a> <b><i>                                          */</i></b>
 <a name="L27" href="source/net/ipv4/tcp_bic.c#L27">27</a> 
 <a name="L28" href="source/net/ipv4/tcp_bic.c#L28">28</a> static int <a href="ident?i=fast_convergence">fast_convergence</a> = 1;
 <a name="L29" href="source/net/ipv4/tcp_bic.c#L29">29</a> static int <a href="ident?i=max_increment">max_increment</a> = 16;
 <a name="L30" href="source/net/ipv4/tcp_bic.c#L30">30</a> static int <a href="ident?i=low_window">low_window</a> = 14;
 <a name="L31" href="source/net/ipv4/tcp_bic.c#L31">31</a> static int <a href="ident?i=beta">beta</a> = 819;          <b><i>/* = 819/1024 (BICTCP_BETA_SCALE) */</i></b>
 <a name="L32" href="source/net/ipv4/tcp_bic.c#L32">32</a> static int <a href="ident?i=initial_ssthresh">initial_ssthresh</a>;
 <a name="L33" href="source/net/ipv4/tcp_bic.c#L33">33</a> static int <a href="ident?i=smooth_part">smooth_part</a> = 20;
 <a name="L34" href="source/net/ipv4/tcp_bic.c#L34">34</a> 
 <a name="L35" href="source/net/ipv4/tcp_bic.c#L35">35</a> <a href="ident?i=module_param">module_param</a>(<a href="ident?i=fast_convergence">fast_convergence</a>, int, 0644);
 <a name="L36" href="source/net/ipv4/tcp_bic.c#L36">36</a> <a href="ident?i=MODULE_PARM_DESC">MODULE_PARM_DESC</a>(<a href="ident?i=fast_convergence">fast_convergence</a>, <i>"turn on/off fast convergence"</i>);
 <a name="L37" href="source/net/ipv4/tcp_bic.c#L37">37</a> <a href="ident?i=module_param">module_param</a>(<a href="ident?i=max_increment">max_increment</a>, int, 0644);
 <a name="L38" href="source/net/ipv4/tcp_bic.c#L38">38</a> <a href="ident?i=MODULE_PARM_DESC">MODULE_PARM_DESC</a>(<a href="ident?i=max_increment">max_increment</a>, <i>"Limit on increment allowed during binary search"</i>);
 <a name="L39" href="source/net/ipv4/tcp_bic.c#L39">39</a> <a href="ident?i=module_param">module_param</a>(<a href="ident?i=low_window">low_window</a>, int, 0644);
 <a name="L40" href="source/net/ipv4/tcp_bic.c#L40">40</a> <a href="ident?i=MODULE_PARM_DESC">MODULE_PARM_DESC</a>(<a href="ident?i=low_window">low_window</a>, <i>"lower bound on congestion window (for TCP friendliness)"</i>);
 <a name="L41" href="source/net/ipv4/tcp_bic.c#L41">41</a> <a href="ident?i=module_param">module_param</a>(<a href="ident?i=beta">beta</a>, int, 0644);
 <a name="L42" href="source/net/ipv4/tcp_bic.c#L42">42</a> <a href="ident?i=MODULE_PARM_DESC">MODULE_PARM_DESC</a>(<a href="ident?i=beta">beta</a>, <i>"beta for multiplicative increase"</i>);
 <a name="L43" href="source/net/ipv4/tcp_bic.c#L43">43</a> <a href="ident?i=module_param">module_param</a>(<a href="ident?i=initial_ssthresh">initial_ssthresh</a>, int, 0644);
 <a name="L44" href="source/net/ipv4/tcp_bic.c#L44">44</a> <a href="ident?i=MODULE_PARM_DESC">MODULE_PARM_DESC</a>(<a href="ident?i=initial_ssthresh">initial_ssthresh</a>, <i>"initial value of slow start threshold"</i>);
 <a name="L45" href="source/net/ipv4/tcp_bic.c#L45">45</a> <a href="ident?i=module_param">module_param</a>(<a href="ident?i=smooth_part">smooth_part</a>, int, 0644);
 <a name="L46" href="source/net/ipv4/tcp_bic.c#L46">46</a> <a href="ident?i=MODULE_PARM_DESC">MODULE_PARM_DESC</a>(<a href="ident?i=smooth_part">smooth_part</a>, <i>"log(B/(B*Smin))/log(B/(B-1))+B, # of RTT from Wmax-B to Wmax"</i>);
 <a name="L47" href="source/net/ipv4/tcp_bic.c#L47">47</a> 
 <a name="L48" href="source/net/ipv4/tcp_bic.c#L48">48</a> <b><i>/* BIC TCP Parameters */</i></b>
 <a name="L49" href="source/net/ipv4/tcp_bic.c#L49">49</a> struct <a href="ident?i=bictcp">bictcp</a> {
 <a name="L50" href="source/net/ipv4/tcp_bic.c#L50">50</a>         <a href="ident?i=u32">u32</a>     cnt;            <b><i>/* increase cwnd by 1 after ACKs */</i></b>
 <a name="L51" href="source/net/ipv4/tcp_bic.c#L51">51</a>         <a href="ident?i=u32">u32</a>     last_max_cwnd;  <b><i>/* last maximum snd_cwnd */</i></b>
 <a name="L52" href="source/net/ipv4/tcp_bic.c#L52">52</a>         <a href="ident?i=u32">u32</a>     loss_cwnd;      <b><i>/* congestion window at last loss */</i></b>
 <a name="L53" href="source/net/ipv4/tcp_bic.c#L53">53</a>         <a href="ident?i=u32">u32</a>     last_cwnd;      <b><i>/* the last snd_cwnd */</i></b>
 <a name="L54" href="source/net/ipv4/tcp_bic.c#L54">54</a>         <a href="ident?i=u32">u32</a>     <a href="ident?i=last_time">last_time</a>;      <b><i>/* time when updated last_cwnd */</i></b>
 <a name="L55" href="source/net/ipv4/tcp_bic.c#L55">55</a>         <a href="ident?i=u32">u32</a>     epoch_start;    <b><i>/* beginning of an epoch */</i></b>
 <a name="L56" href="source/net/ipv4/tcp_bic.c#L56">56</a> #define <a href="ident?i=ACK_RATIO_SHIFT">ACK_RATIO_SHIFT</a> 4
 <a name="L57" href="source/net/ipv4/tcp_bic.c#L57">57</a>         <a href="ident?i=u32">u32</a>     delayed_ack;    <b><i>/* estimate the ratio of Packets/ACKs &lt;&lt; 4 */</i></b>
 <a name="L58" href="source/net/ipv4/tcp_bic.c#L58">58</a> };
 <a name="L59" href="source/net/ipv4/tcp_bic.c#L59">59</a> 
 <a name="L60" href="source/net/ipv4/tcp_bic.c#L60">60</a> static inline void <a href="ident?i=bictcp_reset">bictcp_reset</a>(struct <a href="ident?i=bictcp">bictcp</a> *<a href="ident?i=ca">ca</a>)
 <a name="L61" href="source/net/ipv4/tcp_bic.c#L61">61</a> {
 <a name="L62" href="source/net/ipv4/tcp_bic.c#L62">62</a>         <a href="ident?i=ca">ca</a>-&gt;cnt = 0;
 <a name="L63" href="source/net/ipv4/tcp_bic.c#L63">63</a>         <a href="ident?i=ca">ca</a>-&gt;last_max_cwnd = 0;
 <a name="L64" href="source/net/ipv4/tcp_bic.c#L64">64</a>         <a href="ident?i=ca">ca</a>-&gt;last_cwnd = 0;
 <a name="L65" href="source/net/ipv4/tcp_bic.c#L65">65</a>         <a href="ident?i=ca">ca</a>-&gt;<a href="ident?i=last_time">last_time</a> = 0;
 <a name="L66" href="source/net/ipv4/tcp_bic.c#L66">66</a>         <a href="ident?i=ca">ca</a>-&gt;epoch_start = 0;
 <a name="L67" href="source/net/ipv4/tcp_bic.c#L67">67</a>         <a href="ident?i=ca">ca</a>-&gt;delayed_ack = 2 &lt;&lt; <a href="ident?i=ACK_RATIO_SHIFT">ACK_RATIO_SHIFT</a>;
 <a name="L68" href="source/net/ipv4/tcp_bic.c#L68">68</a> }
 <a name="L69" href="source/net/ipv4/tcp_bic.c#L69">69</a> 
 <a name="L70" href="source/net/ipv4/tcp_bic.c#L70">70</a> static void <a href="ident?i=bictcp_init">bictcp_init</a>(struct <a href="ident?i=sock">sock</a> *sk)
 <a name="L71" href="source/net/ipv4/tcp_bic.c#L71">71</a> {
 <a name="L72" href="source/net/ipv4/tcp_bic.c#L72">72</a>         struct <a href="ident?i=bictcp">bictcp</a> *<a href="ident?i=ca">ca</a> = <a href="ident?i=inet_csk_ca">inet_csk_ca</a>(sk);
 <a name="L73" href="source/net/ipv4/tcp_bic.c#L73">73</a> 
 <a name="L74" href="source/net/ipv4/tcp_bic.c#L74">74</a>         <a href="ident?i=bictcp_reset">bictcp_reset</a>(<a href="ident?i=ca">ca</a>);
 <a name="L75" href="source/net/ipv4/tcp_bic.c#L75">75</a>         <a href="ident?i=ca">ca</a>-&gt;loss_cwnd = 0;
 <a name="L76" href="source/net/ipv4/tcp_bic.c#L76">76</a> 
 <a name="L77" href="source/net/ipv4/tcp_bic.c#L77">77</a>         if (<a href="ident?i=initial_ssthresh">initial_ssthresh</a>)
 <a name="L78" href="source/net/ipv4/tcp_bic.c#L78">78</a>                 <a href="ident?i=tcp_sk">tcp_sk</a>(sk)-&gt;snd_ssthresh = <a href="ident?i=initial_ssthresh">initial_ssthresh</a>;
 <a name="L79" href="source/net/ipv4/tcp_bic.c#L79">79</a> }
 <a name="L80" href="source/net/ipv4/tcp_bic.c#L80">80</a> 
 <a name="L81" href="source/net/ipv4/tcp_bic.c#L81">81</a> <b><i>/*</i></b>
 <a name="L82" href="source/net/ipv4/tcp_bic.c#L82">82</a> <b><i> * Compute congestion window to use.</i></b>
 <a name="L83" href="source/net/ipv4/tcp_bic.c#L83">83</a> <b><i> */</i></b>
 <a name="L84" href="source/net/ipv4/tcp_bic.c#L84">84</a> static inline void <a href="ident?i=bictcp_update">bictcp_update</a>(struct <a href="ident?i=bictcp">bictcp</a> *<a href="ident?i=ca">ca</a>, <a href="ident?i=u32">u32</a> cwnd)
 <a name="L85" href="source/net/ipv4/tcp_bic.c#L85">85</a> {
 <a name="L86" href="source/net/ipv4/tcp_bic.c#L86">86</a>         if (<a href="ident?i=ca">ca</a>-&gt;last_cwnd == cwnd &amp;&amp;
 <a name="L87" href="source/net/ipv4/tcp_bic.c#L87">87</a>             (<a href="ident?i=s32">s32</a>)(<a href="ident?i=tcp_time_stamp">tcp_time_stamp</a> - <a href="ident?i=ca">ca</a>-&gt;<a href="ident?i=last_time">last_time</a>) &lt;= <a href="ident?i=HZ">HZ</a> / 32)
 <a name="L88" href="source/net/ipv4/tcp_bic.c#L88">88</a>                 return;
 <a name="L89" href="source/net/ipv4/tcp_bic.c#L89">89</a> 
 <a name="L90" href="source/net/ipv4/tcp_bic.c#L90">90</a>         <a href="ident?i=ca">ca</a>-&gt;last_cwnd = cwnd;
 <a name="L91" href="source/net/ipv4/tcp_bic.c#L91">91</a>         <a href="ident?i=ca">ca</a>-&gt;<a href="ident?i=last_time">last_time</a> = <a href="ident?i=tcp_time_stamp">tcp_time_stamp</a>;
 <a name="L92" href="source/net/ipv4/tcp_bic.c#L92">92</a> 
 <a name="L93" href="source/net/ipv4/tcp_bic.c#L93">93</a>         if (<a href="ident?i=ca">ca</a>-&gt;epoch_start == 0) <b><i>/* record the beginning of an epoch */</i></b>
 <a name="L94" href="source/net/ipv4/tcp_bic.c#L94">94</a>                 <a href="ident?i=ca">ca</a>-&gt;epoch_start = <a href="ident?i=tcp_time_stamp">tcp_time_stamp</a>;
 <a name="L95" href="source/net/ipv4/tcp_bic.c#L95">95</a> 
 <a name="L96" href="source/net/ipv4/tcp_bic.c#L96">96</a>         <b><i>/* start off normal */</i></b>
 <a name="L97" href="source/net/ipv4/tcp_bic.c#L97">97</a>         if (cwnd &lt;= <a href="ident?i=low_window">low_window</a>) {
 <a name="L98" href="source/net/ipv4/tcp_bic.c#L98">98</a>                 <a href="ident?i=ca">ca</a>-&gt;cnt = cwnd;
 <a name="L99" href="source/net/ipv4/tcp_bic.c#L99">99</a>                 return;
<a name="L100" href="source/net/ipv4/tcp_bic.c#L100">100</a>         }
<a name="L101" href="source/net/ipv4/tcp_bic.c#L101">101</a> 
<a name="L102" href="source/net/ipv4/tcp_bic.c#L102">102</a>         <b><i>/* binary increase */</i></b>
<a name="L103" href="source/net/ipv4/tcp_bic.c#L103">103</a>         if (cwnd &lt; <a href="ident?i=ca">ca</a>-&gt;last_max_cwnd) {
<a name="L104" href="source/net/ipv4/tcp_bic.c#L104">104</a>                 <a href="ident?i=__u32">__u32</a>   dist = (<a href="ident?i=ca">ca</a>-&gt;last_max_cwnd - cwnd)
<a name="L105" href="source/net/ipv4/tcp_bic.c#L105">105</a>                         / <a href="ident?i=BICTCP_B">BICTCP_B</a>;
<a name="L106" href="source/net/ipv4/tcp_bic.c#L106">106</a> 
<a name="L107" href="source/net/ipv4/tcp_bic.c#L107">107</a>                 if (dist &gt; <a href="ident?i=max_increment">max_increment</a>)
<a name="L108" href="source/net/ipv4/tcp_bic.c#L108">108</a>                         <b><i>/* linear increase */</i></b>
<a name="L109" href="source/net/ipv4/tcp_bic.c#L109">109</a>                         <a href="ident?i=ca">ca</a>-&gt;cnt = cwnd / <a href="ident?i=max_increment">max_increment</a>;
<a name="L110" href="source/net/ipv4/tcp_bic.c#L110">110</a>                 else if (dist &lt;= 1U)
<a name="L111" href="source/net/ipv4/tcp_bic.c#L111">111</a>                         <b><i>/* binary search increase */</i></b>
<a name="L112" href="source/net/ipv4/tcp_bic.c#L112">112</a>                         <a href="ident?i=ca">ca</a>-&gt;cnt = (cwnd * <a href="ident?i=smooth_part">smooth_part</a>) / <a href="ident?i=BICTCP_B">BICTCP_B</a>;
<a name="L113" href="source/net/ipv4/tcp_bic.c#L113">113</a>                 else
<a name="L114" href="source/net/ipv4/tcp_bic.c#L114">114</a>                         <b><i>/* binary search increase */</i></b>
<a name="L115" href="source/net/ipv4/tcp_bic.c#L115">115</a>                         <a href="ident?i=ca">ca</a>-&gt;cnt = cwnd / dist;
<a name="L116" href="source/net/ipv4/tcp_bic.c#L116">116</a>         } else {
<a name="L117" href="source/net/ipv4/tcp_bic.c#L117">117</a>                 <b><i>/* slow start AMD linear increase */</i></b>
<a name="L118" href="source/net/ipv4/tcp_bic.c#L118">118</a>                 if (cwnd &lt; <a href="ident?i=ca">ca</a>-&gt;last_max_cwnd + <a href="ident?i=BICTCP_B">BICTCP_B</a>)
<a name="L119" href="source/net/ipv4/tcp_bic.c#L119">119</a>                         <b><i>/* slow start */</i></b>
<a name="L120" href="source/net/ipv4/tcp_bic.c#L120">120</a>                         <a href="ident?i=ca">ca</a>-&gt;cnt = (cwnd * <a href="ident?i=smooth_part">smooth_part</a>) / <a href="ident?i=BICTCP_B">BICTCP_B</a>;
<a name="L121" href="source/net/ipv4/tcp_bic.c#L121">121</a>                 else if (cwnd &lt; <a href="ident?i=ca">ca</a>-&gt;last_max_cwnd + <a href="ident?i=max_increment">max_increment</a>*(<a href="ident?i=BICTCP_B">BICTCP_B</a>-1))
<a name="L122" href="source/net/ipv4/tcp_bic.c#L122">122</a>                         <b><i>/* slow start */</i></b>
<a name="L123" href="source/net/ipv4/tcp_bic.c#L123">123</a>                         <a href="ident?i=ca">ca</a>-&gt;cnt = (cwnd * (<a href="ident?i=BICTCP_B">BICTCP_B</a>-1))
<a name="L124" href="source/net/ipv4/tcp_bic.c#L124">124</a>                                 / (cwnd - <a href="ident?i=ca">ca</a>-&gt;last_max_cwnd);
<a name="L125" href="source/net/ipv4/tcp_bic.c#L125">125</a>                 else
<a name="L126" href="source/net/ipv4/tcp_bic.c#L126">126</a>                         <b><i>/* linear increase */</i></b>
<a name="L127" href="source/net/ipv4/tcp_bic.c#L127">127</a>                         <a href="ident?i=ca">ca</a>-&gt;cnt = cwnd / <a href="ident?i=max_increment">max_increment</a>;
<a name="L128" href="source/net/ipv4/tcp_bic.c#L128">128</a>         }
<a name="L129" href="source/net/ipv4/tcp_bic.c#L129">129</a> 
<a name="L130" href="source/net/ipv4/tcp_bic.c#L130">130</a>         <b><i>/* if in slow start or link utilization is very low */</i></b>
<a name="L131" href="source/net/ipv4/tcp_bic.c#L131">131</a>         if (<a href="ident?i=ca">ca</a>-&gt;last_max_cwnd == 0) {
<a name="L132" href="source/net/ipv4/tcp_bic.c#L132">132</a>                 if (<a href="ident?i=ca">ca</a>-&gt;cnt &gt; 20) <b><i>/* increase cwnd 5% per RTT */</i></b>
<a name="L133" href="source/net/ipv4/tcp_bic.c#L133">133</a>                         <a href="ident?i=ca">ca</a>-&gt;cnt = 20;
<a name="L134" href="source/net/ipv4/tcp_bic.c#L134">134</a>         }
<a name="L135" href="source/net/ipv4/tcp_bic.c#L135">135</a> 
<a name="L136" href="source/net/ipv4/tcp_bic.c#L136">136</a>         <a href="ident?i=ca">ca</a>-&gt;cnt = (<a href="ident?i=ca">ca</a>-&gt;cnt &lt;&lt; <a href="ident?i=ACK_RATIO_SHIFT">ACK_RATIO_SHIFT</a>) / <a href="ident?i=ca">ca</a>-&gt;delayed_ack;
<a name="L137" href="source/net/ipv4/tcp_bic.c#L137">137</a>         if (<a href="ident?i=ca">ca</a>-&gt;cnt == 0)                       <b><i>/* cannot be zero */</i></b>
<a name="L138" href="source/net/ipv4/tcp_bic.c#L138">138</a>                 <a href="ident?i=ca">ca</a>-&gt;cnt = 1;
<a name="L139" href="source/net/ipv4/tcp_bic.c#L139">139</a> }
<a name="L140" href="source/net/ipv4/tcp_bic.c#L140">140</a> 
<a name="L141" href="source/net/ipv4/tcp_bic.c#L141">141</a> static void <a href="ident?i=bictcp_cong_avoid">bictcp_cong_avoid</a>(struct <a href="ident?i=sock">sock</a> *sk, <a href="ident?i=u32">u32</a> ack, <a href="ident?i=u32">u32</a> acked)
<a name="L142" href="source/net/ipv4/tcp_bic.c#L142">142</a> {
<a name="L143" href="source/net/ipv4/tcp_bic.c#L143">143</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L144" href="source/net/ipv4/tcp_bic.c#L144">144</a>         struct <a href="ident?i=bictcp">bictcp</a> *<a href="ident?i=ca">ca</a> = <a href="ident?i=inet_csk_ca">inet_csk_ca</a>(sk);
<a name="L145" href="source/net/ipv4/tcp_bic.c#L145">145</a> 
<a name="L146" href="source/net/ipv4/tcp_bic.c#L146">146</a>         if (!<a href="ident?i=tcp_is_cwnd_limited">tcp_is_cwnd_limited</a>(sk))
<a name="L147" href="source/net/ipv4/tcp_bic.c#L147">147</a>                 return;
<a name="L148" href="source/net/ipv4/tcp_bic.c#L148">148</a> 
<a name="L149" href="source/net/ipv4/tcp_bic.c#L149">149</a>         if (<a href="ident?i=tp">tp</a>-&gt;snd_cwnd &lt;= <a href="ident?i=tp">tp</a>-&gt;snd_ssthresh)
<a name="L150" href="source/net/ipv4/tcp_bic.c#L150">150</a>                 <a href="ident?i=tcp_slow_start">tcp_slow_start</a>(<a href="ident?i=tp">tp</a>, acked);
<a name="L151" href="source/net/ipv4/tcp_bic.c#L151">151</a>         else {
<a name="L152" href="source/net/ipv4/tcp_bic.c#L152">152</a>                 <a href="ident?i=bictcp_update">bictcp_update</a>(<a href="ident?i=ca">ca</a>, <a href="ident?i=tp">tp</a>-&gt;snd_cwnd);
<a name="L153" href="source/net/ipv4/tcp_bic.c#L153">153</a>                 <a href="ident?i=tcp_cong_avoid_ai">tcp_cong_avoid_ai</a>(<a href="ident?i=tp">tp</a>, <a href="ident?i=ca">ca</a>-&gt;cnt, 1);
<a name="L154" href="source/net/ipv4/tcp_bic.c#L154">154</a>         }
<a name="L155" href="source/net/ipv4/tcp_bic.c#L155">155</a> }
<a name="L156" href="source/net/ipv4/tcp_bic.c#L156">156</a> 
<a name="L157" href="source/net/ipv4/tcp_bic.c#L157">157</a> <b><i>/*</i></b>
<a name="L158" href="source/net/ipv4/tcp_bic.c#L158">158</a> <b><i> *      behave like Reno until low_window is reached,</i></b>
<a name="L159" href="source/net/ipv4/tcp_bic.c#L159">159</a> <b><i> *      then increase congestion window slowly</i></b>
<a name="L160" href="source/net/ipv4/tcp_bic.c#L160">160</a> <b><i> */</i></b>
<a name="L161" href="source/net/ipv4/tcp_bic.c#L161">161</a> static <a href="ident?i=u32">u32</a> <a href="ident?i=bictcp_recalc_ssthresh">bictcp_recalc_ssthresh</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L162" href="source/net/ipv4/tcp_bic.c#L162">162</a> {
<a name="L163" href="source/net/ipv4/tcp_bic.c#L163">163</a>         const struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L164" href="source/net/ipv4/tcp_bic.c#L164">164</a>         struct <a href="ident?i=bictcp">bictcp</a> *<a href="ident?i=ca">ca</a> = <a href="ident?i=inet_csk_ca">inet_csk_ca</a>(sk);
<a name="L165" href="source/net/ipv4/tcp_bic.c#L165">165</a> 
<a name="L166" href="source/net/ipv4/tcp_bic.c#L166">166</a>         <a href="ident?i=ca">ca</a>-&gt;epoch_start = 0;    <b><i>/* end of epoch */</i></b>
<a name="L167" href="source/net/ipv4/tcp_bic.c#L167">167</a> 
<a name="L168" href="source/net/ipv4/tcp_bic.c#L168">168</a>         <b><i>/* Wmax and fast convergence */</i></b>
<a name="L169" href="source/net/ipv4/tcp_bic.c#L169">169</a>         if (<a href="ident?i=tp">tp</a>-&gt;snd_cwnd &lt; <a href="ident?i=ca">ca</a>-&gt;last_max_cwnd &amp;&amp; <a href="ident?i=fast_convergence">fast_convergence</a>)
<a name="L170" href="source/net/ipv4/tcp_bic.c#L170">170</a>                 <a href="ident?i=ca">ca</a>-&gt;last_max_cwnd = (<a href="ident?i=tp">tp</a>-&gt;snd_cwnd * (<a href="ident?i=BICTCP_BETA_SCALE">BICTCP_BETA_SCALE</a> + <a href="ident?i=beta">beta</a>))
<a name="L171" href="source/net/ipv4/tcp_bic.c#L171">171</a>                         / (2 * <a href="ident?i=BICTCP_BETA_SCALE">BICTCP_BETA_SCALE</a>);
<a name="L172" href="source/net/ipv4/tcp_bic.c#L172">172</a>         else
<a name="L173" href="source/net/ipv4/tcp_bic.c#L173">173</a>                 <a href="ident?i=ca">ca</a>-&gt;last_max_cwnd = <a href="ident?i=tp">tp</a>-&gt;snd_cwnd;
<a name="L174" href="source/net/ipv4/tcp_bic.c#L174">174</a> 
<a name="L175" href="source/net/ipv4/tcp_bic.c#L175">175</a>         <a href="ident?i=ca">ca</a>-&gt;loss_cwnd = <a href="ident?i=tp">tp</a>-&gt;snd_cwnd;
<a name="L176" href="source/net/ipv4/tcp_bic.c#L176">176</a> 
<a name="L177" href="source/net/ipv4/tcp_bic.c#L177">177</a>         if (<a href="ident?i=tp">tp</a>-&gt;snd_cwnd &lt;= <a href="ident?i=low_window">low_window</a>)
<a name="L178" href="source/net/ipv4/tcp_bic.c#L178">178</a>                 return <a href="ident?i=max">max</a>(<a href="ident?i=tp">tp</a>-&gt;snd_cwnd &gt;&gt; 1U, 2U);
<a name="L179" href="source/net/ipv4/tcp_bic.c#L179">179</a>         else
<a name="L180" href="source/net/ipv4/tcp_bic.c#L180">180</a>                 return <a href="ident?i=max">max</a>((<a href="ident?i=tp">tp</a>-&gt;snd_cwnd * <a href="ident?i=beta">beta</a>) / <a href="ident?i=BICTCP_BETA_SCALE">BICTCP_BETA_SCALE</a>, 2U);
<a name="L181" href="source/net/ipv4/tcp_bic.c#L181">181</a> }
<a name="L182" href="source/net/ipv4/tcp_bic.c#L182">182</a> 
<a name="L183" href="source/net/ipv4/tcp_bic.c#L183">183</a> static <a href="ident?i=u32">u32</a> <a href="ident?i=bictcp_undo_cwnd">bictcp_undo_cwnd</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L184" href="source/net/ipv4/tcp_bic.c#L184">184</a> {
<a name="L185" href="source/net/ipv4/tcp_bic.c#L185">185</a>         const struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L186" href="source/net/ipv4/tcp_bic.c#L186">186</a>         const struct <a href="ident?i=bictcp">bictcp</a> *<a href="ident?i=ca">ca</a> = <a href="ident?i=inet_csk_ca">inet_csk_ca</a>(sk);
<a name="L187" href="source/net/ipv4/tcp_bic.c#L187">187</a> 
<a name="L188" href="source/net/ipv4/tcp_bic.c#L188">188</a>         return <a href="ident?i=max">max</a>(<a href="ident?i=tp">tp</a>-&gt;snd_cwnd, <a href="ident?i=ca">ca</a>-&gt;loss_cwnd);
<a name="L189" href="source/net/ipv4/tcp_bic.c#L189">189</a> }
<a name="L190" href="source/net/ipv4/tcp_bic.c#L190">190</a> 
<a name="L191" href="source/net/ipv4/tcp_bic.c#L191">191</a> static void <a href="ident?i=bictcp_state">bictcp_state</a>(struct <a href="ident?i=sock">sock</a> *sk, <a href="ident?i=u8">u8</a> <a href="ident?i=new_state">new_state</a>)
<a name="L192" href="source/net/ipv4/tcp_bic.c#L192">192</a> {
<a name="L193" href="source/net/ipv4/tcp_bic.c#L193">193</a>         if (<a href="ident?i=new_state">new_state</a> == TCP_CA_Loss)
<a name="L194" href="source/net/ipv4/tcp_bic.c#L194">194</a>                 <a href="ident?i=bictcp_reset">bictcp_reset</a>(<a href="ident?i=inet_csk_ca">inet_csk_ca</a>(sk));
<a name="L195" href="source/net/ipv4/tcp_bic.c#L195">195</a> }
<a name="L196" href="source/net/ipv4/tcp_bic.c#L196">196</a> 
<a name="L197" href="source/net/ipv4/tcp_bic.c#L197">197</a> <b><i>/* Track delayed acknowledgment ratio using sliding window</i></b>
<a name="L198" href="source/net/ipv4/tcp_bic.c#L198">198</a> <b><i> * ratio = (15*ratio + sample) / 16</i></b>
<a name="L199" href="source/net/ipv4/tcp_bic.c#L199">199</a> <b><i> */</i></b>
<a name="L200" href="source/net/ipv4/tcp_bic.c#L200">200</a> static void <a href="ident?i=bictcp_acked">bictcp_acked</a>(struct <a href="ident?i=sock">sock</a> *sk, <a href="ident?i=u32">u32</a> cnt, <a href="ident?i=s32">s32</a> rtt)
<a name="L201" href="source/net/ipv4/tcp_bic.c#L201">201</a> {
<a name="L202" href="source/net/ipv4/tcp_bic.c#L202">202</a>         const struct <a href="ident?i=inet_connection_sock">inet_connection_sock</a> *icsk = <a href="ident?i=inet_csk">inet_csk</a>(sk);
<a name="L203" href="source/net/ipv4/tcp_bic.c#L203">203</a> 
<a name="L204" href="source/net/ipv4/tcp_bic.c#L204">204</a>         if (icsk-&gt;icsk_ca_state == TCP_CA_Open) {
<a name="L205" href="source/net/ipv4/tcp_bic.c#L205">205</a>                 struct <a href="ident?i=bictcp">bictcp</a> *<a href="ident?i=ca">ca</a> = <a href="ident?i=inet_csk_ca">inet_csk_ca</a>(sk);
<a name="L206" href="source/net/ipv4/tcp_bic.c#L206">206</a> 
<a name="L207" href="source/net/ipv4/tcp_bic.c#L207">207</a>                 cnt -= <a href="ident?i=ca">ca</a>-&gt;delayed_ack &gt;&gt; <a href="ident?i=ACK_RATIO_SHIFT">ACK_RATIO_SHIFT</a>;
<a name="L208" href="source/net/ipv4/tcp_bic.c#L208">208</a>                 <a href="ident?i=ca">ca</a>-&gt;delayed_ack += cnt;
<a name="L209" href="source/net/ipv4/tcp_bic.c#L209">209</a>         }
<a name="L210" href="source/net/ipv4/tcp_bic.c#L210">210</a> }
<a name="L211" href="source/net/ipv4/tcp_bic.c#L211">211</a> 
<a name="L212" href="source/net/ipv4/tcp_bic.c#L212">212</a> static struct <a href="ident?i=tcp_congestion_ops">tcp_congestion_ops</a> <a href="ident?i=bictcp">bictcp</a> <a href="ident?i=__read_mostly">__read_mostly</a> = {
<a name="L213" href="source/net/ipv4/tcp_bic.c#L213">213</a>         .<a href="ident?i=init">init</a>           = <a href="ident?i=bictcp_init">bictcp_init</a>,
<a name="L214" href="source/net/ipv4/tcp_bic.c#L214">214</a>         .ssthresh       = <a href="ident?i=bictcp_recalc_ssthresh">bictcp_recalc_ssthresh</a>,
<a name="L215" href="source/net/ipv4/tcp_bic.c#L215">215</a>         .cong_avoid     = <a href="ident?i=bictcp_cong_avoid">bictcp_cong_avoid</a>,
<a name="L216" href="source/net/ipv4/tcp_bic.c#L216">216</a>         .<a href="ident?i=set_state">set_state</a>      = <a href="ident?i=bictcp_state">bictcp_state</a>,
<a name="L217" href="source/net/ipv4/tcp_bic.c#L217">217</a>         .undo_cwnd      = <a href="ident?i=bictcp_undo_cwnd">bictcp_undo_cwnd</a>,
<a name="L218" href="source/net/ipv4/tcp_bic.c#L218">218</a>         .pkts_acked     = <a href="ident?i=bictcp_acked">bictcp_acked</a>,
<a name="L219" href="source/net/ipv4/tcp_bic.c#L219">219</a>         .owner          = <a href="ident?i=THIS_MODULE">THIS_MODULE</a>,
<a name="L220" href="source/net/ipv4/tcp_bic.c#L220">220</a>         .<a href="ident?i=name">name</a>           = <i>"bic"</i>,
<a name="L221" href="source/net/ipv4/tcp_bic.c#L221">221</a> };
<a name="L222" href="source/net/ipv4/tcp_bic.c#L222">222</a> 
<a name="L223" href="source/net/ipv4/tcp_bic.c#L223">223</a> static int <a href="ident?i=__init">__init</a> <a href="ident?i=bictcp_register">bictcp_register</a>(void)
<a name="L224" href="source/net/ipv4/tcp_bic.c#L224">224</a> {
<a name="L225" href="source/net/ipv4/tcp_bic.c#L225">225</a>         <a href="ident?i=BUILD_BUG_ON">BUILD_BUG_ON</a>(sizeof(struct <a href="ident?i=bictcp">bictcp</a>) &gt; <a href="ident?i=ICSK_CA_PRIV_SIZE">ICSK_CA_PRIV_SIZE</a>);
<a name="L226" href="source/net/ipv4/tcp_bic.c#L226">226</a>         return <a href="ident?i=tcp_register_congestion_control">tcp_register_congestion_control</a>(&amp;<a href="ident?i=bictcp">bictcp</a>);
<a name="L227" href="source/net/ipv4/tcp_bic.c#L227">227</a> }
<a name="L228" href="source/net/ipv4/tcp_bic.c#L228">228</a> 
<a name="L229" href="source/net/ipv4/tcp_bic.c#L229">229</a> static void <a href="ident?i=__exit">__exit</a> <a href="ident?i=bictcp_unregister">bictcp_unregister</a>(void)
<a name="L230" href="source/net/ipv4/tcp_bic.c#L230">230</a> {
<a name="L231" href="source/net/ipv4/tcp_bic.c#L231">231</a>         <a href="ident?i=tcp_unregister_congestion_control">tcp_unregister_congestion_control</a>(&amp;<a href="ident?i=bictcp">bictcp</a>);
<a name="L232" href="source/net/ipv4/tcp_bic.c#L232">232</a> }
<a name="L233" href="source/net/ipv4/tcp_bic.c#L233">233</a> 
<a name="L234" href="source/net/ipv4/tcp_bic.c#L234">234</a> <a href="ident?i=module_init">module_init</a>(<a href="ident?i=bictcp_register">bictcp_register</a>);
<a name="L235" href="source/net/ipv4/tcp_bic.c#L235">235</a> <a href="ident?i=module_exit">module_exit</a>(<a href="ident?i=bictcp_unregister">bictcp_unregister</a>);
<a name="L236" href="source/net/ipv4/tcp_bic.c#L236">236</a> 
<a name="L237" href="source/net/ipv4/tcp_bic.c#L237">237</a> <a href="ident?i=MODULE_AUTHOR">MODULE_AUTHOR</a>(<i>"Stephen Hemminger"</i>);
<a name="L238" href="source/net/ipv4/tcp_bic.c#L238">238</a> <a href="ident?i=MODULE_LICENSE">MODULE_LICENSE</a>(<i>"GPL"</i>);
<a name="L239" href="source/net/ipv4/tcp_bic.c#L239">239</a> <a href="ident?i=MODULE_DESCRIPTION">MODULE_DESCRIPTION</a>(<i>"BIC TCP"</i>);
<a name="L240" href="source/net/ipv4/tcp_bic.c#L240">240</a> </pre></div><p>
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
