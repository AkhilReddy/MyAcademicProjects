<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title>Linux/net/ipv4/tcp_output.c - Linux Cross Reference - Free Electrons</title>
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
		 &nbsp;&bull;&nbsp;<b><i>source navigation</i></b> &nbsp;&bull;&nbsp;<a href="diff/net/ipv4/tcp_output.c">diff markup</a> &nbsp;&bull;&nbsp;<a href="ident">identifier search</a> &nbsp;&bull;&nbsp;<a href="search">freetext search</a> &nbsp;&bull;&nbsp;
		</p>
	</div>
</div>

<div id="topbar">
  
  <p>Version: &nbsp;<a href="source/net/ipv4/tcp_output.c?v=2.0.40">2.0.40</a>&nbsp;<a href="source/net/ipv4/tcp_output.c?v=2.2.26">2.2.26</a>&nbsp;<a href="source/net/ipv4/tcp_output.c?v=2.4.37">2.4.37</a>&nbsp;<a href="source/net/ipv4/tcp_output.c?v=3.5">3.5</a>&nbsp;<a href="source/net/ipv4/tcp_output.c?v=3.6">3.6</a>&nbsp;<a href="source/net/ipv4/tcp_output.c?v=3.7">3.7</a>&nbsp;<a href="source/net/ipv4/tcp_output.c?v=3.8">3.8</a>&nbsp;<a href="source/net/ipv4/tcp_output.c?v=3.9">3.9</a>&nbsp;<a href="source/net/ipv4/tcp_output.c?v=3.10">3.10</a>&nbsp;<a href="source/net/ipv4/tcp_output.c?v=3.11">3.11</a>&nbsp;<a href="source/net/ipv4/tcp_output.c?v=3.12">3.12</a>&nbsp;<a href="source/net/ipv4/tcp_output.c?v=3.13">3.13</a>&nbsp;<a href="source/net/ipv4/tcp_output.c?v=3.14">3.14</a>&nbsp;<a href="source/net/ipv4/tcp_output.c?v=3.15">3.15</a>&nbsp;<a href="source/net/ipv4/tcp_output.c?v=3.16">3.16</a>&nbsp;<a href="source/net/ipv4/tcp_output.c?v=3.17">3.17</a>&nbsp;<a href="source/net/ipv4/tcp_output.c?v=3.18">3.18</a>&nbsp;<a href="source/net/ipv4/tcp_output.c?v=3.19">3.19</a>&nbsp;<a href="source/net/ipv4/tcp_output.c?v=4.0">4.0</a>&nbsp;<b><i>4.1</i></b></p>
  
</div>

<h1><a href="source/">Linux</a>/<a href="source/net/">net</a>/<a href="source/net/ipv4/">ipv4</a>/<a href="source/net/ipv4/tcp_output.c">tcp_output.c</a></h1>
<div id="lxrcode"><pre>  <a name="L1" href="source/net/ipv4/tcp_output.c#L1">1</a> <b><i>/*</i></b>
  <a name="L2" href="source/net/ipv4/tcp_output.c#L2">2</a> <b><i> * INET         An implementation of the TCP/IP protocol suite for the LINUX</i></b>
  <a name="L3" href="source/net/ipv4/tcp_output.c#L3">3</a> <b><i> *              operating system.  INET is implemented using the  BSD Socket</i></b>
  <a name="L4" href="source/net/ipv4/tcp_output.c#L4">4</a> <b><i> *              interface as the means of communication with the user level.</i></b>
  <a name="L5" href="source/net/ipv4/tcp_output.c#L5">5</a> <b><i> *</i></b>
  <a name="L6" href="source/net/ipv4/tcp_output.c#L6">6</a> <b><i> *              Implementation of the Transmission Control Protocol(TCP).</i></b>
  <a name="L7" href="source/net/ipv4/tcp_output.c#L7">7</a> <b><i> *</i></b>
  <a name="L8" href="source/net/ipv4/tcp_output.c#L8">8</a> <b><i> * Authors:     Ross Biro</i></b>
  <a name="L9" href="source/net/ipv4/tcp_output.c#L9">9</a> <b><i> *              Fred N. van Kempen, &lt;waltje@uWalt.NL.Mugnet.ORG&gt;</i></b>
 <a name="L10" href="source/net/ipv4/tcp_output.c#L10">10</a> <b><i> *              Mark Evans, &lt;evansmp@uhura.aston.ac.uk&gt;</i></b>
 <a name="L11" href="source/net/ipv4/tcp_output.c#L11">11</a> <b><i> *              Corey Minyard &lt;wf-rch!minyard@relay.EU.net&gt;</i></b>
 <a name="L12" href="source/net/ipv4/tcp_output.c#L12">12</a> <b><i> *              Florian La Roche, &lt;flla@stud.uni-sb.de&gt;</i></b>
 <a name="L13" href="source/net/ipv4/tcp_output.c#L13">13</a> <b><i> *              Charles Hedrick, &lt;hedrick@klinzhai.rutgers.edu&gt;</i></b>
 <a name="L14" href="source/net/ipv4/tcp_output.c#L14">14</a> <b><i> *              Linus Torvalds, &lt;torvalds@cs.helsinki.fi&gt;</i></b>
 <a name="L15" href="source/net/ipv4/tcp_output.c#L15">15</a> <b><i> *              Alan Cox, &lt;gw4pts@gw4pts.ampr.org&gt;</i></b>
 <a name="L16" href="source/net/ipv4/tcp_output.c#L16">16</a> <b><i> *              Matthew Dillon, &lt;dillon@apollo.west.oic.com&gt;</i></b>
 <a name="L17" href="source/net/ipv4/tcp_output.c#L17">17</a> <b><i> *              Arnt Gulbrandsen, &lt;agulbra@nvg.unit.no&gt;</i></b>
 <a name="L18" href="source/net/ipv4/tcp_output.c#L18">18</a> <b><i> *              Jorge Cwik, &lt;jorge@laser.satlink.net&gt;</i></b>
 <a name="L19" href="source/net/ipv4/tcp_output.c#L19">19</a> <b><i> */</i></b>
 <a name="L20" href="source/net/ipv4/tcp_output.c#L20">20</a> 
 <a name="L21" href="source/net/ipv4/tcp_output.c#L21">21</a> <b><i>/*</i></b>
 <a name="L22" href="source/net/ipv4/tcp_output.c#L22">22</a> <b><i> * Changes:     Pedro Roque     :       Retransmit queue handled by TCP.</i></b>
 <a name="L23" href="source/net/ipv4/tcp_output.c#L23">23</a> <b><i> *                              :       Fragmentation on mtu decrease</i></b>
 <a name="L24" href="source/net/ipv4/tcp_output.c#L24">24</a> <b><i> *                              :       Segment collapse on retransmit</i></b>
 <a name="L25" href="source/net/ipv4/tcp_output.c#L25">25</a> <b><i> *                              :       AF independence</i></b>
 <a name="L26" href="source/net/ipv4/tcp_output.c#L26">26</a> <b><i> *</i></b>
 <a name="L27" href="source/net/ipv4/tcp_output.c#L27">27</a> <b><i> *              Linus Torvalds  :       send_delayed_ack</i></b>
 <a name="L28" href="source/net/ipv4/tcp_output.c#L28">28</a> <b><i> *              David S. Miller :       Charge memory using the right skb</i></b>
 <a name="L29" href="source/net/ipv4/tcp_output.c#L29">29</a> <b><i> *                                      during syn/ack processing.</i></b>
 <a name="L30" href="source/net/ipv4/tcp_output.c#L30">30</a> <b><i> *              David S. Miller :       Output engine completely rewritten.</i></b>
 <a name="L31" href="source/net/ipv4/tcp_output.c#L31">31</a> <b><i> *              Andrea Arcangeli:       SYNACK carry ts_recent in tsecr.</i></b>
 <a name="L32" href="source/net/ipv4/tcp_output.c#L32">32</a> <b><i> *              Cacophonix Gaul :       draft-minshall-nagle-01</i></b>
 <a name="L33" href="source/net/ipv4/tcp_output.c#L33">33</a> <b><i> *              J Hadi Salim    :       ECN support</i></b>
 <a name="L34" href="source/net/ipv4/tcp_output.c#L34">34</a> <b><i> *</i></b>
 <a name="L35" href="source/net/ipv4/tcp_output.c#L35">35</a> <b><i> */</i></b>
 <a name="L36" href="source/net/ipv4/tcp_output.c#L36">36</a> 
 <a name="L37" href="source/net/ipv4/tcp_output.c#L37">37</a> #define <a href="ident?i=pr_fmt">pr_fmt</a>(<a href="ident?i=fmt">fmt</a>) <i>"TCP: "</i> <a href="ident?i=fmt">fmt</a>
 <a name="L38" href="source/net/ipv4/tcp_output.c#L38">38</a> 
 <a name="L39" href="source/net/ipv4/tcp_output.c#L39">39</a> #include &lt;net/tcp.h&gt;
 <a name="L40" href="source/net/ipv4/tcp_output.c#L40">40</a> 
 <a name="L41" href="source/net/ipv4/tcp_output.c#L41">41</a> #include &lt;linux/compiler.h&gt;
 <a name="L42" href="source/net/ipv4/tcp_output.c#L42">42</a> #include &lt;linux/gfp.h&gt;
 <a name="L43" href="source/net/ipv4/tcp_output.c#L43">43</a> #include &lt;linux/module.h&gt;
 <a name="L44" href="source/net/ipv4/tcp_output.c#L44">44</a> 
 <a name="L45" href="source/net/ipv4/tcp_output.c#L45">45</a> <b><i>/* People can turn this off for buggy TCP's found in printers etc. */</i></b>
 <a name="L46" href="source/net/ipv4/tcp_output.c#L46">46</a> int <a href="ident?i=sysctl_tcp_retrans_collapse">sysctl_tcp_retrans_collapse</a> <a href="ident?i=__read_mostly">__read_mostly</a> = 1;
 <a name="L47" href="source/net/ipv4/tcp_output.c#L47">47</a> 
 <a name="L48" href="source/net/ipv4/tcp_output.c#L48">48</a> <b><i>/* People can turn this on to work with those rare, broken TCPs that</i></b>
 <a name="L49" href="source/net/ipv4/tcp_output.c#L49">49</a> <b><i> * interpret the window field as a signed quantity.</i></b>
 <a name="L50" href="source/net/ipv4/tcp_output.c#L50">50</a> <b><i> */</i></b>
 <a name="L51" href="source/net/ipv4/tcp_output.c#L51">51</a> int <a href="ident?i=sysctl_tcp_workaround_signed_windows">sysctl_tcp_workaround_signed_windows</a> <a href="ident?i=__read_mostly">__read_mostly</a> = 0;
 <a name="L52" href="source/net/ipv4/tcp_output.c#L52">52</a> 
 <a name="L53" href="source/net/ipv4/tcp_output.c#L53">53</a> <b><i>/* Default TSQ limit of two TSO segments */</i></b>
 <a name="L54" href="source/net/ipv4/tcp_output.c#L54">54</a> int <a href="ident?i=sysctl_tcp_limit_output_bytes">sysctl_tcp_limit_output_bytes</a> <a href="ident?i=__read_mostly">__read_mostly</a> = 131072;
 <a name="L55" href="source/net/ipv4/tcp_output.c#L55">55</a> 
 <a name="L56" href="source/net/ipv4/tcp_output.c#L56">56</a> <b><i>/* This limits the percentage of the congestion window which we</i></b>
 <a name="L57" href="source/net/ipv4/tcp_output.c#L57">57</a> <b><i> * will allow a single TSO frame to consume.  Building TSO frames</i></b>
 <a name="L58" href="source/net/ipv4/tcp_output.c#L58">58</a> <b><i> * which are too large can cause TCP streams to be bursty.</i></b>
 <a name="L59" href="source/net/ipv4/tcp_output.c#L59">59</a> <b><i> */</i></b>
 <a name="L60" href="source/net/ipv4/tcp_output.c#L60">60</a> int <a href="ident?i=sysctl_tcp_tso_win_divisor">sysctl_tcp_tso_win_divisor</a> <a href="ident?i=__read_mostly">__read_mostly</a> = 3;
 <a name="L61" href="source/net/ipv4/tcp_output.c#L61">61</a> 
 <a name="L62" href="source/net/ipv4/tcp_output.c#L62">62</a> <b><i>/* By default, RFC2861 behavior.  */</i></b>
 <a name="L63" href="source/net/ipv4/tcp_output.c#L63">63</a> int <a href="ident?i=sysctl_tcp_slow_start_after_idle">sysctl_tcp_slow_start_after_idle</a> <a href="ident?i=__read_mostly">__read_mostly</a> = 1;
 <a name="L64" href="source/net/ipv4/tcp_output.c#L64">64</a> 
 <a name="L65" href="source/net/ipv4/tcp_output.c#L65">65</a> unsigned int <a href="ident?i=sysctl_tcp_notsent_lowat">sysctl_tcp_notsent_lowat</a> <a href="ident?i=__read_mostly">__read_mostly</a> = <a href="ident?i=UINT_MAX">UINT_MAX</a>;
 <a name="L66" href="source/net/ipv4/tcp_output.c#L66">66</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=sysctl_tcp_notsent_lowat">sysctl_tcp_notsent_lowat</a>);
 <a name="L67" href="source/net/ipv4/tcp_output.c#L67">67</a> 
 <a name="L68" href="source/net/ipv4/tcp_output.c#L68">68</a> static <a href="ident?i=bool">bool</a> <a href="ident?i=tcp_write_xmit">tcp_write_xmit</a>(struct <a href="ident?i=sock">sock</a> *sk, unsigned int mss_now, int nonagle,
 <a name="L69" href="source/net/ipv4/tcp_output.c#L69">69</a>                            int push_one, <a href="ident?i=gfp_t">gfp_t</a> gfp);
 <a name="L70" href="source/net/ipv4/tcp_output.c#L70">70</a> 
 <a name="L71" href="source/net/ipv4/tcp_output.c#L71">71</a> <b><i>/* Account for new data that has been sent to the network. */</i></b>
 <a name="L72" href="source/net/ipv4/tcp_output.c#L72">72</a> static void <a href="ident?i=tcp_event_new_data_sent">tcp_event_new_data_sent</a>(struct <a href="ident?i=sock">sock</a> *sk, const struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
 <a name="L73" href="source/net/ipv4/tcp_output.c#L73">73</a> {
 <a name="L74" href="source/net/ipv4/tcp_output.c#L74">74</a>         struct <a href="ident?i=inet_connection_sock">inet_connection_sock</a> *icsk = <a href="ident?i=inet_csk">inet_csk</a>(sk);
 <a name="L75" href="source/net/ipv4/tcp_output.c#L75">75</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
 <a name="L76" href="source/net/ipv4/tcp_output.c#L76">76</a>         unsigned int prior_packets = <a href="ident?i=tp">tp</a>-&gt;packets_out;
 <a name="L77" href="source/net/ipv4/tcp_output.c#L77">77</a> 
 <a name="L78" href="source/net/ipv4/tcp_output.c#L78">78</a>         <a href="ident?i=tcp_advance_send_head">tcp_advance_send_head</a>(sk, <a href="ident?i=skb">skb</a>);
 <a name="L79" href="source/net/ipv4/tcp_output.c#L79">79</a>         <a href="ident?i=tp">tp</a>-&gt;snd_nxt = <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;end_seq;
 <a name="L80" href="source/net/ipv4/tcp_output.c#L80">80</a> 
 <a name="L81" href="source/net/ipv4/tcp_output.c#L81">81</a>         <a href="ident?i=tp">tp</a>-&gt;packets_out += <a href="ident?i=tcp_skb_pcount">tcp_skb_pcount</a>(<a href="ident?i=skb">skb</a>);
 <a name="L82" href="source/net/ipv4/tcp_output.c#L82">82</a>         if (!prior_packets || icsk-&gt;icsk_pending == <a href="ident?i=ICSK_TIME_EARLY_RETRANS">ICSK_TIME_EARLY_RETRANS</a> ||
 <a name="L83" href="source/net/ipv4/tcp_output.c#L83">83</a>             icsk-&gt;icsk_pending == <a href="ident?i=ICSK_TIME_LOSS_PROBE">ICSK_TIME_LOSS_PROBE</a>) {
 <a name="L84" href="source/net/ipv4/tcp_output.c#L84">84</a>                 <a href="ident?i=tcp_rearm_rto">tcp_rearm_rto</a>(sk);
 <a name="L85" href="source/net/ipv4/tcp_output.c#L85">85</a>         }
 <a name="L86" href="source/net/ipv4/tcp_output.c#L86">86</a> 
 <a name="L87" href="source/net/ipv4/tcp_output.c#L87">87</a>         <a href="ident?i=NET_ADD_STATS">NET_ADD_STATS</a>(<a href="ident?i=sock_net">sock_net</a>(sk), LINUX_MIB_TCPORIGDATASENT,
 <a name="L88" href="source/net/ipv4/tcp_output.c#L88">88</a>                       <a href="ident?i=tcp_skb_pcount">tcp_skb_pcount</a>(<a href="ident?i=skb">skb</a>));
 <a name="L89" href="source/net/ipv4/tcp_output.c#L89">89</a> }
 <a name="L90" href="source/net/ipv4/tcp_output.c#L90">90</a> 
 <a name="L91" href="source/net/ipv4/tcp_output.c#L91">91</a> <b><i>/* SND.NXT, if window was not shrunk.</i></b>
 <a name="L92" href="source/net/ipv4/tcp_output.c#L92">92</a> <b><i> * If window has been shrunk, what should we make? It is not clear at all.</i></b>
 <a name="L93" href="source/net/ipv4/tcp_output.c#L93">93</a> <b><i> * Using SND.UNA we will fail to open window, SND.NXT is out of window. :-(</i></b>
 <a name="L94" href="source/net/ipv4/tcp_output.c#L94">94</a> <b><i> * Anything in between SND.UNA...SND.UNA+SND.WND also can be already</i></b>
 <a name="L95" href="source/net/ipv4/tcp_output.c#L95">95</a> <b><i> * invalid. OK, let's make this for now:</i></b>
 <a name="L96" href="source/net/ipv4/tcp_output.c#L96">96</a> <b><i> */</i></b>
 <a name="L97" href="source/net/ipv4/tcp_output.c#L97">97</a> static inline <a href="ident?i=__u32">__u32</a> <a href="ident?i=tcp_acceptable_seq">tcp_acceptable_seq</a>(const struct <a href="ident?i=sock">sock</a> *sk)
 <a name="L98" href="source/net/ipv4/tcp_output.c#L98">98</a> {
 <a name="L99" href="source/net/ipv4/tcp_output.c#L99">99</a>         const struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L100" href="source/net/ipv4/tcp_output.c#L100">100</a> 
<a name="L101" href="source/net/ipv4/tcp_output.c#L101">101</a>         if (!<a href="ident?i=before">before</a>(<a href="ident?i=tcp_wnd_end">tcp_wnd_end</a>(<a href="ident?i=tp">tp</a>), <a href="ident?i=tp">tp</a>-&gt;snd_nxt))
<a name="L102" href="source/net/ipv4/tcp_output.c#L102">102</a>                 return <a href="ident?i=tp">tp</a>-&gt;snd_nxt;
<a name="L103" href="source/net/ipv4/tcp_output.c#L103">103</a>         else
<a name="L104" href="source/net/ipv4/tcp_output.c#L104">104</a>                 return <a href="ident?i=tcp_wnd_end">tcp_wnd_end</a>(<a href="ident?i=tp">tp</a>);
<a name="L105" href="source/net/ipv4/tcp_output.c#L105">105</a> }
<a name="L106" href="source/net/ipv4/tcp_output.c#L106">106</a> 
<a name="L107" href="source/net/ipv4/tcp_output.c#L107">107</a> <b><i>/* Calculate mss to advertise in SYN segment.</i></b>
<a name="L108" href="source/net/ipv4/tcp_output.c#L108">108</a> <b><i> * RFC1122, RFC1063, draft-ietf-tcpimpl-pmtud-01 state that:</i></b>
<a name="L109" href="source/net/ipv4/tcp_output.c#L109">109</a> <b><i> *</i></b>
<a name="L110" href="source/net/ipv4/tcp_output.c#L110">110</a> <b><i> * 1. It is independent of path mtu.</i></b>
<a name="L111" href="source/net/ipv4/tcp_output.c#L111">111</a> <b><i> * 2. Ideally, it is maximal possible segment size i.e. 65535-40.</i></b>
<a name="L112" href="source/net/ipv4/tcp_output.c#L112">112</a> <b><i> * 3. For IPv4 it is reasonable to calculate it from maximal MTU of</i></b>
<a name="L113" href="source/net/ipv4/tcp_output.c#L113">113</a> <b><i> *    attached devices, because some buggy hosts are confused by</i></b>
<a name="L114" href="source/net/ipv4/tcp_output.c#L114">114</a> <b><i> *    large MSS.</i></b>
<a name="L115" href="source/net/ipv4/tcp_output.c#L115">115</a> <b><i> * 4. We do not make 3, we advertise MSS, calculated from first</i></b>
<a name="L116" href="source/net/ipv4/tcp_output.c#L116">116</a> <b><i> *    hop device mtu, but allow to raise it to ip_rt_min_advmss.</i></b>
<a name="L117" href="source/net/ipv4/tcp_output.c#L117">117</a> <b><i> *    This may be overridden via information stored in routing table.</i></b>
<a name="L118" href="source/net/ipv4/tcp_output.c#L118">118</a> <b><i> * 5. Value 65535 for MSS is valid in IPv6 and means "as large as possible,</i></b>
<a name="L119" href="source/net/ipv4/tcp_output.c#L119">119</a> <b><i> *    probably even Jumbo".</i></b>
<a name="L120" href="source/net/ipv4/tcp_output.c#L120">120</a> <b><i> */</i></b>
<a name="L121" href="source/net/ipv4/tcp_output.c#L121">121</a> static <a href="ident?i=__u16">__u16</a> <a href="ident?i=tcp_advertise_mss">tcp_advertise_mss</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L122" href="source/net/ipv4/tcp_output.c#L122">122</a> {
<a name="L123" href="source/net/ipv4/tcp_output.c#L123">123</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L124" href="source/net/ipv4/tcp_output.c#L124">124</a>         const struct <a href="ident?i=dst_entry">dst_entry</a> *<a href="ident?i=dst">dst</a> = <a href="ident?i=__sk_dst_get">__sk_dst_get</a>(sk);
<a name="L125" href="source/net/ipv4/tcp_output.c#L125">125</a>         int mss = <a href="ident?i=tp">tp</a>-&gt;advmss;
<a name="L126" href="source/net/ipv4/tcp_output.c#L126">126</a> 
<a name="L127" href="source/net/ipv4/tcp_output.c#L127">127</a>         if (<a href="ident?i=dst">dst</a>) {
<a name="L128" href="source/net/ipv4/tcp_output.c#L128">128</a>                 unsigned int metric = <a href="ident?i=dst_metric_advmss">dst_metric_advmss</a>(<a href="ident?i=dst">dst</a>);
<a name="L129" href="source/net/ipv4/tcp_output.c#L129">129</a> 
<a name="L130" href="source/net/ipv4/tcp_output.c#L130">130</a>                 if (metric &lt; mss) {
<a name="L131" href="source/net/ipv4/tcp_output.c#L131">131</a>                         mss = metric;
<a name="L132" href="source/net/ipv4/tcp_output.c#L132">132</a>                         <a href="ident?i=tp">tp</a>-&gt;advmss = mss;
<a name="L133" href="source/net/ipv4/tcp_output.c#L133">133</a>                 }
<a name="L134" href="source/net/ipv4/tcp_output.c#L134">134</a>         }
<a name="L135" href="source/net/ipv4/tcp_output.c#L135">135</a> 
<a name="L136" href="source/net/ipv4/tcp_output.c#L136">136</a>         return (<a href="ident?i=__u16">__u16</a>)mss;
<a name="L137" href="source/net/ipv4/tcp_output.c#L137">137</a> }
<a name="L138" href="source/net/ipv4/tcp_output.c#L138">138</a> 
<a name="L139" href="source/net/ipv4/tcp_output.c#L139">139</a> <b><i>/* RFC2861. Reset CWND after idle period longer RTO to "restart window".</i></b>
<a name="L140" href="source/net/ipv4/tcp_output.c#L140">140</a> <b><i> * This is the first part of cwnd validation mechanism. */</i></b>
<a name="L141" href="source/net/ipv4/tcp_output.c#L141">141</a> static void <a href="ident?i=tcp_cwnd_restart">tcp_cwnd_restart</a>(struct <a href="ident?i=sock">sock</a> *sk, const struct <a href="ident?i=dst_entry">dst_entry</a> *<a href="ident?i=dst">dst</a>)
<a name="L142" href="source/net/ipv4/tcp_output.c#L142">142</a> {
<a name="L143" href="source/net/ipv4/tcp_output.c#L143">143</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L144" href="source/net/ipv4/tcp_output.c#L144">144</a>         <a href="ident?i=s32">s32</a> <a href="ident?i=delta">delta</a> = <a href="ident?i=tcp_time_stamp">tcp_time_stamp</a> - <a href="ident?i=tp">tp</a>-&gt;lsndtime;
<a name="L145" href="source/net/ipv4/tcp_output.c#L145">145</a>         <a href="ident?i=u32">u32</a> restart_cwnd = <a href="ident?i=tcp_init_cwnd">tcp_init_cwnd</a>(<a href="ident?i=tp">tp</a>, <a href="ident?i=dst">dst</a>);
<a name="L146" href="source/net/ipv4/tcp_output.c#L146">146</a>         <a href="ident?i=u32">u32</a> cwnd = <a href="ident?i=tp">tp</a>-&gt;snd_cwnd;
<a name="L147" href="source/net/ipv4/tcp_output.c#L147">147</a> 
<a name="L148" href="source/net/ipv4/tcp_output.c#L148">148</a>         <a href="ident?i=tcp_ca_event">tcp_ca_event</a>(sk, CA_EVENT_CWND_RESTART);
<a name="L149" href="source/net/ipv4/tcp_output.c#L149">149</a> 
<a name="L150" href="source/net/ipv4/tcp_output.c#L150">150</a>         <a href="ident?i=tp">tp</a>-&gt;snd_ssthresh = <a href="ident?i=tcp_current_ssthresh">tcp_current_ssthresh</a>(sk);
<a name="L151" href="source/net/ipv4/tcp_output.c#L151">151</a>         restart_cwnd = <a href="ident?i=min">min</a>(restart_cwnd, cwnd);
<a name="L152" href="source/net/ipv4/tcp_output.c#L152">152</a> 
<a name="L153" href="source/net/ipv4/tcp_output.c#L153">153</a>         while ((<a href="ident?i=delta">delta</a> -= <a href="ident?i=inet_csk">inet_csk</a>(sk)-&gt;icsk_rto) &gt; 0 &amp;&amp; cwnd &gt; restart_cwnd)
<a name="L154" href="source/net/ipv4/tcp_output.c#L154">154</a>                 cwnd &gt;&gt;= 1;
<a name="L155" href="source/net/ipv4/tcp_output.c#L155">155</a>         <a href="ident?i=tp">tp</a>-&gt;snd_cwnd = <a href="ident?i=max">max</a>(cwnd, restart_cwnd);
<a name="L156" href="source/net/ipv4/tcp_output.c#L156">156</a>         <a href="ident?i=tp">tp</a>-&gt;snd_cwnd_stamp = <a href="ident?i=tcp_time_stamp">tcp_time_stamp</a>;
<a name="L157" href="source/net/ipv4/tcp_output.c#L157">157</a>         <a href="ident?i=tp">tp</a>-&gt;snd_cwnd_used = 0;
<a name="L158" href="source/net/ipv4/tcp_output.c#L158">158</a> }
<a name="L159" href="source/net/ipv4/tcp_output.c#L159">159</a> 
<a name="L160" href="source/net/ipv4/tcp_output.c#L160">160</a> <b><i>/* Congestion state accounting after a packet has been sent. */</i></b>
<a name="L161" href="source/net/ipv4/tcp_output.c#L161">161</a> static void <a href="ident?i=tcp_event_data_sent">tcp_event_data_sent</a>(struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a>,
<a name="L162" href="source/net/ipv4/tcp_output.c#L162">162</a>                                 struct <a href="ident?i=sock">sock</a> *sk)
<a name="L163" href="source/net/ipv4/tcp_output.c#L163">163</a> {
<a name="L164" href="source/net/ipv4/tcp_output.c#L164">164</a>         struct <a href="ident?i=inet_connection_sock">inet_connection_sock</a> *icsk = <a href="ident?i=inet_csk">inet_csk</a>(sk);
<a name="L165" href="source/net/ipv4/tcp_output.c#L165">165</a>         const <a href="ident?i=u32">u32</a> <a href="ident?i=now">now</a> = <a href="ident?i=tcp_time_stamp">tcp_time_stamp</a>;
<a name="L166" href="source/net/ipv4/tcp_output.c#L166">166</a>         const struct <a href="ident?i=dst_entry">dst_entry</a> *<a href="ident?i=dst">dst</a> = <a href="ident?i=__sk_dst_get">__sk_dst_get</a>(sk);
<a name="L167" href="source/net/ipv4/tcp_output.c#L167">167</a> 
<a name="L168" href="source/net/ipv4/tcp_output.c#L168">168</a>         if (<a href="ident?i=sysctl_tcp_slow_start_after_idle">sysctl_tcp_slow_start_after_idle</a> &amp;&amp;
<a name="L169" href="source/net/ipv4/tcp_output.c#L169">169</a>             (!<a href="ident?i=tp">tp</a>-&gt;packets_out &amp;&amp; (<a href="ident?i=s32">s32</a>)(<a href="ident?i=now">now</a> - <a href="ident?i=tp">tp</a>-&gt;lsndtime) &gt; icsk-&gt;icsk_rto))
<a name="L170" href="source/net/ipv4/tcp_output.c#L170">170</a>                 <a href="ident?i=tcp_cwnd_restart">tcp_cwnd_restart</a>(sk, <a href="ident?i=__sk_dst_get">__sk_dst_get</a>(sk));
<a name="L171" href="source/net/ipv4/tcp_output.c#L171">171</a> 
<a name="L172" href="source/net/ipv4/tcp_output.c#L172">172</a>         <a href="ident?i=tp">tp</a>-&gt;lsndtime = <a href="ident?i=now">now</a>;
<a name="L173" href="source/net/ipv4/tcp_output.c#L173">173</a> 
<a name="L174" href="source/net/ipv4/tcp_output.c#L174">174</a>         <b><i>/* If it is a reply for ato after last received</i></b>
<a name="L175" href="source/net/ipv4/tcp_output.c#L175">175</a> <b><i>         * packet, enter pingpong mode.</i></b>
<a name="L176" href="source/net/ipv4/tcp_output.c#L176">176</a> <b><i>         */</i></b>
<a name="L177" href="source/net/ipv4/tcp_output.c#L177">177</a>         if ((<a href="ident?i=u32">u32</a>)(<a href="ident?i=now">now</a> - icsk-&gt;icsk_ack.lrcvtime) &lt; icsk-&gt;icsk_ack.ato &amp;&amp;
<a name="L178" href="source/net/ipv4/tcp_output.c#L178">178</a>             (!<a href="ident?i=dst">dst</a> || !<a href="ident?i=dst_metric">dst_metric</a>(<a href="ident?i=dst">dst</a>, <a href="ident?i=RTAX_QUICKACK">RTAX_QUICKACK</a>)))
<a name="L179" href="source/net/ipv4/tcp_output.c#L179">179</a>                         icsk-&gt;icsk_ack.pingpong = 1;
<a name="L180" href="source/net/ipv4/tcp_output.c#L180">180</a> }
<a name="L181" href="source/net/ipv4/tcp_output.c#L181">181</a> 
<a name="L182" href="source/net/ipv4/tcp_output.c#L182">182</a> <b><i>/* Account for an ACK we sent. */</i></b>
<a name="L183" href="source/net/ipv4/tcp_output.c#L183">183</a> static inline void <a href="ident?i=tcp_event_ack_sent">tcp_event_ack_sent</a>(struct <a href="ident?i=sock">sock</a> *sk, unsigned int pkts)
<a name="L184" href="source/net/ipv4/tcp_output.c#L184">184</a> {
<a name="L185" href="source/net/ipv4/tcp_output.c#L185">185</a>         <a href="ident?i=tcp_dec_quickack_mode">tcp_dec_quickack_mode</a>(sk, pkts);
<a name="L186" href="source/net/ipv4/tcp_output.c#L186">186</a>         <a href="ident?i=inet_csk_clear_xmit_timer">inet_csk_clear_xmit_timer</a>(sk, <a href="ident?i=ICSK_TIME_DACK">ICSK_TIME_DACK</a>);
<a name="L187" href="source/net/ipv4/tcp_output.c#L187">187</a> }
<a name="L188" href="source/net/ipv4/tcp_output.c#L188">188</a> 
<a name="L189" href="source/net/ipv4/tcp_output.c#L189">189</a> 
<a name="L190" href="source/net/ipv4/tcp_output.c#L190">190</a> <a href="ident?i=u32">u32</a> <a href="ident?i=tcp_default_init_rwnd">tcp_default_init_rwnd</a>(<a href="ident?i=u32">u32</a> mss)
<a name="L191" href="source/net/ipv4/tcp_output.c#L191">191</a> {
<a name="L192" href="source/net/ipv4/tcp_output.c#L192">192</a>         <b><i>/* Initial receive window should be twice of TCP_INIT_CWND to</i></b>
<a name="L193" href="source/net/ipv4/tcp_output.c#L193">193</a> <b><i>         * enable proper sending of new unsent data during fast recovery</i></b>
<a name="L194" href="source/net/ipv4/tcp_output.c#L194">194</a> <b><i>         * (RFC 3517, Section 4, NextSeg() rule (2)). Further place a</i></b>
<a name="L195" href="source/net/ipv4/tcp_output.c#L195">195</a> <b><i>         * limit when mss is larger than 1460.</i></b>
<a name="L196" href="source/net/ipv4/tcp_output.c#L196">196</a> <b><i>         */</i></b>
<a name="L197" href="source/net/ipv4/tcp_output.c#L197">197</a>         <a href="ident?i=u32">u32</a> init_rwnd = <a href="ident?i=TCP_INIT_CWND">TCP_INIT_CWND</a> * 2;
<a name="L198" href="source/net/ipv4/tcp_output.c#L198">198</a> 
<a name="L199" href="source/net/ipv4/tcp_output.c#L199">199</a>         if (mss &gt; 1460)
<a name="L200" href="source/net/ipv4/tcp_output.c#L200">200</a>                 init_rwnd = <a href="ident?i=max">max</a>((1460 * init_rwnd) / mss, 2U);
<a name="L201" href="source/net/ipv4/tcp_output.c#L201">201</a>         return init_rwnd;
<a name="L202" href="source/net/ipv4/tcp_output.c#L202">202</a> }
<a name="L203" href="source/net/ipv4/tcp_output.c#L203">203</a> 
<a name="L204" href="source/net/ipv4/tcp_output.c#L204">204</a> <b><i>/* Determine a window scaling and initial window to offer.</i></b>
<a name="L205" href="source/net/ipv4/tcp_output.c#L205">205</a> <b><i> * Based on the assumption that the given amount of space</i></b>
<a name="L206" href="source/net/ipv4/tcp_output.c#L206">206</a> <b><i> * will be offered. Store the results in the tp structure.</i></b>
<a name="L207" href="source/net/ipv4/tcp_output.c#L207">207</a> <b><i> * NOTE: for smooth operation initial space offering should</i></b>
<a name="L208" href="source/net/ipv4/tcp_output.c#L208">208</a> <b><i> * be a multiple of mss if possible. We assume here that mss &gt;= 1.</i></b>
<a name="L209" href="source/net/ipv4/tcp_output.c#L209">209</a> <b><i> * This MUST be enforced by all callers.</i></b>
<a name="L210" href="source/net/ipv4/tcp_output.c#L210">210</a> <b><i> */</i></b>
<a name="L211" href="source/net/ipv4/tcp_output.c#L211">211</a> void <a href="ident?i=tcp_select_initial_window">tcp_select_initial_window</a>(int __space, <a href="ident?i=__u32">__u32</a> mss,
<a name="L212" href="source/net/ipv4/tcp_output.c#L212">212</a>                                <a href="ident?i=__u32">__u32</a> *rcv_wnd, <a href="ident?i=__u32">__u32</a> *window_clamp,
<a name="L213" href="source/net/ipv4/tcp_output.c#L213">213</a>                                int wscale_ok, <a href="ident?i=__u8">__u8</a> *rcv_wscale,
<a name="L214" href="source/net/ipv4/tcp_output.c#L214">214</a>                                <a href="ident?i=__u32">__u32</a> init_rcv_wnd)
<a name="L215" href="source/net/ipv4/tcp_output.c#L215">215</a> {
<a name="L216" href="source/net/ipv4/tcp_output.c#L216">216</a>         unsigned int <a href="ident?i=space">space</a> = (__space &lt; 0 ? 0 : __space);
<a name="L217" href="source/net/ipv4/tcp_output.c#L217">217</a> 
<a name="L218" href="source/net/ipv4/tcp_output.c#L218">218</a>         <b><i>/* If no clamp set the clamp to the max possible scaled window */</i></b>
<a name="L219" href="source/net/ipv4/tcp_output.c#L219">219</a>         if (*window_clamp == 0)
<a name="L220" href="source/net/ipv4/tcp_output.c#L220">220</a>                 (*window_clamp) = (65535 &lt;&lt; 14);
<a name="L221" href="source/net/ipv4/tcp_output.c#L221">221</a>         <a href="ident?i=space">space</a> = <a href="ident?i=min">min</a>(*window_clamp, <a href="ident?i=space">space</a>);
<a name="L222" href="source/net/ipv4/tcp_output.c#L222">222</a> 
<a name="L223" href="source/net/ipv4/tcp_output.c#L223">223</a>         <b><i>/* Quantize space offering to a multiple of mss if possible. */</i></b>
<a name="L224" href="source/net/ipv4/tcp_output.c#L224">224</a>         if (<a href="ident?i=space">space</a> &gt; mss)
<a name="L225" href="source/net/ipv4/tcp_output.c#L225">225</a>                 <a href="ident?i=space">space</a> = (<a href="ident?i=space">space</a> / mss) * mss;
<a name="L226" href="source/net/ipv4/tcp_output.c#L226">226</a> 
<a name="L227" href="source/net/ipv4/tcp_output.c#L227">227</a>         <b><i>/* NOTE: offering an initial window larger than 32767</i></b>
<a name="L228" href="source/net/ipv4/tcp_output.c#L228">228</a> <b><i>         * will break some buggy TCP stacks. If the admin tells us</i></b>
<a name="L229" href="source/net/ipv4/tcp_output.c#L229">229</a> <b><i>         * it is likely we could be speaking with such a buggy stack</i></b>
<a name="L230" href="source/net/ipv4/tcp_output.c#L230">230</a> <b><i>         * we will truncate our initial window offering to 32K-1</i></b>
<a name="L231" href="source/net/ipv4/tcp_output.c#L231">231</a> <b><i>         * unless the remote has sent us a window scaling option,</i></b>
<a name="L232" href="source/net/ipv4/tcp_output.c#L232">232</a> <b><i>         * which we interpret as a sign the remote TCP is not</i></b>
<a name="L233" href="source/net/ipv4/tcp_output.c#L233">233</a> <b><i>         * misinterpreting the window field as a signed quantity.</i></b>
<a name="L234" href="source/net/ipv4/tcp_output.c#L234">234</a> <b><i>         */</i></b>
<a name="L235" href="source/net/ipv4/tcp_output.c#L235">235</a>         if (<a href="ident?i=sysctl_tcp_workaround_signed_windows">sysctl_tcp_workaround_signed_windows</a>)
<a name="L236" href="source/net/ipv4/tcp_output.c#L236">236</a>                 (*rcv_wnd) = <a href="ident?i=min">min</a>(<a href="ident?i=space">space</a>, <a href="ident?i=MAX_TCP_WINDOW">MAX_TCP_WINDOW</a>);
<a name="L237" href="source/net/ipv4/tcp_output.c#L237">237</a>         else
<a name="L238" href="source/net/ipv4/tcp_output.c#L238">238</a>                 (*rcv_wnd) = <a href="ident?i=space">space</a>;
<a name="L239" href="source/net/ipv4/tcp_output.c#L239">239</a> 
<a name="L240" href="source/net/ipv4/tcp_output.c#L240">240</a>         (*rcv_wscale) = 0;
<a name="L241" href="source/net/ipv4/tcp_output.c#L241">241</a>         if (wscale_ok) {
<a name="L242" href="source/net/ipv4/tcp_output.c#L242">242</a>                 <b><i>/* Set window scaling on max possible window</i></b>
<a name="L243" href="source/net/ipv4/tcp_output.c#L243">243</a> <b><i>                 * See RFC1323 for an explanation of the limit to 14</i></b>
<a name="L244" href="source/net/ipv4/tcp_output.c#L244">244</a> <b><i>                 */</i></b>
<a name="L245" href="source/net/ipv4/tcp_output.c#L245">245</a>                 <a href="ident?i=space">space</a> = <a href="ident?i=max_t">max_t</a>(<a href="ident?i=u32">u32</a>, <a href="ident?i=sysctl_tcp_rmem">sysctl_tcp_rmem</a>[2], <a href="ident?i=sysctl_rmem_max">sysctl_rmem_max</a>);
<a name="L246" href="source/net/ipv4/tcp_output.c#L246">246</a>                 <a href="ident?i=space">space</a> = <a href="ident?i=min_t">min_t</a>(<a href="ident?i=u32">u32</a>, <a href="ident?i=space">space</a>, *window_clamp);
<a name="L247" href="source/net/ipv4/tcp_output.c#L247">247</a>                 while (<a href="ident?i=space">space</a> &gt; 65535 &amp;&amp; (*rcv_wscale) &lt; 14) {
<a name="L248" href="source/net/ipv4/tcp_output.c#L248">248</a>                         <a href="ident?i=space">space</a> &gt;&gt;= 1;
<a name="L249" href="source/net/ipv4/tcp_output.c#L249">249</a>                         (*rcv_wscale)++;
<a name="L250" href="source/net/ipv4/tcp_output.c#L250">250</a>                 }
<a name="L251" href="source/net/ipv4/tcp_output.c#L251">251</a>         }
<a name="L252" href="source/net/ipv4/tcp_output.c#L252">252</a> 
<a name="L253" href="source/net/ipv4/tcp_output.c#L253">253</a>         if (mss &gt; (1 &lt;&lt; *rcv_wscale)) {
<a name="L254" href="source/net/ipv4/tcp_output.c#L254">254</a>                 if (!init_rcv_wnd) <b><i>/* Use default unless specified otherwise */</i></b>
<a name="L255" href="source/net/ipv4/tcp_output.c#L255">255</a>                         init_rcv_wnd = <a href="ident?i=tcp_default_init_rwnd">tcp_default_init_rwnd</a>(mss);
<a name="L256" href="source/net/ipv4/tcp_output.c#L256">256</a>                 *rcv_wnd = <a href="ident?i=min">min</a>(*rcv_wnd, init_rcv_wnd * mss);
<a name="L257" href="source/net/ipv4/tcp_output.c#L257">257</a>         }
<a name="L258" href="source/net/ipv4/tcp_output.c#L258">258</a> 
<a name="L259" href="source/net/ipv4/tcp_output.c#L259">259</a>         <b><i>/* Set the clamp no higher than max representable value */</i></b>
<a name="L260" href="source/net/ipv4/tcp_output.c#L260">260</a>         (*window_clamp) = <a href="ident?i=min">min</a>(65535U &lt;&lt; (*rcv_wscale), *window_clamp);
<a name="L261" href="source/net/ipv4/tcp_output.c#L261">261</a> }
<a name="L262" href="source/net/ipv4/tcp_output.c#L262">262</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=tcp_select_initial_window">tcp_select_initial_window</a>);
<a name="L263" href="source/net/ipv4/tcp_output.c#L263">263</a> 
<a name="L264" href="source/net/ipv4/tcp_output.c#L264">264</a> <b><i>/* Chose a new window to advertise, update state in tcp_sock for the</i></b>
<a name="L265" href="source/net/ipv4/tcp_output.c#L265">265</a> <b><i> * socket, and return result with RFC1323 scaling applied.  The return</i></b>
<a name="L266" href="source/net/ipv4/tcp_output.c#L266">266</a> <b><i> * value can be stuffed directly into th-&gt;window for an outgoing</i></b>
<a name="L267" href="source/net/ipv4/tcp_output.c#L267">267</a> <b><i> * frame.</i></b>
<a name="L268" href="source/net/ipv4/tcp_output.c#L268">268</a> <b><i> */</i></b>
<a name="L269" href="source/net/ipv4/tcp_output.c#L269">269</a> static <a href="ident?i=u16">u16</a> <a href="ident?i=tcp_select_window">tcp_select_window</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L270" href="source/net/ipv4/tcp_output.c#L270">270</a> {
<a name="L271" href="source/net/ipv4/tcp_output.c#L271">271</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L272" href="source/net/ipv4/tcp_output.c#L272">272</a>         <a href="ident?i=u32">u32</a> old_win = <a href="ident?i=tp">tp</a>-&gt;rcv_wnd;
<a name="L273" href="source/net/ipv4/tcp_output.c#L273">273</a>         <a href="ident?i=u32">u32</a> cur_win = <a href="ident?i=tcp_receive_window">tcp_receive_window</a>(<a href="ident?i=tp">tp</a>);
<a name="L274" href="source/net/ipv4/tcp_output.c#L274">274</a>         <a href="ident?i=u32">u32</a> new_win = <a href="ident?i=__tcp_select_window">__tcp_select_window</a>(sk);
<a name="L275" href="source/net/ipv4/tcp_output.c#L275">275</a> 
<a name="L276" href="source/net/ipv4/tcp_output.c#L276">276</a>         <b><i>/* Never shrink the offered window */</i></b>
<a name="L277" href="source/net/ipv4/tcp_output.c#L277">277</a>         if (new_win &lt; cur_win) {
<a name="L278" href="source/net/ipv4/tcp_output.c#L278">278</a>                 <b><i>/* Danger Will Robinson!</i></b>
<a name="L279" href="source/net/ipv4/tcp_output.c#L279">279</a> <b><i>                 * Don't update rcv_wup/rcv_wnd here or else</i></b>
<a name="L280" href="source/net/ipv4/tcp_output.c#L280">280</a> <b><i>                 * we will not be able to advertise a zero</i></b>
<a name="L281" href="source/net/ipv4/tcp_output.c#L281">281</a> <b><i>                 * window in time.  --DaveM</i></b>
<a name="L282" href="source/net/ipv4/tcp_output.c#L282">282</a> <b><i>                 *</i></b>
<a name="L283" href="source/net/ipv4/tcp_output.c#L283">283</a> <b><i>                 * Relax Will Robinson.</i></b>
<a name="L284" href="source/net/ipv4/tcp_output.c#L284">284</a> <b><i>                 */</i></b>
<a name="L285" href="source/net/ipv4/tcp_output.c#L285">285</a>                 if (new_win == 0)
<a name="L286" href="source/net/ipv4/tcp_output.c#L286">286</a>                         <a href="ident?i=NET_INC_STATS">NET_INC_STATS</a>(<a href="ident?i=sock_net">sock_net</a>(sk),
<a name="L287" href="source/net/ipv4/tcp_output.c#L287">287</a>                                       LINUX_MIB_TCPWANTZEROWINDOWADV);
<a name="L288" href="source/net/ipv4/tcp_output.c#L288">288</a>                 new_win = <a href="ident?i=ALIGN">ALIGN</a>(cur_win, 1 &lt;&lt; <a href="ident?i=tp">tp</a>-&gt;rx_opt.rcv_wscale);
<a name="L289" href="source/net/ipv4/tcp_output.c#L289">289</a>         }
<a name="L290" href="source/net/ipv4/tcp_output.c#L290">290</a>         <a href="ident?i=tp">tp</a>-&gt;rcv_wnd = new_win;
<a name="L291" href="source/net/ipv4/tcp_output.c#L291">291</a>         <a href="ident?i=tp">tp</a>-&gt;rcv_wup = <a href="ident?i=tp">tp</a>-&gt;rcv_nxt;
<a name="L292" href="source/net/ipv4/tcp_output.c#L292">292</a> 
<a name="L293" href="source/net/ipv4/tcp_output.c#L293">293</a>         <b><i>/* Make sure we do not exceed the maximum possible</i></b>
<a name="L294" href="source/net/ipv4/tcp_output.c#L294">294</a> <b><i>         * scaled window.</i></b>
<a name="L295" href="source/net/ipv4/tcp_output.c#L295">295</a> <b><i>         */</i></b>
<a name="L296" href="source/net/ipv4/tcp_output.c#L296">296</a>         if (!<a href="ident?i=tp">tp</a>-&gt;rx_opt.rcv_wscale &amp;&amp; <a href="ident?i=sysctl_tcp_workaround_signed_windows">sysctl_tcp_workaround_signed_windows</a>)
<a name="L297" href="source/net/ipv4/tcp_output.c#L297">297</a>                 new_win = <a href="ident?i=min">min</a>(new_win, <a href="ident?i=MAX_TCP_WINDOW">MAX_TCP_WINDOW</a>);
<a name="L298" href="source/net/ipv4/tcp_output.c#L298">298</a>         else
<a name="L299" href="source/net/ipv4/tcp_output.c#L299">299</a>                 new_win = <a href="ident?i=min">min</a>(new_win, (65535U &lt;&lt; <a href="ident?i=tp">tp</a>-&gt;rx_opt.rcv_wscale));
<a name="L300" href="source/net/ipv4/tcp_output.c#L300">300</a> 
<a name="L301" href="source/net/ipv4/tcp_output.c#L301">301</a>         <b><i>/* RFC1323 scaling applied */</i></b>
<a name="L302" href="source/net/ipv4/tcp_output.c#L302">302</a>         new_win &gt;&gt;= <a href="ident?i=tp">tp</a>-&gt;rx_opt.rcv_wscale;
<a name="L303" href="source/net/ipv4/tcp_output.c#L303">303</a> 
<a name="L304" href="source/net/ipv4/tcp_output.c#L304">304</a>         <b><i>/* If we advertise zero window, disable fast path. */</i></b>
<a name="L305" href="source/net/ipv4/tcp_output.c#L305">305</a>         if (new_win == 0) {
<a name="L306" href="source/net/ipv4/tcp_output.c#L306">306</a>                 <a href="ident?i=tp">tp</a>-&gt;pred_flags = 0;
<a name="L307" href="source/net/ipv4/tcp_output.c#L307">307</a>                 if (old_win)
<a name="L308" href="source/net/ipv4/tcp_output.c#L308">308</a>                         <a href="ident?i=NET_INC_STATS">NET_INC_STATS</a>(<a href="ident?i=sock_net">sock_net</a>(sk),
<a name="L309" href="source/net/ipv4/tcp_output.c#L309">309</a>                                       LINUX_MIB_TCPTOZEROWINDOWADV);
<a name="L310" href="source/net/ipv4/tcp_output.c#L310">310</a>         } else if (old_win == 0) {
<a name="L311" href="source/net/ipv4/tcp_output.c#L311">311</a>                 <a href="ident?i=NET_INC_STATS">NET_INC_STATS</a>(<a href="ident?i=sock_net">sock_net</a>(sk), LINUX_MIB_TCPFROMZEROWINDOWADV);
<a name="L312" href="source/net/ipv4/tcp_output.c#L312">312</a>         }
<a name="L313" href="source/net/ipv4/tcp_output.c#L313">313</a> 
<a name="L314" href="source/net/ipv4/tcp_output.c#L314">314</a>         return new_win;
<a name="L315" href="source/net/ipv4/tcp_output.c#L315">315</a> }
<a name="L316" href="source/net/ipv4/tcp_output.c#L316">316</a> 
<a name="L317" href="source/net/ipv4/tcp_output.c#L317">317</a> <b><i>/* Packet ECN state for a SYN-ACK */</i></b>
<a name="L318" href="source/net/ipv4/tcp_output.c#L318">318</a> static void <a href="ident?i=tcp_ecn_send_synack">tcp_ecn_send_synack</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L319" href="source/net/ipv4/tcp_output.c#L319">319</a> {
<a name="L320" href="source/net/ipv4/tcp_output.c#L320">320</a>         const struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L321" href="source/net/ipv4/tcp_output.c#L321">321</a> 
<a name="L322" href="source/net/ipv4/tcp_output.c#L322">322</a>         <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;tcp_flags &amp;= ~TCPHDR_CWR;
<a name="L323" href="source/net/ipv4/tcp_output.c#L323">323</a>         if (!(<a href="ident?i=tp">tp</a>-&gt;ecn_flags &amp; <a href="ident?i=TCP_ECN_OK">TCP_ECN_OK</a>))
<a name="L324" href="source/net/ipv4/tcp_output.c#L324">324</a>                 <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;tcp_flags &amp;= ~TCPHDR_ECE;
<a name="L325" href="source/net/ipv4/tcp_output.c#L325">325</a>         else if (<a href="ident?i=tcp_ca_needs_ecn">tcp_ca_needs_ecn</a>(sk))
<a name="L326" href="source/net/ipv4/tcp_output.c#L326">326</a>                 <a href="ident?i=INET_ECN_xmit">INET_ECN_xmit</a>(sk);
<a name="L327" href="source/net/ipv4/tcp_output.c#L327">327</a> }
<a name="L328" href="source/net/ipv4/tcp_output.c#L328">328</a> 
<a name="L329" href="source/net/ipv4/tcp_output.c#L329">329</a> <b><i>/* Packet ECN state for a SYN.  */</i></b>
<a name="L330" href="source/net/ipv4/tcp_output.c#L330">330</a> static void <a href="ident?i=tcp_ecn_send_syn">tcp_ecn_send_syn</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L331" href="source/net/ipv4/tcp_output.c#L331">331</a> {
<a name="L332" href="source/net/ipv4/tcp_output.c#L332">332</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L333" href="source/net/ipv4/tcp_output.c#L333">333</a>         <a href="ident?i=bool">bool</a> <a href="ident?i=use_ecn">use_ecn</a> = <a href="ident?i=sock_net">sock_net</a>(sk)-&gt;ipv4.sysctl_tcp_ecn == 1 ||
<a name="L334" href="source/net/ipv4/tcp_output.c#L334">334</a>                        <a href="ident?i=tcp_ca_needs_ecn">tcp_ca_needs_ecn</a>(sk);
<a name="L335" href="source/net/ipv4/tcp_output.c#L335">335</a> 
<a name="L336" href="source/net/ipv4/tcp_output.c#L336">336</a>         if (!<a href="ident?i=use_ecn">use_ecn</a>) {
<a name="L337" href="source/net/ipv4/tcp_output.c#L337">337</a>                 const struct <a href="ident?i=dst_entry">dst_entry</a> *<a href="ident?i=dst">dst</a> = <a href="ident?i=__sk_dst_get">__sk_dst_get</a>(sk);
<a name="L338" href="source/net/ipv4/tcp_output.c#L338">338</a> 
<a name="L339" href="source/net/ipv4/tcp_output.c#L339">339</a>                 if (<a href="ident?i=dst">dst</a> &amp;&amp; <a href="ident?i=dst_feature">dst_feature</a>(<a href="ident?i=dst">dst</a>, <a href="ident?i=RTAX_FEATURE_ECN">RTAX_FEATURE_ECN</a>))
<a name="L340" href="source/net/ipv4/tcp_output.c#L340">340</a>                         <a href="ident?i=use_ecn">use_ecn</a> = <a href="ident?i=true">true</a>;
<a name="L341" href="source/net/ipv4/tcp_output.c#L341">341</a>         }
<a name="L342" href="source/net/ipv4/tcp_output.c#L342">342</a> 
<a name="L343" href="source/net/ipv4/tcp_output.c#L343">343</a>         <a href="ident?i=tp">tp</a>-&gt;ecn_flags = 0;
<a name="L344" href="source/net/ipv4/tcp_output.c#L344">344</a> 
<a name="L345" href="source/net/ipv4/tcp_output.c#L345">345</a>         if (<a href="ident?i=use_ecn">use_ecn</a>) {
<a name="L346" href="source/net/ipv4/tcp_output.c#L346">346</a>                 <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;tcp_flags |= <a href="ident?i=TCPHDR_ECE">TCPHDR_ECE</a> | <a href="ident?i=TCPHDR_CWR">TCPHDR_CWR</a>;
<a name="L347" href="source/net/ipv4/tcp_output.c#L347">347</a>                 <a href="ident?i=tp">tp</a>-&gt;ecn_flags = <a href="ident?i=TCP_ECN_OK">TCP_ECN_OK</a>;
<a name="L348" href="source/net/ipv4/tcp_output.c#L348">348</a>                 if (<a href="ident?i=tcp_ca_needs_ecn">tcp_ca_needs_ecn</a>(sk))
<a name="L349" href="source/net/ipv4/tcp_output.c#L349">349</a>                         <a href="ident?i=INET_ECN_xmit">INET_ECN_xmit</a>(sk);
<a name="L350" href="source/net/ipv4/tcp_output.c#L350">350</a>         }
<a name="L351" href="source/net/ipv4/tcp_output.c#L351">351</a> }
<a name="L352" href="source/net/ipv4/tcp_output.c#L352">352</a> 
<a name="L353" href="source/net/ipv4/tcp_output.c#L353">353</a> static void
<a name="L354" href="source/net/ipv4/tcp_output.c#L354">354</a> <a href="ident?i=tcp_ecn_make_synack">tcp_ecn_make_synack</a>(const struct <a href="ident?i=request_sock">request_sock</a> *<a href="ident?i=req">req</a>, struct <a href="ident?i=tcphdr">tcphdr</a> *<a href="ident?i=th">th</a>,
<a name="L355" href="source/net/ipv4/tcp_output.c#L355">355</a>                     struct <a href="ident?i=sock">sock</a> *sk)
<a name="L356" href="source/net/ipv4/tcp_output.c#L356">356</a> {
<a name="L357" href="source/net/ipv4/tcp_output.c#L357">357</a>         if (<a href="ident?i=inet_rsk">inet_rsk</a>(<a href="ident?i=req">req</a>)-&gt;ecn_ok) {
<a name="L358" href="source/net/ipv4/tcp_output.c#L358">358</a>                 <a href="ident?i=th">th</a>-&gt;ece = 1;
<a name="L359" href="source/net/ipv4/tcp_output.c#L359">359</a>                 if (<a href="ident?i=tcp_ca_needs_ecn">tcp_ca_needs_ecn</a>(sk))
<a name="L360" href="source/net/ipv4/tcp_output.c#L360">360</a>                         <a href="ident?i=INET_ECN_xmit">INET_ECN_xmit</a>(sk);
<a name="L361" href="source/net/ipv4/tcp_output.c#L361">361</a>         }
<a name="L362" href="source/net/ipv4/tcp_output.c#L362">362</a> }
<a name="L363" href="source/net/ipv4/tcp_output.c#L363">363</a> 
<a name="L364" href="source/net/ipv4/tcp_output.c#L364">364</a> <b><i>/* Set up ECN state for a packet on a ESTABLISHED socket that is about to</i></b>
<a name="L365" href="source/net/ipv4/tcp_output.c#L365">365</a> <b><i> * be sent.</i></b>
<a name="L366" href="source/net/ipv4/tcp_output.c#L366">366</a> <b><i> */</i></b>
<a name="L367" href="source/net/ipv4/tcp_output.c#L367">367</a> static void <a href="ident?i=tcp_ecn_send">tcp_ecn_send</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
<a name="L368" href="source/net/ipv4/tcp_output.c#L368">368</a>                                 int tcp_header_len)
<a name="L369" href="source/net/ipv4/tcp_output.c#L369">369</a> {
<a name="L370" href="source/net/ipv4/tcp_output.c#L370">370</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L371" href="source/net/ipv4/tcp_output.c#L371">371</a> 
<a name="L372" href="source/net/ipv4/tcp_output.c#L372">372</a>         if (<a href="ident?i=tp">tp</a>-&gt;ecn_flags &amp; <a href="ident?i=TCP_ECN_OK">TCP_ECN_OK</a>) {
<a name="L373" href="source/net/ipv4/tcp_output.c#L373">373</a>                 <b><i>/* Not-retransmitted data segment: set ECT and inject CWR. */</i></b>
<a name="L374" href="source/net/ipv4/tcp_output.c#L374">374</a>                 if (<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a> != tcp_header_len &amp;&amp;
<a name="L375" href="source/net/ipv4/tcp_output.c#L375">375</a>                     !<a href="ident?i=before">before</a>(<a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=seq">seq</a>, <a href="ident?i=tp">tp</a>-&gt;snd_nxt)) {
<a name="L376" href="source/net/ipv4/tcp_output.c#L376">376</a>                         <a href="ident?i=INET_ECN_xmit">INET_ECN_xmit</a>(sk);
<a name="L377" href="source/net/ipv4/tcp_output.c#L377">377</a>                         if (<a href="ident?i=tp">tp</a>-&gt;ecn_flags &amp; <a href="ident?i=TCP_ECN_QUEUE_CWR">TCP_ECN_QUEUE_CWR</a>) {
<a name="L378" href="source/net/ipv4/tcp_output.c#L378">378</a>                                 <a href="ident?i=tp">tp</a>-&gt;ecn_flags &amp;= ~TCP_ECN_QUEUE_CWR;
<a name="L379" href="source/net/ipv4/tcp_output.c#L379">379</a>                                 <a href="ident?i=tcp_hdr">tcp_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;cwr = 1;
<a name="L380" href="source/net/ipv4/tcp_output.c#L380">380</a>                                 <a href="ident?i=skb_shinfo">skb_shinfo</a>(<a href="ident?i=skb">skb</a>)-&gt;gso_type |= SKB_GSO_TCP_ECN;
<a name="L381" href="source/net/ipv4/tcp_output.c#L381">381</a>                         }
<a name="L382" href="source/net/ipv4/tcp_output.c#L382">382</a>                 } else if (!<a href="ident?i=tcp_ca_needs_ecn">tcp_ca_needs_ecn</a>(sk)) {
<a name="L383" href="source/net/ipv4/tcp_output.c#L383">383</a>                         <b><i>/* ACK or retransmitted segment: clear ECT|CE */</i></b>
<a name="L384" href="source/net/ipv4/tcp_output.c#L384">384</a>                         <a href="ident?i=INET_ECN_dontxmit">INET_ECN_dontxmit</a>(sk);
<a name="L385" href="source/net/ipv4/tcp_output.c#L385">385</a>                 }
<a name="L386" href="source/net/ipv4/tcp_output.c#L386">386</a>                 if (<a href="ident?i=tp">tp</a>-&gt;ecn_flags &amp; <a href="ident?i=TCP_ECN_DEMAND_CWR">TCP_ECN_DEMAND_CWR</a>)
<a name="L387" href="source/net/ipv4/tcp_output.c#L387">387</a>                         <a href="ident?i=tcp_hdr">tcp_hdr</a>(<a href="ident?i=skb">skb</a>)-&gt;ece = 1;
<a name="L388" href="source/net/ipv4/tcp_output.c#L388">388</a>         }
<a name="L389" href="source/net/ipv4/tcp_output.c#L389">389</a> }
<a name="L390" href="source/net/ipv4/tcp_output.c#L390">390</a> 
<a name="L391" href="source/net/ipv4/tcp_output.c#L391">391</a> <b><i>/* Constructs common control bits of non-data skb. If SYN/FIN is present,</i></b>
<a name="L392" href="source/net/ipv4/tcp_output.c#L392">392</a> <b><i> * auto increment end seqno.</i></b>
<a name="L393" href="source/net/ipv4/tcp_output.c#L393">393</a> <b><i> */</i></b>
<a name="L394" href="source/net/ipv4/tcp_output.c#L394">394</a> static void <a href="ident?i=tcp_init_nondata_skb">tcp_init_nondata_skb</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, <a href="ident?i=u32">u32</a> <a href="ident?i=seq">seq</a>, <a href="ident?i=u8">u8</a> <a href="ident?i=flags">flags</a>)
<a name="L395" href="source/net/ipv4/tcp_output.c#L395">395</a> {
<a name="L396" href="source/net/ipv4/tcp_output.c#L396">396</a>         struct <a href="ident?i=skb_shared_info">skb_shared_info</a> *shinfo = <a href="ident?i=skb_shinfo">skb_shinfo</a>(<a href="ident?i=skb">skb</a>);
<a name="L397" href="source/net/ipv4/tcp_output.c#L397">397</a> 
<a name="L398" href="source/net/ipv4/tcp_output.c#L398">398</a>         <a href="ident?i=skb">skb</a>-&gt;ip_summed = <a href="ident?i=CHECKSUM_PARTIAL">CHECKSUM_PARTIAL</a>;
<a name="L399" href="source/net/ipv4/tcp_output.c#L399">399</a>         <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=csum">csum</a> = 0;
<a name="L400" href="source/net/ipv4/tcp_output.c#L400">400</a> 
<a name="L401" href="source/net/ipv4/tcp_output.c#L401">401</a>         <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;tcp_flags = <a href="ident?i=flags">flags</a>;
<a name="L402" href="source/net/ipv4/tcp_output.c#L402">402</a>         <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;sacked = 0;
<a name="L403" href="source/net/ipv4/tcp_output.c#L403">403</a> 
<a name="L404" href="source/net/ipv4/tcp_output.c#L404">404</a>         <a href="ident?i=tcp_skb_pcount_set">tcp_skb_pcount_set</a>(<a href="ident?i=skb">skb</a>, 1);
<a name="L405" href="source/net/ipv4/tcp_output.c#L405">405</a>         shinfo-&gt;gso_size = 0;
<a name="L406" href="source/net/ipv4/tcp_output.c#L406">406</a>         shinfo-&gt;gso_type = 0;
<a name="L407" href="source/net/ipv4/tcp_output.c#L407">407</a> 
<a name="L408" href="source/net/ipv4/tcp_output.c#L408">408</a>         <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=seq">seq</a> = <a href="ident?i=seq">seq</a>;
<a name="L409" href="source/net/ipv4/tcp_output.c#L409">409</a>         if (<a href="ident?i=flags">flags</a> &amp; (<a href="ident?i=TCPHDR_SYN">TCPHDR_SYN</a> | <a href="ident?i=TCPHDR_FIN">TCPHDR_FIN</a>))
<a name="L410" href="source/net/ipv4/tcp_output.c#L410">410</a>                 <a href="ident?i=seq">seq</a>++;
<a name="L411" href="source/net/ipv4/tcp_output.c#L411">411</a>         <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;end_seq = <a href="ident?i=seq">seq</a>;
<a name="L412" href="source/net/ipv4/tcp_output.c#L412">412</a> }
<a name="L413" href="source/net/ipv4/tcp_output.c#L413">413</a> 
<a name="L414" href="source/net/ipv4/tcp_output.c#L414">414</a> static inline <a href="ident?i=bool">bool</a> <a href="ident?i=tcp_urg_mode">tcp_urg_mode</a>(const struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a>)
<a name="L415" href="source/net/ipv4/tcp_output.c#L415">415</a> {
<a name="L416" href="source/net/ipv4/tcp_output.c#L416">416</a>         return <a href="ident?i=tp">tp</a>-&gt;snd_una != <a href="ident?i=tp">tp</a>-&gt;snd_up;
<a name="L417" href="source/net/ipv4/tcp_output.c#L417">417</a> }
<a name="L418" href="source/net/ipv4/tcp_output.c#L418">418</a> 
<a name="L419" href="source/net/ipv4/tcp_output.c#L419">419</a> #define <a href="ident?i=OPTION_SACK_ADVERTISE">OPTION_SACK_ADVERTISE</a>   (1 &lt;&lt; 0)
<a name="L420" href="source/net/ipv4/tcp_output.c#L420">420</a> #define <a href="ident?i=OPTION_TS">OPTION_TS</a>               (1 &lt;&lt; 1)
<a name="L421" href="source/net/ipv4/tcp_output.c#L421">421</a> #define <a href="ident?i=OPTION_MD5">OPTION_MD5</a>              (1 &lt;&lt; 2)
<a name="L422" href="source/net/ipv4/tcp_output.c#L422">422</a> #define <a href="ident?i=OPTION_WSCALE">OPTION_WSCALE</a>           (1 &lt;&lt; 3)
<a name="L423" href="source/net/ipv4/tcp_output.c#L423">423</a> #define <a href="ident?i=OPTION_FAST_OPEN_COOKIE">OPTION_FAST_OPEN_COOKIE</a> (1 &lt;&lt; 8)
<a name="L424" href="source/net/ipv4/tcp_output.c#L424">424</a> 
<a name="L425" href="source/net/ipv4/tcp_output.c#L425">425</a> struct <a href="ident?i=tcp_out_options">tcp_out_options</a> {
<a name="L426" href="source/net/ipv4/tcp_output.c#L426">426</a>         <a href="ident?i=u16">u16</a> <a href="ident?i=options">options</a>;            <b><i>/* bit field of OPTION_* */</i></b>
<a name="L427" href="source/net/ipv4/tcp_output.c#L427">427</a>         <a href="ident?i=u16">u16</a> mss;                <b><i>/* 0 to disable */</i></b>
<a name="L428" href="source/net/ipv4/tcp_output.c#L428">428</a>         <a href="ident?i=u8">u8</a> <a href="ident?i=ws">ws</a>;                  <b><i>/* window scale, 0 to disable */</i></b>
<a name="L429" href="source/net/ipv4/tcp_output.c#L429">429</a>         <a href="ident?i=u8">u8</a> num_sack_blocks;     <b><i>/* number of SACK blocks to include */</i></b>
<a name="L430" href="source/net/ipv4/tcp_output.c#L430">430</a>         <a href="ident?i=u8">u8</a> hash_size;           <b><i>/* bytes in hash_location */</i></b>
<a name="L431" href="source/net/ipv4/tcp_output.c#L431">431</a>         <a href="ident?i=__u8">__u8</a> *hash_location;    <b><i>/* temporary pointer, overloaded */</i></b>
<a name="L432" href="source/net/ipv4/tcp_output.c#L432">432</a>         <a href="ident?i=__u32">__u32</a> tsval, tsecr;     <b><i>/* need to include OPTION_TS */</i></b>
<a name="L433" href="source/net/ipv4/tcp_output.c#L433">433</a>         struct <a href="ident?i=tcp_fastopen_cookie">tcp_fastopen_cookie</a> *fastopen_cookie;    <b><i>/* Fast open cookie */</i></b>
<a name="L434" href="source/net/ipv4/tcp_output.c#L434">434</a> };
<a name="L435" href="source/net/ipv4/tcp_output.c#L435">435</a> 
<a name="L436" href="source/net/ipv4/tcp_output.c#L436">436</a> <b><i>/* Write previously computed TCP options to the packet.</i></b>
<a name="L437" href="source/net/ipv4/tcp_output.c#L437">437</a> <b><i> *</i></b>
<a name="L438" href="source/net/ipv4/tcp_output.c#L438">438</a> <b><i> * Beware: Something in the Internet is very sensitive to the ordering of</i></b>
<a name="L439" href="source/net/ipv4/tcp_output.c#L439">439</a> <b><i> * TCP options, we learned this through the hard way, so be careful here.</i></b>
<a name="L440" href="source/net/ipv4/tcp_output.c#L440">440</a> <b><i> * Luckily we can at least blame others for their non-compliance but from</i></b>
<a name="L441" href="source/net/ipv4/tcp_output.c#L441">441</a> <b><i> * inter-operability perspective it seems that we're somewhat stuck with</i></b>
<a name="L442" href="source/net/ipv4/tcp_output.c#L442">442</a> <b><i> * the ordering which we have been using if we want to keep working with</i></b>
<a name="L443" href="source/net/ipv4/tcp_output.c#L443">443</a> <b><i> * those broken things (not that it currently hurts anybody as there isn't</i></b>
<a name="L444" href="source/net/ipv4/tcp_output.c#L444">444</a> <b><i> * particular reason why the ordering would need to be changed).</i></b>
<a name="L445" href="source/net/ipv4/tcp_output.c#L445">445</a> <b><i> *</i></b>
<a name="L446" href="source/net/ipv4/tcp_output.c#L446">446</a> <b><i> * At least SACK_PERM as the first option is known to lead to a disaster</i></b>
<a name="L447" href="source/net/ipv4/tcp_output.c#L447">447</a> <b><i> * (but it may well be that other scenarios fail similarly).</i></b>
<a name="L448" href="source/net/ipv4/tcp_output.c#L448">448</a> <b><i> */</i></b>
<a name="L449" href="source/net/ipv4/tcp_output.c#L449">449</a> static void <a href="ident?i=tcp_options_write">tcp_options_write</a>(<a href="ident?i=__be32">__be32</a> *<a href="ident?i=ptr">ptr</a>, struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a>,
<a name="L450" href="source/net/ipv4/tcp_output.c#L450">450</a>                               struct <a href="ident?i=tcp_out_options">tcp_out_options</a> *<a href="ident?i=opts">opts</a>)
<a name="L451" href="source/net/ipv4/tcp_output.c#L451">451</a> {
<a name="L452" href="source/net/ipv4/tcp_output.c#L452">452</a>         <a href="ident?i=u16">u16</a> <a href="ident?i=options">options</a> = <a href="ident?i=opts">opts</a>-&gt;<a href="ident?i=options">options</a>;    <b><i>/* mungable copy */</i></b>
<a name="L453" href="source/net/ipv4/tcp_output.c#L453">453</a> 
<a name="L454" href="source/net/ipv4/tcp_output.c#L454">454</a>         if (<a href="ident?i=unlikely">unlikely</a>(<a href="ident?i=OPTION_MD5">OPTION_MD5</a> &amp; <a href="ident?i=options">options</a>)) {
<a name="L455" href="source/net/ipv4/tcp_output.c#L455">455</a>                 *<a href="ident?i=ptr">ptr</a>++ = <a href="ident?i=htonl">htonl</a>((<a href="ident?i=TCPOPT_NOP">TCPOPT_NOP</a> &lt;&lt; 24) | (<a href="ident?i=TCPOPT_NOP">TCPOPT_NOP</a> &lt;&lt; 16) |
<a name="L456" href="source/net/ipv4/tcp_output.c#L456">456</a>                                (<a href="ident?i=TCPOPT_MD5SIG">TCPOPT_MD5SIG</a> &lt;&lt; 8) | <a href="ident?i=TCPOLEN_MD5SIG">TCPOLEN_MD5SIG</a>);
<a name="L457" href="source/net/ipv4/tcp_output.c#L457">457</a>                 <b><i>/* overload cookie hash location */</i></b>
<a name="L458" href="source/net/ipv4/tcp_output.c#L458">458</a>                 <a href="ident?i=opts">opts</a>-&gt;hash_location = (<a href="ident?i=__u8">__u8</a> *)<a href="ident?i=ptr">ptr</a>;
<a name="L459" href="source/net/ipv4/tcp_output.c#L459">459</a>                 <a href="ident?i=ptr">ptr</a> += 4;
<a name="L460" href="source/net/ipv4/tcp_output.c#L460">460</a>         }
<a name="L461" href="source/net/ipv4/tcp_output.c#L461">461</a> 
<a name="L462" href="source/net/ipv4/tcp_output.c#L462">462</a>         if (<a href="ident?i=unlikely">unlikely</a>(<a href="ident?i=opts">opts</a>-&gt;mss)) {
<a name="L463" href="source/net/ipv4/tcp_output.c#L463">463</a>                 *<a href="ident?i=ptr">ptr</a>++ = <a href="ident?i=htonl">htonl</a>((<a href="ident?i=TCPOPT_MSS">TCPOPT_MSS</a> &lt;&lt; 24) |
<a name="L464" href="source/net/ipv4/tcp_output.c#L464">464</a>                                (<a href="ident?i=TCPOLEN_MSS">TCPOLEN_MSS</a> &lt;&lt; 16) |
<a name="L465" href="source/net/ipv4/tcp_output.c#L465">465</a>                                <a href="ident?i=opts">opts</a>-&gt;mss);
<a name="L466" href="source/net/ipv4/tcp_output.c#L466">466</a>         }
<a name="L467" href="source/net/ipv4/tcp_output.c#L467">467</a> 
<a name="L468" href="source/net/ipv4/tcp_output.c#L468">468</a>         if (<a href="ident?i=likely">likely</a>(<a href="ident?i=OPTION_TS">OPTION_TS</a> &amp; <a href="ident?i=options">options</a>)) {
<a name="L469" href="source/net/ipv4/tcp_output.c#L469">469</a>                 if (<a href="ident?i=unlikely">unlikely</a>(<a href="ident?i=OPTION_SACK_ADVERTISE">OPTION_SACK_ADVERTISE</a> &amp; <a href="ident?i=options">options</a>)) {
<a name="L470" href="source/net/ipv4/tcp_output.c#L470">470</a>                         *<a href="ident?i=ptr">ptr</a>++ = <a href="ident?i=htonl">htonl</a>((<a href="ident?i=TCPOPT_SACK_PERM">TCPOPT_SACK_PERM</a> &lt;&lt; 24) |
<a name="L471" href="source/net/ipv4/tcp_output.c#L471">471</a>                                        (<a href="ident?i=TCPOLEN_SACK_PERM">TCPOLEN_SACK_PERM</a> &lt;&lt; 16) |
<a name="L472" href="source/net/ipv4/tcp_output.c#L472">472</a>                                        (<a href="ident?i=TCPOPT_TIMESTAMP">TCPOPT_TIMESTAMP</a> &lt;&lt; 8) |
<a name="L473" href="source/net/ipv4/tcp_output.c#L473">473</a>                                        <a href="ident?i=TCPOLEN_TIMESTAMP">TCPOLEN_TIMESTAMP</a>);
<a name="L474" href="source/net/ipv4/tcp_output.c#L474">474</a>                         <a href="ident?i=options">options</a> &amp;= ~OPTION_SACK_ADVERTISE;
<a name="L475" href="source/net/ipv4/tcp_output.c#L475">475</a>                 } else {
<a name="L476" href="source/net/ipv4/tcp_output.c#L476">476</a>                         *<a href="ident?i=ptr">ptr</a>++ = <a href="ident?i=htonl">htonl</a>((<a href="ident?i=TCPOPT_NOP">TCPOPT_NOP</a> &lt;&lt; 24) |
<a name="L477" href="source/net/ipv4/tcp_output.c#L477">477</a>                                        (<a href="ident?i=TCPOPT_NOP">TCPOPT_NOP</a> &lt;&lt; 16) |
<a name="L478" href="source/net/ipv4/tcp_output.c#L478">478</a>                                        (<a href="ident?i=TCPOPT_TIMESTAMP">TCPOPT_TIMESTAMP</a> &lt;&lt; 8) |
<a name="L479" href="source/net/ipv4/tcp_output.c#L479">479</a>                                        <a href="ident?i=TCPOLEN_TIMESTAMP">TCPOLEN_TIMESTAMP</a>);
<a name="L480" href="source/net/ipv4/tcp_output.c#L480">480</a>                 }
<a name="L481" href="source/net/ipv4/tcp_output.c#L481">481</a>                 *<a href="ident?i=ptr">ptr</a>++ = <a href="ident?i=htonl">htonl</a>(<a href="ident?i=opts">opts</a>-&gt;tsval);
<a name="L482" href="source/net/ipv4/tcp_output.c#L482">482</a>                 *<a href="ident?i=ptr">ptr</a>++ = <a href="ident?i=htonl">htonl</a>(<a href="ident?i=opts">opts</a>-&gt;tsecr);
<a name="L483" href="source/net/ipv4/tcp_output.c#L483">483</a>         }
<a name="L484" href="source/net/ipv4/tcp_output.c#L484">484</a> 
<a name="L485" href="source/net/ipv4/tcp_output.c#L485">485</a>         if (<a href="ident?i=unlikely">unlikely</a>(<a href="ident?i=OPTION_SACK_ADVERTISE">OPTION_SACK_ADVERTISE</a> &amp; <a href="ident?i=options">options</a>)) {
<a name="L486" href="source/net/ipv4/tcp_output.c#L486">486</a>                 *<a href="ident?i=ptr">ptr</a>++ = <a href="ident?i=htonl">htonl</a>((<a href="ident?i=TCPOPT_NOP">TCPOPT_NOP</a> &lt;&lt; 24) |
<a name="L487" href="source/net/ipv4/tcp_output.c#L487">487</a>                                (<a href="ident?i=TCPOPT_NOP">TCPOPT_NOP</a> &lt;&lt; 16) |
<a name="L488" href="source/net/ipv4/tcp_output.c#L488">488</a>                                (<a href="ident?i=TCPOPT_SACK_PERM">TCPOPT_SACK_PERM</a> &lt;&lt; 8) |
<a name="L489" href="source/net/ipv4/tcp_output.c#L489">489</a>                                <a href="ident?i=TCPOLEN_SACK_PERM">TCPOLEN_SACK_PERM</a>);
<a name="L490" href="source/net/ipv4/tcp_output.c#L490">490</a>         }
<a name="L491" href="source/net/ipv4/tcp_output.c#L491">491</a> 
<a name="L492" href="source/net/ipv4/tcp_output.c#L492">492</a>         if (<a href="ident?i=unlikely">unlikely</a>(<a href="ident?i=OPTION_WSCALE">OPTION_WSCALE</a> &amp; <a href="ident?i=options">options</a>)) {
<a name="L493" href="source/net/ipv4/tcp_output.c#L493">493</a>                 *<a href="ident?i=ptr">ptr</a>++ = <a href="ident?i=htonl">htonl</a>((<a href="ident?i=TCPOPT_NOP">TCPOPT_NOP</a> &lt;&lt; 24) |
<a name="L494" href="source/net/ipv4/tcp_output.c#L494">494</a>                                (<a href="ident?i=TCPOPT_WINDOW">TCPOPT_WINDOW</a> &lt;&lt; 16) |
<a name="L495" href="source/net/ipv4/tcp_output.c#L495">495</a>                                (<a href="ident?i=TCPOLEN_WINDOW">TCPOLEN_WINDOW</a> &lt;&lt; 8) |
<a name="L496" href="source/net/ipv4/tcp_output.c#L496">496</a>                                <a href="ident?i=opts">opts</a>-&gt;<a href="ident?i=ws">ws</a>);
<a name="L497" href="source/net/ipv4/tcp_output.c#L497">497</a>         }
<a name="L498" href="source/net/ipv4/tcp_output.c#L498">498</a> 
<a name="L499" href="source/net/ipv4/tcp_output.c#L499">499</a>         if (<a href="ident?i=unlikely">unlikely</a>(<a href="ident?i=opts">opts</a>-&gt;num_sack_blocks)) {
<a name="L500" href="source/net/ipv4/tcp_output.c#L500">500</a>                 struct <a href="ident?i=tcp_sack_block">tcp_sack_block</a> *<a href="ident?i=sp">sp</a> = <a href="ident?i=tp">tp</a>-&gt;rx_opt.dsack ?
<a name="L501" href="source/net/ipv4/tcp_output.c#L501">501</a>                         <a href="ident?i=tp">tp</a>-&gt;duplicate_sack : <a href="ident?i=tp">tp</a>-&gt;selective_acks;
<a name="L502" href="source/net/ipv4/tcp_output.c#L502">502</a>                 int this_sack;
<a name="L503" href="source/net/ipv4/tcp_output.c#L503">503</a> 
<a name="L504" href="source/net/ipv4/tcp_output.c#L504">504</a>                 *<a href="ident?i=ptr">ptr</a>++ = <a href="ident?i=htonl">htonl</a>((<a href="ident?i=TCPOPT_NOP">TCPOPT_NOP</a>  &lt;&lt; 24) |
<a name="L505" href="source/net/ipv4/tcp_output.c#L505">505</a>                                (<a href="ident?i=TCPOPT_NOP">TCPOPT_NOP</a>  &lt;&lt; 16) |
<a name="L506" href="source/net/ipv4/tcp_output.c#L506">506</a>                                (<a href="ident?i=TCPOPT_SACK">TCPOPT_SACK</a> &lt;&lt;  8) |
<a name="L507" href="source/net/ipv4/tcp_output.c#L507">507</a>                                (<a href="ident?i=TCPOLEN_SACK_BASE">TCPOLEN_SACK_BASE</a> + (<a href="ident?i=opts">opts</a>-&gt;num_sack_blocks *
<a name="L508" href="source/net/ipv4/tcp_output.c#L508">508</a>                                                      <a href="ident?i=TCPOLEN_SACK_PERBLOCK">TCPOLEN_SACK_PERBLOCK</a>)));
<a name="L509" href="source/net/ipv4/tcp_output.c#L509">509</a> 
<a name="L510" href="source/net/ipv4/tcp_output.c#L510">510</a>                 for (this_sack = 0; this_sack &lt; <a href="ident?i=opts">opts</a>-&gt;num_sack_blocks;
<a name="L511" href="source/net/ipv4/tcp_output.c#L511">511</a>                      ++this_sack) {
<a name="L512" href="source/net/ipv4/tcp_output.c#L512">512</a>                         *<a href="ident?i=ptr">ptr</a>++ = <a href="ident?i=htonl">htonl</a>(<a href="ident?i=sp">sp</a>[this_sack].<a href="ident?i=start_seq">start_seq</a>);
<a name="L513" href="source/net/ipv4/tcp_output.c#L513">513</a>                         *<a href="ident?i=ptr">ptr</a>++ = <a href="ident?i=htonl">htonl</a>(<a href="ident?i=sp">sp</a>[this_sack].end_seq);
<a name="L514" href="source/net/ipv4/tcp_output.c#L514">514</a>                 }
<a name="L515" href="source/net/ipv4/tcp_output.c#L515">515</a> 
<a name="L516" href="source/net/ipv4/tcp_output.c#L516">516</a>                 <a href="ident?i=tp">tp</a>-&gt;rx_opt.dsack = 0;
<a name="L517" href="source/net/ipv4/tcp_output.c#L517">517</a>         }
<a name="L518" href="source/net/ipv4/tcp_output.c#L518">518</a> 
<a name="L519" href="source/net/ipv4/tcp_output.c#L519">519</a>         if (<a href="ident?i=unlikely">unlikely</a>(<a href="ident?i=OPTION_FAST_OPEN_COOKIE">OPTION_FAST_OPEN_COOKIE</a> &amp; <a href="ident?i=options">options</a>)) {
<a name="L520" href="source/net/ipv4/tcp_output.c#L520">520</a>                 struct <a href="ident?i=tcp_fastopen_cookie">tcp_fastopen_cookie</a> *foc = <a href="ident?i=opts">opts</a>-&gt;fastopen_cookie;
<a name="L521" href="source/net/ipv4/tcp_output.c#L521">521</a>                 <a href="ident?i=u8">u8</a> *<a href="ident?i=p">p</a> = (<a href="ident?i=u8">u8</a> *)<a href="ident?i=ptr">ptr</a>;
<a name="L522" href="source/net/ipv4/tcp_output.c#L522">522</a>                 <a href="ident?i=u32">u32</a> <a href="ident?i=len">len</a>; <b><i>/* Fast Open option length */</i></b>
<a name="L523" href="source/net/ipv4/tcp_output.c#L523">523</a> 
<a name="L524" href="source/net/ipv4/tcp_output.c#L524">524</a>                 if (foc-&gt;exp) {
<a name="L525" href="source/net/ipv4/tcp_output.c#L525">525</a>                         <a href="ident?i=len">len</a> = <a href="ident?i=TCPOLEN_EXP_FASTOPEN_BASE">TCPOLEN_EXP_FASTOPEN_BASE</a> + foc-&gt;<a href="ident?i=len">len</a>;
<a name="L526" href="source/net/ipv4/tcp_output.c#L526">526</a>                         *<a href="ident?i=ptr">ptr</a> = <a href="ident?i=htonl">htonl</a>((<a href="ident?i=TCPOPT_EXP">TCPOPT_EXP</a> &lt;&lt; 24) | (<a href="ident?i=len">len</a> &lt;&lt; 16) |
<a name="L527" href="source/net/ipv4/tcp_output.c#L527">527</a>                                      <a href="ident?i=TCPOPT_FASTOPEN_MAGIC">TCPOPT_FASTOPEN_MAGIC</a>);
<a name="L528" href="source/net/ipv4/tcp_output.c#L528">528</a>                         <a href="ident?i=p">p</a> += <a href="ident?i=TCPOLEN_EXP_FASTOPEN_BASE">TCPOLEN_EXP_FASTOPEN_BASE</a>;
<a name="L529" href="source/net/ipv4/tcp_output.c#L529">529</a>                 } else {
<a name="L530" href="source/net/ipv4/tcp_output.c#L530">530</a>                         <a href="ident?i=len">len</a> = <a href="ident?i=TCPOLEN_FASTOPEN_BASE">TCPOLEN_FASTOPEN_BASE</a> + foc-&gt;<a href="ident?i=len">len</a>;
<a name="L531" href="source/net/ipv4/tcp_output.c#L531">531</a>                         *<a href="ident?i=p">p</a>++ = <a href="ident?i=TCPOPT_FASTOPEN">TCPOPT_FASTOPEN</a>;
<a name="L532" href="source/net/ipv4/tcp_output.c#L532">532</a>                         *<a href="ident?i=p">p</a>++ = <a href="ident?i=len">len</a>;
<a name="L533" href="source/net/ipv4/tcp_output.c#L533">533</a>                 }
<a name="L534" href="source/net/ipv4/tcp_output.c#L534">534</a> 
<a name="L535" href="source/net/ipv4/tcp_output.c#L535">535</a>                 <a href="ident?i=memcpy">memcpy</a>(<a href="ident?i=p">p</a>, foc-&gt;<a href="ident?i=val">val</a>, foc-&gt;<a href="ident?i=len">len</a>);
<a name="L536" href="source/net/ipv4/tcp_output.c#L536">536</a>                 if ((<a href="ident?i=len">len</a> &amp; 3) == 2) {
<a name="L537" href="source/net/ipv4/tcp_output.c#L537">537</a>                         <a href="ident?i=p">p</a>[foc-&gt;<a href="ident?i=len">len</a>] = <a href="ident?i=TCPOPT_NOP">TCPOPT_NOP</a>;
<a name="L538" href="source/net/ipv4/tcp_output.c#L538">538</a>                         <a href="ident?i=p">p</a>[foc-&gt;<a href="ident?i=len">len</a> + 1] = <a href="ident?i=TCPOPT_NOP">TCPOPT_NOP</a>;
<a name="L539" href="source/net/ipv4/tcp_output.c#L539">539</a>                 }
<a name="L540" href="source/net/ipv4/tcp_output.c#L540">540</a>                 <a href="ident?i=ptr">ptr</a> += (<a href="ident?i=len">len</a> + 3) &gt;&gt; 2;
<a name="L541" href="source/net/ipv4/tcp_output.c#L541">541</a>         }
<a name="L542" href="source/net/ipv4/tcp_output.c#L542">542</a> }
<a name="L543" href="source/net/ipv4/tcp_output.c#L543">543</a> 
<a name="L544" href="source/net/ipv4/tcp_output.c#L544">544</a> <b><i>/* Compute TCP options for SYN packets. This is not the final</i></b>
<a name="L545" href="source/net/ipv4/tcp_output.c#L545">545</a> <b><i> * network wire format yet.</i></b>
<a name="L546" href="source/net/ipv4/tcp_output.c#L546">546</a> <b><i> */</i></b>
<a name="L547" href="source/net/ipv4/tcp_output.c#L547">547</a> static unsigned int <a href="ident?i=tcp_syn_options">tcp_syn_options</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
<a name="L548" href="source/net/ipv4/tcp_output.c#L548">548</a>                                 struct <a href="ident?i=tcp_out_options">tcp_out_options</a> *<a href="ident?i=opts">opts</a>,
<a name="L549" href="source/net/ipv4/tcp_output.c#L549">549</a>                                 struct <a href="ident?i=tcp_md5sig_key">tcp_md5sig_key</a> **md5)
<a name="L550" href="source/net/ipv4/tcp_output.c#L550">550</a> {
<a name="L551" href="source/net/ipv4/tcp_output.c#L551">551</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L552" href="source/net/ipv4/tcp_output.c#L552">552</a>         unsigned int <a href="ident?i=remaining">remaining</a> = <a href="ident?i=MAX_TCP_OPTION_SPACE">MAX_TCP_OPTION_SPACE</a>;
<a name="L553" href="source/net/ipv4/tcp_output.c#L553">553</a>         struct <a href="ident?i=tcp_fastopen_request">tcp_fastopen_request</a> *fastopen = <a href="ident?i=tp">tp</a>-&gt;fastopen_req;
<a name="L554" href="source/net/ipv4/tcp_output.c#L554">554</a> 
<a name="L555" href="source/net/ipv4/tcp_output.c#L555">555</a> #ifdef CONFIG_TCP_MD5SIG
<a name="L556" href="source/net/ipv4/tcp_output.c#L556">556</a>         *md5 = <a href="ident?i=tp">tp</a>-&gt;af_specific-&gt;md5_lookup(sk, sk);
<a name="L557" href="source/net/ipv4/tcp_output.c#L557">557</a>         if (*md5) {
<a name="L558" href="source/net/ipv4/tcp_output.c#L558">558</a>                 <a href="ident?i=opts">opts</a>-&gt;<a href="ident?i=options">options</a> |= <a href="ident?i=OPTION_MD5">OPTION_MD5</a>;
<a name="L559" href="source/net/ipv4/tcp_output.c#L559">559</a>                 <a href="ident?i=remaining">remaining</a> -= <a href="ident?i=TCPOLEN_MD5SIG_ALIGNED">TCPOLEN_MD5SIG_ALIGNED</a>;
<a name="L560" href="source/net/ipv4/tcp_output.c#L560">560</a>         }
<a name="L561" href="source/net/ipv4/tcp_output.c#L561">561</a> #else
<a name="L562" href="source/net/ipv4/tcp_output.c#L562">562</a>         *md5 = <a href="ident?i=NULL">NULL</a>;
<a name="L563" href="source/net/ipv4/tcp_output.c#L563">563</a> #endif
<a name="L564" href="source/net/ipv4/tcp_output.c#L564">564</a> 
<a name="L565" href="source/net/ipv4/tcp_output.c#L565">565</a>         <b><i>/* We always get an MSS option.  The option bytes which will be seen in</i></b>
<a name="L566" href="source/net/ipv4/tcp_output.c#L566">566</a> <b><i>         * normal data packets should timestamps be used, must be in the MSS</i></b>
<a name="L567" href="source/net/ipv4/tcp_output.c#L567">567</a> <b><i>         * advertised.  But we subtract them from tp-&gt;mss_cache so that</i></b>
<a name="L568" href="source/net/ipv4/tcp_output.c#L568">568</a> <b><i>         * calculations in tcp_sendmsg are simpler etc.  So account for this</i></b>
<a name="L569" href="source/net/ipv4/tcp_output.c#L569">569</a> <b><i>         * fact here if necessary.  If we don't do this correctly, as a</i></b>
<a name="L570" href="source/net/ipv4/tcp_output.c#L570">570</a> <b><i>         * receiver we won't recognize data packets as being full sized when we</i></b>
<a name="L571" href="source/net/ipv4/tcp_output.c#L571">571</a> <b><i>         * should, and thus we won't abide by the delayed ACK rules correctly.</i></b>
<a name="L572" href="source/net/ipv4/tcp_output.c#L572">572</a> <b><i>         * SACKs don't matter, we never delay an ACK when we have any of those</i></b>
<a name="L573" href="source/net/ipv4/tcp_output.c#L573">573</a> <b><i>         * going out.  */</i></b>
<a name="L574" href="source/net/ipv4/tcp_output.c#L574">574</a>         <a href="ident?i=opts">opts</a>-&gt;mss = <a href="ident?i=tcp_advertise_mss">tcp_advertise_mss</a>(sk);
<a name="L575" href="source/net/ipv4/tcp_output.c#L575">575</a>         <a href="ident?i=remaining">remaining</a> -= <a href="ident?i=TCPOLEN_MSS_ALIGNED">TCPOLEN_MSS_ALIGNED</a>;
<a name="L576" href="source/net/ipv4/tcp_output.c#L576">576</a> 
<a name="L577" href="source/net/ipv4/tcp_output.c#L577">577</a>         if (<a href="ident?i=likely">likely</a>(<a href="ident?i=sysctl_tcp_timestamps">sysctl_tcp_timestamps</a> &amp;&amp; !*md5)) {
<a name="L578" href="source/net/ipv4/tcp_output.c#L578">578</a>                 <a href="ident?i=opts">opts</a>-&gt;<a href="ident?i=options">options</a> |= <a href="ident?i=OPTION_TS">OPTION_TS</a>;
<a name="L579" href="source/net/ipv4/tcp_output.c#L579">579</a>                 <a href="ident?i=opts">opts</a>-&gt;tsval = <a href="ident?i=tcp_skb_timestamp">tcp_skb_timestamp</a>(<a href="ident?i=skb">skb</a>) + <a href="ident?i=tp">tp</a>-&gt;tsoffset;
<a name="L580" href="source/net/ipv4/tcp_output.c#L580">580</a>                 <a href="ident?i=opts">opts</a>-&gt;tsecr = <a href="ident?i=tp">tp</a>-&gt;rx_opt.ts_recent;
<a name="L581" href="source/net/ipv4/tcp_output.c#L581">581</a>                 <a href="ident?i=remaining">remaining</a> -= <a href="ident?i=TCPOLEN_TSTAMP_ALIGNED">TCPOLEN_TSTAMP_ALIGNED</a>;
<a name="L582" href="source/net/ipv4/tcp_output.c#L582">582</a>         }
<a name="L583" href="source/net/ipv4/tcp_output.c#L583">583</a>         if (<a href="ident?i=likely">likely</a>(<a href="ident?i=sysctl_tcp_window_scaling">sysctl_tcp_window_scaling</a>)) {
<a name="L584" href="source/net/ipv4/tcp_output.c#L584">584</a>                 <a href="ident?i=opts">opts</a>-&gt;<a href="ident?i=ws">ws</a> = <a href="ident?i=tp">tp</a>-&gt;rx_opt.rcv_wscale;
<a name="L585" href="source/net/ipv4/tcp_output.c#L585">585</a>                 <a href="ident?i=opts">opts</a>-&gt;<a href="ident?i=options">options</a> |= <a href="ident?i=OPTION_WSCALE">OPTION_WSCALE</a>;
<a name="L586" href="source/net/ipv4/tcp_output.c#L586">586</a>                 <a href="ident?i=remaining">remaining</a> -= <a href="ident?i=TCPOLEN_WSCALE_ALIGNED">TCPOLEN_WSCALE_ALIGNED</a>;
<a name="L587" href="source/net/ipv4/tcp_output.c#L587">587</a>         }
<a name="L588" href="source/net/ipv4/tcp_output.c#L588">588</a>         if (<a href="ident?i=likely">likely</a>(<a href="ident?i=sysctl_tcp_sack">sysctl_tcp_sack</a>)) {
<a name="L589" href="source/net/ipv4/tcp_output.c#L589">589</a>                 <a href="ident?i=opts">opts</a>-&gt;<a href="ident?i=options">options</a> |= <a href="ident?i=OPTION_SACK_ADVERTISE">OPTION_SACK_ADVERTISE</a>;
<a name="L590" href="source/net/ipv4/tcp_output.c#L590">590</a>                 if (<a href="ident?i=unlikely">unlikely</a>(!(<a href="ident?i=OPTION_TS">OPTION_TS</a> &amp; <a href="ident?i=opts">opts</a>-&gt;<a href="ident?i=options">options</a>)))
<a name="L591" href="source/net/ipv4/tcp_output.c#L591">591</a>                         <a href="ident?i=remaining">remaining</a> -= <a href="ident?i=TCPOLEN_SACKPERM_ALIGNED">TCPOLEN_SACKPERM_ALIGNED</a>;
<a name="L592" href="source/net/ipv4/tcp_output.c#L592">592</a>         }
<a name="L593" href="source/net/ipv4/tcp_output.c#L593">593</a> 
<a name="L594" href="source/net/ipv4/tcp_output.c#L594">594</a>         if (fastopen &amp;&amp; fastopen-&gt;cookie.<a href="ident?i=len">len</a> &gt;= 0) {
<a name="L595" href="source/net/ipv4/tcp_output.c#L595">595</a>                 <a href="ident?i=u32">u32</a> need = fastopen-&gt;cookie.<a href="ident?i=len">len</a>;
<a name="L596" href="source/net/ipv4/tcp_output.c#L596">596</a> 
<a name="L597" href="source/net/ipv4/tcp_output.c#L597">597</a>                 need += fastopen-&gt;cookie.exp ? <a href="ident?i=TCPOLEN_EXP_FASTOPEN_BASE">TCPOLEN_EXP_FASTOPEN_BASE</a> :
<a name="L598" href="source/net/ipv4/tcp_output.c#L598">598</a>                                                <a href="ident?i=TCPOLEN_FASTOPEN_BASE">TCPOLEN_FASTOPEN_BASE</a>;
<a name="L599" href="source/net/ipv4/tcp_output.c#L599">599</a>                 need = (need + 3) &amp; ~3U;  <b><i>/* Align to 32 bits */</i></b>
<a name="L600" href="source/net/ipv4/tcp_output.c#L600">600</a>                 if (<a href="ident?i=remaining">remaining</a> &gt;= need) {
<a name="L601" href="source/net/ipv4/tcp_output.c#L601">601</a>                         <a href="ident?i=opts">opts</a>-&gt;<a href="ident?i=options">options</a> |= <a href="ident?i=OPTION_FAST_OPEN_COOKIE">OPTION_FAST_OPEN_COOKIE</a>;
<a name="L602" href="source/net/ipv4/tcp_output.c#L602">602</a>                         <a href="ident?i=opts">opts</a>-&gt;fastopen_cookie = &amp;fastopen-&gt;cookie;
<a name="L603" href="source/net/ipv4/tcp_output.c#L603">603</a>                         <a href="ident?i=remaining">remaining</a> -= need;
<a name="L604" href="source/net/ipv4/tcp_output.c#L604">604</a>                         <a href="ident?i=tp">tp</a>-&gt;syn_fastopen = 1;
<a name="L605" href="source/net/ipv4/tcp_output.c#L605">605</a>                         <a href="ident?i=tp">tp</a>-&gt;syn_fastopen_exp = fastopen-&gt;cookie.exp ? 1 : 0;
<a name="L606" href="source/net/ipv4/tcp_output.c#L606">606</a>                 }
<a name="L607" href="source/net/ipv4/tcp_output.c#L607">607</a>         }
<a name="L608" href="source/net/ipv4/tcp_output.c#L608">608</a> 
<a name="L609" href="source/net/ipv4/tcp_output.c#L609">609</a>         return <a href="ident?i=MAX_TCP_OPTION_SPACE">MAX_TCP_OPTION_SPACE</a> - <a href="ident?i=remaining">remaining</a>;
<a name="L610" href="source/net/ipv4/tcp_output.c#L610">610</a> }
<a name="L611" href="source/net/ipv4/tcp_output.c#L611">611</a> 
<a name="L612" href="source/net/ipv4/tcp_output.c#L612">612</a> <b><i>/* Set up TCP options for SYN-ACKs. */</i></b>
<a name="L613" href="source/net/ipv4/tcp_output.c#L613">613</a> static unsigned int <a href="ident?i=tcp_synack_options">tcp_synack_options</a>(struct <a href="ident?i=sock">sock</a> *sk,
<a name="L614" href="source/net/ipv4/tcp_output.c#L614">614</a>                                    struct <a href="ident?i=request_sock">request_sock</a> *<a href="ident?i=req">req</a>,
<a name="L615" href="source/net/ipv4/tcp_output.c#L615">615</a>                                    unsigned int mss, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
<a name="L616" href="source/net/ipv4/tcp_output.c#L616">616</a>                                    struct <a href="ident?i=tcp_out_options">tcp_out_options</a> *<a href="ident?i=opts">opts</a>,
<a name="L617" href="source/net/ipv4/tcp_output.c#L617">617</a>                                    const struct <a href="ident?i=tcp_md5sig_key">tcp_md5sig_key</a> *md5,
<a name="L618" href="source/net/ipv4/tcp_output.c#L618">618</a>                                    struct <a href="ident?i=tcp_fastopen_cookie">tcp_fastopen_cookie</a> *foc)
<a name="L619" href="source/net/ipv4/tcp_output.c#L619">619</a> {
<a name="L620" href="source/net/ipv4/tcp_output.c#L620">620</a>         struct <a href="ident?i=inet_request_sock">inet_request_sock</a> *ireq = <a href="ident?i=inet_rsk">inet_rsk</a>(<a href="ident?i=req">req</a>);
<a name="L621" href="source/net/ipv4/tcp_output.c#L621">621</a>         unsigned int <a href="ident?i=remaining">remaining</a> = <a href="ident?i=MAX_TCP_OPTION_SPACE">MAX_TCP_OPTION_SPACE</a>;
<a name="L622" href="source/net/ipv4/tcp_output.c#L622">622</a> 
<a name="L623" href="source/net/ipv4/tcp_output.c#L623">623</a> #ifdef CONFIG_TCP_MD5SIG
<a name="L624" href="source/net/ipv4/tcp_output.c#L624">624</a>         if (md5) {
<a name="L625" href="source/net/ipv4/tcp_output.c#L625">625</a>                 <a href="ident?i=opts">opts</a>-&gt;<a href="ident?i=options">options</a> |= <a href="ident?i=OPTION_MD5">OPTION_MD5</a>;
<a name="L626" href="source/net/ipv4/tcp_output.c#L626">626</a>                 <a href="ident?i=remaining">remaining</a> -= <a href="ident?i=TCPOLEN_MD5SIG_ALIGNED">TCPOLEN_MD5SIG_ALIGNED</a>;
<a name="L627" href="source/net/ipv4/tcp_output.c#L627">627</a> 
<a name="L628" href="source/net/ipv4/tcp_output.c#L628">628</a>                 <b><i>/* We can't fit any SACK blocks in a packet with MD5 + TS</i></b>
<a name="L629" href="source/net/ipv4/tcp_output.c#L629">629</a> <b><i>                 * options. There was discussion about disabling SACK</i></b>
<a name="L630" href="source/net/ipv4/tcp_output.c#L630">630</a> <b><i>                 * rather than TS in order to fit in better with old,</i></b>
<a name="L631" href="source/net/ipv4/tcp_output.c#L631">631</a> <b><i>                 * buggy kernels, but that was deemed to be unnecessary.</i></b>
<a name="L632" href="source/net/ipv4/tcp_output.c#L632">632</a> <b><i>                 */</i></b>
<a name="L633" href="source/net/ipv4/tcp_output.c#L633">633</a>                 ireq-&gt;tstamp_ok &amp;= !ireq-&gt;sack_ok;
<a name="L634" href="source/net/ipv4/tcp_output.c#L634">634</a>         }
<a name="L635" href="source/net/ipv4/tcp_output.c#L635">635</a> #endif
<a name="L636" href="source/net/ipv4/tcp_output.c#L636">636</a> 
<a name="L637" href="source/net/ipv4/tcp_output.c#L637">637</a>         <b><i>/* We always send an MSS option. */</i></b>
<a name="L638" href="source/net/ipv4/tcp_output.c#L638">638</a>         <a href="ident?i=opts">opts</a>-&gt;mss = mss;
<a name="L639" href="source/net/ipv4/tcp_output.c#L639">639</a>         <a href="ident?i=remaining">remaining</a> -= <a href="ident?i=TCPOLEN_MSS_ALIGNED">TCPOLEN_MSS_ALIGNED</a>;
<a name="L640" href="source/net/ipv4/tcp_output.c#L640">640</a> 
<a name="L641" href="source/net/ipv4/tcp_output.c#L641">641</a>         if (<a href="ident?i=likely">likely</a>(ireq-&gt;wscale_ok)) {
<a name="L642" href="source/net/ipv4/tcp_output.c#L642">642</a>                 <a href="ident?i=opts">opts</a>-&gt;<a href="ident?i=ws">ws</a> = ireq-&gt;rcv_wscale;
<a name="L643" href="source/net/ipv4/tcp_output.c#L643">643</a>                 <a href="ident?i=opts">opts</a>-&gt;<a href="ident?i=options">options</a> |= <a href="ident?i=OPTION_WSCALE">OPTION_WSCALE</a>;
<a name="L644" href="source/net/ipv4/tcp_output.c#L644">644</a>                 <a href="ident?i=remaining">remaining</a> -= <a href="ident?i=TCPOLEN_WSCALE_ALIGNED">TCPOLEN_WSCALE_ALIGNED</a>;
<a name="L645" href="source/net/ipv4/tcp_output.c#L645">645</a>         }
<a name="L646" href="source/net/ipv4/tcp_output.c#L646">646</a>         if (<a href="ident?i=likely">likely</a>(ireq-&gt;tstamp_ok)) {
<a name="L647" href="source/net/ipv4/tcp_output.c#L647">647</a>                 <a href="ident?i=opts">opts</a>-&gt;<a href="ident?i=options">options</a> |= <a href="ident?i=OPTION_TS">OPTION_TS</a>;
<a name="L648" href="source/net/ipv4/tcp_output.c#L648">648</a>                 <a href="ident?i=opts">opts</a>-&gt;tsval = <a href="ident?i=tcp_skb_timestamp">tcp_skb_timestamp</a>(<a href="ident?i=skb">skb</a>);
<a name="L649" href="source/net/ipv4/tcp_output.c#L649">649</a>                 <a href="ident?i=opts">opts</a>-&gt;tsecr = <a href="ident?i=req">req</a>-&gt;ts_recent;
<a name="L650" href="source/net/ipv4/tcp_output.c#L650">650</a>                 <a href="ident?i=remaining">remaining</a> -= <a href="ident?i=TCPOLEN_TSTAMP_ALIGNED">TCPOLEN_TSTAMP_ALIGNED</a>;
<a name="L651" href="source/net/ipv4/tcp_output.c#L651">651</a>         }
<a name="L652" href="source/net/ipv4/tcp_output.c#L652">652</a>         if (<a href="ident?i=likely">likely</a>(ireq-&gt;sack_ok)) {
<a name="L653" href="source/net/ipv4/tcp_output.c#L653">653</a>                 <a href="ident?i=opts">opts</a>-&gt;<a href="ident?i=options">options</a> |= <a href="ident?i=OPTION_SACK_ADVERTISE">OPTION_SACK_ADVERTISE</a>;
<a name="L654" href="source/net/ipv4/tcp_output.c#L654">654</a>                 if (<a href="ident?i=unlikely">unlikely</a>(!ireq-&gt;tstamp_ok))
<a name="L655" href="source/net/ipv4/tcp_output.c#L655">655</a>                         <a href="ident?i=remaining">remaining</a> -= <a href="ident?i=TCPOLEN_SACKPERM_ALIGNED">TCPOLEN_SACKPERM_ALIGNED</a>;
<a name="L656" href="source/net/ipv4/tcp_output.c#L656">656</a>         }
<a name="L657" href="source/net/ipv4/tcp_output.c#L657">657</a>         if (foc != <a href="ident?i=NULL">NULL</a> &amp;&amp; foc-&gt;<a href="ident?i=len">len</a> &gt;= 0) {
<a name="L658" href="source/net/ipv4/tcp_output.c#L658">658</a>                 <a href="ident?i=u32">u32</a> need = foc-&gt;<a href="ident?i=len">len</a>;
<a name="L659" href="source/net/ipv4/tcp_output.c#L659">659</a> 
<a name="L660" href="source/net/ipv4/tcp_output.c#L660">660</a>                 need += foc-&gt;exp ? <a href="ident?i=TCPOLEN_EXP_FASTOPEN_BASE">TCPOLEN_EXP_FASTOPEN_BASE</a> :
<a name="L661" href="source/net/ipv4/tcp_output.c#L661">661</a>                                    <a href="ident?i=TCPOLEN_FASTOPEN_BASE">TCPOLEN_FASTOPEN_BASE</a>;
<a name="L662" href="source/net/ipv4/tcp_output.c#L662">662</a>                 need = (need + 3) &amp; ~3U;  <b><i>/* Align to 32 bits */</i></b>
<a name="L663" href="source/net/ipv4/tcp_output.c#L663">663</a>                 if (<a href="ident?i=remaining">remaining</a> &gt;= need) {
<a name="L664" href="source/net/ipv4/tcp_output.c#L664">664</a>                         <a href="ident?i=opts">opts</a>-&gt;<a href="ident?i=options">options</a> |= <a href="ident?i=OPTION_FAST_OPEN_COOKIE">OPTION_FAST_OPEN_COOKIE</a>;
<a name="L665" href="source/net/ipv4/tcp_output.c#L665">665</a>                         <a href="ident?i=opts">opts</a>-&gt;fastopen_cookie = foc;
<a name="L666" href="source/net/ipv4/tcp_output.c#L666">666</a>                         <a href="ident?i=remaining">remaining</a> -= need;
<a name="L667" href="source/net/ipv4/tcp_output.c#L667">667</a>                 }
<a name="L668" href="source/net/ipv4/tcp_output.c#L668">668</a>         }
<a name="L669" href="source/net/ipv4/tcp_output.c#L669">669</a> 
<a name="L670" href="source/net/ipv4/tcp_output.c#L670">670</a>         return <a href="ident?i=MAX_TCP_OPTION_SPACE">MAX_TCP_OPTION_SPACE</a> - <a href="ident?i=remaining">remaining</a>;
<a name="L671" href="source/net/ipv4/tcp_output.c#L671">671</a> }
<a name="L672" href="source/net/ipv4/tcp_output.c#L672">672</a> 
<a name="L673" href="source/net/ipv4/tcp_output.c#L673">673</a> <b><i>/* Compute TCP options for ESTABLISHED sockets. This is not the</i></b>
<a name="L674" href="source/net/ipv4/tcp_output.c#L674">674</a> <b><i> * final wire format yet.</i></b>
<a name="L675" href="source/net/ipv4/tcp_output.c#L675">675</a> <b><i> */</i></b>
<a name="L676" href="source/net/ipv4/tcp_output.c#L676">676</a> static unsigned int <a href="ident?i=tcp_established_options">tcp_established_options</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
<a name="L677" href="source/net/ipv4/tcp_output.c#L677">677</a>                                         struct <a href="ident?i=tcp_out_options">tcp_out_options</a> *<a href="ident?i=opts">opts</a>,
<a name="L678" href="source/net/ipv4/tcp_output.c#L678">678</a>                                         struct <a href="ident?i=tcp_md5sig_key">tcp_md5sig_key</a> **md5)
<a name="L679" href="source/net/ipv4/tcp_output.c#L679">679</a> {
<a name="L680" href="source/net/ipv4/tcp_output.c#L680">680</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L681" href="source/net/ipv4/tcp_output.c#L681">681</a>         unsigned int <a href="ident?i=size">size</a> = 0;
<a name="L682" href="source/net/ipv4/tcp_output.c#L682">682</a>         unsigned int eff_sacks;
<a name="L683" href="source/net/ipv4/tcp_output.c#L683">683</a> 
<a name="L684" href="source/net/ipv4/tcp_output.c#L684">684</a>         <a href="ident?i=opts">opts</a>-&gt;<a href="ident?i=options">options</a> = 0;
<a name="L685" href="source/net/ipv4/tcp_output.c#L685">685</a> 
<a name="L686" href="source/net/ipv4/tcp_output.c#L686">686</a> #ifdef CONFIG_TCP_MD5SIG
<a name="L687" href="source/net/ipv4/tcp_output.c#L687">687</a>         *md5 = <a href="ident?i=tp">tp</a>-&gt;af_specific-&gt;md5_lookup(sk, sk);
<a name="L688" href="source/net/ipv4/tcp_output.c#L688">688</a>         if (<a href="ident?i=unlikely">unlikely</a>(*md5)) {
<a name="L689" href="source/net/ipv4/tcp_output.c#L689">689</a>                 <a href="ident?i=opts">opts</a>-&gt;<a href="ident?i=options">options</a> |= <a href="ident?i=OPTION_MD5">OPTION_MD5</a>;
<a name="L690" href="source/net/ipv4/tcp_output.c#L690">690</a>                 <a href="ident?i=size">size</a> += <a href="ident?i=TCPOLEN_MD5SIG_ALIGNED">TCPOLEN_MD5SIG_ALIGNED</a>;
<a name="L691" href="source/net/ipv4/tcp_output.c#L691">691</a>         }
<a name="L692" href="source/net/ipv4/tcp_output.c#L692">692</a> #else
<a name="L693" href="source/net/ipv4/tcp_output.c#L693">693</a>         *md5 = <a href="ident?i=NULL">NULL</a>;
<a name="L694" href="source/net/ipv4/tcp_output.c#L694">694</a> #endif
<a name="L695" href="source/net/ipv4/tcp_output.c#L695">695</a> 
<a name="L696" href="source/net/ipv4/tcp_output.c#L696">696</a>         if (<a href="ident?i=likely">likely</a>(<a href="ident?i=tp">tp</a>-&gt;rx_opt.tstamp_ok)) {
<a name="L697" href="source/net/ipv4/tcp_output.c#L697">697</a>                 <a href="ident?i=opts">opts</a>-&gt;<a href="ident?i=options">options</a> |= <a href="ident?i=OPTION_TS">OPTION_TS</a>;
<a name="L698" href="source/net/ipv4/tcp_output.c#L698">698</a>                 <a href="ident?i=opts">opts</a>-&gt;tsval = <a href="ident?i=skb">skb</a> ? <a href="ident?i=tcp_skb_timestamp">tcp_skb_timestamp</a>(<a href="ident?i=skb">skb</a>) + <a href="ident?i=tp">tp</a>-&gt;tsoffset : 0;
<a name="L699" href="source/net/ipv4/tcp_output.c#L699">699</a>                 <a href="ident?i=opts">opts</a>-&gt;tsecr = <a href="ident?i=tp">tp</a>-&gt;rx_opt.ts_recent;
<a name="L700" href="source/net/ipv4/tcp_output.c#L700">700</a>                 <a href="ident?i=size">size</a> += <a href="ident?i=TCPOLEN_TSTAMP_ALIGNED">TCPOLEN_TSTAMP_ALIGNED</a>;
<a name="L701" href="source/net/ipv4/tcp_output.c#L701">701</a>         }
<a name="L702" href="source/net/ipv4/tcp_output.c#L702">702</a> 
<a name="L703" href="source/net/ipv4/tcp_output.c#L703">703</a>         eff_sacks = <a href="ident?i=tp">tp</a>-&gt;rx_opt.num_sacks + <a href="ident?i=tp">tp</a>-&gt;rx_opt.dsack;
<a name="L704" href="source/net/ipv4/tcp_output.c#L704">704</a>         if (<a href="ident?i=unlikely">unlikely</a>(eff_sacks)) {
<a name="L705" href="source/net/ipv4/tcp_output.c#L705">705</a>                 const unsigned int <a href="ident?i=remaining">remaining</a> = <a href="ident?i=MAX_TCP_OPTION_SPACE">MAX_TCP_OPTION_SPACE</a> - <a href="ident?i=size">size</a>;
<a name="L706" href="source/net/ipv4/tcp_output.c#L706">706</a>                 <a href="ident?i=opts">opts</a>-&gt;num_sack_blocks =
<a name="L707" href="source/net/ipv4/tcp_output.c#L707">707</a>                         <a href="ident?i=min_t">min_t</a>(unsigned int, eff_sacks,
<a name="L708" href="source/net/ipv4/tcp_output.c#L708">708</a>                               (<a href="ident?i=remaining">remaining</a> - <a href="ident?i=TCPOLEN_SACK_BASE_ALIGNED">TCPOLEN_SACK_BASE_ALIGNED</a>) /
<a name="L709" href="source/net/ipv4/tcp_output.c#L709">709</a>                               <a href="ident?i=TCPOLEN_SACK_PERBLOCK">TCPOLEN_SACK_PERBLOCK</a>);
<a name="L710" href="source/net/ipv4/tcp_output.c#L710">710</a>                 <a href="ident?i=size">size</a> += <a href="ident?i=TCPOLEN_SACK_BASE_ALIGNED">TCPOLEN_SACK_BASE_ALIGNED</a> +
<a name="L711" href="source/net/ipv4/tcp_output.c#L711">711</a>                         <a href="ident?i=opts">opts</a>-&gt;num_sack_blocks * <a href="ident?i=TCPOLEN_SACK_PERBLOCK">TCPOLEN_SACK_PERBLOCK</a>;
<a name="L712" href="source/net/ipv4/tcp_output.c#L712">712</a>         }
<a name="L713" href="source/net/ipv4/tcp_output.c#L713">713</a> 
<a name="L714" href="source/net/ipv4/tcp_output.c#L714">714</a>         return <a href="ident?i=size">size</a>;
<a name="L715" href="source/net/ipv4/tcp_output.c#L715">715</a> }
<a name="L716" href="source/net/ipv4/tcp_output.c#L716">716</a> 
<a name="L717" href="source/net/ipv4/tcp_output.c#L717">717</a> 
<a name="L718" href="source/net/ipv4/tcp_output.c#L718">718</a> <b><i>/* TCP SMALL QUEUES (TSQ)</i></b>
<a name="L719" href="source/net/ipv4/tcp_output.c#L719">719</a> <b><i> *</i></b>
<a name="L720" href="source/net/ipv4/tcp_output.c#L720">720</a> <b><i> * TSQ goal is to keep small amount of skbs per tcp flow in tx queues (qdisc+dev)</i></b>
<a name="L721" href="source/net/ipv4/tcp_output.c#L721">721</a> <b><i> * to reduce RTT and bufferbloat.</i></b>
<a name="L722" href="source/net/ipv4/tcp_output.c#L722">722</a> <b><i> * We do this using a special skb destructor (tcp_wfree).</i></b>
<a name="L723" href="source/net/ipv4/tcp_output.c#L723">723</a> <b><i> *</i></b>
<a name="L724" href="source/net/ipv4/tcp_output.c#L724">724</a> <b><i> * Its important tcp_wfree() can be replaced by sock_wfree() in the event skb</i></b>
<a name="L725" href="source/net/ipv4/tcp_output.c#L725">725</a> <b><i> * needs to be reallocated in a driver.</i></b>
<a name="L726" href="source/net/ipv4/tcp_output.c#L726">726</a> <b><i> * The invariant being skb-&gt;truesize subtracted from sk-&gt;sk_wmem_alloc</i></b>
<a name="L727" href="source/net/ipv4/tcp_output.c#L727">727</a> <b><i> *</i></b>
<a name="L728" href="source/net/ipv4/tcp_output.c#L728">728</a> <b><i> * Since transmit from skb destructor is forbidden, we use a tasklet</i></b>
<a name="L729" href="source/net/ipv4/tcp_output.c#L729">729</a> <b><i> * to process all sockets that eventually need to send more skbs.</i></b>
<a name="L730" href="source/net/ipv4/tcp_output.c#L730">730</a> <b><i> * We use one tasklet per cpu, with its own queue of sockets.</i></b>
<a name="L731" href="source/net/ipv4/tcp_output.c#L731">731</a> <b><i> */</i></b>
<a name="L732" href="source/net/ipv4/tcp_output.c#L732">732</a> struct <a href="ident?i=tsq_tasklet">tsq_tasklet</a> {
<a name="L733" href="source/net/ipv4/tcp_output.c#L733">733</a>         struct <a href="ident?i=tasklet_struct">tasklet_struct</a>   tasklet;
<a name="L734" href="source/net/ipv4/tcp_output.c#L734">734</a>         struct <a href="ident?i=list_head">list_head</a>        <a href="ident?i=head">head</a>; <b><i>/* queue of tcp sockets */</i></b>
<a name="L735" href="source/net/ipv4/tcp_output.c#L735">735</a> };
<a name="L736" href="source/net/ipv4/tcp_output.c#L736">736</a> static <a href="ident?i=DEFINE_PER_CPU">DEFINE_PER_CPU</a>(struct <a href="ident?i=tsq_tasklet">tsq_tasklet</a>, <a href="ident?i=tsq_tasklet">tsq_tasklet</a>);
<a name="L737" href="source/net/ipv4/tcp_output.c#L737">737</a> 
<a name="L738" href="source/net/ipv4/tcp_output.c#L738">738</a> static void <a href="ident?i=tcp_tsq_handler">tcp_tsq_handler</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L739" href="source/net/ipv4/tcp_output.c#L739">739</a> {
<a name="L740" href="source/net/ipv4/tcp_output.c#L740">740</a>         if ((1 &lt;&lt; sk-&gt;<a href="ident?i=sk_state">sk_state</a>) &amp;
<a name="L741" href="source/net/ipv4/tcp_output.c#L741">741</a>             (TCPF_ESTABLISHED | TCPF_FIN_WAIT1 | TCPF_CLOSING |
<a name="L742" href="source/net/ipv4/tcp_output.c#L742">742</a>              TCPF_CLOSE_WAIT  | TCPF_LAST_ACK))
<a name="L743" href="source/net/ipv4/tcp_output.c#L743">743</a>                 <a href="ident?i=tcp_write_xmit">tcp_write_xmit</a>(sk, <a href="ident?i=tcp_current_mss">tcp_current_mss</a>(sk), <a href="ident?i=tcp_sk">tcp_sk</a>(sk)-&gt;nonagle,
<a name="L744" href="source/net/ipv4/tcp_output.c#L744">744</a>                                0, <a href="ident?i=GFP_ATOMIC">GFP_ATOMIC</a>);
<a name="L745" href="source/net/ipv4/tcp_output.c#L745">745</a> }
<a name="L746" href="source/net/ipv4/tcp_output.c#L746">746</a> <b><i>/*</i></b>
<a name="L747" href="source/net/ipv4/tcp_output.c#L747">747</a> <b><i> * One tasklet per cpu tries to send more skbs.</i></b>
<a name="L748" href="source/net/ipv4/tcp_output.c#L748">748</a> <b><i> * We run in tasklet context but need to disable irqs when</i></b>
<a name="L749" href="source/net/ipv4/tcp_output.c#L749">749</a> <b><i> * transferring tsq-&gt;head because tcp_wfree() might</i></b>
<a name="L750" href="source/net/ipv4/tcp_output.c#L750">750</a> <b><i> * interrupt us (non NAPI drivers)</i></b>
<a name="L751" href="source/net/ipv4/tcp_output.c#L751">751</a> <b><i> */</i></b>
<a name="L752" href="source/net/ipv4/tcp_output.c#L752">752</a> static void <a href="ident?i=tcp_tasklet_func">tcp_tasklet_func</a>(unsigned long <a href="ident?i=data">data</a>)
<a name="L753" href="source/net/ipv4/tcp_output.c#L753">753</a> {
<a name="L754" href="source/net/ipv4/tcp_output.c#L754">754</a>         struct <a href="ident?i=tsq_tasklet">tsq_tasklet</a> *tsq = (struct <a href="ident?i=tsq_tasklet">tsq_tasklet</a> *)<a href="ident?i=data">data</a>;
<a name="L755" href="source/net/ipv4/tcp_output.c#L755">755</a>         <a href="ident?i=LIST_HEAD">LIST_HEAD</a>(<a href="ident?i=list">list</a>);
<a name="L756" href="source/net/ipv4/tcp_output.c#L756">756</a>         unsigned long <a href="ident?i=flags">flags</a>;
<a name="L757" href="source/net/ipv4/tcp_output.c#L757">757</a>         struct <a href="ident?i=list_head">list_head</a> *q, *<a href="ident?i=n">n</a>;
<a name="L758" href="source/net/ipv4/tcp_output.c#L758">758</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a>;
<a name="L759" href="source/net/ipv4/tcp_output.c#L759">759</a>         struct <a href="ident?i=sock">sock</a> *sk;
<a name="L760" href="source/net/ipv4/tcp_output.c#L760">760</a> 
<a name="L761" href="source/net/ipv4/tcp_output.c#L761">761</a>         <a href="ident?i=local_irq_save">local_irq_save</a>(<a href="ident?i=flags">flags</a>);
<a name="L762" href="source/net/ipv4/tcp_output.c#L762">762</a>         <a href="ident?i=list_splice_init">list_splice_init</a>(&amp;tsq-&gt;<a href="ident?i=head">head</a>, &amp;<a href="ident?i=list">list</a>);
<a name="L763" href="source/net/ipv4/tcp_output.c#L763">763</a>         <a href="ident?i=local_irq_restore">local_irq_restore</a>(<a href="ident?i=flags">flags</a>);
<a name="L764" href="source/net/ipv4/tcp_output.c#L764">764</a> 
<a name="L765" href="source/net/ipv4/tcp_output.c#L765">765</a>         <a href="ident?i=list_for_each_safe">list_for_each_safe</a>(q, <a href="ident?i=n">n</a>, &amp;<a href="ident?i=list">list</a>) {
<a name="L766" href="source/net/ipv4/tcp_output.c#L766">766</a>                 <a href="ident?i=tp">tp</a> = <a href="ident?i=list_entry">list_entry</a>(q, struct <a href="ident?i=tcp_sock">tcp_sock</a>, tsq_node);
<a name="L767" href="source/net/ipv4/tcp_output.c#L767">767</a>                 <a href="ident?i=list_del">list_del</a>(&amp;<a href="ident?i=tp">tp</a>-&gt;tsq_node);
<a name="L768" href="source/net/ipv4/tcp_output.c#L768">768</a> 
<a name="L769" href="source/net/ipv4/tcp_output.c#L769">769</a>                 sk = (struct <a href="ident?i=sock">sock</a> *)<a href="ident?i=tp">tp</a>;
<a name="L770" href="source/net/ipv4/tcp_output.c#L770">770</a>                 <a href="ident?i=bh_lock_sock">bh_lock_sock</a>(sk);
<a name="L771" href="source/net/ipv4/tcp_output.c#L771">771</a> 
<a name="L772" href="source/net/ipv4/tcp_output.c#L772">772</a>                 if (!<a href="ident?i=sock_owned_by_user">sock_owned_by_user</a>(sk)) {
<a name="L773" href="source/net/ipv4/tcp_output.c#L773">773</a>                         <a href="ident?i=tcp_tsq_handler">tcp_tsq_handler</a>(sk);
<a name="L774" href="source/net/ipv4/tcp_output.c#L774">774</a>                 } else {
<a name="L775" href="source/net/ipv4/tcp_output.c#L775">775</a>                         <b><i>/* defer the work to tcp_release_cb() */</i></b>
<a name="L776" href="source/net/ipv4/tcp_output.c#L776">776</a>                         <a href="ident?i=set_bit">set_bit</a>(TCP_TSQ_DEFERRED, &amp;<a href="ident?i=tp">tp</a>-&gt;<a href="ident?i=tsq_flags">tsq_flags</a>);
<a name="L777" href="source/net/ipv4/tcp_output.c#L777">777</a>                 }
<a name="L778" href="source/net/ipv4/tcp_output.c#L778">778</a>                 <a href="ident?i=bh_unlock_sock">bh_unlock_sock</a>(sk);
<a name="L779" href="source/net/ipv4/tcp_output.c#L779">779</a> 
<a name="L780" href="source/net/ipv4/tcp_output.c#L780">780</a>                 <a href="ident?i=clear_bit">clear_bit</a>(TSQ_QUEUED, &amp;<a href="ident?i=tp">tp</a>-&gt;<a href="ident?i=tsq_flags">tsq_flags</a>);
<a name="L781" href="source/net/ipv4/tcp_output.c#L781">781</a>                 <a href="ident?i=sk_free">sk_free</a>(sk);
<a name="L782" href="source/net/ipv4/tcp_output.c#L782">782</a>         }
<a name="L783" href="source/net/ipv4/tcp_output.c#L783">783</a> }
<a name="L784" href="source/net/ipv4/tcp_output.c#L784">784</a> 
<a name="L785" href="source/net/ipv4/tcp_output.c#L785">785</a> #define <a href="ident?i=TCP_DEFERRED_ALL">TCP_DEFERRED_ALL</a> ((1UL &lt;&lt; TCP_TSQ_DEFERRED) |           \
<a name="L786" href="source/net/ipv4/tcp_output.c#L786">786</a>                           (1UL &lt;&lt; TCP_WRITE_TIMER_DEFERRED) |   \
<a name="L787" href="source/net/ipv4/tcp_output.c#L787">787</a>                           (1UL &lt;&lt; TCP_DELACK_TIMER_DEFERRED) |  \
<a name="L788" href="source/net/ipv4/tcp_output.c#L788">788</a>                           (1UL &lt;&lt; TCP_MTU_REDUCED_DEFERRED))
<a name="L789" href="source/net/ipv4/tcp_output.c#L789">789</a> <b><i>/**</i></b>
<a name="L790" href="source/net/ipv4/tcp_output.c#L790">790</a> <b><i> * tcp_release_cb - tcp release_sock() callback</i></b>
<a name="L791" href="source/net/ipv4/tcp_output.c#L791">791</a> <b><i> * @sk: socket</i></b>
<a name="L792" href="source/net/ipv4/tcp_output.c#L792">792</a> <b><i> *</i></b>
<a name="L793" href="source/net/ipv4/tcp_output.c#L793">793</a> <b><i> * called from release_sock() to perform protocol dependent</i></b>
<a name="L794" href="source/net/ipv4/tcp_output.c#L794">794</a> <b><i> * actions before socket release.</i></b>
<a name="L795" href="source/net/ipv4/tcp_output.c#L795">795</a> <b><i> */</i></b>
<a name="L796" href="source/net/ipv4/tcp_output.c#L796">796</a> void <a href="ident?i=tcp_release_cb">tcp_release_cb</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L797" href="source/net/ipv4/tcp_output.c#L797">797</a> {
<a name="L798" href="source/net/ipv4/tcp_output.c#L798">798</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L799" href="source/net/ipv4/tcp_output.c#L799">799</a>         unsigned long <a href="ident?i=flags">flags</a>, nflags;
<a name="L800" href="source/net/ipv4/tcp_output.c#L800">800</a> 
<a name="L801" href="source/net/ipv4/tcp_output.c#L801">801</a>         <b><i>/* perform an atomic operation only if at least one flag is set */</i></b>
<a name="L802" href="source/net/ipv4/tcp_output.c#L802">802</a>         do {
<a name="L803" href="source/net/ipv4/tcp_output.c#L803">803</a>                 <a href="ident?i=flags">flags</a> = <a href="ident?i=tp">tp</a>-&gt;<a href="ident?i=tsq_flags">tsq_flags</a>;
<a name="L804" href="source/net/ipv4/tcp_output.c#L804">804</a>                 if (!(<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=TCP_DEFERRED_ALL">TCP_DEFERRED_ALL</a>))
<a name="L805" href="source/net/ipv4/tcp_output.c#L805">805</a>                         return;
<a name="L806" href="source/net/ipv4/tcp_output.c#L806">806</a>                 nflags = <a href="ident?i=flags">flags</a> &amp; ~TCP_DEFERRED_ALL;
<a name="L807" href="source/net/ipv4/tcp_output.c#L807">807</a>         } while (<a href="ident?i=cmpxchg">cmpxchg</a>(&amp;<a href="ident?i=tp">tp</a>-&gt;<a href="ident?i=tsq_flags">tsq_flags</a>, <a href="ident?i=flags">flags</a>, nflags) != <a href="ident?i=flags">flags</a>);
<a name="L808" href="source/net/ipv4/tcp_output.c#L808">808</a> 
<a name="L809" href="source/net/ipv4/tcp_output.c#L809">809</a>         if (<a href="ident?i=flags">flags</a> &amp; (1UL &lt;&lt; TCP_TSQ_DEFERRED))
<a name="L810" href="source/net/ipv4/tcp_output.c#L810">810</a>                 <a href="ident?i=tcp_tsq_handler">tcp_tsq_handler</a>(sk);
<a name="L811" href="source/net/ipv4/tcp_output.c#L811">811</a> 
<a name="L812" href="source/net/ipv4/tcp_output.c#L812">812</a>         <b><i>/* Here begins the tricky part :</i></b>
<a name="L813" href="source/net/ipv4/tcp_output.c#L813">813</a> <b><i>         * We are called from release_sock() with :</i></b>
<a name="L814" href="source/net/ipv4/tcp_output.c#L814">814</a> <b><i>         * 1) BH disabled</i></b>
<a name="L815" href="source/net/ipv4/tcp_output.c#L815">815</a> <b><i>         * 2) sk_lock.slock spinlock held</i></b>
<a name="L816" href="source/net/ipv4/tcp_output.c#L816">816</a> <b><i>         * 3) socket owned by us (sk-&gt;sk_lock.owned == 1)</i></b>
<a name="L817" href="source/net/ipv4/tcp_output.c#L817">817</a> <b><i>         *</i></b>
<a name="L818" href="source/net/ipv4/tcp_output.c#L818">818</a> <b><i>         * But following code is meant to be called from BH handlers,</i></b>
<a name="L819" href="source/net/ipv4/tcp_output.c#L819">819</a> <b><i>         * so we should keep BH disabled, but early release socket ownership</i></b>
<a name="L820" href="source/net/ipv4/tcp_output.c#L820">820</a> <b><i>         */</i></b>
<a name="L821" href="source/net/ipv4/tcp_output.c#L821">821</a>         <a href="ident?i=sock_release_ownership">sock_release_ownership</a>(sk);
<a name="L822" href="source/net/ipv4/tcp_output.c#L822">822</a> 
<a name="L823" href="source/net/ipv4/tcp_output.c#L823">823</a>         if (<a href="ident?i=flags">flags</a> &amp; (1UL &lt;&lt; TCP_WRITE_TIMER_DEFERRED)) {
<a name="L824" href="source/net/ipv4/tcp_output.c#L824">824</a>                 <a href="ident?i=tcp_write_timer_handler">tcp_write_timer_handler</a>(sk);
<a name="L825" href="source/net/ipv4/tcp_output.c#L825">825</a>                 <a href="ident?i=__sock_put">__sock_put</a>(sk);
<a name="L826" href="source/net/ipv4/tcp_output.c#L826">826</a>         }
<a name="L827" href="source/net/ipv4/tcp_output.c#L827">827</a>         if (<a href="ident?i=flags">flags</a> &amp; (1UL &lt;&lt; TCP_DELACK_TIMER_DEFERRED)) {
<a name="L828" href="source/net/ipv4/tcp_output.c#L828">828</a>                 <a href="ident?i=tcp_delack_timer_handler">tcp_delack_timer_handler</a>(sk);
<a name="L829" href="source/net/ipv4/tcp_output.c#L829">829</a>                 <a href="ident?i=__sock_put">__sock_put</a>(sk);
<a name="L830" href="source/net/ipv4/tcp_output.c#L830">830</a>         }
<a name="L831" href="source/net/ipv4/tcp_output.c#L831">831</a>         if (<a href="ident?i=flags">flags</a> &amp; (1UL &lt;&lt; TCP_MTU_REDUCED_DEFERRED)) {
<a name="L832" href="source/net/ipv4/tcp_output.c#L832">832</a>                 <a href="ident?i=inet_csk">inet_csk</a>(sk)-&gt;icsk_af_ops-&gt;mtu_reduced(sk);
<a name="L833" href="source/net/ipv4/tcp_output.c#L833">833</a>                 <a href="ident?i=__sock_put">__sock_put</a>(sk);
<a name="L834" href="source/net/ipv4/tcp_output.c#L834">834</a>         }
<a name="L835" href="source/net/ipv4/tcp_output.c#L835">835</a> }
<a name="L836" href="source/net/ipv4/tcp_output.c#L836">836</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=tcp_release_cb">tcp_release_cb</a>);
<a name="L837" href="source/net/ipv4/tcp_output.c#L837">837</a> 
<a name="L838" href="source/net/ipv4/tcp_output.c#L838">838</a> void <a href="ident?i=__init">__init</a> <a href="ident?i=tcp_tasklet_init">tcp_tasklet_init</a>(void)
<a name="L839" href="source/net/ipv4/tcp_output.c#L839">839</a> {
<a name="L840" href="source/net/ipv4/tcp_output.c#L840">840</a>         int <a href="ident?i=i">i</a>;
<a name="L841" href="source/net/ipv4/tcp_output.c#L841">841</a> 
<a name="L842" href="source/net/ipv4/tcp_output.c#L842">842</a>         <a href="ident?i=for_each_possible_cpu">for_each_possible_cpu</a>(<a href="ident?i=i">i</a>) {
<a name="L843" href="source/net/ipv4/tcp_output.c#L843">843</a>                 struct <a href="ident?i=tsq_tasklet">tsq_tasklet</a> *tsq = &amp;<a href="ident?i=per_cpu">per_cpu</a>(<a href="ident?i=tsq_tasklet">tsq_tasklet</a>, <a href="ident?i=i">i</a>);
<a name="L844" href="source/net/ipv4/tcp_output.c#L844">844</a> 
<a name="L845" href="source/net/ipv4/tcp_output.c#L845">845</a>                 <a href="ident?i=INIT_LIST_HEAD">INIT_LIST_HEAD</a>(&amp;tsq-&gt;<a href="ident?i=head">head</a>);
<a name="L846" href="source/net/ipv4/tcp_output.c#L846">846</a>                 <a href="ident?i=tasklet_init">tasklet_init</a>(&amp;tsq-&gt;tasklet,
<a name="L847" href="source/net/ipv4/tcp_output.c#L847">847</a>                              <a href="ident?i=tcp_tasklet_func">tcp_tasklet_func</a>,
<a name="L848" href="source/net/ipv4/tcp_output.c#L848">848</a>                              (unsigned long)tsq);
<a name="L849" href="source/net/ipv4/tcp_output.c#L849">849</a>         }
<a name="L850" href="source/net/ipv4/tcp_output.c#L850">850</a> }
<a name="L851" href="source/net/ipv4/tcp_output.c#L851">851</a> 
<a name="L852" href="source/net/ipv4/tcp_output.c#L852">852</a> <b><i>/*</i></b>
<a name="L853" href="source/net/ipv4/tcp_output.c#L853">853</a> <b><i> * Write buffer destructor automatically called from kfree_skb.</i></b>
<a name="L854" href="source/net/ipv4/tcp_output.c#L854">854</a> <b><i> * We can't xmit new skbs from this context, as we might already</i></b>
<a name="L855" href="source/net/ipv4/tcp_output.c#L855">855</a> <b><i> * hold qdisc lock.</i></b>
<a name="L856" href="source/net/ipv4/tcp_output.c#L856">856</a> <b><i> */</i></b>
<a name="L857" href="source/net/ipv4/tcp_output.c#L857">857</a> void <a href="ident?i=tcp_wfree">tcp_wfree</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L858" href="source/net/ipv4/tcp_output.c#L858">858</a> {
<a name="L859" href="source/net/ipv4/tcp_output.c#L859">859</a>         struct <a href="ident?i=sock">sock</a> *sk = <a href="ident?i=skb">skb</a>-&gt;sk;
<a name="L860" href="source/net/ipv4/tcp_output.c#L860">860</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L861" href="source/net/ipv4/tcp_output.c#L861">861</a>         int wmem;
<a name="L862" href="source/net/ipv4/tcp_output.c#L862">862</a> 
<a name="L863" href="source/net/ipv4/tcp_output.c#L863">863</a>         <b><i>/* Keep one reference on sk_wmem_alloc.</i></b>
<a name="L864" href="source/net/ipv4/tcp_output.c#L864">864</a> <b><i>         * Will be released by sk_free() from here or tcp_tasklet_func()</i></b>
<a name="L865" href="source/net/ipv4/tcp_output.c#L865">865</a> <b><i>         */</i></b>
<a name="L866" href="source/net/ipv4/tcp_output.c#L866">866</a>         wmem = <a href="ident?i=atomic_sub_return">atomic_sub_return</a>(<a href="ident?i=skb">skb</a>-&gt;truesize - 1, &amp;sk-&gt;sk_wmem_alloc);
<a name="L867" href="source/net/ipv4/tcp_output.c#L867">867</a> 
<a name="L868" href="source/net/ipv4/tcp_output.c#L868">868</a>         <b><i>/* If this softirq is serviced by ksoftirqd, we are likely under stress.</i></b>
<a name="L869" href="source/net/ipv4/tcp_output.c#L869">869</a> <b><i>         * Wait until our queues (qdisc + devices) are drained.</i></b>
<a name="L870" href="source/net/ipv4/tcp_output.c#L870">870</a> <b><i>         * This gives :</i></b>
<a name="L871" href="source/net/ipv4/tcp_output.c#L871">871</a> <b><i>         * - less callbacks to tcp_write_xmit(), reducing stress (batches)</i></b>
<a name="L872" href="source/net/ipv4/tcp_output.c#L872">872</a> <b><i>         * - chance for incoming ACK (processed by another cpu maybe)</i></b>
<a name="L873" href="source/net/ipv4/tcp_output.c#L873">873</a> <b><i>         *   to migrate this flow (skb-&gt;ooo_okay will be eventually set)</i></b>
<a name="L874" href="source/net/ipv4/tcp_output.c#L874">874</a> <b><i>         */</i></b>
<a name="L875" href="source/net/ipv4/tcp_output.c#L875">875</a>         if (wmem &gt;= <a href="ident?i=SKB_TRUESIZE">SKB_TRUESIZE</a>(1) &amp;&amp; <a href="ident?i=this_cpu_ksoftirqd">this_cpu_ksoftirqd</a>() == <a href="ident?i=current">current</a>)
<a name="L876" href="source/net/ipv4/tcp_output.c#L876">876</a>                 goto <a href="ident?i=out">out</a>;
<a name="L877" href="source/net/ipv4/tcp_output.c#L877">877</a> 
<a name="L878" href="source/net/ipv4/tcp_output.c#L878">878</a>         if (<a href="ident?i=test_and_clear_bit">test_and_clear_bit</a>(TSQ_THROTTLED, &amp;<a href="ident?i=tp">tp</a>-&gt;<a href="ident?i=tsq_flags">tsq_flags</a>) &amp;&amp;
<a name="L879" href="source/net/ipv4/tcp_output.c#L879">879</a>             !<a href="ident?i=test_and_set_bit">test_and_set_bit</a>(TSQ_QUEUED, &amp;<a href="ident?i=tp">tp</a>-&gt;<a href="ident?i=tsq_flags">tsq_flags</a>)) {
<a name="L880" href="source/net/ipv4/tcp_output.c#L880">880</a>                 unsigned long <a href="ident?i=flags">flags</a>;
<a name="L881" href="source/net/ipv4/tcp_output.c#L881">881</a>                 struct <a href="ident?i=tsq_tasklet">tsq_tasklet</a> *tsq;
<a name="L882" href="source/net/ipv4/tcp_output.c#L882">882</a> 
<a name="L883" href="source/net/ipv4/tcp_output.c#L883">883</a>                 <b><i>/* queue this socket to tasklet queue */</i></b>
<a name="L884" href="source/net/ipv4/tcp_output.c#L884">884</a>                 <a href="ident?i=local_irq_save">local_irq_save</a>(<a href="ident?i=flags">flags</a>);
<a name="L885" href="source/net/ipv4/tcp_output.c#L885">885</a>                 tsq = <a href="ident?i=this_cpu_ptr">this_cpu_ptr</a>(&amp;<a href="ident?i=tsq_tasklet">tsq_tasklet</a>);
<a name="L886" href="source/net/ipv4/tcp_output.c#L886">886</a>                 <a href="ident?i=list_add">list_add</a>(&amp;<a href="ident?i=tp">tp</a>-&gt;tsq_node, &amp;tsq-&gt;<a href="ident?i=head">head</a>);
<a name="L887" href="source/net/ipv4/tcp_output.c#L887">887</a>                 <a href="ident?i=tasklet_schedule">tasklet_schedule</a>(&amp;tsq-&gt;tasklet);
<a name="L888" href="source/net/ipv4/tcp_output.c#L888">888</a>                 <a href="ident?i=local_irq_restore">local_irq_restore</a>(<a href="ident?i=flags">flags</a>);
<a name="L889" href="source/net/ipv4/tcp_output.c#L889">889</a>                 return;
<a name="L890" href="source/net/ipv4/tcp_output.c#L890">890</a>         }
<a name="L891" href="source/net/ipv4/tcp_output.c#L891">891</a> <a href="ident?i=out">out</a>:
<a name="L892" href="source/net/ipv4/tcp_output.c#L892">892</a>         <a href="ident?i=sk_free">sk_free</a>(sk);
<a name="L893" href="source/net/ipv4/tcp_output.c#L893">893</a> }
<a name="L894" href="source/net/ipv4/tcp_output.c#L894">894</a> 
<a name="L895" href="source/net/ipv4/tcp_output.c#L895">895</a> <b><i>/* This routine actually transmits TCP packets queued in by</i></b>
<a name="L896" href="source/net/ipv4/tcp_output.c#L896">896</a> <b><i> * tcp_do_sendmsg().  This is used by both the initial</i></b>
<a name="L897" href="source/net/ipv4/tcp_output.c#L897">897</a> <b><i> * transmission and possible later retransmissions.</i></b>
<a name="L898" href="source/net/ipv4/tcp_output.c#L898">898</a> <b><i> * All SKB's seen here are completely headerless.  It is our</i></b>
<a name="L899" href="source/net/ipv4/tcp_output.c#L899">899</a> <b><i> * job to build the TCP header, and pass the packet down to</i></b>
<a name="L900" href="source/net/ipv4/tcp_output.c#L900">900</a> <b><i> * IP so it can do the same plus pass the packet off to the</i></b>
<a name="L901" href="source/net/ipv4/tcp_output.c#L901">901</a> <b><i> * device.</i></b>
<a name="L902" href="source/net/ipv4/tcp_output.c#L902">902</a> <b><i> *</i></b>
<a name="L903" href="source/net/ipv4/tcp_output.c#L903">903</a> <b><i> * We are working here with either a clone of the original</i></b>
<a name="L904" href="source/net/ipv4/tcp_output.c#L904">904</a> <b><i> * SKB, or a fresh unique copy made by the retransmit engine.</i></b>
<a name="L905" href="source/net/ipv4/tcp_output.c#L905">905</a> <b><i> */</i></b>
<a name="L906" href="source/net/ipv4/tcp_output.c#L906">906</a> static int <a href="ident?i=tcp_transmit_skb">tcp_transmit_skb</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, int clone_it,
<a name="L907" href="source/net/ipv4/tcp_output.c#L907">907</a>                             <a href="ident?i=gfp_t">gfp_t</a> gfp_mask)
<a name="L908" href="source/net/ipv4/tcp_output.c#L908">908</a> {
<a name="L909" href="source/net/ipv4/tcp_output.c#L909">909</a>         const struct <a href="ident?i=inet_connection_sock">inet_connection_sock</a> *icsk = <a href="ident?i=inet_csk">inet_csk</a>(sk);
<a name="L910" href="source/net/ipv4/tcp_output.c#L910">910</a>         struct <a href="ident?i=inet_sock">inet_sock</a> *inet;
<a name="L911" href="source/net/ipv4/tcp_output.c#L911">911</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a>;
<a name="L912" href="source/net/ipv4/tcp_output.c#L912">912</a>         struct <a href="ident?i=tcp_skb_cb">tcp_skb_cb</a> *<a href="ident?i=tcb">tcb</a>;
<a name="L913" href="source/net/ipv4/tcp_output.c#L913">913</a>         struct <a href="ident?i=tcp_out_options">tcp_out_options</a> <a href="ident?i=opts">opts</a>;
<a name="L914" href="source/net/ipv4/tcp_output.c#L914">914</a>         unsigned int tcp_options_size, tcp_header_size;
<a name="L915" href="source/net/ipv4/tcp_output.c#L915">915</a>         struct <a href="ident?i=tcp_md5sig_key">tcp_md5sig_key</a> *md5;
<a name="L916" href="source/net/ipv4/tcp_output.c#L916">916</a>         struct <a href="ident?i=tcphdr">tcphdr</a> *<a href="ident?i=th">th</a>;
<a name="L917" href="source/net/ipv4/tcp_output.c#L917">917</a>         int <a href="ident?i=err">err</a>;
<a name="L918" href="source/net/ipv4/tcp_output.c#L918">918</a> 
<a name="L919" href="source/net/ipv4/tcp_output.c#L919">919</a>         <a href="ident?i=BUG_ON">BUG_ON</a>(!<a href="ident?i=skb">skb</a> || !<a href="ident?i=tcp_skb_pcount">tcp_skb_pcount</a>(<a href="ident?i=skb">skb</a>));
<a name="L920" href="source/net/ipv4/tcp_output.c#L920">920</a> 
<a name="L921" href="source/net/ipv4/tcp_output.c#L921">921</a>         if (clone_it) {
<a name="L922" href="source/net/ipv4/tcp_output.c#L922">922</a>                 <a href="ident?i=skb_mstamp_get">skb_mstamp_get</a>(&amp;<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=skb_mstamp">skb_mstamp</a>);
<a name="L923" href="source/net/ipv4/tcp_output.c#L923">923</a> 
<a name="L924" href="source/net/ipv4/tcp_output.c#L924">924</a>                 if (<a href="ident?i=unlikely">unlikely</a>(<a href="ident?i=skb_cloned">skb_cloned</a>(<a href="ident?i=skb">skb</a>)))
<a name="L925" href="source/net/ipv4/tcp_output.c#L925">925</a>                         <a href="ident?i=skb">skb</a> = <a href="ident?i=pskb_copy">pskb_copy</a>(<a href="ident?i=skb">skb</a>, gfp_mask);
<a name="L926" href="source/net/ipv4/tcp_output.c#L926">926</a>                 else
<a name="L927" href="source/net/ipv4/tcp_output.c#L927">927</a>                         <a href="ident?i=skb">skb</a> = <a href="ident?i=skb_clone">skb_clone</a>(<a href="ident?i=skb">skb</a>, gfp_mask);
<a name="L928" href="source/net/ipv4/tcp_output.c#L928">928</a>                 if (<a href="ident?i=unlikely">unlikely</a>(!<a href="ident?i=skb">skb</a>))
<a name="L929" href="source/net/ipv4/tcp_output.c#L929">929</a>                         return -<a href="ident?i=ENOBUFS">ENOBUFS</a>;
<a name="L930" href="source/net/ipv4/tcp_output.c#L930">930</a>         }
<a name="L931" href="source/net/ipv4/tcp_output.c#L931">931</a> 
<a name="L932" href="source/net/ipv4/tcp_output.c#L932">932</a>         inet = <a href="ident?i=inet_sk">inet_sk</a>(sk);
<a name="L933" href="source/net/ipv4/tcp_output.c#L933">933</a>         <a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L934" href="source/net/ipv4/tcp_output.c#L934">934</a>         <a href="ident?i=tcb">tcb</a> = <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>);
<a name="L935" href="source/net/ipv4/tcp_output.c#L935">935</a>         <a href="ident?i=memset">memset</a>(&amp;<a href="ident?i=opts">opts</a>, 0, sizeof(<a href="ident?i=opts">opts</a>));
<a name="L936" href="source/net/ipv4/tcp_output.c#L936">936</a> 
<a name="L937" href="source/net/ipv4/tcp_output.c#L937">937</a>         if (<a href="ident?i=unlikely">unlikely</a>(<a href="ident?i=tcb">tcb</a>-&gt;tcp_flags &amp; <a href="ident?i=TCPHDR_SYN">TCPHDR_SYN</a>))
<a name="L938" href="source/net/ipv4/tcp_output.c#L938">938</a>                 tcp_options_size = <a href="ident?i=tcp_syn_options">tcp_syn_options</a>(sk, <a href="ident?i=skb">skb</a>, &amp;<a href="ident?i=opts">opts</a>, &amp;md5);
<a name="L939" href="source/net/ipv4/tcp_output.c#L939">939</a>         else
<a name="L940" href="source/net/ipv4/tcp_output.c#L940">940</a>                 tcp_options_size = <a href="ident?i=tcp_established_options">tcp_established_options</a>(sk, <a href="ident?i=skb">skb</a>, &amp;<a href="ident?i=opts">opts</a>,
<a name="L941" href="source/net/ipv4/tcp_output.c#L941">941</a>                                                            &amp;md5);
<a name="L942" href="source/net/ipv4/tcp_output.c#L942">942</a>         tcp_header_size = tcp_options_size + sizeof(struct <a href="ident?i=tcphdr">tcphdr</a>);
<a name="L943" href="source/net/ipv4/tcp_output.c#L943">943</a> 
<a name="L944" href="source/net/ipv4/tcp_output.c#L944">944</a>         if (<a href="ident?i=tcp_packets_in_flight">tcp_packets_in_flight</a>(<a href="ident?i=tp">tp</a>) == 0)
<a name="L945" href="source/net/ipv4/tcp_output.c#L945">945</a>                 <a href="ident?i=tcp_ca_event">tcp_ca_event</a>(sk, CA_EVENT_TX_START);
<a name="L946" href="source/net/ipv4/tcp_output.c#L946">946</a> 
<a name="L947" href="source/net/ipv4/tcp_output.c#L947">947</a>         <b><i>/* if no packet is in qdisc/device queue, then allow XPS to select</i></b>
<a name="L948" href="source/net/ipv4/tcp_output.c#L948">948</a> <b><i>         * another queue. We can be called from tcp_tsq_handler()</i></b>
<a name="L949" href="source/net/ipv4/tcp_output.c#L949">949</a> <b><i>         * which holds one reference to sk_wmem_alloc.</i></b>
<a name="L950" href="source/net/ipv4/tcp_output.c#L950">950</a> <b><i>         *</i></b>
<a name="L951" href="source/net/ipv4/tcp_output.c#L951">951</a> <b><i>         * TODO: Ideally, in-flight pure ACK packets should not matter here.</i></b>
<a name="L952" href="source/net/ipv4/tcp_output.c#L952">952</a> <b><i>         * One way to get this would be to set skb-&gt;truesize = 2 on them.</i></b>
<a name="L953" href="source/net/ipv4/tcp_output.c#L953">953</a> <b><i>         */</i></b>
<a name="L954" href="source/net/ipv4/tcp_output.c#L954">954</a>         <a href="ident?i=skb">skb</a>-&gt;ooo_okay = <a href="ident?i=sk_wmem_alloc_get">sk_wmem_alloc_get</a>(sk) &lt; <a href="ident?i=SKB_TRUESIZE">SKB_TRUESIZE</a>(1);
<a name="L955" href="source/net/ipv4/tcp_output.c#L955">955</a> 
<a name="L956" href="source/net/ipv4/tcp_output.c#L956">956</a>         <a href="ident?i=skb_push">skb_push</a>(<a href="ident?i=skb">skb</a>, tcp_header_size);
<a name="L957" href="source/net/ipv4/tcp_output.c#L957">957</a>         <a href="ident?i=skb_reset_transport_header">skb_reset_transport_header</a>(<a href="ident?i=skb">skb</a>);
<a name="L958" href="source/net/ipv4/tcp_output.c#L958">958</a> 
<a name="L959" href="source/net/ipv4/tcp_output.c#L959">959</a>         <a href="ident?i=skb_orphan">skb_orphan</a>(<a href="ident?i=skb">skb</a>);
<a name="L960" href="source/net/ipv4/tcp_output.c#L960">960</a>         <a href="ident?i=skb">skb</a>-&gt;sk = sk;
<a name="L961" href="source/net/ipv4/tcp_output.c#L961">961</a>         <a href="ident?i=skb">skb</a>-&gt;destructor = <a href="ident?i=skb_is_tcp_pure_ack">skb_is_tcp_pure_ack</a>(<a href="ident?i=skb">skb</a>) ? <a href="ident?i=sock_wfree">sock_wfree</a> : <a href="ident?i=tcp_wfree">tcp_wfree</a>;
<a name="L962" href="source/net/ipv4/tcp_output.c#L962">962</a>         <a href="ident?i=skb_set_hash_from_sk">skb_set_hash_from_sk</a>(<a href="ident?i=skb">skb</a>, sk);
<a name="L963" href="source/net/ipv4/tcp_output.c#L963">963</a>         <a href="ident?i=atomic_add">atomic_add</a>(<a href="ident?i=skb">skb</a>-&gt;truesize, &amp;sk-&gt;sk_wmem_alloc);
<a name="L964" href="source/net/ipv4/tcp_output.c#L964">964</a> 
<a name="L965" href="source/net/ipv4/tcp_output.c#L965">965</a>         <b><i>/* Build TCP header and checksum it. */</i></b>
<a name="L966" href="source/net/ipv4/tcp_output.c#L966">966</a>         <a href="ident?i=th">th</a> = <a href="ident?i=tcp_hdr">tcp_hdr</a>(<a href="ident?i=skb">skb</a>);
<a name="L967" href="source/net/ipv4/tcp_output.c#L967">967</a>         <a href="ident?i=th">th</a>-&gt;source              = inet-&gt;inet_sport;
<a name="L968" href="source/net/ipv4/tcp_output.c#L968">968</a>         <a href="ident?i=th">th</a>-&gt;<a href="ident?i=dest">dest</a>                = inet-&gt;<a href="ident?i=inet_dport">inet_dport</a>;
<a name="L969" href="source/net/ipv4/tcp_output.c#L969">969</a>         <a href="ident?i=th">th</a>-&gt;<a href="ident?i=seq">seq</a>                 = <a href="ident?i=htonl">htonl</a>(<a href="ident?i=tcb">tcb</a>-&gt;<a href="ident?i=seq">seq</a>);
<a name="L970" href="source/net/ipv4/tcp_output.c#L970">970</a>         <a href="ident?i=th">th</a>-&gt;ack_seq             = <a href="ident?i=htonl">htonl</a>(<a href="ident?i=tp">tp</a>-&gt;rcv_nxt);
<a name="L971" href="source/net/ipv4/tcp_output.c#L971">971</a>         *(((<a href="ident?i=__be16">__be16</a> *)<a href="ident?i=th">th</a>) + 6)   = <a href="ident?i=htons">htons</a>(((tcp_header_size &gt;&gt; 2) &lt;&lt; 12) |
<a name="L972" href="source/net/ipv4/tcp_output.c#L972">972</a>                                         <a href="ident?i=tcb">tcb</a>-&gt;tcp_flags);
<a name="L973" href="source/net/ipv4/tcp_output.c#L973">973</a> 
<a name="L974" href="source/net/ipv4/tcp_output.c#L974">974</a>         if (<a href="ident?i=unlikely">unlikely</a>(<a href="ident?i=tcb">tcb</a>-&gt;tcp_flags &amp; <a href="ident?i=TCPHDR_SYN">TCPHDR_SYN</a>)) {
<a name="L975" href="source/net/ipv4/tcp_output.c#L975">975</a>                 <b><i>/* RFC1323: The window in SYN &amp; SYN/ACK segments</i></b>
<a name="L976" href="source/net/ipv4/tcp_output.c#L976">976</a> <b><i>                 * is never scaled.</i></b>
<a name="L977" href="source/net/ipv4/tcp_output.c#L977">977</a> <b><i>                 */</i></b>
<a name="L978" href="source/net/ipv4/tcp_output.c#L978">978</a>                 <a href="ident?i=th">th</a>-&gt;<a href="ident?i=window">window</a>      = <a href="ident?i=htons">htons</a>(<a href="ident?i=min">min</a>(<a href="ident?i=tp">tp</a>-&gt;rcv_wnd, 65535U));
<a name="L979" href="source/net/ipv4/tcp_output.c#L979">979</a>         } else {
<a name="L980" href="source/net/ipv4/tcp_output.c#L980">980</a>                 <a href="ident?i=th">th</a>-&gt;<a href="ident?i=window">window</a>      = <a href="ident?i=htons">htons</a>(<a href="ident?i=tcp_select_window">tcp_select_window</a>(sk));
<a name="L981" href="source/net/ipv4/tcp_output.c#L981">981</a>         }
<a name="L982" href="source/net/ipv4/tcp_output.c#L982">982</a>         <a href="ident?i=th">th</a>-&gt;<a href="ident?i=check">check</a>               = 0;
<a name="L983" href="source/net/ipv4/tcp_output.c#L983">983</a>         <a href="ident?i=th">th</a>-&gt;urg_ptr             = 0;
<a name="L984" href="source/net/ipv4/tcp_output.c#L984">984</a> 
<a name="L985" href="source/net/ipv4/tcp_output.c#L985">985</a>         <b><i>/* The urg_mode check is necessary during a below snd_una win probe */</i></b>
<a name="L986" href="source/net/ipv4/tcp_output.c#L986">986</a>         if (<a href="ident?i=unlikely">unlikely</a>(<a href="ident?i=tcp_urg_mode">tcp_urg_mode</a>(<a href="ident?i=tp">tp</a>) &amp;&amp; <a href="ident?i=before">before</a>(<a href="ident?i=tcb">tcb</a>-&gt;<a href="ident?i=seq">seq</a>, <a href="ident?i=tp">tp</a>-&gt;snd_up))) {
<a name="L987" href="source/net/ipv4/tcp_output.c#L987">987</a>                 if (<a href="ident?i=before">before</a>(<a href="ident?i=tp">tp</a>-&gt;snd_up, <a href="ident?i=tcb">tcb</a>-&gt;<a href="ident?i=seq">seq</a> + 0x10000)) {
<a name="L988" href="source/net/ipv4/tcp_output.c#L988">988</a>                         <a href="ident?i=th">th</a>-&gt;urg_ptr = <a href="ident?i=htons">htons</a>(<a href="ident?i=tp">tp</a>-&gt;snd_up - <a href="ident?i=tcb">tcb</a>-&gt;<a href="ident?i=seq">seq</a>);
<a name="L989" href="source/net/ipv4/tcp_output.c#L989">989</a>                         <a href="ident?i=th">th</a>-&gt;urg = 1;
<a name="L990" href="source/net/ipv4/tcp_output.c#L990">990</a>                 } else if (<a href="ident?i=after">after</a>(<a href="ident?i=tcb">tcb</a>-&gt;<a href="ident?i=seq">seq</a> + 0xFFFF, <a href="ident?i=tp">tp</a>-&gt;snd_nxt)) {
<a name="L991" href="source/net/ipv4/tcp_output.c#L991">991</a>                         <a href="ident?i=th">th</a>-&gt;urg_ptr = <a href="ident?i=htons">htons</a>(0xFFFF);
<a name="L992" href="source/net/ipv4/tcp_output.c#L992">992</a>                         <a href="ident?i=th">th</a>-&gt;urg = 1;
<a name="L993" href="source/net/ipv4/tcp_output.c#L993">993</a>                 }
<a name="L994" href="source/net/ipv4/tcp_output.c#L994">994</a>         }
<a name="L995" href="source/net/ipv4/tcp_output.c#L995">995</a> 
<a name="L996" href="source/net/ipv4/tcp_output.c#L996">996</a>         <a href="ident?i=tcp_options_write">tcp_options_write</a>((<a href="ident?i=__be32">__be32</a> *)(<a href="ident?i=th">th</a> + 1), <a href="ident?i=tp">tp</a>, &amp;<a href="ident?i=opts">opts</a>);
<a name="L997" href="source/net/ipv4/tcp_output.c#L997">997</a>         if (<a href="ident?i=likely">likely</a>((<a href="ident?i=tcb">tcb</a>-&gt;tcp_flags &amp; <a href="ident?i=TCPHDR_SYN">TCPHDR_SYN</a>) == 0))
<a name="L998" href="source/net/ipv4/tcp_output.c#L998">998</a>                 <a href="ident?i=tcp_ecn_send">tcp_ecn_send</a>(sk, <a href="ident?i=skb">skb</a>, tcp_header_size);
<a name="L999" href="source/net/ipv4/tcp_output.c#L999">999</a> 
<a name="L1000" href="source/net/ipv4/tcp_output.c#L1000">1000</a> #ifdef CONFIG_TCP_MD5SIG
<a name="L1001" href="source/net/ipv4/tcp_output.c#L1001">1001</a>         <b><i>/* Calculate the MD5 hash, as we have all we need now */</i></b>
<a name="L1002" href="source/net/ipv4/tcp_output.c#L1002">1002</a>         if (md5) {
<a name="L1003" href="source/net/ipv4/tcp_output.c#L1003">1003</a>                 <a href="ident?i=sk_nocaps_add">sk_nocaps_add</a>(sk, <a href="ident?i=NETIF_F_GSO_MASK">NETIF_F_GSO_MASK</a>);
<a name="L1004" href="source/net/ipv4/tcp_output.c#L1004">1004</a>                 <a href="ident?i=tp">tp</a>-&gt;af_specific-&gt;calc_md5_hash(<a href="ident?i=opts">opts</a>.hash_location,
<a name="L1005" href="source/net/ipv4/tcp_output.c#L1005">1005</a>                                                md5, sk, <a href="ident?i=skb">skb</a>);
<a name="L1006" href="source/net/ipv4/tcp_output.c#L1006">1006</a>         }
<a name="L1007" href="source/net/ipv4/tcp_output.c#L1007">1007</a> #endif
<a name="L1008" href="source/net/ipv4/tcp_output.c#L1008">1008</a> 
<a name="L1009" href="source/net/ipv4/tcp_output.c#L1009">1009</a>         icsk-&gt;icsk_af_ops-&gt;send_check(sk, <a href="ident?i=skb">skb</a>);
<a name="L1010" href="source/net/ipv4/tcp_output.c#L1010">1010</a> 
<a name="L1011" href="source/net/ipv4/tcp_output.c#L1011">1011</a>         if (<a href="ident?i=likely">likely</a>(<a href="ident?i=tcb">tcb</a>-&gt;tcp_flags &amp; <a href="ident?i=TCPHDR_ACK">TCPHDR_ACK</a>))
<a name="L1012" href="source/net/ipv4/tcp_output.c#L1012">1012</a>                 <a href="ident?i=tcp_event_ack_sent">tcp_event_ack_sent</a>(sk, <a href="ident?i=tcp_skb_pcount">tcp_skb_pcount</a>(<a href="ident?i=skb">skb</a>));
<a name="L1013" href="source/net/ipv4/tcp_output.c#L1013">1013</a> 
<a name="L1014" href="source/net/ipv4/tcp_output.c#L1014">1014</a>         if (<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a> != tcp_header_size)
<a name="L1015" href="source/net/ipv4/tcp_output.c#L1015">1015</a>                 <a href="ident?i=tcp_event_data_sent">tcp_event_data_sent</a>(<a href="ident?i=tp">tp</a>, sk);
<a name="L1016" href="source/net/ipv4/tcp_output.c#L1016">1016</a> 
<a name="L1017" href="source/net/ipv4/tcp_output.c#L1017">1017</a>         if (<a href="ident?i=after">after</a>(<a href="ident?i=tcb">tcb</a>-&gt;end_seq, <a href="ident?i=tp">tp</a>-&gt;snd_nxt) || <a href="ident?i=tcb">tcb</a>-&gt;<a href="ident?i=seq">seq</a> == <a href="ident?i=tcb">tcb</a>-&gt;end_seq)
<a name="L1018" href="source/net/ipv4/tcp_output.c#L1018">1018</a>                 <a href="ident?i=TCP_ADD_STATS">TCP_ADD_STATS</a>(<a href="ident?i=sock_net">sock_net</a>(sk), TCP_MIB_OUTSEGS,
<a name="L1019" href="source/net/ipv4/tcp_output.c#L1019">1019</a>                               <a href="ident?i=tcp_skb_pcount">tcp_skb_pcount</a>(<a href="ident?i=skb">skb</a>));
<a name="L1020" href="source/net/ipv4/tcp_output.c#L1020">1020</a> 
<a name="L1021" href="source/net/ipv4/tcp_output.c#L1021">1021</a>         <b><i>/* OK, its time to fill skb_shinfo(skb)-&gt;gso_segs */</i></b>
<a name="L1022" href="source/net/ipv4/tcp_output.c#L1022">1022</a>         <a href="ident?i=skb_shinfo">skb_shinfo</a>(<a href="ident?i=skb">skb</a>)-&gt;gso_segs = <a href="ident?i=tcp_skb_pcount">tcp_skb_pcount</a>(<a href="ident?i=skb">skb</a>);
<a name="L1023" href="source/net/ipv4/tcp_output.c#L1023">1023</a> 
<a name="L1024" href="source/net/ipv4/tcp_output.c#L1024">1024</a>         <b><i>/* Our usage of tstamp should remain private */</i></b>
<a name="L1025" href="source/net/ipv4/tcp_output.c#L1025">1025</a>         <a href="ident?i=skb">skb</a>-&gt;tstamp.tv64 = 0;
<a name="L1026" href="source/net/ipv4/tcp_output.c#L1026">1026</a> 
<a name="L1027" href="source/net/ipv4/tcp_output.c#L1027">1027</a>         <b><i>/* Cleanup our debris for IP stacks */</i></b>
<a name="L1028" href="source/net/ipv4/tcp_output.c#L1028">1028</a>         <a href="ident?i=memset">memset</a>(<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=cb">cb</a>, 0, <a href="ident?i=max">max</a>(sizeof(struct <a href="ident?i=inet_skb_parm">inet_skb_parm</a>),
<a name="L1029" href="source/net/ipv4/tcp_output.c#L1029">1029</a>                                sizeof(struct <a href="ident?i=inet6_skb_parm">inet6_skb_parm</a>)));
<a name="L1030" href="source/net/ipv4/tcp_output.c#L1030">1030</a> 
<a name="L1031" href="source/net/ipv4/tcp_output.c#L1031">1031</a>         <a href="ident?i=err">err</a> = icsk-&gt;icsk_af_ops-&gt;queue_xmit(sk, <a href="ident?i=skb">skb</a>, &amp;inet-&gt;cork.fl);
<a name="L1032" href="source/net/ipv4/tcp_output.c#L1032">1032</a> 
<a name="L1033" href="source/net/ipv4/tcp_output.c#L1033">1033</a>         if (<a href="ident?i=likely">likely</a>(<a href="ident?i=err">err</a> &lt;= 0))
<a name="L1034" href="source/net/ipv4/tcp_output.c#L1034">1034</a>                 return <a href="ident?i=err">err</a>;
<a name="L1035" href="source/net/ipv4/tcp_output.c#L1035">1035</a> 
<a name="L1036" href="source/net/ipv4/tcp_output.c#L1036">1036</a>         <a href="ident?i=tcp_enter_cwr">tcp_enter_cwr</a>(sk);
<a name="L1037" href="source/net/ipv4/tcp_output.c#L1037">1037</a> 
<a name="L1038" href="source/net/ipv4/tcp_output.c#L1038">1038</a>         return <a href="ident?i=net_xmit_eval">net_xmit_eval</a>(<a href="ident?i=err">err</a>);
<a name="L1039" href="source/net/ipv4/tcp_output.c#L1039">1039</a> }
<a name="L1040" href="source/net/ipv4/tcp_output.c#L1040">1040</a> 
<a name="L1041" href="source/net/ipv4/tcp_output.c#L1041">1041</a> <b><i>/* This routine just queues the buffer for sending.</i></b>
<a name="L1042" href="source/net/ipv4/tcp_output.c#L1042">1042</a> <b><i> *</i></b>
<a name="L1043" href="source/net/ipv4/tcp_output.c#L1043">1043</a> <b><i> * NOTE: probe0 timer is not checked, do not forget tcp_push_pending_frames,</i></b>
<a name="L1044" href="source/net/ipv4/tcp_output.c#L1044">1044</a> <b><i> * otherwise socket can stall.</i></b>
<a name="L1045" href="source/net/ipv4/tcp_output.c#L1045">1045</a> <b><i> */</i></b>
<a name="L1046" href="source/net/ipv4/tcp_output.c#L1046">1046</a> static void <a href="ident?i=tcp_queue_skb">tcp_queue_skb</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L1047" href="source/net/ipv4/tcp_output.c#L1047">1047</a> {
<a name="L1048" href="source/net/ipv4/tcp_output.c#L1048">1048</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L1049" href="source/net/ipv4/tcp_output.c#L1049">1049</a> 
<a name="L1050" href="source/net/ipv4/tcp_output.c#L1050">1050</a>         <b><i>/* Advance write_seq and place onto the write_queue. */</i></b>
<a name="L1051" href="source/net/ipv4/tcp_output.c#L1051">1051</a>         <a href="ident?i=tp">tp</a>-&gt;write_seq = <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;end_seq;
<a name="L1052" href="source/net/ipv4/tcp_output.c#L1052">1052</a>         <a href="ident?i=__skb_header_release">__skb_header_release</a>(<a href="ident?i=skb">skb</a>);
<a name="L1053" href="source/net/ipv4/tcp_output.c#L1053">1053</a>         <a href="ident?i=tcp_add_write_queue_tail">tcp_add_write_queue_tail</a>(sk, <a href="ident?i=skb">skb</a>);
<a name="L1054" href="source/net/ipv4/tcp_output.c#L1054">1054</a>         sk-&gt;sk_wmem_queued += <a href="ident?i=skb">skb</a>-&gt;truesize;
<a name="L1055" href="source/net/ipv4/tcp_output.c#L1055">1055</a>         <a href="ident?i=sk_mem_charge">sk_mem_charge</a>(sk, <a href="ident?i=skb">skb</a>-&gt;truesize);
<a name="L1056" href="source/net/ipv4/tcp_output.c#L1056">1056</a> }
<a name="L1057" href="source/net/ipv4/tcp_output.c#L1057">1057</a> 
<a name="L1058" href="source/net/ipv4/tcp_output.c#L1058">1058</a> <b><i>/* Initialize TSO segments for a packet. */</i></b>
<a name="L1059" href="source/net/ipv4/tcp_output.c#L1059">1059</a> static void <a href="ident?i=tcp_set_skb_tso_segs">tcp_set_skb_tso_segs</a>(const struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
<a name="L1060" href="source/net/ipv4/tcp_output.c#L1060">1060</a>                                  unsigned int mss_now)
<a name="L1061" href="source/net/ipv4/tcp_output.c#L1061">1061</a> {
<a name="L1062" href="source/net/ipv4/tcp_output.c#L1062">1062</a>         struct <a href="ident?i=skb_shared_info">skb_shared_info</a> *shinfo = <a href="ident?i=skb_shinfo">skb_shinfo</a>(<a href="ident?i=skb">skb</a>);
<a name="L1063" href="source/net/ipv4/tcp_output.c#L1063">1063</a> 
<a name="L1064" href="source/net/ipv4/tcp_output.c#L1064">1064</a>         <b><i>/* Make sure we own this skb before messing gso_size/gso_segs */</i></b>
<a name="L1065" href="source/net/ipv4/tcp_output.c#L1065">1065</a>         <a href="ident?i=WARN_ON_ONCE">WARN_ON_ONCE</a>(<a href="ident?i=skb_cloned">skb_cloned</a>(<a href="ident?i=skb">skb</a>));
<a name="L1066" href="source/net/ipv4/tcp_output.c#L1066">1066</a> 
<a name="L1067" href="source/net/ipv4/tcp_output.c#L1067">1067</a>         if (<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a> &lt;= mss_now || <a href="ident?i=skb">skb</a>-&gt;ip_summed == <a href="ident?i=CHECKSUM_NONE">CHECKSUM_NONE</a>) {
<a name="L1068" href="source/net/ipv4/tcp_output.c#L1068">1068</a>                 <b><i>/* Avoid the costly divide in the normal</i></b>
<a name="L1069" href="source/net/ipv4/tcp_output.c#L1069">1069</a> <b><i>                 * non-TSO case.</i></b>
<a name="L1070" href="source/net/ipv4/tcp_output.c#L1070">1070</a> <b><i>                 */</i></b>
<a name="L1071" href="source/net/ipv4/tcp_output.c#L1071">1071</a>                 <a href="ident?i=tcp_skb_pcount_set">tcp_skb_pcount_set</a>(<a href="ident?i=skb">skb</a>, 1);
<a name="L1072" href="source/net/ipv4/tcp_output.c#L1072">1072</a>                 shinfo-&gt;gso_size = 0;
<a name="L1073" href="source/net/ipv4/tcp_output.c#L1073">1073</a>                 shinfo-&gt;gso_type = 0;
<a name="L1074" href="source/net/ipv4/tcp_output.c#L1074">1074</a>         } else {
<a name="L1075" href="source/net/ipv4/tcp_output.c#L1075">1075</a>                 <a href="ident?i=tcp_skb_pcount_set">tcp_skb_pcount_set</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=DIV_ROUND_UP">DIV_ROUND_UP</a>(<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a>, mss_now));
<a name="L1076" href="source/net/ipv4/tcp_output.c#L1076">1076</a>                 shinfo-&gt;gso_size = mss_now;
<a name="L1077" href="source/net/ipv4/tcp_output.c#L1077">1077</a>                 shinfo-&gt;gso_type = sk-&gt;sk_gso_type;
<a name="L1078" href="source/net/ipv4/tcp_output.c#L1078">1078</a>         }
<a name="L1079" href="source/net/ipv4/tcp_output.c#L1079">1079</a> }
<a name="L1080" href="source/net/ipv4/tcp_output.c#L1080">1080</a> 
<a name="L1081" href="source/net/ipv4/tcp_output.c#L1081">1081</a> <b><i>/* When a modification to fackets out becomes necessary, we need to check</i></b>
<a name="L1082" href="source/net/ipv4/tcp_output.c#L1082">1082</a> <b><i> * skb is counted to fackets_out or not.</i></b>
<a name="L1083" href="source/net/ipv4/tcp_output.c#L1083">1083</a> <b><i> */</i></b>
<a name="L1084" href="source/net/ipv4/tcp_output.c#L1084">1084</a> static void <a href="ident?i=tcp_adjust_fackets_out">tcp_adjust_fackets_out</a>(struct <a href="ident?i=sock">sock</a> *sk, const struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
<a name="L1085" href="source/net/ipv4/tcp_output.c#L1085">1085</a>                                    int decr)
<a name="L1086" href="source/net/ipv4/tcp_output.c#L1086">1086</a> {
<a name="L1087" href="source/net/ipv4/tcp_output.c#L1087">1087</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L1088" href="source/net/ipv4/tcp_output.c#L1088">1088</a> 
<a name="L1089" href="source/net/ipv4/tcp_output.c#L1089">1089</a>         if (!<a href="ident?i=tp">tp</a>-&gt;sacked_out || <a href="ident?i=tcp_is_reno">tcp_is_reno</a>(<a href="ident?i=tp">tp</a>))
<a name="L1090" href="source/net/ipv4/tcp_output.c#L1090">1090</a>                 return;
<a name="L1091" href="source/net/ipv4/tcp_output.c#L1091">1091</a> 
<a name="L1092" href="source/net/ipv4/tcp_output.c#L1092">1092</a>         if (<a href="ident?i=after">after</a>(<a href="ident?i=tcp_highest_sack_seq">tcp_highest_sack_seq</a>(<a href="ident?i=tp">tp</a>), <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=seq">seq</a>))
<a name="L1093" href="source/net/ipv4/tcp_output.c#L1093">1093</a>                 <a href="ident?i=tp">tp</a>-&gt;fackets_out -= decr;
<a name="L1094" href="source/net/ipv4/tcp_output.c#L1094">1094</a> }
<a name="L1095" href="source/net/ipv4/tcp_output.c#L1095">1095</a> 
<a name="L1096" href="source/net/ipv4/tcp_output.c#L1096">1096</a> <b><i>/* Pcount in the middle of the write queue got changed, we need to do various</i></b>
<a name="L1097" href="source/net/ipv4/tcp_output.c#L1097">1097</a> <b><i> * tweaks to fix counters</i></b>
<a name="L1098" href="source/net/ipv4/tcp_output.c#L1098">1098</a> <b><i> */</i></b>
<a name="L1099" href="source/net/ipv4/tcp_output.c#L1099">1099</a> static void <a href="ident?i=tcp_adjust_pcount">tcp_adjust_pcount</a>(struct <a href="ident?i=sock">sock</a> *sk, const struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, int decr)
<a name="L1100" href="source/net/ipv4/tcp_output.c#L1100">1100</a> {
<a name="L1101" href="source/net/ipv4/tcp_output.c#L1101">1101</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L1102" href="source/net/ipv4/tcp_output.c#L1102">1102</a> 
<a name="L1103" href="source/net/ipv4/tcp_output.c#L1103">1103</a>         <a href="ident?i=tp">tp</a>-&gt;packets_out -= decr;
<a name="L1104" href="source/net/ipv4/tcp_output.c#L1104">1104</a> 
<a name="L1105" href="source/net/ipv4/tcp_output.c#L1105">1105</a>         if (<a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;sacked &amp; <a href="ident?i=TCPCB_SACKED_ACKED">TCPCB_SACKED_ACKED</a>)
<a name="L1106" href="source/net/ipv4/tcp_output.c#L1106">1106</a>                 <a href="ident?i=tp">tp</a>-&gt;sacked_out -= decr;
<a name="L1107" href="source/net/ipv4/tcp_output.c#L1107">1107</a>         if (<a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;sacked &amp; <a href="ident?i=TCPCB_SACKED_RETRANS">TCPCB_SACKED_RETRANS</a>)
<a name="L1108" href="source/net/ipv4/tcp_output.c#L1108">1108</a>                 <a href="ident?i=tp">tp</a>-&gt;retrans_out -= decr;
<a name="L1109" href="source/net/ipv4/tcp_output.c#L1109">1109</a>         if (<a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;sacked &amp; <a href="ident?i=TCPCB_LOST">TCPCB_LOST</a>)
<a name="L1110" href="source/net/ipv4/tcp_output.c#L1110">1110</a>                 <a href="ident?i=tp">tp</a>-&gt;lost_out -= decr;
<a name="L1111" href="source/net/ipv4/tcp_output.c#L1111">1111</a> 
<a name="L1112" href="source/net/ipv4/tcp_output.c#L1112">1112</a>         <b><i>/* Reno case is special. Sigh... */</i></b>
<a name="L1113" href="source/net/ipv4/tcp_output.c#L1113">1113</a>         if (<a href="ident?i=tcp_is_reno">tcp_is_reno</a>(<a href="ident?i=tp">tp</a>) &amp;&amp; decr &gt; 0)
<a name="L1114" href="source/net/ipv4/tcp_output.c#L1114">1114</a>                 <a href="ident?i=tp">tp</a>-&gt;sacked_out -= <a href="ident?i=min_t">min_t</a>(<a href="ident?i=u32">u32</a>, <a href="ident?i=tp">tp</a>-&gt;sacked_out, decr);
<a name="L1115" href="source/net/ipv4/tcp_output.c#L1115">1115</a> 
<a name="L1116" href="source/net/ipv4/tcp_output.c#L1116">1116</a>         <a href="ident?i=tcp_adjust_fackets_out">tcp_adjust_fackets_out</a>(sk, <a href="ident?i=skb">skb</a>, decr);
<a name="L1117" href="source/net/ipv4/tcp_output.c#L1117">1117</a> 
<a name="L1118" href="source/net/ipv4/tcp_output.c#L1118">1118</a>         if (<a href="ident?i=tp">tp</a>-&gt;lost_skb_hint &amp;&amp;
<a name="L1119" href="source/net/ipv4/tcp_output.c#L1119">1119</a>             <a href="ident?i=before">before</a>(<a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=seq">seq</a>, <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=tp">tp</a>-&gt;lost_skb_hint)-&gt;<a href="ident?i=seq">seq</a>) &amp;&amp;
<a name="L1120" href="source/net/ipv4/tcp_output.c#L1120">1120</a>             (<a href="ident?i=tcp_is_fack">tcp_is_fack</a>(<a href="ident?i=tp">tp</a>) || (<a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;sacked &amp; <a href="ident?i=TCPCB_SACKED_ACKED">TCPCB_SACKED_ACKED</a>)))
<a name="L1121" href="source/net/ipv4/tcp_output.c#L1121">1121</a>                 <a href="ident?i=tp">tp</a>-&gt;lost_cnt_hint -= decr;
<a name="L1122" href="source/net/ipv4/tcp_output.c#L1122">1122</a> 
<a name="L1123" href="source/net/ipv4/tcp_output.c#L1123">1123</a>         <a href="ident?i=tcp_verify_left_out">tcp_verify_left_out</a>(<a href="ident?i=tp">tp</a>);
<a name="L1124" href="source/net/ipv4/tcp_output.c#L1124">1124</a> }
<a name="L1125" href="source/net/ipv4/tcp_output.c#L1125">1125</a> 
<a name="L1126" href="source/net/ipv4/tcp_output.c#L1126">1126</a> static void <a href="ident?i=tcp_fragment_tstamp">tcp_fragment_tstamp</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, struct <a href="ident?i=sk_buff">sk_buff</a> *skb2)
<a name="L1127" href="source/net/ipv4/tcp_output.c#L1127">1127</a> {
<a name="L1128" href="source/net/ipv4/tcp_output.c#L1128">1128</a>         struct <a href="ident?i=skb_shared_info">skb_shared_info</a> *shinfo = <a href="ident?i=skb_shinfo">skb_shinfo</a>(<a href="ident?i=skb">skb</a>);
<a name="L1129" href="source/net/ipv4/tcp_output.c#L1129">1129</a> 
<a name="L1130" href="source/net/ipv4/tcp_output.c#L1130">1130</a>         if (<a href="ident?i=unlikely">unlikely</a>(shinfo-&gt;tx_flags &amp; <a href="ident?i=SKBTX_ANY_TSTAMP">SKBTX_ANY_TSTAMP</a>) &amp;&amp;
<a name="L1131" href="source/net/ipv4/tcp_output.c#L1131">1131</a>             !<a href="ident?i=before">before</a>(shinfo-&gt;tskey, <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(skb2)-&gt;<a href="ident?i=seq">seq</a>)) {
<a name="L1132" href="source/net/ipv4/tcp_output.c#L1132">1132</a>                 struct <a href="ident?i=skb_shared_info">skb_shared_info</a> *shinfo2 = <a href="ident?i=skb_shinfo">skb_shinfo</a>(skb2);
<a name="L1133" href="source/net/ipv4/tcp_output.c#L1133">1133</a>                 <a href="ident?i=u8">u8</a> tsflags = shinfo-&gt;tx_flags &amp; <a href="ident?i=SKBTX_ANY_TSTAMP">SKBTX_ANY_TSTAMP</a>;
<a name="L1134" href="source/net/ipv4/tcp_output.c#L1134">1134</a> 
<a name="L1135" href="source/net/ipv4/tcp_output.c#L1135">1135</a>                 shinfo-&gt;tx_flags &amp;= ~tsflags;
<a name="L1136" href="source/net/ipv4/tcp_output.c#L1136">1136</a>                 shinfo2-&gt;tx_flags |= tsflags;
<a name="L1137" href="source/net/ipv4/tcp_output.c#L1137">1137</a>                 <a href="ident?i=swap">swap</a>(shinfo-&gt;tskey, shinfo2-&gt;tskey);
<a name="L1138" href="source/net/ipv4/tcp_output.c#L1138">1138</a>         }
<a name="L1139" href="source/net/ipv4/tcp_output.c#L1139">1139</a> }
<a name="L1140" href="source/net/ipv4/tcp_output.c#L1140">1140</a> 
<a name="L1141" href="source/net/ipv4/tcp_output.c#L1141">1141</a> <b><i>/* Function to create two new TCP segments.  Shrinks the given segment</i></b>
<a name="L1142" href="source/net/ipv4/tcp_output.c#L1142">1142</a> <b><i> * to the specified size and appends a new segment with the rest of the</i></b>
<a name="L1143" href="source/net/ipv4/tcp_output.c#L1143">1143</a> <b><i> * packet to the list.  This won't be called frequently, I hope.</i></b>
<a name="L1144" href="source/net/ipv4/tcp_output.c#L1144">1144</a> <b><i> * Remember, these are still headerless SKBs at this point.</i></b>
<a name="L1145" href="source/net/ipv4/tcp_output.c#L1145">1145</a> <b><i> */</i></b>
<a name="L1146" href="source/net/ipv4/tcp_output.c#L1146">1146</a> int <a href="ident?i=tcp_fragment">tcp_fragment</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, <a href="ident?i=u32">u32</a> <a href="ident?i=len">len</a>,
<a name="L1147" href="source/net/ipv4/tcp_output.c#L1147">1147</a>                  unsigned int mss_now, <a href="ident?i=gfp_t">gfp_t</a> gfp)
<a name="L1148" href="source/net/ipv4/tcp_output.c#L1148">1148</a> {
<a name="L1149" href="source/net/ipv4/tcp_output.c#L1149">1149</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L1150" href="source/net/ipv4/tcp_output.c#L1150">1150</a>         struct <a href="ident?i=sk_buff">sk_buff</a> *buff;
<a name="L1151" href="source/net/ipv4/tcp_output.c#L1151">1151</a>         int nsize, old_factor;
<a name="L1152" href="source/net/ipv4/tcp_output.c#L1152">1152</a>         int nlen;
<a name="L1153" href="source/net/ipv4/tcp_output.c#L1153">1153</a>         <a href="ident?i=u8">u8</a> <a href="ident?i=flags">flags</a>;
<a name="L1154" href="source/net/ipv4/tcp_output.c#L1154">1154</a> 
<a name="L1155" href="source/net/ipv4/tcp_output.c#L1155">1155</a>         if (<a href="ident?i=WARN_ON">WARN_ON</a>(<a href="ident?i=len">len</a> &gt; <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a>))
<a name="L1156" href="source/net/ipv4/tcp_output.c#L1156">1156</a>                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L1157" href="source/net/ipv4/tcp_output.c#L1157">1157</a> 
<a name="L1158" href="source/net/ipv4/tcp_output.c#L1158">1158</a>         nsize = <a href="ident?i=skb_headlen">skb_headlen</a>(<a href="ident?i=skb">skb</a>) - <a href="ident?i=len">len</a>;
<a name="L1159" href="source/net/ipv4/tcp_output.c#L1159">1159</a>         if (nsize &lt; 0)
<a name="L1160" href="source/net/ipv4/tcp_output.c#L1160">1160</a>                 nsize = 0;
<a name="L1161" href="source/net/ipv4/tcp_output.c#L1161">1161</a> 
<a name="L1162" href="source/net/ipv4/tcp_output.c#L1162">1162</a>         if (<a href="ident?i=skb_unclone">skb_unclone</a>(<a href="ident?i=skb">skb</a>, gfp))
<a name="L1163" href="source/net/ipv4/tcp_output.c#L1163">1163</a>                 return -<a href="ident?i=ENOMEM">ENOMEM</a>;
<a name="L1164" href="source/net/ipv4/tcp_output.c#L1164">1164</a> 
<a name="L1165" href="source/net/ipv4/tcp_output.c#L1165">1165</a>         <b><i>/* Get a new skb... force flag on. */</i></b>
<a name="L1166" href="source/net/ipv4/tcp_output.c#L1166">1166</a>         buff = <a href="ident?i=sk_stream_alloc_skb">sk_stream_alloc_skb</a>(sk, nsize, gfp);
<a name="L1167" href="source/net/ipv4/tcp_output.c#L1167">1167</a>         if (!buff)
<a name="L1168" href="source/net/ipv4/tcp_output.c#L1168">1168</a>                 return -<a href="ident?i=ENOMEM">ENOMEM</a>; <b><i>/* We'll just try again later. */</i></b>
<a name="L1169" href="source/net/ipv4/tcp_output.c#L1169">1169</a> 
<a name="L1170" href="source/net/ipv4/tcp_output.c#L1170">1170</a>         sk-&gt;sk_wmem_queued += buff-&gt;truesize;
<a name="L1171" href="source/net/ipv4/tcp_output.c#L1171">1171</a>         <a href="ident?i=sk_mem_charge">sk_mem_charge</a>(sk, buff-&gt;truesize);
<a name="L1172" href="source/net/ipv4/tcp_output.c#L1172">1172</a>         nlen = <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a> - <a href="ident?i=len">len</a> - nsize;
<a name="L1173" href="source/net/ipv4/tcp_output.c#L1173">1173</a>         buff-&gt;truesize += nlen;
<a name="L1174" href="source/net/ipv4/tcp_output.c#L1174">1174</a>         <a href="ident?i=skb">skb</a>-&gt;truesize -= nlen;
<a name="L1175" href="source/net/ipv4/tcp_output.c#L1175">1175</a> 
<a name="L1176" href="source/net/ipv4/tcp_output.c#L1176">1176</a>         <b><i>/* Correct the sequence numbers. */</i></b>
<a name="L1177" href="source/net/ipv4/tcp_output.c#L1177">1177</a>         <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(buff)-&gt;<a href="ident?i=seq">seq</a> = <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=seq">seq</a> + <a href="ident?i=len">len</a>;
<a name="L1178" href="source/net/ipv4/tcp_output.c#L1178">1178</a>         <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(buff)-&gt;end_seq = <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;end_seq;
<a name="L1179" href="source/net/ipv4/tcp_output.c#L1179">1179</a>         <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;end_seq = <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(buff)-&gt;<a href="ident?i=seq">seq</a>;
<a name="L1180" href="source/net/ipv4/tcp_output.c#L1180">1180</a> 
<a name="L1181" href="source/net/ipv4/tcp_output.c#L1181">1181</a>         <b><i>/* PSH and FIN should only be set in the second packet. */</i></b>
<a name="L1182" href="source/net/ipv4/tcp_output.c#L1182">1182</a>         <a href="ident?i=flags">flags</a> = <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;tcp_flags;
<a name="L1183" href="source/net/ipv4/tcp_output.c#L1183">1183</a>         <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;tcp_flags = <a href="ident?i=flags">flags</a> &amp; ~(<a href="ident?i=TCPHDR_FIN">TCPHDR_FIN</a> | <a href="ident?i=TCPHDR_PSH">TCPHDR_PSH</a>);
<a name="L1184" href="source/net/ipv4/tcp_output.c#L1184">1184</a>         <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(buff)-&gt;tcp_flags = <a href="ident?i=flags">flags</a>;
<a name="L1185" href="source/net/ipv4/tcp_output.c#L1185">1185</a>         <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(buff)-&gt;sacked = <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;sacked;
<a name="L1186" href="source/net/ipv4/tcp_output.c#L1186">1186</a> 
<a name="L1187" href="source/net/ipv4/tcp_output.c#L1187">1187</a>         if (!<a href="ident?i=skb_shinfo">skb_shinfo</a>(<a href="ident?i=skb">skb</a>)-&gt;nr_frags &amp;&amp; <a href="ident?i=skb">skb</a>-&gt;ip_summed != <a href="ident?i=CHECKSUM_PARTIAL">CHECKSUM_PARTIAL</a>) {
<a name="L1188" href="source/net/ipv4/tcp_output.c#L1188">1188</a>                 <b><i>/* Copy and checksum data tail into the new buffer. */</i></b>
<a name="L1189" href="source/net/ipv4/tcp_output.c#L1189">1189</a>                 buff-&gt;<a href="ident?i=csum">csum</a> = <a href="ident?i=csum_partial_copy_nocheck">csum_partial_copy_nocheck</a>(<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=data">data</a> + <a href="ident?i=len">len</a>,
<a name="L1190" href="source/net/ipv4/tcp_output.c#L1190">1190</a>                                                        <a href="ident?i=skb_put">skb_put</a>(buff, nsize),
<a name="L1191" href="source/net/ipv4/tcp_output.c#L1191">1191</a>                                                        nsize, 0);
<a name="L1192" href="source/net/ipv4/tcp_output.c#L1192">1192</a> 
<a name="L1193" href="source/net/ipv4/tcp_output.c#L1193">1193</a>                 <a href="ident?i=skb_trim">skb_trim</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=len">len</a>);
<a name="L1194" href="source/net/ipv4/tcp_output.c#L1194">1194</a> 
<a name="L1195" href="source/net/ipv4/tcp_output.c#L1195">1195</a>                 <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=csum">csum</a> = <a href="ident?i=csum_block_sub">csum_block_sub</a>(<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=csum">csum</a>, buff-&gt;<a href="ident?i=csum">csum</a>, <a href="ident?i=len">len</a>);
<a name="L1196" href="source/net/ipv4/tcp_output.c#L1196">1196</a>         } else {
<a name="L1197" href="source/net/ipv4/tcp_output.c#L1197">1197</a>                 <a href="ident?i=skb">skb</a>-&gt;ip_summed = <a href="ident?i=CHECKSUM_PARTIAL">CHECKSUM_PARTIAL</a>;
<a name="L1198" href="source/net/ipv4/tcp_output.c#L1198">1198</a>                 <a href="ident?i=skb_split">skb_split</a>(<a href="ident?i=skb">skb</a>, buff, <a href="ident?i=len">len</a>);
<a name="L1199" href="source/net/ipv4/tcp_output.c#L1199">1199</a>         }
<a name="L1200" href="source/net/ipv4/tcp_output.c#L1200">1200</a> 
<a name="L1201" href="source/net/ipv4/tcp_output.c#L1201">1201</a>         buff-&gt;ip_summed = <a href="ident?i=skb">skb</a>-&gt;ip_summed;
<a name="L1202" href="source/net/ipv4/tcp_output.c#L1202">1202</a> 
<a name="L1203" href="source/net/ipv4/tcp_output.c#L1203">1203</a>         buff-&gt;tstamp = <a href="ident?i=skb">skb</a>-&gt;tstamp;
<a name="L1204" href="source/net/ipv4/tcp_output.c#L1204">1204</a>         <a href="ident?i=tcp_fragment_tstamp">tcp_fragment_tstamp</a>(<a href="ident?i=skb">skb</a>, buff);
<a name="L1205" href="source/net/ipv4/tcp_output.c#L1205">1205</a> 
<a name="L1206" href="source/net/ipv4/tcp_output.c#L1206">1206</a>         old_factor = <a href="ident?i=tcp_skb_pcount">tcp_skb_pcount</a>(<a href="ident?i=skb">skb</a>);
<a name="L1207" href="source/net/ipv4/tcp_output.c#L1207">1207</a> 
<a name="L1208" href="source/net/ipv4/tcp_output.c#L1208">1208</a>         <b><i>/* Fix up tso_factor for both original and new SKB.  */</i></b>
<a name="L1209" href="source/net/ipv4/tcp_output.c#L1209">1209</a>         <a href="ident?i=tcp_set_skb_tso_segs">tcp_set_skb_tso_segs</a>(sk, <a href="ident?i=skb">skb</a>, mss_now);
<a name="L1210" href="source/net/ipv4/tcp_output.c#L1210">1210</a>         <a href="ident?i=tcp_set_skb_tso_segs">tcp_set_skb_tso_segs</a>(sk, buff, mss_now);
<a name="L1211" href="source/net/ipv4/tcp_output.c#L1211">1211</a> 
<a name="L1212" href="source/net/ipv4/tcp_output.c#L1212">1212</a>         <b><i>/* If this packet has been sent out already, we must</i></b>
<a name="L1213" href="source/net/ipv4/tcp_output.c#L1213">1213</a> <b><i>         * adjust the various packet counters.</i></b>
<a name="L1214" href="source/net/ipv4/tcp_output.c#L1214">1214</a> <b><i>         */</i></b>
<a name="L1215" href="source/net/ipv4/tcp_output.c#L1215">1215</a>         if (!<a href="ident?i=before">before</a>(<a href="ident?i=tp">tp</a>-&gt;snd_nxt, <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(buff)-&gt;end_seq)) {
<a name="L1216" href="source/net/ipv4/tcp_output.c#L1216">1216</a>                 int diff = old_factor - <a href="ident?i=tcp_skb_pcount">tcp_skb_pcount</a>(<a href="ident?i=skb">skb</a>) -
<a name="L1217" href="source/net/ipv4/tcp_output.c#L1217">1217</a>                         <a href="ident?i=tcp_skb_pcount">tcp_skb_pcount</a>(buff);
<a name="L1218" href="source/net/ipv4/tcp_output.c#L1218">1218</a> 
<a name="L1219" href="source/net/ipv4/tcp_output.c#L1219">1219</a>                 if (diff)
<a name="L1220" href="source/net/ipv4/tcp_output.c#L1220">1220</a>                         <a href="ident?i=tcp_adjust_pcount">tcp_adjust_pcount</a>(sk, <a href="ident?i=skb">skb</a>, diff);
<a name="L1221" href="source/net/ipv4/tcp_output.c#L1221">1221</a>         }
<a name="L1222" href="source/net/ipv4/tcp_output.c#L1222">1222</a> 
<a name="L1223" href="source/net/ipv4/tcp_output.c#L1223">1223</a>         <b><i>/* Link BUFF into the send queue. */</i></b>
<a name="L1224" href="source/net/ipv4/tcp_output.c#L1224">1224</a>         <a href="ident?i=__skb_header_release">__skb_header_release</a>(buff);
<a name="L1225" href="source/net/ipv4/tcp_output.c#L1225">1225</a>         <a href="ident?i=tcp_insert_write_queue_after">tcp_insert_write_queue_after</a>(<a href="ident?i=skb">skb</a>, buff, sk);
<a name="L1226" href="source/net/ipv4/tcp_output.c#L1226">1226</a> 
<a name="L1227" href="source/net/ipv4/tcp_output.c#L1227">1227</a>         return 0;
<a name="L1228" href="source/net/ipv4/tcp_output.c#L1228">1228</a> }
<a name="L1229" href="source/net/ipv4/tcp_output.c#L1229">1229</a> 
<a name="L1230" href="source/net/ipv4/tcp_output.c#L1230">1230</a> <b><i>/* This is similar to __pskb_pull_head() (it will go to core/skbuff.c</i></b>
<a name="L1231" href="source/net/ipv4/tcp_output.c#L1231">1231</a> <b><i> * eventually). The difference is that pulled data not copied, but</i></b>
<a name="L1232" href="source/net/ipv4/tcp_output.c#L1232">1232</a> <b><i> * immediately discarded.</i></b>
<a name="L1233" href="source/net/ipv4/tcp_output.c#L1233">1233</a> <b><i> */</i></b>
<a name="L1234" href="source/net/ipv4/tcp_output.c#L1234">1234</a> static void <a href="ident?i=__pskb_trim_head">__pskb_trim_head</a>(struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, int <a href="ident?i=len">len</a>)
<a name="L1235" href="source/net/ipv4/tcp_output.c#L1235">1235</a> {
<a name="L1236" href="source/net/ipv4/tcp_output.c#L1236">1236</a>         struct <a href="ident?i=skb_shared_info">skb_shared_info</a> *shinfo;
<a name="L1237" href="source/net/ipv4/tcp_output.c#L1237">1237</a>         int <a href="ident?i=i">i</a>, k, <a href="ident?i=eat">eat</a>;
<a name="L1238" href="source/net/ipv4/tcp_output.c#L1238">1238</a> 
<a name="L1239" href="source/net/ipv4/tcp_output.c#L1239">1239</a>         <a href="ident?i=eat">eat</a> = <a href="ident?i=min_t">min_t</a>(int, <a href="ident?i=len">len</a>, <a href="ident?i=skb_headlen">skb_headlen</a>(<a href="ident?i=skb">skb</a>));
<a name="L1240" href="source/net/ipv4/tcp_output.c#L1240">1240</a>         if (<a href="ident?i=eat">eat</a>) {
<a name="L1241" href="source/net/ipv4/tcp_output.c#L1241">1241</a>                 <a href="ident?i=__skb_pull">__skb_pull</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=eat">eat</a>);
<a name="L1242" href="source/net/ipv4/tcp_output.c#L1242">1242</a>                 <a href="ident?i=len">len</a> -= <a href="ident?i=eat">eat</a>;
<a name="L1243" href="source/net/ipv4/tcp_output.c#L1243">1243</a>                 if (!<a href="ident?i=len">len</a>)
<a name="L1244" href="source/net/ipv4/tcp_output.c#L1244">1244</a>                         return;
<a name="L1245" href="source/net/ipv4/tcp_output.c#L1245">1245</a>         }
<a name="L1246" href="source/net/ipv4/tcp_output.c#L1246">1246</a>         <a href="ident?i=eat">eat</a> = <a href="ident?i=len">len</a>;
<a name="L1247" href="source/net/ipv4/tcp_output.c#L1247">1247</a>         k = 0;
<a name="L1248" href="source/net/ipv4/tcp_output.c#L1248">1248</a>         shinfo = <a href="ident?i=skb_shinfo">skb_shinfo</a>(<a href="ident?i=skb">skb</a>);
<a name="L1249" href="source/net/ipv4/tcp_output.c#L1249">1249</a>         for (<a href="ident?i=i">i</a> = 0; <a href="ident?i=i">i</a> &lt; shinfo-&gt;nr_frags; <a href="ident?i=i">i</a>++) {
<a name="L1250" href="source/net/ipv4/tcp_output.c#L1250">1250</a>                 int <a href="ident?i=size">size</a> = <a href="ident?i=skb_frag_size">skb_frag_size</a>(&amp;shinfo-&gt;frags[<a href="ident?i=i">i</a>]);
<a name="L1251" href="source/net/ipv4/tcp_output.c#L1251">1251</a> 
<a name="L1252" href="source/net/ipv4/tcp_output.c#L1252">1252</a>                 if (<a href="ident?i=size">size</a> &lt;= <a href="ident?i=eat">eat</a>) {
<a name="L1253" href="source/net/ipv4/tcp_output.c#L1253">1253</a>                         <a href="ident?i=skb_frag_unref">skb_frag_unref</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=i">i</a>);
<a name="L1254" href="source/net/ipv4/tcp_output.c#L1254">1254</a>                         <a href="ident?i=eat">eat</a> -= <a href="ident?i=size">size</a>;
<a name="L1255" href="source/net/ipv4/tcp_output.c#L1255">1255</a>                 } else {
<a name="L1256" href="source/net/ipv4/tcp_output.c#L1256">1256</a>                         shinfo-&gt;frags[k] = shinfo-&gt;frags[<a href="ident?i=i">i</a>];
<a name="L1257" href="source/net/ipv4/tcp_output.c#L1257">1257</a>                         if (<a href="ident?i=eat">eat</a>) {
<a name="L1258" href="source/net/ipv4/tcp_output.c#L1258">1258</a>                                 shinfo-&gt;frags[k].<a href="ident?i=page_offset">page_offset</a> += <a href="ident?i=eat">eat</a>;
<a name="L1259" href="source/net/ipv4/tcp_output.c#L1259">1259</a>                                 <a href="ident?i=skb_frag_size_sub">skb_frag_size_sub</a>(&amp;shinfo-&gt;frags[k], <a href="ident?i=eat">eat</a>);
<a name="L1260" href="source/net/ipv4/tcp_output.c#L1260">1260</a>                                 <a href="ident?i=eat">eat</a> = 0;
<a name="L1261" href="source/net/ipv4/tcp_output.c#L1261">1261</a>                         }
<a name="L1262" href="source/net/ipv4/tcp_output.c#L1262">1262</a>                         k++;
<a name="L1263" href="source/net/ipv4/tcp_output.c#L1263">1263</a>                 }
<a name="L1264" href="source/net/ipv4/tcp_output.c#L1264">1264</a>         }
<a name="L1265" href="source/net/ipv4/tcp_output.c#L1265">1265</a>         shinfo-&gt;nr_frags = k;
<a name="L1266" href="source/net/ipv4/tcp_output.c#L1266">1266</a> 
<a name="L1267" href="source/net/ipv4/tcp_output.c#L1267">1267</a>         <a href="ident?i=skb_reset_tail_pointer">skb_reset_tail_pointer</a>(<a href="ident?i=skb">skb</a>);
<a name="L1268" href="source/net/ipv4/tcp_output.c#L1268">1268</a>         <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=data_len">data_len</a> -= <a href="ident?i=len">len</a>;
<a name="L1269" href="source/net/ipv4/tcp_output.c#L1269">1269</a>         <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a> = <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=data_len">data_len</a>;
<a name="L1270" href="source/net/ipv4/tcp_output.c#L1270">1270</a> }
<a name="L1271" href="source/net/ipv4/tcp_output.c#L1271">1271</a> 
<a name="L1272" href="source/net/ipv4/tcp_output.c#L1272">1272</a> <b><i>/* Remove acked data from a packet in the transmit queue. */</i></b>
<a name="L1273" href="source/net/ipv4/tcp_output.c#L1273">1273</a> int <a href="ident?i=tcp_trim_head">tcp_trim_head</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, <a href="ident?i=u32">u32</a> <a href="ident?i=len">len</a>)
<a name="L1274" href="source/net/ipv4/tcp_output.c#L1274">1274</a> {
<a name="L1275" href="source/net/ipv4/tcp_output.c#L1275">1275</a>         if (<a href="ident?i=skb_unclone">skb_unclone</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=GFP_ATOMIC">GFP_ATOMIC</a>))
<a name="L1276" href="source/net/ipv4/tcp_output.c#L1276">1276</a>                 return -<a href="ident?i=ENOMEM">ENOMEM</a>;
<a name="L1277" href="source/net/ipv4/tcp_output.c#L1277">1277</a> 
<a name="L1278" href="source/net/ipv4/tcp_output.c#L1278">1278</a>         <a href="ident?i=__pskb_trim_head">__pskb_trim_head</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=len">len</a>);
<a name="L1279" href="source/net/ipv4/tcp_output.c#L1279">1279</a> 
<a name="L1280" href="source/net/ipv4/tcp_output.c#L1280">1280</a>         <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=seq">seq</a> += <a href="ident?i=len">len</a>;
<a name="L1281" href="source/net/ipv4/tcp_output.c#L1281">1281</a>         <a href="ident?i=skb">skb</a>-&gt;ip_summed = <a href="ident?i=CHECKSUM_PARTIAL">CHECKSUM_PARTIAL</a>;
<a name="L1282" href="source/net/ipv4/tcp_output.c#L1282">1282</a> 
<a name="L1283" href="source/net/ipv4/tcp_output.c#L1283">1283</a>         <a href="ident?i=skb">skb</a>-&gt;truesize        -= <a href="ident?i=len">len</a>;
<a name="L1284" href="source/net/ipv4/tcp_output.c#L1284">1284</a>         sk-&gt;sk_wmem_queued   -= <a href="ident?i=len">len</a>;
<a name="L1285" href="source/net/ipv4/tcp_output.c#L1285">1285</a>         <a href="ident?i=sk_mem_uncharge">sk_mem_uncharge</a>(sk, <a href="ident?i=len">len</a>);
<a name="L1286" href="source/net/ipv4/tcp_output.c#L1286">1286</a>         <a href="ident?i=sock_set_flag">sock_set_flag</a>(sk, SOCK_QUEUE_SHRUNK);
<a name="L1287" href="source/net/ipv4/tcp_output.c#L1287">1287</a> 
<a name="L1288" href="source/net/ipv4/tcp_output.c#L1288">1288</a>         <b><i>/* Any change of skb-&gt;len requires recalculation of tso factor. */</i></b>
<a name="L1289" href="source/net/ipv4/tcp_output.c#L1289">1289</a>         if (<a href="ident?i=tcp_skb_pcount">tcp_skb_pcount</a>(<a href="ident?i=skb">skb</a>) &gt; 1)
<a name="L1290" href="source/net/ipv4/tcp_output.c#L1290">1290</a>                 <a href="ident?i=tcp_set_skb_tso_segs">tcp_set_skb_tso_segs</a>(sk, <a href="ident?i=skb">skb</a>, <a href="ident?i=tcp_skb_mss">tcp_skb_mss</a>(<a href="ident?i=skb">skb</a>));
<a name="L1291" href="source/net/ipv4/tcp_output.c#L1291">1291</a> 
<a name="L1292" href="source/net/ipv4/tcp_output.c#L1292">1292</a>         return 0;
<a name="L1293" href="source/net/ipv4/tcp_output.c#L1293">1293</a> }
<a name="L1294" href="source/net/ipv4/tcp_output.c#L1294">1294</a> 
<a name="L1295" href="source/net/ipv4/tcp_output.c#L1295">1295</a> <b><i>/* Calculate MSS not accounting any TCP options.  */</i></b>
<a name="L1296" href="source/net/ipv4/tcp_output.c#L1296">1296</a> static inline int <a href="ident?i=__tcp_mtu_to_mss">__tcp_mtu_to_mss</a>(struct <a href="ident?i=sock">sock</a> *sk, int pmtu)
<a name="L1297" href="source/net/ipv4/tcp_output.c#L1297">1297</a> {
<a name="L1298" href="source/net/ipv4/tcp_output.c#L1298">1298</a>         const struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L1299" href="source/net/ipv4/tcp_output.c#L1299">1299</a>         const struct <a href="ident?i=inet_connection_sock">inet_connection_sock</a> *icsk = <a href="ident?i=inet_csk">inet_csk</a>(sk);
<a name="L1300" href="source/net/ipv4/tcp_output.c#L1300">1300</a>         int mss_now;
<a name="L1301" href="source/net/ipv4/tcp_output.c#L1301">1301</a> 
<a name="L1302" href="source/net/ipv4/tcp_output.c#L1302">1302</a>         <b><i>/* Calculate base mss without TCP options:</i></b>
<a name="L1303" href="source/net/ipv4/tcp_output.c#L1303">1303</a> <b><i>           It is MMS_S - sizeof(tcphdr) of rfc1122</i></b>
<a name="L1304" href="source/net/ipv4/tcp_output.c#L1304">1304</a> <b><i>         */</i></b>
<a name="L1305" href="source/net/ipv4/tcp_output.c#L1305">1305</a>         mss_now = pmtu - icsk-&gt;icsk_af_ops-&gt;net_header_len - sizeof(struct <a href="ident?i=tcphdr">tcphdr</a>);
<a name="L1306" href="source/net/ipv4/tcp_output.c#L1306">1306</a> 
<a name="L1307" href="source/net/ipv4/tcp_output.c#L1307">1307</a>         <b><i>/* IPv6 adds a frag_hdr in case RTAX_FEATURE_ALLFRAG is set */</i></b>
<a name="L1308" href="source/net/ipv4/tcp_output.c#L1308">1308</a>         if (icsk-&gt;icsk_af_ops-&gt;net_frag_header_len) {
<a name="L1309" href="source/net/ipv4/tcp_output.c#L1309">1309</a>                 const struct <a href="ident?i=dst_entry">dst_entry</a> *<a href="ident?i=dst">dst</a> = <a href="ident?i=__sk_dst_get">__sk_dst_get</a>(sk);
<a name="L1310" href="source/net/ipv4/tcp_output.c#L1310">1310</a> 
<a name="L1311" href="source/net/ipv4/tcp_output.c#L1311">1311</a>                 if (<a href="ident?i=dst">dst</a> &amp;&amp; <a href="ident?i=dst_allfrag">dst_allfrag</a>(<a href="ident?i=dst">dst</a>))
<a name="L1312" href="source/net/ipv4/tcp_output.c#L1312">1312</a>                         mss_now -= icsk-&gt;icsk_af_ops-&gt;net_frag_header_len;
<a name="L1313" href="source/net/ipv4/tcp_output.c#L1313">1313</a>         }
<a name="L1314" href="source/net/ipv4/tcp_output.c#L1314">1314</a> 
<a name="L1315" href="source/net/ipv4/tcp_output.c#L1315">1315</a>         <b><i>/* Clamp it (mss_clamp does not include tcp options) */</i></b>
<a name="L1316" href="source/net/ipv4/tcp_output.c#L1316">1316</a>         if (mss_now &gt; <a href="ident?i=tp">tp</a>-&gt;rx_opt.mss_clamp)
<a name="L1317" href="source/net/ipv4/tcp_output.c#L1317">1317</a>                 mss_now = <a href="ident?i=tp">tp</a>-&gt;rx_opt.mss_clamp;
<a name="L1318" href="source/net/ipv4/tcp_output.c#L1318">1318</a> 
<a name="L1319" href="source/net/ipv4/tcp_output.c#L1319">1319</a>         <b><i>/* Now subtract optional transport overhead */</i></b>
<a name="L1320" href="source/net/ipv4/tcp_output.c#L1320">1320</a>         mss_now -= icsk-&gt;icsk_ext_hdr_len;
<a name="L1321" href="source/net/ipv4/tcp_output.c#L1321">1321</a> 
<a name="L1322" href="source/net/ipv4/tcp_output.c#L1322">1322</a>         <b><i>/* Then reserve room for full set of TCP options and 8 bytes of data */</i></b>
<a name="L1323" href="source/net/ipv4/tcp_output.c#L1323">1323</a>         if (mss_now &lt; 48)
<a name="L1324" href="source/net/ipv4/tcp_output.c#L1324">1324</a>                 mss_now = 48;
<a name="L1325" href="source/net/ipv4/tcp_output.c#L1325">1325</a>         return mss_now;
<a name="L1326" href="source/net/ipv4/tcp_output.c#L1326">1326</a> }
<a name="L1327" href="source/net/ipv4/tcp_output.c#L1327">1327</a> 
<a name="L1328" href="source/net/ipv4/tcp_output.c#L1328">1328</a> <b><i>/* Calculate MSS. Not accounting for SACKs here.  */</i></b>
<a name="L1329" href="source/net/ipv4/tcp_output.c#L1329">1329</a> int <a href="ident?i=tcp_mtu_to_mss">tcp_mtu_to_mss</a>(struct <a href="ident?i=sock">sock</a> *sk, int pmtu)
<a name="L1330" href="source/net/ipv4/tcp_output.c#L1330">1330</a> {
<a name="L1331" href="source/net/ipv4/tcp_output.c#L1331">1331</a>         <b><i>/* Subtract TCP options size, not including SACKs */</i></b>
<a name="L1332" href="source/net/ipv4/tcp_output.c#L1332">1332</a>         return <a href="ident?i=__tcp_mtu_to_mss">__tcp_mtu_to_mss</a>(sk, pmtu) -
<a name="L1333" href="source/net/ipv4/tcp_output.c#L1333">1333</a>                (<a href="ident?i=tcp_sk">tcp_sk</a>(sk)-&gt;tcp_header_len - sizeof(struct <a href="ident?i=tcphdr">tcphdr</a>));
<a name="L1334" href="source/net/ipv4/tcp_output.c#L1334">1334</a> }
<a name="L1335" href="source/net/ipv4/tcp_output.c#L1335">1335</a> 
<a name="L1336" href="source/net/ipv4/tcp_output.c#L1336">1336</a> <b><i>/* Inverse of above */</i></b>
<a name="L1337" href="source/net/ipv4/tcp_output.c#L1337">1337</a> int <a href="ident?i=tcp_mss_to_mtu">tcp_mss_to_mtu</a>(struct <a href="ident?i=sock">sock</a> *sk, int mss)
<a name="L1338" href="source/net/ipv4/tcp_output.c#L1338">1338</a> {
<a name="L1339" href="source/net/ipv4/tcp_output.c#L1339">1339</a>         const struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L1340" href="source/net/ipv4/tcp_output.c#L1340">1340</a>         const struct <a href="ident?i=inet_connection_sock">inet_connection_sock</a> *icsk = <a href="ident?i=inet_csk">inet_csk</a>(sk);
<a name="L1341" href="source/net/ipv4/tcp_output.c#L1341">1341</a>         int <a href="ident?i=mtu">mtu</a>;
<a name="L1342" href="source/net/ipv4/tcp_output.c#L1342">1342</a> 
<a name="L1343" href="source/net/ipv4/tcp_output.c#L1343">1343</a>         <a href="ident?i=mtu">mtu</a> = mss +
<a name="L1344" href="source/net/ipv4/tcp_output.c#L1344">1344</a>               <a href="ident?i=tp">tp</a>-&gt;tcp_header_len +
<a name="L1345" href="source/net/ipv4/tcp_output.c#L1345">1345</a>               icsk-&gt;icsk_ext_hdr_len +
<a name="L1346" href="source/net/ipv4/tcp_output.c#L1346">1346</a>               icsk-&gt;icsk_af_ops-&gt;net_header_len;
<a name="L1347" href="source/net/ipv4/tcp_output.c#L1347">1347</a> 
<a name="L1348" href="source/net/ipv4/tcp_output.c#L1348">1348</a>         <b><i>/* IPv6 adds a frag_hdr in case RTAX_FEATURE_ALLFRAG is set */</i></b>
<a name="L1349" href="source/net/ipv4/tcp_output.c#L1349">1349</a>         if (icsk-&gt;icsk_af_ops-&gt;net_frag_header_len) {
<a name="L1350" href="source/net/ipv4/tcp_output.c#L1350">1350</a>                 const struct <a href="ident?i=dst_entry">dst_entry</a> *<a href="ident?i=dst">dst</a> = <a href="ident?i=__sk_dst_get">__sk_dst_get</a>(sk);
<a name="L1351" href="source/net/ipv4/tcp_output.c#L1351">1351</a> 
<a name="L1352" href="source/net/ipv4/tcp_output.c#L1352">1352</a>                 if (<a href="ident?i=dst">dst</a> &amp;&amp; <a href="ident?i=dst_allfrag">dst_allfrag</a>(<a href="ident?i=dst">dst</a>))
<a name="L1353" href="source/net/ipv4/tcp_output.c#L1353">1353</a>                         <a href="ident?i=mtu">mtu</a> += icsk-&gt;icsk_af_ops-&gt;net_frag_header_len;
<a name="L1354" href="source/net/ipv4/tcp_output.c#L1354">1354</a>         }
<a name="L1355" href="source/net/ipv4/tcp_output.c#L1355">1355</a>         return <a href="ident?i=mtu">mtu</a>;
<a name="L1356" href="source/net/ipv4/tcp_output.c#L1356">1356</a> }
<a name="L1357" href="source/net/ipv4/tcp_output.c#L1357">1357</a> 
<a name="L1358" href="source/net/ipv4/tcp_output.c#L1358">1358</a> <b><i>/* MTU probing init per socket */</i></b>
<a name="L1359" href="source/net/ipv4/tcp_output.c#L1359">1359</a> void <a href="ident?i=tcp_mtup_init">tcp_mtup_init</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L1360" href="source/net/ipv4/tcp_output.c#L1360">1360</a> {
<a name="L1361" href="source/net/ipv4/tcp_output.c#L1361">1361</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L1362" href="source/net/ipv4/tcp_output.c#L1362">1362</a>         struct <a href="ident?i=inet_connection_sock">inet_connection_sock</a> *icsk = <a href="ident?i=inet_csk">inet_csk</a>(sk);
<a name="L1363" href="source/net/ipv4/tcp_output.c#L1363">1363</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=sock_net">sock_net</a>(sk);
<a name="L1364" href="source/net/ipv4/tcp_output.c#L1364">1364</a> 
<a name="L1365" href="source/net/ipv4/tcp_output.c#L1365">1365</a>         icsk-&gt;icsk_mtup.<a href="ident?i=enabled">enabled</a> = <a href="ident?i=net">net</a>-&gt;ipv4.sysctl_tcp_mtu_probing &gt; 1;
<a name="L1366" href="source/net/ipv4/tcp_output.c#L1366">1366</a>         icsk-&gt;icsk_mtup.search_high = <a href="ident?i=tp">tp</a>-&gt;rx_opt.mss_clamp + sizeof(struct <a href="ident?i=tcphdr">tcphdr</a>) +
<a name="L1367" href="source/net/ipv4/tcp_output.c#L1367">1367</a>                                icsk-&gt;icsk_af_ops-&gt;net_header_len;
<a name="L1368" href="source/net/ipv4/tcp_output.c#L1368">1368</a>         icsk-&gt;icsk_mtup.search_low = <a href="ident?i=tcp_mss_to_mtu">tcp_mss_to_mtu</a>(sk, <a href="ident?i=net">net</a>-&gt;ipv4.sysctl_tcp_base_mss);
<a name="L1369" href="source/net/ipv4/tcp_output.c#L1369">1369</a>         icsk-&gt;icsk_mtup.probe_size = 0;
<a name="L1370" href="source/net/ipv4/tcp_output.c#L1370">1370</a>         if (icsk-&gt;icsk_mtup.<a href="ident?i=enabled">enabled</a>)
<a name="L1371" href="source/net/ipv4/tcp_output.c#L1371">1371</a>                 icsk-&gt;icsk_mtup.probe_timestamp = <a href="ident?i=tcp_time_stamp">tcp_time_stamp</a>;
<a name="L1372" href="source/net/ipv4/tcp_output.c#L1372">1372</a> }
<a name="L1373" href="source/net/ipv4/tcp_output.c#L1373">1373</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=tcp_mtup_init">tcp_mtup_init</a>);
<a name="L1374" href="source/net/ipv4/tcp_output.c#L1374">1374</a> 
<a name="L1375" href="source/net/ipv4/tcp_output.c#L1375">1375</a> <b><i>/* This function synchronize snd mss to current pmtu/exthdr set.</i></b>
<a name="L1376" href="source/net/ipv4/tcp_output.c#L1376">1376</a> <b><i></i></b>
<a name="L1377" href="source/net/ipv4/tcp_output.c#L1377">1377</a> <b><i>   tp-&gt;rx_opt.user_mss is mss set by user by TCP_MAXSEG. It does NOT counts</i></b>
<a name="L1378" href="source/net/ipv4/tcp_output.c#L1378">1378</a> <b><i>   for TCP options, but includes only bare TCP header.</i></b>
<a name="L1379" href="source/net/ipv4/tcp_output.c#L1379">1379</a> <b><i></i></b>
<a name="L1380" href="source/net/ipv4/tcp_output.c#L1380">1380</a> <b><i>   tp-&gt;rx_opt.mss_clamp is mss negotiated at connection setup.</i></b>
<a name="L1381" href="source/net/ipv4/tcp_output.c#L1381">1381</a> <b><i>   It is minimum of user_mss and mss received with SYN.</i></b>
<a name="L1382" href="source/net/ipv4/tcp_output.c#L1382">1382</a> <b><i>   It also does not include TCP options.</i></b>
<a name="L1383" href="source/net/ipv4/tcp_output.c#L1383">1383</a> <b><i></i></b>
<a name="L1384" href="source/net/ipv4/tcp_output.c#L1384">1384</a> <b><i>   inet_csk(sk)-&gt;icsk_pmtu_cookie is last pmtu, seen by this function.</i></b>
<a name="L1385" href="source/net/ipv4/tcp_output.c#L1385">1385</a> <b><i></i></b>
<a name="L1386" href="source/net/ipv4/tcp_output.c#L1386">1386</a> <b><i>   tp-&gt;mss_cache is current effective sending mss, including</i></b>
<a name="L1387" href="source/net/ipv4/tcp_output.c#L1387">1387</a> <b><i>   all tcp options except for SACKs. It is evaluated,</i></b>
<a name="L1388" href="source/net/ipv4/tcp_output.c#L1388">1388</a> <b><i>   taking into account current pmtu, but never exceeds</i></b>
<a name="L1389" href="source/net/ipv4/tcp_output.c#L1389">1389</a> <b><i>   tp-&gt;rx_opt.mss_clamp.</i></b>
<a name="L1390" href="source/net/ipv4/tcp_output.c#L1390">1390</a> <b><i></i></b>
<a name="L1391" href="source/net/ipv4/tcp_output.c#L1391">1391</a> <b><i>   NOTE1. rfc1122 clearly states that advertised MSS</i></b>
<a name="L1392" href="source/net/ipv4/tcp_output.c#L1392">1392</a> <b><i>   DOES NOT include either tcp or ip options.</i></b>
<a name="L1393" href="source/net/ipv4/tcp_output.c#L1393">1393</a> <b><i></i></b>
<a name="L1394" href="source/net/ipv4/tcp_output.c#L1394">1394</a> <b><i>   NOTE2. inet_csk(sk)-&gt;icsk_pmtu_cookie and tp-&gt;mss_cache</i></b>
<a name="L1395" href="source/net/ipv4/tcp_output.c#L1395">1395</a> <b><i>   are READ ONLY outside this function.         --ANK (980731)</i></b>
<a name="L1396" href="source/net/ipv4/tcp_output.c#L1396">1396</a> <b><i> */</i></b>
<a name="L1397" href="source/net/ipv4/tcp_output.c#L1397">1397</a> unsigned int <a href="ident?i=tcp_sync_mss">tcp_sync_mss</a>(struct <a href="ident?i=sock">sock</a> *sk, <a href="ident?i=u32">u32</a> pmtu)
<a name="L1398" href="source/net/ipv4/tcp_output.c#L1398">1398</a> {
<a name="L1399" href="source/net/ipv4/tcp_output.c#L1399">1399</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L1400" href="source/net/ipv4/tcp_output.c#L1400">1400</a>         struct <a href="ident?i=inet_connection_sock">inet_connection_sock</a> *icsk = <a href="ident?i=inet_csk">inet_csk</a>(sk);
<a name="L1401" href="source/net/ipv4/tcp_output.c#L1401">1401</a>         int mss_now;
<a name="L1402" href="source/net/ipv4/tcp_output.c#L1402">1402</a> 
<a name="L1403" href="source/net/ipv4/tcp_output.c#L1403">1403</a>         if (icsk-&gt;icsk_mtup.search_high &gt; pmtu)
<a name="L1404" href="source/net/ipv4/tcp_output.c#L1404">1404</a>                 icsk-&gt;icsk_mtup.search_high = pmtu;
<a name="L1405" href="source/net/ipv4/tcp_output.c#L1405">1405</a> 
<a name="L1406" href="source/net/ipv4/tcp_output.c#L1406">1406</a>         mss_now = <a href="ident?i=tcp_mtu_to_mss">tcp_mtu_to_mss</a>(sk, pmtu);
<a name="L1407" href="source/net/ipv4/tcp_output.c#L1407">1407</a>         mss_now = <a href="ident?i=tcp_bound_to_half_wnd">tcp_bound_to_half_wnd</a>(<a href="ident?i=tp">tp</a>, mss_now);
<a name="L1408" href="source/net/ipv4/tcp_output.c#L1408">1408</a> 
<a name="L1409" href="source/net/ipv4/tcp_output.c#L1409">1409</a>         <b><i>/* And store cached results */</i></b>
<a name="L1410" href="source/net/ipv4/tcp_output.c#L1410">1410</a>         icsk-&gt;icsk_pmtu_cookie = pmtu;
<a name="L1411" href="source/net/ipv4/tcp_output.c#L1411">1411</a>         if (icsk-&gt;icsk_mtup.<a href="ident?i=enabled">enabled</a>)
<a name="L1412" href="source/net/ipv4/tcp_output.c#L1412">1412</a>                 mss_now = <a href="ident?i=min">min</a>(mss_now, <a href="ident?i=tcp_mtu_to_mss">tcp_mtu_to_mss</a>(sk, icsk-&gt;icsk_mtup.search_low));
<a name="L1413" href="source/net/ipv4/tcp_output.c#L1413">1413</a>         <a href="ident?i=tp">tp</a>-&gt;mss_cache = mss_now;
<a name="L1414" href="source/net/ipv4/tcp_output.c#L1414">1414</a> 
<a name="L1415" href="source/net/ipv4/tcp_output.c#L1415">1415</a>         return mss_now;
<a name="L1416" href="source/net/ipv4/tcp_output.c#L1416">1416</a> }
<a name="L1417" href="source/net/ipv4/tcp_output.c#L1417">1417</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=tcp_sync_mss">tcp_sync_mss</a>);
<a name="L1418" href="source/net/ipv4/tcp_output.c#L1418">1418</a> 
<a name="L1419" href="source/net/ipv4/tcp_output.c#L1419">1419</a> <b><i>/* Compute the current effective MSS, taking SACKs and IP options,</i></b>
<a name="L1420" href="source/net/ipv4/tcp_output.c#L1420">1420</a> <b><i> * and even PMTU discovery events into account.</i></b>
<a name="L1421" href="source/net/ipv4/tcp_output.c#L1421">1421</a> <b><i> */</i></b>
<a name="L1422" href="source/net/ipv4/tcp_output.c#L1422">1422</a> unsigned int <a href="ident?i=tcp_current_mss">tcp_current_mss</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L1423" href="source/net/ipv4/tcp_output.c#L1423">1423</a> {
<a name="L1424" href="source/net/ipv4/tcp_output.c#L1424">1424</a>         const struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L1425" href="source/net/ipv4/tcp_output.c#L1425">1425</a>         const struct <a href="ident?i=dst_entry">dst_entry</a> *<a href="ident?i=dst">dst</a> = <a href="ident?i=__sk_dst_get">__sk_dst_get</a>(sk);
<a name="L1426" href="source/net/ipv4/tcp_output.c#L1426">1426</a>         <a href="ident?i=u32">u32</a> mss_now;
<a name="L1427" href="source/net/ipv4/tcp_output.c#L1427">1427</a>         unsigned int <a href="ident?i=header_len">header_len</a>;
<a name="L1428" href="source/net/ipv4/tcp_output.c#L1428">1428</a>         struct <a href="ident?i=tcp_out_options">tcp_out_options</a> <a href="ident?i=opts">opts</a>;
<a name="L1429" href="source/net/ipv4/tcp_output.c#L1429">1429</a>         struct <a href="ident?i=tcp_md5sig_key">tcp_md5sig_key</a> *md5;
<a name="L1430" href="source/net/ipv4/tcp_output.c#L1430">1430</a> 
<a name="L1431" href="source/net/ipv4/tcp_output.c#L1431">1431</a>         mss_now = <a href="ident?i=tp">tp</a>-&gt;mss_cache;
<a name="L1432" href="source/net/ipv4/tcp_output.c#L1432">1432</a> 
<a name="L1433" href="source/net/ipv4/tcp_output.c#L1433">1433</a>         if (<a href="ident?i=dst">dst</a>) {
<a name="L1434" href="source/net/ipv4/tcp_output.c#L1434">1434</a>                 <a href="ident?i=u32">u32</a> <a href="ident?i=mtu">mtu</a> = <a href="ident?i=dst_mtu">dst_mtu</a>(<a href="ident?i=dst">dst</a>);
<a name="L1435" href="source/net/ipv4/tcp_output.c#L1435">1435</a>                 if (<a href="ident?i=mtu">mtu</a> != <a href="ident?i=inet_csk">inet_csk</a>(sk)-&gt;icsk_pmtu_cookie)
<a name="L1436" href="source/net/ipv4/tcp_output.c#L1436">1436</a>                         mss_now = <a href="ident?i=tcp_sync_mss">tcp_sync_mss</a>(sk, <a href="ident?i=mtu">mtu</a>);
<a name="L1437" href="source/net/ipv4/tcp_output.c#L1437">1437</a>         }
<a name="L1438" href="source/net/ipv4/tcp_output.c#L1438">1438</a> 
<a name="L1439" href="source/net/ipv4/tcp_output.c#L1439">1439</a>         <a href="ident?i=header_len">header_len</a> = <a href="ident?i=tcp_established_options">tcp_established_options</a>(sk, <a href="ident?i=NULL">NULL</a>, &amp;<a href="ident?i=opts">opts</a>, &amp;md5) +
<a name="L1440" href="source/net/ipv4/tcp_output.c#L1440">1440</a>                      sizeof(struct <a href="ident?i=tcphdr">tcphdr</a>);
<a name="L1441" href="source/net/ipv4/tcp_output.c#L1441">1441</a>         <b><i>/* The mss_cache is sized based on tp-&gt;tcp_header_len, which assumes</i></b>
<a name="L1442" href="source/net/ipv4/tcp_output.c#L1442">1442</a> <b><i>         * some common options. If this is an odd packet (because we have SACK</i></b>
<a name="L1443" href="source/net/ipv4/tcp_output.c#L1443">1443</a> <b><i>         * blocks etc) then our calculated header_len will be different, and</i></b>
<a name="L1444" href="source/net/ipv4/tcp_output.c#L1444">1444</a> <b><i>         * we have to adjust mss_now correspondingly */</i></b>
<a name="L1445" href="source/net/ipv4/tcp_output.c#L1445">1445</a>         if (<a href="ident?i=header_len">header_len</a> != <a href="ident?i=tp">tp</a>-&gt;tcp_header_len) {
<a name="L1446" href="source/net/ipv4/tcp_output.c#L1446">1446</a>                 int <a href="ident?i=delta">delta</a> = (int) <a href="ident?i=header_len">header_len</a> - <a href="ident?i=tp">tp</a>-&gt;tcp_header_len;
<a name="L1447" href="source/net/ipv4/tcp_output.c#L1447">1447</a>                 mss_now -= <a href="ident?i=delta">delta</a>;
<a name="L1448" href="source/net/ipv4/tcp_output.c#L1448">1448</a>         }
<a name="L1449" href="source/net/ipv4/tcp_output.c#L1449">1449</a> 
<a name="L1450" href="source/net/ipv4/tcp_output.c#L1450">1450</a>         return mss_now;
<a name="L1451" href="source/net/ipv4/tcp_output.c#L1451">1451</a> }
<a name="L1452" href="source/net/ipv4/tcp_output.c#L1452">1452</a> 
<a name="L1453" href="source/net/ipv4/tcp_output.c#L1453">1453</a> <b><i>/* RFC2861, slow part. Adjust cwnd, after it was not full during one rto.</i></b>
<a name="L1454" href="source/net/ipv4/tcp_output.c#L1454">1454</a> <b><i> * As additional protections, we do not touch cwnd in retransmission phases,</i></b>
<a name="L1455" href="source/net/ipv4/tcp_output.c#L1455">1455</a> <b><i> * and if application hit its sndbuf limit recently.</i></b>
<a name="L1456" href="source/net/ipv4/tcp_output.c#L1456">1456</a> <b><i> */</i></b>
<a name="L1457" href="source/net/ipv4/tcp_output.c#L1457">1457</a> static void <a href="ident?i=tcp_cwnd_application_limited">tcp_cwnd_application_limited</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L1458" href="source/net/ipv4/tcp_output.c#L1458">1458</a> {
<a name="L1459" href="source/net/ipv4/tcp_output.c#L1459">1459</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L1460" href="source/net/ipv4/tcp_output.c#L1460">1460</a> 
<a name="L1461" href="source/net/ipv4/tcp_output.c#L1461">1461</a>         if (<a href="ident?i=inet_csk">inet_csk</a>(sk)-&gt;icsk_ca_state == TCP_CA_Open &amp;&amp;
<a name="L1462" href="source/net/ipv4/tcp_output.c#L1462">1462</a>             sk-&gt;sk_socket &amp;&amp; !<a href="ident?i=test_bit">test_bit</a>(<a href="ident?i=SOCK_NOSPACE">SOCK_NOSPACE</a>, &amp;sk-&gt;sk_socket-&gt;<a href="ident?i=flags">flags</a>)) {
<a name="L1463" href="source/net/ipv4/tcp_output.c#L1463">1463</a>                 <b><i>/* Limited by application or receiver window. */</i></b>
<a name="L1464" href="source/net/ipv4/tcp_output.c#L1464">1464</a>                 <a href="ident?i=u32">u32</a> init_win = <a href="ident?i=tcp_init_cwnd">tcp_init_cwnd</a>(<a href="ident?i=tp">tp</a>, <a href="ident?i=__sk_dst_get">__sk_dst_get</a>(sk));
<a name="L1465" href="source/net/ipv4/tcp_output.c#L1465">1465</a>                 <a href="ident?i=u32">u32</a> win_used = <a href="ident?i=max">max</a>(<a href="ident?i=tp">tp</a>-&gt;snd_cwnd_used, init_win);
<a name="L1466" href="source/net/ipv4/tcp_output.c#L1466">1466</a>                 if (win_used &lt; <a href="ident?i=tp">tp</a>-&gt;snd_cwnd) {
<a name="L1467" href="source/net/ipv4/tcp_output.c#L1467">1467</a>                         <a href="ident?i=tp">tp</a>-&gt;snd_ssthresh = <a href="ident?i=tcp_current_ssthresh">tcp_current_ssthresh</a>(sk);
<a name="L1468" href="source/net/ipv4/tcp_output.c#L1468">1468</a>                         <a href="ident?i=tp">tp</a>-&gt;snd_cwnd = (<a href="ident?i=tp">tp</a>-&gt;snd_cwnd + win_used) &gt;&gt; 1;
<a name="L1469" href="source/net/ipv4/tcp_output.c#L1469">1469</a>                 }
<a name="L1470" href="source/net/ipv4/tcp_output.c#L1470">1470</a>                 <a href="ident?i=tp">tp</a>-&gt;snd_cwnd_used = 0;
<a name="L1471" href="source/net/ipv4/tcp_output.c#L1471">1471</a>         }
<a name="L1472" href="source/net/ipv4/tcp_output.c#L1472">1472</a>         <a href="ident?i=tp">tp</a>-&gt;snd_cwnd_stamp = <a href="ident?i=tcp_time_stamp">tcp_time_stamp</a>;
<a name="L1473" href="source/net/ipv4/tcp_output.c#L1473">1473</a> }
<a name="L1474" href="source/net/ipv4/tcp_output.c#L1474">1474</a> 
<a name="L1475" href="source/net/ipv4/tcp_output.c#L1475">1475</a> static void <a href="ident?i=tcp_cwnd_validate">tcp_cwnd_validate</a>(struct <a href="ident?i=sock">sock</a> *sk, <a href="ident?i=bool">bool</a> is_cwnd_limited)
<a name="L1476" href="source/net/ipv4/tcp_output.c#L1476">1476</a> {
<a name="L1477" href="source/net/ipv4/tcp_output.c#L1477">1477</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L1478" href="source/net/ipv4/tcp_output.c#L1478">1478</a> 
<a name="L1479" href="source/net/ipv4/tcp_output.c#L1479">1479</a>         <b><i>/* Track the maximum number of outstanding packets in each</i></b>
<a name="L1480" href="source/net/ipv4/tcp_output.c#L1480">1480</a> <b><i>         * window, and remember whether we were cwnd-limited then.</i></b>
<a name="L1481" href="source/net/ipv4/tcp_output.c#L1481">1481</a> <b><i>         */</i></b>
<a name="L1482" href="source/net/ipv4/tcp_output.c#L1482">1482</a>         if (!<a href="ident?i=before">before</a>(<a href="ident?i=tp">tp</a>-&gt;snd_una, <a href="ident?i=tp">tp</a>-&gt;max_packets_seq) ||
<a name="L1483" href="source/net/ipv4/tcp_output.c#L1483">1483</a>             <a href="ident?i=tp">tp</a>-&gt;packets_out &gt; <a href="ident?i=tp">tp</a>-&gt;max_packets_out) {
<a name="L1484" href="source/net/ipv4/tcp_output.c#L1484">1484</a>                 <a href="ident?i=tp">tp</a>-&gt;max_packets_out = <a href="ident?i=tp">tp</a>-&gt;packets_out;
<a name="L1485" href="source/net/ipv4/tcp_output.c#L1485">1485</a>                 <a href="ident?i=tp">tp</a>-&gt;max_packets_seq = <a href="ident?i=tp">tp</a>-&gt;snd_nxt;
<a name="L1486" href="source/net/ipv4/tcp_output.c#L1486">1486</a>                 <a href="ident?i=tp">tp</a>-&gt;is_cwnd_limited = is_cwnd_limited;
<a name="L1487" href="source/net/ipv4/tcp_output.c#L1487">1487</a>         }
<a name="L1488" href="source/net/ipv4/tcp_output.c#L1488">1488</a> 
<a name="L1489" href="source/net/ipv4/tcp_output.c#L1489">1489</a>         if (<a href="ident?i=tcp_is_cwnd_limited">tcp_is_cwnd_limited</a>(sk)) {
<a name="L1490" href="source/net/ipv4/tcp_output.c#L1490">1490</a>                 <b><i>/* Network is feed fully. */</i></b>
<a name="L1491" href="source/net/ipv4/tcp_output.c#L1491">1491</a>                 <a href="ident?i=tp">tp</a>-&gt;snd_cwnd_used = 0;
<a name="L1492" href="source/net/ipv4/tcp_output.c#L1492">1492</a>                 <a href="ident?i=tp">tp</a>-&gt;snd_cwnd_stamp = <a href="ident?i=tcp_time_stamp">tcp_time_stamp</a>;
<a name="L1493" href="source/net/ipv4/tcp_output.c#L1493">1493</a>         } else {
<a name="L1494" href="source/net/ipv4/tcp_output.c#L1494">1494</a>                 <b><i>/* Network starves. */</i></b>
<a name="L1495" href="source/net/ipv4/tcp_output.c#L1495">1495</a>                 if (<a href="ident?i=tp">tp</a>-&gt;packets_out &gt; <a href="ident?i=tp">tp</a>-&gt;snd_cwnd_used)
<a name="L1496" href="source/net/ipv4/tcp_output.c#L1496">1496</a>                         <a href="ident?i=tp">tp</a>-&gt;snd_cwnd_used = <a href="ident?i=tp">tp</a>-&gt;packets_out;
<a name="L1497" href="source/net/ipv4/tcp_output.c#L1497">1497</a> 
<a name="L1498" href="source/net/ipv4/tcp_output.c#L1498">1498</a>                 if (<a href="ident?i=sysctl_tcp_slow_start_after_idle">sysctl_tcp_slow_start_after_idle</a> &amp;&amp;
<a name="L1499" href="source/net/ipv4/tcp_output.c#L1499">1499</a>                     (<a href="ident?i=s32">s32</a>)(<a href="ident?i=tcp_time_stamp">tcp_time_stamp</a> - <a href="ident?i=tp">tp</a>-&gt;snd_cwnd_stamp) &gt;= <a href="ident?i=inet_csk">inet_csk</a>(sk)-&gt;icsk_rto)
<a name="L1500" href="source/net/ipv4/tcp_output.c#L1500">1500</a>                         <a href="ident?i=tcp_cwnd_application_limited">tcp_cwnd_application_limited</a>(sk);
<a name="L1501" href="source/net/ipv4/tcp_output.c#L1501">1501</a>         }
<a name="L1502" href="source/net/ipv4/tcp_output.c#L1502">1502</a> }
<a name="L1503" href="source/net/ipv4/tcp_output.c#L1503">1503</a> 
<a name="L1504" href="source/net/ipv4/tcp_output.c#L1504">1504</a> <b><i>/* Minshall's variant of the Nagle send check. */</i></b>
<a name="L1505" href="source/net/ipv4/tcp_output.c#L1505">1505</a> static <a href="ident?i=bool">bool</a> <a href="ident?i=tcp_minshall_check">tcp_minshall_check</a>(const struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a>)
<a name="L1506" href="source/net/ipv4/tcp_output.c#L1506">1506</a> {
<a name="L1507" href="source/net/ipv4/tcp_output.c#L1507">1507</a>         return <a href="ident?i=after">after</a>(<a href="ident?i=tp">tp</a>-&gt;snd_sml, <a href="ident?i=tp">tp</a>-&gt;snd_una) &amp;&amp;
<a name="L1508" href="source/net/ipv4/tcp_output.c#L1508">1508</a>                 !<a href="ident?i=after">after</a>(<a href="ident?i=tp">tp</a>-&gt;snd_sml, <a href="ident?i=tp">tp</a>-&gt;snd_nxt);
<a name="L1509" href="source/net/ipv4/tcp_output.c#L1509">1509</a> }
<a name="L1510" href="source/net/ipv4/tcp_output.c#L1510">1510</a> 
<a name="L1511" href="source/net/ipv4/tcp_output.c#L1511">1511</a> <b><i>/* Update snd_sml if this skb is under mss</i></b>
<a name="L1512" href="source/net/ipv4/tcp_output.c#L1512">1512</a> <b><i> * Note that a TSO packet might end with a sub-mss segment</i></b>
<a name="L1513" href="source/net/ipv4/tcp_output.c#L1513">1513</a> <b><i> * The test is really :</i></b>
<a name="L1514" href="source/net/ipv4/tcp_output.c#L1514">1514</a> <b><i> * if ((skb-&gt;len % mss) != 0)</i></b>
<a name="L1515" href="source/net/ipv4/tcp_output.c#L1515">1515</a> <b><i> *        tp-&gt;snd_sml = TCP_SKB_CB(skb)-&gt;end_seq;</i></b>
<a name="L1516" href="source/net/ipv4/tcp_output.c#L1516">1516</a> <b><i> * But we can avoid doing the divide again given we already have</i></b>
<a name="L1517" href="source/net/ipv4/tcp_output.c#L1517">1517</a> <b><i> *  skb_pcount = skb-&gt;len / mss_now</i></b>
<a name="L1518" href="source/net/ipv4/tcp_output.c#L1518">1518</a> <b><i> */</i></b>
<a name="L1519" href="source/net/ipv4/tcp_output.c#L1519">1519</a> static void <a href="ident?i=tcp_minshall_update">tcp_minshall_update</a>(struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a>, unsigned int mss_now,
<a name="L1520" href="source/net/ipv4/tcp_output.c#L1520">1520</a>                                 const struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L1521" href="source/net/ipv4/tcp_output.c#L1521">1521</a> {
<a name="L1522" href="source/net/ipv4/tcp_output.c#L1522">1522</a>         if (<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a> &lt; <a href="ident?i=tcp_skb_pcount">tcp_skb_pcount</a>(<a href="ident?i=skb">skb</a>) * mss_now)
<a name="L1523" href="source/net/ipv4/tcp_output.c#L1523">1523</a>                 <a href="ident?i=tp">tp</a>-&gt;snd_sml = <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;end_seq;
<a name="L1524" href="source/net/ipv4/tcp_output.c#L1524">1524</a> }
<a name="L1525" href="source/net/ipv4/tcp_output.c#L1525">1525</a> 
<a name="L1526" href="source/net/ipv4/tcp_output.c#L1526">1526</a> <b><i>/* Return false, if packet can be sent now without violation Nagle's rules:</i></b>
<a name="L1527" href="source/net/ipv4/tcp_output.c#L1527">1527</a> <b><i> * 1. It is full sized. (provided by caller in %partial bool)</i></b>
<a name="L1528" href="source/net/ipv4/tcp_output.c#L1528">1528</a> <b><i> * 2. Or it contains FIN. (already checked by caller)</i></b>
<a name="L1529" href="source/net/ipv4/tcp_output.c#L1529">1529</a> <b><i> * 3. Or TCP_CORK is not set, and TCP_NODELAY is set.</i></b>
<a name="L1530" href="source/net/ipv4/tcp_output.c#L1530">1530</a> <b><i> * 4. Or TCP_CORK is not set, and all sent packets are ACKed.</i></b>
<a name="L1531" href="source/net/ipv4/tcp_output.c#L1531">1531</a> <b><i> *    With Minshall's modification: all sent small packets are ACKed.</i></b>
<a name="L1532" href="source/net/ipv4/tcp_output.c#L1532">1532</a> <b><i> */</i></b>
<a name="L1533" href="source/net/ipv4/tcp_output.c#L1533">1533</a> static <a href="ident?i=bool">bool</a> <a href="ident?i=tcp_nagle_check">tcp_nagle_check</a>(<a href="ident?i=bool">bool</a> partial, const struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a>,
<a name="L1534" href="source/net/ipv4/tcp_output.c#L1534">1534</a>                             int nonagle)
<a name="L1535" href="source/net/ipv4/tcp_output.c#L1535">1535</a> {
<a name="L1536" href="source/net/ipv4/tcp_output.c#L1536">1536</a>         return partial &amp;&amp;
<a name="L1537" href="source/net/ipv4/tcp_output.c#L1537">1537</a>                 ((nonagle &amp; <a href="ident?i=TCP_NAGLE_CORK">TCP_NAGLE_CORK</a>) ||
<a name="L1538" href="source/net/ipv4/tcp_output.c#L1538">1538</a>                  (!nonagle &amp;&amp; <a href="ident?i=tp">tp</a>-&gt;packets_out &amp;&amp; <a href="ident?i=tcp_minshall_check">tcp_minshall_check</a>(<a href="ident?i=tp">tp</a>)));
<a name="L1539" href="source/net/ipv4/tcp_output.c#L1539">1539</a> }
<a name="L1540" href="source/net/ipv4/tcp_output.c#L1540">1540</a> 
<a name="L1541" href="source/net/ipv4/tcp_output.c#L1541">1541</a> <b><i>/* Return how many segs we'd like on a TSO packet,</i></b>
<a name="L1542" href="source/net/ipv4/tcp_output.c#L1542">1542</a> <b><i> * to send one TSO packet per ms</i></b>
<a name="L1543" href="source/net/ipv4/tcp_output.c#L1543">1543</a> <b><i> */</i></b>
<a name="L1544" href="source/net/ipv4/tcp_output.c#L1544">1544</a> static <a href="ident?i=u32">u32</a> <a href="ident?i=tcp_tso_autosize">tcp_tso_autosize</a>(const struct <a href="ident?i=sock">sock</a> *sk, unsigned int mss_now)
<a name="L1545" href="source/net/ipv4/tcp_output.c#L1545">1545</a> {
<a name="L1546" href="source/net/ipv4/tcp_output.c#L1546">1546</a>         <a href="ident?i=u32">u32</a> <a href="ident?i=bytes">bytes</a>, segs;
<a name="L1547" href="source/net/ipv4/tcp_output.c#L1547">1547</a> 
<a name="L1548" href="source/net/ipv4/tcp_output.c#L1548">1548</a>         <a href="ident?i=bytes">bytes</a> = <a href="ident?i=min">min</a>(sk-&gt;sk_pacing_rate &gt;&gt; 10,
<a name="L1549" href="source/net/ipv4/tcp_output.c#L1549">1549</a>                     sk-&gt;sk_gso_max_size - 1 - <a href="ident?i=MAX_TCP_HEADER">MAX_TCP_HEADER</a>);
<a name="L1550" href="source/net/ipv4/tcp_output.c#L1550">1550</a> 
<a name="L1551" href="source/net/ipv4/tcp_output.c#L1551">1551</a>         <b><i>/* Goal is to send at least one packet per ms,</i></b>
<a name="L1552" href="source/net/ipv4/tcp_output.c#L1552">1552</a> <b><i>         * not one big TSO packet every 100 ms.</i></b>
<a name="L1553" href="source/net/ipv4/tcp_output.c#L1553">1553</a> <b><i>         * This preserves ACK clocking and is consistent</i></b>
<a name="L1554" href="source/net/ipv4/tcp_output.c#L1554">1554</a> <b><i>         * with tcp_tso_should_defer() heuristic.</i></b>
<a name="L1555" href="source/net/ipv4/tcp_output.c#L1555">1555</a> <b><i>         */</i></b>
<a name="L1556" href="source/net/ipv4/tcp_output.c#L1556">1556</a>         segs = <a href="ident?i=max_t">max_t</a>(<a href="ident?i=u32">u32</a>, <a href="ident?i=bytes">bytes</a> / mss_now, <a href="ident?i=sysctl_tcp_min_tso_segs">sysctl_tcp_min_tso_segs</a>);
<a name="L1557" href="source/net/ipv4/tcp_output.c#L1557">1557</a> 
<a name="L1558" href="source/net/ipv4/tcp_output.c#L1558">1558</a>         return <a href="ident?i=min_t">min_t</a>(<a href="ident?i=u32">u32</a>, segs, sk-&gt;sk_gso_max_segs);
<a name="L1559" href="source/net/ipv4/tcp_output.c#L1559">1559</a> }
<a name="L1560" href="source/net/ipv4/tcp_output.c#L1560">1560</a> 
<a name="L1561" href="source/net/ipv4/tcp_output.c#L1561">1561</a> <b><i>/* Returns the portion of skb which can be sent right away */</i></b>
<a name="L1562" href="source/net/ipv4/tcp_output.c#L1562">1562</a> static unsigned int <a href="ident?i=tcp_mss_split_point">tcp_mss_split_point</a>(const struct <a href="ident?i=sock">sock</a> *sk,
<a name="L1563" href="source/net/ipv4/tcp_output.c#L1563">1563</a>                                         const struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
<a name="L1564" href="source/net/ipv4/tcp_output.c#L1564">1564</a>                                         unsigned int mss_now,
<a name="L1565" href="source/net/ipv4/tcp_output.c#L1565">1565</a>                                         unsigned int max_segs,
<a name="L1566" href="source/net/ipv4/tcp_output.c#L1566">1566</a>                                         int nonagle)
<a name="L1567" href="source/net/ipv4/tcp_output.c#L1567">1567</a> {
<a name="L1568" href="source/net/ipv4/tcp_output.c#L1568">1568</a>         const struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L1569" href="source/net/ipv4/tcp_output.c#L1569">1569</a>         <a href="ident?i=u32">u32</a> partial, needed, <a href="ident?i=window">window</a>, <a href="ident?i=max_len">max_len</a>;
<a name="L1570" href="source/net/ipv4/tcp_output.c#L1570">1570</a> 
<a name="L1571" href="source/net/ipv4/tcp_output.c#L1571">1571</a>         <a href="ident?i=window">window</a> = <a href="ident?i=tcp_wnd_end">tcp_wnd_end</a>(<a href="ident?i=tp">tp</a>) - <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=seq">seq</a>;
<a name="L1572" href="source/net/ipv4/tcp_output.c#L1572">1572</a>         <a href="ident?i=max_len">max_len</a> = mss_now * max_segs;
<a name="L1573" href="source/net/ipv4/tcp_output.c#L1573">1573</a> 
<a name="L1574" href="source/net/ipv4/tcp_output.c#L1574">1574</a>         if (<a href="ident?i=likely">likely</a>(<a href="ident?i=max_len">max_len</a> &lt;= <a href="ident?i=window">window</a> &amp;&amp; <a href="ident?i=skb">skb</a> != <a href="ident?i=tcp_write_queue_tail">tcp_write_queue_tail</a>(sk)))
<a name="L1575" href="source/net/ipv4/tcp_output.c#L1575">1575</a>                 return <a href="ident?i=max_len">max_len</a>;
<a name="L1576" href="source/net/ipv4/tcp_output.c#L1576">1576</a> 
<a name="L1577" href="source/net/ipv4/tcp_output.c#L1577">1577</a>         needed = <a href="ident?i=min">min</a>(<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a>, <a href="ident?i=window">window</a>);
<a name="L1578" href="source/net/ipv4/tcp_output.c#L1578">1578</a> 
<a name="L1579" href="source/net/ipv4/tcp_output.c#L1579">1579</a>         if (<a href="ident?i=max_len">max_len</a> &lt;= needed)
<a name="L1580" href="source/net/ipv4/tcp_output.c#L1580">1580</a>                 return <a href="ident?i=max_len">max_len</a>;
<a name="L1581" href="source/net/ipv4/tcp_output.c#L1581">1581</a> 
<a name="L1582" href="source/net/ipv4/tcp_output.c#L1582">1582</a>         partial = needed % mss_now;
<a name="L1583" href="source/net/ipv4/tcp_output.c#L1583">1583</a>         <b><i>/* If last segment is not a full MSS, check if Nagle rules allow us</i></b>
<a name="L1584" href="source/net/ipv4/tcp_output.c#L1584">1584</a> <b><i>         * to include this last segment in this skb.</i></b>
<a name="L1585" href="source/net/ipv4/tcp_output.c#L1585">1585</a> <b><i>         * Otherwise, we'll split the skb at last MSS boundary</i></b>
<a name="L1586" href="source/net/ipv4/tcp_output.c#L1586">1586</a> <b><i>         */</i></b>
<a name="L1587" href="source/net/ipv4/tcp_output.c#L1587">1587</a>         if (<a href="ident?i=tcp_nagle_check">tcp_nagle_check</a>(partial != 0, <a href="ident?i=tp">tp</a>, nonagle))
<a name="L1588" href="source/net/ipv4/tcp_output.c#L1588">1588</a>                 return needed - partial;
<a name="L1589" href="source/net/ipv4/tcp_output.c#L1589">1589</a> 
<a name="L1590" href="source/net/ipv4/tcp_output.c#L1590">1590</a>         return needed;
<a name="L1591" href="source/net/ipv4/tcp_output.c#L1591">1591</a> }
<a name="L1592" href="source/net/ipv4/tcp_output.c#L1592">1592</a> 
<a name="L1593" href="source/net/ipv4/tcp_output.c#L1593">1593</a> <b><i>/* Can at least one segment of SKB be sent right now, according to the</i></b>
<a name="L1594" href="source/net/ipv4/tcp_output.c#L1594">1594</a> <b><i> * congestion window rules?  If so, return how many segments are allowed.</i></b>
<a name="L1595" href="source/net/ipv4/tcp_output.c#L1595">1595</a> <b><i> */</i></b>
<a name="L1596" href="source/net/ipv4/tcp_output.c#L1596">1596</a> static inline unsigned int <a href="ident?i=tcp_cwnd_test">tcp_cwnd_test</a>(const struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a>,
<a name="L1597" href="source/net/ipv4/tcp_output.c#L1597">1597</a>                                          const struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L1598" href="source/net/ipv4/tcp_output.c#L1598">1598</a> {
<a name="L1599" href="source/net/ipv4/tcp_output.c#L1599">1599</a>         <a href="ident?i=u32">u32</a> <a href="ident?i=in_flight">in_flight</a>, cwnd, halfcwnd;
<a name="L1600" href="source/net/ipv4/tcp_output.c#L1600">1600</a> 
<a name="L1601" href="source/net/ipv4/tcp_output.c#L1601">1601</a>         <b><i>/* Don't be strict about the congestion window for the final FIN.  */</i></b>
<a name="L1602" href="source/net/ipv4/tcp_output.c#L1602">1602</a>         if ((<a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;tcp_flags &amp; <a href="ident?i=TCPHDR_FIN">TCPHDR_FIN</a>) &amp;&amp;
<a name="L1603" href="source/net/ipv4/tcp_output.c#L1603">1603</a>             <a href="ident?i=tcp_skb_pcount">tcp_skb_pcount</a>(<a href="ident?i=skb">skb</a>) == 1)
<a name="L1604" href="source/net/ipv4/tcp_output.c#L1604">1604</a>                 return 1;
<a name="L1605" href="source/net/ipv4/tcp_output.c#L1605">1605</a> 
<a name="L1606" href="source/net/ipv4/tcp_output.c#L1606">1606</a>         <a href="ident?i=in_flight">in_flight</a> = <a href="ident?i=tcp_packets_in_flight">tcp_packets_in_flight</a>(<a href="ident?i=tp">tp</a>);
<a name="L1607" href="source/net/ipv4/tcp_output.c#L1607">1607</a>         cwnd = <a href="ident?i=tp">tp</a>-&gt;snd_cwnd;
<a name="L1608" href="source/net/ipv4/tcp_output.c#L1608">1608</a>         if (<a href="ident?i=in_flight">in_flight</a> &gt;= cwnd)
<a name="L1609" href="source/net/ipv4/tcp_output.c#L1609">1609</a>                 return 0;
<a name="L1610" href="source/net/ipv4/tcp_output.c#L1610">1610</a> 
<a name="L1611" href="source/net/ipv4/tcp_output.c#L1611">1611</a>         <b><i>/* For better scheduling, ensure we have at least</i></b>
<a name="L1612" href="source/net/ipv4/tcp_output.c#L1612">1612</a> <b><i>         * 2 GSO packets in flight.</i></b>
<a name="L1613" href="source/net/ipv4/tcp_output.c#L1613">1613</a> <b><i>         */</i></b>
<a name="L1614" href="source/net/ipv4/tcp_output.c#L1614">1614</a>         halfcwnd = <a href="ident?i=max">max</a>(cwnd &gt;&gt; 1, 1U);
<a name="L1615" href="source/net/ipv4/tcp_output.c#L1615">1615</a>         return <a href="ident?i=min">min</a>(halfcwnd, cwnd - <a href="ident?i=in_flight">in_flight</a>);
<a name="L1616" href="source/net/ipv4/tcp_output.c#L1616">1616</a> }
<a name="L1617" href="source/net/ipv4/tcp_output.c#L1617">1617</a> 
<a name="L1618" href="source/net/ipv4/tcp_output.c#L1618">1618</a> <b><i>/* Initialize TSO state of a skb.</i></b>
<a name="L1619" href="source/net/ipv4/tcp_output.c#L1619">1619</a> <b><i> * This must be invoked the first time we consider transmitting</i></b>
<a name="L1620" href="source/net/ipv4/tcp_output.c#L1620">1620</a> <b><i> * SKB onto the wire.</i></b>
<a name="L1621" href="source/net/ipv4/tcp_output.c#L1621">1621</a> <b><i> */</i></b>
<a name="L1622" href="source/net/ipv4/tcp_output.c#L1622">1622</a> static int <a href="ident?i=tcp_init_tso_segs">tcp_init_tso_segs</a>(const struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
<a name="L1623" href="source/net/ipv4/tcp_output.c#L1623">1623</a>                              unsigned int mss_now)
<a name="L1624" href="source/net/ipv4/tcp_output.c#L1624">1624</a> {
<a name="L1625" href="source/net/ipv4/tcp_output.c#L1625">1625</a>         int tso_segs = <a href="ident?i=tcp_skb_pcount">tcp_skb_pcount</a>(<a href="ident?i=skb">skb</a>);
<a name="L1626" href="source/net/ipv4/tcp_output.c#L1626">1626</a> 
<a name="L1627" href="source/net/ipv4/tcp_output.c#L1627">1627</a>         if (!tso_segs || (tso_segs &gt; 1 &amp;&amp; <a href="ident?i=tcp_skb_mss">tcp_skb_mss</a>(<a href="ident?i=skb">skb</a>) != mss_now)) {
<a name="L1628" href="source/net/ipv4/tcp_output.c#L1628">1628</a>                 <a href="ident?i=tcp_set_skb_tso_segs">tcp_set_skb_tso_segs</a>(sk, <a href="ident?i=skb">skb</a>, mss_now);
<a name="L1629" href="source/net/ipv4/tcp_output.c#L1629">1629</a>                 tso_segs = <a href="ident?i=tcp_skb_pcount">tcp_skb_pcount</a>(<a href="ident?i=skb">skb</a>);
<a name="L1630" href="source/net/ipv4/tcp_output.c#L1630">1630</a>         }
<a name="L1631" href="source/net/ipv4/tcp_output.c#L1631">1631</a>         return tso_segs;
<a name="L1632" href="source/net/ipv4/tcp_output.c#L1632">1632</a> }
<a name="L1633" href="source/net/ipv4/tcp_output.c#L1633">1633</a> 
<a name="L1634" href="source/net/ipv4/tcp_output.c#L1634">1634</a> 
<a name="L1635" href="source/net/ipv4/tcp_output.c#L1635">1635</a> <b><i>/* Return true if the Nagle test allows this packet to be</i></b>
<a name="L1636" href="source/net/ipv4/tcp_output.c#L1636">1636</a> <b><i> * sent now.</i></b>
<a name="L1637" href="source/net/ipv4/tcp_output.c#L1637">1637</a> <b><i> */</i></b>
<a name="L1638" href="source/net/ipv4/tcp_output.c#L1638">1638</a> static inline <a href="ident?i=bool">bool</a> <a href="ident?i=tcp_nagle_test">tcp_nagle_test</a>(const struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a>, const struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
<a name="L1639" href="source/net/ipv4/tcp_output.c#L1639">1639</a>                                   unsigned int cur_mss, int nonagle)
<a name="L1640" href="source/net/ipv4/tcp_output.c#L1640">1640</a> {
<a name="L1641" href="source/net/ipv4/tcp_output.c#L1641">1641</a>         <b><i>/* Nagle rule does not apply to frames, which sit in the middle of the</i></b>
<a name="L1642" href="source/net/ipv4/tcp_output.c#L1642">1642</a> <b><i>         * write_queue (they have no chances to get new data).</i></b>
<a name="L1643" href="source/net/ipv4/tcp_output.c#L1643">1643</a> <b><i>         *</i></b>
<a name="L1644" href="source/net/ipv4/tcp_output.c#L1644">1644</a> <b><i>         * This is implemented in the callers, where they modify the 'nonagle'</i></b>
<a name="L1645" href="source/net/ipv4/tcp_output.c#L1645">1645</a> <b><i>         * argument based upon the location of SKB in the send queue.</i></b>
<a name="L1646" href="source/net/ipv4/tcp_output.c#L1646">1646</a> <b><i>         */</i></b>
<a name="L1647" href="source/net/ipv4/tcp_output.c#L1647">1647</a>         if (nonagle &amp; <a href="ident?i=TCP_NAGLE_PUSH">TCP_NAGLE_PUSH</a>)
<a name="L1648" href="source/net/ipv4/tcp_output.c#L1648">1648</a>                 return <a href="ident?i=true">true</a>;
<a name="L1649" href="source/net/ipv4/tcp_output.c#L1649">1649</a> 
<a name="L1650" href="source/net/ipv4/tcp_output.c#L1650">1650</a>         <b><i>/* Don't use the nagle rule for urgent data (or for the final FIN). */</i></b>
<a name="L1651" href="source/net/ipv4/tcp_output.c#L1651">1651</a>         if (<a href="ident?i=tcp_urg_mode">tcp_urg_mode</a>(<a href="ident?i=tp">tp</a>) || (<a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;tcp_flags &amp; <a href="ident?i=TCPHDR_FIN">TCPHDR_FIN</a>))
<a name="L1652" href="source/net/ipv4/tcp_output.c#L1652">1652</a>                 return <a href="ident?i=true">true</a>;
<a name="L1653" href="source/net/ipv4/tcp_output.c#L1653">1653</a> 
<a name="L1654" href="source/net/ipv4/tcp_output.c#L1654">1654</a>         if (!<a href="ident?i=tcp_nagle_check">tcp_nagle_check</a>(<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a> &lt; cur_mss, <a href="ident?i=tp">tp</a>, nonagle))
<a name="L1655" href="source/net/ipv4/tcp_output.c#L1655">1655</a>                 return <a href="ident?i=true">true</a>;
<a name="L1656" href="source/net/ipv4/tcp_output.c#L1656">1656</a> 
<a name="L1657" href="source/net/ipv4/tcp_output.c#L1657">1657</a>         return <a href="ident?i=false">false</a>;
<a name="L1658" href="source/net/ipv4/tcp_output.c#L1658">1658</a> }
<a name="L1659" href="source/net/ipv4/tcp_output.c#L1659">1659</a> 
<a name="L1660" href="source/net/ipv4/tcp_output.c#L1660">1660</a> <b><i>/* Does at least the first segment of SKB fit into the send window? */</i></b>
<a name="L1661" href="source/net/ipv4/tcp_output.c#L1661">1661</a> static <a href="ident?i=bool">bool</a> <a href="ident?i=tcp_snd_wnd_test">tcp_snd_wnd_test</a>(const struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a>,
<a name="L1662" href="source/net/ipv4/tcp_output.c#L1662">1662</a>                              const struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
<a name="L1663" href="source/net/ipv4/tcp_output.c#L1663">1663</a>                              unsigned int cur_mss)
<a name="L1664" href="source/net/ipv4/tcp_output.c#L1664">1664</a> {
<a name="L1665" href="source/net/ipv4/tcp_output.c#L1665">1665</a>         <a href="ident?i=u32">u32</a> end_seq = <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;end_seq;
<a name="L1666" href="source/net/ipv4/tcp_output.c#L1666">1666</a> 
<a name="L1667" href="source/net/ipv4/tcp_output.c#L1667">1667</a>         if (<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a> &gt; cur_mss)
<a name="L1668" href="source/net/ipv4/tcp_output.c#L1668">1668</a>                 end_seq = <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=seq">seq</a> + cur_mss;
<a name="L1669" href="source/net/ipv4/tcp_output.c#L1669">1669</a> 
<a name="L1670" href="source/net/ipv4/tcp_output.c#L1670">1670</a>         return !<a href="ident?i=after">after</a>(end_seq, <a href="ident?i=tcp_wnd_end">tcp_wnd_end</a>(<a href="ident?i=tp">tp</a>));
<a name="L1671" href="source/net/ipv4/tcp_output.c#L1671">1671</a> }
<a name="L1672" href="source/net/ipv4/tcp_output.c#L1672">1672</a> 
<a name="L1673" href="source/net/ipv4/tcp_output.c#L1673">1673</a> <b><i>/* This checks if the data bearing packet SKB (usually tcp_send_head(sk))</i></b>
<a name="L1674" href="source/net/ipv4/tcp_output.c#L1674">1674</a> <b><i> * should be put on the wire right now.  If so, it returns the number of</i></b>
<a name="L1675" href="source/net/ipv4/tcp_output.c#L1675">1675</a> <b><i> * packets allowed by the congestion window.</i></b>
<a name="L1676" href="source/net/ipv4/tcp_output.c#L1676">1676</a> <b><i> */</i></b>
<a name="L1677" href="source/net/ipv4/tcp_output.c#L1677">1677</a> static unsigned int <a href="ident?i=tcp_snd_test">tcp_snd_test</a>(const struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
<a name="L1678" href="source/net/ipv4/tcp_output.c#L1678">1678</a>                                  unsigned int cur_mss, int nonagle)
<a name="L1679" href="source/net/ipv4/tcp_output.c#L1679">1679</a> {
<a name="L1680" href="source/net/ipv4/tcp_output.c#L1680">1680</a>         const struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L1681" href="source/net/ipv4/tcp_output.c#L1681">1681</a>         unsigned int cwnd_quota;
<a name="L1682" href="source/net/ipv4/tcp_output.c#L1682">1682</a> 
<a name="L1683" href="source/net/ipv4/tcp_output.c#L1683">1683</a>         <a href="ident?i=tcp_init_tso_segs">tcp_init_tso_segs</a>(sk, <a href="ident?i=skb">skb</a>, cur_mss);
<a name="L1684" href="source/net/ipv4/tcp_output.c#L1684">1684</a> 
<a name="L1685" href="source/net/ipv4/tcp_output.c#L1685">1685</a>         if (!<a href="ident?i=tcp_nagle_test">tcp_nagle_test</a>(<a href="ident?i=tp">tp</a>, <a href="ident?i=skb">skb</a>, cur_mss, nonagle))
<a name="L1686" href="source/net/ipv4/tcp_output.c#L1686">1686</a>                 return 0;
<a name="L1687" href="source/net/ipv4/tcp_output.c#L1687">1687</a> 
<a name="L1688" href="source/net/ipv4/tcp_output.c#L1688">1688</a>         cwnd_quota = <a href="ident?i=tcp_cwnd_test">tcp_cwnd_test</a>(<a href="ident?i=tp">tp</a>, <a href="ident?i=skb">skb</a>);
<a name="L1689" href="source/net/ipv4/tcp_output.c#L1689">1689</a>         if (cwnd_quota &amp;&amp; !<a href="ident?i=tcp_snd_wnd_test">tcp_snd_wnd_test</a>(<a href="ident?i=tp">tp</a>, <a href="ident?i=skb">skb</a>, cur_mss))
<a name="L1690" href="source/net/ipv4/tcp_output.c#L1690">1690</a>                 cwnd_quota = 0;
<a name="L1691" href="source/net/ipv4/tcp_output.c#L1691">1691</a> 
<a name="L1692" href="source/net/ipv4/tcp_output.c#L1692">1692</a>         return cwnd_quota;
<a name="L1693" href="source/net/ipv4/tcp_output.c#L1693">1693</a> }
<a name="L1694" href="source/net/ipv4/tcp_output.c#L1694">1694</a> 
<a name="L1695" href="source/net/ipv4/tcp_output.c#L1695">1695</a> <b><i>/* Test if sending is allowed right now. */</i></b>
<a name="L1696" href="source/net/ipv4/tcp_output.c#L1696">1696</a> <a href="ident?i=bool">bool</a> <a href="ident?i=tcp_may_send_now">tcp_may_send_now</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L1697" href="source/net/ipv4/tcp_output.c#L1697">1697</a> {
<a name="L1698" href="source/net/ipv4/tcp_output.c#L1698">1698</a>         const struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L1699" href="source/net/ipv4/tcp_output.c#L1699">1699</a>         struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a> = <a href="ident?i=tcp_send_head">tcp_send_head</a>(sk);
<a name="L1700" href="source/net/ipv4/tcp_output.c#L1700">1700</a> 
<a name="L1701" href="source/net/ipv4/tcp_output.c#L1701">1701</a>         return <a href="ident?i=skb">skb</a> &amp;&amp;
<a name="L1702" href="source/net/ipv4/tcp_output.c#L1702">1702</a>                 <a href="ident?i=tcp_snd_test">tcp_snd_test</a>(sk, <a href="ident?i=skb">skb</a>, <a href="ident?i=tcp_current_mss">tcp_current_mss</a>(sk),
<a name="L1703" href="source/net/ipv4/tcp_output.c#L1703">1703</a>                              (<a href="ident?i=tcp_skb_is_last">tcp_skb_is_last</a>(sk, <a href="ident?i=skb">skb</a>) ?
<a name="L1704" href="source/net/ipv4/tcp_output.c#L1704">1704</a>                               <a href="ident?i=tp">tp</a>-&gt;nonagle : <a href="ident?i=TCP_NAGLE_PUSH">TCP_NAGLE_PUSH</a>));
<a name="L1705" href="source/net/ipv4/tcp_output.c#L1705">1705</a> }
<a name="L1706" href="source/net/ipv4/tcp_output.c#L1706">1706</a> 
<a name="L1707" href="source/net/ipv4/tcp_output.c#L1707">1707</a> <b><i>/* Trim TSO SKB to LEN bytes, put the remaining data into a new packet</i></b>
<a name="L1708" href="source/net/ipv4/tcp_output.c#L1708">1708</a> <b><i> * which is put after SKB on the list.  It is very much like</i></b>
<a name="L1709" href="source/net/ipv4/tcp_output.c#L1709">1709</a> <b><i> * tcp_fragment() except that it may make several kinds of assumptions</i></b>
<a name="L1710" href="source/net/ipv4/tcp_output.c#L1710">1710</a> <b><i> * in order to speed up the splitting operation.  In particular, we</i></b>
<a name="L1711" href="source/net/ipv4/tcp_output.c#L1711">1711</a> <b><i> * know that all the data is in scatter-gather pages, and that the</i></b>
<a name="L1712" href="source/net/ipv4/tcp_output.c#L1712">1712</a> <b><i> * packet has never been sent out before (and thus is not cloned).</i></b>
<a name="L1713" href="source/net/ipv4/tcp_output.c#L1713">1713</a> <b><i> */</i></b>
<a name="L1714" href="source/net/ipv4/tcp_output.c#L1714">1714</a> static int <a href="ident?i=tso_fragment">tso_fragment</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, unsigned int <a href="ident?i=len">len</a>,
<a name="L1715" href="source/net/ipv4/tcp_output.c#L1715">1715</a>                         unsigned int mss_now, <a href="ident?i=gfp_t">gfp_t</a> gfp)
<a name="L1716" href="source/net/ipv4/tcp_output.c#L1716">1716</a> {
<a name="L1717" href="source/net/ipv4/tcp_output.c#L1717">1717</a>         struct <a href="ident?i=sk_buff">sk_buff</a> *buff;
<a name="L1718" href="source/net/ipv4/tcp_output.c#L1718">1718</a>         int nlen = <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a> - <a href="ident?i=len">len</a>;
<a name="L1719" href="source/net/ipv4/tcp_output.c#L1719">1719</a>         <a href="ident?i=u8">u8</a> <a href="ident?i=flags">flags</a>;
<a name="L1720" href="source/net/ipv4/tcp_output.c#L1720">1720</a> 
<a name="L1721" href="source/net/ipv4/tcp_output.c#L1721">1721</a>         <b><i>/* All of a TSO frame must be composed of paged data.  */</i></b>
<a name="L1722" href="source/net/ipv4/tcp_output.c#L1722">1722</a>         if (<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a> != <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=data_len">data_len</a>)
<a name="L1723" href="source/net/ipv4/tcp_output.c#L1723">1723</a>                 return <a href="ident?i=tcp_fragment">tcp_fragment</a>(sk, <a href="ident?i=skb">skb</a>, <a href="ident?i=len">len</a>, mss_now, gfp);
<a name="L1724" href="source/net/ipv4/tcp_output.c#L1724">1724</a> 
<a name="L1725" href="source/net/ipv4/tcp_output.c#L1725">1725</a>         buff = <a href="ident?i=sk_stream_alloc_skb">sk_stream_alloc_skb</a>(sk, 0, gfp);
<a name="L1726" href="source/net/ipv4/tcp_output.c#L1726">1726</a>         if (<a href="ident?i=unlikely">unlikely</a>(!buff))
<a name="L1727" href="source/net/ipv4/tcp_output.c#L1727">1727</a>                 return -<a href="ident?i=ENOMEM">ENOMEM</a>;
<a name="L1728" href="source/net/ipv4/tcp_output.c#L1728">1728</a> 
<a name="L1729" href="source/net/ipv4/tcp_output.c#L1729">1729</a>         sk-&gt;sk_wmem_queued += buff-&gt;truesize;
<a name="L1730" href="source/net/ipv4/tcp_output.c#L1730">1730</a>         <a href="ident?i=sk_mem_charge">sk_mem_charge</a>(sk, buff-&gt;truesize);
<a name="L1731" href="source/net/ipv4/tcp_output.c#L1731">1731</a>         buff-&gt;truesize += nlen;
<a name="L1732" href="source/net/ipv4/tcp_output.c#L1732">1732</a>         <a href="ident?i=skb">skb</a>-&gt;truesize -= nlen;
<a name="L1733" href="source/net/ipv4/tcp_output.c#L1733">1733</a> 
<a name="L1734" href="source/net/ipv4/tcp_output.c#L1734">1734</a>         <b><i>/* Correct the sequence numbers. */</i></b>
<a name="L1735" href="source/net/ipv4/tcp_output.c#L1735">1735</a>         <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(buff)-&gt;<a href="ident?i=seq">seq</a> = <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=seq">seq</a> + <a href="ident?i=len">len</a>;
<a name="L1736" href="source/net/ipv4/tcp_output.c#L1736">1736</a>         <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(buff)-&gt;end_seq = <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;end_seq;
<a name="L1737" href="source/net/ipv4/tcp_output.c#L1737">1737</a>         <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;end_seq = <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(buff)-&gt;<a href="ident?i=seq">seq</a>;
<a name="L1738" href="source/net/ipv4/tcp_output.c#L1738">1738</a> 
<a name="L1739" href="source/net/ipv4/tcp_output.c#L1739">1739</a>         <b><i>/* PSH and FIN should only be set in the second packet. */</i></b>
<a name="L1740" href="source/net/ipv4/tcp_output.c#L1740">1740</a>         <a href="ident?i=flags">flags</a> = <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;tcp_flags;
<a name="L1741" href="source/net/ipv4/tcp_output.c#L1741">1741</a>         <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;tcp_flags = <a href="ident?i=flags">flags</a> &amp; ~(<a href="ident?i=TCPHDR_FIN">TCPHDR_FIN</a> | <a href="ident?i=TCPHDR_PSH">TCPHDR_PSH</a>);
<a name="L1742" href="source/net/ipv4/tcp_output.c#L1742">1742</a>         <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(buff)-&gt;tcp_flags = <a href="ident?i=flags">flags</a>;
<a name="L1743" href="source/net/ipv4/tcp_output.c#L1743">1743</a> 
<a name="L1744" href="source/net/ipv4/tcp_output.c#L1744">1744</a>         <b><i>/* This packet was never sent out yet, so no SACK bits. */</i></b>
<a name="L1745" href="source/net/ipv4/tcp_output.c#L1745">1745</a>         <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(buff)-&gt;sacked = 0;
<a name="L1746" href="source/net/ipv4/tcp_output.c#L1746">1746</a> 
<a name="L1747" href="source/net/ipv4/tcp_output.c#L1747">1747</a>         buff-&gt;ip_summed = <a href="ident?i=skb">skb</a>-&gt;ip_summed = <a href="ident?i=CHECKSUM_PARTIAL">CHECKSUM_PARTIAL</a>;
<a name="L1748" href="source/net/ipv4/tcp_output.c#L1748">1748</a>         <a href="ident?i=skb_split">skb_split</a>(<a href="ident?i=skb">skb</a>, buff, <a href="ident?i=len">len</a>);
<a name="L1749" href="source/net/ipv4/tcp_output.c#L1749">1749</a>         <a href="ident?i=tcp_fragment_tstamp">tcp_fragment_tstamp</a>(<a href="ident?i=skb">skb</a>, buff);
<a name="L1750" href="source/net/ipv4/tcp_output.c#L1750">1750</a> 
<a name="L1751" href="source/net/ipv4/tcp_output.c#L1751">1751</a>         <b><i>/* Fix up tso_factor for both original and new SKB.  */</i></b>
<a name="L1752" href="source/net/ipv4/tcp_output.c#L1752">1752</a>         <a href="ident?i=tcp_set_skb_tso_segs">tcp_set_skb_tso_segs</a>(sk, <a href="ident?i=skb">skb</a>, mss_now);
<a name="L1753" href="source/net/ipv4/tcp_output.c#L1753">1753</a>         <a href="ident?i=tcp_set_skb_tso_segs">tcp_set_skb_tso_segs</a>(sk, buff, mss_now);
<a name="L1754" href="source/net/ipv4/tcp_output.c#L1754">1754</a> 
<a name="L1755" href="source/net/ipv4/tcp_output.c#L1755">1755</a>         <b><i>/* Link BUFF into the send queue. */</i></b>
<a name="L1756" href="source/net/ipv4/tcp_output.c#L1756">1756</a>         <a href="ident?i=__skb_header_release">__skb_header_release</a>(buff);
<a name="L1757" href="source/net/ipv4/tcp_output.c#L1757">1757</a>         <a href="ident?i=tcp_insert_write_queue_after">tcp_insert_write_queue_after</a>(<a href="ident?i=skb">skb</a>, buff, sk);
<a name="L1758" href="source/net/ipv4/tcp_output.c#L1758">1758</a> 
<a name="L1759" href="source/net/ipv4/tcp_output.c#L1759">1759</a>         return 0;
<a name="L1760" href="source/net/ipv4/tcp_output.c#L1760">1760</a> }
<a name="L1761" href="source/net/ipv4/tcp_output.c#L1761">1761</a> 
<a name="L1762" href="source/net/ipv4/tcp_output.c#L1762">1762</a> <b><i>/* Try to defer sending, if possible, in order to minimize the amount</i></b>
<a name="L1763" href="source/net/ipv4/tcp_output.c#L1763">1763</a> <b><i> * of TSO splitting we do.  View it as a kind of TSO Nagle test.</i></b>
<a name="L1764" href="source/net/ipv4/tcp_output.c#L1764">1764</a> <b><i> *</i></b>
<a name="L1765" href="source/net/ipv4/tcp_output.c#L1765">1765</a> <b><i> * This algorithm is from John Heffner.</i></b>
<a name="L1766" href="source/net/ipv4/tcp_output.c#L1766">1766</a> <b><i> */</i></b>
<a name="L1767" href="source/net/ipv4/tcp_output.c#L1767">1767</a> static <a href="ident?i=bool">bool</a> <a href="ident?i=tcp_tso_should_defer">tcp_tso_should_defer</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
<a name="L1768" href="source/net/ipv4/tcp_output.c#L1768">1768</a>                                  <a href="ident?i=bool">bool</a> *is_cwnd_limited, <a href="ident?i=u32">u32</a> max_segs)
<a name="L1769" href="source/net/ipv4/tcp_output.c#L1769">1769</a> {
<a name="L1770" href="source/net/ipv4/tcp_output.c#L1770">1770</a>         const struct <a href="ident?i=inet_connection_sock">inet_connection_sock</a> *icsk = <a href="ident?i=inet_csk">inet_csk</a>(sk);
<a name="L1771" href="source/net/ipv4/tcp_output.c#L1771">1771</a>         <a href="ident?i=u32">u32</a> age, send_win, cong_win, <a href="ident?i=limit">limit</a>, <a href="ident?i=in_flight">in_flight</a>;
<a name="L1772" href="source/net/ipv4/tcp_output.c#L1772">1772</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L1773" href="source/net/ipv4/tcp_output.c#L1773">1773</a>         struct <a href="ident?i=skb_mstamp">skb_mstamp</a> <a href="ident?i=now">now</a>;
<a name="L1774" href="source/net/ipv4/tcp_output.c#L1774">1774</a>         struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=head">head</a>;
<a name="L1775" href="source/net/ipv4/tcp_output.c#L1775">1775</a>         int win_divisor;
<a name="L1776" href="source/net/ipv4/tcp_output.c#L1776">1776</a> 
<a name="L1777" href="source/net/ipv4/tcp_output.c#L1777">1777</a>         if (<a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;tcp_flags &amp; <a href="ident?i=TCPHDR_FIN">TCPHDR_FIN</a>)
<a name="L1778" href="source/net/ipv4/tcp_output.c#L1778">1778</a>                 goto send_now;
<a name="L1779" href="source/net/ipv4/tcp_output.c#L1779">1779</a> 
<a name="L1780" href="source/net/ipv4/tcp_output.c#L1780">1780</a>         if (!((1 &lt;&lt; icsk-&gt;icsk_ca_state) &amp; (<a href="ident?i=TCPF_CA_Open">TCPF_CA_Open</a> | <a href="ident?i=TCPF_CA_CWR">TCPF_CA_CWR</a>)))
<a name="L1781" href="source/net/ipv4/tcp_output.c#L1781">1781</a>                 goto send_now;
<a name="L1782" href="source/net/ipv4/tcp_output.c#L1782">1782</a> 
<a name="L1783" href="source/net/ipv4/tcp_output.c#L1783">1783</a>         <b><i>/* Avoid bursty behavior by allowing defer</i></b>
<a name="L1784" href="source/net/ipv4/tcp_output.c#L1784">1784</a> <b><i>         * only if the last write was recent.</i></b>
<a name="L1785" href="source/net/ipv4/tcp_output.c#L1785">1785</a> <b><i>         */</i></b>
<a name="L1786" href="source/net/ipv4/tcp_output.c#L1786">1786</a>         if ((<a href="ident?i=s32">s32</a>)(<a href="ident?i=tcp_time_stamp">tcp_time_stamp</a> - <a href="ident?i=tp">tp</a>-&gt;lsndtime) &gt; 0)
<a name="L1787" href="source/net/ipv4/tcp_output.c#L1787">1787</a>                 goto send_now;
<a name="L1788" href="source/net/ipv4/tcp_output.c#L1788">1788</a> 
<a name="L1789" href="source/net/ipv4/tcp_output.c#L1789">1789</a>         <a href="ident?i=in_flight">in_flight</a> = <a href="ident?i=tcp_packets_in_flight">tcp_packets_in_flight</a>(<a href="ident?i=tp">tp</a>);
<a name="L1790" href="source/net/ipv4/tcp_output.c#L1790">1790</a> 
<a name="L1791" href="source/net/ipv4/tcp_output.c#L1791">1791</a>         <a href="ident?i=BUG_ON">BUG_ON</a>(<a href="ident?i=tcp_skb_pcount">tcp_skb_pcount</a>(<a href="ident?i=skb">skb</a>) &lt;= 1 || (<a href="ident?i=tp">tp</a>-&gt;snd_cwnd &lt;= <a href="ident?i=in_flight">in_flight</a>));
<a name="L1792" href="source/net/ipv4/tcp_output.c#L1792">1792</a> 
<a name="L1793" href="source/net/ipv4/tcp_output.c#L1793">1793</a>         send_win = <a href="ident?i=tcp_wnd_end">tcp_wnd_end</a>(<a href="ident?i=tp">tp</a>) - <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=seq">seq</a>;
<a name="L1794" href="source/net/ipv4/tcp_output.c#L1794">1794</a> 
<a name="L1795" href="source/net/ipv4/tcp_output.c#L1795">1795</a>         <b><i>/* From in_flight test above, we know that cwnd &gt; in_flight.  */</i></b>
<a name="L1796" href="source/net/ipv4/tcp_output.c#L1796">1796</a>         cong_win = (<a href="ident?i=tp">tp</a>-&gt;snd_cwnd - <a href="ident?i=in_flight">in_flight</a>) * <a href="ident?i=tp">tp</a>-&gt;mss_cache;
<a name="L1797" href="source/net/ipv4/tcp_output.c#L1797">1797</a> 
<a name="L1798" href="source/net/ipv4/tcp_output.c#L1798">1798</a>         <a href="ident?i=limit">limit</a> = <a href="ident?i=min">min</a>(send_win, cong_win);
<a name="L1799" href="source/net/ipv4/tcp_output.c#L1799">1799</a> 
<a name="L1800" href="source/net/ipv4/tcp_output.c#L1800">1800</a>         <b><i>/* If a full-sized TSO skb can be sent, do it. */</i></b>
<a name="L1801" href="source/net/ipv4/tcp_output.c#L1801">1801</a>         if (<a href="ident?i=limit">limit</a> &gt;= max_segs * <a href="ident?i=tp">tp</a>-&gt;mss_cache)
<a name="L1802" href="source/net/ipv4/tcp_output.c#L1802">1802</a>                 goto send_now;
<a name="L1803" href="source/net/ipv4/tcp_output.c#L1803">1803</a> 
<a name="L1804" href="source/net/ipv4/tcp_output.c#L1804">1804</a>         <b><i>/* Middle in queue won't get any more data, full sendable already? */</i></b>
<a name="L1805" href="source/net/ipv4/tcp_output.c#L1805">1805</a>         if ((<a href="ident?i=skb">skb</a> != <a href="ident?i=tcp_write_queue_tail">tcp_write_queue_tail</a>(sk)) &amp;&amp; (<a href="ident?i=limit">limit</a> &gt;= <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a>))
<a name="L1806" href="source/net/ipv4/tcp_output.c#L1806">1806</a>                 goto send_now;
<a name="L1807" href="source/net/ipv4/tcp_output.c#L1807">1807</a> 
<a name="L1808" href="source/net/ipv4/tcp_output.c#L1808">1808</a>         win_divisor = <a href="ident?i=ACCESS_ONCE">ACCESS_ONCE</a>(<a href="ident?i=sysctl_tcp_tso_win_divisor">sysctl_tcp_tso_win_divisor</a>);
<a name="L1809" href="source/net/ipv4/tcp_output.c#L1809">1809</a>         if (win_divisor) {
<a name="L1810" href="source/net/ipv4/tcp_output.c#L1810">1810</a>                 <a href="ident?i=u32">u32</a> <a href="ident?i=chunk">chunk</a> = <a href="ident?i=min">min</a>(<a href="ident?i=tp">tp</a>-&gt;snd_wnd, <a href="ident?i=tp">tp</a>-&gt;snd_cwnd * <a href="ident?i=tp">tp</a>-&gt;mss_cache);
<a name="L1811" href="source/net/ipv4/tcp_output.c#L1811">1811</a> 
<a name="L1812" href="source/net/ipv4/tcp_output.c#L1812">1812</a>                 <b><i>/* If at least some fraction of a window is available,</i></b>
<a name="L1813" href="source/net/ipv4/tcp_output.c#L1813">1813</a> <b><i>                 * just use it.</i></b>
<a name="L1814" href="source/net/ipv4/tcp_output.c#L1814">1814</a> <b><i>                 */</i></b>
<a name="L1815" href="source/net/ipv4/tcp_output.c#L1815">1815</a>                 <a href="ident?i=chunk">chunk</a> /= win_divisor;
<a name="L1816" href="source/net/ipv4/tcp_output.c#L1816">1816</a>                 if (<a href="ident?i=limit">limit</a> &gt;= <a href="ident?i=chunk">chunk</a>)
<a name="L1817" href="source/net/ipv4/tcp_output.c#L1817">1817</a>                         goto send_now;
<a name="L1818" href="source/net/ipv4/tcp_output.c#L1818">1818</a>         } else {
<a name="L1819" href="source/net/ipv4/tcp_output.c#L1819">1819</a>                 <b><i>/* Different approach, try not to defer past a single</i></b>
<a name="L1820" href="source/net/ipv4/tcp_output.c#L1820">1820</a> <b><i>                 * ACK.  Receiver should ACK every other full sized</i></b>
<a name="L1821" href="source/net/ipv4/tcp_output.c#L1821">1821</a> <b><i>                 * frame, so if we have space for more than 3 frames</i></b>
<a name="L1822" href="source/net/ipv4/tcp_output.c#L1822">1822</a> <b><i>                 * then send now.</i></b>
<a name="L1823" href="source/net/ipv4/tcp_output.c#L1823">1823</a> <b><i>                 */</i></b>
<a name="L1824" href="source/net/ipv4/tcp_output.c#L1824">1824</a>                 if (<a href="ident?i=limit">limit</a> &gt; <a href="ident?i=tcp_max_tso_deferred_mss">tcp_max_tso_deferred_mss</a>(<a href="ident?i=tp">tp</a>) * <a href="ident?i=tp">tp</a>-&gt;mss_cache)
<a name="L1825" href="source/net/ipv4/tcp_output.c#L1825">1825</a>                         goto send_now;
<a name="L1826" href="source/net/ipv4/tcp_output.c#L1826">1826</a>         }
<a name="L1827" href="source/net/ipv4/tcp_output.c#L1827">1827</a> 
<a name="L1828" href="source/net/ipv4/tcp_output.c#L1828">1828</a>         <a href="ident?i=head">head</a> = <a href="ident?i=tcp_write_queue_head">tcp_write_queue_head</a>(sk);
<a name="L1829" href="source/net/ipv4/tcp_output.c#L1829">1829</a>         <a href="ident?i=skb_mstamp_get">skb_mstamp_get</a>(&amp;<a href="ident?i=now">now</a>);
<a name="L1830" href="source/net/ipv4/tcp_output.c#L1830">1830</a>         age = <a href="ident?i=skb_mstamp_us_delta">skb_mstamp_us_delta</a>(&amp;<a href="ident?i=now">now</a>, &amp;<a href="ident?i=head">head</a>-&gt;<a href="ident?i=skb_mstamp">skb_mstamp</a>);
<a name="L1831" href="source/net/ipv4/tcp_output.c#L1831">1831</a>         <b><i>/* If next ACK is likely to come too late (half srtt), do not defer */</i></b>
<a name="L1832" href="source/net/ipv4/tcp_output.c#L1832">1832</a>         if (age &lt; (<a href="ident?i=tp">tp</a>-&gt;srtt_us &gt;&gt; 4))
<a name="L1833" href="source/net/ipv4/tcp_output.c#L1833">1833</a>                 goto send_now;
<a name="L1834" href="source/net/ipv4/tcp_output.c#L1834">1834</a> 
<a name="L1835" href="source/net/ipv4/tcp_output.c#L1835">1835</a>         <b><i>/* Ok, it looks like it is advisable to defer. */</i></b>
<a name="L1836" href="source/net/ipv4/tcp_output.c#L1836">1836</a> 
<a name="L1837" href="source/net/ipv4/tcp_output.c#L1837">1837</a>         if (cong_win &lt; send_win &amp;&amp; cong_win &lt; <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a>)
<a name="L1838" href="source/net/ipv4/tcp_output.c#L1838">1838</a>                 *is_cwnd_limited = <a href="ident?i=true">true</a>;
<a name="L1839" href="source/net/ipv4/tcp_output.c#L1839">1839</a> 
<a name="L1840" href="source/net/ipv4/tcp_output.c#L1840">1840</a>         return <a href="ident?i=true">true</a>;
<a name="L1841" href="source/net/ipv4/tcp_output.c#L1841">1841</a> 
<a name="L1842" href="source/net/ipv4/tcp_output.c#L1842">1842</a> send_now:
<a name="L1843" href="source/net/ipv4/tcp_output.c#L1843">1843</a>         return <a href="ident?i=false">false</a>;
<a name="L1844" href="source/net/ipv4/tcp_output.c#L1844">1844</a> }
<a name="L1845" href="source/net/ipv4/tcp_output.c#L1845">1845</a> 
<a name="L1846" href="source/net/ipv4/tcp_output.c#L1846">1846</a> static inline void <a href="ident?i=tcp_mtu_check_reprobe">tcp_mtu_check_reprobe</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L1847" href="source/net/ipv4/tcp_output.c#L1847">1847</a> {
<a name="L1848" href="source/net/ipv4/tcp_output.c#L1848">1848</a>         struct <a href="ident?i=inet_connection_sock">inet_connection_sock</a> *icsk = <a href="ident?i=inet_csk">inet_csk</a>(sk);
<a name="L1849" href="source/net/ipv4/tcp_output.c#L1849">1849</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L1850" href="source/net/ipv4/tcp_output.c#L1850">1850</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=sock_net">sock_net</a>(sk);
<a name="L1851" href="source/net/ipv4/tcp_output.c#L1851">1851</a>         <a href="ident?i=u32">u32</a> <a href="ident?i=interval">interval</a>;
<a name="L1852" href="source/net/ipv4/tcp_output.c#L1852">1852</a>         <a href="ident?i=s32">s32</a> <a href="ident?i=delta">delta</a>;
<a name="L1853" href="source/net/ipv4/tcp_output.c#L1853">1853</a> 
<a name="L1854" href="source/net/ipv4/tcp_output.c#L1854">1854</a>         <a href="ident?i=interval">interval</a> = <a href="ident?i=net">net</a>-&gt;ipv4.sysctl_tcp_probe_interval;
<a name="L1855" href="source/net/ipv4/tcp_output.c#L1855">1855</a>         <a href="ident?i=delta">delta</a> = <a href="ident?i=tcp_time_stamp">tcp_time_stamp</a> - icsk-&gt;icsk_mtup.probe_timestamp;
<a name="L1856" href="source/net/ipv4/tcp_output.c#L1856">1856</a>         if (<a href="ident?i=unlikely">unlikely</a>(<a href="ident?i=delta">delta</a> &gt;= <a href="ident?i=interval">interval</a> * <a href="ident?i=HZ">HZ</a>)) {
<a name="L1857" href="source/net/ipv4/tcp_output.c#L1857">1857</a>                 int mss = <a href="ident?i=tcp_current_mss">tcp_current_mss</a>(sk);
<a name="L1858" href="source/net/ipv4/tcp_output.c#L1858">1858</a> 
<a name="L1859" href="source/net/ipv4/tcp_output.c#L1859">1859</a>                 <b><i>/* Update current search range */</i></b>
<a name="L1860" href="source/net/ipv4/tcp_output.c#L1860">1860</a>                 icsk-&gt;icsk_mtup.probe_size = 0;
<a name="L1861" href="source/net/ipv4/tcp_output.c#L1861">1861</a>                 icsk-&gt;icsk_mtup.search_high = <a href="ident?i=tp">tp</a>-&gt;rx_opt.mss_clamp +
<a name="L1862" href="source/net/ipv4/tcp_output.c#L1862">1862</a>                         sizeof(struct <a href="ident?i=tcphdr">tcphdr</a>) +
<a name="L1863" href="source/net/ipv4/tcp_output.c#L1863">1863</a>                         icsk-&gt;icsk_af_ops-&gt;net_header_len;
<a name="L1864" href="source/net/ipv4/tcp_output.c#L1864">1864</a>                 icsk-&gt;icsk_mtup.search_low = <a href="ident?i=tcp_mss_to_mtu">tcp_mss_to_mtu</a>(sk, mss);
<a name="L1865" href="source/net/ipv4/tcp_output.c#L1865">1865</a> 
<a name="L1866" href="source/net/ipv4/tcp_output.c#L1866">1866</a>                 <b><i>/* Update probe time stamp */</i></b>
<a name="L1867" href="source/net/ipv4/tcp_output.c#L1867">1867</a>                 icsk-&gt;icsk_mtup.probe_timestamp = <a href="ident?i=tcp_time_stamp">tcp_time_stamp</a>;
<a name="L1868" href="source/net/ipv4/tcp_output.c#L1868">1868</a>         }
<a name="L1869" href="source/net/ipv4/tcp_output.c#L1869">1869</a> }
<a name="L1870" href="source/net/ipv4/tcp_output.c#L1870">1870</a> 
<a name="L1871" href="source/net/ipv4/tcp_output.c#L1871">1871</a> <b><i>/* Create a new MTU probe if we are ready.</i></b>
<a name="L1872" href="source/net/ipv4/tcp_output.c#L1872">1872</a> <b><i> * MTU probe is regularly attempting to increase the path MTU by</i></b>
<a name="L1873" href="source/net/ipv4/tcp_output.c#L1873">1873</a> <b><i> * deliberately sending larger packets.  This discovers routing</i></b>
<a name="L1874" href="source/net/ipv4/tcp_output.c#L1874">1874</a> <b><i> * changes resulting in larger path MTUs.</i></b>
<a name="L1875" href="source/net/ipv4/tcp_output.c#L1875">1875</a> <b><i> *</i></b>
<a name="L1876" href="source/net/ipv4/tcp_output.c#L1876">1876</a> <b><i> * Returns 0 if we should wait to probe (no cwnd available),</i></b>
<a name="L1877" href="source/net/ipv4/tcp_output.c#L1877">1877</a> <b><i> *         1 if a probe was sent,</i></b>
<a name="L1878" href="source/net/ipv4/tcp_output.c#L1878">1878</a> <b><i> *         -1 otherwise</i></b>
<a name="L1879" href="source/net/ipv4/tcp_output.c#L1879">1879</a> <b><i> */</i></b>
<a name="L1880" href="source/net/ipv4/tcp_output.c#L1880">1880</a> static int <a href="ident?i=tcp_mtu_probe">tcp_mtu_probe</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L1881" href="source/net/ipv4/tcp_output.c#L1881">1881</a> {
<a name="L1882" href="source/net/ipv4/tcp_output.c#L1882">1882</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L1883" href="source/net/ipv4/tcp_output.c#L1883">1883</a>         struct <a href="ident?i=inet_connection_sock">inet_connection_sock</a> *icsk = <a href="ident?i=inet_csk">inet_csk</a>(sk);
<a name="L1884" href="source/net/ipv4/tcp_output.c#L1884">1884</a>         struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, *nskb, *<a href="ident?i=next">next</a>;
<a name="L1885" href="source/net/ipv4/tcp_output.c#L1885">1885</a>         struct <a href="ident?i=net">net</a> *<a href="ident?i=net">net</a> = <a href="ident?i=sock_net">sock_net</a>(sk);
<a name="L1886" href="source/net/ipv4/tcp_output.c#L1886">1886</a>         int <a href="ident?i=len">len</a>;
<a name="L1887" href="source/net/ipv4/tcp_output.c#L1887">1887</a>         int probe_size;
<a name="L1888" href="source/net/ipv4/tcp_output.c#L1888">1888</a>         int size_needed;
<a name="L1889" href="source/net/ipv4/tcp_output.c#L1889">1889</a>         int <a href="ident?i=copy">copy</a>;
<a name="L1890" href="source/net/ipv4/tcp_output.c#L1890">1890</a>         int mss_now;
<a name="L1891" href="source/net/ipv4/tcp_output.c#L1891">1891</a>         int <a href="ident?i=interval">interval</a>;
<a name="L1892" href="source/net/ipv4/tcp_output.c#L1892">1892</a> 
<a name="L1893" href="source/net/ipv4/tcp_output.c#L1893">1893</a>         <b><i>/* Not currently probing/verifying,</i></b>
<a name="L1894" href="source/net/ipv4/tcp_output.c#L1894">1894</a> <b><i>         * not in recovery,</i></b>
<a name="L1895" href="source/net/ipv4/tcp_output.c#L1895">1895</a> <b><i>         * have enough cwnd, and</i></b>
<a name="L1896" href="source/net/ipv4/tcp_output.c#L1896">1896</a> <b><i>         * not SACKing (the variable headers throw things off) */</i></b>
<a name="L1897" href="source/net/ipv4/tcp_output.c#L1897">1897</a>         if (!icsk-&gt;icsk_mtup.<a href="ident?i=enabled">enabled</a> ||
<a name="L1898" href="source/net/ipv4/tcp_output.c#L1898">1898</a>             icsk-&gt;icsk_mtup.probe_size ||
<a name="L1899" href="source/net/ipv4/tcp_output.c#L1899">1899</a>             <a href="ident?i=inet_csk">inet_csk</a>(sk)-&gt;icsk_ca_state != TCP_CA_Open ||
<a name="L1900" href="source/net/ipv4/tcp_output.c#L1900">1900</a>             <a href="ident?i=tp">tp</a>-&gt;snd_cwnd &lt; 11 ||
<a name="L1901" href="source/net/ipv4/tcp_output.c#L1901">1901</a>             <a href="ident?i=tp">tp</a>-&gt;rx_opt.num_sacks || <a href="ident?i=tp">tp</a>-&gt;rx_opt.dsack)
<a name="L1902" href="source/net/ipv4/tcp_output.c#L1902">1902</a>                 return -1;
<a name="L1903" href="source/net/ipv4/tcp_output.c#L1903">1903</a> 
<a name="L1904" href="source/net/ipv4/tcp_output.c#L1904">1904</a>         <b><i>/* Use binary search for probe_size between tcp_mss_base,</i></b>
<a name="L1905" href="source/net/ipv4/tcp_output.c#L1905">1905</a> <b><i>         * and current mss_clamp. if (search_high - search_low)</i></b>
<a name="L1906" href="source/net/ipv4/tcp_output.c#L1906">1906</a> <b><i>         * smaller than a threshold, backoff from probing.</i></b>
<a name="L1907" href="source/net/ipv4/tcp_output.c#L1907">1907</a> <b><i>         */</i></b>
<a name="L1908" href="source/net/ipv4/tcp_output.c#L1908">1908</a>         mss_now = <a href="ident?i=tcp_current_mss">tcp_current_mss</a>(sk);
<a name="L1909" href="source/net/ipv4/tcp_output.c#L1909">1909</a>         probe_size = <a href="ident?i=tcp_mtu_to_mss">tcp_mtu_to_mss</a>(sk, (icsk-&gt;icsk_mtup.search_high +
<a name="L1910" href="source/net/ipv4/tcp_output.c#L1910">1910</a>                                     icsk-&gt;icsk_mtup.search_low) &gt;&gt; 1);
<a name="L1911" href="source/net/ipv4/tcp_output.c#L1911">1911</a>         size_needed = probe_size + (<a href="ident?i=tp">tp</a>-&gt;reordering + 1) * <a href="ident?i=tp">tp</a>-&gt;mss_cache;
<a name="L1912" href="source/net/ipv4/tcp_output.c#L1912">1912</a>         <a href="ident?i=interval">interval</a> = icsk-&gt;icsk_mtup.search_high - icsk-&gt;icsk_mtup.search_low;
<a name="L1913" href="source/net/ipv4/tcp_output.c#L1913">1913</a>         <b><i>/* When misfortune happens, we are reprobing actively,</i></b>
<a name="L1914" href="source/net/ipv4/tcp_output.c#L1914">1914</a> <b><i>         * and then reprobe timer has expired. We stick with current</i></b>
<a name="L1915" href="source/net/ipv4/tcp_output.c#L1915">1915</a> <b><i>         * probing process by not resetting search range to its orignal.</i></b>
<a name="L1916" href="source/net/ipv4/tcp_output.c#L1916">1916</a> <b><i>         */</i></b>
<a name="L1917" href="source/net/ipv4/tcp_output.c#L1917">1917</a>         if (probe_size &gt; <a href="ident?i=tcp_mtu_to_mss">tcp_mtu_to_mss</a>(sk, icsk-&gt;icsk_mtup.search_high) ||
<a name="L1918" href="source/net/ipv4/tcp_output.c#L1918">1918</a>                 <a href="ident?i=interval">interval</a> &lt; <a href="ident?i=net">net</a>-&gt;ipv4.sysctl_tcp_probe_threshold) {
<a name="L1919" href="source/net/ipv4/tcp_output.c#L1919">1919</a>                 <b><i>/* Check whether enough time has elaplased for</i></b>
<a name="L1920" href="source/net/ipv4/tcp_output.c#L1920">1920</a> <b><i>                 * another round of probing.</i></b>
<a name="L1921" href="source/net/ipv4/tcp_output.c#L1921">1921</a> <b><i>                 */</i></b>
<a name="L1922" href="source/net/ipv4/tcp_output.c#L1922">1922</a>                 <a href="ident?i=tcp_mtu_check_reprobe">tcp_mtu_check_reprobe</a>(sk);
<a name="L1923" href="source/net/ipv4/tcp_output.c#L1923">1923</a>                 return -1;
<a name="L1924" href="source/net/ipv4/tcp_output.c#L1924">1924</a>         }
<a name="L1925" href="source/net/ipv4/tcp_output.c#L1925">1925</a> 
<a name="L1926" href="source/net/ipv4/tcp_output.c#L1926">1926</a>         <b><i>/* Have enough data in the send queue to probe? */</i></b>
<a name="L1927" href="source/net/ipv4/tcp_output.c#L1927">1927</a>         if (<a href="ident?i=tp">tp</a>-&gt;write_seq - <a href="ident?i=tp">tp</a>-&gt;snd_nxt &lt; size_needed)
<a name="L1928" href="source/net/ipv4/tcp_output.c#L1928">1928</a>                 return -1;
<a name="L1929" href="source/net/ipv4/tcp_output.c#L1929">1929</a> 
<a name="L1930" href="source/net/ipv4/tcp_output.c#L1930">1930</a>         if (<a href="ident?i=tp">tp</a>-&gt;snd_wnd &lt; size_needed)
<a name="L1931" href="source/net/ipv4/tcp_output.c#L1931">1931</a>                 return -1;
<a name="L1932" href="source/net/ipv4/tcp_output.c#L1932">1932</a>         if (<a href="ident?i=after">after</a>(<a href="ident?i=tp">tp</a>-&gt;snd_nxt + size_needed, <a href="ident?i=tcp_wnd_end">tcp_wnd_end</a>(<a href="ident?i=tp">tp</a>)))
<a name="L1933" href="source/net/ipv4/tcp_output.c#L1933">1933</a>                 return 0;
<a name="L1934" href="source/net/ipv4/tcp_output.c#L1934">1934</a> 
<a name="L1935" href="source/net/ipv4/tcp_output.c#L1935">1935</a>         <b><i>/* Do we need to wait to drain cwnd? With none in flight, don't stall */</i></b>
<a name="L1936" href="source/net/ipv4/tcp_output.c#L1936">1936</a>         if (<a href="ident?i=tcp_packets_in_flight">tcp_packets_in_flight</a>(<a href="ident?i=tp">tp</a>) + 2 &gt; <a href="ident?i=tp">tp</a>-&gt;snd_cwnd) {
<a name="L1937" href="source/net/ipv4/tcp_output.c#L1937">1937</a>                 if (!<a href="ident?i=tcp_packets_in_flight">tcp_packets_in_flight</a>(<a href="ident?i=tp">tp</a>))
<a name="L1938" href="source/net/ipv4/tcp_output.c#L1938">1938</a>                         return -1;
<a name="L1939" href="source/net/ipv4/tcp_output.c#L1939">1939</a>                 else
<a name="L1940" href="source/net/ipv4/tcp_output.c#L1940">1940</a>                         return 0;
<a name="L1941" href="source/net/ipv4/tcp_output.c#L1941">1941</a>         }
<a name="L1942" href="source/net/ipv4/tcp_output.c#L1942">1942</a> 
<a name="L1943" href="source/net/ipv4/tcp_output.c#L1943">1943</a>         <b><i>/* We're allowed to probe.  Build it now. */</i></b>
<a name="L1944" href="source/net/ipv4/tcp_output.c#L1944">1944</a>         nskb = <a href="ident?i=sk_stream_alloc_skb">sk_stream_alloc_skb</a>(sk, probe_size, <a href="ident?i=GFP_ATOMIC">GFP_ATOMIC</a>);
<a name="L1945" href="source/net/ipv4/tcp_output.c#L1945">1945</a>         if (!nskb)
<a name="L1946" href="source/net/ipv4/tcp_output.c#L1946">1946</a>                 return -1;
<a name="L1947" href="source/net/ipv4/tcp_output.c#L1947">1947</a>         sk-&gt;sk_wmem_queued += nskb-&gt;truesize;
<a name="L1948" href="source/net/ipv4/tcp_output.c#L1948">1948</a>         <a href="ident?i=sk_mem_charge">sk_mem_charge</a>(sk, nskb-&gt;truesize);
<a name="L1949" href="source/net/ipv4/tcp_output.c#L1949">1949</a> 
<a name="L1950" href="source/net/ipv4/tcp_output.c#L1950">1950</a>         <a href="ident?i=skb">skb</a> = <a href="ident?i=tcp_send_head">tcp_send_head</a>(sk);
<a name="L1951" href="source/net/ipv4/tcp_output.c#L1951">1951</a> 
<a name="L1952" href="source/net/ipv4/tcp_output.c#L1952">1952</a>         <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(nskb)-&gt;<a href="ident?i=seq">seq</a> = <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=seq">seq</a>;
<a name="L1953" href="source/net/ipv4/tcp_output.c#L1953">1953</a>         <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(nskb)-&gt;end_seq = <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=seq">seq</a> + probe_size;
<a name="L1954" href="source/net/ipv4/tcp_output.c#L1954">1954</a>         <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(nskb)-&gt;tcp_flags = <a href="ident?i=TCPHDR_ACK">TCPHDR_ACK</a>;
<a name="L1955" href="source/net/ipv4/tcp_output.c#L1955">1955</a>         <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(nskb)-&gt;sacked = 0;
<a name="L1956" href="source/net/ipv4/tcp_output.c#L1956">1956</a>         nskb-&gt;<a href="ident?i=csum">csum</a> = 0;
<a name="L1957" href="source/net/ipv4/tcp_output.c#L1957">1957</a>         nskb-&gt;ip_summed = <a href="ident?i=skb">skb</a>-&gt;ip_summed;
<a name="L1958" href="source/net/ipv4/tcp_output.c#L1958">1958</a> 
<a name="L1959" href="source/net/ipv4/tcp_output.c#L1959">1959</a>         <a href="ident?i=tcp_insert_write_queue_before">tcp_insert_write_queue_before</a>(nskb, <a href="ident?i=skb">skb</a>, sk);
<a name="L1960" href="source/net/ipv4/tcp_output.c#L1960">1960</a> 
<a name="L1961" href="source/net/ipv4/tcp_output.c#L1961">1961</a>         <a href="ident?i=len">len</a> = 0;
<a name="L1962" href="source/net/ipv4/tcp_output.c#L1962">1962</a>         <a href="ident?i=tcp_for_write_queue_from_safe">tcp_for_write_queue_from_safe</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=next">next</a>, sk) {
<a name="L1963" href="source/net/ipv4/tcp_output.c#L1963">1963</a>                 <a href="ident?i=copy">copy</a> = <a href="ident?i=min_t">min_t</a>(int, <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a>, probe_size - <a href="ident?i=len">len</a>);
<a name="L1964" href="source/net/ipv4/tcp_output.c#L1964">1964</a>                 if (nskb-&gt;ip_summed)
<a name="L1965" href="source/net/ipv4/tcp_output.c#L1965">1965</a>                         <a href="ident?i=skb_copy_bits">skb_copy_bits</a>(<a href="ident?i=skb">skb</a>, 0, <a href="ident?i=skb_put">skb_put</a>(nskb, <a href="ident?i=copy">copy</a>), <a href="ident?i=copy">copy</a>);
<a name="L1966" href="source/net/ipv4/tcp_output.c#L1966">1966</a>                 else
<a name="L1967" href="source/net/ipv4/tcp_output.c#L1967">1967</a>                         nskb-&gt;<a href="ident?i=csum">csum</a> = <a href="ident?i=skb_copy_and_csum_bits">skb_copy_and_csum_bits</a>(<a href="ident?i=skb">skb</a>, 0,
<a name="L1968" href="source/net/ipv4/tcp_output.c#L1968">1968</a>                                                             <a href="ident?i=skb_put">skb_put</a>(nskb, <a href="ident?i=copy">copy</a>),
<a name="L1969" href="source/net/ipv4/tcp_output.c#L1969">1969</a>                                                             <a href="ident?i=copy">copy</a>, nskb-&gt;<a href="ident?i=csum">csum</a>);
<a name="L1970" href="source/net/ipv4/tcp_output.c#L1970">1970</a> 
<a name="L1971" href="source/net/ipv4/tcp_output.c#L1971">1971</a>                 if (<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a> &lt;= <a href="ident?i=copy">copy</a>) {
<a name="L1972" href="source/net/ipv4/tcp_output.c#L1972">1972</a>                         <b><i>/* We've eaten all the data from this skb.</i></b>
<a name="L1973" href="source/net/ipv4/tcp_output.c#L1973">1973</a> <b><i>                         * Throw it away. */</i></b>
<a name="L1974" href="source/net/ipv4/tcp_output.c#L1974">1974</a>                         <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(nskb)-&gt;tcp_flags |= <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;tcp_flags;
<a name="L1975" href="source/net/ipv4/tcp_output.c#L1975">1975</a>                         <a href="ident?i=tcp_unlink_write_queue">tcp_unlink_write_queue</a>(<a href="ident?i=skb">skb</a>, sk);
<a name="L1976" href="source/net/ipv4/tcp_output.c#L1976">1976</a>                         <a href="ident?i=sk_wmem_free_skb">sk_wmem_free_skb</a>(sk, <a href="ident?i=skb">skb</a>);
<a name="L1977" href="source/net/ipv4/tcp_output.c#L1977">1977</a>                 } else {
<a name="L1978" href="source/net/ipv4/tcp_output.c#L1978">1978</a>                         <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(nskb)-&gt;tcp_flags |= <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;tcp_flags &amp;
<a name="L1979" href="source/net/ipv4/tcp_output.c#L1979">1979</a>                                                    ~(<a href="ident?i=TCPHDR_FIN">TCPHDR_FIN</a>|<a href="ident?i=TCPHDR_PSH">TCPHDR_PSH</a>);
<a name="L1980" href="source/net/ipv4/tcp_output.c#L1980">1980</a>                         if (!<a href="ident?i=skb_shinfo">skb_shinfo</a>(<a href="ident?i=skb">skb</a>)-&gt;nr_frags) {
<a name="L1981" href="source/net/ipv4/tcp_output.c#L1981">1981</a>                                 <a href="ident?i=skb_pull">skb_pull</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=copy">copy</a>);
<a name="L1982" href="source/net/ipv4/tcp_output.c#L1982">1982</a>                                 if (<a href="ident?i=skb">skb</a>-&gt;ip_summed != <a href="ident?i=CHECKSUM_PARTIAL">CHECKSUM_PARTIAL</a>)
<a name="L1983" href="source/net/ipv4/tcp_output.c#L1983">1983</a>                                         <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=csum">csum</a> = <a href="ident?i=csum_partial">csum_partial</a>(<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=data">data</a>,
<a name="L1984" href="source/net/ipv4/tcp_output.c#L1984">1984</a>                                                                  <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a>, 0);
<a name="L1985" href="source/net/ipv4/tcp_output.c#L1985">1985</a>                         } else {
<a name="L1986" href="source/net/ipv4/tcp_output.c#L1986">1986</a>                                 <a href="ident?i=__pskb_trim_head">__pskb_trim_head</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=copy">copy</a>);
<a name="L1987" href="source/net/ipv4/tcp_output.c#L1987">1987</a>                                 <a href="ident?i=tcp_set_skb_tso_segs">tcp_set_skb_tso_segs</a>(sk, <a href="ident?i=skb">skb</a>, mss_now);
<a name="L1988" href="source/net/ipv4/tcp_output.c#L1988">1988</a>                         }
<a name="L1989" href="source/net/ipv4/tcp_output.c#L1989">1989</a>                         <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=seq">seq</a> += <a href="ident?i=copy">copy</a>;
<a name="L1990" href="source/net/ipv4/tcp_output.c#L1990">1990</a>                 }
<a name="L1991" href="source/net/ipv4/tcp_output.c#L1991">1991</a> 
<a name="L1992" href="source/net/ipv4/tcp_output.c#L1992">1992</a>                 <a href="ident?i=len">len</a> += <a href="ident?i=copy">copy</a>;
<a name="L1993" href="source/net/ipv4/tcp_output.c#L1993">1993</a> 
<a name="L1994" href="source/net/ipv4/tcp_output.c#L1994">1994</a>                 if (<a href="ident?i=len">len</a> &gt;= probe_size)
<a name="L1995" href="source/net/ipv4/tcp_output.c#L1995">1995</a>                         break;
<a name="L1996" href="source/net/ipv4/tcp_output.c#L1996">1996</a>         }
<a name="L1997" href="source/net/ipv4/tcp_output.c#L1997">1997</a>         <a href="ident?i=tcp_init_tso_segs">tcp_init_tso_segs</a>(sk, nskb, nskb-&gt;<a href="ident?i=len">len</a>);
<a name="L1998" href="source/net/ipv4/tcp_output.c#L1998">1998</a> 
<a name="L1999" href="source/net/ipv4/tcp_output.c#L1999">1999</a>         <b><i>/* We're ready to send.  If this fails, the probe will</i></b>
<a name="L2000" href="source/net/ipv4/tcp_output.c#L2000">2000</a> <b><i>         * be resegmented into mss-sized pieces by tcp_write_xmit().</i></b>
<a name="L2001" href="source/net/ipv4/tcp_output.c#L2001">2001</a> <b><i>         */</i></b>
<a name="L2002" href="source/net/ipv4/tcp_output.c#L2002">2002</a>         if (!<a href="ident?i=tcp_transmit_skb">tcp_transmit_skb</a>(sk, nskb, 1, <a href="ident?i=GFP_ATOMIC">GFP_ATOMIC</a>)) {
<a name="L2003" href="source/net/ipv4/tcp_output.c#L2003">2003</a>                 <b><i>/* Decrement cwnd here because we are sending</i></b>
<a name="L2004" href="source/net/ipv4/tcp_output.c#L2004">2004</a> <b><i>                 * effectively two packets. */</i></b>
<a name="L2005" href="source/net/ipv4/tcp_output.c#L2005">2005</a>                 <a href="ident?i=tp">tp</a>-&gt;snd_cwnd--;
<a name="L2006" href="source/net/ipv4/tcp_output.c#L2006">2006</a>                 <a href="ident?i=tcp_event_new_data_sent">tcp_event_new_data_sent</a>(sk, nskb);
<a name="L2007" href="source/net/ipv4/tcp_output.c#L2007">2007</a> 
<a name="L2008" href="source/net/ipv4/tcp_output.c#L2008">2008</a>                 icsk-&gt;icsk_mtup.probe_size = <a href="ident?i=tcp_mss_to_mtu">tcp_mss_to_mtu</a>(sk, nskb-&gt;<a href="ident?i=len">len</a>);
<a name="L2009" href="source/net/ipv4/tcp_output.c#L2009">2009</a>                 <a href="ident?i=tp">tp</a>-&gt;mtu_probe.probe_seq_start = <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(nskb)-&gt;<a href="ident?i=seq">seq</a>;
<a name="L2010" href="source/net/ipv4/tcp_output.c#L2010">2010</a>                 <a href="ident?i=tp">tp</a>-&gt;mtu_probe.probe_seq_end = <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(nskb)-&gt;end_seq;
<a name="L2011" href="source/net/ipv4/tcp_output.c#L2011">2011</a> 
<a name="L2012" href="source/net/ipv4/tcp_output.c#L2012">2012</a>                 return 1;
<a name="L2013" href="source/net/ipv4/tcp_output.c#L2013">2013</a>         }
<a name="L2014" href="source/net/ipv4/tcp_output.c#L2014">2014</a> 
<a name="L2015" href="source/net/ipv4/tcp_output.c#L2015">2015</a>         return -1;
<a name="L2016" href="source/net/ipv4/tcp_output.c#L2016">2016</a> }
<a name="L2017" href="source/net/ipv4/tcp_output.c#L2017">2017</a> 
<a name="L2018" href="source/net/ipv4/tcp_output.c#L2018">2018</a> <b><i>/* This routine writes packets to the network.  It advances the</i></b>
<a name="L2019" href="source/net/ipv4/tcp_output.c#L2019">2019</a> <b><i> * send_head.  This happens as incoming acks open up the remote</i></b>
<a name="L2020" href="source/net/ipv4/tcp_output.c#L2020">2020</a> <b><i> * window for us.</i></b>
<a name="L2021" href="source/net/ipv4/tcp_output.c#L2021">2021</a> <b><i> *</i></b>
<a name="L2022" href="source/net/ipv4/tcp_output.c#L2022">2022</a> <b><i> * LARGESEND note: !tcp_urg_mode is overkill, only frames between</i></b>
<a name="L2023" href="source/net/ipv4/tcp_output.c#L2023">2023</a> <b><i> * snd_up-64k-mss .. snd_up cannot be large. However, taking into</i></b>
<a name="L2024" href="source/net/ipv4/tcp_output.c#L2024">2024</a> <b><i> * account rare use of URG, this is not a big flaw.</i></b>
<a name="L2025" href="source/net/ipv4/tcp_output.c#L2025">2025</a> <b><i> *</i></b>
<a name="L2026" href="source/net/ipv4/tcp_output.c#L2026">2026</a> <b><i> * Send at most one packet when push_one &gt; 0. Temporarily ignore</i></b>
<a name="L2027" href="source/net/ipv4/tcp_output.c#L2027">2027</a> <b><i> * cwnd limit to force at most one packet out when push_one == 2.</i></b>
<a name="L2028" href="source/net/ipv4/tcp_output.c#L2028">2028</a> <b><i></i></b>
<a name="L2029" href="source/net/ipv4/tcp_output.c#L2029">2029</a> <b><i> * Returns true, if no segments are in flight and we have queued segments,</i></b>
<a name="L2030" href="source/net/ipv4/tcp_output.c#L2030">2030</a> <b><i> * but cannot send anything now because of SWS or another problem.</i></b>
<a name="L2031" href="source/net/ipv4/tcp_output.c#L2031">2031</a> <b><i> */</i></b>
<a name="L2032" href="source/net/ipv4/tcp_output.c#L2032">2032</a> static <a href="ident?i=bool">bool</a> <a href="ident?i=tcp_write_xmit">tcp_write_xmit</a>(struct <a href="ident?i=sock">sock</a> *sk, unsigned int mss_now, int nonagle,
<a name="L2033" href="source/net/ipv4/tcp_output.c#L2033">2033</a>                            int push_one, <a href="ident?i=gfp_t">gfp_t</a> gfp)
<a name="L2034" href="source/net/ipv4/tcp_output.c#L2034">2034</a> {
<a name="L2035" href="source/net/ipv4/tcp_output.c#L2035">2035</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L2036" href="source/net/ipv4/tcp_output.c#L2036">2036</a>         struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>;
<a name="L2037" href="source/net/ipv4/tcp_output.c#L2037">2037</a>         unsigned int tso_segs, sent_pkts;
<a name="L2038" href="source/net/ipv4/tcp_output.c#L2038">2038</a>         int cwnd_quota;
<a name="L2039" href="source/net/ipv4/tcp_output.c#L2039">2039</a>         int <a href="ident?i=result">result</a>;
<a name="L2040" href="source/net/ipv4/tcp_output.c#L2040">2040</a>         <a href="ident?i=bool">bool</a> is_cwnd_limited = <a href="ident?i=false">false</a>;
<a name="L2041" href="source/net/ipv4/tcp_output.c#L2041">2041</a>         <a href="ident?i=u32">u32</a> max_segs;
<a name="L2042" href="source/net/ipv4/tcp_output.c#L2042">2042</a> 
<a name="L2043" href="source/net/ipv4/tcp_output.c#L2043">2043</a>         sent_pkts = 0;
<a name="L2044" href="source/net/ipv4/tcp_output.c#L2044">2044</a> 
<a name="L2045" href="source/net/ipv4/tcp_output.c#L2045">2045</a>         if (!push_one) {
<a name="L2046" href="source/net/ipv4/tcp_output.c#L2046">2046</a>                 <b><i>/* Do MTU probing. */</i></b>
<a name="L2047" href="source/net/ipv4/tcp_output.c#L2047">2047</a>                 <a href="ident?i=result">result</a> = <a href="ident?i=tcp_mtu_probe">tcp_mtu_probe</a>(sk);
<a name="L2048" href="source/net/ipv4/tcp_output.c#L2048">2048</a>                 if (!<a href="ident?i=result">result</a>) {
<a name="L2049" href="source/net/ipv4/tcp_output.c#L2049">2049</a>                         return <a href="ident?i=false">false</a>;
<a name="L2050" href="source/net/ipv4/tcp_output.c#L2050">2050</a>                 } else if (<a href="ident?i=result">result</a> &gt; 0) {
<a name="L2051" href="source/net/ipv4/tcp_output.c#L2051">2051</a>                         sent_pkts = 1;
<a name="L2052" href="source/net/ipv4/tcp_output.c#L2052">2052</a>                 }
<a name="L2053" href="source/net/ipv4/tcp_output.c#L2053">2053</a>         }
<a name="L2054" href="source/net/ipv4/tcp_output.c#L2054">2054</a> 
<a name="L2055" href="source/net/ipv4/tcp_output.c#L2055">2055</a>         max_segs = <a href="ident?i=tcp_tso_autosize">tcp_tso_autosize</a>(sk, mss_now);
<a name="L2056" href="source/net/ipv4/tcp_output.c#L2056">2056</a>         while ((<a href="ident?i=skb">skb</a> = <a href="ident?i=tcp_send_head">tcp_send_head</a>(sk))) {
<a name="L2057" href="source/net/ipv4/tcp_output.c#L2057">2057</a>                 unsigned int <a href="ident?i=limit">limit</a>;
<a name="L2058" href="source/net/ipv4/tcp_output.c#L2058">2058</a> 
<a name="L2059" href="source/net/ipv4/tcp_output.c#L2059">2059</a>                 tso_segs = <a href="ident?i=tcp_init_tso_segs">tcp_init_tso_segs</a>(sk, <a href="ident?i=skb">skb</a>, mss_now);
<a name="L2060" href="source/net/ipv4/tcp_output.c#L2060">2060</a>                 <a href="ident?i=BUG_ON">BUG_ON</a>(!tso_segs);
<a name="L2061" href="source/net/ipv4/tcp_output.c#L2061">2061</a> 
<a name="L2062" href="source/net/ipv4/tcp_output.c#L2062">2062</a>                 if (<a href="ident?i=unlikely">unlikely</a>(<a href="ident?i=tp">tp</a>-&gt;repair) &amp;&amp; <a href="ident?i=tp">tp</a>-&gt;repair_queue == TCP_SEND_QUEUE) {
<a name="L2063" href="source/net/ipv4/tcp_output.c#L2063">2063</a>                         <b><i>/* "skb_mstamp" is used as a start point for the retransmit timer */</i></b>
<a name="L2064" href="source/net/ipv4/tcp_output.c#L2064">2064</a>                         <a href="ident?i=skb_mstamp_get">skb_mstamp_get</a>(&amp;<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=skb_mstamp">skb_mstamp</a>);
<a name="L2065" href="source/net/ipv4/tcp_output.c#L2065">2065</a>                         goto repair; <b><i>/* Skip network transmission */</i></b>
<a name="L2066" href="source/net/ipv4/tcp_output.c#L2066">2066</a>                 }
<a name="L2067" href="source/net/ipv4/tcp_output.c#L2067">2067</a> 
<a name="L2068" href="source/net/ipv4/tcp_output.c#L2068">2068</a>                 cwnd_quota = <a href="ident?i=tcp_cwnd_test">tcp_cwnd_test</a>(<a href="ident?i=tp">tp</a>, <a href="ident?i=skb">skb</a>);
<a name="L2069" href="source/net/ipv4/tcp_output.c#L2069">2069</a>                 if (!cwnd_quota) {
<a name="L2070" href="source/net/ipv4/tcp_output.c#L2070">2070</a>                         is_cwnd_limited = <a href="ident?i=true">true</a>;
<a name="L2071" href="source/net/ipv4/tcp_output.c#L2071">2071</a>                         if (push_one == 2)
<a name="L2072" href="source/net/ipv4/tcp_output.c#L2072">2072</a>                                 <b><i>/* Force out a loss probe pkt. */</i></b>
<a name="L2073" href="source/net/ipv4/tcp_output.c#L2073">2073</a>                                 cwnd_quota = 1;
<a name="L2074" href="source/net/ipv4/tcp_output.c#L2074">2074</a>                         else
<a name="L2075" href="source/net/ipv4/tcp_output.c#L2075">2075</a>                                 break;
<a name="L2076" href="source/net/ipv4/tcp_output.c#L2076">2076</a>                 }
<a name="L2077" href="source/net/ipv4/tcp_output.c#L2077">2077</a> 
<a name="L2078" href="source/net/ipv4/tcp_output.c#L2078">2078</a>                 if (<a href="ident?i=unlikely">unlikely</a>(!<a href="ident?i=tcp_snd_wnd_test">tcp_snd_wnd_test</a>(<a href="ident?i=tp">tp</a>, <a href="ident?i=skb">skb</a>, mss_now)))
<a name="L2079" href="source/net/ipv4/tcp_output.c#L2079">2079</a>                         break;
<a name="L2080" href="source/net/ipv4/tcp_output.c#L2080">2080</a> 
<a name="L2081" href="source/net/ipv4/tcp_output.c#L2081">2081</a>                 if (tso_segs == 1 || !max_segs) {
<a name="L2082" href="source/net/ipv4/tcp_output.c#L2082">2082</a>                         if (<a href="ident?i=unlikely">unlikely</a>(!<a href="ident?i=tcp_nagle_test">tcp_nagle_test</a>(<a href="ident?i=tp">tp</a>, <a href="ident?i=skb">skb</a>, mss_now,
<a name="L2083" href="source/net/ipv4/tcp_output.c#L2083">2083</a>                                                      (<a href="ident?i=tcp_skb_is_last">tcp_skb_is_last</a>(sk, <a href="ident?i=skb">skb</a>) ?
<a name="L2084" href="source/net/ipv4/tcp_output.c#L2084">2084</a>                                                       nonagle : <a href="ident?i=TCP_NAGLE_PUSH">TCP_NAGLE_PUSH</a>))))
<a name="L2085" href="source/net/ipv4/tcp_output.c#L2085">2085</a>                                 break;
<a name="L2086" href="source/net/ipv4/tcp_output.c#L2086">2086</a>                 } else {
<a name="L2087" href="source/net/ipv4/tcp_output.c#L2087">2087</a>                         if (!push_one &amp;&amp;
<a name="L2088" href="source/net/ipv4/tcp_output.c#L2088">2088</a>                             <a href="ident?i=tcp_tso_should_defer">tcp_tso_should_defer</a>(sk, <a href="ident?i=skb">skb</a>, &amp;is_cwnd_limited,
<a name="L2089" href="source/net/ipv4/tcp_output.c#L2089">2089</a>                                                  max_segs))
<a name="L2090" href="source/net/ipv4/tcp_output.c#L2090">2090</a>                                 break;
<a name="L2091" href="source/net/ipv4/tcp_output.c#L2091">2091</a>                 }
<a name="L2092" href="source/net/ipv4/tcp_output.c#L2092">2092</a> 
<a name="L2093" href="source/net/ipv4/tcp_output.c#L2093">2093</a>                 <a href="ident?i=limit">limit</a> = mss_now;
<a name="L2094" href="source/net/ipv4/tcp_output.c#L2094">2094</a>                 if (tso_segs &gt; 1 &amp;&amp; max_segs &amp;&amp; !<a href="ident?i=tcp_urg_mode">tcp_urg_mode</a>(<a href="ident?i=tp">tp</a>))
<a name="L2095" href="source/net/ipv4/tcp_output.c#L2095">2095</a>                         <a href="ident?i=limit">limit</a> = <a href="ident?i=tcp_mss_split_point">tcp_mss_split_point</a>(sk, <a href="ident?i=skb">skb</a>, mss_now,
<a name="L2096" href="source/net/ipv4/tcp_output.c#L2096">2096</a>                                                     <a href="ident?i=min_t">min_t</a>(unsigned int,
<a name="L2097" href="source/net/ipv4/tcp_output.c#L2097">2097</a>                                                           cwnd_quota,
<a name="L2098" href="source/net/ipv4/tcp_output.c#L2098">2098</a>                                                           max_segs),
<a name="L2099" href="source/net/ipv4/tcp_output.c#L2099">2099</a>                                                     nonagle);
<a name="L2100" href="source/net/ipv4/tcp_output.c#L2100">2100</a> 
<a name="L2101" href="source/net/ipv4/tcp_output.c#L2101">2101</a>                 if (<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a> &gt; <a href="ident?i=limit">limit</a> &amp;&amp;
<a name="L2102" href="source/net/ipv4/tcp_output.c#L2102">2102</a>                     <a href="ident?i=unlikely">unlikely</a>(<a href="ident?i=tso_fragment">tso_fragment</a>(sk, <a href="ident?i=skb">skb</a>, <a href="ident?i=limit">limit</a>, mss_now, gfp)))
<a name="L2103" href="source/net/ipv4/tcp_output.c#L2103">2103</a>                         break;
<a name="L2104" href="source/net/ipv4/tcp_output.c#L2104">2104</a> 
<a name="L2105" href="source/net/ipv4/tcp_output.c#L2105">2105</a>                 <b><i>/* TCP Small Queues :</i></b>
<a name="L2106" href="source/net/ipv4/tcp_output.c#L2106">2106</a> <b><i>                 * Control number of packets in qdisc/devices to two packets / or ~1 ms.</i></b>
<a name="L2107" href="source/net/ipv4/tcp_output.c#L2107">2107</a> <b><i>                 * This allows for :</i></b>
<a name="L2108" href="source/net/ipv4/tcp_output.c#L2108">2108</a> <b><i>                 *  - better RTT estimation and ACK scheduling</i></b>
<a name="L2109" href="source/net/ipv4/tcp_output.c#L2109">2109</a> <b><i>                 *  - faster recovery</i></b>
<a name="L2110" href="source/net/ipv4/tcp_output.c#L2110">2110</a> <b><i>                 *  - high rates</i></b>
<a name="L2111" href="source/net/ipv4/tcp_output.c#L2111">2111</a> <b><i>                 * Alas, some drivers / subsystems require a fair amount</i></b>
<a name="L2112" href="source/net/ipv4/tcp_output.c#L2112">2112</a> <b><i>                 * of queued bytes to ensure line rate.</i></b>
<a name="L2113" href="source/net/ipv4/tcp_output.c#L2113">2113</a> <b><i>                 * One example is wifi aggregation (802.11 AMPDU)</i></b>
<a name="L2114" href="source/net/ipv4/tcp_output.c#L2114">2114</a> <b><i>                 */</i></b>
<a name="L2115" href="source/net/ipv4/tcp_output.c#L2115">2115</a>                 <a href="ident?i=limit">limit</a> = <a href="ident?i=max">max</a>(2 * <a href="ident?i=skb">skb</a>-&gt;truesize, sk-&gt;sk_pacing_rate &gt;&gt; 10);
<a name="L2116" href="source/net/ipv4/tcp_output.c#L2116">2116</a>                 <a href="ident?i=limit">limit</a> = <a href="ident?i=min_t">min_t</a>(<a href="ident?i=u32">u32</a>, <a href="ident?i=limit">limit</a>, <a href="ident?i=sysctl_tcp_limit_output_bytes">sysctl_tcp_limit_output_bytes</a>);
<a name="L2117" href="source/net/ipv4/tcp_output.c#L2117">2117</a> 
<a name="L2118" href="source/net/ipv4/tcp_output.c#L2118">2118</a>                 if (<a href="ident?i=atomic_read">atomic_read</a>(&amp;sk-&gt;sk_wmem_alloc) &gt; <a href="ident?i=limit">limit</a>) {
<a name="L2119" href="source/net/ipv4/tcp_output.c#L2119">2119</a>                         <a href="ident?i=set_bit">set_bit</a>(TSQ_THROTTLED, &amp;<a href="ident?i=tp">tp</a>-&gt;<a href="ident?i=tsq_flags">tsq_flags</a>);
<a name="L2120" href="source/net/ipv4/tcp_output.c#L2120">2120</a>                         <b><i>/* It is possible TX completion already happened</i></b>
<a name="L2121" href="source/net/ipv4/tcp_output.c#L2121">2121</a> <b><i>                         * before we set TSQ_THROTTLED, so we must</i></b>
<a name="L2122" href="source/net/ipv4/tcp_output.c#L2122">2122</a> <b><i>                         * test again the condition.</i></b>
<a name="L2123" href="source/net/ipv4/tcp_output.c#L2123">2123</a> <b><i>                         */</i></b>
<a name="L2124" href="source/net/ipv4/tcp_output.c#L2124">2124</a>                         <a href="ident?i=smp_mb__after_atomic">smp_mb__after_atomic</a>();
<a name="L2125" href="source/net/ipv4/tcp_output.c#L2125">2125</a>                         if (<a href="ident?i=atomic_read">atomic_read</a>(&amp;sk-&gt;sk_wmem_alloc) &gt; <a href="ident?i=limit">limit</a>)
<a name="L2126" href="source/net/ipv4/tcp_output.c#L2126">2126</a>                                 break;
<a name="L2127" href="source/net/ipv4/tcp_output.c#L2127">2127</a>                 }
<a name="L2128" href="source/net/ipv4/tcp_output.c#L2128">2128</a> 
<a name="L2129" href="source/net/ipv4/tcp_output.c#L2129">2129</a>                 if (<a href="ident?i=unlikely">unlikely</a>(<a href="ident?i=tcp_transmit_skb">tcp_transmit_skb</a>(sk, <a href="ident?i=skb">skb</a>, 1, gfp)))
<a name="L2130" href="source/net/ipv4/tcp_output.c#L2130">2130</a>                         break;
<a name="L2131" href="source/net/ipv4/tcp_output.c#L2131">2131</a> 
<a name="L2132" href="source/net/ipv4/tcp_output.c#L2132">2132</a> repair:
<a name="L2133" href="source/net/ipv4/tcp_output.c#L2133">2133</a>                 <b><i>/* Advance the send_head.  This one is sent out.</i></b>
<a name="L2134" href="source/net/ipv4/tcp_output.c#L2134">2134</a> <b><i>                 * This call will increment packets_out.</i></b>
<a name="L2135" href="source/net/ipv4/tcp_output.c#L2135">2135</a> <b><i>                 */</i></b>
<a name="L2136" href="source/net/ipv4/tcp_output.c#L2136">2136</a>                 <a href="ident?i=tcp_event_new_data_sent">tcp_event_new_data_sent</a>(sk, <a href="ident?i=skb">skb</a>);
<a name="L2137" href="source/net/ipv4/tcp_output.c#L2137">2137</a> 
<a name="L2138" href="source/net/ipv4/tcp_output.c#L2138">2138</a>                 <a href="ident?i=tcp_minshall_update">tcp_minshall_update</a>(<a href="ident?i=tp">tp</a>, mss_now, <a href="ident?i=skb">skb</a>);
<a name="L2139" href="source/net/ipv4/tcp_output.c#L2139">2139</a>                 sent_pkts += <a href="ident?i=tcp_skb_pcount">tcp_skb_pcount</a>(<a href="ident?i=skb">skb</a>);
<a name="L2140" href="source/net/ipv4/tcp_output.c#L2140">2140</a> 
<a name="L2141" href="source/net/ipv4/tcp_output.c#L2141">2141</a>                 if (push_one)
<a name="L2142" href="source/net/ipv4/tcp_output.c#L2142">2142</a>                         break;
<a name="L2143" href="source/net/ipv4/tcp_output.c#L2143">2143</a>         }
<a name="L2144" href="source/net/ipv4/tcp_output.c#L2144">2144</a> 
<a name="L2145" href="source/net/ipv4/tcp_output.c#L2145">2145</a>         if (<a href="ident?i=likely">likely</a>(sent_pkts)) {
<a name="L2146" href="source/net/ipv4/tcp_output.c#L2146">2146</a>                 if (<a href="ident?i=tcp_in_cwnd_reduction">tcp_in_cwnd_reduction</a>(sk))
<a name="L2147" href="source/net/ipv4/tcp_output.c#L2147">2147</a>                         <a href="ident?i=tp">tp</a>-&gt;prr_out += sent_pkts;
<a name="L2148" href="source/net/ipv4/tcp_output.c#L2148">2148</a> 
<a name="L2149" href="source/net/ipv4/tcp_output.c#L2149">2149</a>                 <b><i>/* Send one loss probe per tail loss episode. */</i></b>
<a name="L2150" href="source/net/ipv4/tcp_output.c#L2150">2150</a>                 if (push_one != 2)
<a name="L2151" href="source/net/ipv4/tcp_output.c#L2151">2151</a>                         <a href="ident?i=tcp_schedule_loss_probe">tcp_schedule_loss_probe</a>(sk);
<a name="L2152" href="source/net/ipv4/tcp_output.c#L2152">2152</a>                 <a href="ident?i=tcp_cwnd_validate">tcp_cwnd_validate</a>(sk, is_cwnd_limited);
<a name="L2153" href="source/net/ipv4/tcp_output.c#L2153">2153</a>                 return <a href="ident?i=false">false</a>;
<a name="L2154" href="source/net/ipv4/tcp_output.c#L2154">2154</a>         }
<a name="L2155" href="source/net/ipv4/tcp_output.c#L2155">2155</a>         return (push_one == 2) || (!<a href="ident?i=tp">tp</a>-&gt;packets_out &amp;&amp; <a href="ident?i=tcp_send_head">tcp_send_head</a>(sk));
<a name="L2156" href="source/net/ipv4/tcp_output.c#L2156">2156</a> }
<a name="L2157" href="source/net/ipv4/tcp_output.c#L2157">2157</a> 
<a name="L2158" href="source/net/ipv4/tcp_output.c#L2158">2158</a> <a href="ident?i=bool">bool</a> <a href="ident?i=tcp_schedule_loss_probe">tcp_schedule_loss_probe</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L2159" href="source/net/ipv4/tcp_output.c#L2159">2159</a> {
<a name="L2160" href="source/net/ipv4/tcp_output.c#L2160">2160</a>         struct <a href="ident?i=inet_connection_sock">inet_connection_sock</a> *icsk = <a href="ident?i=inet_csk">inet_csk</a>(sk);
<a name="L2161" href="source/net/ipv4/tcp_output.c#L2161">2161</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L2162" href="source/net/ipv4/tcp_output.c#L2162">2162</a>         <a href="ident?i=u32">u32</a> <a href="ident?i=timeout">timeout</a>, tlp_time_stamp, rto_time_stamp;
<a name="L2163" href="source/net/ipv4/tcp_output.c#L2163">2163</a>         <a href="ident?i=u32">u32</a> rtt = <a href="ident?i=usecs_to_jiffies">usecs_to_jiffies</a>(<a href="ident?i=tp">tp</a>-&gt;srtt_us &gt;&gt; 3);
<a name="L2164" href="source/net/ipv4/tcp_output.c#L2164">2164</a> 
<a name="L2165" href="source/net/ipv4/tcp_output.c#L2165">2165</a>         if (<a href="ident?i=WARN_ON">WARN_ON</a>(icsk-&gt;icsk_pending == <a href="ident?i=ICSK_TIME_EARLY_RETRANS">ICSK_TIME_EARLY_RETRANS</a>))
<a name="L2166" href="source/net/ipv4/tcp_output.c#L2166">2166</a>                 return <a href="ident?i=false">false</a>;
<a name="L2167" href="source/net/ipv4/tcp_output.c#L2167">2167</a>         <b><i>/* No consecutive loss probes. */</i></b>
<a name="L2168" href="source/net/ipv4/tcp_output.c#L2168">2168</a>         if (<a href="ident?i=WARN_ON">WARN_ON</a>(icsk-&gt;icsk_pending == <a href="ident?i=ICSK_TIME_LOSS_PROBE">ICSK_TIME_LOSS_PROBE</a>)) {
<a name="L2169" href="source/net/ipv4/tcp_output.c#L2169">2169</a>                 <a href="ident?i=tcp_rearm_rto">tcp_rearm_rto</a>(sk);
<a name="L2170" href="source/net/ipv4/tcp_output.c#L2170">2170</a>                 return <a href="ident?i=false">false</a>;
<a name="L2171" href="source/net/ipv4/tcp_output.c#L2171">2171</a>         }
<a name="L2172" href="source/net/ipv4/tcp_output.c#L2172">2172</a>         <b><i>/* Don't do any loss probe on a Fast Open connection before 3WHS</i></b>
<a name="L2173" href="source/net/ipv4/tcp_output.c#L2173">2173</a> <b><i>         * finishes.</i></b>
<a name="L2174" href="source/net/ipv4/tcp_output.c#L2174">2174</a> <b><i>         */</i></b>
<a name="L2175" href="source/net/ipv4/tcp_output.c#L2175">2175</a>         if (sk-&gt;<a href="ident?i=sk_state">sk_state</a> == TCP_SYN_RECV)
<a name="L2176" href="source/net/ipv4/tcp_output.c#L2176">2176</a>                 return <a href="ident?i=false">false</a>;
<a name="L2177" href="source/net/ipv4/tcp_output.c#L2177">2177</a> 
<a name="L2178" href="source/net/ipv4/tcp_output.c#L2178">2178</a>         <b><i>/* TLP is only scheduled when next timer event is RTO. */</i></b>
<a name="L2179" href="source/net/ipv4/tcp_output.c#L2179">2179</a>         if (icsk-&gt;icsk_pending != <a href="ident?i=ICSK_TIME_RETRANS">ICSK_TIME_RETRANS</a>)
<a name="L2180" href="source/net/ipv4/tcp_output.c#L2180">2180</a>                 return <a href="ident?i=false">false</a>;
<a name="L2181" href="source/net/ipv4/tcp_output.c#L2181">2181</a> 
<a name="L2182" href="source/net/ipv4/tcp_output.c#L2182">2182</a>         <b><i>/* Schedule a loss probe in 2*RTT for SACK capable connections</i></b>
<a name="L2183" href="source/net/ipv4/tcp_output.c#L2183">2183</a> <b><i>         * in Open state, that are either limited by cwnd or application.</i></b>
<a name="L2184" href="source/net/ipv4/tcp_output.c#L2184">2184</a> <b><i>         */</i></b>
<a name="L2185" href="source/net/ipv4/tcp_output.c#L2185">2185</a>         if (<a href="ident?i=sysctl_tcp_early_retrans">sysctl_tcp_early_retrans</a> &lt; 3 || !<a href="ident?i=tp">tp</a>-&gt;srtt_us || !<a href="ident?i=tp">tp</a>-&gt;packets_out ||
<a name="L2186" href="source/net/ipv4/tcp_output.c#L2186">2186</a>             !<a href="ident?i=tcp_is_sack">tcp_is_sack</a>(<a href="ident?i=tp">tp</a>) || <a href="ident?i=inet_csk">inet_csk</a>(sk)-&gt;icsk_ca_state != TCP_CA_Open)
<a name="L2187" href="source/net/ipv4/tcp_output.c#L2187">2187</a>                 return <a href="ident?i=false">false</a>;
<a name="L2188" href="source/net/ipv4/tcp_output.c#L2188">2188</a> 
<a name="L2189" href="source/net/ipv4/tcp_output.c#L2189">2189</a>         if ((<a href="ident?i=tp">tp</a>-&gt;snd_cwnd &gt; <a href="ident?i=tcp_packets_in_flight">tcp_packets_in_flight</a>(<a href="ident?i=tp">tp</a>)) &amp;&amp;
<a name="L2190" href="source/net/ipv4/tcp_output.c#L2190">2190</a>              <a href="ident?i=tcp_send_head">tcp_send_head</a>(sk))
<a name="L2191" href="source/net/ipv4/tcp_output.c#L2191">2191</a>                 return <a href="ident?i=false">false</a>;
<a name="L2192" href="source/net/ipv4/tcp_output.c#L2192">2192</a> 
<a name="L2193" href="source/net/ipv4/tcp_output.c#L2193">2193</a>         <b><i>/* Probe timeout is at least 1.5*rtt + TCP_DELACK_MAX to account</i></b>
<a name="L2194" href="source/net/ipv4/tcp_output.c#L2194">2194</a> <b><i>         * for delayed ack when there's one outstanding packet.</i></b>
<a name="L2195" href="source/net/ipv4/tcp_output.c#L2195">2195</a> <b><i>         */</i></b>
<a name="L2196" href="source/net/ipv4/tcp_output.c#L2196">2196</a>         <a href="ident?i=timeout">timeout</a> = rtt &lt;&lt; 1;
<a name="L2197" href="source/net/ipv4/tcp_output.c#L2197">2197</a>         if (<a href="ident?i=tp">tp</a>-&gt;packets_out == 1)
<a name="L2198" href="source/net/ipv4/tcp_output.c#L2198">2198</a>                 <a href="ident?i=timeout">timeout</a> = <a href="ident?i=max_t">max_t</a>(<a href="ident?i=u32">u32</a>, <a href="ident?i=timeout">timeout</a>,
<a name="L2199" href="source/net/ipv4/tcp_output.c#L2199">2199</a>                                 (rtt + (rtt &gt;&gt; 1) + <a href="ident?i=TCP_DELACK_MAX">TCP_DELACK_MAX</a>));
<a name="L2200" href="source/net/ipv4/tcp_output.c#L2200">2200</a>         <a href="ident?i=timeout">timeout</a> = <a href="ident?i=max_t">max_t</a>(<a href="ident?i=u32">u32</a>, <a href="ident?i=timeout">timeout</a>, <a href="ident?i=msecs_to_jiffies">msecs_to_jiffies</a>(10));
<a name="L2201" href="source/net/ipv4/tcp_output.c#L2201">2201</a> 
<a name="L2202" href="source/net/ipv4/tcp_output.c#L2202">2202</a>         <b><i>/* If RTO is shorter, just schedule TLP in its place. */</i></b>
<a name="L2203" href="source/net/ipv4/tcp_output.c#L2203">2203</a>         tlp_time_stamp = <a href="ident?i=tcp_time_stamp">tcp_time_stamp</a> + <a href="ident?i=timeout">timeout</a>;
<a name="L2204" href="source/net/ipv4/tcp_output.c#L2204">2204</a>         rto_time_stamp = (<a href="ident?i=u32">u32</a>)<a href="ident?i=inet_csk">inet_csk</a>(sk)-&gt;icsk_timeout;
<a name="L2205" href="source/net/ipv4/tcp_output.c#L2205">2205</a>         if ((<a href="ident?i=s32">s32</a>)(tlp_time_stamp - rto_time_stamp) &gt; 0) {
<a name="L2206" href="source/net/ipv4/tcp_output.c#L2206">2206</a>                 <a href="ident?i=s32">s32</a> <a href="ident?i=delta">delta</a> = rto_time_stamp - <a href="ident?i=tcp_time_stamp">tcp_time_stamp</a>;
<a name="L2207" href="source/net/ipv4/tcp_output.c#L2207">2207</a>                 if (<a href="ident?i=delta">delta</a> &gt; 0)
<a name="L2208" href="source/net/ipv4/tcp_output.c#L2208">2208</a>                         <a href="ident?i=timeout">timeout</a> = <a href="ident?i=delta">delta</a>;
<a name="L2209" href="source/net/ipv4/tcp_output.c#L2209">2209</a>         }
<a name="L2210" href="source/net/ipv4/tcp_output.c#L2210">2210</a> 
<a name="L2211" href="source/net/ipv4/tcp_output.c#L2211">2211</a>         <a href="ident?i=inet_csk_reset_xmit_timer">inet_csk_reset_xmit_timer</a>(sk, <a href="ident?i=ICSK_TIME_LOSS_PROBE">ICSK_TIME_LOSS_PROBE</a>, <a href="ident?i=timeout">timeout</a>,
<a name="L2212" href="source/net/ipv4/tcp_output.c#L2212">2212</a>                                   <a href="ident?i=TCP_RTO_MAX">TCP_RTO_MAX</a>);
<a name="L2213" href="source/net/ipv4/tcp_output.c#L2213">2213</a>         return <a href="ident?i=true">true</a>;
<a name="L2214" href="source/net/ipv4/tcp_output.c#L2214">2214</a> }
<a name="L2215" href="source/net/ipv4/tcp_output.c#L2215">2215</a> 
<a name="L2216" href="source/net/ipv4/tcp_output.c#L2216">2216</a> <b><i>/* Thanks to skb fast clones, we can detect if a prior transmit of</i></b>
<a name="L2217" href="source/net/ipv4/tcp_output.c#L2217">2217</a> <b><i> * a packet is still in a qdisc or driver queue.</i></b>
<a name="L2218" href="source/net/ipv4/tcp_output.c#L2218">2218</a> <b><i> * In this case, there is very little point doing a retransmit !</i></b>
<a name="L2219" href="source/net/ipv4/tcp_output.c#L2219">2219</a> <b><i> * Note: This is called from BH context only.</i></b>
<a name="L2220" href="source/net/ipv4/tcp_output.c#L2220">2220</a> <b><i> */</i></b>
<a name="L2221" href="source/net/ipv4/tcp_output.c#L2221">2221</a> static <a href="ident?i=bool">bool</a> <a href="ident?i=skb_still_in_host_queue">skb_still_in_host_queue</a>(const struct <a href="ident?i=sock">sock</a> *sk,
<a name="L2222" href="source/net/ipv4/tcp_output.c#L2222">2222</a>                                     const struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L2223" href="source/net/ipv4/tcp_output.c#L2223">2223</a> {
<a name="L2224" href="source/net/ipv4/tcp_output.c#L2224">2224</a>         if (<a href="ident?i=unlikely">unlikely</a>(<a href="ident?i=skb_fclone_busy">skb_fclone_busy</a>(sk, <a href="ident?i=skb">skb</a>))) {
<a name="L2225" href="source/net/ipv4/tcp_output.c#L2225">2225</a>                 <a href="ident?i=NET_INC_STATS_BH">NET_INC_STATS_BH</a>(<a href="ident?i=sock_net">sock_net</a>(sk),
<a name="L2226" href="source/net/ipv4/tcp_output.c#L2226">2226</a>                                  LINUX_MIB_TCPSPURIOUS_RTX_HOSTQUEUES);
<a name="L2227" href="source/net/ipv4/tcp_output.c#L2227">2227</a>                 return <a href="ident?i=true">true</a>;
<a name="L2228" href="source/net/ipv4/tcp_output.c#L2228">2228</a>         }
<a name="L2229" href="source/net/ipv4/tcp_output.c#L2229">2229</a>         return <a href="ident?i=false">false</a>;
<a name="L2230" href="source/net/ipv4/tcp_output.c#L2230">2230</a> }
<a name="L2231" href="source/net/ipv4/tcp_output.c#L2231">2231</a> 
<a name="L2232" href="source/net/ipv4/tcp_output.c#L2232">2232</a> <b><i>/* When probe timeout (PTO) fires, send a new segment if one exists, else</i></b>
<a name="L2233" href="source/net/ipv4/tcp_output.c#L2233">2233</a> <b><i> * retransmit the last segment.</i></b>
<a name="L2234" href="source/net/ipv4/tcp_output.c#L2234">2234</a> <b><i> */</i></b>
<a name="L2235" href="source/net/ipv4/tcp_output.c#L2235">2235</a> void <a href="ident?i=tcp_send_loss_probe">tcp_send_loss_probe</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L2236" href="source/net/ipv4/tcp_output.c#L2236">2236</a> {
<a name="L2237" href="source/net/ipv4/tcp_output.c#L2237">2237</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L2238" href="source/net/ipv4/tcp_output.c#L2238">2238</a>         struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>;
<a name="L2239" href="source/net/ipv4/tcp_output.c#L2239">2239</a>         int pcount;
<a name="L2240" href="source/net/ipv4/tcp_output.c#L2240">2240</a>         int mss = <a href="ident?i=tcp_current_mss">tcp_current_mss</a>(sk);
<a name="L2241" href="source/net/ipv4/tcp_output.c#L2241">2241</a>         int <a href="ident?i=err">err</a> = -1;
<a name="L2242" href="source/net/ipv4/tcp_output.c#L2242">2242</a> 
<a name="L2243" href="source/net/ipv4/tcp_output.c#L2243">2243</a>         if (<a href="ident?i=tcp_send_head">tcp_send_head</a>(sk)) {
<a name="L2244" href="source/net/ipv4/tcp_output.c#L2244">2244</a>                 <a href="ident?i=err">err</a> = <a href="ident?i=tcp_write_xmit">tcp_write_xmit</a>(sk, mss, <a href="ident?i=TCP_NAGLE_OFF">TCP_NAGLE_OFF</a>, 2, <a href="ident?i=GFP_ATOMIC">GFP_ATOMIC</a>);
<a name="L2245" href="source/net/ipv4/tcp_output.c#L2245">2245</a>                 goto rearm_timer;
<a name="L2246" href="source/net/ipv4/tcp_output.c#L2246">2246</a>         }
<a name="L2247" href="source/net/ipv4/tcp_output.c#L2247">2247</a> 
<a name="L2248" href="source/net/ipv4/tcp_output.c#L2248">2248</a>         <b><i>/* At most one outstanding TLP retransmission. */</i></b>
<a name="L2249" href="source/net/ipv4/tcp_output.c#L2249">2249</a>         if (<a href="ident?i=tp">tp</a>-&gt;tlp_high_seq)
<a name="L2250" href="source/net/ipv4/tcp_output.c#L2250">2250</a>                 goto rearm_timer;
<a name="L2251" href="source/net/ipv4/tcp_output.c#L2251">2251</a> 
<a name="L2252" href="source/net/ipv4/tcp_output.c#L2252">2252</a>         <b><i>/* Retransmit last segment. */</i></b>
<a name="L2253" href="source/net/ipv4/tcp_output.c#L2253">2253</a>         <a href="ident?i=skb">skb</a> = <a href="ident?i=tcp_write_queue_tail">tcp_write_queue_tail</a>(sk);
<a name="L2254" href="source/net/ipv4/tcp_output.c#L2254">2254</a>         if (<a href="ident?i=WARN_ON">WARN_ON</a>(!<a href="ident?i=skb">skb</a>))
<a name="L2255" href="source/net/ipv4/tcp_output.c#L2255">2255</a>                 goto rearm_timer;
<a name="L2256" href="source/net/ipv4/tcp_output.c#L2256">2256</a> 
<a name="L2257" href="source/net/ipv4/tcp_output.c#L2257">2257</a>         if (<a href="ident?i=skb_still_in_host_queue">skb_still_in_host_queue</a>(sk, <a href="ident?i=skb">skb</a>))
<a name="L2258" href="source/net/ipv4/tcp_output.c#L2258">2258</a>                 goto rearm_timer;
<a name="L2259" href="source/net/ipv4/tcp_output.c#L2259">2259</a> 
<a name="L2260" href="source/net/ipv4/tcp_output.c#L2260">2260</a>         pcount = <a href="ident?i=tcp_skb_pcount">tcp_skb_pcount</a>(<a href="ident?i=skb">skb</a>);
<a name="L2261" href="source/net/ipv4/tcp_output.c#L2261">2261</a>         if (<a href="ident?i=WARN_ON">WARN_ON</a>(!pcount))
<a name="L2262" href="source/net/ipv4/tcp_output.c#L2262">2262</a>                 goto rearm_timer;
<a name="L2263" href="source/net/ipv4/tcp_output.c#L2263">2263</a> 
<a name="L2264" href="source/net/ipv4/tcp_output.c#L2264">2264</a>         if ((pcount &gt; 1) &amp;&amp; (<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a> &gt; (pcount - 1) * mss)) {
<a name="L2265" href="source/net/ipv4/tcp_output.c#L2265">2265</a>                 if (<a href="ident?i=unlikely">unlikely</a>(<a href="ident?i=tcp_fragment">tcp_fragment</a>(sk, <a href="ident?i=skb">skb</a>, (pcount - 1) * mss, mss,
<a name="L2266" href="source/net/ipv4/tcp_output.c#L2266">2266</a>                                           <a href="ident?i=GFP_ATOMIC">GFP_ATOMIC</a>)))
<a name="L2267" href="source/net/ipv4/tcp_output.c#L2267">2267</a>                         goto rearm_timer;
<a name="L2268" href="source/net/ipv4/tcp_output.c#L2268">2268</a>                 <a href="ident?i=skb">skb</a> = <a href="ident?i=tcp_write_queue_tail">tcp_write_queue_tail</a>(sk);
<a name="L2269" href="source/net/ipv4/tcp_output.c#L2269">2269</a>         }
<a name="L2270" href="source/net/ipv4/tcp_output.c#L2270">2270</a> 
<a name="L2271" href="source/net/ipv4/tcp_output.c#L2271">2271</a>         if (<a href="ident?i=WARN_ON">WARN_ON</a>(!<a href="ident?i=skb">skb</a> || !<a href="ident?i=tcp_skb_pcount">tcp_skb_pcount</a>(<a href="ident?i=skb">skb</a>)))
<a name="L2272" href="source/net/ipv4/tcp_output.c#L2272">2272</a>                 goto rearm_timer;
<a name="L2273" href="source/net/ipv4/tcp_output.c#L2273">2273</a> 
<a name="L2274" href="source/net/ipv4/tcp_output.c#L2274">2274</a>         <a href="ident?i=err">err</a> = <a href="ident?i=__tcp_retransmit_skb">__tcp_retransmit_skb</a>(sk, <a href="ident?i=skb">skb</a>);
<a name="L2275" href="source/net/ipv4/tcp_output.c#L2275">2275</a> 
<a name="L2276" href="source/net/ipv4/tcp_output.c#L2276">2276</a>         <b><i>/* Record snd_nxt for loss detection. */</i></b>
<a name="L2277" href="source/net/ipv4/tcp_output.c#L2277">2277</a>         if (<a href="ident?i=likely">likely</a>(!<a href="ident?i=err">err</a>))
<a name="L2278" href="source/net/ipv4/tcp_output.c#L2278">2278</a>                 <a href="ident?i=tp">tp</a>-&gt;tlp_high_seq = <a href="ident?i=tp">tp</a>-&gt;snd_nxt;
<a name="L2279" href="source/net/ipv4/tcp_output.c#L2279">2279</a> 
<a name="L2280" href="source/net/ipv4/tcp_output.c#L2280">2280</a> rearm_timer:
<a name="L2281" href="source/net/ipv4/tcp_output.c#L2281">2281</a>         <a href="ident?i=inet_csk_reset_xmit_timer">inet_csk_reset_xmit_timer</a>(sk, <a href="ident?i=ICSK_TIME_RETRANS">ICSK_TIME_RETRANS</a>,
<a name="L2282" href="source/net/ipv4/tcp_output.c#L2282">2282</a>                                   <a href="ident?i=inet_csk">inet_csk</a>(sk)-&gt;icsk_rto,
<a name="L2283" href="source/net/ipv4/tcp_output.c#L2283">2283</a>                                   <a href="ident?i=TCP_RTO_MAX">TCP_RTO_MAX</a>);
<a name="L2284" href="source/net/ipv4/tcp_output.c#L2284">2284</a> 
<a name="L2285" href="source/net/ipv4/tcp_output.c#L2285">2285</a>         if (<a href="ident?i=likely">likely</a>(!<a href="ident?i=err">err</a>))
<a name="L2286" href="source/net/ipv4/tcp_output.c#L2286">2286</a>                 <a href="ident?i=NET_INC_STATS_BH">NET_INC_STATS_BH</a>(<a href="ident?i=sock_net">sock_net</a>(sk),
<a name="L2287" href="source/net/ipv4/tcp_output.c#L2287">2287</a>                                  LINUX_MIB_TCPLOSSPROBES);
<a name="L2288" href="source/net/ipv4/tcp_output.c#L2288">2288</a> }
<a name="L2289" href="source/net/ipv4/tcp_output.c#L2289">2289</a> 
<a name="L2290" href="source/net/ipv4/tcp_output.c#L2290">2290</a> <b><i>/* Push out any pending frames which were held back due to</i></b>
<a name="L2291" href="source/net/ipv4/tcp_output.c#L2291">2291</a> <b><i> * TCP_CORK or attempt at coalescing tiny packets.</i></b>
<a name="L2292" href="source/net/ipv4/tcp_output.c#L2292">2292</a> <b><i> * The socket must be locked by the caller.</i></b>
<a name="L2293" href="source/net/ipv4/tcp_output.c#L2293">2293</a> <b><i> */</i></b>
<a name="L2294" href="source/net/ipv4/tcp_output.c#L2294">2294</a> void <a href="ident?i=__tcp_push_pending_frames">__tcp_push_pending_frames</a>(struct <a href="ident?i=sock">sock</a> *sk, unsigned int cur_mss,
<a name="L2295" href="source/net/ipv4/tcp_output.c#L2295">2295</a>                                int nonagle)
<a name="L2296" href="source/net/ipv4/tcp_output.c#L2296">2296</a> {
<a name="L2297" href="source/net/ipv4/tcp_output.c#L2297">2297</a>         <b><i>/* If we are closed, the bytes will have to remain here.</i></b>
<a name="L2298" href="source/net/ipv4/tcp_output.c#L2298">2298</a> <b><i>         * In time closedown will finish, we empty the write queue and</i></b>
<a name="L2299" href="source/net/ipv4/tcp_output.c#L2299">2299</a> <b><i>         * all will be happy.</i></b>
<a name="L2300" href="source/net/ipv4/tcp_output.c#L2300">2300</a> <b><i>         */</i></b>
<a name="L2301" href="source/net/ipv4/tcp_output.c#L2301">2301</a>         if (<a href="ident?i=unlikely">unlikely</a>(sk-&gt;<a href="ident?i=sk_state">sk_state</a> == TCP_CLOSE))
<a name="L2302" href="source/net/ipv4/tcp_output.c#L2302">2302</a>                 return;
<a name="L2303" href="source/net/ipv4/tcp_output.c#L2303">2303</a> 
<a name="L2304" href="source/net/ipv4/tcp_output.c#L2304">2304</a>         if (<a href="ident?i=tcp_write_xmit">tcp_write_xmit</a>(sk, cur_mss, nonagle, 0,
<a name="L2305" href="source/net/ipv4/tcp_output.c#L2305">2305</a>                            <a href="ident?i=sk_gfp_atomic">sk_gfp_atomic</a>(sk, <a href="ident?i=GFP_ATOMIC">GFP_ATOMIC</a>)))
<a name="L2306" href="source/net/ipv4/tcp_output.c#L2306">2306</a>                 <a href="ident?i=tcp_check_probe_timer">tcp_check_probe_timer</a>(sk);
<a name="L2307" href="source/net/ipv4/tcp_output.c#L2307">2307</a> }
<a name="L2308" href="source/net/ipv4/tcp_output.c#L2308">2308</a> 
<a name="L2309" href="source/net/ipv4/tcp_output.c#L2309">2309</a> <b><i>/* Send _single_ skb sitting at the send head. This function requires</i></b>
<a name="L2310" href="source/net/ipv4/tcp_output.c#L2310">2310</a> <b><i> * true push pending frames to setup probe timer etc.</i></b>
<a name="L2311" href="source/net/ipv4/tcp_output.c#L2311">2311</a> <b><i> */</i></b>
<a name="L2312" href="source/net/ipv4/tcp_output.c#L2312">2312</a> void <a href="ident?i=tcp_push_one">tcp_push_one</a>(struct <a href="ident?i=sock">sock</a> *sk, unsigned int mss_now)
<a name="L2313" href="source/net/ipv4/tcp_output.c#L2313">2313</a> {
<a name="L2314" href="source/net/ipv4/tcp_output.c#L2314">2314</a>         struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a> = <a href="ident?i=tcp_send_head">tcp_send_head</a>(sk);
<a name="L2315" href="source/net/ipv4/tcp_output.c#L2315">2315</a> 
<a name="L2316" href="source/net/ipv4/tcp_output.c#L2316">2316</a>         <a href="ident?i=BUG_ON">BUG_ON</a>(!<a href="ident?i=skb">skb</a> || <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a> &lt; mss_now);
<a name="L2317" href="source/net/ipv4/tcp_output.c#L2317">2317</a> 
<a name="L2318" href="source/net/ipv4/tcp_output.c#L2318">2318</a>         <a href="ident?i=tcp_write_xmit">tcp_write_xmit</a>(sk, mss_now, <a href="ident?i=TCP_NAGLE_PUSH">TCP_NAGLE_PUSH</a>, 1, sk-&gt;sk_allocation);
<a name="L2319" href="source/net/ipv4/tcp_output.c#L2319">2319</a> }
<a name="L2320" href="source/net/ipv4/tcp_output.c#L2320">2320</a> 
<a name="L2321" href="source/net/ipv4/tcp_output.c#L2321">2321</a> <b><i>/* This function returns the amount that we can raise the</i></b>
<a name="L2322" href="source/net/ipv4/tcp_output.c#L2322">2322</a> <b><i> * usable window based on the following constraints</i></b>
<a name="L2323" href="source/net/ipv4/tcp_output.c#L2323">2323</a> <b><i> *</i></b>
<a name="L2324" href="source/net/ipv4/tcp_output.c#L2324">2324</a> <b><i> * 1. The window can never be shrunk once it is offered (RFC 793)</i></b>
<a name="L2325" href="source/net/ipv4/tcp_output.c#L2325">2325</a> <b><i> * 2. We limit memory per socket</i></b>
<a name="L2326" href="source/net/ipv4/tcp_output.c#L2326">2326</a> <b><i> *</i></b>
<a name="L2327" href="source/net/ipv4/tcp_output.c#L2327">2327</a> <b><i> * RFC 1122:</i></b>
<a name="L2328" href="source/net/ipv4/tcp_output.c#L2328">2328</a> <b><i> * "the suggested [SWS] avoidance algorithm for the receiver is to keep</i></b>
<a name="L2329" href="source/net/ipv4/tcp_output.c#L2329">2329</a> <b><i> *  RECV.NEXT + RCV.WIN fixed until:</i></b>
<a name="L2330" href="source/net/ipv4/tcp_output.c#L2330">2330</a> <b><i> *  RCV.BUFF - RCV.USER - RCV.WINDOW &gt;= min(1/2 RCV.BUFF, MSS)"</i></b>
<a name="L2331" href="source/net/ipv4/tcp_output.c#L2331">2331</a> <b><i> *</i></b>
<a name="L2332" href="source/net/ipv4/tcp_output.c#L2332">2332</a> <b><i> * i.e. don't raise the right edge of the window until you can raise</i></b>
<a name="L2333" href="source/net/ipv4/tcp_output.c#L2333">2333</a> <b><i> * it at least MSS bytes.</i></b>
<a name="L2334" href="source/net/ipv4/tcp_output.c#L2334">2334</a> <b><i> *</i></b>
<a name="L2335" href="source/net/ipv4/tcp_output.c#L2335">2335</a> <b><i> * Unfortunately, the recommended algorithm breaks header prediction,</i></b>
<a name="L2336" href="source/net/ipv4/tcp_output.c#L2336">2336</a> <b><i> * since header prediction assumes th-&gt;window stays fixed.</i></b>
<a name="L2337" href="source/net/ipv4/tcp_output.c#L2337">2337</a> <b><i> *</i></b>
<a name="L2338" href="source/net/ipv4/tcp_output.c#L2338">2338</a> <b><i> * Strictly speaking, keeping th-&gt;window fixed violates the receiver</i></b>
<a name="L2339" href="source/net/ipv4/tcp_output.c#L2339">2339</a> <b><i> * side SWS prevention criteria. The problem is that under this rule</i></b>
<a name="L2340" href="source/net/ipv4/tcp_output.c#L2340">2340</a> <b><i> * a stream of single byte packets will cause the right side of the</i></b>
<a name="L2341" href="source/net/ipv4/tcp_output.c#L2341">2341</a> <b><i> * window to always advance by a single byte.</i></b>
<a name="L2342" href="source/net/ipv4/tcp_output.c#L2342">2342</a> <b><i> *</i></b>
<a name="L2343" href="source/net/ipv4/tcp_output.c#L2343">2343</a> <b><i> * Of course, if the sender implements sender side SWS prevention</i></b>
<a name="L2344" href="source/net/ipv4/tcp_output.c#L2344">2344</a> <b><i> * then this will not be a problem.</i></b>
<a name="L2345" href="source/net/ipv4/tcp_output.c#L2345">2345</a> <b><i> *</i></b>
<a name="L2346" href="source/net/ipv4/tcp_output.c#L2346">2346</a> <b><i> * BSD seems to make the following compromise:</i></b>
<a name="L2347" href="source/net/ipv4/tcp_output.c#L2347">2347</a> <b><i> *</i></b>
<a name="L2348" href="source/net/ipv4/tcp_output.c#L2348">2348</a> <b><i> *      If the free space is less than the 1/4 of the maximum</i></b>
<a name="L2349" href="source/net/ipv4/tcp_output.c#L2349">2349</a> <b><i> *      space available and the free space is less than 1/2 mss,</i></b>
<a name="L2350" href="source/net/ipv4/tcp_output.c#L2350">2350</a> <b><i> *      then set the window to 0.</i></b>
<a name="L2351" href="source/net/ipv4/tcp_output.c#L2351">2351</a> <b><i> *      [ Actually, bsd uses MSS and 1/4 of maximal _window_ ]</i></b>
<a name="L2352" href="source/net/ipv4/tcp_output.c#L2352">2352</a> <b><i> *      Otherwise, just prevent the window from shrinking</i></b>
<a name="L2353" href="source/net/ipv4/tcp_output.c#L2353">2353</a> <b><i> *      and from being larger than the largest representable value.</i></b>
<a name="L2354" href="source/net/ipv4/tcp_output.c#L2354">2354</a> <b><i> *</i></b>
<a name="L2355" href="source/net/ipv4/tcp_output.c#L2355">2355</a> <b><i> * This prevents incremental opening of the window in the regime</i></b>
<a name="L2356" href="source/net/ipv4/tcp_output.c#L2356">2356</a> <b><i> * where TCP is limited by the speed of the reader side taking</i></b>
<a name="L2357" href="source/net/ipv4/tcp_output.c#L2357">2357</a> <b><i> * data out of the TCP receive queue. It does nothing about</i></b>
<a name="L2358" href="source/net/ipv4/tcp_output.c#L2358">2358</a> <b><i> * those cases where the window is constrained on the sender side</i></b>
<a name="L2359" href="source/net/ipv4/tcp_output.c#L2359">2359</a> <b><i> * because the pipeline is full.</i></b>
<a name="L2360" href="source/net/ipv4/tcp_output.c#L2360">2360</a> <b><i> *</i></b>
<a name="L2361" href="source/net/ipv4/tcp_output.c#L2361">2361</a> <b><i> * BSD also seems to "accidentally" limit itself to windows that are a</i></b>
<a name="L2362" href="source/net/ipv4/tcp_output.c#L2362">2362</a> <b><i> * multiple of MSS, at least until the free space gets quite small.</i></b>
<a name="L2363" href="source/net/ipv4/tcp_output.c#L2363">2363</a> <b><i> * This would appear to be a side effect of the mbuf implementation.</i></b>
<a name="L2364" href="source/net/ipv4/tcp_output.c#L2364">2364</a> <b><i> * Combining these two algorithms results in the observed behavior</i></b>
<a name="L2365" href="source/net/ipv4/tcp_output.c#L2365">2365</a> <b><i> * of having a fixed window size at almost all times.</i></b>
<a name="L2366" href="source/net/ipv4/tcp_output.c#L2366">2366</a> <b><i> *</i></b>
<a name="L2367" href="source/net/ipv4/tcp_output.c#L2367">2367</a> <b><i> * Below we obtain similar behavior by forcing the offered window to</i></b>
<a name="L2368" href="source/net/ipv4/tcp_output.c#L2368">2368</a> <b><i> * a multiple of the mss when it is feasible to do so.</i></b>
<a name="L2369" href="source/net/ipv4/tcp_output.c#L2369">2369</a> <b><i> *</i></b>
<a name="L2370" href="source/net/ipv4/tcp_output.c#L2370">2370</a> <b><i> * Note, we don't "adjust" for TIMESTAMP or SACK option bytes.</i></b>
<a name="L2371" href="source/net/ipv4/tcp_output.c#L2371">2371</a> <b><i> * Regular options like TIMESTAMP are taken into account.</i></b>
<a name="L2372" href="source/net/ipv4/tcp_output.c#L2372">2372</a> <b><i> */</i></b>
<a name="L2373" href="source/net/ipv4/tcp_output.c#L2373">2373</a> <a href="ident?i=u32">u32</a> <a href="ident?i=__tcp_select_window">__tcp_select_window</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L2374" href="source/net/ipv4/tcp_output.c#L2374">2374</a> {
<a name="L2375" href="source/net/ipv4/tcp_output.c#L2375">2375</a>         struct <a href="ident?i=inet_connection_sock">inet_connection_sock</a> *icsk = <a href="ident?i=inet_csk">inet_csk</a>(sk);
<a name="L2376" href="source/net/ipv4/tcp_output.c#L2376">2376</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L2377" href="source/net/ipv4/tcp_output.c#L2377">2377</a>         <b><i>/* MSS for the peer's data.  Previous versions used mss_clamp</i></b>
<a name="L2378" href="source/net/ipv4/tcp_output.c#L2378">2378</a> <b><i>         * here.  I don't know if the value based on our guesses</i></b>
<a name="L2379" href="source/net/ipv4/tcp_output.c#L2379">2379</a> <b><i>         * of peer's MSS is better for the performance.  It's more correct</i></b>
<a name="L2380" href="source/net/ipv4/tcp_output.c#L2380">2380</a> <b><i>         * but may be worse for the performance because of rcv_mss</i></b>
<a name="L2381" href="source/net/ipv4/tcp_output.c#L2381">2381</a> <b><i>         * fluctuations.  --SAW  1998/11/1</i></b>
<a name="L2382" href="source/net/ipv4/tcp_output.c#L2382">2382</a> <b><i>         */</i></b>
<a name="L2383" href="source/net/ipv4/tcp_output.c#L2383">2383</a>         int mss = icsk-&gt;icsk_ack.rcv_mss;
<a name="L2384" href="source/net/ipv4/tcp_output.c#L2384">2384</a>         int free_space = <a href="ident?i=tcp_space">tcp_space</a>(sk);
<a name="L2385" href="source/net/ipv4/tcp_output.c#L2385">2385</a>         int allowed_space = <a href="ident?i=tcp_full_space">tcp_full_space</a>(sk);
<a name="L2386" href="source/net/ipv4/tcp_output.c#L2386">2386</a>         int full_space = <a href="ident?i=min_t">min_t</a>(int, <a href="ident?i=tp">tp</a>-&gt;window_clamp, allowed_space);
<a name="L2387" href="source/net/ipv4/tcp_output.c#L2387">2387</a>         int <a href="ident?i=window">window</a>;
<a name="L2388" href="source/net/ipv4/tcp_output.c#L2388">2388</a> 
<a name="L2389" href="source/net/ipv4/tcp_output.c#L2389">2389</a>         if (mss &gt; full_space)
<a name="L2390" href="source/net/ipv4/tcp_output.c#L2390">2390</a>                 mss = full_space;
<a name="L2391" href="source/net/ipv4/tcp_output.c#L2391">2391</a> 
<a name="L2392" href="source/net/ipv4/tcp_output.c#L2392">2392</a>         if (free_space &lt; (full_space &gt;&gt; 1)) {
<a name="L2393" href="source/net/ipv4/tcp_output.c#L2393">2393</a>                 icsk-&gt;icsk_ack.quick = 0;
<a name="L2394" href="source/net/ipv4/tcp_output.c#L2394">2394</a> 
<a name="L2395" href="source/net/ipv4/tcp_output.c#L2395">2395</a>                 if (<a href="ident?i=sk_under_memory_pressure">sk_under_memory_pressure</a>(sk))
<a name="L2396" href="source/net/ipv4/tcp_output.c#L2396">2396</a>                         <a href="ident?i=tp">tp</a>-&gt;rcv_ssthresh = <a href="ident?i=min">min</a>(<a href="ident?i=tp">tp</a>-&gt;rcv_ssthresh,
<a name="L2397" href="source/net/ipv4/tcp_output.c#L2397">2397</a>                                                4U * <a href="ident?i=tp">tp</a>-&gt;advmss);
<a name="L2398" href="source/net/ipv4/tcp_output.c#L2398">2398</a> 
<a name="L2399" href="source/net/ipv4/tcp_output.c#L2399">2399</a>                 <b><i>/* free_space might become our new window, make sure we don't</i></b>
<a name="L2400" href="source/net/ipv4/tcp_output.c#L2400">2400</a> <b><i>                 * increase it due to wscale.</i></b>
<a name="L2401" href="source/net/ipv4/tcp_output.c#L2401">2401</a> <b><i>                 */</i></b>
<a name="L2402" href="source/net/ipv4/tcp_output.c#L2402">2402</a>                 free_space = <a href="ident?i=round_down">round_down</a>(free_space, 1 &lt;&lt; <a href="ident?i=tp">tp</a>-&gt;rx_opt.rcv_wscale);
<a name="L2403" href="source/net/ipv4/tcp_output.c#L2403">2403</a> 
<a name="L2404" href="source/net/ipv4/tcp_output.c#L2404">2404</a>                 <b><i>/* if free space is less than mss estimate, or is below 1/16th</i></b>
<a name="L2405" href="source/net/ipv4/tcp_output.c#L2405">2405</a> <b><i>                 * of the maximum allowed, try to move to zero-window, else</i></b>
<a name="L2406" href="source/net/ipv4/tcp_output.c#L2406">2406</a> <b><i>                 * tcp_clamp_window() will grow rcv buf up to tcp_rmem[2], and</i></b>
<a name="L2407" href="source/net/ipv4/tcp_output.c#L2407">2407</a> <b><i>                 * new incoming data is dropped due to memory limits.</i></b>
<a name="L2408" href="source/net/ipv4/tcp_output.c#L2408">2408</a> <b><i>                 * With large window, mss test triggers way too late in order</i></b>
<a name="L2409" href="source/net/ipv4/tcp_output.c#L2409">2409</a> <b><i>                 * to announce zero window in time before rmem limit kicks in.</i></b>
<a name="L2410" href="source/net/ipv4/tcp_output.c#L2410">2410</a> <b><i>                 */</i></b>
<a name="L2411" href="source/net/ipv4/tcp_output.c#L2411">2411</a>                 if (free_space &lt; (allowed_space &gt;&gt; 4) || free_space &lt; mss)
<a name="L2412" href="source/net/ipv4/tcp_output.c#L2412">2412</a>                         return 0;
<a name="L2413" href="source/net/ipv4/tcp_output.c#L2413">2413</a>         }
<a name="L2414" href="source/net/ipv4/tcp_output.c#L2414">2414</a> 
<a name="L2415" href="source/net/ipv4/tcp_output.c#L2415">2415</a>         if (free_space &gt; <a href="ident?i=tp">tp</a>-&gt;rcv_ssthresh)
<a name="L2416" href="source/net/ipv4/tcp_output.c#L2416">2416</a>                 free_space = <a href="ident?i=tp">tp</a>-&gt;rcv_ssthresh;
<a name="L2417" href="source/net/ipv4/tcp_output.c#L2417">2417</a> 
<a name="L2418" href="source/net/ipv4/tcp_output.c#L2418">2418</a>         <b><i>/* Don't do rounding if we are using window scaling, since the</i></b>
<a name="L2419" href="source/net/ipv4/tcp_output.c#L2419">2419</a> <b><i>         * scaled window will not line up with the MSS boundary anyway.</i></b>
<a name="L2420" href="source/net/ipv4/tcp_output.c#L2420">2420</a> <b><i>         */</i></b>
<a name="L2421" href="source/net/ipv4/tcp_output.c#L2421">2421</a>         <a href="ident?i=window">window</a> = <a href="ident?i=tp">tp</a>-&gt;rcv_wnd;
<a name="L2422" href="source/net/ipv4/tcp_output.c#L2422">2422</a>         if (<a href="ident?i=tp">tp</a>-&gt;rx_opt.rcv_wscale) {
<a name="L2423" href="source/net/ipv4/tcp_output.c#L2423">2423</a>                 <a href="ident?i=window">window</a> = free_space;
<a name="L2424" href="source/net/ipv4/tcp_output.c#L2424">2424</a> 
<a name="L2425" href="source/net/ipv4/tcp_output.c#L2425">2425</a>                 <b><i>/* Advertise enough space so that it won't get scaled away.</i></b>
<a name="L2426" href="source/net/ipv4/tcp_output.c#L2426">2426</a> <b><i>                 * Import case: prevent zero window announcement if</i></b>
<a name="L2427" href="source/net/ipv4/tcp_output.c#L2427">2427</a> <b><i>                 * 1&lt;&lt;rcv_wscale &gt; mss.</i></b>
<a name="L2428" href="source/net/ipv4/tcp_output.c#L2428">2428</a> <b><i>                 */</i></b>
<a name="L2429" href="source/net/ipv4/tcp_output.c#L2429">2429</a>                 if (((<a href="ident?i=window">window</a> &gt;&gt; <a href="ident?i=tp">tp</a>-&gt;rx_opt.rcv_wscale) &lt;&lt; <a href="ident?i=tp">tp</a>-&gt;rx_opt.rcv_wscale) != <a href="ident?i=window">window</a>)
<a name="L2430" href="source/net/ipv4/tcp_output.c#L2430">2430</a>                         <a href="ident?i=window">window</a> = (((<a href="ident?i=window">window</a> &gt;&gt; <a href="ident?i=tp">tp</a>-&gt;rx_opt.rcv_wscale) + 1)
<a name="L2431" href="source/net/ipv4/tcp_output.c#L2431">2431</a>                                   &lt;&lt; <a href="ident?i=tp">tp</a>-&gt;rx_opt.rcv_wscale);
<a name="L2432" href="source/net/ipv4/tcp_output.c#L2432">2432</a>         } else {
<a name="L2433" href="source/net/ipv4/tcp_output.c#L2433">2433</a>                 <b><i>/* Get the largest window that is a nice multiple of mss.</i></b>
<a name="L2434" href="source/net/ipv4/tcp_output.c#L2434">2434</a> <b><i>                 * Window clamp already applied above.</i></b>
<a name="L2435" href="source/net/ipv4/tcp_output.c#L2435">2435</a> <b><i>                 * If our current window offering is within 1 mss of the</i></b>
<a name="L2436" href="source/net/ipv4/tcp_output.c#L2436">2436</a> <b><i>                 * free space we just keep it. This prevents the divide</i></b>
<a name="L2437" href="source/net/ipv4/tcp_output.c#L2437">2437</a> <b><i>                 * and multiply from happening most of the time.</i></b>
<a name="L2438" href="source/net/ipv4/tcp_output.c#L2438">2438</a> <b><i>                 * We also don't do any window rounding when the free space</i></b>
<a name="L2439" href="source/net/ipv4/tcp_output.c#L2439">2439</a> <b><i>                 * is too small.</i></b>
<a name="L2440" href="source/net/ipv4/tcp_output.c#L2440">2440</a> <b><i>                 */</i></b>
<a name="L2441" href="source/net/ipv4/tcp_output.c#L2441">2441</a>                 if (<a href="ident?i=window">window</a> &lt;= free_space - mss || <a href="ident?i=window">window</a> &gt; free_space)
<a name="L2442" href="source/net/ipv4/tcp_output.c#L2442">2442</a>                         <a href="ident?i=window">window</a> = (free_space / mss) * mss;
<a name="L2443" href="source/net/ipv4/tcp_output.c#L2443">2443</a>                 else if (mss == full_space &amp;&amp;
<a name="L2444" href="source/net/ipv4/tcp_output.c#L2444">2444</a>                          free_space &gt; <a href="ident?i=window">window</a> + (full_space &gt;&gt; 1))
<a name="L2445" href="source/net/ipv4/tcp_output.c#L2445">2445</a>                         <a href="ident?i=window">window</a> = free_space;
<a name="L2446" href="source/net/ipv4/tcp_output.c#L2446">2446</a>         }
<a name="L2447" href="source/net/ipv4/tcp_output.c#L2447">2447</a> 
<a name="L2448" href="source/net/ipv4/tcp_output.c#L2448">2448</a>         return <a href="ident?i=window">window</a>;
<a name="L2449" href="source/net/ipv4/tcp_output.c#L2449">2449</a> }
<a name="L2450" href="source/net/ipv4/tcp_output.c#L2450">2450</a> 
<a name="L2451" href="source/net/ipv4/tcp_output.c#L2451">2451</a> <b><i>/* Collapses two adjacent SKB's during retransmission. */</i></b>
<a name="L2452" href="source/net/ipv4/tcp_output.c#L2452">2452</a> static void <a href="ident?i=tcp_collapse_retrans">tcp_collapse_retrans</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L2453" href="source/net/ipv4/tcp_output.c#L2453">2453</a> {
<a name="L2454" href="source/net/ipv4/tcp_output.c#L2454">2454</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L2455" href="source/net/ipv4/tcp_output.c#L2455">2455</a>         struct <a href="ident?i=sk_buff">sk_buff</a> *next_skb = <a href="ident?i=tcp_write_queue_next">tcp_write_queue_next</a>(sk, <a href="ident?i=skb">skb</a>);
<a name="L2456" href="source/net/ipv4/tcp_output.c#L2456">2456</a>         int skb_size, next_skb_size;
<a name="L2457" href="source/net/ipv4/tcp_output.c#L2457">2457</a> 
<a name="L2458" href="source/net/ipv4/tcp_output.c#L2458">2458</a>         skb_size = <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a>;
<a name="L2459" href="source/net/ipv4/tcp_output.c#L2459">2459</a>         next_skb_size = next_skb-&gt;<a href="ident?i=len">len</a>;
<a name="L2460" href="source/net/ipv4/tcp_output.c#L2460">2460</a> 
<a name="L2461" href="source/net/ipv4/tcp_output.c#L2461">2461</a>         <a href="ident?i=BUG_ON">BUG_ON</a>(<a href="ident?i=tcp_skb_pcount">tcp_skb_pcount</a>(<a href="ident?i=skb">skb</a>) != 1 || <a href="ident?i=tcp_skb_pcount">tcp_skb_pcount</a>(next_skb) != 1);
<a name="L2462" href="source/net/ipv4/tcp_output.c#L2462">2462</a> 
<a name="L2463" href="source/net/ipv4/tcp_output.c#L2463">2463</a>         <a href="ident?i=tcp_highest_sack_combine">tcp_highest_sack_combine</a>(sk, next_skb, <a href="ident?i=skb">skb</a>);
<a name="L2464" href="source/net/ipv4/tcp_output.c#L2464">2464</a> 
<a name="L2465" href="source/net/ipv4/tcp_output.c#L2465">2465</a>         <a href="ident?i=tcp_unlink_write_queue">tcp_unlink_write_queue</a>(next_skb, sk);
<a name="L2466" href="source/net/ipv4/tcp_output.c#L2466">2466</a> 
<a name="L2467" href="source/net/ipv4/tcp_output.c#L2467">2467</a>         <a href="ident?i=skb_copy_from_linear_data">skb_copy_from_linear_data</a>(next_skb, <a href="ident?i=skb_put">skb_put</a>(<a href="ident?i=skb">skb</a>, next_skb_size),
<a name="L2468" href="source/net/ipv4/tcp_output.c#L2468">2468</a>                                   next_skb_size);
<a name="L2469" href="source/net/ipv4/tcp_output.c#L2469">2469</a> 
<a name="L2470" href="source/net/ipv4/tcp_output.c#L2470">2470</a>         if (next_skb-&gt;ip_summed == <a href="ident?i=CHECKSUM_PARTIAL">CHECKSUM_PARTIAL</a>)
<a name="L2471" href="source/net/ipv4/tcp_output.c#L2471">2471</a>                 <a href="ident?i=skb">skb</a>-&gt;ip_summed = <a href="ident?i=CHECKSUM_PARTIAL">CHECKSUM_PARTIAL</a>;
<a name="L2472" href="source/net/ipv4/tcp_output.c#L2472">2472</a> 
<a name="L2473" href="source/net/ipv4/tcp_output.c#L2473">2473</a>         if (<a href="ident?i=skb">skb</a>-&gt;ip_summed != <a href="ident?i=CHECKSUM_PARTIAL">CHECKSUM_PARTIAL</a>)
<a name="L2474" href="source/net/ipv4/tcp_output.c#L2474">2474</a>                 <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=csum">csum</a> = <a href="ident?i=csum_block_add">csum_block_add</a>(<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=csum">csum</a>, next_skb-&gt;<a href="ident?i=csum">csum</a>, skb_size);
<a name="L2475" href="source/net/ipv4/tcp_output.c#L2475">2475</a> 
<a name="L2476" href="source/net/ipv4/tcp_output.c#L2476">2476</a>         <b><i>/* Update sequence range on original skb. */</i></b>
<a name="L2477" href="source/net/ipv4/tcp_output.c#L2477">2477</a>         <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;end_seq = <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(next_skb)-&gt;end_seq;
<a name="L2478" href="source/net/ipv4/tcp_output.c#L2478">2478</a> 
<a name="L2479" href="source/net/ipv4/tcp_output.c#L2479">2479</a>         <b><i>/* Merge over control information. This moves PSH/FIN etc. over */</i></b>
<a name="L2480" href="source/net/ipv4/tcp_output.c#L2480">2480</a>         <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;tcp_flags |= <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(next_skb)-&gt;tcp_flags;
<a name="L2481" href="source/net/ipv4/tcp_output.c#L2481">2481</a> 
<a name="L2482" href="source/net/ipv4/tcp_output.c#L2482">2482</a>         <b><i>/* All done, get rid of second SKB and account for it so</i></b>
<a name="L2483" href="source/net/ipv4/tcp_output.c#L2483">2483</a> <b><i>         * packet counting does not break.</i></b>
<a name="L2484" href="source/net/ipv4/tcp_output.c#L2484">2484</a> <b><i>         */</i></b>
<a name="L2485" href="source/net/ipv4/tcp_output.c#L2485">2485</a>         <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;sacked |= <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(next_skb)-&gt;sacked &amp; <a href="ident?i=TCPCB_EVER_RETRANS">TCPCB_EVER_RETRANS</a>;
<a name="L2486" href="source/net/ipv4/tcp_output.c#L2486">2486</a> 
<a name="L2487" href="source/net/ipv4/tcp_output.c#L2487">2487</a>         <b><i>/* changed transmit queue under us so clear hints */</i></b>
<a name="L2488" href="source/net/ipv4/tcp_output.c#L2488">2488</a>         <a href="ident?i=tcp_clear_retrans_hints_partial">tcp_clear_retrans_hints_partial</a>(<a href="ident?i=tp">tp</a>);
<a name="L2489" href="source/net/ipv4/tcp_output.c#L2489">2489</a>         if (next_skb == <a href="ident?i=tp">tp</a>-&gt;retransmit_skb_hint)
<a name="L2490" href="source/net/ipv4/tcp_output.c#L2490">2490</a>                 <a href="ident?i=tp">tp</a>-&gt;retransmit_skb_hint = <a href="ident?i=skb">skb</a>;
<a name="L2491" href="source/net/ipv4/tcp_output.c#L2491">2491</a> 
<a name="L2492" href="source/net/ipv4/tcp_output.c#L2492">2492</a>         <a href="ident?i=tcp_adjust_pcount">tcp_adjust_pcount</a>(sk, next_skb, <a href="ident?i=tcp_skb_pcount">tcp_skb_pcount</a>(next_skb));
<a name="L2493" href="source/net/ipv4/tcp_output.c#L2493">2493</a> 
<a name="L2494" href="source/net/ipv4/tcp_output.c#L2494">2494</a>         <a href="ident?i=sk_wmem_free_skb">sk_wmem_free_skb</a>(sk, next_skb);
<a name="L2495" href="source/net/ipv4/tcp_output.c#L2495">2495</a> }
<a name="L2496" href="source/net/ipv4/tcp_output.c#L2496">2496</a> 
<a name="L2497" href="source/net/ipv4/tcp_output.c#L2497">2497</a> <b><i>/* Check if coalescing SKBs is legal. */</i></b>
<a name="L2498" href="source/net/ipv4/tcp_output.c#L2498">2498</a> static <a href="ident?i=bool">bool</a> <a href="ident?i=tcp_can_collapse">tcp_can_collapse</a>(const struct <a href="ident?i=sock">sock</a> *sk, const struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L2499" href="source/net/ipv4/tcp_output.c#L2499">2499</a> {
<a name="L2500" href="source/net/ipv4/tcp_output.c#L2500">2500</a>         if (<a href="ident?i=tcp_skb_pcount">tcp_skb_pcount</a>(<a href="ident?i=skb">skb</a>) &gt; 1)
<a name="L2501" href="source/net/ipv4/tcp_output.c#L2501">2501</a>                 return <a href="ident?i=false">false</a>;
<a name="L2502" href="source/net/ipv4/tcp_output.c#L2502">2502</a>         <b><i>/* TODO: SACK collapsing could be used to remove this condition */</i></b>
<a name="L2503" href="source/net/ipv4/tcp_output.c#L2503">2503</a>         if (<a href="ident?i=skb_shinfo">skb_shinfo</a>(<a href="ident?i=skb">skb</a>)-&gt;nr_frags != 0)
<a name="L2504" href="source/net/ipv4/tcp_output.c#L2504">2504</a>                 return <a href="ident?i=false">false</a>;
<a name="L2505" href="source/net/ipv4/tcp_output.c#L2505">2505</a>         if (<a href="ident?i=skb_cloned">skb_cloned</a>(<a href="ident?i=skb">skb</a>))
<a name="L2506" href="source/net/ipv4/tcp_output.c#L2506">2506</a>                 return <a href="ident?i=false">false</a>;
<a name="L2507" href="source/net/ipv4/tcp_output.c#L2507">2507</a>         if (<a href="ident?i=skb">skb</a> == <a href="ident?i=tcp_send_head">tcp_send_head</a>(sk))
<a name="L2508" href="source/net/ipv4/tcp_output.c#L2508">2508</a>                 return <a href="ident?i=false">false</a>;
<a name="L2509" href="source/net/ipv4/tcp_output.c#L2509">2509</a>         <b><i>/* Some heurestics for collapsing over SACK'd could be invented */</i></b>
<a name="L2510" href="source/net/ipv4/tcp_output.c#L2510">2510</a>         if (<a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;sacked &amp; <a href="ident?i=TCPCB_SACKED_ACKED">TCPCB_SACKED_ACKED</a>)
<a name="L2511" href="source/net/ipv4/tcp_output.c#L2511">2511</a>                 return <a href="ident?i=false">false</a>;
<a name="L2512" href="source/net/ipv4/tcp_output.c#L2512">2512</a> 
<a name="L2513" href="source/net/ipv4/tcp_output.c#L2513">2513</a>         return <a href="ident?i=true">true</a>;
<a name="L2514" href="source/net/ipv4/tcp_output.c#L2514">2514</a> }
<a name="L2515" href="source/net/ipv4/tcp_output.c#L2515">2515</a> 
<a name="L2516" href="source/net/ipv4/tcp_output.c#L2516">2516</a> <b><i>/* Collapse packets in the retransmit queue to make to create</i></b>
<a name="L2517" href="source/net/ipv4/tcp_output.c#L2517">2517</a> <b><i> * less packets on the wire. This is only done on retransmission.</i></b>
<a name="L2518" href="source/net/ipv4/tcp_output.c#L2518">2518</a> <b><i> */</i></b>
<a name="L2519" href="source/net/ipv4/tcp_output.c#L2519">2519</a> static void <a href="ident?i=tcp_retrans_try_collapse">tcp_retrans_try_collapse</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=sk_buff">sk_buff</a> *to,
<a name="L2520" href="source/net/ipv4/tcp_output.c#L2520">2520</a>                                      int <a href="ident?i=space">space</a>)
<a name="L2521" href="source/net/ipv4/tcp_output.c#L2521">2521</a> {
<a name="L2522" href="source/net/ipv4/tcp_output.c#L2522">2522</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L2523" href="source/net/ipv4/tcp_output.c#L2523">2523</a>         struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a> = to, *<a href="ident?i=tmp">tmp</a>;
<a name="L2524" href="source/net/ipv4/tcp_output.c#L2524">2524</a>         <a href="ident?i=bool">bool</a> <a href="ident?i=first">first</a> = <a href="ident?i=true">true</a>;
<a name="L2525" href="source/net/ipv4/tcp_output.c#L2525">2525</a> 
<a name="L2526" href="source/net/ipv4/tcp_output.c#L2526">2526</a>         if (!<a href="ident?i=sysctl_tcp_retrans_collapse">sysctl_tcp_retrans_collapse</a>)
<a name="L2527" href="source/net/ipv4/tcp_output.c#L2527">2527</a>                 return;
<a name="L2528" href="source/net/ipv4/tcp_output.c#L2528">2528</a>         if (<a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;tcp_flags &amp; <a href="ident?i=TCPHDR_SYN">TCPHDR_SYN</a>)
<a name="L2529" href="source/net/ipv4/tcp_output.c#L2529">2529</a>                 return;
<a name="L2530" href="source/net/ipv4/tcp_output.c#L2530">2530</a> 
<a name="L2531" href="source/net/ipv4/tcp_output.c#L2531">2531</a>         <a href="ident?i=tcp_for_write_queue_from_safe">tcp_for_write_queue_from_safe</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=tmp">tmp</a>, sk) {
<a name="L2532" href="source/net/ipv4/tcp_output.c#L2532">2532</a>                 if (!<a href="ident?i=tcp_can_collapse">tcp_can_collapse</a>(sk, <a href="ident?i=skb">skb</a>))
<a name="L2533" href="source/net/ipv4/tcp_output.c#L2533">2533</a>                         break;
<a name="L2534" href="source/net/ipv4/tcp_output.c#L2534">2534</a> 
<a name="L2535" href="source/net/ipv4/tcp_output.c#L2535">2535</a>                 <a href="ident?i=space">space</a> -= <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a>;
<a name="L2536" href="source/net/ipv4/tcp_output.c#L2536">2536</a> 
<a name="L2537" href="source/net/ipv4/tcp_output.c#L2537">2537</a>                 if (<a href="ident?i=first">first</a>) {
<a name="L2538" href="source/net/ipv4/tcp_output.c#L2538">2538</a>                         <a href="ident?i=first">first</a> = <a href="ident?i=false">false</a>;
<a name="L2539" href="source/net/ipv4/tcp_output.c#L2539">2539</a>                         continue;
<a name="L2540" href="source/net/ipv4/tcp_output.c#L2540">2540</a>                 }
<a name="L2541" href="source/net/ipv4/tcp_output.c#L2541">2541</a> 
<a name="L2542" href="source/net/ipv4/tcp_output.c#L2542">2542</a>                 if (<a href="ident?i=space">space</a> &lt; 0)
<a name="L2543" href="source/net/ipv4/tcp_output.c#L2543">2543</a>                         break;
<a name="L2544" href="source/net/ipv4/tcp_output.c#L2544">2544</a>                 <b><i>/* Punt if not enough space exists in the first SKB for</i></b>
<a name="L2545" href="source/net/ipv4/tcp_output.c#L2545">2545</a> <b><i>                 * the data in the second</i></b>
<a name="L2546" href="source/net/ipv4/tcp_output.c#L2546">2546</a> <b><i>                 */</i></b>
<a name="L2547" href="source/net/ipv4/tcp_output.c#L2547">2547</a>                 if (<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a> &gt; <a href="ident?i=skb_availroom">skb_availroom</a>(to))
<a name="L2548" href="source/net/ipv4/tcp_output.c#L2548">2548</a>                         break;
<a name="L2549" href="source/net/ipv4/tcp_output.c#L2549">2549</a> 
<a name="L2550" href="source/net/ipv4/tcp_output.c#L2550">2550</a>                 if (<a href="ident?i=after">after</a>(<a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;end_seq, <a href="ident?i=tcp_wnd_end">tcp_wnd_end</a>(<a href="ident?i=tp">tp</a>)))
<a name="L2551" href="source/net/ipv4/tcp_output.c#L2551">2551</a>                         break;
<a name="L2552" href="source/net/ipv4/tcp_output.c#L2552">2552</a> 
<a name="L2553" href="source/net/ipv4/tcp_output.c#L2553">2553</a>                 <a href="ident?i=tcp_collapse_retrans">tcp_collapse_retrans</a>(sk, to);
<a name="L2554" href="source/net/ipv4/tcp_output.c#L2554">2554</a>         }
<a name="L2555" href="source/net/ipv4/tcp_output.c#L2555">2555</a> }
<a name="L2556" href="source/net/ipv4/tcp_output.c#L2556">2556</a> 
<a name="L2557" href="source/net/ipv4/tcp_output.c#L2557">2557</a> <b><i>/* This retransmits one SKB.  Policy decisions and retransmit queue</i></b>
<a name="L2558" href="source/net/ipv4/tcp_output.c#L2558">2558</a> <b><i> * state updates are done by the caller.  Returns non-zero if an</i></b>
<a name="L2559" href="source/net/ipv4/tcp_output.c#L2559">2559</a> <b><i> * error occurred which prevented the send.</i></b>
<a name="L2560" href="source/net/ipv4/tcp_output.c#L2560">2560</a> <b><i> */</i></b>
<a name="L2561" href="source/net/ipv4/tcp_output.c#L2561">2561</a> int <a href="ident?i=__tcp_retransmit_skb">__tcp_retransmit_skb</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L2562" href="source/net/ipv4/tcp_output.c#L2562">2562</a> {
<a name="L2563" href="source/net/ipv4/tcp_output.c#L2563">2563</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L2564" href="source/net/ipv4/tcp_output.c#L2564">2564</a>         struct <a href="ident?i=inet_connection_sock">inet_connection_sock</a> *icsk = <a href="ident?i=inet_csk">inet_csk</a>(sk);
<a name="L2565" href="source/net/ipv4/tcp_output.c#L2565">2565</a>         unsigned int cur_mss;
<a name="L2566" href="source/net/ipv4/tcp_output.c#L2566">2566</a>         int <a href="ident?i=err">err</a>;
<a name="L2567" href="source/net/ipv4/tcp_output.c#L2567">2567</a> 
<a name="L2568" href="source/net/ipv4/tcp_output.c#L2568">2568</a>         <b><i>/* Inconslusive MTU probe */</i></b>
<a name="L2569" href="source/net/ipv4/tcp_output.c#L2569">2569</a>         if (icsk-&gt;icsk_mtup.probe_size) {
<a name="L2570" href="source/net/ipv4/tcp_output.c#L2570">2570</a>                 icsk-&gt;icsk_mtup.probe_size = 0;
<a name="L2571" href="source/net/ipv4/tcp_output.c#L2571">2571</a>         }
<a name="L2572" href="source/net/ipv4/tcp_output.c#L2572">2572</a> 
<a name="L2573" href="source/net/ipv4/tcp_output.c#L2573">2573</a>         <b><i>/* Do not sent more than we queued. 1/4 is reserved for possible</i></b>
<a name="L2574" href="source/net/ipv4/tcp_output.c#L2574">2574</a> <b><i>         * copying overhead: fragmentation, tunneling, mangling etc.</i></b>
<a name="L2575" href="source/net/ipv4/tcp_output.c#L2575">2575</a> <b><i>         */</i></b>
<a name="L2576" href="source/net/ipv4/tcp_output.c#L2576">2576</a>         if (<a href="ident?i=atomic_read">atomic_read</a>(&amp;sk-&gt;sk_wmem_alloc) &gt;
<a name="L2577" href="source/net/ipv4/tcp_output.c#L2577">2577</a>             <a href="ident?i=min">min</a>(sk-&gt;sk_wmem_queued + (sk-&gt;sk_wmem_queued &gt;&gt; 2), sk-&gt;sk_sndbuf))
<a name="L2578" href="source/net/ipv4/tcp_output.c#L2578">2578</a>                 return -<a href="ident?i=EAGAIN">EAGAIN</a>;
<a name="L2579" href="source/net/ipv4/tcp_output.c#L2579">2579</a> 
<a name="L2580" href="source/net/ipv4/tcp_output.c#L2580">2580</a>         if (<a href="ident?i=skb_still_in_host_queue">skb_still_in_host_queue</a>(sk, <a href="ident?i=skb">skb</a>))
<a name="L2581" href="source/net/ipv4/tcp_output.c#L2581">2581</a>                 return -<a href="ident?i=EBUSY">EBUSY</a>;
<a name="L2582" href="source/net/ipv4/tcp_output.c#L2582">2582</a> 
<a name="L2583" href="source/net/ipv4/tcp_output.c#L2583">2583</a>         if (<a href="ident?i=before">before</a>(<a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=seq">seq</a>, <a href="ident?i=tp">tp</a>-&gt;snd_una)) {
<a name="L2584" href="source/net/ipv4/tcp_output.c#L2584">2584</a>                 if (<a href="ident?i=before">before</a>(<a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;end_seq, <a href="ident?i=tp">tp</a>-&gt;snd_una))
<a name="L2585" href="source/net/ipv4/tcp_output.c#L2585">2585</a>                         <a href="ident?i=BUG">BUG</a>();
<a name="L2586" href="source/net/ipv4/tcp_output.c#L2586">2586</a>                 if (<a href="ident?i=tcp_trim_head">tcp_trim_head</a>(sk, <a href="ident?i=skb">skb</a>, <a href="ident?i=tp">tp</a>-&gt;snd_una - <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=seq">seq</a>))
<a name="L2587" href="source/net/ipv4/tcp_output.c#L2587">2587</a>                         return -<a href="ident?i=ENOMEM">ENOMEM</a>;
<a name="L2588" href="source/net/ipv4/tcp_output.c#L2588">2588</a>         }
<a name="L2589" href="source/net/ipv4/tcp_output.c#L2589">2589</a> 
<a name="L2590" href="source/net/ipv4/tcp_output.c#L2590">2590</a>         if (<a href="ident?i=inet_csk">inet_csk</a>(sk)-&gt;icsk_af_ops-&gt;rebuild_header(sk))
<a name="L2591" href="source/net/ipv4/tcp_output.c#L2591">2591</a>                 return -<a href="ident?i=EHOSTUNREACH">EHOSTUNREACH</a>; <b><i>/* Routing failure or similar. */</i></b>
<a name="L2592" href="source/net/ipv4/tcp_output.c#L2592">2592</a> 
<a name="L2593" href="source/net/ipv4/tcp_output.c#L2593">2593</a>         cur_mss = <a href="ident?i=tcp_current_mss">tcp_current_mss</a>(sk);
<a name="L2594" href="source/net/ipv4/tcp_output.c#L2594">2594</a> 
<a name="L2595" href="source/net/ipv4/tcp_output.c#L2595">2595</a>         <b><i>/* If receiver has shrunk his window, and skb is out of</i></b>
<a name="L2596" href="source/net/ipv4/tcp_output.c#L2596">2596</a> <b><i>         * new window, do not retransmit it. The exception is the</i></b>
<a name="L2597" href="source/net/ipv4/tcp_output.c#L2597">2597</a> <b><i>         * case, when window is shrunk to zero. In this case</i></b>
<a name="L2598" href="source/net/ipv4/tcp_output.c#L2598">2598</a> <b><i>         * our retransmit serves as a zero window probe.</i></b>
<a name="L2599" href="source/net/ipv4/tcp_output.c#L2599">2599</a> <b><i>         */</i></b>
<a name="L2600" href="source/net/ipv4/tcp_output.c#L2600">2600</a>         if (!<a href="ident?i=before">before</a>(<a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=seq">seq</a>, <a href="ident?i=tcp_wnd_end">tcp_wnd_end</a>(<a href="ident?i=tp">tp</a>)) &amp;&amp;
<a name="L2601" href="source/net/ipv4/tcp_output.c#L2601">2601</a>             <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=seq">seq</a> != <a href="ident?i=tp">tp</a>-&gt;snd_una)
<a name="L2602" href="source/net/ipv4/tcp_output.c#L2602">2602</a>                 return -<a href="ident?i=EAGAIN">EAGAIN</a>;
<a name="L2603" href="source/net/ipv4/tcp_output.c#L2603">2603</a> 
<a name="L2604" href="source/net/ipv4/tcp_output.c#L2604">2604</a>         if (<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a> &gt; cur_mss) {
<a name="L2605" href="source/net/ipv4/tcp_output.c#L2605">2605</a>                 if (<a href="ident?i=tcp_fragment">tcp_fragment</a>(sk, <a href="ident?i=skb">skb</a>, cur_mss, cur_mss, <a href="ident?i=GFP_ATOMIC">GFP_ATOMIC</a>))
<a name="L2606" href="source/net/ipv4/tcp_output.c#L2606">2606</a>                         return -<a href="ident?i=ENOMEM">ENOMEM</a>; <b><i>/* We'll try again later. */</i></b>
<a name="L2607" href="source/net/ipv4/tcp_output.c#L2607">2607</a>         } else {
<a name="L2608" href="source/net/ipv4/tcp_output.c#L2608">2608</a>                 int oldpcount = <a href="ident?i=tcp_skb_pcount">tcp_skb_pcount</a>(<a href="ident?i=skb">skb</a>);
<a name="L2609" href="source/net/ipv4/tcp_output.c#L2609">2609</a> 
<a name="L2610" href="source/net/ipv4/tcp_output.c#L2610">2610</a>                 if (<a href="ident?i=unlikely">unlikely</a>(oldpcount &gt; 1)) {
<a name="L2611" href="source/net/ipv4/tcp_output.c#L2611">2611</a>                         if (<a href="ident?i=skb_unclone">skb_unclone</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=GFP_ATOMIC">GFP_ATOMIC</a>))
<a name="L2612" href="source/net/ipv4/tcp_output.c#L2612">2612</a>                                 return -<a href="ident?i=ENOMEM">ENOMEM</a>;
<a name="L2613" href="source/net/ipv4/tcp_output.c#L2613">2613</a>                         <a href="ident?i=tcp_init_tso_segs">tcp_init_tso_segs</a>(sk, <a href="ident?i=skb">skb</a>, cur_mss);
<a name="L2614" href="source/net/ipv4/tcp_output.c#L2614">2614</a>                         <a href="ident?i=tcp_adjust_pcount">tcp_adjust_pcount</a>(sk, <a href="ident?i=skb">skb</a>, oldpcount - <a href="ident?i=tcp_skb_pcount">tcp_skb_pcount</a>(<a href="ident?i=skb">skb</a>));
<a name="L2615" href="source/net/ipv4/tcp_output.c#L2615">2615</a>                 }
<a name="L2616" href="source/net/ipv4/tcp_output.c#L2616">2616</a>         }
<a name="L2617" href="source/net/ipv4/tcp_output.c#L2617">2617</a> 
<a name="L2618" href="source/net/ipv4/tcp_output.c#L2618">2618</a>         <a href="ident?i=tcp_retrans_try_collapse">tcp_retrans_try_collapse</a>(sk, <a href="ident?i=skb">skb</a>, cur_mss);
<a name="L2619" href="source/net/ipv4/tcp_output.c#L2619">2619</a> 
<a name="L2620" href="source/net/ipv4/tcp_output.c#L2620">2620</a>         <b><i>/* Make a copy, if the first transmission SKB clone we made</i></b>
<a name="L2621" href="source/net/ipv4/tcp_output.c#L2621">2621</a> <b><i>         * is still in somebody's hands, else make a clone.</i></b>
<a name="L2622" href="source/net/ipv4/tcp_output.c#L2622">2622</a> <b><i>         */</i></b>
<a name="L2623" href="source/net/ipv4/tcp_output.c#L2623">2623</a> 
<a name="L2624" href="source/net/ipv4/tcp_output.c#L2624">2624</a>         <b><i>/* make sure skb-&gt;data is aligned on arches that require it</i></b>
<a name="L2625" href="source/net/ipv4/tcp_output.c#L2625">2625</a> <b><i>         * and check if ack-trimming &amp; collapsing extended the headroom</i></b>
<a name="L2626" href="source/net/ipv4/tcp_output.c#L2626">2626</a> <b><i>         * beyond what csum_start can cover.</i></b>
<a name="L2627" href="source/net/ipv4/tcp_output.c#L2627">2627</a> <b><i>         */</i></b>
<a name="L2628" href="source/net/ipv4/tcp_output.c#L2628">2628</a>         if (<a href="ident?i=unlikely">unlikely</a>((<a href="ident?i=NET_IP_ALIGN">NET_IP_ALIGN</a> &amp;&amp; ((unsigned long)<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=data">data</a> &amp; 3)) ||
<a name="L2629" href="source/net/ipv4/tcp_output.c#L2629">2629</a>                      <a href="ident?i=skb_headroom">skb_headroom</a>(<a href="ident?i=skb">skb</a>) &gt;= 0xFFFF)) {
<a name="L2630" href="source/net/ipv4/tcp_output.c#L2630">2630</a>                 struct <a href="ident?i=sk_buff">sk_buff</a> *nskb = <a href="ident?i=__pskb_copy">__pskb_copy</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=MAX_TCP_HEADER">MAX_TCP_HEADER</a>,
<a name="L2631" href="source/net/ipv4/tcp_output.c#L2631">2631</a>                                                    <a href="ident?i=GFP_ATOMIC">GFP_ATOMIC</a>);
<a name="L2632" href="source/net/ipv4/tcp_output.c#L2632">2632</a>                 <a href="ident?i=err">err</a> = nskb ? <a href="ident?i=tcp_transmit_skb">tcp_transmit_skb</a>(sk, nskb, 0, <a href="ident?i=GFP_ATOMIC">GFP_ATOMIC</a>) :
<a name="L2633" href="source/net/ipv4/tcp_output.c#L2633">2633</a>                              -<a href="ident?i=ENOBUFS">ENOBUFS</a>;
<a name="L2634" href="source/net/ipv4/tcp_output.c#L2634">2634</a>         } else {
<a name="L2635" href="source/net/ipv4/tcp_output.c#L2635">2635</a>                 <a href="ident?i=err">err</a> = <a href="ident?i=tcp_transmit_skb">tcp_transmit_skb</a>(sk, <a href="ident?i=skb">skb</a>, 1, <a href="ident?i=GFP_ATOMIC">GFP_ATOMIC</a>);
<a name="L2636" href="source/net/ipv4/tcp_output.c#L2636">2636</a>         }
<a name="L2637" href="source/net/ipv4/tcp_output.c#L2637">2637</a> 
<a name="L2638" href="source/net/ipv4/tcp_output.c#L2638">2638</a>         if (<a href="ident?i=likely">likely</a>(!<a href="ident?i=err">err</a>)) {
<a name="L2639" href="source/net/ipv4/tcp_output.c#L2639">2639</a>                 <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;sacked |= <a href="ident?i=TCPCB_EVER_RETRANS">TCPCB_EVER_RETRANS</a>;
<a name="L2640" href="source/net/ipv4/tcp_output.c#L2640">2640</a>                 <b><i>/* Update global TCP statistics. */</i></b>
<a name="L2641" href="source/net/ipv4/tcp_output.c#L2641">2641</a>                 <a href="ident?i=TCP_INC_STATS">TCP_INC_STATS</a>(<a href="ident?i=sock_net">sock_net</a>(sk), TCP_MIB_RETRANSSEGS);
<a name="L2642" href="source/net/ipv4/tcp_output.c#L2642">2642</a>                 if (<a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;tcp_flags &amp; <a href="ident?i=TCPHDR_SYN">TCPHDR_SYN</a>)
<a name="L2643" href="source/net/ipv4/tcp_output.c#L2643">2643</a>                         <a href="ident?i=NET_INC_STATS_BH">NET_INC_STATS_BH</a>(<a href="ident?i=sock_net">sock_net</a>(sk), LINUX_MIB_TCPSYNRETRANS);
<a name="L2644" href="source/net/ipv4/tcp_output.c#L2644">2644</a>                 <a href="ident?i=tp">tp</a>-&gt;total_retrans++;
<a name="L2645" href="source/net/ipv4/tcp_output.c#L2645">2645</a>         }
<a name="L2646" href="source/net/ipv4/tcp_output.c#L2646">2646</a>         return <a href="ident?i=err">err</a>;
<a name="L2647" href="source/net/ipv4/tcp_output.c#L2647">2647</a> }
<a name="L2648" href="source/net/ipv4/tcp_output.c#L2648">2648</a> 
<a name="L2649" href="source/net/ipv4/tcp_output.c#L2649">2649</a> int <a href="ident?i=tcp_retransmit_skb">tcp_retransmit_skb</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L2650" href="source/net/ipv4/tcp_output.c#L2650">2650</a> {
<a name="L2651" href="source/net/ipv4/tcp_output.c#L2651">2651</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L2652" href="source/net/ipv4/tcp_output.c#L2652">2652</a>         int <a href="ident?i=err">err</a> = <a href="ident?i=__tcp_retransmit_skb">__tcp_retransmit_skb</a>(sk, <a href="ident?i=skb">skb</a>);
<a name="L2653" href="source/net/ipv4/tcp_output.c#L2653">2653</a> 
<a name="L2654" href="source/net/ipv4/tcp_output.c#L2654">2654</a>         if (<a href="ident?i=err">err</a> == 0) {
<a name="L2655" href="source/net/ipv4/tcp_output.c#L2655">2655</a> #if <a href="ident?i=FASTRETRANS_DEBUG">FASTRETRANS_DEBUG</a> &gt; 0
<a name="L2656" href="source/net/ipv4/tcp_output.c#L2656">2656</a>                 if (<a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;sacked &amp; <a href="ident?i=TCPCB_SACKED_RETRANS">TCPCB_SACKED_RETRANS</a>) {
<a name="L2657" href="source/net/ipv4/tcp_output.c#L2657">2657</a>                         <a href="ident?i=net_dbg_ratelimited">net_dbg_ratelimited</a>(<i>"retrans_out leaked\n"</i>);
<a name="L2658" href="source/net/ipv4/tcp_output.c#L2658">2658</a>                 }
<a name="L2659" href="source/net/ipv4/tcp_output.c#L2659">2659</a> #endif
<a name="L2660" href="source/net/ipv4/tcp_output.c#L2660">2660</a>                 if (!<a href="ident?i=tp">tp</a>-&gt;retrans_out)
<a name="L2661" href="source/net/ipv4/tcp_output.c#L2661">2661</a>                         <a href="ident?i=tp">tp</a>-&gt;lost_retrans_low = <a href="ident?i=tp">tp</a>-&gt;snd_nxt;
<a name="L2662" href="source/net/ipv4/tcp_output.c#L2662">2662</a>                 <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;sacked |= <a href="ident?i=TCPCB_RETRANS">TCPCB_RETRANS</a>;
<a name="L2663" href="source/net/ipv4/tcp_output.c#L2663">2663</a>                 <a href="ident?i=tp">tp</a>-&gt;retrans_out += <a href="ident?i=tcp_skb_pcount">tcp_skb_pcount</a>(<a href="ident?i=skb">skb</a>);
<a name="L2664" href="source/net/ipv4/tcp_output.c#L2664">2664</a> 
<a name="L2665" href="source/net/ipv4/tcp_output.c#L2665">2665</a>                 <b><i>/* Save stamp of the first retransmit. */</i></b>
<a name="L2666" href="source/net/ipv4/tcp_output.c#L2666">2666</a>                 if (!<a href="ident?i=tp">tp</a>-&gt;retrans_stamp)
<a name="L2667" href="source/net/ipv4/tcp_output.c#L2667">2667</a>                         <a href="ident?i=tp">tp</a>-&gt;retrans_stamp = <a href="ident?i=tcp_skb_timestamp">tcp_skb_timestamp</a>(<a href="ident?i=skb">skb</a>);
<a name="L2668" href="source/net/ipv4/tcp_output.c#L2668">2668</a> 
<a name="L2669" href="source/net/ipv4/tcp_output.c#L2669">2669</a>                 <b><i>/* snd_nxt is stored to detect loss of retransmitted segment,</i></b>
<a name="L2670" href="source/net/ipv4/tcp_output.c#L2670">2670</a> <b><i>                 * see tcp_input.c tcp_sacktag_write_queue().</i></b>
<a name="L2671" href="source/net/ipv4/tcp_output.c#L2671">2671</a> <b><i>                 */</i></b>
<a name="L2672" href="source/net/ipv4/tcp_output.c#L2672">2672</a>                 <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;ack_seq = <a href="ident?i=tp">tp</a>-&gt;snd_nxt;
<a name="L2673" href="source/net/ipv4/tcp_output.c#L2673">2673</a>         } else if (<a href="ident?i=err">err</a> != -<a href="ident?i=EBUSY">EBUSY</a>) {
<a name="L2674" href="source/net/ipv4/tcp_output.c#L2674">2674</a>                 <a href="ident?i=NET_INC_STATS_BH">NET_INC_STATS_BH</a>(<a href="ident?i=sock_net">sock_net</a>(sk), LINUX_MIB_TCPRETRANSFAIL);
<a name="L2675" href="source/net/ipv4/tcp_output.c#L2675">2675</a>         }
<a name="L2676" href="source/net/ipv4/tcp_output.c#L2676">2676</a> 
<a name="L2677" href="source/net/ipv4/tcp_output.c#L2677">2677</a>         if (<a href="ident?i=tp">tp</a>-&gt;undo_retrans &lt; 0)
<a name="L2678" href="source/net/ipv4/tcp_output.c#L2678">2678</a>                 <a href="ident?i=tp">tp</a>-&gt;undo_retrans = 0;
<a name="L2679" href="source/net/ipv4/tcp_output.c#L2679">2679</a>         <a href="ident?i=tp">tp</a>-&gt;undo_retrans += <a href="ident?i=tcp_skb_pcount">tcp_skb_pcount</a>(<a href="ident?i=skb">skb</a>);
<a name="L2680" href="source/net/ipv4/tcp_output.c#L2680">2680</a>         return <a href="ident?i=err">err</a>;
<a name="L2681" href="source/net/ipv4/tcp_output.c#L2681">2681</a> }
<a name="L2682" href="source/net/ipv4/tcp_output.c#L2682">2682</a> 
<a name="L2683" href="source/net/ipv4/tcp_output.c#L2683">2683</a> <b><i>/* Check if we forward retransmits are possible in the current</i></b>
<a name="L2684" href="source/net/ipv4/tcp_output.c#L2684">2684</a> <b><i> * window/congestion state.</i></b>
<a name="L2685" href="source/net/ipv4/tcp_output.c#L2685">2685</a> <b><i> */</i></b>
<a name="L2686" href="source/net/ipv4/tcp_output.c#L2686">2686</a> static <a href="ident?i=bool">bool</a> <a href="ident?i=tcp_can_forward_retransmit">tcp_can_forward_retransmit</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L2687" href="source/net/ipv4/tcp_output.c#L2687">2687</a> {
<a name="L2688" href="source/net/ipv4/tcp_output.c#L2688">2688</a>         const struct <a href="ident?i=inet_connection_sock">inet_connection_sock</a> *icsk = <a href="ident?i=inet_csk">inet_csk</a>(sk);
<a name="L2689" href="source/net/ipv4/tcp_output.c#L2689">2689</a>         const struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L2690" href="source/net/ipv4/tcp_output.c#L2690">2690</a> 
<a name="L2691" href="source/net/ipv4/tcp_output.c#L2691">2691</a>         <b><i>/* Forward retransmissions are possible only during Recovery. */</i></b>
<a name="L2692" href="source/net/ipv4/tcp_output.c#L2692">2692</a>         if (icsk-&gt;icsk_ca_state != TCP_CA_Recovery)
<a name="L2693" href="source/net/ipv4/tcp_output.c#L2693">2693</a>                 return <a href="ident?i=false">false</a>;
<a name="L2694" href="source/net/ipv4/tcp_output.c#L2694">2694</a> 
<a name="L2695" href="source/net/ipv4/tcp_output.c#L2695">2695</a>         <b><i>/* No forward retransmissions in Reno are possible. */</i></b>
<a name="L2696" href="source/net/ipv4/tcp_output.c#L2696">2696</a>         if (<a href="ident?i=tcp_is_reno">tcp_is_reno</a>(<a href="ident?i=tp">tp</a>))
<a name="L2697" href="source/net/ipv4/tcp_output.c#L2697">2697</a>                 return <a href="ident?i=false">false</a>;
<a name="L2698" href="source/net/ipv4/tcp_output.c#L2698">2698</a> 
<a name="L2699" href="source/net/ipv4/tcp_output.c#L2699">2699</a>         <b><i>/* Yeah, we have to make difficult choice between forward transmission</i></b>
<a name="L2700" href="source/net/ipv4/tcp_output.c#L2700">2700</a> <b><i>         * and retransmission... Both ways have their merits...</i></b>
<a name="L2701" href="source/net/ipv4/tcp_output.c#L2701">2701</a> <b><i>         *</i></b>
<a name="L2702" href="source/net/ipv4/tcp_output.c#L2702">2702</a> <b><i>         * For now we do not retransmit anything, while we have some new</i></b>
<a name="L2703" href="source/net/ipv4/tcp_output.c#L2703">2703</a> <b><i>         * segments to send. In the other cases, follow rule 3 for</i></b>
<a name="L2704" href="source/net/ipv4/tcp_output.c#L2704">2704</a> <b><i>         * NextSeg() specified in RFC3517.</i></b>
<a name="L2705" href="source/net/ipv4/tcp_output.c#L2705">2705</a> <b><i>         */</i></b>
<a name="L2706" href="source/net/ipv4/tcp_output.c#L2706">2706</a> 
<a name="L2707" href="source/net/ipv4/tcp_output.c#L2707">2707</a>         if (<a href="ident?i=tcp_may_send_now">tcp_may_send_now</a>(sk))
<a name="L2708" href="source/net/ipv4/tcp_output.c#L2708">2708</a>                 return <a href="ident?i=false">false</a>;
<a name="L2709" href="source/net/ipv4/tcp_output.c#L2709">2709</a> 
<a name="L2710" href="source/net/ipv4/tcp_output.c#L2710">2710</a>         return <a href="ident?i=true">true</a>;
<a name="L2711" href="source/net/ipv4/tcp_output.c#L2711">2711</a> }
<a name="L2712" href="source/net/ipv4/tcp_output.c#L2712">2712</a> 
<a name="L2713" href="source/net/ipv4/tcp_output.c#L2713">2713</a> <b><i>/* This gets called after a retransmit timeout, and the initially</i></b>
<a name="L2714" href="source/net/ipv4/tcp_output.c#L2714">2714</a> <b><i> * retransmitted data is acknowledged.  It tries to continue</i></b>
<a name="L2715" href="source/net/ipv4/tcp_output.c#L2715">2715</a> <b><i> * resending the rest of the retransmit queue, until either</i></b>
<a name="L2716" href="source/net/ipv4/tcp_output.c#L2716">2716</a> <b><i> * we've sent it all or the congestion window limit is reached.</i></b>
<a name="L2717" href="source/net/ipv4/tcp_output.c#L2717">2717</a> <b><i> * If doing SACK, the first ACK which comes back for a timeout</i></b>
<a name="L2718" href="source/net/ipv4/tcp_output.c#L2718">2718</a> <b><i> * based retransmit packet might feed us FACK information again.</i></b>
<a name="L2719" href="source/net/ipv4/tcp_output.c#L2719">2719</a> <b><i> * If so, we use it to avoid unnecessarily retransmissions.</i></b>
<a name="L2720" href="source/net/ipv4/tcp_output.c#L2720">2720</a> <b><i> */</i></b>
<a name="L2721" href="source/net/ipv4/tcp_output.c#L2721">2721</a> void <a href="ident?i=tcp_xmit_retransmit_queue">tcp_xmit_retransmit_queue</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L2722" href="source/net/ipv4/tcp_output.c#L2722">2722</a> {
<a name="L2723" href="source/net/ipv4/tcp_output.c#L2723">2723</a>         const struct <a href="ident?i=inet_connection_sock">inet_connection_sock</a> *icsk = <a href="ident?i=inet_csk">inet_csk</a>(sk);
<a name="L2724" href="source/net/ipv4/tcp_output.c#L2724">2724</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L2725" href="source/net/ipv4/tcp_output.c#L2725">2725</a>         struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>;
<a name="L2726" href="source/net/ipv4/tcp_output.c#L2726">2726</a>         struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=hole">hole</a> = <a href="ident?i=NULL">NULL</a>;
<a name="L2727" href="source/net/ipv4/tcp_output.c#L2727">2727</a>         <a href="ident?i=u32">u32</a> last_lost;
<a name="L2728" href="source/net/ipv4/tcp_output.c#L2728">2728</a>         int mib_idx;
<a name="L2729" href="source/net/ipv4/tcp_output.c#L2729">2729</a>         int fwd_rexmitting = 0;
<a name="L2730" href="source/net/ipv4/tcp_output.c#L2730">2730</a> 
<a name="L2731" href="source/net/ipv4/tcp_output.c#L2731">2731</a>         if (!<a href="ident?i=tp">tp</a>-&gt;packets_out)
<a name="L2732" href="source/net/ipv4/tcp_output.c#L2732">2732</a>                 return;
<a name="L2733" href="source/net/ipv4/tcp_output.c#L2733">2733</a> 
<a name="L2734" href="source/net/ipv4/tcp_output.c#L2734">2734</a>         if (!<a href="ident?i=tp">tp</a>-&gt;lost_out)
<a name="L2735" href="source/net/ipv4/tcp_output.c#L2735">2735</a>                 <a href="ident?i=tp">tp</a>-&gt;retransmit_high = <a href="ident?i=tp">tp</a>-&gt;snd_una;
<a name="L2736" href="source/net/ipv4/tcp_output.c#L2736">2736</a> 
<a name="L2737" href="source/net/ipv4/tcp_output.c#L2737">2737</a>         if (<a href="ident?i=tp">tp</a>-&gt;retransmit_skb_hint) {
<a name="L2738" href="source/net/ipv4/tcp_output.c#L2738">2738</a>                 <a href="ident?i=skb">skb</a> = <a href="ident?i=tp">tp</a>-&gt;retransmit_skb_hint;
<a name="L2739" href="source/net/ipv4/tcp_output.c#L2739">2739</a>                 last_lost = <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;end_seq;
<a name="L2740" href="source/net/ipv4/tcp_output.c#L2740">2740</a>                 if (<a href="ident?i=after">after</a>(last_lost, <a href="ident?i=tp">tp</a>-&gt;retransmit_high))
<a name="L2741" href="source/net/ipv4/tcp_output.c#L2741">2741</a>                         last_lost = <a href="ident?i=tp">tp</a>-&gt;retransmit_high;
<a name="L2742" href="source/net/ipv4/tcp_output.c#L2742">2742</a>         } else {
<a name="L2743" href="source/net/ipv4/tcp_output.c#L2743">2743</a>                 <a href="ident?i=skb">skb</a> = <a href="ident?i=tcp_write_queue_head">tcp_write_queue_head</a>(sk);
<a name="L2744" href="source/net/ipv4/tcp_output.c#L2744">2744</a>                 last_lost = <a href="ident?i=tp">tp</a>-&gt;snd_una;
<a name="L2745" href="source/net/ipv4/tcp_output.c#L2745">2745</a>         }
<a name="L2746" href="source/net/ipv4/tcp_output.c#L2746">2746</a> 
<a name="L2747" href="source/net/ipv4/tcp_output.c#L2747">2747</a>         <a href="ident?i=tcp_for_write_queue_from">tcp_for_write_queue_from</a>(<a href="ident?i=skb">skb</a>, sk) {
<a name="L2748" href="source/net/ipv4/tcp_output.c#L2748">2748</a>                 <a href="ident?i=__u8">__u8</a> sacked = <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;sacked;
<a name="L2749" href="source/net/ipv4/tcp_output.c#L2749">2749</a> 
<a name="L2750" href="source/net/ipv4/tcp_output.c#L2750">2750</a>                 if (<a href="ident?i=skb">skb</a> == <a href="ident?i=tcp_send_head">tcp_send_head</a>(sk))
<a name="L2751" href="source/net/ipv4/tcp_output.c#L2751">2751</a>                         break;
<a name="L2752" href="source/net/ipv4/tcp_output.c#L2752">2752</a>                 <b><i>/* we could do better than to assign each time */</i></b>
<a name="L2753" href="source/net/ipv4/tcp_output.c#L2753">2753</a>                 if (!<a href="ident?i=hole">hole</a>)
<a name="L2754" href="source/net/ipv4/tcp_output.c#L2754">2754</a>                         <a href="ident?i=tp">tp</a>-&gt;retransmit_skb_hint = <a href="ident?i=skb">skb</a>;
<a name="L2755" href="source/net/ipv4/tcp_output.c#L2755">2755</a> 
<a name="L2756" href="source/net/ipv4/tcp_output.c#L2756">2756</a>                 <b><i>/* Assume this retransmit will generate</i></b>
<a name="L2757" href="source/net/ipv4/tcp_output.c#L2757">2757</a> <b><i>                 * only one packet for congestion window</i></b>
<a name="L2758" href="source/net/ipv4/tcp_output.c#L2758">2758</a> <b><i>                 * calculation purposes.  This works because</i></b>
<a name="L2759" href="source/net/ipv4/tcp_output.c#L2759">2759</a> <b><i>                 * tcp_retransmit_skb() will chop up the</i></b>
<a name="L2760" href="source/net/ipv4/tcp_output.c#L2760">2760</a> <b><i>                 * packet to be MSS sized and all the</i></b>
<a name="L2761" href="source/net/ipv4/tcp_output.c#L2761">2761</a> <b><i>                 * packet counting works out.</i></b>
<a name="L2762" href="source/net/ipv4/tcp_output.c#L2762">2762</a> <b><i>                 */</i></b>
<a name="L2763" href="source/net/ipv4/tcp_output.c#L2763">2763</a>                 if (<a href="ident?i=tcp_packets_in_flight">tcp_packets_in_flight</a>(<a href="ident?i=tp">tp</a>) &gt;= <a href="ident?i=tp">tp</a>-&gt;snd_cwnd)
<a name="L2764" href="source/net/ipv4/tcp_output.c#L2764">2764</a>                         return;
<a name="L2765" href="source/net/ipv4/tcp_output.c#L2765">2765</a> 
<a name="L2766" href="source/net/ipv4/tcp_output.c#L2766">2766</a>                 if (fwd_rexmitting) {
<a name="L2767" href="source/net/ipv4/tcp_output.c#L2767">2767</a> begin_fwd:
<a name="L2768" href="source/net/ipv4/tcp_output.c#L2768">2768</a>                         if (!<a href="ident?i=before">before</a>(<a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=seq">seq</a>, <a href="ident?i=tcp_highest_sack_seq">tcp_highest_sack_seq</a>(<a href="ident?i=tp">tp</a>)))
<a name="L2769" href="source/net/ipv4/tcp_output.c#L2769">2769</a>                                 break;
<a name="L2770" href="source/net/ipv4/tcp_output.c#L2770">2770</a>                         mib_idx = LINUX_MIB_TCPFORWARDRETRANS;
<a name="L2771" href="source/net/ipv4/tcp_output.c#L2771">2771</a> 
<a name="L2772" href="source/net/ipv4/tcp_output.c#L2772">2772</a>                 } else if (!<a href="ident?i=before">before</a>(<a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=seq">seq</a>, <a href="ident?i=tp">tp</a>-&gt;retransmit_high)) {
<a name="L2773" href="source/net/ipv4/tcp_output.c#L2773">2773</a>                         <a href="ident?i=tp">tp</a>-&gt;retransmit_high = last_lost;
<a name="L2774" href="source/net/ipv4/tcp_output.c#L2774">2774</a>                         if (!<a href="ident?i=tcp_can_forward_retransmit">tcp_can_forward_retransmit</a>(sk))
<a name="L2775" href="source/net/ipv4/tcp_output.c#L2775">2775</a>                                 break;
<a name="L2776" href="source/net/ipv4/tcp_output.c#L2776">2776</a>                         <b><i>/* Backtrack if necessary to non-L'ed skb */</i></b>
<a name="L2777" href="source/net/ipv4/tcp_output.c#L2777">2777</a>                         if (<a href="ident?i=hole">hole</a>) {
<a name="L2778" href="source/net/ipv4/tcp_output.c#L2778">2778</a>                                 <a href="ident?i=skb">skb</a> = <a href="ident?i=hole">hole</a>;
<a name="L2779" href="source/net/ipv4/tcp_output.c#L2779">2779</a>                                 <a href="ident?i=hole">hole</a> = <a href="ident?i=NULL">NULL</a>;
<a name="L2780" href="source/net/ipv4/tcp_output.c#L2780">2780</a>                         }
<a name="L2781" href="source/net/ipv4/tcp_output.c#L2781">2781</a>                         fwd_rexmitting = 1;
<a name="L2782" href="source/net/ipv4/tcp_output.c#L2782">2782</a>                         goto begin_fwd;
<a name="L2783" href="source/net/ipv4/tcp_output.c#L2783">2783</a> 
<a name="L2784" href="source/net/ipv4/tcp_output.c#L2784">2784</a>                 } else if (!(sacked &amp; <a href="ident?i=TCPCB_LOST">TCPCB_LOST</a>)) {
<a name="L2785" href="source/net/ipv4/tcp_output.c#L2785">2785</a>                         if (!<a href="ident?i=hole">hole</a> &amp;&amp; !(sacked &amp; (<a href="ident?i=TCPCB_SACKED_RETRANS">TCPCB_SACKED_RETRANS</a>|<a href="ident?i=TCPCB_SACKED_ACKED">TCPCB_SACKED_ACKED</a>)))
<a name="L2786" href="source/net/ipv4/tcp_output.c#L2786">2786</a>                                 <a href="ident?i=hole">hole</a> = <a href="ident?i=skb">skb</a>;
<a name="L2787" href="source/net/ipv4/tcp_output.c#L2787">2787</a>                         continue;
<a name="L2788" href="source/net/ipv4/tcp_output.c#L2788">2788</a> 
<a name="L2789" href="source/net/ipv4/tcp_output.c#L2789">2789</a>                 } else {
<a name="L2790" href="source/net/ipv4/tcp_output.c#L2790">2790</a>                         last_lost = <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;end_seq;
<a name="L2791" href="source/net/ipv4/tcp_output.c#L2791">2791</a>                         if (icsk-&gt;icsk_ca_state != TCP_CA_Loss)
<a name="L2792" href="source/net/ipv4/tcp_output.c#L2792">2792</a>                                 mib_idx = LINUX_MIB_TCPFASTRETRANS;
<a name="L2793" href="source/net/ipv4/tcp_output.c#L2793">2793</a>                         else
<a name="L2794" href="source/net/ipv4/tcp_output.c#L2794">2794</a>                                 mib_idx = LINUX_MIB_TCPSLOWSTARTRETRANS;
<a name="L2795" href="source/net/ipv4/tcp_output.c#L2795">2795</a>                 }
<a name="L2796" href="source/net/ipv4/tcp_output.c#L2796">2796</a> 
<a name="L2797" href="source/net/ipv4/tcp_output.c#L2797">2797</a>                 if (sacked &amp; (<a href="ident?i=TCPCB_SACKED_ACKED">TCPCB_SACKED_ACKED</a>|<a href="ident?i=TCPCB_SACKED_RETRANS">TCPCB_SACKED_RETRANS</a>))
<a name="L2798" href="source/net/ipv4/tcp_output.c#L2798">2798</a>                         continue;
<a name="L2799" href="source/net/ipv4/tcp_output.c#L2799">2799</a> 
<a name="L2800" href="source/net/ipv4/tcp_output.c#L2800">2800</a>                 if (<a href="ident?i=tcp_retransmit_skb">tcp_retransmit_skb</a>(sk, <a href="ident?i=skb">skb</a>))
<a name="L2801" href="source/net/ipv4/tcp_output.c#L2801">2801</a>                         return;
<a name="L2802" href="source/net/ipv4/tcp_output.c#L2802">2802</a> 
<a name="L2803" href="source/net/ipv4/tcp_output.c#L2803">2803</a>                 <a href="ident?i=NET_INC_STATS_BH">NET_INC_STATS_BH</a>(<a href="ident?i=sock_net">sock_net</a>(sk), mib_idx);
<a name="L2804" href="source/net/ipv4/tcp_output.c#L2804">2804</a> 
<a name="L2805" href="source/net/ipv4/tcp_output.c#L2805">2805</a>                 if (<a href="ident?i=tcp_in_cwnd_reduction">tcp_in_cwnd_reduction</a>(sk))
<a name="L2806" href="source/net/ipv4/tcp_output.c#L2806">2806</a>                         <a href="ident?i=tp">tp</a>-&gt;prr_out += <a href="ident?i=tcp_skb_pcount">tcp_skb_pcount</a>(<a href="ident?i=skb">skb</a>);
<a name="L2807" href="source/net/ipv4/tcp_output.c#L2807">2807</a> 
<a name="L2808" href="source/net/ipv4/tcp_output.c#L2808">2808</a>                 if (<a href="ident?i=skb">skb</a> == <a href="ident?i=tcp_write_queue_head">tcp_write_queue_head</a>(sk))
<a name="L2809" href="source/net/ipv4/tcp_output.c#L2809">2809</a>                         <a href="ident?i=inet_csk_reset_xmit_timer">inet_csk_reset_xmit_timer</a>(sk, <a href="ident?i=ICSK_TIME_RETRANS">ICSK_TIME_RETRANS</a>,
<a name="L2810" href="source/net/ipv4/tcp_output.c#L2810">2810</a>                                                   <a href="ident?i=inet_csk">inet_csk</a>(sk)-&gt;icsk_rto,
<a name="L2811" href="source/net/ipv4/tcp_output.c#L2811">2811</a>                                                   <a href="ident?i=TCP_RTO_MAX">TCP_RTO_MAX</a>);
<a name="L2812" href="source/net/ipv4/tcp_output.c#L2812">2812</a>         }
<a name="L2813" href="source/net/ipv4/tcp_output.c#L2813">2813</a> }
<a name="L2814" href="source/net/ipv4/tcp_output.c#L2814">2814</a> 
<a name="L2815" href="source/net/ipv4/tcp_output.c#L2815">2815</a> <b><i>/* We allow to exceed memory limits for FIN packets to expedite</i></b>
<a name="L2816" href="source/net/ipv4/tcp_output.c#L2816">2816</a> <b><i> * connection tear down and (memory) recovery.</i></b>
<a name="L2817" href="source/net/ipv4/tcp_output.c#L2817">2817</a> <b><i> * Otherwise tcp_send_fin() could be tempted to either delay FIN</i></b>
<a name="L2818" href="source/net/ipv4/tcp_output.c#L2818">2818</a> <b><i> * or even be forced to close flow without any FIN.</i></b>
<a name="L2819" href="source/net/ipv4/tcp_output.c#L2819">2819</a> <b><i> */</i></b>
<a name="L2820" href="source/net/ipv4/tcp_output.c#L2820">2820</a> static void <a href="ident?i=sk_forced_wmem_schedule">sk_forced_wmem_schedule</a>(struct <a href="ident?i=sock">sock</a> *sk, int <a href="ident?i=size">size</a>)
<a name="L2821" href="source/net/ipv4/tcp_output.c#L2821">2821</a> {
<a name="L2822" href="source/net/ipv4/tcp_output.c#L2822">2822</a>         int amt, <a href="ident?i=status">status</a>;
<a name="L2823" href="source/net/ipv4/tcp_output.c#L2823">2823</a> 
<a name="L2824" href="source/net/ipv4/tcp_output.c#L2824">2824</a>         if (<a href="ident?i=size">size</a> &lt;= sk-&gt;sk_forward_alloc)
<a name="L2825" href="source/net/ipv4/tcp_output.c#L2825">2825</a>                 return;
<a name="L2826" href="source/net/ipv4/tcp_output.c#L2826">2826</a>         amt = <a href="ident?i=sk_mem_pages">sk_mem_pages</a>(<a href="ident?i=size">size</a>);
<a name="L2827" href="source/net/ipv4/tcp_output.c#L2827">2827</a>         sk-&gt;sk_forward_alloc += amt * <a href="ident?i=SK_MEM_QUANTUM">SK_MEM_QUANTUM</a>;
<a name="L2828" href="source/net/ipv4/tcp_output.c#L2828">2828</a>         <a href="ident?i=sk_memory_allocated_add">sk_memory_allocated_add</a>(sk, amt, &amp;<a href="ident?i=status">status</a>);
<a name="L2829" href="source/net/ipv4/tcp_output.c#L2829">2829</a> }
<a name="L2830" href="source/net/ipv4/tcp_output.c#L2830">2830</a> 
<a name="L2831" href="source/net/ipv4/tcp_output.c#L2831">2831</a> <b><i>/* Send a FIN. The caller locks the socket for us.</i></b>
<a name="L2832" href="source/net/ipv4/tcp_output.c#L2832">2832</a> <b><i> * We should try to send a FIN packet really hard, but eventually give up.</i></b>
<a name="L2833" href="source/net/ipv4/tcp_output.c#L2833">2833</a> <b><i> */</i></b>
<a name="L2834" href="source/net/ipv4/tcp_output.c#L2834">2834</a> void <a href="ident?i=tcp_send_fin">tcp_send_fin</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L2835" href="source/net/ipv4/tcp_output.c#L2835">2835</a> {
<a name="L2836" href="source/net/ipv4/tcp_output.c#L2836">2836</a>         struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, *tskb = <a href="ident?i=tcp_write_queue_tail">tcp_write_queue_tail</a>(sk);
<a name="L2837" href="source/net/ipv4/tcp_output.c#L2837">2837</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L2838" href="source/net/ipv4/tcp_output.c#L2838">2838</a> 
<a name="L2839" href="source/net/ipv4/tcp_output.c#L2839">2839</a>         <b><i>/* Optimization, tack on the FIN if we have one skb in write queue and</i></b>
<a name="L2840" href="source/net/ipv4/tcp_output.c#L2840">2840</a> <b><i>         * this skb was not yet sent, or we are under memory pressure.</i></b>
<a name="L2841" href="source/net/ipv4/tcp_output.c#L2841">2841</a> <b><i>         * Note: in the latter case, FIN packet will be sent after a timeout,</i></b>
<a name="L2842" href="source/net/ipv4/tcp_output.c#L2842">2842</a> <b><i>         * as TCP stack thinks it has already been transmitted.</i></b>
<a name="L2843" href="source/net/ipv4/tcp_output.c#L2843">2843</a> <b><i>         */</i></b>
<a name="L2844" href="source/net/ipv4/tcp_output.c#L2844">2844</a>         if (tskb &amp;&amp; (<a href="ident?i=tcp_send_head">tcp_send_head</a>(sk) || <a href="ident?i=sk_under_memory_pressure">sk_under_memory_pressure</a>(sk))) {
<a name="L2845" href="source/net/ipv4/tcp_output.c#L2845">2845</a> <a href="ident?i=coalesce">coalesce</a>:
<a name="L2846" href="source/net/ipv4/tcp_output.c#L2846">2846</a>                 <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(tskb)-&gt;tcp_flags |= <a href="ident?i=TCPHDR_FIN">TCPHDR_FIN</a>;
<a name="L2847" href="source/net/ipv4/tcp_output.c#L2847">2847</a>                 <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(tskb)-&gt;end_seq++;
<a name="L2848" href="source/net/ipv4/tcp_output.c#L2848">2848</a>                 <a href="ident?i=tp">tp</a>-&gt;write_seq++;
<a name="L2849" href="source/net/ipv4/tcp_output.c#L2849">2849</a>                 if (!<a href="ident?i=tcp_send_head">tcp_send_head</a>(sk)) {
<a name="L2850" href="source/net/ipv4/tcp_output.c#L2850">2850</a>                         <b><i>/* This means tskb was already sent.</i></b>
<a name="L2851" href="source/net/ipv4/tcp_output.c#L2851">2851</a> <b><i>                         * Pretend we included the FIN on previous transmit.</i></b>
<a name="L2852" href="source/net/ipv4/tcp_output.c#L2852">2852</a> <b><i>                         * We need to set tp-&gt;snd_nxt to the value it would have</i></b>
<a name="L2853" href="source/net/ipv4/tcp_output.c#L2853">2853</a> <b><i>                         * if FIN had been sent. This is because retransmit path</i></b>
<a name="L2854" href="source/net/ipv4/tcp_output.c#L2854">2854</a> <b><i>                         * does not change tp-&gt;snd_nxt.</i></b>
<a name="L2855" href="source/net/ipv4/tcp_output.c#L2855">2855</a> <b><i>                         */</i></b>
<a name="L2856" href="source/net/ipv4/tcp_output.c#L2856">2856</a>                         <a href="ident?i=tp">tp</a>-&gt;snd_nxt++;
<a name="L2857" href="source/net/ipv4/tcp_output.c#L2857">2857</a>                         return;
<a name="L2858" href="source/net/ipv4/tcp_output.c#L2858">2858</a>                 }
<a name="L2859" href="source/net/ipv4/tcp_output.c#L2859">2859</a>         } else {
<a name="L2860" href="source/net/ipv4/tcp_output.c#L2860">2860</a>                 <a href="ident?i=skb">skb</a> = <a href="ident?i=alloc_skb_fclone">alloc_skb_fclone</a>(<a href="ident?i=MAX_TCP_HEADER">MAX_TCP_HEADER</a>, sk-&gt;sk_allocation);
<a name="L2861" href="source/net/ipv4/tcp_output.c#L2861">2861</a>                 if (<a href="ident?i=unlikely">unlikely</a>(!<a href="ident?i=skb">skb</a>)) {
<a name="L2862" href="source/net/ipv4/tcp_output.c#L2862">2862</a>                         if (tskb)
<a name="L2863" href="source/net/ipv4/tcp_output.c#L2863">2863</a>                                 goto <a href="ident?i=coalesce">coalesce</a>;
<a name="L2864" href="source/net/ipv4/tcp_output.c#L2864">2864</a>                         return;
<a name="L2865" href="source/net/ipv4/tcp_output.c#L2865">2865</a>                 }
<a name="L2866" href="source/net/ipv4/tcp_output.c#L2866">2866</a>                 <a href="ident?i=skb_reserve">skb_reserve</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=MAX_TCP_HEADER">MAX_TCP_HEADER</a>);
<a name="L2867" href="source/net/ipv4/tcp_output.c#L2867">2867</a>                 <a href="ident?i=sk_forced_wmem_schedule">sk_forced_wmem_schedule</a>(sk, <a href="ident?i=skb">skb</a>-&gt;truesize);
<a name="L2868" href="source/net/ipv4/tcp_output.c#L2868">2868</a>                 <b><i>/* FIN eats a sequence byte, write_seq advanced by tcp_queue_skb(). */</i></b>
<a name="L2869" href="source/net/ipv4/tcp_output.c#L2869">2869</a>                 <a href="ident?i=tcp_init_nondata_skb">tcp_init_nondata_skb</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=tp">tp</a>-&gt;write_seq,
<a name="L2870" href="source/net/ipv4/tcp_output.c#L2870">2870</a>                                      <a href="ident?i=TCPHDR_ACK">TCPHDR_ACK</a> | <a href="ident?i=TCPHDR_FIN">TCPHDR_FIN</a>);
<a name="L2871" href="source/net/ipv4/tcp_output.c#L2871">2871</a>                 <a href="ident?i=tcp_queue_skb">tcp_queue_skb</a>(sk, <a href="ident?i=skb">skb</a>);
<a name="L2872" href="source/net/ipv4/tcp_output.c#L2872">2872</a>         }
<a name="L2873" href="source/net/ipv4/tcp_output.c#L2873">2873</a>         <a href="ident?i=__tcp_push_pending_frames">__tcp_push_pending_frames</a>(sk, <a href="ident?i=tcp_current_mss">tcp_current_mss</a>(sk), <a href="ident?i=TCP_NAGLE_OFF">TCP_NAGLE_OFF</a>);
<a name="L2874" href="source/net/ipv4/tcp_output.c#L2874">2874</a> }
<a name="L2875" href="source/net/ipv4/tcp_output.c#L2875">2875</a> 
<a name="L2876" href="source/net/ipv4/tcp_output.c#L2876">2876</a> <b><i>/* We get here when a process closes a file descriptor (either due to</i></b>
<a name="L2877" href="source/net/ipv4/tcp_output.c#L2877">2877</a> <b><i> * an explicit close() or as a byproduct of exit()'ing) and there</i></b>
<a name="L2878" href="source/net/ipv4/tcp_output.c#L2878">2878</a> <b><i> * was unread data in the receive queue.  This behavior is recommended</i></b>
<a name="L2879" href="source/net/ipv4/tcp_output.c#L2879">2879</a> <b><i> * by RFC 2525, section 2.17.  -DaveM</i></b>
<a name="L2880" href="source/net/ipv4/tcp_output.c#L2880">2880</a> <b><i> */</i></b>
<a name="L2881" href="source/net/ipv4/tcp_output.c#L2881">2881</a> void <a href="ident?i=tcp_send_active_reset">tcp_send_active_reset</a>(struct <a href="ident?i=sock">sock</a> *sk, <a href="ident?i=gfp_t">gfp_t</a> <a href="ident?i=priority">priority</a>)
<a name="L2882" href="source/net/ipv4/tcp_output.c#L2882">2882</a> {
<a name="L2883" href="source/net/ipv4/tcp_output.c#L2883">2883</a>         struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>;
<a name="L2884" href="source/net/ipv4/tcp_output.c#L2884">2884</a> 
<a name="L2885" href="source/net/ipv4/tcp_output.c#L2885">2885</a>         <b><i>/* NOTE: No TCP options attached and we never retransmit this. */</i></b>
<a name="L2886" href="source/net/ipv4/tcp_output.c#L2886">2886</a>         <a href="ident?i=skb">skb</a> = <a href="ident?i=alloc_skb">alloc_skb</a>(<a href="ident?i=MAX_TCP_HEADER">MAX_TCP_HEADER</a>, <a href="ident?i=priority">priority</a>);
<a name="L2887" href="source/net/ipv4/tcp_output.c#L2887">2887</a>         if (!<a href="ident?i=skb">skb</a>) {
<a name="L2888" href="source/net/ipv4/tcp_output.c#L2888">2888</a>                 <a href="ident?i=NET_INC_STATS">NET_INC_STATS</a>(<a href="ident?i=sock_net">sock_net</a>(sk), LINUX_MIB_TCPABORTFAILED);
<a name="L2889" href="source/net/ipv4/tcp_output.c#L2889">2889</a>                 return;
<a name="L2890" href="source/net/ipv4/tcp_output.c#L2890">2890</a>         }
<a name="L2891" href="source/net/ipv4/tcp_output.c#L2891">2891</a> 
<a name="L2892" href="source/net/ipv4/tcp_output.c#L2892">2892</a>         <b><i>/* Reserve space for headers and prepare control bits. */</i></b>
<a name="L2893" href="source/net/ipv4/tcp_output.c#L2893">2893</a>         <a href="ident?i=skb_reserve">skb_reserve</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=MAX_TCP_HEADER">MAX_TCP_HEADER</a>);
<a name="L2894" href="source/net/ipv4/tcp_output.c#L2894">2894</a>         <a href="ident?i=tcp_init_nondata_skb">tcp_init_nondata_skb</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=tcp_acceptable_seq">tcp_acceptable_seq</a>(sk),
<a name="L2895" href="source/net/ipv4/tcp_output.c#L2895">2895</a>                              <a href="ident?i=TCPHDR_ACK">TCPHDR_ACK</a> | <a href="ident?i=TCPHDR_RST">TCPHDR_RST</a>);
<a name="L2896" href="source/net/ipv4/tcp_output.c#L2896">2896</a>         <b><i>/* Send it off. */</i></b>
<a name="L2897" href="source/net/ipv4/tcp_output.c#L2897">2897</a>         if (<a href="ident?i=tcp_transmit_skb">tcp_transmit_skb</a>(sk, <a href="ident?i=skb">skb</a>, 0, <a href="ident?i=priority">priority</a>))
<a name="L2898" href="source/net/ipv4/tcp_output.c#L2898">2898</a>                 <a href="ident?i=NET_INC_STATS">NET_INC_STATS</a>(<a href="ident?i=sock_net">sock_net</a>(sk), LINUX_MIB_TCPABORTFAILED);
<a name="L2899" href="source/net/ipv4/tcp_output.c#L2899">2899</a> 
<a name="L2900" href="source/net/ipv4/tcp_output.c#L2900">2900</a>         <a href="ident?i=TCP_INC_STATS">TCP_INC_STATS</a>(<a href="ident?i=sock_net">sock_net</a>(sk), TCP_MIB_OUTRSTS);
<a name="L2901" href="source/net/ipv4/tcp_output.c#L2901">2901</a> }
<a name="L2902" href="source/net/ipv4/tcp_output.c#L2902">2902</a> 
<a name="L2903" href="source/net/ipv4/tcp_output.c#L2903">2903</a> <b><i>/* Send a crossed SYN-ACK during socket establishment.</i></b>
<a name="L2904" href="source/net/ipv4/tcp_output.c#L2904">2904</a> <b><i> * WARNING: This routine must only be called when we have already sent</i></b>
<a name="L2905" href="source/net/ipv4/tcp_output.c#L2905">2905</a> <b><i> * a SYN packet that crossed the incoming SYN that caused this routine</i></b>
<a name="L2906" href="source/net/ipv4/tcp_output.c#L2906">2906</a> <b><i> * to get called. If this assumption fails then the initial rcv_wnd</i></b>
<a name="L2907" href="source/net/ipv4/tcp_output.c#L2907">2907</a> <b><i> * and rcv_wscale values will not be correct.</i></b>
<a name="L2908" href="source/net/ipv4/tcp_output.c#L2908">2908</a> <b><i> */</i></b>
<a name="L2909" href="source/net/ipv4/tcp_output.c#L2909">2909</a> int <a href="ident?i=tcp_send_synack">tcp_send_synack</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L2910" href="source/net/ipv4/tcp_output.c#L2910">2910</a> {
<a name="L2911" href="source/net/ipv4/tcp_output.c#L2911">2911</a>         struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>;
<a name="L2912" href="source/net/ipv4/tcp_output.c#L2912">2912</a> 
<a name="L2913" href="source/net/ipv4/tcp_output.c#L2913">2913</a>         <a href="ident?i=skb">skb</a> = <a href="ident?i=tcp_write_queue_head">tcp_write_queue_head</a>(sk);
<a name="L2914" href="source/net/ipv4/tcp_output.c#L2914">2914</a>         if (!<a href="ident?i=skb">skb</a> || !(<a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;tcp_flags &amp; <a href="ident?i=TCPHDR_SYN">TCPHDR_SYN</a>)) {
<a name="L2915" href="source/net/ipv4/tcp_output.c#L2915">2915</a>                 <a href="ident?i=pr_debug">pr_debug</a>(<i>"%s: wrong queue state\n"</i>, <a href="ident?i=__func__">__func__</a>);
<a name="L2916" href="source/net/ipv4/tcp_output.c#L2916">2916</a>                 return -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L2917" href="source/net/ipv4/tcp_output.c#L2917">2917</a>         }
<a name="L2918" href="source/net/ipv4/tcp_output.c#L2918">2918</a>         if (!(<a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;tcp_flags &amp; <a href="ident?i=TCPHDR_ACK">TCPHDR_ACK</a>)) {
<a name="L2919" href="source/net/ipv4/tcp_output.c#L2919">2919</a>                 if (<a href="ident?i=skb_cloned">skb_cloned</a>(<a href="ident?i=skb">skb</a>)) {
<a name="L2920" href="source/net/ipv4/tcp_output.c#L2920">2920</a>                         struct <a href="ident?i=sk_buff">sk_buff</a> *nskb = <a href="ident?i=skb_copy">skb_copy</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=GFP_ATOMIC">GFP_ATOMIC</a>);
<a name="L2921" href="source/net/ipv4/tcp_output.c#L2921">2921</a>                         if (!nskb)
<a name="L2922" href="source/net/ipv4/tcp_output.c#L2922">2922</a>                                 return -<a href="ident?i=ENOMEM">ENOMEM</a>;
<a name="L2923" href="source/net/ipv4/tcp_output.c#L2923">2923</a>                         <a href="ident?i=tcp_unlink_write_queue">tcp_unlink_write_queue</a>(<a href="ident?i=skb">skb</a>, sk);
<a name="L2924" href="source/net/ipv4/tcp_output.c#L2924">2924</a>                         <a href="ident?i=__skb_header_release">__skb_header_release</a>(nskb);
<a name="L2925" href="source/net/ipv4/tcp_output.c#L2925">2925</a>                         <a href="ident?i=__tcp_add_write_queue_head">__tcp_add_write_queue_head</a>(sk, nskb);
<a name="L2926" href="source/net/ipv4/tcp_output.c#L2926">2926</a>                         <a href="ident?i=sk_wmem_free_skb">sk_wmem_free_skb</a>(sk, <a href="ident?i=skb">skb</a>);
<a name="L2927" href="source/net/ipv4/tcp_output.c#L2927">2927</a>                         sk-&gt;sk_wmem_queued += nskb-&gt;truesize;
<a name="L2928" href="source/net/ipv4/tcp_output.c#L2928">2928</a>                         <a href="ident?i=sk_mem_charge">sk_mem_charge</a>(sk, nskb-&gt;truesize);
<a name="L2929" href="source/net/ipv4/tcp_output.c#L2929">2929</a>                         <a href="ident?i=skb">skb</a> = nskb;
<a name="L2930" href="source/net/ipv4/tcp_output.c#L2930">2930</a>                 }
<a name="L2931" href="source/net/ipv4/tcp_output.c#L2931">2931</a> 
<a name="L2932" href="source/net/ipv4/tcp_output.c#L2932">2932</a>                 <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;tcp_flags |= <a href="ident?i=TCPHDR_ACK">TCPHDR_ACK</a>;
<a name="L2933" href="source/net/ipv4/tcp_output.c#L2933">2933</a>                 <a href="ident?i=tcp_ecn_send_synack">tcp_ecn_send_synack</a>(sk, <a href="ident?i=skb">skb</a>);
<a name="L2934" href="source/net/ipv4/tcp_output.c#L2934">2934</a>         }
<a name="L2935" href="source/net/ipv4/tcp_output.c#L2935">2935</a>         return <a href="ident?i=tcp_transmit_skb">tcp_transmit_skb</a>(sk, <a href="ident?i=skb">skb</a>, 1, <a href="ident?i=GFP_ATOMIC">GFP_ATOMIC</a>);
<a name="L2936" href="source/net/ipv4/tcp_output.c#L2936">2936</a> }
<a name="L2937" href="source/net/ipv4/tcp_output.c#L2937">2937</a> 
<a name="L2938" href="source/net/ipv4/tcp_output.c#L2938">2938</a> <b><i>/**</i></b>
<a name="L2939" href="source/net/ipv4/tcp_output.c#L2939">2939</a> <b><i> * tcp_make_synack - Prepare a SYN-ACK.</i></b>
<a name="L2940" href="source/net/ipv4/tcp_output.c#L2940">2940</a> <b><i> * sk: listener socket</i></b>
<a name="L2941" href="source/net/ipv4/tcp_output.c#L2941">2941</a> <b><i> * dst: dst entry attached to the SYNACK</i></b>
<a name="L2942" href="source/net/ipv4/tcp_output.c#L2942">2942</a> <b><i> * req: request_sock pointer</i></b>
<a name="L2943" href="source/net/ipv4/tcp_output.c#L2943">2943</a> <b><i> *</i></b>
<a name="L2944" href="source/net/ipv4/tcp_output.c#L2944">2944</a> <b><i> * Allocate one skb and build a SYNACK packet.</i></b>
<a name="L2945" href="source/net/ipv4/tcp_output.c#L2945">2945</a> <b><i> * @dst is consumed : Caller should not use it again.</i></b>
<a name="L2946" href="source/net/ipv4/tcp_output.c#L2946">2946</a> <b><i> */</i></b>
<a name="L2947" href="source/net/ipv4/tcp_output.c#L2947">2947</a> struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=tcp_make_synack">tcp_make_synack</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=dst_entry">dst_entry</a> *<a href="ident?i=dst">dst</a>,
<a name="L2948" href="source/net/ipv4/tcp_output.c#L2948">2948</a>                                 struct <a href="ident?i=request_sock">request_sock</a> *<a href="ident?i=req">req</a>,
<a name="L2949" href="source/net/ipv4/tcp_output.c#L2949">2949</a>                                 struct <a href="ident?i=tcp_fastopen_cookie">tcp_fastopen_cookie</a> *foc)
<a name="L2950" href="source/net/ipv4/tcp_output.c#L2950">2950</a> {
<a name="L2951" href="source/net/ipv4/tcp_output.c#L2951">2951</a>         struct <a href="ident?i=tcp_out_options">tcp_out_options</a> <a href="ident?i=opts">opts</a>;
<a name="L2952" href="source/net/ipv4/tcp_output.c#L2952">2952</a>         struct <a href="ident?i=inet_request_sock">inet_request_sock</a> *ireq = <a href="ident?i=inet_rsk">inet_rsk</a>(<a href="ident?i=req">req</a>);
<a name="L2953" href="source/net/ipv4/tcp_output.c#L2953">2953</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L2954" href="source/net/ipv4/tcp_output.c#L2954">2954</a>         struct <a href="ident?i=tcphdr">tcphdr</a> *<a href="ident?i=th">th</a>;
<a name="L2955" href="source/net/ipv4/tcp_output.c#L2955">2955</a>         struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>;
<a name="L2956" href="source/net/ipv4/tcp_output.c#L2956">2956</a>         struct <a href="ident?i=tcp_md5sig_key">tcp_md5sig_key</a> *md5 = <a href="ident?i=NULL">NULL</a>;
<a name="L2957" href="source/net/ipv4/tcp_output.c#L2957">2957</a>         int tcp_header_size;
<a name="L2958" href="source/net/ipv4/tcp_output.c#L2958">2958</a>         int mss;
<a name="L2959" href="source/net/ipv4/tcp_output.c#L2959">2959</a> 
<a name="L2960" href="source/net/ipv4/tcp_output.c#L2960">2960</a>         <a href="ident?i=skb">skb</a> = <a href="ident?i=sock_wmalloc">sock_wmalloc</a>(sk, <a href="ident?i=MAX_TCP_HEADER">MAX_TCP_HEADER</a>, 1, <a href="ident?i=GFP_ATOMIC">GFP_ATOMIC</a>);
<a name="L2961" href="source/net/ipv4/tcp_output.c#L2961">2961</a>         if (<a href="ident?i=unlikely">unlikely</a>(!<a href="ident?i=skb">skb</a>)) {
<a name="L2962" href="source/net/ipv4/tcp_output.c#L2962">2962</a>                 <a href="ident?i=dst_release">dst_release</a>(<a href="ident?i=dst">dst</a>);
<a name="L2963" href="source/net/ipv4/tcp_output.c#L2963">2963</a>                 return <a href="ident?i=NULL">NULL</a>;
<a name="L2964" href="source/net/ipv4/tcp_output.c#L2964">2964</a>         }
<a name="L2965" href="source/net/ipv4/tcp_output.c#L2965">2965</a>         <b><i>/* Reserve space for headers. */</i></b>
<a name="L2966" href="source/net/ipv4/tcp_output.c#L2966">2966</a>         <a href="ident?i=skb_reserve">skb_reserve</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=MAX_TCP_HEADER">MAX_TCP_HEADER</a>);
<a name="L2967" href="source/net/ipv4/tcp_output.c#L2967">2967</a> 
<a name="L2968" href="source/net/ipv4/tcp_output.c#L2968">2968</a>         <a href="ident?i=skb_dst_set">skb_dst_set</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=dst">dst</a>);
<a name="L2969" href="source/net/ipv4/tcp_output.c#L2969">2969</a> 
<a name="L2970" href="source/net/ipv4/tcp_output.c#L2970">2970</a>         mss = <a href="ident?i=dst_metric_advmss">dst_metric_advmss</a>(<a href="ident?i=dst">dst</a>);
<a name="L2971" href="source/net/ipv4/tcp_output.c#L2971">2971</a>         if (<a href="ident?i=tp">tp</a>-&gt;rx_opt.user_mss &amp;&amp; <a href="ident?i=tp">tp</a>-&gt;rx_opt.user_mss &lt; mss)
<a name="L2972" href="source/net/ipv4/tcp_output.c#L2972">2972</a>                 mss = <a href="ident?i=tp">tp</a>-&gt;rx_opt.user_mss;
<a name="L2973" href="source/net/ipv4/tcp_output.c#L2973">2973</a> 
<a name="L2974" href="source/net/ipv4/tcp_output.c#L2974">2974</a>         <a href="ident?i=memset">memset</a>(&amp;<a href="ident?i=opts">opts</a>, 0, sizeof(<a href="ident?i=opts">opts</a>));
<a name="L2975" href="source/net/ipv4/tcp_output.c#L2975">2975</a> #ifdef CONFIG_SYN_COOKIES
<a name="L2976" href="source/net/ipv4/tcp_output.c#L2976">2976</a>         if (<a href="ident?i=unlikely">unlikely</a>(<a href="ident?i=req">req</a>-&gt;cookie_ts))
<a name="L2977" href="source/net/ipv4/tcp_output.c#L2977">2977</a>                 <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=skb_mstamp">skb_mstamp</a>.stamp_jiffies = <a href="ident?i=cookie_init_timestamp">cookie_init_timestamp</a>(<a href="ident?i=req">req</a>);
<a name="L2978" href="source/net/ipv4/tcp_output.c#L2978">2978</a>         else
<a name="L2979" href="source/net/ipv4/tcp_output.c#L2979">2979</a> #endif
<a name="L2980" href="source/net/ipv4/tcp_output.c#L2980">2980</a>         <a href="ident?i=skb_mstamp_get">skb_mstamp_get</a>(&amp;<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=skb_mstamp">skb_mstamp</a>);
<a name="L2981" href="source/net/ipv4/tcp_output.c#L2981">2981</a> 
<a name="L2982" href="source/net/ipv4/tcp_output.c#L2982">2982</a> #ifdef CONFIG_TCP_MD5SIG
<a name="L2983" href="source/net/ipv4/tcp_output.c#L2983">2983</a>         <a href="ident?i=rcu_read_lock">rcu_read_lock</a>();
<a name="L2984" href="source/net/ipv4/tcp_output.c#L2984">2984</a>         md5 = <a href="ident?i=tcp_rsk">tcp_rsk</a>(<a href="ident?i=req">req</a>)-&gt;af_specific-&gt;req_md5_lookup(sk, <a href="ident?i=req_to_sk">req_to_sk</a>(<a href="ident?i=req">req</a>));
<a name="L2985" href="source/net/ipv4/tcp_output.c#L2985">2985</a> #endif
<a name="L2986" href="source/net/ipv4/tcp_output.c#L2986">2986</a>         tcp_header_size = <a href="ident?i=tcp_synack_options">tcp_synack_options</a>(sk, <a href="ident?i=req">req</a>, mss, <a href="ident?i=skb">skb</a>, &amp;<a href="ident?i=opts">opts</a>, md5,
<a name="L2987" href="source/net/ipv4/tcp_output.c#L2987">2987</a>                                              foc) + sizeof(*<a href="ident?i=th">th</a>);
<a name="L2988" href="source/net/ipv4/tcp_output.c#L2988">2988</a> 
<a name="L2989" href="source/net/ipv4/tcp_output.c#L2989">2989</a>         <a href="ident?i=skb_push">skb_push</a>(<a href="ident?i=skb">skb</a>, tcp_header_size);
<a name="L2990" href="source/net/ipv4/tcp_output.c#L2990">2990</a>         <a href="ident?i=skb_reset_transport_header">skb_reset_transport_header</a>(<a href="ident?i=skb">skb</a>);
<a name="L2991" href="source/net/ipv4/tcp_output.c#L2991">2991</a> 
<a name="L2992" href="source/net/ipv4/tcp_output.c#L2992">2992</a>         <a href="ident?i=th">th</a> = <a href="ident?i=tcp_hdr">tcp_hdr</a>(<a href="ident?i=skb">skb</a>);
<a name="L2993" href="source/net/ipv4/tcp_output.c#L2993">2993</a>         <a href="ident?i=memset">memset</a>(<a href="ident?i=th">th</a>, 0, sizeof(struct <a href="ident?i=tcphdr">tcphdr</a>));
<a name="L2994" href="source/net/ipv4/tcp_output.c#L2994">2994</a>         <a href="ident?i=th">th</a>-&gt;syn = 1;
<a name="L2995" href="source/net/ipv4/tcp_output.c#L2995">2995</a>         <a href="ident?i=th">th</a>-&gt;ack = 1;
<a name="L2996" href="source/net/ipv4/tcp_output.c#L2996">2996</a>         <a href="ident?i=tcp_ecn_make_synack">tcp_ecn_make_synack</a>(<a href="ident?i=req">req</a>, <a href="ident?i=th">th</a>, sk);
<a name="L2997" href="source/net/ipv4/tcp_output.c#L2997">2997</a>         <a href="ident?i=th">th</a>-&gt;source = <a href="ident?i=htons">htons</a>(ireq-&gt;<a href="ident?i=ir_num">ir_num</a>);
<a name="L2998" href="source/net/ipv4/tcp_output.c#L2998">2998</a>         <a href="ident?i=th">th</a>-&gt;<a href="ident?i=dest">dest</a> = ireq-&gt;<a href="ident?i=ir_rmt_port">ir_rmt_port</a>;
<a name="L2999" href="source/net/ipv4/tcp_output.c#L2999">2999</a>         <b><i>/* Setting of flags are superfluous here for callers (and ECE is</i></b>
<a name="L3000" href="source/net/ipv4/tcp_output.c#L3000">3000</a> <b><i>         * not even correctly set)</i></b>
<a name="L3001" href="source/net/ipv4/tcp_output.c#L3001">3001</a> <b><i>         */</i></b>
<a name="L3002" href="source/net/ipv4/tcp_output.c#L3002">3002</a>         <a href="ident?i=tcp_init_nondata_skb">tcp_init_nondata_skb</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=tcp_rsk">tcp_rsk</a>(<a href="ident?i=req">req</a>)-&gt;snt_isn,
<a name="L3003" href="source/net/ipv4/tcp_output.c#L3003">3003</a>                              <a href="ident?i=TCPHDR_SYN">TCPHDR_SYN</a> | <a href="ident?i=TCPHDR_ACK">TCPHDR_ACK</a>);
<a name="L3004" href="source/net/ipv4/tcp_output.c#L3004">3004</a> 
<a name="L3005" href="source/net/ipv4/tcp_output.c#L3005">3005</a>         <a href="ident?i=th">th</a>-&gt;<a href="ident?i=seq">seq</a> = <a href="ident?i=htonl">htonl</a>(<a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=seq">seq</a>);
<a name="L3006" href="source/net/ipv4/tcp_output.c#L3006">3006</a>         <b><i>/* XXX data is queued and acked as is. No buffer/window check */</i></b>
<a name="L3007" href="source/net/ipv4/tcp_output.c#L3007">3007</a>         <a href="ident?i=th">th</a>-&gt;ack_seq = <a href="ident?i=htonl">htonl</a>(<a href="ident?i=tcp_rsk">tcp_rsk</a>(<a href="ident?i=req">req</a>)-&gt;rcv_nxt);
<a name="L3008" href="source/net/ipv4/tcp_output.c#L3008">3008</a> 
<a name="L3009" href="source/net/ipv4/tcp_output.c#L3009">3009</a>         <b><i>/* RFC1323: The window in SYN &amp; SYN/ACK segments is never scaled. */</i></b>
<a name="L3010" href="source/net/ipv4/tcp_output.c#L3010">3010</a>         <a href="ident?i=th">th</a>-&gt;<a href="ident?i=window">window</a> = <a href="ident?i=htons">htons</a>(<a href="ident?i=min">min</a>(<a href="ident?i=req">req</a>-&gt;rcv_wnd, 65535U));
<a name="L3011" href="source/net/ipv4/tcp_output.c#L3011">3011</a>         <a href="ident?i=tcp_options_write">tcp_options_write</a>((<a href="ident?i=__be32">__be32</a> *)(<a href="ident?i=th">th</a> + 1), <a href="ident?i=tp">tp</a>, &amp;<a href="ident?i=opts">opts</a>);
<a name="L3012" href="source/net/ipv4/tcp_output.c#L3012">3012</a>         <a href="ident?i=th">th</a>-&gt;doff = (tcp_header_size &gt;&gt; 2);
<a name="L3013" href="source/net/ipv4/tcp_output.c#L3013">3013</a>         <a href="ident?i=TCP_INC_STATS_BH">TCP_INC_STATS_BH</a>(<a href="ident?i=sock_net">sock_net</a>(sk), TCP_MIB_OUTSEGS);
<a name="L3014" href="source/net/ipv4/tcp_output.c#L3014">3014</a> 
<a name="L3015" href="source/net/ipv4/tcp_output.c#L3015">3015</a> #ifdef CONFIG_TCP_MD5SIG
<a name="L3016" href="source/net/ipv4/tcp_output.c#L3016">3016</a>         <b><i>/* Okay, we have all we need - do the md5 hash if needed */</i></b>
<a name="L3017" href="source/net/ipv4/tcp_output.c#L3017">3017</a>         if (md5)
<a name="L3018" href="source/net/ipv4/tcp_output.c#L3018">3018</a>                 <a href="ident?i=tcp_rsk">tcp_rsk</a>(<a href="ident?i=req">req</a>)-&gt;af_specific-&gt;calc_md5_hash(<a href="ident?i=opts">opts</a>.hash_location,
<a name="L3019" href="source/net/ipv4/tcp_output.c#L3019">3019</a>                                                md5, <a href="ident?i=req_to_sk">req_to_sk</a>(<a href="ident?i=req">req</a>), <a href="ident?i=skb">skb</a>);
<a name="L3020" href="source/net/ipv4/tcp_output.c#L3020">3020</a>         <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L3021" href="source/net/ipv4/tcp_output.c#L3021">3021</a> #endif
<a name="L3022" href="source/net/ipv4/tcp_output.c#L3022">3022</a> 
<a name="L3023" href="source/net/ipv4/tcp_output.c#L3023">3023</a>         <b><i>/* Do not fool tcpdump (if any), clean our debris */</i></b>
<a name="L3024" href="source/net/ipv4/tcp_output.c#L3024">3024</a>         <a href="ident?i=skb">skb</a>-&gt;tstamp.tv64 = 0;
<a name="L3025" href="source/net/ipv4/tcp_output.c#L3025">3025</a>         return <a href="ident?i=skb">skb</a>;
<a name="L3026" href="source/net/ipv4/tcp_output.c#L3026">3026</a> }
<a name="L3027" href="source/net/ipv4/tcp_output.c#L3027">3027</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=tcp_make_synack">tcp_make_synack</a>);
<a name="L3028" href="source/net/ipv4/tcp_output.c#L3028">3028</a> 
<a name="L3029" href="source/net/ipv4/tcp_output.c#L3029">3029</a> static void <a href="ident?i=tcp_ca_dst_init">tcp_ca_dst_init</a>(struct <a href="ident?i=sock">sock</a> *sk, const struct <a href="ident?i=dst_entry">dst_entry</a> *<a href="ident?i=dst">dst</a>)
<a name="L3030" href="source/net/ipv4/tcp_output.c#L3030">3030</a> {
<a name="L3031" href="source/net/ipv4/tcp_output.c#L3031">3031</a>         struct <a href="ident?i=inet_connection_sock">inet_connection_sock</a> *icsk = <a href="ident?i=inet_csk">inet_csk</a>(sk);
<a name="L3032" href="source/net/ipv4/tcp_output.c#L3032">3032</a>         const struct <a href="ident?i=tcp_congestion_ops">tcp_congestion_ops</a> *<a href="ident?i=ca">ca</a>;
<a name="L3033" href="source/net/ipv4/tcp_output.c#L3033">3033</a>         <a href="ident?i=u32">u32</a> ca_key = <a href="ident?i=dst_metric">dst_metric</a>(<a href="ident?i=dst">dst</a>, <a href="ident?i=RTAX_CC_ALGO">RTAX_CC_ALGO</a>);
<a name="L3034" href="source/net/ipv4/tcp_output.c#L3034">3034</a> 
<a name="L3035" href="source/net/ipv4/tcp_output.c#L3035">3035</a>         if (ca_key == <a href="ident?i=TCP_CA_UNSPEC">TCP_CA_UNSPEC</a>)
<a name="L3036" href="source/net/ipv4/tcp_output.c#L3036">3036</a>                 return;
<a name="L3037" href="source/net/ipv4/tcp_output.c#L3037">3037</a> 
<a name="L3038" href="source/net/ipv4/tcp_output.c#L3038">3038</a>         <a href="ident?i=rcu_read_lock">rcu_read_lock</a>();
<a name="L3039" href="source/net/ipv4/tcp_output.c#L3039">3039</a>         <a href="ident?i=ca">ca</a> = <a href="ident?i=tcp_ca_find_key">tcp_ca_find_key</a>(ca_key);
<a name="L3040" href="source/net/ipv4/tcp_output.c#L3040">3040</a>         if (<a href="ident?i=likely">likely</a>(<a href="ident?i=ca">ca</a> &amp;&amp; <a href="ident?i=try_module_get">try_module_get</a>(<a href="ident?i=ca">ca</a>-&gt;owner))) {
<a name="L3041" href="source/net/ipv4/tcp_output.c#L3041">3041</a>                 <a href="ident?i=module_put">module_put</a>(icsk-&gt;icsk_ca_ops-&gt;owner);
<a name="L3042" href="source/net/ipv4/tcp_output.c#L3042">3042</a>                 icsk-&gt;icsk_ca_dst_locked = <a href="ident?i=tcp_ca_dst_locked">tcp_ca_dst_locked</a>(<a href="ident?i=dst">dst</a>);
<a name="L3043" href="source/net/ipv4/tcp_output.c#L3043">3043</a>                 icsk-&gt;icsk_ca_ops = <a href="ident?i=ca">ca</a>;
<a name="L3044" href="source/net/ipv4/tcp_output.c#L3044">3044</a>         }
<a name="L3045" href="source/net/ipv4/tcp_output.c#L3045">3045</a>         <a href="ident?i=rcu_read_unlock">rcu_read_unlock</a>();
<a name="L3046" href="source/net/ipv4/tcp_output.c#L3046">3046</a> }
<a name="L3047" href="source/net/ipv4/tcp_output.c#L3047">3047</a> 
<a name="L3048" href="source/net/ipv4/tcp_output.c#L3048">3048</a> <b><i>/* Do all connect socket setups that can be done AF independent. */</i></b>
<a name="L3049" href="source/net/ipv4/tcp_output.c#L3049">3049</a> static void <a href="ident?i=tcp_connect_init">tcp_connect_init</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L3050" href="source/net/ipv4/tcp_output.c#L3050">3050</a> {
<a name="L3051" href="source/net/ipv4/tcp_output.c#L3051">3051</a>         const struct <a href="ident?i=dst_entry">dst_entry</a> *<a href="ident?i=dst">dst</a> = <a href="ident?i=__sk_dst_get">__sk_dst_get</a>(sk);
<a name="L3052" href="source/net/ipv4/tcp_output.c#L3052">3052</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L3053" href="source/net/ipv4/tcp_output.c#L3053">3053</a>         <a href="ident?i=__u8">__u8</a> rcv_wscale;
<a name="L3054" href="source/net/ipv4/tcp_output.c#L3054">3054</a> 
<a name="L3055" href="source/net/ipv4/tcp_output.c#L3055">3055</a>         <b><i>/* We'll fix this up when we get a response from the other end.</i></b>
<a name="L3056" href="source/net/ipv4/tcp_output.c#L3056">3056</a> <b><i>         * See tcp_input.c:tcp_rcv_state_process case TCP_SYN_SENT.</i></b>
<a name="L3057" href="source/net/ipv4/tcp_output.c#L3057">3057</a> <b><i>         */</i></b>
<a name="L3058" href="source/net/ipv4/tcp_output.c#L3058">3058</a>         <a href="ident?i=tp">tp</a>-&gt;tcp_header_len = sizeof(struct <a href="ident?i=tcphdr">tcphdr</a>) +
<a name="L3059" href="source/net/ipv4/tcp_output.c#L3059">3059</a>                 (<a href="ident?i=sysctl_tcp_timestamps">sysctl_tcp_timestamps</a> ? <a href="ident?i=TCPOLEN_TSTAMP_ALIGNED">TCPOLEN_TSTAMP_ALIGNED</a> : 0);
<a name="L3060" href="source/net/ipv4/tcp_output.c#L3060">3060</a> 
<a name="L3061" href="source/net/ipv4/tcp_output.c#L3061">3061</a> #ifdef CONFIG_TCP_MD5SIG
<a name="L3062" href="source/net/ipv4/tcp_output.c#L3062">3062</a>         if (<a href="ident?i=tp">tp</a>-&gt;af_specific-&gt;md5_lookup(sk, sk))
<a name="L3063" href="source/net/ipv4/tcp_output.c#L3063">3063</a>                 <a href="ident?i=tp">tp</a>-&gt;tcp_header_len += <a href="ident?i=TCPOLEN_MD5SIG_ALIGNED">TCPOLEN_MD5SIG_ALIGNED</a>;
<a name="L3064" href="source/net/ipv4/tcp_output.c#L3064">3064</a> #endif
<a name="L3065" href="source/net/ipv4/tcp_output.c#L3065">3065</a> 
<a name="L3066" href="source/net/ipv4/tcp_output.c#L3066">3066</a>         <b><i>/* If user gave his TCP_MAXSEG, record it to clamp */</i></b>
<a name="L3067" href="source/net/ipv4/tcp_output.c#L3067">3067</a>         if (<a href="ident?i=tp">tp</a>-&gt;rx_opt.user_mss)
<a name="L3068" href="source/net/ipv4/tcp_output.c#L3068">3068</a>                 <a href="ident?i=tp">tp</a>-&gt;rx_opt.mss_clamp = <a href="ident?i=tp">tp</a>-&gt;rx_opt.user_mss;
<a name="L3069" href="source/net/ipv4/tcp_output.c#L3069">3069</a>         <a href="ident?i=tp">tp</a>-&gt;max_window = 0;
<a name="L3070" href="source/net/ipv4/tcp_output.c#L3070">3070</a>         <a href="ident?i=tcp_mtup_init">tcp_mtup_init</a>(sk);
<a name="L3071" href="source/net/ipv4/tcp_output.c#L3071">3071</a>         <a href="ident?i=tcp_sync_mss">tcp_sync_mss</a>(sk, <a href="ident?i=dst_mtu">dst_mtu</a>(<a href="ident?i=dst">dst</a>));
<a name="L3072" href="source/net/ipv4/tcp_output.c#L3072">3072</a> 
<a name="L3073" href="source/net/ipv4/tcp_output.c#L3073">3073</a>         <a href="ident?i=tcp_ca_dst_init">tcp_ca_dst_init</a>(sk, <a href="ident?i=dst">dst</a>);
<a name="L3074" href="source/net/ipv4/tcp_output.c#L3074">3074</a> 
<a name="L3075" href="source/net/ipv4/tcp_output.c#L3075">3075</a>         if (!<a href="ident?i=tp">tp</a>-&gt;window_clamp)
<a name="L3076" href="source/net/ipv4/tcp_output.c#L3076">3076</a>                 <a href="ident?i=tp">tp</a>-&gt;window_clamp = <a href="ident?i=dst_metric">dst_metric</a>(<a href="ident?i=dst">dst</a>, <a href="ident?i=RTAX_WINDOW">RTAX_WINDOW</a>);
<a name="L3077" href="source/net/ipv4/tcp_output.c#L3077">3077</a>         <a href="ident?i=tp">tp</a>-&gt;advmss = <a href="ident?i=dst_metric_advmss">dst_metric_advmss</a>(<a href="ident?i=dst">dst</a>);
<a name="L3078" href="source/net/ipv4/tcp_output.c#L3078">3078</a>         if (<a href="ident?i=tp">tp</a>-&gt;rx_opt.user_mss &amp;&amp; <a href="ident?i=tp">tp</a>-&gt;rx_opt.user_mss &lt; <a href="ident?i=tp">tp</a>-&gt;advmss)
<a name="L3079" href="source/net/ipv4/tcp_output.c#L3079">3079</a>                 <a href="ident?i=tp">tp</a>-&gt;advmss = <a href="ident?i=tp">tp</a>-&gt;rx_opt.user_mss;
<a name="L3080" href="source/net/ipv4/tcp_output.c#L3080">3080</a> 
<a name="L3081" href="source/net/ipv4/tcp_output.c#L3081">3081</a>         <a href="ident?i=tcp_initialize_rcv_mss">tcp_initialize_rcv_mss</a>(sk);
<a name="L3082" href="source/net/ipv4/tcp_output.c#L3082">3082</a> 
<a name="L3083" href="source/net/ipv4/tcp_output.c#L3083">3083</a>         <b><i>/* limit the window selection if the user enforce a smaller rx buffer */</i></b>
<a name="L3084" href="source/net/ipv4/tcp_output.c#L3084">3084</a>         if (sk-&gt;sk_userlocks &amp; <a href="ident?i=SOCK_RCVBUF_LOCK">SOCK_RCVBUF_LOCK</a> &amp;&amp;
<a name="L3085" href="source/net/ipv4/tcp_output.c#L3085">3085</a>             (<a href="ident?i=tp">tp</a>-&gt;window_clamp &gt; <a href="ident?i=tcp_full_space">tcp_full_space</a>(sk) || <a href="ident?i=tp">tp</a>-&gt;window_clamp == 0))
<a name="L3086" href="source/net/ipv4/tcp_output.c#L3086">3086</a>                 <a href="ident?i=tp">tp</a>-&gt;window_clamp = <a href="ident?i=tcp_full_space">tcp_full_space</a>(sk);
<a name="L3087" href="source/net/ipv4/tcp_output.c#L3087">3087</a> 
<a name="L3088" href="source/net/ipv4/tcp_output.c#L3088">3088</a>         <a href="ident?i=tcp_select_initial_window">tcp_select_initial_window</a>(<a href="ident?i=tcp_full_space">tcp_full_space</a>(sk),
<a name="L3089" href="source/net/ipv4/tcp_output.c#L3089">3089</a>                                   <a href="ident?i=tp">tp</a>-&gt;advmss - (<a href="ident?i=tp">tp</a>-&gt;rx_opt.ts_recent_stamp ? <a href="ident?i=tp">tp</a>-&gt;tcp_header_len - sizeof(struct <a href="ident?i=tcphdr">tcphdr</a>) : 0),
<a name="L3090" href="source/net/ipv4/tcp_output.c#L3090">3090</a>                                   &amp;<a href="ident?i=tp">tp</a>-&gt;rcv_wnd,
<a name="L3091" href="source/net/ipv4/tcp_output.c#L3091">3091</a>                                   &amp;<a href="ident?i=tp">tp</a>-&gt;window_clamp,
<a name="L3092" href="source/net/ipv4/tcp_output.c#L3092">3092</a>                                   <a href="ident?i=sysctl_tcp_window_scaling">sysctl_tcp_window_scaling</a>,
<a name="L3093" href="source/net/ipv4/tcp_output.c#L3093">3093</a>                                   &amp;rcv_wscale,
<a name="L3094" href="source/net/ipv4/tcp_output.c#L3094">3094</a>                                   <a href="ident?i=dst_metric">dst_metric</a>(<a href="ident?i=dst">dst</a>, <a href="ident?i=RTAX_INITRWND">RTAX_INITRWND</a>));
<a name="L3095" href="source/net/ipv4/tcp_output.c#L3095">3095</a> 
<a name="L3096" href="source/net/ipv4/tcp_output.c#L3096">3096</a>         <a href="ident?i=tp">tp</a>-&gt;rx_opt.rcv_wscale = rcv_wscale;
<a name="L3097" href="source/net/ipv4/tcp_output.c#L3097">3097</a>         <a href="ident?i=tp">tp</a>-&gt;rcv_ssthresh = <a href="ident?i=tp">tp</a>-&gt;rcv_wnd;
<a name="L3098" href="source/net/ipv4/tcp_output.c#L3098">3098</a> 
<a name="L3099" href="source/net/ipv4/tcp_output.c#L3099">3099</a>         sk-&gt;sk_err = 0;
<a name="L3100" href="source/net/ipv4/tcp_output.c#L3100">3100</a>         <a href="ident?i=sock_reset_flag">sock_reset_flag</a>(sk, SOCK_DONE);
<a name="L3101" href="source/net/ipv4/tcp_output.c#L3101">3101</a>         <a href="ident?i=tp">tp</a>-&gt;snd_wnd = 0;
<a name="L3102" href="source/net/ipv4/tcp_output.c#L3102">3102</a>         <a href="ident?i=tcp_init_wl">tcp_init_wl</a>(<a href="ident?i=tp">tp</a>, 0);
<a name="L3103" href="source/net/ipv4/tcp_output.c#L3103">3103</a>         <a href="ident?i=tp">tp</a>-&gt;snd_una = <a href="ident?i=tp">tp</a>-&gt;write_seq;
<a name="L3104" href="source/net/ipv4/tcp_output.c#L3104">3104</a>         <a href="ident?i=tp">tp</a>-&gt;snd_sml = <a href="ident?i=tp">tp</a>-&gt;write_seq;
<a name="L3105" href="source/net/ipv4/tcp_output.c#L3105">3105</a>         <a href="ident?i=tp">tp</a>-&gt;snd_up = <a href="ident?i=tp">tp</a>-&gt;write_seq;
<a name="L3106" href="source/net/ipv4/tcp_output.c#L3106">3106</a>         <a href="ident?i=tp">tp</a>-&gt;snd_nxt = <a href="ident?i=tp">tp</a>-&gt;write_seq;
<a name="L3107" href="source/net/ipv4/tcp_output.c#L3107">3107</a> 
<a name="L3108" href="source/net/ipv4/tcp_output.c#L3108">3108</a>         if (<a href="ident?i=likely">likely</a>(!<a href="ident?i=tp">tp</a>-&gt;repair))
<a name="L3109" href="source/net/ipv4/tcp_output.c#L3109">3109</a>                 <a href="ident?i=tp">tp</a>-&gt;rcv_nxt = 0;
<a name="L3110" href="source/net/ipv4/tcp_output.c#L3110">3110</a>         else
<a name="L3111" href="source/net/ipv4/tcp_output.c#L3111">3111</a>                 <a href="ident?i=tp">tp</a>-&gt;rcv_tstamp = <a href="ident?i=tcp_time_stamp">tcp_time_stamp</a>;
<a name="L3112" href="source/net/ipv4/tcp_output.c#L3112">3112</a>         <a href="ident?i=tp">tp</a>-&gt;rcv_wup = <a href="ident?i=tp">tp</a>-&gt;rcv_nxt;
<a name="L3113" href="source/net/ipv4/tcp_output.c#L3113">3113</a>         <a href="ident?i=tp">tp</a>-&gt;copied_seq = <a href="ident?i=tp">tp</a>-&gt;rcv_nxt;
<a name="L3114" href="source/net/ipv4/tcp_output.c#L3114">3114</a> 
<a name="L3115" href="source/net/ipv4/tcp_output.c#L3115">3115</a>         <a href="ident?i=inet_csk">inet_csk</a>(sk)-&gt;icsk_rto = <a href="ident?i=TCP_TIMEOUT_INIT">TCP_TIMEOUT_INIT</a>;
<a name="L3116" href="source/net/ipv4/tcp_output.c#L3116">3116</a>         <a href="ident?i=inet_csk">inet_csk</a>(sk)-&gt;icsk_retransmits = 0;
<a name="L3117" href="source/net/ipv4/tcp_output.c#L3117">3117</a>         <a href="ident?i=tcp_clear_retrans">tcp_clear_retrans</a>(<a href="ident?i=tp">tp</a>);
<a name="L3118" href="source/net/ipv4/tcp_output.c#L3118">3118</a> }
<a name="L3119" href="source/net/ipv4/tcp_output.c#L3119">3119</a> 
<a name="L3120" href="source/net/ipv4/tcp_output.c#L3120">3120</a> static void <a href="ident?i=tcp_connect_queue_skb">tcp_connect_queue_skb</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L3121" href="source/net/ipv4/tcp_output.c#L3121">3121</a> {
<a name="L3122" href="source/net/ipv4/tcp_output.c#L3122">3122</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L3123" href="source/net/ipv4/tcp_output.c#L3123">3123</a>         struct <a href="ident?i=tcp_skb_cb">tcp_skb_cb</a> *<a href="ident?i=tcb">tcb</a> = <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>);
<a name="L3124" href="source/net/ipv4/tcp_output.c#L3124">3124</a> 
<a name="L3125" href="source/net/ipv4/tcp_output.c#L3125">3125</a>         <a href="ident?i=tcb">tcb</a>-&gt;end_seq += <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a>;
<a name="L3126" href="source/net/ipv4/tcp_output.c#L3126">3126</a>         <a href="ident?i=__skb_header_release">__skb_header_release</a>(<a href="ident?i=skb">skb</a>);
<a name="L3127" href="source/net/ipv4/tcp_output.c#L3127">3127</a>         <a href="ident?i=__tcp_add_write_queue_tail">__tcp_add_write_queue_tail</a>(sk, <a href="ident?i=skb">skb</a>);
<a name="L3128" href="source/net/ipv4/tcp_output.c#L3128">3128</a>         sk-&gt;sk_wmem_queued += <a href="ident?i=skb">skb</a>-&gt;truesize;
<a name="L3129" href="source/net/ipv4/tcp_output.c#L3129">3129</a>         <a href="ident?i=sk_mem_charge">sk_mem_charge</a>(sk, <a href="ident?i=skb">skb</a>-&gt;truesize);
<a name="L3130" href="source/net/ipv4/tcp_output.c#L3130">3130</a>         <a href="ident?i=tp">tp</a>-&gt;write_seq = <a href="ident?i=tcb">tcb</a>-&gt;end_seq;
<a name="L3131" href="source/net/ipv4/tcp_output.c#L3131">3131</a>         <a href="ident?i=tp">tp</a>-&gt;packets_out += <a href="ident?i=tcp_skb_pcount">tcp_skb_pcount</a>(<a href="ident?i=skb">skb</a>);
<a name="L3132" href="source/net/ipv4/tcp_output.c#L3132">3132</a> }
<a name="L3133" href="source/net/ipv4/tcp_output.c#L3133">3133</a> 
<a name="L3134" href="source/net/ipv4/tcp_output.c#L3134">3134</a> <b><i>/* Build and send a SYN with data and (cached) Fast Open cookie. However,</i></b>
<a name="L3135" href="source/net/ipv4/tcp_output.c#L3135">3135</a> <b><i> * queue a data-only packet after the regular SYN, such that regular SYNs</i></b>
<a name="L3136" href="source/net/ipv4/tcp_output.c#L3136">3136</a> <b><i> * are retransmitted on timeouts. Also if the remote SYN-ACK acknowledges</i></b>
<a name="L3137" href="source/net/ipv4/tcp_output.c#L3137">3137</a> <b><i> * only the SYN sequence, the data are retransmitted in the first ACK.</i></b>
<a name="L3138" href="source/net/ipv4/tcp_output.c#L3138">3138</a> <b><i> * If cookie is not cached or other error occurs, falls back to send a</i></b>
<a name="L3139" href="source/net/ipv4/tcp_output.c#L3139">3139</a> <b><i> * regular SYN with Fast Open cookie request option.</i></b>
<a name="L3140" href="source/net/ipv4/tcp_output.c#L3140">3140</a> <b><i> */</i></b>
<a name="L3141" href="source/net/ipv4/tcp_output.c#L3141">3141</a> static int <a href="ident?i=tcp_send_syn_data">tcp_send_syn_data</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=sk_buff">sk_buff</a> *syn)
<a name="L3142" href="source/net/ipv4/tcp_output.c#L3142">3142</a> {
<a name="L3143" href="source/net/ipv4/tcp_output.c#L3143">3143</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L3144" href="source/net/ipv4/tcp_output.c#L3144">3144</a>         struct <a href="ident?i=tcp_fastopen_request">tcp_fastopen_request</a> *fo = <a href="ident?i=tp">tp</a>-&gt;fastopen_req;
<a name="L3145" href="source/net/ipv4/tcp_output.c#L3145">3145</a>         int syn_loss = 0, <a href="ident?i=space">space</a>, <a href="ident?i=err">err</a> = 0, copied;
<a name="L3146" href="source/net/ipv4/tcp_output.c#L3146">3146</a>         unsigned long last_syn_loss = 0;
<a name="L3147" href="source/net/ipv4/tcp_output.c#L3147">3147</a>         struct <a href="ident?i=sk_buff">sk_buff</a> *syn_data;
<a name="L3148" href="source/net/ipv4/tcp_output.c#L3148">3148</a> 
<a name="L3149" href="source/net/ipv4/tcp_output.c#L3149">3149</a>         <a href="ident?i=tp">tp</a>-&gt;rx_opt.mss_clamp = <a href="ident?i=tp">tp</a>-&gt;advmss;  <b><i>/* If MSS is not cached */</i></b>
<a name="L3150" href="source/net/ipv4/tcp_output.c#L3150">3150</a>         <a href="ident?i=tcp_fastopen_cache_get">tcp_fastopen_cache_get</a>(sk, &amp;<a href="ident?i=tp">tp</a>-&gt;rx_opt.mss_clamp, &amp;fo-&gt;cookie,
<a name="L3151" href="source/net/ipv4/tcp_output.c#L3151">3151</a>                                &amp;syn_loss, &amp;last_syn_loss);
<a name="L3152" href="source/net/ipv4/tcp_output.c#L3152">3152</a>         <b><i>/* Recurring FO SYN losses: revert to regular handshake temporarily */</i></b>
<a name="L3153" href="source/net/ipv4/tcp_output.c#L3153">3153</a>         if (syn_loss &gt; 1 &amp;&amp;
<a name="L3154" href="source/net/ipv4/tcp_output.c#L3154">3154</a>             <a href="ident?i=time_before">time_before</a>(<a href="ident?i=jiffies">jiffies</a>, last_syn_loss + (60*<a href="ident?i=HZ">HZ</a> &lt;&lt; syn_loss))) {
<a name="L3155" href="source/net/ipv4/tcp_output.c#L3155">3155</a>                 fo-&gt;cookie.<a href="ident?i=len">len</a> = -1;
<a name="L3156" href="source/net/ipv4/tcp_output.c#L3156">3156</a>                 goto fallback;
<a name="L3157" href="source/net/ipv4/tcp_output.c#L3157">3157</a>         }
<a name="L3158" href="source/net/ipv4/tcp_output.c#L3158">3158</a> 
<a name="L3159" href="source/net/ipv4/tcp_output.c#L3159">3159</a>         if (<a href="ident?i=sysctl_tcp_fastopen">sysctl_tcp_fastopen</a> &amp; <a href="ident?i=TFO_CLIENT_NO_COOKIE">TFO_CLIENT_NO_COOKIE</a>)
<a name="L3160" href="source/net/ipv4/tcp_output.c#L3160">3160</a>                 fo-&gt;cookie.<a href="ident?i=len">len</a> = -1;
<a name="L3161" href="source/net/ipv4/tcp_output.c#L3161">3161</a>         else if (fo-&gt;cookie.<a href="ident?i=len">len</a> &lt;= 0)
<a name="L3162" href="source/net/ipv4/tcp_output.c#L3162">3162</a>                 goto fallback;
<a name="L3163" href="source/net/ipv4/tcp_output.c#L3163">3163</a> 
<a name="L3164" href="source/net/ipv4/tcp_output.c#L3164">3164</a>         <b><i>/* MSS for SYN-data is based on cached MSS and bounded by PMTU and</i></b>
<a name="L3165" href="source/net/ipv4/tcp_output.c#L3165">3165</a> <b><i>         * user-MSS. Reserve maximum option space for middleboxes that add</i></b>
<a name="L3166" href="source/net/ipv4/tcp_output.c#L3166">3166</a> <b><i>         * private TCP options. The cost is reduced data space in SYN :(</i></b>
<a name="L3167" href="source/net/ipv4/tcp_output.c#L3167">3167</a> <b><i>         */</i></b>
<a name="L3168" href="source/net/ipv4/tcp_output.c#L3168">3168</a>         if (<a href="ident?i=tp">tp</a>-&gt;rx_opt.user_mss &amp;&amp; <a href="ident?i=tp">tp</a>-&gt;rx_opt.user_mss &lt; <a href="ident?i=tp">tp</a>-&gt;rx_opt.mss_clamp)
<a name="L3169" href="source/net/ipv4/tcp_output.c#L3169">3169</a>                 <a href="ident?i=tp">tp</a>-&gt;rx_opt.mss_clamp = <a href="ident?i=tp">tp</a>-&gt;rx_opt.user_mss;
<a name="L3170" href="source/net/ipv4/tcp_output.c#L3170">3170</a>         <a href="ident?i=space">space</a> = <a href="ident?i=__tcp_mtu_to_mss">__tcp_mtu_to_mss</a>(sk, <a href="ident?i=inet_csk">inet_csk</a>(sk)-&gt;icsk_pmtu_cookie) -
<a name="L3171" href="source/net/ipv4/tcp_output.c#L3171">3171</a>                 <a href="ident?i=MAX_TCP_OPTION_SPACE">MAX_TCP_OPTION_SPACE</a>;
<a name="L3172" href="source/net/ipv4/tcp_output.c#L3172">3172</a> 
<a name="L3173" href="source/net/ipv4/tcp_output.c#L3173">3173</a>         <a href="ident?i=space">space</a> = <a href="ident?i=min_t">min_t</a>(<a href="ident?i=size_t">size_t</a>, <a href="ident?i=space">space</a>, fo-&gt;<a href="ident?i=size">size</a>);
<a name="L3174" href="source/net/ipv4/tcp_output.c#L3174">3174</a> 
<a name="L3175" href="source/net/ipv4/tcp_output.c#L3175">3175</a>         <b><i>/* limit to order-0 allocations */</i></b>
<a name="L3176" href="source/net/ipv4/tcp_output.c#L3176">3176</a>         <a href="ident?i=space">space</a> = <a href="ident?i=min_t">min_t</a>(<a href="ident?i=size_t">size_t</a>, <a href="ident?i=space">space</a>, <a href="ident?i=SKB_MAX_HEAD">SKB_MAX_HEAD</a>(<a href="ident?i=MAX_TCP_HEADER">MAX_TCP_HEADER</a>));
<a name="L3177" href="source/net/ipv4/tcp_output.c#L3177">3177</a> 
<a name="L3178" href="source/net/ipv4/tcp_output.c#L3178">3178</a>         syn_data = <a href="ident?i=sk_stream_alloc_skb">sk_stream_alloc_skb</a>(sk, <a href="ident?i=space">space</a>, sk-&gt;sk_allocation);
<a name="L3179" href="source/net/ipv4/tcp_output.c#L3179">3179</a>         if (!syn_data)
<a name="L3180" href="source/net/ipv4/tcp_output.c#L3180">3180</a>                 goto fallback;
<a name="L3181" href="source/net/ipv4/tcp_output.c#L3181">3181</a>         syn_data-&gt;ip_summed = <a href="ident?i=CHECKSUM_PARTIAL">CHECKSUM_PARTIAL</a>;
<a name="L3182" href="source/net/ipv4/tcp_output.c#L3182">3182</a>         <a href="ident?i=memcpy">memcpy</a>(syn_data-&gt;<a href="ident?i=cb">cb</a>, syn-&gt;<a href="ident?i=cb">cb</a>, sizeof(syn-&gt;<a href="ident?i=cb">cb</a>));
<a name="L3183" href="source/net/ipv4/tcp_output.c#L3183">3183</a>         copied = <a href="ident?i=copy_from_iter">copy_from_iter</a>(<a href="ident?i=skb_put">skb_put</a>(syn_data, <a href="ident?i=space">space</a>), <a href="ident?i=space">space</a>,
<a name="L3184" href="source/net/ipv4/tcp_output.c#L3184">3184</a>                                 &amp;fo-&gt;<a href="ident?i=data">data</a>-&gt;msg_iter);
<a name="L3185" href="source/net/ipv4/tcp_output.c#L3185">3185</a>         if (<a href="ident?i=unlikely">unlikely</a>(!copied)) {
<a name="L3186" href="source/net/ipv4/tcp_output.c#L3186">3186</a>                 <a href="ident?i=kfree_skb">kfree_skb</a>(syn_data);
<a name="L3187" href="source/net/ipv4/tcp_output.c#L3187">3187</a>                 goto fallback;
<a name="L3188" href="source/net/ipv4/tcp_output.c#L3188">3188</a>         }
<a name="L3189" href="source/net/ipv4/tcp_output.c#L3189">3189</a>         if (copied != <a href="ident?i=space">space</a>) {
<a name="L3190" href="source/net/ipv4/tcp_output.c#L3190">3190</a>                 <a href="ident?i=skb_trim">skb_trim</a>(syn_data, copied);
<a name="L3191" href="source/net/ipv4/tcp_output.c#L3191">3191</a>                 <a href="ident?i=space">space</a> = copied;
<a name="L3192" href="source/net/ipv4/tcp_output.c#L3192">3192</a>         }
<a name="L3193" href="source/net/ipv4/tcp_output.c#L3193">3193</a> 
<a name="L3194" href="source/net/ipv4/tcp_output.c#L3194">3194</a>         <b><i>/* No more data pending in inet_wait_for_connect() */</i></b>
<a name="L3195" href="source/net/ipv4/tcp_output.c#L3195">3195</a>         if (<a href="ident?i=space">space</a> == fo-&gt;<a href="ident?i=size">size</a>)
<a name="L3196" href="source/net/ipv4/tcp_output.c#L3196">3196</a>                 fo-&gt;<a href="ident?i=data">data</a> = <a href="ident?i=NULL">NULL</a>;
<a name="L3197" href="source/net/ipv4/tcp_output.c#L3197">3197</a>         fo-&gt;copied = <a href="ident?i=space">space</a>;
<a name="L3198" href="source/net/ipv4/tcp_output.c#L3198">3198</a> 
<a name="L3199" href="source/net/ipv4/tcp_output.c#L3199">3199</a>         <a href="ident?i=tcp_connect_queue_skb">tcp_connect_queue_skb</a>(sk, syn_data);
<a name="L3200" href="source/net/ipv4/tcp_output.c#L3200">3200</a> 
<a name="L3201" href="source/net/ipv4/tcp_output.c#L3201">3201</a>         <a href="ident?i=err">err</a> = <a href="ident?i=tcp_transmit_skb">tcp_transmit_skb</a>(sk, syn_data, 1, sk-&gt;sk_allocation);
<a name="L3202" href="source/net/ipv4/tcp_output.c#L3202">3202</a> 
<a name="L3203" href="source/net/ipv4/tcp_output.c#L3203">3203</a>         syn-&gt;<a href="ident?i=skb_mstamp">skb_mstamp</a> = syn_data-&gt;<a href="ident?i=skb_mstamp">skb_mstamp</a>;
<a name="L3204" href="source/net/ipv4/tcp_output.c#L3204">3204</a> 
<a name="L3205" href="source/net/ipv4/tcp_output.c#L3205">3205</a>         <b><i>/* Now full SYN+DATA was cloned and sent (or not),</i></b>
<a name="L3206" href="source/net/ipv4/tcp_output.c#L3206">3206</a> <b><i>         * remove the SYN from the original skb (syn_data)</i></b>
<a name="L3207" href="source/net/ipv4/tcp_output.c#L3207">3207</a> <b><i>         * we keep in write queue in case of a retransmit, as we</i></b>
<a name="L3208" href="source/net/ipv4/tcp_output.c#L3208">3208</a> <b><i>         * also have the SYN packet (with no data) in the same queue.</i></b>
<a name="L3209" href="source/net/ipv4/tcp_output.c#L3209">3209</a> <b><i>         */</i></b>
<a name="L3210" href="source/net/ipv4/tcp_output.c#L3210">3210</a>         <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(syn_data)-&gt;<a href="ident?i=seq">seq</a>++;
<a name="L3211" href="source/net/ipv4/tcp_output.c#L3211">3211</a>         <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(syn_data)-&gt;tcp_flags = <a href="ident?i=TCPHDR_ACK">TCPHDR_ACK</a> | <a href="ident?i=TCPHDR_PSH">TCPHDR_PSH</a>;
<a name="L3212" href="source/net/ipv4/tcp_output.c#L3212">3212</a>         if (!<a href="ident?i=err">err</a>) {
<a name="L3213" href="source/net/ipv4/tcp_output.c#L3213">3213</a>                 <a href="ident?i=tp">tp</a>-&gt;syn_data = (fo-&gt;copied &gt; 0);
<a name="L3214" href="source/net/ipv4/tcp_output.c#L3214">3214</a>                 <a href="ident?i=NET_INC_STATS">NET_INC_STATS</a>(<a href="ident?i=sock_net">sock_net</a>(sk), LINUX_MIB_TCPORIGDATASENT);
<a name="L3215" href="source/net/ipv4/tcp_output.c#L3215">3215</a>                 goto <a href="ident?i=done">done</a>;
<a name="L3216" href="source/net/ipv4/tcp_output.c#L3216">3216</a>         }
<a name="L3217" href="source/net/ipv4/tcp_output.c#L3217">3217</a> 
<a name="L3218" href="source/net/ipv4/tcp_output.c#L3218">3218</a> fallback:
<a name="L3219" href="source/net/ipv4/tcp_output.c#L3219">3219</a>         <b><i>/* Send a regular SYN with Fast Open cookie request option */</i></b>
<a name="L3220" href="source/net/ipv4/tcp_output.c#L3220">3220</a>         if (fo-&gt;cookie.<a href="ident?i=len">len</a> &gt; 0)
<a name="L3221" href="source/net/ipv4/tcp_output.c#L3221">3221</a>                 fo-&gt;cookie.<a href="ident?i=len">len</a> = 0;
<a name="L3222" href="source/net/ipv4/tcp_output.c#L3222">3222</a>         <a href="ident?i=err">err</a> = <a href="ident?i=tcp_transmit_skb">tcp_transmit_skb</a>(sk, syn, 1, sk-&gt;sk_allocation);
<a name="L3223" href="source/net/ipv4/tcp_output.c#L3223">3223</a>         if (<a href="ident?i=err">err</a>)
<a name="L3224" href="source/net/ipv4/tcp_output.c#L3224">3224</a>                 <a href="ident?i=tp">tp</a>-&gt;syn_fastopen = 0;
<a name="L3225" href="source/net/ipv4/tcp_output.c#L3225">3225</a> <a href="ident?i=done">done</a>:
<a name="L3226" href="source/net/ipv4/tcp_output.c#L3226">3226</a>         fo-&gt;cookie.<a href="ident?i=len">len</a> = -1;  <b><i>/* Exclude Fast Open option for SYN retries */</i></b>
<a name="L3227" href="source/net/ipv4/tcp_output.c#L3227">3227</a>         return <a href="ident?i=err">err</a>;
<a name="L3228" href="source/net/ipv4/tcp_output.c#L3228">3228</a> }
<a name="L3229" href="source/net/ipv4/tcp_output.c#L3229">3229</a> 
<a name="L3230" href="source/net/ipv4/tcp_output.c#L3230">3230</a> <b><i>/* Build a SYN and send it off. */</i></b>
<a name="L3231" href="source/net/ipv4/tcp_output.c#L3231">3231</a> int <a href="ident?i=tcp_connect">tcp_connect</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L3232" href="source/net/ipv4/tcp_output.c#L3232">3232</a> {
<a name="L3233" href="source/net/ipv4/tcp_output.c#L3233">3233</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L3234" href="source/net/ipv4/tcp_output.c#L3234">3234</a>         struct <a href="ident?i=sk_buff">sk_buff</a> *buff;
<a name="L3235" href="source/net/ipv4/tcp_output.c#L3235">3235</a>         int <a href="ident?i=err">err</a>;
<a name="L3236" href="source/net/ipv4/tcp_output.c#L3236">3236</a> 
<a name="L3237" href="source/net/ipv4/tcp_output.c#L3237">3237</a>         <a href="ident?i=tcp_connect_init">tcp_connect_init</a>(sk);
<a name="L3238" href="source/net/ipv4/tcp_output.c#L3238">3238</a> 
<a name="L3239" href="source/net/ipv4/tcp_output.c#L3239">3239</a>         if (<a href="ident?i=unlikely">unlikely</a>(<a href="ident?i=tp">tp</a>-&gt;repair)) {
<a name="L3240" href="source/net/ipv4/tcp_output.c#L3240">3240</a>                 <a href="ident?i=tcp_finish_connect">tcp_finish_connect</a>(sk, <a href="ident?i=NULL">NULL</a>);
<a name="L3241" href="source/net/ipv4/tcp_output.c#L3241">3241</a>                 return 0;
<a name="L3242" href="source/net/ipv4/tcp_output.c#L3242">3242</a>         }
<a name="L3243" href="source/net/ipv4/tcp_output.c#L3243">3243</a> 
<a name="L3244" href="source/net/ipv4/tcp_output.c#L3244">3244</a>         buff = <a href="ident?i=sk_stream_alloc_skb">sk_stream_alloc_skb</a>(sk, 0, sk-&gt;sk_allocation);
<a name="L3245" href="source/net/ipv4/tcp_output.c#L3245">3245</a>         if (<a href="ident?i=unlikely">unlikely</a>(!buff))
<a name="L3246" href="source/net/ipv4/tcp_output.c#L3246">3246</a>                 return -<a href="ident?i=ENOBUFS">ENOBUFS</a>;
<a name="L3247" href="source/net/ipv4/tcp_output.c#L3247">3247</a> 
<a name="L3248" href="source/net/ipv4/tcp_output.c#L3248">3248</a>         <a href="ident?i=tcp_init_nondata_skb">tcp_init_nondata_skb</a>(buff, <a href="ident?i=tp">tp</a>-&gt;write_seq++, <a href="ident?i=TCPHDR_SYN">TCPHDR_SYN</a>);
<a name="L3249" href="source/net/ipv4/tcp_output.c#L3249">3249</a>         <a href="ident?i=tp">tp</a>-&gt;retrans_stamp = <a href="ident?i=tcp_time_stamp">tcp_time_stamp</a>;
<a name="L3250" href="source/net/ipv4/tcp_output.c#L3250">3250</a>         <a href="ident?i=tcp_connect_queue_skb">tcp_connect_queue_skb</a>(sk, buff);
<a name="L3251" href="source/net/ipv4/tcp_output.c#L3251">3251</a>         <a href="ident?i=tcp_ecn_send_syn">tcp_ecn_send_syn</a>(sk, buff);
<a name="L3252" href="source/net/ipv4/tcp_output.c#L3252">3252</a> 
<a name="L3253" href="source/net/ipv4/tcp_output.c#L3253">3253</a>         <b><i>/* Send off SYN; include data in Fast Open. */</i></b>
<a name="L3254" href="source/net/ipv4/tcp_output.c#L3254">3254</a>         <a href="ident?i=err">err</a> = <a href="ident?i=tp">tp</a>-&gt;fastopen_req ? <a href="ident?i=tcp_send_syn_data">tcp_send_syn_data</a>(sk, buff) :
<a name="L3255" href="source/net/ipv4/tcp_output.c#L3255">3255</a>               <a href="ident?i=tcp_transmit_skb">tcp_transmit_skb</a>(sk, buff, 1, sk-&gt;sk_allocation);
<a name="L3256" href="source/net/ipv4/tcp_output.c#L3256">3256</a>         if (<a href="ident?i=err">err</a> == -<a href="ident?i=ECONNREFUSED">ECONNREFUSED</a>)
<a name="L3257" href="source/net/ipv4/tcp_output.c#L3257">3257</a>                 return <a href="ident?i=err">err</a>;
<a name="L3258" href="source/net/ipv4/tcp_output.c#L3258">3258</a> 
<a name="L3259" href="source/net/ipv4/tcp_output.c#L3259">3259</a>         <b><i>/* We change tp-&gt;snd_nxt after the tcp_transmit_skb() call</i></b>
<a name="L3260" href="source/net/ipv4/tcp_output.c#L3260">3260</a> <b><i>         * in order to make this packet get counted in tcpOutSegs.</i></b>
<a name="L3261" href="source/net/ipv4/tcp_output.c#L3261">3261</a> <b><i>         */</i></b>
<a name="L3262" href="source/net/ipv4/tcp_output.c#L3262">3262</a>         <a href="ident?i=tp">tp</a>-&gt;snd_nxt = <a href="ident?i=tp">tp</a>-&gt;write_seq;
<a name="L3263" href="source/net/ipv4/tcp_output.c#L3263">3263</a>         <a href="ident?i=tp">tp</a>-&gt;pushed_seq = <a href="ident?i=tp">tp</a>-&gt;write_seq;
<a name="L3264" href="source/net/ipv4/tcp_output.c#L3264">3264</a>         <a href="ident?i=TCP_INC_STATS">TCP_INC_STATS</a>(<a href="ident?i=sock_net">sock_net</a>(sk), TCP_MIB_ACTIVEOPENS);
<a name="L3265" href="source/net/ipv4/tcp_output.c#L3265">3265</a> 
<a name="L3266" href="source/net/ipv4/tcp_output.c#L3266">3266</a>         <b><i>/* Timer for repeating the SYN until an answer. */</i></b>
<a name="L3267" href="source/net/ipv4/tcp_output.c#L3267">3267</a>         <a href="ident?i=inet_csk_reset_xmit_timer">inet_csk_reset_xmit_timer</a>(sk, <a href="ident?i=ICSK_TIME_RETRANS">ICSK_TIME_RETRANS</a>,
<a name="L3268" href="source/net/ipv4/tcp_output.c#L3268">3268</a>                                   <a href="ident?i=inet_csk">inet_csk</a>(sk)-&gt;icsk_rto, <a href="ident?i=TCP_RTO_MAX">TCP_RTO_MAX</a>);
<a name="L3269" href="source/net/ipv4/tcp_output.c#L3269">3269</a>         return 0;
<a name="L3270" href="source/net/ipv4/tcp_output.c#L3270">3270</a> }
<a name="L3271" href="source/net/ipv4/tcp_output.c#L3271">3271</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=tcp_connect">tcp_connect</a>);
<a name="L3272" href="source/net/ipv4/tcp_output.c#L3272">3272</a> 
<a name="L3273" href="source/net/ipv4/tcp_output.c#L3273">3273</a> <b><i>/* Send out a delayed ack, the caller does the policy checking</i></b>
<a name="L3274" href="source/net/ipv4/tcp_output.c#L3274">3274</a> <b><i> * to see if we should even be here.  See tcp_input.c:tcp_ack_snd_check()</i></b>
<a name="L3275" href="source/net/ipv4/tcp_output.c#L3275">3275</a> <b><i> * for details.</i></b>
<a name="L3276" href="source/net/ipv4/tcp_output.c#L3276">3276</a> <b><i> */</i></b>
<a name="L3277" href="source/net/ipv4/tcp_output.c#L3277">3277</a> void <a href="ident?i=tcp_send_delayed_ack">tcp_send_delayed_ack</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L3278" href="source/net/ipv4/tcp_output.c#L3278">3278</a> {
<a name="L3279" href="source/net/ipv4/tcp_output.c#L3279">3279</a>         struct <a href="ident?i=inet_connection_sock">inet_connection_sock</a> *icsk = <a href="ident?i=inet_csk">inet_csk</a>(sk);
<a name="L3280" href="source/net/ipv4/tcp_output.c#L3280">3280</a>         int ato = icsk-&gt;icsk_ack.ato;
<a name="L3281" href="source/net/ipv4/tcp_output.c#L3281">3281</a>         unsigned long <a href="ident?i=timeout">timeout</a>;
<a name="L3282" href="source/net/ipv4/tcp_output.c#L3282">3282</a> 
<a name="L3283" href="source/net/ipv4/tcp_output.c#L3283">3283</a>         <a href="ident?i=tcp_ca_event">tcp_ca_event</a>(sk, CA_EVENT_DELAYED_ACK);
<a name="L3284" href="source/net/ipv4/tcp_output.c#L3284">3284</a> 
<a name="L3285" href="source/net/ipv4/tcp_output.c#L3285">3285</a>         if (ato &gt; <a href="ident?i=TCP_DELACK_MIN">TCP_DELACK_MIN</a>) {
<a name="L3286" href="source/net/ipv4/tcp_output.c#L3286">3286</a>                 const struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L3287" href="source/net/ipv4/tcp_output.c#L3287">3287</a>                 int max_ato = <a href="ident?i=HZ">HZ</a> / 2;
<a name="L3288" href="source/net/ipv4/tcp_output.c#L3288">3288</a> 
<a name="L3289" href="source/net/ipv4/tcp_output.c#L3289">3289</a>                 if (icsk-&gt;icsk_ack.pingpong ||
<a name="L3290" href="source/net/ipv4/tcp_output.c#L3290">3290</a>                     (icsk-&gt;icsk_ack.<a href="ident?i=pending">pending</a> &amp; ICSK_ACK_PUSHED))
<a name="L3291" href="source/net/ipv4/tcp_output.c#L3291">3291</a>                         max_ato = <a href="ident?i=TCP_DELACK_MAX">TCP_DELACK_MAX</a>;
<a name="L3292" href="source/net/ipv4/tcp_output.c#L3292">3292</a> 
<a name="L3293" href="source/net/ipv4/tcp_output.c#L3293">3293</a>                 <b><i>/* Slow path, intersegment interval is "high". */</i></b>
<a name="L3294" href="source/net/ipv4/tcp_output.c#L3294">3294</a> 
<a name="L3295" href="source/net/ipv4/tcp_output.c#L3295">3295</a>                 <b><i>/* If some rtt estimate is known, use it to bound delayed ack.</i></b>
<a name="L3296" href="source/net/ipv4/tcp_output.c#L3296">3296</a> <b><i>                 * Do not use inet_csk(sk)-&gt;icsk_rto here, use results of rtt measurements</i></b>
<a name="L3297" href="source/net/ipv4/tcp_output.c#L3297">3297</a> <b><i>                 * directly.</i></b>
<a name="L3298" href="source/net/ipv4/tcp_output.c#L3298">3298</a> <b><i>                 */</i></b>
<a name="L3299" href="source/net/ipv4/tcp_output.c#L3299">3299</a>                 if (<a href="ident?i=tp">tp</a>-&gt;srtt_us) {
<a name="L3300" href="source/net/ipv4/tcp_output.c#L3300">3300</a>                         int rtt = <a href="ident?i=max_t">max_t</a>(int, <a href="ident?i=usecs_to_jiffies">usecs_to_jiffies</a>(<a href="ident?i=tp">tp</a>-&gt;srtt_us &gt;&gt; 3),
<a name="L3301" href="source/net/ipv4/tcp_output.c#L3301">3301</a>                                         <a href="ident?i=TCP_DELACK_MIN">TCP_DELACK_MIN</a>);
<a name="L3302" href="source/net/ipv4/tcp_output.c#L3302">3302</a> 
<a name="L3303" href="source/net/ipv4/tcp_output.c#L3303">3303</a>                         if (rtt &lt; max_ato)
<a name="L3304" href="source/net/ipv4/tcp_output.c#L3304">3304</a>                                 max_ato = rtt;
<a name="L3305" href="source/net/ipv4/tcp_output.c#L3305">3305</a>                 }
<a name="L3306" href="source/net/ipv4/tcp_output.c#L3306">3306</a> 
<a name="L3307" href="source/net/ipv4/tcp_output.c#L3307">3307</a>                 ato = <a href="ident?i=min">min</a>(ato, max_ato);
<a name="L3308" href="source/net/ipv4/tcp_output.c#L3308">3308</a>         }
<a name="L3309" href="source/net/ipv4/tcp_output.c#L3309">3309</a> 
<a name="L3310" href="source/net/ipv4/tcp_output.c#L3310">3310</a>         <b><i>/* Stay within the limit we were given */</i></b>
<a name="L3311" href="source/net/ipv4/tcp_output.c#L3311">3311</a>         <a href="ident?i=timeout">timeout</a> = <a href="ident?i=jiffies">jiffies</a> + ato;
<a name="L3312" href="source/net/ipv4/tcp_output.c#L3312">3312</a> 
<a name="L3313" href="source/net/ipv4/tcp_output.c#L3313">3313</a>         <b><i>/* Use new timeout only if there wasn't a older one earlier. */</i></b>
<a name="L3314" href="source/net/ipv4/tcp_output.c#L3314">3314</a>         if (icsk-&gt;icsk_ack.<a href="ident?i=pending">pending</a> &amp; ICSK_ACK_TIMER) {
<a name="L3315" href="source/net/ipv4/tcp_output.c#L3315">3315</a>                 <b><i>/* If delack timer was blocked or is about to expire,</i></b>
<a name="L3316" href="source/net/ipv4/tcp_output.c#L3316">3316</a> <b><i>                 * send ACK now.</i></b>
<a name="L3317" href="source/net/ipv4/tcp_output.c#L3317">3317</a> <b><i>                 */</i></b>
<a name="L3318" href="source/net/ipv4/tcp_output.c#L3318">3318</a>                 if (icsk-&gt;icsk_ack.blocked ||
<a name="L3319" href="source/net/ipv4/tcp_output.c#L3319">3319</a>                     <a href="ident?i=time_before_eq">time_before_eq</a>(icsk-&gt;icsk_ack.<a href="ident?i=timeout">timeout</a>, <a href="ident?i=jiffies">jiffies</a> + (ato &gt;&gt; 2))) {
<a name="L3320" href="source/net/ipv4/tcp_output.c#L3320">3320</a>                         <a href="ident?i=tcp_send_ack">tcp_send_ack</a>(sk);
<a name="L3321" href="source/net/ipv4/tcp_output.c#L3321">3321</a>                         return;
<a name="L3322" href="source/net/ipv4/tcp_output.c#L3322">3322</a>                 }
<a name="L3323" href="source/net/ipv4/tcp_output.c#L3323">3323</a> 
<a name="L3324" href="source/net/ipv4/tcp_output.c#L3324">3324</a>                 if (!<a href="ident?i=time_before">time_before</a>(<a href="ident?i=timeout">timeout</a>, icsk-&gt;icsk_ack.<a href="ident?i=timeout">timeout</a>))
<a name="L3325" href="source/net/ipv4/tcp_output.c#L3325">3325</a>                         <a href="ident?i=timeout">timeout</a> = icsk-&gt;icsk_ack.<a href="ident?i=timeout">timeout</a>;
<a name="L3326" href="source/net/ipv4/tcp_output.c#L3326">3326</a>         }
<a name="L3327" href="source/net/ipv4/tcp_output.c#L3327">3327</a>         icsk-&gt;icsk_ack.<a href="ident?i=pending">pending</a> |= ICSK_ACK_SCHED | ICSK_ACK_TIMER;
<a name="L3328" href="source/net/ipv4/tcp_output.c#L3328">3328</a>         icsk-&gt;icsk_ack.<a href="ident?i=timeout">timeout</a> = <a href="ident?i=timeout">timeout</a>;
<a name="L3329" href="source/net/ipv4/tcp_output.c#L3329">3329</a>         <a href="ident?i=sk_reset_timer">sk_reset_timer</a>(sk, &amp;icsk-&gt;icsk_delack_timer, <a href="ident?i=timeout">timeout</a>);
<a name="L3330" href="source/net/ipv4/tcp_output.c#L3330">3330</a> }
<a name="L3331" href="source/net/ipv4/tcp_output.c#L3331">3331</a> 
<a name="L3332" href="source/net/ipv4/tcp_output.c#L3332">3332</a> <b><i>/* This routine sends an ack and also updates the window. */</i></b>
<a name="L3333" href="source/net/ipv4/tcp_output.c#L3333">3333</a> void <a href="ident?i=tcp_send_ack">tcp_send_ack</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L3334" href="source/net/ipv4/tcp_output.c#L3334">3334</a> {
<a name="L3335" href="source/net/ipv4/tcp_output.c#L3335">3335</a>         struct <a href="ident?i=sk_buff">sk_buff</a> *buff;
<a name="L3336" href="source/net/ipv4/tcp_output.c#L3336">3336</a> 
<a name="L3337" href="source/net/ipv4/tcp_output.c#L3337">3337</a>         <b><i>/* If we have been reset, we may not send again. */</i></b>
<a name="L3338" href="source/net/ipv4/tcp_output.c#L3338">3338</a>         if (sk-&gt;<a href="ident?i=sk_state">sk_state</a> == TCP_CLOSE)
<a name="L3339" href="source/net/ipv4/tcp_output.c#L3339">3339</a>                 return;
<a name="L3340" href="source/net/ipv4/tcp_output.c#L3340">3340</a> 
<a name="L3341" href="source/net/ipv4/tcp_output.c#L3341">3341</a>         <a href="ident?i=tcp_ca_event">tcp_ca_event</a>(sk, CA_EVENT_NON_DELAYED_ACK);
<a name="L3342" href="source/net/ipv4/tcp_output.c#L3342">3342</a> 
<a name="L3343" href="source/net/ipv4/tcp_output.c#L3343">3343</a>         <b><i>/* We are not putting this on the write queue, so</i></b>
<a name="L3344" href="source/net/ipv4/tcp_output.c#L3344">3344</a> <b><i>         * tcp_transmit_skb() will set the ownership to this</i></b>
<a name="L3345" href="source/net/ipv4/tcp_output.c#L3345">3345</a> <b><i>         * sock.</i></b>
<a name="L3346" href="source/net/ipv4/tcp_output.c#L3346">3346</a> <b><i>         */</i></b>
<a name="L3347" href="source/net/ipv4/tcp_output.c#L3347">3347</a>         buff = <a href="ident?i=alloc_skb">alloc_skb</a>(<a href="ident?i=MAX_TCP_HEADER">MAX_TCP_HEADER</a>, <a href="ident?i=sk_gfp_atomic">sk_gfp_atomic</a>(sk, <a href="ident?i=GFP_ATOMIC">GFP_ATOMIC</a>));
<a name="L3348" href="source/net/ipv4/tcp_output.c#L3348">3348</a>         if (!buff) {
<a name="L3349" href="source/net/ipv4/tcp_output.c#L3349">3349</a>                 <a href="ident?i=inet_csk_schedule_ack">inet_csk_schedule_ack</a>(sk);
<a name="L3350" href="source/net/ipv4/tcp_output.c#L3350">3350</a>                 <a href="ident?i=inet_csk">inet_csk</a>(sk)-&gt;icsk_ack.ato = <a href="ident?i=TCP_ATO_MIN">TCP_ATO_MIN</a>;
<a name="L3351" href="source/net/ipv4/tcp_output.c#L3351">3351</a>                 <a href="ident?i=inet_csk_reset_xmit_timer">inet_csk_reset_xmit_timer</a>(sk, <a href="ident?i=ICSK_TIME_DACK">ICSK_TIME_DACK</a>,
<a name="L3352" href="source/net/ipv4/tcp_output.c#L3352">3352</a>                                           <a href="ident?i=TCP_DELACK_MAX">TCP_DELACK_MAX</a>, <a href="ident?i=TCP_RTO_MAX">TCP_RTO_MAX</a>);
<a name="L3353" href="source/net/ipv4/tcp_output.c#L3353">3353</a>                 return;
<a name="L3354" href="source/net/ipv4/tcp_output.c#L3354">3354</a>         }
<a name="L3355" href="source/net/ipv4/tcp_output.c#L3355">3355</a> 
<a name="L3356" href="source/net/ipv4/tcp_output.c#L3356">3356</a>         <b><i>/* Reserve space for headers and prepare control bits. */</i></b>
<a name="L3357" href="source/net/ipv4/tcp_output.c#L3357">3357</a>         <a href="ident?i=skb_reserve">skb_reserve</a>(buff, <a href="ident?i=MAX_TCP_HEADER">MAX_TCP_HEADER</a>);
<a name="L3358" href="source/net/ipv4/tcp_output.c#L3358">3358</a>         <a href="ident?i=tcp_init_nondata_skb">tcp_init_nondata_skb</a>(buff, <a href="ident?i=tcp_acceptable_seq">tcp_acceptable_seq</a>(sk), <a href="ident?i=TCPHDR_ACK">TCPHDR_ACK</a>);
<a name="L3359" href="source/net/ipv4/tcp_output.c#L3359">3359</a> 
<a name="L3360" href="source/net/ipv4/tcp_output.c#L3360">3360</a>         <b><i>/* We do not want pure acks influencing TCP Small Queues or fq/pacing</i></b>
<a name="L3361" href="source/net/ipv4/tcp_output.c#L3361">3361</a> <b><i>         * too much.</i></b>
<a name="L3362" href="source/net/ipv4/tcp_output.c#L3362">3362</a> <b><i>         * SKB_TRUESIZE(max(1 .. 66, MAX_TCP_HEADER)) is unfortunately ~784</i></b>
<a name="L3363" href="source/net/ipv4/tcp_output.c#L3363">3363</a> <b><i>         * We also avoid tcp_wfree() overhead (cache line miss accessing</i></b>
<a name="L3364" href="source/net/ipv4/tcp_output.c#L3364">3364</a> <b><i>         * tp-&gt;tsq_flags) by using regular sock_wfree()</i></b>
<a name="L3365" href="source/net/ipv4/tcp_output.c#L3365">3365</a> <b><i>         */</i></b>
<a name="L3366" href="source/net/ipv4/tcp_output.c#L3366">3366</a>         <a href="ident?i=skb_set_tcp_pure_ack">skb_set_tcp_pure_ack</a>(buff);
<a name="L3367" href="source/net/ipv4/tcp_output.c#L3367">3367</a> 
<a name="L3368" href="source/net/ipv4/tcp_output.c#L3368">3368</a>         <b><i>/* Send it off, this clears delayed acks for us. */</i></b>
<a name="L3369" href="source/net/ipv4/tcp_output.c#L3369">3369</a>         <a href="ident?i=skb_mstamp_get">skb_mstamp_get</a>(&amp;buff-&gt;<a href="ident?i=skb_mstamp">skb_mstamp</a>);
<a name="L3370" href="source/net/ipv4/tcp_output.c#L3370">3370</a>         <a href="ident?i=tcp_transmit_skb">tcp_transmit_skb</a>(sk, buff, 0, <a href="ident?i=sk_gfp_atomic">sk_gfp_atomic</a>(sk, <a href="ident?i=GFP_ATOMIC">GFP_ATOMIC</a>));
<a name="L3371" href="source/net/ipv4/tcp_output.c#L3371">3371</a> }
<a name="L3372" href="source/net/ipv4/tcp_output.c#L3372">3372</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=tcp_send_ack">tcp_send_ack</a>);
<a name="L3373" href="source/net/ipv4/tcp_output.c#L3373">3373</a> 
<a name="L3374" href="source/net/ipv4/tcp_output.c#L3374">3374</a> <b><i>/* This routine sends a packet with an out of date sequence</i></b>
<a name="L3375" href="source/net/ipv4/tcp_output.c#L3375">3375</a> <b><i> * number. It assumes the other end will try to ack it.</i></b>
<a name="L3376" href="source/net/ipv4/tcp_output.c#L3376">3376</a> <b><i> *</i></b>
<a name="L3377" href="source/net/ipv4/tcp_output.c#L3377">3377</a> <b><i> * Question: what should we make while urgent mode?</i></b>
<a name="L3378" href="source/net/ipv4/tcp_output.c#L3378">3378</a> <b><i> * 4.4BSD forces sending single byte of data. We cannot send</i></b>
<a name="L3379" href="source/net/ipv4/tcp_output.c#L3379">3379</a> <b><i> * out of window data, because we have SND.NXT==SND.MAX...</i></b>
<a name="L3380" href="source/net/ipv4/tcp_output.c#L3380">3380</a> <b><i> *</i></b>
<a name="L3381" href="source/net/ipv4/tcp_output.c#L3381">3381</a> <b><i> * Current solution: to send TWO zero-length segments in urgent mode:</i></b>
<a name="L3382" href="source/net/ipv4/tcp_output.c#L3382">3382</a> <b><i> * one is with SEG.SEQ=SND.UNA to deliver urgent pointer, another is</i></b>
<a name="L3383" href="source/net/ipv4/tcp_output.c#L3383">3383</a> <b><i> * out-of-date with SND.UNA-1 to probe window.</i></b>
<a name="L3384" href="source/net/ipv4/tcp_output.c#L3384">3384</a> <b><i> */</i></b>
<a name="L3385" href="source/net/ipv4/tcp_output.c#L3385">3385</a> static int <a href="ident?i=tcp_xmit_probe_skb">tcp_xmit_probe_skb</a>(struct <a href="ident?i=sock">sock</a> *sk, int urgent)
<a name="L3386" href="source/net/ipv4/tcp_output.c#L3386">3386</a> {
<a name="L3387" href="source/net/ipv4/tcp_output.c#L3387">3387</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L3388" href="source/net/ipv4/tcp_output.c#L3388">3388</a>         struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>;
<a name="L3389" href="source/net/ipv4/tcp_output.c#L3389">3389</a> 
<a name="L3390" href="source/net/ipv4/tcp_output.c#L3390">3390</a>         <b><i>/* We don't queue it, tcp_transmit_skb() sets ownership. */</i></b>
<a name="L3391" href="source/net/ipv4/tcp_output.c#L3391">3391</a>         <a href="ident?i=skb">skb</a> = <a href="ident?i=alloc_skb">alloc_skb</a>(<a href="ident?i=MAX_TCP_HEADER">MAX_TCP_HEADER</a>, <a href="ident?i=sk_gfp_atomic">sk_gfp_atomic</a>(sk, <a href="ident?i=GFP_ATOMIC">GFP_ATOMIC</a>));
<a name="L3392" href="source/net/ipv4/tcp_output.c#L3392">3392</a>         if (!<a href="ident?i=skb">skb</a>)
<a name="L3393" href="source/net/ipv4/tcp_output.c#L3393">3393</a>                 return -1;
<a name="L3394" href="source/net/ipv4/tcp_output.c#L3394">3394</a> 
<a name="L3395" href="source/net/ipv4/tcp_output.c#L3395">3395</a>         <b><i>/* Reserve space for headers and set control bits. */</i></b>
<a name="L3396" href="source/net/ipv4/tcp_output.c#L3396">3396</a>         <a href="ident?i=skb_reserve">skb_reserve</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=MAX_TCP_HEADER">MAX_TCP_HEADER</a>);
<a name="L3397" href="source/net/ipv4/tcp_output.c#L3397">3397</a>         <b><i>/* Use a previous sequence.  This should cause the other</i></b>
<a name="L3398" href="source/net/ipv4/tcp_output.c#L3398">3398</a> <b><i>         * end to send an ack.  Don't queue or clone SKB, just</i></b>
<a name="L3399" href="source/net/ipv4/tcp_output.c#L3399">3399</a> <b><i>         * send it.</i></b>
<a name="L3400" href="source/net/ipv4/tcp_output.c#L3400">3400</a> <b><i>         */</i></b>
<a name="L3401" href="source/net/ipv4/tcp_output.c#L3401">3401</a>         <a href="ident?i=tcp_init_nondata_skb">tcp_init_nondata_skb</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=tp">tp</a>-&gt;snd_una - !urgent, <a href="ident?i=TCPHDR_ACK">TCPHDR_ACK</a>);
<a name="L3402" href="source/net/ipv4/tcp_output.c#L3402">3402</a>         <a href="ident?i=skb_mstamp_get">skb_mstamp_get</a>(&amp;<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=skb_mstamp">skb_mstamp</a>);
<a name="L3403" href="source/net/ipv4/tcp_output.c#L3403">3403</a>         return <a href="ident?i=tcp_transmit_skb">tcp_transmit_skb</a>(sk, <a href="ident?i=skb">skb</a>, 0, <a href="ident?i=GFP_ATOMIC">GFP_ATOMIC</a>);
<a name="L3404" href="source/net/ipv4/tcp_output.c#L3404">3404</a> }
<a name="L3405" href="source/net/ipv4/tcp_output.c#L3405">3405</a> 
<a name="L3406" href="source/net/ipv4/tcp_output.c#L3406">3406</a> void <a href="ident?i=tcp_send_window_probe">tcp_send_window_probe</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L3407" href="source/net/ipv4/tcp_output.c#L3407">3407</a> {
<a name="L3408" href="source/net/ipv4/tcp_output.c#L3408">3408</a>         if (sk-&gt;<a href="ident?i=sk_state">sk_state</a> == TCP_ESTABLISHED) {
<a name="L3409" href="source/net/ipv4/tcp_output.c#L3409">3409</a>                 <a href="ident?i=tcp_sk">tcp_sk</a>(sk)-&gt;snd_wl1 = <a href="ident?i=tcp_sk">tcp_sk</a>(sk)-&gt;rcv_nxt - 1;
<a name="L3410" href="source/net/ipv4/tcp_output.c#L3410">3410</a>                 <a href="ident?i=tcp_xmit_probe_skb">tcp_xmit_probe_skb</a>(sk, 0);
<a name="L3411" href="source/net/ipv4/tcp_output.c#L3411">3411</a>         }
<a name="L3412" href="source/net/ipv4/tcp_output.c#L3412">3412</a> }
<a name="L3413" href="source/net/ipv4/tcp_output.c#L3413">3413</a> 
<a name="L3414" href="source/net/ipv4/tcp_output.c#L3414">3414</a> <b><i>/* Initiate keepalive or window probe from timer. */</i></b>
<a name="L3415" href="source/net/ipv4/tcp_output.c#L3415">3415</a> int <a href="ident?i=tcp_write_wakeup">tcp_write_wakeup</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L3416" href="source/net/ipv4/tcp_output.c#L3416">3416</a> {
<a name="L3417" href="source/net/ipv4/tcp_output.c#L3417">3417</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L3418" href="source/net/ipv4/tcp_output.c#L3418">3418</a>         struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>;
<a name="L3419" href="source/net/ipv4/tcp_output.c#L3419">3419</a> 
<a name="L3420" href="source/net/ipv4/tcp_output.c#L3420">3420</a>         if (sk-&gt;<a href="ident?i=sk_state">sk_state</a> == TCP_CLOSE)
<a name="L3421" href="source/net/ipv4/tcp_output.c#L3421">3421</a>                 return -1;
<a name="L3422" href="source/net/ipv4/tcp_output.c#L3422">3422</a> 
<a name="L3423" href="source/net/ipv4/tcp_output.c#L3423">3423</a>         <a href="ident?i=skb">skb</a> = <a href="ident?i=tcp_send_head">tcp_send_head</a>(sk);
<a name="L3424" href="source/net/ipv4/tcp_output.c#L3424">3424</a>         if (<a href="ident?i=skb">skb</a> &amp;&amp; <a href="ident?i=before">before</a>(<a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=seq">seq</a>, <a href="ident?i=tcp_wnd_end">tcp_wnd_end</a>(<a href="ident?i=tp">tp</a>))) {
<a name="L3425" href="source/net/ipv4/tcp_output.c#L3425">3425</a>                 int <a href="ident?i=err">err</a>;
<a name="L3426" href="source/net/ipv4/tcp_output.c#L3426">3426</a>                 unsigned int mss = <a href="ident?i=tcp_current_mss">tcp_current_mss</a>(sk);
<a name="L3427" href="source/net/ipv4/tcp_output.c#L3427">3427</a>                 unsigned int seg_size = <a href="ident?i=tcp_wnd_end">tcp_wnd_end</a>(<a href="ident?i=tp">tp</a>) - <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=seq">seq</a>;
<a name="L3428" href="source/net/ipv4/tcp_output.c#L3428">3428</a> 
<a name="L3429" href="source/net/ipv4/tcp_output.c#L3429">3429</a>                 if (<a href="ident?i=before">before</a>(<a href="ident?i=tp">tp</a>-&gt;pushed_seq, <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;end_seq))
<a name="L3430" href="source/net/ipv4/tcp_output.c#L3430">3430</a>                         <a href="ident?i=tp">tp</a>-&gt;pushed_seq = <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;end_seq;
<a name="L3431" href="source/net/ipv4/tcp_output.c#L3431">3431</a> 
<a name="L3432" href="source/net/ipv4/tcp_output.c#L3432">3432</a>                 <b><i>/* We are probing the opening of a window</i></b>
<a name="L3433" href="source/net/ipv4/tcp_output.c#L3433">3433</a> <b><i>                 * but the window size is != 0</i></b>
<a name="L3434" href="source/net/ipv4/tcp_output.c#L3434">3434</a> <b><i>                 * must have been a result SWS avoidance ( sender )</i></b>
<a name="L3435" href="source/net/ipv4/tcp_output.c#L3435">3435</a> <b><i>                 */</i></b>
<a name="L3436" href="source/net/ipv4/tcp_output.c#L3436">3436</a>                 if (seg_size &lt; <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;end_seq - <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=seq">seq</a> ||
<a name="L3437" href="source/net/ipv4/tcp_output.c#L3437">3437</a>                     <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a> &gt; mss) {
<a name="L3438" href="source/net/ipv4/tcp_output.c#L3438">3438</a>                         seg_size = <a href="ident?i=min">min</a>(seg_size, mss);
<a name="L3439" href="source/net/ipv4/tcp_output.c#L3439">3439</a>                         <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;tcp_flags |= <a href="ident?i=TCPHDR_PSH">TCPHDR_PSH</a>;
<a name="L3440" href="source/net/ipv4/tcp_output.c#L3440">3440</a>                         if (<a href="ident?i=tcp_fragment">tcp_fragment</a>(sk, <a href="ident?i=skb">skb</a>, seg_size, mss, <a href="ident?i=GFP_ATOMIC">GFP_ATOMIC</a>))
<a name="L3441" href="source/net/ipv4/tcp_output.c#L3441">3441</a>                                 return -1;
<a name="L3442" href="source/net/ipv4/tcp_output.c#L3442">3442</a>                 } else if (!<a href="ident?i=tcp_skb_pcount">tcp_skb_pcount</a>(<a href="ident?i=skb">skb</a>))
<a name="L3443" href="source/net/ipv4/tcp_output.c#L3443">3443</a>                         <a href="ident?i=tcp_set_skb_tso_segs">tcp_set_skb_tso_segs</a>(sk, <a href="ident?i=skb">skb</a>, mss);
<a name="L3444" href="source/net/ipv4/tcp_output.c#L3444">3444</a> 
<a name="L3445" href="source/net/ipv4/tcp_output.c#L3445">3445</a>                 <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;tcp_flags |= <a href="ident?i=TCPHDR_PSH">TCPHDR_PSH</a>;
<a name="L3446" href="source/net/ipv4/tcp_output.c#L3446">3446</a>                 <a href="ident?i=err">err</a> = <a href="ident?i=tcp_transmit_skb">tcp_transmit_skb</a>(sk, <a href="ident?i=skb">skb</a>, 1, <a href="ident?i=GFP_ATOMIC">GFP_ATOMIC</a>);
<a name="L3447" href="source/net/ipv4/tcp_output.c#L3447">3447</a>                 if (!<a href="ident?i=err">err</a>)
<a name="L3448" href="source/net/ipv4/tcp_output.c#L3448">3448</a>                         <a href="ident?i=tcp_event_new_data_sent">tcp_event_new_data_sent</a>(sk, <a href="ident?i=skb">skb</a>);
<a name="L3449" href="source/net/ipv4/tcp_output.c#L3449">3449</a>                 return <a href="ident?i=err">err</a>;
<a name="L3450" href="source/net/ipv4/tcp_output.c#L3450">3450</a>         } else {
<a name="L3451" href="source/net/ipv4/tcp_output.c#L3451">3451</a>                 if (<a href="ident?i=between">between</a>(<a href="ident?i=tp">tp</a>-&gt;snd_up, <a href="ident?i=tp">tp</a>-&gt;snd_una + 1, <a href="ident?i=tp">tp</a>-&gt;snd_una + 0xFFFF))
<a name="L3452" href="source/net/ipv4/tcp_output.c#L3452">3452</a>                         <a href="ident?i=tcp_xmit_probe_skb">tcp_xmit_probe_skb</a>(sk, 1);
<a name="L3453" href="source/net/ipv4/tcp_output.c#L3453">3453</a>                 return <a href="ident?i=tcp_xmit_probe_skb">tcp_xmit_probe_skb</a>(sk, 0);
<a name="L3454" href="source/net/ipv4/tcp_output.c#L3454">3454</a>         }
<a name="L3455" href="source/net/ipv4/tcp_output.c#L3455">3455</a> }
<a name="L3456" href="source/net/ipv4/tcp_output.c#L3456">3456</a> 
<a name="L3457" href="source/net/ipv4/tcp_output.c#L3457">3457</a> <b><i>/* A window probe timeout has occurred.  If window is not closed send</i></b>
<a name="L3458" href="source/net/ipv4/tcp_output.c#L3458">3458</a> <b><i> * a partial packet else a zero probe.</i></b>
<a name="L3459" href="source/net/ipv4/tcp_output.c#L3459">3459</a> <b><i> */</i></b>
<a name="L3460" href="source/net/ipv4/tcp_output.c#L3460">3460</a> void <a href="ident?i=tcp_send_probe0">tcp_send_probe0</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L3461" href="source/net/ipv4/tcp_output.c#L3461">3461</a> {
<a name="L3462" href="source/net/ipv4/tcp_output.c#L3462">3462</a>         struct <a href="ident?i=inet_connection_sock">inet_connection_sock</a> *icsk = <a href="ident?i=inet_csk">inet_csk</a>(sk);
<a name="L3463" href="source/net/ipv4/tcp_output.c#L3463">3463</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L3464" href="source/net/ipv4/tcp_output.c#L3464">3464</a>         unsigned long probe_max;
<a name="L3465" href="source/net/ipv4/tcp_output.c#L3465">3465</a>         int <a href="ident?i=err">err</a>;
<a name="L3466" href="source/net/ipv4/tcp_output.c#L3466">3466</a> 
<a name="L3467" href="source/net/ipv4/tcp_output.c#L3467">3467</a>         <a href="ident?i=err">err</a> = <a href="ident?i=tcp_write_wakeup">tcp_write_wakeup</a>(sk);
<a name="L3468" href="source/net/ipv4/tcp_output.c#L3468">3468</a> 
<a name="L3469" href="source/net/ipv4/tcp_output.c#L3469">3469</a>         if (<a href="ident?i=tp">tp</a>-&gt;packets_out || !<a href="ident?i=tcp_send_head">tcp_send_head</a>(sk)) {
<a name="L3470" href="source/net/ipv4/tcp_output.c#L3470">3470</a>                 <b><i>/* Cancel probe timer, if it is not required. */</i></b>
<a name="L3471" href="source/net/ipv4/tcp_output.c#L3471">3471</a>                 icsk-&gt;icsk_probes_out = 0;
<a name="L3472" href="source/net/ipv4/tcp_output.c#L3472">3472</a>                 icsk-&gt;icsk_backoff = 0;
<a name="L3473" href="source/net/ipv4/tcp_output.c#L3473">3473</a>                 return;
<a name="L3474" href="source/net/ipv4/tcp_output.c#L3474">3474</a>         }
<a name="L3475" href="source/net/ipv4/tcp_output.c#L3475">3475</a> 
<a name="L3476" href="source/net/ipv4/tcp_output.c#L3476">3476</a>         if (<a href="ident?i=err">err</a> &lt;= 0) {
<a name="L3477" href="source/net/ipv4/tcp_output.c#L3477">3477</a>                 if (icsk-&gt;icsk_backoff &lt; <a href="ident?i=sysctl_tcp_retries2">sysctl_tcp_retries2</a>)
<a name="L3478" href="source/net/ipv4/tcp_output.c#L3478">3478</a>                         icsk-&gt;icsk_backoff++;
<a name="L3479" href="source/net/ipv4/tcp_output.c#L3479">3479</a>                 icsk-&gt;icsk_probes_out++;
<a name="L3480" href="source/net/ipv4/tcp_output.c#L3480">3480</a>                 probe_max = <a href="ident?i=TCP_RTO_MAX">TCP_RTO_MAX</a>;
<a name="L3481" href="source/net/ipv4/tcp_output.c#L3481">3481</a>         } else {
<a name="L3482" href="source/net/ipv4/tcp_output.c#L3482">3482</a>                 <b><i>/* If packet was not sent due to local congestion,</i></b>
<a name="L3483" href="source/net/ipv4/tcp_output.c#L3483">3483</a> <b><i>                 * do not backoff and do not remember icsk_probes_out.</i></b>
<a name="L3484" href="source/net/ipv4/tcp_output.c#L3484">3484</a> <b><i>                 * Let local senders to fight for local resources.</i></b>
<a name="L3485" href="source/net/ipv4/tcp_output.c#L3485">3485</a> <b><i>                 *</i></b>
<a name="L3486" href="source/net/ipv4/tcp_output.c#L3486">3486</a> <b><i>                 * Use accumulated backoff yet.</i></b>
<a name="L3487" href="source/net/ipv4/tcp_output.c#L3487">3487</a> <b><i>                 */</i></b>
<a name="L3488" href="source/net/ipv4/tcp_output.c#L3488">3488</a>                 if (!icsk-&gt;icsk_probes_out)
<a name="L3489" href="source/net/ipv4/tcp_output.c#L3489">3489</a>                         icsk-&gt;icsk_probes_out = 1;
<a name="L3490" href="source/net/ipv4/tcp_output.c#L3490">3490</a>                 probe_max = <a href="ident?i=TCP_RESOURCE_PROBE_INTERVAL">TCP_RESOURCE_PROBE_INTERVAL</a>;
<a name="L3491" href="source/net/ipv4/tcp_output.c#L3491">3491</a>         }
<a name="L3492" href="source/net/ipv4/tcp_output.c#L3492">3492</a>         <a href="ident?i=inet_csk_reset_xmit_timer">inet_csk_reset_xmit_timer</a>(sk, <a href="ident?i=ICSK_TIME_PROBE0">ICSK_TIME_PROBE0</a>,
<a name="L3493" href="source/net/ipv4/tcp_output.c#L3493">3493</a>                                   <a href="ident?i=inet_csk_rto_backoff">inet_csk_rto_backoff</a>(icsk, probe_max),
<a name="L3494" href="source/net/ipv4/tcp_output.c#L3494">3494</a>                                   <a href="ident?i=TCP_RTO_MAX">TCP_RTO_MAX</a>);
<a name="L3495" href="source/net/ipv4/tcp_output.c#L3495">3495</a> }
<a name="L3496" href="source/net/ipv4/tcp_output.c#L3496">3496</a> 
<a name="L3497" href="source/net/ipv4/tcp_output.c#L3497">3497</a> int <a href="ident?i=tcp_rtx_synack">tcp_rtx_synack</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=request_sock">request_sock</a> *<a href="ident?i=req">req</a>)
<a name="L3498" href="source/net/ipv4/tcp_output.c#L3498">3498</a> {
<a name="L3499" href="source/net/ipv4/tcp_output.c#L3499">3499</a>         const struct <a href="ident?i=tcp_request_sock_ops">tcp_request_sock_ops</a> *af_ops = <a href="ident?i=tcp_rsk">tcp_rsk</a>(<a href="ident?i=req">req</a>)-&gt;af_specific;
<a name="L3500" href="source/net/ipv4/tcp_output.c#L3500">3500</a>         struct <a href="ident?i=flowi">flowi</a> fl;
<a name="L3501" href="source/net/ipv4/tcp_output.c#L3501">3501</a>         int <a href="ident?i=res">res</a>;
<a name="L3502" href="source/net/ipv4/tcp_output.c#L3502">3502</a> 
<a name="L3503" href="source/net/ipv4/tcp_output.c#L3503">3503</a>         <a href="ident?i=res">res</a> = af_ops-&gt;send_synack(sk, <a href="ident?i=NULL">NULL</a>, &amp;fl, <a href="ident?i=req">req</a>, 0, <a href="ident?i=NULL">NULL</a>);
<a name="L3504" href="source/net/ipv4/tcp_output.c#L3504">3504</a>         if (!<a href="ident?i=res">res</a>) {
<a name="L3505" href="source/net/ipv4/tcp_output.c#L3505">3505</a>                 <a href="ident?i=TCP_INC_STATS_BH">TCP_INC_STATS_BH</a>(<a href="ident?i=sock_net">sock_net</a>(sk), TCP_MIB_RETRANSSEGS);
<a name="L3506" href="source/net/ipv4/tcp_output.c#L3506">3506</a>                 <a href="ident?i=NET_INC_STATS_BH">NET_INC_STATS_BH</a>(<a href="ident?i=sock_net">sock_net</a>(sk), LINUX_MIB_TCPSYNRETRANS);
<a name="L3507" href="source/net/ipv4/tcp_output.c#L3507">3507</a>         }
<a name="L3508" href="source/net/ipv4/tcp_output.c#L3508">3508</a>         return <a href="ident?i=res">res</a>;
<a name="L3509" href="source/net/ipv4/tcp_output.c#L3509">3509</a> }
<a name="L3510" href="source/net/ipv4/tcp_output.c#L3510">3510</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=tcp_rtx_synack">tcp_rtx_synack</a>);
<a name="L3511" href="source/net/ipv4/tcp_output.c#L3511">3511</a> </pre></div><p>
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
