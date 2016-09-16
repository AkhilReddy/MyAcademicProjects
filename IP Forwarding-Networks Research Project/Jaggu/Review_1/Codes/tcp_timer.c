<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title>Linux/net/ipv4/tcp_timer.c - Linux Cross Reference - Free Electrons</title>
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
		 &nbsp;&bull;&nbsp;<b><i>source navigation</i></b> &nbsp;&bull;&nbsp;<a href="diff/net/ipv4/tcp_timer.c">diff markup</a> &nbsp;&bull;&nbsp;<a href="ident">identifier search</a> &nbsp;&bull;&nbsp;<a href="search">freetext search</a> &nbsp;&bull;&nbsp;
		</p>
	</div>
</div>

<div id="topbar">
  
  <p>Version: &nbsp;<a href="source/net/ipv4/tcp_timer.c?v=2.0.40">2.0.40</a>&nbsp;<a href="source/net/ipv4/tcp_timer.c?v=2.2.26">2.2.26</a>&nbsp;<a href="source/net/ipv4/tcp_timer.c?v=2.4.37">2.4.37</a>&nbsp;<a href="source/net/ipv4/tcp_timer.c?v=3.5">3.5</a>&nbsp;<a href="source/net/ipv4/tcp_timer.c?v=3.6">3.6</a>&nbsp;<a href="source/net/ipv4/tcp_timer.c?v=3.7">3.7</a>&nbsp;<a href="source/net/ipv4/tcp_timer.c?v=3.8">3.8</a>&nbsp;<a href="source/net/ipv4/tcp_timer.c?v=3.9">3.9</a>&nbsp;<a href="source/net/ipv4/tcp_timer.c?v=3.10">3.10</a>&nbsp;<a href="source/net/ipv4/tcp_timer.c?v=3.11">3.11</a>&nbsp;<a href="source/net/ipv4/tcp_timer.c?v=3.12">3.12</a>&nbsp;<a href="source/net/ipv4/tcp_timer.c?v=3.13">3.13</a>&nbsp;<a href="source/net/ipv4/tcp_timer.c?v=3.14">3.14</a>&nbsp;<a href="source/net/ipv4/tcp_timer.c?v=3.15">3.15</a>&nbsp;<a href="source/net/ipv4/tcp_timer.c?v=3.16">3.16</a>&nbsp;<a href="source/net/ipv4/tcp_timer.c?v=3.17">3.17</a>&nbsp;<a href="source/net/ipv4/tcp_timer.c?v=3.18">3.18</a>&nbsp;<a href="source/net/ipv4/tcp_timer.c?v=3.19">3.19</a>&nbsp;<a href="source/net/ipv4/tcp_timer.c?v=4.0">4.0</a>&nbsp;<b><i>4.1</i></b></p>
  
</div>

<h1><a href="source/">Linux</a>/<a href="source/net/">net</a>/<a href="source/net/ipv4/">ipv4</a>/<a href="source/net/ipv4/tcp_timer.c">tcp_timer.c</a></h1>
<div id="lxrcode"><pre>  <a name="L1" href="source/net/ipv4/tcp_timer.c#L1">1</a> <b><i>/*</i></b>
  <a name="L2" href="source/net/ipv4/tcp_timer.c#L2">2</a> <b><i> * INET         An implementation of the TCP/IP protocol suite for the LINUX</i></b>
  <a name="L3" href="source/net/ipv4/tcp_timer.c#L3">3</a> <b><i> *              operating system.  INET is implemented using the  BSD Socket</i></b>
  <a name="L4" href="source/net/ipv4/tcp_timer.c#L4">4</a> <b><i> *              interface as the means of communication with the user level.</i></b>
  <a name="L5" href="source/net/ipv4/tcp_timer.c#L5">5</a> <b><i> *</i></b>
  <a name="L6" href="source/net/ipv4/tcp_timer.c#L6">6</a> <b><i> *              Implementation of the Transmission Control Protocol(TCP).</i></b>
  <a name="L7" href="source/net/ipv4/tcp_timer.c#L7">7</a> <b><i> *</i></b>
  <a name="L8" href="source/net/ipv4/tcp_timer.c#L8">8</a> <b><i> * Authors:     Ross Biro</i></b>
  <a name="L9" href="source/net/ipv4/tcp_timer.c#L9">9</a> <b><i> *              Fred N. van Kempen, &lt;waltje@uWalt.NL.Mugnet.ORG&gt;</i></b>
 <a name="L10" href="source/net/ipv4/tcp_timer.c#L10">10</a> <b><i> *              Mark Evans, &lt;evansmp@uhura.aston.ac.uk&gt;</i></b>
 <a name="L11" href="source/net/ipv4/tcp_timer.c#L11">11</a> <b><i> *              Corey Minyard &lt;wf-rch!minyard@relay.EU.net&gt;</i></b>
 <a name="L12" href="source/net/ipv4/tcp_timer.c#L12">12</a> <b><i> *              Florian La Roche, &lt;flla@stud.uni-sb.de&gt;</i></b>
 <a name="L13" href="source/net/ipv4/tcp_timer.c#L13">13</a> <b><i> *              Charles Hedrick, &lt;hedrick@klinzhai.rutgers.edu&gt;</i></b>
 <a name="L14" href="source/net/ipv4/tcp_timer.c#L14">14</a> <b><i> *              Linus Torvalds, &lt;torvalds@cs.helsinki.fi&gt;</i></b>
 <a name="L15" href="source/net/ipv4/tcp_timer.c#L15">15</a> <b><i> *              Alan Cox, &lt;gw4pts@gw4pts.ampr.org&gt;</i></b>
 <a name="L16" href="source/net/ipv4/tcp_timer.c#L16">16</a> <b><i> *              Matthew Dillon, &lt;dillon@apollo.west.oic.com&gt;</i></b>
 <a name="L17" href="source/net/ipv4/tcp_timer.c#L17">17</a> <b><i> *              Arnt Gulbrandsen, &lt;agulbra@nvg.unit.no&gt;</i></b>
 <a name="L18" href="source/net/ipv4/tcp_timer.c#L18">18</a> <b><i> *              Jorge Cwik, &lt;jorge@laser.satlink.net&gt;</i></b>
 <a name="L19" href="source/net/ipv4/tcp_timer.c#L19">19</a> <b><i> */</i></b>
 <a name="L20" href="source/net/ipv4/tcp_timer.c#L20">20</a> 
 <a name="L21" href="source/net/ipv4/tcp_timer.c#L21">21</a> #include &lt;linux/module.h&gt;
 <a name="L22" href="source/net/ipv4/tcp_timer.c#L22">22</a> #include &lt;linux/gfp.h&gt;
 <a name="L23" href="source/net/ipv4/tcp_timer.c#L23">23</a> #include &lt;net/tcp.h&gt;
 <a name="L24" href="source/net/ipv4/tcp_timer.c#L24">24</a> 
 <a name="L25" href="source/net/ipv4/tcp_timer.c#L25">25</a> int <a href="ident?i=sysctl_tcp_syn_retries">sysctl_tcp_syn_retries</a> <a href="ident?i=__read_mostly">__read_mostly</a> = <a href="ident?i=TCP_SYN_RETRIES">TCP_SYN_RETRIES</a>;
 <a name="L26" href="source/net/ipv4/tcp_timer.c#L26">26</a> int <a href="ident?i=sysctl_tcp_synack_retries">sysctl_tcp_synack_retries</a> <a href="ident?i=__read_mostly">__read_mostly</a> = <a href="ident?i=TCP_SYNACK_RETRIES">TCP_SYNACK_RETRIES</a>;
 <a name="L27" href="source/net/ipv4/tcp_timer.c#L27">27</a> int <a href="ident?i=sysctl_tcp_keepalive_time">sysctl_tcp_keepalive_time</a> <a href="ident?i=__read_mostly">__read_mostly</a> = <a href="ident?i=TCP_KEEPALIVE_TIME">TCP_KEEPALIVE_TIME</a>;
 <a name="L28" href="source/net/ipv4/tcp_timer.c#L28">28</a> int <a href="ident?i=sysctl_tcp_keepalive_probes">sysctl_tcp_keepalive_probes</a> <a href="ident?i=__read_mostly">__read_mostly</a> = <a href="ident?i=TCP_KEEPALIVE_PROBES">TCP_KEEPALIVE_PROBES</a>;
 <a name="L29" href="source/net/ipv4/tcp_timer.c#L29">29</a> int <a href="ident?i=sysctl_tcp_keepalive_intvl">sysctl_tcp_keepalive_intvl</a> <a href="ident?i=__read_mostly">__read_mostly</a> = <a href="ident?i=TCP_KEEPALIVE_INTVL">TCP_KEEPALIVE_INTVL</a>;
 <a name="L30" href="source/net/ipv4/tcp_timer.c#L30">30</a> int <a href="ident?i=sysctl_tcp_retries1">sysctl_tcp_retries1</a> <a href="ident?i=__read_mostly">__read_mostly</a> = <a href="ident?i=TCP_RETR1">TCP_RETR1</a>;
 <a name="L31" href="source/net/ipv4/tcp_timer.c#L31">31</a> int <a href="ident?i=sysctl_tcp_retries2">sysctl_tcp_retries2</a> <a href="ident?i=__read_mostly">__read_mostly</a> = <a href="ident?i=TCP_RETR2">TCP_RETR2</a>;
 <a name="L32" href="source/net/ipv4/tcp_timer.c#L32">32</a> int <a href="ident?i=sysctl_tcp_orphan_retries">sysctl_tcp_orphan_retries</a> <a href="ident?i=__read_mostly">__read_mostly</a>;
 <a name="L33" href="source/net/ipv4/tcp_timer.c#L33">33</a> int <a href="ident?i=sysctl_tcp_thin_linear_timeouts">sysctl_tcp_thin_linear_timeouts</a> <a href="ident?i=__read_mostly">__read_mostly</a>;
 <a name="L34" href="source/net/ipv4/tcp_timer.c#L34">34</a> 
 <a name="L35" href="source/net/ipv4/tcp_timer.c#L35">35</a> static void <a href="ident?i=tcp_write_err">tcp_write_err</a>(struct <a href="ident?i=sock">sock</a> *sk)
 <a name="L36" href="source/net/ipv4/tcp_timer.c#L36">36</a> {
 <a name="L37" href="source/net/ipv4/tcp_timer.c#L37">37</a>         sk-&gt;sk_err = sk-&gt;sk_err_soft ? : <a href="ident?i=ETIMEDOUT">ETIMEDOUT</a>;
 <a name="L38" href="source/net/ipv4/tcp_timer.c#L38">38</a>         sk-&gt;sk_error_report(sk);
 <a name="L39" href="source/net/ipv4/tcp_timer.c#L39">39</a> 
 <a name="L40" href="source/net/ipv4/tcp_timer.c#L40">40</a>         <a href="ident?i=tcp_done">tcp_done</a>(sk);
 <a name="L41" href="source/net/ipv4/tcp_timer.c#L41">41</a>         <a href="ident?i=NET_INC_STATS_BH">NET_INC_STATS_BH</a>(<a href="ident?i=sock_net">sock_net</a>(sk), LINUX_MIB_TCPABORTONTIMEOUT);
 <a name="L42" href="source/net/ipv4/tcp_timer.c#L42">42</a> }
 <a name="L43" href="source/net/ipv4/tcp_timer.c#L43">43</a> 
 <a name="L44" href="source/net/ipv4/tcp_timer.c#L44">44</a> <b><i>/* Do not allow orphaned sockets to eat all our resources.</i></b>
 <a name="L45" href="source/net/ipv4/tcp_timer.c#L45">45</a> <b><i> * This is direct violation of TCP specs, but it is required</i></b>
 <a name="L46" href="source/net/ipv4/tcp_timer.c#L46">46</a> <b><i> * to prevent DoS attacks. It is called when a retransmission timeout</i></b>
 <a name="L47" href="source/net/ipv4/tcp_timer.c#L47">47</a> <b><i> * or zero probe timeout occurs on orphaned socket.</i></b>
 <a name="L48" href="source/net/ipv4/tcp_timer.c#L48">48</a> <b><i> *</i></b>
 <a name="L49" href="source/net/ipv4/tcp_timer.c#L49">49</a> <b><i> * Criteria is still not confirmed experimentally and may change.</i></b>
 <a name="L50" href="source/net/ipv4/tcp_timer.c#L50">50</a> <b><i> * We kill the socket, if:</i></b>
 <a name="L51" href="source/net/ipv4/tcp_timer.c#L51">51</a> <b><i> * 1. If number of orphaned sockets exceeds an administratively configured</i></b>
 <a name="L52" href="source/net/ipv4/tcp_timer.c#L52">52</a> <b><i> *    limit.</i></b>
 <a name="L53" href="source/net/ipv4/tcp_timer.c#L53">53</a> <b><i> * 2. If we have strong memory pressure.</i></b>
 <a name="L54" href="source/net/ipv4/tcp_timer.c#L54">54</a> <b><i> */</i></b>
 <a name="L55" href="source/net/ipv4/tcp_timer.c#L55">55</a> static int <a href="ident?i=tcp_out_of_resources">tcp_out_of_resources</a>(struct <a href="ident?i=sock">sock</a> *sk, <a href="ident?i=bool">bool</a> <a href="ident?i=do_reset">do_reset</a>)
 <a name="L56" href="source/net/ipv4/tcp_timer.c#L56">56</a> {
 <a name="L57" href="source/net/ipv4/tcp_timer.c#L57">57</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
 <a name="L58" href="source/net/ipv4/tcp_timer.c#L58">58</a>         int <a href="ident?i=shift">shift</a> = 0;
 <a name="L59" href="source/net/ipv4/tcp_timer.c#L59">59</a> 
 <a name="L60" href="source/net/ipv4/tcp_timer.c#L60">60</a>         <b><i>/* If peer does not open window for long time, or did not transmit</i></b>
 <a name="L61" href="source/net/ipv4/tcp_timer.c#L61">61</a> <b><i>         * anything for long time, penalize it. */</i></b>
 <a name="L62" href="source/net/ipv4/tcp_timer.c#L62">62</a>         if ((<a href="ident?i=s32">s32</a>)(<a href="ident?i=tcp_time_stamp">tcp_time_stamp</a> - <a href="ident?i=tp">tp</a>-&gt;lsndtime) &gt; 2*<a href="ident?i=TCP_RTO_MAX">TCP_RTO_MAX</a> || !<a href="ident?i=do_reset">do_reset</a>)
 <a name="L63" href="source/net/ipv4/tcp_timer.c#L63">63</a>                 <a href="ident?i=shift">shift</a>++;
 <a name="L64" href="source/net/ipv4/tcp_timer.c#L64">64</a> 
 <a name="L65" href="source/net/ipv4/tcp_timer.c#L65">65</a>         <b><i>/* If some dubious ICMP arrived, penalize even more. */</i></b>
 <a name="L66" href="source/net/ipv4/tcp_timer.c#L66">66</a>         if (sk-&gt;sk_err_soft)
 <a name="L67" href="source/net/ipv4/tcp_timer.c#L67">67</a>                 <a href="ident?i=shift">shift</a>++;
 <a name="L68" href="source/net/ipv4/tcp_timer.c#L68">68</a> 
 <a name="L69" href="source/net/ipv4/tcp_timer.c#L69">69</a>         if (<a href="ident?i=tcp_check_oom">tcp_check_oom</a>(sk, <a href="ident?i=shift">shift</a>)) {
 <a name="L70" href="source/net/ipv4/tcp_timer.c#L70">70</a>                 <b><i>/* Catch exceptional cases, when connection requires reset.</i></b>
 <a name="L71" href="source/net/ipv4/tcp_timer.c#L71">71</a> <b><i>                 *      1. Last segment was sent recently. */</i></b>
 <a name="L72" href="source/net/ipv4/tcp_timer.c#L72">72</a>                 if ((<a href="ident?i=s32">s32</a>)(<a href="ident?i=tcp_time_stamp">tcp_time_stamp</a> - <a href="ident?i=tp">tp</a>-&gt;lsndtime) &lt;= <a href="ident?i=TCP_TIMEWAIT_LEN">TCP_TIMEWAIT_LEN</a> ||
 <a name="L73" href="source/net/ipv4/tcp_timer.c#L73">73</a>                     <b><i>/*  2. Window is closed. */</i></b>
 <a name="L74" href="source/net/ipv4/tcp_timer.c#L74">74</a>                     (!<a href="ident?i=tp">tp</a>-&gt;snd_wnd &amp;&amp; !<a href="ident?i=tp">tp</a>-&gt;packets_out))
 <a name="L75" href="source/net/ipv4/tcp_timer.c#L75">75</a>                         <a href="ident?i=do_reset">do_reset</a> = <a href="ident?i=true">true</a>;
 <a name="L76" href="source/net/ipv4/tcp_timer.c#L76">76</a>                 if (<a href="ident?i=do_reset">do_reset</a>)
 <a name="L77" href="source/net/ipv4/tcp_timer.c#L77">77</a>                         <a href="ident?i=tcp_send_active_reset">tcp_send_active_reset</a>(sk, <a href="ident?i=GFP_ATOMIC">GFP_ATOMIC</a>);
 <a name="L78" href="source/net/ipv4/tcp_timer.c#L78">78</a>                 <a href="ident?i=tcp_done">tcp_done</a>(sk);
 <a name="L79" href="source/net/ipv4/tcp_timer.c#L79">79</a>                 <a href="ident?i=NET_INC_STATS_BH">NET_INC_STATS_BH</a>(<a href="ident?i=sock_net">sock_net</a>(sk), LINUX_MIB_TCPABORTONMEMORY);
 <a name="L80" href="source/net/ipv4/tcp_timer.c#L80">80</a>                 return 1;
 <a name="L81" href="source/net/ipv4/tcp_timer.c#L81">81</a>         }
 <a name="L82" href="source/net/ipv4/tcp_timer.c#L82">82</a>         return 0;
 <a name="L83" href="source/net/ipv4/tcp_timer.c#L83">83</a> }
 <a name="L84" href="source/net/ipv4/tcp_timer.c#L84">84</a> 
 <a name="L85" href="source/net/ipv4/tcp_timer.c#L85">85</a> <b><i>/* Calculate maximal number or retries on an orphaned socket. */</i></b>
 <a name="L86" href="source/net/ipv4/tcp_timer.c#L86">86</a> static int <a href="ident?i=tcp_orphan_retries">tcp_orphan_retries</a>(struct <a href="ident?i=sock">sock</a> *sk, int alive)
 <a name="L87" href="source/net/ipv4/tcp_timer.c#L87">87</a> {
 <a name="L88" href="source/net/ipv4/tcp_timer.c#L88">88</a>         int <a href="ident?i=retries">retries</a> = <a href="ident?i=sysctl_tcp_orphan_retries">sysctl_tcp_orphan_retries</a>; <b><i>/* May be zero. */</i></b>
 <a name="L89" href="source/net/ipv4/tcp_timer.c#L89">89</a> 
 <a name="L90" href="source/net/ipv4/tcp_timer.c#L90">90</a>         <b><i>/* We know from an ICMP that something is wrong. */</i></b>
 <a name="L91" href="source/net/ipv4/tcp_timer.c#L91">91</a>         if (sk-&gt;sk_err_soft &amp;&amp; !alive)
 <a name="L92" href="source/net/ipv4/tcp_timer.c#L92">92</a>                 <a href="ident?i=retries">retries</a> = 0;
 <a name="L93" href="source/net/ipv4/tcp_timer.c#L93">93</a> 
 <a name="L94" href="source/net/ipv4/tcp_timer.c#L94">94</a>         <b><i>/* However, if socket sent something recently, select some safe</i></b>
 <a name="L95" href="source/net/ipv4/tcp_timer.c#L95">95</a> <b><i>         * number of retries. 8 corresponds to &gt;100 seconds with minimal</i></b>
 <a name="L96" href="source/net/ipv4/tcp_timer.c#L96">96</a> <b><i>         * RTO of 200msec. */</i></b>
 <a name="L97" href="source/net/ipv4/tcp_timer.c#L97">97</a>         if (<a href="ident?i=retries">retries</a> == 0 &amp;&amp; alive)
 <a name="L98" href="source/net/ipv4/tcp_timer.c#L98">98</a>                 <a href="ident?i=retries">retries</a> = 8;
 <a name="L99" href="source/net/ipv4/tcp_timer.c#L99">99</a>         return <a href="ident?i=retries">retries</a>;
<a name="L100" href="source/net/ipv4/tcp_timer.c#L100">100</a> }
<a name="L101" href="source/net/ipv4/tcp_timer.c#L101">101</a> 
<a name="L102" href="source/net/ipv4/tcp_timer.c#L102">102</a> static void <a href="ident?i=tcp_mtu_probing">tcp_mtu_probing</a>(struct <a href="ident?i=inet_connection_sock">inet_connection_sock</a> *icsk, struct <a href="ident?i=sock">sock</a> *sk)
<a name="L103" href="source/net/ipv4/tcp_timer.c#L103">103</a> {
<a name="L104" href="source/net/ipv4/tcp_timer.c#L104">104</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=sock_net">sock_net</a>(sk);
<a name="L105" href="source/net/ipv4/tcp_timer.c#L105">105</a> 
<a name="L106" href="source/net/ipv4/tcp_timer.c#L106">106</a>         <b><i>/* Black hole detection */</i></b>
<a name="L107" href="source/net/ipv4/tcp_timer.c#L107">107</a>         if (<a href="ident?i=net">net</a>-&gt;ipv4.sysctl_tcp_mtu_probing) {
<a name="L108" href="source/net/ipv4/tcp_timer.c#L108">108</a>                 if (!icsk-&gt;icsk_mtup.<a href="ident?i=enabled">enabled</a>) {
<a name="L109" href="source/net/ipv4/tcp_timer.c#L109">109</a>                         icsk-&gt;icsk_mtup.<a href="ident?i=enabled">enabled</a> = 1;
<a name="L110" href="source/net/ipv4/tcp_timer.c#L110">110</a>                         icsk-&gt;icsk_mtup.probe_timestamp = <a href="ident?i=tcp_time_stamp">tcp_time_stamp</a>;
<a name="L111" href="source/net/ipv4/tcp_timer.c#L111">111</a>                         <a href="ident?i=tcp_sync_mss">tcp_sync_mss</a>(sk, icsk-&gt;icsk_pmtu_cookie);
<a name="L112" href="source/net/ipv4/tcp_timer.c#L112">112</a>                 } else {
<a name="L113" href="source/net/ipv4/tcp_timer.c#L113">113</a>                         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=sock_net">sock_net</a>(sk);
<a name="L114" href="source/net/ipv4/tcp_timer.c#L114">114</a>                         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L115" href="source/net/ipv4/tcp_timer.c#L115">115</a>                         int mss;
<a name="L116" href="source/net/ipv4/tcp_timer.c#L116">116</a> 
<a name="L117" href="source/net/ipv4/tcp_timer.c#L117">117</a>                         mss = <a href="ident?i=tcp_mtu_to_mss">tcp_mtu_to_mss</a>(sk, icsk-&gt;icsk_mtup.search_low) &gt;&gt; 1;
<a name="L118" href="source/net/ipv4/tcp_timer.c#L118">118</a>                         mss = <a href="ident?i=min">min</a>(<a href="ident?i=net">net</a>-&gt;ipv4.sysctl_tcp_base_mss, mss);
<a name="L119" href="source/net/ipv4/tcp_timer.c#L119">119</a>                         mss = <a href="ident?i=max">max</a>(mss, 68 - <a href="ident?i=tp">tp</a>-&gt;tcp_header_len);
<a name="L120" href="source/net/ipv4/tcp_timer.c#L120">120</a>                         icsk-&gt;icsk_mtup.search_low = <a href="ident?i=tcp_mss_to_mtu">tcp_mss_to_mtu</a>(sk, mss);
<a name="L121" href="source/net/ipv4/tcp_timer.c#L121">121</a>                         <a href="ident?i=tcp_sync_mss">tcp_sync_mss</a>(sk, icsk-&gt;icsk_pmtu_cookie);
<a name="L122" href="source/net/ipv4/tcp_timer.c#L122">122</a>                 }
<a name="L123" href="source/net/ipv4/tcp_timer.c#L123">123</a>         }
<a name="L124" href="source/net/ipv4/tcp_timer.c#L124">124</a> }
<a name="L125" href="source/net/ipv4/tcp_timer.c#L125">125</a> 
<a name="L126" href="source/net/ipv4/tcp_timer.c#L126">126</a> <b><i>/* This function calculates a "timeout" which is equivalent to the timeout of a</i></b>
<a name="L127" href="source/net/ipv4/tcp_timer.c#L127">127</a> <b><i> * TCP connection after "boundary" unsuccessful, exponentially backed-off</i></b>
<a name="L128" href="source/net/ipv4/tcp_timer.c#L128">128</a> <b><i> * retransmissions with an initial RTO of TCP_RTO_MIN or TCP_TIMEOUT_INIT if</i></b>
<a name="L129" href="source/net/ipv4/tcp_timer.c#L129">129</a> <b><i> * syn_set flag is set.</i></b>
<a name="L130" href="source/net/ipv4/tcp_timer.c#L130">130</a> <b><i> */</i></b>
<a name="L131" href="source/net/ipv4/tcp_timer.c#L131">131</a> static <a href="ident?i=bool">bool</a> <a href="ident?i=retransmits_timed_out">retransmits_timed_out</a>(struct <a href="ident?i=sock">sock</a> *sk,
<a name="L132" href="source/net/ipv4/tcp_timer.c#L132">132</a>                                   unsigned int <a href="ident?i=boundary">boundary</a>,
<a name="L133" href="source/net/ipv4/tcp_timer.c#L133">133</a>                                   unsigned int <a href="ident?i=timeout">timeout</a>,
<a name="L134" href="source/net/ipv4/tcp_timer.c#L134">134</a>                                   <a href="ident?i=bool">bool</a> syn_set)
<a name="L135" href="source/net/ipv4/tcp_timer.c#L135">135</a> {
<a name="L136" href="source/net/ipv4/tcp_timer.c#L136">136</a>         unsigned int linear_backoff_thresh, start_ts;
<a name="L137" href="source/net/ipv4/tcp_timer.c#L137">137</a>         unsigned int rto_base = syn_set ? <a href="ident?i=TCP_TIMEOUT_INIT">TCP_TIMEOUT_INIT</a> : <a href="ident?i=TCP_RTO_MIN">TCP_RTO_MIN</a>;
<a name="L138" href="source/net/ipv4/tcp_timer.c#L138">138</a> 
<a name="L139" href="source/net/ipv4/tcp_timer.c#L139">139</a>         if (!<a href="ident?i=inet_csk">inet_csk</a>(sk)-&gt;icsk_retransmits)
<a name="L140" href="source/net/ipv4/tcp_timer.c#L140">140</a>                 return <a href="ident?i=false">false</a>;
<a name="L141" href="source/net/ipv4/tcp_timer.c#L141">141</a> 
<a name="L142" href="source/net/ipv4/tcp_timer.c#L142">142</a>         start_ts = <a href="ident?i=tcp_sk">tcp_sk</a>(sk)-&gt;retrans_stamp;
<a name="L143" href="source/net/ipv4/tcp_timer.c#L143">143</a>         if (<a href="ident?i=unlikely">unlikely</a>(!start_ts))
<a name="L144" href="source/net/ipv4/tcp_timer.c#L144">144</a>                 start_ts = <a href="ident?i=tcp_skb_timestamp">tcp_skb_timestamp</a>(<a href="ident?i=tcp_write_queue_head">tcp_write_queue_head</a>(sk));
<a name="L145" href="source/net/ipv4/tcp_timer.c#L145">145</a> 
<a name="L146" href="source/net/ipv4/tcp_timer.c#L146">146</a>         if (<a href="ident?i=likely">likely</a>(<a href="ident?i=timeout">timeout</a> == 0)) {
<a name="L147" href="source/net/ipv4/tcp_timer.c#L147">147</a>                 linear_backoff_thresh = <a href="ident?i=ilog2">ilog2</a>(<a href="ident?i=TCP_RTO_MAX">TCP_RTO_MAX</a>/rto_base);
<a name="L148" href="source/net/ipv4/tcp_timer.c#L148">148</a> 
<a name="L149" href="source/net/ipv4/tcp_timer.c#L149">149</a>                 if (<a href="ident?i=boundary">boundary</a> &lt;= linear_backoff_thresh)
<a name="L150" href="source/net/ipv4/tcp_timer.c#L150">150</a>                         <a href="ident?i=timeout">timeout</a> = ((2 &lt;&lt; <a href="ident?i=boundary">boundary</a>) - 1) * rto_base;
<a name="L151" href="source/net/ipv4/tcp_timer.c#L151">151</a>                 else
<a name="L152" href="source/net/ipv4/tcp_timer.c#L152">152</a>                         <a href="ident?i=timeout">timeout</a> = ((2 &lt;&lt; linear_backoff_thresh) - 1) * rto_base +
<a name="L153" href="source/net/ipv4/tcp_timer.c#L153">153</a>                                 (<a href="ident?i=boundary">boundary</a> - linear_backoff_thresh) * <a href="ident?i=TCP_RTO_MAX">TCP_RTO_MAX</a>;
<a name="L154" href="source/net/ipv4/tcp_timer.c#L154">154</a>         }
<a name="L155" href="source/net/ipv4/tcp_timer.c#L155">155</a>         return (<a href="ident?i=tcp_time_stamp">tcp_time_stamp</a> - start_ts) &gt;= <a href="ident?i=timeout">timeout</a>;
<a name="L156" href="source/net/ipv4/tcp_timer.c#L156">156</a> }
<a name="L157" href="source/net/ipv4/tcp_timer.c#L157">157</a> 
<a name="L158" href="source/net/ipv4/tcp_timer.c#L158">158</a> <b><i>/* A write timeout has occurred. Process the after effects. */</i></b>
<a name="L159" href="source/net/ipv4/tcp_timer.c#L159">159</a> static int <a href="ident?i=tcp_write_timeout">tcp_write_timeout</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L160" href="source/net/ipv4/tcp_timer.c#L160">160</a> {
<a name="L161" href="source/net/ipv4/tcp_timer.c#L161">161</a>         struct <a href="ident?i=inet_connection_sock">inet_connection_sock</a> *icsk = <a href="ident?i=inet_csk">inet_csk</a>(sk);
<a name="L162" href="source/net/ipv4/tcp_timer.c#L162">162</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L163" href="source/net/ipv4/tcp_timer.c#L163">163</a>         int retry_until;
<a name="L164" href="source/net/ipv4/tcp_timer.c#L164">164</a>         <a href="ident?i=bool">bool</a> <a href="ident?i=do_reset">do_reset</a>, syn_set = <a href="ident?i=false">false</a>;
<a name="L165" href="source/net/ipv4/tcp_timer.c#L165">165</a> 
<a name="L166" href="source/net/ipv4/tcp_timer.c#L166">166</a>         if ((1 &lt;&lt; sk-&gt;<a href="ident?i=sk_state">sk_state</a>) &amp; (TCPF_SYN_SENT | TCPF_SYN_RECV)) {
<a name="L167" href="source/net/ipv4/tcp_timer.c#L167">167</a>                 if (icsk-&gt;icsk_retransmits) {
<a name="L168" href="source/net/ipv4/tcp_timer.c#L168">168</a>                         <a href="ident?i=dst_negative_advice">dst_negative_advice</a>(sk);
<a name="L169" href="source/net/ipv4/tcp_timer.c#L169">169</a>                         if (<a href="ident?i=tp">tp</a>-&gt;syn_fastopen || <a href="ident?i=tp">tp</a>-&gt;syn_data)
<a name="L170" href="source/net/ipv4/tcp_timer.c#L170">170</a>                                 <a href="ident?i=tcp_fastopen_cache_set">tcp_fastopen_cache_set</a>(sk, 0, <a href="ident?i=NULL">NULL</a>, <a href="ident?i=true">true</a>, 0);
<a name="L171" href="source/net/ipv4/tcp_timer.c#L171">171</a>                         if (<a href="ident?i=tp">tp</a>-&gt;syn_data)
<a name="L172" href="source/net/ipv4/tcp_timer.c#L172">172</a>                                 <a href="ident?i=NET_INC_STATS_BH">NET_INC_STATS_BH</a>(<a href="ident?i=sock_net">sock_net</a>(sk),
<a name="L173" href="source/net/ipv4/tcp_timer.c#L173">173</a>                                                  LINUX_MIB_TCPFASTOPENACTIVEFAIL);
<a name="L174" href="source/net/ipv4/tcp_timer.c#L174">174</a>                 }
<a name="L175" href="source/net/ipv4/tcp_timer.c#L175">175</a>                 retry_until = icsk-&gt;icsk_syn_retries ? : <a href="ident?i=sysctl_tcp_syn_retries">sysctl_tcp_syn_retries</a>;
<a name="L176" href="source/net/ipv4/tcp_timer.c#L176">176</a>                 syn_set = <a href="ident?i=true">true</a>;
<a name="L177" href="source/net/ipv4/tcp_timer.c#L177">177</a>         } else {
<a name="L178" href="source/net/ipv4/tcp_timer.c#L178">178</a>                 if (<a href="ident?i=retransmits_timed_out">retransmits_timed_out</a>(sk, <a href="ident?i=sysctl_tcp_retries1">sysctl_tcp_retries1</a>, 0, 0)) {
<a name="L179" href="source/net/ipv4/tcp_timer.c#L179">179</a>                         <b><i>/* Black hole detection */</i></b>
<a name="L180" href="source/net/ipv4/tcp_timer.c#L180">180</a>                         <a href="ident?i=tcp_mtu_probing">tcp_mtu_probing</a>(icsk, sk);
<a name="L181" href="source/net/ipv4/tcp_timer.c#L181">181</a> 
<a name="L182" href="source/net/ipv4/tcp_timer.c#L182">182</a>                         <a href="ident?i=dst_negative_advice">dst_negative_advice</a>(sk);
<a name="L183" href="source/net/ipv4/tcp_timer.c#L183">183</a>                 }
<a name="L184" href="source/net/ipv4/tcp_timer.c#L184">184</a> 
<a name="L185" href="source/net/ipv4/tcp_timer.c#L185">185</a>                 retry_until = <a href="ident?i=sysctl_tcp_retries2">sysctl_tcp_retries2</a>;
<a name="L186" href="source/net/ipv4/tcp_timer.c#L186">186</a>                 if (<a href="ident?i=sock_flag">sock_flag</a>(sk, SOCK_DEAD)) {
<a name="L187" href="source/net/ipv4/tcp_timer.c#L187">187</a>                         const int alive = icsk-&gt;icsk_rto &lt; <a href="ident?i=TCP_RTO_MAX">TCP_RTO_MAX</a>;
<a name="L188" href="source/net/ipv4/tcp_timer.c#L188">188</a> 
<a name="L189" href="source/net/ipv4/tcp_timer.c#L189">189</a>                         retry_until = <a href="ident?i=tcp_orphan_retries">tcp_orphan_retries</a>(sk, alive);
<a name="L190" href="source/net/ipv4/tcp_timer.c#L190">190</a>                         <a href="ident?i=do_reset">do_reset</a> = alive ||
<a name="L191" href="source/net/ipv4/tcp_timer.c#L191">191</a>                                 !<a href="ident?i=retransmits_timed_out">retransmits_timed_out</a>(sk, retry_until, 0, 0);
<a name="L192" href="source/net/ipv4/tcp_timer.c#L192">192</a> 
<a name="L193" href="source/net/ipv4/tcp_timer.c#L193">193</a>                         if (<a href="ident?i=tcp_out_of_resources">tcp_out_of_resources</a>(sk, <a href="ident?i=do_reset">do_reset</a>))
<a name="L194" href="source/net/ipv4/tcp_timer.c#L194">194</a>                                 return 1;
<a name="L195" href="source/net/ipv4/tcp_timer.c#L195">195</a>                 }
<a name="L196" href="source/net/ipv4/tcp_timer.c#L196">196</a>         }
<a name="L197" href="source/net/ipv4/tcp_timer.c#L197">197</a> 
<a name="L198" href="source/net/ipv4/tcp_timer.c#L198">198</a>         if (<a href="ident?i=retransmits_timed_out">retransmits_timed_out</a>(sk, retry_until,
<a name="L199" href="source/net/ipv4/tcp_timer.c#L199">199</a>                                   syn_set ? 0 : icsk-&gt;icsk_user_timeout, syn_set)) {
<a name="L200" href="source/net/ipv4/tcp_timer.c#L200">200</a>                 <b><i>/* Has it gone just too far? */</i></b>
<a name="L201" href="source/net/ipv4/tcp_timer.c#L201">201</a>                 <a href="ident?i=tcp_write_err">tcp_write_err</a>(sk);
<a name="L202" href="source/net/ipv4/tcp_timer.c#L202">202</a>                 return 1;
<a name="L203" href="source/net/ipv4/tcp_timer.c#L203">203</a>         }
<a name="L204" href="source/net/ipv4/tcp_timer.c#L204">204</a>         return 0;
<a name="L205" href="source/net/ipv4/tcp_timer.c#L205">205</a> }
<a name="L206" href="source/net/ipv4/tcp_timer.c#L206">206</a> 
<a name="L207" href="source/net/ipv4/tcp_timer.c#L207">207</a> void <a href="ident?i=tcp_delack_timer_handler">tcp_delack_timer_handler</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L208" href="source/net/ipv4/tcp_timer.c#L208">208</a> {
<a name="L209" href="source/net/ipv4/tcp_timer.c#L209">209</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L210" href="source/net/ipv4/tcp_timer.c#L210">210</a>         struct <a href="ident?i=inet_connection_sock">inet_connection_sock</a> *icsk = <a href="ident?i=inet_csk">inet_csk</a>(sk);
<a name="L211" href="source/net/ipv4/tcp_timer.c#L211">211</a> 
<a name="L212" href="source/net/ipv4/tcp_timer.c#L212">212</a>         <a href="ident?i=sk_mem_reclaim_partial">sk_mem_reclaim_partial</a>(sk);
<a name="L213" href="source/net/ipv4/tcp_timer.c#L213">213</a> 
<a name="L214" href="source/net/ipv4/tcp_timer.c#L214">214</a>         if (sk-&gt;<a href="ident?i=sk_state">sk_state</a> == TCP_CLOSE || !(icsk-&gt;icsk_ack.<a href="ident?i=pending">pending</a> &amp; ICSK_ACK_TIMER))
<a name="L215" href="source/net/ipv4/tcp_timer.c#L215">215</a>                 goto <a href="ident?i=out">out</a>;
<a name="L216" href="source/net/ipv4/tcp_timer.c#L216">216</a> 
<a name="L217" href="source/net/ipv4/tcp_timer.c#L217">217</a>         if (<a href="ident?i=time_after">time_after</a>(icsk-&gt;icsk_ack.<a href="ident?i=timeout">timeout</a>, <a href="ident?i=jiffies">jiffies</a>)) {
<a name="L218" href="source/net/ipv4/tcp_timer.c#L218">218</a>                 <a href="ident?i=sk_reset_timer">sk_reset_timer</a>(sk, &amp;icsk-&gt;icsk_delack_timer, icsk-&gt;icsk_ack.<a href="ident?i=timeout">timeout</a>);
<a name="L219" href="source/net/ipv4/tcp_timer.c#L219">219</a>                 goto <a href="ident?i=out">out</a>;
<a name="L220" href="source/net/ipv4/tcp_timer.c#L220">220</a>         }
<a name="L221" href="source/net/ipv4/tcp_timer.c#L221">221</a>         icsk-&gt;icsk_ack.<a href="ident?i=pending">pending</a> &amp;= ~ICSK_ACK_TIMER;
<a name="L222" href="source/net/ipv4/tcp_timer.c#L222">222</a> 
<a name="L223" href="source/net/ipv4/tcp_timer.c#L223">223</a>         if (!<a href="ident?i=skb_queue_empty">skb_queue_empty</a>(&amp;<a href="ident?i=tp">tp</a>-&gt;ucopy.prequeue)) {
<a name="L224" href="source/net/ipv4/tcp_timer.c#L224">224</a>                 struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>;
<a name="L225" href="source/net/ipv4/tcp_timer.c#L225">225</a> 
<a name="L226" href="source/net/ipv4/tcp_timer.c#L226">226</a>                 <a href="ident?i=NET_INC_STATS_BH">NET_INC_STATS_BH</a>(<a href="ident?i=sock_net">sock_net</a>(sk), LINUX_MIB_TCPSCHEDULERFAILED);
<a name="L227" href="source/net/ipv4/tcp_timer.c#L227">227</a> 
<a name="L228" href="source/net/ipv4/tcp_timer.c#L228">228</a>                 while ((<a href="ident?i=skb">skb</a> = <a href="ident?i=__skb_dequeue">__skb_dequeue</a>(&amp;<a href="ident?i=tp">tp</a>-&gt;ucopy.prequeue)) != <a href="ident?i=NULL">NULL</a>)
<a name="L229" href="source/net/ipv4/tcp_timer.c#L229">229</a>                         <a href="ident?i=sk_backlog_rcv">sk_backlog_rcv</a>(sk, <a href="ident?i=skb">skb</a>);
<a name="L230" href="source/net/ipv4/tcp_timer.c#L230">230</a> 
<a name="L231" href="source/net/ipv4/tcp_timer.c#L231">231</a>                 <a href="ident?i=tp">tp</a>-&gt;ucopy.<a href="ident?i=memory">memory</a> = 0;
<a name="L232" href="source/net/ipv4/tcp_timer.c#L232">232</a>         }
<a name="L233" href="source/net/ipv4/tcp_timer.c#L233">233</a> 
<a name="L234" href="source/net/ipv4/tcp_timer.c#L234">234</a>         if (<a href="ident?i=inet_csk_ack_scheduled">inet_csk_ack_scheduled</a>(sk)) {
<a name="L235" href="source/net/ipv4/tcp_timer.c#L235">235</a>                 if (!icsk-&gt;icsk_ack.pingpong) {
<a name="L236" href="source/net/ipv4/tcp_timer.c#L236">236</a>                         <b><i>/* Delayed ACK missed: inflate ATO. */</i></b>
<a name="L237" href="source/net/ipv4/tcp_timer.c#L237">237</a>                         icsk-&gt;icsk_ack.ato = <a href="ident?i=min">min</a>(icsk-&gt;icsk_ack.ato &lt;&lt; 1, icsk-&gt;icsk_rto);
<a name="L238" href="source/net/ipv4/tcp_timer.c#L238">238</a>                 } else {
<a name="L239" href="source/net/ipv4/tcp_timer.c#L239">239</a>                         <b><i>/* Delayed ACK missed: leave pingpong mode and</i></b>
<a name="L240" href="source/net/ipv4/tcp_timer.c#L240">240</a> <b><i>                         * deflate ATO.</i></b>
<a name="L241" href="source/net/ipv4/tcp_timer.c#L241">241</a> <b><i>                         */</i></b>
<a name="L242" href="source/net/ipv4/tcp_timer.c#L242">242</a>                         icsk-&gt;icsk_ack.pingpong = 0;
<a name="L243" href="source/net/ipv4/tcp_timer.c#L243">243</a>                         icsk-&gt;icsk_ack.ato      = <a href="ident?i=TCP_ATO_MIN">TCP_ATO_MIN</a>;
<a name="L244" href="source/net/ipv4/tcp_timer.c#L244">244</a>                 }
<a name="L245" href="source/net/ipv4/tcp_timer.c#L245">245</a>                 <a href="ident?i=tcp_send_ack">tcp_send_ack</a>(sk);
<a name="L246" href="source/net/ipv4/tcp_timer.c#L246">246</a>                 <a href="ident?i=NET_INC_STATS_BH">NET_INC_STATS_BH</a>(<a href="ident?i=sock_net">sock_net</a>(sk), LINUX_MIB_DELAYEDACKS);
<a name="L247" href="source/net/ipv4/tcp_timer.c#L247">247</a>         }
<a name="L248" href="source/net/ipv4/tcp_timer.c#L248">248</a> 
<a name="L249" href="source/net/ipv4/tcp_timer.c#L249">249</a> <a href="ident?i=out">out</a>:
<a name="L250" href="source/net/ipv4/tcp_timer.c#L250">250</a>         if (<a href="ident?i=sk_under_memory_pressure">sk_under_memory_pressure</a>(sk))
<a name="L251" href="source/net/ipv4/tcp_timer.c#L251">251</a>                 <a href="ident?i=sk_mem_reclaim">sk_mem_reclaim</a>(sk);
<a name="L252" href="source/net/ipv4/tcp_timer.c#L252">252</a> }
<a name="L253" href="source/net/ipv4/tcp_timer.c#L253">253</a> 
<a name="L254" href="source/net/ipv4/tcp_timer.c#L254">254</a> static void <a href="ident?i=tcp_delack_timer">tcp_delack_timer</a>(unsigned long <a href="ident?i=data">data</a>)
<a name="L255" href="source/net/ipv4/tcp_timer.c#L255">255</a> {
<a name="L256" href="source/net/ipv4/tcp_timer.c#L256">256</a>         struct <a href="ident?i=sock">sock</a> *sk = (struct <a href="ident?i=sock">sock</a> *)<a href="ident?i=data">data</a>;
<a name="L257" href="source/net/ipv4/tcp_timer.c#L257">257</a> 
<a name="L258" href="source/net/ipv4/tcp_timer.c#L258">258</a>         <a href="ident?i=bh_lock_sock">bh_lock_sock</a>(sk);
<a name="L259" href="source/net/ipv4/tcp_timer.c#L259">259</a>         if (!<a href="ident?i=sock_owned_by_user">sock_owned_by_user</a>(sk)) {
<a name="L260" href="source/net/ipv4/tcp_timer.c#L260">260</a>                 <a href="ident?i=tcp_delack_timer_handler">tcp_delack_timer_handler</a>(sk);
<a name="L261" href="source/net/ipv4/tcp_timer.c#L261">261</a>         } else {
<a name="L262" href="source/net/ipv4/tcp_timer.c#L262">262</a>                 <a href="ident?i=inet_csk">inet_csk</a>(sk)-&gt;icsk_ack.blocked = 1;
<a name="L263" href="source/net/ipv4/tcp_timer.c#L263">263</a>                 <a href="ident?i=NET_INC_STATS_BH">NET_INC_STATS_BH</a>(<a href="ident?i=sock_net">sock_net</a>(sk), LINUX_MIB_DELAYEDACKLOCKED);
<a name="L264" href="source/net/ipv4/tcp_timer.c#L264">264</a>                 <b><i>/* deleguate our work to tcp_release_cb() */</i></b>
<a name="L265" href="source/net/ipv4/tcp_timer.c#L265">265</a>                 if (!<a href="ident?i=test_and_set_bit">test_and_set_bit</a>(TCP_DELACK_TIMER_DEFERRED, &amp;<a href="ident?i=tcp_sk">tcp_sk</a>(sk)-&gt;<a href="ident?i=tsq_flags">tsq_flags</a>))
<a name="L266" href="source/net/ipv4/tcp_timer.c#L266">266</a>                         <a href="ident?i=sock_hold">sock_hold</a>(sk);
<a name="L267" href="source/net/ipv4/tcp_timer.c#L267">267</a>         }
<a name="L268" href="source/net/ipv4/tcp_timer.c#L268">268</a>         <a href="ident?i=bh_unlock_sock">bh_unlock_sock</a>(sk);
<a name="L269" href="source/net/ipv4/tcp_timer.c#L269">269</a>         <a href="ident?i=sock_put">sock_put</a>(sk);
<a name="L270" href="source/net/ipv4/tcp_timer.c#L270">270</a> }
<a name="L271" href="source/net/ipv4/tcp_timer.c#L271">271</a> 
<a name="L272" href="source/net/ipv4/tcp_timer.c#L272">272</a> static void <a href="ident?i=tcp_probe_timer">tcp_probe_timer</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L273" href="source/net/ipv4/tcp_timer.c#L273">273</a> {
<a name="L274" href="source/net/ipv4/tcp_timer.c#L274">274</a>         struct <a href="ident?i=inet_connection_sock">inet_connection_sock</a> *icsk = <a href="ident?i=inet_csk">inet_csk</a>(sk);
<a name="L275" href="source/net/ipv4/tcp_timer.c#L275">275</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L276" href="source/net/ipv4/tcp_timer.c#L276">276</a>         int max_probes;
<a name="L277" href="source/net/ipv4/tcp_timer.c#L277">277</a>         <a href="ident?i=u32">u32</a> start_ts;
<a name="L278" href="source/net/ipv4/tcp_timer.c#L278">278</a> 
<a name="L279" href="source/net/ipv4/tcp_timer.c#L279">279</a>         if (<a href="ident?i=tp">tp</a>-&gt;packets_out || !<a href="ident?i=tcp_send_head">tcp_send_head</a>(sk)) {
<a name="L280" href="source/net/ipv4/tcp_timer.c#L280">280</a>                 icsk-&gt;icsk_probes_out = 0;
<a name="L281" href="source/net/ipv4/tcp_timer.c#L281">281</a>                 return;
<a name="L282" href="source/net/ipv4/tcp_timer.c#L282">282</a>         }
<a name="L283" href="source/net/ipv4/tcp_timer.c#L283">283</a> 
<a name="L284" href="source/net/ipv4/tcp_timer.c#L284">284</a>         <b><i>/* RFC 1122 4.2.2.17 requires the sender to stay open indefinitely as</i></b>
<a name="L285" href="source/net/ipv4/tcp_timer.c#L285">285</a> <b><i>         * long as the receiver continues to respond probes. We support this by</i></b>
<a name="L286" href="source/net/ipv4/tcp_timer.c#L286">286</a> <b><i>         * default and reset icsk_probes_out with incoming ACKs. But if the</i></b>
<a name="L287" href="source/net/ipv4/tcp_timer.c#L287">287</a> <b><i>         * socket is orphaned or the user specifies TCP_USER_TIMEOUT, we</i></b>
<a name="L288" href="source/net/ipv4/tcp_timer.c#L288">288</a> <b><i>         * kill the socket when the retry count and the time exceeds the</i></b>
<a name="L289" href="source/net/ipv4/tcp_timer.c#L289">289</a> <b><i>         * corresponding system limit. We also implement similar policy when</i></b>
<a name="L290" href="source/net/ipv4/tcp_timer.c#L290">290</a> <b><i>         * we use RTO to probe window in tcp_retransmit_timer().</i></b>
<a name="L291" href="source/net/ipv4/tcp_timer.c#L291">291</a> <b><i>         */</i></b>
<a name="L292" href="source/net/ipv4/tcp_timer.c#L292">292</a>         start_ts = <a href="ident?i=tcp_skb_timestamp">tcp_skb_timestamp</a>(<a href="ident?i=tcp_send_head">tcp_send_head</a>(sk));
<a name="L293" href="source/net/ipv4/tcp_timer.c#L293">293</a>         if (!start_ts)
<a name="L294" href="source/net/ipv4/tcp_timer.c#L294">294</a>                 <a href="ident?i=skb_mstamp_get">skb_mstamp_get</a>(&amp;<a href="ident?i=tcp_send_head">tcp_send_head</a>(sk)-&gt;<a href="ident?i=skb_mstamp">skb_mstamp</a>);
<a name="L295" href="source/net/ipv4/tcp_timer.c#L295">295</a>         else if (icsk-&gt;icsk_user_timeout &amp;&amp;
<a name="L296" href="source/net/ipv4/tcp_timer.c#L296">296</a>                  (<a href="ident?i=s32">s32</a>)(<a href="ident?i=tcp_time_stamp">tcp_time_stamp</a> - start_ts) &gt; icsk-&gt;icsk_user_timeout)
<a name="L297" href="source/net/ipv4/tcp_timer.c#L297">297</a>                 goto <a href="ident?i=abort">abort</a>;
<a name="L298" href="source/net/ipv4/tcp_timer.c#L298">298</a> 
<a name="L299" href="source/net/ipv4/tcp_timer.c#L299">299</a>         max_probes = <a href="ident?i=sysctl_tcp_retries2">sysctl_tcp_retries2</a>;
<a name="L300" href="source/net/ipv4/tcp_timer.c#L300">300</a>         if (<a href="ident?i=sock_flag">sock_flag</a>(sk, SOCK_DEAD)) {
<a name="L301" href="source/net/ipv4/tcp_timer.c#L301">301</a>                 const int alive = <a href="ident?i=inet_csk_rto_backoff">inet_csk_rto_backoff</a>(icsk, <a href="ident?i=TCP_RTO_MAX">TCP_RTO_MAX</a>) &lt; <a href="ident?i=TCP_RTO_MAX">TCP_RTO_MAX</a>;
<a name="L302" href="source/net/ipv4/tcp_timer.c#L302">302</a> 
<a name="L303" href="source/net/ipv4/tcp_timer.c#L303">303</a>                 max_probes = <a href="ident?i=tcp_orphan_retries">tcp_orphan_retries</a>(sk, alive);
<a name="L304" href="source/net/ipv4/tcp_timer.c#L304">304</a>                 if (!alive &amp;&amp; icsk-&gt;icsk_backoff &gt;= max_probes)
<a name="L305" href="source/net/ipv4/tcp_timer.c#L305">305</a>                         goto <a href="ident?i=abort">abort</a>;
<a name="L306" href="source/net/ipv4/tcp_timer.c#L306">306</a>                 if (<a href="ident?i=tcp_out_of_resources">tcp_out_of_resources</a>(sk, <a href="ident?i=true">true</a>))
<a name="L307" href="source/net/ipv4/tcp_timer.c#L307">307</a>                         return;
<a name="L308" href="source/net/ipv4/tcp_timer.c#L308">308</a>         }
<a name="L309" href="source/net/ipv4/tcp_timer.c#L309">309</a> 
<a name="L310" href="source/net/ipv4/tcp_timer.c#L310">310</a>         if (icsk-&gt;icsk_probes_out &gt; max_probes) {
<a name="L311" href="source/net/ipv4/tcp_timer.c#L311">311</a> <a href="ident?i=abort">abort</a>:          <a href="ident?i=tcp_write_err">tcp_write_err</a>(sk);
<a name="L312" href="source/net/ipv4/tcp_timer.c#L312">312</a>         } else {
<a name="L313" href="source/net/ipv4/tcp_timer.c#L313">313</a>                 <b><i>/* Only send another probe if we didn't close things up. */</i></b>
<a name="L314" href="source/net/ipv4/tcp_timer.c#L314">314</a>                 <a href="ident?i=tcp_send_probe0">tcp_send_probe0</a>(sk);
<a name="L315" href="source/net/ipv4/tcp_timer.c#L315">315</a>         }
<a name="L316" href="source/net/ipv4/tcp_timer.c#L316">316</a> }
<a name="L317" href="source/net/ipv4/tcp_timer.c#L317">317</a> 
<a name="L318" href="source/net/ipv4/tcp_timer.c#L318">318</a> <b><i>/*</i></b>
<a name="L319" href="source/net/ipv4/tcp_timer.c#L319">319</a> <b><i> *      Timer for Fast Open socket to retransmit SYNACK. Note that the</i></b>
<a name="L320" href="source/net/ipv4/tcp_timer.c#L320">320</a> <b><i> *      sk here is the child socket, not the parent (listener) socket.</i></b>
<a name="L321" href="source/net/ipv4/tcp_timer.c#L321">321</a> <b><i> */</i></b>
<a name="L322" href="source/net/ipv4/tcp_timer.c#L322">322</a> static void <a href="ident?i=tcp_fastopen_synack_timer">tcp_fastopen_synack_timer</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L323" href="source/net/ipv4/tcp_timer.c#L323">323</a> {
<a name="L324" href="source/net/ipv4/tcp_timer.c#L324">324</a>         struct <a href="ident?i=inet_connection_sock">inet_connection_sock</a> *icsk = <a href="ident?i=inet_csk">inet_csk</a>(sk);
<a name="L325" href="source/net/ipv4/tcp_timer.c#L325">325</a>         int max_retries = icsk-&gt;icsk_syn_retries ? :
<a name="L326" href="source/net/ipv4/tcp_timer.c#L326">326</a>             <a href="ident?i=sysctl_tcp_synack_retries">sysctl_tcp_synack_retries</a> + 1; <b><i>/* add one more retry for fastopen */</i></b>
<a name="L327" href="source/net/ipv4/tcp_timer.c#L327">327</a>         struct <a href="ident?i=request_sock">request_sock</a> *<a href="ident?i=req">req</a>;
<a name="L328" href="source/net/ipv4/tcp_timer.c#L328">328</a> 
<a name="L329" href="source/net/ipv4/tcp_timer.c#L329">329</a>         <a href="ident?i=req">req</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk)-&gt;fastopen_rsk;
<a name="L330" href="source/net/ipv4/tcp_timer.c#L330">330</a>         <a href="ident?i=req">req</a>-&gt;rsk_ops-&gt;syn_ack_timeout(<a href="ident?i=req">req</a>);
<a name="L331" href="source/net/ipv4/tcp_timer.c#L331">331</a> 
<a name="L332" href="source/net/ipv4/tcp_timer.c#L332">332</a>         if (<a href="ident?i=req">req</a>-&gt;num_timeout &gt;= max_retries) {
<a name="L333" href="source/net/ipv4/tcp_timer.c#L333">333</a>                 <a href="ident?i=tcp_write_err">tcp_write_err</a>(sk);
<a name="L334" href="source/net/ipv4/tcp_timer.c#L334">334</a>                 return;
<a name="L335" href="source/net/ipv4/tcp_timer.c#L335">335</a>         }
<a name="L336" href="source/net/ipv4/tcp_timer.c#L336">336</a>         <b><i>/* XXX (TFO) - Unlike regular SYN-ACK retransmit, we ignore error</i></b>
<a name="L337" href="source/net/ipv4/tcp_timer.c#L337">337</a> <b><i>         * returned from rtx_syn_ack() to make it more persistent like</i></b>
<a name="L338" href="source/net/ipv4/tcp_timer.c#L338">338</a> <b><i>         * regular retransmit because if the child socket has been accepted</i></b>
<a name="L339" href="source/net/ipv4/tcp_timer.c#L339">339</a> <b><i>         * it's not good to give up too easily.</i></b>
<a name="L340" href="source/net/ipv4/tcp_timer.c#L340">340</a> <b><i>         */</i></b>
<a name="L341" href="source/net/ipv4/tcp_timer.c#L341">341</a>         <a href="ident?i=inet_rtx_syn_ack">inet_rtx_syn_ack</a>(sk, <a href="ident?i=req">req</a>);
<a name="L342" href="source/net/ipv4/tcp_timer.c#L342">342</a>         <a href="ident?i=req">req</a>-&gt;num_timeout++;
<a name="L343" href="source/net/ipv4/tcp_timer.c#L343">343</a>         <a href="ident?i=inet_csk_reset_xmit_timer">inet_csk_reset_xmit_timer</a>(sk, <a href="ident?i=ICSK_TIME_RETRANS">ICSK_TIME_RETRANS</a>,
<a name="L344" href="source/net/ipv4/tcp_timer.c#L344">344</a>                           <a href="ident?i=TCP_TIMEOUT_INIT">TCP_TIMEOUT_INIT</a> &lt;&lt; <a href="ident?i=req">req</a>-&gt;num_timeout, <a href="ident?i=TCP_RTO_MAX">TCP_RTO_MAX</a>);
<a name="L345" href="source/net/ipv4/tcp_timer.c#L345">345</a> }
<a name="L346" href="source/net/ipv4/tcp_timer.c#L346">346</a> 
<a name="L347" href="source/net/ipv4/tcp_timer.c#L347">347</a> <b><i>/*</i></b>
<a name="L348" href="source/net/ipv4/tcp_timer.c#L348">348</a> <b><i> *      The TCP retransmit timer.</i></b>
<a name="L349" href="source/net/ipv4/tcp_timer.c#L349">349</a> <b><i> */</i></b>
<a name="L350" href="source/net/ipv4/tcp_timer.c#L350">350</a> 
<a name="L351" href="source/net/ipv4/tcp_timer.c#L351">351</a> void <a href="ident?i=tcp_retransmit_timer">tcp_retransmit_timer</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L352" href="source/net/ipv4/tcp_timer.c#L352">352</a> {
<a name="L353" href="source/net/ipv4/tcp_timer.c#L353">353</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L354" href="source/net/ipv4/tcp_timer.c#L354">354</a>         struct <a href="ident?i=inet_connection_sock">inet_connection_sock</a> *icsk = <a href="ident?i=inet_csk">inet_csk</a>(sk);
<a name="L355" href="source/net/ipv4/tcp_timer.c#L355">355</a> 
<a name="L356" href="source/net/ipv4/tcp_timer.c#L356">356</a>         if (<a href="ident?i=tp">tp</a>-&gt;fastopen_rsk) {
<a name="L357" href="source/net/ipv4/tcp_timer.c#L357">357</a>                 <a href="ident?i=WARN_ON_ONCE">WARN_ON_ONCE</a>(sk-&gt;<a href="ident?i=sk_state">sk_state</a> != TCP_SYN_RECV &amp;&amp;
<a name="L358" href="source/net/ipv4/tcp_timer.c#L358">358</a>                              sk-&gt;<a href="ident?i=sk_state">sk_state</a> != TCP_FIN_WAIT1);
<a name="L359" href="source/net/ipv4/tcp_timer.c#L359">359</a>                 <a href="ident?i=tcp_fastopen_synack_timer">tcp_fastopen_synack_timer</a>(sk);
<a name="L360" href="source/net/ipv4/tcp_timer.c#L360">360</a>                 <b><i>/* Before we receive ACK to our SYN-ACK don't retransmit</i></b>
<a name="L361" href="source/net/ipv4/tcp_timer.c#L361">361</a> <b><i>                 * anything else (e.g., data or FIN segments).</i></b>
<a name="L362" href="source/net/ipv4/tcp_timer.c#L362">362</a> <b><i>                 */</i></b>
<a name="L363" href="source/net/ipv4/tcp_timer.c#L363">363</a>                 return;
<a name="L364" href="source/net/ipv4/tcp_timer.c#L364">364</a>         }
<a name="L365" href="source/net/ipv4/tcp_timer.c#L365">365</a>         if (!<a href="ident?i=tp">tp</a>-&gt;packets_out)
<a name="L366" href="source/net/ipv4/tcp_timer.c#L366">366</a>                 goto <a href="ident?i=out">out</a>;
<a name="L367" href="source/net/ipv4/tcp_timer.c#L367">367</a> 
<a name="L368" href="source/net/ipv4/tcp_timer.c#L368">368</a>         <a href="ident?i=WARN_ON">WARN_ON</a>(<a href="ident?i=tcp_write_queue_empty">tcp_write_queue_empty</a>(sk));
<a name="L369" href="source/net/ipv4/tcp_timer.c#L369">369</a> 
<a name="L370" href="source/net/ipv4/tcp_timer.c#L370">370</a>         <a href="ident?i=tp">tp</a>-&gt;tlp_high_seq = 0;
<a name="L371" href="source/net/ipv4/tcp_timer.c#L371">371</a> 
<a name="L372" href="source/net/ipv4/tcp_timer.c#L372">372</a>         if (!<a href="ident?i=tp">tp</a>-&gt;snd_wnd &amp;&amp; !<a href="ident?i=sock_flag">sock_flag</a>(sk, SOCK_DEAD) &amp;&amp;
<a name="L373" href="source/net/ipv4/tcp_timer.c#L373">373</a>             !((1 &lt;&lt; sk-&gt;<a href="ident?i=sk_state">sk_state</a>) &amp; (TCPF_SYN_SENT | TCPF_SYN_RECV))) {
<a name="L374" href="source/net/ipv4/tcp_timer.c#L374">374</a>                 <b><i>/* Receiver dastardly shrinks window. Our retransmits</i></b>
<a name="L375" href="source/net/ipv4/tcp_timer.c#L375">375</a> <b><i>                 * become zero probes, but we should not timeout this</i></b>
<a name="L376" href="source/net/ipv4/tcp_timer.c#L376">376</a> <b><i>                 * connection. If the socket is an orphan, time it out,</i></b>
<a name="L377" href="source/net/ipv4/tcp_timer.c#L377">377</a> <b><i>                 * we cannot allow such beasts to hang infinitely.</i></b>
<a name="L378" href="source/net/ipv4/tcp_timer.c#L378">378</a> <b><i>                 */</i></b>
<a name="L379" href="source/net/ipv4/tcp_timer.c#L379">379</a>                 struct <a href="ident?i=inet_sock">inet_sock</a> *inet = <a href="ident?i=inet_sk">inet_sk</a>(sk);
<a name="L380" href="source/net/ipv4/tcp_timer.c#L380">380</a>                 if (sk-&gt;<a href="ident?i=sk_family">sk_family</a> == <a href="ident?i=AF_INET">AF_INET</a>) {
<a name="L381" href="source/net/ipv4/tcp_timer.c#L381">381</a>                         <a href="ident?i=net_dbg_ratelimited">net_dbg_ratelimited</a>(<i>"Peer %pI4:%u/%u unexpectedly shrunk window %u:%u (repaired)\n"</i>,
<a name="L382" href="source/net/ipv4/tcp_timer.c#L382">382</a>                                             &amp;inet-&gt;<a href="ident?i=inet_daddr">inet_daddr</a>,
<a name="L383" href="source/net/ipv4/tcp_timer.c#L383">383</a>                                             <a href="ident?i=ntohs">ntohs</a>(inet-&gt;<a href="ident?i=inet_dport">inet_dport</a>),
<a name="L384" href="source/net/ipv4/tcp_timer.c#L384">384</a>                                             inet-&gt;<a href="ident?i=inet_num">inet_num</a>,
<a name="L385" href="source/net/ipv4/tcp_timer.c#L385">385</a>                                             <a href="ident?i=tp">tp</a>-&gt;snd_una, <a href="ident?i=tp">tp</a>-&gt;snd_nxt);
<a name="L386" href="source/net/ipv4/tcp_timer.c#L386">386</a>                 }
<a name="L387" href="source/net/ipv4/tcp_timer.c#L387">387</a> #if <a href="ident?i=IS_ENABLED">IS_ENABLED</a>(CONFIG_IPV6)
<a name="L388" href="source/net/ipv4/tcp_timer.c#L388">388</a>                 else if (sk-&gt;<a href="ident?i=sk_family">sk_family</a> == <a href="ident?i=AF_INET6">AF_INET6</a>) {
<a name="L389" href="source/net/ipv4/tcp_timer.c#L389">389</a>                         <a href="ident?i=net_dbg_ratelimited">net_dbg_ratelimited</a>(<i>"Peer %pI6:%u/%u unexpectedly shrunk window %u:%u (repaired)\n"</i>,
<a name="L390" href="source/net/ipv4/tcp_timer.c#L390">390</a>                                             &amp;sk-&gt;<a href="ident?i=sk_v6_daddr">sk_v6_daddr</a>,
<a name="L391" href="source/net/ipv4/tcp_timer.c#L391">391</a>                                             <a href="ident?i=ntohs">ntohs</a>(inet-&gt;<a href="ident?i=inet_dport">inet_dport</a>),
<a name="L392" href="source/net/ipv4/tcp_timer.c#L392">392</a>                                             inet-&gt;<a href="ident?i=inet_num">inet_num</a>,
<a name="L393" href="source/net/ipv4/tcp_timer.c#L393">393</a>                                             <a href="ident?i=tp">tp</a>-&gt;snd_una, <a href="ident?i=tp">tp</a>-&gt;snd_nxt);
<a name="L394" href="source/net/ipv4/tcp_timer.c#L394">394</a>                 }
<a name="L395" href="source/net/ipv4/tcp_timer.c#L395">395</a> #endif
<a name="L396" href="source/net/ipv4/tcp_timer.c#L396">396</a>                 if (<a href="ident?i=tcp_time_stamp">tcp_time_stamp</a> - <a href="ident?i=tp">tp</a>-&gt;rcv_tstamp &gt; <a href="ident?i=TCP_RTO_MAX">TCP_RTO_MAX</a>) {
<a name="L397" href="source/net/ipv4/tcp_timer.c#L397">397</a>                         <a href="ident?i=tcp_write_err">tcp_write_err</a>(sk);
<a name="L398" href="source/net/ipv4/tcp_timer.c#L398">398</a>                         goto <a href="ident?i=out">out</a>;
<a name="L399" href="source/net/ipv4/tcp_timer.c#L399">399</a>                 }
<a name="L400" href="source/net/ipv4/tcp_timer.c#L400">400</a>                 <a href="ident?i=tcp_enter_loss">tcp_enter_loss</a>(sk);
<a name="L401" href="source/net/ipv4/tcp_timer.c#L401">401</a>                 <a href="ident?i=tcp_retransmit_skb">tcp_retransmit_skb</a>(sk, <a href="ident?i=tcp_write_queue_head">tcp_write_queue_head</a>(sk));
<a name="L402" href="source/net/ipv4/tcp_timer.c#L402">402</a>                 <a href="ident?i=__sk_dst_reset">__sk_dst_reset</a>(sk);
<a name="L403" href="source/net/ipv4/tcp_timer.c#L403">403</a>                 goto out_reset_timer;
<a name="L404" href="source/net/ipv4/tcp_timer.c#L404">404</a>         }
<a name="L405" href="source/net/ipv4/tcp_timer.c#L405">405</a> 
<a name="L406" href="source/net/ipv4/tcp_timer.c#L406">406</a>         if (<a href="ident?i=tcp_write_timeout">tcp_write_timeout</a>(sk))
<a name="L407" href="source/net/ipv4/tcp_timer.c#L407">407</a>                 goto <a href="ident?i=out">out</a>;
<a name="L408" href="source/net/ipv4/tcp_timer.c#L408">408</a> 
<a name="L409" href="source/net/ipv4/tcp_timer.c#L409">409</a>         if (icsk-&gt;icsk_retransmits == 0) {
<a name="L410" href="source/net/ipv4/tcp_timer.c#L410">410</a>                 int mib_idx;
<a name="L411" href="source/net/ipv4/tcp_timer.c#L411">411</a> 
<a name="L412" href="source/net/ipv4/tcp_timer.c#L412">412</a>                 if (icsk-&gt;icsk_ca_state == TCP_CA_Recovery) {
<a name="L413" href="source/net/ipv4/tcp_timer.c#L413">413</a>                         if (<a href="ident?i=tcp_is_sack">tcp_is_sack</a>(<a href="ident?i=tp">tp</a>))
<a name="L414" href="source/net/ipv4/tcp_timer.c#L414">414</a>                                 mib_idx = LINUX_MIB_TCPSACKRECOVERYFAIL;
<a name="L415" href="source/net/ipv4/tcp_timer.c#L415">415</a>                         else
<a name="L416" href="source/net/ipv4/tcp_timer.c#L416">416</a>                                 mib_idx = LINUX_MIB_TCPRENORECOVERYFAIL;
<a name="L417" href="source/net/ipv4/tcp_timer.c#L417">417</a>                 } else if (icsk-&gt;icsk_ca_state == TCP_CA_Loss) {
<a name="L418" href="source/net/ipv4/tcp_timer.c#L418">418</a>                         mib_idx = LINUX_MIB_TCPLOSSFAILURES;
<a name="L419" href="source/net/ipv4/tcp_timer.c#L419">419</a>                 } else if ((icsk-&gt;icsk_ca_state == TCP_CA_Disorder) ||
<a name="L420" href="source/net/ipv4/tcp_timer.c#L420">420</a>                            <a href="ident?i=tp">tp</a>-&gt;sacked_out) {
<a name="L421" href="source/net/ipv4/tcp_timer.c#L421">421</a>                         if (<a href="ident?i=tcp_is_sack">tcp_is_sack</a>(<a href="ident?i=tp">tp</a>))
<a name="L422" href="source/net/ipv4/tcp_timer.c#L422">422</a>                                 mib_idx = LINUX_MIB_TCPSACKFAILURES;
<a name="L423" href="source/net/ipv4/tcp_timer.c#L423">423</a>                         else
<a name="L424" href="source/net/ipv4/tcp_timer.c#L424">424</a>                                 mib_idx = LINUX_MIB_TCPRENOFAILURES;
<a name="L425" href="source/net/ipv4/tcp_timer.c#L425">425</a>                 } else {
<a name="L426" href="source/net/ipv4/tcp_timer.c#L426">426</a>                         mib_idx = LINUX_MIB_TCPTIMEOUTS;
<a name="L427" href="source/net/ipv4/tcp_timer.c#L427">427</a>                 }
<a name="L428" href="source/net/ipv4/tcp_timer.c#L428">428</a>                 <a href="ident?i=NET_INC_STATS_BH">NET_INC_STATS_BH</a>(<a href="ident?i=sock_net">sock_net</a>(sk), mib_idx);
<a name="L429" href="source/net/ipv4/tcp_timer.c#L429">429</a>         }
<a name="L430" href="source/net/ipv4/tcp_timer.c#L430">430</a> 
<a name="L431" href="source/net/ipv4/tcp_timer.c#L431">431</a>         <a href="ident?i=tcp_enter_loss">tcp_enter_loss</a>(sk);
<a name="L432" href="source/net/ipv4/tcp_timer.c#L432">432</a> 
<a name="L433" href="source/net/ipv4/tcp_timer.c#L433">433</a>         if (<a href="ident?i=tcp_retransmit_skb">tcp_retransmit_skb</a>(sk, <a href="ident?i=tcp_write_queue_head">tcp_write_queue_head</a>(sk)) &gt; 0) {
<a name="L434" href="source/net/ipv4/tcp_timer.c#L434">434</a>                 <b><i>/* Retransmission failed because of local congestion,</i></b>
<a name="L435" href="source/net/ipv4/tcp_timer.c#L435">435</a> <b><i>                 * do not backoff.</i></b>
<a name="L436" href="source/net/ipv4/tcp_timer.c#L436">436</a> <b><i>                 */</i></b>
<a name="L437" href="source/net/ipv4/tcp_timer.c#L437">437</a>                 if (!icsk-&gt;icsk_retransmits)
<a name="L438" href="source/net/ipv4/tcp_timer.c#L438">438</a>                         icsk-&gt;icsk_retransmits = 1;
<a name="L439" href="source/net/ipv4/tcp_timer.c#L439">439</a>                 <a href="ident?i=inet_csk_reset_xmit_timer">inet_csk_reset_xmit_timer</a>(sk, <a href="ident?i=ICSK_TIME_RETRANS">ICSK_TIME_RETRANS</a>,
<a name="L440" href="source/net/ipv4/tcp_timer.c#L440">440</a>                                           <a href="ident?i=min">min</a>(icsk-&gt;icsk_rto, <a href="ident?i=TCP_RESOURCE_PROBE_INTERVAL">TCP_RESOURCE_PROBE_INTERVAL</a>),
<a name="L441" href="source/net/ipv4/tcp_timer.c#L441">441</a>                                           <a href="ident?i=TCP_RTO_MAX">TCP_RTO_MAX</a>);
<a name="L442" href="source/net/ipv4/tcp_timer.c#L442">442</a>                 goto <a href="ident?i=out">out</a>;
<a name="L443" href="source/net/ipv4/tcp_timer.c#L443">443</a>         }
<a name="L444" href="source/net/ipv4/tcp_timer.c#L444">444</a> 
<a name="L445" href="source/net/ipv4/tcp_timer.c#L445">445</a>         <b><i>/* Increase the timeout each time we retransmit.  Note that</i></b>
<a name="L446" href="source/net/ipv4/tcp_timer.c#L446">446</a> <b><i>         * we do not increase the rtt estimate.  rto is initialized</i></b>
<a name="L447" href="source/net/ipv4/tcp_timer.c#L447">447</a> <b><i>         * from rtt, but increases here.  Jacobson (SIGCOMM 88) suggests</i></b>
<a name="L448" href="source/net/ipv4/tcp_timer.c#L448">448</a> <b><i>         * that doubling rto each time is the least we can get away with.</i></b>
<a name="L449" href="source/net/ipv4/tcp_timer.c#L449">449</a> <b><i>         * In KA9Q, Karn uses this for the first few times, and then</i></b>
<a name="L450" href="source/net/ipv4/tcp_timer.c#L450">450</a> <b><i>         * goes to quadratic.  netBSD doubles, but only goes up to *64,</i></b>
<a name="L451" href="source/net/ipv4/tcp_timer.c#L451">451</a> <b><i>         * and clamps at 1 to 64 sec afterwards.  Note that 120 sec is</i></b>
<a name="L452" href="source/net/ipv4/tcp_timer.c#L452">452</a> <b><i>         * defined in the protocol as the maximum possible RTT.  I guess</i></b>
<a name="L453" href="source/net/ipv4/tcp_timer.c#L453">453</a> <b><i>         * we'll have to use something other than TCP to talk to the</i></b>
<a name="L454" href="source/net/ipv4/tcp_timer.c#L454">454</a> <b><i>         * University of Mars.</i></b>
<a name="L455" href="source/net/ipv4/tcp_timer.c#L455">455</a> <b><i>         *</i></b>
<a name="L456" href="source/net/ipv4/tcp_timer.c#L456">456</a> <b><i>         * PAWS allows us longer timeouts and large windows, so once</i></b>
<a name="L457" href="source/net/ipv4/tcp_timer.c#L457">457</a> <b><i>         * implemented ftp to mars will work nicely. We will have to fix</i></b>
<a name="L458" href="source/net/ipv4/tcp_timer.c#L458">458</a> <b><i>         * the 120 second clamps though!</i></b>
<a name="L459" href="source/net/ipv4/tcp_timer.c#L459">459</a> <b><i>         */</i></b>
<a name="L460" href="source/net/ipv4/tcp_timer.c#L460">460</a>         icsk-&gt;icsk_backoff++;
<a name="L461" href="source/net/ipv4/tcp_timer.c#L461">461</a>         icsk-&gt;icsk_retransmits++;
<a name="L462" href="source/net/ipv4/tcp_timer.c#L462">462</a> 
<a name="L463" href="source/net/ipv4/tcp_timer.c#L463">463</a> out_reset_timer:
<a name="L464" href="source/net/ipv4/tcp_timer.c#L464">464</a>         <b><i>/* If stream is thin, use linear timeouts. Since 'icsk_backoff' is</i></b>
<a name="L465" href="source/net/ipv4/tcp_timer.c#L465">465</a> <b><i>         * used to reset timer, set to 0. Recalculate 'icsk_rto' as this</i></b>
<a name="L466" href="source/net/ipv4/tcp_timer.c#L466">466</a> <b><i>         * might be increased if the stream oscillates between thin and thick,</i></b>
<a name="L467" href="source/net/ipv4/tcp_timer.c#L467">467</a> <b><i>         * thus the old value might already be too high compared to the value</i></b>
<a name="L468" href="source/net/ipv4/tcp_timer.c#L468">468</a> <b><i>         * set by 'tcp_set_rto' in tcp_input.c which resets the rto without</i></b>
<a name="L469" href="source/net/ipv4/tcp_timer.c#L469">469</a> <b><i>         * backoff. Limit to TCP_THIN_LINEAR_RETRIES before initiating</i></b>
<a name="L470" href="source/net/ipv4/tcp_timer.c#L470">470</a> <b><i>         * exponential backoff behaviour to avoid continue hammering</i></b>
<a name="L471" href="source/net/ipv4/tcp_timer.c#L471">471</a> <b><i>         * linear-timeout retransmissions into a black hole</i></b>
<a name="L472" href="source/net/ipv4/tcp_timer.c#L472">472</a> <b><i>         */</i></b>
<a name="L473" href="source/net/ipv4/tcp_timer.c#L473">473</a>         if (sk-&gt;<a href="ident?i=sk_state">sk_state</a> == TCP_ESTABLISHED &amp;&amp;
<a name="L474" href="source/net/ipv4/tcp_timer.c#L474">474</a>             (<a href="ident?i=tp">tp</a>-&gt;thin_lto || <a href="ident?i=sysctl_tcp_thin_linear_timeouts">sysctl_tcp_thin_linear_timeouts</a>) &amp;&amp;
<a name="L475" href="source/net/ipv4/tcp_timer.c#L475">475</a>             <a href="ident?i=tcp_stream_is_thin">tcp_stream_is_thin</a>(<a href="ident?i=tp">tp</a>) &amp;&amp;
<a name="L476" href="source/net/ipv4/tcp_timer.c#L476">476</a>             icsk-&gt;icsk_retransmits &lt;= <a href="ident?i=TCP_THIN_LINEAR_RETRIES">TCP_THIN_LINEAR_RETRIES</a>) {
<a name="L477" href="source/net/ipv4/tcp_timer.c#L477">477</a>                 icsk-&gt;icsk_backoff = 0;
<a name="L478" href="source/net/ipv4/tcp_timer.c#L478">478</a>                 icsk-&gt;icsk_rto = <a href="ident?i=min">min</a>(<a href="ident?i=__tcp_set_rto">__tcp_set_rto</a>(<a href="ident?i=tp">tp</a>), <a href="ident?i=TCP_RTO_MAX">TCP_RTO_MAX</a>);
<a name="L479" href="source/net/ipv4/tcp_timer.c#L479">479</a>         } else {
<a name="L480" href="source/net/ipv4/tcp_timer.c#L480">480</a>                 <b><i>/* Use normal (exponential) backoff */</i></b>
<a name="L481" href="source/net/ipv4/tcp_timer.c#L481">481</a>                 icsk-&gt;icsk_rto = <a href="ident?i=min">min</a>(icsk-&gt;icsk_rto &lt;&lt; 1, <a href="ident?i=TCP_RTO_MAX">TCP_RTO_MAX</a>);
<a name="L482" href="source/net/ipv4/tcp_timer.c#L482">482</a>         }
<a name="L483" href="source/net/ipv4/tcp_timer.c#L483">483</a>         <a href="ident?i=inet_csk_reset_xmit_timer">inet_csk_reset_xmit_timer</a>(sk, <a href="ident?i=ICSK_TIME_RETRANS">ICSK_TIME_RETRANS</a>, icsk-&gt;icsk_rto, <a href="ident?i=TCP_RTO_MAX">TCP_RTO_MAX</a>);
<a name="L484" href="source/net/ipv4/tcp_timer.c#L484">484</a>         if (<a href="ident?i=retransmits_timed_out">retransmits_timed_out</a>(sk, <a href="ident?i=sysctl_tcp_retries1">sysctl_tcp_retries1</a> + 1, 0, 0))
<a name="L485" href="source/net/ipv4/tcp_timer.c#L485">485</a>                 <a href="ident?i=__sk_dst_reset">__sk_dst_reset</a>(sk);
<a name="L486" href="source/net/ipv4/tcp_timer.c#L486">486</a> 
<a name="L487" href="source/net/ipv4/tcp_timer.c#L487">487</a> <a href="ident?i=out">out</a>:;
<a name="L488" href="source/net/ipv4/tcp_timer.c#L488">488</a> }
<a name="L489" href="source/net/ipv4/tcp_timer.c#L489">489</a> 
<a name="L490" href="source/net/ipv4/tcp_timer.c#L490">490</a> void <a href="ident?i=tcp_write_timer_handler">tcp_write_timer_handler</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L491" href="source/net/ipv4/tcp_timer.c#L491">491</a> {
<a name="L492" href="source/net/ipv4/tcp_timer.c#L492">492</a>         struct <a href="ident?i=inet_connection_sock">inet_connection_sock</a> *icsk = <a href="ident?i=inet_csk">inet_csk</a>(sk);
<a name="L493" href="source/net/ipv4/tcp_timer.c#L493">493</a>         int <a href="ident?i=event">event</a>;
<a name="L494" href="source/net/ipv4/tcp_timer.c#L494">494</a> 
<a name="L495" href="source/net/ipv4/tcp_timer.c#L495">495</a>         if (sk-&gt;<a href="ident?i=sk_state">sk_state</a> == TCP_CLOSE || !icsk-&gt;icsk_pending)
<a name="L496" href="source/net/ipv4/tcp_timer.c#L496">496</a>                 goto <a href="ident?i=out">out</a>;
<a name="L497" href="source/net/ipv4/tcp_timer.c#L497">497</a> 
<a name="L498" href="source/net/ipv4/tcp_timer.c#L498">498</a>         if (<a href="ident?i=time_after">time_after</a>(icsk-&gt;icsk_timeout, <a href="ident?i=jiffies">jiffies</a>)) {
<a name="L499" href="source/net/ipv4/tcp_timer.c#L499">499</a>                 <a href="ident?i=sk_reset_timer">sk_reset_timer</a>(sk, &amp;icsk-&gt;icsk_retransmit_timer, icsk-&gt;icsk_timeout);
<a name="L500" href="source/net/ipv4/tcp_timer.c#L500">500</a>                 goto <a href="ident?i=out">out</a>;
<a name="L501" href="source/net/ipv4/tcp_timer.c#L501">501</a>         }
<a name="L502" href="source/net/ipv4/tcp_timer.c#L502">502</a> 
<a name="L503" href="source/net/ipv4/tcp_timer.c#L503">503</a>         <a href="ident?i=event">event</a> = icsk-&gt;icsk_pending;
<a name="L504" href="source/net/ipv4/tcp_timer.c#L504">504</a> 
<a name="L505" href="source/net/ipv4/tcp_timer.c#L505">505</a>         switch (<a href="ident?i=event">event</a>) {
<a name="L506" href="source/net/ipv4/tcp_timer.c#L506">506</a>         case <a href="ident?i=ICSK_TIME_EARLY_RETRANS">ICSK_TIME_EARLY_RETRANS</a>:
<a name="L507" href="source/net/ipv4/tcp_timer.c#L507">507</a>                 <a href="ident?i=tcp_resume_early_retransmit">tcp_resume_early_retransmit</a>(sk);
<a name="L508" href="source/net/ipv4/tcp_timer.c#L508">508</a>                 break;
<a name="L509" href="source/net/ipv4/tcp_timer.c#L509">509</a>         case <a href="ident?i=ICSK_TIME_LOSS_PROBE">ICSK_TIME_LOSS_PROBE</a>:
<a name="L510" href="source/net/ipv4/tcp_timer.c#L510">510</a>                 <a href="ident?i=tcp_send_loss_probe">tcp_send_loss_probe</a>(sk);
<a name="L511" href="source/net/ipv4/tcp_timer.c#L511">511</a>                 break;
<a name="L512" href="source/net/ipv4/tcp_timer.c#L512">512</a>         case <a href="ident?i=ICSK_TIME_RETRANS">ICSK_TIME_RETRANS</a>:
<a name="L513" href="source/net/ipv4/tcp_timer.c#L513">513</a>                 icsk-&gt;icsk_pending = 0;
<a name="L514" href="source/net/ipv4/tcp_timer.c#L514">514</a>                 <a href="ident?i=tcp_retransmit_timer">tcp_retransmit_timer</a>(sk);
<a name="L515" href="source/net/ipv4/tcp_timer.c#L515">515</a>                 break;
<a name="L516" href="source/net/ipv4/tcp_timer.c#L516">516</a>         case <a href="ident?i=ICSK_TIME_PROBE0">ICSK_TIME_PROBE0</a>:
<a name="L517" href="source/net/ipv4/tcp_timer.c#L517">517</a>                 icsk-&gt;icsk_pending = 0;
<a name="L518" href="source/net/ipv4/tcp_timer.c#L518">518</a>                 <a href="ident?i=tcp_probe_timer">tcp_probe_timer</a>(sk);
<a name="L519" href="source/net/ipv4/tcp_timer.c#L519">519</a>                 break;
<a name="L520" href="source/net/ipv4/tcp_timer.c#L520">520</a>         }
<a name="L521" href="source/net/ipv4/tcp_timer.c#L521">521</a> 
<a name="L522" href="source/net/ipv4/tcp_timer.c#L522">522</a> <a href="ident?i=out">out</a>:
<a name="L523" href="source/net/ipv4/tcp_timer.c#L523">523</a>         <a href="ident?i=sk_mem_reclaim">sk_mem_reclaim</a>(sk);
<a name="L524" href="source/net/ipv4/tcp_timer.c#L524">524</a> }
<a name="L525" href="source/net/ipv4/tcp_timer.c#L525">525</a> 
<a name="L526" href="source/net/ipv4/tcp_timer.c#L526">526</a> static void <a href="ident?i=tcp_write_timer">tcp_write_timer</a>(unsigned long <a href="ident?i=data">data</a>)
<a name="L527" href="source/net/ipv4/tcp_timer.c#L527">527</a> {
<a name="L528" href="source/net/ipv4/tcp_timer.c#L528">528</a>         struct <a href="ident?i=sock">sock</a> *sk = (struct <a href="ident?i=sock">sock</a> *)<a href="ident?i=data">data</a>;
<a name="L529" href="source/net/ipv4/tcp_timer.c#L529">529</a> 
<a name="L530" href="source/net/ipv4/tcp_timer.c#L530">530</a>         <a href="ident?i=bh_lock_sock">bh_lock_sock</a>(sk);
<a name="L531" href="source/net/ipv4/tcp_timer.c#L531">531</a>         if (!<a href="ident?i=sock_owned_by_user">sock_owned_by_user</a>(sk)) {
<a name="L532" href="source/net/ipv4/tcp_timer.c#L532">532</a>                 <a href="ident?i=tcp_write_timer_handler">tcp_write_timer_handler</a>(sk);
<a name="L533" href="source/net/ipv4/tcp_timer.c#L533">533</a>         } else {
<a name="L534" href="source/net/ipv4/tcp_timer.c#L534">534</a>                 <b><i>/* deleguate our work to tcp_release_cb() */</i></b>
<a name="L535" href="source/net/ipv4/tcp_timer.c#L535">535</a>                 if (!<a href="ident?i=test_and_set_bit">test_and_set_bit</a>(TCP_WRITE_TIMER_DEFERRED, &amp;<a href="ident?i=tcp_sk">tcp_sk</a>(sk)-&gt;<a href="ident?i=tsq_flags">tsq_flags</a>))
<a name="L536" href="source/net/ipv4/tcp_timer.c#L536">536</a>                         <a href="ident?i=sock_hold">sock_hold</a>(sk);
<a name="L537" href="source/net/ipv4/tcp_timer.c#L537">537</a>         }
<a name="L538" href="source/net/ipv4/tcp_timer.c#L538">538</a>         <a href="ident?i=bh_unlock_sock">bh_unlock_sock</a>(sk);
<a name="L539" href="source/net/ipv4/tcp_timer.c#L539">539</a>         <a href="ident?i=sock_put">sock_put</a>(sk);
<a name="L540" href="source/net/ipv4/tcp_timer.c#L540">540</a> }
<a name="L541" href="source/net/ipv4/tcp_timer.c#L541">541</a> 
<a name="L542" href="source/net/ipv4/tcp_timer.c#L542">542</a> void <a href="ident?i=tcp_syn_ack_timeout">tcp_syn_ack_timeout</a>(const struct <a href="ident?i=request_sock">request_sock</a> *<a href="ident?i=req">req</a>)
<a name="L543" href="source/net/ipv4/tcp_timer.c#L543">543</a> {
<a name="L544" href="source/net/ipv4/tcp_timer.c#L544">544</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=read_pnet">read_pnet</a>(&amp;<a href="ident?i=inet_rsk">inet_rsk</a>(<a href="ident?i=req">req</a>)-&gt;<a href="ident?i=ireq_net">ireq_net</a>);
<a name="L545" href="source/net/ipv4/tcp_timer.c#L545">545</a> 
<a name="L546" href="source/net/ipv4/tcp_timer.c#L546">546</a>         <a href="ident?i=NET_INC_STATS_BH">NET_INC_STATS_BH</a>(<a href="ident?i=net">net</a>, LINUX_MIB_TCPTIMEOUTS);
<a name="L547" href="source/net/ipv4/tcp_timer.c#L547">547</a> }
<a name="L548" href="source/net/ipv4/tcp_timer.c#L548">548</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=tcp_syn_ack_timeout">tcp_syn_ack_timeout</a>);
<a name="L549" href="source/net/ipv4/tcp_timer.c#L549">549</a> 
<a name="L550" href="source/net/ipv4/tcp_timer.c#L550">550</a> void <a href="ident?i=tcp_set_keepalive">tcp_set_keepalive</a>(struct <a href="ident?i=sock">sock</a> *sk, int <a href="ident?i=val">val</a>)
<a name="L551" href="source/net/ipv4/tcp_timer.c#L551">551</a> {
<a name="L552" href="source/net/ipv4/tcp_timer.c#L552">552</a>         if ((1 &lt;&lt; sk-&gt;<a href="ident?i=sk_state">sk_state</a>) &amp; (TCPF_CLOSE | TCPF_LISTEN))
<a name="L553" href="source/net/ipv4/tcp_timer.c#L553">553</a>                 return;
<a name="L554" href="source/net/ipv4/tcp_timer.c#L554">554</a> 
<a name="L555" href="source/net/ipv4/tcp_timer.c#L555">555</a>         if (<a href="ident?i=val">val</a> &amp;&amp; !<a href="ident?i=sock_flag">sock_flag</a>(sk, SOCK_KEEPOPEN))
<a name="L556" href="source/net/ipv4/tcp_timer.c#L556">556</a>                 <a href="ident?i=inet_csk_reset_keepalive_timer">inet_csk_reset_keepalive_timer</a>(sk, <a href="ident?i=keepalive_time_when">keepalive_time_when</a>(<a href="ident?i=tcp_sk">tcp_sk</a>(sk)));
<a name="L557" href="source/net/ipv4/tcp_timer.c#L557">557</a>         else if (!<a href="ident?i=val">val</a>)
<a name="L558" href="source/net/ipv4/tcp_timer.c#L558">558</a>                 <a href="ident?i=inet_csk_delete_keepalive_timer">inet_csk_delete_keepalive_timer</a>(sk);
<a name="L559" href="source/net/ipv4/tcp_timer.c#L559">559</a> }
<a name="L560" href="source/net/ipv4/tcp_timer.c#L560">560</a> 
<a name="L561" href="source/net/ipv4/tcp_timer.c#L561">561</a> 
<a name="L562" href="source/net/ipv4/tcp_timer.c#L562">562</a> static void <a href="ident?i=tcp_keepalive_timer">tcp_keepalive_timer</a> (unsigned long <a href="ident?i=data">data</a>)
<a name="L563" href="source/net/ipv4/tcp_timer.c#L563">563</a> {
<a name="L564" href="source/net/ipv4/tcp_timer.c#L564">564</a>         struct <a href="ident?i=sock">sock</a> *sk = (struct <a href="ident?i=sock">sock</a> *) <a href="ident?i=data">data</a>;
<a name="L565" href="source/net/ipv4/tcp_timer.c#L565">565</a>         struct <a href="ident?i=inet_connection_sock">inet_connection_sock</a> *icsk = <a href="ident?i=inet_csk">inet_csk</a>(sk);
<a name="L566" href="source/net/ipv4/tcp_timer.c#L566">566</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L567" href="source/net/ipv4/tcp_timer.c#L567">567</a>         <a href="ident?i=u32">u32</a> elapsed;
<a name="L568" href="source/net/ipv4/tcp_timer.c#L568">568</a> 
<a name="L569" href="source/net/ipv4/tcp_timer.c#L569">569</a>         <b><i>/* Only process if socket is not in use. */</i></b>
<a name="L570" href="source/net/ipv4/tcp_timer.c#L570">570</a>         <a href="ident?i=bh_lock_sock">bh_lock_sock</a>(sk);
<a name="L571" href="source/net/ipv4/tcp_timer.c#L571">571</a>         if (<a href="ident?i=sock_owned_by_user">sock_owned_by_user</a>(sk)) {
<a name="L572" href="source/net/ipv4/tcp_timer.c#L572">572</a>                 <b><i>/* Try again later. */</i></b>
<a name="L573" href="source/net/ipv4/tcp_timer.c#L573">573</a>                 <a href="ident?i=inet_csk_reset_keepalive_timer">inet_csk_reset_keepalive_timer</a> (sk, <a href="ident?i=HZ">HZ</a>/20);
<a name="L574" href="source/net/ipv4/tcp_timer.c#L574">574</a>                 goto <a href="ident?i=out">out</a>;
<a name="L575" href="source/net/ipv4/tcp_timer.c#L575">575</a>         }
<a name="L576" href="source/net/ipv4/tcp_timer.c#L576">576</a> 
<a name="L577" href="source/net/ipv4/tcp_timer.c#L577">577</a>         if (sk-&gt;<a href="ident?i=sk_state">sk_state</a> == TCP_LISTEN) {
<a name="L578" href="source/net/ipv4/tcp_timer.c#L578">578</a>                 <a href="ident?i=pr_err">pr_err</a>(<i>"Hmm... keepalive on a LISTEN ???\n"</i>);
<a name="L579" href="source/net/ipv4/tcp_timer.c#L579">579</a>                 goto <a href="ident?i=out">out</a>;
<a name="L580" href="source/net/ipv4/tcp_timer.c#L580">580</a>         }
<a name="L581" href="source/net/ipv4/tcp_timer.c#L581">581</a> 
<a name="L582" href="source/net/ipv4/tcp_timer.c#L582">582</a>         if (sk-&gt;<a href="ident?i=sk_state">sk_state</a> == TCP_FIN_WAIT2 &amp;&amp; <a href="ident?i=sock_flag">sock_flag</a>(sk, SOCK_DEAD)) {
<a name="L583" href="source/net/ipv4/tcp_timer.c#L583">583</a>                 if (<a href="ident?i=tp">tp</a>-&gt;linger2 &gt;= 0) {
<a name="L584" href="source/net/ipv4/tcp_timer.c#L584">584</a>                         const int tmo = <a href="ident?i=tcp_fin_time">tcp_fin_time</a>(sk) - <a href="ident?i=TCP_TIMEWAIT_LEN">TCP_TIMEWAIT_LEN</a>;
<a name="L585" href="source/net/ipv4/tcp_timer.c#L585">585</a> 
<a name="L586" href="source/net/ipv4/tcp_timer.c#L586">586</a>                         if (tmo &gt; 0) {
<a name="L587" href="source/net/ipv4/tcp_timer.c#L587">587</a>                                 <a href="ident?i=tcp_time_wait">tcp_time_wait</a>(sk, TCP_FIN_WAIT2, tmo);
<a name="L588" href="source/net/ipv4/tcp_timer.c#L588">588</a>                                 goto <a href="ident?i=out">out</a>;
<a name="L589" href="source/net/ipv4/tcp_timer.c#L589">589</a>                         }
<a name="L590" href="source/net/ipv4/tcp_timer.c#L590">590</a>                 }
<a name="L591" href="source/net/ipv4/tcp_timer.c#L591">591</a>                 <a href="ident?i=tcp_send_active_reset">tcp_send_active_reset</a>(sk, <a href="ident?i=GFP_ATOMIC">GFP_ATOMIC</a>);
<a name="L592" href="source/net/ipv4/tcp_timer.c#L592">592</a>                 goto death;
<a name="L593" href="source/net/ipv4/tcp_timer.c#L593">593</a>         }
<a name="L594" href="source/net/ipv4/tcp_timer.c#L594">594</a> 
<a name="L595" href="source/net/ipv4/tcp_timer.c#L595">595</a>         if (!<a href="ident?i=sock_flag">sock_flag</a>(sk, SOCK_KEEPOPEN) || sk-&gt;<a href="ident?i=sk_state">sk_state</a> == TCP_CLOSE)
<a name="L596" href="source/net/ipv4/tcp_timer.c#L596">596</a>                 goto <a href="ident?i=out">out</a>;
<a name="L597" href="source/net/ipv4/tcp_timer.c#L597">597</a> 
<a name="L598" href="source/net/ipv4/tcp_timer.c#L598">598</a>         elapsed = <a href="ident?i=keepalive_time_when">keepalive_time_when</a>(<a href="ident?i=tp">tp</a>);
<a name="L599" href="source/net/ipv4/tcp_timer.c#L599">599</a> 
<a name="L600" href="source/net/ipv4/tcp_timer.c#L600">600</a>         <b><i>/* It is alive without keepalive 8) */</i></b>
<a name="L601" href="source/net/ipv4/tcp_timer.c#L601">601</a>         if (<a href="ident?i=tp">tp</a>-&gt;packets_out || <a href="ident?i=tcp_send_head">tcp_send_head</a>(sk))
<a name="L602" href="source/net/ipv4/tcp_timer.c#L602">602</a>                 goto resched;
<a name="L603" href="source/net/ipv4/tcp_timer.c#L603">603</a> 
<a name="L604" href="source/net/ipv4/tcp_timer.c#L604">604</a>         elapsed = <a href="ident?i=keepalive_time_elapsed">keepalive_time_elapsed</a>(<a href="ident?i=tp">tp</a>);
<a name="L605" href="source/net/ipv4/tcp_timer.c#L605">605</a> 
<a name="L606" href="source/net/ipv4/tcp_timer.c#L606">606</a>         if (elapsed &gt;= <a href="ident?i=keepalive_time_when">keepalive_time_when</a>(<a href="ident?i=tp">tp</a>)) {
<a name="L607" href="source/net/ipv4/tcp_timer.c#L607">607</a>                 <b><i>/* If the TCP_USER_TIMEOUT option is enabled, use that</i></b>
<a name="L608" href="source/net/ipv4/tcp_timer.c#L608">608</a> <b><i>                 * to determine when to timeout instead.</i></b>
<a name="L609" href="source/net/ipv4/tcp_timer.c#L609">609</a> <b><i>                 */</i></b>
<a name="L610" href="source/net/ipv4/tcp_timer.c#L610">610</a>                 if ((icsk-&gt;icsk_user_timeout != 0 &amp;&amp;
<a name="L611" href="source/net/ipv4/tcp_timer.c#L611">611</a>                     elapsed &gt;= icsk-&gt;icsk_user_timeout &amp;&amp;
<a name="L612" href="source/net/ipv4/tcp_timer.c#L612">612</a>                     icsk-&gt;icsk_probes_out &gt; 0) ||
<a name="L613" href="source/net/ipv4/tcp_timer.c#L613">613</a>                     (icsk-&gt;icsk_user_timeout == 0 &amp;&amp;
<a name="L614" href="source/net/ipv4/tcp_timer.c#L614">614</a>                     icsk-&gt;icsk_probes_out &gt;= <a href="ident?i=keepalive_probes">keepalive_probes</a>(<a href="ident?i=tp">tp</a>))) {
<a name="L615" href="source/net/ipv4/tcp_timer.c#L615">615</a>                         <a href="ident?i=tcp_send_active_reset">tcp_send_active_reset</a>(sk, <a href="ident?i=GFP_ATOMIC">GFP_ATOMIC</a>);
<a name="L616" href="source/net/ipv4/tcp_timer.c#L616">616</a>                         <a href="ident?i=tcp_write_err">tcp_write_err</a>(sk);
<a name="L617" href="source/net/ipv4/tcp_timer.c#L617">617</a>                         goto <a href="ident?i=out">out</a>;
<a name="L618" href="source/net/ipv4/tcp_timer.c#L618">618</a>                 }
<a name="L619" href="source/net/ipv4/tcp_timer.c#L619">619</a>                 if (<a href="ident?i=tcp_write_wakeup">tcp_write_wakeup</a>(sk) &lt;= 0) {
<a name="L620" href="source/net/ipv4/tcp_timer.c#L620">620</a>                         icsk-&gt;icsk_probes_out++;
<a name="L621" href="source/net/ipv4/tcp_timer.c#L621">621</a>                         elapsed = <a href="ident?i=keepalive_intvl_when">keepalive_intvl_when</a>(<a href="ident?i=tp">tp</a>);
<a name="L622" href="source/net/ipv4/tcp_timer.c#L622">622</a>                 } else {
<a name="L623" href="source/net/ipv4/tcp_timer.c#L623">623</a>                         <b><i>/* If keepalive was lost due to local congestion,</i></b>
<a name="L624" href="source/net/ipv4/tcp_timer.c#L624">624</a> <b><i>                         * try harder.</i></b>
<a name="L625" href="source/net/ipv4/tcp_timer.c#L625">625</a> <b><i>                         */</i></b>
<a name="L626" href="source/net/ipv4/tcp_timer.c#L626">626</a>                         elapsed = <a href="ident?i=TCP_RESOURCE_PROBE_INTERVAL">TCP_RESOURCE_PROBE_INTERVAL</a>;
<a name="L627" href="source/net/ipv4/tcp_timer.c#L627">627</a>                 }
<a name="L628" href="source/net/ipv4/tcp_timer.c#L628">628</a>         } else {
<a name="L629" href="source/net/ipv4/tcp_timer.c#L629">629</a>                 <b><i>/* It is tp-&gt;rcv_tstamp + keepalive_time_when(tp) */</i></b>
<a name="L630" href="source/net/ipv4/tcp_timer.c#L630">630</a>                 elapsed = <a href="ident?i=keepalive_time_when">keepalive_time_when</a>(<a href="ident?i=tp">tp</a>) - elapsed;
<a name="L631" href="source/net/ipv4/tcp_timer.c#L631">631</a>         }
<a name="L632" href="source/net/ipv4/tcp_timer.c#L632">632</a> 
<a name="L633" href="source/net/ipv4/tcp_timer.c#L633">633</a>         <a href="ident?i=sk_mem_reclaim">sk_mem_reclaim</a>(sk);
<a name="L634" href="source/net/ipv4/tcp_timer.c#L634">634</a> 
<a name="L635" href="source/net/ipv4/tcp_timer.c#L635">635</a> resched:
<a name="L636" href="source/net/ipv4/tcp_timer.c#L636">636</a>         <a href="ident?i=inet_csk_reset_keepalive_timer">inet_csk_reset_keepalive_timer</a> (sk, elapsed);
<a name="L637" href="source/net/ipv4/tcp_timer.c#L637">637</a>         goto <a href="ident?i=out">out</a>;
<a name="L638" href="source/net/ipv4/tcp_timer.c#L638">638</a> 
<a name="L639" href="source/net/ipv4/tcp_timer.c#L639">639</a> death:
<a name="L640" href="source/net/ipv4/tcp_timer.c#L640">640</a>         <a href="ident?i=tcp_done">tcp_done</a>(sk);
<a name="L641" href="source/net/ipv4/tcp_timer.c#L641">641</a> 
<a name="L642" href="source/net/ipv4/tcp_timer.c#L642">642</a> <a href="ident?i=out">out</a>:
<a name="L643" href="source/net/ipv4/tcp_timer.c#L643">643</a>         <a href="ident?i=bh_unlock_sock">bh_unlock_sock</a>(sk);
<a name="L644" href="source/net/ipv4/tcp_timer.c#L644">644</a>         <a href="ident?i=sock_put">sock_put</a>(sk);
<a name="L645" href="source/net/ipv4/tcp_timer.c#L645">645</a> }
<a name="L646" href="source/net/ipv4/tcp_timer.c#L646">646</a> 
<a name="L647" href="source/net/ipv4/tcp_timer.c#L647">647</a> void <a href="ident?i=tcp_init_xmit_timers">tcp_init_xmit_timers</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L648" href="source/net/ipv4/tcp_timer.c#L648">648</a> {
<a name="L649" href="source/net/ipv4/tcp_timer.c#L649">649</a>         <a href="ident?i=inet_csk_init_xmit_timers">inet_csk_init_xmit_timers</a>(sk, &amp;<a href="ident?i=tcp_write_timer">tcp_write_timer</a>, &amp;<a href="ident?i=tcp_delack_timer">tcp_delack_timer</a>,
<a name="L650" href="source/net/ipv4/tcp_timer.c#L650">650</a>                                   &amp;<a href="ident?i=tcp_keepalive_timer">tcp_keepalive_timer</a>);
<a name="L651" href="source/net/ipv4/tcp_timer.c#L651">651</a> }
<a name="L652" href="source/net/ipv4/tcp_timer.c#L652">652</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=tcp_init_xmit_timers">tcp_init_xmit_timers</a>);
<a name="L653" href="source/net/ipv4/tcp_timer.c#L653">653</a> </pre></div><p>
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
