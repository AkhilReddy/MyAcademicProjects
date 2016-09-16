<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title>Linux/net/ipv4/tcp_lp.c - Linux Cross Reference - Free Electrons</title>
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
		 &nbsp;&bull;&nbsp;<b><i>source navigation</i></b> &nbsp;&bull;&nbsp;<a href="diff/net/ipv4/tcp_lp.c">diff markup</a> &nbsp;&bull;&nbsp;<a href="ident">identifier search</a> &nbsp;&bull;&nbsp;<a href="search">freetext search</a> &nbsp;&bull;&nbsp;
		</p>
	</div>
</div>

<div id="topbar">
  
  <p>Version: &nbsp;<a href="source/net/ipv4/tcp_lp.c?v=2.0.40">2.0.40</a>&nbsp;<a href="source/net/ipv4/tcp_lp.c?v=2.2.26">2.2.26</a>&nbsp;<a href="source/net/ipv4/tcp_lp.c?v=2.4.37">2.4.37</a>&nbsp;<a href="source/net/ipv4/tcp_lp.c?v=3.5">3.5</a>&nbsp;<a href="source/net/ipv4/tcp_lp.c?v=3.6">3.6</a>&nbsp;<a href="source/net/ipv4/tcp_lp.c?v=3.7">3.7</a>&nbsp;<a href="source/net/ipv4/tcp_lp.c?v=3.8">3.8</a>&nbsp;<a href="source/net/ipv4/tcp_lp.c?v=3.9">3.9</a>&nbsp;<a href="source/net/ipv4/tcp_lp.c?v=3.10">3.10</a>&nbsp;<a href="source/net/ipv4/tcp_lp.c?v=3.11">3.11</a>&nbsp;<a href="source/net/ipv4/tcp_lp.c?v=3.12">3.12</a>&nbsp;<a href="source/net/ipv4/tcp_lp.c?v=3.13">3.13</a>&nbsp;<a href="source/net/ipv4/tcp_lp.c?v=3.14">3.14</a>&nbsp;<a href="source/net/ipv4/tcp_lp.c?v=3.15">3.15</a>&nbsp;<a href="source/net/ipv4/tcp_lp.c?v=3.16">3.16</a>&nbsp;<a href="source/net/ipv4/tcp_lp.c?v=3.17">3.17</a>&nbsp;<a href="source/net/ipv4/tcp_lp.c?v=3.18">3.18</a>&nbsp;<a href="source/net/ipv4/tcp_lp.c?v=3.19">3.19</a>&nbsp;<a href="source/net/ipv4/tcp_lp.c?v=4.0">4.0</a>&nbsp;<b><i>4.1</i></b></p>
  
</div>

<h1><a href="source/">Linux</a>/<a href="source/net/">net</a>/<a href="source/net/ipv4/">ipv4</a>/<a href="source/net/ipv4/tcp_lp.c">tcp_lp.c</a></h1>
<div id="lxrcode"><pre>  <a name="L1" href="source/net/ipv4/tcp_lp.c#L1">1</a> <b><i>/*</i></b>
  <a name="L2" href="source/net/ipv4/tcp_lp.c#L2">2</a> <b><i> * TCP Low Priority (TCP-LP)</i></b>
  <a name="L3" href="source/net/ipv4/tcp_lp.c#L3">3</a> <b><i> *</i></b>
  <a name="L4" href="source/net/ipv4/tcp_lp.c#L4">4</a> <b><i> * TCP Low Priority is a distributed algorithm whose goal is to utilize only</i></b>
  <a name="L5" href="source/net/ipv4/tcp_lp.c#L5">5</a> <b><i> *   the excess network bandwidth as compared to the ``fair share`` of</i></b>
  <a name="L6" href="source/net/ipv4/tcp_lp.c#L6">6</a> <b><i> *   bandwidth as targeted by TCP.</i></b>
  <a name="L7" href="source/net/ipv4/tcp_lp.c#L7">7</a> <b><i> *</i></b>
  <a name="L8" href="source/net/ipv4/tcp_lp.c#L8">8</a> <b><i> * As of 2.6.13, Linux supports pluggable congestion control algorithms.</i></b>
  <a name="L9" href="source/net/ipv4/tcp_lp.c#L9">9</a> <b><i> * Due to the limitation of the API, we take the following changes from</i></b>
 <a name="L10" href="source/net/ipv4/tcp_lp.c#L10">10</a> <b><i> * the original TCP-LP implementation:</i></b>
 <a name="L11" href="source/net/ipv4/tcp_lp.c#L11">11</a> <b><i> *   o We use newReno in most core CA handling. Only add some checking</i></b>
 <a name="L12" href="source/net/ipv4/tcp_lp.c#L12">12</a> <b><i> *     within cong_avoid.</i></b>
 <a name="L13" href="source/net/ipv4/tcp_lp.c#L13">13</a> <b><i> *   o Error correcting in remote HZ, therefore remote HZ will be keeped</i></b>
 <a name="L14" href="source/net/ipv4/tcp_lp.c#L14">14</a> <b><i> *     on checking and updating.</i></b>
 <a name="L15" href="source/net/ipv4/tcp_lp.c#L15">15</a> <b><i> *   o Handling calculation of One-Way-Delay (OWD) within rtt_sample, since</i></b>
 <a name="L16" href="source/net/ipv4/tcp_lp.c#L16">16</a> <b><i> *     OWD have a similar meaning as RTT. Also correct the buggy formular.</i></b>
 <a name="L17" href="source/net/ipv4/tcp_lp.c#L17">17</a> <b><i> *   o Handle reaction for Early Congestion Indication (ECI) within</i></b>
 <a name="L18" href="source/net/ipv4/tcp_lp.c#L18">18</a> <b><i> *     pkts_acked, as mentioned within pseudo code.</i></b>
 <a name="L19" href="source/net/ipv4/tcp_lp.c#L19">19</a> <b><i> *   o OWD is handled in relative format, where local time stamp will in</i></b>
 <a name="L20" href="source/net/ipv4/tcp_lp.c#L20">20</a> <b><i> *     tcp_time_stamp format.</i></b>
 <a name="L21" href="source/net/ipv4/tcp_lp.c#L21">21</a> <b><i> *</i></b>
 <a name="L22" href="source/net/ipv4/tcp_lp.c#L22">22</a> <b><i> * Original Author:</i></b>
 <a name="L23" href="source/net/ipv4/tcp_lp.c#L23">23</a> <b><i> *   Aleksandar Kuzmanovic &lt;akuzma@northwestern.edu&gt;</i></b>
 <a name="L24" href="source/net/ipv4/tcp_lp.c#L24">24</a> <b><i> * Available from:</i></b>
 <a name="L25" href="source/net/ipv4/tcp_lp.c#L25">25</a> <b><i> *   <a href="http://www.ece.rice.edu/~akuzma/Doc/akuzma/TCP-LP.pdf">http://www.ece.rice.edu/~akuzma/Doc/akuzma/TCP-LP.pdf</a></i></b>
 <a name="L26" href="source/net/ipv4/tcp_lp.c#L26">26</a> <b><i> * Original implementation for 2.4.19:</i></b>
 <a name="L27" href="source/net/ipv4/tcp_lp.c#L27">27</a> <b><i> *   <a href="http://www-ece.rice.edu/networks/TCP-LP/">http://www-ece.rice.edu/networks/TCP-LP/</a></i></b>
 <a name="L28" href="source/net/ipv4/tcp_lp.c#L28">28</a> <b><i> *</i></b>
 <a name="L29" href="source/net/ipv4/tcp_lp.c#L29">29</a> <b><i> * 2.6.x module Authors:</i></b>
 <a name="L30" href="source/net/ipv4/tcp_lp.c#L30">30</a> <b><i> *   Wong Hoi Sing, Edison &lt;hswong3i@gmail.com&gt;</i></b>
 <a name="L31" href="source/net/ipv4/tcp_lp.c#L31">31</a> <b><i> *   Hung Hing Lun, Mike &lt;hlhung3i@gmail.com&gt;</i></b>
 <a name="L32" href="source/net/ipv4/tcp_lp.c#L32">32</a> <b><i> * SourceForge project page:</i></b>
 <a name="L33" href="source/net/ipv4/tcp_lp.c#L33">33</a> <b><i> *   <a href="http://tcp-lp-mod.sourceforge.net/">http://tcp-lp-mod.sourceforge.net/</a></i></b>
 <a name="L34" href="source/net/ipv4/tcp_lp.c#L34">34</a> <b><i> */</i></b>
 <a name="L35" href="source/net/ipv4/tcp_lp.c#L35">35</a> 
 <a name="L36" href="source/net/ipv4/tcp_lp.c#L36">36</a> #include &lt;linux/module.h&gt;
 <a name="L37" href="source/net/ipv4/tcp_lp.c#L37">37</a> #include &lt;net/tcp.h&gt;
 <a name="L38" href="source/net/ipv4/tcp_lp.c#L38">38</a> 
 <a name="L39" href="source/net/ipv4/tcp_lp.c#L39">39</a> <b><i>/* resolution of owd */</i></b>
 <a name="L40" href="source/net/ipv4/tcp_lp.c#L40">40</a> #define <a href="ident?i=LP_RESOL">LP_RESOL</a>       1000
 <a name="L41" href="source/net/ipv4/tcp_lp.c#L41">41</a> 
 <a name="L42" href="source/net/ipv4/tcp_lp.c#L42">42</a> <b><i>/**</i></b>
 <a name="L43" href="source/net/ipv4/tcp_lp.c#L43">43</a> <b><i> * enum tcp_lp_state</i></b>
 <a name="L44" href="source/net/ipv4/tcp_lp.c#L44">44</a> <b><i> * @LP_VALID_RHZ: is remote HZ valid?</i></b>
 <a name="L45" href="source/net/ipv4/tcp_lp.c#L45">45</a> <b><i> * @LP_VALID_OWD: is OWD valid?</i></b>
 <a name="L46" href="source/net/ipv4/tcp_lp.c#L46">46</a> <b><i> * @LP_WITHIN_THR: are we within threshold?</i></b>
 <a name="L47" href="source/net/ipv4/tcp_lp.c#L47">47</a> <b><i> * @LP_WITHIN_INF: are we within inference?</i></b>
 <a name="L48" href="source/net/ipv4/tcp_lp.c#L48">48</a> <b><i> *</i></b>
 <a name="L49" href="source/net/ipv4/tcp_lp.c#L49">49</a> <b><i> * TCP-LP's state flags.</i></b>
 <a name="L50" href="source/net/ipv4/tcp_lp.c#L50">50</a> <b><i> * We create this set of state flag mainly for debugging.</i></b>
 <a name="L51" href="source/net/ipv4/tcp_lp.c#L51">51</a> <b><i> */</i></b>
 <a name="L52" href="source/net/ipv4/tcp_lp.c#L52">52</a> enum <a href="ident?i=tcp_lp_state">tcp_lp_state</a> {
 <a name="L53" href="source/net/ipv4/tcp_lp.c#L53">53</a>         LP_VALID_RHZ = (1 &lt;&lt; 0),
 <a name="L54" href="source/net/ipv4/tcp_lp.c#L54">54</a>         LP_VALID_OWD = (1 &lt;&lt; 1),
 <a name="L55" href="source/net/ipv4/tcp_lp.c#L55">55</a>         LP_WITHIN_THR = (1 &lt;&lt; 3),
 <a name="L56" href="source/net/ipv4/tcp_lp.c#L56">56</a>         LP_WITHIN_INF = (1 &lt;&lt; 4),
 <a name="L57" href="source/net/ipv4/tcp_lp.c#L57">57</a> };
 <a name="L58" href="source/net/ipv4/tcp_lp.c#L58">58</a> 
 <a name="L59" href="source/net/ipv4/tcp_lp.c#L59">59</a> <b><i>/**</i></b>
 <a name="L60" href="source/net/ipv4/tcp_lp.c#L60">60</a> <b><i> * struct lp</i></b>
 <a name="L61" href="source/net/ipv4/tcp_lp.c#L61">61</a> <b><i> * @flag: TCP-LP state flag</i></b>
 <a name="L62" href="source/net/ipv4/tcp_lp.c#L62">62</a> <b><i> * @sowd: smoothed OWD &lt;&lt; 3</i></b>
 <a name="L63" href="source/net/ipv4/tcp_lp.c#L63">63</a> <b><i> * @owd_min: min OWD</i></b>
 <a name="L64" href="source/net/ipv4/tcp_lp.c#L64">64</a> <b><i> * @owd_max: max OWD</i></b>
 <a name="L65" href="source/net/ipv4/tcp_lp.c#L65">65</a> <b><i> * @owd_max_rsv: resrved max owd</i></b>
 <a name="L66" href="source/net/ipv4/tcp_lp.c#L66">66</a> <b><i> * @remote_hz: estimated remote HZ</i></b>
 <a name="L67" href="source/net/ipv4/tcp_lp.c#L67">67</a> <b><i> * @remote_ref_time: remote reference time</i></b>
 <a name="L68" href="source/net/ipv4/tcp_lp.c#L68">68</a> <b><i> * @local_ref_time: local reference time</i></b>
 <a name="L69" href="source/net/ipv4/tcp_lp.c#L69">69</a> <b><i> * @last_drop: time for last active drop</i></b>
 <a name="L70" href="source/net/ipv4/tcp_lp.c#L70">70</a> <b><i> * @inference: current inference</i></b>
 <a name="L71" href="source/net/ipv4/tcp_lp.c#L71">71</a> <b><i> *</i></b>
 <a name="L72" href="source/net/ipv4/tcp_lp.c#L72">72</a> <b><i> * TCP-LP's private struct.</i></b>
 <a name="L73" href="source/net/ipv4/tcp_lp.c#L73">73</a> <b><i> * We get the idea from original TCP-LP implementation where only left those we</i></b>
 <a name="L74" href="source/net/ipv4/tcp_lp.c#L74">74</a> <b><i> * found are really useful.</i></b>
 <a name="L75" href="source/net/ipv4/tcp_lp.c#L75">75</a> <b><i> */</i></b>
 <a name="L76" href="source/net/ipv4/tcp_lp.c#L76">76</a> struct <a href="ident?i=lp">lp</a> {
 <a name="L77" href="source/net/ipv4/tcp_lp.c#L77">77</a>         <a href="ident?i=u32">u32</a> <a href="ident?i=flag">flag</a>;
 <a name="L78" href="source/net/ipv4/tcp_lp.c#L78">78</a>         <a href="ident?i=u32">u32</a> sowd;
 <a name="L79" href="source/net/ipv4/tcp_lp.c#L79">79</a>         <a href="ident?i=u32">u32</a> owd_min;
 <a name="L80" href="source/net/ipv4/tcp_lp.c#L80">80</a>         <a href="ident?i=u32">u32</a> owd_max;
 <a name="L81" href="source/net/ipv4/tcp_lp.c#L81">81</a>         <a href="ident?i=u32">u32</a> owd_max_rsv;
 <a name="L82" href="source/net/ipv4/tcp_lp.c#L82">82</a>         <a href="ident?i=u32">u32</a> remote_hz;
 <a name="L83" href="source/net/ipv4/tcp_lp.c#L83">83</a>         <a href="ident?i=u32">u32</a> remote_ref_time;
 <a name="L84" href="source/net/ipv4/tcp_lp.c#L84">84</a>         <a href="ident?i=u32">u32</a> local_ref_time;
 <a name="L85" href="source/net/ipv4/tcp_lp.c#L85">85</a>         <a href="ident?i=u32">u32</a> last_drop;
 <a name="L86" href="source/net/ipv4/tcp_lp.c#L86">86</a>         <a href="ident?i=u32">u32</a> inference;
 <a name="L87" href="source/net/ipv4/tcp_lp.c#L87">87</a> };
 <a name="L88" href="source/net/ipv4/tcp_lp.c#L88">88</a> 
 <a name="L89" href="source/net/ipv4/tcp_lp.c#L89">89</a> <b><i>/**</i></b>
 <a name="L90" href="source/net/ipv4/tcp_lp.c#L90">90</a> <b><i> * tcp_lp_init</i></b>
 <a name="L91" href="source/net/ipv4/tcp_lp.c#L91">91</a> <b><i> *</i></b>
 <a name="L92" href="source/net/ipv4/tcp_lp.c#L92">92</a> <b><i> * Init all required variables.</i></b>
 <a name="L93" href="source/net/ipv4/tcp_lp.c#L93">93</a> <b><i> * Clone the handling from Vegas module implementation.</i></b>
 <a name="L94" href="source/net/ipv4/tcp_lp.c#L94">94</a> <b><i> */</i></b>
 <a name="L95" href="source/net/ipv4/tcp_lp.c#L95">95</a> static void <a href="ident?i=tcp_lp_init">tcp_lp_init</a>(struct <a href="ident?i=sock">sock</a> *sk)
 <a name="L96" href="source/net/ipv4/tcp_lp.c#L96">96</a> {
 <a name="L97" href="source/net/ipv4/tcp_lp.c#L97">97</a>         struct <a href="ident?i=lp">lp</a> *<a href="ident?i=lp">lp</a> = <a href="ident?i=inet_csk_ca">inet_csk_ca</a>(sk);
 <a name="L98" href="source/net/ipv4/tcp_lp.c#L98">98</a> 
 <a name="L99" href="source/net/ipv4/tcp_lp.c#L99">99</a>         <a href="ident?i=lp">lp</a>-&gt;<a href="ident?i=flag">flag</a> = 0;
<a name="L100" href="source/net/ipv4/tcp_lp.c#L100">100</a>         <a href="ident?i=lp">lp</a>-&gt;sowd = 0;
<a name="L101" href="source/net/ipv4/tcp_lp.c#L101">101</a>         <a href="ident?i=lp">lp</a>-&gt;owd_min = 0xffffffff;
<a name="L102" href="source/net/ipv4/tcp_lp.c#L102">102</a>         <a href="ident?i=lp">lp</a>-&gt;owd_max = 0;
<a name="L103" href="source/net/ipv4/tcp_lp.c#L103">103</a>         <a href="ident?i=lp">lp</a>-&gt;owd_max_rsv = 0;
<a name="L104" href="source/net/ipv4/tcp_lp.c#L104">104</a>         <a href="ident?i=lp">lp</a>-&gt;remote_hz = 0;
<a name="L105" href="source/net/ipv4/tcp_lp.c#L105">105</a>         <a href="ident?i=lp">lp</a>-&gt;remote_ref_time = 0;
<a name="L106" href="source/net/ipv4/tcp_lp.c#L106">106</a>         <a href="ident?i=lp">lp</a>-&gt;local_ref_time = 0;
<a name="L107" href="source/net/ipv4/tcp_lp.c#L107">107</a>         <a href="ident?i=lp">lp</a>-&gt;last_drop = 0;
<a name="L108" href="source/net/ipv4/tcp_lp.c#L108">108</a>         <a href="ident?i=lp">lp</a>-&gt;inference = 0;
<a name="L109" href="source/net/ipv4/tcp_lp.c#L109">109</a> }
<a name="L110" href="source/net/ipv4/tcp_lp.c#L110">110</a> 
<a name="L111" href="source/net/ipv4/tcp_lp.c#L111">111</a> <b><i>/**</i></b>
<a name="L112" href="source/net/ipv4/tcp_lp.c#L112">112</a> <b><i> * tcp_lp_cong_avoid</i></b>
<a name="L113" href="source/net/ipv4/tcp_lp.c#L113">113</a> <b><i> *</i></b>
<a name="L114" href="source/net/ipv4/tcp_lp.c#L114">114</a> <b><i> * Implementation of cong_avoid.</i></b>
<a name="L115" href="source/net/ipv4/tcp_lp.c#L115">115</a> <b><i> * Will only call newReno CA when away from inference.</i></b>
<a name="L116" href="source/net/ipv4/tcp_lp.c#L116">116</a> <b><i> * From TCP-LP's paper, this will be handled in additive increasement.</i></b>
<a name="L117" href="source/net/ipv4/tcp_lp.c#L117">117</a> <b><i> */</i></b>
<a name="L118" href="source/net/ipv4/tcp_lp.c#L118">118</a> static void <a href="ident?i=tcp_lp_cong_avoid">tcp_lp_cong_avoid</a>(struct <a href="ident?i=sock">sock</a> *sk, <a href="ident?i=u32">u32</a> ack, <a href="ident?i=u32">u32</a> acked)
<a name="L119" href="source/net/ipv4/tcp_lp.c#L119">119</a> {
<a name="L120" href="source/net/ipv4/tcp_lp.c#L120">120</a>         struct <a href="ident?i=lp">lp</a> *<a href="ident?i=lp">lp</a> = <a href="ident?i=inet_csk_ca">inet_csk_ca</a>(sk);
<a name="L121" href="source/net/ipv4/tcp_lp.c#L121">121</a> 
<a name="L122" href="source/net/ipv4/tcp_lp.c#L122">122</a>         if (!(<a href="ident?i=lp">lp</a>-&gt;<a href="ident?i=flag">flag</a> &amp; LP_WITHIN_INF))
<a name="L123" href="source/net/ipv4/tcp_lp.c#L123">123</a>                 <a href="ident?i=tcp_reno_cong_avoid">tcp_reno_cong_avoid</a>(sk, ack, acked);
<a name="L124" href="source/net/ipv4/tcp_lp.c#L124">124</a> }
<a name="L125" href="source/net/ipv4/tcp_lp.c#L125">125</a> 
<a name="L126" href="source/net/ipv4/tcp_lp.c#L126">126</a> <b><i>/**</i></b>
<a name="L127" href="source/net/ipv4/tcp_lp.c#L127">127</a> <b><i> * tcp_lp_remote_hz_estimator</i></b>
<a name="L128" href="source/net/ipv4/tcp_lp.c#L128">128</a> <b><i> *</i></b>
<a name="L129" href="source/net/ipv4/tcp_lp.c#L129">129</a> <b><i> * Estimate remote HZ.</i></b>
<a name="L130" href="source/net/ipv4/tcp_lp.c#L130">130</a> <b><i> * We keep on updating the estimated value, where original TCP-LP</i></b>
<a name="L131" href="source/net/ipv4/tcp_lp.c#L131">131</a> <b><i> * implementation only guest it for once and use forever.</i></b>
<a name="L132" href="source/net/ipv4/tcp_lp.c#L132">132</a> <b><i> */</i></b>
<a name="L133" href="source/net/ipv4/tcp_lp.c#L133">133</a> static <a href="ident?i=u32">u32</a> <a href="ident?i=tcp_lp_remote_hz_estimator">tcp_lp_remote_hz_estimator</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L134" href="source/net/ipv4/tcp_lp.c#L134">134</a> {
<a name="L135" href="source/net/ipv4/tcp_lp.c#L135">135</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L136" href="source/net/ipv4/tcp_lp.c#L136">136</a>         struct <a href="ident?i=lp">lp</a> *<a href="ident?i=lp">lp</a> = <a href="ident?i=inet_csk_ca">inet_csk_ca</a>(sk);
<a name="L137" href="source/net/ipv4/tcp_lp.c#L137">137</a>         <a href="ident?i=s64">s64</a> rhz = <a href="ident?i=lp">lp</a>-&gt;remote_hz &lt;&lt; 6;   <b><i>/* remote HZ &lt;&lt; 6 */</i></b>
<a name="L138" href="source/net/ipv4/tcp_lp.c#L138">138</a>         <a href="ident?i=s64">s64</a> <a href="ident?i=m">m</a> = 0;
<a name="L139" href="source/net/ipv4/tcp_lp.c#L139">139</a> 
<a name="L140" href="source/net/ipv4/tcp_lp.c#L140">140</a>         <b><i>/* not yet record reference time</i></b>
<a name="L141" href="source/net/ipv4/tcp_lp.c#L141">141</a> <b><i>         * go away!! record it before come back!! */</i></b>
<a name="L142" href="source/net/ipv4/tcp_lp.c#L142">142</a>         if (<a href="ident?i=lp">lp</a>-&gt;remote_ref_time == 0 || <a href="ident?i=lp">lp</a>-&gt;local_ref_time == 0)
<a name="L143" href="source/net/ipv4/tcp_lp.c#L143">143</a>                 goto <a href="ident?i=out">out</a>;
<a name="L144" href="source/net/ipv4/tcp_lp.c#L144">144</a> 
<a name="L145" href="source/net/ipv4/tcp_lp.c#L145">145</a>         <b><i>/* we can't calc remote HZ with no different!! */</i></b>
<a name="L146" href="source/net/ipv4/tcp_lp.c#L146">146</a>         if (<a href="ident?i=tp">tp</a>-&gt;rx_opt.rcv_tsval == <a href="ident?i=lp">lp</a>-&gt;remote_ref_time ||
<a name="L147" href="source/net/ipv4/tcp_lp.c#L147">147</a>             <a href="ident?i=tp">tp</a>-&gt;rx_opt.rcv_tsecr == <a href="ident?i=lp">lp</a>-&gt;local_ref_time)
<a name="L148" href="source/net/ipv4/tcp_lp.c#L148">148</a>                 goto <a href="ident?i=out">out</a>;
<a name="L149" href="source/net/ipv4/tcp_lp.c#L149">149</a> 
<a name="L150" href="source/net/ipv4/tcp_lp.c#L150">150</a>         <a href="ident?i=m">m</a> = <a href="ident?i=HZ">HZ</a> * (<a href="ident?i=tp">tp</a>-&gt;rx_opt.rcv_tsval -
<a name="L151" href="source/net/ipv4/tcp_lp.c#L151">151</a>                   <a href="ident?i=lp">lp</a>-&gt;remote_ref_time) / (<a href="ident?i=tp">tp</a>-&gt;rx_opt.rcv_tsecr -
<a name="L152" href="source/net/ipv4/tcp_lp.c#L152">152</a>                                           <a href="ident?i=lp">lp</a>-&gt;local_ref_time);
<a name="L153" href="source/net/ipv4/tcp_lp.c#L153">153</a>         if (<a href="ident?i=m">m</a> &lt; 0)
<a name="L154" href="source/net/ipv4/tcp_lp.c#L154">154</a>                 <a href="ident?i=m">m</a> = -<a href="ident?i=m">m</a>;
<a name="L155" href="source/net/ipv4/tcp_lp.c#L155">155</a> 
<a name="L156" href="source/net/ipv4/tcp_lp.c#L156">156</a>         if (rhz &gt; 0) {
<a name="L157" href="source/net/ipv4/tcp_lp.c#L157">157</a>                 <a href="ident?i=m">m</a> -= rhz &gt;&gt; 6;  <b><i>/* m is now error in remote HZ est */</i></b>
<a name="L158" href="source/net/ipv4/tcp_lp.c#L158">158</a>                 rhz += <a href="ident?i=m">m</a>;       <b><i>/* 63/64 old + 1/64 new */</i></b>
<a name="L159" href="source/net/ipv4/tcp_lp.c#L159">159</a>         } else
<a name="L160" href="source/net/ipv4/tcp_lp.c#L160">160</a>                 rhz = <a href="ident?i=m">m</a> &lt;&lt; 6;
<a name="L161" href="source/net/ipv4/tcp_lp.c#L161">161</a> 
<a name="L162" href="source/net/ipv4/tcp_lp.c#L162">162</a>  <a href="ident?i=out">out</a>:
<a name="L163" href="source/net/ipv4/tcp_lp.c#L163">163</a>         <b><i>/* record time for successful remote HZ calc */</i></b>
<a name="L164" href="source/net/ipv4/tcp_lp.c#L164">164</a>         if ((rhz &gt;&gt; 6) &gt; 0)
<a name="L165" href="source/net/ipv4/tcp_lp.c#L165">165</a>                 <a href="ident?i=lp">lp</a>-&gt;<a href="ident?i=flag">flag</a> |= LP_VALID_RHZ;
<a name="L166" href="source/net/ipv4/tcp_lp.c#L166">166</a>         else
<a name="L167" href="source/net/ipv4/tcp_lp.c#L167">167</a>                 <a href="ident?i=lp">lp</a>-&gt;<a href="ident?i=flag">flag</a> &amp;= ~LP_VALID_RHZ;
<a name="L168" href="source/net/ipv4/tcp_lp.c#L168">168</a> 
<a name="L169" href="source/net/ipv4/tcp_lp.c#L169">169</a>         <b><i>/* record reference time stamp */</i></b>
<a name="L170" href="source/net/ipv4/tcp_lp.c#L170">170</a>         <a href="ident?i=lp">lp</a>-&gt;remote_ref_time = <a href="ident?i=tp">tp</a>-&gt;rx_opt.rcv_tsval;
<a name="L171" href="source/net/ipv4/tcp_lp.c#L171">171</a>         <a href="ident?i=lp">lp</a>-&gt;local_ref_time = <a href="ident?i=tp">tp</a>-&gt;rx_opt.rcv_tsecr;
<a name="L172" href="source/net/ipv4/tcp_lp.c#L172">172</a> 
<a name="L173" href="source/net/ipv4/tcp_lp.c#L173">173</a>         return rhz &gt;&gt; 6;
<a name="L174" href="source/net/ipv4/tcp_lp.c#L174">174</a> }
<a name="L175" href="source/net/ipv4/tcp_lp.c#L175">175</a> 
<a name="L176" href="source/net/ipv4/tcp_lp.c#L176">176</a> <b><i>/**</i></b>
<a name="L177" href="source/net/ipv4/tcp_lp.c#L177">177</a> <b><i> * tcp_lp_owd_calculator</i></b>
<a name="L178" href="source/net/ipv4/tcp_lp.c#L178">178</a> <b><i> *</i></b>
<a name="L179" href="source/net/ipv4/tcp_lp.c#L179">179</a> <b><i> * Calculate one way delay (in relative format).</i></b>
<a name="L180" href="source/net/ipv4/tcp_lp.c#L180">180</a> <b><i> * Original implement OWD as minus of remote time difference to local time</i></b>
<a name="L181" href="source/net/ipv4/tcp_lp.c#L181">181</a> <b><i> * difference directly. As this time difference just simply equal to RTT, when</i></b>
<a name="L182" href="source/net/ipv4/tcp_lp.c#L182">182</a> <b><i> * the network status is stable, remote RTT will equal to local RTT, and result</i></b>
<a name="L183" href="source/net/ipv4/tcp_lp.c#L183">183</a> <b><i> * OWD into zero.</i></b>
<a name="L184" href="source/net/ipv4/tcp_lp.c#L184">184</a> <b><i> * It seems to be a bug and so we fixed it.</i></b>
<a name="L185" href="source/net/ipv4/tcp_lp.c#L185">185</a> <b><i> */</i></b>
<a name="L186" href="source/net/ipv4/tcp_lp.c#L186">186</a> static <a href="ident?i=u32">u32</a> <a href="ident?i=tcp_lp_owd_calculator">tcp_lp_owd_calculator</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L187" href="source/net/ipv4/tcp_lp.c#L187">187</a> {
<a name="L188" href="source/net/ipv4/tcp_lp.c#L188">188</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L189" href="source/net/ipv4/tcp_lp.c#L189">189</a>         struct <a href="ident?i=lp">lp</a> *<a href="ident?i=lp">lp</a> = <a href="ident?i=inet_csk_ca">inet_csk_ca</a>(sk);
<a name="L190" href="source/net/ipv4/tcp_lp.c#L190">190</a>         <a href="ident?i=s64">s64</a> owd = 0;
<a name="L191" href="source/net/ipv4/tcp_lp.c#L191">191</a> 
<a name="L192" href="source/net/ipv4/tcp_lp.c#L192">192</a>         <a href="ident?i=lp">lp</a>-&gt;remote_hz = <a href="ident?i=tcp_lp_remote_hz_estimator">tcp_lp_remote_hz_estimator</a>(sk);
<a name="L193" href="source/net/ipv4/tcp_lp.c#L193">193</a> 
<a name="L194" href="source/net/ipv4/tcp_lp.c#L194">194</a>         if (<a href="ident?i=lp">lp</a>-&gt;<a href="ident?i=flag">flag</a> &amp; LP_VALID_RHZ) {
<a name="L195" href="source/net/ipv4/tcp_lp.c#L195">195</a>                 owd =
<a name="L196" href="source/net/ipv4/tcp_lp.c#L196">196</a>                     <a href="ident?i=tp">tp</a>-&gt;rx_opt.rcv_tsval * (<a href="ident?i=LP_RESOL">LP_RESOL</a> / <a href="ident?i=lp">lp</a>-&gt;remote_hz) -
<a name="L197" href="source/net/ipv4/tcp_lp.c#L197">197</a>                     <a href="ident?i=tp">tp</a>-&gt;rx_opt.rcv_tsecr * (<a href="ident?i=LP_RESOL">LP_RESOL</a> / <a href="ident?i=HZ">HZ</a>);
<a name="L198" href="source/net/ipv4/tcp_lp.c#L198">198</a>                 if (owd &lt; 0)
<a name="L199" href="source/net/ipv4/tcp_lp.c#L199">199</a>                         owd = -owd;
<a name="L200" href="source/net/ipv4/tcp_lp.c#L200">200</a>         }
<a name="L201" href="source/net/ipv4/tcp_lp.c#L201">201</a> 
<a name="L202" href="source/net/ipv4/tcp_lp.c#L202">202</a>         if (owd &gt; 0)
<a name="L203" href="source/net/ipv4/tcp_lp.c#L203">203</a>                 <a href="ident?i=lp">lp</a>-&gt;<a href="ident?i=flag">flag</a> |= LP_VALID_OWD;
<a name="L204" href="source/net/ipv4/tcp_lp.c#L204">204</a>         else
<a name="L205" href="source/net/ipv4/tcp_lp.c#L205">205</a>                 <a href="ident?i=lp">lp</a>-&gt;<a href="ident?i=flag">flag</a> &amp;= ~LP_VALID_OWD;
<a name="L206" href="source/net/ipv4/tcp_lp.c#L206">206</a> 
<a name="L207" href="source/net/ipv4/tcp_lp.c#L207">207</a>         return owd;
<a name="L208" href="source/net/ipv4/tcp_lp.c#L208">208</a> }
<a name="L209" href="source/net/ipv4/tcp_lp.c#L209">209</a> 
<a name="L210" href="source/net/ipv4/tcp_lp.c#L210">210</a> <b><i>/**</i></b>
<a name="L211" href="source/net/ipv4/tcp_lp.c#L211">211</a> <b><i> * tcp_lp_rtt_sample</i></b>
<a name="L212" href="source/net/ipv4/tcp_lp.c#L212">212</a> <b><i> *</i></b>
<a name="L213" href="source/net/ipv4/tcp_lp.c#L213">213</a> <b><i> * Implementation or rtt_sample.</i></b>
<a name="L214" href="source/net/ipv4/tcp_lp.c#L214">214</a> <b><i> * Will take the following action,</i></b>
<a name="L215" href="source/net/ipv4/tcp_lp.c#L215">215</a> <b><i> *   1. calc OWD,</i></b>
<a name="L216" href="source/net/ipv4/tcp_lp.c#L216">216</a> <b><i> *   2. record the min/max OWD,</i></b>
<a name="L217" href="source/net/ipv4/tcp_lp.c#L217">217</a> <b><i> *   3. calc smoothed OWD (SOWD).</i></b>
<a name="L218" href="source/net/ipv4/tcp_lp.c#L218">218</a> <b><i> * Most ideas come from the original TCP-LP implementation.</i></b>
<a name="L219" href="source/net/ipv4/tcp_lp.c#L219">219</a> <b><i> */</i></b>
<a name="L220" href="source/net/ipv4/tcp_lp.c#L220">220</a> static void <a href="ident?i=tcp_lp_rtt_sample">tcp_lp_rtt_sample</a>(struct <a href="ident?i=sock">sock</a> *sk, <a href="ident?i=u32">u32</a> rtt)
<a name="L221" href="source/net/ipv4/tcp_lp.c#L221">221</a> {
<a name="L222" href="source/net/ipv4/tcp_lp.c#L222">222</a>         struct <a href="ident?i=lp">lp</a> *<a href="ident?i=lp">lp</a> = <a href="ident?i=inet_csk_ca">inet_csk_ca</a>(sk);
<a name="L223" href="source/net/ipv4/tcp_lp.c#L223">223</a>         <a href="ident?i=s64">s64</a> mowd = <a href="ident?i=tcp_lp_owd_calculator">tcp_lp_owd_calculator</a>(sk);
<a name="L224" href="source/net/ipv4/tcp_lp.c#L224">224</a> 
<a name="L225" href="source/net/ipv4/tcp_lp.c#L225">225</a>         <b><i>/* sorry that we don't have valid data */</i></b>
<a name="L226" href="source/net/ipv4/tcp_lp.c#L226">226</a>         if (!(<a href="ident?i=lp">lp</a>-&gt;<a href="ident?i=flag">flag</a> &amp; LP_VALID_RHZ) || !(<a href="ident?i=lp">lp</a>-&gt;<a href="ident?i=flag">flag</a> &amp; LP_VALID_OWD))
<a name="L227" href="source/net/ipv4/tcp_lp.c#L227">227</a>                 return;
<a name="L228" href="source/net/ipv4/tcp_lp.c#L228">228</a> 
<a name="L229" href="source/net/ipv4/tcp_lp.c#L229">229</a>         <b><i>/* record the next min owd */</i></b>
<a name="L230" href="source/net/ipv4/tcp_lp.c#L230">230</a>         if (mowd &lt; <a href="ident?i=lp">lp</a>-&gt;owd_min)
<a name="L231" href="source/net/ipv4/tcp_lp.c#L231">231</a>                 <a href="ident?i=lp">lp</a>-&gt;owd_min = mowd;
<a name="L232" href="source/net/ipv4/tcp_lp.c#L232">232</a> 
<a name="L233" href="source/net/ipv4/tcp_lp.c#L233">233</a>         <b><i>/* always forget the max of the max</i></b>
<a name="L234" href="source/net/ipv4/tcp_lp.c#L234">234</a> <b><i>         * we just set owd_max as one below it */</i></b>
<a name="L235" href="source/net/ipv4/tcp_lp.c#L235">235</a>         if (mowd &gt; <a href="ident?i=lp">lp</a>-&gt;owd_max) {
<a name="L236" href="source/net/ipv4/tcp_lp.c#L236">236</a>                 if (mowd &gt; <a href="ident?i=lp">lp</a>-&gt;owd_max_rsv) {
<a name="L237" href="source/net/ipv4/tcp_lp.c#L237">237</a>                         if (<a href="ident?i=lp">lp</a>-&gt;owd_max_rsv == 0)
<a name="L238" href="source/net/ipv4/tcp_lp.c#L238">238</a>                                 <a href="ident?i=lp">lp</a>-&gt;owd_max = mowd;
<a name="L239" href="source/net/ipv4/tcp_lp.c#L239">239</a>                         else
<a name="L240" href="source/net/ipv4/tcp_lp.c#L240">240</a>                                 <a href="ident?i=lp">lp</a>-&gt;owd_max = <a href="ident?i=lp">lp</a>-&gt;owd_max_rsv;
<a name="L241" href="source/net/ipv4/tcp_lp.c#L241">241</a>                         <a href="ident?i=lp">lp</a>-&gt;owd_max_rsv = mowd;
<a name="L242" href="source/net/ipv4/tcp_lp.c#L242">242</a>                 } else
<a name="L243" href="source/net/ipv4/tcp_lp.c#L243">243</a>                         <a href="ident?i=lp">lp</a>-&gt;owd_max = mowd;
<a name="L244" href="source/net/ipv4/tcp_lp.c#L244">244</a>         }
<a name="L245" href="source/net/ipv4/tcp_lp.c#L245">245</a> 
<a name="L246" href="source/net/ipv4/tcp_lp.c#L246">246</a>         <b><i>/* calc for smoothed owd */</i></b>
<a name="L247" href="source/net/ipv4/tcp_lp.c#L247">247</a>         if (<a href="ident?i=lp">lp</a>-&gt;sowd != 0) {
<a name="L248" href="source/net/ipv4/tcp_lp.c#L248">248</a>                 mowd -= <a href="ident?i=lp">lp</a>-&gt;sowd &gt;&gt; 3;  <b><i>/* m is now error in owd est */</i></b>
<a name="L249" href="source/net/ipv4/tcp_lp.c#L249">249</a>                 <a href="ident?i=lp">lp</a>-&gt;sowd += mowd;       <b><i>/* owd = 7/8 owd + 1/8 new */</i></b>
<a name="L250" href="source/net/ipv4/tcp_lp.c#L250">250</a>         } else
<a name="L251" href="source/net/ipv4/tcp_lp.c#L251">251</a>                 <a href="ident?i=lp">lp</a>-&gt;sowd = mowd &lt;&lt; 3;   <b><i>/* take the measured time be owd */</i></b>
<a name="L252" href="source/net/ipv4/tcp_lp.c#L252">252</a> }
<a name="L253" href="source/net/ipv4/tcp_lp.c#L253">253</a> 
<a name="L254" href="source/net/ipv4/tcp_lp.c#L254">254</a> <b><i>/**</i></b>
<a name="L255" href="source/net/ipv4/tcp_lp.c#L255">255</a> <b><i> * tcp_lp_pkts_acked</i></b>
<a name="L256" href="source/net/ipv4/tcp_lp.c#L256">256</a> <b><i> *</i></b>
<a name="L257" href="source/net/ipv4/tcp_lp.c#L257">257</a> <b><i> * Implementation of pkts_acked.</i></b>
<a name="L258" href="source/net/ipv4/tcp_lp.c#L258">258</a> <b><i> * Deal with active drop under Early Congestion Indication.</i></b>
<a name="L259" href="source/net/ipv4/tcp_lp.c#L259">259</a> <b><i> * Only drop to half and 1 will be handle, because we hope to use back</i></b>
<a name="L260" href="source/net/ipv4/tcp_lp.c#L260">260</a> <b><i> * newReno in increase case.</i></b>
<a name="L261" href="source/net/ipv4/tcp_lp.c#L261">261</a> <b><i> * We work it out by following the idea from TCP-LP's paper directly</i></b>
<a name="L262" href="source/net/ipv4/tcp_lp.c#L262">262</a> <b><i> */</i></b>
<a name="L263" href="source/net/ipv4/tcp_lp.c#L263">263</a> static void <a href="ident?i=tcp_lp_pkts_acked">tcp_lp_pkts_acked</a>(struct <a href="ident?i=sock">sock</a> *sk, <a href="ident?i=u32">u32</a> num_acked, <a href="ident?i=s32">s32</a> rtt_us)
<a name="L264" href="source/net/ipv4/tcp_lp.c#L264">264</a> {
<a name="L265" href="source/net/ipv4/tcp_lp.c#L265">265</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L266" href="source/net/ipv4/tcp_lp.c#L266">266</a>         struct <a href="ident?i=lp">lp</a> *<a href="ident?i=lp">lp</a> = <a href="ident?i=inet_csk_ca">inet_csk_ca</a>(sk);
<a name="L267" href="source/net/ipv4/tcp_lp.c#L267">267</a> 
<a name="L268" href="source/net/ipv4/tcp_lp.c#L268">268</a>         if (rtt_us &gt; 0)
<a name="L269" href="source/net/ipv4/tcp_lp.c#L269">269</a>                 <a href="ident?i=tcp_lp_rtt_sample">tcp_lp_rtt_sample</a>(sk, rtt_us);
<a name="L270" href="source/net/ipv4/tcp_lp.c#L270">270</a> 
<a name="L271" href="source/net/ipv4/tcp_lp.c#L271">271</a>         <b><i>/* calc inference */</i></b>
<a name="L272" href="source/net/ipv4/tcp_lp.c#L272">272</a>         if (<a href="ident?i=tcp_time_stamp">tcp_time_stamp</a> &gt; <a href="ident?i=tp">tp</a>-&gt;rx_opt.rcv_tsecr)
<a name="L273" href="source/net/ipv4/tcp_lp.c#L273">273</a>                 <a href="ident?i=lp">lp</a>-&gt;inference = 3 * (<a href="ident?i=tcp_time_stamp">tcp_time_stamp</a> - <a href="ident?i=tp">tp</a>-&gt;rx_opt.rcv_tsecr);
<a name="L274" href="source/net/ipv4/tcp_lp.c#L274">274</a> 
<a name="L275" href="source/net/ipv4/tcp_lp.c#L275">275</a>         <b><i>/* test if within inference */</i></b>
<a name="L276" href="source/net/ipv4/tcp_lp.c#L276">276</a>         if (<a href="ident?i=lp">lp</a>-&gt;last_drop &amp;&amp; (<a href="ident?i=tcp_time_stamp">tcp_time_stamp</a> - <a href="ident?i=lp">lp</a>-&gt;last_drop &lt; <a href="ident?i=lp">lp</a>-&gt;inference))
<a name="L277" href="source/net/ipv4/tcp_lp.c#L277">277</a>                 <a href="ident?i=lp">lp</a>-&gt;<a href="ident?i=flag">flag</a> |= LP_WITHIN_INF;
<a name="L278" href="source/net/ipv4/tcp_lp.c#L278">278</a>         else
<a name="L279" href="source/net/ipv4/tcp_lp.c#L279">279</a>                 <a href="ident?i=lp">lp</a>-&gt;<a href="ident?i=flag">flag</a> &amp;= ~LP_WITHIN_INF;
<a name="L280" href="source/net/ipv4/tcp_lp.c#L280">280</a> 
<a name="L281" href="source/net/ipv4/tcp_lp.c#L281">281</a>         <b><i>/* test if within threshold */</i></b>
<a name="L282" href="source/net/ipv4/tcp_lp.c#L282">282</a>         if (<a href="ident?i=lp">lp</a>-&gt;sowd &gt;&gt; 3 &lt;
<a name="L283" href="source/net/ipv4/tcp_lp.c#L283">283</a>             <a href="ident?i=lp">lp</a>-&gt;owd_min + 15 * (<a href="ident?i=lp">lp</a>-&gt;owd_max - <a href="ident?i=lp">lp</a>-&gt;owd_min) / 100)
<a name="L284" href="source/net/ipv4/tcp_lp.c#L284">284</a>                 <a href="ident?i=lp">lp</a>-&gt;<a href="ident?i=flag">flag</a> |= LP_WITHIN_THR;
<a name="L285" href="source/net/ipv4/tcp_lp.c#L285">285</a>         else
<a name="L286" href="source/net/ipv4/tcp_lp.c#L286">286</a>                 <a href="ident?i=lp">lp</a>-&gt;<a href="ident?i=flag">flag</a> &amp;= ~LP_WITHIN_THR;
<a name="L287" href="source/net/ipv4/tcp_lp.c#L287">287</a> 
<a name="L288" href="source/net/ipv4/tcp_lp.c#L288">288</a>         <a href="ident?i=pr_debug">pr_debug</a>(<i>"TCP-LP: %05o|%5u|%5u|%15u|%15u|%15u\n"</i>, <a href="ident?i=lp">lp</a>-&gt;<a href="ident?i=flag">flag</a>,
<a name="L289" href="source/net/ipv4/tcp_lp.c#L289">289</a>                  <a href="ident?i=tp">tp</a>-&gt;snd_cwnd, <a href="ident?i=lp">lp</a>-&gt;remote_hz, <a href="ident?i=lp">lp</a>-&gt;owd_min, <a href="ident?i=lp">lp</a>-&gt;owd_max,
<a name="L290" href="source/net/ipv4/tcp_lp.c#L290">290</a>                  <a href="ident?i=lp">lp</a>-&gt;sowd &gt;&gt; 3);
<a name="L291" href="source/net/ipv4/tcp_lp.c#L291">291</a> 
<a name="L292" href="source/net/ipv4/tcp_lp.c#L292">292</a>         if (<a href="ident?i=lp">lp</a>-&gt;<a href="ident?i=flag">flag</a> &amp; LP_WITHIN_THR)
<a name="L293" href="source/net/ipv4/tcp_lp.c#L293">293</a>                 return;
<a name="L294" href="source/net/ipv4/tcp_lp.c#L294">294</a> 
<a name="L295" href="source/net/ipv4/tcp_lp.c#L295">295</a>         <b><i>/* FIXME: try to reset owd_min and owd_max here</i></b>
<a name="L296" href="source/net/ipv4/tcp_lp.c#L296">296</a> <b><i>         * so decrease the chance the min/max is no longer suitable</i></b>
<a name="L297" href="source/net/ipv4/tcp_lp.c#L297">297</a> <b><i>         * and will usually within threshold when whithin inference */</i></b>
<a name="L298" href="source/net/ipv4/tcp_lp.c#L298">298</a>         <a href="ident?i=lp">lp</a>-&gt;owd_min = <a href="ident?i=lp">lp</a>-&gt;sowd &gt;&gt; 3;
<a name="L299" href="source/net/ipv4/tcp_lp.c#L299">299</a>         <a href="ident?i=lp">lp</a>-&gt;owd_max = <a href="ident?i=lp">lp</a>-&gt;sowd &gt;&gt; 2;
<a name="L300" href="source/net/ipv4/tcp_lp.c#L300">300</a>         <a href="ident?i=lp">lp</a>-&gt;owd_max_rsv = <a href="ident?i=lp">lp</a>-&gt;sowd &gt;&gt; 2;
<a name="L301" href="source/net/ipv4/tcp_lp.c#L301">301</a> 
<a name="L302" href="source/net/ipv4/tcp_lp.c#L302">302</a>         <b><i>/* happened within inference</i></b>
<a name="L303" href="source/net/ipv4/tcp_lp.c#L303">303</a> <b><i>         * drop snd_cwnd into 1 */</i></b>
<a name="L304" href="source/net/ipv4/tcp_lp.c#L304">304</a>         if (<a href="ident?i=lp">lp</a>-&gt;<a href="ident?i=flag">flag</a> &amp; LP_WITHIN_INF)
<a name="L305" href="source/net/ipv4/tcp_lp.c#L305">305</a>                 <a href="ident?i=tp">tp</a>-&gt;snd_cwnd = 1U;
<a name="L306" href="source/net/ipv4/tcp_lp.c#L306">306</a> 
<a name="L307" href="source/net/ipv4/tcp_lp.c#L307">307</a>         <b><i>/* happened after inference</i></b>
<a name="L308" href="source/net/ipv4/tcp_lp.c#L308">308</a> <b><i>         * cut snd_cwnd into half */</i></b>
<a name="L309" href="source/net/ipv4/tcp_lp.c#L309">309</a>         else
<a name="L310" href="source/net/ipv4/tcp_lp.c#L310">310</a>                 <a href="ident?i=tp">tp</a>-&gt;snd_cwnd = <a href="ident?i=max">max</a>(<a href="ident?i=tp">tp</a>-&gt;snd_cwnd &gt;&gt; 1U, 1U);
<a name="L311" href="source/net/ipv4/tcp_lp.c#L311">311</a> 
<a name="L312" href="source/net/ipv4/tcp_lp.c#L312">312</a>         <b><i>/* record this drop time */</i></b>
<a name="L313" href="source/net/ipv4/tcp_lp.c#L313">313</a>         <a href="ident?i=lp">lp</a>-&gt;last_drop = <a href="ident?i=tcp_time_stamp">tcp_time_stamp</a>;
<a name="L314" href="source/net/ipv4/tcp_lp.c#L314">314</a> }
<a name="L315" href="source/net/ipv4/tcp_lp.c#L315">315</a> 
<a name="L316" href="source/net/ipv4/tcp_lp.c#L316">316</a> static struct <a href="ident?i=tcp_congestion_ops">tcp_congestion_ops</a> tcp_lp <a href="ident?i=__read_mostly">__read_mostly</a> = {
<a name="L317" href="source/net/ipv4/tcp_lp.c#L317">317</a>         .<a href="ident?i=init">init</a> = <a href="ident?i=tcp_lp_init">tcp_lp_init</a>,
<a name="L318" href="source/net/ipv4/tcp_lp.c#L318">318</a>         .ssthresh = <a href="ident?i=tcp_reno_ssthresh">tcp_reno_ssthresh</a>,
<a name="L319" href="source/net/ipv4/tcp_lp.c#L319">319</a>         .cong_avoid = <a href="ident?i=tcp_lp_cong_avoid">tcp_lp_cong_avoid</a>,
<a name="L320" href="source/net/ipv4/tcp_lp.c#L320">320</a>         .pkts_acked = <a href="ident?i=tcp_lp_pkts_acked">tcp_lp_pkts_acked</a>,
<a name="L321" href="source/net/ipv4/tcp_lp.c#L321">321</a> 
<a name="L322" href="source/net/ipv4/tcp_lp.c#L322">322</a>         .owner = <a href="ident?i=THIS_MODULE">THIS_MODULE</a>,
<a name="L323" href="source/net/ipv4/tcp_lp.c#L323">323</a>         .<a href="ident?i=name">name</a> = <i>"lp"</i>
<a name="L324" href="source/net/ipv4/tcp_lp.c#L324">324</a> };
<a name="L325" href="source/net/ipv4/tcp_lp.c#L325">325</a> 
<a name="L326" href="source/net/ipv4/tcp_lp.c#L326">326</a> static int <a href="ident?i=__init">__init</a> <a href="ident?i=tcp_lp_register">tcp_lp_register</a>(void)
<a name="L327" href="source/net/ipv4/tcp_lp.c#L327">327</a> {
<a name="L328" href="source/net/ipv4/tcp_lp.c#L328">328</a>         <a href="ident?i=BUILD_BUG_ON">BUILD_BUG_ON</a>(sizeof(struct <a href="ident?i=lp">lp</a>) &gt; <a href="ident?i=ICSK_CA_PRIV_SIZE">ICSK_CA_PRIV_SIZE</a>);
<a name="L329" href="source/net/ipv4/tcp_lp.c#L329">329</a>         return <a href="ident?i=tcp_register_congestion_control">tcp_register_congestion_control</a>(&amp;tcp_lp);
<a name="L330" href="source/net/ipv4/tcp_lp.c#L330">330</a> }
<a name="L331" href="source/net/ipv4/tcp_lp.c#L331">331</a> 
<a name="L332" href="source/net/ipv4/tcp_lp.c#L332">332</a> static void <a href="ident?i=__exit">__exit</a> <a href="ident?i=tcp_lp_unregister">tcp_lp_unregister</a>(void)
<a name="L333" href="source/net/ipv4/tcp_lp.c#L333">333</a> {
<a name="L334" href="source/net/ipv4/tcp_lp.c#L334">334</a>         <a href="ident?i=tcp_unregister_congestion_control">tcp_unregister_congestion_control</a>(&amp;tcp_lp);
<a name="L335" href="source/net/ipv4/tcp_lp.c#L335">335</a> }
<a name="L336" href="source/net/ipv4/tcp_lp.c#L336">336</a> 
<a name="L337" href="source/net/ipv4/tcp_lp.c#L337">337</a> <a href="ident?i=module_init">module_init</a>(<a href="ident?i=tcp_lp_register">tcp_lp_register</a>);
<a name="L338" href="source/net/ipv4/tcp_lp.c#L338">338</a> <a href="ident?i=module_exit">module_exit</a>(<a href="ident?i=tcp_lp_unregister">tcp_lp_unregister</a>);
<a name="L339" href="source/net/ipv4/tcp_lp.c#L339">339</a> 
<a name="L340" href="source/net/ipv4/tcp_lp.c#L340">340</a> <a href="ident?i=MODULE_AUTHOR">MODULE_AUTHOR</a>(<i>"Wong Hoi Sing Edison, Hung Hing Lun Mike"</i>);
<a name="L341" href="source/net/ipv4/tcp_lp.c#L341">341</a> <a href="ident?i=MODULE_LICENSE">MODULE_LICENSE</a>(<i>"GPL"</i>);
<a name="L342" href="source/net/ipv4/tcp_lp.c#L342">342</a> <a href="ident?i=MODULE_DESCRIPTION">MODULE_DESCRIPTION</a>(<i>"TCP Low Priority"</i>);
<a name="L343" href="source/net/ipv4/tcp_lp.c#L343">343</a> </pre></div><p>
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
