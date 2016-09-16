<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title>Linux/net/ipv4/tcp_htcp.c - Linux Cross Reference - Free Electrons</title>
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
		 &nbsp;&bull;&nbsp;<b><i>source navigation</i></b> &nbsp;&bull;&nbsp;<a href="diff/net/ipv4/tcp_htcp.c">diff markup</a> &nbsp;&bull;&nbsp;<a href="ident">identifier search</a> &nbsp;&bull;&nbsp;<a href="search">freetext search</a> &nbsp;&bull;&nbsp;
		</p>
	</div>
</div>

<div id="topbar">
  
  <p>Version: &nbsp;<a href="source/net/ipv4/tcp_htcp.c?v=2.0.40">2.0.40</a>&nbsp;<a href="source/net/ipv4/tcp_htcp.c?v=2.2.26">2.2.26</a>&nbsp;<a href="source/net/ipv4/tcp_htcp.c?v=2.4.37">2.4.37</a>&nbsp;<a href="source/net/ipv4/tcp_htcp.c?v=3.5">3.5</a>&nbsp;<a href="source/net/ipv4/tcp_htcp.c?v=3.6">3.6</a>&nbsp;<a href="source/net/ipv4/tcp_htcp.c?v=3.7">3.7</a>&nbsp;<a href="source/net/ipv4/tcp_htcp.c?v=3.8">3.8</a>&nbsp;<a href="source/net/ipv4/tcp_htcp.c?v=3.9">3.9</a>&nbsp;<a href="source/net/ipv4/tcp_htcp.c?v=3.10">3.10</a>&nbsp;<a href="source/net/ipv4/tcp_htcp.c?v=3.11">3.11</a>&nbsp;<a href="source/net/ipv4/tcp_htcp.c?v=3.12">3.12</a>&nbsp;<a href="source/net/ipv4/tcp_htcp.c?v=3.13">3.13</a>&nbsp;<a href="source/net/ipv4/tcp_htcp.c?v=3.14">3.14</a>&nbsp;<a href="source/net/ipv4/tcp_htcp.c?v=3.15">3.15</a>&nbsp;<a href="source/net/ipv4/tcp_htcp.c?v=3.16">3.16</a>&nbsp;<a href="source/net/ipv4/tcp_htcp.c?v=3.17">3.17</a>&nbsp;<a href="source/net/ipv4/tcp_htcp.c?v=3.18">3.18</a>&nbsp;<a href="source/net/ipv4/tcp_htcp.c?v=3.19">3.19</a>&nbsp;<a href="source/net/ipv4/tcp_htcp.c?v=4.0">4.0</a>&nbsp;<b><i>4.1</i></b></p>
  
</div>

<h1><a href="source/">Linux</a>/<a href="source/net/">net</a>/<a href="source/net/ipv4/">ipv4</a>/<a href="source/net/ipv4/tcp_htcp.c">tcp_htcp.c</a></h1>
<div id="lxrcode"><pre>  <a name="L1" href="source/net/ipv4/tcp_htcp.c#L1">1</a> <b><i>/*</i></b>
  <a name="L2" href="source/net/ipv4/tcp_htcp.c#L2">2</a> <b><i> * H-TCP congestion control. The algorithm is detailed in:</i></b>
  <a name="L3" href="source/net/ipv4/tcp_htcp.c#L3">3</a> <b><i> * R.N.Shorten, D.J.Leith:</i></b>
  <a name="L4" href="source/net/ipv4/tcp_htcp.c#L4">4</a> <b><i> *   "H-TCP: TCP for high-speed and long-distance networks"</i></b>
  <a name="L5" href="source/net/ipv4/tcp_htcp.c#L5">5</a> <b><i> *   Proc. PFLDnet, Argonne, 2004.</i></b>
  <a name="L6" href="source/net/ipv4/tcp_htcp.c#L6">6</a> <b><i> * <a href="http://www.hamilton.ie/net/htcp3.pdf">http://www.hamilton.ie/net/htcp3.pdf</a></i></b>
  <a name="L7" href="source/net/ipv4/tcp_htcp.c#L7">7</a> <b><i> */</i></b>
  <a name="L8" href="source/net/ipv4/tcp_htcp.c#L8">8</a> 
  <a name="L9" href="source/net/ipv4/tcp_htcp.c#L9">9</a> #include &lt;linux/mm.h&gt;
 <a name="L10" href="source/net/ipv4/tcp_htcp.c#L10">10</a> #include &lt;linux/module.h&gt;
 <a name="L11" href="source/net/ipv4/tcp_htcp.c#L11">11</a> #include &lt;net/tcp.h&gt;
 <a name="L12" href="source/net/ipv4/tcp_htcp.c#L12">12</a> 
 <a name="L13" href="source/net/ipv4/tcp_htcp.c#L13">13</a> #define <a href="ident?i=ALPHA_BASE">ALPHA_BASE</a>      (1&lt;&lt;7)  <b><i>/* 1.0 with shift &lt;&lt; 7 */</i></b>
 <a name="L14" href="source/net/ipv4/tcp_htcp.c#L14">14</a> #define <a href="ident?i=BETA_MIN">BETA_MIN</a>        (1&lt;&lt;6)  <b><i>/* 0.5 with shift &lt;&lt; 7 */</i></b>
 <a name="L15" href="source/net/ipv4/tcp_htcp.c#L15">15</a> #define <a href="ident?i=BETA_MAX">BETA_MAX</a>        102     <b><i>/* 0.8 with shift &lt;&lt; 7 */</i></b>
 <a name="L16" href="source/net/ipv4/tcp_htcp.c#L16">16</a> 
 <a name="L17" href="source/net/ipv4/tcp_htcp.c#L17">17</a> static int use_rtt_scaling <a href="ident?i=__read_mostly">__read_mostly</a> = 1;
 <a name="L18" href="source/net/ipv4/tcp_htcp.c#L18">18</a> <a href="ident?i=module_param">module_param</a>(use_rtt_scaling, int, 0644);
 <a name="L19" href="source/net/ipv4/tcp_htcp.c#L19">19</a> <a href="ident?i=MODULE_PARM_DESC">MODULE_PARM_DESC</a>(use_rtt_scaling, <i>"turn on/off RTT scaling"</i>);
 <a name="L20" href="source/net/ipv4/tcp_htcp.c#L20">20</a> 
 <a name="L21" href="source/net/ipv4/tcp_htcp.c#L21">21</a> static int use_bandwidth_switch <a href="ident?i=__read_mostly">__read_mostly</a> = 1;
 <a name="L22" href="source/net/ipv4/tcp_htcp.c#L22">22</a> <a href="ident?i=module_param">module_param</a>(use_bandwidth_switch, int, 0644);
 <a name="L23" href="source/net/ipv4/tcp_htcp.c#L23">23</a> <a href="ident?i=MODULE_PARM_DESC">MODULE_PARM_DESC</a>(use_bandwidth_switch, <i>"turn on/off bandwidth switcher"</i>);
 <a name="L24" href="source/net/ipv4/tcp_htcp.c#L24">24</a> 
 <a name="L25" href="source/net/ipv4/tcp_htcp.c#L25">25</a> struct <a href="ident?i=htcp">htcp</a> {
 <a name="L26" href="source/net/ipv4/tcp_htcp.c#L26">26</a>         <a href="ident?i=u32">u32</a>     <a href="ident?i=alpha">alpha</a>;          <b><i>/* Fixed point arith, &lt;&lt; 7 */</i></b>
 <a name="L27" href="source/net/ipv4/tcp_htcp.c#L27">27</a>         <a href="ident?i=u8">u8</a>      <a href="ident?i=beta">beta</a>;           <b><i>/* Fixed point arith, &lt;&lt; 7 */</i></b>
 <a name="L28" href="source/net/ipv4/tcp_htcp.c#L28">28</a>         <a href="ident?i=u8">u8</a>      modeswitch;     <b><i>/* Delay modeswitch</i></b>
 <a name="L29" href="source/net/ipv4/tcp_htcp.c#L29">29</a> <b><i>                                   until we had at least one congestion event */</i></b>
 <a name="L30" href="source/net/ipv4/tcp_htcp.c#L30">30</a>         <a href="ident?i=u16">u16</a>     pkts_acked;
 <a name="L31" href="source/net/ipv4/tcp_htcp.c#L31">31</a>         <a href="ident?i=u32">u32</a>     packetcount;
 <a name="L32" href="source/net/ipv4/tcp_htcp.c#L32">32</a>         <a href="ident?i=u32">u32</a>     minRTT;
 <a name="L33" href="source/net/ipv4/tcp_htcp.c#L33">33</a>         <a href="ident?i=u32">u32</a>     maxRTT;
 <a name="L34" href="source/net/ipv4/tcp_htcp.c#L34">34</a>         <a href="ident?i=u32">u32</a>     last_cong;      <b><i>/* Time since last congestion event end */</i></b>
 <a name="L35" href="source/net/ipv4/tcp_htcp.c#L35">35</a>         <a href="ident?i=u32">u32</a>     undo_last_cong;
 <a name="L36" href="source/net/ipv4/tcp_htcp.c#L36">36</a> 
 <a name="L37" href="source/net/ipv4/tcp_htcp.c#L37">37</a>         <a href="ident?i=u32">u32</a>     undo_maxRTT;
 <a name="L38" href="source/net/ipv4/tcp_htcp.c#L38">38</a>         <a href="ident?i=u32">u32</a>     undo_old_maxB;
 <a name="L39" href="source/net/ipv4/tcp_htcp.c#L39">39</a> 
 <a name="L40" href="source/net/ipv4/tcp_htcp.c#L40">40</a>         <b><i>/* Bandwidth estimation */</i></b>
 <a name="L41" href="source/net/ipv4/tcp_htcp.c#L41">41</a>         <a href="ident?i=u32">u32</a>     minB;
 <a name="L42" href="source/net/ipv4/tcp_htcp.c#L42">42</a>         <a href="ident?i=u32">u32</a>     maxB;
 <a name="L43" href="source/net/ipv4/tcp_htcp.c#L43">43</a>         <a href="ident?i=u32">u32</a>     old_maxB;
 <a name="L44" href="source/net/ipv4/tcp_htcp.c#L44">44</a>         <a href="ident?i=u32">u32</a>     Bi;
 <a name="L45" href="source/net/ipv4/tcp_htcp.c#L45">45</a>         <a href="ident?i=u32">u32</a>     lasttime;
 <a name="L46" href="source/net/ipv4/tcp_htcp.c#L46">46</a> };
 <a name="L47" href="source/net/ipv4/tcp_htcp.c#L47">47</a> 
 <a name="L48" href="source/net/ipv4/tcp_htcp.c#L48">48</a> static inline <a href="ident?i=u32">u32</a> <a href="ident?i=htcp_cong_time">htcp_cong_time</a>(const struct <a href="ident?i=htcp">htcp</a> *<a href="ident?i=ca">ca</a>)
 <a name="L49" href="source/net/ipv4/tcp_htcp.c#L49">49</a> {
 <a name="L50" href="source/net/ipv4/tcp_htcp.c#L50">50</a>         return <a href="ident?i=jiffies">jiffies</a> - <a href="ident?i=ca">ca</a>-&gt;last_cong;
 <a name="L51" href="source/net/ipv4/tcp_htcp.c#L51">51</a> }
 <a name="L52" href="source/net/ipv4/tcp_htcp.c#L52">52</a> 
 <a name="L53" href="source/net/ipv4/tcp_htcp.c#L53">53</a> static inline <a href="ident?i=u32">u32</a> <a href="ident?i=htcp_ccount">htcp_ccount</a>(const struct <a href="ident?i=htcp">htcp</a> *<a href="ident?i=ca">ca</a>)
 <a name="L54" href="source/net/ipv4/tcp_htcp.c#L54">54</a> {
 <a name="L55" href="source/net/ipv4/tcp_htcp.c#L55">55</a>         return <a href="ident?i=htcp_cong_time">htcp_cong_time</a>(<a href="ident?i=ca">ca</a>) / <a href="ident?i=ca">ca</a>-&gt;minRTT;
 <a name="L56" href="source/net/ipv4/tcp_htcp.c#L56">56</a> }
 <a name="L57" href="source/net/ipv4/tcp_htcp.c#L57">57</a> 
 <a name="L58" href="source/net/ipv4/tcp_htcp.c#L58">58</a> static inline void <a href="ident?i=htcp_reset">htcp_reset</a>(struct <a href="ident?i=htcp">htcp</a> *<a href="ident?i=ca">ca</a>)
 <a name="L59" href="source/net/ipv4/tcp_htcp.c#L59">59</a> {
 <a name="L60" href="source/net/ipv4/tcp_htcp.c#L60">60</a>         <a href="ident?i=ca">ca</a>-&gt;undo_last_cong = <a href="ident?i=ca">ca</a>-&gt;last_cong;
 <a name="L61" href="source/net/ipv4/tcp_htcp.c#L61">61</a>         <a href="ident?i=ca">ca</a>-&gt;undo_maxRTT = <a href="ident?i=ca">ca</a>-&gt;maxRTT;
 <a name="L62" href="source/net/ipv4/tcp_htcp.c#L62">62</a>         <a href="ident?i=ca">ca</a>-&gt;undo_old_maxB = <a href="ident?i=ca">ca</a>-&gt;old_maxB;
 <a name="L63" href="source/net/ipv4/tcp_htcp.c#L63">63</a> 
 <a name="L64" href="source/net/ipv4/tcp_htcp.c#L64">64</a>         <a href="ident?i=ca">ca</a>-&gt;last_cong = <a href="ident?i=jiffies">jiffies</a>;
 <a name="L65" href="source/net/ipv4/tcp_htcp.c#L65">65</a> }
 <a name="L66" href="source/net/ipv4/tcp_htcp.c#L66">66</a> 
 <a name="L67" href="source/net/ipv4/tcp_htcp.c#L67">67</a> static <a href="ident?i=u32">u32</a> <a href="ident?i=htcp_cwnd_undo">htcp_cwnd_undo</a>(struct <a href="ident?i=sock">sock</a> *sk)
 <a name="L68" href="source/net/ipv4/tcp_htcp.c#L68">68</a> {
 <a name="L69" href="source/net/ipv4/tcp_htcp.c#L69">69</a>         const struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
 <a name="L70" href="source/net/ipv4/tcp_htcp.c#L70">70</a>         struct <a href="ident?i=htcp">htcp</a> *<a href="ident?i=ca">ca</a> = <a href="ident?i=inet_csk_ca">inet_csk_ca</a>(sk);
 <a name="L71" href="source/net/ipv4/tcp_htcp.c#L71">71</a> 
 <a name="L72" href="source/net/ipv4/tcp_htcp.c#L72">72</a>         if (<a href="ident?i=ca">ca</a>-&gt;undo_last_cong) {
 <a name="L73" href="source/net/ipv4/tcp_htcp.c#L73">73</a>                 <a href="ident?i=ca">ca</a>-&gt;last_cong = <a href="ident?i=ca">ca</a>-&gt;undo_last_cong;
 <a name="L74" href="source/net/ipv4/tcp_htcp.c#L74">74</a>                 <a href="ident?i=ca">ca</a>-&gt;maxRTT = <a href="ident?i=ca">ca</a>-&gt;undo_maxRTT;
 <a name="L75" href="source/net/ipv4/tcp_htcp.c#L75">75</a>                 <a href="ident?i=ca">ca</a>-&gt;old_maxB = <a href="ident?i=ca">ca</a>-&gt;undo_old_maxB;
 <a name="L76" href="source/net/ipv4/tcp_htcp.c#L76">76</a>                 <a href="ident?i=ca">ca</a>-&gt;undo_last_cong = 0;
 <a name="L77" href="source/net/ipv4/tcp_htcp.c#L77">77</a>         }
 <a name="L78" href="source/net/ipv4/tcp_htcp.c#L78">78</a> 
 <a name="L79" href="source/net/ipv4/tcp_htcp.c#L79">79</a>         return <a href="ident?i=max">max</a>(<a href="ident?i=tp">tp</a>-&gt;snd_cwnd, (<a href="ident?i=tp">tp</a>-&gt;snd_ssthresh &lt;&lt; 7) / <a href="ident?i=ca">ca</a>-&gt;<a href="ident?i=beta">beta</a>);
 <a name="L80" href="source/net/ipv4/tcp_htcp.c#L80">80</a> }
 <a name="L81" href="source/net/ipv4/tcp_htcp.c#L81">81</a> 
 <a name="L82" href="source/net/ipv4/tcp_htcp.c#L82">82</a> static inline void <a href="ident?i=measure_rtt">measure_rtt</a>(struct <a href="ident?i=sock">sock</a> *sk, <a href="ident?i=u32">u32</a> srtt)
 <a name="L83" href="source/net/ipv4/tcp_htcp.c#L83">83</a> {
 <a name="L84" href="source/net/ipv4/tcp_htcp.c#L84">84</a>         const struct <a href="ident?i=inet_connection_sock">inet_connection_sock</a> *icsk = <a href="ident?i=inet_csk">inet_csk</a>(sk);
 <a name="L85" href="source/net/ipv4/tcp_htcp.c#L85">85</a>         struct <a href="ident?i=htcp">htcp</a> *<a href="ident?i=ca">ca</a> = <a href="ident?i=inet_csk_ca">inet_csk_ca</a>(sk);
 <a name="L86" href="source/net/ipv4/tcp_htcp.c#L86">86</a> 
 <a name="L87" href="source/net/ipv4/tcp_htcp.c#L87">87</a>         <b><i>/* keep track of minimum RTT seen so far, minRTT is zero at first */</i></b>
 <a name="L88" href="source/net/ipv4/tcp_htcp.c#L88">88</a>         if (<a href="ident?i=ca">ca</a>-&gt;minRTT &gt; srtt || !<a href="ident?i=ca">ca</a>-&gt;minRTT)
 <a name="L89" href="source/net/ipv4/tcp_htcp.c#L89">89</a>                 <a href="ident?i=ca">ca</a>-&gt;minRTT = srtt;
 <a name="L90" href="source/net/ipv4/tcp_htcp.c#L90">90</a> 
 <a name="L91" href="source/net/ipv4/tcp_htcp.c#L91">91</a>         <b><i>/* max RTT */</i></b>
 <a name="L92" href="source/net/ipv4/tcp_htcp.c#L92">92</a>         if (icsk-&gt;icsk_ca_state == TCP_CA_Open) {
 <a name="L93" href="source/net/ipv4/tcp_htcp.c#L93">93</a>                 if (<a href="ident?i=ca">ca</a>-&gt;maxRTT &lt; <a href="ident?i=ca">ca</a>-&gt;minRTT)
 <a name="L94" href="source/net/ipv4/tcp_htcp.c#L94">94</a>                         <a href="ident?i=ca">ca</a>-&gt;maxRTT = <a href="ident?i=ca">ca</a>-&gt;minRTT;
 <a name="L95" href="source/net/ipv4/tcp_htcp.c#L95">95</a>                 if (<a href="ident?i=ca">ca</a>-&gt;maxRTT &lt; srtt &amp;&amp;
 <a name="L96" href="source/net/ipv4/tcp_htcp.c#L96">96</a>                     srtt &lt;= <a href="ident?i=ca">ca</a>-&gt;maxRTT + <a href="ident?i=msecs_to_jiffies">msecs_to_jiffies</a>(20))
 <a name="L97" href="source/net/ipv4/tcp_htcp.c#L97">97</a>                         <a href="ident?i=ca">ca</a>-&gt;maxRTT = srtt;
 <a name="L98" href="source/net/ipv4/tcp_htcp.c#L98">98</a>         }
 <a name="L99" href="source/net/ipv4/tcp_htcp.c#L99">99</a> }
<a name="L100" href="source/net/ipv4/tcp_htcp.c#L100">100</a> 
<a name="L101" href="source/net/ipv4/tcp_htcp.c#L101">101</a> static void <a href="ident?i=measure_achieved_throughput">measure_achieved_throughput</a>(struct <a href="ident?i=sock">sock</a> *sk,
<a name="L102" href="source/net/ipv4/tcp_htcp.c#L102">102</a>                                         <a href="ident?i=u32">u32</a> pkts_acked, <a href="ident?i=s32">s32</a> rtt)
<a name="L103" href="source/net/ipv4/tcp_htcp.c#L103">103</a> {
<a name="L104" href="source/net/ipv4/tcp_htcp.c#L104">104</a>         const struct <a href="ident?i=inet_connection_sock">inet_connection_sock</a> *icsk = <a href="ident?i=inet_csk">inet_csk</a>(sk);
<a name="L105" href="source/net/ipv4/tcp_htcp.c#L105">105</a>         const struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L106" href="source/net/ipv4/tcp_htcp.c#L106">106</a>         struct <a href="ident?i=htcp">htcp</a> *<a href="ident?i=ca">ca</a> = <a href="ident?i=inet_csk_ca">inet_csk_ca</a>(sk);
<a name="L107" href="source/net/ipv4/tcp_htcp.c#L107">107</a>         <a href="ident?i=u32">u32</a> <a href="ident?i=now">now</a> = <a href="ident?i=tcp_time_stamp">tcp_time_stamp</a>;
<a name="L108" href="source/net/ipv4/tcp_htcp.c#L108">108</a> 
<a name="L109" href="source/net/ipv4/tcp_htcp.c#L109">109</a>         if (icsk-&gt;icsk_ca_state == TCP_CA_Open)
<a name="L110" href="source/net/ipv4/tcp_htcp.c#L110">110</a>                 <a href="ident?i=ca">ca</a>-&gt;pkts_acked = pkts_acked;
<a name="L111" href="source/net/ipv4/tcp_htcp.c#L111">111</a> 
<a name="L112" href="source/net/ipv4/tcp_htcp.c#L112">112</a>         if (rtt &gt; 0)
<a name="L113" href="source/net/ipv4/tcp_htcp.c#L113">113</a>                 <a href="ident?i=measure_rtt">measure_rtt</a>(sk, <a href="ident?i=usecs_to_jiffies">usecs_to_jiffies</a>(rtt));
<a name="L114" href="source/net/ipv4/tcp_htcp.c#L114">114</a> 
<a name="L115" href="source/net/ipv4/tcp_htcp.c#L115">115</a>         if (!use_bandwidth_switch)
<a name="L116" href="source/net/ipv4/tcp_htcp.c#L116">116</a>                 return;
<a name="L117" href="source/net/ipv4/tcp_htcp.c#L117">117</a> 
<a name="L118" href="source/net/ipv4/tcp_htcp.c#L118">118</a>         <b><i>/* achieved throughput calculations */</i></b>
<a name="L119" href="source/net/ipv4/tcp_htcp.c#L119">119</a>         if (!((1 &lt;&lt; icsk-&gt;icsk_ca_state) &amp; (<a href="ident?i=TCPF_CA_Open">TCPF_CA_Open</a> | <a href="ident?i=TCPF_CA_Disorder">TCPF_CA_Disorder</a>))) {
<a name="L120" href="source/net/ipv4/tcp_htcp.c#L120">120</a>                 <a href="ident?i=ca">ca</a>-&gt;packetcount = 0;
<a name="L121" href="source/net/ipv4/tcp_htcp.c#L121">121</a>                 <a href="ident?i=ca">ca</a>-&gt;lasttime = <a href="ident?i=now">now</a>;
<a name="L122" href="source/net/ipv4/tcp_htcp.c#L122">122</a>                 return;
<a name="L123" href="source/net/ipv4/tcp_htcp.c#L123">123</a>         }
<a name="L124" href="source/net/ipv4/tcp_htcp.c#L124">124</a> 
<a name="L125" href="source/net/ipv4/tcp_htcp.c#L125">125</a>         <a href="ident?i=ca">ca</a>-&gt;packetcount += pkts_acked;
<a name="L126" href="source/net/ipv4/tcp_htcp.c#L126">126</a> 
<a name="L127" href="source/net/ipv4/tcp_htcp.c#L127">127</a>         if (<a href="ident?i=ca">ca</a>-&gt;packetcount &gt;= <a href="ident?i=tp">tp</a>-&gt;snd_cwnd - (<a href="ident?i=ca">ca</a>-&gt;<a href="ident?i=alpha">alpha</a> &gt;&gt; 7 ? : 1) &amp;&amp;
<a name="L128" href="source/net/ipv4/tcp_htcp.c#L128">128</a>             <a href="ident?i=now">now</a> - <a href="ident?i=ca">ca</a>-&gt;lasttime &gt;= <a href="ident?i=ca">ca</a>-&gt;minRTT &amp;&amp;
<a name="L129" href="source/net/ipv4/tcp_htcp.c#L129">129</a>             <a href="ident?i=ca">ca</a>-&gt;minRTT &gt; 0) {
<a name="L130" href="source/net/ipv4/tcp_htcp.c#L130">130</a>                 <a href="ident?i=__u32">__u32</a> cur_Bi = <a href="ident?i=ca">ca</a>-&gt;packetcount * <a href="ident?i=HZ">HZ</a> / (<a href="ident?i=now">now</a> - <a href="ident?i=ca">ca</a>-&gt;lasttime);
<a name="L131" href="source/net/ipv4/tcp_htcp.c#L131">131</a> 
<a name="L132" href="source/net/ipv4/tcp_htcp.c#L132">132</a>                 if (<a href="ident?i=htcp_ccount">htcp_ccount</a>(<a href="ident?i=ca">ca</a>) &lt;= 3) {
<a name="L133" href="source/net/ipv4/tcp_htcp.c#L133">133</a>                         <b><i>/* just after backoff */</i></b>
<a name="L134" href="source/net/ipv4/tcp_htcp.c#L134">134</a>                         <a href="ident?i=ca">ca</a>-&gt;minB = <a href="ident?i=ca">ca</a>-&gt;maxB = <a href="ident?i=ca">ca</a>-&gt;Bi = cur_Bi;
<a name="L135" href="source/net/ipv4/tcp_htcp.c#L135">135</a>                 } else {
<a name="L136" href="source/net/ipv4/tcp_htcp.c#L136">136</a>                         <a href="ident?i=ca">ca</a>-&gt;Bi = (3 * <a href="ident?i=ca">ca</a>-&gt;Bi + cur_Bi) / 4;
<a name="L137" href="source/net/ipv4/tcp_htcp.c#L137">137</a>                         if (<a href="ident?i=ca">ca</a>-&gt;Bi &gt; <a href="ident?i=ca">ca</a>-&gt;maxB)
<a name="L138" href="source/net/ipv4/tcp_htcp.c#L138">138</a>                                 <a href="ident?i=ca">ca</a>-&gt;maxB = <a href="ident?i=ca">ca</a>-&gt;Bi;
<a name="L139" href="source/net/ipv4/tcp_htcp.c#L139">139</a>                         if (<a href="ident?i=ca">ca</a>-&gt;minB &gt; <a href="ident?i=ca">ca</a>-&gt;maxB)
<a name="L140" href="source/net/ipv4/tcp_htcp.c#L140">140</a>                                 <a href="ident?i=ca">ca</a>-&gt;minB = <a href="ident?i=ca">ca</a>-&gt;maxB;
<a name="L141" href="source/net/ipv4/tcp_htcp.c#L141">141</a>                 }
<a name="L142" href="source/net/ipv4/tcp_htcp.c#L142">142</a>                 <a href="ident?i=ca">ca</a>-&gt;packetcount = 0;
<a name="L143" href="source/net/ipv4/tcp_htcp.c#L143">143</a>                 <a href="ident?i=ca">ca</a>-&gt;lasttime = <a href="ident?i=now">now</a>;
<a name="L144" href="source/net/ipv4/tcp_htcp.c#L144">144</a>         }
<a name="L145" href="source/net/ipv4/tcp_htcp.c#L145">145</a> }
<a name="L146" href="source/net/ipv4/tcp_htcp.c#L146">146</a> 
<a name="L147" href="source/net/ipv4/tcp_htcp.c#L147">147</a> static inline void <a href="ident?i=htcp_beta_update">htcp_beta_update</a>(struct <a href="ident?i=htcp">htcp</a> *<a href="ident?i=ca">ca</a>, <a href="ident?i=u32">u32</a> minRTT, <a href="ident?i=u32">u32</a> maxRTT)
<a name="L148" href="source/net/ipv4/tcp_htcp.c#L148">148</a> {
<a name="L149" href="source/net/ipv4/tcp_htcp.c#L149">149</a>         if (use_bandwidth_switch) {
<a name="L150" href="source/net/ipv4/tcp_htcp.c#L150">150</a>                 <a href="ident?i=u32">u32</a> maxB = <a href="ident?i=ca">ca</a>-&gt;maxB;
<a name="L151" href="source/net/ipv4/tcp_htcp.c#L151">151</a>                 <a href="ident?i=u32">u32</a> old_maxB = <a href="ident?i=ca">ca</a>-&gt;old_maxB;
<a name="L152" href="source/net/ipv4/tcp_htcp.c#L152">152</a> 
<a name="L153" href="source/net/ipv4/tcp_htcp.c#L153">153</a>                 <a href="ident?i=ca">ca</a>-&gt;old_maxB = <a href="ident?i=ca">ca</a>-&gt;maxB;
<a name="L154" href="source/net/ipv4/tcp_htcp.c#L154">154</a>                 if (!<a href="ident?i=between">between</a>(5 * maxB, 4 * old_maxB, 6 * old_maxB)) {
<a name="L155" href="source/net/ipv4/tcp_htcp.c#L155">155</a>                         <a href="ident?i=ca">ca</a>-&gt;<a href="ident?i=beta">beta</a> = <a href="ident?i=BETA_MIN">BETA_MIN</a>;
<a name="L156" href="source/net/ipv4/tcp_htcp.c#L156">156</a>                         <a href="ident?i=ca">ca</a>-&gt;modeswitch = 0;
<a name="L157" href="source/net/ipv4/tcp_htcp.c#L157">157</a>                         return;
<a name="L158" href="source/net/ipv4/tcp_htcp.c#L158">158</a>                 }
<a name="L159" href="source/net/ipv4/tcp_htcp.c#L159">159</a>         }
<a name="L160" href="source/net/ipv4/tcp_htcp.c#L160">160</a> 
<a name="L161" href="source/net/ipv4/tcp_htcp.c#L161">161</a>         if (<a href="ident?i=ca">ca</a>-&gt;modeswitch &amp;&amp; minRTT &gt; <a href="ident?i=msecs_to_jiffies">msecs_to_jiffies</a>(10) &amp;&amp; maxRTT) {
<a name="L162" href="source/net/ipv4/tcp_htcp.c#L162">162</a>                 <a href="ident?i=ca">ca</a>-&gt;<a href="ident?i=beta">beta</a> = (minRTT &lt;&lt; 7) / maxRTT;
<a name="L163" href="source/net/ipv4/tcp_htcp.c#L163">163</a>                 if (<a href="ident?i=ca">ca</a>-&gt;<a href="ident?i=beta">beta</a> &lt; <a href="ident?i=BETA_MIN">BETA_MIN</a>)
<a name="L164" href="source/net/ipv4/tcp_htcp.c#L164">164</a>                         <a href="ident?i=ca">ca</a>-&gt;<a href="ident?i=beta">beta</a> = <a href="ident?i=BETA_MIN">BETA_MIN</a>;
<a name="L165" href="source/net/ipv4/tcp_htcp.c#L165">165</a>                 else if (<a href="ident?i=ca">ca</a>-&gt;<a href="ident?i=beta">beta</a> &gt; <a href="ident?i=BETA_MAX">BETA_MAX</a>)
<a name="L166" href="source/net/ipv4/tcp_htcp.c#L166">166</a>                         <a href="ident?i=ca">ca</a>-&gt;<a href="ident?i=beta">beta</a> = <a href="ident?i=BETA_MAX">BETA_MAX</a>;
<a name="L167" href="source/net/ipv4/tcp_htcp.c#L167">167</a>         } else {
<a name="L168" href="source/net/ipv4/tcp_htcp.c#L168">168</a>                 <a href="ident?i=ca">ca</a>-&gt;<a href="ident?i=beta">beta</a> = <a href="ident?i=BETA_MIN">BETA_MIN</a>;
<a name="L169" href="source/net/ipv4/tcp_htcp.c#L169">169</a>                 <a href="ident?i=ca">ca</a>-&gt;modeswitch = 1;
<a name="L170" href="source/net/ipv4/tcp_htcp.c#L170">170</a>         }
<a name="L171" href="source/net/ipv4/tcp_htcp.c#L171">171</a> }
<a name="L172" href="source/net/ipv4/tcp_htcp.c#L172">172</a> 
<a name="L173" href="source/net/ipv4/tcp_htcp.c#L173">173</a> static inline void <a href="ident?i=htcp_alpha_update">htcp_alpha_update</a>(struct <a href="ident?i=htcp">htcp</a> *<a href="ident?i=ca">ca</a>)
<a name="L174" href="source/net/ipv4/tcp_htcp.c#L174">174</a> {
<a name="L175" href="source/net/ipv4/tcp_htcp.c#L175">175</a>         <a href="ident?i=u32">u32</a> minRTT = <a href="ident?i=ca">ca</a>-&gt;minRTT;
<a name="L176" href="source/net/ipv4/tcp_htcp.c#L176">176</a>         <a href="ident?i=u32">u32</a> factor = 1;
<a name="L177" href="source/net/ipv4/tcp_htcp.c#L177">177</a>         <a href="ident?i=u32">u32</a> diff = <a href="ident?i=htcp_cong_time">htcp_cong_time</a>(<a href="ident?i=ca">ca</a>);
<a name="L178" href="source/net/ipv4/tcp_htcp.c#L178">178</a> 
<a name="L179" href="source/net/ipv4/tcp_htcp.c#L179">179</a>         if (diff &gt; <a href="ident?i=HZ">HZ</a>) {
<a name="L180" href="source/net/ipv4/tcp_htcp.c#L180">180</a>                 diff -= <a href="ident?i=HZ">HZ</a>;
<a name="L181" href="source/net/ipv4/tcp_htcp.c#L181">181</a>                 factor = 1 + (10 * diff + ((diff / 2) * (diff / 2) / <a href="ident?i=HZ">HZ</a>)) / <a href="ident?i=HZ">HZ</a>;
<a name="L182" href="source/net/ipv4/tcp_htcp.c#L182">182</a>         }
<a name="L183" href="source/net/ipv4/tcp_htcp.c#L183">183</a> 
<a name="L184" href="source/net/ipv4/tcp_htcp.c#L184">184</a>         if (use_rtt_scaling &amp;&amp; minRTT) {
<a name="L185" href="source/net/ipv4/tcp_htcp.c#L185">185</a>                 <a href="ident?i=u32">u32</a> <a href="ident?i=scale">scale</a> = (<a href="ident?i=HZ">HZ</a> &lt;&lt; 3) / (10 * minRTT);
<a name="L186" href="source/net/ipv4/tcp_htcp.c#L186">186</a> 
<a name="L187" href="source/net/ipv4/tcp_htcp.c#L187">187</a>                 <b><i>/* clamping ratio to interval [0.5,10]&lt;&lt;3 */</i></b>
<a name="L188" href="source/net/ipv4/tcp_htcp.c#L188">188</a>                 <a href="ident?i=scale">scale</a> = <a href="ident?i=min">min</a>(<a href="ident?i=max">max</a>(<a href="ident?i=scale">scale</a>, 1U &lt;&lt; 2), 10U &lt;&lt; 3);
<a name="L189" href="source/net/ipv4/tcp_htcp.c#L189">189</a>                 factor = (factor &lt;&lt; 3) / <a href="ident?i=scale">scale</a>;
<a name="L190" href="source/net/ipv4/tcp_htcp.c#L190">190</a>                 if (!factor)
<a name="L191" href="source/net/ipv4/tcp_htcp.c#L191">191</a>                         factor = 1;
<a name="L192" href="source/net/ipv4/tcp_htcp.c#L192">192</a>         }
<a name="L193" href="source/net/ipv4/tcp_htcp.c#L193">193</a> 
<a name="L194" href="source/net/ipv4/tcp_htcp.c#L194">194</a>         <a href="ident?i=ca">ca</a>-&gt;<a href="ident?i=alpha">alpha</a> = 2 * factor * ((1 &lt;&lt; 7) - <a href="ident?i=ca">ca</a>-&gt;<a href="ident?i=beta">beta</a>);
<a name="L195" href="source/net/ipv4/tcp_htcp.c#L195">195</a>         if (!<a href="ident?i=ca">ca</a>-&gt;<a href="ident?i=alpha">alpha</a>)
<a name="L196" href="source/net/ipv4/tcp_htcp.c#L196">196</a>                 <a href="ident?i=ca">ca</a>-&gt;<a href="ident?i=alpha">alpha</a> = <a href="ident?i=ALPHA_BASE">ALPHA_BASE</a>;
<a name="L197" href="source/net/ipv4/tcp_htcp.c#L197">197</a> }
<a name="L198" href="source/net/ipv4/tcp_htcp.c#L198">198</a> 
<a name="L199" href="source/net/ipv4/tcp_htcp.c#L199">199</a> <b><i>/*</i></b>
<a name="L200" href="source/net/ipv4/tcp_htcp.c#L200">200</a> <b><i> * After we have the rtt data to calculate beta, we'd still prefer to wait one</i></b>
<a name="L201" href="source/net/ipv4/tcp_htcp.c#L201">201</a> <b><i> * rtt before we adjust our beta to ensure we are working from a consistent</i></b>
<a name="L202" href="source/net/ipv4/tcp_htcp.c#L202">202</a> <b><i> * data.</i></b>
<a name="L203" href="source/net/ipv4/tcp_htcp.c#L203">203</a> <b><i> *</i></b>
<a name="L204" href="source/net/ipv4/tcp_htcp.c#L204">204</a> <b><i> * This function should be called when we hit a congestion event since only at</i></b>
<a name="L205" href="source/net/ipv4/tcp_htcp.c#L205">205</a> <b><i> * that point do we really have a real sense of maxRTT (the queues en route</i></b>
<a name="L206" href="source/net/ipv4/tcp_htcp.c#L206">206</a> <b><i> * were getting just too full now).</i></b>
<a name="L207" href="source/net/ipv4/tcp_htcp.c#L207">207</a> <b><i> */</i></b>
<a name="L208" href="source/net/ipv4/tcp_htcp.c#L208">208</a> static void <a href="ident?i=htcp_param_update">htcp_param_update</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L209" href="source/net/ipv4/tcp_htcp.c#L209">209</a> {
<a name="L210" href="source/net/ipv4/tcp_htcp.c#L210">210</a>         struct <a href="ident?i=htcp">htcp</a> *<a href="ident?i=ca">ca</a> = <a href="ident?i=inet_csk_ca">inet_csk_ca</a>(sk);
<a name="L211" href="source/net/ipv4/tcp_htcp.c#L211">211</a>         <a href="ident?i=u32">u32</a> minRTT = <a href="ident?i=ca">ca</a>-&gt;minRTT;
<a name="L212" href="source/net/ipv4/tcp_htcp.c#L212">212</a>         <a href="ident?i=u32">u32</a> maxRTT = <a href="ident?i=ca">ca</a>-&gt;maxRTT;
<a name="L213" href="source/net/ipv4/tcp_htcp.c#L213">213</a> 
<a name="L214" href="source/net/ipv4/tcp_htcp.c#L214">214</a>         <a href="ident?i=htcp_beta_update">htcp_beta_update</a>(<a href="ident?i=ca">ca</a>, minRTT, maxRTT);
<a name="L215" href="source/net/ipv4/tcp_htcp.c#L215">215</a>         <a href="ident?i=htcp_alpha_update">htcp_alpha_update</a>(<a href="ident?i=ca">ca</a>);
<a name="L216" href="source/net/ipv4/tcp_htcp.c#L216">216</a> 
<a name="L217" href="source/net/ipv4/tcp_htcp.c#L217">217</a>         <b><i>/* add slowly fading memory for maxRTT to accommodate routing changes */</i></b>
<a name="L218" href="source/net/ipv4/tcp_htcp.c#L218">218</a>         if (minRTT &gt; 0 &amp;&amp; maxRTT &gt; minRTT)
<a name="L219" href="source/net/ipv4/tcp_htcp.c#L219">219</a>                 <a href="ident?i=ca">ca</a>-&gt;maxRTT = minRTT + ((maxRTT - minRTT) * 95) / 100;
<a name="L220" href="source/net/ipv4/tcp_htcp.c#L220">220</a> }
<a name="L221" href="source/net/ipv4/tcp_htcp.c#L221">221</a> 
<a name="L222" href="source/net/ipv4/tcp_htcp.c#L222">222</a> static <a href="ident?i=u32">u32</a> <a href="ident?i=htcp_recalc_ssthresh">htcp_recalc_ssthresh</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L223" href="source/net/ipv4/tcp_htcp.c#L223">223</a> {
<a name="L224" href="source/net/ipv4/tcp_htcp.c#L224">224</a>         const struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L225" href="source/net/ipv4/tcp_htcp.c#L225">225</a>         const struct <a href="ident?i=htcp">htcp</a> *<a href="ident?i=ca">ca</a> = <a href="ident?i=inet_csk_ca">inet_csk_ca</a>(sk);
<a name="L226" href="source/net/ipv4/tcp_htcp.c#L226">226</a> 
<a name="L227" href="source/net/ipv4/tcp_htcp.c#L227">227</a>         <a href="ident?i=htcp_param_update">htcp_param_update</a>(sk);
<a name="L228" href="source/net/ipv4/tcp_htcp.c#L228">228</a>         return <a href="ident?i=max">max</a>((<a href="ident?i=tp">tp</a>-&gt;snd_cwnd * <a href="ident?i=ca">ca</a>-&gt;<a href="ident?i=beta">beta</a>) &gt;&gt; 7, 2U);
<a name="L229" href="source/net/ipv4/tcp_htcp.c#L229">229</a> }
<a name="L230" href="source/net/ipv4/tcp_htcp.c#L230">230</a> 
<a name="L231" href="source/net/ipv4/tcp_htcp.c#L231">231</a> static void <a href="ident?i=htcp_cong_avoid">htcp_cong_avoid</a>(struct <a href="ident?i=sock">sock</a> *sk, <a href="ident?i=u32">u32</a> ack, <a href="ident?i=u32">u32</a> acked)
<a name="L232" href="source/net/ipv4/tcp_htcp.c#L232">232</a> {
<a name="L233" href="source/net/ipv4/tcp_htcp.c#L233">233</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L234" href="source/net/ipv4/tcp_htcp.c#L234">234</a>         struct <a href="ident?i=htcp">htcp</a> *<a href="ident?i=ca">ca</a> = <a href="ident?i=inet_csk_ca">inet_csk_ca</a>(sk);
<a name="L235" href="source/net/ipv4/tcp_htcp.c#L235">235</a> 
<a name="L236" href="source/net/ipv4/tcp_htcp.c#L236">236</a>         if (!<a href="ident?i=tcp_is_cwnd_limited">tcp_is_cwnd_limited</a>(sk))
<a name="L237" href="source/net/ipv4/tcp_htcp.c#L237">237</a>                 return;
<a name="L238" href="source/net/ipv4/tcp_htcp.c#L238">238</a> 
<a name="L239" href="source/net/ipv4/tcp_htcp.c#L239">239</a>         if (<a href="ident?i=tp">tp</a>-&gt;snd_cwnd &lt;= <a href="ident?i=tp">tp</a>-&gt;snd_ssthresh)
<a name="L240" href="source/net/ipv4/tcp_htcp.c#L240">240</a>                 <a href="ident?i=tcp_slow_start">tcp_slow_start</a>(<a href="ident?i=tp">tp</a>, acked);
<a name="L241" href="source/net/ipv4/tcp_htcp.c#L241">241</a>         else {
<a name="L242" href="source/net/ipv4/tcp_htcp.c#L242">242</a>                 <b><i>/* In dangerous area, increase slowly.</i></b>
<a name="L243" href="source/net/ipv4/tcp_htcp.c#L243">243</a> <b><i>                 * In theory this is tp-&gt;snd_cwnd += alpha / tp-&gt;snd_cwnd</i></b>
<a name="L244" href="source/net/ipv4/tcp_htcp.c#L244">244</a> <b><i>                 */</i></b>
<a name="L245" href="source/net/ipv4/tcp_htcp.c#L245">245</a>                 if ((<a href="ident?i=tp">tp</a>-&gt;snd_cwnd_cnt * <a href="ident?i=ca">ca</a>-&gt;<a href="ident?i=alpha">alpha</a>)&gt;&gt;7 &gt;= <a href="ident?i=tp">tp</a>-&gt;snd_cwnd) {
<a name="L246" href="source/net/ipv4/tcp_htcp.c#L246">246</a>                         if (<a href="ident?i=tp">tp</a>-&gt;snd_cwnd &lt; <a href="ident?i=tp">tp</a>-&gt;snd_cwnd_clamp)
<a name="L247" href="source/net/ipv4/tcp_htcp.c#L247">247</a>                                 <a href="ident?i=tp">tp</a>-&gt;snd_cwnd++;
<a name="L248" href="source/net/ipv4/tcp_htcp.c#L248">248</a>                         <a href="ident?i=tp">tp</a>-&gt;snd_cwnd_cnt = 0;
<a name="L249" href="source/net/ipv4/tcp_htcp.c#L249">249</a>                         <a href="ident?i=htcp_alpha_update">htcp_alpha_update</a>(<a href="ident?i=ca">ca</a>);
<a name="L250" href="source/net/ipv4/tcp_htcp.c#L250">250</a>                 } else
<a name="L251" href="source/net/ipv4/tcp_htcp.c#L251">251</a>                         <a href="ident?i=tp">tp</a>-&gt;snd_cwnd_cnt += <a href="ident?i=ca">ca</a>-&gt;pkts_acked;
<a name="L252" href="source/net/ipv4/tcp_htcp.c#L252">252</a> 
<a name="L253" href="source/net/ipv4/tcp_htcp.c#L253">253</a>                 <a href="ident?i=ca">ca</a>-&gt;pkts_acked = 1;
<a name="L254" href="source/net/ipv4/tcp_htcp.c#L254">254</a>         }
<a name="L255" href="source/net/ipv4/tcp_htcp.c#L255">255</a> }
<a name="L256" href="source/net/ipv4/tcp_htcp.c#L256">256</a> 
<a name="L257" href="source/net/ipv4/tcp_htcp.c#L257">257</a> static void <a href="ident?i=htcp_init">htcp_init</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L258" href="source/net/ipv4/tcp_htcp.c#L258">258</a> {
<a name="L259" href="source/net/ipv4/tcp_htcp.c#L259">259</a>         struct <a href="ident?i=htcp">htcp</a> *<a href="ident?i=ca">ca</a> = <a href="ident?i=inet_csk_ca">inet_csk_ca</a>(sk);
<a name="L260" href="source/net/ipv4/tcp_htcp.c#L260">260</a> 
<a name="L261" href="source/net/ipv4/tcp_htcp.c#L261">261</a>         <a href="ident?i=memset">memset</a>(<a href="ident?i=ca">ca</a>, 0, sizeof(struct <a href="ident?i=htcp">htcp</a>));
<a name="L262" href="source/net/ipv4/tcp_htcp.c#L262">262</a>         <a href="ident?i=ca">ca</a>-&gt;<a href="ident?i=alpha">alpha</a> = <a href="ident?i=ALPHA_BASE">ALPHA_BASE</a>;
<a name="L263" href="source/net/ipv4/tcp_htcp.c#L263">263</a>         <a href="ident?i=ca">ca</a>-&gt;<a href="ident?i=beta">beta</a> = <a href="ident?i=BETA_MIN">BETA_MIN</a>;
<a name="L264" href="source/net/ipv4/tcp_htcp.c#L264">264</a>         <a href="ident?i=ca">ca</a>-&gt;pkts_acked = 1;
<a name="L265" href="source/net/ipv4/tcp_htcp.c#L265">265</a>         <a href="ident?i=ca">ca</a>-&gt;last_cong = <a href="ident?i=jiffies">jiffies</a>;
<a name="L266" href="source/net/ipv4/tcp_htcp.c#L266">266</a> }
<a name="L267" href="source/net/ipv4/tcp_htcp.c#L267">267</a> 
<a name="L268" href="source/net/ipv4/tcp_htcp.c#L268">268</a> static void <a href="ident?i=htcp_state">htcp_state</a>(struct <a href="ident?i=sock">sock</a> *sk, <a href="ident?i=u8">u8</a> <a href="ident?i=new_state">new_state</a>)
<a name="L269" href="source/net/ipv4/tcp_htcp.c#L269">269</a> {
<a name="L270" href="source/net/ipv4/tcp_htcp.c#L270">270</a>         switch (<a href="ident?i=new_state">new_state</a>) {
<a name="L271" href="source/net/ipv4/tcp_htcp.c#L271">271</a>         case TCP_CA_Open:
<a name="L272" href="source/net/ipv4/tcp_htcp.c#L272">272</a>                 {
<a name="L273" href="source/net/ipv4/tcp_htcp.c#L273">273</a>                         struct <a href="ident?i=htcp">htcp</a> *<a href="ident?i=ca">ca</a> = <a href="ident?i=inet_csk_ca">inet_csk_ca</a>(sk);
<a name="L274" href="source/net/ipv4/tcp_htcp.c#L274">274</a> 
<a name="L275" href="source/net/ipv4/tcp_htcp.c#L275">275</a>                         if (<a href="ident?i=ca">ca</a>-&gt;undo_last_cong) {
<a name="L276" href="source/net/ipv4/tcp_htcp.c#L276">276</a>                                 <a href="ident?i=ca">ca</a>-&gt;last_cong = <a href="ident?i=jiffies">jiffies</a>;
<a name="L277" href="source/net/ipv4/tcp_htcp.c#L277">277</a>                                 <a href="ident?i=ca">ca</a>-&gt;undo_last_cong = 0;
<a name="L278" href="source/net/ipv4/tcp_htcp.c#L278">278</a>                         }
<a name="L279" href="source/net/ipv4/tcp_htcp.c#L279">279</a>                 }
<a name="L280" href="source/net/ipv4/tcp_htcp.c#L280">280</a>                 break;
<a name="L281" href="source/net/ipv4/tcp_htcp.c#L281">281</a>         case TCP_CA_CWR:
<a name="L282" href="source/net/ipv4/tcp_htcp.c#L282">282</a>         case TCP_CA_Recovery:
<a name="L283" href="source/net/ipv4/tcp_htcp.c#L283">283</a>         case TCP_CA_Loss:
<a name="L284" href="source/net/ipv4/tcp_htcp.c#L284">284</a>                 <a href="ident?i=htcp_reset">htcp_reset</a>(<a href="ident?i=inet_csk_ca">inet_csk_ca</a>(sk));
<a name="L285" href="source/net/ipv4/tcp_htcp.c#L285">285</a>                 break;
<a name="L286" href="source/net/ipv4/tcp_htcp.c#L286">286</a>         }
<a name="L287" href="source/net/ipv4/tcp_htcp.c#L287">287</a> }
<a name="L288" href="source/net/ipv4/tcp_htcp.c#L288">288</a> 
<a name="L289" href="source/net/ipv4/tcp_htcp.c#L289">289</a> static struct <a href="ident?i=tcp_congestion_ops">tcp_congestion_ops</a> <a href="ident?i=htcp">htcp</a> <a href="ident?i=__read_mostly">__read_mostly</a> = {
<a name="L290" href="source/net/ipv4/tcp_htcp.c#L290">290</a>         .<a href="ident?i=init">init</a>           = <a href="ident?i=htcp_init">htcp_init</a>,
<a name="L291" href="source/net/ipv4/tcp_htcp.c#L291">291</a>         .ssthresh       = <a href="ident?i=htcp_recalc_ssthresh">htcp_recalc_ssthresh</a>,
<a name="L292" href="source/net/ipv4/tcp_htcp.c#L292">292</a>         .cong_avoid     = <a href="ident?i=htcp_cong_avoid">htcp_cong_avoid</a>,
<a name="L293" href="source/net/ipv4/tcp_htcp.c#L293">293</a>         .<a href="ident?i=set_state">set_state</a>      = <a href="ident?i=htcp_state">htcp_state</a>,
<a name="L294" href="source/net/ipv4/tcp_htcp.c#L294">294</a>         .undo_cwnd      = <a href="ident?i=htcp_cwnd_undo">htcp_cwnd_undo</a>,
<a name="L295" href="source/net/ipv4/tcp_htcp.c#L295">295</a>         .pkts_acked     = <a href="ident?i=measure_achieved_throughput">measure_achieved_throughput</a>,
<a name="L296" href="source/net/ipv4/tcp_htcp.c#L296">296</a>         .owner          = <a href="ident?i=THIS_MODULE">THIS_MODULE</a>,
<a name="L297" href="source/net/ipv4/tcp_htcp.c#L297">297</a>         .<a href="ident?i=name">name</a>           = <i>"htcp"</i>,
<a name="L298" href="source/net/ipv4/tcp_htcp.c#L298">298</a> };
<a name="L299" href="source/net/ipv4/tcp_htcp.c#L299">299</a> 
<a name="L300" href="source/net/ipv4/tcp_htcp.c#L300">300</a> static int <a href="ident?i=__init">__init</a> <a href="ident?i=htcp_register">htcp_register</a>(void)
<a name="L301" href="source/net/ipv4/tcp_htcp.c#L301">301</a> {
<a name="L302" href="source/net/ipv4/tcp_htcp.c#L302">302</a>         <a href="ident?i=BUILD_BUG_ON">BUILD_BUG_ON</a>(sizeof(struct <a href="ident?i=htcp">htcp</a>) &gt; <a href="ident?i=ICSK_CA_PRIV_SIZE">ICSK_CA_PRIV_SIZE</a>);
<a name="L303" href="source/net/ipv4/tcp_htcp.c#L303">303</a>         <a href="ident?i=BUILD_BUG_ON">BUILD_BUG_ON</a>(<a href="ident?i=BETA_MIN">BETA_MIN</a> &gt;= <a href="ident?i=BETA_MAX">BETA_MAX</a>);
<a name="L304" href="source/net/ipv4/tcp_htcp.c#L304">304</a>         return <a href="ident?i=tcp_register_congestion_control">tcp_register_congestion_control</a>(&amp;<a href="ident?i=htcp">htcp</a>);
<a name="L305" href="source/net/ipv4/tcp_htcp.c#L305">305</a> }
<a name="L306" href="source/net/ipv4/tcp_htcp.c#L306">306</a> 
<a name="L307" href="source/net/ipv4/tcp_htcp.c#L307">307</a> static void <a href="ident?i=__exit">__exit</a> <a href="ident?i=htcp_unregister">htcp_unregister</a>(void)
<a name="L308" href="source/net/ipv4/tcp_htcp.c#L308">308</a> {
<a name="L309" href="source/net/ipv4/tcp_htcp.c#L309">309</a>         <a href="ident?i=tcp_unregister_congestion_control">tcp_unregister_congestion_control</a>(&amp;<a href="ident?i=htcp">htcp</a>);
<a name="L310" href="source/net/ipv4/tcp_htcp.c#L310">310</a> }
<a name="L311" href="source/net/ipv4/tcp_htcp.c#L311">311</a> 
<a name="L312" href="source/net/ipv4/tcp_htcp.c#L312">312</a> <a href="ident?i=module_init">module_init</a>(<a href="ident?i=htcp_register">htcp_register</a>);
<a name="L313" href="source/net/ipv4/tcp_htcp.c#L313">313</a> <a href="ident?i=module_exit">module_exit</a>(<a href="ident?i=htcp_unregister">htcp_unregister</a>);
<a name="L314" href="source/net/ipv4/tcp_htcp.c#L314">314</a> 
<a name="L315" href="source/net/ipv4/tcp_htcp.c#L315">315</a> <a href="ident?i=MODULE_AUTHOR">MODULE_AUTHOR</a>(<i>"Baruch Even"</i>);
<a name="L316" href="source/net/ipv4/tcp_htcp.c#L316">316</a> <a href="ident?i=MODULE_LICENSE">MODULE_LICENSE</a>(<i>"GPL"</i>);
<a name="L317" href="source/net/ipv4/tcp_htcp.c#L317">317</a> <a href="ident?i=MODULE_DESCRIPTION">MODULE_DESCRIPTION</a>(<i>"H-TCP"</i>);
<a name="L318" href="source/net/ipv4/tcp_htcp.c#L318">318</a> </pre></div><p>
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
