<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title>Linux/net/ipv4/tcp_veno.c - Linux Cross Reference - Free Electrons</title>
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
		 &nbsp;&bull;&nbsp;<b><i>source navigation</i></b> &nbsp;&bull;&nbsp;<a href="diff/net/ipv4/tcp_veno.c">diff markup</a> &nbsp;&bull;&nbsp;<a href="ident">identifier search</a> &nbsp;&bull;&nbsp;<a href="search">freetext search</a> &nbsp;&bull;&nbsp;
		</p>
	</div>
</div>

<div id="topbar">
  
  <p>Version: &nbsp;<a href="source/net/ipv4/tcp_veno.c?v=2.0.40">2.0.40</a>&nbsp;<a href="source/net/ipv4/tcp_veno.c?v=2.2.26">2.2.26</a>&nbsp;<a href="source/net/ipv4/tcp_veno.c?v=2.4.37">2.4.37</a>&nbsp;<a href="source/net/ipv4/tcp_veno.c?v=3.5">3.5</a>&nbsp;<a href="source/net/ipv4/tcp_veno.c?v=3.6">3.6</a>&nbsp;<a href="source/net/ipv4/tcp_veno.c?v=3.7">3.7</a>&nbsp;<a href="source/net/ipv4/tcp_veno.c?v=3.8">3.8</a>&nbsp;<a href="source/net/ipv4/tcp_veno.c?v=3.9">3.9</a>&nbsp;<a href="source/net/ipv4/tcp_veno.c?v=3.10">3.10</a>&nbsp;<a href="source/net/ipv4/tcp_veno.c?v=3.11">3.11</a>&nbsp;<a href="source/net/ipv4/tcp_veno.c?v=3.12">3.12</a>&nbsp;<a href="source/net/ipv4/tcp_veno.c?v=3.13">3.13</a>&nbsp;<a href="source/net/ipv4/tcp_veno.c?v=3.14">3.14</a>&nbsp;<a href="source/net/ipv4/tcp_veno.c?v=3.15">3.15</a>&nbsp;<a href="source/net/ipv4/tcp_veno.c?v=3.16">3.16</a>&nbsp;<a href="source/net/ipv4/tcp_veno.c?v=3.17">3.17</a>&nbsp;<a href="source/net/ipv4/tcp_veno.c?v=3.18">3.18</a>&nbsp;<a href="source/net/ipv4/tcp_veno.c?v=3.19">3.19</a>&nbsp;<a href="source/net/ipv4/tcp_veno.c?v=4.0">4.0</a>&nbsp;<b><i>4.1</i></b></p>
  
</div>

<h1><a href="source/">Linux</a>/<a href="source/net/">net</a>/<a href="source/net/ipv4/">ipv4</a>/<a href="source/net/ipv4/tcp_veno.c">tcp_veno.c</a></h1>
<div id="lxrcode"><pre>  <a name="L1" href="source/net/ipv4/tcp_veno.c#L1">1</a> <b><i>/*</i></b>
  <a name="L2" href="source/net/ipv4/tcp_veno.c#L2">2</a> <b><i> * TCP Veno congestion control</i></b>
  <a name="L3" href="source/net/ipv4/tcp_veno.c#L3">3</a> <b><i> *</i></b>
  <a name="L4" href="source/net/ipv4/tcp_veno.c#L4">4</a> <b><i> * This is based on the congestion detection/avoidance scheme described in</i></b>
  <a name="L5" href="source/net/ipv4/tcp_veno.c#L5">5</a> <b><i> *    C. P. Fu, S. C. Liew.</i></b>
  <a name="L6" href="source/net/ipv4/tcp_veno.c#L6">6</a> <b><i> *    "TCP Veno: TCP Enhancement for Transmission over Wireless Access Networks."</i></b>
  <a name="L7" href="source/net/ipv4/tcp_veno.c#L7">7</a> <b><i> *    IEEE Journal on Selected Areas in Communication,</i></b>
  <a name="L8" href="source/net/ipv4/tcp_veno.c#L8">8</a> <b><i> *    Feb. 2003.</i></b>
  <a name="L9" href="source/net/ipv4/tcp_veno.c#L9">9</a> <b><i> *      See <a href="http://www.ie.cuhk.edu.hk/fileadmin/staff_upload/soung/Journal/J3.pdf">http://www.ie.cuhk.edu.hk/fileadmin/staff_upload/soung/Journal/J3.pdf</a></i></b>
 <a name="L10" href="source/net/ipv4/tcp_veno.c#L10">10</a> <b><i> */</i></b>
 <a name="L11" href="source/net/ipv4/tcp_veno.c#L11">11</a> 
 <a name="L12" href="source/net/ipv4/tcp_veno.c#L12">12</a> #include &lt;linux/mm.h&gt;
 <a name="L13" href="source/net/ipv4/tcp_veno.c#L13">13</a> #include &lt;linux/module.h&gt;
 <a name="L14" href="source/net/ipv4/tcp_veno.c#L14">14</a> #include &lt;linux/skbuff.h&gt;
 <a name="L15" href="source/net/ipv4/tcp_veno.c#L15">15</a> #include &lt;linux/inet_diag.h&gt;
 <a name="L16" href="source/net/ipv4/tcp_veno.c#L16">16</a> 
 <a name="L17" href="source/net/ipv4/tcp_veno.c#L17">17</a> #include &lt;net/tcp.h&gt;
 <a name="L18" href="source/net/ipv4/tcp_veno.c#L18">18</a> 
 <a name="L19" href="source/net/ipv4/tcp_veno.c#L19">19</a> <b><i>/* Default values of the Veno variables, in fixed-point representation</i></b>
 <a name="L20" href="source/net/ipv4/tcp_veno.c#L20">20</a> <b><i> * with V_PARAM_SHIFT bits to the right of the binary point.</i></b>
 <a name="L21" href="source/net/ipv4/tcp_veno.c#L21">21</a> <b><i> */</i></b>
 <a name="L22" href="source/net/ipv4/tcp_veno.c#L22">22</a> #define <a href="ident?i=V_PARAM_SHIFT">V_PARAM_SHIFT</a> 1
 <a name="L23" href="source/net/ipv4/tcp_veno.c#L23">23</a> static const int <a href="ident?i=beta">beta</a> = 3 &lt;&lt; <a href="ident?i=V_PARAM_SHIFT">V_PARAM_SHIFT</a>;
 <a name="L24" href="source/net/ipv4/tcp_veno.c#L24">24</a> 
 <a name="L25" href="source/net/ipv4/tcp_veno.c#L25">25</a> <b><i>/* Veno variables */</i></b>
 <a name="L26" href="source/net/ipv4/tcp_veno.c#L26">26</a> struct <a href="ident?i=veno">veno</a> {
 <a name="L27" href="source/net/ipv4/tcp_veno.c#L27">27</a>         <a href="ident?i=u8">u8</a> doing_veno_now;      <b><i>/* if true, do veno for this rtt */</i></b>
 <a name="L28" href="source/net/ipv4/tcp_veno.c#L28">28</a>         <a href="ident?i=u16">u16</a> cntrtt;             <b><i>/* # of rtts measured within last rtt */</i></b>
 <a name="L29" href="source/net/ipv4/tcp_veno.c#L29">29</a>         <a href="ident?i=u32">u32</a> minrtt;             <b><i>/* min of rtts measured within last rtt (in usec) */</i></b>
 <a name="L30" href="source/net/ipv4/tcp_veno.c#L30">30</a>         <a href="ident?i=u32">u32</a> basertt;            <b><i>/* the min of all Veno rtt measurements seen (in usec) */</i></b>
 <a name="L31" href="source/net/ipv4/tcp_veno.c#L31">31</a>         <a href="ident?i=u32">u32</a> <a href="ident?i=inc">inc</a>;                <b><i>/* decide whether to increase cwnd */</i></b>
 <a name="L32" href="source/net/ipv4/tcp_veno.c#L32">32</a>         <a href="ident?i=u32">u32</a> diff;               <b><i>/* calculate the diff rate */</i></b>
 <a name="L33" href="source/net/ipv4/tcp_veno.c#L33">33</a> };
 <a name="L34" href="source/net/ipv4/tcp_veno.c#L34">34</a> 
 <a name="L35" href="source/net/ipv4/tcp_veno.c#L35">35</a> <b><i>/* There are several situations when we must "re-start" Veno:</i></b>
 <a name="L36" href="source/net/ipv4/tcp_veno.c#L36">36</a> <b><i> *</i></b>
 <a name="L37" href="source/net/ipv4/tcp_veno.c#L37">37</a> <b><i> *  o when a connection is established</i></b>
 <a name="L38" href="source/net/ipv4/tcp_veno.c#L38">38</a> <b><i> *  o after an RTO</i></b>
 <a name="L39" href="source/net/ipv4/tcp_veno.c#L39">39</a> <b><i> *  o after fast recovery</i></b>
 <a name="L40" href="source/net/ipv4/tcp_veno.c#L40">40</a> <b><i> *  o when we send a packet and there is no outstanding</i></b>
 <a name="L41" href="source/net/ipv4/tcp_veno.c#L41">41</a> <b><i> *    unacknowledged data (restarting an idle connection)</i></b>
 <a name="L42" href="source/net/ipv4/tcp_veno.c#L42">42</a> <b><i> *</i></b>
 <a name="L43" href="source/net/ipv4/tcp_veno.c#L43">43</a> <b><i> */</i></b>
 <a name="L44" href="source/net/ipv4/tcp_veno.c#L44">44</a> static inline void <a href="ident?i=veno_enable">veno_enable</a>(struct <a href="ident?i=sock">sock</a> *sk)
 <a name="L45" href="source/net/ipv4/tcp_veno.c#L45">45</a> {
 <a name="L46" href="source/net/ipv4/tcp_veno.c#L46">46</a>         struct <a href="ident?i=veno">veno</a> *<a href="ident?i=veno">veno</a> = <a href="ident?i=inet_csk_ca">inet_csk_ca</a>(sk);
 <a name="L47" href="source/net/ipv4/tcp_veno.c#L47">47</a> 
 <a name="L48" href="source/net/ipv4/tcp_veno.c#L48">48</a>         <b><i>/* turn on Veno */</i></b>
 <a name="L49" href="source/net/ipv4/tcp_veno.c#L49">49</a>         <a href="ident?i=veno">veno</a>-&gt;doing_veno_now = 1;
 <a name="L50" href="source/net/ipv4/tcp_veno.c#L50">50</a> 
 <a name="L51" href="source/net/ipv4/tcp_veno.c#L51">51</a>         <a href="ident?i=veno">veno</a>-&gt;minrtt = 0x7fffffff;
 <a name="L52" href="source/net/ipv4/tcp_veno.c#L52">52</a> }
 <a name="L53" href="source/net/ipv4/tcp_veno.c#L53">53</a> 
 <a name="L54" href="source/net/ipv4/tcp_veno.c#L54">54</a> static inline void <a href="ident?i=veno_disable">veno_disable</a>(struct <a href="ident?i=sock">sock</a> *sk)
 <a name="L55" href="source/net/ipv4/tcp_veno.c#L55">55</a> {
 <a name="L56" href="source/net/ipv4/tcp_veno.c#L56">56</a>         struct <a href="ident?i=veno">veno</a> *<a href="ident?i=veno">veno</a> = <a href="ident?i=inet_csk_ca">inet_csk_ca</a>(sk);
 <a name="L57" href="source/net/ipv4/tcp_veno.c#L57">57</a> 
 <a name="L58" href="source/net/ipv4/tcp_veno.c#L58">58</a>         <b><i>/* turn off Veno */</i></b>
 <a name="L59" href="source/net/ipv4/tcp_veno.c#L59">59</a>         <a href="ident?i=veno">veno</a>-&gt;doing_veno_now = 0;
 <a name="L60" href="source/net/ipv4/tcp_veno.c#L60">60</a> }
 <a name="L61" href="source/net/ipv4/tcp_veno.c#L61">61</a> 
 <a name="L62" href="source/net/ipv4/tcp_veno.c#L62">62</a> static void <a href="ident?i=tcp_veno_init">tcp_veno_init</a>(struct <a href="ident?i=sock">sock</a> *sk)
 <a name="L63" href="source/net/ipv4/tcp_veno.c#L63">63</a> {
 <a name="L64" href="source/net/ipv4/tcp_veno.c#L64">64</a>         struct <a href="ident?i=veno">veno</a> *<a href="ident?i=veno">veno</a> = <a href="ident?i=inet_csk_ca">inet_csk_ca</a>(sk);
 <a name="L65" href="source/net/ipv4/tcp_veno.c#L65">65</a> 
 <a name="L66" href="source/net/ipv4/tcp_veno.c#L66">66</a>         <a href="ident?i=veno">veno</a>-&gt;basertt = 0x7fffffff;
 <a name="L67" href="source/net/ipv4/tcp_veno.c#L67">67</a>         <a href="ident?i=veno">veno</a>-&gt;<a href="ident?i=inc">inc</a> = 1;
 <a name="L68" href="source/net/ipv4/tcp_veno.c#L68">68</a>         <a href="ident?i=veno_enable">veno_enable</a>(sk);
 <a name="L69" href="source/net/ipv4/tcp_veno.c#L69">69</a> }
 <a name="L70" href="source/net/ipv4/tcp_veno.c#L70">70</a> 
 <a name="L71" href="source/net/ipv4/tcp_veno.c#L71">71</a> <b><i>/* Do rtt sampling needed for Veno. */</i></b>
 <a name="L72" href="source/net/ipv4/tcp_veno.c#L72">72</a> static void <a href="ident?i=tcp_veno_pkts_acked">tcp_veno_pkts_acked</a>(struct <a href="ident?i=sock">sock</a> *sk, <a href="ident?i=u32">u32</a> cnt, <a href="ident?i=s32">s32</a> rtt_us)
 <a name="L73" href="source/net/ipv4/tcp_veno.c#L73">73</a> {
 <a name="L74" href="source/net/ipv4/tcp_veno.c#L74">74</a>         struct <a href="ident?i=veno">veno</a> *<a href="ident?i=veno">veno</a> = <a href="ident?i=inet_csk_ca">inet_csk_ca</a>(sk);
 <a name="L75" href="source/net/ipv4/tcp_veno.c#L75">75</a>         <a href="ident?i=u32">u32</a> vrtt;
 <a name="L76" href="source/net/ipv4/tcp_veno.c#L76">76</a> 
 <a name="L77" href="source/net/ipv4/tcp_veno.c#L77">77</a>         if (rtt_us &lt; 0)
 <a name="L78" href="source/net/ipv4/tcp_veno.c#L78">78</a>                 return;
 <a name="L79" href="source/net/ipv4/tcp_veno.c#L79">79</a> 
 <a name="L80" href="source/net/ipv4/tcp_veno.c#L80">80</a>         <b><i>/* Never allow zero rtt or baseRTT */</i></b>
 <a name="L81" href="source/net/ipv4/tcp_veno.c#L81">81</a>         vrtt = rtt_us + 1;
 <a name="L82" href="source/net/ipv4/tcp_veno.c#L82">82</a> 
 <a name="L83" href="source/net/ipv4/tcp_veno.c#L83">83</a>         <b><i>/* Filter to find propagation delay: */</i></b>
 <a name="L84" href="source/net/ipv4/tcp_veno.c#L84">84</a>         if (vrtt &lt; <a href="ident?i=veno">veno</a>-&gt;basertt)
 <a name="L85" href="source/net/ipv4/tcp_veno.c#L85">85</a>                 <a href="ident?i=veno">veno</a>-&gt;basertt = vrtt;
 <a name="L86" href="source/net/ipv4/tcp_veno.c#L86">86</a> 
 <a name="L87" href="source/net/ipv4/tcp_veno.c#L87">87</a>         <b><i>/* Find the min rtt during the last rtt to find</i></b>
 <a name="L88" href="source/net/ipv4/tcp_veno.c#L88">88</a> <b><i>         * the current prop. delay + queuing delay:</i></b>
 <a name="L89" href="source/net/ipv4/tcp_veno.c#L89">89</a> <b><i>         */</i></b>
 <a name="L90" href="source/net/ipv4/tcp_veno.c#L90">90</a>         <a href="ident?i=veno">veno</a>-&gt;minrtt = <a href="ident?i=min">min</a>(<a href="ident?i=veno">veno</a>-&gt;minrtt, vrtt);
 <a name="L91" href="source/net/ipv4/tcp_veno.c#L91">91</a>         <a href="ident?i=veno">veno</a>-&gt;cntrtt++;
 <a name="L92" href="source/net/ipv4/tcp_veno.c#L92">92</a> }
 <a name="L93" href="source/net/ipv4/tcp_veno.c#L93">93</a> 
 <a name="L94" href="source/net/ipv4/tcp_veno.c#L94">94</a> static void <a href="ident?i=tcp_veno_state">tcp_veno_state</a>(struct <a href="ident?i=sock">sock</a> *sk, <a href="ident?i=u8">u8</a> ca_state)
 <a name="L95" href="source/net/ipv4/tcp_veno.c#L95">95</a> {
 <a name="L96" href="source/net/ipv4/tcp_veno.c#L96">96</a>         if (ca_state == TCP_CA_Open)
 <a name="L97" href="source/net/ipv4/tcp_veno.c#L97">97</a>                 <a href="ident?i=veno_enable">veno_enable</a>(sk);
 <a name="L98" href="source/net/ipv4/tcp_veno.c#L98">98</a>         else
 <a name="L99" href="source/net/ipv4/tcp_veno.c#L99">99</a>                 <a href="ident?i=veno_disable">veno_disable</a>(sk);
<a name="L100" href="source/net/ipv4/tcp_veno.c#L100">100</a> }
<a name="L101" href="source/net/ipv4/tcp_veno.c#L101">101</a> 
<a name="L102" href="source/net/ipv4/tcp_veno.c#L102">102</a> <b><i>/*</i></b>
<a name="L103" href="source/net/ipv4/tcp_veno.c#L103">103</a> <b><i> * If the connection is idle and we are restarting,</i></b>
<a name="L104" href="source/net/ipv4/tcp_veno.c#L104">104</a> <b><i> * then we don't want to do any Veno calculations</i></b>
<a name="L105" href="source/net/ipv4/tcp_veno.c#L105">105</a> <b><i> * until we get fresh rtt samples.  So when we</i></b>
<a name="L106" href="source/net/ipv4/tcp_veno.c#L106">106</a> <b><i> * restart, we reset our Veno state to a clean</i></b>
<a name="L107" href="source/net/ipv4/tcp_veno.c#L107">107</a> <b><i> * state. After we get acks for this flight of</i></b>
<a name="L108" href="source/net/ipv4/tcp_veno.c#L108">108</a> <b><i> * packets, _then_ we can make Veno calculations</i></b>
<a name="L109" href="source/net/ipv4/tcp_veno.c#L109">109</a> <b><i> * again.</i></b>
<a name="L110" href="source/net/ipv4/tcp_veno.c#L110">110</a> <b><i> */</i></b>
<a name="L111" href="source/net/ipv4/tcp_veno.c#L111">111</a> static void <a href="ident?i=tcp_veno_cwnd_event">tcp_veno_cwnd_event</a>(struct <a href="ident?i=sock">sock</a> *sk, enum <a href="ident?i=tcp_ca_event">tcp_ca_event</a> <a href="ident?i=event">event</a>)
<a name="L112" href="source/net/ipv4/tcp_veno.c#L112">112</a> {
<a name="L113" href="source/net/ipv4/tcp_veno.c#L113">113</a>         if (<a href="ident?i=event">event</a> == CA_EVENT_CWND_RESTART || <a href="ident?i=event">event</a> == CA_EVENT_TX_START)
<a name="L114" href="source/net/ipv4/tcp_veno.c#L114">114</a>                 <a href="ident?i=tcp_veno_init">tcp_veno_init</a>(sk);
<a name="L115" href="source/net/ipv4/tcp_veno.c#L115">115</a> }
<a name="L116" href="source/net/ipv4/tcp_veno.c#L116">116</a> 
<a name="L117" href="source/net/ipv4/tcp_veno.c#L117">117</a> static void <a href="ident?i=tcp_veno_cong_avoid">tcp_veno_cong_avoid</a>(struct <a href="ident?i=sock">sock</a> *sk, <a href="ident?i=u32">u32</a> ack, <a href="ident?i=u32">u32</a> acked)
<a name="L118" href="source/net/ipv4/tcp_veno.c#L118">118</a> {
<a name="L119" href="source/net/ipv4/tcp_veno.c#L119">119</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L120" href="source/net/ipv4/tcp_veno.c#L120">120</a>         struct <a href="ident?i=veno">veno</a> *<a href="ident?i=veno">veno</a> = <a href="ident?i=inet_csk_ca">inet_csk_ca</a>(sk);
<a name="L121" href="source/net/ipv4/tcp_veno.c#L121">121</a> 
<a name="L122" href="source/net/ipv4/tcp_veno.c#L122">122</a>         if (!<a href="ident?i=veno">veno</a>-&gt;doing_veno_now) {
<a name="L123" href="source/net/ipv4/tcp_veno.c#L123">123</a>                 <a href="ident?i=tcp_reno_cong_avoid">tcp_reno_cong_avoid</a>(sk, ack, acked);
<a name="L124" href="source/net/ipv4/tcp_veno.c#L124">124</a>                 return;
<a name="L125" href="source/net/ipv4/tcp_veno.c#L125">125</a>         }
<a name="L126" href="source/net/ipv4/tcp_veno.c#L126">126</a> 
<a name="L127" href="source/net/ipv4/tcp_veno.c#L127">127</a>         <b><i>/* limited by applications */</i></b>
<a name="L128" href="source/net/ipv4/tcp_veno.c#L128">128</a>         if (!<a href="ident?i=tcp_is_cwnd_limited">tcp_is_cwnd_limited</a>(sk))
<a name="L129" href="source/net/ipv4/tcp_veno.c#L129">129</a>                 return;
<a name="L130" href="source/net/ipv4/tcp_veno.c#L130">130</a> 
<a name="L131" href="source/net/ipv4/tcp_veno.c#L131">131</a>         <b><i>/* We do the Veno calculations only if we got enough rtt samples */</i></b>
<a name="L132" href="source/net/ipv4/tcp_veno.c#L132">132</a>         if (<a href="ident?i=veno">veno</a>-&gt;cntrtt &lt;= 2) {
<a name="L133" href="source/net/ipv4/tcp_veno.c#L133">133</a>                 <b><i>/* We don't have enough rtt samples to do the Veno</i></b>
<a name="L134" href="source/net/ipv4/tcp_veno.c#L134">134</a> <b><i>                 * calculation, so we'll behave like Reno.</i></b>
<a name="L135" href="source/net/ipv4/tcp_veno.c#L135">135</a> <b><i>                 */</i></b>
<a name="L136" href="source/net/ipv4/tcp_veno.c#L136">136</a>                 <a href="ident?i=tcp_reno_cong_avoid">tcp_reno_cong_avoid</a>(sk, ack, acked);
<a name="L137" href="source/net/ipv4/tcp_veno.c#L137">137</a>         } else {
<a name="L138" href="source/net/ipv4/tcp_veno.c#L138">138</a>                 <a href="ident?i=u64">u64</a> target_cwnd;
<a name="L139" href="source/net/ipv4/tcp_veno.c#L139">139</a>                 <a href="ident?i=u32">u32</a> rtt;
<a name="L140" href="source/net/ipv4/tcp_veno.c#L140">140</a> 
<a name="L141" href="source/net/ipv4/tcp_veno.c#L141">141</a>                 <b><i>/* We have enough rtt samples, so, using the Veno</i></b>
<a name="L142" href="source/net/ipv4/tcp_veno.c#L142">142</a> <b><i>                 * algorithm, we determine the state of the network.</i></b>
<a name="L143" href="source/net/ipv4/tcp_veno.c#L143">143</a> <b><i>                 */</i></b>
<a name="L144" href="source/net/ipv4/tcp_veno.c#L144">144</a> 
<a name="L145" href="source/net/ipv4/tcp_veno.c#L145">145</a>                 rtt = <a href="ident?i=veno">veno</a>-&gt;minrtt;
<a name="L146" href="source/net/ipv4/tcp_veno.c#L146">146</a> 
<a name="L147" href="source/net/ipv4/tcp_veno.c#L147">147</a>                 target_cwnd = (<a href="ident?i=u64">u64</a>)<a href="ident?i=tp">tp</a>-&gt;snd_cwnd * <a href="ident?i=veno">veno</a>-&gt;basertt;
<a name="L148" href="source/net/ipv4/tcp_veno.c#L148">148</a>                 target_cwnd &lt;&lt;= <a href="ident?i=V_PARAM_SHIFT">V_PARAM_SHIFT</a>;
<a name="L149" href="source/net/ipv4/tcp_veno.c#L149">149</a>                 <a href="ident?i=do_div">do_div</a>(target_cwnd, rtt);
<a name="L150" href="source/net/ipv4/tcp_veno.c#L150">150</a> 
<a name="L151" href="source/net/ipv4/tcp_veno.c#L151">151</a>                 <a href="ident?i=veno">veno</a>-&gt;diff = (<a href="ident?i=tp">tp</a>-&gt;snd_cwnd &lt;&lt; <a href="ident?i=V_PARAM_SHIFT">V_PARAM_SHIFT</a>) - target_cwnd;
<a name="L152" href="source/net/ipv4/tcp_veno.c#L152">152</a> 
<a name="L153" href="source/net/ipv4/tcp_veno.c#L153">153</a>                 if (<a href="ident?i=tp">tp</a>-&gt;snd_cwnd &lt;= <a href="ident?i=tp">tp</a>-&gt;snd_ssthresh) {
<a name="L154" href="source/net/ipv4/tcp_veno.c#L154">154</a>                         <b><i>/* Slow start.  */</i></b>
<a name="L155" href="source/net/ipv4/tcp_veno.c#L155">155</a>                         <a href="ident?i=tcp_slow_start">tcp_slow_start</a>(<a href="ident?i=tp">tp</a>, acked);
<a name="L156" href="source/net/ipv4/tcp_veno.c#L156">156</a>                 } else {
<a name="L157" href="source/net/ipv4/tcp_veno.c#L157">157</a>                         <b><i>/* Congestion avoidance. */</i></b>
<a name="L158" href="source/net/ipv4/tcp_veno.c#L158">158</a>                         if (<a href="ident?i=veno">veno</a>-&gt;diff &lt; <a href="ident?i=beta">beta</a>) {
<a name="L159" href="source/net/ipv4/tcp_veno.c#L159">159</a>                                 <b><i>/* In the "non-congestive state", increase cwnd</i></b>
<a name="L160" href="source/net/ipv4/tcp_veno.c#L160">160</a> <b><i>                                 *  every rtt.</i></b>
<a name="L161" href="source/net/ipv4/tcp_veno.c#L161">161</a> <b><i>                                 */</i></b>
<a name="L162" href="source/net/ipv4/tcp_veno.c#L162">162</a>                                 <a href="ident?i=tcp_cong_avoid_ai">tcp_cong_avoid_ai</a>(<a href="ident?i=tp">tp</a>, <a href="ident?i=tp">tp</a>-&gt;snd_cwnd, 1);
<a name="L163" href="source/net/ipv4/tcp_veno.c#L163">163</a>                         } else {
<a name="L164" href="source/net/ipv4/tcp_veno.c#L164">164</a>                                 <b><i>/* In the "congestive state", increase cwnd</i></b>
<a name="L165" href="source/net/ipv4/tcp_veno.c#L165">165</a> <b><i>                                 * every other rtt.</i></b>
<a name="L166" href="source/net/ipv4/tcp_veno.c#L166">166</a> <b><i>                                 */</i></b>
<a name="L167" href="source/net/ipv4/tcp_veno.c#L167">167</a>                                 if (<a href="ident?i=tp">tp</a>-&gt;snd_cwnd_cnt &gt;= <a href="ident?i=tp">tp</a>-&gt;snd_cwnd) {
<a name="L168" href="source/net/ipv4/tcp_veno.c#L168">168</a>                                         if (<a href="ident?i=veno">veno</a>-&gt;<a href="ident?i=inc">inc</a> &amp;&amp;
<a name="L169" href="source/net/ipv4/tcp_veno.c#L169">169</a>                                             <a href="ident?i=tp">tp</a>-&gt;snd_cwnd &lt; <a href="ident?i=tp">tp</a>-&gt;snd_cwnd_clamp) {
<a name="L170" href="source/net/ipv4/tcp_veno.c#L170">170</a>                                                 <a href="ident?i=tp">tp</a>-&gt;snd_cwnd++;
<a name="L171" href="source/net/ipv4/tcp_veno.c#L171">171</a>                                                 <a href="ident?i=veno">veno</a>-&gt;<a href="ident?i=inc">inc</a> = 0;
<a name="L172" href="source/net/ipv4/tcp_veno.c#L172">172</a>                                         } else
<a name="L173" href="source/net/ipv4/tcp_veno.c#L173">173</a>                                                 <a href="ident?i=veno">veno</a>-&gt;<a href="ident?i=inc">inc</a> = 1;
<a name="L174" href="source/net/ipv4/tcp_veno.c#L174">174</a>                                         <a href="ident?i=tp">tp</a>-&gt;snd_cwnd_cnt = 0;
<a name="L175" href="source/net/ipv4/tcp_veno.c#L175">175</a>                                 } else
<a name="L176" href="source/net/ipv4/tcp_veno.c#L176">176</a>                                         <a href="ident?i=tp">tp</a>-&gt;snd_cwnd_cnt++;
<a name="L177" href="source/net/ipv4/tcp_veno.c#L177">177</a>                         }
<a name="L178" href="source/net/ipv4/tcp_veno.c#L178">178</a>                 }
<a name="L179" href="source/net/ipv4/tcp_veno.c#L179">179</a>                 if (<a href="ident?i=tp">tp</a>-&gt;snd_cwnd &lt; 2)
<a name="L180" href="source/net/ipv4/tcp_veno.c#L180">180</a>                         <a href="ident?i=tp">tp</a>-&gt;snd_cwnd = 2;
<a name="L181" href="source/net/ipv4/tcp_veno.c#L181">181</a>                 else if (<a href="ident?i=tp">tp</a>-&gt;snd_cwnd &gt; <a href="ident?i=tp">tp</a>-&gt;snd_cwnd_clamp)
<a name="L182" href="source/net/ipv4/tcp_veno.c#L182">182</a>                         <a href="ident?i=tp">tp</a>-&gt;snd_cwnd = <a href="ident?i=tp">tp</a>-&gt;snd_cwnd_clamp;
<a name="L183" href="source/net/ipv4/tcp_veno.c#L183">183</a>         }
<a name="L184" href="source/net/ipv4/tcp_veno.c#L184">184</a>         <b><i>/* Wipe the slate clean for the next rtt. */</i></b>
<a name="L185" href="source/net/ipv4/tcp_veno.c#L185">185</a>         <b><i>/* veno-&gt;cntrtt = 0; */</i></b>
<a name="L186" href="source/net/ipv4/tcp_veno.c#L186">186</a>         <a href="ident?i=veno">veno</a>-&gt;minrtt = 0x7fffffff;
<a name="L187" href="source/net/ipv4/tcp_veno.c#L187">187</a> }
<a name="L188" href="source/net/ipv4/tcp_veno.c#L188">188</a> 
<a name="L189" href="source/net/ipv4/tcp_veno.c#L189">189</a> <b><i>/* Veno MD phase */</i></b>
<a name="L190" href="source/net/ipv4/tcp_veno.c#L190">190</a> static <a href="ident?i=u32">u32</a> <a href="ident?i=tcp_veno_ssthresh">tcp_veno_ssthresh</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L191" href="source/net/ipv4/tcp_veno.c#L191">191</a> {
<a name="L192" href="source/net/ipv4/tcp_veno.c#L192">192</a>         const struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L193" href="source/net/ipv4/tcp_veno.c#L193">193</a>         struct <a href="ident?i=veno">veno</a> *<a href="ident?i=veno">veno</a> = <a href="ident?i=inet_csk_ca">inet_csk_ca</a>(sk);
<a name="L194" href="source/net/ipv4/tcp_veno.c#L194">194</a> 
<a name="L195" href="source/net/ipv4/tcp_veno.c#L195">195</a>         if (<a href="ident?i=veno">veno</a>-&gt;diff &lt; <a href="ident?i=beta">beta</a>)
<a name="L196" href="source/net/ipv4/tcp_veno.c#L196">196</a>                 <b><i>/* in "non-congestive state", cut cwnd by 1/5 */</i></b>
<a name="L197" href="source/net/ipv4/tcp_veno.c#L197">197</a>                 return <a href="ident?i=max">max</a>(<a href="ident?i=tp">tp</a>-&gt;snd_cwnd * 4 / 5, 2U);
<a name="L198" href="source/net/ipv4/tcp_veno.c#L198">198</a>         else
<a name="L199" href="source/net/ipv4/tcp_veno.c#L199">199</a>                 <b><i>/* in "congestive state", cut cwnd by 1/2 */</i></b>
<a name="L200" href="source/net/ipv4/tcp_veno.c#L200">200</a>                 return <a href="ident?i=max">max</a>(<a href="ident?i=tp">tp</a>-&gt;snd_cwnd &gt;&gt; 1U, 2U);
<a name="L201" href="source/net/ipv4/tcp_veno.c#L201">201</a> }
<a name="L202" href="source/net/ipv4/tcp_veno.c#L202">202</a> 
<a name="L203" href="source/net/ipv4/tcp_veno.c#L203">203</a> static struct <a href="ident?i=tcp_congestion_ops">tcp_congestion_ops</a> tcp_veno <a href="ident?i=__read_mostly">__read_mostly</a> = {
<a name="L204" href="source/net/ipv4/tcp_veno.c#L204">204</a>         .<a href="ident?i=init">init</a>           = <a href="ident?i=tcp_veno_init">tcp_veno_init</a>,
<a name="L205" href="source/net/ipv4/tcp_veno.c#L205">205</a>         .ssthresh       = <a href="ident?i=tcp_veno_ssthresh">tcp_veno_ssthresh</a>,
<a name="L206" href="source/net/ipv4/tcp_veno.c#L206">206</a>         .cong_avoid     = <a href="ident?i=tcp_veno_cong_avoid">tcp_veno_cong_avoid</a>,
<a name="L207" href="source/net/ipv4/tcp_veno.c#L207">207</a>         .pkts_acked     = <a href="ident?i=tcp_veno_pkts_acked">tcp_veno_pkts_acked</a>,
<a name="L208" href="source/net/ipv4/tcp_veno.c#L208">208</a>         .<a href="ident?i=set_state">set_state</a>      = <a href="ident?i=tcp_veno_state">tcp_veno_state</a>,
<a name="L209" href="source/net/ipv4/tcp_veno.c#L209">209</a>         .cwnd_event     = <a href="ident?i=tcp_veno_cwnd_event">tcp_veno_cwnd_event</a>,
<a name="L210" href="source/net/ipv4/tcp_veno.c#L210">210</a> 
<a name="L211" href="source/net/ipv4/tcp_veno.c#L211">211</a>         .owner          = <a href="ident?i=THIS_MODULE">THIS_MODULE</a>,
<a name="L212" href="source/net/ipv4/tcp_veno.c#L212">212</a>         .<a href="ident?i=name">name</a>           = <i>"veno"</i>,
<a name="L213" href="source/net/ipv4/tcp_veno.c#L213">213</a> };
<a name="L214" href="source/net/ipv4/tcp_veno.c#L214">214</a> 
<a name="L215" href="source/net/ipv4/tcp_veno.c#L215">215</a> static int <a href="ident?i=__init">__init</a> <a href="ident?i=tcp_veno_register">tcp_veno_register</a>(void)
<a name="L216" href="source/net/ipv4/tcp_veno.c#L216">216</a> {
<a name="L217" href="source/net/ipv4/tcp_veno.c#L217">217</a>         <a href="ident?i=BUILD_BUG_ON">BUILD_BUG_ON</a>(sizeof(struct <a href="ident?i=veno">veno</a>) &gt; <a href="ident?i=ICSK_CA_PRIV_SIZE">ICSK_CA_PRIV_SIZE</a>);
<a name="L218" href="source/net/ipv4/tcp_veno.c#L218">218</a>         <a href="ident?i=tcp_register_congestion_control">tcp_register_congestion_control</a>(&amp;tcp_veno);
<a name="L219" href="source/net/ipv4/tcp_veno.c#L219">219</a>         return 0;
<a name="L220" href="source/net/ipv4/tcp_veno.c#L220">220</a> }
<a name="L221" href="source/net/ipv4/tcp_veno.c#L221">221</a> 
<a name="L222" href="source/net/ipv4/tcp_veno.c#L222">222</a> static void <a href="ident?i=__exit">__exit</a> <a href="ident?i=tcp_veno_unregister">tcp_veno_unregister</a>(void)
<a name="L223" href="source/net/ipv4/tcp_veno.c#L223">223</a> {
<a name="L224" href="source/net/ipv4/tcp_veno.c#L224">224</a>         <a href="ident?i=tcp_unregister_congestion_control">tcp_unregister_congestion_control</a>(&amp;tcp_veno);
<a name="L225" href="source/net/ipv4/tcp_veno.c#L225">225</a> }
<a name="L226" href="source/net/ipv4/tcp_veno.c#L226">226</a> 
<a name="L227" href="source/net/ipv4/tcp_veno.c#L227">227</a> <a href="ident?i=module_init">module_init</a>(<a href="ident?i=tcp_veno_register">tcp_veno_register</a>);
<a name="L228" href="source/net/ipv4/tcp_veno.c#L228">228</a> <a href="ident?i=module_exit">module_exit</a>(<a href="ident?i=tcp_veno_unregister">tcp_veno_unregister</a>);
<a name="L229" href="source/net/ipv4/tcp_veno.c#L229">229</a> 
<a name="L230" href="source/net/ipv4/tcp_veno.c#L230">230</a> <a href="ident?i=MODULE_AUTHOR">MODULE_AUTHOR</a>(<i>"Bin Zhou, Cheng Peng Fu"</i>);
<a name="L231" href="source/net/ipv4/tcp_veno.c#L231">231</a> <a href="ident?i=MODULE_LICENSE">MODULE_LICENSE</a>(<i>"GPL"</i>);
<a name="L232" href="source/net/ipv4/tcp_veno.c#L232">232</a> <a href="ident?i=MODULE_DESCRIPTION">MODULE_DESCRIPTION</a>(<i>"TCP Veno"</i>);
<a name="L233" href="source/net/ipv4/tcp_veno.c#L233">233</a> </pre></div><p>
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
