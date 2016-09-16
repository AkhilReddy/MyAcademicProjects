<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title>Linux/net/ipv4/tcp_minisocks.c - Linux Cross Reference - Free Electrons</title>
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
		 &nbsp;&bull;&nbsp;<b><i>source navigation</i></b> &nbsp;&bull;&nbsp;<a href="diff/net/ipv4/tcp_minisocks.c">diff markup</a> &nbsp;&bull;&nbsp;<a href="ident">identifier search</a> &nbsp;&bull;&nbsp;<a href="search">freetext search</a> &nbsp;&bull;&nbsp;
		</p>
	</div>
</div>

<div id="topbar">
  
  <p>Version: &nbsp;<a href="source/net/ipv4/tcp_minisocks.c?v=2.0.40">2.0.40</a>&nbsp;<a href="source/net/ipv4/tcp_minisocks.c?v=2.2.26">2.2.26</a>&nbsp;<a href="source/net/ipv4/tcp_minisocks.c?v=2.4.37">2.4.37</a>&nbsp;<a href="source/net/ipv4/tcp_minisocks.c?v=3.5">3.5</a>&nbsp;<a href="source/net/ipv4/tcp_minisocks.c?v=3.6">3.6</a>&nbsp;<a href="source/net/ipv4/tcp_minisocks.c?v=3.7">3.7</a>&nbsp;<a href="source/net/ipv4/tcp_minisocks.c?v=3.8">3.8</a>&nbsp;<a href="source/net/ipv4/tcp_minisocks.c?v=3.9">3.9</a>&nbsp;<a href="source/net/ipv4/tcp_minisocks.c?v=3.10">3.10</a>&nbsp;<a href="source/net/ipv4/tcp_minisocks.c?v=3.11">3.11</a>&nbsp;<a href="source/net/ipv4/tcp_minisocks.c?v=3.12">3.12</a>&nbsp;<a href="source/net/ipv4/tcp_minisocks.c?v=3.13">3.13</a>&nbsp;<a href="source/net/ipv4/tcp_minisocks.c?v=3.14">3.14</a>&nbsp;<a href="source/net/ipv4/tcp_minisocks.c?v=3.15">3.15</a>&nbsp;<a href="source/net/ipv4/tcp_minisocks.c?v=3.16">3.16</a>&nbsp;<a href="source/net/ipv4/tcp_minisocks.c?v=3.17">3.17</a>&nbsp;<a href="source/net/ipv4/tcp_minisocks.c?v=3.18">3.18</a>&nbsp;<a href="source/net/ipv4/tcp_minisocks.c?v=3.19">3.19</a>&nbsp;<a href="source/net/ipv4/tcp_minisocks.c?v=4.0">4.0</a>&nbsp;<b><i>4.1</i></b></p>
  
</div>

<h1><a href="source/">Linux</a>/<a href="source/net/">net</a>/<a href="source/net/ipv4/">ipv4</a>/<a href="source/net/ipv4/tcp_minisocks.c">tcp_minisocks.c</a></h1>
<div id="lxrcode"><pre>  <a name="L1" href="source/net/ipv4/tcp_minisocks.c#L1">1</a> <b><i>/*</i></b>
  <a name="L2" href="source/net/ipv4/tcp_minisocks.c#L2">2</a> <b><i> * INET         An implementation of the TCP/IP protocol suite for the LINUX</i></b>
  <a name="L3" href="source/net/ipv4/tcp_minisocks.c#L3">3</a> <b><i> *              operating system.  INET is implemented using the  BSD Socket</i></b>
  <a name="L4" href="source/net/ipv4/tcp_minisocks.c#L4">4</a> <b><i> *              interface as the means of communication with the user level.</i></b>
  <a name="L5" href="source/net/ipv4/tcp_minisocks.c#L5">5</a> <b><i> *</i></b>
  <a name="L6" href="source/net/ipv4/tcp_minisocks.c#L6">6</a> <b><i> *              Implementation of the Transmission Control Protocol(TCP).</i></b>
  <a name="L7" href="source/net/ipv4/tcp_minisocks.c#L7">7</a> <b><i> *</i></b>
  <a name="L8" href="source/net/ipv4/tcp_minisocks.c#L8">8</a> <b><i> * Authors:     Ross Biro</i></b>
  <a name="L9" href="source/net/ipv4/tcp_minisocks.c#L9">9</a> <b><i> *              Fred N. van Kempen, &lt;waltje@uWalt.NL.Mugnet.ORG&gt;</i></b>
 <a name="L10" href="source/net/ipv4/tcp_minisocks.c#L10">10</a> <b><i> *              Mark Evans, &lt;evansmp@uhura.aston.ac.uk&gt;</i></b>
 <a name="L11" href="source/net/ipv4/tcp_minisocks.c#L11">11</a> <b><i> *              Corey Minyard &lt;wf-rch!minyard@relay.EU.net&gt;</i></b>
 <a name="L12" href="source/net/ipv4/tcp_minisocks.c#L12">12</a> <b><i> *              Florian La Roche, &lt;flla@stud.uni-sb.de&gt;</i></b>
 <a name="L13" href="source/net/ipv4/tcp_minisocks.c#L13">13</a> <b><i> *              Charles Hedrick, &lt;hedrick@klinzhai.rutgers.edu&gt;</i></b>
 <a name="L14" href="source/net/ipv4/tcp_minisocks.c#L14">14</a> <b><i> *              Linus Torvalds, &lt;torvalds@cs.helsinki.fi&gt;</i></b>
 <a name="L15" href="source/net/ipv4/tcp_minisocks.c#L15">15</a> <b><i> *              Alan Cox, &lt;gw4pts@gw4pts.ampr.org&gt;</i></b>
 <a name="L16" href="source/net/ipv4/tcp_minisocks.c#L16">16</a> <b><i> *              Matthew Dillon, &lt;dillon@apollo.west.oic.com&gt;</i></b>
 <a name="L17" href="source/net/ipv4/tcp_minisocks.c#L17">17</a> <b><i> *              Arnt Gulbrandsen, &lt;agulbra@nvg.unit.no&gt;</i></b>
 <a name="L18" href="source/net/ipv4/tcp_minisocks.c#L18">18</a> <b><i> *              Jorge Cwik, &lt;jorge@laser.satlink.net&gt;</i></b>
 <a name="L19" href="source/net/ipv4/tcp_minisocks.c#L19">19</a> <b><i> */</i></b>
 <a name="L20" href="source/net/ipv4/tcp_minisocks.c#L20">20</a> 
 <a name="L21" href="source/net/ipv4/tcp_minisocks.c#L21">21</a> #include &lt;linux/mm.h&gt;
 <a name="L22" href="source/net/ipv4/tcp_minisocks.c#L22">22</a> #include &lt;linux/module.h&gt;
 <a name="L23" href="source/net/ipv4/tcp_minisocks.c#L23">23</a> #include &lt;linux/slab.h&gt;
 <a name="L24" href="source/net/ipv4/tcp_minisocks.c#L24">24</a> #include &lt;linux/sysctl.h&gt;
 <a name="L25" href="source/net/ipv4/tcp_minisocks.c#L25">25</a> #include &lt;linux/workqueue.h&gt;
 <a name="L26" href="source/net/ipv4/tcp_minisocks.c#L26">26</a> #include &lt;net/tcp.h&gt;
 <a name="L27" href="source/net/ipv4/tcp_minisocks.c#L27">27</a> #include &lt;net/inet_common.h&gt;
 <a name="L28" href="source/net/ipv4/tcp_minisocks.c#L28">28</a> #include &lt;net/xfrm.h&gt;
 <a name="L29" href="source/net/ipv4/tcp_minisocks.c#L29">29</a> 
 <a name="L30" href="source/net/ipv4/tcp_minisocks.c#L30">30</a> int <a href="ident?i=sysctl_tcp_syncookies">sysctl_tcp_syncookies</a> <a href="ident?i=__read_mostly">__read_mostly</a> = 1;
 <a name="L31" href="source/net/ipv4/tcp_minisocks.c#L31">31</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=sysctl_tcp_syncookies">sysctl_tcp_syncookies</a>);
 <a name="L32" href="source/net/ipv4/tcp_minisocks.c#L32">32</a> 
 <a name="L33" href="source/net/ipv4/tcp_minisocks.c#L33">33</a> int <a href="ident?i=sysctl_tcp_abort_on_overflow">sysctl_tcp_abort_on_overflow</a> <a href="ident?i=__read_mostly">__read_mostly</a>;
 <a name="L34" href="source/net/ipv4/tcp_minisocks.c#L34">34</a> 
 <a name="L35" href="source/net/ipv4/tcp_minisocks.c#L35">35</a> struct <a href="ident?i=inet_timewait_death_row">inet_timewait_death_row</a> <a href="ident?i=tcp_death_row">tcp_death_row</a> = {
 <a name="L36" href="source/net/ipv4/tcp_minisocks.c#L36">36</a>         .sysctl_max_tw_buckets = <a href="ident?i=NR_FILE">NR_FILE</a> * 2,
 <a name="L37" href="source/net/ipv4/tcp_minisocks.c#L37">37</a>         .hashinfo       = &amp;<a href="ident?i=tcp_hashinfo">tcp_hashinfo</a>,
 <a name="L38" href="source/net/ipv4/tcp_minisocks.c#L38">38</a> };
 <a name="L39" href="source/net/ipv4/tcp_minisocks.c#L39">39</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=tcp_death_row">tcp_death_row</a>);
 <a name="L40" href="source/net/ipv4/tcp_minisocks.c#L40">40</a> 
 <a name="L41" href="source/net/ipv4/tcp_minisocks.c#L41">41</a> static <a href="ident?i=bool">bool</a> <a href="ident?i=tcp_in_window">tcp_in_window</a>(<a href="ident?i=u32">u32</a> <a href="ident?i=seq">seq</a>, <a href="ident?i=u32">u32</a> end_seq, <a href="ident?i=u32">u32</a> s_win, <a href="ident?i=u32">u32</a> e_win)
 <a name="L42" href="source/net/ipv4/tcp_minisocks.c#L42">42</a> {
 <a name="L43" href="source/net/ipv4/tcp_minisocks.c#L43">43</a>         if (<a href="ident?i=seq">seq</a> == s_win)
 <a name="L44" href="source/net/ipv4/tcp_minisocks.c#L44">44</a>                 return <a href="ident?i=true">true</a>;
 <a name="L45" href="source/net/ipv4/tcp_minisocks.c#L45">45</a>         if (<a href="ident?i=after">after</a>(end_seq, s_win) &amp;&amp; <a href="ident?i=before">before</a>(<a href="ident?i=seq">seq</a>, e_win))
 <a name="L46" href="source/net/ipv4/tcp_minisocks.c#L46">46</a>                 return <a href="ident?i=true">true</a>;
 <a name="L47" href="source/net/ipv4/tcp_minisocks.c#L47">47</a>         return <a href="ident?i=seq">seq</a> == e_win &amp;&amp; <a href="ident?i=seq">seq</a> == end_seq;
 <a name="L48" href="source/net/ipv4/tcp_minisocks.c#L48">48</a> }
 <a name="L49" href="source/net/ipv4/tcp_minisocks.c#L49">49</a> 
 <a name="L50" href="source/net/ipv4/tcp_minisocks.c#L50">50</a> static enum <a href="ident?i=tcp_tw_status">tcp_tw_status</a>
 <a name="L51" href="source/net/ipv4/tcp_minisocks.c#L51">51</a> <a href="ident?i=tcp_timewait_check_oow_rate_limit">tcp_timewait_check_oow_rate_limit</a>(struct <a href="ident?i=inet_timewait_sock">inet_timewait_sock</a> *<a href="ident?i=tw">tw</a>,
 <a name="L52" href="source/net/ipv4/tcp_minisocks.c#L52">52</a>                                   const struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, int mib_idx)
 <a name="L53" href="source/net/ipv4/tcp_minisocks.c#L53">53</a> {
 <a name="L54" href="source/net/ipv4/tcp_minisocks.c#L54">54</a>         struct <a href="ident?i=tcp_timewait_sock">tcp_timewait_sock</a> *tcptw = <a href="ident?i=tcp_twsk">tcp_twsk</a>((struct <a href="ident?i=sock">sock</a> *)<a href="ident?i=tw">tw</a>);
 <a name="L55" href="source/net/ipv4/tcp_minisocks.c#L55">55</a> 
 <a name="L56" href="source/net/ipv4/tcp_minisocks.c#L56">56</a>         if (!<a href="ident?i=tcp_oow_rate_limited">tcp_oow_rate_limited</a>(<a href="ident?i=twsk_net">twsk_net</a>(<a href="ident?i=tw">tw</a>), <a href="ident?i=skb">skb</a>, mib_idx,
 <a name="L57" href="source/net/ipv4/tcp_minisocks.c#L57">57</a>                                   &amp;tcptw-&gt;tw_last_oow_ack_time)) {
 <a name="L58" href="source/net/ipv4/tcp_minisocks.c#L58">58</a>                 <b><i>/* Send ACK. Note, we do not put the bucket,</i></b>
 <a name="L59" href="source/net/ipv4/tcp_minisocks.c#L59">59</a> <b><i>                 * it will be released by caller.</i></b>
 <a name="L60" href="source/net/ipv4/tcp_minisocks.c#L60">60</a> <b><i>                 */</i></b>
 <a name="L61" href="source/net/ipv4/tcp_minisocks.c#L61">61</a>                 return TCP_TW_ACK;
 <a name="L62" href="source/net/ipv4/tcp_minisocks.c#L62">62</a>         }
 <a name="L63" href="source/net/ipv4/tcp_minisocks.c#L63">63</a> 
 <a name="L64" href="source/net/ipv4/tcp_minisocks.c#L64">64</a>         <b><i>/* We are rate-limiting, so just release the tw sock and drop skb. */</i></b>
 <a name="L65" href="source/net/ipv4/tcp_minisocks.c#L65">65</a>         <a href="ident?i=inet_twsk_put">inet_twsk_put</a>(<a href="ident?i=tw">tw</a>);
 <a name="L66" href="source/net/ipv4/tcp_minisocks.c#L66">66</a>         return TCP_TW_SUCCESS;
 <a name="L67" href="source/net/ipv4/tcp_minisocks.c#L67">67</a> }
 <a name="L68" href="source/net/ipv4/tcp_minisocks.c#L68">68</a> 
 <a name="L69" href="source/net/ipv4/tcp_minisocks.c#L69">69</a> <b><i>/*</i></b>
 <a name="L70" href="source/net/ipv4/tcp_minisocks.c#L70">70</a> <b><i> * * Main purpose of TIME-WAIT state is to close connection gracefully,</i></b>
 <a name="L71" href="source/net/ipv4/tcp_minisocks.c#L71">71</a> <b><i> *   when one of ends sits in LAST-ACK or CLOSING retransmitting FIN</i></b>
 <a name="L72" href="source/net/ipv4/tcp_minisocks.c#L72">72</a> <b><i> *   (and, probably, tail of data) and one or more our ACKs are lost.</i></b>
 <a name="L73" href="source/net/ipv4/tcp_minisocks.c#L73">73</a> <b><i> * * What is TIME-WAIT timeout? It is associated with maximal packet</i></b>
 <a name="L74" href="source/net/ipv4/tcp_minisocks.c#L74">74</a> <b><i> *   lifetime in the internet, which results in wrong conclusion, that</i></b>
 <a name="L75" href="source/net/ipv4/tcp_minisocks.c#L75">75</a> <b><i> *   it is set to catch "old duplicate segments" wandering out of their path.</i></b>
 <a name="L76" href="source/net/ipv4/tcp_minisocks.c#L76">76</a> <b><i> *   It is not quite correct. This timeout is calculated so that it exceeds</i></b>
 <a name="L77" href="source/net/ipv4/tcp_minisocks.c#L77">77</a> <b><i> *   maximal retransmission timeout enough to allow to lose one (or more)</i></b>
 <a name="L78" href="source/net/ipv4/tcp_minisocks.c#L78">78</a> <b><i> *   segments sent by peer and our ACKs. This time may be calculated from RTO.</i></b>
 <a name="L79" href="source/net/ipv4/tcp_minisocks.c#L79">79</a> <b><i> * * When TIME-WAIT socket receives RST, it means that another end</i></b>
 <a name="L80" href="source/net/ipv4/tcp_minisocks.c#L80">80</a> <b><i> *   finally closed and we are allowed to kill TIME-WAIT too.</i></b>
 <a name="L81" href="source/net/ipv4/tcp_minisocks.c#L81">81</a> <b><i> * * Second purpose of TIME-WAIT is catching old duplicate segments.</i></b>
 <a name="L82" href="source/net/ipv4/tcp_minisocks.c#L82">82</a> <b><i> *   Well, certainly it is pure paranoia, but if we load TIME-WAIT</i></b>
 <a name="L83" href="source/net/ipv4/tcp_minisocks.c#L83">83</a> <b><i> *   with this semantics, we MUST NOT kill TIME-WAIT state with RSTs.</i></b>
 <a name="L84" href="source/net/ipv4/tcp_minisocks.c#L84">84</a> <b><i> * * If we invented some more clever way to catch duplicates</i></b>
 <a name="L85" href="source/net/ipv4/tcp_minisocks.c#L85">85</a> <b><i> *   (f.e. based on PAWS), we could truncate TIME-WAIT to several RTOs.</i></b>
 <a name="L86" href="source/net/ipv4/tcp_minisocks.c#L86">86</a> <b><i> *</i></b>
 <a name="L87" href="source/net/ipv4/tcp_minisocks.c#L87">87</a> <b><i> * The algorithm below is based on FORMAL INTERPRETATION of RFCs.</i></b>
 <a name="L88" href="source/net/ipv4/tcp_minisocks.c#L88">88</a> <b><i> * When you compare it to RFCs, please, read section SEGMENT ARRIVES</i></b>
 <a name="L89" href="source/net/ipv4/tcp_minisocks.c#L89">89</a> <b><i> * from the very beginning.</i></b>
 <a name="L90" href="source/net/ipv4/tcp_minisocks.c#L90">90</a> <b><i> *</i></b>
 <a name="L91" href="source/net/ipv4/tcp_minisocks.c#L91">91</a> <b><i> * NOTE. With recycling (and later with fin-wait-2) TW bucket</i></b>
 <a name="L92" href="source/net/ipv4/tcp_minisocks.c#L92">92</a> <b><i> * is _not_ stateless. It means, that strictly speaking we must</i></b>
 <a name="L93" href="source/net/ipv4/tcp_minisocks.c#L93">93</a> <b><i> * spinlock it. I do not want! Well, probability of misbehaviour</i></b>
 <a name="L94" href="source/net/ipv4/tcp_minisocks.c#L94">94</a> <b><i> * is ridiculously low and, seems, we could use some mb() tricks</i></b>
 <a name="L95" href="source/net/ipv4/tcp_minisocks.c#L95">95</a> <b><i> * to avoid misread sequence numbers, states etc.  --ANK</i></b>
 <a name="L96" href="source/net/ipv4/tcp_minisocks.c#L96">96</a> <b><i> *</i></b>
 <a name="L97" href="source/net/ipv4/tcp_minisocks.c#L97">97</a> <b><i> * We don't need to initialize tmp_out.sack_ok as we don't use the results</i></b>
 <a name="L98" href="source/net/ipv4/tcp_minisocks.c#L98">98</a> <b><i> */</i></b>
 <a name="L99" href="source/net/ipv4/tcp_minisocks.c#L99">99</a> enum <a href="ident?i=tcp_tw_status">tcp_tw_status</a>
<a name="L100" href="source/net/ipv4/tcp_minisocks.c#L100">100</a> <a href="ident?i=tcp_timewait_state_process">tcp_timewait_state_process</a>(struct <a href="ident?i=inet_timewait_sock">inet_timewait_sock</a> *<a href="ident?i=tw">tw</a>, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
<a name="L101" href="source/net/ipv4/tcp_minisocks.c#L101">101</a>                            const struct <a href="ident?i=tcphdr">tcphdr</a> *<a href="ident?i=th">th</a>)
<a name="L102" href="source/net/ipv4/tcp_minisocks.c#L102">102</a> {
<a name="L103" href="source/net/ipv4/tcp_minisocks.c#L103">103</a>         struct <a href="ident?i=tcp_options_received">tcp_options_received</a> tmp_opt;
<a name="L104" href="source/net/ipv4/tcp_minisocks.c#L104">104</a>         struct <a href="ident?i=tcp_timewait_sock">tcp_timewait_sock</a> *tcptw = <a href="ident?i=tcp_twsk">tcp_twsk</a>((struct <a href="ident?i=sock">sock</a> *)<a href="ident?i=tw">tw</a>);
<a name="L105" href="source/net/ipv4/tcp_minisocks.c#L105">105</a>         <a href="ident?i=bool">bool</a> paws_reject = <a href="ident?i=false">false</a>;
<a name="L106" href="source/net/ipv4/tcp_minisocks.c#L106">106</a> 
<a name="L107" href="source/net/ipv4/tcp_minisocks.c#L107">107</a>         tmp_opt.saw_tstamp = 0;
<a name="L108" href="source/net/ipv4/tcp_minisocks.c#L108">108</a>         if (<a href="ident?i=th">th</a>-&gt;doff &gt; (sizeof(*<a href="ident?i=th">th</a>) &gt;&gt; 2) &amp;&amp; tcptw-&gt;tw_ts_recent_stamp) {
<a name="L109" href="source/net/ipv4/tcp_minisocks.c#L109">109</a>                 <a href="ident?i=tcp_parse_options">tcp_parse_options</a>(<a href="ident?i=skb">skb</a>, &amp;tmp_opt, 0, <a href="ident?i=NULL">NULL</a>);
<a name="L110" href="source/net/ipv4/tcp_minisocks.c#L110">110</a> 
<a name="L111" href="source/net/ipv4/tcp_minisocks.c#L111">111</a>                 if (tmp_opt.saw_tstamp) {
<a name="L112" href="source/net/ipv4/tcp_minisocks.c#L112">112</a>                         tmp_opt.rcv_tsecr       -= tcptw-&gt;tw_ts_offset;
<a name="L113" href="source/net/ipv4/tcp_minisocks.c#L113">113</a>                         tmp_opt.ts_recent       = tcptw-&gt;tw_ts_recent;
<a name="L114" href="source/net/ipv4/tcp_minisocks.c#L114">114</a>                         tmp_opt.ts_recent_stamp = tcptw-&gt;tw_ts_recent_stamp;
<a name="L115" href="source/net/ipv4/tcp_minisocks.c#L115">115</a>                         paws_reject = <a href="ident?i=tcp_paws_reject">tcp_paws_reject</a>(&amp;tmp_opt, <a href="ident?i=th">th</a>-&gt;rst);
<a name="L116" href="source/net/ipv4/tcp_minisocks.c#L116">116</a>                 }
<a name="L117" href="source/net/ipv4/tcp_minisocks.c#L117">117</a>         }
<a name="L118" href="source/net/ipv4/tcp_minisocks.c#L118">118</a> 
<a name="L119" href="source/net/ipv4/tcp_minisocks.c#L119">119</a>         if (<a href="ident?i=tw">tw</a>-&gt;tw_substate == TCP_FIN_WAIT2) {
<a name="L120" href="source/net/ipv4/tcp_minisocks.c#L120">120</a>                 <b><i>/* Just repeat all the checks of tcp_rcv_state_process() */</i></b>
<a name="L121" href="source/net/ipv4/tcp_minisocks.c#L121">121</a> 
<a name="L122" href="source/net/ipv4/tcp_minisocks.c#L122">122</a>                 <b><i>/* Out of window, send ACK */</i></b>
<a name="L123" href="source/net/ipv4/tcp_minisocks.c#L123">123</a>                 if (paws_reject ||
<a name="L124" href="source/net/ipv4/tcp_minisocks.c#L124">124</a>                     !<a href="ident?i=tcp_in_window">tcp_in_window</a>(<a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=seq">seq</a>, <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;end_seq,
<a name="L125" href="source/net/ipv4/tcp_minisocks.c#L125">125</a>                                    tcptw-&gt;tw_rcv_nxt,
<a name="L126" href="source/net/ipv4/tcp_minisocks.c#L126">126</a>                                    tcptw-&gt;tw_rcv_nxt + tcptw-&gt;tw_rcv_wnd))
<a name="L127" href="source/net/ipv4/tcp_minisocks.c#L127">127</a>                         return <a href="ident?i=tcp_timewait_check_oow_rate_limit">tcp_timewait_check_oow_rate_limit</a>(
<a name="L128" href="source/net/ipv4/tcp_minisocks.c#L128">128</a>                                 <a href="ident?i=tw">tw</a>, <a href="ident?i=skb">skb</a>, LINUX_MIB_TCPACKSKIPPEDFINWAIT2);
<a name="L129" href="source/net/ipv4/tcp_minisocks.c#L129">129</a> 
<a name="L130" href="source/net/ipv4/tcp_minisocks.c#L130">130</a>                 if (<a href="ident?i=th">th</a>-&gt;rst)
<a name="L131" href="source/net/ipv4/tcp_minisocks.c#L131">131</a>                         goto kill;
<a name="L132" href="source/net/ipv4/tcp_minisocks.c#L132">132</a> 
<a name="L133" href="source/net/ipv4/tcp_minisocks.c#L133">133</a>                 if (<a href="ident?i=th">th</a>-&gt;syn &amp;&amp; !<a href="ident?i=before">before</a>(<a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=seq">seq</a>, tcptw-&gt;tw_rcv_nxt))
<a name="L134" href="source/net/ipv4/tcp_minisocks.c#L134">134</a>                         goto kill_with_rst;
<a name="L135" href="source/net/ipv4/tcp_minisocks.c#L135">135</a> 
<a name="L136" href="source/net/ipv4/tcp_minisocks.c#L136">136</a>                 <b><i>/* Dup ACK? */</i></b>
<a name="L137" href="source/net/ipv4/tcp_minisocks.c#L137">137</a>                 if (!<a href="ident?i=th">th</a>-&gt;ack ||
<a name="L138" href="source/net/ipv4/tcp_minisocks.c#L138">138</a>                     !<a href="ident?i=after">after</a>(<a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;end_seq, tcptw-&gt;tw_rcv_nxt) ||
<a name="L139" href="source/net/ipv4/tcp_minisocks.c#L139">139</a>                     <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;end_seq == <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=seq">seq</a>) {
<a name="L140" href="source/net/ipv4/tcp_minisocks.c#L140">140</a>                         <a href="ident?i=inet_twsk_put">inet_twsk_put</a>(<a href="ident?i=tw">tw</a>);
<a name="L141" href="source/net/ipv4/tcp_minisocks.c#L141">141</a>                         return TCP_TW_SUCCESS;
<a name="L142" href="source/net/ipv4/tcp_minisocks.c#L142">142</a>                 }
<a name="L143" href="source/net/ipv4/tcp_minisocks.c#L143">143</a> 
<a name="L144" href="source/net/ipv4/tcp_minisocks.c#L144">144</a>                 <b><i>/* New data or FIN. If new data arrive after half-duplex close,</i></b>
<a name="L145" href="source/net/ipv4/tcp_minisocks.c#L145">145</a> <b><i>                 * reset.</i></b>
<a name="L146" href="source/net/ipv4/tcp_minisocks.c#L146">146</a> <b><i>                 */</i></b>
<a name="L147" href="source/net/ipv4/tcp_minisocks.c#L147">147</a>                 if (!<a href="ident?i=th">th</a>-&gt;fin ||
<a name="L148" href="source/net/ipv4/tcp_minisocks.c#L148">148</a>                     <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;end_seq != tcptw-&gt;tw_rcv_nxt + 1) {
<a name="L149" href="source/net/ipv4/tcp_minisocks.c#L149">149</a> kill_with_rst:
<a name="L150" href="source/net/ipv4/tcp_minisocks.c#L150">150</a>                         <a href="ident?i=inet_twsk_deschedule">inet_twsk_deschedule</a>(<a href="ident?i=tw">tw</a>);
<a name="L151" href="source/net/ipv4/tcp_minisocks.c#L151">151</a>                         <a href="ident?i=inet_twsk_put">inet_twsk_put</a>(<a href="ident?i=tw">tw</a>);
<a name="L152" href="source/net/ipv4/tcp_minisocks.c#L152">152</a>                         return TCP_TW_RST;
<a name="L153" href="source/net/ipv4/tcp_minisocks.c#L153">153</a>                 }
<a name="L154" href="source/net/ipv4/tcp_minisocks.c#L154">154</a> 
<a name="L155" href="source/net/ipv4/tcp_minisocks.c#L155">155</a>                 <b><i>/* FIN arrived, enter true time-wait state. */</i></b>
<a name="L156" href="source/net/ipv4/tcp_minisocks.c#L156">156</a>                 <a href="ident?i=tw">tw</a>-&gt;tw_substate   = TCP_TIME_WAIT;
<a name="L157" href="source/net/ipv4/tcp_minisocks.c#L157">157</a>                 tcptw-&gt;tw_rcv_nxt = <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;end_seq;
<a name="L158" href="source/net/ipv4/tcp_minisocks.c#L158">158</a>                 if (tmp_opt.saw_tstamp) {
<a name="L159" href="source/net/ipv4/tcp_minisocks.c#L159">159</a>                         tcptw-&gt;tw_ts_recent_stamp = <a href="ident?i=get_seconds">get_seconds</a>();
<a name="L160" href="source/net/ipv4/tcp_minisocks.c#L160">160</a>                         tcptw-&gt;tw_ts_recent       = tmp_opt.rcv_tsval;
<a name="L161" href="source/net/ipv4/tcp_minisocks.c#L161">161</a>                 }
<a name="L162" href="source/net/ipv4/tcp_minisocks.c#L162">162</a> 
<a name="L163" href="source/net/ipv4/tcp_minisocks.c#L163">163</a>                 if (<a href="ident?i=tcp_death_row">tcp_death_row</a>.sysctl_tw_recycle &amp;&amp;
<a name="L164" href="source/net/ipv4/tcp_minisocks.c#L164">164</a>                     tcptw-&gt;tw_ts_recent_stamp &amp;&amp;
<a name="L165" href="source/net/ipv4/tcp_minisocks.c#L165">165</a>                     <a href="ident?i=tcp_tw_remember_stamp">tcp_tw_remember_stamp</a>(<a href="ident?i=tw">tw</a>))
<a name="L166" href="source/net/ipv4/tcp_minisocks.c#L166">166</a>                         <a href="ident?i=inet_twsk_schedule">inet_twsk_schedule</a>(<a href="ident?i=tw">tw</a>, <a href="ident?i=tw">tw</a>-&gt;tw_timeout);
<a name="L167" href="source/net/ipv4/tcp_minisocks.c#L167">167</a>                 else
<a name="L168" href="source/net/ipv4/tcp_minisocks.c#L168">168</a>                         <a href="ident?i=inet_twsk_schedule">inet_twsk_schedule</a>(<a href="ident?i=tw">tw</a>, <a href="ident?i=TCP_TIMEWAIT_LEN">TCP_TIMEWAIT_LEN</a>);
<a name="L169" href="source/net/ipv4/tcp_minisocks.c#L169">169</a>                 return TCP_TW_ACK;
<a name="L170" href="source/net/ipv4/tcp_minisocks.c#L170">170</a>         }
<a name="L171" href="source/net/ipv4/tcp_minisocks.c#L171">171</a> 
<a name="L172" href="source/net/ipv4/tcp_minisocks.c#L172">172</a>         <b><i>/*</i></b>
<a name="L173" href="source/net/ipv4/tcp_minisocks.c#L173">173</a> <b><i>         *      Now real TIME-WAIT state.</i></b>
<a name="L174" href="source/net/ipv4/tcp_minisocks.c#L174">174</a> <b><i>         *</i></b>
<a name="L175" href="source/net/ipv4/tcp_minisocks.c#L175">175</a> <b><i>         *      RFC 1122:</i></b>
<a name="L176" href="source/net/ipv4/tcp_minisocks.c#L176">176</a> <b><i>         *      "When a connection is [...] on TIME-WAIT state [...]</i></b>
<a name="L177" href="source/net/ipv4/tcp_minisocks.c#L177">177</a> <b><i>         *      [a TCP] MAY accept a new SYN from the remote TCP to</i></b>
<a name="L178" href="source/net/ipv4/tcp_minisocks.c#L178">178</a> <b><i>         *      reopen the connection directly, if it:</i></b>
<a name="L179" href="source/net/ipv4/tcp_minisocks.c#L179">179</a> <b><i>         *</i></b>
<a name="L180" href="source/net/ipv4/tcp_minisocks.c#L180">180</a> <b><i>         *      (1)  assigns its initial sequence number for the new</i></b>
<a name="L181" href="source/net/ipv4/tcp_minisocks.c#L181">181</a> <b><i>         *      connection to be larger than the largest sequence</i></b>
<a name="L182" href="source/net/ipv4/tcp_minisocks.c#L182">182</a> <b><i>         *      number it used on the previous connection incarnation,</i></b>
<a name="L183" href="source/net/ipv4/tcp_minisocks.c#L183">183</a> <b><i>         *      and</i></b>
<a name="L184" href="source/net/ipv4/tcp_minisocks.c#L184">184</a> <b><i>         *</i></b>
<a name="L185" href="source/net/ipv4/tcp_minisocks.c#L185">185</a> <b><i>         *      (2)  returns to TIME-WAIT state if the SYN turns out</i></b>
<a name="L186" href="source/net/ipv4/tcp_minisocks.c#L186">186</a> <b><i>         *      to be an old duplicate".</i></b>
<a name="L187" href="source/net/ipv4/tcp_minisocks.c#L187">187</a> <b><i>         */</i></b>
<a name="L188" href="source/net/ipv4/tcp_minisocks.c#L188">188</a> 
<a name="L189" href="source/net/ipv4/tcp_minisocks.c#L189">189</a>         if (!paws_reject &amp;&amp;
<a name="L190" href="source/net/ipv4/tcp_minisocks.c#L190">190</a>             (<a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=seq">seq</a> == tcptw-&gt;tw_rcv_nxt &amp;&amp;
<a name="L191" href="source/net/ipv4/tcp_minisocks.c#L191">191</a>              (<a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=seq">seq</a> == <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;end_seq || <a href="ident?i=th">th</a>-&gt;rst))) {
<a name="L192" href="source/net/ipv4/tcp_minisocks.c#L192">192</a>                 <b><i>/* In window segment, it may be only reset or bare ack. */</i></b>
<a name="L193" href="source/net/ipv4/tcp_minisocks.c#L193">193</a> 
<a name="L194" href="source/net/ipv4/tcp_minisocks.c#L194">194</a>                 if (<a href="ident?i=th">th</a>-&gt;rst) {
<a name="L195" href="source/net/ipv4/tcp_minisocks.c#L195">195</a>                         <b><i>/* This is TIME_WAIT assassination, in two flavors.</i></b>
<a name="L196" href="source/net/ipv4/tcp_minisocks.c#L196">196</a> <b><i>                         * Oh well... nobody has a sufficient solution to this</i></b>
<a name="L197" href="source/net/ipv4/tcp_minisocks.c#L197">197</a> <b><i>                         * protocol bug yet.</i></b>
<a name="L198" href="source/net/ipv4/tcp_minisocks.c#L198">198</a> <b><i>                         */</i></b>
<a name="L199" href="source/net/ipv4/tcp_minisocks.c#L199">199</a>                         if (<a href="ident?i=sysctl_tcp_rfc1337">sysctl_tcp_rfc1337</a> == 0) {
<a name="L200" href="source/net/ipv4/tcp_minisocks.c#L200">200</a> kill:
<a name="L201" href="source/net/ipv4/tcp_minisocks.c#L201">201</a>                                 <a href="ident?i=inet_twsk_deschedule">inet_twsk_deschedule</a>(<a href="ident?i=tw">tw</a>);
<a name="L202" href="source/net/ipv4/tcp_minisocks.c#L202">202</a>                                 <a href="ident?i=inet_twsk_put">inet_twsk_put</a>(<a href="ident?i=tw">tw</a>);
<a name="L203" href="source/net/ipv4/tcp_minisocks.c#L203">203</a>                                 return TCP_TW_SUCCESS;
<a name="L204" href="source/net/ipv4/tcp_minisocks.c#L204">204</a>                         }
<a name="L205" href="source/net/ipv4/tcp_minisocks.c#L205">205</a>                 }
<a name="L206" href="source/net/ipv4/tcp_minisocks.c#L206">206</a>                 <a href="ident?i=inet_twsk_schedule">inet_twsk_schedule</a>(<a href="ident?i=tw">tw</a>, <a href="ident?i=TCP_TIMEWAIT_LEN">TCP_TIMEWAIT_LEN</a>);
<a name="L207" href="source/net/ipv4/tcp_minisocks.c#L207">207</a> 
<a name="L208" href="source/net/ipv4/tcp_minisocks.c#L208">208</a>                 if (tmp_opt.saw_tstamp) {
<a name="L209" href="source/net/ipv4/tcp_minisocks.c#L209">209</a>                         tcptw-&gt;tw_ts_recent       = tmp_opt.rcv_tsval;
<a name="L210" href="source/net/ipv4/tcp_minisocks.c#L210">210</a>                         tcptw-&gt;tw_ts_recent_stamp = <a href="ident?i=get_seconds">get_seconds</a>();
<a name="L211" href="source/net/ipv4/tcp_minisocks.c#L211">211</a>                 }
<a name="L212" href="source/net/ipv4/tcp_minisocks.c#L212">212</a> 
<a name="L213" href="source/net/ipv4/tcp_minisocks.c#L213">213</a>                 <a href="ident?i=inet_twsk_put">inet_twsk_put</a>(<a href="ident?i=tw">tw</a>);
<a name="L214" href="source/net/ipv4/tcp_minisocks.c#L214">214</a>                 return TCP_TW_SUCCESS;
<a name="L215" href="source/net/ipv4/tcp_minisocks.c#L215">215</a>         }
<a name="L216" href="source/net/ipv4/tcp_minisocks.c#L216">216</a> 
<a name="L217" href="source/net/ipv4/tcp_minisocks.c#L217">217</a>         <b><i>/* Out of window segment.</i></b>
<a name="L218" href="source/net/ipv4/tcp_minisocks.c#L218">218</a> <b><i></i></b>
<a name="L219" href="source/net/ipv4/tcp_minisocks.c#L219">219</a> <b><i>           All the segments are ACKed immediately.</i></b>
<a name="L220" href="source/net/ipv4/tcp_minisocks.c#L220">220</a> <b><i></i></b>
<a name="L221" href="source/net/ipv4/tcp_minisocks.c#L221">221</a> <b><i>           The only exception is new SYN. We accept it, if it is</i></b>
<a name="L222" href="source/net/ipv4/tcp_minisocks.c#L222">222</a> <b><i>           not old duplicate and we are not in danger to be killed</i></b>
<a name="L223" href="source/net/ipv4/tcp_minisocks.c#L223">223</a> <b><i>           by delayed old duplicates. RFC check is that it has</i></b>
<a name="L224" href="source/net/ipv4/tcp_minisocks.c#L224">224</a> <b><i>           newer sequence number works at rates &lt;40Mbit/sec.</i></b>
<a name="L225" href="source/net/ipv4/tcp_minisocks.c#L225">225</a> <b><i>           However, if paws works, it is reliable AND even more,</i></b>
<a name="L226" href="source/net/ipv4/tcp_minisocks.c#L226">226</a> <b><i>           we even may relax silly seq space cutoff.</i></b>
<a name="L227" href="source/net/ipv4/tcp_minisocks.c#L227">227</a> <b><i></i></b>
<a name="L228" href="source/net/ipv4/tcp_minisocks.c#L228">228</a> <b><i>           RED-PEN: we violate main RFC requirement, if this SYN will appear</i></b>
<a name="L229" href="source/net/ipv4/tcp_minisocks.c#L229">229</a> <b><i>           old duplicate (i.e. we receive RST in reply to SYN-ACK),</i></b>
<a name="L230" href="source/net/ipv4/tcp_minisocks.c#L230">230</a> <b><i>           we must return socket to time-wait state. It is not good,</i></b>
<a name="L231" href="source/net/ipv4/tcp_minisocks.c#L231">231</a> <b><i>           but not fatal yet.</i></b>
<a name="L232" href="source/net/ipv4/tcp_minisocks.c#L232">232</a> <b><i>         */</i></b>
<a name="L233" href="source/net/ipv4/tcp_minisocks.c#L233">233</a> 
<a name="L234" href="source/net/ipv4/tcp_minisocks.c#L234">234</a>         if (<a href="ident?i=th">th</a>-&gt;syn &amp;&amp; !<a href="ident?i=th">th</a>-&gt;rst &amp;&amp; !<a href="ident?i=th">th</a>-&gt;ack &amp;&amp; !paws_reject &amp;&amp;
<a name="L235" href="source/net/ipv4/tcp_minisocks.c#L235">235</a>             (<a href="ident?i=after">after</a>(<a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=seq">seq</a>, tcptw-&gt;tw_rcv_nxt) ||
<a name="L236" href="source/net/ipv4/tcp_minisocks.c#L236">236</a>              (tmp_opt.saw_tstamp &amp;&amp;
<a name="L237" href="source/net/ipv4/tcp_minisocks.c#L237">237</a>               (<a href="ident?i=s32">s32</a>)(tcptw-&gt;tw_ts_recent - tmp_opt.rcv_tsval) &lt; 0))) {
<a name="L238" href="source/net/ipv4/tcp_minisocks.c#L238">238</a>                 <a href="ident?i=u32">u32</a> isn = tcptw-&gt;tw_snd_nxt + 65535 + 2;
<a name="L239" href="source/net/ipv4/tcp_minisocks.c#L239">239</a>                 if (isn == 0)
<a name="L240" href="source/net/ipv4/tcp_minisocks.c#L240">240</a>                         isn++;
<a name="L241" href="source/net/ipv4/tcp_minisocks.c#L241">241</a>                 <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;tcp_tw_isn = isn;
<a name="L242" href="source/net/ipv4/tcp_minisocks.c#L242">242</a>                 return TCP_TW_SYN;
<a name="L243" href="source/net/ipv4/tcp_minisocks.c#L243">243</a>         }
<a name="L244" href="source/net/ipv4/tcp_minisocks.c#L244">244</a> 
<a name="L245" href="source/net/ipv4/tcp_minisocks.c#L245">245</a>         if (paws_reject)
<a name="L246" href="source/net/ipv4/tcp_minisocks.c#L246">246</a>                 <a href="ident?i=NET_INC_STATS_BH">NET_INC_STATS_BH</a>(<a href="ident?i=twsk_net">twsk_net</a>(<a href="ident?i=tw">tw</a>), LINUX_MIB_PAWSESTABREJECTED);
<a name="L247" href="source/net/ipv4/tcp_minisocks.c#L247">247</a> 
<a name="L248" href="source/net/ipv4/tcp_minisocks.c#L248">248</a>         if (!<a href="ident?i=th">th</a>-&gt;rst) {
<a name="L249" href="source/net/ipv4/tcp_minisocks.c#L249">249</a>                 <b><i>/* In this case we must reset the TIMEWAIT timer.</i></b>
<a name="L250" href="source/net/ipv4/tcp_minisocks.c#L250">250</a> <b><i>                 *</i></b>
<a name="L251" href="source/net/ipv4/tcp_minisocks.c#L251">251</a> <b><i>                 * If it is ACKless SYN it may be both old duplicate</i></b>
<a name="L252" href="source/net/ipv4/tcp_minisocks.c#L252">252</a> <b><i>                 * and new good SYN with random sequence number &lt;rcv_nxt.</i></b>
<a name="L253" href="source/net/ipv4/tcp_minisocks.c#L253">253</a> <b><i>                 * Do not reschedule in the last case.</i></b>
<a name="L254" href="source/net/ipv4/tcp_minisocks.c#L254">254</a> <b><i>                 */</i></b>
<a name="L255" href="source/net/ipv4/tcp_minisocks.c#L255">255</a>                 if (paws_reject || <a href="ident?i=th">th</a>-&gt;ack)
<a name="L256" href="source/net/ipv4/tcp_minisocks.c#L256">256</a>                         <a href="ident?i=inet_twsk_schedule">inet_twsk_schedule</a>(<a href="ident?i=tw">tw</a>, <a href="ident?i=TCP_TIMEWAIT_LEN">TCP_TIMEWAIT_LEN</a>);
<a name="L257" href="source/net/ipv4/tcp_minisocks.c#L257">257</a> 
<a name="L258" href="source/net/ipv4/tcp_minisocks.c#L258">258</a>                 return <a href="ident?i=tcp_timewait_check_oow_rate_limit">tcp_timewait_check_oow_rate_limit</a>(
<a name="L259" href="source/net/ipv4/tcp_minisocks.c#L259">259</a>                         <a href="ident?i=tw">tw</a>, <a href="ident?i=skb">skb</a>, LINUX_MIB_TCPACKSKIPPEDTIMEWAIT);
<a name="L260" href="source/net/ipv4/tcp_minisocks.c#L260">260</a>         }
<a name="L261" href="source/net/ipv4/tcp_minisocks.c#L261">261</a>         <a href="ident?i=inet_twsk_put">inet_twsk_put</a>(<a href="ident?i=tw">tw</a>);
<a name="L262" href="source/net/ipv4/tcp_minisocks.c#L262">262</a>         return TCP_TW_SUCCESS;
<a name="L263" href="source/net/ipv4/tcp_minisocks.c#L263">263</a> }
<a name="L264" href="source/net/ipv4/tcp_minisocks.c#L264">264</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=tcp_timewait_state_process">tcp_timewait_state_process</a>);
<a name="L265" href="source/net/ipv4/tcp_minisocks.c#L265">265</a> 
<a name="L266" href="source/net/ipv4/tcp_minisocks.c#L266">266</a> <b><i>/*</i></b>
<a name="L267" href="source/net/ipv4/tcp_minisocks.c#L267">267</a> <b><i> * Move a socket to time-wait or dead fin-wait-2 state.</i></b>
<a name="L268" href="source/net/ipv4/tcp_minisocks.c#L268">268</a> <b><i> */</i></b>
<a name="L269" href="source/net/ipv4/tcp_minisocks.c#L269">269</a> void <a href="ident?i=tcp_time_wait">tcp_time_wait</a>(struct <a href="ident?i=sock">sock</a> *sk, int <a href="ident?i=state">state</a>, int timeo)
<a name="L270" href="source/net/ipv4/tcp_minisocks.c#L270">270</a> {
<a name="L271" href="source/net/ipv4/tcp_minisocks.c#L271">271</a>         const struct <a href="ident?i=inet_connection_sock">inet_connection_sock</a> *icsk = <a href="ident?i=inet_csk">inet_csk</a>(sk);
<a name="L272" href="source/net/ipv4/tcp_minisocks.c#L272">272</a>         const struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L273" href="source/net/ipv4/tcp_minisocks.c#L273">273</a>         struct <a href="ident?i=inet_timewait_sock">inet_timewait_sock</a> *<a href="ident?i=tw">tw</a>;
<a name="L274" href="source/net/ipv4/tcp_minisocks.c#L274">274</a>         <a href="ident?i=bool">bool</a> recycle_ok = <a href="ident?i=false">false</a>;
<a name="L275" href="source/net/ipv4/tcp_minisocks.c#L275">275</a> 
<a name="L276" href="source/net/ipv4/tcp_minisocks.c#L276">276</a>         if (<a href="ident?i=tcp_death_row">tcp_death_row</a>.sysctl_tw_recycle &amp;&amp; <a href="ident?i=tp">tp</a>-&gt;rx_opt.ts_recent_stamp)
<a name="L277" href="source/net/ipv4/tcp_minisocks.c#L277">277</a>                 recycle_ok = <a href="ident?i=tcp_remember_stamp">tcp_remember_stamp</a>(sk);
<a name="L278" href="source/net/ipv4/tcp_minisocks.c#L278">278</a> 
<a name="L279" href="source/net/ipv4/tcp_minisocks.c#L279">279</a>         <a href="ident?i=tw">tw</a> = <a href="ident?i=inet_twsk_alloc">inet_twsk_alloc</a>(sk, &amp;<a href="ident?i=tcp_death_row">tcp_death_row</a>, <a href="ident?i=state">state</a>);
<a name="L280" href="source/net/ipv4/tcp_minisocks.c#L280">280</a> 
<a name="L281" href="source/net/ipv4/tcp_minisocks.c#L281">281</a>         if (<a href="ident?i=tw">tw</a>) {
<a name="L282" href="source/net/ipv4/tcp_minisocks.c#L282">282</a>                 struct <a href="ident?i=tcp_timewait_sock">tcp_timewait_sock</a> *tcptw = <a href="ident?i=tcp_twsk">tcp_twsk</a>((struct <a href="ident?i=sock">sock</a> *)<a href="ident?i=tw">tw</a>);
<a name="L283" href="source/net/ipv4/tcp_minisocks.c#L283">283</a>                 const int <a href="ident?i=rto">rto</a> = (icsk-&gt;icsk_rto &lt;&lt; 2) - (icsk-&gt;icsk_rto &gt;&gt; 1);
<a name="L284" href="source/net/ipv4/tcp_minisocks.c#L284">284</a>                 struct <a href="ident?i=inet_sock">inet_sock</a> *inet = <a href="ident?i=inet_sk">inet_sk</a>(sk);
<a name="L285" href="source/net/ipv4/tcp_minisocks.c#L285">285</a> 
<a name="L286" href="source/net/ipv4/tcp_minisocks.c#L286">286</a>                 <a href="ident?i=tw">tw</a>-&gt;tw_transparent      = inet-&gt;transparent;
<a name="L287" href="source/net/ipv4/tcp_minisocks.c#L287">287</a>                 <a href="ident?i=tw">tw</a>-&gt;tw_rcv_wscale       = <a href="ident?i=tp">tp</a>-&gt;rx_opt.rcv_wscale;
<a name="L288" href="source/net/ipv4/tcp_minisocks.c#L288">288</a>                 tcptw-&gt;tw_rcv_nxt       = <a href="ident?i=tp">tp</a>-&gt;rcv_nxt;
<a name="L289" href="source/net/ipv4/tcp_minisocks.c#L289">289</a>                 tcptw-&gt;tw_snd_nxt       = <a href="ident?i=tp">tp</a>-&gt;snd_nxt;
<a name="L290" href="source/net/ipv4/tcp_minisocks.c#L290">290</a>                 tcptw-&gt;tw_rcv_wnd       = <a href="ident?i=tcp_receive_window">tcp_receive_window</a>(<a href="ident?i=tp">tp</a>);
<a name="L291" href="source/net/ipv4/tcp_minisocks.c#L291">291</a>                 tcptw-&gt;tw_ts_recent     = <a href="ident?i=tp">tp</a>-&gt;rx_opt.ts_recent;
<a name="L292" href="source/net/ipv4/tcp_minisocks.c#L292">292</a>                 tcptw-&gt;tw_ts_recent_stamp = <a href="ident?i=tp">tp</a>-&gt;rx_opt.ts_recent_stamp;
<a name="L293" href="source/net/ipv4/tcp_minisocks.c#L293">293</a>                 tcptw-&gt;tw_ts_offset     = <a href="ident?i=tp">tp</a>-&gt;tsoffset;
<a name="L294" href="source/net/ipv4/tcp_minisocks.c#L294">294</a>                 tcptw-&gt;tw_last_oow_ack_time = 0;
<a name="L295" href="source/net/ipv4/tcp_minisocks.c#L295">295</a> 
<a name="L296" href="source/net/ipv4/tcp_minisocks.c#L296">296</a> #if <a href="ident?i=IS_ENABLED">IS_ENABLED</a>(CONFIG_IPV6)
<a name="L297" href="source/net/ipv4/tcp_minisocks.c#L297">297</a>                 if (<a href="ident?i=tw">tw</a>-&gt;<a href="ident?i=tw_family">tw_family</a> == <a href="ident?i=PF_INET6">PF_INET6</a>) {
<a name="L298" href="source/net/ipv4/tcp_minisocks.c#L298">298</a>                         struct <a href="ident?i=ipv6_pinfo">ipv6_pinfo</a> *np = <a href="ident?i=inet6_sk">inet6_sk</a>(sk);
<a name="L299" href="source/net/ipv4/tcp_minisocks.c#L299">299</a> 
<a name="L300" href="source/net/ipv4/tcp_minisocks.c#L300">300</a>                         <a href="ident?i=tw">tw</a>-&gt;<a href="ident?i=tw_v6_daddr">tw_v6_daddr</a> = sk-&gt;<a href="ident?i=sk_v6_daddr">sk_v6_daddr</a>;
<a name="L301" href="source/net/ipv4/tcp_minisocks.c#L301">301</a>                         <a href="ident?i=tw">tw</a>-&gt;<a href="ident?i=tw_v6_rcv_saddr">tw_v6_rcv_saddr</a> = sk-&gt;<a href="ident?i=sk_v6_rcv_saddr">sk_v6_rcv_saddr</a>;
<a name="L302" href="source/net/ipv4/tcp_minisocks.c#L302">302</a>                         <a href="ident?i=tw">tw</a>-&gt;<a href="ident?i=tw_tclass">tw_tclass</a> = np-&gt;tclass;
<a name="L303" href="source/net/ipv4/tcp_minisocks.c#L303">303</a>                         <a href="ident?i=tw">tw</a>-&gt;tw_flowlabel = <a href="ident?i=be32_to_cpu">be32_to_cpu</a>(np-&gt;flow_label &amp; <a href="ident?i=IPV6_FLOWLABEL_MASK">IPV6_FLOWLABEL_MASK</a>);
<a name="L304" href="source/net/ipv4/tcp_minisocks.c#L304">304</a>                         <a href="ident?i=tw">tw</a>-&gt;<a href="ident?i=tw_ipv6only">tw_ipv6only</a> = sk-&gt;<a href="ident?i=sk_ipv6only">sk_ipv6only</a>;
<a name="L305" href="source/net/ipv4/tcp_minisocks.c#L305">305</a>                 }
<a name="L306" href="source/net/ipv4/tcp_minisocks.c#L306">306</a> #endif
<a name="L307" href="source/net/ipv4/tcp_minisocks.c#L307">307</a> 
<a name="L308" href="source/net/ipv4/tcp_minisocks.c#L308">308</a> #ifdef CONFIG_TCP_MD5SIG
<a name="L309" href="source/net/ipv4/tcp_minisocks.c#L309">309</a>                 <b><i>/*</i></b>
<a name="L310" href="source/net/ipv4/tcp_minisocks.c#L310">310</a> <b><i>                 * The timewait bucket does not have the key DB from the</i></b>
<a name="L311" href="source/net/ipv4/tcp_minisocks.c#L311">311</a> <b><i>                 * sock structure. We just make a quick copy of the</i></b>
<a name="L312" href="source/net/ipv4/tcp_minisocks.c#L312">312</a> <b><i>                 * md5 key being used (if indeed we are using one)</i></b>
<a name="L313" href="source/net/ipv4/tcp_minisocks.c#L313">313</a> <b><i>                 * so the timewait ack generating code has the key.</i></b>
<a name="L314" href="source/net/ipv4/tcp_minisocks.c#L314">314</a> <b><i>                 */</i></b>
<a name="L315" href="source/net/ipv4/tcp_minisocks.c#L315">315</a>                 do {
<a name="L316" href="source/net/ipv4/tcp_minisocks.c#L316">316</a>                         struct <a href="ident?i=tcp_md5sig_key">tcp_md5sig_key</a> *<a href="ident?i=key">key</a>;
<a name="L317" href="source/net/ipv4/tcp_minisocks.c#L317">317</a>                         tcptw-&gt;tw_md5_key = <a href="ident?i=NULL">NULL</a>;
<a name="L318" href="source/net/ipv4/tcp_minisocks.c#L318">318</a>                         <a href="ident?i=key">key</a> = <a href="ident?i=tp">tp</a>-&gt;af_specific-&gt;md5_lookup(sk, sk);
<a name="L319" href="source/net/ipv4/tcp_minisocks.c#L319">319</a>                         if (<a href="ident?i=key">key</a>) {
<a name="L320" href="source/net/ipv4/tcp_minisocks.c#L320">320</a>                                 tcptw-&gt;tw_md5_key = <a href="ident?i=kmemdup">kmemdup</a>(<a href="ident?i=key">key</a>, sizeof(*<a href="ident?i=key">key</a>), <a href="ident?i=GFP_ATOMIC">GFP_ATOMIC</a>);
<a name="L321" href="source/net/ipv4/tcp_minisocks.c#L321">321</a>                                 if (tcptw-&gt;tw_md5_key &amp;&amp; !<a href="ident?i=tcp_alloc_md5sig_pool">tcp_alloc_md5sig_pool</a>())
<a name="L322" href="source/net/ipv4/tcp_minisocks.c#L322">322</a>                                         <a href="ident?i=BUG">BUG</a>();
<a name="L323" href="source/net/ipv4/tcp_minisocks.c#L323">323</a>                         }
<a name="L324" href="source/net/ipv4/tcp_minisocks.c#L324">324</a>                 } while (0);
<a name="L325" href="source/net/ipv4/tcp_minisocks.c#L325">325</a> #endif
<a name="L326" href="source/net/ipv4/tcp_minisocks.c#L326">326</a> 
<a name="L327" href="source/net/ipv4/tcp_minisocks.c#L327">327</a>                 <b><i>/* Linkage updates. */</i></b>
<a name="L328" href="source/net/ipv4/tcp_minisocks.c#L328">328</a>                 <a href="ident?i=__inet_twsk_hashdance">__inet_twsk_hashdance</a>(<a href="ident?i=tw">tw</a>, sk, &amp;<a href="ident?i=tcp_hashinfo">tcp_hashinfo</a>);
<a name="L329" href="source/net/ipv4/tcp_minisocks.c#L329">329</a> 
<a name="L330" href="source/net/ipv4/tcp_minisocks.c#L330">330</a>                 <b><i>/* Get the TIME_WAIT timeout firing. */</i></b>
<a name="L331" href="source/net/ipv4/tcp_minisocks.c#L331">331</a>                 if (timeo &lt; <a href="ident?i=rto">rto</a>)
<a name="L332" href="source/net/ipv4/tcp_minisocks.c#L332">332</a>                         timeo = <a href="ident?i=rto">rto</a>;
<a name="L333" href="source/net/ipv4/tcp_minisocks.c#L333">333</a> 
<a name="L334" href="source/net/ipv4/tcp_minisocks.c#L334">334</a>                 if (recycle_ok) {
<a name="L335" href="source/net/ipv4/tcp_minisocks.c#L335">335</a>                         <a href="ident?i=tw">tw</a>-&gt;tw_timeout = <a href="ident?i=rto">rto</a>;
<a name="L336" href="source/net/ipv4/tcp_minisocks.c#L336">336</a>                 } else {
<a name="L337" href="source/net/ipv4/tcp_minisocks.c#L337">337</a>                         <a href="ident?i=tw">tw</a>-&gt;tw_timeout = <a href="ident?i=TCP_TIMEWAIT_LEN">TCP_TIMEWAIT_LEN</a>;
<a name="L338" href="source/net/ipv4/tcp_minisocks.c#L338">338</a>                         if (<a href="ident?i=state">state</a> == TCP_TIME_WAIT)
<a name="L339" href="source/net/ipv4/tcp_minisocks.c#L339">339</a>                                 timeo = <a href="ident?i=TCP_TIMEWAIT_LEN">TCP_TIMEWAIT_LEN</a>;
<a name="L340" href="source/net/ipv4/tcp_minisocks.c#L340">340</a>                 }
<a name="L341" href="source/net/ipv4/tcp_minisocks.c#L341">341</a> 
<a name="L342" href="source/net/ipv4/tcp_minisocks.c#L342">342</a>                 <a href="ident?i=inet_twsk_schedule">inet_twsk_schedule</a>(<a href="ident?i=tw">tw</a>, timeo);
<a name="L343" href="source/net/ipv4/tcp_minisocks.c#L343">343</a>                 <a href="ident?i=inet_twsk_put">inet_twsk_put</a>(<a href="ident?i=tw">tw</a>);
<a name="L344" href="source/net/ipv4/tcp_minisocks.c#L344">344</a>         } else {
<a name="L345" href="source/net/ipv4/tcp_minisocks.c#L345">345</a>                 <b><i>/* Sorry, if we're out of memory, just CLOSE this</i></b>
<a name="L346" href="source/net/ipv4/tcp_minisocks.c#L346">346</a> <b><i>                 * socket up.  We've got bigger problems than</i></b>
<a name="L347" href="source/net/ipv4/tcp_minisocks.c#L347">347</a> <b><i>                 * non-graceful socket closings.</i></b>
<a name="L348" href="source/net/ipv4/tcp_minisocks.c#L348">348</a> <b><i>                 */</i></b>
<a name="L349" href="source/net/ipv4/tcp_minisocks.c#L349">349</a>                 <a href="ident?i=NET_INC_STATS_BH">NET_INC_STATS_BH</a>(<a href="ident?i=sock_net">sock_net</a>(sk), LINUX_MIB_TCPTIMEWAITOVERFLOW);
<a name="L350" href="source/net/ipv4/tcp_minisocks.c#L350">350</a>         }
<a name="L351" href="source/net/ipv4/tcp_minisocks.c#L351">351</a> 
<a name="L352" href="source/net/ipv4/tcp_minisocks.c#L352">352</a>         <a href="ident?i=tcp_update_metrics">tcp_update_metrics</a>(sk);
<a name="L353" href="source/net/ipv4/tcp_minisocks.c#L353">353</a>         <a href="ident?i=tcp_done">tcp_done</a>(sk);
<a name="L354" href="source/net/ipv4/tcp_minisocks.c#L354">354</a> }
<a name="L355" href="source/net/ipv4/tcp_minisocks.c#L355">355</a> 
<a name="L356" href="source/net/ipv4/tcp_minisocks.c#L356">356</a> void <a href="ident?i=tcp_twsk_destructor">tcp_twsk_destructor</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L357" href="source/net/ipv4/tcp_minisocks.c#L357">357</a> {
<a name="L358" href="source/net/ipv4/tcp_minisocks.c#L358">358</a> #ifdef CONFIG_TCP_MD5SIG
<a name="L359" href="source/net/ipv4/tcp_minisocks.c#L359">359</a>         struct <a href="ident?i=tcp_timewait_sock">tcp_timewait_sock</a> *twsk = <a href="ident?i=tcp_twsk">tcp_twsk</a>(sk);
<a name="L360" href="source/net/ipv4/tcp_minisocks.c#L360">360</a> 
<a name="L361" href="source/net/ipv4/tcp_minisocks.c#L361">361</a>         if (twsk-&gt;tw_md5_key)
<a name="L362" href="source/net/ipv4/tcp_minisocks.c#L362">362</a>                 <a href="ident?i=kfree_rcu">kfree_rcu</a>(twsk-&gt;tw_md5_key, rcu);
<a name="L363" href="source/net/ipv4/tcp_minisocks.c#L363">363</a> #endif
<a name="L364" href="source/net/ipv4/tcp_minisocks.c#L364">364</a> }
<a name="L365" href="source/net/ipv4/tcp_minisocks.c#L365">365</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=tcp_twsk_destructor">tcp_twsk_destructor</a>);
<a name="L366" href="source/net/ipv4/tcp_minisocks.c#L366">366</a> 
<a name="L367" href="source/net/ipv4/tcp_minisocks.c#L367">367</a> void <a href="ident?i=tcp_openreq_init_rwin">tcp_openreq_init_rwin</a>(struct <a href="ident?i=request_sock">request_sock</a> *<a href="ident?i=req">req</a>,
<a name="L368" href="source/net/ipv4/tcp_minisocks.c#L368">368</a>                            struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=dst_entry">dst_entry</a> *<a href="ident?i=dst">dst</a>)
<a name="L369" href="source/net/ipv4/tcp_minisocks.c#L369">369</a> {
<a name="L370" href="source/net/ipv4/tcp_minisocks.c#L370">370</a>         struct <a href="ident?i=inet_request_sock">inet_request_sock</a> *ireq = <a href="ident?i=inet_rsk">inet_rsk</a>(<a href="ident?i=req">req</a>);
<a name="L371" href="source/net/ipv4/tcp_minisocks.c#L371">371</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L372" href="source/net/ipv4/tcp_minisocks.c#L372">372</a>         <a href="ident?i=__u8">__u8</a> rcv_wscale;
<a name="L373" href="source/net/ipv4/tcp_minisocks.c#L373">373</a>         int mss = <a href="ident?i=dst_metric_advmss">dst_metric_advmss</a>(<a href="ident?i=dst">dst</a>);
<a name="L374" href="source/net/ipv4/tcp_minisocks.c#L374">374</a> 
<a name="L375" href="source/net/ipv4/tcp_minisocks.c#L375">375</a>         if (<a href="ident?i=tp">tp</a>-&gt;rx_opt.user_mss &amp;&amp; <a href="ident?i=tp">tp</a>-&gt;rx_opt.user_mss &lt; mss)
<a name="L376" href="source/net/ipv4/tcp_minisocks.c#L376">376</a>                 mss = <a href="ident?i=tp">tp</a>-&gt;rx_opt.user_mss;
<a name="L377" href="source/net/ipv4/tcp_minisocks.c#L377">377</a> 
<a name="L378" href="source/net/ipv4/tcp_minisocks.c#L378">378</a>         <b><i>/* Set this up on the first call only */</i></b>
<a name="L379" href="source/net/ipv4/tcp_minisocks.c#L379">379</a>         <a href="ident?i=req">req</a>-&gt;window_clamp = <a href="ident?i=tp">tp</a>-&gt;window_clamp ? : <a href="ident?i=dst_metric">dst_metric</a>(<a href="ident?i=dst">dst</a>, <a href="ident?i=RTAX_WINDOW">RTAX_WINDOW</a>);
<a name="L380" href="source/net/ipv4/tcp_minisocks.c#L380">380</a> 
<a name="L381" href="source/net/ipv4/tcp_minisocks.c#L381">381</a>         <b><i>/* limit the window selection if the user enforce a smaller rx buffer */</i></b>
<a name="L382" href="source/net/ipv4/tcp_minisocks.c#L382">382</a>         if (sk-&gt;sk_userlocks &amp; <a href="ident?i=SOCK_RCVBUF_LOCK">SOCK_RCVBUF_LOCK</a> &amp;&amp;
<a name="L383" href="source/net/ipv4/tcp_minisocks.c#L383">383</a>             (<a href="ident?i=req">req</a>-&gt;window_clamp &gt; <a href="ident?i=tcp_full_space">tcp_full_space</a>(sk) || <a href="ident?i=req">req</a>-&gt;window_clamp == 0))
<a name="L384" href="source/net/ipv4/tcp_minisocks.c#L384">384</a>                 <a href="ident?i=req">req</a>-&gt;window_clamp = <a href="ident?i=tcp_full_space">tcp_full_space</a>(sk);
<a name="L385" href="source/net/ipv4/tcp_minisocks.c#L385">385</a> 
<a name="L386" href="source/net/ipv4/tcp_minisocks.c#L386">386</a>         <b><i>/* tcp_full_space because it is guaranteed to be the first packet */</i></b>
<a name="L387" href="source/net/ipv4/tcp_minisocks.c#L387">387</a>         <a href="ident?i=tcp_select_initial_window">tcp_select_initial_window</a>(<a href="ident?i=tcp_full_space">tcp_full_space</a>(sk),
<a name="L388" href="source/net/ipv4/tcp_minisocks.c#L388">388</a>                 mss - (ireq-&gt;tstamp_ok ? <a href="ident?i=TCPOLEN_TSTAMP_ALIGNED">TCPOLEN_TSTAMP_ALIGNED</a> : 0),
<a name="L389" href="source/net/ipv4/tcp_minisocks.c#L389">389</a>                 &amp;<a href="ident?i=req">req</a>-&gt;rcv_wnd,
<a name="L390" href="source/net/ipv4/tcp_minisocks.c#L390">390</a>                 &amp;<a href="ident?i=req">req</a>-&gt;window_clamp,
<a name="L391" href="source/net/ipv4/tcp_minisocks.c#L391">391</a>                 ireq-&gt;wscale_ok,
<a name="L392" href="source/net/ipv4/tcp_minisocks.c#L392">392</a>                 &amp;rcv_wscale,
<a name="L393" href="source/net/ipv4/tcp_minisocks.c#L393">393</a>                 <a href="ident?i=dst_metric">dst_metric</a>(<a href="ident?i=dst">dst</a>, <a href="ident?i=RTAX_INITRWND">RTAX_INITRWND</a>));
<a name="L394" href="source/net/ipv4/tcp_minisocks.c#L394">394</a>         ireq-&gt;rcv_wscale = rcv_wscale;
<a name="L395" href="source/net/ipv4/tcp_minisocks.c#L395">395</a> }
<a name="L396" href="source/net/ipv4/tcp_minisocks.c#L396">396</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=tcp_openreq_init_rwin">tcp_openreq_init_rwin</a>);
<a name="L397" href="source/net/ipv4/tcp_minisocks.c#L397">397</a> 
<a name="L398" href="source/net/ipv4/tcp_minisocks.c#L398">398</a> static void <a href="ident?i=tcp_ecn_openreq_child">tcp_ecn_openreq_child</a>(struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a>,
<a name="L399" href="source/net/ipv4/tcp_minisocks.c#L399">399</a>                                   const struct <a href="ident?i=request_sock">request_sock</a> *<a href="ident?i=req">req</a>)
<a name="L400" href="source/net/ipv4/tcp_minisocks.c#L400">400</a> {
<a name="L401" href="source/net/ipv4/tcp_minisocks.c#L401">401</a>         <a href="ident?i=tp">tp</a>-&gt;ecn_flags = <a href="ident?i=inet_rsk">inet_rsk</a>(<a href="ident?i=req">req</a>)-&gt;ecn_ok ? <a href="ident?i=TCP_ECN_OK">TCP_ECN_OK</a> : 0;
<a name="L402" href="source/net/ipv4/tcp_minisocks.c#L402">402</a> }
<a name="L403" href="source/net/ipv4/tcp_minisocks.c#L403">403</a> 
<a name="L404" href="source/net/ipv4/tcp_minisocks.c#L404">404</a> void <a href="ident?i=tcp_ca_openreq_child">tcp_ca_openreq_child</a>(struct <a href="ident?i=sock">sock</a> *sk, const struct <a href="ident?i=dst_entry">dst_entry</a> *<a href="ident?i=dst">dst</a>)
<a name="L405" href="source/net/ipv4/tcp_minisocks.c#L405">405</a> {
<a name="L406" href="source/net/ipv4/tcp_minisocks.c#L406">406</a>         struct <a href="ident?i=inet_connection_sock">inet_connection_sock</a> *icsk = <a href="ident?i=inet_csk">inet_csk</a>(sk);
<a name="L407" href="source/net/ipv4/tcp_minisocks.c#L407">407</a>         <a href="ident?i=u32">u32</a> ca_key = <a href="ident?i=dst_metric">dst_metric</a>(<a href="ident?i=dst">dst</a>, <a href="ident?i=RTAX_CC_ALGO">RTAX_CC_ALGO</a>);
<a name="L408" href="source/net/ipv4/tcp_minisocks.c#L408">408</a>         <a href="ident?i=bool">bool</a> ca_got_dst = <a href="ident?i=false">false</a>;
<a name="L409" href="source/net/ipv4/tcp_minisocks.c#L409">409</a> 
<a name="L410" href="source/net/ipv4/tcp_minisocks.c#L410">410</a>         if (ca_key != <a href="ident?i=TCP_CA_UNSPEC">TCP_CA_UNSPEC</a>) {
<a name="L411" href="source/net/ipv4/tcp_minisocks.c#L411">411</a>                 const struct <a href="ident?i=tcp_congestion_ops">tcp_congestion_ops</a> *<a href="ident?i=ca">ca</a>;
<a name="L412" href="source/net/ipv4/tcp_minisocks.c#L412">412</a> 
<a name="L413" href="source/net/ipv4/tcp_minisocks.c#L413">413</a>                 <a href="ident?i=rcu_read_lock">rcu_read_lock</a>();
<a name="L414" href="source/net/ipv4/tcp_minisocks.c#L414">414</a>                 <a href="ident?i=ca">ca</a> = <a href="ident?i=tcp_ca_find_key">tcp_ca_find_key</a>(ca_key);
<a name="L415" href="source/net/ipv4/tcp_minisocks.c#L415">415</a>                 if (<a href="ident?i=likely">likely</a>(<a href="ident?i=ca">ca</a> &amp;&amp; <a href="ident?i=try_module_get">try_module_get</a>(<a href="ident?i=ca">ca</a>-&gt;owner))) {
<a name="L416" href="source/net/ipv4/tcp_minisocks.c#L416">416</a>                         icsk-&gt;icsk_ca_dst_locked = <a href="ident?i=tcp_ca_dst_locked">tcp_ca_dst_locked</a>(<a href="ident?i=dst">dst</a>);
<a name="L417" href="source/net/ipv4/tcp_minisocks.c#L417">417</a>                         icsk-&gt;icsk_ca_ops = <a href="ident?i=ca">ca</a>;
<a name="L418" href="source/net/ipv4/tcp_minisocks.c#L418">418</a>                         ca_got_dst = <a href="ident?i=true">true</a>;
<a name="L419" href="source/net/ipv4/tcp_minisocks.c#L419">419</a>                 }
<a name="L420" href="source/net/ipv4/tcp_minisocks.c#L420">420</a>                 <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L421" href="source/net/ipv4/tcp_minisocks.c#L421">421</a>         }
<a name="L422" href="source/net/ipv4/tcp_minisocks.c#L422">422</a> 
<a name="L423" href="source/net/ipv4/tcp_minisocks.c#L423">423</a>         <b><i>/* If no valid choice made yet, assign current system default ca. */</i></b>
<a name="L424" href="source/net/ipv4/tcp_minisocks.c#L424">424</a>         if (!ca_got_dst &amp;&amp;
<a name="L425" href="source/net/ipv4/tcp_minisocks.c#L425">425</a>             (!icsk-&gt;icsk_ca_setsockopt ||
<a name="L426" href="source/net/ipv4/tcp_minisocks.c#L426">426</a>              !<a href="ident?i=try_module_get">try_module_get</a>(icsk-&gt;icsk_ca_ops-&gt;owner)))
<a name="L427" href="source/net/ipv4/tcp_minisocks.c#L427">427</a>                 <a href="ident?i=tcp_assign_congestion_control">tcp_assign_congestion_control</a>(sk);
<a name="L428" href="source/net/ipv4/tcp_minisocks.c#L428">428</a> 
<a name="L429" href="source/net/ipv4/tcp_minisocks.c#L429">429</a>         <a href="ident?i=tcp_set_ca_state">tcp_set_ca_state</a>(sk, TCP_CA_Open);
<a name="L430" href="source/net/ipv4/tcp_minisocks.c#L430">430</a> }
<a name="L431" href="source/net/ipv4/tcp_minisocks.c#L431">431</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=tcp_ca_openreq_child">tcp_ca_openreq_child</a>);
<a name="L432" href="source/net/ipv4/tcp_minisocks.c#L432">432</a> 
<a name="L433" href="source/net/ipv4/tcp_minisocks.c#L433">433</a> <b><i>/* This is not only more efficient than what we used to do, it eliminates</i></b>
<a name="L434" href="source/net/ipv4/tcp_minisocks.c#L434">434</a> <b><i> * a lot of code duplication between IPv4/IPv6 SYN recv processing. -DaveM</i></b>
<a name="L435" href="source/net/ipv4/tcp_minisocks.c#L435">435</a> <b><i> *</i></b>
<a name="L436" href="source/net/ipv4/tcp_minisocks.c#L436">436</a> <b><i> * Actually, we could lots of memory writes here. tp of listening</i></b>
<a name="L437" href="source/net/ipv4/tcp_minisocks.c#L437">437</a> <b><i> * socket contains all necessary default parameters.</i></b>
<a name="L438" href="source/net/ipv4/tcp_minisocks.c#L438">438</a> <b><i> */</i></b>
<a name="L439" href="source/net/ipv4/tcp_minisocks.c#L439">439</a> struct <a href="ident?i=sock">sock</a> *<a href="ident?i=tcp_create_openreq_child">tcp_create_openreq_child</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=request_sock">request_sock</a> *<a href="ident?i=req">req</a>, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L440" href="source/net/ipv4/tcp_minisocks.c#L440">440</a> {
<a name="L441" href="source/net/ipv4/tcp_minisocks.c#L441">441</a>         struct <a href="ident?i=sock">sock</a> *newsk = <a href="ident?i=inet_csk_clone_lock">inet_csk_clone_lock</a>(sk, <a href="ident?i=req">req</a>, <a href="ident?i=GFP_ATOMIC">GFP_ATOMIC</a>);
<a name="L442" href="source/net/ipv4/tcp_minisocks.c#L442">442</a> 
<a name="L443" href="source/net/ipv4/tcp_minisocks.c#L443">443</a>         if (newsk) {
<a name="L444" href="source/net/ipv4/tcp_minisocks.c#L444">444</a>                 const struct <a href="ident?i=inet_request_sock">inet_request_sock</a> *ireq = <a href="ident?i=inet_rsk">inet_rsk</a>(<a href="ident?i=req">req</a>);
<a name="L445" href="source/net/ipv4/tcp_minisocks.c#L445">445</a>                 struct <a href="ident?i=tcp_request_sock">tcp_request_sock</a> *treq = <a href="ident?i=tcp_rsk">tcp_rsk</a>(<a href="ident?i=req">req</a>);
<a name="L446" href="source/net/ipv4/tcp_minisocks.c#L446">446</a>                 struct <a href="ident?i=inet_connection_sock">inet_connection_sock</a> *newicsk = <a href="ident?i=inet_csk">inet_csk</a>(newsk);
<a name="L447" href="source/net/ipv4/tcp_minisocks.c#L447">447</a>                 struct <a href="ident?i=tcp_sock">tcp_sock</a> *newtp = <a href="ident?i=tcp_sk">tcp_sk</a>(newsk);
<a name="L448" href="source/net/ipv4/tcp_minisocks.c#L448">448</a> 
<a name="L449" href="source/net/ipv4/tcp_minisocks.c#L449">449</a>                 <b><i>/* Now setup tcp_sock */</i></b>
<a name="L450" href="source/net/ipv4/tcp_minisocks.c#L450">450</a>                 newtp-&gt;pred_flags = 0;
<a name="L451" href="source/net/ipv4/tcp_minisocks.c#L451">451</a> 
<a name="L452" href="source/net/ipv4/tcp_minisocks.c#L452">452</a>                 newtp-&gt;rcv_wup = newtp-&gt;copied_seq =
<a name="L453" href="source/net/ipv4/tcp_minisocks.c#L453">453</a>                 newtp-&gt;rcv_nxt = treq-&gt;rcv_isn + 1;
<a name="L454" href="source/net/ipv4/tcp_minisocks.c#L454">454</a> 
<a name="L455" href="source/net/ipv4/tcp_minisocks.c#L455">455</a>                 newtp-&gt;snd_sml = newtp-&gt;snd_una =
<a name="L456" href="source/net/ipv4/tcp_minisocks.c#L456">456</a>                 newtp-&gt;snd_nxt = newtp-&gt;snd_up = treq-&gt;snt_isn + 1;
<a name="L457" href="source/net/ipv4/tcp_minisocks.c#L457">457</a> 
<a name="L458" href="source/net/ipv4/tcp_minisocks.c#L458">458</a>                 <a href="ident?i=tcp_prequeue_init">tcp_prequeue_init</a>(newtp);
<a name="L459" href="source/net/ipv4/tcp_minisocks.c#L459">459</a>                 <a href="ident?i=INIT_LIST_HEAD">INIT_LIST_HEAD</a>(&amp;newtp-&gt;tsq_node);
<a name="L460" href="source/net/ipv4/tcp_minisocks.c#L460">460</a> 
<a name="L461" href="source/net/ipv4/tcp_minisocks.c#L461">461</a>                 <a href="ident?i=tcp_init_wl">tcp_init_wl</a>(newtp, treq-&gt;rcv_isn);
<a name="L462" href="source/net/ipv4/tcp_minisocks.c#L462">462</a> 
<a name="L463" href="source/net/ipv4/tcp_minisocks.c#L463">463</a>                 newtp-&gt;srtt_us = 0;
<a name="L464" href="source/net/ipv4/tcp_minisocks.c#L464">464</a>                 newtp-&gt;mdev_us = <a href="ident?i=jiffies_to_usecs">jiffies_to_usecs</a>(<a href="ident?i=TCP_TIMEOUT_INIT">TCP_TIMEOUT_INIT</a>);
<a name="L465" href="source/net/ipv4/tcp_minisocks.c#L465">465</a>                 newicsk-&gt;icsk_rto = <a href="ident?i=TCP_TIMEOUT_INIT">TCP_TIMEOUT_INIT</a>;
<a name="L466" href="source/net/ipv4/tcp_minisocks.c#L466">466</a> 
<a name="L467" href="source/net/ipv4/tcp_minisocks.c#L467">467</a>                 newtp-&gt;packets_out = 0;
<a name="L468" href="source/net/ipv4/tcp_minisocks.c#L468">468</a>                 newtp-&gt;retrans_out = 0;
<a name="L469" href="source/net/ipv4/tcp_minisocks.c#L469">469</a>                 newtp-&gt;sacked_out = 0;
<a name="L470" href="source/net/ipv4/tcp_minisocks.c#L470">470</a>                 newtp-&gt;fackets_out = 0;
<a name="L471" href="source/net/ipv4/tcp_minisocks.c#L471">471</a>                 newtp-&gt;snd_ssthresh = <a href="ident?i=TCP_INFINITE_SSTHRESH">TCP_INFINITE_SSTHRESH</a>;
<a name="L472" href="source/net/ipv4/tcp_minisocks.c#L472">472</a>                 <a href="ident?i=tcp_enable_early_retrans">tcp_enable_early_retrans</a>(newtp);
<a name="L473" href="source/net/ipv4/tcp_minisocks.c#L473">473</a>                 newtp-&gt;tlp_high_seq = 0;
<a name="L474" href="source/net/ipv4/tcp_minisocks.c#L474">474</a>                 newtp-&gt;lsndtime = treq-&gt;snt_synack;
<a name="L475" href="source/net/ipv4/tcp_minisocks.c#L475">475</a>                 newtp-&gt;last_oow_ack_time = 0;
<a name="L476" href="source/net/ipv4/tcp_minisocks.c#L476">476</a>                 newtp-&gt;total_retrans = <a href="ident?i=req">req</a>-&gt;num_retrans;
<a name="L477" href="source/net/ipv4/tcp_minisocks.c#L477">477</a> 
<a name="L478" href="source/net/ipv4/tcp_minisocks.c#L478">478</a>                 <b><i>/* So many TCP implementations out there (incorrectly) count the</i></b>
<a name="L479" href="source/net/ipv4/tcp_minisocks.c#L479">479</a> <b><i>                 * initial SYN frame in their delayed-ACK and congestion control</i></b>
<a name="L480" href="source/net/ipv4/tcp_minisocks.c#L480">480</a> <b><i>                 * algorithms that we must have the following bandaid to talk</i></b>
<a name="L481" href="source/net/ipv4/tcp_minisocks.c#L481">481</a> <b><i>                 * efficiently to them.  -DaveM</i></b>
<a name="L482" href="source/net/ipv4/tcp_minisocks.c#L482">482</a> <b><i>                 */</i></b>
<a name="L483" href="source/net/ipv4/tcp_minisocks.c#L483">483</a>                 newtp-&gt;snd_cwnd = <a href="ident?i=TCP_INIT_CWND">TCP_INIT_CWND</a>;
<a name="L484" href="source/net/ipv4/tcp_minisocks.c#L484">484</a>                 newtp-&gt;snd_cwnd_cnt = 0;
<a name="L485" href="source/net/ipv4/tcp_minisocks.c#L485">485</a> 
<a name="L486" href="source/net/ipv4/tcp_minisocks.c#L486">486</a>                 <a href="ident?i=tcp_init_xmit_timers">tcp_init_xmit_timers</a>(newsk);
<a name="L487" href="source/net/ipv4/tcp_minisocks.c#L487">487</a>                 <a href="ident?i=__skb_queue_head_init">__skb_queue_head_init</a>(&amp;newtp-&gt;out_of_order_queue);
<a name="L488" href="source/net/ipv4/tcp_minisocks.c#L488">488</a>                 newtp-&gt;write_seq = newtp-&gt;pushed_seq = treq-&gt;snt_isn + 1;
<a name="L489" href="source/net/ipv4/tcp_minisocks.c#L489">489</a> 
<a name="L490" href="source/net/ipv4/tcp_minisocks.c#L490">490</a>                 newtp-&gt;rx_opt.saw_tstamp = 0;
<a name="L491" href="source/net/ipv4/tcp_minisocks.c#L491">491</a> 
<a name="L492" href="source/net/ipv4/tcp_minisocks.c#L492">492</a>                 newtp-&gt;rx_opt.dsack = 0;
<a name="L493" href="source/net/ipv4/tcp_minisocks.c#L493">493</a>                 newtp-&gt;rx_opt.num_sacks = 0;
<a name="L494" href="source/net/ipv4/tcp_minisocks.c#L494">494</a> 
<a name="L495" href="source/net/ipv4/tcp_minisocks.c#L495">495</a>                 newtp-&gt;urg_data = 0;
<a name="L496" href="source/net/ipv4/tcp_minisocks.c#L496">496</a> 
<a name="L497" href="source/net/ipv4/tcp_minisocks.c#L497">497</a>                 if (<a href="ident?i=sock_flag">sock_flag</a>(newsk, SOCK_KEEPOPEN))
<a name="L498" href="source/net/ipv4/tcp_minisocks.c#L498">498</a>                         <a href="ident?i=inet_csk_reset_keepalive_timer">inet_csk_reset_keepalive_timer</a>(newsk,
<a name="L499" href="source/net/ipv4/tcp_minisocks.c#L499">499</a>                                                        <a href="ident?i=keepalive_time_when">keepalive_time_when</a>(newtp));
<a name="L500" href="source/net/ipv4/tcp_minisocks.c#L500">500</a> 
<a name="L501" href="source/net/ipv4/tcp_minisocks.c#L501">501</a>                 newtp-&gt;rx_opt.tstamp_ok = ireq-&gt;tstamp_ok;
<a name="L502" href="source/net/ipv4/tcp_minisocks.c#L502">502</a>                 if ((newtp-&gt;rx_opt.sack_ok = ireq-&gt;sack_ok) != 0) {
<a name="L503" href="source/net/ipv4/tcp_minisocks.c#L503">503</a>                         if (<a href="ident?i=sysctl_tcp_fack">sysctl_tcp_fack</a>)
<a name="L504" href="source/net/ipv4/tcp_minisocks.c#L504">504</a>                                 <a href="ident?i=tcp_enable_fack">tcp_enable_fack</a>(newtp);
<a name="L505" href="source/net/ipv4/tcp_minisocks.c#L505">505</a>                 }
<a name="L506" href="source/net/ipv4/tcp_minisocks.c#L506">506</a>                 newtp-&gt;window_clamp = <a href="ident?i=req">req</a>-&gt;window_clamp;
<a name="L507" href="source/net/ipv4/tcp_minisocks.c#L507">507</a>                 newtp-&gt;rcv_ssthresh = <a href="ident?i=req">req</a>-&gt;rcv_wnd;
<a name="L508" href="source/net/ipv4/tcp_minisocks.c#L508">508</a>                 newtp-&gt;rcv_wnd = <a href="ident?i=req">req</a>-&gt;rcv_wnd;
<a name="L509" href="source/net/ipv4/tcp_minisocks.c#L509">509</a>                 newtp-&gt;rx_opt.wscale_ok = ireq-&gt;wscale_ok;
<a name="L510" href="source/net/ipv4/tcp_minisocks.c#L510">510</a>                 if (newtp-&gt;rx_opt.wscale_ok) {
<a name="L511" href="source/net/ipv4/tcp_minisocks.c#L511">511</a>                         newtp-&gt;rx_opt.snd_wscale = ireq-&gt;snd_wscale;
<a name="L512" href="source/net/ipv4/tcp_minisocks.c#L512">512</a>                         newtp-&gt;rx_opt.rcv_wscale = ireq-&gt;rcv_wscale;
<a name="L513" href="source/net/ipv4/tcp_minisocks.c#L513">513</a>                 } else {
<a name="L514" href="source/net/ipv4/tcp_minisocks.c#L514">514</a>                         newtp-&gt;rx_opt.snd_wscale = newtp-&gt;rx_opt.rcv_wscale = 0;
<a name="L515" href="source/net/ipv4/tcp_minisocks.c#L515">515</a>                         newtp-&gt;window_clamp = <a href="ident?i=min">min</a>(newtp-&gt;window_clamp, 65535U);
<a name="L516" href="source/net/ipv4/tcp_minisocks.c#L516">516</a>                 }
<a name="L517" href="source/net/ipv4/tcp_minisocks.c#L517">517</a>                 newtp-&gt;snd_wnd = (<a href="ident?i=ntohs">ntohs</a>(<a href="ident?i=tcp_hdr">tcp_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=window">window</a>) &lt;&lt;
<a name="L518" href="source/net/ipv4/tcp_minisocks.c#L518">518</a>                                   newtp-&gt;rx_opt.snd_wscale);
<a name="L519" href="source/net/ipv4/tcp_minisocks.c#L519">519</a>                 newtp-&gt;max_window = newtp-&gt;snd_wnd;
<a name="L520" href="source/net/ipv4/tcp_minisocks.c#L520">520</a> 
<a name="L521" href="source/net/ipv4/tcp_minisocks.c#L521">521</a>                 if (newtp-&gt;rx_opt.tstamp_ok) {
<a name="L522" href="source/net/ipv4/tcp_minisocks.c#L522">522</a>                         newtp-&gt;rx_opt.ts_recent = <a href="ident?i=req">req</a>-&gt;ts_recent;
<a name="L523" href="source/net/ipv4/tcp_minisocks.c#L523">523</a>                         newtp-&gt;rx_opt.ts_recent_stamp = <a href="ident?i=get_seconds">get_seconds</a>();
<a name="L524" href="source/net/ipv4/tcp_minisocks.c#L524">524</a>                         newtp-&gt;tcp_header_len = sizeof(struct <a href="ident?i=tcphdr">tcphdr</a>) + <a href="ident?i=TCPOLEN_TSTAMP_ALIGNED">TCPOLEN_TSTAMP_ALIGNED</a>;
<a name="L525" href="source/net/ipv4/tcp_minisocks.c#L525">525</a>                 } else {
<a name="L526" href="source/net/ipv4/tcp_minisocks.c#L526">526</a>                         newtp-&gt;rx_opt.ts_recent_stamp = 0;
<a name="L527" href="source/net/ipv4/tcp_minisocks.c#L527">527</a>                         newtp-&gt;tcp_header_len = sizeof(struct <a href="ident?i=tcphdr">tcphdr</a>);
<a name="L528" href="source/net/ipv4/tcp_minisocks.c#L528">528</a>                 }
<a name="L529" href="source/net/ipv4/tcp_minisocks.c#L529">529</a>                 newtp-&gt;tsoffset = 0;
<a name="L530" href="source/net/ipv4/tcp_minisocks.c#L530">530</a> #ifdef CONFIG_TCP_MD5SIG
<a name="L531" href="source/net/ipv4/tcp_minisocks.c#L531">531</a>                 newtp-&gt;md5sig_info = <a href="ident?i=NULL">NULL</a>;      <b><i>/*XXX*/</i></b>
<a name="L532" href="source/net/ipv4/tcp_minisocks.c#L532">532</a>                 if (newtp-&gt;af_specific-&gt;md5_lookup(sk, newsk))
<a name="L533" href="source/net/ipv4/tcp_minisocks.c#L533">533</a>                         newtp-&gt;tcp_header_len += <a href="ident?i=TCPOLEN_MD5SIG_ALIGNED">TCPOLEN_MD5SIG_ALIGNED</a>;
<a name="L534" href="source/net/ipv4/tcp_minisocks.c#L534">534</a> #endif
<a name="L535" href="source/net/ipv4/tcp_minisocks.c#L535">535</a>                 if (<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a> &gt;= <a href="ident?i=TCP_MSS_DEFAULT">TCP_MSS_DEFAULT</a> + newtp-&gt;tcp_header_len)
<a name="L536" href="source/net/ipv4/tcp_minisocks.c#L536">536</a>                         newicsk-&gt;icsk_ack.last_seg_size = <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a> - newtp-&gt;tcp_header_len;
<a name="L537" href="source/net/ipv4/tcp_minisocks.c#L537">537</a>                 newtp-&gt;rx_opt.mss_clamp = <a href="ident?i=req">req</a>-&gt;mss;
<a name="L538" href="source/net/ipv4/tcp_minisocks.c#L538">538</a>                 <a href="ident?i=tcp_ecn_openreq_child">tcp_ecn_openreq_child</a>(newtp, <a href="ident?i=req">req</a>);
<a name="L539" href="source/net/ipv4/tcp_minisocks.c#L539">539</a>                 newtp-&gt;fastopen_rsk = <a href="ident?i=NULL">NULL</a>;
<a name="L540" href="source/net/ipv4/tcp_minisocks.c#L540">540</a>                 newtp-&gt;syn_data_acked = 0;
<a name="L541" href="source/net/ipv4/tcp_minisocks.c#L541">541</a> 
<a name="L542" href="source/net/ipv4/tcp_minisocks.c#L542">542</a>                 <a href="ident?i=TCP_INC_STATS_BH">TCP_INC_STATS_BH</a>(<a href="ident?i=sock_net">sock_net</a>(sk), TCP_MIB_PASSIVEOPENS);
<a name="L543" href="source/net/ipv4/tcp_minisocks.c#L543">543</a>         }
<a name="L544" href="source/net/ipv4/tcp_minisocks.c#L544">544</a>         return newsk;
<a name="L545" href="source/net/ipv4/tcp_minisocks.c#L545">545</a> }
<a name="L546" href="source/net/ipv4/tcp_minisocks.c#L546">546</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=tcp_create_openreq_child">tcp_create_openreq_child</a>);
<a name="L547" href="source/net/ipv4/tcp_minisocks.c#L547">547</a> 
<a name="L548" href="source/net/ipv4/tcp_minisocks.c#L548">548</a> <b><i>/*</i></b>
<a name="L549" href="source/net/ipv4/tcp_minisocks.c#L549">549</a> <b><i> * Process an incoming packet for SYN_RECV sockets represented as a</i></b>
<a name="L550" href="source/net/ipv4/tcp_minisocks.c#L550">550</a> <b><i> * request_sock. Normally sk is the listener socket but for TFO it</i></b>
<a name="L551" href="source/net/ipv4/tcp_minisocks.c#L551">551</a> <b><i> * points to the child socket.</i></b>
<a name="L552" href="source/net/ipv4/tcp_minisocks.c#L552">552</a> <b><i> *</i></b>
<a name="L553" href="source/net/ipv4/tcp_minisocks.c#L553">553</a> <b><i> * XXX (TFO) - The current impl contains a special check for ack</i></b>
<a name="L554" href="source/net/ipv4/tcp_minisocks.c#L554">554</a> <b><i> * validation and inside tcp_v4_reqsk_send_ack(). Can we do better?</i></b>
<a name="L555" href="source/net/ipv4/tcp_minisocks.c#L555">555</a> <b><i> *</i></b>
<a name="L556" href="source/net/ipv4/tcp_minisocks.c#L556">556</a> <b><i> * We don't need to initialize tmp_opt.sack_ok as we don't use the results</i></b>
<a name="L557" href="source/net/ipv4/tcp_minisocks.c#L557">557</a> <b><i> */</i></b>
<a name="L558" href="source/net/ipv4/tcp_minisocks.c#L558">558</a> 
<a name="L559" href="source/net/ipv4/tcp_minisocks.c#L559">559</a> struct <a href="ident?i=sock">sock</a> *<a href="ident?i=tcp_check_req">tcp_check_req</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
<a name="L560" href="source/net/ipv4/tcp_minisocks.c#L560">560</a>                            struct <a href="ident?i=request_sock">request_sock</a> *<a href="ident?i=req">req</a>,
<a name="L561" href="source/net/ipv4/tcp_minisocks.c#L561">561</a>                            <a href="ident?i=bool">bool</a> fastopen)
<a name="L562" href="source/net/ipv4/tcp_minisocks.c#L562">562</a> {
<a name="L563" href="source/net/ipv4/tcp_minisocks.c#L563">563</a>         struct <a href="ident?i=tcp_options_received">tcp_options_received</a> tmp_opt;
<a name="L564" href="source/net/ipv4/tcp_minisocks.c#L564">564</a>         struct <a href="ident?i=sock">sock</a> *<a href="ident?i=child">child</a>;
<a name="L565" href="source/net/ipv4/tcp_minisocks.c#L565">565</a>         const struct <a href="ident?i=tcphdr">tcphdr</a> *<a href="ident?i=th">th</a> = <a href="ident?i=tcp_hdr">tcp_hdr</a>(<a href="ident?i=skb">skb</a>);
<a name="L566" href="source/net/ipv4/tcp_minisocks.c#L566">566</a>         <a href="ident?i=__be32">__be32</a> flg = <a href="ident?i=tcp_flag_word">tcp_flag_word</a>(<a href="ident?i=th">th</a>) &amp; (TCP_FLAG_RST|TCP_FLAG_SYN|TCP_FLAG_ACK);
<a name="L567" href="source/net/ipv4/tcp_minisocks.c#L567">567</a>         <a href="ident?i=bool">bool</a> paws_reject = <a href="ident?i=false">false</a>;
<a name="L568" href="source/net/ipv4/tcp_minisocks.c#L568">568</a> 
<a name="L569" href="source/net/ipv4/tcp_minisocks.c#L569">569</a>         <a href="ident?i=BUG_ON">BUG_ON</a>(fastopen == (sk-&gt;<a href="ident?i=sk_state">sk_state</a> == TCP_LISTEN));
<a name="L570" href="source/net/ipv4/tcp_minisocks.c#L570">570</a> 
<a name="L571" href="source/net/ipv4/tcp_minisocks.c#L571">571</a>         tmp_opt.saw_tstamp = 0;
<a name="L572" href="source/net/ipv4/tcp_minisocks.c#L572">572</a>         if (<a href="ident?i=th">th</a>-&gt;doff &gt; (sizeof(struct <a href="ident?i=tcphdr">tcphdr</a>)&gt;&gt;2)) {
<a name="L573" href="source/net/ipv4/tcp_minisocks.c#L573">573</a>                 <a href="ident?i=tcp_parse_options">tcp_parse_options</a>(<a href="ident?i=skb">skb</a>, &amp;tmp_opt, 0, <a href="ident?i=NULL">NULL</a>);
<a name="L574" href="source/net/ipv4/tcp_minisocks.c#L574">574</a> 
<a name="L575" href="source/net/ipv4/tcp_minisocks.c#L575">575</a>                 if (tmp_opt.saw_tstamp) {
<a name="L576" href="source/net/ipv4/tcp_minisocks.c#L576">576</a>                         tmp_opt.ts_recent = <a href="ident?i=req">req</a>-&gt;ts_recent;
<a name="L577" href="source/net/ipv4/tcp_minisocks.c#L577">577</a>                         <b><i>/* We do not store true stamp, but it is not required,</i></b>
<a name="L578" href="source/net/ipv4/tcp_minisocks.c#L578">578</a> <b><i>                         * it can be estimated (approximately)</i></b>
<a name="L579" href="source/net/ipv4/tcp_minisocks.c#L579">579</a> <b><i>                         * from another data.</i></b>
<a name="L580" href="source/net/ipv4/tcp_minisocks.c#L580">580</a> <b><i>                         */</i></b>
<a name="L581" href="source/net/ipv4/tcp_minisocks.c#L581">581</a>                         tmp_opt.ts_recent_stamp = <a href="ident?i=get_seconds">get_seconds</a>() - ((<a href="ident?i=TCP_TIMEOUT_INIT">TCP_TIMEOUT_INIT</a>/<a href="ident?i=HZ">HZ</a>)&lt;&lt;<a href="ident?i=req">req</a>-&gt;num_timeout);
<a name="L582" href="source/net/ipv4/tcp_minisocks.c#L582">582</a>                         paws_reject = <a href="ident?i=tcp_paws_reject">tcp_paws_reject</a>(&amp;tmp_opt, <a href="ident?i=th">th</a>-&gt;rst);
<a name="L583" href="source/net/ipv4/tcp_minisocks.c#L583">583</a>                 }
<a name="L584" href="source/net/ipv4/tcp_minisocks.c#L584">584</a>         }
<a name="L585" href="source/net/ipv4/tcp_minisocks.c#L585">585</a> 
<a name="L586" href="source/net/ipv4/tcp_minisocks.c#L586">586</a>         <b><i>/* Check for pure retransmitted SYN. */</i></b>
<a name="L587" href="source/net/ipv4/tcp_minisocks.c#L587">587</a>         if (<a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=seq">seq</a> == <a href="ident?i=tcp_rsk">tcp_rsk</a>(<a href="ident?i=req">req</a>)-&gt;rcv_isn &amp;&amp;
<a name="L588" href="source/net/ipv4/tcp_minisocks.c#L588">588</a>             flg == TCP_FLAG_SYN &amp;&amp;
<a name="L589" href="source/net/ipv4/tcp_minisocks.c#L589">589</a>             !paws_reject) {
<a name="L590" href="source/net/ipv4/tcp_minisocks.c#L590">590</a>                 <b><i>/*</i></b>
<a name="L591" href="source/net/ipv4/tcp_minisocks.c#L591">591</a> <b><i>                 * RFC793 draws (Incorrectly! It was fixed in RFC1122)</i></b>
<a name="L592" href="source/net/ipv4/tcp_minisocks.c#L592">592</a> <b><i>                 * this case on figure 6 and figure 8, but formal</i></b>
<a name="L593" href="source/net/ipv4/tcp_minisocks.c#L593">593</a> <b><i>                 * protocol description says NOTHING.</i></b>
<a name="L594" href="source/net/ipv4/tcp_minisocks.c#L594">594</a> <b><i>                 * To be more exact, it says that we should send ACK,</i></b>
<a name="L595" href="source/net/ipv4/tcp_minisocks.c#L595">595</a> <b><i>                 * because this segment (at least, if it has no data)</i></b>
<a name="L596" href="source/net/ipv4/tcp_minisocks.c#L596">596</a> <b><i>                 * is out of window.</i></b>
<a name="L597" href="source/net/ipv4/tcp_minisocks.c#L597">597</a> <b><i>                 *</i></b>
<a name="L598" href="source/net/ipv4/tcp_minisocks.c#L598">598</a> <b><i>                 *  CONCLUSION: RFC793 (even with RFC1122) DOES NOT</i></b>
<a name="L599" href="source/net/ipv4/tcp_minisocks.c#L599">599</a> <b><i>                 *  describe SYN-RECV state. All the description</i></b>
<a name="L600" href="source/net/ipv4/tcp_minisocks.c#L600">600</a> <b><i>                 *  is wrong, we cannot believe to it and should</i></b>
<a name="L601" href="source/net/ipv4/tcp_minisocks.c#L601">601</a> <b><i>                 *  rely only on common sense and implementation</i></b>
<a name="L602" href="source/net/ipv4/tcp_minisocks.c#L602">602</a> <b><i>                 *  experience.</i></b>
<a name="L603" href="source/net/ipv4/tcp_minisocks.c#L603">603</a> <b><i>                 *</i></b>
<a name="L604" href="source/net/ipv4/tcp_minisocks.c#L604">604</a> <b><i>                 * Enforce "SYN-ACK" according to figure 8, figure 6</i></b>
<a name="L605" href="source/net/ipv4/tcp_minisocks.c#L605">605</a> <b><i>                 * of RFC793, fixed by RFC1122.</i></b>
<a name="L606" href="source/net/ipv4/tcp_minisocks.c#L606">606</a> <b><i>                 *</i></b>
<a name="L607" href="source/net/ipv4/tcp_minisocks.c#L607">607</a> <b><i>                 * Note that even if there is new data in the SYN packet</i></b>
<a name="L608" href="source/net/ipv4/tcp_minisocks.c#L608">608</a> <b><i>                 * they will be thrown away too.</i></b>
<a name="L609" href="source/net/ipv4/tcp_minisocks.c#L609">609</a> <b><i>                 *</i></b>
<a name="L610" href="source/net/ipv4/tcp_minisocks.c#L610">610</a> <b><i>                 * Reset timer after retransmitting SYNACK, similar to</i></b>
<a name="L611" href="source/net/ipv4/tcp_minisocks.c#L611">611</a> <b><i>                 * the idea of fast retransmit in recovery.</i></b>
<a name="L612" href="source/net/ipv4/tcp_minisocks.c#L612">612</a> <b><i>                 */</i></b>
<a name="L613" href="source/net/ipv4/tcp_minisocks.c#L613">613</a>                 if (!<a href="ident?i=tcp_oow_rate_limited">tcp_oow_rate_limited</a>(<a href="ident?i=sock_net">sock_net</a>(sk), <a href="ident?i=skb">skb</a>,
<a name="L614" href="source/net/ipv4/tcp_minisocks.c#L614">614</a>                                           LINUX_MIB_TCPACKSKIPPEDSYNRECV,
<a name="L615" href="source/net/ipv4/tcp_minisocks.c#L615">615</a>                                           &amp;<a href="ident?i=tcp_rsk">tcp_rsk</a>(<a href="ident?i=req">req</a>)-&gt;last_oow_ack_time) &amp;&amp;
<a name="L616" href="source/net/ipv4/tcp_minisocks.c#L616">616</a> 
<a name="L617" href="source/net/ipv4/tcp_minisocks.c#L617">617</a>                     !<a href="ident?i=inet_rtx_syn_ack">inet_rtx_syn_ack</a>(sk, <a href="ident?i=req">req</a>)) {
<a name="L618" href="source/net/ipv4/tcp_minisocks.c#L618">618</a>                         unsigned long expires = <a href="ident?i=jiffies">jiffies</a>;
<a name="L619" href="source/net/ipv4/tcp_minisocks.c#L619">619</a> 
<a name="L620" href="source/net/ipv4/tcp_minisocks.c#L620">620</a>                         expires += <a href="ident?i=min">min</a>(<a href="ident?i=TCP_TIMEOUT_INIT">TCP_TIMEOUT_INIT</a> &lt;&lt; <a href="ident?i=req">req</a>-&gt;num_timeout,
<a name="L621" href="source/net/ipv4/tcp_minisocks.c#L621">621</a>                                        <a href="ident?i=TCP_RTO_MAX">TCP_RTO_MAX</a>);
<a name="L622" href="source/net/ipv4/tcp_minisocks.c#L622">622</a>                         if (!fastopen)
<a name="L623" href="source/net/ipv4/tcp_minisocks.c#L623">623</a>                                 <a href="ident?i=mod_timer_pending">mod_timer_pending</a>(&amp;<a href="ident?i=req">req</a>-&gt;rsk_timer, expires);
<a name="L624" href="source/net/ipv4/tcp_minisocks.c#L624">624</a>                         else
<a name="L625" href="source/net/ipv4/tcp_minisocks.c#L625">625</a>                                 <a href="ident?i=req">req</a>-&gt;rsk_timer.expires = expires;
<a name="L626" href="source/net/ipv4/tcp_minisocks.c#L626">626</a>                 }
<a name="L627" href="source/net/ipv4/tcp_minisocks.c#L627">627</a>                 return <a href="ident?i=NULL">NULL</a>;
<a name="L628" href="source/net/ipv4/tcp_minisocks.c#L628">628</a>         }
<a name="L629" href="source/net/ipv4/tcp_minisocks.c#L629">629</a> 
<a name="L630" href="source/net/ipv4/tcp_minisocks.c#L630">630</a>         <b><i>/* Further reproduces section "SEGMENT ARRIVES"</i></b>
<a name="L631" href="source/net/ipv4/tcp_minisocks.c#L631">631</a> <b><i>           for state SYN-RECEIVED of RFC793.</i></b>
<a name="L632" href="source/net/ipv4/tcp_minisocks.c#L632">632</a> <b><i>           It is broken, however, it does not work only</i></b>
<a name="L633" href="source/net/ipv4/tcp_minisocks.c#L633">633</a> <b><i>           when SYNs are crossed.</i></b>
<a name="L634" href="source/net/ipv4/tcp_minisocks.c#L634">634</a> <b><i></i></b>
<a name="L635" href="source/net/ipv4/tcp_minisocks.c#L635">635</a> <b><i>           You would think that SYN crossing is impossible here, since</i></b>
<a name="L636" href="source/net/ipv4/tcp_minisocks.c#L636">636</a> <b><i>           we should have a SYN_SENT socket (from connect()) on our end,</i></b>
<a name="L637" href="source/net/ipv4/tcp_minisocks.c#L637">637</a> <b><i>           but this is not true if the crossed SYNs were sent to both</i></b>
<a name="L638" href="source/net/ipv4/tcp_minisocks.c#L638">638</a> <b><i>           ends by a malicious third party.  We must defend against this,</i></b>
<a name="L639" href="source/net/ipv4/tcp_minisocks.c#L639">639</a> <b><i>           and to do that we first verify the ACK (as per RFC793, page</i></b>
<a name="L640" href="source/net/ipv4/tcp_minisocks.c#L640">640</a> <b><i>           36) and reset if it is invalid.  Is this a true full defense?</i></b>
<a name="L641" href="source/net/ipv4/tcp_minisocks.c#L641">641</a> <b><i>           To convince ourselves, let us consider a way in which the ACK</i></b>
<a name="L642" href="source/net/ipv4/tcp_minisocks.c#L642">642</a> <b><i>           test can still pass in this 'malicious crossed SYNs' case.</i></b>
<a name="L643" href="source/net/ipv4/tcp_minisocks.c#L643">643</a> <b><i>           Malicious sender sends identical SYNs (and thus identical sequence</i></b>
<a name="L644" href="source/net/ipv4/tcp_minisocks.c#L644">644</a> <b><i>           numbers) to both A and B:</i></b>
<a name="L645" href="source/net/ipv4/tcp_minisocks.c#L645">645</a> <b><i></i></b>
<a name="L646" href="source/net/ipv4/tcp_minisocks.c#L646">646</a> <b><i>                A: gets SYN, seq=7</i></b>
<a name="L647" href="source/net/ipv4/tcp_minisocks.c#L647">647</a> <b><i>                B: gets SYN, seq=7</i></b>
<a name="L648" href="source/net/ipv4/tcp_minisocks.c#L648">648</a> <b><i></i></b>
<a name="L649" href="source/net/ipv4/tcp_minisocks.c#L649">649</a> <b><i>           By our good fortune, both A and B select the same initial</i></b>
<a name="L650" href="source/net/ipv4/tcp_minisocks.c#L650">650</a> <b><i>           send sequence number of seven :-)</i></b>
<a name="L651" href="source/net/ipv4/tcp_minisocks.c#L651">651</a> <b><i></i></b>
<a name="L652" href="source/net/ipv4/tcp_minisocks.c#L652">652</a> <b><i>                A: sends SYN|ACK, seq=7, ack_seq=8</i></b>
<a name="L653" href="source/net/ipv4/tcp_minisocks.c#L653">653</a> <b><i>                B: sends SYN|ACK, seq=7, ack_seq=8</i></b>
<a name="L654" href="source/net/ipv4/tcp_minisocks.c#L654">654</a> <b><i></i></b>
<a name="L655" href="source/net/ipv4/tcp_minisocks.c#L655">655</a> <b><i>           So we are now A eating this SYN|ACK, ACK test passes.  So</i></b>
<a name="L656" href="source/net/ipv4/tcp_minisocks.c#L656">656</a> <b><i>           does sequence test, SYN is truncated, and thus we consider</i></b>
<a name="L657" href="source/net/ipv4/tcp_minisocks.c#L657">657</a> <b><i>           it a bare ACK.</i></b>
<a name="L658" href="source/net/ipv4/tcp_minisocks.c#L658">658</a> <b><i></i></b>
<a name="L659" href="source/net/ipv4/tcp_minisocks.c#L659">659</a> <b><i>           If icsk-&gt;icsk_accept_queue.rskq_defer_accept, we silently drop this</i></b>
<a name="L660" href="source/net/ipv4/tcp_minisocks.c#L660">660</a> <b><i>           bare ACK.  Otherwise, we create an established connection.  Both</i></b>
<a name="L661" href="source/net/ipv4/tcp_minisocks.c#L661">661</a> <b><i>           ends (listening sockets) accept the new incoming connection and try</i></b>
<a name="L662" href="source/net/ipv4/tcp_minisocks.c#L662">662</a> <b><i>           to talk to each other. 8-)</i></b>
<a name="L663" href="source/net/ipv4/tcp_minisocks.c#L663">663</a> <b><i></i></b>
<a name="L664" href="source/net/ipv4/tcp_minisocks.c#L664">664</a> <b><i>           Note: This case is both harmless, and rare.  Possibility is about the</i></b>
<a name="L665" href="source/net/ipv4/tcp_minisocks.c#L665">665</a> <b><i>           same as us discovering intelligent life on another plant tomorrow.</i></b>
<a name="L666" href="source/net/ipv4/tcp_minisocks.c#L666">666</a> <b><i></i></b>
<a name="L667" href="source/net/ipv4/tcp_minisocks.c#L667">667</a> <b><i>           But generally, we should (RFC lies!) to accept ACK</i></b>
<a name="L668" href="source/net/ipv4/tcp_minisocks.c#L668">668</a> <b><i>           from SYNACK both here and in tcp_rcv_state_process().</i></b>
<a name="L669" href="source/net/ipv4/tcp_minisocks.c#L669">669</a> <b><i>           tcp_rcv_state_process() does not, hence, we do not too.</i></b>
<a name="L670" href="source/net/ipv4/tcp_minisocks.c#L670">670</a> <b><i></i></b>
<a name="L671" href="source/net/ipv4/tcp_minisocks.c#L671">671</a> <b><i>           Note that the case is absolutely generic:</i></b>
<a name="L672" href="source/net/ipv4/tcp_minisocks.c#L672">672</a> <b><i>           we cannot optimize anything here without</i></b>
<a name="L673" href="source/net/ipv4/tcp_minisocks.c#L673">673</a> <b><i>           violating protocol. All the checks must be made</i></b>
<a name="L674" href="source/net/ipv4/tcp_minisocks.c#L674">674</a> <b><i>           before attempt to create socket.</i></b>
<a name="L675" href="source/net/ipv4/tcp_minisocks.c#L675">675</a> <b><i>         */</i></b>
<a name="L676" href="source/net/ipv4/tcp_minisocks.c#L676">676</a> 
<a name="L677" href="source/net/ipv4/tcp_minisocks.c#L677">677</a>         <b><i>/* RFC793 page 36: "If the connection is in any non-synchronized state ...</i></b>
<a name="L678" href="source/net/ipv4/tcp_minisocks.c#L678">678</a> <b><i>         *                  and the incoming segment acknowledges something not yet</i></b>
<a name="L679" href="source/net/ipv4/tcp_minisocks.c#L679">679</a> <b><i>         *                  sent (the segment carries an unacceptable ACK) ...</i></b>
<a name="L680" href="source/net/ipv4/tcp_minisocks.c#L680">680</a> <b><i>         *                  a reset is sent."</i></b>
<a name="L681" href="source/net/ipv4/tcp_minisocks.c#L681">681</a> <b><i>         *</i></b>
<a name="L682" href="source/net/ipv4/tcp_minisocks.c#L682">682</a> <b><i>         * Invalid ACK: reset will be sent by listening socket.</i></b>
<a name="L683" href="source/net/ipv4/tcp_minisocks.c#L683">683</a> <b><i>         * Note that the ACK validity check for a Fast Open socket is done</i></b>
<a name="L684" href="source/net/ipv4/tcp_minisocks.c#L684">684</a> <b><i>         * elsewhere and is checked directly against the child socket rather</i></b>
<a name="L685" href="source/net/ipv4/tcp_minisocks.c#L685">685</a> <b><i>         * than req because user data may have been sent out.</i></b>
<a name="L686" href="source/net/ipv4/tcp_minisocks.c#L686">686</a> <b><i>         */</i></b>
<a name="L687" href="source/net/ipv4/tcp_minisocks.c#L687">687</a>         if ((flg &amp; TCP_FLAG_ACK) &amp;&amp; !fastopen &amp;&amp;
<a name="L688" href="source/net/ipv4/tcp_minisocks.c#L688">688</a>             (<a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;ack_seq !=
<a name="L689" href="source/net/ipv4/tcp_minisocks.c#L689">689</a>              <a href="ident?i=tcp_rsk">tcp_rsk</a>(<a href="ident?i=req">req</a>)-&gt;snt_isn + 1))
<a name="L690" href="source/net/ipv4/tcp_minisocks.c#L690">690</a>                 return sk;
<a name="L691" href="source/net/ipv4/tcp_minisocks.c#L691">691</a> 
<a name="L692" href="source/net/ipv4/tcp_minisocks.c#L692">692</a>         <b><i>/* Also, it would be not so bad idea to check rcv_tsecr, which</i></b>
<a name="L693" href="source/net/ipv4/tcp_minisocks.c#L693">693</a> <b><i>         * is essentially ACK extension and too early or too late values</i></b>
<a name="L694" href="source/net/ipv4/tcp_minisocks.c#L694">694</a> <b><i>         * should cause reset in unsynchronized states.</i></b>
<a name="L695" href="source/net/ipv4/tcp_minisocks.c#L695">695</a> <b><i>         */</i></b>
<a name="L696" href="source/net/ipv4/tcp_minisocks.c#L696">696</a> 
<a name="L697" href="source/net/ipv4/tcp_minisocks.c#L697">697</a>         <b><i>/* RFC793: "first check sequence number". */</i></b>
<a name="L698" href="source/net/ipv4/tcp_minisocks.c#L698">698</a> 
<a name="L699" href="source/net/ipv4/tcp_minisocks.c#L699">699</a>         if (paws_reject || !<a href="ident?i=tcp_in_window">tcp_in_window</a>(<a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=seq">seq</a>, <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;end_seq,
<a name="L700" href="source/net/ipv4/tcp_minisocks.c#L700">700</a>                                           <a href="ident?i=tcp_rsk">tcp_rsk</a>(<a href="ident?i=req">req</a>)-&gt;rcv_nxt, <a href="ident?i=tcp_rsk">tcp_rsk</a>(<a href="ident?i=req">req</a>)-&gt;rcv_nxt + <a href="ident?i=req">req</a>-&gt;rcv_wnd)) {
<a name="L701" href="source/net/ipv4/tcp_minisocks.c#L701">701</a>                 <b><i>/* Out of window: send ACK and drop. */</i></b>
<a name="L702" href="source/net/ipv4/tcp_minisocks.c#L702">702</a>                 if (!(flg &amp; TCP_FLAG_RST))
<a name="L703" href="source/net/ipv4/tcp_minisocks.c#L703">703</a>                         <a href="ident?i=req">req</a>-&gt;rsk_ops-&gt;<a href="ident?i=send_ack">send_ack</a>(sk, <a href="ident?i=skb">skb</a>, <a href="ident?i=req">req</a>);
<a name="L704" href="source/net/ipv4/tcp_minisocks.c#L704">704</a>                 if (paws_reject)
<a name="L705" href="source/net/ipv4/tcp_minisocks.c#L705">705</a>                         <a href="ident?i=NET_INC_STATS_BH">NET_INC_STATS_BH</a>(<a href="ident?i=sock_net">sock_net</a>(sk), LINUX_MIB_PAWSESTABREJECTED);
<a name="L706" href="source/net/ipv4/tcp_minisocks.c#L706">706</a>                 return <a href="ident?i=NULL">NULL</a>;
<a name="L707" href="source/net/ipv4/tcp_minisocks.c#L707">707</a>         }
<a name="L708" href="source/net/ipv4/tcp_minisocks.c#L708">708</a> 
<a name="L709" href="source/net/ipv4/tcp_minisocks.c#L709">709</a>         <b><i>/* In sequence, PAWS is OK. */</i></b>
<a name="L710" href="source/net/ipv4/tcp_minisocks.c#L710">710</a> 
<a name="L711" href="source/net/ipv4/tcp_minisocks.c#L711">711</a>         if (tmp_opt.saw_tstamp &amp;&amp; !<a href="ident?i=after">after</a>(<a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=seq">seq</a>, <a href="ident?i=tcp_rsk">tcp_rsk</a>(<a href="ident?i=req">req</a>)-&gt;rcv_nxt))
<a name="L712" href="source/net/ipv4/tcp_minisocks.c#L712">712</a>                 <a href="ident?i=req">req</a>-&gt;ts_recent = tmp_opt.rcv_tsval;
<a name="L713" href="source/net/ipv4/tcp_minisocks.c#L713">713</a> 
<a name="L714" href="source/net/ipv4/tcp_minisocks.c#L714">714</a>         if (<a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=seq">seq</a> == <a href="ident?i=tcp_rsk">tcp_rsk</a>(<a href="ident?i=req">req</a>)-&gt;rcv_isn) {
<a name="L715" href="source/net/ipv4/tcp_minisocks.c#L715">715</a>                 <b><i>/* Truncate SYN, it is out of window starting</i></b>
<a name="L716" href="source/net/ipv4/tcp_minisocks.c#L716">716</a> <b><i>                   at tcp_rsk(req)-&gt;rcv_isn + 1. */</i></b>
<a name="L717" href="source/net/ipv4/tcp_minisocks.c#L717">717</a>                 flg &amp;= ~TCP_FLAG_SYN;
<a name="L718" href="source/net/ipv4/tcp_minisocks.c#L718">718</a>         }
<a name="L719" href="source/net/ipv4/tcp_minisocks.c#L719">719</a> 
<a name="L720" href="source/net/ipv4/tcp_minisocks.c#L720">720</a>         <b><i>/* RFC793: "second check the RST bit" and</i></b>
<a name="L721" href="source/net/ipv4/tcp_minisocks.c#L721">721</a> <b><i>         *         "fourth, check the SYN bit"</i></b>
<a name="L722" href="source/net/ipv4/tcp_minisocks.c#L722">722</a> <b><i>         */</i></b>
<a name="L723" href="source/net/ipv4/tcp_minisocks.c#L723">723</a>         if (flg &amp; (TCP_FLAG_RST|TCP_FLAG_SYN)) {
<a name="L724" href="source/net/ipv4/tcp_minisocks.c#L724">724</a>                 <a href="ident?i=TCP_INC_STATS_BH">TCP_INC_STATS_BH</a>(<a href="ident?i=sock_net">sock_net</a>(sk), TCP_MIB_ATTEMPTFAILS);
<a name="L725" href="source/net/ipv4/tcp_minisocks.c#L725">725</a>                 goto embryonic_reset;
<a name="L726" href="source/net/ipv4/tcp_minisocks.c#L726">726</a>         }
<a name="L727" href="source/net/ipv4/tcp_minisocks.c#L727">727</a> 
<a name="L728" href="source/net/ipv4/tcp_minisocks.c#L728">728</a>         <b><i>/* ACK sequence verified above, just make sure ACK is</i></b>
<a name="L729" href="source/net/ipv4/tcp_minisocks.c#L729">729</a> <b><i>         * set.  If ACK not set, just silently drop the packet.</i></b>
<a name="L730" href="source/net/ipv4/tcp_minisocks.c#L730">730</a> <b><i>         *</i></b>
<a name="L731" href="source/net/ipv4/tcp_minisocks.c#L731">731</a> <b><i>         * XXX (TFO) - if we ever allow "data after SYN", the</i></b>
<a name="L732" href="source/net/ipv4/tcp_minisocks.c#L732">732</a> <b><i>         * following check needs to be removed.</i></b>
<a name="L733" href="source/net/ipv4/tcp_minisocks.c#L733">733</a> <b><i>         */</i></b>
<a name="L734" href="source/net/ipv4/tcp_minisocks.c#L734">734</a>         if (!(flg &amp; TCP_FLAG_ACK))
<a name="L735" href="source/net/ipv4/tcp_minisocks.c#L735">735</a>                 return <a href="ident?i=NULL">NULL</a>;
<a name="L736" href="source/net/ipv4/tcp_minisocks.c#L736">736</a> 
<a name="L737" href="source/net/ipv4/tcp_minisocks.c#L737">737</a>         <b><i>/* For Fast Open no more processing is needed (sk is the</i></b>
<a name="L738" href="source/net/ipv4/tcp_minisocks.c#L738">738</a> <b><i>         * child socket).</i></b>
<a name="L739" href="source/net/ipv4/tcp_minisocks.c#L739">739</a> <b><i>         */</i></b>
<a name="L740" href="source/net/ipv4/tcp_minisocks.c#L740">740</a>         if (fastopen)
<a name="L741" href="source/net/ipv4/tcp_minisocks.c#L741">741</a>                 return sk;
<a name="L742" href="source/net/ipv4/tcp_minisocks.c#L742">742</a> 
<a name="L743" href="source/net/ipv4/tcp_minisocks.c#L743">743</a>         <b><i>/* While TCP_DEFER_ACCEPT is active, drop bare ACK. */</i></b>
<a name="L744" href="source/net/ipv4/tcp_minisocks.c#L744">744</a>         if (<a href="ident?i=req">req</a>-&gt;num_timeout &lt; <a href="ident?i=inet_csk">inet_csk</a>(sk)-&gt;icsk_accept_queue.rskq_defer_accept &amp;&amp;
<a name="L745" href="source/net/ipv4/tcp_minisocks.c#L745">745</a>             <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;end_seq == <a href="ident?i=tcp_rsk">tcp_rsk</a>(<a href="ident?i=req">req</a>)-&gt;rcv_isn + 1) {
<a name="L746" href="source/net/ipv4/tcp_minisocks.c#L746">746</a>                 <a href="ident?i=inet_rsk">inet_rsk</a>(<a href="ident?i=req">req</a>)-&gt;acked = 1;
<a name="L747" href="source/net/ipv4/tcp_minisocks.c#L747">747</a>                 <a href="ident?i=NET_INC_STATS_BH">NET_INC_STATS_BH</a>(<a href="ident?i=sock_net">sock_net</a>(sk), LINUX_MIB_TCPDEFERACCEPTDROP);
<a name="L748" href="source/net/ipv4/tcp_minisocks.c#L748">748</a>                 return <a href="ident?i=NULL">NULL</a>;
<a name="L749" href="source/net/ipv4/tcp_minisocks.c#L749">749</a>         }
<a name="L750" href="source/net/ipv4/tcp_minisocks.c#L750">750</a> 
<a name="L751" href="source/net/ipv4/tcp_minisocks.c#L751">751</a>         <b><i>/* OK, ACK is valid, create big socket and</i></b>
<a name="L752" href="source/net/ipv4/tcp_minisocks.c#L752">752</a> <b><i>         * feed this segment to it. It will repeat all</i></b>
<a name="L753" href="source/net/ipv4/tcp_minisocks.c#L753">753</a> <b><i>         * the tests. THIS SEGMENT MUST MOVE SOCKET TO</i></b>
<a name="L754" href="source/net/ipv4/tcp_minisocks.c#L754">754</a> <b><i>         * ESTABLISHED STATE. If it will be dropped after</i></b>
<a name="L755" href="source/net/ipv4/tcp_minisocks.c#L755">755</a> <b><i>         * socket is created, wait for troubles.</i></b>
<a name="L756" href="source/net/ipv4/tcp_minisocks.c#L756">756</a> <b><i>         */</i></b>
<a name="L757" href="source/net/ipv4/tcp_minisocks.c#L757">757</a>         <a href="ident?i=child">child</a> = <a href="ident?i=inet_csk">inet_csk</a>(sk)-&gt;icsk_af_ops-&gt;syn_recv_sock(sk, <a href="ident?i=skb">skb</a>, <a href="ident?i=req">req</a>, <a href="ident?i=NULL">NULL</a>);
<a name="L758" href="source/net/ipv4/tcp_minisocks.c#L758">758</a>         if (!<a href="ident?i=child">child</a>)
<a name="L759" href="source/net/ipv4/tcp_minisocks.c#L759">759</a>                 goto listen_overflow;
<a name="L760" href="source/net/ipv4/tcp_minisocks.c#L760">760</a> 
<a name="L761" href="source/net/ipv4/tcp_minisocks.c#L761">761</a>         <a href="ident?i=inet_csk_reqsk_queue_drop">inet_csk_reqsk_queue_drop</a>(sk, <a href="ident?i=req">req</a>);
<a name="L762" href="source/net/ipv4/tcp_minisocks.c#L762">762</a>         <a href="ident?i=inet_csk_reqsk_queue_add">inet_csk_reqsk_queue_add</a>(sk, <a href="ident?i=req">req</a>, <a href="ident?i=child">child</a>);
<a name="L763" href="source/net/ipv4/tcp_minisocks.c#L763">763</a>         <b><i>/* Warning: caller must not call reqsk_put(req);</i></b>
<a name="L764" href="source/net/ipv4/tcp_minisocks.c#L764">764</a> <b><i>         * child stole last reference on it.</i></b>
<a name="L765" href="source/net/ipv4/tcp_minisocks.c#L765">765</a> <b><i>         */</i></b>
<a name="L766" href="source/net/ipv4/tcp_minisocks.c#L766">766</a>         return <a href="ident?i=child">child</a>;
<a name="L767" href="source/net/ipv4/tcp_minisocks.c#L767">767</a> 
<a name="L768" href="source/net/ipv4/tcp_minisocks.c#L768">768</a> listen_overflow:
<a name="L769" href="source/net/ipv4/tcp_minisocks.c#L769">769</a>         if (!<a href="ident?i=sysctl_tcp_abort_on_overflow">sysctl_tcp_abort_on_overflow</a>) {
<a name="L770" href="source/net/ipv4/tcp_minisocks.c#L770">770</a>                 <a href="ident?i=inet_rsk">inet_rsk</a>(<a href="ident?i=req">req</a>)-&gt;acked = 1;
<a name="L771" href="source/net/ipv4/tcp_minisocks.c#L771">771</a>                 return <a href="ident?i=NULL">NULL</a>;
<a name="L772" href="source/net/ipv4/tcp_minisocks.c#L772">772</a>         }
<a name="L773" href="source/net/ipv4/tcp_minisocks.c#L773">773</a> 
<a name="L774" href="source/net/ipv4/tcp_minisocks.c#L774">774</a> embryonic_reset:
<a name="L775" href="source/net/ipv4/tcp_minisocks.c#L775">775</a>         if (!(flg &amp; TCP_FLAG_RST)) {
<a name="L776" href="source/net/ipv4/tcp_minisocks.c#L776">776</a>                 <b><i>/* Received a bad SYN pkt - for TFO We try not to reset</i></b>
<a name="L777" href="source/net/ipv4/tcp_minisocks.c#L777">777</a> <b><i>                 * the local connection unless it's really necessary to</i></b>
<a name="L778" href="source/net/ipv4/tcp_minisocks.c#L778">778</a> <b><i>                 * avoid becoming vulnerable to outside attack aiming at</i></b>
<a name="L779" href="source/net/ipv4/tcp_minisocks.c#L779">779</a> <b><i>                 * resetting legit local connections.</i></b>
<a name="L780" href="source/net/ipv4/tcp_minisocks.c#L780">780</a> <b><i>                 */</i></b>
<a name="L781" href="source/net/ipv4/tcp_minisocks.c#L781">781</a>                 <a href="ident?i=req">req</a>-&gt;rsk_ops-&gt;<a href="ident?i=send_reset">send_reset</a>(sk, <a href="ident?i=skb">skb</a>);
<a name="L782" href="source/net/ipv4/tcp_minisocks.c#L782">782</a>         } else if (fastopen) { <b><i>/* received a valid RST pkt */</i></b>
<a name="L783" href="source/net/ipv4/tcp_minisocks.c#L783">783</a>                 <a href="ident?i=reqsk_fastopen_remove">reqsk_fastopen_remove</a>(sk, <a href="ident?i=req">req</a>, <a href="ident?i=true">true</a>);
<a name="L784" href="source/net/ipv4/tcp_minisocks.c#L784">784</a>                 <a href="ident?i=tcp_reset">tcp_reset</a>(sk);
<a name="L785" href="source/net/ipv4/tcp_minisocks.c#L785">785</a>         }
<a name="L786" href="source/net/ipv4/tcp_minisocks.c#L786">786</a>         if (!fastopen) {
<a name="L787" href="source/net/ipv4/tcp_minisocks.c#L787">787</a>                 <a href="ident?i=inet_csk_reqsk_queue_drop">inet_csk_reqsk_queue_drop</a>(sk, <a href="ident?i=req">req</a>);
<a name="L788" href="source/net/ipv4/tcp_minisocks.c#L788">788</a>                 <a href="ident?i=NET_INC_STATS_BH">NET_INC_STATS_BH</a>(<a href="ident?i=sock_net">sock_net</a>(sk), LINUX_MIB_EMBRYONICRSTS);
<a name="L789" href="source/net/ipv4/tcp_minisocks.c#L789">789</a>         }
<a name="L790" href="source/net/ipv4/tcp_minisocks.c#L790">790</a>         return <a href="ident?i=NULL">NULL</a>;
<a name="L791" href="source/net/ipv4/tcp_minisocks.c#L791">791</a> }
<a name="L792" href="source/net/ipv4/tcp_minisocks.c#L792">792</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=tcp_check_req">tcp_check_req</a>);
<a name="L793" href="source/net/ipv4/tcp_minisocks.c#L793">793</a> 
<a name="L794" href="source/net/ipv4/tcp_minisocks.c#L794">794</a> <b><i>/*</i></b>
<a name="L795" href="source/net/ipv4/tcp_minisocks.c#L795">795</a> <b><i> * Queue segment on the new socket if the new socket is active,</i></b>
<a name="L796" href="source/net/ipv4/tcp_minisocks.c#L796">796</a> <b><i> * otherwise we just shortcircuit this and continue with</i></b>
<a name="L797" href="source/net/ipv4/tcp_minisocks.c#L797">797</a> <b><i> * the new socket.</i></b>
<a name="L798" href="source/net/ipv4/tcp_minisocks.c#L798">798</a> <b><i> *</i></b>
<a name="L799" href="source/net/ipv4/tcp_minisocks.c#L799">799</a> <b><i> * For the vast majority of cases child-&gt;sk_state will be TCP_SYN_RECV</i></b>
<a name="L800" href="source/net/ipv4/tcp_minisocks.c#L800">800</a> <b><i> * when entering. But other states are possible due to a race condition</i></b>
<a name="L801" href="source/net/ipv4/tcp_minisocks.c#L801">801</a> <b><i> * where after __inet_lookup_established() fails but before the listener</i></b>
<a name="L802" href="source/net/ipv4/tcp_minisocks.c#L802">802</a> <b><i> * locked is obtained, other packets cause the same connection to</i></b>
<a name="L803" href="source/net/ipv4/tcp_minisocks.c#L803">803</a> <b><i> * be created.</i></b>
<a name="L804" href="source/net/ipv4/tcp_minisocks.c#L804">804</a> <b><i> */</i></b>
<a name="L805" href="source/net/ipv4/tcp_minisocks.c#L805">805</a> 
<a name="L806" href="source/net/ipv4/tcp_minisocks.c#L806">806</a> int <a href="ident?i=tcp_child_process">tcp_child_process</a>(struct <a href="ident?i=sock">sock</a> *<a href="ident?i=parent">parent</a>, struct <a href="ident?i=sock">sock</a> *<a href="ident?i=child">child</a>,
<a name="L807" href="source/net/ipv4/tcp_minisocks.c#L807">807</a>                       struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L808" href="source/net/ipv4/tcp_minisocks.c#L808">808</a> {
<a name="L809" href="source/net/ipv4/tcp_minisocks.c#L809">809</a>         int <a href="ident?i=ret">ret</a> = 0;
<a name="L810" href="source/net/ipv4/tcp_minisocks.c#L810">810</a>         int <a href="ident?i=state">state</a> = <a href="ident?i=child">child</a>-&gt;<a href="ident?i=sk_state">sk_state</a>;
<a name="L811" href="source/net/ipv4/tcp_minisocks.c#L811">811</a> 
<a name="L812" href="source/net/ipv4/tcp_minisocks.c#L812">812</a>         if (!<a href="ident?i=sock_owned_by_user">sock_owned_by_user</a>(<a href="ident?i=child">child</a>)) {
<a name="L813" href="source/net/ipv4/tcp_minisocks.c#L813">813</a>                 <a href="ident?i=ret">ret</a> = <a href="ident?i=tcp_rcv_state_process">tcp_rcv_state_process</a>(<a href="ident?i=child">child</a>, <a href="ident?i=skb">skb</a>, <a href="ident?i=tcp_hdr">tcp_hdr</a>(<a href="ident?i=skb">skb</a>),
<a name="L814" href="source/net/ipv4/tcp_minisocks.c#L814">814</a>                                             <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a>);
<a name="L815" href="source/net/ipv4/tcp_minisocks.c#L815">815</a>                 <b><i>/* Wakeup parent, send SIGIO */</i></b>
<a name="L816" href="source/net/ipv4/tcp_minisocks.c#L816">816</a>                 if (<a href="ident?i=state">state</a> == TCP_SYN_RECV &amp;&amp; <a href="ident?i=child">child</a>-&gt;<a href="ident?i=sk_state">sk_state</a> != <a href="ident?i=state">state</a>)
<a name="L817" href="source/net/ipv4/tcp_minisocks.c#L817">817</a>                         <a href="ident?i=parent">parent</a>-&gt;sk_data_ready(<a href="ident?i=parent">parent</a>);
<a name="L818" href="source/net/ipv4/tcp_minisocks.c#L818">818</a>         } else {
<a name="L819" href="source/net/ipv4/tcp_minisocks.c#L819">819</a>                 <b><i>/* Alas, it is possible again, because we do lookup</i></b>
<a name="L820" href="source/net/ipv4/tcp_minisocks.c#L820">820</a> <b><i>                 * in main socket hash table and lock on listening</i></b>
<a name="L821" href="source/net/ipv4/tcp_minisocks.c#L821">821</a> <b><i>                 * socket does not protect us more.</i></b>
<a name="L822" href="source/net/ipv4/tcp_minisocks.c#L822">822</a> <b><i>                 */</i></b>
<a name="L823" href="source/net/ipv4/tcp_minisocks.c#L823">823</a>                 <a href="ident?i=__sk_add_backlog">__sk_add_backlog</a>(<a href="ident?i=child">child</a>, <a href="ident?i=skb">skb</a>);
<a name="L824" href="source/net/ipv4/tcp_minisocks.c#L824">824</a>         }
<a name="L825" href="source/net/ipv4/tcp_minisocks.c#L825">825</a> 
<a name="L826" href="source/net/ipv4/tcp_minisocks.c#L826">826</a>         <a href="ident?i=bh_unlock_sock">bh_unlock_sock</a>(<a href="ident?i=child">child</a>);
<a name="L827" href="source/net/ipv4/tcp_minisocks.c#L827">827</a>         <a href="ident?i=sock_put">sock_put</a>(<a href="ident?i=child">child</a>);
<a name="L828" href="source/net/ipv4/tcp_minisocks.c#L828">828</a>         return <a href="ident?i=ret">ret</a>;
<a name="L829" href="source/net/ipv4/tcp_minisocks.c#L829">829</a> }
<a name="L830" href="source/net/ipv4/tcp_minisocks.c#L830">830</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=tcp_child_process">tcp_child_process</a>);
<a name="L831" href="source/net/ipv4/tcp_minisocks.c#L831">831</a> </pre></div><p>
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
