<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title>Linux/net/ipv4/tcp_cubic.c - Linux Cross Reference - Free Electrons</title>
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
		 &nbsp;&bull;&nbsp;<b><i>source navigation</i></b> &nbsp;&bull;&nbsp;<a href="diff/net/ipv4/tcp_cubic.c">diff markup</a> &nbsp;&bull;&nbsp;<a href="ident">identifier search</a> &nbsp;&bull;&nbsp;<a href="search">freetext search</a> &nbsp;&bull;&nbsp;
		</p>
	</div>
</div>

<div id="topbar">
  
  <p>Version: &nbsp;<a href="source/net/ipv4/tcp_cubic.c?v=2.0.40">2.0.40</a>&nbsp;<a href="source/net/ipv4/tcp_cubic.c?v=2.2.26">2.2.26</a>&nbsp;<a href="source/net/ipv4/tcp_cubic.c?v=2.4.37">2.4.37</a>&nbsp;<a href="source/net/ipv4/tcp_cubic.c?v=3.5">3.5</a>&nbsp;<a href="source/net/ipv4/tcp_cubic.c?v=3.6">3.6</a>&nbsp;<a href="source/net/ipv4/tcp_cubic.c?v=3.7">3.7</a>&nbsp;<a href="source/net/ipv4/tcp_cubic.c?v=3.8">3.8</a>&nbsp;<a href="source/net/ipv4/tcp_cubic.c?v=3.9">3.9</a>&nbsp;<a href="source/net/ipv4/tcp_cubic.c?v=3.10">3.10</a>&nbsp;<a href="source/net/ipv4/tcp_cubic.c?v=3.11">3.11</a>&nbsp;<a href="source/net/ipv4/tcp_cubic.c?v=3.12">3.12</a>&nbsp;<a href="source/net/ipv4/tcp_cubic.c?v=3.13">3.13</a>&nbsp;<a href="source/net/ipv4/tcp_cubic.c?v=3.14">3.14</a>&nbsp;<a href="source/net/ipv4/tcp_cubic.c?v=3.15">3.15</a>&nbsp;<a href="source/net/ipv4/tcp_cubic.c?v=3.16">3.16</a>&nbsp;<a href="source/net/ipv4/tcp_cubic.c?v=3.17">3.17</a>&nbsp;<a href="source/net/ipv4/tcp_cubic.c?v=3.18">3.18</a>&nbsp;<a href="source/net/ipv4/tcp_cubic.c?v=3.19">3.19</a>&nbsp;<a href="source/net/ipv4/tcp_cubic.c?v=4.0">4.0</a>&nbsp;<b><i>4.1</i></b></p>
  
</div>

<h1><a href="source/">Linux</a>/<a href="source/net/">net</a>/<a href="source/net/ipv4/">ipv4</a>/<a href="source/net/ipv4/tcp_cubic.c">tcp_cubic.c</a></h1>
<div id="lxrcode"><pre>  <a name="L1" href="source/net/ipv4/tcp_cubic.c#L1">1</a> <b><i>/*</i></b>
  <a name="L2" href="source/net/ipv4/tcp_cubic.c#L2">2</a> <b><i> * TCP CUBIC: Binary Increase Congestion control for TCP v2.3</i></b>
  <a name="L3" href="source/net/ipv4/tcp_cubic.c#L3">3</a> <b><i> * Home page:</i></b>
  <a name="L4" href="source/net/ipv4/tcp_cubic.c#L4">4</a> <b><i> *      <a href="http://netsrv.csc.ncsu.edu/twiki/bin/view/Main/BIC">http://netsrv.csc.ncsu.edu/twiki/bin/view/Main/BIC</a></i></b>
  <a name="L5" href="source/net/ipv4/tcp_cubic.c#L5">5</a> <b><i> * This is from the implementation of CUBIC TCP in</i></b>
  <a name="L6" href="source/net/ipv4/tcp_cubic.c#L6">6</a> <b><i> * Sangtae Ha, Injong Rhee and Lisong Xu,</i></b>
  <a name="L7" href="source/net/ipv4/tcp_cubic.c#L7">7</a> <b><i> *  "CUBIC: A New TCP-Friendly High-Speed TCP Variant"</i></b>
  <a name="L8" href="source/net/ipv4/tcp_cubic.c#L8">8</a> <b><i> *  in ACM SIGOPS Operating System Review, July 2008.</i></b>
  <a name="L9" href="source/net/ipv4/tcp_cubic.c#L9">9</a> <b><i> * Available from:</i></b>
 <a name="L10" href="source/net/ipv4/tcp_cubic.c#L10">10</a> <b><i> *  <a href="http://netsrv.csc.ncsu.edu/export/cubic_a_new_tcp_2008.pdf">http://netsrv.csc.ncsu.edu/export/cubic_a_new_tcp_2008.pdf</a></i></b>
 <a name="L11" href="source/net/ipv4/tcp_cubic.c#L11">11</a> <b><i> *</i></b>
 <a name="L12" href="source/net/ipv4/tcp_cubic.c#L12">12</a> <b><i> * CUBIC integrates a new slow start algorithm, called HyStart.</i></b>
 <a name="L13" href="source/net/ipv4/tcp_cubic.c#L13">13</a> <b><i> * The details of HyStart are presented in</i></b>
 <a name="L14" href="source/net/ipv4/tcp_cubic.c#L14">14</a> <b><i> *  Sangtae Ha and Injong Rhee,</i></b>
 <a name="L15" href="source/net/ipv4/tcp_cubic.c#L15">15</a> <b><i> *  "Taming the Elephants: New TCP Slow Start", NCSU TechReport 2008.</i></b>
 <a name="L16" href="source/net/ipv4/tcp_cubic.c#L16">16</a> <b><i> * Available from:</i></b>
 <a name="L17" href="source/net/ipv4/tcp_cubic.c#L17">17</a> <b><i> *  <a href="http://netsrv.csc.ncsu.edu/export/hystart_techreport_2008.pdf">http://netsrv.csc.ncsu.edu/export/hystart_techreport_2008.pdf</a></i></b>
 <a name="L18" href="source/net/ipv4/tcp_cubic.c#L18">18</a> <b><i> *</i></b>
 <a name="L19" href="source/net/ipv4/tcp_cubic.c#L19">19</a> <b><i> * All testing results are available from:</i></b>
 <a name="L20" href="source/net/ipv4/tcp_cubic.c#L20">20</a> <b><i> * <a href="http://netsrv.csc.ncsu.edu/wiki/index.php/TCP_Testing">http://netsrv.csc.ncsu.edu/wiki/index.php/TCP_Testing</a></i></b>
 <a name="L21" href="source/net/ipv4/tcp_cubic.c#L21">21</a> <b><i> *</i></b>
 <a name="L22" href="source/net/ipv4/tcp_cubic.c#L22">22</a> <b><i> * Unless CUBIC is enabled and congestion window is large</i></b>
 <a name="L23" href="source/net/ipv4/tcp_cubic.c#L23">23</a> <b><i> * this behaves the same as the original Reno.</i></b>
 <a name="L24" href="source/net/ipv4/tcp_cubic.c#L24">24</a> <b><i> */</i></b>
 <a name="L25" href="source/net/ipv4/tcp_cubic.c#L25">25</a> 
 <a name="L26" href="source/net/ipv4/tcp_cubic.c#L26">26</a> #include &lt;linux/mm.h&gt;
 <a name="L27" href="source/net/ipv4/tcp_cubic.c#L27">27</a> #include &lt;linux/module.h&gt;
 <a name="L28" href="source/net/ipv4/tcp_cubic.c#L28">28</a> #include &lt;linux/math64.h&gt;
 <a name="L29" href="source/net/ipv4/tcp_cubic.c#L29">29</a> #include &lt;net/tcp.h&gt;
 <a name="L30" href="source/net/ipv4/tcp_cubic.c#L30">30</a> 
 <a name="L31" href="source/net/ipv4/tcp_cubic.c#L31">31</a> #define <a href="ident?i=BICTCP_BETA_SCALE">BICTCP_BETA_SCALE</a>    1024       <b><i>/* Scale factor beta calculation</i></b>
 <a name="L32" href="source/net/ipv4/tcp_cubic.c#L32">32</a> <b><i>                                         * max_cwnd = snd_cwnd * beta</i></b>
 <a name="L33" href="source/net/ipv4/tcp_cubic.c#L33">33</a> <b><i>                                         */</i></b>
 <a name="L34" href="source/net/ipv4/tcp_cubic.c#L34">34</a> #define <a href="ident?i=BICTCP_HZ">BICTCP_HZ</a>               10      <b><i>/* BIC HZ 2^10 = 1024 */</i></b>
 <a name="L35" href="source/net/ipv4/tcp_cubic.c#L35">35</a> 
 <a name="L36" href="source/net/ipv4/tcp_cubic.c#L36">36</a> <b><i>/* Two methods of hybrid slow start */</i></b>
 <a name="L37" href="source/net/ipv4/tcp_cubic.c#L37">37</a> #define <a href="ident?i=HYSTART_ACK_TRAIN">HYSTART_ACK_TRAIN</a>       0x1
 <a name="L38" href="source/net/ipv4/tcp_cubic.c#L38">38</a> #define <a href="ident?i=HYSTART_DELAY">HYSTART_DELAY</a>           0x2
 <a name="L39" href="source/net/ipv4/tcp_cubic.c#L39">39</a> 
 <a name="L40" href="source/net/ipv4/tcp_cubic.c#L40">40</a> <b><i>/* Number of delay samples for detecting the increase of delay */</i></b>
 <a name="L41" href="source/net/ipv4/tcp_cubic.c#L41">41</a> #define <a href="ident?i=HYSTART_MIN_SAMPLES">HYSTART_MIN_SAMPLES</a>     8
 <a name="L42" href="source/net/ipv4/tcp_cubic.c#L42">42</a> #define <a href="ident?i=HYSTART_DELAY_MIN">HYSTART_DELAY_MIN</a>       (4U&lt;&lt;3)
 <a name="L43" href="source/net/ipv4/tcp_cubic.c#L43">43</a> #define <a href="ident?i=HYSTART_DELAY_MAX">HYSTART_DELAY_MAX</a>       (16U&lt;&lt;3)
 <a name="L44" href="source/net/ipv4/tcp_cubic.c#L44">44</a> #define <a href="ident?i=HYSTART_DELAY_THRESH">HYSTART_DELAY_THRESH</a>(<a href="ident?i=x">x</a>) <a href="ident?i=clamp">clamp</a>(<a href="ident?i=x">x</a>, <a href="ident?i=HYSTART_DELAY_MIN">HYSTART_DELAY_MIN</a>, <a href="ident?i=HYSTART_DELAY_MAX">HYSTART_DELAY_MAX</a>)
 <a name="L45" href="source/net/ipv4/tcp_cubic.c#L45">45</a> 
 <a name="L46" href="source/net/ipv4/tcp_cubic.c#L46">46</a> static int <a href="ident?i=fast_convergence">fast_convergence</a> <a href="ident?i=__read_mostly">__read_mostly</a> = 1;
 <a name="L47" href="source/net/ipv4/tcp_cubic.c#L47">47</a> static int <a href="ident?i=beta">beta</a> <a href="ident?i=__read_mostly">__read_mostly</a> = 717;    <b><i>/* = 717/1024 (BICTCP_BETA_SCALE) */</i></b>
 <a name="L48" href="source/net/ipv4/tcp_cubic.c#L48">48</a> static int <a href="ident?i=initial_ssthresh">initial_ssthresh</a> <a href="ident?i=__read_mostly">__read_mostly</a>;
 <a name="L49" href="source/net/ipv4/tcp_cubic.c#L49">49</a> static int bic_scale <a href="ident?i=__read_mostly">__read_mostly</a> = 41;
 <a name="L50" href="source/net/ipv4/tcp_cubic.c#L50">50</a> static int tcp_friendliness <a href="ident?i=__read_mostly">__read_mostly</a> = 1;
 <a name="L51" href="source/net/ipv4/tcp_cubic.c#L51">51</a> 
 <a name="L52" href="source/net/ipv4/tcp_cubic.c#L52">52</a> static int hystart <a href="ident?i=__read_mostly">__read_mostly</a> = 1;
 <a name="L53" href="source/net/ipv4/tcp_cubic.c#L53">53</a> static int hystart_detect <a href="ident?i=__read_mostly">__read_mostly</a> = <a href="ident?i=HYSTART_ACK_TRAIN">HYSTART_ACK_TRAIN</a> | <a href="ident?i=HYSTART_DELAY">HYSTART_DELAY</a>;
 <a name="L54" href="source/net/ipv4/tcp_cubic.c#L54">54</a> static int hystart_low_window <a href="ident?i=__read_mostly">__read_mostly</a> = 16;
 <a name="L55" href="source/net/ipv4/tcp_cubic.c#L55">55</a> static int hystart_ack_delta <a href="ident?i=__read_mostly">__read_mostly</a> = 2;
 <a name="L56" href="source/net/ipv4/tcp_cubic.c#L56">56</a> 
 <a name="L57" href="source/net/ipv4/tcp_cubic.c#L57">57</a> static <a href="ident?i=u32">u32</a> cube_rtt_scale <a href="ident?i=__read_mostly">__read_mostly</a>;
 <a name="L58" href="source/net/ipv4/tcp_cubic.c#L58">58</a> static <a href="ident?i=u32">u32</a> beta_scale <a href="ident?i=__read_mostly">__read_mostly</a>;
 <a name="L59" href="source/net/ipv4/tcp_cubic.c#L59">59</a> static <a href="ident?i=u64">u64</a> cube_factor <a href="ident?i=__read_mostly">__read_mostly</a>;
 <a name="L60" href="source/net/ipv4/tcp_cubic.c#L60">60</a> 
 <a name="L61" href="source/net/ipv4/tcp_cubic.c#L61">61</a> <b><i>/* Note parameters that are used for precomputing scale factors are read-only */</i></b>
 <a name="L62" href="source/net/ipv4/tcp_cubic.c#L62">62</a> <a href="ident?i=module_param">module_param</a>(<a href="ident?i=fast_convergence">fast_convergence</a>, int, 0644);
 <a name="L63" href="source/net/ipv4/tcp_cubic.c#L63">63</a> <a href="ident?i=MODULE_PARM_DESC">MODULE_PARM_DESC</a>(<a href="ident?i=fast_convergence">fast_convergence</a>, <i>"turn on/off fast convergence"</i>);
 <a name="L64" href="source/net/ipv4/tcp_cubic.c#L64">64</a> <a href="ident?i=module_param">module_param</a>(<a href="ident?i=beta">beta</a>, int, 0644);
 <a name="L65" href="source/net/ipv4/tcp_cubic.c#L65">65</a> <a href="ident?i=MODULE_PARM_DESC">MODULE_PARM_DESC</a>(<a href="ident?i=beta">beta</a>, <i>"beta for multiplicative increase"</i>);
 <a name="L66" href="source/net/ipv4/tcp_cubic.c#L66">66</a> <a href="ident?i=module_param">module_param</a>(<a href="ident?i=initial_ssthresh">initial_ssthresh</a>, int, 0644);
 <a name="L67" href="source/net/ipv4/tcp_cubic.c#L67">67</a> <a href="ident?i=MODULE_PARM_DESC">MODULE_PARM_DESC</a>(<a href="ident?i=initial_ssthresh">initial_ssthresh</a>, <i>"initial value of slow start threshold"</i>);
 <a name="L68" href="source/net/ipv4/tcp_cubic.c#L68">68</a> <a href="ident?i=module_param">module_param</a>(bic_scale, int, 0444);
 <a name="L69" href="source/net/ipv4/tcp_cubic.c#L69">69</a> <a href="ident?i=MODULE_PARM_DESC">MODULE_PARM_DESC</a>(bic_scale, <i>"scale (scaled by 1024) value for bic function (bic_scale/1024)"</i>);
 <a name="L70" href="source/net/ipv4/tcp_cubic.c#L70">70</a> <a href="ident?i=module_param">module_param</a>(tcp_friendliness, int, 0644);
 <a name="L71" href="source/net/ipv4/tcp_cubic.c#L71">71</a> <a href="ident?i=MODULE_PARM_DESC">MODULE_PARM_DESC</a>(tcp_friendliness, <i>"turn on/off tcp friendliness"</i>);
 <a name="L72" href="source/net/ipv4/tcp_cubic.c#L72">72</a> <a href="ident?i=module_param">module_param</a>(hystart, int, 0644);
 <a name="L73" href="source/net/ipv4/tcp_cubic.c#L73">73</a> <a href="ident?i=MODULE_PARM_DESC">MODULE_PARM_DESC</a>(hystart, <i>"turn on/off hybrid slow start algorithm"</i>);
 <a name="L74" href="source/net/ipv4/tcp_cubic.c#L74">74</a> <a href="ident?i=module_param">module_param</a>(hystart_detect, int, 0644);
 <a name="L75" href="source/net/ipv4/tcp_cubic.c#L75">75</a> <a href="ident?i=MODULE_PARM_DESC">MODULE_PARM_DESC</a>(hystart_detect, <i>"hyrbrid slow start detection mechanisms"</i>
 <a name="L76" href="source/net/ipv4/tcp_cubic.c#L76">76</a>                  <i>" 1: packet-train 2: delay 3: both packet-train and delay"</i>);
 <a name="L77" href="source/net/ipv4/tcp_cubic.c#L77">77</a> <a href="ident?i=module_param">module_param</a>(hystart_low_window, int, 0644);
 <a name="L78" href="source/net/ipv4/tcp_cubic.c#L78">78</a> <a href="ident?i=MODULE_PARM_DESC">MODULE_PARM_DESC</a>(hystart_low_window, <i>"lower bound cwnd for hybrid slow start"</i>);
 <a name="L79" href="source/net/ipv4/tcp_cubic.c#L79">79</a> <a href="ident?i=module_param">module_param</a>(hystart_ack_delta, int, 0644);
 <a name="L80" href="source/net/ipv4/tcp_cubic.c#L80">80</a> <a href="ident?i=MODULE_PARM_DESC">MODULE_PARM_DESC</a>(hystart_ack_delta, <i>"spacing between ack's indicating train (msecs)"</i>);
 <a name="L81" href="source/net/ipv4/tcp_cubic.c#L81">81</a> 
 <a name="L82" href="source/net/ipv4/tcp_cubic.c#L82">82</a> <b><i>/* BIC TCP Parameters */</i></b>
 <a name="L83" href="source/net/ipv4/tcp_cubic.c#L83">83</a> struct <a href="ident?i=bictcp">bictcp</a> {
 <a name="L84" href="source/net/ipv4/tcp_cubic.c#L84">84</a>         <a href="ident?i=u32">u32</a>     cnt;            <b><i>/* increase cwnd by 1 after ACKs */</i></b>
 <a name="L85" href="source/net/ipv4/tcp_cubic.c#L85">85</a>         <a href="ident?i=u32">u32</a>     last_max_cwnd;  <b><i>/* last maximum snd_cwnd */</i></b>
 <a name="L86" href="source/net/ipv4/tcp_cubic.c#L86">86</a>         <a href="ident?i=u32">u32</a>     loss_cwnd;      <b><i>/* congestion window at last loss */</i></b>
 <a name="L87" href="source/net/ipv4/tcp_cubic.c#L87">87</a>         <a href="ident?i=u32">u32</a>     last_cwnd;      <b><i>/* the last snd_cwnd */</i></b>
 <a name="L88" href="source/net/ipv4/tcp_cubic.c#L88">88</a>         <a href="ident?i=u32">u32</a>     <a href="ident?i=last_time">last_time</a>;      <b><i>/* time when updated last_cwnd */</i></b>
 <a name="L89" href="source/net/ipv4/tcp_cubic.c#L89">89</a>         <a href="ident?i=u32">u32</a>     bic_origin_point;<b><i>/* origin point of bic function */</i></b>
 <a name="L90" href="source/net/ipv4/tcp_cubic.c#L90">90</a>         <a href="ident?i=u32">u32</a>     bic_K;          <b><i>/* time to origin point</i></b>
 <a name="L91" href="source/net/ipv4/tcp_cubic.c#L91">91</a> <b><i>                                   from the beginning of the current epoch */</i></b>
 <a name="L92" href="source/net/ipv4/tcp_cubic.c#L92">92</a>         <a href="ident?i=u32">u32</a>     delay_min;      <b><i>/* min delay (msec &lt;&lt; 3) */</i></b>
 <a name="L93" href="source/net/ipv4/tcp_cubic.c#L93">93</a>         <a href="ident?i=u32">u32</a>     epoch_start;    <b><i>/* beginning of an epoch */</i></b>
 <a name="L94" href="source/net/ipv4/tcp_cubic.c#L94">94</a>         <a href="ident?i=u32">u32</a>     ack_cnt;        <b><i>/* number of acks */</i></b>
 <a name="L95" href="source/net/ipv4/tcp_cubic.c#L95">95</a>         <a href="ident?i=u32">u32</a>     tcp_cwnd;       <b><i>/* estimated tcp cwnd */</i></b>
 <a name="L96" href="source/net/ipv4/tcp_cubic.c#L96">96</a>         <a href="ident?i=u16">u16</a>     <a href="ident?i=unused">unused</a>;
 <a name="L97" href="source/net/ipv4/tcp_cubic.c#L97">97</a>         <a href="ident?i=u8">u8</a>      sample_cnt;     <b><i>/* number of samples to decide curr_rtt */</i></b>
 <a name="L98" href="source/net/ipv4/tcp_cubic.c#L98">98</a>         <a href="ident?i=u8">u8</a>      <a href="ident?i=found">found</a>;          <b><i>/* the exit point is found? */</i></b>
 <a name="L99" href="source/net/ipv4/tcp_cubic.c#L99">99</a>         <a href="ident?i=u32">u32</a>     round_start;    <b><i>/* beginning of each round */</i></b>
<a name="L100" href="source/net/ipv4/tcp_cubic.c#L100">100</a>         <a href="ident?i=u32">u32</a>     end_seq;        <b><i>/* end_seq of the round */</i></b>
<a name="L101" href="source/net/ipv4/tcp_cubic.c#L101">101</a>         <a href="ident?i=u32">u32</a>     last_ack;       <b><i>/* last time when the ACK spacing is close */</i></b>
<a name="L102" href="source/net/ipv4/tcp_cubic.c#L102">102</a>         <a href="ident?i=u32">u32</a>     curr_rtt;       <b><i>/* the minimum rtt of current round */</i></b>
<a name="L103" href="source/net/ipv4/tcp_cubic.c#L103">103</a> };
<a name="L104" href="source/net/ipv4/tcp_cubic.c#L104">104</a> 
<a name="L105" href="source/net/ipv4/tcp_cubic.c#L105">105</a> static inline void <a href="ident?i=bictcp_reset">bictcp_reset</a>(struct <a href="ident?i=bictcp">bictcp</a> *<a href="ident?i=ca">ca</a>)
<a name="L106" href="source/net/ipv4/tcp_cubic.c#L106">106</a> {
<a name="L107" href="source/net/ipv4/tcp_cubic.c#L107">107</a>         <a href="ident?i=ca">ca</a>-&gt;cnt = 0;
<a name="L108" href="source/net/ipv4/tcp_cubic.c#L108">108</a>         <a href="ident?i=ca">ca</a>-&gt;last_max_cwnd = 0;
<a name="L109" href="source/net/ipv4/tcp_cubic.c#L109">109</a>         <a href="ident?i=ca">ca</a>-&gt;last_cwnd = 0;
<a name="L110" href="source/net/ipv4/tcp_cubic.c#L110">110</a>         <a href="ident?i=ca">ca</a>-&gt;<a href="ident?i=last_time">last_time</a> = 0;
<a name="L111" href="source/net/ipv4/tcp_cubic.c#L111">111</a>         <a href="ident?i=ca">ca</a>-&gt;bic_origin_point = 0;
<a name="L112" href="source/net/ipv4/tcp_cubic.c#L112">112</a>         <a href="ident?i=ca">ca</a>-&gt;bic_K = 0;
<a name="L113" href="source/net/ipv4/tcp_cubic.c#L113">113</a>         <a href="ident?i=ca">ca</a>-&gt;delay_min = 0;
<a name="L114" href="source/net/ipv4/tcp_cubic.c#L114">114</a>         <a href="ident?i=ca">ca</a>-&gt;epoch_start = 0;
<a name="L115" href="source/net/ipv4/tcp_cubic.c#L115">115</a>         <a href="ident?i=ca">ca</a>-&gt;ack_cnt = 0;
<a name="L116" href="source/net/ipv4/tcp_cubic.c#L116">116</a>         <a href="ident?i=ca">ca</a>-&gt;tcp_cwnd = 0;
<a name="L117" href="source/net/ipv4/tcp_cubic.c#L117">117</a>         <a href="ident?i=ca">ca</a>-&gt;<a href="ident?i=found">found</a> = 0;
<a name="L118" href="source/net/ipv4/tcp_cubic.c#L118">118</a> }
<a name="L119" href="source/net/ipv4/tcp_cubic.c#L119">119</a> 
<a name="L120" href="source/net/ipv4/tcp_cubic.c#L120">120</a> static inline <a href="ident?i=u32">u32</a> <a href="ident?i=bictcp_clock">bictcp_clock</a>(void)
<a name="L121" href="source/net/ipv4/tcp_cubic.c#L121">121</a> {
<a name="L122" href="source/net/ipv4/tcp_cubic.c#L122">122</a> #if <a href="ident?i=HZ">HZ</a> &lt; 1000
<a name="L123" href="source/net/ipv4/tcp_cubic.c#L123">123</a>         return <a href="ident?i=ktime_to_ms">ktime_to_ms</a>(<a href="ident?i=ktime_get_real">ktime_get_real</a>());
<a name="L124" href="source/net/ipv4/tcp_cubic.c#L124">124</a> #else
<a name="L125" href="source/net/ipv4/tcp_cubic.c#L125">125</a>         return <a href="ident?i=jiffies_to_msecs">jiffies_to_msecs</a>(<a href="ident?i=jiffies">jiffies</a>);
<a name="L126" href="source/net/ipv4/tcp_cubic.c#L126">126</a> #endif
<a name="L127" href="source/net/ipv4/tcp_cubic.c#L127">127</a> }
<a name="L128" href="source/net/ipv4/tcp_cubic.c#L128">128</a> 
<a name="L129" href="source/net/ipv4/tcp_cubic.c#L129">129</a> static inline void <a href="ident?i=bictcp_hystart_reset">bictcp_hystart_reset</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L130" href="source/net/ipv4/tcp_cubic.c#L130">130</a> {
<a name="L131" href="source/net/ipv4/tcp_cubic.c#L131">131</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L132" href="source/net/ipv4/tcp_cubic.c#L132">132</a>         struct <a href="ident?i=bictcp">bictcp</a> *<a href="ident?i=ca">ca</a> = <a href="ident?i=inet_csk_ca">inet_csk_ca</a>(sk);
<a name="L133" href="source/net/ipv4/tcp_cubic.c#L133">133</a> 
<a name="L134" href="source/net/ipv4/tcp_cubic.c#L134">134</a>         <a href="ident?i=ca">ca</a>-&gt;round_start = <a href="ident?i=ca">ca</a>-&gt;last_ack = <a href="ident?i=bictcp_clock">bictcp_clock</a>();
<a name="L135" href="source/net/ipv4/tcp_cubic.c#L135">135</a>         <a href="ident?i=ca">ca</a>-&gt;end_seq = <a href="ident?i=tp">tp</a>-&gt;snd_nxt;
<a name="L136" href="source/net/ipv4/tcp_cubic.c#L136">136</a>         <a href="ident?i=ca">ca</a>-&gt;curr_rtt = 0;
<a name="L137" href="source/net/ipv4/tcp_cubic.c#L137">137</a>         <a href="ident?i=ca">ca</a>-&gt;sample_cnt = 0;
<a name="L138" href="source/net/ipv4/tcp_cubic.c#L138">138</a> }
<a name="L139" href="source/net/ipv4/tcp_cubic.c#L139">139</a> 
<a name="L140" href="source/net/ipv4/tcp_cubic.c#L140">140</a> static void <a href="ident?i=bictcp_init">bictcp_init</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L141" href="source/net/ipv4/tcp_cubic.c#L141">141</a> {
<a name="L142" href="source/net/ipv4/tcp_cubic.c#L142">142</a>         struct <a href="ident?i=bictcp">bictcp</a> *<a href="ident?i=ca">ca</a> = <a href="ident?i=inet_csk_ca">inet_csk_ca</a>(sk);
<a name="L143" href="source/net/ipv4/tcp_cubic.c#L143">143</a> 
<a name="L144" href="source/net/ipv4/tcp_cubic.c#L144">144</a>         <a href="ident?i=bictcp_reset">bictcp_reset</a>(<a href="ident?i=ca">ca</a>);
<a name="L145" href="source/net/ipv4/tcp_cubic.c#L145">145</a>         <a href="ident?i=ca">ca</a>-&gt;loss_cwnd = 0;
<a name="L146" href="source/net/ipv4/tcp_cubic.c#L146">146</a> 
<a name="L147" href="source/net/ipv4/tcp_cubic.c#L147">147</a>         if (hystart)
<a name="L148" href="source/net/ipv4/tcp_cubic.c#L148">148</a>                 <a href="ident?i=bictcp_hystart_reset">bictcp_hystart_reset</a>(sk);
<a name="L149" href="source/net/ipv4/tcp_cubic.c#L149">149</a> 
<a name="L150" href="source/net/ipv4/tcp_cubic.c#L150">150</a>         if (!hystart &amp;&amp; <a href="ident?i=initial_ssthresh">initial_ssthresh</a>)
<a name="L151" href="source/net/ipv4/tcp_cubic.c#L151">151</a>                 <a href="ident?i=tcp_sk">tcp_sk</a>(sk)-&gt;snd_ssthresh = <a href="ident?i=initial_ssthresh">initial_ssthresh</a>;
<a name="L152" href="source/net/ipv4/tcp_cubic.c#L152">152</a> }
<a name="L153" href="source/net/ipv4/tcp_cubic.c#L153">153</a> 
<a name="L154" href="source/net/ipv4/tcp_cubic.c#L154">154</a> <b><i>/* calculate the cubic root of x using a table lookup followed by one</i></b>
<a name="L155" href="source/net/ipv4/tcp_cubic.c#L155">155</a> <b><i> * Newton-Raphson iteration.</i></b>
<a name="L156" href="source/net/ipv4/tcp_cubic.c#L156">156</a> <b><i> * Avg err ~= 0.195%</i></b>
<a name="L157" href="source/net/ipv4/tcp_cubic.c#L157">157</a> <b><i> */</i></b>
<a name="L158" href="source/net/ipv4/tcp_cubic.c#L158">158</a> static <a href="ident?i=u32">u32</a> <a href="ident?i=cubic_root">cubic_root</a>(<a href="ident?i=u64">u64</a> <a href="ident?i=a">a</a>)
<a name="L159" href="source/net/ipv4/tcp_cubic.c#L159">159</a> {
<a name="L160" href="source/net/ipv4/tcp_cubic.c#L160">160</a>         <a href="ident?i=u32">u32</a> <a href="ident?i=x">x</a>, <a href="ident?i=b">b</a>, <a href="ident?i=shift">shift</a>;
<a name="L161" href="source/net/ipv4/tcp_cubic.c#L161">161</a>         <b><i>/*</i></b>
<a name="L162" href="source/net/ipv4/tcp_cubic.c#L162">162</a> <b><i>         * cbrt(x) MSB values for x MSB values in [0..63].</i></b>
<a name="L163" href="source/net/ipv4/tcp_cubic.c#L163">163</a> <b><i>         * Precomputed then refined by hand - Willy Tarreau</i></b>
<a name="L164" href="source/net/ipv4/tcp_cubic.c#L164">164</a> <b><i>         *</i></b>
<a name="L165" href="source/net/ipv4/tcp_cubic.c#L165">165</a> <b><i>         * For x in [0..63],</i></b>
<a name="L166" href="source/net/ipv4/tcp_cubic.c#L166">166</a> <b><i>         *   v = cbrt(x &lt;&lt; 18) - 1</i></b>
<a name="L167" href="source/net/ipv4/tcp_cubic.c#L167">167</a> <b><i>         *   cbrt(x) = (v[x] + 10) &gt;&gt; 6</i></b>
<a name="L168" href="source/net/ipv4/tcp_cubic.c#L168">168</a> <b><i>         */</i></b>
<a name="L169" href="source/net/ipv4/tcp_cubic.c#L169">169</a>         static const <a href="ident?i=u8">u8</a> <a href="ident?i=v">v</a>[] = {
<a name="L170" href="source/net/ipv4/tcp_cubic.c#L170">170</a>                 <b><i>/* 0x00 */</i></b>    0,   54,   54,   54,  118,  118,  118,  118,
<a name="L171" href="source/net/ipv4/tcp_cubic.c#L171">171</a>                 <b><i>/* 0x08 */</i></b>  123,  129,  134,  138,  143,  147,  151,  156,
<a name="L172" href="source/net/ipv4/tcp_cubic.c#L172">172</a>                 <b><i>/* 0x10 */</i></b>  157,  161,  164,  168,  170,  173,  176,  179,
<a name="L173" href="source/net/ipv4/tcp_cubic.c#L173">173</a>                 <b><i>/* 0x18 */</i></b>  181,  185,  187,  190,  192,  194,  197,  199,
<a name="L174" href="source/net/ipv4/tcp_cubic.c#L174">174</a>                 <b><i>/* 0x20 */</i></b>  200,  202,  204,  206,  209,  211,  213,  215,
<a name="L175" href="source/net/ipv4/tcp_cubic.c#L175">175</a>                 <b><i>/* 0x28 */</i></b>  217,  219,  221,  222,  224,  225,  227,  229,
<a name="L176" href="source/net/ipv4/tcp_cubic.c#L176">176</a>                 <b><i>/* 0x30 */</i></b>  231,  232,  234,  236,  237,  239,  240,  242,
<a name="L177" href="source/net/ipv4/tcp_cubic.c#L177">177</a>                 <b><i>/* 0x38 */</i></b>  244,  245,  246,  248,  250,  251,  252,  254,
<a name="L178" href="source/net/ipv4/tcp_cubic.c#L178">178</a>         };
<a name="L179" href="source/net/ipv4/tcp_cubic.c#L179">179</a> 
<a name="L180" href="source/net/ipv4/tcp_cubic.c#L180">180</a>         <a href="ident?i=b">b</a> = <a href="ident?i=fls64">fls64</a>(<a href="ident?i=a">a</a>);
<a name="L181" href="source/net/ipv4/tcp_cubic.c#L181">181</a>         if (<a href="ident?i=b">b</a> &lt; 7) {
<a name="L182" href="source/net/ipv4/tcp_cubic.c#L182">182</a>                 <b><i>/* a in [0..63] */</i></b>
<a name="L183" href="source/net/ipv4/tcp_cubic.c#L183">183</a>                 return ((<a href="ident?i=u32">u32</a>)<a href="ident?i=v">v</a>[(<a href="ident?i=u32">u32</a>)<a href="ident?i=a">a</a>] + 35) &gt;&gt; 6;
<a name="L184" href="source/net/ipv4/tcp_cubic.c#L184">184</a>         }
<a name="L185" href="source/net/ipv4/tcp_cubic.c#L185">185</a> 
<a name="L186" href="source/net/ipv4/tcp_cubic.c#L186">186</a>         <a href="ident?i=b">b</a> = ((<a href="ident?i=b">b</a> * 84) &gt;&gt; 8) - 1;
<a name="L187" href="source/net/ipv4/tcp_cubic.c#L187">187</a>         <a href="ident?i=shift">shift</a> = (<a href="ident?i=a">a</a> &gt;&gt; (<a href="ident?i=b">b</a> * 3));
<a name="L188" href="source/net/ipv4/tcp_cubic.c#L188">188</a> 
<a name="L189" href="source/net/ipv4/tcp_cubic.c#L189">189</a>         <a href="ident?i=x">x</a> = ((<a href="ident?i=u32">u32</a>)(((<a href="ident?i=u32">u32</a>)<a href="ident?i=v">v</a>[<a href="ident?i=shift">shift</a>] + 10) &lt;&lt; <a href="ident?i=b">b</a>)) &gt;&gt; 6;
<a name="L190" href="source/net/ipv4/tcp_cubic.c#L190">190</a> 
<a name="L191" href="source/net/ipv4/tcp_cubic.c#L191">191</a>         <b><i>/*</i></b>
<a name="L192" href="source/net/ipv4/tcp_cubic.c#L192">192</a> <b><i>         * Newton-Raphson iteration</i></b>
<a name="L193" href="source/net/ipv4/tcp_cubic.c#L193">193</a> <b><i>         *                         2</i></b>
<a name="L194" href="source/net/ipv4/tcp_cubic.c#L194">194</a> <b><i>         * x    = ( 2 * x  +  a / x  ) / 3</i></b>
<a name="L195" href="source/net/ipv4/tcp_cubic.c#L195">195</a> <b><i>         *  k+1          k         k</i></b>
<a name="L196" href="source/net/ipv4/tcp_cubic.c#L196">196</a> <b><i>         */</i></b>
<a name="L197" href="source/net/ipv4/tcp_cubic.c#L197">197</a>         <a href="ident?i=x">x</a> = (2 * <a href="ident?i=x">x</a> + (<a href="ident?i=u32">u32</a>)<a href="ident?i=div64_u64">div64_u64</a>(<a href="ident?i=a">a</a>, (<a href="ident?i=u64">u64</a>)<a href="ident?i=x">x</a> * (<a href="ident?i=u64">u64</a>)(<a href="ident?i=x">x</a> - 1)));
<a name="L198" href="source/net/ipv4/tcp_cubic.c#L198">198</a>         <a href="ident?i=x">x</a> = ((<a href="ident?i=x">x</a> * 341) &gt;&gt; 10);
<a name="L199" href="source/net/ipv4/tcp_cubic.c#L199">199</a>         return <a href="ident?i=x">x</a>;
<a name="L200" href="source/net/ipv4/tcp_cubic.c#L200">200</a> }
<a name="L201" href="source/net/ipv4/tcp_cubic.c#L201">201</a> 
<a name="L202" href="source/net/ipv4/tcp_cubic.c#L202">202</a> <b><i>/*</i></b>
<a name="L203" href="source/net/ipv4/tcp_cubic.c#L203">203</a> <b><i> * Compute congestion window to use.</i></b>
<a name="L204" href="source/net/ipv4/tcp_cubic.c#L204">204</a> <b><i> */</i></b>
<a name="L205" href="source/net/ipv4/tcp_cubic.c#L205">205</a> static inline void <a href="ident?i=bictcp_update">bictcp_update</a>(struct <a href="ident?i=bictcp">bictcp</a> *<a href="ident?i=ca">ca</a>, <a href="ident?i=u32">u32</a> cwnd, <a href="ident?i=u32">u32</a> acked)
<a name="L206" href="source/net/ipv4/tcp_cubic.c#L206">206</a> {
<a name="L207" href="source/net/ipv4/tcp_cubic.c#L207">207</a>         <a href="ident?i=u32">u32</a> <a href="ident?i=delta">delta</a>, bic_target, max_cnt;
<a name="L208" href="source/net/ipv4/tcp_cubic.c#L208">208</a>         <a href="ident?i=u64">u64</a> offs, <a href="ident?i=t">t</a>;
<a name="L209" href="source/net/ipv4/tcp_cubic.c#L209">209</a> 
<a name="L210" href="source/net/ipv4/tcp_cubic.c#L210">210</a>         <a href="ident?i=ca">ca</a>-&gt;ack_cnt += acked;   <b><i>/* count the number of ACKed packets */</i></b>
<a name="L211" href="source/net/ipv4/tcp_cubic.c#L211">211</a> 
<a name="L212" href="source/net/ipv4/tcp_cubic.c#L212">212</a>         if (<a href="ident?i=ca">ca</a>-&gt;last_cwnd == cwnd &amp;&amp;
<a name="L213" href="source/net/ipv4/tcp_cubic.c#L213">213</a>             (<a href="ident?i=s32">s32</a>)(<a href="ident?i=tcp_time_stamp">tcp_time_stamp</a> - <a href="ident?i=ca">ca</a>-&gt;<a href="ident?i=last_time">last_time</a>) &lt;= <a href="ident?i=HZ">HZ</a> / 32)
<a name="L214" href="source/net/ipv4/tcp_cubic.c#L214">214</a>                 return;
<a name="L215" href="source/net/ipv4/tcp_cubic.c#L215">215</a> 
<a name="L216" href="source/net/ipv4/tcp_cubic.c#L216">216</a>         <b><i>/* The CUBIC function can update ca-&gt;cnt at most once per jiffy.</i></b>
<a name="L217" href="source/net/ipv4/tcp_cubic.c#L217">217</a> <b><i>         * On all cwnd reduction events, ca-&gt;epoch_start is set to 0,</i></b>
<a name="L218" href="source/net/ipv4/tcp_cubic.c#L218">218</a> <b><i>         * which will force a recalculation of ca-&gt;cnt.</i></b>
<a name="L219" href="source/net/ipv4/tcp_cubic.c#L219">219</a> <b><i>         */</i></b>
<a name="L220" href="source/net/ipv4/tcp_cubic.c#L220">220</a>         if (<a href="ident?i=ca">ca</a>-&gt;epoch_start &amp;&amp; <a href="ident?i=tcp_time_stamp">tcp_time_stamp</a> == <a href="ident?i=ca">ca</a>-&gt;<a href="ident?i=last_time">last_time</a>)
<a name="L221" href="source/net/ipv4/tcp_cubic.c#L221">221</a>                 goto tcp_friendliness;
<a name="L222" href="source/net/ipv4/tcp_cubic.c#L222">222</a> 
<a name="L223" href="source/net/ipv4/tcp_cubic.c#L223">223</a>         <a href="ident?i=ca">ca</a>-&gt;last_cwnd = cwnd;
<a name="L224" href="source/net/ipv4/tcp_cubic.c#L224">224</a>         <a href="ident?i=ca">ca</a>-&gt;<a href="ident?i=last_time">last_time</a> = <a href="ident?i=tcp_time_stamp">tcp_time_stamp</a>;
<a name="L225" href="source/net/ipv4/tcp_cubic.c#L225">225</a> 
<a name="L226" href="source/net/ipv4/tcp_cubic.c#L226">226</a>         if (<a href="ident?i=ca">ca</a>-&gt;epoch_start == 0) {
<a name="L227" href="source/net/ipv4/tcp_cubic.c#L227">227</a>                 <a href="ident?i=ca">ca</a>-&gt;epoch_start = <a href="ident?i=tcp_time_stamp">tcp_time_stamp</a>;       <b><i>/* record beginning */</i></b>
<a name="L228" href="source/net/ipv4/tcp_cubic.c#L228">228</a>                 <a href="ident?i=ca">ca</a>-&gt;ack_cnt = acked;                    <b><i>/* start counting */</i></b>
<a name="L229" href="source/net/ipv4/tcp_cubic.c#L229">229</a>                 <a href="ident?i=ca">ca</a>-&gt;tcp_cwnd = cwnd;                    <b><i>/* syn with cubic */</i></b>
<a name="L230" href="source/net/ipv4/tcp_cubic.c#L230">230</a> 
<a name="L231" href="source/net/ipv4/tcp_cubic.c#L231">231</a>                 if (<a href="ident?i=ca">ca</a>-&gt;last_max_cwnd &lt;= cwnd) {
<a name="L232" href="source/net/ipv4/tcp_cubic.c#L232">232</a>                         <a href="ident?i=ca">ca</a>-&gt;bic_K = 0;
<a name="L233" href="source/net/ipv4/tcp_cubic.c#L233">233</a>                         <a href="ident?i=ca">ca</a>-&gt;bic_origin_point = cwnd;
<a name="L234" href="source/net/ipv4/tcp_cubic.c#L234">234</a>                 } else {
<a name="L235" href="source/net/ipv4/tcp_cubic.c#L235">235</a>                         <b><i>/* Compute new K based on</i></b>
<a name="L236" href="source/net/ipv4/tcp_cubic.c#L236">236</a> <b><i>                         * (wmax-cwnd) * (srtt&gt;&gt;3 / HZ) / c * 2^(3*bictcp_HZ)</i></b>
<a name="L237" href="source/net/ipv4/tcp_cubic.c#L237">237</a> <b><i>                         */</i></b>
<a name="L238" href="source/net/ipv4/tcp_cubic.c#L238">238</a>                         <a href="ident?i=ca">ca</a>-&gt;bic_K = <a href="ident?i=cubic_root">cubic_root</a>(cube_factor
<a name="L239" href="source/net/ipv4/tcp_cubic.c#L239">239</a>                                                * (<a href="ident?i=ca">ca</a>-&gt;last_max_cwnd - cwnd));
<a name="L240" href="source/net/ipv4/tcp_cubic.c#L240">240</a>                         <a href="ident?i=ca">ca</a>-&gt;bic_origin_point = <a href="ident?i=ca">ca</a>-&gt;last_max_cwnd;
<a name="L241" href="source/net/ipv4/tcp_cubic.c#L241">241</a>                 }
<a name="L242" href="source/net/ipv4/tcp_cubic.c#L242">242</a>         }
<a name="L243" href="source/net/ipv4/tcp_cubic.c#L243">243</a> 
<a name="L244" href="source/net/ipv4/tcp_cubic.c#L244">244</a>         <b><i>/* cubic function - calc*/</i></b>
<a name="L245" href="source/net/ipv4/tcp_cubic.c#L245">245</a>         <b><i>/* calculate c * time^3 / rtt,</i></b>
<a name="L246" href="source/net/ipv4/tcp_cubic.c#L246">246</a> <b><i>         *  while considering overflow in calculation of time^3</i></b>
<a name="L247" href="source/net/ipv4/tcp_cubic.c#L247">247</a> <b><i>         * (so time^3 is done by using 64 bit)</i></b>
<a name="L248" href="source/net/ipv4/tcp_cubic.c#L248">248</a> <b><i>         * and without the support of division of 64bit numbers</i></b>
<a name="L249" href="source/net/ipv4/tcp_cubic.c#L249">249</a> <b><i>         * (so all divisions are done by using 32 bit)</i></b>
<a name="L250" href="source/net/ipv4/tcp_cubic.c#L250">250</a> <b><i>         *  also NOTE the unit of those veriables</i></b>
<a name="L251" href="source/net/ipv4/tcp_cubic.c#L251">251</a> <b><i>         *        time  = (t - K) / 2^bictcp_HZ</i></b>
<a name="L252" href="source/net/ipv4/tcp_cubic.c#L252">252</a> <b><i>         *        c = bic_scale &gt;&gt; 10</i></b>
<a name="L253" href="source/net/ipv4/tcp_cubic.c#L253">253</a> <b><i>         * rtt  = (srtt &gt;&gt; 3) / HZ</i></b>
<a name="L254" href="source/net/ipv4/tcp_cubic.c#L254">254</a> <b><i>         * !!! The following code does not have overflow problems,</i></b>
<a name="L255" href="source/net/ipv4/tcp_cubic.c#L255">255</a> <b><i>         * if the cwnd &lt; 1 million packets !!!</i></b>
<a name="L256" href="source/net/ipv4/tcp_cubic.c#L256">256</a> <b><i>         */</i></b>
<a name="L257" href="source/net/ipv4/tcp_cubic.c#L257">257</a> 
<a name="L258" href="source/net/ipv4/tcp_cubic.c#L258">258</a>         <a href="ident?i=t">t</a> = (<a href="ident?i=s32">s32</a>)(<a href="ident?i=tcp_time_stamp">tcp_time_stamp</a> - <a href="ident?i=ca">ca</a>-&gt;epoch_start);
<a name="L259" href="source/net/ipv4/tcp_cubic.c#L259">259</a>         <a href="ident?i=t">t</a> += <a href="ident?i=msecs_to_jiffies">msecs_to_jiffies</a>(<a href="ident?i=ca">ca</a>-&gt;delay_min &gt;&gt; 3);
<a name="L260" href="source/net/ipv4/tcp_cubic.c#L260">260</a>         <b><i>/* change the unit from HZ to bictcp_HZ */</i></b>
<a name="L261" href="source/net/ipv4/tcp_cubic.c#L261">261</a>         <a href="ident?i=t">t</a> &lt;&lt;= <a href="ident?i=BICTCP_HZ">BICTCP_HZ</a>;
<a name="L262" href="source/net/ipv4/tcp_cubic.c#L262">262</a>         <a href="ident?i=do_div">do_div</a>(<a href="ident?i=t">t</a>, <a href="ident?i=HZ">HZ</a>);
<a name="L263" href="source/net/ipv4/tcp_cubic.c#L263">263</a> 
<a name="L264" href="source/net/ipv4/tcp_cubic.c#L264">264</a>         if (<a href="ident?i=t">t</a> &lt; <a href="ident?i=ca">ca</a>-&gt;bic_K)              <b><i>/* t - K */</i></b>
<a name="L265" href="source/net/ipv4/tcp_cubic.c#L265">265</a>                 offs = <a href="ident?i=ca">ca</a>-&gt;bic_K - <a href="ident?i=t">t</a>;
<a name="L266" href="source/net/ipv4/tcp_cubic.c#L266">266</a>         else
<a name="L267" href="source/net/ipv4/tcp_cubic.c#L267">267</a>                 offs = <a href="ident?i=t">t</a> - <a href="ident?i=ca">ca</a>-&gt;bic_K;
<a name="L268" href="source/net/ipv4/tcp_cubic.c#L268">268</a> 
<a name="L269" href="source/net/ipv4/tcp_cubic.c#L269">269</a>         <b><i>/* c/rtt * (t-K)^3 */</i></b>
<a name="L270" href="source/net/ipv4/tcp_cubic.c#L270">270</a>         <a href="ident?i=delta">delta</a> = (cube_rtt_scale * offs * offs * offs) &gt;&gt; (10+3*<a href="ident?i=BICTCP_HZ">BICTCP_HZ</a>);
<a name="L271" href="source/net/ipv4/tcp_cubic.c#L271">271</a>         if (<a href="ident?i=t">t</a> &lt; <a href="ident?i=ca">ca</a>-&gt;bic_K)                            <b><i>/* below origin*/</i></b>
<a name="L272" href="source/net/ipv4/tcp_cubic.c#L272">272</a>                 bic_target = <a href="ident?i=ca">ca</a>-&gt;bic_origin_point - <a href="ident?i=delta">delta</a>;
<a name="L273" href="source/net/ipv4/tcp_cubic.c#L273">273</a>         else                                          <b><i>/* above origin*/</i></b>
<a name="L274" href="source/net/ipv4/tcp_cubic.c#L274">274</a>                 bic_target = <a href="ident?i=ca">ca</a>-&gt;bic_origin_point + <a href="ident?i=delta">delta</a>;
<a name="L275" href="source/net/ipv4/tcp_cubic.c#L275">275</a> 
<a name="L276" href="source/net/ipv4/tcp_cubic.c#L276">276</a>         <b><i>/* cubic function - calc bictcp_cnt*/</i></b>
<a name="L277" href="source/net/ipv4/tcp_cubic.c#L277">277</a>         if (bic_target &gt; cwnd) {
<a name="L278" href="source/net/ipv4/tcp_cubic.c#L278">278</a>                 <a href="ident?i=ca">ca</a>-&gt;cnt = cwnd / (bic_target - cwnd);
<a name="L279" href="source/net/ipv4/tcp_cubic.c#L279">279</a>         } else {
<a name="L280" href="source/net/ipv4/tcp_cubic.c#L280">280</a>                 <a href="ident?i=ca">ca</a>-&gt;cnt = 100 * cwnd;              <b><i>/* very small increment*/</i></b>
<a name="L281" href="source/net/ipv4/tcp_cubic.c#L281">281</a>         }
<a name="L282" href="source/net/ipv4/tcp_cubic.c#L282">282</a> 
<a name="L283" href="source/net/ipv4/tcp_cubic.c#L283">283</a>         <b><i>/*</i></b>
<a name="L284" href="source/net/ipv4/tcp_cubic.c#L284">284</a> <b><i>         * The initial growth of cubic function may be too conservative</i></b>
<a name="L285" href="source/net/ipv4/tcp_cubic.c#L285">285</a> <b><i>         * when the available bandwidth is still unknown.</i></b>
<a name="L286" href="source/net/ipv4/tcp_cubic.c#L286">286</a> <b><i>         */</i></b>
<a name="L287" href="source/net/ipv4/tcp_cubic.c#L287">287</a>         if (<a href="ident?i=ca">ca</a>-&gt;last_max_cwnd == 0 &amp;&amp; <a href="ident?i=ca">ca</a>-&gt;cnt &gt; 20)
<a name="L288" href="source/net/ipv4/tcp_cubic.c#L288">288</a>                 <a href="ident?i=ca">ca</a>-&gt;cnt = 20;   <b><i>/* increase cwnd 5% per RTT */</i></b>
<a name="L289" href="source/net/ipv4/tcp_cubic.c#L289">289</a> 
<a name="L290" href="source/net/ipv4/tcp_cubic.c#L290">290</a> tcp_friendliness:
<a name="L291" href="source/net/ipv4/tcp_cubic.c#L291">291</a>         <b><i>/* TCP Friendly */</i></b>
<a name="L292" href="source/net/ipv4/tcp_cubic.c#L292">292</a>         if (tcp_friendliness) {
<a name="L293" href="source/net/ipv4/tcp_cubic.c#L293">293</a>                 <a href="ident?i=u32">u32</a> <a href="ident?i=scale">scale</a> = beta_scale;
<a name="L294" href="source/net/ipv4/tcp_cubic.c#L294">294</a> 
<a name="L295" href="source/net/ipv4/tcp_cubic.c#L295">295</a>                 <a href="ident?i=delta">delta</a> = (cwnd * <a href="ident?i=scale">scale</a>) &gt;&gt; 3;
<a name="L296" href="source/net/ipv4/tcp_cubic.c#L296">296</a>                 while (<a href="ident?i=ca">ca</a>-&gt;ack_cnt &gt; <a href="ident?i=delta">delta</a>) {           <b><i>/* update tcp cwnd */</i></b>
<a name="L297" href="source/net/ipv4/tcp_cubic.c#L297">297</a>                         <a href="ident?i=ca">ca</a>-&gt;ack_cnt -= <a href="ident?i=delta">delta</a>;
<a name="L298" href="source/net/ipv4/tcp_cubic.c#L298">298</a>                         <a href="ident?i=ca">ca</a>-&gt;tcp_cwnd++;
<a name="L299" href="source/net/ipv4/tcp_cubic.c#L299">299</a>                 }
<a name="L300" href="source/net/ipv4/tcp_cubic.c#L300">300</a> 
<a name="L301" href="source/net/ipv4/tcp_cubic.c#L301">301</a>                 if (<a href="ident?i=ca">ca</a>-&gt;tcp_cwnd &gt; cwnd) {      <b><i>/* if bic is slower than tcp */</i></b>
<a name="L302" href="source/net/ipv4/tcp_cubic.c#L302">302</a>                         <a href="ident?i=delta">delta</a> = <a href="ident?i=ca">ca</a>-&gt;tcp_cwnd - cwnd;
<a name="L303" href="source/net/ipv4/tcp_cubic.c#L303">303</a>                         max_cnt = cwnd / <a href="ident?i=delta">delta</a>;
<a name="L304" href="source/net/ipv4/tcp_cubic.c#L304">304</a>                         if (<a href="ident?i=ca">ca</a>-&gt;cnt &gt; max_cnt)
<a name="L305" href="source/net/ipv4/tcp_cubic.c#L305">305</a>                                 <a href="ident?i=ca">ca</a>-&gt;cnt = max_cnt;
<a name="L306" href="source/net/ipv4/tcp_cubic.c#L306">306</a>                 }
<a name="L307" href="source/net/ipv4/tcp_cubic.c#L307">307</a>         }
<a name="L308" href="source/net/ipv4/tcp_cubic.c#L308">308</a> 
<a name="L309" href="source/net/ipv4/tcp_cubic.c#L309">309</a>         <b><i>/* The maximum rate of cwnd increase CUBIC allows is 1 packet per</i></b>
<a name="L310" href="source/net/ipv4/tcp_cubic.c#L310">310</a> <b><i>         * 2 packets ACKed, meaning cwnd grows at 1.5x per RTT.</i></b>
<a name="L311" href="source/net/ipv4/tcp_cubic.c#L311">311</a> <b><i>         */</i></b>
<a name="L312" href="source/net/ipv4/tcp_cubic.c#L312">312</a>         <a href="ident?i=ca">ca</a>-&gt;cnt = <a href="ident?i=max">max</a>(<a href="ident?i=ca">ca</a>-&gt;cnt, 2U);
<a name="L313" href="source/net/ipv4/tcp_cubic.c#L313">313</a> }
<a name="L314" href="source/net/ipv4/tcp_cubic.c#L314">314</a> 
<a name="L315" href="source/net/ipv4/tcp_cubic.c#L315">315</a> static void <a href="ident?i=bictcp_cong_avoid">bictcp_cong_avoid</a>(struct <a href="ident?i=sock">sock</a> *sk, <a href="ident?i=u32">u32</a> ack, <a href="ident?i=u32">u32</a> acked)
<a name="L316" href="source/net/ipv4/tcp_cubic.c#L316">316</a> {
<a name="L317" href="source/net/ipv4/tcp_cubic.c#L317">317</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L318" href="source/net/ipv4/tcp_cubic.c#L318">318</a>         struct <a href="ident?i=bictcp">bictcp</a> *<a href="ident?i=ca">ca</a> = <a href="ident?i=inet_csk_ca">inet_csk_ca</a>(sk);
<a name="L319" href="source/net/ipv4/tcp_cubic.c#L319">319</a> 
<a name="L320" href="source/net/ipv4/tcp_cubic.c#L320">320</a>         if (!<a href="ident?i=tcp_is_cwnd_limited">tcp_is_cwnd_limited</a>(sk))
<a name="L321" href="source/net/ipv4/tcp_cubic.c#L321">321</a>                 return;
<a name="L322" href="source/net/ipv4/tcp_cubic.c#L322">322</a> 
<a name="L323" href="source/net/ipv4/tcp_cubic.c#L323">323</a>         if (<a href="ident?i=tp">tp</a>-&gt;snd_cwnd &lt;= <a href="ident?i=tp">tp</a>-&gt;snd_ssthresh) {
<a name="L324" href="source/net/ipv4/tcp_cubic.c#L324">324</a>                 if (hystart &amp;&amp; <a href="ident?i=after">after</a>(ack, <a href="ident?i=ca">ca</a>-&gt;end_seq))
<a name="L325" href="source/net/ipv4/tcp_cubic.c#L325">325</a>                         <a href="ident?i=bictcp_hystart_reset">bictcp_hystart_reset</a>(sk);
<a name="L326" href="source/net/ipv4/tcp_cubic.c#L326">326</a>                 acked = <a href="ident?i=tcp_slow_start">tcp_slow_start</a>(<a href="ident?i=tp">tp</a>, acked);
<a name="L327" href="source/net/ipv4/tcp_cubic.c#L327">327</a>                 if (!acked)
<a name="L328" href="source/net/ipv4/tcp_cubic.c#L328">328</a>                         return;
<a name="L329" href="source/net/ipv4/tcp_cubic.c#L329">329</a>         }
<a name="L330" href="source/net/ipv4/tcp_cubic.c#L330">330</a>         <a href="ident?i=bictcp_update">bictcp_update</a>(<a href="ident?i=ca">ca</a>, <a href="ident?i=tp">tp</a>-&gt;snd_cwnd, acked);
<a name="L331" href="source/net/ipv4/tcp_cubic.c#L331">331</a>         <a href="ident?i=tcp_cong_avoid_ai">tcp_cong_avoid_ai</a>(<a href="ident?i=tp">tp</a>, <a href="ident?i=ca">ca</a>-&gt;cnt, acked);
<a name="L332" href="source/net/ipv4/tcp_cubic.c#L332">332</a> }
<a name="L333" href="source/net/ipv4/tcp_cubic.c#L333">333</a> 
<a name="L334" href="source/net/ipv4/tcp_cubic.c#L334">334</a> static <a href="ident?i=u32">u32</a> <a href="ident?i=bictcp_recalc_ssthresh">bictcp_recalc_ssthresh</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L335" href="source/net/ipv4/tcp_cubic.c#L335">335</a> {
<a name="L336" href="source/net/ipv4/tcp_cubic.c#L336">336</a>         const struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L337" href="source/net/ipv4/tcp_cubic.c#L337">337</a>         struct <a href="ident?i=bictcp">bictcp</a> *<a href="ident?i=ca">ca</a> = <a href="ident?i=inet_csk_ca">inet_csk_ca</a>(sk);
<a name="L338" href="source/net/ipv4/tcp_cubic.c#L338">338</a> 
<a name="L339" href="source/net/ipv4/tcp_cubic.c#L339">339</a>         <a href="ident?i=ca">ca</a>-&gt;epoch_start = 0;    <b><i>/* end of epoch */</i></b>
<a name="L340" href="source/net/ipv4/tcp_cubic.c#L340">340</a> 
<a name="L341" href="source/net/ipv4/tcp_cubic.c#L341">341</a>         <b><i>/* Wmax and fast convergence */</i></b>
<a name="L342" href="source/net/ipv4/tcp_cubic.c#L342">342</a>         if (<a href="ident?i=tp">tp</a>-&gt;snd_cwnd &lt; <a href="ident?i=ca">ca</a>-&gt;last_max_cwnd &amp;&amp; <a href="ident?i=fast_convergence">fast_convergence</a>)
<a name="L343" href="source/net/ipv4/tcp_cubic.c#L343">343</a>                 <a href="ident?i=ca">ca</a>-&gt;last_max_cwnd = (<a href="ident?i=tp">tp</a>-&gt;snd_cwnd * (<a href="ident?i=BICTCP_BETA_SCALE">BICTCP_BETA_SCALE</a> + <a href="ident?i=beta">beta</a>))
<a name="L344" href="source/net/ipv4/tcp_cubic.c#L344">344</a>                         / (2 * <a href="ident?i=BICTCP_BETA_SCALE">BICTCP_BETA_SCALE</a>);
<a name="L345" href="source/net/ipv4/tcp_cubic.c#L345">345</a>         else
<a name="L346" href="source/net/ipv4/tcp_cubic.c#L346">346</a>                 <a href="ident?i=ca">ca</a>-&gt;last_max_cwnd = <a href="ident?i=tp">tp</a>-&gt;snd_cwnd;
<a name="L347" href="source/net/ipv4/tcp_cubic.c#L347">347</a> 
<a name="L348" href="source/net/ipv4/tcp_cubic.c#L348">348</a>         <a href="ident?i=ca">ca</a>-&gt;loss_cwnd = <a href="ident?i=tp">tp</a>-&gt;snd_cwnd;
<a name="L349" href="source/net/ipv4/tcp_cubic.c#L349">349</a> 
<a name="L350" href="source/net/ipv4/tcp_cubic.c#L350">350</a>         return <a href="ident?i=max">max</a>((<a href="ident?i=tp">tp</a>-&gt;snd_cwnd * <a href="ident?i=beta">beta</a>) / <a href="ident?i=BICTCP_BETA_SCALE">BICTCP_BETA_SCALE</a>, 2U);
<a name="L351" href="source/net/ipv4/tcp_cubic.c#L351">351</a> }
<a name="L352" href="source/net/ipv4/tcp_cubic.c#L352">352</a> 
<a name="L353" href="source/net/ipv4/tcp_cubic.c#L353">353</a> static <a href="ident?i=u32">u32</a> <a href="ident?i=bictcp_undo_cwnd">bictcp_undo_cwnd</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L354" href="source/net/ipv4/tcp_cubic.c#L354">354</a> {
<a name="L355" href="source/net/ipv4/tcp_cubic.c#L355">355</a>         struct <a href="ident?i=bictcp">bictcp</a> *<a href="ident?i=ca">ca</a> = <a href="ident?i=inet_csk_ca">inet_csk_ca</a>(sk);
<a name="L356" href="source/net/ipv4/tcp_cubic.c#L356">356</a> 
<a name="L357" href="source/net/ipv4/tcp_cubic.c#L357">357</a>         return <a href="ident?i=max">max</a>(<a href="ident?i=tcp_sk">tcp_sk</a>(sk)-&gt;snd_cwnd, <a href="ident?i=ca">ca</a>-&gt;loss_cwnd);
<a name="L358" href="source/net/ipv4/tcp_cubic.c#L358">358</a> }
<a name="L359" href="source/net/ipv4/tcp_cubic.c#L359">359</a> 
<a name="L360" href="source/net/ipv4/tcp_cubic.c#L360">360</a> static void <a href="ident?i=bictcp_state">bictcp_state</a>(struct <a href="ident?i=sock">sock</a> *sk, <a href="ident?i=u8">u8</a> <a href="ident?i=new_state">new_state</a>)
<a name="L361" href="source/net/ipv4/tcp_cubic.c#L361">361</a> {
<a name="L362" href="source/net/ipv4/tcp_cubic.c#L362">362</a>         if (<a href="ident?i=new_state">new_state</a> == TCP_CA_Loss) {
<a name="L363" href="source/net/ipv4/tcp_cubic.c#L363">363</a>                 <a href="ident?i=bictcp_reset">bictcp_reset</a>(<a href="ident?i=inet_csk_ca">inet_csk_ca</a>(sk));
<a name="L364" href="source/net/ipv4/tcp_cubic.c#L364">364</a>                 <a href="ident?i=bictcp_hystart_reset">bictcp_hystart_reset</a>(sk);
<a name="L365" href="source/net/ipv4/tcp_cubic.c#L365">365</a>         }
<a name="L366" href="source/net/ipv4/tcp_cubic.c#L366">366</a> }
<a name="L367" href="source/net/ipv4/tcp_cubic.c#L367">367</a> 
<a name="L368" href="source/net/ipv4/tcp_cubic.c#L368">368</a> static void <a href="ident?i=hystart_update">hystart_update</a>(struct <a href="ident?i=sock">sock</a> *sk, <a href="ident?i=u32">u32</a> <a href="ident?i=delay">delay</a>)
<a name="L369" href="source/net/ipv4/tcp_cubic.c#L369">369</a> {
<a name="L370" href="source/net/ipv4/tcp_cubic.c#L370">370</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L371" href="source/net/ipv4/tcp_cubic.c#L371">371</a>         struct <a href="ident?i=bictcp">bictcp</a> *<a href="ident?i=ca">ca</a> = <a href="ident?i=inet_csk_ca">inet_csk_ca</a>(sk);
<a name="L372" href="source/net/ipv4/tcp_cubic.c#L372">372</a> 
<a name="L373" href="source/net/ipv4/tcp_cubic.c#L373">373</a>         if (<a href="ident?i=ca">ca</a>-&gt;<a href="ident?i=found">found</a> &amp; hystart_detect)
<a name="L374" href="source/net/ipv4/tcp_cubic.c#L374">374</a>                 return;
<a name="L375" href="source/net/ipv4/tcp_cubic.c#L375">375</a> 
<a name="L376" href="source/net/ipv4/tcp_cubic.c#L376">376</a>         if (hystart_detect &amp; <a href="ident?i=HYSTART_ACK_TRAIN">HYSTART_ACK_TRAIN</a>) {
<a name="L377" href="source/net/ipv4/tcp_cubic.c#L377">377</a>                 <a href="ident?i=u32">u32</a> <a href="ident?i=now">now</a> = <a href="ident?i=bictcp_clock">bictcp_clock</a>();
<a name="L378" href="source/net/ipv4/tcp_cubic.c#L378">378</a> 
<a name="L379" href="source/net/ipv4/tcp_cubic.c#L379">379</a>                 <b><i>/* first detection parameter - ack-train detection */</i></b>
<a name="L380" href="source/net/ipv4/tcp_cubic.c#L380">380</a>                 if ((<a href="ident?i=s32">s32</a>)(<a href="ident?i=now">now</a> - <a href="ident?i=ca">ca</a>-&gt;last_ack) &lt;= hystart_ack_delta) {
<a name="L381" href="source/net/ipv4/tcp_cubic.c#L381">381</a>                         <a href="ident?i=ca">ca</a>-&gt;last_ack = <a href="ident?i=now">now</a>;
<a name="L382" href="source/net/ipv4/tcp_cubic.c#L382">382</a>                         if ((<a href="ident?i=s32">s32</a>)(<a href="ident?i=now">now</a> - <a href="ident?i=ca">ca</a>-&gt;round_start) &gt; <a href="ident?i=ca">ca</a>-&gt;delay_min &gt;&gt; 4) {
<a name="L383" href="source/net/ipv4/tcp_cubic.c#L383">383</a>                                 <a href="ident?i=ca">ca</a>-&gt;<a href="ident?i=found">found</a> |= <a href="ident?i=HYSTART_ACK_TRAIN">HYSTART_ACK_TRAIN</a>;
<a name="L384" href="source/net/ipv4/tcp_cubic.c#L384">384</a>                                 <a href="ident?i=NET_INC_STATS_BH">NET_INC_STATS_BH</a>(<a href="ident?i=sock_net">sock_net</a>(sk),
<a name="L385" href="source/net/ipv4/tcp_cubic.c#L385">385</a>                                                  LINUX_MIB_TCPHYSTARTTRAINDETECT);
<a name="L386" href="source/net/ipv4/tcp_cubic.c#L386">386</a>                                 <a href="ident?i=NET_ADD_STATS_BH">NET_ADD_STATS_BH</a>(<a href="ident?i=sock_net">sock_net</a>(sk),
<a name="L387" href="source/net/ipv4/tcp_cubic.c#L387">387</a>                                                  LINUX_MIB_TCPHYSTARTTRAINCWND,
<a name="L388" href="source/net/ipv4/tcp_cubic.c#L388">388</a>                                                  <a href="ident?i=tp">tp</a>-&gt;snd_cwnd);
<a name="L389" href="source/net/ipv4/tcp_cubic.c#L389">389</a>                                 <a href="ident?i=tp">tp</a>-&gt;snd_ssthresh = <a href="ident?i=tp">tp</a>-&gt;snd_cwnd;
<a name="L390" href="source/net/ipv4/tcp_cubic.c#L390">390</a>                         }
<a name="L391" href="source/net/ipv4/tcp_cubic.c#L391">391</a>                 }
<a name="L392" href="source/net/ipv4/tcp_cubic.c#L392">392</a>         }
<a name="L393" href="source/net/ipv4/tcp_cubic.c#L393">393</a> 
<a name="L394" href="source/net/ipv4/tcp_cubic.c#L394">394</a>         if (hystart_detect &amp; <a href="ident?i=HYSTART_DELAY">HYSTART_DELAY</a>) {
<a name="L395" href="source/net/ipv4/tcp_cubic.c#L395">395</a>                 <b><i>/* obtain the minimum delay of more than sampling packets */</i></b>
<a name="L396" href="source/net/ipv4/tcp_cubic.c#L396">396</a>                 if (<a href="ident?i=ca">ca</a>-&gt;sample_cnt &lt; <a href="ident?i=HYSTART_MIN_SAMPLES">HYSTART_MIN_SAMPLES</a>) {
<a name="L397" href="source/net/ipv4/tcp_cubic.c#L397">397</a>                         if (<a href="ident?i=ca">ca</a>-&gt;curr_rtt == 0 || <a href="ident?i=ca">ca</a>-&gt;curr_rtt &gt; <a href="ident?i=delay">delay</a>)
<a name="L398" href="source/net/ipv4/tcp_cubic.c#L398">398</a>                                 <a href="ident?i=ca">ca</a>-&gt;curr_rtt = <a href="ident?i=delay">delay</a>;
<a name="L399" href="source/net/ipv4/tcp_cubic.c#L399">399</a> 
<a name="L400" href="source/net/ipv4/tcp_cubic.c#L400">400</a>                         <a href="ident?i=ca">ca</a>-&gt;sample_cnt++;
<a name="L401" href="source/net/ipv4/tcp_cubic.c#L401">401</a>                 } else {
<a name="L402" href="source/net/ipv4/tcp_cubic.c#L402">402</a>                         if (<a href="ident?i=ca">ca</a>-&gt;curr_rtt &gt; <a href="ident?i=ca">ca</a>-&gt;delay_min +
<a name="L403" href="source/net/ipv4/tcp_cubic.c#L403">403</a>                             <a href="ident?i=HYSTART_DELAY_THRESH">HYSTART_DELAY_THRESH</a>(<a href="ident?i=ca">ca</a>-&gt;delay_min &gt;&gt; 3)) {
<a name="L404" href="source/net/ipv4/tcp_cubic.c#L404">404</a>                                 <a href="ident?i=ca">ca</a>-&gt;<a href="ident?i=found">found</a> |= <a href="ident?i=HYSTART_DELAY">HYSTART_DELAY</a>;
<a name="L405" href="source/net/ipv4/tcp_cubic.c#L405">405</a>                                 <a href="ident?i=NET_INC_STATS_BH">NET_INC_STATS_BH</a>(<a href="ident?i=sock_net">sock_net</a>(sk),
<a name="L406" href="source/net/ipv4/tcp_cubic.c#L406">406</a>                                                  LINUX_MIB_TCPHYSTARTDELAYDETECT);
<a name="L407" href="source/net/ipv4/tcp_cubic.c#L407">407</a>                                 <a href="ident?i=NET_ADD_STATS_BH">NET_ADD_STATS_BH</a>(<a href="ident?i=sock_net">sock_net</a>(sk),
<a name="L408" href="source/net/ipv4/tcp_cubic.c#L408">408</a>                                                  LINUX_MIB_TCPHYSTARTDELAYCWND,
<a name="L409" href="source/net/ipv4/tcp_cubic.c#L409">409</a>                                                  <a href="ident?i=tp">tp</a>-&gt;snd_cwnd);
<a name="L410" href="source/net/ipv4/tcp_cubic.c#L410">410</a>                                 <a href="ident?i=tp">tp</a>-&gt;snd_ssthresh = <a href="ident?i=tp">tp</a>-&gt;snd_cwnd;
<a name="L411" href="source/net/ipv4/tcp_cubic.c#L411">411</a>                         }
<a name="L412" href="source/net/ipv4/tcp_cubic.c#L412">412</a>                 }
<a name="L413" href="source/net/ipv4/tcp_cubic.c#L413">413</a>         }
<a name="L414" href="source/net/ipv4/tcp_cubic.c#L414">414</a> }
<a name="L415" href="source/net/ipv4/tcp_cubic.c#L415">415</a> 
<a name="L416" href="source/net/ipv4/tcp_cubic.c#L416">416</a> <b><i>/* Track delayed acknowledgment ratio using sliding window</i></b>
<a name="L417" href="source/net/ipv4/tcp_cubic.c#L417">417</a> <b><i> * ratio = (15*ratio + sample) / 16</i></b>
<a name="L418" href="source/net/ipv4/tcp_cubic.c#L418">418</a> <b><i> */</i></b>
<a name="L419" href="source/net/ipv4/tcp_cubic.c#L419">419</a> static void <a href="ident?i=bictcp_acked">bictcp_acked</a>(struct <a href="ident?i=sock">sock</a> *sk, <a href="ident?i=u32">u32</a> cnt, <a href="ident?i=s32">s32</a> rtt_us)
<a name="L420" href="source/net/ipv4/tcp_cubic.c#L420">420</a> {
<a name="L421" href="source/net/ipv4/tcp_cubic.c#L421">421</a>         const struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L422" href="source/net/ipv4/tcp_cubic.c#L422">422</a>         struct <a href="ident?i=bictcp">bictcp</a> *<a href="ident?i=ca">ca</a> = <a href="ident?i=inet_csk_ca">inet_csk_ca</a>(sk);
<a name="L423" href="source/net/ipv4/tcp_cubic.c#L423">423</a>         <a href="ident?i=u32">u32</a> <a href="ident?i=delay">delay</a>;
<a name="L424" href="source/net/ipv4/tcp_cubic.c#L424">424</a> 
<a name="L425" href="source/net/ipv4/tcp_cubic.c#L425">425</a>         <b><i>/* Some calls are for duplicates without timetamps */</i></b>
<a name="L426" href="source/net/ipv4/tcp_cubic.c#L426">426</a>         if (rtt_us &lt; 0)
<a name="L427" href="source/net/ipv4/tcp_cubic.c#L427">427</a>                 return;
<a name="L428" href="source/net/ipv4/tcp_cubic.c#L428">428</a> 
<a name="L429" href="source/net/ipv4/tcp_cubic.c#L429">429</a>         <b><i>/* Discard delay samples right after fast recovery */</i></b>
<a name="L430" href="source/net/ipv4/tcp_cubic.c#L430">430</a>         if (<a href="ident?i=ca">ca</a>-&gt;epoch_start &amp;&amp; (<a href="ident?i=s32">s32</a>)(<a href="ident?i=tcp_time_stamp">tcp_time_stamp</a> - <a href="ident?i=ca">ca</a>-&gt;epoch_start) &lt; <a href="ident?i=HZ">HZ</a>)
<a name="L431" href="source/net/ipv4/tcp_cubic.c#L431">431</a>                 return;
<a name="L432" href="source/net/ipv4/tcp_cubic.c#L432">432</a> 
<a name="L433" href="source/net/ipv4/tcp_cubic.c#L433">433</a>         <a href="ident?i=delay">delay</a> = (rtt_us &lt;&lt; 3) / <a href="ident?i=USEC_PER_MSEC">USEC_PER_MSEC</a>;
<a name="L434" href="source/net/ipv4/tcp_cubic.c#L434">434</a>         if (<a href="ident?i=delay">delay</a> == 0)
<a name="L435" href="source/net/ipv4/tcp_cubic.c#L435">435</a>                 <a href="ident?i=delay">delay</a> = 1;
<a name="L436" href="source/net/ipv4/tcp_cubic.c#L436">436</a> 
<a name="L437" href="source/net/ipv4/tcp_cubic.c#L437">437</a>         <b><i>/* first time call or link delay decreases */</i></b>
<a name="L438" href="source/net/ipv4/tcp_cubic.c#L438">438</a>         if (<a href="ident?i=ca">ca</a>-&gt;delay_min == 0 || <a href="ident?i=ca">ca</a>-&gt;delay_min &gt; <a href="ident?i=delay">delay</a>)
<a name="L439" href="source/net/ipv4/tcp_cubic.c#L439">439</a>                 <a href="ident?i=ca">ca</a>-&gt;delay_min = <a href="ident?i=delay">delay</a>;
<a name="L440" href="source/net/ipv4/tcp_cubic.c#L440">440</a> 
<a name="L441" href="source/net/ipv4/tcp_cubic.c#L441">441</a>         <b><i>/* hystart triggers when cwnd is larger than some threshold */</i></b>
<a name="L442" href="source/net/ipv4/tcp_cubic.c#L442">442</a>         if (hystart &amp;&amp; <a href="ident?i=tp">tp</a>-&gt;snd_cwnd &lt;= <a href="ident?i=tp">tp</a>-&gt;snd_ssthresh &amp;&amp;
<a name="L443" href="source/net/ipv4/tcp_cubic.c#L443">443</a>             <a href="ident?i=tp">tp</a>-&gt;snd_cwnd &gt;= hystart_low_window)
<a name="L444" href="source/net/ipv4/tcp_cubic.c#L444">444</a>                 <a href="ident?i=hystart_update">hystart_update</a>(sk, <a href="ident?i=delay">delay</a>);
<a name="L445" href="source/net/ipv4/tcp_cubic.c#L445">445</a> }
<a name="L446" href="source/net/ipv4/tcp_cubic.c#L446">446</a> 
<a name="L447" href="source/net/ipv4/tcp_cubic.c#L447">447</a> static struct <a href="ident?i=tcp_congestion_ops">tcp_congestion_ops</a> cubictcp <a href="ident?i=__read_mostly">__read_mostly</a> = {
<a name="L448" href="source/net/ipv4/tcp_cubic.c#L448">448</a>         .<a href="ident?i=init">init</a>           = <a href="ident?i=bictcp_init">bictcp_init</a>,
<a name="L449" href="source/net/ipv4/tcp_cubic.c#L449">449</a>         .ssthresh       = <a href="ident?i=bictcp_recalc_ssthresh">bictcp_recalc_ssthresh</a>,
<a name="L450" href="source/net/ipv4/tcp_cubic.c#L450">450</a>         .cong_avoid     = <a href="ident?i=bictcp_cong_avoid">bictcp_cong_avoid</a>,
<a name="L451" href="source/net/ipv4/tcp_cubic.c#L451">451</a>         .<a href="ident?i=set_state">set_state</a>      = <a href="ident?i=bictcp_state">bictcp_state</a>,
<a name="L452" href="source/net/ipv4/tcp_cubic.c#L452">452</a>         .undo_cwnd      = <a href="ident?i=bictcp_undo_cwnd">bictcp_undo_cwnd</a>,
<a name="L453" href="source/net/ipv4/tcp_cubic.c#L453">453</a>         .pkts_acked     = <a href="ident?i=bictcp_acked">bictcp_acked</a>,
<a name="L454" href="source/net/ipv4/tcp_cubic.c#L454">454</a>         .owner          = <a href="ident?i=THIS_MODULE">THIS_MODULE</a>,
<a name="L455" href="source/net/ipv4/tcp_cubic.c#L455">455</a>         .<a href="ident?i=name">name</a>           = <i>"cubic"</i>,
<a name="L456" href="source/net/ipv4/tcp_cubic.c#L456">456</a> };
<a name="L457" href="source/net/ipv4/tcp_cubic.c#L457">457</a> 
<a name="L458" href="source/net/ipv4/tcp_cubic.c#L458">458</a> static int <a href="ident?i=__init">__init</a> <a href="ident?i=cubictcp_register">cubictcp_register</a>(void)
<a name="L459" href="source/net/ipv4/tcp_cubic.c#L459">459</a> {
<a name="L460" href="source/net/ipv4/tcp_cubic.c#L460">460</a>         <a href="ident?i=BUILD_BUG_ON">BUILD_BUG_ON</a>(sizeof(struct <a href="ident?i=bictcp">bictcp</a>) &gt; <a href="ident?i=ICSK_CA_PRIV_SIZE">ICSK_CA_PRIV_SIZE</a>);
<a name="L461" href="source/net/ipv4/tcp_cubic.c#L461">461</a> 
<a name="L462" href="source/net/ipv4/tcp_cubic.c#L462">462</a>         <b><i>/* Precompute a bunch of the scaling factors that are used per-packet</i></b>
<a name="L463" href="source/net/ipv4/tcp_cubic.c#L463">463</a> <b><i>         * based on SRTT of 100ms</i></b>
<a name="L464" href="source/net/ipv4/tcp_cubic.c#L464">464</a> <b><i>         */</i></b>
<a name="L465" href="source/net/ipv4/tcp_cubic.c#L465">465</a> 
<a name="L466" href="source/net/ipv4/tcp_cubic.c#L466">466</a>         beta_scale = 8*(<a href="ident?i=BICTCP_BETA_SCALE">BICTCP_BETA_SCALE</a>+<a href="ident?i=beta">beta</a>) / 3
<a name="L467" href="source/net/ipv4/tcp_cubic.c#L467">467</a>                 / (<a href="ident?i=BICTCP_BETA_SCALE">BICTCP_BETA_SCALE</a> - <a href="ident?i=beta">beta</a>);
<a name="L468" href="source/net/ipv4/tcp_cubic.c#L468">468</a> 
<a name="L469" href="source/net/ipv4/tcp_cubic.c#L469">469</a>         cube_rtt_scale = (bic_scale * 10);      <b><i>/* 1024*c/rtt */</i></b>
<a name="L470" href="source/net/ipv4/tcp_cubic.c#L470">470</a> 
<a name="L471" href="source/net/ipv4/tcp_cubic.c#L471">471</a>         <b><i>/* calculate the "K" for (wmax-cwnd) = c/rtt * K^3</i></b>
<a name="L472" href="source/net/ipv4/tcp_cubic.c#L472">472</a> <b><i>         *  so K = cubic_root( (wmax-cwnd)*rtt/c )</i></b>
<a name="L473" href="source/net/ipv4/tcp_cubic.c#L473">473</a> <b><i>         * the unit of K is bictcp_HZ=2^10, not HZ</i></b>
<a name="L474" href="source/net/ipv4/tcp_cubic.c#L474">474</a> <b><i>         *</i></b>
<a name="L475" href="source/net/ipv4/tcp_cubic.c#L475">475</a> <b><i>         *  c = bic_scale &gt;&gt; 10</i></b>
<a name="L476" href="source/net/ipv4/tcp_cubic.c#L476">476</a> <b><i>         *  rtt = 100ms</i></b>
<a name="L477" href="source/net/ipv4/tcp_cubic.c#L477">477</a> <b><i>         *</i></b>
<a name="L478" href="source/net/ipv4/tcp_cubic.c#L478">478</a> <b><i>         * the following code has been designed and tested for</i></b>
<a name="L479" href="source/net/ipv4/tcp_cubic.c#L479">479</a> <b><i>         * cwnd &lt; 1 million packets</i></b>
<a name="L480" href="source/net/ipv4/tcp_cubic.c#L480">480</a> <b><i>         * RTT &lt; 100 seconds</i></b>
<a name="L481" href="source/net/ipv4/tcp_cubic.c#L481">481</a> <b><i>         * HZ &lt; 1,000,00  (corresponding to 10 nano-second)</i></b>
<a name="L482" href="source/net/ipv4/tcp_cubic.c#L482">482</a> <b><i>         */</i></b>
<a name="L483" href="source/net/ipv4/tcp_cubic.c#L483">483</a> 
<a name="L484" href="source/net/ipv4/tcp_cubic.c#L484">484</a>         <b><i>/* 1/c * 2^2*bictcp_HZ * srtt */</i></b>
<a name="L485" href="source/net/ipv4/tcp_cubic.c#L485">485</a>         cube_factor = 1ull &lt;&lt; (10+3*<a href="ident?i=BICTCP_HZ">BICTCP_HZ</a>); <b><i>/* 2^40 */</i></b>
<a name="L486" href="source/net/ipv4/tcp_cubic.c#L486">486</a> 
<a name="L487" href="source/net/ipv4/tcp_cubic.c#L487">487</a>         <b><i>/* divide by bic_scale and by constant Srtt (100ms) */</i></b>
<a name="L488" href="source/net/ipv4/tcp_cubic.c#L488">488</a>         <a href="ident?i=do_div">do_div</a>(cube_factor, bic_scale * 10);
<a name="L489" href="source/net/ipv4/tcp_cubic.c#L489">489</a> 
<a name="L490" href="source/net/ipv4/tcp_cubic.c#L490">490</a>         return <a href="ident?i=tcp_register_congestion_control">tcp_register_congestion_control</a>(&amp;cubictcp);
<a name="L491" href="source/net/ipv4/tcp_cubic.c#L491">491</a> }
<a name="L492" href="source/net/ipv4/tcp_cubic.c#L492">492</a> 
<a name="L493" href="source/net/ipv4/tcp_cubic.c#L493">493</a> static void <a href="ident?i=__exit">__exit</a> <a href="ident?i=cubictcp_unregister">cubictcp_unregister</a>(void)
<a name="L494" href="source/net/ipv4/tcp_cubic.c#L494">494</a> {
<a name="L495" href="source/net/ipv4/tcp_cubic.c#L495">495</a>         <a href="ident?i=tcp_unregister_congestion_control">tcp_unregister_congestion_control</a>(&amp;cubictcp);
<a name="L496" href="source/net/ipv4/tcp_cubic.c#L496">496</a> }
<a name="L497" href="source/net/ipv4/tcp_cubic.c#L497">497</a> 
<a name="L498" href="source/net/ipv4/tcp_cubic.c#L498">498</a> <a href="ident?i=module_init">module_init</a>(<a href="ident?i=cubictcp_register">cubictcp_register</a>);
<a name="L499" href="source/net/ipv4/tcp_cubic.c#L499">499</a> <a href="ident?i=module_exit">module_exit</a>(<a href="ident?i=cubictcp_unregister">cubictcp_unregister</a>);
<a name="L500" href="source/net/ipv4/tcp_cubic.c#L500">500</a> 
<a name="L501" href="source/net/ipv4/tcp_cubic.c#L501">501</a> <a href="ident?i=MODULE_AUTHOR">MODULE_AUTHOR</a>(<i>"Sangtae Ha, Stephen Hemminger"</i>);
<a name="L502" href="source/net/ipv4/tcp_cubic.c#L502">502</a> <a href="ident?i=MODULE_LICENSE">MODULE_LICENSE</a>(<i>"GPL"</i>);
<a name="L503" href="source/net/ipv4/tcp_cubic.c#L503">503</a> <a href="ident?i=MODULE_DESCRIPTION">MODULE_DESCRIPTION</a>(<i>"CUBIC TCP"</i>);
<a name="L504" href="source/net/ipv4/tcp_cubic.c#L504">504</a> <a href="ident?i=MODULE_VERSION">MODULE_VERSION</a>(<i>"2.3"</i>);
<a name="L505" href="source/net/ipv4/tcp_cubic.c#L505">505</a> </pre></div><p>
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
