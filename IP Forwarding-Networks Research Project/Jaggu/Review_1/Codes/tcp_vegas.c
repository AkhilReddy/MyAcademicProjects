<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title>Linux/net/ipv4/tcp_vegas.c - Linux Cross Reference - Free Electrons</title>
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
		 &nbsp;&bull;&nbsp;<b><i>source navigation</i></b> &nbsp;&bull;&nbsp;<a href="diff/net/ipv4/tcp_vegas.c">diff markup</a> &nbsp;&bull;&nbsp;<a href="ident">identifier search</a> &nbsp;&bull;&nbsp;<a href="search">freetext search</a> &nbsp;&bull;&nbsp;
		</p>
	</div>
</div>

<div id="topbar">
  
  <p>Version: &nbsp;<a href="source/net/ipv4/tcp_vegas.c?v=2.0.40">2.0.40</a>&nbsp;<a href="source/net/ipv4/tcp_vegas.c?v=2.2.26">2.2.26</a>&nbsp;<a href="source/net/ipv4/tcp_vegas.c?v=2.4.37">2.4.37</a>&nbsp;<a href="source/net/ipv4/tcp_vegas.c?v=3.5">3.5</a>&nbsp;<a href="source/net/ipv4/tcp_vegas.c?v=3.6">3.6</a>&nbsp;<a href="source/net/ipv4/tcp_vegas.c?v=3.7">3.7</a>&nbsp;<a href="source/net/ipv4/tcp_vegas.c?v=3.8">3.8</a>&nbsp;<a href="source/net/ipv4/tcp_vegas.c?v=3.9">3.9</a>&nbsp;<a href="source/net/ipv4/tcp_vegas.c?v=3.10">3.10</a>&nbsp;<a href="source/net/ipv4/tcp_vegas.c?v=3.11">3.11</a>&nbsp;<a href="source/net/ipv4/tcp_vegas.c?v=3.12">3.12</a>&nbsp;<a href="source/net/ipv4/tcp_vegas.c?v=3.13">3.13</a>&nbsp;<a href="source/net/ipv4/tcp_vegas.c?v=3.14">3.14</a>&nbsp;<a href="source/net/ipv4/tcp_vegas.c?v=3.15">3.15</a>&nbsp;<a href="source/net/ipv4/tcp_vegas.c?v=3.16">3.16</a>&nbsp;<a href="source/net/ipv4/tcp_vegas.c?v=3.17">3.17</a>&nbsp;<a href="source/net/ipv4/tcp_vegas.c?v=3.18">3.18</a>&nbsp;<a href="source/net/ipv4/tcp_vegas.c?v=3.19">3.19</a>&nbsp;<a href="source/net/ipv4/tcp_vegas.c?v=4.0">4.0</a>&nbsp;<b><i>4.1</i></b></p>
  
</div>

<h1><a href="source/">Linux</a>/<a href="source/net/">net</a>/<a href="source/net/ipv4/">ipv4</a>/<a href="source/net/ipv4/tcp_vegas.c">tcp_vegas.c</a></h1>
<div id="lxrcode"><pre>  <a name="L1" href="source/net/ipv4/tcp_vegas.c#L1">1</a> <b><i>/*</i></b>
  <a name="L2" href="source/net/ipv4/tcp_vegas.c#L2">2</a> <b><i> * TCP Vegas congestion control</i></b>
  <a name="L3" href="source/net/ipv4/tcp_vegas.c#L3">3</a> <b><i> *</i></b>
  <a name="L4" href="source/net/ipv4/tcp_vegas.c#L4">4</a> <b><i> * This is based on the congestion detection/avoidance scheme described in</i></b>
  <a name="L5" href="source/net/ipv4/tcp_vegas.c#L5">5</a> <b><i> *    Lawrence S. Brakmo and Larry L. Peterson.</i></b>
  <a name="L6" href="source/net/ipv4/tcp_vegas.c#L6">6</a> <b><i> *    "TCP Vegas: End to end congestion avoidance on a global internet."</i></b>
  <a name="L7" href="source/net/ipv4/tcp_vegas.c#L7">7</a> <b><i> *    IEEE Journal on Selected Areas in Communication, 13(8):1465--1480,</i></b>
  <a name="L8" href="source/net/ipv4/tcp_vegas.c#L8">8</a> <b><i> *    October 1995. Available from:</i></b>
  <a name="L9" href="source/net/ipv4/tcp_vegas.c#L9">9</a> <b><i> *      <a href="ftp://ftp.cs.arizona.edu/xkernel/Papers/jsac.ps">ftp://ftp.cs.arizona.edu/xkernel/Papers/jsac.ps</a></i></b>
 <a name="L10" href="source/net/ipv4/tcp_vegas.c#L10">10</a> <b><i> *</i></b>
 <a name="L11" href="source/net/ipv4/tcp_vegas.c#L11">11</a> <b><i> * See <a href="http://www.cs.arizona.edu/xkernel/">http://www.cs.arizona.edu/xkernel/</a> for their implementation.</i></b>
 <a name="L12" href="source/net/ipv4/tcp_vegas.c#L12">12</a> <b><i> * The main aspects that distinguish this implementation from the</i></b>
 <a name="L13" href="source/net/ipv4/tcp_vegas.c#L13">13</a> <b><i> * Arizona Vegas implementation are:</i></b>
 <a name="L14" href="source/net/ipv4/tcp_vegas.c#L14">14</a> <b><i> *   o We do not change the loss detection or recovery mechanisms of</i></b>
 <a name="L15" href="source/net/ipv4/tcp_vegas.c#L15">15</a> <b><i> *     Linux in any way. Linux already recovers from losses quite well,</i></b>
 <a name="L16" href="source/net/ipv4/tcp_vegas.c#L16">16</a> <b><i> *     using fine-grained timers, NewReno, and FACK.</i></b>
 <a name="L17" href="source/net/ipv4/tcp_vegas.c#L17">17</a> <b><i> *   o To avoid the performance penalty imposed by increasing cwnd</i></b>
 <a name="L18" href="source/net/ipv4/tcp_vegas.c#L18">18</a> <b><i> *     only every-other RTT during slow start, we increase during</i></b>
 <a name="L19" href="source/net/ipv4/tcp_vegas.c#L19">19</a> <b><i> *     every RTT during slow start, just like Reno.</i></b>
 <a name="L20" href="source/net/ipv4/tcp_vegas.c#L20">20</a> <b><i> *   o Largely to allow continuous cwnd growth during slow start,</i></b>
 <a name="L21" href="source/net/ipv4/tcp_vegas.c#L21">21</a> <b><i> *     we use the rate at which ACKs come back as the "actual"</i></b>
 <a name="L22" href="source/net/ipv4/tcp_vegas.c#L22">22</a> <b><i> *     rate, rather than the rate at which data is sent.</i></b>
 <a name="L23" href="source/net/ipv4/tcp_vegas.c#L23">23</a> <b><i> *   o To speed convergence to the right rate, we set the cwnd</i></b>
 <a name="L24" href="source/net/ipv4/tcp_vegas.c#L24">24</a> <b><i> *     to achieve the right ("actual") rate when we exit slow start.</i></b>
 <a name="L25" href="source/net/ipv4/tcp_vegas.c#L25">25</a> <b><i> *   o To filter out the noise caused by delayed ACKs, we use the</i></b>
 <a name="L26" href="source/net/ipv4/tcp_vegas.c#L26">26</a> <b><i> *     minimum RTT sample observed during the last RTT to calculate</i></b>
 <a name="L27" href="source/net/ipv4/tcp_vegas.c#L27">27</a> <b><i> *     the actual rate.</i></b>
 <a name="L28" href="source/net/ipv4/tcp_vegas.c#L28">28</a> <b><i> *   o When the sender re-starts from idle, it waits until it has</i></b>
 <a name="L29" href="source/net/ipv4/tcp_vegas.c#L29">29</a> <b><i> *     received ACKs for an entire flight of new data before making</i></b>
 <a name="L30" href="source/net/ipv4/tcp_vegas.c#L30">30</a> <b><i> *     a cwnd adjustment decision. The original Vegas implementation</i></b>
 <a name="L31" href="source/net/ipv4/tcp_vegas.c#L31">31</a> <b><i> *     assumed senders never went idle.</i></b>
 <a name="L32" href="source/net/ipv4/tcp_vegas.c#L32">32</a> <b><i> */</i></b>
 <a name="L33" href="source/net/ipv4/tcp_vegas.c#L33">33</a> 
 <a name="L34" href="source/net/ipv4/tcp_vegas.c#L34">34</a> #include &lt;linux/mm.h&gt;
 <a name="L35" href="source/net/ipv4/tcp_vegas.c#L35">35</a> #include &lt;linux/module.h&gt;
 <a name="L36" href="source/net/ipv4/tcp_vegas.c#L36">36</a> #include &lt;linux/skbuff.h&gt;
 <a name="L37" href="source/net/ipv4/tcp_vegas.c#L37">37</a> #include &lt;linux/inet_diag.h&gt;
 <a name="L38" href="source/net/ipv4/tcp_vegas.c#L38">38</a> 
 <a name="L39" href="source/net/ipv4/tcp_vegas.c#L39">39</a> #include &lt;net/tcp.h&gt;
 <a name="L40" href="source/net/ipv4/tcp_vegas.c#L40">40</a> 
 <a name="L41" href="source/net/ipv4/tcp_vegas.c#L41">41</a> #include "<a href="source/net/ipv4/tcp_vegas.h">tcp_vegas.h</a>"
 <a name="L42" href="source/net/ipv4/tcp_vegas.c#L42">42</a> 
 <a name="L43" href="source/net/ipv4/tcp_vegas.c#L43">43</a> static int <a href="ident?i=alpha">alpha</a> = 2;
 <a name="L44" href="source/net/ipv4/tcp_vegas.c#L44">44</a> static int <a href="ident?i=beta">beta</a>  = 4;
 <a name="L45" href="source/net/ipv4/tcp_vegas.c#L45">45</a> static int <a href="ident?i=gamma">gamma</a> = 1;
 <a name="L46" href="source/net/ipv4/tcp_vegas.c#L46">46</a> 
 <a name="L47" href="source/net/ipv4/tcp_vegas.c#L47">47</a> <a href="ident?i=module_param">module_param</a>(<a href="ident?i=alpha">alpha</a>, int, 0644);
 <a name="L48" href="source/net/ipv4/tcp_vegas.c#L48">48</a> <a href="ident?i=MODULE_PARM_DESC">MODULE_PARM_DESC</a>(<a href="ident?i=alpha">alpha</a>, <i>"lower bound of packets in network"</i>);
 <a name="L49" href="source/net/ipv4/tcp_vegas.c#L49">49</a> <a href="ident?i=module_param">module_param</a>(<a href="ident?i=beta">beta</a>, int, 0644);
 <a name="L50" href="source/net/ipv4/tcp_vegas.c#L50">50</a> <a href="ident?i=MODULE_PARM_DESC">MODULE_PARM_DESC</a>(<a href="ident?i=beta">beta</a>, <i>"upper bound of packets in network"</i>);
 <a name="L51" href="source/net/ipv4/tcp_vegas.c#L51">51</a> <a href="ident?i=module_param">module_param</a>(<a href="ident?i=gamma">gamma</a>, int, 0644);
 <a name="L52" href="source/net/ipv4/tcp_vegas.c#L52">52</a> <a href="ident?i=MODULE_PARM_DESC">MODULE_PARM_DESC</a>(<a href="ident?i=gamma">gamma</a>, <i>"limit on increase (scale by 2)"</i>);
 <a name="L53" href="source/net/ipv4/tcp_vegas.c#L53">53</a> 
 <a name="L54" href="source/net/ipv4/tcp_vegas.c#L54">54</a> <b><i>/* There are several situations when we must "re-start" Vegas:</i></b>
 <a name="L55" href="source/net/ipv4/tcp_vegas.c#L55">55</a> <b><i> *</i></b>
 <a name="L56" href="source/net/ipv4/tcp_vegas.c#L56">56</a> <b><i> *  o when a connection is established</i></b>
 <a name="L57" href="source/net/ipv4/tcp_vegas.c#L57">57</a> <b><i> *  o after an RTO</i></b>
 <a name="L58" href="source/net/ipv4/tcp_vegas.c#L58">58</a> <b><i> *  o after fast recovery</i></b>
 <a name="L59" href="source/net/ipv4/tcp_vegas.c#L59">59</a> <b><i> *  o when we send a packet and there is no outstanding</i></b>
 <a name="L60" href="source/net/ipv4/tcp_vegas.c#L60">60</a> <b><i> *    unacknowledged data (restarting an idle connection)</i></b>
 <a name="L61" href="source/net/ipv4/tcp_vegas.c#L61">61</a> <b><i> *</i></b>
 <a name="L62" href="source/net/ipv4/tcp_vegas.c#L62">62</a> <b><i> * In these circumstances we cannot do a Vegas calculation at the</i></b>
 <a name="L63" href="source/net/ipv4/tcp_vegas.c#L63">63</a> <b><i> * end of the first RTT, because any calculation we do is using</i></b>
 <a name="L64" href="source/net/ipv4/tcp_vegas.c#L64">64</a> <b><i> * stale info -- both the saved cwnd and congestion feedback are</i></b>
 <a name="L65" href="source/net/ipv4/tcp_vegas.c#L65">65</a> <b><i> * stale.</i></b>
 <a name="L66" href="source/net/ipv4/tcp_vegas.c#L66">66</a> <b><i> *</i></b>
 <a name="L67" href="source/net/ipv4/tcp_vegas.c#L67">67</a> <b><i> * Instead we must wait until the completion of an RTT during</i></b>
 <a name="L68" href="source/net/ipv4/tcp_vegas.c#L68">68</a> <b><i> * which we actually receive ACKs.</i></b>
 <a name="L69" href="source/net/ipv4/tcp_vegas.c#L69">69</a> <b><i> */</i></b>
 <a name="L70" href="source/net/ipv4/tcp_vegas.c#L70">70</a> static void <a href="ident?i=vegas_enable">vegas_enable</a>(struct <a href="ident?i=sock">sock</a> *sk)
 <a name="L71" href="source/net/ipv4/tcp_vegas.c#L71">71</a> {
 <a name="L72" href="source/net/ipv4/tcp_vegas.c#L72">72</a>         const struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
 <a name="L73" href="source/net/ipv4/tcp_vegas.c#L73">73</a>         struct <a href="ident?i=vegas">vegas</a> *<a href="ident?i=vegas">vegas</a> = <a href="ident?i=inet_csk_ca">inet_csk_ca</a>(sk);
 <a name="L74" href="source/net/ipv4/tcp_vegas.c#L74">74</a> 
 <a name="L75" href="source/net/ipv4/tcp_vegas.c#L75">75</a>         <b><i>/* Begin taking Vegas samples next time we send something. */</i></b>
 <a name="L76" href="source/net/ipv4/tcp_vegas.c#L76">76</a>         <a href="ident?i=vegas">vegas</a>-&gt;doing_vegas_now = 1;
 <a name="L77" href="source/net/ipv4/tcp_vegas.c#L77">77</a> 
 <a name="L78" href="source/net/ipv4/tcp_vegas.c#L78">78</a>         <b><i>/* Set the beginning of the next send window. */</i></b>
 <a name="L79" href="source/net/ipv4/tcp_vegas.c#L79">79</a>         <a href="ident?i=vegas">vegas</a>-&gt;beg_snd_nxt = <a href="ident?i=tp">tp</a>-&gt;snd_nxt;
 <a name="L80" href="source/net/ipv4/tcp_vegas.c#L80">80</a> 
 <a name="L81" href="source/net/ipv4/tcp_vegas.c#L81">81</a>         <a href="ident?i=vegas">vegas</a>-&gt;cntRTT = 0;
 <a name="L82" href="source/net/ipv4/tcp_vegas.c#L82">82</a>         <a href="ident?i=vegas">vegas</a>-&gt;minRTT = 0x7fffffff;
 <a name="L83" href="source/net/ipv4/tcp_vegas.c#L83">83</a> }
 <a name="L84" href="source/net/ipv4/tcp_vegas.c#L84">84</a> 
 <a name="L85" href="source/net/ipv4/tcp_vegas.c#L85">85</a> <b><i>/* Stop taking Vegas samples for now. */</i></b>
 <a name="L86" href="source/net/ipv4/tcp_vegas.c#L86">86</a> static inline void <a href="ident?i=vegas_disable">vegas_disable</a>(struct <a href="ident?i=sock">sock</a> *sk)
 <a name="L87" href="source/net/ipv4/tcp_vegas.c#L87">87</a> {
 <a name="L88" href="source/net/ipv4/tcp_vegas.c#L88">88</a>         struct <a href="ident?i=vegas">vegas</a> *<a href="ident?i=vegas">vegas</a> = <a href="ident?i=inet_csk_ca">inet_csk_ca</a>(sk);
 <a name="L89" href="source/net/ipv4/tcp_vegas.c#L89">89</a> 
 <a name="L90" href="source/net/ipv4/tcp_vegas.c#L90">90</a>         <a href="ident?i=vegas">vegas</a>-&gt;doing_vegas_now = 0;
 <a name="L91" href="source/net/ipv4/tcp_vegas.c#L91">91</a> }
 <a name="L92" href="source/net/ipv4/tcp_vegas.c#L92">92</a> 
 <a name="L93" href="source/net/ipv4/tcp_vegas.c#L93">93</a> void <a href="ident?i=tcp_vegas_init">tcp_vegas_init</a>(struct <a href="ident?i=sock">sock</a> *sk)
 <a name="L94" href="source/net/ipv4/tcp_vegas.c#L94">94</a> {
 <a name="L95" href="source/net/ipv4/tcp_vegas.c#L95">95</a>         struct <a href="ident?i=vegas">vegas</a> *<a href="ident?i=vegas">vegas</a> = <a href="ident?i=inet_csk_ca">inet_csk_ca</a>(sk);
 <a name="L96" href="source/net/ipv4/tcp_vegas.c#L96">96</a> 
 <a name="L97" href="source/net/ipv4/tcp_vegas.c#L97">97</a>         <a href="ident?i=vegas">vegas</a>-&gt;baseRTT = 0x7fffffff;
 <a name="L98" href="source/net/ipv4/tcp_vegas.c#L98">98</a>         <a href="ident?i=vegas_enable">vegas_enable</a>(sk);
 <a name="L99" href="source/net/ipv4/tcp_vegas.c#L99">99</a> }
<a name="L100" href="source/net/ipv4/tcp_vegas.c#L100">100</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=tcp_vegas_init">tcp_vegas_init</a>);
<a name="L101" href="source/net/ipv4/tcp_vegas.c#L101">101</a> 
<a name="L102" href="source/net/ipv4/tcp_vegas.c#L102">102</a> <b><i>/* Do RTT sampling needed for Vegas.</i></b>
<a name="L103" href="source/net/ipv4/tcp_vegas.c#L103">103</a> <b><i> * Basically we:</i></b>
<a name="L104" href="source/net/ipv4/tcp_vegas.c#L104">104</a> <b><i> *   o min-filter RTT samples from within an RTT to get the current</i></b>
<a name="L105" href="source/net/ipv4/tcp_vegas.c#L105">105</a> <b><i> *     propagation delay + queuing delay (we are min-filtering to try to</i></b>
<a name="L106" href="source/net/ipv4/tcp_vegas.c#L106">106</a> <b><i> *     avoid the effects of delayed ACKs)</i></b>
<a name="L107" href="source/net/ipv4/tcp_vegas.c#L107">107</a> <b><i> *   o min-filter RTT samples from a much longer window (forever for now)</i></b>
<a name="L108" href="source/net/ipv4/tcp_vegas.c#L108">108</a> <b><i> *     to find the propagation delay (baseRTT)</i></b>
<a name="L109" href="source/net/ipv4/tcp_vegas.c#L109">109</a> <b><i> */</i></b>
<a name="L110" href="source/net/ipv4/tcp_vegas.c#L110">110</a> void <a href="ident?i=tcp_vegas_pkts_acked">tcp_vegas_pkts_acked</a>(struct <a href="ident?i=sock">sock</a> *sk, <a href="ident?i=u32">u32</a> cnt, <a href="ident?i=s32">s32</a> rtt_us)
<a name="L111" href="source/net/ipv4/tcp_vegas.c#L111">111</a> {
<a name="L112" href="source/net/ipv4/tcp_vegas.c#L112">112</a>         struct <a href="ident?i=vegas">vegas</a> *<a href="ident?i=vegas">vegas</a> = <a href="ident?i=inet_csk_ca">inet_csk_ca</a>(sk);
<a name="L113" href="source/net/ipv4/tcp_vegas.c#L113">113</a>         <a href="ident?i=u32">u32</a> vrtt;
<a name="L114" href="source/net/ipv4/tcp_vegas.c#L114">114</a> 
<a name="L115" href="source/net/ipv4/tcp_vegas.c#L115">115</a>         if (rtt_us &lt; 0)
<a name="L116" href="source/net/ipv4/tcp_vegas.c#L116">116</a>                 return;
<a name="L117" href="source/net/ipv4/tcp_vegas.c#L117">117</a> 
<a name="L118" href="source/net/ipv4/tcp_vegas.c#L118">118</a>         <b><i>/* Never allow zero rtt or baseRTT */</i></b>
<a name="L119" href="source/net/ipv4/tcp_vegas.c#L119">119</a>         vrtt = rtt_us + 1;
<a name="L120" href="source/net/ipv4/tcp_vegas.c#L120">120</a> 
<a name="L121" href="source/net/ipv4/tcp_vegas.c#L121">121</a>         <b><i>/* Filter to find propagation delay: */</i></b>
<a name="L122" href="source/net/ipv4/tcp_vegas.c#L122">122</a>         if (vrtt &lt; <a href="ident?i=vegas">vegas</a>-&gt;baseRTT)
<a name="L123" href="source/net/ipv4/tcp_vegas.c#L123">123</a>                 <a href="ident?i=vegas">vegas</a>-&gt;baseRTT = vrtt;
<a name="L124" href="source/net/ipv4/tcp_vegas.c#L124">124</a> 
<a name="L125" href="source/net/ipv4/tcp_vegas.c#L125">125</a>         <b><i>/* Find the min RTT during the last RTT to find</i></b>
<a name="L126" href="source/net/ipv4/tcp_vegas.c#L126">126</a> <b><i>         * the current prop. delay + queuing delay:</i></b>
<a name="L127" href="source/net/ipv4/tcp_vegas.c#L127">127</a> <b><i>         */</i></b>
<a name="L128" href="source/net/ipv4/tcp_vegas.c#L128">128</a>         <a href="ident?i=vegas">vegas</a>-&gt;minRTT = <a href="ident?i=min">min</a>(<a href="ident?i=vegas">vegas</a>-&gt;minRTT, vrtt);
<a name="L129" href="source/net/ipv4/tcp_vegas.c#L129">129</a>         <a href="ident?i=vegas">vegas</a>-&gt;cntRTT++;
<a name="L130" href="source/net/ipv4/tcp_vegas.c#L130">130</a> }
<a name="L131" href="source/net/ipv4/tcp_vegas.c#L131">131</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=tcp_vegas_pkts_acked">tcp_vegas_pkts_acked</a>);
<a name="L132" href="source/net/ipv4/tcp_vegas.c#L132">132</a> 
<a name="L133" href="source/net/ipv4/tcp_vegas.c#L133">133</a> void <a href="ident?i=tcp_vegas_state">tcp_vegas_state</a>(struct <a href="ident?i=sock">sock</a> *sk, <a href="ident?i=u8">u8</a> ca_state)
<a name="L134" href="source/net/ipv4/tcp_vegas.c#L134">134</a> {
<a name="L135" href="source/net/ipv4/tcp_vegas.c#L135">135</a>         if (ca_state == TCP_CA_Open)
<a name="L136" href="source/net/ipv4/tcp_vegas.c#L136">136</a>                 <a href="ident?i=vegas_enable">vegas_enable</a>(sk);
<a name="L137" href="source/net/ipv4/tcp_vegas.c#L137">137</a>         else
<a name="L138" href="source/net/ipv4/tcp_vegas.c#L138">138</a>                 <a href="ident?i=vegas_disable">vegas_disable</a>(sk);
<a name="L139" href="source/net/ipv4/tcp_vegas.c#L139">139</a> }
<a name="L140" href="source/net/ipv4/tcp_vegas.c#L140">140</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=tcp_vegas_state">tcp_vegas_state</a>);
<a name="L141" href="source/net/ipv4/tcp_vegas.c#L141">141</a> 
<a name="L142" href="source/net/ipv4/tcp_vegas.c#L142">142</a> <b><i>/*</i></b>
<a name="L143" href="source/net/ipv4/tcp_vegas.c#L143">143</a> <b><i> * If the connection is idle and we are restarting,</i></b>
<a name="L144" href="source/net/ipv4/tcp_vegas.c#L144">144</a> <b><i> * then we don't want to do any Vegas calculations</i></b>
<a name="L145" href="source/net/ipv4/tcp_vegas.c#L145">145</a> <b><i> * until we get fresh RTT samples.  So when we</i></b>
<a name="L146" href="source/net/ipv4/tcp_vegas.c#L146">146</a> <b><i> * restart, we reset our Vegas state to a clean</i></b>
<a name="L147" href="source/net/ipv4/tcp_vegas.c#L147">147</a> <b><i> * slate. After we get acks for this flight of</i></b>
<a name="L148" href="source/net/ipv4/tcp_vegas.c#L148">148</a> <b><i> * packets, _then_ we can make Vegas calculations</i></b>
<a name="L149" href="source/net/ipv4/tcp_vegas.c#L149">149</a> <b><i> * again.</i></b>
<a name="L150" href="source/net/ipv4/tcp_vegas.c#L150">150</a> <b><i> */</i></b>
<a name="L151" href="source/net/ipv4/tcp_vegas.c#L151">151</a> void <a href="ident?i=tcp_vegas_cwnd_event">tcp_vegas_cwnd_event</a>(struct <a href="ident?i=sock">sock</a> *sk, enum <a href="ident?i=tcp_ca_event">tcp_ca_event</a> <a href="ident?i=event">event</a>)
<a name="L152" href="source/net/ipv4/tcp_vegas.c#L152">152</a> {
<a name="L153" href="source/net/ipv4/tcp_vegas.c#L153">153</a>         if (<a href="ident?i=event">event</a> == CA_EVENT_CWND_RESTART ||
<a name="L154" href="source/net/ipv4/tcp_vegas.c#L154">154</a>             <a href="ident?i=event">event</a> == CA_EVENT_TX_START)
<a name="L155" href="source/net/ipv4/tcp_vegas.c#L155">155</a>                 <a href="ident?i=tcp_vegas_init">tcp_vegas_init</a>(sk);
<a name="L156" href="source/net/ipv4/tcp_vegas.c#L156">156</a> }
<a name="L157" href="source/net/ipv4/tcp_vegas.c#L157">157</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=tcp_vegas_cwnd_event">tcp_vegas_cwnd_event</a>);
<a name="L158" href="source/net/ipv4/tcp_vegas.c#L158">158</a> 
<a name="L159" href="source/net/ipv4/tcp_vegas.c#L159">159</a> static inline <a href="ident?i=u32">u32</a> <a href="ident?i=tcp_vegas_ssthresh">tcp_vegas_ssthresh</a>(struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a>)
<a name="L160" href="source/net/ipv4/tcp_vegas.c#L160">160</a> {
<a name="L161" href="source/net/ipv4/tcp_vegas.c#L161">161</a>         return  <a href="ident?i=min">min</a>(<a href="ident?i=tp">tp</a>-&gt;snd_ssthresh, <a href="ident?i=tp">tp</a>-&gt;snd_cwnd-1);
<a name="L162" href="source/net/ipv4/tcp_vegas.c#L162">162</a> }
<a name="L163" href="source/net/ipv4/tcp_vegas.c#L163">163</a> 
<a name="L164" href="source/net/ipv4/tcp_vegas.c#L164">164</a> static void <a href="ident?i=tcp_vegas_cong_avoid">tcp_vegas_cong_avoid</a>(struct <a href="ident?i=sock">sock</a> *sk, <a href="ident?i=u32">u32</a> ack, <a href="ident?i=u32">u32</a> acked)
<a name="L165" href="source/net/ipv4/tcp_vegas.c#L165">165</a> {
<a name="L166" href="source/net/ipv4/tcp_vegas.c#L166">166</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L167" href="source/net/ipv4/tcp_vegas.c#L167">167</a>         struct <a href="ident?i=vegas">vegas</a> *<a href="ident?i=vegas">vegas</a> = <a href="ident?i=inet_csk_ca">inet_csk_ca</a>(sk);
<a name="L168" href="source/net/ipv4/tcp_vegas.c#L168">168</a> 
<a name="L169" href="source/net/ipv4/tcp_vegas.c#L169">169</a>         if (!<a href="ident?i=vegas">vegas</a>-&gt;doing_vegas_now) {
<a name="L170" href="source/net/ipv4/tcp_vegas.c#L170">170</a>                 <a href="ident?i=tcp_reno_cong_avoid">tcp_reno_cong_avoid</a>(sk, ack, acked);
<a name="L171" href="source/net/ipv4/tcp_vegas.c#L171">171</a>                 return;
<a name="L172" href="source/net/ipv4/tcp_vegas.c#L172">172</a>         }
<a name="L173" href="source/net/ipv4/tcp_vegas.c#L173">173</a> 
<a name="L174" href="source/net/ipv4/tcp_vegas.c#L174">174</a>         if (<a href="ident?i=after">after</a>(ack, <a href="ident?i=vegas">vegas</a>-&gt;beg_snd_nxt)) {
<a name="L175" href="source/net/ipv4/tcp_vegas.c#L175">175</a>                 <b><i>/* Do the Vegas once-per-RTT cwnd adjustment. */</i></b>
<a name="L176" href="source/net/ipv4/tcp_vegas.c#L176">176</a> 
<a name="L177" href="source/net/ipv4/tcp_vegas.c#L177">177</a>                 <b><i>/* Save the extent of the current window so we can use this</i></b>
<a name="L178" href="source/net/ipv4/tcp_vegas.c#L178">178</a> <b><i>                 * at the end of the next RTT.</i></b>
<a name="L179" href="source/net/ipv4/tcp_vegas.c#L179">179</a> <b><i>                 */</i></b>
<a name="L180" href="source/net/ipv4/tcp_vegas.c#L180">180</a>                 <a href="ident?i=vegas">vegas</a>-&gt;beg_snd_nxt  = <a href="ident?i=tp">tp</a>-&gt;snd_nxt;
<a name="L181" href="source/net/ipv4/tcp_vegas.c#L181">181</a> 
<a name="L182" href="source/net/ipv4/tcp_vegas.c#L182">182</a>                 <b><i>/* We do the Vegas calculations only if we got enough RTT</i></b>
<a name="L183" href="source/net/ipv4/tcp_vegas.c#L183">183</a> <b><i>                 * samples that we can be reasonably sure that we got</i></b>
<a name="L184" href="source/net/ipv4/tcp_vegas.c#L184">184</a> <b><i>                 * at least one RTT sample that wasn't from a delayed ACK.</i></b>
<a name="L185" href="source/net/ipv4/tcp_vegas.c#L185">185</a> <b><i>                 * If we only had 2 samples total,</i></b>
<a name="L186" href="source/net/ipv4/tcp_vegas.c#L186">186</a> <b><i>                 * then that means we're getting only 1 ACK per RTT, which</i></b>
<a name="L187" href="source/net/ipv4/tcp_vegas.c#L187">187</a> <b><i>                 * means they're almost certainly delayed ACKs.</i></b>
<a name="L188" href="source/net/ipv4/tcp_vegas.c#L188">188</a> <b><i>                 * If  we have 3 samples, we should be OK.</i></b>
<a name="L189" href="source/net/ipv4/tcp_vegas.c#L189">189</a> <b><i>                 */</i></b>
<a name="L190" href="source/net/ipv4/tcp_vegas.c#L190">190</a> 
<a name="L191" href="source/net/ipv4/tcp_vegas.c#L191">191</a>                 if (<a href="ident?i=vegas">vegas</a>-&gt;cntRTT &lt;= 2) {
<a name="L192" href="source/net/ipv4/tcp_vegas.c#L192">192</a>                         <b><i>/* We don't have enough RTT samples to do the Vegas</i></b>
<a name="L193" href="source/net/ipv4/tcp_vegas.c#L193">193</a> <b><i>                         * calculation, so we'll behave like Reno.</i></b>
<a name="L194" href="source/net/ipv4/tcp_vegas.c#L194">194</a> <b><i>                         */</i></b>
<a name="L195" href="source/net/ipv4/tcp_vegas.c#L195">195</a>                         <a href="ident?i=tcp_reno_cong_avoid">tcp_reno_cong_avoid</a>(sk, ack, acked);
<a name="L196" href="source/net/ipv4/tcp_vegas.c#L196">196</a>                 } else {
<a name="L197" href="source/net/ipv4/tcp_vegas.c#L197">197</a>                         <a href="ident?i=u32">u32</a> rtt, diff;
<a name="L198" href="source/net/ipv4/tcp_vegas.c#L198">198</a>                         <a href="ident?i=u64">u64</a> target_cwnd;
<a name="L199" href="source/net/ipv4/tcp_vegas.c#L199">199</a> 
<a name="L200" href="source/net/ipv4/tcp_vegas.c#L200">200</a>                         <b><i>/* We have enough RTT samples, so, using the Vegas</i></b>
<a name="L201" href="source/net/ipv4/tcp_vegas.c#L201">201</a> <b><i>                         * algorithm, we determine if we should increase or</i></b>
<a name="L202" href="source/net/ipv4/tcp_vegas.c#L202">202</a> <b><i>                         * decrease cwnd, and by how much.</i></b>
<a name="L203" href="source/net/ipv4/tcp_vegas.c#L203">203</a> <b><i>                         */</i></b>
<a name="L204" href="source/net/ipv4/tcp_vegas.c#L204">204</a> 
<a name="L205" href="source/net/ipv4/tcp_vegas.c#L205">205</a>                         <b><i>/* Pluck out the RTT we are using for the Vegas</i></b>
<a name="L206" href="source/net/ipv4/tcp_vegas.c#L206">206</a> <b><i>                         * calculations. This is the min RTT seen during the</i></b>
<a name="L207" href="source/net/ipv4/tcp_vegas.c#L207">207</a> <b><i>                         * last RTT. Taking the min filters out the effects</i></b>
<a name="L208" href="source/net/ipv4/tcp_vegas.c#L208">208</a> <b><i>                         * of delayed ACKs, at the cost of noticing congestion</i></b>
<a name="L209" href="source/net/ipv4/tcp_vegas.c#L209">209</a> <b><i>                         * a bit later.</i></b>
<a name="L210" href="source/net/ipv4/tcp_vegas.c#L210">210</a> <b><i>                         */</i></b>
<a name="L211" href="source/net/ipv4/tcp_vegas.c#L211">211</a>                         rtt = <a href="ident?i=vegas">vegas</a>-&gt;minRTT;
<a name="L212" href="source/net/ipv4/tcp_vegas.c#L212">212</a> 
<a name="L213" href="source/net/ipv4/tcp_vegas.c#L213">213</a>                         <b><i>/* Calculate the cwnd we should have, if we weren't</i></b>
<a name="L214" href="source/net/ipv4/tcp_vegas.c#L214">214</a> <b><i>                         * going too fast.</i></b>
<a name="L215" href="source/net/ipv4/tcp_vegas.c#L215">215</a> <b><i>                         *</i></b>
<a name="L216" href="source/net/ipv4/tcp_vegas.c#L216">216</a> <b><i>                         * This is:</i></b>
<a name="L217" href="source/net/ipv4/tcp_vegas.c#L217">217</a> <b><i>                         *     (actual rate in segments) * baseRTT</i></b>
<a name="L218" href="source/net/ipv4/tcp_vegas.c#L218">218</a> <b><i>                         */</i></b>
<a name="L219" href="source/net/ipv4/tcp_vegas.c#L219">219</a>                         target_cwnd = (<a href="ident?i=u64">u64</a>)<a href="ident?i=tp">tp</a>-&gt;snd_cwnd * <a href="ident?i=vegas">vegas</a>-&gt;baseRTT;
<a name="L220" href="source/net/ipv4/tcp_vegas.c#L220">220</a>                         <a href="ident?i=do_div">do_div</a>(target_cwnd, rtt);
<a name="L221" href="source/net/ipv4/tcp_vegas.c#L221">221</a> 
<a name="L222" href="source/net/ipv4/tcp_vegas.c#L222">222</a>                         <b><i>/* Calculate the difference between the window we had,</i></b>
<a name="L223" href="source/net/ipv4/tcp_vegas.c#L223">223</a> <b><i>                         * and the window we would like to have. This quantity</i></b>
<a name="L224" href="source/net/ipv4/tcp_vegas.c#L224">224</a> <b><i>                         * is the "Diff" from the Arizona Vegas papers.</i></b>
<a name="L225" href="source/net/ipv4/tcp_vegas.c#L225">225</a> <b><i>                         */</i></b>
<a name="L226" href="source/net/ipv4/tcp_vegas.c#L226">226</a>                         diff = <a href="ident?i=tp">tp</a>-&gt;snd_cwnd * (rtt-<a href="ident?i=vegas">vegas</a>-&gt;baseRTT) / <a href="ident?i=vegas">vegas</a>-&gt;baseRTT;
<a name="L227" href="source/net/ipv4/tcp_vegas.c#L227">227</a> 
<a name="L228" href="source/net/ipv4/tcp_vegas.c#L228">228</a>                         if (diff &gt; <a href="ident?i=gamma">gamma</a> &amp;&amp; <a href="ident?i=tp">tp</a>-&gt;snd_cwnd &lt;= <a href="ident?i=tp">tp</a>-&gt;snd_ssthresh) {
<a name="L229" href="source/net/ipv4/tcp_vegas.c#L229">229</a>                                 <b><i>/* Going too fast. Time to slow down</i></b>
<a name="L230" href="source/net/ipv4/tcp_vegas.c#L230">230</a> <b><i>                                 * and switch to congestion avoidance.</i></b>
<a name="L231" href="source/net/ipv4/tcp_vegas.c#L231">231</a> <b><i>                                 */</i></b>
<a name="L232" href="source/net/ipv4/tcp_vegas.c#L232">232</a> 
<a name="L233" href="source/net/ipv4/tcp_vegas.c#L233">233</a>                                 <b><i>/* Set cwnd to match the actual rate</i></b>
<a name="L234" href="source/net/ipv4/tcp_vegas.c#L234">234</a> <b><i>                                 * exactly:</i></b>
<a name="L235" href="source/net/ipv4/tcp_vegas.c#L235">235</a> <b><i>                                 *   cwnd = (actual rate) * baseRTT</i></b>
<a name="L236" href="source/net/ipv4/tcp_vegas.c#L236">236</a> <b><i>                                 * Then we add 1 because the integer</i></b>
<a name="L237" href="source/net/ipv4/tcp_vegas.c#L237">237</a> <b><i>                                 * truncation robs us of full link</i></b>
<a name="L238" href="source/net/ipv4/tcp_vegas.c#L238">238</a> <b><i>                                 * utilization.</i></b>
<a name="L239" href="source/net/ipv4/tcp_vegas.c#L239">239</a> <b><i>                                 */</i></b>
<a name="L240" href="source/net/ipv4/tcp_vegas.c#L240">240</a>                                 <a href="ident?i=tp">tp</a>-&gt;snd_cwnd = <a href="ident?i=min">min</a>(<a href="ident?i=tp">tp</a>-&gt;snd_cwnd, (<a href="ident?i=u32">u32</a>)target_cwnd+1);
<a name="L241" href="source/net/ipv4/tcp_vegas.c#L241">241</a>                                 <a href="ident?i=tp">tp</a>-&gt;snd_ssthresh = <a href="ident?i=tcp_vegas_ssthresh">tcp_vegas_ssthresh</a>(<a href="ident?i=tp">tp</a>);
<a name="L242" href="source/net/ipv4/tcp_vegas.c#L242">242</a> 
<a name="L243" href="source/net/ipv4/tcp_vegas.c#L243">243</a>                         } else if (<a href="ident?i=tp">tp</a>-&gt;snd_cwnd &lt;= <a href="ident?i=tp">tp</a>-&gt;snd_ssthresh) {
<a name="L244" href="source/net/ipv4/tcp_vegas.c#L244">244</a>                                 <b><i>/* Slow start.  */</i></b>
<a name="L245" href="source/net/ipv4/tcp_vegas.c#L245">245</a>                                 <a href="ident?i=tcp_slow_start">tcp_slow_start</a>(<a href="ident?i=tp">tp</a>, acked);
<a name="L246" href="source/net/ipv4/tcp_vegas.c#L246">246</a>                         } else {
<a name="L247" href="source/net/ipv4/tcp_vegas.c#L247">247</a>                                 <b><i>/* Congestion avoidance. */</i></b>
<a name="L248" href="source/net/ipv4/tcp_vegas.c#L248">248</a> 
<a name="L249" href="source/net/ipv4/tcp_vegas.c#L249">249</a>                                 <b><i>/* Figure out where we would like cwnd</i></b>
<a name="L250" href="source/net/ipv4/tcp_vegas.c#L250">250</a> <b><i>                                 * to be.</i></b>
<a name="L251" href="source/net/ipv4/tcp_vegas.c#L251">251</a> <b><i>                                 */</i></b>
<a name="L252" href="source/net/ipv4/tcp_vegas.c#L252">252</a>                                 if (diff &gt; <a href="ident?i=beta">beta</a>) {
<a name="L253" href="source/net/ipv4/tcp_vegas.c#L253">253</a>                                         <b><i>/* The old window was too fast, so</i></b>
<a name="L254" href="source/net/ipv4/tcp_vegas.c#L254">254</a> <b><i>                                         * we slow down.</i></b>
<a name="L255" href="source/net/ipv4/tcp_vegas.c#L255">255</a> <b><i>                                         */</i></b>
<a name="L256" href="source/net/ipv4/tcp_vegas.c#L256">256</a>                                         <a href="ident?i=tp">tp</a>-&gt;snd_cwnd--;
<a name="L257" href="source/net/ipv4/tcp_vegas.c#L257">257</a>                                         <a href="ident?i=tp">tp</a>-&gt;snd_ssthresh
<a name="L258" href="source/net/ipv4/tcp_vegas.c#L258">258</a>                                                 = <a href="ident?i=tcp_vegas_ssthresh">tcp_vegas_ssthresh</a>(<a href="ident?i=tp">tp</a>);
<a name="L259" href="source/net/ipv4/tcp_vegas.c#L259">259</a>                                 } else if (diff &lt; <a href="ident?i=alpha">alpha</a>) {
<a name="L260" href="source/net/ipv4/tcp_vegas.c#L260">260</a>                                         <b><i>/* We don't have enough extra packets</i></b>
<a name="L261" href="source/net/ipv4/tcp_vegas.c#L261">261</a> <b><i>                                         * in the network, so speed up.</i></b>
<a name="L262" href="source/net/ipv4/tcp_vegas.c#L262">262</a> <b><i>                                         */</i></b>
<a name="L263" href="source/net/ipv4/tcp_vegas.c#L263">263</a>                                         <a href="ident?i=tp">tp</a>-&gt;snd_cwnd++;
<a name="L264" href="source/net/ipv4/tcp_vegas.c#L264">264</a>                                 } else {
<a name="L265" href="source/net/ipv4/tcp_vegas.c#L265">265</a>                                         <b><i>/* Sending just as fast as we</i></b>
<a name="L266" href="source/net/ipv4/tcp_vegas.c#L266">266</a> <b><i>                                         * should be.</i></b>
<a name="L267" href="source/net/ipv4/tcp_vegas.c#L267">267</a> <b><i>                                         */</i></b>
<a name="L268" href="source/net/ipv4/tcp_vegas.c#L268">268</a>                                 }
<a name="L269" href="source/net/ipv4/tcp_vegas.c#L269">269</a>                         }
<a name="L270" href="source/net/ipv4/tcp_vegas.c#L270">270</a> 
<a name="L271" href="source/net/ipv4/tcp_vegas.c#L271">271</a>                         if (<a href="ident?i=tp">tp</a>-&gt;snd_cwnd &lt; 2)
<a name="L272" href="source/net/ipv4/tcp_vegas.c#L272">272</a>                                 <a href="ident?i=tp">tp</a>-&gt;snd_cwnd = 2;
<a name="L273" href="source/net/ipv4/tcp_vegas.c#L273">273</a>                         else if (<a href="ident?i=tp">tp</a>-&gt;snd_cwnd &gt; <a href="ident?i=tp">tp</a>-&gt;snd_cwnd_clamp)
<a name="L274" href="source/net/ipv4/tcp_vegas.c#L274">274</a>                                 <a href="ident?i=tp">tp</a>-&gt;snd_cwnd = <a href="ident?i=tp">tp</a>-&gt;snd_cwnd_clamp;
<a name="L275" href="source/net/ipv4/tcp_vegas.c#L275">275</a> 
<a name="L276" href="source/net/ipv4/tcp_vegas.c#L276">276</a>                         <a href="ident?i=tp">tp</a>-&gt;snd_ssthresh = <a href="ident?i=tcp_current_ssthresh">tcp_current_ssthresh</a>(sk);
<a name="L277" href="source/net/ipv4/tcp_vegas.c#L277">277</a>                 }
<a name="L278" href="source/net/ipv4/tcp_vegas.c#L278">278</a> 
<a name="L279" href="source/net/ipv4/tcp_vegas.c#L279">279</a>                 <b><i>/* Wipe the slate clean for the next RTT. */</i></b>
<a name="L280" href="source/net/ipv4/tcp_vegas.c#L280">280</a>                 <a href="ident?i=vegas">vegas</a>-&gt;cntRTT = 0;
<a name="L281" href="source/net/ipv4/tcp_vegas.c#L281">281</a>                 <a href="ident?i=vegas">vegas</a>-&gt;minRTT = 0x7fffffff;
<a name="L282" href="source/net/ipv4/tcp_vegas.c#L282">282</a>         }
<a name="L283" href="source/net/ipv4/tcp_vegas.c#L283">283</a>         <b><i>/* Use normal slow start */</i></b>
<a name="L284" href="source/net/ipv4/tcp_vegas.c#L284">284</a>         else if (<a href="ident?i=tp">tp</a>-&gt;snd_cwnd &lt;= <a href="ident?i=tp">tp</a>-&gt;snd_ssthresh)
<a name="L285" href="source/net/ipv4/tcp_vegas.c#L285">285</a>                 <a href="ident?i=tcp_slow_start">tcp_slow_start</a>(<a href="ident?i=tp">tp</a>, acked);
<a name="L286" href="source/net/ipv4/tcp_vegas.c#L286">286</a> }
<a name="L287" href="source/net/ipv4/tcp_vegas.c#L287">287</a> 
<a name="L288" href="source/net/ipv4/tcp_vegas.c#L288">288</a> <b><i>/* Extract info for Tcp socket info provided via netlink. */</i></b>
<a name="L289" href="source/net/ipv4/tcp_vegas.c#L289">289</a> <a href="ident?i=size_t">size_t</a> <a href="ident?i=tcp_vegas_get_info">tcp_vegas_get_info</a>(struct <a href="ident?i=sock">sock</a> *sk, <a href="ident?i=u32">u32</a> ext, int *<a href="ident?i=attr">attr</a>,
<a name="L290" href="source/net/ipv4/tcp_vegas.c#L290">290</a>                           union <a href="ident?i=tcp_cc_info">tcp_cc_info</a> *<a href="ident?i=info">info</a>)
<a name="L291" href="source/net/ipv4/tcp_vegas.c#L291">291</a> {
<a name="L292" href="source/net/ipv4/tcp_vegas.c#L292">292</a>         const struct <a href="ident?i=vegas">vegas</a> *<a href="ident?i=ca">ca</a> = <a href="ident?i=inet_csk_ca">inet_csk_ca</a>(sk);
<a name="L293" href="source/net/ipv4/tcp_vegas.c#L293">293</a> 
<a name="L294" href="source/net/ipv4/tcp_vegas.c#L294">294</a>         if (ext &amp; (1 &lt;&lt; (INET_DIAG_VEGASINFO - 1))) {
<a name="L295" href="source/net/ipv4/tcp_vegas.c#L295">295</a>                 <a href="ident?i=info">info</a>-&gt;<a href="ident?i=vegas">vegas</a>.tcpv_enabled = <a href="ident?i=ca">ca</a>-&gt;doing_vegas_now,
<a name="L296" href="source/net/ipv4/tcp_vegas.c#L296">296</a>                 <a href="ident?i=info">info</a>-&gt;<a href="ident?i=vegas">vegas</a>.tcpv_rttcnt = <a href="ident?i=ca">ca</a>-&gt;cntRTT,
<a name="L297" href="source/net/ipv4/tcp_vegas.c#L297">297</a>                 <a href="ident?i=info">info</a>-&gt;<a href="ident?i=vegas">vegas</a>.tcpv_rtt = <a href="ident?i=ca">ca</a>-&gt;baseRTT,
<a name="L298" href="source/net/ipv4/tcp_vegas.c#L298">298</a>                 <a href="ident?i=info">info</a>-&gt;<a href="ident?i=vegas">vegas</a>.tcpv_minrtt = <a href="ident?i=ca">ca</a>-&gt;minRTT,
<a name="L299" href="source/net/ipv4/tcp_vegas.c#L299">299</a> 
<a name="L300" href="source/net/ipv4/tcp_vegas.c#L300">300</a>                 *<a href="ident?i=attr">attr</a> = INET_DIAG_VEGASINFO;
<a name="L301" href="source/net/ipv4/tcp_vegas.c#L301">301</a>                 return sizeof(struct <a href="ident?i=tcpvegas_info">tcpvegas_info</a>);
<a name="L302" href="source/net/ipv4/tcp_vegas.c#L302">302</a>         }
<a name="L303" href="source/net/ipv4/tcp_vegas.c#L303">303</a>         return 0;
<a name="L304" href="source/net/ipv4/tcp_vegas.c#L304">304</a> }
<a name="L305" href="source/net/ipv4/tcp_vegas.c#L305">305</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=tcp_vegas_get_info">tcp_vegas_get_info</a>);
<a name="L306" href="source/net/ipv4/tcp_vegas.c#L306">306</a> 
<a name="L307" href="source/net/ipv4/tcp_vegas.c#L307">307</a> static struct <a href="ident?i=tcp_congestion_ops">tcp_congestion_ops</a> tcp_vegas <a href="ident?i=__read_mostly">__read_mostly</a> = {
<a name="L308" href="source/net/ipv4/tcp_vegas.c#L308">308</a>         .<a href="ident?i=init">init</a>           = <a href="ident?i=tcp_vegas_init">tcp_vegas_init</a>,
<a name="L309" href="source/net/ipv4/tcp_vegas.c#L309">309</a>         .ssthresh       = <a href="ident?i=tcp_reno_ssthresh">tcp_reno_ssthresh</a>,
<a name="L310" href="source/net/ipv4/tcp_vegas.c#L310">310</a>         .cong_avoid     = <a href="ident?i=tcp_vegas_cong_avoid">tcp_vegas_cong_avoid</a>,
<a name="L311" href="source/net/ipv4/tcp_vegas.c#L311">311</a>         .pkts_acked     = <a href="ident?i=tcp_vegas_pkts_acked">tcp_vegas_pkts_acked</a>,
<a name="L312" href="source/net/ipv4/tcp_vegas.c#L312">312</a>         .<a href="ident?i=set_state">set_state</a>      = <a href="ident?i=tcp_vegas_state">tcp_vegas_state</a>,
<a name="L313" href="source/net/ipv4/tcp_vegas.c#L313">313</a>         .cwnd_event     = <a href="ident?i=tcp_vegas_cwnd_event">tcp_vegas_cwnd_event</a>,
<a name="L314" href="source/net/ipv4/tcp_vegas.c#L314">314</a>         .<a href="ident?i=get_info">get_info</a>       = <a href="ident?i=tcp_vegas_get_info">tcp_vegas_get_info</a>,
<a name="L315" href="source/net/ipv4/tcp_vegas.c#L315">315</a> 
<a name="L316" href="source/net/ipv4/tcp_vegas.c#L316">316</a>         .owner          = <a href="ident?i=THIS_MODULE">THIS_MODULE</a>,
<a name="L317" href="source/net/ipv4/tcp_vegas.c#L317">317</a>         .<a href="ident?i=name">name</a>           = <i>"vegas"</i>,
<a name="L318" href="source/net/ipv4/tcp_vegas.c#L318">318</a> };
<a name="L319" href="source/net/ipv4/tcp_vegas.c#L319">319</a> 
<a name="L320" href="source/net/ipv4/tcp_vegas.c#L320">320</a> static int <a href="ident?i=__init">__init</a> <a href="ident?i=tcp_vegas_register">tcp_vegas_register</a>(void)
<a name="L321" href="source/net/ipv4/tcp_vegas.c#L321">321</a> {
<a name="L322" href="source/net/ipv4/tcp_vegas.c#L322">322</a>         <a href="ident?i=BUILD_BUG_ON">BUILD_BUG_ON</a>(sizeof(struct <a href="ident?i=vegas">vegas</a>) &gt; <a href="ident?i=ICSK_CA_PRIV_SIZE">ICSK_CA_PRIV_SIZE</a>);
<a name="L323" href="source/net/ipv4/tcp_vegas.c#L323">323</a>         <a href="ident?i=tcp_register_congestion_control">tcp_register_congestion_control</a>(&amp;tcp_vegas);
<a name="L324" href="source/net/ipv4/tcp_vegas.c#L324">324</a>         return 0;
<a name="L325" href="source/net/ipv4/tcp_vegas.c#L325">325</a> }
<a name="L326" href="source/net/ipv4/tcp_vegas.c#L326">326</a> 
<a name="L327" href="source/net/ipv4/tcp_vegas.c#L327">327</a> static void <a href="ident?i=__exit">__exit</a> <a href="ident?i=tcp_vegas_unregister">tcp_vegas_unregister</a>(void)
<a name="L328" href="source/net/ipv4/tcp_vegas.c#L328">328</a> {
<a name="L329" href="source/net/ipv4/tcp_vegas.c#L329">329</a>         <a href="ident?i=tcp_unregister_congestion_control">tcp_unregister_congestion_control</a>(&amp;tcp_vegas);
<a name="L330" href="source/net/ipv4/tcp_vegas.c#L330">330</a> }
<a name="L331" href="source/net/ipv4/tcp_vegas.c#L331">331</a> 
<a name="L332" href="source/net/ipv4/tcp_vegas.c#L332">332</a> <a href="ident?i=module_init">module_init</a>(<a href="ident?i=tcp_vegas_register">tcp_vegas_register</a>);
<a name="L333" href="source/net/ipv4/tcp_vegas.c#L333">333</a> <a href="ident?i=module_exit">module_exit</a>(<a href="ident?i=tcp_vegas_unregister">tcp_vegas_unregister</a>);
<a name="L334" href="source/net/ipv4/tcp_vegas.c#L334">334</a> 
<a name="L335" href="source/net/ipv4/tcp_vegas.c#L335">335</a> <a href="ident?i=MODULE_AUTHOR">MODULE_AUTHOR</a>(<i>"Stephen Hemminger"</i>);
<a name="L336" href="source/net/ipv4/tcp_vegas.c#L336">336</a> <a href="ident?i=MODULE_LICENSE">MODULE_LICENSE</a>(<i>"GPL"</i>);
<a name="L337" href="source/net/ipv4/tcp_vegas.c#L337">337</a> <a href="ident?i=MODULE_DESCRIPTION">MODULE_DESCRIPTION</a>(<i>"TCP Vegas"</i>);
<a name="L338" href="source/net/ipv4/tcp_vegas.c#L338">338</a> </pre></div><p>
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
