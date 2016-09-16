<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title>Linux/net/ipv4/tcp_input.c - Linux Cross Reference - Free Electrons</title>
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
		 &nbsp;&bull;&nbsp;<b><i>source navigation</i></b> &nbsp;&bull;&nbsp;<a href="diff/net/ipv4/tcp_input.c">diff markup</a> &nbsp;&bull;&nbsp;<a href="ident">identifier search</a> &nbsp;&bull;&nbsp;<a href="search">freetext search</a> &nbsp;&bull;&nbsp;
		</p>
	</div>
</div>

<div id="topbar">
  
  <p>Version: &nbsp;<a href="source/net/ipv4/tcp_input.c?v=2.0.40">2.0.40</a>&nbsp;<a href="source/net/ipv4/tcp_input.c?v=2.2.26">2.2.26</a>&nbsp;<a href="source/net/ipv4/tcp_input.c?v=2.4.37">2.4.37</a>&nbsp;<a href="source/net/ipv4/tcp_input.c?v=3.5">3.5</a>&nbsp;<a href="source/net/ipv4/tcp_input.c?v=3.6">3.6</a>&nbsp;<a href="source/net/ipv4/tcp_input.c?v=3.7">3.7</a>&nbsp;<a href="source/net/ipv4/tcp_input.c?v=3.8">3.8</a>&nbsp;<a href="source/net/ipv4/tcp_input.c?v=3.9">3.9</a>&nbsp;<a href="source/net/ipv4/tcp_input.c?v=3.10">3.10</a>&nbsp;<a href="source/net/ipv4/tcp_input.c?v=3.11">3.11</a>&nbsp;<a href="source/net/ipv4/tcp_input.c?v=3.12">3.12</a>&nbsp;<a href="source/net/ipv4/tcp_input.c?v=3.13">3.13</a>&nbsp;<a href="source/net/ipv4/tcp_input.c?v=3.14">3.14</a>&nbsp;<a href="source/net/ipv4/tcp_input.c?v=3.15">3.15</a>&nbsp;<a href="source/net/ipv4/tcp_input.c?v=3.16">3.16</a>&nbsp;<a href="source/net/ipv4/tcp_input.c?v=3.17">3.17</a>&nbsp;<a href="source/net/ipv4/tcp_input.c?v=3.18">3.18</a>&nbsp;<a href="source/net/ipv4/tcp_input.c?v=3.19">3.19</a>&nbsp;<a href="source/net/ipv4/tcp_input.c?v=4.0">4.0</a>&nbsp;<b><i>4.1</i></b></p>
  
</div>

<h1><a href="source/">Linux</a>/<a href="source/net/">net</a>/<a href="source/net/ipv4/">ipv4</a>/<a href="source/net/ipv4/tcp_input.c">tcp_input.c</a></h1>
<div id="lxrcode"><pre>  <a name="L1" href="source/net/ipv4/tcp_input.c#L1">1</a> <b><i>/*</i></b>
  <a name="L2" href="source/net/ipv4/tcp_input.c#L2">2</a> <b><i> * INET         An implementation of the TCP/IP protocol suite for the LINUX</i></b>
  <a name="L3" href="source/net/ipv4/tcp_input.c#L3">3</a> <b><i> *              operating system.  INET is implemented using the  BSD Socket</i></b>
  <a name="L4" href="source/net/ipv4/tcp_input.c#L4">4</a> <b><i> *              interface as the means of communication with the user level.</i></b>
  <a name="L5" href="source/net/ipv4/tcp_input.c#L5">5</a> <b><i> *</i></b>
  <a name="L6" href="source/net/ipv4/tcp_input.c#L6">6</a> <b><i> *              Implementation of the Transmission Control Protocol(TCP).</i></b>
  <a name="L7" href="source/net/ipv4/tcp_input.c#L7">7</a> <b><i> *</i></b>
  <a name="L8" href="source/net/ipv4/tcp_input.c#L8">8</a> <b><i> * Authors:     Ross Biro</i></b>
  <a name="L9" href="source/net/ipv4/tcp_input.c#L9">9</a> <b><i> *              Fred N. van Kempen, &lt;waltje@uWalt.NL.Mugnet.ORG&gt;</i></b>
 <a name="L10" href="source/net/ipv4/tcp_input.c#L10">10</a> <b><i> *              Mark Evans, &lt;evansmp@uhura.aston.ac.uk&gt;</i></b>
 <a name="L11" href="source/net/ipv4/tcp_input.c#L11">11</a> <b><i> *              Corey Minyard &lt;wf-rch!minyard@relay.EU.net&gt;</i></b>
 <a name="L12" href="source/net/ipv4/tcp_input.c#L12">12</a> <b><i> *              Florian La Roche, &lt;flla@stud.uni-sb.de&gt;</i></b>
 <a name="L13" href="source/net/ipv4/tcp_input.c#L13">13</a> <b><i> *              Charles Hedrick, &lt;hedrick@klinzhai.rutgers.edu&gt;</i></b>
 <a name="L14" href="source/net/ipv4/tcp_input.c#L14">14</a> <b><i> *              Linus Torvalds, &lt;torvalds@cs.helsinki.fi&gt;</i></b>
 <a name="L15" href="source/net/ipv4/tcp_input.c#L15">15</a> <b><i> *              Alan Cox, &lt;gw4pts@gw4pts.ampr.org&gt;</i></b>
 <a name="L16" href="source/net/ipv4/tcp_input.c#L16">16</a> <b><i> *              Matthew Dillon, &lt;dillon@apollo.west.oic.com&gt;</i></b>
 <a name="L17" href="source/net/ipv4/tcp_input.c#L17">17</a> <b><i> *              Arnt Gulbrandsen, &lt;agulbra@nvg.unit.no&gt;</i></b>
 <a name="L18" href="source/net/ipv4/tcp_input.c#L18">18</a> <b><i> *              Jorge Cwik, &lt;jorge@laser.satlink.net&gt;</i></b>
 <a name="L19" href="source/net/ipv4/tcp_input.c#L19">19</a> <b><i> */</i></b>
 <a name="L20" href="source/net/ipv4/tcp_input.c#L20">20</a> 
 <a name="L21" href="source/net/ipv4/tcp_input.c#L21">21</a> <b><i>/*</i></b>
 <a name="L22" href="source/net/ipv4/tcp_input.c#L22">22</a> <b><i> * Changes:</i></b>
 <a name="L23" href="source/net/ipv4/tcp_input.c#L23">23</a> <b><i> *              Pedro Roque     :       Fast Retransmit/Recovery.</i></b>
 <a name="L24" href="source/net/ipv4/tcp_input.c#L24">24</a> <b><i> *                                      Two receive queues.</i></b>
 <a name="L25" href="source/net/ipv4/tcp_input.c#L25">25</a> <b><i> *                                      Retransmit queue handled by TCP.</i></b>
 <a name="L26" href="source/net/ipv4/tcp_input.c#L26">26</a> <b><i> *                                      Better retransmit timer handling.</i></b>
 <a name="L27" href="source/net/ipv4/tcp_input.c#L27">27</a> <b><i> *                                      New congestion avoidance.</i></b>
 <a name="L28" href="source/net/ipv4/tcp_input.c#L28">28</a> <b><i> *                                      Header prediction.</i></b>
 <a name="L29" href="source/net/ipv4/tcp_input.c#L29">29</a> <b><i> *                                      Variable renaming.</i></b>
 <a name="L30" href="source/net/ipv4/tcp_input.c#L30">30</a> <b><i> *</i></b>
 <a name="L31" href="source/net/ipv4/tcp_input.c#L31">31</a> <b><i> *              Eric            :       Fast Retransmit.</i></b>
 <a name="L32" href="source/net/ipv4/tcp_input.c#L32">32</a> <b><i> *              Randy Scott     :       MSS option defines.</i></b>
 <a name="L33" href="source/net/ipv4/tcp_input.c#L33">33</a> <b><i> *              Eric Schenk     :       Fixes to slow start algorithm.</i></b>
 <a name="L34" href="source/net/ipv4/tcp_input.c#L34">34</a> <b><i> *              Eric Schenk     :       Yet another double ACK bug.</i></b>
 <a name="L35" href="source/net/ipv4/tcp_input.c#L35">35</a> <b><i> *              Eric Schenk     :       Delayed ACK bug fixes.</i></b>
 <a name="L36" href="source/net/ipv4/tcp_input.c#L36">36</a> <b><i> *              Eric Schenk     :       Floyd style fast retrans war avoidance.</i></b>
 <a name="L37" href="source/net/ipv4/tcp_input.c#L37">37</a> <b><i> *              David S. Miller :       Don't allow zero congestion window.</i></b>
 <a name="L38" href="source/net/ipv4/tcp_input.c#L38">38</a> <b><i> *              Eric Schenk     :       Fix retransmitter so that it sends</i></b>
 <a name="L39" href="source/net/ipv4/tcp_input.c#L39">39</a> <b><i> *                                      next packet on ack of previous packet.</i></b>
 <a name="L40" href="source/net/ipv4/tcp_input.c#L40">40</a> <b><i> *              Andi Kleen      :       Moved open_request checking here</i></b>
 <a name="L41" href="source/net/ipv4/tcp_input.c#L41">41</a> <b><i> *                                      and process RSTs for open_requests.</i></b>
 <a name="L42" href="source/net/ipv4/tcp_input.c#L42">42</a> <b><i> *              Andi Kleen      :       Better prune_queue, and other fixes.</i></b>
 <a name="L43" href="source/net/ipv4/tcp_input.c#L43">43</a> <b><i> *              Andrey Savochkin:       Fix RTT measurements in the presence of</i></b>
 <a name="L44" href="source/net/ipv4/tcp_input.c#L44">44</a> <b><i> *                                      timestamps.</i></b>
 <a name="L45" href="source/net/ipv4/tcp_input.c#L45">45</a> <b><i> *              Andrey Savochkin:       Check sequence numbers correctly when</i></b>
 <a name="L46" href="source/net/ipv4/tcp_input.c#L46">46</a> <b><i> *                                      removing SACKs due to in sequence incoming</i></b>
 <a name="L47" href="source/net/ipv4/tcp_input.c#L47">47</a> <b><i> *                                      data segments.</i></b>
 <a name="L48" href="source/net/ipv4/tcp_input.c#L48">48</a> <b><i> *              Andi Kleen:             Make sure we never ack data there is not</i></b>
 <a name="L49" href="source/net/ipv4/tcp_input.c#L49">49</a> <b><i> *                                      enough room for. Also make this condition</i></b>
 <a name="L50" href="source/net/ipv4/tcp_input.c#L50">50</a> <b><i> *                                      a fatal error if it might still happen.</i></b>
 <a name="L51" href="source/net/ipv4/tcp_input.c#L51">51</a> <b><i> *              Andi Kleen:             Add tcp_measure_rcv_mss to make</i></b>
 <a name="L52" href="source/net/ipv4/tcp_input.c#L52">52</a> <b><i> *                                      connections with MSS&lt;min(MTU,ann. MSS)</i></b>
 <a name="L53" href="source/net/ipv4/tcp_input.c#L53">53</a> <b><i> *                                      work without delayed acks.</i></b>
 <a name="L54" href="source/net/ipv4/tcp_input.c#L54">54</a> <b><i> *              Andi Kleen:             Process packets with PSH set in the</i></b>
 <a name="L55" href="source/net/ipv4/tcp_input.c#L55">55</a> <b><i> *                                      fast path.</i></b>
 <a name="L56" href="source/net/ipv4/tcp_input.c#L56">56</a> <b><i> *              J Hadi Salim:           ECN support</i></b>
 <a name="L57" href="source/net/ipv4/tcp_input.c#L57">57</a> <b><i> *              Andrei Gurtov,</i></b>
 <a name="L58" href="source/net/ipv4/tcp_input.c#L58">58</a> <b><i> *              Pasi Sarolahti,</i></b>
 <a name="L59" href="source/net/ipv4/tcp_input.c#L59">59</a> <b><i> *              Panu Kuhlberg:          Experimental audit of TCP (re)transmission</i></b>
 <a name="L60" href="source/net/ipv4/tcp_input.c#L60">60</a> <b><i> *                                      engine. Lots of bugs are found.</i></b>
 <a name="L61" href="source/net/ipv4/tcp_input.c#L61">61</a> <b><i> *              Pasi Sarolahti:         F-RTO for dealing with spurious RTOs</i></b>
 <a name="L62" href="source/net/ipv4/tcp_input.c#L62">62</a> <b><i> */</i></b>
 <a name="L63" href="source/net/ipv4/tcp_input.c#L63">63</a> 
 <a name="L64" href="source/net/ipv4/tcp_input.c#L64">64</a> #define <a href="ident?i=pr_fmt">pr_fmt</a>(<a href="ident?i=fmt">fmt</a>) <i>"TCP: "</i> <a href="ident?i=fmt">fmt</a>
 <a name="L65" href="source/net/ipv4/tcp_input.c#L65">65</a> 
 <a name="L66" href="source/net/ipv4/tcp_input.c#L66">66</a> #include &lt;linux/mm.h&gt;
 <a name="L67" href="source/net/ipv4/tcp_input.c#L67">67</a> #include &lt;linux/slab.h&gt;
 <a name="L68" href="source/net/ipv4/tcp_input.c#L68">68</a> #include &lt;linux/module.h&gt;
 <a name="L69" href="source/net/ipv4/tcp_input.c#L69">69</a> #include &lt;linux/sysctl.h&gt;
 <a name="L70" href="source/net/ipv4/tcp_input.c#L70">70</a> #include &lt;linux/kernel.h&gt;
 <a name="L71" href="source/net/ipv4/tcp_input.c#L71">71</a> #include &lt;linux/prefetch.h&gt;
 <a name="L72" href="source/net/ipv4/tcp_input.c#L72">72</a> #include &lt;net/dst.h&gt;
 <a name="L73" href="source/net/ipv4/tcp_input.c#L73">73</a> #include &lt;net/tcp.h&gt;
 <a name="L74" href="source/net/ipv4/tcp_input.c#L74">74</a> #include &lt;net/inet_common.h&gt;
 <a name="L75" href="source/net/ipv4/tcp_input.c#L75">75</a> #include &lt;linux/ipsec.h&gt;
 <a name="L76" href="source/net/ipv4/tcp_input.c#L76">76</a> #include &lt;asm/unaligned.h&gt;
 <a name="L77" href="source/net/ipv4/tcp_input.c#L77">77</a> #include &lt;linux/errqueue.h&gt;
 <a name="L78" href="source/net/ipv4/tcp_input.c#L78">78</a> 
 <a name="L79" href="source/net/ipv4/tcp_input.c#L79">79</a> int <a href="ident?i=sysctl_tcp_timestamps">sysctl_tcp_timestamps</a> <a href="ident?i=__read_mostly">__read_mostly</a> = 1;
 <a name="L80" href="source/net/ipv4/tcp_input.c#L80">80</a> int <a href="ident?i=sysctl_tcp_window_scaling">sysctl_tcp_window_scaling</a> <a href="ident?i=__read_mostly">__read_mostly</a> = 1;
 <a name="L81" href="source/net/ipv4/tcp_input.c#L81">81</a> int <a href="ident?i=sysctl_tcp_sack">sysctl_tcp_sack</a> <a href="ident?i=__read_mostly">__read_mostly</a> = 1;
 <a name="L82" href="source/net/ipv4/tcp_input.c#L82">82</a> int <a href="ident?i=sysctl_tcp_fack">sysctl_tcp_fack</a> <a href="ident?i=__read_mostly">__read_mostly</a> = 1;
 <a name="L83" href="source/net/ipv4/tcp_input.c#L83">83</a> int <a href="ident?i=sysctl_tcp_reordering">sysctl_tcp_reordering</a> <a href="ident?i=__read_mostly">__read_mostly</a> = <a href="ident?i=TCP_FASTRETRANS_THRESH">TCP_FASTRETRANS_THRESH</a>;
 <a name="L84" href="source/net/ipv4/tcp_input.c#L84">84</a> int <a href="ident?i=sysctl_tcp_max_reordering">sysctl_tcp_max_reordering</a> <a href="ident?i=__read_mostly">__read_mostly</a> = 300;
 <a name="L85" href="source/net/ipv4/tcp_input.c#L85">85</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=sysctl_tcp_reordering">sysctl_tcp_reordering</a>);
 <a name="L86" href="source/net/ipv4/tcp_input.c#L86">86</a> int <a href="ident?i=sysctl_tcp_dsack">sysctl_tcp_dsack</a> <a href="ident?i=__read_mostly">__read_mostly</a> = 1;
 <a name="L87" href="source/net/ipv4/tcp_input.c#L87">87</a> int <a href="ident?i=sysctl_tcp_app_win">sysctl_tcp_app_win</a> <a href="ident?i=__read_mostly">__read_mostly</a> = 31;
 <a name="L88" href="source/net/ipv4/tcp_input.c#L88">88</a> int <a href="ident?i=sysctl_tcp_adv_win_scale">sysctl_tcp_adv_win_scale</a> <a href="ident?i=__read_mostly">__read_mostly</a> = 1;
 <a name="L89" href="source/net/ipv4/tcp_input.c#L89">89</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=sysctl_tcp_adv_win_scale">sysctl_tcp_adv_win_scale</a>);
 <a name="L90" href="source/net/ipv4/tcp_input.c#L90">90</a> 
 <a name="L91" href="source/net/ipv4/tcp_input.c#L91">91</a> <b><i>/* rfc5961 challenge ack rate limiting */</i></b>
 <a name="L92" href="source/net/ipv4/tcp_input.c#L92">92</a> int <a href="ident?i=sysctl_tcp_challenge_ack_limit">sysctl_tcp_challenge_ack_limit</a> = 100;
 <a name="L93" href="source/net/ipv4/tcp_input.c#L93">93</a> 
 <a name="L94" href="source/net/ipv4/tcp_input.c#L94">94</a> int <a href="ident?i=sysctl_tcp_stdurg">sysctl_tcp_stdurg</a> <a href="ident?i=__read_mostly">__read_mostly</a>;
 <a name="L95" href="source/net/ipv4/tcp_input.c#L95">95</a> int <a href="ident?i=sysctl_tcp_rfc1337">sysctl_tcp_rfc1337</a> <a href="ident?i=__read_mostly">__read_mostly</a>;
 <a name="L96" href="source/net/ipv4/tcp_input.c#L96">96</a> int <a href="ident?i=sysctl_tcp_max_orphans">sysctl_tcp_max_orphans</a> <a href="ident?i=__read_mostly">__read_mostly</a> = <a href="ident?i=NR_FILE">NR_FILE</a>;
 <a name="L97" href="source/net/ipv4/tcp_input.c#L97">97</a> int <a href="ident?i=sysctl_tcp_frto">sysctl_tcp_frto</a> <a href="ident?i=__read_mostly">__read_mostly</a> = 2;
 <a name="L98" href="source/net/ipv4/tcp_input.c#L98">98</a> 
 <a name="L99" href="source/net/ipv4/tcp_input.c#L99">99</a> int <a href="ident?i=sysctl_tcp_thin_dupack">sysctl_tcp_thin_dupack</a> <a href="ident?i=__read_mostly">__read_mostly</a>;
<a name="L100" href="source/net/ipv4/tcp_input.c#L100">100</a> 
<a name="L101" href="source/net/ipv4/tcp_input.c#L101">101</a> int <a href="ident?i=sysctl_tcp_moderate_rcvbuf">sysctl_tcp_moderate_rcvbuf</a> <a href="ident?i=__read_mostly">__read_mostly</a> = 1;
<a name="L102" href="source/net/ipv4/tcp_input.c#L102">102</a> int <a href="ident?i=sysctl_tcp_early_retrans">sysctl_tcp_early_retrans</a> <a href="ident?i=__read_mostly">__read_mostly</a> = 3;
<a name="L103" href="source/net/ipv4/tcp_input.c#L103">103</a> int <a href="ident?i=sysctl_tcp_invalid_ratelimit">sysctl_tcp_invalid_ratelimit</a> <a href="ident?i=__read_mostly">__read_mostly</a> = <a href="ident?i=HZ">HZ</a>/2;
<a name="L104" href="source/net/ipv4/tcp_input.c#L104">104</a> 
<a name="L105" href="source/net/ipv4/tcp_input.c#L105">105</a> #define <a href="ident?i=FLAG_DATA">FLAG_DATA</a>               0x01 <b><i>/* Incoming frame contained data.          */</i></b>
<a name="L106" href="source/net/ipv4/tcp_input.c#L106">106</a> #define <a href="ident?i=FLAG_WIN_UPDATE">FLAG_WIN_UPDATE</a>         0x02 <b><i>/* Incoming ACK was a window update.       */</i></b>
<a name="L107" href="source/net/ipv4/tcp_input.c#L107">107</a> #define <a href="ident?i=FLAG_DATA_ACKED">FLAG_DATA_ACKED</a>         0x04 <b><i>/* This ACK acknowledged new data.         */</i></b>
<a name="L108" href="source/net/ipv4/tcp_input.c#L108">108</a> #define <a href="ident?i=FLAG_RETRANS_DATA_ACKED">FLAG_RETRANS_DATA_ACKED</a> 0x08 <b><i>/* "" "" some of which was retransmitted.  */</i></b>
<a name="L109" href="source/net/ipv4/tcp_input.c#L109">109</a> #define <a href="ident?i=FLAG_SYN_ACKED">FLAG_SYN_ACKED</a>          0x10 <b><i>/* This ACK acknowledged SYN.              */</i></b>
<a name="L110" href="source/net/ipv4/tcp_input.c#L110">110</a> #define <a href="ident?i=FLAG_DATA_SACKED">FLAG_DATA_SACKED</a>        0x20 <b><i>/* New SACK.                               */</i></b>
<a name="L111" href="source/net/ipv4/tcp_input.c#L111">111</a> #define <a href="ident?i=FLAG_ECE">FLAG_ECE</a>                0x40 <b><i>/* ECE in this ACK                         */</i></b>
<a name="L112" href="source/net/ipv4/tcp_input.c#L112">112</a> #define <a href="ident?i=FLAG_SLOWPATH">FLAG_SLOWPATH</a>           0x100 <b><i>/* Do not skip RFC checks for window update.*/</i></b>
<a name="L113" href="source/net/ipv4/tcp_input.c#L113">113</a> #define <a href="ident?i=FLAG_ORIG_SACK_ACKED">FLAG_ORIG_SACK_ACKED</a>    0x200 <b><i>/* Never retransmitted data are (s)acked  */</i></b>
<a name="L114" href="source/net/ipv4/tcp_input.c#L114">114</a> #define <a href="ident?i=FLAG_SND_UNA_ADVANCED">FLAG_SND_UNA_ADVANCED</a>   0x400 <b><i>/* Snd_una was changed (!= FLAG_DATA_ACKED) */</i></b>
<a name="L115" href="source/net/ipv4/tcp_input.c#L115">115</a> #define <a href="ident?i=FLAG_DSACKING_ACK">FLAG_DSACKING_ACK</a>       0x800 <b><i>/* SACK blocks contained D-SACK info */</i></b>
<a name="L116" href="source/net/ipv4/tcp_input.c#L116">116</a> #define <a href="ident?i=FLAG_SACK_RENEGING">FLAG_SACK_RENEGING</a>      0x2000 <b><i>/* snd_una advanced to a sacked seq */</i></b>
<a name="L117" href="source/net/ipv4/tcp_input.c#L117">117</a> #define <a href="ident?i=FLAG_UPDATE_TS_RECENT">FLAG_UPDATE_TS_RECENT</a>   0x4000 <b><i>/* tcp_replace_ts_recent() */</i></b>
<a name="L118" href="source/net/ipv4/tcp_input.c#L118">118</a> 
<a name="L119" href="source/net/ipv4/tcp_input.c#L119">119</a> #define <a href="ident?i=FLAG_ACKED">FLAG_ACKED</a>              (<a href="ident?i=FLAG_DATA_ACKED">FLAG_DATA_ACKED</a>|<a href="ident?i=FLAG_SYN_ACKED">FLAG_SYN_ACKED</a>)
<a name="L120" href="source/net/ipv4/tcp_input.c#L120">120</a> #define <a href="ident?i=FLAG_NOT_DUP">FLAG_NOT_DUP</a>            (<a href="ident?i=FLAG_DATA">FLAG_DATA</a>|<a href="ident?i=FLAG_WIN_UPDATE">FLAG_WIN_UPDATE</a>|<a href="ident?i=FLAG_ACKED">FLAG_ACKED</a>)
<a name="L121" href="source/net/ipv4/tcp_input.c#L121">121</a> #define <a href="ident?i=FLAG_CA_ALERT">FLAG_CA_ALERT</a>           (<a href="ident?i=FLAG_DATA_SACKED">FLAG_DATA_SACKED</a>|<a href="ident?i=FLAG_ECE">FLAG_ECE</a>)
<a name="L122" href="source/net/ipv4/tcp_input.c#L122">122</a> #define <a href="ident?i=FLAG_FORWARD_PROGRESS">FLAG_FORWARD_PROGRESS</a>   (<a href="ident?i=FLAG_ACKED">FLAG_ACKED</a>|<a href="ident?i=FLAG_DATA_SACKED">FLAG_DATA_SACKED</a>)
<a name="L123" href="source/net/ipv4/tcp_input.c#L123">123</a> 
<a name="L124" href="source/net/ipv4/tcp_input.c#L124">124</a> #define <a href="ident?i=TCP_REMNANT">TCP_REMNANT</a> (TCP_FLAG_FIN|TCP_FLAG_URG|TCP_FLAG_SYN|TCP_FLAG_PSH)
<a name="L125" href="source/net/ipv4/tcp_input.c#L125">125</a> #define <a href="ident?i=TCP_HP_BITS">TCP_HP_BITS</a> (~(TCP_RESERVED_BITS|TCP_FLAG_PSH))
<a name="L126" href="source/net/ipv4/tcp_input.c#L126">126</a> 
<a name="L127" href="source/net/ipv4/tcp_input.c#L127">127</a> <b><i>/* Adapt the MSS value used to make delayed ack decision to the</i></b>
<a name="L128" href="source/net/ipv4/tcp_input.c#L128">128</a> <b><i> * real world.</i></b>
<a name="L129" href="source/net/ipv4/tcp_input.c#L129">129</a> <b><i> */</i></b>
<a name="L130" href="source/net/ipv4/tcp_input.c#L130">130</a> static void <a href="ident?i=tcp_measure_rcv_mss">tcp_measure_rcv_mss</a>(struct <a href="ident?i=sock">sock</a> *sk, const struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L131" href="source/net/ipv4/tcp_input.c#L131">131</a> {
<a name="L132" href="source/net/ipv4/tcp_input.c#L132">132</a>         struct <a href="ident?i=inet_connection_sock">inet_connection_sock</a> *icsk = <a href="ident?i=inet_csk">inet_csk</a>(sk);
<a name="L133" href="source/net/ipv4/tcp_input.c#L133">133</a>         const unsigned int lss = icsk-&gt;icsk_ack.last_seg_size;
<a name="L134" href="source/net/ipv4/tcp_input.c#L134">134</a>         unsigned int <a href="ident?i=len">len</a>;
<a name="L135" href="source/net/ipv4/tcp_input.c#L135">135</a> 
<a name="L136" href="source/net/ipv4/tcp_input.c#L136">136</a>         icsk-&gt;icsk_ack.last_seg_size = 0;
<a name="L137" href="source/net/ipv4/tcp_input.c#L137">137</a> 
<a name="L138" href="source/net/ipv4/tcp_input.c#L138">138</a>         <b><i>/* skb-&gt;len may jitter because of SACKs, even if peer</i></b>
<a name="L139" href="source/net/ipv4/tcp_input.c#L139">139</a> <b><i>         * sends good full-sized frames.</i></b>
<a name="L140" href="source/net/ipv4/tcp_input.c#L140">140</a> <b><i>         */</i></b>
<a name="L141" href="source/net/ipv4/tcp_input.c#L141">141</a>         <a href="ident?i=len">len</a> = <a href="ident?i=skb_shinfo">skb_shinfo</a>(<a href="ident?i=skb">skb</a>)-&gt;gso_size ? : <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a>;
<a name="L142" href="source/net/ipv4/tcp_input.c#L142">142</a>         if (<a href="ident?i=len">len</a> &gt;= icsk-&gt;icsk_ack.rcv_mss) {
<a name="L143" href="source/net/ipv4/tcp_input.c#L143">143</a>                 icsk-&gt;icsk_ack.rcv_mss = <a href="ident?i=len">len</a>;
<a name="L144" href="source/net/ipv4/tcp_input.c#L144">144</a>         } else {
<a name="L145" href="source/net/ipv4/tcp_input.c#L145">145</a>                 <b><i>/* Otherwise, we make more careful check taking into account,</i></b>
<a name="L146" href="source/net/ipv4/tcp_input.c#L146">146</a> <b><i>                 * that SACKs block is variable.</i></b>
<a name="L147" href="source/net/ipv4/tcp_input.c#L147">147</a> <b><i>                 *</i></b>
<a name="L148" href="source/net/ipv4/tcp_input.c#L148">148</a> <b><i>                 * "len" is invariant segment length, including TCP header.</i></b>
<a name="L149" href="source/net/ipv4/tcp_input.c#L149">149</a> <b><i>                 */</i></b>
<a name="L150" href="source/net/ipv4/tcp_input.c#L150">150</a>                 <a href="ident?i=len">len</a> += <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=data">data</a> - <a href="ident?i=skb_transport_header">skb_transport_header</a>(<a href="ident?i=skb">skb</a>);
<a name="L151" href="source/net/ipv4/tcp_input.c#L151">151</a>                 if (<a href="ident?i=len">len</a> &gt;= <a href="ident?i=TCP_MSS_DEFAULT">TCP_MSS_DEFAULT</a> + sizeof(struct <a href="ident?i=tcphdr">tcphdr</a>) ||
<a name="L152" href="source/net/ipv4/tcp_input.c#L152">152</a>                     <b><i>/* If PSH is not set, packet should be</i></b>
<a name="L153" href="source/net/ipv4/tcp_input.c#L153">153</a> <b><i>                     * full sized, provided peer TCP is not badly broken.</i></b>
<a name="L154" href="source/net/ipv4/tcp_input.c#L154">154</a> <b><i>                     * This observation (if it is correct 8)) allows</i></b>
<a name="L155" href="source/net/ipv4/tcp_input.c#L155">155</a> <b><i>                     * to handle super-low mtu links fairly.</i></b>
<a name="L156" href="source/net/ipv4/tcp_input.c#L156">156</a> <b><i>                     */</i></b>
<a name="L157" href="source/net/ipv4/tcp_input.c#L157">157</a>                     (<a href="ident?i=len">len</a> &gt;= <a href="ident?i=TCP_MIN_MSS">TCP_MIN_MSS</a> + sizeof(struct <a href="ident?i=tcphdr">tcphdr</a>) &amp;&amp;
<a name="L158" href="source/net/ipv4/tcp_input.c#L158">158</a>                      !(<a href="ident?i=tcp_flag_word">tcp_flag_word</a>(<a href="ident?i=tcp_hdr">tcp_hdr</a>(<a href="ident?i=skb">skb</a>)) &amp; <a href="ident?i=TCP_REMNANT">TCP_REMNANT</a>))) {
<a name="L159" href="source/net/ipv4/tcp_input.c#L159">159</a>                         <b><i>/* Subtract also invariant (if peer is RFC compliant),</i></b>
<a name="L160" href="source/net/ipv4/tcp_input.c#L160">160</a> <b><i>                         * tcp header plus fixed timestamp option length.</i></b>
<a name="L161" href="source/net/ipv4/tcp_input.c#L161">161</a> <b><i>                         * Resulting "len" is MSS free of SACK jitter.</i></b>
<a name="L162" href="source/net/ipv4/tcp_input.c#L162">162</a> <b><i>                         */</i></b>
<a name="L163" href="source/net/ipv4/tcp_input.c#L163">163</a>                         <a href="ident?i=len">len</a> -= <a href="ident?i=tcp_sk">tcp_sk</a>(sk)-&gt;tcp_header_len;
<a name="L164" href="source/net/ipv4/tcp_input.c#L164">164</a>                         icsk-&gt;icsk_ack.last_seg_size = <a href="ident?i=len">len</a>;
<a name="L165" href="source/net/ipv4/tcp_input.c#L165">165</a>                         if (<a href="ident?i=len">len</a> == lss) {
<a name="L166" href="source/net/ipv4/tcp_input.c#L166">166</a>                                 icsk-&gt;icsk_ack.rcv_mss = <a href="ident?i=len">len</a>;
<a name="L167" href="source/net/ipv4/tcp_input.c#L167">167</a>                                 return;
<a name="L168" href="source/net/ipv4/tcp_input.c#L168">168</a>                         }
<a name="L169" href="source/net/ipv4/tcp_input.c#L169">169</a>                 }
<a name="L170" href="source/net/ipv4/tcp_input.c#L170">170</a>                 if (icsk-&gt;icsk_ack.<a href="ident?i=pending">pending</a> &amp; ICSK_ACK_PUSHED)
<a name="L171" href="source/net/ipv4/tcp_input.c#L171">171</a>                         icsk-&gt;icsk_ack.<a href="ident?i=pending">pending</a> |= ICSK_ACK_PUSHED2;
<a name="L172" href="source/net/ipv4/tcp_input.c#L172">172</a>                 icsk-&gt;icsk_ack.<a href="ident?i=pending">pending</a> |= ICSK_ACK_PUSHED;
<a name="L173" href="source/net/ipv4/tcp_input.c#L173">173</a>         }
<a name="L174" href="source/net/ipv4/tcp_input.c#L174">174</a> }
<a name="L175" href="source/net/ipv4/tcp_input.c#L175">175</a> 
<a name="L176" href="source/net/ipv4/tcp_input.c#L176">176</a> static void <a href="ident?i=tcp_incr_quickack">tcp_incr_quickack</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L177" href="source/net/ipv4/tcp_input.c#L177">177</a> {
<a name="L178" href="source/net/ipv4/tcp_input.c#L178">178</a>         struct <a href="ident?i=inet_connection_sock">inet_connection_sock</a> *icsk = <a href="ident?i=inet_csk">inet_csk</a>(sk);
<a name="L179" href="source/net/ipv4/tcp_input.c#L179">179</a>         unsigned int quickacks = <a href="ident?i=tcp_sk">tcp_sk</a>(sk)-&gt;rcv_wnd / (2 * icsk-&gt;icsk_ack.rcv_mss);
<a name="L180" href="source/net/ipv4/tcp_input.c#L180">180</a> 
<a name="L181" href="source/net/ipv4/tcp_input.c#L181">181</a>         if (quickacks == 0)
<a name="L182" href="source/net/ipv4/tcp_input.c#L182">182</a>                 quickacks = 2;
<a name="L183" href="source/net/ipv4/tcp_input.c#L183">183</a>         if (quickacks &gt; icsk-&gt;icsk_ack.quick)
<a name="L184" href="source/net/ipv4/tcp_input.c#L184">184</a>                 icsk-&gt;icsk_ack.quick = <a href="ident?i=min">min</a>(quickacks, <a href="ident?i=TCP_MAX_QUICKACKS">TCP_MAX_QUICKACKS</a>);
<a name="L185" href="source/net/ipv4/tcp_input.c#L185">185</a> }
<a name="L186" href="source/net/ipv4/tcp_input.c#L186">186</a> 
<a name="L187" href="source/net/ipv4/tcp_input.c#L187">187</a> static void <a href="ident?i=tcp_enter_quickack_mode">tcp_enter_quickack_mode</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L188" href="source/net/ipv4/tcp_input.c#L188">188</a> {
<a name="L189" href="source/net/ipv4/tcp_input.c#L189">189</a>         struct <a href="ident?i=inet_connection_sock">inet_connection_sock</a> *icsk = <a href="ident?i=inet_csk">inet_csk</a>(sk);
<a name="L190" href="source/net/ipv4/tcp_input.c#L190">190</a>         <a href="ident?i=tcp_incr_quickack">tcp_incr_quickack</a>(sk);
<a name="L191" href="source/net/ipv4/tcp_input.c#L191">191</a>         icsk-&gt;icsk_ack.pingpong = 0;
<a name="L192" href="source/net/ipv4/tcp_input.c#L192">192</a>         icsk-&gt;icsk_ack.ato = <a href="ident?i=TCP_ATO_MIN">TCP_ATO_MIN</a>;
<a name="L193" href="source/net/ipv4/tcp_input.c#L193">193</a> }
<a name="L194" href="source/net/ipv4/tcp_input.c#L194">194</a> 
<a name="L195" href="source/net/ipv4/tcp_input.c#L195">195</a> <b><i>/* Send ACKs quickly, if "quick" count is not exhausted</i></b>
<a name="L196" href="source/net/ipv4/tcp_input.c#L196">196</a> <b><i> * and the session is not interactive.</i></b>
<a name="L197" href="source/net/ipv4/tcp_input.c#L197">197</a> <b><i> */</i></b>
<a name="L198" href="source/net/ipv4/tcp_input.c#L198">198</a> 
<a name="L199" href="source/net/ipv4/tcp_input.c#L199">199</a> static inline <a href="ident?i=bool">bool</a> <a href="ident?i=tcp_in_quickack_mode">tcp_in_quickack_mode</a>(const struct <a href="ident?i=sock">sock</a> *sk)
<a name="L200" href="source/net/ipv4/tcp_input.c#L200">200</a> {
<a name="L201" href="source/net/ipv4/tcp_input.c#L201">201</a>         const struct <a href="ident?i=inet_connection_sock">inet_connection_sock</a> *icsk = <a href="ident?i=inet_csk">inet_csk</a>(sk);
<a name="L202" href="source/net/ipv4/tcp_input.c#L202">202</a> 
<a name="L203" href="source/net/ipv4/tcp_input.c#L203">203</a>         return icsk-&gt;icsk_ack.quick &amp;&amp; !icsk-&gt;icsk_ack.pingpong;
<a name="L204" href="source/net/ipv4/tcp_input.c#L204">204</a> }
<a name="L205" href="source/net/ipv4/tcp_input.c#L205">205</a> 
<a name="L206" href="source/net/ipv4/tcp_input.c#L206">206</a> static void <a href="ident?i=tcp_ecn_queue_cwr">tcp_ecn_queue_cwr</a>(struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a>)
<a name="L207" href="source/net/ipv4/tcp_input.c#L207">207</a> {
<a name="L208" href="source/net/ipv4/tcp_input.c#L208">208</a>         if (<a href="ident?i=tp">tp</a>-&gt;ecn_flags &amp; <a href="ident?i=TCP_ECN_OK">TCP_ECN_OK</a>)
<a name="L209" href="source/net/ipv4/tcp_input.c#L209">209</a>                 <a href="ident?i=tp">tp</a>-&gt;ecn_flags |= <a href="ident?i=TCP_ECN_QUEUE_CWR">TCP_ECN_QUEUE_CWR</a>;
<a name="L210" href="source/net/ipv4/tcp_input.c#L210">210</a> }
<a name="L211" href="source/net/ipv4/tcp_input.c#L211">211</a> 
<a name="L212" href="source/net/ipv4/tcp_input.c#L212">212</a> static void <a href="ident?i=tcp_ecn_accept_cwr">tcp_ecn_accept_cwr</a>(struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a>, const struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L213" href="source/net/ipv4/tcp_input.c#L213">213</a> {
<a name="L214" href="source/net/ipv4/tcp_input.c#L214">214</a>         if (<a href="ident?i=tcp_hdr">tcp_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;cwr)
<a name="L215" href="source/net/ipv4/tcp_input.c#L215">215</a>                 <a href="ident?i=tp">tp</a>-&gt;ecn_flags &amp;= ~TCP_ECN_DEMAND_CWR;
<a name="L216" href="source/net/ipv4/tcp_input.c#L216">216</a> }
<a name="L217" href="source/net/ipv4/tcp_input.c#L217">217</a> 
<a name="L218" href="source/net/ipv4/tcp_input.c#L218">218</a> static void <a href="ident?i=tcp_ecn_withdraw_cwr">tcp_ecn_withdraw_cwr</a>(struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a>)
<a name="L219" href="source/net/ipv4/tcp_input.c#L219">219</a> {
<a name="L220" href="source/net/ipv4/tcp_input.c#L220">220</a>         <a href="ident?i=tp">tp</a>-&gt;ecn_flags &amp;= ~TCP_ECN_DEMAND_CWR;
<a name="L221" href="source/net/ipv4/tcp_input.c#L221">221</a> }
<a name="L222" href="source/net/ipv4/tcp_input.c#L222">222</a> 
<a name="L223" href="source/net/ipv4/tcp_input.c#L223">223</a> static void <a href="ident?i=__tcp_ecn_check_ce">__tcp_ecn_check_ce</a>(struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a>, const struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L224" href="source/net/ipv4/tcp_input.c#L224">224</a> {
<a name="L225" href="source/net/ipv4/tcp_input.c#L225">225</a>         switch (<a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;ip_dsfield &amp; INET_ECN_MASK) {
<a name="L226" href="source/net/ipv4/tcp_input.c#L226">226</a>         case INET_ECN_NOT_ECT:
<a name="L227" href="source/net/ipv4/tcp_input.c#L227">227</a>                 <b><i>/* Funny extension: if ECT is not set on a segment,</i></b>
<a name="L228" href="source/net/ipv4/tcp_input.c#L228">228</a> <b><i>                 * and we already seen ECT on a previous segment,</i></b>
<a name="L229" href="source/net/ipv4/tcp_input.c#L229">229</a> <b><i>                 * it is probably a retransmit.</i></b>
<a name="L230" href="source/net/ipv4/tcp_input.c#L230">230</a> <b><i>                 */</i></b>
<a name="L231" href="source/net/ipv4/tcp_input.c#L231">231</a>                 if (<a href="ident?i=tp">tp</a>-&gt;ecn_flags &amp; <a href="ident?i=TCP_ECN_SEEN">TCP_ECN_SEEN</a>)
<a name="L232" href="source/net/ipv4/tcp_input.c#L232">232</a>                         <a href="ident?i=tcp_enter_quickack_mode">tcp_enter_quickack_mode</a>((struct <a href="ident?i=sock">sock</a> *)<a href="ident?i=tp">tp</a>);
<a name="L233" href="source/net/ipv4/tcp_input.c#L233">233</a>                 break;
<a name="L234" href="source/net/ipv4/tcp_input.c#L234">234</a>         case INET_ECN_CE:
<a name="L235" href="source/net/ipv4/tcp_input.c#L235">235</a>                 if (<a href="ident?i=tcp_ca_needs_ecn">tcp_ca_needs_ecn</a>((struct <a href="ident?i=sock">sock</a> *)<a href="ident?i=tp">tp</a>))
<a name="L236" href="source/net/ipv4/tcp_input.c#L236">236</a>                         <a href="ident?i=tcp_ca_event">tcp_ca_event</a>((struct <a href="ident?i=sock">sock</a> *)<a href="ident?i=tp">tp</a>, CA_EVENT_ECN_IS_CE);
<a name="L237" href="source/net/ipv4/tcp_input.c#L237">237</a> 
<a name="L238" href="source/net/ipv4/tcp_input.c#L238">238</a>                 if (!(<a href="ident?i=tp">tp</a>-&gt;ecn_flags &amp; <a href="ident?i=TCP_ECN_DEMAND_CWR">TCP_ECN_DEMAND_CWR</a>)) {
<a name="L239" href="source/net/ipv4/tcp_input.c#L239">239</a>                         <b><i>/* Better not delay acks, sender can have a very low cwnd */</i></b>
<a name="L240" href="source/net/ipv4/tcp_input.c#L240">240</a>                         <a href="ident?i=tcp_enter_quickack_mode">tcp_enter_quickack_mode</a>((struct <a href="ident?i=sock">sock</a> *)<a href="ident?i=tp">tp</a>);
<a name="L241" href="source/net/ipv4/tcp_input.c#L241">241</a>                         <a href="ident?i=tp">tp</a>-&gt;ecn_flags |= <a href="ident?i=TCP_ECN_DEMAND_CWR">TCP_ECN_DEMAND_CWR</a>;
<a name="L242" href="source/net/ipv4/tcp_input.c#L242">242</a>                 }
<a name="L243" href="source/net/ipv4/tcp_input.c#L243">243</a>                 <a href="ident?i=tp">tp</a>-&gt;ecn_flags |= <a href="ident?i=TCP_ECN_SEEN">TCP_ECN_SEEN</a>;
<a name="L244" href="source/net/ipv4/tcp_input.c#L244">244</a>                 break;
<a name="L245" href="source/net/ipv4/tcp_input.c#L245">245</a>         default:
<a name="L246" href="source/net/ipv4/tcp_input.c#L246">246</a>                 if (<a href="ident?i=tcp_ca_needs_ecn">tcp_ca_needs_ecn</a>((struct <a href="ident?i=sock">sock</a> *)<a href="ident?i=tp">tp</a>))
<a name="L247" href="source/net/ipv4/tcp_input.c#L247">247</a>                         <a href="ident?i=tcp_ca_event">tcp_ca_event</a>((struct <a href="ident?i=sock">sock</a> *)<a href="ident?i=tp">tp</a>, CA_EVENT_ECN_NO_CE);
<a name="L248" href="source/net/ipv4/tcp_input.c#L248">248</a>                 <a href="ident?i=tp">tp</a>-&gt;ecn_flags |= <a href="ident?i=TCP_ECN_SEEN">TCP_ECN_SEEN</a>;
<a name="L249" href="source/net/ipv4/tcp_input.c#L249">249</a>                 break;
<a name="L250" href="source/net/ipv4/tcp_input.c#L250">250</a>         }
<a name="L251" href="source/net/ipv4/tcp_input.c#L251">251</a> }
<a name="L252" href="source/net/ipv4/tcp_input.c#L252">252</a> 
<a name="L253" href="source/net/ipv4/tcp_input.c#L253">253</a> static void <a href="ident?i=tcp_ecn_check_ce">tcp_ecn_check_ce</a>(struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a>, const struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L254" href="source/net/ipv4/tcp_input.c#L254">254</a> {
<a name="L255" href="source/net/ipv4/tcp_input.c#L255">255</a>         if (<a href="ident?i=tp">tp</a>-&gt;ecn_flags &amp; <a href="ident?i=TCP_ECN_OK">TCP_ECN_OK</a>)
<a name="L256" href="source/net/ipv4/tcp_input.c#L256">256</a>                 <a href="ident?i=__tcp_ecn_check_ce">__tcp_ecn_check_ce</a>(<a href="ident?i=tp">tp</a>, <a href="ident?i=skb">skb</a>);
<a name="L257" href="source/net/ipv4/tcp_input.c#L257">257</a> }
<a name="L258" href="source/net/ipv4/tcp_input.c#L258">258</a> 
<a name="L259" href="source/net/ipv4/tcp_input.c#L259">259</a> static void <a href="ident?i=tcp_ecn_rcv_synack">tcp_ecn_rcv_synack</a>(struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a>, const struct <a href="ident?i=tcphdr">tcphdr</a> *<a href="ident?i=th">th</a>)
<a name="L260" href="source/net/ipv4/tcp_input.c#L260">260</a> {
<a name="L261" href="source/net/ipv4/tcp_input.c#L261">261</a>         if ((<a href="ident?i=tp">tp</a>-&gt;ecn_flags &amp; <a href="ident?i=TCP_ECN_OK">TCP_ECN_OK</a>) &amp;&amp; (!<a href="ident?i=th">th</a>-&gt;ece || <a href="ident?i=th">th</a>-&gt;cwr))
<a name="L262" href="source/net/ipv4/tcp_input.c#L262">262</a>                 <a href="ident?i=tp">tp</a>-&gt;ecn_flags &amp;= ~TCP_ECN_OK;
<a name="L263" href="source/net/ipv4/tcp_input.c#L263">263</a> }
<a name="L264" href="source/net/ipv4/tcp_input.c#L264">264</a> 
<a name="L265" href="source/net/ipv4/tcp_input.c#L265">265</a> static void <a href="ident?i=tcp_ecn_rcv_syn">tcp_ecn_rcv_syn</a>(struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a>, const struct <a href="ident?i=tcphdr">tcphdr</a> *<a href="ident?i=th">th</a>)
<a name="L266" href="source/net/ipv4/tcp_input.c#L266">266</a> {
<a name="L267" href="source/net/ipv4/tcp_input.c#L267">267</a>         if ((<a href="ident?i=tp">tp</a>-&gt;ecn_flags &amp; <a href="ident?i=TCP_ECN_OK">TCP_ECN_OK</a>) &amp;&amp; (!<a href="ident?i=th">th</a>-&gt;ece || !<a href="ident?i=th">th</a>-&gt;cwr))
<a name="L268" href="source/net/ipv4/tcp_input.c#L268">268</a>                 <a href="ident?i=tp">tp</a>-&gt;ecn_flags &amp;= ~TCP_ECN_OK;
<a name="L269" href="source/net/ipv4/tcp_input.c#L269">269</a> }
<a name="L270" href="source/net/ipv4/tcp_input.c#L270">270</a> 
<a name="L271" href="source/net/ipv4/tcp_input.c#L271">271</a> static <a href="ident?i=bool">bool</a> <a href="ident?i=tcp_ecn_rcv_ecn_echo">tcp_ecn_rcv_ecn_echo</a>(const struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a>, const struct <a href="ident?i=tcphdr">tcphdr</a> *<a href="ident?i=th">th</a>)
<a name="L272" href="source/net/ipv4/tcp_input.c#L272">272</a> {
<a name="L273" href="source/net/ipv4/tcp_input.c#L273">273</a>         if (<a href="ident?i=th">th</a>-&gt;ece &amp;&amp; !<a href="ident?i=th">th</a>-&gt;syn &amp;&amp; (<a href="ident?i=tp">tp</a>-&gt;ecn_flags &amp; <a href="ident?i=TCP_ECN_OK">TCP_ECN_OK</a>))
<a name="L274" href="source/net/ipv4/tcp_input.c#L274">274</a>                 return <a href="ident?i=true">true</a>;
<a name="L275" href="source/net/ipv4/tcp_input.c#L275">275</a>         return <a href="ident?i=false">false</a>;
<a name="L276" href="source/net/ipv4/tcp_input.c#L276">276</a> }
<a name="L277" href="source/net/ipv4/tcp_input.c#L277">277</a> 
<a name="L278" href="source/net/ipv4/tcp_input.c#L278">278</a> <b><i>/* Buffer size and advertised window tuning.</i></b>
<a name="L279" href="source/net/ipv4/tcp_input.c#L279">279</a> <b><i> *</i></b>
<a name="L280" href="source/net/ipv4/tcp_input.c#L280">280</a> <b><i> * 1. Tuning sk-&gt;sk_sndbuf, when connection enters established state.</i></b>
<a name="L281" href="source/net/ipv4/tcp_input.c#L281">281</a> <b><i> */</i></b>
<a name="L282" href="source/net/ipv4/tcp_input.c#L282">282</a> 
<a name="L283" href="source/net/ipv4/tcp_input.c#L283">283</a> static void <a href="ident?i=tcp_sndbuf_expand">tcp_sndbuf_expand</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L284" href="source/net/ipv4/tcp_input.c#L284">284</a> {
<a name="L285" href="source/net/ipv4/tcp_input.c#L285">285</a>         const struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L286" href="source/net/ipv4/tcp_input.c#L286">286</a>         int sndmem, per_mss;
<a name="L287" href="source/net/ipv4/tcp_input.c#L287">287</a>         <a href="ident?i=u32">u32</a> nr_segs;
<a name="L288" href="source/net/ipv4/tcp_input.c#L288">288</a> 
<a name="L289" href="source/net/ipv4/tcp_input.c#L289">289</a>         <b><i>/* Worst case is non GSO/TSO : each frame consumes one skb</i></b>
<a name="L290" href="source/net/ipv4/tcp_input.c#L290">290</a> <b><i>         * and skb-&gt;head is kmalloced using power of two area of memory</i></b>
<a name="L291" href="source/net/ipv4/tcp_input.c#L291">291</a> <b><i>         */</i></b>
<a name="L292" href="source/net/ipv4/tcp_input.c#L292">292</a>         per_mss = <a href="ident?i=max_t">max_t</a>(<a href="ident?i=u32">u32</a>, <a href="ident?i=tp">tp</a>-&gt;rx_opt.mss_clamp, <a href="ident?i=tp">tp</a>-&gt;mss_cache) +
<a name="L293" href="source/net/ipv4/tcp_input.c#L293">293</a>                   <a href="ident?i=MAX_TCP_HEADER">MAX_TCP_HEADER</a> +
<a name="L294" href="source/net/ipv4/tcp_input.c#L294">294</a>                   <a href="ident?i=SKB_DATA_ALIGN">SKB_DATA_ALIGN</a>(sizeof(struct <a href="ident?i=skb_shared_info">skb_shared_info</a>));
<a name="L295" href="source/net/ipv4/tcp_input.c#L295">295</a> 
<a name="L296" href="source/net/ipv4/tcp_input.c#L296">296</a>         per_mss = <a href="ident?i=roundup_pow_of_two">roundup_pow_of_two</a>(per_mss) +
<a name="L297" href="source/net/ipv4/tcp_input.c#L297">297</a>                   <a href="ident?i=SKB_DATA_ALIGN">SKB_DATA_ALIGN</a>(sizeof(struct <a href="ident?i=sk_buff">sk_buff</a>));
<a name="L298" href="source/net/ipv4/tcp_input.c#L298">298</a> 
<a name="L299" href="source/net/ipv4/tcp_input.c#L299">299</a>         nr_segs = <a href="ident?i=max_t">max_t</a>(<a href="ident?i=u32">u32</a>, <a href="ident?i=TCP_INIT_CWND">TCP_INIT_CWND</a>, <a href="ident?i=tp">tp</a>-&gt;snd_cwnd);
<a name="L300" href="source/net/ipv4/tcp_input.c#L300">300</a>         nr_segs = <a href="ident?i=max_t">max_t</a>(<a href="ident?i=u32">u32</a>, nr_segs, <a href="ident?i=tp">tp</a>-&gt;reordering + 1);
<a name="L301" href="source/net/ipv4/tcp_input.c#L301">301</a> 
<a name="L302" href="source/net/ipv4/tcp_input.c#L302">302</a>         <b><i>/* Fast Recovery (RFC 5681 3.2) :</i></b>
<a name="L303" href="source/net/ipv4/tcp_input.c#L303">303</a> <b><i>         * Cubic needs 1.7 factor, rounded to 2 to include</i></b>
<a name="L304" href="source/net/ipv4/tcp_input.c#L304">304</a> <b><i>         * extra cushion (application might react slowly to POLLOUT)</i></b>
<a name="L305" href="source/net/ipv4/tcp_input.c#L305">305</a> <b><i>         */</i></b>
<a name="L306" href="source/net/ipv4/tcp_input.c#L306">306</a>         sndmem = 2 * nr_segs * per_mss;
<a name="L307" href="source/net/ipv4/tcp_input.c#L307">307</a> 
<a name="L308" href="source/net/ipv4/tcp_input.c#L308">308</a>         if (sk-&gt;sk_sndbuf &lt; sndmem)
<a name="L309" href="source/net/ipv4/tcp_input.c#L309">309</a>                 sk-&gt;sk_sndbuf = <a href="ident?i=min">min</a>(sndmem, <a href="ident?i=sysctl_tcp_wmem">sysctl_tcp_wmem</a>[2]);
<a name="L310" href="source/net/ipv4/tcp_input.c#L310">310</a> }
<a name="L311" href="source/net/ipv4/tcp_input.c#L311">311</a> 
<a name="L312" href="source/net/ipv4/tcp_input.c#L312">312</a> <b><i>/* 2. Tuning advertised window (window_clamp, rcv_ssthresh)</i></b>
<a name="L313" href="source/net/ipv4/tcp_input.c#L313">313</a> <b><i> *</i></b>
<a name="L314" href="source/net/ipv4/tcp_input.c#L314">314</a> <b><i> * All tcp_full_space() is split to two parts: "network" buffer, allocated</i></b>
<a name="L315" href="source/net/ipv4/tcp_input.c#L315">315</a> <b><i> * forward and advertised in receiver window (tp-&gt;rcv_wnd) and</i></b>
<a name="L316" href="source/net/ipv4/tcp_input.c#L316">316</a> <b><i> * "application buffer", required to isolate scheduling/application</i></b>
<a name="L317" href="source/net/ipv4/tcp_input.c#L317">317</a> <b><i> * latencies from network.</i></b>
<a name="L318" href="source/net/ipv4/tcp_input.c#L318">318</a> <b><i> * window_clamp is maximal advertised window. It can be less than</i></b>
<a name="L319" href="source/net/ipv4/tcp_input.c#L319">319</a> <b><i> * tcp_full_space(), in this case tcp_full_space() - window_clamp</i></b>
<a name="L320" href="source/net/ipv4/tcp_input.c#L320">320</a> <b><i> * is reserved for "application" buffer. The less window_clamp is</i></b>
<a name="L321" href="source/net/ipv4/tcp_input.c#L321">321</a> <b><i> * the smoother our behaviour from viewpoint of network, but the lower</i></b>
<a name="L322" href="source/net/ipv4/tcp_input.c#L322">322</a> <b><i> * throughput and the higher sensitivity of the connection to losses. 8)</i></b>
<a name="L323" href="source/net/ipv4/tcp_input.c#L323">323</a> <b><i> *</i></b>
<a name="L324" href="source/net/ipv4/tcp_input.c#L324">324</a> <b><i> * rcv_ssthresh is more strict window_clamp used at "slow start"</i></b>
<a name="L325" href="source/net/ipv4/tcp_input.c#L325">325</a> <b><i> * phase to predict further behaviour of this connection.</i></b>
<a name="L326" href="source/net/ipv4/tcp_input.c#L326">326</a> <b><i> * It is used for two goals:</i></b>
<a name="L327" href="source/net/ipv4/tcp_input.c#L327">327</a> <b><i> * - to enforce header prediction at sender, even when application</i></b>
<a name="L328" href="source/net/ipv4/tcp_input.c#L328">328</a> <b><i> *   requires some significant "application buffer". It is check #1.</i></b>
<a name="L329" href="source/net/ipv4/tcp_input.c#L329">329</a> <b><i> * - to prevent pruning of receive queue because of misprediction</i></b>
<a name="L330" href="source/net/ipv4/tcp_input.c#L330">330</a> <b><i> *   of receiver window. Check #2.</i></b>
<a name="L331" href="source/net/ipv4/tcp_input.c#L331">331</a> <b><i> *</i></b>
<a name="L332" href="source/net/ipv4/tcp_input.c#L332">332</a> <b><i> * The scheme does not work when sender sends good segments opening</i></b>
<a name="L333" href="source/net/ipv4/tcp_input.c#L333">333</a> <b><i> * window and then starts to feed us spaghetti. But it should work</i></b>
<a name="L334" href="source/net/ipv4/tcp_input.c#L334">334</a> <b><i> * in common situations. Otherwise, we have to rely on queue collapsing.</i></b>
<a name="L335" href="source/net/ipv4/tcp_input.c#L335">335</a> <b><i> */</i></b>
<a name="L336" href="source/net/ipv4/tcp_input.c#L336">336</a> 
<a name="L337" href="source/net/ipv4/tcp_input.c#L337">337</a> <b><i>/* Slow part of check#2. */</i></b>
<a name="L338" href="source/net/ipv4/tcp_input.c#L338">338</a> static int <a href="ident?i=__tcp_grow_window">__tcp_grow_window</a>(const struct <a href="ident?i=sock">sock</a> *sk, const struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L339" href="source/net/ipv4/tcp_input.c#L339">339</a> {
<a name="L340" href="source/net/ipv4/tcp_input.c#L340">340</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L341" href="source/net/ipv4/tcp_input.c#L341">341</a>         <b><i>/* Optimize this! */</i></b>
<a name="L342" href="source/net/ipv4/tcp_input.c#L342">342</a>         int truesize = <a href="ident?i=tcp_win_from_space">tcp_win_from_space</a>(<a href="ident?i=skb">skb</a>-&gt;truesize) &gt;&gt; 1;
<a name="L343" href="source/net/ipv4/tcp_input.c#L343">343</a>         int <a href="ident?i=window">window</a> = <a href="ident?i=tcp_win_from_space">tcp_win_from_space</a>(<a href="ident?i=sysctl_tcp_rmem">sysctl_tcp_rmem</a>[2]) &gt;&gt; 1;
<a name="L344" href="source/net/ipv4/tcp_input.c#L344">344</a> 
<a name="L345" href="source/net/ipv4/tcp_input.c#L345">345</a>         while (<a href="ident?i=tp">tp</a>-&gt;rcv_ssthresh &lt;= <a href="ident?i=window">window</a>) {
<a name="L346" href="source/net/ipv4/tcp_input.c#L346">346</a>                 if (truesize &lt;= <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a>)
<a name="L347" href="source/net/ipv4/tcp_input.c#L347">347</a>                         return 2 * <a href="ident?i=inet_csk">inet_csk</a>(sk)-&gt;icsk_ack.rcv_mss;
<a name="L348" href="source/net/ipv4/tcp_input.c#L348">348</a> 
<a name="L349" href="source/net/ipv4/tcp_input.c#L349">349</a>                 truesize &gt;&gt;= 1;
<a name="L350" href="source/net/ipv4/tcp_input.c#L350">350</a>                 <a href="ident?i=window">window</a> &gt;&gt;= 1;
<a name="L351" href="source/net/ipv4/tcp_input.c#L351">351</a>         }
<a name="L352" href="source/net/ipv4/tcp_input.c#L352">352</a>         return 0;
<a name="L353" href="source/net/ipv4/tcp_input.c#L353">353</a> }
<a name="L354" href="source/net/ipv4/tcp_input.c#L354">354</a> 
<a name="L355" href="source/net/ipv4/tcp_input.c#L355">355</a> static void <a href="ident?i=tcp_grow_window">tcp_grow_window</a>(struct <a href="ident?i=sock">sock</a> *sk, const struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L356" href="source/net/ipv4/tcp_input.c#L356">356</a> {
<a name="L357" href="source/net/ipv4/tcp_input.c#L357">357</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L358" href="source/net/ipv4/tcp_input.c#L358">358</a> 
<a name="L359" href="source/net/ipv4/tcp_input.c#L359">359</a>         <b><i>/* Check #1 */</i></b>
<a name="L360" href="source/net/ipv4/tcp_input.c#L360">360</a>         if (<a href="ident?i=tp">tp</a>-&gt;rcv_ssthresh &lt; <a href="ident?i=tp">tp</a>-&gt;window_clamp &amp;&amp;
<a name="L361" href="source/net/ipv4/tcp_input.c#L361">361</a>             (int)<a href="ident?i=tp">tp</a>-&gt;rcv_ssthresh &lt; <a href="ident?i=tcp_space">tcp_space</a>(sk) &amp;&amp;
<a name="L362" href="source/net/ipv4/tcp_input.c#L362">362</a>             !<a href="ident?i=sk_under_memory_pressure">sk_under_memory_pressure</a>(sk)) {
<a name="L363" href="source/net/ipv4/tcp_input.c#L363">363</a>                 int incr;
<a name="L364" href="source/net/ipv4/tcp_input.c#L364">364</a> 
<a name="L365" href="source/net/ipv4/tcp_input.c#L365">365</a>                 <b><i>/* Check #2. Increase window, if skb with such overhead</i></b>
<a name="L366" href="source/net/ipv4/tcp_input.c#L366">366</a> <b><i>                 * will fit to rcvbuf in future.</i></b>
<a name="L367" href="source/net/ipv4/tcp_input.c#L367">367</a> <b><i>                 */</i></b>
<a name="L368" href="source/net/ipv4/tcp_input.c#L368">368</a>                 if (<a href="ident?i=tcp_win_from_space">tcp_win_from_space</a>(<a href="ident?i=skb">skb</a>-&gt;truesize) &lt;= <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a>)
<a name="L369" href="source/net/ipv4/tcp_input.c#L369">369</a>                         incr = 2 * <a href="ident?i=tp">tp</a>-&gt;advmss;
<a name="L370" href="source/net/ipv4/tcp_input.c#L370">370</a>                 else
<a name="L371" href="source/net/ipv4/tcp_input.c#L371">371</a>                         incr = <a href="ident?i=__tcp_grow_window">__tcp_grow_window</a>(sk, <a href="ident?i=skb">skb</a>);
<a name="L372" href="source/net/ipv4/tcp_input.c#L372">372</a> 
<a name="L373" href="source/net/ipv4/tcp_input.c#L373">373</a>                 if (incr) {
<a name="L374" href="source/net/ipv4/tcp_input.c#L374">374</a>                         incr = <a href="ident?i=max_t">max_t</a>(int, incr, 2 * <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a>);
<a name="L375" href="source/net/ipv4/tcp_input.c#L375">375</a>                         <a href="ident?i=tp">tp</a>-&gt;rcv_ssthresh = <a href="ident?i=min">min</a>(<a href="ident?i=tp">tp</a>-&gt;rcv_ssthresh + incr,
<a name="L376" href="source/net/ipv4/tcp_input.c#L376">376</a>                                                <a href="ident?i=tp">tp</a>-&gt;window_clamp);
<a name="L377" href="source/net/ipv4/tcp_input.c#L377">377</a>                         <a href="ident?i=inet_csk">inet_csk</a>(sk)-&gt;icsk_ack.quick |= 1;
<a name="L378" href="source/net/ipv4/tcp_input.c#L378">378</a>                 }
<a name="L379" href="source/net/ipv4/tcp_input.c#L379">379</a>         }
<a name="L380" href="source/net/ipv4/tcp_input.c#L380">380</a> }
<a name="L381" href="source/net/ipv4/tcp_input.c#L381">381</a> 
<a name="L382" href="source/net/ipv4/tcp_input.c#L382">382</a> <b><i>/* 3. Tuning rcvbuf, when connection enters established state. */</i></b>
<a name="L383" href="source/net/ipv4/tcp_input.c#L383">383</a> static void <a href="ident?i=tcp_fixup_rcvbuf">tcp_fixup_rcvbuf</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L384" href="source/net/ipv4/tcp_input.c#L384">384</a> {
<a name="L385" href="source/net/ipv4/tcp_input.c#L385">385</a>         <a href="ident?i=u32">u32</a> mss = <a href="ident?i=tcp_sk">tcp_sk</a>(sk)-&gt;advmss;
<a name="L386" href="source/net/ipv4/tcp_input.c#L386">386</a>         int rcvmem;
<a name="L387" href="source/net/ipv4/tcp_input.c#L387">387</a> 
<a name="L388" href="source/net/ipv4/tcp_input.c#L388">388</a>         rcvmem = 2 * <a href="ident?i=SKB_TRUESIZE">SKB_TRUESIZE</a>(mss + <a href="ident?i=MAX_TCP_HEADER">MAX_TCP_HEADER</a>) *
<a name="L389" href="source/net/ipv4/tcp_input.c#L389">389</a>                  <a href="ident?i=tcp_default_init_rwnd">tcp_default_init_rwnd</a>(mss);
<a name="L390" href="source/net/ipv4/tcp_input.c#L390">390</a> 
<a name="L391" href="source/net/ipv4/tcp_input.c#L391">391</a>         <b><i>/* Dynamic Right Sizing (DRS) has 2 to 3 RTT latency</i></b>
<a name="L392" href="source/net/ipv4/tcp_input.c#L392">392</a> <b><i>         * Allow enough cushion so that sender is not limited by our window</i></b>
<a name="L393" href="source/net/ipv4/tcp_input.c#L393">393</a> <b><i>         */</i></b>
<a name="L394" href="source/net/ipv4/tcp_input.c#L394">394</a>         if (<a href="ident?i=sysctl_tcp_moderate_rcvbuf">sysctl_tcp_moderate_rcvbuf</a>)
<a name="L395" href="source/net/ipv4/tcp_input.c#L395">395</a>                 rcvmem &lt;&lt;= 2;
<a name="L396" href="source/net/ipv4/tcp_input.c#L396">396</a> 
<a name="L397" href="source/net/ipv4/tcp_input.c#L397">397</a>         if (sk-&gt;sk_rcvbuf &lt; rcvmem)
<a name="L398" href="source/net/ipv4/tcp_input.c#L398">398</a>                 sk-&gt;sk_rcvbuf = <a href="ident?i=min">min</a>(rcvmem, <a href="ident?i=sysctl_tcp_rmem">sysctl_tcp_rmem</a>[2]);
<a name="L399" href="source/net/ipv4/tcp_input.c#L399">399</a> }
<a name="L400" href="source/net/ipv4/tcp_input.c#L400">400</a> 
<a name="L401" href="source/net/ipv4/tcp_input.c#L401">401</a> <b><i>/* 4. Try to fixup all. It is made immediately after connection enters</i></b>
<a name="L402" href="source/net/ipv4/tcp_input.c#L402">402</a> <b><i> *    established state.</i></b>
<a name="L403" href="source/net/ipv4/tcp_input.c#L403">403</a> <b><i> */</i></b>
<a name="L404" href="source/net/ipv4/tcp_input.c#L404">404</a> void <a href="ident?i=tcp_init_buffer_space">tcp_init_buffer_space</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L405" href="source/net/ipv4/tcp_input.c#L405">405</a> {
<a name="L406" href="source/net/ipv4/tcp_input.c#L406">406</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L407" href="source/net/ipv4/tcp_input.c#L407">407</a>         int maxwin;
<a name="L408" href="source/net/ipv4/tcp_input.c#L408">408</a> 
<a name="L409" href="source/net/ipv4/tcp_input.c#L409">409</a>         if (!(sk-&gt;sk_userlocks &amp; <a href="ident?i=SOCK_RCVBUF_LOCK">SOCK_RCVBUF_LOCK</a>))
<a name="L410" href="source/net/ipv4/tcp_input.c#L410">410</a>                 <a href="ident?i=tcp_fixup_rcvbuf">tcp_fixup_rcvbuf</a>(sk);
<a name="L411" href="source/net/ipv4/tcp_input.c#L411">411</a>         if (!(sk-&gt;sk_userlocks &amp; <a href="ident?i=SOCK_SNDBUF_LOCK">SOCK_SNDBUF_LOCK</a>))
<a name="L412" href="source/net/ipv4/tcp_input.c#L412">412</a>                 <a href="ident?i=tcp_sndbuf_expand">tcp_sndbuf_expand</a>(sk);
<a name="L413" href="source/net/ipv4/tcp_input.c#L413">413</a> 
<a name="L414" href="source/net/ipv4/tcp_input.c#L414">414</a>         <a href="ident?i=tp">tp</a>-&gt;rcvq_space.<a href="ident?i=space">space</a> = <a href="ident?i=tp">tp</a>-&gt;rcv_wnd;
<a name="L415" href="source/net/ipv4/tcp_input.c#L415">415</a>         <a href="ident?i=tp">tp</a>-&gt;rcvq_space.<a href="ident?i=time">time</a> = <a href="ident?i=tcp_time_stamp">tcp_time_stamp</a>;
<a name="L416" href="source/net/ipv4/tcp_input.c#L416">416</a>         <a href="ident?i=tp">tp</a>-&gt;rcvq_space.<a href="ident?i=seq">seq</a> = <a href="ident?i=tp">tp</a>-&gt;copied_seq;
<a name="L417" href="source/net/ipv4/tcp_input.c#L417">417</a> 
<a name="L418" href="source/net/ipv4/tcp_input.c#L418">418</a>         maxwin = <a href="ident?i=tcp_full_space">tcp_full_space</a>(sk);
<a name="L419" href="source/net/ipv4/tcp_input.c#L419">419</a> 
<a name="L420" href="source/net/ipv4/tcp_input.c#L420">420</a>         if (<a href="ident?i=tp">tp</a>-&gt;window_clamp &gt;= maxwin) {
<a name="L421" href="source/net/ipv4/tcp_input.c#L421">421</a>                 <a href="ident?i=tp">tp</a>-&gt;window_clamp = maxwin;
<a name="L422" href="source/net/ipv4/tcp_input.c#L422">422</a> 
<a name="L423" href="source/net/ipv4/tcp_input.c#L423">423</a>                 if (<a href="ident?i=sysctl_tcp_app_win">sysctl_tcp_app_win</a> &amp;&amp; maxwin &gt; 4 * <a href="ident?i=tp">tp</a>-&gt;advmss)
<a name="L424" href="source/net/ipv4/tcp_input.c#L424">424</a>                         <a href="ident?i=tp">tp</a>-&gt;window_clamp = <a href="ident?i=max">max</a>(maxwin -
<a name="L425" href="source/net/ipv4/tcp_input.c#L425">425</a>                                                (maxwin &gt;&gt; <a href="ident?i=sysctl_tcp_app_win">sysctl_tcp_app_win</a>),
<a name="L426" href="source/net/ipv4/tcp_input.c#L426">426</a>                                                4 * <a href="ident?i=tp">tp</a>-&gt;advmss);
<a name="L427" href="source/net/ipv4/tcp_input.c#L427">427</a>         }
<a name="L428" href="source/net/ipv4/tcp_input.c#L428">428</a> 
<a name="L429" href="source/net/ipv4/tcp_input.c#L429">429</a>         <b><i>/* Force reservation of one segment. */</i></b>
<a name="L430" href="source/net/ipv4/tcp_input.c#L430">430</a>         if (<a href="ident?i=sysctl_tcp_app_win">sysctl_tcp_app_win</a> &amp;&amp;
<a name="L431" href="source/net/ipv4/tcp_input.c#L431">431</a>             <a href="ident?i=tp">tp</a>-&gt;window_clamp &gt; 2 * <a href="ident?i=tp">tp</a>-&gt;advmss &amp;&amp;
<a name="L432" href="source/net/ipv4/tcp_input.c#L432">432</a>             <a href="ident?i=tp">tp</a>-&gt;window_clamp + <a href="ident?i=tp">tp</a>-&gt;advmss &gt; maxwin)
<a name="L433" href="source/net/ipv4/tcp_input.c#L433">433</a>                 <a href="ident?i=tp">tp</a>-&gt;window_clamp = <a href="ident?i=max">max</a>(2 * <a href="ident?i=tp">tp</a>-&gt;advmss, maxwin - <a href="ident?i=tp">tp</a>-&gt;advmss);
<a name="L434" href="source/net/ipv4/tcp_input.c#L434">434</a> 
<a name="L435" href="source/net/ipv4/tcp_input.c#L435">435</a>         <a href="ident?i=tp">tp</a>-&gt;rcv_ssthresh = <a href="ident?i=min">min</a>(<a href="ident?i=tp">tp</a>-&gt;rcv_ssthresh, <a href="ident?i=tp">tp</a>-&gt;window_clamp);
<a name="L436" href="source/net/ipv4/tcp_input.c#L436">436</a>         <a href="ident?i=tp">tp</a>-&gt;snd_cwnd_stamp = <a href="ident?i=tcp_time_stamp">tcp_time_stamp</a>;
<a name="L437" href="source/net/ipv4/tcp_input.c#L437">437</a> }
<a name="L438" href="source/net/ipv4/tcp_input.c#L438">438</a> 
<a name="L439" href="source/net/ipv4/tcp_input.c#L439">439</a> <b><i>/* 5. Recalculate window clamp after socket hit its memory bounds. */</i></b>
<a name="L440" href="source/net/ipv4/tcp_input.c#L440">440</a> static void <a href="ident?i=tcp_clamp_window">tcp_clamp_window</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L441" href="source/net/ipv4/tcp_input.c#L441">441</a> {
<a name="L442" href="source/net/ipv4/tcp_input.c#L442">442</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L443" href="source/net/ipv4/tcp_input.c#L443">443</a>         struct <a href="ident?i=inet_connection_sock">inet_connection_sock</a> *icsk = <a href="ident?i=inet_csk">inet_csk</a>(sk);
<a name="L444" href="source/net/ipv4/tcp_input.c#L444">444</a> 
<a name="L445" href="source/net/ipv4/tcp_input.c#L445">445</a>         icsk-&gt;icsk_ack.quick = 0;
<a name="L446" href="source/net/ipv4/tcp_input.c#L446">446</a> 
<a name="L447" href="source/net/ipv4/tcp_input.c#L447">447</a>         if (sk-&gt;sk_rcvbuf &lt; <a href="ident?i=sysctl_tcp_rmem">sysctl_tcp_rmem</a>[2] &amp;&amp;
<a name="L448" href="source/net/ipv4/tcp_input.c#L448">448</a>             !(sk-&gt;sk_userlocks &amp; <a href="ident?i=SOCK_RCVBUF_LOCK">SOCK_RCVBUF_LOCK</a>) &amp;&amp;
<a name="L449" href="source/net/ipv4/tcp_input.c#L449">449</a>             !<a href="ident?i=sk_under_memory_pressure">sk_under_memory_pressure</a>(sk) &amp;&amp;
<a name="L450" href="source/net/ipv4/tcp_input.c#L450">450</a>             <a href="ident?i=sk_memory_allocated">sk_memory_allocated</a>(sk) &lt; <a href="ident?i=sk_prot_mem_limits">sk_prot_mem_limits</a>(sk, 0)) {
<a name="L451" href="source/net/ipv4/tcp_input.c#L451">451</a>                 sk-&gt;sk_rcvbuf = <a href="ident?i=min">min</a>(<a href="ident?i=atomic_read">atomic_read</a>(&amp;sk-&gt;<a href="ident?i=sk_rmem_alloc">sk_rmem_alloc</a>),
<a name="L452" href="source/net/ipv4/tcp_input.c#L452">452</a>                                     <a href="ident?i=sysctl_tcp_rmem">sysctl_tcp_rmem</a>[2]);
<a name="L453" href="source/net/ipv4/tcp_input.c#L453">453</a>         }
<a name="L454" href="source/net/ipv4/tcp_input.c#L454">454</a>         if (<a href="ident?i=atomic_read">atomic_read</a>(&amp;sk-&gt;<a href="ident?i=sk_rmem_alloc">sk_rmem_alloc</a>) &gt; sk-&gt;sk_rcvbuf)
<a name="L455" href="source/net/ipv4/tcp_input.c#L455">455</a>                 <a href="ident?i=tp">tp</a>-&gt;rcv_ssthresh = <a href="ident?i=min">min</a>(<a href="ident?i=tp">tp</a>-&gt;window_clamp, 2U * <a href="ident?i=tp">tp</a>-&gt;advmss);
<a name="L456" href="source/net/ipv4/tcp_input.c#L456">456</a> }
<a name="L457" href="source/net/ipv4/tcp_input.c#L457">457</a> 
<a name="L458" href="source/net/ipv4/tcp_input.c#L458">458</a> <b><i>/* Initialize RCV_MSS value.</i></b>
<a name="L459" href="source/net/ipv4/tcp_input.c#L459">459</a> <b><i> * RCV_MSS is an our guess about MSS used by the peer.</i></b>
<a name="L460" href="source/net/ipv4/tcp_input.c#L460">460</a> <b><i> * We haven't any direct information about the MSS.</i></b>
<a name="L461" href="source/net/ipv4/tcp_input.c#L461">461</a> <b><i> * It's better to underestimate the RCV_MSS rather than overestimate.</i></b>
<a name="L462" href="source/net/ipv4/tcp_input.c#L462">462</a> <b><i> * Overestimations make us ACKing less frequently than needed.</i></b>
<a name="L463" href="source/net/ipv4/tcp_input.c#L463">463</a> <b><i> * Underestimations are more easy to detect and fix by tcp_measure_rcv_mss().</i></b>
<a name="L464" href="source/net/ipv4/tcp_input.c#L464">464</a> <b><i> */</i></b>
<a name="L465" href="source/net/ipv4/tcp_input.c#L465">465</a> void <a href="ident?i=tcp_initialize_rcv_mss">tcp_initialize_rcv_mss</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L466" href="source/net/ipv4/tcp_input.c#L466">466</a> {
<a name="L467" href="source/net/ipv4/tcp_input.c#L467">467</a>         const struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L468" href="source/net/ipv4/tcp_input.c#L468">468</a>         unsigned int <a href="ident?i=hint">hint</a> = <a href="ident?i=min_t">min_t</a>(unsigned int, <a href="ident?i=tp">tp</a>-&gt;advmss, <a href="ident?i=tp">tp</a>-&gt;mss_cache);
<a name="L469" href="source/net/ipv4/tcp_input.c#L469">469</a> 
<a name="L470" href="source/net/ipv4/tcp_input.c#L470">470</a>         <a href="ident?i=hint">hint</a> = <a href="ident?i=min">min</a>(<a href="ident?i=hint">hint</a>, <a href="ident?i=tp">tp</a>-&gt;rcv_wnd / 2);
<a name="L471" href="source/net/ipv4/tcp_input.c#L471">471</a>         <a href="ident?i=hint">hint</a> = <a href="ident?i=min">min</a>(<a href="ident?i=hint">hint</a>, <a href="ident?i=TCP_MSS_DEFAULT">TCP_MSS_DEFAULT</a>);
<a name="L472" href="source/net/ipv4/tcp_input.c#L472">472</a>         <a href="ident?i=hint">hint</a> = <a href="ident?i=max">max</a>(<a href="ident?i=hint">hint</a>, <a href="ident?i=TCP_MIN_MSS">TCP_MIN_MSS</a>);
<a name="L473" href="source/net/ipv4/tcp_input.c#L473">473</a> 
<a name="L474" href="source/net/ipv4/tcp_input.c#L474">474</a>         <a href="ident?i=inet_csk">inet_csk</a>(sk)-&gt;icsk_ack.rcv_mss = <a href="ident?i=hint">hint</a>;
<a name="L475" href="source/net/ipv4/tcp_input.c#L475">475</a> }
<a name="L476" href="source/net/ipv4/tcp_input.c#L476">476</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=tcp_initialize_rcv_mss">tcp_initialize_rcv_mss</a>);
<a name="L477" href="source/net/ipv4/tcp_input.c#L477">477</a> 
<a name="L478" href="source/net/ipv4/tcp_input.c#L478">478</a> <b><i>/* Receiver "autotuning" code.</i></b>
<a name="L479" href="source/net/ipv4/tcp_input.c#L479">479</a> <b><i> *</i></b>
<a name="L480" href="source/net/ipv4/tcp_input.c#L480">480</a> <b><i> * The algorithm for RTT estimation w/o timestamps is based on</i></b>
<a name="L481" href="source/net/ipv4/tcp_input.c#L481">481</a> <b><i> * Dynamic Right-Sizing (DRS) by Wu Feng and Mike Fisk of LANL.</i></b>
<a name="L482" href="source/net/ipv4/tcp_input.c#L482">482</a> <b><i> * &lt;<a href="http://public.lanl.gov/radiant/pubs.html#DRS&gt;">http://public.lanl.gov/radiant/pubs.html#DRS&gt;</a></i></b>
<a name="L483" href="source/net/ipv4/tcp_input.c#L483">483</a> <b><i> *</i></b>
<a name="L484" href="source/net/ipv4/tcp_input.c#L484">484</a> <b><i> * More detail on this code can be found at</i></b>
<a name="L485" href="source/net/ipv4/tcp_input.c#L485">485</a> <b><i> * &lt;<a href="http://staff.psc.edu/jheffner/&gt;,">http://staff.psc.edu/jheffner/&gt;,</a></i></b>
<a name="L486" href="source/net/ipv4/tcp_input.c#L486">486</a> <b><i> * though this reference is out of date.  A new paper</i></b>
<a name="L487" href="source/net/ipv4/tcp_input.c#L487">487</a> <b><i> * is pending.</i></b>
<a name="L488" href="source/net/ipv4/tcp_input.c#L488">488</a> <b><i> */</i></b>
<a name="L489" href="source/net/ipv4/tcp_input.c#L489">489</a> static void <a href="ident?i=tcp_rcv_rtt_update">tcp_rcv_rtt_update</a>(struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a>, <a href="ident?i=u32">u32</a> <a href="ident?i=sample">sample</a>, int win_dep)
<a name="L490" href="source/net/ipv4/tcp_input.c#L490">490</a> {
<a name="L491" href="source/net/ipv4/tcp_input.c#L491">491</a>         <a href="ident?i=u32">u32</a> new_sample = <a href="ident?i=tp">tp</a>-&gt;rcv_rtt_est.rtt;
<a name="L492" href="source/net/ipv4/tcp_input.c#L492">492</a>         long <a href="ident?i=m">m</a> = <a href="ident?i=sample">sample</a>;
<a name="L493" href="source/net/ipv4/tcp_input.c#L493">493</a> 
<a name="L494" href="source/net/ipv4/tcp_input.c#L494">494</a>         if (<a href="ident?i=m">m</a> == 0)
<a name="L495" href="source/net/ipv4/tcp_input.c#L495">495</a>                 <a href="ident?i=m">m</a> = 1;
<a name="L496" href="source/net/ipv4/tcp_input.c#L496">496</a> 
<a name="L497" href="source/net/ipv4/tcp_input.c#L497">497</a>         if (new_sample != 0) {
<a name="L498" href="source/net/ipv4/tcp_input.c#L498">498</a>                 <b><i>/* If we sample in larger samples in the non-timestamp</i></b>
<a name="L499" href="source/net/ipv4/tcp_input.c#L499">499</a> <b><i>                 * case, we could grossly overestimate the RTT especially</i></b>
<a name="L500" href="source/net/ipv4/tcp_input.c#L500">500</a> <b><i>                 * with chatty applications or bulk transfer apps which</i></b>
<a name="L501" href="source/net/ipv4/tcp_input.c#L501">501</a> <b><i>                 * are stalled on filesystem I/O.</i></b>
<a name="L502" href="source/net/ipv4/tcp_input.c#L502">502</a> <b><i>                 *</i></b>
<a name="L503" href="source/net/ipv4/tcp_input.c#L503">503</a> <b><i>                 * Also, since we are only going for a minimum in the</i></b>
<a name="L504" href="source/net/ipv4/tcp_input.c#L504">504</a> <b><i>                 * non-timestamp case, we do not smooth things out</i></b>
<a name="L505" href="source/net/ipv4/tcp_input.c#L505">505</a> <b><i>                 * else with timestamps disabled convergence takes too</i></b>
<a name="L506" href="source/net/ipv4/tcp_input.c#L506">506</a> <b><i>                 * long.</i></b>
<a name="L507" href="source/net/ipv4/tcp_input.c#L507">507</a> <b><i>                 */</i></b>
<a name="L508" href="source/net/ipv4/tcp_input.c#L508">508</a>                 if (!win_dep) {
<a name="L509" href="source/net/ipv4/tcp_input.c#L509">509</a>                         <a href="ident?i=m">m</a> -= (new_sample &gt;&gt; 3);
<a name="L510" href="source/net/ipv4/tcp_input.c#L510">510</a>                         new_sample += <a href="ident?i=m">m</a>;
<a name="L511" href="source/net/ipv4/tcp_input.c#L511">511</a>                 } else {
<a name="L512" href="source/net/ipv4/tcp_input.c#L512">512</a>                         <a href="ident?i=m">m</a> &lt;&lt;= 3;
<a name="L513" href="source/net/ipv4/tcp_input.c#L513">513</a>                         if (<a href="ident?i=m">m</a> &lt; new_sample)
<a name="L514" href="source/net/ipv4/tcp_input.c#L514">514</a>                                 new_sample = <a href="ident?i=m">m</a>;
<a name="L515" href="source/net/ipv4/tcp_input.c#L515">515</a>                 }
<a name="L516" href="source/net/ipv4/tcp_input.c#L516">516</a>         } else {
<a name="L517" href="source/net/ipv4/tcp_input.c#L517">517</a>                 <b><i>/* No previous measure. */</i></b>
<a name="L518" href="source/net/ipv4/tcp_input.c#L518">518</a>                 new_sample = <a href="ident?i=m">m</a> &lt;&lt; 3;
<a name="L519" href="source/net/ipv4/tcp_input.c#L519">519</a>         }
<a name="L520" href="source/net/ipv4/tcp_input.c#L520">520</a> 
<a name="L521" href="source/net/ipv4/tcp_input.c#L521">521</a>         if (<a href="ident?i=tp">tp</a>-&gt;rcv_rtt_est.rtt != new_sample)
<a name="L522" href="source/net/ipv4/tcp_input.c#L522">522</a>                 <a href="ident?i=tp">tp</a>-&gt;rcv_rtt_est.rtt = new_sample;
<a name="L523" href="source/net/ipv4/tcp_input.c#L523">523</a> }
<a name="L524" href="source/net/ipv4/tcp_input.c#L524">524</a> 
<a name="L525" href="source/net/ipv4/tcp_input.c#L525">525</a> static inline void <a href="ident?i=tcp_rcv_rtt_measure">tcp_rcv_rtt_measure</a>(struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a>)
<a name="L526" href="source/net/ipv4/tcp_input.c#L526">526</a> {
<a name="L527" href="source/net/ipv4/tcp_input.c#L527">527</a>         if (<a href="ident?i=tp">tp</a>-&gt;rcv_rtt_est.<a href="ident?i=time">time</a> == 0)
<a name="L528" href="source/net/ipv4/tcp_input.c#L528">528</a>                 goto new_measure;
<a name="L529" href="source/net/ipv4/tcp_input.c#L529">529</a>         if (<a href="ident?i=before">before</a>(<a href="ident?i=tp">tp</a>-&gt;rcv_nxt, <a href="ident?i=tp">tp</a>-&gt;rcv_rtt_est.<a href="ident?i=seq">seq</a>))
<a name="L530" href="source/net/ipv4/tcp_input.c#L530">530</a>                 return;
<a name="L531" href="source/net/ipv4/tcp_input.c#L531">531</a>         <a href="ident?i=tcp_rcv_rtt_update">tcp_rcv_rtt_update</a>(<a href="ident?i=tp">tp</a>, <a href="ident?i=tcp_time_stamp">tcp_time_stamp</a> - <a href="ident?i=tp">tp</a>-&gt;rcv_rtt_est.<a href="ident?i=time">time</a>, 1);
<a name="L532" href="source/net/ipv4/tcp_input.c#L532">532</a> 
<a name="L533" href="source/net/ipv4/tcp_input.c#L533">533</a> new_measure:
<a name="L534" href="source/net/ipv4/tcp_input.c#L534">534</a>         <a href="ident?i=tp">tp</a>-&gt;rcv_rtt_est.<a href="ident?i=seq">seq</a> = <a href="ident?i=tp">tp</a>-&gt;rcv_nxt + <a href="ident?i=tp">tp</a>-&gt;rcv_wnd;
<a name="L535" href="source/net/ipv4/tcp_input.c#L535">535</a>         <a href="ident?i=tp">tp</a>-&gt;rcv_rtt_est.<a href="ident?i=time">time</a> = <a href="ident?i=tcp_time_stamp">tcp_time_stamp</a>;
<a name="L536" href="source/net/ipv4/tcp_input.c#L536">536</a> }
<a name="L537" href="source/net/ipv4/tcp_input.c#L537">537</a> 
<a name="L538" href="source/net/ipv4/tcp_input.c#L538">538</a> static inline void <a href="ident?i=tcp_rcv_rtt_measure_ts">tcp_rcv_rtt_measure_ts</a>(struct <a href="ident?i=sock">sock</a> *sk,
<a name="L539" href="source/net/ipv4/tcp_input.c#L539">539</a>                                           const struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L540" href="source/net/ipv4/tcp_input.c#L540">540</a> {
<a name="L541" href="source/net/ipv4/tcp_input.c#L541">541</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L542" href="source/net/ipv4/tcp_input.c#L542">542</a>         if (<a href="ident?i=tp">tp</a>-&gt;rx_opt.rcv_tsecr &amp;&amp;
<a name="L543" href="source/net/ipv4/tcp_input.c#L543">543</a>             (<a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;end_seq -
<a name="L544" href="source/net/ipv4/tcp_input.c#L544">544</a>              <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=seq">seq</a> &gt;= <a href="ident?i=inet_csk">inet_csk</a>(sk)-&gt;icsk_ack.rcv_mss))
<a name="L545" href="source/net/ipv4/tcp_input.c#L545">545</a>                 <a href="ident?i=tcp_rcv_rtt_update">tcp_rcv_rtt_update</a>(<a href="ident?i=tp">tp</a>, <a href="ident?i=tcp_time_stamp">tcp_time_stamp</a> - <a href="ident?i=tp">tp</a>-&gt;rx_opt.rcv_tsecr, 0);
<a name="L546" href="source/net/ipv4/tcp_input.c#L546">546</a> }
<a name="L547" href="source/net/ipv4/tcp_input.c#L547">547</a> 
<a name="L548" href="source/net/ipv4/tcp_input.c#L548">548</a> <b><i>/*</i></b>
<a name="L549" href="source/net/ipv4/tcp_input.c#L549">549</a> <b><i> * This function should be called every time data is copied to user space.</i></b>
<a name="L550" href="source/net/ipv4/tcp_input.c#L550">550</a> <b><i> * It calculates the appropriate TCP receive buffer space.</i></b>
<a name="L551" href="source/net/ipv4/tcp_input.c#L551">551</a> <b><i> */</i></b>
<a name="L552" href="source/net/ipv4/tcp_input.c#L552">552</a> void <a href="ident?i=tcp_rcv_space_adjust">tcp_rcv_space_adjust</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L553" href="source/net/ipv4/tcp_input.c#L553">553</a> {
<a name="L554" href="source/net/ipv4/tcp_input.c#L554">554</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L555" href="source/net/ipv4/tcp_input.c#L555">555</a>         int <a href="ident?i=time">time</a>;
<a name="L556" href="source/net/ipv4/tcp_input.c#L556">556</a>         int copied;
<a name="L557" href="source/net/ipv4/tcp_input.c#L557">557</a> 
<a name="L558" href="source/net/ipv4/tcp_input.c#L558">558</a>         <a href="ident?i=time">time</a> = <a href="ident?i=tcp_time_stamp">tcp_time_stamp</a> - <a href="ident?i=tp">tp</a>-&gt;rcvq_space.<a href="ident?i=time">time</a>;
<a name="L559" href="source/net/ipv4/tcp_input.c#L559">559</a>         if (<a href="ident?i=time">time</a> &lt; (<a href="ident?i=tp">tp</a>-&gt;rcv_rtt_est.rtt &gt;&gt; 3) || <a href="ident?i=tp">tp</a>-&gt;rcv_rtt_est.rtt == 0)
<a name="L560" href="source/net/ipv4/tcp_input.c#L560">560</a>                 return;
<a name="L561" href="source/net/ipv4/tcp_input.c#L561">561</a> 
<a name="L562" href="source/net/ipv4/tcp_input.c#L562">562</a>         <b><i>/* Number of bytes copied to user in last RTT */</i></b>
<a name="L563" href="source/net/ipv4/tcp_input.c#L563">563</a>         copied = <a href="ident?i=tp">tp</a>-&gt;copied_seq - <a href="ident?i=tp">tp</a>-&gt;rcvq_space.<a href="ident?i=seq">seq</a>;
<a name="L564" href="source/net/ipv4/tcp_input.c#L564">564</a>         if (copied &lt;= <a href="ident?i=tp">tp</a>-&gt;rcvq_space.<a href="ident?i=space">space</a>)
<a name="L565" href="source/net/ipv4/tcp_input.c#L565">565</a>                 goto new_measure;
<a name="L566" href="source/net/ipv4/tcp_input.c#L566">566</a> 
<a name="L567" href="source/net/ipv4/tcp_input.c#L567">567</a>         <b><i>/* A bit of theory :</i></b>
<a name="L568" href="source/net/ipv4/tcp_input.c#L568">568</a> <b><i>         * copied = bytes received in previous RTT, our base window</i></b>
<a name="L569" href="source/net/ipv4/tcp_input.c#L569">569</a> <b><i>         * To cope with packet losses, we need a 2x factor</i></b>
<a name="L570" href="source/net/ipv4/tcp_input.c#L570">570</a> <b><i>         * To cope with slow start, and sender growing its cwin by 100 %</i></b>
<a name="L571" href="source/net/ipv4/tcp_input.c#L571">571</a> <b><i>         * every RTT, we need a 4x factor, because the ACK we are sending</i></b>
<a name="L572" href="source/net/ipv4/tcp_input.c#L572">572</a> <b><i>         * now is for the next RTT, not the current one :</i></b>
<a name="L573" href="source/net/ipv4/tcp_input.c#L573">573</a> <b><i>         * &lt;prev RTT . &gt;&lt;current RTT .. &gt;&lt;next RTT .... &gt;</i></b>
<a name="L574" href="source/net/ipv4/tcp_input.c#L574">574</a> <b><i>         */</i></b>
<a name="L575" href="source/net/ipv4/tcp_input.c#L575">575</a> 
<a name="L576" href="source/net/ipv4/tcp_input.c#L576">576</a>         if (<a href="ident?i=sysctl_tcp_moderate_rcvbuf">sysctl_tcp_moderate_rcvbuf</a> &amp;&amp;
<a name="L577" href="source/net/ipv4/tcp_input.c#L577">577</a>             !(sk-&gt;sk_userlocks &amp; <a href="ident?i=SOCK_RCVBUF_LOCK">SOCK_RCVBUF_LOCK</a>)) {
<a name="L578" href="source/net/ipv4/tcp_input.c#L578">578</a>                 int rcvwin, rcvmem, rcvbuf;
<a name="L579" href="source/net/ipv4/tcp_input.c#L579">579</a> 
<a name="L580" href="source/net/ipv4/tcp_input.c#L580">580</a>                 <b><i>/* minimal window to cope with packet losses, assuming</i></b>
<a name="L581" href="source/net/ipv4/tcp_input.c#L581">581</a> <b><i>                 * steady state. Add some cushion because of small variations.</i></b>
<a name="L582" href="source/net/ipv4/tcp_input.c#L582">582</a> <b><i>                 */</i></b>
<a name="L583" href="source/net/ipv4/tcp_input.c#L583">583</a>                 rcvwin = (copied &lt;&lt; 1) + 16 * <a href="ident?i=tp">tp</a>-&gt;advmss;
<a name="L584" href="source/net/ipv4/tcp_input.c#L584">584</a> 
<a name="L585" href="source/net/ipv4/tcp_input.c#L585">585</a>                 <b><i>/* If rate increased by 25%,</i></b>
<a name="L586" href="source/net/ipv4/tcp_input.c#L586">586</a> <b><i>                 *      assume slow start, rcvwin = 3 * copied</i></b>
<a name="L587" href="source/net/ipv4/tcp_input.c#L587">587</a> <b><i>                 * If rate increased by 50%,</i></b>
<a name="L588" href="source/net/ipv4/tcp_input.c#L588">588</a> <b><i>                 *      assume sender can use 2x growth, rcvwin = 4 * copied</i></b>
<a name="L589" href="source/net/ipv4/tcp_input.c#L589">589</a> <b><i>                 */</i></b>
<a name="L590" href="source/net/ipv4/tcp_input.c#L590">590</a>                 if (copied &gt;=
<a name="L591" href="source/net/ipv4/tcp_input.c#L591">591</a>                     <a href="ident?i=tp">tp</a>-&gt;rcvq_space.<a href="ident?i=space">space</a> + (<a href="ident?i=tp">tp</a>-&gt;rcvq_space.<a href="ident?i=space">space</a> &gt;&gt; 2)) {
<a name="L592" href="source/net/ipv4/tcp_input.c#L592">592</a>                         if (copied &gt;=
<a name="L593" href="source/net/ipv4/tcp_input.c#L593">593</a>                             <a href="ident?i=tp">tp</a>-&gt;rcvq_space.<a href="ident?i=space">space</a> + (<a href="ident?i=tp">tp</a>-&gt;rcvq_space.<a href="ident?i=space">space</a> &gt;&gt; 1))
<a name="L594" href="source/net/ipv4/tcp_input.c#L594">594</a>                                 rcvwin &lt;&lt;= 1;
<a name="L595" href="source/net/ipv4/tcp_input.c#L595">595</a>                         else
<a name="L596" href="source/net/ipv4/tcp_input.c#L596">596</a>                                 rcvwin += (rcvwin &gt;&gt; 1);
<a name="L597" href="source/net/ipv4/tcp_input.c#L597">597</a>                 }
<a name="L598" href="source/net/ipv4/tcp_input.c#L598">598</a> 
<a name="L599" href="source/net/ipv4/tcp_input.c#L599">599</a>                 rcvmem = <a href="ident?i=SKB_TRUESIZE">SKB_TRUESIZE</a>(<a href="ident?i=tp">tp</a>-&gt;advmss + <a href="ident?i=MAX_TCP_HEADER">MAX_TCP_HEADER</a>);
<a name="L600" href="source/net/ipv4/tcp_input.c#L600">600</a>                 while (<a href="ident?i=tcp_win_from_space">tcp_win_from_space</a>(rcvmem) &lt; <a href="ident?i=tp">tp</a>-&gt;advmss)
<a name="L601" href="source/net/ipv4/tcp_input.c#L601">601</a>                         rcvmem += 128;
<a name="L602" href="source/net/ipv4/tcp_input.c#L602">602</a> 
<a name="L603" href="source/net/ipv4/tcp_input.c#L603">603</a>                 rcvbuf = <a href="ident?i=min">min</a>(rcvwin / <a href="ident?i=tp">tp</a>-&gt;advmss * rcvmem, <a href="ident?i=sysctl_tcp_rmem">sysctl_tcp_rmem</a>[2]);
<a name="L604" href="source/net/ipv4/tcp_input.c#L604">604</a>                 if (rcvbuf &gt; sk-&gt;sk_rcvbuf) {
<a name="L605" href="source/net/ipv4/tcp_input.c#L605">605</a>                         sk-&gt;sk_rcvbuf = rcvbuf;
<a name="L606" href="source/net/ipv4/tcp_input.c#L606">606</a> 
<a name="L607" href="source/net/ipv4/tcp_input.c#L607">607</a>                         <b><i>/* Make the window clamp follow along.  */</i></b>
<a name="L608" href="source/net/ipv4/tcp_input.c#L608">608</a>                         <a href="ident?i=tp">tp</a>-&gt;window_clamp = rcvwin;
<a name="L609" href="source/net/ipv4/tcp_input.c#L609">609</a>                 }
<a name="L610" href="source/net/ipv4/tcp_input.c#L610">610</a>         }
<a name="L611" href="source/net/ipv4/tcp_input.c#L611">611</a>         <a href="ident?i=tp">tp</a>-&gt;rcvq_space.<a href="ident?i=space">space</a> = copied;
<a name="L612" href="source/net/ipv4/tcp_input.c#L612">612</a> 
<a name="L613" href="source/net/ipv4/tcp_input.c#L613">613</a> new_measure:
<a name="L614" href="source/net/ipv4/tcp_input.c#L614">614</a>         <a href="ident?i=tp">tp</a>-&gt;rcvq_space.<a href="ident?i=seq">seq</a> = <a href="ident?i=tp">tp</a>-&gt;copied_seq;
<a name="L615" href="source/net/ipv4/tcp_input.c#L615">615</a>         <a href="ident?i=tp">tp</a>-&gt;rcvq_space.<a href="ident?i=time">time</a> = <a href="ident?i=tcp_time_stamp">tcp_time_stamp</a>;
<a name="L616" href="source/net/ipv4/tcp_input.c#L616">616</a> }
<a name="L617" href="source/net/ipv4/tcp_input.c#L617">617</a> 
<a name="L618" href="source/net/ipv4/tcp_input.c#L618">618</a> <b><i>/* There is something which you must keep in mind when you analyze the</i></b>
<a name="L619" href="source/net/ipv4/tcp_input.c#L619">619</a> <b><i> * behavior of the tp-&gt;ato delayed ack timeout interval.  When a</i></b>
<a name="L620" href="source/net/ipv4/tcp_input.c#L620">620</a> <b><i> * connection starts up, we want to ack as quickly as possible.  The</i></b>
<a name="L621" href="source/net/ipv4/tcp_input.c#L621">621</a> <b><i> * problem is that "good" TCP's do slow start at the beginning of data</i></b>
<a name="L622" href="source/net/ipv4/tcp_input.c#L622">622</a> <b><i> * transmission.  The means that until we send the first few ACK's the</i></b>
<a name="L623" href="source/net/ipv4/tcp_input.c#L623">623</a> <b><i> * sender will sit on his end and only queue most of his data, because</i></b>
<a name="L624" href="source/net/ipv4/tcp_input.c#L624">624</a> <b><i> * he can only send snd_cwnd unacked packets at any given time.  For</i></b>
<a name="L625" href="source/net/ipv4/tcp_input.c#L625">625</a> <b><i> * each ACK we send, he increments snd_cwnd and transmits more of his</i></b>
<a name="L626" href="source/net/ipv4/tcp_input.c#L626">626</a> <b><i> * queue.  -DaveM</i></b>
<a name="L627" href="source/net/ipv4/tcp_input.c#L627">627</a> <b><i> */</i></b>
<a name="L628" href="source/net/ipv4/tcp_input.c#L628">628</a> static void <a href="ident?i=tcp_event_data_recv">tcp_event_data_recv</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L629" href="source/net/ipv4/tcp_input.c#L629">629</a> {
<a name="L630" href="source/net/ipv4/tcp_input.c#L630">630</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L631" href="source/net/ipv4/tcp_input.c#L631">631</a>         struct <a href="ident?i=inet_connection_sock">inet_connection_sock</a> *icsk = <a href="ident?i=inet_csk">inet_csk</a>(sk);
<a name="L632" href="source/net/ipv4/tcp_input.c#L632">632</a>         <a href="ident?i=u32">u32</a> <a href="ident?i=now">now</a>;
<a name="L633" href="source/net/ipv4/tcp_input.c#L633">633</a> 
<a name="L634" href="source/net/ipv4/tcp_input.c#L634">634</a>         <a href="ident?i=inet_csk_schedule_ack">inet_csk_schedule_ack</a>(sk);
<a name="L635" href="source/net/ipv4/tcp_input.c#L635">635</a> 
<a name="L636" href="source/net/ipv4/tcp_input.c#L636">636</a>         <a href="ident?i=tcp_measure_rcv_mss">tcp_measure_rcv_mss</a>(sk, <a href="ident?i=skb">skb</a>);
<a name="L637" href="source/net/ipv4/tcp_input.c#L637">637</a> 
<a name="L638" href="source/net/ipv4/tcp_input.c#L638">638</a>         <a href="ident?i=tcp_rcv_rtt_measure">tcp_rcv_rtt_measure</a>(<a href="ident?i=tp">tp</a>);
<a name="L639" href="source/net/ipv4/tcp_input.c#L639">639</a> 
<a name="L640" href="source/net/ipv4/tcp_input.c#L640">640</a>         <a href="ident?i=now">now</a> = <a href="ident?i=tcp_time_stamp">tcp_time_stamp</a>;
<a name="L641" href="source/net/ipv4/tcp_input.c#L641">641</a> 
<a name="L642" href="source/net/ipv4/tcp_input.c#L642">642</a>         if (!icsk-&gt;icsk_ack.ato) {
<a name="L643" href="source/net/ipv4/tcp_input.c#L643">643</a>                 <b><i>/* The _first_ data packet received, initialize</i></b>
<a name="L644" href="source/net/ipv4/tcp_input.c#L644">644</a> <b><i>                 * delayed ACK engine.</i></b>
<a name="L645" href="source/net/ipv4/tcp_input.c#L645">645</a> <b><i>                 */</i></b>
<a name="L646" href="source/net/ipv4/tcp_input.c#L646">646</a>                 <a href="ident?i=tcp_incr_quickack">tcp_incr_quickack</a>(sk);
<a name="L647" href="source/net/ipv4/tcp_input.c#L647">647</a>                 icsk-&gt;icsk_ack.ato = <a href="ident?i=TCP_ATO_MIN">TCP_ATO_MIN</a>;
<a name="L648" href="source/net/ipv4/tcp_input.c#L648">648</a>         } else {
<a name="L649" href="source/net/ipv4/tcp_input.c#L649">649</a>                 int <a href="ident?i=m">m</a> = <a href="ident?i=now">now</a> - icsk-&gt;icsk_ack.lrcvtime;
<a name="L650" href="source/net/ipv4/tcp_input.c#L650">650</a> 
<a name="L651" href="source/net/ipv4/tcp_input.c#L651">651</a>                 if (<a href="ident?i=m">m</a> &lt;= <a href="ident?i=TCP_ATO_MIN">TCP_ATO_MIN</a> / 2) {
<a name="L652" href="source/net/ipv4/tcp_input.c#L652">652</a>                         <b><i>/* The fastest case is the first. */</i></b>
<a name="L653" href="source/net/ipv4/tcp_input.c#L653">653</a>                         icsk-&gt;icsk_ack.ato = (icsk-&gt;icsk_ack.ato &gt;&gt; 1) + <a href="ident?i=TCP_ATO_MIN">TCP_ATO_MIN</a> / 2;
<a name="L654" href="source/net/ipv4/tcp_input.c#L654">654</a>                 } else if (<a href="ident?i=m">m</a> &lt; icsk-&gt;icsk_ack.ato) {
<a name="L655" href="source/net/ipv4/tcp_input.c#L655">655</a>                         icsk-&gt;icsk_ack.ato = (icsk-&gt;icsk_ack.ato &gt;&gt; 1) + <a href="ident?i=m">m</a>;
<a name="L656" href="source/net/ipv4/tcp_input.c#L656">656</a>                         if (icsk-&gt;icsk_ack.ato &gt; icsk-&gt;icsk_rto)
<a name="L657" href="source/net/ipv4/tcp_input.c#L657">657</a>                                 icsk-&gt;icsk_ack.ato = icsk-&gt;icsk_rto;
<a name="L658" href="source/net/ipv4/tcp_input.c#L658">658</a>                 } else if (<a href="ident?i=m">m</a> &gt; icsk-&gt;icsk_rto) {
<a name="L659" href="source/net/ipv4/tcp_input.c#L659">659</a>                         <b><i>/* Too long gap. Apparently sender failed to</i></b>
<a name="L660" href="source/net/ipv4/tcp_input.c#L660">660</a> <b><i>                         * restart window, so that we send ACKs quickly.</i></b>
<a name="L661" href="source/net/ipv4/tcp_input.c#L661">661</a> <b><i>                         */</i></b>
<a name="L662" href="source/net/ipv4/tcp_input.c#L662">662</a>                         <a href="ident?i=tcp_incr_quickack">tcp_incr_quickack</a>(sk);
<a name="L663" href="source/net/ipv4/tcp_input.c#L663">663</a>                         <a href="ident?i=sk_mem_reclaim">sk_mem_reclaim</a>(sk);
<a name="L664" href="source/net/ipv4/tcp_input.c#L664">664</a>                 }
<a name="L665" href="source/net/ipv4/tcp_input.c#L665">665</a>         }
<a name="L666" href="source/net/ipv4/tcp_input.c#L666">666</a>         icsk-&gt;icsk_ack.lrcvtime = <a href="ident?i=now">now</a>;
<a name="L667" href="source/net/ipv4/tcp_input.c#L667">667</a> 
<a name="L668" href="source/net/ipv4/tcp_input.c#L668">668</a>         <a href="ident?i=tcp_ecn_check_ce">tcp_ecn_check_ce</a>(<a href="ident?i=tp">tp</a>, <a href="ident?i=skb">skb</a>);
<a name="L669" href="source/net/ipv4/tcp_input.c#L669">669</a> 
<a name="L670" href="source/net/ipv4/tcp_input.c#L670">670</a>         if (<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a> &gt;= 128)
<a name="L671" href="source/net/ipv4/tcp_input.c#L671">671</a>                 <a href="ident?i=tcp_grow_window">tcp_grow_window</a>(sk, <a href="ident?i=skb">skb</a>);
<a name="L672" href="source/net/ipv4/tcp_input.c#L672">672</a> }
<a name="L673" href="source/net/ipv4/tcp_input.c#L673">673</a> 
<a name="L674" href="source/net/ipv4/tcp_input.c#L674">674</a> <b><i>/* Called to compute a smoothed rtt estimate. The data fed to this</i></b>
<a name="L675" href="source/net/ipv4/tcp_input.c#L675">675</a> <b><i> * routine either comes from timestamps, or from segments that were</i></b>
<a name="L676" href="source/net/ipv4/tcp_input.c#L676">676</a> <b><i> * known _not_ to have been retransmitted [see Karn/Partridge</i></b>
<a name="L677" href="source/net/ipv4/tcp_input.c#L677">677</a> <b><i> * Proceedings SIGCOMM 87]. The algorithm is from the SIGCOMM 88</i></b>
<a name="L678" href="source/net/ipv4/tcp_input.c#L678">678</a> <b><i> * piece by Van Jacobson.</i></b>
<a name="L679" href="source/net/ipv4/tcp_input.c#L679">679</a> <b><i> * NOTE: the next three routines used to be one big routine.</i></b>
<a name="L680" href="source/net/ipv4/tcp_input.c#L680">680</a> <b><i> * To save cycles in the RFC 1323 implementation it was better to break</i></b>
<a name="L681" href="source/net/ipv4/tcp_input.c#L681">681</a> <b><i> * it up into three procedures. -- erics</i></b>
<a name="L682" href="source/net/ipv4/tcp_input.c#L682">682</a> <b><i> */</i></b>
<a name="L683" href="source/net/ipv4/tcp_input.c#L683">683</a> static void <a href="ident?i=tcp_rtt_estimator">tcp_rtt_estimator</a>(struct <a href="ident?i=sock">sock</a> *sk, long mrtt_us)
<a name="L684" href="source/net/ipv4/tcp_input.c#L684">684</a> {
<a name="L685" href="source/net/ipv4/tcp_input.c#L685">685</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L686" href="source/net/ipv4/tcp_input.c#L686">686</a>         long <a href="ident?i=m">m</a> = mrtt_us; <b><i>/* RTT */</i></b>
<a name="L687" href="source/net/ipv4/tcp_input.c#L687">687</a>         <a href="ident?i=u32">u32</a> srtt = <a href="ident?i=tp">tp</a>-&gt;srtt_us;
<a name="L688" href="source/net/ipv4/tcp_input.c#L688">688</a> 
<a name="L689" href="source/net/ipv4/tcp_input.c#L689">689</a>         <b><i>/*      The following amusing code comes from Jacobson's</i></b>
<a name="L690" href="source/net/ipv4/tcp_input.c#L690">690</a> <b><i>         *      article in SIGCOMM '88.  Note that rtt and mdev</i></b>
<a name="L691" href="source/net/ipv4/tcp_input.c#L691">691</a> <b><i>         *      are scaled versions of rtt and mean deviation.</i></b>
<a name="L692" href="source/net/ipv4/tcp_input.c#L692">692</a> <b><i>         *      This is designed to be as fast as possible</i></b>
<a name="L693" href="source/net/ipv4/tcp_input.c#L693">693</a> <b><i>         *      m stands for "measurement".</i></b>
<a name="L694" href="source/net/ipv4/tcp_input.c#L694">694</a> <b><i>         *</i></b>
<a name="L695" href="source/net/ipv4/tcp_input.c#L695">695</a> <b><i>         *      On a 1990 paper the rto value is changed to:</i></b>
<a name="L696" href="source/net/ipv4/tcp_input.c#L696">696</a> <b><i>         *      RTO = rtt + 4 * mdev</i></b>
<a name="L697" href="source/net/ipv4/tcp_input.c#L697">697</a> <b><i>         *</i></b>
<a name="L698" href="source/net/ipv4/tcp_input.c#L698">698</a> <b><i>         * Funny. This algorithm seems to be very broken.</i></b>
<a name="L699" href="source/net/ipv4/tcp_input.c#L699">699</a> <b><i>         * These formulae increase RTO, when it should be decreased, increase</i></b>
<a name="L700" href="source/net/ipv4/tcp_input.c#L700">700</a> <b><i>         * too slowly, when it should be increased quickly, decrease too quickly</i></b>
<a name="L701" href="source/net/ipv4/tcp_input.c#L701">701</a> <b><i>         * etc. I guess in BSD RTO takes ONE value, so that it is absolutely</i></b>
<a name="L702" href="source/net/ipv4/tcp_input.c#L702">702</a> <b><i>         * does not matter how to _calculate_ it. Seems, it was trap</i></b>
<a name="L703" href="source/net/ipv4/tcp_input.c#L703">703</a> <b><i>         * that VJ failed to avoid. 8)</i></b>
<a name="L704" href="source/net/ipv4/tcp_input.c#L704">704</a> <b><i>         */</i></b>
<a name="L705" href="source/net/ipv4/tcp_input.c#L705">705</a>         if (srtt != 0) {
<a name="L706" href="source/net/ipv4/tcp_input.c#L706">706</a>                 <a href="ident?i=m">m</a> -= (srtt &gt;&gt; 3);       <b><i>/* m is now error in rtt est */</i></b>
<a name="L707" href="source/net/ipv4/tcp_input.c#L707">707</a>                 srtt += <a href="ident?i=m">m</a>;              <b><i>/* rtt = 7/8 rtt + 1/8 new */</i></b>
<a name="L708" href="source/net/ipv4/tcp_input.c#L708">708</a>                 if (<a href="ident?i=m">m</a> &lt; 0) {
<a name="L709" href="source/net/ipv4/tcp_input.c#L709">709</a>                         <a href="ident?i=m">m</a> = -<a href="ident?i=m">m</a>;         <b><i>/* m is now abs(error) */</i></b>
<a name="L710" href="source/net/ipv4/tcp_input.c#L710">710</a>                         <a href="ident?i=m">m</a> -= (<a href="ident?i=tp">tp</a>-&gt;mdev_us &gt;&gt; 2);   <b><i>/* similar update on mdev */</i></b>
<a name="L711" href="source/net/ipv4/tcp_input.c#L711">711</a>                         <b><i>/* This is similar to one of Eifel findings.</i></b>
<a name="L712" href="source/net/ipv4/tcp_input.c#L712">712</a> <b><i>                         * Eifel blocks mdev updates when rtt decreases.</i></b>
<a name="L713" href="source/net/ipv4/tcp_input.c#L713">713</a> <b><i>                         * This solution is a bit different: we use finer gain</i></b>
<a name="L714" href="source/net/ipv4/tcp_input.c#L714">714</a> <b><i>                         * for mdev in this case (alpha*beta).</i></b>
<a name="L715" href="source/net/ipv4/tcp_input.c#L715">715</a> <b><i>                         * Like Eifel it also prevents growth of rto,</i></b>
<a name="L716" href="source/net/ipv4/tcp_input.c#L716">716</a> <b><i>                         * but also it limits too fast rto decreases,</i></b>
<a name="L717" href="source/net/ipv4/tcp_input.c#L717">717</a> <b><i>                         * happening in pure Eifel.</i></b>
<a name="L718" href="source/net/ipv4/tcp_input.c#L718">718</a> <b><i>                         */</i></b>
<a name="L719" href="source/net/ipv4/tcp_input.c#L719">719</a>                         if (<a href="ident?i=m">m</a> &gt; 0)
<a name="L720" href="source/net/ipv4/tcp_input.c#L720">720</a>                                 <a href="ident?i=m">m</a> &gt;&gt;= 3;
<a name="L721" href="source/net/ipv4/tcp_input.c#L721">721</a>                 } else {
<a name="L722" href="source/net/ipv4/tcp_input.c#L722">722</a>                         <a href="ident?i=m">m</a> -= (<a href="ident?i=tp">tp</a>-&gt;mdev_us &gt;&gt; 2);   <b><i>/* similar update on mdev */</i></b>
<a name="L723" href="source/net/ipv4/tcp_input.c#L723">723</a>                 }
<a name="L724" href="source/net/ipv4/tcp_input.c#L724">724</a>                 <a href="ident?i=tp">tp</a>-&gt;mdev_us += <a href="ident?i=m">m</a>;               <b><i>/* mdev = 3/4 mdev + 1/4 new */</i></b>
<a name="L725" href="source/net/ipv4/tcp_input.c#L725">725</a>                 if (<a href="ident?i=tp">tp</a>-&gt;mdev_us &gt; <a href="ident?i=tp">tp</a>-&gt;mdev_max_us) {
<a name="L726" href="source/net/ipv4/tcp_input.c#L726">726</a>                         <a href="ident?i=tp">tp</a>-&gt;mdev_max_us = <a href="ident?i=tp">tp</a>-&gt;mdev_us;
<a name="L727" href="source/net/ipv4/tcp_input.c#L727">727</a>                         if (<a href="ident?i=tp">tp</a>-&gt;mdev_max_us &gt; <a href="ident?i=tp">tp</a>-&gt;rttvar_us)
<a name="L728" href="source/net/ipv4/tcp_input.c#L728">728</a>                                 <a href="ident?i=tp">tp</a>-&gt;rttvar_us = <a href="ident?i=tp">tp</a>-&gt;mdev_max_us;
<a name="L729" href="source/net/ipv4/tcp_input.c#L729">729</a>                 }
<a name="L730" href="source/net/ipv4/tcp_input.c#L730">730</a>                 if (<a href="ident?i=after">after</a>(<a href="ident?i=tp">tp</a>-&gt;snd_una, <a href="ident?i=tp">tp</a>-&gt;rtt_seq)) {
<a name="L731" href="source/net/ipv4/tcp_input.c#L731">731</a>                         if (<a href="ident?i=tp">tp</a>-&gt;mdev_max_us &lt; <a href="ident?i=tp">tp</a>-&gt;rttvar_us)
<a name="L732" href="source/net/ipv4/tcp_input.c#L732">732</a>                                 <a href="ident?i=tp">tp</a>-&gt;rttvar_us -= (<a href="ident?i=tp">tp</a>-&gt;rttvar_us - <a href="ident?i=tp">tp</a>-&gt;mdev_max_us) &gt;&gt; 2;
<a name="L733" href="source/net/ipv4/tcp_input.c#L733">733</a>                         <a href="ident?i=tp">tp</a>-&gt;rtt_seq = <a href="ident?i=tp">tp</a>-&gt;snd_nxt;
<a name="L734" href="source/net/ipv4/tcp_input.c#L734">734</a>                         <a href="ident?i=tp">tp</a>-&gt;mdev_max_us = <a href="ident?i=tcp_rto_min_us">tcp_rto_min_us</a>(sk);
<a name="L735" href="source/net/ipv4/tcp_input.c#L735">735</a>                 }
<a name="L736" href="source/net/ipv4/tcp_input.c#L736">736</a>         } else {
<a name="L737" href="source/net/ipv4/tcp_input.c#L737">737</a>                 <b><i>/* no previous measure. */</i></b>
<a name="L738" href="source/net/ipv4/tcp_input.c#L738">738</a>                 srtt = <a href="ident?i=m">m</a> &lt;&lt; 3;          <b><i>/* take the measured time to be rtt */</i></b>
<a name="L739" href="source/net/ipv4/tcp_input.c#L739">739</a>                 <a href="ident?i=tp">tp</a>-&gt;mdev_us = <a href="ident?i=m">m</a> &lt;&lt; 1;   <b><i>/* make sure rto = 3*rtt */</i></b>
<a name="L740" href="source/net/ipv4/tcp_input.c#L740">740</a>                 <a href="ident?i=tp">tp</a>-&gt;rttvar_us = <a href="ident?i=max">max</a>(<a href="ident?i=tp">tp</a>-&gt;mdev_us, <a href="ident?i=tcp_rto_min_us">tcp_rto_min_us</a>(sk));
<a name="L741" href="source/net/ipv4/tcp_input.c#L741">741</a>                 <a href="ident?i=tp">tp</a>-&gt;mdev_max_us = <a href="ident?i=tp">tp</a>-&gt;rttvar_us;
<a name="L742" href="source/net/ipv4/tcp_input.c#L742">742</a>                 <a href="ident?i=tp">tp</a>-&gt;rtt_seq = <a href="ident?i=tp">tp</a>-&gt;snd_nxt;
<a name="L743" href="source/net/ipv4/tcp_input.c#L743">743</a>         }
<a name="L744" href="source/net/ipv4/tcp_input.c#L744">744</a>         <a href="ident?i=tp">tp</a>-&gt;srtt_us = <a href="ident?i=max">max</a>(1U, srtt);
<a name="L745" href="source/net/ipv4/tcp_input.c#L745">745</a> }
<a name="L746" href="source/net/ipv4/tcp_input.c#L746">746</a> 
<a name="L747" href="source/net/ipv4/tcp_input.c#L747">747</a> <b><i>/* Set the sk_pacing_rate to allow proper sizing of TSO packets.</i></b>
<a name="L748" href="source/net/ipv4/tcp_input.c#L748">748</a> <b><i> * Note: TCP stack does not yet implement pacing.</i></b>
<a name="L749" href="source/net/ipv4/tcp_input.c#L749">749</a> <b><i> * FQ packet scheduler can be used to implement cheap but effective</i></b>
<a name="L750" href="source/net/ipv4/tcp_input.c#L750">750</a> <b><i> * TCP pacing, to smooth the burst on large writes when packets</i></b>
<a name="L751" href="source/net/ipv4/tcp_input.c#L751">751</a> <b><i> * in flight is significantly lower than cwnd (or rwin)</i></b>
<a name="L752" href="source/net/ipv4/tcp_input.c#L752">752</a> <b><i> */</i></b>
<a name="L753" href="source/net/ipv4/tcp_input.c#L753">753</a> static void <a href="ident?i=tcp_update_pacing_rate">tcp_update_pacing_rate</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L754" href="source/net/ipv4/tcp_input.c#L754">754</a> {
<a name="L755" href="source/net/ipv4/tcp_input.c#L755">755</a>         const struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L756" href="source/net/ipv4/tcp_input.c#L756">756</a>         <a href="ident?i=u64">u64</a> <a href="ident?i=rate">rate</a>;
<a name="L757" href="source/net/ipv4/tcp_input.c#L757">757</a> 
<a name="L758" href="source/net/ipv4/tcp_input.c#L758">758</a>         <b><i>/* set sk_pacing_rate to 200 % of current rate (mss * cwnd / srtt) */</i></b>
<a name="L759" href="source/net/ipv4/tcp_input.c#L759">759</a>         <a href="ident?i=rate">rate</a> = (<a href="ident?i=u64">u64</a>)<a href="ident?i=tp">tp</a>-&gt;mss_cache * 2 * (<a href="ident?i=USEC_PER_SEC">USEC_PER_SEC</a> &lt;&lt; 3);
<a name="L760" href="source/net/ipv4/tcp_input.c#L760">760</a> 
<a name="L761" href="source/net/ipv4/tcp_input.c#L761">761</a>         <a href="ident?i=rate">rate</a> *= <a href="ident?i=max">max</a>(<a href="ident?i=tp">tp</a>-&gt;snd_cwnd, <a href="ident?i=tp">tp</a>-&gt;packets_out);
<a name="L762" href="source/net/ipv4/tcp_input.c#L762">762</a> 
<a name="L763" href="source/net/ipv4/tcp_input.c#L763">763</a>         if (<a href="ident?i=likely">likely</a>(<a href="ident?i=tp">tp</a>-&gt;srtt_us))
<a name="L764" href="source/net/ipv4/tcp_input.c#L764">764</a>                 <a href="ident?i=do_div">do_div</a>(<a href="ident?i=rate">rate</a>, <a href="ident?i=tp">tp</a>-&gt;srtt_us);
<a name="L765" href="source/net/ipv4/tcp_input.c#L765">765</a> 
<a name="L766" href="source/net/ipv4/tcp_input.c#L766">766</a>         <b><i>/* ACCESS_ONCE() is needed because sch_fq fetches sk_pacing_rate</i></b>
<a name="L767" href="source/net/ipv4/tcp_input.c#L767">767</a> <b><i>         * without any lock. We want to make sure compiler wont store</i></b>
<a name="L768" href="source/net/ipv4/tcp_input.c#L768">768</a> <b><i>         * intermediate values in this location.</i></b>
<a name="L769" href="source/net/ipv4/tcp_input.c#L769">769</a> <b><i>         */</i></b>
<a name="L770" href="source/net/ipv4/tcp_input.c#L770">770</a>         <a href="ident?i=ACCESS_ONCE">ACCESS_ONCE</a>(sk-&gt;sk_pacing_rate) = <a href="ident?i=min_t">min_t</a>(<a href="ident?i=u64">u64</a>, <a href="ident?i=rate">rate</a>,
<a name="L771" href="source/net/ipv4/tcp_input.c#L771">771</a>                                                 sk-&gt;sk_max_pacing_rate);
<a name="L772" href="source/net/ipv4/tcp_input.c#L772">772</a> }
<a name="L773" href="source/net/ipv4/tcp_input.c#L773">773</a> 
<a name="L774" href="source/net/ipv4/tcp_input.c#L774">774</a> <b><i>/* Calculate rto without backoff.  This is the second half of Van Jacobson's</i></b>
<a name="L775" href="source/net/ipv4/tcp_input.c#L775">775</a> <b><i> * routine referred to above.</i></b>
<a name="L776" href="source/net/ipv4/tcp_input.c#L776">776</a> <b><i> */</i></b>
<a name="L777" href="source/net/ipv4/tcp_input.c#L777">777</a> static void <a href="ident?i=tcp_set_rto">tcp_set_rto</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L778" href="source/net/ipv4/tcp_input.c#L778">778</a> {
<a name="L779" href="source/net/ipv4/tcp_input.c#L779">779</a>         const struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L780" href="source/net/ipv4/tcp_input.c#L780">780</a>         <b><i>/* Old crap is replaced with new one. 8)</i></b>
<a name="L781" href="source/net/ipv4/tcp_input.c#L781">781</a> <b><i>         *</i></b>
<a name="L782" href="source/net/ipv4/tcp_input.c#L782">782</a> <b><i>         * More seriously:</i></b>
<a name="L783" href="source/net/ipv4/tcp_input.c#L783">783</a> <b><i>         * 1. If rtt variance happened to be less 50msec, it is hallucination.</i></b>
<a name="L784" href="source/net/ipv4/tcp_input.c#L784">784</a> <b><i>         *    It cannot be less due to utterly erratic ACK generation made</i></b>
<a name="L785" href="source/net/ipv4/tcp_input.c#L785">785</a> <b><i>         *    at least by solaris and freebsd. "Erratic ACKs" has _nothing_</i></b>
<a name="L786" href="source/net/ipv4/tcp_input.c#L786">786</a> <b><i>         *    to do with delayed acks, because at cwnd&gt;2 true delack timeout</i></b>
<a name="L787" href="source/net/ipv4/tcp_input.c#L787">787</a> <b><i>         *    is invisible. Actually, Linux-2.4 also generates erratic</i></b>
<a name="L788" href="source/net/ipv4/tcp_input.c#L788">788</a> <b><i>         *    ACKs in some circumstances.</i></b>
<a name="L789" href="source/net/ipv4/tcp_input.c#L789">789</a> <b><i>         */</i></b>
<a name="L790" href="source/net/ipv4/tcp_input.c#L790">790</a>         <a href="ident?i=inet_csk">inet_csk</a>(sk)-&gt;icsk_rto = <a href="ident?i=__tcp_set_rto">__tcp_set_rto</a>(<a href="ident?i=tp">tp</a>);
<a name="L791" href="source/net/ipv4/tcp_input.c#L791">791</a> 
<a name="L792" href="source/net/ipv4/tcp_input.c#L792">792</a>         <b><i>/* 2. Fixups made earlier cannot be right.</i></b>
<a name="L793" href="source/net/ipv4/tcp_input.c#L793">793</a> <b><i>         *    If we do not estimate RTO correctly without them,</i></b>
<a name="L794" href="source/net/ipv4/tcp_input.c#L794">794</a> <b><i>         *    all the algo is pure shit and should be replaced</i></b>
<a name="L795" href="source/net/ipv4/tcp_input.c#L795">795</a> <b><i>         *    with correct one. It is exactly, which we pretend to do.</i></b>
<a name="L796" href="source/net/ipv4/tcp_input.c#L796">796</a> <b><i>         */</i></b>
<a name="L797" href="source/net/ipv4/tcp_input.c#L797">797</a> 
<a name="L798" href="source/net/ipv4/tcp_input.c#L798">798</a>         <b><i>/* NOTE: clamping at TCP_RTO_MIN is not required, current algo</i></b>
<a name="L799" href="source/net/ipv4/tcp_input.c#L799">799</a> <b><i>         * guarantees that rto is higher.</i></b>
<a name="L800" href="source/net/ipv4/tcp_input.c#L800">800</a> <b><i>         */</i></b>
<a name="L801" href="source/net/ipv4/tcp_input.c#L801">801</a>         <a href="ident?i=tcp_bound_rto">tcp_bound_rto</a>(sk);
<a name="L802" href="source/net/ipv4/tcp_input.c#L802">802</a> }
<a name="L803" href="source/net/ipv4/tcp_input.c#L803">803</a> 
<a name="L804" href="source/net/ipv4/tcp_input.c#L804">804</a> <a href="ident?i=__u32">__u32</a> <a href="ident?i=tcp_init_cwnd">tcp_init_cwnd</a>(const struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a>, const struct <a href="ident?i=dst_entry">dst_entry</a> *<a href="ident?i=dst">dst</a>)
<a name="L805" href="source/net/ipv4/tcp_input.c#L805">805</a> {
<a name="L806" href="source/net/ipv4/tcp_input.c#L806">806</a>         <a href="ident?i=__u32">__u32</a> cwnd = (<a href="ident?i=dst">dst</a> ? <a href="ident?i=dst_metric">dst_metric</a>(<a href="ident?i=dst">dst</a>, <a href="ident?i=RTAX_INITCWND">RTAX_INITCWND</a>) : 0);
<a name="L807" href="source/net/ipv4/tcp_input.c#L807">807</a> 
<a name="L808" href="source/net/ipv4/tcp_input.c#L808">808</a>         if (!cwnd)
<a name="L809" href="source/net/ipv4/tcp_input.c#L809">809</a>                 cwnd = <a href="ident?i=TCP_INIT_CWND">TCP_INIT_CWND</a>;
<a name="L810" href="source/net/ipv4/tcp_input.c#L810">810</a>         return <a href="ident?i=min_t">min_t</a>(<a href="ident?i=__u32">__u32</a>, cwnd, <a href="ident?i=tp">tp</a>-&gt;snd_cwnd_clamp);
<a name="L811" href="source/net/ipv4/tcp_input.c#L811">811</a> }
<a name="L812" href="source/net/ipv4/tcp_input.c#L812">812</a> 
<a name="L813" href="source/net/ipv4/tcp_input.c#L813">813</a> <b><i>/*</i></b>
<a name="L814" href="source/net/ipv4/tcp_input.c#L814">814</a> <b><i> * Packet counting of FACK is based on in-order assumptions, therefore TCP</i></b>
<a name="L815" href="source/net/ipv4/tcp_input.c#L815">815</a> <b><i> * disables it when reordering is detected</i></b>
<a name="L816" href="source/net/ipv4/tcp_input.c#L816">816</a> <b><i> */</i></b>
<a name="L817" href="source/net/ipv4/tcp_input.c#L817">817</a> void <a href="ident?i=tcp_disable_fack">tcp_disable_fack</a>(struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a>)
<a name="L818" href="source/net/ipv4/tcp_input.c#L818">818</a> {
<a name="L819" href="source/net/ipv4/tcp_input.c#L819">819</a>         <b><i>/* RFC3517 uses different metric in lost marker =&gt; reset on change */</i></b>
<a name="L820" href="source/net/ipv4/tcp_input.c#L820">820</a>         if (<a href="ident?i=tcp_is_fack">tcp_is_fack</a>(<a href="ident?i=tp">tp</a>))
<a name="L821" href="source/net/ipv4/tcp_input.c#L821">821</a>                 <a href="ident?i=tp">tp</a>-&gt;lost_skb_hint = <a href="ident?i=NULL">NULL</a>;
<a name="L822" href="source/net/ipv4/tcp_input.c#L822">822</a>         <a href="ident?i=tp">tp</a>-&gt;rx_opt.sack_ok &amp;= ~TCP_FACK_ENABLED;
<a name="L823" href="source/net/ipv4/tcp_input.c#L823">823</a> }
<a name="L824" href="source/net/ipv4/tcp_input.c#L824">824</a> 
<a name="L825" href="source/net/ipv4/tcp_input.c#L825">825</a> <b><i>/* Take a notice that peer is sending D-SACKs */</i></b>
<a name="L826" href="source/net/ipv4/tcp_input.c#L826">826</a> static void <a href="ident?i=tcp_dsack_seen">tcp_dsack_seen</a>(struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a>)
<a name="L827" href="source/net/ipv4/tcp_input.c#L827">827</a> {
<a name="L828" href="source/net/ipv4/tcp_input.c#L828">828</a>         <a href="ident?i=tp">tp</a>-&gt;rx_opt.sack_ok |= <a href="ident?i=TCP_DSACK_SEEN">TCP_DSACK_SEEN</a>;
<a name="L829" href="source/net/ipv4/tcp_input.c#L829">829</a> }
<a name="L830" href="source/net/ipv4/tcp_input.c#L830">830</a> 
<a name="L831" href="source/net/ipv4/tcp_input.c#L831">831</a> static void <a href="ident?i=tcp_update_reordering">tcp_update_reordering</a>(struct <a href="ident?i=sock">sock</a> *sk, const int metric,
<a name="L832" href="source/net/ipv4/tcp_input.c#L832">832</a>                                   const int <a href="ident?i=ts">ts</a>)
<a name="L833" href="source/net/ipv4/tcp_input.c#L833">833</a> {
<a name="L834" href="source/net/ipv4/tcp_input.c#L834">834</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L835" href="source/net/ipv4/tcp_input.c#L835">835</a>         if (metric &gt; <a href="ident?i=tp">tp</a>-&gt;reordering) {
<a name="L836" href="source/net/ipv4/tcp_input.c#L836">836</a>                 int mib_idx;
<a name="L837" href="source/net/ipv4/tcp_input.c#L837">837</a> 
<a name="L838" href="source/net/ipv4/tcp_input.c#L838">838</a>                 <a href="ident?i=tp">tp</a>-&gt;reordering = <a href="ident?i=min">min</a>(<a href="ident?i=sysctl_tcp_max_reordering">sysctl_tcp_max_reordering</a>, metric);
<a name="L839" href="source/net/ipv4/tcp_input.c#L839">839</a> 
<a name="L840" href="source/net/ipv4/tcp_input.c#L840">840</a>                 <b><i>/* This exciting event is worth to be remembered. 8) */</i></b>
<a name="L841" href="source/net/ipv4/tcp_input.c#L841">841</a>                 if (<a href="ident?i=ts">ts</a>)
<a name="L842" href="source/net/ipv4/tcp_input.c#L842">842</a>                         mib_idx = LINUX_MIB_TCPTSREORDER;
<a name="L843" href="source/net/ipv4/tcp_input.c#L843">843</a>                 else if (<a href="ident?i=tcp_is_reno">tcp_is_reno</a>(<a href="ident?i=tp">tp</a>))
<a name="L844" href="source/net/ipv4/tcp_input.c#L844">844</a>                         mib_idx = LINUX_MIB_TCPRENOREORDER;
<a name="L845" href="source/net/ipv4/tcp_input.c#L845">845</a>                 else if (<a href="ident?i=tcp_is_fack">tcp_is_fack</a>(<a href="ident?i=tp">tp</a>))
<a name="L846" href="source/net/ipv4/tcp_input.c#L846">846</a>                         mib_idx = LINUX_MIB_TCPFACKREORDER;
<a name="L847" href="source/net/ipv4/tcp_input.c#L847">847</a>                 else
<a name="L848" href="source/net/ipv4/tcp_input.c#L848">848</a>                         mib_idx = LINUX_MIB_TCPSACKREORDER;
<a name="L849" href="source/net/ipv4/tcp_input.c#L849">849</a> 
<a name="L850" href="source/net/ipv4/tcp_input.c#L850">850</a>                 <a href="ident?i=NET_INC_STATS_BH">NET_INC_STATS_BH</a>(<a href="ident?i=sock_net">sock_net</a>(sk), mib_idx);
<a name="L851" href="source/net/ipv4/tcp_input.c#L851">851</a> #if <a href="ident?i=FASTRETRANS_DEBUG">FASTRETRANS_DEBUG</a> &gt; 1
<a name="L852" href="source/net/ipv4/tcp_input.c#L852">852</a>                 <a href="ident?i=pr_debug">pr_debug</a>(<i>"Disorder%d %d %u f%u s%u rr%d\n"</i>,
<a name="L853" href="source/net/ipv4/tcp_input.c#L853">853</a>                          <a href="ident?i=tp">tp</a>-&gt;rx_opt.sack_ok, <a href="ident?i=inet_csk">inet_csk</a>(sk)-&gt;icsk_ca_state,
<a name="L854" href="source/net/ipv4/tcp_input.c#L854">854</a>                          <a href="ident?i=tp">tp</a>-&gt;reordering,
<a name="L855" href="source/net/ipv4/tcp_input.c#L855">855</a>                          <a href="ident?i=tp">tp</a>-&gt;fackets_out,
<a name="L856" href="source/net/ipv4/tcp_input.c#L856">856</a>                          <a href="ident?i=tp">tp</a>-&gt;sacked_out,
<a name="L857" href="source/net/ipv4/tcp_input.c#L857">857</a>                          <a href="ident?i=tp">tp</a>-&gt;undo_marker ? <a href="ident?i=tp">tp</a>-&gt;undo_retrans : 0);
<a name="L858" href="source/net/ipv4/tcp_input.c#L858">858</a> #endif
<a name="L859" href="source/net/ipv4/tcp_input.c#L859">859</a>                 <a href="ident?i=tcp_disable_fack">tcp_disable_fack</a>(<a href="ident?i=tp">tp</a>);
<a name="L860" href="source/net/ipv4/tcp_input.c#L860">860</a>         }
<a name="L861" href="source/net/ipv4/tcp_input.c#L861">861</a> 
<a name="L862" href="source/net/ipv4/tcp_input.c#L862">862</a>         if (metric &gt; 0)
<a name="L863" href="source/net/ipv4/tcp_input.c#L863">863</a>                 <a href="ident?i=tcp_disable_early_retrans">tcp_disable_early_retrans</a>(<a href="ident?i=tp">tp</a>);
<a name="L864" href="source/net/ipv4/tcp_input.c#L864">864</a> }
<a name="L865" href="source/net/ipv4/tcp_input.c#L865">865</a> 
<a name="L866" href="source/net/ipv4/tcp_input.c#L866">866</a> <b><i>/* This must be called before lost_out is incremented */</i></b>
<a name="L867" href="source/net/ipv4/tcp_input.c#L867">867</a> static void <a href="ident?i=tcp_verify_retransmit_hint">tcp_verify_retransmit_hint</a>(struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a>, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L868" href="source/net/ipv4/tcp_input.c#L868">868</a> {
<a name="L869" href="source/net/ipv4/tcp_input.c#L869">869</a>         if (!<a href="ident?i=tp">tp</a>-&gt;retransmit_skb_hint ||
<a name="L870" href="source/net/ipv4/tcp_input.c#L870">870</a>             <a href="ident?i=before">before</a>(<a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=seq">seq</a>,
<a name="L871" href="source/net/ipv4/tcp_input.c#L871">871</a>                    <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=tp">tp</a>-&gt;retransmit_skb_hint)-&gt;<a href="ident?i=seq">seq</a>))
<a name="L872" href="source/net/ipv4/tcp_input.c#L872">872</a>                 <a href="ident?i=tp">tp</a>-&gt;retransmit_skb_hint = <a href="ident?i=skb">skb</a>;
<a name="L873" href="source/net/ipv4/tcp_input.c#L873">873</a> 
<a name="L874" href="source/net/ipv4/tcp_input.c#L874">874</a>         if (!<a href="ident?i=tp">tp</a>-&gt;lost_out ||
<a name="L875" href="source/net/ipv4/tcp_input.c#L875">875</a>             <a href="ident?i=after">after</a>(<a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;end_seq, <a href="ident?i=tp">tp</a>-&gt;retransmit_high))
<a name="L876" href="source/net/ipv4/tcp_input.c#L876">876</a>                 <a href="ident?i=tp">tp</a>-&gt;retransmit_high = <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;end_seq;
<a name="L877" href="source/net/ipv4/tcp_input.c#L877">877</a> }
<a name="L878" href="source/net/ipv4/tcp_input.c#L878">878</a> 
<a name="L879" href="source/net/ipv4/tcp_input.c#L879">879</a> static void <a href="ident?i=tcp_skb_mark_lost">tcp_skb_mark_lost</a>(struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a>, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L880" href="source/net/ipv4/tcp_input.c#L880">880</a> {
<a name="L881" href="source/net/ipv4/tcp_input.c#L881">881</a>         if (!(<a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;sacked &amp; (<a href="ident?i=TCPCB_LOST">TCPCB_LOST</a>|<a href="ident?i=TCPCB_SACKED_ACKED">TCPCB_SACKED_ACKED</a>))) {
<a name="L882" href="source/net/ipv4/tcp_input.c#L882">882</a>                 <a href="ident?i=tcp_verify_retransmit_hint">tcp_verify_retransmit_hint</a>(<a href="ident?i=tp">tp</a>, <a href="ident?i=skb">skb</a>);
<a name="L883" href="source/net/ipv4/tcp_input.c#L883">883</a> 
<a name="L884" href="source/net/ipv4/tcp_input.c#L884">884</a>                 <a href="ident?i=tp">tp</a>-&gt;lost_out += <a href="ident?i=tcp_skb_pcount">tcp_skb_pcount</a>(<a href="ident?i=skb">skb</a>);
<a name="L885" href="source/net/ipv4/tcp_input.c#L885">885</a>                 <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;sacked |= <a href="ident?i=TCPCB_LOST">TCPCB_LOST</a>;
<a name="L886" href="source/net/ipv4/tcp_input.c#L886">886</a>         }
<a name="L887" href="source/net/ipv4/tcp_input.c#L887">887</a> }
<a name="L888" href="source/net/ipv4/tcp_input.c#L888">888</a> 
<a name="L889" href="source/net/ipv4/tcp_input.c#L889">889</a> static void <a href="ident?i=tcp_skb_mark_lost_uncond_verify">tcp_skb_mark_lost_uncond_verify</a>(struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a>,
<a name="L890" href="source/net/ipv4/tcp_input.c#L890">890</a>                                             struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L891" href="source/net/ipv4/tcp_input.c#L891">891</a> {
<a name="L892" href="source/net/ipv4/tcp_input.c#L892">892</a>         <a href="ident?i=tcp_verify_retransmit_hint">tcp_verify_retransmit_hint</a>(<a href="ident?i=tp">tp</a>, <a href="ident?i=skb">skb</a>);
<a name="L893" href="source/net/ipv4/tcp_input.c#L893">893</a> 
<a name="L894" href="source/net/ipv4/tcp_input.c#L894">894</a>         if (!(<a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;sacked &amp; (<a href="ident?i=TCPCB_LOST">TCPCB_LOST</a>|<a href="ident?i=TCPCB_SACKED_ACKED">TCPCB_SACKED_ACKED</a>))) {
<a name="L895" href="source/net/ipv4/tcp_input.c#L895">895</a>                 <a href="ident?i=tp">tp</a>-&gt;lost_out += <a href="ident?i=tcp_skb_pcount">tcp_skb_pcount</a>(<a href="ident?i=skb">skb</a>);
<a name="L896" href="source/net/ipv4/tcp_input.c#L896">896</a>                 <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;sacked |= <a href="ident?i=TCPCB_LOST">TCPCB_LOST</a>;
<a name="L897" href="source/net/ipv4/tcp_input.c#L897">897</a>         }
<a name="L898" href="source/net/ipv4/tcp_input.c#L898">898</a> }
<a name="L899" href="source/net/ipv4/tcp_input.c#L899">899</a> 
<a name="L900" href="source/net/ipv4/tcp_input.c#L900">900</a> <b><i>/* This procedure tags the retransmission queue when SACKs arrive.</i></b>
<a name="L901" href="source/net/ipv4/tcp_input.c#L901">901</a> <b><i> *</i></b>
<a name="L902" href="source/net/ipv4/tcp_input.c#L902">902</a> <b><i> * We have three tag bits: SACKED(S), RETRANS(R) and LOST(L).</i></b>
<a name="L903" href="source/net/ipv4/tcp_input.c#L903">903</a> <b><i> * Packets in queue with these bits set are counted in variables</i></b>
<a name="L904" href="source/net/ipv4/tcp_input.c#L904">904</a> <b><i> * sacked_out, retrans_out and lost_out, correspondingly.</i></b>
<a name="L905" href="source/net/ipv4/tcp_input.c#L905">905</a> <b><i> *</i></b>
<a name="L906" href="source/net/ipv4/tcp_input.c#L906">906</a> <b><i> * Valid combinations are:</i></b>
<a name="L907" href="source/net/ipv4/tcp_input.c#L907">907</a> <b><i> * Tag  InFlight        Description</i></b>
<a name="L908" href="source/net/ipv4/tcp_input.c#L908">908</a> <b><i> * 0    1               - orig segment is in flight.</i></b>
<a name="L909" href="source/net/ipv4/tcp_input.c#L909">909</a> <b><i> * S    0               - nothing flies, orig reached receiver.</i></b>
<a name="L910" href="source/net/ipv4/tcp_input.c#L910">910</a> <b><i> * L    0               - nothing flies, orig lost by net.</i></b>
<a name="L911" href="source/net/ipv4/tcp_input.c#L911">911</a> <b><i> * R    2               - both orig and retransmit are in flight.</i></b>
<a name="L912" href="source/net/ipv4/tcp_input.c#L912">912</a> <b><i> * L|R  1               - orig is lost, retransmit is in flight.</i></b>
<a name="L913" href="source/net/ipv4/tcp_input.c#L913">913</a> <b><i> * S|R  1               - orig reached receiver, retrans is still in flight.</i></b>
<a name="L914" href="source/net/ipv4/tcp_input.c#L914">914</a> <b><i> * (L|S|R is logically valid, it could occur when L|R is sacked,</i></b>
<a name="L915" href="source/net/ipv4/tcp_input.c#L915">915</a> <b><i> *  but it is equivalent to plain S and code short-curcuits it to S.</i></b>
<a name="L916" href="source/net/ipv4/tcp_input.c#L916">916</a> <b><i> *  L|S is logically invalid, it would mean -1 packet in flight 8))</i></b>
<a name="L917" href="source/net/ipv4/tcp_input.c#L917">917</a> <b><i> *</i></b>
<a name="L918" href="source/net/ipv4/tcp_input.c#L918">918</a> <b><i> * These 6 states form finite state machine, controlled by the following events:</i></b>
<a name="L919" href="source/net/ipv4/tcp_input.c#L919">919</a> <b><i> * 1. New ACK (+SACK) arrives. (tcp_sacktag_write_queue())</i></b>
<a name="L920" href="source/net/ipv4/tcp_input.c#L920">920</a> <b><i> * 2. Retransmission. (tcp_retransmit_skb(), tcp_xmit_retransmit_queue())</i></b>
<a name="L921" href="source/net/ipv4/tcp_input.c#L921">921</a> <b><i> * 3. Loss detection event of two flavors:</i></b>
<a name="L922" href="source/net/ipv4/tcp_input.c#L922">922</a> <b><i> *      A. Scoreboard estimator decided the packet is lost.</i></b>
<a name="L923" href="source/net/ipv4/tcp_input.c#L923">923</a> <b><i> *         A'. Reno "three dupacks" marks head of queue lost.</i></b>
<a name="L924" href="source/net/ipv4/tcp_input.c#L924">924</a> <b><i> *         A''. Its FACK modification, head until snd.fack is lost.</i></b>
<a name="L925" href="source/net/ipv4/tcp_input.c#L925">925</a> <b><i> *      B. SACK arrives sacking SND.NXT at the moment, when the</i></b>
<a name="L926" href="source/net/ipv4/tcp_input.c#L926">926</a> <b><i> *         segment was retransmitted.</i></b>
<a name="L927" href="source/net/ipv4/tcp_input.c#L927">927</a> <b><i> * 4. D-SACK added new rule: D-SACK changes any tag to S.</i></b>
<a name="L928" href="source/net/ipv4/tcp_input.c#L928">928</a> <b><i> *</i></b>
<a name="L929" href="source/net/ipv4/tcp_input.c#L929">929</a> <b><i> * It is pleasant to note, that state diagram turns out to be commutative,</i></b>
<a name="L930" href="source/net/ipv4/tcp_input.c#L930">930</a> <b><i> * so that we are allowed not to be bothered by order of our actions,</i></b>
<a name="L931" href="source/net/ipv4/tcp_input.c#L931">931</a> <b><i> * when multiple events arrive simultaneously. (see the function below).</i></b>
<a name="L932" href="source/net/ipv4/tcp_input.c#L932">932</a> <b><i> *</i></b>
<a name="L933" href="source/net/ipv4/tcp_input.c#L933">933</a> <b><i> * Reordering detection.</i></b>
<a name="L934" href="source/net/ipv4/tcp_input.c#L934">934</a> <b><i> * --------------------</i></b>
<a name="L935" href="source/net/ipv4/tcp_input.c#L935">935</a> <b><i> * Reordering metric is maximal distance, which a packet can be displaced</i></b>
<a name="L936" href="source/net/ipv4/tcp_input.c#L936">936</a> <b><i> * in packet stream. With SACKs we can estimate it:</i></b>
<a name="L937" href="source/net/ipv4/tcp_input.c#L937">937</a> <b><i> *</i></b>
<a name="L938" href="source/net/ipv4/tcp_input.c#L938">938</a> <b><i> * 1. SACK fills old hole and the corresponding segment was not</i></b>
<a name="L939" href="source/net/ipv4/tcp_input.c#L939">939</a> <b><i> *    ever retransmitted -&gt; reordering. Alas, we cannot use it</i></b>
<a name="L940" href="source/net/ipv4/tcp_input.c#L940">940</a> <b><i> *    when segment was retransmitted.</i></b>
<a name="L941" href="source/net/ipv4/tcp_input.c#L941">941</a> <b><i> * 2. The last flaw is solved with D-SACK. D-SACK arrives</i></b>
<a name="L942" href="source/net/ipv4/tcp_input.c#L942">942</a> <b><i> *    for retransmitted and already SACKed segment -&gt; reordering..</i></b>
<a name="L943" href="source/net/ipv4/tcp_input.c#L943">943</a> <b><i> * Both of these heuristics are not used in Loss state, when we cannot</i></b>
<a name="L944" href="source/net/ipv4/tcp_input.c#L944">944</a> <b><i> * account for retransmits accurately.</i></b>
<a name="L945" href="source/net/ipv4/tcp_input.c#L945">945</a> <b><i> *</i></b>
<a name="L946" href="source/net/ipv4/tcp_input.c#L946">946</a> <b><i> * SACK block validation.</i></b>
<a name="L947" href="source/net/ipv4/tcp_input.c#L947">947</a> <b><i> * ----------------------</i></b>
<a name="L948" href="source/net/ipv4/tcp_input.c#L948">948</a> <b><i> *</i></b>
<a name="L949" href="source/net/ipv4/tcp_input.c#L949">949</a> <b><i> * SACK block range validation checks that the received SACK block fits to</i></b>
<a name="L950" href="source/net/ipv4/tcp_input.c#L950">950</a> <b><i> * the expected sequence limits, i.e., it is between SND.UNA and SND.NXT.</i></b>
<a name="L951" href="source/net/ipv4/tcp_input.c#L951">951</a> <b><i> * Note that SND.UNA is not included to the range though being valid because</i></b>
<a name="L952" href="source/net/ipv4/tcp_input.c#L952">952</a> <b><i> * it means that the receiver is rather inconsistent with itself reporting</i></b>
<a name="L953" href="source/net/ipv4/tcp_input.c#L953">953</a> <b><i> * SACK reneging when it should advance SND.UNA. Such SACK block this is</i></b>
<a name="L954" href="source/net/ipv4/tcp_input.c#L954">954</a> <b><i> * perfectly valid, however, in light of RFC2018 which explicitly states</i></b>
<a name="L955" href="source/net/ipv4/tcp_input.c#L955">955</a> <b><i> * that "SACK block MUST reflect the newest segment.  Even if the newest</i></b>
<a name="L956" href="source/net/ipv4/tcp_input.c#L956">956</a> <b><i> * segment is going to be discarded ...", not that it looks very clever</i></b>
<a name="L957" href="source/net/ipv4/tcp_input.c#L957">957</a> <b><i> * in case of head skb. Due to potentional receiver driven attacks, we</i></b>
<a name="L958" href="source/net/ipv4/tcp_input.c#L958">958</a> <b><i> * choose to avoid immediate execution of a walk in write queue due to</i></b>
<a name="L959" href="source/net/ipv4/tcp_input.c#L959">959</a> <b><i> * reneging and defer head skb's loss recovery to standard loss recovery</i></b>
<a name="L960" href="source/net/ipv4/tcp_input.c#L960">960</a> <b><i> * procedure that will eventually trigger (nothing forbids us doing this).</i></b>
<a name="L961" href="source/net/ipv4/tcp_input.c#L961">961</a> <b><i> *</i></b>
<a name="L962" href="source/net/ipv4/tcp_input.c#L962">962</a> <b><i> * Implements also blockage to start_seq wrap-around. Problem lies in the</i></b>
<a name="L963" href="source/net/ipv4/tcp_input.c#L963">963</a> <b><i> * fact that though start_seq (s) is before end_seq (i.e., not reversed),</i></b>
<a name="L964" href="source/net/ipv4/tcp_input.c#L964">964</a> <b><i> * there's no guarantee that it will be before snd_nxt (n). The problem</i></b>
<a name="L965" href="source/net/ipv4/tcp_input.c#L965">965</a> <b><i> * happens when start_seq resides between end_seq wrap (e_w) and snd_nxt</i></b>
<a name="L966" href="source/net/ipv4/tcp_input.c#L966">966</a> <b><i> * wrap (s_w):</i></b>
<a name="L967" href="source/net/ipv4/tcp_input.c#L967">967</a> <b><i> *</i></b>
<a name="L968" href="source/net/ipv4/tcp_input.c#L968">968</a> <b><i> *         &lt;- outs wnd -&gt;                          &lt;- wrapzone -&gt;</i></b>
<a name="L969" href="source/net/ipv4/tcp_input.c#L969">969</a> <b><i> *         u     e      n                         u_w   e_w  s n_w</i></b>
<a name="L970" href="source/net/ipv4/tcp_input.c#L970">970</a> <b><i> *         |     |      |                          |     |   |  |</i></b>
<a name="L971" href="source/net/ipv4/tcp_input.c#L971">971</a> <b><i> * |&lt;------------+------+----- TCP seqno space --------------+----------&gt;|</i></b>
<a name="L972" href="source/net/ipv4/tcp_input.c#L972">972</a> <b><i> * ...-- &lt;2^31 -&gt;|                                           |&lt;--------...</i></b>
<a name="L973" href="source/net/ipv4/tcp_input.c#L973">973</a> <b><i> * ...---- &gt;2^31 ------&gt;|                                    |&lt;--------...</i></b>
<a name="L974" href="source/net/ipv4/tcp_input.c#L974">974</a> <b><i> *</i></b>
<a name="L975" href="source/net/ipv4/tcp_input.c#L975">975</a> <b><i> * Current code wouldn't be vulnerable but it's better still to discard such</i></b>
<a name="L976" href="source/net/ipv4/tcp_input.c#L976">976</a> <b><i> * crazy SACK blocks. Doing this check for start_seq alone closes somewhat</i></b>
<a name="L977" href="source/net/ipv4/tcp_input.c#L977">977</a> <b><i> * similar case (end_seq after snd_nxt wrap) as earlier reversed check in</i></b>
<a name="L978" href="source/net/ipv4/tcp_input.c#L978">978</a> <b><i> * snd_nxt wrap -&gt; snd_una region will then become "well defined", i.e.,</i></b>
<a name="L979" href="source/net/ipv4/tcp_input.c#L979">979</a> <b><i> * equal to the ideal case (infinite seqno space without wrap caused issues).</i></b>
<a name="L980" href="source/net/ipv4/tcp_input.c#L980">980</a> <b><i> *</i></b>
<a name="L981" href="source/net/ipv4/tcp_input.c#L981">981</a> <b><i> * With D-SACK the lower bound is extended to cover sequence space below</i></b>
<a name="L982" href="source/net/ipv4/tcp_input.c#L982">982</a> <b><i> * SND.UNA down to undo_marker, which is the last point of interest. Yet</i></b>
<a name="L983" href="source/net/ipv4/tcp_input.c#L983">983</a> <b><i> * again, D-SACK block must not to go across snd_una (for the same reason as</i></b>
<a name="L984" href="source/net/ipv4/tcp_input.c#L984">984</a> <b><i> * for the normal SACK blocks, explained above). But there all simplicity</i></b>
<a name="L985" href="source/net/ipv4/tcp_input.c#L985">985</a> <b><i> * ends, TCP might receive valid D-SACKs below that. As long as they reside</i></b>
<a name="L986" href="source/net/ipv4/tcp_input.c#L986">986</a> <b><i> * fully below undo_marker they do not affect behavior in anyway and can</i></b>
<a name="L987" href="source/net/ipv4/tcp_input.c#L987">987</a> <b><i> * therefore be safely ignored. In rare cases (which are more or less</i></b>
<a name="L988" href="source/net/ipv4/tcp_input.c#L988">988</a> <b><i> * theoretical ones), the D-SACK will nicely cross that boundary due to skb</i></b>
<a name="L989" href="source/net/ipv4/tcp_input.c#L989">989</a> <b><i> * fragmentation and packet reordering past skb's retransmission. To consider</i></b>
<a name="L990" href="source/net/ipv4/tcp_input.c#L990">990</a> <b><i> * them correctly, the acceptable range must be extended even more though</i></b>
<a name="L991" href="source/net/ipv4/tcp_input.c#L991">991</a> <b><i> * the exact amount is rather hard to quantify. However, tp-&gt;max_window can</i></b>
<a name="L992" href="source/net/ipv4/tcp_input.c#L992">992</a> <b><i> * be used as an exaggerated estimate.</i></b>
<a name="L993" href="source/net/ipv4/tcp_input.c#L993">993</a> <b><i> */</i></b>
<a name="L994" href="source/net/ipv4/tcp_input.c#L994">994</a> static <a href="ident?i=bool">bool</a> <a href="ident?i=tcp_is_sackblock_valid">tcp_is_sackblock_valid</a>(struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a>, <a href="ident?i=bool">bool</a> is_dsack,
<a name="L995" href="source/net/ipv4/tcp_input.c#L995">995</a>                                    <a href="ident?i=u32">u32</a> <a href="ident?i=start_seq">start_seq</a>, <a href="ident?i=u32">u32</a> end_seq)
<a name="L996" href="source/net/ipv4/tcp_input.c#L996">996</a> {
<a name="L997" href="source/net/ipv4/tcp_input.c#L997">997</a>         <b><i>/* Too far in future, or reversed (interpretation is ambiguous) */</i></b>
<a name="L998" href="source/net/ipv4/tcp_input.c#L998">998</a>         if (<a href="ident?i=after">after</a>(end_seq, <a href="ident?i=tp">tp</a>-&gt;snd_nxt) || !<a href="ident?i=before">before</a>(<a href="ident?i=start_seq">start_seq</a>, end_seq))
<a name="L999" href="source/net/ipv4/tcp_input.c#L999">999</a>                 return <a href="ident?i=false">false</a>;
<a name="L1000" href="source/net/ipv4/tcp_input.c#L1000">1000</a> 
<a name="L1001" href="source/net/ipv4/tcp_input.c#L1001">1001</a>         <b><i>/* Nasty start_seq wrap-around check (see comments above) */</i></b>
<a name="L1002" href="source/net/ipv4/tcp_input.c#L1002">1002</a>         if (!<a href="ident?i=before">before</a>(<a href="ident?i=start_seq">start_seq</a>, <a href="ident?i=tp">tp</a>-&gt;snd_nxt))
<a name="L1003" href="source/net/ipv4/tcp_input.c#L1003">1003</a>                 return <a href="ident?i=false">false</a>;
<a name="L1004" href="source/net/ipv4/tcp_input.c#L1004">1004</a> 
<a name="L1005" href="source/net/ipv4/tcp_input.c#L1005">1005</a>         <b><i>/* In outstanding window? ...This is valid exit for D-SACKs too.</i></b>
<a name="L1006" href="source/net/ipv4/tcp_input.c#L1006">1006</a> <b><i>         * start_seq == snd_una is non-sensical (see comments above)</i></b>
<a name="L1007" href="source/net/ipv4/tcp_input.c#L1007">1007</a> <b><i>         */</i></b>
<a name="L1008" href="source/net/ipv4/tcp_input.c#L1008">1008</a>         if (<a href="ident?i=after">after</a>(<a href="ident?i=start_seq">start_seq</a>, <a href="ident?i=tp">tp</a>-&gt;snd_una))
<a name="L1009" href="source/net/ipv4/tcp_input.c#L1009">1009</a>                 return <a href="ident?i=true">true</a>;
<a name="L1010" href="source/net/ipv4/tcp_input.c#L1010">1010</a> 
<a name="L1011" href="source/net/ipv4/tcp_input.c#L1011">1011</a>         if (!is_dsack || !<a href="ident?i=tp">tp</a>-&gt;undo_marker)
<a name="L1012" href="source/net/ipv4/tcp_input.c#L1012">1012</a>                 return <a href="ident?i=false">false</a>;
<a name="L1013" href="source/net/ipv4/tcp_input.c#L1013">1013</a> 
<a name="L1014" href="source/net/ipv4/tcp_input.c#L1014">1014</a>         <b><i>/* ...Then it's D-SACK, and must reside below snd_una completely */</i></b>
<a name="L1015" href="source/net/ipv4/tcp_input.c#L1015">1015</a>         if (<a href="ident?i=after">after</a>(end_seq, <a href="ident?i=tp">tp</a>-&gt;snd_una))
<a name="L1016" href="source/net/ipv4/tcp_input.c#L1016">1016</a>                 return <a href="ident?i=false">false</a>;
<a name="L1017" href="source/net/ipv4/tcp_input.c#L1017">1017</a> 
<a name="L1018" href="source/net/ipv4/tcp_input.c#L1018">1018</a>         if (!<a href="ident?i=before">before</a>(<a href="ident?i=start_seq">start_seq</a>, <a href="ident?i=tp">tp</a>-&gt;undo_marker))
<a name="L1019" href="source/net/ipv4/tcp_input.c#L1019">1019</a>                 return <a href="ident?i=true">true</a>;
<a name="L1020" href="source/net/ipv4/tcp_input.c#L1020">1020</a> 
<a name="L1021" href="source/net/ipv4/tcp_input.c#L1021">1021</a>         <b><i>/* Too old */</i></b>
<a name="L1022" href="source/net/ipv4/tcp_input.c#L1022">1022</a>         if (!<a href="ident?i=after">after</a>(end_seq, <a href="ident?i=tp">tp</a>-&gt;undo_marker))
<a name="L1023" href="source/net/ipv4/tcp_input.c#L1023">1023</a>                 return <a href="ident?i=false">false</a>;
<a name="L1024" href="source/net/ipv4/tcp_input.c#L1024">1024</a> 
<a name="L1025" href="source/net/ipv4/tcp_input.c#L1025">1025</a>         <b><i>/* Undo_marker boundary crossing (overestimates a lot). Known already:</i></b>
<a name="L1026" href="source/net/ipv4/tcp_input.c#L1026">1026</a> <b><i>         *   start_seq &lt; undo_marker and end_seq &gt;= undo_marker.</i></b>
<a name="L1027" href="source/net/ipv4/tcp_input.c#L1027">1027</a> <b><i>         */</i></b>
<a name="L1028" href="source/net/ipv4/tcp_input.c#L1028">1028</a>         return !<a href="ident?i=before">before</a>(<a href="ident?i=start_seq">start_seq</a>, end_seq - <a href="ident?i=tp">tp</a>-&gt;max_window);
<a name="L1029" href="source/net/ipv4/tcp_input.c#L1029">1029</a> }
<a name="L1030" href="source/net/ipv4/tcp_input.c#L1030">1030</a> 
<a name="L1031" href="source/net/ipv4/tcp_input.c#L1031">1031</a> <b><i>/* Check for lost retransmit. This superb idea is borrowed from "ratehalving".</i></b>
<a name="L1032" href="source/net/ipv4/tcp_input.c#L1032">1032</a> <b><i> * Event "B". Later note: FACK people cheated me again 8), we have to account</i></b>
<a name="L1033" href="source/net/ipv4/tcp_input.c#L1033">1033</a> <b><i> * for reordering! Ugly, but should help.</i></b>
<a name="L1034" href="source/net/ipv4/tcp_input.c#L1034">1034</a> <b><i> *</i></b>
<a name="L1035" href="source/net/ipv4/tcp_input.c#L1035">1035</a> <b><i> * Search retransmitted skbs from write_queue that were sent when snd_nxt was</i></b>
<a name="L1036" href="source/net/ipv4/tcp_input.c#L1036">1036</a> <b><i> * less than what is now known to be received by the other end (derived from</i></b>
<a name="L1037" href="source/net/ipv4/tcp_input.c#L1037">1037</a> <b><i> * highest SACK block). Also calculate the lowest snd_nxt among the remaining</i></b>
<a name="L1038" href="source/net/ipv4/tcp_input.c#L1038">1038</a> <b><i> * retransmitted skbs to avoid some costly processing per ACKs.</i></b>
<a name="L1039" href="source/net/ipv4/tcp_input.c#L1039">1039</a> <b><i> */</i></b>
<a name="L1040" href="source/net/ipv4/tcp_input.c#L1040">1040</a> static void <a href="ident?i=tcp_mark_lost_retrans">tcp_mark_lost_retrans</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L1041" href="source/net/ipv4/tcp_input.c#L1041">1041</a> {
<a name="L1042" href="source/net/ipv4/tcp_input.c#L1042">1042</a>         const struct <a href="ident?i=inet_connection_sock">inet_connection_sock</a> *icsk = <a href="ident?i=inet_csk">inet_csk</a>(sk);
<a name="L1043" href="source/net/ipv4/tcp_input.c#L1043">1043</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L1044" href="source/net/ipv4/tcp_input.c#L1044">1044</a>         struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>;
<a name="L1045" href="source/net/ipv4/tcp_input.c#L1045">1045</a>         int cnt = 0;
<a name="L1046" href="source/net/ipv4/tcp_input.c#L1046">1046</a>         <a href="ident?i=u32">u32</a> new_low_seq = <a href="ident?i=tp">tp</a>-&gt;snd_nxt;
<a name="L1047" href="source/net/ipv4/tcp_input.c#L1047">1047</a>         <a href="ident?i=u32">u32</a> received_upto = <a href="ident?i=tcp_highest_sack_seq">tcp_highest_sack_seq</a>(<a href="ident?i=tp">tp</a>);
<a name="L1048" href="source/net/ipv4/tcp_input.c#L1048">1048</a> 
<a name="L1049" href="source/net/ipv4/tcp_input.c#L1049">1049</a>         if (!<a href="ident?i=tcp_is_fack">tcp_is_fack</a>(<a href="ident?i=tp">tp</a>) || !<a href="ident?i=tp">tp</a>-&gt;retrans_out ||
<a name="L1050" href="source/net/ipv4/tcp_input.c#L1050">1050</a>             !<a href="ident?i=after">after</a>(received_upto, <a href="ident?i=tp">tp</a>-&gt;lost_retrans_low) ||
<a name="L1051" href="source/net/ipv4/tcp_input.c#L1051">1051</a>             icsk-&gt;icsk_ca_state != TCP_CA_Recovery)
<a name="L1052" href="source/net/ipv4/tcp_input.c#L1052">1052</a>                 return;
<a name="L1053" href="source/net/ipv4/tcp_input.c#L1053">1053</a> 
<a name="L1054" href="source/net/ipv4/tcp_input.c#L1054">1054</a>         <a href="ident?i=tcp_for_write_queue">tcp_for_write_queue</a>(<a href="ident?i=skb">skb</a>, sk) {
<a name="L1055" href="source/net/ipv4/tcp_input.c#L1055">1055</a>                 <a href="ident?i=u32">u32</a> ack_seq = <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;ack_seq;
<a name="L1056" href="source/net/ipv4/tcp_input.c#L1056">1056</a> 
<a name="L1057" href="source/net/ipv4/tcp_input.c#L1057">1057</a>                 if (<a href="ident?i=skb">skb</a> == <a href="ident?i=tcp_send_head">tcp_send_head</a>(sk))
<a name="L1058" href="source/net/ipv4/tcp_input.c#L1058">1058</a>                         break;
<a name="L1059" href="source/net/ipv4/tcp_input.c#L1059">1059</a>                 if (cnt == <a href="ident?i=tp">tp</a>-&gt;retrans_out)
<a name="L1060" href="source/net/ipv4/tcp_input.c#L1060">1060</a>                         break;
<a name="L1061" href="source/net/ipv4/tcp_input.c#L1061">1061</a>                 if (!<a href="ident?i=after">after</a>(<a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;end_seq, <a href="ident?i=tp">tp</a>-&gt;snd_una))
<a name="L1062" href="source/net/ipv4/tcp_input.c#L1062">1062</a>                         continue;
<a name="L1063" href="source/net/ipv4/tcp_input.c#L1063">1063</a> 
<a name="L1064" href="source/net/ipv4/tcp_input.c#L1064">1064</a>                 if (!(<a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;sacked &amp; <a href="ident?i=TCPCB_SACKED_RETRANS">TCPCB_SACKED_RETRANS</a>))
<a name="L1065" href="source/net/ipv4/tcp_input.c#L1065">1065</a>                         continue;
<a name="L1066" href="source/net/ipv4/tcp_input.c#L1066">1066</a> 
<a name="L1067" href="source/net/ipv4/tcp_input.c#L1067">1067</a>                 <b><i>/* TODO: We would like to get rid of tcp_is_fack(tp) only</i></b>
<a name="L1068" href="source/net/ipv4/tcp_input.c#L1068">1068</a> <b><i>                 * constraint here (see above) but figuring out that at</i></b>
<a name="L1069" href="source/net/ipv4/tcp_input.c#L1069">1069</a> <b><i>                 * least tp-&gt;reordering SACK blocks reside between ack_seq</i></b>
<a name="L1070" href="source/net/ipv4/tcp_input.c#L1070">1070</a> <b><i>                 * and received_upto is not easy task to do cheaply with</i></b>
<a name="L1071" href="source/net/ipv4/tcp_input.c#L1071">1071</a> <b><i>                 * the available datastructures.</i></b>
<a name="L1072" href="source/net/ipv4/tcp_input.c#L1072">1072</a> <b><i>                 *</i></b>
<a name="L1073" href="source/net/ipv4/tcp_input.c#L1073">1073</a> <b><i>                 * Whether FACK should check here for tp-&gt;reordering segs</i></b>
<a name="L1074" href="source/net/ipv4/tcp_input.c#L1074">1074</a> <b><i>                 * in-between one could argue for either way (it would be</i></b>
<a name="L1075" href="source/net/ipv4/tcp_input.c#L1075">1075</a> <b><i>                 * rather simple to implement as we could count fack_count</i></b>
<a name="L1076" href="source/net/ipv4/tcp_input.c#L1076">1076</a> <b><i>                 * during the walk and do tp-&gt;fackets_out - fack_count).</i></b>
<a name="L1077" href="source/net/ipv4/tcp_input.c#L1077">1077</a> <b><i>                 */</i></b>
<a name="L1078" href="source/net/ipv4/tcp_input.c#L1078">1078</a>                 if (<a href="ident?i=after">after</a>(received_upto, ack_seq)) {
<a name="L1079" href="source/net/ipv4/tcp_input.c#L1079">1079</a>                         <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;sacked &amp;= ~TCPCB_SACKED_RETRANS;
<a name="L1080" href="source/net/ipv4/tcp_input.c#L1080">1080</a>                         <a href="ident?i=tp">tp</a>-&gt;retrans_out -= <a href="ident?i=tcp_skb_pcount">tcp_skb_pcount</a>(<a href="ident?i=skb">skb</a>);
<a name="L1081" href="source/net/ipv4/tcp_input.c#L1081">1081</a> 
<a name="L1082" href="source/net/ipv4/tcp_input.c#L1082">1082</a>                         <a href="ident?i=tcp_skb_mark_lost_uncond_verify">tcp_skb_mark_lost_uncond_verify</a>(<a href="ident?i=tp">tp</a>, <a href="ident?i=skb">skb</a>);
<a name="L1083" href="source/net/ipv4/tcp_input.c#L1083">1083</a>                         <a href="ident?i=NET_INC_STATS_BH">NET_INC_STATS_BH</a>(<a href="ident?i=sock_net">sock_net</a>(sk), LINUX_MIB_TCPLOSTRETRANSMIT);
<a name="L1084" href="source/net/ipv4/tcp_input.c#L1084">1084</a>                 } else {
<a name="L1085" href="source/net/ipv4/tcp_input.c#L1085">1085</a>                         if (<a href="ident?i=before">before</a>(ack_seq, new_low_seq))
<a name="L1086" href="source/net/ipv4/tcp_input.c#L1086">1086</a>                                 new_low_seq = ack_seq;
<a name="L1087" href="source/net/ipv4/tcp_input.c#L1087">1087</a>                         cnt += <a href="ident?i=tcp_skb_pcount">tcp_skb_pcount</a>(<a href="ident?i=skb">skb</a>);
<a name="L1088" href="source/net/ipv4/tcp_input.c#L1088">1088</a>                 }
<a name="L1089" href="source/net/ipv4/tcp_input.c#L1089">1089</a>         }
<a name="L1090" href="source/net/ipv4/tcp_input.c#L1090">1090</a> 
<a name="L1091" href="source/net/ipv4/tcp_input.c#L1091">1091</a>         if (<a href="ident?i=tp">tp</a>-&gt;retrans_out)
<a name="L1092" href="source/net/ipv4/tcp_input.c#L1092">1092</a>                 <a href="ident?i=tp">tp</a>-&gt;lost_retrans_low = new_low_seq;
<a name="L1093" href="source/net/ipv4/tcp_input.c#L1093">1093</a> }
<a name="L1094" href="source/net/ipv4/tcp_input.c#L1094">1094</a> 
<a name="L1095" href="source/net/ipv4/tcp_input.c#L1095">1095</a> static <a href="ident?i=bool">bool</a> <a href="ident?i=tcp_check_dsack">tcp_check_dsack</a>(struct <a href="ident?i=sock">sock</a> *sk, const struct <a href="ident?i=sk_buff">sk_buff</a> *ack_skb,
<a name="L1096" href="source/net/ipv4/tcp_input.c#L1096">1096</a>                             struct <a href="ident?i=tcp_sack_block_wire">tcp_sack_block_wire</a> *<a href="ident?i=sp">sp</a>, int num_sacks,
<a name="L1097" href="source/net/ipv4/tcp_input.c#L1097">1097</a>                             <a href="ident?i=u32">u32</a> prior_snd_una)
<a name="L1098" href="source/net/ipv4/tcp_input.c#L1098">1098</a> {
<a name="L1099" href="source/net/ipv4/tcp_input.c#L1099">1099</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L1100" href="source/net/ipv4/tcp_input.c#L1100">1100</a>         <a href="ident?i=u32">u32</a> start_seq_0 = <a href="ident?i=get_unaligned_be32">get_unaligned_be32</a>(&amp;<a href="ident?i=sp">sp</a>[0].<a href="ident?i=start_seq">start_seq</a>);
<a name="L1101" href="source/net/ipv4/tcp_input.c#L1101">1101</a>         <a href="ident?i=u32">u32</a> end_seq_0 = <a href="ident?i=get_unaligned_be32">get_unaligned_be32</a>(&amp;<a href="ident?i=sp">sp</a>[0].end_seq);
<a name="L1102" href="source/net/ipv4/tcp_input.c#L1102">1102</a>         <a href="ident?i=bool">bool</a> dup_sack = <a href="ident?i=false">false</a>;
<a name="L1103" href="source/net/ipv4/tcp_input.c#L1103">1103</a> 
<a name="L1104" href="source/net/ipv4/tcp_input.c#L1104">1104</a>         if (<a href="ident?i=before">before</a>(start_seq_0, <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(ack_skb)-&gt;ack_seq)) {
<a name="L1105" href="source/net/ipv4/tcp_input.c#L1105">1105</a>                 dup_sack = <a href="ident?i=true">true</a>;
<a name="L1106" href="source/net/ipv4/tcp_input.c#L1106">1106</a>                 <a href="ident?i=tcp_dsack_seen">tcp_dsack_seen</a>(<a href="ident?i=tp">tp</a>);
<a name="L1107" href="source/net/ipv4/tcp_input.c#L1107">1107</a>                 <a href="ident?i=NET_INC_STATS_BH">NET_INC_STATS_BH</a>(<a href="ident?i=sock_net">sock_net</a>(sk), LINUX_MIB_TCPDSACKRECV);
<a name="L1108" href="source/net/ipv4/tcp_input.c#L1108">1108</a>         } else if (num_sacks &gt; 1) {
<a name="L1109" href="source/net/ipv4/tcp_input.c#L1109">1109</a>                 <a href="ident?i=u32">u32</a> end_seq_1 = <a href="ident?i=get_unaligned_be32">get_unaligned_be32</a>(&amp;<a href="ident?i=sp">sp</a>[1].end_seq);
<a name="L1110" href="source/net/ipv4/tcp_input.c#L1110">1110</a>                 <a href="ident?i=u32">u32</a> start_seq_1 = <a href="ident?i=get_unaligned_be32">get_unaligned_be32</a>(&amp;<a href="ident?i=sp">sp</a>[1].<a href="ident?i=start_seq">start_seq</a>);
<a name="L1111" href="source/net/ipv4/tcp_input.c#L1111">1111</a> 
<a name="L1112" href="source/net/ipv4/tcp_input.c#L1112">1112</a>                 if (!<a href="ident?i=after">after</a>(end_seq_0, end_seq_1) &amp;&amp;
<a name="L1113" href="source/net/ipv4/tcp_input.c#L1113">1113</a>                     !<a href="ident?i=before">before</a>(start_seq_0, start_seq_1)) {
<a name="L1114" href="source/net/ipv4/tcp_input.c#L1114">1114</a>                         dup_sack = <a href="ident?i=true">true</a>;
<a name="L1115" href="source/net/ipv4/tcp_input.c#L1115">1115</a>                         <a href="ident?i=tcp_dsack_seen">tcp_dsack_seen</a>(<a href="ident?i=tp">tp</a>);
<a name="L1116" href="source/net/ipv4/tcp_input.c#L1116">1116</a>                         <a href="ident?i=NET_INC_STATS_BH">NET_INC_STATS_BH</a>(<a href="ident?i=sock_net">sock_net</a>(sk),
<a name="L1117" href="source/net/ipv4/tcp_input.c#L1117">1117</a>                                         LINUX_MIB_TCPDSACKOFORECV);
<a name="L1118" href="source/net/ipv4/tcp_input.c#L1118">1118</a>                 }
<a name="L1119" href="source/net/ipv4/tcp_input.c#L1119">1119</a>         }
<a name="L1120" href="source/net/ipv4/tcp_input.c#L1120">1120</a> 
<a name="L1121" href="source/net/ipv4/tcp_input.c#L1121">1121</a>         <b><i>/* D-SACK for already forgotten data... Do dumb counting. */</i></b>
<a name="L1122" href="source/net/ipv4/tcp_input.c#L1122">1122</a>         if (dup_sack &amp;&amp; <a href="ident?i=tp">tp</a>-&gt;undo_marker &amp;&amp; <a href="ident?i=tp">tp</a>-&gt;undo_retrans &gt; 0 &amp;&amp;
<a name="L1123" href="source/net/ipv4/tcp_input.c#L1123">1123</a>             !<a href="ident?i=after">after</a>(end_seq_0, prior_snd_una) &amp;&amp;
<a name="L1124" href="source/net/ipv4/tcp_input.c#L1124">1124</a>             <a href="ident?i=after">after</a>(end_seq_0, <a href="ident?i=tp">tp</a>-&gt;undo_marker))
<a name="L1125" href="source/net/ipv4/tcp_input.c#L1125">1125</a>                 <a href="ident?i=tp">tp</a>-&gt;undo_retrans--;
<a name="L1126" href="source/net/ipv4/tcp_input.c#L1126">1126</a> 
<a name="L1127" href="source/net/ipv4/tcp_input.c#L1127">1127</a>         return dup_sack;
<a name="L1128" href="source/net/ipv4/tcp_input.c#L1128">1128</a> }
<a name="L1129" href="source/net/ipv4/tcp_input.c#L1129">1129</a> 
<a name="L1130" href="source/net/ipv4/tcp_input.c#L1130">1130</a> struct <a href="ident?i=tcp_sacktag_state">tcp_sacktag_state</a> {
<a name="L1131" href="source/net/ipv4/tcp_input.c#L1131">1131</a>         int     reord;
<a name="L1132" href="source/net/ipv4/tcp_input.c#L1132">1132</a>         int     fack_count;
<a name="L1133" href="source/net/ipv4/tcp_input.c#L1133">1133</a>         long    rtt_us; <b><i>/* RTT measured by SACKing never-retransmitted data */</i></b>
<a name="L1134" href="source/net/ipv4/tcp_input.c#L1134">1134</a>         int     <a href="ident?i=flag">flag</a>;
<a name="L1135" href="source/net/ipv4/tcp_input.c#L1135">1135</a> };
<a name="L1136" href="source/net/ipv4/tcp_input.c#L1136">1136</a> 
<a name="L1137" href="source/net/ipv4/tcp_input.c#L1137">1137</a> <b><i>/* Check if skb is fully within the SACK block. In presence of GSO skbs,</i></b>
<a name="L1138" href="source/net/ipv4/tcp_input.c#L1138">1138</a> <b><i> * the incoming SACK may not exactly match but we can find smaller MSS</i></b>
<a name="L1139" href="source/net/ipv4/tcp_input.c#L1139">1139</a> <b><i> * aligned portion of it that matches. Therefore we might need to fragment</i></b>
<a name="L1140" href="source/net/ipv4/tcp_input.c#L1140">1140</a> <b><i> * which may fail and creates some hassle (caller must handle error case</i></b>
<a name="L1141" href="source/net/ipv4/tcp_input.c#L1141">1141</a> <b><i> * returns).</i></b>
<a name="L1142" href="source/net/ipv4/tcp_input.c#L1142">1142</a> <b><i> *</i></b>
<a name="L1143" href="source/net/ipv4/tcp_input.c#L1143">1143</a> <b><i> * FIXME: this could be merged to shift decision code</i></b>
<a name="L1144" href="source/net/ipv4/tcp_input.c#L1144">1144</a> <b><i> */</i></b>
<a name="L1145" href="source/net/ipv4/tcp_input.c#L1145">1145</a> static int <a href="ident?i=tcp_match_skb_to_sack">tcp_match_skb_to_sack</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
<a name="L1146" href="source/net/ipv4/tcp_input.c#L1146">1146</a>                                   <a href="ident?i=u32">u32</a> <a href="ident?i=start_seq">start_seq</a>, <a href="ident?i=u32">u32</a> end_seq)
<a name="L1147" href="source/net/ipv4/tcp_input.c#L1147">1147</a> {
<a name="L1148" href="source/net/ipv4/tcp_input.c#L1148">1148</a>         int <a href="ident?i=err">err</a>;
<a name="L1149" href="source/net/ipv4/tcp_input.c#L1149">1149</a>         <a href="ident?i=bool">bool</a> in_sack;
<a name="L1150" href="source/net/ipv4/tcp_input.c#L1150">1150</a>         unsigned int pkt_len;
<a name="L1151" href="source/net/ipv4/tcp_input.c#L1151">1151</a>         unsigned int mss;
<a name="L1152" href="source/net/ipv4/tcp_input.c#L1152">1152</a> 
<a name="L1153" href="source/net/ipv4/tcp_input.c#L1153">1153</a>         in_sack = !<a href="ident?i=after">after</a>(<a href="ident?i=start_seq">start_seq</a>, <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=seq">seq</a>) &amp;&amp;
<a name="L1154" href="source/net/ipv4/tcp_input.c#L1154">1154</a>                   !<a href="ident?i=before">before</a>(end_seq, <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;end_seq);
<a name="L1155" href="source/net/ipv4/tcp_input.c#L1155">1155</a> 
<a name="L1156" href="source/net/ipv4/tcp_input.c#L1156">1156</a>         if (<a href="ident?i=tcp_skb_pcount">tcp_skb_pcount</a>(<a href="ident?i=skb">skb</a>) &gt; 1 &amp;&amp; !in_sack &amp;&amp;
<a name="L1157" href="source/net/ipv4/tcp_input.c#L1157">1157</a>             <a href="ident?i=after">after</a>(<a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;end_seq, <a href="ident?i=start_seq">start_seq</a>)) {
<a name="L1158" href="source/net/ipv4/tcp_input.c#L1158">1158</a>                 mss = <a href="ident?i=tcp_skb_mss">tcp_skb_mss</a>(<a href="ident?i=skb">skb</a>);
<a name="L1159" href="source/net/ipv4/tcp_input.c#L1159">1159</a>                 in_sack = !<a href="ident?i=after">after</a>(<a href="ident?i=start_seq">start_seq</a>, <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=seq">seq</a>);
<a name="L1160" href="source/net/ipv4/tcp_input.c#L1160">1160</a> 
<a name="L1161" href="source/net/ipv4/tcp_input.c#L1161">1161</a>                 if (!in_sack) {
<a name="L1162" href="source/net/ipv4/tcp_input.c#L1162">1162</a>                         pkt_len = <a href="ident?i=start_seq">start_seq</a> - <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=seq">seq</a>;
<a name="L1163" href="source/net/ipv4/tcp_input.c#L1163">1163</a>                         if (pkt_len &lt; mss)
<a name="L1164" href="source/net/ipv4/tcp_input.c#L1164">1164</a>                                 pkt_len = mss;
<a name="L1165" href="source/net/ipv4/tcp_input.c#L1165">1165</a>                 } else {
<a name="L1166" href="source/net/ipv4/tcp_input.c#L1166">1166</a>                         pkt_len = end_seq - <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=seq">seq</a>;
<a name="L1167" href="source/net/ipv4/tcp_input.c#L1167">1167</a>                         if (pkt_len &lt; mss)
<a name="L1168" href="source/net/ipv4/tcp_input.c#L1168">1168</a>                                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L1169" href="source/net/ipv4/tcp_input.c#L1169">1169</a>                 }
<a name="L1170" href="source/net/ipv4/tcp_input.c#L1170">1170</a> 
<a name="L1171" href="source/net/ipv4/tcp_input.c#L1171">1171</a>                 <b><i>/* Round if necessary so that SACKs cover only full MSSes</i></b>
<a name="L1172" href="source/net/ipv4/tcp_input.c#L1172">1172</a> <b><i>                 * and/or the remaining small portion (if present)</i></b>
<a name="L1173" href="source/net/ipv4/tcp_input.c#L1173">1173</a> <b><i>                 */</i></b>
<a name="L1174" href="source/net/ipv4/tcp_input.c#L1174">1174</a>                 if (pkt_len &gt; mss) {
<a name="L1175" href="source/net/ipv4/tcp_input.c#L1175">1175</a>                         unsigned int new_len = (pkt_len / mss) * mss;
<a name="L1176" href="source/net/ipv4/tcp_input.c#L1176">1176</a>                         if (!in_sack &amp;&amp; new_len &lt; pkt_len) {
<a name="L1177" href="source/net/ipv4/tcp_input.c#L1177">1177</a>                                 new_len += mss;
<a name="L1178" href="source/net/ipv4/tcp_input.c#L1178">1178</a>                                 if (new_len &gt;= <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a>)
<a name="L1179" href="source/net/ipv4/tcp_input.c#L1179">1179</a>                                         return 0;
<a name="L1180" href="source/net/ipv4/tcp_input.c#L1180">1180</a>                         }
<a name="L1181" href="source/net/ipv4/tcp_input.c#L1181">1181</a>                         pkt_len = new_len;
<a name="L1182" href="source/net/ipv4/tcp_input.c#L1182">1182</a>                 }
<a name="L1183" href="source/net/ipv4/tcp_input.c#L1183">1183</a>                 <a href="ident?i=err">err</a> = <a href="ident?i=tcp_fragment">tcp_fragment</a>(sk, <a href="ident?i=skb">skb</a>, pkt_len, mss, <a href="ident?i=GFP_ATOMIC">GFP_ATOMIC</a>);
<a name="L1184" href="source/net/ipv4/tcp_input.c#L1184">1184</a>                 if (<a href="ident?i=err">err</a> &lt; 0)
<a name="L1185" href="source/net/ipv4/tcp_input.c#L1185">1185</a>                         return <a href="ident?i=err">err</a>;
<a name="L1186" href="source/net/ipv4/tcp_input.c#L1186">1186</a>         }
<a name="L1187" href="source/net/ipv4/tcp_input.c#L1187">1187</a> 
<a name="L1188" href="source/net/ipv4/tcp_input.c#L1188">1188</a>         return in_sack;
<a name="L1189" href="source/net/ipv4/tcp_input.c#L1189">1189</a> }
<a name="L1190" href="source/net/ipv4/tcp_input.c#L1190">1190</a> 
<a name="L1191" href="source/net/ipv4/tcp_input.c#L1191">1191</a> <b><i>/* Mark the given newly-SACKed range as such, adjusting counters and hints. */</i></b>
<a name="L1192" href="source/net/ipv4/tcp_input.c#L1192">1192</a> static <a href="ident?i=u8">u8</a> <a href="ident?i=tcp_sacktag_one">tcp_sacktag_one</a>(struct <a href="ident?i=sock">sock</a> *sk,
<a name="L1193" href="source/net/ipv4/tcp_input.c#L1193">1193</a>                           struct <a href="ident?i=tcp_sacktag_state">tcp_sacktag_state</a> *<a href="ident?i=state">state</a>, <a href="ident?i=u8">u8</a> sacked,
<a name="L1194" href="source/net/ipv4/tcp_input.c#L1194">1194</a>                           <a href="ident?i=u32">u32</a> <a href="ident?i=start_seq">start_seq</a>, <a href="ident?i=u32">u32</a> end_seq,
<a name="L1195" href="source/net/ipv4/tcp_input.c#L1195">1195</a>                           int dup_sack, int pcount,
<a name="L1196" href="source/net/ipv4/tcp_input.c#L1196">1196</a>                           const struct <a href="ident?i=skb_mstamp">skb_mstamp</a> *xmit_time)
<a name="L1197" href="source/net/ipv4/tcp_input.c#L1197">1197</a> {
<a name="L1198" href="source/net/ipv4/tcp_input.c#L1198">1198</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L1199" href="source/net/ipv4/tcp_input.c#L1199">1199</a>         int fack_count = <a href="ident?i=state">state</a>-&gt;fack_count;
<a name="L1200" href="source/net/ipv4/tcp_input.c#L1200">1200</a> 
<a name="L1201" href="source/net/ipv4/tcp_input.c#L1201">1201</a>         <b><i>/* Account D-SACK for retransmitted packet. */</i></b>
<a name="L1202" href="source/net/ipv4/tcp_input.c#L1202">1202</a>         if (dup_sack &amp;&amp; (sacked &amp; <a href="ident?i=TCPCB_RETRANS">TCPCB_RETRANS</a>)) {
<a name="L1203" href="source/net/ipv4/tcp_input.c#L1203">1203</a>                 if (<a href="ident?i=tp">tp</a>-&gt;undo_marker &amp;&amp; <a href="ident?i=tp">tp</a>-&gt;undo_retrans &gt; 0 &amp;&amp;
<a name="L1204" href="source/net/ipv4/tcp_input.c#L1204">1204</a>                     <a href="ident?i=after">after</a>(end_seq, <a href="ident?i=tp">tp</a>-&gt;undo_marker))
<a name="L1205" href="source/net/ipv4/tcp_input.c#L1205">1205</a>                         <a href="ident?i=tp">tp</a>-&gt;undo_retrans--;
<a name="L1206" href="source/net/ipv4/tcp_input.c#L1206">1206</a>                 if (sacked &amp; <a href="ident?i=TCPCB_SACKED_ACKED">TCPCB_SACKED_ACKED</a>)
<a name="L1207" href="source/net/ipv4/tcp_input.c#L1207">1207</a>                         <a href="ident?i=state">state</a>-&gt;reord = <a href="ident?i=min">min</a>(fack_count, <a href="ident?i=state">state</a>-&gt;reord);
<a name="L1208" href="source/net/ipv4/tcp_input.c#L1208">1208</a>         }
<a name="L1209" href="source/net/ipv4/tcp_input.c#L1209">1209</a> 
<a name="L1210" href="source/net/ipv4/tcp_input.c#L1210">1210</a>         <b><i>/* Nothing to do; acked frame is about to be dropped (was ACKed). */</i></b>
<a name="L1211" href="source/net/ipv4/tcp_input.c#L1211">1211</a>         if (!<a href="ident?i=after">after</a>(end_seq, <a href="ident?i=tp">tp</a>-&gt;snd_una))
<a name="L1212" href="source/net/ipv4/tcp_input.c#L1212">1212</a>                 return sacked;
<a name="L1213" href="source/net/ipv4/tcp_input.c#L1213">1213</a> 
<a name="L1214" href="source/net/ipv4/tcp_input.c#L1214">1214</a>         if (!(sacked &amp; <a href="ident?i=TCPCB_SACKED_ACKED">TCPCB_SACKED_ACKED</a>)) {
<a name="L1215" href="source/net/ipv4/tcp_input.c#L1215">1215</a>                 if (sacked &amp; <a href="ident?i=TCPCB_SACKED_RETRANS">TCPCB_SACKED_RETRANS</a>) {
<a name="L1216" href="source/net/ipv4/tcp_input.c#L1216">1216</a>                         <b><i>/* If the segment is not tagged as lost,</i></b>
<a name="L1217" href="source/net/ipv4/tcp_input.c#L1217">1217</a> <b><i>                         * we do not clear RETRANS, believing</i></b>
<a name="L1218" href="source/net/ipv4/tcp_input.c#L1218">1218</a> <b><i>                         * that retransmission is still in flight.</i></b>
<a name="L1219" href="source/net/ipv4/tcp_input.c#L1219">1219</a> <b><i>                         */</i></b>
<a name="L1220" href="source/net/ipv4/tcp_input.c#L1220">1220</a>                         if (sacked &amp; <a href="ident?i=TCPCB_LOST">TCPCB_LOST</a>) {
<a name="L1221" href="source/net/ipv4/tcp_input.c#L1221">1221</a>                                 sacked &amp;= ~(<a href="ident?i=TCPCB_LOST">TCPCB_LOST</a>|<a href="ident?i=TCPCB_SACKED_RETRANS">TCPCB_SACKED_RETRANS</a>);
<a name="L1222" href="source/net/ipv4/tcp_input.c#L1222">1222</a>                                 <a href="ident?i=tp">tp</a>-&gt;lost_out -= pcount;
<a name="L1223" href="source/net/ipv4/tcp_input.c#L1223">1223</a>                                 <a href="ident?i=tp">tp</a>-&gt;retrans_out -= pcount;
<a name="L1224" href="source/net/ipv4/tcp_input.c#L1224">1224</a>                         }
<a name="L1225" href="source/net/ipv4/tcp_input.c#L1225">1225</a>                 } else {
<a name="L1226" href="source/net/ipv4/tcp_input.c#L1226">1226</a>                         if (!(sacked &amp; <a href="ident?i=TCPCB_RETRANS">TCPCB_RETRANS</a>)) {
<a name="L1227" href="source/net/ipv4/tcp_input.c#L1227">1227</a>                                 <b><i>/* New sack for not retransmitted frame,</i></b>
<a name="L1228" href="source/net/ipv4/tcp_input.c#L1228">1228</a> <b><i>                                 * which was in hole. It is reordering.</i></b>
<a name="L1229" href="source/net/ipv4/tcp_input.c#L1229">1229</a> <b><i>                                 */</i></b>
<a name="L1230" href="source/net/ipv4/tcp_input.c#L1230">1230</a>                                 if (<a href="ident?i=before">before</a>(<a href="ident?i=start_seq">start_seq</a>,
<a name="L1231" href="source/net/ipv4/tcp_input.c#L1231">1231</a>                                            <a href="ident?i=tcp_highest_sack_seq">tcp_highest_sack_seq</a>(<a href="ident?i=tp">tp</a>)))
<a name="L1232" href="source/net/ipv4/tcp_input.c#L1232">1232</a>                                         <a href="ident?i=state">state</a>-&gt;reord = <a href="ident?i=min">min</a>(fack_count,
<a name="L1233" href="source/net/ipv4/tcp_input.c#L1233">1233</a>                                                            <a href="ident?i=state">state</a>-&gt;reord);
<a name="L1234" href="source/net/ipv4/tcp_input.c#L1234">1234</a>                                 if (!<a href="ident?i=after">after</a>(end_seq, <a href="ident?i=tp">tp</a>-&gt;high_seq))
<a name="L1235" href="source/net/ipv4/tcp_input.c#L1235">1235</a>                                         <a href="ident?i=state">state</a>-&gt;<a href="ident?i=flag">flag</a> |= <a href="ident?i=FLAG_ORIG_SACK_ACKED">FLAG_ORIG_SACK_ACKED</a>;
<a name="L1236" href="source/net/ipv4/tcp_input.c#L1236">1236</a>                                 <b><i>/* Pick the earliest sequence sacked for RTT */</i></b>
<a name="L1237" href="source/net/ipv4/tcp_input.c#L1237">1237</a>                                 if (<a href="ident?i=state">state</a>-&gt;rtt_us &lt; 0) {
<a name="L1238" href="source/net/ipv4/tcp_input.c#L1238">1238</a>                                         struct <a href="ident?i=skb_mstamp">skb_mstamp</a> <a href="ident?i=now">now</a>;
<a name="L1239" href="source/net/ipv4/tcp_input.c#L1239">1239</a> 
<a name="L1240" href="source/net/ipv4/tcp_input.c#L1240">1240</a>                                         <a href="ident?i=skb_mstamp_get">skb_mstamp_get</a>(&amp;<a href="ident?i=now">now</a>);
<a name="L1241" href="source/net/ipv4/tcp_input.c#L1241">1241</a>                                         <a href="ident?i=state">state</a>-&gt;rtt_us = <a href="ident?i=skb_mstamp_us_delta">skb_mstamp_us_delta</a>(&amp;<a href="ident?i=now">now</a>,
<a name="L1242" href="source/net/ipv4/tcp_input.c#L1242">1242</a>                                                                 xmit_time);
<a name="L1243" href="source/net/ipv4/tcp_input.c#L1243">1243</a>                                 }
<a name="L1244" href="source/net/ipv4/tcp_input.c#L1244">1244</a>                         }
<a name="L1245" href="source/net/ipv4/tcp_input.c#L1245">1245</a> 
<a name="L1246" href="source/net/ipv4/tcp_input.c#L1246">1246</a>                         if (sacked &amp; <a href="ident?i=TCPCB_LOST">TCPCB_LOST</a>) {
<a name="L1247" href="source/net/ipv4/tcp_input.c#L1247">1247</a>                                 sacked &amp;= ~TCPCB_LOST;
<a name="L1248" href="source/net/ipv4/tcp_input.c#L1248">1248</a>                                 <a href="ident?i=tp">tp</a>-&gt;lost_out -= pcount;
<a name="L1249" href="source/net/ipv4/tcp_input.c#L1249">1249</a>                         }
<a name="L1250" href="source/net/ipv4/tcp_input.c#L1250">1250</a>                 }
<a name="L1251" href="source/net/ipv4/tcp_input.c#L1251">1251</a> 
<a name="L1252" href="source/net/ipv4/tcp_input.c#L1252">1252</a>                 sacked |= <a href="ident?i=TCPCB_SACKED_ACKED">TCPCB_SACKED_ACKED</a>;
<a name="L1253" href="source/net/ipv4/tcp_input.c#L1253">1253</a>                 <a href="ident?i=state">state</a>-&gt;<a href="ident?i=flag">flag</a> |= <a href="ident?i=FLAG_DATA_SACKED">FLAG_DATA_SACKED</a>;
<a name="L1254" href="source/net/ipv4/tcp_input.c#L1254">1254</a>                 <a href="ident?i=tp">tp</a>-&gt;sacked_out += pcount;
<a name="L1255" href="source/net/ipv4/tcp_input.c#L1255">1255</a> 
<a name="L1256" href="source/net/ipv4/tcp_input.c#L1256">1256</a>                 fack_count += pcount;
<a name="L1257" href="source/net/ipv4/tcp_input.c#L1257">1257</a> 
<a name="L1258" href="source/net/ipv4/tcp_input.c#L1258">1258</a>                 <b><i>/* Lost marker hint past SACKed? Tweak RFC3517 cnt */</i></b>
<a name="L1259" href="source/net/ipv4/tcp_input.c#L1259">1259</a>                 if (!<a href="ident?i=tcp_is_fack">tcp_is_fack</a>(<a href="ident?i=tp">tp</a>) &amp;&amp; <a href="ident?i=tp">tp</a>-&gt;lost_skb_hint &amp;&amp;
<a name="L1260" href="source/net/ipv4/tcp_input.c#L1260">1260</a>                     <a href="ident?i=before">before</a>(<a href="ident?i=start_seq">start_seq</a>, <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=tp">tp</a>-&gt;lost_skb_hint)-&gt;<a href="ident?i=seq">seq</a>))
<a name="L1261" href="source/net/ipv4/tcp_input.c#L1261">1261</a>                         <a href="ident?i=tp">tp</a>-&gt;lost_cnt_hint += pcount;
<a name="L1262" href="source/net/ipv4/tcp_input.c#L1262">1262</a> 
<a name="L1263" href="source/net/ipv4/tcp_input.c#L1263">1263</a>                 if (fack_count &gt; <a href="ident?i=tp">tp</a>-&gt;fackets_out)
<a name="L1264" href="source/net/ipv4/tcp_input.c#L1264">1264</a>                         <a href="ident?i=tp">tp</a>-&gt;fackets_out = fack_count;
<a name="L1265" href="source/net/ipv4/tcp_input.c#L1265">1265</a>         }
<a name="L1266" href="source/net/ipv4/tcp_input.c#L1266">1266</a> 
<a name="L1267" href="source/net/ipv4/tcp_input.c#L1267">1267</a>         <b><i>/* D-SACK. We can detect redundant retransmission in S|R and plain R</i></b>
<a name="L1268" href="source/net/ipv4/tcp_input.c#L1268">1268</a> <b><i>         * frames and clear it. undo_retrans is decreased above, L|R frames</i></b>
<a name="L1269" href="source/net/ipv4/tcp_input.c#L1269">1269</a> <b><i>         * are accounted above as well.</i></b>
<a name="L1270" href="source/net/ipv4/tcp_input.c#L1270">1270</a> <b><i>         */</i></b>
<a name="L1271" href="source/net/ipv4/tcp_input.c#L1271">1271</a>         if (dup_sack &amp;&amp; (sacked &amp; <a href="ident?i=TCPCB_SACKED_RETRANS">TCPCB_SACKED_RETRANS</a>)) {
<a name="L1272" href="source/net/ipv4/tcp_input.c#L1272">1272</a>                 sacked &amp;= ~TCPCB_SACKED_RETRANS;
<a name="L1273" href="source/net/ipv4/tcp_input.c#L1273">1273</a>                 <a href="ident?i=tp">tp</a>-&gt;retrans_out -= pcount;
<a name="L1274" href="source/net/ipv4/tcp_input.c#L1274">1274</a>         }
<a name="L1275" href="source/net/ipv4/tcp_input.c#L1275">1275</a> 
<a name="L1276" href="source/net/ipv4/tcp_input.c#L1276">1276</a>         return sacked;
<a name="L1277" href="source/net/ipv4/tcp_input.c#L1277">1277</a> }
<a name="L1278" href="source/net/ipv4/tcp_input.c#L1278">1278</a> 
<a name="L1279" href="source/net/ipv4/tcp_input.c#L1279">1279</a> <b><i>/* Shift newly-SACKed bytes from this skb to the immediately previous</i></b>
<a name="L1280" href="source/net/ipv4/tcp_input.c#L1280">1280</a> <b><i> * already-SACKed sk_buff. Mark the newly-SACKed bytes as such.</i></b>
<a name="L1281" href="source/net/ipv4/tcp_input.c#L1281">1281</a> <b><i> */</i></b>
<a name="L1282" href="source/net/ipv4/tcp_input.c#L1282">1282</a> static <a href="ident?i=bool">bool</a> <a href="ident?i=tcp_shifted_skb">tcp_shifted_skb</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
<a name="L1283" href="source/net/ipv4/tcp_input.c#L1283">1283</a>                             struct <a href="ident?i=tcp_sacktag_state">tcp_sacktag_state</a> *<a href="ident?i=state">state</a>,
<a name="L1284" href="source/net/ipv4/tcp_input.c#L1284">1284</a>                             unsigned int pcount, int shifted, int mss,
<a name="L1285" href="source/net/ipv4/tcp_input.c#L1285">1285</a>                             <a href="ident?i=bool">bool</a> dup_sack)
<a name="L1286" href="source/net/ipv4/tcp_input.c#L1286">1286</a> {
<a name="L1287" href="source/net/ipv4/tcp_input.c#L1287">1287</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L1288" href="source/net/ipv4/tcp_input.c#L1288">1288</a>         struct <a href="ident?i=sk_buff">sk_buff</a> *prev = <a href="ident?i=tcp_write_queue_prev">tcp_write_queue_prev</a>(sk, <a href="ident?i=skb">skb</a>);
<a name="L1289" href="source/net/ipv4/tcp_input.c#L1289">1289</a>         <a href="ident?i=u32">u32</a> <a href="ident?i=start_seq">start_seq</a> = <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=seq">seq</a>;   <b><i>/* start of newly-SACKed */</i></b>
<a name="L1290" href="source/net/ipv4/tcp_input.c#L1290">1290</a>         <a href="ident?i=u32">u32</a> end_seq = <a href="ident?i=start_seq">start_seq</a> + shifted;      <b><i>/* end of newly-SACKed */</i></b>
<a name="L1291" href="source/net/ipv4/tcp_input.c#L1291">1291</a> 
<a name="L1292" href="source/net/ipv4/tcp_input.c#L1292">1292</a>         <a href="ident?i=BUG_ON">BUG_ON</a>(!pcount);
<a name="L1293" href="source/net/ipv4/tcp_input.c#L1293">1293</a> 
<a name="L1294" href="source/net/ipv4/tcp_input.c#L1294">1294</a>         <b><i>/* Adjust counters and hints for the newly sacked sequence</i></b>
<a name="L1295" href="source/net/ipv4/tcp_input.c#L1295">1295</a> <b><i>         * range but discard the return value since prev is already</i></b>
<a name="L1296" href="source/net/ipv4/tcp_input.c#L1296">1296</a> <b><i>         * marked. We must tag the range first because the seq</i></b>
<a name="L1297" href="source/net/ipv4/tcp_input.c#L1297">1297</a> <b><i>         * advancement below implicitly advances</i></b>
<a name="L1298" href="source/net/ipv4/tcp_input.c#L1298">1298</a> <b><i>         * tcp_highest_sack_seq() when skb is highest_sack.</i></b>
<a name="L1299" href="source/net/ipv4/tcp_input.c#L1299">1299</a> <b><i>         */</i></b>
<a name="L1300" href="source/net/ipv4/tcp_input.c#L1300">1300</a>         <a href="ident?i=tcp_sacktag_one">tcp_sacktag_one</a>(sk, <a href="ident?i=state">state</a>, <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;sacked,
<a name="L1301" href="source/net/ipv4/tcp_input.c#L1301">1301</a>                         <a href="ident?i=start_seq">start_seq</a>, end_seq, dup_sack, pcount,
<a name="L1302" href="source/net/ipv4/tcp_input.c#L1302">1302</a>                         &amp;<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=skb_mstamp">skb_mstamp</a>);
<a name="L1303" href="source/net/ipv4/tcp_input.c#L1303">1303</a> 
<a name="L1304" href="source/net/ipv4/tcp_input.c#L1304">1304</a>         if (<a href="ident?i=skb">skb</a> == <a href="ident?i=tp">tp</a>-&gt;lost_skb_hint)
<a name="L1305" href="source/net/ipv4/tcp_input.c#L1305">1305</a>                 <a href="ident?i=tp">tp</a>-&gt;lost_cnt_hint += pcount;
<a name="L1306" href="source/net/ipv4/tcp_input.c#L1306">1306</a> 
<a name="L1307" href="source/net/ipv4/tcp_input.c#L1307">1307</a>         <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(prev)-&gt;end_seq += shifted;
<a name="L1308" href="source/net/ipv4/tcp_input.c#L1308">1308</a>         <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=seq">seq</a> += shifted;
<a name="L1309" href="source/net/ipv4/tcp_input.c#L1309">1309</a> 
<a name="L1310" href="source/net/ipv4/tcp_input.c#L1310">1310</a>         <a href="ident?i=tcp_skb_pcount_add">tcp_skb_pcount_add</a>(prev, pcount);
<a name="L1311" href="source/net/ipv4/tcp_input.c#L1311">1311</a>         <a href="ident?i=BUG_ON">BUG_ON</a>(<a href="ident?i=tcp_skb_pcount">tcp_skb_pcount</a>(<a href="ident?i=skb">skb</a>) &lt; pcount);
<a name="L1312" href="source/net/ipv4/tcp_input.c#L1312">1312</a>         <a href="ident?i=tcp_skb_pcount_add">tcp_skb_pcount_add</a>(<a href="ident?i=skb">skb</a>, -pcount);
<a name="L1313" href="source/net/ipv4/tcp_input.c#L1313">1313</a> 
<a name="L1314" href="source/net/ipv4/tcp_input.c#L1314">1314</a>         <b><i>/* When we're adding to gso_segs == 1, gso_size will be zero,</i></b>
<a name="L1315" href="source/net/ipv4/tcp_input.c#L1315">1315</a> <b><i>         * in theory this shouldn't be necessary but as long as DSACK</i></b>
<a name="L1316" href="source/net/ipv4/tcp_input.c#L1316">1316</a> <b><i>         * code can come after this skb later on it's better to keep</i></b>
<a name="L1317" href="source/net/ipv4/tcp_input.c#L1317">1317</a> <b><i>         * setting gso_size to something.</i></b>
<a name="L1318" href="source/net/ipv4/tcp_input.c#L1318">1318</a> <b><i>         */</i></b>
<a name="L1319" href="source/net/ipv4/tcp_input.c#L1319">1319</a>         if (!<a href="ident?i=skb_shinfo">skb_shinfo</a>(prev)-&gt;gso_size) {
<a name="L1320" href="source/net/ipv4/tcp_input.c#L1320">1320</a>                 <a href="ident?i=skb_shinfo">skb_shinfo</a>(prev)-&gt;gso_size = mss;
<a name="L1321" href="source/net/ipv4/tcp_input.c#L1321">1321</a>                 <a href="ident?i=skb_shinfo">skb_shinfo</a>(prev)-&gt;gso_type = sk-&gt;sk_gso_type;
<a name="L1322" href="source/net/ipv4/tcp_input.c#L1322">1322</a>         }
<a name="L1323" href="source/net/ipv4/tcp_input.c#L1323">1323</a> 
<a name="L1324" href="source/net/ipv4/tcp_input.c#L1324">1324</a>         <b><i>/* CHECKME: To clear or not to clear? Mimics normal skb currently */</i></b>
<a name="L1325" href="source/net/ipv4/tcp_input.c#L1325">1325</a>         if (<a href="ident?i=tcp_skb_pcount">tcp_skb_pcount</a>(<a href="ident?i=skb">skb</a>) &lt;= 1) {
<a name="L1326" href="source/net/ipv4/tcp_input.c#L1326">1326</a>                 <a href="ident?i=skb_shinfo">skb_shinfo</a>(<a href="ident?i=skb">skb</a>)-&gt;gso_size = 0;
<a name="L1327" href="source/net/ipv4/tcp_input.c#L1327">1327</a>                 <a href="ident?i=skb_shinfo">skb_shinfo</a>(<a href="ident?i=skb">skb</a>)-&gt;gso_type = 0;
<a name="L1328" href="source/net/ipv4/tcp_input.c#L1328">1328</a>         }
<a name="L1329" href="source/net/ipv4/tcp_input.c#L1329">1329</a> 
<a name="L1330" href="source/net/ipv4/tcp_input.c#L1330">1330</a>         <b><i>/* Difference in this won't matter, both ACKed by the same cumul. ACK */</i></b>
<a name="L1331" href="source/net/ipv4/tcp_input.c#L1331">1331</a>         <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(prev)-&gt;sacked |= (<a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;sacked &amp; <a href="ident?i=TCPCB_EVER_RETRANS">TCPCB_EVER_RETRANS</a>);
<a name="L1332" href="source/net/ipv4/tcp_input.c#L1332">1332</a> 
<a name="L1333" href="source/net/ipv4/tcp_input.c#L1333">1333</a>         if (<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a> &gt; 0) {
<a name="L1334" href="source/net/ipv4/tcp_input.c#L1334">1334</a>                 <a href="ident?i=BUG_ON">BUG_ON</a>(!<a href="ident?i=tcp_skb_pcount">tcp_skb_pcount</a>(<a href="ident?i=skb">skb</a>));
<a name="L1335" href="source/net/ipv4/tcp_input.c#L1335">1335</a>                 <a href="ident?i=NET_INC_STATS_BH">NET_INC_STATS_BH</a>(<a href="ident?i=sock_net">sock_net</a>(sk), LINUX_MIB_SACKSHIFTED);
<a name="L1336" href="source/net/ipv4/tcp_input.c#L1336">1336</a>                 return <a href="ident?i=false">false</a>;
<a name="L1337" href="source/net/ipv4/tcp_input.c#L1337">1337</a>         }
<a name="L1338" href="source/net/ipv4/tcp_input.c#L1338">1338</a> 
<a name="L1339" href="source/net/ipv4/tcp_input.c#L1339">1339</a>         <b><i>/* Whole SKB was eaten :-) */</i></b>
<a name="L1340" href="source/net/ipv4/tcp_input.c#L1340">1340</a> 
<a name="L1341" href="source/net/ipv4/tcp_input.c#L1341">1341</a>         if (<a href="ident?i=skb">skb</a> == <a href="ident?i=tp">tp</a>-&gt;retransmit_skb_hint)
<a name="L1342" href="source/net/ipv4/tcp_input.c#L1342">1342</a>                 <a href="ident?i=tp">tp</a>-&gt;retransmit_skb_hint = prev;
<a name="L1343" href="source/net/ipv4/tcp_input.c#L1343">1343</a>         if (<a href="ident?i=skb">skb</a> == <a href="ident?i=tp">tp</a>-&gt;lost_skb_hint) {
<a name="L1344" href="source/net/ipv4/tcp_input.c#L1344">1344</a>                 <a href="ident?i=tp">tp</a>-&gt;lost_skb_hint = prev;
<a name="L1345" href="source/net/ipv4/tcp_input.c#L1345">1345</a>                 <a href="ident?i=tp">tp</a>-&gt;lost_cnt_hint -= <a href="ident?i=tcp_skb_pcount">tcp_skb_pcount</a>(prev);
<a name="L1346" href="source/net/ipv4/tcp_input.c#L1346">1346</a>         }
<a name="L1347" href="source/net/ipv4/tcp_input.c#L1347">1347</a> 
<a name="L1348" href="source/net/ipv4/tcp_input.c#L1348">1348</a>         <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(prev)-&gt;tcp_flags |= <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;tcp_flags;
<a name="L1349" href="source/net/ipv4/tcp_input.c#L1349">1349</a>         if (<a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;tcp_flags &amp; <a href="ident?i=TCPHDR_FIN">TCPHDR_FIN</a>)
<a name="L1350" href="source/net/ipv4/tcp_input.c#L1350">1350</a>                 <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(prev)-&gt;end_seq++;
<a name="L1351" href="source/net/ipv4/tcp_input.c#L1351">1351</a> 
<a name="L1352" href="source/net/ipv4/tcp_input.c#L1352">1352</a>         if (<a href="ident?i=skb">skb</a> == <a href="ident?i=tcp_highest_sack">tcp_highest_sack</a>(sk))
<a name="L1353" href="source/net/ipv4/tcp_input.c#L1353">1353</a>                 <a href="ident?i=tcp_advance_highest_sack">tcp_advance_highest_sack</a>(sk, <a href="ident?i=skb">skb</a>);
<a name="L1354" href="source/net/ipv4/tcp_input.c#L1354">1354</a> 
<a name="L1355" href="source/net/ipv4/tcp_input.c#L1355">1355</a>         <a href="ident?i=tcp_unlink_write_queue">tcp_unlink_write_queue</a>(<a href="ident?i=skb">skb</a>, sk);
<a name="L1356" href="source/net/ipv4/tcp_input.c#L1356">1356</a>         <a href="ident?i=sk_wmem_free_skb">sk_wmem_free_skb</a>(sk, <a href="ident?i=skb">skb</a>);
<a name="L1357" href="source/net/ipv4/tcp_input.c#L1357">1357</a> 
<a name="L1358" href="source/net/ipv4/tcp_input.c#L1358">1358</a>         <a href="ident?i=NET_INC_STATS_BH">NET_INC_STATS_BH</a>(<a href="ident?i=sock_net">sock_net</a>(sk), LINUX_MIB_SACKMERGED);
<a name="L1359" href="source/net/ipv4/tcp_input.c#L1359">1359</a> 
<a name="L1360" href="source/net/ipv4/tcp_input.c#L1360">1360</a>         return <a href="ident?i=true">true</a>;
<a name="L1361" href="source/net/ipv4/tcp_input.c#L1361">1361</a> }
<a name="L1362" href="source/net/ipv4/tcp_input.c#L1362">1362</a> 
<a name="L1363" href="source/net/ipv4/tcp_input.c#L1363">1363</a> <b><i>/* I wish gso_size would have a bit more sane initialization than</i></b>
<a name="L1364" href="source/net/ipv4/tcp_input.c#L1364">1364</a> <b><i> * something-or-zero which complicates things</i></b>
<a name="L1365" href="source/net/ipv4/tcp_input.c#L1365">1365</a> <b><i> */</i></b>
<a name="L1366" href="source/net/ipv4/tcp_input.c#L1366">1366</a> static int <a href="ident?i=tcp_skb_seglen">tcp_skb_seglen</a>(const struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L1367" href="source/net/ipv4/tcp_input.c#L1367">1367</a> {
<a name="L1368" href="source/net/ipv4/tcp_input.c#L1368">1368</a>         return <a href="ident?i=tcp_skb_pcount">tcp_skb_pcount</a>(<a href="ident?i=skb">skb</a>) == 1 ? <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a> : <a href="ident?i=tcp_skb_mss">tcp_skb_mss</a>(<a href="ident?i=skb">skb</a>);
<a name="L1369" href="source/net/ipv4/tcp_input.c#L1369">1369</a> }
<a name="L1370" href="source/net/ipv4/tcp_input.c#L1370">1370</a> 
<a name="L1371" href="source/net/ipv4/tcp_input.c#L1371">1371</a> <b><i>/* Shifting pages past head area doesn't work */</i></b>
<a name="L1372" href="source/net/ipv4/tcp_input.c#L1372">1372</a> static int <a href="ident?i=skb_can_shift">skb_can_shift</a>(const struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L1373" href="source/net/ipv4/tcp_input.c#L1373">1373</a> {
<a name="L1374" href="source/net/ipv4/tcp_input.c#L1374">1374</a>         return !<a href="ident?i=skb_headlen">skb_headlen</a>(<a href="ident?i=skb">skb</a>) &amp;&amp; <a href="ident?i=skb_is_nonlinear">skb_is_nonlinear</a>(<a href="ident?i=skb">skb</a>);
<a name="L1375" href="source/net/ipv4/tcp_input.c#L1375">1375</a> }
<a name="L1376" href="source/net/ipv4/tcp_input.c#L1376">1376</a> 
<a name="L1377" href="source/net/ipv4/tcp_input.c#L1377">1377</a> <b><i>/* Try collapsing SACK blocks spanning across multiple skbs to a single</i></b>
<a name="L1378" href="source/net/ipv4/tcp_input.c#L1378">1378</a> <b><i> * skb.</i></b>
<a name="L1379" href="source/net/ipv4/tcp_input.c#L1379">1379</a> <b><i> */</i></b>
<a name="L1380" href="source/net/ipv4/tcp_input.c#L1380">1380</a> static struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=tcp_shift_skb_data">tcp_shift_skb_data</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
<a name="L1381" href="source/net/ipv4/tcp_input.c#L1381">1381</a>                                           struct <a href="ident?i=tcp_sacktag_state">tcp_sacktag_state</a> *<a href="ident?i=state">state</a>,
<a name="L1382" href="source/net/ipv4/tcp_input.c#L1382">1382</a>                                           <a href="ident?i=u32">u32</a> <a href="ident?i=start_seq">start_seq</a>, <a href="ident?i=u32">u32</a> end_seq,
<a name="L1383" href="source/net/ipv4/tcp_input.c#L1383">1383</a>                                           <a href="ident?i=bool">bool</a> dup_sack)
<a name="L1384" href="source/net/ipv4/tcp_input.c#L1384">1384</a> {
<a name="L1385" href="source/net/ipv4/tcp_input.c#L1385">1385</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L1386" href="source/net/ipv4/tcp_input.c#L1386">1386</a>         struct <a href="ident?i=sk_buff">sk_buff</a> *prev;
<a name="L1387" href="source/net/ipv4/tcp_input.c#L1387">1387</a>         int mss;
<a name="L1388" href="source/net/ipv4/tcp_input.c#L1388">1388</a>         int pcount = 0;
<a name="L1389" href="source/net/ipv4/tcp_input.c#L1389">1389</a>         int <a href="ident?i=len">len</a>;
<a name="L1390" href="source/net/ipv4/tcp_input.c#L1390">1390</a>         int in_sack;
<a name="L1391" href="source/net/ipv4/tcp_input.c#L1391">1391</a> 
<a name="L1392" href="source/net/ipv4/tcp_input.c#L1392">1392</a>         if (!<a href="ident?i=sk_can_gso">sk_can_gso</a>(sk))
<a name="L1393" href="source/net/ipv4/tcp_input.c#L1393">1393</a>                 goto fallback;
<a name="L1394" href="source/net/ipv4/tcp_input.c#L1394">1394</a> 
<a name="L1395" href="source/net/ipv4/tcp_input.c#L1395">1395</a>         <b><i>/* Normally R but no L won't result in plain S */</i></b>
<a name="L1396" href="source/net/ipv4/tcp_input.c#L1396">1396</a>         if (!dup_sack &amp;&amp;
<a name="L1397" href="source/net/ipv4/tcp_input.c#L1397">1397</a>             (<a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;sacked &amp; (<a href="ident?i=TCPCB_LOST">TCPCB_LOST</a>|<a href="ident?i=TCPCB_SACKED_RETRANS">TCPCB_SACKED_RETRANS</a>)) == <a href="ident?i=TCPCB_SACKED_RETRANS">TCPCB_SACKED_RETRANS</a>)
<a name="L1398" href="source/net/ipv4/tcp_input.c#L1398">1398</a>                 goto fallback;
<a name="L1399" href="source/net/ipv4/tcp_input.c#L1399">1399</a>         if (!<a href="ident?i=skb_can_shift">skb_can_shift</a>(<a href="ident?i=skb">skb</a>))
<a name="L1400" href="source/net/ipv4/tcp_input.c#L1400">1400</a>                 goto fallback;
<a name="L1401" href="source/net/ipv4/tcp_input.c#L1401">1401</a>         <b><i>/* This frame is about to be dropped (was ACKed). */</i></b>
<a name="L1402" href="source/net/ipv4/tcp_input.c#L1402">1402</a>         if (!<a href="ident?i=after">after</a>(<a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;end_seq, <a href="ident?i=tp">tp</a>-&gt;snd_una))
<a name="L1403" href="source/net/ipv4/tcp_input.c#L1403">1403</a>                 goto fallback;
<a name="L1404" href="source/net/ipv4/tcp_input.c#L1404">1404</a> 
<a name="L1405" href="source/net/ipv4/tcp_input.c#L1405">1405</a>         <b><i>/* Can only happen with delayed DSACK + discard craziness */</i></b>
<a name="L1406" href="source/net/ipv4/tcp_input.c#L1406">1406</a>         if (<a href="ident?i=unlikely">unlikely</a>(<a href="ident?i=skb">skb</a> == <a href="ident?i=tcp_write_queue_head">tcp_write_queue_head</a>(sk)))
<a name="L1407" href="source/net/ipv4/tcp_input.c#L1407">1407</a>                 goto fallback;
<a name="L1408" href="source/net/ipv4/tcp_input.c#L1408">1408</a>         prev = <a href="ident?i=tcp_write_queue_prev">tcp_write_queue_prev</a>(sk, <a href="ident?i=skb">skb</a>);
<a name="L1409" href="source/net/ipv4/tcp_input.c#L1409">1409</a> 
<a name="L1410" href="source/net/ipv4/tcp_input.c#L1410">1410</a>         if ((<a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(prev)-&gt;sacked &amp; <a href="ident?i=TCPCB_TAGBITS">TCPCB_TAGBITS</a>) != <a href="ident?i=TCPCB_SACKED_ACKED">TCPCB_SACKED_ACKED</a>)
<a name="L1411" href="source/net/ipv4/tcp_input.c#L1411">1411</a>                 goto fallback;
<a name="L1412" href="source/net/ipv4/tcp_input.c#L1412">1412</a> 
<a name="L1413" href="source/net/ipv4/tcp_input.c#L1413">1413</a>         in_sack = !<a href="ident?i=after">after</a>(<a href="ident?i=start_seq">start_seq</a>, <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=seq">seq</a>) &amp;&amp;
<a name="L1414" href="source/net/ipv4/tcp_input.c#L1414">1414</a>                   !<a href="ident?i=before">before</a>(end_seq, <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;end_seq);
<a name="L1415" href="source/net/ipv4/tcp_input.c#L1415">1415</a> 
<a name="L1416" href="source/net/ipv4/tcp_input.c#L1416">1416</a>         if (in_sack) {
<a name="L1417" href="source/net/ipv4/tcp_input.c#L1417">1417</a>                 <a href="ident?i=len">len</a> = <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a>;
<a name="L1418" href="source/net/ipv4/tcp_input.c#L1418">1418</a>                 pcount = <a href="ident?i=tcp_skb_pcount">tcp_skb_pcount</a>(<a href="ident?i=skb">skb</a>);
<a name="L1419" href="source/net/ipv4/tcp_input.c#L1419">1419</a>                 mss = <a href="ident?i=tcp_skb_seglen">tcp_skb_seglen</a>(<a href="ident?i=skb">skb</a>);
<a name="L1420" href="source/net/ipv4/tcp_input.c#L1420">1420</a> 
<a name="L1421" href="source/net/ipv4/tcp_input.c#L1421">1421</a>                 <b><i>/* TODO: Fix DSACKs to not fragment already SACKed and we can</i></b>
<a name="L1422" href="source/net/ipv4/tcp_input.c#L1422">1422</a> <b><i>                 * drop this restriction as unnecessary</i></b>
<a name="L1423" href="source/net/ipv4/tcp_input.c#L1423">1423</a> <b><i>                 */</i></b>
<a name="L1424" href="source/net/ipv4/tcp_input.c#L1424">1424</a>                 if (mss != <a href="ident?i=tcp_skb_seglen">tcp_skb_seglen</a>(prev))
<a name="L1425" href="source/net/ipv4/tcp_input.c#L1425">1425</a>                         goto fallback;
<a name="L1426" href="source/net/ipv4/tcp_input.c#L1426">1426</a>         } else {
<a name="L1427" href="source/net/ipv4/tcp_input.c#L1427">1427</a>                 if (!<a href="ident?i=after">after</a>(<a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;end_seq, <a href="ident?i=start_seq">start_seq</a>))
<a name="L1428" href="source/net/ipv4/tcp_input.c#L1428">1428</a>                         goto <a href="ident?i=noop">noop</a>;
<a name="L1429" href="source/net/ipv4/tcp_input.c#L1429">1429</a>                 <b><i>/* CHECKME: This is non-MSS split case only?, this will</i></b>
<a name="L1430" href="source/net/ipv4/tcp_input.c#L1430">1430</a> <b><i>                 * cause skipped skbs due to advancing loop btw, original</i></b>
<a name="L1431" href="source/net/ipv4/tcp_input.c#L1431">1431</a> <b><i>                 * has that feature too</i></b>
<a name="L1432" href="source/net/ipv4/tcp_input.c#L1432">1432</a> <b><i>                 */</i></b>
<a name="L1433" href="source/net/ipv4/tcp_input.c#L1433">1433</a>                 if (<a href="ident?i=tcp_skb_pcount">tcp_skb_pcount</a>(<a href="ident?i=skb">skb</a>) &lt;= 1)
<a name="L1434" href="source/net/ipv4/tcp_input.c#L1434">1434</a>                         goto <a href="ident?i=noop">noop</a>;
<a name="L1435" href="source/net/ipv4/tcp_input.c#L1435">1435</a> 
<a name="L1436" href="source/net/ipv4/tcp_input.c#L1436">1436</a>                 in_sack = !<a href="ident?i=after">after</a>(<a href="ident?i=start_seq">start_seq</a>, <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=seq">seq</a>);
<a name="L1437" href="source/net/ipv4/tcp_input.c#L1437">1437</a>                 if (!in_sack) {
<a name="L1438" href="source/net/ipv4/tcp_input.c#L1438">1438</a>                         <b><i>/* TODO: head merge to next could be attempted here</i></b>
<a name="L1439" href="source/net/ipv4/tcp_input.c#L1439">1439</a> <b><i>                         * if (!after(TCP_SKB_CB(skb)-&gt;end_seq, end_seq)),</i></b>
<a name="L1440" href="source/net/ipv4/tcp_input.c#L1440">1440</a> <b><i>                         * though it might not be worth of the additional hassle</i></b>
<a name="L1441" href="source/net/ipv4/tcp_input.c#L1441">1441</a> <b><i>                         *</i></b>
<a name="L1442" href="source/net/ipv4/tcp_input.c#L1442">1442</a> <b><i>                         * ...we can probably just fallback to what was done</i></b>
<a name="L1443" href="source/net/ipv4/tcp_input.c#L1443">1443</a> <b><i>                         * previously. We could try merging non-SACKed ones</i></b>
<a name="L1444" href="source/net/ipv4/tcp_input.c#L1444">1444</a> <b><i>                         * as well but it probably isn't going to buy off</i></b>
<a name="L1445" href="source/net/ipv4/tcp_input.c#L1445">1445</a> <b><i>                         * because later SACKs might again split them, and</i></b>
<a name="L1446" href="source/net/ipv4/tcp_input.c#L1446">1446</a> <b><i>                         * it would make skb timestamp tracking considerably</i></b>
<a name="L1447" href="source/net/ipv4/tcp_input.c#L1447">1447</a> <b><i>                         * harder problem.</i></b>
<a name="L1448" href="source/net/ipv4/tcp_input.c#L1448">1448</a> <b><i>                         */</i></b>
<a name="L1449" href="source/net/ipv4/tcp_input.c#L1449">1449</a>                         goto fallback;
<a name="L1450" href="source/net/ipv4/tcp_input.c#L1450">1450</a>                 }
<a name="L1451" href="source/net/ipv4/tcp_input.c#L1451">1451</a> 
<a name="L1452" href="source/net/ipv4/tcp_input.c#L1452">1452</a>                 <a href="ident?i=len">len</a> = end_seq - <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=seq">seq</a>;
<a name="L1453" href="source/net/ipv4/tcp_input.c#L1453">1453</a>                 <a href="ident?i=BUG_ON">BUG_ON</a>(<a href="ident?i=len">len</a> &lt; 0);
<a name="L1454" href="source/net/ipv4/tcp_input.c#L1454">1454</a>                 <a href="ident?i=BUG_ON">BUG_ON</a>(<a href="ident?i=len">len</a> &gt; <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a>);
<a name="L1455" href="source/net/ipv4/tcp_input.c#L1455">1455</a> 
<a name="L1456" href="source/net/ipv4/tcp_input.c#L1456">1456</a>                 <b><i>/* MSS boundaries should be honoured or else pcount will</i></b>
<a name="L1457" href="source/net/ipv4/tcp_input.c#L1457">1457</a> <b><i>                 * severely break even though it makes things bit trickier.</i></b>
<a name="L1458" href="source/net/ipv4/tcp_input.c#L1458">1458</a> <b><i>                 * Optimize common case to avoid most of the divides</i></b>
<a name="L1459" href="source/net/ipv4/tcp_input.c#L1459">1459</a> <b><i>                 */</i></b>
<a name="L1460" href="source/net/ipv4/tcp_input.c#L1460">1460</a>                 mss = <a href="ident?i=tcp_skb_mss">tcp_skb_mss</a>(<a href="ident?i=skb">skb</a>);
<a name="L1461" href="source/net/ipv4/tcp_input.c#L1461">1461</a> 
<a name="L1462" href="source/net/ipv4/tcp_input.c#L1462">1462</a>                 <b><i>/* TODO: Fix DSACKs to not fragment already SACKed and we can</i></b>
<a name="L1463" href="source/net/ipv4/tcp_input.c#L1463">1463</a> <b><i>                 * drop this restriction as unnecessary</i></b>
<a name="L1464" href="source/net/ipv4/tcp_input.c#L1464">1464</a> <b><i>                 */</i></b>
<a name="L1465" href="source/net/ipv4/tcp_input.c#L1465">1465</a>                 if (mss != <a href="ident?i=tcp_skb_seglen">tcp_skb_seglen</a>(prev))
<a name="L1466" href="source/net/ipv4/tcp_input.c#L1466">1466</a>                         goto fallback;
<a name="L1467" href="source/net/ipv4/tcp_input.c#L1467">1467</a> 
<a name="L1468" href="source/net/ipv4/tcp_input.c#L1468">1468</a>                 if (<a href="ident?i=len">len</a> == mss) {
<a name="L1469" href="source/net/ipv4/tcp_input.c#L1469">1469</a>                         pcount = 1;
<a name="L1470" href="source/net/ipv4/tcp_input.c#L1470">1470</a>                 } else if (<a href="ident?i=len">len</a> &lt; mss) {
<a name="L1471" href="source/net/ipv4/tcp_input.c#L1471">1471</a>                         goto <a href="ident?i=noop">noop</a>;
<a name="L1472" href="source/net/ipv4/tcp_input.c#L1472">1472</a>                 } else {
<a name="L1473" href="source/net/ipv4/tcp_input.c#L1473">1473</a>                         pcount = <a href="ident?i=len">len</a> / mss;
<a name="L1474" href="source/net/ipv4/tcp_input.c#L1474">1474</a>                         <a href="ident?i=len">len</a> = pcount * mss;
<a name="L1475" href="source/net/ipv4/tcp_input.c#L1475">1475</a>                 }
<a name="L1476" href="source/net/ipv4/tcp_input.c#L1476">1476</a>         }
<a name="L1477" href="source/net/ipv4/tcp_input.c#L1477">1477</a> 
<a name="L1478" href="source/net/ipv4/tcp_input.c#L1478">1478</a>         <b><i>/* tcp_sacktag_one() won't SACK-tag ranges below snd_una */</i></b>
<a name="L1479" href="source/net/ipv4/tcp_input.c#L1479">1479</a>         if (!<a href="ident?i=after">after</a>(<a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=seq">seq</a> + <a href="ident?i=len">len</a>, <a href="ident?i=tp">tp</a>-&gt;snd_una))
<a name="L1480" href="source/net/ipv4/tcp_input.c#L1480">1480</a>                 goto fallback;
<a name="L1481" href="source/net/ipv4/tcp_input.c#L1481">1481</a> 
<a name="L1482" href="source/net/ipv4/tcp_input.c#L1482">1482</a>         if (!<a href="ident?i=skb_shift">skb_shift</a>(prev, <a href="ident?i=skb">skb</a>, <a href="ident?i=len">len</a>))
<a name="L1483" href="source/net/ipv4/tcp_input.c#L1483">1483</a>                 goto fallback;
<a name="L1484" href="source/net/ipv4/tcp_input.c#L1484">1484</a>         if (!<a href="ident?i=tcp_shifted_skb">tcp_shifted_skb</a>(sk, <a href="ident?i=skb">skb</a>, <a href="ident?i=state">state</a>, pcount, <a href="ident?i=len">len</a>, mss, dup_sack))
<a name="L1485" href="source/net/ipv4/tcp_input.c#L1485">1485</a>                 goto <a href="ident?i=out">out</a>;
<a name="L1486" href="source/net/ipv4/tcp_input.c#L1486">1486</a> 
<a name="L1487" href="source/net/ipv4/tcp_input.c#L1487">1487</a>         <b><i>/* Hole filled allows collapsing with the next as well, this is very</i></b>
<a name="L1488" href="source/net/ipv4/tcp_input.c#L1488">1488</a> <b><i>         * useful when hole on every nth skb pattern happens</i></b>
<a name="L1489" href="source/net/ipv4/tcp_input.c#L1489">1489</a> <b><i>         */</i></b>
<a name="L1490" href="source/net/ipv4/tcp_input.c#L1490">1490</a>         if (prev == <a href="ident?i=tcp_write_queue_tail">tcp_write_queue_tail</a>(sk))
<a name="L1491" href="source/net/ipv4/tcp_input.c#L1491">1491</a>                 goto <a href="ident?i=out">out</a>;
<a name="L1492" href="source/net/ipv4/tcp_input.c#L1492">1492</a>         <a href="ident?i=skb">skb</a> = <a href="ident?i=tcp_write_queue_next">tcp_write_queue_next</a>(sk, prev);
<a name="L1493" href="source/net/ipv4/tcp_input.c#L1493">1493</a> 
<a name="L1494" href="source/net/ipv4/tcp_input.c#L1494">1494</a>         if (!<a href="ident?i=skb_can_shift">skb_can_shift</a>(<a href="ident?i=skb">skb</a>) ||
<a name="L1495" href="source/net/ipv4/tcp_input.c#L1495">1495</a>             (<a href="ident?i=skb">skb</a> == <a href="ident?i=tcp_send_head">tcp_send_head</a>(sk)) ||
<a name="L1496" href="source/net/ipv4/tcp_input.c#L1496">1496</a>             ((<a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;sacked &amp; <a href="ident?i=TCPCB_TAGBITS">TCPCB_TAGBITS</a>) != <a href="ident?i=TCPCB_SACKED_ACKED">TCPCB_SACKED_ACKED</a>) ||
<a name="L1497" href="source/net/ipv4/tcp_input.c#L1497">1497</a>             (mss != <a href="ident?i=tcp_skb_seglen">tcp_skb_seglen</a>(<a href="ident?i=skb">skb</a>)))
<a name="L1498" href="source/net/ipv4/tcp_input.c#L1498">1498</a>                 goto <a href="ident?i=out">out</a>;
<a name="L1499" href="source/net/ipv4/tcp_input.c#L1499">1499</a> 
<a name="L1500" href="source/net/ipv4/tcp_input.c#L1500">1500</a>         <a href="ident?i=len">len</a> = <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a>;
<a name="L1501" href="source/net/ipv4/tcp_input.c#L1501">1501</a>         if (<a href="ident?i=skb_shift">skb_shift</a>(prev, <a href="ident?i=skb">skb</a>, <a href="ident?i=len">len</a>)) {
<a name="L1502" href="source/net/ipv4/tcp_input.c#L1502">1502</a>                 pcount += <a href="ident?i=tcp_skb_pcount">tcp_skb_pcount</a>(<a href="ident?i=skb">skb</a>);
<a name="L1503" href="source/net/ipv4/tcp_input.c#L1503">1503</a>                 <a href="ident?i=tcp_shifted_skb">tcp_shifted_skb</a>(sk, <a href="ident?i=skb">skb</a>, <a href="ident?i=state">state</a>, <a href="ident?i=tcp_skb_pcount">tcp_skb_pcount</a>(<a href="ident?i=skb">skb</a>), <a href="ident?i=len">len</a>, mss, 0);
<a name="L1504" href="source/net/ipv4/tcp_input.c#L1504">1504</a>         }
<a name="L1505" href="source/net/ipv4/tcp_input.c#L1505">1505</a> 
<a name="L1506" href="source/net/ipv4/tcp_input.c#L1506">1506</a> <a href="ident?i=out">out</a>:
<a name="L1507" href="source/net/ipv4/tcp_input.c#L1507">1507</a>         <a href="ident?i=state">state</a>-&gt;fack_count += pcount;
<a name="L1508" href="source/net/ipv4/tcp_input.c#L1508">1508</a>         return prev;
<a name="L1509" href="source/net/ipv4/tcp_input.c#L1509">1509</a> 
<a name="L1510" href="source/net/ipv4/tcp_input.c#L1510">1510</a> <a href="ident?i=noop">noop</a>:
<a name="L1511" href="source/net/ipv4/tcp_input.c#L1511">1511</a>         return <a href="ident?i=skb">skb</a>;
<a name="L1512" href="source/net/ipv4/tcp_input.c#L1512">1512</a> 
<a name="L1513" href="source/net/ipv4/tcp_input.c#L1513">1513</a> fallback:
<a name="L1514" href="source/net/ipv4/tcp_input.c#L1514">1514</a>         <a href="ident?i=NET_INC_STATS_BH">NET_INC_STATS_BH</a>(<a href="ident?i=sock_net">sock_net</a>(sk), LINUX_MIB_SACKSHIFTFALLBACK);
<a name="L1515" href="source/net/ipv4/tcp_input.c#L1515">1515</a>         return <a href="ident?i=NULL">NULL</a>;
<a name="L1516" href="source/net/ipv4/tcp_input.c#L1516">1516</a> }
<a name="L1517" href="source/net/ipv4/tcp_input.c#L1517">1517</a> 
<a name="L1518" href="source/net/ipv4/tcp_input.c#L1518">1518</a> static struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=tcp_sacktag_walk">tcp_sacktag_walk</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, struct <a href="ident?i=sock">sock</a> *sk,
<a name="L1519" href="source/net/ipv4/tcp_input.c#L1519">1519</a>                                         struct <a href="ident?i=tcp_sack_block">tcp_sack_block</a> *next_dup,
<a name="L1520" href="source/net/ipv4/tcp_input.c#L1520">1520</a>                                         struct <a href="ident?i=tcp_sacktag_state">tcp_sacktag_state</a> *<a href="ident?i=state">state</a>,
<a name="L1521" href="source/net/ipv4/tcp_input.c#L1521">1521</a>                                         <a href="ident?i=u32">u32</a> <a href="ident?i=start_seq">start_seq</a>, <a href="ident?i=u32">u32</a> end_seq,
<a name="L1522" href="source/net/ipv4/tcp_input.c#L1522">1522</a>                                         <a href="ident?i=bool">bool</a> dup_sack_in)
<a name="L1523" href="source/net/ipv4/tcp_input.c#L1523">1523</a> {
<a name="L1524" href="source/net/ipv4/tcp_input.c#L1524">1524</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L1525" href="source/net/ipv4/tcp_input.c#L1525">1525</a>         struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=tmp">tmp</a>;
<a name="L1526" href="source/net/ipv4/tcp_input.c#L1526">1526</a> 
<a name="L1527" href="source/net/ipv4/tcp_input.c#L1527">1527</a>         <a href="ident?i=tcp_for_write_queue_from">tcp_for_write_queue_from</a>(<a href="ident?i=skb">skb</a>, sk) {
<a name="L1528" href="source/net/ipv4/tcp_input.c#L1528">1528</a>                 int in_sack = 0;
<a name="L1529" href="source/net/ipv4/tcp_input.c#L1529">1529</a>                 <a href="ident?i=bool">bool</a> dup_sack = dup_sack_in;
<a name="L1530" href="source/net/ipv4/tcp_input.c#L1530">1530</a> 
<a name="L1531" href="source/net/ipv4/tcp_input.c#L1531">1531</a>                 if (<a href="ident?i=skb">skb</a> == <a href="ident?i=tcp_send_head">tcp_send_head</a>(sk))
<a name="L1532" href="source/net/ipv4/tcp_input.c#L1532">1532</a>                         break;
<a name="L1533" href="source/net/ipv4/tcp_input.c#L1533">1533</a> 
<a name="L1534" href="source/net/ipv4/tcp_input.c#L1534">1534</a>                 <b><i>/* queue is in-order =&gt; we can short-circuit the walk early */</i></b>
<a name="L1535" href="source/net/ipv4/tcp_input.c#L1535">1535</a>                 if (!<a href="ident?i=before">before</a>(<a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=seq">seq</a>, end_seq))
<a name="L1536" href="source/net/ipv4/tcp_input.c#L1536">1536</a>                         break;
<a name="L1537" href="source/net/ipv4/tcp_input.c#L1537">1537</a> 
<a name="L1538" href="source/net/ipv4/tcp_input.c#L1538">1538</a>                 if (next_dup  &amp;&amp;
<a name="L1539" href="source/net/ipv4/tcp_input.c#L1539">1539</a>                     <a href="ident?i=before">before</a>(<a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=seq">seq</a>, next_dup-&gt;end_seq)) {
<a name="L1540" href="source/net/ipv4/tcp_input.c#L1540">1540</a>                         in_sack = <a href="ident?i=tcp_match_skb_to_sack">tcp_match_skb_to_sack</a>(sk, <a href="ident?i=skb">skb</a>,
<a name="L1541" href="source/net/ipv4/tcp_input.c#L1541">1541</a>                                                         next_dup-&gt;<a href="ident?i=start_seq">start_seq</a>,
<a name="L1542" href="source/net/ipv4/tcp_input.c#L1542">1542</a>                                                         next_dup-&gt;end_seq);
<a name="L1543" href="source/net/ipv4/tcp_input.c#L1543">1543</a>                         if (in_sack &gt; 0)
<a name="L1544" href="source/net/ipv4/tcp_input.c#L1544">1544</a>                                 dup_sack = <a href="ident?i=true">true</a>;
<a name="L1545" href="source/net/ipv4/tcp_input.c#L1545">1545</a>                 }
<a name="L1546" href="source/net/ipv4/tcp_input.c#L1546">1546</a> 
<a name="L1547" href="source/net/ipv4/tcp_input.c#L1547">1547</a>                 <b><i>/* skb reference here is a bit tricky to get right, since</i></b>
<a name="L1548" href="source/net/ipv4/tcp_input.c#L1548">1548</a> <b><i>                 * shifting can eat and free both this skb and the next,</i></b>
<a name="L1549" href="source/net/ipv4/tcp_input.c#L1549">1549</a> <b><i>                 * so not even _safe variant of the loop is enough.</i></b>
<a name="L1550" href="source/net/ipv4/tcp_input.c#L1550">1550</a> <b><i>                 */</i></b>
<a name="L1551" href="source/net/ipv4/tcp_input.c#L1551">1551</a>                 if (in_sack &lt;= 0) {
<a name="L1552" href="source/net/ipv4/tcp_input.c#L1552">1552</a>                         <a href="ident?i=tmp">tmp</a> = <a href="ident?i=tcp_shift_skb_data">tcp_shift_skb_data</a>(sk, <a href="ident?i=skb">skb</a>, <a href="ident?i=state">state</a>,
<a name="L1553" href="source/net/ipv4/tcp_input.c#L1553">1553</a>                                                  <a href="ident?i=start_seq">start_seq</a>, end_seq, dup_sack);
<a name="L1554" href="source/net/ipv4/tcp_input.c#L1554">1554</a>                         if (<a href="ident?i=tmp">tmp</a>) {
<a name="L1555" href="source/net/ipv4/tcp_input.c#L1555">1555</a>                                 if (<a href="ident?i=tmp">tmp</a> != <a href="ident?i=skb">skb</a>) {
<a name="L1556" href="source/net/ipv4/tcp_input.c#L1556">1556</a>                                         <a href="ident?i=skb">skb</a> = <a href="ident?i=tmp">tmp</a>;
<a name="L1557" href="source/net/ipv4/tcp_input.c#L1557">1557</a>                                         continue;
<a name="L1558" href="source/net/ipv4/tcp_input.c#L1558">1558</a>                                 }
<a name="L1559" href="source/net/ipv4/tcp_input.c#L1559">1559</a> 
<a name="L1560" href="source/net/ipv4/tcp_input.c#L1560">1560</a>                                 in_sack = 0;
<a name="L1561" href="source/net/ipv4/tcp_input.c#L1561">1561</a>                         } else {
<a name="L1562" href="source/net/ipv4/tcp_input.c#L1562">1562</a>                                 in_sack = <a href="ident?i=tcp_match_skb_to_sack">tcp_match_skb_to_sack</a>(sk, <a href="ident?i=skb">skb</a>,
<a name="L1563" href="source/net/ipv4/tcp_input.c#L1563">1563</a>                                                                 <a href="ident?i=start_seq">start_seq</a>,
<a name="L1564" href="source/net/ipv4/tcp_input.c#L1564">1564</a>                                                                 end_seq);
<a name="L1565" href="source/net/ipv4/tcp_input.c#L1565">1565</a>                         }
<a name="L1566" href="source/net/ipv4/tcp_input.c#L1566">1566</a>                 }
<a name="L1567" href="source/net/ipv4/tcp_input.c#L1567">1567</a> 
<a name="L1568" href="source/net/ipv4/tcp_input.c#L1568">1568</a>                 if (<a href="ident?i=unlikely">unlikely</a>(in_sack &lt; 0))
<a name="L1569" href="source/net/ipv4/tcp_input.c#L1569">1569</a>                         break;
<a name="L1570" href="source/net/ipv4/tcp_input.c#L1570">1570</a> 
<a name="L1571" href="source/net/ipv4/tcp_input.c#L1571">1571</a>                 if (in_sack) {
<a name="L1572" href="source/net/ipv4/tcp_input.c#L1572">1572</a>                         <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;sacked =
<a name="L1573" href="source/net/ipv4/tcp_input.c#L1573">1573</a>                                 <a href="ident?i=tcp_sacktag_one">tcp_sacktag_one</a>(sk,
<a name="L1574" href="source/net/ipv4/tcp_input.c#L1574">1574</a>                                                 <a href="ident?i=state">state</a>,
<a name="L1575" href="source/net/ipv4/tcp_input.c#L1575">1575</a>                                                 <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;sacked,
<a name="L1576" href="source/net/ipv4/tcp_input.c#L1576">1576</a>                                                 <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=seq">seq</a>,
<a name="L1577" href="source/net/ipv4/tcp_input.c#L1577">1577</a>                                                 <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;end_seq,
<a name="L1578" href="source/net/ipv4/tcp_input.c#L1578">1578</a>                                                 dup_sack,
<a name="L1579" href="source/net/ipv4/tcp_input.c#L1579">1579</a>                                                 <a href="ident?i=tcp_skb_pcount">tcp_skb_pcount</a>(<a href="ident?i=skb">skb</a>),
<a name="L1580" href="source/net/ipv4/tcp_input.c#L1580">1580</a>                                                 &amp;<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=skb_mstamp">skb_mstamp</a>);
<a name="L1581" href="source/net/ipv4/tcp_input.c#L1581">1581</a> 
<a name="L1582" href="source/net/ipv4/tcp_input.c#L1582">1582</a>                         if (!<a href="ident?i=before">before</a>(<a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=seq">seq</a>,
<a name="L1583" href="source/net/ipv4/tcp_input.c#L1583">1583</a>                                     <a href="ident?i=tcp_highest_sack_seq">tcp_highest_sack_seq</a>(<a href="ident?i=tp">tp</a>)))
<a name="L1584" href="source/net/ipv4/tcp_input.c#L1584">1584</a>                                 <a href="ident?i=tcp_advance_highest_sack">tcp_advance_highest_sack</a>(sk, <a href="ident?i=skb">skb</a>);
<a name="L1585" href="source/net/ipv4/tcp_input.c#L1585">1585</a>                 }
<a name="L1586" href="source/net/ipv4/tcp_input.c#L1586">1586</a> 
<a name="L1587" href="source/net/ipv4/tcp_input.c#L1587">1587</a>                 <a href="ident?i=state">state</a>-&gt;fack_count += <a href="ident?i=tcp_skb_pcount">tcp_skb_pcount</a>(<a href="ident?i=skb">skb</a>);
<a name="L1588" href="source/net/ipv4/tcp_input.c#L1588">1588</a>         }
<a name="L1589" href="source/net/ipv4/tcp_input.c#L1589">1589</a>         return <a href="ident?i=skb">skb</a>;
<a name="L1590" href="source/net/ipv4/tcp_input.c#L1590">1590</a> }
<a name="L1591" href="source/net/ipv4/tcp_input.c#L1591">1591</a> 
<a name="L1592" href="source/net/ipv4/tcp_input.c#L1592">1592</a> <b><i>/* Avoid all extra work that is being done by sacktag while walking in</i></b>
<a name="L1593" href="source/net/ipv4/tcp_input.c#L1593">1593</a> <b><i> * a normal way</i></b>
<a name="L1594" href="source/net/ipv4/tcp_input.c#L1594">1594</a> <b><i> */</i></b>
<a name="L1595" href="source/net/ipv4/tcp_input.c#L1595">1595</a> static struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=tcp_sacktag_skip">tcp_sacktag_skip</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, struct <a href="ident?i=sock">sock</a> *sk,
<a name="L1596" href="source/net/ipv4/tcp_input.c#L1596">1596</a>                                         struct <a href="ident?i=tcp_sacktag_state">tcp_sacktag_state</a> *<a href="ident?i=state">state</a>,
<a name="L1597" href="source/net/ipv4/tcp_input.c#L1597">1597</a>                                         <a href="ident?i=u32">u32</a> skip_to_seq)
<a name="L1598" href="source/net/ipv4/tcp_input.c#L1598">1598</a> {
<a name="L1599" href="source/net/ipv4/tcp_input.c#L1599">1599</a>         <a href="ident?i=tcp_for_write_queue_from">tcp_for_write_queue_from</a>(<a href="ident?i=skb">skb</a>, sk) {
<a name="L1600" href="source/net/ipv4/tcp_input.c#L1600">1600</a>                 if (<a href="ident?i=skb">skb</a> == <a href="ident?i=tcp_send_head">tcp_send_head</a>(sk))
<a name="L1601" href="source/net/ipv4/tcp_input.c#L1601">1601</a>                         break;
<a name="L1602" href="source/net/ipv4/tcp_input.c#L1602">1602</a> 
<a name="L1603" href="source/net/ipv4/tcp_input.c#L1603">1603</a>                 if (<a href="ident?i=after">after</a>(<a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;end_seq, skip_to_seq))
<a name="L1604" href="source/net/ipv4/tcp_input.c#L1604">1604</a>                         break;
<a name="L1605" href="source/net/ipv4/tcp_input.c#L1605">1605</a> 
<a name="L1606" href="source/net/ipv4/tcp_input.c#L1606">1606</a>                 <a href="ident?i=state">state</a>-&gt;fack_count += <a href="ident?i=tcp_skb_pcount">tcp_skb_pcount</a>(<a href="ident?i=skb">skb</a>);
<a name="L1607" href="source/net/ipv4/tcp_input.c#L1607">1607</a>         }
<a name="L1608" href="source/net/ipv4/tcp_input.c#L1608">1608</a>         return <a href="ident?i=skb">skb</a>;
<a name="L1609" href="source/net/ipv4/tcp_input.c#L1609">1609</a> }
<a name="L1610" href="source/net/ipv4/tcp_input.c#L1610">1610</a> 
<a name="L1611" href="source/net/ipv4/tcp_input.c#L1611">1611</a> static struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=tcp_maybe_skipping_dsack">tcp_maybe_skipping_dsack</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
<a name="L1612" href="source/net/ipv4/tcp_input.c#L1612">1612</a>                                                 struct <a href="ident?i=sock">sock</a> *sk,
<a name="L1613" href="source/net/ipv4/tcp_input.c#L1613">1613</a>                                                 struct <a href="ident?i=tcp_sack_block">tcp_sack_block</a> *next_dup,
<a name="L1614" href="source/net/ipv4/tcp_input.c#L1614">1614</a>                                                 struct <a href="ident?i=tcp_sacktag_state">tcp_sacktag_state</a> *<a href="ident?i=state">state</a>,
<a name="L1615" href="source/net/ipv4/tcp_input.c#L1615">1615</a>                                                 <a href="ident?i=u32">u32</a> skip_to_seq)
<a name="L1616" href="source/net/ipv4/tcp_input.c#L1616">1616</a> {
<a name="L1617" href="source/net/ipv4/tcp_input.c#L1617">1617</a>         if (!next_dup)
<a name="L1618" href="source/net/ipv4/tcp_input.c#L1618">1618</a>                 return <a href="ident?i=skb">skb</a>;
<a name="L1619" href="source/net/ipv4/tcp_input.c#L1619">1619</a> 
<a name="L1620" href="source/net/ipv4/tcp_input.c#L1620">1620</a>         if (<a href="ident?i=before">before</a>(next_dup-&gt;<a href="ident?i=start_seq">start_seq</a>, skip_to_seq)) {
<a name="L1621" href="source/net/ipv4/tcp_input.c#L1621">1621</a>                 <a href="ident?i=skb">skb</a> = <a href="ident?i=tcp_sacktag_skip">tcp_sacktag_skip</a>(<a href="ident?i=skb">skb</a>, sk, <a href="ident?i=state">state</a>, next_dup-&gt;<a href="ident?i=start_seq">start_seq</a>);
<a name="L1622" href="source/net/ipv4/tcp_input.c#L1622">1622</a>                 <a href="ident?i=skb">skb</a> = <a href="ident?i=tcp_sacktag_walk">tcp_sacktag_walk</a>(<a href="ident?i=skb">skb</a>, sk, <a href="ident?i=NULL">NULL</a>, <a href="ident?i=state">state</a>,
<a name="L1623" href="source/net/ipv4/tcp_input.c#L1623">1623</a>                                        next_dup-&gt;<a href="ident?i=start_seq">start_seq</a>, next_dup-&gt;end_seq,
<a name="L1624" href="source/net/ipv4/tcp_input.c#L1624">1624</a>                                        1);
<a name="L1625" href="source/net/ipv4/tcp_input.c#L1625">1625</a>         }
<a name="L1626" href="source/net/ipv4/tcp_input.c#L1626">1626</a> 
<a name="L1627" href="source/net/ipv4/tcp_input.c#L1627">1627</a>         return <a href="ident?i=skb">skb</a>;
<a name="L1628" href="source/net/ipv4/tcp_input.c#L1628">1628</a> }
<a name="L1629" href="source/net/ipv4/tcp_input.c#L1629">1629</a> 
<a name="L1630" href="source/net/ipv4/tcp_input.c#L1630">1630</a> static int <a href="ident?i=tcp_sack_cache_ok">tcp_sack_cache_ok</a>(const struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a>, const struct <a href="ident?i=tcp_sack_block">tcp_sack_block</a> *<a href="ident?i=cache">cache</a>)
<a name="L1631" href="source/net/ipv4/tcp_input.c#L1631">1631</a> {
<a name="L1632" href="source/net/ipv4/tcp_input.c#L1632">1632</a>         return <a href="ident?i=cache">cache</a> &lt; <a href="ident?i=tp">tp</a>-&gt;recv_sack_cache + <a href="ident?i=ARRAY_SIZE">ARRAY_SIZE</a>(<a href="ident?i=tp">tp</a>-&gt;recv_sack_cache);
<a name="L1633" href="source/net/ipv4/tcp_input.c#L1633">1633</a> }
<a name="L1634" href="source/net/ipv4/tcp_input.c#L1634">1634</a> 
<a name="L1635" href="source/net/ipv4/tcp_input.c#L1635">1635</a> static int
<a name="L1636" href="source/net/ipv4/tcp_input.c#L1636">1636</a> <a href="ident?i=tcp_sacktag_write_queue">tcp_sacktag_write_queue</a>(struct <a href="ident?i=sock">sock</a> *sk, const struct <a href="ident?i=sk_buff">sk_buff</a> *ack_skb,
<a name="L1637" href="source/net/ipv4/tcp_input.c#L1637">1637</a>                         <a href="ident?i=u32">u32</a> prior_snd_una, long *sack_rtt_us)
<a name="L1638" href="source/net/ipv4/tcp_input.c#L1638">1638</a> {
<a name="L1639" href="source/net/ipv4/tcp_input.c#L1639">1639</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L1640" href="source/net/ipv4/tcp_input.c#L1640">1640</a>         const unsigned char *<a href="ident?i=ptr">ptr</a> = (<a href="ident?i=skb_transport_header">skb_transport_header</a>(ack_skb) +
<a name="L1641" href="source/net/ipv4/tcp_input.c#L1641">1641</a>                                     <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(ack_skb)-&gt;sacked);
<a name="L1642" href="source/net/ipv4/tcp_input.c#L1642">1642</a>         struct <a href="ident?i=tcp_sack_block_wire">tcp_sack_block_wire</a> *sp_wire = (struct <a href="ident?i=tcp_sack_block_wire">tcp_sack_block_wire</a> *)(<a href="ident?i=ptr">ptr</a>+2);
<a name="L1643" href="source/net/ipv4/tcp_input.c#L1643">1643</a>         struct <a href="ident?i=tcp_sack_block">tcp_sack_block</a> <a href="ident?i=sp">sp</a>[<a href="ident?i=TCP_NUM_SACKS">TCP_NUM_SACKS</a>];
<a name="L1644" href="source/net/ipv4/tcp_input.c#L1644">1644</a>         struct <a href="ident?i=tcp_sack_block">tcp_sack_block</a> *<a href="ident?i=cache">cache</a>;
<a name="L1645" href="source/net/ipv4/tcp_input.c#L1645">1645</a>         struct <a href="ident?i=tcp_sacktag_state">tcp_sacktag_state</a> <a href="ident?i=state">state</a>;
<a name="L1646" href="source/net/ipv4/tcp_input.c#L1646">1646</a>         struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>;
<a name="L1647" href="source/net/ipv4/tcp_input.c#L1647">1647</a>         int num_sacks = <a href="ident?i=min">min</a>(<a href="ident?i=TCP_NUM_SACKS">TCP_NUM_SACKS</a>, (<a href="ident?i=ptr">ptr</a>[1] - <a href="ident?i=TCPOLEN_SACK_BASE">TCPOLEN_SACK_BASE</a>) &gt;&gt; 3);
<a name="L1648" href="source/net/ipv4/tcp_input.c#L1648">1648</a>         int used_sacks;
<a name="L1649" href="source/net/ipv4/tcp_input.c#L1649">1649</a>         <a href="ident?i=bool">bool</a> found_dup_sack = <a href="ident?i=false">false</a>;
<a name="L1650" href="source/net/ipv4/tcp_input.c#L1650">1650</a>         int <a href="ident?i=i">i</a>, j;
<a name="L1651" href="source/net/ipv4/tcp_input.c#L1651">1651</a>         int first_sack_index;
<a name="L1652" href="source/net/ipv4/tcp_input.c#L1652">1652</a> 
<a name="L1653" href="source/net/ipv4/tcp_input.c#L1653">1653</a>         <a href="ident?i=state">state</a>.<a href="ident?i=flag">flag</a> = 0;
<a name="L1654" href="source/net/ipv4/tcp_input.c#L1654">1654</a>         <a href="ident?i=state">state</a>.reord = <a href="ident?i=tp">tp</a>-&gt;packets_out;
<a name="L1655" href="source/net/ipv4/tcp_input.c#L1655">1655</a>         <a href="ident?i=state">state</a>.rtt_us = -1L;
<a name="L1656" href="source/net/ipv4/tcp_input.c#L1656">1656</a> 
<a name="L1657" href="source/net/ipv4/tcp_input.c#L1657">1657</a>         if (!<a href="ident?i=tp">tp</a>-&gt;sacked_out) {
<a name="L1658" href="source/net/ipv4/tcp_input.c#L1658">1658</a>                 if (<a href="ident?i=WARN_ON">WARN_ON</a>(<a href="ident?i=tp">tp</a>-&gt;fackets_out))
<a name="L1659" href="source/net/ipv4/tcp_input.c#L1659">1659</a>                         <a href="ident?i=tp">tp</a>-&gt;fackets_out = 0;
<a name="L1660" href="source/net/ipv4/tcp_input.c#L1660">1660</a>                 <a href="ident?i=tcp_highest_sack_reset">tcp_highest_sack_reset</a>(sk);
<a name="L1661" href="source/net/ipv4/tcp_input.c#L1661">1661</a>         }
<a name="L1662" href="source/net/ipv4/tcp_input.c#L1662">1662</a> 
<a name="L1663" href="source/net/ipv4/tcp_input.c#L1663">1663</a>         found_dup_sack = <a href="ident?i=tcp_check_dsack">tcp_check_dsack</a>(sk, ack_skb, sp_wire,
<a name="L1664" href="source/net/ipv4/tcp_input.c#L1664">1664</a>                                          num_sacks, prior_snd_una);
<a name="L1665" href="source/net/ipv4/tcp_input.c#L1665">1665</a>         if (found_dup_sack)
<a name="L1666" href="source/net/ipv4/tcp_input.c#L1666">1666</a>                 <a href="ident?i=state">state</a>.<a href="ident?i=flag">flag</a> |= <a href="ident?i=FLAG_DSACKING_ACK">FLAG_DSACKING_ACK</a>;
<a name="L1667" href="source/net/ipv4/tcp_input.c#L1667">1667</a> 
<a name="L1668" href="source/net/ipv4/tcp_input.c#L1668">1668</a>         <b><i>/* Eliminate too old ACKs, but take into</i></b>
<a name="L1669" href="source/net/ipv4/tcp_input.c#L1669">1669</a> <b><i>         * account more or less fresh ones, they can</i></b>
<a name="L1670" href="source/net/ipv4/tcp_input.c#L1670">1670</a> <b><i>         * contain valid SACK info.</i></b>
<a name="L1671" href="source/net/ipv4/tcp_input.c#L1671">1671</a> <b><i>         */</i></b>
<a name="L1672" href="source/net/ipv4/tcp_input.c#L1672">1672</a>         if (<a href="ident?i=before">before</a>(<a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(ack_skb)-&gt;ack_seq, prior_snd_una - <a href="ident?i=tp">tp</a>-&gt;max_window))
<a name="L1673" href="source/net/ipv4/tcp_input.c#L1673">1673</a>                 return 0;
<a name="L1674" href="source/net/ipv4/tcp_input.c#L1674">1674</a> 
<a name="L1675" href="source/net/ipv4/tcp_input.c#L1675">1675</a>         if (!<a href="ident?i=tp">tp</a>-&gt;packets_out)
<a name="L1676" href="source/net/ipv4/tcp_input.c#L1676">1676</a>                 goto <a href="ident?i=out">out</a>;
<a name="L1677" href="source/net/ipv4/tcp_input.c#L1677">1677</a> 
<a name="L1678" href="source/net/ipv4/tcp_input.c#L1678">1678</a>         used_sacks = 0;
<a name="L1679" href="source/net/ipv4/tcp_input.c#L1679">1679</a>         first_sack_index = 0;
<a name="L1680" href="source/net/ipv4/tcp_input.c#L1680">1680</a>         for (<a href="ident?i=i">i</a> = 0; <a href="ident?i=i">i</a> &lt; num_sacks; <a href="ident?i=i">i</a>++) {
<a name="L1681" href="source/net/ipv4/tcp_input.c#L1681">1681</a>                 <a href="ident?i=bool">bool</a> dup_sack = !<a href="ident?i=i">i</a> &amp;&amp; found_dup_sack;
<a name="L1682" href="source/net/ipv4/tcp_input.c#L1682">1682</a> 
<a name="L1683" href="source/net/ipv4/tcp_input.c#L1683">1683</a>                 <a href="ident?i=sp">sp</a>[used_sacks].<a href="ident?i=start_seq">start_seq</a> = <a href="ident?i=get_unaligned_be32">get_unaligned_be32</a>(&amp;sp_wire[<a href="ident?i=i">i</a>].<a href="ident?i=start_seq">start_seq</a>);
<a name="L1684" href="source/net/ipv4/tcp_input.c#L1684">1684</a>                 <a href="ident?i=sp">sp</a>[used_sacks].end_seq = <a href="ident?i=get_unaligned_be32">get_unaligned_be32</a>(&amp;sp_wire[<a href="ident?i=i">i</a>].end_seq);
<a name="L1685" href="source/net/ipv4/tcp_input.c#L1685">1685</a> 
<a name="L1686" href="source/net/ipv4/tcp_input.c#L1686">1686</a>                 if (!<a href="ident?i=tcp_is_sackblock_valid">tcp_is_sackblock_valid</a>(<a href="ident?i=tp">tp</a>, dup_sack,
<a name="L1687" href="source/net/ipv4/tcp_input.c#L1687">1687</a>                                             <a href="ident?i=sp">sp</a>[used_sacks].<a href="ident?i=start_seq">start_seq</a>,
<a name="L1688" href="source/net/ipv4/tcp_input.c#L1688">1688</a>                                             <a href="ident?i=sp">sp</a>[used_sacks].end_seq)) {
<a name="L1689" href="source/net/ipv4/tcp_input.c#L1689">1689</a>                         int mib_idx;
<a name="L1690" href="source/net/ipv4/tcp_input.c#L1690">1690</a> 
<a name="L1691" href="source/net/ipv4/tcp_input.c#L1691">1691</a>                         if (dup_sack) {
<a name="L1692" href="source/net/ipv4/tcp_input.c#L1692">1692</a>                                 if (!<a href="ident?i=tp">tp</a>-&gt;undo_marker)
<a name="L1693" href="source/net/ipv4/tcp_input.c#L1693">1693</a>                                         mib_idx = LINUX_MIB_TCPDSACKIGNOREDNOUNDO;
<a name="L1694" href="source/net/ipv4/tcp_input.c#L1694">1694</a>                                 else
<a name="L1695" href="source/net/ipv4/tcp_input.c#L1695">1695</a>                                         mib_idx = LINUX_MIB_TCPDSACKIGNOREDOLD;
<a name="L1696" href="source/net/ipv4/tcp_input.c#L1696">1696</a>                         } else {
<a name="L1697" href="source/net/ipv4/tcp_input.c#L1697">1697</a>                                 <b><i>/* Don't count olds caused by ACK reordering */</i></b>
<a name="L1698" href="source/net/ipv4/tcp_input.c#L1698">1698</a>                                 if ((<a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(ack_skb)-&gt;ack_seq != <a href="ident?i=tp">tp</a>-&gt;snd_una) &amp;&amp;
<a name="L1699" href="source/net/ipv4/tcp_input.c#L1699">1699</a>                                     !<a href="ident?i=after">after</a>(<a href="ident?i=sp">sp</a>[used_sacks].end_seq, <a href="ident?i=tp">tp</a>-&gt;snd_una))
<a name="L1700" href="source/net/ipv4/tcp_input.c#L1700">1700</a>                                         continue;
<a name="L1701" href="source/net/ipv4/tcp_input.c#L1701">1701</a>                                 mib_idx = LINUX_MIB_TCPSACKDISCARD;
<a name="L1702" href="source/net/ipv4/tcp_input.c#L1702">1702</a>                         }
<a name="L1703" href="source/net/ipv4/tcp_input.c#L1703">1703</a> 
<a name="L1704" href="source/net/ipv4/tcp_input.c#L1704">1704</a>                         <a href="ident?i=NET_INC_STATS_BH">NET_INC_STATS_BH</a>(<a href="ident?i=sock_net">sock_net</a>(sk), mib_idx);
<a name="L1705" href="source/net/ipv4/tcp_input.c#L1705">1705</a>                         if (<a href="ident?i=i">i</a> == 0)
<a name="L1706" href="source/net/ipv4/tcp_input.c#L1706">1706</a>                                 first_sack_index = -1;
<a name="L1707" href="source/net/ipv4/tcp_input.c#L1707">1707</a>                         continue;
<a name="L1708" href="source/net/ipv4/tcp_input.c#L1708">1708</a>                 }
<a name="L1709" href="source/net/ipv4/tcp_input.c#L1709">1709</a> 
<a name="L1710" href="source/net/ipv4/tcp_input.c#L1710">1710</a>                 <b><i>/* Ignore very old stuff early */</i></b>
<a name="L1711" href="source/net/ipv4/tcp_input.c#L1711">1711</a>                 if (!<a href="ident?i=after">after</a>(<a href="ident?i=sp">sp</a>[used_sacks].end_seq, prior_snd_una))
<a name="L1712" href="source/net/ipv4/tcp_input.c#L1712">1712</a>                         continue;
<a name="L1713" href="source/net/ipv4/tcp_input.c#L1713">1713</a> 
<a name="L1714" href="source/net/ipv4/tcp_input.c#L1714">1714</a>                 used_sacks++;
<a name="L1715" href="source/net/ipv4/tcp_input.c#L1715">1715</a>         }
<a name="L1716" href="source/net/ipv4/tcp_input.c#L1716">1716</a> 
<a name="L1717" href="source/net/ipv4/tcp_input.c#L1717">1717</a>         <b><i>/* order SACK blocks to allow in order walk of the retrans queue */</i></b>
<a name="L1718" href="source/net/ipv4/tcp_input.c#L1718">1718</a>         for (<a href="ident?i=i">i</a> = used_sacks - 1; <a href="ident?i=i">i</a> &gt; 0; <a href="ident?i=i">i</a>--) {
<a name="L1719" href="source/net/ipv4/tcp_input.c#L1719">1719</a>                 for (j = 0; j &lt; <a href="ident?i=i">i</a>; j++) {
<a name="L1720" href="source/net/ipv4/tcp_input.c#L1720">1720</a>                         if (<a href="ident?i=after">after</a>(<a href="ident?i=sp">sp</a>[j].<a href="ident?i=start_seq">start_seq</a>, <a href="ident?i=sp">sp</a>[j + 1].<a href="ident?i=start_seq">start_seq</a>)) {
<a name="L1721" href="source/net/ipv4/tcp_input.c#L1721">1721</a>                                 <a href="ident?i=swap">swap</a>(<a href="ident?i=sp">sp</a>[j], <a href="ident?i=sp">sp</a>[j + 1]);
<a name="L1722" href="source/net/ipv4/tcp_input.c#L1722">1722</a> 
<a name="L1723" href="source/net/ipv4/tcp_input.c#L1723">1723</a>                                 <b><i>/* Track where the first SACK block goes to */</i></b>
<a name="L1724" href="source/net/ipv4/tcp_input.c#L1724">1724</a>                                 if (j == first_sack_index)
<a name="L1725" href="source/net/ipv4/tcp_input.c#L1725">1725</a>                                         first_sack_index = j + 1;
<a name="L1726" href="source/net/ipv4/tcp_input.c#L1726">1726</a>                         }
<a name="L1727" href="source/net/ipv4/tcp_input.c#L1727">1727</a>                 }
<a name="L1728" href="source/net/ipv4/tcp_input.c#L1728">1728</a>         }
<a name="L1729" href="source/net/ipv4/tcp_input.c#L1729">1729</a> 
<a name="L1730" href="source/net/ipv4/tcp_input.c#L1730">1730</a>         <a href="ident?i=skb">skb</a> = <a href="ident?i=tcp_write_queue_head">tcp_write_queue_head</a>(sk);
<a name="L1731" href="source/net/ipv4/tcp_input.c#L1731">1731</a>         <a href="ident?i=state">state</a>.fack_count = 0;
<a name="L1732" href="source/net/ipv4/tcp_input.c#L1732">1732</a>         <a href="ident?i=i">i</a> = 0;
<a name="L1733" href="source/net/ipv4/tcp_input.c#L1733">1733</a> 
<a name="L1734" href="source/net/ipv4/tcp_input.c#L1734">1734</a>         if (!<a href="ident?i=tp">tp</a>-&gt;sacked_out) {
<a name="L1735" href="source/net/ipv4/tcp_input.c#L1735">1735</a>                 <b><i>/* It's already past, so skip checking against it */</i></b>
<a name="L1736" href="source/net/ipv4/tcp_input.c#L1736">1736</a>                 <a href="ident?i=cache">cache</a> = <a href="ident?i=tp">tp</a>-&gt;recv_sack_cache + <a href="ident?i=ARRAY_SIZE">ARRAY_SIZE</a>(<a href="ident?i=tp">tp</a>-&gt;recv_sack_cache);
<a name="L1737" href="source/net/ipv4/tcp_input.c#L1737">1737</a>         } else {
<a name="L1738" href="source/net/ipv4/tcp_input.c#L1738">1738</a>                 <a href="ident?i=cache">cache</a> = <a href="ident?i=tp">tp</a>-&gt;recv_sack_cache;
<a name="L1739" href="source/net/ipv4/tcp_input.c#L1739">1739</a>                 <b><i>/* Skip empty blocks in at head of the cache */</i></b>
<a name="L1740" href="source/net/ipv4/tcp_input.c#L1740">1740</a>                 while (<a href="ident?i=tcp_sack_cache_ok">tcp_sack_cache_ok</a>(<a href="ident?i=tp">tp</a>, <a href="ident?i=cache">cache</a>) &amp;&amp; !<a href="ident?i=cache">cache</a>-&gt;<a href="ident?i=start_seq">start_seq</a> &amp;&amp;
<a name="L1741" href="source/net/ipv4/tcp_input.c#L1741">1741</a>                        !<a href="ident?i=cache">cache</a>-&gt;end_seq)
<a name="L1742" href="source/net/ipv4/tcp_input.c#L1742">1742</a>                         <a href="ident?i=cache">cache</a>++;
<a name="L1743" href="source/net/ipv4/tcp_input.c#L1743">1743</a>         }
<a name="L1744" href="source/net/ipv4/tcp_input.c#L1744">1744</a> 
<a name="L1745" href="source/net/ipv4/tcp_input.c#L1745">1745</a>         while (<a href="ident?i=i">i</a> &lt; used_sacks) {
<a name="L1746" href="source/net/ipv4/tcp_input.c#L1746">1746</a>                 <a href="ident?i=u32">u32</a> <a href="ident?i=start_seq">start_seq</a> = <a href="ident?i=sp">sp</a>[<a href="ident?i=i">i</a>].<a href="ident?i=start_seq">start_seq</a>;
<a name="L1747" href="source/net/ipv4/tcp_input.c#L1747">1747</a>                 <a href="ident?i=u32">u32</a> end_seq = <a href="ident?i=sp">sp</a>[<a href="ident?i=i">i</a>].end_seq;
<a name="L1748" href="source/net/ipv4/tcp_input.c#L1748">1748</a>                 <a href="ident?i=bool">bool</a> dup_sack = (found_dup_sack &amp;&amp; (<a href="ident?i=i">i</a> == first_sack_index));
<a name="L1749" href="source/net/ipv4/tcp_input.c#L1749">1749</a>                 struct <a href="ident?i=tcp_sack_block">tcp_sack_block</a> *next_dup = <a href="ident?i=NULL">NULL</a>;
<a name="L1750" href="source/net/ipv4/tcp_input.c#L1750">1750</a> 
<a name="L1751" href="source/net/ipv4/tcp_input.c#L1751">1751</a>                 if (found_dup_sack &amp;&amp; ((<a href="ident?i=i">i</a> + 1) == first_sack_index))
<a name="L1752" href="source/net/ipv4/tcp_input.c#L1752">1752</a>                         next_dup = &amp;<a href="ident?i=sp">sp</a>[<a href="ident?i=i">i</a> + 1];
<a name="L1753" href="source/net/ipv4/tcp_input.c#L1753">1753</a> 
<a name="L1754" href="source/net/ipv4/tcp_input.c#L1754">1754</a>                 <b><i>/* Skip too early cached blocks */</i></b>
<a name="L1755" href="source/net/ipv4/tcp_input.c#L1755">1755</a>                 while (<a href="ident?i=tcp_sack_cache_ok">tcp_sack_cache_ok</a>(<a href="ident?i=tp">tp</a>, <a href="ident?i=cache">cache</a>) &amp;&amp;
<a name="L1756" href="source/net/ipv4/tcp_input.c#L1756">1756</a>                        !<a href="ident?i=before">before</a>(<a href="ident?i=start_seq">start_seq</a>, <a href="ident?i=cache">cache</a>-&gt;end_seq))
<a name="L1757" href="source/net/ipv4/tcp_input.c#L1757">1757</a>                         <a href="ident?i=cache">cache</a>++;
<a name="L1758" href="source/net/ipv4/tcp_input.c#L1758">1758</a> 
<a name="L1759" href="source/net/ipv4/tcp_input.c#L1759">1759</a>                 <b><i>/* Can skip some work by looking recv_sack_cache? */</i></b>
<a name="L1760" href="source/net/ipv4/tcp_input.c#L1760">1760</a>                 if (<a href="ident?i=tcp_sack_cache_ok">tcp_sack_cache_ok</a>(<a href="ident?i=tp">tp</a>, <a href="ident?i=cache">cache</a>) &amp;&amp; !dup_sack &amp;&amp;
<a name="L1761" href="source/net/ipv4/tcp_input.c#L1761">1761</a>                     <a href="ident?i=after">after</a>(end_seq, <a href="ident?i=cache">cache</a>-&gt;<a href="ident?i=start_seq">start_seq</a>)) {
<a name="L1762" href="source/net/ipv4/tcp_input.c#L1762">1762</a> 
<a name="L1763" href="source/net/ipv4/tcp_input.c#L1763">1763</a>                         <b><i>/* Head todo? */</i></b>
<a name="L1764" href="source/net/ipv4/tcp_input.c#L1764">1764</a>                         if (<a href="ident?i=before">before</a>(<a href="ident?i=start_seq">start_seq</a>, <a href="ident?i=cache">cache</a>-&gt;<a href="ident?i=start_seq">start_seq</a>)) {
<a name="L1765" href="source/net/ipv4/tcp_input.c#L1765">1765</a>                                 <a href="ident?i=skb">skb</a> = <a href="ident?i=tcp_sacktag_skip">tcp_sacktag_skip</a>(<a href="ident?i=skb">skb</a>, sk, &amp;<a href="ident?i=state">state</a>,
<a name="L1766" href="source/net/ipv4/tcp_input.c#L1766">1766</a>                                                        <a href="ident?i=start_seq">start_seq</a>);
<a name="L1767" href="source/net/ipv4/tcp_input.c#L1767">1767</a>                                 <a href="ident?i=skb">skb</a> = <a href="ident?i=tcp_sacktag_walk">tcp_sacktag_walk</a>(<a href="ident?i=skb">skb</a>, sk, next_dup,
<a name="L1768" href="source/net/ipv4/tcp_input.c#L1768">1768</a>                                                        &amp;<a href="ident?i=state">state</a>,
<a name="L1769" href="source/net/ipv4/tcp_input.c#L1769">1769</a>                                                        <a href="ident?i=start_seq">start_seq</a>,
<a name="L1770" href="source/net/ipv4/tcp_input.c#L1770">1770</a>                                                        <a href="ident?i=cache">cache</a>-&gt;<a href="ident?i=start_seq">start_seq</a>,
<a name="L1771" href="source/net/ipv4/tcp_input.c#L1771">1771</a>                                                        dup_sack);
<a name="L1772" href="source/net/ipv4/tcp_input.c#L1772">1772</a>                         }
<a name="L1773" href="source/net/ipv4/tcp_input.c#L1773">1773</a> 
<a name="L1774" href="source/net/ipv4/tcp_input.c#L1774">1774</a>                         <b><i>/* Rest of the block already fully processed? */</i></b>
<a name="L1775" href="source/net/ipv4/tcp_input.c#L1775">1775</a>                         if (!<a href="ident?i=after">after</a>(end_seq, <a href="ident?i=cache">cache</a>-&gt;end_seq))
<a name="L1776" href="source/net/ipv4/tcp_input.c#L1776">1776</a>                                 goto advance_sp;
<a name="L1777" href="source/net/ipv4/tcp_input.c#L1777">1777</a> 
<a name="L1778" href="source/net/ipv4/tcp_input.c#L1778">1778</a>                         <a href="ident?i=skb">skb</a> = <a href="ident?i=tcp_maybe_skipping_dsack">tcp_maybe_skipping_dsack</a>(<a href="ident?i=skb">skb</a>, sk, next_dup,
<a name="L1779" href="source/net/ipv4/tcp_input.c#L1779">1779</a>                                                        &amp;<a href="ident?i=state">state</a>,
<a name="L1780" href="source/net/ipv4/tcp_input.c#L1780">1780</a>                                                        <a href="ident?i=cache">cache</a>-&gt;end_seq);
<a name="L1781" href="source/net/ipv4/tcp_input.c#L1781">1781</a> 
<a name="L1782" href="source/net/ipv4/tcp_input.c#L1782">1782</a>                         <b><i>/* ...tail remains todo... */</i></b>
<a name="L1783" href="source/net/ipv4/tcp_input.c#L1783">1783</a>                         if (<a href="ident?i=tcp_highest_sack_seq">tcp_highest_sack_seq</a>(<a href="ident?i=tp">tp</a>) == <a href="ident?i=cache">cache</a>-&gt;end_seq) {
<a name="L1784" href="source/net/ipv4/tcp_input.c#L1784">1784</a>                                 <b><i>/* ...but better entrypoint exists! */</i></b>
<a name="L1785" href="source/net/ipv4/tcp_input.c#L1785">1785</a>                                 <a href="ident?i=skb">skb</a> = <a href="ident?i=tcp_highest_sack">tcp_highest_sack</a>(sk);
<a name="L1786" href="source/net/ipv4/tcp_input.c#L1786">1786</a>                                 if (!<a href="ident?i=skb">skb</a>)
<a name="L1787" href="source/net/ipv4/tcp_input.c#L1787">1787</a>                                         break;
<a name="L1788" href="source/net/ipv4/tcp_input.c#L1788">1788</a>                                 <a href="ident?i=state">state</a>.fack_count = <a href="ident?i=tp">tp</a>-&gt;fackets_out;
<a name="L1789" href="source/net/ipv4/tcp_input.c#L1789">1789</a>                                 <a href="ident?i=cache">cache</a>++;
<a name="L1790" href="source/net/ipv4/tcp_input.c#L1790">1790</a>                                 goto <a href="ident?i=walk">walk</a>;
<a name="L1791" href="source/net/ipv4/tcp_input.c#L1791">1791</a>                         }
<a name="L1792" href="source/net/ipv4/tcp_input.c#L1792">1792</a> 
<a name="L1793" href="source/net/ipv4/tcp_input.c#L1793">1793</a>                         <a href="ident?i=skb">skb</a> = <a href="ident?i=tcp_sacktag_skip">tcp_sacktag_skip</a>(<a href="ident?i=skb">skb</a>, sk, &amp;<a href="ident?i=state">state</a>, <a href="ident?i=cache">cache</a>-&gt;end_seq);
<a name="L1794" href="source/net/ipv4/tcp_input.c#L1794">1794</a>                         <b><i>/* Check overlap against next cached too (past this one already) */</i></b>
<a name="L1795" href="source/net/ipv4/tcp_input.c#L1795">1795</a>                         <a href="ident?i=cache">cache</a>++;
<a name="L1796" href="source/net/ipv4/tcp_input.c#L1796">1796</a>                         continue;
<a name="L1797" href="source/net/ipv4/tcp_input.c#L1797">1797</a>                 }
<a name="L1798" href="source/net/ipv4/tcp_input.c#L1798">1798</a> 
<a name="L1799" href="source/net/ipv4/tcp_input.c#L1799">1799</a>                 if (!<a href="ident?i=before">before</a>(<a href="ident?i=start_seq">start_seq</a>, <a href="ident?i=tcp_highest_sack_seq">tcp_highest_sack_seq</a>(<a href="ident?i=tp">tp</a>))) {
<a name="L1800" href="source/net/ipv4/tcp_input.c#L1800">1800</a>                         <a href="ident?i=skb">skb</a> = <a href="ident?i=tcp_highest_sack">tcp_highest_sack</a>(sk);
<a name="L1801" href="source/net/ipv4/tcp_input.c#L1801">1801</a>                         if (!<a href="ident?i=skb">skb</a>)
<a name="L1802" href="source/net/ipv4/tcp_input.c#L1802">1802</a>                                 break;
<a name="L1803" href="source/net/ipv4/tcp_input.c#L1803">1803</a>                         <a href="ident?i=state">state</a>.fack_count = <a href="ident?i=tp">tp</a>-&gt;fackets_out;
<a name="L1804" href="source/net/ipv4/tcp_input.c#L1804">1804</a>                 }
<a name="L1805" href="source/net/ipv4/tcp_input.c#L1805">1805</a>                 <a href="ident?i=skb">skb</a> = <a href="ident?i=tcp_sacktag_skip">tcp_sacktag_skip</a>(<a href="ident?i=skb">skb</a>, sk, &amp;<a href="ident?i=state">state</a>, <a href="ident?i=start_seq">start_seq</a>);
<a name="L1806" href="source/net/ipv4/tcp_input.c#L1806">1806</a> 
<a name="L1807" href="source/net/ipv4/tcp_input.c#L1807">1807</a> <a href="ident?i=walk">walk</a>:
<a name="L1808" href="source/net/ipv4/tcp_input.c#L1808">1808</a>                 <a href="ident?i=skb">skb</a> = <a href="ident?i=tcp_sacktag_walk">tcp_sacktag_walk</a>(<a href="ident?i=skb">skb</a>, sk, next_dup, &amp;<a href="ident?i=state">state</a>,
<a name="L1809" href="source/net/ipv4/tcp_input.c#L1809">1809</a>                                        <a href="ident?i=start_seq">start_seq</a>, end_seq, dup_sack);
<a name="L1810" href="source/net/ipv4/tcp_input.c#L1810">1810</a> 
<a name="L1811" href="source/net/ipv4/tcp_input.c#L1811">1811</a> advance_sp:
<a name="L1812" href="source/net/ipv4/tcp_input.c#L1812">1812</a>                 <a href="ident?i=i">i</a>++;
<a name="L1813" href="source/net/ipv4/tcp_input.c#L1813">1813</a>         }
<a name="L1814" href="source/net/ipv4/tcp_input.c#L1814">1814</a> 
<a name="L1815" href="source/net/ipv4/tcp_input.c#L1815">1815</a>         <b><i>/* Clear the head of the cache sack blocks so we can skip it next time */</i></b>
<a name="L1816" href="source/net/ipv4/tcp_input.c#L1816">1816</a>         for (<a href="ident?i=i">i</a> = 0; <a href="ident?i=i">i</a> &lt; <a href="ident?i=ARRAY_SIZE">ARRAY_SIZE</a>(<a href="ident?i=tp">tp</a>-&gt;recv_sack_cache) - used_sacks; <a href="ident?i=i">i</a>++) {
<a name="L1817" href="source/net/ipv4/tcp_input.c#L1817">1817</a>                 <a href="ident?i=tp">tp</a>-&gt;recv_sack_cache[<a href="ident?i=i">i</a>].<a href="ident?i=start_seq">start_seq</a> = 0;
<a name="L1818" href="source/net/ipv4/tcp_input.c#L1818">1818</a>                 <a href="ident?i=tp">tp</a>-&gt;recv_sack_cache[<a href="ident?i=i">i</a>].end_seq = 0;
<a name="L1819" href="source/net/ipv4/tcp_input.c#L1819">1819</a>         }
<a name="L1820" href="source/net/ipv4/tcp_input.c#L1820">1820</a>         for (j = 0; j &lt; used_sacks; j++)
<a name="L1821" href="source/net/ipv4/tcp_input.c#L1821">1821</a>                 <a href="ident?i=tp">tp</a>-&gt;recv_sack_cache[<a href="ident?i=i">i</a>++] = <a href="ident?i=sp">sp</a>[j];
<a name="L1822" href="source/net/ipv4/tcp_input.c#L1822">1822</a> 
<a name="L1823" href="source/net/ipv4/tcp_input.c#L1823">1823</a>         if ((<a href="ident?i=state">state</a>.reord &lt; <a href="ident?i=tp">tp</a>-&gt;fackets_out) &amp;&amp;
<a name="L1824" href="source/net/ipv4/tcp_input.c#L1824">1824</a>             ((<a href="ident?i=inet_csk">inet_csk</a>(sk)-&gt;icsk_ca_state != TCP_CA_Loss) || <a href="ident?i=tp">tp</a>-&gt;undo_marker))
<a name="L1825" href="source/net/ipv4/tcp_input.c#L1825">1825</a>                 <a href="ident?i=tcp_update_reordering">tcp_update_reordering</a>(sk, <a href="ident?i=tp">tp</a>-&gt;fackets_out - <a href="ident?i=state">state</a>.reord, 0);
<a name="L1826" href="source/net/ipv4/tcp_input.c#L1826">1826</a> 
<a name="L1827" href="source/net/ipv4/tcp_input.c#L1827">1827</a>         <a href="ident?i=tcp_mark_lost_retrans">tcp_mark_lost_retrans</a>(sk);
<a name="L1828" href="source/net/ipv4/tcp_input.c#L1828">1828</a>         <a href="ident?i=tcp_verify_left_out">tcp_verify_left_out</a>(<a href="ident?i=tp">tp</a>);
<a name="L1829" href="source/net/ipv4/tcp_input.c#L1829">1829</a> <a href="ident?i=out">out</a>:
<a name="L1830" href="source/net/ipv4/tcp_input.c#L1830">1830</a> 
<a name="L1831" href="source/net/ipv4/tcp_input.c#L1831">1831</a> #if <a href="ident?i=FASTRETRANS_DEBUG">FASTRETRANS_DEBUG</a> &gt; 0
<a name="L1832" href="source/net/ipv4/tcp_input.c#L1832">1832</a>         <a href="ident?i=WARN_ON">WARN_ON</a>((int)<a href="ident?i=tp">tp</a>-&gt;sacked_out &lt; 0);
<a name="L1833" href="source/net/ipv4/tcp_input.c#L1833">1833</a>         <a href="ident?i=WARN_ON">WARN_ON</a>((int)<a href="ident?i=tp">tp</a>-&gt;lost_out &lt; 0);
<a name="L1834" href="source/net/ipv4/tcp_input.c#L1834">1834</a>         <a href="ident?i=WARN_ON">WARN_ON</a>((int)<a href="ident?i=tp">tp</a>-&gt;retrans_out &lt; 0);
<a name="L1835" href="source/net/ipv4/tcp_input.c#L1835">1835</a>         <a href="ident?i=WARN_ON">WARN_ON</a>((int)<a href="ident?i=tcp_packets_in_flight">tcp_packets_in_flight</a>(<a href="ident?i=tp">tp</a>) &lt; 0);
<a name="L1836" href="source/net/ipv4/tcp_input.c#L1836">1836</a> #endif
<a name="L1837" href="source/net/ipv4/tcp_input.c#L1837">1837</a>         *sack_rtt_us = <a href="ident?i=state">state</a>.rtt_us;
<a name="L1838" href="source/net/ipv4/tcp_input.c#L1838">1838</a>         return <a href="ident?i=state">state</a>.<a href="ident?i=flag">flag</a>;
<a name="L1839" href="source/net/ipv4/tcp_input.c#L1839">1839</a> }
<a name="L1840" href="source/net/ipv4/tcp_input.c#L1840">1840</a> 
<a name="L1841" href="source/net/ipv4/tcp_input.c#L1841">1841</a> <b><i>/* Limits sacked_out so that sum with lost_out isn't ever larger than</i></b>
<a name="L1842" href="source/net/ipv4/tcp_input.c#L1842">1842</a> <b><i> * packets_out. Returns false if sacked_out adjustement wasn't necessary.</i></b>
<a name="L1843" href="source/net/ipv4/tcp_input.c#L1843">1843</a> <b><i> */</i></b>
<a name="L1844" href="source/net/ipv4/tcp_input.c#L1844">1844</a> static <a href="ident?i=bool">bool</a> <a href="ident?i=tcp_limit_reno_sacked">tcp_limit_reno_sacked</a>(struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a>)
<a name="L1845" href="source/net/ipv4/tcp_input.c#L1845">1845</a> {
<a name="L1846" href="source/net/ipv4/tcp_input.c#L1846">1846</a>         <a href="ident?i=u32">u32</a> holes;
<a name="L1847" href="source/net/ipv4/tcp_input.c#L1847">1847</a> 
<a name="L1848" href="source/net/ipv4/tcp_input.c#L1848">1848</a>         holes = <a href="ident?i=max">max</a>(<a href="ident?i=tp">tp</a>-&gt;lost_out, 1U);
<a name="L1849" href="source/net/ipv4/tcp_input.c#L1849">1849</a>         holes = <a href="ident?i=min">min</a>(holes, <a href="ident?i=tp">tp</a>-&gt;packets_out);
<a name="L1850" href="source/net/ipv4/tcp_input.c#L1850">1850</a> 
<a name="L1851" href="source/net/ipv4/tcp_input.c#L1851">1851</a>         if ((<a href="ident?i=tp">tp</a>-&gt;sacked_out + holes) &gt; <a href="ident?i=tp">tp</a>-&gt;packets_out) {
<a name="L1852" href="source/net/ipv4/tcp_input.c#L1852">1852</a>                 <a href="ident?i=tp">tp</a>-&gt;sacked_out = <a href="ident?i=tp">tp</a>-&gt;packets_out - holes;
<a name="L1853" href="source/net/ipv4/tcp_input.c#L1853">1853</a>                 return <a href="ident?i=true">true</a>;
<a name="L1854" href="source/net/ipv4/tcp_input.c#L1854">1854</a>         }
<a name="L1855" href="source/net/ipv4/tcp_input.c#L1855">1855</a>         return <a href="ident?i=false">false</a>;
<a name="L1856" href="source/net/ipv4/tcp_input.c#L1856">1856</a> }
<a name="L1857" href="source/net/ipv4/tcp_input.c#L1857">1857</a> 
<a name="L1858" href="source/net/ipv4/tcp_input.c#L1858">1858</a> <b><i>/* If we receive more dupacks than we expected counting segments</i></b>
<a name="L1859" href="source/net/ipv4/tcp_input.c#L1859">1859</a> <b><i> * in assumption of absent reordering, interpret this as reordering.</i></b>
<a name="L1860" href="source/net/ipv4/tcp_input.c#L1860">1860</a> <b><i> * The only another reason could be bug in receiver TCP.</i></b>
<a name="L1861" href="source/net/ipv4/tcp_input.c#L1861">1861</a> <b><i> */</i></b>
<a name="L1862" href="source/net/ipv4/tcp_input.c#L1862">1862</a> static void <a href="ident?i=tcp_check_reno_reordering">tcp_check_reno_reordering</a>(struct <a href="ident?i=sock">sock</a> *sk, const int addend)
<a name="L1863" href="source/net/ipv4/tcp_input.c#L1863">1863</a> {
<a name="L1864" href="source/net/ipv4/tcp_input.c#L1864">1864</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L1865" href="source/net/ipv4/tcp_input.c#L1865">1865</a>         if (<a href="ident?i=tcp_limit_reno_sacked">tcp_limit_reno_sacked</a>(<a href="ident?i=tp">tp</a>))
<a name="L1866" href="source/net/ipv4/tcp_input.c#L1866">1866</a>                 <a href="ident?i=tcp_update_reordering">tcp_update_reordering</a>(sk, <a href="ident?i=tp">tp</a>-&gt;packets_out + addend, 0);
<a name="L1867" href="source/net/ipv4/tcp_input.c#L1867">1867</a> }
<a name="L1868" href="source/net/ipv4/tcp_input.c#L1868">1868</a> 
<a name="L1869" href="source/net/ipv4/tcp_input.c#L1869">1869</a> <b><i>/* Emulate SACKs for SACKless connection: account for a new dupack. */</i></b>
<a name="L1870" href="source/net/ipv4/tcp_input.c#L1870">1870</a> 
<a name="L1871" href="source/net/ipv4/tcp_input.c#L1871">1871</a> static void <a href="ident?i=tcp_add_reno_sack">tcp_add_reno_sack</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L1872" href="source/net/ipv4/tcp_input.c#L1872">1872</a> {
<a name="L1873" href="source/net/ipv4/tcp_input.c#L1873">1873</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L1874" href="source/net/ipv4/tcp_input.c#L1874">1874</a>         <a href="ident?i=tp">tp</a>-&gt;sacked_out++;
<a name="L1875" href="source/net/ipv4/tcp_input.c#L1875">1875</a>         <a href="ident?i=tcp_check_reno_reordering">tcp_check_reno_reordering</a>(sk, 0);
<a name="L1876" href="source/net/ipv4/tcp_input.c#L1876">1876</a>         <a href="ident?i=tcp_verify_left_out">tcp_verify_left_out</a>(<a href="ident?i=tp">tp</a>);
<a name="L1877" href="source/net/ipv4/tcp_input.c#L1877">1877</a> }
<a name="L1878" href="source/net/ipv4/tcp_input.c#L1878">1878</a> 
<a name="L1879" href="source/net/ipv4/tcp_input.c#L1879">1879</a> <b><i>/* Account for ACK, ACKing some data in Reno Recovery phase. */</i></b>
<a name="L1880" href="source/net/ipv4/tcp_input.c#L1880">1880</a> 
<a name="L1881" href="source/net/ipv4/tcp_input.c#L1881">1881</a> static void <a href="ident?i=tcp_remove_reno_sacks">tcp_remove_reno_sacks</a>(struct <a href="ident?i=sock">sock</a> *sk, int acked)
<a name="L1882" href="source/net/ipv4/tcp_input.c#L1882">1882</a> {
<a name="L1883" href="source/net/ipv4/tcp_input.c#L1883">1883</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L1884" href="source/net/ipv4/tcp_input.c#L1884">1884</a> 
<a name="L1885" href="source/net/ipv4/tcp_input.c#L1885">1885</a>         if (acked &gt; 0) {
<a name="L1886" href="source/net/ipv4/tcp_input.c#L1886">1886</a>                 <b><i>/* One ACK acked hole. The rest eat duplicate ACKs. */</i></b>
<a name="L1887" href="source/net/ipv4/tcp_input.c#L1887">1887</a>                 if (acked - 1 &gt;= <a href="ident?i=tp">tp</a>-&gt;sacked_out)
<a name="L1888" href="source/net/ipv4/tcp_input.c#L1888">1888</a>                         <a href="ident?i=tp">tp</a>-&gt;sacked_out = 0;
<a name="L1889" href="source/net/ipv4/tcp_input.c#L1889">1889</a>                 else
<a name="L1890" href="source/net/ipv4/tcp_input.c#L1890">1890</a>                         <a href="ident?i=tp">tp</a>-&gt;sacked_out -= acked - 1;
<a name="L1891" href="source/net/ipv4/tcp_input.c#L1891">1891</a>         }
<a name="L1892" href="source/net/ipv4/tcp_input.c#L1892">1892</a>         <a href="ident?i=tcp_check_reno_reordering">tcp_check_reno_reordering</a>(sk, acked);
<a name="L1893" href="source/net/ipv4/tcp_input.c#L1893">1893</a>         <a href="ident?i=tcp_verify_left_out">tcp_verify_left_out</a>(<a href="ident?i=tp">tp</a>);
<a name="L1894" href="source/net/ipv4/tcp_input.c#L1894">1894</a> }
<a name="L1895" href="source/net/ipv4/tcp_input.c#L1895">1895</a> 
<a name="L1896" href="source/net/ipv4/tcp_input.c#L1896">1896</a> static inline void <a href="ident?i=tcp_reset_reno_sack">tcp_reset_reno_sack</a>(struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a>)
<a name="L1897" href="source/net/ipv4/tcp_input.c#L1897">1897</a> {
<a name="L1898" href="source/net/ipv4/tcp_input.c#L1898">1898</a>         <a href="ident?i=tp">tp</a>-&gt;sacked_out = 0;
<a name="L1899" href="source/net/ipv4/tcp_input.c#L1899">1899</a> }
<a name="L1900" href="source/net/ipv4/tcp_input.c#L1900">1900</a> 
<a name="L1901" href="source/net/ipv4/tcp_input.c#L1901">1901</a> void <a href="ident?i=tcp_clear_retrans">tcp_clear_retrans</a>(struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a>)
<a name="L1902" href="source/net/ipv4/tcp_input.c#L1902">1902</a> {
<a name="L1903" href="source/net/ipv4/tcp_input.c#L1903">1903</a>         <a href="ident?i=tp">tp</a>-&gt;retrans_out = 0;
<a name="L1904" href="source/net/ipv4/tcp_input.c#L1904">1904</a>         <a href="ident?i=tp">tp</a>-&gt;lost_out = 0;
<a name="L1905" href="source/net/ipv4/tcp_input.c#L1905">1905</a>         <a href="ident?i=tp">tp</a>-&gt;undo_marker = 0;
<a name="L1906" href="source/net/ipv4/tcp_input.c#L1906">1906</a>         <a href="ident?i=tp">tp</a>-&gt;undo_retrans = -1;
<a name="L1907" href="source/net/ipv4/tcp_input.c#L1907">1907</a>         <a href="ident?i=tp">tp</a>-&gt;fackets_out = 0;
<a name="L1908" href="source/net/ipv4/tcp_input.c#L1908">1908</a>         <a href="ident?i=tp">tp</a>-&gt;sacked_out = 0;
<a name="L1909" href="source/net/ipv4/tcp_input.c#L1909">1909</a> }
<a name="L1910" href="source/net/ipv4/tcp_input.c#L1910">1910</a> 
<a name="L1911" href="source/net/ipv4/tcp_input.c#L1911">1911</a> static inline void <a href="ident?i=tcp_init_undo">tcp_init_undo</a>(struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a>)
<a name="L1912" href="source/net/ipv4/tcp_input.c#L1912">1912</a> {
<a name="L1913" href="source/net/ipv4/tcp_input.c#L1913">1913</a>         <a href="ident?i=tp">tp</a>-&gt;undo_marker = <a href="ident?i=tp">tp</a>-&gt;snd_una;
<a name="L1914" href="source/net/ipv4/tcp_input.c#L1914">1914</a>         <b><i>/* Retransmission still in flight may cause DSACKs later. */</i></b>
<a name="L1915" href="source/net/ipv4/tcp_input.c#L1915">1915</a>         <a href="ident?i=tp">tp</a>-&gt;undo_retrans = <a href="ident?i=tp">tp</a>-&gt;retrans_out ? : -1;
<a name="L1916" href="source/net/ipv4/tcp_input.c#L1916">1916</a> }
<a name="L1917" href="source/net/ipv4/tcp_input.c#L1917">1917</a> 
<a name="L1918" href="source/net/ipv4/tcp_input.c#L1918">1918</a> <b><i>/* Enter Loss state. If we detect SACK reneging, forget all SACK information</i></b>
<a name="L1919" href="source/net/ipv4/tcp_input.c#L1919">1919</a> <b><i> * and reset tags completely, otherwise preserve SACKs. If receiver</i></b>
<a name="L1920" href="source/net/ipv4/tcp_input.c#L1920">1920</a> <b><i> * dropped its ofo queue, we will know this due to reneging detection.</i></b>
<a name="L1921" href="source/net/ipv4/tcp_input.c#L1921">1921</a> <b><i> */</i></b>
<a name="L1922" href="source/net/ipv4/tcp_input.c#L1922">1922</a> void <a href="ident?i=tcp_enter_loss">tcp_enter_loss</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L1923" href="source/net/ipv4/tcp_input.c#L1923">1923</a> {
<a name="L1924" href="source/net/ipv4/tcp_input.c#L1924">1924</a>         const struct <a href="ident?i=inet_connection_sock">inet_connection_sock</a> *icsk = <a href="ident?i=inet_csk">inet_csk</a>(sk);
<a name="L1925" href="source/net/ipv4/tcp_input.c#L1925">1925</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L1926" href="source/net/ipv4/tcp_input.c#L1926">1926</a>         struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>;
<a name="L1927" href="source/net/ipv4/tcp_input.c#L1927">1927</a>         <a href="ident?i=bool">bool</a> new_recovery = <a href="ident?i=false">false</a>;
<a name="L1928" href="source/net/ipv4/tcp_input.c#L1928">1928</a>         <a href="ident?i=bool">bool</a> is_reneg;                  <b><i>/* is receiver reneging on SACKs? */</i></b>
<a name="L1929" href="source/net/ipv4/tcp_input.c#L1929">1929</a> 
<a name="L1930" href="source/net/ipv4/tcp_input.c#L1930">1930</a>         <b><i>/* Reduce ssthresh if it has not yet been made inside this window. */</i></b>
<a name="L1931" href="source/net/ipv4/tcp_input.c#L1931">1931</a>         if (icsk-&gt;icsk_ca_state &lt;= TCP_CA_Disorder ||
<a name="L1932" href="source/net/ipv4/tcp_input.c#L1932">1932</a>             !<a href="ident?i=after">after</a>(<a href="ident?i=tp">tp</a>-&gt;high_seq, <a href="ident?i=tp">tp</a>-&gt;snd_una) ||
<a name="L1933" href="source/net/ipv4/tcp_input.c#L1933">1933</a>             (icsk-&gt;icsk_ca_state == TCP_CA_Loss &amp;&amp; !icsk-&gt;icsk_retransmits)) {
<a name="L1934" href="source/net/ipv4/tcp_input.c#L1934">1934</a>                 new_recovery = <a href="ident?i=true">true</a>;
<a name="L1935" href="source/net/ipv4/tcp_input.c#L1935">1935</a>                 <a href="ident?i=tp">tp</a>-&gt;prior_ssthresh = <a href="ident?i=tcp_current_ssthresh">tcp_current_ssthresh</a>(sk);
<a name="L1936" href="source/net/ipv4/tcp_input.c#L1936">1936</a>                 <a href="ident?i=tp">tp</a>-&gt;snd_ssthresh = icsk-&gt;icsk_ca_ops-&gt;ssthresh(sk);
<a name="L1937" href="source/net/ipv4/tcp_input.c#L1937">1937</a>                 <a href="ident?i=tcp_ca_event">tcp_ca_event</a>(sk, CA_EVENT_LOSS);
<a name="L1938" href="source/net/ipv4/tcp_input.c#L1938">1938</a>                 <a href="ident?i=tcp_init_undo">tcp_init_undo</a>(<a href="ident?i=tp">tp</a>);
<a name="L1939" href="source/net/ipv4/tcp_input.c#L1939">1939</a>         }
<a name="L1940" href="source/net/ipv4/tcp_input.c#L1940">1940</a>         <a href="ident?i=tp">tp</a>-&gt;snd_cwnd       = 1;
<a name="L1941" href="source/net/ipv4/tcp_input.c#L1941">1941</a>         <a href="ident?i=tp">tp</a>-&gt;snd_cwnd_cnt   = 0;
<a name="L1942" href="source/net/ipv4/tcp_input.c#L1942">1942</a>         <a href="ident?i=tp">tp</a>-&gt;snd_cwnd_stamp = <a href="ident?i=tcp_time_stamp">tcp_time_stamp</a>;
<a name="L1943" href="source/net/ipv4/tcp_input.c#L1943">1943</a> 
<a name="L1944" href="source/net/ipv4/tcp_input.c#L1944">1944</a>         <a href="ident?i=tp">tp</a>-&gt;retrans_out = 0;
<a name="L1945" href="source/net/ipv4/tcp_input.c#L1945">1945</a>         <a href="ident?i=tp">tp</a>-&gt;lost_out = 0;
<a name="L1946" href="source/net/ipv4/tcp_input.c#L1946">1946</a> 
<a name="L1947" href="source/net/ipv4/tcp_input.c#L1947">1947</a>         if (<a href="ident?i=tcp_is_reno">tcp_is_reno</a>(<a href="ident?i=tp">tp</a>))
<a name="L1948" href="source/net/ipv4/tcp_input.c#L1948">1948</a>                 <a href="ident?i=tcp_reset_reno_sack">tcp_reset_reno_sack</a>(<a href="ident?i=tp">tp</a>);
<a name="L1949" href="source/net/ipv4/tcp_input.c#L1949">1949</a> 
<a name="L1950" href="source/net/ipv4/tcp_input.c#L1950">1950</a>         <a href="ident?i=skb">skb</a> = <a href="ident?i=tcp_write_queue_head">tcp_write_queue_head</a>(sk);
<a name="L1951" href="source/net/ipv4/tcp_input.c#L1951">1951</a>         is_reneg = <a href="ident?i=skb">skb</a> &amp;&amp; (<a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;sacked &amp; <a href="ident?i=TCPCB_SACKED_ACKED">TCPCB_SACKED_ACKED</a>);
<a name="L1952" href="source/net/ipv4/tcp_input.c#L1952">1952</a>         if (is_reneg) {
<a name="L1953" href="source/net/ipv4/tcp_input.c#L1953">1953</a>                 <a href="ident?i=NET_INC_STATS_BH">NET_INC_STATS_BH</a>(<a href="ident?i=sock_net">sock_net</a>(sk), LINUX_MIB_TCPSACKRENEGING);
<a name="L1954" href="source/net/ipv4/tcp_input.c#L1954">1954</a>                 <a href="ident?i=tp">tp</a>-&gt;sacked_out = 0;
<a name="L1955" href="source/net/ipv4/tcp_input.c#L1955">1955</a>                 <a href="ident?i=tp">tp</a>-&gt;fackets_out = 0;
<a name="L1956" href="source/net/ipv4/tcp_input.c#L1956">1956</a>         }
<a name="L1957" href="source/net/ipv4/tcp_input.c#L1957">1957</a>         <a href="ident?i=tcp_clear_all_retrans_hints">tcp_clear_all_retrans_hints</a>(<a href="ident?i=tp">tp</a>);
<a name="L1958" href="source/net/ipv4/tcp_input.c#L1958">1958</a> 
<a name="L1959" href="source/net/ipv4/tcp_input.c#L1959">1959</a>         <a href="ident?i=tcp_for_write_queue">tcp_for_write_queue</a>(<a href="ident?i=skb">skb</a>, sk) {
<a name="L1960" href="source/net/ipv4/tcp_input.c#L1960">1960</a>                 if (<a href="ident?i=skb">skb</a> == <a href="ident?i=tcp_send_head">tcp_send_head</a>(sk))
<a name="L1961" href="source/net/ipv4/tcp_input.c#L1961">1961</a>                         break;
<a name="L1962" href="source/net/ipv4/tcp_input.c#L1962">1962</a> 
<a name="L1963" href="source/net/ipv4/tcp_input.c#L1963">1963</a>                 <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;sacked &amp;= (~TCPCB_TAGBITS)|<a href="ident?i=TCPCB_SACKED_ACKED">TCPCB_SACKED_ACKED</a>;
<a name="L1964" href="source/net/ipv4/tcp_input.c#L1964">1964</a>                 if (!(<a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;sacked&amp;<a href="ident?i=TCPCB_SACKED_ACKED">TCPCB_SACKED_ACKED</a>) || is_reneg) {
<a name="L1965" href="source/net/ipv4/tcp_input.c#L1965">1965</a>                         <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;sacked &amp;= ~TCPCB_SACKED_ACKED;
<a name="L1966" href="source/net/ipv4/tcp_input.c#L1966">1966</a>                         <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;sacked |= <a href="ident?i=TCPCB_LOST">TCPCB_LOST</a>;
<a name="L1967" href="source/net/ipv4/tcp_input.c#L1967">1967</a>                         <a href="ident?i=tp">tp</a>-&gt;lost_out += <a href="ident?i=tcp_skb_pcount">tcp_skb_pcount</a>(<a href="ident?i=skb">skb</a>);
<a name="L1968" href="source/net/ipv4/tcp_input.c#L1968">1968</a>                         <a href="ident?i=tp">tp</a>-&gt;retransmit_high = <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;end_seq;
<a name="L1969" href="source/net/ipv4/tcp_input.c#L1969">1969</a>                 }
<a name="L1970" href="source/net/ipv4/tcp_input.c#L1970">1970</a>         }
<a name="L1971" href="source/net/ipv4/tcp_input.c#L1971">1971</a>         <a href="ident?i=tcp_verify_left_out">tcp_verify_left_out</a>(<a href="ident?i=tp">tp</a>);
<a name="L1972" href="source/net/ipv4/tcp_input.c#L1972">1972</a> 
<a name="L1973" href="source/net/ipv4/tcp_input.c#L1973">1973</a>         <b><i>/* Timeout in disordered state after receiving substantial DUPACKs</i></b>
<a name="L1974" href="source/net/ipv4/tcp_input.c#L1974">1974</a> <b><i>         * suggests that the degree of reordering is over-estimated.</i></b>
<a name="L1975" href="source/net/ipv4/tcp_input.c#L1975">1975</a> <b><i>         */</i></b>
<a name="L1976" href="source/net/ipv4/tcp_input.c#L1976">1976</a>         if (icsk-&gt;icsk_ca_state &lt;= TCP_CA_Disorder &amp;&amp;
<a name="L1977" href="source/net/ipv4/tcp_input.c#L1977">1977</a>             <a href="ident?i=tp">tp</a>-&gt;sacked_out &gt;= <a href="ident?i=sysctl_tcp_reordering">sysctl_tcp_reordering</a>)
<a name="L1978" href="source/net/ipv4/tcp_input.c#L1978">1978</a>                 <a href="ident?i=tp">tp</a>-&gt;reordering = <a href="ident?i=min_t">min_t</a>(unsigned int, <a href="ident?i=tp">tp</a>-&gt;reordering,
<a name="L1979" href="source/net/ipv4/tcp_input.c#L1979">1979</a>                                        <a href="ident?i=sysctl_tcp_reordering">sysctl_tcp_reordering</a>);
<a name="L1980" href="source/net/ipv4/tcp_input.c#L1980">1980</a>         <a href="ident?i=tcp_set_ca_state">tcp_set_ca_state</a>(sk, TCP_CA_Loss);
<a name="L1981" href="source/net/ipv4/tcp_input.c#L1981">1981</a>         <a href="ident?i=tp">tp</a>-&gt;high_seq = <a href="ident?i=tp">tp</a>-&gt;snd_nxt;
<a name="L1982" href="source/net/ipv4/tcp_input.c#L1982">1982</a>         <a href="ident?i=tcp_ecn_queue_cwr">tcp_ecn_queue_cwr</a>(<a href="ident?i=tp">tp</a>);
<a name="L1983" href="source/net/ipv4/tcp_input.c#L1983">1983</a> 
<a name="L1984" href="source/net/ipv4/tcp_input.c#L1984">1984</a>         <b><i>/* F-RTO RFC5682 sec 3.1 step 1: retransmit SND.UNA if no previous</i></b>
<a name="L1985" href="source/net/ipv4/tcp_input.c#L1985">1985</a> <b><i>         * loss recovery is underway except recurring timeout(s) on</i></b>
<a name="L1986" href="source/net/ipv4/tcp_input.c#L1986">1986</a> <b><i>         * the same SND.UNA (sec 3.2). Disable F-RTO on path MTU probing</i></b>
<a name="L1987" href="source/net/ipv4/tcp_input.c#L1987">1987</a> <b><i>         */</i></b>
<a name="L1988" href="source/net/ipv4/tcp_input.c#L1988">1988</a>         <a href="ident?i=tp">tp</a>-&gt;frto = <a href="ident?i=sysctl_tcp_frto">sysctl_tcp_frto</a> &amp;&amp;
<a name="L1989" href="source/net/ipv4/tcp_input.c#L1989">1989</a>                    (new_recovery || icsk-&gt;icsk_retransmits) &amp;&amp;
<a name="L1990" href="source/net/ipv4/tcp_input.c#L1990">1990</a>                    !<a href="ident?i=inet_csk">inet_csk</a>(sk)-&gt;icsk_mtup.probe_size;
<a name="L1991" href="source/net/ipv4/tcp_input.c#L1991">1991</a> }
<a name="L1992" href="source/net/ipv4/tcp_input.c#L1992">1992</a> 
<a name="L1993" href="source/net/ipv4/tcp_input.c#L1993">1993</a> <b><i>/* If ACK arrived pointing to a remembered SACK, it means that our</i></b>
<a name="L1994" href="source/net/ipv4/tcp_input.c#L1994">1994</a> <b><i> * remembered SACKs do not reflect real state of receiver i.e.</i></b>
<a name="L1995" href="source/net/ipv4/tcp_input.c#L1995">1995</a> <b><i> * receiver _host_ is heavily congested (or buggy).</i></b>
<a name="L1996" href="source/net/ipv4/tcp_input.c#L1996">1996</a> <b><i> *</i></b>
<a name="L1997" href="source/net/ipv4/tcp_input.c#L1997">1997</a> <b><i> * To avoid big spurious retransmission bursts due to transient SACK</i></b>
<a name="L1998" href="source/net/ipv4/tcp_input.c#L1998">1998</a> <b><i> * scoreboard oddities that look like reneging, we give the receiver a</i></b>
<a name="L1999" href="source/net/ipv4/tcp_input.c#L1999">1999</a> <b><i> * little time (max(RTT/2, 10ms)) to send us some more ACKs that will</i></b>
<a name="L2000" href="source/net/ipv4/tcp_input.c#L2000">2000</a> <b><i> * restore sanity to the SACK scoreboard. If the apparent reneging</i></b>
<a name="L2001" href="source/net/ipv4/tcp_input.c#L2001">2001</a> <b><i> * persists until this RTO then we'll clear the SACK scoreboard.</i></b>
<a name="L2002" href="source/net/ipv4/tcp_input.c#L2002">2002</a> <b><i> */</i></b>
<a name="L2003" href="source/net/ipv4/tcp_input.c#L2003">2003</a> static <a href="ident?i=bool">bool</a> <a href="ident?i=tcp_check_sack_reneging">tcp_check_sack_reneging</a>(struct <a href="ident?i=sock">sock</a> *sk, int <a href="ident?i=flag">flag</a>)
<a name="L2004" href="source/net/ipv4/tcp_input.c#L2004">2004</a> {
<a name="L2005" href="source/net/ipv4/tcp_input.c#L2005">2005</a>         if (<a href="ident?i=flag">flag</a> &amp; <a href="ident?i=FLAG_SACK_RENEGING">FLAG_SACK_RENEGING</a>) {
<a name="L2006" href="source/net/ipv4/tcp_input.c#L2006">2006</a>                 struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L2007" href="source/net/ipv4/tcp_input.c#L2007">2007</a>                 unsigned long <a href="ident?i=delay">delay</a> = <a href="ident?i=max">max</a>(<a href="ident?i=usecs_to_jiffies">usecs_to_jiffies</a>(<a href="ident?i=tp">tp</a>-&gt;srtt_us &gt;&gt; 4),
<a name="L2008" href="source/net/ipv4/tcp_input.c#L2008">2008</a>                                           <a href="ident?i=msecs_to_jiffies">msecs_to_jiffies</a>(10));
<a name="L2009" href="source/net/ipv4/tcp_input.c#L2009">2009</a> 
<a name="L2010" href="source/net/ipv4/tcp_input.c#L2010">2010</a>                 <a href="ident?i=inet_csk_reset_xmit_timer">inet_csk_reset_xmit_timer</a>(sk, <a href="ident?i=ICSK_TIME_RETRANS">ICSK_TIME_RETRANS</a>,
<a name="L2011" href="source/net/ipv4/tcp_input.c#L2011">2011</a>                                           <a href="ident?i=delay">delay</a>, <a href="ident?i=TCP_RTO_MAX">TCP_RTO_MAX</a>);
<a name="L2012" href="source/net/ipv4/tcp_input.c#L2012">2012</a>                 return <a href="ident?i=true">true</a>;
<a name="L2013" href="source/net/ipv4/tcp_input.c#L2013">2013</a>         }
<a name="L2014" href="source/net/ipv4/tcp_input.c#L2014">2014</a>         return <a href="ident?i=false">false</a>;
<a name="L2015" href="source/net/ipv4/tcp_input.c#L2015">2015</a> }
<a name="L2016" href="source/net/ipv4/tcp_input.c#L2016">2016</a> 
<a name="L2017" href="source/net/ipv4/tcp_input.c#L2017">2017</a> static inline int <a href="ident?i=tcp_fackets_out">tcp_fackets_out</a>(const struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a>)
<a name="L2018" href="source/net/ipv4/tcp_input.c#L2018">2018</a> {
<a name="L2019" href="source/net/ipv4/tcp_input.c#L2019">2019</a>         return <a href="ident?i=tcp_is_reno">tcp_is_reno</a>(<a href="ident?i=tp">tp</a>) ? <a href="ident?i=tp">tp</a>-&gt;sacked_out + 1 : <a href="ident?i=tp">tp</a>-&gt;fackets_out;
<a name="L2020" href="source/net/ipv4/tcp_input.c#L2020">2020</a> }
<a name="L2021" href="source/net/ipv4/tcp_input.c#L2021">2021</a> 
<a name="L2022" href="source/net/ipv4/tcp_input.c#L2022">2022</a> <b><i>/* Heurestics to calculate number of duplicate ACKs. There's no dupACKs</i></b>
<a name="L2023" href="source/net/ipv4/tcp_input.c#L2023">2023</a> <b><i> * counter when SACK is enabled (without SACK, sacked_out is used for</i></b>
<a name="L2024" href="source/net/ipv4/tcp_input.c#L2024">2024</a> <b><i> * that purpose).</i></b>
<a name="L2025" href="source/net/ipv4/tcp_input.c#L2025">2025</a> <b><i> *</i></b>
<a name="L2026" href="source/net/ipv4/tcp_input.c#L2026">2026</a> <b><i> * Instead, with FACK TCP uses fackets_out that includes both SACKed</i></b>
<a name="L2027" href="source/net/ipv4/tcp_input.c#L2027">2027</a> <b><i> * segments up to the highest received SACK block so far and holes in</i></b>
<a name="L2028" href="source/net/ipv4/tcp_input.c#L2028">2028</a> <b><i> * between them.</i></b>
<a name="L2029" href="source/net/ipv4/tcp_input.c#L2029">2029</a> <b><i> *</i></b>
<a name="L2030" href="source/net/ipv4/tcp_input.c#L2030">2030</a> <b><i> * With reordering, holes may still be in flight, so RFC3517 recovery</i></b>
<a name="L2031" href="source/net/ipv4/tcp_input.c#L2031">2031</a> <b><i> * uses pure sacked_out (total number of SACKed segments) even though</i></b>
<a name="L2032" href="source/net/ipv4/tcp_input.c#L2032">2032</a> <b><i> * it violates the RFC that uses duplicate ACKs, often these are equal</i></b>
<a name="L2033" href="source/net/ipv4/tcp_input.c#L2033">2033</a> <b><i> * but when e.g. out-of-window ACKs or packet duplication occurs,</i></b>
<a name="L2034" href="source/net/ipv4/tcp_input.c#L2034">2034</a> <b><i> * they differ. Since neither occurs due to loss, TCP should really</i></b>
<a name="L2035" href="source/net/ipv4/tcp_input.c#L2035">2035</a> <b><i> * ignore them.</i></b>
<a name="L2036" href="source/net/ipv4/tcp_input.c#L2036">2036</a> <b><i> */</i></b>
<a name="L2037" href="source/net/ipv4/tcp_input.c#L2037">2037</a> static inline int <a href="ident?i=tcp_dupack_heuristics">tcp_dupack_heuristics</a>(const struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a>)
<a name="L2038" href="source/net/ipv4/tcp_input.c#L2038">2038</a> {
<a name="L2039" href="source/net/ipv4/tcp_input.c#L2039">2039</a>         return <a href="ident?i=tcp_is_fack">tcp_is_fack</a>(<a href="ident?i=tp">tp</a>) ? <a href="ident?i=tp">tp</a>-&gt;fackets_out : <a href="ident?i=tp">tp</a>-&gt;sacked_out + 1;
<a name="L2040" href="source/net/ipv4/tcp_input.c#L2040">2040</a> }
<a name="L2041" href="source/net/ipv4/tcp_input.c#L2041">2041</a> 
<a name="L2042" href="source/net/ipv4/tcp_input.c#L2042">2042</a> static <a href="ident?i=bool">bool</a> <a href="ident?i=tcp_pause_early_retransmit">tcp_pause_early_retransmit</a>(struct <a href="ident?i=sock">sock</a> *sk, int <a href="ident?i=flag">flag</a>)
<a name="L2043" href="source/net/ipv4/tcp_input.c#L2043">2043</a> {
<a name="L2044" href="source/net/ipv4/tcp_input.c#L2044">2044</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L2045" href="source/net/ipv4/tcp_input.c#L2045">2045</a>         unsigned long <a href="ident?i=delay">delay</a>;
<a name="L2046" href="source/net/ipv4/tcp_input.c#L2046">2046</a> 
<a name="L2047" href="source/net/ipv4/tcp_input.c#L2047">2047</a>         <b><i>/* Delay early retransmit and entering fast recovery for</i></b>
<a name="L2048" href="source/net/ipv4/tcp_input.c#L2048">2048</a> <b><i>         * max(RTT/4, 2msec) unless ack has ECE mark, no RTT samples</i></b>
<a name="L2049" href="source/net/ipv4/tcp_input.c#L2049">2049</a> <b><i>         * available, or RTO is scheduled to fire first.</i></b>
<a name="L2050" href="source/net/ipv4/tcp_input.c#L2050">2050</a> <b><i>         */</i></b>
<a name="L2051" href="source/net/ipv4/tcp_input.c#L2051">2051</a>         if (<a href="ident?i=sysctl_tcp_early_retrans">sysctl_tcp_early_retrans</a> &lt; 2 || <a href="ident?i=sysctl_tcp_early_retrans">sysctl_tcp_early_retrans</a> &gt; 3 ||
<a name="L2052" href="source/net/ipv4/tcp_input.c#L2052">2052</a>             (<a href="ident?i=flag">flag</a> &amp; <a href="ident?i=FLAG_ECE">FLAG_ECE</a>) || !<a href="ident?i=tp">tp</a>-&gt;srtt_us)
<a name="L2053" href="source/net/ipv4/tcp_input.c#L2053">2053</a>                 return <a href="ident?i=false">false</a>;
<a name="L2054" href="source/net/ipv4/tcp_input.c#L2054">2054</a> 
<a name="L2055" href="source/net/ipv4/tcp_input.c#L2055">2055</a>         <a href="ident?i=delay">delay</a> = <a href="ident?i=max">max</a>(<a href="ident?i=usecs_to_jiffies">usecs_to_jiffies</a>(<a href="ident?i=tp">tp</a>-&gt;srtt_us &gt;&gt; 5),
<a name="L2056" href="source/net/ipv4/tcp_input.c#L2056">2056</a>                     <a href="ident?i=msecs_to_jiffies">msecs_to_jiffies</a>(2));
<a name="L2057" href="source/net/ipv4/tcp_input.c#L2057">2057</a> 
<a name="L2058" href="source/net/ipv4/tcp_input.c#L2058">2058</a>         if (!<a href="ident?i=time_after">time_after</a>(<a href="ident?i=inet_csk">inet_csk</a>(sk)-&gt;icsk_timeout, (<a href="ident?i=jiffies">jiffies</a> + <a href="ident?i=delay">delay</a>)))
<a name="L2059" href="source/net/ipv4/tcp_input.c#L2059">2059</a>                 return <a href="ident?i=false">false</a>;
<a name="L2060" href="source/net/ipv4/tcp_input.c#L2060">2060</a> 
<a name="L2061" href="source/net/ipv4/tcp_input.c#L2061">2061</a>         <a href="ident?i=inet_csk_reset_xmit_timer">inet_csk_reset_xmit_timer</a>(sk, <a href="ident?i=ICSK_TIME_EARLY_RETRANS">ICSK_TIME_EARLY_RETRANS</a>, <a href="ident?i=delay">delay</a>,
<a name="L2062" href="source/net/ipv4/tcp_input.c#L2062">2062</a>                                   <a href="ident?i=TCP_RTO_MAX">TCP_RTO_MAX</a>);
<a name="L2063" href="source/net/ipv4/tcp_input.c#L2063">2063</a>         return <a href="ident?i=true">true</a>;
<a name="L2064" href="source/net/ipv4/tcp_input.c#L2064">2064</a> }
<a name="L2065" href="source/net/ipv4/tcp_input.c#L2065">2065</a> 
<a name="L2066" href="source/net/ipv4/tcp_input.c#L2066">2066</a> <b><i>/* Linux NewReno/SACK/FACK/ECN state machine.</i></b>
<a name="L2067" href="source/net/ipv4/tcp_input.c#L2067">2067</a> <b><i> * --------------------------------------</i></b>
<a name="L2068" href="source/net/ipv4/tcp_input.c#L2068">2068</a> <b><i> *</i></b>
<a name="L2069" href="source/net/ipv4/tcp_input.c#L2069">2069</a> <b><i> * "Open"       Normal state, no dubious events, fast path.</i></b>
<a name="L2070" href="source/net/ipv4/tcp_input.c#L2070">2070</a> <b><i> * "Disorder"   In all the respects it is "Open",</i></b>
<a name="L2071" href="source/net/ipv4/tcp_input.c#L2071">2071</a> <b><i> *              but requires a bit more attention. It is entered when</i></b>
<a name="L2072" href="source/net/ipv4/tcp_input.c#L2072">2072</a> <b><i> *              we see some SACKs or dupacks. It is split of "Open"</i></b>
<a name="L2073" href="source/net/ipv4/tcp_input.c#L2073">2073</a> <b><i> *              mainly to move some processing from fast path to slow one.</i></b>
<a name="L2074" href="source/net/ipv4/tcp_input.c#L2074">2074</a> <b><i> * "CWR"        CWND was reduced due to some Congestion Notification event.</i></b>
<a name="L2075" href="source/net/ipv4/tcp_input.c#L2075">2075</a> <b><i> *              It can be ECN, ICMP source quench, local device congestion.</i></b>
<a name="L2076" href="source/net/ipv4/tcp_input.c#L2076">2076</a> <b><i> * "Recovery"   CWND was reduced, we are fast-retransmitting.</i></b>
<a name="L2077" href="source/net/ipv4/tcp_input.c#L2077">2077</a> <b><i> * "Loss"       CWND was reduced due to RTO timeout or SACK reneging.</i></b>
<a name="L2078" href="source/net/ipv4/tcp_input.c#L2078">2078</a> <b><i> *</i></b>
<a name="L2079" href="source/net/ipv4/tcp_input.c#L2079">2079</a> <b><i> * tcp_fastretrans_alert() is entered:</i></b>
<a name="L2080" href="source/net/ipv4/tcp_input.c#L2080">2080</a> <b><i> * - each incoming ACK, if state is not "Open"</i></b>
<a name="L2081" href="source/net/ipv4/tcp_input.c#L2081">2081</a> <b><i> * - when arrived ACK is unusual, namely:</i></b>
<a name="L2082" href="source/net/ipv4/tcp_input.c#L2082">2082</a> <b><i> *      * SACK</i></b>
<a name="L2083" href="source/net/ipv4/tcp_input.c#L2083">2083</a> <b><i> *      * Duplicate ACK.</i></b>
<a name="L2084" href="source/net/ipv4/tcp_input.c#L2084">2084</a> <b><i> *      * ECN ECE.</i></b>
<a name="L2085" href="source/net/ipv4/tcp_input.c#L2085">2085</a> <b><i> *</i></b>
<a name="L2086" href="source/net/ipv4/tcp_input.c#L2086">2086</a> <b><i> * Counting packets in flight is pretty simple.</i></b>
<a name="L2087" href="source/net/ipv4/tcp_input.c#L2087">2087</a> <b><i> *</i></b>
<a name="L2088" href="source/net/ipv4/tcp_input.c#L2088">2088</a> <b><i> *      in_flight = packets_out - left_out + retrans_out</i></b>
<a name="L2089" href="source/net/ipv4/tcp_input.c#L2089">2089</a> <b><i> *</i></b>
<a name="L2090" href="source/net/ipv4/tcp_input.c#L2090">2090</a> <b><i> *      packets_out is SND.NXT-SND.UNA counted in packets.</i></b>
<a name="L2091" href="source/net/ipv4/tcp_input.c#L2091">2091</a> <b><i> *</i></b>
<a name="L2092" href="source/net/ipv4/tcp_input.c#L2092">2092</a> <b><i> *      retrans_out is number of retransmitted segments.</i></b>
<a name="L2093" href="source/net/ipv4/tcp_input.c#L2093">2093</a> <b><i> *</i></b>
<a name="L2094" href="source/net/ipv4/tcp_input.c#L2094">2094</a> <b><i> *      left_out is number of segments left network, but not ACKed yet.</i></b>
<a name="L2095" href="source/net/ipv4/tcp_input.c#L2095">2095</a> <b><i> *</i></b>
<a name="L2096" href="source/net/ipv4/tcp_input.c#L2096">2096</a> <b><i> *              left_out = sacked_out + lost_out</i></b>
<a name="L2097" href="source/net/ipv4/tcp_input.c#L2097">2097</a> <b><i> *</i></b>
<a name="L2098" href="source/net/ipv4/tcp_input.c#L2098">2098</a> <b><i> *     sacked_out: Packets, which arrived to receiver out of order</i></b>
<a name="L2099" href="source/net/ipv4/tcp_input.c#L2099">2099</a> <b><i> *                 and hence not ACKed. With SACKs this number is simply</i></b>
<a name="L2100" href="source/net/ipv4/tcp_input.c#L2100">2100</a> <b><i> *                 amount of SACKed data. Even without SACKs</i></b>
<a name="L2101" href="source/net/ipv4/tcp_input.c#L2101">2101</a> <b><i> *                 it is easy to give pretty reliable estimate of this number,</i></b>
<a name="L2102" href="source/net/ipv4/tcp_input.c#L2102">2102</a> <b><i> *                 counting duplicate ACKs.</i></b>
<a name="L2103" href="source/net/ipv4/tcp_input.c#L2103">2103</a> <b><i> *</i></b>
<a name="L2104" href="source/net/ipv4/tcp_input.c#L2104">2104</a> <b><i> *       lost_out: Packets lost by network. TCP has no explicit</i></b>
<a name="L2105" href="source/net/ipv4/tcp_input.c#L2105">2105</a> <b><i> *                 "loss notification" feedback from network (for now).</i></b>
<a name="L2106" href="source/net/ipv4/tcp_input.c#L2106">2106</a> <b><i> *                 It means that this number can be only _guessed_.</i></b>
<a name="L2107" href="source/net/ipv4/tcp_input.c#L2107">2107</a> <b><i> *                 Actually, it is the heuristics to predict lossage that</i></b>
<a name="L2108" href="source/net/ipv4/tcp_input.c#L2108">2108</a> <b><i> *                 distinguishes different algorithms.</i></b>
<a name="L2109" href="source/net/ipv4/tcp_input.c#L2109">2109</a> <b><i> *</i></b>
<a name="L2110" href="source/net/ipv4/tcp_input.c#L2110">2110</a> <b><i> *      F.e. after RTO, when all the queue is considered as lost,</i></b>
<a name="L2111" href="source/net/ipv4/tcp_input.c#L2111">2111</a> <b><i> *      lost_out = packets_out and in_flight = retrans_out.</i></b>
<a name="L2112" href="source/net/ipv4/tcp_input.c#L2112">2112</a> <b><i> *</i></b>
<a name="L2113" href="source/net/ipv4/tcp_input.c#L2113">2113</a> <b><i> *              Essentially, we have now two algorithms counting</i></b>
<a name="L2114" href="source/net/ipv4/tcp_input.c#L2114">2114</a> <b><i> *              lost packets.</i></b>
<a name="L2115" href="source/net/ipv4/tcp_input.c#L2115">2115</a> <b><i> *</i></b>
<a name="L2116" href="source/net/ipv4/tcp_input.c#L2116">2116</a> <b><i> *              FACK: It is the simplest heuristics. As soon as we decided</i></b>
<a name="L2117" href="source/net/ipv4/tcp_input.c#L2117">2117</a> <b><i> *              that something is lost, we decide that _all_ not SACKed</i></b>
<a name="L2118" href="source/net/ipv4/tcp_input.c#L2118">2118</a> <b><i> *              packets until the most forward SACK are lost. I.e.</i></b>
<a name="L2119" href="source/net/ipv4/tcp_input.c#L2119">2119</a> <b><i> *              lost_out = fackets_out - sacked_out and left_out = fackets_out.</i></b>
<a name="L2120" href="source/net/ipv4/tcp_input.c#L2120">2120</a> <b><i> *              It is absolutely correct estimate, if network does not reorder</i></b>
<a name="L2121" href="source/net/ipv4/tcp_input.c#L2121">2121</a> <b><i> *              packets. And it loses any connection to reality when reordering</i></b>
<a name="L2122" href="source/net/ipv4/tcp_input.c#L2122">2122</a> <b><i> *              takes place. We use FACK by default until reordering</i></b>
<a name="L2123" href="source/net/ipv4/tcp_input.c#L2123">2123</a> <b><i> *              is suspected on the path to this destination.</i></b>
<a name="L2124" href="source/net/ipv4/tcp_input.c#L2124">2124</a> <b><i> *</i></b>
<a name="L2125" href="source/net/ipv4/tcp_input.c#L2125">2125</a> <b><i> *              NewReno: when Recovery is entered, we assume that one segment</i></b>
<a name="L2126" href="source/net/ipv4/tcp_input.c#L2126">2126</a> <b><i> *              is lost (classic Reno). While we are in Recovery and</i></b>
<a name="L2127" href="source/net/ipv4/tcp_input.c#L2127">2127</a> <b><i> *              a partial ACK arrives, we assume that one more packet</i></b>
<a name="L2128" href="source/net/ipv4/tcp_input.c#L2128">2128</a> <b><i> *              is lost (NewReno). This heuristics are the same in NewReno</i></b>
<a name="L2129" href="source/net/ipv4/tcp_input.c#L2129">2129</a> <b><i> *              and SACK.</i></b>
<a name="L2130" href="source/net/ipv4/tcp_input.c#L2130">2130</a> <b><i> *</i></b>
<a name="L2131" href="source/net/ipv4/tcp_input.c#L2131">2131</a> <b><i> *  Imagine, that's all! Forget about all this shamanism about CWND inflation</i></b>
<a name="L2132" href="source/net/ipv4/tcp_input.c#L2132">2132</a> <b><i> *  deflation etc. CWND is real congestion window, never inflated, changes</i></b>
<a name="L2133" href="source/net/ipv4/tcp_input.c#L2133">2133</a> <b><i> *  only according to classic VJ rules.</i></b>
<a name="L2134" href="source/net/ipv4/tcp_input.c#L2134">2134</a> <b><i> *</i></b>
<a name="L2135" href="source/net/ipv4/tcp_input.c#L2135">2135</a> <b><i> * Really tricky (and requiring careful tuning) part of algorithm</i></b>
<a name="L2136" href="source/net/ipv4/tcp_input.c#L2136">2136</a> <b><i> * is hidden in functions tcp_time_to_recover() and tcp_xmit_retransmit_queue().</i></b>
<a name="L2137" href="source/net/ipv4/tcp_input.c#L2137">2137</a> <b><i> * The first determines the moment _when_ we should reduce CWND and,</i></b>
<a name="L2138" href="source/net/ipv4/tcp_input.c#L2138">2138</a> <b><i> * hence, slow down forward transmission. In fact, it determines the moment</i></b>
<a name="L2139" href="source/net/ipv4/tcp_input.c#L2139">2139</a> <b><i> * when we decide that hole is caused by loss, rather than by a reorder.</i></b>
<a name="L2140" href="source/net/ipv4/tcp_input.c#L2140">2140</a> <b><i> *</i></b>
<a name="L2141" href="source/net/ipv4/tcp_input.c#L2141">2141</a> <b><i> * tcp_xmit_retransmit_queue() decides, _what_ we should retransmit to fill</i></b>
<a name="L2142" href="source/net/ipv4/tcp_input.c#L2142">2142</a> <b><i> * holes, caused by lost packets.</i></b>
<a name="L2143" href="source/net/ipv4/tcp_input.c#L2143">2143</a> <b><i> *</i></b>
<a name="L2144" href="source/net/ipv4/tcp_input.c#L2144">2144</a> <b><i> * And the most logically complicated part of algorithm is undo</i></b>
<a name="L2145" href="source/net/ipv4/tcp_input.c#L2145">2145</a> <b><i> * heuristics. We detect false retransmits due to both too early</i></b>
<a name="L2146" href="source/net/ipv4/tcp_input.c#L2146">2146</a> <b><i> * fast retransmit (reordering) and underestimated RTO, analyzing</i></b>
<a name="L2147" href="source/net/ipv4/tcp_input.c#L2147">2147</a> <b><i> * timestamps and D-SACKs. When we detect that some segments were</i></b>
<a name="L2148" href="source/net/ipv4/tcp_input.c#L2148">2148</a> <b><i> * retransmitted by mistake and CWND reduction was wrong, we undo</i></b>
<a name="L2149" href="source/net/ipv4/tcp_input.c#L2149">2149</a> <b><i> * window reduction and abort recovery phase. This logic is hidden</i></b>
<a name="L2150" href="source/net/ipv4/tcp_input.c#L2150">2150</a> <b><i> * inside several functions named tcp_try_undo_&lt;something&gt;.</i></b>
<a name="L2151" href="source/net/ipv4/tcp_input.c#L2151">2151</a> <b><i> */</i></b>
<a name="L2152" href="source/net/ipv4/tcp_input.c#L2152">2152</a> 
<a name="L2153" href="source/net/ipv4/tcp_input.c#L2153">2153</a> <b><i>/* This function decides, when we should leave Disordered state</i></b>
<a name="L2154" href="source/net/ipv4/tcp_input.c#L2154">2154</a> <b><i> * and enter Recovery phase, reducing congestion window.</i></b>
<a name="L2155" href="source/net/ipv4/tcp_input.c#L2155">2155</a> <b><i> *</i></b>
<a name="L2156" href="source/net/ipv4/tcp_input.c#L2156">2156</a> <b><i> * Main question: may we further continue forward transmission</i></b>
<a name="L2157" href="source/net/ipv4/tcp_input.c#L2157">2157</a> <b><i> * with the same cwnd?</i></b>
<a name="L2158" href="source/net/ipv4/tcp_input.c#L2158">2158</a> <b><i> */</i></b>
<a name="L2159" href="source/net/ipv4/tcp_input.c#L2159">2159</a> static <a href="ident?i=bool">bool</a> <a href="ident?i=tcp_time_to_recover">tcp_time_to_recover</a>(struct <a href="ident?i=sock">sock</a> *sk, int <a href="ident?i=flag">flag</a>)
<a name="L2160" href="source/net/ipv4/tcp_input.c#L2160">2160</a> {
<a name="L2161" href="source/net/ipv4/tcp_input.c#L2161">2161</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L2162" href="source/net/ipv4/tcp_input.c#L2162">2162</a>         <a href="ident?i=__u32">__u32</a> packets_out;
<a name="L2163" href="source/net/ipv4/tcp_input.c#L2163">2163</a> 
<a name="L2164" href="source/net/ipv4/tcp_input.c#L2164">2164</a>         <b><i>/* Trick#1: The loss is proven. */</i></b>
<a name="L2165" href="source/net/ipv4/tcp_input.c#L2165">2165</a>         if (<a href="ident?i=tp">tp</a>-&gt;lost_out)
<a name="L2166" href="source/net/ipv4/tcp_input.c#L2166">2166</a>                 return <a href="ident?i=true">true</a>;
<a name="L2167" href="source/net/ipv4/tcp_input.c#L2167">2167</a> 
<a name="L2168" href="source/net/ipv4/tcp_input.c#L2168">2168</a>         <b><i>/* Not-A-Trick#2 : Classic rule... */</i></b>
<a name="L2169" href="source/net/ipv4/tcp_input.c#L2169">2169</a>         if (<a href="ident?i=tcp_dupack_heuristics">tcp_dupack_heuristics</a>(<a href="ident?i=tp">tp</a>) &gt; <a href="ident?i=tp">tp</a>-&gt;reordering)
<a name="L2170" href="source/net/ipv4/tcp_input.c#L2170">2170</a>                 return <a href="ident?i=true">true</a>;
<a name="L2171" href="source/net/ipv4/tcp_input.c#L2171">2171</a> 
<a name="L2172" href="source/net/ipv4/tcp_input.c#L2172">2172</a>         <b><i>/* Trick#4: It is still not OK... But will it be useful to delay</i></b>
<a name="L2173" href="source/net/ipv4/tcp_input.c#L2173">2173</a> <b><i>         * recovery more?</i></b>
<a name="L2174" href="source/net/ipv4/tcp_input.c#L2174">2174</a> <b><i>         */</i></b>
<a name="L2175" href="source/net/ipv4/tcp_input.c#L2175">2175</a>         packets_out = <a href="ident?i=tp">tp</a>-&gt;packets_out;
<a name="L2176" href="source/net/ipv4/tcp_input.c#L2176">2176</a>         if (packets_out &lt;= <a href="ident?i=tp">tp</a>-&gt;reordering &amp;&amp;
<a name="L2177" href="source/net/ipv4/tcp_input.c#L2177">2177</a>             <a href="ident?i=tp">tp</a>-&gt;sacked_out &gt;= <a href="ident?i=max_t">max_t</a>(<a href="ident?i=__u32">__u32</a>, packets_out/2, <a href="ident?i=sysctl_tcp_reordering">sysctl_tcp_reordering</a>) &amp;&amp;
<a name="L2178" href="source/net/ipv4/tcp_input.c#L2178">2178</a>             !<a href="ident?i=tcp_may_send_now">tcp_may_send_now</a>(sk)) {
<a name="L2179" href="source/net/ipv4/tcp_input.c#L2179">2179</a>                 <b><i>/* We have nothing to send. This connection is limited</i></b>
<a name="L2180" href="source/net/ipv4/tcp_input.c#L2180">2180</a> <b><i>                 * either by receiver window or by application.</i></b>
<a name="L2181" href="source/net/ipv4/tcp_input.c#L2181">2181</a> <b><i>                 */</i></b>
<a name="L2182" href="source/net/ipv4/tcp_input.c#L2182">2182</a>                 return <a href="ident?i=true">true</a>;
<a name="L2183" href="source/net/ipv4/tcp_input.c#L2183">2183</a>         }
<a name="L2184" href="source/net/ipv4/tcp_input.c#L2184">2184</a> 
<a name="L2185" href="source/net/ipv4/tcp_input.c#L2185">2185</a>         <b><i>/* If a thin stream is detected, retransmit after first</i></b>
<a name="L2186" href="source/net/ipv4/tcp_input.c#L2186">2186</a> <b><i>         * received dupack. Employ only if SACK is supported in order</i></b>
<a name="L2187" href="source/net/ipv4/tcp_input.c#L2187">2187</a> <b><i>         * to avoid possible corner-case series of spurious retransmissions</i></b>
<a name="L2188" href="source/net/ipv4/tcp_input.c#L2188">2188</a> <b><i>         * Use only if there are no unsent data.</i></b>
<a name="L2189" href="source/net/ipv4/tcp_input.c#L2189">2189</a> <b><i>         */</i></b>
<a name="L2190" href="source/net/ipv4/tcp_input.c#L2190">2190</a>         if ((<a href="ident?i=tp">tp</a>-&gt;thin_dupack || <a href="ident?i=sysctl_tcp_thin_dupack">sysctl_tcp_thin_dupack</a>) &amp;&amp;
<a name="L2191" href="source/net/ipv4/tcp_input.c#L2191">2191</a>             <a href="ident?i=tcp_stream_is_thin">tcp_stream_is_thin</a>(<a href="ident?i=tp">tp</a>) &amp;&amp; <a href="ident?i=tcp_dupack_heuristics">tcp_dupack_heuristics</a>(<a href="ident?i=tp">tp</a>) &gt; 1 &amp;&amp;
<a name="L2192" href="source/net/ipv4/tcp_input.c#L2192">2192</a>             <a href="ident?i=tcp_is_sack">tcp_is_sack</a>(<a href="ident?i=tp">tp</a>) &amp;&amp; !<a href="ident?i=tcp_send_head">tcp_send_head</a>(sk))
<a name="L2193" href="source/net/ipv4/tcp_input.c#L2193">2193</a>                 return <a href="ident?i=true">true</a>;
<a name="L2194" href="source/net/ipv4/tcp_input.c#L2194">2194</a> 
<a name="L2195" href="source/net/ipv4/tcp_input.c#L2195">2195</a>         <b><i>/* Trick#6: TCP early retransmit, per RFC5827.  To avoid spurious</i></b>
<a name="L2196" href="source/net/ipv4/tcp_input.c#L2196">2196</a> <b><i>         * retransmissions due to small network reorderings, we implement</i></b>
<a name="L2197" href="source/net/ipv4/tcp_input.c#L2197">2197</a> <b><i>         * Mitigation A.3 in the RFC and delay the retransmission for a short</i></b>
<a name="L2198" href="source/net/ipv4/tcp_input.c#L2198">2198</a> <b><i>         * interval if appropriate.</i></b>
<a name="L2199" href="source/net/ipv4/tcp_input.c#L2199">2199</a> <b><i>         */</i></b>
<a name="L2200" href="source/net/ipv4/tcp_input.c#L2200">2200</a>         if (<a href="ident?i=tp">tp</a>-&gt;do_early_retrans &amp;&amp; !<a href="ident?i=tp">tp</a>-&gt;retrans_out &amp;&amp; <a href="ident?i=tp">tp</a>-&gt;sacked_out &amp;&amp;
<a name="L2201" href="source/net/ipv4/tcp_input.c#L2201">2201</a>             (<a href="ident?i=tp">tp</a>-&gt;packets_out &gt;= (<a href="ident?i=tp">tp</a>-&gt;sacked_out + 1) &amp;&amp; <a href="ident?i=tp">tp</a>-&gt;packets_out &lt; 4) &amp;&amp;
<a name="L2202" href="source/net/ipv4/tcp_input.c#L2202">2202</a>             !<a href="ident?i=tcp_may_send_now">tcp_may_send_now</a>(sk))
<a name="L2203" href="source/net/ipv4/tcp_input.c#L2203">2203</a>                 return !<a href="ident?i=tcp_pause_early_retransmit">tcp_pause_early_retransmit</a>(sk, <a href="ident?i=flag">flag</a>);
<a name="L2204" href="source/net/ipv4/tcp_input.c#L2204">2204</a> 
<a name="L2205" href="source/net/ipv4/tcp_input.c#L2205">2205</a>         return <a href="ident?i=false">false</a>;
<a name="L2206" href="source/net/ipv4/tcp_input.c#L2206">2206</a> }
<a name="L2207" href="source/net/ipv4/tcp_input.c#L2207">2207</a> 
<a name="L2208" href="source/net/ipv4/tcp_input.c#L2208">2208</a> <b><i>/* Detect loss in event "A" above by marking head of queue up as lost.</i></b>
<a name="L2209" href="source/net/ipv4/tcp_input.c#L2209">2209</a> <b><i> * For FACK or non-SACK(Reno) senders, the first "packets" number of segments</i></b>
<a name="L2210" href="source/net/ipv4/tcp_input.c#L2210">2210</a> <b><i> * are considered lost. For RFC3517 SACK, a segment is considered lost if it</i></b>
<a name="L2211" href="source/net/ipv4/tcp_input.c#L2211">2211</a> <b><i> * has at least tp-&gt;reordering SACKed seqments above it; "packets" refers to</i></b>
<a name="L2212" href="source/net/ipv4/tcp_input.c#L2212">2212</a> <b><i> * the maximum SACKed segments to pass before reaching this limit.</i></b>
<a name="L2213" href="source/net/ipv4/tcp_input.c#L2213">2213</a> <b><i> */</i></b>
<a name="L2214" href="source/net/ipv4/tcp_input.c#L2214">2214</a> static void <a href="ident?i=tcp_mark_head_lost">tcp_mark_head_lost</a>(struct <a href="ident?i=sock">sock</a> *sk, int packets, int mark_head)
<a name="L2215" href="source/net/ipv4/tcp_input.c#L2215">2215</a> {
<a name="L2216" href="source/net/ipv4/tcp_input.c#L2216">2216</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L2217" href="source/net/ipv4/tcp_input.c#L2217">2217</a>         struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>;
<a name="L2218" href="source/net/ipv4/tcp_input.c#L2218">2218</a>         int cnt, oldcnt;
<a name="L2219" href="source/net/ipv4/tcp_input.c#L2219">2219</a>         int <a href="ident?i=err">err</a>;
<a name="L2220" href="source/net/ipv4/tcp_input.c#L2220">2220</a>         unsigned int mss;
<a name="L2221" href="source/net/ipv4/tcp_input.c#L2221">2221</a>         <b><i>/* Use SACK to deduce losses of new sequences sent during recovery */</i></b>
<a name="L2222" href="source/net/ipv4/tcp_input.c#L2222">2222</a>         const <a href="ident?i=u32">u32</a> loss_high = <a href="ident?i=tcp_is_sack">tcp_is_sack</a>(<a href="ident?i=tp">tp</a>) ?  <a href="ident?i=tp">tp</a>-&gt;snd_nxt : <a href="ident?i=tp">tp</a>-&gt;high_seq;
<a name="L2223" href="source/net/ipv4/tcp_input.c#L2223">2223</a> 
<a name="L2224" href="source/net/ipv4/tcp_input.c#L2224">2224</a>         <a href="ident?i=WARN_ON">WARN_ON</a>(packets &gt; <a href="ident?i=tp">tp</a>-&gt;packets_out);
<a name="L2225" href="source/net/ipv4/tcp_input.c#L2225">2225</a>         if (<a href="ident?i=tp">tp</a>-&gt;lost_skb_hint) {
<a name="L2226" href="source/net/ipv4/tcp_input.c#L2226">2226</a>                 <a href="ident?i=skb">skb</a> = <a href="ident?i=tp">tp</a>-&gt;lost_skb_hint;
<a name="L2227" href="source/net/ipv4/tcp_input.c#L2227">2227</a>                 cnt = <a href="ident?i=tp">tp</a>-&gt;lost_cnt_hint;
<a name="L2228" href="source/net/ipv4/tcp_input.c#L2228">2228</a>                 <b><i>/* Head already handled? */</i></b>
<a name="L2229" href="source/net/ipv4/tcp_input.c#L2229">2229</a>                 if (mark_head &amp;&amp; <a href="ident?i=skb">skb</a> != <a href="ident?i=tcp_write_queue_head">tcp_write_queue_head</a>(sk))
<a name="L2230" href="source/net/ipv4/tcp_input.c#L2230">2230</a>                         return;
<a name="L2231" href="source/net/ipv4/tcp_input.c#L2231">2231</a>         } else {
<a name="L2232" href="source/net/ipv4/tcp_input.c#L2232">2232</a>                 <a href="ident?i=skb">skb</a> = <a href="ident?i=tcp_write_queue_head">tcp_write_queue_head</a>(sk);
<a name="L2233" href="source/net/ipv4/tcp_input.c#L2233">2233</a>                 cnt = 0;
<a name="L2234" href="source/net/ipv4/tcp_input.c#L2234">2234</a>         }
<a name="L2235" href="source/net/ipv4/tcp_input.c#L2235">2235</a> 
<a name="L2236" href="source/net/ipv4/tcp_input.c#L2236">2236</a>         <a href="ident?i=tcp_for_write_queue_from">tcp_for_write_queue_from</a>(<a href="ident?i=skb">skb</a>, sk) {
<a name="L2237" href="source/net/ipv4/tcp_input.c#L2237">2237</a>                 if (<a href="ident?i=skb">skb</a> == <a href="ident?i=tcp_send_head">tcp_send_head</a>(sk))
<a name="L2238" href="source/net/ipv4/tcp_input.c#L2238">2238</a>                         break;
<a name="L2239" href="source/net/ipv4/tcp_input.c#L2239">2239</a>                 <b><i>/* TODO: do this better */</i></b>
<a name="L2240" href="source/net/ipv4/tcp_input.c#L2240">2240</a>                 <b><i>/* this is not the most efficient way to do this... */</i></b>
<a name="L2241" href="source/net/ipv4/tcp_input.c#L2241">2241</a>                 <a href="ident?i=tp">tp</a>-&gt;lost_skb_hint = <a href="ident?i=skb">skb</a>;
<a name="L2242" href="source/net/ipv4/tcp_input.c#L2242">2242</a>                 <a href="ident?i=tp">tp</a>-&gt;lost_cnt_hint = cnt;
<a name="L2243" href="source/net/ipv4/tcp_input.c#L2243">2243</a> 
<a name="L2244" href="source/net/ipv4/tcp_input.c#L2244">2244</a>                 if (<a href="ident?i=after">after</a>(<a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;end_seq, loss_high))
<a name="L2245" href="source/net/ipv4/tcp_input.c#L2245">2245</a>                         break;
<a name="L2246" href="source/net/ipv4/tcp_input.c#L2246">2246</a> 
<a name="L2247" href="source/net/ipv4/tcp_input.c#L2247">2247</a>                 oldcnt = cnt;
<a name="L2248" href="source/net/ipv4/tcp_input.c#L2248">2248</a>                 if (<a href="ident?i=tcp_is_fack">tcp_is_fack</a>(<a href="ident?i=tp">tp</a>) || <a href="ident?i=tcp_is_reno">tcp_is_reno</a>(<a href="ident?i=tp">tp</a>) ||
<a name="L2249" href="source/net/ipv4/tcp_input.c#L2249">2249</a>                     (<a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;sacked &amp; <a href="ident?i=TCPCB_SACKED_ACKED">TCPCB_SACKED_ACKED</a>))
<a name="L2250" href="source/net/ipv4/tcp_input.c#L2250">2250</a>                         cnt += <a href="ident?i=tcp_skb_pcount">tcp_skb_pcount</a>(<a href="ident?i=skb">skb</a>);
<a name="L2251" href="source/net/ipv4/tcp_input.c#L2251">2251</a> 
<a name="L2252" href="source/net/ipv4/tcp_input.c#L2252">2252</a>                 if (cnt &gt; packets) {
<a name="L2253" href="source/net/ipv4/tcp_input.c#L2253">2253</a>                         if ((<a href="ident?i=tcp_is_sack">tcp_is_sack</a>(<a href="ident?i=tp">tp</a>) &amp;&amp; !<a href="ident?i=tcp_is_fack">tcp_is_fack</a>(<a href="ident?i=tp">tp</a>)) ||
<a name="L2254" href="source/net/ipv4/tcp_input.c#L2254">2254</a>                             (<a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;sacked &amp; <a href="ident?i=TCPCB_SACKED_ACKED">TCPCB_SACKED_ACKED</a>) ||
<a name="L2255" href="source/net/ipv4/tcp_input.c#L2255">2255</a>                             (oldcnt &gt;= packets))
<a name="L2256" href="source/net/ipv4/tcp_input.c#L2256">2256</a>                                 break;
<a name="L2257" href="source/net/ipv4/tcp_input.c#L2257">2257</a> 
<a name="L2258" href="source/net/ipv4/tcp_input.c#L2258">2258</a>                         mss = <a href="ident?i=skb_shinfo">skb_shinfo</a>(<a href="ident?i=skb">skb</a>)-&gt;gso_size;
<a name="L2259" href="source/net/ipv4/tcp_input.c#L2259">2259</a>                         <a href="ident?i=err">err</a> = <a href="ident?i=tcp_fragment">tcp_fragment</a>(sk, <a href="ident?i=skb">skb</a>, (packets - oldcnt) * mss,
<a name="L2260" href="source/net/ipv4/tcp_input.c#L2260">2260</a>                                            mss, <a href="ident?i=GFP_ATOMIC">GFP_ATOMIC</a>);
<a name="L2261" href="source/net/ipv4/tcp_input.c#L2261">2261</a>                         if (<a href="ident?i=err">err</a> &lt; 0)
<a name="L2262" href="source/net/ipv4/tcp_input.c#L2262">2262</a>                                 break;
<a name="L2263" href="source/net/ipv4/tcp_input.c#L2263">2263</a>                         cnt = packets;
<a name="L2264" href="source/net/ipv4/tcp_input.c#L2264">2264</a>                 }
<a name="L2265" href="source/net/ipv4/tcp_input.c#L2265">2265</a> 
<a name="L2266" href="source/net/ipv4/tcp_input.c#L2266">2266</a>                 <a href="ident?i=tcp_skb_mark_lost">tcp_skb_mark_lost</a>(<a href="ident?i=tp">tp</a>, <a href="ident?i=skb">skb</a>);
<a name="L2267" href="source/net/ipv4/tcp_input.c#L2267">2267</a> 
<a name="L2268" href="source/net/ipv4/tcp_input.c#L2268">2268</a>                 if (mark_head)
<a name="L2269" href="source/net/ipv4/tcp_input.c#L2269">2269</a>                         break;
<a name="L2270" href="source/net/ipv4/tcp_input.c#L2270">2270</a>         }
<a name="L2271" href="source/net/ipv4/tcp_input.c#L2271">2271</a>         <a href="ident?i=tcp_verify_left_out">tcp_verify_left_out</a>(<a href="ident?i=tp">tp</a>);
<a name="L2272" href="source/net/ipv4/tcp_input.c#L2272">2272</a> }
<a name="L2273" href="source/net/ipv4/tcp_input.c#L2273">2273</a> 
<a name="L2274" href="source/net/ipv4/tcp_input.c#L2274">2274</a> <b><i>/* Account newly detected lost packet(s) */</i></b>
<a name="L2275" href="source/net/ipv4/tcp_input.c#L2275">2275</a> 
<a name="L2276" href="source/net/ipv4/tcp_input.c#L2276">2276</a> static void <a href="ident?i=tcp_update_scoreboard">tcp_update_scoreboard</a>(struct <a href="ident?i=sock">sock</a> *sk, int fast_rexmit)
<a name="L2277" href="source/net/ipv4/tcp_input.c#L2277">2277</a> {
<a name="L2278" href="source/net/ipv4/tcp_input.c#L2278">2278</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L2279" href="source/net/ipv4/tcp_input.c#L2279">2279</a> 
<a name="L2280" href="source/net/ipv4/tcp_input.c#L2280">2280</a>         if (<a href="ident?i=tcp_is_reno">tcp_is_reno</a>(<a href="ident?i=tp">tp</a>)) {
<a name="L2281" href="source/net/ipv4/tcp_input.c#L2281">2281</a>                 <a href="ident?i=tcp_mark_head_lost">tcp_mark_head_lost</a>(sk, 1, 1);
<a name="L2282" href="source/net/ipv4/tcp_input.c#L2282">2282</a>         } else if (<a href="ident?i=tcp_is_fack">tcp_is_fack</a>(<a href="ident?i=tp">tp</a>)) {
<a name="L2283" href="source/net/ipv4/tcp_input.c#L2283">2283</a>                 int lost = <a href="ident?i=tp">tp</a>-&gt;fackets_out - <a href="ident?i=tp">tp</a>-&gt;reordering;
<a name="L2284" href="source/net/ipv4/tcp_input.c#L2284">2284</a>                 if (lost &lt;= 0)
<a name="L2285" href="source/net/ipv4/tcp_input.c#L2285">2285</a>                         lost = 1;
<a name="L2286" href="source/net/ipv4/tcp_input.c#L2286">2286</a>                 <a href="ident?i=tcp_mark_head_lost">tcp_mark_head_lost</a>(sk, lost, 0);
<a name="L2287" href="source/net/ipv4/tcp_input.c#L2287">2287</a>         } else {
<a name="L2288" href="source/net/ipv4/tcp_input.c#L2288">2288</a>                 int sacked_upto = <a href="ident?i=tp">tp</a>-&gt;sacked_out - <a href="ident?i=tp">tp</a>-&gt;reordering;
<a name="L2289" href="source/net/ipv4/tcp_input.c#L2289">2289</a>                 if (sacked_upto &gt;= 0)
<a name="L2290" href="source/net/ipv4/tcp_input.c#L2290">2290</a>                         <a href="ident?i=tcp_mark_head_lost">tcp_mark_head_lost</a>(sk, sacked_upto, 0);
<a name="L2291" href="source/net/ipv4/tcp_input.c#L2291">2291</a>                 else if (fast_rexmit)
<a name="L2292" href="source/net/ipv4/tcp_input.c#L2292">2292</a>                         <a href="ident?i=tcp_mark_head_lost">tcp_mark_head_lost</a>(sk, 1, 1);
<a name="L2293" href="source/net/ipv4/tcp_input.c#L2293">2293</a>         }
<a name="L2294" href="source/net/ipv4/tcp_input.c#L2294">2294</a> }
<a name="L2295" href="source/net/ipv4/tcp_input.c#L2295">2295</a> 
<a name="L2296" href="source/net/ipv4/tcp_input.c#L2296">2296</a> <b><i>/* CWND moderation, preventing bursts due to too big ACKs</i></b>
<a name="L2297" href="source/net/ipv4/tcp_input.c#L2297">2297</a> <b><i> * in dubious situations.</i></b>
<a name="L2298" href="source/net/ipv4/tcp_input.c#L2298">2298</a> <b><i> */</i></b>
<a name="L2299" href="source/net/ipv4/tcp_input.c#L2299">2299</a> static inline void <a href="ident?i=tcp_moderate_cwnd">tcp_moderate_cwnd</a>(struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a>)
<a name="L2300" href="source/net/ipv4/tcp_input.c#L2300">2300</a> {
<a name="L2301" href="source/net/ipv4/tcp_input.c#L2301">2301</a>         <a href="ident?i=tp">tp</a>-&gt;snd_cwnd = <a href="ident?i=min">min</a>(<a href="ident?i=tp">tp</a>-&gt;snd_cwnd,
<a name="L2302" href="source/net/ipv4/tcp_input.c#L2302">2302</a>                            <a href="ident?i=tcp_packets_in_flight">tcp_packets_in_flight</a>(<a href="ident?i=tp">tp</a>) + <a href="ident?i=tcp_max_burst">tcp_max_burst</a>(<a href="ident?i=tp">tp</a>));
<a name="L2303" href="source/net/ipv4/tcp_input.c#L2303">2303</a>         <a href="ident?i=tp">tp</a>-&gt;snd_cwnd_stamp = <a href="ident?i=tcp_time_stamp">tcp_time_stamp</a>;
<a name="L2304" href="source/net/ipv4/tcp_input.c#L2304">2304</a> }
<a name="L2305" href="source/net/ipv4/tcp_input.c#L2305">2305</a> 
<a name="L2306" href="source/net/ipv4/tcp_input.c#L2306">2306</a> <b><i>/* Nothing was retransmitted or returned timestamp is less</i></b>
<a name="L2307" href="source/net/ipv4/tcp_input.c#L2307">2307</a> <b><i> * than timestamp of the first retransmission.</i></b>
<a name="L2308" href="source/net/ipv4/tcp_input.c#L2308">2308</a> <b><i> */</i></b>
<a name="L2309" href="source/net/ipv4/tcp_input.c#L2309">2309</a> static inline <a href="ident?i=bool">bool</a> <a href="ident?i=tcp_packet_delayed">tcp_packet_delayed</a>(const struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a>)
<a name="L2310" href="source/net/ipv4/tcp_input.c#L2310">2310</a> {
<a name="L2311" href="source/net/ipv4/tcp_input.c#L2311">2311</a>         return !<a href="ident?i=tp">tp</a>-&gt;retrans_stamp ||
<a name="L2312" href="source/net/ipv4/tcp_input.c#L2312">2312</a>                 (<a href="ident?i=tp">tp</a>-&gt;rx_opt.saw_tstamp &amp;&amp; <a href="ident?i=tp">tp</a>-&gt;rx_opt.rcv_tsecr &amp;&amp;
<a name="L2313" href="source/net/ipv4/tcp_input.c#L2313">2313</a>                  <a href="ident?i=before">before</a>(<a href="ident?i=tp">tp</a>-&gt;rx_opt.rcv_tsecr, <a href="ident?i=tp">tp</a>-&gt;retrans_stamp));
<a name="L2314" href="source/net/ipv4/tcp_input.c#L2314">2314</a> }
<a name="L2315" href="source/net/ipv4/tcp_input.c#L2315">2315</a> 
<a name="L2316" href="source/net/ipv4/tcp_input.c#L2316">2316</a> <b><i>/* Undo procedures. */</i></b>
<a name="L2317" href="source/net/ipv4/tcp_input.c#L2317">2317</a> 
<a name="L2318" href="source/net/ipv4/tcp_input.c#L2318">2318</a> <b><i>/* We can clear retrans_stamp when there are no retransmissions in the</i></b>
<a name="L2319" href="source/net/ipv4/tcp_input.c#L2319">2319</a> <b><i> * window. It would seem that it is trivially available for us in</i></b>
<a name="L2320" href="source/net/ipv4/tcp_input.c#L2320">2320</a> <b><i> * tp-&gt;retrans_out, however, that kind of assumptions doesn't consider</i></b>
<a name="L2321" href="source/net/ipv4/tcp_input.c#L2321">2321</a> <b><i> * what will happen if errors occur when sending retransmission for the</i></b>
<a name="L2322" href="source/net/ipv4/tcp_input.c#L2322">2322</a> <b><i> * second time. ...It could the that such segment has only</i></b>
<a name="L2323" href="source/net/ipv4/tcp_input.c#L2323">2323</a> <b><i> * TCPCB_EVER_RETRANS set at the present time. It seems that checking</i></b>
<a name="L2324" href="source/net/ipv4/tcp_input.c#L2324">2324</a> <b><i> * the head skb is enough except for some reneging corner cases that</i></b>
<a name="L2325" href="source/net/ipv4/tcp_input.c#L2325">2325</a> <b><i> * are not worth the effort.</i></b>
<a name="L2326" href="source/net/ipv4/tcp_input.c#L2326">2326</a> <b><i> *</i></b>
<a name="L2327" href="source/net/ipv4/tcp_input.c#L2327">2327</a> <b><i> * Main reason for all this complexity is the fact that connection dying</i></b>
<a name="L2328" href="source/net/ipv4/tcp_input.c#L2328">2328</a> <b><i> * time now depends on the validity of the retrans_stamp, in particular,</i></b>
<a name="L2329" href="source/net/ipv4/tcp_input.c#L2329">2329</a> <b><i> * that successive retransmissions of a segment must not advance</i></b>
<a name="L2330" href="source/net/ipv4/tcp_input.c#L2330">2330</a> <b><i> * retrans_stamp under any conditions.</i></b>
<a name="L2331" href="source/net/ipv4/tcp_input.c#L2331">2331</a> <b><i> */</i></b>
<a name="L2332" href="source/net/ipv4/tcp_input.c#L2332">2332</a> static <a href="ident?i=bool">bool</a> <a href="ident?i=tcp_any_retrans_done">tcp_any_retrans_done</a>(const struct <a href="ident?i=sock">sock</a> *sk)
<a name="L2333" href="source/net/ipv4/tcp_input.c#L2333">2333</a> {
<a name="L2334" href="source/net/ipv4/tcp_input.c#L2334">2334</a>         const struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L2335" href="source/net/ipv4/tcp_input.c#L2335">2335</a>         struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>;
<a name="L2336" href="source/net/ipv4/tcp_input.c#L2336">2336</a> 
<a name="L2337" href="source/net/ipv4/tcp_input.c#L2337">2337</a>         if (<a href="ident?i=tp">tp</a>-&gt;retrans_out)
<a name="L2338" href="source/net/ipv4/tcp_input.c#L2338">2338</a>                 return <a href="ident?i=true">true</a>;
<a name="L2339" href="source/net/ipv4/tcp_input.c#L2339">2339</a> 
<a name="L2340" href="source/net/ipv4/tcp_input.c#L2340">2340</a>         <a href="ident?i=skb">skb</a> = <a href="ident?i=tcp_write_queue_head">tcp_write_queue_head</a>(sk);
<a name="L2341" href="source/net/ipv4/tcp_input.c#L2341">2341</a>         if (<a href="ident?i=unlikely">unlikely</a>(<a href="ident?i=skb">skb</a> &amp;&amp; <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;sacked &amp; <a href="ident?i=TCPCB_EVER_RETRANS">TCPCB_EVER_RETRANS</a>))
<a name="L2342" href="source/net/ipv4/tcp_input.c#L2342">2342</a>                 return <a href="ident?i=true">true</a>;
<a name="L2343" href="source/net/ipv4/tcp_input.c#L2343">2343</a> 
<a name="L2344" href="source/net/ipv4/tcp_input.c#L2344">2344</a>         return <a href="ident?i=false">false</a>;
<a name="L2345" href="source/net/ipv4/tcp_input.c#L2345">2345</a> }
<a name="L2346" href="source/net/ipv4/tcp_input.c#L2346">2346</a> 
<a name="L2347" href="source/net/ipv4/tcp_input.c#L2347">2347</a> #if <a href="ident?i=FASTRETRANS_DEBUG">FASTRETRANS_DEBUG</a> &gt; 1
<a name="L2348" href="source/net/ipv4/tcp_input.c#L2348">2348</a> static void <a href="ident?i=DBGUNDO">DBGUNDO</a>(struct <a href="ident?i=sock">sock</a> *sk, const char *<a href="ident?i=msg">msg</a>)
<a name="L2349" href="source/net/ipv4/tcp_input.c#L2349">2349</a> {
<a name="L2350" href="source/net/ipv4/tcp_input.c#L2350">2350</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L2351" href="source/net/ipv4/tcp_input.c#L2351">2351</a>         struct <a href="ident?i=inet_sock">inet_sock</a> *inet = <a href="ident?i=inet_sk">inet_sk</a>(sk);
<a name="L2352" href="source/net/ipv4/tcp_input.c#L2352">2352</a> 
<a name="L2353" href="source/net/ipv4/tcp_input.c#L2353">2353</a>         if (sk-&gt;<a href="ident?i=sk_family">sk_family</a> == <a href="ident?i=AF_INET">AF_INET</a>) {
<a name="L2354" href="source/net/ipv4/tcp_input.c#L2354">2354</a>                 <a href="ident?i=pr_debug">pr_debug</a>(<i>"Undo %s %pI4/%u c%u l%u ss%u/%u p%u\n"</i>,
<a name="L2355" href="source/net/ipv4/tcp_input.c#L2355">2355</a>                          <a href="ident?i=msg">msg</a>,
<a name="L2356" href="source/net/ipv4/tcp_input.c#L2356">2356</a>                          &amp;inet-&gt;<a href="ident?i=inet_daddr">inet_daddr</a>, <a href="ident?i=ntohs">ntohs</a>(inet-&gt;<a href="ident?i=inet_dport">inet_dport</a>),
<a name="L2357" href="source/net/ipv4/tcp_input.c#L2357">2357</a>                          <a href="ident?i=tp">tp</a>-&gt;snd_cwnd, <a href="ident?i=tcp_left_out">tcp_left_out</a>(<a href="ident?i=tp">tp</a>),
<a name="L2358" href="source/net/ipv4/tcp_input.c#L2358">2358</a>                          <a href="ident?i=tp">tp</a>-&gt;snd_ssthresh, <a href="ident?i=tp">tp</a>-&gt;prior_ssthresh,
<a name="L2359" href="source/net/ipv4/tcp_input.c#L2359">2359</a>                          <a href="ident?i=tp">tp</a>-&gt;packets_out);
<a name="L2360" href="source/net/ipv4/tcp_input.c#L2360">2360</a>         }
<a name="L2361" href="source/net/ipv4/tcp_input.c#L2361">2361</a> #if <a href="ident?i=IS_ENABLED">IS_ENABLED</a>(CONFIG_IPV6)
<a name="L2362" href="source/net/ipv4/tcp_input.c#L2362">2362</a>         else if (sk-&gt;<a href="ident?i=sk_family">sk_family</a> == <a href="ident?i=AF_INET6">AF_INET6</a>) {
<a name="L2363" href="source/net/ipv4/tcp_input.c#L2363">2363</a>                 struct <a href="ident?i=ipv6_pinfo">ipv6_pinfo</a> *np = <a href="ident?i=inet6_sk">inet6_sk</a>(sk);
<a name="L2364" href="source/net/ipv4/tcp_input.c#L2364">2364</a>                 <a href="ident?i=pr_debug">pr_debug</a>(<i>"Undo %s %pI6/%u c%u l%u ss%u/%u p%u\n"</i>,
<a name="L2365" href="source/net/ipv4/tcp_input.c#L2365">2365</a>                          <a href="ident?i=msg">msg</a>,
<a name="L2366" href="source/net/ipv4/tcp_input.c#L2366">2366</a>                          &amp;np-&gt;<a href="ident?i=daddr">daddr</a>, <a href="ident?i=ntohs">ntohs</a>(inet-&gt;<a href="ident?i=inet_dport">inet_dport</a>),
<a name="L2367" href="source/net/ipv4/tcp_input.c#L2367">2367</a>                          <a href="ident?i=tp">tp</a>-&gt;snd_cwnd, <a href="ident?i=tcp_left_out">tcp_left_out</a>(<a href="ident?i=tp">tp</a>),
<a name="L2368" href="source/net/ipv4/tcp_input.c#L2368">2368</a>                          <a href="ident?i=tp">tp</a>-&gt;snd_ssthresh, <a href="ident?i=tp">tp</a>-&gt;prior_ssthresh,
<a name="L2369" href="source/net/ipv4/tcp_input.c#L2369">2369</a>                          <a href="ident?i=tp">tp</a>-&gt;packets_out);
<a name="L2370" href="source/net/ipv4/tcp_input.c#L2370">2370</a>         }
<a name="L2371" href="source/net/ipv4/tcp_input.c#L2371">2371</a> #endif
<a name="L2372" href="source/net/ipv4/tcp_input.c#L2372">2372</a> }
<a name="L2373" href="source/net/ipv4/tcp_input.c#L2373">2373</a> #else
<a name="L2374" href="source/net/ipv4/tcp_input.c#L2374">2374</a> #define <a href="ident?i=DBGUNDO">DBGUNDO</a>(<a href="ident?i=x">x</a>...) do { } while (0)
<a name="L2375" href="source/net/ipv4/tcp_input.c#L2375">2375</a> #endif
<a name="L2376" href="source/net/ipv4/tcp_input.c#L2376">2376</a> 
<a name="L2377" href="source/net/ipv4/tcp_input.c#L2377">2377</a> static void <a href="ident?i=tcp_undo_cwnd_reduction">tcp_undo_cwnd_reduction</a>(struct <a href="ident?i=sock">sock</a> *sk, <a href="ident?i=bool">bool</a> unmark_loss)
<a name="L2378" href="source/net/ipv4/tcp_input.c#L2378">2378</a> {
<a name="L2379" href="source/net/ipv4/tcp_input.c#L2379">2379</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L2380" href="source/net/ipv4/tcp_input.c#L2380">2380</a> 
<a name="L2381" href="source/net/ipv4/tcp_input.c#L2381">2381</a>         if (unmark_loss) {
<a name="L2382" href="source/net/ipv4/tcp_input.c#L2382">2382</a>                 struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>;
<a name="L2383" href="source/net/ipv4/tcp_input.c#L2383">2383</a> 
<a name="L2384" href="source/net/ipv4/tcp_input.c#L2384">2384</a>                 <a href="ident?i=tcp_for_write_queue">tcp_for_write_queue</a>(<a href="ident?i=skb">skb</a>, sk) {
<a name="L2385" href="source/net/ipv4/tcp_input.c#L2385">2385</a>                         if (<a href="ident?i=skb">skb</a> == <a href="ident?i=tcp_send_head">tcp_send_head</a>(sk))
<a name="L2386" href="source/net/ipv4/tcp_input.c#L2386">2386</a>                                 break;
<a name="L2387" href="source/net/ipv4/tcp_input.c#L2387">2387</a>                         <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;sacked &amp;= ~TCPCB_LOST;
<a name="L2388" href="source/net/ipv4/tcp_input.c#L2388">2388</a>                 }
<a name="L2389" href="source/net/ipv4/tcp_input.c#L2389">2389</a>                 <a href="ident?i=tp">tp</a>-&gt;lost_out = 0;
<a name="L2390" href="source/net/ipv4/tcp_input.c#L2390">2390</a>                 <a href="ident?i=tcp_clear_all_retrans_hints">tcp_clear_all_retrans_hints</a>(<a href="ident?i=tp">tp</a>);
<a name="L2391" href="source/net/ipv4/tcp_input.c#L2391">2391</a>         }
<a name="L2392" href="source/net/ipv4/tcp_input.c#L2392">2392</a> 
<a name="L2393" href="source/net/ipv4/tcp_input.c#L2393">2393</a>         if (<a href="ident?i=tp">tp</a>-&gt;prior_ssthresh) {
<a name="L2394" href="source/net/ipv4/tcp_input.c#L2394">2394</a>                 const struct <a href="ident?i=inet_connection_sock">inet_connection_sock</a> *icsk = <a href="ident?i=inet_csk">inet_csk</a>(sk);
<a name="L2395" href="source/net/ipv4/tcp_input.c#L2395">2395</a> 
<a name="L2396" href="source/net/ipv4/tcp_input.c#L2396">2396</a>                 if (icsk-&gt;icsk_ca_ops-&gt;undo_cwnd)
<a name="L2397" href="source/net/ipv4/tcp_input.c#L2397">2397</a>                         <a href="ident?i=tp">tp</a>-&gt;snd_cwnd = icsk-&gt;icsk_ca_ops-&gt;undo_cwnd(sk);
<a name="L2398" href="source/net/ipv4/tcp_input.c#L2398">2398</a>                 else
<a name="L2399" href="source/net/ipv4/tcp_input.c#L2399">2399</a>                         <a href="ident?i=tp">tp</a>-&gt;snd_cwnd = <a href="ident?i=max">max</a>(<a href="ident?i=tp">tp</a>-&gt;snd_cwnd, <a href="ident?i=tp">tp</a>-&gt;snd_ssthresh &lt;&lt; 1);
<a name="L2400" href="source/net/ipv4/tcp_input.c#L2400">2400</a> 
<a name="L2401" href="source/net/ipv4/tcp_input.c#L2401">2401</a>                 if (<a href="ident?i=tp">tp</a>-&gt;prior_ssthresh &gt; <a href="ident?i=tp">tp</a>-&gt;snd_ssthresh) {
<a name="L2402" href="source/net/ipv4/tcp_input.c#L2402">2402</a>                         <a href="ident?i=tp">tp</a>-&gt;snd_ssthresh = <a href="ident?i=tp">tp</a>-&gt;prior_ssthresh;
<a name="L2403" href="source/net/ipv4/tcp_input.c#L2403">2403</a>                         <a href="ident?i=tcp_ecn_withdraw_cwr">tcp_ecn_withdraw_cwr</a>(<a href="ident?i=tp">tp</a>);
<a name="L2404" href="source/net/ipv4/tcp_input.c#L2404">2404</a>                 }
<a name="L2405" href="source/net/ipv4/tcp_input.c#L2405">2405</a>         } else {
<a name="L2406" href="source/net/ipv4/tcp_input.c#L2406">2406</a>                 <a href="ident?i=tp">tp</a>-&gt;snd_cwnd = <a href="ident?i=max">max</a>(<a href="ident?i=tp">tp</a>-&gt;snd_cwnd, <a href="ident?i=tp">tp</a>-&gt;snd_ssthresh);
<a name="L2407" href="source/net/ipv4/tcp_input.c#L2407">2407</a>         }
<a name="L2408" href="source/net/ipv4/tcp_input.c#L2408">2408</a>         <a href="ident?i=tp">tp</a>-&gt;snd_cwnd_stamp = <a href="ident?i=tcp_time_stamp">tcp_time_stamp</a>;
<a name="L2409" href="source/net/ipv4/tcp_input.c#L2409">2409</a>         <a href="ident?i=tp">tp</a>-&gt;undo_marker = 0;
<a name="L2410" href="source/net/ipv4/tcp_input.c#L2410">2410</a> }
<a name="L2411" href="source/net/ipv4/tcp_input.c#L2411">2411</a> 
<a name="L2412" href="source/net/ipv4/tcp_input.c#L2412">2412</a> static inline <a href="ident?i=bool">bool</a> <a href="ident?i=tcp_may_undo">tcp_may_undo</a>(const struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a>)
<a name="L2413" href="source/net/ipv4/tcp_input.c#L2413">2413</a> {
<a name="L2414" href="source/net/ipv4/tcp_input.c#L2414">2414</a>         return <a href="ident?i=tp">tp</a>-&gt;undo_marker &amp;&amp; (!<a href="ident?i=tp">tp</a>-&gt;undo_retrans || <a href="ident?i=tcp_packet_delayed">tcp_packet_delayed</a>(<a href="ident?i=tp">tp</a>));
<a name="L2415" href="source/net/ipv4/tcp_input.c#L2415">2415</a> }
<a name="L2416" href="source/net/ipv4/tcp_input.c#L2416">2416</a> 
<a name="L2417" href="source/net/ipv4/tcp_input.c#L2417">2417</a> <b><i>/* People celebrate: "We love our President!" */</i></b>
<a name="L2418" href="source/net/ipv4/tcp_input.c#L2418">2418</a> static <a href="ident?i=bool">bool</a> <a href="ident?i=tcp_try_undo_recovery">tcp_try_undo_recovery</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L2419" href="source/net/ipv4/tcp_input.c#L2419">2419</a> {
<a name="L2420" href="source/net/ipv4/tcp_input.c#L2420">2420</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L2421" href="source/net/ipv4/tcp_input.c#L2421">2421</a> 
<a name="L2422" href="source/net/ipv4/tcp_input.c#L2422">2422</a>         if (<a href="ident?i=tcp_may_undo">tcp_may_undo</a>(<a href="ident?i=tp">tp</a>)) {
<a name="L2423" href="source/net/ipv4/tcp_input.c#L2423">2423</a>                 int mib_idx;
<a name="L2424" href="source/net/ipv4/tcp_input.c#L2424">2424</a> 
<a name="L2425" href="source/net/ipv4/tcp_input.c#L2425">2425</a>                 <b><i>/* Happy end! We did not retransmit anything</i></b>
<a name="L2426" href="source/net/ipv4/tcp_input.c#L2426">2426</a> <b><i>                 * or our original transmission succeeded.</i></b>
<a name="L2427" href="source/net/ipv4/tcp_input.c#L2427">2427</a> <b><i>                 */</i></b>
<a name="L2428" href="source/net/ipv4/tcp_input.c#L2428">2428</a>                 <a href="ident?i=DBGUNDO">DBGUNDO</a>(sk, <a href="ident?i=inet_csk">inet_csk</a>(sk)-&gt;icsk_ca_state == TCP_CA_Loss ? <i>"loss"</i> : <i>"retrans"</i>);
<a name="L2429" href="source/net/ipv4/tcp_input.c#L2429">2429</a>                 <a href="ident?i=tcp_undo_cwnd_reduction">tcp_undo_cwnd_reduction</a>(sk, <a href="ident?i=false">false</a>);
<a name="L2430" href="source/net/ipv4/tcp_input.c#L2430">2430</a>                 if (<a href="ident?i=inet_csk">inet_csk</a>(sk)-&gt;icsk_ca_state == TCP_CA_Loss)
<a name="L2431" href="source/net/ipv4/tcp_input.c#L2431">2431</a>                         mib_idx = LINUX_MIB_TCPLOSSUNDO;
<a name="L2432" href="source/net/ipv4/tcp_input.c#L2432">2432</a>                 else
<a name="L2433" href="source/net/ipv4/tcp_input.c#L2433">2433</a>                         mib_idx = LINUX_MIB_TCPFULLUNDO;
<a name="L2434" href="source/net/ipv4/tcp_input.c#L2434">2434</a> 
<a name="L2435" href="source/net/ipv4/tcp_input.c#L2435">2435</a>                 <a href="ident?i=NET_INC_STATS_BH">NET_INC_STATS_BH</a>(<a href="ident?i=sock_net">sock_net</a>(sk), mib_idx);
<a name="L2436" href="source/net/ipv4/tcp_input.c#L2436">2436</a>         }
<a name="L2437" href="source/net/ipv4/tcp_input.c#L2437">2437</a>         if (<a href="ident?i=tp">tp</a>-&gt;snd_una == <a href="ident?i=tp">tp</a>-&gt;high_seq &amp;&amp; <a href="ident?i=tcp_is_reno">tcp_is_reno</a>(<a href="ident?i=tp">tp</a>)) {
<a name="L2438" href="source/net/ipv4/tcp_input.c#L2438">2438</a>                 <b><i>/* Hold old state until something *above* high_seq</i></b>
<a name="L2439" href="source/net/ipv4/tcp_input.c#L2439">2439</a> <b><i>                 * is ACKed. For Reno it is MUST to prevent false</i></b>
<a name="L2440" href="source/net/ipv4/tcp_input.c#L2440">2440</a> <b><i>                 * fast retransmits (RFC2582). SACK TCP is safe. */</i></b>
<a name="L2441" href="source/net/ipv4/tcp_input.c#L2441">2441</a>                 <a href="ident?i=tcp_moderate_cwnd">tcp_moderate_cwnd</a>(<a href="ident?i=tp">tp</a>);
<a name="L2442" href="source/net/ipv4/tcp_input.c#L2442">2442</a>                 if (!<a href="ident?i=tcp_any_retrans_done">tcp_any_retrans_done</a>(sk))
<a name="L2443" href="source/net/ipv4/tcp_input.c#L2443">2443</a>                         <a href="ident?i=tp">tp</a>-&gt;retrans_stamp = 0;
<a name="L2444" href="source/net/ipv4/tcp_input.c#L2444">2444</a>                 return <a href="ident?i=true">true</a>;
<a name="L2445" href="source/net/ipv4/tcp_input.c#L2445">2445</a>         }
<a name="L2446" href="source/net/ipv4/tcp_input.c#L2446">2446</a>         <a href="ident?i=tcp_set_ca_state">tcp_set_ca_state</a>(sk, TCP_CA_Open);
<a name="L2447" href="source/net/ipv4/tcp_input.c#L2447">2447</a>         return <a href="ident?i=false">false</a>;
<a name="L2448" href="source/net/ipv4/tcp_input.c#L2448">2448</a> }
<a name="L2449" href="source/net/ipv4/tcp_input.c#L2449">2449</a> 
<a name="L2450" href="source/net/ipv4/tcp_input.c#L2450">2450</a> <b><i>/* Try to undo cwnd reduction, because D-SACKs acked all retransmitted data */</i></b>
<a name="L2451" href="source/net/ipv4/tcp_input.c#L2451">2451</a> static <a href="ident?i=bool">bool</a> <a href="ident?i=tcp_try_undo_dsack">tcp_try_undo_dsack</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L2452" href="source/net/ipv4/tcp_input.c#L2452">2452</a> {
<a name="L2453" href="source/net/ipv4/tcp_input.c#L2453">2453</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L2454" href="source/net/ipv4/tcp_input.c#L2454">2454</a> 
<a name="L2455" href="source/net/ipv4/tcp_input.c#L2455">2455</a>         if (<a href="ident?i=tp">tp</a>-&gt;undo_marker &amp;&amp; !<a href="ident?i=tp">tp</a>-&gt;undo_retrans) {
<a name="L2456" href="source/net/ipv4/tcp_input.c#L2456">2456</a>                 <a href="ident?i=DBGUNDO">DBGUNDO</a>(sk, <i>"D-SACK"</i>);
<a name="L2457" href="source/net/ipv4/tcp_input.c#L2457">2457</a>                 <a href="ident?i=tcp_undo_cwnd_reduction">tcp_undo_cwnd_reduction</a>(sk, <a href="ident?i=false">false</a>);
<a name="L2458" href="source/net/ipv4/tcp_input.c#L2458">2458</a>                 <a href="ident?i=NET_INC_STATS_BH">NET_INC_STATS_BH</a>(<a href="ident?i=sock_net">sock_net</a>(sk), LINUX_MIB_TCPDSACKUNDO);
<a name="L2459" href="source/net/ipv4/tcp_input.c#L2459">2459</a>                 return <a href="ident?i=true">true</a>;
<a name="L2460" href="source/net/ipv4/tcp_input.c#L2460">2460</a>         }
<a name="L2461" href="source/net/ipv4/tcp_input.c#L2461">2461</a>         return <a href="ident?i=false">false</a>;
<a name="L2462" href="source/net/ipv4/tcp_input.c#L2462">2462</a> }
<a name="L2463" href="source/net/ipv4/tcp_input.c#L2463">2463</a> 
<a name="L2464" href="source/net/ipv4/tcp_input.c#L2464">2464</a> <b><i>/* Undo during loss recovery after partial ACK or using F-RTO. */</i></b>
<a name="L2465" href="source/net/ipv4/tcp_input.c#L2465">2465</a> static <a href="ident?i=bool">bool</a> <a href="ident?i=tcp_try_undo_loss">tcp_try_undo_loss</a>(struct <a href="ident?i=sock">sock</a> *sk, <a href="ident?i=bool">bool</a> frto_undo)
<a name="L2466" href="source/net/ipv4/tcp_input.c#L2466">2466</a> {
<a name="L2467" href="source/net/ipv4/tcp_input.c#L2467">2467</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L2468" href="source/net/ipv4/tcp_input.c#L2468">2468</a> 
<a name="L2469" href="source/net/ipv4/tcp_input.c#L2469">2469</a>         if (frto_undo || <a href="ident?i=tcp_may_undo">tcp_may_undo</a>(<a href="ident?i=tp">tp</a>)) {
<a name="L2470" href="source/net/ipv4/tcp_input.c#L2470">2470</a>                 <a href="ident?i=tcp_undo_cwnd_reduction">tcp_undo_cwnd_reduction</a>(sk, <a href="ident?i=true">true</a>);
<a name="L2471" href="source/net/ipv4/tcp_input.c#L2471">2471</a> 
<a name="L2472" href="source/net/ipv4/tcp_input.c#L2472">2472</a>                 <a href="ident?i=DBGUNDO">DBGUNDO</a>(sk, <i>"partial loss"</i>);
<a name="L2473" href="source/net/ipv4/tcp_input.c#L2473">2473</a>                 <a href="ident?i=NET_INC_STATS_BH">NET_INC_STATS_BH</a>(<a href="ident?i=sock_net">sock_net</a>(sk), LINUX_MIB_TCPLOSSUNDO);
<a name="L2474" href="source/net/ipv4/tcp_input.c#L2474">2474</a>                 if (frto_undo)
<a name="L2475" href="source/net/ipv4/tcp_input.c#L2475">2475</a>                         <a href="ident?i=NET_INC_STATS_BH">NET_INC_STATS_BH</a>(<a href="ident?i=sock_net">sock_net</a>(sk),
<a name="L2476" href="source/net/ipv4/tcp_input.c#L2476">2476</a>                                          LINUX_MIB_TCPSPURIOUSRTOS);
<a name="L2477" href="source/net/ipv4/tcp_input.c#L2477">2477</a>                 <a href="ident?i=inet_csk">inet_csk</a>(sk)-&gt;icsk_retransmits = 0;
<a name="L2478" href="source/net/ipv4/tcp_input.c#L2478">2478</a>                 if (frto_undo || <a href="ident?i=tcp_is_sack">tcp_is_sack</a>(<a href="ident?i=tp">tp</a>))
<a name="L2479" href="source/net/ipv4/tcp_input.c#L2479">2479</a>                         <a href="ident?i=tcp_set_ca_state">tcp_set_ca_state</a>(sk, TCP_CA_Open);
<a name="L2480" href="source/net/ipv4/tcp_input.c#L2480">2480</a>                 return <a href="ident?i=true">true</a>;
<a name="L2481" href="source/net/ipv4/tcp_input.c#L2481">2481</a>         }
<a name="L2482" href="source/net/ipv4/tcp_input.c#L2482">2482</a>         return <a href="ident?i=false">false</a>;
<a name="L2483" href="source/net/ipv4/tcp_input.c#L2483">2483</a> }
<a name="L2484" href="source/net/ipv4/tcp_input.c#L2484">2484</a> 
<a name="L2485" href="source/net/ipv4/tcp_input.c#L2485">2485</a> <b><i>/* The cwnd reduction in CWR and Recovery use the PRR algorithm</i></b>
<a name="L2486" href="source/net/ipv4/tcp_input.c#L2486">2486</a> <b><i> * https://datatracker.ietf.org/doc/draft-ietf-tcpm-proportional-rate-reduction/</i></b>
<a name="L2487" href="source/net/ipv4/tcp_input.c#L2487">2487</a> <b><i> * It computes the number of packets to send (sndcnt) based on packets newly</i></b>
<a name="L2488" href="source/net/ipv4/tcp_input.c#L2488">2488</a> <b><i> * delivered:</i></b>
<a name="L2489" href="source/net/ipv4/tcp_input.c#L2489">2489</a> <b><i> *   1) If the packets in flight is larger than ssthresh, PRR spreads the</i></b>
<a name="L2490" href="source/net/ipv4/tcp_input.c#L2490">2490</a> <b><i> *      cwnd reductions across a full RTT.</i></b>
<a name="L2491" href="source/net/ipv4/tcp_input.c#L2491">2491</a> <b><i> *   2) If packets in flight is lower than ssthresh (such as due to excess</i></b>
<a name="L2492" href="source/net/ipv4/tcp_input.c#L2492">2492</a> <b><i> *      losses and/or application stalls), do not perform any further cwnd</i></b>
<a name="L2493" href="source/net/ipv4/tcp_input.c#L2493">2493</a> <b><i> *      reductions, but instead slow start up to ssthresh.</i></b>
<a name="L2494" href="source/net/ipv4/tcp_input.c#L2494">2494</a> <b><i> */</i></b>
<a name="L2495" href="source/net/ipv4/tcp_input.c#L2495">2495</a> static void <a href="ident?i=tcp_init_cwnd_reduction">tcp_init_cwnd_reduction</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L2496" href="source/net/ipv4/tcp_input.c#L2496">2496</a> {
<a name="L2497" href="source/net/ipv4/tcp_input.c#L2497">2497</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L2498" href="source/net/ipv4/tcp_input.c#L2498">2498</a> 
<a name="L2499" href="source/net/ipv4/tcp_input.c#L2499">2499</a>         <a href="ident?i=tp">tp</a>-&gt;high_seq = <a href="ident?i=tp">tp</a>-&gt;snd_nxt;
<a name="L2500" href="source/net/ipv4/tcp_input.c#L2500">2500</a>         <a href="ident?i=tp">tp</a>-&gt;tlp_high_seq = 0;
<a name="L2501" href="source/net/ipv4/tcp_input.c#L2501">2501</a>         <a href="ident?i=tp">tp</a>-&gt;snd_cwnd_cnt = 0;
<a name="L2502" href="source/net/ipv4/tcp_input.c#L2502">2502</a>         <a href="ident?i=tp">tp</a>-&gt;prior_cwnd = <a href="ident?i=tp">tp</a>-&gt;snd_cwnd;
<a name="L2503" href="source/net/ipv4/tcp_input.c#L2503">2503</a>         <a href="ident?i=tp">tp</a>-&gt;prr_delivered = 0;
<a name="L2504" href="source/net/ipv4/tcp_input.c#L2504">2504</a>         <a href="ident?i=tp">tp</a>-&gt;prr_out = 0;
<a name="L2505" href="source/net/ipv4/tcp_input.c#L2505">2505</a>         <a href="ident?i=tp">tp</a>-&gt;snd_ssthresh = <a href="ident?i=inet_csk">inet_csk</a>(sk)-&gt;icsk_ca_ops-&gt;ssthresh(sk);
<a name="L2506" href="source/net/ipv4/tcp_input.c#L2506">2506</a>         <a href="ident?i=tcp_ecn_queue_cwr">tcp_ecn_queue_cwr</a>(<a href="ident?i=tp">tp</a>);
<a name="L2507" href="source/net/ipv4/tcp_input.c#L2507">2507</a> }
<a name="L2508" href="source/net/ipv4/tcp_input.c#L2508">2508</a> 
<a name="L2509" href="source/net/ipv4/tcp_input.c#L2509">2509</a> static void <a href="ident?i=tcp_cwnd_reduction">tcp_cwnd_reduction</a>(struct <a href="ident?i=sock">sock</a> *sk, const int prior_unsacked,
<a name="L2510" href="source/net/ipv4/tcp_input.c#L2510">2510</a>                                int fast_rexmit)
<a name="L2511" href="source/net/ipv4/tcp_input.c#L2511">2511</a> {
<a name="L2512" href="source/net/ipv4/tcp_input.c#L2512">2512</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L2513" href="source/net/ipv4/tcp_input.c#L2513">2513</a>         int sndcnt = 0;
<a name="L2514" href="source/net/ipv4/tcp_input.c#L2514">2514</a>         int <a href="ident?i=delta">delta</a> = <a href="ident?i=tp">tp</a>-&gt;snd_ssthresh - <a href="ident?i=tcp_packets_in_flight">tcp_packets_in_flight</a>(<a href="ident?i=tp">tp</a>);
<a name="L2515" href="source/net/ipv4/tcp_input.c#L2515">2515</a>         int newly_acked_sacked = prior_unsacked -
<a name="L2516" href="source/net/ipv4/tcp_input.c#L2516">2516</a>                                  (<a href="ident?i=tp">tp</a>-&gt;packets_out - <a href="ident?i=tp">tp</a>-&gt;sacked_out);
<a name="L2517" href="source/net/ipv4/tcp_input.c#L2517">2517</a> 
<a name="L2518" href="source/net/ipv4/tcp_input.c#L2518">2518</a>         <a href="ident?i=tp">tp</a>-&gt;prr_delivered += newly_acked_sacked;
<a name="L2519" href="source/net/ipv4/tcp_input.c#L2519">2519</a>         if (<a href="ident?i=tcp_packets_in_flight">tcp_packets_in_flight</a>(<a href="ident?i=tp">tp</a>) &gt; <a href="ident?i=tp">tp</a>-&gt;snd_ssthresh) {
<a name="L2520" href="source/net/ipv4/tcp_input.c#L2520">2520</a>                 <a href="ident?i=u64">u64</a> dividend = (<a href="ident?i=u64">u64</a>)<a href="ident?i=tp">tp</a>-&gt;snd_ssthresh * <a href="ident?i=tp">tp</a>-&gt;prr_delivered +
<a name="L2521" href="source/net/ipv4/tcp_input.c#L2521">2521</a>                                <a href="ident?i=tp">tp</a>-&gt;prior_cwnd - 1;
<a name="L2522" href="source/net/ipv4/tcp_input.c#L2522">2522</a>                 sndcnt = <a href="ident?i=div_u64">div_u64</a>(dividend, <a href="ident?i=tp">tp</a>-&gt;prior_cwnd) - <a href="ident?i=tp">tp</a>-&gt;prr_out;
<a name="L2523" href="source/net/ipv4/tcp_input.c#L2523">2523</a>         } else {
<a name="L2524" href="source/net/ipv4/tcp_input.c#L2524">2524</a>                 sndcnt = <a href="ident?i=min_t">min_t</a>(int, <a href="ident?i=delta">delta</a>,
<a name="L2525" href="source/net/ipv4/tcp_input.c#L2525">2525</a>                                <a href="ident?i=max_t">max_t</a>(int, <a href="ident?i=tp">tp</a>-&gt;prr_delivered - <a href="ident?i=tp">tp</a>-&gt;prr_out,
<a name="L2526" href="source/net/ipv4/tcp_input.c#L2526">2526</a>                                      newly_acked_sacked) + 1);
<a name="L2527" href="source/net/ipv4/tcp_input.c#L2527">2527</a>         }
<a name="L2528" href="source/net/ipv4/tcp_input.c#L2528">2528</a> 
<a name="L2529" href="source/net/ipv4/tcp_input.c#L2529">2529</a>         sndcnt = <a href="ident?i=max">max</a>(sndcnt, (fast_rexmit ? 1 : 0));
<a name="L2530" href="source/net/ipv4/tcp_input.c#L2530">2530</a>         <a href="ident?i=tp">tp</a>-&gt;snd_cwnd = <a href="ident?i=tcp_packets_in_flight">tcp_packets_in_flight</a>(<a href="ident?i=tp">tp</a>) + sndcnt;
<a name="L2531" href="source/net/ipv4/tcp_input.c#L2531">2531</a> }
<a name="L2532" href="source/net/ipv4/tcp_input.c#L2532">2532</a> 
<a name="L2533" href="source/net/ipv4/tcp_input.c#L2533">2533</a> static inline void <a href="ident?i=tcp_end_cwnd_reduction">tcp_end_cwnd_reduction</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L2534" href="source/net/ipv4/tcp_input.c#L2534">2534</a> {
<a name="L2535" href="source/net/ipv4/tcp_input.c#L2535">2535</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L2536" href="source/net/ipv4/tcp_input.c#L2536">2536</a> 
<a name="L2537" href="source/net/ipv4/tcp_input.c#L2537">2537</a>         <b><i>/* Reset cwnd to ssthresh in CWR or Recovery (unless it's undone) */</i></b>
<a name="L2538" href="source/net/ipv4/tcp_input.c#L2538">2538</a>         if (<a href="ident?i=inet_csk">inet_csk</a>(sk)-&gt;icsk_ca_state == TCP_CA_CWR ||
<a name="L2539" href="source/net/ipv4/tcp_input.c#L2539">2539</a>             (<a href="ident?i=tp">tp</a>-&gt;undo_marker &amp;&amp; <a href="ident?i=tp">tp</a>-&gt;snd_ssthresh &lt; <a href="ident?i=TCP_INFINITE_SSTHRESH">TCP_INFINITE_SSTHRESH</a>)) {
<a name="L2540" href="source/net/ipv4/tcp_input.c#L2540">2540</a>                 <a href="ident?i=tp">tp</a>-&gt;snd_cwnd = <a href="ident?i=tp">tp</a>-&gt;snd_ssthresh;
<a name="L2541" href="source/net/ipv4/tcp_input.c#L2541">2541</a>                 <a href="ident?i=tp">tp</a>-&gt;snd_cwnd_stamp = <a href="ident?i=tcp_time_stamp">tcp_time_stamp</a>;
<a name="L2542" href="source/net/ipv4/tcp_input.c#L2542">2542</a>         }
<a name="L2543" href="source/net/ipv4/tcp_input.c#L2543">2543</a>         <a href="ident?i=tcp_ca_event">tcp_ca_event</a>(sk, CA_EVENT_COMPLETE_CWR);
<a name="L2544" href="source/net/ipv4/tcp_input.c#L2544">2544</a> }
<a name="L2545" href="source/net/ipv4/tcp_input.c#L2545">2545</a> 
<a name="L2546" href="source/net/ipv4/tcp_input.c#L2546">2546</a> <b><i>/* Enter CWR state. Disable cwnd undo since congestion is proven with ECN */</i></b>
<a name="L2547" href="source/net/ipv4/tcp_input.c#L2547">2547</a> void <a href="ident?i=tcp_enter_cwr">tcp_enter_cwr</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L2548" href="source/net/ipv4/tcp_input.c#L2548">2548</a> {
<a name="L2549" href="source/net/ipv4/tcp_input.c#L2549">2549</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L2550" href="source/net/ipv4/tcp_input.c#L2550">2550</a> 
<a name="L2551" href="source/net/ipv4/tcp_input.c#L2551">2551</a>         <a href="ident?i=tp">tp</a>-&gt;prior_ssthresh = 0;
<a name="L2552" href="source/net/ipv4/tcp_input.c#L2552">2552</a>         if (<a href="ident?i=inet_csk">inet_csk</a>(sk)-&gt;icsk_ca_state &lt; TCP_CA_CWR) {
<a name="L2553" href="source/net/ipv4/tcp_input.c#L2553">2553</a>                 <a href="ident?i=tp">tp</a>-&gt;undo_marker = 0;
<a name="L2554" href="source/net/ipv4/tcp_input.c#L2554">2554</a>                 <a href="ident?i=tcp_init_cwnd_reduction">tcp_init_cwnd_reduction</a>(sk);
<a name="L2555" href="source/net/ipv4/tcp_input.c#L2555">2555</a>                 <a href="ident?i=tcp_set_ca_state">tcp_set_ca_state</a>(sk, TCP_CA_CWR);
<a name="L2556" href="source/net/ipv4/tcp_input.c#L2556">2556</a>         }
<a name="L2557" href="source/net/ipv4/tcp_input.c#L2557">2557</a> }
<a name="L2558" href="source/net/ipv4/tcp_input.c#L2558">2558</a> 
<a name="L2559" href="source/net/ipv4/tcp_input.c#L2559">2559</a> static void <a href="ident?i=tcp_try_keep_open">tcp_try_keep_open</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L2560" href="source/net/ipv4/tcp_input.c#L2560">2560</a> {
<a name="L2561" href="source/net/ipv4/tcp_input.c#L2561">2561</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L2562" href="source/net/ipv4/tcp_input.c#L2562">2562</a>         int <a href="ident?i=state">state</a> = TCP_CA_Open;
<a name="L2563" href="source/net/ipv4/tcp_input.c#L2563">2563</a> 
<a name="L2564" href="source/net/ipv4/tcp_input.c#L2564">2564</a>         if (<a href="ident?i=tcp_left_out">tcp_left_out</a>(<a href="ident?i=tp">tp</a>) || <a href="ident?i=tcp_any_retrans_done">tcp_any_retrans_done</a>(sk))
<a name="L2565" href="source/net/ipv4/tcp_input.c#L2565">2565</a>                 <a href="ident?i=state">state</a> = TCP_CA_Disorder;
<a name="L2566" href="source/net/ipv4/tcp_input.c#L2566">2566</a> 
<a name="L2567" href="source/net/ipv4/tcp_input.c#L2567">2567</a>         if (<a href="ident?i=inet_csk">inet_csk</a>(sk)-&gt;icsk_ca_state != <a href="ident?i=state">state</a>) {
<a name="L2568" href="source/net/ipv4/tcp_input.c#L2568">2568</a>                 <a href="ident?i=tcp_set_ca_state">tcp_set_ca_state</a>(sk, <a href="ident?i=state">state</a>);
<a name="L2569" href="source/net/ipv4/tcp_input.c#L2569">2569</a>                 <a href="ident?i=tp">tp</a>-&gt;high_seq = <a href="ident?i=tp">tp</a>-&gt;snd_nxt;
<a name="L2570" href="source/net/ipv4/tcp_input.c#L2570">2570</a>         }
<a name="L2571" href="source/net/ipv4/tcp_input.c#L2571">2571</a> }
<a name="L2572" href="source/net/ipv4/tcp_input.c#L2572">2572</a> 
<a name="L2573" href="source/net/ipv4/tcp_input.c#L2573">2573</a> static void <a href="ident?i=tcp_try_to_open">tcp_try_to_open</a>(struct <a href="ident?i=sock">sock</a> *sk, int <a href="ident?i=flag">flag</a>, const int prior_unsacked)
<a name="L2574" href="source/net/ipv4/tcp_input.c#L2574">2574</a> {
<a name="L2575" href="source/net/ipv4/tcp_input.c#L2575">2575</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L2576" href="source/net/ipv4/tcp_input.c#L2576">2576</a> 
<a name="L2577" href="source/net/ipv4/tcp_input.c#L2577">2577</a>         <a href="ident?i=tcp_verify_left_out">tcp_verify_left_out</a>(<a href="ident?i=tp">tp</a>);
<a name="L2578" href="source/net/ipv4/tcp_input.c#L2578">2578</a> 
<a name="L2579" href="source/net/ipv4/tcp_input.c#L2579">2579</a>         if (!<a href="ident?i=tcp_any_retrans_done">tcp_any_retrans_done</a>(sk))
<a name="L2580" href="source/net/ipv4/tcp_input.c#L2580">2580</a>                 <a href="ident?i=tp">tp</a>-&gt;retrans_stamp = 0;
<a name="L2581" href="source/net/ipv4/tcp_input.c#L2581">2581</a> 
<a name="L2582" href="source/net/ipv4/tcp_input.c#L2582">2582</a>         if (<a href="ident?i=flag">flag</a> &amp; <a href="ident?i=FLAG_ECE">FLAG_ECE</a>)
<a name="L2583" href="source/net/ipv4/tcp_input.c#L2583">2583</a>                 <a href="ident?i=tcp_enter_cwr">tcp_enter_cwr</a>(sk);
<a name="L2584" href="source/net/ipv4/tcp_input.c#L2584">2584</a> 
<a name="L2585" href="source/net/ipv4/tcp_input.c#L2585">2585</a>         if (<a href="ident?i=inet_csk">inet_csk</a>(sk)-&gt;icsk_ca_state != TCP_CA_CWR) {
<a name="L2586" href="source/net/ipv4/tcp_input.c#L2586">2586</a>                 <a href="ident?i=tcp_try_keep_open">tcp_try_keep_open</a>(sk);
<a name="L2587" href="source/net/ipv4/tcp_input.c#L2587">2587</a>         } else {
<a name="L2588" href="source/net/ipv4/tcp_input.c#L2588">2588</a>                 <a href="ident?i=tcp_cwnd_reduction">tcp_cwnd_reduction</a>(sk, prior_unsacked, 0);
<a name="L2589" href="source/net/ipv4/tcp_input.c#L2589">2589</a>         }
<a name="L2590" href="source/net/ipv4/tcp_input.c#L2590">2590</a> }
<a name="L2591" href="source/net/ipv4/tcp_input.c#L2591">2591</a> 
<a name="L2592" href="source/net/ipv4/tcp_input.c#L2592">2592</a> static void <a href="ident?i=tcp_mtup_probe_failed">tcp_mtup_probe_failed</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L2593" href="source/net/ipv4/tcp_input.c#L2593">2593</a> {
<a name="L2594" href="source/net/ipv4/tcp_input.c#L2594">2594</a>         struct <a href="ident?i=inet_connection_sock">inet_connection_sock</a> *icsk = <a href="ident?i=inet_csk">inet_csk</a>(sk);
<a name="L2595" href="source/net/ipv4/tcp_input.c#L2595">2595</a> 
<a name="L2596" href="source/net/ipv4/tcp_input.c#L2596">2596</a>         icsk-&gt;icsk_mtup.search_high = icsk-&gt;icsk_mtup.probe_size - 1;
<a name="L2597" href="source/net/ipv4/tcp_input.c#L2597">2597</a>         icsk-&gt;icsk_mtup.probe_size = 0;
<a name="L2598" href="source/net/ipv4/tcp_input.c#L2598">2598</a> }
<a name="L2599" href="source/net/ipv4/tcp_input.c#L2599">2599</a> 
<a name="L2600" href="source/net/ipv4/tcp_input.c#L2600">2600</a> static void <a href="ident?i=tcp_mtup_probe_success">tcp_mtup_probe_success</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L2601" href="source/net/ipv4/tcp_input.c#L2601">2601</a> {
<a name="L2602" href="source/net/ipv4/tcp_input.c#L2602">2602</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L2603" href="source/net/ipv4/tcp_input.c#L2603">2603</a>         struct <a href="ident?i=inet_connection_sock">inet_connection_sock</a> *icsk = <a href="ident?i=inet_csk">inet_csk</a>(sk);
<a name="L2604" href="source/net/ipv4/tcp_input.c#L2604">2604</a> 
<a name="L2605" href="source/net/ipv4/tcp_input.c#L2605">2605</a>         <b><i>/* FIXME: breaks with very large cwnd */</i></b>
<a name="L2606" href="source/net/ipv4/tcp_input.c#L2606">2606</a>         <a href="ident?i=tp">tp</a>-&gt;prior_ssthresh = <a href="ident?i=tcp_current_ssthresh">tcp_current_ssthresh</a>(sk);
<a name="L2607" href="source/net/ipv4/tcp_input.c#L2607">2607</a>         <a href="ident?i=tp">tp</a>-&gt;snd_cwnd = <a href="ident?i=tp">tp</a>-&gt;snd_cwnd *
<a name="L2608" href="source/net/ipv4/tcp_input.c#L2608">2608</a>                        <a href="ident?i=tcp_mss_to_mtu">tcp_mss_to_mtu</a>(sk, <a href="ident?i=tp">tp</a>-&gt;mss_cache) /
<a name="L2609" href="source/net/ipv4/tcp_input.c#L2609">2609</a>                        icsk-&gt;icsk_mtup.probe_size;
<a name="L2610" href="source/net/ipv4/tcp_input.c#L2610">2610</a>         <a href="ident?i=tp">tp</a>-&gt;snd_cwnd_cnt = 0;
<a name="L2611" href="source/net/ipv4/tcp_input.c#L2611">2611</a>         <a href="ident?i=tp">tp</a>-&gt;snd_cwnd_stamp = <a href="ident?i=tcp_time_stamp">tcp_time_stamp</a>;
<a name="L2612" href="source/net/ipv4/tcp_input.c#L2612">2612</a>         <a href="ident?i=tp">tp</a>-&gt;snd_ssthresh = <a href="ident?i=tcp_current_ssthresh">tcp_current_ssthresh</a>(sk);
<a name="L2613" href="source/net/ipv4/tcp_input.c#L2613">2613</a> 
<a name="L2614" href="source/net/ipv4/tcp_input.c#L2614">2614</a>         icsk-&gt;icsk_mtup.search_low = icsk-&gt;icsk_mtup.probe_size;
<a name="L2615" href="source/net/ipv4/tcp_input.c#L2615">2615</a>         icsk-&gt;icsk_mtup.probe_size = 0;
<a name="L2616" href="source/net/ipv4/tcp_input.c#L2616">2616</a>         <a href="ident?i=tcp_sync_mss">tcp_sync_mss</a>(sk, icsk-&gt;icsk_pmtu_cookie);
<a name="L2617" href="source/net/ipv4/tcp_input.c#L2617">2617</a> }
<a name="L2618" href="source/net/ipv4/tcp_input.c#L2618">2618</a> 
<a name="L2619" href="source/net/ipv4/tcp_input.c#L2619">2619</a> <b><i>/* Do a simple retransmit without using the backoff mechanisms in</i></b>
<a name="L2620" href="source/net/ipv4/tcp_input.c#L2620">2620</a> <b><i> * tcp_timer. This is used for path mtu discovery.</i></b>
<a name="L2621" href="source/net/ipv4/tcp_input.c#L2621">2621</a> <b><i> * The socket is already locked here.</i></b>
<a name="L2622" href="source/net/ipv4/tcp_input.c#L2622">2622</a> <b><i> */</i></b>
<a name="L2623" href="source/net/ipv4/tcp_input.c#L2623">2623</a> void <a href="ident?i=tcp_simple_retransmit">tcp_simple_retransmit</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L2624" href="source/net/ipv4/tcp_input.c#L2624">2624</a> {
<a name="L2625" href="source/net/ipv4/tcp_input.c#L2625">2625</a>         const struct <a href="ident?i=inet_connection_sock">inet_connection_sock</a> *icsk = <a href="ident?i=inet_csk">inet_csk</a>(sk);
<a name="L2626" href="source/net/ipv4/tcp_input.c#L2626">2626</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L2627" href="source/net/ipv4/tcp_input.c#L2627">2627</a>         struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>;
<a name="L2628" href="source/net/ipv4/tcp_input.c#L2628">2628</a>         unsigned int mss = <a href="ident?i=tcp_current_mss">tcp_current_mss</a>(sk);
<a name="L2629" href="source/net/ipv4/tcp_input.c#L2629">2629</a>         <a href="ident?i=u32">u32</a> prior_lost = <a href="ident?i=tp">tp</a>-&gt;lost_out;
<a name="L2630" href="source/net/ipv4/tcp_input.c#L2630">2630</a> 
<a name="L2631" href="source/net/ipv4/tcp_input.c#L2631">2631</a>         <a href="ident?i=tcp_for_write_queue">tcp_for_write_queue</a>(<a href="ident?i=skb">skb</a>, sk) {
<a name="L2632" href="source/net/ipv4/tcp_input.c#L2632">2632</a>                 if (<a href="ident?i=skb">skb</a> == <a href="ident?i=tcp_send_head">tcp_send_head</a>(sk))
<a name="L2633" href="source/net/ipv4/tcp_input.c#L2633">2633</a>                         break;
<a name="L2634" href="source/net/ipv4/tcp_input.c#L2634">2634</a>                 if (<a href="ident?i=tcp_skb_seglen">tcp_skb_seglen</a>(<a href="ident?i=skb">skb</a>) &gt; mss &amp;&amp;
<a name="L2635" href="source/net/ipv4/tcp_input.c#L2635">2635</a>                     !(<a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;sacked &amp; <a href="ident?i=TCPCB_SACKED_ACKED">TCPCB_SACKED_ACKED</a>)) {
<a name="L2636" href="source/net/ipv4/tcp_input.c#L2636">2636</a>                         if (<a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;sacked &amp; <a href="ident?i=TCPCB_SACKED_RETRANS">TCPCB_SACKED_RETRANS</a>) {
<a name="L2637" href="source/net/ipv4/tcp_input.c#L2637">2637</a>                                 <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;sacked &amp;= ~TCPCB_SACKED_RETRANS;
<a name="L2638" href="source/net/ipv4/tcp_input.c#L2638">2638</a>                                 <a href="ident?i=tp">tp</a>-&gt;retrans_out -= <a href="ident?i=tcp_skb_pcount">tcp_skb_pcount</a>(<a href="ident?i=skb">skb</a>);
<a name="L2639" href="source/net/ipv4/tcp_input.c#L2639">2639</a>                         }
<a name="L2640" href="source/net/ipv4/tcp_input.c#L2640">2640</a>                         <a href="ident?i=tcp_skb_mark_lost_uncond_verify">tcp_skb_mark_lost_uncond_verify</a>(<a href="ident?i=tp">tp</a>, <a href="ident?i=skb">skb</a>);
<a name="L2641" href="source/net/ipv4/tcp_input.c#L2641">2641</a>                 }
<a name="L2642" href="source/net/ipv4/tcp_input.c#L2642">2642</a>         }
<a name="L2643" href="source/net/ipv4/tcp_input.c#L2643">2643</a> 
<a name="L2644" href="source/net/ipv4/tcp_input.c#L2644">2644</a>         <a href="ident?i=tcp_clear_retrans_hints_partial">tcp_clear_retrans_hints_partial</a>(<a href="ident?i=tp">tp</a>);
<a name="L2645" href="source/net/ipv4/tcp_input.c#L2645">2645</a> 
<a name="L2646" href="source/net/ipv4/tcp_input.c#L2646">2646</a>         if (prior_lost == <a href="ident?i=tp">tp</a>-&gt;lost_out)
<a name="L2647" href="source/net/ipv4/tcp_input.c#L2647">2647</a>                 return;
<a name="L2648" href="source/net/ipv4/tcp_input.c#L2648">2648</a> 
<a name="L2649" href="source/net/ipv4/tcp_input.c#L2649">2649</a>         if (<a href="ident?i=tcp_is_reno">tcp_is_reno</a>(<a href="ident?i=tp">tp</a>))
<a name="L2650" href="source/net/ipv4/tcp_input.c#L2650">2650</a>                 <a href="ident?i=tcp_limit_reno_sacked">tcp_limit_reno_sacked</a>(<a href="ident?i=tp">tp</a>);
<a name="L2651" href="source/net/ipv4/tcp_input.c#L2651">2651</a> 
<a name="L2652" href="source/net/ipv4/tcp_input.c#L2652">2652</a>         <a href="ident?i=tcp_verify_left_out">tcp_verify_left_out</a>(<a href="ident?i=tp">tp</a>);
<a name="L2653" href="source/net/ipv4/tcp_input.c#L2653">2653</a> 
<a name="L2654" href="source/net/ipv4/tcp_input.c#L2654">2654</a>         <b><i>/* Don't muck with the congestion window here.</i></b>
<a name="L2655" href="source/net/ipv4/tcp_input.c#L2655">2655</a> <b><i>         * Reason is that we do not increase amount of _data_</i></b>
<a name="L2656" href="source/net/ipv4/tcp_input.c#L2656">2656</a> <b><i>         * in network, but units changed and effective</i></b>
<a name="L2657" href="source/net/ipv4/tcp_input.c#L2657">2657</a> <b><i>         * cwnd/ssthresh really reduced now.</i></b>
<a name="L2658" href="source/net/ipv4/tcp_input.c#L2658">2658</a> <b><i>         */</i></b>
<a name="L2659" href="source/net/ipv4/tcp_input.c#L2659">2659</a>         if (icsk-&gt;icsk_ca_state != TCP_CA_Loss) {
<a name="L2660" href="source/net/ipv4/tcp_input.c#L2660">2660</a>                 <a href="ident?i=tp">tp</a>-&gt;high_seq = <a href="ident?i=tp">tp</a>-&gt;snd_nxt;
<a name="L2661" href="source/net/ipv4/tcp_input.c#L2661">2661</a>                 <a href="ident?i=tp">tp</a>-&gt;snd_ssthresh = <a href="ident?i=tcp_current_ssthresh">tcp_current_ssthresh</a>(sk);
<a name="L2662" href="source/net/ipv4/tcp_input.c#L2662">2662</a>                 <a href="ident?i=tp">tp</a>-&gt;prior_ssthresh = 0;
<a name="L2663" href="source/net/ipv4/tcp_input.c#L2663">2663</a>                 <a href="ident?i=tp">tp</a>-&gt;undo_marker = 0;
<a name="L2664" href="source/net/ipv4/tcp_input.c#L2664">2664</a>                 <a href="ident?i=tcp_set_ca_state">tcp_set_ca_state</a>(sk, TCP_CA_Loss);
<a name="L2665" href="source/net/ipv4/tcp_input.c#L2665">2665</a>         }
<a name="L2666" href="source/net/ipv4/tcp_input.c#L2666">2666</a>         <a href="ident?i=tcp_xmit_retransmit_queue">tcp_xmit_retransmit_queue</a>(sk);
<a name="L2667" href="source/net/ipv4/tcp_input.c#L2667">2667</a> }
<a name="L2668" href="source/net/ipv4/tcp_input.c#L2668">2668</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=tcp_simple_retransmit">tcp_simple_retransmit</a>);
<a name="L2669" href="source/net/ipv4/tcp_input.c#L2669">2669</a> 
<a name="L2670" href="source/net/ipv4/tcp_input.c#L2670">2670</a> static void <a href="ident?i=tcp_enter_recovery">tcp_enter_recovery</a>(struct <a href="ident?i=sock">sock</a> *sk, <a href="ident?i=bool">bool</a> ece_ack)
<a name="L2671" href="source/net/ipv4/tcp_input.c#L2671">2671</a> {
<a name="L2672" href="source/net/ipv4/tcp_input.c#L2672">2672</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L2673" href="source/net/ipv4/tcp_input.c#L2673">2673</a>         int mib_idx;
<a name="L2674" href="source/net/ipv4/tcp_input.c#L2674">2674</a> 
<a name="L2675" href="source/net/ipv4/tcp_input.c#L2675">2675</a>         if (<a href="ident?i=tcp_is_reno">tcp_is_reno</a>(<a href="ident?i=tp">tp</a>))
<a name="L2676" href="source/net/ipv4/tcp_input.c#L2676">2676</a>                 mib_idx = LINUX_MIB_TCPRENORECOVERY;
<a name="L2677" href="source/net/ipv4/tcp_input.c#L2677">2677</a>         else
<a name="L2678" href="source/net/ipv4/tcp_input.c#L2678">2678</a>                 mib_idx = LINUX_MIB_TCPSACKRECOVERY;
<a name="L2679" href="source/net/ipv4/tcp_input.c#L2679">2679</a> 
<a name="L2680" href="source/net/ipv4/tcp_input.c#L2680">2680</a>         <a href="ident?i=NET_INC_STATS_BH">NET_INC_STATS_BH</a>(<a href="ident?i=sock_net">sock_net</a>(sk), mib_idx);
<a name="L2681" href="source/net/ipv4/tcp_input.c#L2681">2681</a> 
<a name="L2682" href="source/net/ipv4/tcp_input.c#L2682">2682</a>         <a href="ident?i=tp">tp</a>-&gt;prior_ssthresh = 0;
<a name="L2683" href="source/net/ipv4/tcp_input.c#L2683">2683</a>         <a href="ident?i=tcp_init_undo">tcp_init_undo</a>(<a href="ident?i=tp">tp</a>);
<a name="L2684" href="source/net/ipv4/tcp_input.c#L2684">2684</a> 
<a name="L2685" href="source/net/ipv4/tcp_input.c#L2685">2685</a>         if (<a href="ident?i=inet_csk">inet_csk</a>(sk)-&gt;icsk_ca_state &lt; TCP_CA_CWR) {
<a name="L2686" href="source/net/ipv4/tcp_input.c#L2686">2686</a>                 if (!ece_ack)
<a name="L2687" href="source/net/ipv4/tcp_input.c#L2687">2687</a>                         <a href="ident?i=tp">tp</a>-&gt;prior_ssthresh = <a href="ident?i=tcp_current_ssthresh">tcp_current_ssthresh</a>(sk);
<a name="L2688" href="source/net/ipv4/tcp_input.c#L2688">2688</a>                 <a href="ident?i=tcp_init_cwnd_reduction">tcp_init_cwnd_reduction</a>(sk);
<a name="L2689" href="source/net/ipv4/tcp_input.c#L2689">2689</a>         }
<a name="L2690" href="source/net/ipv4/tcp_input.c#L2690">2690</a>         <a href="ident?i=tcp_set_ca_state">tcp_set_ca_state</a>(sk, TCP_CA_Recovery);
<a name="L2691" href="source/net/ipv4/tcp_input.c#L2691">2691</a> }
<a name="L2692" href="source/net/ipv4/tcp_input.c#L2692">2692</a> 
<a name="L2693" href="source/net/ipv4/tcp_input.c#L2693">2693</a> <b><i>/* Process an ACK in CA_Loss state. Move to CA_Open if lost data are</i></b>
<a name="L2694" href="source/net/ipv4/tcp_input.c#L2694">2694</a> <b><i> * recovered or spurious. Otherwise retransmits more on partial ACKs.</i></b>
<a name="L2695" href="source/net/ipv4/tcp_input.c#L2695">2695</a> <b><i> */</i></b>
<a name="L2696" href="source/net/ipv4/tcp_input.c#L2696">2696</a> static void <a href="ident?i=tcp_process_loss">tcp_process_loss</a>(struct <a href="ident?i=sock">sock</a> *sk, int <a href="ident?i=flag">flag</a>, <a href="ident?i=bool">bool</a> is_dupack)
<a name="L2697" href="source/net/ipv4/tcp_input.c#L2697">2697</a> {
<a name="L2698" href="source/net/ipv4/tcp_input.c#L2698">2698</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L2699" href="source/net/ipv4/tcp_input.c#L2699">2699</a>         <a href="ident?i=bool">bool</a> recovered = !<a href="ident?i=before">before</a>(<a href="ident?i=tp">tp</a>-&gt;snd_una, <a href="ident?i=tp">tp</a>-&gt;high_seq);
<a name="L2700" href="source/net/ipv4/tcp_input.c#L2700">2700</a> 
<a name="L2701" href="source/net/ipv4/tcp_input.c#L2701">2701</a>         if ((<a href="ident?i=flag">flag</a> &amp; <a href="ident?i=FLAG_SND_UNA_ADVANCED">FLAG_SND_UNA_ADVANCED</a>) &amp;&amp;
<a name="L2702" href="source/net/ipv4/tcp_input.c#L2702">2702</a>             <a href="ident?i=tcp_try_undo_loss">tcp_try_undo_loss</a>(sk, <a href="ident?i=false">false</a>))
<a name="L2703" href="source/net/ipv4/tcp_input.c#L2703">2703</a>                 return;
<a name="L2704" href="source/net/ipv4/tcp_input.c#L2704">2704</a> 
<a name="L2705" href="source/net/ipv4/tcp_input.c#L2705">2705</a>         if (<a href="ident?i=tp">tp</a>-&gt;frto) { <b><i>/* F-RTO RFC5682 sec 3.1 (sack enhanced version). */</i></b>
<a name="L2706" href="source/net/ipv4/tcp_input.c#L2706">2706</a>                 <b><i>/* Step 3.b. A timeout is spurious if not all data are</i></b>
<a name="L2707" href="source/net/ipv4/tcp_input.c#L2707">2707</a> <b><i>                 * lost, i.e., never-retransmitted data are (s)acked.</i></b>
<a name="L2708" href="source/net/ipv4/tcp_input.c#L2708">2708</a> <b><i>                 */</i></b>
<a name="L2709" href="source/net/ipv4/tcp_input.c#L2709">2709</a>                 if ((<a href="ident?i=flag">flag</a> &amp; <a href="ident?i=FLAG_ORIG_SACK_ACKED">FLAG_ORIG_SACK_ACKED</a>) &amp;&amp;
<a name="L2710" href="source/net/ipv4/tcp_input.c#L2710">2710</a>                     <a href="ident?i=tcp_try_undo_loss">tcp_try_undo_loss</a>(sk, <a href="ident?i=true">true</a>))
<a name="L2711" href="source/net/ipv4/tcp_input.c#L2711">2711</a>                         return;
<a name="L2712" href="source/net/ipv4/tcp_input.c#L2712">2712</a> 
<a name="L2713" href="source/net/ipv4/tcp_input.c#L2713">2713</a>                 if (<a href="ident?i=after">after</a>(<a href="ident?i=tp">tp</a>-&gt;snd_nxt, <a href="ident?i=tp">tp</a>-&gt;high_seq)) {
<a name="L2714" href="source/net/ipv4/tcp_input.c#L2714">2714</a>                         if (<a href="ident?i=flag">flag</a> &amp; <a href="ident?i=FLAG_DATA_SACKED">FLAG_DATA_SACKED</a> || is_dupack)
<a name="L2715" href="source/net/ipv4/tcp_input.c#L2715">2715</a>                                 <a href="ident?i=tp">tp</a>-&gt;frto = 0; <b><i>/* Step 3.a. loss was real */</i></b>
<a name="L2716" href="source/net/ipv4/tcp_input.c#L2716">2716</a>                 } else if (<a href="ident?i=flag">flag</a> &amp; <a href="ident?i=FLAG_SND_UNA_ADVANCED">FLAG_SND_UNA_ADVANCED</a> &amp;&amp; !recovered) {
<a name="L2717" href="source/net/ipv4/tcp_input.c#L2717">2717</a>                         <a href="ident?i=tp">tp</a>-&gt;high_seq = <a href="ident?i=tp">tp</a>-&gt;snd_nxt;
<a name="L2718" href="source/net/ipv4/tcp_input.c#L2718">2718</a>                         <a href="ident?i=__tcp_push_pending_frames">__tcp_push_pending_frames</a>(sk, <a href="ident?i=tcp_current_mss">tcp_current_mss</a>(sk),
<a name="L2719" href="source/net/ipv4/tcp_input.c#L2719">2719</a>                                                   <a href="ident?i=TCP_NAGLE_OFF">TCP_NAGLE_OFF</a>);
<a name="L2720" href="source/net/ipv4/tcp_input.c#L2720">2720</a>                         if (<a href="ident?i=after">after</a>(<a href="ident?i=tp">tp</a>-&gt;snd_nxt, <a href="ident?i=tp">tp</a>-&gt;high_seq))
<a name="L2721" href="source/net/ipv4/tcp_input.c#L2721">2721</a>                                 return; <b><i>/* Step 2.b */</i></b>
<a name="L2722" href="source/net/ipv4/tcp_input.c#L2722">2722</a>                         <a href="ident?i=tp">tp</a>-&gt;frto = 0;
<a name="L2723" href="source/net/ipv4/tcp_input.c#L2723">2723</a>                 }
<a name="L2724" href="source/net/ipv4/tcp_input.c#L2724">2724</a>         }
<a name="L2725" href="source/net/ipv4/tcp_input.c#L2725">2725</a> 
<a name="L2726" href="source/net/ipv4/tcp_input.c#L2726">2726</a>         if (recovered) {
<a name="L2727" href="source/net/ipv4/tcp_input.c#L2727">2727</a>                 <b><i>/* F-RTO RFC5682 sec 3.1 step 2.a and 1st part of step 3.a */</i></b>
<a name="L2728" href="source/net/ipv4/tcp_input.c#L2728">2728</a>                 <a href="ident?i=tcp_try_undo_recovery">tcp_try_undo_recovery</a>(sk);
<a name="L2729" href="source/net/ipv4/tcp_input.c#L2729">2729</a>                 return;
<a name="L2730" href="source/net/ipv4/tcp_input.c#L2730">2730</a>         }
<a name="L2731" href="source/net/ipv4/tcp_input.c#L2731">2731</a>         if (<a href="ident?i=tcp_is_reno">tcp_is_reno</a>(<a href="ident?i=tp">tp</a>)) {
<a name="L2732" href="source/net/ipv4/tcp_input.c#L2732">2732</a>                 <b><i>/* A Reno DUPACK means new data in F-RTO step 2.b above are</i></b>
<a name="L2733" href="source/net/ipv4/tcp_input.c#L2733">2733</a> <b><i>                 * delivered. Lower inflight to clock out (re)tranmissions.</i></b>
<a name="L2734" href="source/net/ipv4/tcp_input.c#L2734">2734</a> <b><i>                 */</i></b>
<a name="L2735" href="source/net/ipv4/tcp_input.c#L2735">2735</a>                 if (<a href="ident?i=after">after</a>(<a href="ident?i=tp">tp</a>-&gt;snd_nxt, <a href="ident?i=tp">tp</a>-&gt;high_seq) &amp;&amp; is_dupack)
<a name="L2736" href="source/net/ipv4/tcp_input.c#L2736">2736</a>                         <a href="ident?i=tcp_add_reno_sack">tcp_add_reno_sack</a>(sk);
<a name="L2737" href="source/net/ipv4/tcp_input.c#L2737">2737</a>                 else if (<a href="ident?i=flag">flag</a> &amp; <a href="ident?i=FLAG_SND_UNA_ADVANCED">FLAG_SND_UNA_ADVANCED</a>)
<a name="L2738" href="source/net/ipv4/tcp_input.c#L2738">2738</a>                         <a href="ident?i=tcp_reset_reno_sack">tcp_reset_reno_sack</a>(<a href="ident?i=tp">tp</a>);
<a name="L2739" href="source/net/ipv4/tcp_input.c#L2739">2739</a>         }
<a name="L2740" href="source/net/ipv4/tcp_input.c#L2740">2740</a>         <a href="ident?i=tcp_xmit_retransmit_queue">tcp_xmit_retransmit_queue</a>(sk);
<a name="L2741" href="source/net/ipv4/tcp_input.c#L2741">2741</a> }
<a name="L2742" href="source/net/ipv4/tcp_input.c#L2742">2742</a> 
<a name="L2743" href="source/net/ipv4/tcp_input.c#L2743">2743</a> <b><i>/* Undo during fast recovery after partial ACK. */</i></b>
<a name="L2744" href="source/net/ipv4/tcp_input.c#L2744">2744</a> static <a href="ident?i=bool">bool</a> <a href="ident?i=tcp_try_undo_partial">tcp_try_undo_partial</a>(struct <a href="ident?i=sock">sock</a> *sk, const int acked,
<a name="L2745" href="source/net/ipv4/tcp_input.c#L2745">2745</a>                                  const int prior_unsacked)
<a name="L2746" href="source/net/ipv4/tcp_input.c#L2746">2746</a> {
<a name="L2747" href="source/net/ipv4/tcp_input.c#L2747">2747</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L2748" href="source/net/ipv4/tcp_input.c#L2748">2748</a> 
<a name="L2749" href="source/net/ipv4/tcp_input.c#L2749">2749</a>         if (<a href="ident?i=tp">tp</a>-&gt;undo_marker &amp;&amp; <a href="ident?i=tcp_packet_delayed">tcp_packet_delayed</a>(<a href="ident?i=tp">tp</a>)) {
<a name="L2750" href="source/net/ipv4/tcp_input.c#L2750">2750</a>                 <b><i>/* Plain luck! Hole if filled with delayed</i></b>
<a name="L2751" href="source/net/ipv4/tcp_input.c#L2751">2751</a> <b><i>                 * packet, rather than with a retransmit.</i></b>
<a name="L2752" href="source/net/ipv4/tcp_input.c#L2752">2752</a> <b><i>                 */</i></b>
<a name="L2753" href="source/net/ipv4/tcp_input.c#L2753">2753</a>                 <a href="ident?i=tcp_update_reordering">tcp_update_reordering</a>(sk, <a href="ident?i=tcp_fackets_out">tcp_fackets_out</a>(<a href="ident?i=tp">tp</a>) + acked, 1);
<a name="L2754" href="source/net/ipv4/tcp_input.c#L2754">2754</a> 
<a name="L2755" href="source/net/ipv4/tcp_input.c#L2755">2755</a>                 <b><i>/* We are getting evidence that the reordering degree is higher</i></b>
<a name="L2756" href="source/net/ipv4/tcp_input.c#L2756">2756</a> <b><i>                 * than we realized. If there are no retransmits out then we</i></b>
<a name="L2757" href="source/net/ipv4/tcp_input.c#L2757">2757</a> <b><i>                 * can undo. Otherwise we clock out new packets but do not</i></b>
<a name="L2758" href="source/net/ipv4/tcp_input.c#L2758">2758</a> <b><i>                 * mark more packets lost or retransmit more.</i></b>
<a name="L2759" href="source/net/ipv4/tcp_input.c#L2759">2759</a> <b><i>                 */</i></b>
<a name="L2760" href="source/net/ipv4/tcp_input.c#L2760">2760</a>                 if (<a href="ident?i=tp">tp</a>-&gt;retrans_out) {
<a name="L2761" href="source/net/ipv4/tcp_input.c#L2761">2761</a>                         <a href="ident?i=tcp_cwnd_reduction">tcp_cwnd_reduction</a>(sk, prior_unsacked, 0);
<a name="L2762" href="source/net/ipv4/tcp_input.c#L2762">2762</a>                         return <a href="ident?i=true">true</a>;
<a name="L2763" href="source/net/ipv4/tcp_input.c#L2763">2763</a>                 }
<a name="L2764" href="source/net/ipv4/tcp_input.c#L2764">2764</a> 
<a name="L2765" href="source/net/ipv4/tcp_input.c#L2765">2765</a>                 if (!<a href="ident?i=tcp_any_retrans_done">tcp_any_retrans_done</a>(sk))
<a name="L2766" href="source/net/ipv4/tcp_input.c#L2766">2766</a>                         <a href="ident?i=tp">tp</a>-&gt;retrans_stamp = 0;
<a name="L2767" href="source/net/ipv4/tcp_input.c#L2767">2767</a> 
<a name="L2768" href="source/net/ipv4/tcp_input.c#L2768">2768</a>                 <a href="ident?i=DBGUNDO">DBGUNDO</a>(sk, <i>"partial recovery"</i>);
<a name="L2769" href="source/net/ipv4/tcp_input.c#L2769">2769</a>                 <a href="ident?i=tcp_undo_cwnd_reduction">tcp_undo_cwnd_reduction</a>(sk, <a href="ident?i=true">true</a>);
<a name="L2770" href="source/net/ipv4/tcp_input.c#L2770">2770</a>                 <a href="ident?i=NET_INC_STATS_BH">NET_INC_STATS_BH</a>(<a href="ident?i=sock_net">sock_net</a>(sk), LINUX_MIB_TCPPARTIALUNDO);
<a name="L2771" href="source/net/ipv4/tcp_input.c#L2771">2771</a>                 <a href="ident?i=tcp_try_keep_open">tcp_try_keep_open</a>(sk);
<a name="L2772" href="source/net/ipv4/tcp_input.c#L2772">2772</a>                 return <a href="ident?i=true">true</a>;
<a name="L2773" href="source/net/ipv4/tcp_input.c#L2773">2773</a>         }
<a name="L2774" href="source/net/ipv4/tcp_input.c#L2774">2774</a>         return <a href="ident?i=false">false</a>;
<a name="L2775" href="source/net/ipv4/tcp_input.c#L2775">2775</a> }
<a name="L2776" href="source/net/ipv4/tcp_input.c#L2776">2776</a> 
<a name="L2777" href="source/net/ipv4/tcp_input.c#L2777">2777</a> <b><i>/* Process an event, which can update packets-in-flight not trivially.</i></b>
<a name="L2778" href="source/net/ipv4/tcp_input.c#L2778">2778</a> <b><i> * Main goal of this function is to calculate new estimate for left_out,</i></b>
<a name="L2779" href="source/net/ipv4/tcp_input.c#L2779">2779</a> <b><i> * taking into account both packets sitting in receiver's buffer and</i></b>
<a name="L2780" href="source/net/ipv4/tcp_input.c#L2780">2780</a> <b><i> * packets lost by network.</i></b>
<a name="L2781" href="source/net/ipv4/tcp_input.c#L2781">2781</a> <b><i> *</i></b>
<a name="L2782" href="source/net/ipv4/tcp_input.c#L2782">2782</a> <b><i> * Besides that it does CWND reduction, when packet loss is detected</i></b>
<a name="L2783" href="source/net/ipv4/tcp_input.c#L2783">2783</a> <b><i> * and changes state of machine.</i></b>
<a name="L2784" href="source/net/ipv4/tcp_input.c#L2784">2784</a> <b><i> *</i></b>
<a name="L2785" href="source/net/ipv4/tcp_input.c#L2785">2785</a> <b><i> * It does _not_ decide what to send, it is made in function</i></b>
<a name="L2786" href="source/net/ipv4/tcp_input.c#L2786">2786</a> <b><i> * tcp_xmit_retransmit_queue().</i></b>
<a name="L2787" href="source/net/ipv4/tcp_input.c#L2787">2787</a> <b><i> */</i></b>
<a name="L2788" href="source/net/ipv4/tcp_input.c#L2788">2788</a> static void <a href="ident?i=tcp_fastretrans_alert">tcp_fastretrans_alert</a>(struct <a href="ident?i=sock">sock</a> *sk, const int acked,
<a name="L2789" href="source/net/ipv4/tcp_input.c#L2789">2789</a>                                   const int prior_unsacked,
<a name="L2790" href="source/net/ipv4/tcp_input.c#L2790">2790</a>                                   <a href="ident?i=bool">bool</a> is_dupack, int <a href="ident?i=flag">flag</a>)
<a name="L2791" href="source/net/ipv4/tcp_input.c#L2791">2791</a> {
<a name="L2792" href="source/net/ipv4/tcp_input.c#L2792">2792</a>         struct <a href="ident?i=inet_connection_sock">inet_connection_sock</a> *icsk = <a href="ident?i=inet_csk">inet_csk</a>(sk);
<a name="L2793" href="source/net/ipv4/tcp_input.c#L2793">2793</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L2794" href="source/net/ipv4/tcp_input.c#L2794">2794</a>         <a href="ident?i=bool">bool</a> do_lost = is_dupack || ((<a href="ident?i=flag">flag</a> &amp; <a href="ident?i=FLAG_DATA_SACKED">FLAG_DATA_SACKED</a>) &amp;&amp;
<a name="L2795" href="source/net/ipv4/tcp_input.c#L2795">2795</a>                                     (<a href="ident?i=tcp_fackets_out">tcp_fackets_out</a>(<a href="ident?i=tp">tp</a>) &gt; <a href="ident?i=tp">tp</a>-&gt;reordering));
<a name="L2796" href="source/net/ipv4/tcp_input.c#L2796">2796</a>         int fast_rexmit = 0;
<a name="L2797" href="source/net/ipv4/tcp_input.c#L2797">2797</a> 
<a name="L2798" href="source/net/ipv4/tcp_input.c#L2798">2798</a>         if (<a href="ident?i=WARN_ON">WARN_ON</a>(!<a href="ident?i=tp">tp</a>-&gt;packets_out &amp;&amp; <a href="ident?i=tp">tp</a>-&gt;sacked_out))
<a name="L2799" href="source/net/ipv4/tcp_input.c#L2799">2799</a>                 <a href="ident?i=tp">tp</a>-&gt;sacked_out = 0;
<a name="L2800" href="source/net/ipv4/tcp_input.c#L2800">2800</a>         if (<a href="ident?i=WARN_ON">WARN_ON</a>(!<a href="ident?i=tp">tp</a>-&gt;sacked_out &amp;&amp; <a href="ident?i=tp">tp</a>-&gt;fackets_out))
<a name="L2801" href="source/net/ipv4/tcp_input.c#L2801">2801</a>                 <a href="ident?i=tp">tp</a>-&gt;fackets_out = 0;
<a name="L2802" href="source/net/ipv4/tcp_input.c#L2802">2802</a> 
<a name="L2803" href="source/net/ipv4/tcp_input.c#L2803">2803</a>         <b><i>/* Now state machine starts.</i></b>
<a name="L2804" href="source/net/ipv4/tcp_input.c#L2804">2804</a> <b><i>         * A. ECE, hence prohibit cwnd undoing, the reduction is required. */</i></b>
<a name="L2805" href="source/net/ipv4/tcp_input.c#L2805">2805</a>         if (<a href="ident?i=flag">flag</a> &amp; <a href="ident?i=FLAG_ECE">FLAG_ECE</a>)
<a name="L2806" href="source/net/ipv4/tcp_input.c#L2806">2806</a>                 <a href="ident?i=tp">tp</a>-&gt;prior_ssthresh = 0;
<a name="L2807" href="source/net/ipv4/tcp_input.c#L2807">2807</a> 
<a name="L2808" href="source/net/ipv4/tcp_input.c#L2808">2808</a>         <b><i>/* B. In all the states check for reneging SACKs. */</i></b>
<a name="L2809" href="source/net/ipv4/tcp_input.c#L2809">2809</a>         if (<a href="ident?i=tcp_check_sack_reneging">tcp_check_sack_reneging</a>(sk, <a href="ident?i=flag">flag</a>))
<a name="L2810" href="source/net/ipv4/tcp_input.c#L2810">2810</a>                 return;
<a name="L2811" href="source/net/ipv4/tcp_input.c#L2811">2811</a> 
<a name="L2812" href="source/net/ipv4/tcp_input.c#L2812">2812</a>         <b><i>/* C. Check consistency of the current state. */</i></b>
<a name="L2813" href="source/net/ipv4/tcp_input.c#L2813">2813</a>         <a href="ident?i=tcp_verify_left_out">tcp_verify_left_out</a>(<a href="ident?i=tp">tp</a>);
<a name="L2814" href="source/net/ipv4/tcp_input.c#L2814">2814</a> 
<a name="L2815" href="source/net/ipv4/tcp_input.c#L2815">2815</a>         <b><i>/* D. Check state exit conditions. State can be terminated</i></b>
<a name="L2816" href="source/net/ipv4/tcp_input.c#L2816">2816</a> <b><i>         *    when high_seq is ACKed. */</i></b>
<a name="L2817" href="source/net/ipv4/tcp_input.c#L2817">2817</a>         if (icsk-&gt;icsk_ca_state == TCP_CA_Open) {
<a name="L2818" href="source/net/ipv4/tcp_input.c#L2818">2818</a>                 <a href="ident?i=WARN_ON">WARN_ON</a>(<a href="ident?i=tp">tp</a>-&gt;retrans_out != 0);
<a name="L2819" href="source/net/ipv4/tcp_input.c#L2819">2819</a>                 <a href="ident?i=tp">tp</a>-&gt;retrans_stamp = 0;
<a name="L2820" href="source/net/ipv4/tcp_input.c#L2820">2820</a>         } else if (!<a href="ident?i=before">before</a>(<a href="ident?i=tp">tp</a>-&gt;snd_una, <a href="ident?i=tp">tp</a>-&gt;high_seq)) {
<a name="L2821" href="source/net/ipv4/tcp_input.c#L2821">2821</a>                 switch (icsk-&gt;icsk_ca_state) {
<a name="L2822" href="source/net/ipv4/tcp_input.c#L2822">2822</a>                 case TCP_CA_CWR:
<a name="L2823" href="source/net/ipv4/tcp_input.c#L2823">2823</a>                         <b><i>/* CWR is to be held something *above* high_seq</i></b>
<a name="L2824" href="source/net/ipv4/tcp_input.c#L2824">2824</a> <b><i>                         * is ACKed for CWR bit to reach receiver. */</i></b>
<a name="L2825" href="source/net/ipv4/tcp_input.c#L2825">2825</a>                         if (<a href="ident?i=tp">tp</a>-&gt;snd_una != <a href="ident?i=tp">tp</a>-&gt;high_seq) {
<a name="L2826" href="source/net/ipv4/tcp_input.c#L2826">2826</a>                                 <a href="ident?i=tcp_end_cwnd_reduction">tcp_end_cwnd_reduction</a>(sk);
<a name="L2827" href="source/net/ipv4/tcp_input.c#L2827">2827</a>                                 <a href="ident?i=tcp_set_ca_state">tcp_set_ca_state</a>(sk, TCP_CA_Open);
<a name="L2828" href="source/net/ipv4/tcp_input.c#L2828">2828</a>                         }
<a name="L2829" href="source/net/ipv4/tcp_input.c#L2829">2829</a>                         break;
<a name="L2830" href="source/net/ipv4/tcp_input.c#L2830">2830</a> 
<a name="L2831" href="source/net/ipv4/tcp_input.c#L2831">2831</a>                 case TCP_CA_Recovery:
<a name="L2832" href="source/net/ipv4/tcp_input.c#L2832">2832</a>                         if (<a href="ident?i=tcp_is_reno">tcp_is_reno</a>(<a href="ident?i=tp">tp</a>))
<a name="L2833" href="source/net/ipv4/tcp_input.c#L2833">2833</a>                                 <a href="ident?i=tcp_reset_reno_sack">tcp_reset_reno_sack</a>(<a href="ident?i=tp">tp</a>);
<a name="L2834" href="source/net/ipv4/tcp_input.c#L2834">2834</a>                         if (<a href="ident?i=tcp_try_undo_recovery">tcp_try_undo_recovery</a>(sk))
<a name="L2835" href="source/net/ipv4/tcp_input.c#L2835">2835</a>                                 return;
<a name="L2836" href="source/net/ipv4/tcp_input.c#L2836">2836</a>                         <a href="ident?i=tcp_end_cwnd_reduction">tcp_end_cwnd_reduction</a>(sk);
<a name="L2837" href="source/net/ipv4/tcp_input.c#L2837">2837</a>                         break;
<a name="L2838" href="source/net/ipv4/tcp_input.c#L2838">2838</a>                 }
<a name="L2839" href="source/net/ipv4/tcp_input.c#L2839">2839</a>         }
<a name="L2840" href="source/net/ipv4/tcp_input.c#L2840">2840</a> 
<a name="L2841" href="source/net/ipv4/tcp_input.c#L2841">2841</a>         <b><i>/* E. Process state. */</i></b>
<a name="L2842" href="source/net/ipv4/tcp_input.c#L2842">2842</a>         switch (icsk-&gt;icsk_ca_state) {
<a name="L2843" href="source/net/ipv4/tcp_input.c#L2843">2843</a>         case TCP_CA_Recovery:
<a name="L2844" href="source/net/ipv4/tcp_input.c#L2844">2844</a>                 if (!(<a href="ident?i=flag">flag</a> &amp; <a href="ident?i=FLAG_SND_UNA_ADVANCED">FLAG_SND_UNA_ADVANCED</a>)) {
<a name="L2845" href="source/net/ipv4/tcp_input.c#L2845">2845</a>                         if (<a href="ident?i=tcp_is_reno">tcp_is_reno</a>(<a href="ident?i=tp">tp</a>) &amp;&amp; is_dupack)
<a name="L2846" href="source/net/ipv4/tcp_input.c#L2846">2846</a>                                 <a href="ident?i=tcp_add_reno_sack">tcp_add_reno_sack</a>(sk);
<a name="L2847" href="source/net/ipv4/tcp_input.c#L2847">2847</a>                 } else {
<a name="L2848" href="source/net/ipv4/tcp_input.c#L2848">2848</a>                         if (<a href="ident?i=tcp_try_undo_partial">tcp_try_undo_partial</a>(sk, acked, prior_unsacked))
<a name="L2849" href="source/net/ipv4/tcp_input.c#L2849">2849</a>                                 return;
<a name="L2850" href="source/net/ipv4/tcp_input.c#L2850">2850</a>                         <b><i>/* Partial ACK arrived. Force fast retransmit. */</i></b>
<a name="L2851" href="source/net/ipv4/tcp_input.c#L2851">2851</a>                         do_lost = <a href="ident?i=tcp_is_reno">tcp_is_reno</a>(<a href="ident?i=tp">tp</a>) ||
<a name="L2852" href="source/net/ipv4/tcp_input.c#L2852">2852</a>                                   <a href="ident?i=tcp_fackets_out">tcp_fackets_out</a>(<a href="ident?i=tp">tp</a>) &gt; <a href="ident?i=tp">tp</a>-&gt;reordering;
<a name="L2853" href="source/net/ipv4/tcp_input.c#L2853">2853</a>                 }
<a name="L2854" href="source/net/ipv4/tcp_input.c#L2854">2854</a>                 if (<a href="ident?i=tcp_try_undo_dsack">tcp_try_undo_dsack</a>(sk)) {
<a name="L2855" href="source/net/ipv4/tcp_input.c#L2855">2855</a>                         <a href="ident?i=tcp_try_keep_open">tcp_try_keep_open</a>(sk);
<a name="L2856" href="source/net/ipv4/tcp_input.c#L2856">2856</a>                         return;
<a name="L2857" href="source/net/ipv4/tcp_input.c#L2857">2857</a>                 }
<a name="L2858" href="source/net/ipv4/tcp_input.c#L2858">2858</a>                 break;
<a name="L2859" href="source/net/ipv4/tcp_input.c#L2859">2859</a>         case TCP_CA_Loss:
<a name="L2860" href="source/net/ipv4/tcp_input.c#L2860">2860</a>                 <a href="ident?i=tcp_process_loss">tcp_process_loss</a>(sk, <a href="ident?i=flag">flag</a>, is_dupack);
<a name="L2861" href="source/net/ipv4/tcp_input.c#L2861">2861</a>                 if (icsk-&gt;icsk_ca_state != TCP_CA_Open)
<a name="L2862" href="source/net/ipv4/tcp_input.c#L2862">2862</a>                         return;
<a name="L2863" href="source/net/ipv4/tcp_input.c#L2863">2863</a>                 <b><i>/* Fall through to processing in Open state. */</i></b>
<a name="L2864" href="source/net/ipv4/tcp_input.c#L2864">2864</a>         default:
<a name="L2865" href="source/net/ipv4/tcp_input.c#L2865">2865</a>                 if (<a href="ident?i=tcp_is_reno">tcp_is_reno</a>(<a href="ident?i=tp">tp</a>)) {
<a name="L2866" href="source/net/ipv4/tcp_input.c#L2866">2866</a>                         if (<a href="ident?i=flag">flag</a> &amp; <a href="ident?i=FLAG_SND_UNA_ADVANCED">FLAG_SND_UNA_ADVANCED</a>)
<a name="L2867" href="source/net/ipv4/tcp_input.c#L2867">2867</a>                                 <a href="ident?i=tcp_reset_reno_sack">tcp_reset_reno_sack</a>(<a href="ident?i=tp">tp</a>);
<a name="L2868" href="source/net/ipv4/tcp_input.c#L2868">2868</a>                         if (is_dupack)
<a name="L2869" href="source/net/ipv4/tcp_input.c#L2869">2869</a>                                 <a href="ident?i=tcp_add_reno_sack">tcp_add_reno_sack</a>(sk);
<a name="L2870" href="source/net/ipv4/tcp_input.c#L2870">2870</a>                 }
<a name="L2871" href="source/net/ipv4/tcp_input.c#L2871">2871</a> 
<a name="L2872" href="source/net/ipv4/tcp_input.c#L2872">2872</a>                 if (icsk-&gt;icsk_ca_state &lt;= TCP_CA_Disorder)
<a name="L2873" href="source/net/ipv4/tcp_input.c#L2873">2873</a>                         <a href="ident?i=tcp_try_undo_dsack">tcp_try_undo_dsack</a>(sk);
<a name="L2874" href="source/net/ipv4/tcp_input.c#L2874">2874</a> 
<a name="L2875" href="source/net/ipv4/tcp_input.c#L2875">2875</a>                 if (!<a href="ident?i=tcp_time_to_recover">tcp_time_to_recover</a>(sk, <a href="ident?i=flag">flag</a>)) {
<a name="L2876" href="source/net/ipv4/tcp_input.c#L2876">2876</a>                         <a href="ident?i=tcp_try_to_open">tcp_try_to_open</a>(sk, <a href="ident?i=flag">flag</a>, prior_unsacked);
<a name="L2877" href="source/net/ipv4/tcp_input.c#L2877">2877</a>                         return;
<a name="L2878" href="source/net/ipv4/tcp_input.c#L2878">2878</a>                 }
<a name="L2879" href="source/net/ipv4/tcp_input.c#L2879">2879</a> 
<a name="L2880" href="source/net/ipv4/tcp_input.c#L2880">2880</a>                 <b><i>/* MTU probe failure: don't reduce cwnd */</i></b>
<a name="L2881" href="source/net/ipv4/tcp_input.c#L2881">2881</a>                 if (icsk-&gt;icsk_ca_state &lt; TCP_CA_CWR &amp;&amp;
<a name="L2882" href="source/net/ipv4/tcp_input.c#L2882">2882</a>                     icsk-&gt;icsk_mtup.probe_size &amp;&amp;
<a name="L2883" href="source/net/ipv4/tcp_input.c#L2883">2883</a>                     <a href="ident?i=tp">tp</a>-&gt;snd_una == <a href="ident?i=tp">tp</a>-&gt;mtu_probe.probe_seq_start) {
<a name="L2884" href="source/net/ipv4/tcp_input.c#L2884">2884</a>                         <a href="ident?i=tcp_mtup_probe_failed">tcp_mtup_probe_failed</a>(sk);
<a name="L2885" href="source/net/ipv4/tcp_input.c#L2885">2885</a>                         <b><i>/* Restores the reduction we did in tcp_mtup_probe() */</i></b>
<a name="L2886" href="source/net/ipv4/tcp_input.c#L2886">2886</a>                         <a href="ident?i=tp">tp</a>-&gt;snd_cwnd++;
<a name="L2887" href="source/net/ipv4/tcp_input.c#L2887">2887</a>                         <a href="ident?i=tcp_simple_retransmit">tcp_simple_retransmit</a>(sk);
<a name="L2888" href="source/net/ipv4/tcp_input.c#L2888">2888</a>                         return;
<a name="L2889" href="source/net/ipv4/tcp_input.c#L2889">2889</a>                 }
<a name="L2890" href="source/net/ipv4/tcp_input.c#L2890">2890</a> 
<a name="L2891" href="source/net/ipv4/tcp_input.c#L2891">2891</a>                 <b><i>/* Otherwise enter Recovery state */</i></b>
<a name="L2892" href="source/net/ipv4/tcp_input.c#L2892">2892</a>                 <a href="ident?i=tcp_enter_recovery">tcp_enter_recovery</a>(sk, (<a href="ident?i=flag">flag</a> &amp; <a href="ident?i=FLAG_ECE">FLAG_ECE</a>));
<a name="L2893" href="source/net/ipv4/tcp_input.c#L2893">2893</a>                 fast_rexmit = 1;
<a name="L2894" href="source/net/ipv4/tcp_input.c#L2894">2894</a>         }
<a name="L2895" href="source/net/ipv4/tcp_input.c#L2895">2895</a> 
<a name="L2896" href="source/net/ipv4/tcp_input.c#L2896">2896</a>         if (do_lost)
<a name="L2897" href="source/net/ipv4/tcp_input.c#L2897">2897</a>                 <a href="ident?i=tcp_update_scoreboard">tcp_update_scoreboard</a>(sk, fast_rexmit);
<a name="L2898" href="source/net/ipv4/tcp_input.c#L2898">2898</a>         <a href="ident?i=tcp_cwnd_reduction">tcp_cwnd_reduction</a>(sk, prior_unsacked, fast_rexmit);
<a name="L2899" href="source/net/ipv4/tcp_input.c#L2899">2899</a>         <a href="ident?i=tcp_xmit_retransmit_queue">tcp_xmit_retransmit_queue</a>(sk);
<a name="L2900" href="source/net/ipv4/tcp_input.c#L2900">2900</a> }
<a name="L2901" href="source/net/ipv4/tcp_input.c#L2901">2901</a> 
<a name="L2902" href="source/net/ipv4/tcp_input.c#L2902">2902</a> static inline <a href="ident?i=bool">bool</a> <a href="ident?i=tcp_ack_update_rtt">tcp_ack_update_rtt</a>(struct <a href="ident?i=sock">sock</a> *sk, const int <a href="ident?i=flag">flag</a>,
<a name="L2903" href="source/net/ipv4/tcp_input.c#L2903">2903</a>                                       long seq_rtt_us, long sack_rtt_us)
<a name="L2904" href="source/net/ipv4/tcp_input.c#L2904">2904</a> {
<a name="L2905" href="source/net/ipv4/tcp_input.c#L2905">2905</a>         const struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L2906" href="source/net/ipv4/tcp_input.c#L2906">2906</a> 
<a name="L2907" href="source/net/ipv4/tcp_input.c#L2907">2907</a>         <b><i>/* Prefer RTT measured from ACK's timing to TS-ECR. This is because</i></b>
<a name="L2908" href="source/net/ipv4/tcp_input.c#L2908">2908</a> <b><i>         * broken middle-boxes or peers may corrupt TS-ECR fields. But</i></b>
<a name="L2909" href="source/net/ipv4/tcp_input.c#L2909">2909</a> <b><i>         * Karn's algorithm forbids taking RTT if some retransmitted data</i></b>
<a name="L2910" href="source/net/ipv4/tcp_input.c#L2910">2910</a> <b><i>         * is acked (RFC6298).</i></b>
<a name="L2911" href="source/net/ipv4/tcp_input.c#L2911">2911</a> <b><i>         */</i></b>
<a name="L2912" href="source/net/ipv4/tcp_input.c#L2912">2912</a>         if (<a href="ident?i=flag">flag</a> &amp; <a href="ident?i=FLAG_RETRANS_DATA_ACKED">FLAG_RETRANS_DATA_ACKED</a>)
<a name="L2913" href="source/net/ipv4/tcp_input.c#L2913">2913</a>                 seq_rtt_us = -1L;
<a name="L2914" href="source/net/ipv4/tcp_input.c#L2914">2914</a> 
<a name="L2915" href="source/net/ipv4/tcp_input.c#L2915">2915</a>         if (seq_rtt_us &lt; 0)
<a name="L2916" href="source/net/ipv4/tcp_input.c#L2916">2916</a>                 seq_rtt_us = sack_rtt_us;
<a name="L2917" href="source/net/ipv4/tcp_input.c#L2917">2917</a> 
<a name="L2918" href="source/net/ipv4/tcp_input.c#L2918">2918</a>         <b><i>/* RTTM Rule: A TSecr value received in a segment is used to</i></b>
<a name="L2919" href="source/net/ipv4/tcp_input.c#L2919">2919</a> <b><i>         * update the averaged RTT measurement only if the segment</i></b>
<a name="L2920" href="source/net/ipv4/tcp_input.c#L2920">2920</a> <b><i>         * acknowledges some new data, i.e., only if it advances the</i></b>
<a name="L2921" href="source/net/ipv4/tcp_input.c#L2921">2921</a> <b><i>         * left edge of the send window.</i></b>
<a name="L2922" href="source/net/ipv4/tcp_input.c#L2922">2922</a> <b><i>         * See draft-ietf-tcplw-high-performance-00, section 3.3.</i></b>
<a name="L2923" href="source/net/ipv4/tcp_input.c#L2923">2923</a> <b><i>         */</i></b>
<a name="L2924" href="source/net/ipv4/tcp_input.c#L2924">2924</a>         if (seq_rtt_us &lt; 0 &amp;&amp; <a href="ident?i=tp">tp</a>-&gt;rx_opt.saw_tstamp &amp;&amp; <a href="ident?i=tp">tp</a>-&gt;rx_opt.rcv_tsecr &amp;&amp;
<a name="L2925" href="source/net/ipv4/tcp_input.c#L2925">2925</a>             <a href="ident?i=flag">flag</a> &amp; <a href="ident?i=FLAG_ACKED">FLAG_ACKED</a>)
<a name="L2926" href="source/net/ipv4/tcp_input.c#L2926">2926</a>                 seq_rtt_us = <a href="ident?i=jiffies_to_usecs">jiffies_to_usecs</a>(<a href="ident?i=tcp_time_stamp">tcp_time_stamp</a> - <a href="ident?i=tp">tp</a>-&gt;rx_opt.rcv_tsecr);
<a name="L2927" href="source/net/ipv4/tcp_input.c#L2927">2927</a> 
<a name="L2928" href="source/net/ipv4/tcp_input.c#L2928">2928</a>         if (seq_rtt_us &lt; 0)
<a name="L2929" href="source/net/ipv4/tcp_input.c#L2929">2929</a>                 return <a href="ident?i=false">false</a>;
<a name="L2930" href="source/net/ipv4/tcp_input.c#L2930">2930</a> 
<a name="L2931" href="source/net/ipv4/tcp_input.c#L2931">2931</a>         <a href="ident?i=tcp_rtt_estimator">tcp_rtt_estimator</a>(sk, seq_rtt_us);
<a name="L2932" href="source/net/ipv4/tcp_input.c#L2932">2932</a>         <a href="ident?i=tcp_set_rto">tcp_set_rto</a>(sk);
<a name="L2933" href="source/net/ipv4/tcp_input.c#L2933">2933</a> 
<a name="L2934" href="source/net/ipv4/tcp_input.c#L2934">2934</a>         <b><i>/* RFC6298: only reset backoff on valid RTT measurement. */</i></b>
<a name="L2935" href="source/net/ipv4/tcp_input.c#L2935">2935</a>         <a href="ident?i=inet_csk">inet_csk</a>(sk)-&gt;icsk_backoff = 0;
<a name="L2936" href="source/net/ipv4/tcp_input.c#L2936">2936</a>         return <a href="ident?i=true">true</a>;
<a name="L2937" href="source/net/ipv4/tcp_input.c#L2937">2937</a> }
<a name="L2938" href="source/net/ipv4/tcp_input.c#L2938">2938</a> 
<a name="L2939" href="source/net/ipv4/tcp_input.c#L2939">2939</a> <b><i>/* Compute time elapsed between (last) SYNACK and the ACK completing 3WHS. */</i></b>
<a name="L2940" href="source/net/ipv4/tcp_input.c#L2940">2940</a> static void <a href="ident?i=tcp_synack_rtt_meas">tcp_synack_rtt_meas</a>(struct <a href="ident?i=sock">sock</a> *sk, const <a href="ident?i=u32">u32</a> synack_stamp)
<a name="L2941" href="source/net/ipv4/tcp_input.c#L2941">2941</a> {
<a name="L2942" href="source/net/ipv4/tcp_input.c#L2942">2942</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L2943" href="source/net/ipv4/tcp_input.c#L2943">2943</a>         long seq_rtt_us = -1L;
<a name="L2944" href="source/net/ipv4/tcp_input.c#L2944">2944</a> 
<a name="L2945" href="source/net/ipv4/tcp_input.c#L2945">2945</a>         if (synack_stamp &amp;&amp; !<a href="ident?i=tp">tp</a>-&gt;total_retrans)
<a name="L2946" href="source/net/ipv4/tcp_input.c#L2946">2946</a>                 seq_rtt_us = <a href="ident?i=jiffies_to_usecs">jiffies_to_usecs</a>(<a href="ident?i=tcp_time_stamp">tcp_time_stamp</a> - synack_stamp);
<a name="L2947" href="source/net/ipv4/tcp_input.c#L2947">2947</a> 
<a name="L2948" href="source/net/ipv4/tcp_input.c#L2948">2948</a>         <b><i>/* If the ACK acks both the SYNACK and the (Fast Open'd) data packets</i></b>
<a name="L2949" href="source/net/ipv4/tcp_input.c#L2949">2949</a> <b><i>         * sent in SYN_RECV, SYNACK RTT is the smooth RTT computed in tcp_ack()</i></b>
<a name="L2950" href="source/net/ipv4/tcp_input.c#L2950">2950</a> <b><i>         */</i></b>
<a name="L2951" href="source/net/ipv4/tcp_input.c#L2951">2951</a>         if (!<a href="ident?i=tp">tp</a>-&gt;srtt_us)
<a name="L2952" href="source/net/ipv4/tcp_input.c#L2952">2952</a>                 <a href="ident?i=tcp_ack_update_rtt">tcp_ack_update_rtt</a>(sk, <a href="ident?i=FLAG_SYN_ACKED">FLAG_SYN_ACKED</a>, seq_rtt_us, -1L);
<a name="L2953" href="source/net/ipv4/tcp_input.c#L2953">2953</a> }
<a name="L2954" href="source/net/ipv4/tcp_input.c#L2954">2954</a> 
<a name="L2955" href="source/net/ipv4/tcp_input.c#L2955">2955</a> static void <a href="ident?i=tcp_cong_avoid">tcp_cong_avoid</a>(struct <a href="ident?i=sock">sock</a> *sk, <a href="ident?i=u32">u32</a> ack, <a href="ident?i=u32">u32</a> acked)
<a name="L2956" href="source/net/ipv4/tcp_input.c#L2956">2956</a> {
<a name="L2957" href="source/net/ipv4/tcp_input.c#L2957">2957</a>         const struct <a href="ident?i=inet_connection_sock">inet_connection_sock</a> *icsk = <a href="ident?i=inet_csk">inet_csk</a>(sk);
<a name="L2958" href="source/net/ipv4/tcp_input.c#L2958">2958</a> 
<a name="L2959" href="source/net/ipv4/tcp_input.c#L2959">2959</a>         icsk-&gt;icsk_ca_ops-&gt;cong_avoid(sk, ack, acked);
<a name="L2960" href="source/net/ipv4/tcp_input.c#L2960">2960</a>         <a href="ident?i=tcp_sk">tcp_sk</a>(sk)-&gt;snd_cwnd_stamp = <a href="ident?i=tcp_time_stamp">tcp_time_stamp</a>;
<a name="L2961" href="source/net/ipv4/tcp_input.c#L2961">2961</a> }
<a name="L2962" href="source/net/ipv4/tcp_input.c#L2962">2962</a> 
<a name="L2963" href="source/net/ipv4/tcp_input.c#L2963">2963</a> <b><i>/* Restart timer after forward progress on connection.</i></b>
<a name="L2964" href="source/net/ipv4/tcp_input.c#L2964">2964</a> <b><i> * RFC2988 recommends to restart timer to now+rto.</i></b>
<a name="L2965" href="source/net/ipv4/tcp_input.c#L2965">2965</a> <b><i> */</i></b>
<a name="L2966" href="source/net/ipv4/tcp_input.c#L2966">2966</a> void <a href="ident?i=tcp_rearm_rto">tcp_rearm_rto</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L2967" href="source/net/ipv4/tcp_input.c#L2967">2967</a> {
<a name="L2968" href="source/net/ipv4/tcp_input.c#L2968">2968</a>         const struct <a href="ident?i=inet_connection_sock">inet_connection_sock</a> *icsk = <a href="ident?i=inet_csk">inet_csk</a>(sk);
<a name="L2969" href="source/net/ipv4/tcp_input.c#L2969">2969</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L2970" href="source/net/ipv4/tcp_input.c#L2970">2970</a> 
<a name="L2971" href="source/net/ipv4/tcp_input.c#L2971">2971</a>         <b><i>/* If the retrans timer is currently being used by Fast Open</i></b>
<a name="L2972" href="source/net/ipv4/tcp_input.c#L2972">2972</a> <b><i>         * for SYN-ACK retrans purpose, stay put.</i></b>
<a name="L2973" href="source/net/ipv4/tcp_input.c#L2973">2973</a> <b><i>         */</i></b>
<a name="L2974" href="source/net/ipv4/tcp_input.c#L2974">2974</a>         if (<a href="ident?i=tp">tp</a>-&gt;fastopen_rsk)
<a name="L2975" href="source/net/ipv4/tcp_input.c#L2975">2975</a>                 return;
<a name="L2976" href="source/net/ipv4/tcp_input.c#L2976">2976</a> 
<a name="L2977" href="source/net/ipv4/tcp_input.c#L2977">2977</a>         if (!<a href="ident?i=tp">tp</a>-&gt;packets_out) {
<a name="L2978" href="source/net/ipv4/tcp_input.c#L2978">2978</a>                 <a href="ident?i=inet_csk_clear_xmit_timer">inet_csk_clear_xmit_timer</a>(sk, <a href="ident?i=ICSK_TIME_RETRANS">ICSK_TIME_RETRANS</a>);
<a name="L2979" href="source/net/ipv4/tcp_input.c#L2979">2979</a>         } else {
<a name="L2980" href="source/net/ipv4/tcp_input.c#L2980">2980</a>                 <a href="ident?i=u32">u32</a> <a href="ident?i=rto">rto</a> = <a href="ident?i=inet_csk">inet_csk</a>(sk)-&gt;icsk_rto;
<a name="L2981" href="source/net/ipv4/tcp_input.c#L2981">2981</a>                 <b><i>/* Offset the time elapsed after installing regular RTO */</i></b>
<a name="L2982" href="source/net/ipv4/tcp_input.c#L2982">2982</a>                 if (icsk-&gt;icsk_pending == <a href="ident?i=ICSK_TIME_EARLY_RETRANS">ICSK_TIME_EARLY_RETRANS</a> ||
<a name="L2983" href="source/net/ipv4/tcp_input.c#L2983">2983</a>                     icsk-&gt;icsk_pending == <a href="ident?i=ICSK_TIME_LOSS_PROBE">ICSK_TIME_LOSS_PROBE</a>) {
<a name="L2984" href="source/net/ipv4/tcp_input.c#L2984">2984</a>                         struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a> = <a href="ident?i=tcp_write_queue_head">tcp_write_queue_head</a>(sk);
<a name="L2985" href="source/net/ipv4/tcp_input.c#L2985">2985</a>                         const <a href="ident?i=u32">u32</a> rto_time_stamp =
<a name="L2986" href="source/net/ipv4/tcp_input.c#L2986">2986</a>                                 <a href="ident?i=tcp_skb_timestamp">tcp_skb_timestamp</a>(<a href="ident?i=skb">skb</a>) + <a href="ident?i=rto">rto</a>;
<a name="L2987" href="source/net/ipv4/tcp_input.c#L2987">2987</a>                         <a href="ident?i=s32">s32</a> <a href="ident?i=delta">delta</a> = (<a href="ident?i=s32">s32</a>)(rto_time_stamp - <a href="ident?i=tcp_time_stamp">tcp_time_stamp</a>);
<a name="L2988" href="source/net/ipv4/tcp_input.c#L2988">2988</a>                         <b><i>/* delta may not be positive if the socket is locked</i></b>
<a name="L2989" href="source/net/ipv4/tcp_input.c#L2989">2989</a> <b><i>                         * when the retrans timer fires and is rescheduled.</i></b>
<a name="L2990" href="source/net/ipv4/tcp_input.c#L2990">2990</a> <b><i>                         */</i></b>
<a name="L2991" href="source/net/ipv4/tcp_input.c#L2991">2991</a>                         if (<a href="ident?i=delta">delta</a> &gt; 0)
<a name="L2992" href="source/net/ipv4/tcp_input.c#L2992">2992</a>                                 <a href="ident?i=rto">rto</a> = <a href="ident?i=delta">delta</a>;
<a name="L2993" href="source/net/ipv4/tcp_input.c#L2993">2993</a>                 }
<a name="L2994" href="source/net/ipv4/tcp_input.c#L2994">2994</a>                 <a href="ident?i=inet_csk_reset_xmit_timer">inet_csk_reset_xmit_timer</a>(sk, <a href="ident?i=ICSK_TIME_RETRANS">ICSK_TIME_RETRANS</a>, <a href="ident?i=rto">rto</a>,
<a name="L2995" href="source/net/ipv4/tcp_input.c#L2995">2995</a>                                           <a href="ident?i=TCP_RTO_MAX">TCP_RTO_MAX</a>);
<a name="L2996" href="source/net/ipv4/tcp_input.c#L2996">2996</a>         }
<a name="L2997" href="source/net/ipv4/tcp_input.c#L2997">2997</a> }
<a name="L2998" href="source/net/ipv4/tcp_input.c#L2998">2998</a> 
<a name="L2999" href="source/net/ipv4/tcp_input.c#L2999">2999</a> <b><i>/* This function is called when the delayed ER timer fires. TCP enters</i></b>
<a name="L3000" href="source/net/ipv4/tcp_input.c#L3000">3000</a> <b><i> * fast recovery and performs fast-retransmit.</i></b>
<a name="L3001" href="source/net/ipv4/tcp_input.c#L3001">3001</a> <b><i> */</i></b>
<a name="L3002" href="source/net/ipv4/tcp_input.c#L3002">3002</a> void <a href="ident?i=tcp_resume_early_retransmit">tcp_resume_early_retransmit</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L3003" href="source/net/ipv4/tcp_input.c#L3003">3003</a> {
<a name="L3004" href="source/net/ipv4/tcp_input.c#L3004">3004</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L3005" href="source/net/ipv4/tcp_input.c#L3005">3005</a> 
<a name="L3006" href="source/net/ipv4/tcp_input.c#L3006">3006</a>         <a href="ident?i=tcp_rearm_rto">tcp_rearm_rto</a>(sk);
<a name="L3007" href="source/net/ipv4/tcp_input.c#L3007">3007</a> 
<a name="L3008" href="source/net/ipv4/tcp_input.c#L3008">3008</a>         <b><i>/* Stop if ER is disabled after the delayed ER timer is scheduled */</i></b>
<a name="L3009" href="source/net/ipv4/tcp_input.c#L3009">3009</a>         if (!<a href="ident?i=tp">tp</a>-&gt;do_early_retrans)
<a name="L3010" href="source/net/ipv4/tcp_input.c#L3010">3010</a>                 return;
<a name="L3011" href="source/net/ipv4/tcp_input.c#L3011">3011</a> 
<a name="L3012" href="source/net/ipv4/tcp_input.c#L3012">3012</a>         <a href="ident?i=tcp_enter_recovery">tcp_enter_recovery</a>(sk, <a href="ident?i=false">false</a>);
<a name="L3013" href="source/net/ipv4/tcp_input.c#L3013">3013</a>         <a href="ident?i=tcp_update_scoreboard">tcp_update_scoreboard</a>(sk, 1);
<a name="L3014" href="source/net/ipv4/tcp_input.c#L3014">3014</a>         <a href="ident?i=tcp_xmit_retransmit_queue">tcp_xmit_retransmit_queue</a>(sk);
<a name="L3015" href="source/net/ipv4/tcp_input.c#L3015">3015</a> }
<a name="L3016" href="source/net/ipv4/tcp_input.c#L3016">3016</a> 
<a name="L3017" href="source/net/ipv4/tcp_input.c#L3017">3017</a> <b><i>/* If we get here, the whole TSO packet has not been acked. */</i></b>
<a name="L3018" href="source/net/ipv4/tcp_input.c#L3018">3018</a> static <a href="ident?i=u32">u32</a> <a href="ident?i=tcp_tso_acked">tcp_tso_acked</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L3019" href="source/net/ipv4/tcp_input.c#L3019">3019</a> {
<a name="L3020" href="source/net/ipv4/tcp_input.c#L3020">3020</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L3021" href="source/net/ipv4/tcp_input.c#L3021">3021</a>         <a href="ident?i=u32">u32</a> packets_acked;
<a name="L3022" href="source/net/ipv4/tcp_input.c#L3022">3022</a> 
<a name="L3023" href="source/net/ipv4/tcp_input.c#L3023">3023</a>         <a href="ident?i=BUG_ON">BUG_ON</a>(!<a href="ident?i=after">after</a>(<a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;end_seq, <a href="ident?i=tp">tp</a>-&gt;snd_una));
<a name="L3024" href="source/net/ipv4/tcp_input.c#L3024">3024</a> 
<a name="L3025" href="source/net/ipv4/tcp_input.c#L3025">3025</a>         packets_acked = <a href="ident?i=tcp_skb_pcount">tcp_skb_pcount</a>(<a href="ident?i=skb">skb</a>);
<a name="L3026" href="source/net/ipv4/tcp_input.c#L3026">3026</a>         if (<a href="ident?i=tcp_trim_head">tcp_trim_head</a>(sk, <a href="ident?i=skb">skb</a>, <a href="ident?i=tp">tp</a>-&gt;snd_una - <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=seq">seq</a>))
<a name="L3027" href="source/net/ipv4/tcp_input.c#L3027">3027</a>                 return 0;
<a name="L3028" href="source/net/ipv4/tcp_input.c#L3028">3028</a>         packets_acked -= <a href="ident?i=tcp_skb_pcount">tcp_skb_pcount</a>(<a href="ident?i=skb">skb</a>);
<a name="L3029" href="source/net/ipv4/tcp_input.c#L3029">3029</a> 
<a name="L3030" href="source/net/ipv4/tcp_input.c#L3030">3030</a>         if (packets_acked) {
<a name="L3031" href="source/net/ipv4/tcp_input.c#L3031">3031</a>                 <a href="ident?i=BUG_ON">BUG_ON</a>(<a href="ident?i=tcp_skb_pcount">tcp_skb_pcount</a>(<a href="ident?i=skb">skb</a>) == 0);
<a name="L3032" href="source/net/ipv4/tcp_input.c#L3032">3032</a>                 <a href="ident?i=BUG_ON">BUG_ON</a>(!<a href="ident?i=before">before</a>(<a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=seq">seq</a>, <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;end_seq));
<a name="L3033" href="source/net/ipv4/tcp_input.c#L3033">3033</a>         }
<a name="L3034" href="source/net/ipv4/tcp_input.c#L3034">3034</a> 
<a name="L3035" href="source/net/ipv4/tcp_input.c#L3035">3035</a>         return packets_acked;
<a name="L3036" href="source/net/ipv4/tcp_input.c#L3036">3036</a> }
<a name="L3037" href="source/net/ipv4/tcp_input.c#L3037">3037</a> 
<a name="L3038" href="source/net/ipv4/tcp_input.c#L3038">3038</a> static void <a href="ident?i=tcp_ack_tstamp">tcp_ack_tstamp</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
<a name="L3039" href="source/net/ipv4/tcp_input.c#L3039">3039</a>                            <a href="ident?i=u32">u32</a> prior_snd_una)
<a name="L3040" href="source/net/ipv4/tcp_input.c#L3040">3040</a> {
<a name="L3041" href="source/net/ipv4/tcp_input.c#L3041">3041</a>         const struct <a href="ident?i=skb_shared_info">skb_shared_info</a> *shinfo;
<a name="L3042" href="source/net/ipv4/tcp_input.c#L3042">3042</a> 
<a name="L3043" href="source/net/ipv4/tcp_input.c#L3043">3043</a>         <b><i>/* Avoid cache line misses to get skb_shinfo() and shinfo-&gt;tx_flags */</i></b>
<a name="L3044" href="source/net/ipv4/tcp_input.c#L3044">3044</a>         if (<a href="ident?i=likely">likely</a>(!(sk-&gt;sk_tsflags &amp; SOF_TIMESTAMPING_TX_ACK)))
<a name="L3045" href="source/net/ipv4/tcp_input.c#L3045">3045</a>                 return;
<a name="L3046" href="source/net/ipv4/tcp_input.c#L3046">3046</a> 
<a name="L3047" href="source/net/ipv4/tcp_input.c#L3047">3047</a>         shinfo = <a href="ident?i=skb_shinfo">skb_shinfo</a>(<a href="ident?i=skb">skb</a>);
<a name="L3048" href="source/net/ipv4/tcp_input.c#L3048">3048</a>         if ((shinfo-&gt;tx_flags &amp; SKBTX_ACK_TSTAMP) &amp;&amp;
<a name="L3049" href="source/net/ipv4/tcp_input.c#L3049">3049</a>             <a href="ident?i=between">between</a>(shinfo-&gt;tskey, prior_snd_una, <a href="ident?i=tcp_sk">tcp_sk</a>(sk)-&gt;snd_una - 1))
<a name="L3050" href="source/net/ipv4/tcp_input.c#L3050">3050</a>                 <a href="ident?i=__skb_tstamp_tx">__skb_tstamp_tx</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=NULL">NULL</a>, sk, SCM_TSTAMP_ACK);
<a name="L3051" href="source/net/ipv4/tcp_input.c#L3051">3051</a> }
<a name="L3052" href="source/net/ipv4/tcp_input.c#L3052">3052</a> 
<a name="L3053" href="source/net/ipv4/tcp_input.c#L3053">3053</a> <b><i>/* Remove acknowledged frames from the retransmission queue. If our packet</i></b>
<a name="L3054" href="source/net/ipv4/tcp_input.c#L3054">3054</a> <b><i> * is before the ack sequence we can discard it as it's confirmed to have</i></b>
<a name="L3055" href="source/net/ipv4/tcp_input.c#L3055">3055</a> <b><i> * arrived at the other end.</i></b>
<a name="L3056" href="source/net/ipv4/tcp_input.c#L3056">3056</a> <b><i> */</i></b>
<a name="L3057" href="source/net/ipv4/tcp_input.c#L3057">3057</a> static int <a href="ident?i=tcp_clean_rtx_queue">tcp_clean_rtx_queue</a>(struct <a href="ident?i=sock">sock</a> *sk, int prior_fackets,
<a name="L3058" href="source/net/ipv4/tcp_input.c#L3058">3058</a>                                <a href="ident?i=u32">u32</a> prior_snd_una, long sack_rtt_us)
<a name="L3059" href="source/net/ipv4/tcp_input.c#L3059">3059</a> {
<a name="L3060" href="source/net/ipv4/tcp_input.c#L3060">3060</a>         const struct <a href="ident?i=inet_connection_sock">inet_connection_sock</a> *icsk = <a href="ident?i=inet_csk">inet_csk</a>(sk);
<a name="L3061" href="source/net/ipv4/tcp_input.c#L3061">3061</a>         struct <a href="ident?i=skb_mstamp">skb_mstamp</a> first_ackt, last_ackt, <a href="ident?i=now">now</a>;
<a name="L3062" href="source/net/ipv4/tcp_input.c#L3062">3062</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L3063" href="source/net/ipv4/tcp_input.c#L3063">3063</a>         <a href="ident?i=u32">u32</a> prior_sacked = <a href="ident?i=tp">tp</a>-&gt;sacked_out;
<a name="L3064" href="source/net/ipv4/tcp_input.c#L3064">3064</a>         <a href="ident?i=u32">u32</a> reord = <a href="ident?i=tp">tp</a>-&gt;packets_out;
<a name="L3065" href="source/net/ipv4/tcp_input.c#L3065">3065</a>         <a href="ident?i=bool">bool</a> fully_acked = <a href="ident?i=true">true</a>;
<a name="L3066" href="source/net/ipv4/tcp_input.c#L3066">3066</a>         long ca_seq_rtt_us = -1L;
<a name="L3067" href="source/net/ipv4/tcp_input.c#L3067">3067</a>         long seq_rtt_us = -1L;
<a name="L3068" href="source/net/ipv4/tcp_input.c#L3068">3068</a>         struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>;
<a name="L3069" href="source/net/ipv4/tcp_input.c#L3069">3069</a>         <a href="ident?i=u32">u32</a> pkts_acked = 0;
<a name="L3070" href="source/net/ipv4/tcp_input.c#L3070">3070</a>         <a href="ident?i=bool">bool</a> rtt_update;
<a name="L3071" href="source/net/ipv4/tcp_input.c#L3071">3071</a>         int <a href="ident?i=flag">flag</a> = 0;
<a name="L3072" href="source/net/ipv4/tcp_input.c#L3072">3072</a> 
<a name="L3073" href="source/net/ipv4/tcp_input.c#L3073">3073</a>         first_ackt.<a href="ident?i=v64">v64</a> = 0;
<a name="L3074" href="source/net/ipv4/tcp_input.c#L3074">3074</a> 
<a name="L3075" href="source/net/ipv4/tcp_input.c#L3075">3075</a>         while ((<a href="ident?i=skb">skb</a> = <a href="ident?i=tcp_write_queue_head">tcp_write_queue_head</a>(sk)) &amp;&amp; <a href="ident?i=skb">skb</a> != <a href="ident?i=tcp_send_head">tcp_send_head</a>(sk)) {
<a name="L3076" href="source/net/ipv4/tcp_input.c#L3076">3076</a>                 struct <a href="ident?i=tcp_skb_cb">tcp_skb_cb</a> *<a href="ident?i=scb">scb</a> = <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>);
<a name="L3077" href="source/net/ipv4/tcp_input.c#L3077">3077</a>                 <a href="ident?i=u8">u8</a> sacked = <a href="ident?i=scb">scb</a>-&gt;sacked;
<a name="L3078" href="source/net/ipv4/tcp_input.c#L3078">3078</a>                 <a href="ident?i=u32">u32</a> acked_pcount;
<a name="L3079" href="source/net/ipv4/tcp_input.c#L3079">3079</a> 
<a name="L3080" href="source/net/ipv4/tcp_input.c#L3080">3080</a>                 <a href="ident?i=tcp_ack_tstamp">tcp_ack_tstamp</a>(sk, <a href="ident?i=skb">skb</a>, prior_snd_una);
<a name="L3081" href="source/net/ipv4/tcp_input.c#L3081">3081</a> 
<a name="L3082" href="source/net/ipv4/tcp_input.c#L3082">3082</a>                 <b><i>/* Determine how many packets and what bytes were acked, tso and else */</i></b>
<a name="L3083" href="source/net/ipv4/tcp_input.c#L3083">3083</a>                 if (<a href="ident?i=after">after</a>(<a href="ident?i=scb">scb</a>-&gt;end_seq, <a href="ident?i=tp">tp</a>-&gt;snd_una)) {
<a name="L3084" href="source/net/ipv4/tcp_input.c#L3084">3084</a>                         if (<a href="ident?i=tcp_skb_pcount">tcp_skb_pcount</a>(<a href="ident?i=skb">skb</a>) == 1 ||
<a name="L3085" href="source/net/ipv4/tcp_input.c#L3085">3085</a>                             !<a href="ident?i=after">after</a>(<a href="ident?i=tp">tp</a>-&gt;snd_una, <a href="ident?i=scb">scb</a>-&gt;<a href="ident?i=seq">seq</a>))
<a name="L3086" href="source/net/ipv4/tcp_input.c#L3086">3086</a>                                 break;
<a name="L3087" href="source/net/ipv4/tcp_input.c#L3087">3087</a> 
<a name="L3088" href="source/net/ipv4/tcp_input.c#L3088">3088</a>                         acked_pcount = <a href="ident?i=tcp_tso_acked">tcp_tso_acked</a>(sk, <a href="ident?i=skb">skb</a>);
<a name="L3089" href="source/net/ipv4/tcp_input.c#L3089">3089</a>                         if (!acked_pcount)
<a name="L3090" href="source/net/ipv4/tcp_input.c#L3090">3090</a>                                 break;
<a name="L3091" href="source/net/ipv4/tcp_input.c#L3091">3091</a> 
<a name="L3092" href="source/net/ipv4/tcp_input.c#L3092">3092</a>                         fully_acked = <a href="ident?i=false">false</a>;
<a name="L3093" href="source/net/ipv4/tcp_input.c#L3093">3093</a>                 } else {
<a name="L3094" href="source/net/ipv4/tcp_input.c#L3094">3094</a>                         <b><i>/* Speedup tcp_unlink_write_queue() and next loop */</i></b>
<a name="L3095" href="source/net/ipv4/tcp_input.c#L3095">3095</a>                         <a href="ident?i=prefetchw">prefetchw</a>(<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=next">next</a>);
<a name="L3096" href="source/net/ipv4/tcp_input.c#L3096">3096</a>                         acked_pcount = <a href="ident?i=tcp_skb_pcount">tcp_skb_pcount</a>(<a href="ident?i=skb">skb</a>);
<a name="L3097" href="source/net/ipv4/tcp_input.c#L3097">3097</a>                 }
<a name="L3098" href="source/net/ipv4/tcp_input.c#L3098">3098</a> 
<a name="L3099" href="source/net/ipv4/tcp_input.c#L3099">3099</a>                 if (<a href="ident?i=unlikely">unlikely</a>(sacked &amp; <a href="ident?i=TCPCB_RETRANS">TCPCB_RETRANS</a>)) {
<a name="L3100" href="source/net/ipv4/tcp_input.c#L3100">3100</a>                         if (sacked &amp; <a href="ident?i=TCPCB_SACKED_RETRANS">TCPCB_SACKED_RETRANS</a>)
<a name="L3101" href="source/net/ipv4/tcp_input.c#L3101">3101</a>                                 <a href="ident?i=tp">tp</a>-&gt;retrans_out -= acked_pcount;
<a name="L3102" href="source/net/ipv4/tcp_input.c#L3102">3102</a>                         <a href="ident?i=flag">flag</a> |= <a href="ident?i=FLAG_RETRANS_DATA_ACKED">FLAG_RETRANS_DATA_ACKED</a>;
<a name="L3103" href="source/net/ipv4/tcp_input.c#L3103">3103</a>                 } else if (!(sacked &amp; <a href="ident?i=TCPCB_SACKED_ACKED">TCPCB_SACKED_ACKED</a>)) {
<a name="L3104" href="source/net/ipv4/tcp_input.c#L3104">3104</a>                         last_ackt = <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=skb_mstamp">skb_mstamp</a>;
<a name="L3105" href="source/net/ipv4/tcp_input.c#L3105">3105</a>                         <a href="ident?i=WARN_ON_ONCE">WARN_ON_ONCE</a>(last_ackt.<a href="ident?i=v64">v64</a> == 0);
<a name="L3106" href="source/net/ipv4/tcp_input.c#L3106">3106</a>                         if (!first_ackt.<a href="ident?i=v64">v64</a>)
<a name="L3107" href="source/net/ipv4/tcp_input.c#L3107">3107</a>                                 first_ackt = last_ackt;
<a name="L3108" href="source/net/ipv4/tcp_input.c#L3108">3108</a> 
<a name="L3109" href="source/net/ipv4/tcp_input.c#L3109">3109</a>                         reord = <a href="ident?i=min">min</a>(pkts_acked, reord);
<a name="L3110" href="source/net/ipv4/tcp_input.c#L3110">3110</a>                         if (!<a href="ident?i=after">after</a>(<a href="ident?i=scb">scb</a>-&gt;end_seq, <a href="ident?i=tp">tp</a>-&gt;high_seq))
<a name="L3111" href="source/net/ipv4/tcp_input.c#L3111">3111</a>                                 <a href="ident?i=flag">flag</a> |= <a href="ident?i=FLAG_ORIG_SACK_ACKED">FLAG_ORIG_SACK_ACKED</a>;
<a name="L3112" href="source/net/ipv4/tcp_input.c#L3112">3112</a>                 }
<a name="L3113" href="source/net/ipv4/tcp_input.c#L3113">3113</a> 
<a name="L3114" href="source/net/ipv4/tcp_input.c#L3114">3114</a>                 if (sacked &amp; <a href="ident?i=TCPCB_SACKED_ACKED">TCPCB_SACKED_ACKED</a>)
<a name="L3115" href="source/net/ipv4/tcp_input.c#L3115">3115</a>                         <a href="ident?i=tp">tp</a>-&gt;sacked_out -= acked_pcount;
<a name="L3116" href="source/net/ipv4/tcp_input.c#L3116">3116</a>                 if (sacked &amp; <a href="ident?i=TCPCB_LOST">TCPCB_LOST</a>)
<a name="L3117" href="source/net/ipv4/tcp_input.c#L3117">3117</a>                         <a href="ident?i=tp">tp</a>-&gt;lost_out -= acked_pcount;
<a name="L3118" href="source/net/ipv4/tcp_input.c#L3118">3118</a> 
<a name="L3119" href="source/net/ipv4/tcp_input.c#L3119">3119</a>                 <a href="ident?i=tp">tp</a>-&gt;packets_out -= acked_pcount;
<a name="L3120" href="source/net/ipv4/tcp_input.c#L3120">3120</a>                 pkts_acked += acked_pcount;
<a name="L3121" href="source/net/ipv4/tcp_input.c#L3121">3121</a> 
<a name="L3122" href="source/net/ipv4/tcp_input.c#L3122">3122</a>                 <b><i>/* Initial outgoing SYN's get put onto the write_queue</i></b>
<a name="L3123" href="source/net/ipv4/tcp_input.c#L3123">3123</a> <b><i>                 * just like anything else we transmit.  It is not</i></b>
<a name="L3124" href="source/net/ipv4/tcp_input.c#L3124">3124</a> <b><i>                 * true data, and if we misinform our callers that</i></b>
<a name="L3125" href="source/net/ipv4/tcp_input.c#L3125">3125</a> <b><i>                 * this ACK acks real data, we will erroneously exit</i></b>
<a name="L3126" href="source/net/ipv4/tcp_input.c#L3126">3126</a> <b><i>                 * connection startup slow start one packet too</i></b>
<a name="L3127" href="source/net/ipv4/tcp_input.c#L3127">3127</a> <b><i>                 * quickly.  This is severely frowned upon behavior.</i></b>
<a name="L3128" href="source/net/ipv4/tcp_input.c#L3128">3128</a> <b><i>                 */</i></b>
<a name="L3129" href="source/net/ipv4/tcp_input.c#L3129">3129</a>                 if (<a href="ident?i=likely">likely</a>(!(<a href="ident?i=scb">scb</a>-&gt;tcp_flags &amp; <a href="ident?i=TCPHDR_SYN">TCPHDR_SYN</a>))) {
<a name="L3130" href="source/net/ipv4/tcp_input.c#L3130">3130</a>                         <a href="ident?i=flag">flag</a> |= <a href="ident?i=FLAG_DATA_ACKED">FLAG_DATA_ACKED</a>;
<a name="L3131" href="source/net/ipv4/tcp_input.c#L3131">3131</a>                 } else {
<a name="L3132" href="source/net/ipv4/tcp_input.c#L3132">3132</a>                         <a href="ident?i=flag">flag</a> |= <a href="ident?i=FLAG_SYN_ACKED">FLAG_SYN_ACKED</a>;
<a name="L3133" href="source/net/ipv4/tcp_input.c#L3133">3133</a>                         <a href="ident?i=tp">tp</a>-&gt;retrans_stamp = 0;
<a name="L3134" href="source/net/ipv4/tcp_input.c#L3134">3134</a>                 }
<a name="L3135" href="source/net/ipv4/tcp_input.c#L3135">3135</a> 
<a name="L3136" href="source/net/ipv4/tcp_input.c#L3136">3136</a>                 if (!fully_acked)
<a name="L3137" href="source/net/ipv4/tcp_input.c#L3137">3137</a>                         break;
<a name="L3138" href="source/net/ipv4/tcp_input.c#L3138">3138</a> 
<a name="L3139" href="source/net/ipv4/tcp_input.c#L3139">3139</a>                 <a href="ident?i=tcp_unlink_write_queue">tcp_unlink_write_queue</a>(<a href="ident?i=skb">skb</a>, sk);
<a name="L3140" href="source/net/ipv4/tcp_input.c#L3140">3140</a>                 <a href="ident?i=sk_wmem_free_skb">sk_wmem_free_skb</a>(sk, <a href="ident?i=skb">skb</a>);
<a name="L3141" href="source/net/ipv4/tcp_input.c#L3141">3141</a>                 if (<a href="ident?i=unlikely">unlikely</a>(<a href="ident?i=skb">skb</a> == <a href="ident?i=tp">tp</a>-&gt;retransmit_skb_hint))
<a name="L3142" href="source/net/ipv4/tcp_input.c#L3142">3142</a>                         <a href="ident?i=tp">tp</a>-&gt;retransmit_skb_hint = <a href="ident?i=NULL">NULL</a>;
<a name="L3143" href="source/net/ipv4/tcp_input.c#L3143">3143</a>                 if (<a href="ident?i=unlikely">unlikely</a>(<a href="ident?i=skb">skb</a> == <a href="ident?i=tp">tp</a>-&gt;lost_skb_hint))
<a name="L3144" href="source/net/ipv4/tcp_input.c#L3144">3144</a>                         <a href="ident?i=tp">tp</a>-&gt;lost_skb_hint = <a href="ident?i=NULL">NULL</a>;
<a name="L3145" href="source/net/ipv4/tcp_input.c#L3145">3145</a>         }
<a name="L3146" href="source/net/ipv4/tcp_input.c#L3146">3146</a> 
<a name="L3147" href="source/net/ipv4/tcp_input.c#L3147">3147</a>         if (<a href="ident?i=likely">likely</a>(<a href="ident?i=between">between</a>(<a href="ident?i=tp">tp</a>-&gt;snd_up, prior_snd_una, <a href="ident?i=tp">tp</a>-&gt;snd_una)))
<a name="L3148" href="source/net/ipv4/tcp_input.c#L3148">3148</a>                 <a href="ident?i=tp">tp</a>-&gt;snd_up = <a href="ident?i=tp">tp</a>-&gt;snd_una;
<a name="L3149" href="source/net/ipv4/tcp_input.c#L3149">3149</a> 
<a name="L3150" href="source/net/ipv4/tcp_input.c#L3150">3150</a>         if (<a href="ident?i=skb">skb</a> &amp;&amp; (<a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;sacked &amp; <a href="ident?i=TCPCB_SACKED_ACKED">TCPCB_SACKED_ACKED</a>))
<a name="L3151" href="source/net/ipv4/tcp_input.c#L3151">3151</a>                 <a href="ident?i=flag">flag</a> |= <a href="ident?i=FLAG_SACK_RENEGING">FLAG_SACK_RENEGING</a>;
<a name="L3152" href="source/net/ipv4/tcp_input.c#L3152">3152</a> 
<a name="L3153" href="source/net/ipv4/tcp_input.c#L3153">3153</a>         <a href="ident?i=skb_mstamp_get">skb_mstamp_get</a>(&amp;<a href="ident?i=now">now</a>);
<a name="L3154" href="source/net/ipv4/tcp_input.c#L3154">3154</a>         if (<a href="ident?i=likely">likely</a>(first_ackt.<a href="ident?i=v64">v64</a>)) {
<a name="L3155" href="source/net/ipv4/tcp_input.c#L3155">3155</a>                 seq_rtt_us = <a href="ident?i=skb_mstamp_us_delta">skb_mstamp_us_delta</a>(&amp;<a href="ident?i=now">now</a>, &amp;first_ackt);
<a name="L3156" href="source/net/ipv4/tcp_input.c#L3156">3156</a>                 ca_seq_rtt_us = <a href="ident?i=skb_mstamp_us_delta">skb_mstamp_us_delta</a>(&amp;<a href="ident?i=now">now</a>, &amp;last_ackt);
<a name="L3157" href="source/net/ipv4/tcp_input.c#L3157">3157</a>         }
<a name="L3158" href="source/net/ipv4/tcp_input.c#L3158">3158</a> 
<a name="L3159" href="source/net/ipv4/tcp_input.c#L3159">3159</a>         rtt_update = <a href="ident?i=tcp_ack_update_rtt">tcp_ack_update_rtt</a>(sk, <a href="ident?i=flag">flag</a>, seq_rtt_us, sack_rtt_us);
<a name="L3160" href="source/net/ipv4/tcp_input.c#L3160">3160</a> 
<a name="L3161" href="source/net/ipv4/tcp_input.c#L3161">3161</a>         if (<a href="ident?i=flag">flag</a> &amp; <a href="ident?i=FLAG_ACKED">FLAG_ACKED</a>) {
<a name="L3162" href="source/net/ipv4/tcp_input.c#L3162">3162</a>                 const struct <a href="ident?i=tcp_congestion_ops">tcp_congestion_ops</a> *ca_ops
<a name="L3163" href="source/net/ipv4/tcp_input.c#L3163">3163</a>                         = <a href="ident?i=inet_csk">inet_csk</a>(sk)-&gt;icsk_ca_ops;
<a name="L3164" href="source/net/ipv4/tcp_input.c#L3164">3164</a> 
<a name="L3165" href="source/net/ipv4/tcp_input.c#L3165">3165</a>                 <a href="ident?i=tcp_rearm_rto">tcp_rearm_rto</a>(sk);
<a name="L3166" href="source/net/ipv4/tcp_input.c#L3166">3166</a>                 if (<a href="ident?i=unlikely">unlikely</a>(icsk-&gt;icsk_mtup.probe_size &amp;&amp;
<a name="L3167" href="source/net/ipv4/tcp_input.c#L3167">3167</a>                              !<a href="ident?i=after">after</a>(<a href="ident?i=tp">tp</a>-&gt;mtu_probe.probe_seq_end, <a href="ident?i=tp">tp</a>-&gt;snd_una))) {
<a name="L3168" href="source/net/ipv4/tcp_input.c#L3168">3168</a>                         <a href="ident?i=tcp_mtup_probe_success">tcp_mtup_probe_success</a>(sk);
<a name="L3169" href="source/net/ipv4/tcp_input.c#L3169">3169</a>                 }
<a name="L3170" href="source/net/ipv4/tcp_input.c#L3170">3170</a> 
<a name="L3171" href="source/net/ipv4/tcp_input.c#L3171">3171</a>                 if (<a href="ident?i=tcp_is_reno">tcp_is_reno</a>(<a href="ident?i=tp">tp</a>)) {
<a name="L3172" href="source/net/ipv4/tcp_input.c#L3172">3172</a>                         <a href="ident?i=tcp_remove_reno_sacks">tcp_remove_reno_sacks</a>(sk, pkts_acked);
<a name="L3173" href="source/net/ipv4/tcp_input.c#L3173">3173</a>                 } else {
<a name="L3174" href="source/net/ipv4/tcp_input.c#L3174">3174</a>                         int <a href="ident?i=delta">delta</a>;
<a name="L3175" href="source/net/ipv4/tcp_input.c#L3175">3175</a> 
<a name="L3176" href="source/net/ipv4/tcp_input.c#L3176">3176</a>                         <b><i>/* Non-retransmitted hole got filled? That's reordering */</i></b>
<a name="L3177" href="source/net/ipv4/tcp_input.c#L3177">3177</a>                         if (reord &lt; prior_fackets)
<a name="L3178" href="source/net/ipv4/tcp_input.c#L3178">3178</a>                                 <a href="ident?i=tcp_update_reordering">tcp_update_reordering</a>(sk, <a href="ident?i=tp">tp</a>-&gt;fackets_out - reord, 0);
<a name="L3179" href="source/net/ipv4/tcp_input.c#L3179">3179</a> 
<a name="L3180" href="source/net/ipv4/tcp_input.c#L3180">3180</a>                         <a href="ident?i=delta">delta</a> = <a href="ident?i=tcp_is_fack">tcp_is_fack</a>(<a href="ident?i=tp">tp</a>) ? pkts_acked :
<a name="L3181" href="source/net/ipv4/tcp_input.c#L3181">3181</a>                                                   prior_sacked - <a href="ident?i=tp">tp</a>-&gt;sacked_out;
<a name="L3182" href="source/net/ipv4/tcp_input.c#L3182">3182</a>                         <a href="ident?i=tp">tp</a>-&gt;lost_cnt_hint -= <a href="ident?i=min">min</a>(<a href="ident?i=tp">tp</a>-&gt;lost_cnt_hint, <a href="ident?i=delta">delta</a>);
<a name="L3183" href="source/net/ipv4/tcp_input.c#L3183">3183</a>                 }
<a name="L3184" href="source/net/ipv4/tcp_input.c#L3184">3184</a> 
<a name="L3185" href="source/net/ipv4/tcp_input.c#L3185">3185</a>                 <a href="ident?i=tp">tp</a>-&gt;fackets_out -= <a href="ident?i=min">min</a>(pkts_acked, <a href="ident?i=tp">tp</a>-&gt;fackets_out);
<a name="L3186" href="source/net/ipv4/tcp_input.c#L3186">3186</a> 
<a name="L3187" href="source/net/ipv4/tcp_input.c#L3187">3187</a>                 if (ca_ops-&gt;pkts_acked) {
<a name="L3188" href="source/net/ipv4/tcp_input.c#L3188">3188</a>                         long rtt_us = <a href="ident?i=min_t">min_t</a>(<a href="ident?i=ulong">ulong</a>, ca_seq_rtt_us, sack_rtt_us);
<a name="L3189" href="source/net/ipv4/tcp_input.c#L3189">3189</a>                         ca_ops-&gt;pkts_acked(sk, pkts_acked, rtt_us);
<a name="L3190" href="source/net/ipv4/tcp_input.c#L3190">3190</a>                 }
<a name="L3191" href="source/net/ipv4/tcp_input.c#L3191">3191</a> 
<a name="L3192" href="source/net/ipv4/tcp_input.c#L3192">3192</a>         } else if (<a href="ident?i=skb">skb</a> &amp;&amp; rtt_update &amp;&amp; sack_rtt_us &gt;= 0 &amp;&amp;
<a name="L3193" href="source/net/ipv4/tcp_input.c#L3193">3193</a>                    sack_rtt_us &gt; <a href="ident?i=skb_mstamp_us_delta">skb_mstamp_us_delta</a>(&amp;<a href="ident?i=now">now</a>, &amp;<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=skb_mstamp">skb_mstamp</a>)) {
<a name="L3194" href="source/net/ipv4/tcp_input.c#L3194">3194</a>                 <b><i>/* Do not re-arm RTO if the sack RTT is measured from data sent</i></b>
<a name="L3195" href="source/net/ipv4/tcp_input.c#L3195">3195</a> <b><i>                 * after when the head was last (re)transmitted. Otherwise the</i></b>
<a name="L3196" href="source/net/ipv4/tcp_input.c#L3196">3196</a> <b><i>                 * timeout may continue to extend in loss recovery.</i></b>
<a name="L3197" href="source/net/ipv4/tcp_input.c#L3197">3197</a> <b><i>                 */</i></b>
<a name="L3198" href="source/net/ipv4/tcp_input.c#L3198">3198</a>                 <a href="ident?i=tcp_rearm_rto">tcp_rearm_rto</a>(sk);
<a name="L3199" href="source/net/ipv4/tcp_input.c#L3199">3199</a>         }
<a name="L3200" href="source/net/ipv4/tcp_input.c#L3200">3200</a> 
<a name="L3201" href="source/net/ipv4/tcp_input.c#L3201">3201</a> #if <a href="ident?i=FASTRETRANS_DEBUG">FASTRETRANS_DEBUG</a> &gt; 0
<a name="L3202" href="source/net/ipv4/tcp_input.c#L3202">3202</a>         <a href="ident?i=WARN_ON">WARN_ON</a>((int)<a href="ident?i=tp">tp</a>-&gt;sacked_out &lt; 0);
<a name="L3203" href="source/net/ipv4/tcp_input.c#L3203">3203</a>         <a href="ident?i=WARN_ON">WARN_ON</a>((int)<a href="ident?i=tp">tp</a>-&gt;lost_out &lt; 0);
<a name="L3204" href="source/net/ipv4/tcp_input.c#L3204">3204</a>         <a href="ident?i=WARN_ON">WARN_ON</a>((int)<a href="ident?i=tp">tp</a>-&gt;retrans_out &lt; 0);
<a name="L3205" href="source/net/ipv4/tcp_input.c#L3205">3205</a>         if (!<a href="ident?i=tp">tp</a>-&gt;packets_out &amp;&amp; <a href="ident?i=tcp_is_sack">tcp_is_sack</a>(<a href="ident?i=tp">tp</a>)) {
<a name="L3206" href="source/net/ipv4/tcp_input.c#L3206">3206</a>                 icsk = <a href="ident?i=inet_csk">inet_csk</a>(sk);
<a name="L3207" href="source/net/ipv4/tcp_input.c#L3207">3207</a>                 if (<a href="ident?i=tp">tp</a>-&gt;lost_out) {
<a name="L3208" href="source/net/ipv4/tcp_input.c#L3208">3208</a>                         <a href="ident?i=pr_debug">pr_debug</a>(<i>"Leak l=%u %d\n"</i>,
<a name="L3209" href="source/net/ipv4/tcp_input.c#L3209">3209</a>                                  <a href="ident?i=tp">tp</a>-&gt;lost_out, icsk-&gt;icsk_ca_state);
<a name="L3210" href="source/net/ipv4/tcp_input.c#L3210">3210</a>                         <a href="ident?i=tp">tp</a>-&gt;lost_out = 0;
<a name="L3211" href="source/net/ipv4/tcp_input.c#L3211">3211</a>                 }
<a name="L3212" href="source/net/ipv4/tcp_input.c#L3212">3212</a>                 if (<a href="ident?i=tp">tp</a>-&gt;sacked_out) {
<a name="L3213" href="source/net/ipv4/tcp_input.c#L3213">3213</a>                         <a href="ident?i=pr_debug">pr_debug</a>(<i>"Leak s=%u %d\n"</i>,
<a name="L3214" href="source/net/ipv4/tcp_input.c#L3214">3214</a>                                  <a href="ident?i=tp">tp</a>-&gt;sacked_out, icsk-&gt;icsk_ca_state);
<a name="L3215" href="source/net/ipv4/tcp_input.c#L3215">3215</a>                         <a href="ident?i=tp">tp</a>-&gt;sacked_out = 0;
<a name="L3216" href="source/net/ipv4/tcp_input.c#L3216">3216</a>                 }
<a name="L3217" href="source/net/ipv4/tcp_input.c#L3217">3217</a>                 if (<a href="ident?i=tp">tp</a>-&gt;retrans_out) {
<a name="L3218" href="source/net/ipv4/tcp_input.c#L3218">3218</a>                         <a href="ident?i=pr_debug">pr_debug</a>(<i>"Leak r=%u %d\n"</i>,
<a name="L3219" href="source/net/ipv4/tcp_input.c#L3219">3219</a>                                  <a href="ident?i=tp">tp</a>-&gt;retrans_out, icsk-&gt;icsk_ca_state);
<a name="L3220" href="source/net/ipv4/tcp_input.c#L3220">3220</a>                         <a href="ident?i=tp">tp</a>-&gt;retrans_out = 0;
<a name="L3221" href="source/net/ipv4/tcp_input.c#L3221">3221</a>                 }
<a name="L3222" href="source/net/ipv4/tcp_input.c#L3222">3222</a>         }
<a name="L3223" href="source/net/ipv4/tcp_input.c#L3223">3223</a> #endif
<a name="L3224" href="source/net/ipv4/tcp_input.c#L3224">3224</a>         return <a href="ident?i=flag">flag</a>;
<a name="L3225" href="source/net/ipv4/tcp_input.c#L3225">3225</a> }
<a name="L3226" href="source/net/ipv4/tcp_input.c#L3226">3226</a> 
<a name="L3227" href="source/net/ipv4/tcp_input.c#L3227">3227</a> static void <a href="ident?i=tcp_ack_probe">tcp_ack_probe</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L3228" href="source/net/ipv4/tcp_input.c#L3228">3228</a> {
<a name="L3229" href="source/net/ipv4/tcp_input.c#L3229">3229</a>         const struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L3230" href="source/net/ipv4/tcp_input.c#L3230">3230</a>         struct <a href="ident?i=inet_connection_sock">inet_connection_sock</a> *icsk = <a href="ident?i=inet_csk">inet_csk</a>(sk);
<a name="L3231" href="source/net/ipv4/tcp_input.c#L3231">3231</a> 
<a name="L3232" href="source/net/ipv4/tcp_input.c#L3232">3232</a>         <b><i>/* Was it a usable window open? */</i></b>
<a name="L3233" href="source/net/ipv4/tcp_input.c#L3233">3233</a> 
<a name="L3234" href="source/net/ipv4/tcp_input.c#L3234">3234</a>         if (!<a href="ident?i=after">after</a>(<a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=tcp_send_head">tcp_send_head</a>(sk))-&gt;end_seq, <a href="ident?i=tcp_wnd_end">tcp_wnd_end</a>(<a href="ident?i=tp">tp</a>))) {
<a name="L3235" href="source/net/ipv4/tcp_input.c#L3235">3235</a>                 icsk-&gt;icsk_backoff = 0;
<a name="L3236" href="source/net/ipv4/tcp_input.c#L3236">3236</a>                 <a href="ident?i=inet_csk_clear_xmit_timer">inet_csk_clear_xmit_timer</a>(sk, <a href="ident?i=ICSK_TIME_PROBE0">ICSK_TIME_PROBE0</a>);
<a name="L3237" href="source/net/ipv4/tcp_input.c#L3237">3237</a>                 <b><i>/* Socket must be waked up by subsequent tcp_data_snd_check().</i></b>
<a name="L3238" href="source/net/ipv4/tcp_input.c#L3238">3238</a> <b><i>                 * This function is not for random using!</i></b>
<a name="L3239" href="source/net/ipv4/tcp_input.c#L3239">3239</a> <b><i>                 */</i></b>
<a name="L3240" href="source/net/ipv4/tcp_input.c#L3240">3240</a>         } else {
<a name="L3241" href="source/net/ipv4/tcp_input.c#L3241">3241</a>                 unsigned long when = <a href="ident?i=inet_csk_rto_backoff">inet_csk_rto_backoff</a>(icsk, <a href="ident?i=TCP_RTO_MAX">TCP_RTO_MAX</a>);
<a name="L3242" href="source/net/ipv4/tcp_input.c#L3242">3242</a> 
<a name="L3243" href="source/net/ipv4/tcp_input.c#L3243">3243</a>                 <a href="ident?i=inet_csk_reset_xmit_timer">inet_csk_reset_xmit_timer</a>(sk, <a href="ident?i=ICSK_TIME_PROBE0">ICSK_TIME_PROBE0</a>,
<a name="L3244" href="source/net/ipv4/tcp_input.c#L3244">3244</a>                                           when, <a href="ident?i=TCP_RTO_MAX">TCP_RTO_MAX</a>);
<a name="L3245" href="source/net/ipv4/tcp_input.c#L3245">3245</a>         }
<a name="L3246" href="source/net/ipv4/tcp_input.c#L3246">3246</a> }
<a name="L3247" href="source/net/ipv4/tcp_input.c#L3247">3247</a> 
<a name="L3248" href="source/net/ipv4/tcp_input.c#L3248">3248</a> static inline <a href="ident?i=bool">bool</a> <a href="ident?i=tcp_ack_is_dubious">tcp_ack_is_dubious</a>(const struct <a href="ident?i=sock">sock</a> *sk, const int <a href="ident?i=flag">flag</a>)
<a name="L3249" href="source/net/ipv4/tcp_input.c#L3249">3249</a> {
<a name="L3250" href="source/net/ipv4/tcp_input.c#L3250">3250</a>         return !(<a href="ident?i=flag">flag</a> &amp; <a href="ident?i=FLAG_NOT_DUP">FLAG_NOT_DUP</a>) || (<a href="ident?i=flag">flag</a> &amp; <a href="ident?i=FLAG_CA_ALERT">FLAG_CA_ALERT</a>) ||
<a name="L3251" href="source/net/ipv4/tcp_input.c#L3251">3251</a>                 <a href="ident?i=inet_csk">inet_csk</a>(sk)-&gt;icsk_ca_state != TCP_CA_Open;
<a name="L3252" href="source/net/ipv4/tcp_input.c#L3252">3252</a> }
<a name="L3253" href="source/net/ipv4/tcp_input.c#L3253">3253</a> 
<a name="L3254" href="source/net/ipv4/tcp_input.c#L3254">3254</a> <b><i>/* Decide wheather to run the increase function of congestion control. */</i></b>
<a name="L3255" href="source/net/ipv4/tcp_input.c#L3255">3255</a> static inline <a href="ident?i=bool">bool</a> <a href="ident?i=tcp_may_raise_cwnd">tcp_may_raise_cwnd</a>(const struct <a href="ident?i=sock">sock</a> *sk, const int <a href="ident?i=flag">flag</a>)
<a name="L3256" href="source/net/ipv4/tcp_input.c#L3256">3256</a> {
<a name="L3257" href="source/net/ipv4/tcp_input.c#L3257">3257</a>         if (<a href="ident?i=tcp_in_cwnd_reduction">tcp_in_cwnd_reduction</a>(sk))
<a name="L3258" href="source/net/ipv4/tcp_input.c#L3258">3258</a>                 return <a href="ident?i=false">false</a>;
<a name="L3259" href="source/net/ipv4/tcp_input.c#L3259">3259</a> 
<a name="L3260" href="source/net/ipv4/tcp_input.c#L3260">3260</a>         <b><i>/* If reordering is high then always grow cwnd whenever data is</i></b>
<a name="L3261" href="source/net/ipv4/tcp_input.c#L3261">3261</a> <b><i>         * delivered regardless of its ordering. Otherwise stay conservative</i></b>
<a name="L3262" href="source/net/ipv4/tcp_input.c#L3262">3262</a> <b><i>         * and only grow cwnd on in-order delivery (RFC5681). A stretched ACK w/</i></b>
<a name="L3263" href="source/net/ipv4/tcp_input.c#L3263">3263</a> <b><i>         * new SACK or ECE mark may first advance cwnd here and later reduce</i></b>
<a name="L3264" href="source/net/ipv4/tcp_input.c#L3264">3264</a> <b><i>         * cwnd in tcp_fastretrans_alert() based on more states.</i></b>
<a name="L3265" href="source/net/ipv4/tcp_input.c#L3265">3265</a> <b><i>         */</i></b>
<a name="L3266" href="source/net/ipv4/tcp_input.c#L3266">3266</a>         if (<a href="ident?i=tcp_sk">tcp_sk</a>(sk)-&gt;reordering &gt; <a href="ident?i=sysctl_tcp_reordering">sysctl_tcp_reordering</a>)
<a name="L3267" href="source/net/ipv4/tcp_input.c#L3267">3267</a>                 return <a href="ident?i=flag">flag</a> &amp; <a href="ident?i=FLAG_FORWARD_PROGRESS">FLAG_FORWARD_PROGRESS</a>;
<a name="L3268" href="source/net/ipv4/tcp_input.c#L3268">3268</a> 
<a name="L3269" href="source/net/ipv4/tcp_input.c#L3269">3269</a>         return <a href="ident?i=flag">flag</a> &amp; <a href="ident?i=FLAG_DATA_ACKED">FLAG_DATA_ACKED</a>;
<a name="L3270" href="source/net/ipv4/tcp_input.c#L3270">3270</a> }
<a name="L3271" href="source/net/ipv4/tcp_input.c#L3271">3271</a> 
<a name="L3272" href="source/net/ipv4/tcp_input.c#L3272">3272</a> <b><i>/* Check that window update is acceptable.</i></b>
<a name="L3273" href="source/net/ipv4/tcp_input.c#L3273">3273</a> <b><i> * The function assumes that snd_una&lt;=ack&lt;=snd_next.</i></b>
<a name="L3274" href="source/net/ipv4/tcp_input.c#L3274">3274</a> <b><i> */</i></b>
<a name="L3275" href="source/net/ipv4/tcp_input.c#L3275">3275</a> static inline <a href="ident?i=bool">bool</a> <a href="ident?i=tcp_may_update_window">tcp_may_update_window</a>(const struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a>,
<a name="L3276" href="source/net/ipv4/tcp_input.c#L3276">3276</a>                                         const <a href="ident?i=u32">u32</a> ack, const <a href="ident?i=u32">u32</a> ack_seq,
<a name="L3277" href="source/net/ipv4/tcp_input.c#L3277">3277</a>                                         const <a href="ident?i=u32">u32</a> nwin)
<a name="L3278" href="source/net/ipv4/tcp_input.c#L3278">3278</a> {
<a name="L3279" href="source/net/ipv4/tcp_input.c#L3279">3279</a>         return  <a href="ident?i=after">after</a>(ack, <a href="ident?i=tp">tp</a>-&gt;snd_una) ||
<a name="L3280" href="source/net/ipv4/tcp_input.c#L3280">3280</a>                 <a href="ident?i=after">after</a>(ack_seq, <a href="ident?i=tp">tp</a>-&gt;snd_wl1) ||
<a name="L3281" href="source/net/ipv4/tcp_input.c#L3281">3281</a>                 (ack_seq == <a href="ident?i=tp">tp</a>-&gt;snd_wl1 &amp;&amp; nwin &gt; <a href="ident?i=tp">tp</a>-&gt;snd_wnd);
<a name="L3282" href="source/net/ipv4/tcp_input.c#L3282">3282</a> }
<a name="L3283" href="source/net/ipv4/tcp_input.c#L3283">3283</a> 
<a name="L3284" href="source/net/ipv4/tcp_input.c#L3284">3284</a> <b><i>/* If we update tp-&gt;snd_una, also update tp-&gt;bytes_acked */</i></b>
<a name="L3285" href="source/net/ipv4/tcp_input.c#L3285">3285</a> static void <a href="ident?i=tcp_snd_una_update">tcp_snd_una_update</a>(struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a>, <a href="ident?i=u32">u32</a> ack)
<a name="L3286" href="source/net/ipv4/tcp_input.c#L3286">3286</a> {
<a name="L3287" href="source/net/ipv4/tcp_input.c#L3287">3287</a>         <a href="ident?i=u32">u32</a> <a href="ident?i=delta">delta</a> = ack - <a href="ident?i=tp">tp</a>-&gt;snd_una;
<a name="L3288" href="source/net/ipv4/tcp_input.c#L3288">3288</a> 
<a name="L3289" href="source/net/ipv4/tcp_input.c#L3289">3289</a>         <a href="ident?i=u64_stats_update_begin">u64_stats_update_begin</a>(&amp;<a href="ident?i=tp">tp</a>-&gt;syncp);
<a name="L3290" href="source/net/ipv4/tcp_input.c#L3290">3290</a>         <a href="ident?i=tp">tp</a>-&gt;bytes_acked += <a href="ident?i=delta">delta</a>;
<a name="L3291" href="source/net/ipv4/tcp_input.c#L3291">3291</a>         <a href="ident?i=u64_stats_update_end">u64_stats_update_end</a>(&amp;<a href="ident?i=tp">tp</a>-&gt;syncp);
<a name="L3292" href="source/net/ipv4/tcp_input.c#L3292">3292</a>         <a href="ident?i=tp">tp</a>-&gt;snd_una = ack;
<a name="L3293" href="source/net/ipv4/tcp_input.c#L3293">3293</a> }
<a name="L3294" href="source/net/ipv4/tcp_input.c#L3294">3294</a> 
<a name="L3295" href="source/net/ipv4/tcp_input.c#L3295">3295</a> <b><i>/* If we update tp-&gt;rcv_nxt, also update tp-&gt;bytes_received */</i></b>
<a name="L3296" href="source/net/ipv4/tcp_input.c#L3296">3296</a> static void <a href="ident?i=tcp_rcv_nxt_update">tcp_rcv_nxt_update</a>(struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a>, <a href="ident?i=u32">u32</a> <a href="ident?i=seq">seq</a>)
<a name="L3297" href="source/net/ipv4/tcp_input.c#L3297">3297</a> {
<a name="L3298" href="source/net/ipv4/tcp_input.c#L3298">3298</a>         <a href="ident?i=u32">u32</a> <a href="ident?i=delta">delta</a> = <a href="ident?i=seq">seq</a> - <a href="ident?i=tp">tp</a>-&gt;rcv_nxt;
<a name="L3299" href="source/net/ipv4/tcp_input.c#L3299">3299</a> 
<a name="L3300" href="source/net/ipv4/tcp_input.c#L3300">3300</a>         <a href="ident?i=u64_stats_update_begin">u64_stats_update_begin</a>(&amp;<a href="ident?i=tp">tp</a>-&gt;syncp);
<a name="L3301" href="source/net/ipv4/tcp_input.c#L3301">3301</a>         <a href="ident?i=tp">tp</a>-&gt;bytes_received += <a href="ident?i=delta">delta</a>;
<a name="L3302" href="source/net/ipv4/tcp_input.c#L3302">3302</a>         <a href="ident?i=u64_stats_update_end">u64_stats_update_end</a>(&amp;<a href="ident?i=tp">tp</a>-&gt;syncp);
<a name="L3303" href="source/net/ipv4/tcp_input.c#L3303">3303</a>         <a href="ident?i=tp">tp</a>-&gt;rcv_nxt = <a href="ident?i=seq">seq</a>;
<a name="L3304" href="source/net/ipv4/tcp_input.c#L3304">3304</a> }
<a name="L3305" href="source/net/ipv4/tcp_input.c#L3305">3305</a> 
<a name="L3306" href="source/net/ipv4/tcp_input.c#L3306">3306</a> <b><i>/* Update our send window.</i></b>
<a name="L3307" href="source/net/ipv4/tcp_input.c#L3307">3307</a> <b><i> *</i></b>
<a name="L3308" href="source/net/ipv4/tcp_input.c#L3308">3308</a> <b><i> * Window update algorithm, described in RFC793/RFC1122 (used in linux-2.2</i></b>
<a name="L3309" href="source/net/ipv4/tcp_input.c#L3309">3309</a> <b><i> * and in FreeBSD. NetBSD's one is even worse.) is wrong.</i></b>
<a name="L3310" href="source/net/ipv4/tcp_input.c#L3310">3310</a> <b><i> */</i></b>
<a name="L3311" href="source/net/ipv4/tcp_input.c#L3311">3311</a> static int <a href="ident?i=tcp_ack_update_window">tcp_ack_update_window</a>(struct <a href="ident?i=sock">sock</a> *sk, const struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, <a href="ident?i=u32">u32</a> ack,
<a name="L3312" href="source/net/ipv4/tcp_input.c#L3312">3312</a>                                  <a href="ident?i=u32">u32</a> ack_seq)
<a name="L3313" href="source/net/ipv4/tcp_input.c#L3313">3313</a> {
<a name="L3314" href="source/net/ipv4/tcp_input.c#L3314">3314</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L3315" href="source/net/ipv4/tcp_input.c#L3315">3315</a>         int <a href="ident?i=flag">flag</a> = 0;
<a name="L3316" href="source/net/ipv4/tcp_input.c#L3316">3316</a>         <a href="ident?i=u32">u32</a> nwin = <a href="ident?i=ntohs">ntohs</a>(<a href="ident?i=tcp_hdr">tcp_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=window">window</a>);
<a name="L3317" href="source/net/ipv4/tcp_input.c#L3317">3317</a> 
<a name="L3318" href="source/net/ipv4/tcp_input.c#L3318">3318</a>         if (<a href="ident?i=likely">likely</a>(!<a href="ident?i=tcp_hdr">tcp_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;syn))
<a name="L3319" href="source/net/ipv4/tcp_input.c#L3319">3319</a>                 nwin &lt;&lt;= <a href="ident?i=tp">tp</a>-&gt;rx_opt.snd_wscale;
<a name="L3320" href="source/net/ipv4/tcp_input.c#L3320">3320</a> 
<a name="L3321" href="source/net/ipv4/tcp_input.c#L3321">3321</a>         if (<a href="ident?i=tcp_may_update_window">tcp_may_update_window</a>(<a href="ident?i=tp">tp</a>, ack, ack_seq, nwin)) {
<a name="L3322" href="source/net/ipv4/tcp_input.c#L3322">3322</a>                 <a href="ident?i=flag">flag</a> |= <a href="ident?i=FLAG_WIN_UPDATE">FLAG_WIN_UPDATE</a>;
<a name="L3323" href="source/net/ipv4/tcp_input.c#L3323">3323</a>                 <a href="ident?i=tcp_update_wl">tcp_update_wl</a>(<a href="ident?i=tp">tp</a>, ack_seq);
<a name="L3324" href="source/net/ipv4/tcp_input.c#L3324">3324</a> 
<a name="L3325" href="source/net/ipv4/tcp_input.c#L3325">3325</a>                 if (<a href="ident?i=tp">tp</a>-&gt;snd_wnd != nwin) {
<a name="L3326" href="source/net/ipv4/tcp_input.c#L3326">3326</a>                         <a href="ident?i=tp">tp</a>-&gt;snd_wnd = nwin;
<a name="L3327" href="source/net/ipv4/tcp_input.c#L3327">3327</a> 
<a name="L3328" href="source/net/ipv4/tcp_input.c#L3328">3328</a>                         <b><i>/* Note, it is the only place, where</i></b>
<a name="L3329" href="source/net/ipv4/tcp_input.c#L3329">3329</a> <b><i>                         * fast path is recovered for sending TCP.</i></b>
<a name="L3330" href="source/net/ipv4/tcp_input.c#L3330">3330</a> <b><i>                         */</i></b>
<a name="L3331" href="source/net/ipv4/tcp_input.c#L3331">3331</a>                         <a href="ident?i=tp">tp</a>-&gt;pred_flags = 0;
<a name="L3332" href="source/net/ipv4/tcp_input.c#L3332">3332</a>                         <a href="ident?i=tcp_fast_path_check">tcp_fast_path_check</a>(sk);
<a name="L3333" href="source/net/ipv4/tcp_input.c#L3333">3333</a> 
<a name="L3334" href="source/net/ipv4/tcp_input.c#L3334">3334</a>                         if (nwin &gt; <a href="ident?i=tp">tp</a>-&gt;max_window) {
<a name="L3335" href="source/net/ipv4/tcp_input.c#L3335">3335</a>                                 <a href="ident?i=tp">tp</a>-&gt;max_window = nwin;
<a name="L3336" href="source/net/ipv4/tcp_input.c#L3336">3336</a>                                 <a href="ident?i=tcp_sync_mss">tcp_sync_mss</a>(sk, <a href="ident?i=inet_csk">inet_csk</a>(sk)-&gt;icsk_pmtu_cookie);
<a name="L3337" href="source/net/ipv4/tcp_input.c#L3337">3337</a>                         }
<a name="L3338" href="source/net/ipv4/tcp_input.c#L3338">3338</a>                 }
<a name="L3339" href="source/net/ipv4/tcp_input.c#L3339">3339</a>         }
<a name="L3340" href="source/net/ipv4/tcp_input.c#L3340">3340</a> 
<a name="L3341" href="source/net/ipv4/tcp_input.c#L3341">3341</a>         <a href="ident?i=tcp_snd_una_update">tcp_snd_una_update</a>(<a href="ident?i=tp">tp</a>, ack);
<a name="L3342" href="source/net/ipv4/tcp_input.c#L3342">3342</a> 
<a name="L3343" href="source/net/ipv4/tcp_input.c#L3343">3343</a>         return <a href="ident?i=flag">flag</a>;
<a name="L3344" href="source/net/ipv4/tcp_input.c#L3344">3344</a> }
<a name="L3345" href="source/net/ipv4/tcp_input.c#L3345">3345</a> 
<a name="L3346" href="source/net/ipv4/tcp_input.c#L3346">3346</a> <b><i>/* Return true if we're currently rate-limiting out-of-window ACKs and</i></b>
<a name="L3347" href="source/net/ipv4/tcp_input.c#L3347">3347</a> <b><i> * thus shouldn't send a dupack right now. We rate-limit dupacks in</i></b>
<a name="L3348" href="source/net/ipv4/tcp_input.c#L3348">3348</a> <b><i> * response to out-of-window SYNs or ACKs to mitigate ACK loops or DoS</i></b>
<a name="L3349" href="source/net/ipv4/tcp_input.c#L3349">3349</a> <b><i> * attacks that send repeated SYNs or ACKs for the same connection. To</i></b>
<a name="L3350" href="source/net/ipv4/tcp_input.c#L3350">3350</a> <b><i> * do this, we do not send a duplicate SYNACK or ACK if the remote</i></b>
<a name="L3351" href="source/net/ipv4/tcp_input.c#L3351">3351</a> <b><i> * endpoint is sending out-of-window SYNs or pure ACKs at a high rate.</i></b>
<a name="L3352" href="source/net/ipv4/tcp_input.c#L3352">3352</a> <b><i> */</i></b>
<a name="L3353" href="source/net/ipv4/tcp_input.c#L3353">3353</a> <a href="ident?i=bool">bool</a> <a href="ident?i=tcp_oow_rate_limited">tcp_oow_rate_limited</a>(struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a>, const struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
<a name="L3354" href="source/net/ipv4/tcp_input.c#L3354">3354</a>                           int mib_idx, <a href="ident?i=u32">u32</a> *last_oow_ack_time)
<a name="L3355" href="source/net/ipv4/tcp_input.c#L3355">3355</a> {
<a name="L3356" href="source/net/ipv4/tcp_input.c#L3356">3356</a>         <b><i>/* Data packets without SYNs are not likely part of an ACK loop. */</i></b>
<a name="L3357" href="source/net/ipv4/tcp_input.c#L3357">3357</a>         if ((<a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=seq">seq</a> != <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;end_seq) &amp;&amp;
<a name="L3358" href="source/net/ipv4/tcp_input.c#L3358">3358</a>             !<a href="ident?i=tcp_hdr">tcp_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;syn)
<a name="L3359" href="source/net/ipv4/tcp_input.c#L3359">3359</a>                 goto not_rate_limited;
<a name="L3360" href="source/net/ipv4/tcp_input.c#L3360">3360</a> 
<a name="L3361" href="source/net/ipv4/tcp_input.c#L3361">3361</a>         if (*last_oow_ack_time) {
<a name="L3362" href="source/net/ipv4/tcp_input.c#L3362">3362</a>                 <a href="ident?i=s32">s32</a> elapsed = (<a href="ident?i=s32">s32</a>)(<a href="ident?i=tcp_time_stamp">tcp_time_stamp</a> - *last_oow_ack_time);
<a name="L3363" href="source/net/ipv4/tcp_input.c#L3363">3363</a> 
<a name="L3364" href="source/net/ipv4/tcp_input.c#L3364">3364</a>                 if (0 &lt;= elapsed &amp;&amp; elapsed &lt; <a href="ident?i=sysctl_tcp_invalid_ratelimit">sysctl_tcp_invalid_ratelimit</a>) {
<a name="L3365" href="source/net/ipv4/tcp_input.c#L3365">3365</a>                         <a href="ident?i=NET_INC_STATS_BH">NET_INC_STATS_BH</a>(<a href="ident?i=net">net</a>, mib_idx);
<a name="L3366" href="source/net/ipv4/tcp_input.c#L3366">3366</a>                         return <a href="ident?i=true">true</a>;    <b><i>/* rate-limited: don't send yet! */</i></b>
<a name="L3367" href="source/net/ipv4/tcp_input.c#L3367">3367</a>                 }
<a name="L3368" href="source/net/ipv4/tcp_input.c#L3368">3368</a>         }
<a name="L3369" href="source/net/ipv4/tcp_input.c#L3369">3369</a> 
<a name="L3370" href="source/net/ipv4/tcp_input.c#L3370">3370</a>         *last_oow_ack_time = <a href="ident?i=tcp_time_stamp">tcp_time_stamp</a>;
<a name="L3371" href="source/net/ipv4/tcp_input.c#L3371">3371</a> 
<a name="L3372" href="source/net/ipv4/tcp_input.c#L3372">3372</a> not_rate_limited:
<a name="L3373" href="source/net/ipv4/tcp_input.c#L3373">3373</a>         return <a href="ident?i=false">false</a>;   <b><i>/* not rate-limited: go ahead, send dupack now! */</i></b>
<a name="L3374" href="source/net/ipv4/tcp_input.c#L3374">3374</a> }
<a name="L3375" href="source/net/ipv4/tcp_input.c#L3375">3375</a> 
<a name="L3376" href="source/net/ipv4/tcp_input.c#L3376">3376</a> <b><i>/* RFC 5961 7 [ACK Throttling] */</i></b>
<a name="L3377" href="source/net/ipv4/tcp_input.c#L3377">3377</a> static void <a href="ident?i=tcp_send_challenge_ack">tcp_send_challenge_ack</a>(struct <a href="ident?i=sock">sock</a> *sk, const struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L3378" href="source/net/ipv4/tcp_input.c#L3378">3378</a> {
<a name="L3379" href="source/net/ipv4/tcp_input.c#L3379">3379</a>         <b><i>/* unprotected vars, we dont care of overwrites */</i></b>
<a name="L3380" href="source/net/ipv4/tcp_input.c#L3380">3380</a>         static <a href="ident?i=u32">u32</a> challenge_timestamp;
<a name="L3381" href="source/net/ipv4/tcp_input.c#L3381">3381</a>         static unsigned int challenge_count;
<a name="L3382" href="source/net/ipv4/tcp_input.c#L3382">3382</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L3383" href="source/net/ipv4/tcp_input.c#L3383">3383</a>         <a href="ident?i=u32">u32</a> <a href="ident?i=now">now</a>;
<a name="L3384" href="source/net/ipv4/tcp_input.c#L3384">3384</a> 
<a name="L3385" href="source/net/ipv4/tcp_input.c#L3385">3385</a>         <b><i>/* First check our per-socket dupack rate limit. */</i></b>
<a name="L3386" href="source/net/ipv4/tcp_input.c#L3386">3386</a>         if (<a href="ident?i=tcp_oow_rate_limited">tcp_oow_rate_limited</a>(<a href="ident?i=sock_net">sock_net</a>(sk), <a href="ident?i=skb">skb</a>,
<a name="L3387" href="source/net/ipv4/tcp_input.c#L3387">3387</a>                                  LINUX_MIB_TCPACKSKIPPEDCHALLENGE,
<a name="L3388" href="source/net/ipv4/tcp_input.c#L3388">3388</a>                                  &amp;<a href="ident?i=tp">tp</a>-&gt;last_oow_ack_time))
<a name="L3389" href="source/net/ipv4/tcp_input.c#L3389">3389</a>                 return;
<a name="L3390" href="source/net/ipv4/tcp_input.c#L3390">3390</a> 
<a name="L3391" href="source/net/ipv4/tcp_input.c#L3391">3391</a>         <b><i>/* Then check the check host-wide RFC 5961 rate limit. */</i></b>
<a name="L3392" href="source/net/ipv4/tcp_input.c#L3392">3392</a>         <a href="ident?i=now">now</a> = <a href="ident?i=jiffies">jiffies</a> / <a href="ident?i=HZ">HZ</a>;
<a name="L3393" href="source/net/ipv4/tcp_input.c#L3393">3393</a>         if (<a href="ident?i=now">now</a> != challenge_timestamp) {
<a name="L3394" href="source/net/ipv4/tcp_input.c#L3394">3394</a>                 challenge_timestamp = <a href="ident?i=now">now</a>;
<a name="L3395" href="source/net/ipv4/tcp_input.c#L3395">3395</a>                 challenge_count = 0;
<a name="L3396" href="source/net/ipv4/tcp_input.c#L3396">3396</a>         }
<a name="L3397" href="source/net/ipv4/tcp_input.c#L3397">3397</a>         if (++challenge_count &lt;= <a href="ident?i=sysctl_tcp_challenge_ack_limit">sysctl_tcp_challenge_ack_limit</a>) {
<a name="L3398" href="source/net/ipv4/tcp_input.c#L3398">3398</a>                 <a href="ident?i=NET_INC_STATS_BH">NET_INC_STATS_BH</a>(<a href="ident?i=sock_net">sock_net</a>(sk), LINUX_MIB_TCPCHALLENGEACK);
<a name="L3399" href="source/net/ipv4/tcp_input.c#L3399">3399</a>                 <a href="ident?i=tcp_send_ack">tcp_send_ack</a>(sk);
<a name="L3400" href="source/net/ipv4/tcp_input.c#L3400">3400</a>         }
<a name="L3401" href="source/net/ipv4/tcp_input.c#L3401">3401</a> }
<a name="L3402" href="source/net/ipv4/tcp_input.c#L3402">3402</a> 
<a name="L3403" href="source/net/ipv4/tcp_input.c#L3403">3403</a> static void <a href="ident?i=tcp_store_ts_recent">tcp_store_ts_recent</a>(struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a>)
<a name="L3404" href="source/net/ipv4/tcp_input.c#L3404">3404</a> {
<a name="L3405" href="source/net/ipv4/tcp_input.c#L3405">3405</a>         <a href="ident?i=tp">tp</a>-&gt;rx_opt.ts_recent = <a href="ident?i=tp">tp</a>-&gt;rx_opt.rcv_tsval;
<a name="L3406" href="source/net/ipv4/tcp_input.c#L3406">3406</a>         <a href="ident?i=tp">tp</a>-&gt;rx_opt.ts_recent_stamp = <a href="ident?i=get_seconds">get_seconds</a>();
<a name="L3407" href="source/net/ipv4/tcp_input.c#L3407">3407</a> }
<a name="L3408" href="source/net/ipv4/tcp_input.c#L3408">3408</a> 
<a name="L3409" href="source/net/ipv4/tcp_input.c#L3409">3409</a> static void <a href="ident?i=tcp_replace_ts_recent">tcp_replace_ts_recent</a>(struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a>, <a href="ident?i=u32">u32</a> <a href="ident?i=seq">seq</a>)
<a name="L3410" href="source/net/ipv4/tcp_input.c#L3410">3410</a> {
<a name="L3411" href="source/net/ipv4/tcp_input.c#L3411">3411</a>         if (<a href="ident?i=tp">tp</a>-&gt;rx_opt.saw_tstamp &amp;&amp; !<a href="ident?i=after">after</a>(<a href="ident?i=seq">seq</a>, <a href="ident?i=tp">tp</a>-&gt;rcv_wup)) {
<a name="L3412" href="source/net/ipv4/tcp_input.c#L3412">3412</a>                 <b><i>/* PAWS bug workaround wrt. ACK frames, the PAWS discard</i></b>
<a name="L3413" href="source/net/ipv4/tcp_input.c#L3413">3413</a> <b><i>                 * extra check below makes sure this can only happen</i></b>
<a name="L3414" href="source/net/ipv4/tcp_input.c#L3414">3414</a> <b><i>                 * for pure ACK frames.  -DaveM</i></b>
<a name="L3415" href="source/net/ipv4/tcp_input.c#L3415">3415</a> <b><i>                 *</i></b>
<a name="L3416" href="source/net/ipv4/tcp_input.c#L3416">3416</a> <b><i>                 * Not only, also it occurs for expired timestamps.</i></b>
<a name="L3417" href="source/net/ipv4/tcp_input.c#L3417">3417</a> <b><i>                 */</i></b>
<a name="L3418" href="source/net/ipv4/tcp_input.c#L3418">3418</a> 
<a name="L3419" href="source/net/ipv4/tcp_input.c#L3419">3419</a>                 if (<a href="ident?i=tcp_paws_check">tcp_paws_check</a>(&amp;<a href="ident?i=tp">tp</a>-&gt;rx_opt, 0))
<a name="L3420" href="source/net/ipv4/tcp_input.c#L3420">3420</a>                         <a href="ident?i=tcp_store_ts_recent">tcp_store_ts_recent</a>(<a href="ident?i=tp">tp</a>);
<a name="L3421" href="source/net/ipv4/tcp_input.c#L3421">3421</a>         }
<a name="L3422" href="source/net/ipv4/tcp_input.c#L3422">3422</a> }
<a name="L3423" href="source/net/ipv4/tcp_input.c#L3423">3423</a> 
<a name="L3424" href="source/net/ipv4/tcp_input.c#L3424">3424</a> <b><i>/* This routine deals with acks during a TLP episode.</i></b>
<a name="L3425" href="source/net/ipv4/tcp_input.c#L3425">3425</a> <b><i> * We mark the end of a TLP episode on receiving TLP dupack or when</i></b>
<a name="L3426" href="source/net/ipv4/tcp_input.c#L3426">3426</a> <b><i> * ack is after tlp_high_seq.</i></b>
<a name="L3427" href="source/net/ipv4/tcp_input.c#L3427">3427</a> <b><i> * Ref: loss detection algorithm in draft-dukkipati-tcpm-tcp-loss-probe.</i></b>
<a name="L3428" href="source/net/ipv4/tcp_input.c#L3428">3428</a> <b><i> */</i></b>
<a name="L3429" href="source/net/ipv4/tcp_input.c#L3429">3429</a> static void <a href="ident?i=tcp_process_tlp_ack">tcp_process_tlp_ack</a>(struct <a href="ident?i=sock">sock</a> *sk, <a href="ident?i=u32">u32</a> ack, int <a href="ident?i=flag">flag</a>)
<a name="L3430" href="source/net/ipv4/tcp_input.c#L3430">3430</a> {
<a name="L3431" href="source/net/ipv4/tcp_input.c#L3431">3431</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L3432" href="source/net/ipv4/tcp_input.c#L3432">3432</a> 
<a name="L3433" href="source/net/ipv4/tcp_input.c#L3433">3433</a>         if (<a href="ident?i=before">before</a>(ack, <a href="ident?i=tp">tp</a>-&gt;tlp_high_seq))
<a name="L3434" href="source/net/ipv4/tcp_input.c#L3434">3434</a>                 return;
<a name="L3435" href="source/net/ipv4/tcp_input.c#L3435">3435</a> 
<a name="L3436" href="source/net/ipv4/tcp_input.c#L3436">3436</a>         if (<a href="ident?i=flag">flag</a> &amp; <a href="ident?i=FLAG_DSACKING_ACK">FLAG_DSACKING_ACK</a>) {
<a name="L3437" href="source/net/ipv4/tcp_input.c#L3437">3437</a>                 <b><i>/* This DSACK means original and TLP probe arrived; no loss */</i></b>
<a name="L3438" href="source/net/ipv4/tcp_input.c#L3438">3438</a>                 <a href="ident?i=tp">tp</a>-&gt;tlp_high_seq = 0;
<a name="L3439" href="source/net/ipv4/tcp_input.c#L3439">3439</a>         } else if (<a href="ident?i=after">after</a>(ack, <a href="ident?i=tp">tp</a>-&gt;tlp_high_seq)) {
<a name="L3440" href="source/net/ipv4/tcp_input.c#L3440">3440</a>                 <b><i>/* ACK advances: there was a loss, so reduce cwnd. Reset</i></b>
<a name="L3441" href="source/net/ipv4/tcp_input.c#L3441">3441</a> <b><i>                 * tlp_high_seq in tcp_init_cwnd_reduction()</i></b>
<a name="L3442" href="source/net/ipv4/tcp_input.c#L3442">3442</a> <b><i>                 */</i></b>
<a name="L3443" href="source/net/ipv4/tcp_input.c#L3443">3443</a>                 <a href="ident?i=tcp_init_cwnd_reduction">tcp_init_cwnd_reduction</a>(sk);
<a name="L3444" href="source/net/ipv4/tcp_input.c#L3444">3444</a>                 <a href="ident?i=tcp_set_ca_state">tcp_set_ca_state</a>(sk, TCP_CA_CWR);
<a name="L3445" href="source/net/ipv4/tcp_input.c#L3445">3445</a>                 <a href="ident?i=tcp_end_cwnd_reduction">tcp_end_cwnd_reduction</a>(sk);
<a name="L3446" href="source/net/ipv4/tcp_input.c#L3446">3446</a>                 <a href="ident?i=tcp_try_keep_open">tcp_try_keep_open</a>(sk);
<a name="L3447" href="source/net/ipv4/tcp_input.c#L3447">3447</a>                 <a href="ident?i=NET_INC_STATS_BH">NET_INC_STATS_BH</a>(<a href="ident?i=sock_net">sock_net</a>(sk),
<a name="L3448" href="source/net/ipv4/tcp_input.c#L3448">3448</a>                                  LINUX_MIB_TCPLOSSPROBERECOVERY);
<a name="L3449" href="source/net/ipv4/tcp_input.c#L3449">3449</a>         } else if (!(<a href="ident?i=flag">flag</a> &amp; (<a href="ident?i=FLAG_SND_UNA_ADVANCED">FLAG_SND_UNA_ADVANCED</a> |
<a name="L3450" href="source/net/ipv4/tcp_input.c#L3450">3450</a>                              <a href="ident?i=FLAG_NOT_DUP">FLAG_NOT_DUP</a> | <a href="ident?i=FLAG_DATA_SACKED">FLAG_DATA_SACKED</a>))) {
<a name="L3451" href="source/net/ipv4/tcp_input.c#L3451">3451</a>                 <b><i>/* Pure dupack: original and TLP probe arrived; no loss */</i></b>
<a name="L3452" href="source/net/ipv4/tcp_input.c#L3452">3452</a>                 <a href="ident?i=tp">tp</a>-&gt;tlp_high_seq = 0;
<a name="L3453" href="source/net/ipv4/tcp_input.c#L3453">3453</a>         }
<a name="L3454" href="source/net/ipv4/tcp_input.c#L3454">3454</a> }
<a name="L3455" href="source/net/ipv4/tcp_input.c#L3455">3455</a> 
<a name="L3456" href="source/net/ipv4/tcp_input.c#L3456">3456</a> static inline void <a href="ident?i=tcp_in_ack_event">tcp_in_ack_event</a>(struct <a href="ident?i=sock">sock</a> *sk, <a href="ident?i=u32">u32</a> <a href="ident?i=flags">flags</a>)
<a name="L3457" href="source/net/ipv4/tcp_input.c#L3457">3457</a> {
<a name="L3458" href="source/net/ipv4/tcp_input.c#L3458">3458</a>         const struct <a href="ident?i=inet_connection_sock">inet_connection_sock</a> *icsk = <a href="ident?i=inet_csk">inet_csk</a>(sk);
<a name="L3459" href="source/net/ipv4/tcp_input.c#L3459">3459</a> 
<a name="L3460" href="source/net/ipv4/tcp_input.c#L3460">3460</a>         if (icsk-&gt;icsk_ca_ops-&gt;in_ack_event)
<a name="L3461" href="source/net/ipv4/tcp_input.c#L3461">3461</a>                 icsk-&gt;icsk_ca_ops-&gt;in_ack_event(sk, <a href="ident?i=flags">flags</a>);
<a name="L3462" href="source/net/ipv4/tcp_input.c#L3462">3462</a> }
<a name="L3463" href="source/net/ipv4/tcp_input.c#L3463">3463</a> 
<a name="L3464" href="source/net/ipv4/tcp_input.c#L3464">3464</a> <b><i>/* This routine deals with incoming acks, but not outgoing ones. */</i></b>
<a name="L3465" href="source/net/ipv4/tcp_input.c#L3465">3465</a> static int <a href="ident?i=tcp_ack">tcp_ack</a>(struct <a href="ident?i=sock">sock</a> *sk, const struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, int <a href="ident?i=flag">flag</a>)
<a name="L3466" href="source/net/ipv4/tcp_input.c#L3466">3466</a> {
<a name="L3467" href="source/net/ipv4/tcp_input.c#L3467">3467</a>         struct <a href="ident?i=inet_connection_sock">inet_connection_sock</a> *icsk = <a href="ident?i=inet_csk">inet_csk</a>(sk);
<a name="L3468" href="source/net/ipv4/tcp_input.c#L3468">3468</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L3469" href="source/net/ipv4/tcp_input.c#L3469">3469</a>         <a href="ident?i=u32">u32</a> prior_snd_una = <a href="ident?i=tp">tp</a>-&gt;snd_una;
<a name="L3470" href="source/net/ipv4/tcp_input.c#L3470">3470</a>         <a href="ident?i=u32">u32</a> ack_seq = <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=seq">seq</a>;
<a name="L3471" href="source/net/ipv4/tcp_input.c#L3471">3471</a>         <a href="ident?i=u32">u32</a> ack = <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;ack_seq;
<a name="L3472" href="source/net/ipv4/tcp_input.c#L3472">3472</a>         <a href="ident?i=bool">bool</a> is_dupack = <a href="ident?i=false">false</a>;
<a name="L3473" href="source/net/ipv4/tcp_input.c#L3473">3473</a>         <a href="ident?i=u32">u32</a> prior_fackets;
<a name="L3474" href="source/net/ipv4/tcp_input.c#L3474">3474</a>         int prior_packets = <a href="ident?i=tp">tp</a>-&gt;packets_out;
<a name="L3475" href="source/net/ipv4/tcp_input.c#L3475">3475</a>         const int prior_unsacked = <a href="ident?i=tp">tp</a>-&gt;packets_out - <a href="ident?i=tp">tp</a>-&gt;sacked_out;
<a name="L3476" href="source/net/ipv4/tcp_input.c#L3476">3476</a>         int acked = 0; <b><i>/* Number of packets newly acked */</i></b>
<a name="L3477" href="source/net/ipv4/tcp_input.c#L3477">3477</a>         long sack_rtt_us = -1L;
<a name="L3478" href="source/net/ipv4/tcp_input.c#L3478">3478</a> 
<a name="L3479" href="source/net/ipv4/tcp_input.c#L3479">3479</a>         <b><i>/* We very likely will need to access write queue head. */</i></b>
<a name="L3480" href="source/net/ipv4/tcp_input.c#L3480">3480</a>         <a href="ident?i=prefetchw">prefetchw</a>(sk-&gt;sk_write_queue.<a href="ident?i=next">next</a>);
<a name="L3481" href="source/net/ipv4/tcp_input.c#L3481">3481</a> 
<a name="L3482" href="source/net/ipv4/tcp_input.c#L3482">3482</a>         <b><i>/* If the ack is older than previous acks</i></b>
<a name="L3483" href="source/net/ipv4/tcp_input.c#L3483">3483</a> <b><i>         * then we can probably ignore it.</i></b>
<a name="L3484" href="source/net/ipv4/tcp_input.c#L3484">3484</a> <b><i>         */</i></b>
<a name="L3485" href="source/net/ipv4/tcp_input.c#L3485">3485</a>         if (<a href="ident?i=before">before</a>(ack, prior_snd_una)) {
<a name="L3486" href="source/net/ipv4/tcp_input.c#L3486">3486</a>                 <b><i>/* RFC 5961 5.2 [Blind Data Injection Attack].[Mitigation] */</i></b>
<a name="L3487" href="source/net/ipv4/tcp_input.c#L3487">3487</a>                 if (<a href="ident?i=before">before</a>(ack, prior_snd_una - <a href="ident?i=tp">tp</a>-&gt;max_window)) {
<a name="L3488" href="source/net/ipv4/tcp_input.c#L3488">3488</a>                         <a href="ident?i=tcp_send_challenge_ack">tcp_send_challenge_ack</a>(sk, <a href="ident?i=skb">skb</a>);
<a name="L3489" href="source/net/ipv4/tcp_input.c#L3489">3489</a>                         return -1;
<a name="L3490" href="source/net/ipv4/tcp_input.c#L3490">3490</a>                 }
<a name="L3491" href="source/net/ipv4/tcp_input.c#L3491">3491</a>                 goto old_ack;
<a name="L3492" href="source/net/ipv4/tcp_input.c#L3492">3492</a>         }
<a name="L3493" href="source/net/ipv4/tcp_input.c#L3493">3493</a> 
<a name="L3494" href="source/net/ipv4/tcp_input.c#L3494">3494</a>         <b><i>/* If the ack includes data we haven't sent yet, discard</i></b>
<a name="L3495" href="source/net/ipv4/tcp_input.c#L3495">3495</a> <b><i>         * this segment (RFC793 Section 3.9).</i></b>
<a name="L3496" href="source/net/ipv4/tcp_input.c#L3496">3496</a> <b><i>         */</i></b>
<a name="L3497" href="source/net/ipv4/tcp_input.c#L3497">3497</a>         if (<a href="ident?i=after">after</a>(ack, <a href="ident?i=tp">tp</a>-&gt;snd_nxt))
<a name="L3498" href="source/net/ipv4/tcp_input.c#L3498">3498</a>                 goto invalid_ack;
<a name="L3499" href="source/net/ipv4/tcp_input.c#L3499">3499</a> 
<a name="L3500" href="source/net/ipv4/tcp_input.c#L3500">3500</a>         if (icsk-&gt;icsk_pending == <a href="ident?i=ICSK_TIME_EARLY_RETRANS">ICSK_TIME_EARLY_RETRANS</a> ||
<a name="L3501" href="source/net/ipv4/tcp_input.c#L3501">3501</a>             icsk-&gt;icsk_pending == <a href="ident?i=ICSK_TIME_LOSS_PROBE">ICSK_TIME_LOSS_PROBE</a>)
<a name="L3502" href="source/net/ipv4/tcp_input.c#L3502">3502</a>                 <a href="ident?i=tcp_rearm_rto">tcp_rearm_rto</a>(sk);
<a name="L3503" href="source/net/ipv4/tcp_input.c#L3503">3503</a> 
<a name="L3504" href="source/net/ipv4/tcp_input.c#L3504">3504</a>         if (<a href="ident?i=after">after</a>(ack, prior_snd_una)) {
<a name="L3505" href="source/net/ipv4/tcp_input.c#L3505">3505</a>                 <a href="ident?i=flag">flag</a> |= <a href="ident?i=FLAG_SND_UNA_ADVANCED">FLAG_SND_UNA_ADVANCED</a>;
<a name="L3506" href="source/net/ipv4/tcp_input.c#L3506">3506</a>                 icsk-&gt;icsk_retransmits = 0;
<a name="L3507" href="source/net/ipv4/tcp_input.c#L3507">3507</a>         }
<a name="L3508" href="source/net/ipv4/tcp_input.c#L3508">3508</a> 
<a name="L3509" href="source/net/ipv4/tcp_input.c#L3509">3509</a>         prior_fackets = <a href="ident?i=tp">tp</a>-&gt;fackets_out;
<a name="L3510" href="source/net/ipv4/tcp_input.c#L3510">3510</a> 
<a name="L3511" href="source/net/ipv4/tcp_input.c#L3511">3511</a>         <b><i>/* ts_recent update must be made after we are sure that the packet</i></b>
<a name="L3512" href="source/net/ipv4/tcp_input.c#L3512">3512</a> <b><i>         * is in window.</i></b>
<a name="L3513" href="source/net/ipv4/tcp_input.c#L3513">3513</a> <b><i>         */</i></b>
<a name="L3514" href="source/net/ipv4/tcp_input.c#L3514">3514</a>         if (<a href="ident?i=flag">flag</a> &amp; <a href="ident?i=FLAG_UPDATE_TS_RECENT">FLAG_UPDATE_TS_RECENT</a>)
<a name="L3515" href="source/net/ipv4/tcp_input.c#L3515">3515</a>                 <a href="ident?i=tcp_replace_ts_recent">tcp_replace_ts_recent</a>(<a href="ident?i=tp">tp</a>, <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=seq">seq</a>);
<a name="L3516" href="source/net/ipv4/tcp_input.c#L3516">3516</a> 
<a name="L3517" href="source/net/ipv4/tcp_input.c#L3517">3517</a>         if (!(<a href="ident?i=flag">flag</a> &amp; <a href="ident?i=FLAG_SLOWPATH">FLAG_SLOWPATH</a>) &amp;&amp; <a href="ident?i=after">after</a>(ack, prior_snd_una)) {
<a name="L3518" href="source/net/ipv4/tcp_input.c#L3518">3518</a>                 <b><i>/* Window is constant, pure forward advance.</i></b>
<a name="L3519" href="source/net/ipv4/tcp_input.c#L3519">3519</a> <b><i>                 * No more checks are required.</i></b>
<a name="L3520" href="source/net/ipv4/tcp_input.c#L3520">3520</a> <b><i>                 * Note, we use the fact that SND.UNA&gt;=SND.WL2.</i></b>
<a name="L3521" href="source/net/ipv4/tcp_input.c#L3521">3521</a> <b><i>                 */</i></b>
<a name="L3522" href="source/net/ipv4/tcp_input.c#L3522">3522</a>                 <a href="ident?i=tcp_update_wl">tcp_update_wl</a>(<a href="ident?i=tp">tp</a>, ack_seq);
<a name="L3523" href="source/net/ipv4/tcp_input.c#L3523">3523</a>                 <a href="ident?i=tcp_snd_una_update">tcp_snd_una_update</a>(<a href="ident?i=tp">tp</a>, ack);
<a name="L3524" href="source/net/ipv4/tcp_input.c#L3524">3524</a>                 <a href="ident?i=flag">flag</a> |= <a href="ident?i=FLAG_WIN_UPDATE">FLAG_WIN_UPDATE</a>;
<a name="L3525" href="source/net/ipv4/tcp_input.c#L3525">3525</a> 
<a name="L3526" href="source/net/ipv4/tcp_input.c#L3526">3526</a>                 <a href="ident?i=tcp_in_ack_event">tcp_in_ack_event</a>(sk, CA_ACK_WIN_UPDATE);
<a name="L3527" href="source/net/ipv4/tcp_input.c#L3527">3527</a> 
<a name="L3528" href="source/net/ipv4/tcp_input.c#L3528">3528</a>                 <a href="ident?i=NET_INC_STATS_BH">NET_INC_STATS_BH</a>(<a href="ident?i=sock_net">sock_net</a>(sk), LINUX_MIB_TCPHPACKS);
<a name="L3529" href="source/net/ipv4/tcp_input.c#L3529">3529</a>         } else {
<a name="L3530" href="source/net/ipv4/tcp_input.c#L3530">3530</a>                 <a href="ident?i=u32">u32</a> ack_ev_flags = CA_ACK_SLOWPATH;
<a name="L3531" href="source/net/ipv4/tcp_input.c#L3531">3531</a> 
<a name="L3532" href="source/net/ipv4/tcp_input.c#L3532">3532</a>                 if (ack_seq != <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;end_seq)
<a name="L3533" href="source/net/ipv4/tcp_input.c#L3533">3533</a>                         <a href="ident?i=flag">flag</a> |= <a href="ident?i=FLAG_DATA">FLAG_DATA</a>;
<a name="L3534" href="source/net/ipv4/tcp_input.c#L3534">3534</a>                 else
<a name="L3535" href="source/net/ipv4/tcp_input.c#L3535">3535</a>                         <a href="ident?i=NET_INC_STATS_BH">NET_INC_STATS_BH</a>(<a href="ident?i=sock_net">sock_net</a>(sk), LINUX_MIB_TCPPUREACKS);
<a name="L3536" href="source/net/ipv4/tcp_input.c#L3536">3536</a> 
<a name="L3537" href="source/net/ipv4/tcp_input.c#L3537">3537</a>                 <a href="ident?i=flag">flag</a> |= <a href="ident?i=tcp_ack_update_window">tcp_ack_update_window</a>(sk, <a href="ident?i=skb">skb</a>, ack, ack_seq);
<a name="L3538" href="source/net/ipv4/tcp_input.c#L3538">3538</a> 
<a name="L3539" href="source/net/ipv4/tcp_input.c#L3539">3539</a>                 if (<a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;sacked)
<a name="L3540" href="source/net/ipv4/tcp_input.c#L3540">3540</a>                         <a href="ident?i=flag">flag</a> |= <a href="ident?i=tcp_sacktag_write_queue">tcp_sacktag_write_queue</a>(sk, <a href="ident?i=skb">skb</a>, prior_snd_una,
<a name="L3541" href="source/net/ipv4/tcp_input.c#L3541">3541</a>                                                         &amp;sack_rtt_us);
<a name="L3542" href="source/net/ipv4/tcp_input.c#L3542">3542</a> 
<a name="L3543" href="source/net/ipv4/tcp_input.c#L3543">3543</a>                 if (<a href="ident?i=tcp_ecn_rcv_ecn_echo">tcp_ecn_rcv_ecn_echo</a>(<a href="ident?i=tp">tp</a>, <a href="ident?i=tcp_hdr">tcp_hdr</a>(<a href="ident?i=skb">skb</a>))) {
<a name="L3544" href="source/net/ipv4/tcp_input.c#L3544">3544</a>                         <a href="ident?i=flag">flag</a> |= <a href="ident?i=FLAG_ECE">FLAG_ECE</a>;
<a name="L3545" href="source/net/ipv4/tcp_input.c#L3545">3545</a>                         ack_ev_flags |= CA_ACK_ECE;
<a name="L3546" href="source/net/ipv4/tcp_input.c#L3546">3546</a>                 }
<a name="L3547" href="source/net/ipv4/tcp_input.c#L3547">3547</a> 
<a name="L3548" href="source/net/ipv4/tcp_input.c#L3548">3548</a>                 if (<a href="ident?i=flag">flag</a> &amp; <a href="ident?i=FLAG_WIN_UPDATE">FLAG_WIN_UPDATE</a>)
<a name="L3549" href="source/net/ipv4/tcp_input.c#L3549">3549</a>                         ack_ev_flags |= CA_ACK_WIN_UPDATE;
<a name="L3550" href="source/net/ipv4/tcp_input.c#L3550">3550</a> 
<a name="L3551" href="source/net/ipv4/tcp_input.c#L3551">3551</a>                 <a href="ident?i=tcp_in_ack_event">tcp_in_ack_event</a>(sk, ack_ev_flags);
<a name="L3552" href="source/net/ipv4/tcp_input.c#L3552">3552</a>         }
<a name="L3553" href="source/net/ipv4/tcp_input.c#L3553">3553</a> 
<a name="L3554" href="source/net/ipv4/tcp_input.c#L3554">3554</a>         <b><i>/* We passed data and got it acked, remove any soft error</i></b>
<a name="L3555" href="source/net/ipv4/tcp_input.c#L3555">3555</a> <b><i>         * log. Something worked...</i></b>
<a name="L3556" href="source/net/ipv4/tcp_input.c#L3556">3556</a> <b><i>         */</i></b>
<a name="L3557" href="source/net/ipv4/tcp_input.c#L3557">3557</a>         sk-&gt;sk_err_soft = 0;
<a name="L3558" href="source/net/ipv4/tcp_input.c#L3558">3558</a>         icsk-&gt;icsk_probes_out = 0;
<a name="L3559" href="source/net/ipv4/tcp_input.c#L3559">3559</a>         <a href="ident?i=tp">tp</a>-&gt;rcv_tstamp = <a href="ident?i=tcp_time_stamp">tcp_time_stamp</a>;
<a name="L3560" href="source/net/ipv4/tcp_input.c#L3560">3560</a>         if (!prior_packets)
<a name="L3561" href="source/net/ipv4/tcp_input.c#L3561">3561</a>                 goto no_queue;
<a name="L3562" href="source/net/ipv4/tcp_input.c#L3562">3562</a> 
<a name="L3563" href="source/net/ipv4/tcp_input.c#L3563">3563</a>         <b><i>/* See if we can take anything off of the retransmit queue. */</i></b>
<a name="L3564" href="source/net/ipv4/tcp_input.c#L3564">3564</a>         acked = <a href="ident?i=tp">tp</a>-&gt;packets_out;
<a name="L3565" href="source/net/ipv4/tcp_input.c#L3565">3565</a>         <a href="ident?i=flag">flag</a> |= <a href="ident?i=tcp_clean_rtx_queue">tcp_clean_rtx_queue</a>(sk, prior_fackets, prior_snd_una,
<a name="L3566" href="source/net/ipv4/tcp_input.c#L3566">3566</a>                                     sack_rtt_us);
<a name="L3567" href="source/net/ipv4/tcp_input.c#L3567">3567</a>         acked -= <a href="ident?i=tp">tp</a>-&gt;packets_out;
<a name="L3568" href="source/net/ipv4/tcp_input.c#L3568">3568</a> 
<a name="L3569" href="source/net/ipv4/tcp_input.c#L3569">3569</a>         <b><i>/* Advance cwnd if state allows */</i></b>
<a name="L3570" href="source/net/ipv4/tcp_input.c#L3570">3570</a>         if (<a href="ident?i=tcp_may_raise_cwnd">tcp_may_raise_cwnd</a>(sk, <a href="ident?i=flag">flag</a>))
<a name="L3571" href="source/net/ipv4/tcp_input.c#L3571">3571</a>                 <a href="ident?i=tcp_cong_avoid">tcp_cong_avoid</a>(sk, ack, acked);
<a name="L3572" href="source/net/ipv4/tcp_input.c#L3572">3572</a> 
<a name="L3573" href="source/net/ipv4/tcp_input.c#L3573">3573</a>         if (<a href="ident?i=tcp_ack_is_dubious">tcp_ack_is_dubious</a>(sk, <a href="ident?i=flag">flag</a>)) {
<a name="L3574" href="source/net/ipv4/tcp_input.c#L3574">3574</a>                 is_dupack = !(<a href="ident?i=flag">flag</a> &amp; (<a href="ident?i=FLAG_SND_UNA_ADVANCED">FLAG_SND_UNA_ADVANCED</a> | <a href="ident?i=FLAG_NOT_DUP">FLAG_NOT_DUP</a>));
<a name="L3575" href="source/net/ipv4/tcp_input.c#L3575">3575</a>                 <a href="ident?i=tcp_fastretrans_alert">tcp_fastretrans_alert</a>(sk, acked, prior_unsacked,
<a name="L3576" href="source/net/ipv4/tcp_input.c#L3576">3576</a>                                       is_dupack, <a href="ident?i=flag">flag</a>);
<a name="L3577" href="source/net/ipv4/tcp_input.c#L3577">3577</a>         }
<a name="L3578" href="source/net/ipv4/tcp_input.c#L3578">3578</a>         if (<a href="ident?i=tp">tp</a>-&gt;tlp_high_seq)
<a name="L3579" href="source/net/ipv4/tcp_input.c#L3579">3579</a>                 <a href="ident?i=tcp_process_tlp_ack">tcp_process_tlp_ack</a>(sk, ack, <a href="ident?i=flag">flag</a>);
<a name="L3580" href="source/net/ipv4/tcp_input.c#L3580">3580</a> 
<a name="L3581" href="source/net/ipv4/tcp_input.c#L3581">3581</a>         if ((<a href="ident?i=flag">flag</a> &amp; <a href="ident?i=FLAG_FORWARD_PROGRESS">FLAG_FORWARD_PROGRESS</a>) || !(<a href="ident?i=flag">flag</a> &amp; <a href="ident?i=FLAG_NOT_DUP">FLAG_NOT_DUP</a>)) {
<a name="L3582" href="source/net/ipv4/tcp_input.c#L3582">3582</a>                 struct <a href="ident?i=dst_entry">dst_entry</a> *<a href="ident?i=dst">dst</a> = <a href="ident?i=__sk_dst_get">__sk_dst_get</a>(sk);
<a name="L3583" href="source/net/ipv4/tcp_input.c#L3583">3583</a>                 if (<a href="ident?i=dst">dst</a>)
<a name="L3584" href="source/net/ipv4/tcp_input.c#L3584">3584</a>                         <a href="ident?i=dst_confirm">dst_confirm</a>(<a href="ident?i=dst">dst</a>);
<a name="L3585" href="source/net/ipv4/tcp_input.c#L3585">3585</a>         }
<a name="L3586" href="source/net/ipv4/tcp_input.c#L3586">3586</a> 
<a name="L3587" href="source/net/ipv4/tcp_input.c#L3587">3587</a>         if (icsk-&gt;icsk_pending == <a href="ident?i=ICSK_TIME_RETRANS">ICSK_TIME_RETRANS</a>)
<a name="L3588" href="source/net/ipv4/tcp_input.c#L3588">3588</a>                 <a href="ident?i=tcp_schedule_loss_probe">tcp_schedule_loss_probe</a>(sk);
<a name="L3589" href="source/net/ipv4/tcp_input.c#L3589">3589</a>         <a href="ident?i=tcp_update_pacing_rate">tcp_update_pacing_rate</a>(sk);
<a name="L3590" href="source/net/ipv4/tcp_input.c#L3590">3590</a>         return 1;
<a name="L3591" href="source/net/ipv4/tcp_input.c#L3591">3591</a> 
<a name="L3592" href="source/net/ipv4/tcp_input.c#L3592">3592</a> no_queue:
<a name="L3593" href="source/net/ipv4/tcp_input.c#L3593">3593</a>         <b><i>/* If data was DSACKed, see if we can undo a cwnd reduction. */</i></b>
<a name="L3594" href="source/net/ipv4/tcp_input.c#L3594">3594</a>         if (<a href="ident?i=flag">flag</a> &amp; <a href="ident?i=FLAG_DSACKING_ACK">FLAG_DSACKING_ACK</a>)
<a name="L3595" href="source/net/ipv4/tcp_input.c#L3595">3595</a>                 <a href="ident?i=tcp_fastretrans_alert">tcp_fastretrans_alert</a>(sk, acked, prior_unsacked,
<a name="L3596" href="source/net/ipv4/tcp_input.c#L3596">3596</a>                                       is_dupack, <a href="ident?i=flag">flag</a>);
<a name="L3597" href="source/net/ipv4/tcp_input.c#L3597">3597</a>         <b><i>/* If this ack opens up a zero window, clear backoff.  It was</i></b>
<a name="L3598" href="source/net/ipv4/tcp_input.c#L3598">3598</a> <b><i>         * being used to time the probes, and is probably far higher than</i></b>
<a name="L3599" href="source/net/ipv4/tcp_input.c#L3599">3599</a> <b><i>         * it needs to be for normal retransmission.</i></b>
<a name="L3600" href="source/net/ipv4/tcp_input.c#L3600">3600</a> <b><i>         */</i></b>
<a name="L3601" href="source/net/ipv4/tcp_input.c#L3601">3601</a>         if (<a href="ident?i=tcp_send_head">tcp_send_head</a>(sk))
<a name="L3602" href="source/net/ipv4/tcp_input.c#L3602">3602</a>                 <a href="ident?i=tcp_ack_probe">tcp_ack_probe</a>(sk);
<a name="L3603" href="source/net/ipv4/tcp_input.c#L3603">3603</a> 
<a name="L3604" href="source/net/ipv4/tcp_input.c#L3604">3604</a>         if (<a href="ident?i=tp">tp</a>-&gt;tlp_high_seq)
<a name="L3605" href="source/net/ipv4/tcp_input.c#L3605">3605</a>                 <a href="ident?i=tcp_process_tlp_ack">tcp_process_tlp_ack</a>(sk, ack, <a href="ident?i=flag">flag</a>);
<a name="L3606" href="source/net/ipv4/tcp_input.c#L3606">3606</a>         return 1;
<a name="L3607" href="source/net/ipv4/tcp_input.c#L3607">3607</a> 
<a name="L3608" href="source/net/ipv4/tcp_input.c#L3608">3608</a> invalid_ack:
<a name="L3609" href="source/net/ipv4/tcp_input.c#L3609">3609</a>         <a href="ident?i=SOCK_DEBUG">SOCK_DEBUG</a>(sk, <i>"Ack %u after %u:%u\n"</i>, ack, <a href="ident?i=tp">tp</a>-&gt;snd_una, <a href="ident?i=tp">tp</a>-&gt;snd_nxt);
<a name="L3610" href="source/net/ipv4/tcp_input.c#L3610">3610</a>         return -1;
<a name="L3611" href="source/net/ipv4/tcp_input.c#L3611">3611</a> 
<a name="L3612" href="source/net/ipv4/tcp_input.c#L3612">3612</a> old_ack:
<a name="L3613" href="source/net/ipv4/tcp_input.c#L3613">3613</a>         <b><i>/* If data was SACKed, tag it and see if we should send more data.</i></b>
<a name="L3614" href="source/net/ipv4/tcp_input.c#L3614">3614</a> <b><i>         * If data was DSACKed, see if we can undo a cwnd reduction.</i></b>
<a name="L3615" href="source/net/ipv4/tcp_input.c#L3615">3615</a> <b><i>         */</i></b>
<a name="L3616" href="source/net/ipv4/tcp_input.c#L3616">3616</a>         if (<a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;sacked) {
<a name="L3617" href="source/net/ipv4/tcp_input.c#L3617">3617</a>                 <a href="ident?i=flag">flag</a> |= <a href="ident?i=tcp_sacktag_write_queue">tcp_sacktag_write_queue</a>(sk, <a href="ident?i=skb">skb</a>, prior_snd_una,
<a name="L3618" href="source/net/ipv4/tcp_input.c#L3618">3618</a>                                                 &amp;sack_rtt_us);
<a name="L3619" href="source/net/ipv4/tcp_input.c#L3619">3619</a>                 <a href="ident?i=tcp_fastretrans_alert">tcp_fastretrans_alert</a>(sk, acked, prior_unsacked,
<a name="L3620" href="source/net/ipv4/tcp_input.c#L3620">3620</a>                                       is_dupack, <a href="ident?i=flag">flag</a>);
<a name="L3621" href="source/net/ipv4/tcp_input.c#L3621">3621</a>         }
<a name="L3622" href="source/net/ipv4/tcp_input.c#L3622">3622</a> 
<a name="L3623" href="source/net/ipv4/tcp_input.c#L3623">3623</a>         <a href="ident?i=SOCK_DEBUG">SOCK_DEBUG</a>(sk, <i>"Ack %u before %u:%u\n"</i>, ack, <a href="ident?i=tp">tp</a>-&gt;snd_una, <a href="ident?i=tp">tp</a>-&gt;snd_nxt);
<a name="L3624" href="source/net/ipv4/tcp_input.c#L3624">3624</a>         return 0;
<a name="L3625" href="source/net/ipv4/tcp_input.c#L3625">3625</a> }
<a name="L3626" href="source/net/ipv4/tcp_input.c#L3626">3626</a> 
<a name="L3627" href="source/net/ipv4/tcp_input.c#L3627">3627</a> static void <a href="ident?i=tcp_parse_fastopen_option">tcp_parse_fastopen_option</a>(int <a href="ident?i=len">len</a>, const unsigned char *cookie,
<a name="L3628" href="source/net/ipv4/tcp_input.c#L3628">3628</a>                                       <a href="ident?i=bool">bool</a> syn, struct <a href="ident?i=tcp_fastopen_cookie">tcp_fastopen_cookie</a> *foc,
<a name="L3629" href="source/net/ipv4/tcp_input.c#L3629">3629</a>                                       <a href="ident?i=bool">bool</a> exp_opt)
<a name="L3630" href="source/net/ipv4/tcp_input.c#L3630">3630</a> {
<a name="L3631" href="source/net/ipv4/tcp_input.c#L3631">3631</a>         <b><i>/* Valid only in SYN or SYN-ACK with an even length.  */</i></b>
<a name="L3632" href="source/net/ipv4/tcp_input.c#L3632">3632</a>         if (!foc || !syn || <a href="ident?i=len">len</a> &lt; 0 || (<a href="ident?i=len">len</a> &amp; 1))
<a name="L3633" href="source/net/ipv4/tcp_input.c#L3633">3633</a>                 return;
<a name="L3634" href="source/net/ipv4/tcp_input.c#L3634">3634</a> 
<a name="L3635" href="source/net/ipv4/tcp_input.c#L3635">3635</a>         if (<a href="ident?i=len">len</a> &gt;= <a href="ident?i=TCP_FASTOPEN_COOKIE_MIN">TCP_FASTOPEN_COOKIE_MIN</a> &amp;&amp;
<a name="L3636" href="source/net/ipv4/tcp_input.c#L3636">3636</a>             <a href="ident?i=len">len</a> &lt;= <a href="ident?i=TCP_FASTOPEN_COOKIE_MAX">TCP_FASTOPEN_COOKIE_MAX</a>)
<a name="L3637" href="source/net/ipv4/tcp_input.c#L3637">3637</a>                 <a href="ident?i=memcpy">memcpy</a>(foc-&gt;<a href="ident?i=val">val</a>, cookie, <a href="ident?i=len">len</a>);
<a name="L3638" href="source/net/ipv4/tcp_input.c#L3638">3638</a>         else if (<a href="ident?i=len">len</a> != 0)
<a name="L3639" href="source/net/ipv4/tcp_input.c#L3639">3639</a>                 <a href="ident?i=len">len</a> = -1;
<a name="L3640" href="source/net/ipv4/tcp_input.c#L3640">3640</a>         foc-&gt;<a href="ident?i=len">len</a> = <a href="ident?i=len">len</a>;
<a name="L3641" href="source/net/ipv4/tcp_input.c#L3641">3641</a>         foc-&gt;exp = exp_opt;
<a name="L3642" href="source/net/ipv4/tcp_input.c#L3642">3642</a> }
<a name="L3643" href="source/net/ipv4/tcp_input.c#L3643">3643</a> 
<a name="L3644" href="source/net/ipv4/tcp_input.c#L3644">3644</a> <b><i>/* Look for tcp options. Normally only called on SYN and SYNACK packets.</i></b>
<a name="L3645" href="source/net/ipv4/tcp_input.c#L3645">3645</a> <b><i> * But, this can also be called on packets in the established flow when</i></b>
<a name="L3646" href="source/net/ipv4/tcp_input.c#L3646">3646</a> <b><i> * the fast version below fails.</i></b>
<a name="L3647" href="source/net/ipv4/tcp_input.c#L3647">3647</a> <b><i> */</i></b>
<a name="L3648" href="source/net/ipv4/tcp_input.c#L3648">3648</a> void <a href="ident?i=tcp_parse_options">tcp_parse_options</a>(const struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
<a name="L3649" href="source/net/ipv4/tcp_input.c#L3649">3649</a>                        struct <a href="ident?i=tcp_options_received">tcp_options_received</a> *opt_rx, int estab,
<a name="L3650" href="source/net/ipv4/tcp_input.c#L3650">3650</a>                        struct <a href="ident?i=tcp_fastopen_cookie">tcp_fastopen_cookie</a> *foc)
<a name="L3651" href="source/net/ipv4/tcp_input.c#L3651">3651</a> {
<a name="L3652" href="source/net/ipv4/tcp_input.c#L3652">3652</a>         const unsigned char *<a href="ident?i=ptr">ptr</a>;
<a name="L3653" href="source/net/ipv4/tcp_input.c#L3653">3653</a>         const struct <a href="ident?i=tcphdr">tcphdr</a> *<a href="ident?i=th">th</a> = <a href="ident?i=tcp_hdr">tcp_hdr</a>(<a href="ident?i=skb">skb</a>);
<a name="L3654" href="source/net/ipv4/tcp_input.c#L3654">3654</a>         int <a href="ident?i=length">length</a> = (<a href="ident?i=th">th</a>-&gt;doff * 4) - sizeof(struct <a href="ident?i=tcphdr">tcphdr</a>);
<a name="L3655" href="source/net/ipv4/tcp_input.c#L3655">3655</a> 
<a name="L3656" href="source/net/ipv4/tcp_input.c#L3656">3656</a>         <a href="ident?i=ptr">ptr</a> = (const unsigned char *)(<a href="ident?i=th">th</a> + 1);
<a name="L3657" href="source/net/ipv4/tcp_input.c#L3657">3657</a>         opt_rx-&gt;saw_tstamp = 0;
<a name="L3658" href="source/net/ipv4/tcp_input.c#L3658">3658</a> 
<a name="L3659" href="source/net/ipv4/tcp_input.c#L3659">3659</a>         while (<a href="ident?i=length">length</a> &gt; 0) {
<a name="L3660" href="source/net/ipv4/tcp_input.c#L3660">3660</a>                 int <a href="ident?i=opcode">opcode</a> = *<a href="ident?i=ptr">ptr</a>++;
<a name="L3661" href="source/net/ipv4/tcp_input.c#L3661">3661</a>                 int opsize;
<a name="L3662" href="source/net/ipv4/tcp_input.c#L3662">3662</a> 
<a name="L3663" href="source/net/ipv4/tcp_input.c#L3663">3663</a>                 switch (<a href="ident?i=opcode">opcode</a>) {
<a name="L3664" href="source/net/ipv4/tcp_input.c#L3664">3664</a>                 case <a href="ident?i=TCPOPT_EOL">TCPOPT_EOL</a>:
<a name="L3665" href="source/net/ipv4/tcp_input.c#L3665">3665</a>                         return;
<a name="L3666" href="source/net/ipv4/tcp_input.c#L3666">3666</a>                 case <a href="ident?i=TCPOPT_NOP">TCPOPT_NOP</a>:        <b><i>/* Ref: RFC 793 section 3.1 */</i></b>
<a name="L3667" href="source/net/ipv4/tcp_input.c#L3667">3667</a>                         <a href="ident?i=length">length</a>--;
<a name="L3668" href="source/net/ipv4/tcp_input.c#L3668">3668</a>                         continue;
<a name="L3669" href="source/net/ipv4/tcp_input.c#L3669">3669</a>                 default:
<a name="L3670" href="source/net/ipv4/tcp_input.c#L3670">3670</a>                         opsize = *<a href="ident?i=ptr">ptr</a>++;
<a name="L3671" href="source/net/ipv4/tcp_input.c#L3671">3671</a>                         if (opsize &lt; 2) <b><i>/* "silly options" */</i></b>
<a name="L3672" href="source/net/ipv4/tcp_input.c#L3672">3672</a>                                 return;
<a name="L3673" href="source/net/ipv4/tcp_input.c#L3673">3673</a>                         if (opsize &gt; <a href="ident?i=length">length</a>)
<a name="L3674" href="source/net/ipv4/tcp_input.c#L3674">3674</a>                                 return; <b><i>/* don't parse partial options */</i></b>
<a name="L3675" href="source/net/ipv4/tcp_input.c#L3675">3675</a>                         switch (<a href="ident?i=opcode">opcode</a>) {
<a name="L3676" href="source/net/ipv4/tcp_input.c#L3676">3676</a>                         case <a href="ident?i=TCPOPT_MSS">TCPOPT_MSS</a>:
<a name="L3677" href="source/net/ipv4/tcp_input.c#L3677">3677</a>                                 if (opsize == <a href="ident?i=TCPOLEN_MSS">TCPOLEN_MSS</a> &amp;&amp; <a href="ident?i=th">th</a>-&gt;syn &amp;&amp; !estab) {
<a name="L3678" href="source/net/ipv4/tcp_input.c#L3678">3678</a>                                         <a href="ident?i=u16">u16</a> in_mss = <a href="ident?i=get_unaligned_be16">get_unaligned_be16</a>(<a href="ident?i=ptr">ptr</a>);
<a name="L3679" href="source/net/ipv4/tcp_input.c#L3679">3679</a>                                         if (in_mss) {
<a name="L3680" href="source/net/ipv4/tcp_input.c#L3680">3680</a>                                                 if (opt_rx-&gt;user_mss &amp;&amp;
<a name="L3681" href="source/net/ipv4/tcp_input.c#L3681">3681</a>                                                     opt_rx-&gt;user_mss &lt; in_mss)
<a name="L3682" href="source/net/ipv4/tcp_input.c#L3682">3682</a>                                                         in_mss = opt_rx-&gt;user_mss;
<a name="L3683" href="source/net/ipv4/tcp_input.c#L3683">3683</a>                                                 opt_rx-&gt;mss_clamp = in_mss;
<a name="L3684" href="source/net/ipv4/tcp_input.c#L3684">3684</a>                                         }
<a name="L3685" href="source/net/ipv4/tcp_input.c#L3685">3685</a>                                 }
<a name="L3686" href="source/net/ipv4/tcp_input.c#L3686">3686</a>                                 break;
<a name="L3687" href="source/net/ipv4/tcp_input.c#L3687">3687</a>                         case <a href="ident?i=TCPOPT_WINDOW">TCPOPT_WINDOW</a>:
<a name="L3688" href="source/net/ipv4/tcp_input.c#L3688">3688</a>                                 if (opsize == <a href="ident?i=TCPOLEN_WINDOW">TCPOLEN_WINDOW</a> &amp;&amp; <a href="ident?i=th">th</a>-&gt;syn &amp;&amp;
<a name="L3689" href="source/net/ipv4/tcp_input.c#L3689">3689</a>                                     !estab &amp;&amp; <a href="ident?i=sysctl_tcp_window_scaling">sysctl_tcp_window_scaling</a>) {
<a name="L3690" href="source/net/ipv4/tcp_input.c#L3690">3690</a>                                         <a href="ident?i=__u8">__u8</a> snd_wscale = *(<a href="ident?i=__u8">__u8</a> *)<a href="ident?i=ptr">ptr</a>;
<a name="L3691" href="source/net/ipv4/tcp_input.c#L3691">3691</a>                                         opt_rx-&gt;wscale_ok = 1;
<a name="L3692" href="source/net/ipv4/tcp_input.c#L3692">3692</a>                                         if (snd_wscale &gt; 14) {
<a name="L3693" href="source/net/ipv4/tcp_input.c#L3693">3693</a>                                                 <a href="ident?i=net_info_ratelimited">net_info_ratelimited</a>(<i>"%s: Illegal window scaling value %d &gt;14 received\n"</i>,
<a name="L3694" href="source/net/ipv4/tcp_input.c#L3694">3694</a>                                                                      <a href="ident?i=__func__">__func__</a>,
<a name="L3695" href="source/net/ipv4/tcp_input.c#L3695">3695</a>                                                                      snd_wscale);
<a name="L3696" href="source/net/ipv4/tcp_input.c#L3696">3696</a>                                                 snd_wscale = 14;
<a name="L3697" href="source/net/ipv4/tcp_input.c#L3697">3697</a>                                         }
<a name="L3698" href="source/net/ipv4/tcp_input.c#L3698">3698</a>                                         opt_rx-&gt;snd_wscale = snd_wscale;
<a name="L3699" href="source/net/ipv4/tcp_input.c#L3699">3699</a>                                 }
<a name="L3700" href="source/net/ipv4/tcp_input.c#L3700">3700</a>                                 break;
<a name="L3701" href="source/net/ipv4/tcp_input.c#L3701">3701</a>                         case <a href="ident?i=TCPOPT_TIMESTAMP">TCPOPT_TIMESTAMP</a>:
<a name="L3702" href="source/net/ipv4/tcp_input.c#L3702">3702</a>                                 if ((opsize == <a href="ident?i=TCPOLEN_TIMESTAMP">TCPOLEN_TIMESTAMP</a>) &amp;&amp;
<a name="L3703" href="source/net/ipv4/tcp_input.c#L3703">3703</a>                                     ((estab &amp;&amp; opt_rx-&gt;tstamp_ok) ||
<a name="L3704" href="source/net/ipv4/tcp_input.c#L3704">3704</a>                                      (!estab &amp;&amp; <a href="ident?i=sysctl_tcp_timestamps">sysctl_tcp_timestamps</a>))) {
<a name="L3705" href="source/net/ipv4/tcp_input.c#L3705">3705</a>                                         opt_rx-&gt;saw_tstamp = 1;
<a name="L3706" href="source/net/ipv4/tcp_input.c#L3706">3706</a>                                         opt_rx-&gt;rcv_tsval = <a href="ident?i=get_unaligned_be32">get_unaligned_be32</a>(<a href="ident?i=ptr">ptr</a>);
<a name="L3707" href="source/net/ipv4/tcp_input.c#L3707">3707</a>                                         opt_rx-&gt;rcv_tsecr = <a href="ident?i=get_unaligned_be32">get_unaligned_be32</a>(<a href="ident?i=ptr">ptr</a> + 4);
<a name="L3708" href="source/net/ipv4/tcp_input.c#L3708">3708</a>                                 }
<a name="L3709" href="source/net/ipv4/tcp_input.c#L3709">3709</a>                                 break;
<a name="L3710" href="source/net/ipv4/tcp_input.c#L3710">3710</a>                         case <a href="ident?i=TCPOPT_SACK_PERM">TCPOPT_SACK_PERM</a>:
<a name="L3711" href="source/net/ipv4/tcp_input.c#L3711">3711</a>                                 if (opsize == <a href="ident?i=TCPOLEN_SACK_PERM">TCPOLEN_SACK_PERM</a> &amp;&amp; <a href="ident?i=th">th</a>-&gt;syn &amp;&amp;
<a name="L3712" href="source/net/ipv4/tcp_input.c#L3712">3712</a>                                     !estab &amp;&amp; <a href="ident?i=sysctl_tcp_sack">sysctl_tcp_sack</a>) {
<a name="L3713" href="source/net/ipv4/tcp_input.c#L3713">3713</a>                                         opt_rx-&gt;sack_ok = <a href="ident?i=TCP_SACK_SEEN">TCP_SACK_SEEN</a>;
<a name="L3714" href="source/net/ipv4/tcp_input.c#L3714">3714</a>                                         <a href="ident?i=tcp_sack_reset">tcp_sack_reset</a>(opt_rx);
<a name="L3715" href="source/net/ipv4/tcp_input.c#L3715">3715</a>                                 }
<a name="L3716" href="source/net/ipv4/tcp_input.c#L3716">3716</a>                                 break;
<a name="L3717" href="source/net/ipv4/tcp_input.c#L3717">3717</a> 
<a name="L3718" href="source/net/ipv4/tcp_input.c#L3718">3718</a>                         case <a href="ident?i=TCPOPT_SACK">TCPOPT_SACK</a>:
<a name="L3719" href="source/net/ipv4/tcp_input.c#L3719">3719</a>                                 if ((opsize &gt;= (<a href="ident?i=TCPOLEN_SACK_BASE">TCPOLEN_SACK_BASE</a> + <a href="ident?i=TCPOLEN_SACK_PERBLOCK">TCPOLEN_SACK_PERBLOCK</a>)) &amp;&amp;
<a name="L3720" href="source/net/ipv4/tcp_input.c#L3720">3720</a>                                    !((opsize - <a href="ident?i=TCPOLEN_SACK_BASE">TCPOLEN_SACK_BASE</a>) % <a href="ident?i=TCPOLEN_SACK_PERBLOCK">TCPOLEN_SACK_PERBLOCK</a>) &amp;&amp;
<a name="L3721" href="source/net/ipv4/tcp_input.c#L3721">3721</a>                                    opt_rx-&gt;sack_ok) {
<a name="L3722" href="source/net/ipv4/tcp_input.c#L3722">3722</a>                                         <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;sacked = (<a href="ident?i=ptr">ptr</a> - 2) - (unsigned char *)<a href="ident?i=th">th</a>;
<a name="L3723" href="source/net/ipv4/tcp_input.c#L3723">3723</a>                                 }
<a name="L3724" href="source/net/ipv4/tcp_input.c#L3724">3724</a>                                 break;
<a name="L3725" href="source/net/ipv4/tcp_input.c#L3725">3725</a> #ifdef CONFIG_TCP_MD5SIG
<a name="L3726" href="source/net/ipv4/tcp_input.c#L3726">3726</a>                         case <a href="ident?i=TCPOPT_MD5SIG">TCPOPT_MD5SIG</a>:
<a name="L3727" href="source/net/ipv4/tcp_input.c#L3727">3727</a>                                 <b><i>/*</i></b>
<a name="L3728" href="source/net/ipv4/tcp_input.c#L3728">3728</a> <b><i>                                 * The MD5 Hash has already been</i></b>
<a name="L3729" href="source/net/ipv4/tcp_input.c#L3729">3729</a> <b><i>                                 * checked (see tcp_v{4,6}_do_rcv()).</i></b>
<a name="L3730" href="source/net/ipv4/tcp_input.c#L3730">3730</a> <b><i>                                 */</i></b>
<a name="L3731" href="source/net/ipv4/tcp_input.c#L3731">3731</a>                                 break;
<a name="L3732" href="source/net/ipv4/tcp_input.c#L3732">3732</a> #endif
<a name="L3733" href="source/net/ipv4/tcp_input.c#L3733">3733</a>                         case <a href="ident?i=TCPOPT_FASTOPEN">TCPOPT_FASTOPEN</a>:
<a name="L3734" href="source/net/ipv4/tcp_input.c#L3734">3734</a>                                 <a href="ident?i=tcp_parse_fastopen_option">tcp_parse_fastopen_option</a>(
<a name="L3735" href="source/net/ipv4/tcp_input.c#L3735">3735</a>                                         opsize - <a href="ident?i=TCPOLEN_FASTOPEN_BASE">TCPOLEN_FASTOPEN_BASE</a>,
<a name="L3736" href="source/net/ipv4/tcp_input.c#L3736">3736</a>                                         <a href="ident?i=ptr">ptr</a>, <a href="ident?i=th">th</a>-&gt;syn, foc, <a href="ident?i=false">false</a>);
<a name="L3737" href="source/net/ipv4/tcp_input.c#L3737">3737</a>                                 break;
<a name="L3738" href="source/net/ipv4/tcp_input.c#L3738">3738</a> 
<a name="L3739" href="source/net/ipv4/tcp_input.c#L3739">3739</a>                         case <a href="ident?i=TCPOPT_EXP">TCPOPT_EXP</a>:
<a name="L3740" href="source/net/ipv4/tcp_input.c#L3740">3740</a>                                 <b><i>/* Fast Open option shares code 254 using a</i></b>
<a name="L3741" href="source/net/ipv4/tcp_input.c#L3741">3741</a> <b><i>                                 * 16 bits magic number.</i></b>
<a name="L3742" href="source/net/ipv4/tcp_input.c#L3742">3742</a> <b><i>                                 */</i></b>
<a name="L3743" href="source/net/ipv4/tcp_input.c#L3743">3743</a>                                 if (opsize &gt;= <a href="ident?i=TCPOLEN_EXP_FASTOPEN_BASE">TCPOLEN_EXP_FASTOPEN_BASE</a> &amp;&amp;
<a name="L3744" href="source/net/ipv4/tcp_input.c#L3744">3744</a>                                     <a href="ident?i=get_unaligned_be16">get_unaligned_be16</a>(<a href="ident?i=ptr">ptr</a>) ==
<a name="L3745" href="source/net/ipv4/tcp_input.c#L3745">3745</a>                                     <a href="ident?i=TCPOPT_FASTOPEN_MAGIC">TCPOPT_FASTOPEN_MAGIC</a>)
<a name="L3746" href="source/net/ipv4/tcp_input.c#L3746">3746</a>                                         <a href="ident?i=tcp_parse_fastopen_option">tcp_parse_fastopen_option</a>(opsize -
<a name="L3747" href="source/net/ipv4/tcp_input.c#L3747">3747</a>                                                 <a href="ident?i=TCPOLEN_EXP_FASTOPEN_BASE">TCPOLEN_EXP_FASTOPEN_BASE</a>,
<a name="L3748" href="source/net/ipv4/tcp_input.c#L3748">3748</a>                                                 <a href="ident?i=ptr">ptr</a> + 2, <a href="ident?i=th">th</a>-&gt;syn, foc, <a href="ident?i=true">true</a>);
<a name="L3749" href="source/net/ipv4/tcp_input.c#L3749">3749</a>                                 break;
<a name="L3750" href="source/net/ipv4/tcp_input.c#L3750">3750</a> 
<a name="L3751" href="source/net/ipv4/tcp_input.c#L3751">3751</a>                         }
<a name="L3752" href="source/net/ipv4/tcp_input.c#L3752">3752</a>                         <a href="ident?i=ptr">ptr</a> += opsize-2;
<a name="L3753" href="source/net/ipv4/tcp_input.c#L3753">3753</a>                         <a href="ident?i=length">length</a> -= opsize;
<a name="L3754" href="source/net/ipv4/tcp_input.c#L3754">3754</a>                 }
<a name="L3755" href="source/net/ipv4/tcp_input.c#L3755">3755</a>         }
<a name="L3756" href="source/net/ipv4/tcp_input.c#L3756">3756</a> }
<a name="L3757" href="source/net/ipv4/tcp_input.c#L3757">3757</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=tcp_parse_options">tcp_parse_options</a>);
<a name="L3758" href="source/net/ipv4/tcp_input.c#L3758">3758</a> 
<a name="L3759" href="source/net/ipv4/tcp_input.c#L3759">3759</a> static <a href="ident?i=bool">bool</a> <a href="ident?i=tcp_parse_aligned_timestamp">tcp_parse_aligned_timestamp</a>(struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a>, const struct <a href="ident?i=tcphdr">tcphdr</a> *<a href="ident?i=th">th</a>)
<a name="L3760" href="source/net/ipv4/tcp_input.c#L3760">3760</a> {
<a name="L3761" href="source/net/ipv4/tcp_input.c#L3761">3761</a>         const <a href="ident?i=__be32">__be32</a> *<a href="ident?i=ptr">ptr</a> = (const <a href="ident?i=__be32">__be32</a> *)(<a href="ident?i=th">th</a> + 1);
<a name="L3762" href="source/net/ipv4/tcp_input.c#L3762">3762</a> 
<a name="L3763" href="source/net/ipv4/tcp_input.c#L3763">3763</a>         if (*<a href="ident?i=ptr">ptr</a> == <a href="ident?i=htonl">htonl</a>((<a href="ident?i=TCPOPT_NOP">TCPOPT_NOP</a> &lt;&lt; 24) | (<a href="ident?i=TCPOPT_NOP">TCPOPT_NOP</a> &lt;&lt; 16)
<a name="L3764" href="source/net/ipv4/tcp_input.c#L3764">3764</a>                           | (<a href="ident?i=TCPOPT_TIMESTAMP">TCPOPT_TIMESTAMP</a> &lt;&lt; 8) | <a href="ident?i=TCPOLEN_TIMESTAMP">TCPOLEN_TIMESTAMP</a>)) {
<a name="L3765" href="source/net/ipv4/tcp_input.c#L3765">3765</a>                 <a href="ident?i=tp">tp</a>-&gt;rx_opt.saw_tstamp = 1;
<a name="L3766" href="source/net/ipv4/tcp_input.c#L3766">3766</a>                 ++<a href="ident?i=ptr">ptr</a>;
<a name="L3767" href="source/net/ipv4/tcp_input.c#L3767">3767</a>                 <a href="ident?i=tp">tp</a>-&gt;rx_opt.rcv_tsval = <a href="ident?i=ntohl">ntohl</a>(*<a href="ident?i=ptr">ptr</a>);
<a name="L3768" href="source/net/ipv4/tcp_input.c#L3768">3768</a>                 ++<a href="ident?i=ptr">ptr</a>;
<a name="L3769" href="source/net/ipv4/tcp_input.c#L3769">3769</a>                 if (*<a href="ident?i=ptr">ptr</a>)
<a name="L3770" href="source/net/ipv4/tcp_input.c#L3770">3770</a>                         <a href="ident?i=tp">tp</a>-&gt;rx_opt.rcv_tsecr = <a href="ident?i=ntohl">ntohl</a>(*<a href="ident?i=ptr">ptr</a>) - <a href="ident?i=tp">tp</a>-&gt;tsoffset;
<a name="L3771" href="source/net/ipv4/tcp_input.c#L3771">3771</a>                 else
<a name="L3772" href="source/net/ipv4/tcp_input.c#L3772">3772</a>                         <a href="ident?i=tp">tp</a>-&gt;rx_opt.rcv_tsecr = 0;
<a name="L3773" href="source/net/ipv4/tcp_input.c#L3773">3773</a>                 return <a href="ident?i=true">true</a>;
<a name="L3774" href="source/net/ipv4/tcp_input.c#L3774">3774</a>         }
<a name="L3775" href="source/net/ipv4/tcp_input.c#L3775">3775</a>         return <a href="ident?i=false">false</a>;
<a name="L3776" href="source/net/ipv4/tcp_input.c#L3776">3776</a> }
<a name="L3777" href="source/net/ipv4/tcp_input.c#L3777">3777</a> 
<a name="L3778" href="source/net/ipv4/tcp_input.c#L3778">3778</a> <b><i>/* Fast parse options. This hopes to only see timestamps.</i></b>
<a name="L3779" href="source/net/ipv4/tcp_input.c#L3779">3779</a> <b><i> * If it is wrong it falls back on tcp_parse_options().</i></b>
<a name="L3780" href="source/net/ipv4/tcp_input.c#L3780">3780</a> <b><i> */</i></b>
<a name="L3781" href="source/net/ipv4/tcp_input.c#L3781">3781</a> static <a href="ident?i=bool">bool</a> <a href="ident?i=tcp_fast_parse_options">tcp_fast_parse_options</a>(const struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
<a name="L3782" href="source/net/ipv4/tcp_input.c#L3782">3782</a>                                    const struct <a href="ident?i=tcphdr">tcphdr</a> *<a href="ident?i=th">th</a>, struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a>)
<a name="L3783" href="source/net/ipv4/tcp_input.c#L3783">3783</a> {
<a name="L3784" href="source/net/ipv4/tcp_input.c#L3784">3784</a>         <b><i>/* In the spirit of fast parsing, compare doff directly to constant</i></b>
<a name="L3785" href="source/net/ipv4/tcp_input.c#L3785">3785</a> <b><i>         * values.  Because equality is used, short doff can be ignored here.</i></b>
<a name="L3786" href="source/net/ipv4/tcp_input.c#L3786">3786</a> <b><i>         */</i></b>
<a name="L3787" href="source/net/ipv4/tcp_input.c#L3787">3787</a>         if (<a href="ident?i=th">th</a>-&gt;doff == (sizeof(*<a href="ident?i=th">th</a>) / 4)) {
<a name="L3788" href="source/net/ipv4/tcp_input.c#L3788">3788</a>                 <a href="ident?i=tp">tp</a>-&gt;rx_opt.saw_tstamp = 0;
<a name="L3789" href="source/net/ipv4/tcp_input.c#L3789">3789</a>                 return <a href="ident?i=false">false</a>;
<a name="L3790" href="source/net/ipv4/tcp_input.c#L3790">3790</a>         } else if (<a href="ident?i=tp">tp</a>-&gt;rx_opt.tstamp_ok &amp;&amp;
<a name="L3791" href="source/net/ipv4/tcp_input.c#L3791">3791</a>                    <a href="ident?i=th">th</a>-&gt;doff == ((sizeof(*<a href="ident?i=th">th</a>) + <a href="ident?i=TCPOLEN_TSTAMP_ALIGNED">TCPOLEN_TSTAMP_ALIGNED</a>) / 4)) {
<a name="L3792" href="source/net/ipv4/tcp_input.c#L3792">3792</a>                 if (<a href="ident?i=tcp_parse_aligned_timestamp">tcp_parse_aligned_timestamp</a>(<a href="ident?i=tp">tp</a>, <a href="ident?i=th">th</a>))
<a name="L3793" href="source/net/ipv4/tcp_input.c#L3793">3793</a>                         return <a href="ident?i=true">true</a>;
<a name="L3794" href="source/net/ipv4/tcp_input.c#L3794">3794</a>         }
<a name="L3795" href="source/net/ipv4/tcp_input.c#L3795">3795</a> 
<a name="L3796" href="source/net/ipv4/tcp_input.c#L3796">3796</a>         <a href="ident?i=tcp_parse_options">tcp_parse_options</a>(<a href="ident?i=skb">skb</a>, &amp;<a href="ident?i=tp">tp</a>-&gt;rx_opt, 1, <a href="ident?i=NULL">NULL</a>);
<a name="L3797" href="source/net/ipv4/tcp_input.c#L3797">3797</a>         if (<a href="ident?i=tp">tp</a>-&gt;rx_opt.saw_tstamp &amp;&amp; <a href="ident?i=tp">tp</a>-&gt;rx_opt.rcv_tsecr)
<a name="L3798" href="source/net/ipv4/tcp_input.c#L3798">3798</a>                 <a href="ident?i=tp">tp</a>-&gt;rx_opt.rcv_tsecr -= <a href="ident?i=tp">tp</a>-&gt;tsoffset;
<a name="L3799" href="source/net/ipv4/tcp_input.c#L3799">3799</a> 
<a name="L3800" href="source/net/ipv4/tcp_input.c#L3800">3800</a>         return <a href="ident?i=true">true</a>;
<a name="L3801" href="source/net/ipv4/tcp_input.c#L3801">3801</a> }
<a name="L3802" href="source/net/ipv4/tcp_input.c#L3802">3802</a> 
<a name="L3803" href="source/net/ipv4/tcp_input.c#L3803">3803</a> #ifdef CONFIG_TCP_MD5SIG
<a name="L3804" href="source/net/ipv4/tcp_input.c#L3804">3804</a> <b><i>/*</i></b>
<a name="L3805" href="source/net/ipv4/tcp_input.c#L3805">3805</a> <b><i> * Parse MD5 Signature option</i></b>
<a name="L3806" href="source/net/ipv4/tcp_input.c#L3806">3806</a> <b><i> */</i></b>
<a name="L3807" href="source/net/ipv4/tcp_input.c#L3807">3807</a> const <a href="ident?i=u8">u8</a> *<a href="ident?i=tcp_parse_md5sig_option">tcp_parse_md5sig_option</a>(const struct <a href="ident?i=tcphdr">tcphdr</a> *<a href="ident?i=th">th</a>)
<a name="L3808" href="source/net/ipv4/tcp_input.c#L3808">3808</a> {
<a name="L3809" href="source/net/ipv4/tcp_input.c#L3809">3809</a>         int <a href="ident?i=length">length</a> = (<a href="ident?i=th">th</a>-&gt;doff &lt;&lt; 2) - sizeof(*<a href="ident?i=th">th</a>);
<a name="L3810" href="source/net/ipv4/tcp_input.c#L3810">3810</a>         const <a href="ident?i=u8">u8</a> *<a href="ident?i=ptr">ptr</a> = (const <a href="ident?i=u8">u8</a> *)(<a href="ident?i=th">th</a> + 1);
<a name="L3811" href="source/net/ipv4/tcp_input.c#L3811">3811</a> 
<a name="L3812" href="source/net/ipv4/tcp_input.c#L3812">3812</a>         <b><i>/* If the TCP option is too short, we can short cut */</i></b>
<a name="L3813" href="source/net/ipv4/tcp_input.c#L3813">3813</a>         if (<a href="ident?i=length">length</a> &lt; <a href="ident?i=TCPOLEN_MD5SIG">TCPOLEN_MD5SIG</a>)
<a name="L3814" href="source/net/ipv4/tcp_input.c#L3814">3814</a>                 return <a href="ident?i=NULL">NULL</a>;
<a name="L3815" href="source/net/ipv4/tcp_input.c#L3815">3815</a> 
<a name="L3816" href="source/net/ipv4/tcp_input.c#L3816">3816</a>         while (<a href="ident?i=length">length</a> &gt; 0) {
<a name="L3817" href="source/net/ipv4/tcp_input.c#L3817">3817</a>                 int <a href="ident?i=opcode">opcode</a> = *<a href="ident?i=ptr">ptr</a>++;
<a name="L3818" href="source/net/ipv4/tcp_input.c#L3818">3818</a>                 int opsize;
<a name="L3819" href="source/net/ipv4/tcp_input.c#L3819">3819</a> 
<a name="L3820" href="source/net/ipv4/tcp_input.c#L3820">3820</a>                 switch (<a href="ident?i=opcode">opcode</a>) {
<a name="L3821" href="source/net/ipv4/tcp_input.c#L3821">3821</a>                 case <a href="ident?i=TCPOPT_EOL">TCPOPT_EOL</a>:
<a name="L3822" href="source/net/ipv4/tcp_input.c#L3822">3822</a>                         return <a href="ident?i=NULL">NULL</a>;
<a name="L3823" href="source/net/ipv4/tcp_input.c#L3823">3823</a>                 case <a href="ident?i=TCPOPT_NOP">TCPOPT_NOP</a>:
<a name="L3824" href="source/net/ipv4/tcp_input.c#L3824">3824</a>                         <a href="ident?i=length">length</a>--;
<a name="L3825" href="source/net/ipv4/tcp_input.c#L3825">3825</a>                         continue;
<a name="L3826" href="source/net/ipv4/tcp_input.c#L3826">3826</a>                 default:
<a name="L3827" href="source/net/ipv4/tcp_input.c#L3827">3827</a>                         opsize = *<a href="ident?i=ptr">ptr</a>++;
<a name="L3828" href="source/net/ipv4/tcp_input.c#L3828">3828</a>                         if (opsize &lt; 2 || opsize &gt; <a href="ident?i=length">length</a>)
<a name="L3829" href="source/net/ipv4/tcp_input.c#L3829">3829</a>                                 return <a href="ident?i=NULL">NULL</a>;
<a name="L3830" href="source/net/ipv4/tcp_input.c#L3830">3830</a>                         if (<a href="ident?i=opcode">opcode</a> == <a href="ident?i=TCPOPT_MD5SIG">TCPOPT_MD5SIG</a>)
<a name="L3831" href="source/net/ipv4/tcp_input.c#L3831">3831</a>                                 return opsize == <a href="ident?i=TCPOLEN_MD5SIG">TCPOLEN_MD5SIG</a> ? <a href="ident?i=ptr">ptr</a> : <a href="ident?i=NULL">NULL</a>;
<a name="L3832" href="source/net/ipv4/tcp_input.c#L3832">3832</a>                 }
<a name="L3833" href="source/net/ipv4/tcp_input.c#L3833">3833</a>                 <a href="ident?i=ptr">ptr</a> += opsize - 2;
<a name="L3834" href="source/net/ipv4/tcp_input.c#L3834">3834</a>                 <a href="ident?i=length">length</a> -= opsize;
<a name="L3835" href="source/net/ipv4/tcp_input.c#L3835">3835</a>         }
<a name="L3836" href="source/net/ipv4/tcp_input.c#L3836">3836</a>         return <a href="ident?i=NULL">NULL</a>;
<a name="L3837" href="source/net/ipv4/tcp_input.c#L3837">3837</a> }
<a name="L3838" href="source/net/ipv4/tcp_input.c#L3838">3838</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=tcp_parse_md5sig_option">tcp_parse_md5sig_option</a>);
<a name="L3839" href="source/net/ipv4/tcp_input.c#L3839">3839</a> #endif
<a name="L3840" href="source/net/ipv4/tcp_input.c#L3840">3840</a> 
<a name="L3841" href="source/net/ipv4/tcp_input.c#L3841">3841</a> <b><i>/* Sorry, PAWS as specified is broken wrt. pure-ACKs -DaveM</i></b>
<a name="L3842" href="source/net/ipv4/tcp_input.c#L3842">3842</a> <b><i> *</i></b>
<a name="L3843" href="source/net/ipv4/tcp_input.c#L3843">3843</a> <b><i> * It is not fatal. If this ACK does _not_ change critical state (seqs, window)</i></b>
<a name="L3844" href="source/net/ipv4/tcp_input.c#L3844">3844</a> <b><i> * it can pass through stack. So, the following predicate verifies that</i></b>
<a name="L3845" href="source/net/ipv4/tcp_input.c#L3845">3845</a> <b><i> * this segment is not used for anything but congestion avoidance or</i></b>
<a name="L3846" href="source/net/ipv4/tcp_input.c#L3846">3846</a> <b><i> * fast retransmit. Moreover, we even are able to eliminate most of such</i></b>
<a name="L3847" href="source/net/ipv4/tcp_input.c#L3847">3847</a> <b><i> * second order effects, if we apply some small "replay" window (~RTO)</i></b>
<a name="L3848" href="source/net/ipv4/tcp_input.c#L3848">3848</a> <b><i> * to timestamp space.</i></b>
<a name="L3849" href="source/net/ipv4/tcp_input.c#L3849">3849</a> <b><i> *</i></b>
<a name="L3850" href="source/net/ipv4/tcp_input.c#L3850">3850</a> <b><i> * All these measures still do not guarantee that we reject wrapped ACKs</i></b>
<a name="L3851" href="source/net/ipv4/tcp_input.c#L3851">3851</a> <b><i> * on networks with high bandwidth, when sequence space is recycled fastly,</i></b>
<a name="L3852" href="source/net/ipv4/tcp_input.c#L3852">3852</a> <b><i> * but it guarantees that such events will be very rare and do not affect</i></b>
<a name="L3853" href="source/net/ipv4/tcp_input.c#L3853">3853</a> <b><i> * connection seriously. This doesn't look nice, but alas, PAWS is really</i></b>
<a name="L3854" href="source/net/ipv4/tcp_input.c#L3854">3854</a> <b><i> * buggy extension.</i></b>
<a name="L3855" href="source/net/ipv4/tcp_input.c#L3855">3855</a> <b><i> *</i></b>
<a name="L3856" href="source/net/ipv4/tcp_input.c#L3856">3856</a> <b><i> * [ Later note. Even worse! It is buggy for segments _with_ data. RFC</i></b>
<a name="L3857" href="source/net/ipv4/tcp_input.c#L3857">3857</a> <b><i> * states that events when retransmit arrives after original data are rare.</i></b>
<a name="L3858" href="source/net/ipv4/tcp_input.c#L3858">3858</a> <b><i> * It is a blatant lie. VJ forgot about fast retransmit! 8)8) It is</i></b>
<a name="L3859" href="source/net/ipv4/tcp_input.c#L3859">3859</a> <b><i> * the biggest problem on large power networks even with minor reordering.</i></b>
<a name="L3860" href="source/net/ipv4/tcp_input.c#L3860">3860</a> <b><i> * OK, let's give it small replay window. If peer clock is even 1hz, it is safe</i></b>
<a name="L3861" href="source/net/ipv4/tcp_input.c#L3861">3861</a> <b><i> * up to bandwidth of 18Gigabit/sec. 8) ]</i></b>
<a name="L3862" href="source/net/ipv4/tcp_input.c#L3862">3862</a> <b><i> */</i></b>
<a name="L3863" href="source/net/ipv4/tcp_input.c#L3863">3863</a> 
<a name="L3864" href="source/net/ipv4/tcp_input.c#L3864">3864</a> static int <a href="ident?i=tcp_disordered_ack">tcp_disordered_ack</a>(const struct <a href="ident?i=sock">sock</a> *sk, const struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L3865" href="source/net/ipv4/tcp_input.c#L3865">3865</a> {
<a name="L3866" href="source/net/ipv4/tcp_input.c#L3866">3866</a>         const struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L3867" href="source/net/ipv4/tcp_input.c#L3867">3867</a>         const struct <a href="ident?i=tcphdr">tcphdr</a> *<a href="ident?i=th">th</a> = <a href="ident?i=tcp_hdr">tcp_hdr</a>(<a href="ident?i=skb">skb</a>);
<a name="L3868" href="source/net/ipv4/tcp_input.c#L3868">3868</a>         <a href="ident?i=u32">u32</a> <a href="ident?i=seq">seq</a> = <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=seq">seq</a>;
<a name="L3869" href="source/net/ipv4/tcp_input.c#L3869">3869</a>         <a href="ident?i=u32">u32</a> ack = <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;ack_seq;
<a name="L3870" href="source/net/ipv4/tcp_input.c#L3870">3870</a> 
<a name="L3871" href="source/net/ipv4/tcp_input.c#L3871">3871</a>         return (<b><i>/* 1. Pure ACK with correct sequence number. */</i></b>
<a name="L3872" href="source/net/ipv4/tcp_input.c#L3872">3872</a>                 (<a href="ident?i=th">th</a>-&gt;ack &amp;&amp; <a href="ident?i=seq">seq</a> == <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;end_seq &amp;&amp; <a href="ident?i=seq">seq</a> == <a href="ident?i=tp">tp</a>-&gt;rcv_nxt) &amp;&amp;
<a name="L3873" href="source/net/ipv4/tcp_input.c#L3873">3873</a> 
<a name="L3874" href="source/net/ipv4/tcp_input.c#L3874">3874</a>                 <b><i>/* 2. ... and duplicate ACK. */</i></b>
<a name="L3875" href="source/net/ipv4/tcp_input.c#L3875">3875</a>                 ack == <a href="ident?i=tp">tp</a>-&gt;snd_una &amp;&amp;
<a name="L3876" href="source/net/ipv4/tcp_input.c#L3876">3876</a> 
<a name="L3877" href="source/net/ipv4/tcp_input.c#L3877">3877</a>                 <b><i>/* 3. ... and does not update window. */</i></b>
<a name="L3878" href="source/net/ipv4/tcp_input.c#L3878">3878</a>                 !<a href="ident?i=tcp_may_update_window">tcp_may_update_window</a>(<a href="ident?i=tp">tp</a>, ack, <a href="ident?i=seq">seq</a>, <a href="ident?i=ntohs">ntohs</a>(<a href="ident?i=th">th</a>-&gt;<a href="ident?i=window">window</a>) &lt;&lt; <a href="ident?i=tp">tp</a>-&gt;rx_opt.snd_wscale) &amp;&amp;
<a name="L3879" href="source/net/ipv4/tcp_input.c#L3879">3879</a> 
<a name="L3880" href="source/net/ipv4/tcp_input.c#L3880">3880</a>                 <b><i>/* 4. ... and sits in replay window. */</i></b>
<a name="L3881" href="source/net/ipv4/tcp_input.c#L3881">3881</a>                 (<a href="ident?i=s32">s32</a>)(<a href="ident?i=tp">tp</a>-&gt;rx_opt.ts_recent - <a href="ident?i=tp">tp</a>-&gt;rx_opt.rcv_tsval) &lt;= (<a href="ident?i=inet_csk">inet_csk</a>(sk)-&gt;icsk_rto * 1024) / <a href="ident?i=HZ">HZ</a>);
<a name="L3882" href="source/net/ipv4/tcp_input.c#L3882">3882</a> }
<a name="L3883" href="source/net/ipv4/tcp_input.c#L3883">3883</a> 
<a name="L3884" href="source/net/ipv4/tcp_input.c#L3884">3884</a> static inline <a href="ident?i=bool">bool</a> <a href="ident?i=tcp_paws_discard">tcp_paws_discard</a>(const struct <a href="ident?i=sock">sock</a> *sk,
<a name="L3885" href="source/net/ipv4/tcp_input.c#L3885">3885</a>                                    const struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L3886" href="source/net/ipv4/tcp_input.c#L3886">3886</a> {
<a name="L3887" href="source/net/ipv4/tcp_input.c#L3887">3887</a>         const struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L3888" href="source/net/ipv4/tcp_input.c#L3888">3888</a> 
<a name="L3889" href="source/net/ipv4/tcp_input.c#L3889">3889</a>         return !<a href="ident?i=tcp_paws_check">tcp_paws_check</a>(&amp;<a href="ident?i=tp">tp</a>-&gt;rx_opt, <a href="ident?i=TCP_PAWS_WINDOW">TCP_PAWS_WINDOW</a>) &amp;&amp;
<a name="L3890" href="source/net/ipv4/tcp_input.c#L3890">3890</a>                !<a href="ident?i=tcp_disordered_ack">tcp_disordered_ack</a>(sk, <a href="ident?i=skb">skb</a>);
<a name="L3891" href="source/net/ipv4/tcp_input.c#L3891">3891</a> }
<a name="L3892" href="source/net/ipv4/tcp_input.c#L3892">3892</a> 
<a name="L3893" href="source/net/ipv4/tcp_input.c#L3893">3893</a> <b><i>/* Check segment sequence number for validity.</i></b>
<a name="L3894" href="source/net/ipv4/tcp_input.c#L3894">3894</a> <b><i> *</i></b>
<a name="L3895" href="source/net/ipv4/tcp_input.c#L3895">3895</a> <b><i> * Segment controls are considered valid, if the segment</i></b>
<a name="L3896" href="source/net/ipv4/tcp_input.c#L3896">3896</a> <b><i> * fits to the window after truncation to the window. Acceptability</i></b>
<a name="L3897" href="source/net/ipv4/tcp_input.c#L3897">3897</a> <b><i> * of data (and SYN, FIN, of course) is checked separately.</i></b>
<a name="L3898" href="source/net/ipv4/tcp_input.c#L3898">3898</a> <b><i> * See tcp_data_queue(), for example.</i></b>
<a name="L3899" href="source/net/ipv4/tcp_input.c#L3899">3899</a> <b><i> *</i></b>
<a name="L3900" href="source/net/ipv4/tcp_input.c#L3900">3900</a> <b><i> * Also, controls (RST is main one) are accepted using RCV.WUP instead</i></b>
<a name="L3901" href="source/net/ipv4/tcp_input.c#L3901">3901</a> <b><i> * of RCV.NXT. Peer still did not advance his SND.UNA when we</i></b>
<a name="L3902" href="source/net/ipv4/tcp_input.c#L3902">3902</a> <b><i> * delayed ACK, so that hisSND.UNA&lt;=ourRCV.WUP.</i></b>
<a name="L3903" href="source/net/ipv4/tcp_input.c#L3903">3903</a> <b><i> * (borrowed from freebsd)</i></b>
<a name="L3904" href="source/net/ipv4/tcp_input.c#L3904">3904</a> <b><i> */</i></b>
<a name="L3905" href="source/net/ipv4/tcp_input.c#L3905">3905</a> 
<a name="L3906" href="source/net/ipv4/tcp_input.c#L3906">3906</a> static inline <a href="ident?i=bool">bool</a> <a href="ident?i=tcp_sequence">tcp_sequence</a>(const struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a>, <a href="ident?i=u32">u32</a> <a href="ident?i=seq">seq</a>, <a href="ident?i=u32">u32</a> end_seq)
<a name="L3907" href="source/net/ipv4/tcp_input.c#L3907">3907</a> {
<a name="L3908" href="source/net/ipv4/tcp_input.c#L3908">3908</a>         return  !<a href="ident?i=before">before</a>(end_seq, <a href="ident?i=tp">tp</a>-&gt;rcv_wup) &amp;&amp;
<a name="L3909" href="source/net/ipv4/tcp_input.c#L3909">3909</a>                 !<a href="ident?i=after">after</a>(<a href="ident?i=seq">seq</a>, <a href="ident?i=tp">tp</a>-&gt;rcv_nxt + <a href="ident?i=tcp_receive_window">tcp_receive_window</a>(<a href="ident?i=tp">tp</a>));
<a name="L3910" href="source/net/ipv4/tcp_input.c#L3910">3910</a> }
<a name="L3911" href="source/net/ipv4/tcp_input.c#L3911">3911</a> 
<a name="L3912" href="source/net/ipv4/tcp_input.c#L3912">3912</a> <b><i>/* When we get a reset we do this. */</i></b>
<a name="L3913" href="source/net/ipv4/tcp_input.c#L3913">3913</a> void <a href="ident?i=tcp_reset">tcp_reset</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L3914" href="source/net/ipv4/tcp_input.c#L3914">3914</a> {
<a name="L3915" href="source/net/ipv4/tcp_input.c#L3915">3915</a>         <b><i>/* We want the right error as BSD sees it (and indeed as we do). */</i></b>
<a name="L3916" href="source/net/ipv4/tcp_input.c#L3916">3916</a>         switch (sk-&gt;<a href="ident?i=sk_state">sk_state</a>) {
<a name="L3917" href="source/net/ipv4/tcp_input.c#L3917">3917</a>         case TCP_SYN_SENT:
<a name="L3918" href="source/net/ipv4/tcp_input.c#L3918">3918</a>                 sk-&gt;sk_err = <a href="ident?i=ECONNREFUSED">ECONNREFUSED</a>;
<a name="L3919" href="source/net/ipv4/tcp_input.c#L3919">3919</a>                 break;
<a name="L3920" href="source/net/ipv4/tcp_input.c#L3920">3920</a>         case TCP_CLOSE_WAIT:
<a name="L3921" href="source/net/ipv4/tcp_input.c#L3921">3921</a>                 sk-&gt;sk_err = <a href="ident?i=EPIPE">EPIPE</a>;
<a name="L3922" href="source/net/ipv4/tcp_input.c#L3922">3922</a>                 break;
<a name="L3923" href="source/net/ipv4/tcp_input.c#L3923">3923</a>         case TCP_CLOSE:
<a name="L3924" href="source/net/ipv4/tcp_input.c#L3924">3924</a>                 return;
<a name="L3925" href="source/net/ipv4/tcp_input.c#L3925">3925</a>         default:
<a name="L3926" href="source/net/ipv4/tcp_input.c#L3926">3926</a>                 sk-&gt;sk_err = <a href="ident?i=ECONNRESET">ECONNRESET</a>;
<a name="L3927" href="source/net/ipv4/tcp_input.c#L3927">3927</a>         }
<a name="L3928" href="source/net/ipv4/tcp_input.c#L3928">3928</a>         <b><i>/* This barrier is coupled with smp_rmb() in tcp_poll() */</i></b>
<a name="L3929" href="source/net/ipv4/tcp_input.c#L3929">3929</a>         <a href="ident?i=smp_wmb">smp_wmb</a>();
<a name="L3930" href="source/net/ipv4/tcp_input.c#L3930">3930</a> 
<a name="L3931" href="source/net/ipv4/tcp_input.c#L3931">3931</a>         if (!<a href="ident?i=sock_flag">sock_flag</a>(sk, SOCK_DEAD))
<a name="L3932" href="source/net/ipv4/tcp_input.c#L3932">3932</a>                 sk-&gt;sk_error_report(sk);
<a name="L3933" href="source/net/ipv4/tcp_input.c#L3933">3933</a> 
<a name="L3934" href="source/net/ipv4/tcp_input.c#L3934">3934</a>         <a href="ident?i=tcp_done">tcp_done</a>(sk);
<a name="L3935" href="source/net/ipv4/tcp_input.c#L3935">3935</a> }
<a name="L3936" href="source/net/ipv4/tcp_input.c#L3936">3936</a> 
<a name="L3937" href="source/net/ipv4/tcp_input.c#L3937">3937</a> <b><i>/*</i></b>
<a name="L3938" href="source/net/ipv4/tcp_input.c#L3938">3938</a> <b><i> *      Process the FIN bit. This now behaves as it is supposed to work</i></b>
<a name="L3939" href="source/net/ipv4/tcp_input.c#L3939">3939</a> <b><i> *      and the FIN takes effect when it is validly part of sequence</i></b>
<a name="L3940" href="source/net/ipv4/tcp_input.c#L3940">3940</a> <b><i> *      space. Not before when we get holes.</i></b>
<a name="L3941" href="source/net/ipv4/tcp_input.c#L3941">3941</a> <b><i> *</i></b>
<a name="L3942" href="source/net/ipv4/tcp_input.c#L3942">3942</a> <b><i> *      If we are ESTABLISHED, a received fin moves us to CLOSE-WAIT</i></b>
<a name="L3943" href="source/net/ipv4/tcp_input.c#L3943">3943</a> <b><i> *      (and thence onto LAST-ACK and finally, CLOSE, we never enter</i></b>
<a name="L3944" href="source/net/ipv4/tcp_input.c#L3944">3944</a> <b><i> *      TIME-WAIT)</i></b>
<a name="L3945" href="source/net/ipv4/tcp_input.c#L3945">3945</a> <b><i> *</i></b>
<a name="L3946" href="source/net/ipv4/tcp_input.c#L3946">3946</a> <b><i> *      If we are in FINWAIT-1, a received FIN indicates simultaneous</i></b>
<a name="L3947" href="source/net/ipv4/tcp_input.c#L3947">3947</a> <b><i> *      close and we go into CLOSING (and later onto TIME-WAIT)</i></b>
<a name="L3948" href="source/net/ipv4/tcp_input.c#L3948">3948</a> <b><i> *</i></b>
<a name="L3949" href="source/net/ipv4/tcp_input.c#L3949">3949</a> <b><i> *      If we are in FINWAIT-2, a received FIN moves us to TIME-WAIT.</i></b>
<a name="L3950" href="source/net/ipv4/tcp_input.c#L3950">3950</a> <b><i> */</i></b>
<a name="L3951" href="source/net/ipv4/tcp_input.c#L3951">3951</a> static void <a href="ident?i=tcp_fin">tcp_fin</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L3952" href="source/net/ipv4/tcp_input.c#L3952">3952</a> {
<a name="L3953" href="source/net/ipv4/tcp_input.c#L3953">3953</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L3954" href="source/net/ipv4/tcp_input.c#L3954">3954</a>         const struct <a href="ident?i=dst_entry">dst_entry</a> *<a href="ident?i=dst">dst</a>;
<a name="L3955" href="source/net/ipv4/tcp_input.c#L3955">3955</a> 
<a name="L3956" href="source/net/ipv4/tcp_input.c#L3956">3956</a>         <a href="ident?i=inet_csk_schedule_ack">inet_csk_schedule_ack</a>(sk);
<a name="L3957" href="source/net/ipv4/tcp_input.c#L3957">3957</a> 
<a name="L3958" href="source/net/ipv4/tcp_input.c#L3958">3958</a>         sk-&gt;sk_shutdown |= <a href="ident?i=RCV_SHUTDOWN">RCV_SHUTDOWN</a>;
<a name="L3959" href="source/net/ipv4/tcp_input.c#L3959">3959</a>         <a href="ident?i=sock_set_flag">sock_set_flag</a>(sk, SOCK_DONE);
<a name="L3960" href="source/net/ipv4/tcp_input.c#L3960">3960</a> 
<a name="L3961" href="source/net/ipv4/tcp_input.c#L3961">3961</a>         switch (sk-&gt;<a href="ident?i=sk_state">sk_state</a>) {
<a name="L3962" href="source/net/ipv4/tcp_input.c#L3962">3962</a>         case TCP_SYN_RECV:
<a name="L3963" href="source/net/ipv4/tcp_input.c#L3963">3963</a>         case TCP_ESTABLISHED:
<a name="L3964" href="source/net/ipv4/tcp_input.c#L3964">3964</a>                 <b><i>/* Move to CLOSE_WAIT */</i></b>
<a name="L3965" href="source/net/ipv4/tcp_input.c#L3965">3965</a>                 <a href="ident?i=tcp_set_state">tcp_set_state</a>(sk, TCP_CLOSE_WAIT);
<a name="L3966" href="source/net/ipv4/tcp_input.c#L3966">3966</a>                 <a href="ident?i=dst">dst</a> = <a href="ident?i=__sk_dst_get">__sk_dst_get</a>(sk);
<a name="L3967" href="source/net/ipv4/tcp_input.c#L3967">3967</a>                 if (!<a href="ident?i=dst">dst</a> || !<a href="ident?i=dst_metric">dst_metric</a>(<a href="ident?i=dst">dst</a>, <a href="ident?i=RTAX_QUICKACK">RTAX_QUICKACK</a>))
<a name="L3968" href="source/net/ipv4/tcp_input.c#L3968">3968</a>                         <a href="ident?i=inet_csk">inet_csk</a>(sk)-&gt;icsk_ack.pingpong = 1;
<a name="L3969" href="source/net/ipv4/tcp_input.c#L3969">3969</a>                 break;
<a name="L3970" href="source/net/ipv4/tcp_input.c#L3970">3970</a> 
<a name="L3971" href="source/net/ipv4/tcp_input.c#L3971">3971</a>         case TCP_CLOSE_WAIT:
<a name="L3972" href="source/net/ipv4/tcp_input.c#L3972">3972</a>         case TCP_CLOSING:
<a name="L3973" href="source/net/ipv4/tcp_input.c#L3973">3973</a>                 <b><i>/* Received a retransmission of the FIN, do</i></b>
<a name="L3974" href="source/net/ipv4/tcp_input.c#L3974">3974</a> <b><i>                 * nothing.</i></b>
<a name="L3975" href="source/net/ipv4/tcp_input.c#L3975">3975</a> <b><i>                 */</i></b>
<a name="L3976" href="source/net/ipv4/tcp_input.c#L3976">3976</a>                 break;
<a name="L3977" href="source/net/ipv4/tcp_input.c#L3977">3977</a>         case TCP_LAST_ACK:
<a name="L3978" href="source/net/ipv4/tcp_input.c#L3978">3978</a>                 <b><i>/* RFC793: Remain in the LAST-ACK state. */</i></b>
<a name="L3979" href="source/net/ipv4/tcp_input.c#L3979">3979</a>                 break;
<a name="L3980" href="source/net/ipv4/tcp_input.c#L3980">3980</a> 
<a name="L3981" href="source/net/ipv4/tcp_input.c#L3981">3981</a>         case TCP_FIN_WAIT1:
<a name="L3982" href="source/net/ipv4/tcp_input.c#L3982">3982</a>                 <b><i>/* This case occurs when a simultaneous close</i></b>
<a name="L3983" href="source/net/ipv4/tcp_input.c#L3983">3983</a> <b><i>                 * happens, we must ack the received FIN and</i></b>
<a name="L3984" href="source/net/ipv4/tcp_input.c#L3984">3984</a> <b><i>                 * enter the CLOSING state.</i></b>
<a name="L3985" href="source/net/ipv4/tcp_input.c#L3985">3985</a> <b><i>                 */</i></b>
<a name="L3986" href="source/net/ipv4/tcp_input.c#L3986">3986</a>                 <a href="ident?i=tcp_send_ack">tcp_send_ack</a>(sk);
<a name="L3987" href="source/net/ipv4/tcp_input.c#L3987">3987</a>                 <a href="ident?i=tcp_set_state">tcp_set_state</a>(sk, TCP_CLOSING);
<a name="L3988" href="source/net/ipv4/tcp_input.c#L3988">3988</a>                 break;
<a name="L3989" href="source/net/ipv4/tcp_input.c#L3989">3989</a>         case TCP_FIN_WAIT2:
<a name="L3990" href="source/net/ipv4/tcp_input.c#L3990">3990</a>                 <b><i>/* Received a FIN -- send ACK and enter TIME_WAIT. */</i></b>
<a name="L3991" href="source/net/ipv4/tcp_input.c#L3991">3991</a>                 <a href="ident?i=tcp_send_ack">tcp_send_ack</a>(sk);
<a name="L3992" href="source/net/ipv4/tcp_input.c#L3992">3992</a>                 <a href="ident?i=tcp_time_wait">tcp_time_wait</a>(sk, TCP_TIME_WAIT, 0);
<a name="L3993" href="source/net/ipv4/tcp_input.c#L3993">3993</a>                 break;
<a name="L3994" href="source/net/ipv4/tcp_input.c#L3994">3994</a>         default:
<a name="L3995" href="source/net/ipv4/tcp_input.c#L3995">3995</a>                 <b><i>/* Only TCP_LISTEN and TCP_CLOSE are left, in these</i></b>
<a name="L3996" href="source/net/ipv4/tcp_input.c#L3996">3996</a> <b><i>                 * cases we should never reach this piece of code.</i></b>
<a name="L3997" href="source/net/ipv4/tcp_input.c#L3997">3997</a> <b><i>                 */</i></b>
<a name="L3998" href="source/net/ipv4/tcp_input.c#L3998">3998</a>                 <a href="ident?i=pr_err">pr_err</a>(<i>"%s: Impossible, sk-&gt;sk_state=%d\n"</i>,
<a name="L3999" href="source/net/ipv4/tcp_input.c#L3999">3999</a>                        <a href="ident?i=__func__">__func__</a>, sk-&gt;<a href="ident?i=sk_state">sk_state</a>);
<a name="L4000" href="source/net/ipv4/tcp_input.c#L4000">4000</a>                 break;
<a name="L4001" href="source/net/ipv4/tcp_input.c#L4001">4001</a>         }
<a name="L4002" href="source/net/ipv4/tcp_input.c#L4002">4002</a> 
<a name="L4003" href="source/net/ipv4/tcp_input.c#L4003">4003</a>         <b><i>/* It _is_ possible, that we have something out-of-order _after_ FIN.</i></b>
<a name="L4004" href="source/net/ipv4/tcp_input.c#L4004">4004</a> <b><i>         * Probably, we should reset in this case. For now drop them.</i></b>
<a name="L4005" href="source/net/ipv4/tcp_input.c#L4005">4005</a> <b><i>         */</i></b>
<a name="L4006" href="source/net/ipv4/tcp_input.c#L4006">4006</a>         <a href="ident?i=__skb_queue_purge">__skb_queue_purge</a>(&amp;<a href="ident?i=tp">tp</a>-&gt;out_of_order_queue);
<a name="L4007" href="source/net/ipv4/tcp_input.c#L4007">4007</a>         if (<a href="ident?i=tcp_is_sack">tcp_is_sack</a>(<a href="ident?i=tp">tp</a>))
<a name="L4008" href="source/net/ipv4/tcp_input.c#L4008">4008</a>                 <a href="ident?i=tcp_sack_reset">tcp_sack_reset</a>(&amp;<a href="ident?i=tp">tp</a>-&gt;rx_opt);
<a name="L4009" href="source/net/ipv4/tcp_input.c#L4009">4009</a>         <a href="ident?i=sk_mem_reclaim">sk_mem_reclaim</a>(sk);
<a name="L4010" href="source/net/ipv4/tcp_input.c#L4010">4010</a> 
<a name="L4011" href="source/net/ipv4/tcp_input.c#L4011">4011</a>         if (!<a href="ident?i=sock_flag">sock_flag</a>(sk, SOCK_DEAD)) {
<a name="L4012" href="source/net/ipv4/tcp_input.c#L4012">4012</a>                 sk-&gt;sk_state_change(sk);
<a name="L4013" href="source/net/ipv4/tcp_input.c#L4013">4013</a> 
<a name="L4014" href="source/net/ipv4/tcp_input.c#L4014">4014</a>                 <b><i>/* Do not send POLL_HUP for half duplex close. */</i></b>
<a name="L4015" href="source/net/ipv4/tcp_input.c#L4015">4015</a>                 if (sk-&gt;sk_shutdown == <a href="ident?i=SHUTDOWN_MASK">SHUTDOWN_MASK</a> ||
<a name="L4016" href="source/net/ipv4/tcp_input.c#L4016">4016</a>                     sk-&gt;<a href="ident?i=sk_state">sk_state</a> == TCP_CLOSE)
<a name="L4017" href="source/net/ipv4/tcp_input.c#L4017">4017</a>                         <a href="ident?i=sk_wake_async">sk_wake_async</a>(sk, SOCK_WAKE_WAITD, <a href="ident?i=POLL_HUP">POLL_HUP</a>);
<a name="L4018" href="source/net/ipv4/tcp_input.c#L4018">4018</a>                 else
<a name="L4019" href="source/net/ipv4/tcp_input.c#L4019">4019</a>                         <a href="ident?i=sk_wake_async">sk_wake_async</a>(sk, SOCK_WAKE_WAITD, <a href="ident?i=POLL_IN">POLL_IN</a>);
<a name="L4020" href="source/net/ipv4/tcp_input.c#L4020">4020</a>         }
<a name="L4021" href="source/net/ipv4/tcp_input.c#L4021">4021</a> }
<a name="L4022" href="source/net/ipv4/tcp_input.c#L4022">4022</a> 
<a name="L4023" href="source/net/ipv4/tcp_input.c#L4023">4023</a> static inline <a href="ident?i=bool">bool</a> <a href="ident?i=tcp_sack_extend">tcp_sack_extend</a>(struct <a href="ident?i=tcp_sack_block">tcp_sack_block</a> *<a href="ident?i=sp">sp</a>, <a href="ident?i=u32">u32</a> <a href="ident?i=seq">seq</a>,
<a name="L4024" href="source/net/ipv4/tcp_input.c#L4024">4024</a>                                   <a href="ident?i=u32">u32</a> end_seq)
<a name="L4025" href="source/net/ipv4/tcp_input.c#L4025">4025</a> {
<a name="L4026" href="source/net/ipv4/tcp_input.c#L4026">4026</a>         if (!<a href="ident?i=after">after</a>(<a href="ident?i=seq">seq</a>, <a href="ident?i=sp">sp</a>-&gt;end_seq) &amp;&amp; !<a href="ident?i=after">after</a>(<a href="ident?i=sp">sp</a>-&gt;<a href="ident?i=start_seq">start_seq</a>, end_seq)) {
<a name="L4027" href="source/net/ipv4/tcp_input.c#L4027">4027</a>                 if (<a href="ident?i=before">before</a>(<a href="ident?i=seq">seq</a>, <a href="ident?i=sp">sp</a>-&gt;<a href="ident?i=start_seq">start_seq</a>))
<a name="L4028" href="source/net/ipv4/tcp_input.c#L4028">4028</a>                         <a href="ident?i=sp">sp</a>-&gt;<a href="ident?i=start_seq">start_seq</a> = <a href="ident?i=seq">seq</a>;
<a name="L4029" href="source/net/ipv4/tcp_input.c#L4029">4029</a>                 if (<a href="ident?i=after">after</a>(end_seq, <a href="ident?i=sp">sp</a>-&gt;end_seq))
<a name="L4030" href="source/net/ipv4/tcp_input.c#L4030">4030</a>                         <a href="ident?i=sp">sp</a>-&gt;end_seq = end_seq;
<a name="L4031" href="source/net/ipv4/tcp_input.c#L4031">4031</a>                 return <a href="ident?i=true">true</a>;
<a name="L4032" href="source/net/ipv4/tcp_input.c#L4032">4032</a>         }
<a name="L4033" href="source/net/ipv4/tcp_input.c#L4033">4033</a>         return <a href="ident?i=false">false</a>;
<a name="L4034" href="source/net/ipv4/tcp_input.c#L4034">4034</a> }
<a name="L4035" href="source/net/ipv4/tcp_input.c#L4035">4035</a> 
<a name="L4036" href="source/net/ipv4/tcp_input.c#L4036">4036</a> static void <a href="ident?i=tcp_dsack_set">tcp_dsack_set</a>(struct <a href="ident?i=sock">sock</a> *sk, <a href="ident?i=u32">u32</a> <a href="ident?i=seq">seq</a>, <a href="ident?i=u32">u32</a> end_seq)
<a name="L4037" href="source/net/ipv4/tcp_input.c#L4037">4037</a> {
<a name="L4038" href="source/net/ipv4/tcp_input.c#L4038">4038</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L4039" href="source/net/ipv4/tcp_input.c#L4039">4039</a> 
<a name="L4040" href="source/net/ipv4/tcp_input.c#L4040">4040</a>         if (<a href="ident?i=tcp_is_sack">tcp_is_sack</a>(<a href="ident?i=tp">tp</a>) &amp;&amp; <a href="ident?i=sysctl_tcp_dsack">sysctl_tcp_dsack</a>) {
<a name="L4041" href="source/net/ipv4/tcp_input.c#L4041">4041</a>                 int mib_idx;
<a name="L4042" href="source/net/ipv4/tcp_input.c#L4042">4042</a> 
<a name="L4043" href="source/net/ipv4/tcp_input.c#L4043">4043</a>                 if (<a href="ident?i=before">before</a>(<a href="ident?i=seq">seq</a>, <a href="ident?i=tp">tp</a>-&gt;rcv_nxt))
<a name="L4044" href="source/net/ipv4/tcp_input.c#L4044">4044</a>                         mib_idx = LINUX_MIB_TCPDSACKOLDSENT;
<a name="L4045" href="source/net/ipv4/tcp_input.c#L4045">4045</a>                 else
<a name="L4046" href="source/net/ipv4/tcp_input.c#L4046">4046</a>                         mib_idx = LINUX_MIB_TCPDSACKOFOSENT;
<a name="L4047" href="source/net/ipv4/tcp_input.c#L4047">4047</a> 
<a name="L4048" href="source/net/ipv4/tcp_input.c#L4048">4048</a>                 <a href="ident?i=NET_INC_STATS_BH">NET_INC_STATS_BH</a>(<a href="ident?i=sock_net">sock_net</a>(sk), mib_idx);
<a name="L4049" href="source/net/ipv4/tcp_input.c#L4049">4049</a> 
<a name="L4050" href="source/net/ipv4/tcp_input.c#L4050">4050</a>                 <a href="ident?i=tp">tp</a>-&gt;rx_opt.dsack = 1;
<a name="L4051" href="source/net/ipv4/tcp_input.c#L4051">4051</a>                 <a href="ident?i=tp">tp</a>-&gt;duplicate_sack[0].<a href="ident?i=start_seq">start_seq</a> = <a href="ident?i=seq">seq</a>;
<a name="L4052" href="source/net/ipv4/tcp_input.c#L4052">4052</a>                 <a href="ident?i=tp">tp</a>-&gt;duplicate_sack[0].end_seq = end_seq;
<a name="L4053" href="source/net/ipv4/tcp_input.c#L4053">4053</a>         }
<a name="L4054" href="source/net/ipv4/tcp_input.c#L4054">4054</a> }
<a name="L4055" href="source/net/ipv4/tcp_input.c#L4055">4055</a> 
<a name="L4056" href="source/net/ipv4/tcp_input.c#L4056">4056</a> static void <a href="ident?i=tcp_dsack_extend">tcp_dsack_extend</a>(struct <a href="ident?i=sock">sock</a> *sk, <a href="ident?i=u32">u32</a> <a href="ident?i=seq">seq</a>, <a href="ident?i=u32">u32</a> end_seq)
<a name="L4057" href="source/net/ipv4/tcp_input.c#L4057">4057</a> {
<a name="L4058" href="source/net/ipv4/tcp_input.c#L4058">4058</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L4059" href="source/net/ipv4/tcp_input.c#L4059">4059</a> 
<a name="L4060" href="source/net/ipv4/tcp_input.c#L4060">4060</a>         if (!<a href="ident?i=tp">tp</a>-&gt;rx_opt.dsack)
<a name="L4061" href="source/net/ipv4/tcp_input.c#L4061">4061</a>                 <a href="ident?i=tcp_dsack_set">tcp_dsack_set</a>(sk, <a href="ident?i=seq">seq</a>, end_seq);
<a name="L4062" href="source/net/ipv4/tcp_input.c#L4062">4062</a>         else
<a name="L4063" href="source/net/ipv4/tcp_input.c#L4063">4063</a>                 <a href="ident?i=tcp_sack_extend">tcp_sack_extend</a>(<a href="ident?i=tp">tp</a>-&gt;duplicate_sack, <a href="ident?i=seq">seq</a>, end_seq);
<a name="L4064" href="source/net/ipv4/tcp_input.c#L4064">4064</a> }
<a name="L4065" href="source/net/ipv4/tcp_input.c#L4065">4065</a> 
<a name="L4066" href="source/net/ipv4/tcp_input.c#L4066">4066</a> static void <a href="ident?i=tcp_send_dupack">tcp_send_dupack</a>(struct <a href="ident?i=sock">sock</a> *sk, const struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L4067" href="source/net/ipv4/tcp_input.c#L4067">4067</a> {
<a name="L4068" href="source/net/ipv4/tcp_input.c#L4068">4068</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L4069" href="source/net/ipv4/tcp_input.c#L4069">4069</a> 
<a name="L4070" href="source/net/ipv4/tcp_input.c#L4070">4070</a>         if (<a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;end_seq != <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=seq">seq</a> &amp;&amp;
<a name="L4071" href="source/net/ipv4/tcp_input.c#L4071">4071</a>             <a href="ident?i=before">before</a>(<a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=seq">seq</a>, <a href="ident?i=tp">tp</a>-&gt;rcv_nxt)) {
<a name="L4072" href="source/net/ipv4/tcp_input.c#L4072">4072</a>                 <a href="ident?i=NET_INC_STATS_BH">NET_INC_STATS_BH</a>(<a href="ident?i=sock_net">sock_net</a>(sk), LINUX_MIB_DELAYEDACKLOST);
<a name="L4073" href="source/net/ipv4/tcp_input.c#L4073">4073</a>                 <a href="ident?i=tcp_enter_quickack_mode">tcp_enter_quickack_mode</a>(sk);
<a name="L4074" href="source/net/ipv4/tcp_input.c#L4074">4074</a> 
<a name="L4075" href="source/net/ipv4/tcp_input.c#L4075">4075</a>                 if (<a href="ident?i=tcp_is_sack">tcp_is_sack</a>(<a href="ident?i=tp">tp</a>) &amp;&amp; <a href="ident?i=sysctl_tcp_dsack">sysctl_tcp_dsack</a>) {
<a name="L4076" href="source/net/ipv4/tcp_input.c#L4076">4076</a>                         <a href="ident?i=u32">u32</a> end_seq = <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;end_seq;
<a name="L4077" href="source/net/ipv4/tcp_input.c#L4077">4077</a> 
<a name="L4078" href="source/net/ipv4/tcp_input.c#L4078">4078</a>                         if (<a href="ident?i=after">after</a>(<a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;end_seq, <a href="ident?i=tp">tp</a>-&gt;rcv_nxt))
<a name="L4079" href="source/net/ipv4/tcp_input.c#L4079">4079</a>                                 end_seq = <a href="ident?i=tp">tp</a>-&gt;rcv_nxt;
<a name="L4080" href="source/net/ipv4/tcp_input.c#L4080">4080</a>                         <a href="ident?i=tcp_dsack_set">tcp_dsack_set</a>(sk, <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=seq">seq</a>, end_seq);
<a name="L4081" href="source/net/ipv4/tcp_input.c#L4081">4081</a>                 }
<a name="L4082" href="source/net/ipv4/tcp_input.c#L4082">4082</a>         }
<a name="L4083" href="source/net/ipv4/tcp_input.c#L4083">4083</a> 
<a name="L4084" href="source/net/ipv4/tcp_input.c#L4084">4084</a>         <a href="ident?i=tcp_send_ack">tcp_send_ack</a>(sk);
<a name="L4085" href="source/net/ipv4/tcp_input.c#L4085">4085</a> }
<a name="L4086" href="source/net/ipv4/tcp_input.c#L4086">4086</a> 
<a name="L4087" href="source/net/ipv4/tcp_input.c#L4087">4087</a> <b><i>/* These routines update the SACK block as out-of-order packets arrive or</i></b>
<a name="L4088" href="source/net/ipv4/tcp_input.c#L4088">4088</a> <b><i> * in-order packets close up the sequence space.</i></b>
<a name="L4089" href="source/net/ipv4/tcp_input.c#L4089">4089</a> <b><i> */</i></b>
<a name="L4090" href="source/net/ipv4/tcp_input.c#L4090">4090</a> static void <a href="ident?i=tcp_sack_maybe_coalesce">tcp_sack_maybe_coalesce</a>(struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a>)
<a name="L4091" href="source/net/ipv4/tcp_input.c#L4091">4091</a> {
<a name="L4092" href="source/net/ipv4/tcp_input.c#L4092">4092</a>         int this_sack;
<a name="L4093" href="source/net/ipv4/tcp_input.c#L4093">4093</a>         struct <a href="ident?i=tcp_sack_block">tcp_sack_block</a> *<a href="ident?i=sp">sp</a> = &amp;<a href="ident?i=tp">tp</a>-&gt;selective_acks[0];
<a name="L4094" href="source/net/ipv4/tcp_input.c#L4094">4094</a>         struct <a href="ident?i=tcp_sack_block">tcp_sack_block</a> *swalk = <a href="ident?i=sp">sp</a> + 1;
<a name="L4095" href="source/net/ipv4/tcp_input.c#L4095">4095</a> 
<a name="L4096" href="source/net/ipv4/tcp_input.c#L4096">4096</a>         <b><i>/* See if the recent change to the first SACK eats into</i></b>
<a name="L4097" href="source/net/ipv4/tcp_input.c#L4097">4097</a> <b><i>         * or hits the sequence space of other SACK blocks, if so coalesce.</i></b>
<a name="L4098" href="source/net/ipv4/tcp_input.c#L4098">4098</a> <b><i>         */</i></b>
<a name="L4099" href="source/net/ipv4/tcp_input.c#L4099">4099</a>         for (this_sack = 1; this_sack &lt; <a href="ident?i=tp">tp</a>-&gt;rx_opt.num_sacks;) {
<a name="L4100" href="source/net/ipv4/tcp_input.c#L4100">4100</a>                 if (<a href="ident?i=tcp_sack_extend">tcp_sack_extend</a>(<a href="ident?i=sp">sp</a>, swalk-&gt;<a href="ident?i=start_seq">start_seq</a>, swalk-&gt;end_seq)) {
<a name="L4101" href="source/net/ipv4/tcp_input.c#L4101">4101</a>                         int <a href="ident?i=i">i</a>;
<a name="L4102" href="source/net/ipv4/tcp_input.c#L4102">4102</a> 
<a name="L4103" href="source/net/ipv4/tcp_input.c#L4103">4103</a>                         <b><i>/* Zap SWALK, by moving every further SACK up by one slot.</i></b>
<a name="L4104" href="source/net/ipv4/tcp_input.c#L4104">4104</a> <b><i>                         * Decrease num_sacks.</i></b>
<a name="L4105" href="source/net/ipv4/tcp_input.c#L4105">4105</a> <b><i>                         */</i></b>
<a name="L4106" href="source/net/ipv4/tcp_input.c#L4106">4106</a>                         <a href="ident?i=tp">tp</a>-&gt;rx_opt.num_sacks--;
<a name="L4107" href="source/net/ipv4/tcp_input.c#L4107">4107</a>                         for (<a href="ident?i=i">i</a> = this_sack; <a href="ident?i=i">i</a> &lt; <a href="ident?i=tp">tp</a>-&gt;rx_opt.num_sacks; <a href="ident?i=i">i</a>++)
<a name="L4108" href="source/net/ipv4/tcp_input.c#L4108">4108</a>                                 <a href="ident?i=sp">sp</a>[<a href="ident?i=i">i</a>] = <a href="ident?i=sp">sp</a>[<a href="ident?i=i">i</a> + 1];
<a name="L4109" href="source/net/ipv4/tcp_input.c#L4109">4109</a>                         continue;
<a name="L4110" href="source/net/ipv4/tcp_input.c#L4110">4110</a>                 }
<a name="L4111" href="source/net/ipv4/tcp_input.c#L4111">4111</a>                 this_sack++, swalk++;
<a name="L4112" href="source/net/ipv4/tcp_input.c#L4112">4112</a>         }
<a name="L4113" href="source/net/ipv4/tcp_input.c#L4113">4113</a> }
<a name="L4114" href="source/net/ipv4/tcp_input.c#L4114">4114</a> 
<a name="L4115" href="source/net/ipv4/tcp_input.c#L4115">4115</a> static void <a href="ident?i=tcp_sack_new_ofo_skb">tcp_sack_new_ofo_skb</a>(struct <a href="ident?i=sock">sock</a> *sk, <a href="ident?i=u32">u32</a> <a href="ident?i=seq">seq</a>, <a href="ident?i=u32">u32</a> end_seq)
<a name="L4116" href="source/net/ipv4/tcp_input.c#L4116">4116</a> {
<a name="L4117" href="source/net/ipv4/tcp_input.c#L4117">4117</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L4118" href="source/net/ipv4/tcp_input.c#L4118">4118</a>         struct <a href="ident?i=tcp_sack_block">tcp_sack_block</a> *<a href="ident?i=sp">sp</a> = &amp;<a href="ident?i=tp">tp</a>-&gt;selective_acks[0];
<a name="L4119" href="source/net/ipv4/tcp_input.c#L4119">4119</a>         int cur_sacks = <a href="ident?i=tp">tp</a>-&gt;rx_opt.num_sacks;
<a name="L4120" href="source/net/ipv4/tcp_input.c#L4120">4120</a>         int this_sack;
<a name="L4121" href="source/net/ipv4/tcp_input.c#L4121">4121</a> 
<a name="L4122" href="source/net/ipv4/tcp_input.c#L4122">4122</a>         if (!cur_sacks)
<a name="L4123" href="source/net/ipv4/tcp_input.c#L4123">4123</a>                 goto new_sack;
<a name="L4124" href="source/net/ipv4/tcp_input.c#L4124">4124</a> 
<a name="L4125" href="source/net/ipv4/tcp_input.c#L4125">4125</a>         for (this_sack = 0; this_sack &lt; cur_sacks; this_sack++, <a href="ident?i=sp">sp</a>++) {
<a name="L4126" href="source/net/ipv4/tcp_input.c#L4126">4126</a>                 if (<a href="ident?i=tcp_sack_extend">tcp_sack_extend</a>(<a href="ident?i=sp">sp</a>, <a href="ident?i=seq">seq</a>, end_seq)) {
<a name="L4127" href="source/net/ipv4/tcp_input.c#L4127">4127</a>                         <b><i>/* Rotate this_sack to the first one. */</i></b>
<a name="L4128" href="source/net/ipv4/tcp_input.c#L4128">4128</a>                         for (; this_sack &gt; 0; this_sack--, <a href="ident?i=sp">sp</a>--)
<a name="L4129" href="source/net/ipv4/tcp_input.c#L4129">4129</a>                                 <a href="ident?i=swap">swap</a>(*<a href="ident?i=sp">sp</a>, *(<a href="ident?i=sp">sp</a> - 1));
<a name="L4130" href="source/net/ipv4/tcp_input.c#L4130">4130</a>                         if (cur_sacks &gt; 1)
<a name="L4131" href="source/net/ipv4/tcp_input.c#L4131">4131</a>                                 <a href="ident?i=tcp_sack_maybe_coalesce">tcp_sack_maybe_coalesce</a>(<a href="ident?i=tp">tp</a>);
<a name="L4132" href="source/net/ipv4/tcp_input.c#L4132">4132</a>                         return;
<a name="L4133" href="source/net/ipv4/tcp_input.c#L4133">4133</a>                 }
<a name="L4134" href="source/net/ipv4/tcp_input.c#L4134">4134</a>         }
<a name="L4135" href="source/net/ipv4/tcp_input.c#L4135">4135</a> 
<a name="L4136" href="source/net/ipv4/tcp_input.c#L4136">4136</a>         <b><i>/* Could not find an adjacent existing SACK, build a new one,</i></b>
<a name="L4137" href="source/net/ipv4/tcp_input.c#L4137">4137</a> <b><i>         * put it at the front, and shift everyone else down.  We</i></b>
<a name="L4138" href="source/net/ipv4/tcp_input.c#L4138">4138</a> <b><i>         * always know there is at least one SACK present already here.</i></b>
<a name="L4139" href="source/net/ipv4/tcp_input.c#L4139">4139</a> <b><i>         *</i></b>
<a name="L4140" href="source/net/ipv4/tcp_input.c#L4140">4140</a> <b><i>         * If the sack array is full, forget about the last one.</i></b>
<a name="L4141" href="source/net/ipv4/tcp_input.c#L4141">4141</a> <b><i>         */</i></b>
<a name="L4142" href="source/net/ipv4/tcp_input.c#L4142">4142</a>         if (this_sack &gt;= <a href="ident?i=TCP_NUM_SACKS">TCP_NUM_SACKS</a>) {
<a name="L4143" href="source/net/ipv4/tcp_input.c#L4143">4143</a>                 this_sack--;
<a name="L4144" href="source/net/ipv4/tcp_input.c#L4144">4144</a>                 <a href="ident?i=tp">tp</a>-&gt;rx_opt.num_sacks--;
<a name="L4145" href="source/net/ipv4/tcp_input.c#L4145">4145</a>                 <a href="ident?i=sp">sp</a>--;
<a name="L4146" href="source/net/ipv4/tcp_input.c#L4146">4146</a>         }
<a name="L4147" href="source/net/ipv4/tcp_input.c#L4147">4147</a>         for (; this_sack &gt; 0; this_sack--, <a href="ident?i=sp">sp</a>--)
<a name="L4148" href="source/net/ipv4/tcp_input.c#L4148">4148</a>                 *<a href="ident?i=sp">sp</a> = *(<a href="ident?i=sp">sp</a> - 1);
<a name="L4149" href="source/net/ipv4/tcp_input.c#L4149">4149</a> 
<a name="L4150" href="source/net/ipv4/tcp_input.c#L4150">4150</a> new_sack:
<a name="L4151" href="source/net/ipv4/tcp_input.c#L4151">4151</a>         <b><i>/* Build the new head SACK, and we're done. */</i></b>
<a name="L4152" href="source/net/ipv4/tcp_input.c#L4152">4152</a>         <a href="ident?i=sp">sp</a>-&gt;<a href="ident?i=start_seq">start_seq</a> = <a href="ident?i=seq">seq</a>;
<a name="L4153" href="source/net/ipv4/tcp_input.c#L4153">4153</a>         <a href="ident?i=sp">sp</a>-&gt;end_seq = end_seq;
<a name="L4154" href="source/net/ipv4/tcp_input.c#L4154">4154</a>         <a href="ident?i=tp">tp</a>-&gt;rx_opt.num_sacks++;
<a name="L4155" href="source/net/ipv4/tcp_input.c#L4155">4155</a> }
<a name="L4156" href="source/net/ipv4/tcp_input.c#L4156">4156</a> 
<a name="L4157" href="source/net/ipv4/tcp_input.c#L4157">4157</a> <b><i>/* RCV.NXT advances, some SACKs should be eaten. */</i></b>
<a name="L4158" href="source/net/ipv4/tcp_input.c#L4158">4158</a> 
<a name="L4159" href="source/net/ipv4/tcp_input.c#L4159">4159</a> static void <a href="ident?i=tcp_sack_remove">tcp_sack_remove</a>(struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a>)
<a name="L4160" href="source/net/ipv4/tcp_input.c#L4160">4160</a> {
<a name="L4161" href="source/net/ipv4/tcp_input.c#L4161">4161</a>         struct <a href="ident?i=tcp_sack_block">tcp_sack_block</a> *<a href="ident?i=sp">sp</a> = &amp;<a href="ident?i=tp">tp</a>-&gt;selective_acks[0];
<a name="L4162" href="source/net/ipv4/tcp_input.c#L4162">4162</a>         int num_sacks = <a href="ident?i=tp">tp</a>-&gt;rx_opt.num_sacks;
<a name="L4163" href="source/net/ipv4/tcp_input.c#L4163">4163</a>         int this_sack;
<a name="L4164" href="source/net/ipv4/tcp_input.c#L4164">4164</a> 
<a name="L4165" href="source/net/ipv4/tcp_input.c#L4165">4165</a>         <b><i>/* Empty ofo queue, hence, all the SACKs are eaten. Clear. */</i></b>
<a name="L4166" href="source/net/ipv4/tcp_input.c#L4166">4166</a>         if (<a href="ident?i=skb_queue_empty">skb_queue_empty</a>(&amp;<a href="ident?i=tp">tp</a>-&gt;out_of_order_queue)) {
<a name="L4167" href="source/net/ipv4/tcp_input.c#L4167">4167</a>                 <a href="ident?i=tp">tp</a>-&gt;rx_opt.num_sacks = 0;
<a name="L4168" href="source/net/ipv4/tcp_input.c#L4168">4168</a>                 return;
<a name="L4169" href="source/net/ipv4/tcp_input.c#L4169">4169</a>         }
<a name="L4170" href="source/net/ipv4/tcp_input.c#L4170">4170</a> 
<a name="L4171" href="source/net/ipv4/tcp_input.c#L4171">4171</a>         for (this_sack = 0; this_sack &lt; num_sacks;) {
<a name="L4172" href="source/net/ipv4/tcp_input.c#L4172">4172</a>                 <b><i>/* Check if the start of the sack is covered by RCV.NXT. */</i></b>
<a name="L4173" href="source/net/ipv4/tcp_input.c#L4173">4173</a>                 if (!<a href="ident?i=before">before</a>(<a href="ident?i=tp">tp</a>-&gt;rcv_nxt, <a href="ident?i=sp">sp</a>-&gt;<a href="ident?i=start_seq">start_seq</a>)) {
<a name="L4174" href="source/net/ipv4/tcp_input.c#L4174">4174</a>                         int <a href="ident?i=i">i</a>;
<a name="L4175" href="source/net/ipv4/tcp_input.c#L4175">4175</a> 
<a name="L4176" href="source/net/ipv4/tcp_input.c#L4176">4176</a>                         <b><i>/* RCV.NXT must cover all the block! */</i></b>
<a name="L4177" href="source/net/ipv4/tcp_input.c#L4177">4177</a>                         <a href="ident?i=WARN_ON">WARN_ON</a>(<a href="ident?i=before">before</a>(<a href="ident?i=tp">tp</a>-&gt;rcv_nxt, <a href="ident?i=sp">sp</a>-&gt;end_seq));
<a name="L4178" href="source/net/ipv4/tcp_input.c#L4178">4178</a> 
<a name="L4179" href="source/net/ipv4/tcp_input.c#L4179">4179</a>                         <b><i>/* Zap this SACK, by moving forward any other SACKS. */</i></b>
<a name="L4180" href="source/net/ipv4/tcp_input.c#L4180">4180</a>                         for (<a href="ident?i=i">i</a> = this_sack+1; <a href="ident?i=i">i</a> &lt; num_sacks; <a href="ident?i=i">i</a>++)
<a name="L4181" href="source/net/ipv4/tcp_input.c#L4181">4181</a>                                 <a href="ident?i=tp">tp</a>-&gt;selective_acks[<a href="ident?i=i">i</a>-1] = <a href="ident?i=tp">tp</a>-&gt;selective_acks[<a href="ident?i=i">i</a>];
<a name="L4182" href="source/net/ipv4/tcp_input.c#L4182">4182</a>                         num_sacks--;
<a name="L4183" href="source/net/ipv4/tcp_input.c#L4183">4183</a>                         continue;
<a name="L4184" href="source/net/ipv4/tcp_input.c#L4184">4184</a>                 }
<a name="L4185" href="source/net/ipv4/tcp_input.c#L4185">4185</a>                 this_sack++;
<a name="L4186" href="source/net/ipv4/tcp_input.c#L4186">4186</a>                 <a href="ident?i=sp">sp</a>++;
<a name="L4187" href="source/net/ipv4/tcp_input.c#L4187">4187</a>         }
<a name="L4188" href="source/net/ipv4/tcp_input.c#L4188">4188</a>         <a href="ident?i=tp">tp</a>-&gt;rx_opt.num_sacks = num_sacks;
<a name="L4189" href="source/net/ipv4/tcp_input.c#L4189">4189</a> }
<a name="L4190" href="source/net/ipv4/tcp_input.c#L4190">4190</a> 
<a name="L4191" href="source/net/ipv4/tcp_input.c#L4191">4191</a> <b><i>/**</i></b>
<a name="L4192" href="source/net/ipv4/tcp_input.c#L4192">4192</a> <b><i> * tcp_try_coalesce - try to merge skb to prior one</i></b>
<a name="L4193" href="source/net/ipv4/tcp_input.c#L4193">4193</a> <b><i> * @sk: socket</i></b>
<a name="L4194" href="source/net/ipv4/tcp_input.c#L4194">4194</a> <b><i> * @to: prior buffer</i></b>
<a name="L4195" href="source/net/ipv4/tcp_input.c#L4195">4195</a> <b><i> * @from: buffer to add in queue</i></b>
<a name="L4196" href="source/net/ipv4/tcp_input.c#L4196">4196</a> <b><i> * @fragstolen: pointer to boolean</i></b>
<a name="L4197" href="source/net/ipv4/tcp_input.c#L4197">4197</a> <b><i> *</i></b>
<a name="L4198" href="source/net/ipv4/tcp_input.c#L4198">4198</a> <b><i> * Before queueing skb @from after @to, try to merge them</i></b>
<a name="L4199" href="source/net/ipv4/tcp_input.c#L4199">4199</a> <b><i> * to reduce overall memory use and queue lengths, if cost is small.</i></b>
<a name="L4200" href="source/net/ipv4/tcp_input.c#L4200">4200</a> <b><i> * Packets in ofo or receive queues can stay a long time.</i></b>
<a name="L4201" href="source/net/ipv4/tcp_input.c#L4201">4201</a> <b><i> * Better try to coalesce them right now to avoid future collapses.</i></b>
<a name="L4202" href="source/net/ipv4/tcp_input.c#L4202">4202</a> <b><i> * Returns true if caller should free @from instead of queueing it</i></b>
<a name="L4203" href="source/net/ipv4/tcp_input.c#L4203">4203</a> <b><i> */</i></b>
<a name="L4204" href="source/net/ipv4/tcp_input.c#L4204">4204</a> static <a href="ident?i=bool">bool</a> <a href="ident?i=tcp_try_coalesce">tcp_try_coalesce</a>(struct <a href="ident?i=sock">sock</a> *sk,
<a name="L4205" href="source/net/ipv4/tcp_input.c#L4205">4205</a>                              struct <a href="ident?i=sk_buff">sk_buff</a> *to,
<a name="L4206" href="source/net/ipv4/tcp_input.c#L4206">4206</a>                              struct <a href="ident?i=sk_buff">sk_buff</a> *from,
<a name="L4207" href="source/net/ipv4/tcp_input.c#L4207">4207</a>                              <a href="ident?i=bool">bool</a> *fragstolen)
<a name="L4208" href="source/net/ipv4/tcp_input.c#L4208">4208</a> {
<a name="L4209" href="source/net/ipv4/tcp_input.c#L4209">4209</a>         int <a href="ident?i=delta">delta</a>;
<a name="L4210" href="source/net/ipv4/tcp_input.c#L4210">4210</a> 
<a name="L4211" href="source/net/ipv4/tcp_input.c#L4211">4211</a>         *fragstolen = <a href="ident?i=false">false</a>;
<a name="L4212" href="source/net/ipv4/tcp_input.c#L4212">4212</a> 
<a name="L4213" href="source/net/ipv4/tcp_input.c#L4213">4213</a>         <b><i>/* Its possible this segment overlaps with prior segment in queue */</i></b>
<a name="L4214" href="source/net/ipv4/tcp_input.c#L4214">4214</a>         if (<a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(from)-&gt;<a href="ident?i=seq">seq</a> != <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(to)-&gt;end_seq)
<a name="L4215" href="source/net/ipv4/tcp_input.c#L4215">4215</a>                 return <a href="ident?i=false">false</a>;
<a name="L4216" href="source/net/ipv4/tcp_input.c#L4216">4216</a> 
<a name="L4217" href="source/net/ipv4/tcp_input.c#L4217">4217</a>         if (!<a href="ident?i=skb_try_coalesce">skb_try_coalesce</a>(to, from, fragstolen, &amp;<a href="ident?i=delta">delta</a>))
<a name="L4218" href="source/net/ipv4/tcp_input.c#L4218">4218</a>                 return <a href="ident?i=false">false</a>;
<a name="L4219" href="source/net/ipv4/tcp_input.c#L4219">4219</a> 
<a name="L4220" href="source/net/ipv4/tcp_input.c#L4220">4220</a>         <a href="ident?i=atomic_add">atomic_add</a>(<a href="ident?i=delta">delta</a>, &amp;sk-&gt;<a href="ident?i=sk_rmem_alloc">sk_rmem_alloc</a>);
<a name="L4221" href="source/net/ipv4/tcp_input.c#L4221">4221</a>         <a href="ident?i=sk_mem_charge">sk_mem_charge</a>(sk, <a href="ident?i=delta">delta</a>);
<a name="L4222" href="source/net/ipv4/tcp_input.c#L4222">4222</a>         <a href="ident?i=NET_INC_STATS_BH">NET_INC_STATS_BH</a>(<a href="ident?i=sock_net">sock_net</a>(sk), LINUX_MIB_TCPRCVCOALESCE);
<a name="L4223" href="source/net/ipv4/tcp_input.c#L4223">4223</a>         <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(to)-&gt;end_seq = <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(from)-&gt;end_seq;
<a name="L4224" href="source/net/ipv4/tcp_input.c#L4224">4224</a>         <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(to)-&gt;ack_seq = <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(from)-&gt;ack_seq;
<a name="L4225" href="source/net/ipv4/tcp_input.c#L4225">4225</a>         <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(to)-&gt;tcp_flags |= <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(from)-&gt;tcp_flags;
<a name="L4226" href="source/net/ipv4/tcp_input.c#L4226">4226</a>         return <a href="ident?i=true">true</a>;
<a name="L4227" href="source/net/ipv4/tcp_input.c#L4227">4227</a> }
<a name="L4228" href="source/net/ipv4/tcp_input.c#L4228">4228</a> 
<a name="L4229" href="source/net/ipv4/tcp_input.c#L4229">4229</a> <b><i>/* This one checks to see if we can put data from the</i></b>
<a name="L4230" href="source/net/ipv4/tcp_input.c#L4230">4230</a> <b><i> * out_of_order queue into the receive_queue.</i></b>
<a name="L4231" href="source/net/ipv4/tcp_input.c#L4231">4231</a> <b><i> */</i></b>
<a name="L4232" href="source/net/ipv4/tcp_input.c#L4232">4232</a> static void <a href="ident?i=tcp_ofo_queue">tcp_ofo_queue</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L4233" href="source/net/ipv4/tcp_input.c#L4233">4233</a> {
<a name="L4234" href="source/net/ipv4/tcp_input.c#L4234">4234</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L4235" href="source/net/ipv4/tcp_input.c#L4235">4235</a>         <a href="ident?i=__u32">__u32</a> dsack_high = <a href="ident?i=tp">tp</a>-&gt;rcv_nxt;
<a name="L4236" href="source/net/ipv4/tcp_input.c#L4236">4236</a>         struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, *<a href="ident?i=tail">tail</a>;
<a name="L4237" href="source/net/ipv4/tcp_input.c#L4237">4237</a>         <a href="ident?i=bool">bool</a> fragstolen, eaten;
<a name="L4238" href="source/net/ipv4/tcp_input.c#L4238">4238</a> 
<a name="L4239" href="source/net/ipv4/tcp_input.c#L4239">4239</a>         while ((<a href="ident?i=skb">skb</a> = <a href="ident?i=skb_peek">skb_peek</a>(&amp;<a href="ident?i=tp">tp</a>-&gt;out_of_order_queue)) != <a href="ident?i=NULL">NULL</a>) {
<a name="L4240" href="source/net/ipv4/tcp_input.c#L4240">4240</a>                 if (<a href="ident?i=after">after</a>(<a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=seq">seq</a>, <a href="ident?i=tp">tp</a>-&gt;rcv_nxt))
<a name="L4241" href="source/net/ipv4/tcp_input.c#L4241">4241</a>                         break;
<a name="L4242" href="source/net/ipv4/tcp_input.c#L4242">4242</a> 
<a name="L4243" href="source/net/ipv4/tcp_input.c#L4243">4243</a>                 if (<a href="ident?i=before">before</a>(<a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=seq">seq</a>, dsack_high)) {
<a name="L4244" href="source/net/ipv4/tcp_input.c#L4244">4244</a>                         <a href="ident?i=__u32">__u32</a> dsack = dsack_high;
<a name="L4245" href="source/net/ipv4/tcp_input.c#L4245">4245</a>                         if (<a href="ident?i=before">before</a>(<a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;end_seq, dsack_high))
<a name="L4246" href="source/net/ipv4/tcp_input.c#L4246">4246</a>                                 dsack_high = <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;end_seq;
<a name="L4247" href="source/net/ipv4/tcp_input.c#L4247">4247</a>                         <a href="ident?i=tcp_dsack_extend">tcp_dsack_extend</a>(sk, <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=seq">seq</a>, dsack);
<a name="L4248" href="source/net/ipv4/tcp_input.c#L4248">4248</a>                 }
<a name="L4249" href="source/net/ipv4/tcp_input.c#L4249">4249</a> 
<a name="L4250" href="source/net/ipv4/tcp_input.c#L4250">4250</a>                 <a href="ident?i=__skb_unlink">__skb_unlink</a>(<a href="ident?i=skb">skb</a>, &amp;<a href="ident?i=tp">tp</a>-&gt;out_of_order_queue);
<a name="L4251" href="source/net/ipv4/tcp_input.c#L4251">4251</a>                 if (!<a href="ident?i=after">after</a>(<a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;end_seq, <a href="ident?i=tp">tp</a>-&gt;rcv_nxt)) {
<a name="L4252" href="source/net/ipv4/tcp_input.c#L4252">4252</a>                         <a href="ident?i=SOCK_DEBUG">SOCK_DEBUG</a>(sk, <i>"ofo packet was already received\n"</i>);
<a name="L4253" href="source/net/ipv4/tcp_input.c#L4253">4253</a>                         <a href="ident?i=__kfree_skb">__kfree_skb</a>(<a href="ident?i=skb">skb</a>);
<a name="L4254" href="source/net/ipv4/tcp_input.c#L4254">4254</a>                         continue;
<a name="L4255" href="source/net/ipv4/tcp_input.c#L4255">4255</a>                 }
<a name="L4256" href="source/net/ipv4/tcp_input.c#L4256">4256</a>                 <a href="ident?i=SOCK_DEBUG">SOCK_DEBUG</a>(sk, <i>"ofo requeuing : rcv_next %X seq %X - %X\n"</i>,
<a name="L4257" href="source/net/ipv4/tcp_input.c#L4257">4257</a>                            <a href="ident?i=tp">tp</a>-&gt;rcv_nxt, <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=seq">seq</a>,
<a name="L4258" href="source/net/ipv4/tcp_input.c#L4258">4258</a>                            <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;end_seq);
<a name="L4259" href="source/net/ipv4/tcp_input.c#L4259">4259</a> 
<a name="L4260" href="source/net/ipv4/tcp_input.c#L4260">4260</a>                 <a href="ident?i=tail">tail</a> = <a href="ident?i=skb_peek_tail">skb_peek_tail</a>(&amp;sk-&gt;sk_receive_queue);
<a name="L4261" href="source/net/ipv4/tcp_input.c#L4261">4261</a>                 eaten = <a href="ident?i=tail">tail</a> &amp;&amp; <a href="ident?i=tcp_try_coalesce">tcp_try_coalesce</a>(sk, <a href="ident?i=tail">tail</a>, <a href="ident?i=skb">skb</a>, &amp;fragstolen);
<a name="L4262" href="source/net/ipv4/tcp_input.c#L4262">4262</a>                 <a href="ident?i=tcp_rcv_nxt_update">tcp_rcv_nxt_update</a>(<a href="ident?i=tp">tp</a>, <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;end_seq);
<a name="L4263" href="source/net/ipv4/tcp_input.c#L4263">4263</a>                 if (!eaten)
<a name="L4264" href="source/net/ipv4/tcp_input.c#L4264">4264</a>                         <a href="ident?i=__skb_queue_tail">__skb_queue_tail</a>(&amp;sk-&gt;sk_receive_queue, <a href="ident?i=skb">skb</a>);
<a name="L4265" href="source/net/ipv4/tcp_input.c#L4265">4265</a>                 if (<a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;tcp_flags &amp; <a href="ident?i=TCPHDR_FIN">TCPHDR_FIN</a>)
<a name="L4266" href="source/net/ipv4/tcp_input.c#L4266">4266</a>                         <a href="ident?i=tcp_fin">tcp_fin</a>(sk);
<a name="L4267" href="source/net/ipv4/tcp_input.c#L4267">4267</a>                 if (eaten)
<a name="L4268" href="source/net/ipv4/tcp_input.c#L4268">4268</a>                         <a href="ident?i=kfree_skb_partial">kfree_skb_partial</a>(<a href="ident?i=skb">skb</a>, fragstolen);
<a name="L4269" href="source/net/ipv4/tcp_input.c#L4269">4269</a>         }
<a name="L4270" href="source/net/ipv4/tcp_input.c#L4270">4270</a> }
<a name="L4271" href="source/net/ipv4/tcp_input.c#L4271">4271</a> 
<a name="L4272" href="source/net/ipv4/tcp_input.c#L4272">4272</a> static <a href="ident?i=bool">bool</a> <a href="ident?i=tcp_prune_ofo_queue">tcp_prune_ofo_queue</a>(struct <a href="ident?i=sock">sock</a> *sk);
<a name="L4273" href="source/net/ipv4/tcp_input.c#L4273">4273</a> static int <a href="ident?i=tcp_prune_queue">tcp_prune_queue</a>(struct <a href="ident?i=sock">sock</a> *sk);
<a name="L4274" href="source/net/ipv4/tcp_input.c#L4274">4274</a> 
<a name="L4275" href="source/net/ipv4/tcp_input.c#L4275">4275</a> static int <a href="ident?i=tcp_try_rmem_schedule">tcp_try_rmem_schedule</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
<a name="L4276" href="source/net/ipv4/tcp_input.c#L4276">4276</a>                                  unsigned int <a href="ident?i=size">size</a>)
<a name="L4277" href="source/net/ipv4/tcp_input.c#L4277">4277</a> {
<a name="L4278" href="source/net/ipv4/tcp_input.c#L4278">4278</a>         if (<a href="ident?i=atomic_read">atomic_read</a>(&amp;sk-&gt;<a href="ident?i=sk_rmem_alloc">sk_rmem_alloc</a>) &gt; sk-&gt;sk_rcvbuf ||
<a name="L4279" href="source/net/ipv4/tcp_input.c#L4279">4279</a>             !<a href="ident?i=sk_rmem_schedule">sk_rmem_schedule</a>(sk, <a href="ident?i=skb">skb</a>, <a href="ident?i=size">size</a>)) {
<a name="L4280" href="source/net/ipv4/tcp_input.c#L4280">4280</a> 
<a name="L4281" href="source/net/ipv4/tcp_input.c#L4281">4281</a>                 if (<a href="ident?i=tcp_prune_queue">tcp_prune_queue</a>(sk) &lt; 0)
<a name="L4282" href="source/net/ipv4/tcp_input.c#L4282">4282</a>                         return -1;
<a name="L4283" href="source/net/ipv4/tcp_input.c#L4283">4283</a> 
<a name="L4284" href="source/net/ipv4/tcp_input.c#L4284">4284</a>                 if (!<a href="ident?i=sk_rmem_schedule">sk_rmem_schedule</a>(sk, <a href="ident?i=skb">skb</a>, <a href="ident?i=size">size</a>)) {
<a name="L4285" href="source/net/ipv4/tcp_input.c#L4285">4285</a>                         if (!<a href="ident?i=tcp_prune_ofo_queue">tcp_prune_ofo_queue</a>(sk))
<a name="L4286" href="source/net/ipv4/tcp_input.c#L4286">4286</a>                                 return -1;
<a name="L4287" href="source/net/ipv4/tcp_input.c#L4287">4287</a> 
<a name="L4288" href="source/net/ipv4/tcp_input.c#L4288">4288</a>                         if (!<a href="ident?i=sk_rmem_schedule">sk_rmem_schedule</a>(sk, <a href="ident?i=skb">skb</a>, <a href="ident?i=size">size</a>))
<a name="L4289" href="source/net/ipv4/tcp_input.c#L4289">4289</a>                                 return -1;
<a name="L4290" href="source/net/ipv4/tcp_input.c#L4290">4290</a>                 }
<a name="L4291" href="source/net/ipv4/tcp_input.c#L4291">4291</a>         }
<a name="L4292" href="source/net/ipv4/tcp_input.c#L4292">4292</a>         return 0;
<a name="L4293" href="source/net/ipv4/tcp_input.c#L4293">4293</a> }
<a name="L4294" href="source/net/ipv4/tcp_input.c#L4294">4294</a> 
<a name="L4295" href="source/net/ipv4/tcp_input.c#L4295">4295</a> static void <a href="ident?i=tcp_data_queue_ofo">tcp_data_queue_ofo</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L4296" href="source/net/ipv4/tcp_input.c#L4296">4296</a> {
<a name="L4297" href="source/net/ipv4/tcp_input.c#L4297">4297</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L4298" href="source/net/ipv4/tcp_input.c#L4298">4298</a>         struct <a href="ident?i=sk_buff">sk_buff</a> *skb1;
<a name="L4299" href="source/net/ipv4/tcp_input.c#L4299">4299</a>         <a href="ident?i=u32">u32</a> <a href="ident?i=seq">seq</a>, end_seq;
<a name="L4300" href="source/net/ipv4/tcp_input.c#L4300">4300</a> 
<a name="L4301" href="source/net/ipv4/tcp_input.c#L4301">4301</a>         <a href="ident?i=tcp_ecn_check_ce">tcp_ecn_check_ce</a>(<a href="ident?i=tp">tp</a>, <a href="ident?i=skb">skb</a>);
<a name="L4302" href="source/net/ipv4/tcp_input.c#L4302">4302</a> 
<a name="L4303" href="source/net/ipv4/tcp_input.c#L4303">4303</a>         if (<a href="ident?i=unlikely">unlikely</a>(<a href="ident?i=tcp_try_rmem_schedule">tcp_try_rmem_schedule</a>(sk, <a href="ident?i=skb">skb</a>, <a href="ident?i=skb">skb</a>-&gt;truesize))) {
<a name="L4304" href="source/net/ipv4/tcp_input.c#L4304">4304</a>                 <a href="ident?i=NET_INC_STATS_BH">NET_INC_STATS_BH</a>(<a href="ident?i=sock_net">sock_net</a>(sk), LINUX_MIB_TCPOFODROP);
<a name="L4305" href="source/net/ipv4/tcp_input.c#L4305">4305</a>                 <a href="ident?i=__kfree_skb">__kfree_skb</a>(<a href="ident?i=skb">skb</a>);
<a name="L4306" href="source/net/ipv4/tcp_input.c#L4306">4306</a>                 return;
<a name="L4307" href="source/net/ipv4/tcp_input.c#L4307">4307</a>         }
<a name="L4308" href="source/net/ipv4/tcp_input.c#L4308">4308</a> 
<a name="L4309" href="source/net/ipv4/tcp_input.c#L4309">4309</a>         <b><i>/* Disable header prediction. */</i></b>
<a name="L4310" href="source/net/ipv4/tcp_input.c#L4310">4310</a>         <a href="ident?i=tp">tp</a>-&gt;pred_flags = 0;
<a name="L4311" href="source/net/ipv4/tcp_input.c#L4311">4311</a>         <a href="ident?i=inet_csk_schedule_ack">inet_csk_schedule_ack</a>(sk);
<a name="L4312" href="source/net/ipv4/tcp_input.c#L4312">4312</a> 
<a name="L4313" href="source/net/ipv4/tcp_input.c#L4313">4313</a>         <a href="ident?i=NET_INC_STATS_BH">NET_INC_STATS_BH</a>(<a href="ident?i=sock_net">sock_net</a>(sk), LINUX_MIB_TCPOFOQUEUE);
<a name="L4314" href="source/net/ipv4/tcp_input.c#L4314">4314</a>         <a href="ident?i=SOCK_DEBUG">SOCK_DEBUG</a>(sk, <i>"out of order segment: rcv_next %X seq %X - %X\n"</i>,
<a name="L4315" href="source/net/ipv4/tcp_input.c#L4315">4315</a>                    <a href="ident?i=tp">tp</a>-&gt;rcv_nxt, <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=seq">seq</a>, <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;end_seq);
<a name="L4316" href="source/net/ipv4/tcp_input.c#L4316">4316</a> 
<a name="L4317" href="source/net/ipv4/tcp_input.c#L4317">4317</a>         skb1 = <a href="ident?i=skb_peek_tail">skb_peek_tail</a>(&amp;<a href="ident?i=tp">tp</a>-&gt;out_of_order_queue);
<a name="L4318" href="source/net/ipv4/tcp_input.c#L4318">4318</a>         if (!skb1) {
<a name="L4319" href="source/net/ipv4/tcp_input.c#L4319">4319</a>                 <b><i>/* Initial out of order segment, build 1 SACK. */</i></b>
<a name="L4320" href="source/net/ipv4/tcp_input.c#L4320">4320</a>                 if (<a href="ident?i=tcp_is_sack">tcp_is_sack</a>(<a href="ident?i=tp">tp</a>)) {
<a name="L4321" href="source/net/ipv4/tcp_input.c#L4321">4321</a>                         <a href="ident?i=tp">tp</a>-&gt;rx_opt.num_sacks = 1;
<a name="L4322" href="source/net/ipv4/tcp_input.c#L4322">4322</a>                         <a href="ident?i=tp">tp</a>-&gt;selective_acks[0].<a href="ident?i=start_seq">start_seq</a> = <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=seq">seq</a>;
<a name="L4323" href="source/net/ipv4/tcp_input.c#L4323">4323</a>                         <a href="ident?i=tp">tp</a>-&gt;selective_acks[0].end_seq =
<a name="L4324" href="source/net/ipv4/tcp_input.c#L4324">4324</a>                                                 <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;end_seq;
<a name="L4325" href="source/net/ipv4/tcp_input.c#L4325">4325</a>                 }
<a name="L4326" href="source/net/ipv4/tcp_input.c#L4326">4326</a>                 <a href="ident?i=__skb_queue_head">__skb_queue_head</a>(&amp;<a href="ident?i=tp">tp</a>-&gt;out_of_order_queue, <a href="ident?i=skb">skb</a>);
<a name="L4327" href="source/net/ipv4/tcp_input.c#L4327">4327</a>                 goto <a href="ident?i=end">end</a>;
<a name="L4328" href="source/net/ipv4/tcp_input.c#L4328">4328</a>         }
<a name="L4329" href="source/net/ipv4/tcp_input.c#L4329">4329</a> 
<a name="L4330" href="source/net/ipv4/tcp_input.c#L4330">4330</a>         <a href="ident?i=seq">seq</a> = <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=seq">seq</a>;
<a name="L4331" href="source/net/ipv4/tcp_input.c#L4331">4331</a>         end_seq = <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;end_seq;
<a name="L4332" href="source/net/ipv4/tcp_input.c#L4332">4332</a> 
<a name="L4333" href="source/net/ipv4/tcp_input.c#L4333">4333</a>         if (<a href="ident?i=seq">seq</a> == <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(skb1)-&gt;end_seq) {
<a name="L4334" href="source/net/ipv4/tcp_input.c#L4334">4334</a>                 <a href="ident?i=bool">bool</a> fragstolen;
<a name="L4335" href="source/net/ipv4/tcp_input.c#L4335">4335</a> 
<a name="L4336" href="source/net/ipv4/tcp_input.c#L4336">4336</a>                 if (!<a href="ident?i=tcp_try_coalesce">tcp_try_coalesce</a>(sk, skb1, <a href="ident?i=skb">skb</a>, &amp;fragstolen)) {
<a name="L4337" href="source/net/ipv4/tcp_input.c#L4337">4337</a>                         <a href="ident?i=__skb_queue_after">__skb_queue_after</a>(&amp;<a href="ident?i=tp">tp</a>-&gt;out_of_order_queue, skb1, <a href="ident?i=skb">skb</a>);
<a name="L4338" href="source/net/ipv4/tcp_input.c#L4338">4338</a>                 } else {
<a name="L4339" href="source/net/ipv4/tcp_input.c#L4339">4339</a>                         <a href="ident?i=tcp_grow_window">tcp_grow_window</a>(sk, <a href="ident?i=skb">skb</a>);
<a name="L4340" href="source/net/ipv4/tcp_input.c#L4340">4340</a>                         <a href="ident?i=kfree_skb_partial">kfree_skb_partial</a>(<a href="ident?i=skb">skb</a>, fragstolen);
<a name="L4341" href="source/net/ipv4/tcp_input.c#L4341">4341</a>                         <a href="ident?i=skb">skb</a> = <a href="ident?i=NULL">NULL</a>;
<a name="L4342" href="source/net/ipv4/tcp_input.c#L4342">4342</a>                 }
<a name="L4343" href="source/net/ipv4/tcp_input.c#L4343">4343</a> 
<a name="L4344" href="source/net/ipv4/tcp_input.c#L4344">4344</a>                 if (!<a href="ident?i=tp">tp</a>-&gt;rx_opt.num_sacks ||
<a name="L4345" href="source/net/ipv4/tcp_input.c#L4345">4345</a>                     <a href="ident?i=tp">tp</a>-&gt;selective_acks[0].end_seq != <a href="ident?i=seq">seq</a>)
<a name="L4346" href="source/net/ipv4/tcp_input.c#L4346">4346</a>                         goto add_sack;
<a name="L4347" href="source/net/ipv4/tcp_input.c#L4347">4347</a> 
<a name="L4348" href="source/net/ipv4/tcp_input.c#L4348">4348</a>                 <b><i>/* Common case: data arrive in order after hole. */</i></b>
<a name="L4349" href="source/net/ipv4/tcp_input.c#L4349">4349</a>                 <a href="ident?i=tp">tp</a>-&gt;selective_acks[0].end_seq = end_seq;
<a name="L4350" href="source/net/ipv4/tcp_input.c#L4350">4350</a>                 goto <a href="ident?i=end">end</a>;
<a name="L4351" href="source/net/ipv4/tcp_input.c#L4351">4351</a>         }
<a name="L4352" href="source/net/ipv4/tcp_input.c#L4352">4352</a> 
<a name="L4353" href="source/net/ipv4/tcp_input.c#L4353">4353</a>         <b><i>/* Find place to insert this segment. */</i></b>
<a name="L4354" href="source/net/ipv4/tcp_input.c#L4354">4354</a>         while (1) {
<a name="L4355" href="source/net/ipv4/tcp_input.c#L4355">4355</a>                 if (!<a href="ident?i=after">after</a>(<a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(skb1)-&gt;<a href="ident?i=seq">seq</a>, <a href="ident?i=seq">seq</a>))
<a name="L4356" href="source/net/ipv4/tcp_input.c#L4356">4356</a>                         break;
<a name="L4357" href="source/net/ipv4/tcp_input.c#L4357">4357</a>                 if (<a href="ident?i=skb_queue_is_first">skb_queue_is_first</a>(&amp;<a href="ident?i=tp">tp</a>-&gt;out_of_order_queue, skb1)) {
<a name="L4358" href="source/net/ipv4/tcp_input.c#L4358">4358</a>                         skb1 = <a href="ident?i=NULL">NULL</a>;
<a name="L4359" href="source/net/ipv4/tcp_input.c#L4359">4359</a>                         break;
<a name="L4360" href="source/net/ipv4/tcp_input.c#L4360">4360</a>                 }
<a name="L4361" href="source/net/ipv4/tcp_input.c#L4361">4361</a>                 skb1 = <a href="ident?i=skb_queue_prev">skb_queue_prev</a>(&amp;<a href="ident?i=tp">tp</a>-&gt;out_of_order_queue, skb1);
<a name="L4362" href="source/net/ipv4/tcp_input.c#L4362">4362</a>         }
<a name="L4363" href="source/net/ipv4/tcp_input.c#L4363">4363</a> 
<a name="L4364" href="source/net/ipv4/tcp_input.c#L4364">4364</a>         <b><i>/* Do skb overlap to previous one? */</i></b>
<a name="L4365" href="source/net/ipv4/tcp_input.c#L4365">4365</a>         if (skb1 &amp;&amp; <a href="ident?i=before">before</a>(<a href="ident?i=seq">seq</a>, <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(skb1)-&gt;end_seq)) {
<a name="L4366" href="source/net/ipv4/tcp_input.c#L4366">4366</a>                 if (!<a href="ident?i=after">after</a>(end_seq, <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(skb1)-&gt;end_seq)) {
<a name="L4367" href="source/net/ipv4/tcp_input.c#L4367">4367</a>                         <b><i>/* All the bits are present. Drop. */</i></b>
<a name="L4368" href="source/net/ipv4/tcp_input.c#L4368">4368</a>                         <a href="ident?i=NET_INC_STATS_BH">NET_INC_STATS_BH</a>(<a href="ident?i=sock_net">sock_net</a>(sk), LINUX_MIB_TCPOFOMERGE);
<a name="L4369" href="source/net/ipv4/tcp_input.c#L4369">4369</a>                         <a href="ident?i=__kfree_skb">__kfree_skb</a>(<a href="ident?i=skb">skb</a>);
<a name="L4370" href="source/net/ipv4/tcp_input.c#L4370">4370</a>                         <a href="ident?i=skb">skb</a> = <a href="ident?i=NULL">NULL</a>;
<a name="L4371" href="source/net/ipv4/tcp_input.c#L4371">4371</a>                         <a href="ident?i=tcp_dsack_set">tcp_dsack_set</a>(sk, <a href="ident?i=seq">seq</a>, end_seq);
<a name="L4372" href="source/net/ipv4/tcp_input.c#L4372">4372</a>                         goto add_sack;
<a name="L4373" href="source/net/ipv4/tcp_input.c#L4373">4373</a>                 }
<a name="L4374" href="source/net/ipv4/tcp_input.c#L4374">4374</a>                 if (<a href="ident?i=after">after</a>(<a href="ident?i=seq">seq</a>, <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(skb1)-&gt;<a href="ident?i=seq">seq</a>)) {
<a name="L4375" href="source/net/ipv4/tcp_input.c#L4375">4375</a>                         <b><i>/* Partial overlap. */</i></b>
<a name="L4376" href="source/net/ipv4/tcp_input.c#L4376">4376</a>                         <a href="ident?i=tcp_dsack_set">tcp_dsack_set</a>(sk, <a href="ident?i=seq">seq</a>,
<a name="L4377" href="source/net/ipv4/tcp_input.c#L4377">4377</a>                                       <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(skb1)-&gt;end_seq);
<a name="L4378" href="source/net/ipv4/tcp_input.c#L4378">4378</a>                 } else {
<a name="L4379" href="source/net/ipv4/tcp_input.c#L4379">4379</a>                         if (<a href="ident?i=skb_queue_is_first">skb_queue_is_first</a>(&amp;<a href="ident?i=tp">tp</a>-&gt;out_of_order_queue,
<a name="L4380" href="source/net/ipv4/tcp_input.c#L4380">4380</a>                                                skb1))
<a name="L4381" href="source/net/ipv4/tcp_input.c#L4381">4381</a>                                 skb1 = <a href="ident?i=NULL">NULL</a>;
<a name="L4382" href="source/net/ipv4/tcp_input.c#L4382">4382</a>                         else
<a name="L4383" href="source/net/ipv4/tcp_input.c#L4383">4383</a>                                 skb1 = <a href="ident?i=skb_queue_prev">skb_queue_prev</a>(
<a name="L4384" href="source/net/ipv4/tcp_input.c#L4384">4384</a>                                         &amp;<a href="ident?i=tp">tp</a>-&gt;out_of_order_queue,
<a name="L4385" href="source/net/ipv4/tcp_input.c#L4385">4385</a>                                         skb1);
<a name="L4386" href="source/net/ipv4/tcp_input.c#L4386">4386</a>                 }
<a name="L4387" href="source/net/ipv4/tcp_input.c#L4387">4387</a>         }
<a name="L4388" href="source/net/ipv4/tcp_input.c#L4388">4388</a>         if (!skb1)
<a name="L4389" href="source/net/ipv4/tcp_input.c#L4389">4389</a>                 <a href="ident?i=__skb_queue_head">__skb_queue_head</a>(&amp;<a href="ident?i=tp">tp</a>-&gt;out_of_order_queue, <a href="ident?i=skb">skb</a>);
<a name="L4390" href="source/net/ipv4/tcp_input.c#L4390">4390</a>         else
<a name="L4391" href="source/net/ipv4/tcp_input.c#L4391">4391</a>                 <a href="ident?i=__skb_queue_after">__skb_queue_after</a>(&amp;<a href="ident?i=tp">tp</a>-&gt;out_of_order_queue, skb1, <a href="ident?i=skb">skb</a>);
<a name="L4392" href="source/net/ipv4/tcp_input.c#L4392">4392</a> 
<a name="L4393" href="source/net/ipv4/tcp_input.c#L4393">4393</a>         <b><i>/* And clean segments covered by new one as whole. */</i></b>
<a name="L4394" href="source/net/ipv4/tcp_input.c#L4394">4394</a>         while (!<a href="ident?i=skb_queue_is_last">skb_queue_is_last</a>(&amp;<a href="ident?i=tp">tp</a>-&gt;out_of_order_queue, <a href="ident?i=skb">skb</a>)) {
<a name="L4395" href="source/net/ipv4/tcp_input.c#L4395">4395</a>                 skb1 = <a href="ident?i=skb_queue_next">skb_queue_next</a>(&amp;<a href="ident?i=tp">tp</a>-&gt;out_of_order_queue, <a href="ident?i=skb">skb</a>);
<a name="L4396" href="source/net/ipv4/tcp_input.c#L4396">4396</a> 
<a name="L4397" href="source/net/ipv4/tcp_input.c#L4397">4397</a>                 if (!<a href="ident?i=after">after</a>(end_seq, <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(skb1)-&gt;<a href="ident?i=seq">seq</a>))
<a name="L4398" href="source/net/ipv4/tcp_input.c#L4398">4398</a>                         break;
<a name="L4399" href="source/net/ipv4/tcp_input.c#L4399">4399</a>                 if (<a href="ident?i=before">before</a>(end_seq, <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(skb1)-&gt;end_seq)) {
<a name="L4400" href="source/net/ipv4/tcp_input.c#L4400">4400</a>                         <a href="ident?i=tcp_dsack_extend">tcp_dsack_extend</a>(sk, <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(skb1)-&gt;<a href="ident?i=seq">seq</a>,
<a name="L4401" href="source/net/ipv4/tcp_input.c#L4401">4401</a>                                          end_seq);
<a name="L4402" href="source/net/ipv4/tcp_input.c#L4402">4402</a>                         break;
<a name="L4403" href="source/net/ipv4/tcp_input.c#L4403">4403</a>                 }
<a name="L4404" href="source/net/ipv4/tcp_input.c#L4404">4404</a>                 <a href="ident?i=__skb_unlink">__skb_unlink</a>(skb1, &amp;<a href="ident?i=tp">tp</a>-&gt;out_of_order_queue);
<a name="L4405" href="source/net/ipv4/tcp_input.c#L4405">4405</a>                 <a href="ident?i=tcp_dsack_extend">tcp_dsack_extend</a>(sk, <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(skb1)-&gt;<a href="ident?i=seq">seq</a>,
<a name="L4406" href="source/net/ipv4/tcp_input.c#L4406">4406</a>                                  <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(skb1)-&gt;end_seq);
<a name="L4407" href="source/net/ipv4/tcp_input.c#L4407">4407</a>                 <a href="ident?i=NET_INC_STATS_BH">NET_INC_STATS_BH</a>(<a href="ident?i=sock_net">sock_net</a>(sk), LINUX_MIB_TCPOFOMERGE);
<a name="L4408" href="source/net/ipv4/tcp_input.c#L4408">4408</a>                 <a href="ident?i=__kfree_skb">__kfree_skb</a>(skb1);
<a name="L4409" href="source/net/ipv4/tcp_input.c#L4409">4409</a>         }
<a name="L4410" href="source/net/ipv4/tcp_input.c#L4410">4410</a> 
<a name="L4411" href="source/net/ipv4/tcp_input.c#L4411">4411</a> add_sack:
<a name="L4412" href="source/net/ipv4/tcp_input.c#L4412">4412</a>         if (<a href="ident?i=tcp_is_sack">tcp_is_sack</a>(<a href="ident?i=tp">tp</a>))
<a name="L4413" href="source/net/ipv4/tcp_input.c#L4413">4413</a>                 <a href="ident?i=tcp_sack_new_ofo_skb">tcp_sack_new_ofo_skb</a>(sk, <a href="ident?i=seq">seq</a>, end_seq);
<a name="L4414" href="source/net/ipv4/tcp_input.c#L4414">4414</a> <a href="ident?i=end">end</a>:
<a name="L4415" href="source/net/ipv4/tcp_input.c#L4415">4415</a>         if (<a href="ident?i=skb">skb</a>) {
<a name="L4416" href="source/net/ipv4/tcp_input.c#L4416">4416</a>                 <a href="ident?i=tcp_grow_window">tcp_grow_window</a>(sk, <a href="ident?i=skb">skb</a>);
<a name="L4417" href="source/net/ipv4/tcp_input.c#L4417">4417</a>                 <a href="ident?i=skb_set_owner_r">skb_set_owner_r</a>(<a href="ident?i=skb">skb</a>, sk);
<a name="L4418" href="source/net/ipv4/tcp_input.c#L4418">4418</a>         }
<a name="L4419" href="source/net/ipv4/tcp_input.c#L4419">4419</a> }
<a name="L4420" href="source/net/ipv4/tcp_input.c#L4420">4420</a> 
<a name="L4421" href="source/net/ipv4/tcp_input.c#L4421">4421</a> static int <a href="ident?i=__must_check">__must_check</a> <a href="ident?i=tcp_queue_rcv">tcp_queue_rcv</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, int hdrlen,
<a name="L4422" href="source/net/ipv4/tcp_input.c#L4422">4422</a>                   <a href="ident?i=bool">bool</a> *fragstolen)
<a name="L4423" href="source/net/ipv4/tcp_input.c#L4423">4423</a> {
<a name="L4424" href="source/net/ipv4/tcp_input.c#L4424">4424</a>         int eaten;
<a name="L4425" href="source/net/ipv4/tcp_input.c#L4425">4425</a>         struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=tail">tail</a> = <a href="ident?i=skb_peek_tail">skb_peek_tail</a>(&amp;sk-&gt;sk_receive_queue);
<a name="L4426" href="source/net/ipv4/tcp_input.c#L4426">4426</a> 
<a name="L4427" href="source/net/ipv4/tcp_input.c#L4427">4427</a>         <a href="ident?i=__skb_pull">__skb_pull</a>(<a href="ident?i=skb">skb</a>, hdrlen);
<a name="L4428" href="source/net/ipv4/tcp_input.c#L4428">4428</a>         eaten = (<a href="ident?i=tail">tail</a> &amp;&amp;
<a name="L4429" href="source/net/ipv4/tcp_input.c#L4429">4429</a>                  <a href="ident?i=tcp_try_coalesce">tcp_try_coalesce</a>(sk, <a href="ident?i=tail">tail</a>, <a href="ident?i=skb">skb</a>, fragstolen)) ? 1 : 0;
<a name="L4430" href="source/net/ipv4/tcp_input.c#L4430">4430</a>         <a href="ident?i=tcp_rcv_nxt_update">tcp_rcv_nxt_update</a>(<a href="ident?i=tcp_sk">tcp_sk</a>(sk), <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;end_seq);
<a name="L4431" href="source/net/ipv4/tcp_input.c#L4431">4431</a>         if (!eaten) {
<a name="L4432" href="source/net/ipv4/tcp_input.c#L4432">4432</a>                 <a href="ident?i=__skb_queue_tail">__skb_queue_tail</a>(&amp;sk-&gt;sk_receive_queue, <a href="ident?i=skb">skb</a>);
<a name="L4433" href="source/net/ipv4/tcp_input.c#L4433">4433</a>                 <a href="ident?i=skb_set_owner_r">skb_set_owner_r</a>(<a href="ident?i=skb">skb</a>, sk);
<a name="L4434" href="source/net/ipv4/tcp_input.c#L4434">4434</a>         }
<a name="L4435" href="source/net/ipv4/tcp_input.c#L4435">4435</a>         return eaten;
<a name="L4436" href="source/net/ipv4/tcp_input.c#L4436">4436</a> }
<a name="L4437" href="source/net/ipv4/tcp_input.c#L4437">4437</a> 
<a name="L4438" href="source/net/ipv4/tcp_input.c#L4438">4438</a> int <a href="ident?i=tcp_send_rcvq">tcp_send_rcvq</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=msghdr">msghdr</a> *<a href="ident?i=msg">msg</a>, <a href="ident?i=size_t">size_t</a> <a href="ident?i=size">size</a>)
<a name="L4439" href="source/net/ipv4/tcp_input.c#L4439">4439</a> {
<a name="L4440" href="source/net/ipv4/tcp_input.c#L4440">4440</a>         struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>;
<a name="L4441" href="source/net/ipv4/tcp_input.c#L4441">4441</a>         <a href="ident?i=bool">bool</a> fragstolen;
<a name="L4442" href="source/net/ipv4/tcp_input.c#L4442">4442</a> 
<a name="L4443" href="source/net/ipv4/tcp_input.c#L4443">4443</a>         if (<a href="ident?i=size">size</a> == 0)
<a name="L4444" href="source/net/ipv4/tcp_input.c#L4444">4444</a>                 return 0;
<a name="L4445" href="source/net/ipv4/tcp_input.c#L4445">4445</a> 
<a name="L4446" href="source/net/ipv4/tcp_input.c#L4446">4446</a>         <a href="ident?i=skb">skb</a> = <a href="ident?i=alloc_skb">alloc_skb</a>(<a href="ident?i=size">size</a>, sk-&gt;sk_allocation);
<a name="L4447" href="source/net/ipv4/tcp_input.c#L4447">4447</a>         if (!<a href="ident?i=skb">skb</a>)
<a name="L4448" href="source/net/ipv4/tcp_input.c#L4448">4448</a>                 goto <a href="ident?i=err">err</a>;
<a name="L4449" href="source/net/ipv4/tcp_input.c#L4449">4449</a> 
<a name="L4450" href="source/net/ipv4/tcp_input.c#L4450">4450</a>         if (<a href="ident?i=tcp_try_rmem_schedule">tcp_try_rmem_schedule</a>(sk, <a href="ident?i=skb">skb</a>, <a href="ident?i=skb">skb</a>-&gt;truesize))
<a name="L4451" href="source/net/ipv4/tcp_input.c#L4451">4451</a>                 goto err_free;
<a name="L4452" href="source/net/ipv4/tcp_input.c#L4452">4452</a> 
<a name="L4453" href="source/net/ipv4/tcp_input.c#L4453">4453</a>         if (<a href="ident?i=memcpy_from_msg">memcpy_from_msg</a>(<a href="ident?i=skb_put">skb_put</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=size">size</a>), <a href="ident?i=msg">msg</a>, <a href="ident?i=size">size</a>))
<a name="L4454" href="source/net/ipv4/tcp_input.c#L4454">4454</a>                 goto err_free;
<a name="L4455" href="source/net/ipv4/tcp_input.c#L4455">4455</a> 
<a name="L4456" href="source/net/ipv4/tcp_input.c#L4456">4456</a>         <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=seq">seq</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk)-&gt;rcv_nxt;
<a name="L4457" href="source/net/ipv4/tcp_input.c#L4457">4457</a>         <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;end_seq = <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=seq">seq</a> + <a href="ident?i=size">size</a>;
<a name="L4458" href="source/net/ipv4/tcp_input.c#L4458">4458</a>         <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;ack_seq = <a href="ident?i=tcp_sk">tcp_sk</a>(sk)-&gt;snd_una - 1;
<a name="L4459" href="source/net/ipv4/tcp_input.c#L4459">4459</a> 
<a name="L4460" href="source/net/ipv4/tcp_input.c#L4460">4460</a>         if (<a href="ident?i=tcp_queue_rcv">tcp_queue_rcv</a>(sk, <a href="ident?i=skb">skb</a>, 0, &amp;fragstolen)) {
<a name="L4461" href="source/net/ipv4/tcp_input.c#L4461">4461</a>                 <a href="ident?i=WARN_ON_ONCE">WARN_ON_ONCE</a>(fragstolen); <b><i>/* should not happen */</i></b>
<a name="L4462" href="source/net/ipv4/tcp_input.c#L4462">4462</a>                 <a href="ident?i=__kfree_skb">__kfree_skb</a>(<a href="ident?i=skb">skb</a>);
<a name="L4463" href="source/net/ipv4/tcp_input.c#L4463">4463</a>         }
<a name="L4464" href="source/net/ipv4/tcp_input.c#L4464">4464</a>         return <a href="ident?i=size">size</a>;
<a name="L4465" href="source/net/ipv4/tcp_input.c#L4465">4465</a> 
<a name="L4466" href="source/net/ipv4/tcp_input.c#L4466">4466</a> err_free:
<a name="L4467" href="source/net/ipv4/tcp_input.c#L4467">4467</a>         <a href="ident?i=kfree_skb">kfree_skb</a>(<a href="ident?i=skb">skb</a>);
<a name="L4468" href="source/net/ipv4/tcp_input.c#L4468">4468</a> <a href="ident?i=err">err</a>:
<a name="L4469" href="source/net/ipv4/tcp_input.c#L4469">4469</a>         return -<a href="ident?i=ENOMEM">ENOMEM</a>;
<a name="L4470" href="source/net/ipv4/tcp_input.c#L4470">4470</a> }
<a name="L4471" href="source/net/ipv4/tcp_input.c#L4471">4471</a> 
<a name="L4472" href="source/net/ipv4/tcp_input.c#L4472">4472</a> static void <a href="ident?i=tcp_data_queue">tcp_data_queue</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L4473" href="source/net/ipv4/tcp_input.c#L4473">4473</a> {
<a name="L4474" href="source/net/ipv4/tcp_input.c#L4474">4474</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L4475" href="source/net/ipv4/tcp_input.c#L4475">4475</a>         int eaten = -1;
<a name="L4476" href="source/net/ipv4/tcp_input.c#L4476">4476</a>         <a href="ident?i=bool">bool</a> fragstolen = <a href="ident?i=false">false</a>;
<a name="L4477" href="source/net/ipv4/tcp_input.c#L4477">4477</a> 
<a name="L4478" href="source/net/ipv4/tcp_input.c#L4478">4478</a>         if (<a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=seq">seq</a> == <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;end_seq)
<a name="L4479" href="source/net/ipv4/tcp_input.c#L4479">4479</a>                 goto <a href="ident?i=drop">drop</a>;
<a name="L4480" href="source/net/ipv4/tcp_input.c#L4480">4480</a> 
<a name="L4481" href="source/net/ipv4/tcp_input.c#L4481">4481</a>         <a href="ident?i=skb_dst_drop">skb_dst_drop</a>(<a href="ident?i=skb">skb</a>);
<a name="L4482" href="source/net/ipv4/tcp_input.c#L4482">4482</a>         <a href="ident?i=__skb_pull">__skb_pull</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=tcp_hdr">tcp_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;doff * 4);
<a name="L4483" href="source/net/ipv4/tcp_input.c#L4483">4483</a> 
<a name="L4484" href="source/net/ipv4/tcp_input.c#L4484">4484</a>         <a href="ident?i=tcp_ecn_accept_cwr">tcp_ecn_accept_cwr</a>(<a href="ident?i=tp">tp</a>, <a href="ident?i=skb">skb</a>);
<a name="L4485" href="source/net/ipv4/tcp_input.c#L4485">4485</a> 
<a name="L4486" href="source/net/ipv4/tcp_input.c#L4486">4486</a>         <a href="ident?i=tp">tp</a>-&gt;rx_opt.dsack = 0;
<a name="L4487" href="source/net/ipv4/tcp_input.c#L4487">4487</a> 
<a name="L4488" href="source/net/ipv4/tcp_input.c#L4488">4488</a>         <b><i>/*  Queue data for delivery to the user.</i></b>
<a name="L4489" href="source/net/ipv4/tcp_input.c#L4489">4489</a> <b><i>         *  Packets in sequence go to the receive queue.</i></b>
<a name="L4490" href="source/net/ipv4/tcp_input.c#L4490">4490</a> <b><i>         *  Out of sequence packets to the out_of_order_queue.</i></b>
<a name="L4491" href="source/net/ipv4/tcp_input.c#L4491">4491</a> <b><i>         */</i></b>
<a name="L4492" href="source/net/ipv4/tcp_input.c#L4492">4492</a>         if (<a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=seq">seq</a> == <a href="ident?i=tp">tp</a>-&gt;rcv_nxt) {
<a name="L4493" href="source/net/ipv4/tcp_input.c#L4493">4493</a>                 if (<a href="ident?i=tcp_receive_window">tcp_receive_window</a>(<a href="ident?i=tp">tp</a>) == 0)
<a name="L4494" href="source/net/ipv4/tcp_input.c#L4494">4494</a>                         goto out_of_window;
<a name="L4495" href="source/net/ipv4/tcp_input.c#L4495">4495</a> 
<a name="L4496" href="source/net/ipv4/tcp_input.c#L4496">4496</a>                 <b><i>/* Ok. In sequence. In window. */</i></b>
<a name="L4497" href="source/net/ipv4/tcp_input.c#L4497">4497</a>                 if (<a href="ident?i=tp">tp</a>-&gt;ucopy.<a href="ident?i=task">task</a> == <a href="ident?i=current">current</a> &amp;&amp;
<a name="L4498" href="source/net/ipv4/tcp_input.c#L4498">4498</a>                     <a href="ident?i=tp">tp</a>-&gt;copied_seq == <a href="ident?i=tp">tp</a>-&gt;rcv_nxt &amp;&amp; <a href="ident?i=tp">tp</a>-&gt;ucopy.<a href="ident?i=len">len</a> &amp;&amp;
<a name="L4499" href="source/net/ipv4/tcp_input.c#L4499">4499</a>                     <a href="ident?i=sock_owned_by_user">sock_owned_by_user</a>(sk) &amp;&amp; !<a href="ident?i=tp">tp</a>-&gt;urg_data) {
<a name="L4500" href="source/net/ipv4/tcp_input.c#L4500">4500</a>                         int <a href="ident?i=chunk">chunk</a> = <a href="ident?i=min_t">min_t</a>(unsigned int, <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a>,
<a name="L4501" href="source/net/ipv4/tcp_input.c#L4501">4501</a>                                           <a href="ident?i=tp">tp</a>-&gt;ucopy.<a href="ident?i=len">len</a>);
<a name="L4502" href="source/net/ipv4/tcp_input.c#L4502">4502</a> 
<a name="L4503" href="source/net/ipv4/tcp_input.c#L4503">4503</a>                         <a href="ident?i=__set_current_state">__set_current_state</a>(<a href="ident?i=TASK_RUNNING">TASK_RUNNING</a>);
<a name="L4504" href="source/net/ipv4/tcp_input.c#L4504">4504</a> 
<a name="L4505" href="source/net/ipv4/tcp_input.c#L4505">4505</a>                         <a href="ident?i=local_bh_enable">local_bh_enable</a>();
<a name="L4506" href="source/net/ipv4/tcp_input.c#L4506">4506</a>                         if (!<a href="ident?i=skb_copy_datagram_msg">skb_copy_datagram_msg</a>(<a href="ident?i=skb">skb</a>, 0, <a href="ident?i=tp">tp</a>-&gt;ucopy.<a href="ident?i=msg">msg</a>, <a href="ident?i=chunk">chunk</a>)) {
<a name="L4507" href="source/net/ipv4/tcp_input.c#L4507">4507</a>                                 <a href="ident?i=tp">tp</a>-&gt;ucopy.<a href="ident?i=len">len</a> -= <a href="ident?i=chunk">chunk</a>;
<a name="L4508" href="source/net/ipv4/tcp_input.c#L4508">4508</a>                                 <a href="ident?i=tp">tp</a>-&gt;copied_seq += <a href="ident?i=chunk">chunk</a>;
<a name="L4509" href="source/net/ipv4/tcp_input.c#L4509">4509</a>                                 eaten = (<a href="ident?i=chunk">chunk</a> == <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a>);
<a name="L4510" href="source/net/ipv4/tcp_input.c#L4510">4510</a>                                 <a href="ident?i=tcp_rcv_space_adjust">tcp_rcv_space_adjust</a>(sk);
<a name="L4511" href="source/net/ipv4/tcp_input.c#L4511">4511</a>                         }
<a name="L4512" href="source/net/ipv4/tcp_input.c#L4512">4512</a>                         <a href="ident?i=local_bh_disable">local_bh_disable</a>();
<a name="L4513" href="source/net/ipv4/tcp_input.c#L4513">4513</a>                 }
<a name="L4514" href="source/net/ipv4/tcp_input.c#L4514">4514</a> 
<a name="L4515" href="source/net/ipv4/tcp_input.c#L4515">4515</a>                 if (eaten &lt;= 0) {
<a name="L4516" href="source/net/ipv4/tcp_input.c#L4516">4516</a> queue_and_out:
<a name="L4517" href="source/net/ipv4/tcp_input.c#L4517">4517</a>                         if (eaten &lt; 0 &amp;&amp;
<a name="L4518" href="source/net/ipv4/tcp_input.c#L4518">4518</a>                             <a href="ident?i=tcp_try_rmem_schedule">tcp_try_rmem_schedule</a>(sk, <a href="ident?i=skb">skb</a>, <a href="ident?i=skb">skb</a>-&gt;truesize))
<a name="L4519" href="source/net/ipv4/tcp_input.c#L4519">4519</a>                                 goto <a href="ident?i=drop">drop</a>;
<a name="L4520" href="source/net/ipv4/tcp_input.c#L4520">4520</a> 
<a name="L4521" href="source/net/ipv4/tcp_input.c#L4521">4521</a>                         eaten = <a href="ident?i=tcp_queue_rcv">tcp_queue_rcv</a>(sk, <a href="ident?i=skb">skb</a>, 0, &amp;fragstolen);
<a name="L4522" href="source/net/ipv4/tcp_input.c#L4522">4522</a>                 }
<a name="L4523" href="source/net/ipv4/tcp_input.c#L4523">4523</a>                 <a href="ident?i=tcp_rcv_nxt_update">tcp_rcv_nxt_update</a>(<a href="ident?i=tp">tp</a>, <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;end_seq);
<a name="L4524" href="source/net/ipv4/tcp_input.c#L4524">4524</a>                 if (<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a>)
<a name="L4525" href="source/net/ipv4/tcp_input.c#L4525">4525</a>                         <a href="ident?i=tcp_event_data_recv">tcp_event_data_recv</a>(sk, <a href="ident?i=skb">skb</a>);
<a name="L4526" href="source/net/ipv4/tcp_input.c#L4526">4526</a>                 if (<a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;tcp_flags &amp; <a href="ident?i=TCPHDR_FIN">TCPHDR_FIN</a>)
<a name="L4527" href="source/net/ipv4/tcp_input.c#L4527">4527</a>                         <a href="ident?i=tcp_fin">tcp_fin</a>(sk);
<a name="L4528" href="source/net/ipv4/tcp_input.c#L4528">4528</a> 
<a name="L4529" href="source/net/ipv4/tcp_input.c#L4529">4529</a>                 if (!<a href="ident?i=skb_queue_empty">skb_queue_empty</a>(&amp;<a href="ident?i=tp">tp</a>-&gt;out_of_order_queue)) {
<a name="L4530" href="source/net/ipv4/tcp_input.c#L4530">4530</a>                         <a href="ident?i=tcp_ofo_queue">tcp_ofo_queue</a>(sk);
<a name="L4531" href="source/net/ipv4/tcp_input.c#L4531">4531</a> 
<a name="L4532" href="source/net/ipv4/tcp_input.c#L4532">4532</a>                         <b><i>/* RFC2581. 4.2. SHOULD send immediate ACK, when</i></b>
<a name="L4533" href="source/net/ipv4/tcp_input.c#L4533">4533</a> <b><i>                         * gap in queue is filled.</i></b>
<a name="L4534" href="source/net/ipv4/tcp_input.c#L4534">4534</a> <b><i>                         */</i></b>
<a name="L4535" href="source/net/ipv4/tcp_input.c#L4535">4535</a>                         if (<a href="ident?i=skb_queue_empty">skb_queue_empty</a>(&amp;<a href="ident?i=tp">tp</a>-&gt;out_of_order_queue))
<a name="L4536" href="source/net/ipv4/tcp_input.c#L4536">4536</a>                                 <a href="ident?i=inet_csk">inet_csk</a>(sk)-&gt;icsk_ack.pingpong = 0;
<a name="L4537" href="source/net/ipv4/tcp_input.c#L4537">4537</a>                 }
<a name="L4538" href="source/net/ipv4/tcp_input.c#L4538">4538</a> 
<a name="L4539" href="source/net/ipv4/tcp_input.c#L4539">4539</a>                 if (<a href="ident?i=tp">tp</a>-&gt;rx_opt.num_sacks)
<a name="L4540" href="source/net/ipv4/tcp_input.c#L4540">4540</a>                         <a href="ident?i=tcp_sack_remove">tcp_sack_remove</a>(<a href="ident?i=tp">tp</a>);
<a name="L4541" href="source/net/ipv4/tcp_input.c#L4541">4541</a> 
<a name="L4542" href="source/net/ipv4/tcp_input.c#L4542">4542</a>                 <a href="ident?i=tcp_fast_path_check">tcp_fast_path_check</a>(sk);
<a name="L4543" href="source/net/ipv4/tcp_input.c#L4543">4543</a> 
<a name="L4544" href="source/net/ipv4/tcp_input.c#L4544">4544</a>                 if (eaten &gt; 0)
<a name="L4545" href="source/net/ipv4/tcp_input.c#L4545">4545</a>                         <a href="ident?i=kfree_skb_partial">kfree_skb_partial</a>(<a href="ident?i=skb">skb</a>, fragstolen);
<a name="L4546" href="source/net/ipv4/tcp_input.c#L4546">4546</a>                 if (!<a href="ident?i=sock_flag">sock_flag</a>(sk, SOCK_DEAD))
<a name="L4547" href="source/net/ipv4/tcp_input.c#L4547">4547</a>                         sk-&gt;sk_data_ready(sk);
<a name="L4548" href="source/net/ipv4/tcp_input.c#L4548">4548</a>                 return;
<a name="L4549" href="source/net/ipv4/tcp_input.c#L4549">4549</a>         }
<a name="L4550" href="source/net/ipv4/tcp_input.c#L4550">4550</a> 
<a name="L4551" href="source/net/ipv4/tcp_input.c#L4551">4551</a>         if (!<a href="ident?i=after">after</a>(<a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;end_seq, <a href="ident?i=tp">tp</a>-&gt;rcv_nxt)) {
<a name="L4552" href="source/net/ipv4/tcp_input.c#L4552">4552</a>                 <b><i>/* A retransmit, 2nd most common case.  Force an immediate ack. */</i></b>
<a name="L4553" href="source/net/ipv4/tcp_input.c#L4553">4553</a>                 <a href="ident?i=NET_INC_STATS_BH">NET_INC_STATS_BH</a>(<a href="ident?i=sock_net">sock_net</a>(sk), LINUX_MIB_DELAYEDACKLOST);
<a name="L4554" href="source/net/ipv4/tcp_input.c#L4554">4554</a>                 <a href="ident?i=tcp_dsack_set">tcp_dsack_set</a>(sk, <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=seq">seq</a>, <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;end_seq);
<a name="L4555" href="source/net/ipv4/tcp_input.c#L4555">4555</a> 
<a name="L4556" href="source/net/ipv4/tcp_input.c#L4556">4556</a> out_of_window:
<a name="L4557" href="source/net/ipv4/tcp_input.c#L4557">4557</a>                 <a href="ident?i=tcp_enter_quickack_mode">tcp_enter_quickack_mode</a>(sk);
<a name="L4558" href="source/net/ipv4/tcp_input.c#L4558">4558</a>                 <a href="ident?i=inet_csk_schedule_ack">inet_csk_schedule_ack</a>(sk);
<a name="L4559" href="source/net/ipv4/tcp_input.c#L4559">4559</a> <a href="ident?i=drop">drop</a>:
<a name="L4560" href="source/net/ipv4/tcp_input.c#L4560">4560</a>                 <a href="ident?i=__kfree_skb">__kfree_skb</a>(<a href="ident?i=skb">skb</a>);
<a name="L4561" href="source/net/ipv4/tcp_input.c#L4561">4561</a>                 return;
<a name="L4562" href="source/net/ipv4/tcp_input.c#L4562">4562</a>         }
<a name="L4563" href="source/net/ipv4/tcp_input.c#L4563">4563</a> 
<a name="L4564" href="source/net/ipv4/tcp_input.c#L4564">4564</a>         <b><i>/* Out of window. F.e. zero window probe. */</i></b>
<a name="L4565" href="source/net/ipv4/tcp_input.c#L4565">4565</a>         if (!<a href="ident?i=before">before</a>(<a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=seq">seq</a>, <a href="ident?i=tp">tp</a>-&gt;rcv_nxt + <a href="ident?i=tcp_receive_window">tcp_receive_window</a>(<a href="ident?i=tp">tp</a>)))
<a name="L4566" href="source/net/ipv4/tcp_input.c#L4566">4566</a>                 goto out_of_window;
<a name="L4567" href="source/net/ipv4/tcp_input.c#L4567">4567</a> 
<a name="L4568" href="source/net/ipv4/tcp_input.c#L4568">4568</a>         <a href="ident?i=tcp_enter_quickack_mode">tcp_enter_quickack_mode</a>(sk);
<a name="L4569" href="source/net/ipv4/tcp_input.c#L4569">4569</a> 
<a name="L4570" href="source/net/ipv4/tcp_input.c#L4570">4570</a>         if (<a href="ident?i=before">before</a>(<a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=seq">seq</a>, <a href="ident?i=tp">tp</a>-&gt;rcv_nxt)) {
<a name="L4571" href="source/net/ipv4/tcp_input.c#L4571">4571</a>                 <b><i>/* Partial packet, seq &lt; rcv_next &lt; end_seq */</i></b>
<a name="L4572" href="source/net/ipv4/tcp_input.c#L4572">4572</a>                 <a href="ident?i=SOCK_DEBUG">SOCK_DEBUG</a>(sk, <i>"partial packet: rcv_next %X seq %X - %X\n"</i>,
<a name="L4573" href="source/net/ipv4/tcp_input.c#L4573">4573</a>                            <a href="ident?i=tp">tp</a>-&gt;rcv_nxt, <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=seq">seq</a>,
<a name="L4574" href="source/net/ipv4/tcp_input.c#L4574">4574</a>                            <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;end_seq);
<a name="L4575" href="source/net/ipv4/tcp_input.c#L4575">4575</a> 
<a name="L4576" href="source/net/ipv4/tcp_input.c#L4576">4576</a>                 <a href="ident?i=tcp_dsack_set">tcp_dsack_set</a>(sk, <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=seq">seq</a>, <a href="ident?i=tp">tp</a>-&gt;rcv_nxt);
<a name="L4577" href="source/net/ipv4/tcp_input.c#L4577">4577</a> 
<a name="L4578" href="source/net/ipv4/tcp_input.c#L4578">4578</a>                 <b><i>/* If window is closed, drop tail of packet. But after</i></b>
<a name="L4579" href="source/net/ipv4/tcp_input.c#L4579">4579</a> <b><i>                 * remembering D-SACK for its head made in previous line.</i></b>
<a name="L4580" href="source/net/ipv4/tcp_input.c#L4580">4580</a> <b><i>                 */</i></b>
<a name="L4581" href="source/net/ipv4/tcp_input.c#L4581">4581</a>                 if (!<a href="ident?i=tcp_receive_window">tcp_receive_window</a>(<a href="ident?i=tp">tp</a>))
<a name="L4582" href="source/net/ipv4/tcp_input.c#L4582">4582</a>                         goto out_of_window;
<a name="L4583" href="source/net/ipv4/tcp_input.c#L4583">4583</a>                 goto queue_and_out;
<a name="L4584" href="source/net/ipv4/tcp_input.c#L4584">4584</a>         }
<a name="L4585" href="source/net/ipv4/tcp_input.c#L4585">4585</a> 
<a name="L4586" href="source/net/ipv4/tcp_input.c#L4586">4586</a>         <a href="ident?i=tcp_data_queue_ofo">tcp_data_queue_ofo</a>(sk, <a href="ident?i=skb">skb</a>);
<a name="L4587" href="source/net/ipv4/tcp_input.c#L4587">4587</a> }
<a name="L4588" href="source/net/ipv4/tcp_input.c#L4588">4588</a> 
<a name="L4589" href="source/net/ipv4/tcp_input.c#L4589">4589</a> static struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=tcp_collapse_one">tcp_collapse_one</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
<a name="L4590" href="source/net/ipv4/tcp_input.c#L4590">4590</a>                                         struct <a href="ident?i=sk_buff_head">sk_buff_head</a> *<a href="ident?i=list">list</a>)
<a name="L4591" href="source/net/ipv4/tcp_input.c#L4591">4591</a> {
<a name="L4592" href="source/net/ipv4/tcp_input.c#L4592">4592</a>         struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=next">next</a> = <a href="ident?i=NULL">NULL</a>;
<a name="L4593" href="source/net/ipv4/tcp_input.c#L4593">4593</a> 
<a name="L4594" href="source/net/ipv4/tcp_input.c#L4594">4594</a>         if (!<a href="ident?i=skb_queue_is_last">skb_queue_is_last</a>(<a href="ident?i=list">list</a>, <a href="ident?i=skb">skb</a>))
<a name="L4595" href="source/net/ipv4/tcp_input.c#L4595">4595</a>                 <a href="ident?i=next">next</a> = <a href="ident?i=skb_queue_next">skb_queue_next</a>(<a href="ident?i=list">list</a>, <a href="ident?i=skb">skb</a>);
<a name="L4596" href="source/net/ipv4/tcp_input.c#L4596">4596</a> 
<a name="L4597" href="source/net/ipv4/tcp_input.c#L4597">4597</a>         <a href="ident?i=__skb_unlink">__skb_unlink</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=list">list</a>);
<a name="L4598" href="source/net/ipv4/tcp_input.c#L4598">4598</a>         <a href="ident?i=__kfree_skb">__kfree_skb</a>(<a href="ident?i=skb">skb</a>);
<a name="L4599" href="source/net/ipv4/tcp_input.c#L4599">4599</a>         <a href="ident?i=NET_INC_STATS_BH">NET_INC_STATS_BH</a>(<a href="ident?i=sock_net">sock_net</a>(sk), LINUX_MIB_TCPRCVCOLLAPSED);
<a name="L4600" href="source/net/ipv4/tcp_input.c#L4600">4600</a> 
<a name="L4601" href="source/net/ipv4/tcp_input.c#L4601">4601</a>         return <a href="ident?i=next">next</a>;
<a name="L4602" href="source/net/ipv4/tcp_input.c#L4602">4602</a> }
<a name="L4603" href="source/net/ipv4/tcp_input.c#L4603">4603</a> 
<a name="L4604" href="source/net/ipv4/tcp_input.c#L4604">4604</a> <b><i>/* Collapse contiguous sequence of skbs head..tail with</i></b>
<a name="L4605" href="source/net/ipv4/tcp_input.c#L4605">4605</a> <b><i> * sequence numbers start..end.</i></b>
<a name="L4606" href="source/net/ipv4/tcp_input.c#L4606">4606</a> <b><i> *</i></b>
<a name="L4607" href="source/net/ipv4/tcp_input.c#L4607">4607</a> <b><i> * If tail is NULL, this means until the end of the list.</i></b>
<a name="L4608" href="source/net/ipv4/tcp_input.c#L4608">4608</a> <b><i> *</i></b>
<a name="L4609" href="source/net/ipv4/tcp_input.c#L4609">4609</a> <b><i> * Segments with FIN/SYN are not collapsed (only because this</i></b>
<a name="L4610" href="source/net/ipv4/tcp_input.c#L4610">4610</a> <b><i> * simplifies code)</i></b>
<a name="L4611" href="source/net/ipv4/tcp_input.c#L4611">4611</a> <b><i> */</i></b>
<a name="L4612" href="source/net/ipv4/tcp_input.c#L4612">4612</a> static void
<a name="L4613" href="source/net/ipv4/tcp_input.c#L4613">4613</a> <a href="ident?i=tcp_collapse">tcp_collapse</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=sk_buff_head">sk_buff_head</a> *<a href="ident?i=list">list</a>,
<a name="L4614" href="source/net/ipv4/tcp_input.c#L4614">4614</a>              struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=head">head</a>, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=tail">tail</a>,
<a name="L4615" href="source/net/ipv4/tcp_input.c#L4615">4615</a>              <a href="ident?i=u32">u32</a> <a href="ident?i=start">start</a>, <a href="ident?i=u32">u32</a> <a href="ident?i=end">end</a>)
<a name="L4616" href="source/net/ipv4/tcp_input.c#L4616">4616</a> {
<a name="L4617" href="source/net/ipv4/tcp_input.c#L4617">4617</a>         struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, *<a href="ident?i=n">n</a>;
<a name="L4618" href="source/net/ipv4/tcp_input.c#L4618">4618</a>         <a href="ident?i=bool">bool</a> end_of_skbs;
<a name="L4619" href="source/net/ipv4/tcp_input.c#L4619">4619</a> 
<a name="L4620" href="source/net/ipv4/tcp_input.c#L4620">4620</a>         <b><i>/* First, check that queue is collapsible and find</i></b>
<a name="L4621" href="source/net/ipv4/tcp_input.c#L4621">4621</a> <b><i>         * the point where collapsing can be useful. */</i></b>
<a name="L4622" href="source/net/ipv4/tcp_input.c#L4622">4622</a>         <a href="ident?i=skb">skb</a> = <a href="ident?i=head">head</a>;
<a name="L4623" href="source/net/ipv4/tcp_input.c#L4623">4623</a> <a href="ident?i=restart">restart</a>:
<a name="L4624" href="source/net/ipv4/tcp_input.c#L4624">4624</a>         end_of_skbs = <a href="ident?i=true">true</a>;
<a name="L4625" href="source/net/ipv4/tcp_input.c#L4625">4625</a>         <a href="ident?i=skb_queue_walk_from_safe">skb_queue_walk_from_safe</a>(<a href="ident?i=list">list</a>, <a href="ident?i=skb">skb</a>, <a href="ident?i=n">n</a>) {
<a name="L4626" href="source/net/ipv4/tcp_input.c#L4626">4626</a>                 if (<a href="ident?i=skb">skb</a> == <a href="ident?i=tail">tail</a>)
<a name="L4627" href="source/net/ipv4/tcp_input.c#L4627">4627</a>                         break;
<a name="L4628" href="source/net/ipv4/tcp_input.c#L4628">4628</a>                 <b><i>/* No new bits? It is possible on ofo queue. */</i></b>
<a name="L4629" href="source/net/ipv4/tcp_input.c#L4629">4629</a>                 if (!<a href="ident?i=before">before</a>(<a href="ident?i=start">start</a>, <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;end_seq)) {
<a name="L4630" href="source/net/ipv4/tcp_input.c#L4630">4630</a>                         <a href="ident?i=skb">skb</a> = <a href="ident?i=tcp_collapse_one">tcp_collapse_one</a>(sk, <a href="ident?i=skb">skb</a>, <a href="ident?i=list">list</a>);
<a name="L4631" href="source/net/ipv4/tcp_input.c#L4631">4631</a>                         if (!<a href="ident?i=skb">skb</a>)
<a name="L4632" href="source/net/ipv4/tcp_input.c#L4632">4632</a>                                 break;
<a name="L4633" href="source/net/ipv4/tcp_input.c#L4633">4633</a>                         goto <a href="ident?i=restart">restart</a>;
<a name="L4634" href="source/net/ipv4/tcp_input.c#L4634">4634</a>                 }
<a name="L4635" href="source/net/ipv4/tcp_input.c#L4635">4635</a> 
<a name="L4636" href="source/net/ipv4/tcp_input.c#L4636">4636</a>                 <b><i>/* The first skb to collapse is:</i></b>
<a name="L4637" href="source/net/ipv4/tcp_input.c#L4637">4637</a> <b><i>                 * - not SYN/FIN and</i></b>
<a name="L4638" href="source/net/ipv4/tcp_input.c#L4638">4638</a> <b><i>                 * - bloated or contains data before "start" or</i></b>
<a name="L4639" href="source/net/ipv4/tcp_input.c#L4639">4639</a> <b><i>                 *   overlaps to the next one.</i></b>
<a name="L4640" href="source/net/ipv4/tcp_input.c#L4640">4640</a> <b><i>                 */</i></b>
<a name="L4641" href="source/net/ipv4/tcp_input.c#L4641">4641</a>                 if (!(<a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;tcp_flags &amp; (<a href="ident?i=TCPHDR_SYN">TCPHDR_SYN</a> | <a href="ident?i=TCPHDR_FIN">TCPHDR_FIN</a>)) &amp;&amp;
<a name="L4642" href="source/net/ipv4/tcp_input.c#L4642">4642</a>                     (<a href="ident?i=tcp_win_from_space">tcp_win_from_space</a>(<a href="ident?i=skb">skb</a>-&gt;truesize) &gt; <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a> ||
<a name="L4643" href="source/net/ipv4/tcp_input.c#L4643">4643</a>                      <a href="ident?i=before">before</a>(<a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=seq">seq</a>, <a href="ident?i=start">start</a>))) {
<a name="L4644" href="source/net/ipv4/tcp_input.c#L4644">4644</a>                         end_of_skbs = <a href="ident?i=false">false</a>;
<a name="L4645" href="source/net/ipv4/tcp_input.c#L4645">4645</a>                         break;
<a name="L4646" href="source/net/ipv4/tcp_input.c#L4646">4646</a>                 }
<a name="L4647" href="source/net/ipv4/tcp_input.c#L4647">4647</a> 
<a name="L4648" href="source/net/ipv4/tcp_input.c#L4648">4648</a>                 if (!<a href="ident?i=skb_queue_is_last">skb_queue_is_last</a>(<a href="ident?i=list">list</a>, <a href="ident?i=skb">skb</a>)) {
<a name="L4649" href="source/net/ipv4/tcp_input.c#L4649">4649</a>                         struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=next">next</a> = <a href="ident?i=skb_queue_next">skb_queue_next</a>(<a href="ident?i=list">list</a>, <a href="ident?i=skb">skb</a>);
<a name="L4650" href="source/net/ipv4/tcp_input.c#L4650">4650</a>                         if (<a href="ident?i=next">next</a> != <a href="ident?i=tail">tail</a> &amp;&amp;
<a name="L4651" href="source/net/ipv4/tcp_input.c#L4651">4651</a>                             <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;end_seq != <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=next">next</a>)-&gt;<a href="ident?i=seq">seq</a>) {
<a name="L4652" href="source/net/ipv4/tcp_input.c#L4652">4652</a>                                 end_of_skbs = <a href="ident?i=false">false</a>;
<a name="L4653" href="source/net/ipv4/tcp_input.c#L4653">4653</a>                                 break;
<a name="L4654" href="source/net/ipv4/tcp_input.c#L4654">4654</a>                         }
<a name="L4655" href="source/net/ipv4/tcp_input.c#L4655">4655</a>                 }
<a name="L4656" href="source/net/ipv4/tcp_input.c#L4656">4656</a> 
<a name="L4657" href="source/net/ipv4/tcp_input.c#L4657">4657</a>                 <b><i>/* Decided to skip this, advance start seq. */</i></b>
<a name="L4658" href="source/net/ipv4/tcp_input.c#L4658">4658</a>                 <a href="ident?i=start">start</a> = <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;end_seq;
<a name="L4659" href="source/net/ipv4/tcp_input.c#L4659">4659</a>         }
<a name="L4660" href="source/net/ipv4/tcp_input.c#L4660">4660</a>         if (end_of_skbs ||
<a name="L4661" href="source/net/ipv4/tcp_input.c#L4661">4661</a>             (<a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;tcp_flags &amp; (<a href="ident?i=TCPHDR_SYN">TCPHDR_SYN</a> | <a href="ident?i=TCPHDR_FIN">TCPHDR_FIN</a>)))
<a name="L4662" href="source/net/ipv4/tcp_input.c#L4662">4662</a>                 return;
<a name="L4663" href="source/net/ipv4/tcp_input.c#L4663">4663</a> 
<a name="L4664" href="source/net/ipv4/tcp_input.c#L4664">4664</a>         while (<a href="ident?i=before">before</a>(<a href="ident?i=start">start</a>, <a href="ident?i=end">end</a>)) {
<a name="L4665" href="source/net/ipv4/tcp_input.c#L4665">4665</a>                 int <a href="ident?i=copy">copy</a> = <a href="ident?i=min_t">min_t</a>(int, <a href="ident?i=SKB_MAX_ORDER">SKB_MAX_ORDER</a>(0, 0), <a href="ident?i=end">end</a> - <a href="ident?i=start">start</a>);
<a name="L4666" href="source/net/ipv4/tcp_input.c#L4666">4666</a>                 struct <a href="ident?i=sk_buff">sk_buff</a> *nskb;
<a name="L4667" href="source/net/ipv4/tcp_input.c#L4667">4667</a> 
<a name="L4668" href="source/net/ipv4/tcp_input.c#L4668">4668</a>                 nskb = <a href="ident?i=alloc_skb">alloc_skb</a>(<a href="ident?i=copy">copy</a>, <a href="ident?i=GFP_ATOMIC">GFP_ATOMIC</a>);
<a name="L4669" href="source/net/ipv4/tcp_input.c#L4669">4669</a>                 if (!nskb)
<a name="L4670" href="source/net/ipv4/tcp_input.c#L4670">4670</a>                         return;
<a name="L4671" href="source/net/ipv4/tcp_input.c#L4671">4671</a> 
<a name="L4672" href="source/net/ipv4/tcp_input.c#L4672">4672</a>                 <a href="ident?i=memcpy">memcpy</a>(nskb-&gt;<a href="ident?i=cb">cb</a>, <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=cb">cb</a>, sizeof(<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=cb">cb</a>));
<a name="L4673" href="source/net/ipv4/tcp_input.c#L4673">4673</a>                 <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(nskb)-&gt;<a href="ident?i=seq">seq</a> = <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(nskb)-&gt;end_seq = <a href="ident?i=start">start</a>;
<a name="L4674" href="source/net/ipv4/tcp_input.c#L4674">4674</a>                 <a href="ident?i=__skb_queue_before">__skb_queue_before</a>(<a href="ident?i=list">list</a>, <a href="ident?i=skb">skb</a>, nskb);
<a name="L4675" href="source/net/ipv4/tcp_input.c#L4675">4675</a>                 <a href="ident?i=skb_set_owner_r">skb_set_owner_r</a>(nskb, sk);
<a name="L4676" href="source/net/ipv4/tcp_input.c#L4676">4676</a> 
<a name="L4677" href="source/net/ipv4/tcp_input.c#L4677">4677</a>                 <b><i>/* Copy data, releasing collapsed skbs. */</i></b>
<a name="L4678" href="source/net/ipv4/tcp_input.c#L4678">4678</a>                 while (<a href="ident?i=copy">copy</a> &gt; 0) {
<a name="L4679" href="source/net/ipv4/tcp_input.c#L4679">4679</a>                         int <a href="ident?i=offset">offset</a> = <a href="ident?i=start">start</a> - <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=seq">seq</a>;
<a name="L4680" href="source/net/ipv4/tcp_input.c#L4680">4680</a>                         int <a href="ident?i=size">size</a> = <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;end_seq - <a href="ident?i=start">start</a>;
<a name="L4681" href="source/net/ipv4/tcp_input.c#L4681">4681</a> 
<a name="L4682" href="source/net/ipv4/tcp_input.c#L4682">4682</a>                         <a href="ident?i=BUG_ON">BUG_ON</a>(<a href="ident?i=offset">offset</a> &lt; 0);
<a name="L4683" href="source/net/ipv4/tcp_input.c#L4683">4683</a>                         if (<a href="ident?i=size">size</a> &gt; 0) {
<a name="L4684" href="source/net/ipv4/tcp_input.c#L4684">4684</a>                                 <a href="ident?i=size">size</a> = <a href="ident?i=min">min</a>(<a href="ident?i=copy">copy</a>, <a href="ident?i=size">size</a>);
<a name="L4685" href="source/net/ipv4/tcp_input.c#L4685">4685</a>                                 if (<a href="ident?i=skb_copy_bits">skb_copy_bits</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=offset">offset</a>, <a href="ident?i=skb_put">skb_put</a>(nskb, <a href="ident?i=size">size</a>), <a href="ident?i=size">size</a>))
<a name="L4686" href="source/net/ipv4/tcp_input.c#L4686">4686</a>                                         <a href="ident?i=BUG">BUG</a>();
<a name="L4687" href="source/net/ipv4/tcp_input.c#L4687">4687</a>                                 <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(nskb)-&gt;end_seq += <a href="ident?i=size">size</a>;
<a name="L4688" href="source/net/ipv4/tcp_input.c#L4688">4688</a>                                 <a href="ident?i=copy">copy</a> -= <a href="ident?i=size">size</a>;
<a name="L4689" href="source/net/ipv4/tcp_input.c#L4689">4689</a>                                 <a href="ident?i=start">start</a> += <a href="ident?i=size">size</a>;
<a name="L4690" href="source/net/ipv4/tcp_input.c#L4690">4690</a>                         }
<a name="L4691" href="source/net/ipv4/tcp_input.c#L4691">4691</a>                         if (!<a href="ident?i=before">before</a>(<a href="ident?i=start">start</a>, <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;end_seq)) {
<a name="L4692" href="source/net/ipv4/tcp_input.c#L4692">4692</a>                                 <a href="ident?i=skb">skb</a> = <a href="ident?i=tcp_collapse_one">tcp_collapse_one</a>(sk, <a href="ident?i=skb">skb</a>, <a href="ident?i=list">list</a>);
<a name="L4693" href="source/net/ipv4/tcp_input.c#L4693">4693</a>                                 if (!<a href="ident?i=skb">skb</a> ||
<a name="L4694" href="source/net/ipv4/tcp_input.c#L4694">4694</a>                                     <a href="ident?i=skb">skb</a> == <a href="ident?i=tail">tail</a> ||
<a name="L4695" href="source/net/ipv4/tcp_input.c#L4695">4695</a>                                     (<a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;tcp_flags &amp; (<a href="ident?i=TCPHDR_SYN">TCPHDR_SYN</a> | <a href="ident?i=TCPHDR_FIN">TCPHDR_FIN</a>)))
<a name="L4696" href="source/net/ipv4/tcp_input.c#L4696">4696</a>                                         return;
<a name="L4697" href="source/net/ipv4/tcp_input.c#L4697">4697</a>                         }
<a name="L4698" href="source/net/ipv4/tcp_input.c#L4698">4698</a>                 }
<a name="L4699" href="source/net/ipv4/tcp_input.c#L4699">4699</a>         }
<a name="L4700" href="source/net/ipv4/tcp_input.c#L4700">4700</a> }
<a name="L4701" href="source/net/ipv4/tcp_input.c#L4701">4701</a> 
<a name="L4702" href="source/net/ipv4/tcp_input.c#L4702">4702</a> <b><i>/* Collapse ofo queue. Algorithm: select contiguous sequence of skbs</i></b>
<a name="L4703" href="source/net/ipv4/tcp_input.c#L4703">4703</a> <b><i> * and tcp_collapse() them until all the queue is collapsed.</i></b>
<a name="L4704" href="source/net/ipv4/tcp_input.c#L4704">4704</a> <b><i> */</i></b>
<a name="L4705" href="source/net/ipv4/tcp_input.c#L4705">4705</a> static void <a href="ident?i=tcp_collapse_ofo_queue">tcp_collapse_ofo_queue</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L4706" href="source/net/ipv4/tcp_input.c#L4706">4706</a> {
<a name="L4707" href="source/net/ipv4/tcp_input.c#L4707">4707</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L4708" href="source/net/ipv4/tcp_input.c#L4708">4708</a>         struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a> = <a href="ident?i=skb_peek">skb_peek</a>(&amp;<a href="ident?i=tp">tp</a>-&gt;out_of_order_queue);
<a name="L4709" href="source/net/ipv4/tcp_input.c#L4709">4709</a>         struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=head">head</a>;
<a name="L4710" href="source/net/ipv4/tcp_input.c#L4710">4710</a>         <a href="ident?i=u32">u32</a> <a href="ident?i=start">start</a>, <a href="ident?i=end">end</a>;
<a name="L4711" href="source/net/ipv4/tcp_input.c#L4711">4711</a> 
<a name="L4712" href="source/net/ipv4/tcp_input.c#L4712">4712</a>         if (!<a href="ident?i=skb">skb</a>)
<a name="L4713" href="source/net/ipv4/tcp_input.c#L4713">4713</a>                 return;
<a name="L4714" href="source/net/ipv4/tcp_input.c#L4714">4714</a> 
<a name="L4715" href="source/net/ipv4/tcp_input.c#L4715">4715</a>         <a href="ident?i=start">start</a> = <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=seq">seq</a>;
<a name="L4716" href="source/net/ipv4/tcp_input.c#L4716">4716</a>         <a href="ident?i=end">end</a> = <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;end_seq;
<a name="L4717" href="source/net/ipv4/tcp_input.c#L4717">4717</a>         <a href="ident?i=head">head</a> = <a href="ident?i=skb">skb</a>;
<a name="L4718" href="source/net/ipv4/tcp_input.c#L4718">4718</a> 
<a name="L4719" href="source/net/ipv4/tcp_input.c#L4719">4719</a>         for (;;) {
<a name="L4720" href="source/net/ipv4/tcp_input.c#L4720">4720</a>                 struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=next">next</a> = <a href="ident?i=NULL">NULL</a>;
<a name="L4721" href="source/net/ipv4/tcp_input.c#L4721">4721</a> 
<a name="L4722" href="source/net/ipv4/tcp_input.c#L4722">4722</a>                 if (!<a href="ident?i=skb_queue_is_last">skb_queue_is_last</a>(&amp;<a href="ident?i=tp">tp</a>-&gt;out_of_order_queue, <a href="ident?i=skb">skb</a>))
<a name="L4723" href="source/net/ipv4/tcp_input.c#L4723">4723</a>                         <a href="ident?i=next">next</a> = <a href="ident?i=skb_queue_next">skb_queue_next</a>(&amp;<a href="ident?i=tp">tp</a>-&gt;out_of_order_queue, <a href="ident?i=skb">skb</a>);
<a name="L4724" href="source/net/ipv4/tcp_input.c#L4724">4724</a>                 <a href="ident?i=skb">skb</a> = <a href="ident?i=next">next</a>;
<a name="L4725" href="source/net/ipv4/tcp_input.c#L4725">4725</a> 
<a name="L4726" href="source/net/ipv4/tcp_input.c#L4726">4726</a>                 <b><i>/* Segment is terminated when we see gap or when</i></b>
<a name="L4727" href="source/net/ipv4/tcp_input.c#L4727">4727</a> <b><i>                 * we are at the end of all the queue. */</i></b>
<a name="L4728" href="source/net/ipv4/tcp_input.c#L4728">4728</a>                 if (!<a href="ident?i=skb">skb</a> ||
<a name="L4729" href="source/net/ipv4/tcp_input.c#L4729">4729</a>                     <a href="ident?i=after">after</a>(<a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=seq">seq</a>, <a href="ident?i=end">end</a>) ||
<a name="L4730" href="source/net/ipv4/tcp_input.c#L4730">4730</a>                     <a href="ident?i=before">before</a>(<a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;end_seq, <a href="ident?i=start">start</a>)) {
<a name="L4731" href="source/net/ipv4/tcp_input.c#L4731">4731</a>                         <a href="ident?i=tcp_collapse">tcp_collapse</a>(sk, &amp;<a href="ident?i=tp">tp</a>-&gt;out_of_order_queue,
<a name="L4732" href="source/net/ipv4/tcp_input.c#L4732">4732</a>                                      <a href="ident?i=head">head</a>, <a href="ident?i=skb">skb</a>, <a href="ident?i=start">start</a>, <a href="ident?i=end">end</a>);
<a name="L4733" href="source/net/ipv4/tcp_input.c#L4733">4733</a>                         <a href="ident?i=head">head</a> = <a href="ident?i=skb">skb</a>;
<a name="L4734" href="source/net/ipv4/tcp_input.c#L4734">4734</a>                         if (!<a href="ident?i=skb">skb</a>)
<a name="L4735" href="source/net/ipv4/tcp_input.c#L4735">4735</a>                                 break;
<a name="L4736" href="source/net/ipv4/tcp_input.c#L4736">4736</a>                         <b><i>/* Start new segment */</i></b>
<a name="L4737" href="source/net/ipv4/tcp_input.c#L4737">4737</a>                         <a href="ident?i=start">start</a> = <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=seq">seq</a>;
<a name="L4738" href="source/net/ipv4/tcp_input.c#L4738">4738</a>                         <a href="ident?i=end">end</a> = <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;end_seq;
<a name="L4739" href="source/net/ipv4/tcp_input.c#L4739">4739</a>                 } else {
<a name="L4740" href="source/net/ipv4/tcp_input.c#L4740">4740</a>                         if (<a href="ident?i=before">before</a>(<a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=seq">seq</a>, <a href="ident?i=start">start</a>))
<a name="L4741" href="source/net/ipv4/tcp_input.c#L4741">4741</a>                                 <a href="ident?i=start">start</a> = <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=seq">seq</a>;
<a name="L4742" href="source/net/ipv4/tcp_input.c#L4742">4742</a>                         if (<a href="ident?i=after">after</a>(<a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;end_seq, <a href="ident?i=end">end</a>))
<a name="L4743" href="source/net/ipv4/tcp_input.c#L4743">4743</a>                                 <a href="ident?i=end">end</a> = <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;end_seq;
<a name="L4744" href="source/net/ipv4/tcp_input.c#L4744">4744</a>                 }
<a name="L4745" href="source/net/ipv4/tcp_input.c#L4745">4745</a>         }
<a name="L4746" href="source/net/ipv4/tcp_input.c#L4746">4746</a> }
<a name="L4747" href="source/net/ipv4/tcp_input.c#L4747">4747</a> 
<a name="L4748" href="source/net/ipv4/tcp_input.c#L4748">4748</a> <b><i>/*</i></b>
<a name="L4749" href="source/net/ipv4/tcp_input.c#L4749">4749</a> <b><i> * Purge the out-of-order queue.</i></b>
<a name="L4750" href="source/net/ipv4/tcp_input.c#L4750">4750</a> <b><i> * Return true if queue was pruned.</i></b>
<a name="L4751" href="source/net/ipv4/tcp_input.c#L4751">4751</a> <b><i> */</i></b>
<a name="L4752" href="source/net/ipv4/tcp_input.c#L4752">4752</a> static <a href="ident?i=bool">bool</a> <a href="ident?i=tcp_prune_ofo_queue">tcp_prune_ofo_queue</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L4753" href="source/net/ipv4/tcp_input.c#L4753">4753</a> {
<a name="L4754" href="source/net/ipv4/tcp_input.c#L4754">4754</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L4755" href="source/net/ipv4/tcp_input.c#L4755">4755</a>         <a href="ident?i=bool">bool</a> <a href="ident?i=res">res</a> = <a href="ident?i=false">false</a>;
<a name="L4756" href="source/net/ipv4/tcp_input.c#L4756">4756</a> 
<a name="L4757" href="source/net/ipv4/tcp_input.c#L4757">4757</a>         if (!<a href="ident?i=skb_queue_empty">skb_queue_empty</a>(&amp;<a href="ident?i=tp">tp</a>-&gt;out_of_order_queue)) {
<a name="L4758" href="source/net/ipv4/tcp_input.c#L4758">4758</a>                 <a href="ident?i=NET_INC_STATS_BH">NET_INC_STATS_BH</a>(<a href="ident?i=sock_net">sock_net</a>(sk), LINUX_MIB_OFOPRUNED);
<a name="L4759" href="source/net/ipv4/tcp_input.c#L4759">4759</a>                 <a href="ident?i=__skb_queue_purge">__skb_queue_purge</a>(&amp;<a href="ident?i=tp">tp</a>-&gt;out_of_order_queue);
<a name="L4760" href="source/net/ipv4/tcp_input.c#L4760">4760</a> 
<a name="L4761" href="source/net/ipv4/tcp_input.c#L4761">4761</a>                 <b><i>/* Reset SACK state.  A conforming SACK implementation will</i></b>
<a name="L4762" href="source/net/ipv4/tcp_input.c#L4762">4762</a> <b><i>                 * do the same at a timeout based retransmit.  When a connection</i></b>
<a name="L4763" href="source/net/ipv4/tcp_input.c#L4763">4763</a> <b><i>                 * is in a sad state like this, we care only about integrity</i></b>
<a name="L4764" href="source/net/ipv4/tcp_input.c#L4764">4764</a> <b><i>                 * of the connection not performance.</i></b>
<a name="L4765" href="source/net/ipv4/tcp_input.c#L4765">4765</a> <b><i>                 */</i></b>
<a name="L4766" href="source/net/ipv4/tcp_input.c#L4766">4766</a>                 if (<a href="ident?i=tp">tp</a>-&gt;rx_opt.sack_ok)
<a name="L4767" href="source/net/ipv4/tcp_input.c#L4767">4767</a>                         <a href="ident?i=tcp_sack_reset">tcp_sack_reset</a>(&amp;<a href="ident?i=tp">tp</a>-&gt;rx_opt);
<a name="L4768" href="source/net/ipv4/tcp_input.c#L4768">4768</a>                 <a href="ident?i=sk_mem_reclaim">sk_mem_reclaim</a>(sk);
<a name="L4769" href="source/net/ipv4/tcp_input.c#L4769">4769</a>                 <a href="ident?i=res">res</a> = <a href="ident?i=true">true</a>;
<a name="L4770" href="source/net/ipv4/tcp_input.c#L4770">4770</a>         }
<a name="L4771" href="source/net/ipv4/tcp_input.c#L4771">4771</a>         return <a href="ident?i=res">res</a>;
<a name="L4772" href="source/net/ipv4/tcp_input.c#L4772">4772</a> }
<a name="L4773" href="source/net/ipv4/tcp_input.c#L4773">4773</a> 
<a name="L4774" href="source/net/ipv4/tcp_input.c#L4774">4774</a> <b><i>/* Reduce allocated memory if we can, trying to get</i></b>
<a name="L4775" href="source/net/ipv4/tcp_input.c#L4775">4775</a> <b><i> * the socket within its memory limits again.</i></b>
<a name="L4776" href="source/net/ipv4/tcp_input.c#L4776">4776</a> <b><i> *</i></b>
<a name="L4777" href="source/net/ipv4/tcp_input.c#L4777">4777</a> <b><i> * Return less than zero if we should start dropping frames</i></b>
<a name="L4778" href="source/net/ipv4/tcp_input.c#L4778">4778</a> <b><i> * until the socket owning process reads some of the data</i></b>
<a name="L4779" href="source/net/ipv4/tcp_input.c#L4779">4779</a> <b><i> * to stabilize the situation.</i></b>
<a name="L4780" href="source/net/ipv4/tcp_input.c#L4780">4780</a> <b><i> */</i></b>
<a name="L4781" href="source/net/ipv4/tcp_input.c#L4781">4781</a> static int <a href="ident?i=tcp_prune_queue">tcp_prune_queue</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L4782" href="source/net/ipv4/tcp_input.c#L4782">4782</a> {
<a name="L4783" href="source/net/ipv4/tcp_input.c#L4783">4783</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L4784" href="source/net/ipv4/tcp_input.c#L4784">4784</a> 
<a name="L4785" href="source/net/ipv4/tcp_input.c#L4785">4785</a>         <a href="ident?i=SOCK_DEBUG">SOCK_DEBUG</a>(sk, <i>"prune_queue: c=%x\n"</i>, <a href="ident?i=tp">tp</a>-&gt;copied_seq);
<a name="L4786" href="source/net/ipv4/tcp_input.c#L4786">4786</a> 
<a name="L4787" href="source/net/ipv4/tcp_input.c#L4787">4787</a>         <a href="ident?i=NET_INC_STATS_BH">NET_INC_STATS_BH</a>(<a href="ident?i=sock_net">sock_net</a>(sk), LINUX_MIB_PRUNECALLED);
<a name="L4788" href="source/net/ipv4/tcp_input.c#L4788">4788</a> 
<a name="L4789" href="source/net/ipv4/tcp_input.c#L4789">4789</a>         if (<a href="ident?i=atomic_read">atomic_read</a>(&amp;sk-&gt;<a href="ident?i=sk_rmem_alloc">sk_rmem_alloc</a>) &gt;= sk-&gt;sk_rcvbuf)
<a name="L4790" href="source/net/ipv4/tcp_input.c#L4790">4790</a>                 <a href="ident?i=tcp_clamp_window">tcp_clamp_window</a>(sk);
<a name="L4791" href="source/net/ipv4/tcp_input.c#L4791">4791</a>         else if (<a href="ident?i=sk_under_memory_pressure">sk_under_memory_pressure</a>(sk))
<a name="L4792" href="source/net/ipv4/tcp_input.c#L4792">4792</a>                 <a href="ident?i=tp">tp</a>-&gt;rcv_ssthresh = <a href="ident?i=min">min</a>(<a href="ident?i=tp">tp</a>-&gt;rcv_ssthresh, 4U * <a href="ident?i=tp">tp</a>-&gt;advmss);
<a name="L4793" href="source/net/ipv4/tcp_input.c#L4793">4793</a> 
<a name="L4794" href="source/net/ipv4/tcp_input.c#L4794">4794</a>         <a href="ident?i=tcp_collapse_ofo_queue">tcp_collapse_ofo_queue</a>(sk);
<a name="L4795" href="source/net/ipv4/tcp_input.c#L4795">4795</a>         if (!<a href="ident?i=skb_queue_empty">skb_queue_empty</a>(&amp;sk-&gt;sk_receive_queue))
<a name="L4796" href="source/net/ipv4/tcp_input.c#L4796">4796</a>                 <a href="ident?i=tcp_collapse">tcp_collapse</a>(sk, &amp;sk-&gt;sk_receive_queue,
<a name="L4797" href="source/net/ipv4/tcp_input.c#L4797">4797</a>                              <a href="ident?i=skb_peek">skb_peek</a>(&amp;sk-&gt;sk_receive_queue),
<a name="L4798" href="source/net/ipv4/tcp_input.c#L4798">4798</a>                              <a href="ident?i=NULL">NULL</a>,
<a name="L4799" href="source/net/ipv4/tcp_input.c#L4799">4799</a>                              <a href="ident?i=tp">tp</a>-&gt;copied_seq, <a href="ident?i=tp">tp</a>-&gt;rcv_nxt);
<a name="L4800" href="source/net/ipv4/tcp_input.c#L4800">4800</a>         <a href="ident?i=sk_mem_reclaim">sk_mem_reclaim</a>(sk);
<a name="L4801" href="source/net/ipv4/tcp_input.c#L4801">4801</a> 
<a name="L4802" href="source/net/ipv4/tcp_input.c#L4802">4802</a>         if (<a href="ident?i=atomic_read">atomic_read</a>(&amp;sk-&gt;<a href="ident?i=sk_rmem_alloc">sk_rmem_alloc</a>) &lt;= sk-&gt;sk_rcvbuf)
<a name="L4803" href="source/net/ipv4/tcp_input.c#L4803">4803</a>                 return 0;
<a name="L4804" href="source/net/ipv4/tcp_input.c#L4804">4804</a> 
<a name="L4805" href="source/net/ipv4/tcp_input.c#L4805">4805</a>         <b><i>/* Collapsing did not help, destructive actions follow.</i></b>
<a name="L4806" href="source/net/ipv4/tcp_input.c#L4806">4806</a> <b><i>         * This must not ever occur. */</i></b>
<a name="L4807" href="source/net/ipv4/tcp_input.c#L4807">4807</a> 
<a name="L4808" href="source/net/ipv4/tcp_input.c#L4808">4808</a>         <a href="ident?i=tcp_prune_ofo_queue">tcp_prune_ofo_queue</a>(sk);
<a name="L4809" href="source/net/ipv4/tcp_input.c#L4809">4809</a> 
<a name="L4810" href="source/net/ipv4/tcp_input.c#L4810">4810</a>         if (<a href="ident?i=atomic_read">atomic_read</a>(&amp;sk-&gt;<a href="ident?i=sk_rmem_alloc">sk_rmem_alloc</a>) &lt;= sk-&gt;sk_rcvbuf)
<a name="L4811" href="source/net/ipv4/tcp_input.c#L4811">4811</a>                 return 0;
<a name="L4812" href="source/net/ipv4/tcp_input.c#L4812">4812</a> 
<a name="L4813" href="source/net/ipv4/tcp_input.c#L4813">4813</a>         <b><i>/* If we are really being abused, tell the caller to silently</i></b>
<a name="L4814" href="source/net/ipv4/tcp_input.c#L4814">4814</a> <b><i>         * drop receive data on the floor.  It will get retransmitted</i></b>
<a name="L4815" href="source/net/ipv4/tcp_input.c#L4815">4815</a> <b><i>         * and hopefully then we'll have sufficient space.</i></b>
<a name="L4816" href="source/net/ipv4/tcp_input.c#L4816">4816</a> <b><i>         */</i></b>
<a name="L4817" href="source/net/ipv4/tcp_input.c#L4817">4817</a>         <a href="ident?i=NET_INC_STATS_BH">NET_INC_STATS_BH</a>(<a href="ident?i=sock_net">sock_net</a>(sk), LINUX_MIB_RCVPRUNED);
<a name="L4818" href="source/net/ipv4/tcp_input.c#L4818">4818</a> 
<a name="L4819" href="source/net/ipv4/tcp_input.c#L4819">4819</a>         <b><i>/* Massive buffer overcommit. */</i></b>
<a name="L4820" href="source/net/ipv4/tcp_input.c#L4820">4820</a>         <a href="ident?i=tp">tp</a>-&gt;pred_flags = 0;
<a name="L4821" href="source/net/ipv4/tcp_input.c#L4821">4821</a>         return -1;
<a name="L4822" href="source/net/ipv4/tcp_input.c#L4822">4822</a> }
<a name="L4823" href="source/net/ipv4/tcp_input.c#L4823">4823</a> 
<a name="L4824" href="source/net/ipv4/tcp_input.c#L4824">4824</a> static <a href="ident?i=bool">bool</a> <a href="ident?i=tcp_should_expand_sndbuf">tcp_should_expand_sndbuf</a>(const struct <a href="ident?i=sock">sock</a> *sk)
<a name="L4825" href="source/net/ipv4/tcp_input.c#L4825">4825</a> {
<a name="L4826" href="source/net/ipv4/tcp_input.c#L4826">4826</a>         const struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L4827" href="source/net/ipv4/tcp_input.c#L4827">4827</a> 
<a name="L4828" href="source/net/ipv4/tcp_input.c#L4828">4828</a>         <b><i>/* If the user specified a specific send buffer setting, do</i></b>
<a name="L4829" href="source/net/ipv4/tcp_input.c#L4829">4829</a> <b><i>         * not modify it.</i></b>
<a name="L4830" href="source/net/ipv4/tcp_input.c#L4830">4830</a> <b><i>         */</i></b>
<a name="L4831" href="source/net/ipv4/tcp_input.c#L4831">4831</a>         if (sk-&gt;sk_userlocks &amp; <a href="ident?i=SOCK_SNDBUF_LOCK">SOCK_SNDBUF_LOCK</a>)
<a name="L4832" href="source/net/ipv4/tcp_input.c#L4832">4832</a>                 return <a href="ident?i=false">false</a>;
<a name="L4833" href="source/net/ipv4/tcp_input.c#L4833">4833</a> 
<a name="L4834" href="source/net/ipv4/tcp_input.c#L4834">4834</a>         <b><i>/* If we are under global TCP memory pressure, do not expand.  */</i></b>
<a name="L4835" href="source/net/ipv4/tcp_input.c#L4835">4835</a>         if (<a href="ident?i=sk_under_memory_pressure">sk_under_memory_pressure</a>(sk))
<a name="L4836" href="source/net/ipv4/tcp_input.c#L4836">4836</a>                 return <a href="ident?i=false">false</a>;
<a name="L4837" href="source/net/ipv4/tcp_input.c#L4837">4837</a> 
<a name="L4838" href="source/net/ipv4/tcp_input.c#L4838">4838</a>         <b><i>/* If we are under soft global TCP memory pressure, do not expand.  */</i></b>
<a name="L4839" href="source/net/ipv4/tcp_input.c#L4839">4839</a>         if (<a href="ident?i=sk_memory_allocated">sk_memory_allocated</a>(sk) &gt;= <a href="ident?i=sk_prot_mem_limits">sk_prot_mem_limits</a>(sk, 0))
<a name="L4840" href="source/net/ipv4/tcp_input.c#L4840">4840</a>                 return <a href="ident?i=false">false</a>;
<a name="L4841" href="source/net/ipv4/tcp_input.c#L4841">4841</a> 
<a name="L4842" href="source/net/ipv4/tcp_input.c#L4842">4842</a>         <b><i>/* If we filled the congestion window, do not expand.  */</i></b>
<a name="L4843" href="source/net/ipv4/tcp_input.c#L4843">4843</a>         if (<a href="ident?i=tcp_packets_in_flight">tcp_packets_in_flight</a>(<a href="ident?i=tp">tp</a>) &gt;= <a href="ident?i=tp">tp</a>-&gt;snd_cwnd)
<a name="L4844" href="source/net/ipv4/tcp_input.c#L4844">4844</a>                 return <a href="ident?i=false">false</a>;
<a name="L4845" href="source/net/ipv4/tcp_input.c#L4845">4845</a> 
<a name="L4846" href="source/net/ipv4/tcp_input.c#L4846">4846</a>         return <a href="ident?i=true">true</a>;
<a name="L4847" href="source/net/ipv4/tcp_input.c#L4847">4847</a> }
<a name="L4848" href="source/net/ipv4/tcp_input.c#L4848">4848</a> 
<a name="L4849" href="source/net/ipv4/tcp_input.c#L4849">4849</a> <b><i>/* When incoming ACK allowed to free some skb from write_queue,</i></b>
<a name="L4850" href="source/net/ipv4/tcp_input.c#L4850">4850</a> <b><i> * we remember this event in flag SOCK_QUEUE_SHRUNK and wake up socket</i></b>
<a name="L4851" href="source/net/ipv4/tcp_input.c#L4851">4851</a> <b><i> * on the exit from tcp input handler.</i></b>
<a name="L4852" href="source/net/ipv4/tcp_input.c#L4852">4852</a> <b><i> *</i></b>
<a name="L4853" href="source/net/ipv4/tcp_input.c#L4853">4853</a> <b><i> * PROBLEM: sndbuf expansion does not work well with largesend.</i></b>
<a name="L4854" href="source/net/ipv4/tcp_input.c#L4854">4854</a> <b><i> */</i></b>
<a name="L4855" href="source/net/ipv4/tcp_input.c#L4855">4855</a> static void <a href="ident?i=tcp_new_space">tcp_new_space</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L4856" href="source/net/ipv4/tcp_input.c#L4856">4856</a> {
<a name="L4857" href="source/net/ipv4/tcp_input.c#L4857">4857</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L4858" href="source/net/ipv4/tcp_input.c#L4858">4858</a> 
<a name="L4859" href="source/net/ipv4/tcp_input.c#L4859">4859</a>         if (<a href="ident?i=tcp_should_expand_sndbuf">tcp_should_expand_sndbuf</a>(sk)) {
<a name="L4860" href="source/net/ipv4/tcp_input.c#L4860">4860</a>                 <a href="ident?i=tcp_sndbuf_expand">tcp_sndbuf_expand</a>(sk);
<a name="L4861" href="source/net/ipv4/tcp_input.c#L4861">4861</a>                 <a href="ident?i=tp">tp</a>-&gt;snd_cwnd_stamp = <a href="ident?i=tcp_time_stamp">tcp_time_stamp</a>;
<a name="L4862" href="source/net/ipv4/tcp_input.c#L4862">4862</a>         }
<a name="L4863" href="source/net/ipv4/tcp_input.c#L4863">4863</a> 
<a name="L4864" href="source/net/ipv4/tcp_input.c#L4864">4864</a>         sk-&gt;sk_write_space(sk);
<a name="L4865" href="source/net/ipv4/tcp_input.c#L4865">4865</a> }
<a name="L4866" href="source/net/ipv4/tcp_input.c#L4866">4866</a> 
<a name="L4867" href="source/net/ipv4/tcp_input.c#L4867">4867</a> static void <a href="ident?i=tcp_check_space">tcp_check_space</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L4868" href="source/net/ipv4/tcp_input.c#L4868">4868</a> {
<a name="L4869" href="source/net/ipv4/tcp_input.c#L4869">4869</a>         if (<a href="ident?i=sock_flag">sock_flag</a>(sk, SOCK_QUEUE_SHRUNK)) {
<a name="L4870" href="source/net/ipv4/tcp_input.c#L4870">4870</a>                 <a href="ident?i=sock_reset_flag">sock_reset_flag</a>(sk, SOCK_QUEUE_SHRUNK);
<a name="L4871" href="source/net/ipv4/tcp_input.c#L4871">4871</a>                 <b><i>/* pairs with tcp_poll() */</i></b>
<a name="L4872" href="source/net/ipv4/tcp_input.c#L4872">4872</a>                 <a href="ident?i=smp_mb__after_atomic">smp_mb__after_atomic</a>();
<a name="L4873" href="source/net/ipv4/tcp_input.c#L4873">4873</a>                 if (sk-&gt;sk_socket &amp;&amp;
<a name="L4874" href="source/net/ipv4/tcp_input.c#L4874">4874</a>                     <a href="ident?i=test_bit">test_bit</a>(<a href="ident?i=SOCK_NOSPACE">SOCK_NOSPACE</a>, &amp;sk-&gt;sk_socket-&gt;<a href="ident?i=flags">flags</a>))
<a name="L4875" href="source/net/ipv4/tcp_input.c#L4875">4875</a>                         <a href="ident?i=tcp_new_space">tcp_new_space</a>(sk);
<a name="L4876" href="source/net/ipv4/tcp_input.c#L4876">4876</a>         }
<a name="L4877" href="source/net/ipv4/tcp_input.c#L4877">4877</a> }
<a name="L4878" href="source/net/ipv4/tcp_input.c#L4878">4878</a> 
<a name="L4879" href="source/net/ipv4/tcp_input.c#L4879">4879</a> static inline void <a href="ident?i=tcp_data_snd_check">tcp_data_snd_check</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L4880" href="source/net/ipv4/tcp_input.c#L4880">4880</a> {
<a name="L4881" href="source/net/ipv4/tcp_input.c#L4881">4881</a>         <a href="ident?i=tcp_push_pending_frames">tcp_push_pending_frames</a>(sk);
<a name="L4882" href="source/net/ipv4/tcp_input.c#L4882">4882</a>         <a href="ident?i=tcp_check_space">tcp_check_space</a>(sk);
<a name="L4883" href="source/net/ipv4/tcp_input.c#L4883">4883</a> }
<a name="L4884" href="source/net/ipv4/tcp_input.c#L4884">4884</a> 
<a name="L4885" href="source/net/ipv4/tcp_input.c#L4885">4885</a> <b><i>/*</i></b>
<a name="L4886" href="source/net/ipv4/tcp_input.c#L4886">4886</a> <b><i> * Check if sending an ack is needed.</i></b>
<a name="L4887" href="source/net/ipv4/tcp_input.c#L4887">4887</a> <b><i> */</i></b>
<a name="L4888" href="source/net/ipv4/tcp_input.c#L4888">4888</a> static void <a href="ident?i=__tcp_ack_snd_check">__tcp_ack_snd_check</a>(struct <a href="ident?i=sock">sock</a> *sk, int ofo_possible)
<a name="L4889" href="source/net/ipv4/tcp_input.c#L4889">4889</a> {
<a name="L4890" href="source/net/ipv4/tcp_input.c#L4890">4890</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L4891" href="source/net/ipv4/tcp_input.c#L4891">4891</a> 
<a name="L4892" href="source/net/ipv4/tcp_input.c#L4892">4892</a>             <b><i>/* More than one full frame received... */</i></b>
<a name="L4893" href="source/net/ipv4/tcp_input.c#L4893">4893</a>         if (((<a href="ident?i=tp">tp</a>-&gt;rcv_nxt - <a href="ident?i=tp">tp</a>-&gt;rcv_wup) &gt; <a href="ident?i=inet_csk">inet_csk</a>(sk)-&gt;icsk_ack.rcv_mss &amp;&amp;
<a name="L4894" href="source/net/ipv4/tcp_input.c#L4894">4894</a>              <b><i>/* ... and right edge of window advances far enough.</i></b>
<a name="L4895" href="source/net/ipv4/tcp_input.c#L4895">4895</a> <b><i>              * (tcp_recvmsg() will send ACK otherwise). Or...</i></b>
<a name="L4896" href="source/net/ipv4/tcp_input.c#L4896">4896</a> <b><i>              */</i></b>
<a name="L4897" href="source/net/ipv4/tcp_input.c#L4897">4897</a>              <a href="ident?i=__tcp_select_window">__tcp_select_window</a>(sk) &gt;= <a href="ident?i=tp">tp</a>-&gt;rcv_wnd) ||
<a name="L4898" href="source/net/ipv4/tcp_input.c#L4898">4898</a>             <b><i>/* We ACK each frame or... */</i></b>
<a name="L4899" href="source/net/ipv4/tcp_input.c#L4899">4899</a>             <a href="ident?i=tcp_in_quickack_mode">tcp_in_quickack_mode</a>(sk) ||
<a name="L4900" href="source/net/ipv4/tcp_input.c#L4900">4900</a>             <b><i>/* We have out of order data. */</i></b>
<a name="L4901" href="source/net/ipv4/tcp_input.c#L4901">4901</a>             (ofo_possible &amp;&amp; <a href="ident?i=skb_peek">skb_peek</a>(&amp;<a href="ident?i=tp">tp</a>-&gt;out_of_order_queue))) {
<a name="L4902" href="source/net/ipv4/tcp_input.c#L4902">4902</a>                 <b><i>/* Then ack it now */</i></b>
<a name="L4903" href="source/net/ipv4/tcp_input.c#L4903">4903</a>                 <a href="ident?i=tcp_send_ack">tcp_send_ack</a>(sk);
<a name="L4904" href="source/net/ipv4/tcp_input.c#L4904">4904</a>         } else {
<a name="L4905" href="source/net/ipv4/tcp_input.c#L4905">4905</a>                 <b><i>/* Else, send delayed ack. */</i></b>
<a name="L4906" href="source/net/ipv4/tcp_input.c#L4906">4906</a>                 <a href="ident?i=tcp_send_delayed_ack">tcp_send_delayed_ack</a>(sk);
<a name="L4907" href="source/net/ipv4/tcp_input.c#L4907">4907</a>         }
<a name="L4908" href="source/net/ipv4/tcp_input.c#L4908">4908</a> }
<a name="L4909" href="source/net/ipv4/tcp_input.c#L4909">4909</a> 
<a name="L4910" href="source/net/ipv4/tcp_input.c#L4910">4910</a> static inline void <a href="ident?i=tcp_ack_snd_check">tcp_ack_snd_check</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L4911" href="source/net/ipv4/tcp_input.c#L4911">4911</a> {
<a name="L4912" href="source/net/ipv4/tcp_input.c#L4912">4912</a>         if (!<a href="ident?i=inet_csk_ack_scheduled">inet_csk_ack_scheduled</a>(sk)) {
<a name="L4913" href="source/net/ipv4/tcp_input.c#L4913">4913</a>                 <b><i>/* We sent a data segment already. */</i></b>
<a name="L4914" href="source/net/ipv4/tcp_input.c#L4914">4914</a>                 return;
<a name="L4915" href="source/net/ipv4/tcp_input.c#L4915">4915</a>         }
<a name="L4916" href="source/net/ipv4/tcp_input.c#L4916">4916</a>         <a href="ident?i=__tcp_ack_snd_check">__tcp_ack_snd_check</a>(sk, 1);
<a name="L4917" href="source/net/ipv4/tcp_input.c#L4917">4917</a> }
<a name="L4918" href="source/net/ipv4/tcp_input.c#L4918">4918</a> 
<a name="L4919" href="source/net/ipv4/tcp_input.c#L4919">4919</a> <b><i>/*</i></b>
<a name="L4920" href="source/net/ipv4/tcp_input.c#L4920">4920</a> <b><i> *      This routine is only called when we have urgent data</i></b>
<a name="L4921" href="source/net/ipv4/tcp_input.c#L4921">4921</a> <b><i> *      signaled. Its the 'slow' part of tcp_urg. It could be</i></b>
<a name="L4922" href="source/net/ipv4/tcp_input.c#L4922">4922</a> <b><i> *      moved inline now as tcp_urg is only called from one</i></b>
<a name="L4923" href="source/net/ipv4/tcp_input.c#L4923">4923</a> <b><i> *      place. We handle URGent data wrong. We have to - as</i></b>
<a name="L4924" href="source/net/ipv4/tcp_input.c#L4924">4924</a> <b><i> *      BSD still doesn't use the correction from RFC961.</i></b>
<a name="L4925" href="source/net/ipv4/tcp_input.c#L4925">4925</a> <b><i> *      For 1003.1g we should support a new option TCP_STDURG to permit</i></b>
<a name="L4926" href="source/net/ipv4/tcp_input.c#L4926">4926</a> <b><i> *      either form (or just set the sysctl tcp_stdurg).</i></b>
<a name="L4927" href="source/net/ipv4/tcp_input.c#L4927">4927</a> <b><i> */</i></b>
<a name="L4928" href="source/net/ipv4/tcp_input.c#L4928">4928</a> 
<a name="L4929" href="source/net/ipv4/tcp_input.c#L4929">4929</a> static void <a href="ident?i=tcp_check_urg">tcp_check_urg</a>(struct <a href="ident?i=sock">sock</a> *sk, const struct <a href="ident?i=tcphdr">tcphdr</a> *<a href="ident?i=th">th</a>)
<a name="L4930" href="source/net/ipv4/tcp_input.c#L4930">4930</a> {
<a name="L4931" href="source/net/ipv4/tcp_input.c#L4931">4931</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L4932" href="source/net/ipv4/tcp_input.c#L4932">4932</a>         <a href="ident?i=u32">u32</a> <a href="ident?i=ptr">ptr</a> = <a href="ident?i=ntohs">ntohs</a>(<a href="ident?i=th">th</a>-&gt;urg_ptr);
<a name="L4933" href="source/net/ipv4/tcp_input.c#L4933">4933</a> 
<a name="L4934" href="source/net/ipv4/tcp_input.c#L4934">4934</a>         if (<a href="ident?i=ptr">ptr</a> &amp;&amp; !<a href="ident?i=sysctl_tcp_stdurg">sysctl_tcp_stdurg</a>)
<a name="L4935" href="source/net/ipv4/tcp_input.c#L4935">4935</a>                 <a href="ident?i=ptr">ptr</a>--;
<a name="L4936" href="source/net/ipv4/tcp_input.c#L4936">4936</a>         <a href="ident?i=ptr">ptr</a> += <a href="ident?i=ntohl">ntohl</a>(<a href="ident?i=th">th</a>-&gt;<a href="ident?i=seq">seq</a>);
<a name="L4937" href="source/net/ipv4/tcp_input.c#L4937">4937</a> 
<a name="L4938" href="source/net/ipv4/tcp_input.c#L4938">4938</a>         <b><i>/* Ignore urgent data that we've already seen and read. */</i></b>
<a name="L4939" href="source/net/ipv4/tcp_input.c#L4939">4939</a>         if (<a href="ident?i=after">after</a>(<a href="ident?i=tp">tp</a>-&gt;copied_seq, <a href="ident?i=ptr">ptr</a>))
<a name="L4940" href="source/net/ipv4/tcp_input.c#L4940">4940</a>                 return;
<a name="L4941" href="source/net/ipv4/tcp_input.c#L4941">4941</a> 
<a name="L4942" href="source/net/ipv4/tcp_input.c#L4942">4942</a>         <b><i>/* Do not replay urg ptr.</i></b>
<a name="L4943" href="source/net/ipv4/tcp_input.c#L4943">4943</a> <b><i>         *</i></b>
<a name="L4944" href="source/net/ipv4/tcp_input.c#L4944">4944</a> <b><i>         * NOTE: interesting situation not covered by specs.</i></b>
<a name="L4945" href="source/net/ipv4/tcp_input.c#L4945">4945</a> <b><i>         * Misbehaving sender may send urg ptr, pointing to segment,</i></b>
<a name="L4946" href="source/net/ipv4/tcp_input.c#L4946">4946</a> <b><i>         * which we already have in ofo queue. We are not able to fetch</i></b>
<a name="L4947" href="source/net/ipv4/tcp_input.c#L4947">4947</a> <b><i>         * such data and will stay in TCP_URG_NOTYET until will be eaten</i></b>
<a name="L4948" href="source/net/ipv4/tcp_input.c#L4948">4948</a> <b><i>         * by recvmsg(). Seems, we are not obliged to handle such wicked</i></b>
<a name="L4949" href="source/net/ipv4/tcp_input.c#L4949">4949</a> <b><i>         * situations. But it is worth to think about possibility of some</i></b>
<a name="L4950" href="source/net/ipv4/tcp_input.c#L4950">4950</a> <b><i>         * DoSes using some hypothetical application level deadlock.</i></b>
<a name="L4951" href="source/net/ipv4/tcp_input.c#L4951">4951</a> <b><i>         */</i></b>
<a name="L4952" href="source/net/ipv4/tcp_input.c#L4952">4952</a>         if (<a href="ident?i=before">before</a>(<a href="ident?i=ptr">ptr</a>, <a href="ident?i=tp">tp</a>-&gt;rcv_nxt))
<a name="L4953" href="source/net/ipv4/tcp_input.c#L4953">4953</a>                 return;
<a name="L4954" href="source/net/ipv4/tcp_input.c#L4954">4954</a> 
<a name="L4955" href="source/net/ipv4/tcp_input.c#L4955">4955</a>         <b><i>/* Do we already have a newer (or duplicate) urgent pointer? */</i></b>
<a name="L4956" href="source/net/ipv4/tcp_input.c#L4956">4956</a>         if (<a href="ident?i=tp">tp</a>-&gt;urg_data &amp;&amp; !<a href="ident?i=after">after</a>(<a href="ident?i=ptr">ptr</a>, <a href="ident?i=tp">tp</a>-&gt;urg_seq))
<a name="L4957" href="source/net/ipv4/tcp_input.c#L4957">4957</a>                 return;
<a name="L4958" href="source/net/ipv4/tcp_input.c#L4958">4958</a> 
<a name="L4959" href="source/net/ipv4/tcp_input.c#L4959">4959</a>         <b><i>/* Tell the world about our new urgent pointer. */</i></b>
<a name="L4960" href="source/net/ipv4/tcp_input.c#L4960">4960</a>         <a href="ident?i=sk_send_sigurg">sk_send_sigurg</a>(sk);
<a name="L4961" href="source/net/ipv4/tcp_input.c#L4961">4961</a> 
<a name="L4962" href="source/net/ipv4/tcp_input.c#L4962">4962</a>         <b><i>/* We may be adding urgent data when the last byte read was</i></b>
<a name="L4963" href="source/net/ipv4/tcp_input.c#L4963">4963</a> <b><i>         * urgent. To do this requires some care. We cannot just ignore</i></b>
<a name="L4964" href="source/net/ipv4/tcp_input.c#L4964">4964</a> <b><i>         * tp-&gt;copied_seq since we would read the last urgent byte again</i></b>
<a name="L4965" href="source/net/ipv4/tcp_input.c#L4965">4965</a> <b><i>         * as data, nor can we alter copied_seq until this data arrives</i></b>
<a name="L4966" href="source/net/ipv4/tcp_input.c#L4966">4966</a> <b><i>         * or we break the semantics of SIOCATMARK (and thus sockatmark())</i></b>
<a name="L4967" href="source/net/ipv4/tcp_input.c#L4967">4967</a> <b><i>         *</i></b>
<a name="L4968" href="source/net/ipv4/tcp_input.c#L4968">4968</a> <b><i>         * NOTE. Double Dutch. Rendering to plain English: author of comment</i></b>
<a name="L4969" href="source/net/ipv4/tcp_input.c#L4969">4969</a> <b><i>         * above did something sort of  send("A", MSG_OOB); send("B", MSG_OOB);</i></b>
<a name="L4970" href="source/net/ipv4/tcp_input.c#L4970">4970</a> <b><i>         * and expect that both A and B disappear from stream. This is _wrong_.</i></b>
<a name="L4971" href="source/net/ipv4/tcp_input.c#L4971">4971</a> <b><i>         * Though this happens in BSD with high probability, this is occasional.</i></b>
<a name="L4972" href="source/net/ipv4/tcp_input.c#L4972">4972</a> <b><i>         * Any application relying on this is buggy. Note also, that fix "works"</i></b>
<a name="L4973" href="source/net/ipv4/tcp_input.c#L4973">4973</a> <b><i>         * only in this artificial test. Insert some normal data between A and B and we will</i></b>
<a name="L4974" href="source/net/ipv4/tcp_input.c#L4974">4974</a> <b><i>         * decline of BSD again. Verdict: it is better to remove to trap</i></b>
<a name="L4975" href="source/net/ipv4/tcp_input.c#L4975">4975</a> <b><i>         * buggy users.</i></b>
<a name="L4976" href="source/net/ipv4/tcp_input.c#L4976">4976</a> <b><i>         */</i></b>
<a name="L4977" href="source/net/ipv4/tcp_input.c#L4977">4977</a>         if (<a href="ident?i=tp">tp</a>-&gt;urg_seq == <a href="ident?i=tp">tp</a>-&gt;copied_seq &amp;&amp; <a href="ident?i=tp">tp</a>-&gt;urg_data &amp;&amp;
<a name="L4978" href="source/net/ipv4/tcp_input.c#L4978">4978</a>             !<a href="ident?i=sock_flag">sock_flag</a>(sk, SOCK_URGINLINE) &amp;&amp; <a href="ident?i=tp">tp</a>-&gt;copied_seq != <a href="ident?i=tp">tp</a>-&gt;rcv_nxt) {
<a name="L4979" href="source/net/ipv4/tcp_input.c#L4979">4979</a>                 struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a> = <a href="ident?i=skb_peek">skb_peek</a>(&amp;sk-&gt;sk_receive_queue);
<a name="L4980" href="source/net/ipv4/tcp_input.c#L4980">4980</a>                 <a href="ident?i=tp">tp</a>-&gt;copied_seq++;
<a name="L4981" href="source/net/ipv4/tcp_input.c#L4981">4981</a>                 if (<a href="ident?i=skb">skb</a> &amp;&amp; !<a href="ident?i=before">before</a>(<a href="ident?i=tp">tp</a>-&gt;copied_seq, <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;end_seq)) {
<a name="L4982" href="source/net/ipv4/tcp_input.c#L4982">4982</a>                         <a href="ident?i=__skb_unlink">__skb_unlink</a>(<a href="ident?i=skb">skb</a>, &amp;sk-&gt;sk_receive_queue);
<a name="L4983" href="source/net/ipv4/tcp_input.c#L4983">4983</a>                         <a href="ident?i=__kfree_skb">__kfree_skb</a>(<a href="ident?i=skb">skb</a>);
<a name="L4984" href="source/net/ipv4/tcp_input.c#L4984">4984</a>                 }
<a name="L4985" href="source/net/ipv4/tcp_input.c#L4985">4985</a>         }
<a name="L4986" href="source/net/ipv4/tcp_input.c#L4986">4986</a> 
<a name="L4987" href="source/net/ipv4/tcp_input.c#L4987">4987</a>         <a href="ident?i=tp">tp</a>-&gt;urg_data = <a href="ident?i=TCP_URG_NOTYET">TCP_URG_NOTYET</a>;
<a name="L4988" href="source/net/ipv4/tcp_input.c#L4988">4988</a>         <a href="ident?i=tp">tp</a>-&gt;urg_seq = <a href="ident?i=ptr">ptr</a>;
<a name="L4989" href="source/net/ipv4/tcp_input.c#L4989">4989</a> 
<a name="L4990" href="source/net/ipv4/tcp_input.c#L4990">4990</a>         <b><i>/* Disable header prediction. */</i></b>
<a name="L4991" href="source/net/ipv4/tcp_input.c#L4991">4991</a>         <a href="ident?i=tp">tp</a>-&gt;pred_flags = 0;
<a name="L4992" href="source/net/ipv4/tcp_input.c#L4992">4992</a> }
<a name="L4993" href="source/net/ipv4/tcp_input.c#L4993">4993</a> 
<a name="L4994" href="source/net/ipv4/tcp_input.c#L4994">4994</a> <b><i>/* This is the 'fast' part of urgent handling. */</i></b>
<a name="L4995" href="source/net/ipv4/tcp_input.c#L4995">4995</a> static void <a href="ident?i=tcp_urg">tcp_urg</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, const struct <a href="ident?i=tcphdr">tcphdr</a> *<a href="ident?i=th">th</a>)
<a name="L4996" href="source/net/ipv4/tcp_input.c#L4996">4996</a> {
<a name="L4997" href="source/net/ipv4/tcp_input.c#L4997">4997</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L4998" href="source/net/ipv4/tcp_input.c#L4998">4998</a> 
<a name="L4999" href="source/net/ipv4/tcp_input.c#L4999">4999</a>         <b><i>/* Check if we get a new urgent pointer - normally not. */</i></b>
<a name="L5000" href="source/net/ipv4/tcp_input.c#L5000">5000</a>         if (<a href="ident?i=th">th</a>-&gt;urg)
<a name="L5001" href="source/net/ipv4/tcp_input.c#L5001">5001</a>                 <a href="ident?i=tcp_check_urg">tcp_check_urg</a>(sk, <a href="ident?i=th">th</a>);
<a name="L5002" href="source/net/ipv4/tcp_input.c#L5002">5002</a> 
<a name="L5003" href="source/net/ipv4/tcp_input.c#L5003">5003</a>         <b><i>/* Do we wait for any urgent data? - normally not... */</i></b>
<a name="L5004" href="source/net/ipv4/tcp_input.c#L5004">5004</a>         if (<a href="ident?i=tp">tp</a>-&gt;urg_data == <a href="ident?i=TCP_URG_NOTYET">TCP_URG_NOTYET</a>) {
<a name="L5005" href="source/net/ipv4/tcp_input.c#L5005">5005</a>                 <a href="ident?i=u32">u32</a> <a href="ident?i=ptr">ptr</a> = <a href="ident?i=tp">tp</a>-&gt;urg_seq - <a href="ident?i=ntohl">ntohl</a>(<a href="ident?i=th">th</a>-&gt;<a href="ident?i=seq">seq</a>) + (<a href="ident?i=th">th</a>-&gt;doff * 4) -
<a name="L5006" href="source/net/ipv4/tcp_input.c#L5006">5006</a>                           <a href="ident?i=th">th</a>-&gt;syn;
<a name="L5007" href="source/net/ipv4/tcp_input.c#L5007">5007</a> 
<a name="L5008" href="source/net/ipv4/tcp_input.c#L5008">5008</a>                 <b><i>/* Is the urgent pointer pointing into this packet? */</i></b>
<a name="L5009" href="source/net/ipv4/tcp_input.c#L5009">5009</a>                 if (<a href="ident?i=ptr">ptr</a> &lt; <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a>) {
<a name="L5010" href="source/net/ipv4/tcp_input.c#L5010">5010</a>                         <a href="ident?i=u8">u8</a> <a href="ident?i=tmp">tmp</a>;
<a name="L5011" href="source/net/ipv4/tcp_input.c#L5011">5011</a>                         if (<a href="ident?i=skb_copy_bits">skb_copy_bits</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=ptr">ptr</a>, &amp;<a href="ident?i=tmp">tmp</a>, 1))
<a name="L5012" href="source/net/ipv4/tcp_input.c#L5012">5012</a>                                 <a href="ident?i=BUG">BUG</a>();
<a name="L5013" href="source/net/ipv4/tcp_input.c#L5013">5013</a>                         <a href="ident?i=tp">tp</a>-&gt;urg_data = <a href="ident?i=TCP_URG_VALID">TCP_URG_VALID</a> | <a href="ident?i=tmp">tmp</a>;
<a name="L5014" href="source/net/ipv4/tcp_input.c#L5014">5014</a>                         if (!<a href="ident?i=sock_flag">sock_flag</a>(sk, SOCK_DEAD))
<a name="L5015" href="source/net/ipv4/tcp_input.c#L5015">5015</a>                                 sk-&gt;sk_data_ready(sk);
<a name="L5016" href="source/net/ipv4/tcp_input.c#L5016">5016</a>                 }
<a name="L5017" href="source/net/ipv4/tcp_input.c#L5017">5017</a>         }
<a name="L5018" href="source/net/ipv4/tcp_input.c#L5018">5018</a> }
<a name="L5019" href="source/net/ipv4/tcp_input.c#L5019">5019</a> 
<a name="L5020" href="source/net/ipv4/tcp_input.c#L5020">5020</a> static int <a href="ident?i=tcp_copy_to_iovec">tcp_copy_to_iovec</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, int hlen)
<a name="L5021" href="source/net/ipv4/tcp_input.c#L5021">5021</a> {
<a name="L5022" href="source/net/ipv4/tcp_input.c#L5022">5022</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L5023" href="source/net/ipv4/tcp_input.c#L5023">5023</a>         int <a href="ident?i=chunk">chunk</a> = <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a> - hlen;
<a name="L5024" href="source/net/ipv4/tcp_input.c#L5024">5024</a>         int <a href="ident?i=err">err</a>;
<a name="L5025" href="source/net/ipv4/tcp_input.c#L5025">5025</a> 
<a name="L5026" href="source/net/ipv4/tcp_input.c#L5026">5026</a>         <a href="ident?i=local_bh_enable">local_bh_enable</a>();
<a name="L5027" href="source/net/ipv4/tcp_input.c#L5027">5027</a>         if (<a href="ident?i=skb_csum_unnecessary">skb_csum_unnecessary</a>(<a href="ident?i=skb">skb</a>))
<a name="L5028" href="source/net/ipv4/tcp_input.c#L5028">5028</a>                 <a href="ident?i=err">err</a> = <a href="ident?i=skb_copy_datagram_msg">skb_copy_datagram_msg</a>(<a href="ident?i=skb">skb</a>, hlen, <a href="ident?i=tp">tp</a>-&gt;ucopy.<a href="ident?i=msg">msg</a>, <a href="ident?i=chunk">chunk</a>);
<a name="L5029" href="source/net/ipv4/tcp_input.c#L5029">5029</a>         else
<a name="L5030" href="source/net/ipv4/tcp_input.c#L5030">5030</a>                 <a href="ident?i=err">err</a> = <a href="ident?i=skb_copy_and_csum_datagram_msg">skb_copy_and_csum_datagram_msg</a>(<a href="ident?i=skb">skb</a>, hlen, <a href="ident?i=tp">tp</a>-&gt;ucopy.<a href="ident?i=msg">msg</a>);
<a name="L5031" href="source/net/ipv4/tcp_input.c#L5031">5031</a> 
<a name="L5032" href="source/net/ipv4/tcp_input.c#L5032">5032</a>         if (!<a href="ident?i=err">err</a>) {
<a name="L5033" href="source/net/ipv4/tcp_input.c#L5033">5033</a>                 <a href="ident?i=tp">tp</a>-&gt;ucopy.<a href="ident?i=len">len</a> -= <a href="ident?i=chunk">chunk</a>;
<a name="L5034" href="source/net/ipv4/tcp_input.c#L5034">5034</a>                 <a href="ident?i=tp">tp</a>-&gt;copied_seq += <a href="ident?i=chunk">chunk</a>;
<a name="L5035" href="source/net/ipv4/tcp_input.c#L5035">5035</a>                 <a href="ident?i=tcp_rcv_space_adjust">tcp_rcv_space_adjust</a>(sk);
<a name="L5036" href="source/net/ipv4/tcp_input.c#L5036">5036</a>         }
<a name="L5037" href="source/net/ipv4/tcp_input.c#L5037">5037</a> 
<a name="L5038" href="source/net/ipv4/tcp_input.c#L5038">5038</a>         <a href="ident?i=local_bh_disable">local_bh_disable</a>();
<a name="L5039" href="source/net/ipv4/tcp_input.c#L5039">5039</a>         return <a href="ident?i=err">err</a>;
<a name="L5040" href="source/net/ipv4/tcp_input.c#L5040">5040</a> }
<a name="L5041" href="source/net/ipv4/tcp_input.c#L5041">5041</a> 
<a name="L5042" href="source/net/ipv4/tcp_input.c#L5042">5042</a> static <a href="ident?i=__sum16">__sum16</a> <a href="ident?i=__tcp_checksum_complete_user">__tcp_checksum_complete_user</a>(struct <a href="ident?i=sock">sock</a> *sk,
<a name="L5043" href="source/net/ipv4/tcp_input.c#L5043">5043</a>                                             struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L5044" href="source/net/ipv4/tcp_input.c#L5044">5044</a> {
<a name="L5045" href="source/net/ipv4/tcp_input.c#L5045">5045</a>         <a href="ident?i=__sum16">__sum16</a> <a href="ident?i=result">result</a>;
<a name="L5046" href="source/net/ipv4/tcp_input.c#L5046">5046</a> 
<a name="L5047" href="source/net/ipv4/tcp_input.c#L5047">5047</a>         if (<a href="ident?i=sock_owned_by_user">sock_owned_by_user</a>(sk)) {
<a name="L5048" href="source/net/ipv4/tcp_input.c#L5048">5048</a>                 <a href="ident?i=local_bh_enable">local_bh_enable</a>();
<a name="L5049" href="source/net/ipv4/tcp_input.c#L5049">5049</a>                 <a href="ident?i=result">result</a> = <a href="ident?i=__tcp_checksum_complete">__tcp_checksum_complete</a>(<a href="ident?i=skb">skb</a>);
<a name="L5050" href="source/net/ipv4/tcp_input.c#L5050">5050</a>                 <a href="ident?i=local_bh_disable">local_bh_disable</a>();
<a name="L5051" href="source/net/ipv4/tcp_input.c#L5051">5051</a>         } else {
<a name="L5052" href="source/net/ipv4/tcp_input.c#L5052">5052</a>                 <a href="ident?i=result">result</a> = <a href="ident?i=__tcp_checksum_complete">__tcp_checksum_complete</a>(<a href="ident?i=skb">skb</a>);
<a name="L5053" href="source/net/ipv4/tcp_input.c#L5053">5053</a>         }
<a name="L5054" href="source/net/ipv4/tcp_input.c#L5054">5054</a>         return <a href="ident?i=result">result</a>;
<a name="L5055" href="source/net/ipv4/tcp_input.c#L5055">5055</a> }
<a name="L5056" href="source/net/ipv4/tcp_input.c#L5056">5056</a> 
<a name="L5057" href="source/net/ipv4/tcp_input.c#L5057">5057</a> static inline <a href="ident?i=bool">bool</a> <a href="ident?i=tcp_checksum_complete_user">tcp_checksum_complete_user</a>(struct <a href="ident?i=sock">sock</a> *sk,
<a name="L5058" href="source/net/ipv4/tcp_input.c#L5058">5058</a>                                              struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L5059" href="source/net/ipv4/tcp_input.c#L5059">5059</a> {
<a name="L5060" href="source/net/ipv4/tcp_input.c#L5060">5060</a>         return !<a href="ident?i=skb_csum_unnecessary">skb_csum_unnecessary</a>(<a href="ident?i=skb">skb</a>) &amp;&amp;
<a name="L5061" href="source/net/ipv4/tcp_input.c#L5061">5061</a>                <a href="ident?i=__tcp_checksum_complete_user">__tcp_checksum_complete_user</a>(sk, <a href="ident?i=skb">skb</a>);
<a name="L5062" href="source/net/ipv4/tcp_input.c#L5062">5062</a> }
<a name="L5063" href="source/net/ipv4/tcp_input.c#L5063">5063</a> 
<a name="L5064" href="source/net/ipv4/tcp_input.c#L5064">5064</a> <b><i>/* Does PAWS and seqno based validation of an incoming segment, flags will</i></b>
<a name="L5065" href="source/net/ipv4/tcp_input.c#L5065">5065</a> <b><i> * play significant role here.</i></b>
<a name="L5066" href="source/net/ipv4/tcp_input.c#L5066">5066</a> <b><i> */</i></b>
<a name="L5067" href="source/net/ipv4/tcp_input.c#L5067">5067</a> static <a href="ident?i=bool">bool</a> <a href="ident?i=tcp_validate_incoming">tcp_validate_incoming</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
<a name="L5068" href="source/net/ipv4/tcp_input.c#L5068">5068</a>                                   const struct <a href="ident?i=tcphdr">tcphdr</a> *<a href="ident?i=th">th</a>, int syn_inerr)
<a name="L5069" href="source/net/ipv4/tcp_input.c#L5069">5069</a> {
<a name="L5070" href="source/net/ipv4/tcp_input.c#L5070">5070</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L5071" href="source/net/ipv4/tcp_input.c#L5071">5071</a> 
<a name="L5072" href="source/net/ipv4/tcp_input.c#L5072">5072</a>         <b><i>/* RFC1323: H1. Apply PAWS check first. */</i></b>
<a name="L5073" href="source/net/ipv4/tcp_input.c#L5073">5073</a>         if (<a href="ident?i=tcp_fast_parse_options">tcp_fast_parse_options</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=th">th</a>, <a href="ident?i=tp">tp</a>) &amp;&amp; <a href="ident?i=tp">tp</a>-&gt;rx_opt.saw_tstamp &amp;&amp;
<a name="L5074" href="source/net/ipv4/tcp_input.c#L5074">5074</a>             <a href="ident?i=tcp_paws_discard">tcp_paws_discard</a>(sk, <a href="ident?i=skb">skb</a>)) {
<a name="L5075" href="source/net/ipv4/tcp_input.c#L5075">5075</a>                 if (!<a href="ident?i=th">th</a>-&gt;rst) {
<a name="L5076" href="source/net/ipv4/tcp_input.c#L5076">5076</a>                         <a href="ident?i=NET_INC_STATS_BH">NET_INC_STATS_BH</a>(<a href="ident?i=sock_net">sock_net</a>(sk), LINUX_MIB_PAWSESTABREJECTED);
<a name="L5077" href="source/net/ipv4/tcp_input.c#L5077">5077</a>                         if (!<a href="ident?i=tcp_oow_rate_limited">tcp_oow_rate_limited</a>(<a href="ident?i=sock_net">sock_net</a>(sk), <a href="ident?i=skb">skb</a>,
<a name="L5078" href="source/net/ipv4/tcp_input.c#L5078">5078</a>                                                   LINUX_MIB_TCPACKSKIPPEDPAWS,
<a name="L5079" href="source/net/ipv4/tcp_input.c#L5079">5079</a>                                                   &amp;<a href="ident?i=tp">tp</a>-&gt;last_oow_ack_time))
<a name="L5080" href="source/net/ipv4/tcp_input.c#L5080">5080</a>                                 <a href="ident?i=tcp_send_dupack">tcp_send_dupack</a>(sk, <a href="ident?i=skb">skb</a>);
<a name="L5081" href="source/net/ipv4/tcp_input.c#L5081">5081</a>                         goto <a href="ident?i=discard">discard</a>;
<a name="L5082" href="source/net/ipv4/tcp_input.c#L5082">5082</a>                 }
<a name="L5083" href="source/net/ipv4/tcp_input.c#L5083">5083</a>                 <b><i>/* Reset is accepted even if it did not pass PAWS. */</i></b>
<a name="L5084" href="source/net/ipv4/tcp_input.c#L5084">5084</a>         }
<a name="L5085" href="source/net/ipv4/tcp_input.c#L5085">5085</a> 
<a name="L5086" href="source/net/ipv4/tcp_input.c#L5086">5086</a>         <b><i>/* Step 1: check sequence number */</i></b>
<a name="L5087" href="source/net/ipv4/tcp_input.c#L5087">5087</a>         if (!<a href="ident?i=tcp_sequence">tcp_sequence</a>(<a href="ident?i=tp">tp</a>, <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=seq">seq</a>, <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;end_seq)) {
<a name="L5088" href="source/net/ipv4/tcp_input.c#L5088">5088</a>                 <b><i>/* RFC793, page 37: "In all states except SYN-SENT, all reset</i></b>
<a name="L5089" href="source/net/ipv4/tcp_input.c#L5089">5089</a> <b><i>                 * (RST) segments are validated by checking their SEQ-fields."</i></b>
<a name="L5090" href="source/net/ipv4/tcp_input.c#L5090">5090</a> <b><i>                 * And page 69: "If an incoming segment is not acceptable,</i></b>
<a name="L5091" href="source/net/ipv4/tcp_input.c#L5091">5091</a> <b><i>                 * an acknowledgment should be sent in reply (unless the RST</i></b>
<a name="L5092" href="source/net/ipv4/tcp_input.c#L5092">5092</a> <b><i>                 * bit is set, if so drop the segment and return)".</i></b>
<a name="L5093" href="source/net/ipv4/tcp_input.c#L5093">5093</a> <b><i>                 */</i></b>
<a name="L5094" href="source/net/ipv4/tcp_input.c#L5094">5094</a>                 if (!<a href="ident?i=th">th</a>-&gt;rst) {
<a name="L5095" href="source/net/ipv4/tcp_input.c#L5095">5095</a>                         if (<a href="ident?i=th">th</a>-&gt;syn)
<a name="L5096" href="source/net/ipv4/tcp_input.c#L5096">5096</a>                                 goto syn_challenge;
<a name="L5097" href="source/net/ipv4/tcp_input.c#L5097">5097</a>                         if (!<a href="ident?i=tcp_oow_rate_limited">tcp_oow_rate_limited</a>(<a href="ident?i=sock_net">sock_net</a>(sk), <a href="ident?i=skb">skb</a>,
<a name="L5098" href="source/net/ipv4/tcp_input.c#L5098">5098</a>                                                   LINUX_MIB_TCPACKSKIPPEDSEQ,
<a name="L5099" href="source/net/ipv4/tcp_input.c#L5099">5099</a>                                                   &amp;<a href="ident?i=tp">tp</a>-&gt;last_oow_ack_time))
<a name="L5100" href="source/net/ipv4/tcp_input.c#L5100">5100</a>                                 <a href="ident?i=tcp_send_dupack">tcp_send_dupack</a>(sk, <a href="ident?i=skb">skb</a>);
<a name="L5101" href="source/net/ipv4/tcp_input.c#L5101">5101</a>                 }
<a name="L5102" href="source/net/ipv4/tcp_input.c#L5102">5102</a>                 goto <a href="ident?i=discard">discard</a>;
<a name="L5103" href="source/net/ipv4/tcp_input.c#L5103">5103</a>         }
<a name="L5104" href="source/net/ipv4/tcp_input.c#L5104">5104</a> 
<a name="L5105" href="source/net/ipv4/tcp_input.c#L5105">5105</a>         <b><i>/* Step 2: check RST bit */</i></b>
<a name="L5106" href="source/net/ipv4/tcp_input.c#L5106">5106</a>         if (<a href="ident?i=th">th</a>-&gt;rst) {
<a name="L5107" href="source/net/ipv4/tcp_input.c#L5107">5107</a>                 <b><i>/* RFC 5961 3.2 :</i></b>
<a name="L5108" href="source/net/ipv4/tcp_input.c#L5108">5108</a> <b><i>                 * If sequence number exactly matches RCV.NXT, then</i></b>
<a name="L5109" href="source/net/ipv4/tcp_input.c#L5109">5109</a> <b><i>                 *     RESET the connection</i></b>
<a name="L5110" href="source/net/ipv4/tcp_input.c#L5110">5110</a> <b><i>                 * else</i></b>
<a name="L5111" href="source/net/ipv4/tcp_input.c#L5111">5111</a> <b><i>                 *     Send a challenge ACK</i></b>
<a name="L5112" href="source/net/ipv4/tcp_input.c#L5112">5112</a> <b><i>                 */</i></b>
<a name="L5113" href="source/net/ipv4/tcp_input.c#L5113">5113</a>                 if (<a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=seq">seq</a> == <a href="ident?i=tp">tp</a>-&gt;rcv_nxt)
<a name="L5114" href="source/net/ipv4/tcp_input.c#L5114">5114</a>                         <a href="ident?i=tcp_reset">tcp_reset</a>(sk);
<a name="L5115" href="source/net/ipv4/tcp_input.c#L5115">5115</a>                 else
<a name="L5116" href="source/net/ipv4/tcp_input.c#L5116">5116</a>                         <a href="ident?i=tcp_send_challenge_ack">tcp_send_challenge_ack</a>(sk, <a href="ident?i=skb">skb</a>);
<a name="L5117" href="source/net/ipv4/tcp_input.c#L5117">5117</a>                 goto <a href="ident?i=discard">discard</a>;
<a name="L5118" href="source/net/ipv4/tcp_input.c#L5118">5118</a>         }
<a name="L5119" href="source/net/ipv4/tcp_input.c#L5119">5119</a> 
<a name="L5120" href="source/net/ipv4/tcp_input.c#L5120">5120</a>         <b><i>/* step 3: check security and precedence [ignored] */</i></b>
<a name="L5121" href="source/net/ipv4/tcp_input.c#L5121">5121</a> 
<a name="L5122" href="source/net/ipv4/tcp_input.c#L5122">5122</a>         <b><i>/* step 4: Check for a SYN</i></b>
<a name="L5123" href="source/net/ipv4/tcp_input.c#L5123">5123</a> <b><i>         * RFC 5961 4.2 : Send a challenge ack</i></b>
<a name="L5124" href="source/net/ipv4/tcp_input.c#L5124">5124</a> <b><i>         */</i></b>
<a name="L5125" href="source/net/ipv4/tcp_input.c#L5125">5125</a>         if (<a href="ident?i=th">th</a>-&gt;syn) {
<a name="L5126" href="source/net/ipv4/tcp_input.c#L5126">5126</a> syn_challenge:
<a name="L5127" href="source/net/ipv4/tcp_input.c#L5127">5127</a>                 if (syn_inerr)
<a name="L5128" href="source/net/ipv4/tcp_input.c#L5128">5128</a>                         <a href="ident?i=TCP_INC_STATS_BH">TCP_INC_STATS_BH</a>(<a href="ident?i=sock_net">sock_net</a>(sk), TCP_MIB_INERRS);
<a name="L5129" href="source/net/ipv4/tcp_input.c#L5129">5129</a>                 <a href="ident?i=NET_INC_STATS_BH">NET_INC_STATS_BH</a>(<a href="ident?i=sock_net">sock_net</a>(sk), LINUX_MIB_TCPSYNCHALLENGE);
<a name="L5130" href="source/net/ipv4/tcp_input.c#L5130">5130</a>                 <a href="ident?i=tcp_send_challenge_ack">tcp_send_challenge_ack</a>(sk, <a href="ident?i=skb">skb</a>);
<a name="L5131" href="source/net/ipv4/tcp_input.c#L5131">5131</a>                 goto <a href="ident?i=discard">discard</a>;
<a name="L5132" href="source/net/ipv4/tcp_input.c#L5132">5132</a>         }
<a name="L5133" href="source/net/ipv4/tcp_input.c#L5133">5133</a> 
<a name="L5134" href="source/net/ipv4/tcp_input.c#L5134">5134</a>         return <a href="ident?i=true">true</a>;
<a name="L5135" href="source/net/ipv4/tcp_input.c#L5135">5135</a> 
<a name="L5136" href="source/net/ipv4/tcp_input.c#L5136">5136</a> <a href="ident?i=discard">discard</a>:
<a name="L5137" href="source/net/ipv4/tcp_input.c#L5137">5137</a>         <a href="ident?i=__kfree_skb">__kfree_skb</a>(<a href="ident?i=skb">skb</a>);
<a name="L5138" href="source/net/ipv4/tcp_input.c#L5138">5138</a>         return <a href="ident?i=false">false</a>;
<a name="L5139" href="source/net/ipv4/tcp_input.c#L5139">5139</a> }
<a name="L5140" href="source/net/ipv4/tcp_input.c#L5140">5140</a> 
<a name="L5141" href="source/net/ipv4/tcp_input.c#L5141">5141</a> <b><i>/*</i></b>
<a name="L5142" href="source/net/ipv4/tcp_input.c#L5142">5142</a> <b><i> *      TCP receive function for the ESTABLISHED state.</i></b>
<a name="L5143" href="source/net/ipv4/tcp_input.c#L5143">5143</a> <b><i> *</i></b>
<a name="L5144" href="source/net/ipv4/tcp_input.c#L5144">5144</a> <b><i> *      It is split into a fast path and a slow path. The fast path is</i></b>
<a name="L5145" href="source/net/ipv4/tcp_input.c#L5145">5145</a> <b><i> *      disabled when:</i></b>
<a name="L5146" href="source/net/ipv4/tcp_input.c#L5146">5146</a> <b><i> *      - A zero window was announced from us - zero window probing</i></b>
<a name="L5147" href="source/net/ipv4/tcp_input.c#L5147">5147</a> <b><i> *        is only handled properly in the slow path.</i></b>
<a name="L5148" href="source/net/ipv4/tcp_input.c#L5148">5148</a> <b><i> *      - Out of order segments arrived.</i></b>
<a name="L5149" href="source/net/ipv4/tcp_input.c#L5149">5149</a> <b><i> *      - Urgent data is expected.</i></b>
<a name="L5150" href="source/net/ipv4/tcp_input.c#L5150">5150</a> <b><i> *      - There is no buffer space left</i></b>
<a name="L5151" href="source/net/ipv4/tcp_input.c#L5151">5151</a> <b><i> *      - Unexpected TCP flags/window values/header lengths are received</i></b>
<a name="L5152" href="source/net/ipv4/tcp_input.c#L5152">5152</a> <b><i> *        (detected by checking the TCP header against pred_flags)</i></b>
<a name="L5153" href="source/net/ipv4/tcp_input.c#L5153">5153</a> <b><i> *      - Data is sent in both directions. Fast path only supports pure senders</i></b>
<a name="L5154" href="source/net/ipv4/tcp_input.c#L5154">5154</a> <b><i> *        or pure receivers (this means either the sequence number or the ack</i></b>
<a name="L5155" href="source/net/ipv4/tcp_input.c#L5155">5155</a> <b><i> *        value must stay constant)</i></b>
<a name="L5156" href="source/net/ipv4/tcp_input.c#L5156">5156</a> <b><i> *      - Unexpected TCP option.</i></b>
<a name="L5157" href="source/net/ipv4/tcp_input.c#L5157">5157</a> <b><i> *</i></b>
<a name="L5158" href="source/net/ipv4/tcp_input.c#L5158">5158</a> <b><i> *      When these conditions are not satisfied it drops into a standard</i></b>
<a name="L5159" href="source/net/ipv4/tcp_input.c#L5159">5159</a> <b><i> *      receive procedure patterned after RFC793 to handle all cases.</i></b>
<a name="L5160" href="source/net/ipv4/tcp_input.c#L5160">5160</a> <b><i> *      The first three cases are guaranteed by proper pred_flags setting,</i></b>
<a name="L5161" href="source/net/ipv4/tcp_input.c#L5161">5161</a> <b><i> *      the rest is checked inline. Fast processing is turned on in</i></b>
<a name="L5162" href="source/net/ipv4/tcp_input.c#L5162">5162</a> <b><i> *      tcp_data_queue when everything is OK.</i></b>
<a name="L5163" href="source/net/ipv4/tcp_input.c#L5163">5163</a> <b><i> */</i></b>
<a name="L5164" href="source/net/ipv4/tcp_input.c#L5164">5164</a> void <a href="ident?i=tcp_rcv_established">tcp_rcv_established</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
<a name="L5165" href="source/net/ipv4/tcp_input.c#L5165">5165</a>                          const struct <a href="ident?i=tcphdr">tcphdr</a> *<a href="ident?i=th">th</a>, unsigned int <a href="ident?i=len">len</a>)
<a name="L5166" href="source/net/ipv4/tcp_input.c#L5166">5166</a> {
<a name="L5167" href="source/net/ipv4/tcp_input.c#L5167">5167</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L5168" href="source/net/ipv4/tcp_input.c#L5168">5168</a> 
<a name="L5169" href="source/net/ipv4/tcp_input.c#L5169">5169</a>         if (<a href="ident?i=unlikely">unlikely</a>(!sk-&gt;sk_rx_dst))
<a name="L5170" href="source/net/ipv4/tcp_input.c#L5170">5170</a>                 <a href="ident?i=inet_csk">inet_csk</a>(sk)-&gt;icsk_af_ops-&gt;sk_rx_dst_set(sk, <a href="ident?i=skb">skb</a>);
<a name="L5171" href="source/net/ipv4/tcp_input.c#L5171">5171</a>         <b><i>/*</i></b>
<a name="L5172" href="source/net/ipv4/tcp_input.c#L5172">5172</a> <b><i>         *      Header prediction.</i></b>
<a name="L5173" href="source/net/ipv4/tcp_input.c#L5173">5173</a> <b><i>         *      The code loosely follows the one in the famous</i></b>
<a name="L5174" href="source/net/ipv4/tcp_input.c#L5174">5174</a> <b><i>         *      "30 instruction TCP receive" Van Jacobson mail.</i></b>
<a name="L5175" href="source/net/ipv4/tcp_input.c#L5175">5175</a> <b><i>         *</i></b>
<a name="L5176" href="source/net/ipv4/tcp_input.c#L5176">5176</a> <b><i>         *      Van's trick is to deposit buffers into socket queue</i></b>
<a name="L5177" href="source/net/ipv4/tcp_input.c#L5177">5177</a> <b><i>         *      on a device interrupt, to call tcp_recv function</i></b>
<a name="L5178" href="source/net/ipv4/tcp_input.c#L5178">5178</a> <b><i>         *      on the receive process context and checksum and copy</i></b>
<a name="L5179" href="source/net/ipv4/tcp_input.c#L5179">5179</a> <b><i>         *      the buffer to user space. smart...</i></b>
<a name="L5180" href="source/net/ipv4/tcp_input.c#L5180">5180</a> <b><i>         *</i></b>
<a name="L5181" href="source/net/ipv4/tcp_input.c#L5181">5181</a> <b><i>         *      Our current scheme is not silly either but we take the</i></b>
<a name="L5182" href="source/net/ipv4/tcp_input.c#L5182">5182</a> <b><i>         *      extra cost of the net_bh soft interrupt processing...</i></b>
<a name="L5183" href="source/net/ipv4/tcp_input.c#L5183">5183</a> <b><i>         *      We do checksum and copy also but from device to kernel.</i></b>
<a name="L5184" href="source/net/ipv4/tcp_input.c#L5184">5184</a> <b><i>         */</i></b>
<a name="L5185" href="source/net/ipv4/tcp_input.c#L5185">5185</a> 
<a name="L5186" href="source/net/ipv4/tcp_input.c#L5186">5186</a>         <a href="ident?i=tp">tp</a>-&gt;rx_opt.saw_tstamp = 0;
<a name="L5187" href="source/net/ipv4/tcp_input.c#L5187">5187</a> 
<a name="L5188" href="source/net/ipv4/tcp_input.c#L5188">5188</a>         <b><i>/*      pred_flags is 0xS?10 &lt;&lt; 16 + snd_wnd</i></b>
<a name="L5189" href="source/net/ipv4/tcp_input.c#L5189">5189</a> <b><i>         *      if header_prediction is to be made</i></b>
<a name="L5190" href="source/net/ipv4/tcp_input.c#L5190">5190</a> <b><i>         *      'S' will always be tp-&gt;tcp_header_len &gt;&gt; 2</i></b>
<a name="L5191" href="source/net/ipv4/tcp_input.c#L5191">5191</a> <b><i>         *      '?' will be 0 for the fast path, otherwise pred_flags is 0 to</i></b>
<a name="L5192" href="source/net/ipv4/tcp_input.c#L5192">5192</a> <b><i>         *  turn it off (when there are holes in the receive</i></b>
<a name="L5193" href="source/net/ipv4/tcp_input.c#L5193">5193</a> <b><i>         *       space for instance)</i></b>
<a name="L5194" href="source/net/ipv4/tcp_input.c#L5194">5194</a> <b><i>         *      PSH flag is ignored.</i></b>
<a name="L5195" href="source/net/ipv4/tcp_input.c#L5195">5195</a> <b><i>         */</i></b>
<a name="L5196" href="source/net/ipv4/tcp_input.c#L5196">5196</a> 
<a name="L5197" href="source/net/ipv4/tcp_input.c#L5197">5197</a>         if ((<a href="ident?i=tcp_flag_word">tcp_flag_word</a>(<a href="ident?i=th">th</a>) &amp; <a href="ident?i=TCP_HP_BITS">TCP_HP_BITS</a>) == <a href="ident?i=tp">tp</a>-&gt;pred_flags &amp;&amp;
<a name="L5198" href="source/net/ipv4/tcp_input.c#L5198">5198</a>             <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=seq">seq</a> == <a href="ident?i=tp">tp</a>-&gt;rcv_nxt &amp;&amp;
<a name="L5199" href="source/net/ipv4/tcp_input.c#L5199">5199</a>             !<a href="ident?i=after">after</a>(<a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;ack_seq, <a href="ident?i=tp">tp</a>-&gt;snd_nxt)) {
<a name="L5200" href="source/net/ipv4/tcp_input.c#L5200">5200</a>                 int tcp_header_len = <a href="ident?i=tp">tp</a>-&gt;tcp_header_len;
<a name="L5201" href="source/net/ipv4/tcp_input.c#L5201">5201</a> 
<a name="L5202" href="source/net/ipv4/tcp_input.c#L5202">5202</a>                 <b><i>/* Timestamp header prediction: tcp_header_len</i></b>
<a name="L5203" href="source/net/ipv4/tcp_input.c#L5203">5203</a> <b><i>                 * is automatically equal to th-&gt;doff*4 due to pred_flags</i></b>
<a name="L5204" href="source/net/ipv4/tcp_input.c#L5204">5204</a> <b><i>                 * match.</i></b>
<a name="L5205" href="source/net/ipv4/tcp_input.c#L5205">5205</a> <b><i>                 */</i></b>
<a name="L5206" href="source/net/ipv4/tcp_input.c#L5206">5206</a> 
<a name="L5207" href="source/net/ipv4/tcp_input.c#L5207">5207</a>                 <b><i>/* Check timestamp */</i></b>
<a name="L5208" href="source/net/ipv4/tcp_input.c#L5208">5208</a>                 if (tcp_header_len == sizeof(struct <a href="ident?i=tcphdr">tcphdr</a>) + <a href="ident?i=TCPOLEN_TSTAMP_ALIGNED">TCPOLEN_TSTAMP_ALIGNED</a>) {
<a name="L5209" href="source/net/ipv4/tcp_input.c#L5209">5209</a>                         <b><i>/* No? Slow path! */</i></b>
<a name="L5210" href="source/net/ipv4/tcp_input.c#L5210">5210</a>                         if (!<a href="ident?i=tcp_parse_aligned_timestamp">tcp_parse_aligned_timestamp</a>(<a href="ident?i=tp">tp</a>, <a href="ident?i=th">th</a>))
<a name="L5211" href="source/net/ipv4/tcp_input.c#L5211">5211</a>                                 goto slow_path;
<a name="L5212" href="source/net/ipv4/tcp_input.c#L5212">5212</a> 
<a name="L5213" href="source/net/ipv4/tcp_input.c#L5213">5213</a>                         <b><i>/* If PAWS failed, check it more carefully in slow path */</i></b>
<a name="L5214" href="source/net/ipv4/tcp_input.c#L5214">5214</a>                         if ((<a href="ident?i=s32">s32</a>)(<a href="ident?i=tp">tp</a>-&gt;rx_opt.rcv_tsval - <a href="ident?i=tp">tp</a>-&gt;rx_opt.ts_recent) &lt; 0)
<a name="L5215" href="source/net/ipv4/tcp_input.c#L5215">5215</a>                                 goto slow_path;
<a name="L5216" href="source/net/ipv4/tcp_input.c#L5216">5216</a> 
<a name="L5217" href="source/net/ipv4/tcp_input.c#L5217">5217</a>                         <b><i>/* DO NOT update ts_recent here, if checksum fails</i></b>
<a name="L5218" href="source/net/ipv4/tcp_input.c#L5218">5218</a> <b><i>                         * and timestamp was corrupted part, it will result</i></b>
<a name="L5219" href="source/net/ipv4/tcp_input.c#L5219">5219</a> <b><i>                         * in a hung connection since we will drop all</i></b>
<a name="L5220" href="source/net/ipv4/tcp_input.c#L5220">5220</a> <b><i>                         * future packets due to the PAWS test.</i></b>
<a name="L5221" href="source/net/ipv4/tcp_input.c#L5221">5221</a> <b><i>                         */</i></b>
<a name="L5222" href="source/net/ipv4/tcp_input.c#L5222">5222</a>                 }
<a name="L5223" href="source/net/ipv4/tcp_input.c#L5223">5223</a> 
<a name="L5224" href="source/net/ipv4/tcp_input.c#L5224">5224</a>                 if (<a href="ident?i=len">len</a> &lt;= tcp_header_len) {
<a name="L5225" href="source/net/ipv4/tcp_input.c#L5225">5225</a>                         <b><i>/* Bulk data transfer: sender */</i></b>
<a name="L5226" href="source/net/ipv4/tcp_input.c#L5226">5226</a>                         if (<a href="ident?i=len">len</a> == tcp_header_len) {
<a name="L5227" href="source/net/ipv4/tcp_input.c#L5227">5227</a>                                 <b><i>/* Predicted packet is in window by definition.</i></b>
<a name="L5228" href="source/net/ipv4/tcp_input.c#L5228">5228</a> <b><i>                                 * seq == rcv_nxt and rcv_wup &lt;= rcv_nxt.</i></b>
<a name="L5229" href="source/net/ipv4/tcp_input.c#L5229">5229</a> <b><i>                                 * Hence, check seq&lt;=rcv_wup reduces to:</i></b>
<a name="L5230" href="source/net/ipv4/tcp_input.c#L5230">5230</a> <b><i>                                 */</i></b>
<a name="L5231" href="source/net/ipv4/tcp_input.c#L5231">5231</a>                                 if (tcp_header_len ==
<a name="L5232" href="source/net/ipv4/tcp_input.c#L5232">5232</a>                                     (sizeof(struct <a href="ident?i=tcphdr">tcphdr</a>) + <a href="ident?i=TCPOLEN_TSTAMP_ALIGNED">TCPOLEN_TSTAMP_ALIGNED</a>) &amp;&amp;
<a name="L5233" href="source/net/ipv4/tcp_input.c#L5233">5233</a>                                     <a href="ident?i=tp">tp</a>-&gt;rcv_nxt == <a href="ident?i=tp">tp</a>-&gt;rcv_wup)
<a name="L5234" href="source/net/ipv4/tcp_input.c#L5234">5234</a>                                         <a href="ident?i=tcp_store_ts_recent">tcp_store_ts_recent</a>(<a href="ident?i=tp">tp</a>);
<a name="L5235" href="source/net/ipv4/tcp_input.c#L5235">5235</a> 
<a name="L5236" href="source/net/ipv4/tcp_input.c#L5236">5236</a>                                 <b><i>/* We know that such packets are checksummed</i></b>
<a name="L5237" href="source/net/ipv4/tcp_input.c#L5237">5237</a> <b><i>                                 * on entry.</i></b>
<a name="L5238" href="source/net/ipv4/tcp_input.c#L5238">5238</a> <b><i>                                 */</i></b>
<a name="L5239" href="source/net/ipv4/tcp_input.c#L5239">5239</a>                                 <a href="ident?i=tcp_ack">tcp_ack</a>(sk, <a href="ident?i=skb">skb</a>, 0);
<a name="L5240" href="source/net/ipv4/tcp_input.c#L5240">5240</a>                                 <a href="ident?i=__kfree_skb">__kfree_skb</a>(<a href="ident?i=skb">skb</a>);
<a name="L5241" href="source/net/ipv4/tcp_input.c#L5241">5241</a>                                 <a href="ident?i=tcp_data_snd_check">tcp_data_snd_check</a>(sk);
<a name="L5242" href="source/net/ipv4/tcp_input.c#L5242">5242</a>                                 return;
<a name="L5243" href="source/net/ipv4/tcp_input.c#L5243">5243</a>                         } else { <b><i>/* Header too small */</i></b>
<a name="L5244" href="source/net/ipv4/tcp_input.c#L5244">5244</a>                                 <a href="ident?i=TCP_INC_STATS_BH">TCP_INC_STATS_BH</a>(<a href="ident?i=sock_net">sock_net</a>(sk), TCP_MIB_INERRS);
<a name="L5245" href="source/net/ipv4/tcp_input.c#L5245">5245</a>                                 goto <a href="ident?i=discard">discard</a>;
<a name="L5246" href="source/net/ipv4/tcp_input.c#L5246">5246</a>                         }
<a name="L5247" href="source/net/ipv4/tcp_input.c#L5247">5247</a>                 } else {
<a name="L5248" href="source/net/ipv4/tcp_input.c#L5248">5248</a>                         int eaten = 0;
<a name="L5249" href="source/net/ipv4/tcp_input.c#L5249">5249</a>                         <a href="ident?i=bool">bool</a> fragstolen = <a href="ident?i=false">false</a>;
<a name="L5250" href="source/net/ipv4/tcp_input.c#L5250">5250</a> 
<a name="L5251" href="source/net/ipv4/tcp_input.c#L5251">5251</a>                         if (<a href="ident?i=tp">tp</a>-&gt;ucopy.<a href="ident?i=task">task</a> == <a href="ident?i=current">current</a> &amp;&amp;
<a name="L5252" href="source/net/ipv4/tcp_input.c#L5252">5252</a>                             <a href="ident?i=tp">tp</a>-&gt;copied_seq == <a href="ident?i=tp">tp</a>-&gt;rcv_nxt &amp;&amp;
<a name="L5253" href="source/net/ipv4/tcp_input.c#L5253">5253</a>                             <a href="ident?i=len">len</a> - tcp_header_len &lt;= <a href="ident?i=tp">tp</a>-&gt;ucopy.<a href="ident?i=len">len</a> &amp;&amp;
<a name="L5254" href="source/net/ipv4/tcp_input.c#L5254">5254</a>                             <a href="ident?i=sock_owned_by_user">sock_owned_by_user</a>(sk)) {
<a name="L5255" href="source/net/ipv4/tcp_input.c#L5255">5255</a>                                 <a href="ident?i=__set_current_state">__set_current_state</a>(<a href="ident?i=TASK_RUNNING">TASK_RUNNING</a>);
<a name="L5256" href="source/net/ipv4/tcp_input.c#L5256">5256</a> 
<a name="L5257" href="source/net/ipv4/tcp_input.c#L5257">5257</a>                                 if (!<a href="ident?i=tcp_copy_to_iovec">tcp_copy_to_iovec</a>(sk, <a href="ident?i=skb">skb</a>, tcp_header_len)) {
<a name="L5258" href="source/net/ipv4/tcp_input.c#L5258">5258</a>                                         <b><i>/* Predicted packet is in window by definition.</i></b>
<a name="L5259" href="source/net/ipv4/tcp_input.c#L5259">5259</a> <b><i>                                         * seq == rcv_nxt and rcv_wup &lt;= rcv_nxt.</i></b>
<a name="L5260" href="source/net/ipv4/tcp_input.c#L5260">5260</a> <b><i>                                         * Hence, check seq&lt;=rcv_wup reduces to:</i></b>
<a name="L5261" href="source/net/ipv4/tcp_input.c#L5261">5261</a> <b><i>                                         */</i></b>
<a name="L5262" href="source/net/ipv4/tcp_input.c#L5262">5262</a>                                         if (tcp_header_len ==
<a name="L5263" href="source/net/ipv4/tcp_input.c#L5263">5263</a>                                             (sizeof(struct <a href="ident?i=tcphdr">tcphdr</a>) +
<a name="L5264" href="source/net/ipv4/tcp_input.c#L5264">5264</a>                                              <a href="ident?i=TCPOLEN_TSTAMP_ALIGNED">TCPOLEN_TSTAMP_ALIGNED</a>) &amp;&amp;
<a name="L5265" href="source/net/ipv4/tcp_input.c#L5265">5265</a>                                             <a href="ident?i=tp">tp</a>-&gt;rcv_nxt == <a href="ident?i=tp">tp</a>-&gt;rcv_wup)
<a name="L5266" href="source/net/ipv4/tcp_input.c#L5266">5266</a>                                                 <a href="ident?i=tcp_store_ts_recent">tcp_store_ts_recent</a>(<a href="ident?i=tp">tp</a>);
<a name="L5267" href="source/net/ipv4/tcp_input.c#L5267">5267</a> 
<a name="L5268" href="source/net/ipv4/tcp_input.c#L5268">5268</a>                                         <a href="ident?i=tcp_rcv_rtt_measure_ts">tcp_rcv_rtt_measure_ts</a>(sk, <a href="ident?i=skb">skb</a>);
<a name="L5269" href="source/net/ipv4/tcp_input.c#L5269">5269</a> 
<a name="L5270" href="source/net/ipv4/tcp_input.c#L5270">5270</a>                                         <a href="ident?i=__skb_pull">__skb_pull</a>(<a href="ident?i=skb">skb</a>, tcp_header_len);
<a name="L5271" href="source/net/ipv4/tcp_input.c#L5271">5271</a>                                         <a href="ident?i=tcp_rcv_nxt_update">tcp_rcv_nxt_update</a>(<a href="ident?i=tp">tp</a>, <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;end_seq);
<a name="L5272" href="source/net/ipv4/tcp_input.c#L5272">5272</a>                                         <a href="ident?i=NET_INC_STATS_BH">NET_INC_STATS_BH</a>(<a href="ident?i=sock_net">sock_net</a>(sk), LINUX_MIB_TCPHPHITSTOUSER);
<a name="L5273" href="source/net/ipv4/tcp_input.c#L5273">5273</a>                                         eaten = 1;
<a name="L5274" href="source/net/ipv4/tcp_input.c#L5274">5274</a>                                 }
<a name="L5275" href="source/net/ipv4/tcp_input.c#L5275">5275</a>                         }
<a name="L5276" href="source/net/ipv4/tcp_input.c#L5276">5276</a>                         if (!eaten) {
<a name="L5277" href="source/net/ipv4/tcp_input.c#L5277">5277</a>                                 if (<a href="ident?i=tcp_checksum_complete_user">tcp_checksum_complete_user</a>(sk, <a href="ident?i=skb">skb</a>))
<a name="L5278" href="source/net/ipv4/tcp_input.c#L5278">5278</a>                                         goto csum_error;
<a name="L5279" href="source/net/ipv4/tcp_input.c#L5279">5279</a> 
<a name="L5280" href="source/net/ipv4/tcp_input.c#L5280">5280</a>                                 if ((int)<a href="ident?i=skb">skb</a>-&gt;truesize &gt; sk-&gt;sk_forward_alloc)
<a name="L5281" href="source/net/ipv4/tcp_input.c#L5281">5281</a>                                         goto step5;
<a name="L5282" href="source/net/ipv4/tcp_input.c#L5282">5282</a> 
<a name="L5283" href="source/net/ipv4/tcp_input.c#L5283">5283</a>                                 <b><i>/* Predicted packet is in window by definition.</i></b>
<a name="L5284" href="source/net/ipv4/tcp_input.c#L5284">5284</a> <b><i>                                 * seq == rcv_nxt and rcv_wup &lt;= rcv_nxt.</i></b>
<a name="L5285" href="source/net/ipv4/tcp_input.c#L5285">5285</a> <b><i>                                 * Hence, check seq&lt;=rcv_wup reduces to:</i></b>
<a name="L5286" href="source/net/ipv4/tcp_input.c#L5286">5286</a> <b><i>                                 */</i></b>
<a name="L5287" href="source/net/ipv4/tcp_input.c#L5287">5287</a>                                 if (tcp_header_len ==
<a name="L5288" href="source/net/ipv4/tcp_input.c#L5288">5288</a>                                     (sizeof(struct <a href="ident?i=tcphdr">tcphdr</a>) + <a href="ident?i=TCPOLEN_TSTAMP_ALIGNED">TCPOLEN_TSTAMP_ALIGNED</a>) &amp;&amp;
<a name="L5289" href="source/net/ipv4/tcp_input.c#L5289">5289</a>                                     <a href="ident?i=tp">tp</a>-&gt;rcv_nxt == <a href="ident?i=tp">tp</a>-&gt;rcv_wup)
<a name="L5290" href="source/net/ipv4/tcp_input.c#L5290">5290</a>                                         <a href="ident?i=tcp_store_ts_recent">tcp_store_ts_recent</a>(<a href="ident?i=tp">tp</a>);
<a name="L5291" href="source/net/ipv4/tcp_input.c#L5291">5291</a> 
<a name="L5292" href="source/net/ipv4/tcp_input.c#L5292">5292</a>                                 <a href="ident?i=tcp_rcv_rtt_measure_ts">tcp_rcv_rtt_measure_ts</a>(sk, <a href="ident?i=skb">skb</a>);
<a name="L5293" href="source/net/ipv4/tcp_input.c#L5293">5293</a> 
<a name="L5294" href="source/net/ipv4/tcp_input.c#L5294">5294</a>                                 <a href="ident?i=NET_INC_STATS_BH">NET_INC_STATS_BH</a>(<a href="ident?i=sock_net">sock_net</a>(sk), LINUX_MIB_TCPHPHITS);
<a name="L5295" href="source/net/ipv4/tcp_input.c#L5295">5295</a> 
<a name="L5296" href="source/net/ipv4/tcp_input.c#L5296">5296</a>                                 <b><i>/* Bulk data transfer: receiver */</i></b>
<a name="L5297" href="source/net/ipv4/tcp_input.c#L5297">5297</a>                                 eaten = <a href="ident?i=tcp_queue_rcv">tcp_queue_rcv</a>(sk, <a href="ident?i=skb">skb</a>, tcp_header_len,
<a name="L5298" href="source/net/ipv4/tcp_input.c#L5298">5298</a>                                                       &amp;fragstolen);
<a name="L5299" href="source/net/ipv4/tcp_input.c#L5299">5299</a>                         }
<a name="L5300" href="source/net/ipv4/tcp_input.c#L5300">5300</a> 
<a name="L5301" href="source/net/ipv4/tcp_input.c#L5301">5301</a>                         <a href="ident?i=tcp_event_data_recv">tcp_event_data_recv</a>(sk, <a href="ident?i=skb">skb</a>);
<a name="L5302" href="source/net/ipv4/tcp_input.c#L5302">5302</a> 
<a name="L5303" href="source/net/ipv4/tcp_input.c#L5303">5303</a>                         if (<a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;ack_seq != <a href="ident?i=tp">tp</a>-&gt;snd_una) {
<a name="L5304" href="source/net/ipv4/tcp_input.c#L5304">5304</a>                                 <b><i>/* Well, only one small jumplet in fast path... */</i></b>
<a name="L5305" href="source/net/ipv4/tcp_input.c#L5305">5305</a>                                 <a href="ident?i=tcp_ack">tcp_ack</a>(sk, <a href="ident?i=skb">skb</a>, <a href="ident?i=FLAG_DATA">FLAG_DATA</a>);
<a name="L5306" href="source/net/ipv4/tcp_input.c#L5306">5306</a>                                 <a href="ident?i=tcp_data_snd_check">tcp_data_snd_check</a>(sk);
<a name="L5307" href="source/net/ipv4/tcp_input.c#L5307">5307</a>                                 if (!<a href="ident?i=inet_csk_ack_scheduled">inet_csk_ack_scheduled</a>(sk))
<a name="L5308" href="source/net/ipv4/tcp_input.c#L5308">5308</a>                                         goto no_ack;
<a name="L5309" href="source/net/ipv4/tcp_input.c#L5309">5309</a>                         }
<a name="L5310" href="source/net/ipv4/tcp_input.c#L5310">5310</a> 
<a name="L5311" href="source/net/ipv4/tcp_input.c#L5311">5311</a>                         <a href="ident?i=__tcp_ack_snd_check">__tcp_ack_snd_check</a>(sk, 0);
<a name="L5312" href="source/net/ipv4/tcp_input.c#L5312">5312</a> no_ack:
<a name="L5313" href="source/net/ipv4/tcp_input.c#L5313">5313</a>                         if (eaten)
<a name="L5314" href="source/net/ipv4/tcp_input.c#L5314">5314</a>                                 <a href="ident?i=kfree_skb_partial">kfree_skb_partial</a>(<a href="ident?i=skb">skb</a>, fragstolen);
<a name="L5315" href="source/net/ipv4/tcp_input.c#L5315">5315</a>                         sk-&gt;sk_data_ready(sk);
<a name="L5316" href="source/net/ipv4/tcp_input.c#L5316">5316</a>                         return;
<a name="L5317" href="source/net/ipv4/tcp_input.c#L5317">5317</a>                 }
<a name="L5318" href="source/net/ipv4/tcp_input.c#L5318">5318</a>         }
<a name="L5319" href="source/net/ipv4/tcp_input.c#L5319">5319</a> 
<a name="L5320" href="source/net/ipv4/tcp_input.c#L5320">5320</a> slow_path:
<a name="L5321" href="source/net/ipv4/tcp_input.c#L5321">5321</a>         if (<a href="ident?i=len">len</a> &lt; (<a href="ident?i=th">th</a>-&gt;doff &lt;&lt; 2) || <a href="ident?i=tcp_checksum_complete_user">tcp_checksum_complete_user</a>(sk, <a href="ident?i=skb">skb</a>))
<a name="L5322" href="source/net/ipv4/tcp_input.c#L5322">5322</a>                 goto csum_error;
<a name="L5323" href="source/net/ipv4/tcp_input.c#L5323">5323</a> 
<a name="L5324" href="source/net/ipv4/tcp_input.c#L5324">5324</a>         if (!<a href="ident?i=th">th</a>-&gt;ack &amp;&amp; !<a href="ident?i=th">th</a>-&gt;rst &amp;&amp; !<a href="ident?i=th">th</a>-&gt;syn)
<a name="L5325" href="source/net/ipv4/tcp_input.c#L5325">5325</a>                 goto <a href="ident?i=discard">discard</a>;
<a name="L5326" href="source/net/ipv4/tcp_input.c#L5326">5326</a> 
<a name="L5327" href="source/net/ipv4/tcp_input.c#L5327">5327</a>         <b><i>/*</i></b>
<a name="L5328" href="source/net/ipv4/tcp_input.c#L5328">5328</a> <b><i>         *      Standard slow path.</i></b>
<a name="L5329" href="source/net/ipv4/tcp_input.c#L5329">5329</a> <b><i>         */</i></b>
<a name="L5330" href="source/net/ipv4/tcp_input.c#L5330">5330</a> 
<a name="L5331" href="source/net/ipv4/tcp_input.c#L5331">5331</a>         if (!<a href="ident?i=tcp_validate_incoming">tcp_validate_incoming</a>(sk, <a href="ident?i=skb">skb</a>, <a href="ident?i=th">th</a>, 1))
<a name="L5332" href="source/net/ipv4/tcp_input.c#L5332">5332</a>                 return;
<a name="L5333" href="source/net/ipv4/tcp_input.c#L5333">5333</a> 
<a name="L5334" href="source/net/ipv4/tcp_input.c#L5334">5334</a> step5:
<a name="L5335" href="source/net/ipv4/tcp_input.c#L5335">5335</a>         if (<a href="ident?i=tcp_ack">tcp_ack</a>(sk, <a href="ident?i=skb">skb</a>, <a href="ident?i=FLAG_SLOWPATH">FLAG_SLOWPATH</a> | <a href="ident?i=FLAG_UPDATE_TS_RECENT">FLAG_UPDATE_TS_RECENT</a>) &lt; 0)
<a name="L5336" href="source/net/ipv4/tcp_input.c#L5336">5336</a>                 goto <a href="ident?i=discard">discard</a>;
<a name="L5337" href="source/net/ipv4/tcp_input.c#L5337">5337</a> 
<a name="L5338" href="source/net/ipv4/tcp_input.c#L5338">5338</a>         <a href="ident?i=tcp_rcv_rtt_measure_ts">tcp_rcv_rtt_measure_ts</a>(sk, <a href="ident?i=skb">skb</a>);
<a name="L5339" href="source/net/ipv4/tcp_input.c#L5339">5339</a> 
<a name="L5340" href="source/net/ipv4/tcp_input.c#L5340">5340</a>         <b><i>/* Process urgent data. */</i></b>
<a name="L5341" href="source/net/ipv4/tcp_input.c#L5341">5341</a>         <a href="ident?i=tcp_urg">tcp_urg</a>(sk, <a href="ident?i=skb">skb</a>, <a href="ident?i=th">th</a>);
<a name="L5342" href="source/net/ipv4/tcp_input.c#L5342">5342</a> 
<a name="L5343" href="source/net/ipv4/tcp_input.c#L5343">5343</a>         <b><i>/* step 7: process the segment text */</i></b>
<a name="L5344" href="source/net/ipv4/tcp_input.c#L5344">5344</a>         <a href="ident?i=tcp_data_queue">tcp_data_queue</a>(sk, <a href="ident?i=skb">skb</a>);
<a name="L5345" href="source/net/ipv4/tcp_input.c#L5345">5345</a> 
<a name="L5346" href="source/net/ipv4/tcp_input.c#L5346">5346</a>         <a href="ident?i=tcp_data_snd_check">tcp_data_snd_check</a>(sk);
<a name="L5347" href="source/net/ipv4/tcp_input.c#L5347">5347</a>         <a href="ident?i=tcp_ack_snd_check">tcp_ack_snd_check</a>(sk);
<a name="L5348" href="source/net/ipv4/tcp_input.c#L5348">5348</a>         return;
<a name="L5349" href="source/net/ipv4/tcp_input.c#L5349">5349</a> 
<a name="L5350" href="source/net/ipv4/tcp_input.c#L5350">5350</a> csum_error:
<a name="L5351" href="source/net/ipv4/tcp_input.c#L5351">5351</a>         <a href="ident?i=TCP_INC_STATS_BH">TCP_INC_STATS_BH</a>(<a href="ident?i=sock_net">sock_net</a>(sk), TCP_MIB_CSUMERRORS);
<a name="L5352" href="source/net/ipv4/tcp_input.c#L5352">5352</a>         <a href="ident?i=TCP_INC_STATS_BH">TCP_INC_STATS_BH</a>(<a href="ident?i=sock_net">sock_net</a>(sk), TCP_MIB_INERRS);
<a name="L5353" href="source/net/ipv4/tcp_input.c#L5353">5353</a> 
<a name="L5354" href="source/net/ipv4/tcp_input.c#L5354">5354</a> <a href="ident?i=discard">discard</a>:
<a name="L5355" href="source/net/ipv4/tcp_input.c#L5355">5355</a>         <a href="ident?i=__kfree_skb">__kfree_skb</a>(<a href="ident?i=skb">skb</a>);
<a name="L5356" href="source/net/ipv4/tcp_input.c#L5356">5356</a> }
<a name="L5357" href="source/net/ipv4/tcp_input.c#L5357">5357</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=tcp_rcv_established">tcp_rcv_established</a>);
<a name="L5358" href="source/net/ipv4/tcp_input.c#L5358">5358</a> 
<a name="L5359" href="source/net/ipv4/tcp_input.c#L5359">5359</a> void <a href="ident?i=tcp_finish_connect">tcp_finish_connect</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L5360" href="source/net/ipv4/tcp_input.c#L5360">5360</a> {
<a name="L5361" href="source/net/ipv4/tcp_input.c#L5361">5361</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L5362" href="source/net/ipv4/tcp_input.c#L5362">5362</a>         struct <a href="ident?i=inet_connection_sock">inet_connection_sock</a> *icsk = <a href="ident?i=inet_csk">inet_csk</a>(sk);
<a name="L5363" href="source/net/ipv4/tcp_input.c#L5363">5363</a> 
<a name="L5364" href="source/net/ipv4/tcp_input.c#L5364">5364</a>         <a href="ident?i=tcp_set_state">tcp_set_state</a>(sk, TCP_ESTABLISHED);
<a name="L5365" href="source/net/ipv4/tcp_input.c#L5365">5365</a> 
<a name="L5366" href="source/net/ipv4/tcp_input.c#L5366">5366</a>         if (<a href="ident?i=skb">skb</a>) {
<a name="L5367" href="source/net/ipv4/tcp_input.c#L5367">5367</a>                 icsk-&gt;icsk_af_ops-&gt;sk_rx_dst_set(sk, <a href="ident?i=skb">skb</a>);
<a name="L5368" href="source/net/ipv4/tcp_input.c#L5368">5368</a>                 <a href="ident?i=security_inet_conn_established">security_inet_conn_established</a>(sk, <a href="ident?i=skb">skb</a>);
<a name="L5369" href="source/net/ipv4/tcp_input.c#L5369">5369</a>         }
<a name="L5370" href="source/net/ipv4/tcp_input.c#L5370">5370</a> 
<a name="L5371" href="source/net/ipv4/tcp_input.c#L5371">5371</a>         <b><i>/* Make sure socket is routed, for correct metrics.  */</i></b>
<a name="L5372" href="source/net/ipv4/tcp_input.c#L5372">5372</a>         icsk-&gt;icsk_af_ops-&gt;rebuild_header(sk);
<a name="L5373" href="source/net/ipv4/tcp_input.c#L5373">5373</a> 
<a name="L5374" href="source/net/ipv4/tcp_input.c#L5374">5374</a>         <a href="ident?i=tcp_init_metrics">tcp_init_metrics</a>(sk);
<a name="L5375" href="source/net/ipv4/tcp_input.c#L5375">5375</a> 
<a name="L5376" href="source/net/ipv4/tcp_input.c#L5376">5376</a>         <a href="ident?i=tcp_init_congestion_control">tcp_init_congestion_control</a>(sk);
<a name="L5377" href="source/net/ipv4/tcp_input.c#L5377">5377</a> 
<a name="L5378" href="source/net/ipv4/tcp_input.c#L5378">5378</a>         <b><i>/* Prevent spurious tcp_cwnd_restart() on first data</i></b>
<a name="L5379" href="source/net/ipv4/tcp_input.c#L5379">5379</a> <b><i>         * packet.</i></b>
<a name="L5380" href="source/net/ipv4/tcp_input.c#L5380">5380</a> <b><i>         */</i></b>
<a name="L5381" href="source/net/ipv4/tcp_input.c#L5381">5381</a>         <a href="ident?i=tp">tp</a>-&gt;lsndtime = <a href="ident?i=tcp_time_stamp">tcp_time_stamp</a>;
<a name="L5382" href="source/net/ipv4/tcp_input.c#L5382">5382</a> 
<a name="L5383" href="source/net/ipv4/tcp_input.c#L5383">5383</a>         <a href="ident?i=tcp_init_buffer_space">tcp_init_buffer_space</a>(sk);
<a name="L5384" href="source/net/ipv4/tcp_input.c#L5384">5384</a> 
<a name="L5385" href="source/net/ipv4/tcp_input.c#L5385">5385</a>         if (<a href="ident?i=sock_flag">sock_flag</a>(sk, SOCK_KEEPOPEN))
<a name="L5386" href="source/net/ipv4/tcp_input.c#L5386">5386</a>                 <a href="ident?i=inet_csk_reset_keepalive_timer">inet_csk_reset_keepalive_timer</a>(sk, <a href="ident?i=keepalive_time_when">keepalive_time_when</a>(<a href="ident?i=tp">tp</a>));
<a name="L5387" href="source/net/ipv4/tcp_input.c#L5387">5387</a> 
<a name="L5388" href="source/net/ipv4/tcp_input.c#L5388">5388</a>         if (!<a href="ident?i=tp">tp</a>-&gt;rx_opt.snd_wscale)
<a name="L5389" href="source/net/ipv4/tcp_input.c#L5389">5389</a>                 <a href="ident?i=__tcp_fast_path_on">__tcp_fast_path_on</a>(<a href="ident?i=tp">tp</a>, <a href="ident?i=tp">tp</a>-&gt;snd_wnd);
<a name="L5390" href="source/net/ipv4/tcp_input.c#L5390">5390</a>         else
<a name="L5391" href="source/net/ipv4/tcp_input.c#L5391">5391</a>                 <a href="ident?i=tp">tp</a>-&gt;pred_flags = 0;
<a name="L5392" href="source/net/ipv4/tcp_input.c#L5392">5392</a> 
<a name="L5393" href="source/net/ipv4/tcp_input.c#L5393">5393</a>         if (!<a href="ident?i=sock_flag">sock_flag</a>(sk, SOCK_DEAD)) {
<a name="L5394" href="source/net/ipv4/tcp_input.c#L5394">5394</a>                 sk-&gt;sk_state_change(sk);
<a name="L5395" href="source/net/ipv4/tcp_input.c#L5395">5395</a>                 <a href="ident?i=sk_wake_async">sk_wake_async</a>(sk, SOCK_WAKE_IO, <a href="ident?i=POLL_OUT">POLL_OUT</a>);
<a name="L5396" href="source/net/ipv4/tcp_input.c#L5396">5396</a>         }
<a name="L5397" href="source/net/ipv4/tcp_input.c#L5397">5397</a> }
<a name="L5398" href="source/net/ipv4/tcp_input.c#L5398">5398</a> 
<a name="L5399" href="source/net/ipv4/tcp_input.c#L5399">5399</a> static <a href="ident?i=bool">bool</a> <a href="ident?i=tcp_rcv_fastopen_synack">tcp_rcv_fastopen_synack</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=sk_buff">sk_buff</a> *synack,
<a name="L5400" href="source/net/ipv4/tcp_input.c#L5400">5400</a>                                     struct <a href="ident?i=tcp_fastopen_cookie">tcp_fastopen_cookie</a> *cookie)
<a name="L5401" href="source/net/ipv4/tcp_input.c#L5401">5401</a> {
<a name="L5402" href="source/net/ipv4/tcp_input.c#L5402">5402</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L5403" href="source/net/ipv4/tcp_input.c#L5403">5403</a>         struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=data">data</a> = <a href="ident?i=tp">tp</a>-&gt;syn_data ? <a href="ident?i=tcp_write_queue_head">tcp_write_queue_head</a>(sk) : <a href="ident?i=NULL">NULL</a>;
<a name="L5404" href="source/net/ipv4/tcp_input.c#L5404">5404</a>         <a href="ident?i=u16">u16</a> mss = <a href="ident?i=tp">tp</a>-&gt;rx_opt.mss_clamp, try_exp = 0;
<a name="L5405" href="source/net/ipv4/tcp_input.c#L5405">5405</a>         <a href="ident?i=bool">bool</a> syn_drop = <a href="ident?i=false">false</a>;
<a name="L5406" href="source/net/ipv4/tcp_input.c#L5406">5406</a> 
<a name="L5407" href="source/net/ipv4/tcp_input.c#L5407">5407</a>         if (mss == <a href="ident?i=tp">tp</a>-&gt;rx_opt.user_mss) {
<a name="L5408" href="source/net/ipv4/tcp_input.c#L5408">5408</a>                 struct <a href="ident?i=tcp_options_received">tcp_options_received</a> opt;
<a name="L5409" href="source/net/ipv4/tcp_input.c#L5409">5409</a> 
<a name="L5410" href="source/net/ipv4/tcp_input.c#L5410">5410</a>                 <b><i>/* Get original SYNACK MSS value if user MSS sets mss_clamp */</i></b>
<a name="L5411" href="source/net/ipv4/tcp_input.c#L5411">5411</a>                 <a href="ident?i=tcp_clear_options">tcp_clear_options</a>(&amp;opt);
<a name="L5412" href="source/net/ipv4/tcp_input.c#L5412">5412</a>                 opt.user_mss = opt.mss_clamp = 0;
<a name="L5413" href="source/net/ipv4/tcp_input.c#L5413">5413</a>                 <a href="ident?i=tcp_parse_options">tcp_parse_options</a>(synack, &amp;opt, 0, <a href="ident?i=NULL">NULL</a>);
<a name="L5414" href="source/net/ipv4/tcp_input.c#L5414">5414</a>                 mss = opt.mss_clamp;
<a name="L5415" href="source/net/ipv4/tcp_input.c#L5415">5415</a>         }
<a name="L5416" href="source/net/ipv4/tcp_input.c#L5416">5416</a> 
<a name="L5417" href="source/net/ipv4/tcp_input.c#L5417">5417</a>         if (!<a href="ident?i=tp">tp</a>-&gt;syn_fastopen) {
<a name="L5418" href="source/net/ipv4/tcp_input.c#L5418">5418</a>                 <b><i>/* Ignore an unsolicited cookie */</i></b>
<a name="L5419" href="source/net/ipv4/tcp_input.c#L5419">5419</a>                 cookie-&gt;<a href="ident?i=len">len</a> = -1;
<a name="L5420" href="source/net/ipv4/tcp_input.c#L5420">5420</a>         } else if (<a href="ident?i=tp">tp</a>-&gt;total_retrans) {
<a name="L5421" href="source/net/ipv4/tcp_input.c#L5421">5421</a>                 <b><i>/* SYN timed out and the SYN-ACK neither has a cookie nor</i></b>
<a name="L5422" href="source/net/ipv4/tcp_input.c#L5422">5422</a> <b><i>                 * acknowledges data. Presumably the remote received only</i></b>
<a name="L5423" href="source/net/ipv4/tcp_input.c#L5423">5423</a> <b><i>                 * the retransmitted (regular) SYNs: either the original</i></b>
<a name="L5424" href="source/net/ipv4/tcp_input.c#L5424">5424</a> <b><i>                 * SYN-data or the corresponding SYN-ACK was dropped.</i></b>
<a name="L5425" href="source/net/ipv4/tcp_input.c#L5425">5425</a> <b><i>                 */</i></b>
<a name="L5426" href="source/net/ipv4/tcp_input.c#L5426">5426</a>                 syn_drop = (cookie-&gt;<a href="ident?i=len">len</a> &lt; 0 &amp;&amp; <a href="ident?i=data">data</a>);
<a name="L5427" href="source/net/ipv4/tcp_input.c#L5427">5427</a>         } else if (cookie-&gt;<a href="ident?i=len">len</a> &lt; 0 &amp;&amp; !<a href="ident?i=tp">tp</a>-&gt;syn_data) {
<a name="L5428" href="source/net/ipv4/tcp_input.c#L5428">5428</a>                 <b><i>/* We requested a cookie but didn't get it. If we did not use</i></b>
<a name="L5429" href="source/net/ipv4/tcp_input.c#L5429">5429</a> <b><i>                 * the (old) exp opt format then try so next time (try_exp=1).</i></b>
<a name="L5430" href="source/net/ipv4/tcp_input.c#L5430">5430</a> <b><i>                 * Otherwise we go back to use the RFC7413 opt (try_exp=2).</i></b>
<a name="L5431" href="source/net/ipv4/tcp_input.c#L5431">5431</a> <b><i>                 */</i></b>
<a name="L5432" href="source/net/ipv4/tcp_input.c#L5432">5432</a>                 try_exp = <a href="ident?i=tp">tp</a>-&gt;syn_fastopen_exp ? 2 : 1;
<a name="L5433" href="source/net/ipv4/tcp_input.c#L5433">5433</a>         }
<a name="L5434" href="source/net/ipv4/tcp_input.c#L5434">5434</a> 
<a name="L5435" href="source/net/ipv4/tcp_input.c#L5435">5435</a>         <a href="ident?i=tcp_fastopen_cache_set">tcp_fastopen_cache_set</a>(sk, mss, cookie, syn_drop, try_exp);
<a name="L5436" href="source/net/ipv4/tcp_input.c#L5436">5436</a> 
<a name="L5437" href="source/net/ipv4/tcp_input.c#L5437">5437</a>         if (<a href="ident?i=data">data</a>) { <b><i>/* Retransmit unacked data in SYN */</i></b>
<a name="L5438" href="source/net/ipv4/tcp_input.c#L5438">5438</a>                 <a href="ident?i=tcp_for_write_queue_from">tcp_for_write_queue_from</a>(<a href="ident?i=data">data</a>, sk) {
<a name="L5439" href="source/net/ipv4/tcp_input.c#L5439">5439</a>                         if (<a href="ident?i=data">data</a> == <a href="ident?i=tcp_send_head">tcp_send_head</a>(sk) ||
<a name="L5440" href="source/net/ipv4/tcp_input.c#L5440">5440</a>                             <a href="ident?i=__tcp_retransmit_skb">__tcp_retransmit_skb</a>(sk, <a href="ident?i=data">data</a>))
<a name="L5441" href="source/net/ipv4/tcp_input.c#L5441">5441</a>                                 break;
<a name="L5442" href="source/net/ipv4/tcp_input.c#L5442">5442</a>                 }
<a name="L5443" href="source/net/ipv4/tcp_input.c#L5443">5443</a>                 <a href="ident?i=tcp_rearm_rto">tcp_rearm_rto</a>(sk);
<a name="L5444" href="source/net/ipv4/tcp_input.c#L5444">5444</a>                 <a href="ident?i=NET_INC_STATS_BH">NET_INC_STATS_BH</a>(<a href="ident?i=sock_net">sock_net</a>(sk), LINUX_MIB_TCPFASTOPENACTIVEFAIL);
<a name="L5445" href="source/net/ipv4/tcp_input.c#L5445">5445</a>                 return <a href="ident?i=true">true</a>;
<a name="L5446" href="source/net/ipv4/tcp_input.c#L5446">5446</a>         }
<a name="L5447" href="source/net/ipv4/tcp_input.c#L5447">5447</a>         <a href="ident?i=tp">tp</a>-&gt;syn_data_acked = <a href="ident?i=tp">tp</a>-&gt;syn_data;
<a name="L5448" href="source/net/ipv4/tcp_input.c#L5448">5448</a>         if (<a href="ident?i=tp">tp</a>-&gt;syn_data_acked)
<a name="L5449" href="source/net/ipv4/tcp_input.c#L5449">5449</a>                 <a href="ident?i=NET_INC_STATS_BH">NET_INC_STATS_BH</a>(<a href="ident?i=sock_net">sock_net</a>(sk), LINUX_MIB_TCPFASTOPENACTIVE);
<a name="L5450" href="source/net/ipv4/tcp_input.c#L5450">5450</a>         return <a href="ident?i=false">false</a>;
<a name="L5451" href="source/net/ipv4/tcp_input.c#L5451">5451</a> }
<a name="L5452" href="source/net/ipv4/tcp_input.c#L5452">5452</a> 
<a name="L5453" href="source/net/ipv4/tcp_input.c#L5453">5453</a> static int <a href="ident?i=tcp_rcv_synsent_state_process">tcp_rcv_synsent_state_process</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
<a name="L5454" href="source/net/ipv4/tcp_input.c#L5454">5454</a>                                          const struct <a href="ident?i=tcphdr">tcphdr</a> *<a href="ident?i=th">th</a>, unsigned int <a href="ident?i=len">len</a>)
<a name="L5455" href="source/net/ipv4/tcp_input.c#L5455">5455</a> {
<a name="L5456" href="source/net/ipv4/tcp_input.c#L5456">5456</a>         struct <a href="ident?i=inet_connection_sock">inet_connection_sock</a> *icsk = <a href="ident?i=inet_csk">inet_csk</a>(sk);
<a name="L5457" href="source/net/ipv4/tcp_input.c#L5457">5457</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L5458" href="source/net/ipv4/tcp_input.c#L5458">5458</a>         struct <a href="ident?i=tcp_fastopen_cookie">tcp_fastopen_cookie</a> foc = { .<a href="ident?i=len">len</a> = -1 };
<a name="L5459" href="source/net/ipv4/tcp_input.c#L5459">5459</a>         int saved_clamp = <a href="ident?i=tp">tp</a>-&gt;rx_opt.mss_clamp;
<a name="L5460" href="source/net/ipv4/tcp_input.c#L5460">5460</a> 
<a name="L5461" href="source/net/ipv4/tcp_input.c#L5461">5461</a>         <a href="ident?i=tcp_parse_options">tcp_parse_options</a>(<a href="ident?i=skb">skb</a>, &amp;<a href="ident?i=tp">tp</a>-&gt;rx_opt, 0, &amp;foc);
<a name="L5462" href="source/net/ipv4/tcp_input.c#L5462">5462</a>         if (<a href="ident?i=tp">tp</a>-&gt;rx_opt.saw_tstamp &amp;&amp; <a href="ident?i=tp">tp</a>-&gt;rx_opt.rcv_tsecr)
<a name="L5463" href="source/net/ipv4/tcp_input.c#L5463">5463</a>                 <a href="ident?i=tp">tp</a>-&gt;rx_opt.rcv_tsecr -= <a href="ident?i=tp">tp</a>-&gt;tsoffset;
<a name="L5464" href="source/net/ipv4/tcp_input.c#L5464">5464</a> 
<a name="L5465" href="source/net/ipv4/tcp_input.c#L5465">5465</a>         if (<a href="ident?i=th">th</a>-&gt;ack) {
<a name="L5466" href="source/net/ipv4/tcp_input.c#L5466">5466</a>                 <b><i>/* rfc793:</i></b>
<a name="L5467" href="source/net/ipv4/tcp_input.c#L5467">5467</a> <b><i>                 * "If the state is SYN-SENT then</i></b>
<a name="L5468" href="source/net/ipv4/tcp_input.c#L5468">5468</a> <b><i>                 *    first check the ACK bit</i></b>
<a name="L5469" href="source/net/ipv4/tcp_input.c#L5469">5469</a> <b><i>                 *      If the ACK bit is set</i></b>
<a name="L5470" href="source/net/ipv4/tcp_input.c#L5470">5470</a> <b><i>                 *        If SEG.ACK =&lt; ISS, or SEG.ACK &gt; SND.NXT, send</i></b>
<a name="L5471" href="source/net/ipv4/tcp_input.c#L5471">5471</a> <b><i>                 *        a reset (unless the RST bit is set, if so drop</i></b>
<a name="L5472" href="source/net/ipv4/tcp_input.c#L5472">5472</a> <b><i>                 *        the segment and return)"</i></b>
<a name="L5473" href="source/net/ipv4/tcp_input.c#L5473">5473</a> <b><i>                 */</i></b>
<a name="L5474" href="source/net/ipv4/tcp_input.c#L5474">5474</a>                 if (!<a href="ident?i=after">after</a>(<a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;ack_seq, <a href="ident?i=tp">tp</a>-&gt;snd_una) ||
<a name="L5475" href="source/net/ipv4/tcp_input.c#L5475">5475</a>                     <a href="ident?i=after">after</a>(<a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;ack_seq, <a href="ident?i=tp">tp</a>-&gt;snd_nxt))
<a name="L5476" href="source/net/ipv4/tcp_input.c#L5476">5476</a>                         goto reset_and_undo;
<a name="L5477" href="source/net/ipv4/tcp_input.c#L5477">5477</a> 
<a name="L5478" href="source/net/ipv4/tcp_input.c#L5478">5478</a>                 if (<a href="ident?i=tp">tp</a>-&gt;rx_opt.saw_tstamp &amp;&amp; <a href="ident?i=tp">tp</a>-&gt;rx_opt.rcv_tsecr &amp;&amp;
<a name="L5479" href="source/net/ipv4/tcp_input.c#L5479">5479</a>                     !<a href="ident?i=between">between</a>(<a href="ident?i=tp">tp</a>-&gt;rx_opt.rcv_tsecr, <a href="ident?i=tp">tp</a>-&gt;retrans_stamp,
<a name="L5480" href="source/net/ipv4/tcp_input.c#L5480">5480</a>                              <a href="ident?i=tcp_time_stamp">tcp_time_stamp</a>)) {
<a name="L5481" href="source/net/ipv4/tcp_input.c#L5481">5481</a>                         <a href="ident?i=NET_INC_STATS_BH">NET_INC_STATS_BH</a>(<a href="ident?i=sock_net">sock_net</a>(sk), LINUX_MIB_PAWSACTIVEREJECTED);
<a name="L5482" href="source/net/ipv4/tcp_input.c#L5482">5482</a>                         goto reset_and_undo;
<a name="L5483" href="source/net/ipv4/tcp_input.c#L5483">5483</a>                 }
<a name="L5484" href="source/net/ipv4/tcp_input.c#L5484">5484</a> 
<a name="L5485" href="source/net/ipv4/tcp_input.c#L5485">5485</a>                 <b><i>/* Now ACK is acceptable.</i></b>
<a name="L5486" href="source/net/ipv4/tcp_input.c#L5486">5486</a> <b><i>                 *</i></b>
<a name="L5487" href="source/net/ipv4/tcp_input.c#L5487">5487</a> <b><i>                 * "If the RST bit is set</i></b>
<a name="L5488" href="source/net/ipv4/tcp_input.c#L5488">5488</a> <b><i>                 *    If the ACK was acceptable then signal the user "error:</i></b>
<a name="L5489" href="source/net/ipv4/tcp_input.c#L5489">5489</a> <b><i>                 *    connection reset", drop the segment, enter CLOSED state,</i></b>
<a name="L5490" href="source/net/ipv4/tcp_input.c#L5490">5490</a> <b><i>                 *    delete TCB, and return."</i></b>
<a name="L5491" href="source/net/ipv4/tcp_input.c#L5491">5491</a> <b><i>                 */</i></b>
<a name="L5492" href="source/net/ipv4/tcp_input.c#L5492">5492</a> 
<a name="L5493" href="source/net/ipv4/tcp_input.c#L5493">5493</a>                 if (<a href="ident?i=th">th</a>-&gt;rst) {
<a name="L5494" href="source/net/ipv4/tcp_input.c#L5494">5494</a>                         <a href="ident?i=tcp_reset">tcp_reset</a>(sk);
<a name="L5495" href="source/net/ipv4/tcp_input.c#L5495">5495</a>                         goto <a href="ident?i=discard">discard</a>;
<a name="L5496" href="source/net/ipv4/tcp_input.c#L5496">5496</a>                 }
<a name="L5497" href="source/net/ipv4/tcp_input.c#L5497">5497</a> 
<a name="L5498" href="source/net/ipv4/tcp_input.c#L5498">5498</a>                 <b><i>/* rfc793:</i></b>
<a name="L5499" href="source/net/ipv4/tcp_input.c#L5499">5499</a> <b><i>                 *   "fifth, if neither of the SYN or RST bits is set then</i></b>
<a name="L5500" href="source/net/ipv4/tcp_input.c#L5500">5500</a> <b><i>                 *    drop the segment and return."</i></b>
<a name="L5501" href="source/net/ipv4/tcp_input.c#L5501">5501</a> <b><i>                 *</i></b>
<a name="L5502" href="source/net/ipv4/tcp_input.c#L5502">5502</a> <b><i>                 *    See note below!</i></b>
<a name="L5503" href="source/net/ipv4/tcp_input.c#L5503">5503</a> <b><i>                 *                                        --ANK(990513)</i></b>
<a name="L5504" href="source/net/ipv4/tcp_input.c#L5504">5504</a> <b><i>                 */</i></b>
<a name="L5505" href="source/net/ipv4/tcp_input.c#L5505">5505</a>                 if (!<a href="ident?i=th">th</a>-&gt;syn)
<a name="L5506" href="source/net/ipv4/tcp_input.c#L5506">5506</a>                         goto discard_and_undo;
<a name="L5507" href="source/net/ipv4/tcp_input.c#L5507">5507</a> 
<a name="L5508" href="source/net/ipv4/tcp_input.c#L5508">5508</a>                 <b><i>/* rfc793:</i></b>
<a name="L5509" href="source/net/ipv4/tcp_input.c#L5509">5509</a> <b><i>                 *   "If the SYN bit is on ...</i></b>
<a name="L5510" href="source/net/ipv4/tcp_input.c#L5510">5510</a> <b><i>                 *    are acceptable then ...</i></b>
<a name="L5511" href="source/net/ipv4/tcp_input.c#L5511">5511</a> <b><i>                 *    (our SYN has been ACKed), change the connection</i></b>
<a name="L5512" href="source/net/ipv4/tcp_input.c#L5512">5512</a> <b><i>                 *    state to ESTABLISHED..."</i></b>
<a name="L5513" href="source/net/ipv4/tcp_input.c#L5513">5513</a> <b><i>                 */</i></b>
<a name="L5514" href="source/net/ipv4/tcp_input.c#L5514">5514</a> 
<a name="L5515" href="source/net/ipv4/tcp_input.c#L5515">5515</a>                 <a href="ident?i=tcp_ecn_rcv_synack">tcp_ecn_rcv_synack</a>(<a href="ident?i=tp">tp</a>, <a href="ident?i=th">th</a>);
<a name="L5516" href="source/net/ipv4/tcp_input.c#L5516">5516</a> 
<a name="L5517" href="source/net/ipv4/tcp_input.c#L5517">5517</a>                 <a href="ident?i=tcp_init_wl">tcp_init_wl</a>(<a href="ident?i=tp">tp</a>, <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=seq">seq</a>);
<a name="L5518" href="source/net/ipv4/tcp_input.c#L5518">5518</a>                 <a href="ident?i=tcp_ack">tcp_ack</a>(sk, <a href="ident?i=skb">skb</a>, <a href="ident?i=FLAG_SLOWPATH">FLAG_SLOWPATH</a>);
<a name="L5519" href="source/net/ipv4/tcp_input.c#L5519">5519</a> 
<a name="L5520" href="source/net/ipv4/tcp_input.c#L5520">5520</a>                 <b><i>/* Ok.. it's good. Set up sequence numbers and</i></b>
<a name="L5521" href="source/net/ipv4/tcp_input.c#L5521">5521</a> <b><i>                 * move to established.</i></b>
<a name="L5522" href="source/net/ipv4/tcp_input.c#L5522">5522</a> <b><i>                 */</i></b>
<a name="L5523" href="source/net/ipv4/tcp_input.c#L5523">5523</a>                 <a href="ident?i=tp">tp</a>-&gt;rcv_nxt = <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=seq">seq</a> + 1;
<a name="L5524" href="source/net/ipv4/tcp_input.c#L5524">5524</a>                 <a href="ident?i=tp">tp</a>-&gt;rcv_wup = <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=seq">seq</a> + 1;
<a name="L5525" href="source/net/ipv4/tcp_input.c#L5525">5525</a> 
<a name="L5526" href="source/net/ipv4/tcp_input.c#L5526">5526</a>                 <b><i>/* RFC1323: The window in SYN &amp; SYN/ACK segments is</i></b>
<a name="L5527" href="source/net/ipv4/tcp_input.c#L5527">5527</a> <b><i>                 * never scaled.</i></b>
<a name="L5528" href="source/net/ipv4/tcp_input.c#L5528">5528</a> <b><i>                 */</i></b>
<a name="L5529" href="source/net/ipv4/tcp_input.c#L5529">5529</a>                 <a href="ident?i=tp">tp</a>-&gt;snd_wnd = <a href="ident?i=ntohs">ntohs</a>(<a href="ident?i=th">th</a>-&gt;<a href="ident?i=window">window</a>);
<a name="L5530" href="source/net/ipv4/tcp_input.c#L5530">5530</a> 
<a name="L5531" href="source/net/ipv4/tcp_input.c#L5531">5531</a>                 if (!<a href="ident?i=tp">tp</a>-&gt;rx_opt.wscale_ok) {
<a name="L5532" href="source/net/ipv4/tcp_input.c#L5532">5532</a>                         <a href="ident?i=tp">tp</a>-&gt;rx_opt.snd_wscale = <a href="ident?i=tp">tp</a>-&gt;rx_opt.rcv_wscale = 0;
<a name="L5533" href="source/net/ipv4/tcp_input.c#L5533">5533</a>                         <a href="ident?i=tp">tp</a>-&gt;window_clamp = <a href="ident?i=min">min</a>(<a href="ident?i=tp">tp</a>-&gt;window_clamp, 65535U);
<a name="L5534" href="source/net/ipv4/tcp_input.c#L5534">5534</a>                 }
<a name="L5535" href="source/net/ipv4/tcp_input.c#L5535">5535</a> 
<a name="L5536" href="source/net/ipv4/tcp_input.c#L5536">5536</a>                 if (<a href="ident?i=tp">tp</a>-&gt;rx_opt.saw_tstamp) {
<a name="L5537" href="source/net/ipv4/tcp_input.c#L5537">5537</a>                         <a href="ident?i=tp">tp</a>-&gt;rx_opt.tstamp_ok       = 1;
<a name="L5538" href="source/net/ipv4/tcp_input.c#L5538">5538</a>                         <a href="ident?i=tp">tp</a>-&gt;tcp_header_len =
<a name="L5539" href="source/net/ipv4/tcp_input.c#L5539">5539</a>                                 sizeof(struct <a href="ident?i=tcphdr">tcphdr</a>) + <a href="ident?i=TCPOLEN_TSTAMP_ALIGNED">TCPOLEN_TSTAMP_ALIGNED</a>;
<a name="L5540" href="source/net/ipv4/tcp_input.c#L5540">5540</a>                         <a href="ident?i=tp">tp</a>-&gt;advmss          -= <a href="ident?i=TCPOLEN_TSTAMP_ALIGNED">TCPOLEN_TSTAMP_ALIGNED</a>;
<a name="L5541" href="source/net/ipv4/tcp_input.c#L5541">5541</a>                         <a href="ident?i=tcp_store_ts_recent">tcp_store_ts_recent</a>(<a href="ident?i=tp">tp</a>);
<a name="L5542" href="source/net/ipv4/tcp_input.c#L5542">5542</a>                 } else {
<a name="L5543" href="source/net/ipv4/tcp_input.c#L5543">5543</a>                         <a href="ident?i=tp">tp</a>-&gt;tcp_header_len = sizeof(struct <a href="ident?i=tcphdr">tcphdr</a>);
<a name="L5544" href="source/net/ipv4/tcp_input.c#L5544">5544</a>                 }
<a name="L5545" href="source/net/ipv4/tcp_input.c#L5545">5545</a> 
<a name="L5546" href="source/net/ipv4/tcp_input.c#L5546">5546</a>                 if (<a href="ident?i=tcp_is_sack">tcp_is_sack</a>(<a href="ident?i=tp">tp</a>) &amp;&amp; <a href="ident?i=sysctl_tcp_fack">sysctl_tcp_fack</a>)
<a name="L5547" href="source/net/ipv4/tcp_input.c#L5547">5547</a>                         <a href="ident?i=tcp_enable_fack">tcp_enable_fack</a>(<a href="ident?i=tp">tp</a>);
<a name="L5548" href="source/net/ipv4/tcp_input.c#L5548">5548</a> 
<a name="L5549" href="source/net/ipv4/tcp_input.c#L5549">5549</a>                 <a href="ident?i=tcp_mtup_init">tcp_mtup_init</a>(sk);
<a name="L5550" href="source/net/ipv4/tcp_input.c#L5550">5550</a>                 <a href="ident?i=tcp_sync_mss">tcp_sync_mss</a>(sk, icsk-&gt;icsk_pmtu_cookie);
<a name="L5551" href="source/net/ipv4/tcp_input.c#L5551">5551</a>                 <a href="ident?i=tcp_initialize_rcv_mss">tcp_initialize_rcv_mss</a>(sk);
<a name="L5552" href="source/net/ipv4/tcp_input.c#L5552">5552</a> 
<a name="L5553" href="source/net/ipv4/tcp_input.c#L5553">5553</a>                 <b><i>/* Remember, tcp_poll() does not lock socket!</i></b>
<a name="L5554" href="source/net/ipv4/tcp_input.c#L5554">5554</a> <b><i>                 * Change state from SYN-SENT only after copied_seq</i></b>
<a name="L5555" href="source/net/ipv4/tcp_input.c#L5555">5555</a> <b><i>                 * is initialized. */</i></b>
<a name="L5556" href="source/net/ipv4/tcp_input.c#L5556">5556</a>                 <a href="ident?i=tp">tp</a>-&gt;copied_seq = <a href="ident?i=tp">tp</a>-&gt;rcv_nxt;
<a name="L5557" href="source/net/ipv4/tcp_input.c#L5557">5557</a> 
<a name="L5558" href="source/net/ipv4/tcp_input.c#L5558">5558</a>                 <a href="ident?i=smp_mb">smp_mb</a>();
<a name="L5559" href="source/net/ipv4/tcp_input.c#L5559">5559</a> 
<a name="L5560" href="source/net/ipv4/tcp_input.c#L5560">5560</a>                 <a href="ident?i=tcp_finish_connect">tcp_finish_connect</a>(sk, <a href="ident?i=skb">skb</a>);
<a name="L5561" href="source/net/ipv4/tcp_input.c#L5561">5561</a> 
<a name="L5562" href="source/net/ipv4/tcp_input.c#L5562">5562</a>                 if ((<a href="ident?i=tp">tp</a>-&gt;syn_fastopen || <a href="ident?i=tp">tp</a>-&gt;syn_data) &amp;&amp;
<a name="L5563" href="source/net/ipv4/tcp_input.c#L5563">5563</a>                     <a href="ident?i=tcp_rcv_fastopen_synack">tcp_rcv_fastopen_synack</a>(sk, <a href="ident?i=skb">skb</a>, &amp;foc))
<a name="L5564" href="source/net/ipv4/tcp_input.c#L5564">5564</a>                         return -1;
<a name="L5565" href="source/net/ipv4/tcp_input.c#L5565">5565</a> 
<a name="L5566" href="source/net/ipv4/tcp_input.c#L5566">5566</a>                 if (sk-&gt;sk_write_pending ||
<a name="L5567" href="source/net/ipv4/tcp_input.c#L5567">5567</a>                     icsk-&gt;icsk_accept_queue.rskq_defer_accept ||
<a name="L5568" href="source/net/ipv4/tcp_input.c#L5568">5568</a>                     icsk-&gt;icsk_ack.pingpong) {
<a name="L5569" href="source/net/ipv4/tcp_input.c#L5569">5569</a>                         <b><i>/* Save one ACK. Data will be ready after</i></b>
<a name="L5570" href="source/net/ipv4/tcp_input.c#L5570">5570</a> <b><i>                         * several ticks, if write_pending is set.</i></b>
<a name="L5571" href="source/net/ipv4/tcp_input.c#L5571">5571</a> <b><i>                         *</i></b>
<a name="L5572" href="source/net/ipv4/tcp_input.c#L5572">5572</a> <b><i>                         * It may be deleted, but with this feature tcpdumps</i></b>
<a name="L5573" href="source/net/ipv4/tcp_input.c#L5573">5573</a> <b><i>                         * look so _wonderfully_ clever, that I was not able</i></b>
<a name="L5574" href="source/net/ipv4/tcp_input.c#L5574">5574</a> <b><i>                         * to stand against the temptation 8)     --ANK</i></b>
<a name="L5575" href="source/net/ipv4/tcp_input.c#L5575">5575</a> <b><i>                         */</i></b>
<a name="L5576" href="source/net/ipv4/tcp_input.c#L5576">5576</a>                         <a href="ident?i=inet_csk_schedule_ack">inet_csk_schedule_ack</a>(sk);
<a name="L5577" href="source/net/ipv4/tcp_input.c#L5577">5577</a>                         icsk-&gt;icsk_ack.lrcvtime = <a href="ident?i=tcp_time_stamp">tcp_time_stamp</a>;
<a name="L5578" href="source/net/ipv4/tcp_input.c#L5578">5578</a>                         <a href="ident?i=tcp_enter_quickack_mode">tcp_enter_quickack_mode</a>(sk);
<a name="L5579" href="source/net/ipv4/tcp_input.c#L5579">5579</a>                         <a href="ident?i=inet_csk_reset_xmit_timer">inet_csk_reset_xmit_timer</a>(sk, <a href="ident?i=ICSK_TIME_DACK">ICSK_TIME_DACK</a>,
<a name="L5580" href="source/net/ipv4/tcp_input.c#L5580">5580</a>                                                   <a href="ident?i=TCP_DELACK_MAX">TCP_DELACK_MAX</a>, <a href="ident?i=TCP_RTO_MAX">TCP_RTO_MAX</a>);
<a name="L5581" href="source/net/ipv4/tcp_input.c#L5581">5581</a> 
<a name="L5582" href="source/net/ipv4/tcp_input.c#L5582">5582</a> <a href="ident?i=discard">discard</a>:
<a name="L5583" href="source/net/ipv4/tcp_input.c#L5583">5583</a>                         <a href="ident?i=__kfree_skb">__kfree_skb</a>(<a href="ident?i=skb">skb</a>);
<a name="L5584" href="source/net/ipv4/tcp_input.c#L5584">5584</a>                         return 0;
<a name="L5585" href="source/net/ipv4/tcp_input.c#L5585">5585</a>                 } else {
<a name="L5586" href="source/net/ipv4/tcp_input.c#L5586">5586</a>                         <a href="ident?i=tcp_send_ack">tcp_send_ack</a>(sk);
<a name="L5587" href="source/net/ipv4/tcp_input.c#L5587">5587</a>                 }
<a name="L5588" href="source/net/ipv4/tcp_input.c#L5588">5588</a>                 return -1;
<a name="L5589" href="source/net/ipv4/tcp_input.c#L5589">5589</a>         }
<a name="L5590" href="source/net/ipv4/tcp_input.c#L5590">5590</a> 
<a name="L5591" href="source/net/ipv4/tcp_input.c#L5591">5591</a>         <b><i>/* No ACK in the segment */</i></b>
<a name="L5592" href="source/net/ipv4/tcp_input.c#L5592">5592</a> 
<a name="L5593" href="source/net/ipv4/tcp_input.c#L5593">5593</a>         if (<a href="ident?i=th">th</a>-&gt;rst) {
<a name="L5594" href="source/net/ipv4/tcp_input.c#L5594">5594</a>                 <b><i>/* rfc793:</i></b>
<a name="L5595" href="source/net/ipv4/tcp_input.c#L5595">5595</a> <b><i>                 * "If the RST bit is set</i></b>
<a name="L5596" href="source/net/ipv4/tcp_input.c#L5596">5596</a> <b><i>                 *</i></b>
<a name="L5597" href="source/net/ipv4/tcp_input.c#L5597">5597</a> <b><i>                 *      Otherwise (no ACK) drop the segment and return."</i></b>
<a name="L5598" href="source/net/ipv4/tcp_input.c#L5598">5598</a> <b><i>                 */</i></b>
<a name="L5599" href="source/net/ipv4/tcp_input.c#L5599">5599</a> 
<a name="L5600" href="source/net/ipv4/tcp_input.c#L5600">5600</a>                 goto discard_and_undo;
<a name="L5601" href="source/net/ipv4/tcp_input.c#L5601">5601</a>         }
<a name="L5602" href="source/net/ipv4/tcp_input.c#L5602">5602</a> 
<a name="L5603" href="source/net/ipv4/tcp_input.c#L5603">5603</a>         <b><i>/* PAWS check. */</i></b>
<a name="L5604" href="source/net/ipv4/tcp_input.c#L5604">5604</a>         if (<a href="ident?i=tp">tp</a>-&gt;rx_opt.ts_recent_stamp &amp;&amp; <a href="ident?i=tp">tp</a>-&gt;rx_opt.saw_tstamp &amp;&amp;
<a name="L5605" href="source/net/ipv4/tcp_input.c#L5605">5605</a>             <a href="ident?i=tcp_paws_reject">tcp_paws_reject</a>(&amp;<a href="ident?i=tp">tp</a>-&gt;rx_opt, 0))
<a name="L5606" href="source/net/ipv4/tcp_input.c#L5606">5606</a>                 goto discard_and_undo;
<a name="L5607" href="source/net/ipv4/tcp_input.c#L5607">5607</a> 
<a name="L5608" href="source/net/ipv4/tcp_input.c#L5608">5608</a>         if (<a href="ident?i=th">th</a>-&gt;syn) {
<a name="L5609" href="source/net/ipv4/tcp_input.c#L5609">5609</a>                 <b><i>/* We see SYN without ACK. It is attempt of</i></b>
<a name="L5610" href="source/net/ipv4/tcp_input.c#L5610">5610</a> <b><i>                 * simultaneous connect with crossed SYNs.</i></b>
<a name="L5611" href="source/net/ipv4/tcp_input.c#L5611">5611</a> <b><i>                 * Particularly, it can be connect to self.</i></b>
<a name="L5612" href="source/net/ipv4/tcp_input.c#L5612">5612</a> <b><i>                 */</i></b>
<a name="L5613" href="source/net/ipv4/tcp_input.c#L5613">5613</a>                 <a href="ident?i=tcp_set_state">tcp_set_state</a>(sk, TCP_SYN_RECV);
<a name="L5614" href="source/net/ipv4/tcp_input.c#L5614">5614</a> 
<a name="L5615" href="source/net/ipv4/tcp_input.c#L5615">5615</a>                 if (<a href="ident?i=tp">tp</a>-&gt;rx_opt.saw_tstamp) {
<a name="L5616" href="source/net/ipv4/tcp_input.c#L5616">5616</a>                         <a href="ident?i=tp">tp</a>-&gt;rx_opt.tstamp_ok = 1;
<a name="L5617" href="source/net/ipv4/tcp_input.c#L5617">5617</a>                         <a href="ident?i=tcp_store_ts_recent">tcp_store_ts_recent</a>(<a href="ident?i=tp">tp</a>);
<a name="L5618" href="source/net/ipv4/tcp_input.c#L5618">5618</a>                         <a href="ident?i=tp">tp</a>-&gt;tcp_header_len =
<a name="L5619" href="source/net/ipv4/tcp_input.c#L5619">5619</a>                                 sizeof(struct <a href="ident?i=tcphdr">tcphdr</a>) + <a href="ident?i=TCPOLEN_TSTAMP_ALIGNED">TCPOLEN_TSTAMP_ALIGNED</a>;
<a name="L5620" href="source/net/ipv4/tcp_input.c#L5620">5620</a>                 } else {
<a name="L5621" href="source/net/ipv4/tcp_input.c#L5621">5621</a>                         <a href="ident?i=tp">tp</a>-&gt;tcp_header_len = sizeof(struct <a href="ident?i=tcphdr">tcphdr</a>);
<a name="L5622" href="source/net/ipv4/tcp_input.c#L5622">5622</a>                 }
<a name="L5623" href="source/net/ipv4/tcp_input.c#L5623">5623</a> 
<a name="L5624" href="source/net/ipv4/tcp_input.c#L5624">5624</a>                 <a href="ident?i=tp">tp</a>-&gt;rcv_nxt = <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=seq">seq</a> + 1;
<a name="L5625" href="source/net/ipv4/tcp_input.c#L5625">5625</a>                 <a href="ident?i=tp">tp</a>-&gt;rcv_wup = <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=seq">seq</a> + 1;
<a name="L5626" href="source/net/ipv4/tcp_input.c#L5626">5626</a> 
<a name="L5627" href="source/net/ipv4/tcp_input.c#L5627">5627</a>                 <b><i>/* RFC1323: The window in SYN &amp; SYN/ACK segments is</i></b>
<a name="L5628" href="source/net/ipv4/tcp_input.c#L5628">5628</a> <b><i>                 * never scaled.</i></b>
<a name="L5629" href="source/net/ipv4/tcp_input.c#L5629">5629</a> <b><i>                 */</i></b>
<a name="L5630" href="source/net/ipv4/tcp_input.c#L5630">5630</a>                 <a href="ident?i=tp">tp</a>-&gt;snd_wnd    = <a href="ident?i=ntohs">ntohs</a>(<a href="ident?i=th">th</a>-&gt;<a href="ident?i=window">window</a>);
<a name="L5631" href="source/net/ipv4/tcp_input.c#L5631">5631</a>                 <a href="ident?i=tp">tp</a>-&gt;snd_wl1    = <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=seq">seq</a>;
<a name="L5632" href="source/net/ipv4/tcp_input.c#L5632">5632</a>                 <a href="ident?i=tp">tp</a>-&gt;max_window = <a href="ident?i=tp">tp</a>-&gt;snd_wnd;
<a name="L5633" href="source/net/ipv4/tcp_input.c#L5633">5633</a> 
<a name="L5634" href="source/net/ipv4/tcp_input.c#L5634">5634</a>                 <a href="ident?i=tcp_ecn_rcv_syn">tcp_ecn_rcv_syn</a>(<a href="ident?i=tp">tp</a>, <a href="ident?i=th">th</a>);
<a name="L5635" href="source/net/ipv4/tcp_input.c#L5635">5635</a> 
<a name="L5636" href="source/net/ipv4/tcp_input.c#L5636">5636</a>                 <a href="ident?i=tcp_mtup_init">tcp_mtup_init</a>(sk);
<a name="L5637" href="source/net/ipv4/tcp_input.c#L5637">5637</a>                 <a href="ident?i=tcp_sync_mss">tcp_sync_mss</a>(sk, icsk-&gt;icsk_pmtu_cookie);
<a name="L5638" href="source/net/ipv4/tcp_input.c#L5638">5638</a>                 <a href="ident?i=tcp_initialize_rcv_mss">tcp_initialize_rcv_mss</a>(sk);
<a name="L5639" href="source/net/ipv4/tcp_input.c#L5639">5639</a> 
<a name="L5640" href="source/net/ipv4/tcp_input.c#L5640">5640</a>                 <a href="ident?i=tcp_send_synack">tcp_send_synack</a>(sk);
<a name="L5641" href="source/net/ipv4/tcp_input.c#L5641">5641</a> #if 0
<a name="L5642" href="source/net/ipv4/tcp_input.c#L5642">5642</a>                 <b><i>/* Note, we could accept data and URG from this segment.</i></b>
<a name="L5643" href="source/net/ipv4/tcp_input.c#L5643">5643</a> <b><i>                 * There are no obstacles to make this (except that we must</i></b>
<a name="L5644" href="source/net/ipv4/tcp_input.c#L5644">5644</a> <b><i>                 * either change tcp_recvmsg() to prevent it from returning data</i></b>
<a name="L5645" href="source/net/ipv4/tcp_input.c#L5645">5645</a> <b><i>                 * before 3WHS completes per RFC793, or employ TCP Fast Open).</i></b>
<a name="L5646" href="source/net/ipv4/tcp_input.c#L5646">5646</a> <b><i>                 *</i></b>
<a name="L5647" href="source/net/ipv4/tcp_input.c#L5647">5647</a> <b><i>                 * However, if we ignore data in ACKless segments sometimes,</i></b>
<a name="L5648" href="source/net/ipv4/tcp_input.c#L5648">5648</a> <b><i>                 * we have no reasons to accept it sometimes.</i></b>
<a name="L5649" href="source/net/ipv4/tcp_input.c#L5649">5649</a> <b><i>                 * Also, seems the code doing it in step6 of tcp_rcv_state_process</i></b>
<a name="L5650" href="source/net/ipv4/tcp_input.c#L5650">5650</a> <b><i>                 * is not flawless. So, discard packet for sanity.</i></b>
<a name="L5651" href="source/net/ipv4/tcp_input.c#L5651">5651</a> <b><i>                 * Uncomment this return to process the data.</i></b>
<a name="L5652" href="source/net/ipv4/tcp_input.c#L5652">5652</a> <b><i>                 */</i></b>
<a name="L5653" href="source/net/ipv4/tcp_input.c#L5653">5653</a>                 return -1;
<a name="L5654" href="source/net/ipv4/tcp_input.c#L5654">5654</a> #else
<a name="L5655" href="source/net/ipv4/tcp_input.c#L5655">5655</a>                 goto <a href="ident?i=discard">discard</a>;
<a name="L5656" href="source/net/ipv4/tcp_input.c#L5656">5656</a> #endif
<a name="L5657" href="source/net/ipv4/tcp_input.c#L5657">5657</a>         }
<a name="L5658" href="source/net/ipv4/tcp_input.c#L5658">5658</a>         <b><i>/* "fifth, if neither of the SYN or RST bits is set then</i></b>
<a name="L5659" href="source/net/ipv4/tcp_input.c#L5659">5659</a> <b><i>         * drop the segment and return."</i></b>
<a name="L5660" href="source/net/ipv4/tcp_input.c#L5660">5660</a> <b><i>         */</i></b>
<a name="L5661" href="source/net/ipv4/tcp_input.c#L5661">5661</a> 
<a name="L5662" href="source/net/ipv4/tcp_input.c#L5662">5662</a> discard_and_undo:
<a name="L5663" href="source/net/ipv4/tcp_input.c#L5663">5663</a>         <a href="ident?i=tcp_clear_options">tcp_clear_options</a>(&amp;<a href="ident?i=tp">tp</a>-&gt;rx_opt);
<a name="L5664" href="source/net/ipv4/tcp_input.c#L5664">5664</a>         <a href="ident?i=tp">tp</a>-&gt;rx_opt.mss_clamp = saved_clamp;
<a name="L5665" href="source/net/ipv4/tcp_input.c#L5665">5665</a>         goto <a href="ident?i=discard">discard</a>;
<a name="L5666" href="source/net/ipv4/tcp_input.c#L5666">5666</a> 
<a name="L5667" href="source/net/ipv4/tcp_input.c#L5667">5667</a> reset_and_undo:
<a name="L5668" href="source/net/ipv4/tcp_input.c#L5668">5668</a>         <a href="ident?i=tcp_clear_options">tcp_clear_options</a>(&amp;<a href="ident?i=tp">tp</a>-&gt;rx_opt);
<a name="L5669" href="source/net/ipv4/tcp_input.c#L5669">5669</a>         <a href="ident?i=tp">tp</a>-&gt;rx_opt.mss_clamp = saved_clamp;
<a name="L5670" href="source/net/ipv4/tcp_input.c#L5670">5670</a>         return 1;
<a name="L5671" href="source/net/ipv4/tcp_input.c#L5671">5671</a> }
<a name="L5672" href="source/net/ipv4/tcp_input.c#L5672">5672</a> 
<a name="L5673" href="source/net/ipv4/tcp_input.c#L5673">5673</a> <b><i>/*</i></b>
<a name="L5674" href="source/net/ipv4/tcp_input.c#L5674">5674</a> <b><i> *      This function implements the receiving procedure of RFC 793 for</i></b>
<a name="L5675" href="source/net/ipv4/tcp_input.c#L5675">5675</a> <b><i> *      all states except ESTABLISHED and TIME_WAIT.</i></b>
<a name="L5676" href="source/net/ipv4/tcp_input.c#L5676">5676</a> <b><i> *      It's called from both tcp_v4_rcv and tcp_v6_rcv and should be</i></b>
<a name="L5677" href="source/net/ipv4/tcp_input.c#L5677">5677</a> <b><i> *      address independent.</i></b>
<a name="L5678" href="source/net/ipv4/tcp_input.c#L5678">5678</a> <b><i> */</i></b>
<a name="L5679" href="source/net/ipv4/tcp_input.c#L5679">5679</a> 
<a name="L5680" href="source/net/ipv4/tcp_input.c#L5680">5680</a> int <a href="ident?i=tcp_rcv_state_process">tcp_rcv_state_process</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
<a name="L5681" href="source/net/ipv4/tcp_input.c#L5681">5681</a>                           const struct <a href="ident?i=tcphdr">tcphdr</a> *<a href="ident?i=th">th</a>, unsigned int <a href="ident?i=len">len</a>)
<a name="L5682" href="source/net/ipv4/tcp_input.c#L5682">5682</a> {
<a name="L5683" href="source/net/ipv4/tcp_input.c#L5683">5683</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L5684" href="source/net/ipv4/tcp_input.c#L5684">5684</a>         struct <a href="ident?i=inet_connection_sock">inet_connection_sock</a> *icsk = <a href="ident?i=inet_csk">inet_csk</a>(sk);
<a name="L5685" href="source/net/ipv4/tcp_input.c#L5685">5685</a>         struct <a href="ident?i=request_sock">request_sock</a> *<a href="ident?i=req">req</a>;
<a name="L5686" href="source/net/ipv4/tcp_input.c#L5686">5686</a>         int queued = 0;
<a name="L5687" href="source/net/ipv4/tcp_input.c#L5687">5687</a>         <a href="ident?i=bool">bool</a> acceptable;
<a name="L5688" href="source/net/ipv4/tcp_input.c#L5688">5688</a>         <a href="ident?i=u32">u32</a> synack_stamp;
<a name="L5689" href="source/net/ipv4/tcp_input.c#L5689">5689</a> 
<a name="L5690" href="source/net/ipv4/tcp_input.c#L5690">5690</a>         <a href="ident?i=tp">tp</a>-&gt;rx_opt.saw_tstamp = 0;
<a name="L5691" href="source/net/ipv4/tcp_input.c#L5691">5691</a> 
<a name="L5692" href="source/net/ipv4/tcp_input.c#L5692">5692</a>         switch (sk-&gt;<a href="ident?i=sk_state">sk_state</a>) {
<a name="L5693" href="source/net/ipv4/tcp_input.c#L5693">5693</a>         case TCP_CLOSE:
<a name="L5694" href="source/net/ipv4/tcp_input.c#L5694">5694</a>                 goto <a href="ident?i=discard">discard</a>;
<a name="L5695" href="source/net/ipv4/tcp_input.c#L5695">5695</a> 
<a name="L5696" href="source/net/ipv4/tcp_input.c#L5696">5696</a>         case TCP_LISTEN:
<a name="L5697" href="source/net/ipv4/tcp_input.c#L5697">5697</a>                 if (<a href="ident?i=th">th</a>-&gt;ack)
<a name="L5698" href="source/net/ipv4/tcp_input.c#L5698">5698</a>                         return 1;
<a name="L5699" href="source/net/ipv4/tcp_input.c#L5699">5699</a> 
<a name="L5700" href="source/net/ipv4/tcp_input.c#L5700">5700</a>                 if (<a href="ident?i=th">th</a>-&gt;rst)
<a name="L5701" href="source/net/ipv4/tcp_input.c#L5701">5701</a>                         goto <a href="ident?i=discard">discard</a>;
<a name="L5702" href="source/net/ipv4/tcp_input.c#L5702">5702</a> 
<a name="L5703" href="source/net/ipv4/tcp_input.c#L5703">5703</a>                 if (<a href="ident?i=th">th</a>-&gt;syn) {
<a name="L5704" href="source/net/ipv4/tcp_input.c#L5704">5704</a>                         if (<a href="ident?i=th">th</a>-&gt;fin)
<a name="L5705" href="source/net/ipv4/tcp_input.c#L5705">5705</a>                                 goto <a href="ident?i=discard">discard</a>;
<a name="L5706" href="source/net/ipv4/tcp_input.c#L5706">5706</a>                         if (icsk-&gt;icsk_af_ops-&gt;conn_request(sk, <a href="ident?i=skb">skb</a>) &lt; 0)
<a name="L5707" href="source/net/ipv4/tcp_input.c#L5707">5707</a>                                 return 1;
<a name="L5708" href="source/net/ipv4/tcp_input.c#L5708">5708</a> 
<a name="L5709" href="source/net/ipv4/tcp_input.c#L5709">5709</a>                         <b><i>/* Now we have several options: In theory there is</i></b>
<a name="L5710" href="source/net/ipv4/tcp_input.c#L5710">5710</a> <b><i>                         * nothing else in the frame. KA9Q has an option to</i></b>
<a name="L5711" href="source/net/ipv4/tcp_input.c#L5711">5711</a> <b><i>                         * send data with the syn, BSD accepts data with the</i></b>
<a name="L5712" href="source/net/ipv4/tcp_input.c#L5712">5712</a> <b><i>                         * syn up to the [to be] advertised window and</i></b>
<a name="L5713" href="source/net/ipv4/tcp_input.c#L5713">5713</a> <b><i>                         * Solaris 2.1 gives you a protocol error. For now</i></b>
<a name="L5714" href="source/net/ipv4/tcp_input.c#L5714">5714</a> <b><i>                         * we just ignore it, that fits the spec precisely</i></b>
<a name="L5715" href="source/net/ipv4/tcp_input.c#L5715">5715</a> <b><i>                         * and avoids incompatibilities. It would be nice in</i></b>
<a name="L5716" href="source/net/ipv4/tcp_input.c#L5716">5716</a> <b><i>                         * future to drop through and process the data.</i></b>
<a name="L5717" href="source/net/ipv4/tcp_input.c#L5717">5717</a> <b><i>                         *</i></b>
<a name="L5718" href="source/net/ipv4/tcp_input.c#L5718">5718</a> <b><i>                         * Now that TTCP is starting to be used we ought to</i></b>
<a name="L5719" href="source/net/ipv4/tcp_input.c#L5719">5719</a> <b><i>                         * queue this data.</i></b>
<a name="L5720" href="source/net/ipv4/tcp_input.c#L5720">5720</a> <b><i>                         * But, this leaves one open to an easy denial of</i></b>
<a name="L5721" href="source/net/ipv4/tcp_input.c#L5721">5721</a> <b><i>                         * service attack, and SYN cookies can't defend</i></b>
<a name="L5722" href="source/net/ipv4/tcp_input.c#L5722">5722</a> <b><i>                         * against this problem. So, we drop the data</i></b>
<a name="L5723" href="source/net/ipv4/tcp_input.c#L5723">5723</a> <b><i>                         * in the interest of security over speed unless</i></b>
<a name="L5724" href="source/net/ipv4/tcp_input.c#L5724">5724</a> <b><i>                         * it's still in use.</i></b>
<a name="L5725" href="source/net/ipv4/tcp_input.c#L5725">5725</a> <b><i>                         */</i></b>
<a name="L5726" href="source/net/ipv4/tcp_input.c#L5726">5726</a>                         <a href="ident?i=kfree_skb">kfree_skb</a>(<a href="ident?i=skb">skb</a>);
<a name="L5727" href="source/net/ipv4/tcp_input.c#L5727">5727</a>                         return 0;
<a name="L5728" href="source/net/ipv4/tcp_input.c#L5728">5728</a>                 }
<a name="L5729" href="source/net/ipv4/tcp_input.c#L5729">5729</a>                 goto <a href="ident?i=discard">discard</a>;
<a name="L5730" href="source/net/ipv4/tcp_input.c#L5730">5730</a> 
<a name="L5731" href="source/net/ipv4/tcp_input.c#L5731">5731</a>         case TCP_SYN_SENT:
<a name="L5732" href="source/net/ipv4/tcp_input.c#L5732">5732</a>                 queued = <a href="ident?i=tcp_rcv_synsent_state_process">tcp_rcv_synsent_state_process</a>(sk, <a href="ident?i=skb">skb</a>, <a href="ident?i=th">th</a>, <a href="ident?i=len">len</a>);
<a name="L5733" href="source/net/ipv4/tcp_input.c#L5733">5733</a>                 if (queued &gt;= 0)
<a name="L5734" href="source/net/ipv4/tcp_input.c#L5734">5734</a>                         return queued;
<a name="L5735" href="source/net/ipv4/tcp_input.c#L5735">5735</a> 
<a name="L5736" href="source/net/ipv4/tcp_input.c#L5736">5736</a>                 <b><i>/* Do step6 onward by hand. */</i></b>
<a name="L5737" href="source/net/ipv4/tcp_input.c#L5737">5737</a>                 <a href="ident?i=tcp_urg">tcp_urg</a>(sk, <a href="ident?i=skb">skb</a>, <a href="ident?i=th">th</a>);
<a name="L5738" href="source/net/ipv4/tcp_input.c#L5738">5738</a>                 <a href="ident?i=__kfree_skb">__kfree_skb</a>(<a href="ident?i=skb">skb</a>);
<a name="L5739" href="source/net/ipv4/tcp_input.c#L5739">5739</a>                 <a href="ident?i=tcp_data_snd_check">tcp_data_snd_check</a>(sk);
<a name="L5740" href="source/net/ipv4/tcp_input.c#L5740">5740</a>                 return 0;
<a name="L5741" href="source/net/ipv4/tcp_input.c#L5741">5741</a>         }
<a name="L5742" href="source/net/ipv4/tcp_input.c#L5742">5742</a> 
<a name="L5743" href="source/net/ipv4/tcp_input.c#L5743">5743</a>         <a href="ident?i=req">req</a> = <a href="ident?i=tp">tp</a>-&gt;fastopen_rsk;
<a name="L5744" href="source/net/ipv4/tcp_input.c#L5744">5744</a>         if (<a href="ident?i=req">req</a>) {
<a name="L5745" href="source/net/ipv4/tcp_input.c#L5745">5745</a>                 <a href="ident?i=WARN_ON_ONCE">WARN_ON_ONCE</a>(sk-&gt;<a href="ident?i=sk_state">sk_state</a> != TCP_SYN_RECV &amp;&amp;
<a name="L5746" href="source/net/ipv4/tcp_input.c#L5746">5746</a>                     sk-&gt;<a href="ident?i=sk_state">sk_state</a> != TCP_FIN_WAIT1);
<a name="L5747" href="source/net/ipv4/tcp_input.c#L5747">5747</a> 
<a name="L5748" href="source/net/ipv4/tcp_input.c#L5748">5748</a>                 if (!<a href="ident?i=tcp_check_req">tcp_check_req</a>(sk, <a href="ident?i=skb">skb</a>, <a href="ident?i=req">req</a>, <a href="ident?i=true">true</a>))
<a name="L5749" href="source/net/ipv4/tcp_input.c#L5749">5749</a>                         goto <a href="ident?i=discard">discard</a>;
<a name="L5750" href="source/net/ipv4/tcp_input.c#L5750">5750</a>         }
<a name="L5751" href="source/net/ipv4/tcp_input.c#L5751">5751</a> 
<a name="L5752" href="source/net/ipv4/tcp_input.c#L5752">5752</a>         if (!<a href="ident?i=th">th</a>-&gt;ack &amp;&amp; !<a href="ident?i=th">th</a>-&gt;rst &amp;&amp; !<a href="ident?i=th">th</a>-&gt;syn)
<a name="L5753" href="source/net/ipv4/tcp_input.c#L5753">5753</a>                 goto <a href="ident?i=discard">discard</a>;
<a name="L5754" href="source/net/ipv4/tcp_input.c#L5754">5754</a> 
<a name="L5755" href="source/net/ipv4/tcp_input.c#L5755">5755</a>         if (!<a href="ident?i=tcp_validate_incoming">tcp_validate_incoming</a>(sk, <a href="ident?i=skb">skb</a>, <a href="ident?i=th">th</a>, 0))
<a name="L5756" href="source/net/ipv4/tcp_input.c#L5756">5756</a>                 return 0;
<a name="L5757" href="source/net/ipv4/tcp_input.c#L5757">5757</a> 
<a name="L5758" href="source/net/ipv4/tcp_input.c#L5758">5758</a>         <b><i>/* step 5: check the ACK field */</i></b>
<a name="L5759" href="source/net/ipv4/tcp_input.c#L5759">5759</a>         acceptable = <a href="ident?i=tcp_ack">tcp_ack</a>(sk, <a href="ident?i=skb">skb</a>, <a href="ident?i=FLAG_SLOWPATH">FLAG_SLOWPATH</a> |
<a name="L5760" href="source/net/ipv4/tcp_input.c#L5760">5760</a>                                       <a href="ident?i=FLAG_UPDATE_TS_RECENT">FLAG_UPDATE_TS_RECENT</a>) &gt; 0;
<a name="L5761" href="source/net/ipv4/tcp_input.c#L5761">5761</a> 
<a name="L5762" href="source/net/ipv4/tcp_input.c#L5762">5762</a>         switch (sk-&gt;<a href="ident?i=sk_state">sk_state</a>) {
<a name="L5763" href="source/net/ipv4/tcp_input.c#L5763">5763</a>         case TCP_SYN_RECV:
<a name="L5764" href="source/net/ipv4/tcp_input.c#L5764">5764</a>                 if (!acceptable)
<a name="L5765" href="source/net/ipv4/tcp_input.c#L5765">5765</a>                         return 1;
<a name="L5766" href="source/net/ipv4/tcp_input.c#L5766">5766</a> 
<a name="L5767" href="source/net/ipv4/tcp_input.c#L5767">5767</a>                 <b><i>/* Once we leave TCP_SYN_RECV, we no longer need req</i></b>
<a name="L5768" href="source/net/ipv4/tcp_input.c#L5768">5768</a> <b><i>                 * so release it.</i></b>
<a name="L5769" href="source/net/ipv4/tcp_input.c#L5769">5769</a> <b><i>                 */</i></b>
<a name="L5770" href="source/net/ipv4/tcp_input.c#L5770">5770</a>                 if (<a href="ident?i=req">req</a>) {
<a name="L5771" href="source/net/ipv4/tcp_input.c#L5771">5771</a>                         synack_stamp = <a href="ident?i=tcp_rsk">tcp_rsk</a>(<a href="ident?i=req">req</a>)-&gt;snt_synack;
<a name="L5772" href="source/net/ipv4/tcp_input.c#L5772">5772</a>                         <a href="ident?i=tp">tp</a>-&gt;total_retrans = <a href="ident?i=req">req</a>-&gt;num_retrans;
<a name="L5773" href="source/net/ipv4/tcp_input.c#L5773">5773</a>                         <a href="ident?i=reqsk_fastopen_remove">reqsk_fastopen_remove</a>(sk, <a href="ident?i=req">req</a>, <a href="ident?i=false">false</a>);
<a name="L5774" href="source/net/ipv4/tcp_input.c#L5774">5774</a>                 } else {
<a name="L5775" href="source/net/ipv4/tcp_input.c#L5775">5775</a>                         synack_stamp = <a href="ident?i=tp">tp</a>-&gt;lsndtime;
<a name="L5776" href="source/net/ipv4/tcp_input.c#L5776">5776</a>                         <b><i>/* Make sure socket is routed, for correct metrics. */</i></b>
<a name="L5777" href="source/net/ipv4/tcp_input.c#L5777">5777</a>                         icsk-&gt;icsk_af_ops-&gt;rebuild_header(sk);
<a name="L5778" href="source/net/ipv4/tcp_input.c#L5778">5778</a>                         <a href="ident?i=tcp_init_congestion_control">tcp_init_congestion_control</a>(sk);
<a name="L5779" href="source/net/ipv4/tcp_input.c#L5779">5779</a> 
<a name="L5780" href="source/net/ipv4/tcp_input.c#L5780">5780</a>                         <a href="ident?i=tcp_mtup_init">tcp_mtup_init</a>(sk);
<a name="L5781" href="source/net/ipv4/tcp_input.c#L5781">5781</a>                         <a href="ident?i=tp">tp</a>-&gt;copied_seq = <a href="ident?i=tp">tp</a>-&gt;rcv_nxt;
<a name="L5782" href="source/net/ipv4/tcp_input.c#L5782">5782</a>                         <a href="ident?i=tcp_init_buffer_space">tcp_init_buffer_space</a>(sk);
<a name="L5783" href="source/net/ipv4/tcp_input.c#L5783">5783</a>                 }
<a name="L5784" href="source/net/ipv4/tcp_input.c#L5784">5784</a>                 <a href="ident?i=smp_mb">smp_mb</a>();
<a name="L5785" href="source/net/ipv4/tcp_input.c#L5785">5785</a>                 <a href="ident?i=tcp_set_state">tcp_set_state</a>(sk, TCP_ESTABLISHED);
<a name="L5786" href="source/net/ipv4/tcp_input.c#L5786">5786</a>                 sk-&gt;sk_state_change(sk);
<a name="L5787" href="source/net/ipv4/tcp_input.c#L5787">5787</a> 
<a name="L5788" href="source/net/ipv4/tcp_input.c#L5788">5788</a>                 <b><i>/* Note, that this wakeup is only for marginal crossed SYN case.</i></b>
<a name="L5789" href="source/net/ipv4/tcp_input.c#L5789">5789</a> <b><i>                 * Passively open sockets are not waked up, because</i></b>
<a name="L5790" href="source/net/ipv4/tcp_input.c#L5790">5790</a> <b><i>                 * sk-&gt;sk_sleep == NULL and sk-&gt;sk_socket == NULL.</i></b>
<a name="L5791" href="source/net/ipv4/tcp_input.c#L5791">5791</a> <b><i>                 */</i></b>
<a name="L5792" href="source/net/ipv4/tcp_input.c#L5792">5792</a>                 if (sk-&gt;sk_socket)
<a name="L5793" href="source/net/ipv4/tcp_input.c#L5793">5793</a>                         <a href="ident?i=sk_wake_async">sk_wake_async</a>(sk, SOCK_WAKE_IO, <a href="ident?i=POLL_OUT">POLL_OUT</a>);
<a name="L5794" href="source/net/ipv4/tcp_input.c#L5794">5794</a> 
<a name="L5795" href="source/net/ipv4/tcp_input.c#L5795">5795</a>                 <a href="ident?i=tp">tp</a>-&gt;snd_una = <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;ack_seq;
<a name="L5796" href="source/net/ipv4/tcp_input.c#L5796">5796</a>                 <a href="ident?i=tp">tp</a>-&gt;snd_wnd = <a href="ident?i=ntohs">ntohs</a>(<a href="ident?i=th">th</a>-&gt;<a href="ident?i=window">window</a>) &lt;&lt; <a href="ident?i=tp">tp</a>-&gt;rx_opt.snd_wscale;
<a name="L5797" href="source/net/ipv4/tcp_input.c#L5797">5797</a>                 <a href="ident?i=tcp_init_wl">tcp_init_wl</a>(<a href="ident?i=tp">tp</a>, <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=seq">seq</a>);
<a name="L5798" href="source/net/ipv4/tcp_input.c#L5798">5798</a>                 <a href="ident?i=tcp_synack_rtt_meas">tcp_synack_rtt_meas</a>(sk, synack_stamp);
<a name="L5799" href="source/net/ipv4/tcp_input.c#L5799">5799</a> 
<a name="L5800" href="source/net/ipv4/tcp_input.c#L5800">5800</a>                 if (<a href="ident?i=tp">tp</a>-&gt;rx_opt.tstamp_ok)
<a name="L5801" href="source/net/ipv4/tcp_input.c#L5801">5801</a>                         <a href="ident?i=tp">tp</a>-&gt;advmss -= <a href="ident?i=TCPOLEN_TSTAMP_ALIGNED">TCPOLEN_TSTAMP_ALIGNED</a>;
<a name="L5802" href="source/net/ipv4/tcp_input.c#L5802">5802</a> 
<a name="L5803" href="source/net/ipv4/tcp_input.c#L5803">5803</a>                 if (<a href="ident?i=req">req</a>) {
<a name="L5804" href="source/net/ipv4/tcp_input.c#L5804">5804</a>                         <b><i>/* Re-arm the timer because data may have been sent out.</i></b>
<a name="L5805" href="source/net/ipv4/tcp_input.c#L5805">5805</a> <b><i>                         * This is similar to the regular data transmission case</i></b>
<a name="L5806" href="source/net/ipv4/tcp_input.c#L5806">5806</a> <b><i>                         * when new data has just been ack'ed.</i></b>
<a name="L5807" href="source/net/ipv4/tcp_input.c#L5807">5807</a> <b><i>                         *</i></b>
<a name="L5808" href="source/net/ipv4/tcp_input.c#L5808">5808</a> <b><i>                         * (TFO) - we could try to be more aggressive and</i></b>
<a name="L5809" href="source/net/ipv4/tcp_input.c#L5809">5809</a> <b><i>                         * retransmitting any data sooner based on when they</i></b>
<a name="L5810" href="source/net/ipv4/tcp_input.c#L5810">5810</a> <b><i>                         * are sent out.</i></b>
<a name="L5811" href="source/net/ipv4/tcp_input.c#L5811">5811</a> <b><i>                         */</i></b>
<a name="L5812" href="source/net/ipv4/tcp_input.c#L5812">5812</a>                         <a href="ident?i=tcp_rearm_rto">tcp_rearm_rto</a>(sk);
<a name="L5813" href="source/net/ipv4/tcp_input.c#L5813">5813</a>                 } else
<a name="L5814" href="source/net/ipv4/tcp_input.c#L5814">5814</a>                         <a href="ident?i=tcp_init_metrics">tcp_init_metrics</a>(sk);
<a name="L5815" href="source/net/ipv4/tcp_input.c#L5815">5815</a> 
<a name="L5816" href="source/net/ipv4/tcp_input.c#L5816">5816</a>                 <a href="ident?i=tcp_update_pacing_rate">tcp_update_pacing_rate</a>(sk);
<a name="L5817" href="source/net/ipv4/tcp_input.c#L5817">5817</a> 
<a name="L5818" href="source/net/ipv4/tcp_input.c#L5818">5818</a>                 <b><i>/* Prevent spurious tcp_cwnd_restart() on first data packet */</i></b>
<a name="L5819" href="source/net/ipv4/tcp_input.c#L5819">5819</a>                 <a href="ident?i=tp">tp</a>-&gt;lsndtime = <a href="ident?i=tcp_time_stamp">tcp_time_stamp</a>;
<a name="L5820" href="source/net/ipv4/tcp_input.c#L5820">5820</a> 
<a name="L5821" href="source/net/ipv4/tcp_input.c#L5821">5821</a>                 <a href="ident?i=tcp_initialize_rcv_mss">tcp_initialize_rcv_mss</a>(sk);
<a name="L5822" href="source/net/ipv4/tcp_input.c#L5822">5822</a>                 <a href="ident?i=tcp_fast_path_on">tcp_fast_path_on</a>(<a href="ident?i=tp">tp</a>);
<a name="L5823" href="source/net/ipv4/tcp_input.c#L5823">5823</a>                 break;
<a name="L5824" href="source/net/ipv4/tcp_input.c#L5824">5824</a> 
<a name="L5825" href="source/net/ipv4/tcp_input.c#L5825">5825</a>         case TCP_FIN_WAIT1: {
<a name="L5826" href="source/net/ipv4/tcp_input.c#L5826">5826</a>                 struct <a href="ident?i=dst_entry">dst_entry</a> *<a href="ident?i=dst">dst</a>;
<a name="L5827" href="source/net/ipv4/tcp_input.c#L5827">5827</a>                 int tmo;
<a name="L5828" href="source/net/ipv4/tcp_input.c#L5828">5828</a> 
<a name="L5829" href="source/net/ipv4/tcp_input.c#L5829">5829</a>                 <b><i>/* If we enter the TCP_FIN_WAIT1 state and we are a</i></b>
<a name="L5830" href="source/net/ipv4/tcp_input.c#L5830">5830</a> <b><i>                 * Fast Open socket and this is the first acceptable</i></b>
<a name="L5831" href="source/net/ipv4/tcp_input.c#L5831">5831</a> <b><i>                 * ACK we have received, this would have acknowledged</i></b>
<a name="L5832" href="source/net/ipv4/tcp_input.c#L5832">5832</a> <b><i>                 * our SYNACK so stop the SYNACK timer.</i></b>
<a name="L5833" href="source/net/ipv4/tcp_input.c#L5833">5833</a> <b><i>                 */</i></b>
<a name="L5834" href="source/net/ipv4/tcp_input.c#L5834">5834</a>                 if (<a href="ident?i=req">req</a>) {
<a name="L5835" href="source/net/ipv4/tcp_input.c#L5835">5835</a>                         <b><i>/* Return RST if ack_seq is invalid.</i></b>
<a name="L5836" href="source/net/ipv4/tcp_input.c#L5836">5836</a> <b><i>                         * Note that RFC793 only says to generate a</i></b>
<a name="L5837" href="source/net/ipv4/tcp_input.c#L5837">5837</a> <b><i>                         * DUPACK for it but for TCP Fast Open it seems</i></b>
<a name="L5838" href="source/net/ipv4/tcp_input.c#L5838">5838</a> <b><i>                         * better to treat this case like TCP_SYN_RECV</i></b>
<a name="L5839" href="source/net/ipv4/tcp_input.c#L5839">5839</a> <b><i>                         * above.</i></b>
<a name="L5840" href="source/net/ipv4/tcp_input.c#L5840">5840</a> <b><i>                         */</i></b>
<a name="L5841" href="source/net/ipv4/tcp_input.c#L5841">5841</a>                         if (!acceptable)
<a name="L5842" href="source/net/ipv4/tcp_input.c#L5842">5842</a>                                 return 1;
<a name="L5843" href="source/net/ipv4/tcp_input.c#L5843">5843</a>                         <b><i>/* We no longer need the request sock. */</i></b>
<a name="L5844" href="source/net/ipv4/tcp_input.c#L5844">5844</a>                         <a href="ident?i=reqsk_fastopen_remove">reqsk_fastopen_remove</a>(sk, <a href="ident?i=req">req</a>, <a href="ident?i=false">false</a>);
<a name="L5845" href="source/net/ipv4/tcp_input.c#L5845">5845</a>                         <a href="ident?i=tcp_rearm_rto">tcp_rearm_rto</a>(sk);
<a name="L5846" href="source/net/ipv4/tcp_input.c#L5846">5846</a>                 }
<a name="L5847" href="source/net/ipv4/tcp_input.c#L5847">5847</a>                 if (<a href="ident?i=tp">tp</a>-&gt;snd_una != <a href="ident?i=tp">tp</a>-&gt;write_seq)
<a name="L5848" href="source/net/ipv4/tcp_input.c#L5848">5848</a>                         break;
<a name="L5849" href="source/net/ipv4/tcp_input.c#L5849">5849</a> 
<a name="L5850" href="source/net/ipv4/tcp_input.c#L5850">5850</a>                 <a href="ident?i=tcp_set_state">tcp_set_state</a>(sk, TCP_FIN_WAIT2);
<a name="L5851" href="source/net/ipv4/tcp_input.c#L5851">5851</a>                 sk-&gt;sk_shutdown |= <a href="ident?i=SEND_SHUTDOWN">SEND_SHUTDOWN</a>;
<a name="L5852" href="source/net/ipv4/tcp_input.c#L5852">5852</a> 
<a name="L5853" href="source/net/ipv4/tcp_input.c#L5853">5853</a>                 <a href="ident?i=dst">dst</a> = <a href="ident?i=__sk_dst_get">__sk_dst_get</a>(sk);
<a name="L5854" href="source/net/ipv4/tcp_input.c#L5854">5854</a>                 if (<a href="ident?i=dst">dst</a>)
<a name="L5855" href="source/net/ipv4/tcp_input.c#L5855">5855</a>                         <a href="ident?i=dst_confirm">dst_confirm</a>(<a href="ident?i=dst">dst</a>);
<a name="L5856" href="source/net/ipv4/tcp_input.c#L5856">5856</a> 
<a name="L5857" href="source/net/ipv4/tcp_input.c#L5857">5857</a>                 if (!<a href="ident?i=sock_flag">sock_flag</a>(sk, SOCK_DEAD)) {
<a name="L5858" href="source/net/ipv4/tcp_input.c#L5858">5858</a>                         <b><i>/* Wake up lingering close() */</i></b>
<a name="L5859" href="source/net/ipv4/tcp_input.c#L5859">5859</a>                         sk-&gt;sk_state_change(sk);
<a name="L5860" href="source/net/ipv4/tcp_input.c#L5860">5860</a>                         break;
<a name="L5861" href="source/net/ipv4/tcp_input.c#L5861">5861</a>                 }
<a name="L5862" href="source/net/ipv4/tcp_input.c#L5862">5862</a> 
<a name="L5863" href="source/net/ipv4/tcp_input.c#L5863">5863</a>                 if (<a href="ident?i=tp">tp</a>-&gt;linger2 &lt; 0 ||
<a name="L5864" href="source/net/ipv4/tcp_input.c#L5864">5864</a>                     (<a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;end_seq != <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=seq">seq</a> &amp;&amp;
<a name="L5865" href="source/net/ipv4/tcp_input.c#L5865">5865</a>                      <a href="ident?i=after">after</a>(<a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;end_seq - <a href="ident?i=th">th</a>-&gt;fin, <a href="ident?i=tp">tp</a>-&gt;rcv_nxt))) {
<a name="L5866" href="source/net/ipv4/tcp_input.c#L5866">5866</a>                         <a href="ident?i=tcp_done">tcp_done</a>(sk);
<a name="L5867" href="source/net/ipv4/tcp_input.c#L5867">5867</a>                         <a href="ident?i=NET_INC_STATS_BH">NET_INC_STATS_BH</a>(<a href="ident?i=sock_net">sock_net</a>(sk), LINUX_MIB_TCPABORTONDATA);
<a name="L5868" href="source/net/ipv4/tcp_input.c#L5868">5868</a>                         return 1;
<a name="L5869" href="source/net/ipv4/tcp_input.c#L5869">5869</a>                 }
<a name="L5870" href="source/net/ipv4/tcp_input.c#L5870">5870</a> 
<a name="L5871" href="source/net/ipv4/tcp_input.c#L5871">5871</a>                 tmo = <a href="ident?i=tcp_fin_time">tcp_fin_time</a>(sk);
<a name="L5872" href="source/net/ipv4/tcp_input.c#L5872">5872</a>                 if (tmo &gt; <a href="ident?i=TCP_TIMEWAIT_LEN">TCP_TIMEWAIT_LEN</a>) {
<a name="L5873" href="source/net/ipv4/tcp_input.c#L5873">5873</a>                         <a href="ident?i=inet_csk_reset_keepalive_timer">inet_csk_reset_keepalive_timer</a>(sk, tmo - <a href="ident?i=TCP_TIMEWAIT_LEN">TCP_TIMEWAIT_LEN</a>);
<a name="L5874" href="source/net/ipv4/tcp_input.c#L5874">5874</a>                 } else if (<a href="ident?i=th">th</a>-&gt;fin || <a href="ident?i=sock_owned_by_user">sock_owned_by_user</a>(sk)) {
<a name="L5875" href="source/net/ipv4/tcp_input.c#L5875">5875</a>                         <b><i>/* Bad case. We could lose such FIN otherwise.</i></b>
<a name="L5876" href="source/net/ipv4/tcp_input.c#L5876">5876</a> <b><i>                         * It is not a big problem, but it looks confusing</i></b>
<a name="L5877" href="source/net/ipv4/tcp_input.c#L5877">5877</a> <b><i>                         * and not so rare event. We still can lose it now,</i></b>
<a name="L5878" href="source/net/ipv4/tcp_input.c#L5878">5878</a> <b><i>                         * if it spins in bh_lock_sock(), but it is really</i></b>
<a name="L5879" href="source/net/ipv4/tcp_input.c#L5879">5879</a> <b><i>                         * marginal case.</i></b>
<a name="L5880" href="source/net/ipv4/tcp_input.c#L5880">5880</a> <b><i>                         */</i></b>
<a name="L5881" href="source/net/ipv4/tcp_input.c#L5881">5881</a>                         <a href="ident?i=inet_csk_reset_keepalive_timer">inet_csk_reset_keepalive_timer</a>(sk, tmo);
<a name="L5882" href="source/net/ipv4/tcp_input.c#L5882">5882</a>                 } else {
<a name="L5883" href="source/net/ipv4/tcp_input.c#L5883">5883</a>                         <a href="ident?i=tcp_time_wait">tcp_time_wait</a>(sk, TCP_FIN_WAIT2, tmo);
<a name="L5884" href="source/net/ipv4/tcp_input.c#L5884">5884</a>                         goto <a href="ident?i=discard">discard</a>;
<a name="L5885" href="source/net/ipv4/tcp_input.c#L5885">5885</a>                 }
<a name="L5886" href="source/net/ipv4/tcp_input.c#L5886">5886</a>                 break;
<a name="L5887" href="source/net/ipv4/tcp_input.c#L5887">5887</a>         }
<a name="L5888" href="source/net/ipv4/tcp_input.c#L5888">5888</a> 
<a name="L5889" href="source/net/ipv4/tcp_input.c#L5889">5889</a>         case TCP_CLOSING:
<a name="L5890" href="source/net/ipv4/tcp_input.c#L5890">5890</a>                 if (<a href="ident?i=tp">tp</a>-&gt;snd_una == <a href="ident?i=tp">tp</a>-&gt;write_seq) {
<a name="L5891" href="source/net/ipv4/tcp_input.c#L5891">5891</a>                         <a href="ident?i=tcp_time_wait">tcp_time_wait</a>(sk, TCP_TIME_WAIT, 0);
<a name="L5892" href="source/net/ipv4/tcp_input.c#L5892">5892</a>                         goto <a href="ident?i=discard">discard</a>;
<a name="L5893" href="source/net/ipv4/tcp_input.c#L5893">5893</a>                 }
<a name="L5894" href="source/net/ipv4/tcp_input.c#L5894">5894</a>                 break;
<a name="L5895" href="source/net/ipv4/tcp_input.c#L5895">5895</a> 
<a name="L5896" href="source/net/ipv4/tcp_input.c#L5896">5896</a>         case TCP_LAST_ACK:
<a name="L5897" href="source/net/ipv4/tcp_input.c#L5897">5897</a>                 if (<a href="ident?i=tp">tp</a>-&gt;snd_una == <a href="ident?i=tp">tp</a>-&gt;write_seq) {
<a name="L5898" href="source/net/ipv4/tcp_input.c#L5898">5898</a>                         <a href="ident?i=tcp_update_metrics">tcp_update_metrics</a>(sk);
<a name="L5899" href="source/net/ipv4/tcp_input.c#L5899">5899</a>                         <a href="ident?i=tcp_done">tcp_done</a>(sk);
<a name="L5900" href="source/net/ipv4/tcp_input.c#L5900">5900</a>                         goto <a href="ident?i=discard">discard</a>;
<a name="L5901" href="source/net/ipv4/tcp_input.c#L5901">5901</a>                 }
<a name="L5902" href="source/net/ipv4/tcp_input.c#L5902">5902</a>                 break;
<a name="L5903" href="source/net/ipv4/tcp_input.c#L5903">5903</a>         }
<a name="L5904" href="source/net/ipv4/tcp_input.c#L5904">5904</a> 
<a name="L5905" href="source/net/ipv4/tcp_input.c#L5905">5905</a>         <b><i>/* step 6: check the URG bit */</i></b>
<a name="L5906" href="source/net/ipv4/tcp_input.c#L5906">5906</a>         <a href="ident?i=tcp_urg">tcp_urg</a>(sk, <a href="ident?i=skb">skb</a>, <a href="ident?i=th">th</a>);
<a name="L5907" href="source/net/ipv4/tcp_input.c#L5907">5907</a> 
<a name="L5908" href="source/net/ipv4/tcp_input.c#L5908">5908</a>         <b><i>/* step 7: process the segment text */</i></b>
<a name="L5909" href="source/net/ipv4/tcp_input.c#L5909">5909</a>         switch (sk-&gt;<a href="ident?i=sk_state">sk_state</a>) {
<a name="L5910" href="source/net/ipv4/tcp_input.c#L5910">5910</a>         case TCP_CLOSE_WAIT:
<a name="L5911" href="source/net/ipv4/tcp_input.c#L5911">5911</a>         case TCP_CLOSING:
<a name="L5912" href="source/net/ipv4/tcp_input.c#L5912">5912</a>         case TCP_LAST_ACK:
<a name="L5913" href="source/net/ipv4/tcp_input.c#L5913">5913</a>                 if (!<a href="ident?i=before">before</a>(<a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=seq">seq</a>, <a href="ident?i=tp">tp</a>-&gt;rcv_nxt))
<a name="L5914" href="source/net/ipv4/tcp_input.c#L5914">5914</a>                         break;
<a name="L5915" href="source/net/ipv4/tcp_input.c#L5915">5915</a>         case TCP_FIN_WAIT1:
<a name="L5916" href="source/net/ipv4/tcp_input.c#L5916">5916</a>         case TCP_FIN_WAIT2:
<a name="L5917" href="source/net/ipv4/tcp_input.c#L5917">5917</a>                 <b><i>/* RFC 793 says to queue data in these states,</i></b>
<a name="L5918" href="source/net/ipv4/tcp_input.c#L5918">5918</a> <b><i>                 * RFC 1122 says we MUST send a reset.</i></b>
<a name="L5919" href="source/net/ipv4/tcp_input.c#L5919">5919</a> <b><i>                 * BSD 4.4 also does reset.</i></b>
<a name="L5920" href="source/net/ipv4/tcp_input.c#L5920">5920</a> <b><i>                 */</i></b>
<a name="L5921" href="source/net/ipv4/tcp_input.c#L5921">5921</a>                 if (sk-&gt;sk_shutdown &amp; <a href="ident?i=RCV_SHUTDOWN">RCV_SHUTDOWN</a>) {
<a name="L5922" href="source/net/ipv4/tcp_input.c#L5922">5922</a>                         if (<a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;end_seq != <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=seq">seq</a> &amp;&amp;
<a name="L5923" href="source/net/ipv4/tcp_input.c#L5923">5923</a>                             <a href="ident?i=after">after</a>(<a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;end_seq - <a href="ident?i=th">th</a>-&gt;fin, <a href="ident?i=tp">tp</a>-&gt;rcv_nxt)) {
<a name="L5924" href="source/net/ipv4/tcp_input.c#L5924">5924</a>                                 <a href="ident?i=NET_INC_STATS_BH">NET_INC_STATS_BH</a>(<a href="ident?i=sock_net">sock_net</a>(sk), LINUX_MIB_TCPABORTONDATA);
<a name="L5925" href="source/net/ipv4/tcp_input.c#L5925">5925</a>                                 <a href="ident?i=tcp_reset">tcp_reset</a>(sk);
<a name="L5926" href="source/net/ipv4/tcp_input.c#L5926">5926</a>                                 return 1;
<a name="L5927" href="source/net/ipv4/tcp_input.c#L5927">5927</a>                         }
<a name="L5928" href="source/net/ipv4/tcp_input.c#L5928">5928</a>                 }
<a name="L5929" href="source/net/ipv4/tcp_input.c#L5929">5929</a>                 <b><i>/* Fall through */</i></b>
<a name="L5930" href="source/net/ipv4/tcp_input.c#L5930">5930</a>         case TCP_ESTABLISHED:
<a name="L5931" href="source/net/ipv4/tcp_input.c#L5931">5931</a>                 <a href="ident?i=tcp_data_queue">tcp_data_queue</a>(sk, <a href="ident?i=skb">skb</a>);
<a name="L5932" href="source/net/ipv4/tcp_input.c#L5932">5932</a>                 queued = 1;
<a name="L5933" href="source/net/ipv4/tcp_input.c#L5933">5933</a>                 break;
<a name="L5934" href="source/net/ipv4/tcp_input.c#L5934">5934</a>         }
<a name="L5935" href="source/net/ipv4/tcp_input.c#L5935">5935</a> 
<a name="L5936" href="source/net/ipv4/tcp_input.c#L5936">5936</a>         <b><i>/* tcp_data could move socket to TIME-WAIT */</i></b>
<a name="L5937" href="source/net/ipv4/tcp_input.c#L5937">5937</a>         if (sk-&gt;<a href="ident?i=sk_state">sk_state</a> != TCP_CLOSE) {
<a name="L5938" href="source/net/ipv4/tcp_input.c#L5938">5938</a>                 <a href="ident?i=tcp_data_snd_check">tcp_data_snd_check</a>(sk);
<a name="L5939" href="source/net/ipv4/tcp_input.c#L5939">5939</a>                 <a href="ident?i=tcp_ack_snd_check">tcp_ack_snd_check</a>(sk);
<a name="L5940" href="source/net/ipv4/tcp_input.c#L5940">5940</a>         }
<a name="L5941" href="source/net/ipv4/tcp_input.c#L5941">5941</a> 
<a name="L5942" href="source/net/ipv4/tcp_input.c#L5942">5942</a>         if (!queued) {
<a name="L5943" href="source/net/ipv4/tcp_input.c#L5943">5943</a> <a href="ident?i=discard">discard</a>:
<a name="L5944" href="source/net/ipv4/tcp_input.c#L5944">5944</a>                 <a href="ident?i=__kfree_skb">__kfree_skb</a>(<a href="ident?i=skb">skb</a>);
<a name="L5945" href="source/net/ipv4/tcp_input.c#L5945">5945</a>         }
<a name="L5946" href="source/net/ipv4/tcp_input.c#L5946">5946</a>         return 0;
<a name="L5947" href="source/net/ipv4/tcp_input.c#L5947">5947</a> }
<a name="L5948" href="source/net/ipv4/tcp_input.c#L5948">5948</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=tcp_rcv_state_process">tcp_rcv_state_process</a>);
<a name="L5949" href="source/net/ipv4/tcp_input.c#L5949">5949</a> 
<a name="L5950" href="source/net/ipv4/tcp_input.c#L5950">5950</a> static inline void <a href="ident?i=pr_drop_req">pr_drop_req</a>(struct <a href="ident?i=request_sock">request_sock</a> *<a href="ident?i=req">req</a>, <a href="ident?i=__u16">__u16</a> <a href="ident?i=port">port</a>, int <a href="ident?i=family">family</a>)
<a name="L5951" href="source/net/ipv4/tcp_input.c#L5951">5951</a> {
<a name="L5952" href="source/net/ipv4/tcp_input.c#L5952">5952</a>         struct <a href="ident?i=inet_request_sock">inet_request_sock</a> *ireq = <a href="ident?i=inet_rsk">inet_rsk</a>(<a href="ident?i=req">req</a>);
<a name="L5953" href="source/net/ipv4/tcp_input.c#L5953">5953</a> 
<a name="L5954" href="source/net/ipv4/tcp_input.c#L5954">5954</a>         if (<a href="ident?i=family">family</a> == <a href="ident?i=AF_INET">AF_INET</a>)
<a name="L5955" href="source/net/ipv4/tcp_input.c#L5955">5955</a>                 <a href="ident?i=net_dbg_ratelimited">net_dbg_ratelimited</a>(<i>"drop open request from %pI4/%u\n"</i>,
<a name="L5956" href="source/net/ipv4/tcp_input.c#L5956">5956</a>                                     &amp;ireq-&gt;<a href="ident?i=ir_rmt_addr">ir_rmt_addr</a>, <a href="ident?i=port">port</a>);
<a name="L5957" href="source/net/ipv4/tcp_input.c#L5957">5957</a> #if <a href="ident?i=IS_ENABLED">IS_ENABLED</a>(CONFIG_IPV6)
<a name="L5958" href="source/net/ipv4/tcp_input.c#L5958">5958</a>         else if (<a href="ident?i=family">family</a> == <a href="ident?i=AF_INET6">AF_INET6</a>)
<a name="L5959" href="source/net/ipv4/tcp_input.c#L5959">5959</a>                 <a href="ident?i=net_dbg_ratelimited">net_dbg_ratelimited</a>(<i>"drop open request from %pI6/%u\n"</i>,
<a name="L5960" href="source/net/ipv4/tcp_input.c#L5960">5960</a>                                     &amp;ireq-&gt;<a href="ident?i=ir_v6_rmt_addr">ir_v6_rmt_addr</a>, <a href="ident?i=port">port</a>);
<a name="L5961" href="source/net/ipv4/tcp_input.c#L5961">5961</a> #endif
<a name="L5962" href="source/net/ipv4/tcp_input.c#L5962">5962</a> }
<a name="L5963" href="source/net/ipv4/tcp_input.c#L5963">5963</a> 
<a name="L5964" href="source/net/ipv4/tcp_input.c#L5964">5964</a> <b><i>/* RFC3168 : 6.1.1 SYN packets must not have ECT/ECN bits set</i></b>
<a name="L5965" href="source/net/ipv4/tcp_input.c#L5965">5965</a> <b><i> *</i></b>
<a name="L5966" href="source/net/ipv4/tcp_input.c#L5966">5966</a> <b><i> * If we receive a SYN packet with these bits set, it means a</i></b>
<a name="L5967" href="source/net/ipv4/tcp_input.c#L5967">5967</a> <b><i> * network is playing bad games with TOS bits. In order to</i></b>
<a name="L5968" href="source/net/ipv4/tcp_input.c#L5968">5968</a> <b><i> * avoid possible false congestion notifications, we disable</i></b>
<a name="L5969" href="source/net/ipv4/tcp_input.c#L5969">5969</a> <b><i> * TCP ECN negotiation.</i></b>
<a name="L5970" href="source/net/ipv4/tcp_input.c#L5970">5970</a> <b><i> *</i></b>
<a name="L5971" href="source/net/ipv4/tcp_input.c#L5971">5971</a> <b><i> * Exception: tcp_ca wants ECN. This is required for DCTCP</i></b>
<a name="L5972" href="source/net/ipv4/tcp_input.c#L5972">5972</a> <b><i> * congestion control: Linux DCTCP asserts ECT on all packets,</i></b>
<a name="L5973" href="source/net/ipv4/tcp_input.c#L5973">5973</a> <b><i> * including SYN, which is most optimal solution; however,</i></b>
<a name="L5974" href="source/net/ipv4/tcp_input.c#L5974">5974</a> <b><i> * others, such as FreeBSD do not.</i></b>
<a name="L5975" href="source/net/ipv4/tcp_input.c#L5975">5975</a> <b><i> */</i></b>
<a name="L5976" href="source/net/ipv4/tcp_input.c#L5976">5976</a> static void <a href="ident?i=tcp_ecn_create_request">tcp_ecn_create_request</a>(struct <a href="ident?i=request_sock">request_sock</a> *<a href="ident?i=req">req</a>,
<a name="L5977" href="source/net/ipv4/tcp_input.c#L5977">5977</a>                                    const struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
<a name="L5978" href="source/net/ipv4/tcp_input.c#L5978">5978</a>                                    const struct <a href="ident?i=sock">sock</a> *listen_sk,
<a name="L5979" href="source/net/ipv4/tcp_input.c#L5979">5979</a>                                    const struct <a href="ident?i=dst_entry">dst_entry</a> *<a href="ident?i=dst">dst</a>)
<a name="L5980" href="source/net/ipv4/tcp_input.c#L5980">5980</a> {
<a name="L5981" href="source/net/ipv4/tcp_input.c#L5981">5981</a>         const struct <a href="ident?i=tcphdr">tcphdr</a> *<a href="ident?i=th">th</a> = <a href="ident?i=tcp_hdr">tcp_hdr</a>(<a href="ident?i=skb">skb</a>);
<a name="L5982" href="source/net/ipv4/tcp_input.c#L5982">5982</a>         const struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=sock_net">sock_net</a>(listen_sk);
<a name="L5983" href="source/net/ipv4/tcp_input.c#L5983">5983</a>         <a href="ident?i=bool">bool</a> th_ecn = <a href="ident?i=th">th</a>-&gt;ece &amp;&amp; <a href="ident?i=th">th</a>-&gt;cwr;
<a name="L5984" href="source/net/ipv4/tcp_input.c#L5984">5984</a>         <a href="ident?i=bool">bool</a> ect, ecn_ok;
<a name="L5985" href="source/net/ipv4/tcp_input.c#L5985">5985</a> 
<a name="L5986" href="source/net/ipv4/tcp_input.c#L5986">5986</a>         if (!th_ecn)
<a name="L5987" href="source/net/ipv4/tcp_input.c#L5987">5987</a>                 return;
<a name="L5988" href="source/net/ipv4/tcp_input.c#L5988">5988</a> 
<a name="L5989" href="source/net/ipv4/tcp_input.c#L5989">5989</a>         ect = !<a href="ident?i=INET_ECN_is_not_ect">INET_ECN_is_not_ect</a>(<a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;ip_dsfield);
<a name="L5990" href="source/net/ipv4/tcp_input.c#L5990">5990</a>         ecn_ok = <a href="ident?i=net">net</a>-&gt;ipv4.sysctl_tcp_ecn || <a href="ident?i=dst_feature">dst_feature</a>(<a href="ident?i=dst">dst</a>, <a href="ident?i=RTAX_FEATURE_ECN">RTAX_FEATURE_ECN</a>);
<a name="L5991" href="source/net/ipv4/tcp_input.c#L5991">5991</a> 
<a name="L5992" href="source/net/ipv4/tcp_input.c#L5992">5992</a>         if ((!ect &amp;&amp; ecn_ok) || <a href="ident?i=tcp_ca_needs_ecn">tcp_ca_needs_ecn</a>(listen_sk))
<a name="L5993" href="source/net/ipv4/tcp_input.c#L5993">5993</a>                 <a href="ident?i=inet_rsk">inet_rsk</a>(<a href="ident?i=req">req</a>)-&gt;ecn_ok = 1;
<a name="L5994" href="source/net/ipv4/tcp_input.c#L5994">5994</a> }
<a name="L5995" href="source/net/ipv4/tcp_input.c#L5995">5995</a> 
<a name="L5996" href="source/net/ipv4/tcp_input.c#L5996">5996</a> static void <a href="ident?i=tcp_openreq_init">tcp_openreq_init</a>(struct <a href="ident?i=request_sock">request_sock</a> *<a href="ident?i=req">req</a>,
<a name="L5997" href="source/net/ipv4/tcp_input.c#L5997">5997</a>                              const struct <a href="ident?i=tcp_options_received">tcp_options_received</a> *rx_opt,
<a name="L5998" href="source/net/ipv4/tcp_input.c#L5998">5998</a>                              struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, const struct <a href="ident?i=sock">sock</a> *sk)
<a name="L5999" href="source/net/ipv4/tcp_input.c#L5999">5999</a> {
<a name="L6000" href="source/net/ipv4/tcp_input.c#L6000">6000</a>         struct <a href="ident?i=inet_request_sock">inet_request_sock</a> *ireq = <a href="ident?i=inet_rsk">inet_rsk</a>(<a href="ident?i=req">req</a>);
<a name="L6001" href="source/net/ipv4/tcp_input.c#L6001">6001</a> 
<a name="L6002" href="source/net/ipv4/tcp_input.c#L6002">6002</a>         <a href="ident?i=req">req</a>-&gt;rcv_wnd = 0;               <b><i>/* So that tcp_send_synack() knows! */</i></b>
<a name="L6003" href="source/net/ipv4/tcp_input.c#L6003">6003</a>         <a href="ident?i=req">req</a>-&gt;cookie_ts = 0;
<a name="L6004" href="source/net/ipv4/tcp_input.c#L6004">6004</a>         <a href="ident?i=tcp_rsk">tcp_rsk</a>(<a href="ident?i=req">req</a>)-&gt;rcv_isn = <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=seq">seq</a>;
<a name="L6005" href="source/net/ipv4/tcp_input.c#L6005">6005</a>         <a href="ident?i=tcp_rsk">tcp_rsk</a>(<a href="ident?i=req">req</a>)-&gt;rcv_nxt = <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=seq">seq</a> + 1;
<a name="L6006" href="source/net/ipv4/tcp_input.c#L6006">6006</a>         <a href="ident?i=tcp_rsk">tcp_rsk</a>(<a href="ident?i=req">req</a>)-&gt;snt_synack = <a href="ident?i=tcp_time_stamp">tcp_time_stamp</a>;
<a name="L6007" href="source/net/ipv4/tcp_input.c#L6007">6007</a>         <a href="ident?i=tcp_rsk">tcp_rsk</a>(<a href="ident?i=req">req</a>)-&gt;last_oow_ack_time = 0;
<a name="L6008" href="source/net/ipv4/tcp_input.c#L6008">6008</a>         <a href="ident?i=req">req</a>-&gt;mss = rx_opt-&gt;mss_clamp;
<a name="L6009" href="source/net/ipv4/tcp_input.c#L6009">6009</a>         <a href="ident?i=req">req</a>-&gt;ts_recent = rx_opt-&gt;saw_tstamp ? rx_opt-&gt;rcv_tsval : 0;
<a name="L6010" href="source/net/ipv4/tcp_input.c#L6010">6010</a>         ireq-&gt;tstamp_ok = rx_opt-&gt;tstamp_ok;
<a name="L6011" href="source/net/ipv4/tcp_input.c#L6011">6011</a>         ireq-&gt;sack_ok = rx_opt-&gt;sack_ok;
<a name="L6012" href="source/net/ipv4/tcp_input.c#L6012">6012</a>         ireq-&gt;snd_wscale = rx_opt-&gt;snd_wscale;
<a name="L6013" href="source/net/ipv4/tcp_input.c#L6013">6013</a>         ireq-&gt;wscale_ok = rx_opt-&gt;wscale_ok;
<a name="L6014" href="source/net/ipv4/tcp_input.c#L6014">6014</a>         ireq-&gt;acked = 0;
<a name="L6015" href="source/net/ipv4/tcp_input.c#L6015">6015</a>         ireq-&gt;ecn_ok = 0;
<a name="L6016" href="source/net/ipv4/tcp_input.c#L6016">6016</a>         ireq-&gt;<a href="ident?i=ir_rmt_port">ir_rmt_port</a> = <a href="ident?i=tcp_hdr">tcp_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;source;
<a name="L6017" href="source/net/ipv4/tcp_input.c#L6017">6017</a>         ireq-&gt;<a href="ident?i=ir_num">ir_num</a> = <a href="ident?i=ntohs">ntohs</a>(<a href="ident?i=tcp_hdr">tcp_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=dest">dest</a>);
<a name="L6018" href="source/net/ipv4/tcp_input.c#L6018">6018</a>         ireq-&gt;ir_mark = <a href="ident?i=inet_request_mark">inet_request_mark</a>(sk, <a href="ident?i=skb">skb</a>);
<a name="L6019" href="source/net/ipv4/tcp_input.c#L6019">6019</a> }
<a name="L6020" href="source/net/ipv4/tcp_input.c#L6020">6020</a> 
<a name="L6021" href="source/net/ipv4/tcp_input.c#L6021">6021</a> struct <a href="ident?i=request_sock">request_sock</a> *<a href="ident?i=inet_reqsk_alloc">inet_reqsk_alloc</a>(const struct <a href="ident?i=request_sock_ops">request_sock_ops</a> *<a href="ident?i=ops">ops</a>,
<a name="L6022" href="source/net/ipv4/tcp_input.c#L6022">6022</a>                                       struct <a href="ident?i=sock">sock</a> *sk_listener)
<a name="L6023" href="source/net/ipv4/tcp_input.c#L6023">6023</a> {
<a name="L6024" href="source/net/ipv4/tcp_input.c#L6024">6024</a>         struct <a href="ident?i=request_sock">request_sock</a> *<a href="ident?i=req">req</a> = <a href="ident?i=reqsk_alloc">reqsk_alloc</a>(<a href="ident?i=ops">ops</a>, sk_listener);
<a name="L6025" href="source/net/ipv4/tcp_input.c#L6025">6025</a> 
<a name="L6026" href="source/net/ipv4/tcp_input.c#L6026">6026</a>         if (<a href="ident?i=req">req</a>) {
<a name="L6027" href="source/net/ipv4/tcp_input.c#L6027">6027</a>                 struct <a href="ident?i=inet_request_sock">inet_request_sock</a> *ireq = <a href="ident?i=inet_rsk">inet_rsk</a>(<a href="ident?i=req">req</a>);
<a name="L6028" href="source/net/ipv4/tcp_input.c#L6028">6028</a> 
<a name="L6029" href="source/net/ipv4/tcp_input.c#L6029">6029</a>                 <a href="ident?i=kmemcheck_annotate_bitfield">kmemcheck_annotate_bitfield</a>(ireq, <a href="ident?i=flags">flags</a>);
<a name="L6030" href="source/net/ipv4/tcp_input.c#L6030">6030</a>                 ireq-&gt;opt = <a href="ident?i=NULL">NULL</a>;
<a name="L6031" href="source/net/ipv4/tcp_input.c#L6031">6031</a>                 <a href="ident?i=atomic64_set">atomic64_set</a>(&amp;ireq-&gt;<a href="ident?i=ir_cookie">ir_cookie</a>, 0);
<a name="L6032" href="source/net/ipv4/tcp_input.c#L6032">6032</a>                 ireq-&gt;<a href="ident?i=ireq_state">ireq_state</a> = TCP_NEW_SYN_RECV;
<a name="L6033" href="source/net/ipv4/tcp_input.c#L6033">6033</a>                 <a href="ident?i=write_pnet">write_pnet</a>(&amp;ireq-&gt;<a href="ident?i=ireq_net">ireq_net</a>, <a href="ident?i=sock_net">sock_net</a>(sk_listener));
<a name="L6034" href="source/net/ipv4/tcp_input.c#L6034">6034</a>                 ireq-&gt;<a href="ident?i=ireq_family">ireq_family</a> = sk_listener-&gt;<a href="ident?i=sk_family">sk_family</a>;
<a name="L6035" href="source/net/ipv4/tcp_input.c#L6035">6035</a>         }
<a name="L6036" href="source/net/ipv4/tcp_input.c#L6036">6036</a> 
<a name="L6037" href="source/net/ipv4/tcp_input.c#L6037">6037</a>         return <a href="ident?i=req">req</a>;
<a name="L6038" href="source/net/ipv4/tcp_input.c#L6038">6038</a> }
<a name="L6039" href="source/net/ipv4/tcp_input.c#L6039">6039</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=inet_reqsk_alloc">inet_reqsk_alloc</a>);
<a name="L6040" href="source/net/ipv4/tcp_input.c#L6040">6040</a> 
<a name="L6041" href="source/net/ipv4/tcp_input.c#L6041">6041</a> <b><i>/*</i></b>
<a name="L6042" href="source/net/ipv4/tcp_input.c#L6042">6042</a> <b><i> * Return true if a syncookie should be sent</i></b>
<a name="L6043" href="source/net/ipv4/tcp_input.c#L6043">6043</a> <b><i> */</i></b>
<a name="L6044" href="source/net/ipv4/tcp_input.c#L6044">6044</a> static <a href="ident?i=bool">bool</a> <a href="ident?i=tcp_syn_flood_action">tcp_syn_flood_action</a>(struct <a href="ident?i=sock">sock</a> *sk,
<a name="L6045" href="source/net/ipv4/tcp_input.c#L6045">6045</a>                                  const struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
<a name="L6046" href="source/net/ipv4/tcp_input.c#L6046">6046</a>                                  const char *<a href="ident?i=proto">proto</a>)
<a name="L6047" href="source/net/ipv4/tcp_input.c#L6047">6047</a> {
<a name="L6048" href="source/net/ipv4/tcp_input.c#L6048">6048</a>         const char *<a href="ident?i=msg">msg</a> = <i>"Dropping request"</i>;
<a name="L6049" href="source/net/ipv4/tcp_input.c#L6049">6049</a>         <a href="ident?i=bool">bool</a> want_cookie = <a href="ident?i=false">false</a>;
<a name="L6050" href="source/net/ipv4/tcp_input.c#L6050">6050</a>         struct <a href="ident?i=listen_sock">listen_sock</a> *lopt;
<a name="L6051" href="source/net/ipv4/tcp_input.c#L6051">6051</a> 
<a name="L6052" href="source/net/ipv4/tcp_input.c#L6052">6052</a> #ifdef CONFIG_SYN_COOKIES
<a name="L6053" href="source/net/ipv4/tcp_input.c#L6053">6053</a>         if (<a href="ident?i=sysctl_tcp_syncookies">sysctl_tcp_syncookies</a>) {
<a name="L6054" href="source/net/ipv4/tcp_input.c#L6054">6054</a>                 <a href="ident?i=msg">msg</a> = <i>"Sending cookies"</i>;
<a name="L6055" href="source/net/ipv4/tcp_input.c#L6055">6055</a>                 want_cookie = <a href="ident?i=true">true</a>;
<a name="L6056" href="source/net/ipv4/tcp_input.c#L6056">6056</a>                 <a href="ident?i=NET_INC_STATS_BH">NET_INC_STATS_BH</a>(<a href="ident?i=sock_net">sock_net</a>(sk), LINUX_MIB_TCPREQQFULLDOCOOKIES);
<a name="L6057" href="source/net/ipv4/tcp_input.c#L6057">6057</a>         } else
<a name="L6058" href="source/net/ipv4/tcp_input.c#L6058">6058</a> #endif
<a name="L6059" href="source/net/ipv4/tcp_input.c#L6059">6059</a>                 <a href="ident?i=NET_INC_STATS_BH">NET_INC_STATS_BH</a>(<a href="ident?i=sock_net">sock_net</a>(sk), LINUX_MIB_TCPREQQFULLDROP);
<a name="L6060" href="source/net/ipv4/tcp_input.c#L6060">6060</a> 
<a name="L6061" href="source/net/ipv4/tcp_input.c#L6061">6061</a>         lopt = <a href="ident?i=inet_csk">inet_csk</a>(sk)-&gt;icsk_accept_queue.listen_opt;
<a name="L6062" href="source/net/ipv4/tcp_input.c#L6062">6062</a>         if (!lopt-&gt;synflood_warned &amp;&amp; <a href="ident?i=sysctl_tcp_syncookies">sysctl_tcp_syncookies</a> != 2) {
<a name="L6063" href="source/net/ipv4/tcp_input.c#L6063">6063</a>                 lopt-&gt;synflood_warned = 1;
<a name="L6064" href="source/net/ipv4/tcp_input.c#L6064">6064</a>                 <a href="ident?i=pr_info">pr_info</a>(<i>"%s: Possible SYN flooding on port %d. %s.  Check SNMP counters.\n"</i>,
<a name="L6065" href="source/net/ipv4/tcp_input.c#L6065">6065</a>                         <a href="ident?i=proto">proto</a>, <a href="ident?i=ntohs">ntohs</a>(<a href="ident?i=tcp_hdr">tcp_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=dest">dest</a>), <a href="ident?i=msg">msg</a>);
<a name="L6066" href="source/net/ipv4/tcp_input.c#L6066">6066</a>         }
<a name="L6067" href="source/net/ipv4/tcp_input.c#L6067">6067</a>         return want_cookie;
<a name="L6068" href="source/net/ipv4/tcp_input.c#L6068">6068</a> }
<a name="L6069" href="source/net/ipv4/tcp_input.c#L6069">6069</a> 
<a name="L6070" href="source/net/ipv4/tcp_input.c#L6070">6070</a> int <a href="ident?i=tcp_conn_request">tcp_conn_request</a>(struct <a href="ident?i=request_sock_ops">request_sock_ops</a> *rsk_ops,
<a name="L6071" href="source/net/ipv4/tcp_input.c#L6071">6071</a>                      const struct <a href="ident?i=tcp_request_sock_ops">tcp_request_sock_ops</a> *af_ops,
<a name="L6072" href="source/net/ipv4/tcp_input.c#L6072">6072</a>                      struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L6073" href="source/net/ipv4/tcp_input.c#L6073">6073</a> {
<a name="L6074" href="source/net/ipv4/tcp_input.c#L6074">6074</a>         struct <a href="ident?i=tcp_options_received">tcp_options_received</a> tmp_opt;
<a name="L6075" href="source/net/ipv4/tcp_input.c#L6075">6075</a>         struct <a href="ident?i=request_sock">request_sock</a> *<a href="ident?i=req">req</a>;
<a name="L6076" href="source/net/ipv4/tcp_input.c#L6076">6076</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L6077" href="source/net/ipv4/tcp_input.c#L6077">6077</a>         struct <a href="ident?i=dst_entry">dst_entry</a> *<a href="ident?i=dst">dst</a> = <a href="ident?i=NULL">NULL</a>;
<a name="L6078" href="source/net/ipv4/tcp_input.c#L6078">6078</a>         <a href="ident?i=__u32">__u32</a> isn = <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;tcp_tw_isn;
<a name="L6079" href="source/net/ipv4/tcp_input.c#L6079">6079</a>         <a href="ident?i=bool">bool</a> want_cookie = <a href="ident?i=false">false</a>, fastopen;
<a name="L6080" href="source/net/ipv4/tcp_input.c#L6080">6080</a>         struct <a href="ident?i=flowi">flowi</a> fl;
<a name="L6081" href="source/net/ipv4/tcp_input.c#L6081">6081</a>         struct <a href="ident?i=tcp_fastopen_cookie">tcp_fastopen_cookie</a> foc = { .<a href="ident?i=len">len</a> = -1 };
<a name="L6082" href="source/net/ipv4/tcp_input.c#L6082">6082</a>         int <a href="ident?i=err">err</a>;
<a name="L6083" href="source/net/ipv4/tcp_input.c#L6083">6083</a> 
<a name="L6084" href="source/net/ipv4/tcp_input.c#L6084">6084</a> 
<a name="L6085" href="source/net/ipv4/tcp_input.c#L6085">6085</a>         <b><i>/* TW buckets are converted to open requests without</i></b>
<a name="L6086" href="source/net/ipv4/tcp_input.c#L6086">6086</a> <b><i>         * limitations, they conserve resources and peer is</i></b>
<a name="L6087" href="source/net/ipv4/tcp_input.c#L6087">6087</a> <b><i>         * evidently real one.</i></b>
<a name="L6088" href="source/net/ipv4/tcp_input.c#L6088">6088</a> <b><i>         */</i></b>
<a name="L6089" href="source/net/ipv4/tcp_input.c#L6089">6089</a>         if ((<a href="ident?i=sysctl_tcp_syncookies">sysctl_tcp_syncookies</a> == 2 ||
<a name="L6090" href="source/net/ipv4/tcp_input.c#L6090">6090</a>              <a href="ident?i=inet_csk_reqsk_queue_is_full">inet_csk_reqsk_queue_is_full</a>(sk)) &amp;&amp; !isn) {
<a name="L6091" href="source/net/ipv4/tcp_input.c#L6091">6091</a>                 want_cookie = <a href="ident?i=tcp_syn_flood_action">tcp_syn_flood_action</a>(sk, <a href="ident?i=skb">skb</a>, rsk_ops-&gt;slab_name);
<a name="L6092" href="source/net/ipv4/tcp_input.c#L6092">6092</a>                 if (!want_cookie)
<a name="L6093" href="source/net/ipv4/tcp_input.c#L6093">6093</a>                         goto <a href="ident?i=drop">drop</a>;
<a name="L6094" href="source/net/ipv4/tcp_input.c#L6094">6094</a>         }
<a name="L6095" href="source/net/ipv4/tcp_input.c#L6095">6095</a> 
<a name="L6096" href="source/net/ipv4/tcp_input.c#L6096">6096</a> 
<a name="L6097" href="source/net/ipv4/tcp_input.c#L6097">6097</a>         <b><i>/* Accept backlog is full. If we have already queued enough</i></b>
<a name="L6098" href="source/net/ipv4/tcp_input.c#L6098">6098</a> <b><i>         * of warm entries in syn queue, drop request. It is better than</i></b>
<a name="L6099" href="source/net/ipv4/tcp_input.c#L6099">6099</a> <b><i>         * clogging syn queue with openreqs with exponentially increasing</i></b>
<a name="L6100" href="source/net/ipv4/tcp_input.c#L6100">6100</a> <b><i>         * timeout.</i></b>
<a name="L6101" href="source/net/ipv4/tcp_input.c#L6101">6101</a> <b><i>         */</i></b>
<a name="L6102" href="source/net/ipv4/tcp_input.c#L6102">6102</a>         if (<a href="ident?i=sk_acceptq_is_full">sk_acceptq_is_full</a>(sk) &amp;&amp; <a href="ident?i=inet_csk_reqsk_queue_young">inet_csk_reqsk_queue_young</a>(sk) &gt; 1) {
<a name="L6103" href="source/net/ipv4/tcp_input.c#L6103">6103</a>                 <a href="ident?i=NET_INC_STATS_BH">NET_INC_STATS_BH</a>(<a href="ident?i=sock_net">sock_net</a>(sk), LINUX_MIB_LISTENOVERFLOWS);
<a name="L6104" href="source/net/ipv4/tcp_input.c#L6104">6104</a>                 goto <a href="ident?i=drop">drop</a>;
<a name="L6105" href="source/net/ipv4/tcp_input.c#L6105">6105</a>         }
<a name="L6106" href="source/net/ipv4/tcp_input.c#L6106">6106</a> 
<a name="L6107" href="source/net/ipv4/tcp_input.c#L6107">6107</a>         <a href="ident?i=req">req</a> = <a href="ident?i=inet_reqsk_alloc">inet_reqsk_alloc</a>(rsk_ops, sk);
<a name="L6108" href="source/net/ipv4/tcp_input.c#L6108">6108</a>         if (!<a href="ident?i=req">req</a>)
<a name="L6109" href="source/net/ipv4/tcp_input.c#L6109">6109</a>                 goto <a href="ident?i=drop">drop</a>;
<a name="L6110" href="source/net/ipv4/tcp_input.c#L6110">6110</a> 
<a name="L6111" href="source/net/ipv4/tcp_input.c#L6111">6111</a>         <a href="ident?i=tcp_rsk">tcp_rsk</a>(<a href="ident?i=req">req</a>)-&gt;af_specific = af_ops;
<a name="L6112" href="source/net/ipv4/tcp_input.c#L6112">6112</a> 
<a name="L6113" href="source/net/ipv4/tcp_input.c#L6113">6113</a>         <a href="ident?i=tcp_clear_options">tcp_clear_options</a>(&amp;tmp_opt);
<a name="L6114" href="source/net/ipv4/tcp_input.c#L6114">6114</a>         tmp_opt.mss_clamp = af_ops-&gt;mss_clamp;
<a name="L6115" href="source/net/ipv4/tcp_input.c#L6115">6115</a>         tmp_opt.user_mss  = <a href="ident?i=tp">tp</a>-&gt;rx_opt.user_mss;
<a name="L6116" href="source/net/ipv4/tcp_input.c#L6116">6116</a>         <a href="ident?i=tcp_parse_options">tcp_parse_options</a>(<a href="ident?i=skb">skb</a>, &amp;tmp_opt, 0, want_cookie ? <a href="ident?i=NULL">NULL</a> : &amp;foc);
<a name="L6117" href="source/net/ipv4/tcp_input.c#L6117">6117</a> 
<a name="L6118" href="source/net/ipv4/tcp_input.c#L6118">6118</a>         if (want_cookie &amp;&amp; !tmp_opt.saw_tstamp)
<a name="L6119" href="source/net/ipv4/tcp_input.c#L6119">6119</a>                 <a href="ident?i=tcp_clear_options">tcp_clear_options</a>(&amp;tmp_opt);
<a name="L6120" href="source/net/ipv4/tcp_input.c#L6120">6120</a> 
<a name="L6121" href="source/net/ipv4/tcp_input.c#L6121">6121</a>         tmp_opt.tstamp_ok = tmp_opt.saw_tstamp;
<a name="L6122" href="source/net/ipv4/tcp_input.c#L6122">6122</a>         <a href="ident?i=tcp_openreq_init">tcp_openreq_init</a>(<a href="ident?i=req">req</a>, &amp;tmp_opt, <a href="ident?i=skb">skb</a>, sk);
<a name="L6123" href="source/net/ipv4/tcp_input.c#L6123">6123</a> 
<a name="L6124" href="source/net/ipv4/tcp_input.c#L6124">6124</a>         <b><i>/* Note: tcp_v6_init_req() might override ir_iif for link locals */</i></b>
<a name="L6125" href="source/net/ipv4/tcp_input.c#L6125">6125</a>         <a href="ident?i=inet_rsk">inet_rsk</a>(<a href="ident?i=req">req</a>)-&gt;<a href="ident?i=ir_iif">ir_iif</a> = sk-&gt;<a href="ident?i=sk_bound_dev_if">sk_bound_dev_if</a>;
<a name="L6126" href="source/net/ipv4/tcp_input.c#L6126">6126</a> 
<a name="L6127" href="source/net/ipv4/tcp_input.c#L6127">6127</a>         af_ops-&gt;init_req(<a href="ident?i=req">req</a>, sk, <a href="ident?i=skb">skb</a>);
<a name="L6128" href="source/net/ipv4/tcp_input.c#L6128">6128</a> 
<a name="L6129" href="source/net/ipv4/tcp_input.c#L6129">6129</a>         if (<a href="ident?i=security_inet_conn_request">security_inet_conn_request</a>(sk, <a href="ident?i=skb">skb</a>, <a href="ident?i=req">req</a>))
<a name="L6130" href="source/net/ipv4/tcp_input.c#L6130">6130</a>                 goto drop_and_free;
<a name="L6131" href="source/net/ipv4/tcp_input.c#L6131">6131</a> 
<a name="L6132" href="source/net/ipv4/tcp_input.c#L6132">6132</a>         if (!want_cookie &amp;&amp; !isn) {
<a name="L6133" href="source/net/ipv4/tcp_input.c#L6133">6133</a>                 <b><i>/* VJ's idea. We save last timestamp seen</i></b>
<a name="L6134" href="source/net/ipv4/tcp_input.c#L6134">6134</a> <b><i>                 * from the destination in peer table, when entering</i></b>
<a name="L6135" href="source/net/ipv4/tcp_input.c#L6135">6135</a> <b><i>                 * state TIME-WAIT, and check against it before</i></b>
<a name="L6136" href="source/net/ipv4/tcp_input.c#L6136">6136</a> <b><i>                 * accepting new connection request.</i></b>
<a name="L6137" href="source/net/ipv4/tcp_input.c#L6137">6137</a> <b><i>                 *</i></b>
<a name="L6138" href="source/net/ipv4/tcp_input.c#L6138">6138</a> <b><i>                 * If "isn" is not zero, this request hit alive</i></b>
<a name="L6139" href="source/net/ipv4/tcp_input.c#L6139">6139</a> <b><i>                 * timewait bucket, so that all the necessary checks</i></b>
<a name="L6140" href="source/net/ipv4/tcp_input.c#L6140">6140</a> <b><i>                 * are made in the function processing timewait state.</i></b>
<a name="L6141" href="source/net/ipv4/tcp_input.c#L6141">6141</a> <b><i>                 */</i></b>
<a name="L6142" href="source/net/ipv4/tcp_input.c#L6142">6142</a>                 if (<a href="ident?i=tcp_death_row">tcp_death_row</a>.sysctl_tw_recycle) {
<a name="L6143" href="source/net/ipv4/tcp_input.c#L6143">6143</a>                         <a href="ident?i=bool">bool</a> strict;
<a name="L6144" href="source/net/ipv4/tcp_input.c#L6144">6144</a> 
<a name="L6145" href="source/net/ipv4/tcp_input.c#L6145">6145</a>                         <a href="ident?i=dst">dst</a> = af_ops-&gt;route_req(sk, &amp;fl, <a href="ident?i=req">req</a>, &amp;strict);
<a name="L6146" href="source/net/ipv4/tcp_input.c#L6146">6146</a> 
<a name="L6147" href="source/net/ipv4/tcp_input.c#L6147">6147</a>                         if (<a href="ident?i=dst">dst</a> &amp;&amp; strict &amp;&amp;
<a name="L6148" href="source/net/ipv4/tcp_input.c#L6148">6148</a>                             !<a href="ident?i=tcp_peer_is_proven">tcp_peer_is_proven</a>(<a href="ident?i=req">req</a>, <a href="ident?i=dst">dst</a>, <a href="ident?i=true">true</a>,
<a name="L6149" href="source/net/ipv4/tcp_input.c#L6149">6149</a>                                                 tmp_opt.saw_tstamp)) {
<a name="L6150" href="source/net/ipv4/tcp_input.c#L6150">6150</a>                                 <a href="ident?i=NET_INC_STATS_BH">NET_INC_STATS_BH</a>(<a href="ident?i=sock_net">sock_net</a>(sk), LINUX_MIB_PAWSPASSIVEREJECTED);
<a name="L6151" href="source/net/ipv4/tcp_input.c#L6151">6151</a>                                 goto drop_and_release;
<a name="L6152" href="source/net/ipv4/tcp_input.c#L6152">6152</a>                         }
<a name="L6153" href="source/net/ipv4/tcp_input.c#L6153">6153</a>                 }
<a name="L6154" href="source/net/ipv4/tcp_input.c#L6154">6154</a>                 <b><i>/* Kill the following clause, if you dislike this way. */</i></b>
<a name="L6155" href="source/net/ipv4/tcp_input.c#L6155">6155</a>                 else if (!<a href="ident?i=sysctl_tcp_syncookies">sysctl_tcp_syncookies</a> &amp;&amp;
<a name="L6156" href="source/net/ipv4/tcp_input.c#L6156">6156</a>                          (<a href="ident?i=sysctl_max_syn_backlog">sysctl_max_syn_backlog</a> - <a href="ident?i=inet_csk_reqsk_queue_len">inet_csk_reqsk_queue_len</a>(sk) &lt;
<a name="L6157" href="source/net/ipv4/tcp_input.c#L6157">6157</a>                           (<a href="ident?i=sysctl_max_syn_backlog">sysctl_max_syn_backlog</a> &gt;&gt; 2)) &amp;&amp;
<a name="L6158" href="source/net/ipv4/tcp_input.c#L6158">6158</a>                          !<a href="ident?i=tcp_peer_is_proven">tcp_peer_is_proven</a>(<a href="ident?i=req">req</a>, <a href="ident?i=dst">dst</a>, <a href="ident?i=false">false</a>,
<a name="L6159" href="source/net/ipv4/tcp_input.c#L6159">6159</a>                                              tmp_opt.saw_tstamp)) {
<a name="L6160" href="source/net/ipv4/tcp_input.c#L6160">6160</a>                         <b><i>/* Without syncookies last quarter of</i></b>
<a name="L6161" href="source/net/ipv4/tcp_input.c#L6161">6161</a> <b><i>                         * backlog is filled with destinations,</i></b>
<a name="L6162" href="source/net/ipv4/tcp_input.c#L6162">6162</a> <b><i>                         * proven to be alive.</i></b>
<a name="L6163" href="source/net/ipv4/tcp_input.c#L6163">6163</a> <b><i>                         * It means that we continue to communicate</i></b>
<a name="L6164" href="source/net/ipv4/tcp_input.c#L6164">6164</a> <b><i>                         * to destinations, already remembered</i></b>
<a name="L6165" href="source/net/ipv4/tcp_input.c#L6165">6165</a> <b><i>                         * to the moment of synflood.</i></b>
<a name="L6166" href="source/net/ipv4/tcp_input.c#L6166">6166</a> <b><i>                         */</i></b>
<a name="L6167" href="source/net/ipv4/tcp_input.c#L6167">6167</a>                         <a href="ident?i=pr_drop_req">pr_drop_req</a>(<a href="ident?i=req">req</a>, <a href="ident?i=ntohs">ntohs</a>(<a href="ident?i=tcp_hdr">tcp_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;source),
<a name="L6168" href="source/net/ipv4/tcp_input.c#L6168">6168</a>                                     rsk_ops-&gt;<a href="ident?i=family">family</a>);
<a name="L6169" href="source/net/ipv4/tcp_input.c#L6169">6169</a>                         goto drop_and_release;
<a name="L6170" href="source/net/ipv4/tcp_input.c#L6170">6170</a>                 }
<a name="L6171" href="source/net/ipv4/tcp_input.c#L6171">6171</a> 
<a name="L6172" href="source/net/ipv4/tcp_input.c#L6172">6172</a>                 isn = af_ops-&gt;<a href="ident?i=init_seq">init_seq</a>(<a href="ident?i=skb">skb</a>);
<a name="L6173" href="source/net/ipv4/tcp_input.c#L6173">6173</a>         }
<a name="L6174" href="source/net/ipv4/tcp_input.c#L6174">6174</a>         if (!<a href="ident?i=dst">dst</a>) {
<a name="L6175" href="source/net/ipv4/tcp_input.c#L6175">6175</a>                 <a href="ident?i=dst">dst</a> = af_ops-&gt;route_req(sk, &amp;fl, <a href="ident?i=req">req</a>, <a href="ident?i=NULL">NULL</a>);
<a name="L6176" href="source/net/ipv4/tcp_input.c#L6176">6176</a>                 if (!<a href="ident?i=dst">dst</a>)
<a name="L6177" href="source/net/ipv4/tcp_input.c#L6177">6177</a>                         goto drop_and_free;
<a name="L6178" href="source/net/ipv4/tcp_input.c#L6178">6178</a>         }
<a name="L6179" href="source/net/ipv4/tcp_input.c#L6179">6179</a> 
<a name="L6180" href="source/net/ipv4/tcp_input.c#L6180">6180</a>         <a href="ident?i=tcp_ecn_create_request">tcp_ecn_create_request</a>(<a href="ident?i=req">req</a>, <a href="ident?i=skb">skb</a>, sk, <a href="ident?i=dst">dst</a>);
<a name="L6181" href="source/net/ipv4/tcp_input.c#L6181">6181</a> 
<a name="L6182" href="source/net/ipv4/tcp_input.c#L6182">6182</a>         if (want_cookie) {
<a name="L6183" href="source/net/ipv4/tcp_input.c#L6183">6183</a>                 isn = <a href="ident?i=cookie_init_sequence">cookie_init_sequence</a>(af_ops, sk, <a href="ident?i=skb">skb</a>, &amp;<a href="ident?i=req">req</a>-&gt;mss);
<a name="L6184" href="source/net/ipv4/tcp_input.c#L6184">6184</a>                 <a href="ident?i=req">req</a>-&gt;cookie_ts = tmp_opt.tstamp_ok;
<a name="L6185" href="source/net/ipv4/tcp_input.c#L6185">6185</a>                 if (!tmp_opt.tstamp_ok)
<a name="L6186" href="source/net/ipv4/tcp_input.c#L6186">6186</a>                         <a href="ident?i=inet_rsk">inet_rsk</a>(<a href="ident?i=req">req</a>)-&gt;ecn_ok = 0;
<a name="L6187" href="source/net/ipv4/tcp_input.c#L6187">6187</a>         }
<a name="L6188" href="source/net/ipv4/tcp_input.c#L6188">6188</a> 
<a name="L6189" href="source/net/ipv4/tcp_input.c#L6189">6189</a>         <a href="ident?i=tcp_rsk">tcp_rsk</a>(<a href="ident?i=req">req</a>)-&gt;snt_isn = isn;
<a name="L6190" href="source/net/ipv4/tcp_input.c#L6190">6190</a>         <a href="ident?i=tcp_openreq_init_rwin">tcp_openreq_init_rwin</a>(<a href="ident?i=req">req</a>, sk, <a href="ident?i=dst">dst</a>);
<a name="L6191" href="source/net/ipv4/tcp_input.c#L6191">6191</a>         fastopen = !want_cookie &amp;&amp;
<a name="L6192" href="source/net/ipv4/tcp_input.c#L6192">6192</a>                    <a href="ident?i=tcp_try_fastopen">tcp_try_fastopen</a>(sk, <a href="ident?i=skb">skb</a>, <a href="ident?i=req">req</a>, &amp;foc, <a href="ident?i=dst">dst</a>);
<a name="L6193" href="source/net/ipv4/tcp_input.c#L6193">6193</a>         <a href="ident?i=err">err</a> = af_ops-&gt;send_synack(sk, <a href="ident?i=dst">dst</a>, &amp;fl, <a href="ident?i=req">req</a>,
<a name="L6194" href="source/net/ipv4/tcp_input.c#L6194">6194</a>                                   <a href="ident?i=skb_get_queue_mapping">skb_get_queue_mapping</a>(<a href="ident?i=skb">skb</a>), &amp;foc);
<a name="L6195" href="source/net/ipv4/tcp_input.c#L6195">6195</a>         if (!fastopen) {
<a name="L6196" href="source/net/ipv4/tcp_input.c#L6196">6196</a>                 if (<a href="ident?i=err">err</a> || want_cookie)
<a name="L6197" href="source/net/ipv4/tcp_input.c#L6197">6197</a>                         goto drop_and_free;
<a name="L6198" href="source/net/ipv4/tcp_input.c#L6198">6198</a> 
<a name="L6199" href="source/net/ipv4/tcp_input.c#L6199">6199</a>                 <a href="ident?i=tcp_rsk">tcp_rsk</a>(<a href="ident?i=req">req</a>)-&gt;tfo_listener = <a href="ident?i=false">false</a>;
<a name="L6200" href="source/net/ipv4/tcp_input.c#L6200">6200</a>                 af_ops-&gt;queue_hash_add(sk, <a href="ident?i=req">req</a>, <a href="ident?i=TCP_TIMEOUT_INIT">TCP_TIMEOUT_INIT</a>);
<a name="L6201" href="source/net/ipv4/tcp_input.c#L6201">6201</a>         }
<a name="L6202" href="source/net/ipv4/tcp_input.c#L6202">6202</a> 
<a name="L6203" href="source/net/ipv4/tcp_input.c#L6203">6203</a>         return 0;
<a name="L6204" href="source/net/ipv4/tcp_input.c#L6204">6204</a> 
<a name="L6205" href="source/net/ipv4/tcp_input.c#L6205">6205</a> drop_and_release:
<a name="L6206" href="source/net/ipv4/tcp_input.c#L6206">6206</a>         <a href="ident?i=dst_release">dst_release</a>(<a href="ident?i=dst">dst</a>);
<a name="L6207" href="source/net/ipv4/tcp_input.c#L6207">6207</a> drop_and_free:
<a name="L6208" href="source/net/ipv4/tcp_input.c#L6208">6208</a>         <a href="ident?i=reqsk_free">reqsk_free</a>(<a href="ident?i=req">req</a>);
<a name="L6209" href="source/net/ipv4/tcp_input.c#L6209">6209</a> <a href="ident?i=drop">drop</a>:
<a name="L6210" href="source/net/ipv4/tcp_input.c#L6210">6210</a>         <a href="ident?i=NET_INC_STATS_BH">NET_INC_STATS_BH</a>(<a href="ident?i=sock_net">sock_net</a>(sk), LINUX_MIB_LISTENDROPS);
<a name="L6211" href="source/net/ipv4/tcp_input.c#L6211">6211</a>         return 0;
<a name="L6212" href="source/net/ipv4/tcp_input.c#L6212">6212</a> }
<a name="L6213" href="source/net/ipv4/tcp_input.c#L6213">6213</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=tcp_conn_request">tcp_conn_request</a>);
<a name="L6214" href="source/net/ipv4/tcp_input.c#L6214">6214</a> </pre></div><p>
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
