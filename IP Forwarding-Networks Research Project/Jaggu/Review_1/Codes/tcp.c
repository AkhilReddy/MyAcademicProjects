<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title>Linux/net/ipv4/tcp.c - Linux Cross Reference - Free Electrons</title>
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
		 &nbsp;&bull;&nbsp;<b><i>source navigation</i></b> &nbsp;&bull;&nbsp;<a href="diff/net/ipv4/tcp.c">diff markup</a> &nbsp;&bull;&nbsp;<a href="ident">identifier search</a> &nbsp;&bull;&nbsp;<a href="search">freetext search</a> &nbsp;&bull;&nbsp;
		</p>
	</div>
</div>

<div id="topbar">
  
  <p>Version: &nbsp;<a href="source/net/ipv4/tcp.c?v=2.0.40">2.0.40</a>&nbsp;<a href="source/net/ipv4/tcp.c?v=2.2.26">2.2.26</a>&nbsp;<a href="source/net/ipv4/tcp.c?v=2.4.37">2.4.37</a>&nbsp;<a href="source/net/ipv4/tcp.c?v=3.5">3.5</a>&nbsp;<a href="source/net/ipv4/tcp.c?v=3.6">3.6</a>&nbsp;<a href="source/net/ipv4/tcp.c?v=3.7">3.7</a>&nbsp;<a href="source/net/ipv4/tcp.c?v=3.8">3.8</a>&nbsp;<a href="source/net/ipv4/tcp.c?v=3.9">3.9</a>&nbsp;<a href="source/net/ipv4/tcp.c?v=3.10">3.10</a>&nbsp;<a href="source/net/ipv4/tcp.c?v=3.11">3.11</a>&nbsp;<a href="source/net/ipv4/tcp.c?v=3.12">3.12</a>&nbsp;<a href="source/net/ipv4/tcp.c?v=3.13">3.13</a>&nbsp;<a href="source/net/ipv4/tcp.c?v=3.14">3.14</a>&nbsp;<a href="source/net/ipv4/tcp.c?v=3.15">3.15</a>&nbsp;<a href="source/net/ipv4/tcp.c?v=3.16">3.16</a>&nbsp;<a href="source/net/ipv4/tcp.c?v=3.17">3.17</a>&nbsp;<a href="source/net/ipv4/tcp.c?v=3.18">3.18</a>&nbsp;<a href="source/net/ipv4/tcp.c?v=3.19">3.19</a>&nbsp;<a href="source/net/ipv4/tcp.c?v=4.0">4.0</a>&nbsp;<b><i>4.1</i></b></p>
  
</div>

<h1><a href="source/">Linux</a>/<a href="source/net/">net</a>/<a href="source/net/ipv4/">ipv4</a>/<a href="source/net/ipv4/tcp.c">tcp.c</a></h1>
<div id="lxrcode"><pre>  <a name="L1" href="source/net/ipv4/tcp.c#L1">1</a> <b><i>/*</i></b>
  <a name="L2" href="source/net/ipv4/tcp.c#L2">2</a> <b><i> * INET         An implementation of the TCP/IP protocol suite for the LINUX</i></b>
  <a name="L3" href="source/net/ipv4/tcp.c#L3">3</a> <b><i> *              operating system.  INET is implemented using the  BSD Socket</i></b>
  <a name="L4" href="source/net/ipv4/tcp.c#L4">4</a> <b><i> *              interface as the means of communication with the user level.</i></b>
  <a name="L5" href="source/net/ipv4/tcp.c#L5">5</a> <b><i> *</i></b>
  <a name="L6" href="source/net/ipv4/tcp.c#L6">6</a> <b><i> *              Implementation of the Transmission Control Protocol(TCP).</i></b>
  <a name="L7" href="source/net/ipv4/tcp.c#L7">7</a> <b><i> *</i></b>
  <a name="L8" href="source/net/ipv4/tcp.c#L8">8</a> <b><i> * Authors:     Ross Biro</i></b>
  <a name="L9" href="source/net/ipv4/tcp.c#L9">9</a> <b><i> *              Fred N. van Kempen, &lt;waltje@uWalt.NL.Mugnet.ORG&gt;</i></b>
 <a name="L10" href="source/net/ipv4/tcp.c#L10">10</a> <b><i> *              Mark Evans, &lt;evansmp@uhura.aston.ac.uk&gt;</i></b>
 <a name="L11" href="source/net/ipv4/tcp.c#L11">11</a> <b><i> *              Corey Minyard &lt;wf-rch!minyard@relay.EU.net&gt;</i></b>
 <a name="L12" href="source/net/ipv4/tcp.c#L12">12</a> <b><i> *              Florian La Roche, &lt;flla@stud.uni-sb.de&gt;</i></b>
 <a name="L13" href="source/net/ipv4/tcp.c#L13">13</a> <b><i> *              Charles Hedrick, &lt;hedrick@klinzhai.rutgers.edu&gt;</i></b>
 <a name="L14" href="source/net/ipv4/tcp.c#L14">14</a> <b><i> *              Linus Torvalds, &lt;torvalds@cs.helsinki.fi&gt;</i></b>
 <a name="L15" href="source/net/ipv4/tcp.c#L15">15</a> <b><i> *              Alan Cox, &lt;gw4pts@gw4pts.ampr.org&gt;</i></b>
 <a name="L16" href="source/net/ipv4/tcp.c#L16">16</a> <b><i> *              Matthew Dillon, &lt;dillon@apollo.west.oic.com&gt;</i></b>
 <a name="L17" href="source/net/ipv4/tcp.c#L17">17</a> <b><i> *              Arnt Gulbrandsen, &lt;agulbra@nvg.unit.no&gt;</i></b>
 <a name="L18" href="source/net/ipv4/tcp.c#L18">18</a> <b><i> *              Jorge Cwik, &lt;jorge@laser.satlink.net&gt;</i></b>
 <a name="L19" href="source/net/ipv4/tcp.c#L19">19</a> <b><i> *</i></b>
 <a name="L20" href="source/net/ipv4/tcp.c#L20">20</a> <b><i> * Fixes:</i></b>
 <a name="L21" href="source/net/ipv4/tcp.c#L21">21</a> <b><i> *              Alan Cox        :       Numerous verify_area() calls</i></b>
 <a name="L22" href="source/net/ipv4/tcp.c#L22">22</a> <b><i> *              Alan Cox        :       Set the ACK bit on a reset</i></b>
 <a name="L23" href="source/net/ipv4/tcp.c#L23">23</a> <b><i> *              Alan Cox        :       Stopped it crashing if it closed while</i></b>
 <a name="L24" href="source/net/ipv4/tcp.c#L24">24</a> <b><i> *                                      sk-&gt;inuse=1 and was trying to connect</i></b>
 <a name="L25" href="source/net/ipv4/tcp.c#L25">25</a> <b><i> *                                      (tcp_err()).</i></b>
 <a name="L26" href="source/net/ipv4/tcp.c#L26">26</a> <b><i> *              Alan Cox        :       All icmp error handling was broken</i></b>
 <a name="L27" href="source/net/ipv4/tcp.c#L27">27</a> <b><i> *                                      pointers passed where wrong and the</i></b>
 <a name="L28" href="source/net/ipv4/tcp.c#L28">28</a> <b><i> *                                      socket was looked up backwards. Nobody</i></b>
 <a name="L29" href="source/net/ipv4/tcp.c#L29">29</a> <b><i> *                                      tested any icmp error code obviously.</i></b>
 <a name="L30" href="source/net/ipv4/tcp.c#L30">30</a> <b><i> *              Alan Cox        :       tcp_err() now handled properly. It</i></b>
 <a name="L31" href="source/net/ipv4/tcp.c#L31">31</a> <b><i> *                                      wakes people on errors. poll</i></b>
 <a name="L32" href="source/net/ipv4/tcp.c#L32">32</a> <b><i> *                                      behaves and the icmp error race</i></b>
 <a name="L33" href="source/net/ipv4/tcp.c#L33">33</a> <b><i> *                                      has gone by moving it into sock.c</i></b>
 <a name="L34" href="source/net/ipv4/tcp.c#L34">34</a> <b><i> *              Alan Cox        :       tcp_send_reset() fixed to work for</i></b>
 <a name="L35" href="source/net/ipv4/tcp.c#L35">35</a> <b><i> *                                      everything not just packets for</i></b>
 <a name="L36" href="source/net/ipv4/tcp.c#L36">36</a> <b><i> *                                      unknown sockets.</i></b>
 <a name="L37" href="source/net/ipv4/tcp.c#L37">37</a> <b><i> *              Alan Cox        :       tcp option processing.</i></b>
 <a name="L38" href="source/net/ipv4/tcp.c#L38">38</a> <b><i> *              Alan Cox        :       Reset tweaked (still not 100%) [Had</i></b>
 <a name="L39" href="source/net/ipv4/tcp.c#L39">39</a> <b><i> *                                      syn rule wrong]</i></b>
 <a name="L40" href="source/net/ipv4/tcp.c#L40">40</a> <b><i> *              Herp Rosmanith  :       More reset fixes</i></b>
 <a name="L41" href="source/net/ipv4/tcp.c#L41">41</a> <b><i> *              Alan Cox        :       No longer acks invalid rst frames.</i></b>
 <a name="L42" href="source/net/ipv4/tcp.c#L42">42</a> <b><i> *                                      Acking any kind of RST is right out.</i></b>
 <a name="L43" href="source/net/ipv4/tcp.c#L43">43</a> <b><i> *              Alan Cox        :       Sets an ignore me flag on an rst</i></b>
 <a name="L44" href="source/net/ipv4/tcp.c#L44">44</a> <b><i> *                                      receive otherwise odd bits of prattle</i></b>
 <a name="L45" href="source/net/ipv4/tcp.c#L45">45</a> <b><i> *                                      escape still</i></b>
 <a name="L46" href="source/net/ipv4/tcp.c#L46">46</a> <b><i> *              Alan Cox        :       Fixed another acking RST frame bug.</i></b>
 <a name="L47" href="source/net/ipv4/tcp.c#L47">47</a> <b><i> *                                      Should stop LAN workplace lockups.</i></b>
 <a name="L48" href="source/net/ipv4/tcp.c#L48">48</a> <b><i> *              Alan Cox        :       Some tidyups using the new skb list</i></b>
 <a name="L49" href="source/net/ipv4/tcp.c#L49">49</a> <b><i> *                                      facilities</i></b>
 <a name="L50" href="source/net/ipv4/tcp.c#L50">50</a> <b><i> *              Alan Cox        :       sk-&gt;keepopen now seems to work</i></b>
 <a name="L51" href="source/net/ipv4/tcp.c#L51">51</a> <b><i> *              Alan Cox        :       Pulls options out correctly on accepts</i></b>
 <a name="L52" href="source/net/ipv4/tcp.c#L52">52</a> <b><i> *              Alan Cox        :       Fixed assorted sk-&gt;rqueue-&gt;next errors</i></b>
 <a name="L53" href="source/net/ipv4/tcp.c#L53">53</a> <b><i> *              Alan Cox        :       PSH doesn't end a TCP read. Switched a</i></b>
 <a name="L54" href="source/net/ipv4/tcp.c#L54">54</a> <b><i> *                                      bit to skb ops.</i></b>
 <a name="L55" href="source/net/ipv4/tcp.c#L55">55</a> <b><i> *              Alan Cox        :       Tidied tcp_data to avoid a potential</i></b>
 <a name="L56" href="source/net/ipv4/tcp.c#L56">56</a> <b><i> *                                      nasty.</i></b>
 <a name="L57" href="source/net/ipv4/tcp.c#L57">57</a> <b><i> *              Alan Cox        :       Added some better commenting, as the</i></b>
 <a name="L58" href="source/net/ipv4/tcp.c#L58">58</a> <b><i> *                                      tcp is hard to follow</i></b>
 <a name="L59" href="source/net/ipv4/tcp.c#L59">59</a> <b><i> *              Alan Cox        :       Removed incorrect check for 20 * psh</i></b>
 <a name="L60" href="source/net/ipv4/tcp.c#L60">60</a> <b><i> *      Michael O'Reilly        :       ack &lt; copied bug fix.</i></b>
 <a name="L61" href="source/net/ipv4/tcp.c#L61">61</a> <b><i> *      Johannes Stille         :       Misc tcp fixes (not all in yet).</i></b>
 <a name="L62" href="source/net/ipv4/tcp.c#L62">62</a> <b><i> *              Alan Cox        :       FIN with no memory -&gt; CRASH</i></b>
 <a name="L63" href="source/net/ipv4/tcp.c#L63">63</a> <b><i> *              Alan Cox        :       Added socket option proto entries.</i></b>
 <a name="L64" href="source/net/ipv4/tcp.c#L64">64</a> <b><i> *                                      Also added awareness of them to accept.</i></b>
 <a name="L65" href="source/net/ipv4/tcp.c#L65">65</a> <b><i> *              Alan Cox        :       Added TCP options (SOL_TCP)</i></b>
 <a name="L66" href="source/net/ipv4/tcp.c#L66">66</a> <b><i> *              Alan Cox        :       Switched wakeup calls to callbacks,</i></b>
 <a name="L67" href="source/net/ipv4/tcp.c#L67">67</a> <b><i> *                                      so the kernel can layer network</i></b>
 <a name="L68" href="source/net/ipv4/tcp.c#L68">68</a> <b><i> *                                      sockets.</i></b>
 <a name="L69" href="source/net/ipv4/tcp.c#L69">69</a> <b><i> *              Alan Cox        :       Use ip_tos/ip_ttl settings.</i></b>
 <a name="L70" href="source/net/ipv4/tcp.c#L70">70</a> <b><i> *              Alan Cox        :       Handle FIN (more) properly (we hope).</i></b>
 <a name="L71" href="source/net/ipv4/tcp.c#L71">71</a> <b><i> *              Alan Cox        :       RST frames sent on unsynchronised</i></b>
 <a name="L72" href="source/net/ipv4/tcp.c#L72">72</a> <b><i> *                                      state ack error.</i></b>
 <a name="L73" href="source/net/ipv4/tcp.c#L73">73</a> <b><i> *              Alan Cox        :       Put in missing check for SYN bit.</i></b>
 <a name="L74" href="source/net/ipv4/tcp.c#L74">74</a> <b><i> *              Alan Cox        :       Added tcp_select_window() aka NET2E</i></b>
 <a name="L75" href="source/net/ipv4/tcp.c#L75">75</a> <b><i> *                                      window non shrink trick.</i></b>
 <a name="L76" href="source/net/ipv4/tcp.c#L76">76</a> <b><i> *              Alan Cox        :       Added a couple of small NET2E timer</i></b>
 <a name="L77" href="source/net/ipv4/tcp.c#L77">77</a> <b><i> *                                      fixes</i></b>
 <a name="L78" href="source/net/ipv4/tcp.c#L78">78</a> <b><i> *              Charles Hedrick :       TCP fixes</i></b>
 <a name="L79" href="source/net/ipv4/tcp.c#L79">79</a> <b><i> *              Toomas Tamm     :       TCP window fixes</i></b>
 <a name="L80" href="source/net/ipv4/tcp.c#L80">80</a> <b><i> *              Alan Cox        :       Small URG fix to rlogin ^C ack fight</i></b>
 <a name="L81" href="source/net/ipv4/tcp.c#L81">81</a> <b><i> *              Charles Hedrick :       Rewrote most of it to actually work</i></b>
 <a name="L82" href="source/net/ipv4/tcp.c#L82">82</a> <b><i> *              Linus           :       Rewrote tcp_read() and URG handling</i></b>
 <a name="L83" href="source/net/ipv4/tcp.c#L83">83</a> <b><i> *                                      completely</i></b>
 <a name="L84" href="source/net/ipv4/tcp.c#L84">84</a> <b><i> *              Gerhard Koerting:       Fixed some missing timer handling</i></b>
 <a name="L85" href="source/net/ipv4/tcp.c#L85">85</a> <b><i> *              Matthew Dillon  :       Reworked TCP machine states as per RFC</i></b>
 <a name="L86" href="source/net/ipv4/tcp.c#L86">86</a> <b><i> *              Gerhard Koerting:       PC/TCP workarounds</i></b>
 <a name="L87" href="source/net/ipv4/tcp.c#L87">87</a> <b><i> *              Adam Caldwell   :       Assorted timer/timing errors</i></b>
 <a name="L88" href="source/net/ipv4/tcp.c#L88">88</a> <b><i> *              Matthew Dillon  :       Fixed another RST bug</i></b>
 <a name="L89" href="source/net/ipv4/tcp.c#L89">89</a> <b><i> *              Alan Cox        :       Move to kernel side addressing changes.</i></b>
 <a name="L90" href="source/net/ipv4/tcp.c#L90">90</a> <b><i> *              Alan Cox        :       Beginning work on TCP fastpathing</i></b>
 <a name="L91" href="source/net/ipv4/tcp.c#L91">91</a> <b><i> *                                      (not yet usable)</i></b>
 <a name="L92" href="source/net/ipv4/tcp.c#L92">92</a> <b><i> *              Arnt Gulbrandsen:       Turbocharged tcp_check() routine.</i></b>
 <a name="L93" href="source/net/ipv4/tcp.c#L93">93</a> <b><i> *              Alan Cox        :       TCP fast path debugging</i></b>
 <a name="L94" href="source/net/ipv4/tcp.c#L94">94</a> <b><i> *              Alan Cox        :       Window clamping</i></b>
 <a name="L95" href="source/net/ipv4/tcp.c#L95">95</a> <b><i> *              Michael Riepe   :       Bug in tcp_check()</i></b>
 <a name="L96" href="source/net/ipv4/tcp.c#L96">96</a> <b><i> *              Matt Dillon     :       More TCP improvements and RST bug fixes</i></b>
 <a name="L97" href="source/net/ipv4/tcp.c#L97">97</a> <b><i> *              Matt Dillon     :       Yet more small nasties remove from the</i></b>
 <a name="L98" href="source/net/ipv4/tcp.c#L98">98</a> <b><i> *                                      TCP code (Be very nice to this man if</i></b>
 <a name="L99" href="source/net/ipv4/tcp.c#L99">99</a> <b><i> *                                      tcp finally works 100%) 8)</i></b>
<a name="L100" href="source/net/ipv4/tcp.c#L100">100</a> <b><i> *              Alan Cox        :       BSD accept semantics.</i></b>
<a name="L101" href="source/net/ipv4/tcp.c#L101">101</a> <b><i> *              Alan Cox        :       Reset on closedown bug.</i></b>
<a name="L102" href="source/net/ipv4/tcp.c#L102">102</a> <b><i> *      Peter De Schrijver      :       ENOTCONN check missing in tcp_sendto().</i></b>
<a name="L103" href="source/net/ipv4/tcp.c#L103">103</a> <b><i> *              Michael Pall    :       Handle poll() after URG properly in</i></b>
<a name="L104" href="source/net/ipv4/tcp.c#L104">104</a> <b><i> *                                      all cases.</i></b>
<a name="L105" href="source/net/ipv4/tcp.c#L105">105</a> <b><i> *              Michael Pall    :       Undo the last fix in tcp_read_urg()</i></b>
<a name="L106" href="source/net/ipv4/tcp.c#L106">106</a> <b><i> *                                      (multi URG PUSH broke rlogin).</i></b>
<a name="L107" href="source/net/ipv4/tcp.c#L107">107</a> <b><i> *              Michael Pall    :       Fix the multi URG PUSH problem in</i></b>
<a name="L108" href="source/net/ipv4/tcp.c#L108">108</a> <b><i> *                                      tcp_readable(), poll() after URG</i></b>
<a name="L109" href="source/net/ipv4/tcp.c#L109">109</a> <b><i> *                                      works now.</i></b>
<a name="L110" href="source/net/ipv4/tcp.c#L110">110</a> <b><i> *              Michael Pall    :       recv(...,MSG_OOB) never blocks in the</i></b>
<a name="L111" href="source/net/ipv4/tcp.c#L111">111</a> <b><i> *                                      BSD api.</i></b>
<a name="L112" href="source/net/ipv4/tcp.c#L112">112</a> <b><i> *              Alan Cox        :       Changed the semantics of sk-&gt;socket to</i></b>
<a name="L113" href="source/net/ipv4/tcp.c#L113">113</a> <b><i> *                                      fix a race and a signal problem with</i></b>
<a name="L114" href="source/net/ipv4/tcp.c#L114">114</a> <b><i> *                                      accept() and async I/O.</i></b>
<a name="L115" href="source/net/ipv4/tcp.c#L115">115</a> <b><i> *              Alan Cox        :       Relaxed the rules on tcp_sendto().</i></b>
<a name="L116" href="source/net/ipv4/tcp.c#L116">116</a> <b><i> *              Yury Shevchuk   :       Really fixed accept() blocking problem.</i></b>
<a name="L117" href="source/net/ipv4/tcp.c#L117">117</a> <b><i> *              Craig I. Hagan  :       Allow for BSD compatible TIME_WAIT for</i></b>
<a name="L118" href="source/net/ipv4/tcp.c#L118">118</a> <b><i> *                                      clients/servers which listen in on</i></b>
<a name="L119" href="source/net/ipv4/tcp.c#L119">119</a> <b><i> *                                      fixed ports.</i></b>
<a name="L120" href="source/net/ipv4/tcp.c#L120">120</a> <b><i> *              Alan Cox        :       Cleaned the above up and shrank it to</i></b>
<a name="L121" href="source/net/ipv4/tcp.c#L121">121</a> <b><i> *                                      a sensible code size.</i></b>
<a name="L122" href="source/net/ipv4/tcp.c#L122">122</a> <b><i> *              Alan Cox        :       Self connect lockup fix.</i></b>
<a name="L123" href="source/net/ipv4/tcp.c#L123">123</a> <b><i> *              Alan Cox        :       No connect to multicast.</i></b>
<a name="L124" href="source/net/ipv4/tcp.c#L124">124</a> <b><i> *              Ross Biro       :       Close unaccepted children on master</i></b>
<a name="L125" href="source/net/ipv4/tcp.c#L125">125</a> <b><i> *                                      socket close.</i></b>
<a name="L126" href="source/net/ipv4/tcp.c#L126">126</a> <b><i> *              Alan Cox        :       Reset tracing code.</i></b>
<a name="L127" href="source/net/ipv4/tcp.c#L127">127</a> <b><i> *              Alan Cox        :       Spurious resets on shutdown.</i></b>
<a name="L128" href="source/net/ipv4/tcp.c#L128">128</a> <b><i> *              Alan Cox        :       Giant 15 minute/60 second timer error</i></b>
<a name="L129" href="source/net/ipv4/tcp.c#L129">129</a> <b><i> *              Alan Cox        :       Small whoops in polling before an</i></b>
<a name="L130" href="source/net/ipv4/tcp.c#L130">130</a> <b><i> *                                      accept.</i></b>
<a name="L131" href="source/net/ipv4/tcp.c#L131">131</a> <b><i> *              Alan Cox        :       Kept the state trace facility since</i></b>
<a name="L132" href="source/net/ipv4/tcp.c#L132">132</a> <b><i> *                                      it's handy for debugging.</i></b>
<a name="L133" href="source/net/ipv4/tcp.c#L133">133</a> <b><i> *              Alan Cox        :       More reset handler fixes.</i></b>
<a name="L134" href="source/net/ipv4/tcp.c#L134">134</a> <b><i> *              Alan Cox        :       Started rewriting the code based on</i></b>
<a name="L135" href="source/net/ipv4/tcp.c#L135">135</a> <b><i> *                                      the RFC's for other useful protocol</i></b>
<a name="L136" href="source/net/ipv4/tcp.c#L136">136</a> <b><i> *                                      references see: Comer, KA9Q NOS, and</i></b>
<a name="L137" href="source/net/ipv4/tcp.c#L137">137</a> <b><i> *                                      for a reference on the difference</i></b>
<a name="L138" href="source/net/ipv4/tcp.c#L138">138</a> <b><i> *                                      between specifications and how BSD</i></b>
<a name="L139" href="source/net/ipv4/tcp.c#L139">139</a> <b><i> *                                      works see the 4.4lite source.</i></b>
<a name="L140" href="source/net/ipv4/tcp.c#L140">140</a> <b><i> *              A.N.Kuznetsov   :       Don't time wait on completion of tidy</i></b>
<a name="L141" href="source/net/ipv4/tcp.c#L141">141</a> <b><i> *                                      close.</i></b>
<a name="L142" href="source/net/ipv4/tcp.c#L142">142</a> <b><i> *              Linus Torvalds  :       Fin/Shutdown &amp; copied_seq changes.</i></b>
<a name="L143" href="source/net/ipv4/tcp.c#L143">143</a> <b><i> *              Linus Torvalds  :       Fixed BSD port reuse to work first syn</i></b>
<a name="L144" href="source/net/ipv4/tcp.c#L144">144</a> <b><i> *              Alan Cox        :       Reimplemented timers as per the RFC</i></b>
<a name="L145" href="source/net/ipv4/tcp.c#L145">145</a> <b><i> *                                      and using multiple timers for sanity.</i></b>
<a name="L146" href="source/net/ipv4/tcp.c#L146">146</a> <b><i> *              Alan Cox        :       Small bug fixes, and a lot of new</i></b>
<a name="L147" href="source/net/ipv4/tcp.c#L147">147</a> <b><i> *                                      comments.</i></b>
<a name="L148" href="source/net/ipv4/tcp.c#L148">148</a> <b><i> *              Alan Cox        :       Fixed dual reader crash by locking</i></b>
<a name="L149" href="source/net/ipv4/tcp.c#L149">149</a> <b><i> *                                      the buffers (much like datagram.c)</i></b>
<a name="L150" href="source/net/ipv4/tcp.c#L150">150</a> <b><i> *              Alan Cox        :       Fixed stuck sockets in probe. A probe</i></b>
<a name="L151" href="source/net/ipv4/tcp.c#L151">151</a> <b><i> *                                      now gets fed up of retrying without</i></b>
<a name="L152" href="source/net/ipv4/tcp.c#L152">152</a> <b><i> *                                      (even a no space) answer.</i></b>
<a name="L153" href="source/net/ipv4/tcp.c#L153">153</a> <b><i> *              Alan Cox        :       Extracted closing code better</i></b>
<a name="L154" href="source/net/ipv4/tcp.c#L154">154</a> <b><i> *              Alan Cox        :       Fixed the closing state machine to</i></b>
<a name="L155" href="source/net/ipv4/tcp.c#L155">155</a> <b><i> *                                      resemble the RFC.</i></b>
<a name="L156" href="source/net/ipv4/tcp.c#L156">156</a> <b><i> *              Alan Cox        :       More 'per spec' fixes.</i></b>
<a name="L157" href="source/net/ipv4/tcp.c#L157">157</a> <b><i> *              Jorge Cwik      :       Even faster checksumming.</i></b>
<a name="L158" href="source/net/ipv4/tcp.c#L158">158</a> <b><i> *              Alan Cox        :       tcp_data() doesn't ack illegal PSH</i></b>
<a name="L159" href="source/net/ipv4/tcp.c#L159">159</a> <b><i> *                                      only frames. At least one pc tcp stack</i></b>
<a name="L160" href="source/net/ipv4/tcp.c#L160">160</a> <b><i> *                                      generates them.</i></b>
<a name="L161" href="source/net/ipv4/tcp.c#L161">161</a> <b><i> *              Alan Cox        :       Cache last socket.</i></b>
<a name="L162" href="source/net/ipv4/tcp.c#L162">162</a> <b><i> *              Alan Cox        :       Per route irtt.</i></b>
<a name="L163" href="source/net/ipv4/tcp.c#L163">163</a> <b><i> *              Matt Day        :       poll()-&gt;select() match BSD precisely on error</i></b>
<a name="L164" href="source/net/ipv4/tcp.c#L164">164</a> <b><i> *              Alan Cox        :       New buffers</i></b>
<a name="L165" href="source/net/ipv4/tcp.c#L165">165</a> <b><i> *              Marc Tamsky     :       Various sk-&gt;prot-&gt;retransmits and</i></b>
<a name="L166" href="source/net/ipv4/tcp.c#L166">166</a> <b><i> *                                      sk-&gt;retransmits misupdating fixed.</i></b>
<a name="L167" href="source/net/ipv4/tcp.c#L167">167</a> <b><i> *                                      Fixed tcp_write_timeout: stuck close,</i></b>
<a name="L168" href="source/net/ipv4/tcp.c#L168">168</a> <b><i> *                                      and TCP syn retries gets used now.</i></b>
<a name="L169" href="source/net/ipv4/tcp.c#L169">169</a> <b><i> *              Mark Yarvis     :       In tcp_read_wakeup(), don't send an</i></b>
<a name="L170" href="source/net/ipv4/tcp.c#L170">170</a> <b><i> *                                      ack if state is TCP_CLOSED.</i></b>
<a name="L171" href="source/net/ipv4/tcp.c#L171">171</a> <b><i> *              Alan Cox        :       Look up device on a retransmit - routes may</i></b>
<a name="L172" href="source/net/ipv4/tcp.c#L172">172</a> <b><i> *                                      change. Doesn't yet cope with MSS shrink right</i></b>
<a name="L173" href="source/net/ipv4/tcp.c#L173">173</a> <b><i> *                                      but it's a start!</i></b>
<a name="L174" href="source/net/ipv4/tcp.c#L174">174</a> <b><i> *              Marc Tamsky     :       Closing in closing fixes.</i></b>
<a name="L175" href="source/net/ipv4/tcp.c#L175">175</a> <b><i> *              Mike Shaver     :       RFC1122 verifications.</i></b>
<a name="L176" href="source/net/ipv4/tcp.c#L176">176</a> <b><i> *              Alan Cox        :       rcv_saddr errors.</i></b>
<a name="L177" href="source/net/ipv4/tcp.c#L177">177</a> <b><i> *              Alan Cox        :       Block double connect().</i></b>
<a name="L178" href="source/net/ipv4/tcp.c#L178">178</a> <b><i> *              Alan Cox        :       Small hooks for enSKIP.</i></b>
<a name="L179" href="source/net/ipv4/tcp.c#L179">179</a> <b><i> *              Alexey Kuznetsov:       Path MTU discovery.</i></b>
<a name="L180" href="source/net/ipv4/tcp.c#L180">180</a> <b><i> *              Alan Cox        :       Support soft errors.</i></b>
<a name="L181" href="source/net/ipv4/tcp.c#L181">181</a> <b><i> *              Alan Cox        :       Fix MTU discovery pathological case</i></b>
<a name="L182" href="source/net/ipv4/tcp.c#L182">182</a> <b><i> *                                      when the remote claims no mtu!</i></b>
<a name="L183" href="source/net/ipv4/tcp.c#L183">183</a> <b><i> *              Marc Tamsky     :       TCP_CLOSE fix.</i></b>
<a name="L184" href="source/net/ipv4/tcp.c#L184">184</a> <b><i> *              Colin (G3TNE)   :       Send a reset on syn ack replies in</i></b>
<a name="L185" href="source/net/ipv4/tcp.c#L185">185</a> <b><i> *                                      window but wrong (fixes NT lpd problems)</i></b>
<a name="L186" href="source/net/ipv4/tcp.c#L186">186</a> <b><i> *              Pedro Roque     :       Better TCP window handling, delayed ack.</i></b>
<a name="L187" href="source/net/ipv4/tcp.c#L187">187</a> <b><i> *              Joerg Reuter    :       No modification of locked buffers in</i></b>
<a name="L188" href="source/net/ipv4/tcp.c#L188">188</a> <b><i> *                                      tcp_do_retransmit()</i></b>
<a name="L189" href="source/net/ipv4/tcp.c#L189">189</a> <b><i> *              Eric Schenk     :       Changed receiver side silly window</i></b>
<a name="L190" href="source/net/ipv4/tcp.c#L190">190</a> <b><i> *                                      avoidance algorithm to BSD style</i></b>
<a name="L191" href="source/net/ipv4/tcp.c#L191">191</a> <b><i> *                                      algorithm. This doubles throughput</i></b>
<a name="L192" href="source/net/ipv4/tcp.c#L192">192</a> <b><i> *                                      against machines running Solaris,</i></b>
<a name="L193" href="source/net/ipv4/tcp.c#L193">193</a> <b><i> *                                      and seems to result in general</i></b>
<a name="L194" href="source/net/ipv4/tcp.c#L194">194</a> <b><i> *                                      improvement.</i></b>
<a name="L195" href="source/net/ipv4/tcp.c#L195">195</a> <b><i> *      Stefan Magdalinski      :       adjusted tcp_readable() to fix FIONREAD</i></b>
<a name="L196" href="source/net/ipv4/tcp.c#L196">196</a> <b><i> *      Willy Konynenberg       :       Transparent proxying support.</i></b>
<a name="L197" href="source/net/ipv4/tcp.c#L197">197</a> <b><i> *      Mike McLagan            :       Routing by source</i></b>
<a name="L198" href="source/net/ipv4/tcp.c#L198">198</a> <b><i> *              Keith Owens     :       Do proper merging with partial SKB's in</i></b>
<a name="L199" href="source/net/ipv4/tcp.c#L199">199</a> <b><i> *                                      tcp_do_sendmsg to avoid burstiness.</i></b>
<a name="L200" href="source/net/ipv4/tcp.c#L200">200</a> <b><i> *              Eric Schenk     :       Fix fast close down bug with</i></b>
<a name="L201" href="source/net/ipv4/tcp.c#L201">201</a> <b><i> *                                      shutdown() followed by close().</i></b>
<a name="L202" href="source/net/ipv4/tcp.c#L202">202</a> <b><i> *              Andi Kleen      :       Make poll agree with SIGIO</i></b>
<a name="L203" href="source/net/ipv4/tcp.c#L203">203</a> <b><i> *      Salvatore Sanfilippo    :       Support SO_LINGER with linger == 1 and</i></b>
<a name="L204" href="source/net/ipv4/tcp.c#L204">204</a> <b><i> *                                      lingertime == 0 (RFC 793 ABORT Call)</i></b>
<a name="L205" href="source/net/ipv4/tcp.c#L205">205</a> <b><i> *      Hirokazu Takahashi      :       Use copy_from_user() instead of</i></b>
<a name="L206" href="source/net/ipv4/tcp.c#L206">206</a> <b><i> *                                      csum_and_copy_from_user() if possible.</i></b>
<a name="L207" href="source/net/ipv4/tcp.c#L207">207</a> <b><i> *</i></b>
<a name="L208" href="source/net/ipv4/tcp.c#L208">208</a> <b><i> *              This program is free software; you can redistribute it and/or</i></b>
<a name="L209" href="source/net/ipv4/tcp.c#L209">209</a> <b><i> *              modify it under the terms of the GNU General Public License</i></b>
<a name="L210" href="source/net/ipv4/tcp.c#L210">210</a> <b><i> *              as published by the Free Software Foundation; either version</i></b>
<a name="L211" href="source/net/ipv4/tcp.c#L211">211</a> <b><i> *              2 of the License, or(at your option) any later version.</i></b>
<a name="L212" href="source/net/ipv4/tcp.c#L212">212</a> <b><i> *</i></b>
<a name="L213" href="source/net/ipv4/tcp.c#L213">213</a> <b><i> * Description of States:</i></b>
<a name="L214" href="source/net/ipv4/tcp.c#L214">214</a> <b><i> *</i></b>
<a name="L215" href="source/net/ipv4/tcp.c#L215">215</a> <b><i> *      TCP_SYN_SENT            sent a connection request, waiting for ack</i></b>
<a name="L216" href="source/net/ipv4/tcp.c#L216">216</a> <b><i> *</i></b>
<a name="L217" href="source/net/ipv4/tcp.c#L217">217</a> <b><i> *      TCP_SYN_RECV            received a connection request, sent ack,</i></b>
<a name="L218" href="source/net/ipv4/tcp.c#L218">218</a> <b><i> *                              waiting for final ack in three-way handshake.</i></b>
<a name="L219" href="source/net/ipv4/tcp.c#L219">219</a> <b><i> *</i></b>
<a name="L220" href="source/net/ipv4/tcp.c#L220">220</a> <b><i> *      TCP_ESTABLISHED         connection established</i></b>
<a name="L221" href="source/net/ipv4/tcp.c#L221">221</a> <b><i> *</i></b>
<a name="L222" href="source/net/ipv4/tcp.c#L222">222</a> <b><i> *      TCP_FIN_WAIT1           our side has shutdown, waiting to complete</i></b>
<a name="L223" href="source/net/ipv4/tcp.c#L223">223</a> <b><i> *                              transmission of remaining buffered data</i></b>
<a name="L224" href="source/net/ipv4/tcp.c#L224">224</a> <b><i> *</i></b>
<a name="L225" href="source/net/ipv4/tcp.c#L225">225</a> <b><i> *      TCP_FIN_WAIT2           all buffered data sent, waiting for remote</i></b>
<a name="L226" href="source/net/ipv4/tcp.c#L226">226</a> <b><i> *                              to shutdown</i></b>
<a name="L227" href="source/net/ipv4/tcp.c#L227">227</a> <b><i> *</i></b>
<a name="L228" href="source/net/ipv4/tcp.c#L228">228</a> <b><i> *      TCP_CLOSING             both sides have shutdown but we still have</i></b>
<a name="L229" href="source/net/ipv4/tcp.c#L229">229</a> <b><i> *                              data we have to finish sending</i></b>
<a name="L230" href="source/net/ipv4/tcp.c#L230">230</a> <b><i> *</i></b>
<a name="L231" href="source/net/ipv4/tcp.c#L231">231</a> <b><i> *      TCP_TIME_WAIT           timeout to catch resent junk before entering</i></b>
<a name="L232" href="source/net/ipv4/tcp.c#L232">232</a> <b><i> *                              closed, can only be entered from FIN_WAIT2</i></b>
<a name="L233" href="source/net/ipv4/tcp.c#L233">233</a> <b><i> *                              or CLOSING.  Required because the other end</i></b>
<a name="L234" href="source/net/ipv4/tcp.c#L234">234</a> <b><i> *                              may not have gotten our last ACK causing it</i></b>
<a name="L235" href="source/net/ipv4/tcp.c#L235">235</a> <b><i> *                              to retransmit the data packet (which we ignore)</i></b>
<a name="L236" href="source/net/ipv4/tcp.c#L236">236</a> <b><i> *</i></b>
<a name="L237" href="source/net/ipv4/tcp.c#L237">237</a> <b><i> *      TCP_CLOSE_WAIT          remote side has shutdown and is waiting for</i></b>
<a name="L238" href="source/net/ipv4/tcp.c#L238">238</a> <b><i> *                              us to finish writing our data and to shutdown</i></b>
<a name="L239" href="source/net/ipv4/tcp.c#L239">239</a> <b><i> *                              (we have to close() to move on to LAST_ACK)</i></b>
<a name="L240" href="source/net/ipv4/tcp.c#L240">240</a> <b><i> *</i></b>
<a name="L241" href="source/net/ipv4/tcp.c#L241">241</a> <b><i> *      TCP_LAST_ACK            out side has shutdown after remote has</i></b>
<a name="L242" href="source/net/ipv4/tcp.c#L242">242</a> <b><i> *                              shutdown.  There may still be data in our</i></b>
<a name="L243" href="source/net/ipv4/tcp.c#L243">243</a> <b><i> *                              buffer that we have to finish sending</i></b>
<a name="L244" href="source/net/ipv4/tcp.c#L244">244</a> <b><i> *</i></b>
<a name="L245" href="source/net/ipv4/tcp.c#L245">245</a> <b><i> *      TCP_CLOSE               socket is finished</i></b>
<a name="L246" href="source/net/ipv4/tcp.c#L246">246</a> <b><i> */</i></b>
<a name="L247" href="source/net/ipv4/tcp.c#L247">247</a> 
<a name="L248" href="source/net/ipv4/tcp.c#L248">248</a> #define <a href="ident?i=pr_fmt">pr_fmt</a>(<a href="ident?i=fmt">fmt</a>) <i>"TCP: "</i> <a href="ident?i=fmt">fmt</a>
<a name="L249" href="source/net/ipv4/tcp.c#L249">249</a> 
<a name="L250" href="source/net/ipv4/tcp.c#L250">250</a> #include &lt;linux/kernel.h&gt;
<a name="L251" href="source/net/ipv4/tcp.c#L251">251</a> #include &lt;linux/module.h&gt;
<a name="L252" href="source/net/ipv4/tcp.c#L252">252</a> #include &lt;linux/types.h&gt;
<a name="L253" href="source/net/ipv4/tcp.c#L253">253</a> #include &lt;linux/fcntl.h&gt;
<a name="L254" href="source/net/ipv4/tcp.c#L254">254</a> #include &lt;linux/poll.h&gt;
<a name="L255" href="source/net/ipv4/tcp.c#L255">255</a> #include &lt;linux/inet_diag.h&gt;
<a name="L256" href="source/net/ipv4/tcp.c#L256">256</a> #include &lt;linux/init.h&gt;
<a name="L257" href="source/net/ipv4/tcp.c#L257">257</a> #include &lt;linux/fs.h&gt;
<a name="L258" href="source/net/ipv4/tcp.c#L258">258</a> #include &lt;linux/skbuff.h&gt;
<a name="L259" href="source/net/ipv4/tcp.c#L259">259</a> #include &lt;linux/scatterlist.h&gt;
<a name="L260" href="source/net/ipv4/tcp.c#L260">260</a> #include &lt;linux/splice.h&gt;
<a name="L261" href="source/net/ipv4/tcp.c#L261">261</a> #include &lt;linux/net.h&gt;
<a name="L262" href="source/net/ipv4/tcp.c#L262">262</a> #include &lt;linux/socket.h&gt;
<a name="L263" href="source/net/ipv4/tcp.c#L263">263</a> #include &lt;linux/random.h&gt;
<a name="L264" href="source/net/ipv4/tcp.c#L264">264</a> #include &lt;linux/bootmem.h&gt;
<a name="L265" href="source/net/ipv4/tcp.c#L265">265</a> #include &lt;linux/highmem.h&gt;
<a name="L266" href="source/net/ipv4/tcp.c#L266">266</a> #include &lt;linux/swap.h&gt;
<a name="L267" href="source/net/ipv4/tcp.c#L267">267</a> #include &lt;linux/cache.h&gt;
<a name="L268" href="source/net/ipv4/tcp.c#L268">268</a> #include &lt;linux/err.h&gt;
<a name="L269" href="source/net/ipv4/tcp.c#L269">269</a> #include &lt;linux/crypto.h&gt;
<a name="L270" href="source/net/ipv4/tcp.c#L270">270</a> #include &lt;linux/time.h&gt;
<a name="L271" href="source/net/ipv4/tcp.c#L271">271</a> #include &lt;linux/slab.h&gt;
<a name="L272" href="source/net/ipv4/tcp.c#L272">272</a> 
<a name="L273" href="source/net/ipv4/tcp.c#L273">273</a> #include &lt;net/icmp.h&gt;
<a name="L274" href="source/net/ipv4/tcp.c#L274">274</a> #include &lt;net/inet_common.h&gt;
<a name="L275" href="source/net/ipv4/tcp.c#L275">275</a> #include &lt;net/tcp.h&gt;
<a name="L276" href="source/net/ipv4/tcp.c#L276">276</a> #include &lt;net/xfrm.h&gt;
<a name="L277" href="source/net/ipv4/tcp.c#L277">277</a> #include &lt;net/ip.h&gt;
<a name="L278" href="source/net/ipv4/tcp.c#L278">278</a> #include &lt;net/sock.h&gt;
<a name="L279" href="source/net/ipv4/tcp.c#L279">279</a> 
<a name="L280" href="source/net/ipv4/tcp.c#L280">280</a> #include &lt;asm/uaccess.h&gt;
<a name="L281" href="source/net/ipv4/tcp.c#L281">281</a> #include &lt;asm/ioctls.h&gt;
<a name="L282" href="source/net/ipv4/tcp.c#L282">282</a> #include &lt;net/busy_poll.h&gt;
<a name="L283" href="source/net/ipv4/tcp.c#L283">283</a> 
<a name="L284" href="source/net/ipv4/tcp.c#L284">284</a> int <a href="ident?i=sysctl_tcp_fin_timeout">sysctl_tcp_fin_timeout</a> <a href="ident?i=__read_mostly">__read_mostly</a> = <a href="ident?i=TCP_FIN_TIMEOUT">TCP_FIN_TIMEOUT</a>;
<a name="L285" href="source/net/ipv4/tcp.c#L285">285</a> 
<a name="L286" href="source/net/ipv4/tcp.c#L286">286</a> int <a href="ident?i=sysctl_tcp_min_tso_segs">sysctl_tcp_min_tso_segs</a> <a href="ident?i=__read_mostly">__read_mostly</a> = 2;
<a name="L287" href="source/net/ipv4/tcp.c#L287">287</a> 
<a name="L288" href="source/net/ipv4/tcp.c#L288">288</a> int <a href="ident?i=sysctl_tcp_autocorking">sysctl_tcp_autocorking</a> <a href="ident?i=__read_mostly">__read_mostly</a> = 1;
<a name="L289" href="source/net/ipv4/tcp.c#L289">289</a> 
<a name="L290" href="source/net/ipv4/tcp.c#L290">290</a> struct <a href="ident?i=percpu_counter">percpu_counter</a> <a href="ident?i=tcp_orphan_count">tcp_orphan_count</a>;
<a name="L291" href="source/net/ipv4/tcp.c#L291">291</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=tcp_orphan_count">tcp_orphan_count</a>);
<a name="L292" href="source/net/ipv4/tcp.c#L292">292</a> 
<a name="L293" href="source/net/ipv4/tcp.c#L293">293</a> long <a href="ident?i=sysctl_tcp_mem">sysctl_tcp_mem</a>[3] <a href="ident?i=__read_mostly">__read_mostly</a>;
<a name="L294" href="source/net/ipv4/tcp.c#L294">294</a> int <a href="ident?i=sysctl_tcp_wmem">sysctl_tcp_wmem</a>[3] <a href="ident?i=__read_mostly">__read_mostly</a>;
<a name="L295" href="source/net/ipv4/tcp.c#L295">295</a> int <a href="ident?i=sysctl_tcp_rmem">sysctl_tcp_rmem</a>[3] <a href="ident?i=__read_mostly">__read_mostly</a>;
<a name="L296" href="source/net/ipv4/tcp.c#L296">296</a> 
<a name="L297" href="source/net/ipv4/tcp.c#L297">297</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=sysctl_tcp_mem">sysctl_tcp_mem</a>);
<a name="L298" href="source/net/ipv4/tcp.c#L298">298</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=sysctl_tcp_rmem">sysctl_tcp_rmem</a>);
<a name="L299" href="source/net/ipv4/tcp.c#L299">299</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=sysctl_tcp_wmem">sysctl_tcp_wmem</a>);
<a name="L300" href="source/net/ipv4/tcp.c#L300">300</a> 
<a name="L301" href="source/net/ipv4/tcp.c#L301">301</a> <a href="ident?i=atomic_long_t">atomic_long_t</a> <a href="ident?i=tcp_memory_allocated">tcp_memory_allocated</a>;     <b><i>/* Current allocated memory. */</i></b>
<a name="L302" href="source/net/ipv4/tcp.c#L302">302</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=tcp_memory_allocated">tcp_memory_allocated</a>);
<a name="L303" href="source/net/ipv4/tcp.c#L303">303</a> 
<a name="L304" href="source/net/ipv4/tcp.c#L304">304</a> <b><i>/*</i></b>
<a name="L305" href="source/net/ipv4/tcp.c#L305">305</a> <b><i> * Current number of TCP sockets.</i></b>
<a name="L306" href="source/net/ipv4/tcp.c#L306">306</a> <b><i> */</i></b>
<a name="L307" href="source/net/ipv4/tcp.c#L307">307</a> struct <a href="ident?i=percpu_counter">percpu_counter</a> <a href="ident?i=tcp_sockets_allocated">tcp_sockets_allocated</a>;
<a name="L308" href="source/net/ipv4/tcp.c#L308">308</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=tcp_sockets_allocated">tcp_sockets_allocated</a>);
<a name="L309" href="source/net/ipv4/tcp.c#L309">309</a> 
<a name="L310" href="source/net/ipv4/tcp.c#L310">310</a> <b><i>/*</i></b>
<a name="L311" href="source/net/ipv4/tcp.c#L311">311</a> <b><i> * TCP splice context</i></b>
<a name="L312" href="source/net/ipv4/tcp.c#L312">312</a> <b><i> */</i></b>
<a name="L313" href="source/net/ipv4/tcp.c#L313">313</a> struct <a href="ident?i=tcp_splice_state">tcp_splice_state</a> {
<a name="L314" href="source/net/ipv4/tcp.c#L314">314</a>         struct <a href="ident?i=pipe_inode_info">pipe_inode_info</a> *<a href="ident?i=pipe">pipe</a>;
<a name="L315" href="source/net/ipv4/tcp.c#L315">315</a>         <a href="ident?i=size_t">size_t</a> <a href="ident?i=len">len</a>;
<a name="L316" href="source/net/ipv4/tcp.c#L316">316</a>         unsigned int <a href="ident?i=flags">flags</a>;
<a name="L317" href="source/net/ipv4/tcp.c#L317">317</a> };
<a name="L318" href="source/net/ipv4/tcp.c#L318">318</a> 
<a name="L319" href="source/net/ipv4/tcp.c#L319">319</a> <b><i>/*</i></b>
<a name="L320" href="source/net/ipv4/tcp.c#L320">320</a> <b><i> * Pressure flag: try to collapse.</i></b>
<a name="L321" href="source/net/ipv4/tcp.c#L321">321</a> <b><i> * Technical note: it is used by multiple contexts non atomically.</i></b>
<a name="L322" href="source/net/ipv4/tcp.c#L322">322</a> <b><i> * All the __sk_mem_schedule() is of this nature: accounting</i></b>
<a name="L323" href="source/net/ipv4/tcp.c#L323">323</a> <b><i> * is strict, actions are advisory and have some latency.</i></b>
<a name="L324" href="source/net/ipv4/tcp.c#L324">324</a> <b><i> */</i></b>
<a name="L325" href="source/net/ipv4/tcp.c#L325">325</a> int <a href="ident?i=tcp_memory_pressure">tcp_memory_pressure</a> <a href="ident?i=__read_mostly">__read_mostly</a>;
<a name="L326" href="source/net/ipv4/tcp.c#L326">326</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=tcp_memory_pressure">tcp_memory_pressure</a>);
<a name="L327" href="source/net/ipv4/tcp.c#L327">327</a> 
<a name="L328" href="source/net/ipv4/tcp.c#L328">328</a> void <a href="ident?i=tcp_enter_memory_pressure">tcp_enter_memory_pressure</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L329" href="source/net/ipv4/tcp.c#L329">329</a> {
<a name="L330" href="source/net/ipv4/tcp.c#L330">330</a>         if (!<a href="ident?i=tcp_memory_pressure">tcp_memory_pressure</a>) {
<a name="L331" href="source/net/ipv4/tcp.c#L331">331</a>                 <a href="ident?i=NET_INC_STATS">NET_INC_STATS</a>(<a href="ident?i=sock_net">sock_net</a>(sk), LINUX_MIB_TCPMEMORYPRESSURES);
<a name="L332" href="source/net/ipv4/tcp.c#L332">332</a>                 <a href="ident?i=tcp_memory_pressure">tcp_memory_pressure</a> = 1;
<a name="L333" href="source/net/ipv4/tcp.c#L333">333</a>         }
<a name="L334" href="source/net/ipv4/tcp.c#L334">334</a> }
<a name="L335" href="source/net/ipv4/tcp.c#L335">335</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=tcp_enter_memory_pressure">tcp_enter_memory_pressure</a>);
<a name="L336" href="source/net/ipv4/tcp.c#L336">336</a> 
<a name="L337" href="source/net/ipv4/tcp.c#L337">337</a> <b><i>/* Convert seconds to retransmits based on initial and max timeout */</i></b>
<a name="L338" href="source/net/ipv4/tcp.c#L338">338</a> static <a href="ident?i=u8">u8</a> <a href="ident?i=secs_to_retrans">secs_to_retrans</a>(int seconds, int <a href="ident?i=timeout">timeout</a>, int rto_max)
<a name="L339" href="source/net/ipv4/tcp.c#L339">339</a> {
<a name="L340" href="source/net/ipv4/tcp.c#L340">340</a>         <a href="ident?i=u8">u8</a> <a href="ident?i=res">res</a> = 0;
<a name="L341" href="source/net/ipv4/tcp.c#L341">341</a> 
<a name="L342" href="source/net/ipv4/tcp.c#L342">342</a>         if (seconds &gt; 0) {
<a name="L343" href="source/net/ipv4/tcp.c#L343">343</a>                 int <a href="ident?i=period">period</a> = <a href="ident?i=timeout">timeout</a>;
<a name="L344" href="source/net/ipv4/tcp.c#L344">344</a> 
<a name="L345" href="source/net/ipv4/tcp.c#L345">345</a>                 <a href="ident?i=res">res</a> = 1;
<a name="L346" href="source/net/ipv4/tcp.c#L346">346</a>                 while (seconds &gt; <a href="ident?i=period">period</a> &amp;&amp; <a href="ident?i=res">res</a> &lt; 255) {
<a name="L347" href="source/net/ipv4/tcp.c#L347">347</a>                         <a href="ident?i=res">res</a>++;
<a name="L348" href="source/net/ipv4/tcp.c#L348">348</a>                         <a href="ident?i=timeout">timeout</a> &lt;&lt;= 1;
<a name="L349" href="source/net/ipv4/tcp.c#L349">349</a>                         if (<a href="ident?i=timeout">timeout</a> &gt; rto_max)
<a name="L350" href="source/net/ipv4/tcp.c#L350">350</a>                                 <a href="ident?i=timeout">timeout</a> = rto_max;
<a name="L351" href="source/net/ipv4/tcp.c#L351">351</a>                         <a href="ident?i=period">period</a> += <a href="ident?i=timeout">timeout</a>;
<a name="L352" href="source/net/ipv4/tcp.c#L352">352</a>                 }
<a name="L353" href="source/net/ipv4/tcp.c#L353">353</a>         }
<a name="L354" href="source/net/ipv4/tcp.c#L354">354</a>         return <a href="ident?i=res">res</a>;
<a name="L355" href="source/net/ipv4/tcp.c#L355">355</a> }
<a name="L356" href="source/net/ipv4/tcp.c#L356">356</a> 
<a name="L357" href="source/net/ipv4/tcp.c#L357">357</a> <b><i>/* Convert retransmits to seconds based on initial and max timeout */</i></b>
<a name="L358" href="source/net/ipv4/tcp.c#L358">358</a> static int <a href="ident?i=retrans_to_secs">retrans_to_secs</a>(<a href="ident?i=u8">u8</a> retrans, int <a href="ident?i=timeout">timeout</a>, int rto_max)
<a name="L359" href="source/net/ipv4/tcp.c#L359">359</a> {
<a name="L360" href="source/net/ipv4/tcp.c#L360">360</a>         int <a href="ident?i=period">period</a> = 0;
<a name="L361" href="source/net/ipv4/tcp.c#L361">361</a> 
<a name="L362" href="source/net/ipv4/tcp.c#L362">362</a>         if (retrans &gt; 0) {
<a name="L363" href="source/net/ipv4/tcp.c#L363">363</a>                 <a href="ident?i=period">period</a> = <a href="ident?i=timeout">timeout</a>;
<a name="L364" href="source/net/ipv4/tcp.c#L364">364</a>                 while (--retrans) {
<a name="L365" href="source/net/ipv4/tcp.c#L365">365</a>                         <a href="ident?i=timeout">timeout</a> &lt;&lt;= 1;
<a name="L366" href="source/net/ipv4/tcp.c#L366">366</a>                         if (<a href="ident?i=timeout">timeout</a> &gt; rto_max)
<a name="L367" href="source/net/ipv4/tcp.c#L367">367</a>                                 <a href="ident?i=timeout">timeout</a> = rto_max;
<a name="L368" href="source/net/ipv4/tcp.c#L368">368</a>                         <a href="ident?i=period">period</a> += <a href="ident?i=timeout">timeout</a>;
<a name="L369" href="source/net/ipv4/tcp.c#L369">369</a>                 }
<a name="L370" href="source/net/ipv4/tcp.c#L370">370</a>         }
<a name="L371" href="source/net/ipv4/tcp.c#L371">371</a>         return <a href="ident?i=period">period</a>;
<a name="L372" href="source/net/ipv4/tcp.c#L372">372</a> }
<a name="L373" href="source/net/ipv4/tcp.c#L373">373</a> 
<a name="L374" href="source/net/ipv4/tcp.c#L374">374</a> <b><i>/* Address-family independent initialization for a tcp_sock.</i></b>
<a name="L375" href="source/net/ipv4/tcp.c#L375">375</a> <b><i> *</i></b>
<a name="L376" href="source/net/ipv4/tcp.c#L376">376</a> <b><i> * NOTE: A lot of things set to zero explicitly by call to</i></b>
<a name="L377" href="source/net/ipv4/tcp.c#L377">377</a> <b><i> *       sk_alloc() so need not be done here.</i></b>
<a name="L378" href="source/net/ipv4/tcp.c#L378">378</a> <b><i> */</i></b>
<a name="L379" href="source/net/ipv4/tcp.c#L379">379</a> void <a href="ident?i=tcp_init_sock">tcp_init_sock</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L380" href="source/net/ipv4/tcp.c#L380">380</a> {
<a name="L381" href="source/net/ipv4/tcp.c#L381">381</a>         struct <a href="ident?i=inet_connection_sock">inet_connection_sock</a> *icsk = <a href="ident?i=inet_csk">inet_csk</a>(sk);
<a name="L382" href="source/net/ipv4/tcp.c#L382">382</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L383" href="source/net/ipv4/tcp.c#L383">383</a> 
<a name="L384" href="source/net/ipv4/tcp.c#L384">384</a>         <a href="ident?i=__skb_queue_head_init">__skb_queue_head_init</a>(&amp;<a href="ident?i=tp">tp</a>-&gt;out_of_order_queue);
<a name="L385" href="source/net/ipv4/tcp.c#L385">385</a>         <a href="ident?i=tcp_init_xmit_timers">tcp_init_xmit_timers</a>(sk);
<a name="L386" href="source/net/ipv4/tcp.c#L386">386</a>         <a href="ident?i=tcp_prequeue_init">tcp_prequeue_init</a>(<a href="ident?i=tp">tp</a>);
<a name="L387" href="source/net/ipv4/tcp.c#L387">387</a>         <a href="ident?i=INIT_LIST_HEAD">INIT_LIST_HEAD</a>(&amp;<a href="ident?i=tp">tp</a>-&gt;tsq_node);
<a name="L388" href="source/net/ipv4/tcp.c#L388">388</a> 
<a name="L389" href="source/net/ipv4/tcp.c#L389">389</a>         icsk-&gt;icsk_rto = <a href="ident?i=TCP_TIMEOUT_INIT">TCP_TIMEOUT_INIT</a>;
<a name="L390" href="source/net/ipv4/tcp.c#L390">390</a>         <a href="ident?i=tp">tp</a>-&gt;mdev_us = <a href="ident?i=jiffies_to_usecs">jiffies_to_usecs</a>(<a href="ident?i=TCP_TIMEOUT_INIT">TCP_TIMEOUT_INIT</a>);
<a name="L391" href="source/net/ipv4/tcp.c#L391">391</a> 
<a name="L392" href="source/net/ipv4/tcp.c#L392">392</a>         <b><i>/* So many TCP implementations out there (incorrectly) count the</i></b>
<a name="L393" href="source/net/ipv4/tcp.c#L393">393</a> <b><i>         * initial SYN frame in their delayed-ACK and congestion control</i></b>
<a name="L394" href="source/net/ipv4/tcp.c#L394">394</a> <b><i>         * algorithms that we must have the following bandaid to talk</i></b>
<a name="L395" href="source/net/ipv4/tcp.c#L395">395</a> <b><i>         * efficiently to them.  -DaveM</i></b>
<a name="L396" href="source/net/ipv4/tcp.c#L396">396</a> <b><i>         */</i></b>
<a name="L397" href="source/net/ipv4/tcp.c#L397">397</a>         <a href="ident?i=tp">tp</a>-&gt;snd_cwnd = <a href="ident?i=TCP_INIT_CWND">TCP_INIT_CWND</a>;
<a name="L398" href="source/net/ipv4/tcp.c#L398">398</a> 
<a name="L399" href="source/net/ipv4/tcp.c#L399">399</a>         <b><i>/* See draft-stevens-tcpca-spec-01 for discussion of the</i></b>
<a name="L400" href="source/net/ipv4/tcp.c#L400">400</a> <b><i>         * initialization of these values.</i></b>
<a name="L401" href="source/net/ipv4/tcp.c#L401">401</a> <b><i>         */</i></b>
<a name="L402" href="source/net/ipv4/tcp.c#L402">402</a>         <a href="ident?i=tp">tp</a>-&gt;snd_ssthresh = <a href="ident?i=TCP_INFINITE_SSTHRESH">TCP_INFINITE_SSTHRESH</a>;
<a name="L403" href="source/net/ipv4/tcp.c#L403">403</a>         <a href="ident?i=tp">tp</a>-&gt;snd_cwnd_clamp = ~0;
<a name="L404" href="source/net/ipv4/tcp.c#L404">404</a>         <a href="ident?i=tp">tp</a>-&gt;mss_cache = <a href="ident?i=TCP_MSS_DEFAULT">TCP_MSS_DEFAULT</a>;
<a name="L405" href="source/net/ipv4/tcp.c#L405">405</a>         <a href="ident?i=u64_stats_init">u64_stats_init</a>(&amp;<a href="ident?i=tp">tp</a>-&gt;syncp);
<a name="L406" href="source/net/ipv4/tcp.c#L406">406</a> 
<a name="L407" href="source/net/ipv4/tcp.c#L407">407</a>         <a href="ident?i=tp">tp</a>-&gt;reordering = <a href="ident?i=sysctl_tcp_reordering">sysctl_tcp_reordering</a>;
<a name="L408" href="source/net/ipv4/tcp.c#L408">408</a>         <a href="ident?i=tcp_enable_early_retrans">tcp_enable_early_retrans</a>(<a href="ident?i=tp">tp</a>);
<a name="L409" href="source/net/ipv4/tcp.c#L409">409</a>         <a href="ident?i=tcp_assign_congestion_control">tcp_assign_congestion_control</a>(sk);
<a name="L410" href="source/net/ipv4/tcp.c#L410">410</a> 
<a name="L411" href="source/net/ipv4/tcp.c#L411">411</a>         <a href="ident?i=tp">tp</a>-&gt;tsoffset = 0;
<a name="L412" href="source/net/ipv4/tcp.c#L412">412</a> 
<a name="L413" href="source/net/ipv4/tcp.c#L413">413</a>         sk-&gt;<a href="ident?i=sk_state">sk_state</a> = TCP_CLOSE;
<a name="L414" href="source/net/ipv4/tcp.c#L414">414</a> 
<a name="L415" href="source/net/ipv4/tcp.c#L415">415</a>         sk-&gt;sk_write_space = <a href="ident?i=sk_stream_write_space">sk_stream_write_space</a>;
<a name="L416" href="source/net/ipv4/tcp.c#L416">416</a>         <a href="ident?i=sock_set_flag">sock_set_flag</a>(sk, SOCK_USE_WRITE_QUEUE);
<a name="L417" href="source/net/ipv4/tcp.c#L417">417</a> 
<a name="L418" href="source/net/ipv4/tcp.c#L418">418</a>         icsk-&gt;icsk_sync_mss = <a href="ident?i=tcp_sync_mss">tcp_sync_mss</a>;
<a name="L419" href="source/net/ipv4/tcp.c#L419">419</a> 
<a name="L420" href="source/net/ipv4/tcp.c#L420">420</a>         sk-&gt;sk_sndbuf = <a href="ident?i=sysctl_tcp_wmem">sysctl_tcp_wmem</a>[1];
<a name="L421" href="source/net/ipv4/tcp.c#L421">421</a>         sk-&gt;sk_rcvbuf = <a href="ident?i=sysctl_tcp_rmem">sysctl_tcp_rmem</a>[1];
<a name="L422" href="source/net/ipv4/tcp.c#L422">422</a> 
<a name="L423" href="source/net/ipv4/tcp.c#L423">423</a>         <a href="ident?i=local_bh_disable">local_bh_disable</a>();
<a name="L424" href="source/net/ipv4/tcp.c#L424">424</a>         <a href="ident?i=sock_update_memcg">sock_update_memcg</a>(sk);
<a name="L425" href="source/net/ipv4/tcp.c#L425">425</a>         <a href="ident?i=sk_sockets_allocated_inc">sk_sockets_allocated_inc</a>(sk);
<a name="L426" href="source/net/ipv4/tcp.c#L426">426</a>         <a href="ident?i=local_bh_enable">local_bh_enable</a>();
<a name="L427" href="source/net/ipv4/tcp.c#L427">427</a> }
<a name="L428" href="source/net/ipv4/tcp.c#L428">428</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=tcp_init_sock">tcp_init_sock</a>);
<a name="L429" href="source/net/ipv4/tcp.c#L429">429</a> 
<a name="L430" href="source/net/ipv4/tcp.c#L430">430</a> static void <a href="ident?i=tcp_tx_timestamp">tcp_tx_timestamp</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L431" href="source/net/ipv4/tcp.c#L431">431</a> {
<a name="L432" href="source/net/ipv4/tcp.c#L432">432</a>         if (sk-&gt;sk_tsflags) {
<a name="L433" href="source/net/ipv4/tcp.c#L433">433</a>                 struct <a href="ident?i=skb_shared_info">skb_shared_info</a> *shinfo = <a href="ident?i=skb_shinfo">skb_shinfo</a>(<a href="ident?i=skb">skb</a>);
<a name="L434" href="source/net/ipv4/tcp.c#L434">434</a> 
<a name="L435" href="source/net/ipv4/tcp.c#L435">435</a>                 <a href="ident?i=sock_tx_timestamp">sock_tx_timestamp</a>(sk, &amp;shinfo-&gt;tx_flags);
<a name="L436" href="source/net/ipv4/tcp.c#L436">436</a>                 if (shinfo-&gt;tx_flags &amp; <a href="ident?i=SKBTX_ANY_TSTAMP">SKBTX_ANY_TSTAMP</a>)
<a name="L437" href="source/net/ipv4/tcp.c#L437">437</a>                         shinfo-&gt;tskey = <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=seq">seq</a> + <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a> - 1;
<a name="L438" href="source/net/ipv4/tcp.c#L438">438</a>         }
<a name="L439" href="source/net/ipv4/tcp.c#L439">439</a> }
<a name="L440" href="source/net/ipv4/tcp.c#L440">440</a> 
<a name="L441" href="source/net/ipv4/tcp.c#L441">441</a> <b><i>/*</i></b>
<a name="L442" href="source/net/ipv4/tcp.c#L442">442</a> <b><i> *      Wait for a TCP event.</i></b>
<a name="L443" href="source/net/ipv4/tcp.c#L443">443</a> <b><i> *</i></b>
<a name="L444" href="source/net/ipv4/tcp.c#L444">444</a> <b><i> *      Note that we don't need to lock the socket, as the upper poll layers</i></b>
<a name="L445" href="source/net/ipv4/tcp.c#L445">445</a> <b><i> *      take care of normal races (between the test and the event) and we don't</i></b>
<a name="L446" href="source/net/ipv4/tcp.c#L446">446</a> <b><i> *      go look at any of the socket buffers directly.</i></b>
<a name="L447" href="source/net/ipv4/tcp.c#L447">447</a> <b><i> */</i></b>
<a name="L448" href="source/net/ipv4/tcp.c#L448">448</a> unsigned int <a href="ident?i=tcp_poll">tcp_poll</a>(struct <a href="ident?i=file">file</a> *<a href="ident?i=file">file</a>, struct <a href="ident?i=socket">socket</a> *<a href="ident?i=sock">sock</a>, <a href="ident?i=poll_table">poll_table</a> *<a href="ident?i=wait">wait</a>)
<a name="L449" href="source/net/ipv4/tcp.c#L449">449</a> {
<a name="L450" href="source/net/ipv4/tcp.c#L450">450</a>         unsigned int <a href="ident?i=mask">mask</a>;
<a name="L451" href="source/net/ipv4/tcp.c#L451">451</a>         struct <a href="ident?i=sock">sock</a> *sk = <a href="ident?i=sock">sock</a>-&gt;sk;
<a name="L452" href="source/net/ipv4/tcp.c#L452">452</a>         const struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L453" href="source/net/ipv4/tcp.c#L453">453</a> 
<a name="L454" href="source/net/ipv4/tcp.c#L454">454</a>         <a href="ident?i=sock_rps_record_flow">sock_rps_record_flow</a>(sk);
<a name="L455" href="source/net/ipv4/tcp.c#L455">455</a> 
<a name="L456" href="source/net/ipv4/tcp.c#L456">456</a>         <a href="ident?i=sock_poll_wait">sock_poll_wait</a>(<a href="ident?i=file">file</a>, <a href="ident?i=sk_sleep">sk_sleep</a>(sk), <a href="ident?i=wait">wait</a>);
<a name="L457" href="source/net/ipv4/tcp.c#L457">457</a>         if (sk-&gt;<a href="ident?i=sk_state">sk_state</a> == TCP_LISTEN)
<a name="L458" href="source/net/ipv4/tcp.c#L458">458</a>                 return <a href="ident?i=inet_csk_listen_poll">inet_csk_listen_poll</a>(sk);
<a name="L459" href="source/net/ipv4/tcp.c#L459">459</a> 
<a name="L460" href="source/net/ipv4/tcp.c#L460">460</a>         <b><i>/* Socket is not locked. We are protected from async events</i></b>
<a name="L461" href="source/net/ipv4/tcp.c#L461">461</a> <b><i>         * by poll logic and correct handling of state changes</i></b>
<a name="L462" href="source/net/ipv4/tcp.c#L462">462</a> <b><i>         * made by other threads is impossible in any case.</i></b>
<a name="L463" href="source/net/ipv4/tcp.c#L463">463</a> <b><i>         */</i></b>
<a name="L464" href="source/net/ipv4/tcp.c#L464">464</a> 
<a name="L465" href="source/net/ipv4/tcp.c#L465">465</a>         <a href="ident?i=mask">mask</a> = 0;
<a name="L466" href="source/net/ipv4/tcp.c#L466">466</a> 
<a name="L467" href="source/net/ipv4/tcp.c#L467">467</a>         <b><i>/*</i></b>
<a name="L468" href="source/net/ipv4/tcp.c#L468">468</a> <b><i>         * POLLHUP is certainly not done right. But poll() doesn't</i></b>
<a name="L469" href="source/net/ipv4/tcp.c#L469">469</a> <b><i>         * have a notion of HUP in just one direction, and for a</i></b>
<a name="L470" href="source/net/ipv4/tcp.c#L470">470</a> <b><i>         * socket the read side is more interesting.</i></b>
<a name="L471" href="source/net/ipv4/tcp.c#L471">471</a> <b><i>         *</i></b>
<a name="L472" href="source/net/ipv4/tcp.c#L472">472</a> <b><i>         * Some poll() documentation says that POLLHUP is incompatible</i></b>
<a name="L473" href="source/net/ipv4/tcp.c#L473">473</a> <b><i>         * with the POLLOUT/POLLWR flags, so somebody should check this</i></b>
<a name="L474" href="source/net/ipv4/tcp.c#L474">474</a> <b><i>         * all. But careful, it tends to be safer to return too many</i></b>
<a name="L475" href="source/net/ipv4/tcp.c#L475">475</a> <b><i>         * bits than too few, and you can easily break real applications</i></b>
<a name="L476" href="source/net/ipv4/tcp.c#L476">476</a> <b><i>         * if you don't tell them that something has hung up!</i></b>
<a name="L477" href="source/net/ipv4/tcp.c#L477">477</a> <b><i>         *</i></b>
<a name="L478" href="source/net/ipv4/tcp.c#L478">478</a> <b><i>         * Check-me.</i></b>
<a name="L479" href="source/net/ipv4/tcp.c#L479">479</a> <b><i>         *</i></b>
<a name="L480" href="source/net/ipv4/tcp.c#L480">480</a> <b><i>         * Check number 1. POLLHUP is _UNMASKABLE_ event (see UNIX98 and</i></b>
<a name="L481" href="source/net/ipv4/tcp.c#L481">481</a> <b><i>         * our fs/select.c). It means that after we received EOF,</i></b>
<a name="L482" href="source/net/ipv4/tcp.c#L482">482</a> <b><i>         * poll always returns immediately, making impossible poll() on write()</i></b>
<a name="L483" href="source/net/ipv4/tcp.c#L483">483</a> <b><i>         * in state CLOSE_WAIT. One solution is evident --- to set POLLHUP</i></b>
<a name="L484" href="source/net/ipv4/tcp.c#L484">484</a> <b><i>         * if and only if shutdown has been made in both directions.</i></b>
<a name="L485" href="source/net/ipv4/tcp.c#L485">485</a> <b><i>         * Actually, it is interesting to look how Solaris and DUX</i></b>
<a name="L486" href="source/net/ipv4/tcp.c#L486">486</a> <b><i>         * solve this dilemma. I would prefer, if POLLHUP were maskable,</i></b>
<a name="L487" href="source/net/ipv4/tcp.c#L487">487</a> <b><i>         * then we could set it on SND_SHUTDOWN. BTW examples given</i></b>
<a name="L488" href="source/net/ipv4/tcp.c#L488">488</a> <b><i>         * in Stevens' books assume exactly this behaviour, it explains</i></b>
<a name="L489" href="source/net/ipv4/tcp.c#L489">489</a> <b><i>         * why POLLHUP is incompatible with POLLOUT.    --ANK</i></b>
<a name="L490" href="source/net/ipv4/tcp.c#L490">490</a> <b><i>         *</i></b>
<a name="L491" href="source/net/ipv4/tcp.c#L491">491</a> <b><i>         * NOTE. Check for TCP_CLOSE is added. The goal is to prevent</i></b>
<a name="L492" href="source/net/ipv4/tcp.c#L492">492</a> <b><i>         * blocking on fresh not-connected or disconnected socket. --ANK</i></b>
<a name="L493" href="source/net/ipv4/tcp.c#L493">493</a> <b><i>         */</i></b>
<a name="L494" href="source/net/ipv4/tcp.c#L494">494</a>         if (sk-&gt;sk_shutdown == <a href="ident?i=SHUTDOWN_MASK">SHUTDOWN_MASK</a> || sk-&gt;<a href="ident?i=sk_state">sk_state</a> == TCP_CLOSE)
<a name="L495" href="source/net/ipv4/tcp.c#L495">495</a>                 <a href="ident?i=mask">mask</a> |= <a href="ident?i=POLLHUP">POLLHUP</a>;
<a name="L496" href="source/net/ipv4/tcp.c#L496">496</a>         if (sk-&gt;sk_shutdown &amp; <a href="ident?i=RCV_SHUTDOWN">RCV_SHUTDOWN</a>)
<a name="L497" href="source/net/ipv4/tcp.c#L497">497</a>                 <a href="ident?i=mask">mask</a> |= <a href="ident?i=POLLIN">POLLIN</a> | <a href="ident?i=POLLRDNORM">POLLRDNORM</a> | <a href="ident?i=POLLRDHUP">POLLRDHUP</a>;
<a name="L498" href="source/net/ipv4/tcp.c#L498">498</a> 
<a name="L499" href="source/net/ipv4/tcp.c#L499">499</a>         <b><i>/* Connected or passive Fast Open socket? */</i></b>
<a name="L500" href="source/net/ipv4/tcp.c#L500">500</a>         if (sk-&gt;<a href="ident?i=sk_state">sk_state</a> != TCP_SYN_SENT &amp;&amp;
<a name="L501" href="source/net/ipv4/tcp.c#L501">501</a>             (sk-&gt;<a href="ident?i=sk_state">sk_state</a> != TCP_SYN_RECV || <a href="ident?i=tp">tp</a>-&gt;fastopen_rsk)) {
<a name="L502" href="source/net/ipv4/tcp.c#L502">502</a>                 int <a href="ident?i=target">target</a> = <a href="ident?i=sock_rcvlowat">sock_rcvlowat</a>(sk, 0, <a href="ident?i=INT_MAX">INT_MAX</a>);
<a name="L503" href="source/net/ipv4/tcp.c#L503">503</a> 
<a name="L504" href="source/net/ipv4/tcp.c#L504">504</a>                 if (<a href="ident?i=tp">tp</a>-&gt;urg_seq == <a href="ident?i=tp">tp</a>-&gt;copied_seq &amp;&amp;
<a name="L505" href="source/net/ipv4/tcp.c#L505">505</a>                     !<a href="ident?i=sock_flag">sock_flag</a>(sk, SOCK_URGINLINE) &amp;&amp;
<a name="L506" href="source/net/ipv4/tcp.c#L506">506</a>                     <a href="ident?i=tp">tp</a>-&gt;urg_data)
<a name="L507" href="source/net/ipv4/tcp.c#L507">507</a>                         <a href="ident?i=target">target</a>++;
<a name="L508" href="source/net/ipv4/tcp.c#L508">508</a> 
<a name="L509" href="source/net/ipv4/tcp.c#L509">509</a>                 <b><i>/* Potential race condition. If read of tp below will</i></b>
<a name="L510" href="source/net/ipv4/tcp.c#L510">510</a> <b><i>                 * escape above sk-&gt;sk_state, we can be illegally awaken</i></b>
<a name="L511" href="source/net/ipv4/tcp.c#L511">511</a> <b><i>                 * in SYN_* states. */</i></b>
<a name="L512" href="source/net/ipv4/tcp.c#L512">512</a>                 if (<a href="ident?i=tp">tp</a>-&gt;rcv_nxt - <a href="ident?i=tp">tp</a>-&gt;copied_seq &gt;= <a href="ident?i=target">target</a>)
<a name="L513" href="source/net/ipv4/tcp.c#L513">513</a>                         <a href="ident?i=mask">mask</a> |= <a href="ident?i=POLLIN">POLLIN</a> | <a href="ident?i=POLLRDNORM">POLLRDNORM</a>;
<a name="L514" href="source/net/ipv4/tcp.c#L514">514</a> 
<a name="L515" href="source/net/ipv4/tcp.c#L515">515</a>                 if (!(sk-&gt;sk_shutdown &amp; <a href="ident?i=SEND_SHUTDOWN">SEND_SHUTDOWN</a>)) {
<a name="L516" href="source/net/ipv4/tcp.c#L516">516</a>                         if (<a href="ident?i=sk_stream_is_writeable">sk_stream_is_writeable</a>(sk)) {
<a name="L517" href="source/net/ipv4/tcp.c#L517">517</a>                                 <a href="ident?i=mask">mask</a> |= <a href="ident?i=POLLOUT">POLLOUT</a> | <a href="ident?i=POLLWRNORM">POLLWRNORM</a>;
<a name="L518" href="source/net/ipv4/tcp.c#L518">518</a>                         } else {  <b><i>/* send SIGIO later */</i></b>
<a name="L519" href="source/net/ipv4/tcp.c#L519">519</a>                                 <a href="ident?i=set_bit">set_bit</a>(<a href="ident?i=SOCK_ASYNC_NOSPACE">SOCK_ASYNC_NOSPACE</a>,
<a name="L520" href="source/net/ipv4/tcp.c#L520">520</a>                                         &amp;sk-&gt;sk_socket-&gt;<a href="ident?i=flags">flags</a>);
<a name="L521" href="source/net/ipv4/tcp.c#L521">521</a>                                 <a href="ident?i=set_bit">set_bit</a>(<a href="ident?i=SOCK_NOSPACE">SOCK_NOSPACE</a>, &amp;sk-&gt;sk_socket-&gt;<a href="ident?i=flags">flags</a>);
<a name="L522" href="source/net/ipv4/tcp.c#L522">522</a> 
<a name="L523" href="source/net/ipv4/tcp.c#L523">523</a>                                 <b><i>/* Race breaker. If space is freed after</i></b>
<a name="L524" href="source/net/ipv4/tcp.c#L524">524</a> <b><i>                                 * wspace test but before the flags are set,</i></b>
<a name="L525" href="source/net/ipv4/tcp.c#L525">525</a> <b><i>                                 * IO signal will be lost. Memory barrier</i></b>
<a name="L526" href="source/net/ipv4/tcp.c#L526">526</a> <b><i>                                 * pairs with the input side.</i></b>
<a name="L527" href="source/net/ipv4/tcp.c#L527">527</a> <b><i>                                 */</i></b>
<a name="L528" href="source/net/ipv4/tcp.c#L528">528</a>                                 <a href="ident?i=smp_mb__after_atomic">smp_mb__after_atomic</a>();
<a name="L529" href="source/net/ipv4/tcp.c#L529">529</a>                                 if (<a href="ident?i=sk_stream_is_writeable">sk_stream_is_writeable</a>(sk))
<a name="L530" href="source/net/ipv4/tcp.c#L530">530</a>                                         <a href="ident?i=mask">mask</a> |= <a href="ident?i=POLLOUT">POLLOUT</a> | <a href="ident?i=POLLWRNORM">POLLWRNORM</a>;
<a name="L531" href="source/net/ipv4/tcp.c#L531">531</a>                         }
<a name="L532" href="source/net/ipv4/tcp.c#L532">532</a>                 } else
<a name="L533" href="source/net/ipv4/tcp.c#L533">533</a>                         <a href="ident?i=mask">mask</a> |= <a href="ident?i=POLLOUT">POLLOUT</a> | <a href="ident?i=POLLWRNORM">POLLWRNORM</a>;
<a name="L534" href="source/net/ipv4/tcp.c#L534">534</a> 
<a name="L535" href="source/net/ipv4/tcp.c#L535">535</a>                 if (<a href="ident?i=tp">tp</a>-&gt;urg_data &amp; <a href="ident?i=TCP_URG_VALID">TCP_URG_VALID</a>)
<a name="L536" href="source/net/ipv4/tcp.c#L536">536</a>                         <a href="ident?i=mask">mask</a> |= <a href="ident?i=POLLPRI">POLLPRI</a>;
<a name="L537" href="source/net/ipv4/tcp.c#L537">537</a>         }
<a name="L538" href="source/net/ipv4/tcp.c#L538">538</a>         <b><i>/* This barrier is coupled with smp_wmb() in tcp_reset() */</i></b>
<a name="L539" href="source/net/ipv4/tcp.c#L539">539</a>         <a href="ident?i=smp_rmb">smp_rmb</a>();
<a name="L540" href="source/net/ipv4/tcp.c#L540">540</a>         if (sk-&gt;sk_err || !<a href="ident?i=skb_queue_empty">skb_queue_empty</a>(&amp;sk-&gt;sk_error_queue))
<a name="L541" href="source/net/ipv4/tcp.c#L541">541</a>                 <a href="ident?i=mask">mask</a> |= <a href="ident?i=POLLERR">POLLERR</a>;
<a name="L542" href="source/net/ipv4/tcp.c#L542">542</a> 
<a name="L543" href="source/net/ipv4/tcp.c#L543">543</a>         return <a href="ident?i=mask">mask</a>;
<a name="L544" href="source/net/ipv4/tcp.c#L544">544</a> }
<a name="L545" href="source/net/ipv4/tcp.c#L545">545</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=tcp_poll">tcp_poll</a>);
<a name="L546" href="source/net/ipv4/tcp.c#L546">546</a> 
<a name="L547" href="source/net/ipv4/tcp.c#L547">547</a> int <a href="ident?i=tcp_ioctl">tcp_ioctl</a>(struct <a href="ident?i=sock">sock</a> *sk, int <a href="ident?i=cmd">cmd</a>, unsigned long <a href="ident?i=arg">arg</a>)
<a name="L548" href="source/net/ipv4/tcp.c#L548">548</a> {
<a name="L549" href="source/net/ipv4/tcp.c#L549">549</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L550" href="source/net/ipv4/tcp.c#L550">550</a>         int answ;
<a name="L551" href="source/net/ipv4/tcp.c#L551">551</a>         <a href="ident?i=bool">bool</a> <a href="ident?i=slow">slow</a>;
<a name="L552" href="source/net/ipv4/tcp.c#L552">552</a> 
<a name="L553" href="source/net/ipv4/tcp.c#L553">553</a>         switch (<a href="ident?i=cmd">cmd</a>) {
<a name="L554" href="source/net/ipv4/tcp.c#L554">554</a>         case <a href="ident?i=SIOCINQ">SIOCINQ</a>:
<a name="L555" href="source/net/ipv4/tcp.c#L555">555</a>                 if (sk-&gt;<a href="ident?i=sk_state">sk_state</a> == TCP_LISTEN)
<a name="L556" href="source/net/ipv4/tcp.c#L556">556</a>                         return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L557" href="source/net/ipv4/tcp.c#L557">557</a> 
<a name="L558" href="source/net/ipv4/tcp.c#L558">558</a>                 <a href="ident?i=slow">slow</a> = <a href="ident?i=lock_sock_fast">lock_sock_fast</a>(sk);
<a name="L559" href="source/net/ipv4/tcp.c#L559">559</a>                 if ((1 &lt;&lt; sk-&gt;<a href="ident?i=sk_state">sk_state</a>) &amp; (TCPF_SYN_SENT | TCPF_SYN_RECV))
<a name="L560" href="source/net/ipv4/tcp.c#L560">560</a>                         answ = 0;
<a name="L561" href="source/net/ipv4/tcp.c#L561">561</a>                 else if (<a href="ident?i=sock_flag">sock_flag</a>(sk, SOCK_URGINLINE) ||
<a name="L562" href="source/net/ipv4/tcp.c#L562">562</a>                          !<a href="ident?i=tp">tp</a>-&gt;urg_data ||
<a name="L563" href="source/net/ipv4/tcp.c#L563">563</a>                          <a href="ident?i=before">before</a>(<a href="ident?i=tp">tp</a>-&gt;urg_seq, <a href="ident?i=tp">tp</a>-&gt;copied_seq) ||
<a name="L564" href="source/net/ipv4/tcp.c#L564">564</a>                          !<a href="ident?i=before">before</a>(<a href="ident?i=tp">tp</a>-&gt;urg_seq, <a href="ident?i=tp">tp</a>-&gt;rcv_nxt)) {
<a name="L565" href="source/net/ipv4/tcp.c#L565">565</a> 
<a name="L566" href="source/net/ipv4/tcp.c#L566">566</a>                         answ = <a href="ident?i=tp">tp</a>-&gt;rcv_nxt - <a href="ident?i=tp">tp</a>-&gt;copied_seq;
<a name="L567" href="source/net/ipv4/tcp.c#L567">567</a> 
<a name="L568" href="source/net/ipv4/tcp.c#L568">568</a>                         <b><i>/* Subtract 1, if FIN was received */</i></b>
<a name="L569" href="source/net/ipv4/tcp.c#L569">569</a>                         if (answ &amp;&amp; <a href="ident?i=sock_flag">sock_flag</a>(sk, SOCK_DONE))
<a name="L570" href="source/net/ipv4/tcp.c#L570">570</a>                                 answ--;
<a name="L571" href="source/net/ipv4/tcp.c#L571">571</a>                 } else
<a name="L572" href="source/net/ipv4/tcp.c#L572">572</a>                         answ = <a href="ident?i=tp">tp</a>-&gt;urg_seq - <a href="ident?i=tp">tp</a>-&gt;copied_seq;
<a name="L573" href="source/net/ipv4/tcp.c#L573">573</a>                 <a href="ident?i=unlock_sock_fast">unlock_sock_fast</a>(sk, <a href="ident?i=slow">slow</a>);
<a name="L574" href="source/net/ipv4/tcp.c#L574">574</a>                 break;
<a name="L575" href="source/net/ipv4/tcp.c#L575">575</a>         case <a href="ident?i=SIOCATMARK">SIOCATMARK</a>:
<a name="L576" href="source/net/ipv4/tcp.c#L576">576</a>                 answ = <a href="ident?i=tp">tp</a>-&gt;urg_data &amp;&amp; <a href="ident?i=tp">tp</a>-&gt;urg_seq == <a href="ident?i=tp">tp</a>-&gt;copied_seq;
<a name="L577" href="source/net/ipv4/tcp.c#L577">577</a>                 break;
<a name="L578" href="source/net/ipv4/tcp.c#L578">578</a>         case <a href="ident?i=SIOCOUTQ">SIOCOUTQ</a>:
<a name="L579" href="source/net/ipv4/tcp.c#L579">579</a>                 if (sk-&gt;<a href="ident?i=sk_state">sk_state</a> == TCP_LISTEN)
<a name="L580" href="source/net/ipv4/tcp.c#L580">580</a>                         return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L581" href="source/net/ipv4/tcp.c#L581">581</a> 
<a name="L582" href="source/net/ipv4/tcp.c#L582">582</a>                 if ((1 &lt;&lt; sk-&gt;<a href="ident?i=sk_state">sk_state</a>) &amp; (TCPF_SYN_SENT | TCPF_SYN_RECV))
<a name="L583" href="source/net/ipv4/tcp.c#L583">583</a>                         answ = 0;
<a name="L584" href="source/net/ipv4/tcp.c#L584">584</a>                 else
<a name="L585" href="source/net/ipv4/tcp.c#L585">585</a>                         answ = <a href="ident?i=tp">tp</a>-&gt;write_seq - <a href="ident?i=tp">tp</a>-&gt;snd_una;
<a name="L586" href="source/net/ipv4/tcp.c#L586">586</a>                 break;
<a name="L587" href="source/net/ipv4/tcp.c#L587">587</a>         case <a href="ident?i=SIOCOUTQNSD">SIOCOUTQNSD</a>:
<a name="L588" href="source/net/ipv4/tcp.c#L588">588</a>                 if (sk-&gt;<a href="ident?i=sk_state">sk_state</a> == TCP_LISTEN)
<a name="L589" href="source/net/ipv4/tcp.c#L589">589</a>                         return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L590" href="source/net/ipv4/tcp.c#L590">590</a> 
<a name="L591" href="source/net/ipv4/tcp.c#L591">591</a>                 if ((1 &lt;&lt; sk-&gt;<a href="ident?i=sk_state">sk_state</a>) &amp; (TCPF_SYN_SENT | TCPF_SYN_RECV))
<a name="L592" href="source/net/ipv4/tcp.c#L592">592</a>                         answ = 0;
<a name="L593" href="source/net/ipv4/tcp.c#L593">593</a>                 else
<a name="L594" href="source/net/ipv4/tcp.c#L594">594</a>                         answ = <a href="ident?i=tp">tp</a>-&gt;write_seq - <a href="ident?i=tp">tp</a>-&gt;snd_nxt;
<a name="L595" href="source/net/ipv4/tcp.c#L595">595</a>                 break;
<a name="L596" href="source/net/ipv4/tcp.c#L596">596</a>         default:
<a name="L597" href="source/net/ipv4/tcp.c#L597">597</a>                 return -<a href="ident?i=ENOIOCTLCMD">ENOIOCTLCMD</a>;
<a name="L598" href="source/net/ipv4/tcp.c#L598">598</a>         }
<a name="L599" href="source/net/ipv4/tcp.c#L599">599</a> 
<a name="L600" href="source/net/ipv4/tcp.c#L600">600</a>         return <a href="ident?i=put_user">put_user</a>(answ, (int <a href="ident?i=__user">__user</a> *)<a href="ident?i=arg">arg</a>);
<a name="L601" href="source/net/ipv4/tcp.c#L601">601</a> }
<a name="L602" href="source/net/ipv4/tcp.c#L602">602</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=tcp_ioctl">tcp_ioctl</a>);
<a name="L603" href="source/net/ipv4/tcp.c#L603">603</a> 
<a name="L604" href="source/net/ipv4/tcp.c#L604">604</a> static inline void <a href="ident?i=tcp_mark_push">tcp_mark_push</a>(struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a>, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L605" href="source/net/ipv4/tcp.c#L605">605</a> {
<a name="L606" href="source/net/ipv4/tcp.c#L606">606</a>         <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;tcp_flags |= <a href="ident?i=TCPHDR_PSH">TCPHDR_PSH</a>;
<a name="L607" href="source/net/ipv4/tcp.c#L607">607</a>         <a href="ident?i=tp">tp</a>-&gt;pushed_seq = <a href="ident?i=tp">tp</a>-&gt;write_seq;
<a name="L608" href="source/net/ipv4/tcp.c#L608">608</a> }
<a name="L609" href="source/net/ipv4/tcp.c#L609">609</a> 
<a name="L610" href="source/net/ipv4/tcp.c#L610">610</a> static inline <a href="ident?i=bool">bool</a> <a href="ident?i=forced_push">forced_push</a>(const struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a>)
<a name="L611" href="source/net/ipv4/tcp.c#L611">611</a> {
<a name="L612" href="source/net/ipv4/tcp.c#L612">612</a>         return <a href="ident?i=after">after</a>(<a href="ident?i=tp">tp</a>-&gt;write_seq, <a href="ident?i=tp">tp</a>-&gt;pushed_seq + (<a href="ident?i=tp">tp</a>-&gt;max_window &gt;&gt; 1));
<a name="L613" href="source/net/ipv4/tcp.c#L613">613</a> }
<a name="L614" href="source/net/ipv4/tcp.c#L614">614</a> 
<a name="L615" href="source/net/ipv4/tcp.c#L615">615</a> static void <a href="ident?i=skb_entail">skb_entail</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>)
<a name="L616" href="source/net/ipv4/tcp.c#L616">616</a> {
<a name="L617" href="source/net/ipv4/tcp.c#L617">617</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L618" href="source/net/ipv4/tcp.c#L618">618</a>         struct <a href="ident?i=tcp_skb_cb">tcp_skb_cb</a> *<a href="ident?i=tcb">tcb</a> = <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>);
<a name="L619" href="source/net/ipv4/tcp.c#L619">619</a> 
<a name="L620" href="source/net/ipv4/tcp.c#L620">620</a>         <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=csum">csum</a>    = 0;
<a name="L621" href="source/net/ipv4/tcp.c#L621">621</a>         <a href="ident?i=tcb">tcb</a>-&gt;<a href="ident?i=seq">seq</a>     = <a href="ident?i=tcb">tcb</a>-&gt;end_seq = <a href="ident?i=tp">tp</a>-&gt;write_seq;
<a name="L622" href="source/net/ipv4/tcp.c#L622">622</a>         <a href="ident?i=tcb">tcb</a>-&gt;tcp_flags = <a href="ident?i=TCPHDR_ACK">TCPHDR_ACK</a>;
<a name="L623" href="source/net/ipv4/tcp.c#L623">623</a>         <a href="ident?i=tcb">tcb</a>-&gt;sacked  = 0;
<a name="L624" href="source/net/ipv4/tcp.c#L624">624</a>         <a href="ident?i=__skb_header_release">__skb_header_release</a>(<a href="ident?i=skb">skb</a>);
<a name="L625" href="source/net/ipv4/tcp.c#L625">625</a>         <a href="ident?i=tcp_add_write_queue_tail">tcp_add_write_queue_tail</a>(sk, <a href="ident?i=skb">skb</a>);
<a name="L626" href="source/net/ipv4/tcp.c#L626">626</a>         sk-&gt;sk_wmem_queued += <a href="ident?i=skb">skb</a>-&gt;truesize;
<a name="L627" href="source/net/ipv4/tcp.c#L627">627</a>         <a href="ident?i=sk_mem_charge">sk_mem_charge</a>(sk, <a href="ident?i=skb">skb</a>-&gt;truesize);
<a name="L628" href="source/net/ipv4/tcp.c#L628">628</a>         if (<a href="ident?i=tp">tp</a>-&gt;nonagle &amp; <a href="ident?i=TCP_NAGLE_PUSH">TCP_NAGLE_PUSH</a>)
<a name="L629" href="source/net/ipv4/tcp.c#L629">629</a>                 <a href="ident?i=tp">tp</a>-&gt;nonagle &amp;= ~TCP_NAGLE_PUSH;
<a name="L630" href="source/net/ipv4/tcp.c#L630">630</a> }
<a name="L631" href="source/net/ipv4/tcp.c#L631">631</a> 
<a name="L632" href="source/net/ipv4/tcp.c#L632">632</a> static inline void <a href="ident?i=tcp_mark_urg">tcp_mark_urg</a>(struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a>, int <a href="ident?i=flags">flags</a>)
<a name="L633" href="source/net/ipv4/tcp.c#L633">633</a> {
<a name="L634" href="source/net/ipv4/tcp.c#L634">634</a>         if (<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=MSG_OOB">MSG_OOB</a>)
<a name="L635" href="source/net/ipv4/tcp.c#L635">635</a>                 <a href="ident?i=tp">tp</a>-&gt;snd_up = <a href="ident?i=tp">tp</a>-&gt;write_seq;
<a name="L636" href="source/net/ipv4/tcp.c#L636">636</a> }
<a name="L637" href="source/net/ipv4/tcp.c#L637">637</a> 
<a name="L638" href="source/net/ipv4/tcp.c#L638">638</a> <b><i>/* If a not yet filled skb is pushed, do not send it if</i></b>
<a name="L639" href="source/net/ipv4/tcp.c#L639">639</a> <b><i> * we have data packets in Qdisc or NIC queues :</i></b>
<a name="L640" href="source/net/ipv4/tcp.c#L640">640</a> <b><i> * Because TX completion will happen shortly, it gives a chance</i></b>
<a name="L641" href="source/net/ipv4/tcp.c#L641">641</a> <b><i> * to coalesce future sendmsg() payload into this skb, without</i></b>
<a name="L642" href="source/net/ipv4/tcp.c#L642">642</a> <b><i> * need for a timer, and with no latency trade off.</i></b>
<a name="L643" href="source/net/ipv4/tcp.c#L643">643</a> <b><i> * As packets containing data payload have a bigger truesize</i></b>
<a name="L644" href="source/net/ipv4/tcp.c#L644">644</a> <b><i> * than pure acks (dataless) packets, the last checks prevent</i></b>
<a name="L645" href="source/net/ipv4/tcp.c#L645">645</a> <b><i> * autocorking if we only have an ACK in Qdisc/NIC queues,</i></b>
<a name="L646" href="source/net/ipv4/tcp.c#L646">646</a> <b><i> * or if TX completion was delayed after we processed ACK packet.</i></b>
<a name="L647" href="source/net/ipv4/tcp.c#L647">647</a> <b><i> */</i></b>
<a name="L648" href="source/net/ipv4/tcp.c#L648">648</a> static <a href="ident?i=bool">bool</a> <a href="ident?i=tcp_should_autocork">tcp_should_autocork</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
<a name="L649" href="source/net/ipv4/tcp.c#L649">649</a>                                 int size_goal)
<a name="L650" href="source/net/ipv4/tcp.c#L650">650</a> {
<a name="L651" href="source/net/ipv4/tcp.c#L651">651</a>         return <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a> &lt; size_goal &amp;&amp;
<a name="L652" href="source/net/ipv4/tcp.c#L652">652</a>                <a href="ident?i=sysctl_tcp_autocorking">sysctl_tcp_autocorking</a> &amp;&amp;
<a name="L653" href="source/net/ipv4/tcp.c#L653">653</a>                <a href="ident?i=skb">skb</a> != <a href="ident?i=tcp_write_queue_head">tcp_write_queue_head</a>(sk) &amp;&amp;
<a name="L654" href="source/net/ipv4/tcp.c#L654">654</a>                <a href="ident?i=atomic_read">atomic_read</a>(&amp;sk-&gt;sk_wmem_alloc) &gt; <a href="ident?i=skb">skb</a>-&gt;truesize;
<a name="L655" href="source/net/ipv4/tcp.c#L655">655</a> }
<a name="L656" href="source/net/ipv4/tcp.c#L656">656</a> 
<a name="L657" href="source/net/ipv4/tcp.c#L657">657</a> static void <a href="ident?i=tcp_push">tcp_push</a>(struct <a href="ident?i=sock">sock</a> *sk, int <a href="ident?i=flags">flags</a>, int mss_now,
<a name="L658" href="source/net/ipv4/tcp.c#L658">658</a>                      int nonagle, int size_goal)
<a name="L659" href="source/net/ipv4/tcp.c#L659">659</a> {
<a name="L660" href="source/net/ipv4/tcp.c#L660">660</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L661" href="source/net/ipv4/tcp.c#L661">661</a>         struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>;
<a name="L662" href="source/net/ipv4/tcp.c#L662">662</a> 
<a name="L663" href="source/net/ipv4/tcp.c#L663">663</a>         if (!<a href="ident?i=tcp_send_head">tcp_send_head</a>(sk))
<a name="L664" href="source/net/ipv4/tcp.c#L664">664</a>                 return;
<a name="L665" href="source/net/ipv4/tcp.c#L665">665</a> 
<a name="L666" href="source/net/ipv4/tcp.c#L666">666</a>         <a href="ident?i=skb">skb</a> = <a href="ident?i=tcp_write_queue_tail">tcp_write_queue_tail</a>(sk);
<a name="L667" href="source/net/ipv4/tcp.c#L667">667</a>         if (!(<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=MSG_MORE">MSG_MORE</a>) || <a href="ident?i=forced_push">forced_push</a>(<a href="ident?i=tp">tp</a>))
<a name="L668" href="source/net/ipv4/tcp.c#L668">668</a>                 <a href="ident?i=tcp_mark_push">tcp_mark_push</a>(<a href="ident?i=tp">tp</a>, <a href="ident?i=skb">skb</a>);
<a name="L669" href="source/net/ipv4/tcp.c#L669">669</a> 
<a name="L670" href="source/net/ipv4/tcp.c#L670">670</a>         <a href="ident?i=tcp_mark_urg">tcp_mark_urg</a>(<a href="ident?i=tp">tp</a>, <a href="ident?i=flags">flags</a>);
<a name="L671" href="source/net/ipv4/tcp.c#L671">671</a> 
<a name="L672" href="source/net/ipv4/tcp.c#L672">672</a>         if (<a href="ident?i=tcp_should_autocork">tcp_should_autocork</a>(sk, <a href="ident?i=skb">skb</a>, size_goal)) {
<a name="L673" href="source/net/ipv4/tcp.c#L673">673</a> 
<a name="L674" href="source/net/ipv4/tcp.c#L674">674</a>                 <b><i>/* avoid atomic op if TSQ_THROTTLED bit is already set */</i></b>
<a name="L675" href="source/net/ipv4/tcp.c#L675">675</a>                 if (!<a href="ident?i=test_bit">test_bit</a>(TSQ_THROTTLED, &amp;<a href="ident?i=tp">tp</a>-&gt;<a href="ident?i=tsq_flags">tsq_flags</a>)) {
<a name="L676" href="source/net/ipv4/tcp.c#L676">676</a>                         <a href="ident?i=NET_INC_STATS">NET_INC_STATS</a>(<a href="ident?i=sock_net">sock_net</a>(sk), LINUX_MIB_TCPAUTOCORKING);
<a name="L677" href="source/net/ipv4/tcp.c#L677">677</a>                         <a href="ident?i=set_bit">set_bit</a>(TSQ_THROTTLED, &amp;<a href="ident?i=tp">tp</a>-&gt;<a href="ident?i=tsq_flags">tsq_flags</a>);
<a name="L678" href="source/net/ipv4/tcp.c#L678">678</a>                 }
<a name="L679" href="source/net/ipv4/tcp.c#L679">679</a>                 <b><i>/* It is possible TX completion already happened</i></b>
<a name="L680" href="source/net/ipv4/tcp.c#L680">680</a> <b><i>                 * before we set TSQ_THROTTLED.</i></b>
<a name="L681" href="source/net/ipv4/tcp.c#L681">681</a> <b><i>                 */</i></b>
<a name="L682" href="source/net/ipv4/tcp.c#L682">682</a>                 if (<a href="ident?i=atomic_read">atomic_read</a>(&amp;sk-&gt;sk_wmem_alloc) &gt; <a href="ident?i=skb">skb</a>-&gt;truesize)
<a name="L683" href="source/net/ipv4/tcp.c#L683">683</a>                         return;
<a name="L684" href="source/net/ipv4/tcp.c#L684">684</a>         }
<a name="L685" href="source/net/ipv4/tcp.c#L685">685</a> 
<a name="L686" href="source/net/ipv4/tcp.c#L686">686</a>         if (<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=MSG_MORE">MSG_MORE</a>)
<a name="L687" href="source/net/ipv4/tcp.c#L687">687</a>                 nonagle = <a href="ident?i=TCP_NAGLE_CORK">TCP_NAGLE_CORK</a>;
<a name="L688" href="source/net/ipv4/tcp.c#L688">688</a> 
<a name="L689" href="source/net/ipv4/tcp.c#L689">689</a>         <a href="ident?i=__tcp_push_pending_frames">__tcp_push_pending_frames</a>(sk, mss_now, nonagle);
<a name="L690" href="source/net/ipv4/tcp.c#L690">690</a> }
<a name="L691" href="source/net/ipv4/tcp.c#L691">691</a> 
<a name="L692" href="source/net/ipv4/tcp.c#L692">692</a> static int <a href="ident?i=tcp_splice_data_recv">tcp_splice_data_recv</a>(<a href="ident?i=read_descriptor_t">read_descriptor_t</a> *rd_desc, struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>,
<a name="L693" href="source/net/ipv4/tcp.c#L693">693</a>                                 unsigned int <a href="ident?i=offset">offset</a>, <a href="ident?i=size_t">size_t</a> <a href="ident?i=len">len</a>)
<a name="L694" href="source/net/ipv4/tcp.c#L694">694</a> {
<a name="L695" href="source/net/ipv4/tcp.c#L695">695</a>         struct <a href="ident?i=tcp_splice_state">tcp_splice_state</a> *tss = rd_desc-&gt;<a href="ident?i=arg">arg</a>.<a href="ident?i=data">data</a>;
<a name="L696" href="source/net/ipv4/tcp.c#L696">696</a>         int <a href="ident?i=ret">ret</a>;
<a name="L697" href="source/net/ipv4/tcp.c#L697">697</a> 
<a name="L698" href="source/net/ipv4/tcp.c#L698">698</a>         <a href="ident?i=ret">ret</a> = <a href="ident?i=skb_splice_bits">skb_splice_bits</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=offset">offset</a>, tss-&gt;<a href="ident?i=pipe">pipe</a>, <a href="ident?i=min">min</a>(rd_desc-&gt;<a href="ident?i=count">count</a>, <a href="ident?i=len">len</a>),
<a name="L699" href="source/net/ipv4/tcp.c#L699">699</a>                               tss-&gt;<a href="ident?i=flags">flags</a>);
<a name="L700" href="source/net/ipv4/tcp.c#L700">700</a>         if (<a href="ident?i=ret">ret</a> &gt; 0)
<a name="L701" href="source/net/ipv4/tcp.c#L701">701</a>                 rd_desc-&gt;<a href="ident?i=count">count</a> -= <a href="ident?i=ret">ret</a>;
<a name="L702" href="source/net/ipv4/tcp.c#L702">702</a>         return <a href="ident?i=ret">ret</a>;
<a name="L703" href="source/net/ipv4/tcp.c#L703">703</a> }
<a name="L704" href="source/net/ipv4/tcp.c#L704">704</a> 
<a name="L705" href="source/net/ipv4/tcp.c#L705">705</a> static int <a href="ident?i=__tcp_splice_read">__tcp_splice_read</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=tcp_splice_state">tcp_splice_state</a> *tss)
<a name="L706" href="source/net/ipv4/tcp.c#L706">706</a> {
<a name="L707" href="source/net/ipv4/tcp.c#L707">707</a>         <b><i>/* Store TCP splice context information in read_descriptor_t. */</i></b>
<a name="L708" href="source/net/ipv4/tcp.c#L708">708</a>         <a href="ident?i=read_descriptor_t">read_descriptor_t</a> rd_desc = {
<a name="L709" href="source/net/ipv4/tcp.c#L709">709</a>                 .<a href="ident?i=arg">arg</a>.<a href="ident?i=data">data</a> = tss,
<a name="L710" href="source/net/ipv4/tcp.c#L710">710</a>                 .<a href="ident?i=count">count</a>    = tss-&gt;<a href="ident?i=len">len</a>,
<a name="L711" href="source/net/ipv4/tcp.c#L711">711</a>         };
<a name="L712" href="source/net/ipv4/tcp.c#L712">712</a> 
<a name="L713" href="source/net/ipv4/tcp.c#L713">713</a>         return <a href="ident?i=tcp_read_sock">tcp_read_sock</a>(sk, &amp;rd_desc, <a href="ident?i=tcp_splice_data_recv">tcp_splice_data_recv</a>);
<a name="L714" href="source/net/ipv4/tcp.c#L714">714</a> }
<a name="L715" href="source/net/ipv4/tcp.c#L715">715</a> 
<a name="L716" href="source/net/ipv4/tcp.c#L716">716</a> <b><i>/**</i></b>
<a name="L717" href="source/net/ipv4/tcp.c#L717">717</a> <b><i> *  tcp_splice_read - splice data from TCP socket to a pipe</i></b>
<a name="L718" href="source/net/ipv4/tcp.c#L718">718</a> <b><i> * @sock:       socket to splice from</i></b>
<a name="L719" href="source/net/ipv4/tcp.c#L719">719</a> <b><i> * @ppos:       position (not valid)</i></b>
<a name="L720" href="source/net/ipv4/tcp.c#L720">720</a> <b><i> * @pipe:       pipe to splice to</i></b>
<a name="L721" href="source/net/ipv4/tcp.c#L721">721</a> <b><i> * @len:        number of bytes to splice</i></b>
<a name="L722" href="source/net/ipv4/tcp.c#L722">722</a> <b><i> * @flags:      splice modifier flags</i></b>
<a name="L723" href="source/net/ipv4/tcp.c#L723">723</a> <b><i> *</i></b>
<a name="L724" href="source/net/ipv4/tcp.c#L724">724</a> <b><i> * Description:</i></b>
<a name="L725" href="source/net/ipv4/tcp.c#L725">725</a> <b><i> *    Will read pages from given socket and fill them into a pipe.</i></b>
<a name="L726" href="source/net/ipv4/tcp.c#L726">726</a> <b><i> *</i></b>
<a name="L727" href="source/net/ipv4/tcp.c#L727">727</a> <b><i> **/</i></b>
<a name="L728" href="source/net/ipv4/tcp.c#L728">728</a> <a href="ident?i=ssize_t">ssize_t</a> <a href="ident?i=tcp_splice_read">tcp_splice_read</a>(struct <a href="ident?i=socket">socket</a> *<a href="ident?i=sock">sock</a>, <a href="ident?i=loff_t">loff_t</a> *<a href="ident?i=ppos">ppos</a>,
<a name="L729" href="source/net/ipv4/tcp.c#L729">729</a>                         struct <a href="ident?i=pipe_inode_info">pipe_inode_info</a> *<a href="ident?i=pipe">pipe</a>, <a href="ident?i=size_t">size_t</a> <a href="ident?i=len">len</a>,
<a name="L730" href="source/net/ipv4/tcp.c#L730">730</a>                         unsigned int <a href="ident?i=flags">flags</a>)
<a name="L731" href="source/net/ipv4/tcp.c#L731">731</a> {
<a name="L732" href="source/net/ipv4/tcp.c#L732">732</a>         struct <a href="ident?i=sock">sock</a> *sk = <a href="ident?i=sock">sock</a>-&gt;sk;
<a name="L733" href="source/net/ipv4/tcp.c#L733">733</a>         struct <a href="ident?i=tcp_splice_state">tcp_splice_state</a> tss = {
<a name="L734" href="source/net/ipv4/tcp.c#L734">734</a>                 .<a href="ident?i=pipe">pipe</a> = <a href="ident?i=pipe">pipe</a>,
<a name="L735" href="source/net/ipv4/tcp.c#L735">735</a>                 .<a href="ident?i=len">len</a> = <a href="ident?i=len">len</a>,
<a name="L736" href="source/net/ipv4/tcp.c#L736">736</a>                 .<a href="ident?i=flags">flags</a> = <a href="ident?i=flags">flags</a>,
<a name="L737" href="source/net/ipv4/tcp.c#L737">737</a>         };
<a name="L738" href="source/net/ipv4/tcp.c#L738">738</a>         long timeo;
<a name="L739" href="source/net/ipv4/tcp.c#L739">739</a>         <a href="ident?i=ssize_t">ssize_t</a> spliced;
<a name="L740" href="source/net/ipv4/tcp.c#L740">740</a>         int <a href="ident?i=ret">ret</a>;
<a name="L741" href="source/net/ipv4/tcp.c#L741">741</a> 
<a name="L742" href="source/net/ipv4/tcp.c#L742">742</a>         <a href="ident?i=sock_rps_record_flow">sock_rps_record_flow</a>(sk);
<a name="L743" href="source/net/ipv4/tcp.c#L743">743</a>         <b><i>/*</i></b>
<a name="L744" href="source/net/ipv4/tcp.c#L744">744</a> <b><i>         * We can't seek on a socket input</i></b>
<a name="L745" href="source/net/ipv4/tcp.c#L745">745</a> <b><i>         */</i></b>
<a name="L746" href="source/net/ipv4/tcp.c#L746">746</a>         if (<a href="ident?i=unlikely">unlikely</a>(*<a href="ident?i=ppos">ppos</a>))
<a name="L747" href="source/net/ipv4/tcp.c#L747">747</a>                 return -<a href="ident?i=ESPIPE">ESPIPE</a>;
<a name="L748" href="source/net/ipv4/tcp.c#L748">748</a> 
<a name="L749" href="source/net/ipv4/tcp.c#L749">749</a>         <a href="ident?i=ret">ret</a> = spliced = 0;
<a name="L750" href="source/net/ipv4/tcp.c#L750">750</a> 
<a name="L751" href="source/net/ipv4/tcp.c#L751">751</a>         <a href="ident?i=lock_sock">lock_sock</a>(sk);
<a name="L752" href="source/net/ipv4/tcp.c#L752">752</a> 
<a name="L753" href="source/net/ipv4/tcp.c#L753">753</a>         timeo = <a href="ident?i=sock_rcvtimeo">sock_rcvtimeo</a>(sk, <a href="ident?i=sock">sock</a>-&gt;<a href="ident?i=file">file</a>-&gt;f_flags &amp; <a href="ident?i=O_NONBLOCK">O_NONBLOCK</a>);
<a name="L754" href="source/net/ipv4/tcp.c#L754">754</a>         while (tss.<a href="ident?i=len">len</a>) {
<a name="L755" href="source/net/ipv4/tcp.c#L755">755</a>                 <a href="ident?i=ret">ret</a> = <a href="ident?i=__tcp_splice_read">__tcp_splice_read</a>(sk, &amp;tss);
<a name="L756" href="source/net/ipv4/tcp.c#L756">756</a>                 if (<a href="ident?i=ret">ret</a> &lt; 0)
<a name="L757" href="source/net/ipv4/tcp.c#L757">757</a>                         break;
<a name="L758" href="source/net/ipv4/tcp.c#L758">758</a>                 else if (!<a href="ident?i=ret">ret</a>) {
<a name="L759" href="source/net/ipv4/tcp.c#L759">759</a>                         if (spliced)
<a name="L760" href="source/net/ipv4/tcp.c#L760">760</a>                                 break;
<a name="L761" href="source/net/ipv4/tcp.c#L761">761</a>                         if (<a href="ident?i=sock_flag">sock_flag</a>(sk, SOCK_DONE))
<a name="L762" href="source/net/ipv4/tcp.c#L762">762</a>                                 break;
<a name="L763" href="source/net/ipv4/tcp.c#L763">763</a>                         if (sk-&gt;sk_err) {
<a name="L764" href="source/net/ipv4/tcp.c#L764">764</a>                                 <a href="ident?i=ret">ret</a> = <a href="ident?i=sock_error">sock_error</a>(sk);
<a name="L765" href="source/net/ipv4/tcp.c#L765">765</a>                                 break;
<a name="L766" href="source/net/ipv4/tcp.c#L766">766</a>                         }
<a name="L767" href="source/net/ipv4/tcp.c#L767">767</a>                         if (sk-&gt;sk_shutdown &amp; <a href="ident?i=RCV_SHUTDOWN">RCV_SHUTDOWN</a>)
<a name="L768" href="source/net/ipv4/tcp.c#L768">768</a>                                 break;
<a name="L769" href="source/net/ipv4/tcp.c#L769">769</a>                         if (sk-&gt;<a href="ident?i=sk_state">sk_state</a> == TCP_CLOSE) {
<a name="L770" href="source/net/ipv4/tcp.c#L770">770</a>                                 <b><i>/*</i></b>
<a name="L771" href="source/net/ipv4/tcp.c#L771">771</a> <b><i>                                 * This occurs when user tries to read</i></b>
<a name="L772" href="source/net/ipv4/tcp.c#L772">772</a> <b><i>                                 * from never connected socket.</i></b>
<a name="L773" href="source/net/ipv4/tcp.c#L773">773</a> <b><i>                                 */</i></b>
<a name="L774" href="source/net/ipv4/tcp.c#L774">774</a>                                 if (!<a href="ident?i=sock_flag">sock_flag</a>(sk, SOCK_DONE))
<a name="L775" href="source/net/ipv4/tcp.c#L775">775</a>                                         <a href="ident?i=ret">ret</a> = -<a href="ident?i=ENOTCONN">ENOTCONN</a>;
<a name="L776" href="source/net/ipv4/tcp.c#L776">776</a>                                 break;
<a name="L777" href="source/net/ipv4/tcp.c#L777">777</a>                         }
<a name="L778" href="source/net/ipv4/tcp.c#L778">778</a>                         if (!timeo) {
<a name="L779" href="source/net/ipv4/tcp.c#L779">779</a>                                 <a href="ident?i=ret">ret</a> = -<a href="ident?i=EAGAIN">EAGAIN</a>;
<a name="L780" href="source/net/ipv4/tcp.c#L780">780</a>                                 break;
<a name="L781" href="source/net/ipv4/tcp.c#L781">781</a>                         }
<a name="L782" href="source/net/ipv4/tcp.c#L782">782</a>                         <a href="ident?i=sk_wait_data">sk_wait_data</a>(sk, &amp;timeo);
<a name="L783" href="source/net/ipv4/tcp.c#L783">783</a>                         if (<a href="ident?i=signal_pending">signal_pending</a>(<a href="ident?i=current">current</a>)) {
<a name="L784" href="source/net/ipv4/tcp.c#L784">784</a>                                 <a href="ident?i=ret">ret</a> = <a href="ident?i=sock_intr_errno">sock_intr_errno</a>(timeo);
<a name="L785" href="source/net/ipv4/tcp.c#L785">785</a>                                 break;
<a name="L786" href="source/net/ipv4/tcp.c#L786">786</a>                         }
<a name="L787" href="source/net/ipv4/tcp.c#L787">787</a>                         continue;
<a name="L788" href="source/net/ipv4/tcp.c#L788">788</a>                 }
<a name="L789" href="source/net/ipv4/tcp.c#L789">789</a>                 tss.<a href="ident?i=len">len</a> -= <a href="ident?i=ret">ret</a>;
<a name="L790" href="source/net/ipv4/tcp.c#L790">790</a>                 spliced += <a href="ident?i=ret">ret</a>;
<a name="L791" href="source/net/ipv4/tcp.c#L791">791</a> 
<a name="L792" href="source/net/ipv4/tcp.c#L792">792</a>                 if (!timeo)
<a name="L793" href="source/net/ipv4/tcp.c#L793">793</a>                         break;
<a name="L794" href="source/net/ipv4/tcp.c#L794">794</a>                 <a href="ident?i=release_sock">release_sock</a>(sk);
<a name="L795" href="source/net/ipv4/tcp.c#L795">795</a>                 <a href="ident?i=lock_sock">lock_sock</a>(sk);
<a name="L796" href="source/net/ipv4/tcp.c#L796">796</a> 
<a name="L797" href="source/net/ipv4/tcp.c#L797">797</a>                 if (sk-&gt;sk_err || sk-&gt;<a href="ident?i=sk_state">sk_state</a> == TCP_CLOSE ||
<a name="L798" href="source/net/ipv4/tcp.c#L798">798</a>                     (sk-&gt;sk_shutdown &amp; <a href="ident?i=RCV_SHUTDOWN">RCV_SHUTDOWN</a>) ||
<a name="L799" href="source/net/ipv4/tcp.c#L799">799</a>                     <a href="ident?i=signal_pending">signal_pending</a>(<a href="ident?i=current">current</a>))
<a name="L800" href="source/net/ipv4/tcp.c#L800">800</a>                         break;
<a name="L801" href="source/net/ipv4/tcp.c#L801">801</a>         }
<a name="L802" href="source/net/ipv4/tcp.c#L802">802</a> 
<a name="L803" href="source/net/ipv4/tcp.c#L803">803</a>         <a href="ident?i=release_sock">release_sock</a>(sk);
<a name="L804" href="source/net/ipv4/tcp.c#L804">804</a> 
<a name="L805" href="source/net/ipv4/tcp.c#L805">805</a>         if (spliced)
<a name="L806" href="source/net/ipv4/tcp.c#L806">806</a>                 return spliced;
<a name="L807" href="source/net/ipv4/tcp.c#L807">807</a> 
<a name="L808" href="source/net/ipv4/tcp.c#L808">808</a>         return <a href="ident?i=ret">ret</a>;
<a name="L809" href="source/net/ipv4/tcp.c#L809">809</a> }
<a name="L810" href="source/net/ipv4/tcp.c#L810">810</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=tcp_splice_read">tcp_splice_read</a>);
<a name="L811" href="source/net/ipv4/tcp.c#L811">811</a> 
<a name="L812" href="source/net/ipv4/tcp.c#L812">812</a> struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=sk_stream_alloc_skb">sk_stream_alloc_skb</a>(struct <a href="ident?i=sock">sock</a> *sk, int <a href="ident?i=size">size</a>, <a href="ident?i=gfp_t">gfp_t</a> gfp)
<a name="L813" href="source/net/ipv4/tcp.c#L813">813</a> {
<a name="L814" href="source/net/ipv4/tcp.c#L814">814</a>         struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>;
<a name="L815" href="source/net/ipv4/tcp.c#L815">815</a> 
<a name="L816" href="source/net/ipv4/tcp.c#L816">816</a>         <b><i>/* The TCP header must be at least 32-bit aligned.  */</i></b>
<a name="L817" href="source/net/ipv4/tcp.c#L817">817</a>         <a href="ident?i=size">size</a> = <a href="ident?i=ALIGN">ALIGN</a>(<a href="ident?i=size">size</a>, 4);
<a name="L818" href="source/net/ipv4/tcp.c#L818">818</a> 
<a name="L819" href="source/net/ipv4/tcp.c#L819">819</a>         <a href="ident?i=skb">skb</a> = <a href="ident?i=alloc_skb_fclone">alloc_skb_fclone</a>(<a href="ident?i=size">size</a> + sk-&gt;<a href="ident?i=sk_prot">sk_prot</a>-&gt;max_header, gfp);
<a name="L820" href="source/net/ipv4/tcp.c#L820">820</a>         if (<a href="ident?i=skb">skb</a>) {
<a name="L821" href="source/net/ipv4/tcp.c#L821">821</a>                 if (<a href="ident?i=sk_wmem_schedule">sk_wmem_schedule</a>(sk, <a href="ident?i=skb">skb</a>-&gt;truesize)) {
<a name="L822" href="source/net/ipv4/tcp.c#L822">822</a>                         <a href="ident?i=skb_reserve">skb_reserve</a>(<a href="ident?i=skb">skb</a>, sk-&gt;<a href="ident?i=sk_prot">sk_prot</a>-&gt;max_header);
<a name="L823" href="source/net/ipv4/tcp.c#L823">823</a>                         <b><i>/*</i></b>
<a name="L824" href="source/net/ipv4/tcp.c#L824">824</a> <b><i>                         * Make sure that we have exactly size bytes</i></b>
<a name="L825" href="source/net/ipv4/tcp.c#L825">825</a> <b><i>                         * available to the caller, no more, no less.</i></b>
<a name="L826" href="source/net/ipv4/tcp.c#L826">826</a> <b><i>                         */</i></b>
<a name="L827" href="source/net/ipv4/tcp.c#L827">827</a>                         <a href="ident?i=skb">skb</a>-&gt;reserved_tailroom = <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=end">end</a> - <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=tail">tail</a> - <a href="ident?i=size">size</a>;
<a name="L828" href="source/net/ipv4/tcp.c#L828">828</a>                         return <a href="ident?i=skb">skb</a>;
<a name="L829" href="source/net/ipv4/tcp.c#L829">829</a>                 }
<a name="L830" href="source/net/ipv4/tcp.c#L830">830</a>                 <a href="ident?i=__kfree_skb">__kfree_skb</a>(<a href="ident?i=skb">skb</a>);
<a name="L831" href="source/net/ipv4/tcp.c#L831">831</a>         } else {
<a name="L832" href="source/net/ipv4/tcp.c#L832">832</a>                 sk-&gt;<a href="ident?i=sk_prot">sk_prot</a>-&gt;enter_memory_pressure(sk);
<a name="L833" href="source/net/ipv4/tcp.c#L833">833</a>                 <a href="ident?i=sk_stream_moderate_sndbuf">sk_stream_moderate_sndbuf</a>(sk);
<a name="L834" href="source/net/ipv4/tcp.c#L834">834</a>         }
<a name="L835" href="source/net/ipv4/tcp.c#L835">835</a>         return <a href="ident?i=NULL">NULL</a>;
<a name="L836" href="source/net/ipv4/tcp.c#L836">836</a> }
<a name="L837" href="source/net/ipv4/tcp.c#L837">837</a> 
<a name="L838" href="source/net/ipv4/tcp.c#L838">838</a> static unsigned int <a href="ident?i=tcp_xmit_size_goal">tcp_xmit_size_goal</a>(struct <a href="ident?i=sock">sock</a> *sk, <a href="ident?i=u32">u32</a> mss_now,
<a name="L839" href="source/net/ipv4/tcp.c#L839">839</a>                                        int large_allowed)
<a name="L840" href="source/net/ipv4/tcp.c#L840">840</a> {
<a name="L841" href="source/net/ipv4/tcp.c#L841">841</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L842" href="source/net/ipv4/tcp.c#L842">842</a>         <a href="ident?i=u32">u32</a> new_size_goal, size_goal;
<a name="L843" href="source/net/ipv4/tcp.c#L843">843</a> 
<a name="L844" href="source/net/ipv4/tcp.c#L844">844</a>         if (!large_allowed || !<a href="ident?i=sk_can_gso">sk_can_gso</a>(sk))
<a name="L845" href="source/net/ipv4/tcp.c#L845">845</a>                 return mss_now;
<a name="L846" href="source/net/ipv4/tcp.c#L846">846</a> 
<a name="L847" href="source/net/ipv4/tcp.c#L847">847</a>         <b><i>/* Note : tcp_tso_autosize() will eventually split this later */</i></b>
<a name="L848" href="source/net/ipv4/tcp.c#L848">848</a>         new_size_goal = sk-&gt;sk_gso_max_size - 1 - <a href="ident?i=MAX_TCP_HEADER">MAX_TCP_HEADER</a>;
<a name="L849" href="source/net/ipv4/tcp.c#L849">849</a>         new_size_goal = <a href="ident?i=tcp_bound_to_half_wnd">tcp_bound_to_half_wnd</a>(<a href="ident?i=tp">tp</a>, new_size_goal);
<a name="L850" href="source/net/ipv4/tcp.c#L850">850</a> 
<a name="L851" href="source/net/ipv4/tcp.c#L851">851</a>         <b><i>/* We try hard to avoid divides here */</i></b>
<a name="L852" href="source/net/ipv4/tcp.c#L852">852</a>         size_goal = <a href="ident?i=tp">tp</a>-&gt;gso_segs * mss_now;
<a name="L853" href="source/net/ipv4/tcp.c#L853">853</a>         if (<a href="ident?i=unlikely">unlikely</a>(new_size_goal &lt; size_goal ||
<a name="L854" href="source/net/ipv4/tcp.c#L854">854</a>                      new_size_goal &gt;= size_goal + mss_now)) {
<a name="L855" href="source/net/ipv4/tcp.c#L855">855</a>                 <a href="ident?i=tp">tp</a>-&gt;gso_segs = <a href="ident?i=min_t">min_t</a>(<a href="ident?i=u16">u16</a>, new_size_goal / mss_now,
<a name="L856" href="source/net/ipv4/tcp.c#L856">856</a>                                      sk-&gt;sk_gso_max_segs);
<a name="L857" href="source/net/ipv4/tcp.c#L857">857</a>                 size_goal = <a href="ident?i=tp">tp</a>-&gt;gso_segs * mss_now;
<a name="L858" href="source/net/ipv4/tcp.c#L858">858</a>         }
<a name="L859" href="source/net/ipv4/tcp.c#L859">859</a> 
<a name="L860" href="source/net/ipv4/tcp.c#L860">860</a>         return <a href="ident?i=max">max</a>(size_goal, mss_now);
<a name="L861" href="source/net/ipv4/tcp.c#L861">861</a> }
<a name="L862" href="source/net/ipv4/tcp.c#L862">862</a> 
<a name="L863" href="source/net/ipv4/tcp.c#L863">863</a> static int <a href="ident?i=tcp_send_mss">tcp_send_mss</a>(struct <a href="ident?i=sock">sock</a> *sk, int *size_goal, int <a href="ident?i=flags">flags</a>)
<a name="L864" href="source/net/ipv4/tcp.c#L864">864</a> {
<a name="L865" href="source/net/ipv4/tcp.c#L865">865</a>         int mss_now;
<a name="L866" href="source/net/ipv4/tcp.c#L866">866</a> 
<a name="L867" href="source/net/ipv4/tcp.c#L867">867</a>         mss_now = <a href="ident?i=tcp_current_mss">tcp_current_mss</a>(sk);
<a name="L868" href="source/net/ipv4/tcp.c#L868">868</a>         *size_goal = <a href="ident?i=tcp_xmit_size_goal">tcp_xmit_size_goal</a>(sk, mss_now, !(<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=MSG_OOB">MSG_OOB</a>));
<a name="L869" href="source/net/ipv4/tcp.c#L869">869</a> 
<a name="L870" href="source/net/ipv4/tcp.c#L870">870</a>         return mss_now;
<a name="L871" href="source/net/ipv4/tcp.c#L871">871</a> }
<a name="L872" href="source/net/ipv4/tcp.c#L872">872</a> 
<a name="L873" href="source/net/ipv4/tcp.c#L873">873</a> static <a href="ident?i=ssize_t">ssize_t</a> <a href="ident?i=do_tcp_sendpages">do_tcp_sendpages</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=page">page</a> *<a href="ident?i=page">page</a>, int <a href="ident?i=offset">offset</a>,
<a name="L874" href="source/net/ipv4/tcp.c#L874">874</a>                                 <a href="ident?i=size_t">size_t</a> <a href="ident?i=size">size</a>, int <a href="ident?i=flags">flags</a>)
<a name="L875" href="source/net/ipv4/tcp.c#L875">875</a> {
<a name="L876" href="source/net/ipv4/tcp.c#L876">876</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L877" href="source/net/ipv4/tcp.c#L877">877</a>         int mss_now, size_goal;
<a name="L878" href="source/net/ipv4/tcp.c#L878">878</a>         int <a href="ident?i=err">err</a>;
<a name="L879" href="source/net/ipv4/tcp.c#L879">879</a>         <a href="ident?i=ssize_t">ssize_t</a> copied;
<a name="L880" href="source/net/ipv4/tcp.c#L880">880</a>         long timeo = <a href="ident?i=sock_sndtimeo">sock_sndtimeo</a>(sk, <a href="ident?i=flags">flags</a> &amp; <a href="ident?i=MSG_DONTWAIT">MSG_DONTWAIT</a>);
<a name="L881" href="source/net/ipv4/tcp.c#L881">881</a> 
<a name="L882" href="source/net/ipv4/tcp.c#L882">882</a>         <b><i>/* Wait for a connection to finish. One exception is TCP Fast Open</i></b>
<a name="L883" href="source/net/ipv4/tcp.c#L883">883</a> <b><i>         * (passive side) where data is allowed to be sent before a connection</i></b>
<a name="L884" href="source/net/ipv4/tcp.c#L884">884</a> <b><i>         * is fully established.</i></b>
<a name="L885" href="source/net/ipv4/tcp.c#L885">885</a> <b><i>         */</i></b>
<a name="L886" href="source/net/ipv4/tcp.c#L886">886</a>         if (((1 &lt;&lt; sk-&gt;<a href="ident?i=sk_state">sk_state</a>) &amp; ~(TCPF_ESTABLISHED | TCPF_CLOSE_WAIT)) &amp;&amp;
<a name="L887" href="source/net/ipv4/tcp.c#L887">887</a>             !<a href="ident?i=tcp_passive_fastopen">tcp_passive_fastopen</a>(sk)) {
<a name="L888" href="source/net/ipv4/tcp.c#L888">888</a>                 if ((<a href="ident?i=err">err</a> = <a href="ident?i=sk_stream_wait_connect">sk_stream_wait_connect</a>(sk, &amp;timeo)) != 0)
<a name="L889" href="source/net/ipv4/tcp.c#L889">889</a>                         goto out_err;
<a name="L890" href="source/net/ipv4/tcp.c#L890">890</a>         }
<a name="L891" href="source/net/ipv4/tcp.c#L891">891</a> 
<a name="L892" href="source/net/ipv4/tcp.c#L892">892</a>         <a href="ident?i=clear_bit">clear_bit</a>(<a href="ident?i=SOCK_ASYNC_NOSPACE">SOCK_ASYNC_NOSPACE</a>, &amp;sk-&gt;sk_socket-&gt;<a href="ident?i=flags">flags</a>);
<a name="L893" href="source/net/ipv4/tcp.c#L893">893</a> 
<a name="L894" href="source/net/ipv4/tcp.c#L894">894</a>         mss_now = <a href="ident?i=tcp_send_mss">tcp_send_mss</a>(sk, &amp;size_goal, <a href="ident?i=flags">flags</a>);
<a name="L895" href="source/net/ipv4/tcp.c#L895">895</a>         copied = 0;
<a name="L896" href="source/net/ipv4/tcp.c#L896">896</a> 
<a name="L897" href="source/net/ipv4/tcp.c#L897">897</a>         <a href="ident?i=err">err</a> = -<a href="ident?i=EPIPE">EPIPE</a>;
<a name="L898" href="source/net/ipv4/tcp.c#L898">898</a>         if (sk-&gt;sk_err || (sk-&gt;sk_shutdown &amp; <a href="ident?i=SEND_SHUTDOWN">SEND_SHUTDOWN</a>))
<a name="L899" href="source/net/ipv4/tcp.c#L899">899</a>                 goto out_err;
<a name="L900" href="source/net/ipv4/tcp.c#L900">900</a> 
<a name="L901" href="source/net/ipv4/tcp.c#L901">901</a>         while (<a href="ident?i=size">size</a> &gt; 0) {
<a name="L902" href="source/net/ipv4/tcp.c#L902">902</a>                 struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a> = <a href="ident?i=tcp_write_queue_tail">tcp_write_queue_tail</a>(sk);
<a name="L903" href="source/net/ipv4/tcp.c#L903">903</a>                 int <a href="ident?i=copy">copy</a>, <a href="ident?i=i">i</a>;
<a name="L904" href="source/net/ipv4/tcp.c#L904">904</a>                 <a href="ident?i=bool">bool</a> can_coalesce;
<a name="L905" href="source/net/ipv4/tcp.c#L905">905</a> 
<a name="L906" href="source/net/ipv4/tcp.c#L906">906</a>                 if (!<a href="ident?i=tcp_send_head">tcp_send_head</a>(sk) || (<a href="ident?i=copy">copy</a> = size_goal - <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a>) &lt;= 0) {
<a name="L907" href="source/net/ipv4/tcp.c#L907">907</a> new_segment:
<a name="L908" href="source/net/ipv4/tcp.c#L908">908</a>                         if (!<a href="ident?i=sk_stream_memory_free">sk_stream_memory_free</a>(sk))
<a name="L909" href="source/net/ipv4/tcp.c#L909">909</a>                                 goto wait_for_sndbuf;
<a name="L910" href="source/net/ipv4/tcp.c#L910">910</a> 
<a name="L911" href="source/net/ipv4/tcp.c#L911">911</a>                         <a href="ident?i=skb">skb</a> = <a href="ident?i=sk_stream_alloc_skb">sk_stream_alloc_skb</a>(sk, 0, sk-&gt;sk_allocation);
<a name="L912" href="source/net/ipv4/tcp.c#L912">912</a>                         if (!<a href="ident?i=skb">skb</a>)
<a name="L913" href="source/net/ipv4/tcp.c#L913">913</a>                                 goto wait_for_memory;
<a name="L914" href="source/net/ipv4/tcp.c#L914">914</a> 
<a name="L915" href="source/net/ipv4/tcp.c#L915">915</a>                         <a href="ident?i=skb_entail">skb_entail</a>(sk, <a href="ident?i=skb">skb</a>);
<a name="L916" href="source/net/ipv4/tcp.c#L916">916</a>                         <a href="ident?i=copy">copy</a> = size_goal;
<a name="L917" href="source/net/ipv4/tcp.c#L917">917</a>                 }
<a name="L918" href="source/net/ipv4/tcp.c#L918">918</a> 
<a name="L919" href="source/net/ipv4/tcp.c#L919">919</a>                 if (<a href="ident?i=copy">copy</a> &gt; <a href="ident?i=size">size</a>)
<a name="L920" href="source/net/ipv4/tcp.c#L920">920</a>                         <a href="ident?i=copy">copy</a> = <a href="ident?i=size">size</a>;
<a name="L921" href="source/net/ipv4/tcp.c#L921">921</a> 
<a name="L922" href="source/net/ipv4/tcp.c#L922">922</a>                 <a href="ident?i=i">i</a> = <a href="ident?i=skb_shinfo">skb_shinfo</a>(<a href="ident?i=skb">skb</a>)-&gt;nr_frags;
<a name="L923" href="source/net/ipv4/tcp.c#L923">923</a>                 can_coalesce = <a href="ident?i=skb_can_coalesce">skb_can_coalesce</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=i">i</a>, <a href="ident?i=page">page</a>, <a href="ident?i=offset">offset</a>);
<a name="L924" href="source/net/ipv4/tcp.c#L924">924</a>                 if (!can_coalesce &amp;&amp; <a href="ident?i=i">i</a> &gt;= <a href="ident?i=MAX_SKB_FRAGS">MAX_SKB_FRAGS</a>) {
<a name="L925" href="source/net/ipv4/tcp.c#L925">925</a>                         <a href="ident?i=tcp_mark_push">tcp_mark_push</a>(<a href="ident?i=tp">tp</a>, <a href="ident?i=skb">skb</a>);
<a name="L926" href="source/net/ipv4/tcp.c#L926">926</a>                         goto new_segment;
<a name="L927" href="source/net/ipv4/tcp.c#L927">927</a>                 }
<a name="L928" href="source/net/ipv4/tcp.c#L928">928</a>                 if (!<a href="ident?i=sk_wmem_schedule">sk_wmem_schedule</a>(sk, <a href="ident?i=copy">copy</a>))
<a name="L929" href="source/net/ipv4/tcp.c#L929">929</a>                         goto wait_for_memory;
<a name="L930" href="source/net/ipv4/tcp.c#L930">930</a> 
<a name="L931" href="source/net/ipv4/tcp.c#L931">931</a>                 if (can_coalesce) {
<a name="L932" href="source/net/ipv4/tcp.c#L932">932</a>                         <a href="ident?i=skb_frag_size_add">skb_frag_size_add</a>(&amp;<a href="ident?i=skb_shinfo">skb_shinfo</a>(<a href="ident?i=skb">skb</a>)-&gt;frags[<a href="ident?i=i">i</a> - 1], <a href="ident?i=copy">copy</a>);
<a name="L933" href="source/net/ipv4/tcp.c#L933">933</a>                 } else {
<a name="L934" href="source/net/ipv4/tcp.c#L934">934</a>                         <a href="ident?i=get_page">get_page</a>(<a href="ident?i=page">page</a>);
<a name="L935" href="source/net/ipv4/tcp.c#L935">935</a>                         <a href="ident?i=skb_fill_page_desc">skb_fill_page_desc</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=i">i</a>, <a href="ident?i=page">page</a>, <a href="ident?i=offset">offset</a>, <a href="ident?i=copy">copy</a>);
<a name="L936" href="source/net/ipv4/tcp.c#L936">936</a>                 }
<a name="L937" href="source/net/ipv4/tcp.c#L937">937</a>                 <a href="ident?i=skb_shinfo">skb_shinfo</a>(<a href="ident?i=skb">skb</a>)-&gt;tx_flags |= SKBTX_SHARED_FRAG;
<a name="L938" href="source/net/ipv4/tcp.c#L938">938</a> 
<a name="L939" href="source/net/ipv4/tcp.c#L939">939</a>                 <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a> += <a href="ident?i=copy">copy</a>;
<a name="L940" href="source/net/ipv4/tcp.c#L940">940</a>                 <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=data_len">data_len</a> += <a href="ident?i=copy">copy</a>;
<a name="L941" href="source/net/ipv4/tcp.c#L941">941</a>                 <a href="ident?i=skb">skb</a>-&gt;truesize += <a href="ident?i=copy">copy</a>;
<a name="L942" href="source/net/ipv4/tcp.c#L942">942</a>                 sk-&gt;sk_wmem_queued += <a href="ident?i=copy">copy</a>;
<a name="L943" href="source/net/ipv4/tcp.c#L943">943</a>                 <a href="ident?i=sk_mem_charge">sk_mem_charge</a>(sk, <a href="ident?i=copy">copy</a>);
<a name="L944" href="source/net/ipv4/tcp.c#L944">944</a>                 <a href="ident?i=skb">skb</a>-&gt;ip_summed = <a href="ident?i=CHECKSUM_PARTIAL">CHECKSUM_PARTIAL</a>;
<a name="L945" href="source/net/ipv4/tcp.c#L945">945</a>                 <a href="ident?i=tp">tp</a>-&gt;write_seq += <a href="ident?i=copy">copy</a>;
<a name="L946" href="source/net/ipv4/tcp.c#L946">946</a>                 <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;end_seq += <a href="ident?i=copy">copy</a>;
<a name="L947" href="source/net/ipv4/tcp.c#L947">947</a>                 <a href="ident?i=tcp_skb_pcount_set">tcp_skb_pcount_set</a>(<a href="ident?i=skb">skb</a>, 0);
<a name="L948" href="source/net/ipv4/tcp.c#L948">948</a> 
<a name="L949" href="source/net/ipv4/tcp.c#L949">949</a>                 if (!copied)
<a name="L950" href="source/net/ipv4/tcp.c#L950">950</a>                         <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;tcp_flags &amp;= ~TCPHDR_PSH;
<a name="L951" href="source/net/ipv4/tcp.c#L951">951</a> 
<a name="L952" href="source/net/ipv4/tcp.c#L952">952</a>                 copied += <a href="ident?i=copy">copy</a>;
<a name="L953" href="source/net/ipv4/tcp.c#L953">953</a>                 <a href="ident?i=offset">offset</a> += <a href="ident?i=copy">copy</a>;
<a name="L954" href="source/net/ipv4/tcp.c#L954">954</a>                 if (!(<a href="ident?i=size">size</a> -= <a href="ident?i=copy">copy</a>)) {
<a name="L955" href="source/net/ipv4/tcp.c#L955">955</a>                         <a href="ident?i=tcp_tx_timestamp">tcp_tx_timestamp</a>(sk, <a href="ident?i=skb">skb</a>);
<a name="L956" href="source/net/ipv4/tcp.c#L956">956</a>                         goto <a href="ident?i=out">out</a>;
<a name="L957" href="source/net/ipv4/tcp.c#L957">957</a>                 }
<a name="L958" href="source/net/ipv4/tcp.c#L958">958</a> 
<a name="L959" href="source/net/ipv4/tcp.c#L959">959</a>                 if (<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a> &lt; size_goal || (<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=MSG_OOB">MSG_OOB</a>))
<a name="L960" href="source/net/ipv4/tcp.c#L960">960</a>                         continue;
<a name="L961" href="source/net/ipv4/tcp.c#L961">961</a> 
<a name="L962" href="source/net/ipv4/tcp.c#L962">962</a>                 if (<a href="ident?i=forced_push">forced_push</a>(<a href="ident?i=tp">tp</a>)) {
<a name="L963" href="source/net/ipv4/tcp.c#L963">963</a>                         <a href="ident?i=tcp_mark_push">tcp_mark_push</a>(<a href="ident?i=tp">tp</a>, <a href="ident?i=skb">skb</a>);
<a name="L964" href="source/net/ipv4/tcp.c#L964">964</a>                         <a href="ident?i=__tcp_push_pending_frames">__tcp_push_pending_frames</a>(sk, mss_now, <a href="ident?i=TCP_NAGLE_PUSH">TCP_NAGLE_PUSH</a>);
<a name="L965" href="source/net/ipv4/tcp.c#L965">965</a>                 } else if (<a href="ident?i=skb">skb</a> == <a href="ident?i=tcp_send_head">tcp_send_head</a>(sk))
<a name="L966" href="source/net/ipv4/tcp.c#L966">966</a>                         <a href="ident?i=tcp_push_one">tcp_push_one</a>(sk, mss_now);
<a name="L967" href="source/net/ipv4/tcp.c#L967">967</a>                 continue;
<a name="L968" href="source/net/ipv4/tcp.c#L968">968</a> 
<a name="L969" href="source/net/ipv4/tcp.c#L969">969</a> wait_for_sndbuf:
<a name="L970" href="source/net/ipv4/tcp.c#L970">970</a>                 <a href="ident?i=set_bit">set_bit</a>(<a href="ident?i=SOCK_NOSPACE">SOCK_NOSPACE</a>, &amp;sk-&gt;sk_socket-&gt;<a href="ident?i=flags">flags</a>);
<a name="L971" href="source/net/ipv4/tcp.c#L971">971</a> wait_for_memory:
<a name="L972" href="source/net/ipv4/tcp.c#L972">972</a>                 <a href="ident?i=tcp_push">tcp_push</a>(sk, <a href="ident?i=flags">flags</a> &amp; ~MSG_MORE, mss_now,
<a name="L973" href="source/net/ipv4/tcp.c#L973">973</a>                          <a href="ident?i=TCP_NAGLE_PUSH">TCP_NAGLE_PUSH</a>, size_goal);
<a name="L974" href="source/net/ipv4/tcp.c#L974">974</a> 
<a name="L975" href="source/net/ipv4/tcp.c#L975">975</a>                 if ((<a href="ident?i=err">err</a> = <a href="ident?i=sk_stream_wait_memory">sk_stream_wait_memory</a>(sk, &amp;timeo)) != 0)
<a name="L976" href="source/net/ipv4/tcp.c#L976">976</a>                         goto <a href="ident?i=do_error">do_error</a>;
<a name="L977" href="source/net/ipv4/tcp.c#L977">977</a> 
<a name="L978" href="source/net/ipv4/tcp.c#L978">978</a>                 mss_now = <a href="ident?i=tcp_send_mss">tcp_send_mss</a>(sk, &amp;size_goal, <a href="ident?i=flags">flags</a>);
<a name="L979" href="source/net/ipv4/tcp.c#L979">979</a>         }
<a name="L980" href="source/net/ipv4/tcp.c#L980">980</a> 
<a name="L981" href="source/net/ipv4/tcp.c#L981">981</a> <a href="ident?i=out">out</a>:
<a name="L982" href="source/net/ipv4/tcp.c#L982">982</a>         if (copied &amp;&amp; !(<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=MSG_SENDPAGE_NOTLAST">MSG_SENDPAGE_NOTLAST</a>))
<a name="L983" href="source/net/ipv4/tcp.c#L983">983</a>                 <a href="ident?i=tcp_push">tcp_push</a>(sk, <a href="ident?i=flags">flags</a>, mss_now, <a href="ident?i=tp">tp</a>-&gt;nonagle, size_goal);
<a name="L984" href="source/net/ipv4/tcp.c#L984">984</a>         return copied;
<a name="L985" href="source/net/ipv4/tcp.c#L985">985</a> 
<a name="L986" href="source/net/ipv4/tcp.c#L986">986</a> <a href="ident?i=do_error">do_error</a>:
<a name="L987" href="source/net/ipv4/tcp.c#L987">987</a>         if (copied)
<a name="L988" href="source/net/ipv4/tcp.c#L988">988</a>                 goto <a href="ident?i=out">out</a>;
<a name="L989" href="source/net/ipv4/tcp.c#L989">989</a> out_err:
<a name="L990" href="source/net/ipv4/tcp.c#L990">990</a>         return <a href="ident?i=sk_stream_error">sk_stream_error</a>(sk, <a href="ident?i=flags">flags</a>, <a href="ident?i=err">err</a>);
<a name="L991" href="source/net/ipv4/tcp.c#L991">991</a> }
<a name="L992" href="source/net/ipv4/tcp.c#L992">992</a> 
<a name="L993" href="source/net/ipv4/tcp.c#L993">993</a> int <a href="ident?i=tcp_sendpage">tcp_sendpage</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=page">page</a> *<a href="ident?i=page">page</a>, int <a href="ident?i=offset">offset</a>,
<a name="L994" href="source/net/ipv4/tcp.c#L994">994</a>                  <a href="ident?i=size_t">size_t</a> <a href="ident?i=size">size</a>, int <a href="ident?i=flags">flags</a>)
<a name="L995" href="source/net/ipv4/tcp.c#L995">995</a> {
<a name="L996" href="source/net/ipv4/tcp.c#L996">996</a>         <a href="ident?i=ssize_t">ssize_t</a> <a href="ident?i=res">res</a>;
<a name="L997" href="source/net/ipv4/tcp.c#L997">997</a> 
<a name="L998" href="source/net/ipv4/tcp.c#L998">998</a>         if (!(sk-&gt;sk_route_caps &amp; <a href="ident?i=NETIF_F_SG">NETIF_F_SG</a>) ||
<a name="L999" href="source/net/ipv4/tcp.c#L999">999</a>             !(sk-&gt;sk_route_caps &amp; <a href="ident?i=NETIF_F_ALL_CSUM">NETIF_F_ALL_CSUM</a>))
<a name="L1000" href="source/net/ipv4/tcp.c#L1000">1000</a>                 return <a href="ident?i=sock_no_sendpage">sock_no_sendpage</a>(sk-&gt;sk_socket, <a href="ident?i=page">page</a>, <a href="ident?i=offset">offset</a>, <a href="ident?i=size">size</a>,
<a name="L1001" href="source/net/ipv4/tcp.c#L1001">1001</a>                                         <a href="ident?i=flags">flags</a>);
<a name="L1002" href="source/net/ipv4/tcp.c#L1002">1002</a> 
<a name="L1003" href="source/net/ipv4/tcp.c#L1003">1003</a>         <a href="ident?i=lock_sock">lock_sock</a>(sk);
<a name="L1004" href="source/net/ipv4/tcp.c#L1004">1004</a>         <a href="ident?i=res">res</a> = <a href="ident?i=do_tcp_sendpages">do_tcp_sendpages</a>(sk, <a href="ident?i=page">page</a>, <a href="ident?i=offset">offset</a>, <a href="ident?i=size">size</a>, <a href="ident?i=flags">flags</a>);
<a name="L1005" href="source/net/ipv4/tcp.c#L1005">1005</a>         <a href="ident?i=release_sock">release_sock</a>(sk);
<a name="L1006" href="source/net/ipv4/tcp.c#L1006">1006</a>         return <a href="ident?i=res">res</a>;
<a name="L1007" href="source/net/ipv4/tcp.c#L1007">1007</a> }
<a name="L1008" href="source/net/ipv4/tcp.c#L1008">1008</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=tcp_sendpage">tcp_sendpage</a>);
<a name="L1009" href="source/net/ipv4/tcp.c#L1009">1009</a> 
<a name="L1010" href="source/net/ipv4/tcp.c#L1010">1010</a> static inline int <a href="ident?i=select_size">select_size</a>(const struct <a href="ident?i=sock">sock</a> *sk, <a href="ident?i=bool">bool</a> sg)
<a name="L1011" href="source/net/ipv4/tcp.c#L1011">1011</a> {
<a name="L1012" href="source/net/ipv4/tcp.c#L1012">1012</a>         const struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L1013" href="source/net/ipv4/tcp.c#L1013">1013</a>         int <a href="ident?i=tmp">tmp</a> = <a href="ident?i=tp">tp</a>-&gt;mss_cache;
<a name="L1014" href="source/net/ipv4/tcp.c#L1014">1014</a> 
<a name="L1015" href="source/net/ipv4/tcp.c#L1015">1015</a>         if (sg) {
<a name="L1016" href="source/net/ipv4/tcp.c#L1016">1016</a>                 if (<a href="ident?i=sk_can_gso">sk_can_gso</a>(sk)) {
<a name="L1017" href="source/net/ipv4/tcp.c#L1017">1017</a>                         <b><i>/* Small frames wont use a full page:</i></b>
<a name="L1018" href="source/net/ipv4/tcp.c#L1018">1018</a> <b><i>                         * Payload will immediately follow tcp header.</i></b>
<a name="L1019" href="source/net/ipv4/tcp.c#L1019">1019</a> <b><i>                         */</i></b>
<a name="L1020" href="source/net/ipv4/tcp.c#L1020">1020</a>                         <a href="ident?i=tmp">tmp</a> = <a href="ident?i=SKB_WITH_OVERHEAD">SKB_WITH_OVERHEAD</a>(2048 - <a href="ident?i=MAX_TCP_HEADER">MAX_TCP_HEADER</a>);
<a name="L1021" href="source/net/ipv4/tcp.c#L1021">1021</a>                 } else {
<a name="L1022" href="source/net/ipv4/tcp.c#L1022">1022</a>                         int pgbreak = <a href="ident?i=SKB_MAX_HEAD">SKB_MAX_HEAD</a>(<a href="ident?i=MAX_TCP_HEADER">MAX_TCP_HEADER</a>);
<a name="L1023" href="source/net/ipv4/tcp.c#L1023">1023</a> 
<a name="L1024" href="source/net/ipv4/tcp.c#L1024">1024</a>                         if (<a href="ident?i=tmp">tmp</a> &gt;= pgbreak &amp;&amp;
<a name="L1025" href="source/net/ipv4/tcp.c#L1025">1025</a>                             <a href="ident?i=tmp">tmp</a> &lt;= pgbreak + (<a href="ident?i=MAX_SKB_FRAGS">MAX_SKB_FRAGS</a> - 1) * <a href="ident?i=PAGE_SIZE">PAGE_SIZE</a>)
<a name="L1026" href="source/net/ipv4/tcp.c#L1026">1026</a>                                 <a href="ident?i=tmp">tmp</a> = pgbreak;
<a name="L1027" href="source/net/ipv4/tcp.c#L1027">1027</a>                 }
<a name="L1028" href="source/net/ipv4/tcp.c#L1028">1028</a>         }
<a name="L1029" href="source/net/ipv4/tcp.c#L1029">1029</a> 
<a name="L1030" href="source/net/ipv4/tcp.c#L1030">1030</a>         return <a href="ident?i=tmp">tmp</a>;
<a name="L1031" href="source/net/ipv4/tcp.c#L1031">1031</a> }
<a name="L1032" href="source/net/ipv4/tcp.c#L1032">1032</a> 
<a name="L1033" href="source/net/ipv4/tcp.c#L1033">1033</a> void <a href="ident?i=tcp_free_fastopen_req">tcp_free_fastopen_req</a>(struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a>)
<a name="L1034" href="source/net/ipv4/tcp.c#L1034">1034</a> {
<a name="L1035" href="source/net/ipv4/tcp.c#L1035">1035</a>         if (<a href="ident?i=tp">tp</a>-&gt;fastopen_req) {
<a name="L1036" href="source/net/ipv4/tcp.c#L1036">1036</a>                 <a href="ident?i=kfree">kfree</a>(<a href="ident?i=tp">tp</a>-&gt;fastopen_req);
<a name="L1037" href="source/net/ipv4/tcp.c#L1037">1037</a>                 <a href="ident?i=tp">tp</a>-&gt;fastopen_req = <a href="ident?i=NULL">NULL</a>;
<a name="L1038" href="source/net/ipv4/tcp.c#L1038">1038</a>         }
<a name="L1039" href="source/net/ipv4/tcp.c#L1039">1039</a> }
<a name="L1040" href="source/net/ipv4/tcp.c#L1040">1040</a> 
<a name="L1041" href="source/net/ipv4/tcp.c#L1041">1041</a> static int <a href="ident?i=tcp_sendmsg_fastopen">tcp_sendmsg_fastopen</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=msghdr">msghdr</a> *<a href="ident?i=msg">msg</a>,
<a name="L1042" href="source/net/ipv4/tcp.c#L1042">1042</a>                                 int *copied, <a href="ident?i=size_t">size_t</a> <a href="ident?i=size">size</a>)
<a name="L1043" href="source/net/ipv4/tcp.c#L1043">1043</a> {
<a name="L1044" href="source/net/ipv4/tcp.c#L1044">1044</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L1045" href="source/net/ipv4/tcp.c#L1045">1045</a>         int <a href="ident?i=err">err</a>, <a href="ident?i=flags">flags</a>;
<a name="L1046" href="source/net/ipv4/tcp.c#L1046">1046</a> 
<a name="L1047" href="source/net/ipv4/tcp.c#L1047">1047</a>         if (!(<a href="ident?i=sysctl_tcp_fastopen">sysctl_tcp_fastopen</a> &amp; <a href="ident?i=TFO_CLIENT_ENABLE">TFO_CLIENT_ENABLE</a>))
<a name="L1048" href="source/net/ipv4/tcp.c#L1048">1048</a>                 return -<a href="ident?i=EOPNOTSUPP">EOPNOTSUPP</a>;
<a name="L1049" href="source/net/ipv4/tcp.c#L1049">1049</a>         if (<a href="ident?i=tp">tp</a>-&gt;fastopen_req)
<a name="L1050" href="source/net/ipv4/tcp.c#L1050">1050</a>                 return -<a href="ident?i=EALREADY">EALREADY</a>; <b><i>/* Another Fast Open is in progress */</i></b>
<a name="L1051" href="source/net/ipv4/tcp.c#L1051">1051</a> 
<a name="L1052" href="source/net/ipv4/tcp.c#L1052">1052</a>         <a href="ident?i=tp">tp</a>-&gt;fastopen_req = <a href="ident?i=kzalloc">kzalloc</a>(sizeof(struct <a href="ident?i=tcp_fastopen_request">tcp_fastopen_request</a>),
<a name="L1053" href="source/net/ipv4/tcp.c#L1053">1053</a>                                    sk-&gt;sk_allocation);
<a name="L1054" href="source/net/ipv4/tcp.c#L1054">1054</a>         if (<a href="ident?i=unlikely">unlikely</a>(!<a href="ident?i=tp">tp</a>-&gt;fastopen_req))
<a name="L1055" href="source/net/ipv4/tcp.c#L1055">1055</a>                 return -<a href="ident?i=ENOBUFS">ENOBUFS</a>;
<a name="L1056" href="source/net/ipv4/tcp.c#L1056">1056</a>         <a href="ident?i=tp">tp</a>-&gt;fastopen_req-&gt;<a href="ident?i=data">data</a> = <a href="ident?i=msg">msg</a>;
<a name="L1057" href="source/net/ipv4/tcp.c#L1057">1057</a>         <a href="ident?i=tp">tp</a>-&gt;fastopen_req-&gt;<a href="ident?i=size">size</a> = <a href="ident?i=size">size</a>;
<a name="L1058" href="source/net/ipv4/tcp.c#L1058">1058</a> 
<a name="L1059" href="source/net/ipv4/tcp.c#L1059">1059</a>         <a href="ident?i=flags">flags</a> = (<a href="ident?i=msg">msg</a>-&gt;msg_flags &amp; <a href="ident?i=MSG_DONTWAIT">MSG_DONTWAIT</a>) ? <a href="ident?i=O_NONBLOCK">O_NONBLOCK</a> : 0;
<a name="L1060" href="source/net/ipv4/tcp.c#L1060">1060</a>         <a href="ident?i=err">err</a> = <a href="ident?i=__inet_stream_connect">__inet_stream_connect</a>(sk-&gt;sk_socket, <a href="ident?i=msg">msg</a>-&gt;msg_name,
<a name="L1061" href="source/net/ipv4/tcp.c#L1061">1061</a>                                     <a href="ident?i=msg">msg</a>-&gt;msg_namelen, <a href="ident?i=flags">flags</a>);
<a name="L1062" href="source/net/ipv4/tcp.c#L1062">1062</a>         *copied = <a href="ident?i=tp">tp</a>-&gt;fastopen_req-&gt;copied;
<a name="L1063" href="source/net/ipv4/tcp.c#L1063">1063</a>         <a href="ident?i=tcp_free_fastopen_req">tcp_free_fastopen_req</a>(<a href="ident?i=tp">tp</a>);
<a name="L1064" href="source/net/ipv4/tcp.c#L1064">1064</a>         return <a href="ident?i=err">err</a>;
<a name="L1065" href="source/net/ipv4/tcp.c#L1065">1065</a> }
<a name="L1066" href="source/net/ipv4/tcp.c#L1066">1066</a> 
<a name="L1067" href="source/net/ipv4/tcp.c#L1067">1067</a> int <a href="ident?i=tcp_sendmsg">tcp_sendmsg</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=msghdr">msghdr</a> *<a href="ident?i=msg">msg</a>, <a href="ident?i=size_t">size_t</a> <a href="ident?i=size">size</a>)
<a name="L1068" href="source/net/ipv4/tcp.c#L1068">1068</a> {
<a name="L1069" href="source/net/ipv4/tcp.c#L1069">1069</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L1070" href="source/net/ipv4/tcp.c#L1070">1070</a>         struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>;
<a name="L1071" href="source/net/ipv4/tcp.c#L1071">1071</a>         int <a href="ident?i=flags">flags</a>, <a href="ident?i=err">err</a>, copied = 0;
<a name="L1072" href="source/net/ipv4/tcp.c#L1072">1072</a>         int mss_now = 0, size_goal, copied_syn = 0;
<a name="L1073" href="source/net/ipv4/tcp.c#L1073">1073</a>         <a href="ident?i=bool">bool</a> sg;
<a name="L1074" href="source/net/ipv4/tcp.c#L1074">1074</a>         long timeo;
<a name="L1075" href="source/net/ipv4/tcp.c#L1075">1075</a> 
<a name="L1076" href="source/net/ipv4/tcp.c#L1076">1076</a>         <a href="ident?i=lock_sock">lock_sock</a>(sk);
<a name="L1077" href="source/net/ipv4/tcp.c#L1077">1077</a> 
<a name="L1078" href="source/net/ipv4/tcp.c#L1078">1078</a>         <a href="ident?i=flags">flags</a> = <a href="ident?i=msg">msg</a>-&gt;msg_flags;
<a name="L1079" href="source/net/ipv4/tcp.c#L1079">1079</a>         if (<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=MSG_FASTOPEN">MSG_FASTOPEN</a>) {
<a name="L1080" href="source/net/ipv4/tcp.c#L1080">1080</a>                 <a href="ident?i=err">err</a> = <a href="ident?i=tcp_sendmsg_fastopen">tcp_sendmsg_fastopen</a>(sk, <a href="ident?i=msg">msg</a>, &amp;copied_syn, <a href="ident?i=size">size</a>);
<a name="L1081" href="source/net/ipv4/tcp.c#L1081">1081</a>                 if (<a href="ident?i=err">err</a> == -<a href="ident?i=EINPROGRESS">EINPROGRESS</a> &amp;&amp; copied_syn &gt; 0)
<a name="L1082" href="source/net/ipv4/tcp.c#L1082">1082</a>                         goto <a href="ident?i=out">out</a>;
<a name="L1083" href="source/net/ipv4/tcp.c#L1083">1083</a>                 else if (<a href="ident?i=err">err</a>)
<a name="L1084" href="source/net/ipv4/tcp.c#L1084">1084</a>                         goto out_err;
<a name="L1085" href="source/net/ipv4/tcp.c#L1085">1085</a>         }
<a name="L1086" href="source/net/ipv4/tcp.c#L1086">1086</a> 
<a name="L1087" href="source/net/ipv4/tcp.c#L1087">1087</a>         timeo = <a href="ident?i=sock_sndtimeo">sock_sndtimeo</a>(sk, <a href="ident?i=flags">flags</a> &amp; <a href="ident?i=MSG_DONTWAIT">MSG_DONTWAIT</a>);
<a name="L1088" href="source/net/ipv4/tcp.c#L1088">1088</a> 
<a name="L1089" href="source/net/ipv4/tcp.c#L1089">1089</a>         <b><i>/* Wait for a connection to finish. One exception is TCP Fast Open</i></b>
<a name="L1090" href="source/net/ipv4/tcp.c#L1090">1090</a> <b><i>         * (passive side) where data is allowed to be sent before a connection</i></b>
<a name="L1091" href="source/net/ipv4/tcp.c#L1091">1091</a> <b><i>         * is fully established.</i></b>
<a name="L1092" href="source/net/ipv4/tcp.c#L1092">1092</a> <b><i>         */</i></b>
<a name="L1093" href="source/net/ipv4/tcp.c#L1093">1093</a>         if (((1 &lt;&lt; sk-&gt;<a href="ident?i=sk_state">sk_state</a>) &amp; ~(TCPF_ESTABLISHED | TCPF_CLOSE_WAIT)) &amp;&amp;
<a name="L1094" href="source/net/ipv4/tcp.c#L1094">1094</a>             !<a href="ident?i=tcp_passive_fastopen">tcp_passive_fastopen</a>(sk)) {
<a name="L1095" href="source/net/ipv4/tcp.c#L1095">1095</a>                 if ((<a href="ident?i=err">err</a> = <a href="ident?i=sk_stream_wait_connect">sk_stream_wait_connect</a>(sk, &amp;timeo)) != 0)
<a name="L1096" href="source/net/ipv4/tcp.c#L1096">1096</a>                         goto <a href="ident?i=do_error">do_error</a>;
<a name="L1097" href="source/net/ipv4/tcp.c#L1097">1097</a>         }
<a name="L1098" href="source/net/ipv4/tcp.c#L1098">1098</a> 
<a name="L1099" href="source/net/ipv4/tcp.c#L1099">1099</a>         if (<a href="ident?i=unlikely">unlikely</a>(<a href="ident?i=tp">tp</a>-&gt;repair)) {
<a name="L1100" href="source/net/ipv4/tcp.c#L1100">1100</a>                 if (<a href="ident?i=tp">tp</a>-&gt;repair_queue == TCP_RECV_QUEUE) {
<a name="L1101" href="source/net/ipv4/tcp.c#L1101">1101</a>                         copied = <a href="ident?i=tcp_send_rcvq">tcp_send_rcvq</a>(sk, <a href="ident?i=msg">msg</a>, <a href="ident?i=size">size</a>);
<a name="L1102" href="source/net/ipv4/tcp.c#L1102">1102</a>                         goto out_nopush;
<a name="L1103" href="source/net/ipv4/tcp.c#L1103">1103</a>                 }
<a name="L1104" href="source/net/ipv4/tcp.c#L1104">1104</a> 
<a name="L1105" href="source/net/ipv4/tcp.c#L1105">1105</a>                 <a href="ident?i=err">err</a> = -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L1106" href="source/net/ipv4/tcp.c#L1106">1106</a>                 if (<a href="ident?i=tp">tp</a>-&gt;repair_queue == TCP_NO_QUEUE)
<a name="L1107" href="source/net/ipv4/tcp.c#L1107">1107</a>                         goto out_err;
<a name="L1108" href="source/net/ipv4/tcp.c#L1108">1108</a> 
<a name="L1109" href="source/net/ipv4/tcp.c#L1109">1109</a>                 <b><i>/* 'common' sending to sendq */</i></b>
<a name="L1110" href="source/net/ipv4/tcp.c#L1110">1110</a>         }
<a name="L1111" href="source/net/ipv4/tcp.c#L1111">1111</a> 
<a name="L1112" href="source/net/ipv4/tcp.c#L1112">1112</a>         <b><i>/* This should be in poll */</i></b>
<a name="L1113" href="source/net/ipv4/tcp.c#L1113">1113</a>         <a href="ident?i=clear_bit">clear_bit</a>(<a href="ident?i=SOCK_ASYNC_NOSPACE">SOCK_ASYNC_NOSPACE</a>, &amp;sk-&gt;sk_socket-&gt;<a href="ident?i=flags">flags</a>);
<a name="L1114" href="source/net/ipv4/tcp.c#L1114">1114</a> 
<a name="L1115" href="source/net/ipv4/tcp.c#L1115">1115</a>         mss_now = <a href="ident?i=tcp_send_mss">tcp_send_mss</a>(sk, &amp;size_goal, <a href="ident?i=flags">flags</a>);
<a name="L1116" href="source/net/ipv4/tcp.c#L1116">1116</a> 
<a name="L1117" href="source/net/ipv4/tcp.c#L1117">1117</a>         <b><i>/* Ok commence sending. */</i></b>
<a name="L1118" href="source/net/ipv4/tcp.c#L1118">1118</a>         copied = 0;
<a name="L1119" href="source/net/ipv4/tcp.c#L1119">1119</a> 
<a name="L1120" href="source/net/ipv4/tcp.c#L1120">1120</a>         <a href="ident?i=err">err</a> = -<a href="ident?i=EPIPE">EPIPE</a>;
<a name="L1121" href="source/net/ipv4/tcp.c#L1121">1121</a>         if (sk-&gt;sk_err || (sk-&gt;sk_shutdown &amp; <a href="ident?i=SEND_SHUTDOWN">SEND_SHUTDOWN</a>))
<a name="L1122" href="source/net/ipv4/tcp.c#L1122">1122</a>                 goto out_err;
<a name="L1123" href="source/net/ipv4/tcp.c#L1123">1123</a> 
<a name="L1124" href="source/net/ipv4/tcp.c#L1124">1124</a>         sg = !!(sk-&gt;sk_route_caps &amp; <a href="ident?i=NETIF_F_SG">NETIF_F_SG</a>);
<a name="L1125" href="source/net/ipv4/tcp.c#L1125">1125</a> 
<a name="L1126" href="source/net/ipv4/tcp.c#L1126">1126</a>         while (<a href="ident?i=msg_data_left">msg_data_left</a>(<a href="ident?i=msg">msg</a>)) {
<a name="L1127" href="source/net/ipv4/tcp.c#L1127">1127</a>                 int <a href="ident?i=copy">copy</a> = 0;
<a name="L1128" href="source/net/ipv4/tcp.c#L1128">1128</a>                 int <a href="ident?i=max">max</a> = size_goal;
<a name="L1129" href="source/net/ipv4/tcp.c#L1129">1129</a> 
<a name="L1130" href="source/net/ipv4/tcp.c#L1130">1130</a>                 <a href="ident?i=skb">skb</a> = <a href="ident?i=tcp_write_queue_tail">tcp_write_queue_tail</a>(sk);
<a name="L1131" href="source/net/ipv4/tcp.c#L1131">1131</a>                 if (<a href="ident?i=tcp_send_head">tcp_send_head</a>(sk)) {
<a name="L1132" href="source/net/ipv4/tcp.c#L1132">1132</a>                         if (<a href="ident?i=skb">skb</a>-&gt;ip_summed == <a href="ident?i=CHECKSUM_NONE">CHECKSUM_NONE</a>)
<a name="L1133" href="source/net/ipv4/tcp.c#L1133">1133</a>                                 <a href="ident?i=max">max</a> = mss_now;
<a name="L1134" href="source/net/ipv4/tcp.c#L1134">1134</a>                         <a href="ident?i=copy">copy</a> = <a href="ident?i=max">max</a> - <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a>;
<a name="L1135" href="source/net/ipv4/tcp.c#L1135">1135</a>                 }
<a name="L1136" href="source/net/ipv4/tcp.c#L1136">1136</a> 
<a name="L1137" href="source/net/ipv4/tcp.c#L1137">1137</a>                 if (<a href="ident?i=copy">copy</a> &lt;= 0) {
<a name="L1138" href="source/net/ipv4/tcp.c#L1138">1138</a> new_segment:
<a name="L1139" href="source/net/ipv4/tcp.c#L1139">1139</a>                         <b><i>/* Allocate new segment. If the interface is SG,</i></b>
<a name="L1140" href="source/net/ipv4/tcp.c#L1140">1140</a> <b><i>                         * allocate skb fitting to single page.</i></b>
<a name="L1141" href="source/net/ipv4/tcp.c#L1141">1141</a> <b><i>                         */</i></b>
<a name="L1142" href="source/net/ipv4/tcp.c#L1142">1142</a>                         if (!<a href="ident?i=sk_stream_memory_free">sk_stream_memory_free</a>(sk))
<a name="L1143" href="source/net/ipv4/tcp.c#L1143">1143</a>                                 goto wait_for_sndbuf;
<a name="L1144" href="source/net/ipv4/tcp.c#L1144">1144</a> 
<a name="L1145" href="source/net/ipv4/tcp.c#L1145">1145</a>                         <a href="ident?i=skb">skb</a> = <a href="ident?i=sk_stream_alloc_skb">sk_stream_alloc_skb</a>(sk,
<a name="L1146" href="source/net/ipv4/tcp.c#L1146">1146</a>                                                   <a href="ident?i=select_size">select_size</a>(sk, sg),
<a name="L1147" href="source/net/ipv4/tcp.c#L1147">1147</a>                                                   sk-&gt;sk_allocation);
<a name="L1148" href="source/net/ipv4/tcp.c#L1148">1148</a>                         if (!<a href="ident?i=skb">skb</a>)
<a name="L1149" href="source/net/ipv4/tcp.c#L1149">1149</a>                                 goto wait_for_memory;
<a name="L1150" href="source/net/ipv4/tcp.c#L1150">1150</a> 
<a name="L1151" href="source/net/ipv4/tcp.c#L1151">1151</a>                         <b><i>/*</i></b>
<a name="L1152" href="source/net/ipv4/tcp.c#L1152">1152</a> <b><i>                         * Check whether we can use HW checksum.</i></b>
<a name="L1153" href="source/net/ipv4/tcp.c#L1153">1153</a> <b><i>                         */</i></b>
<a name="L1154" href="source/net/ipv4/tcp.c#L1154">1154</a>                         if (sk-&gt;sk_route_caps &amp; <a href="ident?i=NETIF_F_ALL_CSUM">NETIF_F_ALL_CSUM</a>)
<a name="L1155" href="source/net/ipv4/tcp.c#L1155">1155</a>                                 <a href="ident?i=skb">skb</a>-&gt;ip_summed = <a href="ident?i=CHECKSUM_PARTIAL">CHECKSUM_PARTIAL</a>;
<a name="L1156" href="source/net/ipv4/tcp.c#L1156">1156</a> 
<a name="L1157" href="source/net/ipv4/tcp.c#L1157">1157</a>                         <a href="ident?i=skb_entail">skb_entail</a>(sk, <a href="ident?i=skb">skb</a>);
<a name="L1158" href="source/net/ipv4/tcp.c#L1158">1158</a>                         <a href="ident?i=copy">copy</a> = size_goal;
<a name="L1159" href="source/net/ipv4/tcp.c#L1159">1159</a>                         <a href="ident?i=max">max</a> = size_goal;
<a name="L1160" href="source/net/ipv4/tcp.c#L1160">1160</a> 
<a name="L1161" href="source/net/ipv4/tcp.c#L1161">1161</a>                         <b><i>/* All packets are restored as if they have</i></b>
<a name="L1162" href="source/net/ipv4/tcp.c#L1162">1162</a> <b><i>                         * already been sent. skb_mstamp isn't set to</i></b>
<a name="L1163" href="source/net/ipv4/tcp.c#L1163">1163</a> <b><i>                         * avoid wrong rtt estimation.</i></b>
<a name="L1164" href="source/net/ipv4/tcp.c#L1164">1164</a> <b><i>                         */</i></b>
<a name="L1165" href="source/net/ipv4/tcp.c#L1165">1165</a>                         if (<a href="ident?i=tp">tp</a>-&gt;repair)
<a name="L1166" href="source/net/ipv4/tcp.c#L1166">1166</a>                                 <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;sacked |= <a href="ident?i=TCPCB_REPAIRED">TCPCB_REPAIRED</a>;
<a name="L1167" href="source/net/ipv4/tcp.c#L1167">1167</a>                 }
<a name="L1168" href="source/net/ipv4/tcp.c#L1168">1168</a> 
<a name="L1169" href="source/net/ipv4/tcp.c#L1169">1169</a>                 <b><i>/* Try to append data to the end of skb. */</i></b>
<a name="L1170" href="source/net/ipv4/tcp.c#L1170">1170</a>                 if (<a href="ident?i=copy">copy</a> &gt; <a href="ident?i=msg_data_left">msg_data_left</a>(<a href="ident?i=msg">msg</a>))
<a name="L1171" href="source/net/ipv4/tcp.c#L1171">1171</a>                         <a href="ident?i=copy">copy</a> = <a href="ident?i=msg_data_left">msg_data_left</a>(<a href="ident?i=msg">msg</a>);
<a name="L1172" href="source/net/ipv4/tcp.c#L1172">1172</a> 
<a name="L1173" href="source/net/ipv4/tcp.c#L1173">1173</a>                 <b><i>/* Where to copy to? */</i></b>
<a name="L1174" href="source/net/ipv4/tcp.c#L1174">1174</a>                 if (<a href="ident?i=skb_availroom">skb_availroom</a>(<a href="ident?i=skb">skb</a>) &gt; 0) {
<a name="L1175" href="source/net/ipv4/tcp.c#L1175">1175</a>                         <b><i>/* We have some space in skb head. Superb! */</i></b>
<a name="L1176" href="source/net/ipv4/tcp.c#L1176">1176</a>                         <a href="ident?i=copy">copy</a> = <a href="ident?i=min_t">min_t</a>(int, <a href="ident?i=copy">copy</a>, <a href="ident?i=skb_availroom">skb_availroom</a>(<a href="ident?i=skb">skb</a>));
<a name="L1177" href="source/net/ipv4/tcp.c#L1177">1177</a>                         <a href="ident?i=err">err</a> = <a href="ident?i=skb_add_data_nocache">skb_add_data_nocache</a>(sk, <a href="ident?i=skb">skb</a>, &amp;<a href="ident?i=msg">msg</a>-&gt;msg_iter, <a href="ident?i=copy">copy</a>);
<a name="L1178" href="source/net/ipv4/tcp.c#L1178">1178</a>                         if (<a href="ident?i=err">err</a>)
<a name="L1179" href="source/net/ipv4/tcp.c#L1179">1179</a>                                 goto <a href="ident?i=do_fault">do_fault</a>;
<a name="L1180" href="source/net/ipv4/tcp.c#L1180">1180</a>                 } else {
<a name="L1181" href="source/net/ipv4/tcp.c#L1181">1181</a>                         <a href="ident?i=bool">bool</a> <a href="ident?i=merge">merge</a> = <a href="ident?i=true">true</a>;
<a name="L1182" href="source/net/ipv4/tcp.c#L1182">1182</a>                         int <a href="ident?i=i">i</a> = <a href="ident?i=skb_shinfo">skb_shinfo</a>(<a href="ident?i=skb">skb</a>)-&gt;nr_frags;
<a name="L1183" href="source/net/ipv4/tcp.c#L1183">1183</a>                         struct <a href="ident?i=page_frag">page_frag</a> *pfrag = <a href="ident?i=sk_page_frag">sk_page_frag</a>(sk);
<a name="L1184" href="source/net/ipv4/tcp.c#L1184">1184</a> 
<a name="L1185" href="source/net/ipv4/tcp.c#L1185">1185</a>                         if (!<a href="ident?i=sk_page_frag_refill">sk_page_frag_refill</a>(sk, pfrag))
<a name="L1186" href="source/net/ipv4/tcp.c#L1186">1186</a>                                 goto wait_for_memory;
<a name="L1187" href="source/net/ipv4/tcp.c#L1187">1187</a> 
<a name="L1188" href="source/net/ipv4/tcp.c#L1188">1188</a>                         if (!<a href="ident?i=skb_can_coalesce">skb_can_coalesce</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=i">i</a>, pfrag-&gt;<a href="ident?i=page">page</a>,
<a name="L1189" href="source/net/ipv4/tcp.c#L1189">1189</a>                                               pfrag-&gt;<a href="ident?i=offset">offset</a>)) {
<a name="L1190" href="source/net/ipv4/tcp.c#L1190">1190</a>                                 if (<a href="ident?i=i">i</a> == <a href="ident?i=MAX_SKB_FRAGS">MAX_SKB_FRAGS</a> || !sg) {
<a name="L1191" href="source/net/ipv4/tcp.c#L1191">1191</a>                                         <a href="ident?i=tcp_mark_push">tcp_mark_push</a>(<a href="ident?i=tp">tp</a>, <a href="ident?i=skb">skb</a>);
<a name="L1192" href="source/net/ipv4/tcp.c#L1192">1192</a>                                         goto new_segment;
<a name="L1193" href="source/net/ipv4/tcp.c#L1193">1193</a>                                 }
<a name="L1194" href="source/net/ipv4/tcp.c#L1194">1194</a>                                 <a href="ident?i=merge">merge</a> = <a href="ident?i=false">false</a>;
<a name="L1195" href="source/net/ipv4/tcp.c#L1195">1195</a>                         }
<a name="L1196" href="source/net/ipv4/tcp.c#L1196">1196</a> 
<a name="L1197" href="source/net/ipv4/tcp.c#L1197">1197</a>                         <a href="ident?i=copy">copy</a> = <a href="ident?i=min_t">min_t</a>(int, <a href="ident?i=copy">copy</a>, pfrag-&gt;<a href="ident?i=size">size</a> - pfrag-&gt;<a href="ident?i=offset">offset</a>);
<a name="L1198" href="source/net/ipv4/tcp.c#L1198">1198</a> 
<a name="L1199" href="source/net/ipv4/tcp.c#L1199">1199</a>                         if (!<a href="ident?i=sk_wmem_schedule">sk_wmem_schedule</a>(sk, <a href="ident?i=copy">copy</a>))
<a name="L1200" href="source/net/ipv4/tcp.c#L1200">1200</a>                                 goto wait_for_memory;
<a name="L1201" href="source/net/ipv4/tcp.c#L1201">1201</a> 
<a name="L1202" href="source/net/ipv4/tcp.c#L1202">1202</a>                         <a href="ident?i=err">err</a> = <a href="ident?i=skb_copy_to_page_nocache">skb_copy_to_page_nocache</a>(sk, &amp;<a href="ident?i=msg">msg</a>-&gt;msg_iter, <a href="ident?i=skb">skb</a>,
<a name="L1203" href="source/net/ipv4/tcp.c#L1203">1203</a>                                                        pfrag-&gt;<a href="ident?i=page">page</a>,
<a name="L1204" href="source/net/ipv4/tcp.c#L1204">1204</a>                                                        pfrag-&gt;<a href="ident?i=offset">offset</a>,
<a name="L1205" href="source/net/ipv4/tcp.c#L1205">1205</a>                                                        <a href="ident?i=copy">copy</a>);
<a name="L1206" href="source/net/ipv4/tcp.c#L1206">1206</a>                         if (<a href="ident?i=err">err</a>)
<a name="L1207" href="source/net/ipv4/tcp.c#L1207">1207</a>                                 goto <a href="ident?i=do_error">do_error</a>;
<a name="L1208" href="source/net/ipv4/tcp.c#L1208">1208</a> 
<a name="L1209" href="source/net/ipv4/tcp.c#L1209">1209</a>                         <b><i>/* Update the skb. */</i></b>
<a name="L1210" href="source/net/ipv4/tcp.c#L1210">1210</a>                         if (<a href="ident?i=merge">merge</a>) {
<a name="L1211" href="source/net/ipv4/tcp.c#L1211">1211</a>                                 <a href="ident?i=skb_frag_size_add">skb_frag_size_add</a>(&amp;<a href="ident?i=skb_shinfo">skb_shinfo</a>(<a href="ident?i=skb">skb</a>)-&gt;frags[<a href="ident?i=i">i</a> - 1], <a href="ident?i=copy">copy</a>);
<a name="L1212" href="source/net/ipv4/tcp.c#L1212">1212</a>                         } else {
<a name="L1213" href="source/net/ipv4/tcp.c#L1213">1213</a>                                 <a href="ident?i=skb_fill_page_desc">skb_fill_page_desc</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=i">i</a>, pfrag-&gt;<a href="ident?i=page">page</a>,
<a name="L1214" href="source/net/ipv4/tcp.c#L1214">1214</a>                                                    pfrag-&gt;<a href="ident?i=offset">offset</a>, <a href="ident?i=copy">copy</a>);
<a name="L1215" href="source/net/ipv4/tcp.c#L1215">1215</a>                                 <a href="ident?i=get_page">get_page</a>(pfrag-&gt;<a href="ident?i=page">page</a>);
<a name="L1216" href="source/net/ipv4/tcp.c#L1216">1216</a>                         }
<a name="L1217" href="source/net/ipv4/tcp.c#L1217">1217</a>                         pfrag-&gt;<a href="ident?i=offset">offset</a> += <a href="ident?i=copy">copy</a>;
<a name="L1218" href="source/net/ipv4/tcp.c#L1218">1218</a>                 }
<a name="L1219" href="source/net/ipv4/tcp.c#L1219">1219</a> 
<a name="L1220" href="source/net/ipv4/tcp.c#L1220">1220</a>                 if (!copied)
<a name="L1221" href="source/net/ipv4/tcp.c#L1221">1221</a>                         <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;tcp_flags &amp;= ~TCPHDR_PSH;
<a name="L1222" href="source/net/ipv4/tcp.c#L1222">1222</a> 
<a name="L1223" href="source/net/ipv4/tcp.c#L1223">1223</a>                 <a href="ident?i=tp">tp</a>-&gt;write_seq += <a href="ident?i=copy">copy</a>;
<a name="L1224" href="source/net/ipv4/tcp.c#L1224">1224</a>                 <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;end_seq += <a href="ident?i=copy">copy</a>;
<a name="L1225" href="source/net/ipv4/tcp.c#L1225">1225</a>                 <a href="ident?i=tcp_skb_pcount_set">tcp_skb_pcount_set</a>(<a href="ident?i=skb">skb</a>, 0);
<a name="L1226" href="source/net/ipv4/tcp.c#L1226">1226</a> 
<a name="L1227" href="source/net/ipv4/tcp.c#L1227">1227</a>                 copied += <a href="ident?i=copy">copy</a>;
<a name="L1228" href="source/net/ipv4/tcp.c#L1228">1228</a>                 if (!<a href="ident?i=msg_data_left">msg_data_left</a>(<a href="ident?i=msg">msg</a>)) {
<a name="L1229" href="source/net/ipv4/tcp.c#L1229">1229</a>                         <a href="ident?i=tcp_tx_timestamp">tcp_tx_timestamp</a>(sk, <a href="ident?i=skb">skb</a>);
<a name="L1230" href="source/net/ipv4/tcp.c#L1230">1230</a>                         goto <a href="ident?i=out">out</a>;
<a name="L1231" href="source/net/ipv4/tcp.c#L1231">1231</a>                 }
<a name="L1232" href="source/net/ipv4/tcp.c#L1232">1232</a> 
<a name="L1233" href="source/net/ipv4/tcp.c#L1233">1233</a>                 if (<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a> &lt; <a href="ident?i=max">max</a> || (<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=MSG_OOB">MSG_OOB</a>) || <a href="ident?i=unlikely">unlikely</a>(<a href="ident?i=tp">tp</a>-&gt;repair))
<a name="L1234" href="source/net/ipv4/tcp.c#L1234">1234</a>                         continue;
<a name="L1235" href="source/net/ipv4/tcp.c#L1235">1235</a> 
<a name="L1236" href="source/net/ipv4/tcp.c#L1236">1236</a>                 if (<a href="ident?i=forced_push">forced_push</a>(<a href="ident?i=tp">tp</a>)) {
<a name="L1237" href="source/net/ipv4/tcp.c#L1237">1237</a>                         <a href="ident?i=tcp_mark_push">tcp_mark_push</a>(<a href="ident?i=tp">tp</a>, <a href="ident?i=skb">skb</a>);
<a name="L1238" href="source/net/ipv4/tcp.c#L1238">1238</a>                         <a href="ident?i=__tcp_push_pending_frames">__tcp_push_pending_frames</a>(sk, mss_now, <a href="ident?i=TCP_NAGLE_PUSH">TCP_NAGLE_PUSH</a>);
<a name="L1239" href="source/net/ipv4/tcp.c#L1239">1239</a>                 } else if (<a href="ident?i=skb">skb</a> == <a href="ident?i=tcp_send_head">tcp_send_head</a>(sk))
<a name="L1240" href="source/net/ipv4/tcp.c#L1240">1240</a>                         <a href="ident?i=tcp_push_one">tcp_push_one</a>(sk, mss_now);
<a name="L1241" href="source/net/ipv4/tcp.c#L1241">1241</a>                 continue;
<a name="L1242" href="source/net/ipv4/tcp.c#L1242">1242</a> 
<a name="L1243" href="source/net/ipv4/tcp.c#L1243">1243</a> wait_for_sndbuf:
<a name="L1244" href="source/net/ipv4/tcp.c#L1244">1244</a>                 <a href="ident?i=set_bit">set_bit</a>(<a href="ident?i=SOCK_NOSPACE">SOCK_NOSPACE</a>, &amp;sk-&gt;sk_socket-&gt;<a href="ident?i=flags">flags</a>);
<a name="L1245" href="source/net/ipv4/tcp.c#L1245">1245</a> wait_for_memory:
<a name="L1246" href="source/net/ipv4/tcp.c#L1246">1246</a>                 if (copied)
<a name="L1247" href="source/net/ipv4/tcp.c#L1247">1247</a>                         <a href="ident?i=tcp_push">tcp_push</a>(sk, <a href="ident?i=flags">flags</a> &amp; ~MSG_MORE, mss_now,
<a name="L1248" href="source/net/ipv4/tcp.c#L1248">1248</a>                                  <a href="ident?i=TCP_NAGLE_PUSH">TCP_NAGLE_PUSH</a>, size_goal);
<a name="L1249" href="source/net/ipv4/tcp.c#L1249">1249</a> 
<a name="L1250" href="source/net/ipv4/tcp.c#L1250">1250</a>                 if ((<a href="ident?i=err">err</a> = <a href="ident?i=sk_stream_wait_memory">sk_stream_wait_memory</a>(sk, &amp;timeo)) != 0)
<a name="L1251" href="source/net/ipv4/tcp.c#L1251">1251</a>                         goto <a href="ident?i=do_error">do_error</a>;
<a name="L1252" href="source/net/ipv4/tcp.c#L1252">1252</a> 
<a name="L1253" href="source/net/ipv4/tcp.c#L1253">1253</a>                 mss_now = <a href="ident?i=tcp_send_mss">tcp_send_mss</a>(sk, &amp;size_goal, <a href="ident?i=flags">flags</a>);
<a name="L1254" href="source/net/ipv4/tcp.c#L1254">1254</a>         }
<a name="L1255" href="source/net/ipv4/tcp.c#L1255">1255</a> 
<a name="L1256" href="source/net/ipv4/tcp.c#L1256">1256</a> <a href="ident?i=out">out</a>:
<a name="L1257" href="source/net/ipv4/tcp.c#L1257">1257</a>         if (copied)
<a name="L1258" href="source/net/ipv4/tcp.c#L1258">1258</a>                 <a href="ident?i=tcp_push">tcp_push</a>(sk, <a href="ident?i=flags">flags</a>, mss_now, <a href="ident?i=tp">tp</a>-&gt;nonagle, size_goal);
<a name="L1259" href="source/net/ipv4/tcp.c#L1259">1259</a> out_nopush:
<a name="L1260" href="source/net/ipv4/tcp.c#L1260">1260</a>         <a href="ident?i=release_sock">release_sock</a>(sk);
<a name="L1261" href="source/net/ipv4/tcp.c#L1261">1261</a>         return copied + copied_syn;
<a name="L1262" href="source/net/ipv4/tcp.c#L1262">1262</a> 
<a name="L1263" href="source/net/ipv4/tcp.c#L1263">1263</a> <a href="ident?i=do_fault">do_fault</a>:
<a name="L1264" href="source/net/ipv4/tcp.c#L1264">1264</a>         if (!<a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a>) {
<a name="L1265" href="source/net/ipv4/tcp.c#L1265">1265</a>                 <a href="ident?i=tcp_unlink_write_queue">tcp_unlink_write_queue</a>(<a href="ident?i=skb">skb</a>, sk);
<a name="L1266" href="source/net/ipv4/tcp.c#L1266">1266</a>                 <b><i>/* It is the one place in all of TCP, except connection</i></b>
<a name="L1267" href="source/net/ipv4/tcp.c#L1267">1267</a> <b><i>                 * reset, where we can be unlinking the send_head.</i></b>
<a name="L1268" href="source/net/ipv4/tcp.c#L1268">1268</a> <b><i>                 */</i></b>
<a name="L1269" href="source/net/ipv4/tcp.c#L1269">1269</a>                 <a href="ident?i=tcp_check_send_head">tcp_check_send_head</a>(sk, <a href="ident?i=skb">skb</a>);
<a name="L1270" href="source/net/ipv4/tcp.c#L1270">1270</a>                 <a href="ident?i=sk_wmem_free_skb">sk_wmem_free_skb</a>(sk, <a href="ident?i=skb">skb</a>);
<a name="L1271" href="source/net/ipv4/tcp.c#L1271">1271</a>         }
<a name="L1272" href="source/net/ipv4/tcp.c#L1272">1272</a> 
<a name="L1273" href="source/net/ipv4/tcp.c#L1273">1273</a> <a href="ident?i=do_error">do_error</a>:
<a name="L1274" href="source/net/ipv4/tcp.c#L1274">1274</a>         if (copied + copied_syn)
<a name="L1275" href="source/net/ipv4/tcp.c#L1275">1275</a>                 goto <a href="ident?i=out">out</a>;
<a name="L1276" href="source/net/ipv4/tcp.c#L1276">1276</a> out_err:
<a name="L1277" href="source/net/ipv4/tcp.c#L1277">1277</a>         <a href="ident?i=err">err</a> = <a href="ident?i=sk_stream_error">sk_stream_error</a>(sk, <a href="ident?i=flags">flags</a>, <a href="ident?i=err">err</a>);
<a name="L1278" href="source/net/ipv4/tcp.c#L1278">1278</a>         <a href="ident?i=release_sock">release_sock</a>(sk);
<a name="L1279" href="source/net/ipv4/tcp.c#L1279">1279</a>         return <a href="ident?i=err">err</a>;
<a name="L1280" href="source/net/ipv4/tcp.c#L1280">1280</a> }
<a name="L1281" href="source/net/ipv4/tcp.c#L1281">1281</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=tcp_sendmsg">tcp_sendmsg</a>);
<a name="L1282" href="source/net/ipv4/tcp.c#L1282">1282</a> 
<a name="L1283" href="source/net/ipv4/tcp.c#L1283">1283</a> <b><i>/*</i></b>
<a name="L1284" href="source/net/ipv4/tcp.c#L1284">1284</a> <b><i> *      Handle reading urgent data. BSD has very simple semantics for</i></b>
<a name="L1285" href="source/net/ipv4/tcp.c#L1285">1285</a> <b><i> *      this, no blocking and very strange errors 8)</i></b>
<a name="L1286" href="source/net/ipv4/tcp.c#L1286">1286</a> <b><i> */</i></b>
<a name="L1287" href="source/net/ipv4/tcp.c#L1287">1287</a> 
<a name="L1288" href="source/net/ipv4/tcp.c#L1288">1288</a> static int <a href="ident?i=tcp_recv_urg">tcp_recv_urg</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=msghdr">msghdr</a> *<a href="ident?i=msg">msg</a>, int <a href="ident?i=len">len</a>, int <a href="ident?i=flags">flags</a>)
<a name="L1289" href="source/net/ipv4/tcp.c#L1289">1289</a> {
<a name="L1290" href="source/net/ipv4/tcp.c#L1290">1290</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L1291" href="source/net/ipv4/tcp.c#L1291">1291</a> 
<a name="L1292" href="source/net/ipv4/tcp.c#L1292">1292</a>         <b><i>/* No URG data to read. */</i></b>
<a name="L1293" href="source/net/ipv4/tcp.c#L1293">1293</a>         if (<a href="ident?i=sock_flag">sock_flag</a>(sk, SOCK_URGINLINE) || !<a href="ident?i=tp">tp</a>-&gt;urg_data ||
<a name="L1294" href="source/net/ipv4/tcp.c#L1294">1294</a>             <a href="ident?i=tp">tp</a>-&gt;urg_data == <a href="ident?i=TCP_URG_READ">TCP_URG_READ</a>)
<a name="L1295" href="source/net/ipv4/tcp.c#L1295">1295</a>                 return -<a href="ident?i=EINVAL">EINVAL</a>; <b><i>/* Yes this is right ! */</i></b>
<a name="L1296" href="source/net/ipv4/tcp.c#L1296">1296</a> 
<a name="L1297" href="source/net/ipv4/tcp.c#L1297">1297</a>         if (sk-&gt;<a href="ident?i=sk_state">sk_state</a> == TCP_CLOSE &amp;&amp; !<a href="ident?i=sock_flag">sock_flag</a>(sk, SOCK_DONE))
<a name="L1298" href="source/net/ipv4/tcp.c#L1298">1298</a>                 return -<a href="ident?i=ENOTCONN">ENOTCONN</a>;
<a name="L1299" href="source/net/ipv4/tcp.c#L1299">1299</a> 
<a name="L1300" href="source/net/ipv4/tcp.c#L1300">1300</a>         if (<a href="ident?i=tp">tp</a>-&gt;urg_data &amp; <a href="ident?i=TCP_URG_VALID">TCP_URG_VALID</a>) {
<a name="L1301" href="source/net/ipv4/tcp.c#L1301">1301</a>                 int <a href="ident?i=err">err</a> = 0;
<a name="L1302" href="source/net/ipv4/tcp.c#L1302">1302</a>                 char <a href="ident?i=c">c</a> = <a href="ident?i=tp">tp</a>-&gt;urg_data;
<a name="L1303" href="source/net/ipv4/tcp.c#L1303">1303</a> 
<a name="L1304" href="source/net/ipv4/tcp.c#L1304">1304</a>                 if (!(<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=MSG_PEEK">MSG_PEEK</a>))
<a name="L1305" href="source/net/ipv4/tcp.c#L1305">1305</a>                         <a href="ident?i=tp">tp</a>-&gt;urg_data = <a href="ident?i=TCP_URG_READ">TCP_URG_READ</a>;
<a name="L1306" href="source/net/ipv4/tcp.c#L1306">1306</a> 
<a name="L1307" href="source/net/ipv4/tcp.c#L1307">1307</a>                 <b><i>/* Read urgent data. */</i></b>
<a name="L1308" href="source/net/ipv4/tcp.c#L1308">1308</a>                 <a href="ident?i=msg">msg</a>-&gt;msg_flags |= <a href="ident?i=MSG_OOB">MSG_OOB</a>;
<a name="L1309" href="source/net/ipv4/tcp.c#L1309">1309</a> 
<a name="L1310" href="source/net/ipv4/tcp.c#L1310">1310</a>                 if (<a href="ident?i=len">len</a> &gt; 0) {
<a name="L1311" href="source/net/ipv4/tcp.c#L1311">1311</a>                         if (!(<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=MSG_TRUNC">MSG_TRUNC</a>))
<a name="L1312" href="source/net/ipv4/tcp.c#L1312">1312</a>                                 <a href="ident?i=err">err</a> = <a href="ident?i=memcpy_to_msg">memcpy_to_msg</a>(<a href="ident?i=msg">msg</a>, &amp;<a href="ident?i=c">c</a>, 1);
<a name="L1313" href="source/net/ipv4/tcp.c#L1313">1313</a>                         <a href="ident?i=len">len</a> = 1;
<a name="L1314" href="source/net/ipv4/tcp.c#L1314">1314</a>                 } else
<a name="L1315" href="source/net/ipv4/tcp.c#L1315">1315</a>                         <a href="ident?i=msg">msg</a>-&gt;msg_flags |= <a href="ident?i=MSG_TRUNC">MSG_TRUNC</a>;
<a name="L1316" href="source/net/ipv4/tcp.c#L1316">1316</a> 
<a name="L1317" href="source/net/ipv4/tcp.c#L1317">1317</a>                 return <a href="ident?i=err">err</a> ? -<a href="ident?i=EFAULT">EFAULT</a> : <a href="ident?i=len">len</a>;
<a name="L1318" href="source/net/ipv4/tcp.c#L1318">1318</a>         }
<a name="L1319" href="source/net/ipv4/tcp.c#L1319">1319</a> 
<a name="L1320" href="source/net/ipv4/tcp.c#L1320">1320</a>         if (sk-&gt;<a href="ident?i=sk_state">sk_state</a> == TCP_CLOSE || (sk-&gt;sk_shutdown &amp; <a href="ident?i=RCV_SHUTDOWN">RCV_SHUTDOWN</a>))
<a name="L1321" href="source/net/ipv4/tcp.c#L1321">1321</a>                 return 0;
<a name="L1322" href="source/net/ipv4/tcp.c#L1322">1322</a> 
<a name="L1323" href="source/net/ipv4/tcp.c#L1323">1323</a>         <b><i>/* Fixed the recv(..., MSG_OOB) behaviour.  BSD docs and</i></b>
<a name="L1324" href="source/net/ipv4/tcp.c#L1324">1324</a> <b><i>         * the available implementations agree in this case:</i></b>
<a name="L1325" href="source/net/ipv4/tcp.c#L1325">1325</a> <b><i>         * this call should never block, independent of the</i></b>
<a name="L1326" href="source/net/ipv4/tcp.c#L1326">1326</a> <b><i>         * blocking state of the socket.</i></b>
<a name="L1327" href="source/net/ipv4/tcp.c#L1327">1327</a> <b><i>         * Mike &lt;pall@rz.uni-karlsruhe.de&gt;</i></b>
<a name="L1328" href="source/net/ipv4/tcp.c#L1328">1328</a> <b><i>         */</i></b>
<a name="L1329" href="source/net/ipv4/tcp.c#L1329">1329</a>         return -<a href="ident?i=EAGAIN">EAGAIN</a>;
<a name="L1330" href="source/net/ipv4/tcp.c#L1330">1330</a> }
<a name="L1331" href="source/net/ipv4/tcp.c#L1331">1331</a> 
<a name="L1332" href="source/net/ipv4/tcp.c#L1332">1332</a> static int <a href="ident?i=tcp_peek_sndq">tcp_peek_sndq</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=msghdr">msghdr</a> *<a href="ident?i=msg">msg</a>, int <a href="ident?i=len">len</a>)
<a name="L1333" href="source/net/ipv4/tcp.c#L1333">1333</a> {
<a name="L1334" href="source/net/ipv4/tcp.c#L1334">1334</a>         struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>;
<a name="L1335" href="source/net/ipv4/tcp.c#L1335">1335</a>         int copied = 0, <a href="ident?i=err">err</a> = 0;
<a name="L1336" href="source/net/ipv4/tcp.c#L1336">1336</a> 
<a name="L1337" href="source/net/ipv4/tcp.c#L1337">1337</a>         <b><i>/* XXX -- need to support SO_PEEK_OFF */</i></b>
<a name="L1338" href="source/net/ipv4/tcp.c#L1338">1338</a> 
<a name="L1339" href="source/net/ipv4/tcp.c#L1339">1339</a>         <a href="ident?i=skb_queue_walk">skb_queue_walk</a>(&amp;sk-&gt;sk_write_queue, <a href="ident?i=skb">skb</a>) {
<a name="L1340" href="source/net/ipv4/tcp.c#L1340">1340</a>                 <a href="ident?i=err">err</a> = <a href="ident?i=skb_copy_datagram_msg">skb_copy_datagram_msg</a>(<a href="ident?i=skb">skb</a>, 0, <a href="ident?i=msg">msg</a>, <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a>);
<a name="L1341" href="source/net/ipv4/tcp.c#L1341">1341</a>                 if (<a href="ident?i=err">err</a>)
<a name="L1342" href="source/net/ipv4/tcp.c#L1342">1342</a>                         break;
<a name="L1343" href="source/net/ipv4/tcp.c#L1343">1343</a> 
<a name="L1344" href="source/net/ipv4/tcp.c#L1344">1344</a>                 copied += <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a>;
<a name="L1345" href="source/net/ipv4/tcp.c#L1345">1345</a>         }
<a name="L1346" href="source/net/ipv4/tcp.c#L1346">1346</a> 
<a name="L1347" href="source/net/ipv4/tcp.c#L1347">1347</a>         return <a href="ident?i=err">err</a> ?: copied;
<a name="L1348" href="source/net/ipv4/tcp.c#L1348">1348</a> }
<a name="L1349" href="source/net/ipv4/tcp.c#L1349">1349</a> 
<a name="L1350" href="source/net/ipv4/tcp.c#L1350">1350</a> <b><i>/* Clean up the receive buffer for full frames taken by the user,</i></b>
<a name="L1351" href="source/net/ipv4/tcp.c#L1351">1351</a> <b><i> * then send an ACK if necessary.  COPIED is the number of bytes</i></b>
<a name="L1352" href="source/net/ipv4/tcp.c#L1352">1352</a> <b><i> * tcp_recvmsg has given to the user so far, it speeds up the</i></b>
<a name="L1353" href="source/net/ipv4/tcp.c#L1353">1353</a> <b><i> * calculation of whether or not we must ACK for the sake of</i></b>
<a name="L1354" href="source/net/ipv4/tcp.c#L1354">1354</a> <b><i> * a window update.</i></b>
<a name="L1355" href="source/net/ipv4/tcp.c#L1355">1355</a> <b><i> */</i></b>
<a name="L1356" href="source/net/ipv4/tcp.c#L1356">1356</a> static void <a href="ident?i=tcp_cleanup_rbuf">tcp_cleanup_rbuf</a>(struct <a href="ident?i=sock">sock</a> *sk, int copied)
<a name="L1357" href="source/net/ipv4/tcp.c#L1357">1357</a> {
<a name="L1358" href="source/net/ipv4/tcp.c#L1358">1358</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L1359" href="source/net/ipv4/tcp.c#L1359">1359</a>         <a href="ident?i=bool">bool</a> time_to_ack = <a href="ident?i=false">false</a>;
<a name="L1360" href="source/net/ipv4/tcp.c#L1360">1360</a> 
<a name="L1361" href="source/net/ipv4/tcp.c#L1361">1361</a>         struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a> = <a href="ident?i=skb_peek">skb_peek</a>(&amp;sk-&gt;sk_receive_queue);
<a name="L1362" href="source/net/ipv4/tcp.c#L1362">1362</a> 
<a name="L1363" href="source/net/ipv4/tcp.c#L1363">1363</a>         <a href="ident?i=WARN">WARN</a>(<a href="ident?i=skb">skb</a> &amp;&amp; !<a href="ident?i=before">before</a>(<a href="ident?i=tp">tp</a>-&gt;copied_seq, <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;end_seq),
<a name="L1364" href="source/net/ipv4/tcp.c#L1364">1364</a>              <i>"cleanup rbuf bug: copied %X seq %X rcvnxt %X\n"</i>,
<a name="L1365" href="source/net/ipv4/tcp.c#L1365">1365</a>              <a href="ident?i=tp">tp</a>-&gt;copied_seq, <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;end_seq, <a href="ident?i=tp">tp</a>-&gt;rcv_nxt);
<a name="L1366" href="source/net/ipv4/tcp.c#L1366">1366</a> 
<a name="L1367" href="source/net/ipv4/tcp.c#L1367">1367</a>         if (<a href="ident?i=inet_csk_ack_scheduled">inet_csk_ack_scheduled</a>(sk)) {
<a name="L1368" href="source/net/ipv4/tcp.c#L1368">1368</a>                 const struct <a href="ident?i=inet_connection_sock">inet_connection_sock</a> *icsk = <a href="ident?i=inet_csk">inet_csk</a>(sk);
<a name="L1369" href="source/net/ipv4/tcp.c#L1369">1369</a>                    <b><i>/* Delayed ACKs frequently hit locked sockets during bulk</i></b>
<a name="L1370" href="source/net/ipv4/tcp.c#L1370">1370</a> <b><i>                    * receive. */</i></b>
<a name="L1371" href="source/net/ipv4/tcp.c#L1371">1371</a>                 if (icsk-&gt;icsk_ack.blocked ||
<a name="L1372" href="source/net/ipv4/tcp.c#L1372">1372</a>                     <b><i>/* Once-per-two-segments ACK was not sent by tcp_input.c */</i></b>
<a name="L1373" href="source/net/ipv4/tcp.c#L1373">1373</a>                     <a href="ident?i=tp">tp</a>-&gt;rcv_nxt - <a href="ident?i=tp">tp</a>-&gt;rcv_wup &gt; icsk-&gt;icsk_ack.rcv_mss ||
<a name="L1374" href="source/net/ipv4/tcp.c#L1374">1374</a>                     <b><i>/*</i></b>
<a name="L1375" href="source/net/ipv4/tcp.c#L1375">1375</a> <b><i>                     * If this read emptied read buffer, we send ACK, if</i></b>
<a name="L1376" href="source/net/ipv4/tcp.c#L1376">1376</a> <b><i>                     * connection is not bidirectional, user drained</i></b>
<a name="L1377" href="source/net/ipv4/tcp.c#L1377">1377</a> <b><i>                     * receive buffer and there was a small segment</i></b>
<a name="L1378" href="source/net/ipv4/tcp.c#L1378">1378</a> <b><i>                     * in queue.</i></b>
<a name="L1379" href="source/net/ipv4/tcp.c#L1379">1379</a> <b><i>                     */</i></b>
<a name="L1380" href="source/net/ipv4/tcp.c#L1380">1380</a>                     (copied &gt; 0 &amp;&amp;
<a name="L1381" href="source/net/ipv4/tcp.c#L1381">1381</a>                      ((icsk-&gt;icsk_ack.<a href="ident?i=pending">pending</a> &amp; ICSK_ACK_PUSHED2) ||
<a name="L1382" href="source/net/ipv4/tcp.c#L1382">1382</a>                       ((icsk-&gt;icsk_ack.<a href="ident?i=pending">pending</a> &amp; ICSK_ACK_PUSHED) &amp;&amp;
<a name="L1383" href="source/net/ipv4/tcp.c#L1383">1383</a>                        !icsk-&gt;icsk_ack.pingpong)) &amp;&amp;
<a name="L1384" href="source/net/ipv4/tcp.c#L1384">1384</a>                       !<a href="ident?i=atomic_read">atomic_read</a>(&amp;sk-&gt;<a href="ident?i=sk_rmem_alloc">sk_rmem_alloc</a>)))
<a name="L1385" href="source/net/ipv4/tcp.c#L1385">1385</a>                         time_to_ack = <a href="ident?i=true">true</a>;
<a name="L1386" href="source/net/ipv4/tcp.c#L1386">1386</a>         }
<a name="L1387" href="source/net/ipv4/tcp.c#L1387">1387</a> 
<a name="L1388" href="source/net/ipv4/tcp.c#L1388">1388</a>         <b><i>/* We send an ACK if we can now advertise a non-zero window</i></b>
<a name="L1389" href="source/net/ipv4/tcp.c#L1389">1389</a> <b><i>         * which has been raised "significantly".</i></b>
<a name="L1390" href="source/net/ipv4/tcp.c#L1390">1390</a> <b><i>         *</i></b>
<a name="L1391" href="source/net/ipv4/tcp.c#L1391">1391</a> <b><i>         * Even if window raised up to infinity, do not send window open ACK</i></b>
<a name="L1392" href="source/net/ipv4/tcp.c#L1392">1392</a> <b><i>         * in states, where we will not receive more. It is useless.</i></b>
<a name="L1393" href="source/net/ipv4/tcp.c#L1393">1393</a> <b><i>         */</i></b>
<a name="L1394" href="source/net/ipv4/tcp.c#L1394">1394</a>         if (copied &gt; 0 &amp;&amp; !time_to_ack &amp;&amp; !(sk-&gt;sk_shutdown &amp; <a href="ident?i=RCV_SHUTDOWN">RCV_SHUTDOWN</a>)) {
<a name="L1395" href="source/net/ipv4/tcp.c#L1395">1395</a>                 <a href="ident?i=__u32">__u32</a> rcv_window_now = <a href="ident?i=tcp_receive_window">tcp_receive_window</a>(<a href="ident?i=tp">tp</a>);
<a name="L1396" href="source/net/ipv4/tcp.c#L1396">1396</a> 
<a name="L1397" href="source/net/ipv4/tcp.c#L1397">1397</a>                 <b><i>/* Optimize, __tcp_select_window() is not cheap. */</i></b>
<a name="L1398" href="source/net/ipv4/tcp.c#L1398">1398</a>                 if (2*rcv_window_now &lt;= <a href="ident?i=tp">tp</a>-&gt;window_clamp) {
<a name="L1399" href="source/net/ipv4/tcp.c#L1399">1399</a>                         <a href="ident?i=__u32">__u32</a> new_window = <a href="ident?i=__tcp_select_window">__tcp_select_window</a>(sk);
<a name="L1400" href="source/net/ipv4/tcp.c#L1400">1400</a> 
<a name="L1401" href="source/net/ipv4/tcp.c#L1401">1401</a>                         <b><i>/* Send ACK now, if this read freed lots of space</i></b>
<a name="L1402" href="source/net/ipv4/tcp.c#L1402">1402</a> <b><i>                         * in our buffer. Certainly, new_window is new window.</i></b>
<a name="L1403" href="source/net/ipv4/tcp.c#L1403">1403</a> <b><i>                         * We can advertise it now, if it is not less than current one.</i></b>
<a name="L1404" href="source/net/ipv4/tcp.c#L1404">1404</a> <b><i>                         * "Lots" means "at least twice" here.</i></b>
<a name="L1405" href="source/net/ipv4/tcp.c#L1405">1405</a> <b><i>                         */</i></b>
<a name="L1406" href="source/net/ipv4/tcp.c#L1406">1406</a>                         if (new_window &amp;&amp; new_window &gt;= 2 * rcv_window_now)
<a name="L1407" href="source/net/ipv4/tcp.c#L1407">1407</a>                                 time_to_ack = <a href="ident?i=true">true</a>;
<a name="L1408" href="source/net/ipv4/tcp.c#L1408">1408</a>                 }
<a name="L1409" href="source/net/ipv4/tcp.c#L1409">1409</a>         }
<a name="L1410" href="source/net/ipv4/tcp.c#L1410">1410</a>         if (time_to_ack)
<a name="L1411" href="source/net/ipv4/tcp.c#L1411">1411</a>                 <a href="ident?i=tcp_send_ack">tcp_send_ack</a>(sk);
<a name="L1412" href="source/net/ipv4/tcp.c#L1412">1412</a> }
<a name="L1413" href="source/net/ipv4/tcp.c#L1413">1413</a> 
<a name="L1414" href="source/net/ipv4/tcp.c#L1414">1414</a> static void <a href="ident?i=tcp_prequeue_process">tcp_prequeue_process</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L1415" href="source/net/ipv4/tcp.c#L1415">1415</a> {
<a name="L1416" href="source/net/ipv4/tcp.c#L1416">1416</a>         struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>;
<a name="L1417" href="source/net/ipv4/tcp.c#L1417">1417</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L1418" href="source/net/ipv4/tcp.c#L1418">1418</a> 
<a name="L1419" href="source/net/ipv4/tcp.c#L1419">1419</a>         <a href="ident?i=NET_INC_STATS_USER">NET_INC_STATS_USER</a>(<a href="ident?i=sock_net">sock_net</a>(sk), LINUX_MIB_TCPPREQUEUED);
<a name="L1420" href="source/net/ipv4/tcp.c#L1420">1420</a> 
<a name="L1421" href="source/net/ipv4/tcp.c#L1421">1421</a>         <b><i>/* RX process wants to run with disabled BHs, though it is not</i></b>
<a name="L1422" href="source/net/ipv4/tcp.c#L1422">1422</a> <b><i>         * necessary */</i></b>
<a name="L1423" href="source/net/ipv4/tcp.c#L1423">1423</a>         <a href="ident?i=local_bh_disable">local_bh_disable</a>();
<a name="L1424" href="source/net/ipv4/tcp.c#L1424">1424</a>         while ((<a href="ident?i=skb">skb</a> = <a href="ident?i=__skb_dequeue">__skb_dequeue</a>(&amp;<a href="ident?i=tp">tp</a>-&gt;ucopy.prequeue)) != <a href="ident?i=NULL">NULL</a>)
<a name="L1425" href="source/net/ipv4/tcp.c#L1425">1425</a>                 <a href="ident?i=sk_backlog_rcv">sk_backlog_rcv</a>(sk, <a href="ident?i=skb">skb</a>);
<a name="L1426" href="source/net/ipv4/tcp.c#L1426">1426</a>         <a href="ident?i=local_bh_enable">local_bh_enable</a>();
<a name="L1427" href="source/net/ipv4/tcp.c#L1427">1427</a> 
<a name="L1428" href="source/net/ipv4/tcp.c#L1428">1428</a>         <b><i>/* Clear memory counter. */</i></b>
<a name="L1429" href="source/net/ipv4/tcp.c#L1429">1429</a>         <a href="ident?i=tp">tp</a>-&gt;ucopy.<a href="ident?i=memory">memory</a> = 0;
<a name="L1430" href="source/net/ipv4/tcp.c#L1430">1430</a> }
<a name="L1431" href="source/net/ipv4/tcp.c#L1431">1431</a> 
<a name="L1432" href="source/net/ipv4/tcp.c#L1432">1432</a> static struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=tcp_recv_skb">tcp_recv_skb</a>(struct <a href="ident?i=sock">sock</a> *sk, <a href="ident?i=u32">u32</a> <a href="ident?i=seq">seq</a>, <a href="ident?i=u32">u32</a> *<a href="ident?i=off">off</a>)
<a name="L1433" href="source/net/ipv4/tcp.c#L1433">1433</a> {
<a name="L1434" href="source/net/ipv4/tcp.c#L1434">1434</a>         struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>;
<a name="L1435" href="source/net/ipv4/tcp.c#L1435">1435</a>         <a href="ident?i=u32">u32</a> <a href="ident?i=offset">offset</a>;
<a name="L1436" href="source/net/ipv4/tcp.c#L1436">1436</a> 
<a name="L1437" href="source/net/ipv4/tcp.c#L1437">1437</a>         while ((<a href="ident?i=skb">skb</a> = <a href="ident?i=skb_peek">skb_peek</a>(&amp;sk-&gt;sk_receive_queue)) != <a href="ident?i=NULL">NULL</a>) {
<a name="L1438" href="source/net/ipv4/tcp.c#L1438">1438</a>                 <a href="ident?i=offset">offset</a> = <a href="ident?i=seq">seq</a> - <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=seq">seq</a>;
<a name="L1439" href="source/net/ipv4/tcp.c#L1439">1439</a>                 if (<a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;tcp_flags &amp; <a href="ident?i=TCPHDR_SYN">TCPHDR_SYN</a>)
<a name="L1440" href="source/net/ipv4/tcp.c#L1440">1440</a>                         <a href="ident?i=offset">offset</a>--;
<a name="L1441" href="source/net/ipv4/tcp.c#L1441">1441</a>                 if (<a href="ident?i=offset">offset</a> &lt; <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a> || (<a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;tcp_flags &amp; <a href="ident?i=TCPHDR_FIN">TCPHDR_FIN</a>)) {
<a name="L1442" href="source/net/ipv4/tcp.c#L1442">1442</a>                         *<a href="ident?i=off">off</a> = <a href="ident?i=offset">offset</a>;
<a name="L1443" href="source/net/ipv4/tcp.c#L1443">1443</a>                         return <a href="ident?i=skb">skb</a>;
<a name="L1444" href="source/net/ipv4/tcp.c#L1444">1444</a>                 }
<a name="L1445" href="source/net/ipv4/tcp.c#L1445">1445</a>                 <b><i>/* This looks weird, but this can happen if TCP collapsing</i></b>
<a name="L1446" href="source/net/ipv4/tcp.c#L1446">1446</a> <b><i>                 * splitted a fat GRO packet, while we released socket lock</i></b>
<a name="L1447" href="source/net/ipv4/tcp.c#L1447">1447</a> <b><i>                 * in skb_splice_bits()</i></b>
<a name="L1448" href="source/net/ipv4/tcp.c#L1448">1448</a> <b><i>                 */</i></b>
<a name="L1449" href="source/net/ipv4/tcp.c#L1449">1449</a>                 <a href="ident?i=sk_eat_skb">sk_eat_skb</a>(sk, <a href="ident?i=skb">skb</a>);
<a name="L1450" href="source/net/ipv4/tcp.c#L1450">1450</a>         }
<a name="L1451" href="source/net/ipv4/tcp.c#L1451">1451</a>         return <a href="ident?i=NULL">NULL</a>;
<a name="L1452" href="source/net/ipv4/tcp.c#L1452">1452</a> }
<a name="L1453" href="source/net/ipv4/tcp.c#L1453">1453</a> 
<a name="L1454" href="source/net/ipv4/tcp.c#L1454">1454</a> <b><i>/*</i></b>
<a name="L1455" href="source/net/ipv4/tcp.c#L1455">1455</a> <b><i> * This routine provides an alternative to tcp_recvmsg() for routines</i></b>
<a name="L1456" href="source/net/ipv4/tcp.c#L1456">1456</a> <b><i> * that would like to handle copying from skbuffs directly in 'sendfile'</i></b>
<a name="L1457" href="source/net/ipv4/tcp.c#L1457">1457</a> <b><i> * fashion.</i></b>
<a name="L1458" href="source/net/ipv4/tcp.c#L1458">1458</a> <b><i> * Note:</i></b>
<a name="L1459" href="source/net/ipv4/tcp.c#L1459">1459</a> <b><i> *      - It is assumed that the socket was locked by the caller.</i></b>
<a name="L1460" href="source/net/ipv4/tcp.c#L1460">1460</a> <b><i> *      - The routine does not block.</i></b>
<a name="L1461" href="source/net/ipv4/tcp.c#L1461">1461</a> <b><i> *      - At present, there is no support for reading OOB data</i></b>
<a name="L1462" href="source/net/ipv4/tcp.c#L1462">1462</a> <b><i> *        or for 'peeking' the socket using this routine</i></b>
<a name="L1463" href="source/net/ipv4/tcp.c#L1463">1463</a> <b><i> *        (although both would be easy to implement).</i></b>
<a name="L1464" href="source/net/ipv4/tcp.c#L1464">1464</a> <b><i> */</i></b>
<a name="L1465" href="source/net/ipv4/tcp.c#L1465">1465</a> int <a href="ident?i=tcp_read_sock">tcp_read_sock</a>(struct <a href="ident?i=sock">sock</a> *sk, <a href="ident?i=read_descriptor_t">read_descriptor_t</a> *<a href="ident?i=desc">desc</a>,
<a name="L1466" href="source/net/ipv4/tcp.c#L1466">1466</a>                   <a href="ident?i=sk_read_actor_t">sk_read_actor_t</a> recv_actor)
<a name="L1467" href="source/net/ipv4/tcp.c#L1467">1467</a> {
<a name="L1468" href="source/net/ipv4/tcp.c#L1468">1468</a>         struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>;
<a name="L1469" href="source/net/ipv4/tcp.c#L1469">1469</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L1470" href="source/net/ipv4/tcp.c#L1470">1470</a>         <a href="ident?i=u32">u32</a> <a href="ident?i=seq">seq</a> = <a href="ident?i=tp">tp</a>-&gt;copied_seq;
<a name="L1471" href="source/net/ipv4/tcp.c#L1471">1471</a>         <a href="ident?i=u32">u32</a> <a href="ident?i=offset">offset</a>;
<a name="L1472" href="source/net/ipv4/tcp.c#L1472">1472</a>         int copied = 0;
<a name="L1473" href="source/net/ipv4/tcp.c#L1473">1473</a> 
<a name="L1474" href="source/net/ipv4/tcp.c#L1474">1474</a>         if (sk-&gt;<a href="ident?i=sk_state">sk_state</a> == TCP_LISTEN)
<a name="L1475" href="source/net/ipv4/tcp.c#L1475">1475</a>                 return -<a href="ident?i=ENOTCONN">ENOTCONN</a>;
<a name="L1476" href="source/net/ipv4/tcp.c#L1476">1476</a>         while ((<a href="ident?i=skb">skb</a> = <a href="ident?i=tcp_recv_skb">tcp_recv_skb</a>(sk, <a href="ident?i=seq">seq</a>, &amp;<a href="ident?i=offset">offset</a>)) != <a href="ident?i=NULL">NULL</a>) {
<a name="L1477" href="source/net/ipv4/tcp.c#L1477">1477</a>                 if (<a href="ident?i=offset">offset</a> &lt; <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a>) {
<a name="L1478" href="source/net/ipv4/tcp.c#L1478">1478</a>                         int <a href="ident?i=used">used</a>;
<a name="L1479" href="source/net/ipv4/tcp.c#L1479">1479</a>                         <a href="ident?i=size_t">size_t</a> <a href="ident?i=len">len</a>;
<a name="L1480" href="source/net/ipv4/tcp.c#L1480">1480</a> 
<a name="L1481" href="source/net/ipv4/tcp.c#L1481">1481</a>                         <a href="ident?i=len">len</a> = <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a> - <a href="ident?i=offset">offset</a>;
<a name="L1482" href="source/net/ipv4/tcp.c#L1482">1482</a>                         <b><i>/* Stop reading if we hit a patch of urgent data */</i></b>
<a name="L1483" href="source/net/ipv4/tcp.c#L1483">1483</a>                         if (<a href="ident?i=tp">tp</a>-&gt;urg_data) {
<a name="L1484" href="source/net/ipv4/tcp.c#L1484">1484</a>                                 <a href="ident?i=u32">u32</a> urg_offset = <a href="ident?i=tp">tp</a>-&gt;urg_seq - <a href="ident?i=seq">seq</a>;
<a name="L1485" href="source/net/ipv4/tcp.c#L1485">1485</a>                                 if (urg_offset &lt; <a href="ident?i=len">len</a>)
<a name="L1486" href="source/net/ipv4/tcp.c#L1486">1486</a>                                         <a href="ident?i=len">len</a> = urg_offset;
<a name="L1487" href="source/net/ipv4/tcp.c#L1487">1487</a>                                 if (!<a href="ident?i=len">len</a>)
<a name="L1488" href="source/net/ipv4/tcp.c#L1488">1488</a>                                         break;
<a name="L1489" href="source/net/ipv4/tcp.c#L1489">1489</a>                         }
<a name="L1490" href="source/net/ipv4/tcp.c#L1490">1490</a>                         <a href="ident?i=used">used</a> = recv_actor(<a href="ident?i=desc">desc</a>, <a href="ident?i=skb">skb</a>, <a href="ident?i=offset">offset</a>, <a href="ident?i=len">len</a>);
<a name="L1491" href="source/net/ipv4/tcp.c#L1491">1491</a>                         if (<a href="ident?i=used">used</a> &lt;= 0) {
<a name="L1492" href="source/net/ipv4/tcp.c#L1492">1492</a>                                 if (!copied)
<a name="L1493" href="source/net/ipv4/tcp.c#L1493">1493</a>                                         copied = <a href="ident?i=used">used</a>;
<a name="L1494" href="source/net/ipv4/tcp.c#L1494">1494</a>                                 break;
<a name="L1495" href="source/net/ipv4/tcp.c#L1495">1495</a>                         } else if (<a href="ident?i=used">used</a> &lt;= <a href="ident?i=len">len</a>) {
<a name="L1496" href="source/net/ipv4/tcp.c#L1496">1496</a>                                 <a href="ident?i=seq">seq</a> += <a href="ident?i=used">used</a>;
<a name="L1497" href="source/net/ipv4/tcp.c#L1497">1497</a>                                 copied += <a href="ident?i=used">used</a>;
<a name="L1498" href="source/net/ipv4/tcp.c#L1498">1498</a>                                 <a href="ident?i=offset">offset</a> += <a href="ident?i=used">used</a>;
<a name="L1499" href="source/net/ipv4/tcp.c#L1499">1499</a>                         }
<a name="L1500" href="source/net/ipv4/tcp.c#L1500">1500</a>                         <b><i>/* If recv_actor drops the lock (e.g. TCP splice</i></b>
<a name="L1501" href="source/net/ipv4/tcp.c#L1501">1501</a> <b><i>                         * receive) the skb pointer might be invalid when</i></b>
<a name="L1502" href="source/net/ipv4/tcp.c#L1502">1502</a> <b><i>                         * getting here: tcp_collapse might have deleted it</i></b>
<a name="L1503" href="source/net/ipv4/tcp.c#L1503">1503</a> <b><i>                         * while aggregating skbs from the socket queue.</i></b>
<a name="L1504" href="source/net/ipv4/tcp.c#L1504">1504</a> <b><i>                         */</i></b>
<a name="L1505" href="source/net/ipv4/tcp.c#L1505">1505</a>                         <a href="ident?i=skb">skb</a> = <a href="ident?i=tcp_recv_skb">tcp_recv_skb</a>(sk, <a href="ident?i=seq">seq</a> - 1, &amp;<a href="ident?i=offset">offset</a>);
<a name="L1506" href="source/net/ipv4/tcp.c#L1506">1506</a>                         if (!<a href="ident?i=skb">skb</a>)
<a name="L1507" href="source/net/ipv4/tcp.c#L1507">1507</a>                                 break;
<a name="L1508" href="source/net/ipv4/tcp.c#L1508">1508</a>                         <b><i>/* TCP coalescing might have appended data to the skb.</i></b>
<a name="L1509" href="source/net/ipv4/tcp.c#L1509">1509</a> <b><i>                         * Try to splice more frags</i></b>
<a name="L1510" href="source/net/ipv4/tcp.c#L1510">1510</a> <b><i>                         */</i></b>
<a name="L1511" href="source/net/ipv4/tcp.c#L1511">1511</a>                         if (<a href="ident?i=offset">offset</a> + 1 != <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a>)
<a name="L1512" href="source/net/ipv4/tcp.c#L1512">1512</a>                                 continue;
<a name="L1513" href="source/net/ipv4/tcp.c#L1513">1513</a>                 }
<a name="L1514" href="source/net/ipv4/tcp.c#L1514">1514</a>                 if (<a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;tcp_flags &amp; <a href="ident?i=TCPHDR_FIN">TCPHDR_FIN</a>) {
<a name="L1515" href="source/net/ipv4/tcp.c#L1515">1515</a>                         <a href="ident?i=sk_eat_skb">sk_eat_skb</a>(sk, <a href="ident?i=skb">skb</a>);
<a name="L1516" href="source/net/ipv4/tcp.c#L1516">1516</a>                         ++<a href="ident?i=seq">seq</a>;
<a name="L1517" href="source/net/ipv4/tcp.c#L1517">1517</a>                         break;
<a name="L1518" href="source/net/ipv4/tcp.c#L1518">1518</a>                 }
<a name="L1519" href="source/net/ipv4/tcp.c#L1519">1519</a>                 <a href="ident?i=sk_eat_skb">sk_eat_skb</a>(sk, <a href="ident?i=skb">skb</a>);
<a name="L1520" href="source/net/ipv4/tcp.c#L1520">1520</a>                 if (!<a href="ident?i=desc">desc</a>-&gt;<a href="ident?i=count">count</a>)
<a name="L1521" href="source/net/ipv4/tcp.c#L1521">1521</a>                         break;
<a name="L1522" href="source/net/ipv4/tcp.c#L1522">1522</a>                 <a href="ident?i=tp">tp</a>-&gt;copied_seq = <a href="ident?i=seq">seq</a>;
<a name="L1523" href="source/net/ipv4/tcp.c#L1523">1523</a>         }
<a name="L1524" href="source/net/ipv4/tcp.c#L1524">1524</a>         <a href="ident?i=tp">tp</a>-&gt;copied_seq = <a href="ident?i=seq">seq</a>;
<a name="L1525" href="source/net/ipv4/tcp.c#L1525">1525</a> 
<a name="L1526" href="source/net/ipv4/tcp.c#L1526">1526</a>         <a href="ident?i=tcp_rcv_space_adjust">tcp_rcv_space_adjust</a>(sk);
<a name="L1527" href="source/net/ipv4/tcp.c#L1527">1527</a> 
<a name="L1528" href="source/net/ipv4/tcp.c#L1528">1528</a>         <b><i>/* Clean up data we have read: This will do ACK frames. */</i></b>
<a name="L1529" href="source/net/ipv4/tcp.c#L1529">1529</a>         if (copied &gt; 0) {
<a name="L1530" href="source/net/ipv4/tcp.c#L1530">1530</a>                 <a href="ident?i=tcp_recv_skb">tcp_recv_skb</a>(sk, <a href="ident?i=seq">seq</a>, &amp;<a href="ident?i=offset">offset</a>);
<a name="L1531" href="source/net/ipv4/tcp.c#L1531">1531</a>                 <a href="ident?i=tcp_cleanup_rbuf">tcp_cleanup_rbuf</a>(sk, copied);
<a name="L1532" href="source/net/ipv4/tcp.c#L1532">1532</a>         }
<a name="L1533" href="source/net/ipv4/tcp.c#L1533">1533</a>         return copied;
<a name="L1534" href="source/net/ipv4/tcp.c#L1534">1534</a> }
<a name="L1535" href="source/net/ipv4/tcp.c#L1535">1535</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=tcp_read_sock">tcp_read_sock</a>);
<a name="L1536" href="source/net/ipv4/tcp.c#L1536">1536</a> 
<a name="L1537" href="source/net/ipv4/tcp.c#L1537">1537</a> <b><i>/*</i></b>
<a name="L1538" href="source/net/ipv4/tcp.c#L1538">1538</a> <b><i> *      This routine copies from a sock struct into the user buffer.</i></b>
<a name="L1539" href="source/net/ipv4/tcp.c#L1539">1539</a> <b><i> *</i></b>
<a name="L1540" href="source/net/ipv4/tcp.c#L1540">1540</a> <b><i> *      Technical note: in 2.3 we work on _locked_ socket, so that</i></b>
<a name="L1541" href="source/net/ipv4/tcp.c#L1541">1541</a> <b><i> *      tricks with *seq access order and skb-&gt;users are not required.</i></b>
<a name="L1542" href="source/net/ipv4/tcp.c#L1542">1542</a> <b><i> *      Probably, code can be easily improved even more.</i></b>
<a name="L1543" href="source/net/ipv4/tcp.c#L1543">1543</a> <b><i> */</i></b>
<a name="L1544" href="source/net/ipv4/tcp.c#L1544">1544</a> 
<a name="L1545" href="source/net/ipv4/tcp.c#L1545">1545</a> int <a href="ident?i=tcp_recvmsg">tcp_recvmsg</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=msghdr">msghdr</a> *<a href="ident?i=msg">msg</a>, <a href="ident?i=size_t">size_t</a> <a href="ident?i=len">len</a>, int nonblock,
<a name="L1546" href="source/net/ipv4/tcp.c#L1546">1546</a>                 int <a href="ident?i=flags">flags</a>, int *addr_len)
<a name="L1547" href="source/net/ipv4/tcp.c#L1547">1547</a> {
<a name="L1548" href="source/net/ipv4/tcp.c#L1548">1548</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L1549" href="source/net/ipv4/tcp.c#L1549">1549</a>         int copied = 0;
<a name="L1550" href="source/net/ipv4/tcp.c#L1550">1550</a>         <a href="ident?i=u32">u32</a> peek_seq;
<a name="L1551" href="source/net/ipv4/tcp.c#L1551">1551</a>         <a href="ident?i=u32">u32</a> *<a href="ident?i=seq">seq</a>;
<a name="L1552" href="source/net/ipv4/tcp.c#L1552">1552</a>         unsigned long <a href="ident?i=used">used</a>;
<a name="L1553" href="source/net/ipv4/tcp.c#L1553">1553</a>         int <a href="ident?i=err">err</a>;
<a name="L1554" href="source/net/ipv4/tcp.c#L1554">1554</a>         int <a href="ident?i=target">target</a>;             <b><i>/* Read at least this many bytes */</i></b>
<a name="L1555" href="source/net/ipv4/tcp.c#L1555">1555</a>         long timeo;
<a name="L1556" href="source/net/ipv4/tcp.c#L1556">1556</a>         struct <a href="ident?i=task_struct">task_struct</a> *user_recv = <a href="ident?i=NULL">NULL</a>;
<a name="L1557" href="source/net/ipv4/tcp.c#L1557">1557</a>         struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>;
<a name="L1558" href="source/net/ipv4/tcp.c#L1558">1558</a>         <a href="ident?i=u32">u32</a> urg_hole = 0;
<a name="L1559" href="source/net/ipv4/tcp.c#L1559">1559</a> 
<a name="L1560" href="source/net/ipv4/tcp.c#L1560">1560</a>         if (<a href="ident?i=unlikely">unlikely</a>(<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=MSG_ERRQUEUE">MSG_ERRQUEUE</a>))
<a name="L1561" href="source/net/ipv4/tcp.c#L1561">1561</a>                 return <a href="ident?i=inet_recv_error">inet_recv_error</a>(sk, <a href="ident?i=msg">msg</a>, <a href="ident?i=len">len</a>, addr_len);
<a name="L1562" href="source/net/ipv4/tcp.c#L1562">1562</a> 
<a name="L1563" href="source/net/ipv4/tcp.c#L1563">1563</a>         if (<a href="ident?i=sk_can_busy_loop">sk_can_busy_loop</a>(sk) &amp;&amp; <a href="ident?i=skb_queue_empty">skb_queue_empty</a>(&amp;sk-&gt;sk_receive_queue) &amp;&amp;
<a name="L1564" href="source/net/ipv4/tcp.c#L1564">1564</a>             (sk-&gt;<a href="ident?i=sk_state">sk_state</a> == TCP_ESTABLISHED))
<a name="L1565" href="source/net/ipv4/tcp.c#L1565">1565</a>                 <a href="ident?i=sk_busy_loop">sk_busy_loop</a>(sk, nonblock);
<a name="L1566" href="source/net/ipv4/tcp.c#L1566">1566</a> 
<a name="L1567" href="source/net/ipv4/tcp.c#L1567">1567</a>         <a href="ident?i=lock_sock">lock_sock</a>(sk);
<a name="L1568" href="source/net/ipv4/tcp.c#L1568">1568</a> 
<a name="L1569" href="source/net/ipv4/tcp.c#L1569">1569</a>         <a href="ident?i=err">err</a> = -<a href="ident?i=ENOTCONN">ENOTCONN</a>;
<a name="L1570" href="source/net/ipv4/tcp.c#L1570">1570</a>         if (sk-&gt;<a href="ident?i=sk_state">sk_state</a> == TCP_LISTEN)
<a name="L1571" href="source/net/ipv4/tcp.c#L1571">1571</a>                 goto <a href="ident?i=out">out</a>;
<a name="L1572" href="source/net/ipv4/tcp.c#L1572">1572</a> 
<a name="L1573" href="source/net/ipv4/tcp.c#L1573">1573</a>         timeo = <a href="ident?i=sock_rcvtimeo">sock_rcvtimeo</a>(sk, nonblock);
<a name="L1574" href="source/net/ipv4/tcp.c#L1574">1574</a> 
<a name="L1575" href="source/net/ipv4/tcp.c#L1575">1575</a>         <b><i>/* Urgent data needs to be handled specially. */</i></b>
<a name="L1576" href="source/net/ipv4/tcp.c#L1576">1576</a>         if (<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=MSG_OOB">MSG_OOB</a>)
<a name="L1577" href="source/net/ipv4/tcp.c#L1577">1577</a>                 goto recv_urg;
<a name="L1578" href="source/net/ipv4/tcp.c#L1578">1578</a> 
<a name="L1579" href="source/net/ipv4/tcp.c#L1579">1579</a>         if (<a href="ident?i=unlikely">unlikely</a>(<a href="ident?i=tp">tp</a>-&gt;repair)) {
<a name="L1580" href="source/net/ipv4/tcp.c#L1580">1580</a>                 <a href="ident?i=err">err</a> = -<a href="ident?i=EPERM">EPERM</a>;
<a name="L1581" href="source/net/ipv4/tcp.c#L1581">1581</a>                 if (!(<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=MSG_PEEK">MSG_PEEK</a>))
<a name="L1582" href="source/net/ipv4/tcp.c#L1582">1582</a>                         goto <a href="ident?i=out">out</a>;
<a name="L1583" href="source/net/ipv4/tcp.c#L1583">1583</a> 
<a name="L1584" href="source/net/ipv4/tcp.c#L1584">1584</a>                 if (<a href="ident?i=tp">tp</a>-&gt;repair_queue == TCP_SEND_QUEUE)
<a name="L1585" href="source/net/ipv4/tcp.c#L1585">1585</a>                         goto recv_sndq;
<a name="L1586" href="source/net/ipv4/tcp.c#L1586">1586</a> 
<a name="L1587" href="source/net/ipv4/tcp.c#L1587">1587</a>                 <a href="ident?i=err">err</a> = -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L1588" href="source/net/ipv4/tcp.c#L1588">1588</a>                 if (<a href="ident?i=tp">tp</a>-&gt;repair_queue == TCP_NO_QUEUE)
<a name="L1589" href="source/net/ipv4/tcp.c#L1589">1589</a>                         goto <a href="ident?i=out">out</a>;
<a name="L1590" href="source/net/ipv4/tcp.c#L1590">1590</a> 
<a name="L1591" href="source/net/ipv4/tcp.c#L1591">1591</a>                 <b><i>/* 'common' recv queue MSG_PEEK-ing */</i></b>
<a name="L1592" href="source/net/ipv4/tcp.c#L1592">1592</a>         }
<a name="L1593" href="source/net/ipv4/tcp.c#L1593">1593</a> 
<a name="L1594" href="source/net/ipv4/tcp.c#L1594">1594</a>         <a href="ident?i=seq">seq</a> = &amp;<a href="ident?i=tp">tp</a>-&gt;copied_seq;
<a name="L1595" href="source/net/ipv4/tcp.c#L1595">1595</a>         if (<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=MSG_PEEK">MSG_PEEK</a>) {
<a name="L1596" href="source/net/ipv4/tcp.c#L1596">1596</a>                 peek_seq = <a href="ident?i=tp">tp</a>-&gt;copied_seq;
<a name="L1597" href="source/net/ipv4/tcp.c#L1597">1597</a>                 <a href="ident?i=seq">seq</a> = &amp;peek_seq;
<a name="L1598" href="source/net/ipv4/tcp.c#L1598">1598</a>         }
<a name="L1599" href="source/net/ipv4/tcp.c#L1599">1599</a> 
<a name="L1600" href="source/net/ipv4/tcp.c#L1600">1600</a>         <a href="ident?i=target">target</a> = <a href="ident?i=sock_rcvlowat">sock_rcvlowat</a>(sk, <a href="ident?i=flags">flags</a> &amp; <a href="ident?i=MSG_WAITALL">MSG_WAITALL</a>, <a href="ident?i=len">len</a>);
<a name="L1601" href="source/net/ipv4/tcp.c#L1601">1601</a> 
<a name="L1602" href="source/net/ipv4/tcp.c#L1602">1602</a>         do {
<a name="L1603" href="source/net/ipv4/tcp.c#L1603">1603</a>                 <a href="ident?i=u32">u32</a> <a href="ident?i=offset">offset</a>;
<a name="L1604" href="source/net/ipv4/tcp.c#L1604">1604</a> 
<a name="L1605" href="source/net/ipv4/tcp.c#L1605">1605</a>                 <b><i>/* Are we at urgent data? Stop if we have read anything or have SIGURG pending. */</i></b>
<a name="L1606" href="source/net/ipv4/tcp.c#L1606">1606</a>                 if (<a href="ident?i=tp">tp</a>-&gt;urg_data &amp;&amp; <a href="ident?i=tp">tp</a>-&gt;urg_seq == *<a href="ident?i=seq">seq</a>) {
<a name="L1607" href="source/net/ipv4/tcp.c#L1607">1607</a>                         if (copied)
<a name="L1608" href="source/net/ipv4/tcp.c#L1608">1608</a>                                 break;
<a name="L1609" href="source/net/ipv4/tcp.c#L1609">1609</a>                         if (<a href="ident?i=signal_pending">signal_pending</a>(<a href="ident?i=current">current</a>)) {
<a name="L1610" href="source/net/ipv4/tcp.c#L1610">1610</a>                                 copied = timeo ? <a href="ident?i=sock_intr_errno">sock_intr_errno</a>(timeo) : -<a href="ident?i=EAGAIN">EAGAIN</a>;
<a name="L1611" href="source/net/ipv4/tcp.c#L1611">1611</a>                                 break;
<a name="L1612" href="source/net/ipv4/tcp.c#L1612">1612</a>                         }
<a name="L1613" href="source/net/ipv4/tcp.c#L1613">1613</a>                 }
<a name="L1614" href="source/net/ipv4/tcp.c#L1614">1614</a> 
<a name="L1615" href="source/net/ipv4/tcp.c#L1615">1615</a>                 <b><i>/* Next get a buffer. */</i></b>
<a name="L1616" href="source/net/ipv4/tcp.c#L1616">1616</a> 
<a name="L1617" href="source/net/ipv4/tcp.c#L1617">1617</a>                 <a href="ident?i=skb_queue_walk">skb_queue_walk</a>(&amp;sk-&gt;sk_receive_queue, <a href="ident?i=skb">skb</a>) {
<a name="L1618" href="source/net/ipv4/tcp.c#L1618">1618</a>                         <b><i>/* Now that we have two receive queues this</i></b>
<a name="L1619" href="source/net/ipv4/tcp.c#L1619">1619</a> <b><i>                         * shouldn't happen.</i></b>
<a name="L1620" href="source/net/ipv4/tcp.c#L1620">1620</a> <b><i>                         */</i></b>
<a name="L1621" href="source/net/ipv4/tcp.c#L1621">1621</a>                         if (<a href="ident?i=WARN">WARN</a>(<a href="ident?i=before">before</a>(*<a href="ident?i=seq">seq</a>, <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=seq">seq</a>),
<a name="L1622" href="source/net/ipv4/tcp.c#L1622">1622</a>                                  <i>"recvmsg bug: copied %X seq %X rcvnxt %X fl %X\n"</i>,
<a name="L1623" href="source/net/ipv4/tcp.c#L1623">1623</a>                                  *<a href="ident?i=seq">seq</a>, <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=seq">seq</a>, <a href="ident?i=tp">tp</a>-&gt;rcv_nxt,
<a name="L1624" href="source/net/ipv4/tcp.c#L1624">1624</a>                                  <a href="ident?i=flags">flags</a>))
<a name="L1625" href="source/net/ipv4/tcp.c#L1625">1625</a>                                 break;
<a name="L1626" href="source/net/ipv4/tcp.c#L1626">1626</a> 
<a name="L1627" href="source/net/ipv4/tcp.c#L1627">1627</a>                         <a href="ident?i=offset">offset</a> = *<a href="ident?i=seq">seq</a> - <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=seq">seq</a>;
<a name="L1628" href="source/net/ipv4/tcp.c#L1628">1628</a>                         if (<a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;tcp_flags &amp; <a href="ident?i=TCPHDR_SYN">TCPHDR_SYN</a>)
<a name="L1629" href="source/net/ipv4/tcp.c#L1629">1629</a>                                 <a href="ident?i=offset">offset</a>--;
<a name="L1630" href="source/net/ipv4/tcp.c#L1630">1630</a>                         if (<a href="ident?i=offset">offset</a> &lt; <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a>)
<a name="L1631" href="source/net/ipv4/tcp.c#L1631">1631</a>                                 goto found_ok_skb;
<a name="L1632" href="source/net/ipv4/tcp.c#L1632">1632</a>                         if (<a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;tcp_flags &amp; <a href="ident?i=TCPHDR_FIN">TCPHDR_FIN</a>)
<a name="L1633" href="source/net/ipv4/tcp.c#L1633">1633</a>                                 goto found_fin_ok;
<a name="L1634" href="source/net/ipv4/tcp.c#L1634">1634</a>                         <a href="ident?i=WARN">WARN</a>(!(<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=MSG_PEEK">MSG_PEEK</a>),
<a name="L1635" href="source/net/ipv4/tcp.c#L1635">1635</a>                              <i>"recvmsg bug 2: copied %X seq %X rcvnxt %X fl %X\n"</i>,
<a name="L1636" href="source/net/ipv4/tcp.c#L1636">1636</a>                              *<a href="ident?i=seq">seq</a>, <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=seq">seq</a>, <a href="ident?i=tp">tp</a>-&gt;rcv_nxt, <a href="ident?i=flags">flags</a>);
<a name="L1637" href="source/net/ipv4/tcp.c#L1637">1637</a>                 }
<a name="L1638" href="source/net/ipv4/tcp.c#L1638">1638</a> 
<a name="L1639" href="source/net/ipv4/tcp.c#L1639">1639</a>                 <b><i>/* Well, if we have backlog, try to process it now yet. */</i></b>
<a name="L1640" href="source/net/ipv4/tcp.c#L1640">1640</a> 
<a name="L1641" href="source/net/ipv4/tcp.c#L1641">1641</a>                 if (copied &gt;= <a href="ident?i=target">target</a> &amp;&amp; !sk-&gt;sk_backlog.<a href="ident?i=tail">tail</a>)
<a name="L1642" href="source/net/ipv4/tcp.c#L1642">1642</a>                         break;
<a name="L1643" href="source/net/ipv4/tcp.c#L1643">1643</a> 
<a name="L1644" href="source/net/ipv4/tcp.c#L1644">1644</a>                 if (copied) {
<a name="L1645" href="source/net/ipv4/tcp.c#L1645">1645</a>                         if (sk-&gt;sk_err ||
<a name="L1646" href="source/net/ipv4/tcp.c#L1646">1646</a>                             sk-&gt;<a href="ident?i=sk_state">sk_state</a> == TCP_CLOSE ||
<a name="L1647" href="source/net/ipv4/tcp.c#L1647">1647</a>                             (sk-&gt;sk_shutdown &amp; <a href="ident?i=RCV_SHUTDOWN">RCV_SHUTDOWN</a>) ||
<a name="L1648" href="source/net/ipv4/tcp.c#L1648">1648</a>                             !timeo ||
<a name="L1649" href="source/net/ipv4/tcp.c#L1649">1649</a>                             <a href="ident?i=signal_pending">signal_pending</a>(<a href="ident?i=current">current</a>))
<a name="L1650" href="source/net/ipv4/tcp.c#L1650">1650</a>                                 break;
<a name="L1651" href="source/net/ipv4/tcp.c#L1651">1651</a>                 } else {
<a name="L1652" href="source/net/ipv4/tcp.c#L1652">1652</a>                         if (<a href="ident?i=sock_flag">sock_flag</a>(sk, SOCK_DONE))
<a name="L1653" href="source/net/ipv4/tcp.c#L1653">1653</a>                                 break;
<a name="L1654" href="source/net/ipv4/tcp.c#L1654">1654</a> 
<a name="L1655" href="source/net/ipv4/tcp.c#L1655">1655</a>                         if (sk-&gt;sk_err) {
<a name="L1656" href="source/net/ipv4/tcp.c#L1656">1656</a>                                 copied = <a href="ident?i=sock_error">sock_error</a>(sk);
<a name="L1657" href="source/net/ipv4/tcp.c#L1657">1657</a>                                 break;
<a name="L1658" href="source/net/ipv4/tcp.c#L1658">1658</a>                         }
<a name="L1659" href="source/net/ipv4/tcp.c#L1659">1659</a> 
<a name="L1660" href="source/net/ipv4/tcp.c#L1660">1660</a>                         if (sk-&gt;sk_shutdown &amp; <a href="ident?i=RCV_SHUTDOWN">RCV_SHUTDOWN</a>)
<a name="L1661" href="source/net/ipv4/tcp.c#L1661">1661</a>                                 break;
<a name="L1662" href="source/net/ipv4/tcp.c#L1662">1662</a> 
<a name="L1663" href="source/net/ipv4/tcp.c#L1663">1663</a>                         if (sk-&gt;<a href="ident?i=sk_state">sk_state</a> == TCP_CLOSE) {
<a name="L1664" href="source/net/ipv4/tcp.c#L1664">1664</a>                                 if (!<a href="ident?i=sock_flag">sock_flag</a>(sk, SOCK_DONE)) {
<a name="L1665" href="source/net/ipv4/tcp.c#L1665">1665</a>                                         <b><i>/* This occurs when user tries to read</i></b>
<a name="L1666" href="source/net/ipv4/tcp.c#L1666">1666</a> <b><i>                                         * from never connected socket.</i></b>
<a name="L1667" href="source/net/ipv4/tcp.c#L1667">1667</a> <b><i>                                         */</i></b>
<a name="L1668" href="source/net/ipv4/tcp.c#L1668">1668</a>                                         copied = -<a href="ident?i=ENOTCONN">ENOTCONN</a>;
<a name="L1669" href="source/net/ipv4/tcp.c#L1669">1669</a>                                         break;
<a name="L1670" href="source/net/ipv4/tcp.c#L1670">1670</a>                                 }
<a name="L1671" href="source/net/ipv4/tcp.c#L1671">1671</a>                                 break;
<a name="L1672" href="source/net/ipv4/tcp.c#L1672">1672</a>                         }
<a name="L1673" href="source/net/ipv4/tcp.c#L1673">1673</a> 
<a name="L1674" href="source/net/ipv4/tcp.c#L1674">1674</a>                         if (!timeo) {
<a name="L1675" href="source/net/ipv4/tcp.c#L1675">1675</a>                                 copied = -<a href="ident?i=EAGAIN">EAGAIN</a>;
<a name="L1676" href="source/net/ipv4/tcp.c#L1676">1676</a>                                 break;
<a name="L1677" href="source/net/ipv4/tcp.c#L1677">1677</a>                         }
<a name="L1678" href="source/net/ipv4/tcp.c#L1678">1678</a> 
<a name="L1679" href="source/net/ipv4/tcp.c#L1679">1679</a>                         if (<a href="ident?i=signal_pending">signal_pending</a>(<a href="ident?i=current">current</a>)) {
<a name="L1680" href="source/net/ipv4/tcp.c#L1680">1680</a>                                 copied = <a href="ident?i=sock_intr_errno">sock_intr_errno</a>(timeo);
<a name="L1681" href="source/net/ipv4/tcp.c#L1681">1681</a>                                 break;
<a name="L1682" href="source/net/ipv4/tcp.c#L1682">1682</a>                         }
<a name="L1683" href="source/net/ipv4/tcp.c#L1683">1683</a>                 }
<a name="L1684" href="source/net/ipv4/tcp.c#L1684">1684</a> 
<a name="L1685" href="source/net/ipv4/tcp.c#L1685">1685</a>                 <a href="ident?i=tcp_cleanup_rbuf">tcp_cleanup_rbuf</a>(sk, copied);
<a name="L1686" href="source/net/ipv4/tcp.c#L1686">1686</a> 
<a name="L1687" href="source/net/ipv4/tcp.c#L1687">1687</a>                 if (!<a href="ident?i=sysctl_tcp_low_latency">sysctl_tcp_low_latency</a> &amp;&amp; <a href="ident?i=tp">tp</a>-&gt;ucopy.<a href="ident?i=task">task</a> == user_recv) {
<a name="L1688" href="source/net/ipv4/tcp.c#L1688">1688</a>                         <b><i>/* Install new reader */</i></b>
<a name="L1689" href="source/net/ipv4/tcp.c#L1689">1689</a>                         if (!user_recv &amp;&amp; !(<a href="ident?i=flags">flags</a> &amp; (<a href="ident?i=MSG_TRUNC">MSG_TRUNC</a> | <a href="ident?i=MSG_PEEK">MSG_PEEK</a>))) {
<a name="L1690" href="source/net/ipv4/tcp.c#L1690">1690</a>                                 user_recv = <a href="ident?i=current">current</a>;
<a name="L1691" href="source/net/ipv4/tcp.c#L1691">1691</a>                                 <a href="ident?i=tp">tp</a>-&gt;ucopy.<a href="ident?i=task">task</a> = user_recv;
<a name="L1692" href="source/net/ipv4/tcp.c#L1692">1692</a>                                 <a href="ident?i=tp">tp</a>-&gt;ucopy.<a href="ident?i=msg">msg</a> = <a href="ident?i=msg">msg</a>;
<a name="L1693" href="source/net/ipv4/tcp.c#L1693">1693</a>                         }
<a name="L1694" href="source/net/ipv4/tcp.c#L1694">1694</a> 
<a name="L1695" href="source/net/ipv4/tcp.c#L1695">1695</a>                         <a href="ident?i=tp">tp</a>-&gt;ucopy.<a href="ident?i=len">len</a> = <a href="ident?i=len">len</a>;
<a name="L1696" href="source/net/ipv4/tcp.c#L1696">1696</a> 
<a name="L1697" href="source/net/ipv4/tcp.c#L1697">1697</a>                         <a href="ident?i=WARN_ON">WARN_ON</a>(<a href="ident?i=tp">tp</a>-&gt;copied_seq != <a href="ident?i=tp">tp</a>-&gt;rcv_nxt &amp;&amp;
<a name="L1698" href="source/net/ipv4/tcp.c#L1698">1698</a>                                 !(<a href="ident?i=flags">flags</a> &amp; (<a href="ident?i=MSG_PEEK">MSG_PEEK</a> | <a href="ident?i=MSG_TRUNC">MSG_TRUNC</a>)));
<a name="L1699" href="source/net/ipv4/tcp.c#L1699">1699</a> 
<a name="L1700" href="source/net/ipv4/tcp.c#L1700">1700</a>                         <b><i>/* Ugly... If prequeue is not empty, we have to</i></b>
<a name="L1701" href="source/net/ipv4/tcp.c#L1701">1701</a> <b><i>                         * process it before releasing socket, otherwise</i></b>
<a name="L1702" href="source/net/ipv4/tcp.c#L1702">1702</a> <b><i>                         * order will be broken at second iteration.</i></b>
<a name="L1703" href="source/net/ipv4/tcp.c#L1703">1703</a> <b><i>                         * More elegant solution is required!!!</i></b>
<a name="L1704" href="source/net/ipv4/tcp.c#L1704">1704</a> <b><i>                         *</i></b>
<a name="L1705" href="source/net/ipv4/tcp.c#L1705">1705</a> <b><i>                         * Look: we have the following (pseudo)queues:</i></b>
<a name="L1706" href="source/net/ipv4/tcp.c#L1706">1706</a> <b><i>                         *</i></b>
<a name="L1707" href="source/net/ipv4/tcp.c#L1707">1707</a> <b><i>                         * 1. packets in flight</i></b>
<a name="L1708" href="source/net/ipv4/tcp.c#L1708">1708</a> <b><i>                         * 2. backlog</i></b>
<a name="L1709" href="source/net/ipv4/tcp.c#L1709">1709</a> <b><i>                         * 3. prequeue</i></b>
<a name="L1710" href="source/net/ipv4/tcp.c#L1710">1710</a> <b><i>                         * 4. receive_queue</i></b>
<a name="L1711" href="source/net/ipv4/tcp.c#L1711">1711</a> <b><i>                         *</i></b>
<a name="L1712" href="source/net/ipv4/tcp.c#L1712">1712</a> <b><i>                         * Each queue can be processed only if the next ones</i></b>
<a name="L1713" href="source/net/ipv4/tcp.c#L1713">1713</a> <b><i>                         * are empty. At this point we have empty receive_queue.</i></b>
<a name="L1714" href="source/net/ipv4/tcp.c#L1714">1714</a> <b><i>                         * But prequeue _can_ be not empty after 2nd iteration,</i></b>
<a name="L1715" href="source/net/ipv4/tcp.c#L1715">1715</a> <b><i>                         * when we jumped to start of loop because backlog</i></b>
<a name="L1716" href="source/net/ipv4/tcp.c#L1716">1716</a> <b><i>                         * processing added something to receive_queue.</i></b>
<a name="L1717" href="source/net/ipv4/tcp.c#L1717">1717</a> <b><i>                         * We cannot release_sock(), because backlog contains</i></b>
<a name="L1718" href="source/net/ipv4/tcp.c#L1718">1718</a> <b><i>                         * packets arrived _after_ prequeued ones.</i></b>
<a name="L1719" href="source/net/ipv4/tcp.c#L1719">1719</a> <b><i>                         *</i></b>
<a name="L1720" href="source/net/ipv4/tcp.c#L1720">1720</a> <b><i>                         * Shortly, algorithm is clear --- to process all</i></b>
<a name="L1721" href="source/net/ipv4/tcp.c#L1721">1721</a> <b><i>                         * the queues in order. We could make it more directly,</i></b>
<a name="L1722" href="source/net/ipv4/tcp.c#L1722">1722</a> <b><i>                         * requeueing packets from backlog to prequeue, if</i></b>
<a name="L1723" href="source/net/ipv4/tcp.c#L1723">1723</a> <b><i>                         * is not empty. It is more elegant, but eats cycles,</i></b>
<a name="L1724" href="source/net/ipv4/tcp.c#L1724">1724</a> <b><i>                         * unfortunately.</i></b>
<a name="L1725" href="source/net/ipv4/tcp.c#L1725">1725</a> <b><i>                         */</i></b>
<a name="L1726" href="source/net/ipv4/tcp.c#L1726">1726</a>                         if (!<a href="ident?i=skb_queue_empty">skb_queue_empty</a>(&amp;<a href="ident?i=tp">tp</a>-&gt;ucopy.prequeue))
<a name="L1727" href="source/net/ipv4/tcp.c#L1727">1727</a>                                 goto do_prequeue;
<a name="L1728" href="source/net/ipv4/tcp.c#L1728">1728</a> 
<a name="L1729" href="source/net/ipv4/tcp.c#L1729">1729</a>                         <b><i>/* __ Set realtime policy in scheduler __ */</i></b>
<a name="L1730" href="source/net/ipv4/tcp.c#L1730">1730</a>                 }
<a name="L1731" href="source/net/ipv4/tcp.c#L1731">1731</a> 
<a name="L1732" href="source/net/ipv4/tcp.c#L1732">1732</a>                 if (copied &gt;= <a href="ident?i=target">target</a>) {
<a name="L1733" href="source/net/ipv4/tcp.c#L1733">1733</a>                         <b><i>/* Do not sleep, just process backlog. */</i></b>
<a name="L1734" href="source/net/ipv4/tcp.c#L1734">1734</a>                         <a href="ident?i=release_sock">release_sock</a>(sk);
<a name="L1735" href="source/net/ipv4/tcp.c#L1735">1735</a>                         <a href="ident?i=lock_sock">lock_sock</a>(sk);
<a name="L1736" href="source/net/ipv4/tcp.c#L1736">1736</a>                 } else
<a name="L1737" href="source/net/ipv4/tcp.c#L1737">1737</a>                         <a href="ident?i=sk_wait_data">sk_wait_data</a>(sk, &amp;timeo);
<a name="L1738" href="source/net/ipv4/tcp.c#L1738">1738</a> 
<a name="L1739" href="source/net/ipv4/tcp.c#L1739">1739</a>                 if (user_recv) {
<a name="L1740" href="source/net/ipv4/tcp.c#L1740">1740</a>                         int <a href="ident?i=chunk">chunk</a>;
<a name="L1741" href="source/net/ipv4/tcp.c#L1741">1741</a> 
<a name="L1742" href="source/net/ipv4/tcp.c#L1742">1742</a>                         <b><i>/* __ Restore normal policy in scheduler __ */</i></b>
<a name="L1743" href="source/net/ipv4/tcp.c#L1743">1743</a> 
<a name="L1744" href="source/net/ipv4/tcp.c#L1744">1744</a>                         if ((<a href="ident?i=chunk">chunk</a> = <a href="ident?i=len">len</a> - <a href="ident?i=tp">tp</a>-&gt;ucopy.<a href="ident?i=len">len</a>) != 0) {
<a name="L1745" href="source/net/ipv4/tcp.c#L1745">1745</a>                                 <a href="ident?i=NET_ADD_STATS_USER">NET_ADD_STATS_USER</a>(<a href="ident?i=sock_net">sock_net</a>(sk), LINUX_MIB_TCPDIRECTCOPYFROMBACKLOG, <a href="ident?i=chunk">chunk</a>);
<a name="L1746" href="source/net/ipv4/tcp.c#L1746">1746</a>                                 <a href="ident?i=len">len</a> -= <a href="ident?i=chunk">chunk</a>;
<a name="L1747" href="source/net/ipv4/tcp.c#L1747">1747</a>                                 copied += <a href="ident?i=chunk">chunk</a>;
<a name="L1748" href="source/net/ipv4/tcp.c#L1748">1748</a>                         }
<a name="L1749" href="source/net/ipv4/tcp.c#L1749">1749</a> 
<a name="L1750" href="source/net/ipv4/tcp.c#L1750">1750</a>                         if (<a href="ident?i=tp">tp</a>-&gt;rcv_nxt == <a href="ident?i=tp">tp</a>-&gt;copied_seq &amp;&amp;
<a name="L1751" href="source/net/ipv4/tcp.c#L1751">1751</a>                             !<a href="ident?i=skb_queue_empty">skb_queue_empty</a>(&amp;<a href="ident?i=tp">tp</a>-&gt;ucopy.prequeue)) {
<a name="L1752" href="source/net/ipv4/tcp.c#L1752">1752</a> do_prequeue:
<a name="L1753" href="source/net/ipv4/tcp.c#L1753">1753</a>                                 <a href="ident?i=tcp_prequeue_process">tcp_prequeue_process</a>(sk);
<a name="L1754" href="source/net/ipv4/tcp.c#L1754">1754</a> 
<a name="L1755" href="source/net/ipv4/tcp.c#L1755">1755</a>                                 if ((<a href="ident?i=chunk">chunk</a> = <a href="ident?i=len">len</a> - <a href="ident?i=tp">tp</a>-&gt;ucopy.<a href="ident?i=len">len</a>) != 0) {
<a name="L1756" href="source/net/ipv4/tcp.c#L1756">1756</a>                                         <a href="ident?i=NET_ADD_STATS_USER">NET_ADD_STATS_USER</a>(<a href="ident?i=sock_net">sock_net</a>(sk), LINUX_MIB_TCPDIRECTCOPYFROMPREQUEUE, <a href="ident?i=chunk">chunk</a>);
<a name="L1757" href="source/net/ipv4/tcp.c#L1757">1757</a>                                         <a href="ident?i=len">len</a> -= <a href="ident?i=chunk">chunk</a>;
<a name="L1758" href="source/net/ipv4/tcp.c#L1758">1758</a>                                         copied += <a href="ident?i=chunk">chunk</a>;
<a name="L1759" href="source/net/ipv4/tcp.c#L1759">1759</a>                                 }
<a name="L1760" href="source/net/ipv4/tcp.c#L1760">1760</a>                         }
<a name="L1761" href="source/net/ipv4/tcp.c#L1761">1761</a>                 }
<a name="L1762" href="source/net/ipv4/tcp.c#L1762">1762</a>                 if ((<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=MSG_PEEK">MSG_PEEK</a>) &amp;&amp;
<a name="L1763" href="source/net/ipv4/tcp.c#L1763">1763</a>                     (peek_seq - copied - urg_hole != <a href="ident?i=tp">tp</a>-&gt;copied_seq)) {
<a name="L1764" href="source/net/ipv4/tcp.c#L1764">1764</a>                         <a href="ident?i=net_dbg_ratelimited">net_dbg_ratelimited</a>(<i>"TCP(%s:%d): Application bug, race in MSG_PEEK\n"</i>,
<a name="L1765" href="source/net/ipv4/tcp.c#L1765">1765</a>                                             <a href="ident?i=current">current</a>-&gt;<a href="ident?i=comm">comm</a>,
<a name="L1766" href="source/net/ipv4/tcp.c#L1766">1766</a>                                             <a href="ident?i=task_pid_nr">task_pid_nr</a>(<a href="ident?i=current">current</a>));
<a name="L1767" href="source/net/ipv4/tcp.c#L1767">1767</a>                         peek_seq = <a href="ident?i=tp">tp</a>-&gt;copied_seq;
<a name="L1768" href="source/net/ipv4/tcp.c#L1768">1768</a>                 }
<a name="L1769" href="source/net/ipv4/tcp.c#L1769">1769</a>                 continue;
<a name="L1770" href="source/net/ipv4/tcp.c#L1770">1770</a> 
<a name="L1771" href="source/net/ipv4/tcp.c#L1771">1771</a>         found_ok_skb:
<a name="L1772" href="source/net/ipv4/tcp.c#L1772">1772</a>                 <b><i>/* Ok so how much can we use? */</i></b>
<a name="L1773" href="source/net/ipv4/tcp.c#L1773">1773</a>                 <a href="ident?i=used">used</a> = <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a> - <a href="ident?i=offset">offset</a>;
<a name="L1774" href="source/net/ipv4/tcp.c#L1774">1774</a>                 if (<a href="ident?i=len">len</a> &lt; <a href="ident?i=used">used</a>)
<a name="L1775" href="source/net/ipv4/tcp.c#L1775">1775</a>                         <a href="ident?i=used">used</a> = <a href="ident?i=len">len</a>;
<a name="L1776" href="source/net/ipv4/tcp.c#L1776">1776</a> 
<a name="L1777" href="source/net/ipv4/tcp.c#L1777">1777</a>                 <b><i>/* Do we have urgent data here? */</i></b>
<a name="L1778" href="source/net/ipv4/tcp.c#L1778">1778</a>                 if (<a href="ident?i=tp">tp</a>-&gt;urg_data) {
<a name="L1779" href="source/net/ipv4/tcp.c#L1779">1779</a>                         <a href="ident?i=u32">u32</a> urg_offset = <a href="ident?i=tp">tp</a>-&gt;urg_seq - *<a href="ident?i=seq">seq</a>;
<a name="L1780" href="source/net/ipv4/tcp.c#L1780">1780</a>                         if (urg_offset &lt; <a href="ident?i=used">used</a>) {
<a name="L1781" href="source/net/ipv4/tcp.c#L1781">1781</a>                                 if (!urg_offset) {
<a name="L1782" href="source/net/ipv4/tcp.c#L1782">1782</a>                                         if (!<a href="ident?i=sock_flag">sock_flag</a>(sk, SOCK_URGINLINE)) {
<a name="L1783" href="source/net/ipv4/tcp.c#L1783">1783</a>                                                 ++*<a href="ident?i=seq">seq</a>;
<a name="L1784" href="source/net/ipv4/tcp.c#L1784">1784</a>                                                 urg_hole++;
<a name="L1785" href="source/net/ipv4/tcp.c#L1785">1785</a>                                                 <a href="ident?i=offset">offset</a>++;
<a name="L1786" href="source/net/ipv4/tcp.c#L1786">1786</a>                                                 <a href="ident?i=used">used</a>--;
<a name="L1787" href="source/net/ipv4/tcp.c#L1787">1787</a>                                                 if (!<a href="ident?i=used">used</a>)
<a name="L1788" href="source/net/ipv4/tcp.c#L1788">1788</a>                                                         goto skip_copy;
<a name="L1789" href="source/net/ipv4/tcp.c#L1789">1789</a>                                         }
<a name="L1790" href="source/net/ipv4/tcp.c#L1790">1790</a>                                 } else
<a name="L1791" href="source/net/ipv4/tcp.c#L1791">1791</a>                                         <a href="ident?i=used">used</a> = urg_offset;
<a name="L1792" href="source/net/ipv4/tcp.c#L1792">1792</a>                         }
<a name="L1793" href="source/net/ipv4/tcp.c#L1793">1793</a>                 }
<a name="L1794" href="source/net/ipv4/tcp.c#L1794">1794</a> 
<a name="L1795" href="source/net/ipv4/tcp.c#L1795">1795</a>                 if (!(<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=MSG_TRUNC">MSG_TRUNC</a>)) {
<a name="L1796" href="source/net/ipv4/tcp.c#L1796">1796</a>                         <a href="ident?i=err">err</a> = <a href="ident?i=skb_copy_datagram_msg">skb_copy_datagram_msg</a>(<a href="ident?i=skb">skb</a>, <a href="ident?i=offset">offset</a>, <a href="ident?i=msg">msg</a>, <a href="ident?i=used">used</a>);
<a name="L1797" href="source/net/ipv4/tcp.c#L1797">1797</a>                         if (<a href="ident?i=err">err</a>) {
<a name="L1798" href="source/net/ipv4/tcp.c#L1798">1798</a>                                 <b><i>/* Exception. Bailout! */</i></b>
<a name="L1799" href="source/net/ipv4/tcp.c#L1799">1799</a>                                 if (!copied)
<a name="L1800" href="source/net/ipv4/tcp.c#L1800">1800</a>                                         copied = -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L1801" href="source/net/ipv4/tcp.c#L1801">1801</a>                                 break;
<a name="L1802" href="source/net/ipv4/tcp.c#L1802">1802</a>                         }
<a name="L1803" href="source/net/ipv4/tcp.c#L1803">1803</a>                 }
<a name="L1804" href="source/net/ipv4/tcp.c#L1804">1804</a> 
<a name="L1805" href="source/net/ipv4/tcp.c#L1805">1805</a>                 *<a href="ident?i=seq">seq</a> += <a href="ident?i=used">used</a>;
<a name="L1806" href="source/net/ipv4/tcp.c#L1806">1806</a>                 copied += <a href="ident?i=used">used</a>;
<a name="L1807" href="source/net/ipv4/tcp.c#L1807">1807</a>                 <a href="ident?i=len">len</a> -= <a href="ident?i=used">used</a>;
<a name="L1808" href="source/net/ipv4/tcp.c#L1808">1808</a> 
<a name="L1809" href="source/net/ipv4/tcp.c#L1809">1809</a>                 <a href="ident?i=tcp_rcv_space_adjust">tcp_rcv_space_adjust</a>(sk);
<a name="L1810" href="source/net/ipv4/tcp.c#L1810">1810</a> 
<a name="L1811" href="source/net/ipv4/tcp.c#L1811">1811</a> skip_copy:
<a name="L1812" href="source/net/ipv4/tcp.c#L1812">1812</a>                 if (<a href="ident?i=tp">tp</a>-&gt;urg_data &amp;&amp; <a href="ident?i=after">after</a>(<a href="ident?i=tp">tp</a>-&gt;copied_seq, <a href="ident?i=tp">tp</a>-&gt;urg_seq)) {
<a name="L1813" href="source/net/ipv4/tcp.c#L1813">1813</a>                         <a href="ident?i=tp">tp</a>-&gt;urg_data = 0;
<a name="L1814" href="source/net/ipv4/tcp.c#L1814">1814</a>                         <a href="ident?i=tcp_fast_path_check">tcp_fast_path_check</a>(sk);
<a name="L1815" href="source/net/ipv4/tcp.c#L1815">1815</a>                 }
<a name="L1816" href="source/net/ipv4/tcp.c#L1816">1816</a>                 if (<a href="ident?i=used">used</a> + <a href="ident?i=offset">offset</a> &lt; <a href="ident?i=skb">skb</a>-&gt;<a href="ident?i=len">len</a>)
<a name="L1817" href="source/net/ipv4/tcp.c#L1817">1817</a>                         continue;
<a name="L1818" href="source/net/ipv4/tcp.c#L1818">1818</a> 
<a name="L1819" href="source/net/ipv4/tcp.c#L1819">1819</a>                 if (<a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;tcp_flags &amp; <a href="ident?i=TCPHDR_FIN">TCPHDR_FIN</a>)
<a name="L1820" href="source/net/ipv4/tcp.c#L1820">1820</a>                         goto found_fin_ok;
<a name="L1821" href="source/net/ipv4/tcp.c#L1821">1821</a>                 if (!(<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=MSG_PEEK">MSG_PEEK</a>))
<a name="L1822" href="source/net/ipv4/tcp.c#L1822">1822</a>                         <a href="ident?i=sk_eat_skb">sk_eat_skb</a>(sk, <a href="ident?i=skb">skb</a>);
<a name="L1823" href="source/net/ipv4/tcp.c#L1823">1823</a>                 continue;
<a name="L1824" href="source/net/ipv4/tcp.c#L1824">1824</a> 
<a name="L1825" href="source/net/ipv4/tcp.c#L1825">1825</a>         found_fin_ok:
<a name="L1826" href="source/net/ipv4/tcp.c#L1826">1826</a>                 <b><i>/* Process the FIN. */</i></b>
<a name="L1827" href="source/net/ipv4/tcp.c#L1827">1827</a>                 ++*<a href="ident?i=seq">seq</a>;
<a name="L1828" href="source/net/ipv4/tcp.c#L1828">1828</a>                 if (!(<a href="ident?i=flags">flags</a> &amp; <a href="ident?i=MSG_PEEK">MSG_PEEK</a>))
<a name="L1829" href="source/net/ipv4/tcp.c#L1829">1829</a>                         <a href="ident?i=sk_eat_skb">sk_eat_skb</a>(sk, <a href="ident?i=skb">skb</a>);
<a name="L1830" href="source/net/ipv4/tcp.c#L1830">1830</a>                 break;
<a name="L1831" href="source/net/ipv4/tcp.c#L1831">1831</a>         } while (<a href="ident?i=len">len</a> &gt; 0);
<a name="L1832" href="source/net/ipv4/tcp.c#L1832">1832</a> 
<a name="L1833" href="source/net/ipv4/tcp.c#L1833">1833</a>         if (user_recv) {
<a name="L1834" href="source/net/ipv4/tcp.c#L1834">1834</a>                 if (!<a href="ident?i=skb_queue_empty">skb_queue_empty</a>(&amp;<a href="ident?i=tp">tp</a>-&gt;ucopy.prequeue)) {
<a name="L1835" href="source/net/ipv4/tcp.c#L1835">1835</a>                         int <a href="ident?i=chunk">chunk</a>;
<a name="L1836" href="source/net/ipv4/tcp.c#L1836">1836</a> 
<a name="L1837" href="source/net/ipv4/tcp.c#L1837">1837</a>                         <a href="ident?i=tp">tp</a>-&gt;ucopy.<a href="ident?i=len">len</a> = copied &gt; 0 ? <a href="ident?i=len">len</a> : 0;
<a name="L1838" href="source/net/ipv4/tcp.c#L1838">1838</a> 
<a name="L1839" href="source/net/ipv4/tcp.c#L1839">1839</a>                         <a href="ident?i=tcp_prequeue_process">tcp_prequeue_process</a>(sk);
<a name="L1840" href="source/net/ipv4/tcp.c#L1840">1840</a> 
<a name="L1841" href="source/net/ipv4/tcp.c#L1841">1841</a>                         if (copied &gt; 0 &amp;&amp; (<a href="ident?i=chunk">chunk</a> = <a href="ident?i=len">len</a> - <a href="ident?i=tp">tp</a>-&gt;ucopy.<a href="ident?i=len">len</a>) != 0) {
<a name="L1842" href="source/net/ipv4/tcp.c#L1842">1842</a>                                 <a href="ident?i=NET_ADD_STATS_USER">NET_ADD_STATS_USER</a>(<a href="ident?i=sock_net">sock_net</a>(sk), LINUX_MIB_TCPDIRECTCOPYFROMPREQUEUE, <a href="ident?i=chunk">chunk</a>);
<a name="L1843" href="source/net/ipv4/tcp.c#L1843">1843</a>                                 <a href="ident?i=len">len</a> -= <a href="ident?i=chunk">chunk</a>;
<a name="L1844" href="source/net/ipv4/tcp.c#L1844">1844</a>                                 copied += <a href="ident?i=chunk">chunk</a>;
<a name="L1845" href="source/net/ipv4/tcp.c#L1845">1845</a>                         }
<a name="L1846" href="source/net/ipv4/tcp.c#L1846">1846</a>                 }
<a name="L1847" href="source/net/ipv4/tcp.c#L1847">1847</a> 
<a name="L1848" href="source/net/ipv4/tcp.c#L1848">1848</a>                 <a href="ident?i=tp">tp</a>-&gt;ucopy.<a href="ident?i=task">task</a> = <a href="ident?i=NULL">NULL</a>;
<a name="L1849" href="source/net/ipv4/tcp.c#L1849">1849</a>                 <a href="ident?i=tp">tp</a>-&gt;ucopy.<a href="ident?i=len">len</a> = 0;
<a name="L1850" href="source/net/ipv4/tcp.c#L1850">1850</a>         }
<a name="L1851" href="source/net/ipv4/tcp.c#L1851">1851</a> 
<a name="L1852" href="source/net/ipv4/tcp.c#L1852">1852</a>         <b><i>/* According to UNIX98, msg_name/msg_namelen are ignored</i></b>
<a name="L1853" href="source/net/ipv4/tcp.c#L1853">1853</a> <b><i>         * on connected socket. I was just happy when found this 8) --ANK</i></b>
<a name="L1854" href="source/net/ipv4/tcp.c#L1854">1854</a> <b><i>         */</i></b>
<a name="L1855" href="source/net/ipv4/tcp.c#L1855">1855</a> 
<a name="L1856" href="source/net/ipv4/tcp.c#L1856">1856</a>         <b><i>/* Clean up data we have read: This will do ACK frames. */</i></b>
<a name="L1857" href="source/net/ipv4/tcp.c#L1857">1857</a>         <a href="ident?i=tcp_cleanup_rbuf">tcp_cleanup_rbuf</a>(sk, copied);
<a name="L1858" href="source/net/ipv4/tcp.c#L1858">1858</a> 
<a name="L1859" href="source/net/ipv4/tcp.c#L1859">1859</a>         <a href="ident?i=release_sock">release_sock</a>(sk);
<a name="L1860" href="source/net/ipv4/tcp.c#L1860">1860</a>         return copied;
<a name="L1861" href="source/net/ipv4/tcp.c#L1861">1861</a> 
<a name="L1862" href="source/net/ipv4/tcp.c#L1862">1862</a> <a href="ident?i=out">out</a>:
<a name="L1863" href="source/net/ipv4/tcp.c#L1863">1863</a>         <a href="ident?i=release_sock">release_sock</a>(sk);
<a name="L1864" href="source/net/ipv4/tcp.c#L1864">1864</a>         return <a href="ident?i=err">err</a>;
<a name="L1865" href="source/net/ipv4/tcp.c#L1865">1865</a> 
<a name="L1866" href="source/net/ipv4/tcp.c#L1866">1866</a> recv_urg:
<a name="L1867" href="source/net/ipv4/tcp.c#L1867">1867</a>         <a href="ident?i=err">err</a> = <a href="ident?i=tcp_recv_urg">tcp_recv_urg</a>(sk, <a href="ident?i=msg">msg</a>, <a href="ident?i=len">len</a>, <a href="ident?i=flags">flags</a>);
<a name="L1868" href="source/net/ipv4/tcp.c#L1868">1868</a>         goto <a href="ident?i=out">out</a>;
<a name="L1869" href="source/net/ipv4/tcp.c#L1869">1869</a> 
<a name="L1870" href="source/net/ipv4/tcp.c#L1870">1870</a> recv_sndq:
<a name="L1871" href="source/net/ipv4/tcp.c#L1871">1871</a>         <a href="ident?i=err">err</a> = <a href="ident?i=tcp_peek_sndq">tcp_peek_sndq</a>(sk, <a href="ident?i=msg">msg</a>, <a href="ident?i=len">len</a>);
<a name="L1872" href="source/net/ipv4/tcp.c#L1872">1872</a>         goto <a href="ident?i=out">out</a>;
<a name="L1873" href="source/net/ipv4/tcp.c#L1873">1873</a> }
<a name="L1874" href="source/net/ipv4/tcp.c#L1874">1874</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=tcp_recvmsg">tcp_recvmsg</a>);
<a name="L1875" href="source/net/ipv4/tcp.c#L1875">1875</a> 
<a name="L1876" href="source/net/ipv4/tcp.c#L1876">1876</a> void <a href="ident?i=tcp_set_state">tcp_set_state</a>(struct <a href="ident?i=sock">sock</a> *sk, int <a href="ident?i=state">state</a>)
<a name="L1877" href="source/net/ipv4/tcp.c#L1877">1877</a> {
<a name="L1878" href="source/net/ipv4/tcp.c#L1878">1878</a>         int oldstate = sk-&gt;<a href="ident?i=sk_state">sk_state</a>;
<a name="L1879" href="source/net/ipv4/tcp.c#L1879">1879</a> 
<a name="L1880" href="source/net/ipv4/tcp.c#L1880">1880</a>         switch (<a href="ident?i=state">state</a>) {
<a name="L1881" href="source/net/ipv4/tcp.c#L1881">1881</a>         case TCP_ESTABLISHED:
<a name="L1882" href="source/net/ipv4/tcp.c#L1882">1882</a>                 if (oldstate != TCP_ESTABLISHED)
<a name="L1883" href="source/net/ipv4/tcp.c#L1883">1883</a>                         <a href="ident?i=TCP_INC_STATS">TCP_INC_STATS</a>(<a href="ident?i=sock_net">sock_net</a>(sk), TCP_MIB_CURRESTAB);
<a name="L1884" href="source/net/ipv4/tcp.c#L1884">1884</a>                 break;
<a name="L1885" href="source/net/ipv4/tcp.c#L1885">1885</a> 
<a name="L1886" href="source/net/ipv4/tcp.c#L1886">1886</a>         case TCP_CLOSE:
<a name="L1887" href="source/net/ipv4/tcp.c#L1887">1887</a>                 if (oldstate == TCP_CLOSE_WAIT || oldstate == TCP_ESTABLISHED)
<a name="L1888" href="source/net/ipv4/tcp.c#L1888">1888</a>                         <a href="ident?i=TCP_INC_STATS">TCP_INC_STATS</a>(<a href="ident?i=sock_net">sock_net</a>(sk), TCP_MIB_ESTABRESETS);
<a name="L1889" href="source/net/ipv4/tcp.c#L1889">1889</a> 
<a name="L1890" href="source/net/ipv4/tcp.c#L1890">1890</a>                 sk-&gt;<a href="ident?i=sk_prot">sk_prot</a>-&gt;unhash(sk);
<a name="L1891" href="source/net/ipv4/tcp.c#L1891">1891</a>                 if (<a href="ident?i=inet_csk">inet_csk</a>(sk)-&gt;icsk_bind_hash &amp;&amp;
<a name="L1892" href="source/net/ipv4/tcp.c#L1892">1892</a>                     !(sk-&gt;sk_userlocks &amp; <a href="ident?i=SOCK_BINDPORT_LOCK">SOCK_BINDPORT_LOCK</a>))
<a name="L1893" href="source/net/ipv4/tcp.c#L1893">1893</a>                         <a href="ident?i=inet_put_port">inet_put_port</a>(sk);
<a name="L1894" href="source/net/ipv4/tcp.c#L1894">1894</a>                 <b><i>/* fall through */</i></b>
<a name="L1895" href="source/net/ipv4/tcp.c#L1895">1895</a>         default:
<a name="L1896" href="source/net/ipv4/tcp.c#L1896">1896</a>                 if (oldstate == TCP_ESTABLISHED)
<a name="L1897" href="source/net/ipv4/tcp.c#L1897">1897</a>                         <a href="ident?i=TCP_DEC_STATS">TCP_DEC_STATS</a>(<a href="ident?i=sock_net">sock_net</a>(sk), TCP_MIB_CURRESTAB);
<a name="L1898" href="source/net/ipv4/tcp.c#L1898">1898</a>         }
<a name="L1899" href="source/net/ipv4/tcp.c#L1899">1899</a> 
<a name="L1900" href="source/net/ipv4/tcp.c#L1900">1900</a>         <b><i>/* Change state AFTER socket is unhashed to avoid closed</i></b>
<a name="L1901" href="source/net/ipv4/tcp.c#L1901">1901</a> <b><i>         * socket sitting in hash tables.</i></b>
<a name="L1902" href="source/net/ipv4/tcp.c#L1902">1902</a> <b><i>         */</i></b>
<a name="L1903" href="source/net/ipv4/tcp.c#L1903">1903</a>         sk-&gt;<a href="ident?i=sk_state">sk_state</a> = <a href="ident?i=state">state</a>;
<a name="L1904" href="source/net/ipv4/tcp.c#L1904">1904</a> 
<a name="L1905" href="source/net/ipv4/tcp.c#L1905">1905</a> #ifdef <a href="ident?i=STATE_TRACE">STATE_TRACE</a>
<a name="L1906" href="source/net/ipv4/tcp.c#L1906">1906</a>         <a href="ident?i=SOCK_DEBUG">SOCK_DEBUG</a>(sk, <i>"TCP sk=%p, State %s -&gt; %s\n"</i>, sk, <a href="ident?i=statename">statename</a>[oldstate], <a href="ident?i=statename">statename</a>[<a href="ident?i=state">state</a>]);
<a name="L1907" href="source/net/ipv4/tcp.c#L1907">1907</a> #endif
<a name="L1908" href="source/net/ipv4/tcp.c#L1908">1908</a> }
<a name="L1909" href="source/net/ipv4/tcp.c#L1909">1909</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=tcp_set_state">tcp_set_state</a>);
<a name="L1910" href="source/net/ipv4/tcp.c#L1910">1910</a> 
<a name="L1911" href="source/net/ipv4/tcp.c#L1911">1911</a> <b><i>/*</i></b>
<a name="L1912" href="source/net/ipv4/tcp.c#L1912">1912</a> <b><i> *      State processing on a close. This implements the state shift for</i></b>
<a name="L1913" href="source/net/ipv4/tcp.c#L1913">1913</a> <b><i> *      sending our FIN frame. Note that we only send a FIN for some</i></b>
<a name="L1914" href="source/net/ipv4/tcp.c#L1914">1914</a> <b><i> *      states. A shutdown() may have already sent the FIN, or we may be</i></b>
<a name="L1915" href="source/net/ipv4/tcp.c#L1915">1915</a> <b><i> *      closed.</i></b>
<a name="L1916" href="source/net/ipv4/tcp.c#L1916">1916</a> <b><i> */</i></b>
<a name="L1917" href="source/net/ipv4/tcp.c#L1917">1917</a> 
<a name="L1918" href="source/net/ipv4/tcp.c#L1918">1918</a> static const unsigned char <a href="ident?i=new_state">new_state</a>[16] = {
<a name="L1919" href="source/net/ipv4/tcp.c#L1919">1919</a>   <b><i>/* current state:        new state:      action:      */</i></b>
<a name="L1920" href="source/net/ipv4/tcp.c#L1920">1920</a>   [0 <b><i>/* (Invalid) */</i></b>]   = TCP_CLOSE,
<a name="L1921" href="source/net/ipv4/tcp.c#L1921">1921</a>   [TCP_ESTABLISHED]     = TCP_FIN_WAIT1 | <a href="ident?i=TCP_ACTION_FIN">TCP_ACTION_FIN</a>,
<a name="L1922" href="source/net/ipv4/tcp.c#L1922">1922</a>   [TCP_SYN_SENT]        = TCP_CLOSE,
<a name="L1923" href="source/net/ipv4/tcp.c#L1923">1923</a>   [TCP_SYN_RECV]        = TCP_FIN_WAIT1 | <a href="ident?i=TCP_ACTION_FIN">TCP_ACTION_FIN</a>,
<a name="L1924" href="source/net/ipv4/tcp.c#L1924">1924</a>   [TCP_FIN_WAIT1]       = TCP_FIN_WAIT1,
<a name="L1925" href="source/net/ipv4/tcp.c#L1925">1925</a>   [TCP_FIN_WAIT2]       = TCP_FIN_WAIT2,
<a name="L1926" href="source/net/ipv4/tcp.c#L1926">1926</a>   [TCP_TIME_WAIT]       = TCP_CLOSE,
<a name="L1927" href="source/net/ipv4/tcp.c#L1927">1927</a>   [TCP_CLOSE]           = TCP_CLOSE,
<a name="L1928" href="source/net/ipv4/tcp.c#L1928">1928</a>   [TCP_CLOSE_WAIT]      = TCP_LAST_ACK  | <a href="ident?i=TCP_ACTION_FIN">TCP_ACTION_FIN</a>,
<a name="L1929" href="source/net/ipv4/tcp.c#L1929">1929</a>   [TCP_LAST_ACK]        = TCP_LAST_ACK,
<a name="L1930" href="source/net/ipv4/tcp.c#L1930">1930</a>   [TCP_LISTEN]          = TCP_CLOSE,
<a name="L1931" href="source/net/ipv4/tcp.c#L1931">1931</a>   [TCP_CLOSING]         = TCP_CLOSING,
<a name="L1932" href="source/net/ipv4/tcp.c#L1932">1932</a>   [TCP_NEW_SYN_RECV]    = TCP_CLOSE,    <b><i>/* should not happen ! */</i></b>
<a name="L1933" href="source/net/ipv4/tcp.c#L1933">1933</a> };
<a name="L1934" href="source/net/ipv4/tcp.c#L1934">1934</a> 
<a name="L1935" href="source/net/ipv4/tcp.c#L1935">1935</a> static int <a href="ident?i=tcp_close_state">tcp_close_state</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L1936" href="source/net/ipv4/tcp.c#L1936">1936</a> {
<a name="L1937" href="source/net/ipv4/tcp.c#L1937">1937</a>         int <a href="ident?i=next">next</a> = (int)<a href="ident?i=new_state">new_state</a>[sk-&gt;<a href="ident?i=sk_state">sk_state</a>];
<a name="L1938" href="source/net/ipv4/tcp.c#L1938">1938</a>         int <a href="ident?i=ns">ns</a> = <a href="ident?i=next">next</a> &amp; <a href="ident?i=TCP_STATE_MASK">TCP_STATE_MASK</a>;
<a name="L1939" href="source/net/ipv4/tcp.c#L1939">1939</a> 
<a name="L1940" href="source/net/ipv4/tcp.c#L1940">1940</a>         <a href="ident?i=tcp_set_state">tcp_set_state</a>(sk, <a href="ident?i=ns">ns</a>);
<a name="L1941" href="source/net/ipv4/tcp.c#L1941">1941</a> 
<a name="L1942" href="source/net/ipv4/tcp.c#L1942">1942</a>         return <a href="ident?i=next">next</a> &amp; <a href="ident?i=TCP_ACTION_FIN">TCP_ACTION_FIN</a>;
<a name="L1943" href="source/net/ipv4/tcp.c#L1943">1943</a> }
<a name="L1944" href="source/net/ipv4/tcp.c#L1944">1944</a> 
<a name="L1945" href="source/net/ipv4/tcp.c#L1945">1945</a> <b><i>/*</i></b>
<a name="L1946" href="source/net/ipv4/tcp.c#L1946">1946</a> <b><i> *      Shutdown the sending side of a connection. Much like close except</i></b>
<a name="L1947" href="source/net/ipv4/tcp.c#L1947">1947</a> <b><i> *      that we don't receive shut down or sock_set_flag(sk, SOCK_DEAD).</i></b>
<a name="L1948" href="source/net/ipv4/tcp.c#L1948">1948</a> <b><i> */</i></b>
<a name="L1949" href="source/net/ipv4/tcp.c#L1949">1949</a> 
<a name="L1950" href="source/net/ipv4/tcp.c#L1950">1950</a> void <a href="ident?i=tcp_shutdown">tcp_shutdown</a>(struct <a href="ident?i=sock">sock</a> *sk, int how)
<a name="L1951" href="source/net/ipv4/tcp.c#L1951">1951</a> {
<a name="L1952" href="source/net/ipv4/tcp.c#L1952">1952</a>         <b><i>/*      We need to grab some memory, and put together a FIN,</i></b>
<a name="L1953" href="source/net/ipv4/tcp.c#L1953">1953</a> <b><i>         *      and then put it into the queue to be sent.</i></b>
<a name="L1954" href="source/net/ipv4/tcp.c#L1954">1954</a> <b><i>         *              Tim MacKenzie(tym@dibbler.cs.monash.edu.au) 4 Dec '92.</i></b>
<a name="L1955" href="source/net/ipv4/tcp.c#L1955">1955</a> <b><i>         */</i></b>
<a name="L1956" href="source/net/ipv4/tcp.c#L1956">1956</a>         if (!(how &amp; <a href="ident?i=SEND_SHUTDOWN">SEND_SHUTDOWN</a>))
<a name="L1957" href="source/net/ipv4/tcp.c#L1957">1957</a>                 return;
<a name="L1958" href="source/net/ipv4/tcp.c#L1958">1958</a> 
<a name="L1959" href="source/net/ipv4/tcp.c#L1959">1959</a>         <b><i>/* If we've already sent a FIN, or it's a closed state, skip this. */</i></b>
<a name="L1960" href="source/net/ipv4/tcp.c#L1960">1960</a>         if ((1 &lt;&lt; sk-&gt;<a href="ident?i=sk_state">sk_state</a>) &amp;
<a name="L1961" href="source/net/ipv4/tcp.c#L1961">1961</a>             (TCPF_ESTABLISHED | TCPF_SYN_SENT |
<a name="L1962" href="source/net/ipv4/tcp.c#L1962">1962</a>              TCPF_SYN_RECV | TCPF_CLOSE_WAIT)) {
<a name="L1963" href="source/net/ipv4/tcp.c#L1963">1963</a>                 <b><i>/* Clear out any half completed packets.  FIN if needed. */</i></b>
<a name="L1964" href="source/net/ipv4/tcp.c#L1964">1964</a>                 if (<a href="ident?i=tcp_close_state">tcp_close_state</a>(sk))
<a name="L1965" href="source/net/ipv4/tcp.c#L1965">1965</a>                         <a href="ident?i=tcp_send_fin">tcp_send_fin</a>(sk);
<a name="L1966" href="source/net/ipv4/tcp.c#L1966">1966</a>         }
<a name="L1967" href="source/net/ipv4/tcp.c#L1967">1967</a> }
<a name="L1968" href="source/net/ipv4/tcp.c#L1968">1968</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=tcp_shutdown">tcp_shutdown</a>);
<a name="L1969" href="source/net/ipv4/tcp.c#L1969">1969</a> 
<a name="L1970" href="source/net/ipv4/tcp.c#L1970">1970</a> <a href="ident?i=bool">bool</a> <a href="ident?i=tcp_check_oom">tcp_check_oom</a>(struct <a href="ident?i=sock">sock</a> *sk, int <a href="ident?i=shift">shift</a>)
<a name="L1971" href="source/net/ipv4/tcp.c#L1971">1971</a> {
<a name="L1972" href="source/net/ipv4/tcp.c#L1972">1972</a>         <a href="ident?i=bool">bool</a> too_many_orphans, out_of_socket_memory;
<a name="L1973" href="source/net/ipv4/tcp.c#L1973">1973</a> 
<a name="L1974" href="source/net/ipv4/tcp.c#L1974">1974</a>         too_many_orphans = <a href="ident?i=tcp_too_many_orphans">tcp_too_many_orphans</a>(sk, <a href="ident?i=shift">shift</a>);
<a name="L1975" href="source/net/ipv4/tcp.c#L1975">1975</a>         out_of_socket_memory = <a href="ident?i=tcp_out_of_memory">tcp_out_of_memory</a>(sk);
<a name="L1976" href="source/net/ipv4/tcp.c#L1976">1976</a> 
<a name="L1977" href="source/net/ipv4/tcp.c#L1977">1977</a>         if (too_many_orphans)
<a name="L1978" href="source/net/ipv4/tcp.c#L1978">1978</a>                 <a href="ident?i=net_info_ratelimited">net_info_ratelimited</a>(<i>"too many orphaned sockets\n"</i>);
<a name="L1979" href="source/net/ipv4/tcp.c#L1979">1979</a>         if (out_of_socket_memory)
<a name="L1980" href="source/net/ipv4/tcp.c#L1980">1980</a>                 <a href="ident?i=net_info_ratelimited">net_info_ratelimited</a>(<i>"out of memory -- consider tuning tcp_mem\n"</i>);
<a name="L1981" href="source/net/ipv4/tcp.c#L1981">1981</a>         return too_many_orphans || out_of_socket_memory;
<a name="L1982" href="source/net/ipv4/tcp.c#L1982">1982</a> }
<a name="L1983" href="source/net/ipv4/tcp.c#L1983">1983</a> 
<a name="L1984" href="source/net/ipv4/tcp.c#L1984">1984</a> void <a href="ident?i=tcp_close">tcp_close</a>(struct <a href="ident?i=sock">sock</a> *sk, long <a href="ident?i=timeout">timeout</a>)
<a name="L1985" href="source/net/ipv4/tcp.c#L1985">1985</a> {
<a name="L1986" href="source/net/ipv4/tcp.c#L1986">1986</a>         struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>;
<a name="L1987" href="source/net/ipv4/tcp.c#L1987">1987</a>         int data_was_unread = 0;
<a name="L1988" href="source/net/ipv4/tcp.c#L1988">1988</a>         int <a href="ident?i=state">state</a>;
<a name="L1989" href="source/net/ipv4/tcp.c#L1989">1989</a> 
<a name="L1990" href="source/net/ipv4/tcp.c#L1990">1990</a>         <a href="ident?i=lock_sock">lock_sock</a>(sk);
<a name="L1991" href="source/net/ipv4/tcp.c#L1991">1991</a>         sk-&gt;sk_shutdown = <a href="ident?i=SHUTDOWN_MASK">SHUTDOWN_MASK</a>;
<a name="L1992" href="source/net/ipv4/tcp.c#L1992">1992</a> 
<a name="L1993" href="source/net/ipv4/tcp.c#L1993">1993</a>         if (sk-&gt;<a href="ident?i=sk_state">sk_state</a> == TCP_LISTEN) {
<a name="L1994" href="source/net/ipv4/tcp.c#L1994">1994</a>                 <a href="ident?i=tcp_set_state">tcp_set_state</a>(sk, TCP_CLOSE);
<a name="L1995" href="source/net/ipv4/tcp.c#L1995">1995</a> 
<a name="L1996" href="source/net/ipv4/tcp.c#L1996">1996</a>                 <b><i>/* Special case. */</i></b>
<a name="L1997" href="source/net/ipv4/tcp.c#L1997">1997</a>                 <a href="ident?i=inet_csk_listen_stop">inet_csk_listen_stop</a>(sk);
<a name="L1998" href="source/net/ipv4/tcp.c#L1998">1998</a> 
<a name="L1999" href="source/net/ipv4/tcp.c#L1999">1999</a>                 goto adjudge_to_death;
<a name="L2000" href="source/net/ipv4/tcp.c#L2000">2000</a>         }
<a name="L2001" href="source/net/ipv4/tcp.c#L2001">2001</a> 
<a name="L2002" href="source/net/ipv4/tcp.c#L2002">2002</a>         <b><i>/*  We need to flush the recv. buffs.  We do this only on the</i></b>
<a name="L2003" href="source/net/ipv4/tcp.c#L2003">2003</a> <b><i>         *  descriptor close, not protocol-sourced closes, because the</i></b>
<a name="L2004" href="source/net/ipv4/tcp.c#L2004">2004</a> <b><i>         *  reader process may not have drained the data yet!</i></b>
<a name="L2005" href="source/net/ipv4/tcp.c#L2005">2005</a> <b><i>         */</i></b>
<a name="L2006" href="source/net/ipv4/tcp.c#L2006">2006</a>         while ((<a href="ident?i=skb">skb</a> = <a href="ident?i=__skb_dequeue">__skb_dequeue</a>(&amp;sk-&gt;sk_receive_queue)) != <a href="ident?i=NULL">NULL</a>) {
<a name="L2007" href="source/net/ipv4/tcp.c#L2007">2007</a>                 <a href="ident?i=u32">u32</a> <a href="ident?i=len">len</a> = <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;end_seq - <a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;<a href="ident?i=seq">seq</a>;
<a name="L2008" href="source/net/ipv4/tcp.c#L2008">2008</a> 
<a name="L2009" href="source/net/ipv4/tcp.c#L2009">2009</a>                 if (<a href="ident?i=TCP_SKB_CB">TCP_SKB_CB</a>(<a href="ident?i=skb">skb</a>)-&gt;tcp_flags &amp; <a href="ident?i=TCPHDR_FIN">TCPHDR_FIN</a>)
<a name="L2010" href="source/net/ipv4/tcp.c#L2010">2010</a>                         <a href="ident?i=len">len</a>--;
<a name="L2011" href="source/net/ipv4/tcp.c#L2011">2011</a>                 data_was_unread += <a href="ident?i=len">len</a>;
<a name="L2012" href="source/net/ipv4/tcp.c#L2012">2012</a>                 <a href="ident?i=__kfree_skb">__kfree_skb</a>(<a href="ident?i=skb">skb</a>);
<a name="L2013" href="source/net/ipv4/tcp.c#L2013">2013</a>         }
<a name="L2014" href="source/net/ipv4/tcp.c#L2014">2014</a> 
<a name="L2015" href="source/net/ipv4/tcp.c#L2015">2015</a>         <a href="ident?i=sk_mem_reclaim">sk_mem_reclaim</a>(sk);
<a name="L2016" href="source/net/ipv4/tcp.c#L2016">2016</a> 
<a name="L2017" href="source/net/ipv4/tcp.c#L2017">2017</a>         <b><i>/* If socket has been already reset (e.g. in tcp_reset()) - kill it. */</i></b>
<a name="L2018" href="source/net/ipv4/tcp.c#L2018">2018</a>         if (sk-&gt;<a href="ident?i=sk_state">sk_state</a> == TCP_CLOSE)
<a name="L2019" href="source/net/ipv4/tcp.c#L2019">2019</a>                 goto adjudge_to_death;
<a name="L2020" href="source/net/ipv4/tcp.c#L2020">2020</a> 
<a name="L2021" href="source/net/ipv4/tcp.c#L2021">2021</a>         <b><i>/* As outlined in RFC 2525, section 2.17, we send a RST here because</i></b>
<a name="L2022" href="source/net/ipv4/tcp.c#L2022">2022</a> <b><i>         * data was lost. To witness the awful effects of the old behavior of</i></b>
<a name="L2023" href="source/net/ipv4/tcp.c#L2023">2023</a> <b><i>         * always doing a FIN, run an older 2.1.x kernel or 2.0.x, start a bulk</i></b>
<a name="L2024" href="source/net/ipv4/tcp.c#L2024">2024</a> <b><i>         * GET in an FTP client, suspend the process, wait for the client to</i></b>
<a name="L2025" href="source/net/ipv4/tcp.c#L2025">2025</a> <b><i>         * advertise a zero window, then kill -9 the FTP client, wheee...</i></b>
<a name="L2026" href="source/net/ipv4/tcp.c#L2026">2026</a> <b><i>         * Note: timeout is always zero in such a case.</i></b>
<a name="L2027" href="source/net/ipv4/tcp.c#L2027">2027</a> <b><i>         */</i></b>
<a name="L2028" href="source/net/ipv4/tcp.c#L2028">2028</a>         if (<a href="ident?i=unlikely">unlikely</a>(<a href="ident?i=tcp_sk">tcp_sk</a>(sk)-&gt;repair)) {
<a name="L2029" href="source/net/ipv4/tcp.c#L2029">2029</a>                 sk-&gt;<a href="ident?i=sk_prot">sk_prot</a>-&gt;<a href="ident?i=disconnect">disconnect</a>(sk, 0);
<a name="L2030" href="source/net/ipv4/tcp.c#L2030">2030</a>         } else if (data_was_unread) {
<a name="L2031" href="source/net/ipv4/tcp.c#L2031">2031</a>                 <b><i>/* Unread data was tossed, zap the connection. */</i></b>
<a name="L2032" href="source/net/ipv4/tcp.c#L2032">2032</a>                 <a href="ident?i=NET_INC_STATS_USER">NET_INC_STATS_USER</a>(<a href="ident?i=sock_net">sock_net</a>(sk), LINUX_MIB_TCPABORTONCLOSE);
<a name="L2033" href="source/net/ipv4/tcp.c#L2033">2033</a>                 <a href="ident?i=tcp_set_state">tcp_set_state</a>(sk, TCP_CLOSE);
<a name="L2034" href="source/net/ipv4/tcp.c#L2034">2034</a>                 <a href="ident?i=tcp_send_active_reset">tcp_send_active_reset</a>(sk, sk-&gt;sk_allocation);
<a name="L2035" href="source/net/ipv4/tcp.c#L2035">2035</a>         } else if (<a href="ident?i=sock_flag">sock_flag</a>(sk, SOCK_LINGER) &amp;&amp; !sk-&gt;sk_lingertime) {
<a name="L2036" href="source/net/ipv4/tcp.c#L2036">2036</a>                 <b><i>/* Check zero linger _after_ checking for unread data. */</i></b>
<a name="L2037" href="source/net/ipv4/tcp.c#L2037">2037</a>                 sk-&gt;<a href="ident?i=sk_prot">sk_prot</a>-&gt;<a href="ident?i=disconnect">disconnect</a>(sk, 0);
<a name="L2038" href="source/net/ipv4/tcp.c#L2038">2038</a>                 <a href="ident?i=NET_INC_STATS_USER">NET_INC_STATS_USER</a>(<a href="ident?i=sock_net">sock_net</a>(sk), LINUX_MIB_TCPABORTONDATA);
<a name="L2039" href="source/net/ipv4/tcp.c#L2039">2039</a>         } else if (<a href="ident?i=tcp_close_state">tcp_close_state</a>(sk)) {
<a name="L2040" href="source/net/ipv4/tcp.c#L2040">2040</a>                 <b><i>/* We FIN if the application ate all the data before</i></b>
<a name="L2041" href="source/net/ipv4/tcp.c#L2041">2041</a> <b><i>                 * zapping the connection.</i></b>
<a name="L2042" href="source/net/ipv4/tcp.c#L2042">2042</a> <b><i>                 */</i></b>
<a name="L2043" href="source/net/ipv4/tcp.c#L2043">2043</a> 
<a name="L2044" href="source/net/ipv4/tcp.c#L2044">2044</a>                 <b><i>/* RED-PEN. Formally speaking, we have broken TCP state</i></b>
<a name="L2045" href="source/net/ipv4/tcp.c#L2045">2045</a> <b><i>                 * machine. State transitions:</i></b>
<a name="L2046" href="source/net/ipv4/tcp.c#L2046">2046</a> <b><i>                 *</i></b>
<a name="L2047" href="source/net/ipv4/tcp.c#L2047">2047</a> <b><i>                 * TCP_ESTABLISHED -&gt; TCP_FIN_WAIT1</i></b>
<a name="L2048" href="source/net/ipv4/tcp.c#L2048">2048</a> <b><i>                 * TCP_SYN_RECV -&gt; TCP_FIN_WAIT1 (forget it, it's impossible)</i></b>
<a name="L2049" href="source/net/ipv4/tcp.c#L2049">2049</a> <b><i>                 * TCP_CLOSE_WAIT -&gt; TCP_LAST_ACK</i></b>
<a name="L2050" href="source/net/ipv4/tcp.c#L2050">2050</a> <b><i>                 *</i></b>
<a name="L2051" href="source/net/ipv4/tcp.c#L2051">2051</a> <b><i>                 * are legal only when FIN has been sent (i.e. in window),</i></b>
<a name="L2052" href="source/net/ipv4/tcp.c#L2052">2052</a> <b><i>                 * rather than queued out of window. Purists blame.</i></b>
<a name="L2053" href="source/net/ipv4/tcp.c#L2053">2053</a> <b><i>                 *</i></b>
<a name="L2054" href="source/net/ipv4/tcp.c#L2054">2054</a> <b><i>                 * F.e. "RFC state" is ESTABLISHED,</i></b>
<a name="L2055" href="source/net/ipv4/tcp.c#L2055">2055</a> <b><i>                 * if Linux state is FIN-WAIT-1, but FIN is still not sent.</i></b>
<a name="L2056" href="source/net/ipv4/tcp.c#L2056">2056</a> <b><i>                 *</i></b>
<a name="L2057" href="source/net/ipv4/tcp.c#L2057">2057</a> <b><i>                 * The visible declinations are that sometimes</i></b>
<a name="L2058" href="source/net/ipv4/tcp.c#L2058">2058</a> <b><i>                 * we enter time-wait state, when it is not required really</i></b>
<a name="L2059" href="source/net/ipv4/tcp.c#L2059">2059</a> <b><i>                 * (harmless), do not send active resets, when they are</i></b>
<a name="L2060" href="source/net/ipv4/tcp.c#L2060">2060</a> <b><i>                 * required by specs (TCP_ESTABLISHED, TCP_CLOSE_WAIT, when</i></b>
<a name="L2061" href="source/net/ipv4/tcp.c#L2061">2061</a> <b><i>                 * they look as CLOSING or LAST_ACK for Linux)</i></b>
<a name="L2062" href="source/net/ipv4/tcp.c#L2062">2062</a> <b><i>                 * Probably, I missed some more holelets.</i></b>
<a name="L2063" href="source/net/ipv4/tcp.c#L2063">2063</a> <b><i>                 *                                              --ANK</i></b>
<a name="L2064" href="source/net/ipv4/tcp.c#L2064">2064</a> <b><i>                 * XXX (TFO) - To start off we don't support SYN+ACK+FIN</i></b>
<a name="L2065" href="source/net/ipv4/tcp.c#L2065">2065</a> <b><i>                 * in a single packet! (May consider it later but will</i></b>
<a name="L2066" href="source/net/ipv4/tcp.c#L2066">2066</a> <b><i>                 * probably need API support or TCP_CORK SYN-ACK until</i></b>
<a name="L2067" href="source/net/ipv4/tcp.c#L2067">2067</a> <b><i>                 * data is written and socket is closed.)</i></b>
<a name="L2068" href="source/net/ipv4/tcp.c#L2068">2068</a> <b><i>                 */</i></b>
<a name="L2069" href="source/net/ipv4/tcp.c#L2069">2069</a>                 <a href="ident?i=tcp_send_fin">tcp_send_fin</a>(sk);
<a name="L2070" href="source/net/ipv4/tcp.c#L2070">2070</a>         }
<a name="L2071" href="source/net/ipv4/tcp.c#L2071">2071</a> 
<a name="L2072" href="source/net/ipv4/tcp.c#L2072">2072</a>         <a href="ident?i=sk_stream_wait_close">sk_stream_wait_close</a>(sk, <a href="ident?i=timeout">timeout</a>);
<a name="L2073" href="source/net/ipv4/tcp.c#L2073">2073</a> 
<a name="L2074" href="source/net/ipv4/tcp.c#L2074">2074</a> adjudge_to_death:
<a name="L2075" href="source/net/ipv4/tcp.c#L2075">2075</a>         <a href="ident?i=state">state</a> = sk-&gt;<a href="ident?i=sk_state">sk_state</a>;
<a name="L2076" href="source/net/ipv4/tcp.c#L2076">2076</a>         <a href="ident?i=sock_hold">sock_hold</a>(sk);
<a name="L2077" href="source/net/ipv4/tcp.c#L2077">2077</a>         <a href="ident?i=sock_orphan">sock_orphan</a>(sk);
<a name="L2078" href="source/net/ipv4/tcp.c#L2078">2078</a> 
<a name="L2079" href="source/net/ipv4/tcp.c#L2079">2079</a>         <b><i>/* It is the last release_sock in its life. It will remove backlog. */</i></b>
<a name="L2080" href="source/net/ipv4/tcp.c#L2080">2080</a>         <a href="ident?i=release_sock">release_sock</a>(sk);
<a name="L2081" href="source/net/ipv4/tcp.c#L2081">2081</a> 
<a name="L2082" href="source/net/ipv4/tcp.c#L2082">2082</a> 
<a name="L2083" href="source/net/ipv4/tcp.c#L2083">2083</a>         <b><i>/* Now socket is owned by kernel and we acquire BH lock</i></b>
<a name="L2084" href="source/net/ipv4/tcp.c#L2084">2084</a> <b><i>           to finish close. No need to check for user refs.</i></b>
<a name="L2085" href="source/net/ipv4/tcp.c#L2085">2085</a> <b><i>         */</i></b>
<a name="L2086" href="source/net/ipv4/tcp.c#L2086">2086</a>         <a href="ident?i=local_bh_disable">local_bh_disable</a>();
<a name="L2087" href="source/net/ipv4/tcp.c#L2087">2087</a>         <a href="ident?i=bh_lock_sock">bh_lock_sock</a>(sk);
<a name="L2088" href="source/net/ipv4/tcp.c#L2088">2088</a>         <a href="ident?i=WARN_ON">WARN_ON</a>(<a href="ident?i=sock_owned_by_user">sock_owned_by_user</a>(sk));
<a name="L2089" href="source/net/ipv4/tcp.c#L2089">2089</a> 
<a name="L2090" href="source/net/ipv4/tcp.c#L2090">2090</a>         <a href="ident?i=percpu_counter_inc">percpu_counter_inc</a>(sk-&gt;<a href="ident?i=sk_prot">sk_prot</a>-&gt;orphan_count);
<a name="L2091" href="source/net/ipv4/tcp.c#L2091">2091</a> 
<a name="L2092" href="source/net/ipv4/tcp.c#L2092">2092</a>         <b><i>/* Have we already been destroyed by a softirq or backlog? */</i></b>
<a name="L2093" href="source/net/ipv4/tcp.c#L2093">2093</a>         if (<a href="ident?i=state">state</a> != TCP_CLOSE &amp;&amp; sk-&gt;<a href="ident?i=sk_state">sk_state</a> == TCP_CLOSE)
<a name="L2094" href="source/net/ipv4/tcp.c#L2094">2094</a>                 goto <a href="ident?i=out">out</a>;
<a name="L2095" href="source/net/ipv4/tcp.c#L2095">2095</a> 
<a name="L2096" href="source/net/ipv4/tcp.c#L2096">2096</a>         <b><i>/*      This is a (useful) BSD violating of the RFC. There is a</i></b>
<a name="L2097" href="source/net/ipv4/tcp.c#L2097">2097</a> <b><i>         *      problem with TCP as specified in that the other end could</i></b>
<a name="L2098" href="source/net/ipv4/tcp.c#L2098">2098</a> <b><i>         *      keep a socket open forever with no application left this end.</i></b>
<a name="L2099" href="source/net/ipv4/tcp.c#L2099">2099</a> <b><i>         *      We use a 1 minute timeout (about the same as BSD) then kill</i></b>
<a name="L2100" href="source/net/ipv4/tcp.c#L2100">2100</a> <b><i>         *      our end. If they send after that then tough - BUT: long enough</i></b>
<a name="L2101" href="source/net/ipv4/tcp.c#L2101">2101</a> <b><i>         *      that we won't make the old 4*rto = almost no time - whoops</i></b>
<a name="L2102" href="source/net/ipv4/tcp.c#L2102">2102</a> <b><i>         *      reset mistake.</i></b>
<a name="L2103" href="source/net/ipv4/tcp.c#L2103">2103</a> <b><i>         *</i></b>
<a name="L2104" href="source/net/ipv4/tcp.c#L2104">2104</a> <b><i>         *      Nope, it was not mistake. It is really desired behaviour</i></b>
<a name="L2105" href="source/net/ipv4/tcp.c#L2105">2105</a> <b><i>         *      f.e. on http servers, when such sockets are useless, but</i></b>
<a name="L2106" href="source/net/ipv4/tcp.c#L2106">2106</a> <b><i>         *      consume significant resources. Let's do it with special</i></b>
<a name="L2107" href="source/net/ipv4/tcp.c#L2107">2107</a> <b><i>         *      linger2 option.                                 --ANK</i></b>
<a name="L2108" href="source/net/ipv4/tcp.c#L2108">2108</a> <b><i>         */</i></b>
<a name="L2109" href="source/net/ipv4/tcp.c#L2109">2109</a> 
<a name="L2110" href="source/net/ipv4/tcp.c#L2110">2110</a>         if (sk-&gt;<a href="ident?i=sk_state">sk_state</a> == TCP_FIN_WAIT2) {
<a name="L2111" href="source/net/ipv4/tcp.c#L2111">2111</a>                 struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L2112" href="source/net/ipv4/tcp.c#L2112">2112</a>                 if (<a href="ident?i=tp">tp</a>-&gt;linger2 &lt; 0) {
<a name="L2113" href="source/net/ipv4/tcp.c#L2113">2113</a>                         <a href="ident?i=tcp_set_state">tcp_set_state</a>(sk, TCP_CLOSE);
<a name="L2114" href="source/net/ipv4/tcp.c#L2114">2114</a>                         <a href="ident?i=tcp_send_active_reset">tcp_send_active_reset</a>(sk, <a href="ident?i=GFP_ATOMIC">GFP_ATOMIC</a>);
<a name="L2115" href="source/net/ipv4/tcp.c#L2115">2115</a>                         <a href="ident?i=NET_INC_STATS_BH">NET_INC_STATS_BH</a>(<a href="ident?i=sock_net">sock_net</a>(sk),
<a name="L2116" href="source/net/ipv4/tcp.c#L2116">2116</a>                                         LINUX_MIB_TCPABORTONLINGER);
<a name="L2117" href="source/net/ipv4/tcp.c#L2117">2117</a>                 } else {
<a name="L2118" href="source/net/ipv4/tcp.c#L2118">2118</a>                         const int tmo = <a href="ident?i=tcp_fin_time">tcp_fin_time</a>(sk);
<a name="L2119" href="source/net/ipv4/tcp.c#L2119">2119</a> 
<a name="L2120" href="source/net/ipv4/tcp.c#L2120">2120</a>                         if (tmo &gt; <a href="ident?i=TCP_TIMEWAIT_LEN">TCP_TIMEWAIT_LEN</a>) {
<a name="L2121" href="source/net/ipv4/tcp.c#L2121">2121</a>                                 <a href="ident?i=inet_csk_reset_keepalive_timer">inet_csk_reset_keepalive_timer</a>(sk,
<a name="L2122" href="source/net/ipv4/tcp.c#L2122">2122</a>                                                 tmo - <a href="ident?i=TCP_TIMEWAIT_LEN">TCP_TIMEWAIT_LEN</a>);
<a name="L2123" href="source/net/ipv4/tcp.c#L2123">2123</a>                         } else {
<a name="L2124" href="source/net/ipv4/tcp.c#L2124">2124</a>                                 <a href="ident?i=tcp_time_wait">tcp_time_wait</a>(sk, TCP_FIN_WAIT2, tmo);
<a name="L2125" href="source/net/ipv4/tcp.c#L2125">2125</a>                                 goto <a href="ident?i=out">out</a>;
<a name="L2126" href="source/net/ipv4/tcp.c#L2126">2126</a>                         }
<a name="L2127" href="source/net/ipv4/tcp.c#L2127">2127</a>                 }
<a name="L2128" href="source/net/ipv4/tcp.c#L2128">2128</a>         }
<a name="L2129" href="source/net/ipv4/tcp.c#L2129">2129</a>         if (sk-&gt;<a href="ident?i=sk_state">sk_state</a> != TCP_CLOSE) {
<a name="L2130" href="source/net/ipv4/tcp.c#L2130">2130</a>                 <a href="ident?i=sk_mem_reclaim">sk_mem_reclaim</a>(sk);
<a name="L2131" href="source/net/ipv4/tcp.c#L2131">2131</a>                 if (<a href="ident?i=tcp_check_oom">tcp_check_oom</a>(sk, 0)) {
<a name="L2132" href="source/net/ipv4/tcp.c#L2132">2132</a>                         <a href="ident?i=tcp_set_state">tcp_set_state</a>(sk, TCP_CLOSE);
<a name="L2133" href="source/net/ipv4/tcp.c#L2133">2133</a>                         <a href="ident?i=tcp_send_active_reset">tcp_send_active_reset</a>(sk, <a href="ident?i=GFP_ATOMIC">GFP_ATOMIC</a>);
<a name="L2134" href="source/net/ipv4/tcp.c#L2134">2134</a>                         <a href="ident?i=NET_INC_STATS_BH">NET_INC_STATS_BH</a>(<a href="ident?i=sock_net">sock_net</a>(sk),
<a name="L2135" href="source/net/ipv4/tcp.c#L2135">2135</a>                                         LINUX_MIB_TCPABORTONMEMORY);
<a name="L2136" href="source/net/ipv4/tcp.c#L2136">2136</a>                 }
<a name="L2137" href="source/net/ipv4/tcp.c#L2137">2137</a>         }
<a name="L2138" href="source/net/ipv4/tcp.c#L2138">2138</a> 
<a name="L2139" href="source/net/ipv4/tcp.c#L2139">2139</a>         if (sk-&gt;<a href="ident?i=sk_state">sk_state</a> == TCP_CLOSE) {
<a name="L2140" href="source/net/ipv4/tcp.c#L2140">2140</a>                 struct <a href="ident?i=request_sock">request_sock</a> *<a href="ident?i=req">req</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk)-&gt;fastopen_rsk;
<a name="L2141" href="source/net/ipv4/tcp.c#L2141">2141</a>                 <b><i>/* We could get here with a non-NULL req if the socket is</i></b>
<a name="L2142" href="source/net/ipv4/tcp.c#L2142">2142</a> <b><i>                 * aborted (e.g., closed with unread data) before 3WHS</i></b>
<a name="L2143" href="source/net/ipv4/tcp.c#L2143">2143</a> <b><i>                 * finishes.</i></b>
<a name="L2144" href="source/net/ipv4/tcp.c#L2144">2144</a> <b><i>                 */</i></b>
<a name="L2145" href="source/net/ipv4/tcp.c#L2145">2145</a>                 if (<a href="ident?i=req">req</a>)
<a name="L2146" href="source/net/ipv4/tcp.c#L2146">2146</a>                         <a href="ident?i=reqsk_fastopen_remove">reqsk_fastopen_remove</a>(sk, <a href="ident?i=req">req</a>, <a href="ident?i=false">false</a>);
<a name="L2147" href="source/net/ipv4/tcp.c#L2147">2147</a>                 <a href="ident?i=inet_csk_destroy_sock">inet_csk_destroy_sock</a>(sk);
<a name="L2148" href="source/net/ipv4/tcp.c#L2148">2148</a>         }
<a name="L2149" href="source/net/ipv4/tcp.c#L2149">2149</a>         <b><i>/* Otherwise, socket is reprieved until protocol close. */</i></b>
<a name="L2150" href="source/net/ipv4/tcp.c#L2150">2150</a> 
<a name="L2151" href="source/net/ipv4/tcp.c#L2151">2151</a> <a href="ident?i=out">out</a>:
<a name="L2152" href="source/net/ipv4/tcp.c#L2152">2152</a>         <a href="ident?i=bh_unlock_sock">bh_unlock_sock</a>(sk);
<a name="L2153" href="source/net/ipv4/tcp.c#L2153">2153</a>         <a href="ident?i=local_bh_enable">local_bh_enable</a>();
<a name="L2154" href="source/net/ipv4/tcp.c#L2154">2154</a>         <a href="ident?i=sock_put">sock_put</a>(sk);
<a name="L2155" href="source/net/ipv4/tcp.c#L2155">2155</a> }
<a name="L2156" href="source/net/ipv4/tcp.c#L2156">2156</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=tcp_close">tcp_close</a>);
<a name="L2157" href="source/net/ipv4/tcp.c#L2157">2157</a> 
<a name="L2158" href="source/net/ipv4/tcp.c#L2158">2158</a> <b><i>/* These states need RST on ABORT according to RFC793 */</i></b>
<a name="L2159" href="source/net/ipv4/tcp.c#L2159">2159</a> 
<a name="L2160" href="source/net/ipv4/tcp.c#L2160">2160</a> static inline <a href="ident?i=bool">bool</a> <a href="ident?i=tcp_need_reset">tcp_need_reset</a>(int <a href="ident?i=state">state</a>)
<a name="L2161" href="source/net/ipv4/tcp.c#L2161">2161</a> {
<a name="L2162" href="source/net/ipv4/tcp.c#L2162">2162</a>         return (1 &lt;&lt; <a href="ident?i=state">state</a>) &amp;
<a name="L2163" href="source/net/ipv4/tcp.c#L2163">2163</a>                (TCPF_ESTABLISHED | TCPF_CLOSE_WAIT | TCPF_FIN_WAIT1 |
<a name="L2164" href="source/net/ipv4/tcp.c#L2164">2164</a>                 TCPF_FIN_WAIT2 | TCPF_SYN_RECV);
<a name="L2165" href="source/net/ipv4/tcp.c#L2165">2165</a> }
<a name="L2166" href="source/net/ipv4/tcp.c#L2166">2166</a> 
<a name="L2167" href="source/net/ipv4/tcp.c#L2167">2167</a> int <a href="ident?i=tcp_disconnect">tcp_disconnect</a>(struct <a href="ident?i=sock">sock</a> *sk, int <a href="ident?i=flags">flags</a>)
<a name="L2168" href="source/net/ipv4/tcp.c#L2168">2168</a> {
<a name="L2169" href="source/net/ipv4/tcp.c#L2169">2169</a>         struct <a href="ident?i=inet_sock">inet_sock</a> *inet = <a href="ident?i=inet_sk">inet_sk</a>(sk);
<a name="L2170" href="source/net/ipv4/tcp.c#L2170">2170</a>         struct <a href="ident?i=inet_connection_sock">inet_connection_sock</a> *icsk = <a href="ident?i=inet_csk">inet_csk</a>(sk);
<a name="L2171" href="source/net/ipv4/tcp.c#L2171">2171</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L2172" href="source/net/ipv4/tcp.c#L2172">2172</a>         int <a href="ident?i=err">err</a> = 0;
<a name="L2173" href="source/net/ipv4/tcp.c#L2173">2173</a>         int old_state = sk-&gt;<a href="ident?i=sk_state">sk_state</a>;
<a name="L2174" href="source/net/ipv4/tcp.c#L2174">2174</a> 
<a name="L2175" href="source/net/ipv4/tcp.c#L2175">2175</a>         if (old_state != TCP_CLOSE)
<a name="L2176" href="source/net/ipv4/tcp.c#L2176">2176</a>                 <a href="ident?i=tcp_set_state">tcp_set_state</a>(sk, TCP_CLOSE);
<a name="L2177" href="source/net/ipv4/tcp.c#L2177">2177</a> 
<a name="L2178" href="source/net/ipv4/tcp.c#L2178">2178</a>         <b><i>/* ABORT function of RFC793 */</i></b>
<a name="L2179" href="source/net/ipv4/tcp.c#L2179">2179</a>         if (old_state == TCP_LISTEN) {
<a name="L2180" href="source/net/ipv4/tcp.c#L2180">2180</a>                 <a href="ident?i=inet_csk_listen_stop">inet_csk_listen_stop</a>(sk);
<a name="L2181" href="source/net/ipv4/tcp.c#L2181">2181</a>         } else if (<a href="ident?i=unlikely">unlikely</a>(<a href="ident?i=tp">tp</a>-&gt;repair)) {
<a name="L2182" href="source/net/ipv4/tcp.c#L2182">2182</a>                 sk-&gt;sk_err = <a href="ident?i=ECONNABORTED">ECONNABORTED</a>;
<a name="L2183" href="source/net/ipv4/tcp.c#L2183">2183</a>         } else if (<a href="ident?i=tcp_need_reset">tcp_need_reset</a>(old_state) ||
<a name="L2184" href="source/net/ipv4/tcp.c#L2184">2184</a>                    (<a href="ident?i=tp">tp</a>-&gt;snd_nxt != <a href="ident?i=tp">tp</a>-&gt;write_seq &amp;&amp;
<a name="L2185" href="source/net/ipv4/tcp.c#L2185">2185</a>                     (1 &lt;&lt; old_state) &amp; (TCPF_CLOSING | TCPF_LAST_ACK))) {
<a name="L2186" href="source/net/ipv4/tcp.c#L2186">2186</a>                 <b><i>/* The last check adjusts for discrepancy of Linux wrt. RFC</i></b>
<a name="L2187" href="source/net/ipv4/tcp.c#L2187">2187</a> <b><i>                 * states</i></b>
<a name="L2188" href="source/net/ipv4/tcp.c#L2188">2188</a> <b><i>                 */</i></b>
<a name="L2189" href="source/net/ipv4/tcp.c#L2189">2189</a>                 <a href="ident?i=tcp_send_active_reset">tcp_send_active_reset</a>(sk, <a href="ident?i=gfp_any">gfp_any</a>());
<a name="L2190" href="source/net/ipv4/tcp.c#L2190">2190</a>                 sk-&gt;sk_err = <a href="ident?i=ECONNRESET">ECONNRESET</a>;
<a name="L2191" href="source/net/ipv4/tcp.c#L2191">2191</a>         } else if (old_state == TCP_SYN_SENT)
<a name="L2192" href="source/net/ipv4/tcp.c#L2192">2192</a>                 sk-&gt;sk_err = <a href="ident?i=ECONNRESET">ECONNRESET</a>;
<a name="L2193" href="source/net/ipv4/tcp.c#L2193">2193</a> 
<a name="L2194" href="source/net/ipv4/tcp.c#L2194">2194</a>         <a href="ident?i=tcp_clear_xmit_timers">tcp_clear_xmit_timers</a>(sk);
<a name="L2195" href="source/net/ipv4/tcp.c#L2195">2195</a>         <a href="ident?i=__skb_queue_purge">__skb_queue_purge</a>(&amp;sk-&gt;sk_receive_queue);
<a name="L2196" href="source/net/ipv4/tcp.c#L2196">2196</a>         <a href="ident?i=tcp_write_queue_purge">tcp_write_queue_purge</a>(sk);
<a name="L2197" href="source/net/ipv4/tcp.c#L2197">2197</a>         <a href="ident?i=__skb_queue_purge">__skb_queue_purge</a>(&amp;<a href="ident?i=tp">tp</a>-&gt;out_of_order_queue);
<a name="L2198" href="source/net/ipv4/tcp.c#L2198">2198</a> 
<a name="L2199" href="source/net/ipv4/tcp.c#L2199">2199</a>         inet-&gt;<a href="ident?i=inet_dport">inet_dport</a> = 0;
<a name="L2200" href="source/net/ipv4/tcp.c#L2200">2200</a> 
<a name="L2201" href="source/net/ipv4/tcp.c#L2201">2201</a>         if (!(sk-&gt;sk_userlocks &amp; <a href="ident?i=SOCK_BINDADDR_LOCK">SOCK_BINDADDR_LOCK</a>))
<a name="L2202" href="source/net/ipv4/tcp.c#L2202">2202</a>                 <a href="ident?i=inet_reset_saddr">inet_reset_saddr</a>(sk);
<a name="L2203" href="source/net/ipv4/tcp.c#L2203">2203</a> 
<a name="L2204" href="source/net/ipv4/tcp.c#L2204">2204</a>         sk-&gt;sk_shutdown = 0;
<a name="L2205" href="source/net/ipv4/tcp.c#L2205">2205</a>         <a href="ident?i=sock_reset_flag">sock_reset_flag</a>(sk, SOCK_DONE);
<a name="L2206" href="source/net/ipv4/tcp.c#L2206">2206</a>         <a href="ident?i=tp">tp</a>-&gt;srtt_us = 0;
<a name="L2207" href="source/net/ipv4/tcp.c#L2207">2207</a>         if ((<a href="ident?i=tp">tp</a>-&gt;write_seq += <a href="ident?i=tp">tp</a>-&gt;max_window + 2) == 0)
<a name="L2208" href="source/net/ipv4/tcp.c#L2208">2208</a>                 <a href="ident?i=tp">tp</a>-&gt;write_seq = 1;
<a name="L2209" href="source/net/ipv4/tcp.c#L2209">2209</a>         icsk-&gt;icsk_backoff = 0;
<a name="L2210" href="source/net/ipv4/tcp.c#L2210">2210</a>         <a href="ident?i=tp">tp</a>-&gt;snd_cwnd = 2;
<a name="L2211" href="source/net/ipv4/tcp.c#L2211">2211</a>         icsk-&gt;icsk_probes_out = 0;
<a name="L2212" href="source/net/ipv4/tcp.c#L2212">2212</a>         <a href="ident?i=tp">tp</a>-&gt;packets_out = 0;
<a name="L2213" href="source/net/ipv4/tcp.c#L2213">2213</a>         <a href="ident?i=tp">tp</a>-&gt;snd_ssthresh = <a href="ident?i=TCP_INFINITE_SSTHRESH">TCP_INFINITE_SSTHRESH</a>;
<a name="L2214" href="source/net/ipv4/tcp.c#L2214">2214</a>         <a href="ident?i=tp">tp</a>-&gt;snd_cwnd_cnt = 0;
<a name="L2215" href="source/net/ipv4/tcp.c#L2215">2215</a>         <a href="ident?i=tp">tp</a>-&gt;window_clamp = 0;
<a name="L2216" href="source/net/ipv4/tcp.c#L2216">2216</a>         <a href="ident?i=tcp_set_ca_state">tcp_set_ca_state</a>(sk, TCP_CA_Open);
<a name="L2217" href="source/net/ipv4/tcp.c#L2217">2217</a>         <a href="ident?i=tcp_clear_retrans">tcp_clear_retrans</a>(<a href="ident?i=tp">tp</a>);
<a name="L2218" href="source/net/ipv4/tcp.c#L2218">2218</a>         <a href="ident?i=inet_csk_delack_init">inet_csk_delack_init</a>(sk);
<a name="L2219" href="source/net/ipv4/tcp.c#L2219">2219</a>         <a href="ident?i=tcp_init_send_head">tcp_init_send_head</a>(sk);
<a name="L2220" href="source/net/ipv4/tcp.c#L2220">2220</a>         <a href="ident?i=memset">memset</a>(&amp;<a href="ident?i=tp">tp</a>-&gt;rx_opt, 0, sizeof(<a href="ident?i=tp">tp</a>-&gt;rx_opt));
<a name="L2221" href="source/net/ipv4/tcp.c#L2221">2221</a>         <a href="ident?i=__sk_dst_reset">__sk_dst_reset</a>(sk);
<a name="L2222" href="source/net/ipv4/tcp.c#L2222">2222</a> 
<a name="L2223" href="source/net/ipv4/tcp.c#L2223">2223</a>         <a href="ident?i=WARN_ON">WARN_ON</a>(inet-&gt;<a href="ident?i=inet_num">inet_num</a> &amp;&amp; !icsk-&gt;icsk_bind_hash);
<a name="L2224" href="source/net/ipv4/tcp.c#L2224">2224</a> 
<a name="L2225" href="source/net/ipv4/tcp.c#L2225">2225</a>         sk-&gt;sk_error_report(sk);
<a name="L2226" href="source/net/ipv4/tcp.c#L2226">2226</a>         return <a href="ident?i=err">err</a>;
<a name="L2227" href="source/net/ipv4/tcp.c#L2227">2227</a> }
<a name="L2228" href="source/net/ipv4/tcp.c#L2228">2228</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=tcp_disconnect">tcp_disconnect</a>);
<a name="L2229" href="source/net/ipv4/tcp.c#L2229">2229</a> 
<a name="L2230" href="source/net/ipv4/tcp.c#L2230">2230</a> void <a href="ident?i=tcp_sock_destruct">tcp_sock_destruct</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L2231" href="source/net/ipv4/tcp.c#L2231">2231</a> {
<a name="L2232" href="source/net/ipv4/tcp.c#L2232">2232</a>         <a href="ident?i=inet_sock_destruct">inet_sock_destruct</a>(sk);
<a name="L2233" href="source/net/ipv4/tcp.c#L2233">2233</a> 
<a name="L2234" href="source/net/ipv4/tcp.c#L2234">2234</a>         <a href="ident?i=kfree">kfree</a>(<a href="ident?i=inet_csk">inet_csk</a>(sk)-&gt;icsk_accept_queue.fastopenq);
<a name="L2235" href="source/net/ipv4/tcp.c#L2235">2235</a> }
<a name="L2236" href="source/net/ipv4/tcp.c#L2236">2236</a> 
<a name="L2237" href="source/net/ipv4/tcp.c#L2237">2237</a> static inline <a href="ident?i=bool">bool</a> <a href="ident?i=tcp_can_repair_sock">tcp_can_repair_sock</a>(const struct <a href="ident?i=sock">sock</a> *sk)
<a name="L2238" href="source/net/ipv4/tcp.c#L2238">2238</a> {
<a name="L2239" href="source/net/ipv4/tcp.c#L2239">2239</a>         return <a href="ident?i=ns_capable">ns_capable</a>(<a href="ident?i=sock_net">sock_net</a>(sk)-&gt;<a href="ident?i=user_ns">user_ns</a>, <a href="ident?i=CAP_NET_ADMIN">CAP_NET_ADMIN</a>) &amp;&amp;
<a name="L2240" href="source/net/ipv4/tcp.c#L2240">2240</a>                 ((1 &lt;&lt; sk-&gt;<a href="ident?i=sk_state">sk_state</a>) &amp; (TCPF_CLOSE | TCPF_ESTABLISHED));
<a name="L2241" href="source/net/ipv4/tcp.c#L2241">2241</a> }
<a name="L2242" href="source/net/ipv4/tcp.c#L2242">2242</a> 
<a name="L2243" href="source/net/ipv4/tcp.c#L2243">2243</a> static int <a href="ident?i=tcp_repair_options_est">tcp_repair_options_est</a>(struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a>,
<a name="L2244" href="source/net/ipv4/tcp.c#L2244">2244</a>                 struct <a href="ident?i=tcp_repair_opt">tcp_repair_opt</a> <a href="ident?i=__user">__user</a> *optbuf, unsigned int <a href="ident?i=len">len</a>)
<a name="L2245" href="source/net/ipv4/tcp.c#L2245">2245</a> {
<a name="L2246" href="source/net/ipv4/tcp.c#L2246">2246</a>         struct <a href="ident?i=tcp_repair_opt">tcp_repair_opt</a> opt;
<a name="L2247" href="source/net/ipv4/tcp.c#L2247">2247</a> 
<a name="L2248" href="source/net/ipv4/tcp.c#L2248">2248</a>         while (<a href="ident?i=len">len</a> &gt;= sizeof(opt)) {
<a name="L2249" href="source/net/ipv4/tcp.c#L2249">2249</a>                 if (<a href="ident?i=copy_from_user">copy_from_user</a>(&amp;opt, optbuf, sizeof(opt)))
<a name="L2250" href="source/net/ipv4/tcp.c#L2250">2250</a>                         return -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L2251" href="source/net/ipv4/tcp.c#L2251">2251</a> 
<a name="L2252" href="source/net/ipv4/tcp.c#L2252">2252</a>                 optbuf++;
<a name="L2253" href="source/net/ipv4/tcp.c#L2253">2253</a>                 <a href="ident?i=len">len</a> -= sizeof(opt);
<a name="L2254" href="source/net/ipv4/tcp.c#L2254">2254</a> 
<a name="L2255" href="source/net/ipv4/tcp.c#L2255">2255</a>                 switch (opt.opt_code) {
<a name="L2256" href="source/net/ipv4/tcp.c#L2256">2256</a>                 case <a href="ident?i=TCPOPT_MSS">TCPOPT_MSS</a>:
<a name="L2257" href="source/net/ipv4/tcp.c#L2257">2257</a>                         <a href="ident?i=tp">tp</a>-&gt;rx_opt.mss_clamp = opt.opt_val;
<a name="L2258" href="source/net/ipv4/tcp.c#L2258">2258</a>                         break;
<a name="L2259" href="source/net/ipv4/tcp.c#L2259">2259</a>                 case <a href="ident?i=TCPOPT_WINDOW">TCPOPT_WINDOW</a>:
<a name="L2260" href="source/net/ipv4/tcp.c#L2260">2260</a>                         {
<a name="L2261" href="source/net/ipv4/tcp.c#L2261">2261</a>                                 <a href="ident?i=u16">u16</a> snd_wscale = opt.opt_val &amp; 0xFFFF;
<a name="L2262" href="source/net/ipv4/tcp.c#L2262">2262</a>                                 <a href="ident?i=u16">u16</a> rcv_wscale = opt.opt_val &gt;&gt; 16;
<a name="L2263" href="source/net/ipv4/tcp.c#L2263">2263</a> 
<a name="L2264" href="source/net/ipv4/tcp.c#L2264">2264</a>                                 if (snd_wscale &gt; 14 || rcv_wscale &gt; 14)
<a name="L2265" href="source/net/ipv4/tcp.c#L2265">2265</a>                                         return -<a href="ident?i=EFBIG">EFBIG</a>;
<a name="L2266" href="source/net/ipv4/tcp.c#L2266">2266</a> 
<a name="L2267" href="source/net/ipv4/tcp.c#L2267">2267</a>                                 <a href="ident?i=tp">tp</a>-&gt;rx_opt.snd_wscale = snd_wscale;
<a name="L2268" href="source/net/ipv4/tcp.c#L2268">2268</a>                                 <a href="ident?i=tp">tp</a>-&gt;rx_opt.rcv_wscale = rcv_wscale;
<a name="L2269" href="source/net/ipv4/tcp.c#L2269">2269</a>                                 <a href="ident?i=tp">tp</a>-&gt;rx_opt.wscale_ok = 1;
<a name="L2270" href="source/net/ipv4/tcp.c#L2270">2270</a>                         }
<a name="L2271" href="source/net/ipv4/tcp.c#L2271">2271</a>                         break;
<a name="L2272" href="source/net/ipv4/tcp.c#L2272">2272</a>                 case <a href="ident?i=TCPOPT_SACK_PERM">TCPOPT_SACK_PERM</a>:
<a name="L2273" href="source/net/ipv4/tcp.c#L2273">2273</a>                         if (opt.opt_val != 0)
<a name="L2274" href="source/net/ipv4/tcp.c#L2274">2274</a>                                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L2275" href="source/net/ipv4/tcp.c#L2275">2275</a> 
<a name="L2276" href="source/net/ipv4/tcp.c#L2276">2276</a>                         <a href="ident?i=tp">tp</a>-&gt;rx_opt.sack_ok |= <a href="ident?i=TCP_SACK_SEEN">TCP_SACK_SEEN</a>;
<a name="L2277" href="source/net/ipv4/tcp.c#L2277">2277</a>                         if (<a href="ident?i=sysctl_tcp_fack">sysctl_tcp_fack</a>)
<a name="L2278" href="source/net/ipv4/tcp.c#L2278">2278</a>                                 <a href="ident?i=tcp_enable_fack">tcp_enable_fack</a>(<a href="ident?i=tp">tp</a>);
<a name="L2279" href="source/net/ipv4/tcp.c#L2279">2279</a>                         break;
<a name="L2280" href="source/net/ipv4/tcp.c#L2280">2280</a>                 case <a href="ident?i=TCPOPT_TIMESTAMP">TCPOPT_TIMESTAMP</a>:
<a name="L2281" href="source/net/ipv4/tcp.c#L2281">2281</a>                         if (opt.opt_val != 0)
<a name="L2282" href="source/net/ipv4/tcp.c#L2282">2282</a>                                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L2283" href="source/net/ipv4/tcp.c#L2283">2283</a> 
<a name="L2284" href="source/net/ipv4/tcp.c#L2284">2284</a>                         <a href="ident?i=tp">tp</a>-&gt;rx_opt.tstamp_ok = 1;
<a name="L2285" href="source/net/ipv4/tcp.c#L2285">2285</a>                         break;
<a name="L2286" href="source/net/ipv4/tcp.c#L2286">2286</a>                 }
<a name="L2287" href="source/net/ipv4/tcp.c#L2287">2287</a>         }
<a name="L2288" href="source/net/ipv4/tcp.c#L2288">2288</a> 
<a name="L2289" href="source/net/ipv4/tcp.c#L2289">2289</a>         return 0;
<a name="L2290" href="source/net/ipv4/tcp.c#L2290">2290</a> }
<a name="L2291" href="source/net/ipv4/tcp.c#L2291">2291</a> 
<a name="L2292" href="source/net/ipv4/tcp.c#L2292">2292</a> <b><i>/*</i></b>
<a name="L2293" href="source/net/ipv4/tcp.c#L2293">2293</a> <b><i> *      Socket option code for TCP.</i></b>
<a name="L2294" href="source/net/ipv4/tcp.c#L2294">2294</a> <b><i> */</i></b>
<a name="L2295" href="source/net/ipv4/tcp.c#L2295">2295</a> static int <a href="ident?i=do_tcp_setsockopt">do_tcp_setsockopt</a>(struct <a href="ident?i=sock">sock</a> *sk, int <a href="ident?i=level">level</a>,
<a name="L2296" href="source/net/ipv4/tcp.c#L2296">2296</a>                 int optname, char <a href="ident?i=__user">__user</a> *optval, unsigned int <a href="ident?i=optlen">optlen</a>)
<a name="L2297" href="source/net/ipv4/tcp.c#L2297">2297</a> {
<a name="L2298" href="source/net/ipv4/tcp.c#L2298">2298</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L2299" href="source/net/ipv4/tcp.c#L2299">2299</a>         struct <a href="ident?i=inet_connection_sock">inet_connection_sock</a> *icsk = <a href="ident?i=inet_csk">inet_csk</a>(sk);
<a name="L2300" href="source/net/ipv4/tcp.c#L2300">2300</a>         int <a href="ident?i=val">val</a>;
<a name="L2301" href="source/net/ipv4/tcp.c#L2301">2301</a>         int <a href="ident?i=err">err</a> = 0;
<a name="L2302" href="source/net/ipv4/tcp.c#L2302">2302</a> 
<a name="L2303" href="source/net/ipv4/tcp.c#L2303">2303</a>         <b><i>/* These are data/string values, all the others are ints */</i></b>
<a name="L2304" href="source/net/ipv4/tcp.c#L2304">2304</a>         switch (optname) {
<a name="L2305" href="source/net/ipv4/tcp.c#L2305">2305</a>         case <a href="ident?i=TCP_CONGESTION">TCP_CONGESTION</a>: {
<a name="L2306" href="source/net/ipv4/tcp.c#L2306">2306</a>                 char <a href="ident?i=name">name</a>[<a href="ident?i=TCP_CA_NAME_MAX">TCP_CA_NAME_MAX</a>];
<a name="L2307" href="source/net/ipv4/tcp.c#L2307">2307</a> 
<a name="L2308" href="source/net/ipv4/tcp.c#L2308">2308</a>                 if (<a href="ident?i=optlen">optlen</a> &lt; 1)
<a name="L2309" href="source/net/ipv4/tcp.c#L2309">2309</a>                         return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L2310" href="source/net/ipv4/tcp.c#L2310">2310</a> 
<a name="L2311" href="source/net/ipv4/tcp.c#L2311">2311</a>                 <a href="ident?i=val">val</a> = <a href="ident?i=strncpy_from_user">strncpy_from_user</a>(<a href="ident?i=name">name</a>, optval,
<a name="L2312" href="source/net/ipv4/tcp.c#L2312">2312</a>                                         <a href="ident?i=min_t">min_t</a>(long, <a href="ident?i=TCP_CA_NAME_MAX">TCP_CA_NAME_MAX</a>-1, <a href="ident?i=optlen">optlen</a>));
<a name="L2313" href="source/net/ipv4/tcp.c#L2313">2313</a>                 if (<a href="ident?i=val">val</a> &lt; 0)
<a name="L2314" href="source/net/ipv4/tcp.c#L2314">2314</a>                         return -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L2315" href="source/net/ipv4/tcp.c#L2315">2315</a>                 <a href="ident?i=name">name</a>[<a href="ident?i=val">val</a>] = 0;
<a name="L2316" href="source/net/ipv4/tcp.c#L2316">2316</a> 
<a name="L2317" href="source/net/ipv4/tcp.c#L2317">2317</a>                 <a href="ident?i=lock_sock">lock_sock</a>(sk);
<a name="L2318" href="source/net/ipv4/tcp.c#L2318">2318</a>                 <a href="ident?i=err">err</a> = <a href="ident?i=tcp_set_congestion_control">tcp_set_congestion_control</a>(sk, <a href="ident?i=name">name</a>);
<a name="L2319" href="source/net/ipv4/tcp.c#L2319">2319</a>                 <a href="ident?i=release_sock">release_sock</a>(sk);
<a name="L2320" href="source/net/ipv4/tcp.c#L2320">2320</a>                 return <a href="ident?i=err">err</a>;
<a name="L2321" href="source/net/ipv4/tcp.c#L2321">2321</a>         }
<a name="L2322" href="source/net/ipv4/tcp.c#L2322">2322</a>         default:
<a name="L2323" href="source/net/ipv4/tcp.c#L2323">2323</a>                 <b><i>/* fallthru */</i></b>
<a name="L2324" href="source/net/ipv4/tcp.c#L2324">2324</a>                 break;
<a name="L2325" href="source/net/ipv4/tcp.c#L2325">2325</a>         }
<a name="L2326" href="source/net/ipv4/tcp.c#L2326">2326</a> 
<a name="L2327" href="source/net/ipv4/tcp.c#L2327">2327</a>         if (<a href="ident?i=optlen">optlen</a> &lt; sizeof(int))
<a name="L2328" href="source/net/ipv4/tcp.c#L2328">2328</a>                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L2329" href="source/net/ipv4/tcp.c#L2329">2329</a> 
<a name="L2330" href="source/net/ipv4/tcp.c#L2330">2330</a>         if (<a href="ident?i=get_user">get_user</a>(<a href="ident?i=val">val</a>, (int <a href="ident?i=__user">__user</a> *)optval))
<a name="L2331" href="source/net/ipv4/tcp.c#L2331">2331</a>                 return -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L2332" href="source/net/ipv4/tcp.c#L2332">2332</a> 
<a name="L2333" href="source/net/ipv4/tcp.c#L2333">2333</a>         <a href="ident?i=lock_sock">lock_sock</a>(sk);
<a name="L2334" href="source/net/ipv4/tcp.c#L2334">2334</a> 
<a name="L2335" href="source/net/ipv4/tcp.c#L2335">2335</a>         switch (optname) {
<a name="L2336" href="source/net/ipv4/tcp.c#L2336">2336</a>         case <a href="ident?i=TCP_MAXSEG">TCP_MAXSEG</a>:
<a name="L2337" href="source/net/ipv4/tcp.c#L2337">2337</a>                 <b><i>/* Values greater than interface MTU won't take effect. However</i></b>
<a name="L2338" href="source/net/ipv4/tcp.c#L2338">2338</a> <b><i>                 * at the point when this call is done we typically don't yet</i></b>
<a name="L2339" href="source/net/ipv4/tcp.c#L2339">2339</a> <b><i>                 * know which interface is going to be used */</i></b>
<a name="L2340" href="source/net/ipv4/tcp.c#L2340">2340</a>                 if (<a href="ident?i=val">val</a> &lt; <a href="ident?i=TCP_MIN_MSS">TCP_MIN_MSS</a> || <a href="ident?i=val">val</a> &gt; <a href="ident?i=MAX_TCP_WINDOW">MAX_TCP_WINDOW</a>) {
<a name="L2341" href="source/net/ipv4/tcp.c#L2341">2341</a>                         <a href="ident?i=err">err</a> = -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L2342" href="source/net/ipv4/tcp.c#L2342">2342</a>                         break;
<a name="L2343" href="source/net/ipv4/tcp.c#L2343">2343</a>                 }
<a name="L2344" href="source/net/ipv4/tcp.c#L2344">2344</a>                 <a href="ident?i=tp">tp</a>-&gt;rx_opt.user_mss = <a href="ident?i=val">val</a>;
<a name="L2345" href="source/net/ipv4/tcp.c#L2345">2345</a>                 break;
<a name="L2346" href="source/net/ipv4/tcp.c#L2346">2346</a> 
<a name="L2347" href="source/net/ipv4/tcp.c#L2347">2347</a>         case <a href="ident?i=TCP_NODELAY">TCP_NODELAY</a>:
<a name="L2348" href="source/net/ipv4/tcp.c#L2348">2348</a>                 if (<a href="ident?i=val">val</a>) {
<a name="L2349" href="source/net/ipv4/tcp.c#L2349">2349</a>                         <b><i>/* TCP_NODELAY is weaker than TCP_CORK, so that</i></b>
<a name="L2350" href="source/net/ipv4/tcp.c#L2350">2350</a> <b><i>                         * this option on corked socket is remembered, but</i></b>
<a name="L2351" href="source/net/ipv4/tcp.c#L2351">2351</a> <b><i>                         * it is not activated until cork is cleared.</i></b>
<a name="L2352" href="source/net/ipv4/tcp.c#L2352">2352</a> <b><i>                         *</i></b>
<a name="L2353" href="source/net/ipv4/tcp.c#L2353">2353</a> <b><i>                         * However, when TCP_NODELAY is set we make</i></b>
<a name="L2354" href="source/net/ipv4/tcp.c#L2354">2354</a> <b><i>                         * an explicit push, which overrides even TCP_CORK</i></b>
<a name="L2355" href="source/net/ipv4/tcp.c#L2355">2355</a> <b><i>                         * for currently queued segments.</i></b>
<a name="L2356" href="source/net/ipv4/tcp.c#L2356">2356</a> <b><i>                         */</i></b>
<a name="L2357" href="source/net/ipv4/tcp.c#L2357">2357</a>                         <a href="ident?i=tp">tp</a>-&gt;nonagle |= <a href="ident?i=TCP_NAGLE_OFF">TCP_NAGLE_OFF</a>|<a href="ident?i=TCP_NAGLE_PUSH">TCP_NAGLE_PUSH</a>;
<a name="L2358" href="source/net/ipv4/tcp.c#L2358">2358</a>                         <a href="ident?i=tcp_push_pending_frames">tcp_push_pending_frames</a>(sk);
<a name="L2359" href="source/net/ipv4/tcp.c#L2359">2359</a>                 } else {
<a name="L2360" href="source/net/ipv4/tcp.c#L2360">2360</a>                         <a href="ident?i=tp">tp</a>-&gt;nonagle &amp;= ~TCP_NAGLE_OFF;
<a name="L2361" href="source/net/ipv4/tcp.c#L2361">2361</a>                 }
<a name="L2362" href="source/net/ipv4/tcp.c#L2362">2362</a>                 break;
<a name="L2363" href="source/net/ipv4/tcp.c#L2363">2363</a> 
<a name="L2364" href="source/net/ipv4/tcp.c#L2364">2364</a>         case <a href="ident?i=TCP_THIN_LINEAR_TIMEOUTS">TCP_THIN_LINEAR_TIMEOUTS</a>:
<a name="L2365" href="source/net/ipv4/tcp.c#L2365">2365</a>                 if (<a href="ident?i=val">val</a> &lt; 0 || <a href="ident?i=val">val</a> &gt; 1)
<a name="L2366" href="source/net/ipv4/tcp.c#L2366">2366</a>                         <a href="ident?i=err">err</a> = -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L2367" href="source/net/ipv4/tcp.c#L2367">2367</a>                 else
<a name="L2368" href="source/net/ipv4/tcp.c#L2368">2368</a>                         <a href="ident?i=tp">tp</a>-&gt;thin_lto = <a href="ident?i=val">val</a>;
<a name="L2369" href="source/net/ipv4/tcp.c#L2369">2369</a>                 break;
<a name="L2370" href="source/net/ipv4/tcp.c#L2370">2370</a> 
<a name="L2371" href="source/net/ipv4/tcp.c#L2371">2371</a>         case <a href="ident?i=TCP_THIN_DUPACK">TCP_THIN_DUPACK</a>:
<a name="L2372" href="source/net/ipv4/tcp.c#L2372">2372</a>                 if (<a href="ident?i=val">val</a> &lt; 0 || <a href="ident?i=val">val</a> &gt; 1)
<a name="L2373" href="source/net/ipv4/tcp.c#L2373">2373</a>                         <a href="ident?i=err">err</a> = -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L2374" href="source/net/ipv4/tcp.c#L2374">2374</a>                 else {
<a name="L2375" href="source/net/ipv4/tcp.c#L2375">2375</a>                         <a href="ident?i=tp">tp</a>-&gt;thin_dupack = <a href="ident?i=val">val</a>;
<a name="L2376" href="source/net/ipv4/tcp.c#L2376">2376</a>                         if (<a href="ident?i=tp">tp</a>-&gt;thin_dupack)
<a name="L2377" href="source/net/ipv4/tcp.c#L2377">2377</a>                                 <a href="ident?i=tcp_disable_early_retrans">tcp_disable_early_retrans</a>(<a href="ident?i=tp">tp</a>);
<a name="L2378" href="source/net/ipv4/tcp.c#L2378">2378</a>                 }
<a name="L2379" href="source/net/ipv4/tcp.c#L2379">2379</a>                 break;
<a name="L2380" href="source/net/ipv4/tcp.c#L2380">2380</a> 
<a name="L2381" href="source/net/ipv4/tcp.c#L2381">2381</a>         case <a href="ident?i=TCP_REPAIR">TCP_REPAIR</a>:
<a name="L2382" href="source/net/ipv4/tcp.c#L2382">2382</a>                 if (!<a href="ident?i=tcp_can_repair_sock">tcp_can_repair_sock</a>(sk))
<a name="L2383" href="source/net/ipv4/tcp.c#L2383">2383</a>                         <a href="ident?i=err">err</a> = -<a href="ident?i=EPERM">EPERM</a>;
<a name="L2384" href="source/net/ipv4/tcp.c#L2384">2384</a>                 else if (<a href="ident?i=val">val</a> == 1) {
<a name="L2385" href="source/net/ipv4/tcp.c#L2385">2385</a>                         <a href="ident?i=tp">tp</a>-&gt;repair = 1;
<a name="L2386" href="source/net/ipv4/tcp.c#L2386">2386</a>                         sk-&gt;<a href="ident?i=sk_reuse">sk_reuse</a> = <a href="ident?i=SK_FORCE_REUSE">SK_FORCE_REUSE</a>;
<a name="L2387" href="source/net/ipv4/tcp.c#L2387">2387</a>                         <a href="ident?i=tp">tp</a>-&gt;repair_queue = TCP_NO_QUEUE;
<a name="L2388" href="source/net/ipv4/tcp.c#L2388">2388</a>                 } else if (<a href="ident?i=val">val</a> == 0) {
<a name="L2389" href="source/net/ipv4/tcp.c#L2389">2389</a>                         <a href="ident?i=tp">tp</a>-&gt;repair = 0;
<a name="L2390" href="source/net/ipv4/tcp.c#L2390">2390</a>                         sk-&gt;<a href="ident?i=sk_reuse">sk_reuse</a> = <a href="ident?i=SK_NO_REUSE">SK_NO_REUSE</a>;
<a name="L2391" href="source/net/ipv4/tcp.c#L2391">2391</a>                         <a href="ident?i=tcp_send_window_probe">tcp_send_window_probe</a>(sk);
<a name="L2392" href="source/net/ipv4/tcp.c#L2392">2392</a>                 } else
<a name="L2393" href="source/net/ipv4/tcp.c#L2393">2393</a>                         <a href="ident?i=err">err</a> = -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L2394" href="source/net/ipv4/tcp.c#L2394">2394</a> 
<a name="L2395" href="source/net/ipv4/tcp.c#L2395">2395</a>                 break;
<a name="L2396" href="source/net/ipv4/tcp.c#L2396">2396</a> 
<a name="L2397" href="source/net/ipv4/tcp.c#L2397">2397</a>         case <a href="ident?i=TCP_REPAIR_QUEUE">TCP_REPAIR_QUEUE</a>:
<a name="L2398" href="source/net/ipv4/tcp.c#L2398">2398</a>                 if (!<a href="ident?i=tp">tp</a>-&gt;repair)
<a name="L2399" href="source/net/ipv4/tcp.c#L2399">2399</a>                         <a href="ident?i=err">err</a> = -<a href="ident?i=EPERM">EPERM</a>;
<a name="L2400" href="source/net/ipv4/tcp.c#L2400">2400</a>                 else if (<a href="ident?i=val">val</a> &lt; TCP_QUEUES_NR)
<a name="L2401" href="source/net/ipv4/tcp.c#L2401">2401</a>                         <a href="ident?i=tp">tp</a>-&gt;repair_queue = <a href="ident?i=val">val</a>;
<a name="L2402" href="source/net/ipv4/tcp.c#L2402">2402</a>                 else
<a name="L2403" href="source/net/ipv4/tcp.c#L2403">2403</a>                         <a href="ident?i=err">err</a> = -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L2404" href="source/net/ipv4/tcp.c#L2404">2404</a>                 break;
<a name="L2405" href="source/net/ipv4/tcp.c#L2405">2405</a> 
<a name="L2406" href="source/net/ipv4/tcp.c#L2406">2406</a>         case <a href="ident?i=TCP_QUEUE_SEQ">TCP_QUEUE_SEQ</a>:
<a name="L2407" href="source/net/ipv4/tcp.c#L2407">2407</a>                 if (sk-&gt;<a href="ident?i=sk_state">sk_state</a> != TCP_CLOSE)
<a name="L2408" href="source/net/ipv4/tcp.c#L2408">2408</a>                         <a href="ident?i=err">err</a> = -<a href="ident?i=EPERM">EPERM</a>;
<a name="L2409" href="source/net/ipv4/tcp.c#L2409">2409</a>                 else if (<a href="ident?i=tp">tp</a>-&gt;repair_queue == TCP_SEND_QUEUE)
<a name="L2410" href="source/net/ipv4/tcp.c#L2410">2410</a>                         <a href="ident?i=tp">tp</a>-&gt;write_seq = <a href="ident?i=val">val</a>;
<a name="L2411" href="source/net/ipv4/tcp.c#L2411">2411</a>                 else if (<a href="ident?i=tp">tp</a>-&gt;repair_queue == TCP_RECV_QUEUE)
<a name="L2412" href="source/net/ipv4/tcp.c#L2412">2412</a>                         <a href="ident?i=tp">tp</a>-&gt;rcv_nxt = <a href="ident?i=val">val</a>;
<a name="L2413" href="source/net/ipv4/tcp.c#L2413">2413</a>                 else
<a name="L2414" href="source/net/ipv4/tcp.c#L2414">2414</a>                         <a href="ident?i=err">err</a> = -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L2415" href="source/net/ipv4/tcp.c#L2415">2415</a>                 break;
<a name="L2416" href="source/net/ipv4/tcp.c#L2416">2416</a> 
<a name="L2417" href="source/net/ipv4/tcp.c#L2417">2417</a>         case <a href="ident?i=TCP_REPAIR_OPTIONS">TCP_REPAIR_OPTIONS</a>:
<a name="L2418" href="source/net/ipv4/tcp.c#L2418">2418</a>                 if (!<a href="ident?i=tp">tp</a>-&gt;repair)
<a name="L2419" href="source/net/ipv4/tcp.c#L2419">2419</a>                         <a href="ident?i=err">err</a> = -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L2420" href="source/net/ipv4/tcp.c#L2420">2420</a>                 else if (sk-&gt;<a href="ident?i=sk_state">sk_state</a> == TCP_ESTABLISHED)
<a name="L2421" href="source/net/ipv4/tcp.c#L2421">2421</a>                         <a href="ident?i=err">err</a> = <a href="ident?i=tcp_repair_options_est">tcp_repair_options_est</a>(<a href="ident?i=tp">tp</a>,
<a name="L2422" href="source/net/ipv4/tcp.c#L2422">2422</a>                                         (struct <a href="ident?i=tcp_repair_opt">tcp_repair_opt</a> <a href="ident?i=__user">__user</a> *)optval,
<a name="L2423" href="source/net/ipv4/tcp.c#L2423">2423</a>                                         <a href="ident?i=optlen">optlen</a>);
<a name="L2424" href="source/net/ipv4/tcp.c#L2424">2424</a>                 else
<a name="L2425" href="source/net/ipv4/tcp.c#L2425">2425</a>                         <a href="ident?i=err">err</a> = -<a href="ident?i=EPERM">EPERM</a>;
<a name="L2426" href="source/net/ipv4/tcp.c#L2426">2426</a>                 break;
<a name="L2427" href="source/net/ipv4/tcp.c#L2427">2427</a> 
<a name="L2428" href="source/net/ipv4/tcp.c#L2428">2428</a>         case <a href="ident?i=TCP_CORK">TCP_CORK</a>:
<a name="L2429" href="source/net/ipv4/tcp.c#L2429">2429</a>                 <b><i>/* When set indicates to always queue non-full frames.</i></b>
<a name="L2430" href="source/net/ipv4/tcp.c#L2430">2430</a> <b><i>                 * Later the user clears this option and we transmit</i></b>
<a name="L2431" href="source/net/ipv4/tcp.c#L2431">2431</a> <b><i>                 * any pending partial frames in the queue.  This is</i></b>
<a name="L2432" href="source/net/ipv4/tcp.c#L2432">2432</a> <b><i>                 * meant to be used alongside sendfile() to get properly</i></b>
<a name="L2433" href="source/net/ipv4/tcp.c#L2433">2433</a> <b><i>                 * filled frames when the user (for example) must write</i></b>
<a name="L2434" href="source/net/ipv4/tcp.c#L2434">2434</a> <b><i>                 * out headers with a write() call first and then use</i></b>
<a name="L2435" href="source/net/ipv4/tcp.c#L2435">2435</a> <b><i>                 * sendfile to send out the data parts.</i></b>
<a name="L2436" href="source/net/ipv4/tcp.c#L2436">2436</a> <b><i>                 *</i></b>
<a name="L2437" href="source/net/ipv4/tcp.c#L2437">2437</a> <b><i>                 * TCP_CORK can be set together with TCP_NODELAY and it is</i></b>
<a name="L2438" href="source/net/ipv4/tcp.c#L2438">2438</a> <b><i>                 * stronger than TCP_NODELAY.</i></b>
<a name="L2439" href="source/net/ipv4/tcp.c#L2439">2439</a> <b><i>                 */</i></b>
<a name="L2440" href="source/net/ipv4/tcp.c#L2440">2440</a>                 if (<a href="ident?i=val">val</a>) {
<a name="L2441" href="source/net/ipv4/tcp.c#L2441">2441</a>                         <a href="ident?i=tp">tp</a>-&gt;nonagle |= <a href="ident?i=TCP_NAGLE_CORK">TCP_NAGLE_CORK</a>;
<a name="L2442" href="source/net/ipv4/tcp.c#L2442">2442</a>                 } else {
<a name="L2443" href="source/net/ipv4/tcp.c#L2443">2443</a>                         <a href="ident?i=tp">tp</a>-&gt;nonagle &amp;= ~TCP_NAGLE_CORK;
<a name="L2444" href="source/net/ipv4/tcp.c#L2444">2444</a>                         if (<a href="ident?i=tp">tp</a>-&gt;nonagle&amp;<a href="ident?i=TCP_NAGLE_OFF">TCP_NAGLE_OFF</a>)
<a name="L2445" href="source/net/ipv4/tcp.c#L2445">2445</a>                                 <a href="ident?i=tp">tp</a>-&gt;nonagle |= <a href="ident?i=TCP_NAGLE_PUSH">TCP_NAGLE_PUSH</a>;
<a name="L2446" href="source/net/ipv4/tcp.c#L2446">2446</a>                         <a href="ident?i=tcp_push_pending_frames">tcp_push_pending_frames</a>(sk);
<a name="L2447" href="source/net/ipv4/tcp.c#L2447">2447</a>                 }
<a name="L2448" href="source/net/ipv4/tcp.c#L2448">2448</a>                 break;
<a name="L2449" href="source/net/ipv4/tcp.c#L2449">2449</a> 
<a name="L2450" href="source/net/ipv4/tcp.c#L2450">2450</a>         case <a href="ident?i=TCP_KEEPIDLE">TCP_KEEPIDLE</a>:
<a name="L2451" href="source/net/ipv4/tcp.c#L2451">2451</a>                 if (<a href="ident?i=val">val</a> &lt; 1 || <a href="ident?i=val">val</a> &gt; <a href="ident?i=MAX_TCP_KEEPIDLE">MAX_TCP_KEEPIDLE</a>)
<a name="L2452" href="source/net/ipv4/tcp.c#L2452">2452</a>                         <a href="ident?i=err">err</a> = -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L2453" href="source/net/ipv4/tcp.c#L2453">2453</a>                 else {
<a name="L2454" href="source/net/ipv4/tcp.c#L2454">2454</a>                         <a href="ident?i=tp">tp</a>-&gt;keepalive_time = <a href="ident?i=val">val</a> * <a href="ident?i=HZ">HZ</a>;
<a name="L2455" href="source/net/ipv4/tcp.c#L2455">2455</a>                         if (<a href="ident?i=sock_flag">sock_flag</a>(sk, SOCK_KEEPOPEN) &amp;&amp;
<a name="L2456" href="source/net/ipv4/tcp.c#L2456">2456</a>                             !((1 &lt;&lt; sk-&gt;<a href="ident?i=sk_state">sk_state</a>) &amp;
<a name="L2457" href="source/net/ipv4/tcp.c#L2457">2457</a>                               (TCPF_CLOSE | TCPF_LISTEN))) {
<a name="L2458" href="source/net/ipv4/tcp.c#L2458">2458</a>                                 <a href="ident?i=u32">u32</a> elapsed = <a href="ident?i=keepalive_time_elapsed">keepalive_time_elapsed</a>(<a href="ident?i=tp">tp</a>);
<a name="L2459" href="source/net/ipv4/tcp.c#L2459">2459</a>                                 if (<a href="ident?i=tp">tp</a>-&gt;keepalive_time &gt; elapsed)
<a name="L2460" href="source/net/ipv4/tcp.c#L2460">2460</a>                                         elapsed = <a href="ident?i=tp">tp</a>-&gt;keepalive_time - elapsed;
<a name="L2461" href="source/net/ipv4/tcp.c#L2461">2461</a>                                 else
<a name="L2462" href="source/net/ipv4/tcp.c#L2462">2462</a>                                         elapsed = 0;
<a name="L2463" href="source/net/ipv4/tcp.c#L2463">2463</a>                                 <a href="ident?i=inet_csk_reset_keepalive_timer">inet_csk_reset_keepalive_timer</a>(sk, elapsed);
<a name="L2464" href="source/net/ipv4/tcp.c#L2464">2464</a>                         }
<a name="L2465" href="source/net/ipv4/tcp.c#L2465">2465</a>                 }
<a name="L2466" href="source/net/ipv4/tcp.c#L2466">2466</a>                 break;
<a name="L2467" href="source/net/ipv4/tcp.c#L2467">2467</a>         case <a href="ident?i=TCP_KEEPINTVL">TCP_KEEPINTVL</a>:
<a name="L2468" href="source/net/ipv4/tcp.c#L2468">2468</a>                 if (<a href="ident?i=val">val</a> &lt; 1 || <a href="ident?i=val">val</a> &gt; <a href="ident?i=MAX_TCP_KEEPINTVL">MAX_TCP_KEEPINTVL</a>)
<a name="L2469" href="source/net/ipv4/tcp.c#L2469">2469</a>                         <a href="ident?i=err">err</a> = -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L2470" href="source/net/ipv4/tcp.c#L2470">2470</a>                 else
<a name="L2471" href="source/net/ipv4/tcp.c#L2471">2471</a>                         <a href="ident?i=tp">tp</a>-&gt;<a href="ident?i=keepalive_intvl">keepalive_intvl</a> = <a href="ident?i=val">val</a> * <a href="ident?i=HZ">HZ</a>;
<a name="L2472" href="source/net/ipv4/tcp.c#L2472">2472</a>                 break;
<a name="L2473" href="source/net/ipv4/tcp.c#L2473">2473</a>         case <a href="ident?i=TCP_KEEPCNT">TCP_KEEPCNT</a>:
<a name="L2474" href="source/net/ipv4/tcp.c#L2474">2474</a>                 if (<a href="ident?i=val">val</a> &lt; 1 || <a href="ident?i=val">val</a> &gt; <a href="ident?i=MAX_TCP_KEEPCNT">MAX_TCP_KEEPCNT</a>)
<a name="L2475" href="source/net/ipv4/tcp.c#L2475">2475</a>                         <a href="ident?i=err">err</a> = -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L2476" href="source/net/ipv4/tcp.c#L2476">2476</a>                 else
<a name="L2477" href="source/net/ipv4/tcp.c#L2477">2477</a>                         <a href="ident?i=tp">tp</a>-&gt;<a href="ident?i=keepalive_probes">keepalive_probes</a> = <a href="ident?i=val">val</a>;
<a name="L2478" href="source/net/ipv4/tcp.c#L2478">2478</a>                 break;
<a name="L2479" href="source/net/ipv4/tcp.c#L2479">2479</a>         case <a href="ident?i=TCP_SYNCNT">TCP_SYNCNT</a>:
<a name="L2480" href="source/net/ipv4/tcp.c#L2480">2480</a>                 if (<a href="ident?i=val">val</a> &lt; 1 || <a href="ident?i=val">val</a> &gt; <a href="ident?i=MAX_TCP_SYNCNT">MAX_TCP_SYNCNT</a>)
<a name="L2481" href="source/net/ipv4/tcp.c#L2481">2481</a>                         <a href="ident?i=err">err</a> = -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L2482" href="source/net/ipv4/tcp.c#L2482">2482</a>                 else
<a name="L2483" href="source/net/ipv4/tcp.c#L2483">2483</a>                         icsk-&gt;icsk_syn_retries = <a href="ident?i=val">val</a>;
<a name="L2484" href="source/net/ipv4/tcp.c#L2484">2484</a>                 break;
<a name="L2485" href="source/net/ipv4/tcp.c#L2485">2485</a> 
<a name="L2486" href="source/net/ipv4/tcp.c#L2486">2486</a>         case <a href="ident?i=TCP_LINGER2">TCP_LINGER2</a>:
<a name="L2487" href="source/net/ipv4/tcp.c#L2487">2487</a>                 if (<a href="ident?i=val">val</a> &lt; 0)
<a name="L2488" href="source/net/ipv4/tcp.c#L2488">2488</a>                         <a href="ident?i=tp">tp</a>-&gt;linger2 = -1;
<a name="L2489" href="source/net/ipv4/tcp.c#L2489">2489</a>                 else if (<a href="ident?i=val">val</a> &gt; <a href="ident?i=sysctl_tcp_fin_timeout">sysctl_tcp_fin_timeout</a> / <a href="ident?i=HZ">HZ</a>)
<a name="L2490" href="source/net/ipv4/tcp.c#L2490">2490</a>                         <a href="ident?i=tp">tp</a>-&gt;linger2 = 0;
<a name="L2491" href="source/net/ipv4/tcp.c#L2491">2491</a>                 else
<a name="L2492" href="source/net/ipv4/tcp.c#L2492">2492</a>                         <a href="ident?i=tp">tp</a>-&gt;linger2 = <a href="ident?i=val">val</a> * <a href="ident?i=HZ">HZ</a>;
<a name="L2493" href="source/net/ipv4/tcp.c#L2493">2493</a>                 break;
<a name="L2494" href="source/net/ipv4/tcp.c#L2494">2494</a> 
<a name="L2495" href="source/net/ipv4/tcp.c#L2495">2495</a>         case <a href="ident?i=TCP_DEFER_ACCEPT">TCP_DEFER_ACCEPT</a>:
<a name="L2496" href="source/net/ipv4/tcp.c#L2496">2496</a>                 <b><i>/* Translate value in seconds to number of retransmits */</i></b>
<a name="L2497" href="source/net/ipv4/tcp.c#L2497">2497</a>                 icsk-&gt;icsk_accept_queue.rskq_defer_accept =
<a name="L2498" href="source/net/ipv4/tcp.c#L2498">2498</a>                         <a href="ident?i=secs_to_retrans">secs_to_retrans</a>(<a href="ident?i=val">val</a>, <a href="ident?i=TCP_TIMEOUT_INIT">TCP_TIMEOUT_INIT</a> / <a href="ident?i=HZ">HZ</a>,
<a name="L2499" href="source/net/ipv4/tcp.c#L2499">2499</a>                                         <a href="ident?i=TCP_RTO_MAX">TCP_RTO_MAX</a> / <a href="ident?i=HZ">HZ</a>);
<a name="L2500" href="source/net/ipv4/tcp.c#L2500">2500</a>                 break;
<a name="L2501" href="source/net/ipv4/tcp.c#L2501">2501</a> 
<a name="L2502" href="source/net/ipv4/tcp.c#L2502">2502</a>         case <a href="ident?i=TCP_WINDOW_CLAMP">TCP_WINDOW_CLAMP</a>:
<a name="L2503" href="source/net/ipv4/tcp.c#L2503">2503</a>                 if (!<a href="ident?i=val">val</a>) {
<a name="L2504" href="source/net/ipv4/tcp.c#L2504">2504</a>                         if (sk-&gt;<a href="ident?i=sk_state">sk_state</a> != TCP_CLOSE) {
<a name="L2505" href="source/net/ipv4/tcp.c#L2505">2505</a>                                 <a href="ident?i=err">err</a> = -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L2506" href="source/net/ipv4/tcp.c#L2506">2506</a>                                 break;
<a name="L2507" href="source/net/ipv4/tcp.c#L2507">2507</a>                         }
<a name="L2508" href="source/net/ipv4/tcp.c#L2508">2508</a>                         <a href="ident?i=tp">tp</a>-&gt;window_clamp = 0;
<a name="L2509" href="source/net/ipv4/tcp.c#L2509">2509</a>                 } else
<a name="L2510" href="source/net/ipv4/tcp.c#L2510">2510</a>                         <a href="ident?i=tp">tp</a>-&gt;window_clamp = <a href="ident?i=val">val</a> &lt; <a href="ident?i=SOCK_MIN_RCVBUF">SOCK_MIN_RCVBUF</a> / 2 ?
<a name="L2511" href="source/net/ipv4/tcp.c#L2511">2511</a>                                                 <a href="ident?i=SOCK_MIN_RCVBUF">SOCK_MIN_RCVBUF</a> / 2 : <a href="ident?i=val">val</a>;
<a name="L2512" href="source/net/ipv4/tcp.c#L2512">2512</a>                 break;
<a name="L2513" href="source/net/ipv4/tcp.c#L2513">2513</a> 
<a name="L2514" href="source/net/ipv4/tcp.c#L2514">2514</a>         case <a href="ident?i=TCP_QUICKACK">TCP_QUICKACK</a>:
<a name="L2515" href="source/net/ipv4/tcp.c#L2515">2515</a>                 if (!<a href="ident?i=val">val</a>) {
<a name="L2516" href="source/net/ipv4/tcp.c#L2516">2516</a>                         icsk-&gt;icsk_ack.pingpong = 1;
<a name="L2517" href="source/net/ipv4/tcp.c#L2517">2517</a>                 } else {
<a name="L2518" href="source/net/ipv4/tcp.c#L2518">2518</a>                         icsk-&gt;icsk_ack.pingpong = 0;
<a name="L2519" href="source/net/ipv4/tcp.c#L2519">2519</a>                         if ((1 &lt;&lt; sk-&gt;<a href="ident?i=sk_state">sk_state</a>) &amp;
<a name="L2520" href="source/net/ipv4/tcp.c#L2520">2520</a>                             (TCPF_ESTABLISHED | TCPF_CLOSE_WAIT) &amp;&amp;
<a name="L2521" href="source/net/ipv4/tcp.c#L2521">2521</a>                             <a href="ident?i=inet_csk_ack_scheduled">inet_csk_ack_scheduled</a>(sk)) {
<a name="L2522" href="source/net/ipv4/tcp.c#L2522">2522</a>                                 icsk-&gt;icsk_ack.<a href="ident?i=pending">pending</a> |= ICSK_ACK_PUSHED;
<a name="L2523" href="source/net/ipv4/tcp.c#L2523">2523</a>                                 <a href="ident?i=tcp_cleanup_rbuf">tcp_cleanup_rbuf</a>(sk, 1);
<a name="L2524" href="source/net/ipv4/tcp.c#L2524">2524</a>                                 if (!(<a href="ident?i=val">val</a> &amp; 1))
<a name="L2525" href="source/net/ipv4/tcp.c#L2525">2525</a>                                         icsk-&gt;icsk_ack.pingpong = 1;
<a name="L2526" href="source/net/ipv4/tcp.c#L2526">2526</a>                         }
<a name="L2527" href="source/net/ipv4/tcp.c#L2527">2527</a>                 }
<a name="L2528" href="source/net/ipv4/tcp.c#L2528">2528</a>                 break;
<a name="L2529" href="source/net/ipv4/tcp.c#L2529">2529</a> 
<a name="L2530" href="source/net/ipv4/tcp.c#L2530">2530</a> #ifdef CONFIG_TCP_MD5SIG
<a name="L2531" href="source/net/ipv4/tcp.c#L2531">2531</a>         case <a href="ident?i=TCP_MD5SIG">TCP_MD5SIG</a>:
<a name="L2532" href="source/net/ipv4/tcp.c#L2532">2532</a>                 <b><i>/* Read the IP-&gt;Key mappings from userspace */</i></b>
<a name="L2533" href="source/net/ipv4/tcp.c#L2533">2533</a>                 <a href="ident?i=err">err</a> = <a href="ident?i=tp">tp</a>-&gt;af_specific-&gt;md5_parse(sk, optval, <a href="ident?i=optlen">optlen</a>);
<a name="L2534" href="source/net/ipv4/tcp.c#L2534">2534</a>                 break;
<a name="L2535" href="source/net/ipv4/tcp.c#L2535">2535</a> #endif
<a name="L2536" href="source/net/ipv4/tcp.c#L2536">2536</a>         case <a href="ident?i=TCP_USER_TIMEOUT">TCP_USER_TIMEOUT</a>:
<a name="L2537" href="source/net/ipv4/tcp.c#L2537">2537</a>                 <b><i>/* Cap the max time in ms TCP will retry or probe the window</i></b>
<a name="L2538" href="source/net/ipv4/tcp.c#L2538">2538</a> <b><i>                 * before giving up and aborting (ETIMEDOUT) a connection.</i></b>
<a name="L2539" href="source/net/ipv4/tcp.c#L2539">2539</a> <b><i>                 */</i></b>
<a name="L2540" href="source/net/ipv4/tcp.c#L2540">2540</a>                 if (<a href="ident?i=val">val</a> &lt; 0)
<a name="L2541" href="source/net/ipv4/tcp.c#L2541">2541</a>                         <a href="ident?i=err">err</a> = -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L2542" href="source/net/ipv4/tcp.c#L2542">2542</a>                 else
<a name="L2543" href="source/net/ipv4/tcp.c#L2543">2543</a>                         icsk-&gt;icsk_user_timeout = <a href="ident?i=msecs_to_jiffies">msecs_to_jiffies</a>(<a href="ident?i=val">val</a>);
<a name="L2544" href="source/net/ipv4/tcp.c#L2544">2544</a>                 break;
<a name="L2545" href="source/net/ipv4/tcp.c#L2545">2545</a> 
<a name="L2546" href="source/net/ipv4/tcp.c#L2546">2546</a>         case <a href="ident?i=TCP_FASTOPEN">TCP_FASTOPEN</a>:
<a name="L2547" href="source/net/ipv4/tcp.c#L2547">2547</a>                 if (<a href="ident?i=val">val</a> &gt;= 0 &amp;&amp; ((1 &lt;&lt; sk-&gt;<a href="ident?i=sk_state">sk_state</a>) &amp; (TCPF_CLOSE |
<a name="L2548" href="source/net/ipv4/tcp.c#L2548">2548</a>                     TCPF_LISTEN)))
<a name="L2549" href="source/net/ipv4/tcp.c#L2549">2549</a>                         <a href="ident?i=err">err</a> = <a href="ident?i=fastopen_init_queue">fastopen_init_queue</a>(sk, <a href="ident?i=val">val</a>);
<a name="L2550" href="source/net/ipv4/tcp.c#L2550">2550</a>                 else
<a name="L2551" href="source/net/ipv4/tcp.c#L2551">2551</a>                         <a href="ident?i=err">err</a> = -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L2552" href="source/net/ipv4/tcp.c#L2552">2552</a>                 break;
<a name="L2553" href="source/net/ipv4/tcp.c#L2553">2553</a>         case <a href="ident?i=TCP_TIMESTAMP">TCP_TIMESTAMP</a>:
<a name="L2554" href="source/net/ipv4/tcp.c#L2554">2554</a>                 if (!<a href="ident?i=tp">tp</a>-&gt;repair)
<a name="L2555" href="source/net/ipv4/tcp.c#L2555">2555</a>                         <a href="ident?i=err">err</a> = -<a href="ident?i=EPERM">EPERM</a>;
<a name="L2556" href="source/net/ipv4/tcp.c#L2556">2556</a>                 else
<a name="L2557" href="source/net/ipv4/tcp.c#L2557">2557</a>                         <a href="ident?i=tp">tp</a>-&gt;tsoffset = <a href="ident?i=val">val</a> - <a href="ident?i=tcp_time_stamp">tcp_time_stamp</a>;
<a name="L2558" href="source/net/ipv4/tcp.c#L2558">2558</a>                 break;
<a name="L2559" href="source/net/ipv4/tcp.c#L2559">2559</a>         case <a href="ident?i=TCP_NOTSENT_LOWAT">TCP_NOTSENT_LOWAT</a>:
<a name="L2560" href="source/net/ipv4/tcp.c#L2560">2560</a>                 <a href="ident?i=tp">tp</a>-&gt;notsent_lowat = <a href="ident?i=val">val</a>;
<a name="L2561" href="source/net/ipv4/tcp.c#L2561">2561</a>                 sk-&gt;sk_write_space(sk);
<a name="L2562" href="source/net/ipv4/tcp.c#L2562">2562</a>                 break;
<a name="L2563" href="source/net/ipv4/tcp.c#L2563">2563</a>         default:
<a name="L2564" href="source/net/ipv4/tcp.c#L2564">2564</a>                 <a href="ident?i=err">err</a> = -<a href="ident?i=ENOPROTOOPT">ENOPROTOOPT</a>;
<a name="L2565" href="source/net/ipv4/tcp.c#L2565">2565</a>                 break;
<a name="L2566" href="source/net/ipv4/tcp.c#L2566">2566</a>         }
<a name="L2567" href="source/net/ipv4/tcp.c#L2567">2567</a> 
<a name="L2568" href="source/net/ipv4/tcp.c#L2568">2568</a>         <a href="ident?i=release_sock">release_sock</a>(sk);
<a name="L2569" href="source/net/ipv4/tcp.c#L2569">2569</a>         return <a href="ident?i=err">err</a>;
<a name="L2570" href="source/net/ipv4/tcp.c#L2570">2570</a> }
<a name="L2571" href="source/net/ipv4/tcp.c#L2571">2571</a> 
<a name="L2572" href="source/net/ipv4/tcp.c#L2572">2572</a> int <a href="ident?i=tcp_setsockopt">tcp_setsockopt</a>(struct <a href="ident?i=sock">sock</a> *sk, int <a href="ident?i=level">level</a>, int optname, char <a href="ident?i=__user">__user</a> *optval,
<a name="L2573" href="source/net/ipv4/tcp.c#L2573">2573</a>                    unsigned int <a href="ident?i=optlen">optlen</a>)
<a name="L2574" href="source/net/ipv4/tcp.c#L2574">2574</a> {
<a name="L2575" href="source/net/ipv4/tcp.c#L2575">2575</a>         const struct <a href="ident?i=inet_connection_sock">inet_connection_sock</a> *icsk = <a href="ident?i=inet_csk">inet_csk</a>(sk);
<a name="L2576" href="source/net/ipv4/tcp.c#L2576">2576</a> 
<a name="L2577" href="source/net/ipv4/tcp.c#L2577">2577</a>         if (<a href="ident?i=level">level</a> != <a href="ident?i=SOL_TCP">SOL_TCP</a>)
<a name="L2578" href="source/net/ipv4/tcp.c#L2578">2578</a>                 return icsk-&gt;icsk_af_ops-&gt;<a href="ident?i=setsockopt">setsockopt</a>(sk, <a href="ident?i=level">level</a>, optname,
<a name="L2579" href="source/net/ipv4/tcp.c#L2579">2579</a>                                                      optval, <a href="ident?i=optlen">optlen</a>);
<a name="L2580" href="source/net/ipv4/tcp.c#L2580">2580</a>         return <a href="ident?i=do_tcp_setsockopt">do_tcp_setsockopt</a>(sk, <a href="ident?i=level">level</a>, optname, optval, <a href="ident?i=optlen">optlen</a>);
<a name="L2581" href="source/net/ipv4/tcp.c#L2581">2581</a> }
<a name="L2582" href="source/net/ipv4/tcp.c#L2582">2582</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=tcp_setsockopt">tcp_setsockopt</a>);
<a name="L2583" href="source/net/ipv4/tcp.c#L2583">2583</a> 
<a name="L2584" href="source/net/ipv4/tcp.c#L2584">2584</a> #ifdef CONFIG_COMPAT
<a name="L2585" href="source/net/ipv4/tcp.c#L2585">2585</a> int <a href="ident?i=compat_tcp_setsockopt">compat_tcp_setsockopt</a>(struct <a href="ident?i=sock">sock</a> *sk, int <a href="ident?i=level">level</a>, int optname,
<a name="L2586" href="source/net/ipv4/tcp.c#L2586">2586</a>                           char <a href="ident?i=__user">__user</a> *optval, unsigned int <a href="ident?i=optlen">optlen</a>)
<a name="L2587" href="source/net/ipv4/tcp.c#L2587">2587</a> {
<a name="L2588" href="source/net/ipv4/tcp.c#L2588">2588</a>         if (<a href="ident?i=level">level</a> != <a href="ident?i=SOL_TCP">SOL_TCP</a>)
<a name="L2589" href="source/net/ipv4/tcp.c#L2589">2589</a>                 return <a href="ident?i=inet_csk_compat_setsockopt">inet_csk_compat_setsockopt</a>(sk, <a href="ident?i=level">level</a>, optname,
<a name="L2590" href="source/net/ipv4/tcp.c#L2590">2590</a>                                                   optval, <a href="ident?i=optlen">optlen</a>);
<a name="L2591" href="source/net/ipv4/tcp.c#L2591">2591</a>         return <a href="ident?i=do_tcp_setsockopt">do_tcp_setsockopt</a>(sk, <a href="ident?i=level">level</a>, optname, optval, <a href="ident?i=optlen">optlen</a>);
<a name="L2592" href="source/net/ipv4/tcp.c#L2592">2592</a> }
<a name="L2593" href="source/net/ipv4/tcp.c#L2593">2593</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=compat_tcp_setsockopt">compat_tcp_setsockopt</a>);
<a name="L2594" href="source/net/ipv4/tcp.c#L2594">2594</a> #endif
<a name="L2595" href="source/net/ipv4/tcp.c#L2595">2595</a> 
<a name="L2596" href="source/net/ipv4/tcp.c#L2596">2596</a> <b><i>/* Return information about state of tcp endpoint in API format. */</i></b>
<a name="L2597" href="source/net/ipv4/tcp.c#L2597">2597</a> void <a href="ident?i=tcp_get_info">tcp_get_info</a>(struct <a href="ident?i=sock">sock</a> *sk, struct <a href="ident?i=tcp_info">tcp_info</a> *<a href="ident?i=info">info</a>)
<a name="L2598" href="source/net/ipv4/tcp.c#L2598">2598</a> {
<a name="L2599" href="source/net/ipv4/tcp.c#L2599">2599</a>         const struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L2600" href="source/net/ipv4/tcp.c#L2600">2600</a>         const struct <a href="ident?i=inet_connection_sock">inet_connection_sock</a> *icsk = <a href="ident?i=inet_csk">inet_csk</a>(sk);
<a name="L2601" href="source/net/ipv4/tcp.c#L2601">2601</a>         <a href="ident?i=u32">u32</a> <a href="ident?i=now">now</a> = <a href="ident?i=tcp_time_stamp">tcp_time_stamp</a>;
<a name="L2602" href="source/net/ipv4/tcp.c#L2602">2602</a>         unsigned int <a href="ident?i=start">start</a>;
<a name="L2603" href="source/net/ipv4/tcp.c#L2603">2603</a>         <a href="ident?i=u32">u32</a> <a href="ident?i=rate">rate</a>;
<a name="L2604" href="source/net/ipv4/tcp.c#L2604">2604</a> 
<a name="L2605" href="source/net/ipv4/tcp.c#L2605">2605</a>         <a href="ident?i=memset">memset</a>(<a href="ident?i=info">info</a>, 0, sizeof(*<a href="ident?i=info">info</a>));
<a name="L2606" href="source/net/ipv4/tcp.c#L2606">2606</a> 
<a name="L2607" href="source/net/ipv4/tcp.c#L2607">2607</a>         <a href="ident?i=info">info</a>-&gt;tcpi_state = sk-&gt;<a href="ident?i=sk_state">sk_state</a>;
<a name="L2608" href="source/net/ipv4/tcp.c#L2608">2608</a>         <a href="ident?i=info">info</a>-&gt;tcpi_ca_state = icsk-&gt;icsk_ca_state;
<a name="L2609" href="source/net/ipv4/tcp.c#L2609">2609</a>         <a href="ident?i=info">info</a>-&gt;tcpi_retransmits = icsk-&gt;icsk_retransmits;
<a name="L2610" href="source/net/ipv4/tcp.c#L2610">2610</a>         <a href="ident?i=info">info</a>-&gt;tcpi_probes = icsk-&gt;icsk_probes_out;
<a name="L2611" href="source/net/ipv4/tcp.c#L2611">2611</a>         <a href="ident?i=info">info</a>-&gt;tcpi_backoff = icsk-&gt;icsk_backoff;
<a name="L2612" href="source/net/ipv4/tcp.c#L2612">2612</a> 
<a name="L2613" href="source/net/ipv4/tcp.c#L2613">2613</a>         if (<a href="ident?i=tp">tp</a>-&gt;rx_opt.tstamp_ok)
<a name="L2614" href="source/net/ipv4/tcp.c#L2614">2614</a>                 <a href="ident?i=info">info</a>-&gt;tcpi_options |= <a href="ident?i=TCPI_OPT_TIMESTAMPS">TCPI_OPT_TIMESTAMPS</a>;
<a name="L2615" href="source/net/ipv4/tcp.c#L2615">2615</a>         if (<a href="ident?i=tcp_is_sack">tcp_is_sack</a>(<a href="ident?i=tp">tp</a>))
<a name="L2616" href="source/net/ipv4/tcp.c#L2616">2616</a>                 <a href="ident?i=info">info</a>-&gt;tcpi_options |= <a href="ident?i=TCPI_OPT_SACK">TCPI_OPT_SACK</a>;
<a name="L2617" href="source/net/ipv4/tcp.c#L2617">2617</a>         if (<a href="ident?i=tp">tp</a>-&gt;rx_opt.wscale_ok) {
<a name="L2618" href="source/net/ipv4/tcp.c#L2618">2618</a>                 <a href="ident?i=info">info</a>-&gt;tcpi_options |= <a href="ident?i=TCPI_OPT_WSCALE">TCPI_OPT_WSCALE</a>;
<a name="L2619" href="source/net/ipv4/tcp.c#L2619">2619</a>                 <a href="ident?i=info">info</a>-&gt;tcpi_snd_wscale = <a href="ident?i=tp">tp</a>-&gt;rx_opt.snd_wscale;
<a name="L2620" href="source/net/ipv4/tcp.c#L2620">2620</a>                 <a href="ident?i=info">info</a>-&gt;tcpi_rcv_wscale = <a href="ident?i=tp">tp</a>-&gt;rx_opt.rcv_wscale;
<a name="L2621" href="source/net/ipv4/tcp.c#L2621">2621</a>         }
<a name="L2622" href="source/net/ipv4/tcp.c#L2622">2622</a> 
<a name="L2623" href="source/net/ipv4/tcp.c#L2623">2623</a>         if (<a href="ident?i=tp">tp</a>-&gt;ecn_flags &amp; <a href="ident?i=TCP_ECN_OK">TCP_ECN_OK</a>)
<a name="L2624" href="source/net/ipv4/tcp.c#L2624">2624</a>                 <a href="ident?i=info">info</a>-&gt;tcpi_options |= <a href="ident?i=TCPI_OPT_ECN">TCPI_OPT_ECN</a>;
<a name="L2625" href="source/net/ipv4/tcp.c#L2625">2625</a>         if (<a href="ident?i=tp">tp</a>-&gt;ecn_flags &amp; <a href="ident?i=TCP_ECN_SEEN">TCP_ECN_SEEN</a>)
<a name="L2626" href="source/net/ipv4/tcp.c#L2626">2626</a>                 <a href="ident?i=info">info</a>-&gt;tcpi_options |= <a href="ident?i=TCPI_OPT_ECN_SEEN">TCPI_OPT_ECN_SEEN</a>;
<a name="L2627" href="source/net/ipv4/tcp.c#L2627">2627</a>         if (<a href="ident?i=tp">tp</a>-&gt;syn_data_acked)
<a name="L2628" href="source/net/ipv4/tcp.c#L2628">2628</a>                 <a href="ident?i=info">info</a>-&gt;tcpi_options |= <a href="ident?i=TCPI_OPT_SYN_DATA">TCPI_OPT_SYN_DATA</a>;
<a name="L2629" href="source/net/ipv4/tcp.c#L2629">2629</a> 
<a name="L2630" href="source/net/ipv4/tcp.c#L2630">2630</a>         <a href="ident?i=info">info</a>-&gt;tcpi_rto = <a href="ident?i=jiffies_to_usecs">jiffies_to_usecs</a>(icsk-&gt;icsk_rto);
<a name="L2631" href="source/net/ipv4/tcp.c#L2631">2631</a>         <a href="ident?i=info">info</a>-&gt;tcpi_ato = <a href="ident?i=jiffies_to_usecs">jiffies_to_usecs</a>(icsk-&gt;icsk_ack.ato);
<a name="L2632" href="source/net/ipv4/tcp.c#L2632">2632</a>         <a href="ident?i=info">info</a>-&gt;tcpi_snd_mss = <a href="ident?i=tp">tp</a>-&gt;mss_cache;
<a name="L2633" href="source/net/ipv4/tcp.c#L2633">2633</a>         <a href="ident?i=info">info</a>-&gt;tcpi_rcv_mss = icsk-&gt;icsk_ack.rcv_mss;
<a name="L2634" href="source/net/ipv4/tcp.c#L2634">2634</a> 
<a name="L2635" href="source/net/ipv4/tcp.c#L2635">2635</a>         if (sk-&gt;<a href="ident?i=sk_state">sk_state</a> == TCP_LISTEN) {
<a name="L2636" href="source/net/ipv4/tcp.c#L2636">2636</a>                 <a href="ident?i=info">info</a>-&gt;tcpi_unacked = sk-&gt;sk_ack_backlog;
<a name="L2637" href="source/net/ipv4/tcp.c#L2637">2637</a>                 <a href="ident?i=info">info</a>-&gt;tcpi_sacked = sk-&gt;sk_max_ack_backlog;
<a name="L2638" href="source/net/ipv4/tcp.c#L2638">2638</a>         } else {
<a name="L2639" href="source/net/ipv4/tcp.c#L2639">2639</a>                 <a href="ident?i=info">info</a>-&gt;tcpi_unacked = <a href="ident?i=tp">tp</a>-&gt;packets_out;
<a name="L2640" href="source/net/ipv4/tcp.c#L2640">2640</a>                 <a href="ident?i=info">info</a>-&gt;tcpi_sacked = <a href="ident?i=tp">tp</a>-&gt;sacked_out;
<a name="L2641" href="source/net/ipv4/tcp.c#L2641">2641</a>         }
<a name="L2642" href="source/net/ipv4/tcp.c#L2642">2642</a>         <a href="ident?i=info">info</a>-&gt;tcpi_lost = <a href="ident?i=tp">tp</a>-&gt;lost_out;
<a name="L2643" href="source/net/ipv4/tcp.c#L2643">2643</a>         <a href="ident?i=info">info</a>-&gt;tcpi_retrans = <a href="ident?i=tp">tp</a>-&gt;retrans_out;
<a name="L2644" href="source/net/ipv4/tcp.c#L2644">2644</a>         <a href="ident?i=info">info</a>-&gt;tcpi_fackets = <a href="ident?i=tp">tp</a>-&gt;fackets_out;
<a name="L2645" href="source/net/ipv4/tcp.c#L2645">2645</a> 
<a name="L2646" href="source/net/ipv4/tcp.c#L2646">2646</a>         <a href="ident?i=info">info</a>-&gt;tcpi_last_data_sent = <a href="ident?i=jiffies_to_msecs">jiffies_to_msecs</a>(<a href="ident?i=now">now</a> - <a href="ident?i=tp">tp</a>-&gt;lsndtime);
<a name="L2647" href="source/net/ipv4/tcp.c#L2647">2647</a>         <a href="ident?i=info">info</a>-&gt;tcpi_last_data_recv = <a href="ident?i=jiffies_to_msecs">jiffies_to_msecs</a>(<a href="ident?i=now">now</a> - icsk-&gt;icsk_ack.lrcvtime);
<a name="L2648" href="source/net/ipv4/tcp.c#L2648">2648</a>         <a href="ident?i=info">info</a>-&gt;tcpi_last_ack_recv = <a href="ident?i=jiffies_to_msecs">jiffies_to_msecs</a>(<a href="ident?i=now">now</a> - <a href="ident?i=tp">tp</a>-&gt;rcv_tstamp);
<a name="L2649" href="source/net/ipv4/tcp.c#L2649">2649</a> 
<a name="L2650" href="source/net/ipv4/tcp.c#L2650">2650</a>         <a href="ident?i=info">info</a>-&gt;tcpi_pmtu = icsk-&gt;icsk_pmtu_cookie;
<a name="L2651" href="source/net/ipv4/tcp.c#L2651">2651</a>         <a href="ident?i=info">info</a>-&gt;tcpi_rcv_ssthresh = <a href="ident?i=tp">tp</a>-&gt;rcv_ssthresh;
<a name="L2652" href="source/net/ipv4/tcp.c#L2652">2652</a>         <a href="ident?i=info">info</a>-&gt;tcpi_rtt = <a href="ident?i=tp">tp</a>-&gt;srtt_us &gt;&gt; 3;
<a name="L2653" href="source/net/ipv4/tcp.c#L2653">2653</a>         <a href="ident?i=info">info</a>-&gt;tcpi_rttvar = <a href="ident?i=tp">tp</a>-&gt;mdev_us &gt;&gt; 2;
<a name="L2654" href="source/net/ipv4/tcp.c#L2654">2654</a>         <a href="ident?i=info">info</a>-&gt;tcpi_snd_ssthresh = <a href="ident?i=tp">tp</a>-&gt;snd_ssthresh;
<a name="L2655" href="source/net/ipv4/tcp.c#L2655">2655</a>         <a href="ident?i=info">info</a>-&gt;tcpi_snd_cwnd = <a href="ident?i=tp">tp</a>-&gt;snd_cwnd;
<a name="L2656" href="source/net/ipv4/tcp.c#L2656">2656</a>         <a href="ident?i=info">info</a>-&gt;tcpi_advmss = <a href="ident?i=tp">tp</a>-&gt;advmss;
<a name="L2657" href="source/net/ipv4/tcp.c#L2657">2657</a>         <a href="ident?i=info">info</a>-&gt;tcpi_reordering = <a href="ident?i=tp">tp</a>-&gt;reordering;
<a name="L2658" href="source/net/ipv4/tcp.c#L2658">2658</a> 
<a name="L2659" href="source/net/ipv4/tcp.c#L2659">2659</a>         <a href="ident?i=info">info</a>-&gt;tcpi_rcv_rtt = <a href="ident?i=jiffies_to_usecs">jiffies_to_usecs</a>(<a href="ident?i=tp">tp</a>-&gt;rcv_rtt_est.rtt)&gt;&gt;3;
<a name="L2660" href="source/net/ipv4/tcp.c#L2660">2660</a>         <a href="ident?i=info">info</a>-&gt;tcpi_rcv_space = <a href="ident?i=tp">tp</a>-&gt;rcvq_space.<a href="ident?i=space">space</a>;
<a name="L2661" href="source/net/ipv4/tcp.c#L2661">2661</a> 
<a name="L2662" href="source/net/ipv4/tcp.c#L2662">2662</a>         <a href="ident?i=info">info</a>-&gt;tcpi_total_retrans = <a href="ident?i=tp">tp</a>-&gt;total_retrans;
<a name="L2663" href="source/net/ipv4/tcp.c#L2663">2663</a> 
<a name="L2664" href="source/net/ipv4/tcp.c#L2664">2664</a>         <a href="ident?i=rate">rate</a> = <a href="ident?i=READ_ONCE">READ_ONCE</a>(sk-&gt;sk_pacing_rate);
<a name="L2665" href="source/net/ipv4/tcp.c#L2665">2665</a>         <a href="ident?i=info">info</a>-&gt;tcpi_pacing_rate = <a href="ident?i=rate">rate</a> != ~0U ? <a href="ident?i=rate">rate</a> : ~0ULL;
<a name="L2666" href="source/net/ipv4/tcp.c#L2666">2666</a> 
<a name="L2667" href="source/net/ipv4/tcp.c#L2667">2667</a>         <a href="ident?i=rate">rate</a> = <a href="ident?i=READ_ONCE">READ_ONCE</a>(sk-&gt;sk_max_pacing_rate);
<a name="L2668" href="source/net/ipv4/tcp.c#L2668">2668</a>         <a href="ident?i=info">info</a>-&gt;tcpi_max_pacing_rate = <a href="ident?i=rate">rate</a> != ~0U ? <a href="ident?i=rate">rate</a> : ~0ULL;
<a name="L2669" href="source/net/ipv4/tcp.c#L2669">2669</a> 
<a name="L2670" href="source/net/ipv4/tcp.c#L2670">2670</a>         do {
<a name="L2671" href="source/net/ipv4/tcp.c#L2671">2671</a>                 <a href="ident?i=start">start</a> = <a href="ident?i=u64_stats_fetch_begin_irq">u64_stats_fetch_begin_irq</a>(&amp;<a href="ident?i=tp">tp</a>-&gt;syncp);
<a name="L2672" href="source/net/ipv4/tcp.c#L2672">2672</a>                 <a href="ident?i=info">info</a>-&gt;tcpi_bytes_acked = <a href="ident?i=tp">tp</a>-&gt;bytes_acked;
<a name="L2673" href="source/net/ipv4/tcp.c#L2673">2673</a>                 <a href="ident?i=info">info</a>-&gt;tcpi_bytes_received = <a href="ident?i=tp">tp</a>-&gt;bytes_received;
<a name="L2674" href="source/net/ipv4/tcp.c#L2674">2674</a>         } while (<a href="ident?i=u64_stats_fetch_retry_irq">u64_stats_fetch_retry_irq</a>(&amp;<a href="ident?i=tp">tp</a>-&gt;syncp, <a href="ident?i=start">start</a>));
<a name="L2675" href="source/net/ipv4/tcp.c#L2675">2675</a> }
<a name="L2676" href="source/net/ipv4/tcp.c#L2676">2676</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=tcp_get_info">tcp_get_info</a>);
<a name="L2677" href="source/net/ipv4/tcp.c#L2677">2677</a> 
<a name="L2678" href="source/net/ipv4/tcp.c#L2678">2678</a> static int <a href="ident?i=do_tcp_getsockopt">do_tcp_getsockopt</a>(struct <a href="ident?i=sock">sock</a> *sk, int <a href="ident?i=level">level</a>,
<a name="L2679" href="source/net/ipv4/tcp.c#L2679">2679</a>                 int optname, char <a href="ident?i=__user">__user</a> *optval, int <a href="ident?i=__user">__user</a> *<a href="ident?i=optlen">optlen</a>)
<a name="L2680" href="source/net/ipv4/tcp.c#L2680">2680</a> {
<a name="L2681" href="source/net/ipv4/tcp.c#L2681">2681</a>         struct <a href="ident?i=inet_connection_sock">inet_connection_sock</a> *icsk = <a href="ident?i=inet_csk">inet_csk</a>(sk);
<a name="L2682" href="source/net/ipv4/tcp.c#L2682">2682</a>         struct <a href="ident?i=tcp_sock">tcp_sock</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk);
<a name="L2683" href="source/net/ipv4/tcp.c#L2683">2683</a>         int <a href="ident?i=val">val</a>, <a href="ident?i=len">len</a>;
<a name="L2684" href="source/net/ipv4/tcp.c#L2684">2684</a> 
<a name="L2685" href="source/net/ipv4/tcp.c#L2685">2685</a>         if (<a href="ident?i=get_user">get_user</a>(<a href="ident?i=len">len</a>, <a href="ident?i=optlen">optlen</a>))
<a name="L2686" href="source/net/ipv4/tcp.c#L2686">2686</a>                 return -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L2687" href="source/net/ipv4/tcp.c#L2687">2687</a> 
<a name="L2688" href="source/net/ipv4/tcp.c#L2688">2688</a>         <a href="ident?i=len">len</a> = <a href="ident?i=min_t">min_t</a>(unsigned int, <a href="ident?i=len">len</a>, sizeof(int));
<a name="L2689" href="source/net/ipv4/tcp.c#L2689">2689</a> 
<a name="L2690" href="source/net/ipv4/tcp.c#L2690">2690</a>         if (<a href="ident?i=len">len</a> &lt; 0)
<a name="L2691" href="source/net/ipv4/tcp.c#L2691">2691</a>                 return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L2692" href="source/net/ipv4/tcp.c#L2692">2692</a> 
<a name="L2693" href="source/net/ipv4/tcp.c#L2693">2693</a>         switch (optname) {
<a name="L2694" href="source/net/ipv4/tcp.c#L2694">2694</a>         case <a href="ident?i=TCP_MAXSEG">TCP_MAXSEG</a>:
<a name="L2695" href="source/net/ipv4/tcp.c#L2695">2695</a>                 <a href="ident?i=val">val</a> = <a href="ident?i=tp">tp</a>-&gt;mss_cache;
<a name="L2696" href="source/net/ipv4/tcp.c#L2696">2696</a>                 if (!<a href="ident?i=val">val</a> &amp;&amp; ((1 &lt;&lt; sk-&gt;<a href="ident?i=sk_state">sk_state</a>) &amp; (TCPF_CLOSE | TCPF_LISTEN)))
<a name="L2697" href="source/net/ipv4/tcp.c#L2697">2697</a>                         <a href="ident?i=val">val</a> = <a href="ident?i=tp">tp</a>-&gt;rx_opt.user_mss;
<a name="L2698" href="source/net/ipv4/tcp.c#L2698">2698</a>                 if (<a href="ident?i=tp">tp</a>-&gt;repair)
<a name="L2699" href="source/net/ipv4/tcp.c#L2699">2699</a>                         <a href="ident?i=val">val</a> = <a href="ident?i=tp">tp</a>-&gt;rx_opt.mss_clamp;
<a name="L2700" href="source/net/ipv4/tcp.c#L2700">2700</a>                 break;
<a name="L2701" href="source/net/ipv4/tcp.c#L2701">2701</a>         case <a href="ident?i=TCP_NODELAY">TCP_NODELAY</a>:
<a name="L2702" href="source/net/ipv4/tcp.c#L2702">2702</a>                 <a href="ident?i=val">val</a> = !!(<a href="ident?i=tp">tp</a>-&gt;nonagle&amp;<a href="ident?i=TCP_NAGLE_OFF">TCP_NAGLE_OFF</a>);
<a name="L2703" href="source/net/ipv4/tcp.c#L2703">2703</a>                 break;
<a name="L2704" href="source/net/ipv4/tcp.c#L2704">2704</a>         case <a href="ident?i=TCP_CORK">TCP_CORK</a>:
<a name="L2705" href="source/net/ipv4/tcp.c#L2705">2705</a>                 <a href="ident?i=val">val</a> = !!(<a href="ident?i=tp">tp</a>-&gt;nonagle&amp;<a href="ident?i=TCP_NAGLE_CORK">TCP_NAGLE_CORK</a>);
<a name="L2706" href="source/net/ipv4/tcp.c#L2706">2706</a>                 break;
<a name="L2707" href="source/net/ipv4/tcp.c#L2707">2707</a>         case <a href="ident?i=TCP_KEEPIDLE">TCP_KEEPIDLE</a>:
<a name="L2708" href="source/net/ipv4/tcp.c#L2708">2708</a>                 <a href="ident?i=val">val</a> = <a href="ident?i=keepalive_time_when">keepalive_time_when</a>(<a href="ident?i=tp">tp</a>) / <a href="ident?i=HZ">HZ</a>;
<a name="L2709" href="source/net/ipv4/tcp.c#L2709">2709</a>                 break;
<a name="L2710" href="source/net/ipv4/tcp.c#L2710">2710</a>         case <a href="ident?i=TCP_KEEPINTVL">TCP_KEEPINTVL</a>:
<a name="L2711" href="source/net/ipv4/tcp.c#L2711">2711</a>                 <a href="ident?i=val">val</a> = <a href="ident?i=keepalive_intvl_when">keepalive_intvl_when</a>(<a href="ident?i=tp">tp</a>) / <a href="ident?i=HZ">HZ</a>;
<a name="L2712" href="source/net/ipv4/tcp.c#L2712">2712</a>                 break;
<a name="L2713" href="source/net/ipv4/tcp.c#L2713">2713</a>         case <a href="ident?i=TCP_KEEPCNT">TCP_KEEPCNT</a>:
<a name="L2714" href="source/net/ipv4/tcp.c#L2714">2714</a>                 <a href="ident?i=val">val</a> = <a href="ident?i=keepalive_probes">keepalive_probes</a>(<a href="ident?i=tp">tp</a>);
<a name="L2715" href="source/net/ipv4/tcp.c#L2715">2715</a>                 break;
<a name="L2716" href="source/net/ipv4/tcp.c#L2716">2716</a>         case <a href="ident?i=TCP_SYNCNT">TCP_SYNCNT</a>:
<a name="L2717" href="source/net/ipv4/tcp.c#L2717">2717</a>                 <a href="ident?i=val">val</a> = icsk-&gt;icsk_syn_retries ? : <a href="ident?i=sysctl_tcp_syn_retries">sysctl_tcp_syn_retries</a>;
<a name="L2718" href="source/net/ipv4/tcp.c#L2718">2718</a>                 break;
<a name="L2719" href="source/net/ipv4/tcp.c#L2719">2719</a>         case <a href="ident?i=TCP_LINGER2">TCP_LINGER2</a>:
<a name="L2720" href="source/net/ipv4/tcp.c#L2720">2720</a>                 <a href="ident?i=val">val</a> = <a href="ident?i=tp">tp</a>-&gt;linger2;
<a name="L2721" href="source/net/ipv4/tcp.c#L2721">2721</a>                 if (<a href="ident?i=val">val</a> &gt;= 0)
<a name="L2722" href="source/net/ipv4/tcp.c#L2722">2722</a>                         <a href="ident?i=val">val</a> = (<a href="ident?i=val">val</a> ? : <a href="ident?i=sysctl_tcp_fin_timeout">sysctl_tcp_fin_timeout</a>) / <a href="ident?i=HZ">HZ</a>;
<a name="L2723" href="source/net/ipv4/tcp.c#L2723">2723</a>                 break;
<a name="L2724" href="source/net/ipv4/tcp.c#L2724">2724</a>         case <a href="ident?i=TCP_DEFER_ACCEPT">TCP_DEFER_ACCEPT</a>:
<a name="L2725" href="source/net/ipv4/tcp.c#L2725">2725</a>                 <a href="ident?i=val">val</a> = <a href="ident?i=retrans_to_secs">retrans_to_secs</a>(icsk-&gt;icsk_accept_queue.rskq_defer_accept,
<a name="L2726" href="source/net/ipv4/tcp.c#L2726">2726</a>                                       <a href="ident?i=TCP_TIMEOUT_INIT">TCP_TIMEOUT_INIT</a> / <a href="ident?i=HZ">HZ</a>, <a href="ident?i=TCP_RTO_MAX">TCP_RTO_MAX</a> / <a href="ident?i=HZ">HZ</a>);
<a name="L2727" href="source/net/ipv4/tcp.c#L2727">2727</a>                 break;
<a name="L2728" href="source/net/ipv4/tcp.c#L2728">2728</a>         case <a href="ident?i=TCP_WINDOW_CLAMP">TCP_WINDOW_CLAMP</a>:
<a name="L2729" href="source/net/ipv4/tcp.c#L2729">2729</a>                 <a href="ident?i=val">val</a> = <a href="ident?i=tp">tp</a>-&gt;window_clamp;
<a name="L2730" href="source/net/ipv4/tcp.c#L2730">2730</a>                 break;
<a name="L2731" href="source/net/ipv4/tcp.c#L2731">2731</a>         case <a href="ident?i=TCP_INFO">TCP_INFO</a>: {
<a name="L2732" href="source/net/ipv4/tcp.c#L2732">2732</a>                 struct <a href="ident?i=tcp_info">tcp_info</a> <a href="ident?i=info">info</a>;
<a name="L2733" href="source/net/ipv4/tcp.c#L2733">2733</a> 
<a name="L2734" href="source/net/ipv4/tcp.c#L2734">2734</a>                 if (<a href="ident?i=get_user">get_user</a>(<a href="ident?i=len">len</a>, <a href="ident?i=optlen">optlen</a>))
<a name="L2735" href="source/net/ipv4/tcp.c#L2735">2735</a>                         return -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L2736" href="source/net/ipv4/tcp.c#L2736">2736</a> 
<a name="L2737" href="source/net/ipv4/tcp.c#L2737">2737</a>                 <a href="ident?i=tcp_get_info">tcp_get_info</a>(sk, &amp;<a href="ident?i=info">info</a>);
<a name="L2738" href="source/net/ipv4/tcp.c#L2738">2738</a> 
<a name="L2739" href="source/net/ipv4/tcp.c#L2739">2739</a>                 <a href="ident?i=len">len</a> = <a href="ident?i=min_t">min_t</a>(unsigned int, <a href="ident?i=len">len</a>, sizeof(<a href="ident?i=info">info</a>));
<a name="L2740" href="source/net/ipv4/tcp.c#L2740">2740</a>                 if (<a href="ident?i=put_user">put_user</a>(<a href="ident?i=len">len</a>, <a href="ident?i=optlen">optlen</a>))
<a name="L2741" href="source/net/ipv4/tcp.c#L2741">2741</a>                         return -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L2742" href="source/net/ipv4/tcp.c#L2742">2742</a>                 if (<a href="ident?i=copy_to_user">copy_to_user</a>(optval, &amp;<a href="ident?i=info">info</a>, <a href="ident?i=len">len</a>))
<a name="L2743" href="source/net/ipv4/tcp.c#L2743">2743</a>                         return -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L2744" href="source/net/ipv4/tcp.c#L2744">2744</a>                 return 0;
<a name="L2745" href="source/net/ipv4/tcp.c#L2745">2745</a>         }
<a name="L2746" href="source/net/ipv4/tcp.c#L2746">2746</a>         case <a href="ident?i=TCP_CC_INFO">TCP_CC_INFO</a>: {
<a name="L2747" href="source/net/ipv4/tcp.c#L2747">2747</a>                 const struct <a href="ident?i=tcp_congestion_ops">tcp_congestion_ops</a> *ca_ops;
<a name="L2748" href="source/net/ipv4/tcp.c#L2748">2748</a>                 union <a href="ident?i=tcp_cc_info">tcp_cc_info</a> <a href="ident?i=info">info</a>;
<a name="L2749" href="source/net/ipv4/tcp.c#L2749">2749</a>                 <a href="ident?i=size_t">size_t</a> sz = 0;
<a name="L2750" href="source/net/ipv4/tcp.c#L2750">2750</a>                 int <a href="ident?i=attr">attr</a>;
<a name="L2751" href="source/net/ipv4/tcp.c#L2751">2751</a> 
<a name="L2752" href="source/net/ipv4/tcp.c#L2752">2752</a>                 if (<a href="ident?i=get_user">get_user</a>(<a href="ident?i=len">len</a>, <a href="ident?i=optlen">optlen</a>))
<a name="L2753" href="source/net/ipv4/tcp.c#L2753">2753</a>                         return -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L2754" href="source/net/ipv4/tcp.c#L2754">2754</a> 
<a name="L2755" href="source/net/ipv4/tcp.c#L2755">2755</a>                 ca_ops = icsk-&gt;icsk_ca_ops;
<a name="L2756" href="source/net/ipv4/tcp.c#L2756">2756</a>                 if (ca_ops &amp;&amp; ca_ops-&gt;<a href="ident?i=get_info">get_info</a>)
<a name="L2757" href="source/net/ipv4/tcp.c#L2757">2757</a>                         sz = ca_ops-&gt;<a href="ident?i=get_info">get_info</a>(sk, ~0U, &amp;<a href="ident?i=attr">attr</a>, &amp;<a href="ident?i=info">info</a>);
<a name="L2758" href="source/net/ipv4/tcp.c#L2758">2758</a> 
<a name="L2759" href="source/net/ipv4/tcp.c#L2759">2759</a>                 <a href="ident?i=len">len</a> = <a href="ident?i=min_t">min_t</a>(unsigned int, <a href="ident?i=len">len</a>, sz);
<a name="L2760" href="source/net/ipv4/tcp.c#L2760">2760</a>                 if (<a href="ident?i=put_user">put_user</a>(<a href="ident?i=len">len</a>, <a href="ident?i=optlen">optlen</a>))
<a name="L2761" href="source/net/ipv4/tcp.c#L2761">2761</a>                         return -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L2762" href="source/net/ipv4/tcp.c#L2762">2762</a>                 if (<a href="ident?i=copy_to_user">copy_to_user</a>(optval, &amp;<a href="ident?i=info">info</a>, <a href="ident?i=len">len</a>))
<a name="L2763" href="source/net/ipv4/tcp.c#L2763">2763</a>                         return -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L2764" href="source/net/ipv4/tcp.c#L2764">2764</a>                 return 0;
<a name="L2765" href="source/net/ipv4/tcp.c#L2765">2765</a>         }
<a name="L2766" href="source/net/ipv4/tcp.c#L2766">2766</a>         case <a href="ident?i=TCP_QUICKACK">TCP_QUICKACK</a>:
<a name="L2767" href="source/net/ipv4/tcp.c#L2767">2767</a>                 <a href="ident?i=val">val</a> = !icsk-&gt;icsk_ack.pingpong;
<a name="L2768" href="source/net/ipv4/tcp.c#L2768">2768</a>                 break;
<a name="L2769" href="source/net/ipv4/tcp.c#L2769">2769</a> 
<a name="L2770" href="source/net/ipv4/tcp.c#L2770">2770</a>         case <a href="ident?i=TCP_CONGESTION">TCP_CONGESTION</a>:
<a name="L2771" href="source/net/ipv4/tcp.c#L2771">2771</a>                 if (<a href="ident?i=get_user">get_user</a>(<a href="ident?i=len">len</a>, <a href="ident?i=optlen">optlen</a>))
<a name="L2772" href="source/net/ipv4/tcp.c#L2772">2772</a>                         return -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L2773" href="source/net/ipv4/tcp.c#L2773">2773</a>                 <a href="ident?i=len">len</a> = <a href="ident?i=min_t">min_t</a>(unsigned int, <a href="ident?i=len">len</a>, <a href="ident?i=TCP_CA_NAME_MAX">TCP_CA_NAME_MAX</a>);
<a name="L2774" href="source/net/ipv4/tcp.c#L2774">2774</a>                 if (<a href="ident?i=put_user">put_user</a>(<a href="ident?i=len">len</a>, <a href="ident?i=optlen">optlen</a>))
<a name="L2775" href="source/net/ipv4/tcp.c#L2775">2775</a>                         return -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L2776" href="source/net/ipv4/tcp.c#L2776">2776</a>                 if (<a href="ident?i=copy_to_user">copy_to_user</a>(optval, icsk-&gt;icsk_ca_ops-&gt;<a href="ident?i=name">name</a>, <a href="ident?i=len">len</a>))
<a name="L2777" href="source/net/ipv4/tcp.c#L2777">2777</a>                         return -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L2778" href="source/net/ipv4/tcp.c#L2778">2778</a>                 return 0;
<a name="L2779" href="source/net/ipv4/tcp.c#L2779">2779</a> 
<a name="L2780" href="source/net/ipv4/tcp.c#L2780">2780</a>         case <a href="ident?i=TCP_THIN_LINEAR_TIMEOUTS">TCP_THIN_LINEAR_TIMEOUTS</a>:
<a name="L2781" href="source/net/ipv4/tcp.c#L2781">2781</a>                 <a href="ident?i=val">val</a> = <a href="ident?i=tp">tp</a>-&gt;thin_lto;
<a name="L2782" href="source/net/ipv4/tcp.c#L2782">2782</a>                 break;
<a name="L2783" href="source/net/ipv4/tcp.c#L2783">2783</a>         case <a href="ident?i=TCP_THIN_DUPACK">TCP_THIN_DUPACK</a>:
<a name="L2784" href="source/net/ipv4/tcp.c#L2784">2784</a>                 <a href="ident?i=val">val</a> = <a href="ident?i=tp">tp</a>-&gt;thin_dupack;
<a name="L2785" href="source/net/ipv4/tcp.c#L2785">2785</a>                 break;
<a name="L2786" href="source/net/ipv4/tcp.c#L2786">2786</a> 
<a name="L2787" href="source/net/ipv4/tcp.c#L2787">2787</a>         case <a href="ident?i=TCP_REPAIR">TCP_REPAIR</a>:
<a name="L2788" href="source/net/ipv4/tcp.c#L2788">2788</a>                 <a href="ident?i=val">val</a> = <a href="ident?i=tp">tp</a>-&gt;repair;
<a name="L2789" href="source/net/ipv4/tcp.c#L2789">2789</a>                 break;
<a name="L2790" href="source/net/ipv4/tcp.c#L2790">2790</a> 
<a name="L2791" href="source/net/ipv4/tcp.c#L2791">2791</a>         case <a href="ident?i=TCP_REPAIR_QUEUE">TCP_REPAIR_QUEUE</a>:
<a name="L2792" href="source/net/ipv4/tcp.c#L2792">2792</a>                 if (<a href="ident?i=tp">tp</a>-&gt;repair)
<a name="L2793" href="source/net/ipv4/tcp.c#L2793">2793</a>                         <a href="ident?i=val">val</a> = <a href="ident?i=tp">tp</a>-&gt;repair_queue;
<a name="L2794" href="source/net/ipv4/tcp.c#L2794">2794</a>                 else
<a name="L2795" href="source/net/ipv4/tcp.c#L2795">2795</a>                         return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L2796" href="source/net/ipv4/tcp.c#L2796">2796</a>                 break;
<a name="L2797" href="source/net/ipv4/tcp.c#L2797">2797</a> 
<a name="L2798" href="source/net/ipv4/tcp.c#L2798">2798</a>         case <a href="ident?i=TCP_QUEUE_SEQ">TCP_QUEUE_SEQ</a>:
<a name="L2799" href="source/net/ipv4/tcp.c#L2799">2799</a>                 if (<a href="ident?i=tp">tp</a>-&gt;repair_queue == TCP_SEND_QUEUE)
<a name="L2800" href="source/net/ipv4/tcp.c#L2800">2800</a>                         <a href="ident?i=val">val</a> = <a href="ident?i=tp">tp</a>-&gt;write_seq;
<a name="L2801" href="source/net/ipv4/tcp.c#L2801">2801</a>                 else if (<a href="ident?i=tp">tp</a>-&gt;repair_queue == TCP_RECV_QUEUE)
<a name="L2802" href="source/net/ipv4/tcp.c#L2802">2802</a>                         <a href="ident?i=val">val</a> = <a href="ident?i=tp">tp</a>-&gt;rcv_nxt;
<a name="L2803" href="source/net/ipv4/tcp.c#L2803">2803</a>                 else
<a name="L2804" href="source/net/ipv4/tcp.c#L2804">2804</a>                         return -<a href="ident?i=EINVAL">EINVAL</a>;
<a name="L2805" href="source/net/ipv4/tcp.c#L2805">2805</a>                 break;
<a name="L2806" href="source/net/ipv4/tcp.c#L2806">2806</a> 
<a name="L2807" href="source/net/ipv4/tcp.c#L2807">2807</a>         case <a href="ident?i=TCP_USER_TIMEOUT">TCP_USER_TIMEOUT</a>:
<a name="L2808" href="source/net/ipv4/tcp.c#L2808">2808</a>                 <a href="ident?i=val">val</a> = <a href="ident?i=jiffies_to_msecs">jiffies_to_msecs</a>(icsk-&gt;icsk_user_timeout);
<a name="L2809" href="source/net/ipv4/tcp.c#L2809">2809</a>                 break;
<a name="L2810" href="source/net/ipv4/tcp.c#L2810">2810</a> 
<a name="L2811" href="source/net/ipv4/tcp.c#L2811">2811</a>         case <a href="ident?i=TCP_FASTOPEN">TCP_FASTOPEN</a>:
<a name="L2812" href="source/net/ipv4/tcp.c#L2812">2812</a>                 if (icsk-&gt;icsk_accept_queue.fastopenq)
<a name="L2813" href="source/net/ipv4/tcp.c#L2813">2813</a>                         <a href="ident?i=val">val</a> = icsk-&gt;icsk_accept_queue.fastopenq-&gt;max_qlen;
<a name="L2814" href="source/net/ipv4/tcp.c#L2814">2814</a>                 else
<a name="L2815" href="source/net/ipv4/tcp.c#L2815">2815</a>                         <a href="ident?i=val">val</a> = 0;
<a name="L2816" href="source/net/ipv4/tcp.c#L2816">2816</a>                 break;
<a name="L2817" href="source/net/ipv4/tcp.c#L2817">2817</a> 
<a name="L2818" href="source/net/ipv4/tcp.c#L2818">2818</a>         case <a href="ident?i=TCP_TIMESTAMP">TCP_TIMESTAMP</a>:
<a name="L2819" href="source/net/ipv4/tcp.c#L2819">2819</a>                 <a href="ident?i=val">val</a> = <a href="ident?i=tcp_time_stamp">tcp_time_stamp</a> + <a href="ident?i=tp">tp</a>-&gt;tsoffset;
<a name="L2820" href="source/net/ipv4/tcp.c#L2820">2820</a>                 break;
<a name="L2821" href="source/net/ipv4/tcp.c#L2821">2821</a>         case <a href="ident?i=TCP_NOTSENT_LOWAT">TCP_NOTSENT_LOWAT</a>:
<a name="L2822" href="source/net/ipv4/tcp.c#L2822">2822</a>                 <a href="ident?i=val">val</a> = <a href="ident?i=tp">tp</a>-&gt;notsent_lowat;
<a name="L2823" href="source/net/ipv4/tcp.c#L2823">2823</a>                 break;
<a name="L2824" href="source/net/ipv4/tcp.c#L2824">2824</a>         default:
<a name="L2825" href="source/net/ipv4/tcp.c#L2825">2825</a>                 return -<a href="ident?i=ENOPROTOOPT">ENOPROTOOPT</a>;
<a name="L2826" href="source/net/ipv4/tcp.c#L2826">2826</a>         }
<a name="L2827" href="source/net/ipv4/tcp.c#L2827">2827</a> 
<a name="L2828" href="source/net/ipv4/tcp.c#L2828">2828</a>         if (<a href="ident?i=put_user">put_user</a>(<a href="ident?i=len">len</a>, <a href="ident?i=optlen">optlen</a>))
<a name="L2829" href="source/net/ipv4/tcp.c#L2829">2829</a>                 return -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L2830" href="source/net/ipv4/tcp.c#L2830">2830</a>         if (<a href="ident?i=copy_to_user">copy_to_user</a>(optval, &amp;<a href="ident?i=val">val</a>, <a href="ident?i=len">len</a>))
<a name="L2831" href="source/net/ipv4/tcp.c#L2831">2831</a>                 return -<a href="ident?i=EFAULT">EFAULT</a>;
<a name="L2832" href="source/net/ipv4/tcp.c#L2832">2832</a>         return 0;
<a name="L2833" href="source/net/ipv4/tcp.c#L2833">2833</a> }
<a name="L2834" href="source/net/ipv4/tcp.c#L2834">2834</a> 
<a name="L2835" href="source/net/ipv4/tcp.c#L2835">2835</a> int <a href="ident?i=tcp_getsockopt">tcp_getsockopt</a>(struct <a href="ident?i=sock">sock</a> *sk, int <a href="ident?i=level">level</a>, int optname, char <a href="ident?i=__user">__user</a> *optval,
<a name="L2836" href="source/net/ipv4/tcp.c#L2836">2836</a>                    int <a href="ident?i=__user">__user</a> *<a href="ident?i=optlen">optlen</a>)
<a name="L2837" href="source/net/ipv4/tcp.c#L2837">2837</a> {
<a name="L2838" href="source/net/ipv4/tcp.c#L2838">2838</a>         struct <a href="ident?i=inet_connection_sock">inet_connection_sock</a> *icsk = <a href="ident?i=inet_csk">inet_csk</a>(sk);
<a name="L2839" href="source/net/ipv4/tcp.c#L2839">2839</a> 
<a name="L2840" href="source/net/ipv4/tcp.c#L2840">2840</a>         if (<a href="ident?i=level">level</a> != <a href="ident?i=SOL_TCP">SOL_TCP</a>)
<a name="L2841" href="source/net/ipv4/tcp.c#L2841">2841</a>                 return icsk-&gt;icsk_af_ops-&gt;getsockopt(sk, <a href="ident?i=level">level</a>, optname,
<a name="L2842" href="source/net/ipv4/tcp.c#L2842">2842</a>                                                      optval, <a href="ident?i=optlen">optlen</a>);
<a name="L2843" href="source/net/ipv4/tcp.c#L2843">2843</a>         return <a href="ident?i=do_tcp_getsockopt">do_tcp_getsockopt</a>(sk, <a href="ident?i=level">level</a>, optname, optval, <a href="ident?i=optlen">optlen</a>);
<a name="L2844" href="source/net/ipv4/tcp.c#L2844">2844</a> }
<a name="L2845" href="source/net/ipv4/tcp.c#L2845">2845</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=tcp_getsockopt">tcp_getsockopt</a>);
<a name="L2846" href="source/net/ipv4/tcp.c#L2846">2846</a> 
<a name="L2847" href="source/net/ipv4/tcp.c#L2847">2847</a> #ifdef CONFIG_COMPAT
<a name="L2848" href="source/net/ipv4/tcp.c#L2848">2848</a> int <a href="ident?i=compat_tcp_getsockopt">compat_tcp_getsockopt</a>(struct <a href="ident?i=sock">sock</a> *sk, int <a href="ident?i=level">level</a>, int optname,
<a name="L2849" href="source/net/ipv4/tcp.c#L2849">2849</a>                           char <a href="ident?i=__user">__user</a> *optval, int <a href="ident?i=__user">__user</a> *<a href="ident?i=optlen">optlen</a>)
<a name="L2850" href="source/net/ipv4/tcp.c#L2850">2850</a> {
<a name="L2851" href="source/net/ipv4/tcp.c#L2851">2851</a>         if (<a href="ident?i=level">level</a> != <a href="ident?i=SOL_TCP">SOL_TCP</a>)
<a name="L2852" href="source/net/ipv4/tcp.c#L2852">2852</a>                 return <a href="ident?i=inet_csk_compat_getsockopt">inet_csk_compat_getsockopt</a>(sk, <a href="ident?i=level">level</a>, optname,
<a name="L2853" href="source/net/ipv4/tcp.c#L2853">2853</a>                                                   optval, <a href="ident?i=optlen">optlen</a>);
<a name="L2854" href="source/net/ipv4/tcp.c#L2854">2854</a>         return <a href="ident?i=do_tcp_getsockopt">do_tcp_getsockopt</a>(sk, <a href="ident?i=level">level</a>, optname, optval, <a href="ident?i=optlen">optlen</a>);
<a name="L2855" href="source/net/ipv4/tcp.c#L2855">2855</a> }
<a name="L2856" href="source/net/ipv4/tcp.c#L2856">2856</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=compat_tcp_getsockopt">compat_tcp_getsockopt</a>);
<a name="L2857" href="source/net/ipv4/tcp.c#L2857">2857</a> #endif
<a name="L2858" href="source/net/ipv4/tcp.c#L2858">2858</a> 
<a name="L2859" href="source/net/ipv4/tcp.c#L2859">2859</a> #ifdef CONFIG_TCP_MD5SIG
<a name="L2860" href="source/net/ipv4/tcp.c#L2860">2860</a> static <a href="ident?i=DEFINE_PER_CPU">DEFINE_PER_CPU</a>(struct <a href="ident?i=tcp_md5sig_pool">tcp_md5sig_pool</a>, <a href="ident?i=tcp_md5sig_pool">tcp_md5sig_pool</a>);
<a name="L2861" href="source/net/ipv4/tcp.c#L2861">2861</a> static <a href="ident?i=DEFINE_MUTEX">DEFINE_MUTEX</a>(tcp_md5sig_mutex);
<a name="L2862" href="source/net/ipv4/tcp.c#L2862">2862</a> static <a href="ident?i=bool">bool</a> <a href="ident?i=tcp_md5sig_pool_populated">tcp_md5sig_pool_populated</a> = <a href="ident?i=false">false</a>;
<a name="L2863" href="source/net/ipv4/tcp.c#L2863">2863</a> 
<a name="L2864" href="source/net/ipv4/tcp.c#L2864">2864</a> static void <a href="ident?i=__tcp_alloc_md5sig_pool">__tcp_alloc_md5sig_pool</a>(void)
<a name="L2865" href="source/net/ipv4/tcp.c#L2865">2865</a> {
<a name="L2866" href="source/net/ipv4/tcp.c#L2866">2866</a>         int <a href="ident?i=cpu">cpu</a>;
<a name="L2867" href="source/net/ipv4/tcp.c#L2867">2867</a> 
<a name="L2868" href="source/net/ipv4/tcp.c#L2868">2868</a>         <a href="ident?i=for_each_possible_cpu">for_each_possible_cpu</a>(<a href="ident?i=cpu">cpu</a>) {
<a name="L2869" href="source/net/ipv4/tcp.c#L2869">2869</a>                 if (!<a href="ident?i=per_cpu">per_cpu</a>(<a href="ident?i=tcp_md5sig_pool">tcp_md5sig_pool</a>, <a href="ident?i=cpu">cpu</a>).md5_desc.<a href="ident?i=tfm">tfm</a>) {
<a name="L2870" href="source/net/ipv4/tcp.c#L2870">2870</a>                         struct <a href="ident?i=crypto_hash">crypto_hash</a> *<a href="ident?i=hash">hash</a>;
<a name="L2871" href="source/net/ipv4/tcp.c#L2871">2871</a> 
<a name="L2872" href="source/net/ipv4/tcp.c#L2872">2872</a>                         <a href="ident?i=hash">hash</a> = <a href="ident?i=crypto_alloc_hash">crypto_alloc_hash</a>(<i>"md5"</i>, 0, <a href="ident?i=CRYPTO_ALG_ASYNC">CRYPTO_ALG_ASYNC</a>);
<a name="L2873" href="source/net/ipv4/tcp.c#L2873">2873</a>                         if (<a href="ident?i=IS_ERR_OR_NULL">IS_ERR_OR_NULL</a>(<a href="ident?i=hash">hash</a>))
<a name="L2874" href="source/net/ipv4/tcp.c#L2874">2874</a>                                 return;
<a name="L2875" href="source/net/ipv4/tcp.c#L2875">2875</a>                         <a href="ident?i=per_cpu">per_cpu</a>(<a href="ident?i=tcp_md5sig_pool">tcp_md5sig_pool</a>, <a href="ident?i=cpu">cpu</a>).md5_desc.<a href="ident?i=tfm">tfm</a> = <a href="ident?i=hash">hash</a>;
<a name="L2876" href="source/net/ipv4/tcp.c#L2876">2876</a>                 }
<a name="L2877" href="source/net/ipv4/tcp.c#L2877">2877</a>         }
<a name="L2878" href="source/net/ipv4/tcp.c#L2878">2878</a>         <b><i>/* before setting tcp_md5sig_pool_populated, we must commit all writes</i></b>
<a name="L2879" href="source/net/ipv4/tcp.c#L2879">2879</a> <b><i>         * to memory. See smp_rmb() in tcp_get_md5sig_pool()</i></b>
<a name="L2880" href="source/net/ipv4/tcp.c#L2880">2880</a> <b><i>         */</i></b>
<a name="L2881" href="source/net/ipv4/tcp.c#L2881">2881</a>         <a href="ident?i=smp_wmb">smp_wmb</a>();
<a name="L2882" href="source/net/ipv4/tcp.c#L2882">2882</a>         <a href="ident?i=tcp_md5sig_pool_populated">tcp_md5sig_pool_populated</a> = <a href="ident?i=true">true</a>;
<a name="L2883" href="source/net/ipv4/tcp.c#L2883">2883</a> }
<a name="L2884" href="source/net/ipv4/tcp.c#L2884">2884</a> 
<a name="L2885" href="source/net/ipv4/tcp.c#L2885">2885</a> <a href="ident?i=bool">bool</a> <a href="ident?i=tcp_alloc_md5sig_pool">tcp_alloc_md5sig_pool</a>(void)
<a name="L2886" href="source/net/ipv4/tcp.c#L2886">2886</a> {
<a name="L2887" href="source/net/ipv4/tcp.c#L2887">2887</a>         if (<a href="ident?i=unlikely">unlikely</a>(!<a href="ident?i=tcp_md5sig_pool_populated">tcp_md5sig_pool_populated</a>)) {
<a name="L2888" href="source/net/ipv4/tcp.c#L2888">2888</a>                 <a href="ident?i=mutex_lock">mutex_lock</a>(&amp;tcp_md5sig_mutex);
<a name="L2889" href="source/net/ipv4/tcp.c#L2889">2889</a> 
<a name="L2890" href="source/net/ipv4/tcp.c#L2890">2890</a>                 if (!<a href="ident?i=tcp_md5sig_pool_populated">tcp_md5sig_pool_populated</a>)
<a name="L2891" href="source/net/ipv4/tcp.c#L2891">2891</a>                         <a href="ident?i=__tcp_alloc_md5sig_pool">__tcp_alloc_md5sig_pool</a>();
<a name="L2892" href="source/net/ipv4/tcp.c#L2892">2892</a> 
<a name="L2893" href="source/net/ipv4/tcp.c#L2893">2893</a>                 <a href="ident?i=mutex_unlock">mutex_unlock</a>(&amp;tcp_md5sig_mutex);
<a name="L2894" href="source/net/ipv4/tcp.c#L2894">2894</a>         }
<a name="L2895" href="source/net/ipv4/tcp.c#L2895">2895</a>         return <a href="ident?i=tcp_md5sig_pool_populated">tcp_md5sig_pool_populated</a>;
<a name="L2896" href="source/net/ipv4/tcp.c#L2896">2896</a> }
<a name="L2897" href="source/net/ipv4/tcp.c#L2897">2897</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=tcp_alloc_md5sig_pool">tcp_alloc_md5sig_pool</a>);
<a name="L2898" href="source/net/ipv4/tcp.c#L2898">2898</a> 
<a name="L2899" href="source/net/ipv4/tcp.c#L2899">2899</a> 
<a name="L2900" href="source/net/ipv4/tcp.c#L2900">2900</a> <b><i>/**</i></b>
<a name="L2901" href="source/net/ipv4/tcp.c#L2901">2901</a> <b><i> *      tcp_get_md5sig_pool - get md5sig_pool for this user</i></b>
<a name="L2902" href="source/net/ipv4/tcp.c#L2902">2902</a> <b><i> *</i></b>
<a name="L2903" href="source/net/ipv4/tcp.c#L2903">2903</a> <b><i> *      We use percpu structure, so if we succeed, we exit with preemption</i></b>
<a name="L2904" href="source/net/ipv4/tcp.c#L2904">2904</a> <b><i> *      and BH disabled, to make sure another thread or softirq handling</i></b>
<a name="L2905" href="source/net/ipv4/tcp.c#L2905">2905</a> <b><i> *      wont try to get same context.</i></b>
<a name="L2906" href="source/net/ipv4/tcp.c#L2906">2906</a> <b><i> */</i></b>
<a name="L2907" href="source/net/ipv4/tcp.c#L2907">2907</a> struct <a href="ident?i=tcp_md5sig_pool">tcp_md5sig_pool</a> *<a href="ident?i=tcp_get_md5sig_pool">tcp_get_md5sig_pool</a>(void)
<a name="L2908" href="source/net/ipv4/tcp.c#L2908">2908</a> {
<a name="L2909" href="source/net/ipv4/tcp.c#L2909">2909</a>         <a href="ident?i=local_bh_disable">local_bh_disable</a>();
<a name="L2910" href="source/net/ipv4/tcp.c#L2910">2910</a> 
<a name="L2911" href="source/net/ipv4/tcp.c#L2911">2911</a>         if (<a href="ident?i=tcp_md5sig_pool_populated">tcp_md5sig_pool_populated</a>) {
<a name="L2912" href="source/net/ipv4/tcp.c#L2912">2912</a>                 <b><i>/* coupled with smp_wmb() in __tcp_alloc_md5sig_pool() */</i></b>
<a name="L2913" href="source/net/ipv4/tcp.c#L2913">2913</a>                 <a href="ident?i=smp_rmb">smp_rmb</a>();
<a name="L2914" href="source/net/ipv4/tcp.c#L2914">2914</a>                 return <a href="ident?i=this_cpu_ptr">this_cpu_ptr</a>(&amp;<a href="ident?i=tcp_md5sig_pool">tcp_md5sig_pool</a>);
<a name="L2915" href="source/net/ipv4/tcp.c#L2915">2915</a>         }
<a name="L2916" href="source/net/ipv4/tcp.c#L2916">2916</a>         <a href="ident?i=local_bh_enable">local_bh_enable</a>();
<a name="L2917" href="source/net/ipv4/tcp.c#L2917">2917</a>         return <a href="ident?i=NULL">NULL</a>;
<a name="L2918" href="source/net/ipv4/tcp.c#L2918">2918</a> }
<a name="L2919" href="source/net/ipv4/tcp.c#L2919">2919</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=tcp_get_md5sig_pool">tcp_get_md5sig_pool</a>);
<a name="L2920" href="source/net/ipv4/tcp.c#L2920">2920</a> 
<a name="L2921" href="source/net/ipv4/tcp.c#L2921">2921</a> int <a href="ident?i=tcp_md5_hash_header">tcp_md5_hash_header</a>(struct <a href="ident?i=tcp_md5sig_pool">tcp_md5sig_pool</a> *hp,
<a name="L2922" href="source/net/ipv4/tcp.c#L2922">2922</a>                         const struct <a href="ident?i=tcphdr">tcphdr</a> *<a href="ident?i=th">th</a>)
<a name="L2923" href="source/net/ipv4/tcp.c#L2923">2923</a> {
<a name="L2924" href="source/net/ipv4/tcp.c#L2924">2924</a>         struct <a href="ident?i=scatterlist">scatterlist</a> sg;
<a name="L2925" href="source/net/ipv4/tcp.c#L2925">2925</a>         struct <a href="ident?i=tcphdr">tcphdr</a> <a href="ident?i=hdr">hdr</a>;
<a name="L2926" href="source/net/ipv4/tcp.c#L2926">2926</a>         int <a href="ident?i=err">err</a>;
<a name="L2927" href="source/net/ipv4/tcp.c#L2927">2927</a> 
<a name="L2928" href="source/net/ipv4/tcp.c#L2928">2928</a>         <b><i>/* We are not allowed to change tcphdr, make a local copy */</i></b>
<a name="L2929" href="source/net/ipv4/tcp.c#L2929">2929</a>         <a href="ident?i=memcpy">memcpy</a>(&amp;<a href="ident?i=hdr">hdr</a>, <a href="ident?i=th">th</a>, sizeof(<a href="ident?i=hdr">hdr</a>));
<a name="L2930" href="source/net/ipv4/tcp.c#L2930">2930</a>         <a href="ident?i=hdr">hdr</a>.<a href="ident?i=check">check</a> = 0;
<a name="L2931" href="source/net/ipv4/tcp.c#L2931">2931</a> 
<a name="L2932" href="source/net/ipv4/tcp.c#L2932">2932</a>         <b><i>/* options aren't included in the hash */</i></b>
<a name="L2933" href="source/net/ipv4/tcp.c#L2933">2933</a>         <a href="ident?i=sg_init_one">sg_init_one</a>(&amp;sg, &amp;<a href="ident?i=hdr">hdr</a>, sizeof(<a href="ident?i=hdr">hdr</a>));
<a name="L2934" href="source/net/ipv4/tcp.c#L2934">2934</a>         <a href="ident?i=err">err</a> = <a href="ident?i=crypto_hash_update">crypto_hash_update</a>(&amp;hp-&gt;md5_desc, &amp;sg, sizeof(<a href="ident?i=hdr">hdr</a>));
<a name="L2935" href="source/net/ipv4/tcp.c#L2935">2935</a>         return <a href="ident?i=err">err</a>;
<a name="L2936" href="source/net/ipv4/tcp.c#L2936">2936</a> }
<a name="L2937" href="source/net/ipv4/tcp.c#L2937">2937</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=tcp_md5_hash_header">tcp_md5_hash_header</a>);
<a name="L2938" href="source/net/ipv4/tcp.c#L2938">2938</a> 
<a name="L2939" href="source/net/ipv4/tcp.c#L2939">2939</a> int <a href="ident?i=tcp_md5_hash_skb_data">tcp_md5_hash_skb_data</a>(struct <a href="ident?i=tcp_md5sig_pool">tcp_md5sig_pool</a> *hp,
<a name="L2940" href="source/net/ipv4/tcp.c#L2940">2940</a>                           const struct <a href="ident?i=sk_buff">sk_buff</a> *<a href="ident?i=skb">skb</a>, unsigned int <a href="ident?i=header_len">header_len</a>)
<a name="L2941" href="source/net/ipv4/tcp.c#L2941">2941</a> {
<a name="L2942" href="source/net/ipv4/tcp.c#L2942">2942</a>         struct <a href="ident?i=scatterlist">scatterlist</a> sg;
<a name="L2943" href="source/net/ipv4/tcp.c#L2943">2943</a>         const struct <a href="ident?i=tcphdr">tcphdr</a> *<a href="ident?i=tp">tp</a> = <a href="ident?i=tcp_hdr">tcp_hdr</a>(<a href="ident?i=skb">skb</a>);
<a name="L2944" href="source/net/ipv4/tcp.c#L2944">2944</a>         struct <a href="ident?i=hash_desc">hash_desc</a> *<a href="ident?i=desc">desc</a> = &amp;hp-&gt;md5_desc;
<a name="L2945" href="source/net/ipv4/tcp.c#L2945">2945</a>         unsigned int <a href="ident?i=i">i</a>;
<a name="L2946" href="source/net/ipv4/tcp.c#L2946">2946</a>         const unsigned int head_data_len = <a href="ident?i=skb_headlen">skb_headlen</a>(<a href="ident?i=skb">skb</a>) &gt; <a href="ident?i=header_len">header_len</a> ?
<a name="L2947" href="source/net/ipv4/tcp.c#L2947">2947</a>                                            <a href="ident?i=skb_headlen">skb_headlen</a>(<a href="ident?i=skb">skb</a>) - <a href="ident?i=header_len">header_len</a> : 0;
<a name="L2948" href="source/net/ipv4/tcp.c#L2948">2948</a>         const struct <a href="ident?i=skb_shared_info">skb_shared_info</a> *shi = <a href="ident?i=skb_shinfo">skb_shinfo</a>(<a href="ident?i=skb">skb</a>);
<a name="L2949" href="source/net/ipv4/tcp.c#L2949">2949</a>         struct <a href="ident?i=sk_buff">sk_buff</a> *frag_iter;
<a name="L2950" href="source/net/ipv4/tcp.c#L2950">2950</a> 
<a name="L2951" href="source/net/ipv4/tcp.c#L2951">2951</a>         <a href="ident?i=sg_init_table">sg_init_table</a>(&amp;sg, 1);
<a name="L2952" href="source/net/ipv4/tcp.c#L2952">2952</a> 
<a name="L2953" href="source/net/ipv4/tcp.c#L2953">2953</a>         <a href="ident?i=sg_set_buf">sg_set_buf</a>(&amp;sg, ((<a href="ident?i=u8">u8</a> *) <a href="ident?i=tp">tp</a>) + <a href="ident?i=header_len">header_len</a>, head_data_len);
<a name="L2954" href="source/net/ipv4/tcp.c#L2954">2954</a>         if (<a href="ident?i=crypto_hash_update">crypto_hash_update</a>(<a href="ident?i=desc">desc</a>, &amp;sg, head_data_len))
<a name="L2955" href="source/net/ipv4/tcp.c#L2955">2955</a>                 return 1;
<a name="L2956" href="source/net/ipv4/tcp.c#L2956">2956</a> 
<a name="L2957" href="source/net/ipv4/tcp.c#L2957">2957</a>         for (<a href="ident?i=i">i</a> = 0; <a href="ident?i=i">i</a> &lt; shi-&gt;nr_frags; ++<a href="ident?i=i">i</a>) {
<a name="L2958" href="source/net/ipv4/tcp.c#L2958">2958</a>                 const struct <a href="ident?i=skb_frag_struct">skb_frag_struct</a> *<a href="ident?i=f">f</a> = &amp;shi-&gt;frags[<a href="ident?i=i">i</a>];
<a name="L2959" href="source/net/ipv4/tcp.c#L2959">2959</a>                 unsigned int <a href="ident?i=offset">offset</a> = <a href="ident?i=f">f</a>-&gt;<a href="ident?i=page_offset">page_offset</a>;
<a name="L2960" href="source/net/ipv4/tcp.c#L2960">2960</a>                 struct <a href="ident?i=page">page</a> *<a href="ident?i=page">page</a> = <a href="ident?i=skb_frag_page">skb_frag_page</a>(<a href="ident?i=f">f</a>) + (<a href="ident?i=offset">offset</a> &gt;&gt; <a href="ident?i=PAGE_SHIFT">PAGE_SHIFT</a>);
<a name="L2961" href="source/net/ipv4/tcp.c#L2961">2961</a> 
<a name="L2962" href="source/net/ipv4/tcp.c#L2962">2962</a>                 <a href="ident?i=sg_set_page">sg_set_page</a>(&amp;sg, <a href="ident?i=page">page</a>, <a href="ident?i=skb_frag_size">skb_frag_size</a>(<a href="ident?i=f">f</a>),
<a name="L2963" href="source/net/ipv4/tcp.c#L2963">2963</a>                             <a href="ident?i=offset_in_page">offset_in_page</a>(<a href="ident?i=offset">offset</a>));
<a name="L2964" href="source/net/ipv4/tcp.c#L2964">2964</a>                 if (<a href="ident?i=crypto_hash_update">crypto_hash_update</a>(<a href="ident?i=desc">desc</a>, &amp;sg, <a href="ident?i=skb_frag_size">skb_frag_size</a>(<a href="ident?i=f">f</a>)))
<a name="L2965" href="source/net/ipv4/tcp.c#L2965">2965</a>                         return 1;
<a name="L2966" href="source/net/ipv4/tcp.c#L2966">2966</a>         }
<a name="L2967" href="source/net/ipv4/tcp.c#L2967">2967</a> 
<a name="L2968" href="source/net/ipv4/tcp.c#L2968">2968</a>         <a href="ident?i=skb_walk_frags">skb_walk_frags</a>(<a href="ident?i=skb">skb</a>, frag_iter)
<a name="L2969" href="source/net/ipv4/tcp.c#L2969">2969</a>                 if (<a href="ident?i=tcp_md5_hash_skb_data">tcp_md5_hash_skb_data</a>(hp, frag_iter, 0))
<a name="L2970" href="source/net/ipv4/tcp.c#L2970">2970</a>                         return 1;
<a name="L2971" href="source/net/ipv4/tcp.c#L2971">2971</a> 
<a name="L2972" href="source/net/ipv4/tcp.c#L2972">2972</a>         return 0;
<a name="L2973" href="source/net/ipv4/tcp.c#L2973">2973</a> }
<a name="L2974" href="source/net/ipv4/tcp.c#L2974">2974</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=tcp_md5_hash_skb_data">tcp_md5_hash_skb_data</a>);
<a name="L2975" href="source/net/ipv4/tcp.c#L2975">2975</a> 
<a name="L2976" href="source/net/ipv4/tcp.c#L2976">2976</a> int <a href="ident?i=tcp_md5_hash_key">tcp_md5_hash_key</a>(struct <a href="ident?i=tcp_md5sig_pool">tcp_md5sig_pool</a> *hp, const struct <a href="ident?i=tcp_md5sig_key">tcp_md5sig_key</a> *<a href="ident?i=key">key</a>)
<a name="L2977" href="source/net/ipv4/tcp.c#L2977">2977</a> {
<a name="L2978" href="source/net/ipv4/tcp.c#L2978">2978</a>         struct <a href="ident?i=scatterlist">scatterlist</a> sg;
<a name="L2979" href="source/net/ipv4/tcp.c#L2979">2979</a> 
<a name="L2980" href="source/net/ipv4/tcp.c#L2980">2980</a>         <a href="ident?i=sg_init_one">sg_init_one</a>(&amp;sg, <a href="ident?i=key">key</a>-&gt;<a href="ident?i=key">key</a>, <a href="ident?i=key">key</a>-&gt;keylen);
<a name="L2981" href="source/net/ipv4/tcp.c#L2981">2981</a>         return <a href="ident?i=crypto_hash_update">crypto_hash_update</a>(&amp;hp-&gt;md5_desc, &amp;sg, <a href="ident?i=key">key</a>-&gt;keylen);
<a name="L2982" href="source/net/ipv4/tcp.c#L2982">2982</a> }
<a name="L2983" href="source/net/ipv4/tcp.c#L2983">2983</a> <a href="ident?i=EXPORT_SYMBOL">EXPORT_SYMBOL</a>(<a href="ident?i=tcp_md5_hash_key">tcp_md5_hash_key</a>);
<a name="L2984" href="source/net/ipv4/tcp.c#L2984">2984</a> 
<a name="L2985" href="source/net/ipv4/tcp.c#L2985">2985</a> #endif
<a name="L2986" href="source/net/ipv4/tcp.c#L2986">2986</a> 
<a name="L2987" href="source/net/ipv4/tcp.c#L2987">2987</a> void <a href="ident?i=tcp_done">tcp_done</a>(struct <a href="ident?i=sock">sock</a> *sk)
<a name="L2988" href="source/net/ipv4/tcp.c#L2988">2988</a> {
<a name="L2989" href="source/net/ipv4/tcp.c#L2989">2989</a>         struct <a href="ident?i=request_sock">request_sock</a> *<a href="ident?i=req">req</a> = <a href="ident?i=tcp_sk">tcp_sk</a>(sk)-&gt;fastopen_rsk;
<a name="L2990" href="source/net/ipv4/tcp.c#L2990">2990</a> 
<a name="L2991" href="source/net/ipv4/tcp.c#L2991">2991</a>         if (sk-&gt;<a href="ident?i=sk_state">sk_state</a> == TCP_SYN_SENT || sk-&gt;<a href="ident?i=sk_state">sk_state</a> == TCP_SYN_RECV)
<a name="L2992" href="source/net/ipv4/tcp.c#L2992">2992</a>                 <a href="ident?i=TCP_INC_STATS_BH">TCP_INC_STATS_BH</a>(<a href="ident?i=sock_net">sock_net</a>(sk), TCP_MIB_ATTEMPTFAILS);
<a name="L2993" href="source/net/ipv4/tcp.c#L2993">2993</a> 
<a name="L2994" href="source/net/ipv4/tcp.c#L2994">2994</a>         <a href="ident?i=tcp_set_state">tcp_set_state</a>(sk, TCP_CLOSE);
<a name="L2995" href="source/net/ipv4/tcp.c#L2995">2995</a>         <a href="ident?i=tcp_clear_xmit_timers">tcp_clear_xmit_timers</a>(sk);
<a name="L2996" href="source/net/ipv4/tcp.c#L2996">2996</a>         if (<a href="ident?i=req">req</a>)
<a name="L2997" href="source/net/ipv4/tcp.c#L2997">2997</a>                 <a href="ident?i=reqsk_fastopen_remove">reqsk_fastopen_remove</a>(sk, <a href="ident?i=req">req</a>, <a href="ident?i=false">false</a>);
<a name="L2998" href="source/net/ipv4/tcp.c#L2998">2998</a> 
<a name="L2999" href="source/net/ipv4/tcp.c#L2999">2999</a>         sk-&gt;sk_shutdown = <a href="ident?i=SHUTDOWN_MASK">SHUTDOWN_MASK</a>;
<a name="L3000" href="source/net/ipv4/tcp.c#L3000">3000</a> 
<a name="L3001" href="source/net/ipv4/tcp.c#L3001">3001</a>         if (!<a href="ident?i=sock_flag">sock_flag</a>(sk, SOCK_DEAD))
<a name="L3002" href="source/net/ipv4/tcp.c#L3002">3002</a>                 sk-&gt;sk_state_change(sk);
<a name="L3003" href="source/net/ipv4/tcp.c#L3003">3003</a>         else
<a name="L3004" href="source/net/ipv4/tcp.c#L3004">3004</a>                 <a href="ident?i=inet_csk_destroy_sock">inet_csk_destroy_sock</a>(sk);
<a name="L3005" href="source/net/ipv4/tcp.c#L3005">3005</a> }
<a name="L3006" href="source/net/ipv4/tcp.c#L3006">3006</a> <a href="ident?i=EXPORT_SYMBOL_GPL">EXPORT_SYMBOL_GPL</a>(<a href="ident?i=tcp_done">tcp_done</a>);
<a name="L3007" href="source/net/ipv4/tcp.c#L3007">3007</a> 
<a name="L3008" href="source/net/ipv4/tcp.c#L3008">3008</a> extern struct <a href="ident?i=tcp_congestion_ops">tcp_congestion_ops</a> <a href="ident?i=tcp_reno">tcp_reno</a>;
<a name="L3009" href="source/net/ipv4/tcp.c#L3009">3009</a> 
<a name="L3010" href="source/net/ipv4/tcp.c#L3010">3010</a> static <a href="ident?i=__initdata">__initdata</a> unsigned long <a href="ident?i=thash_entries">thash_entries</a>;
<a name="L3011" href="source/net/ipv4/tcp.c#L3011">3011</a> static int <a href="ident?i=__init">__init</a> <a href="ident?i=set_thash_entries">set_thash_entries</a>(char *<a href="ident?i=str">str</a>)
<a name="L3012" href="source/net/ipv4/tcp.c#L3012">3012</a> {
<a name="L3013" href="source/net/ipv4/tcp.c#L3013">3013</a>         <a href="ident?i=ssize_t">ssize_t</a> <a href="ident?i=ret">ret</a>;
<a name="L3014" href="source/net/ipv4/tcp.c#L3014">3014</a> 
<a name="L3015" href="source/net/ipv4/tcp.c#L3015">3015</a>         if (!<a href="ident?i=str">str</a>)
<a name="L3016" href="source/net/ipv4/tcp.c#L3016">3016</a>                 return 0;
<a name="L3017" href="source/net/ipv4/tcp.c#L3017">3017</a> 
<a name="L3018" href="source/net/ipv4/tcp.c#L3018">3018</a>         <a href="ident?i=ret">ret</a> = <a href="ident?i=kstrtoul">kstrtoul</a>(<a href="ident?i=str">str</a>, 0, &amp;<a href="ident?i=thash_entries">thash_entries</a>);
<a name="L3019" href="source/net/ipv4/tcp.c#L3019">3019</a>         if (<a href="ident?i=ret">ret</a>)
<a name="L3020" href="source/net/ipv4/tcp.c#L3020">3020</a>                 return 0;
<a name="L3021" href="source/net/ipv4/tcp.c#L3021">3021</a> 
<a name="L3022" href="source/net/ipv4/tcp.c#L3022">3022</a>         return 1;
<a name="L3023" href="source/net/ipv4/tcp.c#L3023">3023</a> }
<a name="L3024" href="source/net/ipv4/tcp.c#L3024">3024</a> <a href="ident?i=__setup">__setup</a>(<i>"thash_entries="</i>, <a href="ident?i=set_thash_entries">set_thash_entries</a>);
<a name="L3025" href="source/net/ipv4/tcp.c#L3025">3025</a> 
<a name="L3026" href="source/net/ipv4/tcp.c#L3026">3026</a> static void <a href="ident?i=__init">__init</a> <a href="ident?i=tcp_init_mem">tcp_init_mem</a>(void)
<a name="L3027" href="source/net/ipv4/tcp.c#L3027">3027</a> {
<a name="L3028" href="source/net/ipv4/tcp.c#L3028">3028</a>         unsigned long <a href="ident?i=limit">limit</a> = <a href="ident?i=nr_free_buffer_pages">nr_free_buffer_pages</a>() / 8;
<a name="L3029" href="source/net/ipv4/tcp.c#L3029">3029</a>         <a href="ident?i=limit">limit</a> = <a href="ident?i=max">max</a>(<a href="ident?i=limit">limit</a>, 128UL);
<a name="L3030" href="source/net/ipv4/tcp.c#L3030">3030</a>         <a href="ident?i=sysctl_tcp_mem">sysctl_tcp_mem</a>[0] = <a href="ident?i=limit">limit</a> / 4 * 3;
<a name="L3031" href="source/net/ipv4/tcp.c#L3031">3031</a>         <a href="ident?i=sysctl_tcp_mem">sysctl_tcp_mem</a>[1] = <a href="ident?i=limit">limit</a>;
<a name="L3032" href="source/net/ipv4/tcp.c#L3032">3032</a>         <a href="ident?i=sysctl_tcp_mem">sysctl_tcp_mem</a>[2] = <a href="ident?i=sysctl_tcp_mem">sysctl_tcp_mem</a>[0] * 2;
<a name="L3033" href="source/net/ipv4/tcp.c#L3033">3033</a> }
<a name="L3034" href="source/net/ipv4/tcp.c#L3034">3034</a> 
<a name="L3035" href="source/net/ipv4/tcp.c#L3035">3035</a> void <a href="ident?i=__init">__init</a> <a href="ident?i=tcp_init">tcp_init</a>(void)
<a name="L3036" href="source/net/ipv4/tcp.c#L3036">3036</a> {
<a name="L3037" href="source/net/ipv4/tcp.c#L3037">3037</a>         unsigned long <a href="ident?i=limit">limit</a>;
<a name="L3038" href="source/net/ipv4/tcp.c#L3038">3038</a>         int max_rshare, max_wshare, cnt;
<a name="L3039" href="source/net/ipv4/tcp.c#L3039">3039</a>         unsigned int <a href="ident?i=i">i</a>;
<a name="L3040" href="source/net/ipv4/tcp.c#L3040">3040</a> 
<a name="L3041" href="source/net/ipv4/tcp.c#L3041">3041</a>         <a href="ident?i=sock_skb_cb_check_size">sock_skb_cb_check_size</a>(sizeof(struct <a href="ident?i=tcp_skb_cb">tcp_skb_cb</a>));
<a name="L3042" href="source/net/ipv4/tcp.c#L3042">3042</a> 
<a name="L3043" href="source/net/ipv4/tcp.c#L3043">3043</a>         <a href="ident?i=percpu_counter_init">percpu_counter_init</a>(&amp;<a href="ident?i=tcp_sockets_allocated">tcp_sockets_allocated</a>, 0, <a href="ident?i=GFP_KERNEL">GFP_KERNEL</a>);
<a name="L3044" href="source/net/ipv4/tcp.c#L3044">3044</a>         <a href="ident?i=percpu_counter_init">percpu_counter_init</a>(&amp;<a href="ident?i=tcp_orphan_count">tcp_orphan_count</a>, 0, <a href="ident?i=GFP_KERNEL">GFP_KERNEL</a>);
<a name="L3045" href="source/net/ipv4/tcp.c#L3045">3045</a>         <a href="ident?i=tcp_hashinfo">tcp_hashinfo</a>.bind_bucket_cachep =
<a name="L3046" href="source/net/ipv4/tcp.c#L3046">3046</a>                 <a href="ident?i=kmem_cache_create">kmem_cache_create</a>(<i>"tcp_bind_bucket"</i>,
<a name="L3047" href="source/net/ipv4/tcp.c#L3047">3047</a>                                   sizeof(struct <a href="ident?i=inet_bind_bucket">inet_bind_bucket</a>), 0,
<a name="L3048" href="source/net/ipv4/tcp.c#L3048">3048</a>                                   <a href="ident?i=SLAB_HWCACHE_ALIGN">SLAB_HWCACHE_ALIGN</a>|<a href="ident?i=SLAB_PANIC">SLAB_PANIC</a>, <a href="ident?i=NULL">NULL</a>);
<a name="L3049" href="source/net/ipv4/tcp.c#L3049">3049</a> 
<a name="L3050" href="source/net/ipv4/tcp.c#L3050">3050</a>         <b><i>/* Size and allocate the main established and bind bucket</i></b>
<a name="L3051" href="source/net/ipv4/tcp.c#L3051">3051</a> <b><i>         * hash tables.</i></b>
<a name="L3052" href="source/net/ipv4/tcp.c#L3052">3052</a> <b><i>         *</i></b>
<a name="L3053" href="source/net/ipv4/tcp.c#L3053">3053</a> <b><i>         * The methodology is similar to that of the buffer cache.</i></b>
<a name="L3054" href="source/net/ipv4/tcp.c#L3054">3054</a> <b><i>         */</i></b>
<a name="L3055" href="source/net/ipv4/tcp.c#L3055">3055</a>         <a href="ident?i=tcp_hashinfo">tcp_hashinfo</a>.ehash =
<a name="L3056" href="source/net/ipv4/tcp.c#L3056">3056</a>                 <a href="ident?i=alloc_large_system_hash">alloc_large_system_hash</a>(<i>"TCP established"</i>,
<a name="L3057" href="source/net/ipv4/tcp.c#L3057">3057</a>                                         sizeof(struct <a href="ident?i=inet_ehash_bucket">inet_ehash_bucket</a>),
<a name="L3058" href="source/net/ipv4/tcp.c#L3058">3058</a>                                         <a href="ident?i=thash_entries">thash_entries</a>,
<a name="L3059" href="source/net/ipv4/tcp.c#L3059">3059</a>                                         17, <b><i>/* one slot per 128 KB of memory */</i></b>
<a name="L3060" href="source/net/ipv4/tcp.c#L3060">3060</a>                                         0,
<a name="L3061" href="source/net/ipv4/tcp.c#L3061">3061</a>                                         <a href="ident?i=NULL">NULL</a>,
<a name="L3062" href="source/net/ipv4/tcp.c#L3062">3062</a>                                         &amp;<a href="ident?i=tcp_hashinfo">tcp_hashinfo</a>.ehash_mask,
<a name="L3063" href="source/net/ipv4/tcp.c#L3063">3063</a>                                         0,
<a name="L3064" href="source/net/ipv4/tcp.c#L3064">3064</a>                                         <a href="ident?i=thash_entries">thash_entries</a> ? 0 : 512 * 1024);
<a name="L3065" href="source/net/ipv4/tcp.c#L3065">3065</a>         for (<a href="ident?i=i">i</a> = 0; <a href="ident?i=i">i</a> &lt;= <a href="ident?i=tcp_hashinfo">tcp_hashinfo</a>.ehash_mask; <a href="ident?i=i">i</a>++)
<a name="L3066" href="source/net/ipv4/tcp.c#L3066">3066</a>                 <a href="ident?i=INIT_HLIST_NULLS_HEAD">INIT_HLIST_NULLS_HEAD</a>(&amp;<a href="ident?i=tcp_hashinfo">tcp_hashinfo</a>.ehash[<a href="ident?i=i">i</a>].<a href="ident?i=chain">chain</a>, <a href="ident?i=i">i</a>);
<a name="L3067" href="source/net/ipv4/tcp.c#L3067">3067</a> 
<a name="L3068" href="source/net/ipv4/tcp.c#L3068">3068</a>         if (<a href="ident?i=inet_ehash_locks_alloc">inet_ehash_locks_alloc</a>(&amp;<a href="ident?i=tcp_hashinfo">tcp_hashinfo</a>))
<a name="L3069" href="source/net/ipv4/tcp.c#L3069">3069</a>                 <a href="ident?i=panic">panic</a>(<i>"TCP: failed to alloc ehash_locks"</i>);
<a name="L3070" href="source/net/ipv4/tcp.c#L3070">3070</a>         <a href="ident?i=tcp_hashinfo">tcp_hashinfo</a>.bhash =
<a name="L3071" href="source/net/ipv4/tcp.c#L3071">3071</a>                 <a href="ident?i=alloc_large_system_hash">alloc_large_system_hash</a>(<i>"TCP bind"</i>,
<a name="L3072" href="source/net/ipv4/tcp.c#L3072">3072</a>                                         sizeof(struct <a href="ident?i=inet_bind_hashbucket">inet_bind_hashbucket</a>),
<a name="L3073" href="source/net/ipv4/tcp.c#L3073">3073</a>                                         <a href="ident?i=tcp_hashinfo">tcp_hashinfo</a>.ehash_mask + 1,
<a name="L3074" href="source/net/ipv4/tcp.c#L3074">3074</a>                                         17, <b><i>/* one slot per 128 KB of memory */</i></b>
<a name="L3075" href="source/net/ipv4/tcp.c#L3075">3075</a>                                         0,
<a name="L3076" href="source/net/ipv4/tcp.c#L3076">3076</a>                                         &amp;<a href="ident?i=tcp_hashinfo">tcp_hashinfo</a>.bhash_size,
<a name="L3077" href="source/net/ipv4/tcp.c#L3077">3077</a>                                         <a href="ident?i=NULL">NULL</a>,
<a name="L3078" href="source/net/ipv4/tcp.c#L3078">3078</a>                                         0,
<a name="L3079" href="source/net/ipv4/tcp.c#L3079">3079</a>                                         64 * 1024);
<a name="L3080" href="source/net/ipv4/tcp.c#L3080">3080</a>         <a href="ident?i=tcp_hashinfo">tcp_hashinfo</a>.bhash_size = 1U &lt;&lt; <a href="ident?i=tcp_hashinfo">tcp_hashinfo</a>.bhash_size;
<a name="L3081" href="source/net/ipv4/tcp.c#L3081">3081</a>         for (<a href="ident?i=i">i</a> = 0; <a href="ident?i=i">i</a> &lt; <a href="ident?i=tcp_hashinfo">tcp_hashinfo</a>.bhash_size; <a href="ident?i=i">i</a>++) {
<a name="L3082" href="source/net/ipv4/tcp.c#L3082">3082</a>                 <a href="ident?i=spin_lock_init">spin_lock_init</a>(&amp;<a href="ident?i=tcp_hashinfo">tcp_hashinfo</a>.bhash[<a href="ident?i=i">i</a>].<a href="ident?i=lock">lock</a>);
<a name="L3083" href="source/net/ipv4/tcp.c#L3083">3083</a>                 <a href="ident?i=INIT_HLIST_HEAD">INIT_HLIST_HEAD</a>(&amp;<a href="ident?i=tcp_hashinfo">tcp_hashinfo</a>.bhash[<a href="ident?i=i">i</a>].<a href="ident?i=chain">chain</a>);
<a name="L3084" href="source/net/ipv4/tcp.c#L3084">3084</a>         }
<a name="L3085" href="source/net/ipv4/tcp.c#L3085">3085</a> 
<a name="L3086" href="source/net/ipv4/tcp.c#L3086">3086</a> 
<a name="L3087" href="source/net/ipv4/tcp.c#L3087">3087</a>         cnt = <a href="ident?i=tcp_hashinfo">tcp_hashinfo</a>.ehash_mask + 1;
<a name="L3088" href="source/net/ipv4/tcp.c#L3088">3088</a> 
<a name="L3089" href="source/net/ipv4/tcp.c#L3089">3089</a>         <a href="ident?i=tcp_death_row">tcp_death_row</a>.sysctl_max_tw_buckets = cnt / 2;
<a name="L3090" href="source/net/ipv4/tcp.c#L3090">3090</a>         <a href="ident?i=sysctl_tcp_max_orphans">sysctl_tcp_max_orphans</a> = cnt / 2;
<a name="L3091" href="source/net/ipv4/tcp.c#L3091">3091</a>         <a href="ident?i=sysctl_max_syn_backlog">sysctl_max_syn_backlog</a> = <a href="ident?i=max">max</a>(128, cnt / 256);
<a name="L3092" href="source/net/ipv4/tcp.c#L3092">3092</a> 
<a name="L3093" href="source/net/ipv4/tcp.c#L3093">3093</a>         <a href="ident?i=tcp_init_mem">tcp_init_mem</a>();
<a name="L3094" href="source/net/ipv4/tcp.c#L3094">3094</a>         <b><i>/* Set per-socket limits to no more than 1/128 the pressure threshold */</i></b>
<a name="L3095" href="source/net/ipv4/tcp.c#L3095">3095</a>         <a href="ident?i=limit">limit</a> = <a href="ident?i=nr_free_buffer_pages">nr_free_buffer_pages</a>() &lt;&lt; (<a href="ident?i=PAGE_SHIFT">PAGE_SHIFT</a> - 7);
<a name="L3096" href="source/net/ipv4/tcp.c#L3096">3096</a>         max_wshare = <a href="ident?i=min">min</a>(4UL*1024*1024, <a href="ident?i=limit">limit</a>);
<a name="L3097" href="source/net/ipv4/tcp.c#L3097">3097</a>         max_rshare = <a href="ident?i=min">min</a>(6UL*1024*1024, <a href="ident?i=limit">limit</a>);
<a name="L3098" href="source/net/ipv4/tcp.c#L3098">3098</a> 
<a name="L3099" href="source/net/ipv4/tcp.c#L3099">3099</a>         <a href="ident?i=sysctl_tcp_wmem">sysctl_tcp_wmem</a>[0] = <a href="ident?i=SK_MEM_QUANTUM">SK_MEM_QUANTUM</a>;
<a name="L3100" href="source/net/ipv4/tcp.c#L3100">3100</a>         <a href="ident?i=sysctl_tcp_wmem">sysctl_tcp_wmem</a>[1] = 16*1024;
<a name="L3101" href="source/net/ipv4/tcp.c#L3101">3101</a>         <a href="ident?i=sysctl_tcp_wmem">sysctl_tcp_wmem</a>[2] = <a href="ident?i=max">max</a>(64*1024, max_wshare);
<a name="L3102" href="source/net/ipv4/tcp.c#L3102">3102</a> 
<a name="L3103" href="source/net/ipv4/tcp.c#L3103">3103</a>         <a href="ident?i=sysctl_tcp_rmem">sysctl_tcp_rmem</a>[0] = <a href="ident?i=SK_MEM_QUANTUM">SK_MEM_QUANTUM</a>;
<a name="L3104" href="source/net/ipv4/tcp.c#L3104">3104</a>         <a href="ident?i=sysctl_tcp_rmem">sysctl_tcp_rmem</a>[1] = 87380;
<a name="L3105" href="source/net/ipv4/tcp.c#L3105">3105</a>         <a href="ident?i=sysctl_tcp_rmem">sysctl_tcp_rmem</a>[2] = <a href="ident?i=max">max</a>(87380, max_rshare);
<a name="L3106" href="source/net/ipv4/tcp.c#L3106">3106</a> 
<a name="L3107" href="source/net/ipv4/tcp.c#L3107">3107</a>         <a href="ident?i=pr_info">pr_info</a>(<i>"Hash tables configured (established %u bind %u)\n"</i>,
<a name="L3108" href="source/net/ipv4/tcp.c#L3108">3108</a>                 <a href="ident?i=tcp_hashinfo">tcp_hashinfo</a>.ehash_mask + 1, <a href="ident?i=tcp_hashinfo">tcp_hashinfo</a>.bhash_size);
<a name="L3109" href="source/net/ipv4/tcp.c#L3109">3109</a> 
<a name="L3110" href="source/net/ipv4/tcp.c#L3110">3110</a>         <a href="ident?i=tcp_metrics_init">tcp_metrics_init</a>();
<a name="L3111" href="source/net/ipv4/tcp.c#L3111">3111</a>         <a href="ident?i=BUG_ON">BUG_ON</a>(<a href="ident?i=tcp_register_congestion_control">tcp_register_congestion_control</a>(&amp;<a href="ident?i=tcp_reno">tcp_reno</a>) != 0);
<a name="L3112" href="source/net/ipv4/tcp.c#L3112">3112</a>         <a href="ident?i=tcp_tasklet_init">tcp_tasklet_init</a>();
<a name="L3113" href="source/net/ipv4/tcp.c#L3113">3113</a> }
<a name="L3114" href="source/net/ipv4/tcp.c#L3114">3114</a> </pre></div><p>
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
