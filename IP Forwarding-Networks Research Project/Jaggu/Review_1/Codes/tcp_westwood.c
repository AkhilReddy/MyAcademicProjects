<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title>Linux/net/ipv4/tcp_westwood.c - Linux Cross Reference - Free Electrons</title>
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
		 &nbsp;&bull;&nbsp;<b><i>source navigation</i></b> &nbsp;&bull;&nbsp;<a href="diff/net/ipv4/tcp_westwood.c">diff markup</a> &nbsp;&bull;&nbsp;<a href="ident">identifier search</a> &nbsp;&bull;&nbsp;<a href="search">freetext search</a> &nbsp;&bull;&nbsp;
		</p>
	</div>
</div>

<div id="topbar">
  
  <p>Version: &nbsp;<a href="source/net/ipv4/tcp_westwood.c?v=2.0.40">2.0.40</a>&nbsp;<a href="source/net/ipv4/tcp_westwood.c?v=2.2.26">2.2.26</a>&nbsp;<a href="source/net/ipv4/tcp_westwood.c?v=2.4.37">2.4.37</a>&nbsp;<a href="source/net/ipv4/tcp_westwood.c?v=3.5">3.5</a>&nbsp;<a href="source/net/ipv4/tcp_westwood.c?v=3.6">3.6</a>&nbsp;<a href="source/net/ipv4/tcp_westwood.c?v=3.7">3.7</a>&nbsp;<a href="source/net/ipv4/tcp_westwood.c?v=3.8">3.8</a>&nbsp;<a href="source/net/ipv4/tcp_westwood.c?v=3.9">3.9</a>&nbsp;<a href="source/net/ipv4/tcp_westwood.c?v=3.10">3.10</a>&nbsp;<a href="source/net/ipv4/tcp_westwood.c?v=3.11">3.11</a>&nbsp;<a href="source/net/ipv4/tcp_westwood.c?v=3.12">3.12</a>&nbsp;<a href="source/net/ipv4/tcp_westwood.c?v=3.13">3.13</a>&nbsp;<a href="source/net/ipv4/tcp_westwood.c?v=3.14">3.14</a>&nbsp;<a href="source/net/ipv4/tcp_westwood.c?v=3.15">3.15</a>&nbsp;<a href="source/net/ipv4/tcp_westwood.c?v=3.16">3.16</a>&nbsp;<a href="source/net/ipv4/tcp_westwood.c?v=3.17">3.17</a>&nbsp;<a href="source/net/ipv4/tcp_westwood.c?v=3.18">3.18</a>&nbsp;<a href="source/net/ipv4/tcp_westwood.c?v=3.19">3.19</a>&nbsp;<a href="source/net/ipv4/tcp_westwood.c?v=4.0">4.0</a>&nbsp;<b><i>4.1</i></b></p>
  
</div>

<h1><a href="source/">Linux</a>/<a href="source/net/">net</a>/<a href="source/net/ipv4/">ipv4</a>/<a href="source/net/ipv4/tcp_westwood.c">tcp_westwood.c</a></h1>
<div id="lxrcode"><pre>  <a name="L1" href="source/net/ipv4/tcp_westwood.c#L1">1</a> <b><i>/*</i></b>
  <a name="L2" href="source/net/ipv4/tcp_westwood.c#L2">2</a> <b><i> * TCP Westwood+: end-to-end bandwidth estimation for TCP</i></b>
  <a name="L3" href="source/net/ipv4/tcp_westwood.c#L3">3</a> <b><i> *</i></b>
  <a name="L4" href="source/net/ipv4/tcp_westwood.c#L4">4</a> <b><i> *      Angelo Dell'Aera: author of the first version of TCP Westwood+ in Linux 2.4</i></b>
  <a name="L5" href="source/net/ipv4/tcp_westwood.c#L5">5</a> <b><i> *</i></b>
  <a name="L6" href="source/net/ipv4/tcp_westwood.c#L6">6</a> <b><i> * Support at <a href="http://c3lab.poliba.it/index.php/Westwood">http://c3lab.poliba.it/index.php/Westwood</a></i></b>
  <a name="L7" href="source/net/ipv4/tcp_westwood.c#L7">7</a> <b><i> * Main references in literature:</i></b>
  <a name="L8" href="source/net/ipv4/tcp_westwood.c#L8">8</a> <b><i> *</i></b>
  <a name="L9" href="source/net/ipv4/tcp_westwood.c#L9">9</a> <b><i> * - Mascolo S, Casetti, M. Gerla et al.</i></b>
 <a name="L10" href="source/net/ipv4/tcp_westwood.c#L10">10</a> <b><i> *   "TCP Westwood: bandwidth estimation for TCP" Proc. ACM Mobicom 2001</i></b>
 <a name="L11" href="source/net/ipv4/tcp_westwood.c#L11">11</a> <b><i> *</i></b>
 <a name="L12" href="source/net/ipv4/tcp_westwood.c#L12">12</a> <b><i> * - A. Grieco, s. Mascolo</i></b>
 <a name="L13" href="source/net/ipv4/tcp_westwood.c#L13">13</a> <b><i> *   "Performance evaluation of New Reno, Vegas, Westwood+ TCP" ACM Computer</i></b>
 <a name="L14" href="source/net/ipv4/tcp_westwood.c#L14">14</a> <b><i> *     Comm. Review, 2004</i></b>
 <a name="L15" href="source/net/ipv4/tcp_westwood.c#L15">15</a> <b><i> *</i></b>
 <a name="L16" href="source/net/ipv4/tcp_westwood.c#L16">16</a> <b><i> * - A. Dell'Aera, L. Grieco, S. Mascolo.</i></b>
 <a name="L17" href="source/net/ipv4/tcp_westwood.c#L17">17</a> <b><i> *   "Linux 2.4 Implementation of Westwood+ TCP with Rate-Halving :</i></b>
 <a name="L18" href="source/net/ipv4/tcp_westwood.c#L18">18</a> <b><i> *    A Performance Evaluation Over the Internet" (ICC 2004), Paris, June 2004</i></b>
 <a name="L19" href="source/net/ipv4/tcp_westwood.c#L19">19</a> <b><i> *</i></b>
 <a name="L20" href="source/net/ipv4/tcp_westwood.c#L20">20</a> <b><i> * Westwood+ employs end-to-end bandwidth measurement to set cwnd and</i></b>
 <a name="L21" href="source/net/ipv4/tcp_westwood.c#L21">21</a> <b><i> * ssthresh after packet loss. The probing phase is as the original Reno.</i></b>
 <a name="L22" href="source/net/ipv4/tcp_westwood.c#L22">22</a> <b><i> */</i></b>
 <a name="L23" href="source/net/ipv4/tcp_westwood.c#L23">23</a> 
 <a name="L24" href="source/net/ipv4/tcp_westwood.c#L24">24</a> #include &lt;linux/mm.h&gt;
 <a name="L25" href="source/net/ipv4/tcp_westwood.c#L25">25</a> #include &lt;linux/module.h&gt;
 <a name="L26" href="source/net/ipv4/tcp_westwood.c#L26">26</a> #include &lt;linux/skbuff.h&gt;
 <a name="L27" href="source/net/ipv4/tcp_westwood.c#L27">27</a> #include &lt;linux/inet_diag.h&gt;
 <a name="L28" href="source/net/ipv4/tcp_westwood.c#L28">28</a> #include &lt;net/tcp.h&gt;
 <a name="L29" href="source/net/ipv4/tcp_westwood.c#L29">29</a> 
 <a name="L30" href="source/net/ipv4/tcp_westwood.c#L30">30</a> <b><i>/* TCP Westwood structure */</i></b>
 <a name="L31" href="source/net/ipv4/tcp_westwood.c#L31">31</a> struct <a href="ident?i=westwood">westwood</a> {
 <a name="L32" href="source/net/ipv4/tcp_westwood.c#L32">32</a>         <a href="ident?i=u32">u32</a>    bw_ns_est;        <b><i>/* first bandwidth estimation..not too smoothed 8) */</i></b>
 <a name="L33" href="source/net/ipv4/tcp_westwood.c#L33">33</a>         <a href="ident?i=u32">u32</a>    bw_est;           <b><i>/* bandwidth estimate */</i></b>
 <a name="L34" href="source/net/ipv4/tcp_westwood.c#L34">34</a>         <a href="ident?i=u32">u32</a>    rtt_win_sx;       <b><i>/* here starts a new evaluation... */</i></b>
 <a name="L35" href="source/net/ipv4/tcp_westwood.c#L35">35</a>         <a href="ident?i=u32">u32</a>    <a href="ident?i=bk">bk</a>;
 <a name="L36" href="source/net/ipv4/tcp_westwood.c#L36">36</a>         <a href="ident?i=u32">u32</a>    snd_una;          <b><i>/* used for evaluating the number of acked bytes */</i></b>
 <a name="L37" href="source/net/ipv4/tcp_westwood.c#L37">37</a>         <a href="ident?i=u32">u32</a>    cumul_ack;
 <a name="L38" href="source/net/ipv4/tcp_westwood.c#L38">38</a>         <a href="ident?i=u32">u32</a>    accounted;
 <a name="L39" href="source/net/ipv4/tcp_westwood.c#L39">39</a>         <a href="ident?i=u32">u32</a>    rtt;
 <a name="L40" href="source/net/ipv4/tcp_westwood.c#L40">40</a>         <a href="ident?i=u32">u32</a>    rtt_min;          <b><i>/* minimum observed RTT */</i></b>
 <a name="L41" href="source/net/ipv4/tcp_westwood.c#L41">41</a>         <a href="ident?i=u8">u8</a>     first_ack;        <b><i>/* flag which infers that this is the first ack */</i></b>
 <a name="L42" href="source/net/ipv4/tcp_westwood.c#L42">42</a>         <a href="ident?i=u8">u8</a>     reset_rtt_min;    <b><i>/* Reset RTT min to next RTT sample*/</i></b>
 <a name="L43" href="source/net/ipv4/tcp_westwood.c#L43">43</a> };
 <a name="L44" href="source/net/ipv4/tcp_westwood.c#L44">44</a> 
 <a name="L45" href="source/net/ipv4/tcp_westwood.c#L45">45</a> <b><i>/* TCP Westwood functions and constants */</i></b>
 <a name="L46" href="source/net/ipv4/tcp_westwood.c#L46">46</a> #define <a href="ident?i=TCP_WESTWOOD_RTT_MIN">TCP_WESTWOOD_RTT_MIN</a>   (<a href="ident?i=HZ">HZ</a>/20)  <b><i>/* 50ms */</i></b>
 <a name="L47" href="source/net/ipv4/tcp_westwood.c#L47">47</a> #define <a href="ident?i=TCP_WESTWOOD_INIT_RTT">TCP_WESTWOOD_INIT_RTT</a>  (20*<a href="ident?i=HZ">HZ</a>)  <b><i>/* maybe too conservative?! */</i></b>
 <a name="L48" href="source/net/ipv4/tcp_westwood.c#L48">48</a> 
 <a name="L49" href="source/net/ipv4/tcp_westwood.c#L49">49</a> <b><i>/*</i></b>
 <a name="L50" href="source/net/ipv4/tcp_westwood.c#L50">50</a> <b><i> * @tcp_westwood_create</i></b>
 <a name="L51" href="source/net/ipv4/tcp_westwood.c#L51">51</a> <b><i> * This function initializes fields used in TCP Westwood+,</i></b>
 <a name="L52" href="source/net/ipv4/tcp_westwood.c#L52">52</a> <b><i> * it is called after the initial SYN, so the sequence numbers</i></b>
 <a name="L53" href="source/net/ipv4/tcp_westwood.c#L53">53</a> <b><i> * are correct but new passive connections we have no</i></b>
 <a name="L54" href="source/net/ipv4/tcp_westwood.c#L54">54</a> <b><i> * information about RTTmin at this time so we simply set it to</i></b>
 <a name="L55" href="source/net/ipv4/tcp_westwood.c#L55">55</a> <b><i> * TCP_WESTWOOD_INIT_RTT. This value was chosen to be too conservative</i></b>
 <a name="L56" href="source/net/ipv4/tcp_westwood.c#L56">56</a> <b><i> * since in this way we're sure it will be updated in a consistent</i></b>
 <a name="L57" href="source/net/ipv4/tcp_westwood.c#L57">57</a> <b><i> * way as soon as possible. It will reasonably happen within the first</i></b>
 <a name="L58" href="source/net/ipv4/tcp_westwood.c#L58">58</a> <b><i> * RTT period of the connection lifetime.</i></b>
 <a name="L59" href="source/net/ipv4/tcp_westwood.c#L59">59</a> <b><i> */</i></b>
 <a name="L60" href="source/net/ipv4/tcp_westwood.c#L60">60</a> static void <a href="ident?i=tcp_westwood_init">tcp_westwood_init</a>(struct <a href="ident?i=sock">sock</a> *sk)
 <a name="L61" href="source/net/ipv4/tcp_westwood.c#L61">61</a> {
 <a name="L62" href="source/net/ipv4/tcp_westwood.c#L62">62</a>         struct <a href="ident?i=westwood">westwood</a> *<a href="ident?i=w">w</a> = <a href="ident?i=inet_csk_ca">inet_csk_ca</a>(sk);
 <a name="L63" href="source/net/ipv4/tcp_westwood.c#L63">63</a> 
 <a name="L64" href="source/net/ipv4/tcp_westwood.c#L64">64</a>         <a href="ident?i=w">w</a>-&gt;<a href="ident?i=bk">bk</a> = 0;
 <a name="L65" href="source/net/ipv4/tcp_westwood.c#L65">65</a>         <a href="ident?i=w">w</a>-&gt;bw_ns_est = 0;
 <a name="L66" href="source/net/ipv4/tcp_westwood.c#L66">66</a>         <a href="ident?i=w">w</a>-&gt;bw_est = 0;
 <a name="L67" href="source/net/ipv4/tcp_westwood.c#L67">67</a>         <a href="ident?i=w">w</a>-&gt;accounted = 0;
 <a name="L68" href="source/net/ipv4/tcp_westwood.c#L68">68</a>         <a href="ident?i=w">w</a>-&gt;cumul_ack = 0;
 <a name="L69" href="source/net/ipv4/tcp_westwood.c#L69">69</a>         <a href="ident?i=w">w</a>-&gt;reset_rtt_min = 1;
 <a name="L70" href="source/net/ipv4/tcp_westwood.c#L70">70</a>         <a href="ident?i=w">w</a>-&gt;rtt_min = <a href="ident?i=w">w</a>-&gt;rtt = <a href="ident?i=TCP_WESTWOOD_INIT_RTT">TCP_WESTWOOD_INIT_RTT</a>;
 <a name="L71" href="source/net/ipv4/tcp_westwood.c#L71">71</a>         <a href="ident?i=w">w</a>-&gt;rtt_win_sx = <a href="ident?i=tcp_time_stamp">tcp_time_stamp</a>;
 <a name="L72" href="source/net/ipv4/tcp_westwood.c#L72">72</a>         <a href="ident?i=w">w</a>-&gt;snd_una = <a href="ident?i=tcp_sk">tcp_sk</a>(sk)-&gt;snd_una;
 <a name="L73" href="source/net/ipv4/tcp_westwood.c#L73">73</a>         <a href="ident?i=w">w</a>-&gt;first_ack = 1;
 <a name="L74" href="source/net/ipv4/tcp_westwood.c#L74">74</a> }
 <a name="L75" href="source/net/ipv4/tcp_westwood.c#L75">75</a> 
 <a name="L76" href="source/net/ipv4/tcp_westwood.c#L76">76</a> <b><i>/*</i></b>
 <a name="L77" href="source/net/ipv4/tcp_westwood.c#L77">77</a> <b><i> * @westwood_do_filter</i></b>
 <a name="L78" href="source/net/ipv4/tcp_westwood.c#L78">78</a> <b><i> * Low-pass filter. Implemented using constant coefficients.</i></b>
 <a name="L79" href="source/net/ipv4/tcp_westwood.c#L79">79</a> <b><i> */</i></b>
 <a name="L80" href="source/net/ipv4/tcp_westwood.c#L80">80</a> static inline <a href="ident?i=u32">u32</a> <a href="ident?i=westwood_do_filter">westwood_do_filter</a>(<a href="ident?i=u32">u32</a> <a href="ident?i=a">a</a>, <a href="ident?i=u32">u32</a> <a href="ident?i=b">b</a>)
 <a name="L81" href="source/net/ipv4/tcp_westwood.c#L81">81</a> {
 <a name="L82" href="source/net/ipv4/tcp_westwood.c#L82">82</a>         return ((7 * <a href="ident?i=a">a</a>) + <a href="ident?i=b">b</a>) &gt;&gt; 3;
 <a name="L83" href="source/net/ipv4/tcp_westwood.c#L83">83</a> }
 <a name="L84" href="source/net/ipv4/tcp_westwood.c#L84">84</a> 
 <a name="L85" href="source/net/ipv4/tcp_westwood.c#L85">85</a> static void <a href="ident?i=westwood_filter">westwood_filter</a>(struct <a href="ident?i=westwood">westwood</a> *<a href="ident?i=w">w</a>, <a href="ident?i=u32">u32</a> <a href="ident?i=delta">delta</a>)
 <a name="L86" href="source/net/ipv4/tcp_westwood.c#L86">86</a> {
 <a name="L87" href="source/net/ipv4/tcp_westwood.c#L87">87</a>         <b><i>/* If the filter is empty fill it with the first sample of bandwidth  */</i></b>
 <a name="L88" href="source/net/ipv4/tcp_westwood.c#L88">88</a>         if (<a href="ident?i=w">w</a>-&gt;bw_ns_est == 0 &amp;&amp; <a href="ident?i=w">w</a>-&gt;bw_est == 0) {
 <a name="L89" href="source/net/ipv4/tcp_westwood.c#L89">89</a>                 <a href="ident?i=w">w</a>-&gt;bw_ns_est = <a href="ident?i=w">w</a>-&gt;<a href="ident?i=bk">bk</a> / <a href="ident?i=delta">delta</a>;
 <a name="L90" href="source/net/ipv4/tcp_westwood.c#L90">90</a>                 <a href="ident?i=w">w</a>-&gt;bw_est = <a href="ident?i=w">w</a>-&gt;bw_ns_est;
 <a name="L91" href="source/net/ipv4/tcp_westwood.c#L91">91</a>         } else {
 <a name="L92" href="source/net/ipv4/tcp_westwood.c#L92">92</a>                 <a href="ident?i=w">w</a>-&gt;bw_ns_est = <a href="ident?i=westwood_do_filter">westwood_do_filter</a>(<a href="ident?i=w">w</a>-&gt;bw_ns_est, <a href="ident?i=w">w</a>-&gt;<a href="ident?i=bk">bk</a> / <a href="ident?i=delta">delta</a>);
 <a name="L93" href="source/net/ipv4/tcp_westwood.c#L93">93</a>                 <a href="ident?i=w">w</a>-&gt;bw_est = <a href="ident?i=westwood_do_filter">westwood_do_filter</a>(<a href="ident?i=w">w</a>-&gt;bw_est, <a href="ident?i=w">w</a>-&gt;bw_ns_est);
 <a name="L94" href="source/net/ipv4/tcp_westwood.c#L94">94</a>         }
 <a name="L95" href="source/net/ipv4/tcp_westwood.c#L95">95</a> }
 <a name="L96" href="source/net/ipv4/tcp_westwood.c#L96">96</a> 
 <a name="L97" href="source/net/ipv4/tcp_westwood.c#L97">97</a> <b><i>/*</i></b>
 <a name="L98" href="source/net/ipv4/tcp_westwood.c#L98">98</a> <b><i> * @westwood_pkts_acked</i></b>
 <a name="L99" href="source/net/ipv4/tcp_westwood.c#L99">99</a> <b><i> * Called after processing group of packets.</i></b>
<a name="L100" href="source/net/ipv4/tcp_westwood.c#L100">100</a> <b><i> * but all westwood needs is the last sample of srtt.</i></b>
<a name="L101" href="source/net/ipv4/tcp_westwood.c#L101">101</a> <b><i> */</i></b>
<a name="L102" href="source/net/ipv4/tcp_westwood.c#L102">102</a> static void <a href="ident?i=tcp_westwood_pkts_acked">tcp_westwood_pkts_acked</a>(struct <a href="ident?i=sock">sock</a> *sk, <a href="ident?i=u32">u32</a> cnt, <a href="ident?i=s32">s32</a> rtt)
<a name="L103" href="source/net/ipv4/tcp_westwood.c#L103">103</a> {
<a name="L104" href="source/net/ipv4/tcp_westwood.c#L104">104</a>         struct <a href="ident?i=westwood">westwood</a> *<a href="ident?i=w">w</a> = <a href="ident?i=inet_csk_ca">inet_csk_ca</a>(sk);
<a name="L105" href="source/net/ipv4/tcp_westwood.c#L105">105</a> 
<a name="L106" href="source/net/ipv4/tcp_westwood.c#L106">106</a>         if (rtt &gt; 0)
<a name="L107" href="source/net/ipv4/tcp_westwood.c#L107">107</a>                 <a href="ident?i=w">w</a>-&gt;rtt = <a href="ident?i=usecs_to_jiffies">usecs_to_jiffies</a>(rtt);
<a name="L108" href="source/net/ipv4/tcp_westwood.c#L108">108</a> }
<a name="L109" href="source/net/ipv4/tcp_westwood.c#L109">109</a> 
<a name="L110" href="source/net/ipv4/tcp_westwood.c#L110">110</a> <b><i>/*</i></b>
<a name="L111" href="source/net/ipv4/tcp_westwood.c#L111">111</a> <b><i> * @westwood_update_window</i></b>
<a name="L112" href="source/net/ipv4/tcp_westwood.c#L112">112</a> <b><i> * It updates RTT evaluation window if it is the right moment to do</i></b>
<a name="L113" href="source/net/ipv4/tcp_westwood.c#L113">113</a> <b><i> * it. If so it calls filter for evaluating bandwidth.</i></b>
<a name="L114" href="source/net/ipv4/tcp_westwood.c#L114">114</a> <b><i> */</i></b>
<a name="L115" href="source/net/ipv4/tcp_westwood.c#L115">115</a> static void <a href="ident?i=westwood_update_window">westwood_update_window</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L116" href="source/net/ipv4/tcp_westwood.c#L116">116</a> {
<a name="L117" href="source/net/ipv4/tcp_westwood.c#L117">117</a>         struct <a href="ident?i=westwood">westwood</a> *<a href="ident?i=w">w</a> = <a href="ident?i=inet_csk_ca">inet_csk_ca</a>(sk);
<a name="L118" href="source/net/ipv4/tcp_westwood.c#L118">118</a>         <a href="ident?i=s32">s32</a> <a href="ident?i=delta">delta</a> = <a href="ident?i=tcp_time_stamp">tcp_time_stamp</a> - <a href="ident?i=w">w</a>-&gt;rtt_win_sx;
<a name="L119" href="source/net/ipv4/tcp_westwood.c#L119">119</a> 
<a name="L120" href="source/net/ipv4/tcp_westwood.c#L120">120</a>         <b><i>/* Initialize w-&gt;snd_una with the first acked sequence number in order</i></b>
<a name="L121" href="source/net/ipv4/tcp_westwood.c#L121">121</a> <b><i>         * to fix mismatch between tp-&gt;snd_una and w-&gt;snd_una for the first</i></b>
<a name="L122" href="source/net/ipv4/tcp_westwood.c#L122">122</a> <b><i>         * bandwidth sample</i></b>
<a name="L123" href="source/net/ipv4/tcp_westwood.c#L123">123</a> <b><i>         */</i></b>
<a name="L124" href="source/net/ipv4/tcp_westwood.c#L124">124</a>         if (<a href="ident?i=w">w</a>-&gt;first_ack) {
<a name="L125" href="source/net/ipv4/tcp_westwood.c#L125">125</a>                 <a href="ident?i=w">w</a>-&gt;snd_una = <a href="ident?i=tcp_sk">tcp_sk</a>(sk)-&gt;snd_una;
<a name="L126" href="source/net/ipv4/tcp_westwood.c#L126">126</a>                 <a href="ident?i=w">w</a>-&gt;first_ack = 0;
<a name="L127" href="source/net/ipv4/tcp_westwood.c#L127">127</a>         }
<a name="L128" href="source/net/ipv4/tcp_westwood.c#L128">128</a> 
<a name="L129" href="source/net/ipv4/tcp_westwood.c#L129">129</a>         <b><i>/*</i></b>
<a name="L130" href="source/net/ipv4/tcp_westwood.c#L130">130</a> <b><i>         * See if a RTT-window has passed.</i></b>
<a name="L131" href="source/net/ipv4/tcp_westwood.c#L131">131</a> <b><i>         * Be careful since if RTT is less than</i></b>
<a name="L132" href="source/net/ipv4/tcp_westwood.c#L132">132</a> <b><i>         * 50ms we don't filter but we continue 'building the sample'.</i></b>
<a name="L133" href="source/net/ipv4/tcp_westwood.c#L133">133</a> <b><i>         * This minimum limit was chosen since an estimation on small</i></b>
<a name="L134" href="source/net/ipv4/tcp_westwood.c#L134">134</a> <b><i>         * time intervals is better to avoid...</i></b>
<a name="L135" href="source/net/ipv4/tcp_westwood.c#L135">135</a> <b><i>         * Obviously on a LAN we reasonably will always have</i></b>
<a name="L136" href="source/net/ipv4/tcp_westwood.c#L136">136</a> <b><i>         * right_bound = left_bound + WESTWOOD_RTT_MIN</i></b>
<a name="L137" href="source/net/ipv4/tcp_westwood.c#L137">137</a> <b><i>         */</i></b>
<a name="L138" href="source/net/ipv4/tcp_westwood.c#L138">138</a>         if (<a href="ident?i=w">w</a>-&gt;rtt &amp;&amp; <a href="ident?i=delta">delta</a> &gt; <a href="ident?i=max_t">max_t</a>(<a href="ident?i=u32">u32</a>, <a href="ident?i=w">w</a>-&gt;rtt, <a href="ident?i=TCP_WESTWOOD_RTT_MIN">TCP_WESTWOOD_RTT_MIN</a>)) {
<a name="L139" href="source/net/ipv4/tcp_westwood.c#L139">139</a>                 <a href="ident?i=westwood_filter">westwood_filter</a>(<a href="ident?i=w">w</a>, <a href="ident?i=delta">delta</a>);
<a name="L140" href="source/net/ipv4/tcp_westwood.c#L140">140</a> 
<a name="L141" href="source/net/ipv4/tcp_westwood.c#L141">141</a>                 <a href="ident?i=w">w</a>-&gt;<a href="ident?i=bk">bk</a> = 0;
<a name="L142" href="source/net/ipv4/tcp_westwood.c#L142">142</a>                 <a href="ident?i=w">w</a>-&gt;rtt_win_sx = <a href="ident?i=tcp_time_stamp">tcp_time_stamp</a>;
<a name="L143" href="source/net/ipv4/tcp_westwood.c#L143">143</a>         }
<a name="L144" href="source/net/ipv4/tcp_westwood.c#L144">144</a> }
<a name="L145" href="source/net/ipv4/tcp_westwood.c#L145">145</a> 
<a name="L146" href="source/net/ipv4/tcp_westwood.c#L146">146</a> static inline void <a href="ident?i=update_rtt_min">update_rtt_min</a>(struct <a href="ident?i=westwood">westwood</a> *<a href="ident?i=w">w</a>)
<a name="L147" href="source/net/ipv4/tcp_westwood.c#L147">147</a> {
<a name="L148" href="source/net/ipv4/tcp_westwood.c#L148">148</a>         if (<a href="ident?i=w">w</a>-&gt;reset_rtt_min) {
<a name="L149" href="source/net/ipv4/tcp_westwood.c#L149">149</a>                 <a href="ident?i=w">w</a>-&gt;rtt_min = <a href="ident?i=w">w</a>-&gt;rtt;
<a name="L150" href="source/net/ipv4/tcp_westwood.c#L150">150</a>                 <a href="ident?i=w">w</a>-&gt;reset_rtt_min = 0;
<a name="L151" href="source/net/ipv4/tcp_westwood.c#L151">151</a>         } else
<a name="L152" href="source/net/ipv4/tcp_westwood.c#L152">152</a>                 <a href="ident?i=w">w</a>-&gt;rtt_min = <a href="ident?i=min">min</a>(<a href="ident?i=w">w</a>-&gt;rtt, <a href="ident?i=w">w</a>-&gt;rtt_min);
<a name="L153" href="source/net/ipv4/tcp_westwood.c#L153">153</a> }
<a name="L154" href="source/net/ipv4/tcp_westwood.c#L154">154</a> 
<a name="L155" href="source/net/ipv4/tcp_westwood.c#L155">155</a> <b><i>/*</i></b>
<a name="L156" href="source/net/ipv4/tcp_westwood.c#L156">156</a> <b><i> * @westwood_fast_bw</i></b>
<a name="L157" href="source/net/ipv4/tcp_westwood.c#L157">157</a> <b><i> * It is called when we are in fast path. In particular it is called when</i></b>
<a name="L158" href="source/net/ipv4/tcp_westwood.c#L158">158</a> <b><i> * header prediction is successful. In such case in fact update is</i></b>
<a name="L159" href="source/net/ipv4/tcp_westwood.c#L159">159</a> <b><i> * straight forward and doesn't need any particular care.</i></b>
<a name="L160" href="source/net/ipv4/tcp_westwood.c#L160">160</a> <b><i> */</i></b>
<a name="L161" href="source/net/ipv4/tcp_westwood.c#L161">161</a> static inline void <a href="ident?i=westwood_fast_bw">westwood_fast_bw</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L162" href="source/net/ipv4/tcp_westwood.c#L162">162</a> {
<a name="L163" href="source/net/ipv4/tcp_westwood.c#L163">163</a>         const struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L164" href="source/net/ipv4/tcp_westwood.c#L164">164</a>         struct <a href="ident?i=westwood">westwood</a> *<a href="ident?i=w">w</a> = <a href="ident?i=inet_csk_ca">inet_csk_ca</a>(sk);
<a name="L165" href="source/net/ipv4/tcp_westwood.c#L165">165</a> 
<a name="L166" href="source/net/ipv4/tcp_westwood.c#L166">166</a>         <a href="ident?i=westwood_update_window">westwood_update_window</a>(sk);
<a name="L167" href="source/net/ipv4/tcp_westwood.c#L167">167</a> 
<a name="L168" href="source/net/ipv4/tcp_westwood.c#L168">168</a>         <a href="ident?i=w">w</a>-&gt;<a href="ident?i=bk">bk</a> += <a href="ident?i=tp">tp</a>-&gt;snd_una - <a href="ident?i=w">w</a>-&gt;snd_una;
<a name="L169" href="source/net/ipv4/tcp_westwood.c#L169">169</a>         <a href="ident?i=w">w</a>-&gt;snd_una = <a href="ident?i=tp">tp</a>-&gt;snd_una;
<a name="L170" href="source/net/ipv4/tcp_westwood.c#L170">170</a>         <a href="ident?i=update_rtt_min">update_rtt_min</a>(<a href="ident?i=w">w</a>);
<a name="L171" href="source/net/ipv4/tcp_westwood.c#L171">171</a> }
<a name="L172" href="source/net/ipv4/tcp_westwood.c#L172">172</a> 
<a name="L173" href="source/net/ipv4/tcp_westwood.c#L173">173</a> <b><i>/*</i></b>
<a name="L174" href="source/net/ipv4/tcp_westwood.c#L174">174</a> <b><i> * @westwood_acked_count</i></b>
<a name="L175" href="source/net/ipv4/tcp_westwood.c#L175">175</a> <b><i> * This function evaluates cumul_ack for evaluating bk in case of</i></b>
<a name="L176" href="source/net/ipv4/tcp_westwood.c#L176">176</a> <b><i> * delayed or partial acks.</i></b>
<a name="L177" href="source/net/ipv4/tcp_westwood.c#L177">177</a> <b><i> */</i></b>
<a name="L178" href="source/net/ipv4/tcp_westwood.c#L178">178</a> static inline <a href="ident?i=u32">u32</a> <a href="ident?i=westwood_acked_count">westwood_acked_count</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L179" href="source/net/ipv4/tcp_westwood.c#L179">179</a> {
<a name="L180" href="source/net/ipv4/tcp_westwood.c#L180">180</a>         const struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L181" href="source/net/ipv4/tcp_westwood.c#L181">181</a>         struct <a href="ident?i=westwood">westwood</a> *<a href="ident?i=w">w</a> = <a href="ident?i=inet_csk_ca">inet_csk_ca</a>(sk);
<a name="L182" href="source/net/ipv4/tcp_westwood.c#L182">182</a> 
<a name="L183" href="source/net/ipv4/tcp_westwood.c#L183">183</a>         <a href="ident?i=w">w</a>-&gt;cumul_ack = <a href="ident?i=tp">tp</a>-&gt;snd_una - <a href="ident?i=w">w</a>-&gt;snd_una;
<a name="L184" href="source/net/ipv4/tcp_westwood.c#L184">184</a> 
<a name="L185" href="source/net/ipv4/tcp_westwood.c#L185">185</a>         <b><i>/* If cumul_ack is 0 this is a dupack since it's not moving</i></b>
<a name="L186" href="source/net/ipv4/tcp_westwood.c#L186">186</a> <b><i>         * tp-&gt;snd_una.</i></b>
<a name="L187" href="source/net/ipv4/tcp_westwood.c#L187">187</a> <b><i>         */</i></b>
<a name="L188" href="source/net/ipv4/tcp_westwood.c#L188">188</a>         if (!<a href="ident?i=w">w</a>-&gt;cumul_ack) {
<a name="L189" href="source/net/ipv4/tcp_westwood.c#L189">189</a>                 <a href="ident?i=w">w</a>-&gt;accounted += <a href="ident?i=tp">tp</a>-&gt;mss_cache;
<a name="L190" href="source/net/ipv4/tcp_westwood.c#L190">190</a>                 <a href="ident?i=w">w</a>-&gt;cumul_ack = <a href="ident?i=tp">tp</a>-&gt;mss_cache;
<a name="L191" href="source/net/ipv4/tcp_westwood.c#L191">191</a>         }
<a name="L192" href="source/net/ipv4/tcp_westwood.c#L192">192</a> 
<a name="L193" href="source/net/ipv4/tcp_westwood.c#L193">193</a>         if (<a href="ident?i=w">w</a>-&gt;cumul_ack &gt; <a href="ident?i=tp">tp</a>-&gt;mss_cache) {
<a name="L194" href="source/net/ipv4/tcp_westwood.c#L194">194</a>                 <b><i>/* Partial or delayed ack */</i></b>
<a name="L195" href="source/net/ipv4/tcp_westwood.c#L195">195</a>                 if (<a href="ident?i=w">w</a>-&gt;accounted &gt;= <a href="ident?i=w">w</a>-&gt;cumul_ack) {
<a name="L196" href="source/net/ipv4/tcp_westwood.c#L196">196</a>                         <a href="ident?i=w">w</a>-&gt;accounted -= <a href="ident?i=w">w</a>-&gt;cumul_ack;
<a name="L197" href="source/net/ipv4/tcp_westwood.c#L197">197</a>                         <a href="ident?i=w">w</a>-&gt;cumul_ack = <a href="ident?i=tp">tp</a>-&gt;mss_cache;
<a name="L198" href="source/net/ipv4/tcp_westwood.c#L198">198</a>                 } else {
<a name="L199" href="source/net/ipv4/tcp_westwood.c#L199">199</a>                         <a href="ident?i=w">w</a>-&gt;cumul_ack -= <a href="ident?i=w">w</a>-&gt;accounted;
<a name="L200" href="source/net/ipv4/tcp_westwood.c#L200">200</a>                         <a href="ident?i=w">w</a>-&gt;accounted = 0;
<a name="L201" href="source/net/ipv4/tcp_westwood.c#L201">201</a>                 }
<a name="L202" href="source/net/ipv4/tcp_westwood.c#L202">202</a>         }
<a name="L203" href="source/net/ipv4/tcp_westwood.c#L203">203</a> 
<a name="L204" href="source/net/ipv4/tcp_westwood.c#L204">204</a>         <a href="ident?i=w">w</a>-&gt;snd_una = <a href="ident?i=tp">tp</a>-&gt;snd_una;
<a name="L205" href="source/net/ipv4/tcp_westwood.c#L205">205</a> 
<a name="L206" href="source/net/ipv4/tcp_westwood.c#L206">206</a>         return <a href="ident?i=w">w</a>-&gt;cumul_ack;
<a name="L207" href="source/net/ipv4/tcp_westwood.c#L207">207</a> }
<a name="L208" href="source/net/ipv4/tcp_westwood.c#L208">208</a> 
<a name="L209" href="source/net/ipv4/tcp_westwood.c#L209">209</a> <b><i>/*</i></b>
<a name="L210" href="source/net/ipv4/tcp_westwood.c#L210">210</a> <b><i> * TCP Westwood</i></b>
<a name="L211" href="source/net/ipv4/tcp_westwood.c#L211">211</a> <b><i> * Here limit is evaluated as Bw estimation*RTTmin (for obtaining it</i></b>
<a name="L212" href="source/net/ipv4/tcp_westwood.c#L212">212</a> <b><i> * in packets we use mss_cache). Rttmin is guaranteed to be &gt;= 2</i></b>
<a name="L213" href="source/net/ipv4/tcp_westwood.c#L213">213</a> <b><i> * so avoids ever returning 0.</i></b>
<a name="L214" href="source/net/ipv4/tcp_westwood.c#L214">214</a> <b><i> */</i></b>
<a name="L215" href="source/net/ipv4/tcp_westwood.c#L215">215</a> static <a href="ident?i=u32">u32</a> <a href="ident?i=tcp_westwood_bw_rttmin">tcp_westwood_bw_rttmin</a>(const struct <a href="ident?i=sock">sock</a> *sk)
<a name="L216" href="source/net/ipv4/tcp_westwood.c#L216">216</a> {
<a name="L217" href="source/net/ipv4/tcp_westwood.c#L217">217</a>         const struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L218" href="source/net/ipv4/tcp_westwood.c#L218">218</a>         const struct <a href="ident?i=westwood">westwood</a> *<a href="ident?i=w">w</a> = <a href="ident?i=inet_csk_ca">inet_csk_ca</a>(sk);
<a name="L219" href="source/net/ipv4/tcp_westwood.c#L219">219</a> 
<a name="L220" href="source/net/ipv4/tcp_westwood.c#L220">220</a>         return <a href="ident?i=max_t">max_t</a>(<a href="ident?i=u32">u32</a>, (<a href="ident?i=w">w</a>-&gt;bw_est * <a href="ident?i=w">w</a>-&gt;rtt_min) / <a href="ident?i=tp">tp</a>-&gt;mss_cache, 2);
<a name="L221" href="source/net/ipv4/tcp_westwood.c#L221">221</a> }
<a name="L222" href="source/net/ipv4/tcp_westwood.c#L222">222</a> 
<a name="L223" href="source/net/ipv4/tcp_westwood.c#L223">223</a> static void <a href="ident?i=tcp_westwood_ack">tcp_westwood_ack</a>(struct <a href="ident?i=sock">sock</a> *sk, <a href="ident?i=u32">u32</a> ack_flags)
<a name="L224" href="source/net/ipv4/tcp_westwood.c#L224">224</a> {
<a name="L225" href="source/net/ipv4/tcp_westwood.c#L225">225</a>         if (ack_flags &amp; CA_ACK_SLOWPATH) {
<a name="L226" href="source/net/ipv4/tcp_westwood.c#L226">226</a>                 struct <a href="ident?i=westwood">westwood</a> *<a href="ident?i=w">w</a> = <a href="ident?i=inet_csk_ca">inet_csk_ca</a>(sk);
<a name="L227" href="source/net/ipv4/tcp_westwood.c#L227">227</a> 
<a name="L228" href="source/net/ipv4/tcp_westwood.c#L228">228</a>                 <a href="ident?i=westwood_update_window">westwood_update_window</a>(sk);
<a name="L229" href="source/net/ipv4/tcp_westwood.c#L229">229</a>                 <a href="ident?i=w">w</a>-&gt;<a href="ident?i=bk">bk</a> += <a href="ident?i=westwood_acked_count">westwood_acked_count</a>(sk);
<a name="L230" href="source/net/ipv4/tcp_westwood.c#L230">230</a> 
<a name="L231" href="source/net/ipv4/tcp_westwood.c#L231">231</a>                 <a href="ident?i=update_rtt_min">update_rtt_min</a>(<a href="ident?i=w">w</a>);
<a name="L232" href="source/net/ipv4/tcp_westwood.c#L232">232</a>                 return;
<a name="L233" href="source/net/ipv4/tcp_westwood.c#L233">233</a>         }
<a name="L234" href="source/net/ipv4/tcp_westwood.c#L234">234</a> 
<a name="L235" href="source/net/ipv4/tcp_westwood.c#L235">235</a>         <a href="ident?i=westwood_fast_bw">westwood_fast_bw</a>(sk);
<a name="L236" href="source/net/ipv4/tcp_westwood.c#L236">236</a> }
<a name="L237" href="source/net/ipv4/tcp_westwood.c#L237">237</a> 
<a name="L238" href="source/net/ipv4/tcp_westwood.c#L238">238</a> static void <a href="ident?i=tcp_westwood_event">tcp_westwood_event</a>(struct <a href="ident?i=sock">sock</a> *sk, enum <a href="ident?i=tcp_ca_event">tcp_ca_event</a> <a href="ident?i=event">event</a>)
<a name="L239" href="source/net/ipv4/tcp_westwood.c#L239">239</a> {
<a name="L240" href="source/net/ipv4/tcp_westwood.c#L240">240</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L241" href="source/net/ipv4/tcp_westwood.c#L241">241</a>         struct <a href="ident?i=westwood">westwood</a> *<a href="ident?i=w">w</a> = <a href="ident?i=inet_csk_ca">inet_csk_ca</a>(sk);
<a name="L242" href="source/net/ipv4/tcp_westwood.c#L242">242</a> 
<a name="L243" href="source/net/ipv4/tcp_westwood.c#L243">243</a>         switch (<a href="ident?i=event">event</a>) {
<a name="L244" href="source/net/ipv4/tcp_westwood.c#L244">244</a>         case CA_EVENT_COMPLETE_CWR:
<a name="L245" href="source/net/ipv4/tcp_westwood.c#L245">245</a>                 <a href="ident?i=tp">tp</a>-&gt;snd_cwnd = <a href="ident?i=tp">tp</a>-&gt;snd_ssthresh = <a href="ident?i=tcp_westwood_bw_rttmin">tcp_westwood_bw_rttmin</a>(sk);
<a name="L246" href="source/net/ipv4/tcp_westwood.c#L246">246</a>                 break;
<a name="L247" href="source/net/ipv4/tcp_westwood.c#L247">247</a>         case CA_EVENT_LOSS:
<a name="L248" href="source/net/ipv4/tcp_westwood.c#L248">248</a>                 <a href="ident?i=tp">tp</a>-&gt;snd_ssthresh = <a href="ident?i=tcp_westwood_bw_rttmin">tcp_westwood_bw_rttmin</a>(sk);
<a name="L249" href="source/net/ipv4/tcp_westwood.c#L249">249</a>                 <b><i>/* Update RTT_min when next ack arrives */</i></b>
<a name="L250" href="source/net/ipv4/tcp_westwood.c#L250">250</a>                 <a href="ident?i=w">w</a>-&gt;reset_rtt_min = 1;
<a name="L251" href="source/net/ipv4/tcp_westwood.c#L251">251</a>                 break;
<a name="L252" href="source/net/ipv4/tcp_westwood.c#L252">252</a>         default:
<a name="L253" href="source/net/ipv4/tcp_westwood.c#L253">253</a>                 <b><i>/* don't care */</i></b>
<a name="L254" href="source/net/ipv4/tcp_westwood.c#L254">254</a>                 break;
<a name="L255" href="source/net/ipv4/tcp_westwood.c#L255">255</a>         }
<a name="L256" href="source/net/ipv4/tcp_westwood.c#L256">256</a> }
<a name="L257" href="source/net/ipv4/tcp_westwood.c#L257">257</a> 
<a name="L258" href="source/net/ipv4/tcp_westwood.c#L258">258</a> <b><i>/* Extract info for Tcp socket info provided via netlink. */</i></b>
<a name="L259" href="source/net/ipv4/tcp_westwood.c#L259">259</a> static <a href="ident?i=size_t">size_t</a> <a href="ident?i=tcp_westwood_info">tcp_westwood_info</a>(struct <a href="ident?i=sock">sock</a> *sk, <a href="ident?i=u32">u32</a> ext, int *<a href="ident?i=attr">attr</a>,
<a name="L260" href="source/net/ipv4/tcp_westwood.c#L260">260</a>                                 union <a href="ident?i=tcp_cc_info">tcp_cc_info</a> *<a href="ident?i=info">info</a>)
<a name="L261" href="source/net/ipv4/tcp_westwood.c#L261">261</a> {
<a name="L262" href="source/net/ipv4/tcp_westwood.c#L262">262</a>         const struct <a href="ident?i=westwood">westwood</a> *<a href="ident?i=ca">ca</a> = <a href="ident?i=inet_csk_ca">inet_csk_ca</a>(sk);
<a name="L263" href="source/net/ipv4/tcp_westwood.c#L263">263</a> 
<a name="L264" href="source/net/ipv4/tcp_westwood.c#L264">264</a>         if (ext &amp; (1 &lt;&lt; (INET_DIAG_VEGASINFO - 1))) {
<a name="L265" href="source/net/ipv4/tcp_westwood.c#L265">265</a>                 <a href="ident?i=info">info</a>-&gt;<a href="ident?i=vegas">vegas</a>.tcpv_enabled = 1;
<a name="L266" href="source/net/ipv4/tcp_westwood.c#L266">266</a>                 <a href="ident?i=info">info</a>-&gt;<a href="ident?i=vegas">vegas</a>.tcpv_rttcnt = 0;
<a name="L267" href="source/net/ipv4/tcp_westwood.c#L267">267</a>                 <a href="ident?i=info">info</a>-&gt;<a href="ident?i=vegas">vegas</a>.tcpv_rtt    = <a href="ident?i=jiffies_to_usecs">jiffies_to_usecs</a>(<a href="ident?i=ca">ca</a>-&gt;rtt),
<a name="L268" href="source/net/ipv4/tcp_westwood.c#L268">268</a>                 <a href="ident?i=info">info</a>-&gt;<a href="ident?i=vegas">vegas</a>.tcpv_minrtt = <a href="ident?i=jiffies_to_usecs">jiffies_to_usecs</a>(<a href="ident?i=ca">ca</a>-&gt;rtt_min),
<a name="L269" href="source/net/ipv4/tcp_westwood.c#L269">269</a> 
<a name="L270" href="source/net/ipv4/tcp_westwood.c#L270">270</a>                 *<a href="ident?i=attr">attr</a> = INET_DIAG_VEGASINFO;
<a name="L271" href="source/net/ipv4/tcp_westwood.c#L271">271</a>                 return sizeof(struct <a href="ident?i=tcpvegas_info">tcpvegas_info</a>);
<a name="L272" href="source/net/ipv4/tcp_westwood.c#L272">272</a>         }
<a name="L273" href="source/net/ipv4/tcp_westwood.c#L273">273</a>         return 0;
<a name="L274" href="source/net/ipv4/tcp_westwood.c#L274">274</a> }
<a name="L275" href="source/net/ipv4/tcp_westwood.c#L275">275</a> 
<a name="L276" href="source/net/ipv4/tcp_westwood.c#L276">276</a> static struct <a href="ident?i=tcp_congestion_ops">tcp_congestion_ops</a> tcp_westwood <a href="ident?i=__read_mostly">__read_mostly</a> = {
<a name="L277" href="source/net/ipv4/tcp_westwood.c#L277">277</a>         .<a href="ident?i=init">init</a>           = <a href="ident?i=tcp_westwood_init">tcp_westwood_init</a>,
<a name="L278" href="source/net/ipv4/tcp_westwood.c#L278">278</a>         .ssthresh       = <a href="ident?i=tcp_reno_ssthresh">tcp_reno_ssthresh</a>,
<a name="L279" href="source/net/ipv4/tcp_westwood.c#L279">279</a>         .cong_avoid     = <a href="ident?i=tcp_reno_cong_avoid">tcp_reno_cong_avoid</a>,
<a name="L280" href="source/net/ipv4/tcp_westwood.c#L280">280</a>         .cwnd_event     = <a href="ident?i=tcp_westwood_event">tcp_westwood_event</a>,
<a name="L281" href="source/net/ipv4/tcp_westwood.c#L281">281</a>         .in_ack_event   = <a href="ident?i=tcp_westwood_ack">tcp_westwood_ack</a>,
<a name="L282" href="source/net/ipv4/tcp_westwood.c#L282">282</a>         .<a href="ident?i=get_info">get_info</a>       = <a href="ident?i=tcp_westwood_info">tcp_westwood_info</a>,
<a name="L283" href="source/net/ipv4/tcp_westwood.c#L283">283</a>         .pkts_acked     = <a href="ident?i=tcp_westwood_pkts_acked">tcp_westwood_pkts_acked</a>,
<a name="L284" href="source/net/ipv4/tcp_westwood.c#L284">284</a> 
<a name="L285" href="source/net/ipv4/tcp_westwood.c#L285">285</a>         .owner          = <a href="ident?i=THIS_MODULE">THIS_MODULE</a>,
<a name="L286" href="source/net/ipv4/tcp_westwood.c#L286">286</a>         .<a href="ident?i=name">name</a>           = <i>"westwood"</i>
<a name="L287" href="source/net/ipv4/tcp_westwood.c#L287">287</a> };
<a name="L288" href="source/net/ipv4/tcp_westwood.c#L288">288</a> 
<a name="L289" href="source/net/ipv4/tcp_westwood.c#L289">289</a> static int <a href="ident?i=__init">__init</a> <a href="ident?i=tcp_westwood_register">tcp_westwood_register</a>(void)
<a name="L290" href="source/net/ipv4/tcp_westwood.c#L290">290</a> {
<a name="L291" href="source/net/ipv4/tcp_westwood.c#L291">291</a>         <a href="ident?i=BUILD_BUG_ON">BUILD_BUG_ON</a>(sizeof(struct <a href="ident?i=westwood">westwood</a>) &gt; <a href="ident?i=ICSK_CA_PRIV_SIZE">ICSK_CA_PRIV_SIZE</a>);
<a name="L292" href="source/net/ipv4/tcp_westwood.c#L292">292</a>         return <a href="ident?i=tcp_register_congestion_control">tcp_register_congestion_control</a>(&amp;tcp_westwood);
<a name="L293" href="source/net/ipv4/tcp_westwood.c#L293">293</a> }
<a name="L294" href="source/net/ipv4/tcp_westwood.c#L294">294</a> 
<a name="L295" href="source/net/ipv4/tcp_westwood.c#L295">295</a> static void <a href="ident?i=__exit">__exit</a> <a href="ident?i=tcp_westwood_unregister">tcp_westwood_unregister</a>(void)
<a name="L296" href="source/net/ipv4/tcp_westwood.c#L296">296</a> {
<a name="L297" href="source/net/ipv4/tcp_westwood.c#L297">297</a>         <a href="ident?i=tcp_unregister_congestion_control">tcp_unregister_congestion_control</a>(&amp;tcp_westwood);
<a name="L298" href="source/net/ipv4/tcp_westwood.c#L298">298</a> }
<a name="L299" href="source/net/ipv4/tcp_westwood.c#L299">299</a> 
<a name="L300" href="source/net/ipv4/tcp_westwood.c#L300">300</a> <a href="ident?i=module_init">module_init</a>(<a href="ident?i=tcp_westwood_register">tcp_westwood_register</a>);
<a name="L301" href="source/net/ipv4/tcp_westwood.c#L301">301</a> <a href="ident?i=module_exit">module_exit</a>(<a href="ident?i=tcp_westwood_unregister">tcp_westwood_unregister</a>);
<a name="L302" href="source/net/ipv4/tcp_westwood.c#L302">302</a> 
<a name="L303" href="source/net/ipv4/tcp_westwood.c#L303">303</a> <a href="ident?i=MODULE_AUTHOR">MODULE_AUTHOR</a>(<i>"Stephen Hemminger, Angelo Dell'Aera"</i>);
<a name="L304" href="source/net/ipv4/tcp_westwood.c#L304">304</a> <a href="ident?i=MODULE_LICENSE">MODULE_LICENSE</a>(<i>"GPL"</i>);
<a name="L305" href="source/net/ipv4/tcp_westwood.c#L305">305</a> <a href="ident?i=MODULE_DESCRIPTION">MODULE_DESCRIPTION</a>(<i>"TCP Westwood+"</i>);
<a name="L306" href="source/net/ipv4/tcp_westwood.c#L306">306</a> </pre></div><p>
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
